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
#समावेश "camss-csid-gen1.h"
#समावेश "camss.h"

#घोषणा CAMSS_CSID_HW_VERSION		0x0
#घोषणा CAMSS_CSID_CORE_CTRL_0		0x004
#घोषणा CAMSS_CSID_CORE_CTRL_1		0x008
#घोषणा CAMSS_CSID_RST_CMD		0x010
#घोषणा CAMSS_CSID_CID_LUT_VC_n(n)	(0x014 + 0x4 * (n))
#घोषणा CAMSS_CSID_CID_n_CFG(n)		(0x024 + 0x4 * (n))
#घोषणा CAMSS_CSID_CID_n_CFG_ISPIF_EN	BIT(0)
#घोषणा CAMSS_CSID_CID_n_CFG_RDI_EN	BIT(1)
#घोषणा CAMSS_CSID_CID_n_CFG_DECODE_FORMAT_SHIFT	4
#घोषणा CAMSS_CSID_CID_n_CFG_PLAIN_FORMAT_8		(PLAIN_FORMAT_PLAIN8 << 8)
#घोषणा CAMSS_CSID_CID_n_CFG_PLAIN_FORMAT_16		(PLAIN_FORMAT_PLAIN16 << 8)
#घोषणा CAMSS_CSID_CID_n_CFG_PLAIN_ALIGNMENT_LSB	(0 << 9)
#घोषणा CAMSS_CSID_CID_n_CFG_PLAIN_ALIGNMENT_MSB	(1 << 9)
#घोषणा CAMSS_CSID_CID_n_CFG_RDI_MODE_RAW_DUMP		(0 << 10)
#घोषणा CAMSS_CSID_CID_n_CFG_RDI_MODE_PLAIN_PACKING	(1 << 10)
#घोषणा CAMSS_CSID_IRQ_CLEAR_CMD	0x064
#घोषणा CAMSS_CSID_IRQ_MASK		0x068
#घोषणा CAMSS_CSID_IRQ_STATUS		0x06c
#घोषणा CAMSS_CSID_TG_CTRL		0x0a8
#घोषणा CAMSS_CSID_TG_CTRL_DISABLE	0xa06436
#घोषणा CAMSS_CSID_TG_CTRL_ENABLE	0xa06437
#घोषणा CAMSS_CSID_TG_VC_CFG		0x0ac
#घोषणा CAMSS_CSID_TG_VC_CFG_H_BLANKING		0x3ff
#घोषणा CAMSS_CSID_TG_VC_CFG_V_BLANKING		0x7f
#घोषणा CAMSS_CSID_TG_DT_n_CGG_0(n)	(0x0b4 + 0xc * (n))
#घोषणा CAMSS_CSID_TG_DT_n_CGG_1(n)	(0x0b8 + 0xc * (n))
#घोषणा CAMSS_CSID_TG_DT_n_CGG_2(n)	(0x0bc + 0xc * (n))

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
	अणु
		MEDIA_BUS_FMT_Y10_1X10,
		DATA_TYPE_RAW_10BIT,
		DECODE_FORMAT_UNCOMPRESSED_10_BIT,
		10,
		1,
	पूर्ण,
पूर्ण;

अटल व्योम csid_configure_stream(काष्ठा csid_device *csid, u8 enable)
अणु
	काष्ठा csid_testgen_config *tg = &csid->testgen;
	u32 sink_code = csid->fmt[MSM_CSID_PAD_SINK].code;
	u32 src_code = csid->fmt[MSM_CSID_PAD_SRC].code;
	u32 val;

	अगर (enable) अणु
		काष्ठा v4l2_mbus_framefmt *input_क्रमmat;
		स्थिर काष्ठा csid_क्रमmat *क्रमmat;
		u8 vc = 0; /* Virtual Channel 0 */
		u8 cid = vc * 4; /* id of Virtual Channel and Data Type set */
		u8 dt_shअगरt;

		अगर (tg->enabled) अणु
			/* Config Test Generator */
			u32 num_bytes_per_line, num_lines;

			input_क्रमmat = &csid->fmt[MSM_CSID_PAD_SRC];
			क्रमmat = csid_get_fmt_entry(csid->क्रमmats, csid->nक्रमmats,
						    input_क्रमmat->code);
			num_bytes_per_line = input_क्रमmat->width * क्रमmat->bpp * क्रमmat->spp / 8;
			num_lines = input_क्रमmat->height;

			/* 31:24 V blank, 23:13 H blank, 3:2 num of active DT */
			/* 1:0 VC */
			val = ((CAMSS_CSID_TG_VC_CFG_V_BLANKING & 0xff) << 24) |
				  ((CAMSS_CSID_TG_VC_CFG_H_BLANKING & 0x7ff) << 13);
			ग_लिखोl_relaxed(val, csid->base + CAMSS_CSID_TG_VC_CFG);

			/* 28:16 bytes per lines, 12:0 num of lines */
			val = ((num_bytes_per_line & 0x1fff) << 16) |
				  (num_lines & 0x1fff);
			ग_लिखोl_relaxed(val, csid->base + CAMSS_CSID_TG_DT_n_CGG_0(0));

			/* 5:0 data type */
			val = क्रमmat->data_type;
			ग_लिखोl_relaxed(val, csid->base + CAMSS_CSID_TG_DT_n_CGG_1(0));

			/* 2:0 output test pattern */
			val = tg->mode - 1;
			ग_लिखोl_relaxed(val, csid->base + CAMSS_CSID_TG_DT_n_CGG_2(0));
		पूर्ण अन्यथा अणु
			काष्ठा csid_phy_config *phy = &csid->phy;

			input_क्रमmat = &csid->fmt[MSM_CSID_PAD_SINK];
			क्रमmat = csid_get_fmt_entry(csid->क्रमmats, csid->nक्रमmats,
						    input_क्रमmat->code);

			val = phy->lane_cnt - 1;
			val |= phy->lane_assign << 4;

			ग_लिखोl_relaxed(val, csid->base + CAMSS_CSID_CORE_CTRL_0);

			val = phy->csiphy_id << 17;
			val |= 0x9;

			ग_लिखोl_relaxed(val, csid->base + CAMSS_CSID_CORE_CTRL_1);
		पूर्ण

		/* Config LUT */

		dt_shअगरt = (cid % 4) * 8;

		val = पढ़ोl_relaxed(csid->base + CAMSS_CSID_CID_LUT_VC_n(vc));
		val &= ~(0xff << dt_shअगरt);
		val |= क्रमmat->data_type << dt_shअगरt;
		ग_लिखोl_relaxed(val, csid->base + CAMSS_CSID_CID_LUT_VC_n(vc));

		val = CAMSS_CSID_CID_n_CFG_ISPIF_EN;
		val |= CAMSS_CSID_CID_n_CFG_RDI_EN;
		val |= क्रमmat->decode_क्रमmat << CAMSS_CSID_CID_n_CFG_DECODE_FORMAT_SHIFT;
		val |= CAMSS_CSID_CID_n_CFG_RDI_MODE_RAW_DUMP;

		अगर ((sink_code == MEDIA_BUS_FMT_SBGGR10_1X10 &&
		     src_code == MEDIA_BUS_FMT_SBGGR10_2X8_PADHI_LE) ||
		    (sink_code == MEDIA_BUS_FMT_Y10_1X10 &&
		     src_code == MEDIA_BUS_FMT_Y10_2X8_PADHI_LE)) अणु
			val |= CAMSS_CSID_CID_n_CFG_RDI_MODE_PLAIN_PACKING;
			val |= CAMSS_CSID_CID_n_CFG_PLAIN_FORMAT_16;
			val |= CAMSS_CSID_CID_n_CFG_PLAIN_ALIGNMENT_LSB;
		पूर्ण

		ग_लिखोl_relaxed(val, csid->base + CAMSS_CSID_CID_n_CFG(cid));

		अगर (tg->enabled) अणु
			val = CAMSS_CSID_TG_CTRL_ENABLE;
			ग_लिखोl_relaxed(val, csid->base + CAMSS_CSID_TG_CTRL);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (tg->enabled) अणु
			val = CAMSS_CSID_TG_CTRL_DISABLE;
			ग_लिखोl_relaxed(val, csid->base + CAMSS_CSID_TG_CTRL);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक csid_configure_testgen_pattern(काष्ठा csid_device *csid, s32 val)
अणु
	अगर (val > 0 && val <= csid->testgen.nmodes)
		csid->testgen.mode = val;

	वापस 0;
पूर्ण

अटल u32 csid_hw_version(काष्ठा csid_device *csid)
अणु
	u32 hw_version = पढ़ोl_relaxed(csid->base + CAMSS_CSID_HW_VERSION);

	dev_dbg(csid->camss->dev, "CSID HW Version = 0x%08x\n", hw_version);

	वापस hw_version;
पूर्ण

/*
 * isr - CSID module पूर्णांकerrupt service routine
 * @irq: Interrupt line
 * @dev: CSID device
 *
 * Return IRQ_HANDLED on success
 */
अटल irqवापस_t csid_isr(पूर्णांक irq, व्योम *dev)
अणु
	काष्ठा csid_device *csid = dev;
	u32 value;

	value = पढ़ोl_relaxed(csid->base + CAMSS_CSID_IRQ_STATUS);
	ग_लिखोl_relaxed(value, csid->base + CAMSS_CSID_IRQ_CLEAR_CMD);

	अगर ((value >> 11) & 0x1)
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

	reinit_completion(&csid->reset_complete);

	ग_लिखोl_relaxed(0x7fff, csid->base + CAMSS_CSID_RST_CMD);

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
	csid->testgen.nmodes = CSID_PAYLOAD_MODE_NUM_SUPPORTED_GEN1;
पूर्ण

स्थिर काष्ठा csid_hw_ops csid_ops_4_7 = अणु
	.configure_stream = csid_configure_stream,
	.configure_testgen_pattern = csid_configure_testgen_pattern,
	.hw_version = csid_hw_version,
	.isr = csid_isr,
	.reset = csid_reset,
	.src_pad_code = csid_src_pad_code,
	.subdev_init = csid_subdev_init,
पूर्ण;
