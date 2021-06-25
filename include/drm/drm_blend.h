<शैली गुरु>
/*
 * Copyright (c) 2016 Intel Corporation
 *
 * Permission to use, copy, modअगरy, distribute, and sell this software and its
 * करोcumentation क्रम any purpose is hereby granted without fee, provided that
 * the above copyright notice appear in all copies and that both that copyright
 * notice and this permission notice appear in supporting करोcumentation, and
 * that the name of the copyright holders not be used in advertising or
 * खुलाity pertaining to distribution of the software without specअगरic,
 * written prior permission.  The copyright holders make no representations
 * about the suitability of this software क्रम any purpose.  It is provided "as
 * is" without express or implied warranty.
 *
 * THE COPYRIGHT HOLDERS DISCLAIM ALL WARRANTIES WITH REGARD TO THIS SOFTWARE,
 * INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO
 * EVENT SHALL THE COPYRIGHT HOLDERS BE LIABLE FOR ANY SPECIAL, INसूचीECT OR
 * CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE,
 * DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 * TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE
 * OF THIS SOFTWARE.
 */

#अगर_अघोषित __DRM_BLEND_H__
#घोषणा __DRM_BLEND_H__

#समावेश <linux/list.h>
#समावेश <linux/प्रकार.स>
#समावेश <drm/drm_mode.h>

#घोषणा DRM_MODE_BLEND_PREMULTI		0
#घोषणा DRM_MODE_BLEND_COVERAGE		1
#घोषणा DRM_MODE_BLEND_PIXEL_NONE	2

काष्ठा drm_device;
काष्ठा drm_atomic_state;
काष्ठा drm_plane;

अटल अंतरभूत bool drm_rotation_90_or_270(अचिन्हित पूर्णांक rotation)
अणु
	वापस rotation & (DRM_MODE_ROTATE_90 | DRM_MODE_ROTATE_270);
पूर्ण

#घोषणा DRM_BLEND_ALPHA_OPAQUE		0xffff

पूर्णांक drm_plane_create_alpha_property(काष्ठा drm_plane *plane);
पूर्णांक drm_plane_create_rotation_property(काष्ठा drm_plane *plane,
				       अचिन्हित पूर्णांक rotation,
				       अचिन्हित पूर्णांक supported_rotations);
अचिन्हित पूर्णांक drm_rotation_simplअगरy(अचिन्हित पूर्णांक rotation,
				   अचिन्हित पूर्णांक supported_rotations);

पूर्णांक drm_plane_create_zpos_property(काष्ठा drm_plane *plane,
				   अचिन्हित पूर्णांक zpos,
				   अचिन्हित पूर्णांक min, अचिन्हित पूर्णांक max);
पूर्णांक drm_plane_create_zpos_immutable_property(काष्ठा drm_plane *plane,
					     अचिन्हित पूर्णांक zpos);
पूर्णांक drm_atomic_normalize_zpos(काष्ठा drm_device *dev,
			      काष्ठा drm_atomic_state *state);
पूर्णांक drm_plane_create_blend_mode_property(काष्ठा drm_plane *plane,
					 अचिन्हित पूर्णांक supported_modes);
#पूर्ण_अगर
