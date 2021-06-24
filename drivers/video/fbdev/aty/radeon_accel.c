<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश "radeonfb.h"

/* the accelerated functions here are patterned after the 
 * "ACCEL_MMIO" अगरdef branches in XFree86
 * --dte
 */

अटल व्योम radeon_fixup_offset(काष्ठा radeonfb_info *rinfo)
अणु
	u32 local_base;

	/* *** Ugly workaround *** */
	/*
	 * On some platक्रमms, the video memory is mapped at 0 in radeon chip space
	 * (like PPCs) by the firmware. X will always move it up so that it's seen
	 * by the chip to be at the same address as the PCI BAR.
	 * That means that when चयनing back from X, there is a mismatch between
	 * the offsets programmed पूर्णांकo the engine. This means that potentially,
	 * accel operations करोne beक्रमe radeonfb has a chance to re-init the engine
	 * will have incorrect offsets, and potentially trash प्रणाली memory !
	 *
	 * The correct fix is क्रम fbcon to never call any accel op beक्रमe the engine
	 * has properly been re-initialized (by a call to set_var), but this is a
	 * complex fix. This workaround in the meanसमय, called beक्रमe every accel
	 * operation, makes sure the offsets are in sync.
	 */

	radeon_fअगरo_रुको (1);
	local_base = INREG(MC_FB_LOCATION) << 16;
	अगर (local_base == rinfo->fb_local_base)
		वापस;

	rinfo->fb_local_base = local_base;

	radeon_fअगरo_रुको (3);
	OUTREG(DEFAULT_PITCH_OFFSET, (rinfo->pitch << 0x16) |
				     (rinfo->fb_local_base >> 10));
	OUTREG(DST_PITCH_OFFSET, (rinfo->pitch << 0x16) | (rinfo->fb_local_base >> 10));
	OUTREG(SRC_PITCH_OFFSET, (rinfo->pitch << 0x16) | (rinfo->fb_local_base >> 10));
पूर्ण

अटल व्योम radeonfb_prim_fillrect(काष्ठा radeonfb_info *rinfo, 
				   स्थिर काष्ठा fb_fillrect *region)
अणु
	radeon_fअगरo_रुको(4);  
  
	OUTREG(DP_GUI_MASTER_CNTL,  
		rinfo->dp_gui_master_cntl  /* contains, like GMC_DST_32BPP */
                | GMC_BRUSH_SOLID_COLOR
                | ROP3_P);
	अगर (radeon_get_dstbpp(rinfo->depth) != DST_8BPP)
		OUTREG(DP_BRUSH_FRGD_CLR, rinfo->pseuकरो_palette[region->color]);
	अन्यथा
		OUTREG(DP_BRUSH_FRGD_CLR, region->color);
	OUTREG(DP_WRITE_MSK, 0xffffffff);
	OUTREG(DP_CNTL, (DST_X_LEFT_TO_RIGHT | DST_Y_TOP_TO_BOTTOM));

	radeon_fअगरo_रुको(2);
	OUTREG(DSTCACHE_CTLSTAT, RB2D_DC_FLUSH_ALL);
	OUTREG(WAIT_UNTIL, (WAIT_2D_IDLECLEAN | WAIT_DMA_GUI_IDLE));

	radeon_fअगरo_रुको(2);  
	OUTREG(DST_Y_X, (region->dy << 16) | region->dx);
	OUTREG(DST_WIDTH_HEIGHT, (region->width << 16) | region->height);
पूर्ण

व्योम radeonfb_fillrect(काष्ठा fb_info *info, स्थिर काष्ठा fb_fillrect *region)
अणु
	काष्ठा radeonfb_info *rinfo = info->par;
	काष्ठा fb_fillrect modded;
	पूर्णांक vxres, vyres;
  
	अगर (info->state != FBINFO_STATE_RUNNING)
		वापस;
	अगर (info->flags & FBINFO_HWACCEL_DISABLED) अणु
		cfb_fillrect(info, region);
		वापस;
	पूर्ण

	radeon_fixup_offset(rinfo);

	vxres = info->var.xres_भव;
	vyres = info->var.yres_भव;

	स_नकल(&modded, region, माप(काष्ठा fb_fillrect));

	अगर(!modded.width || !modded.height ||
	   modded.dx >= vxres || modded.dy >= vyres)
		वापस;
  
	अगर(modded.dx + modded.width  > vxres) modded.width  = vxres - modded.dx;
	अगर(modded.dy + modded.height > vyres) modded.height = vyres - modded.dy;

	radeonfb_prim_fillrect(rinfo, &modded);
पूर्ण

अटल व्योम radeonfb_prim_copyarea(काष्ठा radeonfb_info *rinfo, 
				   स्थिर काष्ठा fb_copyarea *area)
अणु
	पूर्णांक xdir, ydir;
	u32 sx, sy, dx, dy, w, h;

	w = area->width; h = area->height;
	dx = area->dx; dy = area->dy;
	sx = area->sx; sy = area->sy;
	xdir = sx - dx;
	ydir = sy - dy;

	अगर ( xdir < 0 ) अणु sx += w-1; dx += w-1; पूर्ण
	अगर ( ydir < 0 ) अणु sy += h-1; dy += h-1; पूर्ण

	radeon_fअगरo_रुको(3);
	OUTREG(DP_GUI_MASTER_CNTL,
		rinfo->dp_gui_master_cntl /* i.e. GMC_DST_32BPP */
		| GMC_BRUSH_NONE
		| GMC_SRC_DSTCOLOR
		| ROP3_S 
		| DP_SRC_SOURCE_MEMORY );
	OUTREG(DP_WRITE_MSK, 0xffffffff);
	OUTREG(DP_CNTL, (xdir>=0 ? DST_X_LEFT_TO_RIGHT : 0)
			| (ydir>=0 ? DST_Y_TOP_TO_BOTTOM : 0));

	radeon_fअगरo_रुको(2);
	OUTREG(DSTCACHE_CTLSTAT, RB2D_DC_FLUSH_ALL);
	OUTREG(WAIT_UNTIL, (WAIT_2D_IDLECLEAN | WAIT_DMA_GUI_IDLE));

	radeon_fअगरo_रुको(3);
	OUTREG(SRC_Y_X, (sy << 16) | sx);
	OUTREG(DST_Y_X, (dy << 16) | dx);
	OUTREG(DST_HEIGHT_WIDTH, (h << 16) | w);
पूर्ण


व्योम radeonfb_copyarea(काष्ठा fb_info *info, स्थिर काष्ठा fb_copyarea *area)
अणु
	काष्ठा radeonfb_info *rinfo = info->par;
	काष्ठा fb_copyarea modded;
	u32 vxres, vyres;
	modded.sx = area->sx;
	modded.sy = area->sy;
	modded.dx = area->dx;
	modded.dy = area->dy;
	modded.width  = area->width;
	modded.height = area->height;
  
	अगर (info->state != FBINFO_STATE_RUNNING)
		वापस;
	अगर (info->flags & FBINFO_HWACCEL_DISABLED) अणु
		cfb_copyarea(info, area);
		वापस;
	पूर्ण

	radeon_fixup_offset(rinfo);

	vxres = info->var.xres_भव;
	vyres = info->var.yres_भव;

	अगर(!modded.width || !modded.height ||
	   modded.sx >= vxres || modded.sy >= vyres ||
	   modded.dx >= vxres || modded.dy >= vyres)
		वापस;
  
	अगर(modded.sx + modded.width > vxres)  modded.width = vxres - modded.sx;
	अगर(modded.dx + modded.width > vxres)  modded.width = vxres - modded.dx;
	अगर(modded.sy + modded.height > vyres) modded.height = vyres - modded.sy;
	अगर(modded.dy + modded.height > vyres) modded.height = vyres - modded.dy;
  
	radeonfb_prim_copyarea(rinfo, &modded);
पूर्ण

व्योम radeonfb_imageblit(काष्ठा fb_info *info, स्थिर काष्ठा fb_image *image)
अणु
	काष्ठा radeonfb_info *rinfo = info->par;

	अगर (info->state != FBINFO_STATE_RUNNING)
		वापस;
	radeon_engine_idle();

	cfb_imageblit(info, image);
पूर्ण

पूर्णांक radeonfb_sync(काष्ठा fb_info *info)
अणु
	काष्ठा radeonfb_info *rinfo = info->par;

	अगर (info->state != FBINFO_STATE_RUNNING)
		वापस 0;
	radeon_engine_idle();

	वापस 0;
पूर्ण

व्योम radeonfb_engine_reset(काष्ठा radeonfb_info *rinfo)
अणु
	u32 घड़ी_cntl_index, mclk_cntl, rbbm_soft_reset;
	u32 host_path_cntl;

	radeon_engine_flush (rinfo);

	घड़ी_cntl_index = INREG(CLOCK_CNTL_INDEX);
	mclk_cntl = INPLL(MCLK_CNTL);

	OUTPLL(MCLK_CNTL, (mclk_cntl |
			   FORCEON_MCLKA |
			   FORCEON_MCLKB |
			   FORCEON_YCLKA |
			   FORCEON_YCLKB |
			   FORCEON_MC |
			   FORCEON_AIC));

	host_path_cntl = INREG(HOST_PATH_CNTL);
	rbbm_soft_reset = INREG(RBBM_SOFT_RESET);

	अगर (IS_R300_VARIANT(rinfo)) अणु
		u32 पंचांगp;

		OUTREG(RBBM_SOFT_RESET, (rbbm_soft_reset |
					 SOFT_RESET_CP |
					 SOFT_RESET_HI |
					 SOFT_RESET_E2));
		INREG(RBBM_SOFT_RESET);
		OUTREG(RBBM_SOFT_RESET, 0);
		पंचांगp = INREG(RB2D_DSTCACHE_MODE);
		OUTREG(RB2D_DSTCACHE_MODE, पंचांगp | (1 << 17)); /* FIXME */
	पूर्ण अन्यथा अणु
		OUTREG(RBBM_SOFT_RESET, rbbm_soft_reset |
					SOFT_RESET_CP |
					SOFT_RESET_HI |
					SOFT_RESET_SE |
					SOFT_RESET_RE |
					SOFT_RESET_PP |
					SOFT_RESET_E2 |
					SOFT_RESET_RB);
		INREG(RBBM_SOFT_RESET);
		OUTREG(RBBM_SOFT_RESET, rbbm_soft_reset & (u32)
					~(SOFT_RESET_CP |
					  SOFT_RESET_HI |
					  SOFT_RESET_SE |
					  SOFT_RESET_RE |
					  SOFT_RESET_PP |
					  SOFT_RESET_E2 |
					  SOFT_RESET_RB));
		INREG(RBBM_SOFT_RESET);
	पूर्ण

	OUTREG(HOST_PATH_CNTL, host_path_cntl | HDP_SOFT_RESET);
	INREG(HOST_PATH_CNTL);
	OUTREG(HOST_PATH_CNTL, host_path_cntl);

	अगर (!IS_R300_VARIANT(rinfo))
		OUTREG(RBBM_SOFT_RESET, rbbm_soft_reset);

	OUTREG(CLOCK_CNTL_INDEX, घड़ी_cntl_index);
	OUTPLL(MCLK_CNTL, mclk_cntl);
पूर्ण

व्योम radeonfb_engine_init (काष्ठा radeonfb_info *rinfo)
अणु
	अचिन्हित दीर्घ temp;

	/* disable 3D engine */
	OUTREG(RB3D_CNTL, 0);

	radeonfb_engine_reset(rinfo);

	radeon_fअगरo_रुको (1);
	अगर (IS_R300_VARIANT(rinfo)) अणु
		OUTREG(RB2D_DSTCACHE_MODE, INREG(RB2D_DSTCACHE_MODE) |
		       RB2D_DC_AUTOFLUSH_ENABLE |
		       RB2D_DC_DC_DISABLE_IGNORE_PE);
	पूर्ण अन्यथा अणु
		/* This needs to be द्विगुन checked with ATI. Latest X driver
		 * completely "forgets" to set this रेजिस्टर on < r3xx, and
		 * we used to just ग_लिखो 0 there... I'll keep the 0 and update
		 * that when we have sorted things out on X side.
		 */
		OUTREG(RB2D_DSTCACHE_MODE, 0);
	पूर्ण

	radeon_fअगरo_रुको (3);
	/* We re-पढ़ो MC_FB_LOCATION from card as it can have been
	 * modअगरied by XFree drivers (ouch !)
	 */
	rinfo->fb_local_base = INREG(MC_FB_LOCATION) << 16;

	OUTREG(DEFAULT_PITCH_OFFSET, (rinfo->pitch << 0x16) |
				     (rinfo->fb_local_base >> 10));
	OUTREG(DST_PITCH_OFFSET, (rinfo->pitch << 0x16) | (rinfo->fb_local_base >> 10));
	OUTREG(SRC_PITCH_OFFSET, (rinfo->pitch << 0x16) | (rinfo->fb_local_base >> 10));

	radeon_fअगरo_रुको (1);
#अगर defined(__BIG_ENDIAN)
	OUTREGP(DP_DATATYPE, HOST_BIG_ENDIAN_EN, ~HOST_BIG_ENDIAN_EN);
#अन्यथा
	OUTREGP(DP_DATATYPE, 0, ~HOST_BIG_ENDIAN_EN);
#पूर्ण_अगर
	radeon_fअगरo_रुको (2);
	OUTREG(DEFAULT_SC_TOP_LEFT, 0);
	OUTREG(DEFAULT_SC_BOTTOM_RIGHT, (DEFAULT_SC_RIGHT_MAX |
					 DEFAULT_SC_BOTTOM_MAX));

	temp = radeon_get_dstbpp(rinfo->depth);
	rinfo->dp_gui_master_cntl = ((temp << 8) | GMC_CLR_CMP_CNTL_DIS);

	radeon_fअगरo_रुको (1);
	OUTREG(DP_GUI_MASTER_CNTL, (rinfo->dp_gui_master_cntl |
				    GMC_BRUSH_SOLID_COLOR |
				    GMC_SRC_DATATYPE_COLOR));

	radeon_fअगरo_रुको (7);

	/* clear line drawing regs */
	OUTREG(DST_LINE_START, 0);
	OUTREG(DST_LINE_END, 0);

	/* set brush color regs */
	OUTREG(DP_BRUSH_FRGD_CLR, 0xffffffff);
	OUTREG(DP_BRUSH_BKGD_CLR, 0x00000000);

	/* set source color regs */
	OUTREG(DP_SRC_FRGD_CLR, 0xffffffff);
	OUTREG(DP_SRC_BKGD_CLR, 0x00000000);

	/* शेष ग_लिखो mask */
	OUTREG(DP_WRITE_MSK, 0xffffffff);

	radeon_engine_idle ();
पूर्ण
