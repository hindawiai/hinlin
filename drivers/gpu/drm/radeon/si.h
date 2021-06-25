<शैली गुरु>
/* si.h -- Private header क्रम radeon driver -*- linux-c -*-
 *
 * Copyright 2011 Advanced Micro Devices, Inc.
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
 */

#अगर_अघोषित __SI_H__
#घोषणा __SI_H__

काष्ठा radeon_device;
काष्ठा radeon_mc;

पूर्णांक si_mc_load_microcode(काष्ठा radeon_device *rdev);
u32 si_gpu_check_soft_reset(काष्ठा radeon_device *rdev);
व्योम si_vram_gtt_location(काष्ठा radeon_device *rdev, काष्ठा radeon_mc *mc);
व्योम si_rlc_reset(काष्ठा radeon_device *rdev);
व्योम si_init_uvd_पूर्णांकernal_cg(काष्ठा radeon_device *rdev);
u32 si_get_csb_size(काष्ठा radeon_device *rdev);
व्योम si_get_csb_buffer(काष्ठा radeon_device *rdev, अस्थिर u32 *buffer);

#पूर्ण_अगर                         /* __SI_H__ */
