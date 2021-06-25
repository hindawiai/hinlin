<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright 2011-2012, Meaकरोr Inge, Mentor Graphics Corporation.
 *
 * Some ideas based on un-pushed work करोne by Vivek Mahajan, Jason Jin, and
 * Mingkai Hu from Freescale Semiconductor, Inc.
 */

#समावेश <linux/list.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/err.h>
#समावेश <linux/export.h>
#समावेश <linux/slab.h>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/hw_irq.h>
#समावेश <यंत्र/ppc-pci.h>
#समावेश <यंत्र/mpic_msgr.h>

#घोषणा MPIC_MSGR_REGISTERS_PER_BLOCK	4
#घोषणा MPIC_MSGR_STRIDE		0x10
#घोषणा MPIC_MSGR_MER_OFFSET		0x100
#घोषणा MSGR_INUSE			0
#घोषणा MSGR_FREE			1

अटल काष्ठा mpic_msgr **mpic_msgrs;
अटल अचिन्हित पूर्णांक mpic_msgr_count;
अटल DEFINE_RAW_SPINLOCK(msgrs_lock);

अटल अंतरभूत व्योम _mpic_msgr_mer_ग_लिखो(काष्ठा mpic_msgr *msgr, u32 value)
अणु
	out_be32(msgr->mer, value);
पूर्ण

अटल अंतरभूत u32 _mpic_msgr_mer_पढ़ो(काष्ठा mpic_msgr *msgr)
अणु
	वापस in_be32(msgr->mer);
पूर्ण

अटल अंतरभूत व्योम _mpic_msgr_disable(काष्ठा mpic_msgr *msgr)
अणु
	u32 mer = _mpic_msgr_mer_पढ़ो(msgr);

	_mpic_msgr_mer_ग_लिखो(msgr, mer & ~(1 << msgr->num));
पूर्ण

काष्ठा mpic_msgr *mpic_msgr_get(अचिन्हित पूर्णांक reg_num)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा mpic_msgr *msgr;

	/* Assume busy until proven otherwise.  */
	msgr = ERR_PTR(-EBUSY);

	अगर (reg_num >= mpic_msgr_count)
		वापस ERR_PTR(-ENODEV);

	raw_spin_lock_irqsave(&msgrs_lock, flags);
	msgr = mpic_msgrs[reg_num];
	अगर (msgr->in_use == MSGR_FREE)
		msgr->in_use = MSGR_INUSE;
	raw_spin_unlock_irqrestore(&msgrs_lock, flags);

	वापस msgr;
पूर्ण
EXPORT_SYMBOL_GPL(mpic_msgr_get);

व्योम mpic_msgr_put(काष्ठा mpic_msgr *msgr)
अणु
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&msgr->lock, flags);
	msgr->in_use = MSGR_FREE;
	_mpic_msgr_disable(msgr);
	raw_spin_unlock_irqrestore(&msgr->lock, flags);
पूर्ण
EXPORT_SYMBOL_GPL(mpic_msgr_put);

व्योम mpic_msgr_enable(काष्ठा mpic_msgr *msgr)
अणु
	अचिन्हित दीर्घ flags;
	u32 mer;

	raw_spin_lock_irqsave(&msgr->lock, flags);
	mer = _mpic_msgr_mer_पढ़ो(msgr);
	_mpic_msgr_mer_ग_लिखो(msgr, mer | (1 << msgr->num));
	raw_spin_unlock_irqrestore(&msgr->lock, flags);
पूर्ण
EXPORT_SYMBOL_GPL(mpic_msgr_enable);

व्योम mpic_msgr_disable(काष्ठा mpic_msgr *msgr)
अणु
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&msgr->lock, flags);
	_mpic_msgr_disable(msgr);
	raw_spin_unlock_irqrestore(&msgr->lock, flags);
पूर्ण
EXPORT_SYMBOL_GPL(mpic_msgr_disable);

/* The following three functions are used to compute the order and number of
 * the message रेजिस्टर blocks.  They are clearly very inefficent.  However,
 * they are called *only* a few बार during device initialization.
 */
अटल अचिन्हित पूर्णांक mpic_msgr_number_of_blocks(व्योम)
अणु
	अचिन्हित पूर्णांक count;
	काष्ठा device_node *aliases;

	count = 0;
	aliases = of_find_node_by_name(शून्य, "aliases");

	अगर (aliases) अणु
		अक्षर buf[32];

		क्रम (;;) अणु
			snम_लिखो(buf, माप(buf), "mpic-msgr-block%d", count);
			अगर (!of_find_property(aliases, buf, शून्य))
				अवरोध;

			count += 1;
		पूर्ण
	पूर्ण

	वापस count;
पूर्ण

अटल अचिन्हित पूर्णांक mpic_msgr_number_of_रेजिस्टरs(व्योम)
अणु
	वापस mpic_msgr_number_of_blocks() * MPIC_MSGR_REGISTERS_PER_BLOCK;
पूर्ण

अटल पूर्णांक mpic_msgr_block_number(काष्ठा device_node *node)
अणु
	काष्ठा device_node *aliases;
	अचिन्हित पूर्णांक index, number_of_blocks;
	अक्षर buf[64];

	number_of_blocks = mpic_msgr_number_of_blocks();
	aliases = of_find_node_by_name(शून्य, "aliases");
	अगर (!aliases)
		वापस -1;

	क्रम (index = 0; index < number_of_blocks; ++index) अणु
		काष्ठा property *prop;

		snम_लिखो(buf, माप(buf), "mpic-msgr-block%d", index);
		prop = of_find_property(aliases, buf, शून्य);
		अगर (node == of_find_node_by_path(prop->value))
			अवरोध;
	पूर्ण

	वापस index == number_of_blocks ? -1 : index;
पूर्ण

/* The probe function क्रम a single message रेजिस्टर block.
 */
अटल पूर्णांक mpic_msgr_probe(काष्ठा platक्रमm_device *dev)
अणु
	व्योम __iomem *msgr_block_addr;
	पूर्णांक block_number;
	काष्ठा resource rsrc;
	अचिन्हित पूर्णांक i;
	अचिन्हित पूर्णांक irq_index;
	काष्ठा device_node *np = dev->dev.of_node;
	अचिन्हित पूर्णांक receive_mask;
	स्थिर अचिन्हित पूर्णांक *prop;

	अगर (!np) अणु
		dev_err(&dev->dev, "Device OF-Node is NULL");
		वापस -EFAULT;
	पूर्ण

	/* Allocate the message रेजिस्टर array upon the first device
	 * रेजिस्टरed.
	 */
	अगर (!mpic_msgrs) अणु
		mpic_msgr_count = mpic_msgr_number_of_रेजिस्टरs();
		dev_info(&dev->dev, "Found %d message registers\n",
				mpic_msgr_count);

		mpic_msgrs = kसुस्मृति(mpic_msgr_count, माप(*mpic_msgrs),
							 GFP_KERNEL);
		अगर (!mpic_msgrs) अणु
			dev_err(&dev->dev,
				"No memory for message register blocks\n");
			वापस -ENOMEM;
		पूर्ण
	पूर्ण
	dev_info(&dev->dev, "Of-device full name %pOF\n", np);

	/* IO map the message रेजिस्टर block. */
	of_address_to_resource(np, 0, &rsrc);
	msgr_block_addr = devm_ioremap(&dev->dev, rsrc.start, resource_size(&rsrc));
	अगर (!msgr_block_addr) अणु
		dev_err(&dev->dev, "Failed to iomap MPIC message registers");
		वापस -EFAULT;
	पूर्ण

	/* Ensure the block has a defined order. */
	block_number = mpic_msgr_block_number(np);
	अगर (block_number < 0) अणु
		dev_err(&dev->dev,
			"Failed to find message register block alias\n");
		वापस -ENODEV;
	पूर्ण
	dev_info(&dev->dev, "Setting up message register block %d\n",
			block_number);

	/* Grab the receive mask which specअगरies what रेजिस्टरs can receive
	 * पूर्णांकerrupts.
	 */
	prop = of_get_property(np, "mpic-msgr-receive-mask", शून्य);
	receive_mask = (prop) ? *prop : 0xF;

	/* Build up the appropriate message रेजिस्टर data काष्ठाures. */
	क्रम (i = 0, irq_index = 0; i < MPIC_MSGR_REGISTERS_PER_BLOCK; ++i) अणु
		काष्ठा mpic_msgr *msgr;
		अचिन्हित पूर्णांक reg_number;

		msgr = kzalloc(माप(काष्ठा mpic_msgr), GFP_KERNEL);
		अगर (!msgr) अणु
			dev_err(&dev->dev, "No memory for message register\n");
			वापस -ENOMEM;
		पूर्ण

		reg_number = block_number * MPIC_MSGR_REGISTERS_PER_BLOCK + i;
		msgr->base = msgr_block_addr + i * MPIC_MSGR_STRIDE;
		msgr->mer = (u32 *)((u8 *)msgr->base + MPIC_MSGR_MER_OFFSET);
		msgr->in_use = MSGR_FREE;
		msgr->num = i;
		raw_spin_lock_init(&msgr->lock);

		अगर (receive_mask & (1 << i)) अणु
			msgr->irq = irq_of_parse_and_map(np, irq_index);
			अगर (!msgr->irq) अणु
				dev_err(&dev->dev,
						"Missing interrupt specifier");
				kमुक्त(msgr);
				वापस -EFAULT;
			पूर्ण
			irq_index += 1;
		पूर्ण अन्यथा अणु
			msgr->irq = 0;
		पूर्ण

		mpic_msgrs[reg_number] = msgr;
		mpic_msgr_disable(msgr);
		dev_info(&dev->dev, "Register %d initialized: irq %d\n",
				reg_number, msgr->irq);

	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id mpic_msgr_ids[] = अणु
	अणु
		.compatible = "fsl,mpic-v3.1-msgr",
		.data = शून्य,
	पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_driver mpic_msgr_driver = अणु
	.driver = अणु
		.name = "mpic-msgr",
		.of_match_table = mpic_msgr_ids,
	पूर्ण,
	.probe = mpic_msgr_probe,
पूर्ण;

अटल __init पूर्णांक mpic_msgr_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&mpic_msgr_driver);
पूर्ण
subsys_initcall(mpic_msgr_init);
