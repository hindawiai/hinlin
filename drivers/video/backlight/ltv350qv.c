<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Power control क्रम Samsung LTV350QV Quarter VGA LCD Panel
 *
 * Copyright (C) 2006, 2007 Aपंचांगel Corporation
 */
#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/fb.h>
#समावेश <linux/init.h>
#समावेश <linux/lcd.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/spi/spi.h>

#समावेश "ltv350qv.h"

#घोषणा POWER_IS_ON(pwr)	((pwr) <= FB_BLANK_NORMAL)

काष्ठा ltv350qv अणु
	काष्ठा spi_device	*spi;
	u8			*buffer;
	पूर्णांक			घातer;
	काष्ठा lcd_device	*ld;
पूर्ण;

/*
 * The घातer-on and घातer-off sequences are taken from the
 * LTV350QV-F04 data sheet from Samsung. The रेजिस्टर definitions are
 * taken from the S6F2002 command list also from Samsung. Both
 * करोcuments are distributed with the AVR32 Linux BSP CD from Aपंचांगel.
 *
 * There's still some voodoo going on here, but it's a lot better than
 * in the first incarnation of the driver where all we had was the raw
 * numbers from the initialization sequence.
 */
अटल पूर्णांक ltv350qv_ग_लिखो_reg(काष्ठा ltv350qv *lcd, u8 reg, u16 val)
अणु
	काष्ठा spi_message msg;
	काष्ठा spi_transfer index_xfer = अणु
		.len		= 3,
		.cs_change	= 1,
	पूर्ण;
	काष्ठा spi_transfer value_xfer = अणु
		.len		= 3,
	पूर्ण;

	spi_message_init(&msg);

	/* रेजिस्टर index */
	lcd->buffer[0] = LTV_OPC_INDEX;
	lcd->buffer[1] = 0x00;
	lcd->buffer[2] = reg & 0x7f;
	index_xfer.tx_buf = lcd->buffer;
	spi_message_add_tail(&index_xfer, &msg);

	/* रेजिस्टर value */
	lcd->buffer[4] = LTV_OPC_DATA;
	lcd->buffer[5] = val >> 8;
	lcd->buffer[6] = val;
	value_xfer.tx_buf = lcd->buffer + 4;
	spi_message_add_tail(&value_xfer, &msg);

	वापस spi_sync(lcd->spi, &msg);
पूर्ण

/* The comments are taken straight from the data sheet */
अटल पूर्णांक ltv350qv_घातer_on(काष्ठा ltv350qv *lcd)
अणु
	पूर्णांक ret;

	/* Power On Reset Display off State */
	अगर (ltv350qv_ग_लिखो_reg(lcd, LTV_PWRCTL1, 0x0000))
		जाओ err;
	usleep_range(15000, 16000);

	/* Power Setting Function 1 */
	अगर (ltv350qv_ग_लिखो_reg(lcd, LTV_PWRCTL1, LTV_VCOM_DISABLE))
		जाओ err;
	अगर (ltv350qv_ग_लिखो_reg(lcd, LTV_PWRCTL2, LTV_VCOML_ENABLE))
		जाओ err_घातer1;

	/* Power Setting Function 2 */
	अगर (ltv350qv_ग_लिखो_reg(lcd, LTV_PWRCTL1,
			       LTV_VCOM_DISABLE | LTV_DRIVE_CURRENT(5)
			       | LTV_SUPPLY_CURRENT(5)))
		जाओ err_घातer2;

	msleep(55);

	/* Inकाष्ठाion Setting */
	ret = ltv350qv_ग_लिखो_reg(lcd, LTV_IFCTL,
				 LTV_NMD | LTV_REV | LTV_NL(0x1d));
	ret |= ltv350qv_ग_लिखो_reg(lcd, LTV_DATACTL,
				  LTV_DS_SAME | LTV_CHS_480
				  | LTV_DF_RGB | LTV_RGB_BGR);
	ret |= ltv350qv_ग_लिखो_reg(lcd, LTV_ENTRY_MODE,
				  LTV_VSPL_ACTIVE_LOW
				  | LTV_HSPL_ACTIVE_LOW
				  | LTV_DPL_SAMPLE_RISING
				  | LTV_EPL_ACTIVE_LOW
				  | LTV_SS_RIGHT_TO_LEFT);
	ret |= ltv350qv_ग_लिखो_reg(lcd, LTV_GATECTL1, LTV_CLW(3));
	ret |= ltv350qv_ग_लिखो_reg(lcd, LTV_GATECTL2,
				  LTV_NW_INV_1LINE | LTV_FWI(3));
	ret |= ltv350qv_ग_लिखो_reg(lcd, LTV_VBP, 0x000a);
	ret |= ltv350qv_ग_लिखो_reg(lcd, LTV_HBP, 0x0021);
	ret |= ltv350qv_ग_लिखो_reg(lcd, LTV_SOTCTL, LTV_SDT(3) | LTV_EQ(0));
	ret |= ltv350qv_ग_लिखो_reg(lcd, LTV_GAMMA(0), 0x0103);
	ret |= ltv350qv_ग_लिखो_reg(lcd, LTV_GAMMA(1), 0x0301);
	ret |= ltv350qv_ग_लिखो_reg(lcd, LTV_GAMMA(2), 0x1f0f);
	ret |= ltv350qv_ग_लिखो_reg(lcd, LTV_GAMMA(3), 0x1f0f);
	ret |= ltv350qv_ग_लिखो_reg(lcd, LTV_GAMMA(4), 0x0707);
	ret |= ltv350qv_ग_लिखो_reg(lcd, LTV_GAMMA(5), 0x0307);
	ret |= ltv350qv_ग_लिखो_reg(lcd, LTV_GAMMA(6), 0x0707);
	ret |= ltv350qv_ग_लिखो_reg(lcd, LTV_GAMMA(7), 0x0000);
	ret |= ltv350qv_ग_लिखो_reg(lcd, LTV_GAMMA(8), 0x0004);
	ret |= ltv350qv_ग_लिखो_reg(lcd, LTV_GAMMA(9), 0x0000);
	अगर (ret)
		जाओ err_settings;

	/* Wait more than 2 frames */
	msleep(20);

	/* Display On Sequence */
	ret = ltv350qv_ग_लिखो_reg(lcd, LTV_PWRCTL1,
				 LTV_VCOM_DISABLE | LTV_VCOMOUT_ENABLE
				 | LTV_POWER_ON | LTV_DRIVE_CURRENT(5)
				 | LTV_SUPPLY_CURRENT(5));
	ret |= ltv350qv_ग_लिखो_reg(lcd, LTV_GATECTL2,
				  LTV_NW_INV_1LINE | LTV_DSC | LTV_FWI(3));
	अगर (ret)
		जाओ err_disp_on;

	/* Display should now be ON. Phew. */
	वापस 0;

err_disp_on:
	/*
	 * Try to recover. Error handling probably isn't very useful
	 * at this poपूर्णांक, just make a best efक्रमt to चयन the panel
	 * off.
	 */
	ltv350qv_ग_लिखो_reg(lcd, LTV_PWRCTL1,
			   LTV_VCOM_DISABLE | LTV_DRIVE_CURRENT(5)
			   | LTV_SUPPLY_CURRENT(5));
	ltv350qv_ग_लिखो_reg(lcd, LTV_GATECTL2,
			   LTV_NW_INV_1LINE | LTV_FWI(3));
err_settings:
err_घातer2:
err_घातer1:
	ltv350qv_ग_लिखो_reg(lcd, LTV_PWRCTL2, 0x0000);
	usleep_range(1000, 1100);
err:
	ltv350qv_ग_लिखो_reg(lcd, LTV_PWRCTL1, LTV_VCOM_DISABLE);
	वापस -EIO;
पूर्ण

अटल पूर्णांक ltv350qv_घातer_off(काष्ठा ltv350qv *lcd)
अणु
	पूर्णांक ret;

	/* Display Off Sequence */
	ret = ltv350qv_ग_लिखो_reg(lcd, LTV_PWRCTL1,
				 LTV_VCOM_DISABLE
				 | LTV_DRIVE_CURRENT(5)
				 | LTV_SUPPLY_CURRENT(5));
	ret |= ltv350qv_ग_लिखो_reg(lcd, LTV_GATECTL2,
				  LTV_NW_INV_1LINE | LTV_FWI(3));

	/* Power करोwn setting 1 */
	ret |= ltv350qv_ग_लिखो_reg(lcd, LTV_PWRCTL2, 0x0000);

	/* Wait at least 1 ms */
	usleep_range(1000, 1100);

	/* Power करोwn setting 2 */
	ret |= ltv350qv_ग_लिखो_reg(lcd, LTV_PWRCTL1, LTV_VCOM_DISABLE);

	/*
	 * No poपूर्णांक in trying to recover here. If we can't चयन the
	 * panel off, what are we supposed to करो other than inक्रमm the
	 * user about the failure?
	 */
	अगर (ret)
		वापस -EIO;

	/* Display घातer should now be OFF */
	वापस 0;
पूर्ण

अटल पूर्णांक ltv350qv_घातer(काष्ठा ltv350qv *lcd, पूर्णांक घातer)
अणु
	पूर्णांक ret = 0;

	अगर (POWER_IS_ON(घातer) && !POWER_IS_ON(lcd->घातer))
		ret = ltv350qv_घातer_on(lcd);
	अन्यथा अगर (!POWER_IS_ON(घातer) && POWER_IS_ON(lcd->घातer))
		ret = ltv350qv_घातer_off(lcd);

	अगर (!ret)
		lcd->घातer = घातer;

	वापस ret;
पूर्ण

अटल पूर्णांक ltv350qv_set_घातer(काष्ठा lcd_device *ld, पूर्णांक घातer)
अणु
	काष्ठा ltv350qv *lcd = lcd_get_data(ld);

	वापस ltv350qv_घातer(lcd, घातer);
पूर्ण

अटल पूर्णांक ltv350qv_get_घातer(काष्ठा lcd_device *ld)
अणु
	काष्ठा ltv350qv *lcd = lcd_get_data(ld);

	वापस lcd->घातer;
पूर्ण

अटल काष्ठा lcd_ops ltv_ops = अणु
	.get_घातer	= ltv350qv_get_घातer,
	.set_घातer	= ltv350qv_set_घातer,
पूर्ण;

अटल पूर्णांक ltv350qv_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा ltv350qv *lcd;
	काष्ठा lcd_device *ld;
	पूर्णांक ret;

	lcd = devm_kzalloc(&spi->dev, माप(काष्ठा ltv350qv), GFP_KERNEL);
	अगर (!lcd)
		वापस -ENOMEM;

	lcd->spi = spi;
	lcd->घातer = FB_BLANK_POWERDOWN;
	lcd->buffer = devm_kzalloc(&spi->dev, 8, GFP_KERNEL);
	अगर (!lcd->buffer)
		वापस -ENOMEM;

	ld = devm_lcd_device_रेजिस्टर(&spi->dev, "ltv350qv", &spi->dev, lcd,
					&ltv_ops);
	अगर (IS_ERR(ld))
		वापस PTR_ERR(ld);

	lcd->ld = ld;

	ret = ltv350qv_घातer(lcd, FB_BLANK_UNBLANK);
	अगर (ret)
		वापस ret;

	spi_set_drvdata(spi, lcd);

	वापस 0;
पूर्ण

अटल पूर्णांक ltv350qv_हटाओ(काष्ठा spi_device *spi)
अणु
	काष्ठा ltv350qv *lcd = spi_get_drvdata(spi);

	ltv350qv_घातer(lcd, FB_BLANK_POWERDOWN);
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक ltv350qv_suspend(काष्ठा device *dev)
अणु
	काष्ठा ltv350qv *lcd = dev_get_drvdata(dev);

	वापस ltv350qv_घातer(lcd, FB_BLANK_POWERDOWN);
पूर्ण

अटल पूर्णांक ltv350qv_resume(काष्ठा device *dev)
अणु
	काष्ठा ltv350qv *lcd = dev_get_drvdata(dev);

	वापस ltv350qv_घातer(lcd, FB_BLANK_UNBLANK);
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(ltv350qv_pm_ops, ltv350qv_suspend, ltv350qv_resume);

/* Power करोwn all displays on reboot, घातeroff or halt */
अटल व्योम ltv350qv_shutकरोwn(काष्ठा spi_device *spi)
अणु
	काष्ठा ltv350qv *lcd = spi_get_drvdata(spi);

	ltv350qv_घातer(lcd, FB_BLANK_POWERDOWN);
पूर्ण

अटल काष्ठा spi_driver ltv350qv_driver = अणु
	.driver = अणु
		.name		= "ltv350qv",
		.pm		= &ltv350qv_pm_ops,
	पूर्ण,

	.probe		= ltv350qv_probe,
	.हटाओ		= ltv350qv_हटाओ,
	.shutकरोwn	= ltv350qv_shutकरोwn,
पूर्ण;

module_spi_driver(ltv350qv_driver);

MODULE_AUTHOR("Haavard Skinnemoen (Atmel)");
MODULE_DESCRIPTION("Samsung LTV350QV LCD Driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("spi:ltv350qv");
