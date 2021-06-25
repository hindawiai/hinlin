<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_GENERIC_BITOPS_FLS_H_
#घोषणा _ASM_GENERIC_BITOPS_FLS_H_

/**
 * fls - find last (most-signअगरicant) bit set
 * @x: the word to search
 *
 * This is defined the same way as ffs.
 * Note fls(0) = 0, fls(1) = 1, fls(0x80000000) = 32.
 */

अटल __always_अंतरभूत पूर्णांक fls(अचिन्हित पूर्णांक x)
अणु
	पूर्णांक r = 32;

	अगर (!x)
		वापस 0;
	अगर (!(x & 0xffff0000u)) अणु
		x <<= 16;
		r -= 16;
	पूर्ण
	अगर (!(x & 0xff000000u)) अणु
		x <<= 8;
		r -= 8;
	पूर्ण
	अगर (!(x & 0xf0000000u)) अणु
		x <<= 4;
		r -= 4;
	पूर्ण
	अगर (!(x & 0xc0000000u)) अणु
		x <<= 2;
		r -= 2;
	पूर्ण
	अगर (!(x & 0x80000000u)) अणु
		x <<= 1;
		r -= 1;
	पूर्ण
	वापस r;
पूर्ण

#पूर्ण_अगर /* _ASM_GENERIC_BITOPS_FLS_H_ */
