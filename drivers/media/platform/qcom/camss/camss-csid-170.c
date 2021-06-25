<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * camss-csid-4-7.c
 *
 * Qualcomm MSM Camera Subप्रणाली - CSID (CSI Decoder) Module
 *
 * Copyright (C) 2020 Linaro Ltd.
 */
#समावेश <linux/completion.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/of.h>

#समावेश "camss-csid.h"
#समावेश "camss-csid-gen2.h"
#समावेश "camss.h"

/* The CSID 2 IP-block is dअगरferent from the others,
 * and is of a bare-bones Lite version, with no PIX
 * पूर्णांकerface support. As a result of that it has an
 * alternate रेजिस्टर layout.
 */
#घोषणा IS_LITE		(csid->id == 2 ? 1 : 0)

#घोषणा CSID_HW_VERSION		0x0
#घोषणा		HW_VERSION_STEPPING	0
#घोषणा		HW_VERSION_REVISION	16
#घोषणा		HW_VERSION_GENERATION	28

#घोषणा CSID_RST_STROBES	0x10
#घोषणा		RST_STROBES	0

#घोषणा CSID_CSI2_RX_IRQ_STATUS	0x20
#घोषणा	CSID_CSI2_RX_IRQ_MASK	0x24
#घोषणा CSID_CSI2_RX_IRQ_CLEAR	0x28

#घोषणा CSID_CSI2_RDIN_IRQ_STATUS(rdi)		((IS_LITE ? 0x30 : 0x40) \
						 + 0x10 * (rdi))
#घोषणा CSID_CSI2_RDIN_IRQ_MASK(rdi)		((IS_LITE ? 0x34 : 0x44) \
						 + 0x10 * (rdi))
#घोषणा CSID_CSI2_RDIN_IRQ_CLEAR(rdi)		((IS_LITE ? 0x38 : 0x48) \
						 + 0x10 * (rdi))
#घोषणा CSID_CSI2_RDIN_IRQ_SET(rdi)		((IS_LITE ? 0x3C : 0x4C) \
						 + 0x10 * (rdi))

#घोषणा CSID_TOP_IRQ_STATUS	0x70
#घोषणा		TOP_IRQ_STATUS_RESET_DONE 0
#घोषणा CSID_TOP_IRQ_MASK	0x74
#घोषणा CSID_TOP_IRQ_CLEAR	0x78
#घोषणा CSID_TOP_IRQ_SET	0x7C
#घोषणा CSID_IRQ_CMD		0x80
#घोषणा		IRQ_CMD_CLEAR	0
#घोषणा		IRQ_CMD_SET	4

#घोषणा CSID_CSI2_RX_CFG0	0x100
#घोषणा		CSI2_RX_CFG0_NUM_ACTIVE_LANES	0
#घोषणा		CSI2_RX_CFG0_DL0_INPUT_SEL	4
#घोषणा		CSI2_RX_CFG0_DL1_INPUT_SEL	8
#घोषणा		CSI2_RX_CFG0_DL2_INPUT_SEL	12
#घोषणा		CSI2_RX_CFG0_DL3_INPUT_SEL	16
#घोषणा		CSI2_RX_CFG0_PHY_NUM_SEL	20
#घोषणा		CSI2_RX_CFG0_PHY_TYPE_SEL	24

#घोषणा CSID_CSI2_RX_CFG1	0x104
#घोषणा		CSI2_RX_CFG1_PACKET_ECC_CORRECTION_EN		0
#घोषणा		CSI2_RX_CFG1_DE_SCRAMBLE_EN			1
#घोषणा		CSI2_RX_CFG1_VC_MODE				2
#घोषणा		CSI2_RX_CFG1_COMPLETE_STREAM_EN			4
#घोषणा		CSI2_RX_CFG1_COMPLETE_STREAM_FRAME_TIMING	5
#घोषणा		CSI2_RX_CFG1_MISR_EN				6
#घोषणा		CSI2_RX_CFG1_CGC_MODE				7
#घोषणा			CGC_MODE_DYNAMIC_GATING		0
#घोषणा			CGC_MODE_ALWAYS_ON		1

#घोषणा CSID_RDI_CFG0(rdi)			((IS_LITE ? 0x200 : 0x300) \
						 + 0x100 * (rdi))
#घोषणा		RDI_CFG0_BYTE_CNTR_EN		0
#घोषणा		RDI_CFG0_FORMAT_MEASURE_EN	1
#घोषणा		RDI_CFG0_TIMESTAMP_EN		2
#घोषणा		RDI_CFG0_DROP_H_EN		3
#घोषणा		RDI_CFG0_DROP_V_EN		4
#घोषणा		RDI_CFG0_CROP_H_EN		5
#घोषणा		RDI_CFG0_CROP_V_EN		6
#घोषणा		RDI_CFG0_MISR_EN		7
#घोषणा		RDI_CFG0_CGC_MODE		8
#घोषणा			CGC_MODE_DYNAMIC	0
#घोषणा			CGC_MODE_ALWAYS_ON	1
#घोषणा		RDI_CFG0_PLAIN_ALIGNMENT	9
#घोषणा			PLAIN_ALIGNMENT_LSB	0
#घोषणा			PLAIN_ALIGNMENT_MSB	1
#घोषणा		RDI_CFG0_PLAIN_FORMAT		10
#घोषणा		RDI_CFG0_DECODE_FORMAT		12
#घोषणा		RDI_CFG0_DATA_TYPE		16
#घोषणा		RDI_CFG0_VIRTUAL_CHANNEL	22
#घोषणा		RDI_CFG0_DT_ID			27
#घोषणा		RDI_CFG0_EARLY_खातापूर्ण_EN		29
#घोषणा		RDI_CFG0_PACKING_FORMAT		30
#घोषणा		RDI_CFG0_ENABLE			31

#घोषणा CSID_RDI_CFG1(rdi)			((IS_LITE ? 0x204 : 0x304)\
						+ 0x100 * (rdi))
#घोषणा		RDI_CFG1_TIMESTAMP_STB_SEL	0

#घोषणा CSID_RDI_CTRL(rdi)			((IS_LITE ? 0x208 : 0x308)\
						+ 0x100 * (rdi))
#घोषणा		RDI_CTRL_HALT_CMD		0
#घोषणा			ALT_CMD_RESUME_AT_FRAME_BOUNDARY	1
#घोषणा		RDI_CTRL_HALT_MODE		2

#घोषणा CSID_RDI_FRM_DROP_PATTERN(rdi)			((IS_LITE ? 0x20C : 0x30C)\
							+ 0x100 * (rdi))
#घोषणा CSID_RDI_FRM_DROP_PERIOD(rdi)			((IS_LITE ? 0x210 : 0x310)\
							+ 0x100 * (rdi))
#घोषणा CSID_RDI_IRQ_SUBSAMPLE_PATTERN(rdi)		((IS_LITE ? 0x214 : 0x314)\
							+ 0x100 * (rdi))
#घोषणा CSID_RDI_IRQ_SUBSAMPLE_PERIOD(rdi)		((IS_LITE ? 0x218 : 0x318)\
							+ 0x100 * (rdi))
#घोषणा CSID_RDI_RPP_PIX_DROP_PATTERN(rdi)		((IS_LITE ? 0x224 : 0x324)\
							+ 0x100 * (rdi))
#घोषणा CSID_RDI_RPP_PIX_DROP_PERIOD(rdi)		((IS_LITE ? 0x228 : 0x328)\
							+ 0x100 * (rdi))
#घोषणा CSID_RDI_RPP_LINE_DROP_PATTERN(rdi)		((IS_LITE ? 0x22C : 0x32C)\
							+ 0x100 * (rdi))
#घोषणा CSID_RDI_RPP_LINE_DROP_PERIOD(rdi)		((IS_LITE ? 0x230 : 0x330)\
							+ 0x100 * (rdi))

#घोषणा CSID_TPG_CTRL		0x600
#घोषणा		TPG_CTRL_TEST_EN		0
#घोषणा		TPG_CTRL_FS_PKT_EN		1
#घोषणा		TPG_CTRL_FE_PKT_EN		2
#घोषणा		TPG_CTRL_NUM_ACTIVE_LANES	4
#घोषणा		TPG_CTRL_CYCLES_BETWEEN_PKTS	8
#घोषणा		TPG_CTRL_NUM_TRAIL_BYTES	20

#घोषणा CSID_TPG_VC_CFG0	0x604
#घोषणा		TPG_VC_CFG0_VC_NUM			0
#घोषणा		TPG_VC_CFG0_NUM_ACTIVE_SLOTS		8
#घोषणा			NUM_ACTIVE_SLOTS_0_ENABLED	0
#घोषणा			NUM_ACTIVE_SLOTS_0_1_ENABLED	1
#घोषणा			NUM_ACTIVE_SLOTS_0_1_2_ENABLED	2
#घोषणा			NUM_ACTIVE_SLOTS_0_1_3_ENABLED	3
#घोषणा		TPG_VC_CFG0_LINE_INTERLEAVING_MODE	10
#घोषणा			INTELEAVING_MODE_INTERLEAVED	0
#घोषणा			INTELEAVING_MODE_ONE_SHOT	1
#घोषणा		TPG_VC_CFG0_NUM_FRAMES			16

#घोषणा CSID_TPG_VC_CFG1	0x608
#घोषणा		TPG_VC_CFG1_H_BLANKING_COUNT		0
#घोषणा		TPG_VC_CFG1_V_BLANKING_COUNT		12
#घोषणा		TPG_VC_CFG1_V_BLANK_FRAME_WIDTH_SEL	24

#घोषणा CSID_TPG_LFSR_SEED	0x60C

#घोषणा CSID_TPG_DT_n_CFG_0(n)	(0x610 + (n) * 0xC)
#घोषणा		TPG_DT_n_CFG_0_FRAME_HEIGHT	0
#घोषणा		TPG_DT_n_CFG_0_FRAME_WIDTH	16

#घोषणा CSID_TPG_DT_n_CFG_1(n)	(0x614 + (n) * 0xC)
#घोषणा		TPG_DT_n_CFG_1_DATA_TYPE	0
#घोषणा		TPG_DT_n_CFG_1_ECC_XOR_MASK	8
#घोषणा		TPG_DT_n_CFG_1_CRC_XOR_MASK	16

#घोषणा CSID_TPG_DT_n_CFG_2(n)	(0x618 + (n) * 0xC)
#घोषणा		TPG_DT_n_CFG_2_PAYLOAD_MODE		0
#घोषणा		TPG_DT_n_CFG_2_USER_SPECIFIED_PAYLOAD	4
#घोषणा		TPG_DT_n_CFG_2_ENCODE_FORMAT		16

#घोषणा CSID_TPG_COLOR_BARS_CFG	0x640
#घोषणा		TPG_COLOR_BARS_CFG_UNICOLOR_BAR_EN	0
#घोषणा		TPG_COLOR_BARS_CFG_UNICOLOR_BAR_SEL	4
#घोषणा		TPG_COLOR_BARS_CFG_SPLIT_EN		5
#घोषणा		TPG_COLOR_BARS_CFG_ROTATE_PERIOD	8

#घोषणा CSID_TPG_COLOR_BOX_CFG	0x644
#घोषणा		TPG_COLOR_BOX_CFG_MODE		0
#घोषणा		TPG_COLOR_BOX_PATTERN_SEL	2

अटल स्थिर काष्ठा csid_क्रमmat csid_क्रमmats[] = अणु
	अणु
		MEDIA_BUS_FMT_UYVY8_2X8,
		DATA_TYPE_YUV422_8BIT,
		DECODE_FORMAT_UNCOMPRESSED_8_BIT,
		8,
		2,
	पूर्ण,
	अणु
		MEDIA_BUS_FMT_VYUY8_2X8,
		DATA_TYPE_YUV422_8BIT,
		DECODE_FORMAT_UNCOMPRESSED_8_BIT,
		8,
		2,
	पूर्ण,
	अणु
		MEDIA_BUS_FMT_YUYV8_2X8,
		DATA_TYPE_YUV422_8BIT,
		DECODE_FORMAT_UNCOMPRESSED_8_BIT,
		8,
		2,
	पूर्ण,
	अणु
		MEDIA_BUS_FMT_YVYU8_2X8,
		DATA_TYPE_YUV422_8BIT,
		DECODE_FORMAT_UNCOMPRESSED_8_BIT,
		8,
		2,
	पूर्ण,
	अणु
		MEDIA_BUS_FMT_SBGGR8_1X8,
		DATA_TYPE_RAW_8BIT,
		DECODE_FORMAT_UNCOMPRESSED_8_BIT,
		8,
		1,
	पूर्ण,
	अणु
		MEDIA_BUS_FMT_SGBRG8_1X8,
		DATA_TYPE_RAW_8BIT,
		DECODE_FORMAT_UNCOMPRESSED_8_BIT,
		8,
		1,
	पूर्ण,
	अणु
		MEDIA_BUS_FMT_SGRBG8_1X8,
		DATA_TYPE_RAW_8BIT,
		DECODE_FORMAT_UNCOMPRESSED_8_BIT,
		8,
		1,
	पूर्ण,
	अणु
		MEDIA_BUS_FMT_SRGGB8_1X8,
		DATA_TYPE_RAW_8BIT,
		DECODE_FORMAT_UNCOMPRESSED_8_BIT,
		8,
		1,
	पूर्ण,
	अणु
		MEDIA_BUS_FMT_SBGGR10_1X10,
		DATA_TYPE_RAW_10BIT,
		DECODE_FORMAT_UNCOMPRESSED_10_BIT,
		10,
		1,
	पूर्ण,
	अणु
		MEDIA_BUS_FMT_SGBRG10_1X10,
		DATA_TYPE_RAW_10BIT,
		DECODE_FORMAT_UNCOMPRESSED_10_BIT,
		10,
		1,
	पूर्ण,
	अणु
		MEDIA_BUS_FMT_SGRBG10_1X10,
		DATA_TYPE_RAW_10BIT,
		DECODE_FORMAT_UNCOMPRESSED_10_BIT,
		10,
		1,
	पूर्ण,
	अणु
		MEDIA_BUS_FMT_SRGGB10_1X10,
		DATA_TYPE_RAW_10BIT,
		DECODE_FORMAT_UNCOMPRESSED_10_BIT,
		10,
		1,
	पूर्ण,
	अणु
		MEDIA_BUS_FMT_Y10_1X10,
		DATA_TYPE_RAW_10BIT,
		DECODE_FORMAT_UNCOMPRESSED_10_BIT,
		10,
		1,
	पूर्ण,
	अणु
		MEDIA_BUS_FMT_SBGGR12_1X12,
		DATA_TYPE_RAW_12BIT,
		DECODE_FORMAT_UNCOMPRESSED_12_BIT,
		12,
		1,
	पूर्ण,
	अणु
		MEDIA_BUS_FMT_SGBRG12_1X12,
		DATA_TYPE_RAW_12BIT,
		DECODE_FORMAT_UNCOMPRESSED_12_BIT,
		12,
		1,
	पूर्ण,
	अणु
		MEDIA_BUS_FMT_SGRBG12_1X12,
		DATA_TYPE_RAW_12BIT,
		DECODE_FORMAT_UNCOMPRESSED_12_BIT,
		12,
		1,
	पूर्ण,
	अणु
		MEDIA_BUS_FMT_SRGGB12_1X12,
		DATA_TYPE_RAW_12BIT,
		DECODE_FORMAT_UNCOMPRESSED_12_BIT,
		12,
		1,
	पूर्ण,
	अणु
		MEDIA_BUS_FMT_SBGGR14_1X14,
		DATA_TYPE_RAW_14BIT,
		DECODE_FORMAT_UNCOMPRESSED_14_BIT,
		14,
		1,
	पूर्ण,
	अणु
		MEDIA_BUS_FMT_SGBRG14_1X14,
		DATA_TYPE_RAW_14BIT,
		DECODE_FORMAT_UNCOMPRESSED_14_BIT,
		14,
		1,
	पूर्ण,
	अणु
		MEDIA_BUS_FMT_SGRBG14_1X14,
		DATA_TYPE_RAW_14BIT,
		DECODE_FORMAT_UNCOMPRESSED_14_BIT,
		14,
		1,
	पूर्ण,
	अणु
		MEDIA_BUS_FMT_SRGGB14_1X14,
		DATA_TYPE_RAW_14BIT,
		DECODE_FORMAT_UNCOMPRESSED_14_BIT,
		14,
		1,
	पूर्ण,
पूर्ण;

अटल व्योम csid_configure_stream(काष्ठा csid_device *csid, u8 enable)
अणु
	काष्ठा csid_testgen_config *tg = &csid->testgen;
	u32 val;
	u32 phy_sel = 0;
	u8 lane_cnt = csid->phy.lane_cnt;
	काष्ठा v4l2_mbus_framefmt *input_क्रमmat = &csid->fmt[MSM_CSID_PAD_SRC];
	स्थिर काष्ठा csid_क्रमmat *क्रमmat = csid_get_fmt_entry(csid->क्रमmats, csid->nक्रमmats,
							      input_क्रमmat->code);

	अगर (!lane_cnt)
		lane_cnt = 4;

	अगर (!tg->enabled)
		phy_sel = csid->phy.csiphy_id;

	अगर (enable) अणु
		u8 vc = 0; /* Virtual Channel 0 */
		u8 dt_id = vc * 4;

		अगर (tg->enabled) अणु
			/* Config Test Generator */
			vc = 0xa;

			/* configure one DT, infinite frames */
			val = vc << TPG_VC_CFG0_VC_NUM;
			val |= INTELEAVING_MODE_ONE_SHOT << TPG_VC_CFG0_LINE_INTERLEAVING_MODE;
			val |= 0 << TPG_VC_CFG0_NUM_FRAMES;
			ग_लिखोl_relaxed(val, csid->base + CSID_TPG_VC_CFG0);

			val = 0x740 << TPG_VC_CFG1_H_BLANKING_COUNT;
			val |= 0x3ff << TPG_VC_CFG1_V_BLANKING_COUNT;
			ग_लिखोl_relaxed(val, csid->base + CSID_TPG_VC_CFG1);

			ग_लिखोl_relaxed(0x12345678, csid->base + CSID_TPG_LFSR_SEED);

			val = input_क्रमmat->height & 0x1fff << TPG_DT_n_CFG_0_FRAME_HEIGHT;
			val |= input_क्रमmat->width & 0x1fff << TPG_DT_n_CFG_0_FRAME_WIDTH;
			ग_लिखोl_relaxed(val, csid->base + CSID_TPG_DT_n_CFG_0(0));

			val = DATA_TYPE_RAW_10BIT << TPG_DT_n_CFG_1_DATA_TYPE;
			ग_लिखोl_relaxed(val, csid->base + CSID_TPG_DT_n_CFG_1(0));

			val = tg->mode << TPG_DT_n_CFG_2_PAYLOAD_MODE;
			val |= 0xBE << TPG_DT_n_CFG_2_USER_SPECIFIED_PAYLOAD;
			val |= क्रमmat->decode_क्रमmat << TPG_DT_n_CFG_2_ENCODE_FORMAT;
			ग_लिखोl_relaxed(val, csid->base + CSID_TPG_DT_n_CFG_2(0));

			ग_लिखोl_relaxed(0, csid->base + CSID_TPG_COLOR_BARS_CFG);

			ग_लिखोl_relaxed(0, csid->base + CSID_TPG_COLOR_BOX_CFG);
		पूर्ण

		val = 1 << RDI_CFG0_BYTE_CNTR_EN;
		val |= 1 << RDI_CFG0_FORMAT_MEASURE_EN;
		val |= 1 << RDI_CFG0_TIMESTAMP_EN;
		val |= DECODE_FORMAT_PAYLOAD_ONLY << RDI_CFG0_DECODE_FORMAT;
		val |= DATA_TYPE_RAW_10BIT << RDI_CFG0_DATA_TYPE;
		val |= vc << RDI_CFG0_VIRTUAL_CHANNEL;
		val |= dt_id << RDI_CFG0_DT_ID;
		ग_लिखोl_relaxed(val, csid->base + CSID_RDI_CFG0(0));

		/* CSID_TIMESTAMP_STB_POST_IRQ */
		val = 2 << RDI_CFG1_TIMESTAMP_STB_SEL;
		ग_लिखोl_relaxed(val, csid->base + CSID_RDI_CFG1(0));

		val = 1;
		ग_लिखोl_relaxed(val, csid->base + CSID_RDI_FRM_DROP_PERIOD(0));

		val = 0;
		ग_लिखोl_relaxed(0, csid->base + CSID_RDI_FRM_DROP_PATTERN(0));

		val = 1;
		ग_लिखोl_relaxed(val, csid->base + CSID_RDI_IRQ_SUBSAMPLE_PERIOD(0));

		val = 0;
		ग_लिखोl_relaxed(val, csid->base + CSID_RDI_IRQ_SUBSAMPLE_PATTERN(0));

		val = 1;
		ग_लिखोl_relaxed(val, csid->base + CSID_RDI_RPP_PIX_DROP_PERIOD(0));

		val = 0;
		ग_लिखोl_relaxed(val, csid->base + CSID_RDI_RPP_PIX_DROP_PATTERN(0));

		val = 1;
		ग_लिखोl_relaxed(val, csid->base + CSID_RDI_RPP_LINE_DROP_PERIOD(0));

		val = 0;
		ग_लिखोl_relaxed(val, csid->base + CSID_RDI_RPP_LINE_DROP_PATTERN(0));

		val = 0;
		ग_लिखोl_relaxed(val, csid->base + CSID_RDI_CTRL(0));

		val = पढ़ोl_relaxed(csid->base + CSID_RDI_CFG0(0));
		val |=  1 << RDI_CFG0_ENABLE;
		ग_लिखोl_relaxed(val, csid->base + CSID_RDI_CFG0(0));
	पूर्ण

	अगर (tg->enabled) अणु
		val = enable << TPG_CTRL_TEST_EN;
		val |= 1 << TPG_CTRL_FS_PKT_EN;
		val |= 1 << TPG_CTRL_FE_PKT_EN;
		val |= (lane_cnt - 1) << TPG_CTRL_NUM_ACTIVE_LANES;
		val |= 0x64 << TPG_CTRL_CYCLES_BETWEEN_PKTS;
		val |= 0xA << TPG_CTRL_NUM_TRAIL_BYTES;
		ग_लिखोl_relaxed(val, csid->base + CSID_TPG_CTRL);
	पूर्ण

	val = (lane_cnt - 1) << CSI2_RX_CFG0_NUM_ACTIVE_LANES;
	val |= csid->phy.lane_assign << CSI2_RX_CFG0_DL0_INPUT_SEL;
	val |= phy_sel << CSI2_RX_CFG0_PHY_NUM_SEL;
	ग_लिखोl_relaxed(val, csid->base + CSID_CSI2_RX_CFG0);

	val = 1 << CSI2_RX_CFG1_PACKET_ECC_CORRECTION_EN;
	val |= 1 << CSI2_RX_CFG1_MISR_EN;
	ग_लिखोl_relaxed(val, csid->base + CSID_CSI2_RX_CFG1); // csi2_vc_mode_shअगरt_val ?

	/* error irqs start at BIT(11) */
	ग_लिखोl_relaxed(~0u, csid->base + CSID_CSI2_RX_IRQ_MASK);

	/* RDI irq */
	ग_लिखोl_relaxed(~0u, csid->base + CSID_TOP_IRQ_MASK);

	val = 1 << RDI_CTRL_HALT_CMD;
	ग_लिखोl_relaxed(val, csid->base + CSID_RDI_CTRL(0));
पूर्ण

अटल पूर्णांक csid_configure_testgen_pattern(काष्ठा csid_device *csid, s32 val)
अणु
	अगर (val > 0 && val <= csid->testgen.nmodes)
		csid->testgen.mode = val;

	वापस 0;
पूर्ण

/*
 * csid_hw_version - CSID hardware version query
 * @csid: CSID device
 *
 * Return HW version or error
 */
अटल u32 csid_hw_version(काष्ठा csid_device *csid)
अणु
	u32 hw_version;
	u32 hw_gen;
	u32 hw_rev;
	u32 hw_step;

	hw_version = पढ़ोl_relaxed(csid->base + CSID_HW_VERSION);
	hw_gen = (hw_version >> HW_VERSION_GENERATION) & 0xF;
	hw_rev = (hw_version >> HW_VERSION_REVISION) & 0xFFF;
	hw_step = (hw_version >> HW_VERSION_STEPPING) & 0xFFFF;
	dev_dbg(csid->camss->dev, "CSID HW Version = %u.%u.%u\n",
		hw_gen, hw_rev, hw_step);

	वापस hw_version;
पूर्ण

/*
 * csid_isr - CSID module पूर्णांकerrupt service routine
 * @irq: Interrupt line
 * @dev: CSID device
 *
 * Return IRQ_HANDLED on success
 */
अटल irqवापस_t csid_isr(पूर्णांक irq, व्योम *dev)
अणु
	काष्ठा csid_device *csid = dev;
	u32 val;
	u8 reset_करोne;

	val = पढ़ोl_relaxed(csid->base + CSID_TOP_IRQ_STATUS);
	ग_लिखोl_relaxed(val, csid->base + CSID_TOP_IRQ_CLEAR);
	reset_करोne = val & BIT(TOP_IRQ_STATUS_RESET_DONE);

	val = पढ़ोl_relaxed(csid->base + CSID_CSI2_RX_IRQ_STATUS);
	ग_लिखोl_relaxed(val, csid->base + CSID_CSI2_RX_IRQ_CLEAR);

	val = पढ़ोl_relaxed(csid->base + CSID_CSI2_RDIN_IRQ_STATUS(0));
	ग_लिखोl_relaxed(val, csid->base + CSID_CSI2_RDIN_IRQ_CLEAR(0));

	val = 1 << IRQ_CMD_CLEAR;
	ग_लिखोl_relaxed(val, csid->base + CSID_IRQ_CMD);

	अगर (reset_करोne)
		complete(&csid->reset_complete);

	वापस IRQ_HANDLED;
पूर्ण

/*
 * csid_reset - Trigger reset on CSID module and रुको to complete
 * @csid: CSID device
 *
 * Return 0 on success or a negative error code otherwise
 */
अटल पूर्णांक csid_reset(काष्ठा csid_device *csid)
अणु
	अचिन्हित दीर्घ समय;
	u32 val;

	reinit_completion(&csid->reset_complete);

	ग_लिखोl_relaxed(1, csid->base + CSID_TOP_IRQ_CLEAR);
	ग_लिखोl_relaxed(1, csid->base + CSID_IRQ_CMD);
	ग_लिखोl_relaxed(1, csid->base + CSID_TOP_IRQ_MASK);
	ग_लिखोl_relaxed(1, csid->base + CSID_IRQ_CMD);

	/* preserve रेजिस्टरs */
	val = 0x1e << RST_STROBES;
	ग_लिखोl_relaxed(val, csid->base + CSID_RST_STROBES);

	समय = रुको_क्रम_completion_समयout(&csid->reset_complete,
					   msecs_to_jअगरfies(CSID_RESET_TIMEOUT_MS));
	अगर (!समय) अणु
		dev_err(csid->camss->dev, "CSID reset timeout\n");
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल u32 csid_src_pad_code(काष्ठा csid_device *csid, u32 sink_code,
			     अचिन्हित पूर्णांक match_क्रमmat_idx, u32 match_code)
अणु
	चयन (sink_code) अणु
	हाल MEDIA_BUS_FMT_SBGGR10_1X10:
	अणु
		u32 src_code[] = अणु
			MEDIA_BUS_FMT_SBGGR10_1X10,
			MEDIA_BUS_FMT_SBGGR10_2X8_PADHI_LE,
		पूर्ण;

		वापस csid_find_code(src_code, ARRAY_SIZE(src_code),
				      match_क्रमmat_idx, match_code);
	पूर्ण
	हाल MEDIA_BUS_FMT_Y10_1X10:
	अणु
		u32 src_code[] = अणु
			MEDIA_BUS_FMT_Y10_1X10,
			MEDIA_BUS_FMT_Y10_2X8_PADHI_LE,
		पूर्ण;

		वापस csid_find_code(src_code, ARRAY_SIZE(src_code),
				      match_क्रमmat_idx, match_code);
	पूर्ण
	शेष:
		अगर (match_क्रमmat_idx > 0)
			वापस 0;

		वापस sink_code;
	पूर्ण
पूर्ण

अटल व्योम csid_subdev_init(काष्ठा csid_device *csid)
अणु
	csid->क्रमmats = csid_क्रमmats;
	csid->nक्रमmats = ARRAY_SIZE(csid_क्रमmats);
	csid->testgen.modes = csid_testgen_modes;
	csid->testgen.nmodes = CSID_PAYLOAD_MODE_NUM_SUPPORTED_GEN2;
पूर्ण

स्थिर काष्ठा csid_hw_ops csid_ops_170 = अणु
	.configure_stream = csid_configure_stream,
	.configure_testgen_pattern = csid_configure_testgen_pattern,
	.hw_version = csid_hw_version,
	.isr = csid_isr,
	.reset = csid_reset,
	.src_pad_code = csid_src_pad_code,
	.subdev_init = csid_subdev_init,
पूर्ण;
