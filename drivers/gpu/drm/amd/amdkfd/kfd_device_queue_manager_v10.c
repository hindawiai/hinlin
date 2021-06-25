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

#समावेश "kfd_device_queue_manager.h"
#समावेश "navi10_enum.h"
#समावेश "gc/gc_10_1_0_offset.h"
#समावेश "gc/gc_10_1_0_sh_mask.h"

अटल पूर्णांक update_qpd_v10(काष्ठा device_queue_manager *dqm,
			 काष्ठा qcm_process_device *qpd);
अटल व्योम init_sdma_vm_v10(काष्ठा device_queue_manager *dqm, काष्ठा queue *q,
			    काष्ठा qcm_process_device *qpd);

व्योम device_queue_manager_init_v10_navi10(
	काष्ठा device_queue_manager_asic_ops *asic_ops)
अणु
	asic_ops->update_qpd = update_qpd_v10;
	asic_ops->init_sdma_vm = init_sdma_vm_v10;
	asic_ops->mqd_manager_init = mqd_manager_init_v10;
पूर्ण

अटल uपूर्णांक32_t compute_sh_mem_bases_64bit(काष्ठा kfd_process_device *pdd)
अणु
	uपूर्णांक32_t shared_base = pdd->lds_base >> 48;
	uपूर्णांक32_t निजी_base = pdd->scratch_base >> 48;

	वापस (shared_base << SH_MEM_BASES__SHARED_BASE__SHIFT) |
		निजी_base;
पूर्ण

अटल पूर्णांक update_qpd_v10(काष्ठा device_queue_manager *dqm,
			 काष्ठा qcm_process_device *qpd)
अणु
	काष्ठा kfd_process_device *pdd;

	pdd = qpd_to_pdd(qpd);

	/* check अगर sh_mem_config रेजिस्टर alपढ़ोy configured */
	अगर (qpd->sh_mem_config == 0) अणु
		qpd->sh_mem_config =
			(SH_MEM_ALIGNMENT_MODE_UNALIGNED <<
				SH_MEM_CONFIG__ALIGNMENT_MODE__SHIFT) |
			(3 << SH_MEM_CONFIG__INITIAL_INST_PREFETCH__SHIFT);
#अगर 0
		/* TODO:
		 *    This shouldn't be an issue with Navi10.  Verअगरy.
		 */
		अगर (vega10_noretry)
			qpd->sh_mem_config |=
				1 << SH_MEM_CONFIG__RETRY_DISABLE__SHIFT;
#पूर्ण_अगर

		qpd->sh_mem_ape1_limit = 0;
		qpd->sh_mem_ape1_base = 0;
	पूर्ण

	qpd->sh_mem_bases = compute_sh_mem_bases_64bit(pdd);

	pr_debug("sh_mem_bases 0x%X\n", qpd->sh_mem_bases);

	वापस 0;
पूर्ण

अटल व्योम init_sdma_vm_v10(काष्ठा device_queue_manager *dqm, काष्ठा queue *q,
			    काष्ठा qcm_process_device *qpd)
अणु
	/* Not needed on SDMAv4 onwards any more */
	q->properties.sdma_vm_addr = 0;
पूर्ण
