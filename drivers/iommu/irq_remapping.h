<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2012 Advanced Micro Devices, Inc.
 * Author: Joerg Roedel <jroedel@suse.de>
 *
 * This header file contains stuff that is shared between dअगरferent पूर्णांकerrupt
 * remapping drivers but with no need to be visible outside of the IOMMU layer.
 */

#अगर_अघोषित __IRQ_REMAPPING_H
#घोषणा __IRQ_REMAPPING_H

#अगर_घोषित CONFIG_IRQ_REMAP

काष्ठा irq_data;
काष्ठा msi_msg;
काष्ठा irq_करोमुख्य;
काष्ठा irq_alloc_info;

बाह्य पूर्णांक irq_remap_broken;
बाह्य पूर्णांक disable_sourceid_checking;
बाह्य पूर्णांक no_x2apic_optout;
बाह्य पूर्णांक irq_remapping_enabled;

बाह्य पूर्णांक disable_irq_post;

काष्ठा irq_remap_ops अणु
	/* The supported capabilities */
	पूर्णांक capability;

	/* Initializes hardware and makes it पढ़ोy क्रम remapping पूर्णांकerrupts */
	पूर्णांक  (*prepare)(व्योम);

	/* Enables the remapping hardware */
	पूर्णांक  (*enable)(व्योम);

	/* Disables the remapping hardware */
	व्योम (*disable)(व्योम);

	/* Reenables the remapping hardware */
	पूर्णांक  (*reenable)(पूर्णांक);

	/* Enable fault handling */
	पूर्णांक  (*enable_faulting)(व्योम);
पूर्ण;

बाह्य काष्ठा irq_remap_ops पूर्णांकel_irq_remap_ops;
बाह्य काष्ठा irq_remap_ops amd_iommu_irq_ops;
बाह्य काष्ठा irq_remap_ops hyperv_irq_remap_ops;

#अन्यथा  /* CONFIG_IRQ_REMAP */

#घोषणा irq_remapping_enabled 0
#घोषणा irq_remap_broken      0
#घोषणा disable_irq_post      1

#पूर्ण_अगर /* CONFIG_IRQ_REMAP */

#पूर्ण_अगर /* __IRQ_REMAPPING_H */
