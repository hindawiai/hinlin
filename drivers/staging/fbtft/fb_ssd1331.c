<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/delay.h>

#समावेश "fbtft.h"

#घोषणा DRVNAME		"fb_ssd1331"
#घोषणा WIDTH		96
#घोषणा HEIGHT		64
#घोषणा GAMMA_NUM	1
#घोषणा GAMMA_LEN	63
#घोषणा DEFAULT_GAMMA	"0 2 2 2 2 2 2 2 " \
			"2 2 2 2 2 2 2 2 " \
			"2 2 2 2 2 2 2 2 " \
			"2 2 2 2 2 2 2 2 " \
			"2 2 2 2 2 2 2 2 " \
			"2 2 2 2 2 2 2 2 " \
			"2 2 2 2 2 2 2 2 " \
			"2 2 2 2 2 2 2" \

अटल पूर्णांक init_display(काष्ठा fbtft_par *par)
अणु
	par->fbtftops.reset(par);

	ग_लिखो_reg(par, 0xae); /* Display Off */

	/* Set Column Address Mapping, COM Scan Direction and Colour Depth */
	अगर (par->info->var.rotate == 180)
		ग_लिखो_reg(par, 0xa0, 0x60 | (par->bgr << 2));
	अन्यथा
		ग_लिखो_reg(par, 0xa0, 0x72 | (par->bgr << 2));

	ग_लिखो_reg(par, 0x72); /* RGB colour */
	ग_लिखो_reg(par, 0xa1, 0x00); /* Set Display Start Line */
	ग_लिखो_reg(par, 0xa2, 0x00); /* Set Display Offset */
	ग_लिखो_reg(par, 0xa4); /* NORMALDISPLAY */
	ग_लिखो_reg(par, 0xa8, 0x3f); /* Set multiplex */
	ग_लिखो_reg(par, 0xad, 0x8e); /* Set master */
	/* ग_लिखो_reg(par, 0xb0, 0x0b);  Set घातer mode */
	ग_लिखो_reg(par, 0xb1, 0x31); /* Preअक्षरge */
	ग_लिखो_reg(par, 0xb3, 0xf0); /* Clock भाग */
	ग_लिखो_reg(par, 0x8a, 0x64); /* Preअक्षरge A */
	ग_लिखो_reg(par, 0x8b, 0x78); /* Preअक्षरge B */
	ग_लिखो_reg(par, 0x8c, 0x64); /* Preअक्षरge C */
	ग_लिखो_reg(par, 0xbb, 0x3a); /* Preअक्षरge level */
	ग_लिखो_reg(par, 0xbe, 0x3e); /* vcomh */
	ग_लिखो_reg(par, 0x87, 0x06); /* Master current */
	ग_लिखो_reg(par, 0x81, 0x91); /* Contrast A */
	ग_लिखो_reg(par, 0x82, 0x50); /* Contrast B */
	ग_लिखो_reg(par, 0x83, 0x7d); /* Contrast C */
	ग_लिखो_reg(par, 0xaf); /* Set Sleep Mode Display On */

	वापस 0;
पूर्ण

अटल व्योम set_addr_win(काष्ठा fbtft_par *par, पूर्णांक xs, पूर्णांक ys, पूर्णांक xe, पूर्णांक ye)
अणु
	ग_लिखो_reg(par, 0x15, xs, xe);
	ग_लिखो_reg(par, 0x75, ys, ye);
पूर्ण

अटल व्योम ग_लिखो_reg8_bus8(काष्ठा fbtft_par *par, पूर्णांक len, ...)
अणु
	बहु_सूची args;
	पूर्णांक i, ret;
	u8 *buf = par->buf;

	अगर (unlikely(par->debug & DEBUG_WRITE_REGISTER)) अणु
		बहु_शुरू(args, len);
		क्रम (i = 0; i < len; i++)
			buf[i] = (u8)बहु_तर्क(args, अचिन्हित पूर्णांक);
		बहु_पूर्ण(args);
		fbtft_par_dbg_hex(DEBUG_WRITE_REGISTER, par, par->info->device,
				  u8, buf, len, "%s: ", __func__);
	पूर्ण

	बहु_शुरू(args, len);

	*buf = (u8)बहु_तर्क(args, अचिन्हित पूर्णांक);
	अगर (par->gpio.dc)
		gpiod_set_value(par->gpio.dc, 0);
	ret = par->fbtftops.ग_लिखो(par, par->buf, माप(u8));
	अगर (ret < 0) अणु
		बहु_पूर्ण(args);
		dev_err(par->info->device,
			"write() failed and returned %d\n", ret);
		वापस;
	पूर्ण
	len--;

	अगर (len) अणु
		i = len;
		जबतक (i--)
			*buf++ = (u8)बहु_तर्क(args, अचिन्हित पूर्णांक);
		ret = par->fbtftops.ग_लिखो(par, par->buf, len * (माप(u8)));
		अगर (ret < 0) अणु
			बहु_पूर्ण(args);
			dev_err(par->info->device,
				"write() failed and returned %d\n", ret);
			वापस;
		पूर्ण
	पूर्ण
	अगर (par->gpio.dc)
		gpiod_set_value(par->gpio.dc, 1);
	बहु_पूर्ण(args);
पूर्ण

/*
 * Grayscale Lookup Table
 * GS1 - GS63
 * The driver Gamma curve contains the relative values between the entries
 * in the Lookup table.
 *
 * From datasheet:
 * 8.8 Gray Scale Decoder
 *
 * there are total 180 Gamma Settings (Setting 0 to Setting 180)
 * available क्रम the Gray Scale table.
 *
 * The gray scale is defined in incremental way, with reference
 * to the length of previous table entry:
 * Setting of GS1 has to be >= 0
 * Setting of GS2 has to be > Setting of GS1 +1
 * Setting of GS3 has to be > Setting of GS2 +1
 * :
 * Setting of GS63 has to be > Setting of GS62 +1
 *
 */
अटल पूर्णांक set_gamma(काष्ठा fbtft_par *par, u32 *curves)
अणु
	अचिन्हित दीर्घ पंचांगp[GAMMA_NUM * GAMMA_LEN];
	पूर्णांक i, acc = 0;

	क्रम (i = 0; i < 63; i++) अणु
		अगर (i > 0 && curves[i] < 2) अणु
			dev_err(par->info->device,
				"Illegal value in Grayscale Lookup Table at index %d. Must be greater than 1\n",
				i);
			वापस -EINVAL;
		पूर्ण
		acc += curves[i];
		पंचांगp[i] = acc;
		अगर (acc > 180) अणु
			dev_err(par->info->device,
				"Illegal value(s) in Grayscale Lookup Table. At index=%d, the accumulated value has exceeded 180\n",
				i);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	ग_लिखो_reg(par, 0xB8,
		  पंचांगp[0], पंचांगp[1], पंचांगp[2], पंचांगp[3], पंचांगp[4], पंचांगp[5], पंचांगp[6],
		  पंचांगp[7], पंचांगp[8], पंचांगp[9], पंचांगp[10], पंचांगp[11], पंचांगp[12], पंचांगp[13],
		  पंचांगp[14], पंचांगp[15], पंचांगp[16], पंचांगp[17], पंचांगp[18], पंचांगp[19], पंचांगp[20],
		  पंचांगp[21], पंचांगp[22], पंचांगp[23], पंचांगp[24], पंचांगp[25], पंचांगp[26],	पंचांगp[27],
		  पंचांगp[28], पंचांगp[29], पंचांगp[30], पंचांगp[31], पंचांगp[32], पंचांगp[33], पंचांगp[34],
		  पंचांगp[35], पंचांगp[36], पंचांगp[37], पंचांगp[38], पंचांगp[39], पंचांगp[40], पंचांगp[41],
		  पंचांगp[42], पंचांगp[43], पंचांगp[44], पंचांगp[45], पंचांगp[46], पंचांगp[47], पंचांगp[48],
		  पंचांगp[49], पंचांगp[50], पंचांगp[51], पंचांगp[52], पंचांगp[53], पंचांगp[54], पंचांगp[55],
		  पंचांगp[56], पंचांगp[57], पंचांगp[58], पंचांगp[59], पंचांगp[60], पंचांगp[61],
		  पंचांगp[62]);

	वापस 0;
पूर्ण

अटल पूर्णांक blank(काष्ठा fbtft_par *par, bool on)
अणु
	fbtft_par_dbg(DEBUG_BLANK, par, "(%s=%s)\n",
		      __func__, on ? "true" : "false");
	अगर (on)
		ग_लिखो_reg(par, 0xAE);
	अन्यथा
		ग_लिखो_reg(par, 0xAF);
	वापस 0;
पूर्ण

अटल काष्ठा fbtft_display display = अणु
	.regwidth = 8,
	.width = WIDTH,
	.height = HEIGHT,
	.gamma_num = GAMMA_NUM,
	.gamma_len = GAMMA_LEN,
	.gamma = DEFAULT_GAMMA,
	.fbtftops = अणु
		.ग_लिखो_रेजिस्टर = ग_लिखो_reg8_bus8,
		.init_display = init_display,
		.set_addr_win = set_addr_win,
		.set_gamma = set_gamma,
		.blank = blank,
	पूर्ण,
पूर्ण;

FBTFT_REGISTER_DRIVER(DRVNAME, "solomon,ssd1331", &display);

MODULE_ALIAS("spi:" DRVNAME);
MODULE_ALIAS("platform:" DRVNAME);
MODULE_ALIAS("spi:ssd1331");
MODULE_ALIAS("platform:ssd1331");

MODULE_DESCRIPTION("SSD1331 OLED Driver");
MODULE_AUTHOR("Alec Smecher (adapted from SSD1351 by James Davies)");
MODULE_LICENSE("GPL");
