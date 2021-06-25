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

#अगर_अघोषित _AMDGPU_PMU_H_
#घोषणा _AMDGPU_PMU_H_

/* PMU types. */
क्रमागत amdgpu_pmu_perf_type अणु
	AMDGPU_PMU_PERF_TYPE_NONE = 0,
	AMDGPU_PMU_PERF_TYPE_DF,
	AMDGPU_PMU_PERF_TYPE_ALL
पूर्ण;

/*
 * PMU type AMDGPU_PMU_PERF_TYPE_ALL can hold events of dअगरferent "type"
 * configurations.  Event config types are parsed from the 64-bit raw
 * config (See EVENT_CONFIG_TYPE_SHIFT and EVENT_CONFIG_TYPE_MASK) and
 * are रेजिस्टरed पूर्णांकo the HW perf events config_base.
 *
 * PMU types with only a single event configuration type
 * (non-AMDGPU_PMU_PERF_TYPE_ALL) have their event config type स्वतः generated
 * when the perक्रमmance counter is added.
 */
क्रमागत amdgpu_pmu_event_config_type अणु
	AMDGPU_PMU_EVENT_CONFIG_TYPE_NONE = 0,
	AMDGPU_PMU_EVENT_CONFIG_TYPE_DF,
	AMDGPU_PMU_EVENT_CONFIG_TYPE_XGMI,
	AMDGPU_PMU_EVENT_CONFIG_TYPE_MAX
पूर्ण;

#घोषणा AMDGPU_PMU_EVENT_CONFIG_TYPE_SHIFT	56
#घोषणा AMDGPU_PMU_EVENT_CONFIG_TYPE_MASK	0xff

पूर्णांक amdgpu_pmu_init(काष्ठा amdgpu_device *adev);
व्योम amdgpu_pmu_fini(काष्ठा amdgpu_device *adev);

#पूर्ण_अगर /* _AMDGPU_PMU_H_ */
