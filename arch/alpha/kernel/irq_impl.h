<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *	linux/arch/alpha/kernel/irq_impl.h
 *
 *	Copyright (C) 1995 Linus Torvalds
 *	Copyright (C) 1998, 2000 Riअक्षरd Henderson
 *
 * This file contains declarations and अंतरभूत functions क्रम पूर्णांकerfacing
 * with the IRQ handling routines in irq.c.
 */

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/profile.h>


#घोषणा RTC_IRQ    8

बाह्य व्योम isa_device_पूर्णांकerrupt(अचिन्हित दीर्घ);
बाह्य व्योम isa_no_iack_sc_device_पूर्णांकerrupt(अचिन्हित दीर्घ);
बाह्य व्योम srm_device_पूर्णांकerrupt(अचिन्हित दीर्घ);
बाह्य व्योम pyxis_device_पूर्णांकerrupt(अचिन्हित दीर्घ);

बाह्य व्योम init_srm_irqs(दीर्घ, अचिन्हित दीर्घ);
बाह्य व्योम init_pyxis_irqs(अचिन्हित दीर्घ);
बाह्य व्योम init_rtc_irq(irq_handler_t  handler);

बाह्य व्योम common_init_isa_dma(व्योम);

बाह्य व्योम i8259a_enable_irq(काष्ठा irq_data *d);
बाह्य व्योम i8259a_disable_irq(काष्ठा irq_data *d);
बाह्य व्योम i8259a_mask_and_ack_irq(काष्ठा irq_data *d);
बाह्य काष्ठा irq_chip i8259a_irq_type;
बाह्य व्योम init_i8259a_irqs(व्योम);

बाह्य व्योम handle_irq(पूर्णांक irq);
