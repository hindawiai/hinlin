<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Frame buffer driver क्रम the Carmine GPU.
 *
 * The driver configures the GPU as follows
 * - FB0 is display 0 with unique memory area
 * - FB1 is display 1 with unique memory area
 * - both display use 32 bit colors
 */
#समावेश <linux/delay.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/fb.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/pci.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>

#समावेश "carminefb.h"
#समावेश "carminefb_regs.h"

#अगर !defined(__LITTLE_ENDIAN) && !defined(__BIG_ENDIAN)
#त्रुटि  "The endianness of the target host has not been defined."
#पूर्ण_अगर

/*
 * The initial video mode can be supplied via two dअगरferent ways:
 * - as a string that is passed to fb_find_mode() (module option fb_mode_str)
 * - as an पूर्णांकeger that picks the video mode from carmine_modedb[] (module
 *   option fb_mode)
 *
 * If nothing is used than the initial video mode will be the
 * CARMINEFB_DEFAULT_VIDEO_MODE member of the carmine_modedb[].
 */
#घोषणा CARMINEFB_DEFAULT_VIDEO_MODE	1

अटल अचिन्हित पूर्णांक fb_mode = CARMINEFB_DEFAULT_VIDEO_MODE;
module_param(fb_mode, uपूर्णांक, 0444);
MODULE_PARM_DESC(fb_mode, "Initial video mode as integer.");

अटल अक्षर *fb_mode_str;
module_param(fb_mode_str, अक्षरp, 0444);
MODULE_PARM_DESC(fb_mode_str, "Initial video mode in characters.");

/*
 * Carminefb displays:
 * 0b000 None
 * 0b001 Display 0
 * 0b010 Display 1
 */
अटल पूर्णांक fb_displays = CARMINE_USE_DISPLAY0 | CARMINE_USE_DISPLAY1;
module_param(fb_displays, पूर्णांक, 0444);
MODULE_PARM_DESC(fb_displays, "Bit mode, which displays are used");

काष्ठा carmine_hw अणु
	व्योम __iomem *v_regs;
	व्योम __iomem *screen_mem;
	काष्ठा fb_info *fb[MAX_DISPLAY];
पूर्ण;

काष्ठा carmine_resolution अणु
	u32 htp;
	u32 hsp;
	u32 hsw;
	u32 hdp;
	u32 vtr;
	u32 vsp;
	u32 vsw;
	u32 vdp;
	u32 disp_mode;
पूर्ण;

काष्ठा carmine_fb अणु
	व्योम __iomem *display_reg;
	व्योम __iomem *screen_base;
	u32 smem_offset;
	u32 cur_mode;
	u32 new_mode;
	काष्ठा carmine_resolution *res;
	u32 pseuकरो_palette[16];
पूर्ण;

अटल काष्ठा fb_fix_screeninfo carminefb_fix = अणु
	.id = "Carmine",
	.type = FB_TYPE_PACKED_PIXELS,
	.visual = FB_VISUAL_TRUECOLOR,
	.accel = FB_ACCEL_NONE,
पूर्ण;

अटल स्थिर काष्ठा fb_videomode carmine_modedb[] = अणु
	अणु
		.name		= "640x480",
		.xres		= 640,
		.yres		= 480,
	पूर्ण, अणु
		.name		= "800x600",
		.xres		= 800,
		.yres		= 600,
	पूर्ण,
पूर्ण;

अटल काष्ठा carmine_resolution car_modes[] = अणु
	अणु
		/* 640x480 */
		.htp = 800,
		.hsp = 672,
		.hsw = 96,
		.hdp = 640,
		.vtr = 525,
		.vsp = 490,
		.vsw = 2,
		.vdp = 480,
		.disp_mode = 0x1400,
	पूर्ण,
	अणु
		/* 800x600 */
		.htp = 1060,
		.hsp = 864,
		.hsw = 72,
		.hdp = 800,
		.vtr = 628,
		.vsp = 601,
		.vsw = 2,
		.vdp = 600,
		.disp_mode = 0x0d00,
	पूर्ण
पूर्ण;

अटल पूर्णांक carmine_find_mode(स्थिर काष्ठा fb_var_screeninfo *var)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(car_modes); i++)
		अगर (car_modes[i].hdp == var->xres &&
		    car_modes[i].vdp == var->yres)
			वापस i;
	वापस -EINVAL;
पूर्ण

अटल व्योम c_set_disp_reg(स्थिर काष्ठा carmine_fb *par,
		u32 offset, u32 val)
अणु
	ग_लिखोl(val, par->display_reg + offset);
पूर्ण

अटल u32 c_get_disp_reg(स्थिर काष्ठा carmine_fb *par,
		u32 offset)
अणु
	वापस पढ़ोl(par->display_reg + offset);
पूर्ण

अटल व्योम c_set_hw_reg(स्थिर काष्ठा carmine_hw *hw,
		u32 offset, u32 val)
अणु
	ग_लिखोl(val, hw->v_regs + offset);
पूर्ण

अटल u32 c_get_hw_reg(स्थिर काष्ठा carmine_hw *hw,
		u32 offset)
अणु
	वापस पढ़ोl(hw->v_regs + offset);
पूर्ण

अटल पूर्णांक carmine_setcolreg(अचिन्हित regno, अचिन्हित red, अचिन्हित green,
		अचिन्हित blue, अचिन्हित transp, काष्ठा fb_info *info)
अणु
	अगर (regno >= 16)
		वापस 1;

	red >>= 8;
	green >>= 8;
	blue >>= 8;
	transp >>= 8;

	((__be32 *)info->pseuकरो_palette)[regno] = cpu_to_be32(transp << 24 |
		red << 0 | green << 8 | blue << 16);
	वापस 0;
पूर्ण

अटल पूर्णांक carmine_check_var(काष्ठा fb_var_screeninfo *var,
		काष्ठा fb_info *info)
अणु
	पूर्णांक ret;

	ret = carmine_find_mode(var);
	अगर (ret < 0)
		वापस ret;

	अगर (var->grayscale || var->rotate || var->nonstd)
		वापस -EINVAL;

	var->xres_भव = var->xres;
	var->yres_भव = var->yres;

	var->bits_per_pixel = 32;

#अगर_घोषित __BIG_ENDIAN
	var->transp.offset = 24;
	var->red.offset = 0;
	var->green.offset = 8;
	var->blue.offset = 16;
#अन्यथा
	var->transp.offset = 24;
	var->red.offset = 16;
	var->green.offset = 8;
	var->blue.offset = 0;
#पूर्ण_अगर

	var->red.length = 8;
	var->green.length = 8;
	var->blue.length = 8;
	var->transp.length = 8;

	var->red.msb_right = 0;
	var->green.msb_right = 0;
	var->blue.msb_right = 0;
	var->transp.msb_right = 0;
	वापस 0;
पूर्ण

अटल व्योम carmine_init_display_param(काष्ठा carmine_fb *par)
अणु
	u32 width;
	u32 height;
	u32 param;
	u32 winकरोw_size;
	u32 soffset = par->smem_offset;

	c_set_disp_reg(par, CARMINE_DISP_REG_C_TRANS, 0);
	c_set_disp_reg(par, CARMINE_DISP_REG_MLMR_TRANS, 0);
	c_set_disp_reg(par, CARMINE_DISP_REG_CURSOR_MODE,
			CARMINE_CURSOR0_PRIORITY_MASK |
			CARMINE_CURSOR1_PRIORITY_MASK |
			CARMINE_CURSOR_CUTZ_MASK);

	/* Set शेष cursor position */
	c_set_disp_reg(par, CARMINE_DISP_REG_CUR1_POS, 0 << 16 | 0);
	c_set_disp_reg(par, CARMINE_DISP_REG_CUR2_POS, 0 << 16 | 0);

	/* Set शेष display mode */
	c_set_disp_reg(par, CARMINE_DISP_REG_L0_EXT_MODE, CARMINE_WINDOW_MODE |
			CARMINE_EXT_CMODE_सूचीECT24_RGBA);
	c_set_disp_reg(par, CARMINE_DISP_REG_L1_EXT_MODE,
			CARMINE_EXT_CMODE_सूचीECT24_RGBA);
	c_set_disp_reg(par, CARMINE_DISP_REG_L2_EXT_MODE, CARMINE_EXTEND_MODE |
			CARMINE_EXT_CMODE_सूचीECT24_RGBA);
	c_set_disp_reg(par, CARMINE_DISP_REG_L3_EXT_MODE, CARMINE_EXTEND_MODE |
			CARMINE_EXT_CMODE_सूचीECT24_RGBA);
	c_set_disp_reg(par, CARMINE_DISP_REG_L4_EXT_MODE, CARMINE_EXTEND_MODE |
			CARMINE_EXT_CMODE_सूचीECT24_RGBA);
	c_set_disp_reg(par, CARMINE_DISP_REG_L5_EXT_MODE, CARMINE_EXTEND_MODE |
			CARMINE_EXT_CMODE_सूचीECT24_RGBA);
	c_set_disp_reg(par, CARMINE_DISP_REG_L6_EXT_MODE, CARMINE_EXTEND_MODE |
			CARMINE_EXT_CMODE_सूचीECT24_RGBA);
	c_set_disp_reg(par, CARMINE_DISP_REG_L7_EXT_MODE, CARMINE_EXTEND_MODE |
			CARMINE_EXT_CMODE_सूचीECT24_RGBA);

	/* Set शेष frame size to layer mode रेजिस्टर */
	width = par->res->hdp * 4 / CARMINE_DISP_WIDTH_UNIT;
	width = width << CARMINE_DISP_WIDTH_SHIFT;

	height = par->res->vdp - 1;
	param = width | height;

	c_set_disp_reg(par, CARMINE_DISP_REG_L0_MODE_W_H, param);
	c_set_disp_reg(par, CARMINE_DISP_REG_L1_WIDTH, width);
	c_set_disp_reg(par, CARMINE_DISP_REG_L2_MODE_W_H, param);
	c_set_disp_reg(par, CARMINE_DISP_REG_L3_MODE_W_H, param);
	c_set_disp_reg(par, CARMINE_DISP_REG_L4_MODE_W_H, param);
	c_set_disp_reg(par, CARMINE_DISP_REG_L5_MODE_W_H, param);
	c_set_disp_reg(par, CARMINE_DISP_REG_L6_MODE_W_H, param);
	c_set_disp_reg(par, CARMINE_DISP_REG_L7_MODE_W_H, param);

	/* Set शेष pos and size */
	winकरोw_size = (par->res->vdp - 1) << CARMINE_DISP_WIN_H_SHIFT;
	winकरोw_size |= par->res->hdp;

	c_set_disp_reg(par, CARMINE_DISP_REG_L0_WIN_POS, 0);
	c_set_disp_reg(par, CARMINE_DISP_REG_L0_WIN_SIZE, winकरोw_size);
	c_set_disp_reg(par, CARMINE_DISP_REG_L1_WIN_POS, 0);
	c_set_disp_reg(par, CARMINE_DISP_REG_L1_WIN_SIZE, winकरोw_size);
	c_set_disp_reg(par, CARMINE_DISP_REG_L2_WIN_POS, 0);
	c_set_disp_reg(par, CARMINE_DISP_REG_L2_WIN_SIZE, winकरोw_size);
	c_set_disp_reg(par, CARMINE_DISP_REG_L3_WIN_POS, 0);
	c_set_disp_reg(par, CARMINE_DISP_REG_L3_WIN_SIZE, winकरोw_size);
	c_set_disp_reg(par, CARMINE_DISP_REG_L4_WIN_POS, 0);
	c_set_disp_reg(par, CARMINE_DISP_REG_L4_WIN_SIZE, winकरोw_size);
	c_set_disp_reg(par, CARMINE_DISP_REG_L5_WIN_POS, 0);
	c_set_disp_reg(par, CARMINE_DISP_REG_L5_WIN_SIZE, winकरोw_size);
	c_set_disp_reg(par, CARMINE_DISP_REG_L6_WIN_POS, 0);
	c_set_disp_reg(par, CARMINE_DISP_REG_L6_WIN_SIZE, winकरोw_size);
	c_set_disp_reg(par, CARMINE_DISP_REG_L7_WIN_POS, 0);
	c_set_disp_reg(par, CARMINE_DISP_REG_L7_WIN_SIZE, winकरोw_size);

	/* Set शेष origin address */
	c_set_disp_reg(par, CARMINE_DISP_REG_L0_ORG_ADR, soffset);
	c_set_disp_reg(par, CARMINE_DISP_REG_L1_ORG_ADR, soffset);
	c_set_disp_reg(par, CARMINE_DISP_REG_L2_ORG_ADR1, soffset);
	c_set_disp_reg(par, CARMINE_DISP_REG_L3_ORG_ADR1, soffset);
	c_set_disp_reg(par, CARMINE_DISP_REG_L4_ORG_ADR1, soffset);
	c_set_disp_reg(par, CARMINE_DISP_REG_L5_ORG_ADR1, soffset);
	c_set_disp_reg(par, CARMINE_DISP_REG_L6_ORG_ADR1, soffset);
	c_set_disp_reg(par, CARMINE_DISP_REG_L7_ORG_ADR1, soffset);

	/* Set शेष display address */
	c_set_disp_reg(par, CARMINE_DISP_REG_L0_DISP_ADR, soffset);
	c_set_disp_reg(par, CARMINE_DISP_REG_L2_DISP_ADR1, soffset);
	c_set_disp_reg(par, CARMINE_DISP_REG_L3_DISP_ADR1, soffset);
	c_set_disp_reg(par, CARMINE_DISP_REG_L4_DISP_ADR1, soffset);
	c_set_disp_reg(par, CARMINE_DISP_REG_L5_DISP_ADR1, soffset);
	c_set_disp_reg(par, CARMINE_DISP_REG_L6_DISP_ADR0, soffset);
	c_set_disp_reg(par, CARMINE_DISP_REG_L7_DISP_ADR0, soffset);

	/* Set शेष display position */
	c_set_disp_reg(par, CARMINE_DISP_REG_L0_DISP_POS, 0);
	c_set_disp_reg(par, CARMINE_DISP_REG_L2_DISP_POS, 0);
	c_set_disp_reg(par, CARMINE_DISP_REG_L3_DISP_POS, 0);
	c_set_disp_reg(par, CARMINE_DISP_REG_L4_DISP_POS, 0);
	c_set_disp_reg(par, CARMINE_DISP_REG_L5_DISP_POS, 0);
	c_set_disp_reg(par, CARMINE_DISP_REG_L6_DISP_POS, 0);
	c_set_disp_reg(par, CARMINE_DISP_REG_L7_DISP_POS, 0);

	/* Set शेष blend mode */
	c_set_disp_reg(par, CARMINE_DISP_REG_BLEND_MODE_L0, 0);
	c_set_disp_reg(par, CARMINE_DISP_REG_BLEND_MODE_L1, 0);
	c_set_disp_reg(par, CARMINE_DISP_REG_BLEND_MODE_L2, 0);
	c_set_disp_reg(par, CARMINE_DISP_REG_BLEND_MODE_L3, 0);
	c_set_disp_reg(par, CARMINE_DISP_REG_BLEND_MODE_L4, 0);
	c_set_disp_reg(par, CARMINE_DISP_REG_BLEND_MODE_L5, 0);
	c_set_disp_reg(par, CARMINE_DISP_REG_BLEND_MODE_L6, 0);
	c_set_disp_reg(par, CARMINE_DISP_REG_BLEND_MODE_L7, 0);

	/* शेष transparency mode */
	c_set_disp_reg(par, CARMINE_DISP_REG_L0_TRANS, 0);
	c_set_disp_reg(par, CARMINE_DISP_REG_L1_TRANS, 0);
	c_set_disp_reg(par, CARMINE_DISP_REG_L2_TRANS, 0);
	c_set_disp_reg(par, CARMINE_DISP_REG_L3_TRANS, 0);
	c_set_disp_reg(par, CARMINE_DISP_REG_L4_TRANS, 0);
	c_set_disp_reg(par, CARMINE_DISP_REG_L5_TRANS, 0);
	c_set_disp_reg(par, CARMINE_DISP_REG_L6_TRANS, 0);
	c_set_disp_reg(par, CARMINE_DISP_REG_L7_TRANS, 0);

	/* Set शेष पढ़ो skip parameter */
	c_set_disp_reg(par, CARMINE_DISP_REG_L0RM, 0);
	c_set_disp_reg(par, CARMINE_DISP_REG_L2RM, 0);
	c_set_disp_reg(par, CARMINE_DISP_REG_L3RM, 0);
	c_set_disp_reg(par, CARMINE_DISP_REG_L4RM, 0);
	c_set_disp_reg(par, CARMINE_DISP_REG_L5RM, 0);
	c_set_disp_reg(par, CARMINE_DISP_REG_L6RM, 0);
	c_set_disp_reg(par, CARMINE_DISP_REG_L7RM, 0);

	c_set_disp_reg(par, CARMINE_DISP_REG_L0PX, 0);
	c_set_disp_reg(par, CARMINE_DISP_REG_L2PX, 0);
	c_set_disp_reg(par, CARMINE_DISP_REG_L3PX, 0);
	c_set_disp_reg(par, CARMINE_DISP_REG_L4PX, 0);
	c_set_disp_reg(par, CARMINE_DISP_REG_L5PX, 0);
	c_set_disp_reg(par, CARMINE_DISP_REG_L6PX, 0);
	c_set_disp_reg(par, CARMINE_DISP_REG_L7PX, 0);

	c_set_disp_reg(par, CARMINE_DISP_REG_L0PY, 0);
	c_set_disp_reg(par, CARMINE_DISP_REG_L2PY, 0);
	c_set_disp_reg(par, CARMINE_DISP_REG_L3PY, 0);
	c_set_disp_reg(par, CARMINE_DISP_REG_L4PY, 0);
	c_set_disp_reg(par, CARMINE_DISP_REG_L5PY, 0);
	c_set_disp_reg(par, CARMINE_DISP_REG_L6PY, 0);
	c_set_disp_reg(par, CARMINE_DISP_REG_L7PY, 0);
पूर्ण

अटल व्योम set_display_parameters(काष्ठा carmine_fb *par)
अणु
	u32 mode;
	u32 hdp, vdp, htp, hsp, hsw, vtr, vsp, vsw;

	/*
	 * display timing. Parameters are decreased by one because hardware
	 * spec is 0 to (n - 1)
	 * */
	hdp = par->res->hdp - 1;
	vdp = par->res->vdp - 1;
	htp = par->res->htp - 1;
	hsp = par->res->hsp - 1;
	hsw = par->res->hsw - 1;
	vtr = par->res->vtr - 1;
	vsp = par->res->vsp - 1;
	vsw = par->res->vsw - 1;

	c_set_disp_reg(par, CARMINE_DISP_REG_H_TOTAL,
			htp << CARMINE_DISP_HTP_SHIFT);
	c_set_disp_reg(par, CARMINE_DISP_REG_H_PERIOD,
			(hdp << CARMINE_DISP_HDB_SHIFT)	| hdp);
	c_set_disp_reg(par, CARMINE_DISP_REG_V_H_W_H_POS,
			(vsw << CARMINE_DISP_VSW_SHIFT) |
			(hsw << CARMINE_DISP_HSW_SHIFT) |
			(hsp));
	c_set_disp_reg(par, CARMINE_DISP_REG_V_TOTAL,
			vtr << CARMINE_DISP_VTR_SHIFT);
	c_set_disp_reg(par, CARMINE_DISP_REG_V_PERIOD_POS,
			(vdp << CARMINE_DISP_VDP_SHIFT) | vsp);

	/* घड़ी */
	mode = c_get_disp_reg(par, CARMINE_DISP_REG_DCM1);
	mode = (mode & ~CARMINE_DISP_DCM_MASK) |
		(par->res->disp_mode & CARMINE_DISP_DCM_MASK);
	/* enable video output and layer 0 */
	mode |= CARMINE_DEN | CARMINE_L0E;
	c_set_disp_reg(par, CARMINE_DISP_REG_DCM1, mode);
पूर्ण

अटल पूर्णांक carmine_set_par(काष्ठा fb_info *info)
अणु
	काष्ठा carmine_fb *par = info->par;
	पूर्णांक ret;

	ret = carmine_find_mode(&info->var);
	अगर (ret < 0)
		वापस ret;

	par->new_mode = ret;
	अगर (par->cur_mode != par->new_mode) अणु

		par->cur_mode = par->new_mode;
		par->res = &car_modes[par->new_mode];

		carmine_init_display_param(par);
		set_display_parameters(par);
	पूर्ण

	info->fix.line_length = info->var.xres * info->var.bits_per_pixel / 8;
	वापस 0;
पूर्ण

अटल पूर्णांक init_hardware(काष्ठा carmine_hw *hw)
अणु
	u32 flags;
	u32 loops;
	u32 ret;

	/* Initialize Carmine */
	/* Sets पूर्णांकernal घड़ी */
	c_set_hw_reg(hw, CARMINE_CTL_REG + CARMINE_CTL_REG_CLOCK_ENABLE,
			CARMINE_DFLT_IP_CLOCK_ENABLE);

	/* Video संकेत output is turned off */
	c_set_hw_reg(hw, CARMINE_DISP0_REG + CARMINE_DISP_REG_DCM1, 0);
	c_set_hw_reg(hw, CARMINE_DISP1_REG + CARMINE_DISP_REG_DCM1, 0);

	/* Software reset */
	c_set_hw_reg(hw, CARMINE_CTL_REG + CARMINE_CTL_REG_SOFTWARE_RESET, 1);
	c_set_hw_reg(hw, CARMINE_CTL_REG + CARMINE_CTL_REG_SOFTWARE_RESET, 0);

	/* I/O mode settings */
	flags = CARMINE_DFLT_IP_DCTL_IO_CONT1 << 16 |
		CARMINE_DFLT_IP_DCTL_IO_CONT0;
	c_set_hw_reg(hw, CARMINE_DCTL_REG + CARMINE_DCTL_REG_IOCONT1_IOCONT0,
			flags);

	/* DRAM initial sequence */
	flags = CARMINE_DFLT_IP_DCTL_MODE << 16 | CARMINE_DFLT_IP_DCTL_ADD;
	c_set_hw_reg(hw, CARMINE_DCTL_REG + CARMINE_DCTL_REG_MODE_ADD,
			flags);

	flags = CARMINE_DFLT_IP_DCTL_SET_TIME1 << 16 |
		CARMINE_DFLT_IP_DCTL_EMODE;
	c_set_hw_reg(hw, CARMINE_DCTL_REG + CARMINE_DCTL_REG_SETTIME1_EMODE,
			flags);

	flags = CARMINE_DFLT_IP_DCTL_REFRESH << 16 |
		CARMINE_DFLT_IP_DCTL_SET_TIME2;
	c_set_hw_reg(hw, CARMINE_DCTL_REG + CARMINE_DCTL_REG_REFRESH_SETTIME2,
			flags);

	flags = CARMINE_DFLT_IP_DCTL_RESERVE2 << 16 |
		CARMINE_DFLT_IP_DCTL_FIFO_DEPTH;
	c_set_hw_reg(hw, CARMINE_DCTL_REG + CARMINE_DCTL_REG_RSV2_RSV1, flags);

	flags = CARMINE_DFLT_IP_DCTL_DDRIF2 << 16 | CARMINE_DFLT_IP_DCTL_DDRIF1;
	c_set_hw_reg(hw, CARMINE_DCTL_REG + CARMINE_DCTL_REG_DDRIF2_DDRIF1,
			flags);

	flags = CARMINE_DFLT_IP_DCTL_RESERVE0 << 16 |
		CARMINE_DFLT_IP_DCTL_STATES;
	c_set_hw_reg(hw, CARMINE_DCTL_REG + CARMINE_DCTL_REG_RSV0_STATES,
			flags);

	/* Executes DLL reset */
	अगर (CARMINE_DCTL_DLL_RESET) अणु
		क्रम (loops = 0; loops < CARMINE_DCTL_INIT_WAIT_LIMIT; loops++) अणु

			ret = c_get_hw_reg(hw, CARMINE_DCTL_REG +
					CARMINE_DCTL_REG_RSV0_STATES);
			ret &= CARMINE_DCTL_REG_STATES_MASK;
			अगर (!ret)
				अवरोध;

			mdelay(CARMINE_DCTL_INIT_WAIT_INTERVAL);
		पूर्ण

		अगर (loops >= CARMINE_DCTL_INIT_WAIT_LIMIT) अणु
			prपूर्णांकk(KERN_ERR "DRAM init failed\n");
			वापस -EIO;
		पूर्ण
	पूर्ण

	flags = CARMINE_DFLT_IP_DCTL_MODE_AFT_RST << 16 |
		CARMINE_DFLT_IP_DCTL_ADD;
	c_set_hw_reg(hw, CARMINE_DCTL_REG + CARMINE_DCTL_REG_MODE_ADD, flags);

	flags = CARMINE_DFLT_IP_DCTL_RESERVE0 << 16 |
		CARMINE_DFLT_IP_DCTL_STATES_AFT_RST;
	c_set_hw_reg(hw, CARMINE_DCTL_REG + CARMINE_DCTL_REG_RSV0_STATES,
			flags);

	/* Initialize the ग_लिखो back रेजिस्टर */
	c_set_hw_reg(hw, CARMINE_WB_REG + CARMINE_WB_REG_WBM,
			CARMINE_WB_REG_WBM_DEFAULT);

	/* Initialize the Kottos रेजिस्टरs */
	c_set_hw_reg(hw, CARMINE_GRAPH_REG + CARMINE_GRAPH_REG_VRINTM, 0);
	c_set_hw_reg(hw, CARMINE_GRAPH_REG + CARMINE_GRAPH_REG_VRERRM, 0);

	/* Set DC offsets */
	c_set_hw_reg(hw, CARMINE_GRAPH_REG + CARMINE_GRAPH_REG_DC_OFFSET_PX, 0);
	c_set_hw_reg(hw, CARMINE_GRAPH_REG + CARMINE_GRAPH_REG_DC_OFFSET_PY, 0);
	c_set_hw_reg(hw, CARMINE_GRAPH_REG + CARMINE_GRAPH_REG_DC_OFFSET_LX, 0);
	c_set_hw_reg(hw, CARMINE_GRAPH_REG + CARMINE_GRAPH_REG_DC_OFFSET_LY, 0);
	c_set_hw_reg(hw, CARMINE_GRAPH_REG + CARMINE_GRAPH_REG_DC_OFFSET_TX, 0);
	c_set_hw_reg(hw, CARMINE_GRAPH_REG + CARMINE_GRAPH_REG_DC_OFFSET_TY, 0);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा fb_ops carminefb_ops = अणु
	.owner		= THIS_MODULE,
	.fb_fillrect	= cfb_fillrect,
	.fb_copyarea	= cfb_copyarea,
	.fb_imageblit	= cfb_imageblit,

	.fb_check_var	= carmine_check_var,
	.fb_set_par	= carmine_set_par,
	.fb_setcolreg	= carmine_setcolreg,
पूर्ण;

अटल पूर्णांक alloc_carmine_fb(व्योम __iomem *regs, व्योम __iomem *smem_base,
			    पूर्णांक smem_offset, काष्ठा device *device,
			    काष्ठा fb_info **rinfo)
अणु
	पूर्णांक ret;
	काष्ठा fb_info *info;
	काष्ठा carmine_fb *par;

	info = framebuffer_alloc(माप *par, device);
	अगर (!info)
		वापस -ENOMEM;

	par = info->par;
	par->display_reg = regs;
	par->smem_offset = smem_offset;

	info->screen_base = smem_base + smem_offset;
	info->screen_size = CARMINE_DISPLAY_MEM;
	info->fbops = &carminefb_ops;

	info->fix = carminefb_fix;
	info->pseuकरो_palette = par->pseuकरो_palette;
	info->flags = FBINFO_DEFAULT;

	ret = fb_alloc_cmap(&info->cmap, 256, 1);
	अगर (ret < 0)
		जाओ err_मुक्त_fb;

	अगर (fb_mode >= ARRAY_SIZE(carmine_modedb))
		fb_mode = CARMINEFB_DEFAULT_VIDEO_MODE;

	par->cur_mode = par->new_mode = ~0;

	ret = fb_find_mode(&info->var, info, fb_mode_str, carmine_modedb,
			ARRAY_SIZE(carmine_modedb),
			&carmine_modedb[fb_mode], 32);
	अगर (!ret || ret == 4) अणु
		ret = -EINVAL;
		जाओ err_dealloc_cmap;
	पूर्ण

	fb_videomode_to_modelist(carmine_modedb, ARRAY_SIZE(carmine_modedb),
			&info->modelist);

	ret = रेजिस्टर_framebuffer(info);
	अगर (ret < 0)
		जाओ err_dealloc_cmap;

	fb_info(info, "%s frame buffer device\n", info->fix.id);

	*rinfo = info;
	वापस 0;

err_dealloc_cmap:
	fb_dealloc_cmap(&info->cmap);
err_मुक्त_fb:
	framebuffer_release(info);
	वापस ret;
पूर्ण

अटल व्योम cleanup_fb_device(काष्ठा fb_info *info)
अणु
	अगर (info) अणु
		unरेजिस्टर_framebuffer(info);
		fb_dealloc_cmap(&info->cmap);
		framebuffer_release(info);
	पूर्ण
पूर्ण

अटल पूर्णांक carminefb_probe(काष्ठा pci_dev *dev, स्थिर काष्ठा pci_device_id *ent)
अणु
	काष्ठा carmine_hw *hw;
	काष्ठा device *device = &dev->dev;
	काष्ठा fb_info *info;
	पूर्णांक ret;

	ret = pci_enable_device(dev);
	अगर (ret)
		वापस ret;

	ret = -ENOMEM;
	hw = kzalloc(माप *hw, GFP_KERNEL);
	अगर (!hw)
		जाओ err_enable_pci;

	carminefb_fix.mmio_start = pci_resource_start(dev, CARMINE_CONFIG_BAR);
	carminefb_fix.mmio_len = pci_resource_len(dev, CARMINE_CONFIG_BAR);

	अगर (!request_mem_region(carminefb_fix.mmio_start,
				carminefb_fix.mmio_len,
				"carminefb regbase")) अणु
		prपूर्णांकk(KERN_ERR "carminefb: Can't reserve regbase.\n");
		ret = -EBUSY;
		जाओ err_मुक्त_hw;
	पूर्ण
	hw->v_regs = ioremap(carminefb_fix.mmio_start,
			carminefb_fix.mmio_len);
	अगर (!hw->v_regs) अणु
		prपूर्णांकk(KERN_ERR "carminefb: Can't remap %s register.\n",
				carminefb_fix.id);
		जाओ err_मुक्त_reg_mmio;
	पूर्ण

	carminefb_fix.smem_start = pci_resource_start(dev, CARMINE_MEMORY_BAR);
	carminefb_fix.smem_len = pci_resource_len(dev, CARMINE_MEMORY_BAR);

	/* The memory area tends to be very large (256 MiB). Remap only what
	 * is required क्रम that largest resolution to aव्योम remaps at run
	 * समय
	 */
	अगर (carminefb_fix.smem_len > CARMINE_TOTAL_DIPLAY_MEM)
		carminefb_fix.smem_len = CARMINE_TOTAL_DIPLAY_MEM;

	अन्यथा अगर (carminefb_fix.smem_len < CARMINE_TOTAL_DIPLAY_MEM) अणु
		prपूर्णांकk(KERN_ERR "carminefb: Memory bar is only %d bytes, %d "
				"are required.", carminefb_fix.smem_len,
				CARMINE_TOTAL_DIPLAY_MEM);
		जाओ err_unmap_vregs;
	पूर्ण

	अगर (!request_mem_region(carminefb_fix.smem_start,
				carminefb_fix.smem_len,	"carminefb smem")) अणु
		prपूर्णांकk(KERN_ERR "carminefb: Can't reserve smem.\n");
		जाओ err_unmap_vregs;
	पूर्ण

	hw->screen_mem = ioremap(carminefb_fix.smem_start,
			carminefb_fix.smem_len);
	अगर (!hw->screen_mem) अणु
		prपूर्णांकk(KERN_ERR "carmine: Can't ioremap smem area.\n");
		जाओ err_reg_smem;
	पूर्ण

	ret = init_hardware(hw);
	अगर (ret)
		जाओ err_unmap_screen;

	info = शून्य;
	अगर (fb_displays & CARMINE_USE_DISPLAY0) अणु
		ret = alloc_carmine_fb(hw->v_regs + CARMINE_DISP0_REG,
				hw->screen_mem, CARMINE_DISPLAY_MEM * 0,
				device, &info);
		अगर (ret)
			जाओ err_deinit_hw;
	पूर्ण

	hw->fb[0] = info;

	info = शून्य;
	अगर (fb_displays & CARMINE_USE_DISPLAY1) अणु
		ret = alloc_carmine_fb(hw->v_regs + CARMINE_DISP1_REG,
				hw->screen_mem, CARMINE_DISPLAY_MEM * 1,
				device, &info);
		अगर (ret)
			जाओ err_cleanup_fb0;
	पूर्ण

	hw->fb[1] = info;
	info = शून्य;

	pci_set_drvdata(dev, hw);
	वापस 0;

err_cleanup_fb0:
	cleanup_fb_device(hw->fb[0]);
err_deinit_hw:
	/* disable घड़ी, etc */
	c_set_hw_reg(hw, CARMINE_CTL_REG + CARMINE_CTL_REG_CLOCK_ENABLE, 0);
err_unmap_screen:
	iounmap(hw->screen_mem);
err_reg_smem:
	release_mem_region(carminefb_fix.smem_start, carminefb_fix.smem_len);
err_unmap_vregs:
	iounmap(hw->v_regs);
err_मुक्त_reg_mmio:
	release_mem_region(carminefb_fix.mmio_start, carminefb_fix.mmio_len);
err_मुक्त_hw:
	kमुक्त(hw);
err_enable_pci:
	pci_disable_device(dev);
	वापस ret;
पूर्ण

अटल व्योम carminefb_हटाओ(काष्ठा pci_dev *dev)
अणु
	काष्ठा carmine_hw *hw = pci_get_drvdata(dev);
	काष्ठा fb_fix_screeninfo fix;
	पूर्णांक i;

	/* in हाल we use only fb1 and not fb1 */
	अगर (hw->fb[0])
		fix = hw->fb[0]->fix;
	अन्यथा
		fix = hw->fb[1]->fix;

	/* deactivate display(s) and चयन घड़ीs */
	c_set_hw_reg(hw, CARMINE_DISP0_REG + CARMINE_DISP_REG_DCM1, 0);
	c_set_hw_reg(hw, CARMINE_DISP1_REG + CARMINE_DISP_REG_DCM1, 0);
	c_set_hw_reg(hw, CARMINE_CTL_REG + CARMINE_CTL_REG_CLOCK_ENABLE, 0);

	क्रम (i = 0; i < MAX_DISPLAY; i++)
		cleanup_fb_device(hw->fb[i]);

	iounmap(hw->screen_mem);
	release_mem_region(fix.smem_start, fix.smem_len);
	iounmap(hw->v_regs);
	release_mem_region(fix.mmio_start, fix.mmio_len);

	pci_disable_device(dev);
	kमुक्त(hw);
पूर्ण

#घोषणा PCI_VENDOR_ID_FUJITU_LIMITED 0x10cf
अटल काष्ठा pci_device_id carmine_devices[] = अणु
अणु
	PCI_DEVICE(PCI_VENDOR_ID_FUJITU_LIMITED, 0x202b)पूर्ण,
	अणु0, 0, 0, 0, 0, 0, 0पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pci, carmine_devices);

अटल काष्ठा pci_driver carmine_pci_driver = अणु
	.name		= "carminefb",
	.id_table	= carmine_devices,
	.probe		= carminefb_probe,
	.हटाओ		= carminefb_हटाओ,
पूर्ण;

अटल पूर्णांक __init carminefb_init(व्योम)
अणु
	अगर (!(fb_displays &
		(CARMINE_USE_DISPLAY0 | CARMINE_USE_DISPLAY1))) अणु
		prपूर्णांकk(KERN_ERR "If you disable both displays than you don't "
				"need the driver at all\n");
		वापस -EINVAL;
	पूर्ण
	वापस pci_रेजिस्टर_driver(&carmine_pci_driver);
पूर्ण
module_init(carminefb_init);

अटल व्योम __निकास carminefb_cleanup(व्योम)
अणु
	pci_unरेजिस्टर_driver(&carmine_pci_driver);
पूर्ण
module_निकास(carminefb_cleanup);

MODULE_AUTHOR("Sebastian Siewior <bigeasy@linutronix.de>");
MODULE_DESCRIPTION("Framebuffer driver for Fujitsu Carmine based devices");
MODULE_LICENSE("GPL v2");
