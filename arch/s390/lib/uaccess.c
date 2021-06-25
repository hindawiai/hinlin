<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  Standard user space access functions based on mvcp/mvcs and करोing
 *  पूर्णांकeresting things in the secondary space mode.
 *
 *    Copyright IBM Corp. 2006,2014
 *    Author(s): Martin Schwidefsky (schwidefsky@de.ibm.com),
 *		 Gerald Schaefer (gerald.schaefer@de.ibm.com)
 */

#समावेश <linux/jump_label.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/export.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/mm.h>
#समावेश <यंत्र/mmu_context.h>
#समावेश <यंत्र/facility.h>

#अगर_घोषित CONFIG_DEBUG_ENTRY
व्योम debug_user_asce(पूर्णांक निकास)
अणु
	अचिन्हित दीर्घ cr1, cr7;

	__ctl_store(cr1, 1, 1);
	__ctl_store(cr7, 7, 7);
	अगर (cr1 == S390_lowcore.kernel_asce && cr7 == S390_lowcore.user_asce)
		वापस;
	panic("incorrect ASCE on kernel %s\n"
	      "cr1:    %016lx cr7:  %016lx\n"
	      "kernel: %016llx user: %016llx\n",
	      निकास ? "exit" : "entry", cr1, cr7,
	      S390_lowcore.kernel_asce, S390_lowcore.user_asce);

पूर्ण
#पूर्ण_अगर /*CONFIG_DEBUG_ENTRY */

#अगर_अघोषित CONFIG_HAVE_MARCH_Z10_FEATURES
अटल DEFINE_STATIC_KEY_FALSE(have_mvcos);

अटल पूर्णांक __init uaccess_init(व्योम)
अणु
	अगर (test_facility(27))
		अटल_branch_enable(&have_mvcos);
	वापस 0;
पूर्ण
early_initcall(uaccess_init);

अटल अंतरभूत पूर्णांक copy_with_mvcos(व्योम)
अणु
	अगर (अटल_branch_likely(&have_mvcos))
		वापस 1;
	वापस 0;
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक copy_with_mvcos(व्योम)
अणु
	वापस 1;
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत अचिन्हित दीर्घ copy_from_user_mvcos(व्योम *x, स्थिर व्योम __user *ptr,
						 अचिन्हित दीर्घ size)
अणु
	रेजिस्टर अचिन्हित दीर्घ reg0 यंत्र("0") = 0x81UL;
	अचिन्हित दीर्घ पंचांगp1, पंचांगp2;

	पंचांगp1 = -4096UL;
	यंत्र अस्थिर(
		"0: .insn ss,0xc80000000000,0(%0,%2),0(%1),0\n"
		"6: jz    4f\n"
		"1: algr  %0,%3\n"
		"   slgr  %1,%3\n"
		"   slgr  %2,%3\n"
		"   j     0b\n"
		"2: la    %4,4095(%1)\n"/* %4 = ptr + 4095 */
		"   nr    %4,%3\n"	/* %4 = (ptr + 4095) & -4096 */
		"   slgr  %4,%1\n"
		"   clgr  %0,%4\n"	/* copy crosses next page boundary? */
		"   jnh   5f\n"
		"3: .insn ss,0xc80000000000,0(%4,%2),0(%1),0\n"
		"7: slgr  %0,%4\n"
		"   j     5f\n"
		"4: slgr  %0,%0\n"
		"5:\n"
		EX_TABLE(0b,2b) EX_TABLE(3b,5b) EX_TABLE(6b,2b) EX_TABLE(7b,5b)
		: "+a" (size), "+a" (ptr), "+a" (x), "+a" (पंचांगp1), "=a" (पंचांगp2)
		: "d" (reg0) : "cc", "memory");
	वापस size;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ copy_from_user_mvcp(व्योम *x, स्थिर व्योम __user *ptr,
						अचिन्हित दीर्घ size)
अणु
	अचिन्हित दीर्घ पंचांगp1, पंचांगp2;

	पंचांगp1 = -256UL;
	यंत्र अस्थिर(
		"   sacf  0\n"
		"0: mvcp  0(%0,%2),0(%1),%3\n"
		"7: jz    5f\n"
		"1: algr  %0,%3\n"
		"   la    %1,256(%1)\n"
		"   la    %2,256(%2)\n"
		"2: mvcp  0(%0,%2),0(%1),%3\n"
		"8: jnz   1b\n"
		"   j     5f\n"
		"3: la    %4,255(%1)\n"	/* %4 = ptr + 255 */
		"   lghi  %3,-4096\n"
		"   nr    %4,%3\n"	/* %4 = (ptr + 255) & -4096 */
		"   slgr  %4,%1\n"
		"   clgr  %0,%4\n"	/* copy crosses next page boundary? */
		"   jnh   6f\n"
		"4: mvcp  0(%4,%2),0(%1),%3\n"
		"9: slgr  %0,%4\n"
		"   j     6f\n"
		"5: slgr  %0,%0\n"
		"6: sacf  768\n"
		EX_TABLE(0b,3b) EX_TABLE(2b,3b) EX_TABLE(4b,6b)
		EX_TABLE(7b,3b) EX_TABLE(8b,3b) EX_TABLE(9b,6b)
		: "+a" (size), "+a" (ptr), "+a" (x), "+a" (पंचांगp1), "=a" (पंचांगp2)
		: : "cc", "memory");
	वापस size;
पूर्ण

अचिन्हित दीर्घ raw_copy_from_user(व्योम *to, स्थिर व्योम __user *from, अचिन्हित दीर्घ n)
अणु
	अगर (copy_with_mvcos())
		वापस copy_from_user_mvcos(to, from, n);
	वापस copy_from_user_mvcp(to, from, n);
पूर्ण
EXPORT_SYMBOL(raw_copy_from_user);

अटल अंतरभूत अचिन्हित दीर्घ copy_to_user_mvcos(व्योम __user *ptr, स्थिर व्योम *x,
					       अचिन्हित दीर्घ size)
अणु
	रेजिस्टर अचिन्हित दीर्घ reg0 यंत्र("0") = 0x810000UL;
	अचिन्हित दीर्घ पंचांगp1, पंचांगp2;

	पंचांगp1 = -4096UL;
	यंत्र अस्थिर(
		"0: .insn ss,0xc80000000000,0(%0,%1),0(%2),0\n"
		"6: jz    4f\n"
		"1: algr  %0,%3\n"
		"   slgr  %1,%3\n"
		"   slgr  %2,%3\n"
		"   j     0b\n"
		"2: la    %4,4095(%1)\n"/* %4 = ptr + 4095 */
		"   nr    %4,%3\n"	/* %4 = (ptr + 4095) & -4096 */
		"   slgr  %4,%1\n"
		"   clgr  %0,%4\n"	/* copy crosses next page boundary? */
		"   jnh   5f\n"
		"3: .insn ss,0xc80000000000,0(%4,%1),0(%2),0\n"
		"7: slgr  %0,%4\n"
		"   j     5f\n"
		"4: slgr  %0,%0\n"
		"5:\n"
		EX_TABLE(0b,2b) EX_TABLE(3b,5b) EX_TABLE(6b,2b) EX_TABLE(7b,5b)
		: "+a" (size), "+a" (ptr), "+a" (x), "+a" (पंचांगp1), "=a" (पंचांगp2)
		: "d" (reg0) : "cc", "memory");
	वापस size;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ copy_to_user_mvcs(व्योम __user *ptr, स्थिर व्योम *x,
					      अचिन्हित दीर्घ size)
अणु
	अचिन्हित दीर्घ पंचांगp1, पंचांगp2;

	पंचांगp1 = -256UL;
	यंत्र अस्थिर(
		"   sacf  0\n"
		"0: mvcs  0(%0,%1),0(%2),%3\n"
		"7: jz    5f\n"
		"1: algr  %0,%3\n"
		"   la    %1,256(%1)\n"
		"   la    %2,256(%2)\n"
		"2: mvcs  0(%0,%1),0(%2),%3\n"
		"8: jnz   1b\n"
		"   j     5f\n"
		"3: la    %4,255(%1)\n" /* %4 = ptr + 255 */
		"   lghi  %3,-4096\n"
		"   nr    %4,%3\n"	/* %4 = (ptr + 255) & -4096 */
		"   slgr  %4,%1\n"
		"   clgr  %0,%4\n"	/* copy crosses next page boundary? */
		"   jnh   6f\n"
		"4: mvcs  0(%4,%1),0(%2),%3\n"
		"9: slgr  %0,%4\n"
		"   j     6f\n"
		"5: slgr  %0,%0\n"
		"6: sacf  768\n"
		EX_TABLE(0b,3b) EX_TABLE(2b,3b) EX_TABLE(4b,6b)
		EX_TABLE(7b,3b) EX_TABLE(8b,3b) EX_TABLE(9b,6b)
		: "+a" (size), "+a" (ptr), "+a" (x), "+a" (पंचांगp1), "=a" (पंचांगp2)
		: : "cc", "memory");
	वापस size;
पूर्ण

अचिन्हित दीर्घ raw_copy_to_user(व्योम __user *to, स्थिर व्योम *from, अचिन्हित दीर्घ n)
अणु
	अगर (copy_with_mvcos())
		वापस copy_to_user_mvcos(to, from, n);
	वापस copy_to_user_mvcs(to, from, n);
पूर्ण
EXPORT_SYMBOL(raw_copy_to_user);

अटल अंतरभूत अचिन्हित दीर्घ copy_in_user_mvcos(व्योम __user *to, स्थिर व्योम __user *from,
					       अचिन्हित दीर्घ size)
अणु
	रेजिस्टर अचिन्हित दीर्घ reg0 यंत्र("0") = 0x810081UL;
	अचिन्हित दीर्घ पंचांगp1, पंचांगp2;

	पंचांगp1 = -4096UL;
	/* FIXME: copy with reduced length. */
	यंत्र अस्थिर(
		"0: .insn ss,0xc80000000000,0(%0,%1),0(%2),0\n"
		"   jz	  2f\n"
		"1: algr  %0,%3\n"
		"   slgr  %1,%3\n"
		"   slgr  %2,%3\n"
		"   j	  0b\n"
		"2:slgr  %0,%0\n"
		"3: \n"
		EX_TABLE(0b,3b)
		: "+a" (size), "+a" (to), "+a" (from), "+a" (पंचांगp1), "=a" (पंचांगp2)
		: "d" (reg0) : "cc", "memory");
	वापस size;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ copy_in_user_mvc(व्योम __user *to, स्थिर व्योम __user *from,
					     अचिन्हित दीर्घ size)
अणु
	अचिन्हित दीर्घ पंचांगp1;

	यंत्र अस्थिर(
		"   sacf  256\n"
		"   aghi  %0,-1\n"
		"   jo	  5f\n"
		"   bras  %3,3f\n"
		"0: aghi  %0,257\n"
		"1: mvc	  0(1,%1),0(%2)\n"
		"   la	  %1,1(%1)\n"
		"   la	  %2,1(%2)\n"
		"   aghi  %0,-1\n"
		"   jnz	  1b\n"
		"   j	  5f\n"
		"2: mvc	  0(256,%1),0(%2)\n"
		"   la	  %1,256(%1)\n"
		"   la	  %2,256(%2)\n"
		"3: aghi  %0,-256\n"
		"   jnm	  2b\n"
		"4: ex	  %0,1b-0b(%3)\n"
		"5: slgr  %0,%0\n"
		"6: sacf  768\n"
		EX_TABLE(1b,6b) EX_TABLE(2b,0b) EX_TABLE(4b,0b)
		: "+a" (size), "+a" (to), "+a" (from), "=a" (पंचांगp1)
		: : "cc", "memory");
	वापस size;
पूर्ण

अचिन्हित दीर्घ raw_copy_in_user(व्योम __user *to, स्थिर व्योम __user *from, अचिन्हित दीर्घ n)
अणु
	अगर (copy_with_mvcos())
		वापस copy_in_user_mvcos(to, from, n);
	वापस copy_in_user_mvc(to, from, n);
पूर्ण
EXPORT_SYMBOL(raw_copy_in_user);

अटल अंतरभूत अचिन्हित दीर्घ clear_user_mvcos(व्योम __user *to, अचिन्हित दीर्घ size)
अणु
	रेजिस्टर अचिन्हित दीर्घ reg0 यंत्र("0") = 0x810000UL;
	अचिन्हित दीर्घ पंचांगp1, पंचांगp2;

	पंचांगp1 = -4096UL;
	यंत्र अस्थिर(
		"0: .insn ss,0xc80000000000,0(%0,%1),0(%4),0\n"
		"   jz	  4f\n"
		"1: algr  %0,%2\n"
		"   slgr  %1,%2\n"
		"   j	  0b\n"
		"2: la	  %3,4095(%1)\n"/* %4 = to + 4095 */
		"   nr	  %3,%2\n"	/* %4 = (to + 4095) & -4096 */
		"   slgr  %3,%1\n"
		"   clgr  %0,%3\n"	/* copy crosses next page boundary? */
		"   jnh	  5f\n"
		"3: .insn ss,0xc80000000000,0(%3,%1),0(%4),0\n"
		"   slgr  %0,%3\n"
		"   j	  5f\n"
		"4: slgr  %0,%0\n"
		"5:\n"
		EX_TABLE(0b,2b) EX_TABLE(3b,5b)
		: "+a" (size), "+a" (to), "+a" (पंचांगp1), "=a" (पंचांगp2)
		: "a" (empty_zero_page), "d" (reg0) : "cc", "memory");
	वापस size;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ clear_user_xc(व्योम __user *to, अचिन्हित दीर्घ size)
अणु
	अचिन्हित दीर्घ पंचांगp1, पंचांगp2;

	यंत्र अस्थिर(
		"   sacf  256\n"
		"   aghi  %0,-1\n"
		"   jo    5f\n"
		"   bras  %3,3f\n"
		"   xc    0(1,%1),0(%1)\n"
		"0: aghi  %0,257\n"
		"   la    %2,255(%1)\n" /* %2 = ptr + 255 */
		"   srl   %2,12\n"
		"   sll   %2,12\n"	/* %2 = (ptr + 255) & -4096 */
		"   slgr  %2,%1\n"
		"   clgr  %0,%2\n"	/* clear crosses next page boundary? */
		"   jnh   5f\n"
		"   aghi  %2,-1\n"
		"1: ex    %2,0(%3)\n"
		"   aghi  %2,1\n"
		"   slgr  %0,%2\n"
		"   j     5f\n"
		"2: xc    0(256,%1),0(%1)\n"
		"   la    %1,256(%1)\n"
		"3: aghi  %0,-256\n"
		"   jnm   2b\n"
		"4: ex    %0,0(%3)\n"
		"5: slgr  %0,%0\n"
		"6: sacf  768\n"
		EX_TABLE(1b,6b) EX_TABLE(2b,0b) EX_TABLE(4b,0b)
		: "+a" (size), "+a" (to), "=a" (पंचांगp1), "=a" (पंचांगp2)
		: : "cc", "memory");
	वापस size;
पूर्ण

अचिन्हित दीर्घ __clear_user(व्योम __user *to, अचिन्हित दीर्घ size)
अणु
	अगर (copy_with_mvcos())
			वापस clear_user_mvcos(to, size);
	वापस clear_user_xc(to, size);
पूर्ण
EXPORT_SYMBOL(__clear_user);

अटल अंतरभूत अचिन्हित दीर्घ strnlen_user_srst(स्थिर अक्षर __user *src,
					      अचिन्हित दीर्घ size)
अणु
	रेजिस्टर अचिन्हित दीर्घ reg0 यंत्र("0") = 0;
	अचिन्हित दीर्घ पंचांगp1, पंचांगp2;

	यंत्र अस्थिर(
		"   la    %2,0(%1)\n"
		"   la    %3,0(%0,%1)\n"
		"   slgr  %0,%0\n"
		"   sacf  256\n"
		"0: srst  %3,%2\n"
		"   jo    0b\n"
		"   la    %0,1(%3)\n"	/* strnlen_user results includes \0 */
		"   slgr  %0,%1\n"
		"1: sacf  768\n"
		EX_TABLE(0b,1b)
		: "+a" (size), "+a" (src), "=a" (पंचांगp1), "=a" (पंचांगp2)
		: "d" (reg0) : "cc", "memory");
	वापस size;
पूर्ण

अचिन्हित दीर्घ __strnlen_user(स्थिर अक्षर __user *src, अचिन्हित दीर्घ size)
अणु
	अगर (unlikely(!size))
		वापस 0;
	वापस strnlen_user_srst(src, size);
पूर्ण
EXPORT_SYMBOL(__strnlen_user);

दीर्घ __म_नकलन_from_user(अक्षर *dst, स्थिर अक्षर __user *src, दीर्घ size)
अणु
	माप_प्रकार करोne, len, offset, len_str;

	अगर (unlikely(size <= 0))
		वापस 0;
	करोne = 0;
	करो अणु
		offset = (माप_प्रकार)src & (L1_CACHE_BYTES - 1);
		len = min(size - करोne, L1_CACHE_BYTES - offset);
		अगर (copy_from_user(dst, src, len))
			वापस -EFAULT;
		len_str = strnlen(dst, len);
		करोne += len_str;
		src += len_str;
		dst += len_str;
	पूर्ण जबतक ((len_str == len) && (करोne < size));
	वापस करोne;
पूर्ण
EXPORT_SYMBOL(__म_नकलन_from_user);
