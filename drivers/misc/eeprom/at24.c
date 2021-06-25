<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * at24.c - handle most I2C EEPROMs
 *
 * Copyright (C) 2005-2007 David Brownell
 * Copyright (C) 2008 Wolfram Sang, Pengutronix
 */

#समावेश <linux/acpi.h>
#समावेश <linux/bitops.h>
#समावेश <linux/capability.h>
#समावेश <linux/delay.h>
#समावेश <linux/i2c.h>
#समावेश <linux/init.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/nvmem-provider.h>
#समावेश <linux/of_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/property.h>
#समावेश <linux/regmap.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/slab.h>

/* Address poपूर्णांकer is 16 bit. */
#घोषणा AT24_FLAG_ADDR16	BIT(7)
/* sysfs-entry will be पढ़ो-only. */
#घोषणा AT24_FLAG_READONLY	BIT(6)
/* sysfs-entry will be world-पढ़ोable. */
#घोषणा AT24_FLAG_IRUGO		BIT(5)
/* Take always 8 addresses (24c00). */
#घोषणा AT24_FLAG_TAKE8ADDR	BIT(4)
/* Factory-programmed serial number. */
#घोषणा AT24_FLAG_SERIAL	BIT(3)
/* Factory-programmed mac address. */
#घोषणा AT24_FLAG_MAC		BIT(2)
/* Does not स्वतः-rollover पढ़ोs to the next slave address. */
#घोषणा AT24_FLAG_NO_RDROL	BIT(1)

/*
 * I2C EEPROMs from most venकरोrs are inexpensive and mostly पूर्णांकerchangeable.
 * Dअगरferences between dअगरferent venकरोr product lines (like Aपंचांगel AT24C or
 * MicroChip 24LC, etc) won't much matter क्रम typical पढ़ो/ग_लिखो access.
 * There are also I2C RAM chips, likewise पूर्णांकerchangeable. One example
 * would be the PCF8570, which acts like a 24c02 EEPROM (256 bytes).
 *
 * However, misconfiguration can lose data. "Set 16-bit memory address"
 * to a part with 8-bit addressing will overग_लिखो data. Writing with too
 * big a page size also loses data. And it's not safe to assume that the
 * conventional addresses 0x50..0x57 only hold eeproms; a PCF8563 RTC
 * uses 0x51, क्रम just one example.
 *
 * Accordingly, explicit board-specअगरic configuration data should be used
 * in almost all हालs. (One partial exception is an SMBus used to access
 * "SPD" data क्रम DRAM sticks. Those only use 24c02 EEPROMs.)
 *
 * So this driver uses "new style" I2C driver binding, expecting to be
 * told what devices exist. That may be in arch/X/mach-Y/board-Z.c or
 * similar kernel-resident tables; or, configuration data coming from
 * a bootloader.
 *
 * Other than binding model, current dअगरferences from "eeprom" driver are
 * that this one handles ग_लिखो access and isn't restricted to 24c02 devices.
 * It also handles larger devices (32 kbit and up) with two-byte addresses,
 * which won't work on pure SMBus प्रणालीs.
 */

काष्ठा at24_client अणु
	काष्ठा i2c_client *client;
	काष्ठा regmap *regmap;
पूर्ण;

काष्ठा at24_data अणु
	/*
	 * Lock protects against activities from other Linux tasks,
	 * but not from changes by other I2C masters.
	 */
	काष्ठा mutex lock;

	अचिन्हित पूर्णांक ग_लिखो_max;
	अचिन्हित पूर्णांक num_addresses;
	अचिन्हित पूर्णांक offset_adj;

	u32 byte_len;
	u16 page_size;
	u8 flags;

	काष्ठा nvmem_device *nvmem;
	काष्ठा regulator *vcc_reg;
	व्योम (*पढ़ो_post)(अचिन्हित पूर्णांक off, अक्षर *buf, माप_प्रकार count);

	/*
	 * Some chips tie up multiple I2C addresses; dummy devices reserve
	 * them क्रम us, and we'll use them with SMBus calls.
	 */
	काष्ठा at24_client client[];
पूर्ण;

/*
 * This parameter is to help this driver aव्योम blocking other drivers out
 * of I2C क्रम potentially troublesome amounts of समय. With a 100 kHz I2C
 * घड़ी, one 256 byte पढ़ो takes about 1/43 second which is excessive;
 * but the 1/170 second it takes at 400 kHz may be quite reasonable; and
 * at 1 MHz (Fm+) a 1/430 second delay could easily be invisible.
 *
 * This value is क्रमced to be a घातer of two so that ग_लिखोs align on pages.
 */
अटल अचिन्हित पूर्णांक at24_io_limit = 128;
module_param_named(io_limit, at24_io_limit, uपूर्णांक, 0);
MODULE_PARM_DESC(at24_io_limit, "Maximum bytes per I/O (default 128)");

/*
 * Specs often allow 5 msec क्रम a page ग_लिखो, someबार 20 msec;
 * it's important to recover from ग_लिखो समयouts.
 */
अटल अचिन्हित पूर्णांक at24_ग_लिखो_समयout = 25;
module_param_named(ग_लिखो_समयout, at24_ग_लिखो_समयout, uपूर्णांक, 0);
MODULE_PARM_DESC(at24_ग_लिखो_समयout, "Time (in ms) to try writes (default 25)");

काष्ठा at24_chip_data अणु
	u32 byte_len;
	u8 flags;
	व्योम (*पढ़ो_post)(अचिन्हित पूर्णांक off, अक्षर *buf, माप_प्रकार count);
पूर्ण;

#घोषणा AT24_CHIP_DATA(_name, _len, _flags)				\
	अटल स्थिर काष्ठा at24_chip_data _name = अणु			\
		.byte_len = _len, .flags = _flags,			\
	पूर्ण

#घोषणा AT24_CHIP_DATA_CB(_name, _len, _flags, _पढ़ो_post)		\
	अटल स्थिर काष्ठा at24_chip_data _name = अणु			\
		.byte_len = _len, .flags = _flags,			\
		.पढ़ो_post = _पढ़ो_post,				\
	पूर्ण

अटल व्योम at24_पढ़ो_post_vaio(अचिन्हित पूर्णांक off, अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक i;

	अगर (capable(CAP_SYS_ADMIN))
		वापस;

	/*
	 * Hide VAIO निजी settings to regular users:
	 * - BIOS passwords: bytes 0x00 to 0x0f
	 * - UUID: bytes 0x10 to 0x1f
	 * - Serial number: 0xc0 to 0xdf
	 */
	क्रम (i = 0; i < count; i++) अणु
		अगर ((off + i <= 0x1f) ||
		    (off + i >= 0xc0 && off + i <= 0xdf))
			buf[i] = 0;
	पूर्ण
पूर्ण

/* needs 8 addresses as A0-A2 are ignored */
AT24_CHIP_DATA(at24_data_24c00, 128 / 8, AT24_FLAG_TAKE8ADDR);
/* old variants can't be handled with this generic entry! */
AT24_CHIP_DATA(at24_data_24c01, 1024 / 8, 0);
AT24_CHIP_DATA(at24_data_24cs01, 16,
	AT24_FLAG_SERIAL | AT24_FLAG_READONLY);
AT24_CHIP_DATA(at24_data_24c02, 2048 / 8, 0);
AT24_CHIP_DATA(at24_data_24cs02, 16,
	AT24_FLAG_SERIAL | AT24_FLAG_READONLY);
AT24_CHIP_DATA(at24_data_24mac402, 48 / 8,
	AT24_FLAG_MAC | AT24_FLAG_READONLY);
AT24_CHIP_DATA(at24_data_24mac602, 64 / 8,
	AT24_FLAG_MAC | AT24_FLAG_READONLY);
/* spd is a 24c02 in memory DIMMs */
AT24_CHIP_DATA(at24_data_spd, 2048 / 8,
	AT24_FLAG_READONLY | AT24_FLAG_IRUGO);
/* 24c02_vaio is a 24c02 on some Sony laptops */
AT24_CHIP_DATA_CB(at24_data_24c02_vaio, 2048 / 8,
	AT24_FLAG_READONLY | AT24_FLAG_IRUGO,
	at24_पढ़ो_post_vaio);
AT24_CHIP_DATA(at24_data_24c04, 4096 / 8, 0);
AT24_CHIP_DATA(at24_data_24cs04, 16,
	AT24_FLAG_SERIAL | AT24_FLAG_READONLY);
/* 24rf08 quirk is handled at i2c-core */
AT24_CHIP_DATA(at24_data_24c08, 8192 / 8, 0);
AT24_CHIP_DATA(at24_data_24cs08, 16,
	AT24_FLAG_SERIAL | AT24_FLAG_READONLY);
AT24_CHIP_DATA(at24_data_24c16, 16384 / 8, 0);
AT24_CHIP_DATA(at24_data_24cs16, 16,
	AT24_FLAG_SERIAL | AT24_FLAG_READONLY);
AT24_CHIP_DATA(at24_data_24c32, 32768 / 8, AT24_FLAG_ADDR16);
AT24_CHIP_DATA(at24_data_24cs32, 16,
	AT24_FLAG_ADDR16 | AT24_FLAG_SERIAL | AT24_FLAG_READONLY);
AT24_CHIP_DATA(at24_data_24c64, 65536 / 8, AT24_FLAG_ADDR16);
AT24_CHIP_DATA(at24_data_24cs64, 16,
	AT24_FLAG_ADDR16 | AT24_FLAG_SERIAL | AT24_FLAG_READONLY);
AT24_CHIP_DATA(at24_data_24c128, 131072 / 8, AT24_FLAG_ADDR16);
AT24_CHIP_DATA(at24_data_24c256, 262144 / 8, AT24_FLAG_ADDR16);
AT24_CHIP_DATA(at24_data_24c512, 524288 / 8, AT24_FLAG_ADDR16);
AT24_CHIP_DATA(at24_data_24c1024, 1048576 / 8, AT24_FLAG_ADDR16);
AT24_CHIP_DATA(at24_data_24c2048, 2097152 / 8, AT24_FLAG_ADDR16);
/* identical to 24c08 ? */
AT24_CHIP_DATA(at24_data_INT3499, 8192 / 8, 0);

अटल स्थिर काष्ठा i2c_device_id at24_ids[] = अणु
	अणु "24c00",	(kernel_uदीर्घ_t)&at24_data_24c00 पूर्ण,
	अणु "24c01",	(kernel_uदीर्घ_t)&at24_data_24c01 पूर्ण,
	अणु "24cs01",	(kernel_uदीर्घ_t)&at24_data_24cs01 पूर्ण,
	अणु "24c02",	(kernel_uदीर्घ_t)&at24_data_24c02 पूर्ण,
	अणु "24cs02",	(kernel_uदीर्घ_t)&at24_data_24cs02 पूर्ण,
	अणु "24mac402",	(kernel_uदीर्घ_t)&at24_data_24mac402 पूर्ण,
	अणु "24mac602",	(kernel_uदीर्घ_t)&at24_data_24mac602 पूर्ण,
	अणु "spd",	(kernel_uदीर्घ_t)&at24_data_spd पूर्ण,
	अणु "24c02-vaio",	(kernel_uदीर्घ_t)&at24_data_24c02_vaio पूर्ण,
	अणु "24c04",	(kernel_uदीर्घ_t)&at24_data_24c04 पूर्ण,
	अणु "24cs04",	(kernel_uदीर्घ_t)&at24_data_24cs04 पूर्ण,
	अणु "24c08",	(kernel_uदीर्घ_t)&at24_data_24c08 पूर्ण,
	अणु "24cs08",	(kernel_uदीर्घ_t)&at24_data_24cs08 पूर्ण,
	अणु "24c16",	(kernel_uदीर्घ_t)&at24_data_24c16 पूर्ण,
	अणु "24cs16",	(kernel_uदीर्घ_t)&at24_data_24cs16 पूर्ण,
	अणु "24c32",	(kernel_uदीर्घ_t)&at24_data_24c32 पूर्ण,
	अणु "24cs32",	(kernel_uदीर्घ_t)&at24_data_24cs32 पूर्ण,
	अणु "24c64",	(kernel_uदीर्घ_t)&at24_data_24c64 पूर्ण,
	अणु "24cs64",	(kernel_uदीर्घ_t)&at24_data_24cs64 पूर्ण,
	अणु "24c128",	(kernel_uदीर्घ_t)&at24_data_24c128 पूर्ण,
	अणु "24c256",	(kernel_uदीर्घ_t)&at24_data_24c256 पूर्ण,
	अणु "24c512",	(kernel_uदीर्घ_t)&at24_data_24c512 पूर्ण,
	अणु "24c1024",	(kernel_uदीर्घ_t)&at24_data_24c1024 पूर्ण,
	अणु "24c2048",    (kernel_uदीर्घ_t)&at24_data_24c2048 पूर्ण,
	अणु "at24",	0 पूर्ण,
	अणु /* END OF LIST */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, at24_ids);

अटल स्थिर काष्ठा of_device_id at24_of_match[] = अणु
	अणु .compatible = "atmel,24c00",		.data = &at24_data_24c00 पूर्ण,
	अणु .compatible = "atmel,24c01",		.data = &at24_data_24c01 पूर्ण,
	अणु .compatible = "atmel,24cs01",		.data = &at24_data_24cs01 पूर्ण,
	अणु .compatible = "atmel,24c02",		.data = &at24_data_24c02 पूर्ण,
	अणु .compatible = "atmel,24cs02",		.data = &at24_data_24cs02 पूर्ण,
	अणु .compatible = "atmel,24mac402",	.data = &at24_data_24mac402 पूर्ण,
	अणु .compatible = "atmel,24mac602",	.data = &at24_data_24mac602 पूर्ण,
	अणु .compatible = "atmel,spd",		.data = &at24_data_spd पूर्ण,
	अणु .compatible = "atmel,24c04",		.data = &at24_data_24c04 पूर्ण,
	अणु .compatible = "atmel,24cs04",		.data = &at24_data_24cs04 पूर्ण,
	अणु .compatible = "atmel,24c08",		.data = &at24_data_24c08 पूर्ण,
	अणु .compatible = "atmel,24cs08",		.data = &at24_data_24cs08 पूर्ण,
	अणु .compatible = "atmel,24c16",		.data = &at24_data_24c16 पूर्ण,
	अणु .compatible = "atmel,24cs16",		.data = &at24_data_24cs16 पूर्ण,
	अणु .compatible = "atmel,24c32",		.data = &at24_data_24c32 पूर्ण,
	अणु .compatible = "atmel,24cs32",		.data = &at24_data_24cs32 पूर्ण,
	अणु .compatible = "atmel,24c64",		.data = &at24_data_24c64 पूर्ण,
	अणु .compatible = "atmel,24cs64",		.data = &at24_data_24cs64 पूर्ण,
	अणु .compatible = "atmel,24c128",		.data = &at24_data_24c128 पूर्ण,
	अणु .compatible = "atmel,24c256",		.data = &at24_data_24c256 पूर्ण,
	अणु .compatible = "atmel,24c512",		.data = &at24_data_24c512 पूर्ण,
	अणु .compatible = "atmel,24c1024",	.data = &at24_data_24c1024 पूर्ण,
	अणु .compatible = "atmel,24c2048",	.data = &at24_data_24c2048 पूर्ण,
	अणु /* END OF LIST */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, at24_of_match);

अटल स्थिर काष्ठा acpi_device_id __maybe_unused at24_acpi_ids[] = अणु
	अणु "INT3499",	(kernel_uदीर्घ_t)&at24_data_INT3499 पूर्ण,
	अणु "TPF0001",	(kernel_uदीर्घ_t)&at24_data_24c1024 पूर्ण,
	अणु /* END OF LIST */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(acpi, at24_acpi_ids);

/*
 * This routine supports chips which consume multiple I2C addresses. It
 * computes the addressing inक्रमmation to be used क्रम a given r/w request.
 * Assumes that sanity checks क्रम offset happened at sysfs-layer.
 *
 * Slave address and byte offset derive from the offset. Always
 * set the byte address; on a multi-master board, another master
 * may have changed the chip's "current" address poपूर्णांकer.
 */
अटल काष्ठा at24_client *at24_translate_offset(काष्ठा at24_data *at24,
						 अचिन्हित पूर्णांक *offset)
अणु
	अचिन्हित पूर्णांक i;

	अगर (at24->flags & AT24_FLAG_ADDR16) अणु
		i = *offset >> 16;
		*offset &= 0xffff;
	पूर्ण अन्यथा अणु
		i = *offset >> 8;
		*offset &= 0xff;
	पूर्ण

	वापस &at24->client[i];
पूर्ण

अटल काष्ठा device *at24_base_client_dev(काष्ठा at24_data *at24)
अणु
	वापस &at24->client[0].client->dev;
पूर्ण

अटल माप_प्रकार at24_adjust_पढ़ो_count(काष्ठा at24_data *at24,
				      अचिन्हित पूर्णांक offset, माप_प्रकार count)
अणु
	अचिन्हित पूर्णांक bits;
	माप_प्रकार reमुख्यder;

	/*
	 * In हाल of multi-address chips that करोn't rollover पढ़ोs to
	 * the next slave address: truncate the count to the slave boundary,
	 * so that the पढ़ो never straddles slaves.
	 */
	अगर (at24->flags & AT24_FLAG_NO_RDROL) अणु
		bits = (at24->flags & AT24_FLAG_ADDR16) ? 16 : 8;
		reमुख्यder = BIT(bits) - offset;
		अगर (count > reमुख्यder)
			count = reमुख्यder;
	पूर्ण

	अगर (count > at24_io_limit)
		count = at24_io_limit;

	वापस count;
पूर्ण

अटल sमाप_प्रकार at24_regmap_पढ़ो(काष्ठा at24_data *at24, अक्षर *buf,
				अचिन्हित पूर्णांक offset, माप_प्रकार count)
अणु
	अचिन्हित दीर्घ समयout, पढ़ो_समय;
	काष्ठा at24_client *at24_client;
	काष्ठा i2c_client *client;
	काष्ठा regmap *regmap;
	पूर्णांक ret;

	at24_client = at24_translate_offset(at24, &offset);
	regmap = at24_client->regmap;
	client = at24_client->client;
	count = at24_adjust_पढ़ो_count(at24, offset, count);

	/* adjust offset क्रम mac and serial पढ़ो ops */
	offset += at24->offset_adj;

	समयout = jअगरfies + msecs_to_jअगरfies(at24_ग_लिखो_समयout);
	करो अणु
		/*
		 * The बारtamp shall be taken beक्रमe the actual operation
		 * to aव्योम a premature समयout in हाल of high CPU load.
		 */
		पढ़ो_समय = jअगरfies;

		ret = regmap_bulk_पढ़ो(regmap, offset, buf, count);
		dev_dbg(&client->dev, "read %zu@%d --> %d (%ld)\n",
			count, offset, ret, jअगरfies);
		अगर (!ret)
			वापस count;

		usleep_range(1000, 1500);
	पूर्ण जबतक (समय_beक्रमe(पढ़ो_समय, समयout));

	वापस -ETIMEDOUT;
पूर्ण

/*
 * Note that अगर the hardware ग_लिखो-protect pin is pulled high, the whole
 * chip is normally ग_लिखो रक्षित. But there are plenty of product
 * variants here, including OTP fuses and partial chip protect.
 *
 * We only use page mode ग_लिखोs; the alternative is sloooow. These routines
 * ग_लिखो at most one page.
 */

अटल माप_प्रकार at24_adjust_ग_लिखो_count(काष्ठा at24_data *at24,
				      अचिन्हित पूर्णांक offset, माप_प्रकार count)
अणु
	अचिन्हित पूर्णांक next_page;

	/* ग_लिखो_max is at most a page */
	अगर (count > at24->ग_लिखो_max)
		count = at24->ग_लिखो_max;

	/* Never roll over backwards, to the start of this page */
	next_page = roundup(offset + 1, at24->page_size);
	अगर (offset + count > next_page)
		count = next_page - offset;

	वापस count;
पूर्ण

अटल sमाप_प्रकार at24_regmap_ग_लिखो(काष्ठा at24_data *at24, स्थिर अक्षर *buf,
				 अचिन्हित पूर्णांक offset, माप_प्रकार count)
अणु
	अचिन्हित दीर्घ समयout, ग_लिखो_समय;
	काष्ठा at24_client *at24_client;
	काष्ठा i2c_client *client;
	काष्ठा regmap *regmap;
	पूर्णांक ret;

	at24_client = at24_translate_offset(at24, &offset);
	regmap = at24_client->regmap;
	client = at24_client->client;
	count = at24_adjust_ग_लिखो_count(at24, offset, count);
	समयout = jअगरfies + msecs_to_jअगरfies(at24_ग_लिखो_समयout);

	करो अणु
		/*
		 * The बारtamp shall be taken beक्रमe the actual operation
		 * to aव्योम a premature समयout in हाल of high CPU load.
		 */
		ग_लिखो_समय = jअगरfies;

		ret = regmap_bulk_ग_लिखो(regmap, offset, buf, count);
		dev_dbg(&client->dev, "write %zu@%d --> %d (%ld)\n",
			count, offset, ret, jअगरfies);
		अगर (!ret)
			वापस count;

		usleep_range(1000, 1500);
	पूर्ण जबतक (समय_beक्रमe(ग_लिखो_समय, समयout));

	वापस -ETIMEDOUT;
पूर्ण

अटल पूर्णांक at24_पढ़ो(व्योम *priv, अचिन्हित पूर्णांक off, व्योम *val, माप_प्रकार count)
अणु
	काष्ठा at24_data *at24;
	काष्ठा device *dev;
	अक्षर *buf = val;
	पूर्णांक i, ret;

	at24 = priv;
	dev = at24_base_client_dev(at24);

	अगर (unlikely(!count))
		वापस count;

	अगर (off + count > at24->byte_len)
		वापस -EINVAL;

	ret = pm_runसमय_get_sync(dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_noidle(dev);
		वापस ret;
	पूर्ण

	/*
	 * Read data from chip, protecting against concurrent updates
	 * from this host, but not from other I2C masters.
	 */
	mutex_lock(&at24->lock);

	क्रम (i = 0; count; i += ret, count -= ret) अणु
		ret = at24_regmap_पढ़ो(at24, buf + i, off + i, count);
		अगर (ret < 0) अणु
			mutex_unlock(&at24->lock);
			pm_runसमय_put(dev);
			वापस ret;
		पूर्ण
	पूर्ण

	mutex_unlock(&at24->lock);

	pm_runसमय_put(dev);

	अगर (unlikely(at24->पढ़ो_post))
		at24->पढ़ो_post(off, buf, i);

	वापस 0;
पूर्ण

अटल पूर्णांक at24_ग_लिखो(व्योम *priv, अचिन्हित पूर्णांक off, व्योम *val, माप_प्रकार count)
अणु
	काष्ठा at24_data *at24;
	काष्ठा device *dev;
	अक्षर *buf = val;
	पूर्णांक ret;

	at24 = priv;
	dev = at24_base_client_dev(at24);

	अगर (unlikely(!count))
		वापस -EINVAL;

	अगर (off + count > at24->byte_len)
		वापस -EINVAL;

	ret = pm_runसमय_get_sync(dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_noidle(dev);
		वापस ret;
	पूर्ण

	/*
	 * Write data to chip, protecting against concurrent updates
	 * from this host, but not from other I2C masters.
	 */
	mutex_lock(&at24->lock);

	जबतक (count) अणु
		ret = at24_regmap_ग_लिखो(at24, buf, off, count);
		अगर (ret < 0) अणु
			mutex_unlock(&at24->lock);
			pm_runसमय_put(dev);
			वापस ret;
		पूर्ण
		buf += ret;
		off += ret;
		count -= ret;
	पूर्ण

	mutex_unlock(&at24->lock);

	pm_runसमय_put(dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा at24_chip_data *at24_get_chip_data(काष्ठा device *dev)
अणु
	काष्ठा device_node *of_node = dev->of_node;
	स्थिर काष्ठा at24_chip_data *cdata;
	स्थिर काष्ठा i2c_device_id *id;

	id = i2c_match_id(at24_ids, to_i2c_client(dev));

	/*
	 * The I2C core allows OF nodes compatibles to match against the
	 * I2C device ID table as a fallback, so check not only अगर an OF
	 * node is present but also अगर it matches an OF device ID entry.
	 */
	अगर (of_node && of_match_device(at24_of_match, dev))
		cdata = of_device_get_match_data(dev);
	अन्यथा अगर (id)
		cdata = (व्योम *)id->driver_data;
	अन्यथा
		cdata = acpi_device_get_match_data(dev);

	अगर (!cdata)
		वापस ERR_PTR(-ENODEV);

	वापस cdata;
पूर्ण

अटल पूर्णांक at24_make_dummy_client(काष्ठा at24_data *at24, अचिन्हित पूर्णांक index,
				  काष्ठा regmap_config *regmap_config)
अणु
	काष्ठा i2c_client *base_client, *dummy_client;
	काष्ठा regmap *regmap;
	काष्ठा device *dev;

	base_client = at24->client[0].client;
	dev = &base_client->dev;

	dummy_client = devm_i2c_new_dummy_device(dev, base_client->adapter,
						 base_client->addr + index);
	अगर (IS_ERR(dummy_client))
		वापस PTR_ERR(dummy_client);

	regmap = devm_regmap_init_i2c(dummy_client, regmap_config);
	अगर (IS_ERR(regmap))
		वापस PTR_ERR(regmap);

	at24->client[index].client = dummy_client;
	at24->client[index].regmap = regmap;

	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक at24_get_offset_adj(u8 flags, अचिन्हित पूर्णांक byte_len)
अणु
	अगर (flags & AT24_FLAG_MAC) अणु
		/* EUI-48 starts from 0x9a, EUI-64 from 0x98 */
		वापस 0xa0 - byte_len;
	पूर्ण अन्यथा अगर (flags & AT24_FLAG_SERIAL && flags & AT24_FLAG_ADDR16) अणु
		/*
		 * For 16 bit address poपूर्णांकers, the word address must contain
		 * a '10' sequence in bits 11 and 10 regardless of the
		 * पूर्णांकended position of the address poपूर्णांकer.
		 */
		वापस 0x0800;
	पूर्ण अन्यथा अगर (flags & AT24_FLAG_SERIAL) अणु
		/*
		 * Otherwise the word address must begin with a '10' sequence,
		 * regardless of the पूर्णांकended address.
		 */
		वापस 0x0080;
	पूर्ण अन्यथा अणु
		वापस 0;
	पूर्ण
पूर्ण

अटल पूर्णांक at24_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा regmap_config regmap_config = अणु पूर्ण;
	काष्ठा nvmem_config nvmem_config = अणु पूर्ण;
	u32 byte_len, page_size, flags, addrw;
	स्थिर काष्ठा at24_chip_data *cdata;
	काष्ठा device *dev = &client->dev;
	bool i2c_fn_i2c, i2c_fn_block;
	अचिन्हित पूर्णांक i, num_addresses;
	काष्ठा at24_data *at24;
	काष्ठा regmap *regmap;
	bool writable;
	u8 test_byte;
	पूर्णांक err;

	i2c_fn_i2c = i2c_check_functionality(client->adapter, I2C_FUNC_I2C);
	i2c_fn_block = i2c_check_functionality(client->adapter,
					       I2C_FUNC_SMBUS_WRITE_I2C_BLOCK);

	cdata = at24_get_chip_data(dev);
	अगर (IS_ERR(cdata))
		वापस PTR_ERR(cdata);

	err = device_property_पढ़ो_u32(dev, "pagesize", &page_size);
	अगर (err)
		/*
		 * This is slow, but we can't know all eeproms, so we better
		 * play safe. Specअगरying custom eeprom-types via device tree
		 * or properties is recommended anyhow.
		 */
		page_size = 1;

	flags = cdata->flags;
	अगर (device_property_present(dev, "read-only"))
		flags |= AT24_FLAG_READONLY;
	अगर (device_property_present(dev, "no-read-rollover"))
		flags |= AT24_FLAG_NO_RDROL;

	err = device_property_पढ़ो_u32(dev, "address-width", &addrw);
	अगर (!err) अणु
		चयन (addrw) अणु
		हाल 8:
			अगर (flags & AT24_FLAG_ADDR16)
				dev_warn(dev,
					 "Override address width to be 8, while default is 16\n");
			flags &= ~AT24_FLAG_ADDR16;
			अवरोध;
		हाल 16:
			flags |= AT24_FLAG_ADDR16;
			अवरोध;
		शेष:
			dev_warn(dev, "Bad \"address-width\" property: %u\n",
				 addrw);
		पूर्ण
	पूर्ण

	err = device_property_पढ़ो_u32(dev, "size", &byte_len);
	अगर (err)
		byte_len = cdata->byte_len;

	अगर (!i2c_fn_i2c && !i2c_fn_block)
		page_size = 1;

	अगर (!page_size) अणु
		dev_err(dev, "page_size must not be 0!\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!is_घातer_of_2(page_size))
		dev_warn(dev, "page_size looks suspicious (no power of 2)!\n");

	err = device_property_पढ़ो_u32(dev, "num-addresses", &num_addresses);
	अगर (err) अणु
		अगर (flags & AT24_FLAG_TAKE8ADDR)
			num_addresses = 8;
		अन्यथा
			num_addresses =	DIV_ROUND_UP(byte_len,
				(flags & AT24_FLAG_ADDR16) ? 65536 : 256);
	पूर्ण

	अगर ((flags & AT24_FLAG_SERIAL) && (flags & AT24_FLAG_MAC)) अणु
		dev_err(dev,
			"invalid device data - cannot have both AT24_FLAG_SERIAL & AT24_FLAG_MAC.");
		वापस -EINVAL;
	पूर्ण

	regmap_config.val_bits = 8;
	regmap_config.reg_bits = (flags & AT24_FLAG_ADDR16) ? 16 : 8;
	regmap_config.disable_locking = true;

	regmap = devm_regmap_init_i2c(client, &regmap_config);
	अगर (IS_ERR(regmap))
		वापस PTR_ERR(regmap);

	at24 = devm_kzalloc(dev, काष्ठा_size(at24, client, num_addresses),
			    GFP_KERNEL);
	अगर (!at24)
		वापस -ENOMEM;

	mutex_init(&at24->lock);
	at24->byte_len = byte_len;
	at24->page_size = page_size;
	at24->flags = flags;
	at24->पढ़ो_post = cdata->पढ़ो_post;
	at24->num_addresses = num_addresses;
	at24->offset_adj = at24_get_offset_adj(flags, byte_len);
	at24->client[0].client = client;
	at24->client[0].regmap = regmap;

	at24->vcc_reg = devm_regulator_get(dev, "vcc");
	अगर (IS_ERR(at24->vcc_reg))
		वापस PTR_ERR(at24->vcc_reg);

	writable = !(flags & AT24_FLAG_READONLY);
	अगर (writable) अणु
		at24->ग_लिखो_max = min_t(अचिन्हित पूर्णांक,
					page_size, at24_io_limit);
		अगर (!i2c_fn_i2c && at24->ग_लिखो_max > I2C_SMBUS_BLOCK_MAX)
			at24->ग_लिखो_max = I2C_SMBUS_BLOCK_MAX;
	पूर्ण

	/* use dummy devices क्रम multiple-address chips */
	क्रम (i = 1; i < num_addresses; i++) अणु
		err = at24_make_dummy_client(at24, i, &regmap_config);
		अगर (err)
			वापस err;
	पूर्ण

	/*
	 * If the 'label' property is not present क्रम the AT24 EEPROM,
	 * then nvmem_config.id is initialised to NVMEM_DEVID_AUTO,
	 * and this will append the 'devid' to the name of the NVMEM
	 * device. This is purely legacy and the AT24 driver has always
	 * शेषed to this. However, अगर the 'label' property is
	 * present then this means that the name is specअगरied by the
	 * firmware and this name should be used verbatim and so it is
	 * not necessary to append the 'devid'.
	 */
	अगर (device_property_present(dev, "label")) अणु
		nvmem_config.id = NVMEM_DEVID_NONE;
		err = device_property_पढ़ो_string(dev, "label",
						  &nvmem_config.name);
		अगर (err)
			वापस err;
	पूर्ण अन्यथा अणु
		nvmem_config.id = NVMEM_DEVID_AUTO;
		nvmem_config.name = dev_name(dev);
	पूर्ण

	nvmem_config.type = NVMEM_TYPE_EEPROM;
	nvmem_config.dev = dev;
	nvmem_config.पढ़ो_only = !writable;
	nvmem_config.root_only = !(flags & AT24_FLAG_IRUGO);
	nvmem_config.owner = THIS_MODULE;
	nvmem_config.compat = true;
	nvmem_config.base_dev = dev;
	nvmem_config.reg_पढ़ो = at24_पढ़ो;
	nvmem_config.reg_ग_लिखो = at24_ग_लिखो;
	nvmem_config.priv = at24;
	nvmem_config.stride = 1;
	nvmem_config.word_size = 1;
	nvmem_config.size = byte_len;

	i2c_set_clientdata(client, at24);

	err = regulator_enable(at24->vcc_reg);
	अगर (err) अणु
		dev_err(dev, "Failed to enable vcc regulator\n");
		वापस err;
	पूर्ण

	/* enable runसमय pm */
	pm_runसमय_set_active(dev);
	pm_runसमय_enable(dev);

	at24->nvmem = devm_nvmem_रेजिस्टर(dev, &nvmem_config);
	अगर (IS_ERR(at24->nvmem)) अणु
		pm_runसमय_disable(dev);
		अगर (!pm_runसमय_status_suspended(dev))
			regulator_disable(at24->vcc_reg);
		वापस PTR_ERR(at24->nvmem);
	पूर्ण

	/*
	 * Perक्रमm a one-byte test पढ़ो to verअगरy that the
	 * chip is functional.
	 */
	err = at24_पढ़ो(at24, 0, &test_byte, 1);
	अगर (err) अणु
		pm_runसमय_disable(dev);
		अगर (!pm_runसमय_status_suspended(dev))
			regulator_disable(at24->vcc_reg);
		वापस -ENODEV;
	पूर्ण

	pm_runसमय_idle(dev);

	अगर (writable)
		dev_info(dev, "%u byte %s EEPROM, writable, %u bytes/write\n",
			 byte_len, client->name, at24->ग_लिखो_max);
	अन्यथा
		dev_info(dev, "%u byte %s EEPROM, read-only\n",
			 byte_len, client->name);

	वापस 0;
पूर्ण

अटल पूर्णांक at24_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा at24_data *at24 = i2c_get_clientdata(client);

	pm_runसमय_disable(&client->dev);
	अगर (!pm_runसमय_status_suspended(&client->dev))
		regulator_disable(at24->vcc_reg);
	pm_runसमय_set_suspended(&client->dev);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused at24_suspend(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा at24_data *at24 = i2c_get_clientdata(client);

	वापस regulator_disable(at24->vcc_reg);
पूर्ण

अटल पूर्णांक __maybe_unused at24_resume(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा at24_data *at24 = i2c_get_clientdata(client);

	वापस regulator_enable(at24->vcc_reg);
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops at24_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(pm_runसमय_क्रमce_suspend,
				pm_runसमय_क्रमce_resume)
	SET_RUNTIME_PM_OPS(at24_suspend, at24_resume, शून्य)
पूर्ण;

अटल काष्ठा i2c_driver at24_driver = अणु
	.driver = अणु
		.name = "at24",
		.pm = &at24_pm_ops,
		.of_match_table = at24_of_match,
		.acpi_match_table = ACPI_PTR(at24_acpi_ids),
	पूर्ण,
	.probe_new = at24_probe,
	.हटाओ = at24_हटाओ,
	.id_table = at24_ids,
पूर्ण;

अटल पूर्णांक __init at24_init(व्योम)
अणु
	अगर (!at24_io_limit) अणु
		pr_err("at24: at24_io_limit must not be 0!\n");
		वापस -EINVAL;
	पूर्ण

	at24_io_limit = roundकरोwn_घात_of_two(at24_io_limit);
	वापस i2c_add_driver(&at24_driver);
पूर्ण
module_init(at24_init);

अटल व्योम __निकास at24_निकास(व्योम)
अणु
	i2c_del_driver(&at24_driver);
पूर्ण
module_निकास(at24_निकास);

MODULE_DESCRIPTION("Driver for most I2C EEPROMs");
MODULE_AUTHOR("David Brownell and Wolfram Sang");
MODULE_LICENSE("GPL");
