<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * External Interrupt Controller on Spider South Bridge
 *
 * (C) Copyright IBM Deutschland Entwicklung GmbH 2005
 *
 * Author: Arnd Bergmann <arndb@de.ibm.com>
 */

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/ioport.h>
#समावेश <linux/pgtable.h>

#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/पन.स>

#समावेश "interrupt.h"

/* रेजिस्टर layout taken from Spider spec, table 7.4-4 */
क्रमागत अणु
	TIR_DEN		= 0x004, /* Detection Enable Register */
	TIR_MSK		= 0x084, /* Mask Level Register */
	TIR_EDC		= 0x0c0, /* Edge Detection Clear Register */
	TIR_PNDA	= 0x100, /* Pending Register A */
	TIR_PNDB	= 0x104, /* Pending Register B */
	TIR_CS		= 0x144, /* Current Status Register */
	TIR_LCSA	= 0x150, /* Level Current Status Register A */
	TIR_LCSB	= 0x154, /* Level Current Status Register B */
	TIR_LCSC	= 0x158, /* Level Current Status Register C */
	TIR_LCSD	= 0x15c, /* Level Current Status Register D */
	TIR_CFGA	= 0x200, /* Setting Register A0 */
	TIR_CFGB	= 0x204, /* Setting Register B0 */
			/* 0x208 ... 0x3ff Setting Register An/Bn */
	TIR_PPNDA	= 0x400, /* Packet Pending Register A */
	TIR_PPNDB	= 0x404, /* Packet Pending Register B */
	TIR_PIERA	= 0x408, /* Packet Output Error Register A */
	TIR_PIERB	= 0x40c, /* Packet Output Error Register B */
	TIR_PIEN	= 0x444, /* Packet Output Enable Register */
	TIR_PIPND	= 0x454, /* Packet Output Pending Register */
	TIRDID		= 0x484, /* Spider Device ID Register */
	REISTIM		= 0x500, /* Reissue Command Timeout Time Setting */
	REISTIMEN	= 0x504, /* Reissue Command Timeout Setting */
	REISWAITEN	= 0x508, /* Reissue Wait Control*/
पूर्ण;

#घोषणा SPIDER_CHIP_COUNT	4
#घोषणा SPIDER_SRC_COUNT	64
#घोषणा SPIDER_IRQ_INVALID	63

काष्ठा spider_pic अणु
	काष्ठा irq_करोमुख्य		*host;
	व्योम __iomem		*regs;
	अचिन्हित पूर्णांक		node_id;
पूर्ण;
अटल काष्ठा spider_pic spider_pics[SPIDER_CHIP_COUNT];

अटल काष्ठा spider_pic *spider_irq_data_to_pic(काष्ठा irq_data *d)
अणु
	वापस irq_data_get_irq_chip_data(d);
पूर्ण

अटल व्योम __iomem *spider_get_irq_config(काष्ठा spider_pic *pic,
					   अचिन्हित पूर्णांक src)
अणु
	वापस pic->regs + TIR_CFGA + 8 * src;
पूर्ण

अटल व्योम spider_unmask_irq(काष्ठा irq_data *d)
अणु
	काष्ठा spider_pic *pic = spider_irq_data_to_pic(d);
	व्योम __iomem *cfg = spider_get_irq_config(pic, irqd_to_hwirq(d));

	out_be32(cfg, in_be32(cfg) | 0x30000000u);
पूर्ण

अटल व्योम spider_mask_irq(काष्ठा irq_data *d)
अणु
	काष्ठा spider_pic *pic = spider_irq_data_to_pic(d);
	व्योम __iomem *cfg = spider_get_irq_config(pic, irqd_to_hwirq(d));

	out_be32(cfg, in_be32(cfg) & ~0x30000000u);
पूर्ण

अटल व्योम spider_ack_irq(काष्ठा irq_data *d)
अणु
	काष्ठा spider_pic *pic = spider_irq_data_to_pic(d);
	अचिन्हित पूर्णांक src = irqd_to_hwirq(d);

	/* Reset edge detection logic अगर necessary
	 */
	अगर (irqd_is_level_type(d))
		वापस;

	/* Only पूर्णांकerrupts 47 to 50 can be set to edge */
	अगर (src < 47 || src > 50)
		वापस;

	/* Perक्रमm the clear of the edge logic */
	out_be32(pic->regs + TIR_EDC, 0x100 | (src & 0xf));
पूर्ण

अटल पूर्णांक spider_set_irq_type(काष्ठा irq_data *d, अचिन्हित पूर्णांक type)
अणु
	अचिन्हित पूर्णांक sense = type & IRQ_TYPE_SENSE_MASK;
	काष्ठा spider_pic *pic = spider_irq_data_to_pic(d);
	अचिन्हित पूर्णांक hw = irqd_to_hwirq(d);
	व्योम __iomem *cfg = spider_get_irq_config(pic, hw);
	u32 old_mask;
	u32 ic;

	/* Note that only level high is supported क्रम most पूर्णांकerrupts */
	अगर (sense != IRQ_TYPE_NONE && sense != IRQ_TYPE_LEVEL_HIGH &&
	    (hw < 47 || hw > 50))
		वापस -EINVAL;

	/* Decode sense type */
	चयन(sense) अणु
	हाल IRQ_TYPE_EDGE_RISING:
		ic = 0x3;
		अवरोध;
	हाल IRQ_TYPE_EDGE_FALLING:
		ic = 0x2;
		अवरोध;
	हाल IRQ_TYPE_LEVEL_LOW:
		ic = 0x0;
		अवरोध;
	हाल IRQ_TYPE_LEVEL_HIGH:
	हाल IRQ_TYPE_NONE:
		ic = 0x1;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* Configure the source. One gross hack that was there beक्रमe and
	 * that I've kept around is the priority to the BE which I set to
	 * be the same as the पूर्णांकerrupt source number. I करोn't know whether
	 * that's supposed to make any kind of sense however, we'll have to
	 * decide that, but क्रम now, I'm not changing the behaviour.
	 */
	old_mask = in_be32(cfg) & 0x30000000u;
	out_be32(cfg, old_mask | (ic << 24) | (0x7 << 16) |
		 (pic->node_id << 4) | 0xe);
	out_be32(cfg + 4, (0x2 << 16) | (hw & 0xff));

	वापस 0;
पूर्ण

अटल काष्ठा irq_chip spider_pic = अणु
	.name = "SPIDER",
	.irq_unmask = spider_unmask_irq,
	.irq_mask = spider_mask_irq,
	.irq_ack = spider_ack_irq,
	.irq_set_type = spider_set_irq_type,
पूर्ण;

अटल पूर्णांक spider_host_map(काष्ठा irq_करोमुख्य *h, अचिन्हित पूर्णांक virq,
			irq_hw_number_t hw)
अणु
	irq_set_chip_data(virq, h->host_data);
	irq_set_chip_and_handler(virq, &spider_pic, handle_level_irq);

	/* Set शेष irq type */
	irq_set_irq_type(virq, IRQ_TYPE_NONE);

	वापस 0;
पूर्ण

अटल पूर्णांक spider_host_xlate(काष्ठा irq_करोमुख्य *h, काष्ठा device_node *ct,
			   स्थिर u32 *पूर्णांकspec, अचिन्हित पूर्णांक पूर्णांकsize,
			   irq_hw_number_t *out_hwirq, अचिन्हित पूर्णांक *out_flags)

अणु
	/* Spider पूर्णांकerrupts have 2 cells, first is the पूर्णांकerrupt source,
	 * second, well, I करोn't know क्रम sure yet ... We mask the top bits
	 * because old device-trees encode a node number in there
	 */
	*out_hwirq = पूर्णांकspec[0] & 0x3f;
	*out_flags = IRQ_TYPE_LEVEL_HIGH;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops spider_host_ops = अणु
	.map = spider_host_map,
	.xlate = spider_host_xlate,
पूर्ण;

अटल व्योम spider_irq_cascade(काष्ठा irq_desc *desc)
अणु
	काष्ठा irq_chip *chip = irq_desc_get_chip(desc);
	काष्ठा spider_pic *pic = irq_desc_get_handler_data(desc);
	अचिन्हित पूर्णांक cs, virq;

	cs = in_be32(pic->regs + TIR_CS) >> 24;
	अगर (cs == SPIDER_IRQ_INVALID)
		virq = 0;
	अन्यथा
		virq = irq_linear_revmap(pic->host, cs);

	अगर (virq)
		generic_handle_irq(virq);

	chip->irq_eoi(&desc->irq_data);
पूर्ण

/* For hooking up the cascade we have a problem. Our device-tree is
 * crap and we करोn't know on which BE iic पूर्णांकerrupt we are hooked on at
 * least not the "standard" way. We can reस्थिरitute it based on two
 * inक्रमmations though: which BE node we are connected to and whether
 * we are connected to IOIF0 or IOIF1. Right now, we really only care
 * about the IBM cell blade and we know that its firmware gives us an
 * पूर्णांकerrupt-map property which is pretty strange.
 */
अटल अचिन्हित पूर्णांक __init spider_find_cascade_and_node(काष्ठा spider_pic *pic)
अणु
	अचिन्हित पूर्णांक virq;
	स्थिर u32 *imap, *पंचांगp;
	पूर्णांक imaplen, पूर्णांकsize, unit;
	काष्ठा device_node *iic;
	काष्ठा device_node *of_node;

	of_node = irq_करोमुख्य_get_of_node(pic->host);

	/* First, we check whether we have a real "interrupts" in the device
	 * tree in हाल the device-tree is ever fixed
	 */
	virq = irq_of_parse_and_map(of_node, 0);
	अगर (virq)
		वापस virq;

	/* Now करो the horrible hacks */
	पंचांगp = of_get_property(of_node, "#interrupt-cells", शून्य);
	अगर (पंचांगp == शून्य)
		वापस 0;
	पूर्णांकsize = *पंचांगp;
	imap = of_get_property(of_node, "interrupt-map", &imaplen);
	अगर (imap == शून्य || imaplen < (पूर्णांकsize + 1))
		वापस 0;
	iic = of_find_node_by_phandle(imap[पूर्णांकsize]);
	अगर (iic == शून्य)
		वापस 0;
	imap += पूर्णांकsize + 1;
	पंचांगp = of_get_property(iic, "#interrupt-cells", शून्य);
	अगर (पंचांगp == शून्य) अणु
		of_node_put(iic);
		वापस 0;
	पूर्ण
	पूर्णांकsize = *पंचांगp;
	/* Assume unit is last entry of पूर्णांकerrupt specअगरier */
	unit = imap[पूर्णांकsize - 1];
	/* Ok, we have a unit, now let's try to get the node */
	पंचांगp = of_get_property(iic, "ibm,interrupt-server-ranges", शून्य);
	अगर (पंचांगp == शून्य) अणु
		of_node_put(iic);
		वापस 0;
	पूर्ण
	/* ugly as hell but works क्रम now */
	pic->node_id = (*पंचांगp) >> 1;
	of_node_put(iic);

	/* Ok, now let's get cracking. You may ask me why I just didn't match
	 * the iic host from the iic OF node, but that way I'm still compatible
	 * with really really old old firmwares क्रम which we करोn't have a node
	 */
	/* Manufacture an IIC पूर्णांकerrupt number of class 2 */
	virq = irq_create_mapping(शून्य,
				  (pic->node_id << IIC_IRQ_NODE_SHIFT) |
				  (2 << IIC_IRQ_CLASS_SHIFT) |
				  unit);
	अगर (!virq)
		prपूर्णांकk(KERN_ERR "spider_pic: failed to map cascade !");
	वापस virq;
पूर्ण


अटल व्योम __init spider_init_one(काष्ठा device_node *of_node, पूर्णांक chip,
				   अचिन्हित दीर्घ addr)
अणु
	काष्ठा spider_pic *pic = &spider_pics[chip];
	पूर्णांक i, virq;

	/* Map रेजिस्टरs */
	pic->regs = ioremap(addr, 0x1000);
	अगर (pic->regs == शून्य)
		panic("spider_pic: can't map registers !");

	/* Allocate a host */
	pic->host = irq_करोमुख्य_add_linear(of_node, SPIDER_SRC_COUNT,
					  &spider_host_ops, pic);
	अगर (pic->host == शून्य)
		panic("spider_pic: can't allocate irq host !");

	/* Go through all sources and disable them */
	क्रम (i = 0; i < SPIDER_SRC_COUNT; i++) अणु
		व्योम __iomem *cfg = pic->regs + TIR_CFGA + 8 * i;
		out_be32(cfg, in_be32(cfg) & ~0x30000000u);
	पूर्ण

	/* करो not mask any पूर्णांकerrupts because of level */
	out_be32(pic->regs + TIR_MSK, 0x0);

	/* enable पूर्णांकerrupt packets to be output */
	out_be32(pic->regs + TIR_PIEN, in_be32(pic->regs + TIR_PIEN) | 0x1);

	/* Hook up the cascade पूर्णांकerrupt to the iic and nodeid */
	virq = spider_find_cascade_and_node(pic);
	अगर (!virq)
		वापस;
	irq_set_handler_data(virq, pic);
	irq_set_chained_handler(virq, spider_irq_cascade);

	prपूर्णांकk(KERN_INFO "spider_pic: node %d, addr: 0x%lx %pOF\n",
	       pic->node_id, addr, of_node);

	/* Enable the पूर्णांकerrupt detection enable bit. Do this last! */
	out_be32(pic->regs + TIR_DEN, in_be32(pic->regs + TIR_DEN) | 0x1);
पूर्ण

व्योम __init spider_init_IRQ(व्योम)
अणु
	काष्ठा resource r;
	काष्ठा device_node *dn;
	पूर्णांक chip = 0;

	/* XXX node numbers are totally bogus. We _hope_ we get the device
	 * nodes in the right order here but that's definitely not guaranteed,
	 * we need to get the node from the device tree instead.
	 * There is currently no proper property क्रम it (but our whole
	 * device-tree is bogus anyway) so all we can करो is pray or maybe test
	 * the address and deduce the node-id
	 */
	क्रम_each_node_by_name(dn, "interrupt-controller") अणु
		अगर (of_device_is_compatible(dn, "CBEA,platform-spider-pic")) अणु
			अगर (of_address_to_resource(dn, 0, &r)) अणु
				prपूर्णांकk(KERN_WARNING "spider-pic: Failed\n");
				जारी;
			पूर्ण
		पूर्ण अन्यथा अगर (of_device_is_compatible(dn, "sti,platform-spider-pic")
			   && (chip < 2)) अणु
			अटल दीर्घ hard_coded_pics[] =
				अणु 0x24000008000ul, 0x34000008000ulपूर्ण;
			r.start = hard_coded_pics[chip];
		पूर्ण अन्यथा
			जारी;
		spider_init_one(dn, chip++, r.start);
	पूर्ण
पूर्ण
