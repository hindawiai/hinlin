<शैली गुरु>
/*
 *  linux/drivers/video/ps3fb.c -- PS3 GPU frame buffer device
 *
 *	Copyright (C) 2006 Sony Computer Entertainment Inc.
 *	Copyright 2006, 2007 Sony Corporation
 *
 *  This file is based on :
 *
 *  linux/drivers/video/vfb.c -- Virtual frame buffer device
 *
 *	Copyright (C) 2002 James Simmons
 *
 *	Copyright (C) 1997 Geert Uytterhoeven
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
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/console.h>
#समावेश <linux/ioctl.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/मुक्तzer.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/fb.h>
#समावेश <linux/fbcon.h>
#समावेश <linux/init.h>

#समावेश <यंत्र/cell-regs.h>
#समावेश <यंत्र/lv1call.h>
#समावेश <यंत्र/ps3av.h>
#समावेश <यंत्र/ps3fb.h>
#समावेश <यंत्र/ps3.h>
#समावेश <यंत्र/ps3gpu.h>


#घोषणा DEVICE_NAME		"ps3fb"

#घोषणा GPU_CMD_BUF_SIZE			(2 * 1024 * 1024)
#घोषणा GPU_FB_START				(64 * 1024)
#घोषणा GPU_IOIF				(0x0d000000UL)
#घोषणा GPU_ALIGN_UP(x)				ALIGN((x), 64)
#घोषणा GPU_MAX_LINE_LENGTH			(65536 - 64)

#घोषणा GPU_INTR_STATUS_VSYNC_0			0	/* vsync on head A */
#घोषणा GPU_INTR_STATUS_VSYNC_1			1	/* vsync on head B */
#घोषणा GPU_INTR_STATUS_FLIP_0			3	/* flip head A */
#घोषणा GPU_INTR_STATUS_FLIP_1			4	/* flip head B */
#घोषणा GPU_INTR_STATUS_QUEUE_0			5	/* queue head A */
#घोषणा GPU_INTR_STATUS_QUEUE_1			6	/* queue head B */

#घोषणा GPU_DRIVER_INFO_VERSION			0x211

/* gpu पूर्णांकernals */
काष्ठा display_head अणु
	u64 be_समय_stamp;
	u32 status;
	u32 offset;
	u32 res1;
	u32 res2;
	u32 field;
	u32 reserved1;

	u64 res3;
	u32 raster;

	u64 vblank_count;
	u32 field_vsync;
	u32 reserved2;
पूर्ण;

काष्ठा gpu_irq अणु
	u32 irq_outlet;
	u32 status;
	u32 mask;
	u32 video_cause;
	u32 graph_cause;
	u32 user_cause;

	u32 res1;
	u64 res2;

	u32 reserved[4];
पूर्ण;

काष्ठा gpu_driver_info अणु
	u32 version_driver;
	u32 version_gpu;
	u32 memory_size;
	u32 hardware_channel;

	u32 nvcore_frequency;
	u32 memory_frequency;

	u32 reserved[1063];
	काष्ठा display_head display_head[8];
	काष्ठा gpu_irq irq;
पूर्ण;

काष्ठा ps3fb_priv अणु
	अचिन्हित पूर्णांक irq_no;

	u64 context_handle, memory_handle;
	काष्ठा gpu_driver_info *dinfo;

	u64 vblank_count;	/* frame count */
	रुको_queue_head_t रुको_vsync;

	atomic_t ext_flip;	/* on/off flip with vsync */
	atomic_t f_count;	/* fb_खोलो count */
	पूर्णांक is_blanked;
	पूर्णांक is_kicked;
	काष्ठा task_काष्ठा *task;
पूर्ण;
अटल काष्ठा ps3fb_priv ps3fb;

काष्ठा ps3fb_par अणु
	u32 pseuकरो_palette[16];
	पूर्णांक mode_id, new_mode_id;
	अचिन्हित पूर्णांक num_frames;	/* num of frame buffers */
	अचिन्हित पूर्णांक width;
	अचिन्हित पूर्णांक height;
	अचिन्हित पूर्णांक ddr_line_length;
	अचिन्हित पूर्णांक ddr_frame_size;
	अचिन्हित पूर्णांक xdr_frame_size;
	अचिन्हित पूर्णांक full_offset;	/* start of fullscreen DDR fb */
	अचिन्हित पूर्णांक fb_offset;		/* start of actual DDR fb */
	अचिन्हित पूर्णांक pan_offset;
पूर्ण;


#घोषणा FIRST_NATIVE_MODE_INDEX	10

अटल स्थिर काष्ठा fb_videomode ps3fb_modedb[] = अणु
    /* 60 Hz broadcast modes (modes "1" to "5") */
    अणु
        /* 480i */
        "480i", 60, 576, 384, 74074, 130, 89, 78, 57, 63, 6,
        FB_SYNC_BROADCAST, FB_VMODE_INTERLACED
    पूर्ण,    अणु
        /* 480p */
        "480p", 60, 576, 384, 37037, 130, 89, 78, 57, 63, 6,
        FB_SYNC_BROADCAST, FB_VMODE_NONINTERLACED
    पूर्ण,    अणु
        /* 720p */
        "720p", 60, 1124, 644, 13481, 298, 148, 57, 44, 80, 5,
        FB_SYNC_BROADCAST, FB_VMODE_NONINTERLACED
    पूर्ण,    अणु
        /* 1080i */
        "1080i", 60, 1688, 964, 13481, 264, 160, 94, 62, 88, 5,
        FB_SYNC_BROADCAST, FB_VMODE_INTERLACED
    पूर्ण,    अणु
        /* 1080p */
        "1080p", 60, 1688, 964, 6741, 264, 160, 94, 62, 88, 5,
        FB_SYNC_BROADCAST, FB_VMODE_NONINTERLACED
    पूर्ण,

    /* 50 Hz broadcast modes (modes "6" to "10") */
    अणु
        /* 576i */
        "576i", 50, 576, 460, 74074, 142, 83, 97, 63, 63, 5,
        FB_SYNC_BROADCAST, FB_VMODE_INTERLACED
    पूर्ण,    अणु
        /* 576p */
        "576p", 50, 576, 460, 37037, 142, 83, 97, 63, 63, 5,
        FB_SYNC_BROADCAST, FB_VMODE_NONINTERLACED
    पूर्ण,    अणु
        /* 720p */
        "720p", 50, 1124, 644, 13468, 298, 478, 57, 44, 80, 5,
        FB_SYNC_BROADCAST, FB_VMODE_NONINTERLACED
    पूर्ण,    अणु
        /* 1080i */
        "1080i", 50, 1688, 964, 13468, 264, 600, 94, 62, 88, 5,
        FB_SYNC_BROADCAST, FB_VMODE_INTERLACED
    पूर्ण,    अणु
        /* 1080p */
        "1080p", 50, 1688, 964, 6734, 264, 600, 94, 62, 88, 5,
        FB_SYNC_BROADCAST, FB_VMODE_NONINTERLACED
    पूर्ण,

    [FIRST_NATIVE_MODE_INDEX] =
    /* 60 Hz broadcast modes (full resolution versions of modes "1" to "5") */
    अणु
	/* 480अगर */
	"480if", 60, 720, 480, 74074, 58, 17, 30, 9, 63, 6,
	FB_SYNC_BROADCAST, FB_VMODE_INTERLACED
    पूर्ण, अणु
	/* 480pf */
	"480pf", 60, 720, 480, 37037, 58, 17, 30, 9, 63, 6,
	FB_SYNC_BROADCAST, FB_VMODE_NONINTERLACED
    पूर्ण, अणु
	/* 720pf */
	"720pf", 60, 1280, 720, 13481, 220, 70, 19, 6, 80, 5,
	FB_SYNC_BROADCAST, FB_VMODE_NONINTERLACED
    पूर्ण, अणु
	/* 1080अगर */
	"1080if", 60, 1920, 1080, 13481, 148, 44, 36, 4, 88, 5,
	FB_SYNC_BROADCAST, FB_VMODE_INTERLACED
    पूर्ण, अणु
	/* 1080pf */
	"1080pf", 60, 1920, 1080, 6741, 148, 44, 36, 4, 88, 5,
	FB_SYNC_BROADCAST, FB_VMODE_NONINTERLACED
    पूर्ण,

    /* 50 Hz broadcast modes (full resolution versions of modes "6" to "10") */
    अणु
	/* 576अगर */
	"576if", 50, 720, 576, 74074, 70, 11, 39, 5, 63, 5,
	FB_SYNC_BROADCAST, FB_VMODE_INTERLACED
    पूर्ण, अणु
	/* 576pf */
	"576pf", 50, 720, 576, 37037, 70, 11, 39, 5, 63, 5,
	FB_SYNC_BROADCAST, FB_VMODE_NONINTERLACED
    पूर्ण, अणु
	/* 720pf */
	"720pf", 50, 1280, 720, 13468, 220, 400, 19, 6, 80, 5,
	FB_SYNC_BROADCAST, FB_VMODE_NONINTERLACED
    पूर्ण, अणु
	/* 1080अगर */
	"1080if", 50, 1920, 1080, 13468, 148, 484, 36, 4, 88, 5,
	FB_SYNC_BROADCAST, FB_VMODE_INTERLACED
    पूर्ण, अणु
	/* 1080pf */
	"1080pf", 50, 1920, 1080, 6734, 148, 484, 36, 4, 88, 5,
	FB_SYNC_BROADCAST, FB_VMODE_NONINTERLACED
    पूर्ण,

    /* VESA modes (modes "11" to "13") */
    अणु
	/* WXGA */
	"wxga", 60, 1280, 768, 12924, 160, 24, 29, 3, 136, 6,
	0, FB_VMODE_NONINTERLACED,
	FB_MODE_IS_VESA
    पूर्ण, अणु
	/* SXGA */
	"sxga", 60, 1280, 1024, 9259, 248, 48, 38, 1, 112, 3,
	FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT, FB_VMODE_NONINTERLACED,
	FB_MODE_IS_VESA
    पूर्ण, अणु
	/* WUXGA */
	"wuxga", 60, 1920, 1200, 6494, 80, 48, 26, 3, 32, 6,
	FB_SYNC_HOR_HIGH_ACT, FB_VMODE_NONINTERLACED,
	FB_MODE_IS_VESA
    पूर्ण
पूर्ण;


#घोषणा HEAD_A
#घोषणा HEAD_B

#घोषणा BPP		4			/* number of bytes per pixel */


अटल पूर्णांक ps3fb_mode;
module_param(ps3fb_mode, पूर्णांक, 0);

अटल अक्षर *mode_option;

अटल पूर्णांक ps3fb_cmp_mode(स्थिर काष्ठा fb_videomode *vmode,
			  स्थिर काष्ठा fb_var_screeninfo *var)
अणु
	दीर्घ xres, yres, left_margin, right_margin, upper_margin, lower_margin;
	दीर्घ dx, dy;

	/* maximum values */
	अगर (var->xres > vmode->xres || var->yres > vmode->yres ||
	    var->pixघड़ी > vmode->pixघड़ी ||
	    var->hsync_len > vmode->hsync_len ||
	    var->vsync_len > vmode->vsync_len)
		वापस -1;

	/* progressive/पूर्णांकerlaced must match */
	अगर ((var->vmode & FB_VMODE_MASK) != vmode->vmode)
		वापस -1;

	/* minimum resolution */
	xres = max(var->xres, 1U);
	yres = max(var->yres, 1U);

	/* minimum margins */
	left_margin = max(var->left_margin, vmode->left_margin);
	right_margin = max(var->right_margin, vmode->right_margin);
	upper_margin = max(var->upper_margin, vmode->upper_margin);
	lower_margin = max(var->lower_margin, vmode->lower_margin);

	/* resolution + margins may not exceed native parameters */
	dx = ((दीर्घ)vmode->left_margin + (दीर्घ)vmode->xres +
	      (दीर्घ)vmode->right_margin) -
	     (left_margin + xres + right_margin);
	अगर (dx < 0)
		वापस -1;

	dy = ((दीर्घ)vmode->upper_margin + (दीर्घ)vmode->yres +
	      (दीर्घ)vmode->lower_margin) -
	     (upper_margin + yres + lower_margin);
	अगर (dy < 0)
		वापस -1;

	/* exact match */
	अगर (!dx && !dy)
		वापस 0;

	/* resolution dअगरference */
	वापस (vmode->xres - xres) * (vmode->yres - yres);
पूर्ण

अटल स्थिर काष्ठा fb_videomode *ps3fb_native_vmode(क्रमागत ps3av_mode_num id)
अणु
	वापस &ps3fb_modedb[FIRST_NATIVE_MODE_INDEX + id - 1];
पूर्ण

अटल स्थिर काष्ठा fb_videomode *ps3fb_vmode(पूर्णांक id)
अणु
	u32 mode = id & PS3AV_MODE_MASK;

	अगर (mode < PS3AV_MODE_480I || mode > PS3AV_MODE_WUXGA)
		वापस शून्य;

	अगर (mode <= PS3AV_MODE_1080P50 && !(id & PS3AV_MODE_FULL)) अणु
		/* Non-fullscreen broadcast mode */
		वापस &ps3fb_modedb[mode - 1];
	पूर्ण

	वापस ps3fb_native_vmode(mode);
पूर्ण

अटल अचिन्हित पूर्णांक ps3fb_find_mode(काष्ठा fb_var_screeninfo *var,
				    u32 *ddr_line_length, u32 *xdr_line_length)
अणु
	अचिन्हित पूर्णांक id, best_id;
	पूर्णांक dअगरf, best_dअगरf;
	स्थिर काष्ठा fb_videomode *vmode;
	दीर्घ gap;

	best_id = 0;
	best_dअगरf = पूर्णांक_उच्च;
	pr_debug("%s: wanted %u [%u] %u x %u [%u] %u\n", __func__,
		 var->left_margin, var->xres, var->right_margin,
		 var->upper_margin, var->yres, var->lower_margin);
	क्रम (id = PS3AV_MODE_480I; id <= PS3AV_MODE_WUXGA; id++) अणु
		vmode = ps3fb_native_vmode(id);
		dअगरf = ps3fb_cmp_mode(vmode, var);
		pr_debug("%s: mode %u: %u [%u] %u x %u [%u] %u: diff = %d\n",
			 __func__, id, vmode->left_margin, vmode->xres,
			 vmode->right_margin, vmode->upper_margin,
			 vmode->yres, vmode->lower_margin, dअगरf);
		अगर (dअगरf < 0)
			जारी;
		अगर (dअगरf < best_dअगरf) अणु
			best_id = id;
			अगर (!dअगरf)
				अवरोध;
			best_dअगरf = dअगरf;
		पूर्ण
	पूर्ण

	अगर (!best_id) अणु
		pr_debug("%s: no suitable mode found\n", __func__);
		वापस 0;
	पूर्ण

	id = best_id;
	vmode = ps3fb_native_vmode(id);

	*ddr_line_length = vmode->xres * BPP;

	/* minimum resolution */
	अगर (!var->xres)
		var->xres = 1;
	अगर (!var->yres)
		var->yres = 1;

	/* minimum भव resolution */
	अगर (var->xres_भव < var->xres)
		var->xres_भव = var->xres;
	अगर (var->yres_भव < var->yres)
		var->yres_भव = var->yres;

	/* minimum margins */
	अगर (var->left_margin < vmode->left_margin)
		var->left_margin = vmode->left_margin;
	अगर (var->right_margin < vmode->right_margin)
		var->right_margin = vmode->right_margin;
	अगर (var->upper_margin < vmode->upper_margin)
		var->upper_margin = vmode->upper_margin;
	अगर (var->lower_margin < vmode->lower_margin)
		var->lower_margin = vmode->lower_margin;

	/* extra margins */
	gap = ((दीर्घ)vmode->left_margin + (दीर्घ)vmode->xres +
	       (दीर्घ)vmode->right_margin) -
	      ((दीर्घ)var->left_margin + (दीर्घ)var->xres +
	       (दीर्घ)var->right_margin);
	अगर (gap > 0) अणु
		var->left_margin += gap/2;
		var->right_margin += (gap+1)/2;
		pr_debug("%s: rounded up H to %u [%u] %u\n", __func__,
			 var->left_margin, var->xres, var->right_margin);
	पूर्ण

	gap = ((दीर्घ)vmode->upper_margin + (दीर्घ)vmode->yres +
	       (दीर्घ)vmode->lower_margin) -
	      ((दीर्घ)var->upper_margin + (दीर्घ)var->yres +
	       (दीर्घ)var->lower_margin);
	अगर (gap > 0) अणु
		var->upper_margin += gap/2;
		var->lower_margin += (gap+1)/2;
		pr_debug("%s: rounded up V to %u [%u] %u\n", __func__,
			 var->upper_margin, var->yres, var->lower_margin);
	पूर्ण

	/* fixed fields */
	var->pixघड़ी = vmode->pixघड़ी;
	var->hsync_len = vmode->hsync_len;
	var->vsync_len = vmode->vsync_len;
	var->sync = vmode->sync;

	अगर (ps3_compare_firmware_version(1, 9, 0) >= 0) अणु
		*xdr_line_length = GPU_ALIGN_UP(var->xres_भव * BPP);
		अगर (*xdr_line_length > GPU_MAX_LINE_LENGTH)
			*xdr_line_length = GPU_MAX_LINE_LENGTH;
	पूर्ण अन्यथा
		*xdr_line_length = *ddr_line_length;

	अगर (vmode->sync & FB_SYNC_BROADCAST) अणु
		/* Full broadcast modes have the full mode bit set */
		अगर (vmode->xres == var->xres && vmode->yres == var->yres)
			id |= PS3AV_MODE_FULL;
	पूर्ण

	pr_debug("%s: mode %u\n", __func__, id);
	वापस id;
पूर्ण

अटल व्योम ps3fb_sync_image(काष्ठा device *dev, u64 frame_offset,
			     u64 dst_offset, u64 src_offset, u32 width,
			     u32 height, u32 dst_line_length,
			     u32 src_line_length)
अणु
	पूर्णांक status;
	u64 line_length;

	line_length = dst_line_length;
	अगर (src_line_length != dst_line_length)
		line_length |= (u64)src_line_length << 32;

	src_offset += GPU_FB_START;

	mutex_lock(&ps3_gpu_mutex);
	status = lv1_gpu_fb_blit(ps3fb.context_handle, dst_offset,
				 GPU_IOIF + src_offset,
				 L1GPU_FB_BLIT_WAIT_FOR_COMPLETION |
				 (width << 16) | height,
				 line_length);
	mutex_unlock(&ps3_gpu_mutex);

	अगर (status)
		dev_err(dev, "%s: lv1_gpu_fb_blit failed: %d\n", __func__,
			status);
#अगर_घोषित HEAD_A
	status = lv1_gpu_display_flip(ps3fb.context_handle, 0, frame_offset);
	अगर (status)
		dev_err(dev, "%s: lv1_gpu_display_flip failed: %d\n", __func__,
			status);
#पूर्ण_अगर
#अगर_घोषित HEAD_B
	status = lv1_gpu_display_flip(ps3fb.context_handle, 1, frame_offset);
	अगर (status)
		dev_err(dev, "%s: lv1_gpu_display_flip failed: %d\n", __func__,
			status);
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक ps3fb_sync(काष्ठा fb_info *info, u32 frame)
अणु
	काष्ठा ps3fb_par *par = info->par;
	पूर्णांक error = 0;
	u64 ddr_base, xdr_base;

	अगर (frame > par->num_frames - 1) अणु
		dev_dbg(info->device, "%s: invalid frame number (%u)\n",
			__func__, frame);
		error = -EINVAL;
		जाओ out;
	पूर्ण

	xdr_base = frame * par->xdr_frame_size;
	ddr_base = frame * par->ddr_frame_size;

	ps3fb_sync_image(info->device, ddr_base + par->full_offset,
			 ddr_base + par->fb_offset, xdr_base + par->pan_offset,
			 par->width, par->height, par->ddr_line_length,
			 info->fix.line_length);

out:
	वापस error;
पूर्ण

अटल पूर्णांक ps3fb_खोलो(काष्ठा fb_info *info, पूर्णांक user)
अणु
	atomic_inc(&ps3fb.f_count);
	वापस 0;
पूर्ण

अटल पूर्णांक ps3fb_release(काष्ठा fb_info *info, पूर्णांक user)
अणु
	अगर (atomic_dec_and_test(&ps3fb.f_count)) अणु
		अगर (atomic_पढ़ो(&ps3fb.ext_flip)) अणु
			atomic_set(&ps3fb.ext_flip, 0);
			अगर (console_trylock()) अणु
				ps3fb_sync(info, 0);	/* single buffer */
				console_unlock();
			पूर्ण
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

    /*
     *  Setting the video mode has been split पूर्णांकo two parts.
     *  First part, xxxfb_check_var, must not ग_लिखो anything
     *  to hardware, it should only verअगरy and adjust var.
     *  This means it करोesn't alter par but it करोes use hardware
     *  data from it to check this var.
     */

अटल पूर्णांक ps3fb_check_var(काष्ठा fb_var_screeninfo *var, काष्ठा fb_info *info)
अणु
	u32 xdr_line_length, ddr_line_length;
	पूर्णांक mode;

	mode = ps3fb_find_mode(var, &ddr_line_length, &xdr_line_length);
	अगर (!mode)
		वापस -EINVAL;

	/* Virtual screen */
	अगर (var->xres_भव > xdr_line_length / BPP) अणु
		dev_dbg(info->device,
			"Horizontal virtual screen size too large\n");
		वापस -EINVAL;
	पूर्ण

	अगर (var->xoffset + var->xres > var->xres_भव ||
	    var->yoffset + var->yres > var->yres_भव) अणु
		dev_dbg(info->device, "panning out-of-range\n");
		वापस -EINVAL;
	पूर्ण

	/* We support ARGB8888 only */
	अगर (var->bits_per_pixel > 32 || var->grayscale ||
	    var->red.offset > 16 || var->green.offset > 8 ||
	    var->blue.offset > 0 || var->transp.offset > 24 ||
	    var->red.length > 8 || var->green.length > 8 ||
	    var->blue.length > 8 || var->transp.length > 8 ||
	    var->red.msb_right || var->green.msb_right ||
	    var->blue.msb_right || var->transp.msb_right || var->nonstd) अणु
		dev_dbg(info->device, "We support ARGB8888 only\n");
		वापस -EINVAL;
	पूर्ण

	var->bits_per_pixel = 32;
	var->red.offset = 16;
	var->green.offset = 8;
	var->blue.offset = 0;
	var->transp.offset = 24;
	var->red.length = 8;
	var->green.length = 8;
	var->blue.length = 8;
	var->transp.length = 8;
	var->red.msb_right = 0;
	var->green.msb_right = 0;
	var->blue.msb_right = 0;
	var->transp.msb_right = 0;

	/* Rotation is not supported */
	अगर (var->rotate) अणु
		dev_dbg(info->device, "Rotation is not supported\n");
		वापस -EINVAL;
	पूर्ण

	/* Memory limit */
	अगर (var->yres_भव * xdr_line_length > info->fix.smem_len) अणु
		dev_dbg(info->device, "Not enough memory\n");
		वापस -ENOMEM;
	पूर्ण

	var->height = -1;
	var->width = -1;

	वापस 0;
पूर्ण

    /*
     * This routine actually sets the video mode.
     */

अटल पूर्णांक ps3fb_set_par(काष्ठा fb_info *info)
अणु
	काष्ठा ps3fb_par *par = info->par;
	अचिन्हित पूर्णांक mode, ddr_line_length, xdr_line_length, lines, maxlines;
	अचिन्हित पूर्णांक ddr_xoff, ddr_yoff, offset;
	स्थिर काष्ठा fb_videomode *vmode;
	u64 dst;

	mode = ps3fb_find_mode(&info->var, &ddr_line_length, &xdr_line_length);
	अगर (!mode)
		वापस -EINVAL;

	vmode = ps3fb_native_vmode(mode & PS3AV_MODE_MASK);

	info->fix.xpanstep = info->var.xres_भव > info->var.xres ? 1 : 0;
	info->fix.ypanstep = info->var.yres_भव > info->var.yres ? 1 : 0;
	info->fix.line_length = xdr_line_length;

	par->ddr_line_length = ddr_line_length;
	par->ddr_frame_size = vmode->yres * ddr_line_length;
	par->xdr_frame_size = info->var.yres_भव * xdr_line_length;

	par->num_frames = info->fix.smem_len /
			  max(par->ddr_frame_size, par->xdr_frame_size);

	/* Keep the special bits we cannot set using fb_var_screeninfo */
	par->new_mode_id = (par->new_mode_id & ~PS3AV_MODE_MASK) | mode;

	par->width = info->var.xres;
	par->height = info->var.yres;

	/* Start of the भव frame buffer (relative to fullscreen) */
	ddr_xoff = info->var.left_margin - vmode->left_margin;
	ddr_yoff = info->var.upper_margin - vmode->upper_margin;
	offset = ddr_yoff * ddr_line_length + ddr_xoff * BPP;

	par->fb_offset = GPU_ALIGN_UP(offset);
	par->full_offset = par->fb_offset - offset;
	par->pan_offset = info->var.yoffset * xdr_line_length +
			  info->var.xoffset * BPP;

	अगर (par->new_mode_id != par->mode_id) अणु
		अगर (ps3av_set_video_mode(par->new_mode_id)) अणु
			par->new_mode_id = par->mode_id;
			वापस -EINVAL;
		पूर्ण
		par->mode_id = par->new_mode_id;
	पूर्ण

	/* Clear XDR frame buffer memory */
	स_रखो((व्योम __क्रमce *)info->screen_base, 0, info->fix.smem_len);

	/* Clear DDR frame buffer memory */
	lines = vmode->yres * par->num_frames;
	अगर (par->full_offset)
		lines++;
	maxlines = info->fix.smem_len / ddr_line_length;
	क्रम (dst = 0; lines; dst += maxlines * ddr_line_length) अणु
		अचिन्हित पूर्णांक l = min(lines, maxlines);
		ps3fb_sync_image(info->device, 0, dst, 0, vmode->xres, l,
				 ddr_line_length, ddr_line_length);
		lines -= l;
	पूर्ण

	वापस 0;
पूर्ण

    /*
     *  Set a single color रेजिस्टर. The values supplied are alपढ़ोy
     *  rounded करोwn to the hardware's capabilities (according to the
     *  entries in the var काष्ठाure). Return != 0 क्रम invalid regno.
     */

अटल पूर्णांक ps3fb_setcolreg(अचिन्हित पूर्णांक regno, अचिन्हित पूर्णांक red,
			   अचिन्हित पूर्णांक green, अचिन्हित पूर्णांक blue,
			   अचिन्हित पूर्णांक transp, काष्ठा fb_info *info)
अणु
	अगर (regno >= 16)
		वापस 1;

	red >>= 8;
	green >>= 8;
	blue >>= 8;
	transp >>= 8;

	((u32 *)info->pseuकरो_palette)[regno] = transp << 24 | red << 16 |
					       green << 8 | blue;
	वापस 0;
पूर्ण

अटल पूर्णांक ps3fb_pan_display(काष्ठा fb_var_screeninfo *var,
			     काष्ठा fb_info *info)
अणु
	काष्ठा ps3fb_par *par = info->par;

	par->pan_offset = var->yoffset * info->fix.line_length +
			  var->xoffset * BPP;
	वापस 0;
पूर्ण

    /*
     *  As we have a भव frame buffer, we need our own mmap function
     */

अटल पूर्णांक ps3fb_mmap(काष्ठा fb_info *info, काष्ठा vm_area_काष्ठा *vma)
अणु
	पूर्णांक r;

	r = vm_iomap_memory(vma, info->fix.smem_start, info->fix.smem_len);

	dev_dbg(info->device, "ps3fb: mmap framebuffer P(%lx)->V(%lx)\n",
		info->fix.smem_start + (vma->vm_pgoff << PAGE_SHIFT),
		vma->vm_start);

	वापस r;
पूर्ण

    /*
     * Blank the display
     */

अटल पूर्णांक ps3fb_blank(पूर्णांक blank, काष्ठा fb_info *info)
अणु
	पूर्णांक retval;

	dev_dbg(info->device, "%s: blank:%d\n", __func__, blank);
	चयन (blank) अणु
	हाल FB_BLANK_POWERDOWN:
	हाल FB_BLANK_HSYNC_SUSPEND:
	हाल FB_BLANK_VSYNC_SUSPEND:
	हाल FB_BLANK_NORMAL:
		retval = ps3av_video_mute(1);	/* mute on */
		अगर (!retval)
			ps3fb.is_blanked = 1;
		अवरोध;

	शेष:		/* unblank */
		retval = ps3av_video_mute(0);	/* mute off */
		अगर (!retval)
			ps3fb.is_blanked = 0;
		अवरोध;
	पूर्ण
	वापस retval;
पूर्ण

अटल पूर्णांक ps3fb_get_vblank(काष्ठा fb_vblank *vblank)
अणु
	स_रखो(vblank, 0, माप(*vblank));
	vblank->flags = FB_VBLANK_HAVE_VSYNC;
	वापस 0;
पूर्ण

अटल पूर्णांक ps3fb_रुको_क्रम_vsync(u32 crtc)
अणु
	पूर्णांक ret;
	u64 count;

	count = ps3fb.vblank_count;
	ret = रुको_event_पूर्णांकerruptible_समयout(ps3fb.रुको_vsync,
					       count != ps3fb.vblank_count,
					       HZ / 10);
	अगर (!ret)
		वापस -ETIMEDOUT;

	वापस 0;
पूर्ण


    /*
     * ioctl
     */

अटल पूर्णांक ps3fb_ioctl(काष्ठा fb_info *info, अचिन्हित पूर्णांक cmd,
		       अचिन्हित दीर्घ arg)
अणु
	व्योम __user *argp = (व्योम __user *)arg;
	u32 val;
	पूर्णांक retval = -EFAULT;

	चयन (cmd) अणु
	हाल FBIOGET_VBLANK:
		अणु
			काष्ठा fb_vblank vblank;
			dev_dbg(info->device, "FBIOGET_VBLANK:\n");
			retval = ps3fb_get_vblank(&vblank);
			अगर (retval)
				अवरोध;

			अगर (copy_to_user(argp, &vblank, माप(vblank)))
				retval = -EFAULT;
			अवरोध;
		पूर्ण

	हाल FBIO_WAITFORVSYNC:
		अणु
			u32 crt;
			dev_dbg(info->device, "FBIO_WAITFORVSYNC:\n");
			अगर (get_user(crt, (u32 __user *) arg))
				अवरोध;

			retval = ps3fb_रुको_क्रम_vsync(crt);
			अवरोध;
		पूर्ण

	हाल PS3FB_IOCTL_SETMODE:
		अणु
			काष्ठा ps3fb_par *par = info->par;
			स्थिर काष्ठा fb_videomode *vmode;
			काष्ठा fb_var_screeninfo var;

			अगर (copy_from_user(&val, argp, माप(val)))
				अवरोध;

			अगर (!(val & PS3AV_MODE_MASK)) अणु
				u32 id = ps3av_get_स्वतः_mode();
				अगर (id > 0)
					val = (val & ~PS3AV_MODE_MASK) | id;
			पूर्ण
			dev_dbg(info->device, "PS3FB_IOCTL_SETMODE:%x\n", val);
			retval = -EINVAL;
			vmode = ps3fb_vmode(val);
			अगर (vmode) अणु
				var = info->var;
				fb_videomode_to_var(&var, vmode);
				console_lock();
				/* Force, in हाल only special bits changed */
				var.activate |= FB_ACTIVATE_FORCE;
				par->new_mode_id = val;
				retval = fb_set_var(info, &var);
				अगर (!retval)
					fbcon_update_vcs(info, var.activate & FB_ACTIVATE_ALL);
				console_unlock();
			पूर्ण
			अवरोध;
		पूर्ण

	हाल PS3FB_IOCTL_GETMODE:
		val = ps3av_get_mode();
		dev_dbg(info->device, "PS3FB_IOCTL_GETMODE:%x\n", val);
		अगर (!copy_to_user(argp, &val, माप(val)))
			retval = 0;
		अवरोध;

	हाल PS3FB_IOCTL_SCREENINFO:
		अणु
			काष्ठा ps3fb_par *par = info->par;
			काष्ठा ps3fb_ioctl_res res;
			dev_dbg(info->device, "PS3FB_IOCTL_SCREENINFO:\n");
			res.xres = info->fix.line_length / BPP;
			res.yres = info->var.yres_भव;
			res.xoff = (res.xres - info->var.xres) / 2;
			res.yoff = (res.yres - info->var.yres) / 2;
			res.num_frames = par->num_frames;
			अगर (!copy_to_user(argp, &res, माप(res)))
				retval = 0;
			अवरोध;
		पूर्ण

	हाल PS3FB_IOCTL_ON:
		dev_dbg(info->device, "PS3FB_IOCTL_ON:\n");
		atomic_inc(&ps3fb.ext_flip);
		retval = 0;
		अवरोध;

	हाल PS3FB_IOCTL_OFF:
		dev_dbg(info->device, "PS3FB_IOCTL_OFF:\n");
		atomic_dec_अगर_positive(&ps3fb.ext_flip);
		retval = 0;
		अवरोध;

	हाल PS3FB_IOCTL_FSEL:
		अगर (copy_from_user(&val, argp, माप(val)))
			अवरोध;

		dev_dbg(info->device, "PS3FB_IOCTL_FSEL:%d\n", val);
		console_lock();
		retval = ps3fb_sync(info, val);
		console_unlock();
		अवरोध;

	शेष:
		retval = -ENOIOCTLCMD;
		अवरोध;
	पूर्ण
	वापस retval;
पूर्ण

अटल पूर्णांक ps3fbd(व्योम *arg)
अणु
	काष्ठा fb_info *info = arg;

	set_मुक्तzable();
	जबतक (!kthपढ़ो_should_stop()) अणु
		try_to_मुक्तze();
		set_current_state(TASK_INTERRUPTIBLE);
		अगर (ps3fb.is_kicked) अणु
			ps3fb.is_kicked = 0;
			console_lock();
			ps3fb_sync(info, 0);	/* single buffer */
			console_unlock();
		पूर्ण
		schedule();
	पूर्ण
	वापस 0;
पूर्ण

अटल irqवापस_t ps3fb_vsync_पूर्णांकerrupt(पूर्णांक irq, व्योम *ptr)
अणु
	काष्ठा device *dev = ptr;
	u64 v1;
	पूर्णांक status;
	काष्ठा display_head *head = &ps3fb.dinfo->display_head[1];

	status = lv1_gpu_context_पूर्णांकr(ps3fb.context_handle, &v1);
	अगर (status) अणु
		dev_err(dev, "%s: lv1_gpu_context_intr failed: %d\n", __func__,
			status);
		वापस IRQ_NONE;
	पूर्ण

	अगर (v1 & (1 << GPU_INTR_STATUS_VSYNC_1)) अणु
		/* VSYNC */
		ps3fb.vblank_count = head->vblank_count;
		अगर (ps3fb.task && !ps3fb.is_blanked &&
		    !atomic_पढ़ो(&ps3fb.ext_flip)) अणु
			ps3fb.is_kicked = 1;
			wake_up_process(ps3fb.task);
		पूर्ण
		wake_up_पूर्णांकerruptible(&ps3fb.रुको_vsync);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण


अटल स्थिर काष्ठा fb_ops ps3fb_ops = अणु
	.fb_खोलो	= ps3fb_खोलो,
	.fb_release	= ps3fb_release,
	.fb_पढ़ो        = fb_sys_पढ़ो,
	.fb_ग_लिखो       = fb_sys_ग_लिखो,
	.fb_check_var	= ps3fb_check_var,
	.fb_set_par	= ps3fb_set_par,
	.fb_setcolreg	= ps3fb_setcolreg,
	.fb_pan_display	= ps3fb_pan_display,
	.fb_fillrect	= sys_fillrect,
	.fb_copyarea	= sys_copyarea,
	.fb_imageblit	= sys_imageblit,
	.fb_mmap	= ps3fb_mmap,
	.fb_blank	= ps3fb_blank,
	.fb_ioctl	= ps3fb_ioctl,
	.fb_compat_ioctl = ps3fb_ioctl
पूर्ण;

अटल स्थिर काष्ठा fb_fix_screeninfo ps3fb_fix = अणु
	.id =		DEVICE_NAME,
	.type =		FB_TYPE_PACKED_PIXELS,
	.visual =	FB_VISUAL_TRUECOLOR,
	.accel =	FB_ACCEL_NONE,
पूर्ण;

अटल पूर्णांक ps3fb_probe(काष्ठा ps3_प्रणाली_bus_device *dev)
अणु
	काष्ठा fb_info *info;
	काष्ठा ps3fb_par *par;
	पूर्णांक retval;
	u64 ddr_lpar = 0;
	u64 lpar_dma_control = 0;
	u64 lpar_driver_info = 0;
	u64 lpar_reports = 0;
	u64 lpar_reports_size = 0;
	u64 xdr_lpar;
	काष्ठा gpu_driver_info *dinfo;
	व्योम *fb_start;
	पूर्णांक status;
	काष्ठा task_काष्ठा *task;
	अचिन्हित दीर्घ max_ps3fb_size;

	अगर (ps3fb_videomemory.size < GPU_CMD_BUF_SIZE) अणु
		dev_err(&dev->core, "%s: Not enough video memory\n", __func__);
		वापस -ENOMEM;
	पूर्ण

	retval = ps3_खोलो_hv_device(dev);
	अगर (retval) अणु
		dev_err(&dev->core, "%s: ps3_open_hv_device failed\n",
			__func__);
		जाओ err;
	पूर्ण

	अगर (!ps3fb_mode)
		ps3fb_mode = ps3av_get_mode();
	dev_dbg(&dev->core, "ps3fb_mode: %d\n", ps3fb_mode);

	atomic_set(&ps3fb.f_count, -1);	/* fbcon खोलोs ps3fb */
	atomic_set(&ps3fb.ext_flip, 0);	/* क्रम flip with vsync */
	init_रुकोqueue_head(&ps3fb.रुको_vsync);

#अगर_घोषित HEAD_A
	status = lv1_gpu_display_sync(0x0, 0, L1GPU_DISPLAY_SYNC_VSYNC);
	अगर (status) अणु
		dev_err(&dev->core, "%s: lv1_gpu_display_sync failed: %d\n",
			__func__, status);
		retval = -ENODEV;
		जाओ err_बंद_device;
	पूर्ण
#पूर्ण_अगर
#अगर_घोषित HEAD_B
	status = lv1_gpu_display_sync(0x0, 1, L1GPU_DISPLAY_SYNC_VSYNC);
	अगर (status) अणु
		dev_err(&dev->core, "%s: lv1_gpu_display_sync failed: %d\n",
			__func__, status);
		retval = -ENODEV;
		जाओ err_बंद_device;
	पूर्ण
#पूर्ण_अगर

	max_ps3fb_size = ALIGN(GPU_IOIF, 256*1024*1024) - GPU_IOIF;
	अगर (ps3fb_videomemory.size > max_ps3fb_size) अणु
		dev_info(&dev->core, "Limiting ps3fb mem size to %lu bytes\n",
			 max_ps3fb_size);
		ps3fb_videomemory.size = max_ps3fb_size;
	पूर्ण

	/* get gpu context handle */
	status = lv1_gpu_memory_allocate(ps3fb_videomemory.size, 0, 0, 0, 0,
					 &ps3fb.memory_handle, &ddr_lpar);
	अगर (status) अणु
		dev_err(&dev->core, "%s: lv1_gpu_memory_allocate failed: %d\n",
			__func__, status);
		retval = -ENOMEM;
		जाओ err_बंद_device;
	पूर्ण
	dev_dbg(&dev->core, "ddr:lpar:0x%llx\n", ddr_lpar);

	status = lv1_gpu_context_allocate(ps3fb.memory_handle, 0,
					  &ps3fb.context_handle,
					  &lpar_dma_control, &lpar_driver_info,
					  &lpar_reports, &lpar_reports_size);
	अगर (status) अणु
		dev_err(&dev->core,
			"%s: lv1_gpu_context_allocate failed: %d\n", __func__,
			status);
		retval = -ENOMEM;
		जाओ err_gpu_memory_मुक्त;
	पूर्ण

	/* vsync पूर्णांकerrupt */
	dinfo = (व्योम __क्रमce *)ioremap(lpar_driver_info, 128 * 1024);
	अगर (!dinfo) अणु
		dev_err(&dev->core, "%s: ioremap failed\n", __func__);
		retval = -ENOMEM;
		जाओ err_gpu_context_मुक्त;
	पूर्ण

	ps3fb.dinfo = dinfo;
	dev_dbg(&dev->core, "version_driver:%x\n", dinfo->version_driver);
	dev_dbg(&dev->core, "irq outlet:%x\n", dinfo->irq.irq_outlet);
	dev_dbg(&dev->core, "version_gpu: %x memory_size: %x ch: %x "
		"core_freq: %d mem_freq:%d\n", dinfo->version_gpu,
		dinfo->memory_size, dinfo->hardware_channel,
		dinfo->nvcore_frequency/1000000,
		dinfo->memory_frequency/1000000);

	अगर (dinfo->version_driver != GPU_DRIVER_INFO_VERSION) अणु
		dev_err(&dev->core, "%s: version_driver err:%x\n", __func__,
			dinfo->version_driver);
		retval = -EINVAL;
		जाओ err_iounmap_dinfo;
	पूर्ण

	retval = ps3_irq_plug_setup(PS3_BINDING_CPU_ANY, dinfo->irq.irq_outlet,
				    &ps3fb.irq_no);
	अगर (retval) अणु
		dev_err(&dev->core, "%s: ps3_alloc_irq failed %d\n", __func__,
			retval);
		जाओ err_iounmap_dinfo;
	पूर्ण

	retval = request_irq(ps3fb.irq_no, ps3fb_vsync_पूर्णांकerrupt,
			     0, DEVICE_NAME, &dev->core);
	अगर (retval) अणु
		dev_err(&dev->core, "%s: request_irq failed %d\n", __func__,
			retval);
		जाओ err_destroy_plug;
	पूर्ण

	dinfo->irq.mask = (1 << GPU_INTR_STATUS_VSYNC_1) |
			  (1 << GPU_INTR_STATUS_FLIP_1);

	/* Clear memory to prevent kernel info leakage पूर्णांकo userspace */
	स_रखो(ps3fb_videomemory.address, 0, ps3fb_videomemory.size);

	xdr_lpar = ps3_mm_phys_to_lpar(__pa(ps3fb_videomemory.address));

	status = lv1_gpu_context_iomap(ps3fb.context_handle, GPU_IOIF,
				       xdr_lpar, ps3fb_videomemory.size,
				       CBE_IOPTE_PP_W | CBE_IOPTE_PP_R |
				       CBE_IOPTE_M);
	अगर (status) अणु
		dev_err(&dev->core, "%s: lv1_gpu_context_iomap failed: %d\n",
			__func__, status);
		retval =  -ENXIO;
		जाओ err_मुक्त_irq;
	पूर्ण

	dev_dbg(&dev->core, "video:%p ioif:%lx lpar:%llx size:%lx\n",
		ps3fb_videomemory.address, GPU_IOIF, xdr_lpar,
		ps3fb_videomemory.size);

	status = lv1_gpu_fb_setup(ps3fb.context_handle, xdr_lpar,
				  GPU_CMD_BUF_SIZE, GPU_IOIF);
	अगर (status) अणु
		dev_err(&dev->core, "%s: lv1_gpu_fb_setup failed: %d\n",
			__func__, status);
		retval = -ENXIO;
		जाओ err_context_unmap;
	पूर्ण

	info = framebuffer_alloc(माप(काष्ठा ps3fb_par), &dev->core);
	अगर (!info) अणु
		retval = -ENOMEM;
		जाओ err_context_fb_बंद;
	पूर्ण

	par = info->par;
	par->mode_id = ~ps3fb_mode;	/* != ps3fb_mode, to trigger change */
	par->new_mode_id = ps3fb_mode;
	par->num_frames = 1;

	info->fbops = &ps3fb_ops;
	info->fix = ps3fb_fix;

	/*
	 * The GPU command buffer is at the start of video memory
	 * As we करोn't use the full command buffer, we can put the actual
	 * frame buffer at offset GPU_FB_START and save some precious XDR
	 * memory
	 */
	fb_start = ps3fb_videomemory.address + GPU_FB_START;
	info->screen_base = (अक्षर __क्रमce __iomem *)fb_start;
	info->fix.smem_start = __pa(fb_start);
	info->fix.smem_len = ps3fb_videomemory.size - GPU_FB_START;

	info->pseuकरो_palette = par->pseuकरो_palette;
	info->flags = FBINFO_DEFAULT | FBINFO_READS_FAST |
		      FBINFO_HWACCEL_XPAN | FBINFO_HWACCEL_YPAN;

	retval = fb_alloc_cmap(&info->cmap, 256, 0);
	अगर (retval < 0)
		जाओ err_framebuffer_release;

	अगर (!fb_find_mode(&info->var, info, mode_option, ps3fb_modedb,
			  ARRAY_SIZE(ps3fb_modedb),
			  ps3fb_vmode(par->new_mode_id), 32)) अणु
		retval = -EINVAL;
		जाओ err_fb_dealloc;
	पूर्ण

	fb_videomode_to_modelist(ps3fb_modedb, ARRAY_SIZE(ps3fb_modedb),
				 &info->modelist);

	retval = रेजिस्टर_framebuffer(info);
	अगर (retval < 0)
		जाओ err_fb_dealloc;

	ps3_प्रणाली_bus_set_drvdata(dev, info);

	dev_info(info->device, "%s %s, using %u KiB of video memory\n",
		 dev_driver_string(info->dev), dev_name(info->dev),
		 info->fix.smem_len >> 10);

	task = kthपढ़ो_run(ps3fbd, info, DEVICE_NAME);
	अगर (IS_ERR(task)) अणु
		retval = PTR_ERR(task);
		जाओ err_unरेजिस्टर_framebuffer;
	पूर्ण

	ps3fb.task = task;

	वापस 0;

err_unरेजिस्टर_framebuffer:
	unरेजिस्टर_framebuffer(info);
err_fb_dealloc:
	fb_dealloc_cmap(&info->cmap);
err_framebuffer_release:
	framebuffer_release(info);
err_context_fb_बंद:
	lv1_gpu_fb_बंद(ps3fb.context_handle);
err_context_unmap:
	lv1_gpu_context_iomap(ps3fb.context_handle, GPU_IOIF, xdr_lpar,
			      ps3fb_videomemory.size, CBE_IOPTE_M);
err_मुक्त_irq:
	मुक्त_irq(ps3fb.irq_no, &dev->core);
err_destroy_plug:
	ps3_irq_plug_destroy(ps3fb.irq_no);
err_iounmap_dinfo:
	iounmap((u8 __क्रमce __iomem *)ps3fb.dinfo);
err_gpu_context_मुक्त:
	lv1_gpu_context_मुक्त(ps3fb.context_handle);
err_gpu_memory_मुक्त:
	lv1_gpu_memory_मुक्त(ps3fb.memory_handle);
err_बंद_device:
	ps3_बंद_hv_device(dev);
err:
	वापस retval;
पूर्ण

अटल व्योम ps3fb_shutकरोwn(काष्ठा ps3_प्रणाली_bus_device *dev)
अणु
	काष्ठा fb_info *info = ps3_प्रणाली_bus_get_drvdata(dev);
	u64 xdr_lpar = ps3_mm_phys_to_lpar(__pa(ps3fb_videomemory.address));

	dev_dbg(&dev->core, " -> %s:%d\n", __func__, __LINE__);

	atomic_inc(&ps3fb.ext_flip);	/* flip off */
	ps3fb.dinfo->irq.mask = 0;

	अगर (ps3fb.task) अणु
		काष्ठा task_काष्ठा *task = ps3fb.task;
		ps3fb.task = शून्य;
		kthपढ़ो_stop(task);
	पूर्ण
	अगर (ps3fb.irq_no) अणु
		मुक्त_irq(ps3fb.irq_no, &dev->core);
		ps3_irq_plug_destroy(ps3fb.irq_no);
	पूर्ण
	अगर (info) अणु
		unरेजिस्टर_framebuffer(info);
		fb_dealloc_cmap(&info->cmap);
		framebuffer_release(info);
		ps3_प्रणाली_bus_set_drvdata(dev, शून्य);
	पूर्ण
	iounmap((u8 __क्रमce __iomem *)ps3fb.dinfo);
	lv1_gpu_fb_बंद(ps3fb.context_handle);
	lv1_gpu_context_iomap(ps3fb.context_handle, GPU_IOIF, xdr_lpar,
			      ps3fb_videomemory.size, CBE_IOPTE_M);
	lv1_gpu_context_मुक्त(ps3fb.context_handle);
	lv1_gpu_memory_मुक्त(ps3fb.memory_handle);
	ps3_बंद_hv_device(dev);
	dev_dbg(&dev->core, " <- %s:%d\n", __func__, __LINE__);
पूर्ण

अटल काष्ठा ps3_प्रणाली_bus_driver ps3fb_driver = अणु
	.match_id	= PS3_MATCH_ID_GPU,
	.match_sub_id	= PS3_MATCH_SUB_ID_GPU_FB,
	.core.name	= DEVICE_NAME,
	.core.owner	= THIS_MODULE,
	.probe		= ps3fb_probe,
	.हटाओ		= ps3fb_shutकरोwn,
	.shutकरोwn	= ps3fb_shutकरोwn,
पूर्ण;

अटल पूर्णांक __init ps3fb_setup(व्योम)
अणु
	अक्षर *options;

#अगर_घोषित MODULE
	वापस 0;
#पूर्ण_अगर

	अगर (fb_get_options(DEVICE_NAME, &options))
		वापस -ENXIO;

	अगर (!options || !*options)
		वापस 0;

	जबतक (1) अणु
		अक्षर *this_opt = strsep(&options, ",");

		अगर (!this_opt)
			अवरोध;
		अगर (!*this_opt)
			जारी;
		अगर (!म_भेदन(this_opt, "mode:", 5))
			ps3fb_mode = simple_म_से_अदीर्घ(this_opt + 5, शून्य, 0);
		अन्यथा
			mode_option = this_opt;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक __init ps3fb_init(व्योम)
अणु
	अगर (!ps3fb_videomemory.address ||  ps3fb_setup())
		वापस -ENXIO;

	वापस ps3_प्रणाली_bus_driver_रेजिस्टर(&ps3fb_driver);
पूर्ण

अटल व्योम __निकास ps3fb_निकास(व्योम)
अणु
	pr_debug(" -> %s:%d\n", __func__, __LINE__);
	ps3_प्रणाली_bus_driver_unरेजिस्टर(&ps3fb_driver);
	pr_debug(" <- %s:%d\n", __func__, __LINE__);
पूर्ण

module_init(ps3fb_init);
module_निकास(ps3fb_निकास);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("PS3 GPU Frame Buffer Driver");
MODULE_AUTHOR("Sony Computer Entertainment Inc.");
MODULE_ALIAS(PS3_MODULE_ALIAS_GPU_FB);
