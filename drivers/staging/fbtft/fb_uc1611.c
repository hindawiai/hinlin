<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * FB driver क्रम the UltraChip UC1611 LCD controller
 *
 * The display is 4-bit grayscale (16 shades) 240x160.
 *
 * Copyright (C) 2015 Henri Chain
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/delay.h>

#समावेश "fbtft.h"

#घोषणा DRVNAME		"fb_uc1611"
#घोषणा WIDTH		240
#घोषणा HEIGHT		160
#घोषणा BPP		8
#घोषणा FPS		40

/*
 * LCD voltage is a combination of ratio, gain, pot and temp
 *
 * V_LCD = V_BIAS * ratio
 * V_LCD = (C_V0 + C_PM थ pot) * (1 + (T - 25) * temp)
 * C_V0 and C_PM depend on ratio and gain
 * T is ambient temperature
 */

/* BR -> actual ratio: 0-3 -> 5, 10, 11, 13 */
अटल अचिन्हित पूर्णांक ratio = 2;
module_param(ratio, uपूर्णांक, 0000);
MODULE_PARM_DESC(ratio, "BR[1:0] Bias voltage ratio: 0-3 (default: 2)");

अटल अचिन्हित पूर्णांक gain = 3;
module_param(gain, uपूर्णांक, 0000);
MODULE_PARM_DESC(gain, "GN[1:0] Bias voltage gain: 0-3 (default: 3)");

अटल अचिन्हित पूर्णांक pot = 16;
module_param(pot, uपूर्णांक, 0000);
MODULE_PARM_DESC(pot, "PM[6:0] Bias voltage pot.: 0-63 (default: 16)");

/* TC -> % compensation per deg C: 0-3 -> -.05, -.10, -.015, -.20 */
अटल अचिन्हित पूर्णांक temp;
module_param(temp, uपूर्णांक, 0000);
MODULE_PARM_DESC(temp, "TC[1:0] Temperature compensation: 0-3 (default: 0)");

/* PC[1:0] -> LCD capacitance: 0-3 -> <20nF, 20-28 nF, 29-40 nF, 40-56 nF */
अटल अचिन्हित पूर्णांक load = 1;
module_param(load, uपूर्णांक, 0000);
MODULE_PARM_DESC(load, "PC[1:0] Panel Loading: 0-3 (default: 1)");

/* PC[3:2] -> V_LCD: 0, 1, 3 -> ext., पूर्णांक. with ratio = 5, पूर्णांक. standard */
अटल अचिन्हित पूर्णांक pump = 3;
module_param(pump, uपूर्णांक, 0000);
MODULE_PARM_DESC(pump, "PC[3:2] Pump control: 0,1,3 (default: 3)");

अटल पूर्णांक init_display(काष्ठा fbtft_par *par)
अणु
	पूर्णांक ret;

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

	/* Reset controller */
	ग_लिखो_reg(par, 0xE2);

	/* Set bias ratio */
	ग_लिखो_reg(par, 0xE8 | (ratio & 0x03));

	/* Set bias gain and potentiometer */
	ग_लिखो_reg(par, 0x81);
	ग_लिखो_reg(par, (gain & 0x03) << 6 | (pot & 0x3F));

	/* Set temperature compensation */
	ग_लिखो_reg(par, 0x24 | (temp & 0x03));

	/* Set panel loading */
	ग_लिखो_reg(par, 0x28 | (load & 0x03));

	/* Set pump control */
	ग_लिखो_reg(par, 0x2C | (pump & 0x03));

	/* Set inverse display */
	ग_लिखो_reg(par, 0xA6 | 0x01);

	/* Set 4-bit grayscale mode */
	ग_लिखो_reg(par, 0xD0 | (0x02 & 0x03));

	/* Set Display enable */
	ग_लिखो_reg(par, 0xA8 | 0x07);

	वापस 0;
पूर्ण

अटल व्योम set_addr_win(काष्ठा fbtft_par *par, पूर्णांक xs, पूर्णांक ys, पूर्णांक xe, पूर्णांक ye)
अणु
	चयन (par->info->var.rotate) अणु
	हाल 90:
	हाल 270:
		/* Set column address */
		ग_लिखो_reg(par, ys & 0x0F);
		ग_लिखो_reg(par, 0x10 | (ys >> 4));

		/* Set page address (भागide xs by 2) (not used by driver) */
		ग_लिखो_reg(par, 0x60 | ((xs >> 1) & 0x0F));
		ग_लिखो_reg(par, 0x70 | (xs >> 5));
		अवरोध;
	शेष:
		/* Set column address (not used by driver) */
		ग_लिखो_reg(par, xs & 0x0F);
		ग_लिखो_reg(par, 0x10 | (xs >> 4));

		/* Set page address (भागide ys by 2) */
		ग_लिखो_reg(par, 0x60 | ((ys >> 1) & 0x0F));
		ग_लिखो_reg(par, 0x70 | (ys >> 5));
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक blank(काष्ठा fbtft_par *par, bool on)
अणु
	fbtft_par_dbg(DEBUG_BLANK, par, "(%s=%s)\n",
		      __func__, on ? "true" : "false");

	अगर (on)
		ग_लिखो_reg(par, 0xA8 | 0x00);
	अन्यथा
		ग_लिखो_reg(par, 0xA8 | 0x07);
	वापस 0;
पूर्ण

अटल पूर्णांक set_var(काष्ठा fbtft_par *par)
अणु
	/* par->info->fix.visual = FB_VISUAL_PSEUDOCOLOR; */
	par->info->var.grayscale = 1;
	par->info->var.red.offset    = 0;
	par->info->var.red.length    = 8;
	par->info->var.green.offset  = 0;
	par->info->var.green.length  = 8;
	par->info->var.blue.offset   = 0;
	par->info->var.blue.length   = 8;
	par->info->var.transp.offset = 0;
	par->info->var.transp.length = 0;

	चयन (par->info->var.rotate) अणु
	हाल 90:
		/* Set RAM address control */
		ग_लिखो_reg(par, 0x88
			| (0x0 & 0x1) << 2 /* Increment positively */
			| (0x1 << 1)	   /* Increment page first */
			| 0x1);		   /* Wrap around (शेष) */

		/* Set LCD mapping */
		ग_लिखो_reg(par, 0xC0
			| (0x0 & 0x1) << 2 /* Mirror Y OFF */
			| (0x0 & 0x1) << 1 /* Mirror X OFF */
			| (0x0 & 0x1));    /* MS nibble last (शेष) */
		अवरोध;
	हाल 180:
		/* Set RAM address control */
		ग_लिखो_reg(par, 0x88
			| (0x0 & 0x1) << 2 /* Increment positively */
			| (0x0 & 0x1) << 1 /* Increment column first */
			| 0x1);		   /* Wrap around (शेष) */

		/* Set LCD mapping */
		ग_लिखो_reg(par, 0xC0
			| (0x1 << 2)	   /* Mirror Y ON */
			| (0x0 & 0x1) << 1 /* Mirror X OFF */
			| (0x0 & 0x1));    /* MS nibble last (शेष) */
		अवरोध;
	हाल 270:
		/* Set RAM address control */
		ग_लिखो_reg(par, 0x88
			| (0x0 & 0x1) << 2 /* Increment positively */
			| (0x1 << 1)	   /* Increment page first */
			| 0x1);		   /* Wrap around (शेष) */

		/* Set LCD mapping */
		ग_लिखो_reg(par, 0xC0
			| (0x1 << 2)	   /* Mirror Y ON */
			| (0x1 << 1)	   /* Mirror X ON */
			| (0x0 & 0x1));    /* MS nibble last (शेष) */
		अवरोध;
	शेष:
		/* Set RAM address control */
		ग_लिखो_reg(par, 0x88
			| (0x0 & 0x1) << 2 /* Increment positively */
			| (0x0 & 0x1) << 1 /* Increment column first */
			| 0x1);		   /* Wrap around (शेष) */

		/* Set LCD mapping */
		ग_लिखो_reg(par, 0xC0
			| (0x0 & 0x1) << 2 /* Mirror Y OFF */
			| (0x1 << 1)	   /* Mirror X ON */
			| (0x0 & 0x1));    /* MS nibble last (शेष) */
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ग_लिखो_vmem(काष्ठा fbtft_par *par, माप_प्रकार offset, माप_प्रकार len)
अणु
	u8 *vmem8 = (u8 *)(par->info->screen_buffer);
	u8 *buf8 = par->txbuf.buf;
	u16 *buf16 = par->txbuf.buf;
	पूर्णांक line_length = par->info->fix.line_length;
	पूर्णांक y_start = offset / line_length;
	पूर्णांक y_end = (offset + len - 1) / line_length;
	पूर्णांक x, y, i;
	पूर्णांक ret = 0;

	चयन (par->pdata->display.buswidth) अणु
	हाल 8:
		चयन (par->info->var.rotate) अणु
		हाल 90:
		हाल 270:
			i = y_start * line_length;
			क्रम (y = y_start; y <= y_end; y++) अणु
				क्रम (x = 0; x < line_length; x += 2) अणु
					*buf8 = vmem8[i] >> 4;
					*buf8 |= vmem8[i + 1] & 0xF0;
					buf8++;
					i += 2;
				पूर्ण
			पूर्ण
			अवरोध;
		शेष:
			/* Must be even because pages are two lines */
			y_start &= 0xFE;
			i = y_start * line_length;
			क्रम (y = y_start; y <= y_end; y += 2) अणु
				क्रम (x = 0; x < line_length; x++) अणु
					*buf8 = vmem8[i] >> 4;
					*buf8 |= vmem8[i + line_length] & 0xF0;
					buf8++;
					i++;
				पूर्ण
				i += line_length;
			पूर्ण
			अवरोध;
		पूर्ण
		gpiod_set_value(par->gpio.dc, 1);

		/* Write data */
		ret = par->fbtftops.ग_लिखो(par, par->txbuf.buf, len / 2);
		अवरोध;
	हाल 9:
		चयन (par->info->var.rotate) अणु
		हाल 90:
		हाल 270:
			i = y_start * line_length;
			क्रम (y = y_start; y <= y_end; y++) अणु
				क्रम (x = 0; x < line_length; x += 2) अणु
					*buf16 = 0x100;
					*buf16 |= vmem8[i] >> 4;
					*buf16 |= vmem8[i + 1] & 0xF0;
					buf16++;
					i += 2;
				पूर्ण
			पूर्ण
			अवरोध;
		शेष:
			/* Must be even because pages are two lines */
			y_start &= 0xFE;
			i = y_start * line_length;
			क्रम (y = y_start; y <= y_end; y += 2) अणु
				क्रम (x = 0; x < line_length; x++) अणु
					*buf16 = 0x100;
					*buf16 |= vmem8[i] >> 4;
					*buf16 |= vmem8[i + line_length] & 0xF0;
					buf16++;
					i++;
				पूर्ण
				i += line_length;
			पूर्ण
			अवरोध;
		पूर्ण

		/* Write data */
		ret = par->fbtftops.ग_लिखो(par, par->txbuf.buf, len);
		अवरोध;
	शेष:
		dev_err(par->info->device, "unsupported buswidth %d\n",
			par->pdata->display.buswidth);
	पूर्ण

	अगर (ret < 0)
		dev_err(par->info->device, "write failed and returned: %d\n",
			ret);

	वापस ret;
पूर्ण

अटल काष्ठा fbtft_display display = अणु
	.txbuflen = -1,
	.regwidth = 8,
	.width = WIDTH,
	.height = HEIGHT,
	.bpp = BPP,
	.fps = FPS,
	.fbtftops = अणु
		.ग_लिखो_vmem = ग_लिखो_vmem,
		.init_display = init_display,
		.set_addr_win = set_addr_win,
		.set_var = set_var,
		.blank = blank,
	पूर्ण,
पूर्ण;

FBTFT_REGISTER_DRIVER(DRVNAME, "ultrachip,uc1611", &display);

MODULE_ALIAS("spi:" DRVNAME);
MODULE_ALIAS("platform:" DRVNAME);
MODULE_ALIAS("spi:uc1611");
MODULE_ALIAS("platform:uc1611");

MODULE_DESCRIPTION("FB driver for the UC1611 LCD controller");
MODULE_AUTHOR("Henri Chain");
MODULE_LICENSE("GPL");
