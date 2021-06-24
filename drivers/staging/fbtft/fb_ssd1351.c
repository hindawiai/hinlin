<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/delay.h>

#समावेश "fbtft.h"

#घोषणा DRVNAME		"fb_ssd1351"
#घोषणा WIDTH		128
#घोषणा HEIGHT		128
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

अटल व्योम रेजिस्टर_onboard_backlight(काष्ठा fbtft_par *par);

अटल पूर्णांक init_display(काष्ठा fbtft_par *par)
अणु
	अगर (par->pdata &&
	    par->pdata->display.backlight == FBTFT_ONBOARD_BACKLIGHT) अणु
		/* module uses onboard GPIO क्रम panel घातer */
		par->fbtftops.रेजिस्टर_backlight = रेजिस्टर_onboard_backlight;
	पूर्ण

	par->fbtftops.reset(par);

	ग_लिखो_reg(par, 0xfd, 0x12); /* Command Lock */
	ग_लिखो_reg(par, 0xfd, 0xb1); /* Command Lock */
	ग_लिखो_reg(par, 0xae); /* Display Off */
	ग_लिखो_reg(par, 0xb3, 0xf1); /* Front Clock Div */
	ग_लिखो_reg(par, 0xca, 0x7f); /* Set Mux Ratio */
	ग_लिखो_reg(par, 0x15, 0x00, 0x7f); /* Set Column Address */
	ग_लिखो_reg(par, 0x75, 0x00, 0x7f); /* Set Row Address */
	ग_लिखो_reg(par, 0xa1, 0x00); /* Set Display Start Line */
	ग_लिखो_reg(par, 0xa2, 0x00); /* Set Display Offset */
	ग_लिखो_reg(par, 0xb5, 0x00); /* Set GPIO */
	ग_लिखो_reg(par, 0xab, 0x01); /* Set Function Selection */
	ग_लिखो_reg(par, 0xb1, 0x32); /* Set Phase Length */
	ग_लिखो_reg(par, 0xb4, 0xa0, 0xb5, 0x55); /* Set Segment Low Voltage */
	ग_लिखो_reg(par, 0xbb, 0x17); /* Set Preअक्षरge Voltage */
	ग_लिखो_reg(par, 0xbe, 0x05); /* Set VComH Voltage */
	ग_लिखो_reg(par, 0xc1, 0xc8, 0x80, 0xc8); /* Set Contrast */
	ग_लिखो_reg(par, 0xc7, 0x0f); /* Set Master Contrast */
	ग_लिखो_reg(par, 0xb6, 0x01); /* Set Second Preअक्षरge Period */
	ग_लिखो_reg(par, 0xa6); /* Set Display Mode Reset */
	ग_लिखो_reg(par, 0xaf); /* Set Sleep Mode Display On */

	वापस 0;
पूर्ण

अटल व्योम set_addr_win(काष्ठा fbtft_par *par, पूर्णांक xs, पूर्णांक ys, पूर्णांक xe, पूर्णांक ye)
अणु
	ग_लिखो_reg(par, 0x15, xs, xe);
	ग_लिखो_reg(par, 0x75, ys, ye);
	ग_लिखो_reg(par, 0x5c);
पूर्ण

अटल पूर्णांक set_var(काष्ठा fbtft_par *par)
अणु
	अचिन्हित पूर्णांक remap;

	अगर (par->fbtftops.init_display != init_display) अणु
		/* करोn't risk messing up रेजिस्टर A0h */
		fbtft_par_dbg(DEBUG_INIT_DISPLAY, par,
			      "%s: skipping since custom init_display() is used\n",
			       __func__);
		वापस 0;
	पूर्ण

	remap = 0x60 | (par->bgr << 2); /* Set Colour Depth */

	चयन (par->info->var.rotate) अणु
	हाल 0:
		ग_लिखो_reg(par, 0xA0, remap | 0x00 | BIT(4));
		अवरोध;
	हाल 270:
		ग_लिखो_reg(par, 0xA0, remap | 0x03 | BIT(4));
		अवरोध;
	हाल 180:
		ग_लिखो_reg(par, 0xA0, remap | 0x02);
		अवरोध;
	हाल 90:
		ग_लिखो_reg(par, 0xA0, remap | 0x01);
		अवरोध;
	पूर्ण

	वापस 0;
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
 *	there are total 180 Gamma Settings (Setting 0 to Setting 180)
 *	available क्रम the Gray Scale table.
 *
 *	The gray scale is defined in incremental way, with reference
 *	to the length of previous table entry:
 *		Setting of GS1 has to be >= 0
 *		Setting of GS2 has to be > Setting of GS1 +1
 *		Setting of GS3 has to be > Setting of GS2 +1
 *		:
 *		Setting of GS63 has to be > Setting of GS62 +1
 *
 */
अटल पूर्णांक set_gamma(काष्ठा fbtft_par *par, u32 *curves)
अणु
	अचिन्हित दीर्घ पंचांगp[GAMMA_NUM * GAMMA_LEN];
	पूर्णांक i, acc = 0;

	क्रम (i = 0; i < 63; i++) अणु
		अगर (i > 0 && curves[i] < 2) अणु
			dev_err(par->info->device,
				"Illegal value in Grayscale Lookup Table at index %d : %d. Must be greater than 1\n",
				i, curves[i]);
			वापस -EINVAL;
		पूर्ण
		acc += curves[i];
		पंचांगp[i] = acc;
		अगर (acc > 180) अणु
			dev_err(par->info->device,
				"Illegal value(s) in Grayscale Lookup Table. At index=%d : %d, the accumulated value has exceeded 180\n",
				i, acc);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	ग_लिखो_reg(par, 0xB8,
		  पंचांगp[0],  पंचांगp[1],  पंचांगp[2],  पंचांगp[3],
		  पंचांगp[4],  पंचांगp[5],  पंचांगp[6],  पंचांगp[7],
		  पंचांगp[8],  पंचांगp[9],  पंचांगp[10], पंचांगp[11],
		  पंचांगp[12], पंचांगp[13], पंचांगp[14], पंचांगp[15],
		  पंचांगp[16], पंचांगp[17], पंचांगp[18], पंचांगp[19],
		  पंचांगp[20], पंचांगp[21], पंचांगp[22], पंचांगp[23],
		  पंचांगp[24], पंचांगp[25], पंचांगp[26], पंचांगp[27],
		  पंचांगp[28], पंचांगp[29], पंचांगp[30], पंचांगp[31],
		  पंचांगp[32], पंचांगp[33], पंचांगp[34], पंचांगp[35],
		  पंचांगp[36], पंचांगp[37], पंचांगp[38], पंचांगp[39],
		  पंचांगp[40], पंचांगp[41], पंचांगp[42], पंचांगp[43],
		  पंचांगp[44], पंचांगp[45], पंचांगp[46], पंचांगp[47],
		  पंचांगp[48], पंचांगp[49], पंचांगp[50], पंचांगp[51],
		  पंचांगp[52], पंचांगp[53], पंचांगp[54], पंचांगp[55],
		  पंचांगp[56], पंचांगp[57], पंचांगp[58], पंचांगp[59],
		  पंचांगp[60], पंचांगp[61], पंचांगp[62]);

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
		.init_display = init_display,
		.set_addr_win = set_addr_win,
		.set_var = set_var,
		.set_gamma = set_gamma,
		.blank = blank,
	पूर्ण,
पूर्ण;

#अगर_घोषित CONFIG_FB_BACKLIGHT
अटल पूर्णांक update_onboard_backlight(काष्ठा backlight_device *bd)
अणु
	काष्ठा fbtft_par *par = bl_get_data(bd);
	bool on;

	fbtft_par_dbg(DEBUG_BACKLIGHT, par,
		      "%s: power=%d, fb_blank=%d\n",
		      __func__, bd->props.घातer, bd->props.fb_blank);

	on = (bd->props.घातer == FB_BLANK_UNBLANK) &&
	     (bd->props.fb_blank == FB_BLANK_UNBLANK);
	/* Onboard backlight connected to GPIO0 on SSD1351, GPIO1 unused */
	ग_लिखो_reg(par, 0xB5, on ? 0x03 : 0x02);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा backlight_ops bl_ops = अणु
	.update_status = update_onboard_backlight,
पूर्ण;

अटल व्योम रेजिस्टर_onboard_backlight(काष्ठा fbtft_par *par)
अणु
	काष्ठा backlight_device *bd;
	काष्ठा backlight_properties bl_props = अणु 0, पूर्ण;

	bl_props.type = BACKLIGHT_RAW;
	bl_props.घातer = FB_BLANK_POWERDOWN;

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
अटल व्योम रेजिस्टर_onboard_backlight(काष्ठा fbtft_par *par) अणु पूर्ण;
#पूर्ण_अगर

FBTFT_REGISTER_DRIVER(DRVNAME, "solomon,ssd1351", &display);

MODULE_ALIAS("spi:" DRVNAME);
MODULE_ALIAS("platform:" DRVNAME);
MODULE_ALIAS("spi:ssd1351");
MODULE_ALIAS("platform:ssd1351");

MODULE_DESCRIPTION("SSD1351 OLED Driver");
MODULE_AUTHOR("James Davies");
MODULE_LICENSE("GPL");
