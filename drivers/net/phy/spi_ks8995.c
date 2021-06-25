<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * SPI driver क्रम Micrel/Kendin KS8995M and KSZ8864RMN ethernet चयनes
 *
 * Copyright (C) 2008 Gabor Juhos <juhosg at खोलोwrt.org>
 *
 * This file was based on: drivers/spi/at25.c
 *     Copyright (C) 2006 David Brownell
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/of.h>
#समावेश <linux/of_gpपन.स>

#समावेश <linux/spi/spi.h>

#घोषणा DRV_VERSION		"0.1.1"
#घोषणा DRV_DESC		"Micrel KS8995 Ethernet switch SPI driver"

/* ------------------------------------------------------------------------ */

#घोषणा KS8995_REG_ID0		0x00    /* Chip ID0 */
#घोषणा KS8995_REG_ID1		0x01    /* Chip ID1 */

#घोषणा KS8995_REG_GC0		0x02    /* Global Control 0 */
#घोषणा KS8995_REG_GC1		0x03    /* Global Control 1 */
#घोषणा KS8995_REG_GC2		0x04    /* Global Control 2 */
#घोषणा KS8995_REG_GC3		0x05    /* Global Control 3 */
#घोषणा KS8995_REG_GC4		0x06    /* Global Control 4 */
#घोषणा KS8995_REG_GC5		0x07    /* Global Control 5 */
#घोषणा KS8995_REG_GC6		0x08    /* Global Control 6 */
#घोषणा KS8995_REG_GC7		0x09    /* Global Control 7 */
#घोषणा KS8995_REG_GC8		0x0a    /* Global Control 8 */
#घोषणा KS8995_REG_GC9		0x0b    /* Global Control 9 */

#घोषणा KS8995_REG_PC(p, r)	((0x10 * p) + r)	 /* Port Control */
#घोषणा KS8995_REG_PS(p, r)	((0x10 * p) + r + 0xe)  /* Port Status */

#घोषणा KS8995_REG_TPC0		0x60    /* TOS Priority Control 0 */
#घोषणा KS8995_REG_TPC1		0x61    /* TOS Priority Control 1 */
#घोषणा KS8995_REG_TPC2		0x62    /* TOS Priority Control 2 */
#घोषणा KS8995_REG_TPC3		0x63    /* TOS Priority Control 3 */
#घोषणा KS8995_REG_TPC4		0x64    /* TOS Priority Control 4 */
#घोषणा KS8995_REG_TPC5		0x65    /* TOS Priority Control 5 */
#घोषणा KS8995_REG_TPC6		0x66    /* TOS Priority Control 6 */
#घोषणा KS8995_REG_TPC7		0x67    /* TOS Priority Control 7 */

#घोषणा KS8995_REG_MAC0		0x68    /* MAC address 0 */
#घोषणा KS8995_REG_MAC1		0x69    /* MAC address 1 */
#घोषणा KS8995_REG_MAC2		0x6a    /* MAC address 2 */
#घोषणा KS8995_REG_MAC3		0x6b    /* MAC address 3 */
#घोषणा KS8995_REG_MAC4		0x6c    /* MAC address 4 */
#घोषणा KS8995_REG_MAC5		0x6d    /* MAC address 5 */

#घोषणा KS8995_REG_IAC0		0x6e    /* Indirect Access Control 0 */
#घोषणा KS8995_REG_IAC1		0x6f    /* Indirect Access Control 0 */
#घोषणा KS8995_REG_IAD7		0x70    /* Indirect Access Data 7 */
#घोषणा KS8995_REG_IAD6		0x71    /* Indirect Access Data 6 */
#घोषणा KS8995_REG_IAD5		0x72    /* Indirect Access Data 5 */
#घोषणा KS8995_REG_IAD4		0x73    /* Indirect Access Data 4 */
#घोषणा KS8995_REG_IAD3		0x74    /* Indirect Access Data 3 */
#घोषणा KS8995_REG_IAD2		0x75    /* Indirect Access Data 2 */
#घोषणा KS8995_REG_IAD1		0x76    /* Indirect Access Data 1 */
#घोषणा KS8995_REG_IAD0		0x77    /* Indirect Access Data 0 */

#घोषणा KSZ8864_REG_ID1		0xfe	/* Chip ID in bit 7 */

#घोषणा KS8995_REGS_SIZE	0x80
#घोषणा KSZ8864_REGS_SIZE	0x100
#घोषणा KSZ8795_REGS_SIZE	0x100

#घोषणा ID1_CHIPID_M		0xf
#घोषणा ID1_CHIPID_S		4
#घोषणा ID1_REVISION_M		0x7
#घोषणा ID1_REVISION_S		1
#घोषणा ID1_START_SW		1	/* start the चयन */

#घोषणा FAMILY_KS8995		0x95
#घोषणा FAMILY_KSZ8795		0x87
#घोषणा CHIPID_M		0
#घोषणा KS8995_CHIP_ID		0x00
#घोषणा KSZ8864_CHIP_ID		0x01
#घोषणा KSZ8795_CHIP_ID		0x09

#घोषणा KS8995_CMD_WRITE	0x02U
#घोषणा KS8995_CMD_READ		0x03U

#घोषणा KS8995_RESET_DELAY	10 /* usec */

क्रमागत ks8995_chip_variant अणु
	ks8995,
	ksz8864,
	ksz8795,
	max_variant
पूर्ण;

काष्ठा ks8995_chip_params अणु
	अक्षर *name;
	पूर्णांक family_id;
	पूर्णांक chip_id;
	पूर्णांक regs_size;
	पूर्णांक addr_width;
	पूर्णांक addr_shअगरt;
पूर्ण;

अटल स्थिर काष्ठा ks8995_chip_params ks8995_chip[] = अणु
	[ks8995] = अणु
		.name = "KS8995MA",
		.family_id = FAMILY_KS8995,
		.chip_id = KS8995_CHIP_ID,
		.regs_size = KS8995_REGS_SIZE,
		.addr_width = 8,
		.addr_shअगरt = 0,
	पूर्ण,
	[ksz8864] = अणु
		.name = "KSZ8864RMN",
		.family_id = FAMILY_KS8995,
		.chip_id = KSZ8864_CHIP_ID,
		.regs_size = KSZ8864_REGS_SIZE,
		.addr_width = 8,
		.addr_shअगरt = 0,
	पूर्ण,
	[ksz8795] = अणु
		.name = "KSZ8795CLX",
		.family_id = FAMILY_KSZ8795,
		.chip_id = KSZ8795_CHIP_ID,
		.regs_size = KSZ8795_REGS_SIZE,
		.addr_width = 12,
		.addr_shअगरt = 1,
	पूर्ण,
पूर्ण;

काष्ठा ks8995_pdata अणु
	पूर्णांक reset_gpio;
	क्रमागत of_gpio_flags reset_gpio_flags;
पूर्ण;

काष्ठा ks8995_चयन अणु
	काष्ठा spi_device	*spi;
	काष्ठा mutex		lock;
	काष्ठा ks8995_pdata	*pdata;
	काष्ठा bin_attribute	regs_attr;
	स्थिर काष्ठा ks8995_chip_params	*chip;
	पूर्णांक			revision_id;
पूर्ण;

अटल स्थिर काष्ठा spi_device_id ks8995_id[] = अणु
	अणु"ks8995", ks8995पूर्ण,
	अणु"ksz8864", ksz8864पूर्ण,
	अणु"ksz8795", ksz8795पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(spi, ks8995_id);

अटल स्थिर काष्ठा of_device_id ks8895_spi_of_match[] = अणु
        अणु .compatible = "micrel,ks8995" पूर्ण,
        अणु .compatible = "micrel,ksz8864" पूर्ण,
        अणु .compatible = "micrel,ksz8795" पूर्ण,
        अणु पूर्ण,
 पूर्ण;
MODULE_DEVICE_TABLE(of, ks8895_spi_of_match);

अटल अंतरभूत u8 get_chip_id(u8 val)
अणु
	वापस (val >> ID1_CHIPID_S) & ID1_CHIPID_M;
पूर्ण

अटल अंतरभूत u8 get_chip_rev(u8 val)
अणु
	वापस (val >> ID1_REVISION_S) & ID1_REVISION_M;
पूर्ण

/* create_spi_cmd - create a chip specअगरic SPI command header
 * @ks: poपूर्णांकer to चयन instance
 * @cmd: SPI command क्रम चयन
 * @address: रेजिस्टर address क्रम command
 *
 * Dअगरferent chip families use dअगरferent bit pattern to address the चयनes
 * रेजिस्टरs:
 *
 * KS8995: 8bit command + 8bit address
 * KSZ8795: 3bit command + 12bit address + 1bit TR (?)
 */
अटल अंतरभूत __be16 create_spi_cmd(काष्ठा ks8995_चयन *ks, पूर्णांक cmd,
				    अचिन्हित address)
अणु
	u16 result = cmd;

	/* make room क्रम address (incl. address shअगरt) */
	result <<= ks->chip->addr_width + ks->chip->addr_shअगरt;
	/* add address */
	result |= address << ks->chip->addr_shअगरt;
	/* SPI protocol needs big endian */
	वापस cpu_to_be16(result);
पूर्ण
/* ------------------------------------------------------------------------ */
अटल पूर्णांक ks8995_पढ़ो(काष्ठा ks8995_चयन *ks, अक्षर *buf,
		 अचिन्हित offset, माप_प्रकार count)
अणु
	__be16 cmd;
	काष्ठा spi_transfer t[2];
	काष्ठा spi_message m;
	पूर्णांक err;

	cmd = create_spi_cmd(ks, KS8995_CMD_READ, offset);
	spi_message_init(&m);

	स_रखो(&t, 0, माप(t));

	t[0].tx_buf = &cmd;
	t[0].len = माप(cmd);
	spi_message_add_tail(&t[0], &m);

	t[1].rx_buf = buf;
	t[1].len = count;
	spi_message_add_tail(&t[1], &m);

	mutex_lock(&ks->lock);
	err = spi_sync(ks->spi, &m);
	mutex_unlock(&ks->lock);

	वापस err ? err : count;
पूर्ण

अटल पूर्णांक ks8995_ग_लिखो(काष्ठा ks8995_चयन *ks, अक्षर *buf,
		 अचिन्हित offset, माप_प्रकार count)
अणु
	__be16 cmd;
	काष्ठा spi_transfer t[2];
	काष्ठा spi_message m;
	पूर्णांक err;

	cmd = create_spi_cmd(ks, KS8995_CMD_WRITE, offset);
	spi_message_init(&m);

	स_रखो(&t, 0, माप(t));

	t[0].tx_buf = &cmd;
	t[0].len = माप(cmd);
	spi_message_add_tail(&t[0], &m);

	t[1].tx_buf = buf;
	t[1].len = count;
	spi_message_add_tail(&t[1], &m);

	mutex_lock(&ks->lock);
	err = spi_sync(ks->spi, &m);
	mutex_unlock(&ks->lock);

	वापस err ? err : count;
पूर्ण

अटल अंतरभूत पूर्णांक ks8995_पढ़ो_reg(काष्ठा ks8995_चयन *ks, u8 addr, u8 *buf)
अणु
	वापस ks8995_पढ़ो(ks, buf, addr, 1) != 1;
पूर्ण

अटल अंतरभूत पूर्णांक ks8995_ग_लिखो_reg(काष्ठा ks8995_चयन *ks, u8 addr, u8 val)
अणु
	अक्षर buf = val;

	वापस ks8995_ग_लिखो(ks, &buf, addr, 1) != 1;
पूर्ण

/* ------------------------------------------------------------------------ */

अटल पूर्णांक ks8995_stop(काष्ठा ks8995_चयन *ks)
अणु
	वापस ks8995_ग_लिखो_reg(ks, KS8995_REG_ID1, 0);
पूर्ण

अटल पूर्णांक ks8995_start(काष्ठा ks8995_चयन *ks)
अणु
	वापस ks8995_ग_लिखो_reg(ks, KS8995_REG_ID1, 1);
पूर्ण

अटल पूर्णांक ks8995_reset(काष्ठा ks8995_चयन *ks)
अणु
	पूर्णांक err;

	err = ks8995_stop(ks);
	अगर (err)
		वापस err;

	udelay(KS8995_RESET_DELAY);

	वापस ks8995_start(ks);
पूर्ण

अटल sमाप_प्रकार ks8995_रेजिस्टरs_पढ़ो(काष्ठा file *filp, काष्ठा kobject *kobj,
	काष्ठा bin_attribute *bin_attr, अक्षर *buf, loff_t off, माप_प्रकार count)
अणु
	काष्ठा device *dev;
	काष्ठा ks8995_चयन *ks8995;

	dev = kobj_to_dev(kobj);
	ks8995 = dev_get_drvdata(dev);

	वापस ks8995_पढ़ो(ks8995, buf, off, count);
पूर्ण

अटल sमाप_प्रकार ks8995_रेजिस्टरs_ग_लिखो(काष्ठा file *filp, काष्ठा kobject *kobj,
	काष्ठा bin_attribute *bin_attr, अक्षर *buf, loff_t off, माप_प्रकार count)
अणु
	काष्ठा device *dev;
	काष्ठा ks8995_चयन *ks8995;

	dev = kobj_to_dev(kobj);
	ks8995 = dev_get_drvdata(dev);

	वापस ks8995_ग_लिखो(ks8995, buf, off, count);
पूर्ण

/* ks8995_get_revision - get chip revision
 * @ks: poपूर्णांकer to चयन instance
 *
 * Verअगरy chip family and id and get chip revision.
 */
अटल पूर्णांक ks8995_get_revision(काष्ठा ks8995_चयन *ks)
अणु
	पूर्णांक err;
	u8 id0, id1, ksz8864_id;

	/* पढ़ो family id */
	err = ks8995_पढ़ो_reg(ks, KS8995_REG_ID0, &id0);
	अगर (err) अणु
		err = -EIO;
		जाओ err_out;
	पूर्ण

	/* verअगरy family id */
	अगर (id0 != ks->chip->family_id) अणु
		dev_err(&ks->spi->dev, "chip family id mismatch: expected 0x%02x but 0x%02x read\n",
			ks->chip->family_id, id0);
		err = -ENODEV;
		जाओ err_out;
	पूर्ण

	चयन (ks->chip->family_id) अणु
	हाल FAMILY_KS8995:
		/* try पढ़ोing chip id at CHIP ID1 */
		err = ks8995_पढ़ो_reg(ks, KS8995_REG_ID1, &id1);
		अगर (err) अणु
			err = -EIO;
			जाओ err_out;
		पूर्ण

		/* verअगरy chip id */
		अगर ((get_chip_id(id1) == CHIPID_M) &&
		    (get_chip_id(id1) == ks->chip->chip_id)) अणु
			/* KS8995MA */
			ks->revision_id = get_chip_rev(id1);
		पूर्ण अन्यथा अगर (get_chip_id(id1) != CHIPID_M) अणु
			/* KSZ8864RMN */
			err = ks8995_पढ़ो_reg(ks, KS8995_REG_ID1, &ksz8864_id);
			अगर (err) अणु
				err = -EIO;
				जाओ err_out;
			पूर्ण

			अगर ((ksz8864_id & 0x80) &&
			    (ks->chip->chip_id == KSZ8864_CHIP_ID)) अणु
				ks->revision_id = get_chip_rev(id1);
			पूर्ण

		पूर्ण अन्यथा अणु
			dev_err(&ks->spi->dev, "unsupported chip id for KS8995 family: 0x%02x\n",
				id1);
			err = -ENODEV;
		पूर्ण
		अवरोध;
	हाल FAMILY_KSZ8795:
		/* try पढ़ोing chip id at CHIP ID1 */
		err = ks8995_पढ़ो_reg(ks, KS8995_REG_ID1, &id1);
		अगर (err) अणु
			err = -EIO;
			जाओ err_out;
		पूर्ण

		अगर (get_chip_id(id1) == ks->chip->chip_id) अणु
			ks->revision_id = get_chip_rev(id1);
		पूर्ण अन्यथा अणु
			dev_err(&ks->spi->dev, "unsupported chip id for KSZ8795 family: 0x%02x\n",
				id1);
			err = -ENODEV;
		पूर्ण
		अवरोध;
	शेष:
		dev_err(&ks->spi->dev, "unsupported family id: 0x%02x\n", id0);
		err = -ENODEV;
		अवरोध;
	पूर्ण
err_out:
	वापस err;
पूर्ण

/* ks8995_parse_dt - setup platक्रमm data from devicetree
 * @ks: poपूर्णांकer to चयन instance
 *
 * Parses supported DT properties and sets up platक्रमm data
 * accordingly.
 */
अटल व्योम ks8995_parse_dt(काष्ठा ks8995_चयन *ks)
अणु
	काष्ठा device_node *np = ks->spi->dev.of_node;
	काष्ठा ks8995_pdata *pdata = ks->pdata;

	अगर (!np)
		वापस;

	pdata->reset_gpio = of_get_named_gpio_flags(np, "reset-gpios", 0,
		&pdata->reset_gpio_flags);
पूर्ण

अटल स्थिर काष्ठा bin_attribute ks8995_रेजिस्टरs_attr = अणु
	.attr = अणु
		.name   = "registers",
		.mode   = 0600,
	पूर्ण,
	.size   = KS8995_REGS_SIZE,
	.पढ़ो   = ks8995_रेजिस्टरs_पढ़ो,
	.ग_लिखो  = ks8995_रेजिस्टरs_ग_लिखो,
पूर्ण;

/* ------------------------------------------------------------------------ */
अटल पूर्णांक ks8995_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा ks8995_चयन *ks;
	पूर्णांक err;
	पूर्णांक variant = spi_get_device_id(spi)->driver_data;

	अगर (variant >= max_variant) अणु
		dev_err(&spi->dev, "bad chip variant %d\n", variant);
		वापस -ENODEV;
	पूर्ण

	ks = devm_kzalloc(&spi->dev, माप(*ks), GFP_KERNEL);
	अगर (!ks)
		वापस -ENOMEM;

	mutex_init(&ks->lock);
	ks->spi = spi;
	ks->chip = &ks8995_chip[variant];

	अगर (ks->spi->dev.of_node) अणु
		ks->pdata = devm_kzalloc(&spi->dev, माप(*ks->pdata),
					 GFP_KERNEL);
		अगर (!ks->pdata)
			वापस -ENOMEM;

		ks->pdata->reset_gpio = -1;

		ks8995_parse_dt(ks);
	पूर्ण

	अगर (!ks->pdata)
		ks->pdata = spi->dev.platक्रमm_data;

	/* de-निश्चित चयन reset */
	अगर (ks->pdata && gpio_is_valid(ks->pdata->reset_gpio)) अणु
		अचिन्हित दीर्घ flags;

		flags = (ks->pdata->reset_gpio_flags == OF_GPIO_ACTIVE_LOW ?
			 GPIOF_ACTIVE_LOW : 0);

		err = devm_gpio_request_one(&spi->dev,
					    ks->pdata->reset_gpio,
					    flags, "switch-reset");
		अगर (err) अणु
			dev_err(&spi->dev,
				"failed to get reset-gpios: %d\n", err);
			वापस -EIO;
		पूर्ण

		gpiod_set_value(gpio_to_desc(ks->pdata->reset_gpio), 0);
	पूर्ण

	spi_set_drvdata(spi, ks);

	spi->mode = SPI_MODE_0;
	spi->bits_per_word = 8;
	err = spi_setup(spi);
	अगर (err) अणु
		dev_err(&spi->dev, "spi_setup failed, err=%d\n", err);
		वापस err;
	पूर्ण

	err = ks8995_get_revision(ks);
	अगर (err)
		वापस err;

	स_नकल(&ks->regs_attr, &ks8995_रेजिस्टरs_attr, माप(ks->regs_attr));
	ks->regs_attr.size = ks->chip->regs_size;

	err = ks8995_reset(ks);
	अगर (err)
		वापस err;

	sysfs_attr_init(&ks->regs_attr.attr);
	err = sysfs_create_bin_file(&spi->dev.kobj, &ks->regs_attr);
	अगर (err) अणु
		dev_err(&spi->dev, "unable to create sysfs file, err=%d\n",
				    err);
		वापस err;
	पूर्ण

	dev_info(&spi->dev, "%s device found, Chip ID:%x, Revision:%x\n",
		 ks->chip->name, ks->chip->chip_id, ks->revision_id);

	वापस 0;
पूर्ण

अटल पूर्णांक ks8995_हटाओ(काष्ठा spi_device *spi)
अणु
	काष्ठा ks8995_चयन *ks = spi_get_drvdata(spi);

	sysfs_हटाओ_bin_file(&spi->dev.kobj, &ks->regs_attr);

	/* निश्चित reset */
	अगर (ks->pdata && gpio_is_valid(ks->pdata->reset_gpio))
		gpiod_set_value(gpio_to_desc(ks->pdata->reset_gpio), 1);

	वापस 0;
पूर्ण

/* ------------------------------------------------------------------------ */
अटल काष्ठा spi_driver ks8995_driver = अणु
	.driver = अणु
		.name	    = "spi-ks8995",
		.of_match_table = of_match_ptr(ks8895_spi_of_match),
	पूर्ण,
	.probe	  = ks8995_probe,
	.हटाओ	  = ks8995_हटाओ,
	.id_table = ks8995_id,
पूर्ण;

module_spi_driver(ks8995_driver);

MODULE_DESCRIPTION(DRV_DESC);
MODULE_VERSION(DRV_VERSION);
MODULE_AUTHOR("Gabor Juhos <juhosg at openwrt.org>");
MODULE_LICENSE("GPL v2");
