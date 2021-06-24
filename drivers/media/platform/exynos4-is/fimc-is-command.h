<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Samsung Exynos4x12 FIMC-IS (Imaging Subप्रणाली) driver
 *
 * FIMC-IS command set definitions
 *
 * Copyright (C) 2013 Samsung Electronics Co., Ltd.
 *
 * Authors: Younghwan Joo <yhwan.joo@samsung.com>
 *          Sylwester Nawrocki <s.nawrocki@samsung.com>
 */

#अगर_अघोषित FIMC_IS_CMD_H_
#घोषणा FIMC_IS_CMD_H_

#घोषणा FIMC_IS_COMMAND_VER	110 /* FIMC-IS command set version 1.10 */

/* Enumeration of commands between the FIMC-IS and the host processor. */

/* HOST to FIMC-IS */
#घोषणा HIC_PREVIEW_STILL	0x0001
#घोषणा HIC_PREVIEW_VIDEO	0x0002
#घोषणा HIC_CAPTURE_STILL	0x0003
#घोषणा HIC_CAPTURE_VIDEO	0x0004
#घोषणा HIC_STREAM_ON		0x0005
#घोषणा HIC_STREAM_OFF		0x0006
#घोषणा HIC_SET_PARAMETER	0x0007
#घोषणा HIC_GET_PARAMETER	0x0008
#घोषणा HIC_SET_TUNE		0x0009
#घोषणा HIC_GET_STATUS		0x000b
/* Sensor part */
#घोषणा HIC_OPEN_SENSOR		0x000c
#घोषणा HIC_CLOSE_SENSOR	0x000d
#घोषणा HIC_SIMMIAN_INIT	0x000e
#घोषणा HIC_SIMMIAN_WRITE	0x000f
#घोषणा HIC_SIMMIAN_READ	0x0010
#घोषणा HIC_POWER_DOWN		0x0011
#घोषणा HIC_GET_SET_खाता_ADDR	0x0012
#घोषणा HIC_LOAD_SET_खाता	0x0013
#घोषणा HIC_MSG_CONFIG		0x0014
#घोषणा HIC_MSG_TEST		0x0015
/* FIMC-IS to HOST */
#घोषणा IHC_GET_SENSOR_NUM	0x1000
#घोषणा IHC_SET_SHOT_MARK	0x1001
/* parameter1: frame number */
/* parameter2: confidence level (smile 0~100) */
/* parameter3: confidence level (blink 0~100) */
#घोषणा IHC_SET_FACE_MARK	0x1002
/* parameter1: coordinate count */
/* parameter2: coordinate buffer address */
#घोषणा IHC_FRAME_DONE		0x1003
/* parameter1: frame start number */
/* parameter2: frame count */
#घोषणा IHC_AA_DONE		0x1004
#घोषणा IHC_NOT_READY		0x1005

#घोषणा IH_REPLY_DONE		0x2000
#घोषणा IH_REPLY_NOT_DONE	0x2001

क्रमागत fimc_is_scenario अणु
	IS_SC_PREVIEW_STILL,
	IS_SC_PREVIEW_VIDEO,
	IS_SC_CAPTURE_STILL,
	IS_SC_CAPTURE_VIDEO,
	IS_SC_MAX
पूर्ण;

क्रमागत fimc_is_sub_scenario अणु
	IS_SC_SUB_DEFAULT,
	IS_SC_SUB_PS_VTCALL,
	IS_SC_SUB_CS_VTCALL,
	IS_SC_SUB_PV_VTCALL,
	IS_SC_SUB_CV_VTCALL,
पूर्ण;

काष्ठा is_common_regs अणु
	u32 hicmd;
	u32 hic_sensorid;
	u32 hic_param[4];
	u32 reserved1[4];

	u32 ihcmd;
	u32 ihc_sensorid;
	u32 ihc_param[4];
	u32 reserved2[4];

	u32 isp_sensor_id;
	u32 isp_param[2];
	u32 reserved3[1];

	u32 scc_sensor_id;
	u32 scc_param[2];
	u32 reserved4[1];

	u32 dnr_sensor_id;
	u32 dnr_param[2];
	u32 reserved5[1];

	u32 scp_sensor_id;
	u32 scp_param[2];
	u32 reserved6[29];
पूर्ण __packed;

काष्ठा is_mcuctl_reg अणु
	u32 mcuctl;
	u32 bboar;

	u32 पूर्णांकgr0;
	u32 पूर्णांकcr0;
	u32 पूर्णांकmr0;
	u32 पूर्णांकsr0;
	u32 पूर्णांकmsr0;

	u32 पूर्णांकgr1;
	u32 पूर्णांकcr1;
	u32 पूर्णांकmr1;
	u32 पूर्णांकsr1;
	u32 पूर्णांकmsr1;

	u32 पूर्णांकcr2;
	u32 पूर्णांकmr2;
	u32 पूर्णांकsr2;
	u32 पूर्णांकmsr2;

	u32 gpoctrl;
	u32 cpoenctlr;
	u32 gpictlr;

	u32 reserved[0xd];

	काष्ठा is_common_regs common;
पूर्ण __packed;

#पूर्ण_अगर /* FIMC_IS_CMD_H_ */
