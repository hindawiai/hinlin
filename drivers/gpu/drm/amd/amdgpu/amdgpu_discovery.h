<शैली गुरु>
/*
 * Copyright 2018 Advanced Micro Devices, Inc.
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

#अगर_अघोषित __AMDGPU_DISCOVERY__
#घोषणा __AMDGPU_DISCOVERY__

#घोषणा DISCOVERY_TMR_SIZE      (4 << 10)
#घोषणा DISCOVERY_TMR_OFFSET    (64 << 10)

व्योम amdgpu_discovery_fini(काष्ठा amdgpu_device *adev);
पूर्णांक amdgpu_discovery_reg_base_init(काष्ठा amdgpu_device *adev);
व्योम amdgpu_discovery_harvest_ip(काष्ठा amdgpu_device *adev);
पूर्णांक amdgpu_discovery_get_ip_version(काष्ठा amdgpu_device *adev, पूर्णांक hw_id,
                                    पूर्णांक *major, पूर्णांक *minor, पूर्णांक *revision);
पूर्णांक amdgpu_discovery_get_gfx_info(काष्ठा amdgpu_device *adev);

#पूर्ण_अगर /* __AMDGPU_DISCOVERY__ */
