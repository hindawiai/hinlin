<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Clock driver क्रम Keystone 2 based devices
 *
 * Copyright (C) 2013 Texas Instruments.
 *	Murali Karicheri <m-karicheri2@ti.com>
 *	Santosh Shilimkar <santosh.shilimkar@ti.com>
 */
#समावेश <linux/clk-provider.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/slab.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of.h>
#समावेश <linux/module.h>

/* PSC रेजिस्टर offsets */
#घोषणा PTCMD			0x120
#घोषणा PTSTAT			0x128
#घोषणा PDSTAT			0x200
#घोषणा PDCTL			0x300
#घोषणा MDSTAT			0x800
#घोषणा MDCTL			0xa00

/* PSC module states */
#घोषणा PSC_STATE_SWRSTDISABLE	0
#घोषणा PSC_STATE_SYNCRST	1
#घोषणा PSC_STATE_DISABLE	2
#घोषणा PSC_STATE_ENABLE	3

#घोषणा MDSTAT_STATE_MASK	0x3f
#घोषणा MDSTAT_MCKOUT		BIT(12)
#घोषणा PDSTAT_STATE_MASK	0x1f
#घोषणा MDCTL_FORCE		BIT(31)
#घोषणा MDCTL_LRESET		BIT(8)
#घोषणा PDCTL_NEXT		BIT(0)

/* Maximum समयout to bail out state transition क्रम module */
#घोषणा STATE_TRANS_MAX_COUNT	0xffff

अटल व्योम __iomem *करोमुख्य_transition_base;

/**
 * काष्ठा clk_psc_data - PSC data
 * @control_base: Base address क्रम a PSC control
 * @करोमुख्य_base: Base address क्रम a PSC करोमुख्य
 * @करोमुख्य_id: PSC करोमुख्य id number
 */
काष्ठा clk_psc_data अणु
	व्योम __iomem *control_base;
	व्योम __iomem *करोमुख्य_base;
	u32 करोमुख्य_id;
पूर्ण;

/**
 * काष्ठा clk_psc - PSC घड़ी काष्ठाure
 * @hw: clk_hw क्रम the psc
 * @psc_data: PSC driver specअगरic data
 * @lock: Spinlock used by the driver
 */
काष्ठा clk_psc अणु
	काष्ठा clk_hw hw;
	काष्ठा clk_psc_data *psc_data;
	spinlock_t *lock;
पूर्ण;

अटल DEFINE_SPINLOCK(psc_lock);

#घोषणा to_clk_psc(_hw) container_of(_hw, काष्ठा clk_psc, hw)

अटल व्योम psc_config(व्योम __iomem *control_base, व्योम __iomem *करोमुख्य_base,
						u32 next_state, u32 करोमुख्य_id)
अणु
	u32 ptcmd, pdstat, pdctl, mdstat, mdctl, ptstat;
	u32 count = STATE_TRANS_MAX_COUNT;

	mdctl = पढ़ोl(control_base + MDCTL);
	mdctl &= ~MDSTAT_STATE_MASK;
	mdctl |= next_state;
	/* For disable, we always put the module in local reset */
	अगर (next_state == PSC_STATE_DISABLE)
		mdctl &= ~MDCTL_LRESET;
	ग_लिखोl(mdctl, control_base + MDCTL);

	pdstat = पढ़ोl(करोमुख्य_base + PDSTAT);
	अगर (!(pdstat & PDSTAT_STATE_MASK)) अणु
		pdctl = पढ़ोl(करोमुख्य_base + PDCTL);
		pdctl |= PDCTL_NEXT;
		ग_लिखोl(pdctl, करोमुख्य_base + PDCTL);
	पूर्ण

	ptcmd = 1 << करोमुख्य_id;
	ग_लिखोl(ptcmd, करोमुख्य_transition_base + PTCMD);
	करो अणु
		ptstat = पढ़ोl(करोमुख्य_transition_base + PTSTAT);
	पूर्ण जबतक (((ptstat >> करोमुख्य_id) & 1) && count--);

	count = STATE_TRANS_MAX_COUNT;
	करो अणु
		mdstat = पढ़ोl(control_base + MDSTAT);
	पूर्ण जबतक (!((mdstat & MDSTAT_STATE_MASK) == next_state) && count--);
पूर्ण

अटल पूर्णांक keystone_clk_is_enabled(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_psc *psc = to_clk_psc(hw);
	काष्ठा clk_psc_data *data = psc->psc_data;
	u32 mdstat = पढ़ोl(data->control_base + MDSTAT);

	वापस (mdstat & MDSTAT_MCKOUT) ? 1 : 0;
पूर्ण

अटल पूर्णांक keystone_clk_enable(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_psc *psc = to_clk_psc(hw);
	काष्ठा clk_psc_data *data = psc->psc_data;
	अचिन्हित दीर्घ flags = 0;

	अगर (psc->lock)
		spin_lock_irqsave(psc->lock, flags);

	psc_config(data->control_base, data->करोमुख्य_base,
				PSC_STATE_ENABLE, data->करोमुख्य_id);

	अगर (psc->lock)
		spin_unlock_irqrestore(psc->lock, flags);

	वापस 0;
पूर्ण

अटल व्योम keystone_clk_disable(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_psc *psc = to_clk_psc(hw);
	काष्ठा clk_psc_data *data = psc->psc_data;
	अचिन्हित दीर्घ flags = 0;

	अगर (psc->lock)
		spin_lock_irqsave(psc->lock, flags);

	psc_config(data->control_base, data->करोमुख्य_base,
				PSC_STATE_DISABLE, data->करोमुख्य_id);

	अगर (psc->lock)
		spin_unlock_irqrestore(psc->lock, flags);
पूर्ण

अटल स्थिर काष्ठा clk_ops clk_psc_ops = अणु
	.enable = keystone_clk_enable,
	.disable = keystone_clk_disable,
	.is_enabled = keystone_clk_is_enabled,
पूर्ण;

/**
 * clk_रेजिस्टर_psc - रेजिस्टर psc घड़ी
 * @dev: device that is रेजिस्टरing this घड़ी
 * @name: name of this घड़ी
 * @parent_name: name of घड़ी's parent
 * @psc_data: platक्रमm data to configure this घड़ी
 * @lock: spinlock used by this घड़ी
 */
अटल काष्ठा clk *clk_रेजिस्टर_psc(काष्ठा device *dev,
			स्थिर अक्षर *name,
			स्थिर अक्षर *parent_name,
			काष्ठा clk_psc_data *psc_data,
			spinlock_t *lock)
अणु
	काष्ठा clk_init_data init;
	काष्ठा clk_psc *psc;
	काष्ठा clk *clk;

	psc = kzalloc(माप(*psc), GFP_KERNEL);
	अगर (!psc)
		वापस ERR_PTR(-ENOMEM);

	init.name = name;
	init.ops = &clk_psc_ops;
	init.flags = 0;
	init.parent_names = (parent_name ? &parent_name : शून्य);
	init.num_parents = (parent_name ? 1 : 0);

	psc->psc_data = psc_data;
	psc->lock = lock;
	psc->hw.init = &init;

	clk = clk_रेजिस्टर(शून्य, &psc->hw);
	अगर (IS_ERR(clk))
		kमुक्त(psc);

	वापस clk;
पूर्ण

/**
 * of_psc_clk_init - initialize psc घड़ी through DT
 * @node: device tree node क्रम this घड़ी
 * @lock: spinlock used by this घड़ी
 */
अटल व्योम __init of_psc_clk_init(काष्ठा device_node *node, spinlock_t *lock)
अणु
	स्थिर अक्षर *clk_name = node->name;
	स्थिर अक्षर *parent_name;
	काष्ठा clk_psc_data *data;
	काष्ठा clk *clk;
	पूर्णांक i;

	data = kzalloc(माप(*data), GFP_KERNEL);
	अगर (!data) अणु
		pr_err("%s: Out of memory\n", __func__);
		वापस;
	पूर्ण

	i = of_property_match_string(node, "reg-names", "control");
	data->control_base = of_iomap(node, i);
	अगर (!data->control_base) अणु
		pr_err("%s: control ioremap failed\n", __func__);
		जाओ out;
	पूर्ण

	i = of_property_match_string(node, "reg-names", "domain");
	data->करोमुख्य_base = of_iomap(node, i);
	अगर (!data->करोमुख्य_base) अणु
		pr_err("%s: domain ioremap failed\n", __func__);
		जाओ unmap_ctrl;
	पूर्ण

	of_property_पढ़ो_u32(node, "domain-id", &data->करोमुख्य_id);

	/* Doमुख्य transition रेजिस्टरs at fixed address space of करोमुख्य_id 0 */
	अगर (!करोमुख्य_transition_base && !data->करोमुख्य_id)
		करोमुख्य_transition_base = data->करोमुख्य_base;

	of_property_पढ़ो_string(node, "clock-output-names", &clk_name);
	parent_name = of_clk_get_parent_name(node, 0);
	अगर (!parent_name) अणु
		pr_err("%s: Parent clock not found\n", __func__);
		जाओ unmap_करोमुख्य;
	पूर्ण

	clk = clk_रेजिस्टर_psc(शून्य, clk_name, parent_name, data, lock);
	अगर (!IS_ERR(clk)) अणु
		of_clk_add_provider(node, of_clk_src_simple_get, clk);
		वापस;
	पूर्ण

	pr_err("%s: error registering clk %pOFn\n", __func__, node);

unmap_करोमुख्य:
	iounmap(data->करोमुख्य_base);
unmap_ctrl:
	iounmap(data->control_base);
out:
	kमुक्त(data);
	वापस;
पूर्ण

/**
 * of_keystone_psc_clk_init - initialize psc घड़ी through DT
 * @node: device tree node क्रम this घड़ी
 */
अटल व्योम __init of_keystone_psc_clk_init(काष्ठा device_node *node)
अणु
	of_psc_clk_init(node, &psc_lock);
पूर्ण
CLK_OF_DECLARE(keystone_gate_clk, "ti,keystone,psc-clock",
					of_keystone_psc_clk_init);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Clock driver for Keystone 2 based devices");
MODULE_AUTHOR("Murali Karicheri <m-karicheri2@ti.com>");
MODULE_AUTHOR("Santosh Shilimkar <santosh.shilimkar@ti.com>");
