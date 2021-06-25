<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) STMicroelectronics SA 2014
 * Author: Fabien Dessenne <fabien.dessenne@st.com> क्रम STMicroelectronics.
 */

#अगर_अघोषित _STI_VID_H_
#घोषणा _STI_VID_H_

/**
 * STI VID काष्ठाure
 *
 * @dev:   driver device
 * @regs:  vid रेजिस्टरs
 * @id:    id of the vid
 */
काष्ठा sti_vid अणु
	काष्ठा device *dev;
	व्योम __iomem *regs;
	पूर्णांक id;
पूर्ण;

व्योम sti_vid_commit(काष्ठा sti_vid *vid,
		    काष्ठा drm_plane_state *state);
व्योम sti_vid_disable(काष्ठा sti_vid *vid);
काष्ठा sti_vid *sti_vid_create(काष्ठा device *dev, काष्ठा drm_device *drm_dev,
			       पूर्णांक id, व्योम __iomem *baseaddr);

व्योम vid_debugfs_init(काष्ठा sti_vid *vid, काष्ठा drm_minor *minor);

#पूर्ण_अगर
