<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_SH_BITOPS_GRB_H
#घोषणा __ASM_SH_BITOPS_GRB_H

अटल अंतरभूत व्योम set_bit(पूर्णांक nr, अस्थिर व्योम * addr)
अणु
	पूर्णांक	mask;
	अस्थिर अचिन्हित पूर्णांक *a = addr;
	अचिन्हित दीर्घ पंचांगp;

	a += nr >> 5;
	mask = 1 << (nr & 0x1f);

        __यंत्र__ __अस्थिर__ (
                "   .align 2              \n\t"
                "   mova    1f,   r0      \n\t" /* r0 = end poपूर्णांक */
                "   mov    r15,   r1      \n\t" /* r1 = saved sp */
                "   mov    #-6,   r15     \n\t" /* LOGIN: r15 = size */
                "   mov.l  @%1,   %0      \n\t" /* load  old value */
                "   or      %2,   %0      \n\t" /* or */
                "   mov.l   %0,   @%1     \n\t" /* store new value */
                "1: mov     r1,   r15     \n\t" /* LOGOUT */
                : "=&r" (पंचांगp),
                  "+r"  (a)
                : "r"   (mask)
                : "memory" , "r0", "r1");
पूर्ण

अटल अंतरभूत व्योम clear_bit(पूर्णांक nr, अस्थिर व्योम * addr)
अणु
	पूर्णांक	mask;
	अस्थिर अचिन्हित पूर्णांक *a = addr;
        अचिन्हित दीर्घ पंचांगp;

	a += nr >> 5;
        mask = ~(1 << (nr & 0x1f));
        __यंत्र__ __अस्थिर__ (
                "   .align 2              \n\t"
                "   mova    1f,   r0      \n\t" /* r0 = end poपूर्णांक */
                "   mov    r15,   r1      \n\t" /* r1 = saved sp */
                "   mov    #-6,   r15     \n\t" /* LOGIN: r15 = size */
                "   mov.l  @%1,   %0      \n\t" /* load  old value */
                "   and     %2,   %0      \n\t" /* and */
                "   mov.l   %0,   @%1     \n\t" /* store new value */
                "1: mov     r1,   r15     \n\t" /* LOGOUT */
                : "=&r" (पंचांगp),
                  "+r"  (a)
                : "r"   (mask)
                : "memory" , "r0", "r1");
पूर्ण

अटल अंतरभूत व्योम change_bit(पूर्णांक nr, अस्थिर व्योम * addr)
अणु
        पूर्णांक     mask;
        अस्थिर अचिन्हित पूर्णांक *a = addr;
        अचिन्हित दीर्घ पंचांगp;

        a += nr >> 5;
        mask = 1 << (nr & 0x1f);
        __यंत्र__ __अस्थिर__ (
                "   .align 2              \n\t"
                "   mova    1f,   r0      \n\t" /* r0 = end poपूर्णांक */
                "   mov    r15,   r1      \n\t" /* r1 = saved sp */
                "   mov    #-6,   r15     \n\t" /* LOGIN: r15 = size */
                "   mov.l  @%1,   %0      \n\t" /* load  old value */
                "   xor     %2,   %0      \n\t" /* xor */
                "   mov.l   %0,   @%1     \n\t" /* store new value */
                "1: mov     r1,   r15     \n\t" /* LOGOUT */
                : "=&r" (पंचांगp),
                  "+r"  (a)
                : "r"   (mask)
                : "memory" , "r0", "r1");
पूर्ण

अटल अंतरभूत पूर्णांक test_and_set_bit(पूर्णांक nr, अस्थिर व्योम * addr)
अणु
        पूर्णांक     mask, retval;
	अस्थिर अचिन्हित पूर्णांक *a = addr;
        अचिन्हित दीर्घ पंचांगp;

	a += nr >> 5;
	mask = 1 << (nr & 0x1f);

        __यंत्र__ __अस्थिर__ (
                "   .align 2              \n\t"
                "   mova    1f,   r0      \n\t" /* r0 = end poपूर्णांक */
                "   mov    r15,   r1      \n\t" /* r1 = saved sp */
                "   mov   #-14,   r15     \n\t" /* LOGIN: r15 = size */
                "   mov.l  @%2,   %0      \n\t" /* load old value */
                "   mov     %0,   %1      \n\t"
                "   tst     %1,   %3      \n\t" /* T = ((*a & mask) == 0) */
                "   mov    #-1,   %1      \n\t" /* retvat = -1 */
                "   negc    %1,   %1      \n\t" /* retval = (mask & *a) != 0 */
                "   or      %3,   %0      \n\t"
                "   mov.l   %0,  @%2      \n\t" /* store new value */
                "1: mov     r1,  r15      \n\t" /* LOGOUT */
                : "=&r" (पंचांगp),
                  "=&r" (retval),
                  "+r"  (a)
                : "r"   (mask)
                : "memory" , "r0", "r1" ,"t");

        वापस retval;
पूर्ण

अटल अंतरभूत पूर्णांक test_and_clear_bit(पूर्णांक nr, अस्थिर व्योम * addr)
अणु
        पूर्णांक     mask, retval,not_mask;
        अस्थिर अचिन्हित पूर्णांक *a = addr;
        अचिन्हित दीर्घ पंचांगp;

        a += nr >> 5;
        mask = 1 << (nr & 0x1f);

	not_mask = ~mask;

        __यंत्र__ __अस्थिर__ (
                "   .align 2              \n\t"
		"   mova    1f,   r0      \n\t" /* r0 = end poपूर्णांक */
                "   mov    r15,   r1      \n\t" /* r1 = saved sp */
		"   mov   #-14,   r15     \n\t" /* LOGIN */
		"   mov.l  @%2,   %0      \n\t" /* load old value */
                "   mov     %0,   %1      \n\t" /* %1 = *a */
                "   tst     %1,   %3      \n\t" /* T = ((*a & mask) == 0) */
		"   mov    #-1,   %1      \n\t" /* retvat = -1 */
                "   negc    %1,   %1      \n\t" /* retval = (mask & *a) != 0 */
                "   and     %4,   %0      \n\t"
                "   mov.l   %0,  @%2      \n\t" /* store new value */
		"1: mov     r1,   r15     \n\t" /* LOGOUT */
		: "=&r" (पंचांगp),
		  "=&r" (retval),
		  "+r"  (a)
		: "r"   (mask),
		  "r"   (not_mask)
		: "memory" , "r0", "r1", "t");

        वापस retval;
पूर्ण

अटल अंतरभूत पूर्णांक test_and_change_bit(पूर्णांक nr, अस्थिर व्योम * addr)
अणु
        पूर्णांक     mask, retval;
        अस्थिर अचिन्हित पूर्णांक *a = addr;
        अचिन्हित दीर्घ पंचांगp;

        a += nr >> 5;
        mask = 1 << (nr & 0x1f);

        __यंत्र__ __अस्थिर__ (
                "   .align 2              \n\t"
                "   mova    1f,   r0      \n\t" /* r0 = end poपूर्णांक */
                "   mov    r15,   r1      \n\t" /* r1 = saved sp */
                "   mov   #-14,   r15     \n\t" /* LOGIN */
                "   mov.l  @%2,   %0      \n\t" /* load old value */
                "   mov     %0,   %1      \n\t" /* %1 = *a */
                "   tst     %1,   %3      \n\t" /* T = ((*a & mask) == 0) */
                "   mov    #-1,   %1      \n\t" /* retvat = -1 */
                "   negc    %1,   %1      \n\t" /* retval = (mask & *a) != 0 */
                "   xor     %3,   %0      \n\t"
                "   mov.l   %0,  @%2      \n\t" /* store new value */
                "1: mov     r1,   r15     \n\t" /* LOGOUT */
                : "=&r" (पंचांगp),
                  "=&r" (retval),
                  "+r"  (a)
                : "r"   (mask)
                : "memory" , "r0", "r1", "t");

        वापस retval;
पूर्ण

#समावेश <यंत्र-generic/bitops/non-atomic.h>

#पूर्ण_अगर /* __ASM_SH_BITOPS_GRB_H */
