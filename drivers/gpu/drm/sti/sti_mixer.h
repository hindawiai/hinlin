<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) STMicroelectronics SA 2014
 * Authors: Benjamin Gaignard <benjamin.gaignard@st.com>
 *          Fabien Dessenne <fabien.dessenne@st.com>
 *          क्रम STMicroelectronics.
 */

#अगर_अघोषित _STI_MIXER_H_
#घोषणा _STI_MIXER_H_

#समावेश <drm/drm_crtc.h>

#समावेश <drm/drm_debugfs.h>
#समावेश <drm/drm_file.h>

#समावेश "sti_plane.h"

काष्ठा device;

#घोषणा to_sti_mixer(x) container_of(x, काष्ठा sti_mixer, drm_crtc)

क्रमागत sti_mixer_status अणु
	STI_MIXER_READY,
	STI_MIXER_DISABLING,
	STI_MIXER_DISABLED,
पूर्ण;

/**
 * STI Mixer subdevice काष्ठाure
 *
 * @dev: driver device
 * @regs: mixer रेजिस्टरs
 * @id: id of the mixer
 * @drm_crtc: crtc object link to the mixer
 * @status: to know the status of the mixer
 */
काष्ठा sti_mixer अणु
	काष्ठा device *dev;
	व्योम __iomem *regs;
	पूर्णांक id;
	काष्ठा drm_crtc drm_crtc;
	क्रमागत sti_mixer_status status;
पूर्ण;

स्थिर अक्षर *sti_mixer_to_str(काष्ठा sti_mixer *mixer);

काष्ठा sti_mixer *sti_mixer_create(काष्ठा device *dev,
				   काष्ठा drm_device *drm_dev,
				   पूर्णांक id,
				   व्योम __iomem *baseaddr);

पूर्णांक sti_mixer_set_plane_status(काष्ठा sti_mixer *mixer,
			       काष्ठा sti_plane *plane, bool status);
पूर्णांक sti_mixer_set_plane_depth(काष्ठा sti_mixer *mixer, काष्ठा sti_plane *plane);
पूर्णांक sti_mixer_active_video_area(काष्ठा sti_mixer *mixer,
				काष्ठा drm_display_mode *mode);

व्योम sti_mixer_set_background_status(काष्ठा sti_mixer *mixer, bool enable);

व्योम sti_mixer_debugfs_init(काष्ठा sti_mixer *mixer, काष्ठा drm_minor *minor);

/* depth in Cross-bar control = z order */
#घोषणा GAM_MIXER_NB_DEPTH_LEVEL 6

#घोषणा STI_MIXER_MAIN 0
#घोषणा STI_MIXER_AUX  1

#पूर्ण_अगर
