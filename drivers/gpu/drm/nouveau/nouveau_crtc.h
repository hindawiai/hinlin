<शैली गुरु>
/*
 * Copyright (C) 2008 Maarten Maathuis.
 * All Rights Reserved.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining
 * a copy of this software and associated करोcumentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modअगरy, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to करो so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice (including the
 * next paragraph) shall be included in all copies or substantial
 * portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE COPYRIGHT OWNER(S) AND/OR ITS SUPPLIERS BE
 * LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 */

#अगर_अघोषित __NOUVEAU_CRTC_H__
#घोषणा __NOUVEAU_CRTC_H__

#समावेश <drm/drm_crtc.h>

#समावेश <nvअगर/notअगरy.h>

काष्ठा nouveau_crtc अणु
	काष्ठा drm_crtc base;

	पूर्णांक index;
	काष्ठा nvअगर_notअगरy vblank;

	uपूर्णांक32_t dpms_saved_fp_control;
	uपूर्णांक32_t fp_users;
	पूर्णांक saturation;
	पूर्णांक sharpness;
	पूर्णांक last_dpms;

	पूर्णांक cursor_saved_x, cursor_saved_y;

	काष्ठा अणु
		पूर्णांक cpp;
		bool blanked;
		uपूर्णांक32_t offset;
		uपूर्णांक32_t handle;
	पूर्ण fb;

	काष्ठा अणु
		काष्ठा nouveau_bo *nvbo;
		uपूर्णांक32_t offset;
		व्योम (*set_offset)(काष्ठा nouveau_crtc *, uपूर्णांक32_t offset);
		व्योम (*set_pos)(काष्ठा nouveau_crtc *, पूर्णांक x, पूर्णांक y);
		व्योम (*hide)(काष्ठा nouveau_crtc *, bool update);
		व्योम (*show)(काष्ठा nouveau_crtc *, bool update);
	पूर्ण cursor;

	काष्ठा अणु
		पूर्णांक depth;
	पूर्ण lut;

	व्योम (*save)(काष्ठा drm_crtc *crtc);
	व्योम (*restore)(काष्ठा drm_crtc *crtc);
पूर्ण;

अटल अंतरभूत काष्ठा nouveau_crtc *nouveau_crtc(काष्ठा drm_crtc *crtc)
अणु
	वापस crtc ? container_of(crtc, काष्ठा nouveau_crtc, base) : शून्य;
पूर्ण

अटल अंतरभूत काष्ठा drm_crtc *to_drm_crtc(काष्ठा nouveau_crtc *crtc)
अणु
	वापस &crtc->base;
पूर्ण

पूर्णांक nv04_cursor_init(काष्ठा nouveau_crtc *);

#पूर्ण_अगर /* __NOUVEAU_CRTC_H__ */
