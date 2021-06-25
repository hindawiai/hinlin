<शैली गुरु>
/**
 * \पile drm_sarea.h
 * \मrief SAREA definitions
 *
 * \चuthor Michel Dथअnzer <michel@daenzer.net>
 */

/*
 * Copyright 2002 Tungsten Graphics, Inc., Cedar Park, Texas.
 * All Rights Reserved.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * TUNGSTEN GRAPHICS AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#अगर_अघोषित _DRM_SAREA_H_
#घोषणा _DRM_SAREA_H_

#समावेश "drm.h"

#अगर defined(__cplusplus)
बाह्य "C" अणु
#पूर्ण_अगर

/* SAREA area needs to be at least a page */
#अगर defined(__alpha__)
#घोषणा SAREA_MAX                       0x2000U
#या_अगर defined(__mips__)
#घोषणा SAREA_MAX                       0x4000U
#या_अगर defined(__ia64__)
#घोषणा SAREA_MAX                       0x10000U	/* 64kB */
#अन्यथा
/* Intel 830M driver needs at least 8k SAREA */
#घोषणा SAREA_MAX                       0x2000U
#पूर्ण_अगर

/** Maximum number of drawables in the SAREA */
#घोषणा SAREA_MAX_DRAWABLES		256

#घोषणा SAREA_DRAWABLE_CLAIMED_ENTRY    0x80000000

/** SAREA drawable */
काष्ठा drm_sarea_drawable अणु
	अचिन्हित पूर्णांक stamp;
	अचिन्हित पूर्णांक flags;
पूर्ण;

/** SAREA frame */
काष्ठा drm_sarea_frame अणु
	अचिन्हित पूर्णांक x;
	अचिन्हित पूर्णांक y;
	अचिन्हित पूर्णांक width;
	अचिन्हित पूर्णांक height;
	अचिन्हित पूर्णांक fullscreen;
पूर्ण;

/** SAREA */
काष्ठा drm_sarea अणु
    /** first thing is always the DRM locking काष्ठाure */
	काष्ठा drm_hw_lock lock;
    /** \टoकरो Use पढ़ोers/ग_लिखोr lock क्रम drm_sarea::drawable_lock */
	काष्ठा drm_hw_lock drawable_lock;
	काष्ठा drm_sarea_drawable drawableTable[SAREA_MAX_DRAWABLES];	/**< drawables */
	काष्ठा drm_sarea_frame frame;	/**< frame */
	drm_context_t dummy_context;
पूर्ण;

#अगर_अघोषित __KERNEL__
प्रकार काष्ठा drm_sarea_drawable drm_sarea_drawable_t;
प्रकार काष्ठा drm_sarea_frame drm_sarea_frame_t;
प्रकार काष्ठा drm_sarea drm_sarea_t;
#पूर्ण_अगर

#अगर defined(__cplusplus)
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर				/* _DRM_SAREA_H_ */
