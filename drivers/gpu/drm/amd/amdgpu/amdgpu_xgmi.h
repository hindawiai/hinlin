<शैली गुरु>
/*
 * Copyright 2016 Advanced Micro Devices, Inc.
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
#अगर_अघोषित __AMDGPU_XGMI_H__
#घोषणा __AMDGPU_XGMI_H__

#समावेश <drm/task_barrier.h>
#समावेश "amdgpu_psp.h"


काष्ठा amdgpu_hive_info अणु
	काष्ठा kobject kobj;
	uपूर्णांक64_t hive_id;
	काष्ठा list_head device_list;
	काष्ठा list_head node;
	atomic_t number_devices;
	काष्ठा mutex hive_lock;
	atomic_t in_reset;
	पूर्णांक hi_req_count;
	काष्ठा amdgpu_device *hi_req_gpu;
	काष्ठा task_barrier tb;
	क्रमागत अणु
		AMDGPU_XGMI_PSTATE_MIN,
		AMDGPU_XGMI_PSTATE_MAX_VEGA20,
		AMDGPU_XGMI_PSTATE_UNKNOWN
	पूर्ण pstate;
पूर्ण;

काष्ठा amdgpu_pcs_ras_field अणु
	स्थिर अक्षर *err_name;
	uपूर्णांक32_t pcs_err_mask;
	uपूर्णांक32_t pcs_err_shअगरt;
पूर्ण;

बाह्य स्थिर काष्ठा amdgpu_xgmi_ras_funcs xgmi_ras_funcs;
काष्ठा amdgpu_hive_info *amdgpu_get_xgmi_hive(काष्ठा amdgpu_device *adev);
व्योम amdgpu_put_xgmi_hive(काष्ठा amdgpu_hive_info *hive);
पूर्णांक amdgpu_xgmi_update_topology(काष्ठा amdgpu_hive_info *hive, काष्ठा amdgpu_device *adev);
पूर्णांक amdgpu_xgmi_add_device(काष्ठा amdgpu_device *adev);
पूर्णांक amdgpu_xgmi_हटाओ_device(काष्ठा amdgpu_device *adev);
पूर्णांक amdgpu_xgmi_set_pstate(काष्ठा amdgpu_device *adev, पूर्णांक pstate);
पूर्णांक amdgpu_xgmi_get_hops_count(काष्ठा amdgpu_device *adev,
		काष्ठा amdgpu_device *peer_adev);
uपूर्णांक64_t amdgpu_xgmi_get_relative_phy_addr(काष्ठा amdgpu_device *adev,
					   uपूर्णांक64_t addr);
अटल अंतरभूत bool amdgpu_xgmi_same_hive(काष्ठा amdgpu_device *adev,
		काष्ठा amdgpu_device *bo_adev)
अणु
	वापस (adev != bo_adev &&
		adev->gmc.xgmi.hive_id &&
		adev->gmc.xgmi.hive_id == bo_adev->gmc.xgmi.hive_id);
पूर्ण

#पूर्ण_अगर
