<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_POWERPC_BOOK3S_32_KUP_H
#घोषणा _ASM_POWERPC_BOOK3S_32_KUP_H

#समावेश <यंत्र/bug.h>
#समावेश <यंत्र/book3s/32/mmu-hash.h>

#अगर_अघोषित __ASSEMBLY__

#अगर_घोषित CONFIG_PPC_KUAP

#समावेश <linux/sched.h>

अटल अंतरभूत व्योम kuap_update_sr(u32 sr, u32 addr, u32 end)
अणु
	addr &= 0xf0000000;	/* align addr to start of segment */
	barrier();	/* make sure thपढ़ो.kuap is updated beक्रमe playing with SRs */
	जबतक (addr < end) अणु
		mtsr(sr, addr);
		sr += 0x111;		/* next VSID */
		sr &= 0xf0ffffff;	/* clear VSID overflow */
		addr += 0x10000000;	/* address of next segment */
	पूर्ण
	isync();	/* Context sync required after mtsr() */
पूर्ण

अटल अंतरभूत व्योम kuap_save_and_lock(काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ kuap = current->thपढ़ो.kuap;
	u32 addr = kuap & 0xf0000000;
	u32 end = kuap << 28;

	regs->kuap = kuap;
	अगर (unlikely(!kuap))
		वापस;

	current->thपढ़ो.kuap = 0;
	kuap_update_sr(mfsr(addr) | SR_KS, addr, end);	/* Set Ks */
पूर्ण

अटल अंतरभूत व्योम kuap_user_restore(काष्ठा pt_regs *regs)
अणु
पूर्ण

अटल अंतरभूत व्योम kuap_kernel_restore(काष्ठा pt_regs *regs, अचिन्हित दीर्घ kuap)
अणु
	u32 addr = regs->kuap & 0xf0000000;
	u32 end = regs->kuap << 28;

	current->thपढ़ो.kuap = regs->kuap;

	अगर (unlikely(regs->kuap == kuap))
		वापस;

	kuap_update_sr(mfsr(addr) & ~SR_KS, addr, end);	/* Clear Ks */
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ kuap_get_and_निश्चित_locked(व्योम)
अणु
	अचिन्हित दीर्घ kuap = current->thपढ़ो.kuap;

	WARN_ON_ONCE(IS_ENABLED(CONFIG_PPC_KUAP_DEBUG) && kuap != 0);

	वापस kuap;
पूर्ण

अटल अंतरभूत व्योम kuap_निश्चित_locked(व्योम)
अणु
	kuap_get_and_निश्चित_locked();
पूर्ण

अटल __always_अंतरभूत व्योम allow_user_access(व्योम __user *to, स्थिर व्योम __user *from,
					      u32 size, अचिन्हित दीर्घ dir)
अणु
	u32 addr, end;

	BUILD_BUG_ON(!__builtin_स्थिरant_p(dir));
	BUILD_BUG_ON(dir & ~KUAP_READ_WRITE);

	अगर (!(dir & KUAP_WRITE))
		वापस;

	addr = (__क्रमce u32)to;

	अगर (unlikely(addr >= TASK_SIZE || !size))
		वापस;

	end = min(addr + size, TASK_SIZE);

	current->thपढ़ो.kuap = (addr & 0xf0000000) | ((((end - 1) >> 28) + 1) & 0xf);
	kuap_update_sr(mfsr(addr) & ~SR_KS, addr, end);	/* Clear Ks */
पूर्ण

अटल __always_अंतरभूत व्योम prevent_user_access(व्योम __user *to, स्थिर व्योम __user *from,
						u32 size, अचिन्हित दीर्घ dir)
अणु
	u32 addr, end;

	BUILD_BUG_ON(!__builtin_स्थिरant_p(dir));

	अगर (dir & KUAP_CURRENT_WRITE) अणु
		u32 kuap = current->thपढ़ो.kuap;

		अगर (unlikely(!kuap))
			वापस;

		addr = kuap & 0xf0000000;
		end = kuap << 28;
	पूर्ण अन्यथा अगर (dir & KUAP_WRITE) अणु
		addr = (__क्रमce u32)to;
		end = min(addr + size, TASK_SIZE);

		अगर (unlikely(addr >= TASK_SIZE || !size))
			वापस;
	पूर्ण अन्यथा अणु
		वापस;
	पूर्ण

	current->thपढ़ो.kuap = 0;
	kuap_update_sr(mfsr(addr) | SR_KS, addr, end);	/* set Ks */
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ prevent_user_access_वापस(व्योम)
अणु
	अचिन्हित दीर्घ flags = current->thपढ़ो.kuap;
	अचिन्हित दीर्घ addr = flags & 0xf0000000;
	अचिन्हित दीर्घ end = flags << 28;
	व्योम __user *to = (__क्रमce व्योम __user *)addr;

	अगर (flags)
		prevent_user_access(to, to, end - addr, KUAP_READ_WRITE);

	वापस flags;
पूर्ण

अटल अंतरभूत व्योम restore_user_access(अचिन्हित दीर्घ flags)
अणु
	अचिन्हित दीर्घ addr = flags & 0xf0000000;
	अचिन्हित दीर्घ end = flags << 28;
	व्योम __user *to = (__क्रमce व्योम __user *)addr;

	अगर (flags)
		allow_user_access(to, to, end - addr, KUAP_READ_WRITE);
पूर्ण

अटल अंतरभूत bool
bad_kuap_fault(काष्ठा pt_regs *regs, अचिन्हित दीर्घ address, bool is_ग_लिखो)
अणु
	अचिन्हित दीर्घ begin = regs->kuap & 0xf0000000;
	अचिन्हित दीर्घ end = regs->kuap << 28;

	वापस is_ग_लिखो && (address < begin || address >= end);
पूर्ण

#पूर्ण_अगर /* CONFIG_PPC_KUAP */

#पूर्ण_अगर /* __ASSEMBLY__ */

#पूर्ण_अगर /* _ASM_POWERPC_BOOK3S_32_KUP_H */
