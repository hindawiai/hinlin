<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (C) 2015 Imagination Technologies
 * Author: Alex Smith <alex.smith@imgtec.com>
 */

#समावेश <यंत्र/sgidefs.h>

#अगर_अघोषित __ASSEMBLY__

#समावेश <यंत्र/यंत्र.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/vdso.h>

अटल अंतरभूत अचिन्हित दीर्घ get_vdso_base(व्योम)
अणु
	अचिन्हित दीर्घ addr;

	/*
	 * We can't use cpu_has_mips_r6 since it needs the cpu_data[]
	 * kernel symbol.
	 */
#अगर_घोषित CONFIG_CPU_MIPSR6
	/*
	 * lapc <symbol> is an alias to addiupc reg, <symbol> - .
	 *
	 * We can't use addiupc because there is no label-label
	 * support क्रम the addiupc reloc
	 */
	__यंत्र__("lapc	%0, _start			\n"
		: "=r" (addr) : :);
#अन्यथा
	/*
	 * Get the base load address of the VDSO. We have to aव्योम generating
	 * relocations and references to the GOT because ld.so करोes not peक्रमm
	 * relocations on the VDSO. We use the current offset from the VDSO base
	 * and perक्रमm a PC-relative branch which gives the असलolute address in
	 * ra, and take the dअगरference. The assembler chokes on
	 * "li %0, _start - .", so embed the offset as a word and branch over
	 * it.
	 *
	 */

	__यंत्र__(
	"	.set push				\n"
	"	.set noreorder				\n"
	"	bal	1f				\n"
	"	 nop					\n"
	"	.word	_start - .			\n"
	"1:	lw	%0, 0($31)			\n"
	"	" STR(PTR_ADDU) " %0, $31, %0		\n"
	"	.set pop				\n"
	: "=r" (addr)
	:
	: "$31");
#पूर्ण_अगर /* CONFIG_CPU_MIPSR6 */

	वापस addr;
पूर्ण

अटल अंतरभूत स्थिर काष्ठा vdso_data *get_vdso_data(व्योम)
अणु
	वापस (स्थिर काष्ठा vdso_data *)(get_vdso_base() - PAGE_SIZE);
पूर्ण

#अगर_घोषित CONFIG_CLKSRC_MIPS_GIC

अटल अंतरभूत व्योम __iomem *get_gic(स्थिर काष्ठा vdso_data *data)
अणु
	वापस (व्योम __iomem *)data - PAGE_SIZE;
पूर्ण

#पूर्ण_अगर /* CONFIG_CLKSRC_MIPS_GIC */

#पूर्ण_अगर /* __ASSEMBLY__ */
