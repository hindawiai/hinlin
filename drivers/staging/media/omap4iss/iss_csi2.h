<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * TI OMAP4 ISS V4L2 Driver - CSI2 module
 *
 * Copyright (C) 2012 Texas Instruments, Inc.
 *
 * Author: Sergio Aguirre <sergio.a.aguirre@gmail.com>
 */

#अगर_अघोषित OMAP4_ISS_CSI2_H
#घोषणा OMAP4_ISS_CSI2_H

#समावेश <linux/types.h>
#समावेश <linux/videodev2.h>

#समावेश "iss_video.h"

काष्ठा iss_csiphy;

/* This is not an exhaustive list */
क्रमागत iss_csi2_pix_क्रमmats अणु
	CSI2_PIX_FMT_OTHERS = 0,
	CSI2_PIX_FMT_YUV422_8BIT = 0x1e,
	CSI2_PIX_FMT_YUV422_8BIT_VP = 0x9e,
	CSI2_PIX_FMT_YUV422_8BIT_VP16 = 0xde,
	CSI2_PIX_FMT_RAW10_EXP16 = 0xab,
	CSI2_PIX_FMT_RAW10_EXP16_VP = 0x12f,
	CSI2_PIX_FMT_RAW8 = 0x2a,
	CSI2_PIX_FMT_RAW8_DPCM10_EXP16 = 0x2aa,
	CSI2_PIX_FMT_RAW8_DPCM10_VP = 0x32a,
	CSI2_PIX_FMT_RAW8_VP = 0x12a,
	CSI2_USERDEF_8BIT_DATA1_DPCM10_VP = 0x340,
	CSI2_USERDEF_8BIT_DATA1_DPCM10 = 0x2c0,
	CSI2_USERDEF_8BIT_DATA1 = 0x40,
पूर्ण;

क्रमागत iss_csi2_irqevents अणु
	OCP_ERR_IRQ = 0x4000,
	SHORT_PACKET_IRQ = 0x2000,
	ECC_CORRECTION_IRQ = 0x1000,
	ECC_NO_CORRECTION_IRQ = 0x800,
	COMPLEXIO2_ERR_IRQ = 0x400,
	COMPLEXIO1_ERR_IRQ = 0x200,
	FIFO_OVF_IRQ = 0x100,
	CONTEXT7 = 0x80,
	CONTEXT6 = 0x40,
	CONTEXT5 = 0x20,
	CONTEXT4 = 0x10,
	CONTEXT3 = 0x8,
	CONTEXT2 = 0x4,
	CONTEXT1 = 0x2,
	CONTEXT0 = 0x1,
पूर्ण;

क्रमागत iss_csi2_ctx_irqevents अणु
	CTX_ECC_CORRECTION = 0x100,
	CTX_LINE_NUMBER = 0x80,
	CTX_FRAME_NUMBER = 0x40,
	CTX_CS = 0x20,
	CTX_LE = 0x8,
	CTX_LS = 0x4,
	CTX_FE = 0x2,
	CTX_FS = 0x1,
पूर्ण;

क्रमागत iss_csi2_frame_mode अणु
	ISS_CSI2_FRAME_IMMEDIATE,
	ISS_CSI2_FRAME_AFTERFEC,
पूर्ण;

#घोषणा ISS_CSI2_MAX_CTX_NUM	7

काष्ठा iss_csi2_ctx_cfg अणु
	u8 ctxnum;		/* context number 0 - 7 */
	u8 dpcm_decompress;

	/* Fields in CSI2_CTx_CTRL2 - locked by CSI2_CTx_CTRL1.CTX_EN */
	u8 भव_id;
	u16 क्रमmat_id;		/* as in CSI2_CTx_CTRL2[9:0] */
	u8 dpcm_predictor;	/* 1: simple, 0: advanced */
	u16 frame;

	/* Fields in CSI2_CTx_CTRL1/3 - Shaकरोwed */
	u16 alpha;
	u16 data_offset;
	u32 ping_addr;
	u32 pong_addr;
	u8 eof_enabled;
	u8 eol_enabled;
	u8 checksum_enabled;
	u8 enabled;
पूर्ण;

काष्ठा iss_csi2_timing_cfg अणु
	u8 ionum;			/* IO1 or IO2 as in CSI2_TIMING */
	अचिन्हित क्रमce_rx_mode:1;
	अचिन्हित stop_state_16x:1;
	अचिन्हित stop_state_4x:1;
	u16 stop_state_counter;
पूर्ण;

काष्ठा iss_csi2_ctrl_cfg अणु
	bool vp_clk_enable;
	bool vp_only_enable;
	u8 vp_out_ctrl;
	क्रमागत iss_csi2_frame_mode frame_mode;
	bool ecc_enable;
	bool अगर_enable;
पूर्ण;

#घोषणा CSI2_PAD_SINK		0
#घोषणा CSI2_PAD_SOURCE		1
#घोषणा CSI2_PADS_NUM		2

#घोषणा CSI2_OUTPUT_IPIPEIF	BIT(0)
#घोषणा CSI2_OUTPUT_MEMORY	BIT(1)

काष्ठा iss_csi2_device अणु
	काष्ठा v4l2_subdev subdev;
	काष्ठा media_pad pads[CSI2_PADS_NUM];
	काष्ठा v4l2_mbus_framefmt क्रमmats[CSI2_PADS_NUM];

	काष्ठा iss_video video_out;
	काष्ठा iss_device *iss;

	u8 available;		/* Is the IP present on the silicon? */

	/* memory resources, as defined in क्रमागत iss_mem_resources */
	अचिन्हित पूर्णांक regs1;
	अचिन्हित पूर्णांक regs2;
	/* ISP subघड़ी, as defined in क्रमागत iss_isp_subclk_resource */
	अचिन्हित पूर्णांक subclk;

	u32 output; /* output to IPIPEIF, memory or both? */
	bool dpcm_decompress;
	अचिन्हित पूर्णांक frame_skip;

	काष्ठा iss_csiphy *phy;
	काष्ठा iss_csi2_ctx_cfg contexts[ISS_CSI2_MAX_CTX_NUM + 1];
	काष्ठा iss_csi2_timing_cfg timing[2];
	काष्ठा iss_csi2_ctrl_cfg ctrl;
	क्रमागत iss_pipeline_stream_state state;
	रुको_queue_head_t रुको;
	atomic_t stopping;
पूर्ण;

व्योम omap4iss_csi2_isr(काष्ठा iss_csi2_device *csi2);
पूर्णांक omap4iss_csi2_reset(काष्ठा iss_csi2_device *csi2);
पूर्णांक omap4iss_csi2_init(काष्ठा iss_device *iss);
पूर्णांक omap4iss_csi2_create_links(काष्ठा iss_device *iss);
व्योम omap4iss_csi2_cleanup(काष्ठा iss_device *iss);
व्योम omap4iss_csi2_unरेजिस्टर_entities(काष्ठा iss_csi2_device *csi2);
पूर्णांक omap4iss_csi2_रेजिस्टर_entities(काष्ठा iss_csi2_device *csi2,
				    काष्ठा v4l2_device *vdev);
#पूर्ण_अगर	/* OMAP4_ISS_CSI2_H */
