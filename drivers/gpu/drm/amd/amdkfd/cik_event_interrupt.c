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

#समावेश "kfd_priv.h"
#समावेश "kfd_events.h"
#समावेश "cik_int.h"
#समावेश "amdgpu_amdkfd.h"
#समावेश "kfd_smi_events.h"

अटल bool cik_event_पूर्णांकerrupt_isr(काष्ठा kfd_dev *dev,
					स्थिर uपूर्णांक32_t *ih_ring_entry,
					uपूर्णांक32_t *patched_ihre,
					bool *patched_flag)
अणु
	स्थिर काष्ठा cik_ih_ring_entry *ihre =
			(स्थिर काष्ठा cik_ih_ring_entry *)ih_ring_entry;
	स्थिर काष्ठा kfd2kgd_calls *f2g = dev->kfd2kgd;
	अचिन्हित पूर्णांक vmid;
	uपूर्णांक16_t pasid;
	bool ret;

	/* This workaround is due to HW/FW limitation on Hawaii that
	 * VMID and PASID are not written पूर्णांकo ih_ring_entry
	 */
	अगर ((ihre->source_id == CIK_INTSRC_GFX_PAGE_INV_FAULT ||
		ihre->source_id == CIK_INTSRC_GFX_MEM_PROT_FAULT) &&
		dev->device_info->asic_family == CHIP_HAWAII) अणु
		काष्ठा cik_ih_ring_entry *पंचांगp_ihre =
			(काष्ठा cik_ih_ring_entry *)patched_ihre;

		*patched_flag = true;
		*पंचांगp_ihre = *ihre;

		vmid = f2g->पढ़ो_vmid_from_vmfault_reg(dev->kgd);
		ret = f2g->get_atc_vmid_pasid_mapping_info(dev->kgd, vmid, &pasid);

		पंचांगp_ihre->ring_id &= 0x000000ff;
		पंचांगp_ihre->ring_id |= vmid << 8;
		पंचांगp_ihre->ring_id |= pasid << 16;

		वापस ret && (pasid != 0) &&
			vmid >= dev->vm_info.first_vmid_kfd &&
			vmid <= dev->vm_info.last_vmid_kfd;
	पूर्ण

	/* Only handle पूर्णांकerrupts from KFD VMIDs */
	vmid  = (ihre->ring_id & 0x0000ff00) >> 8;
	अगर (vmid < dev->vm_info.first_vmid_kfd ||
	    vmid > dev->vm_info.last_vmid_kfd)
		वापस false;

	/* If there is no valid PASID, it's likely a firmware bug */
	pasid = (ihre->ring_id & 0xffff0000) >> 16;
	अगर (WARN_ONCE(pasid == 0, "FW bug: No PASID in KFD interrupt"))
		वापस false;

	/* Interrupt types we care about: various संकेतs and faults.
	 * They will be क्रमwarded to a work queue (see below).
	 */
	वापस ihre->source_id == CIK_INTSRC_CP_END_OF_PIPE ||
		ihre->source_id == CIK_INTSRC_SDMA_TRAP ||
		ihre->source_id == CIK_INTSRC_SQ_INTERRUPT_MSG ||
		ihre->source_id == CIK_INTSRC_CP_BAD_OPCODE ||
		((ihre->source_id == CIK_INTSRC_GFX_PAGE_INV_FAULT ||
		ihre->source_id == CIK_INTSRC_GFX_MEM_PROT_FAULT) &&
		!amdgpu_no_queue_eviction_on_vm_fault);
पूर्ण

अटल व्योम cik_event_पूर्णांकerrupt_wq(काष्ठा kfd_dev *dev,
					स्थिर uपूर्णांक32_t *ih_ring_entry)
अणु
	स्थिर काष्ठा cik_ih_ring_entry *ihre =
			(स्थिर काष्ठा cik_ih_ring_entry *)ih_ring_entry;
	uपूर्णांक32_t context_id = ihre->data & 0xfffffff;
	अचिन्हित पूर्णांक vmid  = (ihre->ring_id & 0x0000ff00) >> 8;
	u32 pasid = (ihre->ring_id & 0xffff0000) >> 16;

	अगर (pasid == 0)
		वापस;

	अगर (ihre->source_id == CIK_INTSRC_CP_END_OF_PIPE)
		kfd_संकेत_event_पूर्णांकerrupt(pasid, context_id, 28);
	अन्यथा अगर (ihre->source_id == CIK_INTSRC_SDMA_TRAP)
		kfd_संकेत_event_पूर्णांकerrupt(pasid, context_id, 28);
	अन्यथा अगर (ihre->source_id == CIK_INTSRC_SQ_INTERRUPT_MSG)
		kfd_संकेत_event_पूर्णांकerrupt(pasid, context_id & 0xff, 8);
	अन्यथा अगर (ihre->source_id == CIK_INTSRC_CP_BAD_OPCODE)
		kfd_संकेत_hw_exception_event(pasid);
	अन्यथा अगर (ihre->source_id == CIK_INTSRC_GFX_PAGE_INV_FAULT ||
		ihre->source_id == CIK_INTSRC_GFX_MEM_PROT_FAULT) अणु
		काष्ठा kfd_vm_fault_info info;

		kfd_smi_event_update_vmfault(dev, pasid);
		kfd_process_vm_fault(dev->dqm, pasid);

		स_रखो(&info, 0, माप(info));
		amdgpu_amdkfd_gpuvm_get_vm_fault_info(dev->kgd, &info);
		अगर (!info.page_addr && !info.status)
			वापस;

		अगर (info.vmid == vmid)
			kfd_संकेत_vm_fault_event(dev, pasid, &info);
		अन्यथा
			kfd_संकेत_vm_fault_event(dev, pasid, शून्य);
	पूर्ण
पूर्ण

स्थिर काष्ठा kfd_event_पूर्णांकerrupt_class event_पूर्णांकerrupt_class_cik = अणु
	.पूर्णांकerrupt_isr = cik_event_पूर्णांकerrupt_isr,
	.पूर्णांकerrupt_wq = cik_event_पूर्णांकerrupt_wq,
पूर्ण;
