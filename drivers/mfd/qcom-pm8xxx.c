<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2011, Code Aurora Forum. All rights reserved.
 */

#घोषणा pr_fmt(fmt) "%s: " fmt, __func__

#समावेश <linux/kernel.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irqchip/chained_irq.h>
#समावेश <linux/irq.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/err.h>
#समावेश <linux/ssbi.h>
#समावेश <linux/regmap.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/mfd/core.h>

#घोषणा	SSBI_REG_ADDR_IRQ_BASE		0x1BB

#घोषणा	SSBI_REG_ADDR_IRQ_ROOT		(SSBI_REG_ADDR_IRQ_BASE + 0)
#घोषणा	SSBI_REG_ADDR_IRQ_M_STATUS1	(SSBI_REG_ADDR_IRQ_BASE + 1)
#घोषणा	SSBI_REG_ADDR_IRQ_M_STATUS2	(SSBI_REG_ADDR_IRQ_BASE + 2)
#घोषणा	SSBI_REG_ADDR_IRQ_M_STATUS3	(SSBI_REG_ADDR_IRQ_BASE + 3)
#घोषणा	SSBI_REG_ADDR_IRQ_M_STATUS4	(SSBI_REG_ADDR_IRQ_BASE + 4)
#घोषणा	SSBI_REG_ADDR_IRQ_BLK_SEL	(SSBI_REG_ADDR_IRQ_BASE + 5)
#घोषणा	SSBI_REG_ADDR_IRQ_IT_STATUS	(SSBI_REG_ADDR_IRQ_BASE + 6)
#घोषणा	SSBI_REG_ADDR_IRQ_CONFIG	(SSBI_REG_ADDR_IRQ_BASE + 7)
#घोषणा	SSBI_REG_ADDR_IRQ_RT_STATUS	(SSBI_REG_ADDR_IRQ_BASE + 8)

#घोषणा	PM8821_SSBI_REG_ADDR_IRQ_BASE	0x100
#घोषणा	PM8821_SSBI_REG_ADDR_IRQ_MASTER0 (PM8821_SSBI_REG_ADDR_IRQ_BASE + 0x30)
#घोषणा	PM8821_SSBI_REG_ADDR_IRQ_MASTER1 (PM8821_SSBI_REG_ADDR_IRQ_BASE + 0xb0)
#घोषणा	PM8821_SSBI_REG(m, b, offset) \
			((m == 0) ? \
			(PM8821_SSBI_REG_ADDR_IRQ_MASTER0 + b + offset) : \
			(PM8821_SSBI_REG_ADDR_IRQ_MASTER1 + b + offset))
#घोषणा	PM8821_SSBI_ADDR_IRQ_ROOT(m, b)		PM8821_SSBI_REG(m, b, 0x0)
#घोषणा	PM8821_SSBI_ADDR_IRQ_CLEAR(m, b)	PM8821_SSBI_REG(m, b, 0x01)
#घोषणा	PM8821_SSBI_ADDR_IRQ_MASK(m, b)		PM8821_SSBI_REG(m, b, 0x08)
#घोषणा	PM8821_SSBI_ADDR_IRQ_RT_STATUS(m, b)	PM8821_SSBI_REG(m, b, 0x0f)

#घोषणा	PM8821_BLOCKS_PER_MASTER	7

#घोषणा	PM_IRQF_LVL_SEL			0x01	/* level select */
#घोषणा	PM_IRQF_MASK_FE			0x02	/* mask falling edge */
#घोषणा	PM_IRQF_MASK_RE			0x04	/* mask rising edge */
#घोषणा	PM_IRQF_CLR			0x08	/* clear पूर्णांकerrupt */
#घोषणा	PM_IRQF_BITS_MASK		0x70
#घोषणा	PM_IRQF_BITS_SHIFT		4
#घोषणा	PM_IRQF_WRITE			0x80

#घोषणा	PM_IRQF_MASK_ALL		(PM_IRQF_MASK_FE | \
					PM_IRQF_MASK_RE)

#घोषणा REG_HWREV		0x002  /* PMIC4 revision */
#घोषणा REG_HWREV_2		0x0E8  /* PMIC4 revision 2 */

#घोषणा PM8XXX_NR_IRQS		256
#घोषणा PM8821_NR_IRQS		112

काष्ठा pm_irq_data अणु
	पूर्णांक num_irqs;
	काष्ठा irq_chip *irq_chip;
	व्योम (*irq_handler)(काष्ठा irq_desc *desc);
पूर्ण;

काष्ठा pm_irq_chip अणु
	काष्ठा regmap		*regmap;
	spinlock_t		pm_irq_lock;
	काष्ठा irq_करोमुख्य	*irqकरोमुख्य;
	अचिन्हित पूर्णांक		num_blocks;
	अचिन्हित पूर्णांक		num_masters;
	स्थिर काष्ठा pm_irq_data *pm_irq_data;
	/* MUST BE AT THE END OF THIS STRUCT */
	u8			config[];
पूर्ण;

अटल पूर्णांक pm8xxx_पढ़ो_block_irq(काष्ठा pm_irq_chip *chip, अचिन्हित पूर्णांक bp,
				 अचिन्हित पूर्णांक *ip)
अणु
	पूर्णांक	rc;

	spin_lock(&chip->pm_irq_lock);
	rc = regmap_ग_लिखो(chip->regmap, SSBI_REG_ADDR_IRQ_BLK_SEL, bp);
	अगर (rc) अणु
		pr_err("Failed Selecting Block %d rc=%d\n", bp, rc);
		जाओ bail;
	पूर्ण

	rc = regmap_पढ़ो(chip->regmap, SSBI_REG_ADDR_IRQ_IT_STATUS, ip);
	अगर (rc)
		pr_err("Failed Reading Status rc=%d\n", rc);
bail:
	spin_unlock(&chip->pm_irq_lock);
	वापस rc;
पूर्ण

अटल पूर्णांक
pm8xxx_config_irq(काष्ठा pm_irq_chip *chip, अचिन्हित पूर्णांक bp, अचिन्हित पूर्णांक cp)
अणु
	पूर्णांक	rc;

	spin_lock(&chip->pm_irq_lock);
	rc = regmap_ग_लिखो(chip->regmap, SSBI_REG_ADDR_IRQ_BLK_SEL, bp);
	अगर (rc) अणु
		pr_err("Failed Selecting Block %d rc=%d\n", bp, rc);
		जाओ bail;
	पूर्ण

	cp |= PM_IRQF_WRITE;
	rc = regmap_ग_लिखो(chip->regmap, SSBI_REG_ADDR_IRQ_CONFIG, cp);
	अगर (rc)
		pr_err("Failed Configuring IRQ rc=%d\n", rc);
bail:
	spin_unlock(&chip->pm_irq_lock);
	वापस rc;
पूर्ण

अटल पूर्णांक pm8xxx_irq_block_handler(काष्ठा pm_irq_chip *chip, पूर्णांक block)
अणु
	पूर्णांक pmirq, irq, i, ret = 0;
	अचिन्हित पूर्णांक bits;

	ret = pm8xxx_पढ़ो_block_irq(chip, block, &bits);
	अगर (ret) अणु
		pr_err("Failed reading %d block ret=%d", block, ret);
		वापस ret;
	पूर्ण
	अगर (!bits) अणु
		pr_err("block bit set in master but no irqs: %d", block);
		वापस 0;
	पूर्ण

	/* Check IRQ bits */
	क्रम (i = 0; i < 8; i++) अणु
		अगर (bits & (1 << i)) अणु
			pmirq = block * 8 + i;
			irq = irq_find_mapping(chip->irqकरोमुख्य, pmirq);
			generic_handle_irq(irq);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक pm8xxx_irq_master_handler(काष्ठा pm_irq_chip *chip, पूर्णांक master)
अणु
	अचिन्हित पूर्णांक blockbits;
	पूर्णांक block_number, i, ret = 0;

	ret = regmap_पढ़ो(chip->regmap, SSBI_REG_ADDR_IRQ_M_STATUS1 + master,
			  &blockbits);
	अगर (ret) अणु
		pr_err("Failed to read master %d ret=%d\n", master, ret);
		वापस ret;
	पूर्ण
	अगर (!blockbits) अणु
		pr_err("master bit set in root but no blocks: %d", master);
		वापस 0;
	पूर्ण

	क्रम (i = 0; i < 8; i++)
		अगर (blockbits & (1 << i)) अणु
			block_number = master * 8 + i;	/* block # */
			ret |= pm8xxx_irq_block_handler(chip, block_number);
		पूर्ण
	वापस ret;
पूर्ण

अटल व्योम pm8xxx_irq_handler(काष्ठा irq_desc *desc)
अणु
	काष्ठा pm_irq_chip *chip = irq_desc_get_handler_data(desc);
	काष्ठा irq_chip *irq_chip = irq_desc_get_chip(desc);
	अचिन्हित पूर्णांक root;
	पूर्णांक	i, ret, masters = 0;

	chained_irq_enter(irq_chip, desc);

	ret = regmap_पढ़ो(chip->regmap, SSBI_REG_ADDR_IRQ_ROOT, &root);
	अगर (ret) अणु
		pr_err("Can't read root status ret=%d\n", ret);
		वापस;
	पूर्ण

	/* on pm8xxx series masters start from bit 1 of the root */
	masters = root >> 1;

	/* Read allowed masters क्रम blocks. */
	क्रम (i = 0; i < chip->num_masters; i++)
		अगर (masters & (1 << i))
			pm8xxx_irq_master_handler(chip, i);

	chained_irq_निकास(irq_chip, desc);
पूर्ण

अटल व्योम pm8821_irq_block_handler(काष्ठा pm_irq_chip *chip,
				     पूर्णांक master, पूर्णांक block)
अणु
	पूर्णांक pmirq, irq, i, ret;
	अचिन्हित पूर्णांक bits;

	ret = regmap_पढ़ो(chip->regmap,
			  PM8821_SSBI_ADDR_IRQ_ROOT(master, block), &bits);
	अगर (ret) अणु
		pr_err("Reading block %d failed ret=%d", block, ret);
		वापस;
	पूर्ण

	/* Convert block offset to global block number */
	block += (master * PM8821_BLOCKS_PER_MASTER) - 1;

	/* Check IRQ bits */
	क्रम (i = 0; i < 8; i++) अणु
		अगर (bits & BIT(i)) अणु
			pmirq = block * 8 + i;
			irq = irq_find_mapping(chip->irqकरोमुख्य, pmirq);
			generic_handle_irq(irq);
		पूर्ण
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम pm8821_irq_master_handler(काष्ठा pm_irq_chip *chip,
					     पूर्णांक master, u8 master_val)
अणु
	पूर्णांक block;

	क्रम (block = 1; block < 8; block++)
		अगर (master_val & BIT(block))
			pm8821_irq_block_handler(chip, master, block);
पूर्ण

अटल व्योम pm8821_irq_handler(काष्ठा irq_desc *desc)
अणु
	काष्ठा pm_irq_chip *chip = irq_desc_get_handler_data(desc);
	काष्ठा irq_chip *irq_chip = irq_desc_get_chip(desc);
	अचिन्हित पूर्णांक master;
	पूर्णांक ret;

	chained_irq_enter(irq_chip, desc);
	ret = regmap_पढ़ो(chip->regmap,
			  PM8821_SSBI_REG_ADDR_IRQ_MASTER0, &master);
	अगर (ret) अणु
		pr_err("Failed to read master 0 ret=%d\n", ret);
		जाओ करोne;
	पूर्ण

	/* bits 1 through 7 marks the first 7 blocks in master 0 */
	अगर (master & GENMASK(7, 1))
		pm8821_irq_master_handler(chip, 0, master);

	/* bit 0 marks अगर master 1 contains any bits */
	अगर (!(master & BIT(0)))
		जाओ करोne;

	ret = regmap_पढ़ो(chip->regmap,
			  PM8821_SSBI_REG_ADDR_IRQ_MASTER1, &master);
	अगर (ret) अणु
		pr_err("Failed to read master 1 ret=%d\n", ret);
		जाओ करोne;
	पूर्ण

	pm8821_irq_master_handler(chip, 1, master);

करोne:
	chained_irq_निकास(irq_chip, desc);
पूर्ण

अटल व्योम pm8xxx_irq_mask_ack(काष्ठा irq_data *d)
अणु
	काष्ठा pm_irq_chip *chip = irq_data_get_irq_chip_data(d);
	अचिन्हित पूर्णांक pmirq = irqd_to_hwirq(d);
	u8	block, config;

	block = pmirq / 8;

	config = chip->config[pmirq] | PM_IRQF_MASK_ALL | PM_IRQF_CLR;
	pm8xxx_config_irq(chip, block, config);
पूर्ण

अटल व्योम pm8xxx_irq_unmask(काष्ठा irq_data *d)
अणु
	काष्ठा pm_irq_chip *chip = irq_data_get_irq_chip_data(d);
	अचिन्हित पूर्णांक pmirq = irqd_to_hwirq(d);
	u8	block, config;

	block = pmirq / 8;

	config = chip->config[pmirq];
	pm8xxx_config_irq(chip, block, config);
पूर्ण

अटल पूर्णांक pm8xxx_irq_set_type(काष्ठा irq_data *d, अचिन्हित पूर्णांक flow_type)
अणु
	काष्ठा pm_irq_chip *chip = irq_data_get_irq_chip_data(d);
	अचिन्हित पूर्णांक pmirq = irqd_to_hwirq(d);
	पूर्णांक irq_bit;
	u8 block, config;

	block = pmirq / 8;
	irq_bit  = pmirq % 8;

	chip->config[pmirq] = (irq_bit << PM_IRQF_BITS_SHIFT)
							| PM_IRQF_MASK_ALL;
	अगर (flow_type & (IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING)) अणु
		अगर (flow_type & IRQF_TRIGGER_RISING)
			chip->config[pmirq] &= ~PM_IRQF_MASK_RE;
		अगर (flow_type & IRQF_TRIGGER_FALLING)
			chip->config[pmirq] &= ~PM_IRQF_MASK_FE;
	पूर्ण अन्यथा अणु
		chip->config[pmirq] |= PM_IRQF_LVL_SEL;

		अगर (flow_type & IRQF_TRIGGER_HIGH)
			chip->config[pmirq] &= ~PM_IRQF_MASK_RE;
		अन्यथा
			chip->config[pmirq] &= ~PM_IRQF_MASK_FE;
	पूर्ण

	config = chip->config[pmirq] | PM_IRQF_CLR;
	वापस pm8xxx_config_irq(chip, block, config);
पूर्ण

अटल पूर्णांक pm8xxx_irq_get_irqchip_state(काष्ठा irq_data *d,
					क्रमागत irqchip_irq_state which,
					bool *state)
अणु
	काष्ठा pm_irq_chip *chip = irq_data_get_irq_chip_data(d);
	अचिन्हित पूर्णांक pmirq = irqd_to_hwirq(d);
	अचिन्हित पूर्णांक bits;
	पूर्णांक irq_bit;
	u8 block;
	पूर्णांक rc;

	अगर (which != IRQCHIP_STATE_LINE_LEVEL)
		वापस -EINVAL;

	block = pmirq / 8;
	irq_bit = pmirq % 8;

	spin_lock(&chip->pm_irq_lock);
	rc = regmap_ग_लिखो(chip->regmap, SSBI_REG_ADDR_IRQ_BLK_SEL, block);
	अगर (rc) अणु
		pr_err("Failed Selecting Block %d rc=%d\n", block, rc);
		जाओ bail;
	पूर्ण

	rc = regmap_पढ़ो(chip->regmap, SSBI_REG_ADDR_IRQ_RT_STATUS, &bits);
	अगर (rc) अणु
		pr_err("Failed Reading Status rc=%d\n", rc);
		जाओ bail;
	पूर्ण

	*state = !!(bits & BIT(irq_bit));
bail:
	spin_unlock(&chip->pm_irq_lock);

	वापस rc;
पूर्ण

अटल काष्ठा irq_chip pm8xxx_irq_chip = अणु
	.name		= "pm8xxx",
	.irq_mask_ack	= pm8xxx_irq_mask_ack,
	.irq_unmask	= pm8xxx_irq_unmask,
	.irq_set_type	= pm8xxx_irq_set_type,
	.irq_get_irqchip_state = pm8xxx_irq_get_irqchip_state,
	.flags		= IRQCHIP_MASK_ON_SUSPEND | IRQCHIP_SKIP_SET_WAKE,
पूर्ण;

अटल व्योम pm8xxx_irq_करोमुख्य_map(काष्ठा pm_irq_chip *chip,
				  काष्ठा irq_करोमुख्य *करोमुख्य, अचिन्हित पूर्णांक irq,
				  irq_hw_number_t hwirq, अचिन्हित पूर्णांक type)
अणु
	irq_करोमुख्य_set_info(करोमुख्य, irq, hwirq, chip->pm_irq_data->irq_chip,
			    chip, handle_level_irq, शून्य, शून्य);
	irq_set_noprobe(irq);
पूर्ण

अटल पूर्णांक pm8xxx_irq_करोमुख्य_alloc(काष्ठा irq_करोमुख्य *करोमुख्य, अचिन्हित पूर्णांक virq,
				   अचिन्हित पूर्णांक nr_irqs, व्योम *data)
अणु
	काष्ठा pm_irq_chip *chip = करोमुख्य->host_data;
	काष्ठा irq_fwspec *fwspec = data;
	irq_hw_number_t hwirq;
	अचिन्हित पूर्णांक type;
	पूर्णांक ret, i;

	ret = irq_करोमुख्य_translate_twocell(करोमुख्य, fwspec, &hwirq, &type);
	अगर (ret)
		वापस ret;

	क्रम (i = 0; i < nr_irqs; i++)
		pm8xxx_irq_करोमुख्य_map(chip, करोमुख्य, virq + i, hwirq + i, type);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops pm8xxx_irq_करोमुख्य_ops = अणु
	.alloc = pm8xxx_irq_करोमुख्य_alloc,
	.मुक्त = irq_करोमुख्य_मुक्त_irqs_common,
	.translate = irq_करोमुख्य_translate_twocell,
पूर्ण;

अटल व्योम pm8821_irq_mask_ack(काष्ठा irq_data *d)
अणु
	काष्ठा pm_irq_chip *chip = irq_data_get_irq_chip_data(d);
	अचिन्हित पूर्णांक pmirq = irqd_to_hwirq(d);
	u8 block, master;
	पूर्णांक irq_bit, rc;

	block = pmirq / 8;
	master = block / PM8821_BLOCKS_PER_MASTER;
	irq_bit = pmirq % 8;
	block %= PM8821_BLOCKS_PER_MASTER;

	rc = regmap_update_bits(chip->regmap,
				PM8821_SSBI_ADDR_IRQ_MASK(master, block),
				BIT(irq_bit), BIT(irq_bit));
	अगर (rc) अणु
		pr_err("Failed to mask IRQ:%d rc=%d\n", pmirq, rc);
		वापस;
	पूर्ण

	rc = regmap_update_bits(chip->regmap,
				PM8821_SSBI_ADDR_IRQ_CLEAR(master, block),
				BIT(irq_bit), BIT(irq_bit));
	अगर (rc)
		pr_err("Failed to CLEAR IRQ:%d rc=%d\n", pmirq, rc);
पूर्ण

अटल व्योम pm8821_irq_unmask(काष्ठा irq_data *d)
अणु
	काष्ठा pm_irq_chip *chip = irq_data_get_irq_chip_data(d);
	अचिन्हित पूर्णांक pmirq = irqd_to_hwirq(d);
	पूर्णांक irq_bit, rc;
	u8 block, master;

	block = pmirq / 8;
	master = block / PM8821_BLOCKS_PER_MASTER;
	irq_bit = pmirq % 8;
	block %= PM8821_BLOCKS_PER_MASTER;

	rc = regmap_update_bits(chip->regmap,
				PM8821_SSBI_ADDR_IRQ_MASK(master, block),
				BIT(irq_bit), ~BIT(irq_bit));
	अगर (rc)
		pr_err("Failed to read/write unmask IRQ:%d rc=%d\n", pmirq, rc);

पूर्ण

अटल पूर्णांक pm8821_irq_get_irqchip_state(काष्ठा irq_data *d,
					क्रमागत irqchip_irq_state which,
					bool *state)
अणु
	काष्ठा pm_irq_chip *chip = irq_data_get_irq_chip_data(d);
	पूर्णांक rc, pmirq = irqd_to_hwirq(d);
	u8 block, irq_bit, master;
	अचिन्हित पूर्णांक bits;

	block = pmirq / 8;
	master = block / PM8821_BLOCKS_PER_MASTER;
	irq_bit = pmirq % 8;
	block %= PM8821_BLOCKS_PER_MASTER;

	rc = regmap_पढ़ो(chip->regmap,
		PM8821_SSBI_ADDR_IRQ_RT_STATUS(master, block), &bits);
	अगर (rc) अणु
		pr_err("Reading Status of IRQ %d failed rc=%d\n", pmirq, rc);
		वापस rc;
	पूर्ण

	*state = !!(bits & BIT(irq_bit));

	वापस rc;
पूर्ण

अटल काष्ठा irq_chip pm8821_irq_chip = अणु
	.name		= "pm8821",
	.irq_mask_ack	= pm8821_irq_mask_ack,
	.irq_unmask	= pm8821_irq_unmask,
	.irq_get_irqchip_state = pm8821_irq_get_irqchip_state,
	.flags		= IRQCHIP_MASK_ON_SUSPEND | IRQCHIP_SKIP_SET_WAKE,
पूर्ण;

अटल स्थिर काष्ठा regmap_config ssbi_regmap_config = अणु
	.reg_bits = 16,
	.val_bits = 8,
	.max_रेजिस्टर = 0x3ff,
	.fast_io = true,
	.reg_पढ़ो = ssbi_reg_पढ़ो,
	.reg_ग_लिखो = ssbi_reg_ग_लिखो
पूर्ण;

अटल स्थिर काष्ठा pm_irq_data pm8xxx_data = अणु
	.num_irqs = PM8XXX_NR_IRQS,
	.irq_chip = &pm8xxx_irq_chip,
	.irq_handler = pm8xxx_irq_handler,
पूर्ण;

अटल स्थिर काष्ठा pm_irq_data pm8821_data = अणु
	.num_irqs = PM8821_NR_IRQS,
	.irq_chip = &pm8821_irq_chip,
	.irq_handler = pm8821_irq_handler,
पूर्ण;

अटल स्थिर काष्ठा of_device_id pm8xxx_id_table[] = अणु
	अणु .compatible = "qcom,pm8018", .data = &pm8xxx_dataपूर्ण,
	अणु .compatible = "qcom,pm8058", .data = &pm8xxx_dataपूर्ण,
	अणु .compatible = "qcom,pm8821", .data = &pm8821_dataपूर्ण,
	अणु .compatible = "qcom,pm8921", .data = &pm8xxx_dataपूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, pm8xxx_id_table);

अटल पूर्णांक pm8xxx_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा pm_irq_data *data;
	काष्ठा regmap *regmap;
	पूर्णांक irq, rc;
	अचिन्हित पूर्णांक val;
	u32 rev;
	काष्ठा pm_irq_chip *chip;

	data = of_device_get_match_data(&pdev->dev);
	अगर (!data) अणु
		dev_err(&pdev->dev, "No matching driver data found\n");
		वापस -EINVAL;
	पूर्ण

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;

	regmap = devm_regmap_init(&pdev->dev, शून्य, pdev->dev.parent,
				  &ssbi_regmap_config);
	अगर (IS_ERR(regmap))
		वापस PTR_ERR(regmap);

	/* Read PMIC chip revision */
	rc = regmap_पढ़ो(regmap, REG_HWREV, &val);
	अगर (rc) अणु
		pr_err("Failed to read hw rev reg %d:rc=%d\n", REG_HWREV, rc);
		वापस rc;
	पूर्ण
	pr_info("PMIC revision 1: %02X\n", val);
	rev = val;

	/* Read PMIC chip revision 2 */
	rc = regmap_पढ़ो(regmap, REG_HWREV_2, &val);
	अगर (rc) अणु
		pr_err("Failed to read hw rev 2 reg %d:rc=%d\n",
			REG_HWREV_2, rc);
		वापस rc;
	पूर्ण
	pr_info("PMIC revision 2: %02X\n", val);
	rev |= val << BITS_PER_BYTE;

	chip = devm_kzalloc(&pdev->dev,
			    काष्ठा_size(chip, config, data->num_irqs),
			    GFP_KERNEL);
	अगर (!chip)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, chip);
	chip->regmap = regmap;
	chip->num_blocks = DIV_ROUND_UP(data->num_irqs, 8);
	chip->num_masters = DIV_ROUND_UP(chip->num_blocks, 8);
	chip->pm_irq_data = data;
	spin_lock_init(&chip->pm_irq_lock);

	chip->irqकरोमुख्य = irq_करोमुख्य_add_linear(pdev->dev.of_node,
						data->num_irqs,
						&pm8xxx_irq_करोमुख्य_ops,
						chip);
	अगर (!chip->irqकरोमुख्य)
		वापस -ENODEV;

	irq_set_chained_handler_and_data(irq, data->irq_handler, chip);
	irq_set_irq_wake(irq, 1);

	rc = of_platक्रमm_populate(pdev->dev.of_node, शून्य, शून्य, &pdev->dev);
	अगर (rc) अणु
		irq_set_chained_handler_and_data(irq, शून्य, शून्य);
		irq_करोमुख्य_हटाओ(chip->irqकरोमुख्य);
	पूर्ण

	वापस rc;
पूर्ण

अटल पूर्णांक pm8xxx_हटाओ_child(काष्ठा device *dev, व्योम *unused)
अणु
	platक्रमm_device_unरेजिस्टर(to_platक्रमm_device(dev));
	वापस 0;
पूर्ण

अटल पूर्णांक pm8xxx_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक irq = platक्रमm_get_irq(pdev, 0);
	काष्ठा pm_irq_chip *chip = platक्रमm_get_drvdata(pdev);

	device_क्रम_each_child(&pdev->dev, शून्य, pm8xxx_हटाओ_child);
	irq_set_chained_handler_and_data(irq, शून्य, शून्य);
	irq_करोमुख्य_हटाओ(chip->irqकरोमुख्य);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver pm8xxx_driver = अणु
	.probe		= pm8xxx_probe,
	.हटाओ		= pm8xxx_हटाओ,
	.driver		= अणु
		.name	= "pm8xxx-core",
		.of_match_table = pm8xxx_id_table,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init pm8xxx_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&pm8xxx_driver);
पूर्ण
subsys_initcall(pm8xxx_init);

अटल व्योम __निकास pm8xxx_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&pm8xxx_driver);
पूर्ण
module_निकास(pm8xxx_निकास);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("PMIC 8xxx core driver");
MODULE_VERSION("1.0");
MODULE_ALIAS("platform:pm8xxx-core");
