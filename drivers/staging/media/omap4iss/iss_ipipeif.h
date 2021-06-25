<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * TI OMAP4 ISS V4L2 Driver - ISP IPIPEIF module
 *
 * Copyright (C) 2012 Texas Instruments, Inc.
 *
 * Author: Sergio Aguirre <sergio.a.aguirre@gmail.com>
 */

#अगर_अघोषित OMAP4_ISS_IPIPEIF_H
#घोषणा OMAP4_ISS_IPIPEIF_H

#समावेश "iss_video.h"

क्रमागत ipipeअगर_input_entity अणु
	IPIPEIF_INPUT_NONE,
	IPIPEIF_INPUT_CSI2A,
	IPIPEIF_INPUT_CSI2B
पूर्ण;

#घोषणा IPIPEIF_OUTPUT_MEMORY			BIT(0)
#घोषणा IPIPEIF_OUTPUT_VP			BIT(1)

/* Sink and source IPIPEIF pads */
#घोषणा IPIPEIF_PAD_SINK			0
#घोषणा IPIPEIF_PAD_SOURCE_ISIF_SF		1
#घोषणा IPIPEIF_PAD_SOURCE_VP			2
#घोषणा IPIPEIF_PADS_NUM			3

/*
 * काष्ठा iss_ipipeअगर_device - Structure क्रम the IPIPEIF module to store its own
 *			    inक्रमmation
 * @subdev: V4L2 subdevice
 * @pads: Sink and source media entity pads
 * @क्रमmats: Active video क्रमmats
 * @input: Active input
 * @output: Active outमाला_दो
 * @video_out: Output video node
 * @error: A hardware error occurred during capture
 * @alaw: A-law compression enabled (1) or disabled (0)
 * @lpf: Low pass filter enabled (1) or disabled (0)
 * @obclamp: Optical-black clamp enabled (1) or disabled (0)
 * @fpc_en: Faulty pixels correction enabled (1) or disabled (0)
 * @blcomp: Black level compensation configuration
 * @clamp: Optical-black or digital clamp configuration
 * @fpc: Faulty pixels correction configuration
 * @lsc: Lens shading compensation configuration
 * @update: Biपंचांगask of controls to update during the next पूर्णांकerrupt
 * @shaकरोw_update: Controls update in progress by userspace
 * @syncअगर: Interface synchronization configuration
 * @vpcfg: Video port configuration
 * @underrun: A buffer underrun occurred and a new buffer has been queued
 * @state: Streaming state
 * @lock: Serializes shaकरोw_update with पूर्णांकerrupt handler
 * @रुको: Wait queue used to stop the module
 * @stopping: Stopping state
 * @ioctl_lock: Serializes ioctl calls and LSC requests मुक्तing
 */
काष्ठा iss_ipipeअगर_device अणु
	काष्ठा v4l2_subdev subdev;
	काष्ठा media_pad pads[IPIPEIF_PADS_NUM];
	काष्ठा v4l2_mbus_framefmt क्रमmats[IPIPEIF_PADS_NUM];

	क्रमागत ipipeअगर_input_entity input;
	अचिन्हित पूर्णांक output;
	काष्ठा iss_video video_out;
	अचिन्हित पूर्णांक error;

	क्रमागत iss_pipeline_stream_state state;
	रुको_queue_head_t रुको;
	atomic_t stopping;
पूर्ण;

काष्ठा iss_device;

पूर्णांक omap4iss_ipipeअगर_init(काष्ठा iss_device *iss);
पूर्णांक omap4iss_ipipeअगर_create_links(काष्ठा iss_device *iss);
व्योम omap4iss_ipipeअगर_cleanup(काष्ठा iss_device *iss);
पूर्णांक omap4iss_ipipeअगर_रेजिस्टर_entities(काष्ठा iss_ipipeअगर_device *ipipeअगर,
				       काष्ठा v4l2_device *vdev);
व्योम omap4iss_ipipeअगर_unरेजिस्टर_entities(काष्ठा iss_ipipeअगर_device *ipipeअगर);

पूर्णांक omap4iss_ipipeअगर_busy(काष्ठा iss_ipipeअगर_device *ipipeअगर);
व्योम omap4iss_ipipeअगर_isr(काष्ठा iss_ipipeअगर_device *ipipeअगर, u32 events);
व्योम omap4iss_ipipeअगर_restore_context(काष्ठा iss_device *iss);
व्योम omap4iss_ipipeअगर_max_rate(काष्ठा iss_ipipeअगर_device *ipipeअगर,
			       अचिन्हित पूर्णांक *max_rate);

#पूर्ण_अगर	/* OMAP4_ISS_IPIPEIF_H */
