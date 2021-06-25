<शैली गुरु>
/*
 * Copyright 2015 Advanced Micro Devices, Inc.
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

#अगर_अघोषित _CORE_STATUS_H_
#घोषणा _CORE_STATUS_H_

क्रमागत dc_status अणु
	DC_OK = 1,

	DC_NO_CONTROLLER_RESOURCE = 2,
	DC_NO_STREAM_ENC_RESOURCE = 3,
	DC_NO_CLOCK_SOURCE_RESOURCE = 4,
	DC_FAIL_CONTROLLER_VALIDATE = 5,
	DC_FAIL_ENC_VALIDATE = 6,
	DC_FAIL_ATTACH_SURFACES = 7,
	DC_FAIL_DETACH_SURFACES = 8,
	DC_FAIL_SURFACE_VALIDATE = 9,
	DC_NO_DP_LINK_BANDWIDTH = 10,
	DC_EXCEED_DONGLE_CAP = 11,
	DC_SURFACE_PIXEL_FORMAT_UNSUPPORTED = 12,
	DC_FAIL_BANDWIDTH_VALIDATE = 13, /* BW and Watermark validation */
	DC_FAIL_SCALING = 14,
	DC_FAIL_DP_LINK_TRAINING = 15,
	DC_FAIL_DSC_VALIDATE = 16,
	DC_NO_DSC_RESOURCE = 17,
	DC_FAIL_UNSUPPORTED_1 = 18,
	DC_FAIL_CLK_EXCEED_MAX = 21,
	DC_FAIL_CLK_BELOW_MIN = 22, /*THIS IS MIN PER IP*/
	DC_FAIL_CLK_BELOW_CFG_REQUIRED = 23, /*THIS IS hard_min in PPLIB*/

	DC_NOT_SUPPORTED = 24,
	DC_UNSUPPORTED_VALUE = 25,

	DC_ERROR_UNEXPECTED = -1
पूर्ण;

अक्षर *dc_status_to_str(क्रमागत dc_status status);

#पूर्ण_अगर /* _CORE_STATUS_H_ */
