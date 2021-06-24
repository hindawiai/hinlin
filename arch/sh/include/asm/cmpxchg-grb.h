<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_SH_CMPXCHG_GRB_H
#घोषणा __ASM_SH_CMPXCHG_GRB_H

अटल अंतरभूत अचिन्हित दीर्घ xchg_u32(अस्थिर u32 *m, अचिन्हित दीर्घ val)
अणु
	अचिन्हित दीर्घ retval;

	__यंत्र__ __अस्थिर__ (
		"   .align 2              \n\t"
		"   mova    1f,   r0      \n\t" /* r0 = end poपूर्णांक */
		"   nop                   \n\t"
		"   mov    r15,   r1      \n\t" /* r1 = saved sp */
		"   mov    #-4,   r15     \n\t" /* LOGIN */
		"   mov.l  @%1,   %0      \n\t" /* load  old value */
		"   mov.l   %2,   @%1     \n\t" /* store new value */
		"1: mov     r1,   r15     \n\t" /* LOGOUT */
		: "=&r" (retval),
		  "+r"  (m),
		  "+r"  (val)		/* inhibit r15 overloading */
		:
		: "memory", "r0", "r1");

	वापस retval;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ xchg_u16(अस्थिर u16 *m, अचिन्हित दीर्घ val)
अणु
	अचिन्हित दीर्घ retval;

	__यंत्र__ __अस्थिर__ (
		"   .align  2             \n\t"
		"   mova    1f,   r0      \n\t" /* r0 = end poपूर्णांक */
		"   mov    r15,   r1      \n\t" /* r1 = saved sp */
		"   mov    #-6,   r15     \n\t" /* LOGIN */
		"   mov.w  @%1,   %0      \n\t" /* load  old value */
		"   extu.w  %0,   %0      \n\t" /* extend as अचिन्हित */
		"   mov.w   %2,   @%1     \n\t" /* store new value */
		"1: mov     r1,   r15     \n\t" /* LOGOUT */
		: "=&r" (retval),
		  "+r"  (m),
		  "+r"  (val)		/* inhibit r15 overloading */
		:
		: "memory" , "r0", "r1");

	वापस retval;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ xchg_u8(अस्थिर u8 *m, अचिन्हित दीर्घ val)
अणु
	अचिन्हित दीर्घ retval;

	__यंत्र__ __अस्थिर__ (
		"   .align  2             \n\t"
		"   mova    1f,   r0      \n\t" /* r0 = end poपूर्णांक */
		"   mov    r15,   r1      \n\t" /* r1 = saved sp */
		"   mov    #-6,   r15     \n\t" /* LOGIN */
		"   mov.b  @%1,   %0      \n\t" /* load  old value */
		"   extu.b  %0,   %0      \n\t" /* extend as अचिन्हित */
		"   mov.b   %2,   @%1     \n\t" /* store new value */
		"1: mov     r1,   r15     \n\t" /* LOGOUT */
		: "=&r" (retval),
		  "+r"  (m),
		  "+r"  (val)		/* inhibit r15 overloading */
		:
		: "memory" , "r0", "r1");

	वापस retval;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ __cmpxchg_u32(अस्थिर पूर्णांक *m, अचिन्हित दीर्घ old,
					  अचिन्हित दीर्घ new)
अणु
	अचिन्हित दीर्घ retval;

	__यंत्र__ __अस्थिर__ (
		"   .align  2             \n\t"
		"   mova    1f,   r0      \n\t" /* r0 = end poपूर्णांक */
		"   nop                   \n\t"
		"   mov    r15,   r1      \n\t" /* r1 = saved sp */
		"   mov    #-8,   r15     \n\t" /* LOGIN */
		"   mov.l  @%3,   %0      \n\t" /* load  old value */
		"   cmp/eq  %0,   %1      \n\t"
		"   bf            1f      \n\t" /* अगर not equal */
		"   mov.l   %2,   @%3     \n\t" /* store new value */
		"1: mov     r1,   r15     \n\t" /* LOGOUT */
		: "=&r" (retval),
		  "+r"  (old), "+r"  (new) /* old or new can be r15 */
		:  "r"  (m)
		: "memory" , "r0", "r1", "t");

	वापस retval;
पूर्ण

#पूर्ण_अगर /* __ASM_SH_CMPXCHG_GRB_H */
