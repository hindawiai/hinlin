<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* drivers/video/backlight/ili9320.c
 *
 * ILI9320 LCD controller driver core.
 *
 * Copyright 2007 Simtec Electronics
 *	http://armlinux.simtec.co.uk/
 *	Ben Dooks <ben@simtec.co.uk>
*/

#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/fb.h>
#समावेश <linux/init.h>
#समावेश <linux/lcd.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>

#समावेश <linux/spi/spi.h>

#समावेश <video/ili9320.h>

#समावेश "ili9320.h"


अटल अंतरभूत पूर्णांक ili9320_ग_लिखो_spi(काष्ठा ili9320 *ili,
				    अचिन्हित पूर्णांक reg,
				    अचिन्हित पूर्णांक value)
अणु
	काष्ठा ili9320_spi *spi = &ili->access.spi;
	अचिन्हित अक्षर *addr = spi->buffer_addr;
	अचिन्हित अक्षर *data = spi->buffer_data;

	/* spi message consits of:
	 * first byte: ID and operation
	 */

	addr[0] = spi->id | ILI9320_SPI_INDEX | ILI9320_SPI_WRITE;
	addr[1] = reg >> 8;
	addr[2] = reg;

	/* second message is the data to transfer */

	data[0] = spi->id | ILI9320_SPI_DATA  | ILI9320_SPI_WRITE;
	data[1] = value >> 8;
	data[2] = value;

	वापस spi_sync(spi->dev, &spi->message);
पूर्ण

पूर्णांक ili9320_ग_लिखो(काष्ठा ili9320 *ili, अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक value)
अणु
	dev_dbg(ili->dev, "write: reg=%02x, val=%04x\n", reg, value);
	वापस ili->ग_लिखो(ili, reg, value);
पूर्ण
EXPORT_SYMBOL_GPL(ili9320_ग_लिखो);

पूर्णांक ili9320_ग_लिखो_regs(काष्ठा ili9320 *ili,
		       स्थिर काष्ठा ili9320_reg *values,
		       पूर्णांक nr_values)
अणु
	पूर्णांक index;
	पूर्णांक ret;

	क्रम (index = 0; index < nr_values; index++, values++) अणु
		ret = ili9320_ग_लिखो(ili, values->address, values->value);
		अगर (ret != 0)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(ili9320_ग_लिखो_regs);

अटल व्योम ili9320_reset(काष्ठा ili9320 *lcd)
अणु
	काष्ठा ili9320_platdata *cfg = lcd->platdata;

	cfg->reset(1);
	mdelay(50);

	cfg->reset(0);
	mdelay(50);

	cfg->reset(1);
	mdelay(100);
पूर्ण

अटल अंतरभूत पूर्णांक ili9320_init_chip(काष्ठा ili9320 *lcd)
अणु
	पूर्णांक ret;

	ili9320_reset(lcd);

	ret = lcd->client->init(lcd, lcd->platdata);
	अगर (ret != 0) अणु
		dev_err(lcd->dev, "failed to initialise display\n");
		वापस ret;
	पूर्ण

	lcd->initialised = 1;
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक ili9320_घातer_on(काष्ठा ili9320 *lcd)
अणु
	अगर (!lcd->initialised)
		ili9320_init_chip(lcd);

	lcd->display1 |= (ILI9320_DISPLAY1_D(3) | ILI9320_DISPLAY1_BASEE);
	ili9320_ग_लिखो(lcd, ILI9320_DISPLAY1, lcd->display1);

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक ili9320_घातer_off(काष्ठा ili9320 *lcd)
अणु
	lcd->display1 &= ~(ILI9320_DISPLAY1_D(3) | ILI9320_DISPLAY1_BASEE);
	ili9320_ग_लिखो(lcd, ILI9320_DISPLAY1, lcd->display1);

	वापस 0;
पूर्ण

#घोषणा POWER_IS_ON(pwr)	((pwr) <= FB_BLANK_NORMAL)

अटल पूर्णांक ili9320_घातer(काष्ठा ili9320 *lcd, पूर्णांक घातer)
अणु
	पूर्णांक ret = 0;

	dev_dbg(lcd->dev, "power %d => %d\n", lcd->घातer, घातer);

	अगर (POWER_IS_ON(घातer) && !POWER_IS_ON(lcd->घातer))
		ret = ili9320_घातer_on(lcd);
	अन्यथा अगर (!POWER_IS_ON(घातer) && POWER_IS_ON(lcd->घातer))
		ret = ili9320_घातer_off(lcd);

	अगर (ret == 0)
		lcd->घातer = घातer;
	अन्यथा
		dev_warn(lcd->dev, "failed to set power mode %d\n", घातer);

	वापस ret;
पूर्ण

अटल अंतरभूत काष्ठा ili9320 *to_our_lcd(काष्ठा lcd_device *lcd)
अणु
	वापस lcd_get_data(lcd);
पूर्ण

अटल पूर्णांक ili9320_set_घातer(काष्ठा lcd_device *ld, पूर्णांक घातer)
अणु
	काष्ठा ili9320 *lcd = to_our_lcd(ld);

	वापस ili9320_घातer(lcd, घातer);
पूर्ण

अटल पूर्णांक ili9320_get_घातer(काष्ठा lcd_device *ld)
अणु
	काष्ठा ili9320 *lcd = to_our_lcd(ld);

	वापस lcd->घातer;
पूर्ण

अटल काष्ठा lcd_ops ili9320_ops = अणु
	.get_घातer	= ili9320_get_घातer,
	.set_घातer	= ili9320_set_घातer,
पूर्ण;

अटल व्योम ili9320_setup_spi(काष्ठा ili9320 *ili,
					काष्ठा spi_device *dev)
अणु
	काष्ठा ili9320_spi *spi = &ili->access.spi;

	ili->ग_लिखो = ili9320_ग_लिखो_spi;
	spi->dev = dev;

	/* fill the two messages we are going to use to send the data
	 * with, the first the address followed by the data. The datasheet
	 * says they should be करोne as two distinct cycles of the SPI CS line.
	 */

	spi->xfer[0].tx_buf = spi->buffer_addr;
	spi->xfer[1].tx_buf = spi->buffer_data;
	spi->xfer[0].len = 3;
	spi->xfer[1].len = 3;
	spi->xfer[0].bits_per_word = 8;
	spi->xfer[1].bits_per_word = 8;
	spi->xfer[0].cs_change = 1;

	spi_message_init(&spi->message);
	spi_message_add_tail(&spi->xfer[0], &spi->message);
	spi_message_add_tail(&spi->xfer[1], &spi->message);
पूर्ण

पूर्णांक ili9320_probe_spi(काष्ठा spi_device *spi,
				काष्ठा ili9320_client *client)
अणु
	काष्ठा ili9320_platdata *cfg = dev_get_platdata(&spi->dev);
	काष्ठा device *dev = &spi->dev;
	काष्ठा ili9320 *ili;
	काष्ठा lcd_device *lcd;
	पूर्णांक ret = 0;

	/* verअगरy we where given some inक्रमmation */

	अगर (cfg == शून्य) अणु
		dev_err(dev, "no platform data supplied\n");
		वापस -EINVAL;
	पूर्ण

	अगर (cfg->hsize <= 0 || cfg->vsize <= 0 || cfg->reset == शून्य) अणु
		dev_err(dev, "invalid platform data supplied\n");
		वापस -EINVAL;
	पूर्ण

	/* allocate and initialse our state */

	ili = devm_kzalloc(&spi->dev, माप(काष्ठा ili9320), GFP_KERNEL);
	अगर (ili == शून्य)
		वापस -ENOMEM;

	ili->access.spi.id = ILI9320_SPI_IDCODE | ILI9320_SPI_ID(1);

	ili->dev = dev;
	ili->client = client;
	ili->घातer = FB_BLANK_POWERDOWN;
	ili->platdata = cfg;

	spi_set_drvdata(spi, ili);

	ili9320_setup_spi(ili, spi);

	lcd = devm_lcd_device_रेजिस्टर(&spi->dev, "ili9320", dev, ili,
					&ili9320_ops);
	अगर (IS_ERR(lcd)) अणु
		dev_err(dev, "failed to register lcd device\n");
		वापस PTR_ERR(lcd);
	पूर्ण

	ili->lcd = lcd;

	dev_info(dev, "initialising %s\n", client->name);

	ret = ili9320_घातer(ili, FB_BLANK_UNBLANK);
	अगर (ret != 0) अणु
		dev_err(dev, "failed to set lcd power state\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(ili9320_probe_spi);

पूर्णांक ili9320_हटाओ(काष्ठा ili9320 *ili)
अणु
	ili9320_घातer(ili, FB_BLANK_POWERDOWN);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(ili9320_हटाओ);

#अगर_घोषित CONFIG_PM_SLEEP
पूर्णांक ili9320_suspend(काष्ठा ili9320 *lcd)
अणु
	पूर्णांक ret;

	ret = ili9320_घातer(lcd, FB_BLANK_POWERDOWN);

	अगर (lcd->platdata->suspend == ILI9320_SUSPEND_DEEP) अणु
		ili9320_ग_लिखो(lcd, ILI9320_POWER1, lcd->घातer1 |
			      ILI9320_POWER1_SLP |
			      ILI9320_POWER1_DSTB);
		lcd->initialised = 0;
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(ili9320_suspend);

पूर्णांक ili9320_resume(काष्ठा ili9320 *lcd)
अणु
	dev_info(lcd->dev, "resuming from power state %d\n", lcd->घातer);

	अगर (lcd->platdata->suspend == ILI9320_SUSPEND_DEEP)
		ili9320_ग_लिखो(lcd, ILI9320_POWER1, 0x00);

	वापस ili9320_घातer(lcd, FB_BLANK_UNBLANK);
पूर्ण
EXPORT_SYMBOL_GPL(ili9320_resume);
#पूर्ण_अगर

/* Power करोwn all displays on reboot, घातeroff or halt */
व्योम ili9320_shutकरोwn(काष्ठा ili9320 *lcd)
अणु
	ili9320_घातer(lcd, FB_BLANK_POWERDOWN);
पूर्ण
EXPORT_SYMBOL_GPL(ili9320_shutकरोwn);

MODULE_AUTHOR("Ben Dooks <ben-linux@fluff.org>");
MODULE_DESCRIPTION("ILI9320 LCD Driver");
MODULE_LICENSE("GPL v2");
