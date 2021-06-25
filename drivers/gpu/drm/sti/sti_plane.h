<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) STMicroelectronics SA 2014
 * Author: Benjamin Gaignard <benjamin.gaignard@st.com> क्रम STMicroelectronics.
 */

#अगर_अघोषित _STI_PLANE_H_
#घोषणा _STI_PLANE_H_

#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_plane_helper.h>

#घोषणा to_sti_plane(x) container_of(x, काष्ठा sti_plane, drm_plane)

#घोषणा STI_PLANE_TYPE_SHIFT 8
#घोषणा STI_PLANE_TYPE_MASK (~((1 << STI_PLANE_TYPE_SHIFT) - 1))

क्रमागत sti_plane_type अणु
	STI_GDP = 1 << STI_PLANE_TYPE_SHIFT,
	STI_VDP = 2 << STI_PLANE_TYPE_SHIFT,
	STI_CUR = 3 << STI_PLANE_TYPE_SHIFT,
	STI_BCK = 4 << STI_PLANE_TYPE_SHIFT
पूर्ण;

क्रमागत sti_plane_id_of_type अणु
	STI_ID_0 = 0,
	STI_ID_1 = 1,
	STI_ID_2 = 2,
	STI_ID_3 = 3
पूर्ण;

क्रमागत sti_plane_desc अणु
	STI_GDP_0       = STI_GDP | STI_ID_0,
	STI_GDP_1       = STI_GDP | STI_ID_1,
	STI_GDP_2       = STI_GDP | STI_ID_2,
	STI_GDP_3       = STI_GDP | STI_ID_3,
	STI_HQVDP_0     = STI_VDP | STI_ID_0,
	STI_CURSOR      = STI_CUR,
	STI_BACK        = STI_BCK
पूर्ण;

क्रमागत sti_plane_status अणु
	STI_PLANE_READY,
	STI_PLANE_UPDATED,
	STI_PLANE_DISABLING,
	STI_PLANE_FLUSHING,
	STI_PLANE_DISABLED,
पूर्ण;

#घोषणा FPS_LENGTH 128
काष्ठा sti_fps_info अणु
	bool output;
	अचिन्हित पूर्णांक curr_frame_counter;
	अचिन्हित पूर्णांक last_frame_counter;
	अचिन्हित पूर्णांक curr_field_counter;
	अचिन्हित पूर्णांक last_field_counter;
	kसमय_प्रकार	     last_बारtamp;
	अक्षर fps_str[FPS_LENGTH];
	अक्षर fips_str[FPS_LENGTH];
पूर्ण;

/**
 * STI plane काष्ठाure
 *
 * @plane:              drm plane it is bound to (अगर any)
 * @desc:               plane type & id
 * @status:             to know the status of the plane
 * @fps_info:           frame per second info
 */
काष्ठा sti_plane अणु
	काष्ठा drm_plane drm_plane;
	क्रमागत sti_plane_desc desc;
	क्रमागत sti_plane_status status;
	काष्ठा sti_fps_info fps_info;
पूर्ण;

स्थिर अक्षर *sti_plane_to_str(काष्ठा sti_plane *plane);
व्योम sti_plane_update_fps(काष्ठा sti_plane *plane,
			  bool new_frame,
			  bool new_field);

व्योम sti_plane_init_property(काष्ठा sti_plane *plane,
			     क्रमागत drm_plane_type type);
व्योम sti_plane_reset(काष्ठा drm_plane *plane);
#पूर्ण_अगर
