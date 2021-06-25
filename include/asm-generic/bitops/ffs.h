<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_GENERIC_BITOPS_FFS_H_
#घोषणा _ASM_GENERIC_BITOPS_FFS_H_

/**
 * ffs - find first bit set
 * @x: the word to search
 *
 * This is defined the same way as
 * the libc and compiler builtin ffs routines, thereक्रमe
 * dअगरfers in spirit from the above ffz (man ffs).
 */
अटल अंतरभूत पूर्णांक ffs(पूर्णांक x)
अणु
	पूर्णांक r = 1;

	अगर (!x)
		वापस 0;
	अगर (!(x & 0xffff)) अणु
		x >>= 16;
		r += 16;
	पूर्ण
	अगर (!(x & 0xff)) अणु
		x >>= 8;
		r += 8;
	पूर्ण
	अगर (!(x & 0xf)) अणु
		x >>= 4;
		r += 4;
	पूर्ण
	अगर (!(x & 3)) अणु
		x >>= 2;
		r += 2;
	पूर्ण
	अगर (!(x & 1)) अणु
		x >>= 1;
		r += 1;
	पूर्ण
	वापस r;
पूर्ण

#पूर्ण_अगर /* _ASM_GENERIC_BITOPS_FFS_H_ */
