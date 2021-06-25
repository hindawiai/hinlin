<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * FB driver क्रम Two KS0108 LCD controllers in AGM1264K-FL display
 *
 * Copyright (C) 2014 ololoshka2871
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/delay.h>
#समावेश <linux/slab.h>

#समावेश "fbtft.h"

/* Uncomment text line to use negative image on display */
/*#घोषणा NEGATIVE*/

#घोषणा WHITE		0xff
#घोषणा BLACK		0

#घोषणा DRVNAME		"fb_agm1264k-fl"
#घोषणा WIDTH		64
#घोषणा HEIGHT		64
#घोषणा TOTALWIDTH	(WIDTH * 2)	 /* because 2 x ks0108 in one display */
#घोषणा FPS			20

#घोषणा EPIN		gpio.wr
#घोषणा RS			gpio.dc
#घोषणा RW			gpio.aux[2]
#घोषणा CS0			gpio.aux[0]
#घोषणा CS1			gpio.aux[1]

/* dअगरfusing error (Floyd-Steinberg) */
#घोषणा DIFFUSING_MATRIX_WIDTH	2
#घोषणा DIFFUSING_MATRIX_HEIGHT	2

अटल स्थिर चिन्हित अक्षर
dअगरfusing_matrix[DIFFUSING_MATRIX_WIDTH][DIFFUSING_MATRIX_HEIGHT] = अणु
	अणु-1, 3पूर्ण,
	अणु3, 2पूर्ण,
पूर्ण;

अटल स्थिर अचिन्हित अक्षर gamma_correction_table[] = अणु
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1,
1, 1, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 4, 4, 4, 4, 5, 5, 5, 5, 6,
6, 6, 6, 7, 7, 7, 8, 8, 8, 9, 9, 9, 10, 10, 11, 11, 11, 12, 12, 13,
13, 13, 14, 14, 15, 15, 16, 16, 17, 17, 18, 18, 19, 19, 20, 20, 21,
22, 22, 23, 23, 24, 25, 25, 26, 26, 27, 28, 28, 29, 30, 30, 31, 32,
33, 33, 34, 35, 35, 36, 37, 38, 39, 39, 40, 41, 42, 43, 43, 44, 45,
46, 47, 48, 49, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61,
62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 73, 74, 75, 76, 77, 78, 79, 81,
82, 83, 84, 85, 87, 88, 89, 90, 91, 93, 94, 95, 97, 98, 99, 100, 102,
103, 105, 106, 107, 109, 110, 111, 113, 114, 116, 117, 119, 120, 121,
123, 124, 126, 127, 129, 130, 132, 133, 135, 137, 138, 140, 141, 143,
145, 146, 148, 149, 151, 153, 154, 156, 158, 159, 161, 163, 165, 166,
168, 170, 172, 173, 175, 177, 179, 181, 182, 184, 186, 188, 190, 192,
194, 196, 197, 199, 201, 203, 205, 207, 209, 211, 213, 215, 217, 219,
221, 223, 225, 227, 229, 231, 234, 236, 238, 240, 242, 244, 246, 248,
251, 253, 255
पूर्ण;

अटल पूर्णांक init_display(काष्ठा fbtft_par *par)
अणु
	u8 i;

	par->fbtftops.reset(par);

	क्रम (i = 0; i < 2; ++i) अणु
		ग_लिखो_reg(par, i, 0x3f); /* display on */
		ग_लिखो_reg(par, i, 0x40); /* set x to 0 */
		ग_लिखो_reg(par, i, 0xb0); /* set page to 0 */
		ग_लिखो_reg(par, i, 0xc0); /* set start line to 0 */
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम reset(काष्ठा fbtft_par *par)
अणु
	अगर (!par->gpio.reset)
		वापस;

	dev_dbg(par->info->device, "%s()\n", __func__);

	gpiod_set_value(par->gpio.reset, 0);
	udelay(20);
	gpiod_set_value(par->gpio.reset, 1);
	mdelay(120);
पूर्ण

/* Check अगर all necessary GPIOS defined */
अटल पूर्णांक verअगरy_gpios(काष्ठा fbtft_par *par)
अणु
	पूर्णांक i;

	dev_dbg(par->info->device,
		"%s()\n", __func__);

	अगर (!par->EPIN) अणु
		dev_err(par->info->device,
			"Missing info about 'wr' (aka E) gpio. Aborting.\n");
		वापस -EINVAL;
	पूर्ण
	क्रम (i = 0; i < 8; ++i) अणु
		अगर (!par->gpio.db[i]) अणु
			dev_err(par->info->device,
				"Missing info about 'db[%i]' gpio. Aborting.\n",
				i);
			वापस -EINVAL;
		पूर्ण
	पूर्ण
	अगर (!par->CS0) अणु
		dev_err(par->info->device,
			"Missing info about 'cs0' gpio. Aborting.\n");
		वापस -EINVAL;
	पूर्ण
	अगर (!par->CS1) अणु
		dev_err(par->info->device,
			"Missing info about 'cs1' gpio. Aborting.\n");
		वापस -EINVAL;
	पूर्ण
	अगर (!par->RW) अणु
		dev_err(par->info->device,
			"Missing info about 'rw' gpio. Aborting.\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल अचिन्हित दीर्घ
request_gpios_match(काष्ठा fbtft_par *par, स्थिर काष्ठा fbtft_gpio *gpio)
अणु
	dev_dbg(par->info->device,
		"%s('%s')\n", __func__, gpio->name);

	अगर (strहालcmp(gpio->name, "wr") == 0) अणु
		/* left ks0108 E pin */
		par->EPIN = gpio->gpio;
		वापस GPIOD_OUT_LOW;
	पूर्ण अन्यथा अगर (strहालcmp(gpio->name, "cs0") == 0) अणु
		/* left ks0108 controller pin */
		par->CS0 = gpio->gpio;
		वापस GPIOD_OUT_HIGH;
	पूर्ण अन्यथा अगर (strहालcmp(gpio->name, "cs1") == 0) अणु
		/* right ks0108 controller pin */
		par->CS1 = gpio->gpio;
		वापस GPIOD_OUT_HIGH;
	पूर्ण

	/* अगर ग_लिखो (rw = 0) e(1->0) perक्रमm ग_लिखो */
	/* अगर पढ़ो (rw = 1) e(0->1) set data on D0-7*/
	अन्यथा अगर (strहालcmp(gpio->name, "rw") == 0) अणु
		par->RW = gpio->gpio;
		वापस GPIOD_OUT_LOW;
	पूर्ण

	वापस FBTFT_GPIO_NO_MATCH;
पूर्ण

/* This function oses to enter commands
 * first byte - destination controller 0 or 1
 * following - commands
 */
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

	अगर (*buf > 1) अणु
		बहु_पूर्ण(args);
		dev_err(par->info->device,
			"Incorrect chip select request (%d)\n", *buf);
		वापस;
	पूर्ण

	/* select chip */
	अगर (*buf) अणु
		/* cs1 */
		gpiod_set_value(par->CS0, 1);
		gpiod_set_value(par->CS1, 0);
	पूर्ण अन्यथा अणु
		/* cs0 */
		gpiod_set_value(par->CS0, 0);
		gpiod_set_value(par->CS1, 1);
	पूर्ण

	gpiod_set_value(par->RS, 0); /* RS->0 (command mode) */
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

	बहु_पूर्ण(args);
पूर्ण

अटल काष्ठा
अणु
	पूर्णांक xs, ys_page, xe, ye_page;
पूर्ण addr_win;

/* save display writing zone */
अटल व्योम set_addr_win(काष्ठा fbtft_par *par, पूर्णांक xs, पूर्णांक ys, पूर्णांक xe, पूर्णांक ye)
अणु
	addr_win.xs = xs;
	addr_win.ys_page = ys / 8;
	addr_win.xe = xe;
	addr_win.ye_page = ye / 8;
पूर्ण

अटल व्योम
स्थिरruct_line_biपंचांगap(काष्ठा fbtft_par *par, u8 *dest, चिन्हित लघु *src,
		      पूर्णांक xs, पूर्णांक xe, पूर्णांक y)
अणु
	पूर्णांक x, i;

	क्रम (x = xs; x < xe; ++x) अणु
		u8 res = 0;

		क्रम (i = 0; i < 8; i++)
			अगर (src[(y * 8 + i) * par->info->var.xres + x])
				res |= 1 << i;
#अगर_घोषित NEGATIVE
		*dest++ = res;
#अन्यथा
		*dest++ = ~res;
#पूर्ण_अगर
	पूर्ण
पूर्ण

अटल व्योम iterate_dअगरfusion_matrix(u32 xres, u32 yres, पूर्णांक x,
				     पूर्णांक y, चिन्हित लघु *convert_buf,
				     चिन्हित लघु pixel, चिन्हित लघु error)
अणु
	u16 i, j;

	/* dअगरfusion matrix row */
	क्रम (i = 0; i < DIFFUSING_MATRIX_WIDTH; ++i)
		/* dअगरfusion matrix column */
		क्रम (j = 0; j < DIFFUSING_MATRIX_HEIGHT; ++j) अणु
			चिन्हित लघु *ग_लिखो_pos;
			चिन्हित अक्षर coeff;

			/* skip pixels out of zone */
			अगर (x + i < 0 || x + i >= xres || y + j >= yres)
				जारी;
			ग_लिखो_pos = &convert_buf[(y + j) * xres + x + i];
			coeff = dअगरfusing_matrix[i][j];
			अगर (-1 == coeff) अणु
				/* pixel itself */
				*ग_लिखो_pos = pixel;
			पूर्ण अन्यथा अणु
				चिन्हित लघु p = *ग_लिखो_pos + error * coeff;

				अगर (p > WHITE)
					p = WHITE;
				अगर (p < BLACK)
					p = BLACK;
				*ग_लिखो_pos = p;
			पूर्ण
		पूर्ण
पूर्ण

अटल पूर्णांक ग_लिखो_vmem(काष्ठा fbtft_par *par, माप_प्रकार offset, माप_प्रकार len)
अणु
	u16 *vmem16 = (u16 *)par->info->screen_buffer;
	u8 *buf = par->txbuf.buf;
	पूर्णांक x, y;
	पूर्णांक ret = 0;

	/* buffer to convert RGB565 -> grayscale16 -> Dithered image 1bpp */
	चिन्हित लघु *convert_buf = kदो_स्मृति_array(par->info->var.xres *
		par->info->var.yres, माप(चिन्हित लघु), GFP_NOIO);

	अगर (!convert_buf)
		वापस -ENOMEM;

	/* converting to grayscale16 */
	क्रम (x = 0; x < par->info->var.xres; ++x)
		क्रम (y = 0; y < par->info->var.yres; ++y) अणु
			u16 pixel = vmem16[y *  par->info->var.xres + x];
			u16 b = pixel & 0x1f;
			u16 g = (pixel & (0x3f << 5)) >> 5;
			u16 r = (pixel & (0x1f << (5 + 6))) >> (5 + 6);

			pixel = (299 * r + 587 * g + 114 * b) / 200;
			अगर (pixel > 255)
				pixel = 255;

			/* gamma-correction by table */
			convert_buf[y *  par->info->var.xres + x] =
				(चिन्हित लघु)gamma_correction_table[pixel];
		पूर्ण

	/* Image Dithering */
	क्रम (x = 0; x < par->info->var.xres; ++x)
		क्रम (y = 0; y < par->info->var.yres; ++y) अणु
			चिन्हित लघु pixel =
				convert_buf[y *  par->info->var.xres + x];
			चिन्हित लघु error_b = pixel - BLACK;
			चिन्हित लघु error_w = pixel - WHITE;
			चिन्हित लघु error;

			/* what color बंद? */
			अगर (असल(error_b) >= असल(error_w)) अणु
				/* white */
				error = error_w;
				pixel = 0xff;
			पूर्ण अन्यथा अणु
				/* black */
				error = error_b;
				pixel = 0;
			पूर्ण

			error /= 8;

			iterate_dअगरfusion_matrix(par->info->var.xres,
						 par->info->var.yres,
						 x, y, convert_buf,
						 pixel, error);
		पूर्ण

	/* 1 string = 2 pages */
	क्रम (y = addr_win.ys_page; y <= addr_win.ye_page; ++y) अणु
		/* left half of display */
		अगर (addr_win.xs < par->info->var.xres / 2) अणु
			स्थिरruct_line_biपंचांगap(par, buf, convert_buf,
					      addr_win.xs,
					      par->info->var.xres / 2, y);

			len = par->info->var.xres / 2 - addr_win.xs;

			/* select left side (sc0)
			 * set addr
			 */
			ग_लिखो_reg(par, 0x00, BIT(6) | (u8)addr_win.xs);
			ग_लिखो_reg(par, 0x00, (0x17 << 3) | (u8)y);

			/* ग_लिखो biपंचांगap */
			gpiod_set_value(par->RS, 1); /* RS->1 (data mode) */
			ret = par->fbtftops.ग_लिखो(par, buf, len);
			अगर (ret < 0)
				dev_err(par->info->device,
					"write failed and returned: %d\n",
					ret);
		पूर्ण
		/* right half of display */
		अगर (addr_win.xe >= par->info->var.xres / 2) अणु
			स्थिरruct_line_biपंचांगap(par, buf,
					      convert_buf,
					      par->info->var.xres / 2,
					      addr_win.xe + 1, y);

			len = addr_win.xe + 1 - par->info->var.xres / 2;

			/* select right side (sc1)
			 * set addr
			 */
			ग_लिखो_reg(par, 0x01, BIT(6));
			ग_लिखो_reg(par, 0x01, (0x17 << 3) | (u8)y);

			/* ग_लिखो biपंचांगap */
			gpiod_set_value(par->RS, 1); /* RS->1 (data mode) */
			par->fbtftops.ग_लिखो(par, buf, len);
			अगर (ret < 0)
				dev_err(par->info->device,
					"write failed and returned: %d\n",
					ret);
		पूर्ण
	पूर्ण
	kमुक्त(convert_buf);

	gpiod_set_value(par->CS0, 1);
	gpiod_set_value(par->CS1, 1);

	वापस ret;
पूर्ण

अटल पूर्णांक ग_लिखो(काष्ठा fbtft_par *par, व्योम *buf, माप_प्रकार len)
अणु
	fbtft_par_dbg_hex(DEBUG_WRITE, par, par->info->device, u8, buf, len,
			  "%s(len=%zu): ", __func__, len);

	gpiod_set_value(par->RW, 0); /* set ग_लिखो mode */

	जबतक (len--) अणु
		u8 i, data;

		data = *(u8 *)buf++;

		/* set data bus */
		क्रम (i = 0; i < 8; ++i)
			gpiod_set_value(par->gpio.db[i], data & (1 << i));
		/* set E */
		gpiod_set_value(par->EPIN, 1);
		udelay(5);
		/* unset E - ग_लिखो */
		gpiod_set_value(par->EPIN, 0);
		udelay(1);
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा fbtft_display display = अणु
	.regwidth = 8,
	.width = TOTALWIDTH,
	.height = HEIGHT,
	.fps = FPS,
	.fbtftops = अणु
		.init_display = init_display,
		.set_addr_win = set_addr_win,
		.verअगरy_gpios = verअगरy_gpios,
		.request_gpios_match = request_gpios_match,
		.reset = reset,
		.ग_लिखो = ग_लिखो,
		.ग_लिखो_रेजिस्टर = ग_लिखो_reg8_bus8,
		.ग_लिखो_vmem = ग_लिखो_vmem,
	पूर्ण,
पूर्ण;

FBTFT_REGISTER_DRIVER(DRVNAME, "displaytronic,fb_agm1264k-fl", &display);

MODULE_ALIAS("platform:" DRVNAME);

MODULE_DESCRIPTION("Two KS0108 LCD controllers in AGM1264K-FL display");
MODULE_AUTHOR("ololoshka2871");
MODULE_LICENSE("GPL");
