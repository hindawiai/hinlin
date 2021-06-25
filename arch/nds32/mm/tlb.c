<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (C) 2005-2017 Andes Technology Corporation

#समावेश <linux/spinlock_types.h>
#समावेश <linux/mm.h>
#समावेश <linux/sched.h>
#समावेश <यंत्र/nds32.h>
#समावेश <nds32_पूर्णांकrinsic.h>

अचिन्हित पूर्णांक cpu_last_cid = अणु TLB_MISC_mskCID + (2 << TLB_MISC_offCID) पूर्ण;

DEFINE_SPINLOCK(cid_lock);

व्योम local_flush_tlb_range(काष्ठा vm_area_काष्ठा *vma,
			   अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	अचिन्हित दीर्घ flags, ocid, ncid;

	अगर ((end - start) > 0x400000) अणु
		__nds32__tlbop_flua();
		__nds32__isb();
		वापस;
	पूर्ण

	spin_lock_irqsave(&cid_lock, flags);
	ocid = __nds32__mfsr(NDS32_SR_TLB_MISC);
	ncid = (ocid & ~TLB_MISC_mskCID) | vma->vm_mm->context.id;
	__nds32__mtsr_dsb(ncid, NDS32_SR_TLB_MISC);
	जबतक (start < end) अणु
		__nds32__tlbop_inv(start);
		__nds32__isb();
		start += PAGE_SIZE;
	पूर्ण
	__nds32__mtsr_dsb(ocid, NDS32_SR_TLB_MISC);
	spin_unlock_irqrestore(&cid_lock, flags);
पूर्ण

व्योम local_flush_tlb_page(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ addr)
अणु
	अचिन्हित दीर्घ flags, ocid, ncid;

	spin_lock_irqsave(&cid_lock, flags);
	ocid = __nds32__mfsr(NDS32_SR_TLB_MISC);
	ncid = (ocid & ~TLB_MISC_mskCID) | vma->vm_mm->context.id;
	__nds32__mtsr_dsb(ncid, NDS32_SR_TLB_MISC);
	__nds32__tlbop_inv(addr);
	__nds32__isb();
	__nds32__mtsr_dsb(ocid, NDS32_SR_TLB_MISC);
	spin_unlock_irqrestore(&cid_lock, flags);
पूर्ण
