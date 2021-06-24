<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Support Infineon TLE62x0 driver chips
 *
 * Copyright (c) 2007 Simtec Electronics
 *	Ben Dooks, <ben@simtec.co.uk>
 */

#समावेश <linux/device.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>

#समावेश <linux/spi/spi.h>
#समावेश <linux/spi/tle62x0.h>


#घोषणा CMD_READ	0x00
#घोषणा CMD_SET		0xff

#घोषणा DIAG_NORMAL	0x03
#घोषणा DIAG_OVERLOAD	0x02
#घोषणा DIAG_OPEN	0x01
#घोषणा DIAG_SHORTGND	0x00

काष्ठा tle62x0_state अणु
	काष्ठा spi_device	*us;
	काष्ठा mutex		lock;
	अचिन्हित पूर्णांक		nr_gpio;
	अचिन्हित पूर्णांक		gpio_state;

	अचिन्हित अक्षर		tx_buff[4];
	अचिन्हित अक्षर		rx_buff[4];
पूर्ण;

अटल पूर्णांक to_gpio_num(काष्ठा device_attribute *attr);

अटल अंतरभूत पूर्णांक tle62x0_ग_लिखो(काष्ठा tle62x0_state *st)
अणु
	अचिन्हित अक्षर *buff = st->tx_buff;
	अचिन्हित पूर्णांक gpio_state = st->gpio_state;

	buff[0] = CMD_SET;

	अगर (st->nr_gpio == 16) अणु
		buff[1] = gpio_state >> 8;
		buff[2] = gpio_state;
	पूर्ण अन्यथा अणु
		buff[1] = gpio_state;
	पूर्ण

	dev_dbg(&st->us->dev, "buff %3ph\n", buff);

	वापस spi_ग_लिखो(st->us, buff, (st->nr_gpio == 16) ? 3 : 2);
पूर्ण

अटल अंतरभूत पूर्णांक tle62x0_पढ़ो(काष्ठा tle62x0_state *st)
अणु
	अचिन्हित अक्षर *txbuff = st->tx_buff;
	काष्ठा spi_transfer xfer = अणु
		.tx_buf		= txbuff,
		.rx_buf		= st->rx_buff,
		.len		= (st->nr_gpio * 2) / 8,
	पूर्ण;
	काष्ठा spi_message msg;

	txbuff[0] = CMD_READ;
	txbuff[1] = 0x00;
	txbuff[2] = 0x00;
	txbuff[3] = 0x00;

	spi_message_init(&msg);
	spi_message_add_tail(&xfer, &msg);

	वापस spi_sync(st->us, &msg);
पूर्ण

अटल अचिन्हित अक्षर *decode_fault(अचिन्हित पूर्णांक fault_code)
अणु
	fault_code &= 3;

	चयन (fault_code) अणु
	हाल DIAG_NORMAL:
		वापस "N";
	हाल DIAG_OVERLOAD:
		वापस "V";
	हाल DIAG_OPEN:
		वापस "O";
	हाल DIAG_SHORTGND:
		वापस "G";
	पूर्ण

	वापस "?";
पूर्ण

अटल sमाप_प्रकार tle62x0_status_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा tle62x0_state *st = dev_get_drvdata(dev);
	अक्षर *bp = buf;
	अचिन्हित अक्षर *buff = st->rx_buff;
	अचिन्हित दीर्घ fault = 0;
	पूर्णांक ptr;
	पूर्णांक ret;

	mutex_lock(&st->lock);
	ret = tle62x0_पढ़ो(st);
	dev_dbg(dev, "tle62x0_read() returned %d\n", ret);
	अगर (ret < 0) अणु
		mutex_unlock(&st->lock);
		वापस ret;
	पूर्ण

	क्रम (ptr = 0; ptr < (st->nr_gpio * 2)/8; ptr += 1) अणु
		fault <<= 8;
		fault  |= ((अचिन्हित दीर्घ)buff[ptr]);

		dev_dbg(dev, "byte %d is %02x\n", ptr, buff[ptr]);
	पूर्ण

	क्रम (ptr = 0; ptr < st->nr_gpio; ptr++) अणु
		bp += प्र_लिखो(bp, "%s ", decode_fault(fault >> (ptr * 2)));
	पूर्ण

	*bp++ = '\n';

	mutex_unlock(&st->lock);
	वापस bp - buf;
पूर्ण

अटल DEVICE_ATTR(status_show, S_IRUGO, tle62x0_status_show, शून्य);

अटल sमाप_प्रकार tle62x0_gpio_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा tle62x0_state *st = dev_get_drvdata(dev);
	पूर्णांक gpio_num = to_gpio_num(attr);
	पूर्णांक value;

	mutex_lock(&st->lock);
	value = (st->gpio_state >> gpio_num) & 1;
	mutex_unlock(&st->lock);

	वापस snम_लिखो(buf, PAGE_SIZE, "%d", value);
पूर्ण

अटल sमाप_प्रकार tle62x0_gpio_store(काष्ठा device *dev,
		काष्ठा device_attribute *attr,
		स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा tle62x0_state *st = dev_get_drvdata(dev);
	पूर्णांक gpio_num = to_gpio_num(attr);
	अचिन्हित दीर्घ val;
	अक्षर *endp;

	val = simple_म_से_अदीर्घ(buf, &endp, 0);
	अगर (buf == endp)
		वापस -EINVAL;

	dev_dbg(dev, "setting gpio %d to %ld\n", gpio_num, val);

	mutex_lock(&st->lock);

	अगर (val)
		st->gpio_state |= 1 << gpio_num;
	अन्यथा
		st->gpio_state &= ~(1 << gpio_num);

	tle62x0_ग_लिखो(st);
	mutex_unlock(&st->lock);

	वापस len;
पूर्ण

अटल DEVICE_ATTR(gpio1, S_IWUSR|S_IRUGO,
		tle62x0_gpio_show, tle62x0_gpio_store);
अटल DEVICE_ATTR(gpio2, S_IWUSR|S_IRUGO,
		tle62x0_gpio_show, tle62x0_gpio_store);
अटल DEVICE_ATTR(gpio3, S_IWUSR|S_IRUGO,
		tle62x0_gpio_show, tle62x0_gpio_store);
अटल DEVICE_ATTR(gpio4, S_IWUSR|S_IRUGO,
		tle62x0_gpio_show, tle62x0_gpio_store);
अटल DEVICE_ATTR(gpio5, S_IWUSR|S_IRUGO,
		tle62x0_gpio_show, tle62x0_gpio_store);
अटल DEVICE_ATTR(gpio6, S_IWUSR|S_IRUGO,
		tle62x0_gpio_show, tle62x0_gpio_store);
अटल DEVICE_ATTR(gpio7, S_IWUSR|S_IRUGO,
		tle62x0_gpio_show, tle62x0_gpio_store);
अटल DEVICE_ATTR(gpio8, S_IWUSR|S_IRUGO,
		tle62x0_gpio_show, tle62x0_gpio_store);
अटल DEVICE_ATTR(gpio9, S_IWUSR|S_IRUGO,
		tle62x0_gpio_show, tle62x0_gpio_store);
अटल DEVICE_ATTR(gpio10, S_IWUSR|S_IRUGO,
		tle62x0_gpio_show, tle62x0_gpio_store);
अटल DEVICE_ATTR(gpio11, S_IWUSR|S_IRUGO,
		tle62x0_gpio_show, tle62x0_gpio_store);
अटल DEVICE_ATTR(gpio12, S_IWUSR|S_IRUGO,
		tle62x0_gpio_show, tle62x0_gpio_store);
अटल DEVICE_ATTR(gpio13, S_IWUSR|S_IRUGO,
		tle62x0_gpio_show, tle62x0_gpio_store);
अटल DEVICE_ATTR(gpio14, S_IWUSR|S_IRUGO,
		tle62x0_gpio_show, tle62x0_gpio_store);
अटल DEVICE_ATTR(gpio15, S_IWUSR|S_IRUGO,
		tle62x0_gpio_show, tle62x0_gpio_store);
अटल DEVICE_ATTR(gpio16, S_IWUSR|S_IRUGO,
		tle62x0_gpio_show, tle62x0_gpio_store);

अटल काष्ठा device_attribute *gpio_attrs[] = अणु
	[0]		= &dev_attr_gpio1,
	[1]		= &dev_attr_gpio2,
	[2]		= &dev_attr_gpio3,
	[3]		= &dev_attr_gpio4,
	[4]		= &dev_attr_gpio5,
	[5]		= &dev_attr_gpio6,
	[6]		= &dev_attr_gpio7,
	[7]		= &dev_attr_gpio8,
	[8]		= &dev_attr_gpio9,
	[9]		= &dev_attr_gpio10,
	[10]		= &dev_attr_gpio11,
	[11]		= &dev_attr_gpio12,
	[12]		= &dev_attr_gpio13,
	[13]		= &dev_attr_gpio14,
	[14]		= &dev_attr_gpio15,
	[15]		= &dev_attr_gpio16
पूर्ण;

अटल पूर्णांक to_gpio_num(काष्ठा device_attribute *attr)
अणु
	पूर्णांक ptr;

	क्रम (ptr = 0; ptr < ARRAY_SIZE(gpio_attrs); ptr++) अणु
		अगर (gpio_attrs[ptr] == attr)
			वापस ptr;
	पूर्ण

	वापस -1;
पूर्ण

अटल पूर्णांक tle62x0_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा tle62x0_state *st;
	काष्ठा tle62x0_pdata *pdata;
	पूर्णांक ptr;
	पूर्णांक ret;

	pdata = dev_get_platdata(&spi->dev);
	अगर (pdata == शून्य) अणु
		dev_err(&spi->dev, "no device data specified\n");
		वापस -EINVAL;
	पूर्ण

	st = kzalloc(माप(काष्ठा tle62x0_state), GFP_KERNEL);
	अगर (st == शून्य)
		वापस -ENOMEM;

	st->us = spi;
	st->nr_gpio = pdata->gpio_count;
	st->gpio_state = pdata->init_state;

	mutex_init(&st->lock);

	ret = device_create_file(&spi->dev, &dev_attr_status_show);
	अगर (ret) अणु
		dev_err(&spi->dev, "cannot create status attribute\n");
		जाओ err_status;
	पूर्ण

	क्रम (ptr = 0; ptr < pdata->gpio_count; ptr++) अणु
		ret = device_create_file(&spi->dev, gpio_attrs[ptr]);
		अगर (ret) अणु
			dev_err(&spi->dev, "cannot create gpio attribute\n");
			जाओ err_gpios;
		पूर्ण
	पूर्ण

	/* tle62x0_ग_लिखो(st); */
	spi_set_drvdata(spi, st);
	वापस 0;

 err_gpios:
	जबतक (--ptr >= 0)
		device_हटाओ_file(&spi->dev, gpio_attrs[ptr]);

	device_हटाओ_file(&spi->dev, &dev_attr_status_show);

 err_status:
	kमुक्त(st);
	वापस ret;
पूर्ण

अटल पूर्णांक tle62x0_हटाओ(काष्ठा spi_device *spi)
अणु
	काष्ठा tle62x0_state *st = spi_get_drvdata(spi);
	पूर्णांक ptr;

	क्रम (ptr = 0; ptr < st->nr_gpio; ptr++)
		device_हटाओ_file(&spi->dev, gpio_attrs[ptr]);

	device_हटाओ_file(&spi->dev, &dev_attr_status_show);
	kमुक्त(st);
	वापस 0;
पूर्ण

अटल काष्ठा spi_driver tle62x0_driver = अणु
	.driver = अणु
		.name	= "tle62x0",
	पूर्ण,
	.probe		= tle62x0_probe,
	.हटाओ		= tle62x0_हटाओ,
पूर्ण;

module_spi_driver(tle62x0_driver);

MODULE_AUTHOR("Ben Dooks <ben@simtec.co.uk>");
MODULE_DESCRIPTION("TLE62x0 SPI driver");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("spi:tle62x0");
