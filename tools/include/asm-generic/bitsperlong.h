<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_GENERIC_BITS_PER_LONG
#घोषणा __ASM_GENERIC_BITS_PER_LONG

#समावेश <uapi/यंत्र-generic/bitsperदीर्घ.h>

#अगर_घोषित __SIZखातापूर्ण_LONG__
#घोषणा BITS_PER_LONG (__अक्षर_बिट__ * __SIZखातापूर्ण_LONG__)
#अन्यथा
#घोषणा BITS_PER_LONG __WORDSIZE
#पूर्ण_अगर

#अगर BITS_PER_LONG != __BITS_PER_LONG
#त्रुटि Inconsistent word size. Check यंत्र/bitsperदीर्घ.h
#पूर्ण_अगर

#अगर_अघोषित BITS_PER_LONG_LONG
#घोषणा BITS_PER_LONG_LONG 64
#पूर्ण_अगर

#घोषणा small_स्थिर_nbits(nbits) \
	(__builtin_स्थिरant_p(nbits) && (nbits) <= BITS_PER_LONG && (nbits) > 0)

#पूर्ण_अगर /* __ASM_GENERIC_BITS_PER_LONG */
