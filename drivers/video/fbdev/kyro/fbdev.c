<शैली गुरु>
/*
 *  linux/drivers/video/kyro/fbdev.c
 *
 *  Copyright (C) 2002 STMicroelectronics
 *  Copyright (C) 2003, 2004 Paul Mundt
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file COPYING in the मुख्य directory of this archive
 * क्रम more details.
 */

#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/माला.स>
#समावेश <linux/delay.h>
#समावेश <linux/fb.h>
#समावेश <linux/ioctl.h>
#समावेश <linux/init.h>
#समावेश <linux/pci.h>
#समावेश <यंत्र/पन.स>
#समावेश <linux/uaccess.h>

#समावेश <video/kyro.h>

#समावेश "STG4000Reg.h"
#समावेश "STG4000Interface.h"

/*
 * PCI Definitions
 */
#घोषणा PCI_VENDOR_ID_ST	0x104a
#घोषणा PCI_DEVICE_ID_STG4000	0x0010

#घोषणा KHZ2PICOS(a) (1000000000UL/(a))

/****************************************************************************/
अटल काष्ठा fb_fix_screeninfo kyro_fix = अणु
	.id		= "ST Kyro",
	.type		= FB_TYPE_PACKED_PIXELS,
	.visual		= FB_VISUAL_TRUECOLOR,
	.accel		= FB_ACCEL_NONE,
पूर्ण;

अटल स्थिर काष्ठा fb_var_screeninfo kyro_var = अणु
	/* 640x480, 16bpp @ 60 Hz */
	.xres		= 640,
	.yres		= 480,
	.xres_भव	= 640,
	.yres_भव	= 480,
	.bits_per_pixel	= 16,
	.red		= अणु 11, 5, 0 पूर्ण,
	.green		= अणु  5, 6, 0 पूर्ण,
	.blue		= अणु  0, 5, 0 पूर्ण,
	.activate	= FB_ACTIVATE_NOW,
	.height		= -1,
	.width		= -1,
	.pixघड़ी	= KHZ2PICOS(25175),
	.left_margin	= 48,
	.right_margin	= 16,
	.upper_margin	= 33,
	.lower_margin	= 10,
	.hsync_len	= 96,
	.vsync_len	= 2,
	.vmode		= FB_VMODE_NONINTERLACED,
पूर्ण;

प्रकार काष्ठा अणु
	STG4000REG __iomem *pSTGReg;	/* Virtual address of PCI रेजिस्टर region */
	u32 ulNextFreeVidMem;	/* Offset from start of vid mem to next मुक्त region */
	u32 ulOverlayOffset;	/* Offset from start of vid mem to overlay */
	u32 ulOverlayStride;	/* Interleaved YUV and 422 mode Y stride */
	u32 ulOverlayUVStride;	/* 422 mode U & V stride */
पूर्ण device_info_t;

/* global graphics card info काष्ठाure (one per card) */
अटल device_info_t deviceInfo;

अटल अक्षर *mode_option = शून्य;
अटल पूर्णांक nopan = 0;
अटल पूर्णांक nowrap = 1;
अटल पूर्णांक nomtrr = 0;

/* PCI driver prototypes */
अटल पूर्णांक kyrofb_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *ent);
अटल व्योम kyrofb_हटाओ(काष्ठा pci_dev *pdev);

अटल काष्ठा fb_videomode kyro_modedb[] = अणु
	अणु
		/* 640x350 @ 85Hz */
		शून्य, 85, 640, 350, KHZ2PICOS(31500),
		96, 32, 60, 32, 64, 3,
		FB_SYNC_HOR_HIGH_ACT, FB_VMODE_NONINTERLACED
	पूर्ण, अणु
		/* 640x400 @ 85Hz */
		शून्य, 85, 640, 400, KHZ2PICOS(31500),
		96, 32, 41, 1, 64, 3,
		FB_SYNC_VERT_HIGH_ACT, FB_VMODE_NONINTERLACED
	पूर्ण, अणु
		/* 720x400 @ 85Hz */
		शून्य, 85, 720, 400, KHZ2PICOS(35500),
		108, 36, 42, 1, 72, 3,
		FB_SYNC_VERT_HIGH_ACT, FB_VMODE_NONINTERLACED
	पूर्ण, अणु
		/* 640x480 @ 60Hz */
		शून्य, 60, 640, 480, KHZ2PICOS(25175),
		48, 16, 33, 10, 96, 2,
		0, FB_VMODE_NONINTERLACED
	पूर्ण, अणु
		/* 640x480 @ 72Hz */
		शून्य, 72, 640, 480, KHZ2PICOS(31500),
		128, 24, 28, 9, 40, 3,
		0, FB_VMODE_NONINTERLACED
	पूर्ण, अणु
		/* 640x480 @ 75Hz */
		शून्य, 75, 640, 480, KHZ2PICOS(31500),
		120, 16, 16, 1, 64, 3,
		0, FB_VMODE_NONINTERLACED
	पूर्ण, अणु
		/* 640x480 @ 85Hz */
		शून्य, 85, 640, 480, KHZ2PICOS(36000),
		80, 56, 25, 1, 56, 3,
		0, FB_VMODE_NONINTERLACED
	पूर्ण, अणु
		/* 800x600 @ 56Hz */
		शून्य, 56, 800, 600, KHZ2PICOS(36000),
		128, 24, 22, 1, 72, 2,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT, FB_VMODE_NONINTERLACED
	पूर्ण, अणु
		/* 800x600 @ 60Hz */
		शून्य, 60, 800, 600, KHZ2PICOS(40000),
		88, 40, 23, 1, 128, 4,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT, FB_VMODE_NONINTERLACED
	पूर्ण, अणु
		/* 800x600 @ 72Hz */
		शून्य, 72, 800, 600, KHZ2PICOS(50000),
		64, 56, 23, 37, 120, 6,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT, FB_VMODE_NONINTERLACED
	पूर्ण, अणु
		/* 800x600 @ 75Hz */
		शून्य, 75, 800, 600, KHZ2PICOS(49500),
		160, 16, 21, 1, 80, 3,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT, FB_VMODE_NONINTERLACED
	पूर्ण, अणु
		/* 800x600 @ 85Hz */
		शून्य, 85, 800, 600, KHZ2PICOS(56250),
		152, 32, 27, 1, 64, 3,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT, FB_VMODE_NONINTERLACED
	पूर्ण, अणु
		/* 1024x768 @ 60Hz */
		शून्य, 60, 1024, 768, KHZ2PICOS(65000),
		160, 24, 29, 3, 136, 6,
		0, FB_VMODE_NONINTERLACED
	पूर्ण, अणु
		/* 1024x768 @ 70Hz */
		शून्य, 70, 1024, 768, KHZ2PICOS(75000),
		144, 24, 29, 3, 136, 6,
		0, FB_VMODE_NONINTERLACED
	पूर्ण, अणु
		/* 1024x768 @ 75Hz */
		शून्य, 75, 1024, 768, KHZ2PICOS(78750),
		176, 16, 28, 1, 96, 3,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT, FB_VMODE_NONINTERLACED
	पूर्ण, अणु
		/* 1024x768 @ 85Hz */
		शून्य, 85, 1024, 768, KHZ2PICOS(94500),
		208, 48, 36, 1, 96, 3,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT, FB_VMODE_NONINTERLACED
	पूर्ण, अणु
		/* 1152x864 @ 75Hz */
		शून्य, 75, 1152, 864, KHZ2PICOS(108000),
		256, 64, 32, 1, 128, 3,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT, FB_VMODE_NONINTERLACED
	पूर्ण, अणु
		/* 1280x960 @ 60Hz */
		शून्य, 60, 1280, 960, KHZ2PICOS(108000),
		312, 96, 36, 1, 112, 3,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT, FB_VMODE_NONINTERLACED
	पूर्ण, अणु
		/* 1280x960 @ 85Hz */
		शून्य, 85, 1280, 960, KHZ2PICOS(148500),
		224, 64, 47, 1, 160, 3,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT, FB_VMODE_NONINTERLACED
	पूर्ण, अणु
		/* 1280x1024 @ 60Hz */
		शून्य, 60, 1280, 1024, KHZ2PICOS(108000),
		248, 48, 38, 1, 112, 3,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT, FB_VMODE_NONINTERLACED
	पूर्ण, अणु
		/* 1280x1024 @ 75Hz */
		शून्य, 75, 1280, 1024, KHZ2PICOS(135000),
		248, 16, 38, 1, 144, 3,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT, FB_VMODE_NONINTERLACED
	पूर्ण, अणु
		/* 1280x1024 @ 85Hz */
		शून्य, 85, 1280, 1024, KHZ2PICOS(157500),
		224, 64, 44, 1, 160, 3,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT, FB_VMODE_NONINTERLACED
	पूर्ण, अणु
		/* 1600x1200 @ 60Hz */
		शून्य, 60, 1600, 1200, KHZ2PICOS(162000),
		304, 64, 46, 1, 192, 3,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT, FB_VMODE_NONINTERLACED
	पूर्ण, अणु
		/* 1600x1200 @ 65Hz */
		शून्य, 65, 1600, 1200, KHZ2PICOS(175500),
		304, 64, 46, 1, 192, 3,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT, FB_VMODE_NONINTERLACED
	पूर्ण, अणु
		/* 1600x1200 @ 70Hz */
		शून्य, 70, 1600, 1200, KHZ2PICOS(189000),
		304, 64, 46, 1, 192, 3,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT, FB_VMODE_NONINTERLACED
	पूर्ण, अणु
		/* 1600x1200 @ 75Hz */
		शून्य, 75, 1600, 1200, KHZ2PICOS(202500),
		304, 64, 46, 1, 192, 3,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT, FB_VMODE_NONINTERLACED
	पूर्ण, अणु
		/* 1600x1200 @ 85Hz */
		शून्य, 85, 1600, 1200, KHZ2PICOS(229500),
		304, 64, 46, 1, 192, 3,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT, FB_VMODE_NONINTERLACED
	पूर्ण, अणु
		/* 1792x1344 @ 60Hz */
		शून्य, 60, 1792, 1344, KHZ2PICOS(204750),
		328, 128, 46, 1, 200, 3,
		FB_SYNC_VERT_HIGH_ACT, FB_VMODE_NONINTERLACED
	पूर्ण, अणु
		/* 1792x1344 @ 75Hz */
		शून्य, 75, 1792, 1344, KHZ2PICOS(261000),
		352, 96, 69, 1, 216, 3,
		FB_SYNC_VERT_HIGH_ACT, FB_VMODE_NONINTERLACED
	पूर्ण, अणु
		/* 1856x1392 @ 60Hz */
		शून्य, 60, 1856, 1392, KHZ2PICOS(218250),
		352, 96, 43, 1, 224, 3,
		FB_SYNC_VERT_HIGH_ACT, FB_VMODE_NONINTERLACED
	पूर्ण, अणु
		/* 1856x1392 @ 75Hz */
		शून्य, 75, 1856, 1392, KHZ2PICOS(288000),
		352, 128, 104, 1, 224, 3,
		FB_SYNC_VERT_HIGH_ACT, FB_VMODE_NONINTERLACED
	पूर्ण, अणु
		/* 1920x1440 @ 60Hz */
		शून्य, 60, 1920, 1440, KHZ2PICOS(234000),
		344, 128, 56, 1, 208, 3,
		FB_SYNC_VERT_HIGH_ACT, FB_VMODE_NONINTERLACED
	पूर्ण, अणु
		/* 1920x1440 @ 75Hz */
		शून्य, 75, 1920, 1440, KHZ2PICOS(297000),
		352, 144, 56, 1, 224, 3,
		FB_SYNC_VERT_HIGH_ACT, FB_VMODE_NONINTERLACED
	पूर्ण,
पूर्ण;
#घोषणा NUM_TOTAL_MODES	ARRAY_SIZE(kyro_modedb)

/*
 * This needs to be kept ordered corresponding to kyro_modedb.
 */
क्रमागत अणु
	VMODE_640_350_85,
	VMODE_640_400_85,
	VMODE_720_400_85,
	VMODE_640_480_60,
	VMODE_640_480_72,
	VMODE_640_480_75,
	VMODE_640_480_85,
	VMODE_800_600_56,
	VMODE_800_600_60,
	VMODE_800_600_72,
	VMODE_800_600_75,
	VMODE_800_600_85,
	VMODE_1024_768_60,
	VMODE_1024_768_70,
	VMODE_1024_768_75,
	VMODE_1024_768_85,
	VMODE_1152_864_75,
	VMODE_1280_960_60,
	VMODE_1280_960_85,
	VMODE_1280_1024_60,
	VMODE_1280_1024_75,
	VMODE_1280_1024_85,
	VMODE_1600_1200_60,
	VMODE_1600_1200_65,
	VMODE_1600_1200_70,
	VMODE_1600_1200_75,
	VMODE_1600_1200_85,
	VMODE_1792_1344_60,
	VMODE_1792_1344_75,
	VMODE_1856_1392_60,
	VMODE_1856_1392_75,
	VMODE_1920_1440_60,
	VMODE_1920_1440_75,
पूर्ण;

/* Accessors */
अटल पूर्णांक kyro_dev_video_mode_set(काष्ठा fb_info *info)
अणु
	काष्ठा kyrofb_info *par = info->par;

	/* Turn off display */
	StopVTG(deviceInfo.pSTGReg);
	DisableRamdacOutput(deviceInfo.pSTGReg);

	/* Bring us out of VGA and पूर्णांकo Hi-Res mode, अगर not alपढ़ोy. */
	DisableVGA(deviceInfo.pSTGReg);

	अगर (InitialiseRamdac(deviceInfo.pSTGReg,
			     info->var.bits_per_pixel,
			     info->var.xres, info->var.yres,
			     par->HSP, par->VSP, &par->PIXCLK) < 0)
		वापस -EINVAL;

	SetupVTG(deviceInfo.pSTGReg, par);

	ResetOverlayRegisters(deviceInfo.pSTGReg);

	/* Turn on display in new mode */
	EnableRamdacOutput(deviceInfo.pSTGReg);
	StartVTG(deviceInfo.pSTGReg);

	deviceInfo.ulNextFreeVidMem = info->var.xres * info->var.yres *
				      info->var.bits_per_pixel;
	deviceInfo.ulOverlayOffset = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक kyro_dev_overlay_create(u32 ulWidth,
				   u32 ulHeight, पूर्णांक bLinear)
अणु
	u32 offset;
	u32 stride, uvStride;

	अगर (deviceInfo.ulOverlayOffset != 0)
		/*
		 * Can only create one overlay without resetting the card or
		 * changing display mode
		 */
		वापस -EINVAL;

	ResetOverlayRegisters(deviceInfo.pSTGReg);

	/* Overlays are addressed in multiples of 16bytes or 32bytes, so make
	 * sure the start offset is on an appropriate boundary.
	 */
	offset = deviceInfo.ulNextFreeVidMem;
	अगर ((offset & 0x1f) != 0) अणु
		offset = (offset + 32L) & 0xffffffE0L;
	पूर्ण

	अगर (CreateOverlaySurface(deviceInfo.pSTGReg, ulWidth, ulHeight,
				 bLinear, offset, &stride, &uvStride) < 0)
		वापस -EINVAL;

	deviceInfo.ulOverlayOffset = offset;
	deviceInfo.ulOverlayStride = stride;
	deviceInfo.ulOverlayUVStride = uvStride;
	deviceInfo.ulNextFreeVidMem = offset + (ulHeight * stride) + (ulHeight * 2 * uvStride);

	SetOverlayBlendMode(deviceInfo.pSTGReg, GLOBAL_ALPHA, 0xf, 0x0);

	वापस 0;
पूर्ण

अटल पूर्णांक kyro_dev_overlay_viewport_set(u32 x, u32 y, u32 ulWidth, u32 ulHeight)
अणु
	अगर (deviceInfo.ulOverlayOffset == 0)
		/* probably haven't called CreateOverlay yet */
		वापस -EINVAL;

	/* Stop Ramdac Output */
	DisableRamdacOutput(deviceInfo.pSTGReg);

	SetOverlayViewPort(deviceInfo.pSTGReg,
			   x, y, x + ulWidth - 1, y + ulHeight - 1);

	EnableOverlayPlane(deviceInfo.pSTGReg);
	/* Start Ramdac Output */
	EnableRamdacOutput(deviceInfo.pSTGReg);

	वापस 0;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ get_line_length(पूर्णांक x, पूर्णांक bpp)
अणु
	वापस (अचिन्हित दीर्घ)((((x*bpp)+31)&~31) >> 3);
पूर्ण

अटल पूर्णांक kyrofb_check_var(काष्ठा fb_var_screeninfo *var, काष्ठा fb_info *info)
अणु
	काष्ठा kyrofb_info *par = info->par;

	अगर (var->bits_per_pixel != 16 && var->bits_per_pixel != 32) अणु
		prपूर्णांकk(KERN_WARNING "kyrofb: depth not supported: %u\n", var->bits_per_pixel);
		वापस -EINVAL;
	पूर्ण

	चयन (var->bits_per_pixel) अणु
	हाल 16:
		var->red.offset = 11;
		var->red.length = 5;
		var->green.offset = 5;
		var->green.length = 6;
		var->blue.length = 5;
		अवरोध;
	हाल 32:
		var->transp.offset = 24;
		var->red.offset = 16;
		var->green.offset = 8;
		var->blue.offset = 0;

		var->red.length = 8;
		var->green.length = 8;
		var->blue.length = 8;
		var->transp.length = 8;
		अवरोध;
	पूर्ण

	/* Height/Width of picture in mm */
	var->height = var->width = -1;

	/* Timing inक्रमmation. All values are in picoseconds */

	/* par->PIXCLK is in 100Hz units. Convert to picoseconds -
	 * ensuring we करो not exceed 32 bit precision
	 */
	/*
	 * XXX: Enabling this really screws over the pixघड़ी value when we
	 * पढ़ो it back with fbset. As such, leaving this commented out appears
	 * to करो the right thing (at least क्रम now) .. bearing in mind that we
	 * have infact alपढ़ोy करोne the KHZ2PICOS conversion in both the modedb
	 * and kyro_var. -- PFM.
	 */
//	var->pixघड़ी = 1000000000 / (par->PIXCLK / 10);

	/* the header file claims we should use picoseconds
	 * - nobody अन्यथा करोes though, the all use pixels and lines
	 * of h and v sizes. Both options here.
	 */

	/*
	 * If we're being called by __fb_try_mode(), then we don't want to
	 * override any of the var settings that we've alपढ़ोy parsed
	 * from our modedb. -- PFM.
	 */
	अगर ((var->activate & FB_ACTIVATE_MASK) == FB_ACTIVATE_TEST)
		वापस 0;

	var->left_margin = par->HBP;
	var->hsync_len = par->HST;
	var->right_margin = par->HFP;

	var->upper_margin = par->VBP;
	var->vsync_len = par->VST;
	var->lower_margin = par->VFP;

	अगर (par->HSP == 1)
		var->sync |= FB_SYNC_HOR_HIGH_ACT;
	अगर (par->VSP == 1)
		var->sync |= FB_SYNC_VERT_HIGH_ACT;

	वापस 0;
पूर्ण

अटल पूर्णांक kyrofb_set_par(काष्ठा fb_info *info)
अणु
	काष्ठा kyrofb_info *par = info->par;
	अचिन्हित दीर्घ lineघड़ी;
	अचिन्हित दीर्घ frameघड़ी;

	/* Actual resolution */
	par->XRES = info->var.xres;
	par->YRES = info->var.yres;

	/* pixel depth */
	par->PIXDEPTH = info->var.bits_per_pixel;

	/* Refresh rate */
	/* समय क्रम a line in ns */
	lineघड़ी = (info->var.pixघड़ी * (info->var.xres +
				    info->var.right_margin +
				    info->var.hsync_len +
				    info->var.left_margin)) / 1000;


	/* समय क्रम a frame in ns (precision in 32bpp) */
	frameघड़ी = lineघड़ी * (info->var.yres +
				  info->var.lower_margin +
				  info->var.vsync_len +
				  info->var.upper_margin);

	/* Calculate refresh rate and horrizontal घड़ीs */
	par->VFREQ = (1000000000 + (frameघड़ी / 2)) / frameघड़ी;
	par->HCLK = (1000000000 + (lineघड़ी / 2)) / lineघड़ी;
	par->PIXCLK = ((1000000000 + (info->var.pixघड़ी / 2))
					/ info->var.pixघड़ी) * 10;

	/* calculate horizontal timings */
	par->HFP = info->var.right_margin;
	par->HST = info->var.hsync_len;
	par->HBP = info->var.left_margin;
	par->HTot = par->XRES + par->HBP + par->HST + par->HFP;

	/* calculate vertical timings */
	par->VFP = info->var.lower_margin;
	par->VST = info->var.vsync_len;
	par->VBP = info->var.upper_margin;
	par->VTot = par->YRES + par->VBP + par->VST + par->VFP;

	par->HSP = (info->var.sync & FB_SYNC_HOR_HIGH_ACT) ? 1 : 0;
	par->VSP = (info->var.sync & FB_SYNC_VERT_HIGH_ACT) ? 1 : 0;

	kyro_dev_video_mode_set(info);

	/* length of a line in bytes    */
	info->fix.line_length = get_line_length(par->XRES, par->PIXDEPTH);
	info->fix.visual = FB_VISUAL_TRUECOLOR;

	वापस 0;
पूर्ण

अटल पूर्णांक kyrofb_setcolreg(u_पूर्णांक regno, u_पूर्णांक red, u_पूर्णांक green,
			    u_पूर्णांक blue, u_पूर्णांक transp, काष्ठा fb_info *info)
अणु
	काष्ठा kyrofb_info *par = info->par;

	अगर (regno > 255)
		वापस 1;	/* Invalid रेजिस्टर */

	अगर (regno < 16) अणु
		चयन (info->var.bits_per_pixel) अणु
		हाल 16:
			par->palette[regno] =
			     (red   & 0xf800) |
			    ((green & 0xfc00) >> 5) |
			    ((blue  & 0xf800) >> 11);
			अवरोध;
		हाल 32:
			red >>= 8; green >>= 8; blue >>= 8; transp >>= 8;
			par->palette[regno] =
			    (transp << 24) | (red << 16) | (green << 8) | blue;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

#अगर_अघोषित MODULE
अटल पूर्णांक __init kyrofb_setup(अक्षर *options)
अणु
	अक्षर *this_opt;

	अगर (!options || !*options)
		वापस 0;

	जबतक ((this_opt = strsep(&options, ","))) अणु
		अगर (!*this_opt)
			जारी;
		अगर (म_भेद(this_opt, "nopan") == 0) अणु
			nopan = 1;
		पूर्ण अन्यथा अगर (म_भेद(this_opt, "nowrap") == 0) अणु
			nowrap = 1;
		पूर्ण अन्यथा अगर (म_भेद(this_opt, "nomtrr") == 0) अणु
			nomtrr = 1;
		पूर्ण अन्यथा अणु
			mode_option = this_opt;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक kyrofb_ioctl(काष्ठा fb_info *info,
			अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	overlay_create ol_create;
	overlay_viewport_set ol_viewport_set;
	व्योम __user *argp = (व्योम __user *)arg;

	चयन (cmd) अणु
	हाल KYRO_IOCTL_OVERLAY_CREATE:
		अगर (copy_from_user(&ol_create, argp, माप(overlay_create)))
			वापस -EFAULT;

		अगर (kyro_dev_overlay_create(ol_create.ulWidth,
					    ol_create.ulHeight, 0) < 0) अणु
			prपूर्णांकk(KERN_ERR "Kyro FB: failed to create overlay surface.\n");

			वापस -EINVAL;
		पूर्ण
		अवरोध;
	हाल KYRO_IOCTL_OVERLAY_VIEWPORT_SET:
		अगर (copy_from_user(&ol_viewport_set, argp,
			       माप(overlay_viewport_set)))
			वापस -EFAULT;

		अगर (kyro_dev_overlay_viewport_set(ol_viewport_set.xOrgin,
						  ol_viewport_set.yOrgin,
						  ol_viewport_set.xSize,
						  ol_viewport_set.ySize) != 0)
		अणु
			prपूर्णांकk(KERN_ERR "Kyro FB: failed to create overlay viewport.\n");
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	हाल KYRO_IOCTL_SET_VIDEO_MODE:
		अणु
			prपूर्णांकk(KERN_ERR "Kyro FB: KYRO_IOCTL_SET_VIDEO_MODE is"
				"obsolete, use the appropriate fb_ioctl()"
				"command instead.\n");
			वापस -EINVAL;
		पूर्ण
	हाल KYRO_IOCTL_UVSTRIDE:
		अगर (copy_to_user(argp, &deviceInfo.ulOverlayUVStride, माप(deviceInfo.ulOverlayUVStride)))
			वापस -EFAULT;
		अवरोध;
	हाल KYRO_IOCTL_STRIDE:
		अगर (copy_to_user(argp, &deviceInfo.ulOverlayStride, माप(deviceInfo.ulOverlayStride)))
			वापस -EFAULT;
		अवरोध;
	हाल KYRO_IOCTL_OVERLAY_OFFSET:
		अगर (copy_to_user(argp, &deviceInfo.ulOverlayOffset, माप(deviceInfo.ulOverlayOffset)))
			वापस -EFAULT;
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pci_device_id kyrofb_pci_tbl[] = अणु
	अणु PCI_VENDOR_ID_ST, PCI_DEVICE_ID_STG4000,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0 पूर्ण,
	अणु 0, पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pci, kyrofb_pci_tbl);

अटल काष्ठा pci_driver kyrofb_pci_driver = अणु
	.name		= "kyrofb",
	.id_table	= kyrofb_pci_tbl,
	.probe		= kyrofb_probe,
	.हटाओ		= kyrofb_हटाओ,
पूर्ण;

अटल स्थिर काष्ठा fb_ops kyrofb_ops = अणु
	.owner		= THIS_MODULE,
	.fb_check_var	= kyrofb_check_var,
	.fb_set_par	= kyrofb_set_par,
	.fb_setcolreg	= kyrofb_setcolreg,
	.fb_ioctl	= kyrofb_ioctl,
	.fb_fillrect	= cfb_fillrect,
	.fb_copyarea	= cfb_copyarea,
	.fb_imageblit	= cfb_imageblit,
पूर्ण;

अटल पूर्णांक kyrofb_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *ent)
अणु
	काष्ठा fb_info *info;
	काष्ठा kyrofb_info *currentpar;
	अचिन्हित दीर्घ size;
	पूर्णांक err;

	अगर ((err = pci_enable_device(pdev))) अणु
		prपूर्णांकk(KERN_WARNING "kyrofb: Can't enable pdev: %d\n", err);
		वापस err;
	पूर्ण

	info = framebuffer_alloc(माप(काष्ठा kyrofb_info), &pdev->dev);
	अगर (!info)
		वापस -ENOMEM;

	currentpar = info->par;

	kyro_fix.smem_start = pci_resource_start(pdev, 0);
	kyro_fix.smem_len   = pci_resource_len(pdev, 0);
	kyro_fix.mmio_start = pci_resource_start(pdev, 1);
	kyro_fix.mmio_len   = pci_resource_len(pdev, 1);

	currentpar->regbase = deviceInfo.pSTGReg =
		ioremap(kyro_fix.mmio_start, kyro_fix.mmio_len);
	अगर (!currentpar->regbase)
		जाओ out_मुक्त_fb;

	info->screen_base = pci_ioremap_wc_bar(pdev, 0);
	अगर (!info->screen_base)
		जाओ out_unmap_regs;

	अगर (!nomtrr)
		currentpar->wc_cookie = arch_phys_wc_add(kyro_fix.smem_start,
							 kyro_fix.smem_len);

	kyro_fix.ypanstep	= nopan ? 0 : 1;
	kyro_fix.ywrapstep	= nowrap ? 0 : 1;

	info->fbops		= &kyrofb_ops;
	info->fix		= kyro_fix;
	info->pseuकरो_palette	= currentpar->palette;
	info->flags		= FBINFO_DEFAULT;

	SetCoreClockPLL(deviceInfo.pSTGReg, pdev);

	deviceInfo.ulNextFreeVidMem = 0;
	deviceInfo.ulOverlayOffset = 0;

	/* This should give a reasonable शेष video mode */
	अगर (!fb_find_mode(&info->var, info, mode_option, kyro_modedb,
			  NUM_TOTAL_MODES, &kyro_modedb[VMODE_1024_768_75], 32))
		info->var = kyro_var;

	fb_alloc_cmap(&info->cmap, 256, 0);

	kyrofb_set_par(info);
	kyrofb_check_var(&info->var, info);

	size = get_line_length(info->var.xres_भव,
			       info->var.bits_per_pixel);
	size *= info->var.yres_भव;

	fb_स_रखो(info->screen_base, 0, size);

	अगर (रेजिस्टर_framebuffer(info) < 0)
		जाओ out_unmap;

	fb_info(info, "%s frame buffer device, at %dx%d@%d using %ldk/%ldk of VRAM\n",
		info->fix.id,
		info->var.xres, info->var.yres, info->var.bits_per_pixel,
		size >> 10, (अचिन्हित दीर्घ)info->fix.smem_len >> 10);

	pci_set_drvdata(pdev, info);

	वापस 0;

out_unmap:
	iounmap(info->screen_base);
out_unmap_regs:
	iounmap(currentpar->regbase);
out_मुक्त_fb:
	framebuffer_release(info);

	वापस -EINVAL;
पूर्ण

अटल व्योम kyrofb_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा fb_info *info = pci_get_drvdata(pdev);
	काष्ठा kyrofb_info *par = info->par;

	/* Reset the board */
	StopVTG(deviceInfo.pSTGReg);
	DisableRamdacOutput(deviceInfo.pSTGReg);

	/* Sync up the PLL */
	SetCoreClockPLL(deviceInfo.pSTGReg, pdev);

	deviceInfo.ulNextFreeVidMem = 0;
	deviceInfo.ulOverlayOffset = 0;

	iounmap(info->screen_base);
	iounmap(par->regbase);

	arch_phys_wc_del(par->wc_cookie);

	unरेजिस्टर_framebuffer(info);
	framebuffer_release(info);
पूर्ण

अटल पूर्णांक __init kyrofb_init(व्योम)
अणु
#अगर_अघोषित MODULE
	अक्षर *option = शून्य;

	अगर (fb_get_options("kyrofb", &option))
		वापस -ENODEV;
	kyrofb_setup(option);
#पूर्ण_अगर
	वापस pci_रेजिस्टर_driver(&kyrofb_pci_driver);
पूर्ण

अटल व्योम __निकास kyrofb_निकास(व्योम)
अणु
	pci_unरेजिस्टर_driver(&kyrofb_pci_driver);
पूर्ण

module_init(kyrofb_init);

#अगर_घोषित MODULE
module_निकास(kyrofb_निकास);
#पूर्ण_अगर

MODULE_AUTHOR("STMicroelectronics; Paul Mundt <lethal@linux-sh.org>");
MODULE_LICENSE("GPL");
