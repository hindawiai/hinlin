<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * ispccp2.h
 *
 * TI OMAP3 ISP - CCP2 module
 *
 * Copyright (C) 2010 Nokia Corporation
 * Copyright (C) 2010 Texas Instruments, Inc.
 *
 * Contacts: Laurent Pinअक्षरt <laurent.pinअक्षरt@ideasonboard.com>
 *	     Sakari Ailus <sakari.ailus@iki.fi>
 */

#अगर_अघोषित OMAP3_ISP_CCP2_H
#घोषणा OMAP3_ISP_CCP2_H

#समावेश <linux/videodev2.h>

काष्ठा isp_device;
काष्ठा isp_csiphy;

/* Sink and source ccp2 pads */
#घोषणा CCP2_PAD_SINK			0
#घोषणा CCP2_PAD_SOURCE			1
#घोषणा CCP2_PADS_NUM			2

/* CCP2 input media entity */
क्रमागत ccp2_input_entity अणु
	CCP2_INPUT_NONE,
	CCP2_INPUT_SENSOR,
	CCP2_INPUT_MEMORY,
पूर्ण;

/* CCP2 output media entity */
क्रमागत ccp2_output_entity अणु
	CCP2_OUTPUT_NONE,
	CCP2_OUTPUT_CCDC,
	CCP2_OUTPUT_MEMORY,
पूर्ण;


/* Logical channel configuration */
काष्ठा isp_पूर्णांकerface_lcx_config अणु
	पूर्णांक crc;
	u32 data_start;
	u32 data_size;
	u32 क्रमmat;
पूर्ण;

/* Memory channel configuration */
काष्ठा isp_पूर्णांकerface_mem_config अणु
	u32 dst_port;
	u32 vsize_count;
	u32 hsize_count;
	u32 src_ofst;
	u32 dst_ofst;
पूर्ण;

/* CCP2 device */
काष्ठा isp_ccp2_device अणु
	काष्ठा v4l2_subdev subdev;
	काष्ठा v4l2_mbus_framefmt क्रमmats[CCP2_PADS_NUM];
	काष्ठा media_pad pads[CCP2_PADS_NUM];

	क्रमागत ccp2_input_entity input;
	क्रमागत ccp2_output_entity output;
	काष्ठा isp_पूर्णांकerface_lcx_config अगर_cfg;
	काष्ठा isp_पूर्णांकerface_mem_config mem_cfg;
	काष्ठा isp_video video_in;
	काष्ठा isp_csiphy *phy;
	काष्ठा regulator *vdds_csib;
	क्रमागत isp_pipeline_stream_state state;
	रुको_queue_head_t रुको;
	atomic_t stopping;
पूर्ण;

/* Function declarations */
पूर्णांक omap3isp_ccp2_init(काष्ठा isp_device *isp);
व्योम omap3isp_ccp2_cleanup(काष्ठा isp_device *isp);
पूर्णांक omap3isp_ccp2_रेजिस्टर_entities(काष्ठा isp_ccp2_device *ccp2,
			काष्ठा v4l2_device *vdev);
व्योम omap3isp_ccp2_unरेजिस्टर_entities(काष्ठा isp_ccp2_device *ccp2);
व्योम omap3isp_ccp2_isr(काष्ठा isp_ccp2_device *ccp2);

#पूर्ण_अगर	/* OMAP3_ISP_CCP2_H */
