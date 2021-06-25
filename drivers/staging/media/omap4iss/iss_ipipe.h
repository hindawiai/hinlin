<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * TI OMAP4 ISS V4L2 Driver - ISP IPIPE module
 *
 * Copyright (C) 2012 Texas Instruments, Inc.
 *
 * Author: Sergio Aguirre <sergio.a.aguirre@gmail.com>
 */

#अगर_अघोषित OMAP4_ISS_IPIPE_H
#घोषणा OMAP4_ISS_IPIPE_H

#समावेश "iss_video.h"

क्रमागत ipipe_input_entity अणु
	IPIPE_INPUT_NONE,
	IPIPE_INPUT_IPIPEIF,
पूर्ण;

#घोषणा IPIPE_OUTPUT_VP				BIT(0)

/* Sink and source IPIPE pads */
#घोषणा IPIPE_PAD_SINK				0
#घोषणा IPIPE_PAD_SOURCE_VP			1
#घोषणा IPIPE_PADS_NUM				2

/*
 * काष्ठा iss_ipipe_device - Structure क्रम the IPIPE module to store its own
 *			    inक्रमmation
 * @subdev: V4L2 subdevice
 * @pads: Sink and source media entity pads
 * @क्रमmats: Active video क्रमmats
 * @input: Active input
 * @output: Active outमाला_दो
 * @error: A hardware error occurred during capture
 * @state: Streaming state
 * @रुको: Wait queue used to stop the module
 * @stopping: Stopping state
 */
काष्ठा iss_ipipe_device अणु
	काष्ठा v4l2_subdev subdev;
	काष्ठा media_pad pads[IPIPE_PADS_NUM];
	काष्ठा v4l2_mbus_framefmt क्रमmats[IPIPE_PADS_NUM];

	क्रमागत ipipe_input_entity input;
	अचिन्हित पूर्णांक output;
	अचिन्हित पूर्णांक error;

	क्रमागत iss_pipeline_stream_state state;
	रुको_queue_head_t रुको;
	atomic_t stopping;
पूर्ण;

काष्ठा iss_device;

पूर्णांक omap4iss_ipipe_रेजिस्टर_entities(काष्ठा iss_ipipe_device *ipipe,
				     काष्ठा v4l2_device *vdev);
व्योम omap4iss_ipipe_unरेजिस्टर_entities(काष्ठा iss_ipipe_device *ipipe);

पूर्णांक omap4iss_ipipe_init(काष्ठा iss_device *iss);
व्योम omap4iss_ipipe_cleanup(काष्ठा iss_device *iss);

#पूर्ण_अगर	/* OMAP4_ISS_IPIPE_H */
