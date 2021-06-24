<शैली गुरु>
/*
 *  Driver क्रम ePAPR Embedded Hypervisor PIC
 *
 *  Copyright 2008-2011 Freescale Semiconductor, Inc.
 *
 *  Author: Ashish Kalra <ashish.kalra@मुक्तscale.com>
 *
 * This file is licensed under the terms of the GNU General Public License
 * version 2.  This program is licensed "as is" without any warranty of any
 * kind, whether express or implied.
 */

#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/irq.h>
#समावेश <linux/smp.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>

#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/smp.h>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/ehv_pic.h>
#समावेश <यंत्र/fsl_hcalls.h>

अटल काष्ठा ehv_pic *global_ehv_pic;
अटल DEFINE_SPINLOCK(ehv_pic_lock);

अटल u32 hwirq_पूर्णांकspec[NR_EHV_PIC_INTS];
अटल u32 __iomem *mpic_percpu_base_vaddr;

#घोषणा IRQ_TYPE_MPIC_सूचीECT 4
#घोषणा MPIC_EOI  0x00B0

/*
 * Linux descriptor level callbacks
 */

व्योम ehv_pic_unmask_irq(काष्ठा irq_data *d)
अणु
	अचिन्हित पूर्णांक src = virq_to_hw(d->irq);

	ev_पूर्णांक_set_mask(src, 0);
पूर्ण

व्योम ehv_pic_mask_irq(काष्ठा irq_data *d)
अणु
	अचिन्हित पूर्णांक src = virq_to_hw(d->irq);

	ev_पूर्णांक_set_mask(src, 1);
पूर्ण

व्योम ehv_pic_end_irq(काष्ठा irq_data *d)
अणु
	अचिन्हित पूर्णांक src = virq_to_hw(d->irq);

	ev_पूर्णांक_eoi(src);
पूर्ण

व्योम ehv_pic_direct_end_irq(काष्ठा irq_data *d)
अणु
	out_be32(mpic_percpu_base_vaddr + MPIC_EOI / 4, 0);
पूर्ण

पूर्णांक ehv_pic_set_affinity(काष्ठा irq_data *d, स्थिर काष्ठा cpumask *dest,
			 bool क्रमce)
अणु
	अचिन्हित पूर्णांक src = virq_to_hw(d->irq);
	अचिन्हित पूर्णांक config, prio, cpu_dest;
	पूर्णांक cpuid = irq_choose_cpu(dest);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ehv_pic_lock, flags);
	ev_पूर्णांक_get_config(src, &config, &prio, &cpu_dest);
	ev_पूर्णांक_set_config(src, config, prio, cpuid);
	spin_unlock_irqrestore(&ehv_pic_lock, flags);

	वापस IRQ_SET_MASK_OK;
पूर्ण

अटल अचिन्हित पूर्णांक ehv_pic_type_to_vecpri(अचिन्हित पूर्णांक type)
अणु
	/* Now convert sense value */

	चयन (type & IRQ_TYPE_SENSE_MASK) अणु
	हाल IRQ_TYPE_EDGE_RISING:
		वापस EHV_PIC_INFO(VECPRI_SENSE_EDGE) |
		       EHV_PIC_INFO(VECPRI_POLARITY_POSITIVE);

	हाल IRQ_TYPE_EDGE_FALLING:
	हाल IRQ_TYPE_EDGE_BOTH:
		वापस EHV_PIC_INFO(VECPRI_SENSE_EDGE) |
		       EHV_PIC_INFO(VECPRI_POLARITY_NEGATIVE);

	हाल IRQ_TYPE_LEVEL_HIGH:
		वापस EHV_PIC_INFO(VECPRI_SENSE_LEVEL) |
		       EHV_PIC_INFO(VECPRI_POLARITY_POSITIVE);

	हाल IRQ_TYPE_LEVEL_LOW:
	शेष:
		वापस EHV_PIC_INFO(VECPRI_SENSE_LEVEL) |
		       EHV_PIC_INFO(VECPRI_POLARITY_NEGATIVE);
	पूर्ण
पूर्ण

पूर्णांक ehv_pic_set_irq_type(काष्ठा irq_data *d, अचिन्हित पूर्णांक flow_type)
अणु
	अचिन्हित पूर्णांक src = virq_to_hw(d->irq);
	अचिन्हित पूर्णांक vecpri, vold, vnew, prio, cpu_dest;
	अचिन्हित दीर्घ flags;

	अगर (flow_type == IRQ_TYPE_NONE)
		flow_type = IRQ_TYPE_LEVEL_LOW;

	irqd_set_trigger_type(d, flow_type);

	vecpri = ehv_pic_type_to_vecpri(flow_type);

	spin_lock_irqsave(&ehv_pic_lock, flags);
	ev_पूर्णांक_get_config(src, &vold, &prio, &cpu_dest);
	vnew = vold & ~(EHV_PIC_INFO(VECPRI_POLARITY_MASK) |
			EHV_PIC_INFO(VECPRI_SENSE_MASK));
	vnew |= vecpri;

	/*
	 * TODO : Add specअगरic पूर्णांकerface call क्रम platक्रमm to set
	 * inभागidual पूर्णांकerrupt priorities.
	 * platक्रमm currently using अटल/शेष priority क्रम all पूर्णांकs
	 */

	prio = 8;

	ev_पूर्णांक_set_config(src, vecpri, prio, cpu_dest);

	spin_unlock_irqrestore(&ehv_pic_lock, flags);
	वापस IRQ_SET_MASK_OK_NOCOPY;
पूर्ण

अटल काष्ठा irq_chip ehv_pic_irq_chip = अणु
	.irq_mask	= ehv_pic_mask_irq,
	.irq_unmask	= ehv_pic_unmask_irq,
	.irq_eoi	= ehv_pic_end_irq,
	.irq_set_type	= ehv_pic_set_irq_type,
पूर्ण;

अटल काष्ठा irq_chip ehv_pic_direct_eoi_irq_chip = अणु
	.irq_mask	= ehv_pic_mask_irq,
	.irq_unmask	= ehv_pic_unmask_irq,
	.irq_eoi	= ehv_pic_direct_end_irq,
	.irq_set_type	= ehv_pic_set_irq_type,
पूर्ण;

/* Return an पूर्णांकerrupt vector or 0 अगर no पूर्णांकerrupt is pending. */
अचिन्हित पूर्णांक ehv_pic_get_irq(व्योम)
अणु
	पूर्णांक irq;

	BUG_ON(global_ehv_pic == शून्य);

	अगर (global_ehv_pic->coreपूर्णांक_flag)
		irq = mfspr(SPRN_EPR); /* अगर core पूर्णांक mode */
	अन्यथा
		ev_पूर्णांक_iack(0, &irq); /* legacy mode */

	अगर (irq == 0xFFFF)    /* 0xFFFF --> no irq is pending */
		वापस 0;

	/*
	 * this will also setup revmap[] in the slow path क्रम the first
	 * समय, next calls will always use fast path by indexing revmap
	 */
	वापस irq_linear_revmap(global_ehv_pic->irqhost, irq);
पूर्ण

अटल पूर्णांक ehv_pic_host_match(काष्ठा irq_करोमुख्य *h, काष्ठा device_node *node,
			      क्रमागत irq_करोमुख्य_bus_token bus_token)
अणु
	/* Exact match, unless ehv_pic node is शून्य */
	काष्ठा device_node *of_node = irq_करोमुख्य_get_of_node(h);
	वापस of_node == शून्य || of_node == node;
पूर्ण

अटल पूर्णांक ehv_pic_host_map(काष्ठा irq_करोमुख्य *h, अचिन्हित पूर्णांक virq,
			 irq_hw_number_t hw)
अणु
	काष्ठा ehv_pic *ehv_pic = h->host_data;
	काष्ठा irq_chip *chip;

	/* Default chip */
	chip = &ehv_pic->hc_irq;

	अगर (mpic_percpu_base_vaddr)
		अगर (hwirq_पूर्णांकspec[hw] & IRQ_TYPE_MPIC_सूचीECT)
			chip = &ehv_pic_direct_eoi_irq_chip;

	irq_set_chip_data(virq, chip);
	/*
	 * using handle_fasteoi_irq as our irq handler, this will
	 * only call the eoi callback and suitable क्रम the MPIC
	 * controller which set ISR/IPR स्वतःmatically and clear the
	 * highest priority active पूर्णांकerrupt in ISR/IPR when we करो
	 * a specअगरic eoi
	 */
	irq_set_chip_and_handler(virq, chip, handle_fasteoi_irq);

	/* Set शेष irq type */
	irq_set_irq_type(virq, IRQ_TYPE_NONE);

	वापस 0;
पूर्ण

अटल पूर्णांक ehv_pic_host_xlate(काष्ठा irq_करोमुख्य *h, काष्ठा device_node *ct,
			   स्थिर u32 *पूर्णांकspec, अचिन्हित पूर्णांक पूर्णांकsize,
			   irq_hw_number_t *out_hwirq, अचिन्हित पूर्णांक *out_flags)

अणु
	/*
	 * पूर्णांकerrupt sense values coming from the guest device tree
	 * पूर्णांकerrupt specअगरiers can have four possible sense and
	 * level encoding inक्रमmation and they need to
	 * be translated between firmware type & linux type.
	 */

	अटल अचिन्हित अक्षर map_of_senses_to_linux_irqtype[4] = अणु
		IRQ_TYPE_EDGE_FALLING,
		IRQ_TYPE_EDGE_RISING,
		IRQ_TYPE_LEVEL_LOW,
		IRQ_TYPE_LEVEL_HIGH,
	पूर्ण;

	*out_hwirq = पूर्णांकspec[0];
	अगर (पूर्णांकsize > 1) अणु
		hwirq_पूर्णांकspec[पूर्णांकspec[0]] = पूर्णांकspec[1];
		*out_flags = map_of_senses_to_linux_irqtype[पूर्णांकspec[1] &
							~IRQ_TYPE_MPIC_सूचीECT];
	पूर्ण अन्यथा अणु
		*out_flags = IRQ_TYPE_NONE;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops ehv_pic_host_ops = अणु
	.match = ehv_pic_host_match,
	.map = ehv_pic_host_map,
	.xlate = ehv_pic_host_xlate,
पूर्ण;

व्योम __init ehv_pic_init(व्योम)
अणु
	काष्ठा device_node *np, *np2;
	काष्ठा ehv_pic *ehv_pic;
	पूर्णांक coreपूर्णांक_flag = 1;

	np = of_find_compatible_node(शून्य, शून्य, "epapr,hv-pic");
	अगर (!np) अणु
		pr_err("ehv_pic_init: could not find epapr,hv-pic node\n");
		वापस;
	पूर्ण

	अगर (!of_find_property(np, "has-external-proxy", शून्य))
		coreपूर्णांक_flag = 0;

	ehv_pic = kzalloc(माप(काष्ठा ehv_pic), GFP_KERNEL);
	अगर (!ehv_pic) अणु
		of_node_put(np);
		वापस;
	पूर्ण

	ehv_pic->irqhost = irq_करोमुख्य_add_linear(np, NR_EHV_PIC_INTS,
						 &ehv_pic_host_ops, ehv_pic);
	अगर (!ehv_pic->irqhost) अणु
		of_node_put(np);
		kमुक्त(ehv_pic);
		वापस;
	पूर्ण

	np2 = of_find_compatible_node(शून्य, शून्य, "fsl,hv-mpic-per-cpu");
	अगर (np2) अणु
		mpic_percpu_base_vaddr = of_iomap(np2, 0);
		अगर (!mpic_percpu_base_vaddr)
			pr_err("ehv_pic_init: of_iomap failed\n");

		of_node_put(np2);
	पूर्ण

	ehv_pic->hc_irq = ehv_pic_irq_chip;
	ehv_pic->hc_irq.irq_set_affinity = ehv_pic_set_affinity;
	ehv_pic->coreपूर्णांक_flag = coreपूर्णांक_flag;

	global_ehv_pic = ehv_pic;
	irq_set_शेष_host(global_ehv_pic->irqhost);
पूर्ण
