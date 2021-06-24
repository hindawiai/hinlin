<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) STMicroelectronics SA 2014
 * Authors: Fabien Dessenne <fabien.dessenne@st.com> क्रम STMicroelectronics.
 */

#समावेश <linux/delay.h>

#समावेश "bdisp.h"
#समावेश "bdisp-filter.h"
#समावेश "bdisp-reg.h"

/* Max width of the source frame in a single node */
#घोषणा MAX_SRC_WIDTH           2048

/* Reset & boot poll config */
#घोषणा POLL_RST_MAX            500
#घोषणा POLL_RST_DELAY_MS       2

क्रमागत bdisp_target_plan अणु
	BDISP_RGB,
	BDISP_Y,
	BDISP_CBCR
पूर्ण;

काष्ठा bdisp_op_cfg अणु
	bool cconv;          /* RGB - YUV conversion */
	bool hflip;          /* Horizontal flip */
	bool vflip;          /* Vertical flip */
	bool wide;           /* Wide (>MAX_SRC_WIDTH) */
	bool scale;          /* Scale */
	u16  h_inc;          /* Horizontal increment in 6.10 क्रमmat */
	u16  v_inc;          /* Vertical increment in 6.10 क्रमmat */
	bool src_पूर्णांकerlaced; /* is the src an पूर्णांकerlaced buffer */
	u8   src_nbp;        /* nb of planes of the src */
	bool src_yuv;        /* is the src a YUV color क्रमmat */
	bool src_420;        /* is the src 4:2:0 chroma subsampled */
	u8   dst_nbp;        /* nb of planes of the dst */
	bool dst_yuv;        /* is the dst a YUV color क्रमmat */
	bool dst_420;        /* is the dst 4:2:0 chroma subsampled */
पूर्ण;

काष्ठा bdisp_filter_addr अणु
	u16 min;             /* Filter min scale factor (6.10 fixed poपूर्णांक) */
	u16 max;             /* Filter max scale factor (6.10 fixed poपूर्णांक) */
	व्योम *virt;          /* Virtual address क्रम filter table */
	dma_addr_t paddr;    /* Physical address क्रम filter table */
पूर्ण;

अटल स्थिर काष्ठा bdisp_filter_h_spec bdisp_h_spec[] = अणु
	अणु
		.min = 0,
		.max = 921,
		.coef = अणु
			0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00,
			0x00, 0x00, 0xff, 0x07, 0x3d, 0xfc, 0x01, 0x00,
			0x00, 0x01, 0xfd, 0x11, 0x36, 0xf9, 0x02, 0x00,
			0x00, 0x01, 0xfb, 0x1b, 0x2e, 0xf9, 0x02, 0x00,
			0x00, 0x01, 0xf9, 0x26, 0x26, 0xf9, 0x01, 0x00,
			0x00, 0x02, 0xf9, 0x30, 0x19, 0xfb, 0x01, 0x00,
			0x00, 0x02, 0xf9, 0x39, 0x0e, 0xfd, 0x01, 0x00,
			0x00, 0x01, 0xfc, 0x3e, 0x06, 0xff, 0x00, 0x00
		पूर्ण
	पूर्ण,
	अणु
		.min = 921,
		.max = 1024,
		.coef = अणु
			0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00,
			0xff, 0x03, 0xfd, 0x08, 0x3e, 0xf9, 0x04, 0xfe,
			0xfd, 0x06, 0xf8, 0x13, 0x3b, 0xf4, 0x07, 0xfc,
			0xfb, 0x08, 0xf5, 0x1f, 0x34, 0xf1, 0x09, 0xfb,
			0xfb, 0x09, 0xf2, 0x2b, 0x2a, 0xf1, 0x09, 0xfb,
			0xfb, 0x09, 0xf2, 0x35, 0x1e, 0xf4, 0x08, 0xfb,
			0xfc, 0x07, 0xf5, 0x3c, 0x12, 0xf7, 0x06, 0xfd,
			0xfe, 0x04, 0xfa, 0x3f, 0x07, 0xfc, 0x03, 0xff
		पूर्ण
	पूर्ण,
	अणु
		.min = 1024,
		.max = 1126,
		.coef = अणु
			0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00,
			0xff, 0x03, 0xfd, 0x08, 0x3e, 0xf9, 0x04, 0xfe,
			0xfd, 0x06, 0xf8, 0x13, 0x3b, 0xf4, 0x07, 0xfc,
			0xfb, 0x08, 0xf5, 0x1f, 0x34, 0xf1, 0x09, 0xfb,
			0xfb, 0x09, 0xf2, 0x2b, 0x2a, 0xf1, 0x09, 0xfb,
			0xfb, 0x09, 0xf2, 0x35, 0x1e, 0xf4, 0x08, 0xfb,
			0xfc, 0x07, 0xf5, 0x3c, 0x12, 0xf7, 0x06, 0xfd,
			0xfe, 0x04, 0xfa, 0x3f, 0x07, 0xfc, 0x03, 0xff
		पूर्ण
	पूर्ण,
	अणु
		.min = 1126,
		.max = 1228,
		.coef = अणु
			0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00,
			0xff, 0x03, 0xfd, 0x08, 0x3e, 0xf9, 0x04, 0xfe,
			0xfd, 0x06, 0xf8, 0x13, 0x3b, 0xf4, 0x07, 0xfc,
			0xfb, 0x08, 0xf5, 0x1f, 0x34, 0xf1, 0x09, 0xfb,
			0xfb, 0x09, 0xf2, 0x2b, 0x2a, 0xf1, 0x09, 0xfb,
			0xfb, 0x09, 0xf2, 0x35, 0x1e, 0xf4, 0x08, 0xfb,
			0xfc, 0x07, 0xf5, 0x3c, 0x12, 0xf7, 0x06, 0xfd,
			0xfe, 0x04, 0xfa, 0x3f, 0x07, 0xfc, 0x03, 0xff
		पूर्ण
	पूर्ण,
	अणु
		.min = 1228,
		.max = 1331,
		.coef = अणु
			0xfd, 0x04, 0xfc, 0x05, 0x39, 0x05, 0xfc, 0x04,
			0xfc, 0x06, 0xf9, 0x0c, 0x39, 0xfe, 0x00, 0x02,
			0xfb, 0x08, 0xf6, 0x17, 0x35, 0xf9, 0x02, 0x00,
			0xfc, 0x08, 0xf4, 0x20, 0x30, 0xf4, 0x05, 0xff,
			0xfd, 0x07, 0xf4, 0x29, 0x28, 0xf3, 0x07, 0xfd,
			0xff, 0x05, 0xf5, 0x31, 0x1f, 0xf3, 0x08, 0xfc,
			0x00, 0x02, 0xf9, 0x38, 0x14, 0xf6, 0x08, 0xfb,
			0x02, 0x00, 0xff, 0x3a, 0x0b, 0xf8, 0x06, 0xfc
		पूर्ण
	पूर्ण,
	अणु
		.min = 1331,
		.max = 1433,
		.coef = अणु
			0xfc, 0x06, 0xf9, 0x09, 0x34, 0x09, 0xf9, 0x06,
			0xfd, 0x07, 0xf7, 0x10, 0x32, 0x02, 0xfc, 0x05,
			0xfe, 0x07, 0xf6, 0x17, 0x2f, 0xfc, 0xff, 0x04,
			0xff, 0x06, 0xf5, 0x20, 0x2a, 0xf9, 0x01, 0x02,
			0x00, 0x04, 0xf6, 0x27, 0x25, 0xf6, 0x04, 0x00,
			0x02, 0x01, 0xf9, 0x2d, 0x1d, 0xf5, 0x06, 0xff,
			0x04, 0xff, 0xfd, 0x31, 0x15, 0xf5, 0x07, 0xfe,
			0x05, 0xfc, 0x02, 0x35, 0x0d, 0xf7, 0x07, 0xfd
		पूर्ण
	पूर्ण,
	अणु
		.min = 1433,
		.max = 1536,
		.coef = अणु
			0xfe, 0x06, 0xf8, 0x0b, 0x30, 0x0b, 0xf8, 0x06,
			0xff, 0x06, 0xf7, 0x12, 0x2d, 0x05, 0xfa, 0x06,
			0x00, 0x04, 0xf6, 0x18, 0x2c, 0x00, 0xfc, 0x06,
			0x01, 0x02, 0xf7, 0x1f, 0x27, 0xfd, 0xff, 0x04,
			0x03, 0x00, 0xf9, 0x24, 0x24, 0xf9, 0x00, 0x03,
			0x04, 0xff, 0xfd, 0x29, 0x1d, 0xf7, 0x02, 0x01,
			0x06, 0xfc, 0x00, 0x2d, 0x17, 0xf6, 0x04, 0x00,
			0x06, 0xfa, 0x05, 0x30, 0x0f, 0xf7, 0x06, 0xff
		पूर्ण
	पूर्ण,
	अणु
		.min = 1536,
		.max = 2048,
		.coef = अणु
			0x05, 0xfd, 0xfb, 0x13, 0x25, 0x13, 0xfb, 0xfd,
			0x05, 0xfc, 0xfd, 0x17, 0x24, 0x0f, 0xf9, 0xff,
			0x04, 0xfa, 0xff, 0x1b, 0x24, 0x0b, 0xf9, 0x00,
			0x03, 0xf9, 0x01, 0x1f, 0x23, 0x08, 0xf8, 0x01,
			0x02, 0xf9, 0x04, 0x22, 0x20, 0x04, 0xf9, 0x02,
			0x01, 0xf8, 0x08, 0x25, 0x1d, 0x01, 0xf9, 0x03,
			0x00, 0xf9, 0x0c, 0x25, 0x1a, 0xfe, 0xfa, 0x04,
			0xff, 0xf9, 0x10, 0x26, 0x15, 0xfc, 0xfc, 0x05
		पूर्ण
	पूर्ण,
	अणु
		.min = 2048,
		.max = 3072,
		.coef = अणु
			0xfc, 0xfd, 0x06, 0x13, 0x18, 0x13, 0x06, 0xfd,
			0xfc, 0xfe, 0x08, 0x15, 0x17, 0x12, 0x04, 0xfc,
			0xfb, 0xfe, 0x0a, 0x16, 0x18, 0x10, 0x03, 0xfc,
			0xfb, 0x00, 0x0b, 0x18, 0x17, 0x0f, 0x01, 0xfb,
			0xfb, 0x00, 0x0d, 0x19, 0x17, 0x0d, 0x00, 0xfb,
			0xfb, 0x01, 0x0f, 0x19, 0x16, 0x0b, 0x00, 0xfb,
			0xfc, 0x03, 0x11, 0x19, 0x15, 0x09, 0xfe, 0xfb,
			0xfc, 0x04, 0x12, 0x1a, 0x12, 0x08, 0xfe, 0xfc
		पूर्ण
	पूर्ण,
	अणु
		.min = 3072,
		.max = 4096,
		.coef = अणु
			0xfe, 0x02, 0x09, 0x0f, 0x0e, 0x0f, 0x09, 0x02,
			0xff, 0x02, 0x09, 0x0f, 0x10, 0x0e, 0x08, 0x01,
			0xff, 0x03, 0x0a, 0x10, 0x10, 0x0d, 0x07, 0x00,
			0x00, 0x04, 0x0b, 0x10, 0x0f, 0x0c, 0x06, 0x00,
			0x00, 0x05, 0x0c, 0x10, 0x0e, 0x0c, 0x05, 0x00,
			0x00, 0x06, 0x0c, 0x11, 0x0e, 0x0b, 0x04, 0x00,
			0x00, 0x07, 0x0d, 0x11, 0x0f, 0x0a, 0x03, 0xff,
			0x01, 0x08, 0x0e, 0x11, 0x0e, 0x09, 0x02, 0xff
		पूर्ण
	पूर्ण,
	अणु
		.min = 4096,
		.max = 5120,
		.coef = अणु
			0x00, 0x04, 0x09, 0x0c, 0x0e, 0x0c, 0x09, 0x04,
			0x01, 0x05, 0x09, 0x0c, 0x0d, 0x0c, 0x08, 0x04,
			0x01, 0x05, 0x0a, 0x0c, 0x0e, 0x0b, 0x08, 0x03,
			0x02, 0x06, 0x0a, 0x0d, 0x0c, 0x0b, 0x07, 0x03,
			0x02, 0x07, 0x0a, 0x0d, 0x0d, 0x0a, 0x07, 0x02,
			0x03, 0x07, 0x0b, 0x0d, 0x0c, 0x0a, 0x06, 0x02,
			0x03, 0x08, 0x0b, 0x0d, 0x0d, 0x0a, 0x05, 0x01,
			0x04, 0x08, 0x0c, 0x0d, 0x0c, 0x09, 0x05, 0x01
		पूर्ण
	पूर्ण,
	अणु
		.min = 5120,
		.max = 65535,
		.coef = अणु
			0x03, 0x06, 0x09, 0x0b, 0x09, 0x0b, 0x09, 0x06,
			0x03, 0x06, 0x09, 0x0b, 0x0c, 0x0a, 0x08, 0x05,
			0x03, 0x06, 0x09, 0x0b, 0x0c, 0x0a, 0x08, 0x05,
			0x04, 0x07, 0x09, 0x0b, 0x0b, 0x0a, 0x08, 0x04,
			0x04, 0x07, 0x0a, 0x0b, 0x0b, 0x0a, 0x07, 0x04,
			0x04, 0x08, 0x0a, 0x0b, 0x0b, 0x09, 0x07, 0x04,
			0x05, 0x08, 0x0a, 0x0b, 0x0c, 0x09, 0x06, 0x03,
			0x05, 0x08, 0x0a, 0x0b, 0x0c, 0x09, 0x06, 0x03
		पूर्ण
	पूर्ण
पूर्ण;

#घोषणा NB_H_FILTER ARRAY_SIZE(bdisp_h_spec)


अटल स्थिर काष्ठा bdisp_filter_v_spec bdisp_v_spec[] = अणु
	अणु
		.min = 0,
		.max = 1024,
		.coef = अणु
			0x00, 0x00, 0x40, 0x00, 0x00,
			0x00, 0x06, 0x3d, 0xfd, 0x00,
			0xfe, 0x0f, 0x38, 0xfb, 0x00,
			0xfd, 0x19, 0x2f, 0xfb, 0x00,
			0xfc, 0x24, 0x24, 0xfc, 0x00,
			0xfb, 0x2f, 0x19, 0xfd, 0x00,
			0xfb, 0x38, 0x0f, 0xfe, 0x00,
			0xfd, 0x3d, 0x06, 0x00, 0x00
		पूर्ण
	पूर्ण,
	अणु
		.min = 1024,
		.max = 1331,
		.coef = अणु
			0xfc, 0x05, 0x3e, 0x05, 0xfc,
			0xf8, 0x0e, 0x3b, 0xff, 0x00,
			0xf5, 0x18, 0x38, 0xf9, 0x02,
			0xf4, 0x21, 0x31, 0xf5, 0x05,
			0xf4, 0x2a, 0x27, 0xf4, 0x07,
			0xf6, 0x30, 0x1e, 0xf4, 0x08,
			0xf9, 0x35, 0x15, 0xf6, 0x07,
			0xff, 0x37, 0x0b, 0xf9, 0x06
		पूर्ण
	पूर्ण,
	अणु
		.min = 1331,
		.max = 1433,
		.coef = अणु
			0xf8, 0x0a, 0x3c, 0x0a, 0xf8,
			0xf6, 0x12, 0x3b, 0x02, 0xfb,
			0xf4, 0x1b, 0x35, 0xfd, 0xff,
			0xf4, 0x23, 0x30, 0xf8, 0x01,
			0xf6, 0x29, 0x27, 0xf6, 0x04,
			0xf9, 0x2e, 0x1e, 0xf5, 0x06,
			0xfd, 0x31, 0x16, 0xf6, 0x06,
			0x02, 0x32, 0x0d, 0xf8, 0x07
		पूर्ण
	पूर्ण,
	अणु
		.min = 1433,
		.max = 1536,
		.coef = अणु
			0xf6, 0x0e, 0x38, 0x0e, 0xf6,
			0xf5, 0x15, 0x38, 0x06, 0xf8,
			0xf5, 0x1d, 0x33, 0x00, 0xfb,
			0xf6, 0x23, 0x2d, 0xfc, 0xfe,
			0xf9, 0x28, 0x26, 0xf9, 0x00,
			0xfc, 0x2c, 0x1e, 0xf7, 0x03,
			0x00, 0x2e, 0x18, 0xf6, 0x04,
			0x05, 0x2e, 0x11, 0xf7, 0x05
		पूर्ण
	पूर्ण,
	अणु
		.min = 1536,
		.max = 2048,
		.coef = अणु
			0xfb, 0x13, 0x24, 0x13, 0xfb,
			0xfd, 0x17, 0x23, 0x0f, 0xfa,
			0xff, 0x1a, 0x23, 0x0b, 0xf9,
			0x01, 0x1d, 0x22, 0x07, 0xf9,
			0x04, 0x20, 0x1f, 0x04, 0xf9,
			0x07, 0x22, 0x1c, 0x01, 0xfa,
			0x0b, 0x24, 0x17, 0xff, 0xfb,
			0x0f, 0x24, 0x14, 0xfd, 0xfc
		पूर्ण
	पूर्ण,
	अणु
		.min = 2048,
		.max = 3072,
		.coef = अणु
			0x05, 0x10, 0x16, 0x10, 0x05,
			0x06, 0x11, 0x16, 0x0f, 0x04,
			0x08, 0x13, 0x15, 0x0e, 0x02,
			0x09, 0x14, 0x16, 0x0c, 0x01,
			0x0b, 0x15, 0x15, 0x0b, 0x00,
			0x0d, 0x16, 0x13, 0x0a, 0x00,
			0x0f, 0x17, 0x13, 0x08, 0xff,
			0x11, 0x18, 0x12, 0x07, 0xfe
		पूर्ण
	पूर्ण,
	अणु
		.min = 3072,
		.max = 4096,
		.coef = अणु
			0x09, 0x0f, 0x10, 0x0f, 0x09,
			0x09, 0x0f, 0x12, 0x0e, 0x08,
			0x0a, 0x10, 0x11, 0x0e, 0x07,
			0x0b, 0x11, 0x11, 0x0d, 0x06,
			0x0c, 0x11, 0x12, 0x0c, 0x05,
			0x0d, 0x12, 0x11, 0x0c, 0x04,
			0x0e, 0x12, 0x11, 0x0b, 0x04,
			0x0f, 0x13, 0x11, 0x0a, 0x03
		पूर्ण
	पूर्ण,
	अणु
		.min = 4096,
		.max = 5120,
		.coef = अणु
			0x0a, 0x0e, 0x10, 0x0e, 0x0a,
			0x0b, 0x0e, 0x0f, 0x0e, 0x0a,
			0x0b, 0x0f, 0x10, 0x0d, 0x09,
			0x0c, 0x0f, 0x10, 0x0d, 0x08,
			0x0d, 0x0f, 0x0f, 0x0d, 0x08,
			0x0d, 0x10, 0x10, 0x0c, 0x07,
			0x0e, 0x10, 0x0f, 0x0c, 0x07,
			0x0f, 0x10, 0x10, 0x0b, 0x06
		पूर्ण
	पूर्ण,
	अणु
		.min = 5120,
		.max = 65535,
		.coef = अणु
			0x0b, 0x0e, 0x0e, 0x0e, 0x0b,
			0x0b, 0x0e, 0x0f, 0x0d, 0x0b,
			0x0c, 0x0e, 0x0f, 0x0d, 0x0a,
			0x0c, 0x0e, 0x0f, 0x0d, 0x0a,
			0x0d, 0x0f, 0x0e, 0x0d, 0x09,
			0x0d, 0x0f, 0x0f, 0x0c, 0x09,
			0x0e, 0x0f, 0x0e, 0x0c, 0x09,
			0x0e, 0x0f, 0x0f, 0x0c, 0x08
		पूर्ण
	पूर्ण
पूर्ण;

#घोषणा NB_V_FILTER ARRAY_SIZE(bdisp_v_spec)

अटल काष्ठा bdisp_filter_addr bdisp_h_filter[NB_H_FILTER];
अटल काष्ठा bdisp_filter_addr bdisp_v_filter[NB_V_FILTER];

/**
 * bdisp_hw_reset
 * @bdisp:      bdisp entity
 *
 * Resets HW
 *
 * RETURNS:
 * 0 on success.
 */
पूर्णांक bdisp_hw_reset(काष्ठा bdisp_dev *bdisp)
अणु
	अचिन्हित पूर्णांक i;

	dev_dbg(bdisp->dev, "%s\n", __func__);

	/* Mask Interrupt */
	ग_लिखोl(0, bdisp->regs + BLT_ITM0);

	/* Reset */
	ग_लिखोl(पढ़ोl(bdisp->regs + BLT_CTL) | BLT_CTL_RESET,
	       bdisp->regs + BLT_CTL);
	ग_लिखोl(0, bdisp->regs + BLT_CTL);

	/* Wait क्रम reset करोne */
	क्रम (i = 0; i < POLL_RST_MAX; i++) अणु
		अगर (पढ़ोl(bdisp->regs + BLT_STA1) & BLT_STA1_IDLE)
			अवरोध;
		udelay(POLL_RST_DELAY_MS * 1000);
	पूर्ण
	अगर (i == POLL_RST_MAX)
		dev_err(bdisp->dev, "Reset timeout\n");

	वापस (i == POLL_RST_MAX) ? -EAGAIN : 0;
पूर्ण

/**
 * bdisp_hw_get_and_clear_irq
 * @bdisp:      bdisp entity
 *
 * Read then reset पूर्णांकerrupt status
 *
 * RETURNS:
 * 0 अगर expected पूर्णांकerrupt was उठाओd.
 */
पूर्णांक bdisp_hw_get_and_clear_irq(काष्ठा bdisp_dev *bdisp)
अणु
	u32 its;

	its = पढ़ोl(bdisp->regs + BLT_ITS);

	/* Check क्रम the only expected IT: LastNode of AQ1 */
	अगर (!(its & BLT_ITS_AQ1_LNA)) अणु
		dev_dbg(bdisp->dev, "Unexpected IT status: 0x%08X\n", its);
		ग_लिखोl(its, bdisp->regs + BLT_ITS);
		वापस -1;
	पूर्ण

	/* Clear and mask */
	ग_लिखोl(its, bdisp->regs + BLT_ITS);
	ग_लिखोl(0, bdisp->regs + BLT_ITM0);

	वापस 0;
पूर्ण

/**
 * bdisp_hw_मुक्त_nodes
 * @ctx:        bdisp context
 *
 * Free node memory
 *
 * RETURNS:
 * None
 */
व्योम bdisp_hw_मुक्त_nodes(काष्ठा bdisp_ctx *ctx)
अणु
	अगर (ctx && ctx->node[0])
		dma_मुक्त_attrs(ctx->bdisp_dev->dev,
			       माप(काष्ठा bdisp_node) * MAX_NB_NODE,
			       ctx->node[0], ctx->node_paddr[0],
			       DMA_ATTR_WRITE_COMBINE);
पूर्ण

/**
 * bdisp_hw_alloc_nodes
 * @ctx:        bdisp context
 *
 * Allocate dma memory क्रम nodes
 *
 * RETURNS:
 * 0 on success
 */
पूर्णांक bdisp_hw_alloc_nodes(काष्ठा bdisp_ctx *ctx)
अणु
	काष्ठा device *dev = ctx->bdisp_dev->dev;
	अचिन्हित पूर्णांक i, node_size = माप(काष्ठा bdisp_node);
	व्योम *base;
	dma_addr_t paddr;

	/* Allocate all the nodes within a single memory page */
	base = dma_alloc_attrs(dev, node_size * MAX_NB_NODE, &paddr,
			       GFP_KERNEL, DMA_ATTR_WRITE_COMBINE);
	अगर (!base) अणु
		dev_err(dev, "%s no mem\n", __func__);
		वापस -ENOMEM;
	पूर्ण

	स_रखो(base, 0, node_size * MAX_NB_NODE);

	क्रम (i = 0; i < MAX_NB_NODE; i++) अणु
		ctx->node[i] = base;
		ctx->node_paddr[i] = paddr;
		dev_dbg(dev, "node[%d]=0x%p (paddr=%pad)\n", i, ctx->node[i],
			&paddr);
		base += node_size;
		paddr += node_size;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * bdisp_hw_मुक्त_filters
 * @dev:        device
 *
 * Free filters memory
 *
 * RETURNS:
 * None
 */
व्योम bdisp_hw_मुक्त_filters(काष्ठा device *dev)
अणु
	पूर्णांक size = (BDISP_HF_NB * NB_H_FILTER) + (BDISP_VF_NB * NB_V_FILTER);

	अगर (bdisp_h_filter[0].virt)
		dma_मुक्त_attrs(dev, size, bdisp_h_filter[0].virt,
			       bdisp_h_filter[0].paddr, DMA_ATTR_WRITE_COMBINE);
पूर्ण

/**
 * bdisp_hw_alloc_filters
 * @dev:        device
 *
 * Allocate dma memory क्रम filters
 *
 * RETURNS:
 * 0 on success
 */
पूर्णांक bdisp_hw_alloc_filters(काष्ठा device *dev)
अणु
	अचिन्हित पूर्णांक i, size;
	व्योम *base;
	dma_addr_t paddr;

	/* Allocate all the filters within a single memory page */
	size = (BDISP_HF_NB * NB_H_FILTER) + (BDISP_VF_NB * NB_V_FILTER);
	base = dma_alloc_attrs(dev, size, &paddr, GFP_KERNEL,
			       DMA_ATTR_WRITE_COMBINE);
	अगर (!base)
		वापस -ENOMEM;

	/* Setup filter addresses */
	क्रम (i = 0; i < NB_H_FILTER; i++) अणु
		bdisp_h_filter[i].min = bdisp_h_spec[i].min;
		bdisp_h_filter[i].max = bdisp_h_spec[i].max;
		स_नकल(base, bdisp_h_spec[i].coef, BDISP_HF_NB);
		bdisp_h_filter[i].virt = base;
		bdisp_h_filter[i].paddr = paddr;
		base += BDISP_HF_NB;
		paddr += BDISP_HF_NB;
	पूर्ण

	क्रम (i = 0; i < NB_V_FILTER; i++) अणु
		bdisp_v_filter[i].min = bdisp_v_spec[i].min;
		bdisp_v_filter[i].max = bdisp_v_spec[i].max;
		स_नकल(base, bdisp_v_spec[i].coef, BDISP_VF_NB);
		bdisp_v_filter[i].virt = base;
		bdisp_v_filter[i].paddr = paddr;
		base += BDISP_VF_NB;
		paddr += BDISP_VF_NB;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * bdisp_hw_get_hf_addr
 * @inc:        resize increment
 *
 * Find the horizontal filter table that fits the resize increment
 *
 * RETURNS:
 * table physical address
 */
अटल dma_addr_t bdisp_hw_get_hf_addr(u16 inc)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = NB_H_FILTER - 1; i > 0; i--)
		अगर ((bdisp_h_filter[i].min < inc) &&
		    (inc <= bdisp_h_filter[i].max))
			अवरोध;

	वापस bdisp_h_filter[i].paddr;
पूर्ण

/**
 * bdisp_hw_get_vf_addr
 * @inc:        resize increment
 *
 * Find the vertical filter table that fits the resize increment
 *
 * RETURNS:
 * table physical address
 */
अटल dma_addr_t bdisp_hw_get_vf_addr(u16 inc)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = NB_V_FILTER - 1; i > 0; i--)
		अगर ((bdisp_v_filter[i].min < inc) &&
		    (inc <= bdisp_v_filter[i].max))
			अवरोध;

	वापस bdisp_v_filter[i].paddr;
पूर्ण

/**
 * bdisp_hw_get_inc
 * @from:       input size
 * @to:         output size
 * @inc:        resize increment in 6.10 क्रमmat
 *
 * Computes the increment (inverse of scale) in 6.10 क्रमmat
 *
 * RETURNS:
 * 0 on success
 */
अटल पूर्णांक bdisp_hw_get_inc(u32 from, u32 to, u16 *inc)
अणु
	u32 पंचांगp;

	अगर (!to)
		वापस -EINVAL;

	अगर (to == from) अणु
		*inc = 1 << 10;
		वापस 0;
	पूर्ण

	पंचांगp = (from << 10) / to;
	अगर ((पंचांगp > 0xFFFF) || (!पंचांगp))
		/* overflow (करोwnscale x 63) or too small (upscale x 1024) */
		वापस -EINVAL;

	*inc = (u16)पंचांगp;

	वापस 0;
पूर्ण

/**
 * bdisp_hw_get_hv_inc
 * @ctx:        device context
 * @h_inc:      horizontal increment
 * @v_inc:      vertical increment
 *
 * Computes the horizontal & vertical increments (inverse of scale)
 *
 * RETURNS:
 * 0 on success
 */
अटल पूर्णांक bdisp_hw_get_hv_inc(काष्ठा bdisp_ctx *ctx, u16 *h_inc, u16 *v_inc)
अणु
	u32 src_w, src_h, dst_w, dst_h;

	src_w = ctx->src.crop.width;
	src_h = ctx->src.crop.height;
	dst_w = ctx->dst.crop.width;
	dst_h = ctx->dst.crop.height;

	अगर (bdisp_hw_get_inc(src_w, dst_w, h_inc) ||
	    bdisp_hw_get_inc(src_h, dst_h, v_inc)) अणु
		dev_err(ctx->bdisp_dev->dev,
			"scale factors failed (%dx%d)->(%dx%d)\n",
			src_w, src_h, dst_w, dst_h);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * bdisp_hw_get_op_cfg
 * @ctx:        device context
 * @c:          operation configuration
 *
 * Check which blitter operations are expected and sets the scaling increments
 *
 * RETURNS:
 * 0 on success
 */
अटल पूर्णांक bdisp_hw_get_op_cfg(काष्ठा bdisp_ctx *ctx, काष्ठा bdisp_op_cfg *c)
अणु
	काष्ठा device *dev = ctx->bdisp_dev->dev;
	काष्ठा bdisp_frame *src = &ctx->src;
	काष्ठा bdisp_frame *dst = &ctx->dst;

	अगर (src->width > MAX_SRC_WIDTH * MAX_VERTICAL_STRIDES) अणु
		dev_err(dev, "Image width out of HW caps\n");
		वापस -EINVAL;
	पूर्ण

	c->wide = src->width > MAX_SRC_WIDTH;

	c->hflip = ctx->hflip;
	c->vflip = ctx->vflip;

	c->src_पूर्णांकerlaced = (src->field == V4L2_FIELD_INTERLACED);

	c->src_nbp = src->fmt->nb_planes;
	c->src_yuv = (src->fmt->pixelक्रमmat == V4L2_PIX_FMT_NV12) ||
			(src->fmt->pixelक्रमmat == V4L2_PIX_FMT_YUV420);
	c->src_420 = c->src_yuv;

	c->dst_nbp = dst->fmt->nb_planes;
	c->dst_yuv = (dst->fmt->pixelक्रमmat == V4L2_PIX_FMT_NV12) ||
			(dst->fmt->pixelक्रमmat == V4L2_PIX_FMT_YUV420);
	c->dst_420 = c->dst_yuv;

	c->cconv = (c->src_yuv != c->dst_yuv);

	अगर (bdisp_hw_get_hv_inc(ctx, &c->h_inc, &c->v_inc)) अणु
		dev_err(dev, "Scale factor out of HW caps\n");
		वापस -EINVAL;
	पूर्ण

	/* Deपूर्णांकerlacing adjusपंचांगent : stretch a field to a frame */
	अगर (c->src_पूर्णांकerlaced)
		c->v_inc /= 2;

	अगर ((c->h_inc != (1 << 10)) || (c->v_inc != (1 << 10)))
		c->scale = true;
	अन्यथा
		c->scale = false;

	वापस 0;
पूर्ण

/**
 * bdisp_hw_color_क्रमmat
 * @pixelक्रमmat: v4l2 pixel क्रमmat
 *
 * v4l2 to bdisp pixel क्रमmat convert
 *
 * RETURNS:
 * bdisp pixel क्रमmat
 */
अटल u32 bdisp_hw_color_क्रमmat(u32 pixelक्रमmat)
अणु
	u32 ret;

	चयन (pixelक्रमmat) अणु
	हाल V4L2_PIX_FMT_YUV420:
		ret = (BDISP_YUV_3B << BLT_TTY_COL_SHIFT);
		अवरोध;
	हाल V4L2_PIX_FMT_NV12:
		ret = (BDISP_NV12 << BLT_TTY_COL_SHIFT) | BLT_TTY_BIG_END;
		अवरोध;
	हाल V4L2_PIX_FMT_RGB565:
		ret = (BDISP_RGB565 << BLT_TTY_COL_SHIFT);
		अवरोध;
	हाल V4L2_PIX_FMT_XBGR32: /* This V4L क्रमmat actually refers to xRGB */
		ret = (BDISP_XRGB8888 << BLT_TTY_COL_SHIFT);
		अवरोध;
	हाल V4L2_PIX_FMT_RGB24:  /* RGB888 क्रमmat */
		ret = (BDISP_RGB888 << BLT_TTY_COL_SHIFT) | BLT_TTY_BIG_END;
		अवरोध;
	हाल V4L2_PIX_FMT_ABGR32: /* This V4L क्रमmat actually refers to ARGB */

	शेष:
		ret = (BDISP_ARGB8888 << BLT_TTY_COL_SHIFT) | BLT_TTY_ALPHA_R;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

/**
 * bdisp_hw_build_node
 * @ctx:        device context
 * @cfg:        operation configuration
 * @node:       node to be set
 * @t_plan:     whether the node refers to a RGB/Y or a CbCr plane
 * @src_x_offset: x offset in the source image
 *
 * Build a node
 *
 * RETURNS:
 * None
 */
अटल व्योम bdisp_hw_build_node(काष्ठा bdisp_ctx *ctx,
				काष्ठा bdisp_op_cfg *cfg,
				काष्ठा bdisp_node *node,
				क्रमागत bdisp_target_plan t_plan, पूर्णांक src_x_offset)
अणु
	काष्ठा bdisp_frame *src = &ctx->src;
	काष्ठा bdisp_frame *dst = &ctx->dst;
	u16 h_inc, v_inc, yh_inc, yv_inc;
	काष्ठा v4l2_rect src_rect = src->crop;
	काष्ठा v4l2_rect dst_rect = dst->crop;
	पूर्णांक dst_x_offset;
	s32 dst_width = dst->crop.width;
	u32 src_fmt, dst_fmt;
	स्थिर u32 *ivmx;

	dev_dbg(ctx->bdisp_dev->dev, "%s\n", __func__);

	स_रखो(node, 0, माप(*node));

	/* Adjust src and dst areas wrt src_x_offset */
	src_rect.left += src_x_offset;
	src_rect.width -= src_x_offset;
	src_rect.width = min_t(__s32, MAX_SRC_WIDTH, src_rect.width);

	dst_x_offset = (src_x_offset * dst_width) / ctx->src.crop.width;
	dst_rect.left += dst_x_offset;
	dst_rect.width = (src_rect.width * dst_width) / ctx->src.crop.width;

	/* General */
	src_fmt = src->fmt->pixelक्रमmat;
	dst_fmt = dst->fmt->pixelक्रमmat;

	node->nip = 0;
	node->cic = BLT_CIC_ALL_GRP;
	node->ack = BLT_ACK_BYPASS_S2S3;

	चयन (cfg->src_nbp) अणु
	हाल 1:
		/* Src2 = RGB / Src1 = Src3 = off */
		node->ins = BLT_INS_S1_OFF | BLT_INS_S2_MEM | BLT_INS_S3_OFF;
		अवरोध;
	हाल 2:
		/* Src3 = Y
		 * Src2 = CbCr or ColorFill अगर writing the Y plane
		 * Src1 = off */
		node->ins = BLT_INS_S1_OFF | BLT_INS_S3_MEM;
		अगर (t_plan == BDISP_Y)
			node->ins |= BLT_INS_S2_CF;
		अन्यथा
			node->ins |= BLT_INS_S2_MEM;
		अवरोध;
	हाल 3:
	शेष:
		/* Src3 = Y
		 * Src2 = Cb or ColorFill अगर writing the Y plane
		 * Src1 = Cr or ColorFill अगर writing the Y plane */
		node->ins = BLT_INS_S3_MEM;
		अगर (t_plan == BDISP_Y)
			node->ins |= BLT_INS_S2_CF | BLT_INS_S1_CF;
		अन्यथा
			node->ins |= BLT_INS_S2_MEM | BLT_INS_S1_MEM;
		अवरोध;
	पूर्ण

	/* Color convert */
	node->ins |= cfg->cconv ? BLT_INS_IVMX : 0;
	/* Scale needed अगर scaling OR 4:2:0 up/करोwnsampling */
	node->ins |= (cfg->scale || cfg->src_420 || cfg->dst_420) ?
			BLT_INS_SCALE : 0;

	/* Target */
	node->tba = (t_plan == BDISP_CBCR) ? dst->paddr[1] : dst->paddr[0];

	node->tty = dst->bytesperline;
	node->tty |= bdisp_hw_color_क्रमmat(dst_fmt);
	node->tty |= BLT_TTY_DITHER;
	node->tty |= (t_plan == BDISP_CBCR) ? BLT_TTY_CHROMA : 0;
	node->tty |= cfg->hflip ? BLT_TTY_HSO : 0;
	node->tty |= cfg->vflip ? BLT_TTY_VSO : 0;

	अगर (cfg->dst_420 && (t_plan == BDISP_CBCR)) अणु
		/* 420 chroma करोwnsampling */
		dst_rect.height /= 2;
		dst_rect.width /= 2;
		dst_rect.left /= 2;
		dst_rect.top /= 2;
		dst_x_offset /= 2;
		dst_width /= 2;
	पूर्ण

	node->txy = cfg->vflip ? (dst_rect.height - 1) : dst_rect.top;
	node->txy <<= 16;
	node->txy |= cfg->hflip ? (dst_width - dst_x_offset - 1) :
			dst_rect.left;

	node->tsz = dst_rect.height << 16 | dst_rect.width;

	अगर (cfg->src_पूर्णांकerlaced) अणु
		/* handle only the top field which is half height of a frame */
		src_rect.top /= 2;
		src_rect.height /= 2;
	पूर्ण

	अगर (cfg->src_nbp == 1) अणु
		/* Src 2 : RGB */
		node->s2ba = src->paddr[0];

		node->s2ty = src->bytesperline;
		अगर (cfg->src_पूर्णांकerlaced)
			node->s2ty *= 2;

		node->s2ty |= bdisp_hw_color_क्रमmat(src_fmt);

		node->s2xy = src_rect.top << 16 | src_rect.left;
		node->s2sz = src_rect.height << 16 | src_rect.width;
	पूर्ण अन्यथा अणु
		/* Src 2 : Cb or CbCr */
		अगर (cfg->src_420) अणु
			/* 420 chroma upsampling */
			src_rect.top /= 2;
			src_rect.left /= 2;
			src_rect.width /= 2;
			src_rect.height /= 2;
		पूर्ण

		node->s2ba = src->paddr[1];

		node->s2ty = src->bytesperline;
		अगर (cfg->src_nbp == 3)
			node->s2ty /= 2;
		अगर (cfg->src_पूर्णांकerlaced)
			node->s2ty *= 2;

		node->s2ty |= bdisp_hw_color_क्रमmat(src_fmt);

		node->s2xy = src_rect.top << 16 | src_rect.left;
		node->s2sz = src_rect.height << 16 | src_rect.width;

		अगर (cfg->src_nbp == 3) अणु
			/* Src 1 : Cr */
			node->s1ba = src->paddr[2];

			node->s1ty = node->s2ty;
			node->s1xy = node->s2xy;
		पूर्ण

		/* Src 3 : Y */
		node->s3ba = src->paddr[0];

		node->s3ty = src->bytesperline;
		अगर (cfg->src_पूर्णांकerlaced)
			node->s3ty *= 2;
		node->s3ty |= bdisp_hw_color_क्रमmat(src_fmt);

		अगर ((t_plan != BDISP_CBCR) && cfg->src_420) अणु
			/* No chroma upsampling क्रम output RGB / Y plane */
			node->s3xy = node->s2xy * 2;
			node->s3sz = node->s2sz * 2;
		पूर्ण अन्यथा अणु
			/* No need to पढ़ो Y (Src3) when writing Chroma */
			node->s3ty |= BLT_S3TY_BLANK_ACC;
			node->s3xy = node->s2xy;
			node->s3sz = node->s2sz;
		पूर्ण
	पूर्ण

	/* Resize (scale OR 4:2:0: chroma up/करोwnsampling) */
	अगर (node->ins & BLT_INS_SCALE) अणु
		/* no need to compute Y when writing CbCr from RGB input */
		bool skip_y = (t_plan == BDISP_CBCR) && !cfg->src_yuv;

		/* FCTL */
		अगर (cfg->scale) अणु
			node->fctl = BLT_FCTL_HV_SCALE;
			अगर (!skip_y)
				node->fctl |= BLT_FCTL_Y_HV_SCALE;
		पूर्ण अन्यथा अणु
			node->fctl = BLT_FCTL_HV_SAMPLE;
			अगर (!skip_y)
				node->fctl |= BLT_FCTL_Y_HV_SAMPLE;
		पूर्ण

		/* RSF - Chroma may need to be up/करोwnsampled */
		h_inc = cfg->h_inc;
		v_inc = cfg->v_inc;
		अगर (!cfg->src_420 && cfg->dst_420 && (t_plan == BDISP_CBCR)) अणु
			/* RGB to 4:2:0 क्रम Chroma: करोwnsample */
			h_inc *= 2;
			v_inc *= 2;
		पूर्ण अन्यथा अगर (cfg->src_420 && !cfg->dst_420) अणु
			/* 4:2:0: to RGB: upsample*/
			h_inc /= 2;
			v_inc /= 2;
		पूर्ण
		node->rsf = v_inc << 16 | h_inc;

		/* RZI */
		node->rzi = BLT_RZI_DEFAULT;

		/* Filter table physical addr */
		node->hfp = bdisp_hw_get_hf_addr(h_inc);
		node->vfp = bdisp_hw_get_vf_addr(v_inc);

		/* Y version */
		अगर (!skip_y) अणु
			yh_inc = cfg->h_inc;
			yv_inc = cfg->v_inc;

			node->y_rsf = yv_inc << 16 | yh_inc;
			node->y_rzi = BLT_RZI_DEFAULT;
			node->y_hfp = bdisp_hw_get_hf_addr(yh_inc);
			node->y_vfp = bdisp_hw_get_vf_addr(yv_inc);
		पूर्ण
	पूर्ण

	/* Versatile matrix क्रम RGB / YUV conversion */
	अगर (cfg->cconv) अणु
		ivmx = cfg->src_yuv ? bdisp_yuv_to_rgb : bdisp_rgb_to_yuv;

		node->ivmx0 = ivmx[0];
		node->ivmx1 = ivmx[1];
		node->ivmx2 = ivmx[2];
		node->ivmx3 = ivmx[3];
	पूर्ण
पूर्ण

/**
 * bdisp_hw_build_all_nodes
 * @ctx:        device context
 *
 * Build all the nodes क्रम the blitter operation
 *
 * RETURNS:
 * 0 on success
 */
अटल पूर्णांक bdisp_hw_build_all_nodes(काष्ठा bdisp_ctx *ctx)
अणु
	काष्ठा bdisp_op_cfg cfg;
	अचिन्हित पूर्णांक i, nid = 0;
	पूर्णांक src_x_offset = 0;

	क्रम (i = 0; i < MAX_NB_NODE; i++)
		अगर (!ctx->node[i]) अणु
			dev_err(ctx->bdisp_dev->dev, "node %d is null\n", i);
			वापस -EINVAL;
		पूर्ण

	/* Get configuration (scale, flip, ...) */
	अगर (bdisp_hw_get_op_cfg(ctx, &cfg))
		वापस -EINVAL;

	/* Split source in vertical strides (HW स्थिरraपूर्णांक) */
	क्रम (i = 0; i < MAX_VERTICAL_STRIDES; i++) अणु
		/* Build RGB/Y node and link it to the previous node */
		bdisp_hw_build_node(ctx, &cfg, ctx->node[nid],
				    cfg.dst_nbp == 1 ? BDISP_RGB : BDISP_Y,
				    src_x_offset);
		अगर (nid)
			ctx->node[nid - 1]->nip = ctx->node_paddr[nid];
		nid++;

		/* Build additional Cb(Cr) node, link it to the previous one */
		अगर (cfg.dst_nbp > 1) अणु
			bdisp_hw_build_node(ctx, &cfg, ctx->node[nid],
					    BDISP_CBCR, src_x_offset);
			ctx->node[nid - 1]->nip = ctx->node_paddr[nid];
			nid++;
		पूर्ण

		/* Next stride until full width covered */
		src_x_offset += MAX_SRC_WIDTH;
		अगर (src_x_offset >= ctx->src.crop.width)
			अवरोध;
	पूर्ण

	/* Mark last node as the last */
	ctx->node[nid - 1]->nip = 0;

	वापस 0;
पूर्ण

/**
 * bdisp_hw_save_request
 * @ctx:        device context
 *
 * Save a copy of the request and of the built nodes
 *
 * RETURNS:
 * None
 */
अटल व्योम bdisp_hw_save_request(काष्ठा bdisp_ctx *ctx)
अणु
	काष्ठा bdisp_node **copy_node = ctx->bdisp_dev->dbg.copy_node;
	काष्ठा bdisp_request *request = &ctx->bdisp_dev->dbg.copy_request;
	काष्ठा bdisp_node **node = ctx->node;
	पूर्णांक i;

	/* Request copy */
	request->src = ctx->src;
	request->dst = ctx->dst;
	request->hflip = ctx->hflip;
	request->vflip = ctx->vflip;
	request->nb_req++;

	/* Nodes copy */
	क्रम (i = 0; i < MAX_NB_NODE; i++) अणु
		/* Allocate memory अगर not करोne yet */
		अगर (!copy_node[i]) अणु
			copy_node[i] = devm_kzalloc(ctx->bdisp_dev->dev,
						    माप(*copy_node[i]),
						    GFP_ATOMIC);
			अगर (!copy_node[i])
				वापस;
		पूर्ण
		*copy_node[i] = *node[i];
	पूर्ण
पूर्ण

/**
 * bdisp_hw_update
 * @ctx:        device context
 *
 * Send the request to the HW
 *
 * RETURNS:
 * 0 on success
 */
पूर्णांक bdisp_hw_update(काष्ठा bdisp_ctx *ctx)
अणु
	पूर्णांक ret;
	काष्ठा bdisp_dev *bdisp = ctx->bdisp_dev;
	काष्ठा device *dev = bdisp->dev;
	अचिन्हित पूर्णांक node_id;

	dev_dbg(dev, "%s\n", __func__);

	/* build nodes */
	ret = bdisp_hw_build_all_nodes(ctx);
	अगर (ret) अणु
		dev_err(dev, "cannot build nodes (%d)\n", ret);
		वापस ret;
	पूर्ण

	/* Save a copy of the request */
	bdisp_hw_save_request(ctx);

	/* Configure पूर्णांकerrupt to 'Last Node Reached for AQ1' */
	ग_लिखोl(BLT_AQ1_CTL_CFG, bdisp->regs + BLT_AQ1_CTL);
	ग_लिखोl(BLT_ITS_AQ1_LNA, bdisp->regs + BLT_ITM0);

	/* Write first node addr */
	ग_लिखोl(ctx->node_paddr[0], bdisp->regs + BLT_AQ1_IP);

	/* Find and ग_लिखो last node addr : this starts the HW processing */
	क्रम (node_id = 0; node_id < MAX_NB_NODE - 1; node_id++) अणु
		अगर (!ctx->node[node_id]->nip)
			अवरोध;
	पूर्ण
	ग_लिखोl(ctx->node_paddr[node_id], bdisp->regs + BLT_AQ1_LNA);

	वापस 0;
पूर्ण
