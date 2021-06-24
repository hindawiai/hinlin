<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_X86_RMWcc
#घोषणा _ASM_X86_RMWcc

/* This counts to 12. Any more, it will वापस 13th argument. */
#घोषणा __RMWcc_ARGS(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _n, X...) _n
#घोषणा RMWcc_ARGS(X...) __RMWcc_ARGS(, ##X, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0)

#घोषणा __RMWcc_CONCAT(a, b) a ## b
#घोषणा RMWcc_CONCAT(a, b) __RMWcc_CONCAT(a, b)

#घोषणा __CLOBBERS_MEM(clb...)	"memory", ## clb

#अगर !defined(__GCC_ASM_FLAG_OUTPUTS__) && defined(CONFIG_CC_HAS_ASM_GOTO)

/* Use यंत्र जाओ */

#घोषणा __GEN_RMWcc(fullop, _var, cc, clobbers, ...)			\
(अणु									\
	bool c = false;							\
	यंत्र_अस्थिर_जाओ (fullop "; j" #cc " %l[cc_label]"		\
			: : [var] "m" (_var), ## __VA_ARGS__		\
			: clobbers : cc_label);				\
	अगर (0) अणु							\
cc_label:	c = true;						\
	पूर्ण								\
	c;								\
पूर्ण)

#अन्यथा /* defined(__GCC_ASM_FLAG_OUTPUTS__) || !defined(CONFIG_CC_HAS_ASM_GOTO) */

/* Use flags output or a set inकाष्ठाion */

#घोषणा __GEN_RMWcc(fullop, _var, cc, clobbers, ...)			\
(अणु									\
	bool c;								\
	यंत्र अस्थिर (fullop CC_SET(cc)					\
			: [var] "+m" (_var), CC_OUT(cc) (c)		\
			: __VA_ARGS__ : clobbers);			\
	c;								\
पूर्ण)

#पूर्ण_अगर /* defined(__GCC_ASM_FLAG_OUTPUTS__) || !defined(CONFIG_CC_HAS_ASM_GOTO) */

#घोषणा GEN_UNARY_RMWcc_4(op, var, cc, arg0)				\
	__GEN_RMWcc(op " " arg0, var, cc, __CLOBBERS_MEM())

#घोषणा GEN_UNARY_RMWcc_3(op, var, cc)					\
	GEN_UNARY_RMWcc_4(op, var, cc, "%[var]")

#घोषणा GEN_UNARY_RMWcc(X...) RMWcc_CONCAT(GEN_UNARY_RMWcc_, RMWcc_ARGS(X))(X)

#घोषणा GEN_BINARY_RMWcc_6(op, var, cc, vcon, _val, arg0)		\
	__GEN_RMWcc(op " %[val], " arg0, var, cc,			\
		    __CLOBBERS_MEM(), [val] vcon (_val))

#घोषणा GEN_BINARY_RMWcc_5(op, var, cc, vcon, val)			\
	GEN_BINARY_RMWcc_6(op, var, cc, vcon, val, "%[var]")

#घोषणा GEN_BINARY_RMWcc(X...) RMWcc_CONCAT(GEN_BINARY_RMWcc_, RMWcc_ARGS(X))(X)

#घोषणा GEN_UNARY_SUFFIXED_RMWcc(op, suffix, var, cc, clobbers...)	\
	__GEN_RMWcc(op " %[var]\n\t" suffix, var, cc,			\
		    __CLOBBERS_MEM(clobbers))

#घोषणा GEN_BINARY_SUFFIXED_RMWcc(op, suffix, var, cc, vcon, _val, clobbers...)\
	__GEN_RMWcc(op " %[val], %[var]\n\t" suffix, var, cc,		\
		    __CLOBBERS_MEM(clobbers), [val] vcon (_val))

#पूर्ण_अगर /* _ASM_X86_RMWcc */
