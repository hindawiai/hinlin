<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_IRQHANDLER_H
#घोषणा _LINUX_IRQHANDLER_H

/*
 * Interrupt flow handler प्रकारs are defined here to aव्योम circular
 * include dependencies.
 */

काष्ठा irq_desc;
काष्ठा irq_data;
प्रकार	व्योम (*irq_flow_handler_t)(काष्ठा irq_desc *desc);

#पूर्ण_अगर
