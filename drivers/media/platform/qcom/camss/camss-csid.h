<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * camss-csid.h
 *
 * Qualcomm MSM Camera Subप्रणाली - CSID (CSI Decoder) Module
 *
 * Copyright (c) 2011-2014, The Linux Foundation. All rights reserved.
 * Copyright (C) 2015-2018 Linaro Ltd.
 */
#अगर_अघोषित QC_MSM_CAMSS_CSID_H
#घोषणा QC_MSM_CAMSS_CSID_H

#समावेश <linux/clk.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <media/media-entity.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-mediabus.h>
#समावेश <media/v4l2-subdev.h>

#घोषणा MSM_CSID_PAD_SINK 0
#घोषणा MSM_CSID_PAD_SRC 1
#घोषणा MSM_CSID_PADS_NUM 2

#घोषणा DATA_TYPE_EMBEDDED_DATA_8BIT	0x12
#घोषणा DATA_TYPE_YUV420_8BIT		0x18
#घोषणा DATA_TYPE_YUV420_10BIT		0x19
#घोषणा DATA_TYPE_YUV420_8BIT_LEGACY	0x1a
#घोषणा DATA_TYPE_YUV420_8BIT_SHIFTED	0x1c /* Chroma Shअगरted Pixel Sampling */
#घोषणा DATA_TYPE_YUV420_10BIT_SHIFTED	0x1d /* Chroma Shअगरted Pixel Sampling */
#घोषणा DATA_TYPE_YUV422_8BIT		0x1e
#घोषणा DATA_TYPE_YUV422_10BIT		0x1f
#घोषणा DATA_TYPE_RGB444		0x20
#घोषणा DATA_TYPE_RGB555		0x21
#घोषणा DATA_TYPE_RGB565		0x22
#घोषणा DATA_TYPE_RGB666		0x23
#घोषणा DATA_TYPE_RGB888		0x24
#घोषणा DATA_TYPE_RAW_24BIT		0x27
#घोषणा DATA_TYPE_RAW_6BIT		0x28
#घोषणा DATA_TYPE_RAW_7BIT		0x29
#घोषणा DATA_TYPE_RAW_8BIT		0x2a
#घोषणा DATA_TYPE_RAW_10BIT		0x2b
#घोषणा DATA_TYPE_RAW_12BIT		0x2c
#घोषणा DATA_TYPE_RAW_14BIT		0x2d
#घोषणा DATA_TYPE_RAW_16BIT		0x2e
#घोषणा DATA_TYPE_RAW_20BIT		0x2f

#घोषणा CSID_RESET_TIMEOUT_MS 500

क्रमागत csid_testgen_mode अणु
	CSID_PAYLOAD_MODE_DISABLED = 0,
	CSID_PAYLOAD_MODE_INCREMENTING = 1,
	CSID_PAYLOAD_MODE_ALTERNATING_55_AA = 2,
	CSID_PAYLOAD_MODE_ALL_ZEROES = 3,
	CSID_PAYLOAD_MODE_ALL_ONES = 4,
	CSID_PAYLOAD_MODE_RANDOM = 5,
	CSID_PAYLOAD_MODE_USER_SPECIFIED = 6,
	CSID_PAYLOAD_MODE_NUM_SUPPORTED_GEN1 = 6, /* excluding disabled */
	CSID_PAYLOAD_MODE_COMPLEX_PATTERN = 7,
	CSID_PAYLOAD_MODE_COLOR_BOX = 8,
	CSID_PAYLOAD_MODE_COLOR_BARS = 9,
	CSID_PAYLOAD_MODE_NUM_SUPPORTED_GEN2 = 9, /* excluding disabled */
पूर्ण;

काष्ठा csid_क्रमmat अणु
	u32 code;
	u8 data_type;
	u8 decode_क्रमmat;
	u8 bpp;
	u8 spp; /* bus samples per pixel */
पूर्ण;

काष्ठा csid_testgen_config अणु
	क्रमागत csid_testgen_mode mode;
	स्थिर अक्षर * स्थिर*modes;
	u8 nmodes;
	u8 enabled;
पूर्ण;

काष्ठा csid_phy_config अणु
	u8 csiphy_id;
	u8 lane_cnt;
	u32 lane_assign;
पूर्ण;

काष्ठा csid_device;

काष्ठा csid_hw_ops अणु
	/*
	 * configure_stream - Configures and starts CSID input stream
	 * @csid: CSID device
	 */
	व्योम (*configure_stream)(काष्ठा csid_device *csid, u8 enable);

	/*
	 * configure_testgen_pattern - Validates and configures output pattern mode
	 * of test pattern generator
	 * @csid: CSID device
	 */
	पूर्णांक (*configure_testgen_pattern)(काष्ठा csid_device *csid, s32 val);

	/*
	 * hw_version - Read hardware version रेजिस्टर from hardware
	 * @csid: CSID device
	 */
	u32 (*hw_version)(काष्ठा csid_device *csid);

	/*
	 * isr - CSID module पूर्णांकerrupt service routine
	 * @irq: Interrupt line
	 * @dev: CSID device
	 *
	 * Return IRQ_HANDLED on success
	 */
	irqवापस_t (*isr)(पूर्णांक irq, व्योम *dev);

	/*
	 * reset - Trigger reset on CSID module and रुको to complete
	 * @csid: CSID device
	 *
	 * Return 0 on success or a negative error code otherwise
	 */
	पूर्णांक (*reset)(काष्ठा csid_device *csid);

	/*
	 * src_pad_code - Pick an output/src क्रमmat based on the input/sink क्रमmat
	 * @csid: CSID device
	 * @sink_code: The sink क्रमmat of the input
	 * @match_क्रमmat_idx: Request preferred index, as defined by subdevice csid_क्रमmat.
	 *	Set @match_code to 0 अगर used.
	 * @match_code: Request preferred code, set @match_क्रमmat_idx to 0 अगर used
	 *
	 * Return 0 on failure or src क्रमmat code otherwise
	 */
	u32 (*src_pad_code)(काष्ठा csid_device *csid, u32 sink_code,
			    अचिन्हित पूर्णांक match_क्रमmat_idx, u32 match_code);

	/*
	 * subdev_init - Initialize CSID device according क्रम hardware revision
	 * @csid: CSID device
	 */
	व्योम (*subdev_init)(काष्ठा csid_device *csid);
पूर्ण;

काष्ठा csid_device अणु
	काष्ठा camss *camss;
	u8 id;
	काष्ठा v4l2_subdev subdev;
	काष्ठा media_pad pads[MSM_CSID_PADS_NUM];
	व्योम __iomem *base;
	u32 irq;
	अक्षर irq_name[30];
	काष्ठा camss_घड़ी *घड़ी;
	पूर्णांक nघड़ीs;
	काष्ठा regulator *vdda;
	काष्ठा completion reset_complete;
	काष्ठा csid_testgen_config testgen;
	काष्ठा csid_phy_config phy;
	काष्ठा v4l2_mbus_framefmt fmt[MSM_CSID_PADS_NUM];
	काष्ठा v4l2_ctrl_handler ctrls;
	काष्ठा v4l2_ctrl *testgen_mode;
	स्थिर काष्ठा csid_क्रमmat *क्रमmats;
	अचिन्हित पूर्णांक nक्रमmats;
	स्थिर काष्ठा csid_hw_ops *ops;
पूर्ण;

काष्ठा resources;

/*
 * csid_find_code - Find a क्रमmat code in an array using array index or क्रमmat code
 * @codes: Array of क्रमmat codes
 * @ncodes: Length of @code array
 * @req_क्रमmat_idx: Request preferred index, as defined by subdevice csid_क्रमmat.
 *	Set @match_code to 0 अगर used.
 * @match_code: Request preferred code, set @req_क्रमmat_idx to 0 अगर used
 *
 * Return 0 on failure or क्रमmat code otherwise
 */
u32 csid_find_code(u32 *codes, अचिन्हित पूर्णांक ncode,
		   अचिन्हित पूर्णांक match_क्रमmat_idx, u32 match_code);

/*
 * csid_get_fmt_entry - Find csid_क्रमmat entry with matching क्रमmat code
 * @क्रमmats: Array of क्रमmat csid_क्रमmat entries
 * @nक्रमmats: Length of @nक्रमmats array
 * @code: Desired क्रमmat code
 *
 * Return क्रमmats[0] on failure to find code
 */
स्थिर काष्ठा csid_क्रमmat *csid_get_fmt_entry(स्थिर काष्ठा csid_क्रमmat *क्रमmats,
					     अचिन्हित पूर्णांक nक्रमmats,
					     u32 code);

पूर्णांक msm_csid_subdev_init(काष्ठा camss *camss, काष्ठा csid_device *csid,
			 स्थिर काष्ठा resources *res, u8 id);

पूर्णांक msm_csid_रेजिस्टर_entity(काष्ठा csid_device *csid,
			     काष्ठा v4l2_device *v4l2_dev);

व्योम msm_csid_unरेजिस्टर_entity(काष्ठा csid_device *csid);

व्योम msm_csid_get_csid_id(काष्ठा media_entity *entity, u8 *id);

बाह्य स्थिर अक्षर * स्थिर csid_testgen_modes[];

बाह्य स्थिर काष्ठा csid_hw_ops csid_ops_4_1;
बाह्य स्थिर काष्ठा csid_hw_ops csid_ops_4_7;
बाह्य स्थिर काष्ठा csid_hw_ops csid_ops_170;


#पूर्ण_अगर /* QC_MSM_CAMSS_CSID_H */
