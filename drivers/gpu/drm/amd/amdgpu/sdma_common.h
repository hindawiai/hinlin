<शैली गुरु>
/*
 * Copyright 2019 Advanced Micro Devices, Inc.
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
 */

#अगर_अघोषित __SDMA_COMMON_H__
#घोषणा __SDMA_COMMON_H__

क्रमागत sdma_utcl2_cache_पढ़ो_policy अणु
	CACHE_READ_POLICY_L2__LRU    = 0x00000000,
	CACHE_READ_POLICY_L2__STREAM = 0x00000001,
	CACHE_READ_POLICY_L2__NOA    = 0x00000002,
	CACHE_READ_POLICY_L2__DEFAULT = CACHE_READ_POLICY_L2__NOA,
पूर्ण;

क्रमागत sdma_utcl2_cache_ग_लिखो_policy अणु
	CACHE_WRITE_POLICY_L2__LRU    = 0x00000000,
	CACHE_WRITE_POLICY_L2__STREAM = 0x00000001,
	CACHE_WRITE_POLICY_L2__NOA    = 0x00000002,
	CACHE_WRITE_POLICY_L2__BYPASS = 0x00000003,
	CACHE_WRITE_POLICY_L2__DEFAULT = CACHE_WRITE_POLICY_L2__BYPASS,
पूर्ण;

#पूर्ण_अगर /* __SDMA_COMMON_H__ */
