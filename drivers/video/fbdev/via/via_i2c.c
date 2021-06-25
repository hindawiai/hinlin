<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright 1998-2009 VIA Technologies, Inc. All Rights Reserved.
 * Copyright 2001-2008 S3 Graphics, Inc. All Rights Reserved.

 */

#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/delay.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/module.h>
#समावेश <linux/via-core.h>
#समावेश <linux/via_i2c.h>

/*
 * There can only be one set of these, so there's no poपूर्णांक in having
 * them be dynamically allocated...
 */
#घोषणा VIAFB_NUM_I2C		5
अटल काष्ठा via_i2c_stuff via_i2c_par[VIAFB_NUM_I2C];
अटल काष्ठा viafb_dev *i2c_vdev;  /* Passed in from core */

अटल व्योम via_i2c_setscl(व्योम *data, पूर्णांक state)
अणु
	u8 val;
	काष्ठा via_port_cfg *adap_data = data;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&i2c_vdev->reg_lock, flags);
	val = via_पढ़ो_reg(adap_data->io_port, adap_data->ioport_index) & 0xF0;
	अगर (state)
		val |= 0x20;
	अन्यथा
		val &= ~0x20;
	चयन (adap_data->type) अणु
	हाल VIA_PORT_I2C:
		val |= 0x01;
		अवरोध;
	हाल VIA_PORT_GPIO:
		val |= 0x82;
		अवरोध;
	शेष:
		prपूर्णांकk(KERN_ERR "viafb_i2c: specify wrong i2c type.\n");
	पूर्ण
	via_ग_लिखो_reg(adap_data->io_port, adap_data->ioport_index, val);
	spin_unlock_irqrestore(&i2c_vdev->reg_lock, flags);
पूर्ण

अटल पूर्णांक via_i2c_माला_लोcl(व्योम *data)
अणु
	काष्ठा via_port_cfg *adap_data = data;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;

	spin_lock_irqsave(&i2c_vdev->reg_lock, flags);
	अगर (adap_data->type == VIA_PORT_GPIO)
		via_ग_लिखो_reg_mask(adap_data->io_port, adap_data->ioport_index,
			0, 0x80);
	अगर (via_पढ़ो_reg(adap_data->io_port, adap_data->ioport_index) & 0x08)
		ret = 1;
	spin_unlock_irqrestore(&i2c_vdev->reg_lock, flags);
	वापस ret;
पूर्ण

अटल पूर्णांक via_i2c_माला_लोda(व्योम *data)
अणु
	काष्ठा via_port_cfg *adap_data = data;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;

	spin_lock_irqsave(&i2c_vdev->reg_lock, flags);
	अगर (adap_data->type == VIA_PORT_GPIO)
		via_ग_लिखो_reg_mask(adap_data->io_port, adap_data->ioport_index,
			0, 0x40);
	अगर (via_पढ़ो_reg(adap_data->io_port, adap_data->ioport_index) & 0x04)
		ret = 1;
	spin_unlock_irqrestore(&i2c_vdev->reg_lock, flags);
	वापस ret;
पूर्ण

अटल व्योम via_i2c_setsda(व्योम *data, पूर्णांक state)
अणु
	u8 val;
	काष्ठा via_port_cfg *adap_data = data;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&i2c_vdev->reg_lock, flags);
	val = via_पढ़ो_reg(adap_data->io_port, adap_data->ioport_index) & 0xF0;
	अगर (state)
		val |= 0x10;
	अन्यथा
		val &= ~0x10;
	चयन (adap_data->type) अणु
	हाल VIA_PORT_I2C:
		val |= 0x01;
		अवरोध;
	हाल VIA_PORT_GPIO:
		val |= 0x42;
		अवरोध;
	शेष:
		prपूर्णांकk(KERN_ERR "viafb_i2c: specify wrong i2c type.\n");
	पूर्ण
	via_ग_लिखो_reg(adap_data->io_port, adap_data->ioport_index, val);
	spin_unlock_irqrestore(&i2c_vdev->reg_lock, flags);
पूर्ण

पूर्णांक viafb_i2c_पढ़ोbyte(u8 adap, u8 slave_addr, u8 index, u8 *pdata)
अणु
	पूर्णांक ret;
	u8 mm1[] = अणु0x00पूर्ण;
	काष्ठा i2c_msg msgs[2];

	अगर (!via_i2c_par[adap].is_active)
		वापस -ENODEV;
	*pdata = 0;
	msgs[0].flags = 0;
	msgs[1].flags = I2C_M_RD;
	msgs[0].addr = msgs[1].addr = slave_addr / 2;
	mm1[0] = index;
	msgs[0].len = 1; msgs[1].len = 1;
	msgs[0].buf = mm1; msgs[1].buf = pdata;
	ret = i2c_transfer(&via_i2c_par[adap].adapter, msgs, 2);
	अगर (ret == 2)
		ret = 0;
	अन्यथा अगर (ret >= 0)
		ret = -EIO;

	वापस ret;
पूर्ण

पूर्णांक viafb_i2c_ग_लिखोbyte(u8 adap, u8 slave_addr, u8 index, u8 data)
अणु
	पूर्णांक ret;
	u8 msg[2] = अणु index, data पूर्ण;
	काष्ठा i2c_msg msgs;

	अगर (!via_i2c_par[adap].is_active)
		वापस -ENODEV;
	msgs.flags = 0;
	msgs.addr = slave_addr / 2;
	msgs.len = 2;
	msgs.buf = msg;
	ret = i2c_transfer(&via_i2c_par[adap].adapter, &msgs, 1);
	अगर (ret == 1)
		ret = 0;
	अन्यथा अगर (ret >= 0)
		ret = -EIO;

	वापस ret;
पूर्ण

पूर्णांक viafb_i2c_पढ़ोbytes(u8 adap, u8 slave_addr, u8 index, u8 *buff, पूर्णांक buff_len)
अणु
	पूर्णांक ret;
	u8 mm1[] = अणु0x00पूर्ण;
	काष्ठा i2c_msg msgs[2];

	अगर (!via_i2c_par[adap].is_active)
		वापस -ENODEV;
	msgs[0].flags = 0;
	msgs[1].flags = I2C_M_RD;
	msgs[0].addr = msgs[1].addr = slave_addr / 2;
	mm1[0] = index;
	msgs[0].len = 1; msgs[1].len = buff_len;
	msgs[0].buf = mm1; msgs[1].buf = buff;
	ret = i2c_transfer(&via_i2c_par[adap].adapter, msgs, 2);
	अगर (ret == 2)
		ret = 0;
	अन्यथा अगर (ret >= 0)
		ret = -EIO;

	वापस ret;
पूर्ण

/*
 * Allow other viafb subdevices to look up a specअगरic adapter
 * by port name.
 */
काष्ठा i2c_adapter *viafb_find_i2c_adapter(क्रमागत viafb_i2c_adap which)
अणु
	काष्ठा via_i2c_stuff *stuff = &via_i2c_par[which];

	वापस &stuff->adapter;
पूर्ण
EXPORT_SYMBOL_GPL(viafb_find_i2c_adapter);


अटल पूर्णांक create_i2c_bus(काष्ठा i2c_adapter *adapter,
			  काष्ठा i2c_algo_bit_data *algo,
			  काष्ठा via_port_cfg *adap_cfg,
			  काष्ठा pci_dev *pdev)
अणु
	algo->setsda = via_i2c_setsda;
	algo->setscl = via_i2c_setscl;
	algo->माला_लोda = via_i2c_माला_लोda;
	algo->माला_लोcl = via_i2c_माला_लोcl;
	algo->udelay = 10;
	algo->समयout = 2;
	algo->data = adap_cfg;

	प्र_लिखो(adapter->name, "viafb i2c io_port idx 0x%02x",
		adap_cfg->ioport_index);
	adapter->owner = THIS_MODULE;
	adapter->class = I2C_CLASS_DDC;
	adapter->algo_data = algo;
	अगर (pdev)
		adapter->dev.parent = &pdev->dev;
	अन्यथा
		adapter->dev.parent = शून्य;
	/* i2c_set_adapdata(adapter, adap_cfg); */

	/* Raise SCL and SDA */
	via_i2c_setsda(adap_cfg, 1);
	via_i2c_setscl(adap_cfg, 1);
	udelay(20);

	वापस i2c_bit_add_bus(adapter);
पूर्ण

अटल पूर्णांक viafb_i2c_probe(काष्ठा platक्रमm_device *platdev)
अणु
	पूर्णांक i, ret;
	काष्ठा via_port_cfg *configs;

	i2c_vdev = platdev->dev.platक्रमm_data;
	configs = i2c_vdev->port_cfg;

	क्रम (i = 0; i < VIAFB_NUM_PORTS; i++) अणु
		काष्ठा via_port_cfg *adap_cfg = configs++;
		काष्ठा via_i2c_stuff *i2c_stuff = &via_i2c_par[i];

		i2c_stuff->is_active = 0;
		अगर (adap_cfg->type == 0 || adap_cfg->mode != VIA_MODE_I2C)
			जारी;
		ret = create_i2c_bus(&i2c_stuff->adapter,
				     &i2c_stuff->algo, adap_cfg,
				शून्य); /* FIXME: PCIDEV */
		अगर (ret < 0) अणु
			prपूर्णांकk(KERN_ERR "viafb: cannot create i2c bus %u:%d\n",
				i, ret);
			जारी;  /* Still try to make the rest */
		पूर्ण
		i2c_stuff->is_active = 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक viafb_i2c_हटाओ(काष्ठा platक्रमm_device *platdev)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < VIAFB_NUM_PORTS; i++) अणु
		काष्ठा via_i2c_stuff *i2c_stuff = &via_i2c_par[i];
		/*
		 * Only हटाओ those entries in the array that we've
		 * actually used (and thus initialized algo_data)
		 */
		अगर (i2c_stuff->is_active)
			i2c_del_adapter(&i2c_stuff->adapter);
	पूर्ण
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver via_i2c_driver = अणु
	.driver = अणु
		.name = "viafb-i2c",
	पूर्ण,
	.probe = viafb_i2c_probe,
	.हटाओ = viafb_i2c_हटाओ,
पूर्ण;

पूर्णांक viafb_i2c_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&via_i2c_driver);
पूर्ण

व्योम viafb_i2c_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&via_i2c_driver);
पूर्ण
