<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (c) 2014-2018 MediaTek Inc.

/*
 * Library क्रम MediaTek External Interrupt Support
 *
 * Author: Maoguang Meng <maoguang.meng@mediatek.com>
 *	   Sean Wang <sean.wang@mediatek.com>
 *
 */

#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/पन.स>
#समावेश <linux/irqchip/chained_irq.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/module.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश "mtk-eint.h"

#घोषणा MTK_EINT_EDGE_SENSITIVE           0
#घोषणा MTK_EINT_LEVEL_SENSITIVE          1
#घोषणा MTK_EINT_DBNC_SET_DBNC_BITS	  4
#घोषणा MTK_EINT_DBNC_RST_BIT		  (0x1 << 1)
#घोषणा MTK_EINT_DBNC_SET_EN		  (0x1 << 0)

अटल स्थिर काष्ठा mtk_eपूर्णांक_regs mtk_generic_eपूर्णांक_regs = अणु
	.stat      = 0x000,
	.ack       = 0x040,
	.mask      = 0x080,
	.mask_set  = 0x0c0,
	.mask_clr  = 0x100,
	.sens      = 0x140,
	.sens_set  = 0x180,
	.sens_clr  = 0x1c0,
	.soft      = 0x200,
	.soft_set  = 0x240,
	.soft_clr  = 0x280,
	.pol       = 0x300,
	.pol_set   = 0x340,
	.pol_clr   = 0x380,
	.करोm_en    = 0x400,
	.dbnc_ctrl = 0x500,
	.dbnc_set  = 0x600,
	.dbnc_clr  = 0x700,
पूर्ण;

अटल व्योम __iomem *mtk_eपूर्णांक_get_offset(काष्ठा mtk_eपूर्णांक *eपूर्णांक,
					 अचिन्हित पूर्णांक eपूर्णांक_num,
					 अचिन्हित पूर्णांक offset)
अणु
	अचिन्हित पूर्णांक eपूर्णांक_base = 0;
	व्योम __iomem *reg;

	अगर (eपूर्णांक_num >= eपूर्णांक->hw->ap_num)
		eपूर्णांक_base = eपूर्णांक->hw->ap_num;

	reg = eपूर्णांक->base + offset + ((eपूर्णांक_num - eपूर्णांक_base) / 32) * 4;

	वापस reg;
पूर्ण

अटल अचिन्हित पूर्णांक mtk_eपूर्णांक_can_en_debounce(काष्ठा mtk_eपूर्णांक *eपूर्णांक,
					     अचिन्हित पूर्णांक eपूर्णांक_num)
अणु
	अचिन्हित पूर्णांक sens;
	अचिन्हित पूर्णांक bit = BIT(eपूर्णांक_num % 32);
	व्योम __iomem *reg = mtk_eपूर्णांक_get_offset(eपूर्णांक, eपूर्णांक_num,
						eपूर्णांक->regs->sens);

	अगर (पढ़ोl(reg) & bit)
		sens = MTK_EINT_LEVEL_SENSITIVE;
	अन्यथा
		sens = MTK_EINT_EDGE_SENSITIVE;

	अगर (eपूर्णांक_num < eपूर्णांक->hw->db_cnt && sens != MTK_EINT_EDGE_SENSITIVE)
		वापस 1;
	अन्यथा
		वापस 0;
पूर्ण

अटल पूर्णांक mtk_eपूर्णांक_flip_edge(काष्ठा mtk_eपूर्णांक *eपूर्णांक, पूर्णांक hwirq)
अणु
	पूर्णांक start_level, curr_level;
	अचिन्हित पूर्णांक reg_offset;
	u32 mask = BIT(hwirq & 0x1f);
	u32 port = (hwirq >> 5) & eपूर्णांक->hw->port_mask;
	व्योम __iomem *reg = eपूर्णांक->base + (port << 2);

	curr_level = eपूर्णांक->gpio_xlate->get_gpio_state(eपूर्णांक->pctl, hwirq);

	करो अणु
		start_level = curr_level;
		अगर (start_level)
			reg_offset = eपूर्णांक->regs->pol_clr;
		अन्यथा
			reg_offset = eपूर्णांक->regs->pol_set;
		ग_लिखोl(mask, reg + reg_offset);

		curr_level = eपूर्णांक->gpio_xlate->get_gpio_state(eपूर्णांक->pctl,
							      hwirq);
	पूर्ण जबतक (start_level != curr_level);

	वापस start_level;
पूर्ण

अटल व्योम mtk_eपूर्णांक_mask(काष्ठा irq_data *d)
अणु
	काष्ठा mtk_eपूर्णांक *eपूर्णांक = irq_data_get_irq_chip_data(d);
	u32 mask = BIT(d->hwirq & 0x1f);
	व्योम __iomem *reg = mtk_eपूर्णांक_get_offset(eपूर्णांक, d->hwirq,
						eपूर्णांक->regs->mask_set);

	eपूर्णांक->cur_mask[d->hwirq >> 5] &= ~mask;

	ग_लिखोl(mask, reg);
पूर्ण

अटल व्योम mtk_eपूर्णांक_unmask(काष्ठा irq_data *d)
अणु
	काष्ठा mtk_eपूर्णांक *eपूर्णांक = irq_data_get_irq_chip_data(d);
	u32 mask = BIT(d->hwirq & 0x1f);
	व्योम __iomem *reg = mtk_eपूर्णांक_get_offset(eपूर्णांक, d->hwirq,
						eपूर्णांक->regs->mask_clr);

	eपूर्णांक->cur_mask[d->hwirq >> 5] |= mask;

	ग_लिखोl(mask, reg);

	अगर (eपूर्णांक->dual_edge[d->hwirq])
		mtk_eपूर्णांक_flip_edge(eपूर्णांक, d->hwirq);
पूर्ण

अटल अचिन्हित पूर्णांक mtk_eपूर्णांक_get_mask(काष्ठा mtk_eपूर्णांक *eपूर्णांक,
				      अचिन्हित पूर्णांक eपूर्णांक_num)
अणु
	अचिन्हित पूर्णांक bit = BIT(eपूर्णांक_num % 32);
	व्योम __iomem *reg = mtk_eपूर्णांक_get_offset(eपूर्णांक, eपूर्णांक_num,
						eपूर्णांक->regs->mask);

	वापस !!(पढ़ोl(reg) & bit);
पूर्ण

अटल व्योम mtk_eपूर्णांक_ack(काष्ठा irq_data *d)
अणु
	काष्ठा mtk_eपूर्णांक *eपूर्णांक = irq_data_get_irq_chip_data(d);
	u32 mask = BIT(d->hwirq & 0x1f);
	व्योम __iomem *reg = mtk_eपूर्णांक_get_offset(eपूर्णांक, d->hwirq,
						eपूर्णांक->regs->ack);

	ग_लिखोl(mask, reg);
पूर्ण

अटल पूर्णांक mtk_eपूर्णांक_set_type(काष्ठा irq_data *d, अचिन्हित पूर्णांक type)
अणु
	काष्ठा mtk_eपूर्णांक *eपूर्णांक = irq_data_get_irq_chip_data(d);
	bool masked;
	u32 mask = BIT(d->hwirq & 0x1f);
	व्योम __iomem *reg;

	अगर (((type & IRQ_TYPE_EDGE_BOTH) && (type & IRQ_TYPE_LEVEL_MASK)) ||
	    ((type & IRQ_TYPE_LEVEL_MASK) == IRQ_TYPE_LEVEL_MASK)) अणु
		dev_err(eपूर्णांक->dev,
			"Can't configure IRQ%d (EINT%lu) for type 0x%X\n",
			d->irq, d->hwirq, type);
		वापस -EINVAL;
	पूर्ण

	अगर ((type & IRQ_TYPE_EDGE_BOTH) == IRQ_TYPE_EDGE_BOTH)
		eपूर्णांक->dual_edge[d->hwirq] = 1;
	अन्यथा
		eपूर्णांक->dual_edge[d->hwirq] = 0;

	अगर (!mtk_eपूर्णांक_get_mask(eपूर्णांक, d->hwirq)) अणु
		mtk_eपूर्णांक_mask(d);
		masked = false;
	पूर्ण अन्यथा अणु
		masked = true;
	पूर्ण

	अगर (type & (IRQ_TYPE_LEVEL_LOW | IRQ_TYPE_EDGE_FALLING)) अणु
		reg = mtk_eपूर्णांक_get_offset(eपूर्णांक, d->hwirq, eपूर्णांक->regs->pol_clr);
		ग_लिखोl(mask, reg);
	पूर्ण अन्यथा अणु
		reg = mtk_eपूर्णांक_get_offset(eपूर्णांक, d->hwirq, eपूर्णांक->regs->pol_set);
		ग_लिखोl(mask, reg);
	पूर्ण

	अगर (type & (IRQ_TYPE_EDGE_RISING | IRQ_TYPE_EDGE_FALLING)) अणु
		reg = mtk_eपूर्णांक_get_offset(eपूर्णांक, d->hwirq, eपूर्णांक->regs->sens_clr);
		ग_लिखोl(mask, reg);
	पूर्ण अन्यथा अणु
		reg = mtk_eपूर्णांक_get_offset(eपूर्णांक, d->hwirq, eपूर्णांक->regs->sens_set);
		ग_लिखोl(mask, reg);
	पूर्ण

	mtk_eपूर्णांक_ack(d);
	अगर (!masked)
		mtk_eपूर्णांक_unmask(d);

	वापस 0;
पूर्ण

अटल पूर्णांक mtk_eपूर्णांक_irq_set_wake(काष्ठा irq_data *d, अचिन्हित पूर्णांक on)
अणु
	काष्ठा mtk_eपूर्णांक *eपूर्णांक = irq_data_get_irq_chip_data(d);
	पूर्णांक shअगरt = d->hwirq & 0x1f;
	पूर्णांक reg = d->hwirq >> 5;

	अगर (on)
		eपूर्णांक->wake_mask[reg] |= BIT(shअगरt);
	अन्यथा
		eपूर्णांक->wake_mask[reg] &= ~BIT(shअगरt);

	वापस 0;
पूर्ण

अटल व्योम mtk_eपूर्णांक_chip_ग_लिखो_mask(स्थिर काष्ठा mtk_eपूर्णांक *eपूर्णांक,
				     व्योम __iomem *base, u32 *buf)
अणु
	पूर्णांक port;
	व्योम __iomem *reg;

	क्रम (port = 0; port < eपूर्णांक->hw->ports; port++) अणु
		reg = base + (port << 2);
		ग_लिखोl_relaxed(~buf[port], reg + eपूर्णांक->regs->mask_set);
		ग_लिखोl_relaxed(buf[port], reg + eपूर्णांक->regs->mask_clr);
	पूर्ण
पूर्ण

अटल पूर्णांक mtk_eपूर्णांक_irq_request_resources(काष्ठा irq_data *d)
अणु
	काष्ठा mtk_eपूर्णांक *eपूर्णांक = irq_data_get_irq_chip_data(d);
	काष्ठा gpio_chip *gpio_c;
	अचिन्हित पूर्णांक gpio_n;
	पूर्णांक err;

	err = eपूर्णांक->gpio_xlate->get_gpio_n(eपूर्णांक->pctl, d->hwirq,
					   &gpio_n, &gpio_c);
	अगर (err < 0) अणु
		dev_err(eपूर्णांक->dev, "Can not find pin\n");
		वापस err;
	पूर्ण

	err = gpiochip_lock_as_irq(gpio_c, gpio_n);
	अगर (err < 0) अणु
		dev_err(eपूर्णांक->dev, "unable to lock HW IRQ %lu for IRQ\n",
			irqd_to_hwirq(d));
		वापस err;
	पूर्ण

	err = eपूर्णांक->gpio_xlate->set_gpio_as_eपूर्णांक(eपूर्णांक->pctl, d->hwirq);
	अगर (err < 0) अणु
		dev_err(eपूर्णांक->dev, "Can not eint mode\n");
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम mtk_eपूर्णांक_irq_release_resources(काष्ठा irq_data *d)
अणु
	काष्ठा mtk_eपूर्णांक *eपूर्णांक = irq_data_get_irq_chip_data(d);
	काष्ठा gpio_chip *gpio_c;
	अचिन्हित पूर्णांक gpio_n;

	eपूर्णांक->gpio_xlate->get_gpio_n(eपूर्णांक->pctl, d->hwirq, &gpio_n,
				     &gpio_c);

	gpiochip_unlock_as_irq(gpio_c, gpio_n);
पूर्ण

अटल काष्ठा irq_chip mtk_eपूर्णांक_irq_chip = अणु
	.name = "mt-eint",
	.irq_disable = mtk_eपूर्णांक_mask,
	.irq_mask = mtk_eपूर्णांक_mask,
	.irq_unmask = mtk_eपूर्णांक_unmask,
	.irq_ack = mtk_eपूर्णांक_ack,
	.irq_set_type = mtk_eपूर्णांक_set_type,
	.irq_set_wake = mtk_eपूर्णांक_irq_set_wake,
	.irq_request_resources = mtk_eपूर्णांक_irq_request_resources,
	.irq_release_resources = mtk_eपूर्णांक_irq_release_resources,
पूर्ण;

अटल अचिन्हित पूर्णांक mtk_eपूर्णांक_hw_init(काष्ठा mtk_eपूर्णांक *eपूर्णांक)
अणु
	व्योम __iomem *reg = eपूर्णांक->base + eपूर्णांक->regs->करोm_en;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < eपूर्णांक->hw->ap_num; i += 32) अणु
		ग_लिखोl(0xffffffff, reg);
		reg += 4;
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम
mtk_eपूर्णांक_debounce_process(काष्ठा mtk_eपूर्णांक *eपूर्णांक, पूर्णांक index)
अणु
	अचिन्हित पूर्णांक rst, ctrl_offset;
	अचिन्हित पूर्णांक bit, dbnc;

	ctrl_offset = (index / 4) * 4 + eपूर्णांक->regs->dbnc_ctrl;
	dbnc = पढ़ोl(eपूर्णांक->base + ctrl_offset);
	bit = MTK_EINT_DBNC_SET_EN << ((index % 4) * 8);
	अगर ((bit & dbnc) > 0) अणु
		ctrl_offset = (index / 4) * 4 + eपूर्णांक->regs->dbnc_set;
		rst = MTK_EINT_DBNC_RST_BIT << ((index % 4) * 8);
		ग_लिखोl(rst, eपूर्णांक->base + ctrl_offset);
	पूर्ण
पूर्ण

अटल व्योम mtk_eपूर्णांक_irq_handler(काष्ठा irq_desc *desc)
अणु
	काष्ठा irq_chip *chip = irq_desc_get_chip(desc);
	काष्ठा mtk_eपूर्णांक *eपूर्णांक = irq_desc_get_handler_data(desc);
	अचिन्हित पूर्णांक status, eपूर्णांक_num;
	पूर्णांक offset, mask_offset, index, virq;
	व्योम __iomem *reg =  mtk_eपूर्णांक_get_offset(eपूर्णांक, 0, eपूर्णांक->regs->stat);
	पूर्णांक dual_edge, start_level, curr_level;

	chained_irq_enter(chip, desc);
	क्रम (eपूर्णांक_num = 0; eपूर्णांक_num < eपूर्णांक->hw->ap_num; eपूर्णांक_num += 32,
	     reg += 4) अणु
		status = पढ़ोl(reg);
		जबतक (status) अणु
			offset = __ffs(status);
			mask_offset = eपूर्णांक_num >> 5;
			index = eपूर्णांक_num + offset;
			virq = irq_find_mapping(eपूर्णांक->करोमुख्य, index);
			status &= ~BIT(offset);

			/*
			 * If we get an पूर्णांकerrupt on pin that was only required
			 * क्रम wake (but no real पूर्णांकerrupt requested), mask the
			 * पूर्णांकerrupt (as would mtk_eपूर्णांक_resume करो anyway later
			 * in the resume sequence).
			 */
			अगर (eपूर्णांक->wake_mask[mask_offset] & BIT(offset) &&
			    !(eपूर्णांक->cur_mask[mask_offset] & BIT(offset))) अणु
				ग_लिखोl_relaxed(BIT(offset), reg -
					eपूर्णांक->regs->stat +
					eपूर्णांक->regs->mask_set);
			पूर्ण

			dual_edge = eपूर्णांक->dual_edge[index];
			अगर (dual_edge) अणु
				/*
				 * Clear soft-irq in हाल we उठाओd it last
				 * समय.
				 */
				ग_लिखोl(BIT(offset), reg - eपूर्णांक->regs->stat +
				       eपूर्णांक->regs->soft_clr);

				start_level =
				eपूर्णांक->gpio_xlate->get_gpio_state(eपूर्णांक->pctl,
								 index);
			पूर्ण

			generic_handle_irq(virq);

			अगर (dual_edge) अणु
				curr_level = mtk_eपूर्णांक_flip_edge(eपूर्णांक, index);

				/*
				 * If level changed, we might lost one edge
				 * पूर्णांकerrupt, उठाओd it through soft-irq.
				 */
				अगर (start_level != curr_level)
					ग_लिखोl(BIT(offset), reg -
					       eपूर्णांक->regs->stat +
					       eपूर्णांक->regs->soft_set);
			पूर्ण

			अगर (index < eपूर्णांक->hw->db_cnt)
				mtk_eपूर्णांक_debounce_process(eपूर्णांक, index);
		पूर्ण
	पूर्ण
	chained_irq_निकास(chip, desc);
पूर्ण

पूर्णांक mtk_eपूर्णांक_करो_suspend(काष्ठा mtk_eपूर्णांक *eपूर्णांक)
अणु
	mtk_eपूर्णांक_chip_ग_लिखो_mask(eपूर्णांक, eपूर्णांक->base, eपूर्णांक->wake_mask);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(mtk_eपूर्णांक_करो_suspend);

पूर्णांक mtk_eपूर्णांक_करो_resume(काष्ठा mtk_eपूर्णांक *eपूर्णांक)
अणु
	mtk_eपूर्णांक_chip_ग_लिखो_mask(eपूर्णांक, eपूर्णांक->base, eपूर्णांक->cur_mask);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(mtk_eपूर्णांक_करो_resume);

पूर्णांक mtk_eपूर्णांक_set_debounce(काष्ठा mtk_eपूर्णांक *eपूर्णांक, अचिन्हित दीर्घ eपूर्णांक_num,
			  अचिन्हित पूर्णांक debounce)
अणु
	पूर्णांक virq, eपूर्णांक_offset;
	अचिन्हित पूर्णांक set_offset, bit, clr_bit, clr_offset, rst, i, unmask,
		     dbnc;
	अटल स्थिर अचिन्हित पूर्णांक debounce_समय[] = अणु500, 1000, 16000, 32000,
						     64000, 128000, 256000पूर्ण;
	काष्ठा irq_data *d;

	virq = irq_find_mapping(eपूर्णांक->करोमुख्य, eपूर्णांक_num);
	eपूर्णांक_offset = (eपूर्णांक_num % 4) * 8;
	d = irq_get_irq_data(virq);

	set_offset = (eपूर्णांक_num / 4) * 4 + eपूर्णांक->regs->dbnc_set;
	clr_offset = (eपूर्णांक_num / 4) * 4 + eपूर्णांक->regs->dbnc_clr;

	अगर (!mtk_eपूर्णांक_can_en_debounce(eपूर्णांक, eपूर्णांक_num))
		वापस -EINVAL;

	dbnc = ARRAY_SIZE(debounce_समय);
	क्रम (i = 0; i < ARRAY_SIZE(debounce_समय); i++) अणु
		अगर (debounce <= debounce_समय[i]) अणु
			dbnc = i;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!mtk_eपूर्णांक_get_mask(eपूर्णांक, eपूर्णांक_num)) अणु
		mtk_eपूर्णांक_mask(d);
		unmask = 1;
	पूर्ण अन्यथा अणु
		unmask = 0;
	पूर्ण

	clr_bit = 0xff << eपूर्णांक_offset;
	ग_लिखोl(clr_bit, eपूर्णांक->base + clr_offset);

	bit = ((dbnc << MTK_EINT_DBNC_SET_DBNC_BITS) | MTK_EINT_DBNC_SET_EN) <<
		eपूर्णांक_offset;
	rst = MTK_EINT_DBNC_RST_BIT << eपूर्णांक_offset;
	ग_लिखोl(rst | bit, eपूर्णांक->base + set_offset);

	/*
	 * Delay a जबतक (more than 2T) to रुको क्रम hw debounce counter reset
	 * work correctly.
	 */
	udelay(1);
	अगर (unmask == 1)
		mtk_eपूर्णांक_unmask(d);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(mtk_eपूर्णांक_set_debounce);

पूर्णांक mtk_eपूर्णांक_find_irq(काष्ठा mtk_eपूर्णांक *eपूर्णांक, अचिन्हित दीर्घ eपूर्णांक_n)
अणु
	पूर्णांक irq;

	irq = irq_find_mapping(eपूर्णांक->करोमुख्य, eपूर्णांक_n);
	अगर (!irq)
		वापस -EINVAL;

	वापस irq;
पूर्ण
EXPORT_SYMBOL_GPL(mtk_eपूर्णांक_find_irq);

पूर्णांक mtk_eपूर्णांक_करो_init(काष्ठा mtk_eपूर्णांक *eपूर्णांक)
अणु
	पूर्णांक i;

	/* If clients करोn't assign a specific regs, let's use generic one */
	अगर (!eपूर्णांक->regs)
		eपूर्णांक->regs = &mtk_generic_eपूर्णांक_regs;

	eपूर्णांक->wake_mask = devm_kसुस्मृति(eपूर्णांक->dev, eपूर्णांक->hw->ports,
				       माप(*eपूर्णांक->wake_mask), GFP_KERNEL);
	अगर (!eपूर्णांक->wake_mask)
		वापस -ENOMEM;

	eपूर्णांक->cur_mask = devm_kसुस्मृति(eपूर्णांक->dev, eपूर्णांक->hw->ports,
				      माप(*eपूर्णांक->cur_mask), GFP_KERNEL);
	अगर (!eपूर्णांक->cur_mask)
		वापस -ENOMEM;

	eपूर्णांक->dual_edge = devm_kसुस्मृति(eपूर्णांक->dev, eपूर्णांक->hw->ap_num,
				       माप(पूर्णांक), GFP_KERNEL);
	अगर (!eपूर्णांक->dual_edge)
		वापस -ENOMEM;

	eपूर्णांक->करोमुख्य = irq_करोमुख्य_add_linear(eपूर्णांक->dev->of_node,
					     eपूर्णांक->hw->ap_num,
					     &irq_करोमुख्य_simple_ops, शून्य);
	अगर (!eपूर्णांक->करोमुख्य)
		वापस -ENOMEM;

	mtk_eपूर्णांक_hw_init(eपूर्णांक);
	क्रम (i = 0; i < eपूर्णांक->hw->ap_num; i++) अणु
		पूर्णांक virq = irq_create_mapping(eपूर्णांक->करोमुख्य, i);

		irq_set_chip_and_handler(virq, &mtk_eपूर्णांक_irq_chip,
					 handle_level_irq);
		irq_set_chip_data(virq, eपूर्णांक);
	पूर्ण

	irq_set_chained_handler_and_data(eपूर्णांक->irq, mtk_eपूर्णांक_irq_handler,
					 eपूर्णांक);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(mtk_eपूर्णांक_करो_init);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("MediaTek EINT Driver");
