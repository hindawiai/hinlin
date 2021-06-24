<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (C) 2013 Imagination Technologies
 * Author: Paul Burton <paul.burton@mips.com>
 */
#अगर_अघोषित _ASM_MSA_H
#घोषणा _ASM_MSA_H

#समावेश <यंत्र/mipsregs.h>

#अगर_अघोषित __ASSEMBLY__

#समावेश <यंत्र/inst.h>

बाह्य व्योम _save_msa(काष्ठा task_काष्ठा *);
बाह्य व्योम _restore_msa(काष्ठा task_काष्ठा *);
बाह्य व्योम _init_msa_upper(व्योम);

बाह्य व्योम पढ़ो_msa_wr_b(अचिन्हित idx, जोड़ fpureg *to);
बाह्य व्योम पढ़ो_msa_wr_h(अचिन्हित idx, जोड़ fpureg *to);
बाह्य व्योम पढ़ो_msa_wr_w(अचिन्हित idx, जोड़ fpureg *to);
बाह्य व्योम पढ़ो_msa_wr_d(अचिन्हित idx, जोड़ fpureg *to);

/**
 * पढ़ो_msa_wr() - Read a single MSA vector रेजिस्टर
 * @idx:	The index of the vector रेजिस्टर to पढ़ो
 * @to:		The FPU रेजिस्टर जोड़ to store the रेजिस्टरs value in
 * @fmt:	The क्रमmat of the data in the vector रेजिस्टर
 *
 * Read the value of MSA vector रेजिस्टर idx पूर्णांकo the FPU रेजिस्टर
 * जोड़ to, using the क्रमmat fmt.
 */
अटल अंतरभूत व्योम पढ़ो_msa_wr(अचिन्हित idx, जोड़ fpureg *to,
			       क्रमागत msa_2b_fmt fmt)
अणु
	चयन (fmt) अणु
	हाल msa_fmt_b:
		पढ़ो_msa_wr_b(idx, to);
		अवरोध;

	हाल msa_fmt_h:
		पढ़ो_msa_wr_h(idx, to);
		अवरोध;

	हाल msa_fmt_w:
		पढ़ो_msa_wr_w(idx, to);
		अवरोध;

	हाल msa_fmt_d:
		पढ़ो_msa_wr_d(idx, to);
		अवरोध;

	शेष:
		BUG();
	पूर्ण
पूर्ण

बाह्य व्योम ग_लिखो_msa_wr_b(अचिन्हित idx, जोड़ fpureg *from);
बाह्य व्योम ग_लिखो_msa_wr_h(अचिन्हित idx, जोड़ fpureg *from);
बाह्य व्योम ग_लिखो_msa_wr_w(अचिन्हित idx, जोड़ fpureg *from);
बाह्य व्योम ग_लिखो_msa_wr_d(अचिन्हित idx, जोड़ fpureg *from);

/**
 * ग_लिखो_msa_wr() - Write a single MSA vector रेजिस्टर
 * @idx:	The index of the vector रेजिस्टर to ग_लिखो
 * @from:	The FPU रेजिस्टर जोड़ to take the रेजिस्टरs value from
 * @fmt:	The क्रमmat of the data in the vector रेजिस्टर
 *
 * Write the value from the FPU रेजिस्टर जोड़ from पूर्णांकo MSA vector
 * रेजिस्टर idx, using the क्रमmat fmt.
 */
अटल अंतरभूत व्योम ग_लिखो_msa_wr(अचिन्हित idx, जोड़ fpureg *from,
				क्रमागत msa_2b_fmt fmt)
अणु
	चयन (fmt) अणु
	हाल msa_fmt_b:
		ग_लिखो_msa_wr_b(idx, from);
		अवरोध;

	हाल msa_fmt_h:
		ग_लिखो_msa_wr_h(idx, from);
		अवरोध;

	हाल msa_fmt_w:
		ग_लिखो_msa_wr_w(idx, from);
		अवरोध;

	हाल msa_fmt_d:
		ग_लिखो_msa_wr_d(idx, from);
		अवरोध;

	शेष:
		BUG();
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम enable_msa(व्योम)
अणु
	अगर (cpu_has_msa) अणु
		set_c0_config5(MIPS_CONF5_MSAEN);
		enable_fpu_hazard();
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम disable_msa(व्योम)
अणु
	अगर (cpu_has_msa) अणु
		clear_c0_config5(MIPS_CONF5_MSAEN);
		disable_fpu_hazard();
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक is_msa_enabled(व्योम)
अणु
	अगर (!cpu_has_msa)
		वापस 0;

	वापस पढ़ो_c0_config5() & MIPS_CONF5_MSAEN;
पूर्ण

अटल अंतरभूत पूर्णांक thपढ़ो_msa_context_live(व्योम)
अणु
	/*
	 * Check cpu_has_msa only अगर it's a स्थिरant. This will allow the
	 * compiler to optimise out code क्रम CPUs without MSA without adding
	 * an extra redundant check क्रम CPUs with MSA.
	 */
	अगर (__builtin_स्थिरant_p(cpu_has_msa) && !cpu_has_msa)
		वापस 0;

	वापस test_thपढ़ो_flag(TIF_MSA_CTX_LIVE);
पूर्ण

अटल अंतरभूत व्योम save_msa(काष्ठा task_काष्ठा *t)
अणु
	अगर (cpu_has_msa)
		_save_msa(t);
पूर्ण

अटल अंतरभूत व्योम restore_msa(काष्ठा task_काष्ठा *t)
अणु
	अगर (cpu_has_msa)
		_restore_msa(t);
पूर्ण

अटल अंतरभूत व्योम init_msa_upper(व्योम)
अणु
	/*
	 * Check cpu_has_msa only अगर it's a स्थिरant. This will allow the
	 * compiler to optimise out code क्रम CPUs without MSA without adding
	 * an extra redundant check क्रम CPUs with MSA.
	 */
	अगर (__builtin_स्थिरant_p(cpu_has_msa) && !cpu_has_msa)
		वापस;

	_init_msa_upper();
पूर्ण

#अगर_अघोषित TOOLCHAIN_SUPPORTS_MSA
/*
 * Define assembler macros using .word क्रम the c[ft]cmsa inकाष्ठाions in order
 * to allow compilation with toolchains that करो not support MSA. Once all
 * toolchains in use support MSA these can be हटाओd.
 */
_ASM_MACRO_2R(cfcmsa, rd, cs,
	_ASM_INSN_IF_MIPS(0x787e0019 | __cs << 11 | __rd << 6)
	_ASM_INSN32_IF_MM(0x587e0016 | __cs << 11 | __rd << 6));
_ASM_MACRO_2R(ctcmsa, cd, rs,
	_ASM_INSN_IF_MIPS(0x783e0019 | __rs << 11 | __cd << 6)
	_ASM_INSN32_IF_MM(0x583e0016 | __rs << 11 | __cd << 6));
#घोषणा _ASM_SET_MSA ""
#अन्यथा /* TOOLCHAIN_SUPPORTS_MSA */
#घोषणा _ASM_SET_MSA ".set\tfp=64\n\t"				\
		     ".set\tmsa\n\t"
#पूर्ण_अगर

#घोषणा __BUILD_MSA_CTL_REG(name, cs)				\
अटल अंतरभूत अचिन्हित पूर्णांक पढ़ो_msa_##name(व्योम)		\
अणु								\
	अचिन्हित पूर्णांक reg;					\
	__यंत्र__ __अस्थिर__(					\
	"	.set	push\n"					\
	_ASM_SET_MSA						\
	"	cfcmsa	%0, $" #cs "\n"				\
	"	.set	pop\n"					\
	: "=r"(reg));						\
	वापस reg;						\
पूर्ण								\
								\
अटल अंतरभूत व्योम ग_लिखो_msa_##name(अचिन्हित पूर्णांक val)		\
अणु								\
	__यंत्र__ __अस्थिर__(					\
	"	.set	push\n"					\
	_ASM_SET_MSA						\
	"	ctcmsa	$" #cs ", %0\n"				\
	"	.set	pop\n"					\
	: : "r"(val));						\
पूर्ण

__BUILD_MSA_CTL_REG(ir, 0)
__BUILD_MSA_CTL_REG(csr, 1)
__BUILD_MSA_CTL_REG(access, 2)
__BUILD_MSA_CTL_REG(save, 3)
__BUILD_MSA_CTL_REG(modअगरy, 4)
__BUILD_MSA_CTL_REG(request, 5)
__BUILD_MSA_CTL_REG(map, 6)
__BUILD_MSA_CTL_REG(unmap, 7)

#पूर्ण_अगर /* !__ASSEMBLY__ */

#घोषणा MSA_IR		0
#घोषणा MSA_CSR		1
#घोषणा MSA_ACCESS	2
#घोषणा MSA_SAVE	3
#घोषणा MSA_MODIFY	4
#घोषणा MSA_REQUEST	5
#घोषणा MSA_MAP		6
#घोषणा MSA_UNMAP	7

/* MSA Implementation Register (MSAIR) */
#घोषणा MSA_IR_REVB		0
#घोषणा MSA_IR_REVF		(_ULCAST_(0xff) << MSA_IR_REVB)
#घोषणा MSA_IR_PROCB		8
#घोषणा MSA_IR_PROCF		(_ULCAST_(0xff) << MSA_IR_PROCB)
#घोषणा MSA_IR_WRPB		16
#घोषणा MSA_IR_WRPF		(_ULCAST_(0x1) << MSA_IR_WRPB)

/* MSA Control & Status Register (MSACSR) */
#घोषणा MSA_CSR_RMB		0
#घोषणा MSA_CSR_RMF		(_ULCAST_(0x3) << MSA_CSR_RMB)
#घोषणा MSA_CSR_RM_NEAREST	0
#घोषणा MSA_CSR_RM_TO_ZERO	1
#घोषणा MSA_CSR_RM_TO_POS	2
#घोषणा MSA_CSR_RM_TO_NEG	3
#घोषणा MSA_CSR_FLAGSB		2
#घोषणा MSA_CSR_FLAGSF		(_ULCAST_(0x1f) << MSA_CSR_FLAGSB)
#घोषणा MSA_CSR_FLAGS_IB	2
#घोषणा MSA_CSR_FLAGS_IF	(_ULCAST_(0x1) << MSA_CSR_FLAGS_IB)
#घोषणा MSA_CSR_FLAGS_UB	3
#घोषणा MSA_CSR_FLAGS_UF	(_ULCAST_(0x1) << MSA_CSR_FLAGS_UB)
#घोषणा MSA_CSR_FLAGS_OB	4
#घोषणा MSA_CSR_FLAGS_OF	(_ULCAST_(0x1) << MSA_CSR_FLAGS_OB)
#घोषणा MSA_CSR_FLAGS_ZB	5
#घोषणा MSA_CSR_FLAGS_ZF	(_ULCAST_(0x1) << MSA_CSR_FLAGS_ZB)
#घोषणा MSA_CSR_FLAGS_VB	6
#घोषणा MSA_CSR_FLAGS_VF	(_ULCAST_(0x1) << MSA_CSR_FLAGS_VB)
#घोषणा MSA_CSR_ENABLESB	7
#घोषणा MSA_CSR_ENABLESF	(_ULCAST_(0x1f) << MSA_CSR_ENABLESB)
#घोषणा MSA_CSR_ENABLES_IB	7
#घोषणा MSA_CSR_ENABLES_IF	(_ULCAST_(0x1) << MSA_CSR_ENABLES_IB)
#घोषणा MSA_CSR_ENABLES_UB	8
#घोषणा MSA_CSR_ENABLES_UF	(_ULCAST_(0x1) << MSA_CSR_ENABLES_UB)
#घोषणा MSA_CSR_ENABLES_OB	9
#घोषणा MSA_CSR_ENABLES_OF	(_ULCAST_(0x1) << MSA_CSR_ENABLES_OB)
#घोषणा MSA_CSR_ENABLES_ZB	10
#घोषणा MSA_CSR_ENABLES_ZF	(_ULCAST_(0x1) << MSA_CSR_ENABLES_ZB)
#घोषणा MSA_CSR_ENABLES_VB	11
#घोषणा MSA_CSR_ENABLES_VF	(_ULCAST_(0x1) << MSA_CSR_ENABLES_VB)
#घोषणा MSA_CSR_CAUSEB		12
#घोषणा MSA_CSR_CAUSEF		(_ULCAST_(0x3f) << MSA_CSR_CAUSEB)
#घोषणा MSA_CSR_CAUSE_IB	12
#घोषणा MSA_CSR_CAUSE_IF	(_ULCAST_(0x1) << MSA_CSR_CAUSE_IB)
#घोषणा MSA_CSR_CAUSE_UB	13
#घोषणा MSA_CSR_CAUSE_UF	(_ULCAST_(0x1) << MSA_CSR_CAUSE_UB)
#घोषणा MSA_CSR_CAUSE_OB	14
#घोषणा MSA_CSR_CAUSE_OF	(_ULCAST_(0x1) << MSA_CSR_CAUSE_OB)
#घोषणा MSA_CSR_CAUSE_ZB	15
#घोषणा MSA_CSR_CAUSE_ZF	(_ULCAST_(0x1) << MSA_CSR_CAUSE_ZB)
#घोषणा MSA_CSR_CAUSE_VB	16
#घोषणा MSA_CSR_CAUSE_VF	(_ULCAST_(0x1) << MSA_CSR_CAUSE_VB)
#घोषणा MSA_CSR_CAUSE_EB	17
#घोषणा MSA_CSR_CAUSE_EF	(_ULCAST_(0x1) << MSA_CSR_CAUSE_EB)
#घोषणा MSA_CSR_NXB		18
#घोषणा MSA_CSR_NXF		(_ULCAST_(0x1) << MSA_CSR_NXB)
#घोषणा MSA_CSR_FSB		24
#घोषणा MSA_CSR_FSF		(_ULCAST_(0x1) << MSA_CSR_FSB)

#पूर्ण_अगर /* _ASM_MSA_H */
