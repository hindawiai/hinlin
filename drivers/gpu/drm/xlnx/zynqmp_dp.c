<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * ZynqMP DisplayPort Driver
 *
 * Copyright (C) 2017 - 2020 Xilinx, Inc.
 *
 * Authors:
 * - Hyun Woo Kwon <hyun.kwon@xilinx.com>
 * - Laurent Pinअक्षरt <laurent.pinअक्षरt@ideasonboard.com>
 */

#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_connector.h>
#समावेश <drm/drm_crtc.h>
#समावेश <drm/drm_device.h>
#समावेश <drm/drm_dp_helper.h>
#समावेश <drm/drm_edid.h>
#समावेश <drm/drm_encoder.h>
#समावेश <drm/drm_managed.h>
#समावेश <drm/drm_modes.h>
#समावेश <drm/drm_of.h>
#समावेश <drm/drm_probe_helper.h>
#समावेश <drm/drm_simple_kms_helper.h>

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/phy/phy.h>
#समावेश <linux/reset.h>

#समावेश "zynqmp_disp.h"
#समावेश "zynqmp_dp.h"
#समावेश "zynqmp_dpsub.h"

अटल uपूर्णांक zynqmp_dp_aux_समयout_ms = 50;
module_param_named(aux_समयout_ms, zynqmp_dp_aux_समयout_ms, uपूर्णांक, 0444);
MODULE_PARM_DESC(aux_समयout_ms, "DP aux timeout value in msec (default: 50)");

/*
 * Some sink requires a delay after घातer on request
 */
अटल uपूर्णांक zynqmp_dp_घातer_on_delay_ms = 4;
module_param_named(घातer_on_delay_ms, zynqmp_dp_घातer_on_delay_ms, uपूर्णांक, 0444);
MODULE_PARM_DESC(घातer_on_delay_ms, "DP power on delay in msec (default: 4)");

/* Link configuration रेजिस्टरs */
#घोषणा ZYNQMP_DP_LINK_BW_SET				0x0
#घोषणा ZYNQMP_DP_LANE_COUNT_SET			0x4
#घोषणा ZYNQMP_DP_ENHANCED_FRAME_EN			0x8
#घोषणा ZYNQMP_DP_TRAINING_PATTERN_SET			0xc
#घोषणा ZYNQMP_DP_SCRAMBLING_DISABLE			0x14
#घोषणा ZYNQMP_DP_DOWNSPREAD_CTL			0x18
#घोषणा ZYNQMP_DP_SOFTWARE_RESET			0x1c
#घोषणा ZYNQMP_DP_SOFTWARE_RESET_STREAM1		BIT(0)
#घोषणा ZYNQMP_DP_SOFTWARE_RESET_STREAM2		BIT(1)
#घोषणा ZYNQMP_DP_SOFTWARE_RESET_STREAM3		BIT(2)
#घोषणा ZYNQMP_DP_SOFTWARE_RESET_STREAM4		BIT(3)
#घोषणा ZYNQMP_DP_SOFTWARE_RESET_AUX			BIT(7)
#घोषणा ZYNQMP_DP_SOFTWARE_RESET_ALL			(ZYNQMP_DP_SOFTWARE_RESET_STREAM1 | \
							 ZYNQMP_DP_SOFTWARE_RESET_STREAM2 | \
							 ZYNQMP_DP_SOFTWARE_RESET_STREAM3 | \
							 ZYNQMP_DP_SOFTWARE_RESET_STREAM4 | \
							 ZYNQMP_DP_SOFTWARE_RESET_AUX)

/* Core enable रेजिस्टरs */
#घोषणा ZYNQMP_DP_TRANSMITTER_ENABLE			0x80
#घोषणा ZYNQMP_DP_MAIN_STREAM_ENABLE			0x84
#घोषणा ZYNQMP_DP_FORCE_SCRAMBLER_RESET			0xc0
#घोषणा ZYNQMP_DP_VERSION				0xf8
#घोषणा ZYNQMP_DP_VERSION_MAJOR_MASK			GENMASK(31, 24)
#घोषणा ZYNQMP_DP_VERSION_MAJOR_SHIFT			24
#घोषणा ZYNQMP_DP_VERSION_MINOR_MASK			GENMASK(23, 16)
#घोषणा ZYNQMP_DP_VERSION_MINOR_SHIFT			16
#घोषणा ZYNQMP_DP_VERSION_REVISION_MASK			GENMASK(15, 12)
#घोषणा ZYNQMP_DP_VERSION_REVISION_SHIFT		12
#घोषणा ZYNQMP_DP_VERSION_PATCH_MASK			GENMASK(11, 8)
#घोषणा ZYNQMP_DP_VERSION_PATCH_SHIFT			8
#घोषणा ZYNQMP_DP_VERSION_INTERNAL_MASK			GENMASK(7, 0)
#घोषणा ZYNQMP_DP_VERSION_INTERNAL_SHIFT		0

/* Core ID रेजिस्टरs */
#घोषणा ZYNQMP_DP_CORE_ID				0xfc
#घोषणा ZYNQMP_DP_CORE_ID_MAJOR_MASK			GENMASK(31, 24)
#घोषणा ZYNQMP_DP_CORE_ID_MAJOR_SHIFT			24
#घोषणा ZYNQMP_DP_CORE_ID_MINOR_MASK			GENMASK(23, 16)
#घोषणा ZYNQMP_DP_CORE_ID_MINOR_SHIFT			16
#घोषणा ZYNQMP_DP_CORE_ID_REVISION_MASK			GENMASK(15, 8)
#घोषणा ZYNQMP_DP_CORE_ID_REVISION_SHIFT		8
#घोषणा ZYNQMP_DP_CORE_ID_सूचीECTION			GENMASK(1)

/* AUX channel पूर्णांकerface रेजिस्टरs */
#घोषणा ZYNQMP_DP_AUX_COMMAND				0x100
#घोषणा ZYNQMP_DP_AUX_COMMAND_CMD_SHIFT			8
#घोषणा ZYNQMP_DP_AUX_COMMAND_ADDRESS_ONLY		BIT(12)
#घोषणा ZYNQMP_DP_AUX_COMMAND_BYTES_SHIFT		0
#घोषणा ZYNQMP_DP_AUX_WRITE_FIFO			0x104
#घोषणा ZYNQMP_DP_AUX_ADDRESS				0x108
#घोषणा ZYNQMP_DP_AUX_CLK_DIVIDER			0x10c
#घोषणा ZYNQMP_DP_AUX_CLK_DIVIDER_AUX_FILTER_SHIFT	8
#घोषणा ZYNQMP_DP_INTERRUPT_SIGNAL_STATE		0x130
#घोषणा ZYNQMP_DP_INTERRUPT_SIGNAL_STATE_HPD		BIT(0)
#घोषणा ZYNQMP_DP_INTERRUPT_SIGNAL_STATE_REQUEST	BIT(1)
#घोषणा ZYNQMP_DP_INTERRUPT_SIGNAL_STATE_REPLY		BIT(2)
#घोषणा ZYNQMP_DP_INTERRUPT_SIGNAL_STATE_REPLY_TIMEOUT	BIT(3)
#घोषणा ZYNQMP_DP_AUX_REPLY_DATA			0x134
#घोषणा ZYNQMP_DP_AUX_REPLY_CODE			0x138
#घोषणा ZYNQMP_DP_AUX_REPLY_CODE_AUX_ACK		(0)
#घोषणा ZYNQMP_DP_AUX_REPLY_CODE_AUX_NACK		BIT(0)
#घोषणा ZYNQMP_DP_AUX_REPLY_CODE_AUX_DEFER		BIT(1)
#घोषणा ZYNQMP_DP_AUX_REPLY_CODE_I2C_ACK		(0)
#घोषणा ZYNQMP_DP_AUX_REPLY_CODE_I2C_NACK		BIT(2)
#घोषणा ZYNQMP_DP_AUX_REPLY_CODE_I2C_DEFER		BIT(3)
#घोषणा ZYNQMP_DP_AUX_REPLY_COUNT			0x13c
#घोषणा ZYNQMP_DP_REPLY_DATA_COUNT			0x148
#घोषणा ZYNQMP_DP_REPLY_DATA_COUNT_MASK			0xff
#घोषणा ZYNQMP_DP_INT_STATUS				0x3a0
#घोषणा ZYNQMP_DP_INT_MASK				0x3a4
#घोषणा ZYNQMP_DP_INT_EN				0x3a8
#घोषणा ZYNQMP_DP_INT_DS				0x3ac
#घोषणा ZYNQMP_DP_INT_HPD_IRQ				BIT(0)
#घोषणा ZYNQMP_DP_INT_HPD_EVENT				BIT(1)
#घोषणा ZYNQMP_DP_INT_REPLY_RECEIVED			BIT(2)
#घोषणा ZYNQMP_DP_INT_REPLY_TIMEOUT			BIT(3)
#घोषणा ZYNQMP_DP_INT_HPD_PULSE_DET			BIT(4)
#घोषणा ZYNQMP_DP_INT_EXT_PKT_TXD			BIT(5)
#घोषणा ZYNQMP_DP_INT_LIV_ABUF_UNDRFLW			BIT(12)
#घोषणा ZYNQMP_DP_INT_VBLANK_START			BIT(13)
#घोषणा ZYNQMP_DP_INT_PIXEL1_MATCH			BIT(14)
#घोषणा ZYNQMP_DP_INT_PIXEL0_MATCH			BIT(15)
#घोषणा ZYNQMP_DP_INT_CHBUF_UNDERFLW_MASK		0x3f0000
#घोषणा ZYNQMP_DP_INT_CHBUF_OVERFLW_MASK		0xfc00000
#घोषणा ZYNQMP_DP_INT_CUST_TS_2				BIT(28)
#घोषणा ZYNQMP_DP_INT_CUST_TS				BIT(29)
#घोषणा ZYNQMP_DP_INT_EXT_VSYNC_TS			BIT(30)
#घोषणा ZYNQMP_DP_INT_VSYNC_TS				BIT(31)
#घोषणा ZYNQMP_DP_INT_ALL				(ZYNQMP_DP_INT_HPD_IRQ | \
							 ZYNQMP_DP_INT_HPD_EVENT | \
							 ZYNQMP_DP_INT_CHBUF_UNDERFLW_MASK | \
							 ZYNQMP_DP_INT_CHBUF_OVERFLW_MASK)

/* Main stream attribute रेजिस्टरs */
#घोषणा ZYNQMP_DP_MAIN_STREAM_HTOTAL			0x180
#घोषणा ZYNQMP_DP_MAIN_STREAM_VTOTAL			0x184
#घोषणा ZYNQMP_DP_MAIN_STREAM_POLARITY			0x188
#घोषणा ZYNQMP_DP_MAIN_STREAM_POLARITY_HSYNC_SHIFT	0
#घोषणा ZYNQMP_DP_MAIN_STREAM_POLARITY_VSYNC_SHIFT	1
#घोषणा ZYNQMP_DP_MAIN_STREAM_HSWIDTH			0x18c
#घोषणा ZYNQMP_DP_MAIN_STREAM_VSWIDTH			0x190
#घोषणा ZYNQMP_DP_MAIN_STREAM_HRES			0x194
#घोषणा ZYNQMP_DP_MAIN_STREAM_VRES			0x198
#घोषणा ZYNQMP_DP_MAIN_STREAM_HSTART			0x19c
#घोषणा ZYNQMP_DP_MAIN_STREAM_VSTART			0x1a0
#घोषणा ZYNQMP_DP_MAIN_STREAM_MISC0			0x1a4
#घोषणा ZYNQMP_DP_MAIN_STREAM_MISC0_SYNC_LOCK		BIT(0)
#घोषणा ZYNQMP_DP_MAIN_STREAM_MISC0_COMP_FORMAT_RGB	(0 << 1)
#घोषणा ZYNQMP_DP_MAIN_STREAM_MISC0_COMP_FORMAT_YCRCB_422	(5 << 1)
#घोषणा ZYNQMP_DP_MAIN_STREAM_MISC0_COMP_FORMAT_YCRCB_444	(6 << 1)
#घोषणा ZYNQMP_DP_MAIN_STREAM_MISC0_COMP_FORMAT_MASK	(7 << 1)
#घोषणा ZYNQMP_DP_MAIN_STREAM_MISC0_DYNAMIC_RANGE	BIT(3)
#घोषणा ZYNQMP_DP_MAIN_STREAM_MISC0_YCBCR_COLR		BIT(4)
#घोषणा ZYNQMP_DP_MAIN_STREAM_MISC0_BPC_6		(0 << 5)
#घोषणा ZYNQMP_DP_MAIN_STREAM_MISC0_BPC_8		(1 << 5)
#घोषणा ZYNQMP_DP_MAIN_STREAM_MISC0_BPC_10		(2 << 5)
#घोषणा ZYNQMP_DP_MAIN_STREAM_MISC0_BPC_12		(3 << 5)
#घोषणा ZYNQMP_DP_MAIN_STREAM_MISC0_BPC_16		(4 << 5)
#घोषणा ZYNQMP_DP_MAIN_STREAM_MISC0_BPC_MASK		(7 << 5)
#घोषणा ZYNQMP_DP_MAIN_STREAM_MISC1			0x1a8
#घोषणा ZYNQMP_DP_MAIN_STREAM_MISC1_Y_ONLY_EN		BIT(7)
#घोषणा ZYNQMP_DP_MAIN_STREAM_M_VID			0x1ac
#घोषणा ZYNQMP_DP_MSA_TRANSFER_UNIT_SIZE		0x1b0
#घोषणा ZYNQMP_DP_MSA_TRANSFER_UNIT_SIZE_TU_SIZE_DEF	64
#घोषणा ZYNQMP_DP_MAIN_STREAM_N_VID			0x1b4
#घोषणा ZYNQMP_DP_USER_PIX_WIDTH			0x1b8
#घोषणा ZYNQMP_DP_USER_DATA_COUNT_PER_LANE		0x1bc
#घोषणा ZYNQMP_DP_MIN_BYTES_PER_TU			0x1c4
#घोषणा ZYNQMP_DP_FRAC_BYTES_PER_TU			0x1c8
#घोषणा ZYNQMP_DP_INIT_WAIT				0x1cc

/* PHY configuration and status रेजिस्टरs */
#घोषणा ZYNQMP_DP_PHY_RESET				0x200
#घोषणा ZYNQMP_DP_PHY_RESET_PHY_RESET			BIT(0)
#घोषणा ZYNQMP_DP_PHY_RESET_GTTX_RESET			BIT(1)
#घोषणा ZYNQMP_DP_PHY_RESET_PHY_PMA_RESET		BIT(8)
#घोषणा ZYNQMP_DP_PHY_RESET_PHY_PCS_RESET		BIT(9)
#घोषणा ZYNQMP_DP_PHY_RESET_ALL_RESET			(ZYNQMP_DP_PHY_RESET_PHY_RESET | \
							 ZYNQMP_DP_PHY_RESET_GTTX_RESET | \
							 ZYNQMP_DP_PHY_RESET_PHY_PMA_RESET | \
							 ZYNQMP_DP_PHY_RESET_PHY_PCS_RESET)
#घोषणा ZYNQMP_DP_PHY_PREEMPHASIS_LANE_0		0x210
#घोषणा ZYNQMP_DP_PHY_PREEMPHASIS_LANE_1		0x214
#घोषणा ZYNQMP_DP_PHY_PREEMPHASIS_LANE_2		0x218
#घोषणा ZYNQMP_DP_PHY_PREEMPHASIS_LANE_3		0x21c
#घोषणा ZYNQMP_DP_PHY_VOLTAGE_DIFF_LANE_0		0x220
#घोषणा ZYNQMP_DP_PHY_VOLTAGE_DIFF_LANE_1		0x224
#घोषणा ZYNQMP_DP_PHY_VOLTAGE_DIFF_LANE_2		0x228
#घोषणा ZYNQMP_DP_PHY_VOLTAGE_DIFF_LANE_3		0x22c
#घोषणा ZYNQMP_DP_PHY_CLOCK_SELECT			0x234
#घोषणा ZYNQMP_DP_PHY_CLOCK_SELECT_1_62G		0x1
#घोषणा ZYNQMP_DP_PHY_CLOCK_SELECT_2_70G		0x3
#घोषणा ZYNQMP_DP_PHY_CLOCK_SELECT_5_40G		0x5
#घोषणा ZYNQMP_DP_TX_PHY_POWER_DOWN			0x238
#घोषणा ZYNQMP_DP_TX_PHY_POWER_DOWN_LANE_0		BIT(0)
#घोषणा ZYNQMP_DP_TX_PHY_POWER_DOWN_LANE_1		BIT(1)
#घोषणा ZYNQMP_DP_TX_PHY_POWER_DOWN_LANE_2		BIT(2)
#घोषणा ZYNQMP_DP_TX_PHY_POWER_DOWN_LANE_3		BIT(3)
#घोषणा ZYNQMP_DP_TX_PHY_POWER_DOWN_ALL			0xf
#घोषणा ZYNQMP_DP_PHY_PRECURSOR_LANE_0			0x23c
#घोषणा ZYNQMP_DP_PHY_PRECURSOR_LANE_1			0x240
#घोषणा ZYNQMP_DP_PHY_PRECURSOR_LANE_2			0x244
#घोषणा ZYNQMP_DP_PHY_PRECURSOR_LANE_3			0x248
#घोषणा ZYNQMP_DP_PHY_POSTCURSOR_LANE_0			0x24c
#घोषणा ZYNQMP_DP_PHY_POSTCURSOR_LANE_1			0x250
#घोषणा ZYNQMP_DP_PHY_POSTCURSOR_LANE_2			0x254
#घोषणा ZYNQMP_DP_PHY_POSTCURSOR_LANE_3			0x258
#घोषणा ZYNQMP_DP_SUB_TX_PHY_PRECURSOR_LANE_0		0x24c
#घोषणा ZYNQMP_DP_SUB_TX_PHY_PRECURSOR_LANE_1		0x250
#घोषणा ZYNQMP_DP_PHY_STATUS				0x280
#घोषणा ZYNQMP_DP_PHY_STATUS_PLL_LOCKED_SHIFT		4
#घोषणा ZYNQMP_DP_PHY_STATUS_FPGA_PLL_LOCKED		BIT(6)

/* Audio रेजिस्टरs */
#घोषणा ZYNQMP_DP_TX_AUDIO_CONTROL			0x300
#घोषणा ZYNQMP_DP_TX_AUDIO_CHANNELS			0x304
#घोषणा ZYNQMP_DP_TX_AUDIO_INFO_DATA			0x308
#घोषणा ZYNQMP_DP_TX_M_AUD				0x328
#घोषणा ZYNQMP_DP_TX_N_AUD				0x32c
#घोषणा ZYNQMP_DP_TX_AUDIO_EXT_DATA			0x330

#घोषणा ZYNQMP_DP_MAX_LANES				2
#घोषणा ZYNQMP_MAX_FREQ					3000000

#घोषणा DP_REDUCED_BIT_RATE				162000
#घोषणा DP_HIGH_BIT_RATE				270000
#घोषणा DP_HIGH_BIT_RATE2				540000
#घोषणा DP_MAX_TRAINING_TRIES				5
#घोषणा DP_V1_2						0x12

/**
 * काष्ठा zynqmp_dp_link_config - Common link config between source and sink
 * @max_rate: maximum link rate
 * @max_lanes: maximum number of lanes
 */
काष्ठा zynqmp_dp_link_config अणु
	पूर्णांक max_rate;
	u8 max_lanes;
पूर्ण;

/**
 * काष्ठा zynqmp_dp_mode - Configured mode of DisplayPort
 * @bw_code: code क्रम bandwidth(link rate)
 * @lane_cnt: number of lanes
 * @pघड़ी: pixel घड़ी frequency of current mode
 * @fmt: क्रमmat identअगरier string
 */
काष्ठा zynqmp_dp_mode अणु
	u8 bw_code;
	u8 lane_cnt;
	पूर्णांक pघड़ी;
	स्थिर अक्षर *fmt;
पूर्ण;

/**
 * काष्ठा zynqmp_dp_config - Configuration of DisplayPort from DTS
 * @misc0: misc0 configuration (per DP v1.2 spec)
 * @misc1: misc1 configuration (per DP v1.2 spec)
 * @bpp: bits per pixel
 */
काष्ठा zynqmp_dp_config अणु
	u8 misc0;
	u8 misc1;
	u8 bpp;
पूर्ण;

/**
 * काष्ठा zynqmp_dp - Xilinx DisplayPort core
 * @encoder: the drm encoder काष्ठाure
 * @connector: the drm connector काष्ठाure
 * @dev: device काष्ठाure
 * @dpsub: Display subप्रणाली
 * @drm: DRM core
 * @iomem: device I/O memory क्रम रेजिस्टर access
 * @reset: reset controller
 * @irq: irq
 * @config: IP core configuration from DTS
 * @aux: aux channel
 * @phy: PHY handles क्रम DP lanes
 * @num_lanes: number of enabled phy lanes
 * @hpd_work: hot plug detection worker
 * @status: connection status
 * @enabled: flag to indicate अगर the device is enabled
 * @dpcd: DP configuration data from currently connected sink device
 * @link_config: common link configuration between IP core and sink device
 * @mode: current mode between IP core and sink device
 * @train_set: set of training data
 */
काष्ठा zynqmp_dp अणु
	काष्ठा drm_encoder encoder;
	काष्ठा drm_connector connector;
	काष्ठा device *dev;
	काष्ठा zynqmp_dpsub *dpsub;
	काष्ठा drm_device *drm;
	व्योम __iomem *iomem;
	काष्ठा reset_control *reset;
	पूर्णांक irq;

	काष्ठा zynqmp_dp_config config;
	काष्ठा drm_dp_aux aux;
	काष्ठा phy *phy[ZYNQMP_DP_MAX_LANES];
	u8 num_lanes;
	काष्ठा delayed_work hpd_work;
	क्रमागत drm_connector_status status;
	bool enabled;

	u8 dpcd[DP_RECEIVER_CAP_SIZE];
	काष्ठा zynqmp_dp_link_config link_config;
	काष्ठा zynqmp_dp_mode mode;
	u8 train_set[ZYNQMP_DP_MAX_LANES];
पूर्ण;

अटल अंतरभूत काष्ठा zynqmp_dp *encoder_to_dp(काष्ठा drm_encoder *encoder)
अणु
	वापस container_of(encoder, काष्ठा zynqmp_dp, encoder);
पूर्ण

अटल अंतरभूत काष्ठा zynqmp_dp *connector_to_dp(काष्ठा drm_connector *connector)
अणु
	वापस container_of(connector, काष्ठा zynqmp_dp, connector);
पूर्ण

अटल व्योम zynqmp_dp_ग_लिखो(काष्ठा zynqmp_dp *dp, पूर्णांक offset, u32 val)
अणु
	ग_लिखोl(val, dp->iomem + offset);
पूर्ण

अटल u32 zynqmp_dp_पढ़ो(काष्ठा zynqmp_dp *dp, पूर्णांक offset)
अणु
	वापस पढ़ोl(dp->iomem + offset);
पूर्ण

अटल व्योम zynqmp_dp_clr(काष्ठा zynqmp_dp *dp, पूर्णांक offset, u32 clr)
अणु
	zynqmp_dp_ग_लिखो(dp, offset, zynqmp_dp_पढ़ो(dp, offset) & ~clr);
पूर्ण

अटल व्योम zynqmp_dp_set(काष्ठा zynqmp_dp *dp, पूर्णांक offset, u32 set)
अणु
	zynqmp_dp_ग_लिखो(dp, offset, zynqmp_dp_पढ़ो(dp, offset) | set);
पूर्ण

/* -----------------------------------------------------------------------------
 * PHY Handling
 */

#घोषणा RST_TIMEOUT_MS			1000

अटल पूर्णांक zynqmp_dp_reset(काष्ठा zynqmp_dp *dp, bool निश्चित)
अणु
	अचिन्हित दीर्घ समयout;

	अगर (निश्चित)
		reset_control_निश्चित(dp->reset);
	अन्यथा
		reset_control_deनिश्चित(dp->reset);

	/* Wait क्रम the (de)निश्चित to complete. */
	समयout = jअगरfies + msecs_to_jअगरfies(RST_TIMEOUT_MS);
	जबतक (!समय_after_eq(jअगरfies, समयout)) अणु
		bool status = !!reset_control_status(dp->reset);

		अगर (निश्चित == status)
			वापस 0;

		cpu_relax();
	पूर्ण

	dev_err(dp->dev, "reset %s timeout\n", निश्चित ? "assert" : "deassert");
	वापस -ETIMEDOUT;
पूर्ण

/**
 * zynqmp_dp_phy_init - Initialize the phy
 * @dp: DisplayPort IP core काष्ठाure
 *
 * Initialize the phy.
 *
 * Return: 0 अगर the phy instances are initialized correctly, or the error code
 * वापसed from the callee functions.
 */
अटल पूर्णांक zynqmp_dp_phy_init(काष्ठा zynqmp_dp *dp)
अणु
	पूर्णांक ret;
	पूर्णांक i;

	क्रम (i = 0; i < dp->num_lanes; i++) अणु
		ret = phy_init(dp->phy[i]);
		अगर (ret) अणु
			dev_err(dp->dev, "failed to init phy lane %d\n", i);
			वापस ret;
		पूर्ण
	पूर्ण

	ret = zynqmp_dp_reset(dp, false);
	अगर (ret < 0)
		वापस ret;

	zynqmp_dp_clr(dp, ZYNQMP_DP_PHY_RESET, ZYNQMP_DP_PHY_RESET_ALL_RESET);

	/*
	 * Power on lanes in reverse order as only lane 0 रुकोs क्रम the PLL to
	 * lock.
	 */
	क्रम (i = dp->num_lanes - 1; i >= 0; i--) अणु
		ret = phy_घातer_on(dp->phy[i]);
		अगर (ret) अणु
			dev_err(dp->dev, "failed to power on phy lane %d\n", i);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/**
 * zynqmp_dp_phy_निकास - Exit the phy
 * @dp: DisplayPort IP core काष्ठाure
 *
 * Exit the phy.
 */
अटल व्योम zynqmp_dp_phy_निकास(काष्ठा zynqmp_dp *dp)
अणु
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	क्रम (i = 0; i < dp->num_lanes; i++) अणु
		ret = phy_घातer_off(dp->phy[i]);
		अगर (ret)
			dev_err(dp->dev, "failed to power off phy(%d) %d\n", i,
				ret);
	पूर्ण

	zynqmp_dp_reset(dp, true);

	क्रम (i = 0; i < dp->num_lanes; i++) अणु
		ret = phy_निकास(dp->phy[i]);
		अगर (ret)
			dev_err(dp->dev, "failed to exit phy(%d) %d\n", i, ret);
	पूर्ण
पूर्ण

/**
 * zynqmp_dp_phy_probe - Probe the PHYs
 * @dp: DisplayPort IP core काष्ठाure
 *
 * Probe PHYs क्रम all lanes. Less PHYs may be available than the number of
 * lanes, which is not considered an error as दीर्घ as at least one PHY is
 * found. The caller can check dp->num_lanes to check how many PHYs were found.
 *
 * Return:
 * * 0				- Success
 * * -ENXIO			- No PHY found
 * * -EPROBE_DEFER		- Probe deferral requested
 * * Other negative value	- PHY retrieval failure
 */
अटल पूर्णांक zynqmp_dp_phy_probe(काष्ठा zynqmp_dp *dp)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ZYNQMP_DP_MAX_LANES; i++) अणु
		अक्षर phy_name[16];
		काष्ठा phy *phy;

		snम_लिखो(phy_name, माप(phy_name), "dp-phy%d", i);
		phy = devm_phy_get(dp->dev, phy_name);

		अगर (IS_ERR(phy)) अणु
			चयन (PTR_ERR(phy)) अणु
			हाल -ENODEV:
				अगर (dp->num_lanes)
					वापस 0;

				dev_err(dp->dev, "no PHY found\n");
				वापस -ENXIO;

			हाल -EPROBE_DEFER:
				वापस -EPROBE_DEFER;

			शेष:
				dev_err(dp->dev, "failed to get PHY lane %u\n",
					i);
				वापस PTR_ERR(phy);
			पूर्ण
		पूर्ण

		dp->phy[i] = phy;
		dp->num_lanes++;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * zynqmp_dp_phy_पढ़ोy - Check अगर PHY is पढ़ोy
 * @dp: DisplayPort IP core काष्ठाure
 *
 * Check अगर PHY is पढ़ोy. If PHY is not पढ़ोy, रुको 1ms to check क्रम 100 बार.
 * This amount of delay was suggested by IP designer.
 *
 * Return: 0 अगर PHY is पढ़ोy, or -ENODEV अगर PHY is not पढ़ोy.
 */
अटल पूर्णांक zynqmp_dp_phy_पढ़ोy(काष्ठा zynqmp_dp *dp)
अणु
	u32 i, reg, पढ़ोy;

	पढ़ोy = (1 << dp->num_lanes) - 1;

	/* Wait क्रम 100 * 1ms. This should be enough समय क्रम PHY to be पढ़ोy */
	क्रम (i = 0; ; i++) अणु
		reg = zynqmp_dp_पढ़ो(dp, ZYNQMP_DP_PHY_STATUS);
		अगर ((reg & पढ़ोy) == पढ़ोy)
			वापस 0;

		अगर (i == 100) अणु
			dev_err(dp->dev, "PHY isn't ready\n");
			वापस -ENODEV;
		पूर्ण

		usleep_range(1000, 1100);
	पूर्ण

	वापस 0;
पूर्ण

/* -----------------------------------------------------------------------------
 * DisplayPort Link Training
 */

/**
 * zynqmp_dp_max_rate - Calculate and वापस available max pixel घड़ी
 * @link_rate: link rate (Kilo-bytes / sec)
 * @lane_num: number of lanes
 * @bpp: bits per pixel
 *
 * Return: max pixel घड़ी (KHz) supported by current link config.
 */
अटल अंतरभूत पूर्णांक zynqmp_dp_max_rate(पूर्णांक link_rate, u8 lane_num, u8 bpp)
अणु
	वापस link_rate * lane_num * 8 / bpp;
पूर्ण

/**
 * zynqmp_dp_mode_configure - Configure the link values
 * @dp: DisplayPort IP core काष्ठाure
 * @pघड़ी: pixel घड़ी क्रम requested display mode
 * @current_bw: current link rate
 *
 * Find the link configuration values, rate and lane count क्रम requested pixel
 * घड़ी @pघड़ी. The @pघड़ी is stored in the mode to be used in other
 * functions later. The वापसed rate is करोwnshअगरted from the current rate
 * @current_bw.
 *
 * Return: Current link rate code, or -EINVAL.
 */
अटल पूर्णांक zynqmp_dp_mode_configure(काष्ठा zynqmp_dp *dp, पूर्णांक pघड़ी,
				    u8 current_bw)
अणु
	पूर्णांक max_rate = dp->link_config.max_rate;
	u8 bw_code;
	u8 max_lanes = dp->link_config.max_lanes;
	u8 max_link_rate_code = drm_dp_link_rate_to_bw_code(max_rate);
	u8 bpp = dp->config.bpp;
	u8 lane_cnt;

	/* Downshअगरt from current bandwidth */
	चयन (current_bw) अणु
	हाल DP_LINK_BW_5_4:
		bw_code = DP_LINK_BW_2_7;
		अवरोध;
	हाल DP_LINK_BW_2_7:
		bw_code = DP_LINK_BW_1_62;
		अवरोध;
	हाल DP_LINK_BW_1_62:
		dev_err(dp->dev, "can't downshift. already lowest link rate\n");
		वापस -EINVAL;
	शेष:
		/* If not given, start with max supported */
		bw_code = max_link_rate_code;
		अवरोध;
	पूर्ण

	क्रम (lane_cnt = 1; lane_cnt <= max_lanes; lane_cnt <<= 1) अणु
		पूर्णांक bw;
		u32 rate;

		bw = drm_dp_bw_code_to_link_rate(bw_code);
		rate = zynqmp_dp_max_rate(bw, lane_cnt, bpp);
		अगर (pघड़ी <= rate) अणु
			dp->mode.bw_code = bw_code;
			dp->mode.lane_cnt = lane_cnt;
			dp->mode.pघड़ी = pघड़ी;
			वापस dp->mode.bw_code;
		पूर्ण
	पूर्ण

	dev_err(dp->dev, "failed to configure link values\n");

	वापस -EINVAL;
पूर्ण

/**
 * zynqmp_dp_adjust_train - Adjust train values
 * @dp: DisplayPort IP core काष्ठाure
 * @link_status: link status from sink which contains requested training values
 */
अटल व्योम zynqmp_dp_adjust_train(काष्ठा zynqmp_dp *dp,
				   u8 link_status[DP_LINK_STATUS_SIZE])
अणु
	u8 *train_set = dp->train_set;
	u8 voltage = 0, preemphasis = 0;
	u8 i;

	क्रम (i = 0; i < dp->mode.lane_cnt; i++) अणु
		u8 v = drm_dp_get_adjust_request_voltage(link_status, i);
		u8 p = drm_dp_get_adjust_request_pre_emphasis(link_status, i);

		अगर (v > voltage)
			voltage = v;

		अगर (p > preemphasis)
			preemphasis = p;
	पूर्ण

	अगर (voltage >= DP_TRAIN_VOLTAGE_SWING_LEVEL_3)
		voltage |= DP_TRAIN_MAX_SWING_REACHED;

	अगर (preemphasis >= DP_TRAIN_PRE_EMPH_LEVEL_2)
		preemphasis |= DP_TRAIN_MAX_PRE_EMPHASIS_REACHED;

	क्रम (i = 0; i < dp->mode.lane_cnt; i++)
		train_set[i] = voltage | preemphasis;
पूर्ण

/**
 * zynqmp_dp_update_vs_emph - Update the training values
 * @dp: DisplayPort IP core काष्ठाure
 *
 * Update the training values based on the request from sink. The mapped values
 * are predefined, and values(vs, pe, pc) are from the device manual.
 *
 * Return: 0 अगर vs and emph are updated successfully, or the error code वापसed
 * by drm_dp_dpcd_ग_लिखो().
 */
अटल पूर्णांक zynqmp_dp_update_vs_emph(काष्ठा zynqmp_dp *dp)
अणु
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	ret = drm_dp_dpcd_ग_लिखो(&dp->aux, DP_TRAINING_LANE0_SET, dp->train_set,
				dp->mode.lane_cnt);
	अगर (ret < 0)
		वापस ret;

	क्रम (i = 0; i < dp->mode.lane_cnt; i++) अणु
		u32 reg = ZYNQMP_DP_SUB_TX_PHY_PRECURSOR_LANE_0 + i * 4;
		जोड़ phy_configure_opts opts = अणु 0 पूर्ण;
		u8 train = dp->train_set[i];

		opts.dp.voltage[0] = (train & DP_TRAIN_VOLTAGE_SWING_MASK)
				   >> DP_TRAIN_VOLTAGE_SWING_SHIFT;
		opts.dp.pre[0] = (train & DP_TRAIN_PRE_EMPHASIS_MASK)
			       >> DP_TRAIN_PRE_EMPHASIS_SHIFT;

		phy_configure(dp->phy[i], &opts);

		zynqmp_dp_ग_लिखो(dp, reg, 0x2);
	पूर्ण

	वापस 0;
पूर्ण

/**
 * zynqmp_dp_link_train_cr - Train घड़ी recovery
 * @dp: DisplayPort IP core काष्ठाure
 *
 * Return: 0 अगर घड़ी recovery train is करोne successfully, or corresponding
 * error code.
 */
अटल पूर्णांक zynqmp_dp_link_train_cr(काष्ठा zynqmp_dp *dp)
अणु
	u8 link_status[DP_LINK_STATUS_SIZE];
	u8 lane_cnt = dp->mode.lane_cnt;
	u8 vs = 0, tries = 0;
	u16 max_tries, i;
	bool cr_करोne;
	पूर्णांक ret;

	zynqmp_dp_ग_लिखो(dp, ZYNQMP_DP_TRAINING_PATTERN_SET,
			DP_TRAINING_PATTERN_1);
	ret = drm_dp_dpcd_ग_लिखोb(&dp->aux, DP_TRAINING_PATTERN_SET,
				 DP_TRAINING_PATTERN_1 |
				 DP_LINK_SCRAMBLING_DISABLE);
	अगर (ret < 0)
		वापस ret;

	/*
	 * 256 loops should be maximum iterations क्रम 4 lanes and 4 values.
	 * So, This loop should निकास beक्रमe 512 iterations
	 */
	क्रम (max_tries = 0; max_tries < 512; max_tries++) अणु
		ret = zynqmp_dp_update_vs_emph(dp);
		अगर (ret)
			वापस ret;

		drm_dp_link_train_घड़ी_recovery_delay(dp->dpcd);
		ret = drm_dp_dpcd_पढ़ो_link_status(&dp->aux, link_status);
		अगर (ret < 0)
			वापस ret;

		cr_करोne = drm_dp_घड़ी_recovery_ok(link_status, lane_cnt);
		अगर (cr_करोne)
			अवरोध;

		क्रम (i = 0; i < lane_cnt; i++)
			अगर (!(dp->train_set[i] & DP_TRAIN_MAX_SWING_REACHED))
				अवरोध;
		अगर (i == lane_cnt)
			अवरोध;

		अगर ((dp->train_set[0] & DP_TRAIN_VOLTAGE_SWING_MASK) == vs)
			tries++;
		अन्यथा
			tries = 0;

		अगर (tries == DP_MAX_TRAINING_TRIES)
			अवरोध;

		vs = dp->train_set[0] & DP_TRAIN_VOLTAGE_SWING_MASK;
		zynqmp_dp_adjust_train(dp, link_status);
	पूर्ण

	अगर (!cr_करोne)
		वापस -EIO;

	वापस 0;
पूर्ण

/**
 * zynqmp_dp_link_train_ce - Train channel equalization
 * @dp: DisplayPort IP core काष्ठाure
 *
 * Return: 0 अगर channel equalization train is करोne successfully, or
 * corresponding error code.
 */
अटल पूर्णांक zynqmp_dp_link_train_ce(काष्ठा zynqmp_dp *dp)
अणु
	u8 link_status[DP_LINK_STATUS_SIZE];
	u8 lane_cnt = dp->mode.lane_cnt;
	u32 pat, tries;
	पूर्णांक ret;
	bool ce_करोne;

	अगर (dp->dpcd[DP_DPCD_REV] >= DP_V1_2 &&
	    dp->dpcd[DP_MAX_LANE_COUNT] & DP_TPS3_SUPPORTED)
		pat = DP_TRAINING_PATTERN_3;
	अन्यथा
		pat = DP_TRAINING_PATTERN_2;

	zynqmp_dp_ग_लिखो(dp, ZYNQMP_DP_TRAINING_PATTERN_SET, pat);
	ret = drm_dp_dpcd_ग_लिखोb(&dp->aux, DP_TRAINING_PATTERN_SET,
				 pat | DP_LINK_SCRAMBLING_DISABLE);
	अगर (ret < 0)
		वापस ret;

	क्रम (tries = 0; tries < DP_MAX_TRAINING_TRIES; tries++) अणु
		ret = zynqmp_dp_update_vs_emph(dp);
		अगर (ret)
			वापस ret;

		drm_dp_link_train_channel_eq_delay(dp->dpcd);
		ret = drm_dp_dpcd_पढ़ो_link_status(&dp->aux, link_status);
		अगर (ret < 0)
			वापस ret;

		ce_करोne = drm_dp_channel_eq_ok(link_status, lane_cnt);
		अगर (ce_करोne)
			अवरोध;

		zynqmp_dp_adjust_train(dp, link_status);
	पूर्ण

	अगर (!ce_करोne)
		वापस -EIO;

	वापस 0;
पूर्ण

/**
 * zynqmp_dp_link_train - Train the link
 * @dp: DisplayPort IP core काष्ठाure
 *
 * Return: 0 अगर all trains are करोne successfully, or corresponding error code.
 */
अटल पूर्णांक zynqmp_dp_train(काष्ठा zynqmp_dp *dp)
अणु
	u32 reg;
	u8 bw_code = dp->mode.bw_code;
	u8 lane_cnt = dp->mode.lane_cnt;
	u8 aux_lane_cnt = lane_cnt;
	bool enhanced;
	पूर्णांक ret;

	zynqmp_dp_ग_लिखो(dp, ZYNQMP_DP_LANE_COUNT_SET, lane_cnt);
	enhanced = drm_dp_enhanced_frame_cap(dp->dpcd);
	अगर (enhanced) अणु
		zynqmp_dp_ग_लिखो(dp, ZYNQMP_DP_ENHANCED_FRAME_EN, 1);
		aux_lane_cnt |= DP_LANE_COUNT_ENHANCED_FRAME_EN;
	पूर्ण

	अगर (dp->dpcd[3] & 0x1) अणु
		zynqmp_dp_ग_लिखो(dp, ZYNQMP_DP_DOWNSPREAD_CTL, 1);
		drm_dp_dpcd_ग_लिखोb(&dp->aux, DP_DOWNSPREAD_CTRL,
				   DP_SPREAD_AMP_0_5);
	पूर्ण अन्यथा अणु
		zynqmp_dp_ग_लिखो(dp, ZYNQMP_DP_DOWNSPREAD_CTL, 0);
		drm_dp_dpcd_ग_लिखोb(&dp->aux, DP_DOWNSPREAD_CTRL, 0);
	पूर्ण

	ret = drm_dp_dpcd_ग_लिखोb(&dp->aux, DP_LANE_COUNT_SET, aux_lane_cnt);
	अगर (ret < 0) अणु
		dev_err(dp->dev, "failed to set lane count\n");
		वापस ret;
	पूर्ण

	ret = drm_dp_dpcd_ग_लिखोb(&dp->aux, DP_MAIN_LINK_CHANNEL_CODING_SET,
				 DP_SET_ANSI_8B10B);
	अगर (ret < 0) अणु
		dev_err(dp->dev, "failed to set ANSI 8B/10B encoding\n");
		वापस ret;
	पूर्ण

	ret = drm_dp_dpcd_ग_लिखोb(&dp->aux, DP_LINK_BW_SET, bw_code);
	अगर (ret < 0) अणु
		dev_err(dp->dev, "failed to set DP bandwidth\n");
		वापस ret;
	पूर्ण

	zynqmp_dp_ग_लिखो(dp, ZYNQMP_DP_LINK_BW_SET, bw_code);
	चयन (bw_code) अणु
	हाल DP_LINK_BW_1_62:
		reg = ZYNQMP_DP_PHY_CLOCK_SELECT_1_62G;
		अवरोध;
	हाल DP_LINK_BW_2_7:
		reg = ZYNQMP_DP_PHY_CLOCK_SELECT_2_70G;
		अवरोध;
	हाल DP_LINK_BW_5_4:
	शेष:
		reg = ZYNQMP_DP_PHY_CLOCK_SELECT_5_40G;
		अवरोध;
	पूर्ण

	zynqmp_dp_ग_लिखो(dp, ZYNQMP_DP_PHY_CLOCK_SELECT, reg);
	ret = zynqmp_dp_phy_पढ़ोy(dp);
	अगर (ret < 0)
		वापस ret;

	zynqmp_dp_ग_लिखो(dp, ZYNQMP_DP_SCRAMBLING_DISABLE, 1);
	स_रखो(dp->train_set, 0, माप(dp->train_set));
	ret = zynqmp_dp_link_train_cr(dp);
	अगर (ret)
		वापस ret;

	ret = zynqmp_dp_link_train_ce(dp);
	अगर (ret)
		वापस ret;

	ret = drm_dp_dpcd_ग_लिखोb(&dp->aux, DP_TRAINING_PATTERN_SET,
				 DP_TRAINING_PATTERN_DISABLE);
	अगर (ret < 0) अणु
		dev_err(dp->dev, "failed to disable training pattern\n");
		वापस ret;
	पूर्ण
	zynqmp_dp_ग_लिखो(dp, ZYNQMP_DP_TRAINING_PATTERN_SET,
			DP_TRAINING_PATTERN_DISABLE);

	zynqmp_dp_ग_लिखो(dp, ZYNQMP_DP_SCRAMBLING_DISABLE, 0);

	वापस 0;
पूर्ण

/**
 * zynqmp_dp_train_loop - Downshअगरt the link rate during training
 * @dp: DisplayPort IP core काष्ठाure
 *
 * Train the link by करोwnshअगरting the link rate अगर training is not successful.
 */
अटल व्योम zynqmp_dp_train_loop(काष्ठा zynqmp_dp *dp)
अणु
	काष्ठा zynqmp_dp_mode *mode = &dp->mode;
	u8 bw = mode->bw_code;
	पूर्णांक ret;

	करो अणु
		अगर (dp->status == connector_status_disconnected ||
		    !dp->enabled)
			वापस;

		ret = zynqmp_dp_train(dp);
		अगर (!ret)
			वापस;

		ret = zynqmp_dp_mode_configure(dp, mode->pघड़ी, bw);
		अगर (ret < 0)
			जाओ err_out;

		bw = ret;
	पूर्ण जबतक (bw >= DP_LINK_BW_1_62);

err_out:
	dev_err(dp->dev, "failed to train the DP link\n");
पूर्ण

/* -----------------------------------------------------------------------------
 * DisplayPort AUX
 */

#घोषणा AUX_READ_BIT	0x1

/**
 * zynqmp_dp_aux_cmd_submit - Submit aux command
 * @dp: DisplayPort IP core काष्ठाure
 * @cmd: aux command
 * @addr: aux address
 * @buf: buffer क्रम command data
 * @bytes: number of bytes क्रम @buf
 * @reply: reply code to be वापसed
 *
 * Submit an aux command. All aux related commands, native or i2c aux
 * पढ़ो/ग_लिखो, are submitted through this function. The function is mapped to
 * the transfer function of काष्ठा drm_dp_aux. This function involves in
 * multiple रेजिस्टर पढ़ोs/ग_लिखोs, thus synchronization is needed, and it is
 * करोne by drm_dp_helper using @hw_mutex. The calling thपढ़ो goes पूर्णांकo sleep
 * अगर there's no immediate reply to the command submission. The reply code is
 * वापसed at @reply अगर @reply != शून्य.
 *
 * Return: 0 अगर the command is submitted properly, or corresponding error code:
 * -EBUSY when there is any request alपढ़ोy being processed
 * -ETIMEDOUT when receiving reply is समयd out
 * -EIO when received bytes are less than requested
 */
अटल पूर्णांक zynqmp_dp_aux_cmd_submit(काष्ठा zynqmp_dp *dp, u32 cmd, u16 addr,
				    u8 *buf, u8 bytes, u8 *reply)
अणु
	bool is_पढ़ो = (cmd & AUX_READ_BIT) ? true : false;
	u32 reg, i;

	reg = zynqmp_dp_पढ़ो(dp, ZYNQMP_DP_INTERRUPT_SIGNAL_STATE);
	अगर (reg & ZYNQMP_DP_INTERRUPT_SIGNAL_STATE_REQUEST)
		वापस -EBUSY;

	zynqmp_dp_ग_लिखो(dp, ZYNQMP_DP_AUX_ADDRESS, addr);
	अगर (!is_पढ़ो)
		क्रम (i = 0; i < bytes; i++)
			zynqmp_dp_ग_लिखो(dp, ZYNQMP_DP_AUX_WRITE_FIFO,
					buf[i]);

	reg = cmd << ZYNQMP_DP_AUX_COMMAND_CMD_SHIFT;
	अगर (!buf || !bytes)
		reg |= ZYNQMP_DP_AUX_COMMAND_ADDRESS_ONLY;
	अन्यथा
		reg |= (bytes - 1) << ZYNQMP_DP_AUX_COMMAND_BYTES_SHIFT;
	zynqmp_dp_ग_लिखो(dp, ZYNQMP_DP_AUX_COMMAND, reg);

	/* Wait क्रम reply to be delivered upto 2ms */
	क्रम (i = 0; ; i++) अणु
		reg = zynqmp_dp_पढ़ो(dp, ZYNQMP_DP_INTERRUPT_SIGNAL_STATE);
		अगर (reg & ZYNQMP_DP_INTERRUPT_SIGNAL_STATE_REPLY)
			अवरोध;

		अगर (reg & ZYNQMP_DP_INTERRUPT_SIGNAL_STATE_REPLY_TIMEOUT ||
		    i == 2)
			वापस -ETIMEDOUT;

		usleep_range(1000, 1100);
	पूर्ण

	reg = zynqmp_dp_पढ़ो(dp, ZYNQMP_DP_AUX_REPLY_CODE);
	अगर (reply)
		*reply = reg;

	अगर (is_पढ़ो &&
	    (reg == ZYNQMP_DP_AUX_REPLY_CODE_AUX_ACK ||
	     reg == ZYNQMP_DP_AUX_REPLY_CODE_I2C_ACK)) अणु
		reg = zynqmp_dp_पढ़ो(dp, ZYNQMP_DP_REPLY_DATA_COUNT);
		अगर ((reg & ZYNQMP_DP_REPLY_DATA_COUNT_MASK) != bytes)
			वापस -EIO;

		क्रम (i = 0; i < bytes; i++)
			buf[i] = zynqmp_dp_पढ़ो(dp, ZYNQMP_DP_AUX_REPLY_DATA);
	पूर्ण

	वापस 0;
पूर्ण

अटल sमाप_प्रकार
zynqmp_dp_aux_transfer(काष्ठा drm_dp_aux *aux, काष्ठा drm_dp_aux_msg *msg)
अणु
	काष्ठा zynqmp_dp *dp = container_of(aux, काष्ठा zynqmp_dp, aux);
	पूर्णांक ret;
	अचिन्हित पूर्णांक i, iter;

	/* Number of loops = समयout in msec / aux delay (400 usec) */
	iter = zynqmp_dp_aux_समयout_ms * 1000 / 400;
	iter = iter ? iter : 1;

	क्रम (i = 0; i < iter; i++) अणु
		ret = zynqmp_dp_aux_cmd_submit(dp, msg->request, msg->address,
					       msg->buffer, msg->size,
					       &msg->reply);
		अगर (!ret) अणु
			dev_dbg(dp->dev, "aux %d retries\n", i);
			वापस msg->size;
		पूर्ण

		अगर (dp->status == connector_status_disconnected) अणु
			dev_dbg(dp->dev, "no connected aux device\n");
			वापस -ENODEV;
		पूर्ण

		usleep_range(400, 500);
	पूर्ण

	dev_dbg(dp->dev, "failed to do aux transfer (%d)\n", ret);

	वापस ret;
पूर्ण

/**
 * zynqmp_dp_aux_init - Initialize and रेजिस्टर the DP AUX
 * @dp: DisplayPort IP core काष्ठाure
 *
 * Program the AUX घड़ी भागider and filter and रेजिस्टर the DP AUX adapter.
 *
 * Return: 0 on success, error value otherwise
 */
अटल पूर्णांक zynqmp_dp_aux_init(काष्ठा zynqmp_dp *dp)
अणु
	अचिन्हित दीर्घ rate;
	अचिन्हित पूर्णांक w;

	/*
	 * The AUX_SIGNAL_WIDTH_FILTER is the number of APB घड़ी cycles
	 * corresponding to the AUX pulse. Allowable values are 8, 16, 24, 32,
	 * 40 and 48. The AUX pulse width must be between 0.4तगs and 0.6तगs,
	 * compute the w / 8 value corresponding to 0.4तगs rounded up, and make
	 * sure it stays below 0.6तगs and within the allowable values.
	 */
	rate = clk_get_rate(dp->dpsub->apb_clk);
	w = DIV_ROUND_UP(4 * rate, 1000 * 1000 * 10 * 8) * 8;
	अगर (w > 6 * rate / (1000 * 1000 * 10) || w > 48) अणु
		dev_err(dp->dev, "aclk frequency too high\n");
		वापस -EINVAL;
	पूर्ण

	zynqmp_dp_ग_लिखो(dp, ZYNQMP_DP_AUX_CLK_DIVIDER,
			(w << ZYNQMP_DP_AUX_CLK_DIVIDER_AUX_FILTER_SHIFT) |
			(rate / (1000 * 1000)));

	dp->aux.name = "ZynqMP DP AUX";
	dp->aux.dev = dp->dev;
	dp->aux.transfer = zynqmp_dp_aux_transfer;

	वापस drm_dp_aux_रेजिस्टर(&dp->aux);
पूर्ण

/**
 * zynqmp_dp_aux_cleanup - Cleanup the DP AUX
 * @dp: DisplayPort IP core काष्ठाure
 *
 * Unरेजिस्टर the DP AUX adapter.
 */
अटल व्योम zynqmp_dp_aux_cleanup(काष्ठा zynqmp_dp *dp)
अणु
	drm_dp_aux_unरेजिस्टर(&dp->aux);
पूर्ण

/* -----------------------------------------------------------------------------
 * DisplayPort Generic Support
 */

/**
 * zynqmp_dp_update_misc - Write the misc रेजिस्टरs
 * @dp: DisplayPort IP core काष्ठाure
 *
 * The misc रेजिस्टर values are stored in the काष्ठाure, and this
 * function applies the values पूर्णांकo the रेजिस्टरs.
 */
अटल व्योम zynqmp_dp_update_misc(काष्ठा zynqmp_dp *dp)
अणु
	zynqmp_dp_ग_लिखो(dp, ZYNQMP_DP_MAIN_STREAM_MISC0, dp->config.misc0);
	zynqmp_dp_ग_लिखो(dp, ZYNQMP_DP_MAIN_STREAM_MISC1, dp->config.misc1);
पूर्ण

/**
 * zynqmp_dp_set_क्रमmat - Set the input क्रमmat
 * @dp: DisplayPort IP core काष्ठाure
 * @क्रमmat: input क्रमmat
 * @bpc: bits per component
 *
 * Update misc रेजिस्टर values based on input @क्रमmat and @bpc.
 *
 * Return: 0 on success, or -EINVAL.
 */
अटल पूर्णांक zynqmp_dp_set_क्रमmat(काष्ठा zynqmp_dp *dp,
				क्रमागत zynqmp_dpsub_क्रमmat क्रमmat,
				अचिन्हित पूर्णांक bpc)
अणु
	अटल स्थिर काष्ठा drm_display_info *display;
	काष्ठा zynqmp_dp_config *config = &dp->config;
	अचिन्हित पूर्णांक num_colors;

	config->misc0 &= ~ZYNQMP_DP_MAIN_STREAM_MISC0_COMP_FORMAT_MASK;
	config->misc1 &= ~ZYNQMP_DP_MAIN_STREAM_MISC1_Y_ONLY_EN;

	चयन (क्रमmat) अणु
	हाल ZYNQMP_DPSUB_FORMAT_RGB:
		config->misc0 |= ZYNQMP_DP_MAIN_STREAM_MISC0_COMP_FORMAT_RGB;
		num_colors = 3;
		अवरोध;

	हाल ZYNQMP_DPSUB_FORMAT_YCRCB444:
		config->misc0 |= ZYNQMP_DP_MAIN_STREAM_MISC0_COMP_FORMAT_YCRCB_444;
		num_colors = 3;
		अवरोध;

	हाल ZYNQMP_DPSUB_FORMAT_YCRCB422:
		config->misc0 |= ZYNQMP_DP_MAIN_STREAM_MISC0_COMP_FORMAT_YCRCB_422;
		num_colors = 2;
		अवरोध;

	हाल ZYNQMP_DPSUB_FORMAT_YONLY:
		config->misc1 |= ZYNQMP_DP_MAIN_STREAM_MISC1_Y_ONLY_EN;
		num_colors = 1;
		अवरोध;

	शेष:
		dev_err(dp->dev, "Invalid colormetry in DT\n");
		वापस -EINVAL;
	पूर्ण

	display = &dp->connector.display_info;
	अगर (display->bpc && bpc > display->bpc) अणु
		dev_warn(dp->dev,
			 "downgrading requested %ubpc to display limit %ubpc\n",
			 bpc, display->bpc);
		bpc = display->bpc;
	पूर्ण

	config->misc0 &= ~ZYNQMP_DP_MAIN_STREAM_MISC0_BPC_MASK;

	चयन (bpc) अणु
	हाल 6:
		config->misc0 |= ZYNQMP_DP_MAIN_STREAM_MISC0_BPC_6;
		अवरोध;
	हाल 8:
		config->misc0 |= ZYNQMP_DP_MAIN_STREAM_MISC0_BPC_8;
		अवरोध;
	हाल 10:
		config->misc0 |= ZYNQMP_DP_MAIN_STREAM_MISC0_BPC_10;
		अवरोध;
	हाल 12:
		config->misc0 |= ZYNQMP_DP_MAIN_STREAM_MISC0_BPC_12;
		अवरोध;
	हाल 16:
		config->misc0 |= ZYNQMP_DP_MAIN_STREAM_MISC0_BPC_16;
		अवरोध;
	शेष:
		dev_warn(dp->dev, "Not supported bpc (%u). fall back to 8bpc\n",
			 bpc);
		config->misc0 |= ZYNQMP_DP_MAIN_STREAM_MISC0_BPC_8;
		bpc = 8;
		अवरोध;
	पूर्ण

	/* Update the current bpp based on the क्रमmat. */
	config->bpp = bpc * num_colors;

	वापस 0;
पूर्ण

/**
 * zynqmp_dp_encoder_mode_set_transfer_unit - Set the transfer unit values
 * @dp: DisplayPort IP core काष्ठाure
 * @mode: requested display mode
 *
 * Set the transfer unit, and calculate all transfer unit size related values.
 * Calculation is based on DP and IP core specअगरication.
 */
अटल व्योम
zynqmp_dp_encoder_mode_set_transfer_unit(काष्ठा zynqmp_dp *dp,
					 काष्ठा drm_display_mode *mode)
अणु
	u32 tu = ZYNQMP_DP_MSA_TRANSFER_UNIT_SIZE_TU_SIZE_DEF;
	u32 bw, vid_kbytes, avg_bytes_per_tu, init_रुको;

	/* Use the max transfer unit size (शेष) */
	zynqmp_dp_ग_लिखो(dp, ZYNQMP_DP_MSA_TRANSFER_UNIT_SIZE, tu);

	vid_kbytes = mode->घड़ी * (dp->config.bpp / 8);
	bw = drm_dp_bw_code_to_link_rate(dp->mode.bw_code);
	avg_bytes_per_tu = vid_kbytes * tu / (dp->mode.lane_cnt * bw / 1000);
	zynqmp_dp_ग_लिखो(dp, ZYNQMP_DP_MIN_BYTES_PER_TU,
			avg_bytes_per_tu / 1000);
	zynqmp_dp_ग_लिखो(dp, ZYNQMP_DP_FRAC_BYTES_PER_TU,
			avg_bytes_per_tu % 1000);

	/* Configure the initial रुको cycle based on transfer unit size */
	अगर (tu < (avg_bytes_per_tu / 1000))
		init_रुको = 0;
	अन्यथा अगर ((avg_bytes_per_tu / 1000) <= 4)
		init_रुको = tu;
	अन्यथा
		init_रुको = tu - avg_bytes_per_tu / 1000;

	zynqmp_dp_ग_लिखो(dp, ZYNQMP_DP_INIT_WAIT, init_रुको);
पूर्ण

/**
 * zynqmp_dp_encoder_mode_set_stream - Configure the मुख्य stream
 * @dp: DisplayPort IP core काष्ठाure
 * @mode: requested display mode
 *
 * Configure the मुख्य stream based on the requested mode @mode. Calculation is
 * based on IP core specअगरication.
 */
अटल व्योम zynqmp_dp_encoder_mode_set_stream(काष्ठा zynqmp_dp *dp,
					      स्थिर काष्ठा drm_display_mode *mode)
अणु
	u8 lane_cnt = dp->mode.lane_cnt;
	u32 reg, wpl;
	अचिन्हित पूर्णांक rate;

	zynqmp_dp_ग_लिखो(dp, ZYNQMP_DP_MAIN_STREAM_HTOTAL, mode->htotal);
	zynqmp_dp_ग_लिखो(dp, ZYNQMP_DP_MAIN_STREAM_VTOTAL, mode->vtotal);
	zynqmp_dp_ग_लिखो(dp, ZYNQMP_DP_MAIN_STREAM_POLARITY,
			(!!(mode->flags & DRM_MODE_FLAG_PVSYNC) <<
			 ZYNQMP_DP_MAIN_STREAM_POLARITY_VSYNC_SHIFT) |
			(!!(mode->flags & DRM_MODE_FLAG_PHSYNC) <<
			 ZYNQMP_DP_MAIN_STREAM_POLARITY_HSYNC_SHIFT));
	zynqmp_dp_ग_लिखो(dp, ZYNQMP_DP_MAIN_STREAM_HSWIDTH,
			mode->hsync_end - mode->hsync_start);
	zynqmp_dp_ग_लिखो(dp, ZYNQMP_DP_MAIN_STREAM_VSWIDTH,
			mode->vsync_end - mode->vsync_start);
	zynqmp_dp_ग_लिखो(dp, ZYNQMP_DP_MAIN_STREAM_HRES, mode->hdisplay);
	zynqmp_dp_ग_लिखो(dp, ZYNQMP_DP_MAIN_STREAM_VRES, mode->vdisplay);
	zynqmp_dp_ग_लिखो(dp, ZYNQMP_DP_MAIN_STREAM_HSTART,
			mode->htotal - mode->hsync_start);
	zynqmp_dp_ग_लिखो(dp, ZYNQMP_DP_MAIN_STREAM_VSTART,
			mode->vtotal - mode->vsync_start);

	/* In synchronous mode, set the भागiers */
	अगर (dp->config.misc0 & ZYNQMP_DP_MAIN_STREAM_MISC0_SYNC_LOCK) अणु
		reg = drm_dp_bw_code_to_link_rate(dp->mode.bw_code);
		zynqmp_dp_ग_लिखो(dp, ZYNQMP_DP_MAIN_STREAM_N_VID, reg);
		zynqmp_dp_ग_लिखो(dp, ZYNQMP_DP_MAIN_STREAM_M_VID, mode->घड़ी);
		rate = zynqmp_disp_get_audio_clk_rate(dp->dpsub->disp);
		अगर (rate) अणु
			dev_dbg(dp->dev, "Audio rate: %d\n", rate / 512);
			zynqmp_dp_ग_लिखो(dp, ZYNQMP_DP_TX_N_AUD, reg);
			zynqmp_dp_ग_लिखो(dp, ZYNQMP_DP_TX_M_AUD, rate / 1000);
		पूर्ण
	पूर्ण

	/* Only 2 channel audio is supported now */
	अगर (zynqmp_disp_audio_enabled(dp->dpsub->disp))
		zynqmp_dp_ग_लिखो(dp, ZYNQMP_DP_TX_AUDIO_CHANNELS, 1);

	zynqmp_dp_ग_लिखो(dp, ZYNQMP_DP_USER_PIX_WIDTH, 1);

	/* Translate to the native 16 bit datapath based on IP core spec */
	wpl = (mode->hdisplay * dp->config.bpp + 15) / 16;
	reg = wpl + wpl % lane_cnt - lane_cnt;
	zynqmp_dp_ग_लिखो(dp, ZYNQMP_DP_USER_DATA_COUNT_PER_LANE, reg);
पूर्ण

/* -----------------------------------------------------------------------------
 * DRM Connector
 */

अटल क्रमागत drm_connector_status
zynqmp_dp_connector_detect(काष्ठा drm_connector *connector, bool क्रमce)
अणु
	काष्ठा zynqmp_dp *dp = connector_to_dp(connector);
	काष्ठा zynqmp_dp_link_config *link_config = &dp->link_config;
	u32 state, i;
	पूर्णांक ret;

	/*
	 * This is from heuristic. It takes some delay (ex, 100 ~ 500 msec) to
	 * get the HPD संकेत with some monitors.
	 */
	क्रम (i = 0; i < 10; i++) अणु
		state = zynqmp_dp_पढ़ो(dp, ZYNQMP_DP_INTERRUPT_SIGNAL_STATE);
		अगर (state & ZYNQMP_DP_INTERRUPT_SIGNAL_STATE_HPD)
			अवरोध;
		msleep(100);
	पूर्ण

	अगर (state & ZYNQMP_DP_INTERRUPT_SIGNAL_STATE_HPD) अणु
		ret = drm_dp_dpcd_पढ़ो(&dp->aux, 0x0, dp->dpcd,
				       माप(dp->dpcd));
		अगर (ret < 0) अणु
			dev_dbg(dp->dev, "DPCD read failed");
			जाओ disconnected;
		पूर्ण

		link_config->max_rate = min_t(पूर्णांक,
					      drm_dp_max_link_rate(dp->dpcd),
					      DP_HIGH_BIT_RATE2);
		link_config->max_lanes = min_t(u8,
					       drm_dp_max_lane_count(dp->dpcd),
					       dp->num_lanes);

		dp->status = connector_status_connected;
		वापस connector_status_connected;
	पूर्ण

disconnected:
	dp->status = connector_status_disconnected;
	वापस connector_status_disconnected;
पूर्ण

अटल पूर्णांक zynqmp_dp_connector_get_modes(काष्ठा drm_connector *connector)
अणु
	काष्ठा zynqmp_dp *dp = connector_to_dp(connector);
	काष्ठा edid *edid;
	पूर्णांक ret;

	edid = drm_get_edid(connector, &dp->aux.ddc);
	अगर (!edid)
		वापस 0;

	drm_connector_update_edid_property(connector, edid);
	ret = drm_add_edid_modes(connector, edid);
	kमुक्त(edid);

	वापस ret;
पूर्ण

अटल काष्ठा drm_encoder *
zynqmp_dp_connector_best_encoder(काष्ठा drm_connector *connector)
अणु
	काष्ठा zynqmp_dp *dp = connector_to_dp(connector);

	वापस &dp->encoder;
पूर्ण

अटल पूर्णांक zynqmp_dp_connector_mode_valid(काष्ठा drm_connector *connector,
					  काष्ठा drm_display_mode *mode)
अणु
	काष्ठा zynqmp_dp *dp = connector_to_dp(connector);
	u8 max_lanes = dp->link_config.max_lanes;
	u8 bpp = dp->config.bpp;
	पूर्णांक max_rate = dp->link_config.max_rate;
	पूर्णांक rate;

	अगर (mode->घड़ी > ZYNQMP_MAX_FREQ) अणु
		dev_dbg(dp->dev, "filtered the mode, %s,for high pixel rate\n",
			mode->name);
		drm_mode_debug_prपूर्णांकmodeline(mode);
		वापस MODE_CLOCK_HIGH;
	पूर्ण

	/* Check with link rate and lane count */
	rate = zynqmp_dp_max_rate(max_rate, max_lanes, bpp);
	अगर (mode->घड़ी > rate) अणु
		dev_dbg(dp->dev, "filtered the mode, %s,for high pixel rate\n",
			mode->name);
		drm_mode_debug_prपूर्णांकmodeline(mode);
		वापस MODE_CLOCK_HIGH;
	पूर्ण

	वापस MODE_OK;
पूर्ण

अटल स्थिर काष्ठा drm_connector_funcs zynqmp_dp_connector_funcs = अणु
	.detect			= zynqmp_dp_connector_detect,
	.fill_modes		= drm_helper_probe_single_connector_modes,
	.destroy		= drm_connector_cleanup,
	.atomic_duplicate_state	= drm_atomic_helper_connector_duplicate_state,
	.atomic_destroy_state	= drm_atomic_helper_connector_destroy_state,
	.reset			= drm_atomic_helper_connector_reset,
पूर्ण;

अटल स्थिर काष्ठा drm_connector_helper_funcs
zynqmp_dp_connector_helper_funcs = अणु
	.get_modes	= zynqmp_dp_connector_get_modes,
	.best_encoder	= zynqmp_dp_connector_best_encoder,
	.mode_valid	= zynqmp_dp_connector_mode_valid,
पूर्ण;

/* -----------------------------------------------------------------------------
 * DRM Encoder
 */

अटल व्योम zynqmp_dp_encoder_enable(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा zynqmp_dp *dp = encoder_to_dp(encoder);
	अचिन्हित पूर्णांक i;
	पूर्णांक ret = 0;

	pm_runसमय_get_sync(dp->dev);
	dp->enabled = true;
	zynqmp_dp_update_misc(dp);
	अगर (zynqmp_disp_audio_enabled(dp->dpsub->disp))
		zynqmp_dp_ग_लिखो(dp, ZYNQMP_DP_TX_AUDIO_CONTROL, 1);
	zynqmp_dp_ग_लिखो(dp, ZYNQMP_DP_TX_PHY_POWER_DOWN, 0);
	अगर (dp->status == connector_status_connected) अणु
		क्रम (i = 0; i < 3; i++) अणु
			ret = drm_dp_dpcd_ग_लिखोb(&dp->aux, DP_SET_POWER,
						 DP_SET_POWER_D0);
			अगर (ret == 1)
				अवरोध;
			usleep_range(300, 500);
		पूर्ण
		/* Some monitors take समय to wake up properly */
		msleep(zynqmp_dp_घातer_on_delay_ms);
	पूर्ण
	अगर (ret != 1)
		dev_dbg(dp->dev, "DP aux failed\n");
	अन्यथा
		zynqmp_dp_train_loop(dp);
	zynqmp_dp_ग_लिखो(dp, ZYNQMP_DP_SOFTWARE_RESET,
			ZYNQMP_DP_SOFTWARE_RESET_ALL);
	zynqmp_dp_ग_लिखो(dp, ZYNQMP_DP_MAIN_STREAM_ENABLE, 1);
पूर्ण

अटल व्योम zynqmp_dp_encoder_disable(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा zynqmp_dp *dp = encoder_to_dp(encoder);

	dp->enabled = false;
	cancel_delayed_work(&dp->hpd_work);
	zynqmp_dp_ग_लिखो(dp, ZYNQMP_DP_MAIN_STREAM_ENABLE, 0);
	drm_dp_dpcd_ग_लिखोb(&dp->aux, DP_SET_POWER, DP_SET_POWER_D3);
	zynqmp_dp_ग_लिखो(dp, ZYNQMP_DP_TX_PHY_POWER_DOWN,
			ZYNQMP_DP_TX_PHY_POWER_DOWN_ALL);
	अगर (zynqmp_disp_audio_enabled(dp->dpsub->disp))
		zynqmp_dp_ग_लिखो(dp, ZYNQMP_DP_TX_AUDIO_CONTROL, 0);
	pm_runसमय_put_sync(dp->dev);
पूर्ण

अटल व्योम
zynqmp_dp_encoder_atomic_mode_set(काष्ठा drm_encoder *encoder,
				  काष्ठा drm_crtc_state *crtc_state,
				  काष्ठा drm_connector_state *connector_state)
अणु
	काष्ठा zynqmp_dp *dp = encoder_to_dp(encoder);
	काष्ठा drm_display_mode *mode = &crtc_state->mode;
	काष्ठा drm_display_mode *adjusted_mode = &crtc_state->adjusted_mode;
	u8 max_lanes = dp->link_config.max_lanes;
	u8 bpp = dp->config.bpp;
	पूर्णांक rate, max_rate = dp->link_config.max_rate;
	पूर्णांक ret;

	zynqmp_dp_set_क्रमmat(dp, ZYNQMP_DPSUB_FORMAT_RGB, 8);

	/* Check again as bpp or क्रमmat might have been chagned */
	rate = zynqmp_dp_max_rate(max_rate, max_lanes, bpp);
	अगर (mode->घड़ी > rate) अणु
		dev_err(dp->dev, "the mode, %s,has too high pixel rate\n",
			mode->name);
		drm_mode_debug_prपूर्णांकmodeline(mode);
	पूर्ण

	ret = zynqmp_dp_mode_configure(dp, adjusted_mode->घड़ी, 0);
	अगर (ret < 0)
		वापस;

	zynqmp_dp_encoder_mode_set_transfer_unit(dp, adjusted_mode);
	zynqmp_dp_encoder_mode_set_stream(dp, adjusted_mode);
पूर्ण

#घोषणा ZYNQMP_DP_MIN_H_BACKPORCH	20

अटल पूर्णांक
zynqmp_dp_encoder_atomic_check(काष्ठा drm_encoder *encoder,
			       काष्ठा drm_crtc_state *crtc_state,
			       काष्ठा drm_connector_state *conn_state)
अणु
	काष्ठा drm_display_mode *mode = &crtc_state->mode;
	काष्ठा drm_display_mode *adjusted_mode = &crtc_state->adjusted_mode;
	पूर्णांक dअगरf = mode->htotal - mode->hsync_end;

	/*
	 * ZynqMP DP requires horizontal backporch to be greater than 12.
	 * This limitation may not be compatible with the sink device.
	 */
	अगर (dअगरf < ZYNQMP_DP_MIN_H_BACKPORCH) अणु
		पूर्णांक vrefresh = (adjusted_mode->घड़ी * 1000) /
			       (adjusted_mode->vtotal * adjusted_mode->htotal);

		dev_dbg(encoder->dev->dev, "hbackporch adjusted: %d to %d",
			dअगरf, ZYNQMP_DP_MIN_H_BACKPORCH - dअगरf);
		dअगरf = ZYNQMP_DP_MIN_H_BACKPORCH - dअगरf;
		adjusted_mode->htotal += dअगरf;
		adjusted_mode->घड़ी = adjusted_mode->vtotal *
				       adjusted_mode->htotal * vrefresh / 1000;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा drm_encoder_helper_funcs zynqmp_dp_encoder_helper_funcs = अणु
	.enable			= zynqmp_dp_encoder_enable,
	.disable		= zynqmp_dp_encoder_disable,
	.atomic_mode_set	= zynqmp_dp_encoder_atomic_mode_set,
	.atomic_check		= zynqmp_dp_encoder_atomic_check,
पूर्ण;

/* -----------------------------------------------------------------------------
 * Interrupt Handling
 */

/**
 * zynqmp_dp_enable_vblank - Enable vblank
 * @dp: DisplayPort IP core काष्ठाure
 *
 * Enable vblank पूर्णांकerrupt
 */
व्योम zynqmp_dp_enable_vblank(काष्ठा zynqmp_dp *dp)
अणु
	zynqmp_dp_ग_लिखो(dp, ZYNQMP_DP_INT_EN, ZYNQMP_DP_INT_VBLANK_START);
पूर्ण

/**
 * zynqmp_dp_disable_vblank - Disable vblank
 * @dp: DisplayPort IP core काष्ठाure
 *
 * Disable vblank पूर्णांकerrupt
 */
व्योम zynqmp_dp_disable_vblank(काष्ठा zynqmp_dp *dp)
अणु
	zynqmp_dp_ग_लिखो(dp, ZYNQMP_DP_INT_DS, ZYNQMP_DP_INT_VBLANK_START);
पूर्ण

अटल व्योम zynqmp_dp_hpd_work_func(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा zynqmp_dp *dp;

	dp = container_of(work, काष्ठा zynqmp_dp, hpd_work.work);

	अगर (dp->drm)
		drm_helper_hpd_irq_event(dp->drm);
पूर्ण

अटल irqवापस_t zynqmp_dp_irq_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा zynqmp_dp *dp = (काष्ठा zynqmp_dp *)data;
	u32 status, mask;

	status = zynqmp_dp_पढ़ो(dp, ZYNQMP_DP_INT_STATUS);
	mask = zynqmp_dp_पढ़ो(dp, ZYNQMP_DP_INT_MASK);
	अगर (!(status & ~mask))
		वापस IRQ_NONE;

	/* dbg क्रम diagnostic, but not much that the driver can करो */
	अगर (status & ZYNQMP_DP_INT_CHBUF_UNDERFLW_MASK)
		dev_dbg_ratelimited(dp->dev, "underflow interrupt\n");
	अगर (status & ZYNQMP_DP_INT_CHBUF_OVERFLW_MASK)
		dev_dbg_ratelimited(dp->dev, "overflow interrupt\n");

	zynqmp_dp_ग_लिखो(dp, ZYNQMP_DP_INT_STATUS, status);

	अगर (status & ZYNQMP_DP_INT_VBLANK_START)
		zynqmp_disp_handle_vblank(dp->dpsub->disp);

	अगर (status & ZYNQMP_DP_INT_HPD_EVENT)
		schedule_delayed_work(&dp->hpd_work, 0);

	अगर (status & ZYNQMP_DP_INT_HPD_IRQ) अणु
		पूर्णांक ret;
		u8 status[DP_LINK_STATUS_SIZE + 2];

		ret = drm_dp_dpcd_पढ़ो(&dp->aux, DP_SINK_COUNT, status,
				       DP_LINK_STATUS_SIZE + 2);
		अगर (ret < 0)
			जाओ handled;

		अगर (status[4] & DP_LINK_STATUS_UPDATED ||
		    !drm_dp_घड़ी_recovery_ok(&status[2], dp->mode.lane_cnt) ||
		    !drm_dp_channel_eq_ok(&status[2], dp->mode.lane_cnt)) अणु
			zynqmp_dp_train_loop(dp);
		पूर्ण
	पूर्ण

handled:
	वापस IRQ_HANDLED;
पूर्ण

/* -----------------------------------------------------------------------------
 * Initialization & Cleanup
 */

पूर्णांक zynqmp_dp_drm_init(काष्ठा zynqmp_dpsub *dpsub)
अणु
	काष्ठा zynqmp_dp *dp = dpsub->dp;
	काष्ठा drm_encoder *encoder = &dp->encoder;
	काष्ठा drm_connector *connector = &dp->connector;
	पूर्णांक ret;

	dp->config.misc0 &= ~ZYNQMP_DP_MAIN_STREAM_MISC0_SYNC_LOCK;
	zynqmp_dp_set_क्रमmat(dp, ZYNQMP_DPSUB_FORMAT_RGB, 8);

	/* Create the DRM encoder and connector. */
	encoder->possible_crtcs |= zynqmp_disp_get_crtc_mask(dpsub->disp);
	drm_simple_encoder_init(dp->drm, encoder, DRM_MODE_ENCODER_TMDS);
	drm_encoder_helper_add(encoder, &zynqmp_dp_encoder_helper_funcs);

	connector->polled = DRM_CONNECTOR_POLL_HPD;
	ret = drm_connector_init(encoder->dev, connector,
				 &zynqmp_dp_connector_funcs,
				 DRM_MODE_CONNECTOR_DisplayPort);
	अगर (ret) अणु
		dev_err(dp->dev, "failed to create the DRM connector\n");
		वापस ret;
	पूर्ण

	drm_connector_helper_add(connector, &zynqmp_dp_connector_helper_funcs);
	drm_connector_रेजिस्टर(connector);
	drm_connector_attach_encoder(connector, encoder);

	/* Initialize and रेजिस्टर the AUX adapter. */
	ret = zynqmp_dp_aux_init(dp);
	अगर (ret) अणु
		dev_err(dp->dev, "failed to initialize DP aux\n");
		वापस ret;
	पूर्ण

	/* Now that initialisation is complete, enable पूर्णांकerrupts. */
	zynqmp_dp_ग_लिखो(dp, ZYNQMP_DP_INT_EN, ZYNQMP_DP_INT_ALL);

	वापस 0;
पूर्ण

पूर्णांक zynqmp_dp_probe(काष्ठा zynqmp_dpsub *dpsub, काष्ठा drm_device *drm)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dpsub->dev);
	काष्ठा zynqmp_dp *dp;
	काष्ठा resource *res;
	पूर्णांक ret;

	dp = drmm_kzalloc(drm, माप(*dp), GFP_KERNEL);
	अगर (!dp)
		वापस -ENOMEM;

	dp->dev = &pdev->dev;
	dp->dpsub = dpsub;
	dp->status = connector_status_disconnected;
	dp->drm = drm;

	INIT_DELAYED_WORK(&dp->hpd_work, zynqmp_dp_hpd_work_func);

	dpsub->dp = dp;

	/* Acquire all resources (IOMEM, IRQ and PHYs). */
	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "dp");
	dp->iomem = devm_ioremap_resource(dp->dev, res);
	अगर (IS_ERR(dp->iomem))
		वापस PTR_ERR(dp->iomem);

	dp->irq = platक्रमm_get_irq(pdev, 0);
	अगर (dp->irq < 0)
		वापस dp->irq;

	dp->reset = devm_reset_control_get(dp->dev, शून्य);
	अगर (IS_ERR(dp->reset)) अणु
		अगर (PTR_ERR(dp->reset) != -EPROBE_DEFER)
			dev_err(dp->dev, "failed to get reset: %ld\n",
				PTR_ERR(dp->reset));
		वापस PTR_ERR(dp->reset);
	पूर्ण

	ret = zynqmp_dp_phy_probe(dp);
	अगर (ret)
		वापस ret;

	/* Initialize the hardware. */
	zynqmp_dp_ग_लिखो(dp, ZYNQMP_DP_TX_PHY_POWER_DOWN,
			ZYNQMP_DP_TX_PHY_POWER_DOWN_ALL);
	zynqmp_dp_set(dp, ZYNQMP_DP_PHY_RESET, ZYNQMP_DP_PHY_RESET_ALL_RESET);
	zynqmp_dp_ग_लिखो(dp, ZYNQMP_DP_FORCE_SCRAMBLER_RESET, 1);
	zynqmp_dp_ग_लिखो(dp, ZYNQMP_DP_TRANSMITTER_ENABLE, 0);
	zynqmp_dp_ग_लिखो(dp, ZYNQMP_DP_INT_DS, 0xffffffff);

	ret = zynqmp_dp_phy_init(dp);
	अगर (ret)
		वापस ret;

	zynqmp_dp_ग_लिखो(dp, ZYNQMP_DP_TRANSMITTER_ENABLE, 1);

	/*
	 * Now that the hardware is initialized and won't generate spurious
	 * पूर्णांकerrupts, request the IRQ.
	 */
	ret = devm_request_thपढ़ोed_irq(dp->dev, dp->irq, शून्य,
					zynqmp_dp_irq_handler, IRQF_ONESHOT,
					dev_name(dp->dev), dp);
	अगर (ret < 0)
		जाओ error;

	dev_dbg(dp->dev, "ZynqMP DisplayPort Tx probed with %u lanes\n",
		dp->num_lanes);

	वापस 0;

error:
	zynqmp_dp_phy_निकास(dp);
	वापस ret;
पूर्ण

व्योम zynqmp_dp_हटाओ(काष्ठा zynqmp_dpsub *dpsub)
अणु
	काष्ठा zynqmp_dp *dp = dpsub->dp;

	zynqmp_dp_ग_लिखो(dp, ZYNQMP_DP_INT_DS, ZYNQMP_DP_INT_ALL);
	disable_irq(dp->irq);

	cancel_delayed_work_sync(&dp->hpd_work);
	zynqmp_dp_aux_cleanup(dp);

	zynqmp_dp_ग_लिखो(dp, ZYNQMP_DP_TRANSMITTER_ENABLE, 0);
	zynqmp_dp_ग_लिखो(dp, ZYNQMP_DP_INT_DS, 0xffffffff);

	zynqmp_dp_phy_निकास(dp);
पूर्ण
