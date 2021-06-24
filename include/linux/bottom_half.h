<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_BH_H
#घोषणा _LINUX_BH_H

#समावेश <linux/preempt.h>

#अगर defined(CONFIG_PREEMPT_RT) || defined(CONFIG_TRACE_IRQFLAGS)
बाह्य व्योम __local_bh_disable_ip(अचिन्हित दीर्घ ip, अचिन्हित पूर्णांक cnt);
#अन्यथा
अटल __always_अंतरभूत व्योम __local_bh_disable_ip(अचिन्हित दीर्घ ip, अचिन्हित पूर्णांक cnt)
अणु
	preempt_count_add(cnt);
	barrier();
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत व्योम local_bh_disable(व्योम)
अणु
	__local_bh_disable_ip(_THIS_IP_, SOFTIRQ_DISABLE_OFFSET);
पूर्ण

बाह्य व्योम _local_bh_enable(व्योम);
बाह्य व्योम __local_bh_enable_ip(अचिन्हित दीर्घ ip, अचिन्हित पूर्णांक cnt);

अटल अंतरभूत व्योम local_bh_enable_ip(अचिन्हित दीर्घ ip)
अणु
	__local_bh_enable_ip(ip, SOFTIRQ_DISABLE_OFFSET);
पूर्ण

अटल अंतरभूत व्योम local_bh_enable(व्योम)
अणु
	__local_bh_enable_ip(_THIS_IP_, SOFTIRQ_DISABLE_OFFSET);
पूर्ण

#अगर_घोषित CONFIG_PREEMPT_RT
बाह्य bool local_bh_blocked(व्योम);
#अन्यथा
अटल अंतरभूत bool local_bh_blocked(व्योम) अणु वापस false; पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* _LINUX_BH_H */
