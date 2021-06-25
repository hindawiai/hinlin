<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * drivers/parisc/gsc.h
 * Declarations क्रम functions in gsc.c
 * Copyright (c) 2000-2002 Helge Deller, Matthew Wilcox
 */

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <यंत्र/hardware.h>
#समावेश <यंत्र/parisc-device.h>

#घोषणा OFFSET_IRR 0x0000   /* Interrupt request रेजिस्टर */
#घोषणा OFFSET_IMR 0x0004   /* Interrupt mask रेजिस्टर */
#घोषणा OFFSET_IPR 0x0008   /* Interrupt pending रेजिस्टर */
#घोषणा OFFSET_ICR 0x000C   /* Interrupt control रेजिस्टर */
#घोषणा OFFSET_IAR 0x0010   /* Interrupt address रेजिस्टर */

/* PA I/O Architected devices support at least 5 bits in the EIM रेजिस्टर. */
#घोषणा GSC_EIM_WIDTH 5

काष्ठा gsc_irq अणु
	अचिन्हित दीर्घ txn_addr;	/* IRQ "target" */
	पूर्णांक txn_data;		/* HW "IRQ" */
	पूर्णांक irq;		/* भव IRQ */
पूर्ण;

काष्ठा gsc_asic अणु
	काष्ठा parisc_device *gsc;
	अचिन्हित दीर्घ hpa;
	अक्षर *name;
	पूर्णांक version;
	पूर्णांक type;
	पूर्णांक eim;
	पूर्णांक global_irq[32];
पूर्ण;

पूर्णांक gsc_common_setup(काष्ठा parisc_device *parent, काष्ठा gsc_asic *gsc_asic);
पूर्णांक gsc_alloc_irq(काष्ठा gsc_irq *dev);			/* dev needs an irq */
पूर्णांक gsc_claim_irq(काष्ठा gsc_irq *dev, पूर्णांक irq);	/* dev needs this irq */
पूर्णांक gsc_assign_irq(काष्ठा irq_chip *type, व्योम *data);
पूर्णांक gsc_find_local_irq(अचिन्हित पूर्णांक irq, पूर्णांक *global_irq, पूर्णांक limit);
व्योम gsc_fixup_irqs(काष्ठा parisc_device *parent, व्योम *ctrl,
		व्योम (*choose)(काष्ठा parisc_device *child, व्योम *ctrl));
व्योम gsc_asic_assign_irq(काष्ठा gsc_asic *asic, पूर्णांक local_irq, पूर्णांक *irqp);

irqवापस_t gsc_asic_पूर्णांकr(पूर्णांक irq, व्योम *dev);
