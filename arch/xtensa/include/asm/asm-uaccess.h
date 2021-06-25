<शैली गुरु>
/*
 * include/यंत्र-xtensa/uaccess.h
 *
 * User space memory access functions
 *
 * These routines provide basic accessing functions to the user memory
 * space क्रम the kernel. This header file provides functions such as:
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2001 - 2005 Tensilica Inc.
 */

#अगर_अघोषित _XTENSA_ASM_UACCESS_H
#घोषणा _XTENSA_ASM_UACCESS_H

#समावेश <linux/त्रुटिसं.स>
#समावेश <यंत्र/types.h>

#समावेश <यंत्र/current.h>
#समावेश <यंत्र/यंत्र-offsets.h>
#समावेश <यंत्र/processor.h>

/*
 * These assembly macros mirror the C macros in यंत्र/uaccess.h.  They
 * should always have identical functionality.  See
 * arch/xtensa/kernel/sys.S क्रम usage.
 */

#घोषणा KERNEL_DS	0
#घोषणा USER_DS		1

/*
 * get_fs पढ़ोs current->thपढ़ो.current_ds पूर्णांकo a रेजिस्टर.
 * On Entry:
 * 	<ad>	anything
 * 	<sp>	stack
 * On Exit:
 * 	<ad>	contains current->thपढ़ो.current_ds
 */
	.macro	get_fs	ad, sp
	GET_CURRENT(\चd,\sp)
#अगर THREAD_CURRENT_DS > 1020
	addi	\चd, \चd, TASK_THREAD
	l32i	\चd, \चd, THREAD_CURRENT_DS - TASK_THREAD
#अन्यथा
	l32i	\चd, \चd, THREAD_CURRENT_DS
#पूर्ण_अगर
	.endm

/*
 * set_fs sets current->thपढ़ो.current_ds to some value.
 * On Entry:
 *	<at>	anything (temp रेजिस्टर)
 *	<av>	value to ग_लिखो
 *	<sp>	stack
 * On Exit:
 *	<at>	destroyed (actually, current)
 *	<av>	preserved, value to ग_लिखो
 */
	.macro	set_fs	at, av, sp
	GET_CURRENT(\चt,\sp)
	s32i	\चv, \चt, THREAD_CURRENT_DS
	.endm

/*
 * kernel_ok determines whether we should bypass addr/size checking.
 * See the equivalent C-macro version below क्रम clarity.
 * On success, kernel_ok branches to a label indicated by parameter
 * <success>.  This implies that the macro falls through to the next
 * insruction on an error.
 *
 * Note that जबतक this macro can be used independently, we deचिन्हित
 * in क्रम optimal use in the access_ok macro below (i.e., we fall
 * through on error).
 *
 * On Entry:
 * 	<at>		anything (temp रेजिस्टर)
 * 	<success>	label to branch to on success; implies
 * 			fall-through macro on error
 * 	<sp>		stack poपूर्णांकer
 * On Exit:
 * 	<at>		destroyed (actually, current->thपढ़ो.current_ds)
 */

#अगर ((KERNEL_DS != 0) || (USER_DS == 0))
# error Assembly macro kernel_ok fails
#पूर्ण_अगर
	.macro	kernel_ok  at, sp, success
	get_fs	\चt, \sp
	beqz	\चt, \success
	.endm

/*
 * user_ok determines whether the access to user-space memory is allowed.
 * See the equivalent C-macro version below क्रम clarity.
 *
 * On error, user_ok branches to a label indicated by parameter
 * <error>.  This implies that the macro falls through to the next
 * inकाष्ठाion on success.
 *
 * Note that जबतक this macro can be used independently, we deचिन्हित
 * in क्रम optimal use in the access_ok macro below (i.e., we fall
 * through on success).
 *
 * On Entry:
 * 	<aa>	रेजिस्टर containing memory address
 * 	<as>	रेजिस्टर containing memory size
 * 	<at>	temp रेजिस्टर
 * 	<error>	label to branch to on error; implies fall-through
 * 		macro on success
 * On Exit:
 * 	<aa>	preserved
 * 	<as>	preserved
 * 	<at>	destroyed (actually, (TASK_SIZE + 1 - size))
 */
	.macro	user_ok	aa, as, at, error
	movi	\चt, __XTENSA_UL_CONST(TASK_SIZE)
	bgeu	\चs, \चt, \error
	sub	\चt, \चt, \चs
	bgeu	\चa, \चt, \error
	.endm

/*
 * access_ok determines whether a memory access is allowed.  See the
 * equivalent C-macro version below क्रम clarity.
 *
 * On error, access_ok branches to a label indicated by parameter
 * <error>.  This implies that the macro falls through to the next
 * inकाष्ठाion on success.
 *
 * Note that we assume success is the common हाल, and we optimize the
 * branch fall-through हाल on success.
 *
 * On Entry:
 * 	<aa>	रेजिस्टर containing memory address
 * 	<as>	रेजिस्टर containing memory size
 * 	<at>	temp रेजिस्टर
 * 	<sp>
 * 	<error>	label to branch to on error; implies fall-through
 * 		macro on success
 * On Exit:
 * 	<aa>	preserved
 * 	<as>	preserved
 * 	<at>	destroyed
 */
	.macro	access_ok  aa, as, at, sp, error
	kernel_ok  \चt, \sp, .Laccess_ok_\@
	user_ok    \चa, \चs, \चt, \error
.Laccess_ok_\@:
	.endm

#पूर्ण_अगर	/* _XTENSA_ASM_UACCESS_H */
