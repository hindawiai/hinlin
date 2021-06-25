<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_TLB_H
#घोषणा __ASM_TLB_H

#समावेश <यंत्र/cpu-features.h>
#समावेश <यंत्र/mipsregs.h>

#घोषणा _UNIQUE_ENTRYHI(base, idx)					\
		(((base) + ((idx) << (PAGE_SHIFT + 1))) |		\
		 (cpu_has_tlbinv ? MIPS_ENTRYHI_EHINV : 0))
#घोषणा UNIQUE_ENTRYHI(idx)		_UNIQUE_ENTRYHI(CKSEG0, idx)
#घोषणा UNIQUE_GUEST_ENTRYHI(idx)	_UNIQUE_ENTRYHI(CKSEG1, idx)

अटल अंतरभूत अचिन्हित पूर्णांक num_wired_entries(व्योम)
अणु
	अचिन्हित पूर्णांक wired = पढ़ो_c0_wired();

	अगर (cpu_has_mips_r6)
		wired &= MIPSR6_WIRED_WIRED;

	वापस wired;
पूर्ण

#समावेश <यंत्र-generic/tlb.h>

#पूर्ण_अगर /* __ASM_TLB_H */
