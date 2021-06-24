<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __NMI_H
#घोषणा __NMI_H

पूर्णांक __init nmi_init(व्योम);
व्योम perfctr_irq(पूर्णांक irq, काष्ठा pt_regs *regs);
व्योम nmi_adjust_hz(अचिन्हित पूर्णांक new_hz);

बाह्य atomic_t nmi_active;

व्योम arch_touch_nmi_watchकरोg(व्योम);
व्योम start_nmi_watchकरोg(व्योम *unused);
व्योम stop_nmi_watchकरोg(व्योम *unused);

#पूर्ण_अगर /* __NMI_H */
