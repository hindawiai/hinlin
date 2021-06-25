<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __MIPS_ASM_GINVT_H__
#घोषणा __MIPS_ASM_GINVT_H__

#समावेश <यंत्र/mipsregs.h>

क्रमागत ginvt_type अणु
	GINVT_FULL,
	GINVT_VA,
	GINVT_MMID,
पूर्ण;

#अगर_घोषित TOOLCHAIN_SUPPORTS_GINV
# define _ASM_SET_GINV	".set	ginv\n"
#अन्यथा
_ASM_MACRO_1R1I(ginvt, rs, type,
		_ASM_INSN_IF_MIPS(0x7c0000bd | (__rs << 21) | (\\टype << 8))
		_ASM_INSN32_IF_MM(0x0000717c | (__rs << 16) | (\\टype << 9)));
# define _ASM_SET_GINV
#पूर्ण_अगर

अटल __always_अंतरभूत व्योम ginvt(अचिन्हित दीर्घ addr, क्रमागत ginvt_type type)
अणु
	यंत्र अस्थिर(
		".set	push\n"
		_ASM_SET_GINV
		"	ginvt	%0, %1\n"
		".set	pop"
		: /* no outमाला_दो */
		: "r"(addr), "i"(type)
		: "memory");
पूर्ण

अटल अंतरभूत व्योम ginvt_full(व्योम)
अणु
	ginvt(0, GINVT_FULL);
पूर्ण

अटल अंतरभूत व्योम ginvt_va(अचिन्हित दीर्घ addr)
अणु
	addr &= PAGE_MASK << 1;
	ginvt(addr, GINVT_VA);
पूर्ण

अटल अंतरभूत व्योम ginvt_mmid(व्योम)
अणु
	ginvt(0, GINVT_MMID);
पूर्ण

अटल अंतरभूत व्योम ginvt_va_mmid(अचिन्हित दीर्घ addr)
अणु
	addr &= PAGE_MASK << 1;
	ginvt(addr, GINVT_VA | GINVT_MMID);
पूर्ण

#पूर्ण_अगर /* __MIPS_ASM_GINVT_H__ */
