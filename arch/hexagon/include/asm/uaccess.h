<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * User memory access support क्रम Hexagon
 *
 * Copyright (c) 2010-2011, The Linux Foundation. All rights reserved.
 */

#अगर_अघोषित _ASM_UACCESS_H
#घोषणा _ASM_UACCESS_H
/*
 * User space memory access functions
 */
#समावेश <यंत्र/sections.h>

/*
 * access_ok: - Checks अगर a user space poपूर्णांकer is valid
 * @addr: User space poपूर्णांकer to start of block to check
 * @size: Size of block to check
 *
 * Context: User context only. This function may sleep अगर pagefaults are
 *          enabled.
 *
 * Checks अगर a poपूर्णांकer to a block of memory in user space is valid.
 *
 * Returns true (nonzero) अगर the memory block *may* be valid, false (zero)
 * अगर it is definitely invalid.
 *
 * User address space in Hexagon, like x86, goes to 0xbfffffff, so the
 * simple MSB-based tests used by MIPS won't work.  Some further
 * optimization is probably possible here, but क्रम now, keep it
 * reasonably simple and not *too* slow.  After all, we've got the
 * MMU क्रम backup.
 */

#घोषणा __access_ok(addr, size) \
	((get_fs().seg == KERNEL_DS.seg) || \
	(((अचिन्हित दीर्घ)addr < get_fs().seg) && \
	  (अचिन्हित दीर्घ)size < (get_fs().seg - (अचिन्हित दीर्घ)addr)))

/*
 * When a kernel-mode page fault is taken, the faulting inकाष्ठाion
 * address is checked against a table of exception_table_entries.
 * Each entry is a tuple of the address of an inकाष्ठाion that may
 * be authorized to fault, and the address at which execution should
 * be resumed instead of the faulting inकाष्ठाion, so as to effect
 * a workaround.
 */

/*  Assembly somewhat optimized copy routines  */
अचिन्हित दीर्घ raw_copy_from_user(व्योम *to, स्थिर व्योम __user *from,
				     अचिन्हित दीर्घ n);
अचिन्हित दीर्घ raw_copy_to_user(व्योम __user *to, स्थिर व्योम *from,
				   अचिन्हित दीर्घ n);
#घोषणा INLINE_COPY_FROM_USER
#घोषणा INLINE_COPY_TO_USER

__kernel_माप_प्रकार __clear_user_hexagon(व्योम __user *dest, अचिन्हित दीर्घ count);
#घोषणा __clear_user(a, s) __clear_user_hexagon((a), (s))

#घोषणा __म_नकलन_from_user(dst, src, n) hexagon_म_नकलन_from_user(dst, src, n)

/*  get around the अगरndef in यंत्र-generic/uaccess.h  */
#घोषणा __strnlen_user __strnlen_user

बाह्य दीर्घ __strnlen_user(स्थिर अक्षर __user *src, दीर्घ n);

अटल अंतरभूत दीर्घ hexagon_म_नकलन_from_user(अक्षर *dst, स्थिर अक्षर __user *src,
					     दीर्घ n);

#समावेश <यंत्र-generic/uaccess.h>

/*  Toकरो:  an actual accelerated version of this.  */
अटल अंतरभूत दीर्घ hexagon_म_नकलन_from_user(अक्षर *dst, स्थिर अक्षर __user *src,
					     दीर्घ n)
अणु
	दीर्घ res = __strnlen_user(src, n);

	अगर (unlikely(!res))
		वापस -EFAULT;

	अगर (res > n) अणु
		दीर्घ left = raw_copy_from_user(dst, src, n);
		अगर (unlikely(left))
			स_रखो(dst + (n - left), 0, left);
		वापस n;
	पूर्ण अन्यथा अणु
		दीर्घ left = raw_copy_from_user(dst, src, res);
		अगर (unlikely(left))
			स_रखो(dst + (res - left), 0, left);
		वापस res-1;
	पूर्ण
पूर्ण

#पूर्ण_अगर
