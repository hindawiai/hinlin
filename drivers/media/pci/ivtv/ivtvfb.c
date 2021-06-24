<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
    On Screen Display cx23415 Framebuffer driver

    This module presents the cx23415 OSD (onscreen display) framebuffer memory
    as a standard Linux /dev/fb style framebuffer device. The framebuffer has
    support क्रम 8, 16 & 32 bpp packed pixel क्रमmats with alpha channel. In 16bpp
    mode, there is a choice of a three color depths (12, 15 or 16 bits), but no
    local alpha. The colorspace is selectable between rgb & yuv.
    Depending on the TV standard configured in the ivtv module at load समय,
    the initial resolution is either 640x400 (NTSC) or 640x480 (PAL) at 8bpp.
    Video timings are locked to ensure a vertical refresh rate of 50Hz (PAL)
    or 59.94 (NTSC)

    Copyright (c) 2003 Matt T. Yourst <yourst@yourst.com>

    Derived from drivers/video/vesafb.c
    Portions (c) 1998 Gerd Knorr <kraxel@goldbach.in-berlin.de>

    2.6 kernel port:
    Copyright (C) 2004 Matthias Badaire

    Copyright (C) 2004  Chris Kennedy <c@groovy.org>

    Copyright (C) 2006  Ian Armstrong <ian@iarmst.demon.co.uk>

 */

#समावेश "ivtv-driver.h"
#समावेश "ivtv-cards.h"
#समावेश "ivtv-i2c.h"
#समावेश "ivtv-udma.h"
#समावेश "ivtv-mailbox.h"
#समावेश "ivtv-firmware.h"

#समावेश <linux/fb.h>
#समावेश <linux/ivtvfb.h>

#अगर_घोषित CONFIG_X86_64
#समावेश <यंत्र/memtype.h>
#पूर्ण_अगर

/* card parameters */
अटल पूर्णांक ivtvfb_card_id = -1;
अटल पूर्णांक ivtvfb_debug = 0;
अटल bool ivtvfb_क्रमce_pat = IS_ENABLED(CONFIG_VIDEO_FB_IVTV_FORCE_PAT);
अटल bool osd_laced;
अटल पूर्णांक osd_depth;
अटल पूर्णांक osd_upper;
अटल पूर्णांक osd_left;
अटल पूर्णांक osd_yres;
अटल पूर्णांक osd_xres;

module_param(ivtvfb_card_id, पूर्णांक, 0444);
module_param_named(debug,ivtvfb_debug, पूर्णांक, 0644);
module_param_named(क्रमce_pat, ivtvfb_क्रमce_pat, bool, 0644);
module_param(osd_laced, bool, 0444);
module_param(osd_depth, पूर्णांक, 0444);
module_param(osd_upper, पूर्णांक, 0444);
module_param(osd_left, पूर्णांक, 0444);
module_param(osd_yres, पूर्णांक, 0444);
module_param(osd_xres, पूर्णांक, 0444);

MODULE_PARM_DESC(ivtvfb_card_id,
		 "Only use framebuffer of the specified ivtv card (0-31)\n"
		 "\t\t\tdefault -1: initialize all available framebuffers");

MODULE_PARM_DESC(debug,
		 "Debug level (bitmask). Default: errors only\n"
		 "\t\t\t(debug = 3 gives full debugging)");

MODULE_PARM_DESC(क्रमce_pat,
		 "Force initialization on x86 PAT-enabled systems (bool).\n");

/* Why upper, left, xres, yres, depth, laced ? To match terminology used
   by fbset.
   Why start at 1 क्रम left & upper coordinate ? Because X करोesn't allow 0 */

MODULE_PARM_DESC(osd_laced,
		 "Interlaced mode\n"
		 "\t\t\t0=off\n"
		 "\t\t\t1=on\n"
		 "\t\t\tdefault off");

MODULE_PARM_DESC(osd_depth,
		 "Bits per pixel - 8, 16, 32\n"
		 "\t\t\tdefault 8");

MODULE_PARM_DESC(osd_upper,
		 "Vertical start position\n"
		 "\t\t\tdefault 0 (Centered)");

MODULE_PARM_DESC(osd_left,
		 "Horizontal start position\n"
		 "\t\t\tdefault 0 (Centered)");

MODULE_PARM_DESC(osd_yres,
		 "Display height\n"
		 "\t\t\tdefault 480 (PAL)\n"
		 "\t\t\t        400 (NTSC)");

MODULE_PARM_DESC(osd_xres,
		 "Display width\n"
		 "\t\t\tdefault 640");

MODULE_AUTHOR("Kevin Thayer, Chris Kennedy, Hans Verkuil, John Harvey, Ian Armstrong");
MODULE_LICENSE("GPL");

/* --------------------------------------------------------------------- */

#घोषणा IVTVFB_DBGFLG_WARN  (1 << 0)
#घोषणा IVTVFB_DBGFLG_INFO  (1 << 1)

#घोषणा IVTVFB_DEBUG(x, type, fmt, args...) \
	करो अणु \
		अगर ((x) & ivtvfb_debug) \
			prपूर्णांकk(KERN_INFO "ivtvfb%d " type ": " fmt, itv->instance , ## args); \
	पूर्ण जबतक (0)
#घोषणा IVTVFB_DEBUG_WARN(fmt, args...)  IVTVFB_DEBUG(IVTVFB_DBGFLG_WARN, "warning", fmt , ## args)
#घोषणा IVTVFB_DEBUG_INFO(fmt, args...)  IVTVFB_DEBUG(IVTVFB_DBGFLG_INFO, "info", fmt , ## args)

/* Standard kernel messages */
#घोषणा IVTVFB_ERR(fmt, args...)   prपूर्णांकk(KERN_ERR  "ivtvfb%d: " fmt, itv->instance , ## args)
#घोषणा IVTVFB_WARN(fmt, args...)  prपूर्णांकk(KERN_WARNING  "ivtvfb%d: " fmt, itv->instance , ## args)
#घोषणा IVTVFB_INFO(fmt, args...)  prपूर्णांकk(KERN_INFO "ivtvfb%d: " fmt, itv->instance , ## args)

/* --------------------------------------------------------------------- */

#घोषणा IVTV_OSD_MAX_WIDTH  720
#घोषणा IVTV_OSD_MAX_HEIGHT 576

#घोषणा IVTV_OSD_BPP_8      0x00
#घोषणा IVTV_OSD_BPP_16_444 0x03
#घोषणा IVTV_OSD_BPP_16_555 0x02
#घोषणा IVTV_OSD_BPP_16_565 0x01
#घोषणा IVTV_OSD_BPP_32     0x04

काष्ठा osd_info अणु
	/* Physical base address */
	अचिन्हित दीर्घ video_pbase;
	/* Relative base address (relative to start of decoder memory) */
	u32 video_rbase;
	/* Mapped base address */
	अस्थिर अक्षर __iomem *video_vbase;
	/* Buffer size */
	u32 video_buffer_size;

	/* video_base rounded करोwn as required by hardware MTRRs */
	अचिन्हित दीर्घ fb_start_aligned_physaddr;
	/* video_base rounded up as required by hardware MTRRs */
	अचिन्हित दीर्घ fb_end_aligned_physaddr;
	पूर्णांक wc_cookie;

	/* Store the buffer offset */
	पूर्णांक set_osd_coords_x;
	पूर्णांक set_osd_coords_y;

	/* Current dimensions (NOT VISIBLE SIZE!) */
	पूर्णांक display_width;
	पूर्णांक display_height;
	पूर्णांक display_byte_stride;

	/* Current bits per pixel */
	पूर्णांक bits_per_pixel;
	पूर्णांक bytes_per_pixel;

	/* Frame buffer stuff */
	काष्ठा fb_info ivtvfb_info;
	काष्ठा fb_var_screeninfo ivtvfb_defined;
	काष्ठा fb_fix_screeninfo ivtvfb_fix;

	/* Used क्रम a warm start */
	काष्ठा fb_var_screeninfo fbvar_cur;
	पूर्णांक blank_cur;
	u32 palette_cur[256];
	u32 pan_cur;
पूर्ण;

काष्ठा ivtv_osd_coords अणु
	अचिन्हित दीर्घ offset;
	अचिन्हित दीर्घ max_offset;
	पूर्णांक pixel_stride;
	पूर्णांक lines;
	पूर्णांक x;
	पूर्णांक y;
पूर्ण;

/* --------------------------------------------------------------------- */

/* ivtv API calls क्रम framebuffer related support */

अटल पूर्णांक ivtvfb_get_framebuffer(काष्ठा ivtv *itv, u32 *fbbase,
				       u32 *fblength)
अणु
	u32 data[CX2341X_MBOX_MAX_DATA];
	पूर्णांक rc;

	ivtv_firmware_check(itv, "ivtvfb_get_framebuffer");
	rc = ivtv_vapi_result(itv, data, CX2341X_OSD_GET_FRAMEBUFFER, 0);
	*fbbase = data[0];
	*fblength = data[1];
	वापस rc;
पूर्ण

अटल पूर्णांक ivtvfb_get_osd_coords(काष्ठा ivtv *itv,
				      काष्ठा ivtv_osd_coords *osd)
अणु
	काष्ठा osd_info *oi = itv->osd_info;
	u32 data[CX2341X_MBOX_MAX_DATA];

	ivtv_vapi_result(itv, data, CX2341X_OSD_GET_OSD_COORDS, 0);

	osd->offset = data[0] - oi->video_rbase;
	osd->max_offset = oi->display_width * oi->display_height * 4;
	osd->pixel_stride = data[1];
	osd->lines = data[2];
	osd->x = data[3];
	osd->y = data[4];
	वापस 0;
पूर्ण

अटल पूर्णांक ivtvfb_set_osd_coords(काष्ठा ivtv *itv, स्थिर काष्ठा ivtv_osd_coords *osd)
अणु
	काष्ठा osd_info *oi = itv->osd_info;

	oi->display_width = osd->pixel_stride;
	oi->display_byte_stride = osd->pixel_stride * oi->bytes_per_pixel;
	oi->set_osd_coords_x += osd->x;
	oi->set_osd_coords_y = osd->y;

	वापस ivtv_vapi(itv, CX2341X_OSD_SET_OSD_COORDS, 5,
			osd->offset + oi->video_rbase,
			osd->pixel_stride,
			osd->lines, osd->x, osd->y);
पूर्ण

अटल पूर्णांक ivtvfb_set_display_winकरोw(काष्ठा ivtv *itv, काष्ठा v4l2_rect *ivtv_winकरोw)
अणु
	पूर्णांक osd_height_limit = itv->is_out_50hz ? 576 : 480;

	/* Only fail अगर resolution too high, otherwise fudge the start coords. */
	अगर ((ivtv_winकरोw->height > osd_height_limit) || (ivtv_winकरोw->width > IVTV_OSD_MAX_WIDTH))
		वापस -EINVAL;

	/* Ensure we करोn't exceed display limits */
	अगर (ivtv_winकरोw->top + ivtv_winकरोw->height > osd_height_limit) अणु
		IVTVFB_DEBUG_WARN("ivtv_ioctl_fb_set_display_window - Invalid height setting (%d, %d)\n",
			ivtv_winकरोw->top, ivtv_winकरोw->height);
		ivtv_winकरोw->top = osd_height_limit - ivtv_winकरोw->height;
	पूर्ण

	अगर (ivtv_winकरोw->left + ivtv_winकरोw->width > IVTV_OSD_MAX_WIDTH) अणु
		IVTVFB_DEBUG_WARN("ivtv_ioctl_fb_set_display_window - Invalid width setting (%d, %d)\n",
			ivtv_winकरोw->left, ivtv_winकरोw->width);
		ivtv_winकरोw->left = IVTV_OSD_MAX_WIDTH - ivtv_winकरोw->width;
	पूर्ण

	/* Set the OSD origin */
	ग_लिखो_reg((ivtv_winकरोw->top << 16) | ivtv_winकरोw->left, 0x02a04);

	/* How much to display */
	ग_लिखो_reg(((ivtv_winकरोw->top+ivtv_winकरोw->height) << 16) | (ivtv_winकरोw->left+ivtv_winकरोw->width), 0x02a08);

	/* Pass this info back the yuv handler */
	itv->yuv_info.osd_vis_w = ivtv_winकरोw->width;
	itv->yuv_info.osd_vis_h = ivtv_winकरोw->height;
	itv->yuv_info.osd_x_offset = ivtv_winकरोw->left;
	itv->yuv_info.osd_y_offset = ivtv_winकरोw->top;

	वापस 0;
पूर्ण

अटल पूर्णांक ivtvfb_prep_dec_dma_to_device(काष्ठा ivtv *itv,
				  अचिन्हित दीर्घ ivtv_dest_addr, व्योम __user *userbuf,
				  पूर्णांक size_in_bytes)
अणु
	DEFINE_WAIT(रुको);
	पूर्णांक got_sig = 0;

	mutex_lock(&itv->udma.lock);
	/* Map User DMA */
	अगर (ivtv_udma_setup(itv, ivtv_dest_addr, userbuf, size_in_bytes) <= 0) अणु
		mutex_unlock(&itv->udma.lock);
		IVTVFB_WARN("ivtvfb_prep_dec_dma_to_device, Error with pin_user_pages: %d bytes, %d pages returned\n",
			       size_in_bytes, itv->udma.page_count);

		/* pin_user_pages must have failed completely */
		वापस -EIO;
	पूर्ण

	IVTVFB_DEBUG_INFO("ivtvfb_prep_dec_dma_to_device, %d bytes, %d pages\n",
		       size_in_bytes, itv->udma.page_count);

	ivtv_udma_prepare(itv);
	prepare_to_रुको(&itv->dma_रुकोq, &रुको, TASK_INTERRUPTIBLE);
	/* अगर no UDMA is pending and no UDMA is in progress, then the DMA
	   is finished */
	जबतक (test_bit(IVTV_F_I_UDMA_PENDING, &itv->i_flags) ||
	       test_bit(IVTV_F_I_UDMA, &itv->i_flags)) अणु
		/* करोn't पूर्णांकerrupt अगर the DMA is in progress but अवरोध off
		   a still pending DMA. */
		got_sig = संकेत_pending(current);
		अगर (got_sig && test_and_clear_bit(IVTV_F_I_UDMA_PENDING, &itv->i_flags))
			अवरोध;
		got_sig = 0;
		schedule();
	पूर्ण
	finish_रुको(&itv->dma_रुकोq, &रुको);

	/* Unmap Last DMA Xfer */
	ivtv_udma_unmap(itv);
	mutex_unlock(&itv->udma.lock);
	अगर (got_sig) अणु
		IVTV_DEBUG_INFO("User stopped OSD\n");
		वापस -EINTR;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ivtvfb_prep_frame(काष्ठा ivtv *itv, पूर्णांक cmd, व्योम __user *source,
			      अचिन्हित दीर्घ dest_offset, पूर्णांक count)
अणु
	DEFINE_WAIT(रुको);
	काष्ठा osd_info *oi = itv->osd_info;

	/* Nothing to करो */
	अगर (count == 0) अणु
		IVTVFB_DEBUG_WARN("ivtvfb_prep_frame: Nothing to do. count = 0\n");
		वापस -EINVAL;
	पूर्ण

	/* Check Total FB Size */
	अगर ((dest_offset + count) > oi->video_buffer_size) अणु
		IVTVFB_WARN("ivtvfb_prep_frame: Overflowing the framebuffer %ld, only %d available\n",
			dest_offset + count, oi->video_buffer_size);
		वापस -E2BIG;
	पूर्ण

	/* Not fatal, but will have undesirable results */
	अगर ((अचिन्हित दीर्घ)source & 3)
		IVTVFB_WARN("ivtvfb_prep_frame: Source address not 32 bit aligned (%p)\n",
			    source);

	अगर (dest_offset & 3)
		IVTVFB_WARN("ivtvfb_prep_frame: Dest offset not 32 bit aligned (%ld)\n", dest_offset);

	अगर (count & 3)
		IVTVFB_WARN("ivtvfb_prep_frame: Count not a multiple of 4 (%d)\n", count);

	/* Check Source */
	अगर (!access_ok(source + dest_offset, count)) अणु
		IVTVFB_WARN("Invalid userspace pointer %p\n", source);

		IVTVFB_DEBUG_WARN("access_ok() failed for offset 0x%08lx source %p count %d\n",
				  dest_offset, source, count);
		वापस -EINVAL;
	पूर्ण

	/* OSD Address to send DMA to */
	dest_offset += IVTV_DECODER_OFFSET + oi->video_rbase;

	/* Fill Buffers */
	वापस ivtvfb_prep_dec_dma_to_device(itv, dest_offset, source, count);
पूर्ण

अटल sमाप_प्रकार ivtvfb_ग_लिखो(काष्ठा fb_info *info, स्थिर अक्षर __user *buf,
						माप_प्रकार count, loff_t *ppos)
अणु
	अचिन्हित दीर्घ p = *ppos;
	व्योम *dst;
	पूर्णांक err = 0;
	पूर्णांक dma_err;
	अचिन्हित दीर्घ total_size;
	काष्ठा ivtv *itv = (काष्ठा ivtv *) info->par;
	अचिन्हित दीर्घ dma_offset =
			IVTV_DECODER_OFFSET + itv->osd_info->video_rbase;
	अचिन्हित दीर्घ dma_size;
	u16 lead = 0, tail = 0;

	अगर (info->state != FBINFO_STATE_RUNNING)
		वापस -EPERM;

	total_size = info->screen_size;

	अगर (total_size == 0)
		total_size = info->fix.smem_len;

	अगर (p > total_size)
		वापस -EFBIG;

	अगर (count > total_size) अणु
		err = -EFBIG;
		count = total_size;
	पूर्ण

	अगर (count + p > total_size) अणु
		अगर (!err)
			err = -ENOSPC;
		count = total_size - p;
	पूर्ण

	dst = (व्योम __क्रमce *) (info->screen_base + p);

	अगर (info->fbops->fb_sync)
		info->fbops->fb_sync(info);

	/* If transfer size > threshold and both src/dst
	addresses are aligned, use DMA */
	अगर (count >= 4096 &&
	    ((अचिन्हित दीर्घ)buf & 3) == ((अचिन्हित दीर्घ)dst & 3)) अणु
		/* Odd address = can't DMA. Align */
		अगर ((अचिन्हित दीर्घ)dst & 3) अणु
			lead = 4 - ((अचिन्हित दीर्घ)dst & 3);
			अगर (copy_from_user(dst, buf, lead))
				वापस -EFAULT;
			buf += lead;
			dst += lead;
		पूर्ण
		/* DMA resolution is 32 bits */
		अगर ((count - lead) & 3)
			tail = (count - lead) & 3;
		/* DMA the data */
		dma_size = count - lead - tail;
		dma_err = ivtvfb_prep_dec_dma_to_device(itv,
		       p + lead + dma_offset, (व्योम __user *)buf, dma_size);
		अगर (dma_err)
			वापस dma_err;
		dst += dma_size;
		buf += dma_size;
		/* Copy any leftover data */
		अगर (tail && copy_from_user(dst, buf, tail))
			वापस -EFAULT;
	पूर्ण अन्यथा अगर (copy_from_user(dst, buf, count)) अणु
		वापस -EFAULT;
	पूर्ण

	अगर  (!err)
		*ppos += count;

	वापस (err) ? err : count;
पूर्ण

अटल पूर्णांक ivtvfb_ioctl(काष्ठा fb_info *info, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	DEFINE_WAIT(रुको);
	काष्ठा ivtv *itv = (काष्ठा ivtv *)info->par;
	पूर्णांक rc = 0;

	चयन (cmd) अणु
		हाल FBIOGET_VBLANK: अणु
			काष्ठा fb_vblank vblank;
			u32 trace;

			स_रखो(&vblank, 0, माप(काष्ठा fb_vblank));

			vblank.flags = FB_VBLANK_HAVE_COUNT |FB_VBLANK_HAVE_VCOUNT |
					FB_VBLANK_HAVE_VSYNC;
			trace = पढ़ो_reg(IVTV_REG_DEC_LINE_FIELD) >> 16;
			अगर (itv->is_out_50hz && trace > 312)
				trace -= 312;
			अन्यथा अगर (itv->is_out_60hz && trace > 262)
				trace -= 262;
			अगर (trace == 1)
				vblank.flags |= FB_VBLANK_VSYNCING;
			vblank.count = itv->last_vsync_field;
			vblank.vcount = trace;
			vblank.hcount = 0;
			अगर (copy_to_user((व्योम __user *)arg, &vblank, माप(vblank)))
				वापस -EFAULT;
			वापस 0;
		पूर्ण

		हाल FBIO_WAITFORVSYNC:
			prepare_to_रुको(&itv->vsync_रुकोq, &रुको, TASK_INTERRUPTIBLE);
			अगर (!schedule_समयout(msecs_to_jअगरfies(50)))
				rc = -ETIMEDOUT;
			finish_रुको(&itv->vsync_रुकोq, &रुको);
			वापस rc;

		हाल IVTVFB_IOC_DMA_FRAME: अणु
			काष्ठा ivtvfb_dma_frame args;

			IVTVFB_DEBUG_INFO("IVTVFB_IOC_DMA_FRAME\n");
			अगर (copy_from_user(&args, (व्योम __user *)arg, माप(args)))
				वापस -EFAULT;

			वापस ivtvfb_prep_frame(itv, cmd, args.source, args.dest_offset, args.count);
		पूर्ण

		शेष:
			IVTVFB_DEBUG_INFO("Unknown ioctl %08x\n", cmd);
			वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

/* Framebuffer device handling */

अटल पूर्णांक ivtvfb_set_var(काष्ठा ivtv *itv, काष्ठा fb_var_screeninfo *var)
अणु
	काष्ठा osd_info *oi = itv->osd_info;
	काष्ठा ivtv_osd_coords ivtv_osd;
	काष्ठा v4l2_rect ivtv_winकरोw;
	पूर्णांक osd_mode = -1;

	IVTVFB_DEBUG_INFO("ivtvfb_set_var\n");

	/* Select color space */
	अगर (var->nonstd) /* YUV */
		ग_लिखो_reg(पढ़ो_reg(0x02a00) | 0x0002000, 0x02a00);
	अन्यथा /* RGB  */
		ग_लिखो_reg(पढ़ो_reg(0x02a00) & ~0x0002000, 0x02a00);

	/* Set the color mode */
	चयन (var->bits_per_pixel) अणु
		हाल 8:
			osd_mode = IVTV_OSD_BPP_8;
			अवरोध;
		हाल 32:
			osd_mode = IVTV_OSD_BPP_32;
			अवरोध;
		हाल 16:
			चयन (var->green.length) अणु
			हाल 4:
				osd_mode = IVTV_OSD_BPP_16_444;
				अवरोध;
			हाल 5:
				osd_mode = IVTV_OSD_BPP_16_555;
				अवरोध;
			हाल 6:
				osd_mode = IVTV_OSD_BPP_16_565;
				अवरोध;
			शेष:
				IVTVFB_DEBUG_WARN("ivtvfb_set_var - Invalid bpp\n");
			पूर्ण
			अवरोध;
		शेष:
			IVTVFB_DEBUG_WARN("ivtvfb_set_var - Invalid bpp\n");
	पूर्ण

	/* Set video mode. Although rare, the display can become scrambled even
	   अगर we करोn't change mode. Always 'bounce' to osd_mode via mode 0 */
	अगर (osd_mode != -1) अणु
		ivtv_vapi(itv, CX2341X_OSD_SET_PIXEL_FORMAT, 1, 0);
		ivtv_vapi(itv, CX2341X_OSD_SET_PIXEL_FORMAT, 1, osd_mode);
	पूर्ण

	oi->bits_per_pixel = var->bits_per_pixel;
	oi->bytes_per_pixel = var->bits_per_pixel / 8;

	/* Set the flicker filter */
	चयन (var->vmode & FB_VMODE_MASK) अणु
		हाल FB_VMODE_NONINTERLACED: /* Filter on */
			ivtv_vapi(itv, CX2341X_OSD_SET_FLICKER_STATE, 1, 1);
			अवरोध;
		हाल FB_VMODE_INTERLACED: /* Filter off */
			ivtv_vapi(itv, CX2341X_OSD_SET_FLICKER_STATE, 1, 0);
			अवरोध;
		शेष:
			IVTVFB_DEBUG_WARN("ivtvfb_set_var - Invalid video mode\n");
	पूर्ण

	/* Read the current osd info */
	ivtvfb_get_osd_coords(itv, &ivtv_osd);

	/* Now set the OSD to the size we want */
	ivtv_osd.pixel_stride = var->xres_भव;
	ivtv_osd.lines = var->yres_भव;
	ivtv_osd.x = 0;
	ivtv_osd.y = 0;
	ivtvfb_set_osd_coords(itv, &ivtv_osd);

	/* Can't seem to find the right API combo क्रम this.
	   Use another function which करोes what we need through direct रेजिस्टर access. */
	ivtv_winकरोw.width = var->xres;
	ivtv_winकरोw.height = var->yres;

	/* Minimum margin cannot be 0, as X won't allow such a mode */
	अगर (!var->upper_margin)
		var->upper_margin++;
	अगर (!var->left_margin)
		var->left_margin++;
	ivtv_winकरोw.top = var->upper_margin - 1;
	ivtv_winकरोw.left = var->left_margin - 1;

	ivtvfb_set_display_winकरोw(itv, &ivtv_winकरोw);

	/* Pass screen size back to yuv handler */
	itv->yuv_info.osd_full_w = ivtv_osd.pixel_stride;
	itv->yuv_info.osd_full_h = ivtv_osd.lines;

	/* Force update of yuv रेजिस्टरs */
	itv->yuv_info.yuv_क्रमced_update = 1;

	/* Keep a copy of these settings */
	स_नकल(&oi->fbvar_cur, var, माप(oi->fbvar_cur));

	IVTVFB_DEBUG_INFO("Display size: %dx%d (virtual %dx%d) @ %dbpp\n",
		      var->xres, var->yres,
		      var->xres_भव, var->yres_भव,
		      var->bits_per_pixel);

	IVTVFB_DEBUG_INFO("Display position: %d, %d\n",
		      var->left_margin, var->upper_margin);

	IVTVFB_DEBUG_INFO("Display filter: %s\n",
			(var->vmode & FB_VMODE_MASK) == FB_VMODE_NONINTERLACED ? "on" : "off");
	IVTVFB_DEBUG_INFO("Color space: %s\n", var->nonstd ? "YUV" : "RGB");

	वापस 0;
पूर्ण

अटल पूर्णांक ivtvfb_get_fix(काष्ठा ivtv *itv, काष्ठा fb_fix_screeninfo *fix)
अणु
	काष्ठा osd_info *oi = itv->osd_info;

	IVTVFB_DEBUG_INFO("ivtvfb_get_fix\n");
	स_रखो(fix, 0, माप(काष्ठा fb_fix_screeninfo));
	strscpy(fix->id, "cx23415 TV out", माप(fix->id));
	fix->smem_start = oi->video_pbase;
	fix->smem_len = oi->video_buffer_size;
	fix->type = FB_TYPE_PACKED_PIXELS;
	fix->visual = (oi->bits_per_pixel == 8) ? FB_VISUAL_PSEUDOCOLOR : FB_VISUAL_TRUECOLOR;
	fix->xpanstep = 1;
	fix->ypanstep = 1;
	fix->ywrapstep = 0;
	fix->line_length = oi->display_byte_stride;
	fix->accel = FB_ACCEL_NONE;
	वापस 0;
पूर्ण

/* Check the requested display mode, वापसing -EINVAL अगर we can't
   handle it. */

अटल पूर्णांक _ivtvfb_check_var(काष्ठा fb_var_screeninfo *var, काष्ठा ivtv *itv)
अणु
	काष्ठा osd_info *oi = itv->osd_info;
	पूर्णांक osd_height_limit;
	u32 pixघड़ी, hlimit, vlimit;

	IVTVFB_DEBUG_INFO("ivtvfb_check_var\n");

	/* Set base references क्रम mode calcs. */
	अगर (itv->is_out_50hz) अणु
		pixघड़ी = 84316;
		hlimit = 776;
		vlimit = 591;
		osd_height_limit = 576;
	पूर्ण
	अन्यथा अणु
		pixघड़ी = 83926;
		hlimit = 776;
		vlimit = 495;
		osd_height_limit = 480;
	पूर्ण

	अगर (var->bits_per_pixel == 8 || var->bits_per_pixel == 32) अणु
		var->transp.offset = 24;
		var->transp.length = 8;
		var->red.offset = 16;
		var->red.length = 8;
		var->green.offset = 8;
		var->green.length = 8;
		var->blue.offset = 0;
		var->blue.length = 8;
	पूर्ण
	अन्यथा अगर (var->bits_per_pixel == 16) अणु
		/* To find out the true mode, check green length */
		चयन (var->green.length) अणु
			हाल 4:
				var->red.offset = 8;
				var->red.length = 4;
				var->green.offset = 4;
				var->green.length = 4;
				var->blue.offset = 0;
				var->blue.length = 4;
				var->transp.offset = 12;
				var->transp.length = 1;
				अवरोध;
			हाल 5:
				var->red.offset = 10;
				var->red.length = 5;
				var->green.offset = 5;
				var->green.length = 5;
				var->blue.offset = 0;
				var->blue.length = 5;
				var->transp.offset = 15;
				var->transp.length = 1;
				अवरोध;
			शेष:
				var->red.offset = 11;
				var->red.length = 5;
				var->green.offset = 5;
				var->green.length = 6;
				var->blue.offset = 0;
				var->blue.length = 5;
				var->transp.offset = 0;
				var->transp.length = 0;
				अवरोध;
		पूर्ण
	पूर्ण
	अन्यथा अणु
		IVTVFB_DEBUG_WARN("Invalid colour mode: %d\n", var->bits_per_pixel);
		वापस -EINVAL;
	पूर्ण

	/* Check the resolution */
	अगर (var->xres > IVTV_OSD_MAX_WIDTH || var->yres > osd_height_limit) अणु
		IVTVFB_DEBUG_WARN("Invalid resolution: %dx%d\n",
				var->xres, var->yres);
		वापस -EINVAL;
	पूर्ण

	/* Max horizontal size is 1023 @ 32bpp, 2046 & 16bpp, 4092 @ 8bpp */
	अगर (var->xres_भव > 4095 / (var->bits_per_pixel / 8) ||
	    var->xres_भव * var->yres_भव * (var->bits_per_pixel / 8) > oi->video_buffer_size ||
	    var->xres_भव < var->xres ||
	    var->yres_भव < var->yres) अणु
		IVTVFB_DEBUG_WARN("Invalid virtual resolution: %dx%d\n",
			var->xres_भव, var->yres_भव);
		वापस -EINVAL;
	पूर्ण

	/* Some extra checks अगर in 8 bit mode */
	अगर (var->bits_per_pixel == 8) अणु
		/* Width must be a multiple of 4 */
		अगर (var->xres & 3) अणु
			IVTVFB_DEBUG_WARN("Invalid resolution for 8bpp: %d\n", var->xres);
			वापस -EINVAL;
		पूर्ण
		अगर (var->xres_भव & 3) अणु
			IVTVFB_DEBUG_WARN("Invalid virtual resolution for 8bpp: %d)\n", var->xres_भव);
			वापस -EINVAL;
		पूर्ण
	पूर्ण
	अन्यथा अगर (var->bits_per_pixel == 16) अणु
		/* Width must be a multiple of 2 */
		अगर (var->xres & 1) अणु
			IVTVFB_DEBUG_WARN("Invalid resolution for 16bpp: %d\n", var->xres);
			वापस -EINVAL;
		पूर्ण
		अगर (var->xres_भव & 1) अणु
			IVTVFB_DEBUG_WARN("Invalid virtual resolution for 16bpp: %d)\n", var->xres_भव);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	/* Now check the offsets */
	अगर (var->xoffset >= var->xres_भव || var->yoffset >= var->yres_भव) अणु
		IVTVFB_DEBUG_WARN("Invalid offset: %d (%d) %d (%d)\n",
			var->xoffset, var->xres_भव, var->yoffset, var->yres_भव);
		वापस -EINVAL;
	पूर्ण

	/* Check pixel क्रमmat */
	अगर (var->nonstd > 1) अणु
		IVTVFB_DEBUG_WARN("Invalid nonstd % d\n", var->nonstd);
		वापस -EINVAL;
	पूर्ण

	/* Check video mode */
	अगर (((var->vmode & FB_VMODE_MASK) != FB_VMODE_NONINTERLACED) &&
		((var->vmode & FB_VMODE_MASK) != FB_VMODE_INTERLACED)) अणु
		IVTVFB_DEBUG_WARN("Invalid video mode: %d\n", var->vmode & FB_VMODE_MASK);
		वापस -EINVAL;
	पूर्ण

	/* Check the left & upper margins
	   If the margins are too large, just center the screen
	   (enक्रमcing margins causes too many problems) */

	अगर (var->left_margin + var->xres > IVTV_OSD_MAX_WIDTH + 1)
		var->left_margin = 1 + ((IVTV_OSD_MAX_WIDTH - var->xres) / 2);

	अगर (var->upper_margin + var->yres > (itv->is_out_50hz ? 577 : 481))
		var->upper_margin = 1 + (((itv->is_out_50hz ? 576 : 480) -
			var->yres) / 2);

	/* Maपूर्णांकain overall 'size' क्रम a स्थिरant refresh rate */
	var->right_margin = hlimit - var->left_margin - var->xres;
	var->lower_margin = vlimit - var->upper_margin - var->yres;

	/* Fixed sync बार */
	var->hsync_len = 24;
	var->vsync_len = 2;

	/* Non-पूर्णांकerlaced / पूर्णांकerlaced mode is used to चयन the OSD filter
	   on or off. Adjust the घड़ी timings to मुख्यtain a स्थिरant
	   vertical refresh rate. */
	अगर ((var->vmode & FB_VMODE_MASK) == FB_VMODE_NONINTERLACED)
		var->pixघड़ी = pixघड़ी / 2;
	अन्यथा
		var->pixघड़ी = pixघड़ी;

	itv->osd_rect.width = var->xres;
	itv->osd_rect.height = var->yres;

	IVTVFB_DEBUG_INFO("Display size: %dx%d (virtual %dx%d) @ %dbpp\n",
		      var->xres, var->yres,
		      var->xres_भव, var->yres_भव,
		      var->bits_per_pixel);

	IVTVFB_DEBUG_INFO("Display position: %d, %d\n",
		      var->left_margin, var->upper_margin);

	IVTVFB_DEBUG_INFO("Display filter: %s\n",
			(var->vmode & FB_VMODE_MASK) == FB_VMODE_NONINTERLACED ? "on" : "off");
	IVTVFB_DEBUG_INFO("Color space: %s\n", var->nonstd ? "YUV" : "RGB");
	वापस 0;
पूर्ण

अटल पूर्णांक ivtvfb_check_var(काष्ठा fb_var_screeninfo *var, काष्ठा fb_info *info)
अणु
	काष्ठा ivtv *itv = (काष्ठा ivtv *) info->par;
	IVTVFB_DEBUG_INFO("ivtvfb_check_var\n");
	वापस _ivtvfb_check_var(var, itv);
पूर्ण

अटल पूर्णांक ivtvfb_pan_display(काष्ठा fb_var_screeninfo *var, काष्ठा fb_info *info)
अणु
	u32 osd_pan_index;
	काष्ठा ivtv *itv = (काष्ठा ivtv *) info->par;

	अगर (var->yoffset + info->var.yres > info->var.yres_भव ||
	    var->xoffset + info->var.xres > info->var.xres_भव)
		वापस -EINVAL;

	osd_pan_index = var->yoffset * info->fix.line_length
		      + var->xoffset * info->var.bits_per_pixel / 8;
	ग_लिखो_reg(osd_pan_index, 0x02A0C);

	/* Pass this info back the yuv handler */
	itv->yuv_info.osd_x_pan = var->xoffset;
	itv->yuv_info.osd_y_pan = var->yoffset;
	/* Force update of yuv रेजिस्टरs */
	itv->yuv_info.yuv_क्रमced_update = 1;
	/* Remember this value */
	itv->osd_info->pan_cur = osd_pan_index;
	वापस 0;
पूर्ण

अटल पूर्णांक ivtvfb_set_par(काष्ठा fb_info *info)
अणु
	पूर्णांक rc = 0;
	काष्ठा ivtv *itv = (काष्ठा ivtv *) info->par;

	IVTVFB_DEBUG_INFO("ivtvfb_set_par\n");

	rc = ivtvfb_set_var(itv, &info->var);
	ivtvfb_pan_display(&info->var, info);
	ivtvfb_get_fix(itv, &info->fix);
	ivtv_firmware_check(itv, "ivtvfb_set_par");
	वापस rc;
पूर्ण

अटल पूर्णांक ivtvfb_setcolreg(अचिन्हित regno, अचिन्हित red, अचिन्हित green,
				अचिन्हित blue, अचिन्हित transp,
				काष्ठा fb_info *info)
अणु
	u32 color, *palette;
	काष्ठा ivtv *itv = (काष्ठा ivtv *)info->par;

	अगर (regno >= info->cmap.len)
		वापस -EINVAL;

	color = ((transp & 0xFF00) << 16) |((red & 0xFF00) << 8) | (green & 0xFF00) | ((blue & 0xFF00) >> 8);
	अगर (info->var.bits_per_pixel <= 8) अणु
		ग_लिखो_reg(regno, 0x02a30);
		ग_लिखो_reg(color, 0x02a34);
		itv->osd_info->palette_cur[regno] = color;
		वापस 0;
	पूर्ण
	अगर (regno >= 16)
		वापस -EINVAL;

	palette = info->pseuकरो_palette;
	अगर (info->var.bits_per_pixel == 16) अणु
		चयन (info->var.green.length) अणु
			हाल 4:
				color = ((red & 0xf000) >> 4) |
					((green & 0xf000) >> 8) |
					((blue & 0xf000) >> 12);
				अवरोध;
			हाल 5:
				color = ((red & 0xf800) >> 1) |
					((green & 0xf800) >> 6) |
					((blue & 0xf800) >> 11);
				अवरोध;
			हाल 6:
				color = (red & 0xf800 ) |
					((green & 0xfc00) >> 5) |
					((blue & 0xf800) >> 11);
				अवरोध;
		पूर्ण
	पूर्ण
	palette[regno] = color;
	वापस 0;
पूर्ण

/* We करोn't really support blanking. All this करोes is enable or
   disable the OSD. */
अटल पूर्णांक ivtvfb_blank(पूर्णांक blank_mode, काष्ठा fb_info *info)
अणु
	काष्ठा ivtv *itv = (काष्ठा ivtv *)info->par;

	IVTVFB_DEBUG_INFO("Set blanking mode : %d\n", blank_mode);
	चयन (blank_mode) अणु
	हाल FB_BLANK_UNBLANK:
		ivtv_vapi(itv, CX2341X_OSD_SET_STATE, 1, 1);
		ivtv_call_hw(itv, IVTV_HW_SAA7127, video, s_stream, 1);
		अवरोध;
	हाल FB_BLANK_NORMAL:
	हाल FB_BLANK_HSYNC_SUSPEND:
	हाल FB_BLANK_VSYNC_SUSPEND:
		ivtv_vapi(itv, CX2341X_OSD_SET_STATE, 1, 0);
		ivtv_call_hw(itv, IVTV_HW_SAA7127, video, s_stream, 1);
		अवरोध;
	हाल FB_BLANK_POWERDOWN:
		ivtv_call_hw(itv, IVTV_HW_SAA7127, video, s_stream, 0);
		ivtv_vapi(itv, CX2341X_OSD_SET_STATE, 1, 0);
		अवरोध;
	पूर्ण
	itv->osd_info->blank_cur = blank_mode;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा fb_ops ivtvfb_ops = अणु
	.owner = THIS_MODULE,
	.fb_ग_लिखो       = ivtvfb_ग_लिखो,
	.fb_check_var   = ivtvfb_check_var,
	.fb_set_par     = ivtvfb_set_par,
	.fb_setcolreg   = ivtvfb_setcolreg,
	.fb_fillrect    = cfb_fillrect,
	.fb_copyarea    = cfb_copyarea,
	.fb_imageblit   = cfb_imageblit,
	.fb_cursor      = शून्य,
	.fb_ioctl       = ivtvfb_ioctl,
	.fb_pan_display = ivtvfb_pan_display,
	.fb_blank       = ivtvfb_blank,
पूर्ण;

/* Restore hardware after firmware restart */
अटल व्योम ivtvfb_restore(काष्ठा ivtv *itv)
अणु
	काष्ठा osd_info *oi = itv->osd_info;
	पूर्णांक i;

	ivtvfb_set_var(itv, &oi->fbvar_cur);
	ivtvfb_blank(oi->blank_cur, &oi->ivtvfb_info);
	क्रम (i = 0; i < 256; i++) अणु
		ग_लिखो_reg(i, 0x02a30);
		ग_लिखो_reg(oi->palette_cur[i], 0x02a34);
	पूर्ण
	ग_लिखो_reg(oi->pan_cur, 0x02a0c);
पूर्ण

/* Initialization */


/* Setup our initial video mode */
अटल पूर्णांक ivtvfb_init_vidmode(काष्ठा ivtv *itv)
अणु
	काष्ठा osd_info *oi = itv->osd_info;
	काष्ठा v4l2_rect start_winकरोw;
	पूर्णांक max_height;

	/* Color mode */

	अगर (osd_depth != 8 && osd_depth != 16 && osd_depth != 32)
		osd_depth = 8;
	oi->bits_per_pixel = osd_depth;
	oi->bytes_per_pixel = oi->bits_per_pixel / 8;

	/* Horizontal size & position */

	अगर (osd_xres > 720)
		osd_xres = 720;

	/* Must be a multiple of 4 क्रम 8bpp & 2 क्रम 16bpp */
	अगर (osd_depth == 8)
		osd_xres &= ~3;
	अन्यथा अगर (osd_depth == 16)
		osd_xres &= ~1;

	start_winकरोw.width = osd_xres ? osd_xres : 640;

	/* Check horizontal start (osd_left). */
	अगर (osd_left && osd_left + start_winकरोw.width > 721) अणु
		IVTVFB_ERR("Invalid osd_left - assuming default\n");
		osd_left = 0;
	पूर्ण

	/* Hardware coords start at 0, user coords start at 1. */
	osd_left--;

	start_winकरोw.left = osd_left >= 0 ?
		 osd_left : ((IVTV_OSD_MAX_WIDTH - start_winकरोw.width) / 2);

	oi->display_byte_stride =
			start_winकरोw.width * oi->bytes_per_pixel;

	/* Vertical size & position */

	max_height = itv->is_out_50hz ? 576 : 480;

	अगर (osd_yres > max_height)
		osd_yres = max_height;

	start_winकरोw.height = osd_yres ?
		osd_yres : itv->is_out_50hz ? 480 : 400;

	/* Check vertical start (osd_upper). */
	अगर (osd_upper + start_winकरोw.height > max_height + 1) अणु
		IVTVFB_ERR("Invalid osd_upper - assuming default\n");
		osd_upper = 0;
	पूर्ण

	/* Hardware coords start at 0, user coords start at 1. */
	osd_upper--;

	start_winकरोw.top = osd_upper >= 0 ? osd_upper : ((max_height - start_winकरोw.height) / 2);

	oi->display_width = start_winकरोw.width;
	oi->display_height = start_winकरोw.height;

	/* Generate a valid fb_var_screeninfo */

	oi->ivtvfb_defined.xres = oi->display_width;
	oi->ivtvfb_defined.yres = oi->display_height;
	oi->ivtvfb_defined.xres_भव = oi->display_width;
	oi->ivtvfb_defined.yres_भव = oi->display_height;
	oi->ivtvfb_defined.bits_per_pixel = oi->bits_per_pixel;
	oi->ivtvfb_defined.vmode = (osd_laced ? FB_VMODE_INTERLACED : FB_VMODE_NONINTERLACED);
	oi->ivtvfb_defined.left_margin = start_winकरोw.left + 1;
	oi->ivtvfb_defined.upper_margin = start_winकरोw.top + 1;
	oi->ivtvfb_defined.accel_flags = FB_ACCEL_NONE;
	oi->ivtvfb_defined.nonstd = 0;

	/* We've filled in the most data, let the usual mode check
	   routine fill in the rest. */
	_ivtvfb_check_var(&oi->ivtvfb_defined, itv);

	/* Generate valid fb_fix_screeninfo */

	ivtvfb_get_fix(itv, &oi->ivtvfb_fix);

	/* Generate valid fb_info */

	oi->ivtvfb_info.node = -1;
	oi->ivtvfb_info.flags = FBINFO_FLAG_DEFAULT;
	oi->ivtvfb_info.par = itv;
	oi->ivtvfb_info.var = oi->ivtvfb_defined;
	oi->ivtvfb_info.fix = oi->ivtvfb_fix;
	oi->ivtvfb_info.screen_base = (u8 __iomem *)oi->video_vbase;
	oi->ivtvfb_info.fbops = &ivtvfb_ops;

	/* Supply some monitor specs. Bogus values will करो क्रम now */
	oi->ivtvfb_info.monspecs.hfmin = 8000;
	oi->ivtvfb_info.monspecs.hfmax = 70000;
	oi->ivtvfb_info.monspecs.vfmin = 10;
	oi->ivtvfb_info.monspecs.vfmax = 100;

	/* Allocate color map */
	अगर (fb_alloc_cmap(&oi->ivtvfb_info.cmap, 256, 1)) अणु
		IVTVFB_ERR("abort, unable to alloc cmap\n");
		वापस -ENOMEM;
	पूर्ण

	/* Allocate the pseuकरो palette */
	oi->ivtvfb_info.pseuकरो_palette =
		kदो_स्मृति_array(16, माप(u32), GFP_KERNEL|__GFP_NOWARN);

	अगर (!oi->ivtvfb_info.pseuकरो_palette) अणु
		IVTVFB_ERR("abort, unable to alloc pseudo palette\n");
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

/* Find OSD buffer base & size. Add to mtrr. Zero osd buffer. */

अटल पूर्णांक ivtvfb_init_io(काष्ठा ivtv *itv)
अणु
	काष्ठा osd_info *oi = itv->osd_info;
	/* Find the largest घातer of two that maps the whole buffer */
	पूर्णांक size_shअगरt = 31;

	mutex_lock(&itv->serialize_lock);
	अगर (ivtv_init_on_first_खोलो(itv)) अणु
		mutex_unlock(&itv->serialize_lock);
		IVTVFB_ERR("Failed to initialize ivtv\n");
		वापस -ENXIO;
	पूर्ण
	mutex_unlock(&itv->serialize_lock);

	अगर (ivtvfb_get_framebuffer(itv, &oi->video_rbase,
					&oi->video_buffer_size) < 0) अणु
		IVTVFB_ERR("Firmware failed to respond\n");
		वापस -EIO;
	पूर्ण

	/* The osd buffer size depends on the number of video buffers allocated
	   on the PVR350 itself. For now we'll hardcode the smallest osd buffer
	   size to prevent any overlap. */
	oi->video_buffer_size = 1704960;

	oi->video_pbase = itv->base_addr + IVTV_DECODER_OFFSET + oi->video_rbase;
	oi->video_vbase = itv->dec_mem + oi->video_rbase;

	अगर (!oi->video_vbase) अणु
		IVTVFB_ERR("abort, video memory 0x%x @ 0x%lx isn't mapped!\n",
		     oi->video_buffer_size, oi->video_pbase);
		वापस -EIO;
	पूर्ण

	IVTVFB_INFO("Framebuffer at 0x%lx, mapped to 0x%p, size %dk\n",
			oi->video_pbase, oi->video_vbase,
			oi->video_buffer_size / 1024);

	जबतक (!(oi->video_buffer_size & (1 << size_shअगरt)))
		size_shअगरt--;
	size_shअगरt++;
	oi->fb_start_aligned_physaddr = oi->video_pbase & ~((1 << size_shअगरt) - 1);
	oi->fb_end_aligned_physaddr = oi->video_pbase + oi->video_buffer_size;
	oi->fb_end_aligned_physaddr += (1 << size_shअगरt) - 1;
	oi->fb_end_aligned_physaddr &= ~((1 << size_shअगरt) - 1);
	oi->wc_cookie = arch_phys_wc_add(oi->fb_start_aligned_physaddr,
					 oi->fb_end_aligned_physaddr -
					 oi->fb_start_aligned_physaddr);
	/* Blank the entire osd. */
	स_रखो_io(oi->video_vbase, 0, oi->video_buffer_size);

	वापस 0;
पूर्ण

/* Release any memory we've grabbed & हटाओ mtrr entry */
अटल व्योम ivtvfb_release_buffers (काष्ठा ivtv *itv)
अणु
	काष्ठा osd_info *oi = itv->osd_info;

	/* Release cmap */
	अगर (oi->ivtvfb_info.cmap.len)
		fb_dealloc_cmap(&oi->ivtvfb_info.cmap);

	/* Release pseuकरो palette */
	kमुक्त(oi->ivtvfb_info.pseuकरो_palette);
	arch_phys_wc_del(oi->wc_cookie);
	kमुक्त(oi);
	itv->osd_info = शून्य;
पूर्ण

/* Initialize the specअगरied card */

अटल पूर्णांक ivtvfb_init_card(काष्ठा ivtv *itv)
अणु
	पूर्णांक rc;

#अगर_घोषित CONFIG_X86_64
	अगर (pat_enabled()) अणु
		अगर (ivtvfb_क्रमce_pat) अणु
			pr_info("PAT is enabled. Write-combined framebuffer caching will be disabled.\n");
			pr_info("To enable caching, boot with nopat kernel parameter\n");
		पूर्ण अन्यथा अणु
			pr_warn("ivtvfb needs PAT disabled for write-combined framebuffer caching.\n");
			pr_warn("Boot with nopat kernel parameter to use caching, or use the\n");
			pr_warn("force_pat module parameter to run with caching disabled\n");
			वापस -ENODEV;
		पूर्ण
	पूर्ण
#पूर्ण_अगर

	अगर (itv->osd_info) अणु
		IVTVFB_ERR("Card %d already initialised\n", ivtvfb_card_id);
		वापस -EBUSY;
	पूर्ण

	itv->osd_info = kzalloc(माप(काष्ठा osd_info),
					GFP_KERNEL|__GFP_NOWARN);
	अगर (itv->osd_info == शून्य) अणु
		IVTVFB_ERR("Failed to allocate memory for osd_info\n");
		वापस -ENOMEM;
	पूर्ण

	/* Find & setup the OSD buffer */
	rc = ivtvfb_init_io(itv);
	अगर (rc) अणु
		ivtvfb_release_buffers(itv);
		वापस rc;
	पूर्ण

	/* Set the startup video mode inक्रमmation */
	अगर ((rc = ivtvfb_init_vidmode(itv))) अणु
		ivtvfb_release_buffers(itv);
		वापस rc;
	पूर्ण

	/* Register the framebuffer */
	अगर (रेजिस्टर_framebuffer(&itv->osd_info->ivtvfb_info) < 0) अणु
		ivtvfb_release_buffers(itv);
		वापस -EINVAL;
	पूर्ण

	itv->osd_video_pbase = itv->osd_info->video_pbase;

	/* Set the card to the requested mode */
	ivtvfb_set_par(&itv->osd_info->ivtvfb_info);

	/* Set color 0 to black */
	ग_लिखो_reg(0, 0x02a30);
	ग_लिखो_reg(0, 0x02a34);

	/* Enable the osd */
	ivtvfb_blank(FB_BLANK_UNBLANK, &itv->osd_info->ivtvfb_info);

	/* Enable restart */
	itv->ivtvfb_restore = ivtvfb_restore;

	/* Allocate DMA */
	ivtv_udma_alloc(itv);
	itv->streams[IVTV_DEC_STREAM_TYPE_YUV].vdev.device_caps |=
		V4L2_CAP_VIDEO_OUTPUT_OVERLAY;
	itv->streams[IVTV_DEC_STREAM_TYPE_MPG].vdev.device_caps |=
		V4L2_CAP_VIDEO_OUTPUT_OVERLAY;
	itv->v4l2_cap |= V4L2_CAP_VIDEO_OUTPUT_OVERLAY;
	वापस 0;

पूर्ण

अटल पूर्णांक __init ivtvfb_callback_init(काष्ठा device *dev, व्योम *p)
अणु
	काष्ठा v4l2_device *v4l2_dev = dev_get_drvdata(dev);
	काष्ठा ivtv *itv = container_of(v4l2_dev, काष्ठा ivtv, v4l2_dev);

	अगर (itv->v4l2_cap & V4L2_CAP_VIDEO_OUTPUT) अणु
		अगर (ivtvfb_init_card(itv) == 0) अणु
			IVTVFB_INFO("Framebuffer registered on %s\n",
					itv->v4l2_dev.name);
			(*(पूर्णांक *)p)++;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक ivtvfb_callback_cleanup(काष्ठा device *dev, व्योम *p)
अणु
	काष्ठा v4l2_device *v4l2_dev = dev_get_drvdata(dev);
	काष्ठा ivtv *itv = container_of(v4l2_dev, काष्ठा ivtv, v4l2_dev);
	काष्ठा osd_info *oi = itv->osd_info;

	अगर (itv->v4l2_cap & V4L2_CAP_VIDEO_OUTPUT) अणु
		itv->streams[IVTV_DEC_STREAM_TYPE_YUV].vdev.device_caps &=
			~V4L2_CAP_VIDEO_OUTPUT_OVERLAY;
		itv->streams[IVTV_DEC_STREAM_TYPE_MPG].vdev.device_caps &=
			~V4L2_CAP_VIDEO_OUTPUT_OVERLAY;
		itv->v4l2_cap &= ~V4L2_CAP_VIDEO_OUTPUT_OVERLAY;
		unरेजिस्टर_framebuffer(&itv->osd_info->ivtvfb_info);
		IVTVFB_INFO("Unregister framebuffer %d\n", itv->instance);
		itv->ivtvfb_restore = शून्य;
		ivtvfb_blank(FB_BLANK_VSYNC_SUSPEND, &oi->ivtvfb_info);
		ivtvfb_release_buffers(itv);
		itv->osd_video_pbase = 0;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक __init ivtvfb_init(व्योम)
अणु
	काष्ठा device_driver *drv;
	पूर्णांक रेजिस्टरed = 0;
	पूर्णांक err;


	अगर (ivtvfb_card_id < -1 || ivtvfb_card_id >= IVTV_MAX_CARDS) अणु
		pr_err("ivtvfb_card_id parameter is out of range (valid range: -1 - %d)\n",
		     IVTV_MAX_CARDS - 1);
		वापस -EINVAL;
	पूर्ण

	drv = driver_find("ivtv", &pci_bus_type);
	err = driver_क्रम_each_device(drv, शून्य, &रेजिस्टरed, ivtvfb_callback_init);
	(व्योम)err;	/* suppress compiler warning */
	अगर (!रेजिस्टरed) अणु
		pr_err("no cards found\n");
		वापस -ENODEV;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम ivtvfb_cleanup(व्योम)
अणु
	काष्ठा device_driver *drv;
	पूर्णांक err;

	pr_info("Unloading framebuffer module\n");

	drv = driver_find("ivtv", &pci_bus_type);
	err = driver_क्रम_each_device(drv, शून्य, शून्य, ivtvfb_callback_cleanup);
	(व्योम)err;	/* suppress compiler warning */
पूर्ण

module_init(ivtvfb_init);
module_निकास(ivtvfb_cleanup);
