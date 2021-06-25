<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * (C) Copyright 2008
 * Stefano Babic, DENX Software Engineering, sbabic@denx.de.
 *
 * This driver implements a lcd device क्रम the ILITEK 922x display
 * controller. The पूर्णांकerface to the display is SPI and the display's
 * memory is cyclically updated over the RGB पूर्णांकerface.
 */

#समावेश <linux/fb.h>
#समावेश <linux/delay.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/lcd.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/slab.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/माला.स>

/* Register offset, see manual section 8.2 */
#घोषणा REG_START_OSCILLATION			0x00
#घोषणा REG_DRIVER_CODE_READ			0x00
#घोषणा REG_DRIVER_OUTPUT_CONTROL		0x01
#घोषणा REG_LCD_AC_DRIVEING_CONTROL		0x02
#घोषणा REG_ENTRY_MODE				0x03
#घोषणा REG_COMPARE_1				0x04
#घोषणा REG_COMPARE_2				0x05
#घोषणा REG_DISPLAY_CONTROL_1			0x07
#घोषणा REG_DISPLAY_CONTROL_2			0x08
#घोषणा REG_DISPLAY_CONTROL_3			0x09
#घोषणा REG_FRAME_CYCLE_CONTROL			0x0B
#घोषणा REG_EXT_INTF_CONTROL			0x0C
#घोषणा REG_POWER_CONTROL_1			0x10
#घोषणा REG_POWER_CONTROL_2			0x11
#घोषणा REG_POWER_CONTROL_3			0x12
#घोषणा REG_POWER_CONTROL_4			0x13
#घोषणा REG_RAM_ADDRESS_SET			0x21
#घोषणा REG_WRITE_DATA_TO_GRAM			0x22
#घोषणा REG_RAM_WRITE_MASK1			0x23
#घोषणा REG_RAM_WRITE_MASK2			0x24
#घोषणा REG_GAMMA_CONTROL_1			0x30
#घोषणा REG_GAMMA_CONTROL_2			0x31
#घोषणा REG_GAMMA_CONTROL_3			0x32
#घोषणा REG_GAMMA_CONTROL_4			0x33
#घोषणा REG_GAMMA_CONTROL_5			0x34
#घोषणा REG_GAMMA_CONTROL_6			0x35
#घोषणा REG_GAMMA_CONTROL_7			0x36
#घोषणा REG_GAMMA_CONTROL_8			0x37
#घोषणा REG_GAMMA_CONTROL_9			0x38
#घोषणा REG_GAMMA_CONTROL_10			0x39
#घोषणा REG_GATE_SCAN_CONTROL			0x40
#घोषणा REG_VERT_SCROLL_CONTROL			0x41
#घोषणा REG_FIRST_SCREEN_DRIVE_POS		0x42
#घोषणा REG_SECOND_SCREEN_DRIVE_POS		0x43
#घोषणा REG_RAM_ADDR_POS_H			0x44
#घोषणा REG_RAM_ADDR_POS_V			0x45
#घोषणा REG_OSCILLATOR_CONTROL			0x4F
#घोषणा REG_GPIO				0x60
#घोषणा REG_OTP_VCM_PROGRAMMING			0x61
#घोषणा REG_OTP_VCM_STATUS_ENABLE		0x62
#घोषणा REG_OTP_PROGRAMMING_ID_KEY		0x65

/*
 * maximum frequency क्रम रेजिस्टर access
 * (not क्रम the GRAM access)
 */
#घोषणा ILITEK_MAX_FREQ_REG	4000000

/*
 * Device ID as found in the datasheet (supports 9221 and 9222)
 */
#घोषणा ILITEK_DEVICE_ID	0x9220
#घोषणा ILITEK_DEVICE_ID_MASK	0xFFF0

/* Last two bits in the START BYTE */
#घोषणा START_RS_INDEX		0
#घोषणा START_RS_REG		1
#घोषणा START_RW_WRITE		0
#घोषणा START_RW_READ		1

/**
 * START_BYTE(id, rs, rw)
 *
 * Set the start byte according to the required operation.
 * The start byte is defined as:
 *   ----------------------------------
 *  | 0 | 1 | 1 | 1 | 0 | ID | RS | RW |
 *   ----------------------------------
 * @id: display's id as set by the manufacturer
 * @rs: operation type bit, one of:
 *	  - START_RS_INDEX	set the index रेजिस्टर
 *	  - START_RS_REG	ग_लिखो/पढ़ो रेजिस्टरs/GRAM
 * @rw: पढ़ो/ग_लिखो operation
 *	 - START_RW_WRITE	ग_लिखो
 *	 - START_RW_READ	पढ़ो
 */
#घोषणा START_BYTE(id, rs, rw)	\
	(0x70 | (((id) & 0x01) << 2) | (((rs) & 0x01) << 1) | ((rw) & 0x01))

/**
 * CHECK_FREQ_REG(spi_device s, spi_transfer x) - Check the frequency
 *	क्रम the SPI transfer. According to the datasheet, the controller
 *	accept higher frequency क्रम the GRAM transfer, but it requires
 *	lower frequency when the रेजिस्टरs are पढ़ो/written.
 *	The macro sets the frequency in the spi_transfer काष्ठाure अगर
 *	the frequency exceeds the maximum value.
 * @s: poपूर्णांकer to an SPI device
 * @x: poपूर्णांकer to the पढ़ो/ग_लिखो buffer pair
 */
#घोषणा CHECK_FREQ_REG(s, x)	\
	करो अणु			\
		अगर (s->max_speed_hz > ILITEK_MAX_FREQ_REG)	\
			((काष्ठा spi_transfer *)x)->speed_hz =	\
					ILITEK_MAX_FREQ_REG;	\
	पूर्ण जबतक (0)

#घोषणा CMD_बफ_मानE		16

#घोषणा POWER_IS_ON(pwr)	((pwr) <= FB_BLANK_NORMAL)

#घोषणा set_tx_byte(b)		(tx_invert ? ~(b) : b)

/*
 * ili922x_id - id as set by manufacturer
 */
अटल पूर्णांक ili922x_id = 1;
module_param(ili922x_id, पूर्णांक, 0);

अटल पूर्णांक tx_invert;
module_param(tx_invert, पूर्णांक, 0);

/*
 * driver's निजी काष्ठाure
 */
काष्ठा ili922x अणु
	काष्ठा spi_device *spi;
	काष्ठा lcd_device *ld;
	पूर्णांक घातer;
पूर्ण;

/**
 * ili922x_पढ़ो_status - पढ़ो status रेजिस्टर from display
 * @spi: spi device
 * @rs:  output value
 */
अटल पूर्णांक ili922x_पढ़ो_status(काष्ठा spi_device *spi, u16 *rs)
अणु
	काष्ठा spi_message msg;
	काष्ठा spi_transfer xfer;
	अचिन्हित अक्षर tbuf[CMD_बफ_मानE];
	अचिन्हित अक्षर rbuf[CMD_बफ_मानE];
	पूर्णांक ret, i;

	स_रखो(&xfer, 0, माप(काष्ठा spi_transfer));
	spi_message_init(&msg);
	xfer.tx_buf = tbuf;
	xfer.rx_buf = rbuf;
	xfer.cs_change = 1;
	CHECK_FREQ_REG(spi, &xfer);

	tbuf[0] = set_tx_byte(START_BYTE(ili922x_id, START_RS_INDEX,
					 START_RW_READ));
	/*
	 * we need 4-byte xfer here due to invalid dummy byte
	 * received after start byte
	 */
	क्रम (i = 1; i < 4; i++)
		tbuf[i] = set_tx_byte(0);	/* dummy */

	xfer.bits_per_word = 8;
	xfer.len = 4;
	spi_message_add_tail(&xfer, &msg);
	ret = spi_sync(spi, &msg);
	अगर (ret < 0) अणु
		dev_dbg(&spi->dev, "Error sending SPI message 0x%x", ret);
		वापस ret;
	पूर्ण

	*rs = (rbuf[2] << 8) + rbuf[3];
	वापस 0;
पूर्ण

/**
 * ili922x_पढ़ो - पढ़ो रेजिस्टर from display
 * @spi: spi device
 * @reg: offset of the रेजिस्टर to be पढ़ो
 * @rx:  output value
 */
अटल पूर्णांक ili922x_पढ़ो(काष्ठा spi_device *spi, u8 reg, u16 *rx)
अणु
	काष्ठा spi_message msg;
	काष्ठा spi_transfer xfer_regindex, xfer_regvalue;
	अचिन्हित अक्षर tbuf[CMD_बफ_मानE];
	अचिन्हित अक्षर rbuf[CMD_बफ_मानE];
	पूर्णांक ret, len = 0, send_bytes;

	स_रखो(&xfer_regindex, 0, माप(काष्ठा spi_transfer));
	स_रखो(&xfer_regvalue, 0, माप(काष्ठा spi_transfer));
	spi_message_init(&msg);
	xfer_regindex.tx_buf = tbuf;
	xfer_regindex.rx_buf = rbuf;
	xfer_regindex.cs_change = 1;
	CHECK_FREQ_REG(spi, &xfer_regindex);

	tbuf[0] = set_tx_byte(START_BYTE(ili922x_id, START_RS_INDEX,
					 START_RW_WRITE));
	tbuf[1] = set_tx_byte(0);
	tbuf[2] = set_tx_byte(reg);
	xfer_regindex.bits_per_word = 8;
	len = xfer_regindex.len = 3;
	spi_message_add_tail(&xfer_regindex, &msg);

	send_bytes = len;

	tbuf[len++] = set_tx_byte(START_BYTE(ili922x_id, START_RS_REG,
					     START_RW_READ));
	tbuf[len++] = set_tx_byte(0);
	tbuf[len] = set_tx_byte(0);

	xfer_regvalue.cs_change = 1;
	xfer_regvalue.len = 3;
	xfer_regvalue.tx_buf = &tbuf[send_bytes];
	xfer_regvalue.rx_buf = &rbuf[send_bytes];
	CHECK_FREQ_REG(spi, &xfer_regvalue);

	spi_message_add_tail(&xfer_regvalue, &msg);
	ret = spi_sync(spi, &msg);
	अगर (ret < 0) अणु
		dev_dbg(&spi->dev, "Error sending SPI message 0x%x", ret);
		वापस ret;
	पूर्ण

	*rx = (rbuf[1 + send_bytes] << 8) + rbuf[2 + send_bytes];
	वापस 0;
पूर्ण

/**
 * ili922x_ग_लिखो - ग_लिखो a controller रेजिस्टर
 * @spi: काष्ठा spi_device *
 * @reg: offset of the रेजिस्टर to be written
 * @value: value to be written
 */
अटल पूर्णांक ili922x_ग_लिखो(काष्ठा spi_device *spi, u8 reg, u16 value)
अणु
	काष्ठा spi_message msg;
	काष्ठा spi_transfer xfer_regindex, xfer_regvalue;
	अचिन्हित अक्षर tbuf[CMD_बफ_मानE];
	अचिन्हित अक्षर rbuf[CMD_बफ_मानE];
	पूर्णांक ret;

	स_रखो(&xfer_regindex, 0, माप(काष्ठा spi_transfer));
	स_रखो(&xfer_regvalue, 0, माप(काष्ठा spi_transfer));

	spi_message_init(&msg);
	xfer_regindex.tx_buf = tbuf;
	xfer_regindex.rx_buf = rbuf;
	xfer_regindex.cs_change = 1;
	CHECK_FREQ_REG(spi, &xfer_regindex);

	tbuf[0] = set_tx_byte(START_BYTE(ili922x_id, START_RS_INDEX,
					 START_RW_WRITE));
	tbuf[1] = set_tx_byte(0);
	tbuf[2] = set_tx_byte(reg);
	xfer_regindex.bits_per_word = 8;
	xfer_regindex.len = 3;
	spi_message_add_tail(&xfer_regindex, &msg);

	ret = spi_sync(spi, &msg);

	spi_message_init(&msg);
	tbuf[0] = set_tx_byte(START_BYTE(ili922x_id, START_RS_REG,
					 START_RW_WRITE));
	tbuf[1] = set_tx_byte((value & 0xFF00) >> 8);
	tbuf[2] = set_tx_byte(value & 0x00FF);

	xfer_regvalue.cs_change = 1;
	xfer_regvalue.len = 3;
	xfer_regvalue.tx_buf = tbuf;
	xfer_regvalue.rx_buf = rbuf;
	CHECK_FREQ_REG(spi, &xfer_regvalue);

	spi_message_add_tail(&xfer_regvalue, &msg);

	ret = spi_sync(spi, &msg);
	अगर (ret < 0) अणु
		dev_err(&spi->dev, "Error sending SPI message 0x%x", ret);
		वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

#अगर_घोषित DEBUG
/**
 * ili922x_reg_dump - dump all रेजिस्टरs
 *
 * @spi: poपूर्णांकer to an SPI device
 */
अटल व्योम ili922x_reg_dump(काष्ठा spi_device *spi)
अणु
	u8 reg;
	u16 rx;

	dev_dbg(&spi->dev, "ILI922x configuration registers:\n");
	क्रम (reg = REG_START_OSCILLATION;
	     reg <= REG_OTP_PROGRAMMING_ID_KEY; reg++) अणु
		ili922x_पढ़ो(spi, reg, &rx);
		dev_dbg(&spi->dev, "reg @ 0x%02X: 0x%04X\n", reg, rx);
	पूर्ण
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम ili922x_reg_dump(काष्ठा spi_device *spi) अणुपूर्ण
#पूर्ण_अगर

/**
 * set_ग_लिखो_to_gram_reg - initialize the display to ग_लिखो the GRAM
 * @spi: spi device
 */
अटल व्योम set_ग_लिखो_to_gram_reg(काष्ठा spi_device *spi)
अणु
	काष्ठा spi_message msg;
	काष्ठा spi_transfer xfer;
	अचिन्हित अक्षर tbuf[CMD_बफ_मानE];

	स_रखो(&xfer, 0, माप(काष्ठा spi_transfer));

	spi_message_init(&msg);
	xfer.tx_buf = tbuf;
	xfer.rx_buf = शून्य;
	xfer.cs_change = 1;

	tbuf[0] = START_BYTE(ili922x_id, START_RS_INDEX, START_RW_WRITE);
	tbuf[1] = 0;
	tbuf[2] = REG_WRITE_DATA_TO_GRAM;

	xfer.bits_per_word = 8;
	xfer.len = 3;
	spi_message_add_tail(&xfer, &msg);
	spi_sync(spi, &msg);
पूर्ण

/**
 * ili922x_घातeron - turn the display on
 * @spi: spi device
 *
 * The sequence to turn on the display is taken from
 * the datasheet and/or the example code provided by the
 * manufacturer.
 */
अटल पूर्णांक ili922x_घातeron(काष्ठा spi_device *spi)
अणु
	पूर्णांक ret;

	/* Power on */
	ret = ili922x_ग_लिखो(spi, REG_POWER_CONTROL_1, 0x0000);
	usleep_range(10000, 10500);
	ret += ili922x_ग_लिखो(spi, REG_POWER_CONTROL_2, 0x0000);
	ret += ili922x_ग_लिखो(spi, REG_POWER_CONTROL_3, 0x0000);
	msleep(40);
	ret += ili922x_ग_लिखो(spi, REG_POWER_CONTROL_4, 0x0000);
	msleep(40);
	/* रेजिस्टर 0x56 is not करोcumented in the datasheet */
	ret += ili922x_ग_लिखो(spi, 0x56, 0x080F);
	ret += ili922x_ग_लिखो(spi, REG_POWER_CONTROL_1, 0x4240);
	usleep_range(10000, 10500);
	ret += ili922x_ग_लिखो(spi, REG_POWER_CONTROL_2, 0x0000);
	ret += ili922x_ग_लिखो(spi, REG_POWER_CONTROL_3, 0x0014);
	msleep(40);
	ret += ili922x_ग_लिखो(spi, REG_POWER_CONTROL_4, 0x1319);
	msleep(40);

	वापस ret;
पूर्ण

/**
 * ili922x_घातeroff - turn the display off
 * @spi: spi device
 */
अटल पूर्णांक ili922x_घातeroff(काष्ठा spi_device *spi)
अणु
	पूर्णांक ret;

	/* Power off */
	ret = ili922x_ग_लिखो(spi, REG_POWER_CONTROL_1, 0x0000);
	usleep_range(10000, 10500);
	ret += ili922x_ग_लिखो(spi, REG_POWER_CONTROL_2, 0x0000);
	ret += ili922x_ग_लिखो(spi, REG_POWER_CONTROL_3, 0x0000);
	msleep(40);
	ret += ili922x_ग_लिखो(spi, REG_POWER_CONTROL_4, 0x0000);
	msleep(40);

	वापस ret;
पूर्ण

/**
 * ili922x_display_init - initialize the display by setting
 *			  the configuration रेजिस्टरs
 * @spi: spi device
 */
अटल व्योम ili922x_display_init(काष्ठा spi_device *spi)
अणु
	ili922x_ग_लिखो(spi, REG_START_OSCILLATION, 1);
	usleep_range(10000, 10500);
	ili922x_ग_लिखो(spi, REG_DRIVER_OUTPUT_CONTROL, 0x691B);
	ili922x_ग_लिखो(spi, REG_LCD_AC_DRIVEING_CONTROL, 0x0700);
	ili922x_ग_लिखो(spi, REG_ENTRY_MODE, 0x1030);
	ili922x_ग_लिखो(spi, REG_COMPARE_1, 0x0000);
	ili922x_ग_लिखो(spi, REG_COMPARE_2, 0x0000);
	ili922x_ग_लिखो(spi, REG_DISPLAY_CONTROL_1, 0x0037);
	ili922x_ग_लिखो(spi, REG_DISPLAY_CONTROL_2, 0x0202);
	ili922x_ग_लिखो(spi, REG_DISPLAY_CONTROL_3, 0x0000);
	ili922x_ग_लिखो(spi, REG_FRAME_CYCLE_CONTROL, 0x0000);

	/* Set RGB पूर्णांकerface */
	ili922x_ग_लिखो(spi, REG_EXT_INTF_CONTROL, 0x0110);

	ili922x_घातeron(spi);

	ili922x_ग_लिखो(spi, REG_GAMMA_CONTROL_1, 0x0302);
	ili922x_ग_लिखो(spi, REG_GAMMA_CONTROL_2, 0x0407);
	ili922x_ग_लिखो(spi, REG_GAMMA_CONTROL_3, 0x0304);
	ili922x_ग_लिखो(spi, REG_GAMMA_CONTROL_4, 0x0203);
	ili922x_ग_लिखो(spi, REG_GAMMA_CONTROL_5, 0x0706);
	ili922x_ग_लिखो(spi, REG_GAMMA_CONTROL_6, 0x0407);
	ili922x_ग_लिखो(spi, REG_GAMMA_CONTROL_7, 0x0706);
	ili922x_ग_लिखो(spi, REG_GAMMA_CONTROL_8, 0x0000);
	ili922x_ग_लिखो(spi, REG_GAMMA_CONTROL_9, 0x0C06);
	ili922x_ग_लिखो(spi, REG_GAMMA_CONTROL_10, 0x0F00);
	ili922x_ग_लिखो(spi, REG_RAM_ADDRESS_SET, 0x0000);
	ili922x_ग_लिखो(spi, REG_GATE_SCAN_CONTROL, 0x0000);
	ili922x_ग_लिखो(spi, REG_VERT_SCROLL_CONTROL, 0x0000);
	ili922x_ग_लिखो(spi, REG_FIRST_SCREEN_DRIVE_POS, 0xDB00);
	ili922x_ग_लिखो(spi, REG_SECOND_SCREEN_DRIVE_POS, 0xDB00);
	ili922x_ग_लिखो(spi, REG_RAM_ADDR_POS_H, 0xAF00);
	ili922x_ग_लिखो(spi, REG_RAM_ADDR_POS_V, 0xDB00);
	ili922x_reg_dump(spi);
	set_ग_लिखो_to_gram_reg(spi);
पूर्ण

अटल पूर्णांक ili922x_lcd_घातer(काष्ठा ili922x *lcd, पूर्णांक घातer)
अणु
	पूर्णांक ret = 0;

	अगर (POWER_IS_ON(घातer) && !POWER_IS_ON(lcd->घातer))
		ret = ili922x_घातeron(lcd->spi);
	अन्यथा अगर (!POWER_IS_ON(घातer) && POWER_IS_ON(lcd->घातer))
		ret = ili922x_घातeroff(lcd->spi);

	अगर (!ret)
		lcd->घातer = घातer;

	वापस ret;
पूर्ण

अटल पूर्णांक ili922x_set_घातer(काष्ठा lcd_device *ld, पूर्णांक घातer)
अणु
	काष्ठा ili922x *ili = lcd_get_data(ld);

	वापस ili922x_lcd_घातer(ili, घातer);
पूर्ण

अटल पूर्णांक ili922x_get_घातer(काष्ठा lcd_device *ld)
अणु
	काष्ठा ili922x *ili = lcd_get_data(ld);

	वापस ili->घातer;
पूर्ण

अटल काष्ठा lcd_ops ili922x_ops = अणु
	.get_घातer = ili922x_get_घातer,
	.set_घातer = ili922x_set_घातer,
पूर्ण;

अटल पूर्णांक ili922x_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा ili922x *ili;
	काष्ठा lcd_device *lcd;
	पूर्णांक ret;
	u16 reg = 0;

	ili = devm_kzalloc(&spi->dev, माप(*ili), GFP_KERNEL);
	अगर (!ili)
		वापस -ENOMEM;

	ili->spi = spi;
	spi_set_drvdata(spi, ili);

	/* check अगर the device is connected */
	ret = ili922x_पढ़ो(spi, REG_DRIVER_CODE_READ, &reg);
	अगर (ret || ((reg & ILITEK_DEVICE_ID_MASK) != ILITEK_DEVICE_ID)) अणु
		dev_err(&spi->dev,
			"no LCD found: Chip ID 0x%x, ret %d\n",
			reg, ret);
		वापस -ENODEV;
	पूर्ण

	dev_info(&spi->dev, "ILI%x found, SPI freq %d, mode %d\n",
		 reg, spi->max_speed_hz, spi->mode);

	ret = ili922x_पढ़ो_status(spi, &reg);
	अगर (ret) अणु
		dev_err(&spi->dev, "reading RS failed...\n");
		वापस ret;
	पूर्ण

	dev_dbg(&spi->dev, "status: 0x%x\n", reg);

	ili922x_display_init(spi);

	ili->घातer = FB_BLANK_POWERDOWN;

	lcd = devm_lcd_device_रेजिस्टर(&spi->dev, "ili922xlcd", &spi->dev, ili,
					&ili922x_ops);
	अगर (IS_ERR(lcd)) अणु
		dev_err(&spi->dev, "cannot register LCD\n");
		वापस PTR_ERR(lcd);
	पूर्ण

	ili->ld = lcd;
	spi_set_drvdata(spi, ili);

	ili922x_lcd_घातer(ili, FB_BLANK_UNBLANK);

	वापस 0;
पूर्ण

अटल पूर्णांक ili922x_हटाओ(काष्ठा spi_device *spi)
अणु
	ili922x_घातeroff(spi);
	वापस 0;
पूर्ण

अटल काष्ठा spi_driver ili922x_driver = अणु
	.driver = अणु
		.name = "ili922x",
	पूर्ण,
	.probe = ili922x_probe,
	.हटाओ = ili922x_हटाओ,
पूर्ण;

module_spi_driver(ili922x_driver);

MODULE_AUTHOR("Stefano Babic <sbabic@denx.de>");
MODULE_DESCRIPTION("ILI9221/9222 LCD driver");
MODULE_LICENSE("GPL");
MODULE_PARM_DESC(ili922x_id, "set controller identifier (default=1)");
MODULE_PARM_DESC(tx_invert, "invert bytes before sending");
