<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) STMicroelectronics SA 2014
 * Authors: Fabien Dessenne <fabien.dessenne@st.com> क्रम STMicroelectronics.
 */

#घोषणा BDISP_HF_NB             64
#घोषणा BDISP_VF_NB             40

/**
 * काष्ठा bdisp_filter_h_spec - Horizontal filter specअगरication
 *
 * @min:        min scale factor क्रम this filter (6.10 fixed poपूर्णांक)
 * @max:        max scale factor क्रम this filter (6.10 fixed poपूर्णांक)
 * @coef:       filter coefficients
 */
काष्ठा bdisp_filter_h_spec अणु
	स्थिर u16 min;
	स्थिर u16 max;
	स्थिर u8 coef[BDISP_HF_NB];
पूर्ण;
/**
 * काष्ठा bdisp_filter_v_spec - Vertical filter specअगरication
 *
 * @min:	min scale factor क्रम this filter (6.10 fixed poपूर्णांक)
 * @max:	max scale factor क्रम this filter (6.10 fixed poपूर्णांक)
 * @coef:	filter coefficients
 */
काष्ठा bdisp_filter_v_spec अणु
	स्थिर u16 min;
	स्थिर u16 max;
	स्थिर u8 coef[BDISP_VF_NB];
पूर्ण;

/* RGB YUV 601 standard conversion */
अटल स्थिर u32 bdisp_rgb_to_yuv[] = अणु
		0x0e1e8bee, 0x08420419, 0xfb5ed471, 0x08004080,
पूर्ण;

अटल स्थिर u32 bdisp_yuv_to_rgb[] = अणु
		0x3324a800, 0xe604ab9c, 0x0004a957, 0x32121eeb,
पूर्ण;
