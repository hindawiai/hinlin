<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *  Copyright IBM Corp. 2003, 2012
 *  Virtual CPU समयr
 *
 *  Author(s): Jan Glauber <jan.glauber@de.ibm.com>
 */

#अगर_अघोषित _ASM_S390_TIMER_H
#घोषणा _ASM_S390_TIMER_H

#घोषणा VTIMER_MAX_SLICE (0x7fffffffffffffffULL)

काष्ठा vसमयr_list अणु
	काष्ठा list_head entry;
	u64 expires;
	u64 पूर्णांकerval;
	व्योम (*function)(अचिन्हित दीर्घ);
	अचिन्हित दीर्घ data;
पूर्ण;

बाह्य व्योम init_virt_समयr(काष्ठा vसमयr_list *समयr);
बाह्य व्योम add_virt_समयr(काष्ठा vसमयr_list *समयr);
बाह्य व्योम add_virt_समयr_periodic(काष्ठा vसमयr_list *समयr);
बाह्य पूर्णांक mod_virt_समयr(काष्ठा vसमयr_list *समयr, u64 expires);
बाह्य पूर्णांक mod_virt_समयr_periodic(काष्ठा vसमयr_list *समयr, u64 expires);
बाह्य पूर्णांक del_virt_समयr(काष्ठा vसमयr_list *समयr);
बाह्य व्योम vसमय_init(व्योम);

#पूर्ण_अगर /* _ASM_S390_TIMER_H */
