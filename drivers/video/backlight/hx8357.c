<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Driver क्रम the Himax HX-8357 LCD Controller
 *
 * Copyright 2012 Free Electrons
 */

#समावेश <linux/delay.h>
#समावेश <linux/lcd.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_gpपन.स>
#समावेश <linux/spi/spi.h>

#घोषणा HX8357_NUM_IM_PINS	3

#घोषणा HX8357_SWRESET			0x01
#घोषणा HX8357_GET_RED_CHANNEL		0x06
#घोषणा HX8357_GET_GREEN_CHANNEL	0x07
#घोषणा HX8357_GET_BLUE_CHANNEL		0x08
#घोषणा HX8357_GET_POWER_MODE		0x0a
#घोषणा HX8357_GET_MADCTL		0x0b
#घोषणा HX8357_GET_PIXEL_FORMAT		0x0c
#घोषणा HX8357_GET_DISPLAY_MODE		0x0d
#घोषणा HX8357_GET_SIGNAL_MODE		0x0e
#घोषणा HX8357_GET_DIAGNOSTIC_RESULT	0x0f
#घोषणा HX8357_ENTER_SLEEP_MODE		0x10
#घोषणा HX8357_EXIT_SLEEP_MODE		0x11
#घोषणा HX8357_ENTER_PARTIAL_MODE	0x12
#घोषणा HX8357_ENTER_NORMAL_MODE	0x13
#घोषणा HX8357_EXIT_INVERSION_MODE	0x20
#घोषणा HX8357_ENTER_INVERSION_MODE	0x21
#घोषणा HX8357_SET_DISPLAY_OFF		0x28
#घोषणा HX8357_SET_DISPLAY_ON		0x29
#घोषणा HX8357_SET_COLUMN_ADDRESS	0x2a
#घोषणा HX8357_SET_PAGE_ADDRESS		0x2b
#घोषणा HX8357_WRITE_MEMORY_START	0x2c
#घोषणा HX8357_READ_MEMORY_START	0x2e
#घोषणा HX8357_SET_PARTIAL_AREA		0x30
#घोषणा HX8357_SET_SCROLL_AREA		0x33
#घोषणा HX8357_SET_TEAR_OFF		0x34
#घोषणा HX8357_SET_TEAR_ON		0x35
#घोषणा HX8357_SET_ADDRESS_MODE		0x36
#घोषणा HX8357_SET_SCROLL_START		0x37
#घोषणा HX8357_EXIT_IDLE_MODE		0x38
#घोषणा HX8357_ENTER_IDLE_MODE		0x39
#घोषणा HX8357_SET_PIXEL_FORMAT		0x3a
#घोषणा HX8357_SET_PIXEL_FORMAT_DBI_3BIT	(0x1)
#घोषणा HX8357_SET_PIXEL_FORMAT_DBI_16BIT	(0x5)
#घोषणा HX8357_SET_PIXEL_FORMAT_DBI_18BIT	(0x6)
#घोषणा HX8357_SET_PIXEL_FORMAT_DPI_3BIT	(0x1 << 4)
#घोषणा HX8357_SET_PIXEL_FORMAT_DPI_16BIT	(0x5 << 4)
#घोषणा HX8357_SET_PIXEL_FORMAT_DPI_18BIT	(0x6 << 4)
#घोषणा HX8357_WRITE_MEMORY_CONTINUE	0x3c
#घोषणा HX8357_READ_MEMORY_CONTINUE	0x3e
#घोषणा HX8357_SET_TEAR_SCAN_LINES	0x44
#घोषणा HX8357_GET_SCAN_LINES		0x45
#घोषणा HX8357_READ_DDB_START		0xa1
#घोषणा HX8357_SET_DISPLAY_MODE		0xb4
#घोषणा HX8357_SET_DISPLAY_MODE_RGB_THROUGH	(0x3)
#घोषणा HX8357_SET_DISPLAY_MODE_RGB_INTERFACE	(1 << 4)
#घोषणा HX8357_SET_PANEL_DRIVING	0xc0
#घोषणा HX8357_SET_DISPLAY_FRAME	0xc5
#घोषणा HX8357_SET_RGB			0xc6
#घोषणा HX8357_SET_RGB_ENABLE_HIGH		(1 << 1)
#घोषणा HX8357_SET_GAMMA		0xc8
#घोषणा HX8357_SET_POWER		0xd0
#घोषणा HX8357_SET_VCOM			0xd1
#घोषणा HX8357_SET_POWER_NORMAL		0xd2
#घोषणा HX8357_SET_PANEL_RELATED	0xe9

#घोषणा HX8369_SET_DISPLAY_BRIGHTNESS		0x51
#घोषणा HX8369_WRITE_CABC_DISPLAY_VALUE		0x53
#घोषणा HX8369_WRITE_CABC_BRIGHT_CTRL		0x55
#घोषणा HX8369_WRITE_CABC_MIN_BRIGHTNESS	0x5e
#घोषणा HX8369_SET_POWER			0xb1
#घोषणा HX8369_SET_DISPLAY_MODE			0xb2
#घोषणा HX8369_SET_DISPLAY_WAVEFORM_CYC		0xb4
#घोषणा HX8369_SET_VCOM				0xb6
#घोषणा HX8369_SET_EXTENSION_COMMAND		0xb9
#घोषणा HX8369_SET_GIP				0xd5
#घोषणा HX8369_SET_GAMMA_CURVE_RELATED		0xe0

काष्ठा hx8357_data अणु
	अचिन्हित		im_pins[HX8357_NUM_IM_PINS];
	अचिन्हित		reset;
	काष्ठा spi_device	*spi;
	पूर्णांक			state;
	bool			use_im_pins;
पूर्ण;

अटल u8 hx8357_seq_घातer[] = अणु
	HX8357_SET_POWER, 0x44, 0x41, 0x06,
पूर्ण;

अटल u8 hx8357_seq_vcom[] = अणु
	HX8357_SET_VCOM, 0x40, 0x10,
पूर्ण;

अटल u8 hx8357_seq_घातer_normal[] = अणु
	HX8357_SET_POWER_NORMAL, 0x05, 0x12,
पूर्ण;

अटल u8 hx8357_seq_panel_driving[] = अणु
	HX8357_SET_PANEL_DRIVING, 0x14, 0x3b, 0x00, 0x02, 0x11,
पूर्ण;

अटल u8 hx8357_seq_display_frame[] = अणु
	HX8357_SET_DISPLAY_FRAME, 0x0c,
पूर्ण;

अटल u8 hx8357_seq_panel_related[] = अणु
	HX8357_SET_PANEL_RELATED, 0x01,
पूर्ण;

अटल u8 hx8357_seq_undefined1[] = अणु
	0xea, 0x03, 0x00, 0x00,
पूर्ण;

अटल u8 hx8357_seq_undefined2[] = अणु
	0xeb, 0x40, 0x54, 0x26, 0xdb,
पूर्ण;

अटल u8 hx8357_seq_gamma[] = अणु
	HX8357_SET_GAMMA, 0x00, 0x15, 0x00, 0x22, 0x00,
	0x08, 0x77, 0x26, 0x77, 0x22, 0x04, 0x00,
पूर्ण;

अटल u8 hx8357_seq_address_mode[] = अणु
	HX8357_SET_ADDRESS_MODE, 0xc0,
पूर्ण;

अटल u8 hx8357_seq_pixel_क्रमmat[] = अणु
	HX8357_SET_PIXEL_FORMAT,
	HX8357_SET_PIXEL_FORMAT_DPI_18BIT |
	HX8357_SET_PIXEL_FORMAT_DBI_18BIT,
पूर्ण;

अटल u8 hx8357_seq_column_address[] = अणु
	HX8357_SET_COLUMN_ADDRESS, 0x00, 0x00, 0x01, 0x3f,
पूर्ण;

अटल u8 hx8357_seq_page_address[] = अणु
	HX8357_SET_PAGE_ADDRESS, 0x00, 0x00, 0x01, 0xdf,
पूर्ण;

अटल u8 hx8357_seq_rgb[] = अणु
	HX8357_SET_RGB, 0x02,
पूर्ण;

अटल u8 hx8357_seq_display_mode[] = अणु
	HX8357_SET_DISPLAY_MODE,
	HX8357_SET_DISPLAY_MODE_RGB_THROUGH |
	HX8357_SET_DISPLAY_MODE_RGB_INTERFACE,
पूर्ण;

अटल u8 hx8369_seq_ग_लिखो_CABC_min_brightness[] = अणु
	HX8369_WRITE_CABC_MIN_BRIGHTNESS, 0x00,
पूर्ण;

अटल u8 hx8369_seq_ग_लिखो_CABC_control[] = अणु
	HX8369_WRITE_CABC_DISPLAY_VALUE, 0x24,
पूर्ण;

अटल u8 hx8369_seq_set_display_brightness[] = अणु
	HX8369_SET_DISPLAY_BRIGHTNESS, 0xFF,
पूर्ण;

अटल u8 hx8369_seq_ग_लिखो_CABC_control_setting[] = अणु
	HX8369_WRITE_CABC_BRIGHT_CTRL, 0x02,
पूर्ण;

अटल u8 hx8369_seq_extension_command[] = अणु
	HX8369_SET_EXTENSION_COMMAND, 0xff, 0x83, 0x69,
पूर्ण;

अटल u8 hx8369_seq_display_related[] = अणु
	HX8369_SET_DISPLAY_MODE, 0x00, 0x2b, 0x03, 0x03, 0x70, 0x00,
	0xff, 0x00, 0x00, 0x00, 0x00, 0x03, 0x03, 0x00,	0x01,
पूर्ण;

अटल u8 hx8369_seq_panel_waveक्रमm_cycle[] = अणु
	HX8369_SET_DISPLAY_WAVEFORM_CYC, 0x0a, 0x1d, 0x80, 0x06, 0x02,
पूर्ण;

अटल u8 hx8369_seq_set_address_mode[] = अणु
	HX8357_SET_ADDRESS_MODE, 0x00,
पूर्ण;

अटल u8 hx8369_seq_vcom[] = अणु
	HX8369_SET_VCOM, 0x3e, 0x3e,
पूर्ण;

अटल u8 hx8369_seq_gip[] = अणु
	HX8369_SET_GIP, 0x00, 0x01, 0x03, 0x25, 0x01, 0x02, 0x28, 0x70,
	0x11, 0x13, 0x00, 0x00, 0x40, 0x26, 0x51, 0x37, 0x00, 0x00, 0x71,
	0x35, 0x60, 0x24, 0x07, 0x0f, 0x04, 0x04,
पूर्ण;

अटल u8 hx8369_seq_घातer[] = अणु
	HX8369_SET_POWER, 0x01, 0x00, 0x34, 0x03, 0x00, 0x11, 0x11, 0x32,
	0x2f, 0x3f, 0x3f, 0x01, 0x3a, 0x01, 0xe6, 0xe6, 0xe6, 0xe6, 0xe6,
पूर्ण;

अटल u8 hx8369_seq_gamma_curve_related[] = अणु
	HX8369_SET_GAMMA_CURVE_RELATED, 0x00, 0x0d, 0x19, 0x2f, 0x3b, 0x3d,
	0x2e, 0x4a, 0x08, 0x0e, 0x0f, 0x14, 0x16, 0x14, 0x14, 0x14, 0x1e,
	0x00, 0x0d, 0x19, 0x2f, 0x3b, 0x3d, 0x2e, 0x4a, 0x08, 0x0e, 0x0f,
	0x14, 0x16, 0x14, 0x14, 0x14, 0x1e,
पूर्ण;

अटल पूर्णांक hx8357_spi_ग_लिखो_then_पढ़ो(काष्ठा lcd_device *lcdev,
				u8 *txbuf, u16 txlen,
				u8 *rxbuf, u16 rxlen)
अणु
	काष्ठा hx8357_data *lcd = lcd_get_data(lcdev);
	काष्ठा spi_message msg;
	काष्ठा spi_transfer xfer[2];
	u16 *local_txbuf = शून्य;
	पूर्णांक ret = 0;

	स_रखो(xfer, 0, माप(xfer));
	spi_message_init(&msg);

	अगर (txlen) अणु
		पूर्णांक i;

		local_txbuf = kसुस्मृति(txlen, माप(*local_txbuf), GFP_KERNEL);

		अगर (!local_txbuf)
			वापस -ENOMEM;

		क्रम (i = 0; i < txlen; i++) अणु
			local_txbuf[i] = txbuf[i];
			अगर (i > 0)
				local_txbuf[i] |= 1 << 8;
		पूर्ण

		xfer[0].len = 2 * txlen;
		xfer[0].bits_per_word = 9;
		xfer[0].tx_buf = local_txbuf;
		spi_message_add_tail(&xfer[0], &msg);
	पूर्ण

	अगर (rxlen) अणु
		xfer[1].len = rxlen;
		xfer[1].bits_per_word = 8;
		xfer[1].rx_buf = rxbuf;
		spi_message_add_tail(&xfer[1], &msg);
	पूर्ण

	ret = spi_sync(lcd->spi, &msg);
	अगर (ret < 0)
		dev_err(&lcdev->dev, "Couldn't send SPI data\n");

	अगर (txlen)
		kमुक्त(local_txbuf);

	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक hx8357_spi_ग_लिखो_array(काष्ठा lcd_device *lcdev,
					u8 *value, u8 len)
अणु
	वापस hx8357_spi_ग_लिखो_then_पढ़ो(lcdev, value, len, शून्य, 0);
पूर्ण

अटल अंतरभूत पूर्णांक hx8357_spi_ग_लिखो_byte(काष्ठा lcd_device *lcdev,
					u8 value)
अणु
	वापस hx8357_spi_ग_लिखो_then_पढ़ो(lcdev, &value, 1, शून्य, 0);
पूर्ण

अटल पूर्णांक hx8357_enter_standby(काष्ठा lcd_device *lcdev)
अणु
	पूर्णांक ret;

	ret = hx8357_spi_ग_लिखो_byte(lcdev, HX8357_SET_DISPLAY_OFF);
	अगर (ret < 0)
		वापस ret;

	usleep_range(10000, 12000);

	ret = hx8357_spi_ग_लिखो_byte(lcdev, HX8357_ENTER_SLEEP_MODE);
	अगर (ret < 0)
		वापस ret;

	/*
	 * The controller needs 120ms when entering in sleep mode beक्रमe we can
	 * send the command to go off sleep mode
	 */
	msleep(120);

	वापस 0;
पूर्ण

अटल पूर्णांक hx8357_निकास_standby(काष्ठा lcd_device *lcdev)
अणु
	पूर्णांक ret;

	ret = hx8357_spi_ग_लिखो_byte(lcdev, HX8357_EXIT_SLEEP_MODE);
	अगर (ret < 0)
		वापस ret;

	/*
	 * The controller needs 120ms when निकासing from sleep mode beक्रमe we
	 * can send the command to enter in sleep mode
	 */
	msleep(120);

	ret = hx8357_spi_ग_लिखो_byte(lcdev, HX8357_SET_DISPLAY_ON);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

अटल व्योम hx8357_lcd_reset(काष्ठा lcd_device *lcdev)
अणु
	काष्ठा hx8357_data *lcd = lcd_get_data(lcdev);

	/* Reset the screen */
	gpio_set_value(lcd->reset, 1);
	usleep_range(10000, 12000);
	gpio_set_value(lcd->reset, 0);
	usleep_range(10000, 12000);
	gpio_set_value(lcd->reset, 1);

	/* The controller needs 120ms to recover from reset */
	msleep(120);
पूर्ण

अटल पूर्णांक hx8357_lcd_init(काष्ठा lcd_device *lcdev)
अणु
	काष्ठा hx8357_data *lcd = lcd_get_data(lcdev);
	पूर्णांक ret;

	/*
	 * Set the पूर्णांकerface selection pins to SPI mode, with three
	 * wires
	 */
	अगर (lcd->use_im_pins) अणु
		gpio_set_value_cansleep(lcd->im_pins[0], 1);
		gpio_set_value_cansleep(lcd->im_pins[1], 0);
		gpio_set_value_cansleep(lcd->im_pins[2], 1);
	पूर्ण

	ret = hx8357_spi_ग_लिखो_array(lcdev, hx8357_seq_घातer,
				ARRAY_SIZE(hx8357_seq_घातer));
	अगर (ret < 0)
		वापस ret;

	ret = hx8357_spi_ग_लिखो_array(lcdev, hx8357_seq_vcom,
				ARRAY_SIZE(hx8357_seq_vcom));
	अगर (ret < 0)
		वापस ret;

	ret = hx8357_spi_ग_लिखो_array(lcdev, hx8357_seq_घातer_normal,
				ARRAY_SIZE(hx8357_seq_घातer_normal));
	अगर (ret < 0)
		वापस ret;

	ret = hx8357_spi_ग_लिखो_array(lcdev, hx8357_seq_panel_driving,
				ARRAY_SIZE(hx8357_seq_panel_driving));
	अगर (ret < 0)
		वापस ret;

	ret = hx8357_spi_ग_लिखो_array(lcdev, hx8357_seq_display_frame,
				ARRAY_SIZE(hx8357_seq_display_frame));
	अगर (ret < 0)
		वापस ret;

	ret = hx8357_spi_ग_लिखो_array(lcdev, hx8357_seq_panel_related,
				ARRAY_SIZE(hx8357_seq_panel_related));
	अगर (ret < 0)
		वापस ret;

	ret = hx8357_spi_ग_लिखो_array(lcdev, hx8357_seq_undefined1,
				ARRAY_SIZE(hx8357_seq_undefined1));
	अगर (ret < 0)
		वापस ret;

	ret = hx8357_spi_ग_लिखो_array(lcdev, hx8357_seq_undefined2,
				ARRAY_SIZE(hx8357_seq_undefined2));
	अगर (ret < 0)
		वापस ret;

	ret = hx8357_spi_ग_लिखो_array(lcdev, hx8357_seq_gamma,
				ARRAY_SIZE(hx8357_seq_gamma));
	अगर (ret < 0)
		वापस ret;

	ret = hx8357_spi_ग_लिखो_array(lcdev, hx8357_seq_address_mode,
				ARRAY_SIZE(hx8357_seq_address_mode));
	अगर (ret < 0)
		वापस ret;

	ret = hx8357_spi_ग_लिखो_array(lcdev, hx8357_seq_pixel_क्रमmat,
				ARRAY_SIZE(hx8357_seq_pixel_क्रमmat));
	अगर (ret < 0)
		वापस ret;

	ret = hx8357_spi_ग_लिखो_array(lcdev, hx8357_seq_column_address,
				ARRAY_SIZE(hx8357_seq_column_address));
	अगर (ret < 0)
		वापस ret;

	ret = hx8357_spi_ग_लिखो_array(lcdev, hx8357_seq_page_address,
				ARRAY_SIZE(hx8357_seq_page_address));
	अगर (ret < 0)
		वापस ret;

	ret = hx8357_spi_ग_लिखो_array(lcdev, hx8357_seq_rgb,
				ARRAY_SIZE(hx8357_seq_rgb));
	अगर (ret < 0)
		वापस ret;

	ret = hx8357_spi_ग_लिखो_array(lcdev, hx8357_seq_display_mode,
				ARRAY_SIZE(hx8357_seq_display_mode));
	अगर (ret < 0)
		वापस ret;

	ret = hx8357_spi_ग_लिखो_byte(lcdev, HX8357_EXIT_SLEEP_MODE);
	अगर (ret < 0)
		वापस ret;

	/*
	 * The controller needs 120ms to fully recover from निकासing sleep mode
	 */
	msleep(120);

	ret = hx8357_spi_ग_लिखो_byte(lcdev, HX8357_SET_DISPLAY_ON);
	अगर (ret < 0)
		वापस ret;

	usleep_range(5000, 7000);

	ret = hx8357_spi_ग_लिखो_byte(lcdev, HX8357_WRITE_MEMORY_START);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक hx8369_lcd_init(काष्ठा lcd_device *lcdev)
अणु
	पूर्णांक ret;

	ret = hx8357_spi_ग_लिखो_array(lcdev, hx8369_seq_extension_command,
				ARRAY_SIZE(hx8369_seq_extension_command));
	अगर (ret < 0)
		वापस ret;
	usleep_range(10000, 12000);

	ret = hx8357_spi_ग_लिखो_array(lcdev, hx8369_seq_display_related,
				ARRAY_SIZE(hx8369_seq_display_related));
	अगर (ret < 0)
		वापस ret;

	ret = hx8357_spi_ग_लिखो_array(lcdev, hx8369_seq_panel_waveक्रमm_cycle,
				ARRAY_SIZE(hx8369_seq_panel_waveक्रमm_cycle));
	अगर (ret < 0)
		वापस ret;

	ret = hx8357_spi_ग_लिखो_array(lcdev, hx8369_seq_set_address_mode,
				ARRAY_SIZE(hx8369_seq_set_address_mode));
	अगर (ret < 0)
		वापस ret;

	ret = hx8357_spi_ग_लिखो_array(lcdev, hx8369_seq_vcom,
				ARRAY_SIZE(hx8369_seq_vcom));
	अगर (ret < 0)
		वापस ret;

	ret = hx8357_spi_ग_लिखो_array(lcdev, hx8369_seq_gip,
				ARRAY_SIZE(hx8369_seq_gip));
	अगर (ret < 0)
		वापस ret;

	ret = hx8357_spi_ग_लिखो_array(lcdev, hx8369_seq_घातer,
				ARRAY_SIZE(hx8369_seq_घातer));
	अगर (ret < 0)
		वापस ret;

	ret = hx8357_spi_ग_लिखो_byte(lcdev, HX8357_EXIT_SLEEP_MODE);
	अगर (ret < 0)
		वापस ret;

	/*
	 * The controller needs 120ms to fully recover from निकासing sleep mode
	 */
	msleep(120);

	ret = hx8357_spi_ग_लिखो_array(lcdev, hx8369_seq_gamma_curve_related,
				ARRAY_SIZE(hx8369_seq_gamma_curve_related));
	अगर (ret < 0)
		वापस ret;

	ret = hx8357_spi_ग_लिखो_byte(lcdev, HX8357_EXIT_SLEEP_MODE);
	अगर (ret < 0)
		वापस ret;
	usleep_range(1000, 1200);

	ret = hx8357_spi_ग_लिखो_array(lcdev, hx8369_seq_ग_लिखो_CABC_control,
				ARRAY_SIZE(hx8369_seq_ग_लिखो_CABC_control));
	अगर (ret < 0)
		वापस ret;
	usleep_range(10000, 12000);

	ret = hx8357_spi_ग_लिखो_array(lcdev,
			hx8369_seq_ग_लिखो_CABC_control_setting,
			ARRAY_SIZE(hx8369_seq_ग_लिखो_CABC_control_setting));
	अगर (ret < 0)
		वापस ret;

	ret = hx8357_spi_ग_लिखो_array(lcdev,
			hx8369_seq_ग_लिखो_CABC_min_brightness,
			ARRAY_SIZE(hx8369_seq_ग_लिखो_CABC_min_brightness));
	अगर (ret < 0)
		वापस ret;
	usleep_range(10000, 12000);

	ret = hx8357_spi_ग_लिखो_array(lcdev, hx8369_seq_set_display_brightness,
				ARRAY_SIZE(hx8369_seq_set_display_brightness));
	अगर (ret < 0)
		वापस ret;

	ret = hx8357_spi_ग_लिखो_byte(lcdev, HX8357_SET_DISPLAY_ON);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

#घोषणा POWER_IS_ON(pwr)	((pwr) <= FB_BLANK_NORMAL)

अटल पूर्णांक hx8357_set_घातer(काष्ठा lcd_device *lcdev, पूर्णांक घातer)
अणु
	काष्ठा hx8357_data *lcd = lcd_get_data(lcdev);
	पूर्णांक ret = 0;

	अगर (POWER_IS_ON(घातer) && !POWER_IS_ON(lcd->state))
		ret = hx8357_निकास_standby(lcdev);
	अन्यथा अगर (!POWER_IS_ON(घातer) && POWER_IS_ON(lcd->state))
		ret = hx8357_enter_standby(lcdev);

	अगर (ret == 0)
		lcd->state = घातer;
	अन्यथा
		dev_warn(&lcdev->dev, "failed to set power mode %d\n", घातer);

	वापस ret;
पूर्ण

अटल पूर्णांक hx8357_get_घातer(काष्ठा lcd_device *lcdev)
अणु
	काष्ठा hx8357_data *lcd = lcd_get_data(lcdev);

	वापस lcd->state;
पूर्ण

अटल काष्ठा lcd_ops hx8357_ops = अणु
	.set_घातer	= hx8357_set_घातer,
	.get_घातer	= hx8357_get_घातer,
पूर्ण;

अटल स्थिर काष्ठा of_device_id hx8357_dt_ids[] = अणु
	अणु
		.compatible = "himax,hx8357",
		.data = hx8357_lcd_init,
	पूर्ण,
	अणु
		.compatible = "himax,hx8369",
		.data = hx8369_lcd_init,
	पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, hx8357_dt_ids);

अटल पूर्णांक hx8357_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा lcd_device *lcdev;
	काष्ठा hx8357_data *lcd;
	स्थिर काष्ठा of_device_id *match;
	पूर्णांक i, ret;

	lcd = devm_kzalloc(&spi->dev, माप(*lcd), GFP_KERNEL);
	अगर (!lcd)
		वापस -ENOMEM;

	ret = spi_setup(spi);
	अगर (ret < 0) अणु
		dev_err(&spi->dev, "SPI setup failed.\n");
		वापस ret;
	पूर्ण

	lcd->spi = spi;

	match = of_match_device(hx8357_dt_ids, &spi->dev);
	अगर (!match || !match->data)
		वापस -EINVAL;

	lcd->reset = of_get_named_gpio(spi->dev.of_node, "gpios-reset", 0);
	अगर (!gpio_is_valid(lcd->reset)) अणु
		dev_err(&spi->dev, "Missing dt property: gpios-reset\n");
		वापस -EINVAL;
	पूर्ण

	ret = devm_gpio_request_one(&spi->dev, lcd->reset,
				    GPIOF_OUT_INIT_HIGH,
				    "hx8357-reset");
	अगर (ret) अणु
		dev_err(&spi->dev,
			"failed to request gpio %d: %d\n",
			lcd->reset, ret);
		वापस -EINVAL;
	पूर्ण

	अगर (of_find_property(spi->dev.of_node, "im-gpios", शून्य)) अणु
		lcd->use_im_pins = 1;

		क्रम (i = 0; i < HX8357_NUM_IM_PINS; i++) अणु
			lcd->im_pins[i] = of_get_named_gpio(spi->dev.of_node,
							    "im-gpios", i);
			अगर (lcd->im_pins[i] == -EPROBE_DEFER) अणु
				dev_info(&spi->dev, "GPIO requested is not here yet, deferring the probe\n");
				वापस -EPROBE_DEFER;
			पूर्ण
			अगर (!gpio_is_valid(lcd->im_pins[i])) अणु
				dev_err(&spi->dev, "Missing dt property: im-gpios\n");
				वापस -EINVAL;
			पूर्ण

			ret = devm_gpio_request_one(&spi->dev, lcd->im_pins[i],
						    GPIOF_OUT_INIT_LOW,
						    "im_pins");
			अगर (ret) अणु
				dev_err(&spi->dev, "failed to request gpio %d: %d\n",
					lcd->im_pins[i], ret);
				वापस -EINVAL;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		lcd->use_im_pins = 0;
	पूर्ण

	lcdev = devm_lcd_device_रेजिस्टर(&spi->dev, "mxsfb", &spi->dev, lcd,
					&hx8357_ops);
	अगर (IS_ERR(lcdev)) अणु
		ret = PTR_ERR(lcdev);
		वापस ret;
	पूर्ण
	spi_set_drvdata(spi, lcdev);

	hx8357_lcd_reset(lcdev);

	ret = ((पूर्णांक (*)(काष्ठा lcd_device *))match->data)(lcdev);
	अगर (ret) अणु
		dev_err(&spi->dev, "Couldn't initialize panel\n");
		वापस ret;
	पूर्ण

	dev_info(&spi->dev, "Panel probed\n");

	वापस 0;
पूर्ण

अटल काष्ठा spi_driver hx8357_driver = अणु
	.probe  = hx8357_probe,
	.driver = अणु
		.name = "hx8357",
		.of_match_table = hx8357_dt_ids,
	पूर्ण,
पूर्ण;

module_spi_driver(hx8357_driver);

MODULE_AUTHOR("Maxime Ripard <maxime.ripard@free-electrons.com>");
MODULE_DESCRIPTION("Himax HX-8357 LCD Driver");
MODULE_LICENSE("GPL");
