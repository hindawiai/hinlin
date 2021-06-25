<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *	Video क्रम Linux Two
 *
 *	A generic video device पूर्णांकerface क्रम the LINUX operating प्रणाली
 *	using a set of device काष्ठाures/vectors क्रम low level operations.
 *
 *	This file replaces the videodev.c file that comes with the
 *	regular kernel distribution.
 *
 * Author:	Bill Dirks <bill@thedirks.org>
 *		based on code by Alan Cox, <alan@cymru.net>
 */

/*
 * Video capture पूर्णांकerface क्रम Linux
 *
 *	A generic video device पूर्णांकerface क्रम the LINUX operating प्रणाली
 *	using a set of device काष्ठाures/vectors क्रम low level operations.
 *
 * Author:	Alan Cox, <alan@lxorguk.ukuu.org.uk>
 *
 * Fixes:
 */

/*
 * Video4linux 1/2 पूर्णांकegration by Justin Schoeman
 * <justin@suntiger.ee.up.ac.za>
 * 2.4 PROCFS support ported from 2.4 kernels by
 *  Iथऔaki Garcथऐa Etxebarria <garetxe@euskalnet.net>
 * Makefile fix by "W. Michael Petullo" <mike@flyn.org>
 * 2.4 devfs support ported from 2.4 kernels by
 *  Dan Merillat <dan@merillat.org>
 * Added Gerd Knorrs v4l1 enhancements (Justin Schoeman)
 */

#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/माला.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/भाग64.h>
#समावेश <media/v4l2-common.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-ctrls.h>

#समावेश <linux/videodev2.h>

/*
 *
 *	V 4 L 2   D R I V E R   H E L P E R   A P I
 *
 */

/*
 *  Video Standard Operations (contributed by Michael Schimek)
 */

/* Helper functions क्रम control handling			     */

/* Fill in a काष्ठा v4l2_queryctrl */
पूर्णांक v4l2_ctrl_query_fill(काष्ठा v4l2_queryctrl *qctrl, s32 _min, s32 _max, s32 _step, s32 _def)
अणु
	स्थिर अक्षर *name;
	s64 min = _min;
	s64 max = _max;
	u64 step = _step;
	s64 def = _def;

	v4l2_ctrl_fill(qctrl->id, &name, &qctrl->type,
		       &min, &max, &step, &def, &qctrl->flags);

	अगर (name == शून्य)
		वापस -EINVAL;

	qctrl->minimum = min;
	qctrl->maximum = max;
	qctrl->step = step;
	qctrl->शेष_value = def;
	qctrl->reserved[0] = qctrl->reserved[1] = 0;
	strscpy(qctrl->name, name, माप(qctrl->name));
	वापस 0;
पूर्ण
EXPORT_SYMBOL(v4l2_ctrl_query_fill);

/* Clamp x to be between min and max, aligned to a multiple of 2^align.  min
 * and max करोn't have to be aligned, but there must be at least one valid
 * value.  E.g., min=17,max=31,align=4 is not allowed as there are no multiples
 * of 16 between 17 and 31.  */
अटल अचिन्हित पूर्णांक clamp_align(अचिन्हित पूर्णांक x, अचिन्हित पूर्णांक min,
				अचिन्हित पूर्णांक max, अचिन्हित पूर्णांक align)
अणु
	/* Bits that must be zero to be aligned */
	अचिन्हित पूर्णांक mask = ~((1 << align) - 1);

	/* Clamp to aligned min and max */
	x = clamp(x, (min + ~mask) & mask, max & mask);

	/* Round to nearest aligned value */
	अगर (align)
		x = (x + (1 << (align - 1))) & mask;

	वापस x;
पूर्ण

अटल अचिन्हित पूर्णांक clamp_roundup(अचिन्हित पूर्णांक x, अचिन्हित पूर्णांक min,
				   अचिन्हित पूर्णांक max, अचिन्हित पूर्णांक alignment)
अणु
	x = clamp(x, min, max);
	अगर (alignment)
		x = round_up(x, alignment);

	वापस x;
पूर्ण

व्योम v4l_bound_align_image(u32 *w, अचिन्हित पूर्णांक wmin, अचिन्हित पूर्णांक wmax,
			   अचिन्हित पूर्णांक walign,
			   u32 *h, अचिन्हित पूर्णांक hmin, अचिन्हित पूर्णांक hmax,
			   अचिन्हित पूर्णांक halign, अचिन्हित पूर्णांक salign)
अणु
	*w = clamp_align(*w, wmin, wmax, walign);
	*h = clamp_align(*h, hmin, hmax, halign);

	/* Usually we करोn't need to align the size and are करोne now. */
	अगर (!salign)
		वापस;

	/* How much alignment करो we have? */
	walign = __ffs(*w);
	halign = __ffs(*h);
	/* Enough to satisfy the image alignment? */
	अगर (walign + halign < salign) अणु
		/* Max walign where there is still a valid width */
		अचिन्हित पूर्णांक wmaxa = __fls(wmax ^ (wmin - 1));
		/* Max halign where there is still a valid height */
		अचिन्हित पूर्णांक hmaxa = __fls(hmax ^ (hmin - 1));

		/* up the smaller alignment until we have enough */
		करो अणु
			अगर (halign >= hmaxa ||
			    (walign <= halign && walign < wmaxa)) अणु
				*w = clamp_align(*w, wmin, wmax, walign + 1);
				walign = __ffs(*w);
			पूर्ण अन्यथा अणु
				*h = clamp_align(*h, hmin, hmax, halign + 1);
				halign = __ffs(*h);
			पूर्ण
		पूर्ण जबतक (halign + walign < salign);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(v4l_bound_align_image);

स्थिर व्योम *
__v4l2_find_nearest_size(स्थिर व्योम *array, माप_प्रकार array_size,
			 माप_प्रकार entry_size, माप_प्रकार width_offset,
			 माप_प्रकार height_offset, s32 width, s32 height)
अणु
	u32 error, min_error = U32_MAX;
	स्थिर व्योम *best = शून्य;
	अचिन्हित पूर्णांक i;

	अगर (!array)
		वापस शून्य;

	क्रम (i = 0; i < array_size; i++, array += entry_size) अणु
		स्थिर u32 *entry_width = array + width_offset;
		स्थिर u32 *entry_height = array + height_offset;

		error = असल(*entry_width - width) + असल(*entry_height - height);
		अगर (error > min_error)
			जारी;

		min_error = error;
		best = array;
		अगर (!error)
			अवरोध;
	पूर्ण

	वापस best;
पूर्ण
EXPORT_SYMBOL_GPL(__v4l2_find_nearest_size);

पूर्णांक v4l2_g_parm_cap(काष्ठा video_device *vdev,
		    काष्ठा v4l2_subdev *sd, काष्ठा v4l2_streamparm *a)
अणु
	काष्ठा v4l2_subdev_frame_पूर्णांकerval ival = अणु 0 पूर्ण;
	पूर्णांक ret;

	अगर (a->type != V4L2_BUF_TYPE_VIDEO_CAPTURE &&
	    a->type != V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE)
		वापस -EINVAL;

	अगर (vdev->device_caps & V4L2_CAP_READWRITE)
		a->parm.capture.पढ़ोbuffers = 2;
	अगर (v4l2_subdev_has_op(sd, video, g_frame_पूर्णांकerval))
		a->parm.capture.capability = V4L2_CAP_TIMEPERFRAME;
	ret = v4l2_subdev_call(sd, video, g_frame_पूर्णांकerval, &ival);
	अगर (!ret)
		a->parm.capture.समयperframe = ival.पूर्णांकerval;
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(v4l2_g_parm_cap);

पूर्णांक v4l2_s_parm_cap(काष्ठा video_device *vdev,
		    काष्ठा v4l2_subdev *sd, काष्ठा v4l2_streamparm *a)
अणु
	काष्ठा v4l2_subdev_frame_पूर्णांकerval ival = अणु
		.पूर्णांकerval = a->parm.capture.समयperframe
	पूर्ण;
	पूर्णांक ret;

	अगर (a->type != V4L2_BUF_TYPE_VIDEO_CAPTURE &&
	    a->type != V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE)
		वापस -EINVAL;

	स_रखो(&a->parm, 0, माप(a->parm));
	अगर (vdev->device_caps & V4L2_CAP_READWRITE)
		a->parm.capture.पढ़ोbuffers = 2;
	अन्यथा
		a->parm.capture.पढ़ोbuffers = 0;

	अगर (v4l2_subdev_has_op(sd, video, g_frame_पूर्णांकerval))
		a->parm.capture.capability = V4L2_CAP_TIMEPERFRAME;
	ret = v4l2_subdev_call(sd, video, s_frame_पूर्णांकerval, &ival);
	अगर (!ret)
		a->parm.capture.समयperframe = ival.पूर्णांकerval;
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(v4l2_s_parm_cap);

स्थिर काष्ठा v4l2_क्रमmat_info *v4l2_क्रमmat_info(u32 क्रमmat)
अणु
	अटल स्थिर काष्ठा v4l2_क्रमmat_info क्रमmats[] = अणु
		/* RGB क्रमmats */
		अणु .क्रमmat = V4L2_PIX_FMT_BGR24,   .pixel_enc = V4L2_PIXEL_ENC_RGB, .mem_planes = 1, .comp_planes = 1, .bpp = अणु 3, 0, 0, 0 पूर्ण, .hभाग = 1, .vभाग = 1 पूर्ण,
		अणु .क्रमmat = V4L2_PIX_FMT_RGB24,   .pixel_enc = V4L2_PIXEL_ENC_RGB, .mem_planes = 1, .comp_planes = 1, .bpp = अणु 3, 0, 0, 0 पूर्ण, .hभाग = 1, .vभाग = 1 पूर्ण,
		अणु .क्रमmat = V4L2_PIX_FMT_HSV24,   .pixel_enc = V4L2_PIXEL_ENC_RGB, .mem_planes = 1, .comp_planes = 1, .bpp = अणु 3, 0, 0, 0 पूर्ण, .hभाग = 1, .vभाग = 1 पूर्ण,
		अणु .क्रमmat = V4L2_PIX_FMT_BGR32,   .pixel_enc = V4L2_PIXEL_ENC_RGB, .mem_planes = 1, .comp_planes = 1, .bpp = अणु 4, 0, 0, 0 पूर्ण, .hभाग = 1, .vभाग = 1 पूर्ण,
		अणु .क्रमmat = V4L2_PIX_FMT_XBGR32,  .pixel_enc = V4L2_PIXEL_ENC_RGB, .mem_planes = 1, .comp_planes = 1, .bpp = अणु 4, 0, 0, 0 पूर्ण, .hभाग = 1, .vभाग = 1 पूर्ण,
		अणु .क्रमmat = V4L2_PIX_FMT_BGRX32,  .pixel_enc = V4L2_PIXEL_ENC_RGB, .mem_planes = 1, .comp_planes = 1, .bpp = अणु 4, 0, 0, 0 पूर्ण, .hभाग = 1, .vभाग = 1 पूर्ण,
		अणु .क्रमmat = V4L2_PIX_FMT_RGB32,   .pixel_enc = V4L2_PIXEL_ENC_RGB, .mem_planes = 1, .comp_planes = 1, .bpp = अणु 4, 0, 0, 0 पूर्ण, .hभाग = 1, .vभाग = 1 पूर्ण,
		अणु .क्रमmat = V4L2_PIX_FMT_XRGB32,  .pixel_enc = V4L2_PIXEL_ENC_RGB, .mem_planes = 1, .comp_planes = 1, .bpp = अणु 4, 0, 0, 0 पूर्ण, .hभाग = 1, .vभाग = 1 पूर्ण,
		अणु .क्रमmat = V4L2_PIX_FMT_RGBX32,  .pixel_enc = V4L2_PIXEL_ENC_RGB, .mem_planes = 1, .comp_planes = 1, .bpp = अणु 4, 0, 0, 0 पूर्ण, .hभाग = 1, .vभाग = 1 पूर्ण,
		अणु .क्रमmat = V4L2_PIX_FMT_HSV32,   .pixel_enc = V4L2_PIXEL_ENC_RGB, .mem_planes = 1, .comp_planes = 1, .bpp = अणु 4, 0, 0, 0 पूर्ण, .hभाग = 1, .vभाग = 1 पूर्ण,
		अणु .क्रमmat = V4L2_PIX_FMT_ARGB32,  .pixel_enc = V4L2_PIXEL_ENC_RGB, .mem_planes = 1, .comp_planes = 1, .bpp = अणु 4, 0, 0, 0 पूर्ण, .hभाग = 1, .vभाग = 1 पूर्ण,
		अणु .क्रमmat = V4L2_PIX_FMT_RGBA32,  .pixel_enc = V4L2_PIXEL_ENC_RGB, .mem_planes = 1, .comp_planes = 1, .bpp = अणु 4, 0, 0, 0 पूर्ण, .hभाग = 1, .vभाग = 1 पूर्ण,
		अणु .क्रमmat = V4L2_PIX_FMT_ABGR32,  .pixel_enc = V4L2_PIXEL_ENC_RGB, .mem_planes = 1, .comp_planes = 1, .bpp = अणु 4, 0, 0, 0 पूर्ण, .hभाग = 1, .vभाग = 1 पूर्ण,
		अणु .क्रमmat = V4L2_PIX_FMT_BGRA32,  .pixel_enc = V4L2_PIXEL_ENC_RGB, .mem_planes = 1, .comp_planes = 1, .bpp = अणु 4, 0, 0, 0 पूर्ण, .hभाग = 1, .vभाग = 1 पूर्ण,
		अणु .क्रमmat = V4L2_PIX_FMT_RGB565,  .pixel_enc = V4L2_PIXEL_ENC_RGB, .mem_planes = 1, .comp_planes = 1, .bpp = अणु 2, 0, 0, 0 पूर्ण, .hभाग = 1, .vभाग = 1 पूर्ण,
		अणु .क्रमmat = V4L2_PIX_FMT_RGB555,  .pixel_enc = V4L2_PIXEL_ENC_RGB, .mem_planes = 1, .comp_planes = 1, .bpp = अणु 2, 0, 0, 0 पूर्ण, .hभाग = 1, .vभाग = 1 पूर्ण,
		अणु .क्रमmat = V4L2_PIX_FMT_BGR666,  .pixel_enc = V4L2_PIXEL_ENC_RGB, .mem_planes = 1, .comp_planes = 1, .bpp = अणु 4, 0, 0, 0 पूर्ण, .hभाग = 1, .vभाग = 1 पूर्ण,

		/* YUV packed क्रमmats */
		अणु .क्रमmat = V4L2_PIX_FMT_YUYV,    .pixel_enc = V4L2_PIXEL_ENC_YUV, .mem_planes = 1, .comp_planes = 1, .bpp = अणु 2, 0, 0, 0 पूर्ण, .hभाग = 2, .vभाग = 1 पूर्ण,
		अणु .क्रमmat = V4L2_PIX_FMT_YVYU,    .pixel_enc = V4L2_PIXEL_ENC_YUV, .mem_planes = 1, .comp_planes = 1, .bpp = अणु 2, 0, 0, 0 पूर्ण, .hभाग = 2, .vभाग = 1 पूर्ण,
		अणु .क्रमmat = V4L2_PIX_FMT_UYVY,    .pixel_enc = V4L2_PIXEL_ENC_YUV, .mem_planes = 1, .comp_planes = 1, .bpp = अणु 2, 0, 0, 0 पूर्ण, .hभाग = 2, .vभाग = 1 पूर्ण,
		अणु .क्रमmat = V4L2_PIX_FMT_VYUY,    .pixel_enc = V4L2_PIXEL_ENC_YUV, .mem_planes = 1, .comp_planes = 1, .bpp = अणु 2, 0, 0, 0 पूर्ण, .hभाग = 2, .vभाग = 1 पूर्ण,

		/* YUV planar क्रमmats */
		अणु .क्रमmat = V4L2_PIX_FMT_NV12,    .pixel_enc = V4L2_PIXEL_ENC_YUV, .mem_planes = 1, .comp_planes = 2, .bpp = अणु 1, 2, 0, 0 पूर्ण, .hभाग = 2, .vभाग = 2 पूर्ण,
		अणु .क्रमmat = V4L2_PIX_FMT_NV21,    .pixel_enc = V4L2_PIXEL_ENC_YUV, .mem_planes = 1, .comp_planes = 2, .bpp = अणु 1, 2, 0, 0 पूर्ण, .hभाग = 2, .vभाग = 2 पूर्ण,
		अणु .क्रमmat = V4L2_PIX_FMT_NV16,    .pixel_enc = V4L2_PIXEL_ENC_YUV, .mem_planes = 1, .comp_planes = 2, .bpp = अणु 1, 2, 0, 0 पूर्ण, .hभाग = 2, .vभाग = 1 पूर्ण,
		अणु .क्रमmat = V4L2_PIX_FMT_NV61,    .pixel_enc = V4L2_PIXEL_ENC_YUV, .mem_planes = 1, .comp_planes = 2, .bpp = अणु 1, 2, 0, 0 पूर्ण, .hभाग = 2, .vभाग = 1 पूर्ण,
		अणु .क्रमmat = V4L2_PIX_FMT_NV24,    .pixel_enc = V4L2_PIXEL_ENC_YUV, .mem_planes = 1, .comp_planes = 2, .bpp = अणु 1, 2, 0, 0 पूर्ण, .hभाग = 1, .vभाग = 1 पूर्ण,
		अणु .क्रमmat = V4L2_PIX_FMT_NV42,    .pixel_enc = V4L2_PIXEL_ENC_YUV, .mem_planes = 1, .comp_planes = 2, .bpp = अणु 1, 2, 0, 0 पूर्ण, .hभाग = 1, .vभाग = 1 पूर्ण,

		अणु .क्रमmat = V4L2_PIX_FMT_YUV410,  .pixel_enc = V4L2_PIXEL_ENC_YUV, .mem_planes = 1, .comp_planes = 3, .bpp = अणु 1, 1, 1, 0 पूर्ण, .hभाग = 4, .vभाग = 4 पूर्ण,
		अणु .क्रमmat = V4L2_PIX_FMT_YVU410,  .pixel_enc = V4L2_PIXEL_ENC_YUV, .mem_planes = 1, .comp_planes = 3, .bpp = अणु 1, 1, 1, 0 पूर्ण, .hभाग = 4, .vभाग = 4 पूर्ण,
		अणु .क्रमmat = V4L2_PIX_FMT_YUV411P, .pixel_enc = V4L2_PIXEL_ENC_YUV, .mem_planes = 1, .comp_planes = 3, .bpp = अणु 1, 1, 1, 0 पूर्ण, .hभाग = 4, .vभाग = 1 पूर्ण,
		अणु .क्रमmat = V4L2_PIX_FMT_YUV420,  .pixel_enc = V4L2_PIXEL_ENC_YUV, .mem_planes = 1, .comp_planes = 3, .bpp = अणु 1, 1, 1, 0 पूर्ण, .hभाग = 2, .vभाग = 2 पूर्ण,
		अणु .क्रमmat = V4L2_PIX_FMT_YVU420,  .pixel_enc = V4L2_PIXEL_ENC_YUV, .mem_planes = 1, .comp_planes = 3, .bpp = अणु 1, 1, 1, 0 पूर्ण, .hभाग = 2, .vभाग = 2 पूर्ण,
		अणु .क्रमmat = V4L2_PIX_FMT_YUV422P, .pixel_enc = V4L2_PIXEL_ENC_YUV, .mem_planes = 1, .comp_planes = 3, .bpp = अणु 1, 1, 1, 0 पूर्ण, .hभाग = 2, .vभाग = 1 पूर्ण,
		अणु .क्रमmat = V4L2_PIX_FMT_GREY,    .pixel_enc = V4L2_PIXEL_ENC_YUV, .mem_planes = 1, .comp_planes = 1, .bpp = अणु 1, 0, 0, 0 पूर्ण, .hभाग = 1, .vभाग = 1 पूर्ण,

		/* YUV planar क्रमmats, non contiguous variant */
		अणु .क्रमmat = V4L2_PIX_FMT_YUV420M, .pixel_enc = V4L2_PIXEL_ENC_YUV, .mem_planes = 3, .comp_planes = 3, .bpp = अणु 1, 1, 1, 0 पूर्ण, .hभाग = 2, .vभाग = 2 पूर्ण,
		अणु .क्रमmat = V4L2_PIX_FMT_YVU420M, .pixel_enc = V4L2_PIXEL_ENC_YUV, .mem_planes = 3, .comp_planes = 3, .bpp = अणु 1, 1, 1, 0 पूर्ण, .hभाग = 2, .vभाग = 2 पूर्ण,
		अणु .क्रमmat = V4L2_PIX_FMT_YUV422M, .pixel_enc = V4L2_PIXEL_ENC_YUV, .mem_planes = 3, .comp_planes = 3, .bpp = अणु 1, 1, 1, 0 पूर्ण, .hभाग = 2, .vभाग = 1 पूर्ण,
		अणु .क्रमmat = V4L2_PIX_FMT_YVU422M, .pixel_enc = V4L2_PIXEL_ENC_YUV, .mem_planes = 3, .comp_planes = 3, .bpp = अणु 1, 1, 1, 0 पूर्ण, .hभाग = 2, .vभाग = 1 पूर्ण,
		अणु .क्रमmat = V4L2_PIX_FMT_YUV444M, .pixel_enc = V4L2_PIXEL_ENC_YUV, .mem_planes = 3, .comp_planes = 3, .bpp = अणु 1, 1, 1, 0 पूर्ण, .hभाग = 1, .vभाग = 1 पूर्ण,
		अणु .क्रमmat = V4L2_PIX_FMT_YVU444M, .pixel_enc = V4L2_PIXEL_ENC_YUV, .mem_planes = 3, .comp_planes = 3, .bpp = अणु 1, 1, 1, 0 पूर्ण, .hभाग = 1, .vभाग = 1 पूर्ण,

		अणु .क्रमmat = V4L2_PIX_FMT_NV12M,   .pixel_enc = V4L2_PIXEL_ENC_YUV, .mem_planes = 2, .comp_planes = 2, .bpp = अणु 1, 2, 0, 0 पूर्ण, .hभाग = 2, .vभाग = 2 पूर्ण,
		अणु .क्रमmat = V4L2_PIX_FMT_NV21M,   .pixel_enc = V4L2_PIXEL_ENC_YUV, .mem_planes = 2, .comp_planes = 2, .bpp = अणु 1, 2, 0, 0 पूर्ण, .hभाग = 2, .vभाग = 2 पूर्ण,
		अणु .क्रमmat = V4L2_PIX_FMT_NV16M,   .pixel_enc = V4L2_PIXEL_ENC_YUV, .mem_planes = 2, .comp_planes = 2, .bpp = अणु 1, 2, 0, 0 पूर्ण, .hभाग = 2, .vभाग = 1 पूर्ण,
		अणु .क्रमmat = V4L2_PIX_FMT_NV61M,   .pixel_enc = V4L2_PIXEL_ENC_YUV, .mem_planes = 2, .comp_planes = 2, .bpp = अणु 1, 2, 0, 0 पूर्ण, .hभाग = 2, .vभाग = 1 पूर्ण,

		/* Bayer RGB क्रमmats */
		अणु .क्रमmat = V4L2_PIX_FMT_SBGGR8,	.pixel_enc = V4L2_PIXEL_ENC_BAYER, .mem_planes = 1, .comp_planes = 1, .bpp = अणु 1, 0, 0, 0 पूर्ण, .hभाग = 1, .vभाग = 1 पूर्ण,
		अणु .क्रमmat = V4L2_PIX_FMT_SGBRG8,	.pixel_enc = V4L2_PIXEL_ENC_BAYER, .mem_planes = 1, .comp_planes = 1, .bpp = अणु 1, 0, 0, 0 पूर्ण, .hभाग = 1, .vभाग = 1 पूर्ण,
		अणु .क्रमmat = V4L2_PIX_FMT_SGRBG8,	.pixel_enc = V4L2_PIXEL_ENC_BAYER, .mem_planes = 1, .comp_planes = 1, .bpp = अणु 1, 0, 0, 0 पूर्ण, .hभाग = 1, .vभाग = 1 पूर्ण,
		अणु .क्रमmat = V4L2_PIX_FMT_SRGGB8,	.pixel_enc = V4L2_PIXEL_ENC_BAYER, .mem_planes = 1, .comp_planes = 1, .bpp = अणु 1, 0, 0, 0 पूर्ण, .hभाग = 1, .vभाग = 1 पूर्ण,
		अणु .क्रमmat = V4L2_PIX_FMT_SBGGR10,	.pixel_enc = V4L2_PIXEL_ENC_BAYER, .mem_planes = 1, .comp_planes = 1, .bpp = अणु 2, 0, 0, 0 पूर्ण, .hभाग = 1, .vभाग = 1 पूर्ण,
		अणु .क्रमmat = V4L2_PIX_FMT_SGBRG10,	.pixel_enc = V4L2_PIXEL_ENC_BAYER, .mem_planes = 1, .comp_planes = 1, .bpp = अणु 2, 0, 0, 0 पूर्ण, .hभाग = 1, .vभाग = 1 पूर्ण,
		अणु .क्रमmat = V4L2_PIX_FMT_SGRBG10,	.pixel_enc = V4L2_PIXEL_ENC_BAYER, .mem_planes = 1, .comp_planes = 1, .bpp = अणु 2, 0, 0, 0 पूर्ण, .hभाग = 1, .vभाग = 1 पूर्ण,
		अणु .क्रमmat = V4L2_PIX_FMT_SRGGB10,	.pixel_enc = V4L2_PIXEL_ENC_BAYER, .mem_planes = 1, .comp_planes = 1, .bpp = अणु 2, 0, 0, 0 पूर्ण, .hभाग = 1, .vभाग = 1 पूर्ण,
		अणु .क्रमmat = V4L2_PIX_FMT_SBGGR10ALAW8,	.pixel_enc = V4L2_PIXEL_ENC_BAYER, .mem_planes = 1, .comp_planes = 1, .bpp = अणु 1, 0, 0, 0 पूर्ण, .hभाग = 1, .vभाग = 1 पूर्ण,
		अणु .क्रमmat = V4L2_PIX_FMT_SGBRG10ALAW8,	.pixel_enc = V4L2_PIXEL_ENC_BAYER, .mem_planes = 1, .comp_planes = 1, .bpp = अणु 1, 0, 0, 0 पूर्ण, .hभाग = 1, .vभाग = 1 पूर्ण,
		अणु .क्रमmat = V4L2_PIX_FMT_SGRBG10ALAW8,	.pixel_enc = V4L2_PIXEL_ENC_BAYER, .mem_planes = 1, .comp_planes = 1, .bpp = अणु 1, 0, 0, 0 पूर्ण, .hभाग = 1, .vभाग = 1 पूर्ण,
		अणु .क्रमmat = V4L2_PIX_FMT_SRGGB10ALAW8,	.pixel_enc = V4L2_PIXEL_ENC_BAYER, .mem_planes = 1, .comp_planes = 1, .bpp = अणु 1, 0, 0, 0 पूर्ण, .hभाग = 1, .vभाग = 1 पूर्ण,
		अणु .क्रमmat = V4L2_PIX_FMT_SBGGR10DPCM8,	.pixel_enc = V4L2_PIXEL_ENC_BAYER, .mem_planes = 1, .comp_planes = 1, .bpp = अणु 1, 0, 0, 0 पूर्ण, .hभाग = 1, .vभाग = 1 पूर्ण,
		अणु .क्रमmat = V4L2_PIX_FMT_SGBRG10DPCM8,	.pixel_enc = V4L2_PIXEL_ENC_BAYER, .mem_planes = 1, .comp_planes = 1, .bpp = अणु 1, 0, 0, 0 पूर्ण, .hभाग = 1, .vभाग = 1 पूर्ण,
		अणु .क्रमmat = V4L2_PIX_FMT_SGRBG10DPCM8,	.pixel_enc = V4L2_PIXEL_ENC_BAYER, .mem_planes = 1, .comp_planes = 1, .bpp = अणु 1, 0, 0, 0 पूर्ण, .hभाग = 1, .vभाग = 1 पूर्ण,
		अणु .क्रमmat = V4L2_PIX_FMT_SRGGB10DPCM8,	.pixel_enc = V4L2_PIXEL_ENC_BAYER, .mem_planes = 1, .comp_planes = 1, .bpp = अणु 1, 0, 0, 0 पूर्ण, .hभाग = 1, .vभाग = 1 पूर्ण,
		अणु .क्रमmat = V4L2_PIX_FMT_SBGGR12,	.pixel_enc = V4L2_PIXEL_ENC_BAYER, .mem_planes = 1, .comp_planes = 1, .bpp = अणु 2, 0, 0, 0 पूर्ण, .hभाग = 1, .vभाग = 1 पूर्ण,
		अणु .क्रमmat = V4L2_PIX_FMT_SGBRG12,	.pixel_enc = V4L2_PIXEL_ENC_BAYER, .mem_planes = 1, .comp_planes = 1, .bpp = अणु 2, 0, 0, 0 पूर्ण, .hभाग = 1, .vभाग = 1 पूर्ण,
		अणु .क्रमmat = V4L2_PIX_FMT_SGRBG12,	.pixel_enc = V4L2_PIXEL_ENC_BAYER, .mem_planes = 1, .comp_planes = 1, .bpp = अणु 2, 0, 0, 0 पूर्ण, .hभाग = 1, .vभाग = 1 पूर्ण,
		अणु .क्रमmat = V4L2_PIX_FMT_SRGGB12,	.pixel_enc = V4L2_PIXEL_ENC_BAYER, .mem_planes = 1, .comp_planes = 1, .bpp = अणु 2, 0, 0, 0 पूर्ण, .hभाग = 1, .vभाग = 1 पूर्ण,
	पूर्ण;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(क्रमmats); ++i)
		अगर (क्रमmats[i].क्रमmat == क्रमmat)
			वापस &क्रमmats[i];
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(v4l2_क्रमmat_info);

अटल अंतरभूत अचिन्हित पूर्णांक v4l2_क्रमmat_block_width(स्थिर काष्ठा v4l2_क्रमmat_info *info, पूर्णांक plane)
अणु
	अगर (!info->block_w[plane])
		वापस 1;
	वापस info->block_w[plane];
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक v4l2_क्रमmat_block_height(स्थिर काष्ठा v4l2_क्रमmat_info *info, पूर्णांक plane)
अणु
	अगर (!info->block_h[plane])
		वापस 1;
	वापस info->block_h[plane];
पूर्ण

व्योम v4l2_apply_frmsize_स्थिरraपूर्णांकs(u32 *width, u32 *height,
				    स्थिर काष्ठा v4l2_frmsize_stepwise *frmsize)
अणु
	अगर (!frmsize)
		वापस;

	/*
	 * Clamp width/height to meet min/max स्थिरraपूर्णांकs and round it up to
	 * macroblock alignment.
	 */
	*width = clamp_roundup(*width, frmsize->min_width, frmsize->max_width,
			       frmsize->step_width);
	*height = clamp_roundup(*height, frmsize->min_height, frmsize->max_height,
				frmsize->step_height);
पूर्ण
EXPORT_SYMBOL_GPL(v4l2_apply_frmsize_स्थिरraपूर्णांकs);

पूर्णांक v4l2_fill_pixfmt_mp(काष्ठा v4l2_pix_क्रमmat_mplane *pixfmt,
			u32 pixelक्रमmat, u32 width, u32 height)
अणु
	स्थिर काष्ठा v4l2_क्रमmat_info *info;
	काष्ठा v4l2_plane_pix_क्रमmat *plane;
	पूर्णांक i;

	info = v4l2_क्रमmat_info(pixelक्रमmat);
	अगर (!info)
		वापस -EINVAL;

	pixfmt->width = width;
	pixfmt->height = height;
	pixfmt->pixelक्रमmat = pixelक्रमmat;
	pixfmt->num_planes = info->mem_planes;

	अगर (info->mem_planes == 1) अणु
		plane = &pixfmt->plane_fmt[0];
		plane->bytesperline = ALIGN(width, v4l2_क्रमmat_block_width(info, 0)) * info->bpp[0];
		plane->sizeimage = 0;

		क्रम (i = 0; i < info->comp_planes; i++) अणु
			अचिन्हित पूर्णांक hभाग = (i == 0) ? 1 : info->hभाग;
			अचिन्हित पूर्णांक vभाग = (i == 0) ? 1 : info->vभाग;
			अचिन्हित पूर्णांक aligned_width;
			अचिन्हित पूर्णांक aligned_height;

			aligned_width = ALIGN(width, v4l2_क्रमmat_block_width(info, i));
			aligned_height = ALIGN(height, v4l2_क्रमmat_block_height(info, i));

			plane->sizeimage += info->bpp[i] *
				DIV_ROUND_UP(aligned_width, hभाग) *
				DIV_ROUND_UP(aligned_height, vभाग);
		पूर्ण
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < info->comp_planes; i++) अणु
			अचिन्हित पूर्णांक hभाग = (i == 0) ? 1 : info->hभाग;
			अचिन्हित पूर्णांक vभाग = (i == 0) ? 1 : info->vभाग;
			अचिन्हित पूर्णांक aligned_width;
			अचिन्हित पूर्णांक aligned_height;

			aligned_width = ALIGN(width, v4l2_क्रमmat_block_width(info, i));
			aligned_height = ALIGN(height, v4l2_क्रमmat_block_height(info, i));

			plane = &pixfmt->plane_fmt[i];
			plane->bytesperline =
				info->bpp[i] * DIV_ROUND_UP(aligned_width, hभाग);
			plane->sizeimage =
				plane->bytesperline * DIV_ROUND_UP(aligned_height, vभाग);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(v4l2_fill_pixfmt_mp);

पूर्णांक v4l2_fill_pixfmt(काष्ठा v4l2_pix_क्रमmat *pixfmt, u32 pixelक्रमmat,
		     u32 width, u32 height)
अणु
	स्थिर काष्ठा v4l2_क्रमmat_info *info;
	पूर्णांक i;

	info = v4l2_क्रमmat_info(pixelक्रमmat);
	अगर (!info)
		वापस -EINVAL;

	/* Single planar API cannot be used क्रम multi plane क्रमmats. */
	अगर (info->mem_planes > 1)
		वापस -EINVAL;

	pixfmt->width = width;
	pixfmt->height = height;
	pixfmt->pixelक्रमmat = pixelक्रमmat;
	pixfmt->bytesperline = ALIGN(width, v4l2_क्रमmat_block_width(info, 0)) * info->bpp[0];
	pixfmt->sizeimage = 0;

	क्रम (i = 0; i < info->comp_planes; i++) अणु
		अचिन्हित पूर्णांक hभाग = (i == 0) ? 1 : info->hभाग;
		अचिन्हित पूर्णांक vभाग = (i == 0) ? 1 : info->vभाग;
		अचिन्हित पूर्णांक aligned_width;
		अचिन्हित पूर्णांक aligned_height;

		aligned_width = ALIGN(width, v4l2_क्रमmat_block_width(info, i));
		aligned_height = ALIGN(height, v4l2_क्रमmat_block_height(info, i));

		pixfmt->sizeimage += info->bpp[i] *
			DIV_ROUND_UP(aligned_width, hभाग) *
			DIV_ROUND_UP(aligned_height, vभाग);
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(v4l2_fill_pixfmt);

s64 v4l2_get_link_freq(काष्ठा v4l2_ctrl_handler *handler, अचिन्हित पूर्णांक mul,
		       अचिन्हित पूर्णांक भाग)
अणु
	काष्ठा v4l2_ctrl *ctrl;
	s64 freq;

	ctrl = v4l2_ctrl_find(handler, V4L2_CID_LINK_FREQ);
	अगर (ctrl) अणु
		काष्ठा v4l2_querymenu qm = अणु .id = V4L2_CID_LINK_FREQ पूर्ण;
		पूर्णांक ret;

		qm.index = v4l2_ctrl_g_ctrl(ctrl);

		ret = v4l2_querymenu(handler, &qm);
		अगर (ret)
			वापस -ENOENT;

		freq = qm.value;
	पूर्ण अन्यथा अणु
		अगर (!mul || !भाग)
			वापस -ENOENT;

		ctrl = v4l2_ctrl_find(handler, V4L2_CID_PIXEL_RATE);
		अगर (!ctrl)
			वापस -ENOENT;

		freq = भाग_u64(v4l2_ctrl_g_ctrl_पूर्णांक64(ctrl) * mul, भाग);

		pr_warn("%s: Link frequency estimated using pixel rate: result might be inaccurate\n",
			__func__);
		pr_warn("%s: Consider implementing support for V4L2_CID_LINK_FREQ in the transmitter driver\n",
			__func__);
	पूर्ण

	वापस freq > 0 ? freq : -EINVAL;
पूर्ण
EXPORT_SYMBOL_GPL(v4l2_get_link_freq);
