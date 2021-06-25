<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित ___ASM_SPARC_UACCESS_H
#घोषणा ___ASM_SPARC_UACCESS_H

#समावेश <यंत्र/extable.h>

#अगर defined(__sparc__) && defined(__arch64__)
#समावेश <यंत्र/uaccess_64.h>
#अन्यथा
#समावेश <यंत्र/uaccess_32.h>
#पूर्ण_अगर

#घोषणा user_addr_max() \
	(uaccess_kernel() ? ~0UL : TASK_SIZE)

दीर्घ म_नकलन_from_user(अक्षर *dest, स्थिर अक्षर __user *src, दीर्घ count);

#पूर्ण_अगर
