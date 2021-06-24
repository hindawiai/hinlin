<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * ispccdc.h
 *
 * TI OMAP3 ISP - CCDC module
 *
 * Copyright (C) 2009-2010 Nokia Corporation
 * Copyright (C) 2009 Texas Instruments, Inc.
 *
 * Contacts: Laurent Pinअक्षरt <laurent.pinअक्षरt@ideasonboard.com>
 *	     Sakari Ailus <sakari.ailus@iki.fi>
 */

#अगर_अघोषित OMAP3_ISP_CCDC_H
#घोषणा OMAP3_ISP_CCDC_H

#समावेश <linux/omap3isp.h>
#समावेश <linux/workqueue.h>

#समावेश "ispvideo.h"

क्रमागत ccdc_input_entity अणु
	CCDC_INPUT_NONE,
	CCDC_INPUT_PARALLEL,
	CCDC_INPUT_CSI2A,
	CCDC_INPUT_CCP2B,
	CCDC_INPUT_CSI2C
पूर्ण;

#घोषणा CCDC_OUTPUT_MEMORY	(1 << 0)
#घोषणा CCDC_OUTPUT_PREVIEW	(1 << 1)
#घोषणा CCDC_OUTPUT_RESIZER	(1 << 2)

#घोषणा	OMAP3ISP_CCDC_NEVENTS	16

काष्ठा ispccdc_fpc अणु
	व्योम *addr;
	dma_addr_t dma;
	अचिन्हित पूर्णांक fpnum;
पूर्ण;

क्रमागत ispccdc_lsc_state अणु
	LSC_STATE_STOPPED = 0,
	LSC_STATE_STOPPING = 1,
	LSC_STATE_RUNNING = 2,
	LSC_STATE_RECONFIG = 3,
पूर्ण;

काष्ठा ispccdc_lsc_config_req अणु
	काष्ठा list_head list;
	काष्ठा omap3isp_ccdc_lsc_config config;
	अचिन्हित अक्षर enable;

	काष्ठा अणु
		व्योम *addr;
		dma_addr_t dma;
		काष्ठा sg_table sgt;
	पूर्ण table;
पूर्ण;

/*
 * ispccdc_lsc - CCDC LSC parameters
 */
काष्ठा ispccdc_lsc अणु
	क्रमागत ispccdc_lsc_state state;
	काष्ठा work_काष्ठा table_work;

	/* LSC queue of configurations */
	spinlock_t req_lock;
	काष्ठा ispccdc_lsc_config_req *request;	/* requested configuration */
	काष्ठा ispccdc_lsc_config_req *active;	/* active configuration */
	काष्ठा list_head मुक्त_queue;	/* configurations क्रम मुक्तing */
पूर्ण;

#घोषणा CCDC_STOP_NOT_REQUESTED		0x00
#घोषणा CCDC_STOP_REQUEST		0x01
#घोषणा CCDC_STOP_EXECUTED		(0x02 | CCDC_STOP_REQUEST)
#घोषणा CCDC_STOP_CCDC_FINISHED		0x04
#घोषणा CCDC_STOP_LSC_FINISHED		0x08
#घोषणा CCDC_STOP_FINISHED		\
	(CCDC_STOP_EXECUTED | CCDC_STOP_CCDC_FINISHED | CCDC_STOP_LSC_FINISHED)

#घोषणा CCDC_EVENT_VD1			0x10
#घोषणा CCDC_EVENT_VD0			0x20
#घोषणा CCDC_EVENT_LSC_DONE		0x40

/* Sink and source CCDC pads */
#घोषणा CCDC_PAD_SINK			0
#घोषणा CCDC_PAD_SOURCE_OF		1
#घोषणा CCDC_PAD_SOURCE_VP		2
#घोषणा CCDC_PADS_NUM			3

#घोषणा CCDC_FIELD_TOP			1
#घोषणा CCDC_FIELD_BOTTOM		2
#घोषणा CCDC_FIELD_BOTH			3

/*
 * काष्ठा isp_ccdc_device - Structure क्रम the CCDC module to store its own
 *			    inक्रमmation
 * @subdev: V4L2 subdevice
 * @pads: Sink and source media entity pads
 * @क्रमmats: Active video क्रमmats
 * @crop: Active crop rectangle on the OF source pad
 * @input: Active input
 * @output: Active outमाला_दो
 * @video_out: Output video node
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
 * @bt656: Whether the input पूर्णांकerface uses BT.656 synchronization
 * @fields: The fields (CCDC_FIELD_*) stored in the current buffer
 * @underrun: A buffer underrun occurred and a new buffer has been queued
 * @state: Streaming state
 * @lock: Serializes shaकरोw_update with पूर्णांकerrupt handler
 * @रुको: Wait queue used to stop the module
 * @stopping: Stopping state
 * @running: Is the CCDC hardware running
 * @ioctl_lock: Serializes ioctl calls and LSC requests मुक्तing
 */
काष्ठा isp_ccdc_device अणु
	काष्ठा v4l2_subdev subdev;
	काष्ठा media_pad pads[CCDC_PADS_NUM];
	काष्ठा v4l2_mbus_framefmt क्रमmats[CCDC_PADS_NUM];
	काष्ठा v4l2_rect crop;

	क्रमागत ccdc_input_entity input;
	अचिन्हित पूर्णांक output;
	काष्ठा isp_video video_out;

	अचिन्हित पूर्णांक alaw:1,
		     lpf:1,
		     obclamp:1,
		     fpc_en:1;
	काष्ठा omap3isp_ccdc_blcomp blcomp;
	काष्ठा omap3isp_ccdc_bclamp clamp;
	काष्ठा ispccdc_fpc fpc;
	काष्ठा ispccdc_lsc lsc;
	अचिन्हित पूर्णांक update;
	अचिन्हित पूर्णांक shaकरोw_update;

	bool bt656;
	अचिन्हित पूर्णांक fields;

	अचिन्हित पूर्णांक underrun:1;
	क्रमागत isp_pipeline_stream_state state;
	spinlock_t lock;
	रुको_queue_head_t रुको;
	अचिन्हित पूर्णांक stopping;
	bool running;
	काष्ठा mutex ioctl_lock;
पूर्ण;

काष्ठा isp_device;

पूर्णांक omap3isp_ccdc_init(काष्ठा isp_device *isp);
व्योम omap3isp_ccdc_cleanup(काष्ठा isp_device *isp);
पूर्णांक omap3isp_ccdc_रेजिस्टर_entities(काष्ठा isp_ccdc_device *ccdc,
	काष्ठा v4l2_device *vdev);
व्योम omap3isp_ccdc_unरेजिस्टर_entities(काष्ठा isp_ccdc_device *ccdc);

पूर्णांक omap3isp_ccdc_busy(काष्ठा isp_ccdc_device *isp_ccdc);
पूर्णांक omap3isp_ccdc_isr(काष्ठा isp_ccdc_device *isp_ccdc, u32 events);
व्योम omap3isp_ccdc_restore_context(काष्ठा isp_device *isp);
व्योम omap3isp_ccdc_max_rate(काष्ठा isp_ccdc_device *ccdc,
	अचिन्हित पूर्णांक *max_rate);

#पूर्ण_अगर	/* OMAP3_ISP_CCDC_H */
