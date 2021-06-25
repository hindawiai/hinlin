<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * vivid-kthपढ़ो-cap.h - video/vbi capture thपढ़ो support functions.
 *
 * Copyright 2014 Cisco Systems, Inc. and/or its affiliates. All rights reserved.
 */

#समावेश <linux/module.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/font.h>
#समावेश <linux/mutex.h>
#समावेश <linux/videodev2.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/मुक्तzer.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/v4l2-dv-timings.h>
#समावेश <यंत्र/भाग64.h>
#समावेश <media/videobuf2-vदो_स्मृति.h>
#समावेश <media/v4l2-dv-timings.h>
#समावेश <media/v4l2-ioctl.h>
#समावेश <media/v4l2-fh.h>
#समावेश <media/v4l2-event.h>
#समावेश <media/v4l2-rect.h>

#समावेश "vivid-core.h"
#समावेश "vivid-vid-common.h"
#समावेश "vivid-vid-cap.h"
#समावेश "vivid-vid-out.h"
#समावेश "vivid-radio-common.h"
#समावेश "vivid-radio-rx.h"
#समावेश "vivid-radio-tx.h"
#समावेश "vivid-sdr-cap.h"
#समावेश "vivid-vbi-cap.h"
#समावेश "vivid-vbi-out.h"
#समावेश "vivid-osd.h"
#समावेश "vivid-ctrls.h"
#समावेश "vivid-kthread-cap.h"
#समावेश "vivid-meta-cap.h"

अटल अंतरभूत v4l2_std_id vivid_get_std_cap(स्थिर काष्ठा vivid_dev *dev)
अणु
	अगर (vivid_is_sdtv_cap(dev))
		वापस dev->std_cap[dev->input];
	वापस 0;
पूर्ण

अटल व्योम copy_pix(काष्ठा vivid_dev *dev, पूर्णांक win_y, पूर्णांक win_x,
			u16 *cap, स्थिर u16 *osd)
अणु
	u16 out;
	पूर्णांक left = dev->overlay_out_left;
	पूर्णांक top = dev->overlay_out_top;
	पूर्णांक fb_x = win_x + left;
	पूर्णांक fb_y = win_y + top;
	पूर्णांक i;

	out = *cap;
	*cap = *osd;
	अगर (dev->biपंचांगap_out) अणु
		स्थिर u8 *p = dev->biपंचांगap_out;
		अचिन्हित stride = (dev->compose_out.width + 7) / 8;

		win_x -= dev->compose_out.left;
		win_y -= dev->compose_out.top;
		अगर (!(p[stride * win_y + win_x / 8] & (1 << (win_x & 7))))
			वापस;
	पूर्ण

	क्रम (i = 0; i < dev->clipcount_out; i++) अणु
		काष्ठा v4l2_rect *r = &dev->clips_out[i].c;

		अगर (fb_y >= r->top && fb_y < r->top + r->height &&
		    fb_x >= r->left && fb_x < r->left + r->width)
			वापस;
	पूर्ण
	अगर ((dev->fbuf_out_flags & V4L2_FBUF_FLAG_CHROMAKEY) &&
	    *osd != dev->chromakey_out)
		वापस;
	अगर ((dev->fbuf_out_flags & V4L2_FBUF_FLAG_SRC_CHROMAKEY) &&
	    out == dev->chromakey_out)
		वापस;
	अगर (dev->fmt_cap->alpha_mask) अणु
		अगर ((dev->fbuf_out_flags & V4L2_FBUF_FLAG_GLOBAL_ALPHA) &&
		    dev->global_alpha_out)
			वापस;
		अगर ((dev->fbuf_out_flags & V4L2_FBUF_FLAG_LOCAL_ALPHA) &&
		    *cap & dev->fmt_cap->alpha_mask)
			वापस;
		अगर ((dev->fbuf_out_flags & V4L2_FBUF_FLAG_LOCAL_INV_ALPHA) &&
		    !(*cap & dev->fmt_cap->alpha_mask))
			वापस;
	पूर्ण
	*cap = out;
पूर्ण

अटल व्योम blend_line(काष्ठा vivid_dev *dev, अचिन्हित y_offset, अचिन्हित x_offset,
		u8 *vcapbuf, स्थिर u8 *vosdbuf,
		अचिन्हित width, अचिन्हित pixsize)
अणु
	अचिन्हित x;

	क्रम (x = 0; x < width; x++, vcapbuf += pixsize, vosdbuf += pixsize) अणु
		copy_pix(dev, y_offset, x_offset + x,
			 (u16 *)vcapbuf, (स्थिर u16 *)vosdbuf);
	पूर्ण
पूर्ण

अटल व्योम scale_line(स्थिर u8 *src, u8 *dst, अचिन्हित srcw, अचिन्हित dstw, अचिन्हित twopixsize)
अणु
	/* Coarse scaling with Bresenham */
	अचिन्हित पूर्णांक_part;
	अचिन्हित fract_part;
	अचिन्हित src_x = 0;
	अचिन्हित error = 0;
	अचिन्हित x;

	/*
	 * We always combine two pixels to prevent color bleed in the packed
	 * yuv हाल.
	 */
	srcw /= 2;
	dstw /= 2;
	पूर्णांक_part = srcw / dstw;
	fract_part = srcw % dstw;
	क्रम (x = 0; x < dstw; x++, dst += twopixsize) अणु
		स_नकल(dst, src + src_x * twopixsize, twopixsize);
		src_x += पूर्णांक_part;
		error += fract_part;
		अगर (error >= dstw) अणु
			error -= dstw;
			src_x++;
		पूर्ण
	पूर्ण
पूर्ण

/*
 * Precalculate the rectangles needed to perक्रमm video looping:
 *
 * The nominal pipeline is that the video output buffer is cropped by
 * crop_out, scaled to compose_out, overlaid with the output overlay,
 * cropped on the capture side by crop_cap and scaled again to the video
 * capture buffer using compose_cap.
 *
 * To keep things efficient we calculate the पूर्णांकersection of compose_out
 * and crop_cap (since that's the only part of the video that will
 * actually end up in the capture buffer), determine which part of the
 * video output buffer that is and which part of the video capture buffer
 * so we can scale the video straight from the output buffer to the capture
 * buffer without any पूर्णांकermediate steps.
 *
 * If we need to deal with an output overlay, then there is no choice and
 * that पूर्णांकermediate step still has to be taken. For the output overlay
 * support we calculate the पूर्णांकersection of the framebuffer and the overlay
 * winकरोw (which may be partially or wholly outside of the framebuffer
 * itself) and the पूर्णांकersection of that with loop_vid_copy (i.e. the part of
 * the actual looped video that will be overlaid). The result is calculated
 * both in framebuffer coordinates (loop_fb_copy) and compose_out coordinates
 * (loop_vid_overlay). Finally calculate the part of the capture buffer that
 * will receive that overlaid video.
 */
अटल व्योम vivid_precalc_copy_rects(काष्ठा vivid_dev *dev)
अणु
	/* Framebuffer rectangle */
	काष्ठा v4l2_rect r_fb = अणु
		0, 0, dev->display_width, dev->display_height
	पूर्ण;
	/* Overlay winकरोw rectangle in framebuffer coordinates */
	काष्ठा v4l2_rect r_overlay = अणु
		dev->overlay_out_left, dev->overlay_out_top,
		dev->compose_out.width, dev->compose_out.height
	पूर्ण;

	v4l2_rect_पूर्णांकersect(&dev->loop_vid_copy, &dev->crop_cap, &dev->compose_out);

	dev->loop_vid_out = dev->loop_vid_copy;
	v4l2_rect_scale(&dev->loop_vid_out, &dev->compose_out, &dev->crop_out);
	dev->loop_vid_out.left += dev->crop_out.left;
	dev->loop_vid_out.top += dev->crop_out.top;

	dev->loop_vid_cap = dev->loop_vid_copy;
	v4l2_rect_scale(&dev->loop_vid_cap, &dev->crop_cap, &dev->compose_cap);

	dprपूर्णांकk(dev, 1,
		"loop_vid_copy: %dx%d@%dx%d loop_vid_out: %dx%d@%dx%d loop_vid_cap: %dx%d@%dx%d\n",
		dev->loop_vid_copy.width, dev->loop_vid_copy.height,
		dev->loop_vid_copy.left, dev->loop_vid_copy.top,
		dev->loop_vid_out.width, dev->loop_vid_out.height,
		dev->loop_vid_out.left, dev->loop_vid_out.top,
		dev->loop_vid_cap.width, dev->loop_vid_cap.height,
		dev->loop_vid_cap.left, dev->loop_vid_cap.top);

	v4l2_rect_पूर्णांकersect(&r_overlay, &r_fb, &r_overlay);

	/* shअगरt r_overlay to the same origin as compose_out */
	r_overlay.left += dev->compose_out.left - dev->overlay_out_left;
	r_overlay.top += dev->compose_out.top - dev->overlay_out_top;

	v4l2_rect_पूर्णांकersect(&dev->loop_vid_overlay, &r_overlay, &dev->loop_vid_copy);
	dev->loop_fb_copy = dev->loop_vid_overlay;

	/* shअगरt dev->loop_fb_copy back again to the fb origin */
	dev->loop_fb_copy.left -= dev->compose_out.left - dev->overlay_out_left;
	dev->loop_fb_copy.top -= dev->compose_out.top - dev->overlay_out_top;

	dev->loop_vid_overlay_cap = dev->loop_vid_overlay;
	v4l2_rect_scale(&dev->loop_vid_overlay_cap, &dev->crop_cap, &dev->compose_cap);

	dprपूर्णांकk(dev, 1,
		"loop_fb_copy: %dx%d@%dx%d loop_vid_overlay: %dx%d@%dx%d loop_vid_overlay_cap: %dx%d@%dx%d\n",
		dev->loop_fb_copy.width, dev->loop_fb_copy.height,
		dev->loop_fb_copy.left, dev->loop_fb_copy.top,
		dev->loop_vid_overlay.width, dev->loop_vid_overlay.height,
		dev->loop_vid_overlay.left, dev->loop_vid_overlay.top,
		dev->loop_vid_overlay_cap.width, dev->loop_vid_overlay_cap.height,
		dev->loop_vid_overlay_cap.left, dev->loop_vid_overlay_cap.top);
पूर्ण

अटल व्योम *plane_vaddr(काष्ठा tpg_data *tpg, काष्ठा vivid_buffer *buf,
			 अचिन्हित p, अचिन्हित bpl[TPG_MAX_PLANES], अचिन्हित h)
अणु
	अचिन्हित i;
	व्योम *vbuf;

	अगर (p == 0 || tpg_g_buffers(tpg) > 1)
		वापस vb2_plane_vaddr(&buf->vb.vb2_buf, p);
	vbuf = vb2_plane_vaddr(&buf->vb.vb2_buf, 0);
	क्रम (i = 0; i < p; i++)
		vbuf += bpl[i] * h / tpg->vकरोwnsampling[i];
	वापस vbuf;
पूर्ण

अटल noअंतरभूत_क्रम_stack पूर्णांक vivid_copy_buffer(काष्ठा vivid_dev *dev, अचिन्हित p,
		u8 *vcapbuf, काष्ठा vivid_buffer *vid_cap_buf)
अणु
	bool blank = dev->must_blank[vid_cap_buf->vb.vb2_buf.index];
	काष्ठा tpg_data *tpg = &dev->tpg;
	काष्ठा vivid_buffer *vid_out_buf = शून्य;
	अचिन्हित vभाग = dev->fmt_out->vकरोwnsampling[p];
	अचिन्हित twopixsize = tpg_g_twopixelsize(tpg, p);
	अचिन्हित img_width = tpg_hभाग(tpg, p, dev->compose_cap.width);
	अचिन्हित img_height = dev->compose_cap.height;
	अचिन्हित stride_cap = tpg->bytesperline[p];
	अचिन्हित stride_out = dev->bytesperline_out[p];
	अचिन्हित stride_osd = dev->display_byte_stride;
	अचिन्हित hmax = (img_height * tpg->perc_fill) / 100;
	u8 *voutbuf;
	u8 *vosdbuf = शून्य;
	अचिन्हित y;
	bool blend = dev->biपंचांगap_out || dev->clipcount_out || dev->fbuf_out_flags;
	/* Coarse scaling with Bresenham */
	अचिन्हित vid_out_पूर्णांक_part;
	अचिन्हित vid_out_fract_part;
	अचिन्हित vid_out_y = 0;
	अचिन्हित vid_out_error = 0;
	अचिन्हित vid_overlay_पूर्णांक_part = 0;
	अचिन्हित vid_overlay_fract_part = 0;
	अचिन्हित vid_overlay_y = 0;
	अचिन्हित vid_overlay_error = 0;
	अचिन्हित vid_cap_left = tpg_hभाग(tpg, p, dev->loop_vid_cap.left);
	अचिन्हित vid_cap_right;
	bool quick;

	vid_out_पूर्णांक_part = dev->loop_vid_out.height / dev->loop_vid_cap.height;
	vid_out_fract_part = dev->loop_vid_out.height % dev->loop_vid_cap.height;

	अगर (!list_empty(&dev->vid_out_active))
		vid_out_buf = list_entry(dev->vid_out_active.next,
					 काष्ठा vivid_buffer, list);
	अगर (vid_out_buf == शून्य)
		वापस -ENODATA;

	vid_cap_buf->vb.field = vid_out_buf->vb.field;

	voutbuf = plane_vaddr(tpg, vid_out_buf, p,
			      dev->bytesperline_out, dev->fmt_out_rect.height);
	अगर (p < dev->fmt_out->buffers)
		voutbuf += vid_out_buf->vb.vb2_buf.planes[p].data_offset;
	voutbuf += tpg_hभाग(tpg, p, dev->loop_vid_out.left) +
		(dev->loop_vid_out.top / vभाग) * stride_out;
	vcapbuf += tpg_hभाग(tpg, p, dev->compose_cap.left) +
		(dev->compose_cap.top / vभाग) * stride_cap;

	अगर (dev->loop_vid_copy.width == 0 || dev->loop_vid_copy.height == 0) अणु
		/*
		 * If there is nothing to copy, then just fill the capture winकरोw
		 * with black.
		 */
		क्रम (y = 0; y < hmax / vभाग; y++, vcapbuf += stride_cap)
			स_नकल(vcapbuf, tpg->black_line[p], img_width);
		वापस 0;
	पूर्ण

	अगर (dev->overlay_out_enabled &&
	    dev->loop_vid_overlay.width && dev->loop_vid_overlay.height) अणु
		vosdbuf = dev->video_vbase;
		vosdbuf += (dev->loop_fb_copy.left * twopixsize) / 2 +
			   dev->loop_fb_copy.top * stride_osd;
		vid_overlay_पूर्णांक_part = dev->loop_vid_overlay.height /
				       dev->loop_vid_overlay_cap.height;
		vid_overlay_fract_part = dev->loop_vid_overlay.height %
					 dev->loop_vid_overlay_cap.height;
	पूर्ण

	vid_cap_right = tpg_hभाग(tpg, p, dev->loop_vid_cap.left + dev->loop_vid_cap.width);
	/* quick is true अगर no video scaling is needed */
	quick = dev->loop_vid_out.width == dev->loop_vid_cap.width;

	dev->cur_scaled_line = dev->loop_vid_out.height;
	क्रम (y = 0; y < hmax; y += vभाग, vcapbuf += stride_cap) अणु
		/* osdline is true अगर this line requires overlay blending */
		bool osdline = vosdbuf && y >= dev->loop_vid_overlay_cap.top &&
			  y < dev->loop_vid_overlay_cap.top + dev->loop_vid_overlay_cap.height;

		/*
		 * If this line of the capture buffer करोesn't get any video, then
		 * just fill with black.
		 */
		अगर (y < dev->loop_vid_cap.top ||
		    y >= dev->loop_vid_cap.top + dev->loop_vid_cap.height) अणु
			स_नकल(vcapbuf, tpg->black_line[p], img_width);
			जारी;
		पूर्ण

		/* fill the left border with black */
		अगर (dev->loop_vid_cap.left)
			स_नकल(vcapbuf, tpg->black_line[p], vid_cap_left);

		/* fill the right border with black */
		अगर (vid_cap_right < img_width)
			स_नकल(vcapbuf + vid_cap_right, tpg->black_line[p],
				img_width - vid_cap_right);

		अगर (quick && !osdline) अणु
			स_नकल(vcapbuf + vid_cap_left,
			       voutbuf + vid_out_y * stride_out,
			       tpg_hभाग(tpg, p, dev->loop_vid_cap.width));
			जाओ update_vid_out_y;
		पूर्ण
		अगर (dev->cur_scaled_line == vid_out_y) अणु
			स_नकल(vcapbuf + vid_cap_left, dev->scaled_line,
			       tpg_hभाग(tpg, p, dev->loop_vid_cap.width));
			जाओ update_vid_out_y;
		पूर्ण
		अगर (!osdline) अणु
			scale_line(voutbuf + vid_out_y * stride_out, dev->scaled_line,
				tpg_hभाग(tpg, p, dev->loop_vid_out.width),
				tpg_hभाग(tpg, p, dev->loop_vid_cap.width),
				tpg_g_twopixelsize(tpg, p));
		पूर्ण अन्यथा अणु
			/*
			 * Offset in bytes within loop_vid_copy to the start of the
			 * loop_vid_overlay rectangle.
			 */
			अचिन्हित offset =
				((dev->loop_vid_overlay.left - dev->loop_vid_copy.left) *
				 twopixsize) / 2;
			u8 *osd = vosdbuf + vid_overlay_y * stride_osd;

			scale_line(voutbuf + vid_out_y * stride_out, dev->blended_line,
				dev->loop_vid_out.width, dev->loop_vid_copy.width,
				tpg_g_twopixelsize(tpg, p));
			अगर (blend)
				blend_line(dev, vid_overlay_y + dev->loop_vid_overlay.top,
					   dev->loop_vid_overlay.left,
					   dev->blended_line + offset, osd,
					   dev->loop_vid_overlay.width, twopixsize / 2);
			अन्यथा
				स_नकल(dev->blended_line + offset,
				       osd, (dev->loop_vid_overlay.width * twopixsize) / 2);
			scale_line(dev->blended_line, dev->scaled_line,
					dev->loop_vid_copy.width, dev->loop_vid_cap.width,
					tpg_g_twopixelsize(tpg, p));
		पूर्ण
		dev->cur_scaled_line = vid_out_y;
		स_नकल(vcapbuf + vid_cap_left, dev->scaled_line,
		       tpg_hभाग(tpg, p, dev->loop_vid_cap.width));

update_vid_out_y:
		अगर (osdline) अणु
			vid_overlay_y += vid_overlay_पूर्णांक_part;
			vid_overlay_error += vid_overlay_fract_part;
			अगर (vid_overlay_error >= dev->loop_vid_overlay_cap.height) अणु
				vid_overlay_error -= dev->loop_vid_overlay_cap.height;
				vid_overlay_y++;
			पूर्ण
		पूर्ण
		vid_out_y += vid_out_पूर्णांक_part;
		vid_out_error += vid_out_fract_part;
		अगर (vid_out_error >= dev->loop_vid_cap.height / vभाग) अणु
			vid_out_error -= dev->loop_vid_cap.height / vभाग;
			vid_out_y++;
		पूर्ण
	पूर्ण

	अगर (!blank)
		वापस 0;
	क्रम (; y < img_height; y += vभाग, vcapbuf += stride_cap)
		स_नकल(vcapbuf, tpg->contrast_line[p], img_width);
	वापस 0;
पूर्ण

अटल व्योम vivid_fillbuff(काष्ठा vivid_dev *dev, काष्ठा vivid_buffer *buf)
अणु
	काष्ठा tpg_data *tpg = &dev->tpg;
	अचिन्हित factor = V4L2_FIELD_HAS_T_OR_B(dev->field_cap) ? 2 : 1;
	अचिन्हित line_height = 16 / factor;
	bool is_tv = vivid_is_sdtv_cap(dev);
	bool is_60hz = is_tv && (dev->std_cap[dev->input] & V4L2_STD_525_60);
	अचिन्हित p;
	पूर्णांक line = 1;
	u8 *basep[TPG_MAX_PLANES][2];
	अचिन्हित ms;
	अक्षर str[100];
	s32 gain;
	bool is_loop = false;

	अगर (dev->loop_video && dev->can_loop_video &&
		((vivid_is_svid_cap(dev) &&
		!VIVID_INVALID_SIGNAL(dev->std_संकेत_mode[dev->input])) ||
		(vivid_is_hdmi_cap(dev) &&
		!VIVID_INVALID_SIGNAL(dev->dv_timings_संकेत_mode[dev->input]))))
		is_loop = true;

	buf->vb.sequence = dev->vid_cap_seq_count;
	v4l2_ctrl_s_ctrl(dev->ro_पूर्णांक32, buf->vb.sequence & 0xff);
	अगर (dev->field_cap == V4L2_FIELD_ALTERNATE) अणु
		/*
		 * 60 Hz standards start with the bottom field, 50 Hz standards
		 * with the top field. So अगर the 0-based seq_count is even,
		 * then the field is TOP क्रम 50 Hz and BOTTOM क्रम 60 Hz
		 * standards.
		 */
		buf->vb.field = ((dev->vid_cap_seq_count & 1) ^ is_60hz) ?
			V4L2_FIELD_BOTTOM : V4L2_FIELD_TOP;
		/*
		 * The sequence counter counts frames, not fields. So भागide
		 * by two.
		 */
		buf->vb.sequence /= 2;
	पूर्ण अन्यथा अणु
		buf->vb.field = dev->field_cap;
	पूर्ण
	tpg_s_field(tpg, buf->vb.field,
		    dev->field_cap == V4L2_FIELD_ALTERNATE);
	tpg_s_perc_fill_blank(tpg, dev->must_blank[buf->vb.vb2_buf.index]);

	vivid_precalc_copy_rects(dev);

	क्रम (p = 0; p < tpg_g_planes(tpg); p++) अणु
		व्योम *vbuf = plane_vaddr(tpg, buf, p,
					 tpg->bytesperline, tpg->buf_height);

		/*
		 * The first plane of a multiplanar क्रमmat has a non-zero
		 * data_offset. This helps testing whether the application
		 * correctly supports non-zero data offsets.
		 */
		अगर (p < tpg_g_buffers(tpg) && dev->fmt_cap->data_offset[p]) अणु
			स_रखो(vbuf, dev->fmt_cap->data_offset[p] & 0xff,
			       dev->fmt_cap->data_offset[p]);
			vbuf += dev->fmt_cap->data_offset[p];
		पूर्ण
		tpg_calc_text_basep(tpg, basep, p, vbuf);
		अगर (!is_loop || vivid_copy_buffer(dev, p, vbuf, buf))
			tpg_fill_plane_buffer(tpg, vivid_get_std_cap(dev),
					p, vbuf);
	पूर्ण
	dev->must_blank[buf->vb.vb2_buf.index] = false;

	/* Updates stream समय, only update at the start of a new frame. */
	अगर (dev->field_cap != V4L2_FIELD_ALTERNATE ||
			(dev->vid_cap_seq_count & 1) == 0)
		dev->ms_vid_cap =
			jअगरfies_to_msecs(jअगरfies - dev->jअगरfies_vid_cap);

	ms = dev->ms_vid_cap;
	अगर (dev->osd_mode <= 1) अणु
		snम_लिखो(str, माप(str), " %02d:%02d:%02d:%03d %u%s",
				(ms / (60 * 60 * 1000)) % 24,
				(ms / (60 * 1000)) % 60,
				(ms / 1000) % 60,
				ms % 1000,
				buf->vb.sequence,
				(dev->field_cap == V4L2_FIELD_ALTERNATE) ?
					(buf->vb.field == V4L2_FIELD_TOP ?
					 " top" : " bottom") : "");
		tpg_gen_text(tpg, basep, line++ * line_height, 16, str);
	पूर्ण
	अगर (dev->osd_mode == 0) अणु
		snम_लिखो(str, माप(str), " %dx%d, input %d ",
				dev->src_rect.width, dev->src_rect.height, dev->input);
		tpg_gen_text(tpg, basep, line++ * line_height, 16, str);

		gain = v4l2_ctrl_g_ctrl(dev->gain);
		mutex_lock(dev->ctrl_hdl_user_vid.lock);
		snम_लिखो(str, माप(str),
			" brightness %3d, contrast %3d, saturation %3d, hue %d ",
			dev->brightness->cur.val,
			dev->contrast->cur.val,
			dev->saturation->cur.val,
			dev->hue->cur.val);
		tpg_gen_text(tpg, basep, line++ * line_height, 16, str);
		snम_लिखो(str, माप(str),
			" autogain %d, gain %3d, alpha 0x%02x ",
			dev->स्वतःgain->cur.val, gain, dev->alpha->cur.val);
		mutex_unlock(dev->ctrl_hdl_user_vid.lock);
		tpg_gen_text(tpg, basep, line++ * line_height, 16, str);
		mutex_lock(dev->ctrl_hdl_user_aud.lock);
		snम_लिखो(str, माप(str),
			" volume %3d, mute %d ",
			dev->volume->cur.val, dev->mute->cur.val);
		mutex_unlock(dev->ctrl_hdl_user_aud.lock);
		tpg_gen_text(tpg, basep, line++ * line_height, 16, str);
		mutex_lock(dev->ctrl_hdl_user_gen.lock);
		snम_लिखो(str, माप(str), " int32 %d, ro_int32 %d, int64 %lld, bitmask %08x ",
			 dev->पूर्णांक32->cur.val,
			 dev->ro_पूर्णांक32->cur.val,
			 *dev->पूर्णांक64->p_cur.p_s64,
			 dev->biपंचांगask->cur.val);
		tpg_gen_text(tpg, basep, line++ * line_height, 16, str);
		snम_लिखो(str, माप(str), " boolean %d, menu %s, string \"%s\" ",
			dev->boolean->cur.val,
			dev->menu->qmenu[dev->menu->cur.val],
			dev->string->p_cur.p_अक्षर);
		tpg_gen_text(tpg, basep, line++ * line_height, 16, str);
		snम_लिखो(str, माप(str), " integer_menu %lld, value %d ",
			dev->पूर्णांक_menu->qmenu_पूर्णांक[dev->पूर्णांक_menu->cur.val],
			dev->पूर्णांक_menu->cur.val);
		mutex_unlock(dev->ctrl_hdl_user_gen.lock);
		tpg_gen_text(tpg, basep, line++ * line_height, 16, str);
		अगर (dev->button_pressed) अणु
			dev->button_pressed--;
			snम_लिखो(str, माप(str), " button pressed!");
			tpg_gen_text(tpg, basep, line++ * line_height, 16, str);
		पूर्ण
		अगर (dev->osd[0]) अणु
			अगर (vivid_is_hdmi_cap(dev)) अणु
				snम_लिखो(str, माप(str),
					 " OSD \"%s\"", dev->osd);
				tpg_gen_text(tpg, basep, line++ * line_height,
					     16, str);
			पूर्ण
			अगर (dev->osd_jअगरfies &&
			    समय_is_beक्रमe_jअगरfies(dev->osd_jअगरfies + 5 * HZ)) अणु
				dev->osd[0] = 0;
				dev->osd_jअगरfies = 0;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

/*
 * Return true अगर this pixel coordinate is a valid video pixel.
 */
अटल bool valid_pix(काष्ठा vivid_dev *dev, पूर्णांक win_y, पूर्णांक win_x, पूर्णांक fb_y, पूर्णांक fb_x)
अणु
	पूर्णांक i;

	अगर (dev->biपंचांगap_cap) अणु
		/*
		 * Only अगर the corresponding bit in the biपंचांगap is set can
		 * the video pixel be shown. Coordinates are relative to
		 * the overlay winकरोw set by VIDIOC_S_FMT.
		 */
		स्थिर u8 *p = dev->biपंचांगap_cap;
		अचिन्हित stride = (dev->compose_cap.width + 7) / 8;

		अगर (!(p[stride * win_y + win_x / 8] & (1 << (win_x & 7))))
			वापस false;
	पूर्ण

	क्रम (i = 0; i < dev->clipcount_cap; i++) अणु
		/*
		 * Only अगर the framebuffer coordinate is not in any of the
		 * clip rectangles will be video pixel be shown.
		 */
		काष्ठा v4l2_rect *r = &dev->clips_cap[i].c;

		अगर (fb_y >= r->top && fb_y < r->top + r->height &&
		    fb_x >= r->left && fb_x < r->left + r->width)
			वापस false;
	पूर्ण
	वापस true;
पूर्ण

/*
 * Draw the image पूर्णांकo the overlay buffer.
 * Note that the combination of overlay and multiplanar is not supported.
 */
अटल व्योम vivid_overlay(काष्ठा vivid_dev *dev, काष्ठा vivid_buffer *buf)
अणु
	काष्ठा tpg_data *tpg = &dev->tpg;
	अचिन्हित pixsize = tpg_g_twopixelsize(tpg, 0) / 2;
	व्योम *vbase = dev->fb_vbase_cap;
	व्योम *vbuf = vb2_plane_vaddr(&buf->vb.vb2_buf, 0);
	अचिन्हित img_width = dev->compose_cap.width;
	अचिन्हित img_height = dev->compose_cap.height;
	अचिन्हित stride = tpg->bytesperline[0];
	/* अगर quick is true, then valid_pix() करोesn't have to be called */
	bool quick = dev->biपंचांगap_cap == शून्य && dev->clipcount_cap == 0;
	पूर्णांक x, y, w, out_x = 0;

	/*
	 * Overlay support is only supported क्रम क्रमmats that have a twopixelsize
	 * that's >= 2. Warn and bail out if that's not the हाल.
	 */
	अगर (WARN_ON(pixsize == 0))
		वापस;
	अगर ((dev->overlay_cap_field == V4L2_FIELD_TOP ||
	     dev->overlay_cap_field == V4L2_FIELD_BOTTOM) &&
	    dev->overlay_cap_field != buf->vb.field)
		वापस;

	vbuf += dev->compose_cap.left * pixsize + dev->compose_cap.top * stride;
	x = dev->overlay_cap_left;
	w = img_width;
	अगर (x < 0) अणु
		out_x = -x;
		w = w - out_x;
		x = 0;
	पूर्ण अन्यथा अणु
		w = dev->fb_cap.fmt.width - x;
		अगर (w > img_width)
			w = img_width;
	पूर्ण
	अगर (w <= 0)
		वापस;
	अगर (dev->overlay_cap_top >= 0)
		vbase += dev->overlay_cap_top * dev->fb_cap.fmt.bytesperline;
	क्रम (y = dev->overlay_cap_top;
	     y < dev->overlay_cap_top + (पूर्णांक)img_height;
	     y++, vbuf += stride) अणु
		पूर्णांक px;

		अगर (y < 0 || y > dev->fb_cap.fmt.height)
			जारी;
		अगर (quick) अणु
			स_नकल(vbase + x * pixsize,
			       vbuf + out_x * pixsize, w * pixsize);
			vbase += dev->fb_cap.fmt.bytesperline;
			जारी;
		पूर्ण
		क्रम (px = 0; px < w; px++) अणु
			अगर (!valid_pix(dev, y - dev->overlay_cap_top,
				       px + out_x, y, px + x))
				जारी;
			स_नकल(vbase + (px + x) * pixsize,
			       vbuf + (px + out_x) * pixsize,
			       pixsize);
		पूर्ण
		vbase += dev->fb_cap.fmt.bytesperline;
	पूर्ण
पूर्ण

अटल व्योम vivid_cap_update_frame_period(काष्ठा vivid_dev *dev)
अणु
	u64 f_period;

	f_period = (u64)dev->समयperframe_vid_cap.numerator * 1000000000;
	अगर (WARN_ON(dev->समयperframe_vid_cap.denominator == 0))
		dev->समयperframe_vid_cap.denominator = 1;
	करो_भाग(f_period, dev->समयperframe_vid_cap.denominator);
	अगर (dev->field_cap == V4L2_FIELD_ALTERNATE)
		f_period >>= 1;
	/*
	 * If "End of Frame", then offset the exposure समय by 0.9
	 * of the frame period.
	 */
	dev->cap_frame_eof_offset = f_period * 9;
	करो_भाग(dev->cap_frame_eof_offset, 10);
	dev->cap_frame_period = f_period;
पूर्ण

अटल noअंतरभूत_क्रम_stack व्योम vivid_thपढ़ो_vid_cap_tick(काष्ठा vivid_dev *dev,
							 पूर्णांक dropped_bufs)
अणु
	काष्ठा vivid_buffer *vid_cap_buf = शून्य;
	काष्ठा vivid_buffer *vbi_cap_buf = शून्य;
	काष्ठा vivid_buffer *meta_cap_buf = शून्य;
	u64 f_समय = 0;

	dprपूर्णांकk(dev, 1, "Video Capture Thread Tick\n");

	जबतक (dropped_bufs-- > 1)
		tpg_update_mv_count(&dev->tpg,
				dev->field_cap == V4L2_FIELD_NONE ||
				dev->field_cap == V4L2_FIELD_ALTERNATE);

	/* Drop a certain percentage of buffers. */
	अगर (dev->perc_dropped_buffers &&
	    pअक्रमom_u32_max(100) < dev->perc_dropped_buffers)
		जाओ update_mv;

	spin_lock(&dev->slock);
	अगर (!list_empty(&dev->vid_cap_active)) अणु
		vid_cap_buf = list_entry(dev->vid_cap_active.next, काष्ठा vivid_buffer, list);
		list_del(&vid_cap_buf->list);
	पूर्ण
	अगर (!list_empty(&dev->vbi_cap_active)) अणु
		अगर (dev->field_cap != V4L2_FIELD_ALTERNATE ||
		    (dev->vbi_cap_seq_count & 1)) अणु
			vbi_cap_buf = list_entry(dev->vbi_cap_active.next,
						 काष्ठा vivid_buffer, list);
			list_del(&vbi_cap_buf->list);
		पूर्ण
	पूर्ण
	अगर (!list_empty(&dev->meta_cap_active)) अणु
		meta_cap_buf = list_entry(dev->meta_cap_active.next,
					  काष्ठा vivid_buffer, list);
		list_del(&meta_cap_buf->list);
	पूर्ण

	spin_unlock(&dev->slock);

	अगर (!vid_cap_buf && !vbi_cap_buf && !meta_cap_buf)
		जाओ update_mv;

	f_समय = dev->cap_frame_period * dev->vid_cap_seq_count +
		 dev->cap_stream_start + dev->समय_wrap_offset;

	अगर (vid_cap_buf) अणु
		v4l2_ctrl_request_setup(vid_cap_buf->vb.vb2_buf.req_obj.req,
					&dev->ctrl_hdl_vid_cap);
		/* Fill buffer */
		vivid_fillbuff(dev, vid_cap_buf);
		dprपूर्णांकk(dev, 1, "filled buffer %d\n",
			vid_cap_buf->vb.vb2_buf.index);

		/* Handle overlay */
		अगर (dev->overlay_cap_owner && dev->fb_cap.base &&
			dev->fb_cap.fmt.pixelक्रमmat == dev->fmt_cap->fourcc)
			vivid_overlay(dev, vid_cap_buf);

		v4l2_ctrl_request_complete(vid_cap_buf->vb.vb2_buf.req_obj.req,
					   &dev->ctrl_hdl_vid_cap);
		vb2_buffer_करोne(&vid_cap_buf->vb.vb2_buf, dev->dqbuf_error ?
				VB2_BUF_STATE_ERROR : VB2_BUF_STATE_DONE);
		dprपूर्णांकk(dev, 2, "vid_cap buffer %d done\n",
				vid_cap_buf->vb.vb2_buf.index);

		vid_cap_buf->vb.vb2_buf.बारtamp = f_समय;
		अगर (!dev->tstamp_src_is_soe)
			vid_cap_buf->vb.vb2_buf.बारtamp += dev->cap_frame_eof_offset;
	पूर्ण

	अगर (vbi_cap_buf) अणु
		u64 vbi_period;

		v4l2_ctrl_request_setup(vbi_cap_buf->vb.vb2_buf.req_obj.req,
					&dev->ctrl_hdl_vbi_cap);
		अगर (dev->stream_sliced_vbi_cap)
			vivid_sliced_vbi_cap_process(dev, vbi_cap_buf);
		अन्यथा
			vivid_raw_vbi_cap_process(dev, vbi_cap_buf);
		v4l2_ctrl_request_complete(vbi_cap_buf->vb.vb2_buf.req_obj.req,
					   &dev->ctrl_hdl_vbi_cap);
		vb2_buffer_करोne(&vbi_cap_buf->vb.vb2_buf, dev->dqbuf_error ?
				VB2_BUF_STATE_ERROR : VB2_BUF_STATE_DONE);
		dprपूर्णांकk(dev, 2, "vbi_cap %d done\n",
				vbi_cap_buf->vb.vb2_buf.index);

		/* If capturing a VBI, offset by 0.05 */
		vbi_period = dev->cap_frame_period * 5;
		करो_भाग(vbi_period, 100);
		vbi_cap_buf->vb.vb2_buf.बारtamp = f_समय + dev->cap_frame_eof_offset + vbi_period;
	पूर्ण

	अगर (meta_cap_buf) अणु
		v4l2_ctrl_request_setup(meta_cap_buf->vb.vb2_buf.req_obj.req,
					&dev->ctrl_hdl_meta_cap);
		vivid_meta_cap_fillbuff(dev, meta_cap_buf, f_समय);
		v4l2_ctrl_request_complete(meta_cap_buf->vb.vb2_buf.req_obj.req,
					   &dev->ctrl_hdl_meta_cap);
		vb2_buffer_करोne(&meta_cap_buf->vb.vb2_buf, dev->dqbuf_error ?
				VB2_BUF_STATE_ERROR : VB2_BUF_STATE_DONE);
		dprपूर्णांकk(dev, 2, "meta_cap %d done\n",
			meta_cap_buf->vb.vb2_buf.index);
		meta_cap_buf->vb.vb2_buf.बारtamp = f_समय + dev->cap_frame_eof_offset;
	पूर्ण

	dev->dqbuf_error = false;

update_mv:
	/* Update the test pattern movement counters */
	tpg_update_mv_count(&dev->tpg, dev->field_cap == V4L2_FIELD_NONE ||
				       dev->field_cap == V4L2_FIELD_ALTERNATE);
पूर्ण

अटल पूर्णांक vivid_thपढ़ो_vid_cap(व्योम *data)
अणु
	काष्ठा vivid_dev *dev = data;
	u64 numerators_since_start;
	u64 buffers_since_start;
	u64 next_jअगरfies_since_start;
	अचिन्हित दीर्घ jअगरfies_since_start;
	अचिन्हित दीर्घ cur_jअगरfies;
	अचिन्हित रुको_jअगरfies;
	अचिन्हित numerator;
	अचिन्हित denominator;
	पूर्णांक dropped_bufs;

	dprपूर्णांकk(dev, 1, "Video Capture Thread Start\n");

	set_मुक्तzable();

	/* Resets frame counters */
	dev->cap_seq_offset = 0;
	dev->cap_seq_count = 0;
	dev->cap_seq_resync = false;
	dev->jअगरfies_vid_cap = jअगरfies;
	dev->cap_stream_start = kसमय_get_ns();
	vivid_cap_update_frame_period(dev);

	क्रम (;;) अणु
		try_to_मुक्तze();
		अगर (kthपढ़ो_should_stop())
			अवरोध;

		अगर (!mutex_trylock(&dev->mutex)) अणु
			schedule();
			जारी;
		पूर्ण

		cur_jअगरfies = jअगरfies;
		अगर (dev->cap_seq_resync) अणु
			dev->jअगरfies_vid_cap = cur_jअगरfies;
			dev->cap_seq_offset = dev->cap_seq_count + 1;
			dev->cap_seq_count = 0;
			dev->cap_stream_start += dev->cap_frame_period *
						 dev->cap_seq_offset;
			vivid_cap_update_frame_period(dev);
			dev->cap_seq_resync = false;
		पूर्ण
		numerator = dev->समयperframe_vid_cap.numerator;
		denominator = dev->समयperframe_vid_cap.denominator;

		अगर (dev->field_cap == V4L2_FIELD_ALTERNATE)
			denominator *= 2;

		/* Calculate the number of jअगरfies since we started streaming */
		jअगरfies_since_start = cur_jअगरfies - dev->jअगरfies_vid_cap;
		/* Get the number of buffers streamed since the start */
		buffers_since_start = (u64)jअगरfies_since_start * denominator +
				      (HZ * numerator) / 2;
		करो_भाग(buffers_since_start, HZ * numerator);

		/*
		 * After more than 0xf0000000 (rounded करोwn to a multiple of
		 * 'jiffies-per-day' to ease jअगरfies_to_msecs calculation)
		 * jअगरfies have passed since we started streaming reset the
		 * counters and keep track of the sequence offset.
		 */
		अगर (jअगरfies_since_start > JIFFIES_RESYNC) अणु
			dev->jअगरfies_vid_cap = cur_jअगरfies;
			dev->cap_seq_offset = buffers_since_start;
			buffers_since_start = 0;
		पूर्ण
		dropped_bufs = buffers_since_start + dev->cap_seq_offset - dev->cap_seq_count;
		dev->cap_seq_count = buffers_since_start + dev->cap_seq_offset;
		dev->vid_cap_seq_count = dev->cap_seq_count - dev->vid_cap_seq_start;
		dev->vbi_cap_seq_count = dev->cap_seq_count - dev->vbi_cap_seq_start;
		dev->meta_cap_seq_count = dev->cap_seq_count - dev->meta_cap_seq_start;

		vivid_thपढ़ो_vid_cap_tick(dev, dropped_bufs);

		/*
		 * Calculate the number of 'numerators' streamed since we started,
		 * including the current buffer.
		 */
		numerators_since_start = ++buffers_since_start * numerator;

		/* And the number of jअगरfies since we started */
		jअगरfies_since_start = jअगरfies - dev->jअगरfies_vid_cap;

		mutex_unlock(&dev->mutex);

		/*
		 * Calculate when that next buffer is supposed to start
		 * in jअगरfies since we started streaming.
		 */
		next_jअगरfies_since_start = numerators_since_start * HZ +
					   denominator / 2;
		करो_भाग(next_jअगरfies_since_start, denominator);
		/* If it is in the past, then just schedule asap */
		अगर (next_jअगरfies_since_start < jअगरfies_since_start)
			next_jअगरfies_since_start = jअगरfies_since_start;

		रुको_jअगरfies = next_jअगरfies_since_start - jअगरfies_since_start;
		जबतक (jअगरfies - cur_jअगरfies < रुको_jअगरfies &&
		       !kthपढ़ो_should_stop())
			schedule();
	पूर्ण
	dprपूर्णांकk(dev, 1, "Video Capture Thread End\n");
	वापस 0;
पूर्ण

अटल व्योम vivid_grab_controls(काष्ठा vivid_dev *dev, bool grab)
अणु
	v4l2_ctrl_grab(dev->ctrl_has_crop_cap, grab);
	v4l2_ctrl_grab(dev->ctrl_has_compose_cap, grab);
	v4l2_ctrl_grab(dev->ctrl_has_scaler_cap, grab);
पूर्ण

पूर्णांक vivid_start_generating_vid_cap(काष्ठा vivid_dev *dev, bool *pstreaming)
अणु
	dprपूर्णांकk(dev, 1, "%s\n", __func__);

	अगर (dev->kthपढ़ो_vid_cap) अणु
		u32 seq_count = dev->cap_seq_count + dev->seq_wrap * 128;

		अगर (pstreaming == &dev->vid_cap_streaming)
			dev->vid_cap_seq_start = seq_count;
		अन्यथा अगर (pstreaming == &dev->vbi_cap_streaming)
			dev->vbi_cap_seq_start = seq_count;
		अन्यथा
			dev->meta_cap_seq_start = seq_count;
		*pstreaming = true;
		वापस 0;
	पूर्ण

	/* Resets frame counters */
	tpg_init_mv_count(&dev->tpg);

	dev->vid_cap_seq_start = dev->seq_wrap * 128;
	dev->vbi_cap_seq_start = dev->seq_wrap * 128;
	dev->meta_cap_seq_start = dev->seq_wrap * 128;

	dev->kthपढ़ो_vid_cap = kthपढ़ो_run(vivid_thपढ़ो_vid_cap, dev,
			"%s-vid-cap", dev->v4l2_dev.name);

	अगर (IS_ERR(dev->kthपढ़ो_vid_cap)) अणु
		पूर्णांक err = PTR_ERR(dev->kthपढ़ो_vid_cap);

		dev->kthपढ़ो_vid_cap = शून्य;
		v4l2_err(&dev->v4l2_dev, "kernel_thread() failed\n");
		वापस err;
	पूर्ण
	*pstreaming = true;
	vivid_grab_controls(dev, true);

	dprपूर्णांकk(dev, 1, "returning from %s\n", __func__);
	वापस 0;
पूर्ण

व्योम vivid_stop_generating_vid_cap(काष्ठा vivid_dev *dev, bool *pstreaming)
अणु
	dprपूर्णांकk(dev, 1, "%s\n", __func__);

	अगर (dev->kthपढ़ो_vid_cap == शून्य)
		वापस;

	*pstreaming = false;
	अगर (pstreaming == &dev->vid_cap_streaming) अणु
		/* Release all active buffers */
		जबतक (!list_empty(&dev->vid_cap_active)) अणु
			काष्ठा vivid_buffer *buf;

			buf = list_entry(dev->vid_cap_active.next,
					 काष्ठा vivid_buffer, list);
			list_del(&buf->list);
			v4l2_ctrl_request_complete(buf->vb.vb2_buf.req_obj.req,
						   &dev->ctrl_hdl_vid_cap);
			vb2_buffer_करोne(&buf->vb.vb2_buf, VB2_BUF_STATE_ERROR);
			dprपूर्णांकk(dev, 2, "vid_cap buffer %d done\n",
				buf->vb.vb2_buf.index);
		पूर्ण
	पूर्ण

	अगर (pstreaming == &dev->vbi_cap_streaming) अणु
		जबतक (!list_empty(&dev->vbi_cap_active)) अणु
			काष्ठा vivid_buffer *buf;

			buf = list_entry(dev->vbi_cap_active.next,
					 काष्ठा vivid_buffer, list);
			list_del(&buf->list);
			v4l2_ctrl_request_complete(buf->vb.vb2_buf.req_obj.req,
						   &dev->ctrl_hdl_vbi_cap);
			vb2_buffer_करोne(&buf->vb.vb2_buf, VB2_BUF_STATE_ERROR);
			dprपूर्णांकk(dev, 2, "vbi_cap buffer %d done\n",
				buf->vb.vb2_buf.index);
		पूर्ण
	पूर्ण

	अगर (pstreaming == &dev->meta_cap_streaming) अणु
		जबतक (!list_empty(&dev->meta_cap_active)) अणु
			काष्ठा vivid_buffer *buf;

			buf = list_entry(dev->meta_cap_active.next,
					 काष्ठा vivid_buffer, list);
			list_del(&buf->list);
			v4l2_ctrl_request_complete(buf->vb.vb2_buf.req_obj.req,
						   &dev->ctrl_hdl_meta_cap);
			vb2_buffer_करोne(&buf->vb.vb2_buf, VB2_BUF_STATE_ERROR);
			dprपूर्णांकk(dev, 2, "meta_cap buffer %d done\n",
				buf->vb.vb2_buf.index);
		पूर्ण
	पूर्ण

	अगर (dev->vid_cap_streaming || dev->vbi_cap_streaming ||
	    dev->meta_cap_streaming)
		वापस;

	/* shutकरोwn control thपढ़ो */
	vivid_grab_controls(dev, false);
	kthपढ़ो_stop(dev->kthपढ़ो_vid_cap);
	dev->kthपढ़ो_vid_cap = शून्य;
पूर्ण
