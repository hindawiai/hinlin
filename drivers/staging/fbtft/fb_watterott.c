<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * FB driver क्रम the Watterott LCD Controller
 *
 * Copyright (C) 2013 Noralf Tronnes
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/delay.h>

#समावेश "fbtft.h"

#घोषणा DRVNAME			"fb_watterott"
#घोषणा WIDTH			320
#घोषणा HEIGHT			240
#घोषणा FPS			5
#घोषणा TXBUFLEN		1024
#घोषणा DEFAULT_BRIGHTNESS	50

#घोषणा CMD_VERSION		0x01
#घोषणा CMD_LCD_LED		0x10
#घोषणा CMD_LCD_RESET		0x11
#घोषणा CMD_LCD_ORIENTATION	0x20
#घोषणा CMD_LCD_DRAWIMAGE	0x27
#घोषणा COLOR_RGB323		8
#घोषणा COLOR_RGB332		9
#घोषणा COLOR_RGB233		10
#घोषणा COLOR_RGB565		16

अटल लघु mode = 565;
module_param(mode, लघु, 0000);
MODULE_PARM_DESC(mode, "RGB color transfer mode: 332, 565 (default)");

अटल व्योम ग_लिखो_reg8_bus8(काष्ठा fbtft_par *par, पूर्णांक len, ...)
अणु
	बहु_सूची args;
	पूर्णांक i, ret;
	u8 *buf = par->buf;

	बहु_शुरू(args, len);
	क्रम (i = 0; i < len; i++)
		*buf++ = (u8)बहु_तर्क(args, अचिन्हित पूर्णांक);
	बहु_पूर्ण(args);

	fbtft_par_dbg_hex(DEBUG_WRITE_REGISTER, par,
			  par->info->device, u8, par->buf,
			  len, "%s: ", __func__);

	ret = par->fbtftops.ग_लिखो(par, par->buf, len);
	अगर (ret < 0) अणु
		dev_err(par->info->device,
			"write() failed and returned %d\n", ret);
		वापस;
	पूर्ण
पूर्ण

अटल पूर्णांक ग_लिखो_vmem(काष्ठा fbtft_par *par, माप_प्रकार offset, माप_प्रकार len)
अणु
	अचिन्हित पूर्णांक start_line, end_line;
	u16 *vmem16 = (u16 *)(par->info->screen_buffer + offset);
	__be16 *pos = par->txbuf.buf + 1;
	__be16 *buf16 = par->txbuf.buf + 10;
	पूर्णांक i, j;
	पूर्णांक ret = 0;

	start_line = offset / par->info->fix.line_length;
	end_line = start_line + (len / par->info->fix.line_length) - 1;

	/* Set command header. pos: x, y, w, h */
	((u8 *)par->txbuf.buf)[0] = CMD_LCD_DRAWIMAGE;
	pos[0] = 0;
	pos[2] = cpu_to_be16(par->info->var.xres);
	pos[3] = cpu_to_be16(1);
	((u8 *)par->txbuf.buf)[9] = COLOR_RGB565;

	क्रम (i = start_line; i <= end_line; i++) अणु
		pos[1] = cpu_to_be16(i);
		क्रम (j = 0; j < par->info->var.xres; j++)
			buf16[j] = cpu_to_be16(*vmem16++);
		ret = par->fbtftops.ग_लिखो(par,
			par->txbuf.buf, 10 + par->info->fix.line_length);
		अगर (ret < 0)
			वापस ret;
		udelay(300);
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक rgb565_to_rgb332(u16 c)
अणु
	वापस ((c & 0xE000) >> 8) | ((c & 000700) >> 6) | ((c & 0x0018) >> 3);
पूर्ण

अटल पूर्णांक ग_लिखो_vmem_8bit(काष्ठा fbtft_par *par, माप_प्रकार offset, माप_प्रकार len)
अणु
	अचिन्हित पूर्णांक start_line, end_line;
	u16 *vmem16 = (u16 *)(par->info->screen_buffer + offset);
	__be16 *pos = par->txbuf.buf + 1;
	u8 *buf8 = par->txbuf.buf + 10;
	पूर्णांक i, j;
	पूर्णांक ret = 0;

	start_line = offset / par->info->fix.line_length;
	end_line = start_line + (len / par->info->fix.line_length) - 1;

	/* Set command header. pos: x, y, w, h */
	((u8 *)par->txbuf.buf)[0] = CMD_LCD_DRAWIMAGE;
	pos[0] = 0;
	pos[2] = cpu_to_be16(par->info->var.xres);
	pos[3] = cpu_to_be16(1);
	((u8 *)par->txbuf.buf)[9] = COLOR_RGB332;

	क्रम (i = start_line; i <= end_line; i++) अणु
		pos[1] = cpu_to_be16(i);
		क्रम (j = 0; j < par->info->var.xres; j++) अणु
			buf8[j] = rgb565_to_rgb332(*vmem16);
			vmem16++;
		पूर्ण
		ret = par->fbtftops.ग_लिखो(par,
			par->txbuf.buf, 10 + par->info->var.xres);
		अगर (ret < 0)
			वापस ret;
		udelay(700);
	पूर्ण

	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक firmware_version(काष्ठा fbtft_par *par)
अणु
	u8 rxbuf[4] = अणु0, पूर्ण;

	ग_लिखो_reg(par, CMD_VERSION);
	par->fbtftops.पढ़ो(par, rxbuf, 4);
	अगर (rxbuf[1] != '.')
		वापस 0;

	वापस (rxbuf[0] - '0') << 8 | (rxbuf[2] - '0') << 4 | (rxbuf[3] - '0');
पूर्ण

अटल पूर्णांक init_display(काष्ठा fbtft_par *par)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक version;
	u8 save_mode;

	/* enable SPI पूर्णांकerface by having CS and MOSI low during reset */
	save_mode = par->spi->mode;
	/*
	 * Set CS active inverse polarity: just setting SPI_CS_HIGH करोes not
	 * work with GPIO based chip selects that are logically active high
	 * but inverted inside the GPIO library, so enक्रमce inverted
	 * semantics.
	 */
	par->spi->mode ^= SPI_CS_HIGH;
	ret = spi_setup(par->spi);
	अगर (ret) अणु
		dev_err(par->info->device,
			"Could not set inverse CS polarity\n");
		वापस ret;
	पूर्ण
	ग_लिखो_reg(par, 0x00); /* make sure mode is set */

	mdelay(50);
	par->fbtftops.reset(par);
	mdelay(1000);
	par->spi->mode = save_mode;
	ret = spi_setup(par->spi);
	अगर (ret) अणु
		dev_err(par->info->device, "Could not restore SPI mode\n");
		वापस ret;
	पूर्ण
	ग_लिखो_reg(par, 0x00);

	version = firmware_version(par);
	fbtft_par_dbg(DEBUG_INIT_DISPLAY, par, "Firmware version: %x.%02x\n",
		      version >> 8, version & 0xFF);

	अगर (mode == 332)
		par->fbtftops.ग_लिखो_vmem = ग_लिखो_vmem_8bit;
	वापस 0;
पूर्ण

अटल व्योम set_addr_win(काष्ठा fbtft_par *par, पूर्णांक xs, पूर्णांक ys, पूर्णांक xe, पूर्णांक ye)
अणु
	/* not used on this controller */
पूर्ण

अटल पूर्णांक set_var(काष्ठा fbtft_par *par)
अणु
	u8 rotate;

	/* this controller rotates घड़ी wise */
	चयन (par->info->var.rotate) अणु
	हाल 90:
		rotate = 27;
		अवरोध;
	हाल 180:
		rotate = 18;
		अवरोध;
	हाल 270:
		rotate = 9;
		अवरोध;
	शेष:
		rotate = 0;
	पूर्ण
	ग_लिखो_reg(par, CMD_LCD_ORIENTATION, rotate);

	वापस 0;
पूर्ण

अटल पूर्णांक verअगरy_gpios(काष्ठा fbtft_par *par)
अणु
	अगर (!par->gpio.reset) अणु
		dev_err(par->info->device, "Missing 'reset' gpio. Aborting.\n");
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_FB_BACKLIGHT
अटल पूर्णांक backlight_chip_update_status(काष्ठा backlight_device *bd)
अणु
	काष्ठा fbtft_par *par = bl_get_data(bd);
	पूर्णांक brightness = bd->props.brightness;

	fbtft_par_dbg(DEBUG_BACKLIGHT, par,
		      "%s: brightness=%d, power=%d, fb_blank=%d\n", __func__,
		      bd->props.brightness, bd->props.घातer,
		      bd->props.fb_blank);

	अगर (bd->props.घातer != FB_BLANK_UNBLANK)
		brightness = 0;

	अगर (bd->props.fb_blank != FB_BLANK_UNBLANK)
		brightness = 0;

	ग_लिखो_reg(par, CMD_LCD_LED, brightness);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा backlight_ops bl_ops = अणु
	.update_status = backlight_chip_update_status,
पूर्ण;

अटल व्योम रेजिस्टर_chip_backlight(काष्ठा fbtft_par *par)
अणु
	काष्ठा backlight_device *bd;
	काष्ठा backlight_properties bl_props = अणु 0, पूर्ण;

	bl_props.type = BACKLIGHT_RAW;
	bl_props.घातer = FB_BLANK_POWERDOWN;
	bl_props.max_brightness = 100;
	bl_props.brightness = DEFAULT_BRIGHTNESS;

	bd = backlight_device_रेजिस्टर(dev_driver_string(par->info->device),
				       par->info->device, par, &bl_ops,
				       &bl_props);
	अगर (IS_ERR(bd)) अणु
		dev_err(par->info->device,
			"cannot register backlight device (%ld)\n",
			PTR_ERR(bd));
		वापस;
	पूर्ण
	par->info->bl_dev = bd;

	अगर (!par->fbtftops.unरेजिस्टर_backlight)
		par->fbtftops.unरेजिस्टर_backlight = fbtft_unरेजिस्टर_backlight;
पूर्ण
#अन्यथा
#घोषणा रेजिस्टर_chip_backlight शून्य
#पूर्ण_अगर

अटल काष्ठा fbtft_display display = अणु
	.regwidth = 8,
	.buswidth = 8,
	.width = WIDTH,
	.height = HEIGHT,
	.fps = FPS,
	.txbuflen = TXBUFLEN,
	.fbtftops = अणु
		.ग_लिखो_रेजिस्टर = ग_लिखो_reg8_bus8,
		.ग_लिखो_vmem = ग_लिखो_vmem,
		.init_display = init_display,
		.set_addr_win = set_addr_win,
		.set_var = set_var,
		.verअगरy_gpios = verअगरy_gpios,
		.रेजिस्टर_backlight = रेजिस्टर_chip_backlight,
	पूर्ण,
पूर्ण;

FBTFT_REGISTER_DRIVER(DRVNAME, "watterott,openlcd", &display);

MODULE_ALIAS("spi:" DRVNAME);

MODULE_DESCRIPTION("FB driver for the Watterott LCD Controller");
MODULE_AUTHOR("Noralf Tronnes");
MODULE_LICENSE("GPL");
