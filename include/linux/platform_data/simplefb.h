<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * simplefb.h - Simple Framebuffer Device
 *
 * Copyright (C) 2013 David Herrmann <dh.herrmann@gmail.com>
 */

#अगर_अघोषित __PLATFORM_DATA_SIMPLEFB_H__
#घोषणा __PLATFORM_DATA_SIMPLEFB_H__

#समावेश <drm/drm_fourcc.h>
#समावेश <linux/fb.h>
#समावेश <linux/types.h>

/* क्रमmat array, use it to initialize a "struct simplefb_format" array */
#घोषणा SIMPLEFB_FORMATS \
अणु \
	अणु "r5g6b5", 16, अणु11, 5पूर्ण, अणु5, 6पूर्ण, अणु0, 5पूर्ण, अणु0, 0पूर्ण, DRM_FORMAT_RGB565 पूर्ण, \
	अणु "r5g5b5a1", 16, अणु11, 5पूर्ण, अणु6, 5पूर्ण, अणु1, 5पूर्ण, अणु0, 1पूर्ण, DRM_FORMAT_RGBA5551 पूर्ण, \
	अणु "x1r5g5b5", 16, अणु10, 5पूर्ण, अणु5, 5पूर्ण, अणु0, 5पूर्ण, अणु0, 0पूर्ण, DRM_FORMAT_XRGB1555 पूर्ण, \
	अणु "a1r5g5b5", 16, अणु10, 5पूर्ण, अणु5, 5पूर्ण, अणु0, 5पूर्ण, अणु15, 1पूर्ण, DRM_FORMAT_ARGB1555 पूर्ण, \
	अणु "r8g8b8", 24, अणु16, 8पूर्ण, अणु8, 8पूर्ण, अणु0, 8पूर्ण, अणु0, 0पूर्ण, DRM_FORMAT_RGB888 पूर्ण, \
	अणु "x8r8g8b8", 32, अणु16, 8पूर्ण, अणु8, 8पूर्ण, अणु0, 8पूर्ण, अणु0, 0पूर्ण, DRM_FORMAT_XRGB8888 पूर्ण, \
	अणु "a8r8g8b8", 32, अणु16, 8पूर्ण, अणु8, 8पूर्ण, अणु0, 8पूर्ण, अणु24, 8पूर्ण, DRM_FORMAT_ARGB8888 पूर्ण, \
	अणु "a8b8g8r8", 32, अणु0, 8पूर्ण, अणु8, 8पूर्ण, अणु16, 8पूर्ण, अणु24, 8पूर्ण, DRM_FORMAT_ABGR8888 पूर्ण, \
	अणु "x2r10g10b10", 32, अणु20, 10पूर्ण, अणु10, 10पूर्ण, अणु0, 10पूर्ण, अणु0, 0पूर्ण, DRM_FORMAT_XRGB2101010 पूर्ण, \
	अणु "a2r10g10b10", 32, अणु20, 10पूर्ण, अणु10, 10पूर्ण, अणु0, 10पूर्ण, अणु30, 2पूर्ण, DRM_FORMAT_ARGB2101010 पूर्ण, \
पूर्ण

/*
 * Data-Format क्रम Simple-Framebuffers
 * @name: unique 0-terminated name that can be used to identअगरy the mode
 * @red,green,blue: Offsets and sizes of the single RGB parts
 * @transp: Offset and size of the alpha bits. length=0 means no alpha
 * @fourcc: 32bit DRM four-CC code (see drm_fourcc.h)
 */
काष्ठा simplefb_क्रमmat अणु
	स्थिर अक्षर *name;
	u32 bits_per_pixel;
	काष्ठा fb_bitfield red;
	काष्ठा fb_bitfield green;
	काष्ठा fb_bitfield blue;
	काष्ठा fb_bitfield transp;
	u32 fourcc;
पूर्ण;

/*
 * Simple-Framebuffer description
 * If the arch-boot code creates simple-framebuffers without DT support, it
 * can pass the width, height, stride and क्रमmat via this platक्रमm-data object.
 * The framebuffer location must be given as IORESOURCE_MEM resource.
 * @क्रमmat must be a क्रमmat as described in "struct simplefb_format" above.
 */
काष्ठा simplefb_platक्रमm_data अणु
	u32 width;
	u32 height;
	u32 stride;
	स्थिर अक्षर *क्रमmat;
पूर्ण;

#पूर्ण_अगर /* __PLATFORM_DATA_SIMPLEFB_H__ */
