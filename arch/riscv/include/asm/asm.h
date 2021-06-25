<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2015 Regents of the University of Calअगरornia
 */

#अगर_अघोषित _ASM_RISCV_ASM_H
#घोषणा _ASM_RISCV_ASM_H

#अगर_घोषित __ASSEMBLY__
#घोषणा __ASM_STR(x)	x
#अन्यथा
#घोषणा __ASM_STR(x)	#x
#पूर्ण_अगर

#अगर __riscv_xlen == 64
#घोषणा __REG_SEL(a, b)	__ASM_STR(a)
#या_अगर __riscv_xlen == 32
#घोषणा __REG_SEL(a, b)	__ASM_STR(b)
#अन्यथा
#त्रुटि "Unexpected __riscv_xlen"
#पूर्ण_अगर

#घोषणा REG_L		__REG_SEL(ld, lw)
#घोषणा REG_S		__REG_SEL(sd, sw)
#घोषणा REG_SC		__REG_SEL(sc.d, sc.w)
#घोषणा REG_ASM		__REG_SEL(.dword, .word)
#घोषणा SZREG		__REG_SEL(8, 4)
#घोषणा LGREG		__REG_SEL(3, 2)

#अगर __SIZखातापूर्ण_POINTER__ == 8
#अगर_घोषित __ASSEMBLY__
#घोषणा RISCV_PTR		.dword
#घोषणा RISCV_SZPTR		8
#घोषणा RISCV_LGPTR		3
#अन्यथा
#घोषणा RISCV_PTR		".dword"
#घोषणा RISCV_SZPTR		"8"
#घोषणा RISCV_LGPTR		"3"
#पूर्ण_अगर
#या_अगर __SIZखातापूर्ण_POINTER__ == 4
#अगर_घोषित __ASSEMBLY__
#घोषणा RISCV_PTR		.word
#घोषणा RISCV_SZPTR		4
#घोषणा RISCV_LGPTR		2
#अन्यथा
#घोषणा RISCV_PTR		".word"
#घोषणा RISCV_SZPTR		"4"
#घोषणा RISCV_LGPTR		"2"
#पूर्ण_अगर
#अन्यथा
#त्रुटि "Unexpected __SIZEOF_POINTER__"
#पूर्ण_अगर

#अगर (__SIZखातापूर्ण_INT__ == 4)
#घोषणा RISCV_INT		__ASM_STR(.word)
#घोषणा RISCV_SZINT		__ASM_STR(4)
#घोषणा RISCV_LGINT		__ASM_STR(2)
#अन्यथा
#त्रुटि "Unexpected __SIZEOF_INT__"
#पूर्ण_अगर

#अगर (__SIZखातापूर्ण_SHORT__ == 2)
#घोषणा RISCV_SHORT		__ASM_STR(.half)
#घोषणा RISCV_SZSHORT		__ASM_STR(2)
#घोषणा RISCV_LGSHORT		__ASM_STR(1)
#अन्यथा
#त्रुटि "Unexpected __SIZEOF_SHORT__"
#पूर्ण_अगर

#पूर्ण_अगर /* _ASM_RISCV_ASM_H */
