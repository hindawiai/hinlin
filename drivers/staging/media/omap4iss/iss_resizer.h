<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * TI OMAP4 ISS V4L2 Driver - ISP RESIZER module
 *
 * Copyright (C) 2012 Texas Instruments, Inc.
 *
 * Author: Sergio Aguirre <sergio.a.aguirre@gmail.com>
 */

#अगर_अघोषित OMAP4_ISS_RESIZER_H
#घोषणा OMAP4_ISS_RESIZER_H

#समावेश "iss_video.h"

क्रमागत resizer_input_entity अणु
	RESIZER_INPUT_NONE,
	RESIZER_INPUT_IPIPE,
	RESIZER_INPUT_IPIPEIF
पूर्ण;

#घोषणा RESIZER_OUTPUT_MEMORY			BIT(0)

/* Sink and source RESIZER pads */
#घोषणा RESIZER_PAD_SINK			0
#घोषणा RESIZER_PAD_SOURCE_MEM			1
#घोषणा RESIZER_PADS_NUM			2

/*
 * काष्ठा iss_resizer_device - Structure क्रम the RESIZER module to store its own
 *			    inक्रमmation
 * @subdev: V4L2 subdevice
 * @pads: Sink and source media entity pads
 * @क्रमmats: Active video क्रमmats
 * @input: Active input
 * @output: Active outमाला_दो
 * @video_out: Output video node
 * @error: A hardware error occurred during capture
 * @state: Streaming state
 * @रुको: Wait queue used to stop the module
 * @stopping: Stopping state
 */
काष्ठा iss_resizer_device अणु
	काष्ठा v4l2_subdev subdev;
	काष्ठा media_pad pads[RESIZER_PADS_NUM];
	काष्ठा v4l2_mbus_framefmt क्रमmats[RESIZER_PADS_NUM];

	क्रमागत resizer_input_entity input;
	अचिन्हित पूर्णांक output;
	काष्ठा iss_video video_out;
	अचिन्हित पूर्णांक error;

	क्रमागत iss_pipeline_stream_state state;
	रुको_queue_head_t रुको;
	atomic_t stopping;
पूर्ण;

काष्ठा iss_device;

पूर्णांक omap4iss_resizer_init(काष्ठा iss_device *iss);
पूर्णांक omap4iss_resizer_create_links(काष्ठा iss_device *iss);
व्योम omap4iss_resizer_cleanup(काष्ठा iss_device *iss);
पूर्णांक omap4iss_resizer_रेजिस्टर_entities(काष्ठा iss_resizer_device *resizer,
				       काष्ठा v4l2_device *vdev);
व्योम omap4iss_resizer_unरेजिस्टर_entities(काष्ठा iss_resizer_device *resizer);

पूर्णांक omap4iss_resizer_busy(काष्ठा iss_resizer_device *resizer);
व्योम omap4iss_resizer_isr(काष्ठा iss_resizer_device *resizer, u32 events);
व्योम omap4iss_resizer_restore_context(काष्ठा iss_device *iss);
व्योम omap4iss_resizer_max_rate(काष्ठा iss_resizer_device *resizer,
			       अचिन्हित पूर्णांक *max_rate);

#पूर्ण_अगर	/* OMAP4_ISS_RESIZER_H */
