<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * FB driver क्रम the ST7789V LCD Controller
 *
 * Copyright (C) 2015 Dennis Menschel
 */

#समावेश <linux/bitops.h>
#समावेश <linux/delay.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/completion.h>
#समावेश <linux/module.h>

#समावेश <video/mipi_display.h>

#समावेश "fbtft.h"

#घोषणा DRVNAME "fb_st7789v"

#घोषणा DEFAULT_GAMMA \
	"70 2C 2E 15 10 09 48 33 53 0B 19 18 20 25\n" \
	"70 2C 2E 15 10 09 48 33 53 0B 19 18 20 25"

#घोषणा HSD20_IPS_GAMMA \
	"D0 05 0A 09 08 05 2E 44 45 0F 17 16 2B 33\n" \
	"D0 05 0A 09 08 05 2E 43 45 0F 16 16 2B 33"

#घोषणा HSD20_IPS 1

/**
 * क्रमागत st7789v_command - ST7789V display controller commands
 *
 * @PORCTRL: porch setting
 * @GCTRL: gate control
 * @VCOMS: VCOM setting
 * @VDVVRHEN: VDV and VRH command enable
 * @VRHS: VRH set
 * @VDVS: VDV set
 * @VCMOFSET: VCOM offset set
 * @PWCTRL1: घातer control 1
 * @PVGAMCTRL: positive voltage gamma control
 * @NVGAMCTRL: negative voltage gamma control
 *
 * The command names are the same as those found in the datasheet to ease
 * looking up their semantics and usage.
 *
 * Note that the ST7789V display controller offers quite a few more commands
 * which have been omitted from this list as they are not used at the moment.
 * Furthermore, commands that are compliant with the MIPI DCS have been left
 * out as well to aव्योम duplicate entries.
 */
क्रमागत st7789v_command अणु
	PORCTRL = 0xB2,
	GCTRL = 0xB7,
	VCOMS = 0xBB,
	VDVVRHEN = 0xC2,
	VRHS = 0xC3,
	VDVS = 0xC4,
	VCMOFSET = 0xC5,
	PWCTRL1 = 0xD0,
	PVGAMCTRL = 0xE0,
	NVGAMCTRL = 0xE1,
पूर्ण;

#घोषणा MADCTL_BGR BIT(3) /* biपंचांगask क्रम RGB/BGR order */
#घोषणा MADCTL_MV BIT(5) /* biपंचांगask क्रम page/column order */
#घोषणा MADCTL_MX BIT(6) /* biपंचांगask क्रम column address order */
#घोषणा MADCTL_MY BIT(7) /* biपंचांगask क्रम page address order */

/* 60Hz क्रम 16.6ms, configured as 2*16.6ms */
#घोषणा PANEL_TE_TIMEOUT_MS  33

अटल काष्ठा completion panel_te; /* completion क्रम panel TE line */
अटल पूर्णांक irq_te; /* Linux IRQ क्रम LCD TE line */

अटल irqवापस_t panel_te_handler(पूर्णांक irq, व्योम *data)
अणु
	complete(&panel_te);
	वापस IRQ_HANDLED;
पूर्ण

/*
 * init_tearing_effect_line() - init tearing effect line.
 * @par: FBTFT parameter object.
 *
 * Return: 0 on success, or a negative error code otherwise.
 */
अटल पूर्णांक init_tearing_effect_line(काष्ठा fbtft_par *par)
अणु
	काष्ठा device *dev = par->info->device;
	काष्ठा gpio_desc *te;
	पूर्णांक rc, irq;

	te = gpiod_get_optional(dev, "te", GPIOD_IN);
	अगर (IS_ERR(te))
		वापस dev_err_probe(dev, PTR_ERR(te), "Failed to request te GPIO\n");

	/* अगर te is शून्य, indicating no configuration, directly वापस success */
	अगर (!te) अणु
		irq_te = 0;
		वापस 0;
	पूर्ण

	irq = gpiod_to_irq(te);

	/* GPIO is locked as an IRQ, we may drop the reference */
	gpiod_put(te);

	अगर (irq < 0)
		वापस irq;

	irq_te = irq;
	init_completion(&panel_te);

	/* The effective state is high and lasts no more than 1000 microseconds */
	rc = devm_request_irq(dev, irq_te, panel_te_handler,
			      IRQF_TRIGGER_RISING, "TE_GPIO", par);
	अगर (rc)
		वापस dev_err_probe(dev, rc, "TE IRQ request failed.\n");

	disable_irq_nosync(irq_te);

	वापस 0;
पूर्ण

/**
 * init_display() - initialize the display controller
 *
 * @par: FBTFT parameter object
 *
 * Most of the commands in this init function set their parameters to the
 * same शेष values which are alपढ़ोy in place after the display has been
 * घातered up. (The मुख्य exception to this rule is the pixel क्रमmat which
 * would शेष to 18 instead of 16 bit per pixel.)
 * Nonetheless, this sequence can be used as a ढाँचा क्रम concrete
 * displays which usually need some adjusपंचांगents.
 *
 * Return: 0 on success, < 0 अगर error occurred.
 */
अटल पूर्णांक init_display(काष्ठा fbtft_par *par)
अणु
	पूर्णांक rc;

	rc = init_tearing_effect_line(par);
	अगर (rc)
		वापस rc;

	/* turn off sleep mode */
	ग_लिखो_reg(par, MIPI_DCS_EXIT_SLEEP_MODE);
	mdelay(120);

	/* set pixel क्रमmat to RGB-565 */
	ग_लिखो_reg(par, MIPI_DCS_SET_PIXEL_FORMAT, MIPI_DCS_PIXEL_FMT_16BIT);
	अगर (HSD20_IPS)
		ग_लिखो_reg(par, PORCTRL, 0x05, 0x05, 0x00, 0x33, 0x33);

	अन्यथा
		ग_लिखो_reg(par, PORCTRL, 0x08, 0x08, 0x00, 0x22, 0x22);

	/*
	 * VGH = 13.26V
	 * VGL = -10.43V
	 */
	अगर (HSD20_IPS)
		ग_लिखो_reg(par, GCTRL, 0x75);
	अन्यथा
		ग_लिखो_reg(par, GCTRL, 0x35);

	/*
	 * VDV and VRH रेजिस्टर values come from command ग_लिखो
	 * (instead of NVM)
	 */
	ग_लिखो_reg(par, VDVVRHEN, 0x01, 0xFF);

	/*
	 * VAP =  4.1V + (VCOM + VCOM offset + 0.5 * VDV)
	 * VAN = -4.1V + (VCOM + VCOM offset + 0.5 * VDV)
	 */
	अगर (HSD20_IPS)
		ग_लिखो_reg(par, VRHS, 0x13);
	अन्यथा
		ग_लिखो_reg(par, VRHS, 0x0B);

	/* VDV = 0V */
	ग_लिखो_reg(par, VDVS, 0x20);

	/* VCOM = 0.9V */
	अगर (HSD20_IPS)
		ग_लिखो_reg(par, VCOMS, 0x22);
	अन्यथा
		ग_लिखो_reg(par, VCOMS, 0x20);

	/* VCOM offset = 0V */
	ग_लिखो_reg(par, VCMOFSET, 0x20);

	/*
	 * AVDD = 6.8V
	 * AVCL = -4.8V
	 * VDS = 2.3V
	 */
	ग_लिखो_reg(par, PWCTRL1, 0xA4, 0xA1);

	/* TE line output is off by शेष when घातering on */
	अगर (irq_te)
		ग_लिखो_reg(par, MIPI_DCS_SET_TEAR_ON, 0x00);

	ग_लिखो_reg(par, MIPI_DCS_SET_DISPLAY_ON);

	अगर (HSD20_IPS)
		ग_लिखो_reg(par, MIPI_DCS_ENTER_INVERT_MODE);

	वापस 0;
पूर्ण

/*
 * ग_लिखो_vmem() - ग_लिखो data to display.
 * @par: FBTFT parameter object.
 * @offset: offset from screen_buffer.
 * @len: the length of data to be writte.
 *
 * Return: 0 on success, or a negative error code otherwise.
 */
अटल पूर्णांक ग_लिखो_vmem(काष्ठा fbtft_par *par, माप_प्रकार offset, माप_प्रकार len)
अणु
	काष्ठा device *dev = par->info->device;
	पूर्णांक ret;

	अगर (irq_te) अणु
		enable_irq(irq_te);
		reinit_completion(&panel_te);
		ret = रुको_क्रम_completion_समयout(&panel_te,
						  msecs_to_jअगरfies(PANEL_TE_TIMEOUT_MS));
		अगर (ret == 0)
			dev_err(dev, "wait panel TE timeout\n");

		disable_irq(irq_te);
	पूर्ण

	चयन (par->pdata->display.buswidth) अणु
	हाल 8:
		ret = fbtft_ग_लिखो_vmem16_bus8(par, offset, len);
		अवरोध;
	हाल 9:
		ret = fbtft_ग_लिखो_vmem16_bus9(par, offset, len);
		अवरोध;
	हाल 16:
		ret = fbtft_ग_लिखो_vmem16_bus16(par, offset, len);
		अवरोध;
	शेष:
		dev_err(dev, "Unsupported buswidth %d\n",
			par->pdata->display.buswidth);
		ret = 0;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

/**
 * set_var() - apply LCD properties like rotation and BGR mode
 *
 * @par: FBTFT parameter object
 *
 * Return: 0 on success, < 0 अगर error occurred.
 */
अटल पूर्णांक set_var(काष्ठा fbtft_par *par)
अणु
	u8 madctl_par = 0;

	अगर (par->bgr)
		madctl_par |= MADCTL_BGR;
	चयन (par->info->var.rotate) अणु
	हाल 0:
		अवरोध;
	हाल 90:
		madctl_par |= (MADCTL_MV | MADCTL_MY);
		अवरोध;
	हाल 180:
		madctl_par |= (MADCTL_MX | MADCTL_MY);
		अवरोध;
	हाल 270:
		madctl_par |= (MADCTL_MV | MADCTL_MX);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	ग_लिखो_reg(par, MIPI_DCS_SET_ADDRESS_MODE, madctl_par);
	वापस 0;
पूर्ण

/**
 * set_gamma() - set gamma curves
 *
 * @par: FBTFT parameter object
 * @curves: gamma curves
 *
 * Beक्रमe the gamma curves are applied, they are preprocessed with a biपंचांगask
 * to ensure syntactically correct input क्रम the display controller.
 * This implies that the curves input parameter might be changed by this
 * function and that illegal gamma values are स्वतः-corrected and not
 * reported as errors.
 *
 * Return: 0 on success, < 0 अगर error occurred.
 */
अटल पूर्णांक set_gamma(काष्ठा fbtft_par *par, u32 *curves)
अणु
	पूर्णांक i;
	पूर्णांक j;
	पूर्णांक c; /* curve index offset */

	/*
	 * Biपंचांगasks क्रम gamma curve command parameters.
	 * The masks are the same क्रम both positive and negative voltage
	 * gamma curves.
	 */
	अटल स्थिर u8 gamma_par_mask[] = अणु
		0xFF, /* V63[3:0], V0[3:0]*/
		0x3F, /* V1[5:0] */
		0x3F, /* V2[5:0] */
		0x1F, /* V4[4:0] */
		0x1F, /* V6[4:0] */
		0x3F, /* J0[1:0], V13[3:0] */
		0x7F, /* V20[6:0] */
		0x77, /* V36[2:0], V27[2:0] */
		0x7F, /* V43[6:0] */
		0x3F, /* J1[1:0], V50[3:0] */
		0x1F, /* V57[4:0] */
		0x1F, /* V59[4:0] */
		0x3F, /* V61[5:0] */
		0x3F, /* V62[5:0] */
	पूर्ण;

	क्रम (i = 0; i < par->gamma.num_curves; i++) अणु
		c = i * par->gamma.num_values;
		क्रम (j = 0; j < par->gamma.num_values; j++)
			curves[c + j] &= gamma_par_mask[j];
		ग_लिखो_reg(par, PVGAMCTRL + i,
			  curves[c + 0],  curves[c + 1],  curves[c + 2],
			  curves[c + 3],  curves[c + 4],  curves[c + 5],
			  curves[c + 6],  curves[c + 7],  curves[c + 8],
			  curves[c + 9],  curves[c + 10], curves[c + 11],
			  curves[c + 12], curves[c + 13]);
	पूर्ण
	वापस 0;
पूर्ण

/**
 * blank() - blank the display
 *
 * @par: FBTFT parameter object
 * @on: whether to enable or disable blanking the display
 *
 * Return: 0 on success, < 0 अगर error occurred.
 */
अटल पूर्णांक blank(काष्ठा fbtft_par *par, bool on)
अणु
	अगर (on)
		ग_लिखो_reg(par, MIPI_DCS_SET_DISPLAY_OFF);
	अन्यथा
		ग_लिखो_reg(par, MIPI_DCS_SET_DISPLAY_ON);
	वापस 0;
पूर्ण

अटल काष्ठा fbtft_display display = अणु
	.regwidth = 8,
	.width = 240,
	.height = 320,
	.gamma_num = 2,
	.gamma_len = 14,
	.gamma = HSD20_IPS_GAMMA,
	.fbtftops = अणु
		.init_display = init_display,
		.ग_लिखो_vmem = ग_लिखो_vmem,
		.set_var = set_var,
		.set_gamma = set_gamma,
		.blank = blank,
	पूर्ण,
पूर्ण;

FBTFT_REGISTER_DRIVER(DRVNAME, "sitronix,st7789v", &display);

MODULE_ALIAS("spi:" DRVNAME);
MODULE_ALIAS("platform:" DRVNAME);
MODULE_ALIAS("spi:st7789v");
MODULE_ALIAS("platform:st7789v");

MODULE_DESCRIPTION("FB driver for the ST7789V LCD Controller");
MODULE_AUTHOR("Dennis Menschel");
MODULE_LICENSE("GPL");
