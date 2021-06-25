<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Driver क्रम 93xx46 EEPROMs
 *
 * (C) 2011 DENX Software Engineering, Anम_से_दij Gustschin <agust@denx.de>
 */

#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_gpपन.स>
#समावेश <linux/slab.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/nvmem-provider.h>
#समावेश <linux/eeprom_93xx46.h>

#घोषणा OP_START	0x4
#घोषणा OP_WRITE	(OP_START | 0x1)
#घोषणा OP_READ		(OP_START | 0x2)
#घोषणा ADDR_EWDS	0x00
#घोषणा ADDR_ERAL	0x20
#घोषणा ADDR_EWEN	0x30

काष्ठा eeprom_93xx46_devtype_data अणु
	अचिन्हित पूर्णांक quirks;
पूर्ण;

अटल स्थिर काष्ठा eeprom_93xx46_devtype_data aपंचांगel_at93c46d_data = अणु
	.quirks = EEPROM_93XX46_QUIRK_SINGLE_WORD_READ |
		  EEPROM_93XX46_QUIRK_INSTRUCTION_LENGTH,
पूर्ण;

अटल स्थिर काष्ठा eeprom_93xx46_devtype_data microchip_93lc46b_data = अणु
	.quirks = EEPROM_93XX46_QUIRK_EXTRA_READ_CYCLE,
पूर्ण;

काष्ठा eeprom_93xx46_dev अणु
	काष्ठा spi_device *spi;
	काष्ठा eeprom_93xx46_platक्रमm_data *pdata;
	काष्ठा mutex lock;
	काष्ठा nvmem_config nvmem_config;
	काष्ठा nvmem_device *nvmem;
	पूर्णांक addrlen;
	पूर्णांक size;
पूर्ण;

अटल अंतरभूत bool has_quirk_single_word_पढ़ो(काष्ठा eeprom_93xx46_dev *edev)
अणु
	वापस edev->pdata->quirks & EEPROM_93XX46_QUIRK_SINGLE_WORD_READ;
पूर्ण

अटल अंतरभूत bool has_quirk_inकाष्ठाion_length(काष्ठा eeprom_93xx46_dev *edev)
अणु
	वापस edev->pdata->quirks & EEPROM_93XX46_QUIRK_INSTRUCTION_LENGTH;
पूर्ण

अटल अंतरभूत bool has_quirk_extra_पढ़ो_cycle(काष्ठा eeprom_93xx46_dev *edev)
अणु
	वापस edev->pdata->quirks & EEPROM_93XX46_QUIRK_EXTRA_READ_CYCLE;
पूर्ण

अटल पूर्णांक eeprom_93xx46_पढ़ो(व्योम *priv, अचिन्हित पूर्णांक off,
			      व्योम *val, माप_प्रकार count)
अणु
	काष्ठा eeprom_93xx46_dev *edev = priv;
	अक्षर *buf = val;
	पूर्णांक err = 0;

	अगर (unlikely(off >= edev->size))
		वापस 0;
	अगर ((off + count) > edev->size)
		count = edev->size - off;
	अगर (unlikely(!count))
		वापस count;

	mutex_lock(&edev->lock);

	अगर (edev->pdata->prepare)
		edev->pdata->prepare(edev);

	जबतक (count) अणु
		काष्ठा spi_message m;
		काष्ठा spi_transfer t[2] = अणु अणु 0 पूर्ण पूर्ण;
		u16 cmd_addr = OP_READ << edev->addrlen;
		माप_प्रकार nbytes = count;
		पूर्णांक bits;

		अगर (edev->addrlen == 7) अणु
			cmd_addr |= off & 0x7f;
			bits = 10;
			अगर (has_quirk_single_word_पढ़ो(edev))
				nbytes = 1;
		पूर्ण अन्यथा अणु
			cmd_addr |= (off >> 1) & 0x3f;
			bits = 9;
			अगर (has_quirk_single_word_पढ़ो(edev))
				nbytes = 2;
		पूर्ण

		dev_dbg(&edev->spi->dev, "read cmd 0x%x, %d Hz\n",
			cmd_addr, edev->spi->max_speed_hz);

		अगर (has_quirk_extra_पढ़ो_cycle(edev)) अणु
			cmd_addr <<= 1;
			bits += 1;
		पूर्ण

		spi_message_init(&m);

		t[0].tx_buf = (अक्षर *)&cmd_addr;
		t[0].len = 2;
		t[0].bits_per_word = bits;
		spi_message_add_tail(&t[0], &m);

		t[1].rx_buf = buf;
		t[1].len = count;
		t[1].bits_per_word = 8;
		spi_message_add_tail(&t[1], &m);

		err = spi_sync(edev->spi, &m);
		/* have to रुको at least Tcsl ns */
		ndelay(250);

		अगर (err) अणु
			dev_err(&edev->spi->dev, "read %zu bytes at %d: err. %d\n",
				nbytes, (पूर्णांक)off, err);
			अवरोध;
		पूर्ण

		buf += nbytes;
		off += nbytes;
		count -= nbytes;
	पूर्ण

	अगर (edev->pdata->finish)
		edev->pdata->finish(edev);

	mutex_unlock(&edev->lock);

	वापस err;
पूर्ण

अटल पूर्णांक eeprom_93xx46_ew(काष्ठा eeprom_93xx46_dev *edev, पूर्णांक is_on)
अणु
	काष्ठा spi_message m;
	काष्ठा spi_transfer t;
	पूर्णांक bits, ret;
	u16 cmd_addr;

	cmd_addr = OP_START << edev->addrlen;
	अगर (edev->addrlen == 7) अणु
		cmd_addr |= (is_on ? ADDR_EWEN : ADDR_EWDS) << 1;
		bits = 10;
	पूर्ण अन्यथा अणु
		cmd_addr |= (is_on ? ADDR_EWEN : ADDR_EWDS);
		bits = 9;
	पूर्ण

	अगर (has_quirk_inकाष्ठाion_length(edev)) अणु
		cmd_addr <<= 2;
		bits += 2;
	पूर्ण

	dev_dbg(&edev->spi->dev, "ew%s cmd 0x%04x, %d bits\n",
			is_on ? "en" : "ds", cmd_addr, bits);

	spi_message_init(&m);
	स_रखो(&t, 0, माप(t));

	t.tx_buf = &cmd_addr;
	t.len = 2;
	t.bits_per_word = bits;
	spi_message_add_tail(&t, &m);

	mutex_lock(&edev->lock);

	अगर (edev->pdata->prepare)
		edev->pdata->prepare(edev);

	ret = spi_sync(edev->spi, &m);
	/* have to रुको at least Tcsl ns */
	ndelay(250);
	अगर (ret)
		dev_err(&edev->spi->dev, "erase/write %sable error %d\n",
			is_on ? "en" : "dis", ret);

	अगर (edev->pdata->finish)
		edev->pdata->finish(edev);

	mutex_unlock(&edev->lock);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार
eeprom_93xx46_ग_लिखो_word(काष्ठा eeprom_93xx46_dev *edev,
			 स्थिर अक्षर *buf, अचिन्हित off)
अणु
	काष्ठा spi_message m;
	काष्ठा spi_transfer t[2];
	पूर्णांक bits, data_len, ret;
	u16 cmd_addr;

	cmd_addr = OP_WRITE << edev->addrlen;

	अगर (edev->addrlen == 7) अणु
		cmd_addr |= off & 0x7f;
		bits = 10;
		data_len = 1;
	पूर्ण अन्यथा अणु
		cmd_addr |= (off >> 1) & 0x3f;
		bits = 9;
		data_len = 2;
	पूर्ण

	dev_dbg(&edev->spi->dev, "write cmd 0x%x\n", cmd_addr);

	spi_message_init(&m);
	स_रखो(t, 0, माप(t));

	t[0].tx_buf = (अक्षर *)&cmd_addr;
	t[0].len = 2;
	t[0].bits_per_word = bits;
	spi_message_add_tail(&t[0], &m);

	t[1].tx_buf = buf;
	t[1].len = data_len;
	t[1].bits_per_word = 8;
	spi_message_add_tail(&t[1], &m);

	ret = spi_sync(edev->spi, &m);
	/* have to रुको program cycle समय Twc ms */
	mdelay(6);
	वापस ret;
पूर्ण

अटल पूर्णांक eeprom_93xx46_ग_लिखो(व्योम *priv, अचिन्हित पूर्णांक off,
				   व्योम *val, माप_प्रकार count)
अणु
	काष्ठा eeprom_93xx46_dev *edev = priv;
	अक्षर *buf = val;
	पूर्णांक i, ret, step = 1;

	अगर (unlikely(off >= edev->size))
		वापस -EFBIG;
	अगर ((off + count) > edev->size)
		count = edev->size - off;
	अगर (unlikely(!count))
		वापस count;

	/* only ग_लिखो even number of bytes on 16-bit devices */
	अगर (edev->addrlen == 6) अणु
		step = 2;
		count &= ~1;
	पूर्ण

	/* erase/ग_लिखो enable */
	ret = eeprom_93xx46_ew(edev, 1);
	अगर (ret)
		वापस ret;

	mutex_lock(&edev->lock);

	अगर (edev->pdata->prepare)
		edev->pdata->prepare(edev);

	क्रम (i = 0; i < count; i += step) अणु
		ret = eeprom_93xx46_ग_लिखो_word(edev, &buf[i], off + i);
		अगर (ret) अणु
			dev_err(&edev->spi->dev, "write failed at %d: %d\n",
				(पूर्णांक)off + i, ret);
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (edev->pdata->finish)
		edev->pdata->finish(edev);

	mutex_unlock(&edev->lock);

	/* erase/ग_लिखो disable */
	eeprom_93xx46_ew(edev, 0);
	वापस ret;
पूर्ण

अटल पूर्णांक eeprom_93xx46_eral(काष्ठा eeprom_93xx46_dev *edev)
अणु
	काष्ठा eeprom_93xx46_platक्रमm_data *pd = edev->pdata;
	काष्ठा spi_message m;
	काष्ठा spi_transfer t;
	पूर्णांक bits, ret;
	u16 cmd_addr;

	cmd_addr = OP_START << edev->addrlen;
	अगर (edev->addrlen == 7) अणु
		cmd_addr |= ADDR_ERAL << 1;
		bits = 10;
	पूर्ण अन्यथा अणु
		cmd_addr |= ADDR_ERAL;
		bits = 9;
	पूर्ण

	अगर (has_quirk_inकाष्ठाion_length(edev)) अणु
		cmd_addr <<= 2;
		bits += 2;
	पूर्ण

	dev_dbg(&edev->spi->dev, "eral cmd 0x%04x, %d bits\n", cmd_addr, bits);

	spi_message_init(&m);
	स_रखो(&t, 0, माप(t));

	t.tx_buf = &cmd_addr;
	t.len = 2;
	t.bits_per_word = bits;
	spi_message_add_tail(&t, &m);

	mutex_lock(&edev->lock);

	अगर (edev->pdata->prepare)
		edev->pdata->prepare(edev);

	ret = spi_sync(edev->spi, &m);
	अगर (ret)
		dev_err(&edev->spi->dev, "erase error %d\n", ret);
	/* have to रुको erase cycle समय Tec ms */
	mdelay(6);

	अगर (pd->finish)
		pd->finish(edev);

	mutex_unlock(&edev->lock);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार eeprom_93xx46_store_erase(काष्ठा device *dev,
					 काष्ठा device_attribute *attr,
					 स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा eeprom_93xx46_dev *edev = dev_get_drvdata(dev);
	पूर्णांक erase = 0, ret;

	माला_पूछो(buf, "%d", &erase);
	अगर (erase) अणु
		ret = eeprom_93xx46_ew(edev, 1);
		अगर (ret)
			वापस ret;
		ret = eeprom_93xx46_eral(edev);
		अगर (ret)
			वापस ret;
		ret = eeprom_93xx46_ew(edev, 0);
		अगर (ret)
			वापस ret;
	पूर्ण
	वापस count;
पूर्ण
अटल DEVICE_ATTR(erase, S_IWUSR, शून्य, eeprom_93xx46_store_erase);

अटल व्योम select_निश्चित(व्योम *context)
अणु
	काष्ठा eeprom_93xx46_dev *edev = context;

	gpiod_set_value_cansleep(edev->pdata->select, 1);
पूर्ण

अटल व्योम select_deनिश्चित(व्योम *context)
अणु
	काष्ठा eeprom_93xx46_dev *edev = context;

	gpiod_set_value_cansleep(edev->pdata->select, 0);
पूर्ण

अटल स्थिर काष्ठा of_device_id eeprom_93xx46_of_table[] = अणु
	अणु .compatible = "eeprom-93xx46", पूर्ण,
	अणु .compatible = "atmel,at93c46d", .data = &aपंचांगel_at93c46d_data, पूर्ण,
	अणु .compatible = "microchip,93lc46b", .data = &microchip_93lc46b_data, पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, eeprom_93xx46_of_table);

अटल पूर्णांक eeprom_93xx46_probe_dt(काष्ठा spi_device *spi)
अणु
	स्थिर काष्ठा of_device_id *of_id =
		of_match_device(eeprom_93xx46_of_table, &spi->dev);
	काष्ठा device_node *np = spi->dev.of_node;
	काष्ठा eeprom_93xx46_platक्रमm_data *pd;
	u32 पंचांगp;
	पूर्णांक ret;

	pd = devm_kzalloc(&spi->dev, माप(*pd), GFP_KERNEL);
	अगर (!pd)
		वापस -ENOMEM;

	ret = of_property_पढ़ो_u32(np, "data-size", &पंचांगp);
	अगर (ret < 0) अणु
		dev_err(&spi->dev, "data-size property not found\n");
		वापस ret;
	पूर्ण

	अगर (पंचांगp == 8) अणु
		pd->flags |= EE_ADDR8;
	पूर्ण अन्यथा अगर (पंचांगp == 16) अणु
		pd->flags |= EE_ADDR16;
	पूर्ण अन्यथा अणु
		dev_err(&spi->dev, "invalid data-size (%d)\n", पंचांगp);
		वापस -EINVAL;
	पूर्ण

	अगर (of_property_पढ़ो_bool(np, "read-only"))
		pd->flags |= EE_READONLY;

	pd->select = devm_gpiod_get_optional(&spi->dev, "select",
					     GPIOD_OUT_LOW);
	अगर (IS_ERR(pd->select))
		वापस PTR_ERR(pd->select);

	pd->prepare = select_निश्चित;
	pd->finish = select_deनिश्चित;
	gpiod_direction_output(pd->select, 0);

	अगर (of_id->data) अणु
		स्थिर काष्ठा eeprom_93xx46_devtype_data *data = of_id->data;

		pd->quirks = data->quirks;
	पूर्ण

	spi->dev.platक्रमm_data = pd;

	वापस 0;
पूर्ण

अटल पूर्णांक eeprom_93xx46_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा eeprom_93xx46_platक्रमm_data *pd;
	काष्ठा eeprom_93xx46_dev *edev;
	पूर्णांक err;

	अगर (spi->dev.of_node) अणु
		err = eeprom_93xx46_probe_dt(spi);
		अगर (err < 0)
			वापस err;
	पूर्ण

	pd = spi->dev.platक्रमm_data;
	अगर (!pd) अणु
		dev_err(&spi->dev, "missing platform data\n");
		वापस -ENODEV;
	पूर्ण

	edev = devm_kzalloc(&spi->dev, माप(*edev), GFP_KERNEL);
	अगर (!edev)
		वापस -ENOMEM;

	अगर (pd->flags & EE_ADDR8)
		edev->addrlen = 7;
	अन्यथा अगर (pd->flags & EE_ADDR16)
		edev->addrlen = 6;
	अन्यथा अणु
		dev_err(&spi->dev, "unspecified address type\n");
		वापस -EINVAL;
	पूर्ण

	mutex_init(&edev->lock);

	edev->spi = spi;
	edev->pdata = pd;

	edev->size = 128;
	edev->nvmem_config.type = NVMEM_TYPE_EEPROM;
	edev->nvmem_config.name = dev_name(&spi->dev);
	edev->nvmem_config.dev = &spi->dev;
	edev->nvmem_config.पढ़ो_only = pd->flags & EE_READONLY;
	edev->nvmem_config.root_only = true;
	edev->nvmem_config.owner = THIS_MODULE;
	edev->nvmem_config.compat = true;
	edev->nvmem_config.base_dev = &spi->dev;
	edev->nvmem_config.reg_पढ़ो = eeprom_93xx46_पढ़ो;
	edev->nvmem_config.reg_ग_लिखो = eeprom_93xx46_ग_लिखो;
	edev->nvmem_config.priv = edev;
	edev->nvmem_config.stride = 4;
	edev->nvmem_config.word_size = 1;
	edev->nvmem_config.size = edev->size;

	edev->nvmem = devm_nvmem_रेजिस्टर(&spi->dev, &edev->nvmem_config);
	अगर (IS_ERR(edev->nvmem))
		वापस PTR_ERR(edev->nvmem);

	dev_info(&spi->dev, "%d-bit eeprom %s\n",
		(pd->flags & EE_ADDR8) ? 8 : 16,
		(pd->flags & EE_READONLY) ? "(readonly)" : "");

	अगर (!(pd->flags & EE_READONLY)) अणु
		अगर (device_create_file(&spi->dev, &dev_attr_erase))
			dev_err(&spi->dev, "can't create erase interface\n");
	पूर्ण

	spi_set_drvdata(spi, edev);
	वापस 0;
पूर्ण

अटल पूर्णांक eeprom_93xx46_हटाओ(काष्ठा spi_device *spi)
अणु
	काष्ठा eeprom_93xx46_dev *edev = spi_get_drvdata(spi);

	अगर (!(edev->pdata->flags & EE_READONLY))
		device_हटाओ_file(&spi->dev, &dev_attr_erase);

	वापस 0;
पूर्ण

अटल काष्ठा spi_driver eeprom_93xx46_driver = अणु
	.driver = अणु
		.name	= "93xx46",
		.of_match_table = of_match_ptr(eeprom_93xx46_of_table),
	पूर्ण,
	.probe		= eeprom_93xx46_probe,
	.हटाओ		= eeprom_93xx46_हटाओ,
पूर्ण;

module_spi_driver(eeprom_93xx46_driver);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Driver for 93xx46 EEPROMs");
MODULE_AUTHOR("Anatolij Gustschin <agust@denx.de>");
MODULE_ALIAS("spi:93xx46");
MODULE_ALIAS("spi:eeprom-93xx46");
MODULE_ALIAS("spi:93lc46b");
