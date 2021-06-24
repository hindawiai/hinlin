<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_POWERPC_SYNCH_H 
#घोषणा _ASM_POWERPC_SYNCH_H 
#अगर_घोषित __KERNEL__

#समावेश <यंत्र/cputable.h>
#समावेश <यंत्र/feature-fixups.h>
#समावेश <यंत्र/ppc-opcode.h>

#अगर_अघोषित __ASSEMBLY__
बाह्य अचिन्हित पूर्णांक __start___lwsync_fixup, __stop___lwsync_fixup;
बाह्य व्योम करो_lwsync_fixups(अचिन्हित दीर्घ value, व्योम *fixup_start,
			     व्योम *fixup_end);

अटल अंतरभूत व्योम eieio(व्योम)
अणु
	__यंत्र__ __अस्थिर__ ("eieio" : : : "memory");
पूर्ण

अटल अंतरभूत व्योम isync(व्योम)
अणु
	__यंत्र__ __अस्थिर__ ("isync" : : : "memory");
पूर्ण

अटल अंतरभूत व्योम ppc_after_tlbiel_barrier(व्योम)
अणु
	यंत्र अस्थिर("ptesync": : :"memory");
	/*
	 * POWER9, POWER10 need a cp_पात after tlbiel to ensure the copy is
	 * invalidated correctly. If this is not करोne, the paste can take data
	 * from the physical address that was translated at copy समय.
	 *
	 * POWER9 in practice करोes not need this, because address spaces with
	 * accelerators mapped will use tlbie (which करोes invalidate the copy)
	 * to invalidate translations. It's not possible to limit POWER10 this
	 * way due to local copy-paste.
	 */
	यंत्र अस्थिर(ASM_FTR_IFSET(PPC_CP_ABORT, "", %0) : : "i" (CPU_FTR_ARCH_31) : "memory");
पूर्ण
#पूर्ण_अगर /* __ASSEMBLY__ */

#अगर defined(__घातerpc64__)
#    define LWSYNC	lwsync
#या_अगर defined(CONFIG_E500)
#    define LWSYNC					\
	START_LWSYNC_SECTION(96);			\
	sync;						\
	MAKE_LWSYNC_SECTION_ENTRY(96, __lwsync_fixup);
#अन्यथा
#    define LWSYNC	sync
#पूर्ण_अगर

#अगर_घोषित CONFIG_SMP
#घोषणा __PPC_ACQUIRE_BARRIER				\
	START_LWSYNC_SECTION(97);			\
	isync;						\
	MAKE_LWSYNC_SECTION_ENTRY(97, __lwsync_fixup);
#घोषणा PPC_ACQUIRE_BARRIER	 "\n" stringअगरy_in_c(__PPC_ACQUIRE_BARRIER)
#घोषणा PPC_RELEASE_BARRIER	 stringअगरy_in_c(LWSYNC) "\n"
#घोषणा PPC_ATOMIC_ENTRY_BARRIER "\n" stringअगरy_in_c(sync) "\n"
#घोषणा PPC_ATOMIC_EXIT_BARRIER	 "\n" stringअगरy_in_c(sync) "\n"
#अन्यथा
#घोषणा PPC_ACQUIRE_BARRIER
#घोषणा PPC_RELEASE_BARRIER
#घोषणा PPC_ATOMIC_ENTRY_BARRIER
#घोषणा PPC_ATOMIC_EXIT_BARRIER
#पूर्ण_अगर

#पूर्ण_अगर /* __KERNEL__ */
#पूर्ण_अगर	/* _ASM_POWERPC_SYNCH_H */
