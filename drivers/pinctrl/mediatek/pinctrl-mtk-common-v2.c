<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2018 MediaTek Inc.
 *
 * Author: Sean Wang <sean.wang@mediatek.com>
 *
 */

#समावेश <dt-bindings/pinctrl/mt65xx.h>
#समावेश <linux/device.h>
#समावेश <linux/err.h>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/of_irq.h>

#समावेश "mtk-eint.h"
#समावेश "pinctrl-mtk-common-v2.h"

/**
 * काष्ठा mtk_drive_desc - the काष्ठाure that holds the inक्रमmation
 *			    of the driving current
 * @min:	the minimum current of this group
 * @max:	the maximum current of this group
 * @step:	the step current of this group
 * @scal:	the weight factor
 *
 * क्रमmula: output = ((input) / step - 1) * scal
 */
काष्ठा mtk_drive_desc अणु
	u8 min;
	u8 max;
	u8 step;
	u8 scal;
पूर्ण;

/* The groups of drive strength */
अटल स्थिर काष्ठा mtk_drive_desc mtk_drive[] = अणु
	[DRV_GRP0] = अणु 4, 16, 4, 1 पूर्ण,
	[DRV_GRP1] = अणु 4, 16, 4, 2 पूर्ण,
	[DRV_GRP2] = अणु 2, 8, 2, 1 पूर्ण,
	[DRV_GRP3] = अणु 2, 8, 2, 2 पूर्ण,
	[DRV_GRP4] = अणु 2, 16, 2, 1 पूर्ण,
पूर्ण;

अटल व्योम mtk_w32(काष्ठा mtk_pinctrl *pctl, u8 i, u32 reg, u32 val)
अणु
	ग_लिखोl_relaxed(val, pctl->base[i] + reg);
पूर्ण

अटल u32 mtk_r32(काष्ठा mtk_pinctrl *pctl, u8 i, u32 reg)
अणु
	वापस पढ़ोl_relaxed(pctl->base[i] + reg);
पूर्ण

व्योम mtk_rmw(काष्ठा mtk_pinctrl *pctl, u8 i, u32 reg, u32 mask, u32 set)
अणु
	u32 val;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&pctl->lock, flags);

	val = mtk_r32(pctl, i, reg);
	val &= ~mask;
	val |= set;
	mtk_w32(pctl, i, reg, val);

	spin_unlock_irqrestore(&pctl->lock, flags);
पूर्ण

अटल पूर्णांक mtk_hw_pin_field_lookup(काष्ठा mtk_pinctrl *hw,
				   स्थिर काष्ठा mtk_pin_desc *desc,
				   पूर्णांक field, काष्ठा mtk_pin_field *pfd)
अणु
	स्थिर काष्ठा mtk_pin_field_calc *c;
	स्थिर काष्ठा mtk_pin_reg_calc *rc;
	पूर्णांक start = 0, end, check;
	bool found = false;
	u32 bits;

	अगर (hw->soc->reg_cal && hw->soc->reg_cal[field].range) अणु
		rc = &hw->soc->reg_cal[field];
	पूर्ण अन्यथा अणु
		dev_dbg(hw->dev,
			"Not support field %d for this soc\n", field);
		वापस -ENOTSUPP;
	पूर्ण

	end = rc->nranges - 1;

	जबतक (start <= end) अणु
		check = (start + end) >> 1;
		अगर (desc->number >= rc->range[check].s_pin
		 && desc->number <= rc->range[check].e_pin) अणु
			found = true;
			अवरोध;
		पूर्ण अन्यथा अगर (start == end)
			अवरोध;
		अन्यथा अगर (desc->number < rc->range[check].s_pin)
			end = check - 1;
		अन्यथा
			start = check + 1;
	पूर्ण

	अगर (!found) अणु
		dev_dbg(hw->dev, "Not support field %d for pin = %d (%s)\n",
			field, desc->number, desc->name);
		वापस -ENOTSUPP;
	पूर्ण

	c = rc->range + check;

	अगर (c->i_base > hw->nbase - 1) अणु
		dev_err(hw->dev,
			"Invalid base for field %d for pin = %d (%s)\n",
			field, desc->number, desc->name);
		वापस -EINVAL;
	पूर्ण

	/* Calculated bits as the overall offset the pin is located at,
	 * अगर c->fixed is held, that determines the all the pins in the
	 * range use the same field with the s_pin.
	 */
	bits = c->fixed ? c->s_bit : c->s_bit +
	       (desc->number - c->s_pin) * (c->x_bits);

	/* Fill pfd from bits. For example 32-bit रेजिस्टर applied is assumed
	 * when c->sz_reg is equal to 32.
	 */
	pfd->index = c->i_base;
	pfd->offset = c->s_addr + c->x_addrs * (bits / c->sz_reg);
	pfd->bitpos = bits % c->sz_reg;
	pfd->mask = (1 << c->x_bits) - 1;

	/* pfd->next is used क्रम indicating that bit wrapping-around happens
	 * which requires the manipulation क्रम bit 0 starting in the next
	 * रेजिस्टर to क्रमm the complete field पढ़ो/ग_लिखो.
	 */
	pfd->next = pfd->bitpos + c->x_bits > c->sz_reg ? c->x_addrs : 0;

	वापस 0;
पूर्ण

अटल पूर्णांक mtk_hw_pin_field_get(काष्ठा mtk_pinctrl *hw,
				स्थिर काष्ठा mtk_pin_desc *desc,
				पूर्णांक field, काष्ठा mtk_pin_field *pfd)
अणु
	अगर (field < 0 || field >= PINCTRL_PIN_REG_MAX) अणु
		dev_err(hw->dev, "Invalid Field %d\n", field);
		वापस -EINVAL;
	पूर्ण

	वापस mtk_hw_pin_field_lookup(hw, desc, field, pfd);
पूर्ण

अटल व्योम mtk_hw_bits_part(काष्ठा mtk_pin_field *pf, पूर्णांक *h, पूर्णांक *l)
अणु
	*l = 32 - pf->bitpos;
	*h = get_count_order(pf->mask) - *l;
पूर्ण

अटल व्योम mtk_hw_ग_लिखो_cross_field(काष्ठा mtk_pinctrl *hw,
				     काष्ठा mtk_pin_field *pf, पूर्णांक value)
अणु
	पूर्णांक nbits_l, nbits_h;

	mtk_hw_bits_part(pf, &nbits_h, &nbits_l);

	mtk_rmw(hw, pf->index, pf->offset, pf->mask << pf->bitpos,
		(value & pf->mask) << pf->bitpos);

	mtk_rmw(hw, pf->index, pf->offset + pf->next, BIT(nbits_h) - 1,
		(value & pf->mask) >> nbits_l);
पूर्ण

अटल व्योम mtk_hw_पढ़ो_cross_field(काष्ठा mtk_pinctrl *hw,
				    काष्ठा mtk_pin_field *pf, पूर्णांक *value)
अणु
	पूर्णांक nbits_l, nbits_h, h, l;

	mtk_hw_bits_part(pf, &nbits_h, &nbits_l);

	l  = (mtk_r32(hw, pf->index, pf->offset)
	      >> pf->bitpos) & (BIT(nbits_l) - 1);
	h  = (mtk_r32(hw, pf->index, pf->offset + pf->next))
	      & (BIT(nbits_h) - 1);

	*value = (h << nbits_l) | l;
पूर्ण

पूर्णांक mtk_hw_set_value(काष्ठा mtk_pinctrl *hw, स्थिर काष्ठा mtk_pin_desc *desc,
		     पूर्णांक field, पूर्णांक value)
अणु
	काष्ठा mtk_pin_field pf;
	पूर्णांक err;

	err = mtk_hw_pin_field_get(hw, desc, field, &pf);
	अगर (err)
		वापस err;

	अगर (value < 0 || value > pf.mask)
		वापस -EINVAL;

	अगर (!pf.next)
		mtk_rmw(hw, pf.index, pf.offset, pf.mask << pf.bitpos,
			(value & pf.mask) << pf.bitpos);
	अन्यथा
		mtk_hw_ग_लिखो_cross_field(hw, &pf, value);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(mtk_hw_set_value);

पूर्णांक mtk_hw_get_value(काष्ठा mtk_pinctrl *hw, स्थिर काष्ठा mtk_pin_desc *desc,
		     पूर्णांक field, पूर्णांक *value)
अणु
	काष्ठा mtk_pin_field pf;
	पूर्णांक err;

	err = mtk_hw_pin_field_get(hw, desc, field, &pf);
	अगर (err)
		वापस err;

	अगर (!pf.next)
		*value = (mtk_r32(hw, pf.index, pf.offset)
			  >> pf.bitpos) & pf.mask;
	अन्यथा
		mtk_hw_पढ़ो_cross_field(hw, &pf, value);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(mtk_hw_get_value);

अटल पूर्णांक mtk_xt_find_eपूर्णांक_num(काष्ठा mtk_pinctrl *hw, अचिन्हित दीर्घ eपूर्णांक_n)
अणु
	स्थिर काष्ठा mtk_pin_desc *desc;
	पूर्णांक i = 0;

	desc = (स्थिर काष्ठा mtk_pin_desc *)hw->soc->pins;

	जबतक (i < hw->soc->npins) अणु
		अगर (desc[i].eपूर्णांक.eपूर्णांक_n == eपूर्णांक_n)
			वापस desc[i].number;
		i++;
	पूर्ण

	वापस EINT_NA;
पूर्ण

/*
 * Virtual GPIO only used inside SOC and not being exported to outside SOC.
 * Some modules use भव GPIO as eपूर्णांक (e.g. pmअगर or usb).
 * In MTK platक्रमm, बाह्यal पूर्णांकerrupt (EINT) and GPIO is 1-1 mapping
 * and we can set GPIO as eपूर्णांक.
 * But some modules use specअगरic eपूर्णांक which करोesn't have real GPIO pin.
 * So we use भव GPIO to map it.
 */

bool mtk_is_virt_gpio(काष्ठा mtk_pinctrl *hw, अचिन्हित पूर्णांक gpio_n)
अणु
	स्थिर काष्ठा mtk_pin_desc *desc;
	bool virt_gpio = false;

	desc = (स्थिर काष्ठा mtk_pin_desc *)&hw->soc->pins[gpio_n];

	/* अगर the GPIO is not supported क्रम eपूर्णांक mode */
	अगर (desc->eपूर्णांक.eपूर्णांक_m == NO_EINT_SUPPORT)
		वापस virt_gpio;

	अगर (desc->funcs && !desc->funcs[desc->eपूर्णांक.eपूर्णांक_m].name)
		virt_gpio = true;

	वापस virt_gpio;
पूर्ण
EXPORT_SYMBOL_GPL(mtk_is_virt_gpio);

अटल पूर्णांक mtk_xt_get_gpio_n(व्योम *data, अचिन्हित दीर्घ eपूर्णांक_n,
			     अचिन्हित पूर्णांक *gpio_n,
			     काष्ठा gpio_chip **gpio_chip)
अणु
	काष्ठा mtk_pinctrl *hw = (काष्ठा mtk_pinctrl *)data;
	स्थिर काष्ठा mtk_pin_desc *desc;

	desc = (स्थिर काष्ठा mtk_pin_desc *)hw->soc->pins;
	*gpio_chip = &hw->chip;

	/* Be greedy to guess first gpio_n is equal to eपूर्णांक_n */
	अगर (desc[eपूर्णांक_n].eपूर्णांक.eपूर्णांक_n == eपूर्णांक_n)
		*gpio_n = eपूर्णांक_n;
	अन्यथा
		*gpio_n = mtk_xt_find_eपूर्णांक_num(hw, eपूर्णांक_n);

	वापस *gpio_n == EINT_NA ? -EINVAL : 0;
पूर्ण

अटल पूर्णांक mtk_xt_get_gpio_state(व्योम *data, अचिन्हित दीर्घ eपूर्णांक_n)
अणु
	काष्ठा mtk_pinctrl *hw = (काष्ठा mtk_pinctrl *)data;
	स्थिर काष्ठा mtk_pin_desc *desc;
	काष्ठा gpio_chip *gpio_chip;
	अचिन्हित पूर्णांक gpio_n;
	पूर्णांक value, err;

	err = mtk_xt_get_gpio_n(hw, eपूर्णांक_n, &gpio_n, &gpio_chip);
	अगर (err)
		वापस err;

	desc = (स्थिर काष्ठा mtk_pin_desc *)&hw->soc->pins[gpio_n];

	err = mtk_hw_get_value(hw, desc, PINCTRL_PIN_REG_DI, &value);
	अगर (err)
		वापस err;

	वापस !!value;
पूर्ण

अटल पूर्णांक mtk_xt_set_gpio_as_eपूर्णांक(व्योम *data, अचिन्हित दीर्घ eपूर्णांक_n)
अणु
	काष्ठा mtk_pinctrl *hw = (काष्ठा mtk_pinctrl *)data;
	स्थिर काष्ठा mtk_pin_desc *desc;
	काष्ठा gpio_chip *gpio_chip;
	अचिन्हित पूर्णांक gpio_n;
	पूर्णांक err;

	err = mtk_xt_get_gpio_n(hw, eपूर्णांक_n, &gpio_n, &gpio_chip);
	अगर (err)
		वापस err;

	अगर (mtk_is_virt_gpio(hw, gpio_n))
		वापस 0;

	desc = (स्थिर काष्ठा mtk_pin_desc *)&hw->soc->pins[gpio_n];

	err = mtk_hw_set_value(hw, desc, PINCTRL_PIN_REG_MODE,
			       desc->eपूर्णांक.eपूर्णांक_m);
	अगर (err)
		वापस err;

	err = mtk_hw_set_value(hw, desc, PINCTRL_PIN_REG_सूची, MTK_INPUT);
	अगर (err)
		वापस err;

	err = mtk_hw_set_value(hw, desc, PINCTRL_PIN_REG_SMT, MTK_ENABLE);
	/* SMT is supposed to be supported by every real GPIO and करोesn't
	 * support भव GPIOs, so the extra condition err != -ENOTSUPP
	 * is just क्रम adding EINT support to these भव GPIOs. It should
	 * add an extra flag in the pin descriptor when more pins with
	 * distinctive अक्षरacteristic come out.
	 */
	अगर (err && err != -ENOTSUPP)
		वापस err;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा mtk_eपूर्णांक_xt mtk_eपूर्णांक_xt = अणु
	.get_gpio_n = mtk_xt_get_gpio_n,
	.get_gpio_state = mtk_xt_get_gpio_state,
	.set_gpio_as_eपूर्णांक = mtk_xt_set_gpio_as_eपूर्णांक,
पूर्ण;

पूर्णांक mtk_build_eपूर्णांक(काष्ठा mtk_pinctrl *hw, काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	पूर्णांक ret;

	अगर (!IS_ENABLED(CONFIG_EINT_MTK))
		वापस 0;

	अगर (!of_property_पढ़ो_bool(np, "interrupt-controller"))
		वापस -ENODEV;

	hw->eपूर्णांक = devm_kzalloc(hw->dev, माप(*hw->eपूर्णांक), GFP_KERNEL);
	अगर (!hw->eपूर्णांक)
		वापस -ENOMEM;

	hw->eपूर्णांक->base = devm_platक्रमm_ioremap_resource_byname(pdev, "eint");
	अगर (IS_ERR(hw->eपूर्णांक->base)) अणु
		ret = PTR_ERR(hw->eपूर्णांक->base);
		जाओ err_मुक्त_eपूर्णांक;
	पूर्ण

	hw->eपूर्णांक->irq = irq_of_parse_and_map(np, 0);
	अगर (!hw->eपूर्णांक->irq) अणु
		ret = -EINVAL;
		जाओ err_मुक्त_eपूर्णांक;
	पूर्ण

	अगर (!hw->soc->eपूर्णांक_hw) अणु
		ret = -ENODEV;
		जाओ err_मुक्त_eपूर्णांक;
	पूर्ण

	hw->eपूर्णांक->dev = &pdev->dev;
	hw->eपूर्णांक->hw = hw->soc->eपूर्णांक_hw;
	hw->eपूर्णांक->pctl = hw;
	hw->eपूर्णांक->gpio_xlate = &mtk_eपूर्णांक_xt;

	वापस mtk_eपूर्णांक_करो_init(hw->eपूर्णांक);

err_मुक्त_eपूर्णांक:
	devm_kमुक्त(hw->dev, hw->eपूर्णांक);
	hw->eपूर्णांक = शून्य;
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(mtk_build_eपूर्णांक);

/* Revision 0 */
पूर्णांक mtk_pinconf_bias_disable_set(काष्ठा mtk_pinctrl *hw,
				 स्थिर काष्ठा mtk_pin_desc *desc)
अणु
	पूर्णांक err;

	err = mtk_hw_set_value(hw, desc, PINCTRL_PIN_REG_PU,
			       MTK_DISABLE);
	अगर (err)
		वापस err;

	err = mtk_hw_set_value(hw, desc, PINCTRL_PIN_REG_PD,
			       MTK_DISABLE);
	अगर (err)
		वापस err;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(mtk_pinconf_bias_disable_set);

पूर्णांक mtk_pinconf_bias_disable_get(काष्ठा mtk_pinctrl *hw,
				 स्थिर काष्ठा mtk_pin_desc *desc, पूर्णांक *res)
अणु
	पूर्णांक v, v2;
	पूर्णांक err;

	err = mtk_hw_get_value(hw, desc, PINCTRL_PIN_REG_PU, &v);
	अगर (err)
		वापस err;

	err = mtk_hw_get_value(hw, desc, PINCTRL_PIN_REG_PD, &v2);
	अगर (err)
		वापस err;

	अगर (v == MTK_ENABLE || v2 == MTK_ENABLE)
		वापस -EINVAL;

	*res = 1;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(mtk_pinconf_bias_disable_get);

पूर्णांक mtk_pinconf_bias_set(काष्ठा mtk_pinctrl *hw,
			 स्थिर काष्ठा mtk_pin_desc *desc, bool pullup)
अणु
	पूर्णांक err, arg;

	arg = pullup ? 1 : 2;

	err = mtk_hw_set_value(hw, desc, PINCTRL_PIN_REG_PU, arg & 1);
	अगर (err)
		वापस err;

	err = mtk_hw_set_value(hw, desc, PINCTRL_PIN_REG_PD,
			       !!(arg & 2));
	अगर (err)
		वापस err;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(mtk_pinconf_bias_set);

पूर्णांक mtk_pinconf_bias_get(काष्ठा mtk_pinctrl *hw,
			 स्थिर काष्ठा mtk_pin_desc *desc, bool pullup, पूर्णांक *res)
अणु
	पूर्णांक reg, err, v;

	reg = pullup ? PINCTRL_PIN_REG_PU : PINCTRL_PIN_REG_PD;

	err = mtk_hw_get_value(hw, desc, reg, &v);
	अगर (err)
		वापस err;

	अगर (!v)
		वापस -EINVAL;

	*res = 1;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(mtk_pinconf_bias_get);

/* Revision 1 */
पूर्णांक mtk_pinconf_bias_disable_set_rev1(काष्ठा mtk_pinctrl *hw,
				      स्थिर काष्ठा mtk_pin_desc *desc)
अणु
	वापस mtk_hw_set_value(hw, desc, PINCTRL_PIN_REG_PULLEN,
				MTK_DISABLE);
पूर्ण
EXPORT_SYMBOL_GPL(mtk_pinconf_bias_disable_set_rev1);

पूर्णांक mtk_pinconf_bias_disable_get_rev1(काष्ठा mtk_pinctrl *hw,
				      स्थिर काष्ठा mtk_pin_desc *desc, पूर्णांक *res)
अणु
	पूर्णांक v, err;

	err = mtk_hw_get_value(hw, desc, PINCTRL_PIN_REG_PULLEN, &v);
	अगर (err)
		वापस err;

	अगर (v == MTK_ENABLE)
		वापस -EINVAL;

	*res = 1;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(mtk_pinconf_bias_disable_get_rev1);

पूर्णांक mtk_pinconf_bias_set_rev1(काष्ठा mtk_pinctrl *hw,
			      स्थिर काष्ठा mtk_pin_desc *desc, bool pullup)
अणु
	पूर्णांक err, arg;

	arg = pullup ? MTK_PULLUP : MTK_PULLDOWN;

	err = mtk_hw_set_value(hw, desc, PINCTRL_PIN_REG_PULLEN,
			       MTK_ENABLE);
	अगर (err)
		वापस err;

	err = mtk_hw_set_value(hw, desc, PINCTRL_PIN_REG_PULLSEL, arg);
	अगर (err)
		वापस err;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(mtk_pinconf_bias_set_rev1);

पूर्णांक mtk_pinconf_bias_get_rev1(काष्ठा mtk_pinctrl *hw,
			      स्थिर काष्ठा mtk_pin_desc *desc, bool pullup,
			      पूर्णांक *res)
अणु
	पूर्णांक err, v;

	err = mtk_hw_get_value(hw, desc, PINCTRL_PIN_REG_PULLEN, &v);
	अगर (err)
		वापस err;

	अगर (v == MTK_DISABLE)
		वापस -EINVAL;

	err = mtk_hw_get_value(hw, desc, PINCTRL_PIN_REG_PULLSEL, &v);
	अगर (err)
		वापस err;

	अगर (pullup ^ (v == MTK_PULLUP))
		वापस -EINVAL;

	*res = 1;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(mtk_pinconf_bias_get_rev1);

/* Combo क्रम the following pull रेजिस्टर type:
 * 1. PU + PD
 * 2. PULLSEL + PULLEN
 * 3. PUPD + R0 + R1
 */
अटल पूर्णांक mtk_pinconf_bias_set_pu_pd(काष्ठा mtk_pinctrl *hw,
				स्थिर काष्ठा mtk_pin_desc *desc,
				u32 pullup, u32 arg)
अणु
	पूर्णांक err, pu, pd;

	अगर (arg == MTK_DISABLE) अणु
		pu = 0;
		pd = 0;
	पूर्ण अन्यथा अगर ((arg == MTK_ENABLE) && pullup) अणु
		pu = 1;
		pd = 0;
	पूर्ण अन्यथा अगर ((arg == MTK_ENABLE) && !pullup) अणु
		pu = 0;
		pd = 1;
	पूर्ण अन्यथा अणु
		err = -EINVAL;
		जाओ out;
	पूर्ण

	err = mtk_hw_set_value(hw, desc, PINCTRL_PIN_REG_PU, pu);
	अगर (err)
		जाओ out;

	err = mtk_hw_set_value(hw, desc, PINCTRL_PIN_REG_PD, pd);

out:
	वापस err;
पूर्ण

अटल पूर्णांक mtk_pinconf_bias_set_pullsel_pullen(काष्ठा mtk_pinctrl *hw,
				स्थिर काष्ठा mtk_pin_desc *desc,
				u32 pullup, u32 arg)
अणु
	पूर्णांक err, enable;

	अगर (arg == MTK_DISABLE)
		enable = 0;
	अन्यथा अगर (arg == MTK_ENABLE)
		enable = 1;
	अन्यथा अणु
		err = -EINVAL;
		जाओ out;
	पूर्ण

	err = mtk_hw_set_value(hw, desc, PINCTRL_PIN_REG_PULLEN, enable);
	अगर (err)
		जाओ out;

	err = mtk_hw_set_value(hw, desc, PINCTRL_PIN_REG_PULLSEL, pullup);

out:
	वापस err;
पूर्ण

अटल पूर्णांक mtk_pinconf_bias_set_pupd_r1_r0(काष्ठा mtk_pinctrl *hw,
				स्थिर काष्ठा mtk_pin_desc *desc,
				u32 pullup, u32 arg)
अणु
	पूर्णांक err, r0, r1;

	अगर ((arg == MTK_DISABLE) || (arg == MTK_PUPD_SET_R1R0_00)) अणु
		pullup = 0;
		r0 = 0;
		r1 = 0;
	पूर्ण अन्यथा अगर (arg == MTK_PUPD_SET_R1R0_01) अणु
		r0 = 1;
		r1 = 0;
	पूर्ण अन्यथा अगर (arg == MTK_PUPD_SET_R1R0_10) अणु
		r0 = 0;
		r1 = 1;
	पूर्ण अन्यथा अगर (arg == MTK_PUPD_SET_R1R0_11) अणु
		r0 = 1;
		r1 = 1;
	पूर्ण अन्यथा अणु
		err = -EINVAL;
		जाओ out;
	पूर्ण

	/* MTK HW PUPD bit: 1 क्रम pull-करोwn, 0 क्रम pull-up */
	err = mtk_hw_set_value(hw, desc, PINCTRL_PIN_REG_PUPD, !pullup);
	अगर (err)
		जाओ out;

	err = mtk_hw_set_value(hw, desc, PINCTRL_PIN_REG_R0, r0);
	अगर (err)
		जाओ out;

	err = mtk_hw_set_value(hw, desc, PINCTRL_PIN_REG_R1, r1);

out:
	वापस err;
पूर्ण

अटल पूर्णांक mtk_pinconf_bias_get_pu_pd(काष्ठा mtk_pinctrl *hw,
				स्थिर काष्ठा mtk_pin_desc *desc,
				u32 *pullup, u32 *enable)
अणु
	पूर्णांक err, pu, pd;

	err = mtk_hw_get_value(hw, desc, PINCTRL_PIN_REG_PU, &pu);
	अगर (err)
		जाओ out;

	err = mtk_hw_get_value(hw, desc, PINCTRL_PIN_REG_PD, &pd);
	अगर (err)
		जाओ out;

	अगर (pu == 0 && pd == 0) अणु
		*pullup = 0;
		*enable = MTK_DISABLE;
	पूर्ण अन्यथा अगर (pu == 1 && pd == 0) अणु
		*pullup = 1;
		*enable = MTK_ENABLE;
	पूर्ण अन्यथा अगर (pu == 0 && pd == 1) अणु
		*pullup = 0;
		*enable = MTK_ENABLE;
	पूर्ण अन्यथा
		err = -EINVAL;

out:
	वापस err;
पूर्ण

अटल पूर्णांक mtk_pinconf_bias_get_pullsel_pullen(काष्ठा mtk_pinctrl *hw,
				स्थिर काष्ठा mtk_pin_desc *desc,
				u32 *pullup, u32 *enable)
अणु
	पूर्णांक err;

	err = mtk_hw_get_value(hw, desc, PINCTRL_PIN_REG_PULLSEL, pullup);
	अगर (err)
		जाओ out;

	err = mtk_hw_get_value(hw, desc, PINCTRL_PIN_REG_PULLEN, enable);

out:
	वापस err;
पूर्ण

अटल पूर्णांक mtk_pinconf_bias_get_pupd_r1_r0(काष्ठा mtk_pinctrl *hw,
				स्थिर काष्ठा mtk_pin_desc *desc,
				u32 *pullup, u32 *enable)
अणु
	पूर्णांक err, r0, r1;

	err = mtk_hw_get_value(hw, desc, PINCTRL_PIN_REG_PUPD, pullup);
	अगर (err)
		जाओ out;
	/* MTK HW PUPD bit: 1 क्रम pull-करोwn, 0 क्रम pull-up */
	*pullup = !(*pullup);

	err = mtk_hw_get_value(hw, desc, PINCTRL_PIN_REG_R0, &r0);
	अगर (err)
		जाओ out;

	err = mtk_hw_get_value(hw, desc, PINCTRL_PIN_REG_R1, &r1);
	अगर (err)
		जाओ out;

	अगर ((r1 == 0) && (r0 == 0))
		*enable = MTK_PUPD_SET_R1R0_00;
	अन्यथा अगर ((r1 == 0) && (r0 == 1))
		*enable = MTK_PUPD_SET_R1R0_01;
	अन्यथा अगर ((r1 == 1) && (r0 == 0))
		*enable = MTK_PUPD_SET_R1R0_10;
	अन्यथा अगर ((r1 == 1) && (r0 == 1))
		*enable = MTK_PUPD_SET_R1R0_11;
	अन्यथा
		err = -EINVAL;

out:
	वापस err;
पूर्ण

पूर्णांक mtk_pinconf_bias_set_combo(काष्ठा mtk_pinctrl *hw,
				स्थिर काष्ठा mtk_pin_desc *desc,
				u32 pullup, u32 arg)
अणु
	पूर्णांक err;

	err = mtk_pinconf_bias_set_pu_pd(hw, desc, pullup, arg);
	अगर (!err)
		जाओ out;

	err = mtk_pinconf_bias_set_pullsel_pullen(hw, desc, pullup, arg);
	अगर (!err)
		जाओ out;

	err = mtk_pinconf_bias_set_pupd_r1_r0(hw, desc, pullup, arg);

out:
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(mtk_pinconf_bias_set_combo);

पूर्णांक mtk_pinconf_bias_get_combo(काष्ठा mtk_pinctrl *hw,
			      स्थिर काष्ठा mtk_pin_desc *desc,
			      u32 *pullup, u32 *enable)
अणु
	पूर्णांक err;

	err = mtk_pinconf_bias_get_pu_pd(hw, desc, pullup, enable);
	अगर (!err)
		जाओ out;

	err = mtk_pinconf_bias_get_pullsel_pullen(hw, desc, pullup, enable);
	अगर (!err)
		जाओ out;

	err = mtk_pinconf_bias_get_pupd_r1_r0(hw, desc, pullup, enable);

out:
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(mtk_pinconf_bias_get_combo);

/* Revision 0 */
पूर्णांक mtk_pinconf_drive_set(काष्ठा mtk_pinctrl *hw,
			  स्थिर काष्ठा mtk_pin_desc *desc, u32 arg)
अणु
	स्थिर काष्ठा mtk_drive_desc *tb;
	पूर्णांक err = -ENOTSUPP;

	tb = &mtk_drive[desc->drv_n];
	/* 4mA when (e8, e4) = (0, 0)
	 * 8mA when (e8, e4) = (0, 1)
	 * 12mA when (e8, e4) = (1, 0)
	 * 16mA when (e8, e4) = (1, 1)
	 */
	अगर ((arg >= tb->min && arg <= tb->max) && !(arg % tb->step)) अणु
		arg = (arg / tb->step - 1) * tb->scal;
		err = mtk_hw_set_value(hw, desc, PINCTRL_PIN_REG_E4,
				       arg & 0x1);
		अगर (err)
			वापस err;

		err = mtk_hw_set_value(hw, desc, PINCTRL_PIN_REG_E8,
				       (arg & 0x2) >> 1);
		अगर (err)
			वापस err;
	पूर्ण

	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(mtk_pinconf_drive_set);

पूर्णांक mtk_pinconf_drive_get(काष्ठा mtk_pinctrl *hw,
			  स्थिर काष्ठा mtk_pin_desc *desc, पूर्णांक *val)
अणु
	स्थिर काष्ठा mtk_drive_desc *tb;
	पूर्णांक err, val1, val2;

	tb = &mtk_drive[desc->drv_n];

	err = mtk_hw_get_value(hw, desc, PINCTRL_PIN_REG_E4, &val1);
	अगर (err)
		वापस err;

	err = mtk_hw_get_value(hw, desc, PINCTRL_PIN_REG_E8, &val2);
	अगर (err)
		वापस err;

	/* 4mA when (e8, e4) = (0, 0); 8mA when (e8, e4) = (0, 1)
	 * 12mA when (e8, e4) = (1, 0); 16mA when (e8, e4) = (1, 1)
	 */
	*val = (((val2 << 1) + val1) / tb->scal + 1) * tb->step;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(mtk_pinconf_drive_get);

/* Revision 1 */
पूर्णांक mtk_pinconf_drive_set_rev1(काष्ठा mtk_pinctrl *hw,
			       स्थिर काष्ठा mtk_pin_desc *desc, u32 arg)
अणु
	स्थिर काष्ठा mtk_drive_desc *tb;
	पूर्णांक err = -ENOTSUPP;

	tb = &mtk_drive[desc->drv_n];

	अगर ((arg >= tb->min && arg <= tb->max) && !(arg % tb->step)) अणु
		arg = (arg / tb->step - 1) * tb->scal;

		err = mtk_hw_set_value(hw, desc, PINCTRL_PIN_REG_DRV,
				       arg);
		अगर (err)
			वापस err;
	पूर्ण

	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(mtk_pinconf_drive_set_rev1);

पूर्णांक mtk_pinconf_drive_get_rev1(काष्ठा mtk_pinctrl *hw,
			       स्थिर काष्ठा mtk_pin_desc *desc, पूर्णांक *val)
अणु
	स्थिर काष्ठा mtk_drive_desc *tb;
	पूर्णांक err, val1;

	tb = &mtk_drive[desc->drv_n];

	err = mtk_hw_get_value(hw, desc, PINCTRL_PIN_REG_DRV, &val1);
	अगर (err)
		वापस err;

	*val = ((val1 & 0x7) / tb->scal + 1) * tb->step;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(mtk_pinconf_drive_get_rev1);

पूर्णांक mtk_pinconf_drive_set_raw(काष्ठा mtk_pinctrl *hw,
			       स्थिर काष्ठा mtk_pin_desc *desc, u32 arg)
अणु
	वापस mtk_hw_set_value(hw, desc, PINCTRL_PIN_REG_DRV, arg);
पूर्ण
EXPORT_SYMBOL_GPL(mtk_pinconf_drive_set_raw);

पूर्णांक mtk_pinconf_drive_get_raw(काष्ठा mtk_pinctrl *hw,
			       स्थिर काष्ठा mtk_pin_desc *desc, पूर्णांक *val)
अणु
	वापस mtk_hw_get_value(hw, desc, PINCTRL_PIN_REG_DRV, val);
पूर्ण
EXPORT_SYMBOL_GPL(mtk_pinconf_drive_get_raw);

पूर्णांक mtk_pinconf_adv_pull_set(काष्ठा mtk_pinctrl *hw,
			     स्थिर काष्ठा mtk_pin_desc *desc, bool pullup,
			     u32 arg)
अणु
	पूर्णांक err;

	/* 10K off & 50K (75K) off, when (R0, R1) = (0, 0);
	 * 10K off & 50K (75K) on, when (R0, R1) = (0, 1);
	 * 10K on & 50K (75K) off, when (R0, R1) = (1, 0);
	 * 10K on & 50K (75K) on, when (R0, R1) = (1, 1)
	 */
	err = mtk_hw_set_value(hw, desc, PINCTRL_PIN_REG_R0, arg & 1);
	अगर (err)
		वापस 0;

	err = mtk_hw_set_value(hw, desc, PINCTRL_PIN_REG_R1,
			       !!(arg & 2));
	अगर (err)
		वापस 0;

	arg = pullup ? 0 : 1;

	err = mtk_hw_set_value(hw, desc, PINCTRL_PIN_REG_PUPD, arg);

	/* If PUPD रेजिस्टर is not supported क्रम that pin, let's fallback to
	 * general bias control.
	 */
	अगर (err == -ENOTSUPP) अणु
		अगर (hw->soc->bias_set) अणु
			err = hw->soc->bias_set(hw, desc, pullup);
			अगर (err)
				वापस err;
		पूर्ण अन्यथा अगर (hw->soc->bias_set_combo) अणु
			err = hw->soc->bias_set_combo(hw, desc, pullup, arg);
			अगर (err)
				वापस err;
		पूर्ण अन्यथा अणु
			वापस -ENOTSUPP;
		पूर्ण
	पूर्ण

	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(mtk_pinconf_adv_pull_set);

पूर्णांक mtk_pinconf_adv_pull_get(काष्ठा mtk_pinctrl *hw,
			     स्थिर काष्ठा mtk_pin_desc *desc, bool pullup,
			     u32 *val)
अणु
	u32 t, t2;
	पूर्णांक err;

	err = mtk_hw_get_value(hw, desc, PINCTRL_PIN_REG_PUPD, &t);

	/* If PUPD रेजिस्टर is not supported क्रम that pin, let's fallback to
	 * general bias control.
	 */
	अगर (err == -ENOTSUPP) अणु
		अगर (hw->soc->bias_get) अणु
			err = hw->soc->bias_get(hw, desc, pullup, val);
			अगर (err)
				वापस err;
		पूर्ण अन्यथा अणु
			वापस -ENOTSUPP;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* t == 0 supposes PULLUP क्रम the customized PULL setup */
		अगर (err)
			वापस err;

		अगर (pullup ^ !t)
			वापस -EINVAL;
	पूर्ण

	err = mtk_hw_get_value(hw, desc, PINCTRL_PIN_REG_R0, &t);
	अगर (err)
		वापस err;

	err = mtk_hw_get_value(hw, desc, PINCTRL_PIN_REG_R1, &t2);
	अगर (err)
		वापस err;

	*val = (t | t2 << 1) & 0x7;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(mtk_pinconf_adv_pull_get);

पूर्णांक mtk_pinconf_adv_drive_set(काष्ठा mtk_pinctrl *hw,
			      स्थिर काष्ठा mtk_pin_desc *desc, u32 arg)
अणु
	पूर्णांक err;
	पूर्णांक en = arg & 1;
	पूर्णांक e0 = !!(arg & 2);
	पूर्णांक e1 = !!(arg & 4);

	err = mtk_hw_set_value(hw, desc, PINCTRL_PIN_REG_DRV_EN, en);
	अगर (err)
		वापस err;

	अगर (!en)
		वापस err;

	err = mtk_hw_set_value(hw, desc, PINCTRL_PIN_REG_DRV_E0, e0);
	अगर (err)
		वापस err;

	err = mtk_hw_set_value(hw, desc, PINCTRL_PIN_REG_DRV_E1, e1);
	अगर (err)
		वापस err;

	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(mtk_pinconf_adv_drive_set);

पूर्णांक mtk_pinconf_adv_drive_get(काष्ठा mtk_pinctrl *hw,
			      स्थिर काष्ठा mtk_pin_desc *desc, u32 *val)
अणु
	u32 en, e0, e1;
	पूर्णांक err;

	err = mtk_hw_get_value(hw, desc, PINCTRL_PIN_REG_DRV_EN, &en);
	अगर (err)
		वापस err;

	err = mtk_hw_get_value(hw, desc, PINCTRL_PIN_REG_DRV_E0, &e0);
	अगर (err)
		वापस err;

	err = mtk_hw_get_value(hw, desc, PINCTRL_PIN_REG_DRV_E1, &e1);
	अगर (err)
		वापस err;

	*val = (en | e0 << 1 | e1 << 2) & 0x7;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(mtk_pinconf_adv_drive_get);

पूर्णांक mtk_pinconf_adv_drive_set_raw(काष्ठा mtk_pinctrl *hw,
				  स्थिर काष्ठा mtk_pin_desc *desc, u32 arg)
अणु
	वापस mtk_hw_set_value(hw, desc, PINCTRL_PIN_REG_DRV_ADV, arg);
पूर्ण
EXPORT_SYMBOL_GPL(mtk_pinconf_adv_drive_set_raw);

पूर्णांक mtk_pinconf_adv_drive_get_raw(काष्ठा mtk_pinctrl *hw,
				  स्थिर काष्ठा mtk_pin_desc *desc, u32 *val)
अणु
	वापस mtk_hw_get_value(hw, desc, PINCTRL_PIN_REG_DRV_ADV, val);
पूर्ण
EXPORT_SYMBOL_GPL(mtk_pinconf_adv_drive_get_raw);

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Sean Wang <sean.wang@mediatek.com>");
MODULE_DESCRIPTION("Pin configuration library module for mediatek SoCs");
