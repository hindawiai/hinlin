<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_NMI_H
#घोषणा _ASM_NMI_H

#अगर_घोषित CONFIG_PPC_WATCHDOG
बाह्य व्योम arch_touch_nmi_watchकरोg(व्योम);
दीर्घ soft_nmi_पूर्णांकerrupt(काष्ठा pt_regs *regs);
#अन्यथा
अटल अंतरभूत व्योम arch_touch_nmi_watchकरोg(व्योम) अणुपूर्ण
#पूर्ण_अगर

#अगर defined(CONFIG_NMI_IPI) && defined(CONFIG_STACKTRACE)
बाह्य व्योम arch_trigger_cpumask_backtrace(स्थिर cpumask_t *mask,
					   bool exclude_self);
#घोषणा arch_trigger_cpumask_backtrace arch_trigger_cpumask_backtrace
#पूर्ण_अगर

बाह्य व्योम hv_nmi_check_nonrecoverable(काष्ठा pt_regs *regs);

#पूर्ण_अगर /* _ASM_NMI_H */
