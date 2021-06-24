<शैली गुरु>
/*
 *  linux/drivers/video/tgafb.c -- DEC 21030 TGA frame buffer device
 *
 *	Copyright (C) 1995 Jay Estabrook
 *	Copyright (C) 1997 Geert Uytterhoeven
 *	Copyright (C) 1999,2000 Martin Lucina, Tom Zerucha
 *	Copyright (C) 2002 Riअक्षरd Henderson
 *	Copyright (C) 2006, 2007  Maciej W. Rozycki
 *
 *  This file is subject to the terms and conditions of the GNU General Public
 *  License. See the file COPYING in the मुख्य directory of this archive क्रम
 *  more details.
 */

#समावेश <linux/bitrev.h>
#समावेश <linux/compiler.h>
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/fb.h>
#समावेश <linux/init.h>
#समावेश <linux/ioport.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/selection.h>
#समावेश <linux/माला.स>
#समावेश <linux/tc.h>

#समावेश <यंत्र/पन.स>

#समावेश <video/tgafb.h>

#अगर_घोषित CONFIG_TC
#घोषणा TGA_BUS_TC(dev) (dev->bus == &tc_bus_type)
#अन्यथा
#घोषणा TGA_BUS_TC(dev) 0
#पूर्ण_अगर

/*
 * Local functions.
 */

अटल पूर्णांक tgafb_check_var(काष्ठा fb_var_screeninfo *, काष्ठा fb_info *);
अटल पूर्णांक tgafb_set_par(काष्ठा fb_info *);
अटल व्योम tgafb_set_pll(काष्ठा tga_par *, पूर्णांक);
अटल पूर्णांक tgafb_setcolreg(अचिन्हित, अचिन्हित, अचिन्हित, अचिन्हित,
			   अचिन्हित, काष्ठा fb_info *);
अटल पूर्णांक tgafb_blank(पूर्णांक, काष्ठा fb_info *);
अटल व्योम tgafb_init_fix(काष्ठा fb_info *);

अटल व्योम tgafb_imageblit(काष्ठा fb_info *, स्थिर काष्ठा fb_image *);
अटल व्योम tgafb_fillrect(काष्ठा fb_info *, स्थिर काष्ठा fb_fillrect *);
अटल व्योम tgafb_copyarea(काष्ठा fb_info *, स्थिर काष्ठा fb_copyarea *);
अटल पूर्णांक tgafb_pan_display(काष्ठा fb_var_screeninfo *var, काष्ठा fb_info *info);

अटल पूर्णांक tgafb_रेजिस्टर(काष्ठा device *dev);
अटल व्योम tgafb_unरेजिस्टर(काष्ठा device *dev);

अटल स्थिर अक्षर *mode_option;
अटल स्थिर अक्षर *mode_option_pci = "640x480@60";
अटल स्थिर अक्षर *mode_option_tc = "1280x1024@72";


अटल काष्ठा pci_driver tgafb_pci_driver;
अटल काष्ठा tc_driver tgafb_tc_driver;

/*
 *  Frame buffer operations
 */

अटल स्थिर काष्ठा fb_ops tgafb_ops = अणु
	.owner			= THIS_MODULE,
	.fb_check_var		= tgafb_check_var,
	.fb_set_par		= tgafb_set_par,
	.fb_setcolreg		= tgafb_setcolreg,
	.fb_blank		= tgafb_blank,
	.fb_pan_display		= tgafb_pan_display,
	.fb_fillrect		= tgafb_fillrect,
	.fb_copyarea		= tgafb_copyarea,
	.fb_imageblit		= tgafb_imageblit,
पूर्ण;


#अगर_घोषित CONFIG_PCI
/*
 *  PCI registration operations
 */
अटल पूर्णांक tgafb_pci_रेजिस्टर(काष्ठा pci_dev *, स्थिर काष्ठा pci_device_id *);
अटल व्योम tgafb_pci_unरेजिस्टर(काष्ठा pci_dev *);

अटल काष्ठा pci_device_id स्थिर tgafb_pci_table[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_DEC, PCI_DEVICE_ID_DEC_TGA) पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, tgafb_pci_table);

अटल काष्ठा pci_driver tgafb_pci_driver = अणु
	.name			= "tgafb",
	.id_table		= tgafb_pci_table,
	.probe			= tgafb_pci_रेजिस्टर,
	.हटाओ			= tgafb_pci_unरेजिस्टर,
पूर्ण;

अटल पूर्णांक tgafb_pci_रेजिस्टर(काष्ठा pci_dev *pdev,
			      स्थिर काष्ठा pci_device_id *ent)
अणु
	वापस tgafb_रेजिस्टर(&pdev->dev);
पूर्ण

अटल व्योम tgafb_pci_unरेजिस्टर(काष्ठा pci_dev *pdev)
अणु
	tgafb_unरेजिस्टर(&pdev->dev);
पूर्ण
#पूर्ण_अगर /* CONFIG_PCI */

#अगर_घोषित CONFIG_TC
/*
 *  TC registration operations
 */
अटल पूर्णांक tgafb_tc_रेजिस्टर(काष्ठा device *);
अटल पूर्णांक tgafb_tc_unरेजिस्टर(काष्ठा device *);

अटल काष्ठा tc_device_id स्थिर tgafb_tc_table[] = अणु
	अणु "DEC     ", "PMAGD-AA" पूर्ण,
	अणु "DEC     ", "PMAGD   " पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(tc, tgafb_tc_table);

अटल काष्ठा tc_driver tgafb_tc_driver = अणु
	.id_table		= tgafb_tc_table,
	.driver			= अणु
		.name		= "tgafb",
		.bus		= &tc_bus_type,
		.probe		= tgafb_tc_रेजिस्टर,
		.हटाओ		= tgafb_tc_unरेजिस्टर,
	पूर्ण,
पूर्ण;

अटल पूर्णांक tgafb_tc_रेजिस्टर(काष्ठा device *dev)
अणु
	पूर्णांक status = tgafb_रेजिस्टर(dev);
	अगर (!status)
		get_device(dev);
	वापस status;
पूर्ण

अटल पूर्णांक tgafb_tc_unरेजिस्टर(काष्ठा device *dev)
अणु
	put_device(dev);
	tgafb_unरेजिस्टर(dev);
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_TC */


/**
 *      tgafb_check_var - Optional function.  Validates a var passed in.
 *      @var: frame buffer variable screen काष्ठाure
 *      @info: frame buffer काष्ठाure that represents a single frame buffer
 */
अटल पूर्णांक
tgafb_check_var(काष्ठा fb_var_screeninfo *var, काष्ठा fb_info *info)
अणु
	काष्ठा tga_par *par = (काष्ठा tga_par *)info->par;

	अगर (par->tga_type == TGA_TYPE_8PLANE) अणु
		अगर (var->bits_per_pixel != 8)
			वापस -EINVAL;
	पूर्ण अन्यथा अणु
		अगर (var->bits_per_pixel != 32)
			वापस -EINVAL;
	पूर्ण
	var->red.length = var->green.length = var->blue.length = 8;
	अगर (var->bits_per_pixel == 32) अणु
		var->red.offset = 16;
		var->green.offset = 8;
		var->blue.offset = 0;
	पूर्ण

	अगर (var->xres_भव != var->xres || var->yres_भव != var->yres)
		वापस -EINVAL;
	अगर (var->xres * var->yres * (var->bits_per_pixel >> 3) > info->fix.smem_len)
		वापस -EINVAL;
	अगर (var->nonstd)
		वापस -EINVAL;
	अगर (1000000000 / var->pixघड़ी > TGA_PLL_MAX_FREQ)
		वापस -EINVAL;
	अगर ((var->vmode & FB_VMODE_MASK) != FB_VMODE_NONINTERLACED)
		वापस -EINVAL;

	/* Some of the acceleration routines assume the line width is
	   a multiple of 8 bytes.  */
	अगर (var->xres * (par->tga_type == TGA_TYPE_8PLANE ? 1 : 4) % 8)
		वापस -EINVAL;

	वापस 0;
पूर्ण

/**
 *      tgafb_set_par - Optional function.  Alters the hardware state.
 *      @info: frame buffer काष्ठाure that represents a single frame buffer
 */
अटल पूर्णांक
tgafb_set_par(काष्ठा fb_info *info)
अणु
	अटल अचिन्हित पूर्णांक स्थिर deep_presets[4] = अणु
		0x00004000,
		0x0000440d,
		0xffffffff,
		0x0000441d
	पूर्ण;
	अटल अचिन्हित पूर्णांक स्थिर rasterop_presets[4] = अणु
		0x00000003,
		0x00000303,
		0xffffffff,
		0x00000303
	पूर्ण;
	अटल अचिन्हित पूर्णांक स्थिर mode_presets[4] = अणु
		0x00000000,
		0x00000300,
		0xffffffff,
		0x00000300
	पूर्ण;
	अटल अचिन्हित पूर्णांक स्थिर base_addr_presets[4] = अणु
		0x00000000,
		0x00000001,
		0xffffffff,
		0x00000001
	पूर्ण;

	काष्ठा tga_par *par = (काष्ठा tga_par *) info->par;
	पूर्णांक tga_bus_pci = dev_is_pci(par->dev);
	पूर्णांक tga_bus_tc = TGA_BUS_TC(par->dev);
	u32 htimings, vtimings, pll_freq;
	u8 tga_type;
	पूर्णांक i;

	/* Encode video timings.  */
	htimings = (((info->var.xres/4) & TGA_HORIZ_ACT_LSB)
		    | (((info->var.xres/4) & 0x600 << 19) & TGA_HORIZ_ACT_MSB));
	vtimings = (info->var.yres & TGA_VERT_ACTIVE);
	htimings |= ((info->var.right_margin/4) << 9) & TGA_HORIZ_FP;
	vtimings |= (info->var.lower_margin << 11) & TGA_VERT_FP;
	htimings |= ((info->var.hsync_len/4) << 14) & TGA_HORIZ_SYNC;
	vtimings |= (info->var.vsync_len << 16) & TGA_VERT_SYNC;
	htimings |= ((info->var.left_margin/4) << 21) & TGA_HORIZ_BP;
	vtimings |= (info->var.upper_margin << 22) & TGA_VERT_BP;

	अगर (info->var.sync & FB_SYNC_HOR_HIGH_ACT)
		htimings |= TGA_HORIZ_POLARITY;
	अगर (info->var.sync & FB_SYNC_VERT_HIGH_ACT)
		vtimings |= TGA_VERT_POLARITY;

	par->htimings = htimings;
	par->vtimings = vtimings;

	par->sync_on_green = !!(info->var.sync & FB_SYNC_ON_GREEN);

	/* Store other useful values in par.  */
	par->xres = info->var.xres;
	par->yres = info->var.yres;
	par->pll_freq = pll_freq = 1000000000 / info->var.pixघड़ी;
	par->bits_per_pixel = info->var.bits_per_pixel;
	info->fix.line_length = par->xres * (par->bits_per_pixel >> 3);

	tga_type = par->tga_type;

	/* First, disable video.  */
	TGA_WRITE_REG(par, TGA_VALID_VIDEO | TGA_VALID_BLANK, TGA_VALID_REG);

	/* Write the DEEP रेजिस्टर.  */
	जबतक (TGA_READ_REG(par, TGA_CMD_STAT_REG) & 1) /* रुको क्रम not busy */
		जारी;
	mb();
	TGA_WRITE_REG(par, deep_presets[tga_type] |
			   (par->sync_on_green ? 0x0 : 0x00010000),
		      TGA_DEEP_REG);
	जबतक (TGA_READ_REG(par, TGA_CMD_STAT_REG) & 1) /* रुको क्रम not busy */
		जारी;
	mb();

	/* Write some more रेजिस्टरs.  */
	TGA_WRITE_REG(par, rasterop_presets[tga_type], TGA_RASTEROP_REG);
	TGA_WRITE_REG(par, mode_presets[tga_type], TGA_MODE_REG);
	TGA_WRITE_REG(par, base_addr_presets[tga_type], TGA_BASE_ADDR_REG);

	/* Calculate & ग_लिखो the PLL.  */
	tgafb_set_pll(par, pll_freq);

	/* Write some more रेजिस्टरs.  */
	TGA_WRITE_REG(par, 0xffffffff, TGA_PLANEMASK_REG);
	TGA_WRITE_REG(par, 0xffffffff, TGA_PIXELMASK_REG);

	/* Init video timing regs.  */
	TGA_WRITE_REG(par, htimings, TGA_HORIZ_REG);
	TGA_WRITE_REG(par, vtimings, TGA_VERT_REG);

	/* Initialise RAMDAC. */
	अगर (tga_type == TGA_TYPE_8PLANE && tga_bus_pci) अणु

		/* Init BT485 RAMDAC रेजिस्टरs.  */
		BT485_WRITE(par, 0xa2 | (par->sync_on_green ? 0x8 : 0x0),
			    BT485_CMD_0);
		BT485_WRITE(par, 0x01, BT485_ADDR_PAL_WRITE);
		BT485_WRITE(par, 0x14, BT485_CMD_3); /* cursor 64x64 */
		BT485_WRITE(par, 0x40, BT485_CMD_1);
		BT485_WRITE(par, 0x20, BT485_CMD_2); /* cursor off, क्रम now */
		BT485_WRITE(par, 0xff, BT485_PIXEL_MASK);

		/* Fill palette रेजिस्टरs.  */
		BT485_WRITE(par, 0x00, BT485_ADDR_PAL_WRITE);
		TGA_WRITE_REG(par, BT485_DATA_PAL, TGA_RAMDAC_SETUP_REG);

		क्रम (i = 0; i < 256 * 3; i += 4) अणु
			TGA_WRITE_REG(par, 0x55 | (BT485_DATA_PAL << 8),
				      TGA_RAMDAC_REG);
			TGA_WRITE_REG(par, 0x00 | (BT485_DATA_PAL << 8),
				      TGA_RAMDAC_REG);
			TGA_WRITE_REG(par, 0x00 | (BT485_DATA_PAL << 8),
				      TGA_RAMDAC_REG);
			TGA_WRITE_REG(par, 0x00 | (BT485_DATA_PAL << 8),
				      TGA_RAMDAC_REG);
		पूर्ण

	पूर्ण अन्यथा अगर (tga_type == TGA_TYPE_8PLANE && tga_bus_tc) अणु

		/* Init BT459 RAMDAC रेजिस्टरs.  */
		BT459_WRITE(par, BT459_REG_ACC, BT459_CMD_REG_0, 0x40);
		BT459_WRITE(par, BT459_REG_ACC, BT459_CMD_REG_1, 0x00);
		BT459_WRITE(par, BT459_REG_ACC, BT459_CMD_REG_2,
			    (par->sync_on_green ? 0xc0 : 0x40));

		BT459_WRITE(par, BT459_REG_ACC, BT459_CUR_CMD_REG, 0x00);

		/* Fill the palette.  */
		BT459_LOAD_ADDR(par, 0x0000);
		TGA_WRITE_REG(par, BT459_PALETTE << 2, TGA_RAMDAC_SETUP_REG);

		क्रम (i = 0; i < 256 * 3; i += 4) अणु
			TGA_WRITE_REG(par, 0x55, TGA_RAMDAC_REG);
			TGA_WRITE_REG(par, 0x00, TGA_RAMDAC_REG);
			TGA_WRITE_REG(par, 0x00, TGA_RAMDAC_REG);
			TGA_WRITE_REG(par, 0x00, TGA_RAMDAC_REG);
		पूर्ण

	पूर्ण अन्यथा अणु /* 24-plane or 24plusZ */

		/* Init BT463 RAMDAC रेजिस्टरs.  */
		BT463_WRITE(par, BT463_REG_ACC, BT463_CMD_REG_0, 0x40);
		BT463_WRITE(par, BT463_REG_ACC, BT463_CMD_REG_1, 0x08);
		BT463_WRITE(par, BT463_REG_ACC, BT463_CMD_REG_2,
			    (par->sync_on_green ? 0xc0 : 0x40));

		BT463_WRITE(par, BT463_REG_ACC, BT463_READ_MASK_0, 0xff);
		BT463_WRITE(par, BT463_REG_ACC, BT463_READ_MASK_1, 0xff);
		BT463_WRITE(par, BT463_REG_ACC, BT463_READ_MASK_2, 0xff);
		BT463_WRITE(par, BT463_REG_ACC, BT463_READ_MASK_3, 0x0f);

		BT463_WRITE(par, BT463_REG_ACC, BT463_BLINK_MASK_0, 0x00);
		BT463_WRITE(par, BT463_REG_ACC, BT463_BLINK_MASK_1, 0x00);
		BT463_WRITE(par, BT463_REG_ACC, BT463_BLINK_MASK_2, 0x00);
		BT463_WRITE(par, BT463_REG_ACC, BT463_BLINK_MASK_3, 0x00);

		/* Fill the palette.  */
		BT463_LOAD_ADDR(par, 0x0000);
		TGA_WRITE_REG(par, BT463_PALETTE << 2, TGA_RAMDAC_SETUP_REG);

#अगर_घोषित CONFIG_HW_CONSOLE
		क्रम (i = 0; i < 16; i++) अणु
			पूर्णांक j = color_table[i];

			TGA_WRITE_REG(par, शेष_red[j], TGA_RAMDAC_REG);
			TGA_WRITE_REG(par, शेष_grn[j], TGA_RAMDAC_REG);
			TGA_WRITE_REG(par, शेष_blu[j], TGA_RAMDAC_REG);
		पूर्ण
		क्रम (i = 0; i < 512 * 3; i += 4) अणु
#अन्यथा
		क्रम (i = 0; i < 528 * 3; i += 4) अणु
#पूर्ण_अगर
			TGA_WRITE_REG(par, 0x55, TGA_RAMDAC_REG);
			TGA_WRITE_REG(par, 0x00, TGA_RAMDAC_REG);
			TGA_WRITE_REG(par, 0x00, TGA_RAMDAC_REG);
			TGA_WRITE_REG(par, 0x00, TGA_RAMDAC_REG);
		पूर्ण

		/* Fill winकरोw type table after start of vertical retrace.  */
		जबतक (!(TGA_READ_REG(par, TGA_INTR_STAT_REG) & 0x01))
			जारी;
		TGA_WRITE_REG(par, 0x01, TGA_INTR_STAT_REG);
		mb();
		जबतक (!(TGA_READ_REG(par, TGA_INTR_STAT_REG) & 0x01))
			जारी;
		TGA_WRITE_REG(par, 0x01, TGA_INTR_STAT_REG);

		BT463_LOAD_ADDR(par, BT463_WINDOW_TYPE_BASE);
		TGA_WRITE_REG(par, BT463_REG_ACC << 2, TGA_RAMDAC_SETUP_REG);

		क्रम (i = 0; i < 16; i++) अणु
			TGA_WRITE_REG(par, 0x00, TGA_RAMDAC_REG);
			TGA_WRITE_REG(par, 0x01, TGA_RAMDAC_REG);
			TGA_WRITE_REG(par, 0x00, TGA_RAMDAC_REG);
		पूर्ण

	पूर्ण

	/* Finally, enable video scan (and pray क्रम the monitor... :-) */
	TGA_WRITE_REG(par, TGA_VALID_VIDEO, TGA_VALID_REG);

	वापस 0;
पूर्ण

#घोषणा DIFFCHECK(X)							  \
करो अणु									  \
	अगर (m <= 0x3f) अणु						  \
		पूर्णांक delta = f - (TGA_PLL_BASE_FREQ * (X)) / (r << shअगरt); \
		अगर (delta < 0)						  \
			delta = -delta;					  \
		अगर (delta < min_dअगरf)					  \
			min_dअगरf = delta, vm = m, va = a, vr = r;	  \
	पूर्ण								  \
पूर्ण जबतक (0)

अटल व्योम
tgafb_set_pll(काष्ठा tga_par *par, पूर्णांक f)
अणु
	पूर्णांक n, shअगरt, base, min_dअगरf, target;
	पूर्णांक r,a,m,vm = 34, va = 1, vr = 30;

	क्रम (r = 0 ; r < 12 ; r++)
		TGA_WRITE_REG(par, !r, TGA_CLOCK_REG);

	अगर (f > TGA_PLL_MAX_FREQ)
		f = TGA_PLL_MAX_FREQ;

	अगर (f >= TGA_PLL_MAX_FREQ / 2)
		shअगरt = 0;
	अन्यथा अगर (f >= TGA_PLL_MAX_FREQ / 4)
		shअगरt = 1;
	अन्यथा
		shअगरt = 2;

	TGA_WRITE_REG(par, shअगरt & 1, TGA_CLOCK_REG);
	TGA_WRITE_REG(par, shअगरt >> 1, TGA_CLOCK_REG);

	क्रम (r = 0 ; r < 10 ; r++)
		TGA_WRITE_REG(par, 0, TGA_CLOCK_REG);

	अगर (f <= 120000) अणु
		TGA_WRITE_REG(par, 0, TGA_CLOCK_REG);
		TGA_WRITE_REG(par, 0, TGA_CLOCK_REG);
	पूर्ण
	अन्यथा अगर (f <= 200000) अणु
		TGA_WRITE_REG(par, 1, TGA_CLOCK_REG);
		TGA_WRITE_REG(par, 0, TGA_CLOCK_REG);
	पूर्ण
	अन्यथा अणु
		TGA_WRITE_REG(par, 0, TGA_CLOCK_REG);
		TGA_WRITE_REG(par, 1, TGA_CLOCK_REG);
	पूर्ण

	TGA_WRITE_REG(par, 1, TGA_CLOCK_REG);
	TGA_WRITE_REG(par, 0, TGA_CLOCK_REG);
	TGA_WRITE_REG(par, 0, TGA_CLOCK_REG);
	TGA_WRITE_REG(par, 1, TGA_CLOCK_REG);
	TGA_WRITE_REG(par, 0, TGA_CLOCK_REG);
	TGA_WRITE_REG(par, 1, TGA_CLOCK_REG);

	target = (f << shअगरt) / TGA_PLL_BASE_FREQ;
	min_dअगरf = TGA_PLL_MAX_FREQ;

	r = 7 / target;
	अगर (!r) r = 1;

	base = target * r;
	जबतक (base < 449) अणु
		क्रम (n = base < 7 ? 7 : base; n < base + target && n < 449; n++) अणु
			m = ((n + 3) / 7) - 1;
			a = 0;
			DIFFCHECK((m + 1) * 7);
			m++;
			DIFFCHECK((m + 1) * 7);
			m = (n / 6) - 1;
			अगर ((a = n % 6))
				DIFFCHECK(n);
		पूर्ण
		r++;
		base += target;
	पूर्ण

	vr--;

	क्रम (r = 0; r < 8; r++)
		TGA_WRITE_REG(par, (vm >> r) & 1, TGA_CLOCK_REG);
	क्रम (r = 0; r < 8 ; r++)
		TGA_WRITE_REG(par, (va >> r) & 1, TGA_CLOCK_REG);
	क्रम (r = 0; r < 7 ; r++)
		TGA_WRITE_REG(par, (vr >> r) & 1, TGA_CLOCK_REG);
	TGA_WRITE_REG(par, ((vr >> 7) & 1)|2, TGA_CLOCK_REG);
पूर्ण


/**
 *      tgafb_setcolreg - Optional function. Sets a color रेजिस्टर.
 *      @regno: boolean, 0 copy local, 1 get_user() function
 *      @red: frame buffer colormap काष्ठाure
 *      @green: The green value which can be up to 16 bits wide
 *      @blue:  The blue value which can be up to 16 bits wide.
 *      @transp: If supported the alpha value which can be up to 16 bits wide.
 *      @info: frame buffer info काष्ठाure
 */
अटल पूर्णांक
tgafb_setcolreg(अचिन्हित regno, अचिन्हित red, अचिन्हित green, अचिन्हित blue,
		अचिन्हित transp, काष्ठा fb_info *info)
अणु
	काष्ठा tga_par *par = (काष्ठा tga_par *) info->par;
	पूर्णांक tga_bus_pci = dev_is_pci(par->dev);
	पूर्णांक tga_bus_tc = TGA_BUS_TC(par->dev);

	अगर (regno > 255)
		वापस 1;
	red >>= 8;
	green >>= 8;
	blue >>= 8;

	अगर (par->tga_type == TGA_TYPE_8PLANE && tga_bus_pci) अणु
		BT485_WRITE(par, regno, BT485_ADDR_PAL_WRITE);
		TGA_WRITE_REG(par, BT485_DATA_PAL, TGA_RAMDAC_SETUP_REG);
		TGA_WRITE_REG(par, red|(BT485_DATA_PAL<<8),TGA_RAMDAC_REG);
		TGA_WRITE_REG(par, green|(BT485_DATA_PAL<<8),TGA_RAMDAC_REG);
		TGA_WRITE_REG(par, blue|(BT485_DATA_PAL<<8),TGA_RAMDAC_REG);
	पूर्ण अन्यथा अगर (par->tga_type == TGA_TYPE_8PLANE && tga_bus_tc) अणु
		BT459_LOAD_ADDR(par, regno);
		TGA_WRITE_REG(par, BT459_PALETTE << 2, TGA_RAMDAC_SETUP_REG);
		TGA_WRITE_REG(par, red, TGA_RAMDAC_REG);
		TGA_WRITE_REG(par, green, TGA_RAMDAC_REG);
		TGA_WRITE_REG(par, blue, TGA_RAMDAC_REG);
	पूर्ण अन्यथा अणु
		अगर (regno < 16) अणु
			u32 value = (regno << 16) | (regno << 8) | regno;
			((u32 *)info->pseuकरो_palette)[regno] = value;
		पूर्ण
		BT463_LOAD_ADDR(par, regno);
		TGA_WRITE_REG(par, BT463_PALETTE << 2, TGA_RAMDAC_SETUP_REG);
		TGA_WRITE_REG(par, red, TGA_RAMDAC_REG);
		TGA_WRITE_REG(par, green, TGA_RAMDAC_REG);
		TGA_WRITE_REG(par, blue, TGA_RAMDAC_REG);
	पूर्ण

	वापस 0;
पूर्ण


/**
 *      tgafb_blank - Optional function.  Blanks the display.
 *      @blank: the blank mode we want.
 *      @info: frame buffer काष्ठाure that represents a single frame buffer
 */
अटल पूर्णांक
tgafb_blank(पूर्णांक blank, काष्ठा fb_info *info)
अणु
	काष्ठा tga_par *par = (काष्ठा tga_par *) info->par;
	u32 vhcr, vvcr, vvvr;
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);

	vhcr = TGA_READ_REG(par, TGA_HORIZ_REG);
	vvcr = TGA_READ_REG(par, TGA_VERT_REG);
	vvvr = TGA_READ_REG(par, TGA_VALID_REG);
	vvvr &= ~(TGA_VALID_VIDEO | TGA_VALID_BLANK);

	चयन (blank) अणु
	हाल FB_BLANK_UNBLANK: /* Unblanking */
		अगर (par->vesa_blanked) अणु
			TGA_WRITE_REG(par, vhcr & 0xbfffffff, TGA_HORIZ_REG);
			TGA_WRITE_REG(par, vvcr & 0xbfffffff, TGA_VERT_REG);
			par->vesa_blanked = 0;
		पूर्ण
		TGA_WRITE_REG(par, vvvr | TGA_VALID_VIDEO, TGA_VALID_REG);
		अवरोध;

	हाल FB_BLANK_NORMAL: /* Normal blanking */
		TGA_WRITE_REG(par, vvvr | TGA_VALID_VIDEO | TGA_VALID_BLANK,
			      TGA_VALID_REG);
		अवरोध;

	हाल FB_BLANK_VSYNC_SUSPEND: /* VESA blank (vsync off) */
		TGA_WRITE_REG(par, vvcr | 0x40000000, TGA_VERT_REG);
		TGA_WRITE_REG(par, vvvr | TGA_VALID_BLANK, TGA_VALID_REG);
		par->vesa_blanked = 1;
		अवरोध;

	हाल FB_BLANK_HSYNC_SUSPEND: /* VESA blank (hsync off) */
		TGA_WRITE_REG(par, vhcr | 0x40000000, TGA_HORIZ_REG);
		TGA_WRITE_REG(par, vvvr | TGA_VALID_BLANK, TGA_VALID_REG);
		par->vesa_blanked = 1;
		अवरोध;

	हाल FB_BLANK_POWERDOWN: /* Poweroff */
		TGA_WRITE_REG(par, vhcr | 0x40000000, TGA_HORIZ_REG);
		TGA_WRITE_REG(par, vvcr | 0x40000000, TGA_VERT_REG);
		TGA_WRITE_REG(par, vvvr | TGA_VALID_BLANK, TGA_VALID_REG);
		par->vesa_blanked = 1;
		अवरोध;
	पूर्ण

	local_irq_restore(flags);
	वापस 0;
पूर्ण


/*
 *  Acceleration.
 */

अटल व्योम
tgafb_mono_imageblit(काष्ठा fb_info *info, स्थिर काष्ठा fb_image *image)
अणु
	काष्ठा tga_par *par = (काष्ठा tga_par *) info->par;
	u32 fgcolor, bgcolor, dx, dy, width, height, vxres, vyres, pixelmask;
	अचिन्हित दीर्घ rincr, line_length, shअगरt, pos, is8bpp;
	अचिन्हित दीर्घ i, j;
	स्थिर अचिन्हित अक्षर *data;
	व्योम __iomem *regs_base;
	व्योम __iomem *fb_base;

	is8bpp = info->var.bits_per_pixel == 8;

	dx = image->dx;
	dy = image->dy;
	width = image->width;
	height = image->height;
	vxres = info->var.xres_भव;
	vyres = info->var.yres_भव;
	line_length = info->fix.line_length;
	rincr = (width + 7) / 8;

	/* A shअगरt below cannot cope with.  */
	अगर (unlikely(width == 0))
		वापस;
	/* Crop the image to the screen.  */
	अगर (dx > vxres || dy > vyres)
		वापस;
	अगर (dx + width > vxres)
		width = vxres - dx;
	अगर (dy + height > vyres)
		height = vyres - dy;

	regs_base = par->tga_regs_base;
	fb_base = par->tga_fb_base;

	/* Expand the color values to fill 32-bits.  */
	/* ??? Would be nice to notice colour changes अन्यथाwhere, so
	   that we can करो this only when necessary.  */
	fgcolor = image->fg_color;
	bgcolor = image->bg_color;
	अगर (is8bpp) अणु
		fgcolor |= fgcolor << 8;
		fgcolor |= fgcolor << 16;
		bgcolor |= bgcolor << 8;
		bgcolor |= bgcolor << 16;
	पूर्ण अन्यथा अणु
		अगर (fgcolor < 16)
			fgcolor = ((u32 *)info->pseuकरो_palette)[fgcolor];
		अगर (bgcolor < 16)
			bgcolor = ((u32 *)info->pseuकरो_palette)[bgcolor];
	पूर्ण
	__raw_ग_लिखोl(fgcolor, regs_base + TGA_FOREGROUND_REG);
	__raw_ग_लिखोl(bgcolor, regs_base + TGA_BACKGROUND_REG);

	/* Acquire proper alignment; set up the PIXELMASK रेजिस्टर
	   so that we only ग_लिखो the proper अक्षरacter cell.  */
	pos = dy * line_length;
	अगर (is8bpp) अणु
		pos += dx;
		shअगरt = pos & 3;
		pos &= -4;
	पूर्ण अन्यथा अणु
		pos += dx * 4;
		shअगरt = (pos & 7) >> 2;
		pos &= -8;
	पूर्ण

	data = (स्थिर अचिन्हित अक्षर *) image->data;

	/* Enable opaque stipple mode.  */
	__raw_ग_लिखोl((is8bpp
		      ? TGA_MODE_SBM_8BPP | TGA_MODE_OPAQUE_STIPPLE
		      : TGA_MODE_SBM_24BPP | TGA_MODE_OPAQUE_STIPPLE),
		     regs_base + TGA_MODE_REG);

	अगर (width + shअगरt <= 32) अणु
		अचिन्हित दीर्घ bwidth;

		/* Handle common हाल of imaging a single अक्षरacter, in
		   a font less than or 32 pixels wide.  */

		/* Aव्योम a shअगरt by 32; width > 0 implied.  */
		pixelmask = (2ul << (width - 1)) - 1;
		pixelmask <<= shअगरt;
		__raw_ग_लिखोl(pixelmask, regs_base + TGA_PIXELMASK_REG);
		wmb();

		bwidth = (width + 7) / 8;

		क्रम (i = 0; i < height; ++i) अणु
			u32 mask = 0;

			/* The image data is bit big endian; we need
			   little endian.  */
			क्रम (j = 0; j < bwidth; ++j)
				mask |= bitrev8(data[j]) << (j * 8);

			__raw_ग_लिखोl(mask << shअगरt, fb_base + pos);

			pos += line_length;
			data += rincr;
		पूर्ण
		wmb();
		__raw_ग_लिखोl(0xffffffff, regs_base + TGA_PIXELMASK_REG);
	पूर्ण अन्यथा अगर (shअगरt == 0) अणु
		अचिन्हित दीर्घ pos0 = pos;
		स्थिर अचिन्हित अक्षर *data0 = data;
		अचिन्हित दीर्घ bincr = (is8bpp ? 8 : 8*4);
		अचिन्हित दीर्घ bwidth;

		/* Handle another common हाल in which accel_अ_दोs
		   generates a large biपंचांगap, which happens to be aligned.
		   Allow the tail to be misaligned.  This हाल is 
		   पूर्णांकeresting because we've not got to hold partial
		   bytes across the words being written.  */

		wmb();

		bwidth = (width / 8) & -4;
		क्रम (i = 0; i < height; ++i) अणु
			क्रम (j = 0; j < bwidth; j += 4) अणु
				u32 mask = 0;
				mask |= bitrev8(data[j+0]) << (0 * 8);
				mask |= bitrev8(data[j+1]) << (1 * 8);
				mask |= bitrev8(data[j+2]) << (2 * 8);
				mask |= bitrev8(data[j+3]) << (3 * 8);
				__raw_ग_लिखोl(mask, fb_base + pos + j*bincr);
			पूर्ण
			pos += line_length;
			data += rincr;
		पूर्ण
		wmb();

		pixelmask = (1ul << (width & 31)) - 1;
		अगर (pixelmask) अणु
			__raw_ग_लिखोl(pixelmask, regs_base + TGA_PIXELMASK_REG);
			wmb();

			pos = pos0 + bwidth*bincr;
			data = data0 + bwidth;
			bwidth = ((width & 31) + 7) / 8;

			क्रम (i = 0; i < height; ++i) अणु
				u32 mask = 0;
				क्रम (j = 0; j < bwidth; ++j)
					mask |= bitrev8(data[j]) << (j * 8);
				__raw_ग_लिखोl(mask, fb_base + pos);
				pos += line_length;
				data += rincr;
			पूर्ण
			wmb();
			__raw_ग_लिखोl(0xffffffff, regs_base + TGA_PIXELMASK_REG);
		पूर्ण
	पूर्ण अन्यथा अणु
		अचिन्हित दीर्घ pos0 = pos;
		स्थिर अचिन्हित अक्षर *data0 = data;
		अचिन्हित दीर्घ bincr = (is8bpp ? 8 : 8*4);
		अचिन्हित दीर्घ bwidth;

		/* Finally, handle the generic हाल of misaligned start.
		   Here we split the ग_लिखो पूर्णांकo 16-bit spans.  This allows
		   us to use only one pixel mask, instead of four as would
		   be required by writing 24-bit spans.  */

		pixelmask = 0xffff << shअगरt;
		__raw_ग_लिखोl(pixelmask, regs_base + TGA_PIXELMASK_REG);
		wmb();

		bwidth = (width / 8) & -2;
		क्रम (i = 0; i < height; ++i) अणु
			क्रम (j = 0; j < bwidth; j += 2) अणु
				u32 mask = 0;
				mask |= bitrev8(data[j+0]) << (0 * 8);
				mask |= bitrev8(data[j+1]) << (1 * 8);
				mask <<= shअगरt;
				__raw_ग_लिखोl(mask, fb_base + pos + j*bincr);
			पूर्ण
			pos += line_length;
			data += rincr;
		पूर्ण
		wmb();

		pixelmask = ((1ul << (width & 15)) - 1) << shअगरt;
		अगर (pixelmask) अणु
			__raw_ग_लिखोl(pixelmask, regs_base + TGA_PIXELMASK_REG);
			wmb();

			pos = pos0 + bwidth*bincr;
			data = data0 + bwidth;
			bwidth = (width & 15) > 8;

			क्रम (i = 0; i < height; ++i) अणु
				u32 mask = bitrev8(data[0]);
				अगर (bwidth)
					mask |= bitrev8(data[1]) << 8;
				mask <<= shअगरt;
				__raw_ग_लिखोl(mask, fb_base + pos);
				pos += line_length;
				data += rincr;
			पूर्ण
			wmb();
		पूर्ण
		__raw_ग_लिखोl(0xffffffff, regs_base + TGA_PIXELMASK_REG);
	पूर्ण

	/* Disable opaque stipple mode.  */
	__raw_ग_लिखोl((is8bpp
		      ? TGA_MODE_SBM_8BPP | TGA_MODE_SIMPLE
		      : TGA_MODE_SBM_24BPP | TGA_MODE_SIMPLE),
		     regs_base + TGA_MODE_REG);
पूर्ण

अटल व्योम
tgafb_clut_imageblit(काष्ठा fb_info *info, स्थिर काष्ठा fb_image *image)
अणु
	काष्ठा tga_par *par = (काष्ठा tga_par *) info->par;
	u32 color, dx, dy, width, height, vxres, vyres;
	u32 *palette = ((u32 *)info->pseuकरो_palette);
	अचिन्हित दीर्घ pos, line_length, i, j;
	स्थिर अचिन्हित अक्षर *data;
	व्योम __iomem *fb_base;

	dx = image->dx;
	dy = image->dy;
	width = image->width;
	height = image->height;
	vxres = info->var.xres_भव;
	vyres = info->var.yres_भव;
	line_length = info->fix.line_length;

	/* Crop the image to the screen.  */
	अगर (dx > vxres || dy > vyres)
		वापस;
	अगर (dx + width > vxres)
		width = vxres - dx;
	अगर (dy + height > vyres)
		height = vyres - dy;

	fb_base = par->tga_fb_base;

	pos = dy * line_length + (dx * 4);
	data = image->data;

	/* Now copy the image, color_expanding via the palette. */
	क्रम (i = 0; i < height; i++) अणु
		क्रम (j = 0; j < width; j++) अणु
			color = palette[*data++];
			__raw_ग_लिखोl(color, fb_base + pos + j*4);
		पूर्ण
		pos += line_length;
	पूर्ण
पूर्ण

/**
 *      tgafb_imageblit - REQUIRED function. Can use generic routines अगर
 *                        non acclerated hardware and packed pixel based.
 *                        Copies a image from प्रणाली memory to the screen.
 *
 *      @info: frame buffer काष्ठाure that represents a single frame buffer
 *      @image: काष्ठाure defining the image.
 */
अटल व्योम
tgafb_imageblit(काष्ठा fb_info *info, स्थिर काष्ठा fb_image *image)
अणु
	अचिन्हित पूर्णांक is8bpp = info->var.bits_per_pixel == 8;

	/* If a mono image, regardless of FB depth, go करो it. */
	अगर (image->depth == 1) अणु
		tgafb_mono_imageblit(info, image);
		वापस;
	पूर्ण

	/* For copies that aren't pixel expansion, there's little we
	   can करो better than the generic code.  */
	/* ??? There is a DMA ग_लिखो mode; I wonder अगर that could be
	   made to pull the data from the image buffer...  */
	अगर (image->depth == info->var.bits_per_pixel) अणु
		cfb_imageblit(info, image);
		वापस;
	पूर्ण

	/* If 24-plane FB and the image is 8-plane with CLUT, we can करो it. */
	अगर (!is8bpp && image->depth == 8) अणु
		tgafb_clut_imageblit(info, image);
		वापस;
	पूर्ण

	/* Silently वापस... */
पूर्ण

/**
 *      tgafb_fillrect - REQUIRED function. Can use generic routines अगर 
 *                       non acclerated hardware and packed pixel based.
 *                       Draws a rectangle on the screen.               
 *
 *      @info: frame buffer काष्ठाure that represents a single frame buffer
 *      @rect: काष्ठाure defining the rectagle and operation.
 */
अटल व्योम
tgafb_fillrect(काष्ठा fb_info *info, स्थिर काष्ठा fb_fillrect *rect)
अणु
	काष्ठा tga_par *par = (काष्ठा tga_par *) info->par;
	पूर्णांक is8bpp = info->var.bits_per_pixel == 8;
	u32 dx, dy, width, height, vxres, vyres, color;
	अचिन्हित दीर्घ pos, align, line_length, i, j;
	व्योम __iomem *regs_base;
	व्योम __iomem *fb_base;

	dx = rect->dx;
	dy = rect->dy;
	width = rect->width;
	height = rect->height;
	vxres = info->var.xres_भव;
	vyres = info->var.yres_भव;
	line_length = info->fix.line_length;
	regs_base = par->tga_regs_base;
	fb_base = par->tga_fb_base;

	/* Crop the rectangle to the screen.  */
	अगर (dx > vxres || dy > vyres || !width || !height)
		वापस;
	अगर (dx + width > vxres)
		width = vxres - dx;
	अगर (dy + height > vyres)
		height = vyres - dy;

	pos = dy * line_length + dx * (is8bpp ? 1 : 4);

	/* ??? We could implement ROP_XOR with opaque fill mode
	   and a RasterOp setting of GXxor, but as far as I can
	   tell, this mode is not actually used in the kernel.
	   Thus I am ignoring it क्रम now.  */
	अगर (rect->rop != ROP_COPY) अणु
		cfb_fillrect(info, rect);
		वापस;
	पूर्ण

	/* Expand the color value to fill 8 pixels.  */
	color = rect->color;
	अगर (is8bpp) अणु
		color |= color << 8;
		color |= color << 16;
		__raw_ग_लिखोl(color, regs_base + TGA_BLOCK_COLOR0_REG);
		__raw_ग_लिखोl(color, regs_base + TGA_BLOCK_COLOR1_REG);
	पूर्ण अन्यथा अणु
		अगर (color < 16)
			color = ((u32 *)info->pseuकरो_palette)[color];
		__raw_ग_लिखोl(color, regs_base + TGA_BLOCK_COLOR0_REG);
		__raw_ग_लिखोl(color, regs_base + TGA_BLOCK_COLOR1_REG);
		__raw_ग_लिखोl(color, regs_base + TGA_BLOCK_COLOR2_REG);
		__raw_ग_लिखोl(color, regs_base + TGA_BLOCK_COLOR3_REG);
		__raw_ग_लिखोl(color, regs_base + TGA_BLOCK_COLOR4_REG);
		__raw_ग_लिखोl(color, regs_base + TGA_BLOCK_COLOR5_REG);
		__raw_ग_लिखोl(color, regs_base + TGA_BLOCK_COLOR6_REG);
		__raw_ग_लिखोl(color, regs_base + TGA_BLOCK_COLOR7_REG);
	पूर्ण

	/* The DATA रेजिस्टर holds the fill mask क्रम block fill mode.
	   Since we're not stippling, this is all ones.  */
	__raw_ग_लिखोl(0xffffffff, regs_base + TGA_DATA_REG);

	/* Enable block fill mode.  */
	__raw_ग_लिखोl((is8bpp
		      ? TGA_MODE_SBM_8BPP | TGA_MODE_BLOCK_FILL
		      : TGA_MODE_SBM_24BPP | TGA_MODE_BLOCK_FILL),
		     regs_base + TGA_MODE_REG);
	wmb();

	/* We can fill 2k pixels per operation.  Notice blocks that fit
	   the width of the screen so that we can take advantage of this
	   and fill more than one line per ग_लिखो.  */
	अगर (width == line_length) अणु
		width *= height;
		height = 1;
	पूर्ण

	/* The ग_लिखो पूर्णांकo the frame buffer must be aligned to 4 bytes,
	   but we are allowed to encode the offset within the word in
	   the data word written.  */
	align = (pos & 3) << 16;
	pos &= -4;

	अगर (width <= 2048) अणु
		u32 data;

		data = (width - 1) | align;

		क्रम (i = 0; i < height; ++i) अणु
			__raw_ग_लिखोl(data, fb_base + pos);
			pos += line_length;
		पूर्ण
	पूर्ण अन्यथा अणु
		अचिन्हित दीर्घ Bpp = (is8bpp ? 1 : 4);
		अचिन्हित दीर्घ nwidth = width & -2048;
		u32 fdata, ldata;

		fdata = (2048 - 1) | align;
		ldata = ((width & 2047) - 1) | align;

		क्रम (i = 0; i < height; ++i) अणु
			क्रम (j = 0; j < nwidth; j += 2048)
				__raw_ग_लिखोl(fdata, fb_base + pos + j*Bpp);
			अगर (j < width)
				__raw_ग_लिखोl(ldata, fb_base + pos + j*Bpp);
			pos += line_length;
		पूर्ण
	पूर्ण
	wmb();

	/* Disable block fill mode.  */
	__raw_ग_लिखोl((is8bpp
		      ? TGA_MODE_SBM_8BPP | TGA_MODE_SIMPLE
		      : TGA_MODE_SBM_24BPP | TGA_MODE_SIMPLE),
		     regs_base + TGA_MODE_REG);
पूर्ण

/*
 *      tgafb_copyarea - REQUIRED function. Can use generic routines अगर
 *                       non acclerated hardware and packed pixel based.
 *                       Copies on area of the screen to another area.
 *
 *      @info: frame buffer काष्ठाure that represents a single frame buffer
 *      @area: काष्ठाure defining the source and destination.
 */

/* Handle the special हाल of copying entire lines, e.g. during scrolling.
   We can aव्योम a lot of needless computation in this हाल.  In the 8bpp
   हाल we need to use the COPY64 रेजिस्टरs instead of mask ग_लिखोs पूर्णांकo 
   the frame buffer to achieve maximum perक्रमmance.  */

अटल अंतरभूत व्योम
copyarea_line_8bpp(काष्ठा fb_info *info, u32 dy, u32 sy,
		   u32 height, u32 width)
अणु
	काष्ठा tga_par *par = (काष्ठा tga_par *) info->par;
	व्योम __iomem *tga_regs = par->tga_regs_base;
	अचिन्हित दीर्घ dpos, spos, i, n64;

	/* Set up the MODE and PIXELSHIFT रेजिस्टरs.  */
	__raw_ग_लिखोl(TGA_MODE_SBM_8BPP | TGA_MODE_COPY, tga_regs+TGA_MODE_REG);
	__raw_ग_लिखोl(0, tga_regs+TGA_PIXELSHIFT_REG);
	wmb();

	n64 = (height * width) / 64;

	अगर (sy < dy) अणु
		spos = (sy + height) * width;
		dpos = (dy + height) * width;

		क्रम (i = 0; i < n64; ++i) अणु
			spos -= 64;
			dpos -= 64;
			__raw_ग_लिखोl(spos, tga_regs+TGA_COPY64_SRC);
			wmb();
			__raw_ग_लिखोl(dpos, tga_regs+TGA_COPY64_DST);
			wmb();
		पूर्ण
	पूर्ण अन्यथा अणु
		spos = sy * width;
		dpos = dy * width;

		क्रम (i = 0; i < n64; ++i) अणु
			__raw_ग_लिखोl(spos, tga_regs+TGA_COPY64_SRC);
			wmb();
			__raw_ग_लिखोl(dpos, tga_regs+TGA_COPY64_DST);
			wmb();
			spos += 64;
			dpos += 64;
		पूर्ण
	पूर्ण

	/* Reset the MODE रेजिस्टर to normal.  */
	__raw_ग_लिखोl(TGA_MODE_SBM_8BPP|TGA_MODE_SIMPLE, tga_regs+TGA_MODE_REG);
पूर्ण

अटल अंतरभूत व्योम
copyarea_line_32bpp(काष्ठा fb_info *info, u32 dy, u32 sy,
		    u32 height, u32 width)
अणु
	काष्ठा tga_par *par = (काष्ठा tga_par *) info->par;
	व्योम __iomem *tga_regs = par->tga_regs_base;
	व्योम __iomem *tga_fb = par->tga_fb_base;
	व्योम __iomem *src;
	व्योम __iomem *dst;
	अचिन्हित दीर्घ i, n16;

	/* Set up the MODE and PIXELSHIFT रेजिस्टरs.  */
	__raw_ग_लिखोl(TGA_MODE_SBM_24BPP | TGA_MODE_COPY, tga_regs+TGA_MODE_REG);
	__raw_ग_लिखोl(0, tga_regs+TGA_PIXELSHIFT_REG);
	wmb();

	n16 = (height * width) / 16;

	अगर (sy < dy) अणु
		src = tga_fb + (sy + height) * width * 4;
		dst = tga_fb + (dy + height) * width * 4;

		क्रम (i = 0; i < n16; ++i) अणु
			src -= 64;
			dst -= 64;
			__raw_ग_लिखोl(0xffff, src);
			wmb();
			__raw_ग_लिखोl(0xffff, dst);
			wmb();
		पूर्ण
	पूर्ण अन्यथा अणु
		src = tga_fb + sy * width * 4;
		dst = tga_fb + dy * width * 4;

		क्रम (i = 0; i < n16; ++i) अणु
			__raw_ग_लिखोl(0xffff, src);
			wmb();
			__raw_ग_लिखोl(0xffff, dst);
			wmb();
			src += 64;
			dst += 64;
		पूर्ण
	पूर्ण

	/* Reset the MODE रेजिस्टर to normal.  */
	__raw_ग_लिखोl(TGA_MODE_SBM_24BPP|TGA_MODE_SIMPLE, tga_regs+TGA_MODE_REG);
पूर्ण

/* The (almost) general हाल of backward copy in 8bpp mode.  */
अटल अंतरभूत व्योम
copyarea_8bpp(काष्ठा fb_info *info, u32 dx, u32 dy, u32 sx, u32 sy,
	      u32 height, u32 width, u32 line_length,
	      स्थिर काष्ठा fb_copyarea *area)
अणु
	काष्ठा tga_par *par = (काष्ठा tga_par *) info->par;
	अचिन्हित i, yincr;
	पूर्णांक depos, sepos, backward, last_step, step;
	u32 mask_last;
	अचिन्हित n32;
	व्योम __iomem *tga_regs;
	व्योम __iomem *tga_fb;

	/* Do acceleration only अगर we are aligned on 8 pixels */
	अगर ((dx | sx | width) & 7) अणु
		cfb_copyarea(info, area);
		वापस;
	पूर्ण

	yincr = line_length;
	अगर (dy > sy) अणु
		dy += height - 1;
		sy += height - 1;
		yincr = -yincr;
	पूर्ण
	backward = dy == sy && dx > sx && dx < sx + width;

	/* Compute the offsets and alignments in the frame buffer.
	   More than anything अन्यथा, these control how we करो copies.  */
	depos = dy * line_length + dx;
	sepos = sy * line_length + sx;
	अगर (backward) अणु
		depos += width;
		sepos += width;
	पूर्ण

	/* Next copy full words at a समय.  */
	n32 = width / 32;
	last_step = width % 32;

	/* Finally copy the unaligned head of the span.  */
	mask_last = (1ul << last_step) - 1;

	अगर (!backward) अणु
		step = 32;
		last_step = 32;
	पूर्ण अन्यथा अणु
		step = -32;
		last_step = -last_step;
		sepos -= 32;
		depos -= 32;
	पूर्ण

	tga_regs = par->tga_regs_base;
	tga_fb = par->tga_fb_base;

	/* Set up the MODE and PIXELSHIFT रेजिस्टरs.  */
	__raw_ग_लिखोl(TGA_MODE_SBM_8BPP|TGA_MODE_COPY, tga_regs+TGA_MODE_REG);
	__raw_ग_लिखोl(0, tga_regs+TGA_PIXELSHIFT_REG);
	wmb();

	क्रम (i = 0; i < height; ++i) अणु
		अचिन्हित दीर्घ j;
		व्योम __iomem *sfb;
		व्योम __iomem *dfb;

		sfb = tga_fb + sepos;
		dfb = tga_fb + depos;

		क्रम (j = 0; j < n32; j++) अणु
			अगर (j < 2 && j + 1 < n32 && !backward &&
			    !(((अचिन्हित दीर्घ)sfb | (अचिन्हित दीर्घ)dfb) & 63)) अणु
				करो अणु
					__raw_ग_लिखोl(sfb - tga_fb, tga_regs+TGA_COPY64_SRC);
					wmb();
					__raw_ग_लिखोl(dfb - tga_fb, tga_regs+TGA_COPY64_DST);
					wmb();
					sfb += 64;
					dfb += 64;
					j += 2;
				पूर्ण जबतक (j + 1 < n32);
				j--;
				जारी;
			पूर्ण
			__raw_ग_लिखोl(0xffffffff, sfb);
			wmb();
			__raw_ग_लिखोl(0xffffffff, dfb);
			wmb();
			sfb += step;
			dfb += step;
		पूर्ण

		अगर (mask_last) अणु
			sfb += last_step - step;
			dfb += last_step - step;
			__raw_ग_लिखोl(mask_last, sfb);
			wmb();
			__raw_ग_लिखोl(mask_last, dfb);
			wmb();
		पूर्ण

		sepos += yincr;
		depos += yincr;
	पूर्ण

	/* Reset the MODE रेजिस्टर to normal.  */
	__raw_ग_लिखोl(TGA_MODE_SBM_8BPP|TGA_MODE_SIMPLE, tga_regs+TGA_MODE_REG);
पूर्ण

अटल व्योम
tgafb_copyarea(काष्ठा fb_info *info, स्थिर काष्ठा fb_copyarea *area) 
अणु
	अचिन्हित दीर्घ dx, dy, width, height, sx, sy, vxres, vyres;
	अचिन्हित दीर्घ line_length, bpp;

	dx = area->dx;
	dy = area->dy;
	width = area->width;
	height = area->height;
	sx = area->sx;
	sy = area->sy;
	vxres = info->var.xres_भव;
	vyres = info->var.yres_भव;
	line_length = info->fix.line_length;

	/* The top left corners must be in the भव screen.  */
	अगर (dx > vxres || sx > vxres || dy > vyres || sy > vyres)
		वापस;

	/* Clip the destination.  */
	अगर (dx + width > vxres)
		width = vxres - dx;
	अगर (dy + height > vyres)
		height = vyres - dy;

	/* The source must be completely inside the भव screen.  */
	अगर (sx + width > vxres || sy + height > vyres)
		वापस;

	bpp = info->var.bits_per_pixel;

	/* Detect copies of the entire line.  */
	अगर (!(line_length & 63) && width * (bpp >> 3) == line_length) अणु
		अगर (bpp == 8)
			copyarea_line_8bpp(info, dy, sy, height, width);
		अन्यथा
			copyarea_line_32bpp(info, dy, sy, height, width);
	पूर्ण

	/* ??? The करोcumentation is unclear to me exactly how the pixelshअगरt
	   रेजिस्टर works in 32bpp mode.  Since I करोn't have hardware to test,
	   give up क्रम now and fall back on the generic routines.  */
	अन्यथा अगर (bpp == 32)
		cfb_copyarea(info, area);

	अन्यथा
		copyarea_8bpp(info, dx, dy, sx, sy, height,
			      width, line_length, area);
पूर्ण


/*
 *  Initialisation
 */

अटल व्योम
tgafb_init_fix(काष्ठा fb_info *info)
अणु
	काष्ठा tga_par *par = (काष्ठा tga_par *)info->par;
	पूर्णांक tga_bus_pci = dev_is_pci(par->dev);
	पूर्णांक tga_bus_tc = TGA_BUS_TC(par->dev);
	u8 tga_type = par->tga_type;
	स्थिर अक्षर *tga_type_name = शून्य;
	अचिन्हित memory_size;

	चयन (tga_type) अणु
	हाल TGA_TYPE_8PLANE:
		अगर (tga_bus_pci)
			tga_type_name = "Digital ZLXp-E1";
		अगर (tga_bus_tc)
			tga_type_name = "Digital ZLX-E1";
		memory_size = 2097152;
		अवरोध;
	हाल TGA_TYPE_24PLANE:
		अगर (tga_bus_pci)
			tga_type_name = "Digital ZLXp-E2";
		अगर (tga_bus_tc)
			tga_type_name = "Digital ZLX-E2";
		memory_size = 8388608;
		अवरोध;
	हाल TGA_TYPE_24PLUSZ:
		अगर (tga_bus_pci)
			tga_type_name = "Digital ZLXp-E3";
		अगर (tga_bus_tc)
			tga_type_name = "Digital ZLX-E3";
		memory_size = 16777216;
		अवरोध;
	पूर्ण
	अगर (!tga_type_name) अणु
		tga_type_name = "Unknown";
		memory_size = 16777216;
	पूर्ण

	strlcpy(info->fix.id, tga_type_name, माप(info->fix.id));

	info->fix.type = FB_TYPE_PACKED_PIXELS;
	info->fix.type_aux = 0;
	info->fix.visual = (tga_type == TGA_TYPE_8PLANE
			    ? FB_VISUAL_PSEUDOCOLOR
			    : FB_VISUAL_सूचीECTCOLOR);

	info->fix.smem_start = (माप_प्रकार) par->tga_fb_base;
	info->fix.smem_len = memory_size;
	info->fix.mmio_start = (माप_प्रकार) par->tga_regs_base;
	info->fix.mmio_len = 512;

	info->fix.xpanstep = 0;
	info->fix.ypanstep = 0;
	info->fix.ywrapstep = 0;

	info->fix.accel = FB_ACCEL_DEC_TGA;

	/*
	 * These are needed by fb_set_logo_truepalette(), so we
	 * set them here क्रम 24-plane cards.
	 */
	अगर (tga_type != TGA_TYPE_8PLANE) अणु
		info->var.red.length = 8;
		info->var.green.length = 8;
		info->var.blue.length = 8;
		info->var.red.offset = 16;
		info->var.green.offset = 8;
		info->var.blue.offset = 0;
	पूर्ण
पूर्ण

अटल पूर्णांक tgafb_pan_display(काष्ठा fb_var_screeninfo *var, काष्ठा fb_info *info)
अणु
	/* We just use this to catch चयनes out of graphics mode. */
	tgafb_set_par(info); /* A bit of overसमाप्त क्रम BASE_ADDR reset. */
	वापस 0;
पूर्ण

अटल पूर्णांक tgafb_रेजिस्टर(काष्ठा device *dev)
अणु
	अटल स्थिर काष्ठा fb_videomode modedb_tc = अणु
		/* 1280x1024 @ 72 Hz, 76.8 kHz hsync */
		"1280x1024@72", 0, 1280, 1024, 7645, 224, 28, 33, 3, 160, 3,
		FB_SYNC_ON_GREEN, FB_VMODE_NONINTERLACED
	पूर्ण;

	अटल अचिन्हित पूर्णांक स्थिर fb_offset_presets[4] = अणु
		TGA_8PLANE_FB_OFFSET,
		TGA_24PLANE_FB_OFFSET,
		0xffffffff,
		TGA_24PLUSZ_FB_OFFSET
	पूर्ण;

	स्थिर काष्ठा fb_videomode *modedb_tga = शून्य;
	resource_माप_प्रकार bar0_start = 0, bar0_len = 0;
	स्थिर अक्षर *mode_option_tga = शून्य;
	पूर्णांक tga_bus_pci = dev_is_pci(dev);
	पूर्णांक tga_bus_tc = TGA_BUS_TC(dev);
	अचिन्हित पूर्णांक modedbमाप_प्रकारga = 0;
	व्योम __iomem *mem_base;
	काष्ठा fb_info *info;
	काष्ठा tga_par *par;
	u8 tga_type;
	पूर्णांक ret = 0;

	/* Enable device in PCI config.  */
	अगर (tga_bus_pci && pci_enable_device(to_pci_dev(dev))) अणु
		prपूर्णांकk(KERN_ERR "tgafb: Cannot enable PCI device\n");
		वापस -ENODEV;
	पूर्ण

	/* Allocate the fb and par काष्ठाures.  */
	info = framebuffer_alloc(माप(काष्ठा tga_par), dev);
	अगर (!info)
		वापस -ENOMEM;

	par = info->par;
	dev_set_drvdata(dev, info);

	/* Request the mem regions.  */
	ret = -ENODEV;
	अगर (tga_bus_pci) अणु
		bar0_start = pci_resource_start(to_pci_dev(dev), 0);
		bar0_len = pci_resource_len(to_pci_dev(dev), 0);
	पूर्ण
	अगर (tga_bus_tc) अणु
		bar0_start = to_tc_dev(dev)->resource.start;
		bar0_len = to_tc_dev(dev)->resource.end - bar0_start + 1;
	पूर्ण
	अगर (!request_mem_region (bar0_start, bar0_len, "tgafb")) अणु
		prपूर्णांकk(KERN_ERR "tgafb: cannot reserve FB region\n");
		जाओ err0;
	पूर्ण

	/* Map the framebuffer.  */
	mem_base = ioremap(bar0_start, bar0_len);
	अगर (!mem_base) अणु
		prपूर्णांकk(KERN_ERR "tgafb: Cannot map MMIO\n");
		जाओ err1;
	पूर्ण

	/* Grab info about the card.  */
	tga_type = (पढ़ोl(mem_base) >> 12) & 0x0f;
	par->dev = dev;
	par->tga_mem_base = mem_base;
	par->tga_fb_base = mem_base + fb_offset_presets[tga_type];
	par->tga_regs_base = mem_base + TGA_REGS_OFFSET;
	par->tga_type = tga_type;
	अगर (tga_bus_pci)
		par->tga_chip_rev = (to_pci_dev(dev))->revision;
	अगर (tga_bus_tc)
		par->tga_chip_rev = TGA_READ_REG(par, TGA_START_REG) & 0xff;

	/* Setup framebuffer.  */
	info->flags = FBINFO_DEFAULT | FBINFO_HWACCEL_COPYAREA |
		      FBINFO_HWACCEL_IMAGEBLIT | FBINFO_HWACCEL_FILLRECT;
	info->fbops = &tgafb_ops;
	info->screen_base = par->tga_fb_base;
	info->pseuकरो_palette = par->palette;

	/* This should give a reasonable शेष video mode.  */
	अगर (tga_bus_pci) अणु
		mode_option_tga = mode_option_pci;
	पूर्ण
	अगर (tga_bus_tc) अणु
		mode_option_tga = mode_option_tc;
		modedb_tga = &modedb_tc;
		modedbमाप_प्रकारga = 1;
	पूर्ण

	tgafb_init_fix(info);

	ret = fb_find_mode(&info->var, info,
			   mode_option ? mode_option : mode_option_tga,
			   modedb_tga, modedbमाप_प्रकारga, शून्य,
			   tga_type == TGA_TYPE_8PLANE ? 8 : 32);
	अगर (ret == 0 || ret == 4) अणु
		prपूर्णांकk(KERN_ERR "tgafb: Could not find valid video mode\n");
		ret = -EINVAL;
		जाओ err1;
	पूर्ण

	अगर (fb_alloc_cmap(&info->cmap, 256, 0)) अणु
		prपूर्णांकk(KERN_ERR "tgafb: Could not allocate color map\n");
		ret = -ENOMEM;
		जाओ err1;
	पूर्ण

	tgafb_set_par(info);

	अगर (रेजिस्टर_framebuffer(info) < 0) अणु
		prपूर्णांकk(KERN_ERR "tgafb: Could not register framebuffer\n");
		ret = -EINVAL;
		जाओ err2;
	पूर्ण

	अगर (tga_bus_pci) अणु
		pr_info("tgafb: DC21030 [TGA] detected, rev=0x%02x\n",
			par->tga_chip_rev);
		pr_info("tgafb: at PCI bus %d, device %d, function %d\n",
			to_pci_dev(dev)->bus->number,
			PCI_SLOT(to_pci_dev(dev)->devfn),
			PCI_FUNC(to_pci_dev(dev)->devfn));
	पूर्ण
	अगर (tga_bus_tc)
		pr_info("tgafb: SFB+ detected, rev=0x%02x\n",
			par->tga_chip_rev);
	fb_info(info, "%s frame buffer device at 0x%lx\n",
		info->fix.id, (दीर्घ)bar0_start);

	वापस 0;

 err2:
	fb_dealloc_cmap(&info->cmap);
 err1:
	अगर (mem_base)
		iounmap(mem_base);
	release_mem_region(bar0_start, bar0_len);
 err0:
	framebuffer_release(info);
	वापस ret;
पूर्ण

अटल व्योम tgafb_unरेजिस्टर(काष्ठा device *dev)
अणु
	resource_माप_प्रकार bar0_start = 0, bar0_len = 0;
	पूर्णांक tga_bus_pci = dev_is_pci(dev);
	पूर्णांक tga_bus_tc = TGA_BUS_TC(dev);
	काष्ठा fb_info *info = शून्य;
	काष्ठा tga_par *par;

	info = dev_get_drvdata(dev);
	अगर (!info)
		वापस;

	par = info->par;
	unरेजिस्टर_framebuffer(info);
	fb_dealloc_cmap(&info->cmap);
	iounmap(par->tga_mem_base);
	अगर (tga_bus_pci) अणु
		bar0_start = pci_resource_start(to_pci_dev(dev), 0);
		bar0_len = pci_resource_len(to_pci_dev(dev), 0);
	पूर्ण
	अगर (tga_bus_tc) अणु
		bar0_start = to_tc_dev(dev)->resource.start;
		bar0_len = to_tc_dev(dev)->resource.end - bar0_start + 1;
	पूर्ण
	release_mem_region(bar0_start, bar0_len);
	framebuffer_release(info);
पूर्ण

अटल व्योम tgafb_निकास(व्योम)
अणु
	tc_unरेजिस्टर_driver(&tgafb_tc_driver);
	pci_unरेजिस्टर_driver(&tgafb_pci_driver);
पूर्ण

#अगर_अघोषित MODULE
अटल पूर्णांक tgafb_setup(अक्षर *arg)
अणु
	अक्षर *this_opt;

	अगर (arg && *arg) अणु
		जबतक ((this_opt = strsep(&arg, ","))) अणु
			अगर (!*this_opt)
				जारी;
			अगर (!म_भेदन(this_opt, "mode:", 5))
				mode_option = this_opt+5;
			अन्यथा
				prपूर्णांकk(KERN_ERR
				       "tgafb: unknown parameter %s\n",
				       this_opt);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण
#पूर्ण_अगर /* !MODULE */

अटल पूर्णांक tgafb_init(व्योम)
अणु
	पूर्णांक status;
#अगर_अघोषित MODULE
	अक्षर *option = शून्य;

	अगर (fb_get_options("tgafb", &option))
		वापस -ENODEV;
	tgafb_setup(option);
#पूर्ण_अगर
	status = pci_रेजिस्टर_driver(&tgafb_pci_driver);
	अगर (!status)
		status = tc_रेजिस्टर_driver(&tgafb_tc_driver);
	वापस status;
पूर्ण

/*
 *  Modularisation
 */

module_init(tgafb_init);
module_निकास(tgafb_निकास);

MODULE_DESCRIPTION("Framebuffer driver for TGA/SFB+ chipset");
MODULE_LICENSE("GPL");
