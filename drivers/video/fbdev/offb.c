<शैली गुरु>
/*
 *  linux/drivers/video/offb.c -- Open Firmware based frame buffer device
 *
 *	Copyright (C) 1997 Geert Uytterhoeven
 *
 *  This driver is partly based on the PowerMac console driver:
 *
 *	Copyright (C) 1996 Paul Mackerras
 *
 *  This file is subject to the terms and conditions of the GNU General Public
 *  License. See the file COPYING in the मुख्य directory of this archive क्रम
 *  more details.
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/माला.स>
#समावेश <linux/mm.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/delay.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/fb.h>
#समावेश <linux/init.h>
#समावेश <linux/ioport.h>
#समावेश <linux/pci.h>
#समावेश <यंत्र/पन.स>

#अगर_घोषित CONFIG_PPC32
#समावेश <यंत्र/bootx.h>
#पूर्ण_अगर

#समावेश "macmodes.h"

/* Supported palette hacks */
क्रमागत अणु
	cmap_unknown,
	cmap_simple,		/* ATI Mach64 */
	cmap_r128,		/* ATI Rage128 */
	cmap_M3A,		/* ATI Rage Mobility M3 Head A */
	cmap_M3B,		/* ATI Rage Mobility M3 Head B */
	cmap_radeon,		/* ATI Radeon */
	cmap_gxt2000,		/* IBM GXT2000 */
	cmap_avivo,		/* ATI R5xx */
	cmap_qemu,		/* qemu vga */
पूर्ण;

काष्ठा offb_par अणु
	अस्थिर व्योम __iomem *cmap_adr;
	अस्थिर व्योम __iomem *cmap_data;
	पूर्णांक cmap_type;
	पूर्णांक blanked;
पूर्ण;

काष्ठा offb_par शेष_par;

#अगर_घोषित CONFIG_PPC32
बाह्य boot_infos_t *boot_infos;
#पूर्ण_अगर

/* Definitions used by the Avivo palette hack */
#घोषणा AVIVO_DC_LUT_RW_SELECT                  0x6480
#घोषणा AVIVO_DC_LUT_RW_MODE                    0x6484
#घोषणा AVIVO_DC_LUT_RW_INDEX                   0x6488
#घोषणा AVIVO_DC_LUT_SEQ_COLOR                  0x648c
#घोषणा AVIVO_DC_LUT_PWL_DATA                   0x6490
#घोषणा AVIVO_DC_LUT_30_COLOR                   0x6494
#घोषणा AVIVO_DC_LUT_READ_PIPE_SELECT           0x6498
#घोषणा AVIVO_DC_LUT_WRITE_EN_MASK              0x649c
#घोषणा AVIVO_DC_LUT_AUTOFILL                   0x64a0

#घोषणा AVIVO_DC_LUTA_CONTROL                   0x64c0
#घोषणा AVIVO_DC_LUTA_BLACK_OFFSET_BLUE         0x64c4
#घोषणा AVIVO_DC_LUTA_BLACK_OFFSET_GREEN        0x64c8
#घोषणा AVIVO_DC_LUTA_BLACK_OFFSET_RED          0x64cc
#घोषणा AVIVO_DC_LUTA_WHITE_OFFSET_BLUE         0x64d0
#घोषणा AVIVO_DC_LUTA_WHITE_OFFSET_GREEN        0x64d4
#घोषणा AVIVO_DC_LUTA_WHITE_OFFSET_RED          0x64d8

#घोषणा AVIVO_DC_LUTB_CONTROL                   0x6cc0
#घोषणा AVIVO_DC_LUTB_BLACK_OFFSET_BLUE         0x6cc4
#घोषणा AVIVO_DC_LUTB_BLACK_OFFSET_GREEN        0x6cc8
#घोषणा AVIVO_DC_LUTB_BLACK_OFFSET_RED          0x6ccc
#घोषणा AVIVO_DC_LUTB_WHITE_OFFSET_BLUE         0x6cd0
#घोषणा AVIVO_DC_LUTB_WHITE_OFFSET_GREEN        0x6cd4
#घोषणा AVIVO_DC_LUTB_WHITE_OFFSET_RED          0x6cd8

    /*
     *  Set a single color रेजिस्टर. The values supplied are alपढ़ोy
     *  rounded करोwn to the hardware's capabilities (according to the
     *  entries in the var काष्ठाure). Return != 0 क्रम invalid regno.
     */

अटल पूर्णांक offb_setcolreg(u_पूर्णांक regno, u_पूर्णांक red, u_पूर्णांक green, u_पूर्णांक blue,
			  u_पूर्णांक transp, काष्ठा fb_info *info)
अणु
	काष्ठा offb_par *par = (काष्ठा offb_par *) info->par;

	अगर (info->fix.visual == FB_VISUAL_TRUECOLOR) अणु
		u32 *pal = info->pseuकरो_palette;
		u32 cr = red >> (16 - info->var.red.length);
		u32 cg = green >> (16 - info->var.green.length);
		u32 cb = blue >> (16 - info->var.blue.length);
		u32 value;

		अगर (regno >= 16)
			वापस -EINVAL;

		value = (cr << info->var.red.offset) |
			(cg << info->var.green.offset) |
			(cb << info->var.blue.offset);
		अगर (info->var.transp.length > 0) अणु
			u32 mask = (1 << info->var.transp.length) - 1;
			mask <<= info->var.transp.offset;
			value |= mask;
		पूर्ण
		pal[regno] = value;
		वापस 0;
	पूर्ण

	अगर (regno > 255)
		वापस -EINVAL;

	red >>= 8;
	green >>= 8;
	blue >>= 8;

	अगर (!par->cmap_adr)
		वापस 0;

	चयन (par->cmap_type) अणु
	हाल cmap_simple:
		ग_लिखोb(regno, par->cmap_adr);
		ग_लिखोb(red, par->cmap_data);
		ग_लिखोb(green, par->cmap_data);
		ग_लिखोb(blue, par->cmap_data);
		अवरोध;
	हाल cmap_M3A:
		/* Clear PALETTE_ACCESS_CNTL in DAC_CNTL */
		out_le32(par->cmap_adr + 0x58,
			 in_le32(par->cmap_adr + 0x58) & ~0x20);
		fallthrough;
	हाल cmap_r128:
		/* Set palette index & data */
		out_8(par->cmap_adr + 0xb0, regno);
		out_le32(par->cmap_adr + 0xb4,
			 (red << 16 | green << 8 | blue));
		अवरोध;
	हाल cmap_M3B:
		/* Set PALETTE_ACCESS_CNTL in DAC_CNTL */
		out_le32(par->cmap_adr + 0x58,
			 in_le32(par->cmap_adr + 0x58) | 0x20);
		/* Set palette index & data */
		out_8(par->cmap_adr + 0xb0, regno);
		out_le32(par->cmap_adr + 0xb4, (red << 16 | green << 8 | blue));
		अवरोध;
	हाल cmap_radeon:
		/* Set palette index & data (could be smarter) */
		out_8(par->cmap_adr + 0xb0, regno);
		out_le32(par->cmap_adr + 0xb4, (red << 16 | green << 8 | blue));
		अवरोध;
	हाल cmap_gxt2000:
		out_le32(((अचिन्हित __iomem *) par->cmap_adr) + regno,
			 (red << 16 | green << 8 | blue));
		अवरोध;
	हाल cmap_avivo:
		/* Write to both LUTs क्रम now */
		ग_लिखोl(1, par->cmap_adr + AVIVO_DC_LUT_RW_SELECT);
		ग_लिखोb(regno, par->cmap_adr + AVIVO_DC_LUT_RW_INDEX);
		ग_लिखोl(((red) << 22) | ((green) << 12) | ((blue) << 2),
		       par->cmap_adr + AVIVO_DC_LUT_30_COLOR);
		ग_लिखोl(0, par->cmap_adr + AVIVO_DC_LUT_RW_SELECT);
		ग_लिखोb(regno, par->cmap_adr + AVIVO_DC_LUT_RW_INDEX);
		ग_लिखोl(((red) << 22) | ((green) << 12) | ((blue) << 2),
		       par->cmap_adr + AVIVO_DC_LUT_30_COLOR);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

    /*
     *  Blank the display.
     */

अटल पूर्णांक offb_blank(पूर्णांक blank, काष्ठा fb_info *info)
अणु
	काष्ठा offb_par *par = (काष्ठा offb_par *) info->par;
	पूर्णांक i, j;

	अगर (!par->cmap_adr)
		वापस 0;

	अगर (!par->blanked)
		अगर (!blank)
			वापस 0;

	par->blanked = blank;

	अगर (blank)
		क्रम (i = 0; i < 256; i++) अणु
			चयन (par->cmap_type) अणु
			हाल cmap_simple:
				ग_लिखोb(i, par->cmap_adr);
				क्रम (j = 0; j < 3; j++)
					ग_लिखोb(0, par->cmap_data);
				अवरोध;
			हाल cmap_M3A:
				/* Clear PALETTE_ACCESS_CNTL in DAC_CNTL */
				out_le32(par->cmap_adr + 0x58,
					 in_le32(par->cmap_adr + 0x58) & ~0x20);
				fallthrough;
			हाल cmap_r128:
				/* Set palette index & data */
				out_8(par->cmap_adr + 0xb0, i);
				out_le32(par->cmap_adr + 0xb4, 0);
				अवरोध;
			हाल cmap_M3B:
				/* Set PALETTE_ACCESS_CNTL in DAC_CNTL */
				out_le32(par->cmap_adr + 0x58,
					 in_le32(par->cmap_adr + 0x58) | 0x20);
				/* Set palette index & data */
				out_8(par->cmap_adr + 0xb0, i);
				out_le32(par->cmap_adr + 0xb4, 0);
				अवरोध;
			हाल cmap_radeon:
				out_8(par->cmap_adr + 0xb0, i);
				out_le32(par->cmap_adr + 0xb4, 0);
				अवरोध;
			हाल cmap_gxt2000:
				out_le32(((अचिन्हित __iomem *) par->cmap_adr) + i,
					 0);
				अवरोध;
			हाल cmap_avivo:
				ग_लिखोl(1, par->cmap_adr + AVIVO_DC_LUT_RW_SELECT);
				ग_लिखोb(i, par->cmap_adr + AVIVO_DC_LUT_RW_INDEX);
				ग_लिखोl(0, par->cmap_adr + AVIVO_DC_LUT_30_COLOR);
				ग_लिखोl(0, par->cmap_adr + AVIVO_DC_LUT_RW_SELECT);
				ग_लिखोb(i, par->cmap_adr + AVIVO_DC_LUT_RW_INDEX);
				ग_लिखोl(0, par->cmap_adr + AVIVO_DC_LUT_30_COLOR);
				अवरोध;
			पूर्ण
	पूर्ण अन्यथा
		fb_set_cmap(&info->cmap, info);
	वापस 0;
पूर्ण

अटल पूर्णांक offb_set_par(काष्ठा fb_info *info)
अणु
	काष्ठा offb_par *par = (काष्ठा offb_par *) info->par;

	/* On avivo, initialize palette control */
	अगर (par->cmap_type == cmap_avivo) अणु
		ग_लिखोl(0, par->cmap_adr + AVIVO_DC_LUTA_CONTROL);
		ग_लिखोl(0, par->cmap_adr + AVIVO_DC_LUTA_BLACK_OFFSET_BLUE);
		ग_लिखोl(0, par->cmap_adr + AVIVO_DC_LUTA_BLACK_OFFSET_GREEN);
		ग_लिखोl(0, par->cmap_adr + AVIVO_DC_LUTA_BLACK_OFFSET_RED);
		ग_लिखोl(0x0000ffff, par->cmap_adr + AVIVO_DC_LUTA_WHITE_OFFSET_BLUE);
		ग_लिखोl(0x0000ffff, par->cmap_adr + AVIVO_DC_LUTA_WHITE_OFFSET_GREEN);
		ग_लिखोl(0x0000ffff, par->cmap_adr + AVIVO_DC_LUTA_WHITE_OFFSET_RED);
		ग_लिखोl(0, par->cmap_adr + AVIVO_DC_LUTB_CONTROL);
		ग_लिखोl(0, par->cmap_adr + AVIVO_DC_LUTB_BLACK_OFFSET_BLUE);
		ग_लिखोl(0, par->cmap_adr + AVIVO_DC_LUTB_BLACK_OFFSET_GREEN);
		ग_लिखोl(0, par->cmap_adr + AVIVO_DC_LUTB_BLACK_OFFSET_RED);
		ग_लिखोl(0x0000ffff, par->cmap_adr + AVIVO_DC_LUTB_WHITE_OFFSET_BLUE);
		ग_लिखोl(0x0000ffff, par->cmap_adr + AVIVO_DC_LUTB_WHITE_OFFSET_GREEN);
		ग_लिखोl(0x0000ffff, par->cmap_adr + AVIVO_DC_LUTB_WHITE_OFFSET_RED);
		ग_लिखोl(1, par->cmap_adr + AVIVO_DC_LUT_RW_SELECT);
		ग_लिखोl(0, par->cmap_adr + AVIVO_DC_LUT_RW_MODE);
		ग_लिखोl(0x0000003f, par->cmap_adr + AVIVO_DC_LUT_WRITE_EN_MASK);
		ग_लिखोl(0, par->cmap_adr + AVIVO_DC_LUT_RW_SELECT);
		ग_लिखोl(0, par->cmap_adr + AVIVO_DC_LUT_RW_MODE);
		ग_लिखोl(0x0000003f, par->cmap_adr + AVIVO_DC_LUT_WRITE_EN_MASK);
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम offb_destroy(काष्ठा fb_info *info)
अणु
	अगर (info->screen_base)
		iounmap(info->screen_base);
	release_mem_region(info->apertures->ranges[0].base, info->apertures->ranges[0].size);
	fb_dealloc_cmap(&info->cmap);
	framebuffer_release(info);
पूर्ण

अटल स्थिर काष्ठा fb_ops offb_ops = अणु
	.owner		= THIS_MODULE,
	.fb_destroy	= offb_destroy,
	.fb_setcolreg	= offb_setcolreg,
	.fb_set_par	= offb_set_par,
	.fb_blank	= offb_blank,
	.fb_fillrect	= cfb_fillrect,
	.fb_copyarea	= cfb_copyarea,
	.fb_imageblit	= cfb_imageblit,
पूर्ण;

अटल व्योम __iomem *offb_map_reg(काष्ठा device_node *np, पूर्णांक index,
				  अचिन्हित दीर्घ offset, अचिन्हित दीर्घ size)
अणु
	स्थिर __be32 *addrp;
	u64 asize, taddr;
	अचिन्हित पूर्णांक flags;

	addrp = of_get_pci_address(np, index, &asize, &flags);
	अगर (addrp == शून्य)
		addrp = of_get_address(np, index, &asize, &flags);
	अगर (addrp == शून्य)
		वापस शून्य;
	अगर ((flags & (IORESOURCE_IO | IORESOURCE_MEM)) == 0)
		वापस शून्य;
	अगर ((offset + size) > asize)
		वापस शून्य;
	taddr = of_translate_address(np, addrp);
	अगर (taddr == OF_BAD_ADDR)
		वापस शून्य;
	वापस ioremap(taddr + offset, size);
पूर्ण

अटल व्योम offb_init_palette_hacks(काष्ठा fb_info *info, काष्ठा device_node *dp,
				    अचिन्हित दीर्घ address)
अणु
	काष्ठा offb_par *par = (काष्ठा offb_par *) info->par;

	अगर (of_node_name_prefix(dp, "ATY,Rage128")) अणु
		par->cmap_adr = offb_map_reg(dp, 2, 0, 0x1fff);
		अगर (par->cmap_adr)
			par->cmap_type = cmap_r128;
	पूर्ण अन्यथा अगर (of_node_name_prefix(dp, "ATY,RageM3pA") ||
		   of_node_name_prefix(dp, "ATY,RageM3p12A")) अणु
		par->cmap_adr = offb_map_reg(dp, 2, 0, 0x1fff);
		अगर (par->cmap_adr)
			par->cmap_type = cmap_M3A;
	पूर्ण अन्यथा अगर (of_node_name_prefix(dp, "ATY,RageM3pB")) अणु
		par->cmap_adr = offb_map_reg(dp, 2, 0, 0x1fff);
		अगर (par->cmap_adr)
			par->cmap_type = cmap_M3B;
	पूर्ण अन्यथा अगर (of_node_name_prefix(dp, "ATY,Rage6")) अणु
		par->cmap_adr = offb_map_reg(dp, 1, 0, 0x1fff);
		अगर (par->cmap_adr)
			par->cmap_type = cmap_radeon;
	पूर्ण अन्यथा अगर (of_node_name_prefix(dp, "ATY,")) अणु
		अचिन्हित दीर्घ base = address & 0xff000000UL;
		par->cmap_adr =
			ioremap(base + 0x7ff000, 0x1000) + 0xcc0;
		par->cmap_data = par->cmap_adr + 1;
		par->cmap_type = cmap_simple;
	पूर्ण अन्यथा अगर (dp && (of_device_is_compatible(dp, "pci1014,b7") ||
			  of_device_is_compatible(dp, "pci1014,21c"))) अणु
		par->cmap_adr = offb_map_reg(dp, 0, 0x6000, 0x1000);
		अगर (par->cmap_adr)
			par->cmap_type = cmap_gxt2000;
	पूर्ण अन्यथा अगर (of_node_name_prefix(dp, "vga,Display-")) अणु
		/* Look क्रम AVIVO initialized by SLOF */
		काष्ठा device_node *pciparent = of_get_parent(dp);
		स्थिर u32 *vid, *did;
		vid = of_get_property(pciparent, "vendor-id", शून्य);
		did = of_get_property(pciparent, "device-id", शून्य);
		/* This will match most R5xx */
		अगर (vid && did && *vid == 0x1002 &&
		    ((*did >= 0x7100 && *did < 0x7800) ||
		     (*did >= 0x9400))) अणु
			par->cmap_adr = offb_map_reg(pciparent, 2, 0, 0x10000);
			अगर (par->cmap_adr)
				par->cmap_type = cmap_avivo;
		पूर्ण
		of_node_put(pciparent);
	पूर्ण अन्यथा अगर (dp && of_device_is_compatible(dp, "qemu,std-vga")) अणु
#अगर_घोषित __BIG_ENDIAN
		स्थिर __be32 io_of_addr[3] = अणु 0x01000000, 0x0, 0x0 पूर्ण;
#अन्यथा
		स्थिर __be32 io_of_addr[3] = अणु 0x00000001, 0x0, 0x0 पूर्ण;
#पूर्ण_अगर
		u64 io_addr = of_translate_address(dp, io_of_addr);
		अगर (io_addr != OF_BAD_ADDR) अणु
			par->cmap_adr = ioremap(io_addr + 0x3c8, 2);
			अगर (par->cmap_adr) अणु
				par->cmap_type = cmap_simple;
				par->cmap_data = par->cmap_adr + 1;
			पूर्ण
		पूर्ण
	पूर्ण
	info->fix.visual = (par->cmap_type != cmap_unknown) ?
		FB_VISUAL_PSEUDOCOLOR : FB_VISUAL_STATIC_PSEUDOCOLOR;
पूर्ण

अटल व्योम __init offb_init_fb(स्थिर अक्षर *name,
				पूर्णांक width, पूर्णांक height, पूर्णांक depth,
				पूर्णांक pitch, अचिन्हित दीर्घ address,
				पूर्णांक क्रमeign_endian, काष्ठा device_node *dp)
अणु
	अचिन्हित दीर्घ res_size = pitch * height;
	काष्ठा offb_par *par = &शेष_par;
	अचिन्हित दीर्घ res_start = address;
	काष्ठा fb_fix_screeninfo *fix;
	काष्ठा fb_var_screeninfo *var;
	काष्ठा fb_info *info;

	अगर (!request_mem_region(res_start, res_size, "offb"))
		वापस;

	prपूर्णांकk(KERN_INFO
	       "Using unsupported %dx%d %s at %lx, depth=%d, pitch=%d\n",
	       width, height, name, address, depth, pitch);
	अगर (depth != 8 && depth != 15 && depth != 16 && depth != 32) अणु
		prपूर्णांकk(KERN_ERR "%pOF: can't use depth = %d\n", dp, depth);
		release_mem_region(res_start, res_size);
		वापस;
	पूर्ण

	info = framebuffer_alloc(माप(u32) * 16, शून्य);

	अगर (info == 0) अणु
		release_mem_region(res_start, res_size);
		वापस;
	पूर्ण

	fix = &info->fix;
	var = &info->var;
	info->par = par;

	अगर (name) अणु
		म_नकल(fix->id, "OFfb ");
		म_जोड़न(fix->id, name, माप(fix->id) - माप("OFfb "));
		fix->id[माप(fix->id) - 1] = '\0';
	पूर्ण अन्यथा
		snम_लिखो(fix->id, माप(fix->id), "OFfb %pOFn", dp);


	var->xres = var->xres_भव = width;
	var->yres = var->yres_भव = height;
	fix->line_length = pitch;

	fix->smem_start = address;
	fix->smem_len = pitch * height;
	fix->type = FB_TYPE_PACKED_PIXELS;
	fix->type_aux = 0;

	par->cmap_type = cmap_unknown;
	अगर (depth == 8)
		offb_init_palette_hacks(info, dp, address);
	अन्यथा
		fix->visual = FB_VISUAL_TRUECOLOR;

	var->xoffset = var->yoffset = 0;
	चयन (depth) अणु
	हाल 8:
		var->bits_per_pixel = 8;
		var->red.offset = 0;
		var->red.length = 8;
		var->green.offset = 0;
		var->green.length = 8;
		var->blue.offset = 0;
		var->blue.length = 8;
		var->transp.offset = 0;
		var->transp.length = 0;
		अवरोध;
	हाल 15:		/* RGB 555 */
		var->bits_per_pixel = 16;
		var->red.offset = 10;
		var->red.length = 5;
		var->green.offset = 5;
		var->green.length = 5;
		var->blue.offset = 0;
		var->blue.length = 5;
		var->transp.offset = 0;
		var->transp.length = 0;
		अवरोध;
	हाल 16:		/* RGB 565 */
		var->bits_per_pixel = 16;
		var->red.offset = 11;
		var->red.length = 5;
		var->green.offset = 5;
		var->green.length = 6;
		var->blue.offset = 0;
		var->blue.length = 5;
		var->transp.offset = 0;
		var->transp.length = 0;
		अवरोध;
	हाल 32:		/* RGB 888 */
		var->bits_per_pixel = 32;
		var->red.offset = 16;
		var->red.length = 8;
		var->green.offset = 8;
		var->green.length = 8;
		var->blue.offset = 0;
		var->blue.length = 8;
		var->transp.offset = 24;
		var->transp.length = 8;
		अवरोध;
	पूर्ण
	var->red.msb_right = var->green.msb_right = var->blue.msb_right =
	    var->transp.msb_right = 0;
	var->grayscale = 0;
	var->nonstd = 0;
	var->activate = 0;
	var->height = var->width = -1;
	var->pixघड़ी = 10000;
	var->left_margin = var->right_margin = 16;
	var->upper_margin = var->lower_margin = 16;
	var->hsync_len = var->vsync_len = 8;
	var->sync = 0;
	var->vmode = FB_VMODE_NONINTERLACED;

	/* set offb aperture size क्रम generic probing */
	info->apertures = alloc_apertures(1);
	अगर (!info->apertures)
		जाओ out_aper;
	info->apertures->ranges[0].base = address;
	info->apertures->ranges[0].size = fix->smem_len;

	info->fbops = &offb_ops;
	info->screen_base = ioremap(address, fix->smem_len);
	info->pseuकरो_palette = (व्योम *) (info + 1);
	info->flags = FBINFO_DEFAULT | FBINFO_MISC_FIRMWARE | क्रमeign_endian;

	fb_alloc_cmap(&info->cmap, 256, 0);

	अगर (रेजिस्टर_framebuffer(info) < 0)
		जाओ out_err;

	fb_info(info, "Open Firmware frame buffer device on %pOF\n", dp);
	वापस;

out_err:
	fb_dealloc_cmap(&info->cmap);
	iounmap(info->screen_base);
out_aper:
	iounmap(par->cmap_adr);
	par->cmap_adr = शून्य;
	framebuffer_release(info);
	release_mem_region(res_start, res_size);
पूर्ण


अटल व्योम __init offb_init_nodriver(काष्ठा device_node *dp, पूर्णांक no_real_node)
अणु
	अचिन्हित पूर्णांक len;
	पूर्णांक i, width = 640, height = 480, depth = 8, pitch = 640;
	अचिन्हित पूर्णांक flags, rsize, addr_prop = 0;
	अचिन्हित दीर्घ max_size = 0;
	u64 rstart, address = OF_BAD_ADDR;
	स्थिर __be32 *pp, *addrp, *up;
	u64 asize;
	पूर्णांक क्रमeign_endian = 0;

#अगर_घोषित __BIG_ENDIAN
	अगर (of_get_property(dp, "little-endian", शून्य))
		क्रमeign_endian = FBINFO_FOREIGN_ENDIAN;
#अन्यथा
	अगर (of_get_property(dp, "big-endian", शून्य))
		क्रमeign_endian = FBINFO_FOREIGN_ENDIAN;
#पूर्ण_अगर

	pp = of_get_property(dp, "linux,bootx-depth", &len);
	अगर (pp == शून्य)
		pp = of_get_property(dp, "depth", &len);
	अगर (pp && len == माप(u32))
		depth = be32_to_cpup(pp);

	pp = of_get_property(dp, "linux,bootx-width", &len);
	अगर (pp == शून्य)
		pp = of_get_property(dp, "width", &len);
	अगर (pp && len == माप(u32))
		width = be32_to_cpup(pp);

	pp = of_get_property(dp, "linux,bootx-height", &len);
	अगर (pp == शून्य)
		pp = of_get_property(dp, "height", &len);
	अगर (pp && len == माप(u32))
		height = be32_to_cpup(pp);

	pp = of_get_property(dp, "linux,bootx-linebytes", &len);
	अगर (pp == शून्य)
		pp = of_get_property(dp, "linebytes", &len);
	अगर (pp && len == माप(u32) && (*pp != 0xffffffffu))
		pitch = be32_to_cpup(pp);
	अन्यथा
		pitch = width * ((depth + 7) / 8);

	rsize = (अचिन्हित दीर्घ)pitch * (अचिन्हित दीर्घ)height;

	/* Ok, now we try to figure out the address of the framebuffer.
	 *
	 * Unक्रमtunately, Open Firmware करोesn't provide a standard way to करो
	 * so. All we can करो is a करोdgy heuristic that happens to work in
	 * practice. On most machines, the "address" property contains what
	 * we need, though not on Matrox cards found in IBM machines. What I've
	 * found that appears to give good results is to go through the PCI
	 * ranges and pick one that is both big enough and अगर possible enबंदs
	 * the "address" property. If none match, we pick the biggest
	 */
	up = of_get_property(dp, "linux,bootx-addr", &len);
	अगर (up == शून्य)
		up = of_get_property(dp, "address", &len);
	अगर (up && len == माप(u32))
		addr_prop = *up;

	/* Hack क्रम when BootX is passing us */
	अगर (no_real_node)
		जाओ skip_addr;

	क्रम (i = 0; (addrp = of_get_address(dp, i, &asize, &flags))
		     != शून्य; i++) अणु
		पूर्णांक match_addrp = 0;

		अगर (!(flags & IORESOURCE_MEM))
			जारी;
		अगर (asize < rsize)
			जारी;
		rstart = of_translate_address(dp, addrp);
		अगर (rstart == OF_BAD_ADDR)
			जारी;
		अगर (addr_prop && (rstart <= addr_prop) &&
		    ((rstart + asize) >= (addr_prop + rsize)))
			match_addrp = 1;
		अगर (match_addrp) अणु
			address = addr_prop;
			अवरोध;
		पूर्ण
		अगर (rsize > max_size) अणु
			max_size = rsize;
			address = OF_BAD_ADDR;
 		पूर्ण

		अगर (address == OF_BAD_ADDR)
			address = rstart;
	पूर्ण
 skip_addr:
	अगर (address == OF_BAD_ADDR && addr_prop)
		address = (u64)addr_prop;
	अगर (address != OF_BAD_ADDR) अणु
#अगर_घोषित CONFIG_PCI
		स्थिर __be32 *vidp, *didp;
		u32 vid, did;
		काष्ठा pci_dev *pdev;

		vidp = of_get_property(dp, "vendor-id", शून्य);
		didp = of_get_property(dp, "device-id", शून्य);
		अगर (vidp && didp) अणु
			vid = be32_to_cpup(vidp);
			did = be32_to_cpup(didp);
			pdev = pci_get_device(vid, did, शून्य);
			अगर (!pdev || pci_enable_device(pdev))
				वापस;
		पूर्ण
#पूर्ण_अगर
		/* kludge क्रम valkyrie */
		अगर (of_node_name_eq(dp, "valkyrie"))
			address += 0x1000;
		offb_init_fb(no_real_node ? "bootx" : शून्य,
			     width, height, depth, pitch, address,
			     क्रमeign_endian, no_real_node ? शून्य : dp);
	पूर्ण
पूर्ण

अटल पूर्णांक __init offb_init(व्योम)
अणु
	काष्ठा device_node *dp = शून्य, *boot_disp = शून्य;

	अगर (fb_get_options("offb", शून्य))
		वापस -ENODEV;

	/* Check अगर we have a MacOS display without a node spec */
	अगर (of_get_property(of_chosen, "linux,bootx-noscreen", शून्य) != शून्य) अणु
		/* The old code tried to work out which node was the MacOS
		 * display based on the address. I'm dropping that since the
		 * lack of a node spec only happens with old BootX versions
		 * (users can update) and with this code, they'll still get
		 * a display (just not the palette hacks).
		 */
		offb_init_nodriver(of_chosen, 1);
	पूर्ण

	क्रम_each_node_by_type(dp, "display") अणु
		अगर (of_get_property(dp, "linux,opened", शून्य) &&
		    of_get_property(dp, "linux,boot-display", शून्य)) अणु
			boot_disp = dp;
			offb_init_nodriver(dp, 0);
		पूर्ण
	पूर्ण
	क्रम_each_node_by_type(dp, "display") अणु
		अगर (of_get_property(dp, "linux,opened", शून्य) &&
		    dp != boot_disp)
			offb_init_nodriver(dp, 0);
	पूर्ण

	वापस 0;
पूर्ण


module_init(offb_init);
MODULE_LICENSE("GPL");
