<शैली गुरु>

/*
 * Copyright 2017 Advanced Micro Devices, Inc.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * Authors: AMD
 *
 */
#अगर_अघोषित __DSCC_TYPES_H__
#घोषणा __DSCC_TYPES_H__

#समावेश <drm/drm_dsc.h>

#अगर_अघोषित NUM_BUF_RANGES
#घोषणा NUM_BUF_RANGES 15
#पूर्ण_अगर

काष्ठा dsc_pps_rc_range अणु
	पूर्णांक range_min_qp;
	पूर्णांक range_max_qp;
	पूर्णांक range_bpg_offset;
पूर्ण;

काष्ठा dsc_parameters अणु
	काष्ठा drm_dsc_config pps;

	/* Additional parameters क्रम रेजिस्टर programming */
	uपूर्णांक32_t bytes_per_pixel; /* In u3.28 क्रमmat */
	uपूर्णांक32_t rc_buffer_model_size;
पूर्ण;

पूर्णांक dscc_compute_dsc_parameters(स्थिर काष्ठा drm_dsc_config *pps, काष्ठा dsc_parameters *dsc_params);

#पूर्ण_अगर

