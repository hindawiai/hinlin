<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * vsp1_drm.h  --  R-Car VSP1 DRM/KMS Interface
 *
 * Copyright (C) 2015 Renesas Electronics Corporation
 *
 * Contact: Laurent Pinअक्षरt (laurent.pinअक्षरt@ideasonboard.com)
 */
#अगर_अघोषित __VSP1_DRM_H__
#घोषणा __VSP1_DRM_H__

#समावेश <linux/mutex.h>
#समावेश <linux/videodev2.h>
#समावेश <linux/रुको.h>

#समावेश <media/vsp1.h>

#समावेश "vsp1_pipe.h"

/**
 * काष्ठा vsp1_drm_pipeline - State क्रम the API exposed to the DRM driver
 * @pipe: the VSP1 pipeline used क्रम display
 * @width: output display width
 * @height: output display height
 * @क्रमce_brx_release: when set, release the BRx during the next reconfiguration
 * @रुको_queue: रुको queue to रुको क्रम BRx release completion
 * @uअगर: UIF entity अगर available क्रम the pipeline
 * @crc: CRC computation configuration
 * @du_complete: frame completion callback क्रम the DU driver (optional)
 * @du_निजी: data to be passed to the du_complete callback
 */
काष्ठा vsp1_drm_pipeline अणु
	काष्ठा vsp1_pipeline pipe;

	अचिन्हित पूर्णांक width;
	अचिन्हित पूर्णांक height;

	bool क्रमce_brx_release;
	रुको_queue_head_t रुको_queue;

	काष्ठा vsp1_entity *uअगर;
	काष्ठा vsp1_du_crc_config crc;

	/* Frame synchronisation */
	व्योम (*du_complete)(व्योम *data, अचिन्हित पूर्णांक status, u32 crc);
	व्योम *du_निजी;
पूर्ण;

/**
 * काष्ठा vsp1_drm - State क्रम the API exposed to the DRM driver
 * @pipe: the VSP1 DRM pipeline used क्रम display
 * @lock: protects the BRU and BRS allocation
 * @inमाला_दो: source crop rectangle, destination compose rectangle and z-order
 *	position क्रम every input (indexed by RPF index)
 */
काष्ठा vsp1_drm अणु
	काष्ठा vsp1_drm_pipeline pipe[VSP1_MAX_LIF];
	काष्ठा mutex lock;

	काष्ठा अणु
		काष्ठा v4l2_rect crop;
		काष्ठा v4l2_rect compose;
		अचिन्हित पूर्णांक zpos;
	पूर्ण inमाला_दो[VSP1_MAX_RPF];
पूर्ण;

अटल अंतरभूत काष्ठा vsp1_drm_pipeline *
to_vsp1_drm_pipeline(काष्ठा vsp1_pipeline *pipe)
अणु
	वापस container_of(pipe, काष्ठा vsp1_drm_pipeline, pipe);
पूर्ण

पूर्णांक vsp1_drm_init(काष्ठा vsp1_device *vsp1);
व्योम vsp1_drm_cleanup(काष्ठा vsp1_device *vsp1);

#पूर्ण_अगर /* __VSP1_DRM_H__ */
