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

#समावेश "kfd_device_queue_manager.h"
#समावेश "cik_regs.h"
#समावेश "oss/oss_2_4_sh_mask.h"
#समावेश "gca/gfx_7_2_sh_mask.h"

अटल bool set_cache_memory_policy_cik(काष्ठा device_queue_manager *dqm,
				   काष्ठा qcm_process_device *qpd,
				   क्रमागत cache_policy शेष_policy,
				   क्रमागत cache_policy alternate_policy,
				   व्योम __user *alternate_aperture_base,
				   uपूर्णांक64_t alternate_aperture_size);
अटल पूर्णांक update_qpd_cik(काष्ठा device_queue_manager *dqm,
					काष्ठा qcm_process_device *qpd);
अटल पूर्णांक update_qpd_cik_hawaii(काष्ठा device_queue_manager *dqm,
					काष्ठा qcm_process_device *qpd);
अटल व्योम init_sdma_vm(काष्ठा device_queue_manager *dqm, काष्ठा queue *q,
				काष्ठा qcm_process_device *qpd);
अटल व्योम init_sdma_vm_hawaii(काष्ठा device_queue_manager *dqm,
				काष्ठा queue *q,
				काष्ठा qcm_process_device *qpd);

व्योम device_queue_manager_init_cik(
		काष्ठा device_queue_manager_asic_ops *asic_ops)
अणु
	asic_ops->set_cache_memory_policy = set_cache_memory_policy_cik;
	asic_ops->update_qpd = update_qpd_cik;
	asic_ops->init_sdma_vm = init_sdma_vm;
	asic_ops->mqd_manager_init = mqd_manager_init_cik;
पूर्ण

व्योम device_queue_manager_init_cik_hawaii(
		काष्ठा device_queue_manager_asic_ops *asic_ops)
अणु
	asic_ops->set_cache_memory_policy = set_cache_memory_policy_cik;
	asic_ops->update_qpd = update_qpd_cik_hawaii;
	asic_ops->init_sdma_vm = init_sdma_vm_hawaii;
	asic_ops->mqd_manager_init = mqd_manager_init_cik_hawaii;
पूर्ण

अटल uपूर्णांक32_t compute_sh_mem_bases_64bit(अचिन्हित पूर्णांक top_address_nybble)
अणु
	/* In 64-bit mode, we can only control the top 3 bits of the LDS,
	 * scratch and GPUVM apertures.
	 * The hardware fills in the reमुख्यing 59 bits according to the
	 * following pattern:
	 * LDS:		X0000000'00000000 - X0000001'00000000 (4GB)
	 * Scratch:	X0000001'00000000 - X0000002'00000000 (4GB)
	 * GPUVM:	Y0010000'00000000 - Y0020000'00000000 (1TB)
	 *
	 * (where X/Y is the configurable nybble with the low-bit 0)
	 *
	 * LDS and scratch will have the same top nybble programmed in the
	 * top 3 bits of SH_MEM_BASES.PRIVATE_BASE.
	 * GPUVM can have a dअगरferent top nybble programmed in the
	 * top 3 bits of SH_MEM_BASES.SHARED_BASE.
	 * We करोn't bother to support dअगरferent top nybbles
	 * क्रम LDS/Scratch and GPUVM.
	 */

	WARN_ON((top_address_nybble & 1) || top_address_nybble > 0xE ||
		top_address_nybble == 0);

	वापस PRIVATE_BASE(top_address_nybble << 12) |
			SHARED_BASE(top_address_nybble << 12);
पूर्ण

अटल bool set_cache_memory_policy_cik(काष्ठा device_queue_manager *dqm,
				   काष्ठा qcm_process_device *qpd,
				   क्रमागत cache_policy शेष_policy,
				   क्रमागत cache_policy alternate_policy,
				   व्योम __user *alternate_aperture_base,
				   uपूर्णांक64_t alternate_aperture_size)
अणु
	uपूर्णांक32_t शेष_mtype;
	uपूर्णांक32_t ape1_mtype;

	शेष_mtype = (शेष_policy == cache_policy_coherent) ?
			MTYPE_NONCACHED :
			MTYPE_CACHED;

	ape1_mtype = (alternate_policy == cache_policy_coherent) ?
			MTYPE_NONCACHED :
			MTYPE_CACHED;

	qpd->sh_mem_config = (qpd->sh_mem_config & PTR32)
			| ALIGNMENT_MODE(SH_MEM_ALIGNMENT_MODE_UNALIGNED)
			| DEFAULT_MTYPE(शेष_mtype)
			| APE1_MTYPE(ape1_mtype);

	वापस true;
पूर्ण

अटल पूर्णांक update_qpd_cik(काष्ठा device_queue_manager *dqm,
		काष्ठा qcm_process_device *qpd)
अणु
	काष्ठा kfd_process_device *pdd;
	अचिन्हित पूर्णांक temp;

	pdd = qpd_to_pdd(qpd);

	/* check अगर sh_mem_config रेजिस्टर alपढ़ोy configured */
	अगर (qpd->sh_mem_config == 0) अणु
		qpd->sh_mem_config =
			ALIGNMENT_MODE(SH_MEM_ALIGNMENT_MODE_UNALIGNED) |
			DEFAULT_MTYPE(MTYPE_NONCACHED) |
			APE1_MTYPE(MTYPE_NONCACHED);
		qpd->sh_mem_ape1_limit = 0;
		qpd->sh_mem_ape1_base = 0;
	पूर्ण

	अगर (qpd->pqm->process->is_32bit_user_mode) अणु
		temp = get_sh_mem_bases_32(pdd);
		qpd->sh_mem_bases = SHARED_BASE(temp);
		qpd->sh_mem_config |= PTR32;
	पूर्ण अन्यथा अणु
		temp = get_sh_mem_bases_nybble_64(pdd);
		qpd->sh_mem_bases = compute_sh_mem_bases_64bit(temp);
		qpd->sh_mem_config |= 1  << SH_MEM_CONFIG__PRIVATE_ATC__SHIFT;
	पूर्ण

	pr_debug("is32bit process: %d sh_mem_bases nybble: 0x%X and register 0x%X\n",
		qpd->pqm->process->is_32bit_user_mode, temp, qpd->sh_mem_bases);

	वापस 0;
पूर्ण

अटल पूर्णांक update_qpd_cik_hawaii(काष्ठा device_queue_manager *dqm,
		काष्ठा qcm_process_device *qpd)
अणु
	काष्ठा kfd_process_device *pdd;
	अचिन्हित पूर्णांक temp;

	pdd = qpd_to_pdd(qpd);

	/* check अगर sh_mem_config रेजिस्टर alपढ़ोy configured */
	अगर (qpd->sh_mem_config == 0) अणु
		qpd->sh_mem_config =
			ALIGNMENT_MODE(SH_MEM_ALIGNMENT_MODE_UNALIGNED) |
			DEFAULT_MTYPE(MTYPE_NONCACHED) |
			APE1_MTYPE(MTYPE_NONCACHED);
		qpd->sh_mem_ape1_limit = 0;
		qpd->sh_mem_ape1_base = 0;
	पूर्ण

	/* On dGPU we're always in GPUVM64 addressing mode with 64-bit
	 * aperture addresses.
	 */
	temp = get_sh_mem_bases_nybble_64(pdd);
	qpd->sh_mem_bases = compute_sh_mem_bases_64bit(temp);

	pr_debug("is32bit process: %d sh_mem_bases nybble: 0x%X and register 0x%X\n",
		qpd->pqm->process->is_32bit_user_mode, temp, qpd->sh_mem_bases);

	वापस 0;
पूर्ण

अटल व्योम init_sdma_vm(काष्ठा device_queue_manager *dqm, काष्ठा queue *q,
				काष्ठा qcm_process_device *qpd)
अणु
	uपूर्णांक32_t value = (1 << SDMA0_RLC0_VIRTUAL_ADDR__ATC__SHIFT);

	अगर (q->process->is_32bit_user_mode)
		value |= (1 << SDMA0_RLC0_VIRTUAL_ADDR__PTR32__SHIFT) |
				get_sh_mem_bases_32(qpd_to_pdd(qpd));
	अन्यथा
		value |= ((get_sh_mem_bases_nybble_64(qpd_to_pdd(qpd))) <<
				SDMA0_RLC0_VIRTUAL_ADDR__SHARED_BASE__SHIFT) &
				SDMA0_RLC0_VIRTUAL_ADDR__SHARED_BASE_MASK;

	q->properties.sdma_vm_addr = value;
पूर्ण

अटल व्योम init_sdma_vm_hawaii(काष्ठा device_queue_manager *dqm,
				काष्ठा queue *q,
				काष्ठा qcm_process_device *qpd)
अणु
	/* On dGPU we're always in GPUVM64 addressing mode with 64-bit
	 * aperture addresses.
	 */
	q->properties.sdma_vm_addr =
		((get_sh_mem_bases_nybble_64(qpd_to_pdd(qpd))) <<
		 SDMA0_RLC0_VIRTUAL_ADDR__SHARED_BASE__SHIFT) &
		SDMA0_RLC0_VIRTUAL_ADDR__SHARED_BASE_MASK;
पूर्ण
