<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/* स्थिर.h: Macros क्रम dealing with स्थिरants.  */

#अगर_अघोषित _UAPI_LINUX_CONST_H
#घोषणा _UAPI_LINUX_CONST_H

/* Some स्थिरant macros are used in both assembler and
 * C code.  Thereक्रमe we cannot annotate them always with
 * 'UL' and other type specअगरiers unilaterally.  We
 * use the following macros to deal with this.
 *
 * Similarly, _AT() will cast an expression with a type in C, but
 * leave it unchanged in यंत्र.
 */

#अगर_घोषित __ASSEMBLY__
#घोषणा _AC(X,Y)	X
#घोषणा _AT(T,X)	X
#अन्यथा
#घोषणा __AC(X,Y)	(X##Y)
#घोषणा _AC(X,Y)	__AC(X,Y)
#घोषणा _AT(T,X)	((T)(X))
#पूर्ण_अगर

#घोषणा _UL(x)		(_AC(x, UL))
#घोषणा _ULL(x)		(_AC(x, ULL))

#घोषणा _BITUL(x)	(_UL(1) << (x))
#घोषणा _BITULL(x)	(_ULL(1) << (x))

#घोषणा __ALIGN_KERNEL(x, a)		__ALIGN_KERNEL_MASK(x, (typeof(x))(a) - 1)
#घोषणा __ALIGN_KERNEL_MASK(x, mask)	(((x) + (mask)) & ~(mask))

#घोषणा __KERNEL_DIV_ROUND_UP(n, d) (((n) + (d) - 1) / (d))

#पूर्ण_अगर /* _UAPI_LINUX_CONST_H */
