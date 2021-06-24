<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

/*
 *  ATI Mach64 Hardware Acceleration
 */

#समावेश <linux/delay.h>
#समावेश <यंत्र/unaligned.h>
#समावेश <linux/fb.h>
#समावेश <video/mach64.h>
#समावेश "atyfb.h"

    /*
     *  Generic Mach64 routines
     */

/* this is क्रम DMA GUI engine! work in progress */
प्रकार काष्ठा अणु
	u32 frame_buf_offset;
	u32 प्रणाली_mem_addr;
	u32 command;
	u32 reserved;
पूर्ण BM_DESCRIPTOR_ENTRY;

#घोषणा LAST_DESCRIPTOR (1 << 31)
#घोषणा SYSTEM_TO_FRAME_BUFFER 0

अटल u32 rotation24bpp(u32 dx, u32 direction)
अणु
	u32 rotation;
	अगर (direction & DST_X_LEFT_TO_RIGHT) अणु
		rotation = (dx / 4) % 6;
	पूर्ण अन्यथा अणु
		rotation = ((dx + 2) / 4) % 6;
	पूर्ण

	वापस ((rotation << 8) | DST_24_ROTATION_ENABLE);
पूर्ण

व्योम aty_reset_engine(काष्ठा atyfb_par *par)
अणु
	/* reset engine */
	aty_st_le32(GEN_TEST_CNTL,
		aty_ld_le32(GEN_TEST_CNTL, par) &
		~(GUI_ENGINE_ENABLE | HWCURSOR_ENABLE), par);
	/* enable engine */
	aty_st_le32(GEN_TEST_CNTL,
		aty_ld_le32(GEN_TEST_CNTL, par) | GUI_ENGINE_ENABLE, par);
	/* ensure engine is not locked up by clearing any FIFO or */
	/* HOST errors */
	aty_st_le32(BUS_CNTL,
		aty_ld_le32(BUS_CNTL, par) | BUS_HOST_ERR_ACK | BUS_FIFO_ERR_ACK, par);

	par->fअगरo_space = 0;
पूर्ण

अटल व्योम reset_GTC_3D_engine(स्थिर काष्ठा atyfb_par *par)
अणु
	aty_st_le32(SCALE_3D_CNTL, 0xc0, par);
	mdelay(GTC_3D_RESET_DELAY);
	aty_st_le32(SETUP_CNTL, 0x00, par);
	mdelay(GTC_3D_RESET_DELAY);
	aty_st_le32(SCALE_3D_CNTL, 0x00, par);
	mdelay(GTC_3D_RESET_DELAY);
पूर्ण

व्योम aty_init_engine(काष्ठा atyfb_par *par, काष्ठा fb_info *info)
अणु
	u32 pitch_value;
	u32 vxres;

	/* determine modal inक्रमmation from global mode काष्ठाure */
	pitch_value = info->fix.line_length / (info->var.bits_per_pixel / 8);
	vxres = info->var.xres_भव;

	अगर (info->var.bits_per_pixel == 24) अणु
		/* In 24 bpp, the engine is in 8 bpp - this requires that all */
		/* horizontal coordinates and widths must be adjusted */
		pitch_value *= 3;
		vxres *= 3;
	पूर्ण

	/* On GTC (RagePro), we need to reset the 3D engine beक्रमe */
	अगर (M64_HAS(RESET_3D))
		reset_GTC_3D_engine(par);

	/* Reset engine, enable, and clear any engine errors */
	aty_reset_engine(par);
	/* Ensure that vga page poपूर्णांकers are set to zero - the upper */
	/* page poपूर्णांकers are set to 1 to handle overflows in the */
	/* lower page */
	aty_st_le32(MEM_VGA_WP_SEL, 0x00010000, par);
	aty_st_le32(MEM_VGA_RP_SEL, 0x00010000, par);

	/* ---- Setup standard engine context ---- */

	/* All GUI रेजिस्टरs here are FIFOed - thereक्रमe, रुको क्रम */
	/* the appropriate number of empty FIFO entries */
	रुको_क्रम_fअगरo(14, par);

	/* enable all रेजिस्टरs to be loaded क्रम context loads */
	aty_st_le32(CONTEXT_MASK, 0xFFFFFFFF, par);

	/* set destination pitch to modal pitch, set offset to zero */
	aty_st_le32(DST_OFF_PITCH, (pitch_value / 8) << 22, par);

	/* zero these रेजिस्टरs (set them to a known state) */
	aty_st_le32(DST_Y_X, 0, par);
	aty_st_le32(DST_HEIGHT, 0, par);
	aty_st_le32(DST_BRES_ERR, 0, par);
	aty_st_le32(DST_BRES_INC, 0, par);
	aty_st_le32(DST_BRES_DEC, 0, par);

	/* set destination drawing attributes */
	aty_st_le32(DST_CNTL, DST_LAST_PEL | DST_Y_TOP_TO_BOTTOM |
		    DST_X_LEFT_TO_RIGHT, par);

	/* set source pitch to modal pitch, set offset to zero */
	aty_st_le32(SRC_OFF_PITCH, (pitch_value / 8) << 22, par);

	/* set these रेजिस्टरs to a known state */
	aty_st_le32(SRC_Y_X, 0, par);
	aty_st_le32(SRC_HEIGHT1_WIDTH1, 1, par);
	aty_st_le32(SRC_Y_X_START, 0, par);
	aty_st_le32(SRC_HEIGHT2_WIDTH2, 1, par);

	/* set source pixel retrieving attributes */
	aty_st_le32(SRC_CNTL, SRC_LINE_X_LEFT_TO_RIGHT, par);

	/* set host attributes */
	रुको_क्रम_fअगरo(13, par);
	aty_st_le32(HOST_CNTL, HOST_BYTE_ALIGN, par);

	/* set pattern attributes */
	aty_st_le32(PAT_REG0, 0, par);
	aty_st_le32(PAT_REG1, 0, par);
	aty_st_le32(PAT_CNTL, 0, par);

	/* set scissors to modal size */
	aty_st_le32(SC_LEFT, 0, par);
	aty_st_le32(SC_TOP, 0, par);
	aty_st_le32(SC_BOTTOM, par->crtc.vyres - 1, par);
	aty_st_le32(SC_RIGHT, vxres - 1, par);

	/* set background color to minimum value (usually BLACK) */
	aty_st_le32(DP_BKGD_CLR, 0, par);

	/* set क्रमeground color to maximum value (usually WHITE) */
	aty_st_le32(DP_FRGD_CLR, 0xFFFFFFFF, par);

	/* set ग_लिखो mask to effect all pixel bits */
	aty_st_le32(DP_WRITE_MASK, 0xFFFFFFFF, par);

	/* set क्रमeground mix to overpaपूर्णांक and background mix to */
	/* no-effect */
	aty_st_le32(DP_MIX, FRGD_MIX_S | BKGD_MIX_D, par);

	/* set primary source pixel channel to क्रमeground color */
	/* रेजिस्टर */
	aty_st_le32(DP_SRC, FRGD_SRC_FRGD_CLR, par);

	/* set compare functionality to false (no-effect on */
	/* destination) */
	रुको_क्रम_fअगरo(3, par);
	aty_st_le32(CLR_CMP_CLR, 0, par);
	aty_st_le32(CLR_CMP_MASK, 0xFFFFFFFF, par);
	aty_st_le32(CLR_CMP_CNTL, 0, par);

	/* set pixel depth */
	रुको_क्रम_fअगरo(2, par);
	aty_st_le32(DP_PIX_WIDTH, par->crtc.dp_pix_width, par);
	aty_st_le32(DP_CHAIN_MASK, par->crtc.dp_chain_mask, par);

	रुको_क्रम_fअगरo(5, par);
 	aty_st_le32(SCALE_3D_CNTL, 0, par);
	aty_st_le32(Z_CNTL, 0, par);
	aty_st_le32(CRTC_INT_CNTL, aty_ld_le32(CRTC_INT_CNTL, par) & ~0x20,
		    par);
	aty_st_le32(GUI_TRAJ_CNTL, 0x100023, par);

	/* insure engine is idle beक्रमe leaving */
	रुको_क्रम_idle(par);
पूर्ण

    /*
     *  Accelerated functions
     */

अटल अंतरभूत व्योम draw_rect(s16 x, s16 y, u16 width, u16 height,
			     काष्ठा atyfb_par *par)
अणु
	/* perक्रमm rectangle fill */
	रुको_क्रम_fअगरo(2, par);
	aty_st_le32(DST_Y_X, (x << 16) | y, par);
	aty_st_le32(DST_HEIGHT_WIDTH, (width << 16) | height, par);
	par->blitter_may_be_busy = 1;
पूर्ण

व्योम atyfb_copyarea(काष्ठा fb_info *info, स्थिर काष्ठा fb_copyarea *area)
अणु
	काष्ठा atyfb_par *par = (काष्ठा atyfb_par *) info->par;
	u32 dy = area->dy, sy = area->sy, direction = DST_LAST_PEL;
	u32 sx = area->sx, dx = area->dx, width = area->width, rotation = 0;

	अगर (par->asleep)
		वापस;
	अगर (!area->width || !area->height)
		वापस;
	अगर (!par->accel_flags) अणु
		cfb_copyarea(info, area);
		वापस;
	पूर्ण

	अगर (info->var.bits_per_pixel == 24) अणु
		/* In 24 bpp, the engine is in 8 bpp - this requires that all */
		/* horizontal coordinates and widths must be adjusted */
		sx *= 3;
		dx *= 3;
		width *= 3;
	पूर्ण

	अगर (area->sy < area->dy) अणु
		dy += area->height - 1;
		sy += area->height - 1;
	पूर्ण अन्यथा
		direction |= DST_Y_TOP_TO_BOTTOM;

	अगर (sx < dx) अणु
		dx += width - 1;
		sx += width - 1;
	पूर्ण अन्यथा
		direction |= DST_X_LEFT_TO_RIGHT;

	अगर (info->var.bits_per_pixel == 24) अणु
		rotation = rotation24bpp(dx, direction);
	पूर्ण

	रुको_क्रम_fअगरo(5, par);
	aty_st_le32(DP_PIX_WIDTH, par->crtc.dp_pix_width, par);
	aty_st_le32(DP_SRC, FRGD_SRC_BLIT, par);
	aty_st_le32(SRC_Y_X, (sx << 16) | sy, par);
	aty_st_le32(SRC_HEIGHT1_WIDTH1, (width << 16) | area->height, par);
	aty_st_le32(DST_CNTL, direction | rotation, par);
	draw_rect(dx, dy, width, area->height, par);
पूर्ण

व्योम atyfb_fillrect(काष्ठा fb_info *info, स्थिर काष्ठा fb_fillrect *rect)
अणु
	काष्ठा atyfb_par *par = (काष्ठा atyfb_par *) info->par;
	u32 color, dx = rect->dx, width = rect->width, rotation = 0;

	अगर (par->asleep)
		वापस;
	अगर (!rect->width || !rect->height)
		वापस;
	अगर (!par->accel_flags) अणु
		cfb_fillrect(info, rect);
		वापस;
	पूर्ण

	अगर (info->fix.visual == FB_VISUAL_TRUECOLOR ||
	    info->fix.visual == FB_VISUAL_सूचीECTCOLOR)
		color = ((u32 *)(info->pseuकरो_palette))[rect->color];
	अन्यथा
		color = rect->color;

	अगर (info->var.bits_per_pixel == 24) अणु
		/* In 24 bpp, the engine is in 8 bpp - this requires that all */
		/* horizontal coordinates and widths must be adjusted */
		dx *= 3;
		width *= 3;
		rotation = rotation24bpp(dx, DST_X_LEFT_TO_RIGHT);
	पूर्ण

	रुको_क्रम_fअगरo(4, par);
	aty_st_le32(DP_PIX_WIDTH, par->crtc.dp_pix_width, par);
	aty_st_le32(DP_FRGD_CLR, color, par);
	aty_st_le32(DP_SRC,
		    BKGD_SRC_BKGD_CLR | FRGD_SRC_FRGD_CLR | MONO_SRC_ONE,
		    par);
	aty_st_le32(DST_CNTL,
		    DST_LAST_PEL | DST_Y_TOP_TO_BOTTOM |
		    DST_X_LEFT_TO_RIGHT | rotation, par);
	draw_rect(dx, rect->dy, width, rect->height, par);
पूर्ण

व्योम atyfb_imageblit(काष्ठा fb_info *info, स्थिर काष्ठा fb_image *image)
अणु
	काष्ठा atyfb_par *par = (काष्ठा atyfb_par *) info->par;
	u32 src_bytes, dx = image->dx, dy = image->dy, width = image->width;
	u32 pix_width, rotation = 0, src, mix;

	अगर (par->asleep)
		वापस;
	अगर (!image->width || !image->height)
		वापस;
	अगर (!par->accel_flags ||
	    (image->depth != 1 && info->var.bits_per_pixel != image->depth)) अणु
		cfb_imageblit(info, image);
		वापस;
	पूर्ण

	pix_width = par->crtc.dp_pix_width;

	चयन (image->depth) अणु
	हाल 1:
	    pix_width &= ~(BYTE_ORDER_MASK | HOST_MASK);
	    pix_width |= (BYTE_ORDER_MSB_TO_LSB | HOST_1BPP);
	    अवरोध;
	हाल 4:
	    pix_width &= ~(BYTE_ORDER_MASK | HOST_MASK);
	    pix_width |= (BYTE_ORDER_MSB_TO_LSB | HOST_4BPP);
	    अवरोध;
	हाल 8:
	    pix_width &= ~HOST_MASK;
	    pix_width |= HOST_8BPP;
	    अवरोध;
	हाल 15:
	    pix_width &= ~HOST_MASK;
	    pix_width |= HOST_15BPP;
	    अवरोध;
	हाल 16:
	    pix_width &= ~HOST_MASK;
	    pix_width |= HOST_16BPP;
	    अवरोध;
	हाल 24:
	    pix_width &= ~HOST_MASK;
	    pix_width |= HOST_24BPP;
	    अवरोध;
	हाल 32:
	    pix_width &= ~HOST_MASK;
	    pix_width |= HOST_32BPP;
	    अवरोध;
	पूर्ण

	अगर (info->var.bits_per_pixel == 24) अणु
		/* In 24 bpp, the engine is in 8 bpp - this requires that all */
		/* horizontal coordinates and widths must be adjusted */
		dx *= 3;
		width *= 3;

		rotation = rotation24bpp(dx, DST_X_LEFT_TO_RIGHT);

		pix_width &= ~DST_MASK;
		pix_width |= DST_8BPP;

		/*
		 * since Rage 3D IIc we have DP_HOST_TRIPLE_EN bit
		 * this hwaccelerated triple has an issue with not aligned data
		 */
		अगर (image->depth == 1 && M64_HAS(HW_TRIPLE) && image->width % 8 == 0)
			pix_width |= DP_HOST_TRIPLE_EN;
	पूर्ण

	अगर (image->depth == 1) अणु
		u32 fg, bg;
		अगर (info->fix.visual == FB_VISUAL_TRUECOLOR ||
		    info->fix.visual == FB_VISUAL_सूचीECTCOLOR) अणु
			fg = ((u32*)(info->pseuकरो_palette))[image->fg_color];
			bg = ((u32*)(info->pseuकरो_palette))[image->bg_color];
		पूर्ण अन्यथा अणु
			fg = image->fg_color;
			bg = image->bg_color;
		पूर्ण

		रुको_क्रम_fअगरo(2, par);
		aty_st_le32(DP_BKGD_CLR, bg, par);
		aty_st_le32(DP_FRGD_CLR, fg, par);
		src = MONO_SRC_HOST | FRGD_SRC_FRGD_CLR | BKGD_SRC_BKGD_CLR;
		mix = FRGD_MIX_S | BKGD_MIX_S;
	पूर्ण अन्यथा अणु
		src = MONO_SRC_ONE | FRGD_SRC_HOST;
		mix = FRGD_MIX_D_XOR_S | BKGD_MIX_D;
	पूर्ण

	रुको_क्रम_fअगरo(5, par);
	aty_st_le32(DP_PIX_WIDTH, pix_width, par);
	aty_st_le32(DP_MIX, mix, par);
	aty_st_le32(DP_SRC, src, par);
	aty_st_le32(HOST_CNTL, HOST_BYTE_ALIGN, par);
	aty_st_le32(DST_CNTL, DST_Y_TOP_TO_BOTTOM | DST_X_LEFT_TO_RIGHT | rotation, par);

	draw_rect(dx, dy, width, image->height, par);
	src_bytes = (((image->width * image->depth) + 7) / 8) * image->height;

	/* manual triple each pixel */
	अगर (image->depth == 1 && info->var.bits_per_pixel == 24 && !(pix_width & DP_HOST_TRIPLE_EN)) अणु
		पूर्णांक inbit, outbit, mult24, byte_id_in_dword, width;
		u8 *pbiपंचांगapin = (u8*)image->data, *pbiपंचांगapout;
		u32 hostdword;

		क्रम (width = image->width, inbit = 7, mult24 = 0; src_bytes; ) अणु
			क्रम (hostdword = 0, pbiपंचांगapout = (u8*)&hostdword, byte_id_in_dword = 0;
				byte_id_in_dword < 4 && src_bytes;
				byte_id_in_dword++, pbiपंचांगapout++) अणु
				क्रम (outbit = 7; outbit >= 0; outbit--) अणु
					*pbiपंचांगapout |= (((*pbiपंचांगapin >> inbit) & 1) << outbit);
					mult24++;
					/* next bit */
					अगर (mult24 == 3) अणु
						mult24 = 0;
						inbit--;
						width--;
					पूर्ण

					/* next byte */
					अगर (inbit < 0 || width == 0) अणु
						src_bytes--;
						pbiपंचांगapin++;
						inbit = 7;

						अगर (width == 0) अणु
						    width = image->width;
						    outbit = 0;
						पूर्ण
					पूर्ण
				पूर्ण
			पूर्ण
			रुको_क्रम_fअगरo(1, par);
			aty_st_le32(HOST_DATA0, le32_to_cpu(hostdword), par);
		पूर्ण
	पूर्ण अन्यथा अणु
		u32 *pbiपंचांगap, dwords = (src_bytes + 3) / 4;
		क्रम (pbiपंचांगap = (u32*)(image->data); dwords; dwords--, pbiपंचांगap++) अणु
			रुको_क्रम_fअगरo(1, par);
			aty_st_le32(HOST_DATA0, get_unaligned_le32(pbiपंचांगap), par);
		पूर्ण
	पूर्ण
पूर्ण
