<शैली गुरु>
#समावेश <linux/kernel.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/sched.h>
#समावेश <linux/संकेत.स>
#समावेश <linux/irq.h>
#समावेश <linux/dma-mapping.h>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/8xx_immap.h>

#समावेश "pic.h"


#घोषणा PIC_VEC_SPURRIOUS      15

बाह्य पूर्णांक cpm_get_irq(काष्ठा pt_regs *regs);

अटल काष्ठा irq_करोमुख्य *mpc8xx_pic_host;
अटल अचिन्हित दीर्घ mpc8xx_cached_irq_mask;
अटल sysconf8xx_t __iomem *siu_reg;

अटल अंतरभूत अचिन्हित दीर्घ mpc8xx_irqd_to_bit(काष्ठा irq_data *d)
अणु
	वापस 0x80000000 >> irqd_to_hwirq(d);
पूर्ण

अटल व्योम mpc8xx_unmask_irq(काष्ठा irq_data *d)
अणु
	mpc8xx_cached_irq_mask |= mpc8xx_irqd_to_bit(d);
	out_be32(&siu_reg->sc_simask, mpc8xx_cached_irq_mask);
पूर्ण

अटल व्योम mpc8xx_mask_irq(काष्ठा irq_data *d)
अणु
	mpc8xx_cached_irq_mask &= ~mpc8xx_irqd_to_bit(d);
	out_be32(&siu_reg->sc_simask, mpc8xx_cached_irq_mask);
पूर्ण

अटल व्योम mpc8xx_ack(काष्ठा irq_data *d)
अणु
	out_be32(&siu_reg->sc_sipend, mpc8xx_irqd_to_bit(d));
पूर्ण

अटल व्योम mpc8xx_end_irq(काष्ठा irq_data *d)
अणु
	mpc8xx_cached_irq_mask |= mpc8xx_irqd_to_bit(d);
	out_be32(&siu_reg->sc_simask, mpc8xx_cached_irq_mask);
पूर्ण

अटल पूर्णांक mpc8xx_set_irq_type(काष्ठा irq_data *d, अचिन्हित पूर्णांक flow_type)
अणु
	/* only बाह्यal IRQ senses are programmable */
	अगर ((flow_type & IRQ_TYPE_EDGE_FALLING) && !(irqd_to_hwirq(d) & 1)) अणु
		अचिन्हित पूर्णांक siel = in_be32(&siu_reg->sc_siel);
		siel |= mpc8xx_irqd_to_bit(d);
		out_be32(&siu_reg->sc_siel, siel);
		irq_set_handler_locked(d, handle_edge_irq);
	पूर्ण
	वापस 0;
पूर्ण

अटल काष्ठा irq_chip mpc8xx_pic = अणु
	.name = "8XX SIU",
	.irq_unmask = mpc8xx_unmask_irq,
	.irq_mask = mpc8xx_mask_irq,
	.irq_ack = mpc8xx_ack,
	.irq_eoi = mpc8xx_end_irq,
	.irq_set_type = mpc8xx_set_irq_type,
पूर्ण;

अचिन्हित पूर्णांक mpc8xx_get_irq(व्योम)
अणु
	पूर्णांक irq;

	/* For MPC8xx, पढ़ो the SIVEC रेजिस्टर and shअगरt the bits करोwn
	 * to get the irq number.
	 */
	irq = in_be32(&siu_reg->sc_sivec) >> 26;

	अगर (irq == PIC_VEC_SPURRIOUS)
		वापस 0;

        वापस irq_linear_revmap(mpc8xx_pic_host, irq);

पूर्ण

अटल पूर्णांक mpc8xx_pic_host_map(काष्ठा irq_करोमुख्य *h, अचिन्हित पूर्णांक virq,
			  irq_hw_number_t hw)
अणु
	pr_debug("mpc8xx_pic_host_map(%d, 0x%lx)\n", virq, hw);

	/* Set शेष irq handle */
	irq_set_chip_and_handler(virq, &mpc8xx_pic, handle_level_irq);
	वापस 0;
पूर्ण


अटल पूर्णांक mpc8xx_pic_host_xlate(काष्ठा irq_करोमुख्य *h, काष्ठा device_node *ct,
			    स्थिर u32 *पूर्णांकspec, अचिन्हित पूर्णांक पूर्णांकsize,
			    irq_hw_number_t *out_hwirq, अचिन्हित पूर्णांक *out_flags)
अणु
	अटल अचिन्हित अक्षर map_pic_senses[4] = अणु
		IRQ_TYPE_EDGE_RISING,
		IRQ_TYPE_LEVEL_LOW,
		IRQ_TYPE_LEVEL_HIGH,
		IRQ_TYPE_EDGE_FALLING,
	पूर्ण;

	अगर (पूर्णांकspec[0] > 0x1f)
		वापस 0;

	*out_hwirq = पूर्णांकspec[0];
	अगर (पूर्णांकsize > 1 && पूर्णांकspec[1] < 4)
		*out_flags = map_pic_senses[पूर्णांकspec[1]];
	अन्यथा
		*out_flags = IRQ_TYPE_NONE;

	वापस 0;
पूर्ण


अटल स्थिर काष्ठा irq_करोमुख्य_ops mpc8xx_pic_host_ops = अणु
	.map = mpc8xx_pic_host_map,
	.xlate = mpc8xx_pic_host_xlate,
पूर्ण;

पूर्णांक __init mpc8xx_pic_init(व्योम)
अणु
	काष्ठा resource res;
	काष्ठा device_node *np;
	पूर्णांक ret;

	np = of_find_compatible_node(शून्य, शून्य, "fsl,pq1-pic");
	अगर (np == शून्य)
		np = of_find_node_by_type(शून्य, "mpc8xx-pic");
	अगर (np == शून्य) अणु
		prपूर्णांकk(KERN_ERR "Could not find fsl,pq1-pic node\n");
		वापस -ENOMEM;
	पूर्ण

	ret = of_address_to_resource(np, 0, &res);
	अगर (ret)
		जाओ out;

	siu_reg = ioremap(res.start, resource_size(&res));
	अगर (siu_reg == शून्य) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	mpc8xx_pic_host = irq_करोमुख्य_add_linear(np, 64, &mpc8xx_pic_host_ops, शून्य);
	अगर (mpc8xx_pic_host == शून्य) अणु
		prपूर्णांकk(KERN_ERR "MPC8xx PIC: failed to allocate irq host!\n");
		ret = -ENOMEM;
	पूर्ण

	ret = 0;
out:
	of_node_put(np);
	वापस ret;
पूर्ण
