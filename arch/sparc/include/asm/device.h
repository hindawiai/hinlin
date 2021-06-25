<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Arch specअगरic extensions to काष्ठा device
 */
#अगर_अघोषित _ASM_SPARC_DEVICE_H
#घोषणा _ASM_SPARC_DEVICE_H

#समावेश <यंत्र/खोलोprom.h>

काष्ठा device_node;
काष्ठा platक्रमm_device;

काष्ठा dev_archdata अणु
	व्योम			*iommu;
	व्योम			*stc;
	व्योम			*host_controller;
	काष्ठा platक्रमm_device	*op;
	पूर्णांक			numa_node;
पूर्ण;

व्योम of_propagate_archdata(काष्ठा platक्रमm_device *bus);

काष्ठा pdev_archdata अणु
	काष्ठा resource		resource[PROMREG_MAX];
	अचिन्हित पूर्णांक		irqs[PROMINTR_MAX];
	पूर्णांक			num_irqs;
पूर्ण;

#पूर्ण_अगर /* _ASM_SPARC_DEVICE_H */
