<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  LCD/Backlight Driver क्रम Sharp Zaurus Handhelds (various models)
 *
 *  Copyright (c) 2004-2006 Riअक्षरd Purdie
 *
 *  Based on Sharp's 2.4 Backlight Driver
 *
 *  Copyright (c) 2008 Marvell International Ltd.
 *	Converted to SPI device based LCD/Backlight device driver
 *	by Eric Miao <eric.miao@marvell.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/fb.h>
#समावेश <linux/lcd.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/spi/corgi_lcd.h>
#समावेश <linux/slab.h>
#समावेश <यंत्र/mach/sharpsl_param.h>

#घोषणा POWER_IS_ON(pwr)	((pwr) <= FB_BLANK_NORMAL)

/* Register Addresses */
#घोषणा RESCTL_ADRS     0x00
#घोषणा PHACTRL_ADRS    0x01
#घोषणा DUTYCTRL_ADRS   0x02
#घोषणा POWERREG0_ADRS  0x03
#घोषणा POWERREG1_ADRS  0x04
#घोषणा GPOR3_ADRS      0x05
#घोषणा PICTRL_ADRS     0x06
#घोषणा POLCTRL_ADRS    0x07

/* Register Bit Definitions */
#घोषणा RESCTL_QVGA     0x01
#घोषणा RESCTL_VGA      0x00

#घोषणा POWER1_VW_ON    0x01  /* VW Supply FET ON */
#घोषणा POWER1_GVSS_ON  0x02  /* GVSS(-8V) Power Supply ON */
#घोषणा POWER1_VDD_ON   0x04  /* VDD(8V),SVSS(-4V) Power Supply ON */

#घोषणा POWER1_VW_OFF   0x00  /* VW Supply FET OFF */
#घोषणा POWER1_GVSS_OFF 0x00  /* GVSS(-8V) Power Supply OFF */
#घोषणा POWER1_VDD_OFF  0x00  /* VDD(8V),SVSS(-4V) Power Supply OFF */

#घोषणा POWER0_COM_DCLK 0x01  /* COM Voltage DC Bias DAC Serial Data Clock */
#घोषणा POWER0_COM_DOUT 0x02  /* COM Voltage DC Bias DAC Serial Data Out */
#घोषणा POWER0_DAC_ON   0x04  /* DAC Power Supply ON */
#घोषणा POWER0_COM_ON   0x08  /* COM Power Supply ON */
#घोषणा POWER0_VCC5_ON  0x10  /* VCC5 Power Supply ON */

#घोषणा POWER0_DAC_OFF  0x00  /* DAC Power Supply OFF */
#घोषणा POWER0_COM_OFF  0x00  /* COM Power Supply OFF */
#घोषणा POWER0_VCC5_OFF 0x00  /* VCC5 Power Supply OFF */

#घोषणा PICTRL_INIT_STATE      0x01
#घोषणा PICTRL_INIOFF          0x02
#घोषणा PICTRL_POWER_DOWN      0x04
#घोषणा PICTRL_COM_SIGNAL_OFF  0x08
#घोषणा PICTRL_DAC_SIGNAL_OFF  0x10

#घोषणा POLCTRL_SYNC_POL_FALL  0x01
#घोषणा POLCTRL_EN_POL_FALL    0x02
#घोषणा POLCTRL_DATA_POL_FALL  0x04
#घोषणा POLCTRL_SYNC_ACT_H     0x08
#घोषणा POLCTRL_EN_ACT_L       0x10

#घोषणा POLCTRL_SYNC_POL_RISE  0x00
#घोषणा POLCTRL_EN_POL_RISE    0x00
#घोषणा POLCTRL_DATA_POL_RISE  0x00
#घोषणा POLCTRL_SYNC_ACT_L     0x00
#घोषणा POLCTRL_EN_ACT_H       0x00

#घोषणा PHACTRL_PHASE_MANUAL   0x01
#घोषणा DEFAULT_PHAD_QVGA     (9)
#घोषणा DEFAULT_COMADJ        (125)

काष्ठा corgi_lcd अणु
	काष्ठा spi_device	*spi_dev;
	काष्ठा lcd_device	*lcd_dev;
	काष्ठा backlight_device	*bl_dev;

	पूर्णांक	limit_mask;
	पूर्णांक	पूर्णांकensity;
	पूर्णांक	घातer;
	पूर्णांक	mode;
	अक्षर	buf[2];

	काष्ठा gpio_desc *backlight_on;
	काष्ठा gpio_desc *backlight_cont;

	व्योम (*kick_battery)(व्योम);
पूर्ण;

अटल पूर्णांक corgi_ssp_lcdtg_send(काष्ठा corgi_lcd *lcd, पूर्णांक reg, uपूर्णांक8_t val);

अटल काष्ठा corgi_lcd *the_corgi_lcd;
अटल अचिन्हित दीर्घ corgibl_flags;
#घोषणा CORGIBL_SUSPENDED     0x01
#घोषणा CORGIBL_BATTLOW       0x02

/*
 * This is only a pseuकरो I2C पूर्णांकerface. We can't use the standard kernel
 * routines as the पूर्णांकerface is ग_लिखो only. We just assume the data is acked...
 */
अटल व्योम lcdtg_ssp_i2c_send(काष्ठा corgi_lcd *lcd, uपूर्णांक8_t data)
अणु
	corgi_ssp_lcdtg_send(lcd, POWERREG0_ADRS, data);
	udelay(10);
पूर्ण

अटल व्योम lcdtg_i2c_send_bit(काष्ठा corgi_lcd *lcd, uपूर्णांक8_t data)
अणु
	lcdtg_ssp_i2c_send(lcd, data);
	lcdtg_ssp_i2c_send(lcd, data | POWER0_COM_DCLK);
	lcdtg_ssp_i2c_send(lcd, data);
पूर्ण

अटल व्योम lcdtg_i2c_send_start(काष्ठा corgi_lcd *lcd, uपूर्णांक8_t base)
अणु
	lcdtg_ssp_i2c_send(lcd, base | POWER0_COM_DCLK | POWER0_COM_DOUT);
	lcdtg_ssp_i2c_send(lcd, base | POWER0_COM_DCLK);
	lcdtg_ssp_i2c_send(lcd, base);
पूर्ण

अटल व्योम lcdtg_i2c_send_stop(काष्ठा corgi_lcd *lcd, uपूर्णांक8_t base)
अणु
	lcdtg_ssp_i2c_send(lcd, base);
	lcdtg_ssp_i2c_send(lcd, base | POWER0_COM_DCLK);
	lcdtg_ssp_i2c_send(lcd, base | POWER0_COM_DCLK | POWER0_COM_DOUT);
पूर्ण

अटल व्योम lcdtg_i2c_send_byte(काष्ठा corgi_lcd *lcd,
				uपूर्णांक8_t base, uपूर्णांक8_t data)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 8; i++) अणु
		अगर (data & 0x80)
			lcdtg_i2c_send_bit(lcd, base | POWER0_COM_DOUT);
		अन्यथा
			lcdtg_i2c_send_bit(lcd, base);
		data <<= 1;
	पूर्ण
पूर्ण

अटल व्योम lcdtg_i2c_रुको_ack(काष्ठा corgi_lcd *lcd, uपूर्णांक8_t base)
अणु
	lcdtg_i2c_send_bit(lcd, base);
पूर्ण

अटल व्योम lcdtg_set_common_voltage(काष्ठा corgi_lcd *lcd,
				     uपूर्णांक8_t base_data, uपूर्णांक8_t data)
अणु
	/* Set Common Voltage to M62332FP via I2C */
	lcdtg_i2c_send_start(lcd, base_data);
	lcdtg_i2c_send_byte(lcd, base_data, 0x9c);
	lcdtg_i2c_रुको_ack(lcd, base_data);
	lcdtg_i2c_send_byte(lcd, base_data, 0x00);
	lcdtg_i2c_रुको_ack(lcd, base_data);
	lcdtg_i2c_send_byte(lcd, base_data, data);
	lcdtg_i2c_रुको_ack(lcd, base_data);
	lcdtg_i2c_send_stop(lcd, base_data);
पूर्ण

अटल पूर्णांक corgi_ssp_lcdtg_send(काष्ठा corgi_lcd *lcd, पूर्णांक adrs, uपूर्णांक8_t data)
अणु
	काष्ठा spi_message msg;
	काष्ठा spi_transfer xfer = अणु
		.len		= 1,
		.cs_change	= 0,
		.tx_buf		= lcd->buf,
	पूर्ण;

	lcd->buf[0] = ((adrs & 0x07) << 5) | (data & 0x1f);
	spi_message_init(&msg);
	spi_message_add_tail(&xfer, &msg);

	वापस spi_sync(lcd->spi_dev, &msg);
पूर्ण

/* Set Phase Adjust */
अटल व्योम lcdtg_set_phadadj(काष्ठा corgi_lcd *lcd, पूर्णांक mode)
अणु
	पूर्णांक adj;

	चयन (mode) अणु
	हाल CORGI_LCD_MODE_VGA:
		/* Setting क्रम VGA */
		adj = sharpsl_param.phadadj;
		adj = (adj < 0) ? PHACTRL_PHASE_MANUAL :
				  PHACTRL_PHASE_MANUAL | ((adj & 0xf) << 1);
		अवरोध;
	हाल CORGI_LCD_MODE_QVGA:
	शेष:
		/* Setting क्रम QVGA */
		adj = (DEFAULT_PHAD_QVGA << 1) | PHACTRL_PHASE_MANUAL;
		अवरोध;
	पूर्ण

	corgi_ssp_lcdtg_send(lcd, PHACTRL_ADRS, adj);
पूर्ण

अटल व्योम corgi_lcd_घातer_on(काष्ठा corgi_lcd *lcd)
अणु
	पूर्णांक comadj;

	/* Initialize Internal Logic & Port */
	corgi_ssp_lcdtg_send(lcd, PICTRL_ADRS,
			PICTRL_POWER_DOWN | PICTRL_INIOFF |
			PICTRL_INIT_STATE | PICTRL_COM_SIGNAL_OFF |
			PICTRL_DAC_SIGNAL_OFF);

	corgi_ssp_lcdtg_send(lcd, POWERREG0_ADRS,
			POWER0_COM_DCLK | POWER0_COM_DOUT | POWER0_DAC_OFF |
			POWER0_COM_OFF | POWER0_VCC5_OFF);

	corgi_ssp_lcdtg_send(lcd, POWERREG1_ADRS,
			POWER1_VW_OFF | POWER1_GVSS_OFF | POWER1_VDD_OFF);

	/* VDD(+8V), SVSS(-4V) ON */
	corgi_ssp_lcdtg_send(lcd, POWERREG1_ADRS,
			POWER1_VW_OFF | POWER1_GVSS_OFF | POWER1_VDD_ON);
	mdelay(3);

	/* DAC ON */
	corgi_ssp_lcdtg_send(lcd, POWERREG0_ADRS,
			POWER0_COM_DCLK | POWER0_COM_DOUT | POWER0_DAC_ON |
			POWER0_COM_OFF | POWER0_VCC5_OFF);

	/* INIB = H, INI = L  */
	/* PICTL[0] = H , PICTL[1] = PICTL[2] = PICTL[4] = L */
	corgi_ssp_lcdtg_send(lcd, PICTRL_ADRS,
			PICTRL_INIT_STATE | PICTRL_COM_SIGNAL_OFF);

	/* Set Common Voltage */
	comadj = sharpsl_param.comadj;
	अगर (comadj < 0)
		comadj = DEFAULT_COMADJ;

	lcdtg_set_common_voltage(lcd, POWER0_DAC_ON | POWER0_COM_OFF |
				 POWER0_VCC5_OFF, comadj);

	/* VCC5 ON, DAC ON */
	corgi_ssp_lcdtg_send(lcd, POWERREG0_ADRS,
			POWER0_COM_DCLK | POWER0_COM_DOUT | POWER0_DAC_ON |
			POWER0_COM_OFF | POWER0_VCC5_ON);

	/* GVSS(-8V) ON, VDD ON */
	corgi_ssp_lcdtg_send(lcd, POWERREG1_ADRS,
			POWER1_VW_OFF | POWER1_GVSS_ON | POWER1_VDD_ON);
	mdelay(2);

	/* COM SIGNAL ON (PICTL[3] = L) */
	corgi_ssp_lcdtg_send(lcd, PICTRL_ADRS, PICTRL_INIT_STATE);

	/* COM ON, DAC ON, VCC5_ON */
	corgi_ssp_lcdtg_send(lcd, POWERREG0_ADRS,
			POWER0_COM_DCLK | POWER0_COM_DOUT | POWER0_DAC_ON |
			POWER0_COM_ON | POWER0_VCC5_ON);

	/* VW ON, GVSS ON, VDD ON */
	corgi_ssp_lcdtg_send(lcd, POWERREG1_ADRS,
			POWER1_VW_ON | POWER1_GVSS_ON | POWER1_VDD_ON);

	/* Signals output enable */
	corgi_ssp_lcdtg_send(lcd, PICTRL_ADRS, 0);

	/* Set Phase Adjust */
	lcdtg_set_phadadj(lcd, lcd->mode);

	/* Initialize क्रम Input Signals from ATI */
	corgi_ssp_lcdtg_send(lcd, POLCTRL_ADRS,
			POLCTRL_SYNC_POL_RISE | POLCTRL_EN_POL_RISE |
			POLCTRL_DATA_POL_RISE | POLCTRL_SYNC_ACT_L |
			POLCTRL_EN_ACT_H);
	udelay(1000);

	चयन (lcd->mode) अणु
	हाल CORGI_LCD_MODE_VGA:
		corgi_ssp_lcdtg_send(lcd, RESCTL_ADRS, RESCTL_VGA);
		अवरोध;
	हाल CORGI_LCD_MODE_QVGA:
	शेष:
		corgi_ssp_lcdtg_send(lcd, RESCTL_ADRS, RESCTL_QVGA);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम corgi_lcd_घातer_off(काष्ठा corgi_lcd *lcd)
अणु
	/* 60Hz x 2 frame = 16.7msec x 2 = 33.4 msec */
	msleep(34);

	/* (1)VW OFF */
	corgi_ssp_lcdtg_send(lcd, POWERREG1_ADRS,
			POWER1_VW_OFF | POWER1_GVSS_ON | POWER1_VDD_ON);

	/* (2)COM OFF */
	corgi_ssp_lcdtg_send(lcd, PICTRL_ADRS, PICTRL_COM_SIGNAL_OFF);
	corgi_ssp_lcdtg_send(lcd, POWERREG0_ADRS,
			POWER0_DAC_ON | POWER0_COM_OFF | POWER0_VCC5_ON);

	/* (3)Set Common Voltage Bias 0V */
	lcdtg_set_common_voltage(lcd, POWER0_DAC_ON | POWER0_COM_OFF |
			POWER0_VCC5_ON, 0);

	/* (4)GVSS OFF */
	corgi_ssp_lcdtg_send(lcd, POWERREG1_ADRS,
			POWER1_VW_OFF | POWER1_GVSS_OFF | POWER1_VDD_ON);

	/* (5)VCC5 OFF */
	corgi_ssp_lcdtg_send(lcd, POWERREG0_ADRS,
			POWER0_DAC_ON | POWER0_COM_OFF | POWER0_VCC5_OFF);

	/* (6)Set PDWN, INIOFF, DACOFF */
	corgi_ssp_lcdtg_send(lcd, PICTRL_ADRS,
			PICTRL_INIOFF | PICTRL_DAC_SIGNAL_OFF |
			PICTRL_POWER_DOWN | PICTRL_COM_SIGNAL_OFF);

	/* (7)DAC OFF */
	corgi_ssp_lcdtg_send(lcd, POWERREG0_ADRS,
			POWER0_DAC_OFF | POWER0_COM_OFF | POWER0_VCC5_OFF);

	/* (8)VDD OFF */
	corgi_ssp_lcdtg_send(lcd, POWERREG1_ADRS,
			POWER1_VW_OFF | POWER1_GVSS_OFF | POWER1_VDD_OFF);
पूर्ण

अटल पूर्णांक corgi_lcd_set_mode(काष्ठा lcd_device *ld, काष्ठा fb_videomode *m)
अणु
	काष्ठा corgi_lcd *lcd = lcd_get_data(ld);
	पूर्णांक mode = CORGI_LCD_MODE_QVGA;

	अगर (m->xres == 640 || m->xres == 480)
		mode = CORGI_LCD_MODE_VGA;

	अगर (lcd->mode == mode)
		वापस 0;

	lcdtg_set_phadadj(lcd, mode);

	चयन (mode) अणु
	हाल CORGI_LCD_MODE_VGA:
		corgi_ssp_lcdtg_send(lcd, RESCTL_ADRS, RESCTL_VGA);
		अवरोध;
	हाल CORGI_LCD_MODE_QVGA:
	शेष:
		corgi_ssp_lcdtg_send(lcd, RESCTL_ADRS, RESCTL_QVGA);
		अवरोध;
	पूर्ण

	lcd->mode = mode;
	वापस 0;
पूर्ण

अटल पूर्णांक corgi_lcd_set_घातer(काष्ठा lcd_device *ld, पूर्णांक घातer)
अणु
	काष्ठा corgi_lcd *lcd = lcd_get_data(ld);

	अगर (POWER_IS_ON(घातer) && !POWER_IS_ON(lcd->घातer))
		corgi_lcd_घातer_on(lcd);

	अगर (!POWER_IS_ON(घातer) && POWER_IS_ON(lcd->घातer))
		corgi_lcd_घातer_off(lcd);

	lcd->घातer = घातer;
	वापस 0;
पूर्ण

अटल पूर्णांक corgi_lcd_get_घातer(काष्ठा lcd_device *ld)
अणु
	काष्ठा corgi_lcd *lcd = lcd_get_data(ld);

	वापस lcd->घातer;
पूर्ण

अटल काष्ठा lcd_ops corgi_lcd_ops = अणु
	.get_घातer	= corgi_lcd_get_घातer,
	.set_घातer	= corgi_lcd_set_घातer,
	.set_mode	= corgi_lcd_set_mode,
पूर्ण;

अटल पूर्णांक corgi_bl_get_पूर्णांकensity(काष्ठा backlight_device *bd)
अणु
	काष्ठा corgi_lcd *lcd = bl_get_data(bd);

	वापस lcd->पूर्णांकensity;
पूर्ण

अटल पूर्णांक corgi_bl_set_पूर्णांकensity(काष्ठा corgi_lcd *lcd, पूर्णांक पूर्णांकensity)
अणु
	पूर्णांक cont;

	अगर (पूर्णांकensity > 0x10)
		पूर्णांकensity += 0x10;

	corgi_ssp_lcdtg_send(lcd, DUTYCTRL_ADRS, पूर्णांकensity);

	/* Bit 5 via GPIO_BACKLIGHT_CONT */
	cont = !!(पूर्णांकensity & 0x20);

	अगर (lcd->backlight_cont)
		gpiod_set_value_cansleep(lcd->backlight_cont, cont);

	अगर (lcd->backlight_on)
		gpiod_set_value_cansleep(lcd->backlight_on, पूर्णांकensity);

	अगर (lcd->kick_battery)
		lcd->kick_battery();

	lcd->पूर्णांकensity = पूर्णांकensity;
	वापस 0;
पूर्ण

अटल पूर्णांक corgi_bl_update_status(काष्ठा backlight_device *bd)
अणु
	काष्ठा corgi_lcd *lcd = bl_get_data(bd);
	पूर्णांक पूर्णांकensity = backlight_get_brightness(bd);

	अगर (corgibl_flags & CORGIBL_SUSPENDED)
		पूर्णांकensity = 0;

	अगर ((corgibl_flags & CORGIBL_BATTLOW) && पूर्णांकensity > lcd->limit_mask)
		पूर्णांकensity = lcd->limit_mask;

	वापस corgi_bl_set_पूर्णांकensity(lcd, पूर्णांकensity);
पूर्ण

व्योम corgi_lcd_limit_पूर्णांकensity(पूर्णांक limit)
अणु
	अगर (limit)
		corgibl_flags |= CORGIBL_BATTLOW;
	अन्यथा
		corgibl_flags &= ~CORGIBL_BATTLOW;

	backlight_update_status(the_corgi_lcd->bl_dev);
पूर्ण
EXPORT_SYMBOL(corgi_lcd_limit_पूर्णांकensity);

अटल स्थिर काष्ठा backlight_ops corgi_bl_ops = अणु
	.get_brightness	= corgi_bl_get_पूर्णांकensity,
	.update_status  = corgi_bl_update_status,
पूर्ण;

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक corgi_lcd_suspend(काष्ठा device *dev)
अणु
	काष्ठा corgi_lcd *lcd = dev_get_drvdata(dev);

	corgibl_flags |= CORGIBL_SUSPENDED;
	corgi_bl_set_पूर्णांकensity(lcd, 0);
	corgi_lcd_set_घातer(lcd->lcd_dev, FB_BLANK_POWERDOWN);
	वापस 0;
पूर्ण

अटल पूर्णांक corgi_lcd_resume(काष्ठा device *dev)
अणु
	काष्ठा corgi_lcd *lcd = dev_get_drvdata(dev);

	corgibl_flags &= ~CORGIBL_SUSPENDED;
	corgi_lcd_set_घातer(lcd->lcd_dev, FB_BLANK_UNBLANK);
	backlight_update_status(lcd->bl_dev);
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(corgi_lcd_pm_ops, corgi_lcd_suspend, corgi_lcd_resume);

अटल पूर्णांक setup_gpio_backlight(काष्ठा corgi_lcd *lcd,
				काष्ठा corgi_lcd_platक्रमm_data *pdata)
अणु
	काष्ठा spi_device *spi = lcd->spi_dev;

	lcd->backlight_on = devm_gpiod_get_optional(&spi->dev,
						    "BL_ON", GPIOD_OUT_LOW);
	अगर (IS_ERR(lcd->backlight_on))
		वापस PTR_ERR(lcd->backlight_on);

	lcd->backlight_cont = devm_gpiod_get_optional(&spi->dev, "BL_CONT",
						      GPIOD_OUT_LOW);
	अगर (IS_ERR(lcd->backlight_cont))
		वापस PTR_ERR(lcd->backlight_cont);

	वापस 0;
पूर्ण

अटल पूर्णांक corgi_lcd_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा backlight_properties props;
	काष्ठा corgi_lcd_platक्रमm_data *pdata = dev_get_platdata(&spi->dev);
	काष्ठा corgi_lcd *lcd;
	पूर्णांक ret = 0;

	अगर (pdata == शून्य) अणु
		dev_err(&spi->dev, "platform data not available\n");
		वापस -EINVAL;
	पूर्ण

	lcd = devm_kzalloc(&spi->dev, माप(काष्ठा corgi_lcd), GFP_KERNEL);
	अगर (!lcd)
		वापस -ENOMEM;

	lcd->spi_dev = spi;

	lcd->lcd_dev = devm_lcd_device_रेजिस्टर(&spi->dev, "corgi_lcd",
						&spi->dev, lcd, &corgi_lcd_ops);
	अगर (IS_ERR(lcd->lcd_dev))
		वापस PTR_ERR(lcd->lcd_dev);

	lcd->घातer = FB_BLANK_POWERDOWN;
	lcd->mode = (pdata) ? pdata->init_mode : CORGI_LCD_MODE_VGA;

	स_रखो(&props, 0, माप(काष्ठा backlight_properties));
	props.type = BACKLIGHT_RAW;
	props.max_brightness = pdata->max_पूर्णांकensity;
	lcd->bl_dev = devm_backlight_device_रेजिस्टर(&spi->dev, "corgi_bl",
						&spi->dev, lcd, &corgi_bl_ops,
						&props);
	अगर (IS_ERR(lcd->bl_dev))
		वापस PTR_ERR(lcd->bl_dev);

	lcd->bl_dev->props.brightness = pdata->शेष_पूर्णांकensity;
	lcd->bl_dev->props.घातer = FB_BLANK_UNBLANK;

	ret = setup_gpio_backlight(lcd, pdata);
	अगर (ret)
		वापस ret;

	lcd->kick_battery = pdata->kick_battery;

	spi_set_drvdata(spi, lcd);
	corgi_lcd_set_घातer(lcd->lcd_dev, FB_BLANK_UNBLANK);
	backlight_update_status(lcd->bl_dev);

	lcd->limit_mask = pdata->limit_mask;
	the_corgi_lcd = lcd;
	वापस 0;
पूर्ण

अटल पूर्णांक corgi_lcd_हटाओ(काष्ठा spi_device *spi)
अणु
	काष्ठा corgi_lcd *lcd = spi_get_drvdata(spi);

	lcd->bl_dev->props.घातer = FB_BLANK_UNBLANK;
	lcd->bl_dev->props.brightness = 0;
	backlight_update_status(lcd->bl_dev);
	corgi_lcd_set_घातer(lcd->lcd_dev, FB_BLANK_POWERDOWN);
	वापस 0;
पूर्ण

अटल काष्ठा spi_driver corgi_lcd_driver = अणु
	.driver		= अणु
		.name	= "corgi-lcd",
		.pm	= &corgi_lcd_pm_ops,
	पूर्ण,
	.probe		= corgi_lcd_probe,
	.हटाओ		= corgi_lcd_हटाओ,
पूर्ण;

module_spi_driver(corgi_lcd_driver);

MODULE_DESCRIPTION("LCD and backlight driver for SHARP C7x0/Cxx00");
MODULE_AUTHOR("Eric Miao <eric.miao@marvell.com>");
MODULE_LICENSE("GPL");
MODULE_ALIAS("spi:corgi-lcd");
