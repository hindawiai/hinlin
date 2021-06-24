<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_X86_NMI_H
#घोषणा _ASM_X86_NMI_H

#समावेश <linux/irq_work.h>
#समावेश <linux/pm.h>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/पन.स>

#अगर_घोषित CONFIG_X86_LOCAL_APIC

बाह्य पूर्णांक reserve_perfctr_nmi(अचिन्हित पूर्णांक);
बाह्य व्योम release_perfctr_nmi(अचिन्हित पूर्णांक);
बाह्य पूर्णांक reserve_evntsel_nmi(अचिन्हित पूर्णांक);
बाह्य व्योम release_evntsel_nmi(अचिन्हित पूर्णांक);

काष्ठा ctl_table;
बाह्य पूर्णांक proc_nmi_enabled(काष्ठा ctl_table *, पूर्णांक ,
			व्योम __user *, माप_प्रकार *, loff_t *);
बाह्य पूर्णांक unknown_nmi_panic;

#पूर्ण_अगर /* CONFIG_X86_LOCAL_APIC */

#घोषणा NMI_FLAG_FIRST	1

क्रमागत अणु
	NMI_LOCAL=0,
	NMI_UNKNOWN,
	NMI_SERR,
	NMI_IO_CHECK,
	NMI_MAX
पूर्ण;

#घोषणा NMI_DONE	0
#घोषणा NMI_HANDLED	1

प्रकार पूर्णांक (*nmi_handler_t)(अचिन्हित पूर्णांक, काष्ठा pt_regs *);

काष्ठा nmiaction अणु
	काष्ठा list_head	list;
	nmi_handler_t		handler;
	u64			max_duration;
	अचिन्हित दीर्घ		flags;
	स्थिर अक्षर		*name;
पूर्ण;

#घोषणा रेजिस्टर_nmi_handler(t, fn, fg, n, init...)	\
(अणु							\
	अटल काष्ठा nmiaction init fn##_na = अणु	\
		.handler = (fn),			\
		.name = (n),				\
		.flags = (fg),				\
	पूर्ण;						\
	__रेजिस्टर_nmi_handler((t), &fn##_na);		\
पूर्ण)

पूर्णांक __रेजिस्टर_nmi_handler(अचिन्हित पूर्णांक, काष्ठा nmiaction *);

व्योम unरेजिस्टर_nmi_handler(अचिन्हित पूर्णांक, स्थिर अक्षर *);

व्योम stop_nmi(व्योम);
व्योम restart_nmi(व्योम);
व्योम local_touch_nmi(व्योम);

#पूर्ण_अगर /* _ASM_X86_NMI_H */
