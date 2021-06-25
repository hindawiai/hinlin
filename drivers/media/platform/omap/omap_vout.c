<शैली गुरु>
/*
 * omap_vout.c
 *
 * Copyright (C) 2005-2010 Texas Instruments.
 *
 * This file is licensed under the terms of the GNU General Public License
 * version 2. This program is licensed "as is" without any warranty of any
 * kind, whether express or implied.
 *
 * Leveraged code from the OMAP2 camera driver
 * Video-क्रम-Linux (Version 2) camera capture driver क्रम
 * the OMAP24xx camera controller.
 *
 * Author: Andy Lowe (source@mvista.com)
 *
 * Copyright (C) 2004 MontaVista Software, Inc.
 * Copyright (C) 2010 Texas Instruments.
 *
 * History:
 * 20-APR-2006 Khasim		Modअगरied VRFB based Rotation,
 *				The image data is always पढ़ो from 0 degree
 *				view and written
 *				to the भव space of desired rotation angle
 * 4-DEC-2006  Jian		Changed to support better memory management
 *
 * 17-Nov-2008 Hardik		Changed driver to use video_ioctl2
 *
 * 23-Feb-2010 Vaibhav H	Modअगरied to use new DSS2 पूर्णांकerface
 *
 */

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/sched.h>
#समावेश <linux/types.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/irq.h>
#समावेश <linux/videodev2.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/slab.h>

#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-ioctl.h>
#समावेश <media/v4l2-event.h>

#समावेश <video/omapvrfb.h>
#समावेश <video/omapfb_dss.h>

#समावेश "omap_voutlib.h"
#समावेश "omap_voutdef.h"
#समावेश "omap_vout_vrfb.h"

MODULE_AUTHOR("Texas Instruments");
MODULE_DESCRIPTION("OMAP Video for Linux Video out driver");
MODULE_LICENSE("GPL");

/* Driver Configuration macros */
#घोषणा VOUT_NAME		"omap_vout"

क्रमागत omap_vout_channels अणु
	OMAP_VIDEO1,
	OMAP_VIDEO2,
पूर्ण;

/* Variables configurable through module params*/
अटल bool vid1_अटल_vrfb_alloc;
अटल bool vid2_अटल_vrfb_alloc;
अटल bool debug;

/* Module parameters */
module_param(vid1_अटल_vrfb_alloc, bool, S_IRUGO);
MODULE_PARM_DESC(vid1_अटल_vrfb_alloc,
	"Static allocation of the VRFB buffer for video1 device");

module_param(vid2_अटल_vrfb_alloc, bool, S_IRUGO);
MODULE_PARM_DESC(vid2_अटल_vrfb_alloc,
	"Static allocation of the VRFB buffer for video2 device");

module_param(debug, bool, S_IRUGO);
MODULE_PARM_DESC(debug, "Debug level (0-1)");

/* list of image क्रमmats supported by OMAP2 video pipelines */
अटल स्थिर काष्ठा v4l2_fmtdesc omap_क्रमmats[] = अणु
	अणु
		/* Note:  V4L2 defines RGB565 as:
		 *
		 *      Byte 0                    Byte 1
		 *      g2 g1 g0 r4 r3 r2 r1 r0   b4 b3 b2 b1 b0 g5 g4 g3
		 *
		 * We पूर्णांकerpret RGB565 as:
		 *
		 *      Byte 0                    Byte 1
		 *      g2 g1 g0 b4 b3 b2 b1 b0   r4 r3 r2 r1 r0 g5 g4 g3
		 */
		.pixelक्रमmat = V4L2_PIX_FMT_RGB565,
	पूर्ण,
	अणु
		/* Note:  V4L2 defines RGB32 as: RGB-8-8-8-8  we use
		 *  this क्रम RGB24 unpack mode, the last 8 bits are ignored
		 * */
		.pixelक्रमmat = V4L2_PIX_FMT_RGB32,
	पूर्ण,
	अणु
		/* Note:  V4L2 defines RGB24 as: RGB-8-8-8  we use
		 *        this क्रम RGB24 packed mode
		 *
		 */
		.pixelक्रमmat = V4L2_PIX_FMT_RGB24,
	पूर्ण,
	अणु
		.pixelक्रमmat = V4L2_PIX_FMT_YUYV,
	पूर्ण,
	अणु
		.pixelक्रमmat = V4L2_PIX_FMT_UYVY,
	पूर्ण,
पूर्ण;

#घोषणा NUM_OUTPUT_FORMATS (ARRAY_SIZE(omap_क्रमmats))

/*
 * Try क्रमmat
 */
अटल पूर्णांक omap_vout_try_क्रमmat(काष्ठा v4l2_pix_क्रमmat *pix)
अणु
	पूर्णांक अगरmt, bpp = 0;

	pix->height = clamp(pix->height, (u32)VID_MIN_HEIGHT,
						(u32)VID_MAX_HEIGHT);
	pix->width = clamp(pix->width, (u32)VID_MIN_WIDTH, (u32)VID_MAX_WIDTH);

	क्रम (अगरmt = 0; अगरmt < NUM_OUTPUT_FORMATS; अगरmt++) अणु
		अगर (pix->pixelक्रमmat == omap_क्रमmats[अगरmt].pixelक्रमmat)
			अवरोध;
	पूर्ण

	अगर (अगरmt == NUM_OUTPUT_FORMATS)
		अगरmt = 0;

	pix->pixelक्रमmat = omap_क्रमmats[अगरmt].pixelक्रमmat;
	pix->field = V4L2_FIELD_NONE;

	चयन (pix->pixelक्रमmat) अणु
	हाल V4L2_PIX_FMT_YUYV:
	हाल V4L2_PIX_FMT_UYVY:
	शेष:
		pix->colorspace = V4L2_COLORSPACE_SRGB;
		bpp = YUYV_BPP;
		अवरोध;
	हाल V4L2_PIX_FMT_RGB565:
	हाल V4L2_PIX_FMT_RGB565X:
		pix->colorspace = V4L2_COLORSPACE_SRGB;
		bpp = RGB565_BPP;
		अवरोध;
	हाल V4L2_PIX_FMT_RGB24:
		pix->colorspace = V4L2_COLORSPACE_SRGB;
		bpp = RGB24_BPP;
		अवरोध;
	हाल V4L2_PIX_FMT_RGB32:
	हाल V4L2_PIX_FMT_BGR32:
		pix->colorspace = V4L2_COLORSPACE_SRGB;
		bpp = RGB32_BPP;
		अवरोध;
	पूर्ण
	pix->bytesperline = pix->width * bpp;
	pix->sizeimage = pix->bytesperline * pix->height;

	वापस bpp;
पूर्ण

/*
 * Convert V4L2 rotation to DSS rotation
 *	V4L2 understand 0, 90, 180, 270.
 *	Convert to 0, 1, 2 and 3 respectively क्रम DSS
 */
अटल पूर्णांक v4l2_rot_to_dss_rot(पूर्णांक v4l2_rotation,
			क्रमागत dss_rotation *rotation, bool mirror)
अणु
	पूर्णांक ret = 0;

	चयन (v4l2_rotation) अणु
	हाल 90:
		*rotation = dss_rotation_90_degree;
		अवरोध;
	हाल 180:
		*rotation = dss_rotation_180_degree;
		अवरोध;
	हाल 270:
		*rotation = dss_rotation_270_degree;
		अवरोध;
	हाल 0:
		*rotation = dss_rotation_0_degree;
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक omap_vout_calculate_offset(काष्ठा omap_vout_device *vout)
अणु
	काष्ठा omapvideo_info *ovid;
	काष्ठा v4l2_rect *crop = &vout->crop;
	काष्ठा v4l2_pix_क्रमmat *pix = &vout->pix;
	पूर्णांक *cropped_offset = &vout->cropped_offset;
	पूर्णांक ps = 2, line_length = 0;

	ovid = &vout->vid_info;

	अगर (ovid->rotation_type == VOUT_ROT_VRFB) अणु
		omap_vout_calculate_vrfb_offset(vout);
	पूर्ण अन्यथा अणु
		vout->line_length = line_length = pix->width;

		अगर (V4L2_PIX_FMT_YUYV == pix->pixelक्रमmat ||
			V4L2_PIX_FMT_UYVY == pix->pixelक्रमmat)
			ps = 2;
		अन्यथा अगर (V4L2_PIX_FMT_RGB32 == pix->pixelक्रमmat)
			ps = 4;
		अन्यथा अगर (V4L2_PIX_FMT_RGB24 == pix->pixelक्रमmat)
			ps = 3;

		vout->ps = ps;

		*cropped_offset = (line_length * ps) *
			crop->top + crop->left * ps;
	पूर्ण

	v4l2_dbg(1, debug, &vout->vid_dev->v4l2_dev, "%s Offset:%x\n",
			__func__, vout->cropped_offset);

	वापस 0;
पूर्ण

/*
 * Convert V4L2 pixel क्रमmat to DSS pixel क्रमmat
 */
अटल पूर्णांक video_mode_to_dss_mode(काष्ठा omap_vout_device *vout)
अणु
	काष्ठा omap_overlay *ovl;
	काष्ठा omapvideo_info *ovid;
	काष्ठा v4l2_pix_क्रमmat *pix = &vout->pix;
	क्रमागत omap_color_mode mode;

	ovid = &vout->vid_info;
	ovl = ovid->overlays[0];

	चयन (pix->pixelक्रमmat) अणु
	हाल V4L2_PIX_FMT_YUYV:
		mode = OMAP_DSS_COLOR_YUV2;
		अवरोध;
	हाल V4L2_PIX_FMT_UYVY:
		mode = OMAP_DSS_COLOR_UYVY;
		अवरोध;
	हाल V4L2_PIX_FMT_RGB565:
		mode = OMAP_DSS_COLOR_RGB16;
		अवरोध;
	हाल V4L2_PIX_FMT_RGB24:
		mode = OMAP_DSS_COLOR_RGB24P;
		अवरोध;
	हाल V4L2_PIX_FMT_RGB32:
		mode = (ovl->id == OMAP_DSS_VIDEO1) ?
			OMAP_DSS_COLOR_RGB24U : OMAP_DSS_COLOR_ARGB32;
		अवरोध;
	हाल V4L2_PIX_FMT_BGR32:
		mode = OMAP_DSS_COLOR_RGBX32;
		अवरोध;
	शेष:
		mode = -EINVAL;
		अवरोध;
	पूर्ण
	वापस mode;
पूर्ण

/*
 * Setup the overlay
 */
अटल पूर्णांक omapvid_setup_overlay(काष्ठा omap_vout_device *vout,
		काष्ठा omap_overlay *ovl, पूर्णांक posx, पूर्णांक posy, पूर्णांक outw,
		पूर्णांक outh, u32 addr)
अणु
	पूर्णांक ret = 0;
	काष्ठा omap_overlay_info info;
	पूर्णांक cropheight, cropwidth, pixwidth;

	अगर ((ovl->caps & OMAP_DSS_OVL_CAP_SCALE) == 0 &&
			(outw != vout->pix.width || outh != vout->pix.height)) अणु
		ret = -EINVAL;
		जाओ setup_ovl_err;
	पूर्ण

	vout->dss_mode = video_mode_to_dss_mode(vout);
	अगर (vout->dss_mode == -EINVAL) अणु
		ret = -EINVAL;
		जाओ setup_ovl_err;
	पूर्ण

	/* Setup the input plane parameters according to
	 * rotation value selected.
	 */
	अगर (is_rotation_90_or_270(vout)) अणु
		cropheight = vout->crop.width;
		cropwidth = vout->crop.height;
		pixwidth = vout->pix.height;
	पूर्ण अन्यथा अणु
		cropheight = vout->crop.height;
		cropwidth = vout->crop.width;
		pixwidth = vout->pix.width;
	पूर्ण

	ovl->get_overlay_info(ovl, &info);
	info.paddr = addr;
	info.width = cropwidth;
	info.height = cropheight;
	info.color_mode = vout->dss_mode;
	info.mirror = vout->mirror;
	info.pos_x = posx;
	info.pos_y = posy;
	info.out_width = outw;
	info.out_height = outh;
	info.global_alpha = vout->win.global_alpha;
	अगर (!is_rotation_enabled(vout)) अणु
		info.rotation = 0;
		info.rotation_type = OMAP_DSS_ROT_DMA;
		info.screen_width = pixwidth;
	पूर्ण अन्यथा अणु
		info.rotation = vout->rotation;
		info.rotation_type = OMAP_DSS_ROT_VRFB;
		info.screen_width = 2048;
	पूर्ण

	v4l2_dbg(1, debug, &vout->vid_dev->v4l2_dev,
		"%s enable=%d addr=%pad width=%d\n height=%d color_mode=%d\n"
		"rotation=%d mirror=%d posx=%d posy=%d out_width = %d \n"
		"out_height=%d rotation_type=%d screen_width=%d\n", __func__,
		ovl->is_enabled(ovl), &info.paddr, info.width, info.height,
		info.color_mode, info.rotation, info.mirror, info.pos_x,
		info.pos_y, info.out_width, info.out_height, info.rotation_type,
		info.screen_width);

	ret = ovl->set_overlay_info(ovl, &info);
	अगर (ret)
		जाओ setup_ovl_err;

	वापस 0;

setup_ovl_err:
	v4l2_warn(&vout->vid_dev->v4l2_dev, "setup_overlay failed\n");
	वापस ret;
पूर्ण

/*
 * Initialize the overlay काष्ठाure
 */
अटल पूर्णांक omapvid_init(काष्ठा omap_vout_device *vout, u32 addr)
अणु
	पूर्णांक ret = 0, i;
	काष्ठा v4l2_winकरोw *win;
	काष्ठा omap_overlay *ovl;
	पूर्णांक posx, posy, outw, outh;
	काष्ठा omap_video_timings *timing;
	काष्ठा omapvideo_info *ovid = &vout->vid_info;

	win = &vout->win;
	क्रम (i = 0; i < ovid->num_overlays; i++) अणु
		काष्ठा omap_dss_device *dssdev;

		ovl = ovid->overlays[i];
		dssdev = ovl->get_device(ovl);

		अगर (!dssdev)
			वापस -EINVAL;

		timing = &dssdev->panel.timings;

		outw = win->w.width;
		outh = win->w.height;
		चयन (vout->rotation) अणु
		हाल dss_rotation_90_degree:
			/* Invert the height and width क्रम 90
			 * and 270 degree rotation
			 */
			swap(outw, outh);
			posy = (timing->y_res - win->w.width) - win->w.left;
			posx = win->w.top;
			अवरोध;

		हाल dss_rotation_180_degree:
			posx = (timing->x_res - win->w.width) - win->w.left;
			posy = (timing->y_res - win->w.height) - win->w.top;
			अवरोध;

		हाल dss_rotation_270_degree:
			swap(outw, outh);
			posy = win->w.left;
			posx = (timing->x_res - win->w.height) - win->w.top;
			अवरोध;

		शेष:
			posx = win->w.left;
			posy = win->w.top;
			अवरोध;
		पूर्ण

		ret = omapvid_setup_overlay(vout, ovl, posx, posy,
				outw, outh, addr);
		अगर (ret)
			जाओ omapvid_init_err;
	पूर्ण
	वापस 0;

omapvid_init_err:
	v4l2_warn(&vout->vid_dev->v4l2_dev, "apply_changes failed\n");
	वापस ret;
पूर्ण

/*
 * Apply the changes set the go bit of DSS
 */
अटल पूर्णांक omapvid_apply_changes(काष्ठा omap_vout_device *vout)
अणु
	पूर्णांक i;
	काष्ठा omap_overlay *ovl;
	काष्ठा omapvideo_info *ovid = &vout->vid_info;

	क्रम (i = 0; i < ovid->num_overlays; i++) अणु
		काष्ठा omap_dss_device *dssdev;

		ovl = ovid->overlays[i];
		dssdev = ovl->get_device(ovl);
		अगर (!dssdev)
			वापस -EINVAL;
		ovl->manager->apply(ovl->manager);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक omapvid_handle_पूर्णांकerlace_display(काष्ठा omap_vout_device *vout,
		अचिन्हित पूर्णांक irqstatus, u64 ts)
अणु
	u32 fid;

	अगर (vout->first_पूर्णांक) अणु
		vout->first_पूर्णांक = 0;
		जाओ err;
	पूर्ण

	अगर (irqstatus & DISPC_IRQ_EVSYNC_ODD)
		fid = 1;
	अन्यथा अगर (irqstatus & DISPC_IRQ_EVSYNC_EVEN)
		fid = 0;
	अन्यथा
		जाओ err;

	vout->field_id ^= 1;
	अगर (fid != vout->field_id) अणु
		अगर (fid == 0)
			vout->field_id = fid;
	पूर्ण अन्यथा अगर (0 == fid) अणु
		अगर (vout->cur_frm == vout->next_frm)
			जाओ err;

		vout->cur_frm->vbuf.vb2_buf.बारtamp = ts;
		vout->cur_frm->vbuf.sequence = vout->sequence++;
		vb2_buffer_करोne(&vout->cur_frm->vbuf.vb2_buf, VB2_BUF_STATE_DONE);
		vout->cur_frm = vout->next_frm;
	पूर्ण अन्यथा अणु
		अगर (list_empty(&vout->dma_queue) ||
				(vout->cur_frm != vout->next_frm))
			जाओ err;
	पूर्ण

	वापस vout->field_id;
err:
	वापस 0;
पूर्ण

अटल व्योम omap_vout_isr(व्योम *arg, अचिन्हित पूर्णांक irqstatus)
अणु
	पूर्णांक ret, fid, mgr_id;
	u32 addr, irq;
	काष्ठा omap_overlay *ovl;
	u64 ts;
	काष्ठा omapvideo_info *ovid;
	काष्ठा omap_dss_device *cur_display;
	काष्ठा omap_vout_device *vout = (काष्ठा omap_vout_device *)arg;

	ovid = &vout->vid_info;
	ovl = ovid->overlays[0];

	mgr_id = ovl->manager->id;

	/* get the display device attached to the overlay */
	cur_display = ovl->get_device(ovl);

	अगर (!cur_display)
		वापस;

	spin_lock(&vout->vbq_lock);
	ts = kसमय_get_ns();

	चयन (cur_display->type) अणु
	हाल OMAP_DISPLAY_TYPE_DSI:
	हाल OMAP_DISPLAY_TYPE_DPI:
	हाल OMAP_DISPLAY_TYPE_DVI:
		अगर (mgr_id == OMAP_DSS_CHANNEL_LCD)
			irq = DISPC_IRQ_VSYNC;
		अन्यथा अगर (mgr_id == OMAP_DSS_CHANNEL_LCD2)
			irq = DISPC_IRQ_VSYNC2;
		अन्यथा
			जाओ vout_isr_err;

		अगर (!(irqstatus & irq))
			जाओ vout_isr_err;
		अवरोध;
	हाल OMAP_DISPLAY_TYPE_VENC:
		fid = omapvid_handle_पूर्णांकerlace_display(vout, irqstatus,
				ts);
		अगर (!fid)
			जाओ vout_isr_err;
		अवरोध;
	हाल OMAP_DISPLAY_TYPE_HDMI:
		अगर (!(irqstatus & DISPC_IRQ_EVSYNC_EVEN))
			जाओ vout_isr_err;
		अवरोध;
	शेष:
		जाओ vout_isr_err;
	पूर्ण

	अगर (!vout->first_पूर्णांक && (vout->cur_frm != vout->next_frm)) अणु
		vout->cur_frm->vbuf.vb2_buf.बारtamp = ts;
		vout->cur_frm->vbuf.sequence = vout->sequence++;
		vb2_buffer_करोne(&vout->cur_frm->vbuf.vb2_buf, VB2_BUF_STATE_DONE);
		vout->cur_frm = vout->next_frm;
	पूर्ण

	vout->first_पूर्णांक = 0;
	अगर (list_empty(&vout->dma_queue))
		जाओ vout_isr_err;

	vout->next_frm = list_entry(vout->dma_queue.next,
			काष्ठा omap_vout_buffer, queue);
	list_del(&vout->next_frm->queue);

	addr = (अचिन्हित दीर्घ)vout->queued_buf_addr[vout->next_frm->vbuf.vb2_buf.index]
		+ vout->cropped_offset;

	/* First save the configuration in ovelray काष्ठाure */
	ret = omapvid_init(vout, addr);
	अगर (ret) अणु
		prपूर्णांकk(KERN_ERR VOUT_NAME
			"failed to set overlay info\n");
		जाओ vout_isr_err;
	पूर्ण

	/* Enable the pipeline and set the Go bit */
	ret = omapvid_apply_changes(vout);
	अगर (ret)
		prपूर्णांकk(KERN_ERR VOUT_NAME "failed to change mode\n");

vout_isr_err:
	spin_unlock(&vout->vbq_lock);
पूर्ण


/*
 * V4L2 ioctls
 */
अटल पूर्णांक vidioc_querycap(काष्ठा file *file, व्योम *fh,
		काष्ठा v4l2_capability *cap)
अणु
	काष्ठा omap_vout_device *vout = video_drvdata(file);

	strscpy(cap->driver, VOUT_NAME, माप(cap->driver));
	strscpy(cap->card, vout->vfd->name, माप(cap->card));
	snम_लिखो(cap->bus_info, माप(cap->bus_info),
		 "platform:%s.%d", VOUT_NAME, vout->vid);
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_क्रमागत_fmt_vid_out(काष्ठा file *file, व्योम *fh,
			काष्ठा v4l2_fmtdesc *fmt)
अणु
	पूर्णांक index = fmt->index;

	अगर (index >= NUM_OUTPUT_FORMATS)
		वापस -EINVAL;

	fmt->flags = omap_क्रमmats[index].flags;
	fmt->pixelक्रमmat = omap_क्रमmats[index].pixelक्रमmat;

	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_g_fmt_vid_out(काष्ठा file *file, व्योम *fh,
			काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा omap_vout_device *vout = video_drvdata(file);

	f->fmt.pix = vout->pix;
	वापस 0;

पूर्ण

अटल पूर्णांक vidioc_try_fmt_vid_out(काष्ठा file *file, व्योम *fh,
			काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा omap_overlay *ovl;
	काष्ठा omapvideo_info *ovid;
	काष्ठा omap_video_timings *timing;
	काष्ठा omap_vout_device *vout = video_drvdata(file);
	काष्ठा omap_dss_device *dssdev;

	ovid = &vout->vid_info;
	ovl = ovid->overlays[0];
	/* get the display device attached to the overlay */
	dssdev = ovl->get_device(ovl);

	अगर (!dssdev)
		वापस -EINVAL;

	timing = &dssdev->panel.timings;

	vout->fbuf.fmt.height = timing->y_res;
	vout->fbuf.fmt.width = timing->x_res;

	omap_vout_try_क्रमmat(&f->fmt.pix);
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_s_fmt_vid_out(काष्ठा file *file, व्योम *fh,
			काष्ठा v4l2_क्रमmat *f)
अणु
	पूर्णांक ret, bpp;
	काष्ठा omap_overlay *ovl;
	काष्ठा omapvideo_info *ovid;
	काष्ठा omap_video_timings *timing;
	काष्ठा omap_vout_device *vout = video_drvdata(file);
	काष्ठा omap_dss_device *dssdev;

	अगर (vb2_is_busy(&vout->vq))
		वापस -EBUSY;

	ovid = &vout->vid_info;
	ovl = ovid->overlays[0];
	dssdev = ovl->get_device(ovl);

	/* get the display device attached to the overlay */
	अगर (!dssdev) अणु
		ret = -EINVAL;
		जाओ s_fmt_vid_out_निकास;
	पूर्ण
	timing = &dssdev->panel.timings;

	/* We करोn't support RGB24-packed mode अगर vrfb rotation
	 * is enabled*/
	अगर ((is_rotation_enabled(vout)) &&
			f->fmt.pix.pixelक्रमmat == V4L2_PIX_FMT_RGB24) अणु
		ret = -EINVAL;
		जाओ s_fmt_vid_out_निकास;
	पूर्ण

	/* get the framebuffer parameters */

	अगर (is_rotation_90_or_270(vout)) अणु
		vout->fbuf.fmt.height = timing->x_res;
		vout->fbuf.fmt.width = timing->y_res;
	पूर्ण अन्यथा अणु
		vout->fbuf.fmt.height = timing->y_res;
		vout->fbuf.fmt.width = timing->x_res;
	पूर्ण

	/* change to smaller size is OK */

	bpp = omap_vout_try_क्रमmat(&f->fmt.pix);
	f->fmt.pix.sizeimage = f->fmt.pix.width * f->fmt.pix.height * bpp;

	/* try & set the new output क्रमmat */
	vout->bpp = bpp;
	vout->pix = f->fmt.pix;
	vout->vrfb_bpp = 1;

	/* If YUYV then vrfb bpp is 2, क्रम  others its 1 */
	अगर (V4L2_PIX_FMT_YUYV == vout->pix.pixelक्रमmat ||
			V4L2_PIX_FMT_UYVY == vout->pix.pixelक्रमmat)
		vout->vrfb_bpp = 2;

	/* set शेष crop and win */
	omap_vout_new_क्रमmat(&vout->pix, &vout->fbuf, &vout->crop, &vout->win);

	ret = 0;

s_fmt_vid_out_निकास:
	वापस ret;
पूर्ण

अटल पूर्णांक vidioc_try_fmt_vid_overlay(काष्ठा file *file, व्योम *fh,
			काष्ठा v4l2_क्रमmat *f)
अणु
	पूर्णांक ret = 0;
	काष्ठा omap_vout_device *vout = video_drvdata(file);
	काष्ठा omap_overlay *ovl;
	काष्ठा omapvideo_info *ovid;
	काष्ठा v4l2_winकरोw *win = &f->fmt.win;

	ovid = &vout->vid_info;
	ovl = ovid->overlays[0];

	ret = omap_vout_try_winकरोw(&vout->fbuf, win);

	अगर (!ret && !(ovl->caps & OMAP_DSS_OVL_CAP_GLOBAL_ALPHA))
		win->global_alpha = 0;

	वापस ret;
पूर्ण

अटल पूर्णांक vidioc_s_fmt_vid_overlay(काष्ठा file *file, व्योम *fh,
			काष्ठा v4l2_क्रमmat *f)
अणु
	पूर्णांक ret = 0;
	काष्ठा omap_overlay *ovl;
	काष्ठा omapvideo_info *ovid;
	काष्ठा omap_vout_device *vout = video_drvdata(file);
	काष्ठा v4l2_winकरोw *win = &f->fmt.win;

	ovid = &vout->vid_info;
	ovl = ovid->overlays[0];

	ret = omap_vout_new_winकरोw(&vout->crop, &vout->win, &vout->fbuf, win);
	अगर (!ret) अणु
		क्रमागत omap_dss_trans_key_type key_type =
			OMAP_DSS_COLOR_KEY_GFX_DST;
		पूर्णांक enable;

		/* Video1 plane करोes not support global alpha on OMAP3 */
		अगर (ovl->caps & OMAP_DSS_OVL_CAP_GLOBAL_ALPHA)
			vout->win.global_alpha = win->global_alpha;
		अन्यथा
			win->global_alpha = 0;
		अगर (vout->fbuf.flags & (V4L2_FBUF_FLAG_CHROMAKEY |
					V4L2_FBUF_FLAG_SRC_CHROMAKEY))
			enable = 1;
		अन्यथा
			enable = 0;
		अगर (vout->fbuf.flags & V4L2_FBUF_FLAG_SRC_CHROMAKEY)
			key_type = OMAP_DSS_COLOR_KEY_VID_SRC;

		अगर (ovl->manager && ovl->manager->get_manager_info &&
		    ovl->manager->set_manager_info) अणु
			काष्ठा omap_overlay_manager_info info;

			ovl->manager->get_manager_info(ovl->manager, &info);
			info.trans_enabled = enable;
			info.trans_key_type = key_type;
			info.trans_key = vout->win.chromakey;

			अगर (ovl->manager->set_manager_info(ovl->manager, &info))
				वापस -EINVAL;
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक vidioc_g_fmt_vid_overlay(काष्ठा file *file, व्योम *fh,
			काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा omap_overlay *ovl;
	काष्ठा omapvideo_info *ovid;
	काष्ठा omap_vout_device *vout = video_drvdata(file);
	काष्ठा v4l2_winकरोw *win = &f->fmt.win;

	ovid = &vout->vid_info;
	ovl = ovid->overlays[0];

	win->w = vout->win.w;
	win->field = vout->win.field;
	win->chromakey = vout->win.chromakey;
	अगर (ovl->caps & OMAP_DSS_OVL_CAP_GLOBAL_ALPHA)
		win->global_alpha = vout->win.global_alpha;
	अन्यथा
		win->global_alpha = 0;
	win->clips = शून्य;
	win->clipcount = 0;
	win->biपंचांगap = शून्य;
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_g_selection(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_selection *sel)
अणु
	काष्ठा omap_vout_device *vout = video_drvdata(file);
	काष्ठा v4l2_pix_क्रमmat *pix = &vout->pix;

	अगर (sel->type != V4L2_BUF_TYPE_VIDEO_OUTPUT)
		वापस -EINVAL;

	चयन (sel->target) अणु
	हाल V4L2_SEL_TGT_CROP:
		sel->r = vout->crop;
		अवरोध;
	हाल V4L2_SEL_TGT_CROP_DEFAULT:
		omap_vout_शेष_crop(&vout->pix, &vout->fbuf, &sel->r);
		अवरोध;
	हाल V4L2_SEL_TGT_CROP_BOUNDS:
		/* Width and height are always even */
		sel->r.width = pix->width & ~1;
		sel->r.height = pix->height & ~1;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_s_selection(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_selection *sel)
अणु
	पूर्णांक ret = -EINVAL;
	काष्ठा omap_vout_device *vout = video_drvdata(file);
	काष्ठा omapvideo_info *ovid;
	काष्ठा omap_overlay *ovl;
	काष्ठा omap_video_timings *timing;
	काष्ठा omap_dss_device *dssdev;

	अगर (sel->type != V4L2_BUF_TYPE_VIDEO_OUTPUT)
		वापस -EINVAL;

	अगर (sel->target != V4L2_SEL_TGT_CROP)
		वापस -EINVAL;

	अगर (vb2_is_busy(&vout->vq))
		वापस -EBUSY;

	ovid = &vout->vid_info;
	ovl = ovid->overlays[0];
	/* get the display device attached to the overlay */
	dssdev = ovl->get_device(ovl);

	अगर (!dssdev) अणु
		ret = -EINVAL;
		जाओ s_crop_err;
	पूर्ण

	timing = &dssdev->panel.timings;

	अगर (is_rotation_90_or_270(vout)) अणु
		vout->fbuf.fmt.height = timing->x_res;
		vout->fbuf.fmt.width = timing->y_res;
	पूर्ण अन्यथा अणु
		vout->fbuf.fmt.height = timing->y_res;
		vout->fbuf.fmt.width = timing->x_res;
	पूर्ण

	ret = omap_vout_new_crop(&vout->pix, &vout->crop, &vout->win,
				 &vout->fbuf, &sel->r);

s_crop_err:
	वापस ret;
पूर्ण

अटल पूर्णांक omap_vout_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा omap_vout_device *vout =
		container_of(ctrl->handler, काष्ठा omap_vout_device, ctrl_handler);
	पूर्णांक ret = 0;

	चयन (ctrl->id) अणु
	हाल V4L2_CID_ROTATE: अणु
		काष्ठा omapvideo_info *ovid;
		पूर्णांक rotation = ctrl->val;

		ovid = &vout->vid_info;

		अगर (rotation && ovid->rotation_type == VOUT_ROT_NONE) अणु
			ret = -दुस्फल;
			अवरोध;
		पूर्ण

		अगर (rotation && vout->pix.pixelक्रमmat == V4L2_PIX_FMT_RGB24) अणु
			ret = -EINVAL;
			अवरोध;
		पूर्ण

		अगर (v4l2_rot_to_dss_rot(rotation, &vout->rotation,
							vout->mirror)) अणु
			ret = -EINVAL;
			अवरोध;
		पूर्ण
		अवरोध;
	पूर्ण
	हाल V4L2_CID_BG_COLOR:
	अणु
		काष्ठा omap_overlay *ovl;
		अचिन्हित पूर्णांक color = ctrl->val;
		काष्ठा omap_overlay_manager_info info;

		ovl = vout->vid_info.overlays[0];

		अगर (!ovl->manager || !ovl->manager->get_manager_info) अणु
			ret = -EINVAL;
			अवरोध;
		पूर्ण

		ovl->manager->get_manager_info(ovl->manager, &info);
		info.शेष_color = color;
		अगर (ovl->manager->set_manager_info(ovl->manager, &info)) अणु
			ret = -EINVAL;
			अवरोध;
		पूर्ण
		अवरोध;
	पूर्ण
	हाल V4L2_CID_VFLIP:
	अणु
		काष्ठा omapvideo_info *ovid;
		अचिन्हित पूर्णांक mirror = ctrl->val;

		ovid = &vout->vid_info;

		अगर (mirror && ovid->rotation_type == VOUT_ROT_NONE) अणु
			ret = -दुस्फल;
			अवरोध;
		पूर्ण

		अगर (mirror  && vout->pix.pixelक्रमmat == V4L2_PIX_FMT_RGB24) अणु
			ret = -EINVAL;
			अवरोध;
		पूर्ण
		vout->mirror = mirror;
		अवरोध;
	पूर्ण
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops omap_vout_ctrl_ops = अणु
	.s_ctrl = omap_vout_s_ctrl,
पूर्ण;

अटल पूर्णांक omap_vout_vb2_queue_setup(काष्ठा vb2_queue *vq,
				     अचिन्हित पूर्णांक *nbufs,
				     अचिन्हित पूर्णांक *num_planes, अचिन्हित पूर्णांक sizes[],
				     काष्ठा device *alloc_devs[])
अणु
	काष्ठा omap_vout_device *vout = vb2_get_drv_priv(vq);
	पूर्णांक size = vout->pix.sizeimage;

	अगर (is_rotation_enabled(vout) && vq->num_buffers + *nbufs > VRFB_NUM_BUFS) अणु
		*nbufs = VRFB_NUM_BUFS - vq->num_buffers;
		अगर (*nbufs == 0)
			वापस -EINVAL;
	पूर्ण

	अगर (*num_planes)
		वापस sizes[0] < size ? -EINVAL : 0;

	*num_planes = 1;
	sizes[0] = size;
	वापस 0;
पूर्ण

अटल पूर्णांक omap_vout_vb2_prepare(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा omap_vout_device *vout = vb2_get_drv_priv(vb->vb2_queue);
	काष्ठा omapvideo_info *ovid = &vout->vid_info;
	काष्ठा omap_vout_buffer *voutbuf = vb2_to_omap_vout_buffer(vb);
	dma_addr_t buf_phy_addr = vb2_dma_contig_plane_dma_addr(vb, 0);

	अगर (vb2_plane_size(vb, 0) < vout->pix.sizeimage) अणु
		v4l2_dbg(1, debug, &vout->vid_dev->v4l2_dev,
			 "%s data will not fit into plane (%lu < %u)\n",
			__func__, vb2_plane_size(vb, 0), vout->pix.sizeimage);
		वापस -EINVAL;
	पूर्ण

	vb2_set_plane_payload(vb, 0, vout->pix.sizeimage);
	voutbuf->vbuf.field = V4L2_FIELD_NONE;

	vout->queued_buf_addr[vb->index] = (u8 *)buf_phy_addr;
	अगर (ovid->rotation_type == VOUT_ROT_VRFB)
		वापस omap_vout_prepare_vrfb(vout, vb);
	वापस 0;
पूर्ण

अटल व्योम omap_vout_vb2_queue(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा omap_vout_device *vout = vb2_get_drv_priv(vb->vb2_queue);
	काष्ठा omap_vout_buffer *voutbuf = vb2_to_omap_vout_buffer(vb);

	list_add_tail(&voutbuf->queue, &vout->dma_queue);
पूर्ण

अटल पूर्णांक omap_vout_vb2_start_streaming(काष्ठा vb2_queue *vq, अचिन्हित पूर्णांक count)
अणु
	काष्ठा omap_vout_device *vout = vb2_get_drv_priv(vq);
	काष्ठा omapvideo_info *ovid = &vout->vid_info;
	काष्ठा omap_vout_buffer *buf, *पंचांगp;
	u32 addr = 0, mask = 0;
	पूर्णांक ret, j;

	/* Get the next frame from the buffer queue */
	vout->next_frm = vout->cur_frm = list_entry(vout->dma_queue.next,
			काष्ठा omap_vout_buffer, queue);
	/* Remove buffer from the buffer queue */
	list_del(&vout->cur_frm->queue);
	/* Initialize field_id and started member */
	vout->field_id = 0;
	vout->first_पूर्णांक = 1;
	vout->sequence = 0;

	अगर (omap_vout_calculate_offset(vout)) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण
	अगर (ovid->rotation_type == VOUT_ROT_VRFB)
		अगर (omap_vout_vrfb_buffer_setup(vout, &count, 0)) अणु
			ret = -ENOMEM;
			जाओ out;
		पूर्ण

	addr = (अचिन्हित दीर्घ)vout->queued_buf_addr[vout->cur_frm->vbuf.vb2_buf.index]
		+ vout->cropped_offset;

	mask = DISPC_IRQ_VSYNC | DISPC_IRQ_EVSYNC_EVEN | DISPC_IRQ_EVSYNC_ODD
		| DISPC_IRQ_VSYNC2;

	/* First save the configuration in overlay काष्ठाure */
	ret = omapvid_init(vout, addr);
	अगर (ret) अणु
		v4l2_err(&vout->vid_dev->v4l2_dev,
				"failed to set overlay info\n");
		जाओ streamon_err1;
	पूर्ण

	omap_dispc_रेजिस्टर_isr(omap_vout_isr, vout, mask);

	/* Enable the pipeline and set the Go bit */
	ret = omapvid_apply_changes(vout);
	अगर (ret)
		v4l2_err(&vout->vid_dev->v4l2_dev, "failed to change mode\n");

	क्रम (j = 0; j < ovid->num_overlays; j++) अणु
		काष्ठा omap_overlay *ovl = ovid->overlays[j];
		काष्ठा omap_dss_device *dssdev = ovl->get_device(ovl);

		अगर (dssdev) अणु
			ret = ovl->enable(ovl);
			अगर (ret)
				जाओ streamon_err1;
		पूर्ण
	पूर्ण
	वापस 0;

streamon_err1:
	mask = DISPC_IRQ_VSYNC | DISPC_IRQ_EVSYNC_EVEN | DISPC_IRQ_EVSYNC_ODD
		| DISPC_IRQ_VSYNC2;

	omap_dispc_unरेजिस्टर_isr(omap_vout_isr, vout, mask);

	क्रम (j = 0; j < ovid->num_overlays; j++) अणु
		काष्ठा omap_overlay *ovl = ovid->overlays[j];
		काष्ठा omap_dss_device *dssdev = ovl->get_device(ovl);

		अगर (dssdev)
			ovl->disable(ovl);
	पूर्ण
	/* Turn of the pipeline */
	अगर (omapvid_apply_changes(vout))
		v4l2_err(&vout->vid_dev->v4l2_dev,
			 "failed to change mode in streamoff\n");

out:
	vb2_buffer_करोne(&vout->cur_frm->vbuf.vb2_buf, VB2_BUF_STATE_QUEUED);
	list_क्रम_each_entry_safe(buf, पंचांगp, &vout->dma_queue, queue) अणु
		list_del(&buf->queue);
		vb2_buffer_करोne(&buf->vbuf.vb2_buf, VB2_BUF_STATE_QUEUED);
	पूर्ण
	वापस ret;
पूर्ण

अटल व्योम omap_vout_vb2_stop_streaming(काष्ठा vb2_queue *vq)
अणु
	काष्ठा omap_vout_device *vout = vb2_get_drv_priv(vq);
	काष्ठा omapvideo_info *ovid = &vout->vid_info;
	काष्ठा omap_vout_buffer *buf, *पंचांगp;
	u32 mask = 0;
	पूर्णांक j;

	mask = DISPC_IRQ_VSYNC | DISPC_IRQ_EVSYNC_EVEN | DISPC_IRQ_EVSYNC_ODD
		| DISPC_IRQ_VSYNC2;

	omap_dispc_unरेजिस्टर_isr(omap_vout_isr, vout, mask);

	क्रम (j = 0; j < ovid->num_overlays; j++) अणु
		काष्ठा omap_overlay *ovl = ovid->overlays[j];
		काष्ठा omap_dss_device *dssdev = ovl->get_device(ovl);

		अगर (dssdev)
			ovl->disable(ovl);
	पूर्ण
	/* Turn of the pipeline */
	अगर (omapvid_apply_changes(vout))
		v4l2_err(&vout->vid_dev->v4l2_dev,
			 "failed to change mode in streamoff\n");

	अगर (vout->next_frm != vout->cur_frm)
		vb2_buffer_करोne(&vout->next_frm->vbuf.vb2_buf, VB2_BUF_STATE_ERROR);
	vb2_buffer_करोne(&vout->cur_frm->vbuf.vb2_buf, VB2_BUF_STATE_ERROR);
	list_क्रम_each_entry_safe(buf, पंचांगp, &vout->dma_queue, queue) अणु
		list_del(&buf->queue);
		vb2_buffer_करोne(&buf->vbuf.vb2_buf, VB2_BUF_STATE_ERROR);
	पूर्ण
पूर्ण

अटल पूर्णांक vidioc_s_fbuf(काष्ठा file *file, व्योम *fh,
				स्थिर काष्ठा v4l2_framebuffer *a)
अणु
	पूर्णांक enable = 0;
	काष्ठा omap_overlay *ovl;
	काष्ठा omapvideo_info *ovid;
	काष्ठा omap_vout_device *vout = video_drvdata(file);
	काष्ठा omap_overlay_manager_info info;
	क्रमागत omap_dss_trans_key_type key_type = OMAP_DSS_COLOR_KEY_GFX_DST;

	ovid = &vout->vid_info;
	ovl = ovid->overlays[0];

	/* OMAP DSS करोesn't support Source and Destination color
	   key together */
	अगर ((a->flags & V4L2_FBUF_FLAG_SRC_CHROMAKEY) &&
			(a->flags & V4L2_FBUF_FLAG_CHROMAKEY))
		वापस -EINVAL;
	/* OMAP DSS Doesn't support the Destination color key
	   and alpha blending together */
	अगर ((a->flags & V4L2_FBUF_FLAG_CHROMAKEY) &&
			(a->flags & V4L2_FBUF_FLAG_LOCAL_ALPHA))
		वापस -EINVAL;

	अगर ((a->flags & V4L2_FBUF_FLAG_SRC_CHROMAKEY)) अणु
		vout->fbuf.flags |= V4L2_FBUF_FLAG_SRC_CHROMAKEY;
		key_type =  OMAP_DSS_COLOR_KEY_VID_SRC;
	पूर्ण अन्यथा
		vout->fbuf.flags &= ~V4L2_FBUF_FLAG_SRC_CHROMAKEY;

	अगर ((a->flags & V4L2_FBUF_FLAG_CHROMAKEY)) अणु
		vout->fbuf.flags |= V4L2_FBUF_FLAG_CHROMAKEY;
		key_type =  OMAP_DSS_COLOR_KEY_GFX_DST;
	पूर्ण अन्यथा
		vout->fbuf.flags &=  ~V4L2_FBUF_FLAG_CHROMAKEY;

	अगर (a->flags & (V4L2_FBUF_FLAG_CHROMAKEY |
				V4L2_FBUF_FLAG_SRC_CHROMAKEY))
		enable = 1;
	अन्यथा
		enable = 0;
	अगर (ovl->manager && ovl->manager->get_manager_info &&
			ovl->manager->set_manager_info) अणु

		ovl->manager->get_manager_info(ovl->manager, &info);
		info.trans_enabled = enable;
		info.trans_key_type = key_type;
		info.trans_key = vout->win.chromakey;

		अगर (ovl->manager->set_manager_info(ovl->manager, &info))
			वापस -EINVAL;
	पूर्ण
	अगर (a->flags & V4L2_FBUF_FLAG_LOCAL_ALPHA) अणु
		vout->fbuf.flags |= V4L2_FBUF_FLAG_LOCAL_ALPHA;
		enable = 1;
	पूर्ण अन्यथा अणु
		vout->fbuf.flags &= ~V4L2_FBUF_FLAG_LOCAL_ALPHA;
		enable = 0;
	पूर्ण
	अगर (ovl->manager && ovl->manager->get_manager_info &&
			ovl->manager->set_manager_info) अणु
		ovl->manager->get_manager_info(ovl->manager, &info);
		/* enable this only अगर there is no zorder cap */
		अगर ((ovl->caps & OMAP_DSS_OVL_CAP_ZORDER) == 0)
			info.partial_alpha_enabled = enable;
		अगर (ovl->manager->set_manager_info(ovl->manager, &info))
			वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_g_fbuf(काष्ठा file *file, व्योम *fh,
		काष्ठा v4l2_framebuffer *a)
अणु
	काष्ठा omap_overlay *ovl;
	काष्ठा omapvideo_info *ovid;
	काष्ठा omap_vout_device *vout = video_drvdata(file);
	काष्ठा omap_overlay_manager_info info;
	काष्ठा omap_video_timings *timing;
	काष्ठा omap_dss_device *dssdev;

	ovid = &vout->vid_info;
	ovl = ovid->overlays[0];
	/* get the display device attached to the overlay */
	dssdev = ovl->get_device(ovl);

	अगर (!dssdev)
		वापस -EINVAL;

	timing = &dssdev->panel.timings;

	vout->fbuf.fmt.height = timing->y_res;
	vout->fbuf.fmt.width = timing->x_res;
	a->fmt.field = V4L2_FIELD_NONE;
	a->fmt.colorspace = V4L2_COLORSPACE_SRGB;
	a->fmt.pixelक्रमmat = V4L2_PIX_FMT_RGBA32;
	a->fmt.height = vout->fbuf.fmt.height;
	a->fmt.width = vout->fbuf.fmt.width;
	a->fmt.bytesperline = vout->fbuf.fmt.width * 4;
	a->fmt.sizeimage = a->fmt.height * a->fmt.bytesperline;
	a->base = vout->fbuf.base;

	a->flags = vout->fbuf.flags;
	a->capability = vout->fbuf.capability;
	a->flags &= ~(V4L2_FBUF_FLAG_SRC_CHROMAKEY | V4L2_FBUF_FLAG_CHROMAKEY |
		      V4L2_FBUF_FLAG_LOCAL_ALPHA);

	अगर (ovl->manager && ovl->manager->get_manager_info) अणु
		ovl->manager->get_manager_info(ovl->manager, &info);
		अगर (info.trans_key_type == OMAP_DSS_COLOR_KEY_VID_SRC)
			a->flags |= V4L2_FBUF_FLAG_SRC_CHROMAKEY;
		अगर (info.trans_key_type == OMAP_DSS_COLOR_KEY_GFX_DST)
			a->flags |= V4L2_FBUF_FLAG_CHROMAKEY;
		अगर (info.partial_alpha_enabled)
			a->flags |= V4L2_FBUF_FLAG_LOCAL_ALPHA;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_क्रमागत_output(काष्ठा file *file, व्योम *priv_fh,
			      काष्ठा v4l2_output *out)
अणु
	अगर (out->index)
		वापस -EINVAL;
	snम_लिखो(out->name, माप(out->name), "Overlay");
	out->type = V4L2_OUTPUT_TYPE_ANALOGVGAOVERLAY;
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_g_output(काष्ठा file *file, व्योम *priv_fh, अचिन्हित पूर्णांक *i)
अणु
	*i = 0;
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_s_output(काष्ठा file *file, व्योम *priv_fh, अचिन्हित पूर्णांक i)
अणु
	वापस i ? -EINVAL : 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_ioctl_ops vout_ioctl_ops = अणु
	.vidioc_querycap			= vidioc_querycap,
	.vidioc_क्रमागत_fmt_vid_out		= vidioc_क्रमागत_fmt_vid_out,
	.vidioc_g_fmt_vid_out			= vidioc_g_fmt_vid_out,
	.vidioc_try_fmt_vid_out			= vidioc_try_fmt_vid_out,
	.vidioc_s_fmt_vid_out			= vidioc_s_fmt_vid_out,
	.vidioc_s_fbuf				= vidioc_s_fbuf,
	.vidioc_g_fbuf				= vidioc_g_fbuf,
	.vidioc_try_fmt_vid_out_overlay		= vidioc_try_fmt_vid_overlay,
	.vidioc_s_fmt_vid_out_overlay		= vidioc_s_fmt_vid_overlay,
	.vidioc_g_fmt_vid_out_overlay		= vidioc_g_fmt_vid_overlay,
	.vidioc_g_selection			= vidioc_g_selection,
	.vidioc_s_selection			= vidioc_s_selection,
	.vidioc_क्रमागत_output			= vidioc_क्रमागत_output,
	.vidioc_g_output			= vidioc_g_output,
	.vidioc_s_output			= vidioc_s_output,
	.vidioc_reqbufs				= vb2_ioctl_reqbufs,
	.vidioc_create_bufs			= vb2_ioctl_create_bufs,
	.vidioc_querybuf			= vb2_ioctl_querybuf,
	.vidioc_qbuf				= vb2_ioctl_qbuf,
	.vidioc_dqbuf				= vb2_ioctl_dqbuf,
	.vidioc_expbuf				= vb2_ioctl_expbuf,
	.vidioc_streamon			= vb2_ioctl_streamon,
	.vidioc_streamoff			= vb2_ioctl_streamoff,
	.vidioc_subscribe_event			= v4l2_ctrl_subscribe_event,
	.vidioc_unsubscribe_event		= v4l2_event_unsubscribe,
पूर्ण;

अटल स्थिर काष्ठा v4l2_file_operations omap_vout_fops = अणु
	.owner		= THIS_MODULE,
	.unlocked_ioctl	= video_ioctl2,
	.poll		= vb2_fop_poll,
	.mmap		= vb2_fop_mmap,
	.खोलो		= v4l2_fh_खोलो,
	.release	= vb2_fop_release,
पूर्ण;

अटल स्थिर काष्ठा vb2_ops omap_vout_vb2_ops = अणु
	.queue_setup		= omap_vout_vb2_queue_setup,
	.buf_queue		= omap_vout_vb2_queue,
	.buf_prepare		= omap_vout_vb2_prepare,
	.start_streaming	= omap_vout_vb2_start_streaming,
	.stop_streaming		= omap_vout_vb2_stop_streaming,
	.रुको_prepare		= vb2_ops_रुको_prepare,
	.रुको_finish		= vb2_ops_रुको_finish,
पूर्ण;

/* Init functions used during driver initialization */
/* Initial setup of video_data */
अटल पूर्णांक __init omap_vout_setup_video_data(काष्ठा omap_vout_device *vout)
अणु
	काष्ठा video_device *vfd;
	काष्ठा v4l2_pix_क्रमmat *pix;
	काष्ठा omap_overlay *ovl = vout->vid_info.overlays[0];
	काष्ठा omap_dss_device *display = ovl->get_device(ovl);
	काष्ठा v4l2_ctrl_handler *hdl;
	काष्ठा vb2_queue *vq;
	पूर्णांक ret;

	/* set the शेष pix */
	pix = &vout->pix;

	/* Set the शेष picture of QVGA  */
	pix->width = QQVGA_WIDTH;
	pix->height = QQVGA_HEIGHT;

	/* Default pixel क्रमmat is RGB 5-6-5 */
	pix->pixelक्रमmat = V4L2_PIX_FMT_RGB565;
	pix->field = V4L2_FIELD_NONE;
	pix->bytesperline = pix->width * 2;
	pix->sizeimage = pix->bytesperline * pix->height;
	pix->colorspace = V4L2_COLORSPACE_SRGB;

	vout->bpp = RGB565_BPP;
	vout->fbuf.fmt.width  =  display->panel.timings.x_res;
	vout->fbuf.fmt.height =  display->panel.timings.y_res;
	vout->cropped_offset = 0;

	/* Set the data काष्ठाures क्रम the overlay parameters*/
	vout->fbuf.flags = V4L2_FBUF_FLAG_OVERLAY;
	vout->fbuf.capability = V4L2_FBUF_CAP_LOCAL_ALPHA |
		V4L2_FBUF_CAP_SRC_CHROMAKEY | V4L2_FBUF_CAP_CHROMAKEY |
		V4L2_FBUF_CAP_EXTERNOVERLAY;
	अगर (ovl->caps & OMAP_DSS_OVL_CAP_GLOBAL_ALPHA) अणु
		vout->win.global_alpha = 255;
		vout->fbuf.capability |= V4L2_FBUF_CAP_GLOBAL_ALPHA;
		vout->fbuf.flags |= V4L2_FBUF_FLAG_GLOBAL_ALPHA;
	पूर्ण अन्यथा अणु
		vout->win.global_alpha = 0;
	पूर्ण
	vout->win.field = V4L2_FIELD_NONE;

	omap_vout_new_क्रमmat(pix, &vout->fbuf, &vout->crop, &vout->win);

	hdl = &vout->ctrl_handler;
	v4l2_ctrl_handler_init(hdl, 3);
	अगर (vout->vid_info.rotation_type == VOUT_ROT_VRFB) अणु
		v4l2_ctrl_new_std(hdl, &omap_vout_ctrl_ops,
				  V4L2_CID_ROTATE, 0, 270, 90, 0);
		v4l2_ctrl_new_std(hdl, &omap_vout_ctrl_ops,
				  V4L2_CID_VFLIP, 0, 1, 1, 0);
	पूर्ण
	v4l2_ctrl_new_std(hdl, &omap_vout_ctrl_ops,
			  V4L2_CID_BG_COLOR, 0, 0xffffff, 1, 0);
	अगर (hdl->error)
		वापस hdl->error;

	vout->rotation = 0;
	vout->mirror = false;
	INIT_LIST_HEAD(&vout->dma_queue);
	अगर (vout->vid_info.rotation_type == VOUT_ROT_VRFB)
		vout->vrfb_bpp = 2;

	/* initialize the video_device काष्ठा */
	vfd = vout->vfd = video_device_alloc();

	अगर (!vfd) अणु
		prपूर्णांकk(KERN_ERR VOUT_NAME
		       ": could not allocate video device struct\n");
		v4l2_ctrl_handler_मुक्त(hdl);
		वापस -ENOMEM;
	पूर्ण
	vfd->ctrl_handler = hdl;
	vfd->release = video_device_release;
	vfd->ioctl_ops = &vout_ioctl_ops;

	strscpy(vfd->name, VOUT_NAME, माप(vfd->name));

	vfd->fops = &omap_vout_fops;
	vfd->v4l2_dev = &vout->vid_dev->v4l2_dev;
	vfd->vfl_dir = VFL_सूची_TX;
	vfd->minor = -1;
	vfd->device_caps = V4L2_CAP_STREAMING | V4L2_CAP_VIDEO_OUTPUT |
			   V4L2_CAP_VIDEO_OUTPUT_OVERLAY;
	mutex_init(&vout->lock);

	vq = &vout->vq;
	vq->type = V4L2_BUF_TYPE_VIDEO_OUTPUT;
	vq->io_modes = VB2_MMAP | VB2_DMABUF;
	vq->drv_priv = vout;
	vq->बारtamp_flags = V4L2_BUF_FLAG_TIMESTAMP_MONOTONIC;
	vq->buf_काष्ठा_size = माप(काष्ठा omap_vout_buffer);
	vq->dev = vfd->v4l2_dev->dev;

	vq->ops = &omap_vout_vb2_ops;
	vq->mem_ops = &vb2_dma_contig_memops;
	vq->lock = &vout->lock;
	vq->min_buffers_needed = 1;
	vfd->queue = vq;

	ret = vb2_queue_init(vq);
	अगर (ret) अणु
		v4l2_ctrl_handler_मुक्त(hdl);
		video_device_release(vfd);
	पूर्ण
	वापस ret;
पूर्ण

/* Setup video buffers */
अटल पूर्णांक __init omap_vout_setup_video_bufs(काष्ठा platक्रमm_device *pdev,
		पूर्णांक vid_num)
अणु
	काष्ठा omapvideo_info *ovid;
	काष्ठा omap_vout_device *vout;
	काष्ठा v4l2_device *v4l2_dev = platक्रमm_get_drvdata(pdev);
	काष्ठा omap2video_device *vid_dev =
		container_of(v4l2_dev, काष्ठा omap2video_device, v4l2_dev);
	पूर्णांक ret = 0;

	vout = vid_dev->vouts[vid_num];
	ovid = &vout->vid_info;

	अगर (ovid->rotation_type == VOUT_ROT_VRFB) अणु
		bool अटल_vrfb_allocation = (vid_num == 0) ?
			vid1_अटल_vrfb_alloc : vid2_अटल_vrfb_alloc;
		ret = omap_vout_setup_vrfb_bufs(pdev, vid_num,
				अटल_vrfb_allocation);
	पूर्ण
	वापस ret;
पूर्ण

/* Create video out devices */
अटल पूर्णांक __init omap_vout_create_video_devices(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret = 0, k;
	काष्ठा omap_vout_device *vout;
	काष्ठा video_device *vfd = शून्य;
	काष्ठा v4l2_device *v4l2_dev = platक्रमm_get_drvdata(pdev);
	काष्ठा omap2video_device *vid_dev = container_of(v4l2_dev,
			काष्ठा omap2video_device, v4l2_dev);
	काष्ठा omap_overlay *ovl = vid_dev->overlays[0];
	काष्ठा omap_overlay_info info;

	ovl->get_overlay_info(ovl, &info);

	क्रम (k = 0; k < pdev->num_resources; k++) अणु

		vout = kzalloc(माप(काष्ठा omap_vout_device), GFP_KERNEL);
		अगर (!vout) अणु
			dev_err(&pdev->dev, ": could not allocate memory\n");
			वापस -ENOMEM;
		पूर्ण

		vout->vid = k;
		vid_dev->vouts[k] = vout;
		vout->vid_dev = vid_dev;
		/* Select video2 अगर only 1 overlay is controlled by V4L2 */
		अगर (pdev->num_resources == 1)
			vout->vid_info.overlays[0] = vid_dev->overlays[k + 2];
		अन्यथा
			/* Else select video1 and video2 one by one. */
			vout->vid_info.overlays[0] = vid_dev->overlays[k + 1];
		vout->vid_info.num_overlays = 1;
		vout->vid_info.id = k + 1;
		spin_lock_init(&vout->vbq_lock);
		/*
		 * Set the framebuffer base, this allows applications to find
		 * the fb corresponding to this overlay.
		 *
		 * To be precise: fbuf.base should match smem_start of
		 * काष्ठा fb_fix_screeninfo.
		 */
		vout->fbuf.base = (व्योम *)info.paddr;

		/* Set VRFB as rotation_type क्रम omap2 and omap3 */
		अगर (omap_vout_dss_omap24xx() || omap_vout_dss_omap34xx())
			vout->vid_info.rotation_type = VOUT_ROT_VRFB;

		/* Setup the शेष configuration क्रम the video devices
		 */
		अगर (omap_vout_setup_video_data(vout) != 0) अणु
			ret = -ENOMEM;
			जाओ error;
		पूर्ण

		/* Allocate शेष number of buffers क्रम the video streaming
		 * and reserve the VRFB space क्रम rotation
		 */
		अगर (omap_vout_setup_video_bufs(pdev, k) != 0) अणु
			ret = -ENOMEM;
			जाओ error1;
		पूर्ण

		/* Register the Video device with V4L2
		 */
		vfd = vout->vfd;
		अगर (video_रेजिस्टर_device(vfd, VFL_TYPE_VIDEO, -1) < 0) अणु
			dev_err(&pdev->dev,
				": Could not register Video for Linux device\n");
			vfd->minor = -1;
			ret = -ENODEV;
			जाओ error2;
		पूर्ण
		video_set_drvdata(vfd, vout);

		dev_info(&pdev->dev,
			 ": registered and initialized video device %d\n",
			 vfd->minor);
		अगर (k == (pdev->num_resources - 1))
			वापस 0;

		जारी;
error2:
		अगर (vout->vid_info.rotation_type == VOUT_ROT_VRFB)
			omap_vout_release_vrfb(vout);
error1:
		video_device_release(vfd);
error:
		kमुक्त(vout);
		वापस ret;
	पूर्ण

	वापस -ENODEV;
पूर्ण
/* Driver functions */
अटल व्योम omap_vout_cleanup_device(काष्ठा omap_vout_device *vout)
अणु
	काष्ठा video_device *vfd;
	काष्ठा omapvideo_info *ovid;

	अगर (!vout)
		वापस;

	vfd = vout->vfd;
	ovid = &vout->vid_info;
	अगर (vfd) अणु
		अगर (!video_is_रेजिस्टरed(vfd)) अणु
			/*
			 * The device was never रेजिस्टरed, so release the
			 * video_device काष्ठा directly.
			 */
			video_device_release(vfd);
		पूर्ण अन्यथा अणु
			/*
			 * The unरेजिस्टर function will release the video_device
			 * काष्ठा as well as unरेजिस्टरing it.
			 */
			video_unरेजिस्टर_device(vfd);
		पूर्ण
	पूर्ण
	v4l2_ctrl_handler_मुक्त(&vout->ctrl_handler);
	अगर (ovid->rotation_type == VOUT_ROT_VRFB) अणु
		omap_vout_release_vrfb(vout);
		/* Free the VRFB buffer अगर allocated
		 * init समय
		 */
		अगर (vout->vrfb_अटल_allocation)
			omap_vout_मुक्त_vrfb_buffers(vout);
	पूर्ण

	kमुक्त(vout);
पूर्ण

अटल पूर्णांक omap_vout_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक k;
	काष्ठा v4l2_device *v4l2_dev = platक्रमm_get_drvdata(pdev);
	काष्ठा omap2video_device *vid_dev = container_of(v4l2_dev, काष्ठा
			omap2video_device, v4l2_dev);

	v4l2_device_unरेजिस्टर(v4l2_dev);
	क्रम (k = 0; k < pdev->num_resources; k++)
		omap_vout_cleanup_device(vid_dev->vouts[k]);

	क्रम (k = 0; k < vid_dev->num_displays; k++) अणु
		अगर (vid_dev->displays[k]->state != OMAP_DSS_DISPLAY_DISABLED)
			vid_dev->displays[k]->driver->disable(vid_dev->displays[k]);

		omap_dss_put_device(vid_dev->displays[k]);
	पूर्ण
	kमुक्त(vid_dev);
	वापस 0;
पूर्ण

अटल पूर्णांक __init omap_vout_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret = 0, i;
	काष्ठा omap_overlay *ovl;
	काष्ठा omap_dss_device *dssdev = शून्य;
	काष्ठा omap_dss_device *def_display;
	काष्ठा omap2video_device *vid_dev = शून्य;

	अगर (omapdss_is_initialized() == false)
		वापस -EPROBE_DEFER;

	ret = omapdss_compat_init();
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to init dss\n");
		वापस ret;
	पूर्ण

	अगर (pdev->num_resources == 0) अणु
		dev_err(&pdev->dev, "probed for an unknown device\n");
		ret = -ENODEV;
		जाओ err_dss_init;
	पूर्ण

	vid_dev = kzalloc(माप(काष्ठा omap2video_device), GFP_KERNEL);
	अगर (vid_dev == शून्य) अणु
		ret = -ENOMEM;
		जाओ err_dss_init;
	पूर्ण

	vid_dev->num_displays = 0;
	क्रम_each_dss_dev(dssdev) अणु
		omap_dss_get_device(dssdev);

		अगर (!dssdev->driver) अणु
			dev_warn(&pdev->dev, "no driver for display: %s\n",
					dssdev->name);
			omap_dss_put_device(dssdev);
			जारी;
		पूर्ण

		vid_dev->displays[vid_dev->num_displays++] = dssdev;
	पूर्ण

	अगर (vid_dev->num_displays == 0) अणु
		dev_err(&pdev->dev, "no displays\n");
		ret = -EINVAL;
		जाओ probe_err0;
	पूर्ण

	vid_dev->num_overlays = omap_dss_get_num_overlays();
	क्रम (i = 0; i < vid_dev->num_overlays; i++)
		vid_dev->overlays[i] = omap_dss_get_overlay(i);

	vid_dev->num_managers = omap_dss_get_num_overlay_managers();
	क्रम (i = 0; i < vid_dev->num_managers; i++)
		vid_dev->managers[i] = omap_dss_get_overlay_manager(i);

	/* Get the Video1 overlay and video2 overlay.
	 * Setup the Display attached to that overlays
	 */
	क्रम (i = 1; i < vid_dev->num_overlays; i++) अणु
		ovl = omap_dss_get_overlay(i);
		dssdev = ovl->get_device(ovl);

		अगर (dssdev) अणु
			def_display = dssdev;
		पूर्ण अन्यथा अणु
			dev_warn(&pdev->dev, "cannot find display\n");
			def_display = शून्य;
		पूर्ण
		अगर (def_display) अणु
			काष्ठा omap_dss_driver *dssdrv = def_display->driver;

			ret = dssdrv->enable(def_display);
			अगर (ret) अणु
				/* Here we are not considering a error
				 *  as display may be enabled by frame
				 *  buffer driver
				 */
				dev_warn(&pdev->dev,
					"'%s' Display already enabled\n",
					def_display->name);
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (v4l2_device_रेजिस्टर(&pdev->dev, &vid_dev->v4l2_dev) < 0) अणु
		dev_err(&pdev->dev, "v4l2_device_register failed\n");
		ret = -ENODEV;
		जाओ probe_err1;
	पूर्ण

	ret = omap_vout_create_video_devices(pdev);
	अगर (ret)
		जाओ probe_err2;

	क्रम (i = 0; i < vid_dev->num_displays; i++) अणु
		काष्ठा omap_dss_device *display = vid_dev->displays[i];

		अगर (display->driver->update)
			display->driver->update(display, 0, 0,
					display->panel.timings.x_res,
					display->panel.timings.y_res);
	पूर्ण
	वापस 0;

probe_err2:
	v4l2_device_unरेजिस्टर(&vid_dev->v4l2_dev);
probe_err1:
	क्रम (i = 1; i < vid_dev->num_overlays; i++) अणु
		def_display = शून्य;
		ovl = omap_dss_get_overlay(i);
		dssdev = ovl->get_device(ovl);

		अगर (dssdev)
			def_display = dssdev;

		अगर (def_display && def_display->driver)
			def_display->driver->disable(def_display);
	पूर्ण
probe_err0:
	kमुक्त(vid_dev);
err_dss_init:
	omapdss_compat_uninit();
	वापस ret;
पूर्ण

अटल काष्ठा platक्रमm_driver omap_vout_driver = अणु
	.driver = अणु
		.name = VOUT_NAME,
	पूर्ण,
	.हटाओ = omap_vout_हटाओ,
पूर्ण;

अटल पूर्णांक __init omap_vout_init(व्योम)
अणु
	अगर (platक्रमm_driver_probe(&omap_vout_driver, omap_vout_probe) != 0) अणु
		prपूर्णांकk(KERN_ERR VOUT_NAME ":Could not register Video driver\n");
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम omap_vout_cleanup(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&omap_vout_driver);
पूर्ण

late_initcall(omap_vout_init);
module_निकास(omap_vout_cleanup);
