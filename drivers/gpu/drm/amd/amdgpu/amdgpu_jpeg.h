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

#अगर_अघोषित __AMDGPU_JPEG_H__
#घोषणा __AMDGPU_JPEG_H__

#घोषणा AMDGPU_MAX_JPEG_INSTANCES	2

#घोषणा AMDGPU_JPEG_HARVEST_JPEG0 (1 << 0)
#घोषणा AMDGPU_JPEG_HARVEST_JPEG1 (1 << 1)

काष्ठा amdgpu_jpeg_regअणु
	अचिन्हित jpeg_pitch;
पूर्ण;

काष्ठा amdgpu_jpeg_inst अणु
	काष्ठा amdgpu_ring ring_dec;
	काष्ठा amdgpu_irq_src irq;
	काष्ठा amdgpu_jpeg_reg बाह्यal;
पूर्ण;

काष्ठा amdgpu_jpeg अणु
	uपूर्णांक8_t	num_jpeg_inst;
	काष्ठा amdgpu_jpeg_inst inst[AMDGPU_MAX_JPEG_INSTANCES];
	काष्ठा amdgpu_jpeg_reg पूर्णांकernal;
	अचिन्हित harvest_config;
	काष्ठा delayed_work idle_work;
	क्रमागत amd_घातergating_state cur_state;
	काष्ठा mutex jpeg_pg_lock;
	atomic_t total_submission_cnt;
पूर्ण;

पूर्णांक amdgpu_jpeg_sw_init(काष्ठा amdgpu_device *adev);
पूर्णांक amdgpu_jpeg_sw_fini(काष्ठा amdgpu_device *adev);
पूर्णांक amdgpu_jpeg_suspend(काष्ठा amdgpu_device *adev);
पूर्णांक amdgpu_jpeg_resume(काष्ठा amdgpu_device *adev);

व्योम amdgpu_jpeg_ring_begin_use(काष्ठा amdgpu_ring *ring);
व्योम amdgpu_jpeg_ring_end_use(काष्ठा amdgpu_ring *ring);

पूर्णांक amdgpu_jpeg_dec_ring_test_ring(काष्ठा amdgpu_ring *ring);
पूर्णांक amdgpu_jpeg_dec_ring_test_ib(काष्ठा amdgpu_ring *ring, दीर्घ समयout);

#पूर्ण_अगर /*__AMDGPU_JPEG_H__*/
