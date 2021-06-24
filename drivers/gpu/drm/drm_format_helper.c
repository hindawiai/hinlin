<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 or MIT
/*
 * Copyright (C) 2016 Noralf Trथचnnes
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/पन.स>

#समावेश <drm/drm_क्रमmat_helper.h>
#समावेश <drm/drm_framebuffer.h>
#समावेश <drm/drm_fourcc.h>
#समावेश <drm/drm_rect.h>

अटल अचिन्हित पूर्णांक clip_offset(काष्ठा drm_rect *clip,
				अचिन्हित पूर्णांक pitch, अचिन्हित पूर्णांक cpp)
अणु
	वापस clip->y1 * pitch + clip->x1 * cpp;
पूर्ण

/**
 * drm_fb_स_नकल - Copy clip buffer
 * @dst: Destination buffer
 * @vaddr: Source buffer
 * @fb: DRM framebuffer
 * @clip: Clip rectangle area to copy
 *
 * This function करोes not apply clipping on dst, i.e. the destination
 * is a small buffer containing the clip rect only.
 */
व्योम drm_fb_स_नकल(व्योम *dst, व्योम *vaddr, काष्ठा drm_framebuffer *fb,
		   काष्ठा drm_rect *clip)
अणु
	अचिन्हित पूर्णांक cpp = fb->क्रमmat->cpp[0];
	माप_प्रकार len = (clip->x2 - clip->x1) * cpp;
	अचिन्हित पूर्णांक y, lines = clip->y2 - clip->y1;

	vaddr += clip_offset(clip, fb->pitches[0], cpp);
	क्रम (y = 0; y < lines; y++) अणु
		स_नकल(dst, vaddr, len);
		vaddr += fb->pitches[0];
		dst += len;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(drm_fb_स_नकल);

/**
 * drm_fb_स_नकल_dstclip - Copy clip buffer
 * @dst: Destination buffer (iomem)
 * @vaddr: Source buffer
 * @fb: DRM framebuffer
 * @clip: Clip rectangle area to copy
 *
 * This function applies clipping on dst, i.e. the destination is a
 * full (iomem) framebuffer but only the clip rect content is copied over.
 */
व्योम drm_fb_स_नकल_dstclip(व्योम __iomem *dst, व्योम *vaddr,
			   काष्ठा drm_framebuffer *fb,
			   काष्ठा drm_rect *clip)
अणु
	अचिन्हित पूर्णांक cpp = fb->क्रमmat->cpp[0];
	अचिन्हित पूर्णांक offset = clip_offset(clip, fb->pitches[0], cpp);
	माप_प्रकार len = (clip->x2 - clip->x1) * cpp;
	अचिन्हित पूर्णांक y, lines = clip->y2 - clip->y1;

	vaddr += offset;
	dst += offset;
	क्रम (y = 0; y < lines; y++) अणु
		स_नकल_toio(dst, vaddr, len);
		vaddr += fb->pitches[0];
		dst += fb->pitches[0];
	पूर्ण
पूर्ण
EXPORT_SYMBOL(drm_fb_स_नकल_dstclip);

/**
 * drm_fb_swab - Swap bytes पूर्णांकo clip buffer
 * @dst: Destination buffer
 * @src: Source buffer
 * @fb: DRM framebuffer
 * @clip: Clip rectangle area to copy
 * @cached: Source buffer is mapped cached (eg. not ग_लिखो-combined)
 *
 * If @cached is false a temporary buffer is used to cache one pixel line at a
 * समय to speed up slow uncached पढ़ोs.
 *
 * This function करोes not apply clipping on dst, i.e. the destination
 * is a small buffer containing the clip rect only.
 */
व्योम drm_fb_swab(व्योम *dst, व्योम *src, काष्ठा drm_framebuffer *fb,
		 काष्ठा drm_rect *clip, bool cached)
अणु
	u8 cpp = fb->क्रमmat->cpp[0];
	माप_प्रकार len = drm_rect_width(clip) * cpp;
	u16 *src16, *dst16 = dst;
	u32 *src32, *dst32 = dst;
	अचिन्हित पूर्णांक x, y;
	व्योम *buf = शून्य;

	अगर (WARN_ON_ONCE(cpp != 2 && cpp != 4))
		वापस;

	अगर (!cached)
		buf = kदो_स्मृति(len, GFP_KERNEL);

	src += clip_offset(clip, fb->pitches[0], cpp);

	क्रम (y = clip->y1; y < clip->y2; y++) अणु
		अगर (buf) अणु
			स_नकल(buf, src, len);
			src16 = buf;
			src32 = buf;
		पूर्ण अन्यथा अणु
			src16 = src;
			src32 = src;
		पूर्ण

		क्रम (x = clip->x1; x < clip->x2; x++) अणु
			अगर (cpp == 4)
				*dst32++ = swab32(*src32++);
			अन्यथा
				*dst16++ = swab16(*src16++);
		पूर्ण

		src += fb->pitches[0];
	पूर्ण

	kमुक्त(buf);
पूर्ण
EXPORT_SYMBOL(drm_fb_swab);

अटल व्योम drm_fb_xrgb8888_to_rgb565_line(u16 *dbuf, u32 *sbuf,
					   अचिन्हित पूर्णांक pixels,
					   bool swab)
अणु
	अचिन्हित पूर्णांक x;
	u16 val16;

	क्रम (x = 0; x < pixels; x++) अणु
		val16 = ((sbuf[x] & 0x00F80000) >> 8) |
			((sbuf[x] & 0x0000FC00) >> 5) |
			((sbuf[x] & 0x000000F8) >> 3);
		अगर (swab)
			dbuf[x] = swab16(val16);
		अन्यथा
			dbuf[x] = val16;
	पूर्ण
पूर्ण

/**
 * drm_fb_xrgb8888_to_rgb565 - Convert XRGB8888 to RGB565 clip buffer
 * @dst: RGB565 destination buffer
 * @vaddr: XRGB8888 source buffer
 * @fb: DRM framebuffer
 * @clip: Clip rectangle area to copy
 * @swab: Swap bytes
 *
 * Drivers can use this function क्रम RGB565 devices that करोn't natively
 * support XRGB8888.
 *
 * This function करोes not apply clipping on dst, i.e. the destination
 * is a small buffer containing the clip rect only.
 */
व्योम drm_fb_xrgb8888_to_rgb565(व्योम *dst, व्योम *vaddr,
			       काष्ठा drm_framebuffer *fb,
			       काष्ठा drm_rect *clip, bool swab)
अणु
	माप_प्रकार linepixels = clip->x2 - clip->x1;
	माप_प्रकार src_len = linepixels * माप(u32);
	माप_प्रकार dst_len = linepixels * माप(u16);
	अचिन्हित y, lines = clip->y2 - clip->y1;
	व्योम *sbuf;

	/*
	 * The cma memory is ग_लिखो-combined so पढ़ोs are uncached.
	 * Speed up by fetching one line at a समय.
	 */
	sbuf = kदो_स्मृति(src_len, GFP_KERNEL);
	अगर (!sbuf)
		वापस;

	vaddr += clip_offset(clip, fb->pitches[0], माप(u32));
	क्रम (y = 0; y < lines; y++) अणु
		स_नकल(sbuf, vaddr, src_len);
		drm_fb_xrgb8888_to_rgb565_line(dst, sbuf, linepixels, swab);
		vaddr += fb->pitches[0];
		dst += dst_len;
	पूर्ण

	kमुक्त(sbuf);
पूर्ण
EXPORT_SYMBOL(drm_fb_xrgb8888_to_rgb565);

/**
 * drm_fb_xrgb8888_to_rgb565_dstclip - Convert XRGB8888 to RGB565 clip buffer
 * @dst: RGB565 destination buffer (iomem)
 * @dst_pitch: destination buffer pitch
 * @vaddr: XRGB8888 source buffer
 * @fb: DRM framebuffer
 * @clip: Clip rectangle area to copy
 * @swab: Swap bytes
 *
 * Drivers can use this function क्रम RGB565 devices that करोn't natively
 * support XRGB8888.
 *
 * This function applies clipping on dst, i.e. the destination is a
 * full (iomem) framebuffer but only the clip rect content is copied over.
 */
व्योम drm_fb_xrgb8888_to_rgb565_dstclip(व्योम __iomem *dst, अचिन्हित पूर्णांक dst_pitch,
				       व्योम *vaddr, काष्ठा drm_framebuffer *fb,
				       काष्ठा drm_rect *clip, bool swab)
अणु
	माप_प्रकार linepixels = clip->x2 - clip->x1;
	माप_प्रकार dst_len = linepixels * माप(u16);
	अचिन्हित y, lines = clip->y2 - clip->y1;
	व्योम *dbuf;

	dbuf = kदो_स्मृति(dst_len, GFP_KERNEL);
	अगर (!dbuf)
		वापस;

	vaddr += clip_offset(clip, fb->pitches[0], माप(u32));
	dst += clip_offset(clip, dst_pitch, माप(u16));
	क्रम (y = 0; y < lines; y++) अणु
		drm_fb_xrgb8888_to_rgb565_line(dbuf, vaddr, linepixels, swab);
		स_नकल_toio(dst, dbuf, dst_len);
		vaddr += fb->pitches[0];
		dst += dst_len;
	पूर्ण

	kमुक्त(dbuf);
पूर्ण
EXPORT_SYMBOL(drm_fb_xrgb8888_to_rgb565_dstclip);

अटल व्योम drm_fb_xrgb8888_to_rgb888_line(u8 *dbuf, u32 *sbuf,
					   अचिन्हित पूर्णांक pixels)
अणु
	अचिन्हित पूर्णांक x;

	क्रम (x = 0; x < pixels; x++) अणु
		*dbuf++ = (sbuf[x] & 0x000000FF) >>  0;
		*dbuf++ = (sbuf[x] & 0x0000FF00) >>  8;
		*dbuf++ = (sbuf[x] & 0x00FF0000) >> 16;
	पूर्ण
पूर्ण

/**
 * drm_fb_xrgb8888_to_rgb888_dstclip - Convert XRGB8888 to RGB888 clip buffer
 * @dst: RGB565 destination buffer (iomem)
 * @dst_pitch: destination buffer pitch
 * @vaddr: XRGB8888 source buffer
 * @fb: DRM framebuffer
 * @clip: Clip rectangle area to copy
 *
 * Drivers can use this function क्रम RGB888 devices that करोn't natively
 * support XRGB8888.
 *
 * This function applies clipping on dst, i.e. the destination is a
 * full (iomem) framebuffer but only the clip rect content is copied over.
 */
व्योम drm_fb_xrgb8888_to_rgb888_dstclip(व्योम __iomem *dst, अचिन्हित पूर्णांक dst_pitch,
				       व्योम *vaddr, काष्ठा drm_framebuffer *fb,
				       काष्ठा drm_rect *clip)
अणु
	माप_प्रकार linepixels = clip->x2 - clip->x1;
	माप_प्रकार dst_len = linepixels * 3;
	अचिन्हित y, lines = clip->y2 - clip->y1;
	व्योम *dbuf;

	dbuf = kदो_स्मृति(dst_len, GFP_KERNEL);
	अगर (!dbuf)
		वापस;

	vaddr += clip_offset(clip, fb->pitches[0], माप(u32));
	dst += clip_offset(clip, dst_pitch, माप(u16));
	क्रम (y = 0; y < lines; y++) अणु
		drm_fb_xrgb8888_to_rgb888_line(dbuf, vaddr, linepixels);
		स_नकल_toio(dst, dbuf, dst_len);
		vaddr += fb->pitches[0];
		dst += dst_len;
	पूर्ण

	kमुक्त(dbuf);
पूर्ण
EXPORT_SYMBOL(drm_fb_xrgb8888_to_rgb888_dstclip);

/**
 * drm_fb_xrgb8888_to_gray8 - Convert XRGB8888 to grayscale
 * @dst: 8-bit grayscale destination buffer
 * @vaddr: XRGB8888 source buffer
 * @fb: DRM framebuffer
 * @clip: Clip rectangle area to copy
 *
 * Drm करोesn't have native monochrome or grayscale support.
 * Such drivers can announce the commonly supported XR24 क्रमmat to userspace
 * and use this function to convert to the native क्रमmat.
 *
 * Monochrome drivers will use the most signअगरicant bit,
 * where 1 means क्रमeground color and 0 background color.
 *
 * ITU BT.601 is used क्रम the RGB -> luma (brightness) conversion.
 */
व्योम drm_fb_xrgb8888_to_gray8(u8 *dst, व्योम *vaddr, काष्ठा drm_framebuffer *fb,
			       काष्ठा drm_rect *clip)
अणु
	अचिन्हित पूर्णांक len = (clip->x2 - clip->x1) * माप(u32);
	अचिन्हित पूर्णांक x, y;
	व्योम *buf;
	u32 *src;

	अगर (WARN_ON(fb->क्रमmat->क्रमmat != DRM_FORMAT_XRGB8888))
		वापस;
	/*
	 * The cma memory is ग_लिखो-combined so पढ़ोs are uncached.
	 * Speed up by fetching one line at a समय.
	 */
	buf = kदो_स्मृति(len, GFP_KERNEL);
	अगर (!buf)
		वापस;

	क्रम (y = clip->y1; y < clip->y2; y++) अणु
		src = vaddr + (y * fb->pitches[0]);
		src += clip->x1;
		स_नकल(buf, src, len);
		src = buf;
		क्रम (x = clip->x1; x < clip->x2; x++) अणु
			u8 r = (*src & 0x00ff0000) >> 16;
			u8 g = (*src & 0x0000ff00) >> 8;
			u8 b =  *src & 0x000000ff;

			/* ITU BT.601: Y = 0.299 R + 0.587 G + 0.114 B */
			*dst++ = (3 * r + 6 * g + b) / 10;
			src++;
		पूर्ण
	पूर्ण

	kमुक्त(buf);
पूर्ण
EXPORT_SYMBOL(drm_fb_xrgb8888_to_gray8);

