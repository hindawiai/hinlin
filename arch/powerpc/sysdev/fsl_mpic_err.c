<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2012 Freescale Semiconductor, Inc.
 *
 * Author: Varun Sethi <varun.sethi@मुक्तscale.com>
 */

#समावेश <linux/irq.h>
#समावेश <linux/smp.h>
#समावेश <linux/पूर्णांकerrupt.h>

#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/mpic.h>

#समावेश "mpic.h"

#घोषणा MPIC_ERR_INT_BASE	0x3900
#घोषणा MPIC_ERR_INT_EISR	0x0000
#घोषणा MPIC_ERR_INT_EIMR	0x0010

अटल अंतरभूत u32 mpic_fsl_err_पढ़ो(u32 __iomem *base, अचिन्हित पूर्णांक err_reg)
अणु
	वापस in_be32(base + (err_reg >> 2));
पूर्ण

अटल अंतरभूत व्योम mpic_fsl_err_ग_लिखो(u32 __iomem *base, u32 value)
अणु
	out_be32(base + (MPIC_ERR_INT_EIMR >> 2), value);
पूर्ण

अटल व्योम fsl_mpic_mask_err(काष्ठा irq_data *d)
अणु
	u32 eimr;
	काष्ठा mpic *mpic = irq_data_get_irq_chip_data(d);
	अचिन्हित पूर्णांक src = virq_to_hw(d->irq) - mpic->err_पूर्णांक_vecs[0];

	eimr = mpic_fsl_err_पढ़ो(mpic->err_regs, MPIC_ERR_INT_EIMR);
	eimr |= (1 << (31 - src));
	mpic_fsl_err_ग_लिखो(mpic->err_regs, eimr);
पूर्ण

अटल व्योम fsl_mpic_unmask_err(काष्ठा irq_data *d)
अणु
	u32 eimr;
	काष्ठा mpic *mpic = irq_data_get_irq_chip_data(d);
	अचिन्हित पूर्णांक src = virq_to_hw(d->irq) - mpic->err_पूर्णांक_vecs[0];

	eimr = mpic_fsl_err_पढ़ो(mpic->err_regs, MPIC_ERR_INT_EIMR);
	eimr &= ~(1 << (31 - src));
	mpic_fsl_err_ग_लिखो(mpic->err_regs, eimr);
पूर्ण

अटल काष्ठा irq_chip fsl_mpic_err_chip = अणु
	.irq_disable	= fsl_mpic_mask_err,
	.irq_mask	= fsl_mpic_mask_err,
	.irq_unmask	= fsl_mpic_unmask_err,
पूर्ण;

पूर्णांक mpic_setup_error_पूर्णांक(काष्ठा mpic *mpic, पूर्णांक पूर्णांकvec)
अणु
	पूर्णांक i;

	mpic->err_regs = ioremap(mpic->paddr + MPIC_ERR_INT_BASE, 0x1000);
	अगर (!mpic->err_regs) अणु
		pr_err("could not map mpic error registers\n");
		वापस -ENOMEM;
	पूर्ण
	mpic->hc_err = fsl_mpic_err_chip;
	mpic->hc_err.name = mpic->name;
	mpic->flags |= MPIC_FSL_HAS_EIMR;
	/* allocate पूर्णांकerrupt vectors क्रम error पूर्णांकerrupts */
	क्रम (i = MPIC_MAX_ERR - 1; i >= 0; i--)
		mpic->err_पूर्णांक_vecs[i] = पूर्णांकvec--;

	वापस 0;
पूर्ण

पूर्णांक mpic_map_error_पूर्णांक(काष्ठा mpic *mpic, अचिन्हित पूर्णांक virq, irq_hw_number_t  hw)
अणु
	अगर ((mpic->flags & MPIC_FSL_HAS_EIMR) &&
	    (hw >= mpic->err_पूर्णांक_vecs[0] &&
	     hw <= mpic->err_पूर्णांक_vecs[MPIC_MAX_ERR - 1])) अणु
		WARN_ON(mpic->flags & MPIC_SECONDARY);

		pr_debug("mpic: mapping as Error Interrupt\n");
		irq_set_chip_data(virq, mpic);
		irq_set_chip_and_handler(virq, &mpic->hc_err,
					 handle_level_irq);
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल irqवापस_t fsl_error_पूर्णांक_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा mpic *mpic = (काष्ठा mpic *) data;
	u32 eisr, eimr;
	पूर्णांक errपूर्णांक;
	अचिन्हित पूर्णांक cascade_irq;

	eisr = mpic_fsl_err_पढ़ो(mpic->err_regs, MPIC_ERR_INT_EISR);
	eimr = mpic_fsl_err_पढ़ो(mpic->err_regs, MPIC_ERR_INT_EIMR);

	अगर (!(eisr & ~eimr))
		वापस IRQ_NONE;

	जबतक (eisr) अणु
		errपूर्णांक = __builtin_clz(eisr);
		cascade_irq = irq_linear_revmap(mpic->irqhost,
				 mpic->err_पूर्णांक_vecs[errपूर्णांक]);
		WARN_ON(!cascade_irq);
		अगर (cascade_irq) अणु
			generic_handle_irq(cascade_irq);
		पूर्ण अन्यथा अणु
			eimr |=  1 << (31 - errपूर्णांक);
			mpic_fsl_err_ग_लिखो(mpic->err_regs, eimr);
		पूर्ण
		eisr &= ~(1 << (31 - errपूर्णांक));
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

व्योम mpic_err_पूर्णांक_init(काष्ठा mpic *mpic, irq_hw_number_t irqnum)
अणु
	अचिन्हित पूर्णांक virq;
	पूर्णांक ret;

	virq = irq_create_mapping(mpic->irqhost, irqnum);
	अगर (!virq) अणु
		pr_err("Error interrupt setup failed\n");
		वापस;
	पूर्ण

	/* Mask all error पूर्णांकerrupts */
	mpic_fsl_err_ग_लिखो(mpic->err_regs, ~0);

	ret = request_irq(virq, fsl_error_पूर्णांक_handler, IRQF_NO_THREAD,
		    "mpic-error-int", mpic);
	अगर (ret)
		pr_err("Failed to register error interrupt handler\n");
पूर्ण
