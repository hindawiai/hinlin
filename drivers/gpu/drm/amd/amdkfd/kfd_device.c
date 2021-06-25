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
 */

#समावेश <linux/द्वा_खोज.h>
#समावेश <linux/pci.h>
#समावेश <linux/slab.h>
#समावेश "kfd_priv.h"
#समावेश "kfd_device_queue_manager.h"
#समावेश "kfd_pm4_headers_vi.h"
#समावेश "cwsr_trap_handler.h"
#समावेश "kfd_iommu.h"
#समावेश "amdgpu_amdkfd.h"
#समावेश "kfd_smi_events.h"

#घोषणा MQD_SIZE_ALIGNED 768

/*
 * kfd_locked is used to lock the kfd driver during suspend or reset
 * once locked, kfd driver will stop any further GPU execution.
 * create process (खोलो) will वापस -EAGAIN.
 */
अटल atomic_t kfd_locked = ATOMIC_INIT(0);

#अगर_घोषित CONFIG_DRM_AMDGPU_CIK
बाह्य स्थिर काष्ठा kfd2kgd_calls gfx_v7_kfd2kgd;
#पूर्ण_अगर
बाह्य स्थिर काष्ठा kfd2kgd_calls gfx_v8_kfd2kgd;
बाह्य स्थिर काष्ठा kfd2kgd_calls gfx_v9_kfd2kgd;
बाह्य स्थिर काष्ठा kfd2kgd_calls arcturus_kfd2kgd;
बाह्य स्थिर काष्ठा kfd2kgd_calls aldebaran_kfd2kgd;
बाह्य स्थिर काष्ठा kfd2kgd_calls gfx_v10_kfd2kgd;
बाह्य स्थिर काष्ठा kfd2kgd_calls gfx_v10_3_kfd2kgd;

अटल स्थिर काष्ठा kfd2kgd_calls *kfd2kgd_funcs[] = अणु
#अगर_घोषित KFD_SUPPORT_IOMMU_V2
#अगर_घोषित CONFIG_DRM_AMDGPU_CIK
	[CHIP_KAVERI] = &gfx_v7_kfd2kgd,
#पूर्ण_अगर
	[CHIP_CARRIZO] = &gfx_v8_kfd2kgd,
	[CHIP_RAVEN] = &gfx_v9_kfd2kgd,
#पूर्ण_अगर
#अगर_घोषित CONFIG_DRM_AMDGPU_CIK
	[CHIP_HAWAII] = &gfx_v7_kfd2kgd,
#पूर्ण_अगर
	[CHIP_TONGA] = &gfx_v8_kfd2kgd,
	[CHIP_FIJI] = &gfx_v8_kfd2kgd,
	[CHIP_POLARIS10] = &gfx_v8_kfd2kgd,
	[CHIP_POLARIS11] = &gfx_v8_kfd2kgd,
	[CHIP_POLARIS12] = &gfx_v8_kfd2kgd,
	[CHIP_VEGAM] = &gfx_v8_kfd2kgd,
	[CHIP_VEGA10] = &gfx_v9_kfd2kgd,
	[CHIP_VEGA12] = &gfx_v9_kfd2kgd,
	[CHIP_VEGA20] = &gfx_v9_kfd2kgd,
	[CHIP_RENOIR] = &gfx_v9_kfd2kgd,
	[CHIP_ARCTURUS] = &arcturus_kfd2kgd,
	[CHIP_ALDEBARAN] = &aldebaran_kfd2kgd,
	[CHIP_NAVI10] = &gfx_v10_kfd2kgd,
	[CHIP_NAVI12] = &gfx_v10_kfd2kgd,
	[CHIP_NAVI14] = &gfx_v10_kfd2kgd,
	[CHIP_SIENNA_CICHLID] = &gfx_v10_3_kfd2kgd,
	[CHIP_NAVY_FLOUNDER] = &gfx_v10_3_kfd2kgd,
	[CHIP_VANGOGH] = &gfx_v10_3_kfd2kgd,
	[CHIP_DIMGREY_CAVEFISH] = &gfx_v10_3_kfd2kgd,
पूर्ण;

#अगर_घोषित KFD_SUPPORT_IOMMU_V2
अटल स्थिर काष्ठा kfd_device_info kaveri_device_info = अणु
	.asic_family = CHIP_KAVERI,
	.asic_name = "kaveri",
	.max_pasid_bits = 16,
	/* max num of queues क्रम KV.TODO should be a dynamic value */
	.max_no_of_hqd	= 24,
	.करोorbell_size  = 4,
	.ih_ring_entry_size = 4 * माप(uपूर्णांक32_t),
	.event_पूर्णांकerrupt_class = &event_पूर्णांकerrupt_class_cik,
	.num_of_watch_poपूर्णांकs = 4,
	.mqd_size_aligned = MQD_SIZE_ALIGNED,
	.supports_cwsr = false,
	.needs_iommu_device = true,
	.needs_pci_atomics = false,
	.num_sdma_engines = 2,
	.num_xgmi_sdma_engines = 0,
	.num_sdma_queues_per_engine = 2,
पूर्ण;

अटल स्थिर काष्ठा kfd_device_info carrizo_device_info = अणु
	.asic_family = CHIP_CARRIZO,
	.asic_name = "carrizo",
	.max_pasid_bits = 16,
	/* max num of queues क्रम CZ.TODO should be a dynamic value */
	.max_no_of_hqd	= 24,
	.करोorbell_size  = 4,
	.ih_ring_entry_size = 4 * माप(uपूर्णांक32_t),
	.event_पूर्णांकerrupt_class = &event_पूर्णांकerrupt_class_cik,
	.num_of_watch_poपूर्णांकs = 4,
	.mqd_size_aligned = MQD_SIZE_ALIGNED,
	.supports_cwsr = true,
	.needs_iommu_device = true,
	.needs_pci_atomics = false,
	.num_sdma_engines = 2,
	.num_xgmi_sdma_engines = 0,
	.num_sdma_queues_per_engine = 2,
पूर्ण;
#पूर्ण_अगर

अटल स्थिर काष्ठा kfd_device_info raven_device_info = अणु
	.asic_family = CHIP_RAVEN,
	.asic_name = "raven",
	.max_pasid_bits = 16,
	.max_no_of_hqd  = 24,
	.करोorbell_size  = 8,
	.ih_ring_entry_size = 8 * माप(uपूर्णांक32_t),
	.event_पूर्णांकerrupt_class = &event_पूर्णांकerrupt_class_v9,
	.num_of_watch_poपूर्णांकs = 4,
	.mqd_size_aligned = MQD_SIZE_ALIGNED,
	.supports_cwsr = true,
	.needs_iommu_device = true,
	.needs_pci_atomics = true,
	.num_sdma_engines = 1,
	.num_xgmi_sdma_engines = 0,
	.num_sdma_queues_per_engine = 2,
पूर्ण;

अटल स्थिर काष्ठा kfd_device_info hawaii_device_info = अणु
	.asic_family = CHIP_HAWAII,
	.asic_name = "hawaii",
	.max_pasid_bits = 16,
	/* max num of queues क्रम KV.TODO should be a dynamic value */
	.max_no_of_hqd	= 24,
	.करोorbell_size  = 4,
	.ih_ring_entry_size = 4 * माप(uपूर्णांक32_t),
	.event_पूर्णांकerrupt_class = &event_पूर्णांकerrupt_class_cik,
	.num_of_watch_poपूर्णांकs = 4,
	.mqd_size_aligned = MQD_SIZE_ALIGNED,
	.supports_cwsr = false,
	.needs_iommu_device = false,
	.needs_pci_atomics = false,
	.num_sdma_engines = 2,
	.num_xgmi_sdma_engines = 0,
	.num_sdma_queues_per_engine = 2,
पूर्ण;

अटल स्थिर काष्ठा kfd_device_info tonga_device_info = अणु
	.asic_family = CHIP_TONGA,
	.asic_name = "tonga",
	.max_pasid_bits = 16,
	.max_no_of_hqd  = 24,
	.करोorbell_size  = 4,
	.ih_ring_entry_size = 4 * माप(uपूर्णांक32_t),
	.event_पूर्णांकerrupt_class = &event_पूर्णांकerrupt_class_cik,
	.num_of_watch_poपूर्णांकs = 4,
	.mqd_size_aligned = MQD_SIZE_ALIGNED,
	.supports_cwsr = false,
	.needs_iommu_device = false,
	.needs_pci_atomics = true,
	.num_sdma_engines = 2,
	.num_xgmi_sdma_engines = 0,
	.num_sdma_queues_per_engine = 2,
पूर्ण;

अटल स्थिर काष्ठा kfd_device_info fiji_device_info = अणु
	.asic_family = CHIP_FIJI,
	.asic_name = "fiji",
	.max_pasid_bits = 16,
	.max_no_of_hqd  = 24,
	.करोorbell_size  = 4,
	.ih_ring_entry_size = 4 * माप(uपूर्णांक32_t),
	.event_पूर्णांकerrupt_class = &event_पूर्णांकerrupt_class_cik,
	.num_of_watch_poपूर्णांकs = 4,
	.mqd_size_aligned = MQD_SIZE_ALIGNED,
	.supports_cwsr = true,
	.needs_iommu_device = false,
	.needs_pci_atomics = true,
	.num_sdma_engines = 2,
	.num_xgmi_sdma_engines = 0,
	.num_sdma_queues_per_engine = 2,
पूर्ण;

अटल स्थिर काष्ठा kfd_device_info fiji_vf_device_info = अणु
	.asic_family = CHIP_FIJI,
	.asic_name = "fiji",
	.max_pasid_bits = 16,
	.max_no_of_hqd  = 24,
	.करोorbell_size  = 4,
	.ih_ring_entry_size = 4 * माप(uपूर्णांक32_t),
	.event_पूर्णांकerrupt_class = &event_पूर्णांकerrupt_class_cik,
	.num_of_watch_poपूर्णांकs = 4,
	.mqd_size_aligned = MQD_SIZE_ALIGNED,
	.supports_cwsr = true,
	.needs_iommu_device = false,
	.needs_pci_atomics = false,
	.num_sdma_engines = 2,
	.num_xgmi_sdma_engines = 0,
	.num_sdma_queues_per_engine = 2,
पूर्ण;


अटल स्थिर काष्ठा kfd_device_info polaris10_device_info = अणु
	.asic_family = CHIP_POLARIS10,
	.asic_name = "polaris10",
	.max_pasid_bits = 16,
	.max_no_of_hqd  = 24,
	.करोorbell_size  = 4,
	.ih_ring_entry_size = 4 * माप(uपूर्णांक32_t),
	.event_पूर्णांकerrupt_class = &event_पूर्णांकerrupt_class_cik,
	.num_of_watch_poपूर्णांकs = 4,
	.mqd_size_aligned = MQD_SIZE_ALIGNED,
	.supports_cwsr = true,
	.needs_iommu_device = false,
	.needs_pci_atomics = true,
	.num_sdma_engines = 2,
	.num_xgmi_sdma_engines = 0,
	.num_sdma_queues_per_engine = 2,
पूर्ण;

अटल स्थिर काष्ठा kfd_device_info polaris10_vf_device_info = अणु
	.asic_family = CHIP_POLARIS10,
	.asic_name = "polaris10",
	.max_pasid_bits = 16,
	.max_no_of_hqd  = 24,
	.करोorbell_size  = 4,
	.ih_ring_entry_size = 4 * माप(uपूर्णांक32_t),
	.event_पूर्णांकerrupt_class = &event_पूर्णांकerrupt_class_cik,
	.num_of_watch_poपूर्णांकs = 4,
	.mqd_size_aligned = MQD_SIZE_ALIGNED,
	.supports_cwsr = true,
	.needs_iommu_device = false,
	.needs_pci_atomics = false,
	.num_sdma_engines = 2,
	.num_xgmi_sdma_engines = 0,
	.num_sdma_queues_per_engine = 2,
पूर्ण;

अटल स्थिर काष्ठा kfd_device_info polaris11_device_info = अणु
	.asic_family = CHIP_POLARIS11,
	.asic_name = "polaris11",
	.max_pasid_bits = 16,
	.max_no_of_hqd  = 24,
	.करोorbell_size  = 4,
	.ih_ring_entry_size = 4 * माप(uपूर्णांक32_t),
	.event_पूर्णांकerrupt_class = &event_पूर्णांकerrupt_class_cik,
	.num_of_watch_poपूर्णांकs = 4,
	.mqd_size_aligned = MQD_SIZE_ALIGNED,
	.supports_cwsr = true,
	.needs_iommu_device = false,
	.needs_pci_atomics = true,
	.num_sdma_engines = 2,
	.num_xgmi_sdma_engines = 0,
	.num_sdma_queues_per_engine = 2,
पूर्ण;

अटल स्थिर काष्ठा kfd_device_info polaris12_device_info = अणु
	.asic_family = CHIP_POLARIS12,
	.asic_name = "polaris12",
	.max_pasid_bits = 16,
	.max_no_of_hqd  = 24,
	.करोorbell_size  = 4,
	.ih_ring_entry_size = 4 * माप(uपूर्णांक32_t),
	.event_पूर्णांकerrupt_class = &event_पूर्णांकerrupt_class_cik,
	.num_of_watch_poपूर्णांकs = 4,
	.mqd_size_aligned = MQD_SIZE_ALIGNED,
	.supports_cwsr = true,
	.needs_iommu_device = false,
	.needs_pci_atomics = true,
	.num_sdma_engines = 2,
	.num_xgmi_sdma_engines = 0,
	.num_sdma_queues_per_engine = 2,
पूर्ण;

अटल स्थिर काष्ठा kfd_device_info vegam_device_info = अणु
	.asic_family = CHIP_VEGAM,
	.asic_name = "vegam",
	.max_pasid_bits = 16,
	.max_no_of_hqd  = 24,
	.करोorbell_size  = 4,
	.ih_ring_entry_size = 4 * माप(uपूर्णांक32_t),
	.event_पूर्णांकerrupt_class = &event_पूर्णांकerrupt_class_cik,
	.num_of_watch_poपूर्णांकs = 4,
	.mqd_size_aligned = MQD_SIZE_ALIGNED,
	.supports_cwsr = true,
	.needs_iommu_device = false,
	.needs_pci_atomics = true,
	.num_sdma_engines = 2,
	.num_xgmi_sdma_engines = 0,
	.num_sdma_queues_per_engine = 2,
पूर्ण;

अटल स्थिर काष्ठा kfd_device_info vega10_device_info = अणु
	.asic_family = CHIP_VEGA10,
	.asic_name = "vega10",
	.max_pasid_bits = 16,
	.max_no_of_hqd  = 24,
	.करोorbell_size  = 8,
	.ih_ring_entry_size = 8 * माप(uपूर्णांक32_t),
	.event_पूर्णांकerrupt_class = &event_पूर्णांकerrupt_class_v9,
	.num_of_watch_poपूर्णांकs = 4,
	.mqd_size_aligned = MQD_SIZE_ALIGNED,
	.supports_cwsr = true,
	.needs_iommu_device = false,
	.needs_pci_atomics = false,
	.num_sdma_engines = 2,
	.num_xgmi_sdma_engines = 0,
	.num_sdma_queues_per_engine = 2,
पूर्ण;

अटल स्थिर काष्ठा kfd_device_info vega10_vf_device_info = अणु
	.asic_family = CHIP_VEGA10,
	.asic_name = "vega10",
	.max_pasid_bits = 16,
	.max_no_of_hqd  = 24,
	.करोorbell_size  = 8,
	.ih_ring_entry_size = 8 * माप(uपूर्णांक32_t),
	.event_पूर्णांकerrupt_class = &event_पूर्णांकerrupt_class_v9,
	.num_of_watch_poपूर्णांकs = 4,
	.mqd_size_aligned = MQD_SIZE_ALIGNED,
	.supports_cwsr = true,
	.needs_iommu_device = false,
	.needs_pci_atomics = false,
	.num_sdma_engines = 2,
	.num_xgmi_sdma_engines = 0,
	.num_sdma_queues_per_engine = 2,
पूर्ण;

अटल स्थिर काष्ठा kfd_device_info vega12_device_info = अणु
	.asic_family = CHIP_VEGA12,
	.asic_name = "vega12",
	.max_pasid_bits = 16,
	.max_no_of_hqd  = 24,
	.करोorbell_size  = 8,
	.ih_ring_entry_size = 8 * माप(uपूर्णांक32_t),
	.event_पूर्णांकerrupt_class = &event_पूर्णांकerrupt_class_v9,
	.num_of_watch_poपूर्णांकs = 4,
	.mqd_size_aligned = MQD_SIZE_ALIGNED,
	.supports_cwsr = true,
	.needs_iommu_device = false,
	.needs_pci_atomics = false,
	.num_sdma_engines = 2,
	.num_xgmi_sdma_engines = 0,
	.num_sdma_queues_per_engine = 2,
पूर्ण;

अटल स्थिर काष्ठा kfd_device_info vega20_device_info = अणु
	.asic_family = CHIP_VEGA20,
	.asic_name = "vega20",
	.max_pasid_bits = 16,
	.max_no_of_hqd	= 24,
	.करोorbell_size	= 8,
	.ih_ring_entry_size = 8 * माप(uपूर्णांक32_t),
	.event_पूर्णांकerrupt_class = &event_पूर्णांकerrupt_class_v9,
	.num_of_watch_poपूर्णांकs = 4,
	.mqd_size_aligned = MQD_SIZE_ALIGNED,
	.supports_cwsr = true,
	.needs_iommu_device = false,
	.needs_pci_atomics = false,
	.num_sdma_engines = 2,
	.num_xgmi_sdma_engines = 0,
	.num_sdma_queues_per_engine = 8,
पूर्ण;

अटल स्थिर काष्ठा kfd_device_info arcturus_device_info = अणु
	.asic_family = CHIP_ARCTURUS,
	.asic_name = "arcturus",
	.max_pasid_bits = 16,
	.max_no_of_hqd	= 24,
	.करोorbell_size	= 8,
	.ih_ring_entry_size = 8 * माप(uपूर्णांक32_t),
	.event_पूर्णांकerrupt_class = &event_पूर्णांकerrupt_class_v9,
	.num_of_watch_poपूर्णांकs = 4,
	.mqd_size_aligned = MQD_SIZE_ALIGNED,
	.supports_cwsr = true,
	.needs_iommu_device = false,
	.needs_pci_atomics = false,
	.num_sdma_engines = 2,
	.num_xgmi_sdma_engines = 6,
	.num_sdma_queues_per_engine = 8,
पूर्ण;

अटल स्थिर काष्ठा kfd_device_info aldebaran_device_info = अणु
	.asic_family = CHIP_ALDEBARAN,
	.asic_name = "aldebaran",
	.max_pasid_bits = 16,
	.max_no_of_hqd	= 24,
	.करोorbell_size	= 8,
	.ih_ring_entry_size = 8 * माप(uपूर्णांक32_t),
	.event_पूर्णांकerrupt_class = &event_पूर्णांकerrupt_class_v9,
	.num_of_watch_poपूर्णांकs = 4,
	.mqd_size_aligned = MQD_SIZE_ALIGNED,
	.supports_cwsr = true,
	.needs_iommu_device = false,
	.needs_pci_atomics = false,
	.num_sdma_engines = 2,
	.num_xgmi_sdma_engines = 3,
	.num_sdma_queues_per_engine = 8,
पूर्ण;

अटल स्थिर काष्ठा kfd_device_info renoir_device_info = अणु
	.asic_family = CHIP_RENOIR,
	.asic_name = "renoir",
	.max_pasid_bits = 16,
	.max_no_of_hqd  = 24,
	.करोorbell_size  = 8,
	.ih_ring_entry_size = 8 * माप(uपूर्णांक32_t),
	.event_पूर्णांकerrupt_class = &event_पूर्णांकerrupt_class_v9,
	.num_of_watch_poपूर्णांकs = 4,
	.mqd_size_aligned = MQD_SIZE_ALIGNED,
	.supports_cwsr = true,
	.needs_iommu_device = false,
	.needs_pci_atomics = false,
	.num_sdma_engines = 1,
	.num_xgmi_sdma_engines = 0,
	.num_sdma_queues_per_engine = 2,
पूर्ण;

अटल स्थिर काष्ठा kfd_device_info navi10_device_info = अणु
	.asic_family = CHIP_NAVI10,
	.asic_name = "navi10",
	.max_pasid_bits = 16,
	.max_no_of_hqd  = 24,
	.करोorbell_size  = 8,
	.ih_ring_entry_size = 8 * माप(uपूर्णांक32_t),
	.event_पूर्णांकerrupt_class = &event_पूर्णांकerrupt_class_v9,
	.num_of_watch_poपूर्णांकs = 4,
	.mqd_size_aligned = MQD_SIZE_ALIGNED,
	.needs_iommu_device = false,
	.supports_cwsr = true,
	.needs_pci_atomics = true,
	.num_sdma_engines = 2,
	.num_xgmi_sdma_engines = 0,
	.num_sdma_queues_per_engine = 8,
पूर्ण;

अटल स्थिर काष्ठा kfd_device_info navi12_device_info = अणु
	.asic_family = CHIP_NAVI12,
	.asic_name = "navi12",
	.max_pasid_bits = 16,
	.max_no_of_hqd  = 24,
	.करोorbell_size  = 8,
	.ih_ring_entry_size = 8 * माप(uपूर्णांक32_t),
	.event_पूर्णांकerrupt_class = &event_पूर्णांकerrupt_class_v9,
	.num_of_watch_poपूर्णांकs = 4,
	.mqd_size_aligned = MQD_SIZE_ALIGNED,
	.needs_iommu_device = false,
	.supports_cwsr = true,
	.needs_pci_atomics = true,
	.num_sdma_engines = 2,
	.num_xgmi_sdma_engines = 0,
	.num_sdma_queues_per_engine = 8,
पूर्ण;

अटल स्थिर काष्ठा kfd_device_info navi14_device_info = अणु
	.asic_family = CHIP_NAVI14,
	.asic_name = "navi14",
	.max_pasid_bits = 16,
	.max_no_of_hqd  = 24,
	.करोorbell_size  = 8,
	.ih_ring_entry_size = 8 * माप(uपूर्णांक32_t),
	.event_पूर्णांकerrupt_class = &event_पूर्णांकerrupt_class_v9,
	.num_of_watch_poपूर्णांकs = 4,
	.mqd_size_aligned = MQD_SIZE_ALIGNED,
	.needs_iommu_device = false,
	.supports_cwsr = true,
	.needs_pci_atomics = true,
	.num_sdma_engines = 2,
	.num_xgmi_sdma_engines = 0,
	.num_sdma_queues_per_engine = 8,
पूर्ण;

अटल स्थिर काष्ठा kfd_device_info sienna_cichlid_device_info = अणु
	.asic_family = CHIP_SIENNA_CICHLID,
	.asic_name = "sienna_cichlid",
	.max_pasid_bits = 16,
	.max_no_of_hqd  = 24,
	.करोorbell_size  = 8,
	.ih_ring_entry_size = 8 * माप(uपूर्णांक32_t),
	.event_पूर्णांकerrupt_class = &event_पूर्णांकerrupt_class_v9,
	.num_of_watch_poपूर्णांकs = 4,
	.mqd_size_aligned = MQD_SIZE_ALIGNED,
	.needs_iommu_device = false,
	.supports_cwsr = true,
	.needs_pci_atomics = true,
	.num_sdma_engines = 4,
	.num_xgmi_sdma_engines = 0,
	.num_sdma_queues_per_engine = 8,
पूर्ण;

अटल स्थिर काष्ठा kfd_device_info navy_flounder_device_info = अणु
	.asic_family = CHIP_NAVY_FLOUNDER,
	.asic_name = "navy_flounder",
	.max_pasid_bits = 16,
	.max_no_of_hqd  = 24,
	.करोorbell_size  = 8,
	.ih_ring_entry_size = 8 * माप(uपूर्णांक32_t),
	.event_पूर्णांकerrupt_class = &event_पूर्णांकerrupt_class_v9,
	.num_of_watch_poपूर्णांकs = 4,
	.mqd_size_aligned = MQD_SIZE_ALIGNED,
	.needs_iommu_device = false,
	.supports_cwsr = true,
	.needs_pci_atomics = true,
	.num_sdma_engines = 2,
	.num_xgmi_sdma_engines = 0,
	.num_sdma_queues_per_engine = 8,
पूर्ण;

अटल स्थिर काष्ठा kfd_device_info vangogh_device_info = अणु
	.asic_family = CHIP_VANGOGH,
	.asic_name = "vangogh",
	.max_pasid_bits = 16,
	.max_no_of_hqd  = 24,
	.करोorbell_size  = 8,
	.ih_ring_entry_size = 8 * माप(uपूर्णांक32_t),
	.event_पूर्णांकerrupt_class = &event_पूर्णांकerrupt_class_v9,
	.num_of_watch_poपूर्णांकs = 4,
	.mqd_size_aligned = MQD_SIZE_ALIGNED,
	.needs_iommu_device = false,
	.supports_cwsr = true,
	.needs_pci_atomics = false,
	.num_sdma_engines = 1,
	.num_xgmi_sdma_engines = 0,
	.num_sdma_queues_per_engine = 2,
पूर्ण;

अटल स्थिर काष्ठा kfd_device_info dimgrey_cavefish_device_info = अणु
	.asic_family = CHIP_DIMGREY_CAVEFISH,
	.asic_name = "dimgrey_cavefish",
	.max_pasid_bits = 16,
	.max_no_of_hqd  = 24,
	.करोorbell_size  = 8,
	.ih_ring_entry_size = 8 * माप(uपूर्णांक32_t),
	.event_पूर्णांकerrupt_class = &event_पूर्णांकerrupt_class_v9,
	.num_of_watch_poपूर्णांकs = 4,
	.mqd_size_aligned = MQD_SIZE_ALIGNED,
	.needs_iommu_device = false,
	.supports_cwsr = true,
	.needs_pci_atomics = true,
	.num_sdma_engines = 2,
	.num_xgmi_sdma_engines = 0,
	.num_sdma_queues_per_engine = 8,
पूर्ण;


/* For each entry, [0] is regular and [1] is भवisation device. */
अटल स्थिर काष्ठा kfd_device_info *kfd_supported_devices[][2] = अणु
#अगर_घोषित KFD_SUPPORT_IOMMU_V2
	[CHIP_KAVERI] = अणु&kaveri_device_info, शून्यपूर्ण,
	[CHIP_CARRIZO] = अणु&carrizo_device_info, शून्यपूर्ण,
#पूर्ण_अगर
	[CHIP_RAVEN] = अणु&raven_device_info, शून्यपूर्ण,
	[CHIP_HAWAII] = अणु&hawaii_device_info, शून्यपूर्ण,
	[CHIP_TONGA] = अणु&tonga_device_info, शून्यपूर्ण,
	[CHIP_FIJI] = अणु&fiji_device_info, &fiji_vf_device_infoपूर्ण,
	[CHIP_POLARIS10] = अणु&polaris10_device_info, &polaris10_vf_device_infoपूर्ण,
	[CHIP_POLARIS11] = अणु&polaris11_device_info, शून्यपूर्ण,
	[CHIP_POLARIS12] = अणु&polaris12_device_info, शून्यपूर्ण,
	[CHIP_VEGAM] = अणु&vegam_device_info, शून्यपूर्ण,
	[CHIP_VEGA10] = अणु&vega10_device_info, &vega10_vf_device_infoपूर्ण,
	[CHIP_VEGA12] = अणु&vega12_device_info, शून्यपूर्ण,
	[CHIP_VEGA20] = अणु&vega20_device_info, शून्यपूर्ण,
	[CHIP_RENOIR] = अणु&renoir_device_info, शून्यपूर्ण,
	[CHIP_ARCTURUS] = अणु&arcturus_device_info, &arcturus_device_infoपूर्ण,
	[CHIP_ALDEBARAN] = अणु&aldebaran_device_info, शून्यपूर्ण,
	[CHIP_NAVI10] = अणु&navi10_device_info, शून्यपूर्ण,
	[CHIP_NAVI12] = अणु&navi12_device_info, &navi12_device_infoपूर्ण,
	[CHIP_NAVI14] = अणु&navi14_device_info, शून्यपूर्ण,
	[CHIP_SIENNA_CICHLID] = अणु&sienna_cichlid_device_info, &sienna_cichlid_device_infoपूर्ण,
	[CHIP_NAVY_FLOUNDER] = अणु&navy_flounder_device_info, &navy_flounder_device_infoपूर्ण,
	[CHIP_VANGOGH] = अणु&vangogh_device_info, शून्यपूर्ण,
	[CHIP_DIMGREY_CAVEFISH] = अणु&dimgrey_cavefish_device_info, &dimgrey_cavefish_device_infoपूर्ण,
पूर्ण;

अटल पूर्णांक kfd_gtt_sa_init(काष्ठा kfd_dev *kfd, अचिन्हित पूर्णांक buf_size,
				अचिन्हित पूर्णांक chunk_size);
अटल व्योम kfd_gtt_sa_fini(काष्ठा kfd_dev *kfd);

अटल पूर्णांक kfd_resume(काष्ठा kfd_dev *kfd);

काष्ठा kfd_dev *kgd2kfd_probe(काष्ठा kgd_dev *kgd,
	काष्ठा pci_dev *pdev, अचिन्हित पूर्णांक asic_type, bool vf)
अणु
	काष्ठा kfd_dev *kfd;
	स्थिर काष्ठा kfd_device_info *device_info;
	स्थिर काष्ठा kfd2kgd_calls *f2g;

	अगर (asic_type >= माप(kfd_supported_devices) / (माप(व्योम *) * 2)
		|| asic_type >= माप(kfd2kgd_funcs) / माप(व्योम *)) अणु
		dev_err(kfd_device, "asic_type %d out of range\n", asic_type);
		वापस शून्य; /* asic_type out of range */
	पूर्ण

	device_info = kfd_supported_devices[asic_type][vf];
	f2g = kfd2kgd_funcs[asic_type];

	अगर (!device_info || !f2g) अणु
		dev_err(kfd_device, "%s %s not supported in kfd\n",
			amdgpu_asic_name[asic_type], vf ? "VF" : "");
		वापस शून्य;
	पूर्ण

	kfd = kzalloc(माप(*kfd), GFP_KERNEL);
	अगर (!kfd)
		वापस शून्य;

	/* Allow BIF to recode atomics to PCIe 3.0 AtomicOps.
	 * 32 and 64-bit requests are possible and must be
	 * supported.
	 */
	kfd->pci_atomic_requested = amdgpu_amdkfd_have_atomics_support(kgd);
	अगर (device_info->needs_pci_atomics &&
	    !kfd->pci_atomic_requested) अणु
		dev_info(kfd_device,
			 "skipped device %x:%x, PCI rejects atomics\n",
			 pdev->venकरोr, pdev->device);
		kमुक्त(kfd);
		वापस शून्य;
	पूर्ण

	kfd->kgd = kgd;
	kfd->device_info = device_info;
	kfd->pdev = pdev;
	kfd->init_complete = false;
	kfd->kfd2kgd = f2g;
	atomic_set(&kfd->compute_profile, 0);

	mutex_init(&kfd->करोorbell_mutex);
	स_रखो(&kfd->करोorbell_available_index, 0,
		माप(kfd->करोorbell_available_index));

	atomic_set(&kfd->sram_ecc_flag, 0);

	ida_init(&kfd->करोorbell_ida);

	वापस kfd;
पूर्ण

अटल व्योम kfd_cwsr_init(काष्ठा kfd_dev *kfd)
अणु
	अगर (cwsr_enable && kfd->device_info->supports_cwsr) अणु
		अगर (kfd->device_info->asic_family < CHIP_VEGA10) अणु
			BUILD_BUG_ON(माप(cwsr_trap_gfx8_hex) > PAGE_SIZE);
			kfd->cwsr_isa = cwsr_trap_gfx8_hex;
			kfd->cwsr_isa_size = माप(cwsr_trap_gfx8_hex);
		पूर्ण अन्यथा अगर (kfd->device_info->asic_family == CHIP_ARCTURUS) अणु
			BUILD_BUG_ON(माप(cwsr_trap_arcturus_hex) > PAGE_SIZE);
			kfd->cwsr_isa = cwsr_trap_arcturus_hex;
			kfd->cwsr_isa_size = माप(cwsr_trap_arcturus_hex);
		पूर्ण अन्यथा अगर (kfd->device_info->asic_family == CHIP_ALDEBARAN) अणु
			BUILD_BUG_ON(माप(cwsr_trap_aldebaran_hex) > PAGE_SIZE);
			kfd->cwsr_isa = cwsr_trap_aldebaran_hex;
			kfd->cwsr_isa_size = माप(cwsr_trap_aldebaran_hex);
		पूर्ण अन्यथा अगर (kfd->device_info->asic_family < CHIP_NAVI10) अणु
			BUILD_BUG_ON(माप(cwsr_trap_gfx9_hex) > PAGE_SIZE);
			kfd->cwsr_isa = cwsr_trap_gfx9_hex;
			kfd->cwsr_isa_size = माप(cwsr_trap_gfx9_hex);
		पूर्ण अन्यथा अगर (kfd->device_info->asic_family < CHIP_SIENNA_CICHLID) अणु
			BUILD_BUG_ON(माप(cwsr_trap_nv1x_hex) > PAGE_SIZE);
			kfd->cwsr_isa = cwsr_trap_nv1x_hex;
			kfd->cwsr_isa_size = माप(cwsr_trap_nv1x_hex);
		पूर्ण अन्यथा अणु
			BUILD_BUG_ON(माप(cwsr_trap_gfx10_hex) > PAGE_SIZE);
			kfd->cwsr_isa = cwsr_trap_gfx10_hex;
			kfd->cwsr_isa_size = माप(cwsr_trap_gfx10_hex);
		पूर्ण

		kfd->cwsr_enabled = true;
	पूर्ण
पूर्ण

अटल पूर्णांक kfd_gws_init(काष्ठा kfd_dev *kfd)
अणु
	पूर्णांक ret = 0;

	अगर (kfd->dqm->sched_policy == KFD_SCHED_POLICY_NO_HWS)
		वापस 0;

	अगर (hws_gws_support
		|| (kfd->device_info->asic_family == CHIP_VEGA10
			&& kfd->mec2_fw_version >= 0x81b3)
		|| (kfd->device_info->asic_family >= CHIP_VEGA12
			&& kfd->device_info->asic_family <= CHIP_RAVEN
			&& kfd->mec2_fw_version >= 0x1b3)
		|| (kfd->device_info->asic_family == CHIP_ARCTURUS
			&& kfd->mec2_fw_version >= 0x30))
		ret = amdgpu_amdkfd_alloc_gws(kfd->kgd,
				amdgpu_amdkfd_get_num_gws(kfd->kgd), &kfd->gws);

	वापस ret;
पूर्ण

अटल व्योम kfd_smi_init(काष्ठा kfd_dev *dev) अणु
	INIT_LIST_HEAD(&dev->smi_clients);
	spin_lock_init(&dev->smi_lock);
पूर्ण

bool kgd2kfd_device_init(काष्ठा kfd_dev *kfd,
			 काष्ठा drm_device *ddev,
			 स्थिर काष्ठा kgd2kfd_shared_resources *gpu_resources)
अणु
	अचिन्हित पूर्णांक size;

	kfd->ddev = ddev;
	kfd->mec_fw_version = amdgpu_amdkfd_get_fw_version(kfd->kgd,
			KGD_ENGINE_MEC1);
	kfd->mec2_fw_version = amdgpu_amdkfd_get_fw_version(kfd->kgd,
			KGD_ENGINE_MEC2);
	kfd->sdma_fw_version = amdgpu_amdkfd_get_fw_version(kfd->kgd,
			KGD_ENGINE_SDMA1);
	kfd->shared_resources = *gpu_resources;

	kfd->vm_info.first_vmid_kfd = ffs(gpu_resources->compute_vmid_biपंचांगap)-1;
	kfd->vm_info.last_vmid_kfd = fls(gpu_resources->compute_vmid_biपंचांगap)-1;
	kfd->vm_info.vmid_num_kfd = kfd->vm_info.last_vmid_kfd
			- kfd->vm_info.first_vmid_kfd + 1;

	/* Verअगरy module parameters regarding mapped process number*/
	अगर ((hws_max_conc_proc < 0)
			|| (hws_max_conc_proc > kfd->vm_info.vmid_num_kfd)) अणु
		dev_err(kfd_device,
			"hws_max_conc_proc %d must be between 0 and %d, use %d instead\n",
			hws_max_conc_proc, kfd->vm_info.vmid_num_kfd,
			kfd->vm_info.vmid_num_kfd);
		kfd->max_proc_per_quantum = kfd->vm_info.vmid_num_kfd;
	पूर्ण अन्यथा
		kfd->max_proc_per_quantum = hws_max_conc_proc;

	/* calculate max size of mqds needed क्रम queues */
	size = max_num_of_queues_per_device *
			kfd->device_info->mqd_size_aligned;

	/*
	 * calculate max size of runlist packet.
	 * There can be only 2 packets at once
	 */
	size += (KFD_MAX_NUM_OF_PROCESSES * माप(काष्ठा pm4_mes_map_process) +
		max_num_of_queues_per_device * माप(काष्ठा pm4_mes_map_queues)
		+ माप(काष्ठा pm4_mes_runlist)) * 2;

	/* Add size of HIQ & DIQ */
	size += KFD_KERNEL_QUEUE_SIZE * 2;

	/* add another 512KB क्रम all other allocations on gart (HPD, fences) */
	size += 512 * 1024;

	अगर (amdgpu_amdkfd_alloc_gtt_mem(
			kfd->kgd, size, &kfd->gtt_mem,
			&kfd->gtt_start_gpu_addr, &kfd->gtt_start_cpu_ptr,
			false)) अणु
		dev_err(kfd_device, "Could not allocate %d bytes\n", size);
		जाओ alloc_gtt_mem_failure;
	पूर्ण

	dev_info(kfd_device, "Allocated %d bytes on gart\n", size);

	/* Initialize GTT sa with 512 byte chunk size */
	अगर (kfd_gtt_sa_init(kfd, size, 512) != 0) अणु
		dev_err(kfd_device, "Error initializing gtt sub-allocator\n");
		जाओ kfd_gtt_sa_init_error;
	पूर्ण

	अगर (kfd_करोorbell_init(kfd)) अणु
		dev_err(kfd_device,
			"Error initializing doorbell aperture\n");
		जाओ kfd_करोorbell_error;
	पूर्ण

	kfd->hive_id = amdgpu_amdkfd_get_hive_id(kfd->kgd);

	kfd->noretry = amdgpu_amdkfd_get_noretry(kfd->kgd);

	अगर (kfd_पूर्णांकerrupt_init(kfd)) अणु
		dev_err(kfd_device, "Error initializing interrupts\n");
		जाओ kfd_पूर्णांकerrupt_error;
	पूर्ण

	kfd->dqm = device_queue_manager_init(kfd);
	अगर (!kfd->dqm) अणु
		dev_err(kfd_device, "Error initializing queue manager\n");
		जाओ device_queue_manager_error;
	पूर्ण

	/* If supported on this device, allocate global GWS that is shared
	 * by all KFD processes
	 */
	अगर (kfd_gws_init(kfd)) अणु
		dev_err(kfd_device, "Could not allocate %d gws\n",
			amdgpu_amdkfd_get_num_gws(kfd->kgd));
		जाओ gws_error;
	पूर्ण

	/* If CRAT is broken, won't set iommu enabled */
	kfd_द्विगुन_confirm_iommu_support(kfd);

	अगर (kfd_iommu_device_init(kfd)) अणु
		dev_err(kfd_device, "Error initializing iommuv2\n");
		जाओ device_iommu_error;
	पूर्ण

	kfd_cwsr_init(kfd);

	अगर (kfd_resume(kfd))
		जाओ kfd_resume_error;

	kfd->dbgmgr = शून्य;

	अगर (kfd_topology_add_device(kfd)) अणु
		dev_err(kfd_device, "Error adding device to topology\n");
		जाओ kfd_topology_add_device_error;
	पूर्ण

	kfd_smi_init(kfd);

	kfd->init_complete = true;
	dev_info(kfd_device, "added device %x:%x\n", kfd->pdev->venकरोr,
		 kfd->pdev->device);

	pr_debug("Starting kfd with the following scheduling policy %d\n",
		kfd->dqm->sched_policy);

	जाओ out;

kfd_topology_add_device_error:
kfd_resume_error:
device_iommu_error:
gws_error:
	device_queue_manager_uninit(kfd->dqm);
device_queue_manager_error:
	kfd_पूर्णांकerrupt_निकास(kfd);
kfd_पूर्णांकerrupt_error:
	kfd_करोorbell_fini(kfd);
kfd_करोorbell_error:
	kfd_gtt_sa_fini(kfd);
kfd_gtt_sa_init_error:
	amdgpu_amdkfd_मुक्त_gtt_mem(kfd->kgd, kfd->gtt_mem);
alloc_gtt_mem_failure:
	अगर (kfd->gws)
		amdgpu_amdkfd_मुक्त_gws(kfd->kgd, kfd->gws);
	dev_err(kfd_device,
		"device %x:%x NOT added due to errors\n",
		kfd->pdev->venकरोr, kfd->pdev->device);
out:
	वापस kfd->init_complete;
पूर्ण

व्योम kgd2kfd_device_निकास(काष्ठा kfd_dev *kfd)
अणु
	अगर (kfd->init_complete) अणु
		kgd2kfd_suspend(kfd, false);
		device_queue_manager_uninit(kfd->dqm);
		kfd_पूर्णांकerrupt_निकास(kfd);
		kfd_topology_हटाओ_device(kfd);
		kfd_करोorbell_fini(kfd);
		ida_destroy(&kfd->करोorbell_ida);
		kfd_gtt_sa_fini(kfd);
		amdgpu_amdkfd_मुक्त_gtt_mem(kfd->kgd, kfd->gtt_mem);
		अगर (kfd->gws)
			amdgpu_amdkfd_मुक्त_gws(kfd->kgd, kfd->gws);
	पूर्ण

	kमुक्त(kfd);
पूर्ण

पूर्णांक kgd2kfd_pre_reset(काष्ठा kfd_dev *kfd)
अणु
	अगर (!kfd->init_complete)
		वापस 0;

	kfd_smi_event_update_gpu_reset(kfd, false);

	kfd->dqm->ops.pre_reset(kfd->dqm);

	kgd2kfd_suspend(kfd, false);

	kfd_संकेत_reset_event(kfd);
	वापस 0;
पूर्ण

/*
 * Fix me. KFD won't be able to resume existing process क्रम now.
 * We will keep all existing process in a evicted state and
 * रुको the process to be terminated.
 */

पूर्णांक kgd2kfd_post_reset(काष्ठा kfd_dev *kfd)
अणु
	पूर्णांक ret;

	अगर (!kfd->init_complete)
		वापस 0;

	ret = kfd_resume(kfd);
	अगर (ret)
		वापस ret;
	atomic_dec(&kfd_locked);

	atomic_set(&kfd->sram_ecc_flag, 0);

	kfd_smi_event_update_gpu_reset(kfd, true);

	वापस 0;
पूर्ण

bool kfd_is_locked(व्योम)
अणु
	वापस  (atomic_पढ़ो(&kfd_locked) > 0);
पूर्ण

व्योम kgd2kfd_suspend(काष्ठा kfd_dev *kfd, bool run_pm)
अणु
	अगर (!kfd->init_complete)
		वापस;

	/* क्रम runसमय suspend, skip locking kfd */
	अगर (!run_pm) अणु
		/* For first KFD device suspend all the KFD processes */
		अगर (atomic_inc_वापस(&kfd_locked) == 1)
			kfd_suspend_all_processes();
	पूर्ण

	kfd->dqm->ops.stop(kfd->dqm);
	kfd_iommu_suspend(kfd);
पूर्ण

पूर्णांक kgd2kfd_resume(काष्ठा kfd_dev *kfd, bool run_pm)
अणु
	पूर्णांक ret, count;

	अगर (!kfd->init_complete)
		वापस 0;

	ret = kfd_resume(kfd);
	अगर (ret)
		वापस ret;

	/* क्रम runसमय resume, skip unlocking kfd */
	अगर (!run_pm) अणु
		count = atomic_dec_वापस(&kfd_locked);
		WARN_ONCE(count < 0, "KFD suspend / resume ref. error");
		अगर (count == 0)
			ret = kfd_resume_all_processes();
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक kfd_resume(काष्ठा kfd_dev *kfd)
अणु
	पूर्णांक err = 0;

	err = kfd_iommu_resume(kfd);
	अगर (err) अणु
		dev_err(kfd_device,
			"Failed to resume IOMMU for device %x:%x\n",
			kfd->pdev->venकरोr, kfd->pdev->device);
		वापस err;
	पूर्ण

	err = kfd->dqm->ops.start(kfd->dqm);
	अगर (err) अणु
		dev_err(kfd_device,
			"Error starting queue manager for device %x:%x\n",
			kfd->pdev->venकरोr, kfd->pdev->device);
		जाओ dqm_start_error;
	पूर्ण

	वापस err;

dqm_start_error:
	kfd_iommu_suspend(kfd);
	वापस err;
पूर्ण

अटल अंतरभूत व्योम kfd_queue_work(काष्ठा workqueue_काष्ठा *wq,
				  काष्ठा work_काष्ठा *work)
अणु
	पूर्णांक cpu, new_cpu;

	cpu = new_cpu = smp_processor_id();
	करो अणु
		new_cpu = cpumask_next(new_cpu, cpu_online_mask) % nr_cpu_ids;
		अगर (cpu_to_node(new_cpu) == numa_node_id())
			अवरोध;
	पूर्ण जबतक (cpu != new_cpu);

	queue_work_on(new_cpu, wq, work);
पूर्ण

/* This is called directly from KGD at ISR. */
व्योम kgd2kfd_पूर्णांकerrupt(काष्ठा kfd_dev *kfd, स्थिर व्योम *ih_ring_entry)
अणु
	uपूर्णांक32_t patched_ihre[KFD_MAX_RING_ENTRY_SIZE];
	bool is_patched = false;
	अचिन्हित दीर्घ flags;

	अगर (!kfd->init_complete)
		वापस;

	अगर (kfd->device_info->ih_ring_entry_size > माप(patched_ihre)) अणु
		dev_err_once(kfd_device, "Ring entry too small\n");
		वापस;
	पूर्ण

	spin_lock_irqsave(&kfd->पूर्णांकerrupt_lock, flags);

	अगर (kfd->पूर्णांकerrupts_active
	    && पूर्णांकerrupt_is_wanted(kfd, ih_ring_entry,
				   patched_ihre, &is_patched)
	    && enqueue_ih_ring_entry(kfd,
				     is_patched ? patched_ihre : ih_ring_entry))
		kfd_queue_work(kfd->ih_wq, &kfd->पूर्णांकerrupt_work);

	spin_unlock_irqrestore(&kfd->पूर्णांकerrupt_lock, flags);
पूर्ण

पूर्णांक kgd2kfd_quiesce_mm(काष्ठा mm_काष्ठा *mm)
अणु
	काष्ठा kfd_process *p;
	पूर्णांक r;

	/* Because we are called from arbitrary context (workqueue) as opposed
	 * to process context, kfd_process could attempt to निकास जबतक we are
	 * running so the lookup function increments the process ref count.
	 */
	p = kfd_lookup_process_by_mm(mm);
	अगर (!p)
		वापस -ESRCH;

	WARN(debug_evictions, "Evicting pid %d", p->lead_thपढ़ो->pid);
	r = kfd_process_evict_queues(p);

	kfd_unref_process(p);
	वापस r;
पूर्ण

पूर्णांक kgd2kfd_resume_mm(काष्ठा mm_काष्ठा *mm)
अणु
	काष्ठा kfd_process *p;
	पूर्णांक r;

	/* Because we are called from arbitrary context (workqueue) as opposed
	 * to process context, kfd_process could attempt to निकास जबतक we are
	 * running so the lookup function increments the process ref count.
	 */
	p = kfd_lookup_process_by_mm(mm);
	अगर (!p)
		वापस -ESRCH;

	r = kfd_process_restore_queues(p);

	kfd_unref_process(p);
	वापस r;
पूर्ण

/** kgd2kfd_schedule_evict_and_restore_process - Schedules work queue that will
 *   prepare क्रम safe eviction of KFD BOs that beदीर्घ to the specअगरied
 *   process.
 *
 * @mm: mm_काष्ठा that identअगरies the specअगरied KFD process
 * @fence: eviction fence attached to KFD process BOs
 *
 */
पूर्णांक kgd2kfd_schedule_evict_and_restore_process(काष्ठा mm_काष्ठा *mm,
					       काष्ठा dma_fence *fence)
अणु
	काष्ठा kfd_process *p;
	अचिन्हित दीर्घ active_समय;
	अचिन्हित दीर्घ delay_jअगरfies = msecs_to_jअगरfies(PROCESS_ACTIVE_TIME_MS);

	अगर (!fence)
		वापस -EINVAL;

	अगर (dma_fence_is_संकेतed(fence))
		वापस 0;

	p = kfd_lookup_process_by_mm(mm);
	अगर (!p)
		वापस -ENODEV;

	अगर (fence->seqno == p->last_eviction_seqno)
		जाओ out;

	p->last_eviction_seqno = fence->seqno;

	/* Aव्योम KFD process starvation. Wait क्रम at least
	 * PROCESS_ACTIVE_TIME_MS beक्रमe evicting the process again
	 */
	active_समय = get_jअगरfies_64() - p->last_restore_बारtamp;
	अगर (delay_jअगरfies > active_समय)
		delay_jअगरfies -= active_समय;
	अन्यथा
		delay_jअगरfies = 0;

	/* During process initialization eviction_work.dwork is initialized
	 * to kfd_evict_bo_worker
	 */
	WARN(debug_evictions, "Scheduling eviction of pid %d in %ld jiffies",
	     p->lead_thपढ़ो->pid, delay_jअगरfies);
	schedule_delayed_work(&p->eviction_work, delay_jअगरfies);
out:
	kfd_unref_process(p);
	वापस 0;
पूर्ण

अटल पूर्णांक kfd_gtt_sa_init(काष्ठा kfd_dev *kfd, अचिन्हित पूर्णांक buf_size,
				अचिन्हित पूर्णांक chunk_size)
अणु
	अचिन्हित पूर्णांक num_of_दीर्घs;

	अगर (WARN_ON(buf_size < chunk_size))
		वापस -EINVAL;
	अगर (WARN_ON(buf_size == 0))
		वापस -EINVAL;
	अगर (WARN_ON(chunk_size == 0))
		वापस -EINVAL;

	kfd->gtt_sa_chunk_size = chunk_size;
	kfd->gtt_sa_num_of_chunks = buf_size / chunk_size;

	num_of_दीर्घs = (kfd->gtt_sa_num_of_chunks + BITS_PER_LONG - 1) /
		BITS_PER_LONG;

	kfd->gtt_sa_biपंचांगap = kसुस्मृति(num_of_दीर्घs, माप(दीर्घ), GFP_KERNEL);

	अगर (!kfd->gtt_sa_biपंचांगap)
		वापस -ENOMEM;

	pr_debug("gtt_sa_num_of_chunks = %d, gtt_sa_bitmap = %p\n",
			kfd->gtt_sa_num_of_chunks, kfd->gtt_sa_biपंचांगap);

	mutex_init(&kfd->gtt_sa_lock);

	वापस 0;

पूर्ण

अटल व्योम kfd_gtt_sa_fini(काष्ठा kfd_dev *kfd)
अणु
	mutex_destroy(&kfd->gtt_sa_lock);
	kमुक्त(kfd->gtt_sa_biपंचांगap);
पूर्ण

अटल अंतरभूत uपूर्णांक64_t kfd_gtt_sa_calc_gpu_addr(uपूर्णांक64_t start_addr,
						अचिन्हित पूर्णांक bit_num,
						अचिन्हित पूर्णांक chunk_size)
अणु
	वापस start_addr + bit_num * chunk_size;
पूर्ण

अटल अंतरभूत uपूर्णांक32_t *kfd_gtt_sa_calc_cpu_addr(व्योम *start_addr,
						अचिन्हित पूर्णांक bit_num,
						अचिन्हित पूर्णांक chunk_size)
अणु
	वापस (uपूर्णांक32_t *) ((uपूर्णांक64_t) start_addr + bit_num * chunk_size);
पूर्ण

पूर्णांक kfd_gtt_sa_allocate(काष्ठा kfd_dev *kfd, अचिन्हित पूर्णांक size,
			काष्ठा kfd_mem_obj **mem_obj)
अणु
	अचिन्हित पूर्णांक found, start_search, cur_size;

	अगर (size == 0)
		वापस -EINVAL;

	अगर (size > kfd->gtt_sa_num_of_chunks * kfd->gtt_sa_chunk_size)
		वापस -ENOMEM;

	*mem_obj = kzalloc(माप(काष्ठा kfd_mem_obj), GFP_KERNEL);
	अगर (!(*mem_obj))
		वापस -ENOMEM;

	pr_debug("Allocated mem_obj = %p for size = %d\n", *mem_obj, size);

	start_search = 0;

	mutex_lock(&kfd->gtt_sa_lock);

kfd_gtt_restart_search:
	/* Find the first chunk that is मुक्त */
	found = find_next_zero_bit(kfd->gtt_sa_biपंचांगap,
					kfd->gtt_sa_num_of_chunks,
					start_search);

	pr_debug("Found = %d\n", found);

	/* If there wasn't any मुक्त chunk, bail out */
	अगर (found == kfd->gtt_sa_num_of_chunks)
		जाओ kfd_gtt_no_मुक्त_chunk;

	/* Update fields of mem_obj */
	(*mem_obj)->range_start = found;
	(*mem_obj)->range_end = found;
	(*mem_obj)->gpu_addr = kfd_gtt_sa_calc_gpu_addr(
					kfd->gtt_start_gpu_addr,
					found,
					kfd->gtt_sa_chunk_size);
	(*mem_obj)->cpu_ptr = kfd_gtt_sa_calc_cpu_addr(
					kfd->gtt_start_cpu_ptr,
					found,
					kfd->gtt_sa_chunk_size);

	pr_debug("gpu_addr = %p, cpu_addr = %p\n",
			(uपूर्णांक64_t *) (*mem_obj)->gpu_addr, (*mem_obj)->cpu_ptr);

	/* If we need only one chunk, mark it as allocated and get out */
	अगर (size <= kfd->gtt_sa_chunk_size) अणु
		pr_debug("Single bit\n");
		set_bit(found, kfd->gtt_sa_biपंचांगap);
		जाओ kfd_gtt_out;
	पूर्ण

	/* Otherwise, try to see अगर we have enough contiguous chunks */
	cur_size = size - kfd->gtt_sa_chunk_size;
	करो अणु
		(*mem_obj)->range_end =
			find_next_zero_bit(kfd->gtt_sa_biपंचांगap,
					kfd->gtt_sa_num_of_chunks, ++found);
		/*
		 * If next मुक्त chunk is not contiguous than we need to
		 * restart our search from the last मुक्त chunk we found (which
		 * wasn't contiguous to the previous ones
		 */
		अगर ((*mem_obj)->range_end != found) अणु
			start_search = found;
			जाओ kfd_gtt_restart_search;
		पूर्ण

		/*
		 * If we reached end of buffer, bail out with error
		 */
		अगर (found == kfd->gtt_sa_num_of_chunks)
			जाओ kfd_gtt_no_मुक्त_chunk;

		/* Check अगर we करोn't need another chunk */
		अगर (cur_size <= kfd->gtt_sa_chunk_size)
			cur_size = 0;
		अन्यथा
			cur_size -= kfd->gtt_sa_chunk_size;

	पूर्ण जबतक (cur_size > 0);

	pr_debug("range_start = %d, range_end = %d\n",
		(*mem_obj)->range_start, (*mem_obj)->range_end);

	/* Mark the chunks as allocated */
	क्रम (found = (*mem_obj)->range_start;
		found <= (*mem_obj)->range_end;
		found++)
		set_bit(found, kfd->gtt_sa_biपंचांगap);

kfd_gtt_out:
	mutex_unlock(&kfd->gtt_sa_lock);
	वापस 0;

kfd_gtt_no_मुक्त_chunk:
	pr_debug("Allocation failed with mem_obj = %p\n", *mem_obj);
	mutex_unlock(&kfd->gtt_sa_lock);
	kमुक्त(*mem_obj);
	वापस -ENOMEM;
पूर्ण

पूर्णांक kfd_gtt_sa_मुक्त(काष्ठा kfd_dev *kfd, काष्ठा kfd_mem_obj *mem_obj)
अणु
	अचिन्हित पूर्णांक bit;

	/* Act like kमुक्त when trying to मुक्त a शून्य object */
	अगर (!mem_obj)
		वापस 0;

	pr_debug("Free mem_obj = %p, range_start = %d, range_end = %d\n",
			mem_obj, mem_obj->range_start, mem_obj->range_end);

	mutex_lock(&kfd->gtt_sa_lock);

	/* Mark the chunks as मुक्त */
	क्रम (bit = mem_obj->range_start;
		bit <= mem_obj->range_end;
		bit++)
		clear_bit(bit, kfd->gtt_sa_biपंचांगap);

	mutex_unlock(&kfd->gtt_sa_lock);

	kमुक्त(mem_obj);
	वापस 0;
पूर्ण

व्योम kgd2kfd_set_sram_ecc_flag(काष्ठा kfd_dev *kfd)
अणु
	अगर (kfd)
		atomic_inc(&kfd->sram_ecc_flag);
पूर्ण

व्योम kfd_inc_compute_active(काष्ठा kfd_dev *kfd)
अणु
	अगर (atomic_inc_वापस(&kfd->compute_profile) == 1)
		amdgpu_amdkfd_set_compute_idle(kfd->kgd, false);
पूर्ण

व्योम kfd_dec_compute_active(काष्ठा kfd_dev *kfd)
अणु
	पूर्णांक count = atomic_dec_वापस(&kfd->compute_profile);

	अगर (count == 0)
		amdgpu_amdkfd_set_compute_idle(kfd->kgd, true);
	WARN_ONCE(count < 0, "Compute profile ref. count error");
पूर्ण

व्योम kgd2kfd_smi_event_throttle(काष्ठा kfd_dev *kfd, uपूर्णांक32_t throttle_biपंचांगask)
अणु
	अगर (kfd && kfd->init_complete)
		kfd_smi_event_update_thermal_throttling(kfd, throttle_biपंचांगask);
पूर्ण

#अगर defined(CONFIG_DEBUG_FS)

/* This function will send a package to HIQ to hang the HWS
 * which will trigger a GPU reset and bring the HWS back to normal state
 */
पूर्णांक kfd_debugfs_hang_hws(काष्ठा kfd_dev *dev)
अणु
	पूर्णांक r = 0;

	अगर (dev->dqm->sched_policy != KFD_SCHED_POLICY_HWS) अणु
		pr_err("HWS is not enabled");
		वापस -EINVAL;
	पूर्ण

	r = pm_debugfs_hang_hws(&dev->dqm->packets);
	अगर (!r)
		r = dqm_debugfs_execute_queues(dev->dqm);

	वापस r;
पूर्ण

#पूर्ण_अगर
