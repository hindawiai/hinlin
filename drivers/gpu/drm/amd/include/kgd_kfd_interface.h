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

/*
 * This file defines the निजी पूर्णांकerface between the
 * AMD kernel graphics drivers and the AMD KFD.
 */

#अगर_अघोषित KGD_KFD_INTERFACE_H_INCLUDED
#घोषणा KGD_KFD_INTERFACE_H_INCLUDED

#समावेश <linux/types.h>
#समावेश <linux/biपंचांगap.h>
#समावेश <linux/dma-fence.h>

काष्ठा pci_dev;

#घोषणा KGD_MAX_QUEUES 128

काष्ठा kfd_dev;
काष्ठा kgd_dev;

काष्ठा kgd_mem;

क्रमागत kfd_preempt_type अणु
	KFD_PREEMPT_TYPE_WAVEFRONT_DRAIN = 0,
	KFD_PREEMPT_TYPE_WAVEFRONT_RESET,
पूर्ण;

काष्ठा kfd_vm_fault_info अणु
	uपूर्णांक64_t	page_addr;
	uपूर्णांक32_t	vmid;
	uपूर्णांक32_t	mc_id;
	uपूर्णांक32_t	status;
	bool		prot_valid;
	bool		prot_पढ़ो;
	bool		prot_ग_लिखो;
	bool		prot_exec;
पूर्ण;

काष्ठा kfd_cu_info अणु
	uपूर्णांक32_t num_shader_engines;
	uपूर्णांक32_t num_shader_arrays_per_engine;
	uपूर्णांक32_t num_cu_per_sh;
	uपूर्णांक32_t cu_active_number;
	uपूर्णांक32_t cu_ao_mask;
	uपूर्णांक32_t simd_per_cu;
	uपूर्णांक32_t max_waves_per_simd;
	uपूर्णांक32_t wave_front_size;
	uपूर्णांक32_t max_scratch_slots_per_cu;
	uपूर्णांक32_t lds_size;
	uपूर्णांक32_t cu_biपंचांगap[4][4];
पूर्ण;

/* For getting GPU local memory inक्रमmation from KGD */
काष्ठा kfd_local_mem_info अणु
	uपूर्णांक64_t local_mem_size_निजी;
	uपूर्णांक64_t local_mem_size_खुला;
	uपूर्णांक32_t vram_width;
	uपूर्णांक32_t mem_clk_max;
पूर्ण;

क्रमागत kgd_memory_pool अणु
	KGD_POOL_SYSTEM_CACHEABLE = 1,
	KGD_POOL_SYSTEM_WRITECOMBINE = 2,
	KGD_POOL_FRAMEBUFFER = 3,
पूर्ण;

/**
 * क्रमागत kfd_sched_policy
 *
 * @KFD_SCHED_POLICY_HWS: H/W scheduling policy known as command processor (cp)
 * scheduling. In this scheduling mode we're using the firmware code to
 * schedule the user mode queues and kernel queues such as HIQ and DIQ.
 * the HIQ queue is used as a special queue that dispatches the configuration
 * to the cp and the user mode queues list that are currently running.
 * the DIQ queue is a debugging queue that dispatches debugging commands to the
 * firmware.
 * in this scheduling mode user mode queues over subscription feature is
 * enabled.
 *
 * @KFD_SCHED_POLICY_HWS_NO_OVERSUBSCRIPTION: The same as above but the over
 * subscription feature disabled.
 *
 * @KFD_SCHED_POLICY_NO_HWS: no H/W scheduling policy is a mode which directly
 * set the command processor रेजिस्टरs and sets the queues "manually". This
 * mode is used *ONLY* क्रम debugging proposes.
 *
 */
क्रमागत kfd_sched_policy अणु
	KFD_SCHED_POLICY_HWS = 0,
	KFD_SCHED_POLICY_HWS_NO_OVERSUBSCRIPTION,
	KFD_SCHED_POLICY_NO_HWS
पूर्ण;

काष्ठा kgd2kfd_shared_resources अणु
	/* Bit n == 1 means VMID n is available क्रम KFD. */
	अचिन्हित पूर्णांक compute_vmid_biपंचांगap;

	/* number of pipes per mec */
	uपूर्णांक32_t num_pipe_per_mec;

	/* number of queues per pipe */
	uपूर्णांक32_t num_queue_per_pipe;

	/* Bit n == 1 means Queue n is available क्रम KFD */
	DECLARE_BITMAP(cp_queue_biपंचांगap, KGD_MAX_QUEUES);

	/* SDMA करोorbell assignments (SOC15 and later chips only). Only
	 * specअगरic करोorbells are routed to each SDMA engine. Others
	 * are routed to IH and VCN. They are not usable by the CP.
	 */
	uपूर्णांक32_t *sdma_करोorbell_idx;

	/* From SOC15 onward, the करोorbell index range not usable क्रम CP
	 * queues.
	 */
	uपूर्णांक32_t non_cp_करोorbells_start;
	uपूर्णांक32_t non_cp_करोorbells_end;

	/* Base address of करोorbell aperture. */
	phys_addr_t करोorbell_physical_address;

	/* Size in bytes of करोorbell aperture. */
	माप_प्रकार करोorbell_aperture_size;

	/* Number of bytes at start of aperture reserved क्रम KGD. */
	माप_प्रकार करोorbell_start_offset;

	/* GPUVM address space size in bytes */
	uपूर्णांक64_t gpuvm_size;

	/* Minor device number of the render node */
	पूर्णांक drm_render_minor;

पूर्ण;

काष्ठा tile_config अणु
	uपूर्णांक32_t *tile_config_ptr;
	uपूर्णांक32_t *macro_tile_config_ptr;
	uपूर्णांक32_t num_tile_configs;
	uपूर्णांक32_t num_macro_tile_configs;

	uपूर्णांक32_t gb_addr_config;
	uपूर्णांक32_t num_banks;
	uपूर्णांक32_t num_ranks;
पूर्ण;

#घोषणा KFD_MAX_NUM_OF_QUEUES_PER_DEVICE_DEFAULT 4096

/**
 * काष्ठा kfd2kgd_calls
 *
 * @program_sh_mem_settings: A function that should initiate the memory
 * properties such as मुख्य aperture memory type (cache / non cached) and
 * secondary aperture base address, size and memory type.
 * This function is used only क्रम no cp scheduling mode.
 *
 * @set_pasid_vmid_mapping: Exposes pasid/vmid pair to the H/W क्रम no cp
 * scheduling mode. Only used क्रम no cp scheduling mode.
 *
 * @hqd_load: Loads the mqd काष्ठाure to a H/W hqd slot. used only क्रम no cp
 * sceduling mode.
 *
 * @hqd_sdma_load: Loads the SDMA mqd काष्ठाure to a H/W SDMA hqd slot.
 * used only क्रम no HWS mode.
 *
 * @hqd_dump: Dumps CPC HQD रेजिस्टरs to an array of address-value pairs.
 * Array is allocated with kदो_स्मृति, needs to be मुक्तd with kमुक्त by caller.
 *
 * @hqd_sdma_dump: Dumps SDMA HQD रेजिस्टरs to an array of address-value pairs.
 * Array is allocated with kदो_स्मृति, needs to be मुक्तd with kमुक्त by caller.
 *
 * @hqd_is_occupies: Checks अगर a hqd slot is occupied.
 *
 * @hqd_destroy: Deकाष्ठाs and preempts the queue asचिन्हित to that hqd slot.
 *
 * @hqd_sdma_is_occupied: Checks अगर an SDMA hqd slot is occupied.
 *
 * @hqd_sdma_destroy: Deकाष्ठाs and preempts the SDMA queue asचिन्हित to that
 * SDMA hqd slot.
 *
 * @set_scratch_backing_va: Sets VA क्रम scratch backing memory of a VMID.
 * Only used क्रम no cp scheduling mode
 *
 * @set_vm_context_page_table_base: Program page table base क्रम a VMID
 *
 * @invalidate_tlbs: Invalidate TLBs क्रम a specअगरic PASID
 *
 * @invalidate_tlbs_vmid: Invalidate TLBs क्रम a specअगरic VMID
 *
 * @पढ़ो_vmid_from_vmfault_reg: On Hawaii the VMID is not set in the
 * IH ring entry. This function allows the KFD ISR to get the VMID
 * from the fault status रेजिस्टर as early as possible.
 *
 * @get_cu_occupancy: Function poपूर्णांकer that वापसs to caller the number
 * of wave fronts that are in flight क्रम all of the queues of a process
 * as identअगरied by its pasid. It is important to note that the value
 * वापसed by this function is a snapshot of current moment and cannot
 * guarantee any minimum क्रम the number of waves in-flight. This function
 * is defined क्रम devices that beदीर्घ to GFX9 and later GFX families. Care
 * must be taken in calling this function as it is not defined क्रम devices
 * that beदीर्घ to GFX8 and below GFX families.
 *
 * This काष्ठाure contains function poपूर्णांकers to services that the kgd driver
 * provides to amdkfd driver.
 *
 */
काष्ठा kfd2kgd_calls अणु
	/* Register access functions */
	व्योम (*program_sh_mem_settings)(काष्ठा kgd_dev *kgd, uपूर्णांक32_t vmid,
			uपूर्णांक32_t sh_mem_config,	uपूर्णांक32_t sh_mem_ape1_base,
			uपूर्णांक32_t sh_mem_ape1_limit, uपूर्णांक32_t sh_mem_bases);

	पूर्णांक (*set_pasid_vmid_mapping)(काष्ठा kgd_dev *kgd, u32 pasid,
					अचिन्हित पूर्णांक vmid);

	पूर्णांक (*init_पूर्णांकerrupts)(काष्ठा kgd_dev *kgd, uपूर्णांक32_t pipe_id);

	पूर्णांक (*hqd_load)(काष्ठा kgd_dev *kgd, व्योम *mqd, uपूर्णांक32_t pipe_id,
			uपूर्णांक32_t queue_id, uपूर्णांक32_t __user *wptr,
			uपूर्णांक32_t wptr_shअगरt, uपूर्णांक32_t wptr_mask,
			काष्ठा mm_काष्ठा *mm);

	पूर्णांक (*hiq_mqd_load)(काष्ठा kgd_dev *kgd, व्योम *mqd,
			    uपूर्णांक32_t pipe_id, uपूर्णांक32_t queue_id,
			    uपूर्णांक32_t करोorbell_off);

	पूर्णांक (*hqd_sdma_load)(काष्ठा kgd_dev *kgd, व्योम *mqd,
			     uपूर्णांक32_t __user *wptr, काष्ठा mm_काष्ठा *mm);

	पूर्णांक (*hqd_dump)(काष्ठा kgd_dev *kgd,
			uपूर्णांक32_t pipe_id, uपूर्णांक32_t queue_id,
			uपूर्णांक32_t (**dump)[2], uपूर्णांक32_t *n_regs);

	पूर्णांक (*hqd_sdma_dump)(काष्ठा kgd_dev *kgd,
			     uपूर्णांक32_t engine_id, uपूर्णांक32_t queue_id,
			     uपूर्णांक32_t (**dump)[2], uपूर्णांक32_t *n_regs);

	bool (*hqd_is_occupied)(काष्ठा kgd_dev *kgd, uपूर्णांक64_t queue_address,
				uपूर्णांक32_t pipe_id, uपूर्णांक32_t queue_id);

	पूर्णांक (*hqd_destroy)(काष्ठा kgd_dev *kgd, व्योम *mqd, uपूर्णांक32_t reset_type,
				अचिन्हित पूर्णांक समयout, uपूर्णांक32_t pipe_id,
				uपूर्णांक32_t queue_id);

	bool (*hqd_sdma_is_occupied)(काष्ठा kgd_dev *kgd, व्योम *mqd);

	पूर्णांक (*hqd_sdma_destroy)(काष्ठा kgd_dev *kgd, व्योम *mqd,
				अचिन्हित पूर्णांक समयout);

	पूर्णांक (*address_watch_disable)(काष्ठा kgd_dev *kgd);
	पूर्णांक (*address_watch_execute)(काष्ठा kgd_dev *kgd,
					अचिन्हित पूर्णांक watch_poपूर्णांक_id,
					uपूर्णांक32_t cntl_val,
					uपूर्णांक32_t addr_hi,
					uपूर्णांक32_t addr_lo);
	पूर्णांक (*wave_control_execute)(काष्ठा kgd_dev *kgd,
					uपूर्णांक32_t gfx_index_val,
					uपूर्णांक32_t sq_cmd);
	uपूर्णांक32_t (*address_watch_get_offset)(काष्ठा kgd_dev *kgd,
					अचिन्हित पूर्णांक watch_poपूर्णांक_id,
					अचिन्हित पूर्णांक reg_offset);
	bool (*get_atc_vmid_pasid_mapping_info)(
					काष्ठा kgd_dev *kgd,
					uपूर्णांक8_t vmid,
					uपूर्णांक16_t *p_pasid);

	/* No दीर्घer needed from GFXv9 onward. The scratch base address is
	 * passed to the shader by the CP. It's the user mode driver's
	 * responsibility.
	 */
	व्योम (*set_scratch_backing_va)(काष्ठा kgd_dev *kgd,
				uपूर्णांक64_t va, uपूर्णांक32_t vmid);

	व्योम (*set_vm_context_page_table_base)(काष्ठा kgd_dev *kgd,
			uपूर्णांक32_t vmid, uपूर्णांक64_t page_table_base);
	uपूर्णांक32_t (*पढ़ो_vmid_from_vmfault_reg)(काष्ठा kgd_dev *kgd);

	व्योम (*get_cu_occupancy)(काष्ठा kgd_dev *kgd, पूर्णांक pasid, पूर्णांक *wave_cnt,
			पूर्णांक *max_waves_per_cu);
पूर्ण;

#पूर्ण_अगर	/* KGD_KFD_INTERFACE_H_INCLUDED */
