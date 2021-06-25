<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * S3C24XX IRQ handling
 *
 * Copyright (c) 2003-2004 Simtec Electronics
 *	Ben Dooks <ben@simtec.co.uk>
 * Copyright (c) 2012 Heiko Stuebner <heiko@sntech.de>
*/

#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/पन.स>
#समावेश <linux/err.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/ioport.h>
#समावेश <linux/device.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/irqchip.h>
#समावेश <linux/irqchip/chained_irq.h>
#समावेश <linux/of.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_address.h>
#समावेश <linux/spi/s3c24xx.h>

#समावेश <यंत्र/exception.h>
#समावेश <यंत्र/mach/irq.h>

#समावेश <mach/irqs.h>
#समावेश "regs-irq.h"
#समावेश "regs-gpio.h"

#समावेश "cpu.h"
#समावेश "regs-irqtype.h"
#समावेश "pm.h"
#समावेश "s3c24xx.h"

#घोषणा S3C_IRQTYPE_NONE	0
#घोषणा S3C_IRQTYPE_EINT	1
#घोषणा S3C_IRQTYPE_EDGE	2
#घोषणा S3C_IRQTYPE_LEVEL	3

काष्ठा s3c_irq_data अणु
	अचिन्हित पूर्णांक type;
	अचिन्हित दीर्घ offset;
	अचिन्हित दीर्घ parent_irq;

	/* data माला_लो filled during init */
	काष्ठा s3c_irq_पूर्णांकc *पूर्णांकc;
	अचिन्हित दीर्घ sub_bits;
	काष्ठा s3c_irq_पूर्णांकc *sub_पूर्णांकc;
पूर्ण;

/*
 * Structure holding the controller data
 * @reg_pending		रेजिस्टर holding pending irqs
 * @reg_पूर्णांकpnd		special रेजिस्टर पूर्णांकpnd in मुख्य पूर्णांकc
 * @reg_mask		mask रेजिस्टर
 * @करोमुख्य		irq_करोमुख्य of the controller
 * @parent		parent controller क्रम ext and sub irqs
 * @irqs		irq-data, always s3c_irq_data[32]
 */
काष्ठा s3c_irq_पूर्णांकc अणु
	व्योम __iomem		*reg_pending;
	व्योम __iomem		*reg_पूर्णांकpnd;
	व्योम __iomem		*reg_mask;
	काष्ठा irq_करोमुख्य	*करोमुख्य;
	काष्ठा s3c_irq_पूर्णांकc	*parent;
	काष्ठा s3c_irq_data	*irqs;
पूर्ण;

/*
 * Array holding poपूर्णांकers to the global controller काष्ठाs
 * [0] ... मुख्य_पूर्णांकc
 * [1] ... sub_पूर्णांकc
 * [2] ... मुख्य_पूर्णांकc2 on s3c2416
 */
अटल काष्ठा s3c_irq_पूर्णांकc *s3c_पूर्णांकc[3];

अटल व्योम s3c_irq_mask(काष्ठा irq_data *data)
अणु
	काष्ठा s3c_irq_data *irq_data = irq_data_get_irq_chip_data(data);
	काष्ठा s3c_irq_पूर्णांकc *पूर्णांकc = irq_data->पूर्णांकc;
	काष्ठा s3c_irq_पूर्णांकc *parent_पूर्णांकc = पूर्णांकc->parent;
	काष्ठा s3c_irq_data *parent_data;
	अचिन्हित दीर्घ mask;
	अचिन्हित पूर्णांक irqno;

	mask = पढ़ोl_relaxed(पूर्णांकc->reg_mask);
	mask |= (1UL << irq_data->offset);
	ग_लिखोl_relaxed(mask, पूर्णांकc->reg_mask);

	अगर (parent_पूर्णांकc) अणु
		parent_data = &parent_पूर्णांकc->irqs[irq_data->parent_irq];

		/* check to see अगर we need to mask the parent IRQ
		 * The parent_irq is always in मुख्य_पूर्णांकc, so the hwirq
		 * क्रम find_mapping करोes not need an offset in any हाल.
		 */
		अगर ((mask & parent_data->sub_bits) == parent_data->sub_bits) अणु
			irqno = irq_find_mapping(parent_पूर्णांकc->करोमुख्य,
					 irq_data->parent_irq);
			s3c_irq_mask(irq_get_irq_data(irqno));
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम s3c_irq_unmask(काष्ठा irq_data *data)
अणु
	काष्ठा s3c_irq_data *irq_data = irq_data_get_irq_chip_data(data);
	काष्ठा s3c_irq_पूर्णांकc *पूर्णांकc = irq_data->पूर्णांकc;
	काष्ठा s3c_irq_पूर्णांकc *parent_पूर्णांकc = पूर्णांकc->parent;
	अचिन्हित दीर्घ mask;
	अचिन्हित पूर्णांक irqno;

	mask = पढ़ोl_relaxed(पूर्णांकc->reg_mask);
	mask &= ~(1UL << irq_data->offset);
	ग_लिखोl_relaxed(mask, पूर्णांकc->reg_mask);

	अगर (parent_पूर्णांकc) अणु
		irqno = irq_find_mapping(parent_पूर्णांकc->करोमुख्य,
					 irq_data->parent_irq);
		s3c_irq_unmask(irq_get_irq_data(irqno));
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम s3c_irq_ack(काष्ठा irq_data *data)
अणु
	काष्ठा s3c_irq_data *irq_data = irq_data_get_irq_chip_data(data);
	काष्ठा s3c_irq_पूर्णांकc *पूर्णांकc = irq_data->पूर्णांकc;
	अचिन्हित दीर्घ bitval = 1UL << irq_data->offset;

	ग_लिखोl_relaxed(bitval, पूर्णांकc->reg_pending);
	अगर (पूर्णांकc->reg_पूर्णांकpnd)
		ग_लिखोl_relaxed(bitval, पूर्णांकc->reg_पूर्णांकpnd);
पूर्ण

अटल पूर्णांक s3c_irq_type(काष्ठा irq_data *data, अचिन्हित पूर्णांक type)
अणु
	चयन (type) अणु
	हाल IRQ_TYPE_NONE:
		अवरोध;
	हाल IRQ_TYPE_EDGE_RISING:
	हाल IRQ_TYPE_EDGE_FALLING:
	हाल IRQ_TYPE_EDGE_BOTH:
		irq_set_handler(data->irq, handle_edge_irq);
		अवरोध;
	हाल IRQ_TYPE_LEVEL_LOW:
	हाल IRQ_TYPE_LEVEL_HIGH:
		irq_set_handler(data->irq, handle_level_irq);
		अवरोध;
	शेष:
		pr_err("No such irq type %d\n", type);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक s3c_irqext_type_set(व्योम __iomem *gpcon_reg,
			       व्योम __iomem *extपूर्णांक_reg,
			       अचिन्हित दीर्घ gpcon_offset,
			       अचिन्हित दीर्घ extपूर्णांक_offset,
			       अचिन्हित पूर्णांक type)
अणु
	अचिन्हित दीर्घ newvalue = 0, value;

	/* Set the GPIO to बाह्यal पूर्णांकerrupt mode */
	value = पढ़ोl_relaxed(gpcon_reg);
	value = (value & ~(3 << gpcon_offset)) | (0x02 << gpcon_offset);
	ग_लिखोl_relaxed(value, gpcon_reg);

	/* Set the बाह्यal पूर्णांकerrupt to poपूर्णांकed trigger type */
	चयन (type)
	अणु
		हाल IRQ_TYPE_NONE:
			pr_warn("No edge setting!\n");
			अवरोध;

		हाल IRQ_TYPE_EDGE_RISING:
			newvalue = S3C2410_EXTINT_RISEEDGE;
			अवरोध;

		हाल IRQ_TYPE_EDGE_FALLING:
			newvalue = S3C2410_EXTINT_FALLEDGE;
			अवरोध;

		हाल IRQ_TYPE_EDGE_BOTH:
			newvalue = S3C2410_EXTINT_BOTHEDGE;
			अवरोध;

		हाल IRQ_TYPE_LEVEL_LOW:
			newvalue = S3C2410_EXTINT_LOWLEV;
			अवरोध;

		हाल IRQ_TYPE_LEVEL_HIGH:
			newvalue = S3C2410_EXTINT_HILEV;
			अवरोध;

		शेष:
			pr_err("No such irq type %d\n", type);
			वापस -EINVAL;
	पूर्ण

	value = पढ़ोl_relaxed(extपूर्णांक_reg);
	value = (value & ~(7 << extपूर्णांक_offset)) | (newvalue << extपूर्णांक_offset);
	ग_लिखोl_relaxed(value, extपूर्णांक_reg);

	वापस 0;
पूर्ण

अटल पूर्णांक s3c_irqext_type(काष्ठा irq_data *data, अचिन्हित पूर्णांक type)
अणु
	व्योम __iomem *extपूर्णांक_reg;
	व्योम __iomem *gpcon_reg;
	अचिन्हित दीर्घ gpcon_offset, extपूर्णांक_offset;

	अगर ((data->hwirq >= 4) && (data->hwirq <= 7)) अणु
		gpcon_reg = S3C2410_GPFCON;
		extपूर्णांक_reg = S3C24XX_EXTINT0;
		gpcon_offset = (data->hwirq) * 2;
		extपूर्णांक_offset = (data->hwirq) * 4;
	पूर्ण अन्यथा अगर ((data->hwirq >= 8) && (data->hwirq <= 15)) अणु
		gpcon_reg = S3C2410_GPGCON;
		extपूर्णांक_reg = S3C24XX_EXTINT1;
		gpcon_offset = (data->hwirq - 8) * 2;
		extपूर्णांक_offset = (data->hwirq - 8) * 4;
	पूर्ण अन्यथा अगर ((data->hwirq >= 16) && (data->hwirq <= 23)) अणु
		gpcon_reg = S3C2410_GPGCON;
		extपूर्णांक_reg = S3C24XX_EXTINT2;
		gpcon_offset = (data->hwirq - 8) * 2;
		extपूर्णांक_offset = (data->hwirq - 16) * 4;
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण

	वापस s3c_irqext_type_set(gpcon_reg, extपूर्णांक_reg, gpcon_offset,
				   extपूर्णांक_offset, type);
पूर्ण

अटल पूर्णांक s3c_irqext0_type(काष्ठा irq_data *data, अचिन्हित पूर्णांक type)
अणु
	व्योम __iomem *extपूर्णांक_reg;
	व्योम __iomem *gpcon_reg;
	अचिन्हित दीर्घ gpcon_offset, extपूर्णांक_offset;

	अगर (data->hwirq <= 3) अणु
		gpcon_reg = S3C2410_GPFCON;
		extपूर्णांक_reg = S3C24XX_EXTINT0;
		gpcon_offset = (data->hwirq) * 2;
		extपूर्णांक_offset = (data->hwirq) * 4;
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण

	वापस s3c_irqext_type_set(gpcon_reg, extपूर्णांक_reg, gpcon_offset,
				   extपूर्णांक_offset, type);
पूर्ण

अटल काष्ठा irq_chip s3c_irq_chip = अणु
	.name		= "s3c",
	.irq_ack	= s3c_irq_ack,
	.irq_mask	= s3c_irq_mask,
	.irq_unmask	= s3c_irq_unmask,
	.irq_set_type	= s3c_irq_type,
	.irq_set_wake	= s3c_irq_wake
पूर्ण;

अटल काष्ठा irq_chip s3c_irq_level_chip = अणु
	.name		= "s3c-level",
	.irq_mask	= s3c_irq_mask,
	.irq_unmask	= s3c_irq_unmask,
	.irq_ack	= s3c_irq_ack,
	.irq_set_type	= s3c_irq_type,
पूर्ण;

अटल काष्ठा irq_chip s3c_irqext_chip = अणु
	.name		= "s3c-ext",
	.irq_mask	= s3c_irq_mask,
	.irq_unmask	= s3c_irq_unmask,
	.irq_ack	= s3c_irq_ack,
	.irq_set_type	= s3c_irqext_type,
	.irq_set_wake	= s3c_irqext_wake
पूर्ण;

अटल काष्ठा irq_chip s3c_irq_eपूर्णांक0t4 = अणु
	.name		= "s3c-ext0",
	.irq_ack	= s3c_irq_ack,
	.irq_mask	= s3c_irq_mask,
	.irq_unmask	= s3c_irq_unmask,
	.irq_set_wake	= s3c_irq_wake,
	.irq_set_type	= s3c_irqext0_type,
पूर्ण;

अटल व्योम s3c_irq_demux(काष्ठा irq_desc *desc)
अणु
	काष्ठा irq_chip *chip = irq_desc_get_chip(desc);
	काष्ठा s3c_irq_data *irq_data = irq_desc_get_chip_data(desc);
	काष्ठा s3c_irq_पूर्णांकc *पूर्णांकc = irq_data->पूर्णांकc;
	काष्ठा s3c_irq_पूर्णांकc *sub_पूर्णांकc = irq_data->sub_पूर्णांकc;
	अचिन्हित पूर्णांक n, offset, irq;
	अचिन्हित दीर्घ src, msk;

	/* we're using inभागidual करोमुख्यs क्रम the non-dt हाल
	 * and one big करोमुख्य क्रम the dt हाल where the subपूर्णांकc
	 * starts at hwirq number 32.
	 */
	offset = irq_करोमुख्य_get_of_node(पूर्णांकc->करोमुख्य) ? 32 : 0;

	chained_irq_enter(chip, desc);

	src = पढ़ोl_relaxed(sub_पूर्णांकc->reg_pending);
	msk = पढ़ोl_relaxed(sub_पूर्णांकc->reg_mask);

	src &= ~msk;
	src &= irq_data->sub_bits;

	जबतक (src) अणु
		n = __ffs(src);
		src &= ~(1 << n);
		irq = irq_find_mapping(sub_पूर्णांकc->करोमुख्य, offset + n);
		generic_handle_irq(irq);
	पूर्ण

	chained_irq_निकास(chip, desc);
पूर्ण

अटल अंतरभूत पूर्णांक s3c24xx_handle_पूर्णांकc(काष्ठा s3c_irq_पूर्णांकc *पूर्णांकc,
				      काष्ठा pt_regs *regs, पूर्णांक पूर्णांकc_offset)
अणु
	पूर्णांक pnd;
	पूर्णांक offset;

	pnd = पढ़ोl_relaxed(पूर्णांकc->reg_पूर्णांकpnd);
	अगर (!pnd)
		वापस false;

	/* non-dt machines use inभागidual करोमुख्यs */
	अगर (!irq_करोमुख्य_get_of_node(पूर्णांकc->करोमुख्य))
		पूर्णांकc_offset = 0;

	/* We have a problem that the INTOFFSET रेजिस्टर करोes not always
	 * show one पूर्णांकerrupt. Occasionally we get two पूर्णांकerrupts through
	 * the prioritiser, and this causes the INTOFFSET रेजिस्टर to show
	 * what looks like the logical-or of the two पूर्णांकerrupt numbers.
	 *
	 * Thanks to Klaus, Shannon, et al क्रम helping to debug this problem
	 */
	offset = पढ़ोl_relaxed(पूर्णांकc->reg_पूर्णांकpnd + 4);

	/* Find the bit manually, when the offset is wrong.
	 * The pending रेजिस्टर only ever contains the one bit of the next
	 * पूर्णांकerrupt to handle.
	 */
	अगर (!(pnd & (1 << offset)))
		offset =  __ffs(pnd);

	handle_करोमुख्य_irq(पूर्णांकc->करोमुख्य, पूर्णांकc_offset + offset, regs);
	वापस true;
पूर्ण

अटल यंत्रlinkage व्योम __exception_irq_entry s3c24xx_handle_irq(काष्ठा pt_regs *regs)
अणु
	करो अणु
		अगर (likely(s3c_पूर्णांकc[0]))
			अगर (s3c24xx_handle_पूर्णांकc(s3c_पूर्णांकc[0], regs, 0))
				जारी;

		अगर (s3c_पूर्णांकc[2])
			अगर (s3c24xx_handle_पूर्णांकc(s3c_पूर्णांकc[2], regs, 64))
				जारी;

		अवरोध;
	पूर्ण जबतक (1);
पूर्ण

#अगर_घोषित CONFIG_FIQ
/**
 * s3c24xx_set_fiq - set the FIQ routing
 * @irq: IRQ number to route to FIQ on processor.
 * @ack_ptr: poपूर्णांकer to a location क्रम storing the bit mask
 * @on: Whether to route @irq to the FIQ, or to हटाओ the FIQ routing.
 *
 * Change the state of the IRQ to FIQ routing depending on @irq and @on. If
 * @on is true, the @irq is checked to see अगर it can be routed and the
 * पूर्णांकerrupt controller updated to route the IRQ. If @on is false, the FIQ
 * routing is cleared, regardless of which @irq is specअगरied.
 *
 * वापसs the mask value क्रम the रेजिस्टर.
 */
पूर्णांक s3c24xx_set_fiq(अचिन्हित पूर्णांक irq, u32 *ack_ptr, bool on)
अणु
	u32 पूर्णांकmod;
	अचिन्हित offs;

	अगर (on) अणु
		offs = irq - FIQ_START;
		अगर (offs > 31)
			वापस 0;

		पूर्णांकmod = 1 << offs;
	पूर्ण अन्यथा अणु
		पूर्णांकmod = 0;
	पूर्ण

	अगर (ack_ptr)
		*ack_ptr = पूर्णांकmod;
	ग_लिखोl_relaxed(पूर्णांकmod, S3C2410_INTMOD);

	वापस पूर्णांकmod;
पूर्ण

EXPORT_SYMBOL_GPL(s3c24xx_set_fiq);
#पूर्ण_अगर

अटल पूर्णांक s3c24xx_irq_map(काष्ठा irq_करोमुख्य *h, अचिन्हित पूर्णांक virq,
							irq_hw_number_t hw)
अणु
	काष्ठा s3c_irq_पूर्णांकc *पूर्णांकc = h->host_data;
	काष्ठा s3c_irq_data *irq_data = &पूर्णांकc->irqs[hw];
	काष्ठा s3c_irq_पूर्णांकc *parent_पूर्णांकc;
	काष्ठा s3c_irq_data *parent_irq_data;
	अचिन्हित पूर्णांक irqno;

	/* attach controller poपूर्णांकer to irq_data */
	irq_data->पूर्णांकc = पूर्णांकc;
	irq_data->offset = hw;

	parent_पूर्णांकc = पूर्णांकc->parent;

	/* set handler and flags */
	चयन (irq_data->type) अणु
	हाल S3C_IRQTYPE_NONE:
		वापस 0;
	हाल S3C_IRQTYPE_EINT:
		/* On the S3C2412, the EINT0to3 have a parent irq
		 * but need the s3c_irq_eपूर्णांक0t4 chip
		 */
		अगर (parent_पूर्णांकc && (!soc_is_s3c2412() || hw >= 4))
			irq_set_chip_and_handler(virq, &s3c_irqext_chip,
						 handle_edge_irq);
		अन्यथा
			irq_set_chip_and_handler(virq, &s3c_irq_eपूर्णांक0t4,
						 handle_edge_irq);
		अवरोध;
	हाल S3C_IRQTYPE_EDGE:
		अगर (parent_पूर्णांकc || पूर्णांकc->reg_pending == S3C2416_SRCPND2)
			irq_set_chip_and_handler(virq, &s3c_irq_level_chip,
						 handle_edge_irq);
		अन्यथा
			irq_set_chip_and_handler(virq, &s3c_irq_chip,
						 handle_edge_irq);
		अवरोध;
	हाल S3C_IRQTYPE_LEVEL:
		अगर (parent_पूर्णांकc)
			irq_set_chip_and_handler(virq, &s3c_irq_level_chip,
						 handle_level_irq);
		अन्यथा
			irq_set_chip_and_handler(virq, &s3c_irq_chip,
						 handle_level_irq);
		अवरोध;
	शेष:
		pr_err("irq-s3c24xx: unsupported irqtype %d\n", irq_data->type);
		वापस -EINVAL;
	पूर्ण

	irq_set_chip_data(virq, irq_data);

	अगर (parent_पूर्णांकc && irq_data->type != S3C_IRQTYPE_NONE) अणु
		अगर (irq_data->parent_irq > 31) अणु
			pr_err("irq-s3c24xx: parent irq %lu is out of range\n",
			       irq_data->parent_irq);
			वापस -EINVAL;
		पूर्ण

		parent_irq_data = &parent_पूर्णांकc->irqs[irq_data->parent_irq];
		parent_irq_data->sub_पूर्णांकc = पूर्णांकc;
		parent_irq_data->sub_bits |= (1UL << hw);

		/* attach the demuxer to the parent irq */
		irqno = irq_find_mapping(parent_पूर्णांकc->करोमुख्य,
					 irq_data->parent_irq);
		अगर (!irqno) अणु
			pr_err("irq-s3c24xx: could not find mapping for parent irq %lu\n",
			       irq_data->parent_irq);
			वापस -EINVAL;
		पूर्ण
		irq_set_chained_handler(irqno, s3c_irq_demux);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops s3c24xx_irq_ops = अणु
	.map = s3c24xx_irq_map,
	.xlate = irq_करोमुख्य_xlate_twocell,
पूर्ण;

अटल व्योम s3c24xx_clear_पूर्णांकc(काष्ठा s3c_irq_पूर्णांकc *पूर्णांकc)
अणु
	व्योम __iomem *reg_source;
	अचिन्हित दीर्घ pend;
	अचिन्हित दीर्घ last;
	पूर्णांक i;

	/* अगर पूर्णांकpnd is set, पढ़ो the next pending irq from there */
	reg_source = पूर्णांकc->reg_पूर्णांकpnd ? पूर्णांकc->reg_पूर्णांकpnd : पूर्णांकc->reg_pending;

	last = 0;
	क्रम (i = 0; i < 4; i++) अणु
		pend = पढ़ोl_relaxed(reg_source);

		अगर (pend == 0 || pend == last)
			अवरोध;

		ग_लिखोl_relaxed(pend, पूर्णांकc->reg_pending);
		अगर (पूर्णांकc->reg_पूर्णांकpnd)
			ग_लिखोl_relaxed(pend, पूर्णांकc->reg_पूर्णांकpnd);

		pr_info("irq: clearing pending status %08x\n", (पूर्णांक)pend);
		last = pend;
	पूर्ण
पूर्ण

अटल काष्ठा s3c_irq_पूर्णांकc * __init s3c24xx_init_पूर्णांकc(काष्ठा device_node *np,
				       काष्ठा s3c_irq_data *irq_data,
				       काष्ठा s3c_irq_पूर्णांकc *parent,
				       अचिन्हित दीर्घ address)
अणु
	काष्ठा s3c_irq_पूर्णांकc *पूर्णांकc;
	व्योम __iomem *base = (व्योम *)0xf6000000; /* अटल mapping */
	पूर्णांक irq_num;
	पूर्णांक irq_start;
	पूर्णांक ret;

	पूर्णांकc = kzalloc(माप(काष्ठा s3c_irq_पूर्णांकc), GFP_KERNEL);
	अगर (!पूर्णांकc)
		वापस ERR_PTR(-ENOMEM);

	पूर्णांकc->irqs = irq_data;

	अगर (parent)
		पूर्णांकc->parent = parent;

	/* select the correct data क्रम the controller.
	 * Need to hard code the irq num start and offset
	 * to preserve the अटल mapping क्रम now
	 */
	चयन (address) अणु
	हाल 0x4a000000:
		pr_debug("irq: found main intc\n");
		पूर्णांकc->reg_pending = base;
		पूर्णांकc->reg_mask = base + 0x08;
		पूर्णांकc->reg_पूर्णांकpnd = base + 0x10;
		irq_num = 32;
		irq_start = S3C2410_IRQ(0);
		अवरोध;
	हाल 0x4a000018:
		pr_debug("irq: found subintc\n");
		पूर्णांकc->reg_pending = base + 0x18;
		पूर्णांकc->reg_mask = base + 0x1c;
		irq_num = 29;
		irq_start = S3C2410_IRQSUB(0);
		अवरोध;
	हाल 0x4a000040:
		pr_debug("irq: found intc2\n");
		पूर्णांकc->reg_pending = base + 0x40;
		पूर्णांकc->reg_mask = base + 0x48;
		पूर्णांकc->reg_पूर्णांकpnd = base + 0x50;
		irq_num = 8;
		irq_start = S3C2416_IRQ(0);
		अवरोध;
	हाल 0x560000a4:
		pr_debug("irq: found eintc\n");
		base = (व्योम *)0xfd000000;

		पूर्णांकc->reg_mask = base + 0xa4;
		पूर्णांकc->reg_pending = base + 0xa8;
		irq_num = 24;
		irq_start = S3C2410_IRQ(32);
		अवरोध;
	शेष:
		pr_err("irq: unsupported controller address\n");
		ret = -EINVAL;
		जाओ err;
	पूर्ण

	/* now that all the data is complete, init the irq-करोमुख्य */
	s3c24xx_clear_पूर्णांकc(पूर्णांकc);
	पूर्णांकc->करोमुख्य = irq_करोमुख्य_add_legacy(np, irq_num, irq_start,
					     0, &s3c24xx_irq_ops,
					     पूर्णांकc);
	अगर (!पूर्णांकc->करोमुख्य) अणु
		pr_err("irq: could not create irq-domain\n");
		ret = -EINVAL;
		जाओ err;
	पूर्ण

	set_handle_irq(s3c24xx_handle_irq);

	वापस पूर्णांकc;

err:
	kमुक्त(पूर्णांकc);
	वापस ERR_PTR(ret);
पूर्ण

अटल काष्ठा s3c_irq_data __maybe_unused init_eपूर्णांक[32] = अणु
	अणु .type = S3C_IRQTYPE_NONE, पूर्ण, /* reserved */
	अणु .type = S3C_IRQTYPE_NONE, पूर्ण, /* reserved */
	अणु .type = S3C_IRQTYPE_NONE, पूर्ण, /* reserved */
	अणु .type = S3C_IRQTYPE_NONE, पूर्ण, /* reserved */
	अणु .type = S3C_IRQTYPE_EINT, .parent_irq = 4 पूर्ण, /* EINT4 */
	अणु .type = S3C_IRQTYPE_EINT, .parent_irq = 4 पूर्ण, /* EINT5 */
	अणु .type = S3C_IRQTYPE_EINT, .parent_irq = 4 पूर्ण, /* EINT6 */
	अणु .type = S3C_IRQTYPE_EINT, .parent_irq = 4 पूर्ण, /* EINT7 */
	अणु .type = S3C_IRQTYPE_EINT, .parent_irq = 5 पूर्ण, /* EINT8 */
	अणु .type = S3C_IRQTYPE_EINT, .parent_irq = 5 पूर्ण, /* EINT9 */
	अणु .type = S3C_IRQTYPE_EINT, .parent_irq = 5 पूर्ण, /* EINT10 */
	अणु .type = S3C_IRQTYPE_EINT, .parent_irq = 5 पूर्ण, /* EINT11 */
	अणु .type = S3C_IRQTYPE_EINT, .parent_irq = 5 पूर्ण, /* EINT12 */
	अणु .type = S3C_IRQTYPE_EINT, .parent_irq = 5 पूर्ण, /* EINT13 */
	अणु .type = S3C_IRQTYPE_EINT, .parent_irq = 5 पूर्ण, /* EINT14 */
	अणु .type = S3C_IRQTYPE_EINT, .parent_irq = 5 पूर्ण, /* EINT15 */
	अणु .type = S3C_IRQTYPE_EINT, .parent_irq = 5 पूर्ण, /* EINT16 */
	अणु .type = S3C_IRQTYPE_EINT, .parent_irq = 5 पूर्ण, /* EINT17 */
	अणु .type = S3C_IRQTYPE_EINT, .parent_irq = 5 पूर्ण, /* EINT18 */
	अणु .type = S3C_IRQTYPE_EINT, .parent_irq = 5 पूर्ण, /* EINT19 */
	अणु .type = S3C_IRQTYPE_EINT, .parent_irq = 5 पूर्ण, /* EINT20 */
	अणु .type = S3C_IRQTYPE_EINT, .parent_irq = 5 पूर्ण, /* EINT21 */
	अणु .type = S3C_IRQTYPE_EINT, .parent_irq = 5 पूर्ण, /* EINT22 */
	अणु .type = S3C_IRQTYPE_EINT, .parent_irq = 5 पूर्ण, /* EINT23 */
पूर्ण;

#अगर_घोषित CONFIG_CPU_S3C2410
अटल काष्ठा s3c_irq_data init_s3c2410base[32] = अणु
	अणु .type = S3C_IRQTYPE_EINT, पूर्ण, /* EINT0 */
	अणु .type = S3C_IRQTYPE_EINT, पूर्ण, /* EINT1 */
	अणु .type = S3C_IRQTYPE_EINT, पूर्ण, /* EINT2 */
	अणु .type = S3C_IRQTYPE_EINT, पूर्ण, /* EINT3 */
	अणु .type = S3C_IRQTYPE_LEVEL, पूर्ण, /* EINT4to7 */
	अणु .type = S3C_IRQTYPE_LEVEL, पूर्ण, /* EINT8to23 */
	अणु .type = S3C_IRQTYPE_NONE, पूर्ण, /* reserved */
	अणु .type = S3C_IRQTYPE_EDGE, पूर्ण, /* nBATT_FLT */
	अणु .type = S3C_IRQTYPE_EDGE, पूर्ण, /* TICK */
	अणु .type = S3C_IRQTYPE_EDGE, पूर्ण, /* WDT */
	अणु .type = S3C_IRQTYPE_EDGE, पूर्ण, /* TIMER0 */
	अणु .type = S3C_IRQTYPE_EDGE, पूर्ण, /* TIMER1 */
	अणु .type = S3C_IRQTYPE_EDGE, पूर्ण, /* TIMER2 */
	अणु .type = S3C_IRQTYPE_EDGE, पूर्ण, /* TIMER3 */
	अणु .type = S3C_IRQTYPE_EDGE, पूर्ण, /* TIMER4 */
	अणु .type = S3C_IRQTYPE_LEVEL, पूर्ण, /* UART2 */
	अणु .type = S3C_IRQTYPE_EDGE, पूर्ण, /* LCD */
	अणु .type = S3C_IRQTYPE_EDGE, पूर्ण, /* DMA0 */
	अणु .type = S3C_IRQTYPE_EDGE, पूर्ण, /* DMA1 */
	अणु .type = S3C_IRQTYPE_EDGE, पूर्ण, /* DMA2 */
	अणु .type = S3C_IRQTYPE_EDGE, पूर्ण, /* DMA3 */
	अणु .type = S3C_IRQTYPE_EDGE, पूर्ण, /* SDI */
	अणु .type = S3C_IRQTYPE_EDGE, पूर्ण, /* SPI0 */
	अणु .type = S3C_IRQTYPE_LEVEL, पूर्ण, /* UART1 */
	अणु .type = S3C_IRQTYPE_NONE, पूर्ण, /* reserved */
	अणु .type = S3C_IRQTYPE_EDGE, पूर्ण, /* USBD */
	अणु .type = S3C_IRQTYPE_EDGE, पूर्ण, /* USBH */
	अणु .type = S3C_IRQTYPE_EDGE, पूर्ण, /* IIC */
	अणु .type = S3C_IRQTYPE_LEVEL, पूर्ण, /* UART0 */
	अणु .type = S3C_IRQTYPE_EDGE, पूर्ण, /* SPI1 */
	अणु .type = S3C_IRQTYPE_EDGE, पूर्ण, /* RTC */
	अणु .type = S3C_IRQTYPE_LEVEL, पूर्ण, /* ADCPARENT */
पूर्ण;

अटल काष्ठा s3c_irq_data init_s3c2410subपूर्णांक[32] = अणु
	अणु .type = S3C_IRQTYPE_LEVEL, .parent_irq = 28 पूर्ण, /* UART0-RX */
	अणु .type = S3C_IRQTYPE_LEVEL, .parent_irq = 28 पूर्ण, /* UART0-TX */
	अणु .type = S3C_IRQTYPE_LEVEL, .parent_irq = 28 पूर्ण, /* UART0-ERR */
	अणु .type = S3C_IRQTYPE_LEVEL, .parent_irq = 23 पूर्ण, /* UART1-RX */
	अणु .type = S3C_IRQTYPE_LEVEL, .parent_irq = 23 पूर्ण, /* UART1-TX */
	अणु .type = S3C_IRQTYPE_LEVEL, .parent_irq = 23 पूर्ण, /* UART1-ERR */
	अणु .type = S3C_IRQTYPE_LEVEL, .parent_irq = 15 पूर्ण, /* UART2-RX */
	अणु .type = S3C_IRQTYPE_LEVEL, .parent_irq = 15 पूर्ण, /* UART2-TX */
	अणु .type = S3C_IRQTYPE_LEVEL, .parent_irq = 15 पूर्ण, /* UART2-ERR */
	अणु .type = S3C_IRQTYPE_EDGE, .parent_irq = 31 पूर्ण, /* TC */
	अणु .type = S3C_IRQTYPE_EDGE, .parent_irq = 31 पूर्ण, /* ADC */
पूर्ण;

व्योम __init s3c2410_init_irq(व्योम)
अणु
#अगर_घोषित CONFIG_FIQ
	init_FIQ(FIQ_START);
#पूर्ण_अगर

	s3c_पूर्णांकc[0] = s3c24xx_init_पूर्णांकc(शून्य, &init_s3c2410base[0], शून्य,
					0x4a000000);
	अगर (IS_ERR(s3c_पूर्णांकc[0])) अणु
		pr_err("irq: could not create main interrupt controller\n");
		वापस;
	पूर्ण

	s3c_पूर्णांकc[1] = s3c24xx_init_पूर्णांकc(शून्य, &init_s3c2410subपूर्णांक[0],
					s3c_पूर्णांकc[0], 0x4a000018);
	s3c24xx_init_पूर्णांकc(शून्य, &init_eपूर्णांक[0], s3c_पूर्णांकc[0], 0x560000a4);
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_CPU_S3C2412
अटल काष्ठा s3c_irq_data init_s3c2412base[32] = अणु
	अणु .type = S3C_IRQTYPE_LEVEL, पूर्ण, /* EINT0 */
	अणु .type = S3C_IRQTYPE_LEVEL, पूर्ण, /* EINT1 */
	अणु .type = S3C_IRQTYPE_LEVEL, पूर्ण, /* EINT2 */
	अणु .type = S3C_IRQTYPE_LEVEL, पूर्ण, /* EINT3 */
	अणु .type = S3C_IRQTYPE_LEVEL, पूर्ण, /* EINT4to7 */
	अणु .type = S3C_IRQTYPE_LEVEL, पूर्ण, /* EINT8to23 */
	अणु .type = S3C_IRQTYPE_NONE, पूर्ण, /* reserved */
	अणु .type = S3C_IRQTYPE_EDGE, पूर्ण, /* nBATT_FLT */
	अणु .type = S3C_IRQTYPE_EDGE, पूर्ण, /* TICK */
	अणु .type = S3C_IRQTYPE_EDGE, पूर्ण, /* WDT */
	अणु .type = S3C_IRQTYPE_EDGE, पूर्ण, /* TIMER0 */
	अणु .type = S3C_IRQTYPE_EDGE, पूर्ण, /* TIMER1 */
	अणु .type = S3C_IRQTYPE_EDGE, पूर्ण, /* TIMER2 */
	अणु .type = S3C_IRQTYPE_EDGE, पूर्ण, /* TIMER3 */
	अणु .type = S3C_IRQTYPE_EDGE, पूर्ण, /* TIMER4 */
	अणु .type = S3C_IRQTYPE_LEVEL, पूर्ण, /* UART2 */
	अणु .type = S3C_IRQTYPE_EDGE, पूर्ण, /* LCD */
	अणु .type = S3C_IRQTYPE_EDGE, पूर्ण, /* DMA0 */
	अणु .type = S3C_IRQTYPE_EDGE, पूर्ण, /* DMA1 */
	अणु .type = S3C_IRQTYPE_EDGE, पूर्ण, /* DMA2 */
	अणु .type = S3C_IRQTYPE_EDGE, पूर्ण, /* DMA3 */
	अणु .type = S3C_IRQTYPE_LEVEL, पूर्ण, /* SDI/CF */
	अणु .type = S3C_IRQTYPE_EDGE, पूर्ण, /* SPI0 */
	अणु .type = S3C_IRQTYPE_LEVEL, पूर्ण, /* UART1 */
	अणु .type = S3C_IRQTYPE_NONE, पूर्ण, /* reserved */
	अणु .type = S3C_IRQTYPE_EDGE, पूर्ण, /* USBD */
	अणु .type = S3C_IRQTYPE_EDGE, पूर्ण, /* USBH */
	अणु .type = S3C_IRQTYPE_EDGE, पूर्ण, /* IIC */
	अणु .type = S3C_IRQTYPE_LEVEL, पूर्ण, /* UART0 */
	अणु .type = S3C_IRQTYPE_EDGE, पूर्ण, /* SPI1 */
	अणु .type = S3C_IRQTYPE_EDGE, पूर्ण, /* RTC */
	अणु .type = S3C_IRQTYPE_LEVEL, पूर्ण, /* ADCPARENT */
पूर्ण;

अटल काष्ठा s3c_irq_data init_s3c2412eपूर्णांक[32] = अणु
	अणु .type = S3C_IRQTYPE_EINT, .parent_irq = 0 पूर्ण, /* EINT0 */
	अणु .type = S3C_IRQTYPE_EINT, .parent_irq = 1 पूर्ण, /* EINT1 */
	अणु .type = S3C_IRQTYPE_EINT, .parent_irq = 2 पूर्ण, /* EINT2 */
	अणु .type = S3C_IRQTYPE_EINT, .parent_irq = 3 पूर्ण, /* EINT3 */
	अणु .type = S3C_IRQTYPE_EINT, .parent_irq = 4 पूर्ण, /* EINT4 */
	अणु .type = S3C_IRQTYPE_EINT, .parent_irq = 4 पूर्ण, /* EINT5 */
	अणु .type = S3C_IRQTYPE_EINT, .parent_irq = 4 पूर्ण, /* EINT6 */
	अणु .type = S3C_IRQTYPE_EINT, .parent_irq = 4 पूर्ण, /* EINT7 */
	अणु .type = S3C_IRQTYPE_EINT, .parent_irq = 5 पूर्ण, /* EINT8 */
	अणु .type = S3C_IRQTYPE_EINT, .parent_irq = 5 पूर्ण, /* EINT9 */
	अणु .type = S3C_IRQTYPE_EINT, .parent_irq = 5 पूर्ण, /* EINT10 */
	अणु .type = S3C_IRQTYPE_EINT, .parent_irq = 5 पूर्ण, /* EINT11 */
	अणु .type = S3C_IRQTYPE_EINT, .parent_irq = 5 पूर्ण, /* EINT12 */
	अणु .type = S3C_IRQTYPE_EINT, .parent_irq = 5 पूर्ण, /* EINT13 */
	अणु .type = S3C_IRQTYPE_EINT, .parent_irq = 5 पूर्ण, /* EINT14 */
	अणु .type = S3C_IRQTYPE_EINT, .parent_irq = 5 पूर्ण, /* EINT15 */
	अणु .type = S3C_IRQTYPE_EINT, .parent_irq = 5 पूर्ण, /* EINT16 */
	अणु .type = S3C_IRQTYPE_EINT, .parent_irq = 5 पूर्ण, /* EINT17 */
	अणु .type = S3C_IRQTYPE_EINT, .parent_irq = 5 पूर्ण, /* EINT18 */
	अणु .type = S3C_IRQTYPE_EINT, .parent_irq = 5 पूर्ण, /* EINT19 */
	अणु .type = S3C_IRQTYPE_EINT, .parent_irq = 5 पूर्ण, /* EINT20 */
	अणु .type = S3C_IRQTYPE_EINT, .parent_irq = 5 पूर्ण, /* EINT21 */
	अणु .type = S3C_IRQTYPE_EINT, .parent_irq = 5 पूर्ण, /* EINT22 */
	अणु .type = S3C_IRQTYPE_EINT, .parent_irq = 5 पूर्ण, /* EINT23 */
पूर्ण;

अटल काष्ठा s3c_irq_data init_s3c2412subपूर्णांक[32] = अणु
	अणु .type = S3C_IRQTYPE_LEVEL, .parent_irq = 28 पूर्ण, /* UART0-RX */
	अणु .type = S3C_IRQTYPE_LEVEL, .parent_irq = 28 पूर्ण, /* UART0-TX */
	अणु .type = S3C_IRQTYPE_LEVEL, .parent_irq = 28 पूर्ण, /* UART0-ERR */
	अणु .type = S3C_IRQTYPE_LEVEL, .parent_irq = 23 पूर्ण, /* UART1-RX */
	अणु .type = S3C_IRQTYPE_LEVEL, .parent_irq = 23 पूर्ण, /* UART1-TX */
	अणु .type = S3C_IRQTYPE_LEVEL, .parent_irq = 23 पूर्ण, /* UART1-ERR */
	अणु .type = S3C_IRQTYPE_LEVEL, .parent_irq = 15 पूर्ण, /* UART2-RX */
	अणु .type = S3C_IRQTYPE_LEVEL, .parent_irq = 15 पूर्ण, /* UART2-TX */
	अणु .type = S3C_IRQTYPE_LEVEL, .parent_irq = 15 पूर्ण, /* UART2-ERR */
	अणु .type = S3C_IRQTYPE_EDGE, .parent_irq = 31 पूर्ण, /* TC */
	अणु .type = S3C_IRQTYPE_EDGE, .parent_irq = 31 पूर्ण, /* ADC */
	अणु .type = S3C_IRQTYPE_NONE, पूर्ण,
	अणु .type = S3C_IRQTYPE_NONE, पूर्ण,
	अणु .type = S3C_IRQTYPE_LEVEL, .parent_irq = 21 पूर्ण, /* SDI */
	अणु .type = S3C_IRQTYPE_LEVEL, .parent_irq = 21 पूर्ण, /* CF */
पूर्ण;

व्योम __init s3c2412_init_irq(व्योम)
अणु
	pr_info("S3C2412: IRQ Support\n");

#अगर_घोषित CONFIG_FIQ
	init_FIQ(FIQ_START);
#पूर्ण_अगर

	s3c_पूर्णांकc[0] = s3c24xx_init_पूर्णांकc(शून्य, &init_s3c2412base[0], शून्य,
					0x4a000000);
	अगर (IS_ERR(s3c_पूर्णांकc[0])) अणु
		pr_err("irq: could not create main interrupt controller\n");
		वापस;
	पूर्ण

	s3c24xx_init_पूर्णांकc(शून्य, &init_s3c2412eपूर्णांक[0], s3c_पूर्णांकc[0], 0x560000a4);
	s3c_पूर्णांकc[1] = s3c24xx_init_पूर्णांकc(शून्य, &init_s3c2412subपूर्णांक[0],
					s3c_पूर्णांकc[0], 0x4a000018);
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_CPU_S3C2416
अटल काष्ठा s3c_irq_data init_s3c2416base[32] = अणु
	अणु .type = S3C_IRQTYPE_EINT, पूर्ण, /* EINT0 */
	अणु .type = S3C_IRQTYPE_EINT, पूर्ण, /* EINT1 */
	अणु .type = S3C_IRQTYPE_EINT, पूर्ण, /* EINT2 */
	अणु .type = S3C_IRQTYPE_EINT, पूर्ण, /* EINT3 */
	अणु .type = S3C_IRQTYPE_LEVEL, पूर्ण, /* EINT4to7 */
	अणु .type = S3C_IRQTYPE_LEVEL, पूर्ण, /* EINT8to23 */
	अणु .type = S3C_IRQTYPE_NONE, पूर्ण, /* reserved */
	अणु .type = S3C_IRQTYPE_EDGE, पूर्ण, /* nBATT_FLT */
	अणु .type = S3C_IRQTYPE_EDGE, पूर्ण, /* TICK */
	अणु .type = S3C_IRQTYPE_LEVEL, पूर्ण, /* WDT/AC97 */
	अणु .type = S3C_IRQTYPE_EDGE, पूर्ण, /* TIMER0 */
	अणु .type = S3C_IRQTYPE_EDGE, पूर्ण, /* TIMER1 */
	अणु .type = S3C_IRQTYPE_EDGE, पूर्ण, /* TIMER2 */
	अणु .type = S3C_IRQTYPE_EDGE, पूर्ण, /* TIMER3 */
	अणु .type = S3C_IRQTYPE_EDGE, पूर्ण, /* TIMER4 */
	अणु .type = S3C_IRQTYPE_LEVEL, पूर्ण, /* UART2 */
	अणु .type = S3C_IRQTYPE_LEVEL, पूर्ण, /* LCD */
	अणु .type = S3C_IRQTYPE_LEVEL, पूर्ण, /* DMA */
	अणु .type = S3C_IRQTYPE_LEVEL, पूर्ण, /* UART3 */
	अणु .type = S3C_IRQTYPE_NONE, पूर्ण, /* reserved */
	अणु .type = S3C_IRQTYPE_EDGE, पूर्ण, /* SDI1 */
	अणु .type = S3C_IRQTYPE_EDGE, पूर्ण, /* SDI0 */
	अणु .type = S3C_IRQTYPE_EDGE, पूर्ण, /* SPI0 */
	अणु .type = S3C_IRQTYPE_LEVEL, पूर्ण, /* UART1 */
	अणु .type = S3C_IRQTYPE_EDGE, पूर्ण, /* न_अंकD */
	अणु .type = S3C_IRQTYPE_EDGE, पूर्ण, /* USBD */
	अणु .type = S3C_IRQTYPE_EDGE, पूर्ण, /* USBH */
	अणु .type = S3C_IRQTYPE_EDGE, पूर्ण, /* IIC */
	अणु .type = S3C_IRQTYPE_LEVEL, पूर्ण, /* UART0 */
	अणु .type = S3C_IRQTYPE_NONE, पूर्ण,
	अणु .type = S3C_IRQTYPE_EDGE, पूर्ण, /* RTC */
	अणु .type = S3C_IRQTYPE_LEVEL, पूर्ण, /* ADCPARENT */
पूर्ण;

अटल काष्ठा s3c_irq_data init_s3c2416subपूर्णांक[32] = अणु
	अणु .type = S3C_IRQTYPE_LEVEL, .parent_irq = 28 पूर्ण, /* UART0-RX */
	अणु .type = S3C_IRQTYPE_LEVEL, .parent_irq = 28 पूर्ण, /* UART0-TX */
	अणु .type = S3C_IRQTYPE_LEVEL, .parent_irq = 28 पूर्ण, /* UART0-ERR */
	अणु .type = S3C_IRQTYPE_LEVEL, .parent_irq = 23 पूर्ण, /* UART1-RX */
	अणु .type = S3C_IRQTYPE_LEVEL, .parent_irq = 23 पूर्ण, /* UART1-TX */
	अणु .type = S3C_IRQTYPE_LEVEL, .parent_irq = 23 पूर्ण, /* UART1-ERR */
	अणु .type = S3C_IRQTYPE_LEVEL, .parent_irq = 15 पूर्ण, /* UART2-RX */
	अणु .type = S3C_IRQTYPE_LEVEL, .parent_irq = 15 पूर्ण, /* UART2-TX */
	अणु .type = S3C_IRQTYPE_LEVEL, .parent_irq = 15 पूर्ण, /* UART2-ERR */
	अणु .type = S3C_IRQTYPE_EDGE, .parent_irq = 31 पूर्ण, /* TC */
	अणु .type = S3C_IRQTYPE_EDGE, .parent_irq = 31 पूर्ण, /* ADC */
	अणु .type = S3C_IRQTYPE_NONE पूर्ण, /* reserved */
	अणु .type = S3C_IRQTYPE_NONE पूर्ण, /* reserved */
	अणु .type = S3C_IRQTYPE_NONE पूर्ण, /* reserved */
	अणु .type = S3C_IRQTYPE_NONE पूर्ण, /* reserved */
	अणु .type = S3C_IRQTYPE_LEVEL, .parent_irq = 16 पूर्ण, /* LCD2 */
	अणु .type = S3C_IRQTYPE_LEVEL, .parent_irq = 16 पूर्ण, /* LCD3 */
	अणु .type = S3C_IRQTYPE_LEVEL, .parent_irq = 16 पूर्ण, /* LCD4 */
	अणु .type = S3C_IRQTYPE_LEVEL, .parent_irq = 17 पूर्ण, /* DMA0 */
	अणु .type = S3C_IRQTYPE_LEVEL, .parent_irq = 17 पूर्ण, /* DMA1 */
	अणु .type = S3C_IRQTYPE_LEVEL, .parent_irq = 17 पूर्ण, /* DMA2 */
	अणु .type = S3C_IRQTYPE_LEVEL, .parent_irq = 17 पूर्ण, /* DMA3 */
	अणु .type = S3C_IRQTYPE_LEVEL, .parent_irq = 17 पूर्ण, /* DMA4 */
	अणु .type = S3C_IRQTYPE_LEVEL, .parent_irq = 17 पूर्ण, /* DMA5 */
	अणु .type = S3C_IRQTYPE_LEVEL, .parent_irq = 18 पूर्ण, /* UART3-RX */
	अणु .type = S3C_IRQTYPE_LEVEL, .parent_irq = 18 पूर्ण, /* UART3-TX */
	अणु .type = S3C_IRQTYPE_LEVEL, .parent_irq = 18 पूर्ण, /* UART3-ERR */
	अणु .type = S3C_IRQTYPE_LEVEL, .parent_irq = 9 पूर्ण, /* WDT */
	अणु .type = S3C_IRQTYPE_LEVEL, .parent_irq = 9 पूर्ण, /* AC97 */
पूर्ण;

अटल काष्ठा s3c_irq_data init_s3c2416_second[32] = अणु
	अणु .type = S3C_IRQTYPE_EDGE पूर्ण, /* 2D */
	अणु .type = S3C_IRQTYPE_NONE पूर्ण, /* reserved */
	अणु .type = S3C_IRQTYPE_NONE पूर्ण, /* reserved */
	अणु .type = S3C_IRQTYPE_NONE पूर्ण, /* reserved */
	अणु .type = S3C_IRQTYPE_EDGE पूर्ण, /* PCM0 */
	अणु .type = S3C_IRQTYPE_NONE पूर्ण, /* reserved */
	अणु .type = S3C_IRQTYPE_EDGE पूर्ण, /* I2S0 */
पूर्ण;

व्योम __init s3c2416_init_irq(व्योम)
अणु
	pr_info("S3C2416: IRQ Support\n");

#अगर_घोषित CONFIG_FIQ
	init_FIQ(FIQ_START);
#पूर्ण_अगर

	s3c_पूर्णांकc[0] = s3c24xx_init_पूर्णांकc(शून्य, &init_s3c2416base[0], शून्य,
					0x4a000000);
	अगर (IS_ERR(s3c_पूर्णांकc[0])) अणु
		pr_err("irq: could not create main interrupt controller\n");
		वापस;
	पूर्ण

	s3c24xx_init_पूर्णांकc(शून्य, &init_eपूर्णांक[0], s3c_पूर्णांकc[0], 0x560000a4);
	s3c_पूर्णांकc[1] = s3c24xx_init_पूर्णांकc(शून्य, &init_s3c2416subपूर्णांक[0],
					s3c_पूर्णांकc[0], 0x4a000018);

	s3c_पूर्णांकc[2] = s3c24xx_init_पूर्णांकc(शून्य, &init_s3c2416_second[0],
					शून्य, 0x4a000040);
पूर्ण

#पूर्ण_अगर

#अगर_घोषित CONFIG_CPU_S3C2440
अटल काष्ठा s3c_irq_data init_s3c2440base[32] = अणु
	अणु .type = S3C_IRQTYPE_EINT, पूर्ण, /* EINT0 */
	अणु .type = S3C_IRQTYPE_EINT, पूर्ण, /* EINT1 */
	अणु .type = S3C_IRQTYPE_EINT, पूर्ण, /* EINT2 */
	अणु .type = S3C_IRQTYPE_EINT, पूर्ण, /* EINT3 */
	अणु .type = S3C_IRQTYPE_LEVEL, पूर्ण, /* EINT4to7 */
	अणु .type = S3C_IRQTYPE_LEVEL, पूर्ण, /* EINT8to23 */
	अणु .type = S3C_IRQTYPE_LEVEL, पूर्ण, /* CAM */
	अणु .type = S3C_IRQTYPE_EDGE, पूर्ण, /* nBATT_FLT */
	अणु .type = S3C_IRQTYPE_EDGE, पूर्ण, /* TICK */
	अणु .type = S3C_IRQTYPE_LEVEL, पूर्ण, /* WDT/AC97 */
	अणु .type = S3C_IRQTYPE_EDGE, पूर्ण, /* TIMER0 */
	अणु .type = S3C_IRQTYPE_EDGE, पूर्ण, /* TIMER1 */
	अणु .type = S3C_IRQTYPE_EDGE, पूर्ण, /* TIMER2 */
	अणु .type = S3C_IRQTYPE_EDGE, पूर्ण, /* TIMER3 */
	अणु .type = S3C_IRQTYPE_EDGE, पूर्ण, /* TIMER4 */
	अणु .type = S3C_IRQTYPE_LEVEL, पूर्ण, /* UART2 */
	अणु .type = S3C_IRQTYPE_EDGE, पूर्ण, /* LCD */
	अणु .type = S3C_IRQTYPE_EDGE, पूर्ण, /* DMA0 */
	अणु .type = S3C_IRQTYPE_EDGE, पूर्ण, /* DMA1 */
	अणु .type = S3C_IRQTYPE_EDGE, पूर्ण, /* DMA2 */
	अणु .type = S3C_IRQTYPE_EDGE, पूर्ण, /* DMA3 */
	अणु .type = S3C_IRQTYPE_EDGE, पूर्ण, /* SDI */
	अणु .type = S3C_IRQTYPE_EDGE, पूर्ण, /* SPI0 */
	अणु .type = S3C_IRQTYPE_LEVEL, पूर्ण, /* UART1 */
	अणु .type = S3C_IRQTYPE_LEVEL, पूर्ण, /* NFCON */
	अणु .type = S3C_IRQTYPE_EDGE, पूर्ण, /* USBD */
	अणु .type = S3C_IRQTYPE_EDGE, पूर्ण, /* USBH */
	अणु .type = S3C_IRQTYPE_EDGE, पूर्ण, /* IIC */
	अणु .type = S3C_IRQTYPE_LEVEL, पूर्ण, /* UART0 */
	अणु .type = S3C_IRQTYPE_EDGE, पूर्ण, /* SPI1 */
	अणु .type = S3C_IRQTYPE_EDGE, पूर्ण, /* RTC */
	अणु .type = S3C_IRQTYPE_LEVEL, पूर्ण, /* ADCPARENT */
पूर्ण;

अटल काष्ठा s3c_irq_data init_s3c2440subपूर्णांक[32] = अणु
	अणु .type = S3C_IRQTYPE_LEVEL, .parent_irq = 28 पूर्ण, /* UART0-RX */
	अणु .type = S3C_IRQTYPE_LEVEL, .parent_irq = 28 पूर्ण, /* UART0-TX */
	अणु .type = S3C_IRQTYPE_LEVEL, .parent_irq = 28 पूर्ण, /* UART0-ERR */
	अणु .type = S3C_IRQTYPE_LEVEL, .parent_irq = 23 पूर्ण, /* UART1-RX */
	अणु .type = S3C_IRQTYPE_LEVEL, .parent_irq = 23 पूर्ण, /* UART1-TX */
	अणु .type = S3C_IRQTYPE_LEVEL, .parent_irq = 23 पूर्ण, /* UART1-ERR */
	अणु .type = S3C_IRQTYPE_LEVEL, .parent_irq = 15 पूर्ण, /* UART2-RX */
	अणु .type = S3C_IRQTYPE_LEVEL, .parent_irq = 15 पूर्ण, /* UART2-TX */
	अणु .type = S3C_IRQTYPE_LEVEL, .parent_irq = 15 पूर्ण, /* UART2-ERR */
	अणु .type = S3C_IRQTYPE_EDGE, .parent_irq = 31 पूर्ण, /* TC */
	अणु .type = S3C_IRQTYPE_EDGE, .parent_irq = 31 पूर्ण, /* ADC */
	अणु .type = S3C_IRQTYPE_LEVEL, .parent_irq = 6 पूर्ण, /* CAM_C */
	अणु .type = S3C_IRQTYPE_LEVEL, .parent_irq = 6 पूर्ण, /* CAM_P */
	अणु .type = S3C_IRQTYPE_LEVEL, .parent_irq = 9 पूर्ण, /* WDT */
	अणु .type = S3C_IRQTYPE_LEVEL, .parent_irq = 9 पूर्ण, /* AC97 */
पूर्ण;

व्योम __init s3c2440_init_irq(व्योम)
अणु
	pr_info("S3C2440: IRQ Support\n");

#अगर_घोषित CONFIG_FIQ
	init_FIQ(FIQ_START);
#पूर्ण_अगर

	s3c_पूर्णांकc[0] = s3c24xx_init_पूर्णांकc(शून्य, &init_s3c2440base[0], शून्य,
					0x4a000000);
	अगर (IS_ERR(s3c_पूर्णांकc[0])) अणु
		pr_err("irq: could not create main interrupt controller\n");
		वापस;
	पूर्ण

	s3c24xx_init_पूर्णांकc(शून्य, &init_eपूर्णांक[0], s3c_पूर्णांकc[0], 0x560000a4);
	s3c_पूर्णांकc[1] = s3c24xx_init_पूर्णांकc(शून्य, &init_s3c2440subपूर्णांक[0],
					s3c_पूर्णांकc[0], 0x4a000018);
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_CPU_S3C2442
अटल काष्ठा s3c_irq_data init_s3c2442base[32] = अणु
	अणु .type = S3C_IRQTYPE_EINT, पूर्ण, /* EINT0 */
	अणु .type = S3C_IRQTYPE_EINT, पूर्ण, /* EINT1 */
	अणु .type = S3C_IRQTYPE_EINT, पूर्ण, /* EINT2 */
	अणु .type = S3C_IRQTYPE_EINT, पूर्ण, /* EINT3 */
	अणु .type = S3C_IRQTYPE_LEVEL, पूर्ण, /* EINT4to7 */
	अणु .type = S3C_IRQTYPE_LEVEL, पूर्ण, /* EINT8to23 */
	अणु .type = S3C_IRQTYPE_LEVEL, पूर्ण, /* CAM */
	अणु .type = S3C_IRQTYPE_EDGE, पूर्ण, /* nBATT_FLT */
	अणु .type = S3C_IRQTYPE_EDGE, पूर्ण, /* TICK */
	अणु .type = S3C_IRQTYPE_EDGE, पूर्ण, /* WDT */
	अणु .type = S3C_IRQTYPE_EDGE, पूर्ण, /* TIMER0 */
	अणु .type = S3C_IRQTYPE_EDGE, पूर्ण, /* TIMER1 */
	अणु .type = S3C_IRQTYPE_EDGE, पूर्ण, /* TIMER2 */
	अणु .type = S3C_IRQTYPE_EDGE, पूर्ण, /* TIMER3 */
	अणु .type = S3C_IRQTYPE_EDGE, पूर्ण, /* TIMER4 */
	अणु .type = S3C_IRQTYPE_LEVEL, पूर्ण, /* UART2 */
	अणु .type = S3C_IRQTYPE_EDGE, पूर्ण, /* LCD */
	अणु .type = S3C_IRQTYPE_EDGE, पूर्ण, /* DMA0 */
	अणु .type = S3C_IRQTYPE_EDGE, पूर्ण, /* DMA1 */
	अणु .type = S3C_IRQTYPE_EDGE, पूर्ण, /* DMA2 */
	अणु .type = S3C_IRQTYPE_EDGE, पूर्ण, /* DMA3 */
	अणु .type = S3C_IRQTYPE_EDGE, पूर्ण, /* SDI */
	अणु .type = S3C_IRQTYPE_EDGE, पूर्ण, /* SPI0 */
	अणु .type = S3C_IRQTYPE_LEVEL, पूर्ण, /* UART1 */
	अणु .type = S3C_IRQTYPE_LEVEL, पूर्ण, /* NFCON */
	अणु .type = S3C_IRQTYPE_EDGE, पूर्ण, /* USBD */
	अणु .type = S3C_IRQTYPE_EDGE, पूर्ण, /* USBH */
	अणु .type = S3C_IRQTYPE_EDGE, पूर्ण, /* IIC */
	अणु .type = S3C_IRQTYPE_LEVEL, पूर्ण, /* UART0 */
	अणु .type = S3C_IRQTYPE_EDGE, पूर्ण, /* SPI1 */
	अणु .type = S3C_IRQTYPE_EDGE, पूर्ण, /* RTC */
	अणु .type = S3C_IRQTYPE_LEVEL, पूर्ण, /* ADCPARENT */
पूर्ण;

अटल काष्ठा s3c_irq_data init_s3c2442subपूर्णांक[32] = अणु
	अणु .type = S3C_IRQTYPE_LEVEL, .parent_irq = 28 पूर्ण, /* UART0-RX */
	अणु .type = S3C_IRQTYPE_LEVEL, .parent_irq = 28 पूर्ण, /* UART0-TX */
	अणु .type = S3C_IRQTYPE_LEVEL, .parent_irq = 28 पूर्ण, /* UART0-ERR */
	अणु .type = S3C_IRQTYPE_LEVEL, .parent_irq = 23 पूर्ण, /* UART1-RX */
	अणु .type = S3C_IRQTYPE_LEVEL, .parent_irq = 23 पूर्ण, /* UART1-TX */
	अणु .type = S3C_IRQTYPE_LEVEL, .parent_irq = 23 पूर्ण, /* UART1-ERR */
	अणु .type = S3C_IRQTYPE_LEVEL, .parent_irq = 15 पूर्ण, /* UART2-RX */
	अणु .type = S3C_IRQTYPE_LEVEL, .parent_irq = 15 पूर्ण, /* UART2-TX */
	अणु .type = S3C_IRQTYPE_LEVEL, .parent_irq = 15 पूर्ण, /* UART2-ERR */
	अणु .type = S3C_IRQTYPE_EDGE, .parent_irq = 31 पूर्ण, /* TC */
	अणु .type = S3C_IRQTYPE_EDGE, .parent_irq = 31 पूर्ण, /* ADC */
	अणु .type = S3C_IRQTYPE_LEVEL, .parent_irq = 6 पूर्ण, /* CAM_C */
	अणु .type = S3C_IRQTYPE_LEVEL, .parent_irq = 6 पूर्ण, /* CAM_P */
पूर्ण;

व्योम __init s3c2442_init_irq(व्योम)
अणु
	pr_info("S3C2442: IRQ Support\n");

#अगर_घोषित CONFIG_FIQ
	init_FIQ(FIQ_START);
#पूर्ण_अगर

	s3c_पूर्णांकc[0] = s3c24xx_init_पूर्णांकc(शून्य, &init_s3c2442base[0], शून्य,
					0x4a000000);
	अगर (IS_ERR(s3c_पूर्णांकc[0])) अणु
		pr_err("irq: could not create main interrupt controller\n");
		वापस;
	पूर्ण

	s3c24xx_init_पूर्णांकc(शून्य, &init_eपूर्णांक[0], s3c_पूर्णांकc[0], 0x560000a4);
	s3c_पूर्णांकc[1] = s3c24xx_init_पूर्णांकc(शून्य, &init_s3c2442subपूर्णांक[0],
					s3c_पूर्णांकc[0], 0x4a000018);
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_CPU_S3C2443
अटल काष्ठा s3c_irq_data init_s3c2443base[32] = अणु
	अणु .type = S3C_IRQTYPE_EINT, पूर्ण, /* EINT0 */
	अणु .type = S3C_IRQTYPE_EINT, पूर्ण, /* EINT1 */
	अणु .type = S3C_IRQTYPE_EINT, पूर्ण, /* EINT2 */
	अणु .type = S3C_IRQTYPE_EINT, पूर्ण, /* EINT3 */
	अणु .type = S3C_IRQTYPE_LEVEL, पूर्ण, /* EINT4to7 */
	अणु .type = S3C_IRQTYPE_LEVEL, पूर्ण, /* EINT8to23 */
	अणु .type = S3C_IRQTYPE_LEVEL, पूर्ण, /* CAM */
	अणु .type = S3C_IRQTYPE_EDGE, पूर्ण, /* nBATT_FLT */
	अणु .type = S3C_IRQTYPE_EDGE, पूर्ण, /* TICK */
	अणु .type = S3C_IRQTYPE_LEVEL, पूर्ण, /* WDT/AC97 */
	अणु .type = S3C_IRQTYPE_EDGE, पूर्ण, /* TIMER0 */
	अणु .type = S3C_IRQTYPE_EDGE, पूर्ण, /* TIMER1 */
	अणु .type = S3C_IRQTYPE_EDGE, पूर्ण, /* TIMER2 */
	अणु .type = S3C_IRQTYPE_EDGE, पूर्ण, /* TIMER3 */
	अणु .type = S3C_IRQTYPE_EDGE, पूर्ण, /* TIMER4 */
	अणु .type = S3C_IRQTYPE_LEVEL, पूर्ण, /* UART2 */
	अणु .type = S3C_IRQTYPE_LEVEL, पूर्ण, /* LCD */
	अणु .type = S3C_IRQTYPE_LEVEL, पूर्ण, /* DMA */
	अणु .type = S3C_IRQTYPE_LEVEL, पूर्ण, /* UART3 */
	अणु .type = S3C_IRQTYPE_EDGE, पूर्ण, /* CFON */
	अणु .type = S3C_IRQTYPE_EDGE, पूर्ण, /* SDI1 */
	अणु .type = S3C_IRQTYPE_EDGE, पूर्ण, /* SDI0 */
	अणु .type = S3C_IRQTYPE_EDGE, पूर्ण, /* SPI0 */
	अणु .type = S3C_IRQTYPE_LEVEL, पूर्ण, /* UART1 */
	अणु .type = S3C_IRQTYPE_EDGE, पूर्ण, /* न_अंकD */
	अणु .type = S3C_IRQTYPE_EDGE, पूर्ण, /* USBD */
	अणु .type = S3C_IRQTYPE_EDGE, पूर्ण, /* USBH */
	अणु .type = S3C_IRQTYPE_EDGE, पूर्ण, /* IIC */
	अणु .type = S3C_IRQTYPE_LEVEL, पूर्ण, /* UART0 */
	अणु .type = S3C_IRQTYPE_EDGE, पूर्ण, /* SPI1 */
	अणु .type = S3C_IRQTYPE_EDGE, पूर्ण, /* RTC */
	अणु .type = S3C_IRQTYPE_LEVEL, पूर्ण, /* ADCPARENT */
पूर्ण;


अटल काष्ठा s3c_irq_data init_s3c2443subपूर्णांक[32] = अणु
	अणु .type = S3C_IRQTYPE_LEVEL, .parent_irq = 28 पूर्ण, /* UART0-RX */
	अणु .type = S3C_IRQTYPE_LEVEL, .parent_irq = 28 पूर्ण, /* UART0-TX */
	अणु .type = S3C_IRQTYPE_LEVEL, .parent_irq = 28 पूर्ण, /* UART0-ERR */
	अणु .type = S3C_IRQTYPE_LEVEL, .parent_irq = 23 पूर्ण, /* UART1-RX */
	अणु .type = S3C_IRQTYPE_LEVEL, .parent_irq = 23 पूर्ण, /* UART1-TX */
	अणु .type = S3C_IRQTYPE_LEVEL, .parent_irq = 23 पूर्ण, /* UART1-ERR */
	अणु .type = S3C_IRQTYPE_LEVEL, .parent_irq = 15 पूर्ण, /* UART2-RX */
	अणु .type = S3C_IRQTYPE_LEVEL, .parent_irq = 15 पूर्ण, /* UART2-TX */
	अणु .type = S3C_IRQTYPE_LEVEL, .parent_irq = 15 पूर्ण, /* UART2-ERR */
	अणु .type = S3C_IRQTYPE_EDGE, .parent_irq = 31 पूर्ण, /* TC */
	अणु .type = S3C_IRQTYPE_EDGE, .parent_irq = 31 पूर्ण, /* ADC */
	अणु .type = S3C_IRQTYPE_LEVEL, .parent_irq = 6 पूर्ण, /* CAM_C */
	अणु .type = S3C_IRQTYPE_LEVEL, .parent_irq = 6 पूर्ण, /* CAM_P */
	अणु .type = S3C_IRQTYPE_NONE पूर्ण, /* reserved */
	अणु .type = S3C_IRQTYPE_LEVEL, .parent_irq = 16 पूर्ण, /* LCD1 */
	अणु .type = S3C_IRQTYPE_LEVEL, .parent_irq = 16 पूर्ण, /* LCD2 */
	अणु .type = S3C_IRQTYPE_LEVEL, .parent_irq = 16 पूर्ण, /* LCD3 */
	अणु .type = S3C_IRQTYPE_LEVEL, .parent_irq = 16 पूर्ण, /* LCD4 */
	अणु .type = S3C_IRQTYPE_LEVEL, .parent_irq = 17 पूर्ण, /* DMA0 */
	अणु .type = S3C_IRQTYPE_LEVEL, .parent_irq = 17 पूर्ण, /* DMA1 */
	अणु .type = S3C_IRQTYPE_LEVEL, .parent_irq = 17 पूर्ण, /* DMA2 */
	अणु .type = S3C_IRQTYPE_LEVEL, .parent_irq = 17 पूर्ण, /* DMA3 */
	अणु .type = S3C_IRQTYPE_LEVEL, .parent_irq = 17 पूर्ण, /* DMA4 */
	अणु .type = S3C_IRQTYPE_LEVEL, .parent_irq = 17 पूर्ण, /* DMA5 */
	अणु .type = S3C_IRQTYPE_LEVEL, .parent_irq = 18 पूर्ण, /* UART3-RX */
	अणु .type = S3C_IRQTYPE_LEVEL, .parent_irq = 18 पूर्ण, /* UART3-TX */
	अणु .type = S3C_IRQTYPE_LEVEL, .parent_irq = 18 पूर्ण, /* UART3-ERR */
	अणु .type = S3C_IRQTYPE_LEVEL, .parent_irq = 9 पूर्ण, /* WDT */
	अणु .type = S3C_IRQTYPE_LEVEL, .parent_irq = 9 पूर्ण, /* AC97 */
पूर्ण;

व्योम __init s3c2443_init_irq(व्योम)
अणु
	pr_info("S3C2443: IRQ Support\n");

#अगर_घोषित CONFIG_FIQ
	init_FIQ(FIQ_START);
#पूर्ण_अगर

	s3c_पूर्णांकc[0] = s3c24xx_init_पूर्णांकc(शून्य, &init_s3c2443base[0], शून्य,
					0x4a000000);
	अगर (IS_ERR(s3c_पूर्णांकc[0])) अणु
		pr_err("irq: could not create main interrupt controller\n");
		वापस;
	पूर्ण

	s3c24xx_init_पूर्णांकc(शून्य, &init_eपूर्णांक[0], s3c_पूर्णांकc[0], 0x560000a4);
	s3c_पूर्णांकc[1] = s3c24xx_init_पूर्णांकc(शून्य, &init_s3c2443subपूर्णांक[0],
					s3c_पूर्णांकc[0], 0x4a000018);
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_OF
अटल पूर्णांक s3c24xx_irq_map_of(काष्ठा irq_करोमुख्य *h, अचिन्हित पूर्णांक virq,
							irq_hw_number_t hw)
अणु
	अचिन्हित पूर्णांक ctrl_num = hw / 32;
	अचिन्हित पूर्णांक पूर्णांकc_hw = hw % 32;
	काष्ठा s3c_irq_पूर्णांकc *पूर्णांकc = s3c_पूर्णांकc[ctrl_num];
	काष्ठा s3c_irq_पूर्णांकc *parent_पूर्णांकc = पूर्णांकc->parent;
	काष्ठा s3c_irq_data *irq_data = &पूर्णांकc->irqs[पूर्णांकc_hw];

	/* attach controller poपूर्णांकer to irq_data */
	irq_data->पूर्णांकc = पूर्णांकc;
	irq_data->offset = पूर्णांकc_hw;

	अगर (!parent_पूर्णांकc)
		irq_set_chip_and_handler(virq, &s3c_irq_chip, handle_edge_irq);
	अन्यथा
		irq_set_chip_and_handler(virq, &s3c_irq_level_chip,
					 handle_edge_irq);

	irq_set_chip_data(virq, irq_data);

	वापस 0;
पूर्ण

/* Translate our of irq notation
 * क्रमmat: <ctrl_num ctrl_irq parent_irq type>
 */
अटल पूर्णांक s3c24xx_irq_xlate_of(काष्ठा irq_करोमुख्य *d, काष्ठा device_node *n,
			स्थिर u32 *पूर्णांकspec, अचिन्हित पूर्णांक पूर्णांकsize,
			irq_hw_number_t *out_hwirq, अचिन्हित पूर्णांक *out_type)
अणु
	काष्ठा s3c_irq_पूर्णांकc *पूर्णांकc;
	काष्ठा s3c_irq_पूर्णांकc *parent_पूर्णांकc;
	काष्ठा s3c_irq_data *irq_data;
	काष्ठा s3c_irq_data *parent_irq_data;
	पूर्णांक irqno;

	अगर (WARN_ON(पूर्णांकsize < 4))
		वापस -EINVAL;

	अगर (पूर्णांकspec[0] > 2 || !s3c_पूर्णांकc[पूर्णांकspec[0]]) अणु
		pr_err("controller number %d invalid\n", पूर्णांकspec[0]);
		वापस -EINVAL;
	पूर्ण
	पूर्णांकc = s3c_पूर्णांकc[पूर्णांकspec[0]];

	*out_hwirq = पूर्णांकspec[0] * 32 + पूर्णांकspec[2];
	*out_type = पूर्णांकspec[3] & IRQ_TYPE_SENSE_MASK;

	parent_पूर्णांकc = पूर्णांकc->parent;
	अगर (parent_पूर्णांकc) अणु
		irq_data = &पूर्णांकc->irqs[पूर्णांकspec[2]];
		irq_data->parent_irq = पूर्णांकspec[1];
		parent_irq_data = &parent_पूर्णांकc->irqs[irq_data->parent_irq];
		parent_irq_data->sub_पूर्णांकc = पूर्णांकc;
		parent_irq_data->sub_bits |= (1UL << पूर्णांकspec[2]);

		/* parent_पूर्णांकc is always s3c_पूर्णांकc[0], so no offset */
		irqno = irq_create_mapping(parent_पूर्णांकc->करोमुख्य, पूर्णांकspec[1]);
		अगर (irqno < 0) अणु
			pr_err("irq: could not map parent interrupt\n");
			वापस irqno;
		पूर्ण

		irq_set_chained_handler(irqno, s3c_irq_demux);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops s3c24xx_irq_ops_of = अणु
	.map = s3c24xx_irq_map_of,
	.xlate = s3c24xx_irq_xlate_of,
पूर्ण;

काष्ठा s3c24xx_irq_of_ctrl अणु
	अक्षर			*name;
	अचिन्हित दीर्घ		offset;
	काष्ठा s3c_irq_पूर्णांकc	**handle;
	काष्ठा s3c_irq_पूर्णांकc	**parent;
	काष्ठा irq_करोमुख्य_ops	*ops;
पूर्ण;

अटल पूर्णांक __init s3c_init_पूर्णांकc_of(काष्ठा device_node *np,
			काष्ठा device_node *पूर्णांकerrupt_parent,
			काष्ठा s3c24xx_irq_of_ctrl *s3c_ctrl, पूर्णांक num_ctrl)
अणु
	काष्ठा s3c_irq_पूर्णांकc *पूर्णांकc;
	काष्ठा s3c24xx_irq_of_ctrl *ctrl;
	काष्ठा irq_करोमुख्य *करोमुख्य;
	व्योम __iomem *reg_base;
	पूर्णांक i;

	reg_base = of_iomap(np, 0);
	अगर (!reg_base) अणु
		pr_err("irq-s3c24xx: could not map irq registers\n");
		वापस -EINVAL;
	पूर्ण

	करोमुख्य = irq_करोमुख्य_add_linear(np, num_ctrl * 32,
						     &s3c24xx_irq_ops_of, शून्य);
	अगर (!करोमुख्य) अणु
		pr_err("irq: could not create irq-domain\n");
		वापस -EINVAL;
	पूर्ण

	क्रम (i = 0; i < num_ctrl; i++) अणु
		ctrl = &s3c_ctrl[i];

		pr_debug("irq: found controller %s\n", ctrl->name);

		पूर्णांकc = kzalloc(माप(काष्ठा s3c_irq_पूर्णांकc), GFP_KERNEL);
		अगर (!पूर्णांकc)
			वापस -ENOMEM;

		पूर्णांकc->करोमुख्य = करोमुख्य;
		पूर्णांकc->irqs = kसुस्मृति(32, माप(काष्ठा s3c_irq_data),
				     GFP_KERNEL);
		अगर (!पूर्णांकc->irqs) अणु
			kमुक्त(पूर्णांकc);
			वापस -ENOMEM;
		पूर्ण

		अगर (ctrl->parent) अणु
			पूर्णांकc->reg_pending = reg_base + ctrl->offset;
			पूर्णांकc->reg_mask = reg_base + ctrl->offset + 0x4;

			अगर (*(ctrl->parent)) अणु
				पूर्णांकc->parent = *(ctrl->parent);
			पूर्ण अन्यथा अणु
				pr_warn("irq: parent of %s missing\n",
					ctrl->name);
				kमुक्त(पूर्णांकc->irqs);
				kमुक्त(पूर्णांकc);
				जारी;
			पूर्ण
		पूर्ण अन्यथा अणु
			पूर्णांकc->reg_pending = reg_base + ctrl->offset;
			पूर्णांकc->reg_mask = reg_base + ctrl->offset + 0x08;
			पूर्णांकc->reg_पूर्णांकpnd = reg_base + ctrl->offset + 0x10;
		पूर्ण

		s3c24xx_clear_पूर्णांकc(पूर्णांकc);
		s3c_पूर्णांकc[i] = पूर्णांकc;
	पूर्ण

	set_handle_irq(s3c24xx_handle_irq);

	वापस 0;
पूर्ण

अटल काष्ठा s3c24xx_irq_of_ctrl s3c2410_ctrl[] = अणु
	अणु
		.name = "intc",
		.offset = 0,
	पूर्ण, अणु
		.name = "subintc",
		.offset = 0x18,
		.parent = &s3c_पूर्णांकc[0],
	पूर्ण
पूर्ण;

अटल पूर्णांक __init s3c2410_init_पूर्णांकc_of(काष्ठा device_node *np,
			काष्ठा device_node *पूर्णांकerrupt_parent)
अणु
	वापस s3c_init_पूर्णांकc_of(np, पूर्णांकerrupt_parent,
				s3c2410_ctrl, ARRAY_SIZE(s3c2410_ctrl));
पूर्ण
IRQCHIP_DECLARE(s3c2410_irq, "samsung,s3c2410-irq", s3c2410_init_पूर्णांकc_of);

अटल काष्ठा s3c24xx_irq_of_ctrl s3c2416_ctrl[] = अणु
	अणु
		.name = "intc",
		.offset = 0,
	पूर्ण, अणु
		.name = "subintc",
		.offset = 0x18,
		.parent = &s3c_पूर्णांकc[0],
	पूर्ण, अणु
		.name = "intc2",
		.offset = 0x40,
	पूर्ण
पूर्ण;

अटल पूर्णांक __init s3c2416_init_पूर्णांकc_of(काष्ठा device_node *np,
			काष्ठा device_node *पूर्णांकerrupt_parent)
अणु
	वापस s3c_init_पूर्णांकc_of(np, पूर्णांकerrupt_parent,
				s3c2416_ctrl, ARRAY_SIZE(s3c2416_ctrl));
पूर्ण
IRQCHIP_DECLARE(s3c2416_irq, "samsung,s3c2416-irq", s3c2416_init_पूर्णांकc_of);
#पूर्ण_अगर
