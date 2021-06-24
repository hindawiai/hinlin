<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *  Copyright IBM Corp. 2014
 *
 *  Author: Martin Schwidefsky <schwidefsky@de.ibm.com>
 */

#अगर_अघोषित _S390_IDLE_H
#घोषणा _S390_IDLE_H

#समावेश <linux/types.h>
#समावेश <linux/device.h>
#समावेश <linux/seqlock.h>

काष्ठा s390_idle_data अणु
	seqcount_t seqcount;
	अचिन्हित दीर्घ idle_count;
	अचिन्हित दीर्घ idle_समय;
	अचिन्हित दीर्घ घड़ी_idle_enter;
	अचिन्हित दीर्घ घड़ी_idle_निकास;
	अचिन्हित दीर्घ समयr_idle_enter;
	अचिन्हित दीर्घ समयr_idle_निकास;
	अचिन्हित दीर्घ mt_cycles_enter[8];
पूर्ण;

बाह्य काष्ठा device_attribute dev_attr_idle_count;
बाह्य काष्ठा device_attribute dev_attr_idle_समय_us;

व्योम psw_idle(काष्ठा s390_idle_data *data, अचिन्हित दीर्घ psw_mask);
व्योम psw_idle_निकास(व्योम);

#पूर्ण_अगर /* _S390_IDLE_H */
