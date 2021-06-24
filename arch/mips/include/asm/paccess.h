<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 1996, 1997, 1998, 1999, 2000 by Ralf Baechle
 * Copyright (C) 1999, 2000 Silicon Graphics, Inc.
 *
 * Protected memory access.  Used क्रम everything that might take revenge
 * by sending a DBE error like accessing possibly non-existent memory or
 * devices.
 */
#अगर_अघोषित _ASM_PACCESS_H
#घोषणा _ASM_PACCESS_H

#समावेश <linux/त्रुटिसं.स>

#अगर_घोषित CONFIG_32BIT
#घोषणा __PA_ADDR	".word"
#पूर्ण_अगर
#अगर_घोषित CONFIG_64BIT
#घोषणा __PA_ADDR	".dword"
#पूर्ण_अगर

बाह्य यंत्रlinkage व्योम handle_ibe(व्योम);
बाह्य यंत्रlinkage व्योम handle_dbe(व्योम);

#घोषणा put_dbe(x, ptr) __put_dbe((x), (ptr), माप(*(ptr)))
#घोषणा get_dbe(x, ptr) __get_dbe((x), (ptr), माप(*(ptr)))

काष्ठा __large_pकाष्ठा अणु अचिन्हित दीर्घ buf[100]; पूर्ण;
#घोषणा __mp(x) (*(काष्ठा __large_pकाष्ठा *)(x))

#घोषणा __get_dbe(x, ptr, size)						\
(अणु									\
	दीर्घ __gu_err;							\
	__typeof__(*(ptr)) __gu_val;					\
	अचिन्हित दीर्घ __gu_addr;					\
	__यंत्र__("":"=r" (__gu_val));					\
	__gu_addr = (अचिन्हित दीर्घ) (ptr);				\
	__यंत्र__("":"=r" (__gu_err));					\
	चयन (size) अणु							\
	हाल 1: __get_dbe_यंत्र("lb"); अवरोध;				\
	हाल 2: __get_dbe_यंत्र("lh"); अवरोध;				\
	हाल 4: __get_dbe_यंत्र("lw"); अवरोध;				\
	हाल 8:	 __get_dbe_यंत्र("ld"); अवरोध;				\
	शेष: __get_dbe_unknown(); अवरोध;				\
	पूर्ण								\
	x = (__typeof__(*(ptr))) __gu_val;				\
	__gu_err;							\
पूर्ण)

#घोषणा __get_dbe_यंत्र(insn)						\
अणु									\
	__यंत्र__ __अस्थिर__(						\
	"1:\t" insn "\t%1,%2\n\t"					\
	"move\t%0,$0\n"							\
	"2:\n\t"							\
	".insn\n\t"							\
	".section\t.fixup,\"ax\"\n"					\
	"3:\tli\t%0,%3\n\t"						\
	"move\t%1,$0\n\t"						\
	"j\t2b\n\t"							\
	".previous\n\t"							\
	".section\t__dbe_table,\"a\"\n\t"				\
	__PA_ADDR "\t1b, 3b\n\t"					\
	".previous"							\
	:"=r" (__gu_err), "=r" (__gu_val)				\
	:"o" (__mp(__gu_addr)), "i" (-EFAULT));				\
पूर्ण

बाह्य व्योम __get_dbe_unknown(व्योम);

#घोषणा __put_dbe(x, ptr, size)						\
(अणु									\
	दीर्घ __pu_err;							\
	__typeof__(*(ptr)) __pu_val;					\
	दीर्घ __pu_addr;							\
	__pu_val = (x);							\
	__pu_addr = (दीर्घ) (ptr);					\
	__यंत्र__("":"=r" (__pu_err));					\
	चयन (size) अणु							\
	हाल 1: __put_dbe_यंत्र("sb"); अवरोध;				\
	हाल 2: __put_dbe_यंत्र("sh"); अवरोध;				\
	हाल 4: __put_dbe_यंत्र("sw"); अवरोध;				\
	हाल 8: __put_dbe_यंत्र("sd"); अवरोध;				\
	शेष: __put_dbe_unknown(); अवरोध;				\
	पूर्ण								\
	__pu_err;							\
पूर्ण)

#घोषणा __put_dbe_यंत्र(insn)						\
अणु									\
	__यंत्र__ __अस्थिर__(						\
	"1:\t" insn "\t%1,%2\n\t"					\
	"move\t%0,$0\n"							\
	"2:\n\t"							\
	".insn\n\t"							\
	".section\t.fixup,\"ax\"\n"					\
	"3:\tli\t%0,%3\n\t"						\
	"j\t2b\n\t"							\
	".previous\n\t"							\
	".section\t__dbe_table,\"a\"\n\t"				\
	__PA_ADDR "\t1b, 3b\n\t"					\
	".previous"							\
	: "=r" (__pu_err)						\
	: "r" (__pu_val), "o" (__mp(__pu_addr)), "i" (-EFAULT));	\
पूर्ण

बाह्य व्योम __put_dbe_unknown(व्योम);

बाह्य अचिन्हित दीर्घ search_dbe_table(अचिन्हित दीर्घ addr);

#पूर्ण_अगर /* _ASM_PACCESS_H */
