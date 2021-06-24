<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright 1998-2008 VIA Technologies, Inc. All Rights Reserved.
 * Copyright 2001-2008 S3 Graphics, Inc. All Rights Reserved.

 */
#समावेश <linux/via-core.h>
#समावेश "global.h"

/*
 * Figure out an appropriate bytes-per-pixel setting.
 */
अटल पूर्णांक viafb_set_bpp(व्योम __iomem *engine, u8 bpp)
अणु
	u32 gemode;

	/* Preserve the reserved bits */
	/* Lowest 2 bits to zero gives us no rotation */
	gemode = पढ़ोl(engine + VIA_REG_GEMODE) & 0xfffffcfc;
	चयन (bpp) अणु
	हाल 8:
		gemode |= VIA_GEM_8bpp;
		अवरोध;
	हाल 16:
		gemode |= VIA_GEM_16bpp;
		अवरोध;
	हाल 32:
		gemode |= VIA_GEM_32bpp;
		अवरोध;
	शेष:
		prपूर्णांकk(KERN_WARNING "viafb_set_bpp: Unsupported bpp %d\n", bpp);
		वापस -EINVAL;
	पूर्ण
	ग_लिखोl(gemode, engine + VIA_REG_GEMODE);
	वापस 0;
पूर्ण


अटल पूर्णांक hw_bitblt_1(व्योम __iomem *engine, u8 op, u32 width, u32 height,
	u8 dst_bpp, u32 dst_addr, u32 dst_pitch, u32 dst_x, u32 dst_y,
	u32 *src_mem, u32 src_addr, u32 src_pitch, u32 src_x, u32 src_y,
	u32 fg_color, u32 bg_color, u8 fill_rop)
अणु
	u32 ge_cmd = 0, पंचांगp, i;
	पूर्णांक ret;

	अगर (!op || op > 3) अणु
		prपूर्णांकk(KERN_WARNING "hw_bitblt_1: Invalid operation: %d\n", op);
		वापस -EINVAL;
	पूर्ण

	अगर (op != VIA_BITBLT_FILL && !src_mem && src_addr == dst_addr) अणु
		अगर (src_x < dst_x) अणु
			ge_cmd |= 0x00008000;
			src_x += width - 1;
			dst_x += width - 1;
		पूर्ण
		अगर (src_y < dst_y) अणु
			ge_cmd |= 0x00004000;
			src_y += height - 1;
			dst_y += height - 1;
		पूर्ण
	पूर्ण

	अगर (op == VIA_BITBLT_FILL) अणु
		चयन (fill_rop) अणु
		हाल 0x00: /* blackness */
		हाल 0x5A: /* pattern inversion */
		हाल 0xF0: /* pattern copy */
		हाल 0xFF: /* whiteness */
			अवरोध;
		शेष:
			prपूर्णांकk(KERN_WARNING "hw_bitblt_1: Invalid fill rop: "
				"%u\n", fill_rop);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	ret = viafb_set_bpp(engine, dst_bpp);
	अगर (ret)
		वापस ret;

	अगर (op != VIA_BITBLT_FILL) अणु
		अगर (src_x & (op == VIA_BITBLT_MONO ? 0xFFFF8000 : 0xFFFFF000)
			|| src_y & 0xFFFFF000) अणु
			prपूर्णांकk(KERN_WARNING "hw_bitblt_1: Unsupported source "
				"x/y %d %d\n", src_x, src_y);
			वापस -EINVAL;
		पूर्ण
		पंचांगp = src_x | (src_y << 16);
		ग_लिखोl(पंचांगp, engine + 0x08);
	पूर्ण

	अगर (dst_x & 0xFFFFF000 || dst_y & 0xFFFFF000) अणु
		prपूर्णांकk(KERN_WARNING "hw_bitblt_1: Unsupported destination x/y "
			"%d %d\n", dst_x, dst_y);
		वापस -EINVAL;
	पूर्ण
	पंचांगp = dst_x | (dst_y << 16);
	ग_लिखोl(पंचांगp, engine + 0x0C);

	अगर ((width - 1) & 0xFFFFF000 || (height - 1) & 0xFFFFF000) अणु
		prपूर्णांकk(KERN_WARNING "hw_bitblt_1: Unsupported width/height "
			"%d %d\n", width, height);
		वापस -EINVAL;
	पूर्ण
	पंचांगp = (width - 1) | ((height - 1) << 16);
	ग_लिखोl(पंचांगp, engine + 0x10);

	अगर (op != VIA_BITBLT_COLOR)
		ग_लिखोl(fg_color, engine + 0x18);

	अगर (op == VIA_BITBLT_MONO)
		ग_लिखोl(bg_color, engine + 0x1C);

	अगर (op != VIA_BITBLT_FILL) अणु
		पंचांगp = src_mem ? 0 : src_addr;
		अगर (dst_addr & 0xE0000007) अणु
			prपूर्णांकk(KERN_WARNING "hw_bitblt_1: Unsupported source "
				"address %X\n", पंचांगp);
			वापस -EINVAL;
		पूर्ण
		पंचांगp >>= 3;
		ग_लिखोl(पंचांगp, engine + 0x30);
	पूर्ण

	अगर (dst_addr & 0xE0000007) अणु
		prपूर्णांकk(KERN_WARNING "hw_bitblt_1: Unsupported destination "
			"address %X\n", dst_addr);
		वापस -EINVAL;
	पूर्ण
	पंचांगp = dst_addr >> 3;
	ग_लिखोl(पंचांगp, engine + 0x34);

	अगर (op == VIA_BITBLT_FILL)
		पंचांगp = 0;
	अन्यथा
		पंचांगp = src_pitch;
	अगर (पंचांगp & 0xFFFFC007 || dst_pitch & 0xFFFFC007) अणु
		prपूर्णांकk(KERN_WARNING "hw_bitblt_1: Unsupported pitch %X %X\n",
			पंचांगp, dst_pitch);
		वापस -EINVAL;
	पूर्ण
	पंचांगp = VIA_PITCH_ENABLE | (पंचांगp >> 3) | (dst_pitch << (16 - 3));
	ग_लिखोl(पंचांगp, engine + 0x38);

	अगर (op == VIA_BITBLT_FILL)
		ge_cmd |= fill_rop << 24 | 0x00002000 | 0x00000001;
	अन्यथा अणु
		ge_cmd |= 0xCC000000; /* ROP=SRCCOPY */
		अगर (src_mem)
			ge_cmd |= 0x00000040;
		अगर (op == VIA_BITBLT_MONO)
			ge_cmd |= 0x00000002 | 0x00000100 | 0x00020000;
		अन्यथा
			ge_cmd |= 0x00000001;
	पूर्ण
	ग_लिखोl(ge_cmd, engine);

	अगर (op == VIA_BITBLT_FILL || !src_mem)
		वापस 0;

	पंचांगp = (width * height * (op == VIA_BITBLT_MONO ? 1 : (dst_bpp >> 3)) +
		3) >> 2;

	क्रम (i = 0; i < पंचांगp; i++)
		ग_लिखोl(src_mem[i], engine + VIA_MMIO_BLTBASE);

	वापस 0;
पूर्ण

अटल पूर्णांक hw_bitblt_2(व्योम __iomem *engine, u8 op, u32 width, u32 height,
	u8 dst_bpp, u32 dst_addr, u32 dst_pitch, u32 dst_x, u32 dst_y,
	u32 *src_mem, u32 src_addr, u32 src_pitch, u32 src_x, u32 src_y,
	u32 fg_color, u32 bg_color, u8 fill_rop)
अणु
	u32 ge_cmd = 0, पंचांगp, i;
	पूर्णांक ret;

	अगर (!op || op > 3) अणु
		prपूर्णांकk(KERN_WARNING "hw_bitblt_2: Invalid operation: %d\n", op);
		वापस -EINVAL;
	पूर्ण

	अगर (op != VIA_BITBLT_FILL && !src_mem && src_addr == dst_addr) अणु
		अगर (src_x < dst_x) अणु
			ge_cmd |= 0x00008000;
			src_x += width - 1;
			dst_x += width - 1;
		पूर्ण
		अगर (src_y < dst_y) अणु
			ge_cmd |= 0x00004000;
			src_y += height - 1;
			dst_y += height - 1;
		पूर्ण
	पूर्ण

	अगर (op == VIA_BITBLT_FILL) अणु
		चयन (fill_rop) अणु
		हाल 0x00: /* blackness */
		हाल 0x5A: /* pattern inversion */
		हाल 0xF0: /* pattern copy */
		हाल 0xFF: /* whiteness */
			अवरोध;
		शेष:
			prपूर्णांकk(KERN_WARNING "hw_bitblt_2: Invalid fill rop: "
				"%u\n", fill_rop);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	ret = viafb_set_bpp(engine, dst_bpp);
	अगर (ret)
		वापस ret;

	अगर (op == VIA_BITBLT_FILL)
		पंचांगp = 0;
	अन्यथा
		पंचांगp = src_pitch;
	अगर (पंचांगp & 0xFFFFC007 || dst_pitch & 0xFFFFC007) अणु
		prपूर्णांकk(KERN_WARNING "hw_bitblt_2: Unsupported pitch %X %X\n",
			पंचांगp, dst_pitch);
		वापस -EINVAL;
	पूर्ण
	पंचांगp = (पंचांगp >> 3) | (dst_pitch << (16 - 3));
	ग_लिखोl(पंचांगp, engine + 0x08);

	अगर ((width - 1) & 0xFFFFF000 || (height - 1) & 0xFFFFF000) अणु
		prपूर्णांकk(KERN_WARNING "hw_bitblt_2: Unsupported width/height "
			"%d %d\n", width, height);
		वापस -EINVAL;
	पूर्ण
	पंचांगp = (width - 1) | ((height - 1) << 16);
	ग_लिखोl(पंचांगp, engine + 0x0C);

	अगर (dst_x & 0xFFFFF000 || dst_y & 0xFFFFF000) अणु
		prपूर्णांकk(KERN_WARNING "hw_bitblt_2: Unsupported destination x/y "
			"%d %d\n", dst_x, dst_y);
		वापस -EINVAL;
	पूर्ण
	पंचांगp = dst_x | (dst_y << 16);
	ग_लिखोl(पंचांगp, engine + 0x10);

	अगर (dst_addr & 0xE0000007) अणु
		prपूर्णांकk(KERN_WARNING "hw_bitblt_2: Unsupported destination "
			"address %X\n", dst_addr);
		वापस -EINVAL;
	पूर्ण
	पंचांगp = dst_addr >> 3;
	ग_लिखोl(पंचांगp, engine + 0x14);

	अगर (op != VIA_BITBLT_FILL) अणु
		अगर (src_x & (op == VIA_BITBLT_MONO ? 0xFFFF8000 : 0xFFFFF000)
			|| src_y & 0xFFFFF000) अणु
			prपूर्णांकk(KERN_WARNING "hw_bitblt_2: Unsupported source "
				"x/y %d %d\n", src_x, src_y);
			वापस -EINVAL;
		पूर्ण
		पंचांगp = src_x | (src_y << 16);
		ग_लिखोl(पंचांगp, engine + 0x18);

		पंचांगp = src_mem ? 0 : src_addr;
		अगर (dst_addr & 0xE0000007) अणु
			prपूर्णांकk(KERN_WARNING "hw_bitblt_2: Unsupported source "
				"address %X\n", पंचांगp);
			वापस -EINVAL;
		पूर्ण
		पंचांगp >>= 3;
		ग_लिखोl(पंचांगp, engine + 0x1C);
	पूर्ण

	अगर (op == VIA_BITBLT_FILL) अणु
		ग_लिखोl(fg_color, engine + 0x58);
	पूर्ण अन्यथा अगर (op == VIA_BITBLT_MONO) अणु
		ग_लिखोl(fg_color, engine + 0x4C);
		ग_लिखोl(bg_color, engine + 0x50);
	पूर्ण

	अगर (op == VIA_BITBLT_FILL)
		ge_cmd |= fill_rop << 24 | 0x00002000 | 0x00000001;
	अन्यथा अणु
		ge_cmd |= 0xCC000000; /* ROP=SRCCOPY */
		अगर (src_mem)
			ge_cmd |= 0x00000040;
		अगर (op == VIA_BITBLT_MONO)
			ge_cmd |= 0x00000002 | 0x00000100 | 0x00020000;
		अन्यथा
			ge_cmd |= 0x00000001;
	पूर्ण
	ग_लिखोl(ge_cmd, engine);

	अगर (op == VIA_BITBLT_FILL || !src_mem)
		वापस 0;

	पंचांगp = (width * height * (op == VIA_BITBLT_MONO ? 1 : (dst_bpp >> 3)) +
		3) >> 2;

	क्रम (i = 0; i < पंचांगp; i++)
		ग_लिखोl(src_mem[i], engine + VIA_MMIO_BLTBASE);

	वापस 0;
पूर्ण

पूर्णांक viafb_setup_engine(काष्ठा fb_info *info)
अणु
	काष्ठा viafb_par *viapar = info->par;
	व्योम __iomem *engine;
	u32 chip_name = viapar->shared->chip_info.gfx_chip_name;

	engine = viapar->shared->vdev->engine_mmio;
	अगर (!engine) अणु
		prपूर्णांकk(KERN_WARNING "viafb_init_accel: ioremap failed, "
			"hardware acceleration disabled\n");
		वापस -ENOMEM;
	पूर्ण

	चयन (chip_name) अणु
	हाल UNICHROME_CLE266:
	हाल UNICHROME_K400:
	हाल UNICHROME_K800:
	हाल UNICHROME_PM800:
	हाल UNICHROME_CN700:
	हाल UNICHROME_CX700:
	हाल UNICHROME_CN750:
	हाल UNICHROME_K8M890:
	हाल UNICHROME_P4M890:
	हाल UNICHROME_P4M900:
		viapar->shared->hw_bitblt = hw_bitblt_1;
		अवरोध;
	हाल UNICHROME_VX800:
	हाल UNICHROME_VX855:
	हाल UNICHROME_VX900:
		viapar->shared->hw_bitblt = hw_bitblt_2;
		अवरोध;
	शेष:
		viapar->shared->hw_bitblt = शून्य;
	पूर्ण

	viapar->fbmem_मुक्त -= CURSOR_SIZE;
	viapar->shared->cursor_vram_addr = viapar->fbmem_मुक्त;
	viapar->fbmem_used += CURSOR_SIZE;

	viapar->fbmem_मुक्त -= VQ_SIZE;
	viapar->shared->vq_vram_addr = viapar->fbmem_मुक्त;
	viapar->fbmem_used += VQ_SIZE;

#अगर IS_ENABLED(CONFIG_VIDEO_VIA_CAMERA)
	/*
	 * Set aside a chunk of framebuffer memory क्रम the camera
	 * driver.  Someday this driver probably needs a proper allocator
	 * क्रम fbmem; क्रम now, we just have to करो this beक्रमe the
	 * framebuffer initializes itself.
	 *
	 * As क्रम the size: the engine can handle three frames,
	 * 16 bits deep, up to VGA resolution.
	 */
	viapar->shared->vdev->camera_fbmem_size = 3*VGA_HEIGHT*VGA_WIDTH*2;
	viapar->fbmem_मुक्त -= viapar->shared->vdev->camera_fbmem_size;
	viapar->fbmem_used += viapar->shared->vdev->camera_fbmem_size;
	viapar->shared->vdev->camera_fbmem_offset = viapar->fbmem_मुक्त;
#पूर्ण_अगर

	viafb_reset_engine(viapar);
	वापस 0;
पूर्ण

व्योम viafb_reset_engine(काष्ठा viafb_par *viapar)
अणु
	व्योम __iomem *engine = viapar->shared->vdev->engine_mmio;
	पूर्णांक highest_reg, i;
	u32 vq_start_addr, vq_end_addr, vq_start_low, vq_end_low, vq_high,
		vq_len, chip_name = viapar->shared->chip_info.gfx_chip_name;

	/* Initialize रेजिस्टरs to reset the 2D engine */
	चयन (viapar->shared->chip_info.twod_engine) अणु
	हाल VIA_2D_ENG_M1:
		highest_reg = 0x5c;
		अवरोध;
	शेष:
		highest_reg = 0x40;
		अवरोध;
	पूर्ण
	क्रम (i = 0; i <= highest_reg; i += 4)
		ग_लिखोl(0x0, engine + i);

	/* Init AGP and VQ regs */
	चयन (chip_name) अणु
	हाल UNICHROME_K8M890:
	हाल UNICHROME_P4M900:
	हाल UNICHROME_VX800:
	हाल UNICHROME_VX855:
	हाल UNICHROME_VX900:
		ग_लिखोl(0x00100000, engine + VIA_REG_CR_TRANSET);
		ग_लिखोl(0x680A0000, engine + VIA_REG_CR_TRANSPACE);
		ग_लिखोl(0x02000000, engine + VIA_REG_CR_TRANSPACE);
		अवरोध;

	शेष:
		ग_लिखोl(0x00100000, engine + VIA_REG_TRANSET);
		ग_लिखोl(0x00000000, engine + VIA_REG_TRANSPACE);
		ग_लिखोl(0x00333004, engine + VIA_REG_TRANSPACE);
		ग_लिखोl(0x60000000, engine + VIA_REG_TRANSPACE);
		ग_लिखोl(0x61000000, engine + VIA_REG_TRANSPACE);
		ग_लिखोl(0x62000000, engine + VIA_REG_TRANSPACE);
		ग_लिखोl(0x63000000, engine + VIA_REG_TRANSPACE);
		ग_लिखोl(0x64000000, engine + VIA_REG_TRANSPACE);
		ग_लिखोl(0x7D000000, engine + VIA_REG_TRANSPACE);

		ग_लिखोl(0xFE020000, engine + VIA_REG_TRANSET);
		ग_लिखोl(0x00000000, engine + VIA_REG_TRANSPACE);
		अवरोध;
	पूर्ण

	/* Enable VQ */
	vq_start_addr = viapar->shared->vq_vram_addr;
	vq_end_addr = viapar->shared->vq_vram_addr + VQ_SIZE - 1;

	vq_start_low = 0x50000000 | (vq_start_addr & 0xFFFFFF);
	vq_end_low = 0x51000000 | (vq_end_addr & 0xFFFFFF);
	vq_high = 0x52000000 | ((vq_start_addr & 0xFF000000) >> 24) |
		((vq_end_addr & 0xFF000000) >> 16);
	vq_len = 0x53000000 | (VQ_SIZE >> 3);

	चयन (chip_name) अणु
	हाल UNICHROME_K8M890:
	हाल UNICHROME_P4M900:
	हाल UNICHROME_VX800:
	हाल UNICHROME_VX855:
	हाल UNICHROME_VX900:
		vq_start_low |= 0x20000000;
		vq_end_low |= 0x20000000;
		vq_high |= 0x20000000;
		vq_len |= 0x20000000;

		ग_लिखोl(0x00100000, engine + VIA_REG_CR_TRANSET);
		ग_लिखोl(vq_high, engine + VIA_REG_CR_TRANSPACE);
		ग_लिखोl(vq_start_low, engine + VIA_REG_CR_TRANSPACE);
		ग_लिखोl(vq_end_low, engine + VIA_REG_CR_TRANSPACE);
		ग_लिखोl(vq_len, engine + VIA_REG_CR_TRANSPACE);
		ग_लिखोl(0x74301001, engine + VIA_REG_CR_TRANSPACE);
		ग_लिखोl(0x00000000, engine + VIA_REG_CR_TRANSPACE);
		अवरोध;
	शेष:
		ग_लिखोl(0x00FE0000, engine + VIA_REG_TRANSET);
		ग_लिखोl(0x080003FE, engine + VIA_REG_TRANSPACE);
		ग_लिखोl(0x0A00027C, engine + VIA_REG_TRANSPACE);
		ग_लिखोl(0x0B000260, engine + VIA_REG_TRANSPACE);
		ग_लिखोl(0x0C000274, engine + VIA_REG_TRANSPACE);
		ग_लिखोl(0x0D000264, engine + VIA_REG_TRANSPACE);
		ग_लिखोl(0x0E000000, engine + VIA_REG_TRANSPACE);
		ग_लिखोl(0x0F000020, engine + VIA_REG_TRANSPACE);
		ग_लिखोl(0x1000027E, engine + VIA_REG_TRANSPACE);
		ग_लिखोl(0x110002FE, engine + VIA_REG_TRANSPACE);
		ग_लिखोl(0x200F0060, engine + VIA_REG_TRANSPACE);

		ग_लिखोl(0x00000006, engine + VIA_REG_TRANSPACE);
		ग_लिखोl(0x40008C0F, engine + VIA_REG_TRANSPACE);
		ग_लिखोl(0x44000000, engine + VIA_REG_TRANSPACE);
		ग_लिखोl(0x45080C04, engine + VIA_REG_TRANSPACE);
		ग_लिखोl(0x46800408, engine + VIA_REG_TRANSPACE);

		ग_लिखोl(vq_high, engine + VIA_REG_TRANSPACE);
		ग_लिखोl(vq_start_low, engine + VIA_REG_TRANSPACE);
		ग_लिखोl(vq_end_low, engine + VIA_REG_TRANSPACE);
		ग_लिखोl(vq_len, engine + VIA_REG_TRANSPACE);
		अवरोध;
	पूर्ण

	/* Set Cursor Image Base Address */
	ग_लिखोl(viapar->shared->cursor_vram_addr, engine + VIA_REG_CURSOR_MODE);
	ग_लिखोl(0x0, engine + VIA_REG_CURSOR_POS);
	ग_लिखोl(0x0, engine + VIA_REG_CURSOR_ORG);
	ग_लिखोl(0x0, engine + VIA_REG_CURSOR_BG);
	ग_लिखोl(0x0, engine + VIA_REG_CURSOR_FG);
	वापस;
पूर्ण

व्योम viafb_show_hw_cursor(काष्ठा fb_info *info, पूर्णांक Status)
अणु
	काष्ठा viafb_par *viapar = info->par;
	u32 temp, iga_path = viapar->iga_path;

	temp = पढ़ोl(viapar->shared->vdev->engine_mmio + VIA_REG_CURSOR_MODE);
	चयन (Status) अणु
	हाल HW_Cursor_ON:
		temp |= 0x1;
		अवरोध;
	हाल HW_Cursor_OFF:
		temp &= 0xFFFFFFFE;
		अवरोध;
	पूर्ण
	चयन (iga_path) अणु
	हाल IGA2:
		temp |= 0x80000000;
		अवरोध;
	हाल IGA1:
	शेष:
		temp &= 0x7FFFFFFF;
	पूर्ण
	ग_लिखोl(temp, viapar->shared->vdev->engine_mmio + VIA_REG_CURSOR_MODE);
पूर्ण

व्योम viafb_रुको_engine_idle(काष्ठा fb_info *info)
अणु
	काष्ठा viafb_par *viapar = info->par;
	पूर्णांक loop = 0;
	u32 mask;
	व्योम __iomem *engine = viapar->shared->vdev->engine_mmio;

	चयन (viapar->shared->chip_info.twod_engine) अणु
	हाल VIA_2D_ENG_H5:
	हाल VIA_2D_ENG_M1:
		mask = VIA_CMD_RGTR_BUSY_M1 | VIA_2D_ENG_BUSY_M1 |
			      VIA_3D_ENG_BUSY_M1;
		अवरोध;
	शेष:
		जबतक (!(पढ़ोl(engine + VIA_REG_STATUS) &
				VIA_VR_QUEUE_BUSY) && (loop < MAXLOOP)) अणु
			loop++;
			cpu_relax();
		पूर्ण
		mask = VIA_CMD_RGTR_BUSY | VIA_2D_ENG_BUSY | VIA_3D_ENG_BUSY;
		अवरोध;
	पूर्ण

	जबतक ((पढ़ोl(engine + VIA_REG_STATUS) & mask) && (loop < MAXLOOP)) अणु
		loop++;
		cpu_relax();
	पूर्ण

	अगर (loop >= MAXLOOP)
		prपूर्णांकk(KERN_ERR "viafb_wait_engine_idle: not syncing\n");
पूर्ण
