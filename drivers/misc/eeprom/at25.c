<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * at25.c -- support most SPI EEPROMs, such as Aपंचांगel AT25 models
 *
 * Copyright (C) 2006 David Brownell
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/sched.h>

#समावेश <linux/nvmem-provider.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/spi/eeprom.h>
#समावेश <linux/property.h>

/*
 * NOTE: this is an *EEPROM* driver.  The vagaries of product naming
 * mean that some AT25 products are EEPROMs, and others are FLASH.
 * Handle FLASH chips with the drivers/mtd/devices/m25p80.c driver,
 * not this one!
 *
 * EEPROMs that can be used with this driver include, क्रम example:
 *   AT25M02, AT25128B
 */

काष्ठा at25_data अणु
	काष्ठा spi_device	*spi;
	काष्ठा mutex		lock;
	काष्ठा spi_eeprom	chip;
	अचिन्हित		addrlen;
	काष्ठा nvmem_config	nvmem_config;
	काष्ठा nvmem_device	*nvmem;
पूर्ण;

#घोषणा	AT25_WREN	0x06		/* latch the ग_लिखो enable */
#घोषणा	AT25_WRDI	0x04		/* reset the ग_लिखो enable */
#घोषणा	AT25_RDSR	0x05		/* पढ़ो status रेजिस्टर */
#घोषणा	AT25_WRSR	0x01		/* ग_लिखो status रेजिस्टर */
#घोषणा	AT25_READ	0x03		/* पढ़ो byte(s) */
#घोषणा	AT25_WRITE	0x02		/* ग_लिखो byte(s)/sector */

#घोषणा	AT25_SR_nRDY	0x01		/* nRDY = ग_लिखो-in-progress */
#घोषणा	AT25_SR_WEN	0x02		/* ग_लिखो enable (latched) */
#घोषणा	AT25_SR_BP0	0x04		/* BP क्रम software ग_लिखोprotect */
#घोषणा	AT25_SR_BP1	0x08
#घोषणा	AT25_SR_WPEN	0x80		/* ग_लिखोprotect enable */

#घोषणा	AT25_INSTR_BIT3	0x08		/* Additional address bit in instr */

#घोषणा EE_MAXADDRLEN	3		/* 24 bit addresses, up to 2 MBytes */

/* Specs often allow 5 msec क्रम a page ग_लिखो, someबार 20 msec;
 * it's important to recover from ग_लिखो समयouts.
 */
#घोषणा	EE_TIMEOUT	25

/*-------------------------------------------------------------------------*/

#घोषणा	io_limit	PAGE_SIZE	/* bytes */

अटल पूर्णांक at25_ee_पढ़ो(व्योम *priv, अचिन्हित पूर्णांक offset,
			व्योम *val, माप_प्रकार count)
अणु
	काष्ठा at25_data *at25 = priv;
	अक्षर *buf = val;
	u8			command[EE_MAXADDRLEN + 1];
	u8			*cp;
	sमाप_प्रकार			status;
	काष्ठा spi_transfer	t[2];
	काष्ठा spi_message	m;
	u8			instr;

	अगर (unlikely(offset >= at25->chip.byte_len))
		वापस -EINVAL;
	अगर ((offset + count) > at25->chip.byte_len)
		count = at25->chip.byte_len - offset;
	अगर (unlikely(!count))
		वापस -EINVAL;

	cp = command;

	instr = AT25_READ;
	अगर (at25->chip.flags & EE_INSTR_BIT3_IS_ADDR)
		अगर (offset >= (1U << (at25->addrlen * 8)))
			instr |= AT25_INSTR_BIT3;
	*cp++ = instr;

	/* 8/16/24-bit address is written MSB first */
	चयन (at25->addrlen) अणु
	शेष:	/* हाल 3 */
		*cp++ = offset >> 16;
		fallthrough;
	हाल 2:
		*cp++ = offset >> 8;
		fallthrough;
	हाल 1:
	हाल 0:	/* can't happen: क्रम better codegen */
		*cp++ = offset >> 0;
	पूर्ण

	spi_message_init(&m);
	स_रखो(t, 0, माप(t));

	t[0].tx_buf = command;
	t[0].len = at25->addrlen + 1;
	spi_message_add_tail(&t[0], &m);

	t[1].rx_buf = buf;
	t[1].len = count;
	spi_message_add_tail(&t[1], &m);

	mutex_lock(&at25->lock);

	/* Read it all at once.
	 *
	 * REVISIT that's potentially a problem with large chips, अगर
	 * other devices on the bus need to be accessed regularly or
	 * this chip is घड़ीed very slowly
	 */
	status = spi_sync(at25->spi, &m);
	dev_dbg(&at25->spi->dev, "read %zu bytes at %d --> %zd\n",
		count, offset, status);

	mutex_unlock(&at25->lock);
	वापस status;
पूर्ण

अटल पूर्णांक at25_ee_ग_लिखो(व्योम *priv, अचिन्हित पूर्णांक off, व्योम *val, माप_प्रकार count)
अणु
	काष्ठा at25_data *at25 = priv;
	स्थिर अक्षर *buf = val;
	पूर्णांक			status = 0;
	अचिन्हित		buf_size;
	u8			*bounce;

	अगर (unlikely(off >= at25->chip.byte_len))
		वापस -EFBIG;
	अगर ((off + count) > at25->chip.byte_len)
		count = at25->chip.byte_len - off;
	अगर (unlikely(!count))
		वापस -EINVAL;

	/* Temp buffer starts with command and address */
	buf_size = at25->chip.page_size;
	अगर (buf_size > io_limit)
		buf_size = io_limit;
	bounce = kदो_स्मृति(buf_size + at25->addrlen + 1, GFP_KERNEL);
	अगर (!bounce)
		वापस -ENOMEM;

	/* For ग_लिखो, rollover is within the page ... so we ग_लिखो at
	 * most one page, then manually roll over to the next page.
	 */
	mutex_lock(&at25->lock);
	करो अणु
		अचिन्हित दीर्घ	समयout, retries;
		अचिन्हित	segment;
		अचिन्हित	offset = (अचिन्हित) off;
		u8		*cp = bounce;
		पूर्णांक		sr;
		u8		instr;

		*cp = AT25_WREN;
		status = spi_ग_लिखो(at25->spi, cp, 1);
		अगर (status < 0) अणु
			dev_dbg(&at25->spi->dev, "WREN --> %d\n", status);
			अवरोध;
		पूर्ण

		instr = AT25_WRITE;
		अगर (at25->chip.flags & EE_INSTR_BIT3_IS_ADDR)
			अगर (offset >= (1U << (at25->addrlen * 8)))
				instr |= AT25_INSTR_BIT3;
		*cp++ = instr;

		/* 8/16/24-bit address is written MSB first */
		चयन (at25->addrlen) अणु
		शेष:	/* हाल 3 */
			*cp++ = offset >> 16;
			fallthrough;
		हाल 2:
			*cp++ = offset >> 8;
			fallthrough;
		हाल 1:
		हाल 0:	/* can't happen: क्रम better codegen */
			*cp++ = offset >> 0;
		पूर्ण

		/* Write as much of a page as we can */
		segment = buf_size - (offset % buf_size);
		अगर (segment > count)
			segment = count;
		स_नकल(cp, buf, segment);
		status = spi_ग_लिखो(at25->spi, bounce,
				segment + at25->addrlen + 1);
		dev_dbg(&at25->spi->dev, "write %u bytes at %u --> %d\n",
			segment, offset, status);
		अगर (status < 0)
			अवरोध;

		/* REVISIT this should detect (or prevent) failed ग_लिखोs
		 * to पढ़ोonly sections of the EEPROM...
		 */

		/* Wait क्रम non-busy status */
		समयout = jअगरfies + msecs_to_jअगरfies(EE_TIMEOUT);
		retries = 0;
		करो अणु

			sr = spi_w8r8(at25->spi, AT25_RDSR);
			अगर (sr < 0 || (sr & AT25_SR_nRDY)) अणु
				dev_dbg(&at25->spi->dev,
					"rdsr --> %d (%02x)\n", sr, sr);
				/* at HZ=100, this is sloooow */
				msleep(1);
				जारी;
			पूर्ण
			अगर (!(sr & AT25_SR_nRDY))
				अवरोध;
		पूर्ण जबतक (retries++ < 3 || समय_beक्रमe_eq(jअगरfies, समयout));

		अगर ((sr < 0) || (sr & AT25_SR_nRDY)) अणु
			dev_err(&at25->spi->dev,
				"write %u bytes offset %u, timeout after %u msecs\n",
				segment, offset,
				jअगरfies_to_msecs(jअगरfies -
					(समयout - EE_TIMEOUT)));
			status = -ETIMEDOUT;
			अवरोध;
		पूर्ण

		off += segment;
		buf += segment;
		count -= segment;

	पूर्ण जबतक (count > 0);

	mutex_unlock(&at25->lock);

	kमुक्त(bounce);
	वापस status;
पूर्ण

/*-------------------------------------------------------------------------*/

अटल पूर्णांक at25_fw_to_chip(काष्ठा device *dev, काष्ठा spi_eeprom *chip)
अणु
	u32 val;

	स_रखो(chip, 0, माप(*chip));
	म_नकलन(chip->name, "at25", माप(chip->name));

	अगर (device_property_पढ़ो_u32(dev, "size", &val) == 0 ||
	    device_property_पढ़ो_u32(dev, "at25,byte-len", &val) == 0) अणु
		chip->byte_len = val;
	पूर्ण अन्यथा अणु
		dev_err(dev, "Error: missing \"size\" property\n");
		वापस -ENODEV;
	पूर्ण

	अगर (device_property_पढ़ो_u32(dev, "pagesize", &val) == 0 ||
	    device_property_पढ़ो_u32(dev, "at25,page-size", &val) == 0) अणु
		chip->page_size = val;
	पूर्ण अन्यथा अणु
		dev_err(dev, "Error: missing \"pagesize\" property\n");
		वापस -ENODEV;
	पूर्ण

	अगर (device_property_पढ़ो_u32(dev, "at25,addr-mode", &val) == 0) अणु
		chip->flags = (u16)val;
	पूर्ण अन्यथा अणु
		अगर (device_property_पढ़ो_u32(dev, "address-width", &val)) अणु
			dev_err(dev,
				"Error: missing \"address-width\" property\n");
			वापस -ENODEV;
		पूर्ण
		चयन (val) अणु
		हाल 9:
			chip->flags |= EE_INSTR_BIT3_IS_ADDR;
			fallthrough;
		हाल 8:
			chip->flags |= EE_ADDR1;
			अवरोध;
		हाल 16:
			chip->flags |= EE_ADDR2;
			अवरोध;
		हाल 24:
			chip->flags |= EE_ADDR3;
			अवरोध;
		शेष:
			dev_err(dev,
				"Error: bad \"address-width\" property: %u\n",
				val);
			वापस -ENODEV;
		पूर्ण
		अगर (device_property_present(dev, "read-only"))
			chip->flags |= EE_READONLY;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक at25_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा at25_data	*at25 = शून्य;
	काष्ठा spi_eeprom	chip;
	पूर्णांक			err;
	पूर्णांक			sr;
	पूर्णांक			addrlen;

	/* Chip description */
	अगर (!spi->dev.platक्रमm_data) अणु
		err = at25_fw_to_chip(&spi->dev, &chip);
		अगर (err)
			वापस err;
	पूर्ण अन्यथा
		chip = *(काष्ठा spi_eeprom *)spi->dev.platक्रमm_data;

	/* For now we only support 8/16/24 bit addressing */
	अगर (chip.flags & EE_ADDR1)
		addrlen = 1;
	अन्यथा अगर (chip.flags & EE_ADDR2)
		addrlen = 2;
	अन्यथा अगर (chip.flags & EE_ADDR3)
		addrlen = 3;
	अन्यथा अणु
		dev_dbg(&spi->dev, "unsupported address type\n");
		वापस -EINVAL;
	पूर्ण

	/* Ping the chip ... the status रेजिस्टर is pretty portable,
	 * unlike probing manufacturer IDs.  We करो expect that प्रणाली
	 * firmware didn't ग_लिखो it in the past few milliseconds!
	 */
	sr = spi_w8r8(spi, AT25_RDSR);
	अगर (sr < 0 || sr & AT25_SR_nRDY) अणु
		dev_dbg(&spi->dev, "rdsr --> %d (%02x)\n", sr, sr);
		वापस -ENXIO;
	पूर्ण

	at25 = devm_kzalloc(&spi->dev, माप(काष्ठा at25_data), GFP_KERNEL);
	अगर (!at25)
		वापस -ENOMEM;

	mutex_init(&at25->lock);
	at25->chip = chip;
	at25->spi = spi;
	spi_set_drvdata(spi, at25);
	at25->addrlen = addrlen;

	at25->nvmem_config.type = NVMEM_TYPE_EEPROM;
	at25->nvmem_config.name = dev_name(&spi->dev);
	at25->nvmem_config.dev = &spi->dev;
	at25->nvmem_config.पढ़ो_only = chip.flags & EE_READONLY;
	at25->nvmem_config.root_only = true;
	at25->nvmem_config.owner = THIS_MODULE;
	at25->nvmem_config.compat = true;
	at25->nvmem_config.base_dev = &spi->dev;
	at25->nvmem_config.reg_पढ़ो = at25_ee_पढ़ो;
	at25->nvmem_config.reg_ग_लिखो = at25_ee_ग_लिखो;
	at25->nvmem_config.priv = at25;
	at25->nvmem_config.stride = 1;
	at25->nvmem_config.word_size = 1;
	at25->nvmem_config.size = chip.byte_len;

	at25->nvmem = devm_nvmem_रेजिस्टर(&spi->dev, &at25->nvmem_config);
	अगर (IS_ERR(at25->nvmem))
		वापस PTR_ERR(at25->nvmem);

	dev_info(&spi->dev, "%d %s %s eeprom%s, pagesize %u\n",
		(chip.byte_len < 1024) ? chip.byte_len : (chip.byte_len / 1024),
		(chip.byte_len < 1024) ? "Byte" : "KByte",
		at25->chip.name,
		(chip.flags & EE_READONLY) ? " (readonly)" : "",
		at25->chip.page_size);
	वापस 0;
पूर्ण

/*-------------------------------------------------------------------------*/

अटल स्थिर काष्ठा of_device_id at25_of_match[] = अणु
	अणु .compatible = "atmel,at25", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, at25_of_match);

अटल काष्ठा spi_driver at25_driver = अणु
	.driver = अणु
		.name		= "at25",
		.of_match_table = at25_of_match,
	पूर्ण,
	.probe		= at25_probe,
पूर्ण;

module_spi_driver(at25_driver);

MODULE_DESCRIPTION("Driver for most SPI EEPROMs");
MODULE_AUTHOR("David Brownell");
MODULE_LICENSE("GPL");
MODULE_ALIAS("spi:at25");
