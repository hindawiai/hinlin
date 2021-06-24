<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * First-level पूर्णांकerrupt controller model क्रम Hexagon.
 *
 * Copyright (c) 2010-2011, The Linux Foundation. All rights reserved.
 */

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/hexagon_vm.h>

अटल व्योम mask_irq(काष्ठा irq_data *data)
अणु
	__vmपूर्णांकop_locdis((दीर्घ) data->irq);
पूर्ण

अटल व्योम mask_irq_num(अचिन्हित पूर्णांक irq)
अणु
	__vmपूर्णांकop_locdis((दीर्घ) irq);
पूर्ण

अटल व्योम unmask_irq(काष्ठा irq_data *data)
अणु
	__vmपूर्णांकop_locen((दीर्घ) data->irq);
पूर्ण

/*  This is actually all we need क्रम handle_fasteoi_irq  */
अटल व्योम eoi_irq(काष्ठा irq_data *data)
अणु
	__vmपूर्णांकop_globen((दीर्घ) data->irq);
पूर्ण

/* Power mamangement wake call. We करोn't need this, however,
 * अगर this is असलent, then an -ENXIO error is वापसed to the
 * msm_serial driver, and it fails to correctly initialize.
 * This is a bug in the msm_serial driver, but, क्रम now, we
 * work around it here, by providing this bogus handler.
 * XXX FIXME!!! हटाओ this when msm_serial is fixed.
 */
अटल पूर्णांक set_wake(काष्ठा irq_data *data, अचिन्हित पूर्णांक on)
अणु
	वापस 0;
पूर्ण

अटल काष्ठा irq_chip hexagon_irq_chip = अणु
	.name		= "HEXAGON",
	.irq_mask	= mask_irq,
	.irq_unmask	= unmask_irq,
	.irq_set_wake	= set_wake,
	.irq_eoi	= eoi_irq
पूर्ण;

/**
 * The hexagon core comes with a first-level पूर्णांकerrupt controller
 * with 32 total possible पूर्णांकerrupts.  When the core is embedded
 * पूर्णांकo dअगरferent प्रणालीs/platक्रमms, it is typically wrapped by
 * macro cells that provide one or more second-level पूर्णांकerrupt
 * controllers that are cascaded पूर्णांकo one or more of the first-level
 * पूर्णांकerrupts handled here. The precise wiring of these other
 * irqs varies from platक्रमm to platक्रमm, and are set up & configured
 * in the platक्रमm-specअगरic files.
 *
 * The first-level पूर्णांकerrupt controller is wrapped by the VM, which
 * भवizes the पूर्णांकerrupt controller क्रम us.  It provides a very
 * simple, fast & efficient API, and so the fasteoi handler is
 * appropriate क्रम this हाल.
 */
व्योम __init init_IRQ(व्योम)
अणु
	पूर्णांक irq;

	क्रम (irq = 0; irq < HEXAGON_CPUINTS; irq++) अणु
		mask_irq_num(irq);
		irq_set_chip_and_handler(irq, &hexagon_irq_chip,
						 handle_fasteoi_irq);
	पूर्ण
पूर्ण
