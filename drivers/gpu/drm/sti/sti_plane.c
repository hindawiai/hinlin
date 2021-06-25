<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) STMicroelectronics SA 2014
 * Authors: Benjamin Gaignard <benjamin.gaignard@st.com>
 *          Fabien Dessenne <fabien.dessenne@st.com>
 *          क्रम STMicroelectronics.
 */

#समावेश <linux/types.h>

#समावेश <drm/drm_fb_cma_helper.h>
#समावेश <drm/drm_fourcc.h>
#समावेश <drm/drm_gem_cma_helper.h>

#समावेश "sti_compositor.h"
#समावेश "sti_drv.h"
#समावेश "sti_plane.h"

स्थिर अक्षर *sti_plane_to_str(काष्ठा sti_plane *plane)
अणु
	चयन (plane->desc) अणु
	हाल STI_GDP_0:
		वापस "GDP0";
	हाल STI_GDP_1:
		वापस "GDP1";
	हाल STI_GDP_2:
		वापस "GDP2";
	हाल STI_GDP_3:
		वापस "GDP3";
	हाल STI_HQVDP_0:
		वापस "HQVDP0";
	हाल STI_CURSOR:
		वापस "CURSOR";
	शेष:
		वापस "<UNKNOWN PLANE>";
	पूर्ण
पूर्ण

#घोषणा STI_FPS_INTERVAL_MS     3000

व्योम sti_plane_update_fps(काष्ठा sti_plane *plane,
			  bool new_frame,
			  bool new_field)
अणु
	काष्ठा drm_plane_state *state = plane->drm_plane.state;
	kसमय_प्रकार now;
	काष्ठा sti_fps_info *fps;
	पूर्णांक fpks, fipks, ms_since_last, num_frames, num_fields;

	now = kसमय_get();

	/* Compute number of frame updates */
	fps = &plane->fps_info;

	अगर (new_field)
		fps->curr_field_counter++;

	/* करो not perक्रमm fps calcul अगर new_frame is false */
	अगर (!new_frame)
		वापस;

	fps->curr_frame_counter++;
	ms_since_last = kसमय_प्रकारo_ms(kसमय_sub(now, fps->last_बारtamp));
	num_frames = fps->curr_frame_counter - fps->last_frame_counter;

	अगर (num_frames <= 0  || ms_since_last < STI_FPS_INTERVAL_MS)
		वापस;

	fps->last_बारtamp = now;
	fps->last_frame_counter = fps->curr_frame_counter;

	अगर (state->fb) अणु
		fpks = (num_frames * 1000000) / ms_since_last;
		snम_लिखो(plane->fps_info.fps_str, FPS_LENGTH,
			 "%-8s %4dx%-4d %.4s @ %3d.%-3.3d fps (%s)",
			 plane->drm_plane.name,
			 state->fb->width,
			 state->fb->height,
			 (अक्षर *)&state->fb->क्रमmat->क्रमmat,
			 fpks / 1000, fpks % 1000,
			 sti_plane_to_str(plane));
	पूर्ण

	अगर (fps->curr_field_counter) अणु
		/* Compute number of field updates */
		num_fields = fps->curr_field_counter - fps->last_field_counter;
		fps->last_field_counter = fps->curr_field_counter;
		fipks = (num_fields * 1000000) / ms_since_last;
		snम_लिखो(plane->fps_info.fips_str,
			 FPS_LENGTH, " - %3d.%-3.3d field/sec",
			 fipks / 1000, fipks % 1000);
	पूर्ण अन्यथा अणु
		plane->fps_info.fips_str[0] = '\0';
	पूर्ण

	अगर (fps->output)
		DRM_INFO("%s%s\n",
			 plane->fps_info.fps_str,
			 plane->fps_info.fips_str);
पूर्ण

अटल पूर्णांक sti_plane_get_शेष_zpos(क्रमागत drm_plane_type type)
अणु
	चयन (type) अणु
	हाल DRM_PLANE_TYPE_PRIMARY:
		वापस 0;
	हाल DRM_PLANE_TYPE_OVERLAY:
		वापस 1;
	हाल DRM_PLANE_TYPE_CURSOR:
		वापस 7;
	पूर्ण
	वापस 0;
पूर्ण

व्योम sti_plane_reset(काष्ठा drm_plane *plane)
अणु
	drm_atomic_helper_plane_reset(plane);
	plane->state->zpos = sti_plane_get_शेष_zpos(plane->type);
पूर्ण

अटल व्योम sti_plane_attach_zorder_property(काष्ठा drm_plane *drm_plane,
					     क्रमागत drm_plane_type type)
अणु
	पूर्णांक zpos = sti_plane_get_शेष_zpos(type);

	चयन (type) अणु
	हाल DRM_PLANE_TYPE_PRIMARY:
	हाल DRM_PLANE_TYPE_OVERLAY:
		drm_plane_create_zpos_property(drm_plane, zpos, 0, 6);
		अवरोध;
	हाल DRM_PLANE_TYPE_CURSOR:
		drm_plane_create_zpos_immutable_property(drm_plane, zpos);
		अवरोध;
	पूर्ण
पूर्ण

व्योम sti_plane_init_property(काष्ठा sti_plane *plane,
			     क्रमागत drm_plane_type type)
अणु
	sti_plane_attach_zorder_property(&plane->drm_plane, type);

	DRM_DEBUG_DRIVER("drm plane:%d mapped to %s\n",
			 plane->drm_plane.base.id, sti_plane_to_str(plane));
पूर्ण
