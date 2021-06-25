<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
#अगर_अघोषित _POWERPC_SYSDEV_MSI_BITMAP_H
#घोषणा _POWERPC_SYSDEV_MSI_BITMAP_H

/*
 * Copyright 2008, Michael Ellerman, IBM Corporation.
 */

#समावेश <linux/of.h>
#समावेश <यंत्र/irq.h>

काष्ठा msi_biपंचांगap अणु
	काष्ठा device_node	*of_node;
	अचिन्हित दीर्घ		*biपंचांगap;
	spinlock_t		lock;
	अचिन्हित पूर्णांक		irq_count;
	bool		 	biपंचांगap_from_slab;
पूर्ण;

पूर्णांक msi_biपंचांगap_alloc_hwirqs(काष्ठा msi_biपंचांगap *bmp, पूर्णांक num);
व्योम msi_biपंचांगap_मुक्त_hwirqs(काष्ठा msi_biपंचांगap *bmp, अचिन्हित पूर्णांक offset,
			    अचिन्हित पूर्णांक num);
व्योम msi_biपंचांगap_reserve_hwirq(काष्ठा msi_biपंचांगap *bmp, अचिन्हित पूर्णांक hwirq);

पूर्णांक msi_biपंचांगap_reserve_dt_hwirqs(काष्ठा msi_biपंचांगap *bmp);

पूर्णांक msi_biपंचांगap_alloc(काष्ठा msi_biपंचांगap *bmp, अचिन्हित पूर्णांक irq_count,
		     काष्ठा device_node *of_node);
व्योम msi_biपंचांगap_मुक्त(काष्ठा msi_biपंचांगap *bmp);

#पूर्ण_अगर /* _POWERPC_SYSDEV_MSI_BITMAP_H */
