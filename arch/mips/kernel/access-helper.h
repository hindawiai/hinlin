<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

#समावेश <linux/uaccess.h>

अटल अंतरभूत पूर्णांक __get_addr(अचिन्हित दीर्घ *a, अचिन्हित दीर्घ *p, bool user)
अणु
	वापस user ? get_user(*a, (अचिन्हित दीर्घ __user *)p) :
		      get_kernel_nofault(*a, p);
पूर्ण

अटल अंतरभूत पूर्णांक __get_inst16(u16 *i, u16 *p, bool user)
अणु
	वापस user ? get_user(*i, (u16 __user *)p) : get_kernel_nofault(*i, p);
पूर्ण

अटल अंतरभूत पूर्णांक __get_inst32(u32 *i, u32 *p, bool user)
अणु
	वापस user ? get_user(*i, (u32 __user *)p) : get_kernel_nofault(*i, p);
पूर्ण
