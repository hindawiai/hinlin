<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Pin Control and GPIO driver क्रम SuperH Pin Function Controller.
 *
 * Authors: Magnus Damm, Paul Mundt, Laurent Pinअक्षरt
 *
 * Copyright (C) 2008 Magnus Damm
 * Copyright (C) 2009 - 2012 Paul Mundt
 */

#घोषणा DRV_NAME "sh-pfc"

#समावेश <linux/bitops.h>
#समावेश <linux/err.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/पन.स>
#समावेश <linux/ioport.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/pinctrl/machine.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/psci.h>
#समावेश <linux/slab.h>
#समावेश <linux/sys_soc.h>

#समावेश "core.h"

अटल पूर्णांक sh_pfc_map_resources(काष्ठा sh_pfc *pfc,
				काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sh_pfc_winकरोw *winकरोws;
	अचिन्हित पूर्णांक *irqs = शून्य;
	अचिन्हित पूर्णांक num_winकरोws;
	काष्ठा resource *res;
	अचिन्हित पूर्णांक i;
	पूर्णांक num_irqs;

	/* Count the MEM and IRQ resources. */
	क्रम (num_winकरोws = 0;; num_winकरोws++) अणु
		res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, num_winकरोws);
		अगर (!res)
			अवरोध;
	पूर्ण
	अगर (num_winकरोws == 0)
		वापस -EINVAL;

	num_irqs = platक्रमm_irq_count(pdev);
	अगर (num_irqs < 0)
		वापस num_irqs;

	/* Allocate memory winकरोws and IRQs arrays. */
	winकरोws = devm_kसुस्मृति(pfc->dev, num_winकरोws, माप(*winकरोws),
			       GFP_KERNEL);
	अगर (winकरोws == शून्य)
		वापस -ENOMEM;

	pfc->num_winकरोws = num_winकरोws;
	pfc->winकरोws = winकरोws;

	अगर (num_irqs) अणु
		irqs = devm_kसुस्मृति(pfc->dev, num_irqs, माप(*irqs),
				    GFP_KERNEL);
		अगर (irqs == शून्य)
			वापस -ENOMEM;

		pfc->num_irqs = num_irqs;
		pfc->irqs = irqs;
	पूर्ण

	/* Fill them. */
	क्रम (i = 0; i < num_winकरोws; i++) अणु
		res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, i);
		winकरोws->phys = res->start;
		winकरोws->size = resource_size(res);
		winकरोws->virt = devm_ioremap_resource(pfc->dev, res);
		अगर (IS_ERR(winकरोws->virt))
			वापस -ENOMEM;
		winकरोws++;
	पूर्ण
	क्रम (i = 0; i < num_irqs; i++)
		*irqs++ = platक्रमm_get_irq(pdev, i);

	वापस 0;
पूर्ण

अटल व्योम __iomem *sh_pfc_phys_to_virt(काष्ठा sh_pfc *pfc, u32 reg)
अणु
	काष्ठा sh_pfc_winकरोw *winकरोw;
	phys_addr_t address = reg;
	अचिन्हित पूर्णांक i;

	/* scan through physical winकरोws and convert address */
	क्रम (i = 0; i < pfc->num_winकरोws; i++) अणु
		winकरोw = pfc->winकरोws + i;

		अगर (address < winकरोw->phys)
			जारी;

		अगर (address >= (winकरोw->phys + winकरोw->size))
			जारी;

		वापस winकरोw->virt + (address - winकरोw->phys);
	पूर्ण

	BUG();
	वापस शून्य;
पूर्ण

पूर्णांक sh_pfc_get_pin_index(काष्ठा sh_pfc *pfc, अचिन्हित पूर्णांक pin)
अणु
	अचिन्हित पूर्णांक offset;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0, offset = 0; i < pfc->nr_ranges; ++i) अणु
		स्थिर काष्ठा sh_pfc_pin_range *range = &pfc->ranges[i];

		अगर (pin <= range->end)
			वापस pin >= range->start
			     ? offset + pin - range->start : -1;

		offset += range->end - range->start + 1;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक sh_pfc_क्रमागत_in_range(u16 क्रमागत_id, स्थिर काष्ठा pinmux_range *r)
अणु
	अगर (क्रमागत_id < r->begin)
		वापस 0;

	अगर (क्रमागत_id > r->end)
		वापस 0;

	वापस 1;
पूर्ण

u32 sh_pfc_पढ़ो_raw_reg(व्योम __iomem *mapped_reg, अचिन्हित पूर्णांक reg_width)
अणु
	चयन (reg_width) अणु
	हाल 8:
		वापस ioपढ़ो8(mapped_reg);
	हाल 16:
		वापस ioपढ़ो16(mapped_reg);
	हाल 32:
		वापस ioपढ़ो32(mapped_reg);
	पूर्ण

	BUG();
	वापस 0;
पूर्ण

व्योम sh_pfc_ग_लिखो_raw_reg(व्योम __iomem *mapped_reg, अचिन्हित पूर्णांक reg_width,
			  u32 data)
अणु
	चयन (reg_width) अणु
	हाल 8:
		ioग_लिखो8(data, mapped_reg);
		वापस;
	हाल 16:
		ioग_लिखो16(data, mapped_reg);
		वापस;
	हाल 32:
		ioग_लिखो32(data, mapped_reg);
		वापस;
	पूर्ण

	BUG();
पूर्ण

u32 sh_pfc_पढ़ो(काष्ठा sh_pfc *pfc, u32 reg)
अणु
	वापस sh_pfc_पढ़ो_raw_reg(sh_pfc_phys_to_virt(pfc, reg), 32);
पूर्ण

अटल व्योम sh_pfc_unlock_reg(काष्ठा sh_pfc *pfc, u32 reg, u32 data)
अणु
	u32 unlock;

	अगर (!pfc->info->unlock_reg)
		वापस;

	अगर (pfc->info->unlock_reg >= 0x80000000UL)
		unlock = pfc->info->unlock_reg;
	अन्यथा
		/* unlock_reg is a mask */
		unlock = reg & ~pfc->info->unlock_reg;

	sh_pfc_ग_लिखो_raw_reg(sh_pfc_phys_to_virt(pfc, unlock), 32, ~data);
पूर्ण

व्योम sh_pfc_ग_लिखो(काष्ठा sh_pfc *pfc, u32 reg, u32 data)
अणु
	sh_pfc_unlock_reg(pfc, reg, data);
	sh_pfc_ग_लिखो_raw_reg(sh_pfc_phys_to_virt(pfc, reg), 32, data);
पूर्ण

अटल व्योम sh_pfc_config_reg_helper(काष्ठा sh_pfc *pfc,
				     स्थिर काष्ठा pinmux_cfg_reg *crp,
				     अचिन्हित पूर्णांक in_pos,
				     व्योम __iomem **mapped_regp, u32 *maskp,
				     अचिन्हित पूर्णांक *posp)
अणु
	अचिन्हित पूर्णांक k;

	*mapped_regp = sh_pfc_phys_to_virt(pfc, crp->reg);

	अगर (crp->field_width) अणु
		*maskp = (1 << crp->field_width) - 1;
		*posp = crp->reg_width - ((in_pos + 1) * crp->field_width);
	पूर्ण अन्यथा अणु
		*maskp = (1 << crp->var_field_width[in_pos]) - 1;
		*posp = crp->reg_width;
		क्रम (k = 0; k <= in_pos; k++)
			*posp -= crp->var_field_width[k];
	पूर्ण
पूर्ण

अटल व्योम sh_pfc_ग_लिखो_config_reg(काष्ठा sh_pfc *pfc,
				    स्थिर काष्ठा pinmux_cfg_reg *crp,
				    अचिन्हित पूर्णांक field, u32 value)
अणु
	व्योम __iomem *mapped_reg;
	अचिन्हित पूर्णांक pos;
	u32 mask, data;

	sh_pfc_config_reg_helper(pfc, crp, field, &mapped_reg, &mask, &pos);

	dev_dbg(pfc->dev, "write_reg addr = %x, value = 0x%x, field = %u, "
		"r_width = %u, f_width = %u\n",
		crp->reg, value, field, crp->reg_width, hweight32(mask));

	mask = ~(mask << pos);
	value = value << pos;

	data = sh_pfc_पढ़ो_raw_reg(mapped_reg, crp->reg_width);
	data &= mask;
	data |= value;

	sh_pfc_unlock_reg(pfc, crp->reg, data);
	sh_pfc_ग_लिखो_raw_reg(mapped_reg, crp->reg_width, data);
पूर्ण

अटल पूर्णांक sh_pfc_get_config_reg(काष्ठा sh_pfc *pfc, u16 क्रमागत_id,
				 स्थिर काष्ठा pinmux_cfg_reg **crp,
				 अचिन्हित पूर्णांक *fieldp, u32 *valuep)
अणु
	अचिन्हित पूर्णांक k = 0;

	जबतक (1) अणु
		स्थिर काष्ठा pinmux_cfg_reg *config_reg =
			pfc->info->cfg_regs + k;
		अचिन्हित पूर्णांक r_width = config_reg->reg_width;
		अचिन्हित पूर्णांक f_width = config_reg->field_width;
		अचिन्हित पूर्णांक curr_width;
		अचिन्हित पूर्णांक bit_pos;
		अचिन्हित पूर्णांक pos = 0;
		अचिन्हित पूर्णांक m = 0;

		अगर (!r_width)
			अवरोध;

		क्रम (bit_pos = 0; bit_pos < r_width; bit_pos += curr_width) अणु
			u32 ncomb;
			u32 n;

			अगर (f_width)
				curr_width = f_width;
			अन्यथा
				curr_width = config_reg->var_field_width[m];

			ncomb = 1 << curr_width;
			क्रम (n = 0; n < ncomb; n++) अणु
				अगर (config_reg->क्रमागत_ids[pos + n] == क्रमागत_id) अणु
					*crp = config_reg;
					*fieldp = m;
					*valuep = n;
					वापस 0;
				पूर्ण
			पूर्ण
			pos += ncomb;
			m++;
		पूर्ण
		k++;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक sh_pfc_mark_to_क्रमागत(काष्ठा sh_pfc *pfc, u16 mark, पूर्णांक pos,
			      u16 *क्रमागत_idp)
अणु
	स्थिर u16 *data = pfc->info->pinmux_data;
	अचिन्हित पूर्णांक k;

	अगर (pos) अणु
		*क्रमागत_idp = data[pos + 1];
		वापस pos + 1;
	पूर्ण

	क्रम (k = 0; k < pfc->info->pinmux_data_size; k++) अणु
		अगर (data[k] == mark) अणु
			*क्रमागत_idp = data[k + 1];
			वापस k + 1;
		पूर्ण
	पूर्ण

	dev_err(pfc->dev, "cannot locate data/mark enum_id for mark %d\n",
		mark);
	वापस -EINVAL;
पूर्ण

पूर्णांक sh_pfc_config_mux(काष्ठा sh_pfc *pfc, अचिन्हित mark, पूर्णांक pinmux_type)
अणु
	स्थिर काष्ठा pinmux_range *range;
	पूर्णांक pos = 0;

	चयन (pinmux_type) अणु
	हाल PINMUX_TYPE_GPIO:
	हाल PINMUX_TYPE_FUNCTION:
		range = शून्य;
		अवरोध;

#अगर_घोषित CONFIG_PINCTRL_SH_PFC_GPIO
	हाल PINMUX_TYPE_OUTPUT:
		range = &pfc->info->output;
		अवरोध;

	हाल PINMUX_TYPE_INPUT:
		range = &pfc->info->input;
		अवरोध;
#पूर्ण_अगर /* CONFIG_PINCTRL_SH_PFC_GPIO */

	शेष:
		वापस -EINVAL;
	पूर्ण

	/* Iterate over all the configuration fields we need to update. */
	जबतक (1) अणु
		स्थिर काष्ठा pinmux_cfg_reg *cr;
		अचिन्हित पूर्णांक field;
		u16 क्रमागत_id;
		u32 value;
		पूर्णांक in_range;
		पूर्णांक ret;

		pos = sh_pfc_mark_to_क्रमागत(pfc, mark, pos, &क्रमागत_id);
		अगर (pos < 0)
			वापस pos;

		अगर (!क्रमागत_id)
			अवरोध;

		/* Check अगर the configuration field selects a function. If it
		 * करोesn't, skip the field if it's not applicable to the
		 * requested pinmux type.
		 */
		in_range = sh_pfc_क्रमागत_in_range(क्रमागत_id, &pfc->info->function);
		अगर (!in_range) अणु
			अगर (pinmux_type == PINMUX_TYPE_FUNCTION) अणु
				/* Functions are allowed to modअगरy all
				 * fields.
				 */
				in_range = 1;
			पूर्ण अन्यथा अगर (pinmux_type != PINMUX_TYPE_GPIO) अणु
				/* Input/output types can only modअगरy fields
				 * that correspond to their respective ranges.
				 */
				in_range = sh_pfc_क्रमागत_in_range(क्रमागत_id, range);

				/*
				 * special हाल pass through क्रम fixed
				 * input-only or output-only pins without
				 * function क्रमागत रेजिस्टर association.
				 */
				अगर (in_range && क्रमागत_id == range->क्रमce)
					जारी;
			पूर्ण
			/* GPIOs are only allowed to modअगरy function fields. */
		पूर्ण

		अगर (!in_range)
			जारी;

		ret = sh_pfc_get_config_reg(pfc, क्रमागत_id, &cr, &field, &value);
		अगर (ret < 0)
			वापस ret;

		sh_pfc_ग_लिखो_config_reg(pfc, cr, field, value);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sh_pfc_init_ranges(काष्ठा sh_pfc *pfc)
अणु
	काष्ठा sh_pfc_pin_range *range;
	अचिन्हित पूर्णांक nr_ranges;
	अचिन्हित पूर्णांक i;

	अगर (pfc->info->pins[0].pin == (u16)-1) अणु
		/* Pin number -1 denotes that the SoC करोesn't report pin numbers
		 * in its pin arrays yet. Consider the pin numbers range as
		 * continuous and allocate a single range.
		 */
		pfc->nr_ranges = 1;
		pfc->ranges = devm_kzalloc(pfc->dev, माप(*pfc->ranges),
					   GFP_KERNEL);
		अगर (pfc->ranges == शून्य)
			वापस -ENOMEM;

		pfc->ranges->start = 0;
		pfc->ranges->end = pfc->info->nr_pins - 1;
		pfc->nr_gpio_pins = pfc->info->nr_pins;

		वापस 0;
	पूर्ण

	/* Count, allocate and fill the ranges. The PFC SoC data pins array must
	 * be sorted by pin numbers, and pins without a GPIO port must come
	 * last.
	 */
	क्रम (i = 1, nr_ranges = 1; i < pfc->info->nr_pins; ++i) अणु
		अगर (pfc->info->pins[i-1].pin != pfc->info->pins[i].pin - 1)
			nr_ranges++;
	पूर्ण

	pfc->nr_ranges = nr_ranges;
	pfc->ranges = devm_kसुस्मृति(pfc->dev, nr_ranges, माप(*pfc->ranges),
				   GFP_KERNEL);
	अगर (pfc->ranges == शून्य)
		वापस -ENOMEM;

	range = pfc->ranges;
	range->start = pfc->info->pins[0].pin;

	क्रम (i = 1; i < pfc->info->nr_pins; ++i) अणु
		अगर (pfc->info->pins[i-1].pin == pfc->info->pins[i].pin - 1)
			जारी;

		range->end = pfc->info->pins[i-1].pin;
		अगर (!(pfc->info->pins[i-1].configs & SH_PFC_PIN_CFG_NO_GPIO))
			pfc->nr_gpio_pins = range->end + 1;

		range++;
		range->start = pfc->info->pins[i].pin;
	पूर्ण

	range->end = pfc->info->pins[i-1].pin;
	अगर (!(pfc->info->pins[i-1].configs & SH_PFC_PIN_CFG_NO_GPIO))
		pfc->nr_gpio_pins = range->end + 1;

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id sh_pfc_of_table[] = अणु
#अगर_घोषित CONFIG_PINCTRL_PFC_EMEV2
	अणु
		.compatible = "renesas,pfc-emev2",
		.data = &emev2_pinmux_info,
	पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_PINCTRL_PFC_R8A73A4
	अणु
		.compatible = "renesas,pfc-r8a73a4",
		.data = &r8a73a4_pinmux_info,
	पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_PINCTRL_PFC_R8A7740
	अणु
		.compatible = "renesas,pfc-r8a7740",
		.data = &r8a7740_pinmux_info,
	पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_PINCTRL_PFC_R8A7742
	अणु
		.compatible = "renesas,pfc-r8a7742",
		.data = &r8a7742_pinmux_info,
	पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_PINCTRL_PFC_R8A7743
	अणु
		.compatible = "renesas,pfc-r8a7743",
		.data = &r8a7743_pinmux_info,
	पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_PINCTRL_PFC_R8A7744
	अणु
		.compatible = "renesas,pfc-r8a7744",
		.data = &r8a7744_pinmux_info,
	पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_PINCTRL_PFC_R8A7745
	अणु
		.compatible = "renesas,pfc-r8a7745",
		.data = &r8a7745_pinmux_info,
	पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_PINCTRL_PFC_R8A77470
	अणु
		.compatible = "renesas,pfc-r8a77470",
		.data = &r8a77470_pinmux_info,
	पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_PINCTRL_PFC_R8A774A1
	अणु
		.compatible = "renesas,pfc-r8a774a1",
		.data = &r8a774a1_pinmux_info,
	पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_PINCTRL_PFC_R8A774B1
	अणु
		.compatible = "renesas,pfc-r8a774b1",
		.data = &r8a774b1_pinmux_info,
	पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_PINCTRL_PFC_R8A774C0
	अणु
		.compatible = "renesas,pfc-r8a774c0",
		.data = &r8a774c0_pinmux_info,
	पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_PINCTRL_PFC_R8A774E1
	अणु
		.compatible = "renesas,pfc-r8a774e1",
		.data = &r8a774e1_pinmux_info,
	पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_PINCTRL_PFC_R8A7778
	अणु
		.compatible = "renesas,pfc-r8a7778",
		.data = &r8a7778_pinmux_info,
	पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_PINCTRL_PFC_R8A7779
	अणु
		.compatible = "renesas,pfc-r8a7779",
		.data = &r8a7779_pinmux_info,
	पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_PINCTRL_PFC_R8A7790
	अणु
		.compatible = "renesas,pfc-r8a7790",
		.data = &r8a7790_pinmux_info,
	पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_PINCTRL_PFC_R8A7791
	अणु
		.compatible = "renesas,pfc-r8a7791",
		.data = &r8a7791_pinmux_info,
	पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_PINCTRL_PFC_R8A7792
	अणु
		.compatible = "renesas,pfc-r8a7792",
		.data = &r8a7792_pinmux_info,
	पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_PINCTRL_PFC_R8A7793
	अणु
		.compatible = "renesas,pfc-r8a7793",
		.data = &r8a7793_pinmux_info,
	पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_PINCTRL_PFC_R8A7794
	अणु
		.compatible = "renesas,pfc-r8a7794",
		.data = &r8a7794_pinmux_info,
	पूर्ण,
#पूर्ण_अगर
/* Both r8a7795 entries must be present to make sanity checks work */
#अगर_घोषित CONFIG_PINCTRL_PFC_R8A77950
	अणु
		.compatible = "renesas,pfc-r8a7795",
		.data = &r8a77950_pinmux_info,
	पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_PINCTRL_PFC_R8A77951
	अणु
		.compatible = "renesas,pfc-r8a7795",
		.data = &r8a77951_pinmux_info,
	पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_PINCTRL_PFC_R8A77960
	अणु
		.compatible = "renesas,pfc-r8a7796",
		.data = &r8a77960_pinmux_info,
	पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_PINCTRL_PFC_R8A77961
	अणु
		.compatible = "renesas,pfc-r8a77961",
		.data = &r8a77961_pinmux_info,
	पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_PINCTRL_PFC_R8A77965
	अणु
		.compatible = "renesas,pfc-r8a77965",
		.data = &r8a77965_pinmux_info,
	पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_PINCTRL_PFC_R8A77970
	अणु
		.compatible = "renesas,pfc-r8a77970",
		.data = &r8a77970_pinmux_info,
	पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_PINCTRL_PFC_R8A77980
	अणु
		.compatible = "renesas,pfc-r8a77980",
		.data = &r8a77980_pinmux_info,
	पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_PINCTRL_PFC_R8A77990
	अणु
		.compatible = "renesas,pfc-r8a77990",
		.data = &r8a77990_pinmux_info,
	पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_PINCTRL_PFC_R8A77995
	अणु
		.compatible = "renesas,pfc-r8a77995",
		.data = &r8a77995_pinmux_info,
	पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_PINCTRL_PFC_R8A779A0
	अणु
		.compatible = "renesas,pfc-r8a779a0",
		.data = &r8a779a0_pinmux_info,
	पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_PINCTRL_PFC_SH73A0
	अणु
		.compatible = "renesas,pfc-sh73a0",
		.data = &sh73a0_pinmux_info,
	पूर्ण,
#पूर्ण_अगर
	अणु पूर्ण,
पूर्ण;
#पूर्ण_अगर

#अगर defined(CONFIG_PM_SLEEP) && defined(CONFIG_ARM_PSCI_FW)
अटल व्योम sh_pfc_nop_reg(काष्ठा sh_pfc *pfc, u32 reg, अचिन्हित पूर्णांक idx)
अणु
पूर्ण

अटल व्योम sh_pfc_save_reg(काष्ठा sh_pfc *pfc, u32 reg, अचिन्हित पूर्णांक idx)
अणु
	pfc->saved_regs[idx] = sh_pfc_पढ़ो(pfc, reg);
पूर्ण

अटल व्योम sh_pfc_restore_reg(काष्ठा sh_pfc *pfc, u32 reg, अचिन्हित पूर्णांक idx)
अणु
	sh_pfc_ग_लिखो(pfc, reg, pfc->saved_regs[idx]);
पूर्ण

अटल अचिन्हित पूर्णांक sh_pfc_walk_regs(काष्ठा sh_pfc *pfc,
	व्योम (*करो_reg)(काष्ठा sh_pfc *pfc, u32 reg, अचिन्हित पूर्णांक idx))
अणु
	अचिन्हित पूर्णांक i, n = 0;

	अगर (pfc->info->cfg_regs)
		क्रम (i = 0; pfc->info->cfg_regs[i].reg; i++)
			करो_reg(pfc, pfc->info->cfg_regs[i].reg, n++);

	अगर (pfc->info->drive_regs)
		क्रम (i = 0; pfc->info->drive_regs[i].reg; i++)
			करो_reg(pfc, pfc->info->drive_regs[i].reg, n++);

	अगर (pfc->info->bias_regs)
		क्रम (i = 0; pfc->info->bias_regs[i].puen; i++) अणु
			करो_reg(pfc, pfc->info->bias_regs[i].puen, n++);
			अगर (pfc->info->bias_regs[i].pud)
				करो_reg(pfc, pfc->info->bias_regs[i].pud, n++);
		पूर्ण

	अगर (pfc->info->ioctrl_regs)
		क्रम (i = 0; pfc->info->ioctrl_regs[i].reg; i++)
			करो_reg(pfc, pfc->info->ioctrl_regs[i].reg, n++);

	वापस n;
पूर्ण

अटल पूर्णांक sh_pfc_suspend_init(काष्ठा sh_pfc *pfc)
अणु
	अचिन्हित पूर्णांक n;

	/* This is the best we can करो to check क्रम the presence of PSCI */
	अगर (!psci_ops.cpu_suspend)
		वापस 0;

	n = sh_pfc_walk_regs(pfc, sh_pfc_nop_reg);
	अगर (!n)
		वापस 0;

	pfc->saved_regs = devm_kदो_स्मृति_array(pfc->dev, n,
					     माप(*pfc->saved_regs),
					     GFP_KERNEL);
	अगर (!pfc->saved_regs)
		वापस -ENOMEM;

	dev_dbg(pfc->dev, "Allocated space to save %u regs\n", n);
	वापस 0;
पूर्ण

अटल पूर्णांक sh_pfc_suspend_noirq(काष्ठा device *dev)
अणु
	काष्ठा sh_pfc *pfc = dev_get_drvdata(dev);

	अगर (pfc->saved_regs)
		sh_pfc_walk_regs(pfc, sh_pfc_save_reg);
	वापस 0;
पूर्ण

अटल पूर्णांक sh_pfc_resume_noirq(काष्ठा device *dev)
अणु
	काष्ठा sh_pfc *pfc = dev_get_drvdata(dev);

	अगर (pfc->saved_regs)
		sh_pfc_walk_regs(pfc, sh_pfc_restore_reg);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops sh_pfc_pm  = अणु
	SET_NOIRQ_SYSTEM_SLEEP_PM_OPS(sh_pfc_suspend_noirq, sh_pfc_resume_noirq)
पूर्ण;
#घोषणा DEV_PM_OPS	&sh_pfc_pm
#अन्यथा
अटल पूर्णांक sh_pfc_suspend_init(काष्ठा sh_pfc *pfc) अणु वापस 0; पूर्ण
#घोषणा DEV_PM_OPS	शून्य
#पूर्ण_अगर /* CONFIG_PM_SLEEP && CONFIG_ARM_PSCI_FW */

#अगर_घोषित DEBUG
#घोषणा SH_PFC_MAX_REGS		300
#घोषणा SH_PFC_MAX_ENUMS	3000

अटल अचिन्हित पूर्णांक sh_pfc_errors __initdata = 0;
अटल अचिन्हित पूर्णांक sh_pfc_warnings __initdata = 0;
अटल u32 *sh_pfc_regs __initdata = शून्य;
अटल u32 sh_pfc_num_regs __initdata = 0;
अटल u16 *sh_pfc_क्रमागतs __initdata = शून्य;
अटल u32 sh_pfc_num_क्रमागतs __initdata = 0;

#घोषणा sh_pfc_err(fmt, ...)					\
	करो अणु							\
		pr_err("%s: " fmt, drvname, ##__VA_ARGS__);	\
		sh_pfc_errors++;				\
	पूर्ण जबतक (0)
#घोषणा sh_pfc_warn(fmt, ...)					\
	करो अणु							\
		pr_warn("%s: " fmt, drvname, ##__VA_ARGS__);	\
		sh_pfc_warnings++;				\
	पूर्ण जबतक (0)

अटल bool __init is0s(स्थिर u16 *क्रमागत_ids, अचिन्हित पूर्णांक n)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < n; i++)
		अगर (क्रमागत_ids[i])
			वापस false;

	वापस true;
पूर्ण

अटल bool __init same_name(स्थिर अक्षर *a, स्थिर अक्षर *b)
अणु
	अगर (!a || !b)
		वापस false;

	वापस !म_भेद(a, b);
पूर्ण

अटल व्योम __init sh_pfc_check_reg(स्थिर अक्षर *drvname, u32 reg)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < sh_pfc_num_regs; i++)
		अगर (reg == sh_pfc_regs[i]) अणु
			sh_pfc_err("reg 0x%x conflict\n", reg);
			वापस;
		पूर्ण

	अगर (sh_pfc_num_regs == SH_PFC_MAX_REGS) अणु
		pr_warn_once("%s: Please increase SH_PFC_MAX_REGS\n", drvname);
		वापस;
	पूर्ण

	sh_pfc_regs[sh_pfc_num_regs++] = reg;
पूर्ण

अटल पूर्णांक __init sh_pfc_check_क्रमागत(स्थिर अक्षर *drvname, u16 क्रमागत_id)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < sh_pfc_num_क्रमागतs; i++) अणु
		अगर (क्रमागत_id == sh_pfc_क्रमागतs[i])
			वापस -EINVAL;
	पूर्ण

	अगर (sh_pfc_num_क्रमागतs == SH_PFC_MAX_ENUMS) अणु
		pr_warn_once("%s: Please increase SH_PFC_MAX_ENUMS\n", drvname);
		वापस 0;
	पूर्ण

	sh_pfc_क्रमागतs[sh_pfc_num_क्रमागतs++] = क्रमागत_id;
	वापस 0;
पूर्ण

अटल व्योम __init sh_pfc_check_reg_क्रमागतs(स्थिर अक्षर *drvname, u32 reg,
					  स्थिर u16 *क्रमागतs, अचिन्हित पूर्णांक n)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < n; i++) अणु
		अगर (क्रमागतs[i] && sh_pfc_check_क्रमागत(drvname, क्रमागतs[i]))
			sh_pfc_err("reg 0x%x enum_id %u conflict\n", reg,
				   क्रमागतs[i]);
	पूर्ण
पूर्ण

अटल व्योम __init sh_pfc_check_pin(स्थिर काष्ठा sh_pfc_soc_info *info,
				    u32 reg, अचिन्हित पूर्णांक pin)
अणु
	स्थिर अक्षर *drvname = info->name;
	अचिन्हित पूर्णांक i;

	अगर (pin == SH_PFC_PIN_NONE)
		वापस;

	क्रम (i = 0; i < info->nr_pins; i++) अणु
		अगर (pin == info->pins[i].pin)
			वापस;
	पूर्ण

	sh_pfc_err("reg 0x%x: pin %u not found\n", reg, pin);
पूर्ण

अटल व्योम __init sh_pfc_check_cfg_reg(स्थिर अक्षर *drvname,
					स्थिर काष्ठा pinmux_cfg_reg *cfg_reg)
अणु
	अचिन्हित पूर्णांक i, n, rw, fw;

	sh_pfc_check_reg(drvname, cfg_reg->reg);

	अगर (cfg_reg->field_width) अणु
		n = cfg_reg->reg_width / cfg_reg->field_width;
		/* Skip field checks (करोne at build समय) */
		जाओ check_क्रमागत_ids;
	पूर्ण

	क्रम (i = 0, n = 0, rw = 0; (fw = cfg_reg->var_field_width[i]); i++) अणु
		अगर (fw > 3 && is0s(&cfg_reg->क्रमागत_ids[n], 1 << fw))
			sh_pfc_warn("reg 0x%x: reserved field [%u:%u] can be split to reduce table size\n",
				    cfg_reg->reg, rw, rw + fw - 1);
		n += 1 << fw;
		rw += fw;
	पूर्ण

	अगर (rw != cfg_reg->reg_width)
		sh_pfc_err("reg 0x%x: var_field_width declares %u instead of %u bits\n",
			   cfg_reg->reg, rw, cfg_reg->reg_width);

	अगर (n != cfg_reg->nr_क्रमागत_ids)
		sh_pfc_err("reg 0x%x: enum_ids[] has %u instead of %u values\n",
			   cfg_reg->reg, cfg_reg->nr_क्रमागत_ids, n);

check_क्रमागत_ids:
	sh_pfc_check_reg_क्रमागतs(drvname, cfg_reg->reg, cfg_reg->क्रमागत_ids, n);
पूर्ण

अटल व्योम __init sh_pfc_check_drive_reg(स्थिर काष्ठा sh_pfc_soc_info *info,
					  स्थिर काष्ठा pinmux_drive_reg *drive)
अणु
	स्थिर अक्षर *drvname = info->name;
	अचिन्हित दीर्घ seen = 0, mask;
	अचिन्हित पूर्णांक i;

	sh_pfc_check_reg(info->name, drive->reg);
	क्रम (i = 0; i < ARRAY_SIZE(drive->fields); i++) अणु
		स्थिर काष्ठा pinmux_drive_reg_field *field = &drive->fields[i];

		अगर (!field->pin && !field->offset && !field->size)
			जारी;

		mask = GENMASK(field->offset + field->size, field->offset);
		अगर (mask & seen)
			sh_pfc_err("drive_reg 0x%x: field %u overlap\n",
				   drive->reg, i);
		seen |= mask;

		sh_pfc_check_pin(info, drive->reg, field->pin);
	पूर्ण
पूर्ण

अटल व्योम __init sh_pfc_check_bias_reg(स्थिर काष्ठा sh_pfc_soc_info *info,
					 स्थिर काष्ठा pinmux_bias_reg *bias)
अणु
	अचिन्हित पूर्णांक i;

	sh_pfc_check_reg(info->name, bias->puen);
	अगर (bias->pud)
		sh_pfc_check_reg(info->name, bias->pud);
	क्रम (i = 0; i < ARRAY_SIZE(bias->pins); i++)
		sh_pfc_check_pin(info, bias->puen, bias->pins[i]);
पूर्ण

अटल व्योम __init sh_pfc_check_info(स्थिर काष्ठा sh_pfc_soc_info *info)
अणु
	स्थिर अक्षर *drvname = info->name;
	अचिन्हित पूर्णांक *refcnts;
	अचिन्हित पूर्णांक i, j, k;

	pr_info("Checking %s\n", drvname);
	sh_pfc_num_regs = 0;
	sh_pfc_num_क्रमागतs = 0;

	/* Check pins */
	क्रम (i = 0; i < info->nr_pins; i++) अणु
		स्थिर काष्ठा sh_pfc_pin *pin = &info->pins[i];

		अगर (!pin->name) अणु
			sh_pfc_err("empty pin %u\n", i);
			जारी;
		पूर्ण
		क्रम (j = 0; j < i; j++) अणु
			स्थिर काष्ठा sh_pfc_pin *pin2 = &info->pins[j];

			अगर (same_name(pin->name, pin2->name))
				sh_pfc_err("pin %s: name conflict\n",
					   pin->name);

			अगर (pin->pin != (u16)-1 && pin->pin == pin2->pin)
				sh_pfc_err("pin %s/%s: pin %u conflict\n",
					   pin->name, pin2->name, pin->pin);

			अगर (pin->क्रमागत_id && pin->क्रमागत_id == pin2->क्रमागत_id)
				sh_pfc_err("pin %s/%s: enum_id %u conflict\n",
					   pin->name, pin2->name,
					   pin->क्रमागत_id);
		पूर्ण
	पूर्ण

	/* Check groups and functions */
	refcnts = kसुस्मृति(info->nr_groups, माप(*refcnts), GFP_KERNEL);
	अगर (!refcnts)
		वापस;

	क्रम (i = 0; i < info->nr_functions; i++) अणु
		स्थिर काष्ठा sh_pfc_function *func = &info->functions[i];

		अगर (!func->name) अणु
			sh_pfc_err("empty function %u\n", i);
			जारी;
		पूर्ण
		क्रम (j = 0; j < i; j++) अणु
			अगर (same_name(func->name, info->functions[j].name))
				sh_pfc_err("function %s: name conflict\n",
					   func->name);
		पूर्ण
		क्रम (j = 0; j < func->nr_groups; j++) अणु
			क्रम (k = 0; k < info->nr_groups; k++) अणु
				अगर (same_name(func->groups[j],
					      info->groups[k].name)) अणु
					refcnts[k]++;
					अवरोध;
				पूर्ण
			पूर्ण

			अगर (k == info->nr_groups)
				sh_pfc_err("function %s: group %s not found\n",
					   func->name, func->groups[j]);
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < info->nr_groups; i++) अणु
		स्थिर काष्ठा sh_pfc_pin_group *group = &info->groups[i];

		अगर (!group->name) अणु
			sh_pfc_err("empty group %u\n", i);
			जारी;
		पूर्ण
		क्रम (j = 0; j < i; j++) अणु
			अगर (same_name(group->name, info->groups[j].name))
				sh_pfc_err("group %s: name conflict\n",
					   group->name);
		पूर्ण
		अगर (!refcnts[i])
			sh_pfc_err("orphan group %s\n", group->name);
		अन्यथा अगर (refcnts[i] > 1)
			sh_pfc_warn("group %s referenced by %u functions\n",
				    group->name, refcnts[i]);
	पूर्ण

	kमुक्त(refcnts);

	/* Check config रेजिस्टर descriptions */
	क्रम (i = 0; info->cfg_regs && info->cfg_regs[i].reg; i++)
		sh_pfc_check_cfg_reg(drvname, &info->cfg_regs[i]);

	/* Check drive strength रेजिस्टरs */
	क्रम (i = 0; info->drive_regs && info->drive_regs[i].reg; i++)
		sh_pfc_check_drive_reg(info, &info->drive_regs[i]);

	/* Check bias रेजिस्टरs */
	क्रम (i = 0; info->bias_regs && info->bias_regs[i].puen; i++)
		sh_pfc_check_bias_reg(info, &info->bias_regs[i]);

	/* Check ioctrl रेजिस्टरs */
	क्रम (i = 0; info->ioctrl_regs && info->ioctrl_regs[i].reg; i++)
		sh_pfc_check_reg(drvname, info->ioctrl_regs[i].reg);

	/* Check data रेजिस्टरs */
	क्रम (i = 0; info->data_regs && info->data_regs[i].reg; i++) अणु
		sh_pfc_check_reg(drvname, info->data_regs[i].reg);
		sh_pfc_check_reg_क्रमागतs(drvname, info->data_regs[i].reg,
				       info->data_regs[i].क्रमागत_ids,
				       info->data_regs[i].reg_width);
	पूर्ण

#अगर_घोषित CONFIG_PINCTRL_SH_FUNC_GPIO
	/* Check function GPIOs */
	क्रम (i = 0; i < info->nr_func_gpios; i++) अणु
		स्थिर काष्ठा pinmux_func *func = &info->func_gpios[i];

		अगर (!func->name) अणु
			sh_pfc_err("empty function gpio %u\n", i);
			जारी;
		पूर्ण
		क्रम (j = 0; j < i; j++) अणु
			अगर (same_name(func->name, info->func_gpios[j].name))
				sh_pfc_err("func_gpio %s: name conflict\n",
					   func->name);
		पूर्ण
		अगर (sh_pfc_check_क्रमागत(drvname, func->क्रमागत_id))
			sh_pfc_err("%s enum_id %u conflict\n", func->name,
				   func->क्रमागत_id);
	पूर्ण
#पूर्ण_अगर
पूर्ण

अटल व्योम __init sh_pfc_check_driver(स्थिर काष्ठा platक्रमm_driver *pdrv)
अणु
	अचिन्हित पूर्णांक i;

	अगर (!IS_ENABLED(CONFIG_SUPERH) &&
	    !of_find_matching_node(शून्य, pdrv->driver.of_match_table))
		वापस;

	sh_pfc_regs = kसुस्मृति(SH_PFC_MAX_REGS, माप(*sh_pfc_regs),
			      GFP_KERNEL);
	अगर (!sh_pfc_regs)
		वापस;

	sh_pfc_क्रमागतs = kसुस्मृति(SH_PFC_MAX_ENUMS, माप(*sh_pfc_क्रमागतs),
			      GFP_KERNEL);
	अगर (!sh_pfc_क्रमागतs)
		जाओ मुक्त_regs;

	pr_warn("Checking builtin pinmux tables\n");

	क्रम (i = 0; pdrv->id_table[i].name[0]; i++)
		sh_pfc_check_info((व्योम *)pdrv->id_table[i].driver_data);

#अगर_घोषित CONFIG_OF
	क्रम (i = 0; pdrv->driver.of_match_table[i].compatible[0]; i++)
		sh_pfc_check_info(pdrv->driver.of_match_table[i].data);
#पूर्ण_अगर

	pr_warn("Detected %u errors and %u warnings\n", sh_pfc_errors,
		sh_pfc_warnings);

	kमुक्त(sh_pfc_क्रमागतs);
मुक्त_regs:
	kमुक्त(sh_pfc_regs);
पूर्ण

#अन्यथा /* !DEBUG */
अटल अंतरभूत व्योम sh_pfc_check_driver(काष्ठा platक्रमm_driver *pdrv) अणुपूर्ण
#पूर्ण_अगर /* !DEBUG */

#अगर_घोषित CONFIG_OF
अटल स्थिर व्योम *sh_pfc_quirk_match(व्योम)
अणु
#अगर defined(CONFIG_PINCTRL_PFC_R8A77950) || \
    defined(CONFIG_PINCTRL_PFC_R8A77951)
	स्थिर काष्ठा soc_device_attribute *match;
	अटल स्थिर काष्ठा soc_device_attribute quirks[] = अणु
		अणु
			.soc_id = "r8a7795", .revision = "ES1.*",
			.data = &r8a77950_pinmux_info,
		पूर्ण,
		अणु
			.soc_id = "r8a7795",
			.data = &r8a77951_pinmux_info,
		पूर्ण,

		अणु /* sentinel */ पूर्ण
	पूर्ण;

	match = soc_device_match(quirks);
	अगर (match)
		वापस match->data ?: ERR_PTR(-ENODEV);
#पूर्ण_अगर /* CONFIG_PINCTRL_PFC_R8A77950 || CONFIG_PINCTRL_PFC_R8A77951 */

	वापस शून्य;
पूर्ण
#पूर्ण_अगर /* CONFIG_OF */

अटल पूर्णांक sh_pfc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा sh_pfc_soc_info *info;
	काष्ठा sh_pfc *pfc;
	पूर्णांक ret;

#अगर_घोषित CONFIG_OF
	अगर (pdev->dev.of_node) अणु
		info = sh_pfc_quirk_match();
		अगर (IS_ERR(info))
			वापस PTR_ERR(info);

		अगर (!info)
			info = of_device_get_match_data(&pdev->dev);
	पूर्ण अन्यथा
#पूर्ण_अगर
		info = (स्थिर व्योम *)platक्रमm_get_device_id(pdev)->driver_data;

	pfc = devm_kzalloc(&pdev->dev, माप(*pfc), GFP_KERNEL);
	अगर (pfc == शून्य)
		वापस -ENOMEM;

	pfc->info = info;
	pfc->dev = &pdev->dev;

	ret = sh_pfc_map_resources(pfc, pdev);
	अगर (unlikely(ret < 0))
		वापस ret;

	spin_lock_init(&pfc->lock);

	अगर (info->ops && info->ops->init) अणु
		ret = info->ops->init(pfc);
		अगर (ret < 0)
			वापस ret;

		/* .init() may have overridden pfc->info */
		info = pfc->info;
	पूर्ण

	ret = sh_pfc_suspend_init(pfc);
	अगर (ret)
		वापस ret;

	/* Enable dummy states क्रम those platक्रमms without pinctrl support */
	अगर (!of_have_populated_dt())
		pinctrl_provide_dummies();

	ret = sh_pfc_init_ranges(pfc);
	अगर (ret < 0)
		वापस ret;

	/*
	 * Initialize pinctrl bindings first
	 */
	ret = sh_pfc_रेजिस्टर_pinctrl(pfc);
	अगर (unlikely(ret != 0))
		वापस ret;

#अगर_घोषित CONFIG_PINCTRL_SH_PFC_GPIO
	/*
	 * Then the GPIO chip
	 */
	ret = sh_pfc_रेजिस्टर_gpiochip(pfc);
	अगर (unlikely(ret != 0)) अणु
		/*
		 * If the GPIO chip fails to come up we still leave the
		 * PFC state as it is, given that there are alपढ़ोy
		 * extant users of it that have succeeded by this poपूर्णांक.
		 */
		dev_notice(pfc->dev, "failed to init GPIO chip, ignoring...\n");
	पूर्ण
#पूर्ण_अगर

	platक्रमm_set_drvdata(pdev, pfc);

	dev_info(pfc->dev, "%s support registered\n", info->name);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा platक्रमm_device_id sh_pfc_id_table[] = अणु
#अगर_घोषित CONFIG_PINCTRL_PFC_SH7203
	अणु "pfc-sh7203", (kernel_uदीर्घ_t)&sh7203_pinmux_info पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_PINCTRL_PFC_SH7264
	अणु "pfc-sh7264", (kernel_uदीर्घ_t)&sh7264_pinmux_info पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_PINCTRL_PFC_SH7269
	अणु "pfc-sh7269", (kernel_uदीर्घ_t)&sh7269_pinmux_info पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_PINCTRL_PFC_SH7720
	अणु "pfc-sh7720", (kernel_uदीर्घ_t)&sh7720_pinmux_info पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_PINCTRL_PFC_SH7722
	अणु "pfc-sh7722", (kernel_uदीर्घ_t)&sh7722_pinmux_info पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_PINCTRL_PFC_SH7723
	अणु "pfc-sh7723", (kernel_uदीर्घ_t)&sh7723_pinmux_info पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_PINCTRL_PFC_SH7724
	अणु "pfc-sh7724", (kernel_uदीर्घ_t)&sh7724_pinmux_info पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_PINCTRL_PFC_SH7734
	अणु "pfc-sh7734", (kernel_uदीर्घ_t)&sh7734_pinmux_info पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_PINCTRL_PFC_SH7757
	अणु "pfc-sh7757", (kernel_uदीर्घ_t)&sh7757_pinmux_info पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_PINCTRL_PFC_SH7785
	अणु "pfc-sh7785", (kernel_uदीर्घ_t)&sh7785_pinmux_info पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_PINCTRL_PFC_SH7786
	अणु "pfc-sh7786", (kernel_uदीर्घ_t)&sh7786_pinmux_info पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_PINCTRL_PFC_SHX3
	अणु "pfc-shx3", (kernel_uदीर्घ_t)&shx3_pinmux_info पूर्ण,
#पूर्ण_अगर
	अणु पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver sh_pfc_driver = अणु
	.probe		= sh_pfc_probe,
	.id_table	= sh_pfc_id_table,
	.driver		= अणु
		.name	= DRV_NAME,
		.of_match_table = of_match_ptr(sh_pfc_of_table),
		.pm     = DEV_PM_OPS,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init sh_pfc_init(व्योम)
अणु
	sh_pfc_check_driver(&sh_pfc_driver);
	वापस platक्रमm_driver_रेजिस्टर(&sh_pfc_driver);
पूर्ण
postcore_initcall(sh_pfc_init);
