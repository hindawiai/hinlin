<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * lm70.c
 *
 * The LM70 is a temperature sensor chip from National Semiconductor (NS).
 * Copyright (C) 2006 Kaiwan N Billimoria <kaiwan@designergraphix.com>
 *
 * The LM70 communicates with a host processor via an SPI/Microwire Bus
 * पूर्णांकerface. The complete datasheet is available at National's website
 * here:
 * http://www.national.com/pf/LM/LM70.hपंचांगl
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/device.h>
#समावेश <linux/err.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/hwmon.h>
#समावेश <linux/mutex.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/property.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/slab.h>
#समावेश <linux/acpi.h>

#घोषणा DRVNAME		"lm70"

#घोषणा LM70_CHIP_LM70		0	/* original NS LM70 */
#घोषणा LM70_CHIP_TMP121	1	/* TI TMP121/TMP123 */
#घोषणा LM70_CHIP_LM71		2	/* NS LM71 */
#घोषणा LM70_CHIP_LM74		3	/* NS LM74 */
#घोषणा LM70_CHIP_TMP122	4	/* TI TMP122/TMP124 */

काष्ठा lm70 अणु
	काष्ठा spi_device *spi;
	काष्ठा mutex lock;
	अचिन्हित पूर्णांक chip;
पूर्ण;

/* sysfs hook function */
अटल sमाप_प्रकार temp1_input_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा lm70 *p_lm70 = dev_get_drvdata(dev);
	काष्ठा spi_device *spi = p_lm70->spi;
	पूर्णांक status, val = 0;
	u8 rxbuf[2];
	s16 raw = 0;

	अगर (mutex_lock_पूर्णांकerruptible(&p_lm70->lock))
		वापस -ERESTARTSYS;

	/*
	 * spi_पढ़ो() requires a DMA-safe buffer; so we use
	 * spi_ग_लिखो_then_पढ़ो(), transmitting 0 bytes.
	 */
	status = spi_ग_लिखो_then_पढ़ो(spi, शून्य, 0, &rxbuf[0], 2);
	अगर (status < 0) अणु
		dev_warn(dev, "spi_write_then_read failed with status %d\n",
			 status);
		जाओ out;
	पूर्ण
	raw = (rxbuf[0] << 8) + rxbuf[1];
	dev_dbg(dev, "rxbuf[0] : 0x%02x rxbuf[1] : 0x%02x raw=0x%04x\n",
		rxbuf[0], rxbuf[1], raw);

	/*
	 * LM70:
	 * The "raw" temperature पढ़ो पूर्णांकo rxbuf[] is a 16-bit चिन्हित 2's
	 * complement value. Only the MSB 11 bits (1 sign + 10 temperature
	 * bits) are meaningful; the LSB 5 bits are to be discarded.
	 * See the datasheet.
	 *
	 * Further, each bit represents 0.25 degrees Celsius; so, multiply
	 * by 0.25. Also multiply by 1000 to represent in millidegrees
	 * Celsius.
	 * So it's equivalent to multiplying by 0.25 * 1000 = 250.
	 *
	 * LM74 and TMP121/TMP122/TMP123/TMP124:
	 * 13 bits of 2's complement data, discard LSB 3 bits,
	 * resolution 0.0625 degrees celsius.
	 *
	 * LM71:
	 * 14 bits of 2's complement data, discard LSB 2 bits,
	 * resolution 0.0312 degrees celsius.
	 */
	चयन (p_lm70->chip) अणु
	हाल LM70_CHIP_LM70:
		val = ((पूर्णांक)raw / 32) * 250;
		अवरोध;

	हाल LM70_CHIP_TMP121:
	हाल LM70_CHIP_TMP122:
	हाल LM70_CHIP_LM74:
		val = ((पूर्णांक)raw / 8) * 625 / 10;
		अवरोध;

	हाल LM70_CHIP_LM71:
		val = ((पूर्णांक)raw / 4) * 3125 / 100;
		अवरोध;
	पूर्ण

	status = प्र_लिखो(buf, "%d\n", val); /* millidegrees Celsius */
out:
	mutex_unlock(&p_lm70->lock);
	वापस status;
पूर्ण

अटल DEVICE_ATTR_RO(temp1_input);

अटल काष्ठा attribute *lm70_attrs[] = अणु
	&dev_attr_temp1_input.attr,
	शून्य
पूर्ण;

ATTRIBUTE_GROUPS(lm70);

/*----------------------------------------------------------------------*/

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id lm70_of_ids[] = अणु
	अणु
		.compatible = "ti,lm70",
		.data = (व्योम *) LM70_CHIP_LM70,
	पूर्ण,
	अणु
		.compatible = "ti,tmp121",
		.data = (व्योम *) LM70_CHIP_TMP121,
	पूर्ण,
	अणु
		.compatible = "ti,tmp122",
		.data = (व्योम *) LM70_CHIP_TMP122,
	पूर्ण,
	अणु
		.compatible = "ti,lm71",
		.data = (व्योम *) LM70_CHIP_LM71,
	पूर्ण,
	अणु
		.compatible = "ti,lm74",
		.data = (व्योम *) LM70_CHIP_LM74,
	पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, lm70_of_ids);
#पूर्ण_अगर

#अगर_घोषित CONFIG_ACPI
अटल स्थिर काष्ठा acpi_device_id lm70_acpi_ids[] = अणु
	अणु
		.id = "LM000070",
		.driver_data = LM70_CHIP_LM70,
	पूर्ण,
	अणु
		.id = "TMP00121",
		.driver_data = LM70_CHIP_TMP121,
	पूर्ण,
	अणु
		.id = "LM000071",
		.driver_data = LM70_CHIP_LM71,
	पूर्ण,
	अणु
		.id = "LM000074",
		.driver_data = LM70_CHIP_LM74,
	पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, lm70_acpi_ids);
#पूर्ण_अगर

अटल पूर्णांक lm70_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा device *hwmon_dev;
	काष्ठा lm70 *p_lm70;
	पूर्णांक chip;

	अगर (dev_fwnode(&spi->dev))
		chip = (पूर्णांक)(uपूर्णांकptr_t)device_get_match_data(&spi->dev);
	अन्यथा
		chip = spi_get_device_id(spi)->driver_data;


	/* संकेतing is SPI_MODE_0 */
	अगर (spi->mode & (SPI_CPOL | SPI_CPHA))
		वापस -EINVAL;

	/* NOTE:  we assume 8-bit words, and convert to 16 bits manually */

	p_lm70 = devm_kzalloc(&spi->dev, माप(*p_lm70), GFP_KERNEL);
	अगर (!p_lm70)
		वापस -ENOMEM;

	mutex_init(&p_lm70->lock);
	p_lm70->chip = chip;
	p_lm70->spi = spi;

	hwmon_dev = devm_hwmon_device_रेजिस्टर_with_groups(&spi->dev,
							   spi->modalias,
							   p_lm70, lm70_groups);
	वापस PTR_ERR_OR_ZERO(hwmon_dev);
पूर्ण

अटल स्थिर काष्ठा spi_device_id lm70_ids[] = अणु
	अणु "lm70",   LM70_CHIP_LM70 पूर्ण,
	अणु "tmp121", LM70_CHIP_TMP121 पूर्ण,
	अणु "tmp122", LM70_CHIP_TMP122 पूर्ण,
	अणु "lm71",   LM70_CHIP_LM71 पूर्ण,
	अणु "lm74",   LM70_CHIP_LM74 पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(spi, lm70_ids);

अटल काष्ठा spi_driver lm70_driver = अणु
	.driver = अणु
		.name	= "lm70",
		.of_match_table	= of_match_ptr(lm70_of_ids),
		.acpi_match_table = ACPI_PTR(lm70_acpi_ids),
	पूर्ण,
	.id_table = lm70_ids,
	.probe	= lm70_probe,
पूर्ण;

module_spi_driver(lm70_driver);

MODULE_AUTHOR("Kaiwan N Billimoria");
MODULE_DESCRIPTION("NS LM70 and compatibles Linux driver");
MODULE_LICENSE("GPL");
