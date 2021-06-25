<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_LINKAGE_H
#घोषणा __ASM_LINKAGE_H

#घोषणा __ALIGN .align 4
#घोषणा __ALIGN_STR ".align 4"

/*
 * Make sure the compiler करोesn't करो anything stupid with the
 * arguments on the stack - they are owned by the *caller*, not
 * the callee. This just fools gcc पूर्णांकo not spilling पूर्णांकo them,
 * and keeps it from करोing tailcall recursion and/or using the
 * stack slots क्रम temporaries, since they are live and "used"
 * all the way to the end of the function.
 */
#घोषणा यंत्रlinkage_protect(n, ret, args...) \
	__यंत्रlinkage_protect##n(ret, ##args)
#घोषणा __यंत्रlinkage_protect_n(ret, args...) \
	__यंत्र__ __अस्थिर__ ("" : "=r" (ret) : "0" (ret), ##args)
#घोषणा __यंत्रlinkage_protect0(ret) \
	__यंत्रlinkage_protect_n(ret)
#घोषणा __यंत्रlinkage_protect1(ret, arg1) \
	__यंत्रlinkage_protect_n(ret, "m" (arg1))
#घोषणा __यंत्रlinkage_protect2(ret, arg1, arg2) \
	__यंत्रlinkage_protect_n(ret, "m" (arg1), "m" (arg2))
#घोषणा __यंत्रlinkage_protect3(ret, arg1, arg2, arg3) \
	__यंत्रlinkage_protect_n(ret, "m" (arg1), "m" (arg2), "m" (arg3))
#घोषणा __यंत्रlinkage_protect4(ret, arg1, arg2, arg3, arg4) \
	__यंत्रlinkage_protect_n(ret, "m" (arg1), "m" (arg2), "m" (arg3), \
			      "m" (arg4))
#घोषणा __यंत्रlinkage_protect5(ret, arg1, arg2, arg3, arg4, arg5) \
	__यंत्रlinkage_protect_n(ret, "m" (arg1), "m" (arg2), "m" (arg3), \
			      "m" (arg4), "m" (arg5))
#घोषणा __यंत्रlinkage_protect6(ret, arg1, arg2, arg3, arg4, arg5, arg6) \
	__यंत्रlinkage_protect_n(ret, "m" (arg1), "m" (arg2), "m" (arg3), \
			      "m" (arg4), "m" (arg5), "m" (arg6))

#पूर्ण_अगर
