<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#अगर_अघोषित __LINUX_KBUILD_H
# error "Please do not build this file directly, build asm-offsets.c instead"
#पूर्ण_अगर

#समावेश <यंत्र/ia32.h>

#अगर defined(CONFIG_KVM_GUEST) && defined(CONFIG_PARAVIRT_SPINLOCKS)
#समावेश <यंत्र/kvm_para.h>
#पूर्ण_अगर

पूर्णांक मुख्य(व्योम)
अणु
#अगर_घोषित CONFIG_PARAVIRT
#अगर_घोषित CONFIG_PARAVIRT_XXL
#अगर_घोषित CONFIG_DEBUG_ENTRY
	OFFSET(PV_IRQ_save_fl, paravirt_patch_ढाँचा, irq.save_fl);
#पूर्ण_अगर
#पूर्ण_अगर
	BLANK();
#पूर्ण_अगर

#अगर defined(CONFIG_KVM_GUEST) && defined(CONFIG_PARAVIRT_SPINLOCKS)
	OFFSET(KVM_STEAL_TIME_preempted, kvm_steal_समय, preempted);
	BLANK();
#पूर्ण_अगर

#घोषणा ENTRY(entry) OFFSET(pt_regs_ ## entry, pt_regs, entry)
	ENTRY(bx);
	ENTRY(cx);
	ENTRY(dx);
	ENTRY(sp);
	ENTRY(bp);
	ENTRY(si);
	ENTRY(di);
	ENTRY(r8);
	ENTRY(r9);
	ENTRY(r10);
	ENTRY(r11);
	ENTRY(r12);
	ENTRY(r13);
	ENTRY(r14);
	ENTRY(r15);
	ENTRY(flags);
	BLANK();
#अघोषित ENTRY

#घोषणा ENTRY(entry) OFFSET(saved_context_ ## entry, saved_context, entry)
	ENTRY(cr0);
	ENTRY(cr2);
	ENTRY(cr3);
	ENTRY(cr4);
	ENTRY(gdt_desc);
	BLANK();
#अघोषित ENTRY

	BLANK();

#अगर_घोषित CONFIG_STACKPROTECTOR
	DEFINE(stack_canary_offset, दुरत्व(काष्ठा fixed_percpu_data, stack_canary));
	BLANK();
#पूर्ण_अगर
	वापस 0;
पूर्ण
