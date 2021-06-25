<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only

#समावेश <linux/uaccess.h>
#समावेश <linux/kernel.h>

bool copy_from_kernel_nofault_allowed(स्थिर व्योम *unsafe_src, माप_प्रकार size)
अणु
	/* highest bit set means kernel space */
	वापस (अचिन्हित दीर्घ)unsafe_src >> (BITS_PER_LONG - 1);
पूर्ण
