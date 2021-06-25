<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _PERF_ASM_UACCESS_H_
#घोषणा _PERF_ASM_UACCESS_H_

#घोषणा __get_user(src, dest)						\
(अणु									\
	(src) = *dest;							\
	0;								\
पूर्ण)

#घोषणा get_user	__get_user

#घोषणा access_ok(addr, size)	1

#पूर्ण_अगर
