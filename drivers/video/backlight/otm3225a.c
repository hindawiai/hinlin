<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Driver क्रम ORISE Technology OTM3225A SOC क्रम TFT LCD
 * Copyright (C) 2017, EETS GmbH, Felix Brack <fb@ltec.ch>
 *
 * This driver implements a lcd device क्रम the ORISE OTM3225A display
 * controller. The control पूर्णांकerface to the display is SPI and the display's
 * memory is updated over the 16-bit RGB पूर्णांकerface.
 * The मुख्य source of inक्रमmation क्रम writing this driver was provided by the
 * OTM3225A datasheet from ORISE Technology. Some inक्रमmation arise from the
 * ILI9328 datasheet from ILITEK as well as from the datasheets and sample code
 * provided by Crystalfontz America Inc. who sells the CFAF240320A-032T, a 3.2"
 * TFT LC display using the OTM3225A controller.
 */

#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/kernel.h>
#समावेश <linux/lcd.h>
#समावेश <linux/module.h>
#समावेश <linux/spi/spi.h>

#घोषणा OTM3225A_INDEX_REG	0x70
#घोषणा OTM3225A_DATA_REG	0x72

/* inकाष्ठाion रेजिस्टर list */
#घोषणा DRIVER_OUTPUT_CTRL_1	0x01
#घोषणा DRIVER_WAVEFORM_CTRL	0x02
#घोषणा ENTRY_MODE		0x03
#घोषणा SCALING_CTRL		0x04
#घोषणा DISPLAY_CTRL_1		0x07
#घोषणा DISPLAY_CTRL_2		0x08
#घोषणा DISPLAY_CTRL_3		0x09
#घोषणा FRAME_CYCLE_CTRL	0x0A
#घोषणा EXT_DISP_IFACE_CTRL_1	0x0C
#घोषणा FRAME_MAKER_POS		0x0D
#घोषणा EXT_DISP_IFACE_CTRL_2	0x0F
#घोषणा POWER_CTRL_1		0x10
#घोषणा POWER_CTRL_2		0x11
#घोषणा POWER_CTRL_3		0x12
#घोषणा POWER_CTRL_4		0x13
#घोषणा GRAM_ADDR_HORIZ_SET	0x20
#घोषणा GRAM_ADDR_VERT_SET	0x21
#घोषणा GRAM_READ_WRITE		0x22
#घोषणा POWER_CTRL_7		0x29
#घोषणा FRAME_RATE_CTRL		0x2B
#घोषणा GAMMA_CTRL_1		0x30
#घोषणा GAMMA_CTRL_2		0x31
#घोषणा GAMMA_CTRL_3		0x32
#घोषणा GAMMA_CTRL_4		0x35
#घोषणा GAMMA_CTRL_5		0x36
#घोषणा GAMMA_CTRL_6		0x37
#घोषणा GAMMA_CTRL_7		0x38
#घोषणा GAMMA_CTRL_8		0x39
#घोषणा GAMMA_CTRL_9		0x3C
#घोषणा GAMMA_CTRL_10		0x3D
#घोषणा WINDOW_HORIZ_RAM_START	0x50
#घोषणा WINDOW_HORIZ_RAM_END	0x51
#घोषणा WINDOW_VERT_RAM_START	0x52
#घोषणा WINDOW_VERT_RAM_END	0x53
#घोषणा DRIVER_OUTPUT_CTRL_2	0x60
#घोषणा BASE_IMG_DISPLAY_CTRL	0x61
#घोषणा VERT_SCROLL_CTRL	0x6A
#घोषणा PD1_DISPLAY_POS		0x80
#घोषणा PD1_RAM_START		0x81
#घोषणा PD1_RAM_END		0x82
#घोषणा PD2_DISPLAY_POS		0x83
#घोषणा PD2_RAM_START		0x84
#घोषणा PD2_RAM_END		0x85
#घोषणा PANEL_IFACE_CTRL_1	0x90
#घोषणा PANEL_IFACE_CTRL_2	0x92
#घोषणा PANEL_IFACE_CTRL_4	0x95
#घोषणा PANEL_IFACE_CTRL_5	0x97

काष्ठा oपंचांग3225a_data अणु
	काष्ठा spi_device *spi;
	काष्ठा lcd_device *ld;
	पूर्णांक घातer;
पूर्ण;

काष्ठा oपंचांग3225a_spi_inकाष्ठाion अणु
	अचिन्हित अक्षर reg;	/* रेजिस्टर to ग_लिखो */
	अचिन्हित लघु value;	/* data to ग_लिखो to 'reg' */
	अचिन्हित लघु delay;	/* delay in ms after ग_लिखो */
पूर्ण;

अटल काष्ठा oपंचांग3225a_spi_inकाष्ठाion display_init[] = अणु
	अणु DRIVER_OUTPUT_CTRL_1,		0x0000, 0 पूर्ण,
	अणु DRIVER_WAVEFORM_CTRL,		0x0700, 0 पूर्ण,
	अणु ENTRY_MODE,			0x50A0, 0 पूर्ण,
	अणु SCALING_CTRL,			0x0000, 0 पूर्ण,
	अणु DISPLAY_CTRL_2,		0x0606, 0 पूर्ण,
	अणु DISPLAY_CTRL_3,		0x0000, 0 पूर्ण,
	अणु FRAME_CYCLE_CTRL,		0x0000, 0 पूर्ण,
	अणु EXT_DISP_IFACE_CTRL_1,	0x0000, 0 पूर्ण,
	अणु FRAME_MAKER_POS,		0x0000, 0 पूर्ण,
	अणु EXT_DISP_IFACE_CTRL_2,	0x0002, 0 पूर्ण,
	अणु POWER_CTRL_2,			0x0007, 0 पूर्ण,
	अणु POWER_CTRL_3,			0x0000, 0 पूर्ण,
	अणु POWER_CTRL_4,			0x0000, 200 पूर्ण,
	अणु DISPLAY_CTRL_1,		0x0101, 0 पूर्ण,
	अणु POWER_CTRL_1,			0x12B0, 0 पूर्ण,
	अणु POWER_CTRL_2,			0x0007, 0 पूर्ण,
	अणु POWER_CTRL_3,			0x01BB, 50 पूर्ण,
	अणु POWER_CTRL_4,			0x0013, 0 पूर्ण,
	अणु POWER_CTRL_7,			0x0010, 50 पूर्ण,
	अणु GAMMA_CTRL_1,			0x000A, 0 पूर्ण,
	अणु GAMMA_CTRL_2,			0x1326, 0 पूर्ण,
	अणु GAMMA_CTRL_3,			0x0A29, 0 पूर्ण,
	अणु GAMMA_CTRL_4,			0x0A0A, 0 पूर्ण,
	अणु GAMMA_CTRL_5,			0x1E03, 0 पूर्ण,
	अणु GAMMA_CTRL_6,			0x031E, 0 पूर्ण,
	अणु GAMMA_CTRL_7,			0x0706, 0 पूर्ण,
	अणु GAMMA_CTRL_8,			0x0303, 0 पूर्ण,
	अणु GAMMA_CTRL_9,			0x010E, 0 पूर्ण,
	अणु GAMMA_CTRL_10,		0x040E, 0 पूर्ण,
	अणु WINDOW_HORIZ_RAM_START,	0x0000, 0 पूर्ण,
	अणु WINDOW_HORIZ_RAM_END,		0x00EF, 0 पूर्ण,
	अणु WINDOW_VERT_RAM_START,	0x0000, 0 पूर्ण,
	अणु WINDOW_VERT_RAM_END,		0x013F, 0 पूर्ण,
	अणु DRIVER_OUTPUT_CTRL_2,		0x2700, 0 पूर्ण,
	अणु BASE_IMG_DISPLAY_CTRL,	0x0001, 0 पूर्ण,
	अणु VERT_SCROLL_CTRL,		0x0000, 0 पूर्ण,
	अणु PD1_DISPLAY_POS,		0x0000, 0 पूर्ण,
	अणु PD1_RAM_START,		0x0000, 0 पूर्ण,
	अणु PD1_RAM_END,			0x0000, 0 पूर्ण,
	अणु PD2_DISPLAY_POS,		0x0000, 0 पूर्ण,
	अणु PD2_RAM_START,		0x0000, 0 पूर्ण,
	अणु PD2_RAM_END,			0x0000, 0 पूर्ण,
	अणु PANEL_IFACE_CTRL_1,		0x0010, 0 पूर्ण,
	अणु PANEL_IFACE_CTRL_2,		0x0000, 0 पूर्ण,
	अणु PANEL_IFACE_CTRL_4,		0x0210, 0 पूर्ण,
	अणु PANEL_IFACE_CTRL_5,		0x0000, 0 पूर्ण,
	अणु DISPLAY_CTRL_1,		0x0133, 0 पूर्ण,
पूर्ण;

अटल काष्ठा oपंचांग3225a_spi_inकाष्ठाion display_enable_rgb_पूर्णांकerface[] = अणु
	अणु ENTRY_MODE,			0x1080, 0 पूर्ण,
	अणु GRAM_ADDR_HORIZ_SET,		0x0000, 0 पूर्ण,
	अणु GRAM_ADDR_VERT_SET,		0x0000, 0 पूर्ण,
	अणु EXT_DISP_IFACE_CTRL_1,	0x0111, 500 पूर्ण,
पूर्ण;

अटल काष्ठा oपंचांग3225a_spi_inकाष्ठाion display_off[] = अणु
	अणु DISPLAY_CTRL_1,	0x0131, 100 पूर्ण,
	अणु DISPLAY_CTRL_1,	0x0130, 100 पूर्ण,
	अणु DISPLAY_CTRL_1,	0x0100, 0 पूर्ण,
	अणु POWER_CTRL_1,		0x0280, 0 पूर्ण,
	अणु POWER_CTRL_3,		0x018B, 0 पूर्ण,
पूर्ण;

अटल काष्ठा oपंचांग3225a_spi_inकाष्ठाion display_on[] = अणु
	अणु POWER_CTRL_1,		0x1280, 0 पूर्ण,
	अणु DISPLAY_CTRL_1,	0x0101, 100 पूर्ण,
	अणु DISPLAY_CTRL_1,	0x0121, 0 पूर्ण,
	अणु DISPLAY_CTRL_1,	0x0123, 100 पूर्ण,
	अणु DISPLAY_CTRL_1,	0x0133, 10 पूर्ण,
पूर्ण;

अटल व्योम oपंचांग3225a_ग_लिखो(काष्ठा spi_device *spi,
			   काष्ठा oपंचांग3225a_spi_inकाष्ठाion *inकाष्ठाion,
			   अचिन्हित पूर्णांक count)
अणु
	अचिन्हित अक्षर buf[3];

	जबतक (count--) अणु
		/* address रेजिस्टर using index रेजिस्टर */
		buf[0] = OTM3225A_INDEX_REG;
		buf[1] = 0x00;
		buf[2] = inकाष्ठाion->reg;
		spi_ग_लिखो(spi, buf, 3);

		/* ग_लिखो data to addressed रेजिस्टर */
		buf[0] = OTM3225A_DATA_REG;
		buf[1] = (inकाष्ठाion->value >> 8) & 0xff;
		buf[2] = inकाष्ठाion->value & 0xff;
		spi_ग_लिखो(spi, buf, 3);

		/* execute delay अगर any */
		अगर (inकाष्ठाion->delay)
			msleep(inकाष्ठाion->delay);
		inकाष्ठाion++;
	पूर्ण
पूर्ण

अटल पूर्णांक oपंचांग3225a_set_घातer(काष्ठा lcd_device *ld, पूर्णांक घातer)
अणु
	काष्ठा oपंचांग3225a_data *dd = lcd_get_data(ld);

	अगर (घातer == dd->घातer)
		वापस 0;

	अगर (घातer > FB_BLANK_UNBLANK)
		oपंचांग3225a_ग_लिखो(dd->spi, display_off, ARRAY_SIZE(display_off));
	अन्यथा
		oपंचांग3225a_ग_लिखो(dd->spi, display_on, ARRAY_SIZE(display_on));
	dd->घातer = घातer;

	वापस 0;
पूर्ण

अटल पूर्णांक oपंचांग3225a_get_घातer(काष्ठा lcd_device *ld)
अणु
	काष्ठा oपंचांग3225a_data *dd = lcd_get_data(ld);

	वापस dd->घातer;
पूर्ण

अटल काष्ठा lcd_ops oपंचांग3225a_ops = अणु
	.set_घातer = oपंचांग3225a_set_घातer,
	.get_घातer = oपंचांग3225a_get_घातer,
पूर्ण;

अटल पूर्णांक oपंचांग3225a_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा oपंचांग3225a_data *dd;
	काष्ठा lcd_device *ld;
	काष्ठा device *dev = &spi->dev;

	dd = devm_kzalloc(dev, माप(काष्ठा oपंचांग3225a_data), GFP_KERNEL);
	अगर (dd == शून्य)
		वापस -ENOMEM;

	ld = devm_lcd_device_रेजिस्टर(dev, dev_name(dev), dev, dd,
				      &oपंचांग3225a_ops);
	अगर (IS_ERR(ld))
		वापस PTR_ERR(ld);

	dd->spi = spi;
	dd->ld = ld;
	dev_set_drvdata(dev, dd);

	dev_info(dev, "Initializing and switching to RGB interface");
	oपंचांग3225a_ग_लिखो(spi, display_init, ARRAY_SIZE(display_init));
	oपंचांग3225a_ग_लिखो(spi, display_enable_rgb_पूर्णांकerface,
		       ARRAY_SIZE(display_enable_rgb_पूर्णांकerface));
	वापस 0;
पूर्ण

अटल काष्ठा spi_driver oपंचांग3225a_driver = अणु
	.driver = अणु
		.name = "otm3225a",
		.owner = THIS_MODULE,
	पूर्ण,
	.probe = oपंचांग3225a_probe,
पूर्ण;

module_spi_driver(oपंचांग3225a_driver);

MODULE_AUTHOR("Felix Brack <fb@ltec.ch>");
MODULE_DESCRIPTION("OTM3225A TFT LCD driver");
MODULE_VERSION("1.0.0");
MODULE_LICENSE("GPL v2");
