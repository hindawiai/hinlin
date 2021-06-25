<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/* Atlantic Network Driver
 *
 * Copyright (C) 2014-2019 aQuantia Corporation
 * Copyright (C) 2019-2020 Marvell International Ltd.
 */

/* File aq_pci_func.h: Declaration of PCI functions. */

#अगर_अघोषित AQ_PCI_FUNC_H
#घोषणा AQ_PCI_FUNC_H

#समावेश "aq_common.h"
#समावेश "aq_nic.h"

काष्ठा aq_board_revision_s अणु
	अचिन्हित लघु devid;
	अचिन्हित लघु revision;
	स्थिर काष्ठा aq_hw_ops *ops;
	स्थिर काष्ठा aq_hw_caps_s *caps;
पूर्ण;

पूर्णांक aq_pci_func_alloc_irq(काष्ठा aq_nic_s *self, अचिन्हित पूर्णांक i,
			  अक्षर *name, irq_handler_t irq_handler,
			  व्योम *irq_arg, cpumask_t *affinity_mask);
व्योम aq_pci_func_मुक्त_irqs(काष्ठा aq_nic_s *self);
अचिन्हित पूर्णांक aq_pci_func_get_irq_type(काष्ठा aq_nic_s *self);

पूर्णांक aq_pci_func_रेजिस्टर_driver(व्योम);
व्योम aq_pci_func_unरेजिस्टर_driver(व्योम);

#पूर्ण_अगर /* AQ_PCI_FUNC_H */
