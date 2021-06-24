<शैली गुरु>
/*
 * Copyright 2014 Advanced Micro Devices, Inc.
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

#अगर_अघोषित __AMDGPU_ATOMFIRMWARE_H__
#घोषणा __AMDGPU_ATOMFIRMWARE_H__

#घोषणा get_index_पूर्णांकo_master_table(master_table, table_name) (दुरत्व(काष्ठा master_table, table_name) / माप(uपूर्णांक16_t))

bool amdgpu_atomfirmware_gpu_supports_भवization(काष्ठा amdgpu_device *adev);
व्योम amdgpu_atomfirmware_scratch_regs_init(काष्ठा amdgpu_device *adev);
पूर्णांक amdgpu_atomfirmware_allocate_fb_scratch(काष्ठा amdgpu_device *adev);
पूर्णांक amdgpu_atomfirmware_get_vram_info(काष्ठा amdgpu_device *adev,
	पूर्णांक *vram_width, पूर्णांक *vram_type, पूर्णांक *vram_venकरोr);
पूर्णांक amdgpu_atomfirmware_get_घड़ी_info(काष्ठा amdgpu_device *adev);
पूर्णांक amdgpu_atomfirmware_get_gfx_info(काष्ठा amdgpu_device *adev);
bool amdgpu_atomfirmware_mem_ecc_supported(काष्ठा amdgpu_device *adev);
bool amdgpu_atomfirmware_sram_ecc_supported(काष्ठा amdgpu_device *adev);
पूर्णांक amdgpu_atomfirmware_get_fw_reserved_fb_size(काष्ठा amdgpu_device *adev);
पूर्णांक amdgpu_mem_train_support(काष्ठा amdgpu_device *adev);

#पूर्ण_अगर
