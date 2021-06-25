<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * FBTFT driver क्रम the RA8875 LCD Controller
 * Copyright by Pf@nne & NOTRO
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>

#समावेश <linux/gpio/consumer.h>
#समावेश "fbtft.h"

#घोषणा DRVNAME "fb_ra8875"

अटल पूर्णांक ग_लिखो_spi(काष्ठा fbtft_par *par, व्योम *buf, माप_प्रकार len)
अणु
	काष्ठा spi_transfer t = अणु
		.tx_buf = buf,
		.len = len,
		.speed_hz = 1000000,
	पूर्ण;
	काष्ठा spi_message m;

	fbtft_par_dbg_hex(DEBUG_WRITE, par, par->info->device, u8, buf, len,
			  "%s(len=%zu): ", __func__, len);

	अगर (!par->spi) अणु
		dev_err(par->info->device,
			"%s: par->spi is unexpectedly NULL\n", __func__);
		वापस -1;
	पूर्ण

	spi_message_init(&m);
	spi_message_add_tail(&t, &m);
	वापस spi_sync(par->spi, &m);
पूर्ण

अटल पूर्णांक init_display(काष्ठा fbtft_par *par)
अणु
	gpiod_set_value(par->gpio.dc, 1);

	fbtft_par_dbg(DEBUG_INIT_DISPLAY, par,
		      "%s()\n", __func__);
	fbtft_par_dbg(DEBUG_INIT_DISPLAY, par,
		      "display size %dx%d\n",
		par->info->var.xres,
		par->info->var.yres);

	par->fbtftops.reset(par);

	अगर ((par->info->var.xres == 320) && (par->info->var.yres == 240)) अणु
		/* PLL घड़ी frequency */
		ग_लिखो_reg(par, 0x88, 0x0A);
		ग_लिखो_reg(par, 0x89, 0x02);
		mdelay(10);
		/* color deep / MCU Interface */
		ग_लिखो_reg(par, 0x10, 0x0C);
		/* pixel घड़ी period  */
		ग_लिखो_reg(par, 0x04, 0x03);
		mdelay(1);
		/* horizontal settings */
		ग_लिखो_reg(par, 0x14, 0x27);
		ग_लिखो_reg(par, 0x15, 0x00);
		ग_लिखो_reg(par, 0x16, 0x05);
		ग_लिखो_reg(par, 0x17, 0x04);
		ग_लिखो_reg(par, 0x18, 0x03);
		/* vertical settings */
		ग_लिखो_reg(par, 0x19, 0xEF);
		ग_लिखो_reg(par, 0x1A, 0x00);
		ग_लिखो_reg(par, 0x1B, 0x05);
		ग_लिखो_reg(par, 0x1C, 0x00);
		ग_लिखो_reg(par, 0x1D, 0x0E);
		ग_लिखो_reg(par, 0x1E, 0x00);
		ग_लिखो_reg(par, 0x1F, 0x02);
	पूर्ण अन्यथा अगर ((par->info->var.xres == 480) &&
		   (par->info->var.yres == 272)) अणु
		/* PLL घड़ी frequency  */
		ग_लिखो_reg(par, 0x88, 0x0A);
		ग_लिखो_reg(par, 0x89, 0x02);
		mdelay(10);
		/* color deep / MCU Interface */
		ग_लिखो_reg(par, 0x10, 0x0C);
		/* pixel घड़ी period  */
		ग_लिखो_reg(par, 0x04, 0x82);
		mdelay(1);
		/* horizontal settings */
		ग_लिखो_reg(par, 0x14, 0x3B);
		ग_लिखो_reg(par, 0x15, 0x00);
		ग_लिखो_reg(par, 0x16, 0x01);
		ग_लिखो_reg(par, 0x17, 0x00);
		ग_लिखो_reg(par, 0x18, 0x05);
		/* vertical settings */
		ग_लिखो_reg(par, 0x19, 0x0F);
		ग_लिखो_reg(par, 0x1A, 0x01);
		ग_लिखो_reg(par, 0x1B, 0x02);
		ग_लिखो_reg(par, 0x1C, 0x00);
		ग_लिखो_reg(par, 0x1D, 0x07);
		ग_लिखो_reg(par, 0x1E, 0x00);
		ग_लिखो_reg(par, 0x1F, 0x09);
	पूर्ण अन्यथा अगर ((par->info->var.xres == 640) &&
		   (par->info->var.yres == 480)) अणु
		/* PLL घड़ी frequency */
		ग_लिखो_reg(par, 0x88, 0x0B);
		ग_लिखो_reg(par, 0x89, 0x02);
		mdelay(10);
		/* color deep / MCU Interface */
		ग_लिखो_reg(par, 0x10, 0x0C);
		/* pixel घड़ी period */
		ग_लिखो_reg(par, 0x04, 0x01);
		mdelay(1);
		/* horizontal settings */
		ग_लिखो_reg(par, 0x14, 0x4F);
		ग_लिखो_reg(par, 0x15, 0x05);
		ग_लिखो_reg(par, 0x16, 0x0F);
		ग_लिखो_reg(par, 0x17, 0x01);
		ग_लिखो_reg(par, 0x18, 0x00);
		/* vertical settings */
		ग_लिखो_reg(par, 0x19, 0xDF);
		ग_लिखो_reg(par, 0x1A, 0x01);
		ग_लिखो_reg(par, 0x1B, 0x0A);
		ग_लिखो_reg(par, 0x1C, 0x00);
		ग_लिखो_reg(par, 0x1D, 0x0E);
		ग_लिखो_reg(par, 0x1E, 0x00);
		ग_लिखो_reg(par, 0x1F, 0x01);
	पूर्ण अन्यथा अगर ((par->info->var.xres == 800) &&
		   (par->info->var.yres == 480)) अणु
		/* PLL घड़ी frequency */
		ग_लिखो_reg(par, 0x88, 0x0B);
		ग_लिखो_reg(par, 0x89, 0x02);
		mdelay(10);
		/* color deep / MCU Interface */
		ग_लिखो_reg(par, 0x10, 0x0C);
		/* pixel घड़ी period */
		ग_लिखो_reg(par, 0x04, 0x81);
		mdelay(1);
		/* horizontal settings */
		ग_लिखो_reg(par, 0x14, 0x63);
		ग_लिखो_reg(par, 0x15, 0x03);
		ग_लिखो_reg(par, 0x16, 0x03);
		ग_लिखो_reg(par, 0x17, 0x02);
		ग_लिखो_reg(par, 0x18, 0x00);
		/* vertical settings */
		ग_लिखो_reg(par, 0x19, 0xDF);
		ग_लिखो_reg(par, 0x1A, 0x01);
		ग_लिखो_reg(par, 0x1B, 0x14);
		ग_लिखो_reg(par, 0x1C, 0x00);
		ग_लिखो_reg(par, 0x1D, 0x06);
		ग_लिखो_reg(par, 0x1E, 0x00);
		ग_लिखो_reg(par, 0x1F, 0x01);
	पूर्ण अन्यथा अणु
		dev_err(par->info->device, "display size is not supported!!");
		वापस -1;
	पूर्ण

	/* PWM घड़ी */
	ग_लिखो_reg(par, 0x8a, 0x81);
	ग_लिखो_reg(par, 0x8b, 0xFF);
	mdelay(10);

	/* Display ON */
	ग_लिखो_reg(par, 0x01, 0x80);
	mdelay(10);

	वापस 0;
पूर्ण

अटल व्योम set_addr_win(काष्ठा fbtft_par *par, पूर्णांक xs, पूर्णांक ys, पूर्णांक xe, पूर्णांक ye)
अणु
	/* Set_Active_Winकरोw */
	ग_लिखो_reg(par, 0x30, xs & 0x00FF);
	ग_लिखो_reg(par, 0x31, (xs & 0xFF00) >> 8);
	ग_लिखो_reg(par, 0x32, ys & 0x00FF);
	ग_लिखो_reg(par, 0x33, (ys & 0xFF00) >> 8);
	ग_लिखो_reg(par, 0x34, (xs + xe) & 0x00FF);
	ग_लिखो_reg(par, 0x35, ((xs + xe) & 0xFF00) >> 8);
	ग_लिखो_reg(par, 0x36, (ys + ye) & 0x00FF);
	ग_लिखो_reg(par, 0x37, ((ys + ye) & 0xFF00) >> 8);

	/* Set_Memory_Write_Cursor */
	ग_लिखो_reg(par, 0x46,  xs & 0xff);
	ग_लिखो_reg(par, 0x47, (xs >> 8) & 0x03);
	ग_लिखो_reg(par, 0x48,  ys & 0xff);
	ग_लिखो_reg(par, 0x49, (ys >> 8) & 0x01);

	ग_लिखो_reg(par, 0x02);
पूर्ण

अटल व्योम ग_लिखो_reg8_bus8(काष्ठा fbtft_par *par, पूर्णांक len, ...)
अणु
	बहु_सूची args;
	पूर्णांक i, ret;
	u8 *buf = par->buf;

	/* slow करोwn spi-speed क्रम writing रेजिस्टरs */
	par->fbtftops.ग_लिखो = ग_लिखो_spi;

	अगर (unlikely(par->debug & DEBUG_WRITE_REGISTER)) अणु
		बहु_शुरू(args, len);
		क्रम (i = 0; i < len; i++)
			buf[i] = (u8)बहु_तर्क(args, अचिन्हित पूर्णांक);
		बहु_पूर्ण(args);
		fbtft_par_dbg_hex(DEBUG_WRITE_REGISTER, par, par->info->device,
				  u8, buf, len, "%s: ", __func__);
	पूर्ण

	बहु_शुरू(args, len);
	*buf++ = 0x80;
	*buf = (u8)बहु_तर्क(args, अचिन्हित पूर्णांक);
	ret = par->fbtftops.ग_लिखो(par, par->buf, 2);
	अगर (ret < 0) अणु
		बहु_पूर्ण(args);
		dev_err(par->info->device, "write() failed and returned %dn",
			ret);
		वापस;
	पूर्ण
	len--;

	udelay(100);

	अगर (len) अणु
		buf = (u8 *)par->buf;
		*buf++ = 0x00;
		i = len;
		जबतक (i--)
			*buf++ = (u8)बहु_तर्क(args, अचिन्हित पूर्णांक);

		ret = par->fbtftops.ग_लिखो(par, par->buf, len + 1);
		अगर (ret < 0) अणु
			बहु_पूर्ण(args);
			dev_err(par->info->device,
				"write() failed and returned %dn", ret);
			वापस;
		पूर्ण
	पूर्ण
	बहु_पूर्ण(args);

	/* restore user spi-speed */
	par->fbtftops.ग_लिखो = fbtft_ग_लिखो_spi;
	udelay(100);
पूर्ण

अटल पूर्णांक ग_लिखो_vmem16_bus8(काष्ठा fbtft_par *par, माप_प्रकार offset, माप_प्रकार len)
अणु
	u16 *vmem16;
	__be16 *txbuf16;
	माप_प्रकार reमुख्य;
	माप_प्रकार to_copy;
	माप_प्रकार tx_array_size;
	पूर्णांक i;
	पूर्णांक ret = 0;
	माप_प्रकार startbyte_size = 0;

	fbtft_par_dbg(DEBUG_WRITE_VMEM, par, "%s(offset=%zu, len=%zu)\n",
		      __func__, offset, len);

	reमुख्य = len / 2;
	vmem16 = (u16 *)(par->info->screen_buffer + offset);
	tx_array_size = par->txbuf.len / 2;
	txbuf16 = par->txbuf.buf + 1;
	tx_array_size -= 2;
	*(u8 *)(par->txbuf.buf) = 0x00;
	startbyte_size = 1;

	जबतक (reमुख्य) अणु
		to_copy = min(tx_array_size, reमुख्य);
		dev_dbg(par->info->device, "    to_copy=%zu, remain=%zu\n",
			to_copy, reमुख्य - to_copy);

		क्रम (i = 0; i < to_copy; i++)
			txbuf16[i] = cpu_to_be16(vmem16[i]);

		vmem16 = vmem16 + to_copy;
		ret = par->fbtftops.ग_लिखो(par, par->txbuf.buf,
			startbyte_size + to_copy * 2);
		अगर (ret < 0)
			वापस ret;
		reमुख्य -= to_copy;
	पूर्ण

	वापस ret;
पूर्ण

अटल काष्ठा fbtft_display display = अणु
	.regwidth = 8,
	.fbtftops = अणु
		.init_display = init_display,
		.set_addr_win = set_addr_win,
		.ग_लिखो_रेजिस्टर = ग_लिखो_reg8_bus8,
		.ग_लिखो_vmem = ग_लिखो_vmem16_bus8,
		.ग_लिखो = ग_लिखो_spi,
	पूर्ण,
पूर्ण;

FBTFT_REGISTER_DRIVER(DRVNAME, "raio,ra8875", &display);

MODULE_ALIAS("spi:" DRVNAME);
MODULE_ALIAS("platform:" DRVNAME);
MODULE_ALIAS("spi:ra8875");
MODULE_ALIAS("platform:ra8875");

MODULE_DESCRIPTION("FB driver for the RA8875 LCD Controller");
MODULE_AUTHOR("Pf@nne");
MODULE_LICENSE("GPL");
