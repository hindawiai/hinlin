<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Cadence MHDP8546 DP bridge driver.
 *
 * Copyright (C) 2020 Cadence Design Systems, Inc.
 *
 * Author: Quentin Schulz <quentin.schulz@मुक्त-electrons.com>
 *         Swapnil Jakhade <sjakhade@cadence.com>
 */

#अगर_अघोषित CDNS_MHDP8546_CORE_H
#घोषणा CDNS_MHDP8546_CORE_H

#समावेश <linux/bits.h>
#समावेश <linux/mutex.h>
#समावेश <linux/spinlock.h>

#समावेश <drm/drm_bridge.h>
#समावेश <drm/drm_connector.h>
#समावेश <drm/drm_dp_helper.h>

काष्ठा clk;
काष्ठा device;
काष्ठा phy;

/* Register offsets */
#घोषणा CDNS_APB_CTRL				0x00000
#घोषणा CDNS_CPU_STALL				BIT(3)

#घोषणा CDNS_MAILBOX_FULL			0x00008
#घोषणा CDNS_MAILBOX_EMPTY			0x0000c
#घोषणा CDNS_MAILBOX_TX_DATA			0x00010
#घोषणा CDNS_MAILBOX_RX_DATA			0x00014
#घोषणा CDNS_KEEP_ALIVE				0x00018
#घोषणा CDNS_KEEP_ALIVE_MASK			GENMASK(7, 0)

#घोषणा CDNS_VER_L				0x0001C
#घोषणा CDNS_VER_H				0x00020
#घोषणा CDNS_LIB_L_ADDR				0x00024
#घोषणा CDNS_LIB_H_ADDR				0x00028

#घोषणा CDNS_MB_INT_MASK			0x00034
#घोषणा CDNS_MB_INT_STATUS			0x00038

#घोषणा CDNS_SW_CLK_L				0x0003c
#घोषणा CDNS_SW_CLK_H				0x00040

#घोषणा CDNS_SW_EVENT0				0x00044
#घोषणा CDNS_DPTX_HPD				BIT(0)

#घोषणा CDNS_SW_EVENT1				0x00048
#घोषणा CDNS_SW_EVENT2				0x0004c
#घोषणा CDNS_SW_EVENT3				0x00050

#घोषणा CDNS_APB_INT_MASK			0x0006C
#घोषणा CDNS_APB_INT_MASK_MAILBOX_INT		BIT(0)
#घोषणा CDNS_APB_INT_MASK_SW_EVENT_INT		BIT(1)

#घोषणा CDNS_APB_INT_STATUS			0x00070

#घोषणा CDNS_DPTX_CAR				0x00904
#घोषणा CDNS_VIF_CLK_EN				BIT(0)
#घोषणा CDNS_VIF_CLK_RSTN			BIT(1)

#घोषणा CDNS_SOURCE_VIDEO_IF(s)			(0x00b00 + ((s) * 0x20))
#घोषणा CDNS_BND_HSYNC2VSYNC(s)			(CDNS_SOURCE_VIDEO_IF(s) + \
						 0x00)
#घोषणा CDNS_IP_DTCT_WIN			GENMASK(11, 0)
#घोषणा CDNS_IP_DET_INTERLACE_FORMAT		BIT(12)
#घोषणा CDNS_IP_BYPASS_V_INTERFACE		BIT(13)

#घोषणा CDNS_HSYNC2VSYNC_POL_CTRL(s)		(CDNS_SOURCE_VIDEO_IF(s) + \
						 0x10)
#घोषणा CDNS_H2V_HSYNC_POL_ACTIVE_LOW		BIT(1)
#घोषणा CDNS_H2V_VSYNC_POL_ACTIVE_LOW		BIT(2)

#घोषणा CDNS_DPTX_PHY_CONFIG			0x02000
#घोषणा CDNS_PHY_TRAINING_EN			BIT(0)
#घोषणा CDNS_PHY_TRAINING_TYPE(x)		(((x) & GENMASK(3, 0)) << 1)
#घोषणा CDNS_PHY_SCRAMBLER_BYPASS		BIT(5)
#घोषणा CDNS_PHY_ENCODER_BYPASS			BIT(6)
#घोषणा CDNS_PHY_SKEW_BYPASS			BIT(7)
#घोषणा CDNS_PHY_TRAINING_AUTO			BIT(8)
#घोषणा CDNS_PHY_LANE0_SKEW(x)			(((x) & GENMASK(2, 0)) << 9)
#घोषणा CDNS_PHY_LANE1_SKEW(x)			(((x) & GENMASK(2, 0)) << 12)
#घोषणा CDNS_PHY_LANE2_SKEW(x)			(((x) & GENMASK(2, 0)) << 15)
#घोषणा CDNS_PHY_LANE3_SKEW(x)			(((x) & GENMASK(2, 0)) << 18)
#घोषणा CDNS_PHY_COMMON_CONFIG			(CDNS_PHY_LANE1_SKEW(1) | \
						CDNS_PHY_LANE2_SKEW(2) |  \
						CDNS_PHY_LANE3_SKEW(3))
#घोषणा CDNS_PHY_10BIT_EN			BIT(21)

#घोषणा CDNS_DP_FRAMER_GLOBAL_CONFIG		0x02200
#घोषणा CDNS_DP_NUM_LANES(x)			((x) - 1)
#घोषणा CDNS_DP_MST_EN				BIT(2)
#घोषणा CDNS_DP_FRAMER_EN			BIT(3)
#घोषणा CDNS_DP_RATE_GOVERNOR_EN		BIT(4)
#घोषणा CDNS_DP_NO_VIDEO_MODE			BIT(5)
#घोषणा CDNS_DP_DISABLE_PHY_RST			BIT(6)
#घोषणा CDNS_DP_WR_FAILING_EDGE_VSYNC		BIT(7)

#घोषणा CDNS_DP_FRAMER_TU			0x02208
#घोषणा CDNS_DP_FRAMER_TU_SIZE(x)		(((x) & GENMASK(6, 0)) << 8)
#घोषणा CDNS_DP_FRAMER_TU_VS(x)			((x) & GENMASK(5, 0))
#घोषणा CDNS_DP_FRAMER_TU_CNT_RST_EN		BIT(15)

#घोषणा CDNS_DP_MTPH_CONTROL			0x02264
#घोषणा CDNS_DP_MTPH_ECF_EN			BIT(0)
#घोषणा CDNS_DP_MTPH_ACT_EN			BIT(1)
#घोषणा CDNS_DP_MTPH_LVP_EN			BIT(2)

#घोषणा CDNS_DP_MTPH_STATUS			0x0226C
#घोषणा CDNS_DP_MTPH_ACT_STATUS			BIT(0)

#घोषणा CDNS_DP_LANE_EN				0x02300
#घोषणा CDNS_DP_LANE_EN_LANES(x)		GENMASK((x) - 1, 0)

#घोषणा CDNS_DP_ENHNCD				0x02304

#घोषणा CDNS_DPTX_STREAM(s)			(0x03000 + (s) * 0x80)
#घोषणा CDNS_DP_MSA_HORIZONTAL_0(s)		(CDNS_DPTX_STREAM(s) + 0x00)
#घोषणा CDNS_DP_MSAH0_H_TOTAL(x)		(x)
#घोषणा CDNS_DP_MSAH0_HSYNC_START(x)		((x) << 16)

#घोषणा CDNS_DP_MSA_HORIZONTAL_1(s)		(CDNS_DPTX_STREAM(s) + 0x04)
#घोषणा CDNS_DP_MSAH1_HSYNC_WIDTH(x)		(x)
#घोषणा CDNS_DP_MSAH1_HSYNC_POL_LOW		BIT(15)
#घोषणा CDNS_DP_MSAH1_HDISP_WIDTH(x)		((x) << 16)

#घोषणा CDNS_DP_MSA_VERTICAL_0(s)		(CDNS_DPTX_STREAM(s) + 0x08)
#घोषणा CDNS_DP_MSAV0_V_TOTAL(x)		(x)
#घोषणा CDNS_DP_MSAV0_VSYNC_START(x)		((x) << 16)

#घोषणा CDNS_DP_MSA_VERTICAL_1(s)		(CDNS_DPTX_STREAM(s) + 0x0c)
#घोषणा CDNS_DP_MSAV1_VSYNC_WIDTH(x)		(x)
#घोषणा CDNS_DP_MSAV1_VSYNC_POL_LOW		BIT(15)
#घोषणा CDNS_DP_MSAV1_VDISP_WIDTH(x)		((x) << 16)

#घोषणा CDNS_DP_MSA_MISC(s)			(CDNS_DPTX_STREAM(s) + 0x10)
#घोषणा CDNS_DP_STREAM_CONFIG(s)		(CDNS_DPTX_STREAM(s) + 0x14)
#घोषणा CDNS_DP_STREAM_CONFIG_2(s)		(CDNS_DPTX_STREAM(s) + 0x2c)
#घोषणा CDNS_DP_SC2_TU_VS_DIFF(x)		((x) << 8)

#घोषणा CDNS_DP_HORIZONTAL(s)			(CDNS_DPTX_STREAM(s) + 0x30)
#घोषणा CDNS_DP_H_HSYNC_WIDTH(x)		(x)
#घोषणा CDNS_DP_H_H_TOTAL(x)			((x) << 16)

#घोषणा CDNS_DP_VERTICAL_0(s)			(CDNS_DPTX_STREAM(s) + 0x34)
#घोषणा CDNS_DP_V0_VHEIGHT(x)			(x)
#घोषणा CDNS_DP_V0_VSTART(x)			((x) << 16)

#घोषणा CDNS_DP_VERTICAL_1(s)			(CDNS_DPTX_STREAM(s) + 0x38)
#घोषणा CDNS_DP_V1_VTOTAL(x)			(x)
#घोषणा CDNS_DP_V1_VTOTAL_EVEN			BIT(16)

#घोषणा CDNS_DP_MST_SLOT_ALLOCATE(s)		(CDNS_DPTX_STREAM(s) + 0x44)
#घोषणा CDNS_DP_S_ALLOC_START_SLOT(x)		(x)
#घोषणा CDNS_DP_S_ALLOC_END_SLOT(x)		((x) << 8)

#घोषणा CDNS_DP_RATE_GOVERNING(s)		(CDNS_DPTX_STREAM(s) + 0x48)
#घोषणा CDNS_DP_RG_TARG_AV_SLOTS_Y(x)		(x)
#घोषणा CDNS_DP_RG_TARG_AV_SLOTS_X(x)		((x) << 4)
#घोषणा CDNS_DP_RG_ENABLE			BIT(10)

#घोषणा CDNS_DP_FRAMER_PXL_REPR(s)		(CDNS_DPTX_STREAM(s) + 0x4c)
#घोषणा CDNS_DP_FRAMER_6_BPC			BIT(0)
#घोषणा CDNS_DP_FRAMER_8_BPC			BIT(1)
#घोषणा CDNS_DP_FRAMER_10_BPC			BIT(2)
#घोषणा CDNS_DP_FRAMER_12_BPC			BIT(3)
#घोषणा CDNS_DP_FRAMER_16_BPC			BIT(4)
#घोषणा CDNS_DP_FRAMER_PXL_FORMAT		0x8
#घोषणा CDNS_DP_FRAMER_RGB			BIT(0)
#घोषणा CDNS_DP_FRAMER_YCBCR444			BIT(1)
#घोषणा CDNS_DP_FRAMER_YCBCR422			BIT(2)
#घोषणा CDNS_DP_FRAMER_YCBCR420			BIT(3)
#घोषणा CDNS_DP_FRAMER_Y_ONLY			BIT(4)

#घोषणा CDNS_DP_FRAMER_SP(s)			(CDNS_DPTX_STREAM(s) + 0x50)
#घोषणा CDNS_DP_FRAMER_VSYNC_POL_LOW		BIT(0)
#घोषणा CDNS_DP_FRAMER_HSYNC_POL_LOW		BIT(1)
#घोषणा CDNS_DP_FRAMER_INTERLACE		BIT(2)

#घोषणा CDNS_DP_LINE_THRESH(s)			(CDNS_DPTX_STREAM(s) + 0x64)
#घोषणा CDNS_DP_ACTIVE_LINE_THRESH(x)		(x)

#घोषणा CDNS_DP_VB_ID(s)			(CDNS_DPTX_STREAM(s) + 0x68)
#घोषणा CDNS_DP_VB_ID_INTERLACED		BIT(2)
#घोषणा CDNS_DP_VB_ID_COMPRESSED		BIT(6)

#घोषणा CDNS_DP_FRONT_BACK_PORCH(s)		(CDNS_DPTX_STREAM(s) + 0x78)
#घोषणा CDNS_DP_BACK_PORCH(x)			(x)
#घोषणा CDNS_DP_FRONT_PORCH(x)			((x) << 16)

#घोषणा CDNS_DP_BYTE_COUNT(s)			(CDNS_DPTX_STREAM(s) + 0x7c)
#घोषणा CDNS_DP_BYTE_COUNT_BYTES_IN_CHUNK_SHIFT	16

/* mailbox */
#घोषणा MAILBOX_RETRY_US			1000
#घोषणा MAILBOX_TIMEOUT_US			2000000

#घोषणा MB_OPCODE_ID				0
#घोषणा MB_MODULE_ID				1
#घोषणा MB_SIZE_MSB_ID				2
#घोषणा MB_SIZE_LSB_ID				3
#घोषणा MB_DATA_ID				4

#घोषणा MB_MODULE_ID_DP_TX			0x01
#घोषणा MB_MODULE_ID_HDCP_TX			0x07
#घोषणा MB_MODULE_ID_HDCP_RX			0x08
#घोषणा MB_MODULE_ID_HDCP_GENERAL		0x09
#घोषणा MB_MODULE_ID_GENERAL			0x0a

/* firmware and opcodes */
#घोषणा FW_NAME					"cadence/mhdp8546.bin"
#घोषणा CDNS_MHDP_IMEM				0x10000

#घोषणा GENERAL_MAIN_CONTROL			0x01
#घोषणा GENERAL_TEST_ECHO			0x02
#घोषणा GENERAL_BUS_SETTINGS			0x03
#घोषणा GENERAL_TEST_ACCESS			0x04
#घोषणा GENERAL_REGISTER_READ			0x07

#घोषणा DPTX_SET_POWER_MNG			0x00
#घोषणा DPTX_GET_EDID				0x02
#घोषणा DPTX_READ_DPCD				0x03
#घोषणा DPTX_WRITE_DPCD				0x04
#घोषणा DPTX_ENABLE_EVENT			0x05
#घोषणा DPTX_WRITE_REGISTER			0x06
#घोषणा DPTX_READ_REGISTER			0x07
#घोषणा DPTX_WRITE_FIELD			0x08
#घोषणा DPTX_READ_EVENT				0x0a
#घोषणा DPTX_GET_LAST_AUX_STAUS			0x0e
#घोषणा DPTX_HPD_STATE				0x11
#घोषणा DPTX_ADJUST_LT				0x12

#घोषणा FW_STANDBY				0
#घोषणा FW_ACTIVE				1

/* HPD */
#घोषणा DPTX_READ_EVENT_HPD_TO_HIGH             BIT(0)
#घोषणा DPTX_READ_EVENT_HPD_TO_LOW              BIT(1)
#घोषणा DPTX_READ_EVENT_HPD_PULSE               BIT(2)
#घोषणा DPTX_READ_EVENT_HPD_STATE               BIT(3)

/* general */
#घोषणा CDNS_DP_TRAINING_PATTERN_4		0x7

#घोषणा CDNS_KEEP_ALIVE_TIMEOUT			2000

#घोषणा CDNS_VOLT_SWING(x)			((x) & GENMASK(1, 0))
#घोषणा CDNS_FORCE_VOLT_SWING			BIT(2)

#घोषणा CDNS_PRE_EMPHASIS(x)			((x) & GENMASK(1, 0))
#घोषणा CDNS_FORCE_PRE_EMPHASIS			BIT(2)

#घोषणा CDNS_SUPPORT_TPS(x)			BIT((x) - 1)

#घोषणा CDNS_FAST_LINK_TRAINING			BIT(0)

#घोषणा CDNS_LANE_MAPPING_TYPE_C_LANE_0(x)	((x) & GENMASK(1, 0))
#घोषणा CDNS_LANE_MAPPING_TYPE_C_LANE_1(x)	((x) & GENMASK(3, 2))
#घोषणा CDNS_LANE_MAPPING_TYPE_C_LANE_2(x)	((x) & GENMASK(5, 4))
#घोषणा CDNS_LANE_MAPPING_TYPE_C_LANE_3(x)	((x) & GENMASK(7, 6))
#घोषणा CDNS_LANE_MAPPING_NORMAL		0xe4
#घोषणा CDNS_LANE_MAPPING_FLIPPED		0x1b

#घोषणा CDNS_DP_MAX_NUM_LANES			4
#घोषणा CDNS_DP_TEST_VSC_SDP			BIT(6) /* 1.3+ */
#घोषणा CDNS_DP_TEST_COLOR_FORMAT_RAW_Y_ONLY	BIT(7)

#घोषणा CDNS_MHDP_MAX_STREAMS			4

#घोषणा DP_LINK_CAP_ENHANCED_FRAMING		BIT(0)

काष्ठा cdns_mhdp_link अणु
	अचिन्हित अक्षर revision;
	अचिन्हित पूर्णांक rate;
	अचिन्हित पूर्णांक num_lanes;
	अचिन्हित दीर्घ capabilities;
पूर्ण;

काष्ठा cdns_mhdp_host अणु
	अचिन्हित पूर्णांक link_rate;
	u8 lanes_cnt;
	u8 volt_swing;
	u8 pre_emphasis;
	u8 pattern_supp;
	u8 lane_mapping;
	bool fast_link;
	bool enhanced;
	bool scrambler;
	bool ssc;
पूर्ण;

काष्ठा cdns_mhdp_sink अणु
	अचिन्हित पूर्णांक link_rate;
	u8 lanes_cnt;
	u8 pattern_supp;
	bool fast_link;
	bool enhanced;
	bool ssc;
पूर्ण;

काष्ठा cdns_mhdp_display_fmt अणु
	u32 color_क्रमmat;
	u32 bpc;
	bool y_only;
पूर्ण;

/*
 * These क्रमागतs present MHDP hw initialization state
 * Legal state transitions are:
 * MHDP_HW_READY <-> MHDP_HW_STOPPED
 */
क्रमागत mhdp_hw_state अणु
	MHDP_HW_READY = 1,	/* HW पढ़ोy, FW active */
	MHDP_HW_STOPPED		/* Driver removal FW to be stopped */
पूर्ण;

काष्ठा cdns_mhdp_device;

काष्ठा mhdp_platक्रमm_ops अणु
	पूर्णांक (*init)(काष्ठा cdns_mhdp_device *mhdp);
	व्योम (*निकास)(काष्ठा cdns_mhdp_device *mhdp);
	व्योम (*enable)(काष्ठा cdns_mhdp_device *mhdp);
	व्योम (*disable)(काष्ठा cdns_mhdp_device *mhdp);
पूर्ण;

काष्ठा cdns_mhdp_bridge_state अणु
	काष्ठा drm_bridge_state base;
	काष्ठा drm_display_mode *current_mode;
पूर्ण;

काष्ठा cdns_mhdp_platक्रमm_info अणु
	स्थिर काष्ठा drm_bridge_timings *timings;
	स्थिर काष्ठा mhdp_platक्रमm_ops *ops;
पूर्ण;

#घोषणा to_cdns_mhdp_bridge_state(s) \
		container_of(s, काष्ठा cdns_mhdp_bridge_state, base)

काष्ठा cdns_mhdp_device अणु
	व्योम __iomem *regs;
	व्योम __iomem *j721e_regs;

	काष्ठा device *dev;
	काष्ठा clk *clk;
	काष्ठा phy *phy;

	स्थिर काष्ठा cdns_mhdp_platक्रमm_info *info;

	/* This is to protect mailbox communications with the firmware */
	काष्ठा mutex mbox_mutex;

	/*
	 * "link_mutex" protects the access to all the link parameters
	 * including the link training process. Link training will be
	 * invoked both from thपढ़ोed पूर्णांकerrupt handler and from atomic
	 * callbacks when link_up is not set. So this mutex protects
	 * flags such as link_up, bridge_enabled, link.num_lanes,
	 * link.rate etc.
	 */
	काष्ठा mutex link_mutex;

	काष्ठा drm_connector connector;
	काष्ठा drm_bridge bridge;

	काष्ठा cdns_mhdp_link link;
	काष्ठा drm_dp_aux aux;

	काष्ठा cdns_mhdp_host host;
	काष्ठा cdns_mhdp_sink sink;
	काष्ठा cdns_mhdp_display_fmt display_fmt;
	u8 stream_id;

	bool link_up;
	bool plugged;

	/*
	 * "start_lock" protects the access to bridge_attached and
	 * hw_state data members that control the delayed firmware
	 * loading and attaching the bridge. They are accessed from
	 * both the DRM core and cdns_mhdp_fw_cb(). In most हालs just
	 * protecting the data members is enough, but the irq mask
	 * setting needs to be रक्षित when enabling the FW.
	 */
	spinlock_t start_lock;
	bool bridge_attached;
	bool bridge_enabled;
	क्रमागत mhdp_hw_state hw_state;
	रुको_queue_head_t fw_load_wq;

	/* Work काष्ठा to schedule a uevent on link train failure */
	काष्ठा work_काष्ठा modeset_retry_work;
पूर्ण;

#घोषणा connector_to_mhdp(x) container_of(x, काष्ठा cdns_mhdp_device, connector)
#घोषणा bridge_to_mhdp(x) container_of(x, काष्ठा cdns_mhdp_device, bridge)

#पूर्ण_अगर
