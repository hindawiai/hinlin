<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * I2C bus driver क्रम Kontron COM modules
 *
 * Copyright (c) 2010-2013 Kontron Europe GmbH
 * Author: Michael Brunner <michael.brunner@kontron.com>
 *
 * The driver is based on the i2c-ocores driver by Peter Korsgaard.
 */

#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/i2c.h>
#समावेश <linux/delay.h>
#समावेश <linux/mfd/kempld.h>

#घोषणा KEMPLD_I2C_PRELOW	0x0b
#घोषणा KEMPLD_I2C_PREHIGH	0x0c
#घोषणा KEMPLD_I2C_DATA		0x0e

#घोषणा KEMPLD_I2C_CTRL		0x0d
#घोषणा I2C_CTRL_IEN		0x40
#घोषणा I2C_CTRL_EN		0x80

#घोषणा KEMPLD_I2C_STAT		0x0f
#घोषणा I2C_STAT_IF		0x01
#घोषणा I2C_STAT_TIP		0x02
#घोषणा I2C_STAT_ARBLOST	0x20
#घोषणा I2C_STAT_BUSY		0x40
#घोषणा I2C_STAT_NACK		0x80

#घोषणा KEMPLD_I2C_CMD		0x0f
#घोषणा I2C_CMD_START		0x91
#घोषणा I2C_CMD_STOP		0x41
#घोषणा I2C_CMD_READ		0x21
#घोषणा I2C_CMD_WRITE		0x11
#घोषणा I2C_CMD_READ_ACK	0x21
#घोषणा I2C_CMD_READ_NACK	0x29
#घोषणा I2C_CMD_IACK		0x01

#घोषणा KEMPLD_I2C_FREQ_MAX	2700	/* 2.7 mHz */
#घोषणा KEMPLD_I2C_FREQ_STD	100	/* 100 kHz */

क्रमागत अणु
	STATE_DONE = 0,
	STATE_INIT,
	STATE_ADDR,
	STATE_ADDR10,
	STATE_START,
	STATE_WRITE,
	STATE_READ,
	STATE_ERROR,
पूर्ण;

काष्ठा kempld_i2c_data अणु
	काष्ठा device			*dev;
	काष्ठा kempld_device_data	*pld;
	काष्ठा i2c_adapter		adap;
	काष्ठा i2c_msg			*msg;
	पूर्णांक				pos;
	पूर्णांक				nmsgs;
	पूर्णांक				state;
	bool				was_active;
पूर्ण;

अटल अचिन्हित पूर्णांक bus_frequency = KEMPLD_I2C_FREQ_STD;
module_param(bus_frequency, uपूर्णांक, 0);
MODULE_PARM_DESC(bus_frequency, "Set I2C bus frequency in kHz (default="
				__MODULE_STRING(KEMPLD_I2C_FREQ_STD)")");

अटल पूर्णांक i2c_bus = -1;
module_param(i2c_bus, पूर्णांक, 0);
MODULE_PARM_DESC(i2c_bus, "Set I2C bus number (default=-1 for dynamic assignment)");

अटल bool i2c_gpio_mux;
module_param(i2c_gpio_mux, bool, 0);
MODULE_PARM_DESC(i2c_gpio_mux, "Enable I2C port on GPIO out (default=false)");

/*
 * kempld_get_mutex must be called prior to calling this function.
 */
अटल पूर्णांक kempld_i2c_process(काष्ठा kempld_i2c_data *i2c)
अणु
	काष्ठा kempld_device_data *pld = i2c->pld;
	u8 stat = kempld_पढ़ो8(pld, KEMPLD_I2C_STAT);
	काष्ठा i2c_msg *msg = i2c->msg;
	u8 addr;

	/* Ready? */
	अगर (stat & I2C_STAT_TIP)
		वापस -EBUSY;

	अगर (i2c->state == STATE_DONE || i2c->state == STATE_ERROR) अणु
		/* Stop has been sent */
		kempld_ग_लिखो8(pld, KEMPLD_I2C_CMD, I2C_CMD_IACK);
		अगर (i2c->state == STATE_ERROR)
			वापस -EIO;
		वापस 0;
	पूर्ण

	/* Error? */
	अगर (stat & I2C_STAT_ARBLOST) अणु
		i2c->state = STATE_ERROR;
		kempld_ग_लिखो8(pld, KEMPLD_I2C_CMD, I2C_CMD_STOP);
		वापस -EAGAIN;
	पूर्ण

	अगर (i2c->state == STATE_INIT) अणु
		अगर (stat & I2C_STAT_BUSY)
			वापस -EBUSY;

		i2c->state = STATE_ADDR;
	पूर्ण

	अगर (i2c->state == STATE_ADDR) अणु
		/* 10 bit address? */
		अगर (i2c->msg->flags & I2C_M_TEN) अणु
			addr = 0xf0 | ((i2c->msg->addr >> 7) & 0x6);
			/* Set पढ़ो bit अगर necessary */
			addr |= (i2c->msg->flags & I2C_M_RD) ? 1 : 0;
			i2c->state = STATE_ADDR10;
		पूर्ण अन्यथा अणु
			addr = i2c_8bit_addr_from_msg(i2c->msg);
			i2c->state = STATE_START;
		पूर्ण

		kempld_ग_लिखो8(pld, KEMPLD_I2C_DATA, addr);
		kempld_ग_लिखो8(pld, KEMPLD_I2C_CMD, I2C_CMD_START);

		वापस 0;
	पूर्ण

	/* Second part of 10 bit addressing */
	अगर (i2c->state == STATE_ADDR10) अणु
		kempld_ग_लिखो8(pld, KEMPLD_I2C_DATA, i2c->msg->addr & 0xff);
		kempld_ग_लिखो8(pld, KEMPLD_I2C_CMD, I2C_CMD_WRITE);

		i2c->state = STATE_START;
		वापस 0;
	पूर्ण

	अगर (i2c->state == STATE_START || i2c->state == STATE_WRITE) अणु
		i2c->state = (msg->flags & I2C_M_RD) ? STATE_READ : STATE_WRITE;

		अगर (stat & I2C_STAT_NACK) अणु
			i2c->state = STATE_ERROR;
			kempld_ग_लिखो8(pld, KEMPLD_I2C_CMD, I2C_CMD_STOP);
			वापस -ENXIO;
		पूर्ण
	पूर्ण अन्यथा अणु
		msg->buf[i2c->pos++] = kempld_पढ़ो8(pld, KEMPLD_I2C_DATA);
	पूर्ण

	अगर (i2c->pos >= msg->len) अणु
		i2c->nmsgs--;
		i2c->msg++;
		i2c->pos = 0;
		msg = i2c->msg;

		अगर (i2c->nmsgs) अणु
			अगर (!(msg->flags & I2C_M_NOSTART)) अणु
				i2c->state = STATE_ADDR;
				वापस 0;
			पूर्ण अन्यथा अणु
				i2c->state = (msg->flags & I2C_M_RD)
					? STATE_READ : STATE_WRITE;
			पूर्ण
		पूर्ण अन्यथा अणु
			i2c->state = STATE_DONE;
			kempld_ग_लिखो8(pld, KEMPLD_I2C_CMD, I2C_CMD_STOP);
			वापस 0;
		पूर्ण
	पूर्ण

	अगर (i2c->state == STATE_READ) अणु
		kempld_ग_लिखो8(pld, KEMPLD_I2C_CMD, i2c->pos == (msg->len - 1) ?
			      I2C_CMD_READ_NACK : I2C_CMD_READ_ACK);
	पूर्ण अन्यथा अणु
		kempld_ग_लिखो8(pld, KEMPLD_I2C_DATA, msg->buf[i2c->pos++]);
		kempld_ग_लिखो8(pld, KEMPLD_I2C_CMD, I2C_CMD_WRITE);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक kempld_i2c_xfer(काष्ठा i2c_adapter *adap, काष्ठा i2c_msg *msgs,
				पूर्णांक num)
अणु
	काष्ठा kempld_i2c_data *i2c = i2c_get_adapdata(adap);
	काष्ठा kempld_device_data *pld = i2c->pld;
	अचिन्हित दीर्घ समयout = jअगरfies + HZ;
	पूर्णांक ret;

	i2c->msg = msgs;
	i2c->pos = 0;
	i2c->nmsgs = num;
	i2c->state = STATE_INIT;

	/* Handle the transfer */
	जबतक (समय_beक्रमe(jअगरfies, समयout)) अणु
		kempld_get_mutex(pld);
		ret = kempld_i2c_process(i2c);
		kempld_release_mutex(pld);

		अगर (i2c->state == STATE_DONE || i2c->state == STATE_ERROR)
			वापस (i2c->state == STATE_DONE) ? num : ret;

		अगर (ret == 0)
			समयout = jअगरfies + HZ;

		usleep_range(5, 15);
	पूर्ण

	i2c->state = STATE_ERROR;

	वापस -ETIMEDOUT;
पूर्ण

/*
 * kempld_get_mutex must be called prior to calling this function.
 */
अटल व्योम kempld_i2c_device_init(काष्ठा kempld_i2c_data *i2c)
अणु
	काष्ठा kempld_device_data *pld = i2c->pld;
	u16 prescale_corr;
	दीर्घ prescale;
	u8 ctrl;
	u8 stat;
	u8 cfg;

	/* Make sure the device is disabled */
	ctrl = kempld_पढ़ो8(pld, KEMPLD_I2C_CTRL);
	ctrl &= ~(I2C_CTRL_EN | I2C_CTRL_IEN);
	kempld_ग_लिखो8(pld, KEMPLD_I2C_CTRL, ctrl);

	अगर (bus_frequency > KEMPLD_I2C_FREQ_MAX)
		bus_frequency = KEMPLD_I2C_FREQ_MAX;

	अगर (pld->info.spec_major == 1)
		prescale = pld->pld_घड़ी / (bus_frequency * 5) - 1000;
	अन्यथा
		prescale = pld->pld_घड़ी / (bus_frequency * 4) - 3000;

	अगर (prescale < 0)
		prescale = 0;

	/* Round to the best matching value */
	prescale_corr = prescale / 1000;
	अगर (prescale % 1000 >= 500)
		prescale_corr++;

	kempld_ग_लिखो8(pld, KEMPLD_I2C_PRELOW, prescale_corr & 0xff);
	kempld_ग_लिखो8(pld, KEMPLD_I2C_PREHIGH, prescale_corr >> 8);

	/* Activate I2C bus output on GPIO pins */
	cfg = kempld_पढ़ो8(pld, KEMPLD_CFG);
	अगर (i2c_gpio_mux)
		cfg |= KEMPLD_CFG_GPIO_I2C_MUX;
	अन्यथा
		cfg &= ~KEMPLD_CFG_GPIO_I2C_MUX;
	kempld_ग_लिखो8(pld, KEMPLD_CFG, cfg);

	/* Enable the device */
	kempld_ग_लिखो8(pld, KEMPLD_I2C_CMD, I2C_CMD_IACK);
	ctrl |= I2C_CTRL_EN;
	kempld_ग_लिखो8(pld, KEMPLD_I2C_CTRL, ctrl);

	stat = kempld_पढ़ो8(pld, KEMPLD_I2C_STAT);
	अगर (stat & I2C_STAT_BUSY)
		kempld_ग_लिखो8(pld, KEMPLD_I2C_CMD, I2C_CMD_STOP);
पूर्ण

अटल u32 kempld_i2c_func(काष्ठा i2c_adapter *adap)
अणु
	वापस I2C_FUNC_I2C | I2C_FUNC_10BIT_ADDR | I2C_FUNC_SMBUS_EMUL;
पूर्ण

अटल स्थिर काष्ठा i2c_algorithm kempld_i2c_algorithm = अणु
	.master_xfer	= kempld_i2c_xfer,
	.functionality	= kempld_i2c_func,
पूर्ण;

अटल स्थिर काष्ठा i2c_adapter kempld_i2c_adapter = अणु
	.owner		= THIS_MODULE,
	.name		= "i2c-kempld",
	.class		= I2C_CLASS_HWMON | I2C_CLASS_SPD,
	.algo		= &kempld_i2c_algorithm,
पूर्ण;

अटल पूर्णांक kempld_i2c_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा kempld_device_data *pld = dev_get_drvdata(pdev->dev.parent);
	काष्ठा kempld_i2c_data *i2c;
	पूर्णांक ret;
	u8 ctrl;

	i2c = devm_kzalloc(&pdev->dev, माप(*i2c), GFP_KERNEL);
	अगर (!i2c)
		वापस -ENOMEM;

	i2c->pld = pld;
	i2c->dev = &pdev->dev;
	i2c->adap = kempld_i2c_adapter;
	i2c->adap.dev.parent = i2c->dev;
	i2c_set_adapdata(&i2c->adap, i2c);
	platक्रमm_set_drvdata(pdev, i2c);

	kempld_get_mutex(pld);
	ctrl = kempld_पढ़ो8(pld, KEMPLD_I2C_CTRL);

	अगर (ctrl & I2C_CTRL_EN)
		i2c->was_active = true;

	kempld_i2c_device_init(i2c);
	kempld_release_mutex(pld);

	/* Add I2C adapter to I2C tree */
	अगर (i2c_bus >= -1)
		i2c->adap.nr = i2c_bus;
	ret = i2c_add_numbered_adapter(&i2c->adap);
	अगर (ret)
		वापस ret;

	dev_info(i2c->dev, "I2C bus initialized at %dkHz\n",
		 bus_frequency);

	वापस 0;
पूर्ण

अटल पूर्णांक kempld_i2c_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा kempld_i2c_data *i2c = platक्रमm_get_drvdata(pdev);
	काष्ठा kempld_device_data *pld = i2c->pld;
	u8 ctrl;

	kempld_get_mutex(pld);
	/*
	 * Disable I2C logic अगर it was not activated beक्रमe the
	 * driver loaded
	 */
	अगर (!i2c->was_active) अणु
		ctrl = kempld_पढ़ो8(pld, KEMPLD_I2C_CTRL);
		ctrl &= ~I2C_CTRL_EN;
		kempld_ग_लिखो8(pld, KEMPLD_I2C_CTRL, ctrl);
	पूर्ण
	kempld_release_mutex(pld);

	i2c_del_adapter(&i2c->adap);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक kempld_i2c_suspend(काष्ठा platक्रमm_device *pdev, pm_message_t state)
अणु
	काष्ठा kempld_i2c_data *i2c = platक्रमm_get_drvdata(pdev);
	काष्ठा kempld_device_data *pld = i2c->pld;
	u8 ctrl;

	kempld_get_mutex(pld);
	ctrl = kempld_पढ़ो8(pld, KEMPLD_I2C_CTRL);
	ctrl &= ~I2C_CTRL_EN;
	kempld_ग_लिखो8(pld, KEMPLD_I2C_CTRL, ctrl);
	kempld_release_mutex(pld);

	वापस 0;
पूर्ण

अटल पूर्णांक kempld_i2c_resume(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा kempld_i2c_data *i2c = platक्रमm_get_drvdata(pdev);
	काष्ठा kempld_device_data *pld = i2c->pld;

	kempld_get_mutex(pld);
	kempld_i2c_device_init(i2c);
	kempld_release_mutex(pld);

	वापस 0;
पूर्ण
#अन्यथा
#घोषणा kempld_i2c_suspend	शून्य
#घोषणा kempld_i2c_resume	शून्य
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver kempld_i2c_driver = अणु
	.driver = अणु
		.name = "kempld-i2c",
	पूर्ण,
	.probe		= kempld_i2c_probe,
	.हटाओ		= kempld_i2c_हटाओ,
	.suspend	= kempld_i2c_suspend,
	.resume		= kempld_i2c_resume,
पूर्ण;

module_platक्रमm_driver(kempld_i2c_driver);

MODULE_DESCRIPTION("KEM PLD I2C Driver");
MODULE_AUTHOR("Michael Brunner <michael.brunner@kontron.com>");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:kempld_i2c");
