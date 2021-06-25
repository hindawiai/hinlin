<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Intel pinctrl/GPIO core driver.
 *
 * Copyright (C) 2015, Intel Corporation
 * Authors: Mathias Nyman <mathias.nyman@linux.पूर्णांकel.com>
 *          Mika Westerberg <mika.westerberg@linux.पूर्णांकel.com>
 */

#समावेश <linux/acpi.h>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/log2.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/property.h>
#समावेश <linux/समय.स>

#समावेश <linux/pinctrl/pinctrl.h>
#समावेश <linux/pinctrl/pinmux.h>
#समावेश <linux/pinctrl/pinconf.h>
#समावेश <linux/pinctrl/pinconf-generic.h>

#समावेश "../core.h"
#समावेश "pinctrl-intel.h"

/* Offset from regs */
#घोषणा REVID				0x000
#घोषणा REVID_SHIFT			16
#घोषणा REVID_MASK			GENMASK(31, 16)

#घोषणा CAPLIST				0x004
#घोषणा CAPLIST_ID_SHIFT		16
#घोषणा CAPLIST_ID_MASK			GENMASK(23, 16)
#घोषणा CAPLIST_ID_GPIO_HW_INFO		1
#घोषणा CAPLIST_ID_PWM			2
#घोषणा CAPLIST_ID_BLINK		3
#घोषणा CAPLIST_ID_EXP			4
#घोषणा CAPLIST_NEXT_SHIFT		0
#घोषणा CAPLIST_NEXT_MASK		GENMASK(15, 0)

#घोषणा PADBAR				0x00c

#घोषणा PADOWN_BITS			4
#घोषणा PADOWN_SHIFT(p)			((p) % 8 * PADOWN_BITS)
#घोषणा PADOWN_MASK(p)			(GENMASK(3, 0) << PADOWN_SHIFT(p))
#घोषणा PADOWN_GPP(p)			((p) / 8)

/* Offset from pad_regs */
#घोषणा PADCFG0				0x000
#घोषणा PADCFG0_RXEVCFG_SHIFT		25
#घोषणा PADCFG0_RXEVCFG_MASK		GENMASK(26, 25)
#घोषणा PADCFG0_RXEVCFG_LEVEL		0
#घोषणा PADCFG0_RXEVCFG_EDGE		1
#घोषणा PADCFG0_RXEVCFG_DISABLED	2
#घोषणा PADCFG0_RXEVCFG_EDGE_BOTH	3
#घोषणा PADCFG0_PREGFRXSEL		BIT(24)
#घोषणा PADCFG0_RXINV			BIT(23)
#घोषणा PADCFG0_GPIROUTIOXAPIC		BIT(20)
#घोषणा PADCFG0_GPIROUTSCI		BIT(19)
#घोषणा PADCFG0_GPIROUTSMI		BIT(18)
#घोषणा PADCFG0_GPIROUTNMI		BIT(17)
#घोषणा PADCFG0_PMODE_SHIFT		10
#घोषणा PADCFG0_PMODE_MASK		GENMASK(13, 10)
#घोषणा PADCFG0_PMODE_GPIO		0
#घोषणा PADCFG0_GPIORXDIS		BIT(9)
#घोषणा PADCFG0_GPIOTXDIS		BIT(8)
#घोषणा PADCFG0_GPIORXSTATE		BIT(1)
#घोषणा PADCFG0_GPIOTXSTATE		BIT(0)

#घोषणा PADCFG1				0x004
#घोषणा PADCFG1_TERM_UP			BIT(13)
#घोषणा PADCFG1_TERM_SHIFT		10
#घोषणा PADCFG1_TERM_MASK		GENMASK(12, 10)
#घोषणा PADCFG1_TERM_20K		BIT(2)
#घोषणा PADCFG1_TERM_5K			BIT(1)
#घोषणा PADCFG1_TERM_1K			BIT(0)
#घोषणा PADCFG1_TERM_833		(BIT(1) | BIT(0))

#घोषणा PADCFG2				0x008
#घोषणा PADCFG2_DEBEN			BIT(0)
#घोषणा PADCFG2_DEBOUNCE_SHIFT		1
#घोषणा PADCFG2_DEBOUNCE_MASK		GENMASK(4, 1)

#घोषणा DEBOUNCE_PERIOD_NSEC		31250

काष्ठा पूर्णांकel_pad_context अणु
	u32 padcfg0;
	u32 padcfg1;
	u32 padcfg2;
पूर्ण;

काष्ठा पूर्णांकel_community_context अणु
	u32 *पूर्णांकmask;
	u32 *hostown;
पूर्ण;

#घोषणा pin_to_padno(c, p)	((p) - (c)->pin_base)
#घोषणा padgroup_offset(g, p)	((p) - (g)->base)

अटल काष्ठा पूर्णांकel_community *पूर्णांकel_get_community(काष्ठा पूर्णांकel_pinctrl *pctrl,
						   अचिन्हित पूर्णांक pin)
अणु
	काष्ठा पूर्णांकel_community *community;
	पूर्णांक i;

	क्रम (i = 0; i < pctrl->ncommunities; i++) अणु
		community = &pctrl->communities[i];
		अगर (pin >= community->pin_base &&
		    pin < community->pin_base + community->npins)
			वापस community;
	पूर्ण

	dev_warn(pctrl->dev, "failed to find community for pin %u\n", pin);
	वापस शून्य;
पूर्ण

अटल स्थिर काष्ठा पूर्णांकel_padgroup *
पूर्णांकel_community_get_padgroup(स्थिर काष्ठा पूर्णांकel_community *community,
			     अचिन्हित पूर्णांक pin)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < community->ngpps; i++) अणु
		स्थिर काष्ठा पूर्णांकel_padgroup *padgrp = &community->gpps[i];

		अगर (pin >= padgrp->base && pin < padgrp->base + padgrp->size)
			वापस padgrp;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल व्योम __iomem *पूर्णांकel_get_padcfg(काष्ठा पूर्णांकel_pinctrl *pctrl,
				      अचिन्हित पूर्णांक pin, अचिन्हित पूर्णांक reg)
अणु
	स्थिर काष्ठा पूर्णांकel_community *community;
	अचिन्हित पूर्णांक padno;
	माप_प्रकार nregs;

	community = पूर्णांकel_get_community(pctrl, pin);
	अगर (!community)
		वापस शून्य;

	padno = pin_to_padno(community, pin);
	nregs = (community->features & PINCTRL_FEATURE_DEBOUNCE) ? 4 : 2;

	अगर (reg >= nregs * 4)
		वापस शून्य;

	वापस community->pad_regs + reg + padno * nregs * 4;
पूर्ण

अटल bool पूर्णांकel_pad_owned_by_host(काष्ठा पूर्णांकel_pinctrl *pctrl, अचिन्हित पूर्णांक pin)
अणु
	स्थिर काष्ठा पूर्णांकel_community *community;
	स्थिर काष्ठा पूर्णांकel_padgroup *padgrp;
	अचिन्हित पूर्णांक gpp, offset, gpp_offset;
	व्योम __iomem *paकरोwn;

	community = पूर्णांकel_get_community(pctrl, pin);
	अगर (!community)
		वापस false;
	अगर (!community->paकरोwn_offset)
		वापस true;

	padgrp = पूर्णांकel_community_get_padgroup(community, pin);
	अगर (!padgrp)
		वापस false;

	gpp_offset = padgroup_offset(padgrp, pin);
	gpp = PADOWN_GPP(gpp_offset);
	offset = community->paकरोwn_offset + padgrp->paकरोwn_num * 4 + gpp * 4;
	paकरोwn = community->regs + offset;

	वापस !(पढ़ोl(paकरोwn) & PADOWN_MASK(gpp_offset));
पूर्ण

अटल bool पूर्णांकel_pad_acpi_mode(काष्ठा पूर्णांकel_pinctrl *pctrl, अचिन्हित पूर्णांक pin)
अणु
	स्थिर काष्ठा पूर्णांकel_community *community;
	स्थिर काष्ठा पूर्णांकel_padgroup *padgrp;
	अचिन्हित पूर्णांक offset, gpp_offset;
	व्योम __iomem *hostown;

	community = पूर्णांकel_get_community(pctrl, pin);
	अगर (!community)
		वापस true;
	अगर (!community->hostown_offset)
		वापस false;

	padgrp = पूर्णांकel_community_get_padgroup(community, pin);
	अगर (!padgrp)
		वापस true;

	gpp_offset = padgroup_offset(padgrp, pin);
	offset = community->hostown_offset + padgrp->reg_num * 4;
	hostown = community->regs + offset;

	वापस !(पढ़ोl(hostown) & BIT(gpp_offset));
पूर्ण

/**
 * क्रमागत - Locking variants of the pad configuration
 *
 * @PAD_UNLOCKED:	pad is fully controlled by the configuration रेजिस्टरs
 * @PAD_LOCKED:		pad configuration रेजिस्टरs, except TX state, are locked
 * @PAD_LOCKED_TX:	pad configuration TX state is locked
 * @PAD_LOCKED_FULL:	pad configuration रेजिस्टरs are locked completely
 *
 * Locking is considered as पढ़ो-only mode क्रम corresponding रेजिस्टरs and
 * their respective fields. That said, TX state bit is locked separately from
 * the मुख्य locking scheme.
 */
क्रमागत अणु
	PAD_UNLOCKED	= 0,
	PAD_LOCKED	= 1,
	PAD_LOCKED_TX	= 2,
	PAD_LOCKED_FULL	= PAD_LOCKED | PAD_LOCKED_TX,
पूर्ण;

अटल पूर्णांक पूर्णांकel_pad_locked(काष्ठा पूर्णांकel_pinctrl *pctrl, अचिन्हित पूर्णांक pin)
अणु
	काष्ठा पूर्णांकel_community *community;
	स्थिर काष्ठा पूर्णांकel_padgroup *padgrp;
	अचिन्हित पूर्णांक offset, gpp_offset;
	u32 value;
	पूर्णांक ret = PAD_UNLOCKED;

	community = पूर्णांकel_get_community(pctrl, pin);
	अगर (!community)
		वापस PAD_LOCKED_FULL;
	अगर (!community->padcfglock_offset)
		वापस PAD_UNLOCKED;

	padgrp = पूर्णांकel_community_get_padgroup(community, pin);
	अगर (!padgrp)
		वापस PAD_LOCKED_FULL;

	gpp_offset = padgroup_offset(padgrp, pin);

	/*
	 * If PADCFGLOCK and PADCFGLOCKTX bits are both clear क्रम this pad,
	 * the pad is considered unlocked. Any other हाल means that it is
	 * either fully or partially locked.
	 */
	offset = community->padcfglock_offset + 0 + padgrp->reg_num * 8;
	value = पढ़ोl(community->regs + offset);
	अगर (value & BIT(gpp_offset))
		ret |= PAD_LOCKED;

	offset = community->padcfglock_offset + 4 + padgrp->reg_num * 8;
	value = पढ़ोl(community->regs + offset);
	अगर (value & BIT(gpp_offset))
		ret |= PAD_LOCKED_TX;

	वापस ret;
पूर्ण

अटल bool पूर्णांकel_pad_is_unlocked(काष्ठा पूर्णांकel_pinctrl *pctrl, अचिन्हित पूर्णांक pin)
अणु
	वापस (पूर्णांकel_pad_locked(pctrl, pin) & PAD_LOCKED) == PAD_UNLOCKED;
पूर्ण

अटल bool पूर्णांकel_pad_usable(काष्ठा पूर्णांकel_pinctrl *pctrl, अचिन्हित पूर्णांक pin)
अणु
	वापस पूर्णांकel_pad_owned_by_host(pctrl, pin) && पूर्णांकel_pad_is_unlocked(pctrl, pin);
पूर्ण

अटल पूर्णांक पूर्णांकel_get_groups_count(काष्ठा pinctrl_dev *pctldev)
अणु
	काष्ठा पूर्णांकel_pinctrl *pctrl = pinctrl_dev_get_drvdata(pctldev);

	वापस pctrl->soc->ngroups;
पूर्ण

अटल स्थिर अक्षर *पूर्णांकel_get_group_name(काष्ठा pinctrl_dev *pctldev,
				      अचिन्हित पूर्णांक group)
अणु
	काष्ठा पूर्णांकel_pinctrl *pctrl = pinctrl_dev_get_drvdata(pctldev);

	वापस pctrl->soc->groups[group].name;
पूर्ण

अटल पूर्णांक पूर्णांकel_get_group_pins(काष्ठा pinctrl_dev *pctldev, अचिन्हित पूर्णांक group,
			      स्थिर अचिन्हित पूर्णांक **pins, अचिन्हित पूर्णांक *npins)
अणु
	काष्ठा पूर्णांकel_pinctrl *pctrl = pinctrl_dev_get_drvdata(pctldev);

	*pins = pctrl->soc->groups[group].pins;
	*npins = pctrl->soc->groups[group].npins;
	वापस 0;
पूर्ण

अटल व्योम पूर्णांकel_pin_dbg_show(काष्ठा pinctrl_dev *pctldev, काष्ठा seq_file *s,
			       अचिन्हित पूर्णांक pin)
अणु
	काष्ठा पूर्णांकel_pinctrl *pctrl = pinctrl_dev_get_drvdata(pctldev);
	व्योम __iomem *padcfg;
	u32 cfg0, cfg1, mode;
	पूर्णांक locked;
	bool acpi;

	अगर (!पूर्णांकel_pad_owned_by_host(pctrl, pin)) अणु
		seq_माला_दो(s, "not available");
		वापस;
	पूर्ण

	cfg0 = पढ़ोl(पूर्णांकel_get_padcfg(pctrl, pin, PADCFG0));
	cfg1 = पढ़ोl(पूर्णांकel_get_padcfg(pctrl, pin, PADCFG1));

	mode = (cfg0 & PADCFG0_PMODE_MASK) >> PADCFG0_PMODE_SHIFT;
	अगर (mode == PADCFG0_PMODE_GPIO)
		seq_माला_दो(s, "GPIO ");
	अन्यथा
		seq_म_लिखो(s, "mode %d ", mode);

	seq_म_लिखो(s, "0x%08x 0x%08x", cfg0, cfg1);

	/* Dump the additional PADCFG रेजिस्टरs अगर available */
	padcfg = पूर्णांकel_get_padcfg(pctrl, pin, PADCFG2);
	अगर (padcfg)
		seq_म_लिखो(s, " 0x%08x", पढ़ोl(padcfg));

	locked = पूर्णांकel_pad_locked(pctrl, pin);
	acpi = पूर्णांकel_pad_acpi_mode(pctrl, pin);

	अगर (locked || acpi) अणु
		seq_माला_दो(s, " [");
		अगर (locked)
			seq_माला_दो(s, "LOCKED");
		अगर ((locked & PAD_LOCKED_FULL) == PAD_LOCKED_TX)
			seq_माला_दो(s, " tx");
		अन्यथा अगर ((locked & PAD_LOCKED_FULL) == PAD_LOCKED_FULL)
			seq_माला_दो(s, " full");

		अगर (locked && acpi)
			seq_माला_दो(s, ", ");

		अगर (acpi)
			seq_माला_दो(s, "ACPI");
		seq_माला_दो(s, "]");
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा pinctrl_ops पूर्णांकel_pinctrl_ops = अणु
	.get_groups_count = पूर्णांकel_get_groups_count,
	.get_group_name = पूर्णांकel_get_group_name,
	.get_group_pins = पूर्णांकel_get_group_pins,
	.pin_dbg_show = पूर्णांकel_pin_dbg_show,
पूर्ण;

अटल पूर्णांक पूर्णांकel_get_functions_count(काष्ठा pinctrl_dev *pctldev)
अणु
	काष्ठा पूर्णांकel_pinctrl *pctrl = pinctrl_dev_get_drvdata(pctldev);

	वापस pctrl->soc->nfunctions;
पूर्ण

अटल स्थिर अक्षर *पूर्णांकel_get_function_name(काष्ठा pinctrl_dev *pctldev,
					   अचिन्हित पूर्णांक function)
अणु
	काष्ठा पूर्णांकel_pinctrl *pctrl = pinctrl_dev_get_drvdata(pctldev);

	वापस pctrl->soc->functions[function].name;
पूर्ण

अटल पूर्णांक पूर्णांकel_get_function_groups(काष्ठा pinctrl_dev *pctldev,
				     अचिन्हित पूर्णांक function,
				     स्थिर अक्षर * स्थिर **groups,
				     अचिन्हित पूर्णांक * स्थिर ngroups)
अणु
	काष्ठा पूर्णांकel_pinctrl *pctrl = pinctrl_dev_get_drvdata(pctldev);

	*groups = pctrl->soc->functions[function].groups;
	*ngroups = pctrl->soc->functions[function].ngroups;
	वापस 0;
पूर्ण

अटल पूर्णांक पूर्णांकel_pinmux_set_mux(काष्ठा pinctrl_dev *pctldev,
				अचिन्हित पूर्णांक function, अचिन्हित पूर्णांक group)
अणु
	काष्ठा पूर्णांकel_pinctrl *pctrl = pinctrl_dev_get_drvdata(pctldev);
	स्थिर काष्ठा पूर्णांकel_pingroup *grp = &pctrl->soc->groups[group];
	अचिन्हित दीर्घ flags;
	पूर्णांक i;

	raw_spin_lock_irqsave(&pctrl->lock, flags);

	/*
	 * All pins in the groups needs to be accessible and writable
	 * beक्रमe we can enable the mux क्रम this group.
	 */
	क्रम (i = 0; i < grp->npins; i++) अणु
		अगर (!पूर्णांकel_pad_usable(pctrl, grp->pins[i])) अणु
			raw_spin_unlock_irqrestore(&pctrl->lock, flags);
			वापस -EBUSY;
		पूर्ण
	पूर्ण

	/* Now enable the mux setting क्रम each pin in the group */
	क्रम (i = 0; i < grp->npins; i++) अणु
		व्योम __iomem *padcfg0;
		u32 value;

		padcfg0 = पूर्णांकel_get_padcfg(pctrl, grp->pins[i], PADCFG0);
		value = पढ़ोl(padcfg0);

		value &= ~PADCFG0_PMODE_MASK;

		अगर (grp->modes)
			value |= grp->modes[i] << PADCFG0_PMODE_SHIFT;
		अन्यथा
			value |= grp->mode << PADCFG0_PMODE_SHIFT;

		ग_लिखोl(value, padcfg0);
	पूर्ण

	raw_spin_unlock_irqrestore(&pctrl->lock, flags);

	वापस 0;
पूर्ण

अटल व्योम __पूर्णांकel_gpio_set_direction(व्योम __iomem *padcfg0, bool input)
अणु
	u32 value;

	value = पढ़ोl(padcfg0);
	अगर (input) अणु
		value &= ~PADCFG0_GPIORXDIS;
		value |= PADCFG0_GPIOTXDIS;
	पूर्ण अन्यथा अणु
		value &= ~PADCFG0_GPIOTXDIS;
		value |= PADCFG0_GPIORXDIS;
	पूर्ण
	ग_लिखोl(value, padcfg0);
पूर्ण

अटल पूर्णांक पूर्णांकel_gpio_get_gpio_mode(व्योम __iomem *padcfg0)
अणु
	वापस (पढ़ोl(padcfg0) & PADCFG0_PMODE_MASK) >> PADCFG0_PMODE_SHIFT;
पूर्ण

अटल व्योम पूर्णांकel_gpio_set_gpio_mode(व्योम __iomem *padcfg0)
अणु
	u32 value;

	value = पढ़ोl(padcfg0);

	/* Put the pad पूर्णांकo GPIO mode */
	value &= ~PADCFG0_PMODE_MASK;
	value |= PADCFG0_PMODE_GPIO;

	/* Disable input and output buffers */
	value |= PADCFG0_GPIORXDIS;
	value |= PADCFG0_GPIOTXDIS;

	/* Disable SCI/SMI/NMI generation */
	value &= ~(PADCFG0_GPIROUTIOXAPIC | PADCFG0_GPIROUTSCI);
	value &= ~(PADCFG0_GPIROUTSMI | PADCFG0_GPIROUTNMI);

	ग_लिखोl(value, padcfg0);
पूर्ण

अटल पूर्णांक पूर्णांकel_gpio_request_enable(काष्ठा pinctrl_dev *pctldev,
				     काष्ठा pinctrl_gpio_range *range,
				     अचिन्हित पूर्णांक pin)
अणु
	काष्ठा पूर्णांकel_pinctrl *pctrl = pinctrl_dev_get_drvdata(pctldev);
	व्योम __iomem *padcfg0;
	अचिन्हित दीर्घ flags;

	padcfg0 = पूर्णांकel_get_padcfg(pctrl, pin, PADCFG0);

	raw_spin_lock_irqsave(&pctrl->lock, flags);

	अगर (!पूर्णांकel_pad_owned_by_host(pctrl, pin)) अणु
		raw_spin_unlock_irqrestore(&pctrl->lock, flags);
		वापस -EBUSY;
	पूर्ण

	अगर (!पूर्णांकel_pad_is_unlocked(pctrl, pin)) अणु
		raw_spin_unlock_irqrestore(&pctrl->lock, flags);
		वापस 0;
	पूर्ण

	/*
	 * If pin is alपढ़ोy configured in GPIO mode, we assume that
	 * firmware provides correct settings. In such हाल we aव्योम
	 * potential glitches on the pin. Otherwise, क्रम the pin in
	 * alternative mode, consumer has to supply respective flags.
	 */
	अगर (पूर्णांकel_gpio_get_gpio_mode(padcfg0) == PADCFG0_PMODE_GPIO) अणु
		raw_spin_unlock_irqrestore(&pctrl->lock, flags);
		वापस 0;
	पूर्ण

	पूर्णांकel_gpio_set_gpio_mode(padcfg0);

	/* Disable TX buffer and enable RX (this will be input) */
	__पूर्णांकel_gpio_set_direction(padcfg0, true);

	raw_spin_unlock_irqrestore(&pctrl->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक पूर्णांकel_gpio_set_direction(काष्ठा pinctrl_dev *pctldev,
				    काष्ठा pinctrl_gpio_range *range,
				    अचिन्हित पूर्णांक pin, bool input)
अणु
	काष्ठा पूर्णांकel_pinctrl *pctrl = pinctrl_dev_get_drvdata(pctldev);
	व्योम __iomem *padcfg0;
	अचिन्हित दीर्घ flags;

	padcfg0 = पूर्णांकel_get_padcfg(pctrl, pin, PADCFG0);

	raw_spin_lock_irqsave(&pctrl->lock, flags);
	__पूर्णांकel_gpio_set_direction(padcfg0, input);
	raw_spin_unlock_irqrestore(&pctrl->lock, flags);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pinmux_ops पूर्णांकel_pinmux_ops = अणु
	.get_functions_count = पूर्णांकel_get_functions_count,
	.get_function_name = पूर्णांकel_get_function_name,
	.get_function_groups = पूर्णांकel_get_function_groups,
	.set_mux = पूर्णांकel_pinmux_set_mux,
	.gpio_request_enable = पूर्णांकel_gpio_request_enable,
	.gpio_set_direction = पूर्णांकel_gpio_set_direction,
पूर्ण;

अटल पूर्णांक पूर्णांकel_config_get_pull(काष्ठा पूर्णांकel_pinctrl *pctrl, अचिन्हित पूर्णांक pin,
				 क्रमागत pin_config_param param, u32 *arg)
अणु
	स्थिर काष्ठा पूर्णांकel_community *community;
	व्योम __iomem *padcfg1;
	अचिन्हित दीर्घ flags;
	u32 value, term;

	community = पूर्णांकel_get_community(pctrl, pin);
	padcfg1 = पूर्णांकel_get_padcfg(pctrl, pin, PADCFG1);

	raw_spin_lock_irqsave(&pctrl->lock, flags);
	value = पढ़ोl(padcfg1);
	raw_spin_unlock_irqrestore(&pctrl->lock, flags);

	term = (value & PADCFG1_TERM_MASK) >> PADCFG1_TERM_SHIFT;

	चयन (param) अणु
	हाल PIN_CONFIG_BIAS_DISABLE:
		अगर (term)
			वापस -EINVAL;
		अवरोध;

	हाल PIN_CONFIG_BIAS_PULL_UP:
		अगर (!term || !(value & PADCFG1_TERM_UP))
			वापस -EINVAL;

		चयन (term) अणु
		हाल PADCFG1_TERM_833:
			*arg = 833;
			अवरोध;
		हाल PADCFG1_TERM_1K:
			*arg = 1000;
			अवरोध;
		हाल PADCFG1_TERM_5K:
			*arg = 5000;
			अवरोध;
		हाल PADCFG1_TERM_20K:
			*arg = 20000;
			अवरोध;
		पूर्ण

		अवरोध;

	हाल PIN_CONFIG_BIAS_PULL_DOWN:
		अगर (!term || value & PADCFG1_TERM_UP)
			वापस -EINVAL;

		चयन (term) अणु
		हाल PADCFG1_TERM_833:
			अगर (!(community->features & PINCTRL_FEATURE_1K_PD))
				वापस -EINVAL;
			*arg = 833;
			अवरोध;
		हाल PADCFG1_TERM_1K:
			अगर (!(community->features & PINCTRL_FEATURE_1K_PD))
				वापस -EINVAL;
			*arg = 1000;
			अवरोध;
		हाल PADCFG1_TERM_5K:
			*arg = 5000;
			अवरोध;
		हाल PADCFG1_TERM_20K:
			*arg = 20000;
			अवरोध;
		पूर्ण

		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक पूर्णांकel_config_get_debounce(काष्ठा पूर्णांकel_pinctrl *pctrl, अचिन्हित पूर्णांक pin,
				     क्रमागत pin_config_param param, u32 *arg)
अणु
	व्योम __iomem *padcfg2;
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ v;
	u32 value2;

	padcfg2 = पूर्णांकel_get_padcfg(pctrl, pin, PADCFG2);
	अगर (!padcfg2)
		वापस -ENOTSUPP;

	raw_spin_lock_irqsave(&pctrl->lock, flags);
	value2 = पढ़ोl(padcfg2);
	raw_spin_unlock_irqrestore(&pctrl->lock, flags);
	अगर (!(value2 & PADCFG2_DEBEN))
		वापस -EINVAL;

	v = (value2 & PADCFG2_DEBOUNCE_MASK) >> PADCFG2_DEBOUNCE_SHIFT;
	*arg = BIT(v) * DEBOUNCE_PERIOD_NSEC / NSEC_PER_USEC;

	वापस 0;
पूर्ण

अटल पूर्णांक पूर्णांकel_config_get(काष्ठा pinctrl_dev *pctldev, अचिन्हित पूर्णांक pin,
			    अचिन्हित दीर्घ *config)
अणु
	काष्ठा पूर्णांकel_pinctrl *pctrl = pinctrl_dev_get_drvdata(pctldev);
	क्रमागत pin_config_param param = pinconf_to_config_param(*config);
	u32 arg = 0;
	पूर्णांक ret;

	अगर (!पूर्णांकel_pad_owned_by_host(pctrl, pin))
		वापस -ENOTSUPP;

	चयन (param) अणु
	हाल PIN_CONFIG_BIAS_DISABLE:
	हाल PIN_CONFIG_BIAS_PULL_UP:
	हाल PIN_CONFIG_BIAS_PULL_DOWN:
		ret = पूर्णांकel_config_get_pull(pctrl, pin, param, &arg);
		अगर (ret)
			वापस ret;
		अवरोध;

	हाल PIN_CONFIG_INPUT_DEBOUNCE:
		ret = पूर्णांकel_config_get_debounce(pctrl, pin, param, &arg);
		अगर (ret)
			वापस ret;
		अवरोध;

	शेष:
		वापस -ENOTSUPP;
	पूर्ण

	*config = pinconf_to_config_packed(param, arg);
	वापस 0;
पूर्ण

अटल पूर्णांक पूर्णांकel_config_set_pull(काष्ठा पूर्णांकel_pinctrl *pctrl, अचिन्हित पूर्णांक pin,
				 अचिन्हित दीर्घ config)
अणु
	अचिन्हित पूर्णांक param = pinconf_to_config_param(config);
	अचिन्हित पूर्णांक arg = pinconf_to_config_argument(config);
	स्थिर काष्ठा पूर्णांकel_community *community;
	व्योम __iomem *padcfg1;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;
	u32 value;

	community = पूर्णांकel_get_community(pctrl, pin);
	padcfg1 = पूर्णांकel_get_padcfg(pctrl, pin, PADCFG1);

	raw_spin_lock_irqsave(&pctrl->lock, flags);

	value = पढ़ोl(padcfg1);

	चयन (param) अणु
	हाल PIN_CONFIG_BIAS_DISABLE:
		value &= ~(PADCFG1_TERM_MASK | PADCFG1_TERM_UP);
		अवरोध;

	हाल PIN_CONFIG_BIAS_PULL_UP:
		value &= ~PADCFG1_TERM_MASK;

		value |= PADCFG1_TERM_UP;

		/* Set शेष strength value in हाल none is given */
		अगर (arg == 1)
			arg = 5000;

		चयन (arg) अणु
		हाल 20000:
			value |= PADCFG1_TERM_20K << PADCFG1_TERM_SHIFT;
			अवरोध;
		हाल 5000:
			value |= PADCFG1_TERM_5K << PADCFG1_TERM_SHIFT;
			अवरोध;
		हाल 1000:
			value |= PADCFG1_TERM_1K << PADCFG1_TERM_SHIFT;
			अवरोध;
		हाल 833:
			value |= PADCFG1_TERM_833 << PADCFG1_TERM_SHIFT;
			अवरोध;
		शेष:
			ret = -EINVAL;
		पूर्ण

		अवरोध;

	हाल PIN_CONFIG_BIAS_PULL_DOWN:
		value &= ~(PADCFG1_TERM_UP | PADCFG1_TERM_MASK);

		/* Set शेष strength value in हाल none is given */
		अगर (arg == 1)
			arg = 5000;

		चयन (arg) अणु
		हाल 20000:
			value |= PADCFG1_TERM_20K << PADCFG1_TERM_SHIFT;
			अवरोध;
		हाल 5000:
			value |= PADCFG1_TERM_5K << PADCFG1_TERM_SHIFT;
			अवरोध;
		हाल 1000:
			अगर (!(community->features & PINCTRL_FEATURE_1K_PD)) अणु
				ret = -EINVAL;
				अवरोध;
			पूर्ण
			value |= PADCFG1_TERM_1K << PADCFG1_TERM_SHIFT;
			अवरोध;
		हाल 833:
			अगर (!(community->features & PINCTRL_FEATURE_1K_PD)) अणु
				ret = -EINVAL;
				अवरोध;
			पूर्ण
			value |= PADCFG1_TERM_833 << PADCFG1_TERM_SHIFT;
			अवरोध;
		शेष:
			ret = -EINVAL;
		पूर्ण

		अवरोध;
	पूर्ण

	अगर (!ret)
		ग_लिखोl(value, padcfg1);

	raw_spin_unlock_irqrestore(&pctrl->lock, flags);

	वापस ret;
पूर्ण

अटल पूर्णांक पूर्णांकel_config_set_debounce(काष्ठा पूर्णांकel_pinctrl *pctrl,
				     अचिन्हित पूर्णांक pin, अचिन्हित पूर्णांक debounce)
अणु
	व्योम __iomem *padcfg0, *padcfg2;
	अचिन्हित दीर्घ flags;
	u32 value0, value2;

	padcfg2 = पूर्णांकel_get_padcfg(pctrl, pin, PADCFG2);
	अगर (!padcfg2)
		वापस -ENOTSUPP;

	padcfg0 = पूर्णांकel_get_padcfg(pctrl, pin, PADCFG0);

	raw_spin_lock_irqsave(&pctrl->lock, flags);

	value0 = पढ़ोl(padcfg0);
	value2 = पढ़ोl(padcfg2);

	/* Disable glitch filter and debouncer */
	value0 &= ~PADCFG0_PREGFRXSEL;
	value2 &= ~(PADCFG2_DEBEN | PADCFG2_DEBOUNCE_MASK);

	अगर (debounce) अणु
		अचिन्हित दीर्घ v;

		v = order_base_2(debounce * NSEC_PER_USEC / DEBOUNCE_PERIOD_NSEC);
		अगर (v < 3 || v > 15) अणु
			raw_spin_unlock_irqrestore(&pctrl->lock, flags);
			वापस -EINVAL;
		पूर्ण

		/* Enable glitch filter and debouncer */
		value0 |= PADCFG0_PREGFRXSEL;
		value2 |= v << PADCFG2_DEBOUNCE_SHIFT;
		value2 |= PADCFG2_DEBEN;
	पूर्ण

	ग_लिखोl(value0, padcfg0);
	ग_लिखोl(value2, padcfg2);

	raw_spin_unlock_irqrestore(&pctrl->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक पूर्णांकel_config_set(काष्ठा pinctrl_dev *pctldev, अचिन्हित पूर्णांक pin,
			  अचिन्हित दीर्घ *configs, अचिन्हित पूर्णांक nconfigs)
अणु
	काष्ठा पूर्णांकel_pinctrl *pctrl = pinctrl_dev_get_drvdata(pctldev);
	पूर्णांक i, ret;

	अगर (!पूर्णांकel_pad_usable(pctrl, pin))
		वापस -ENOTSUPP;

	क्रम (i = 0; i < nconfigs; i++) अणु
		चयन (pinconf_to_config_param(configs[i])) अणु
		हाल PIN_CONFIG_BIAS_DISABLE:
		हाल PIN_CONFIG_BIAS_PULL_UP:
		हाल PIN_CONFIG_BIAS_PULL_DOWN:
			ret = पूर्णांकel_config_set_pull(pctrl, pin, configs[i]);
			अगर (ret)
				वापस ret;
			अवरोध;

		हाल PIN_CONFIG_INPUT_DEBOUNCE:
			ret = पूर्णांकel_config_set_debounce(pctrl, pin,
				pinconf_to_config_argument(configs[i]));
			अगर (ret)
				वापस ret;
			अवरोध;

		शेष:
			वापस -ENOTSUPP;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pinconf_ops पूर्णांकel_pinconf_ops = अणु
	.is_generic = true,
	.pin_config_get = पूर्णांकel_config_get,
	.pin_config_set = पूर्णांकel_config_set,
पूर्ण;

अटल स्थिर काष्ठा pinctrl_desc पूर्णांकel_pinctrl_desc = अणु
	.pctlops = &पूर्णांकel_pinctrl_ops,
	.pmxops = &पूर्णांकel_pinmux_ops,
	.confops = &पूर्णांकel_pinconf_ops,
	.owner = THIS_MODULE,
पूर्ण;

/**
 * पूर्णांकel_gpio_to_pin() - Translate from GPIO offset to pin number
 * @pctrl: Pinctrl काष्ठाure
 * @offset: GPIO offset from gpiolib
 * @community: Community is filled here अगर not %शून्य
 * @padgrp: Pad group is filled here अगर not %शून्य
 *
 * When coming through gpiolib irqchip, the GPIO offset is not
 * स्वतःmatically translated to pinctrl pin number. This function can be
 * used to find out the corresponding pinctrl pin.
 */
अटल पूर्णांक पूर्णांकel_gpio_to_pin(काष्ठा पूर्णांकel_pinctrl *pctrl, अचिन्हित पूर्णांक offset,
			     स्थिर काष्ठा पूर्णांकel_community **community,
			     स्थिर काष्ठा पूर्णांकel_padgroup **padgrp)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < pctrl->ncommunities; i++) अणु
		स्थिर काष्ठा पूर्णांकel_community *comm = &pctrl->communities[i];
		पूर्णांक j;

		क्रम (j = 0; j < comm->ngpps; j++) अणु
			स्थिर काष्ठा पूर्णांकel_padgroup *pgrp = &comm->gpps[j];

			अगर (pgrp->gpio_base == INTEL_GPIO_BASE_NOMAP)
				जारी;

			अगर (offset >= pgrp->gpio_base &&
			    offset < pgrp->gpio_base + pgrp->size) अणु
				पूर्णांक pin;

				pin = pgrp->base + offset - pgrp->gpio_base;
				अगर (community)
					*community = comm;
				अगर (padgrp)
					*padgrp = pgrp;

				वापस pin;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस -EINVAL;
पूर्ण

/**
 * पूर्णांकel_pin_to_gpio() - Translate from pin number to GPIO offset
 * @pctrl: Pinctrl काष्ठाure
 * @pin: pin number
 *
 * Translate the pin number of pinctrl to GPIO offset
 */
अटल __maybe_unused पूर्णांक पूर्णांकel_pin_to_gpio(काष्ठा पूर्णांकel_pinctrl *pctrl, पूर्णांक pin)
अणु
	स्थिर काष्ठा पूर्णांकel_community *community;
	स्थिर काष्ठा पूर्णांकel_padgroup *padgrp;

	community = पूर्णांकel_get_community(pctrl, pin);
	अगर (!community)
		वापस -EINVAL;

	padgrp = पूर्णांकel_community_get_padgroup(community, pin);
	अगर (!padgrp)
		वापस -EINVAL;

	वापस pin - padgrp->base + padgrp->gpio_base;
पूर्ण

अटल पूर्णांक पूर्णांकel_gpio_get(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset)
अणु
	काष्ठा पूर्णांकel_pinctrl *pctrl = gpiochip_get_data(chip);
	व्योम __iomem *reg;
	u32 padcfg0;
	पूर्णांक pin;

	pin = पूर्णांकel_gpio_to_pin(pctrl, offset, शून्य, शून्य);
	अगर (pin < 0)
		वापस -EINVAL;

	reg = पूर्णांकel_get_padcfg(pctrl, pin, PADCFG0);
	अगर (!reg)
		वापस -EINVAL;

	padcfg0 = पढ़ोl(reg);
	अगर (!(padcfg0 & PADCFG0_GPIOTXDIS))
		वापस !!(padcfg0 & PADCFG0_GPIOTXSTATE);

	वापस !!(padcfg0 & PADCFG0_GPIORXSTATE);
पूर्ण

अटल व्योम पूर्णांकel_gpio_set(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset,
			   पूर्णांक value)
अणु
	काष्ठा पूर्णांकel_pinctrl *pctrl = gpiochip_get_data(chip);
	अचिन्हित दीर्घ flags;
	व्योम __iomem *reg;
	u32 padcfg0;
	पूर्णांक pin;

	pin = पूर्णांकel_gpio_to_pin(pctrl, offset, शून्य, शून्य);
	अगर (pin < 0)
		वापस;

	reg = पूर्णांकel_get_padcfg(pctrl, pin, PADCFG0);
	अगर (!reg)
		वापस;

	raw_spin_lock_irqsave(&pctrl->lock, flags);
	padcfg0 = पढ़ोl(reg);
	अगर (value)
		padcfg0 |= PADCFG0_GPIOTXSTATE;
	अन्यथा
		padcfg0 &= ~PADCFG0_GPIOTXSTATE;
	ग_लिखोl(padcfg0, reg);
	raw_spin_unlock_irqrestore(&pctrl->lock, flags);
पूर्ण

अटल पूर्णांक पूर्णांकel_gpio_get_direction(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset)
अणु
	काष्ठा पूर्णांकel_pinctrl *pctrl = gpiochip_get_data(chip);
	अचिन्हित दीर्घ flags;
	व्योम __iomem *reg;
	u32 padcfg0;
	पूर्णांक pin;

	pin = पूर्णांकel_gpio_to_pin(pctrl, offset, शून्य, शून्य);
	अगर (pin < 0)
		वापस -EINVAL;

	reg = पूर्णांकel_get_padcfg(pctrl, pin, PADCFG0);
	अगर (!reg)
		वापस -EINVAL;

	raw_spin_lock_irqsave(&pctrl->lock, flags);
	padcfg0 = पढ़ोl(reg);
	raw_spin_unlock_irqrestore(&pctrl->lock, flags);
	अगर (padcfg0 & PADCFG0_PMODE_MASK)
		वापस -EINVAL;

	अगर (padcfg0 & PADCFG0_GPIOTXDIS)
		वापस GPIO_LINE_सूचीECTION_IN;

	वापस GPIO_LINE_सूचीECTION_OUT;
पूर्ण

अटल पूर्णांक पूर्णांकel_gpio_direction_input(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset)
अणु
	वापस pinctrl_gpio_direction_input(chip->base + offset);
पूर्ण

अटल पूर्णांक पूर्णांकel_gpio_direction_output(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset,
				       पूर्णांक value)
अणु
	पूर्णांकel_gpio_set(chip, offset, value);
	वापस pinctrl_gpio_direction_output(chip->base + offset);
पूर्ण

अटल स्थिर काष्ठा gpio_chip पूर्णांकel_gpio_chip = अणु
	.owner = THIS_MODULE,
	.request = gpiochip_generic_request,
	.मुक्त = gpiochip_generic_मुक्त,
	.get_direction = पूर्णांकel_gpio_get_direction,
	.direction_input = पूर्णांकel_gpio_direction_input,
	.direction_output = पूर्णांकel_gpio_direction_output,
	.get = पूर्णांकel_gpio_get,
	.set = पूर्णांकel_gpio_set,
	.set_config = gpiochip_generic_config,
पूर्ण;

अटल व्योम पूर्णांकel_gpio_irq_ack(काष्ठा irq_data *d)
अणु
	काष्ठा gpio_chip *gc = irq_data_get_irq_chip_data(d);
	काष्ठा पूर्णांकel_pinctrl *pctrl = gpiochip_get_data(gc);
	स्थिर काष्ठा पूर्णांकel_community *community;
	स्थिर काष्ठा पूर्णांकel_padgroup *padgrp;
	पूर्णांक pin;

	pin = पूर्णांकel_gpio_to_pin(pctrl, irqd_to_hwirq(d), &community, &padgrp);
	अगर (pin >= 0) अणु
		अचिन्हित पूर्णांक gpp, gpp_offset, is_offset;

		gpp = padgrp->reg_num;
		gpp_offset = padgroup_offset(padgrp, pin);
		is_offset = community->is_offset + gpp * 4;

		raw_spin_lock(&pctrl->lock);
		ग_लिखोl(BIT(gpp_offset), community->regs + is_offset);
		raw_spin_unlock(&pctrl->lock);
	पूर्ण
पूर्ण

अटल व्योम पूर्णांकel_gpio_irq_mask_unmask(काष्ठा irq_data *d, bool mask)
अणु
	काष्ठा gpio_chip *gc = irq_data_get_irq_chip_data(d);
	काष्ठा पूर्णांकel_pinctrl *pctrl = gpiochip_get_data(gc);
	स्थिर काष्ठा पूर्णांकel_community *community;
	स्थिर काष्ठा पूर्णांकel_padgroup *padgrp;
	पूर्णांक pin;

	pin = पूर्णांकel_gpio_to_pin(pctrl, irqd_to_hwirq(d), &community, &padgrp);
	अगर (pin >= 0) अणु
		अचिन्हित पूर्णांक gpp, gpp_offset;
		अचिन्हित दीर्घ flags;
		व्योम __iomem *reg, *is;
		u32 value;

		gpp = padgrp->reg_num;
		gpp_offset = padgroup_offset(padgrp, pin);

		reg = community->regs + community->ie_offset + gpp * 4;
		is = community->regs + community->is_offset + gpp * 4;

		raw_spin_lock_irqsave(&pctrl->lock, flags);

		/* Clear पूर्णांकerrupt status first to aव्योम unexpected पूर्णांकerrupt */
		ग_लिखोl(BIT(gpp_offset), is);

		value = पढ़ोl(reg);
		अगर (mask)
			value &= ~BIT(gpp_offset);
		अन्यथा
			value |= BIT(gpp_offset);
		ग_लिखोl(value, reg);
		raw_spin_unlock_irqrestore(&pctrl->lock, flags);
	पूर्ण
पूर्ण

अटल व्योम पूर्णांकel_gpio_irq_mask(काष्ठा irq_data *d)
अणु
	पूर्णांकel_gpio_irq_mask_unmask(d, true);
पूर्ण

अटल व्योम पूर्णांकel_gpio_irq_unmask(काष्ठा irq_data *d)
अणु
	पूर्णांकel_gpio_irq_mask_unmask(d, false);
पूर्ण

अटल पूर्णांक पूर्णांकel_gpio_irq_type(काष्ठा irq_data *d, अचिन्हित पूर्णांक type)
अणु
	काष्ठा gpio_chip *gc = irq_data_get_irq_chip_data(d);
	काष्ठा पूर्णांकel_pinctrl *pctrl = gpiochip_get_data(gc);
	अचिन्हित पूर्णांक pin = पूर्णांकel_gpio_to_pin(pctrl, irqd_to_hwirq(d), शून्य, शून्य);
	अचिन्हित दीर्घ flags;
	व्योम __iomem *reg;
	u32 value;

	reg = पूर्णांकel_get_padcfg(pctrl, pin, PADCFG0);
	अगर (!reg)
		वापस -EINVAL;

	/*
	 * If the pin is in ACPI mode it is still usable as a GPIO but it
	 * cannot be used as IRQ because GPI_IS status bit will not be
	 * updated by the host controller hardware.
	 */
	अगर (पूर्णांकel_pad_acpi_mode(pctrl, pin)) अणु
		dev_warn(pctrl->dev, "pin %u cannot be used as IRQ\n", pin);
		वापस -EPERM;
	पूर्ण

	raw_spin_lock_irqsave(&pctrl->lock, flags);

	पूर्णांकel_gpio_set_gpio_mode(reg);

	/* Disable TX buffer and enable RX (this will be input) */
	__पूर्णांकel_gpio_set_direction(reg, true);

	value = पढ़ोl(reg);

	value &= ~(PADCFG0_RXEVCFG_MASK | PADCFG0_RXINV);

	अगर ((type & IRQ_TYPE_EDGE_BOTH) == IRQ_TYPE_EDGE_BOTH) अणु
		value |= PADCFG0_RXEVCFG_EDGE_BOTH << PADCFG0_RXEVCFG_SHIFT;
	पूर्ण अन्यथा अगर (type & IRQ_TYPE_EDGE_FALLING) अणु
		value |= PADCFG0_RXEVCFG_EDGE << PADCFG0_RXEVCFG_SHIFT;
		value |= PADCFG0_RXINV;
	पूर्ण अन्यथा अगर (type & IRQ_TYPE_EDGE_RISING) अणु
		value |= PADCFG0_RXEVCFG_EDGE << PADCFG0_RXEVCFG_SHIFT;
	पूर्ण अन्यथा अगर (type & IRQ_TYPE_LEVEL_MASK) अणु
		अगर (type & IRQ_TYPE_LEVEL_LOW)
			value |= PADCFG0_RXINV;
	पूर्ण अन्यथा अणु
		value |= PADCFG0_RXEVCFG_DISABLED << PADCFG0_RXEVCFG_SHIFT;
	पूर्ण

	ग_लिखोl(value, reg);

	अगर (type & IRQ_TYPE_EDGE_BOTH)
		irq_set_handler_locked(d, handle_edge_irq);
	अन्यथा अगर (type & IRQ_TYPE_LEVEL_MASK)
		irq_set_handler_locked(d, handle_level_irq);

	raw_spin_unlock_irqrestore(&pctrl->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक पूर्णांकel_gpio_irq_wake(काष्ठा irq_data *d, अचिन्हित पूर्णांक on)
अणु
	काष्ठा gpio_chip *gc = irq_data_get_irq_chip_data(d);
	काष्ठा पूर्णांकel_pinctrl *pctrl = gpiochip_get_data(gc);
	अचिन्हित पूर्णांक pin = पूर्णांकel_gpio_to_pin(pctrl, irqd_to_hwirq(d), शून्य, शून्य);

	अगर (on)
		enable_irq_wake(pctrl->irq);
	अन्यथा
		disable_irq_wake(pctrl->irq);

	dev_dbg(pctrl->dev, "%sable wake for pin %u\n", on ? "en" : "dis", pin);
	वापस 0;
पूर्ण

अटल पूर्णांक पूर्णांकel_gpio_community_irq_handler(काष्ठा पूर्णांकel_pinctrl *pctrl,
					    स्थिर काष्ठा पूर्णांकel_community *community)
अणु
	काष्ठा gpio_chip *gc = &pctrl->chip;
	अचिन्हित पूर्णांक gpp;
	पूर्णांक ret = 0;

	क्रम (gpp = 0; gpp < community->ngpps; gpp++) अणु
		स्थिर काष्ठा पूर्णांकel_padgroup *padgrp = &community->gpps[gpp];
		अचिन्हित दीर्घ pending, enabled, gpp_offset;

		raw_spin_lock(&pctrl->lock);

		pending = पढ़ोl(community->regs + community->is_offset +
				padgrp->reg_num * 4);
		enabled = पढ़ोl(community->regs + community->ie_offset +
				padgrp->reg_num * 4);

		raw_spin_unlock(&pctrl->lock);

		/* Only पूर्णांकerrupts that are enabled */
		pending &= enabled;

		क्रम_each_set_bit(gpp_offset, &pending, padgrp->size) अणु
			अचिन्हित पूर्णांक irq;

			irq = irq_find_mapping(gc->irq.करोमुख्य,
					       padgrp->gpio_base + gpp_offset);
			generic_handle_irq(irq);
		पूर्ण

		ret += pending ? 1 : 0;
	पूर्ण

	वापस ret;
पूर्ण

अटल irqवापस_t पूर्णांकel_gpio_irq(पूर्णांक irq, व्योम *data)
अणु
	स्थिर काष्ठा पूर्णांकel_community *community;
	काष्ठा पूर्णांकel_pinctrl *pctrl = data;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret = 0;

	/* Need to check all communities क्रम pending पूर्णांकerrupts */
	क्रम (i = 0; i < pctrl->ncommunities; i++) अणु
		community = &pctrl->communities[i];
		ret += पूर्णांकel_gpio_community_irq_handler(pctrl, community);
	पूर्ण

	वापस IRQ_RETVAL(ret);
पूर्ण

अटल पूर्णांक पूर्णांकel_gpio_add_community_ranges(काष्ठा पूर्णांकel_pinctrl *pctrl,
				स्थिर काष्ठा पूर्णांकel_community *community)
अणु
	पूर्णांक ret = 0, i;

	क्रम (i = 0; i < community->ngpps; i++) अणु
		स्थिर काष्ठा पूर्णांकel_padgroup *gpp = &community->gpps[i];

		अगर (gpp->gpio_base == INTEL_GPIO_BASE_NOMAP)
			जारी;

		ret = gpiochip_add_pin_range(&pctrl->chip, dev_name(pctrl->dev),
					     gpp->gpio_base, gpp->base,
					     gpp->size);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक पूर्णांकel_gpio_add_pin_ranges(काष्ठा gpio_chip *gc)
अणु
	काष्ठा पूर्णांकel_pinctrl *pctrl = gpiochip_get_data(gc);
	पूर्णांक ret, i;

	क्रम (i = 0; i < pctrl->ncommunities; i++) अणु
		काष्ठा पूर्णांकel_community *community = &pctrl->communities[i];

		ret = पूर्णांकel_gpio_add_community_ranges(pctrl, community);
		अगर (ret) अणु
			dev_err(pctrl->dev, "failed to add GPIO pin range\n");
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक पूर्णांकel_gpio_ngpio(स्थिर काष्ठा पूर्णांकel_pinctrl *pctrl)
अणु
	स्थिर काष्ठा पूर्णांकel_community *community;
	अचिन्हित पूर्णांक ngpio = 0;
	पूर्णांक i, j;

	क्रम (i = 0; i < pctrl->ncommunities; i++) अणु
		community = &pctrl->communities[i];
		क्रम (j = 0; j < community->ngpps; j++) अणु
			स्थिर काष्ठा पूर्णांकel_padgroup *gpp = &community->gpps[j];

			अगर (gpp->gpio_base == INTEL_GPIO_BASE_NOMAP)
				जारी;

			अगर (gpp->gpio_base + gpp->size > ngpio)
				ngpio = gpp->gpio_base + gpp->size;
		पूर्ण
	पूर्ण

	वापस ngpio;
पूर्ण

अटल पूर्णांक पूर्णांकel_gpio_probe(काष्ठा पूर्णांकel_pinctrl *pctrl, पूर्णांक irq)
अणु
	पूर्णांक ret;
	काष्ठा gpio_irq_chip *girq;

	pctrl->chip = पूर्णांकel_gpio_chip;

	/* Setup GPIO chip */
	pctrl->chip.ngpio = पूर्णांकel_gpio_ngpio(pctrl);
	pctrl->chip.label = dev_name(pctrl->dev);
	pctrl->chip.parent = pctrl->dev;
	pctrl->chip.base = -1;
	pctrl->chip.add_pin_ranges = पूर्णांकel_gpio_add_pin_ranges;
	pctrl->irq = irq;

	/* Setup IRQ chip */
	pctrl->irqchip.name = dev_name(pctrl->dev);
	pctrl->irqchip.irq_ack = पूर्णांकel_gpio_irq_ack;
	pctrl->irqchip.irq_mask = पूर्णांकel_gpio_irq_mask;
	pctrl->irqchip.irq_unmask = पूर्णांकel_gpio_irq_unmask;
	pctrl->irqchip.irq_set_type = पूर्णांकel_gpio_irq_type;
	pctrl->irqchip.irq_set_wake = पूर्णांकel_gpio_irq_wake;
	pctrl->irqchip.flags = IRQCHIP_MASK_ON_SUSPEND;

	/*
	 * On some platक्रमms several GPIO controllers share the same पूर्णांकerrupt
	 * line.
	 */
	ret = devm_request_irq(pctrl->dev, irq, पूर्णांकel_gpio_irq,
			       IRQF_SHARED | IRQF_NO_THREAD,
			       dev_name(pctrl->dev), pctrl);
	अगर (ret) अणु
		dev_err(pctrl->dev, "failed to request interrupt\n");
		वापस ret;
	पूर्ण

	girq = &pctrl->chip.irq;
	girq->chip = &pctrl->irqchip;
	/* This will let us handle the IRQ in the driver */
	girq->parent_handler = शून्य;
	girq->num_parents = 0;
	girq->शेष_type = IRQ_TYPE_NONE;
	girq->handler = handle_bad_irq;

	ret = devm_gpiochip_add_data(pctrl->dev, &pctrl->chip, pctrl);
	अगर (ret) अणु
		dev_err(pctrl->dev, "failed to register gpiochip\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक पूर्णांकel_pinctrl_add_padgroups_by_gpps(काष्ठा पूर्णांकel_pinctrl *pctrl,
					       काष्ठा पूर्णांकel_community *community)
अणु
	काष्ठा पूर्णांकel_padgroup *gpps;
	अचिन्हित पूर्णांक paकरोwn_num = 0;
	माप_प्रकार i, ngpps = community->ngpps;

	gpps = devm_kसुस्मृति(pctrl->dev, ngpps, माप(*gpps), GFP_KERNEL);
	अगर (!gpps)
		वापस -ENOMEM;

	क्रम (i = 0; i < ngpps; i++) अणु
		gpps[i] = community->gpps[i];

		अगर (gpps[i].size > 32)
			वापस -EINVAL;

		/* Special treaपंचांगent क्रम GPIO base */
		चयन (gpps[i].gpio_base) अणु
			हाल INTEL_GPIO_BASE_MATCH:
				gpps[i].gpio_base = gpps[i].base;
				अवरोध;
			हाल INTEL_GPIO_BASE_ZERO:
				gpps[i].gpio_base = 0;
				अवरोध;
			हाल INTEL_GPIO_BASE_NOMAP:
				अवरोध;
			शेष:
				अवरोध;
		पूर्ण

		gpps[i].paकरोwn_num = paकरोwn_num;
		paकरोwn_num += DIV_ROUND_UP(gpps[i].size * 4, 32);
	पूर्ण

	community->gpps = gpps;

	वापस 0;
पूर्ण

अटल पूर्णांक पूर्णांकel_pinctrl_add_padgroups_by_size(काष्ठा पूर्णांकel_pinctrl *pctrl,
					       काष्ठा पूर्णांकel_community *community)
अणु
	काष्ठा पूर्णांकel_padgroup *gpps;
	अचिन्हित पूर्णांक npins = community->npins;
	अचिन्हित पूर्णांक paकरोwn_num = 0;
	माप_प्रकार i, ngpps = DIV_ROUND_UP(npins, community->gpp_size);

	अगर (community->gpp_size > 32)
		वापस -EINVAL;

	gpps = devm_kसुस्मृति(pctrl->dev, ngpps, माप(*gpps), GFP_KERNEL);
	अगर (!gpps)
		वापस -ENOMEM;

	क्रम (i = 0; i < ngpps; i++) अणु
		अचिन्हित पूर्णांक gpp_size = community->gpp_size;

		gpps[i].reg_num = i;
		gpps[i].base = community->pin_base + i * gpp_size;
		gpps[i].size = min(gpp_size, npins);
		npins -= gpps[i].size;

		gpps[i].gpio_base = gpps[i].base;
		gpps[i].paकरोwn_num = paकरोwn_num;

		/*
		 * In older hardware the number of paकरोwn रेजिस्टरs per
		 * group is fixed regardless of the group size.
		 */
		अगर (community->gpp_num_paकरोwn_regs)
			paकरोwn_num += community->gpp_num_paकरोwn_regs;
		अन्यथा
			paकरोwn_num += DIV_ROUND_UP(gpps[i].size * 4, 32);
	पूर्ण

	community->ngpps = ngpps;
	community->gpps = gpps;

	वापस 0;
पूर्ण

अटल पूर्णांक पूर्णांकel_pinctrl_pm_init(काष्ठा पूर्णांकel_pinctrl *pctrl)
अणु
#अगर_घोषित CONFIG_PM_SLEEP
	स्थिर काष्ठा पूर्णांकel_pinctrl_soc_data *soc = pctrl->soc;
	काष्ठा पूर्णांकel_community_context *communities;
	काष्ठा पूर्णांकel_pad_context *pads;
	पूर्णांक i;

	pads = devm_kसुस्मृति(pctrl->dev, soc->npins, माप(*pads), GFP_KERNEL);
	अगर (!pads)
		वापस -ENOMEM;

	communities = devm_kसुस्मृति(pctrl->dev, pctrl->ncommunities,
				   माप(*communities), GFP_KERNEL);
	अगर (!communities)
		वापस -ENOMEM;


	क्रम (i = 0; i < pctrl->ncommunities; i++) अणु
		काष्ठा पूर्णांकel_community *community = &pctrl->communities[i];
		u32 *पूर्णांकmask, *hostown;

		पूर्णांकmask = devm_kसुस्मृति(pctrl->dev, community->ngpps,
				       माप(*पूर्णांकmask), GFP_KERNEL);
		अगर (!पूर्णांकmask)
			वापस -ENOMEM;

		communities[i].पूर्णांकmask = पूर्णांकmask;

		hostown = devm_kसुस्मृति(pctrl->dev, community->ngpps,
				       माप(*hostown), GFP_KERNEL);
		अगर (!hostown)
			वापस -ENOMEM;

		communities[i].hostown = hostown;
	पूर्ण

	pctrl->context.pads = pads;
	pctrl->context.communities = communities;
#पूर्ण_अगर

	वापस 0;
पूर्ण

अटल पूर्णांक पूर्णांकel_pinctrl_probe(काष्ठा platक्रमm_device *pdev,
			       स्थिर काष्ठा पूर्णांकel_pinctrl_soc_data *soc_data)
अणु
	काष्ठा पूर्णांकel_pinctrl *pctrl;
	पूर्णांक i, ret, irq;

	pctrl = devm_kzalloc(&pdev->dev, माप(*pctrl), GFP_KERNEL);
	अगर (!pctrl)
		वापस -ENOMEM;

	pctrl->dev = &pdev->dev;
	pctrl->soc = soc_data;
	raw_spin_lock_init(&pctrl->lock);

	/*
	 * Make a copy of the communities which we can use to hold poपूर्णांकers
	 * to the रेजिस्टरs.
	 */
	pctrl->ncommunities = pctrl->soc->ncommunities;
	pctrl->communities = devm_kसुस्मृति(&pdev->dev, pctrl->ncommunities,
				  माप(*pctrl->communities), GFP_KERNEL);
	अगर (!pctrl->communities)
		वापस -ENOMEM;

	क्रम (i = 0; i < pctrl->ncommunities; i++) अणु
		काष्ठा पूर्णांकel_community *community = &pctrl->communities[i];
		व्योम __iomem *regs;
		u32 offset;
		u32 value;

		*community = pctrl->soc->communities[i];

		regs = devm_platक्रमm_ioremap_resource(pdev, community->barno);
		अगर (IS_ERR(regs))
			वापस PTR_ERR(regs);

		/*
		 * Determine community features based on the revision.
		 * A value of all ones means the device is not present.
		 */
		value = पढ़ोl(regs + REVID);
		अगर (value == ~0u)
			वापस -ENODEV;
		अगर (((value & REVID_MASK) >> REVID_SHIFT) >= 0x94) अणु
			community->features |= PINCTRL_FEATURE_DEBOUNCE;
			community->features |= PINCTRL_FEATURE_1K_PD;
		पूर्ण

		/* Determine community features based on the capabilities */
		offset = CAPLIST;
		करो अणु
			value = पढ़ोl(regs + offset);
			चयन ((value & CAPLIST_ID_MASK) >> CAPLIST_ID_SHIFT) अणु
			हाल CAPLIST_ID_GPIO_HW_INFO:
				community->features |= PINCTRL_FEATURE_GPIO_HW_INFO;
				अवरोध;
			हाल CAPLIST_ID_PWM:
				community->features |= PINCTRL_FEATURE_PWM;
				अवरोध;
			हाल CAPLIST_ID_BLINK:
				community->features |= PINCTRL_FEATURE_BLINK;
				अवरोध;
			हाल CAPLIST_ID_EXP:
				community->features |= PINCTRL_FEATURE_EXP;
				अवरोध;
			शेष:
				अवरोध;
			पूर्ण
			offset = (value & CAPLIST_NEXT_MASK) >> CAPLIST_NEXT_SHIFT;
		पूर्ण जबतक (offset);

		dev_dbg(&pdev->dev, "Community%d features: %#08x\n", i, community->features);

		/* Read offset of the pad configuration रेजिस्टरs */
		offset = पढ़ोl(regs + PADBAR);

		community->regs = regs;
		community->pad_regs = regs + offset;

		अगर (community->gpps)
			ret = पूर्णांकel_pinctrl_add_padgroups_by_gpps(pctrl, community);
		अन्यथा
			ret = पूर्णांकel_pinctrl_add_padgroups_by_size(pctrl, community);
		अगर (ret)
			वापस ret;
	पूर्ण

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;

	ret = पूर्णांकel_pinctrl_pm_init(pctrl);
	अगर (ret)
		वापस ret;

	pctrl->pctldesc = पूर्णांकel_pinctrl_desc;
	pctrl->pctldesc.name = dev_name(&pdev->dev);
	pctrl->pctldesc.pins = pctrl->soc->pins;
	pctrl->pctldesc.npins = pctrl->soc->npins;

	pctrl->pctldev = devm_pinctrl_रेजिस्टर(&pdev->dev, &pctrl->pctldesc,
					       pctrl);
	अगर (IS_ERR(pctrl->pctldev)) अणु
		dev_err(&pdev->dev, "failed to register pinctrl driver\n");
		वापस PTR_ERR(pctrl->pctldev);
	पूर्ण

	ret = पूर्णांकel_gpio_probe(pctrl, irq);
	अगर (ret)
		वापस ret;

	platक्रमm_set_drvdata(pdev, pctrl);

	वापस 0;
पूर्ण

पूर्णांक पूर्णांकel_pinctrl_probe_by_hid(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा पूर्णांकel_pinctrl_soc_data *data;

	data = device_get_match_data(&pdev->dev);
	अगर (!data)
		वापस -ENODATA;

	वापस पूर्णांकel_pinctrl_probe(pdev, data);
पूर्ण
EXPORT_SYMBOL_GPL(पूर्णांकel_pinctrl_probe_by_hid);

पूर्णांक पूर्णांकel_pinctrl_probe_by_uid(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा पूर्णांकel_pinctrl_soc_data *data;

	data = पूर्णांकel_pinctrl_get_soc_data(pdev);
	अगर (IS_ERR(data))
		वापस PTR_ERR(data);

	वापस पूर्णांकel_pinctrl_probe(pdev, data);
पूर्ण
EXPORT_SYMBOL_GPL(पूर्णांकel_pinctrl_probe_by_uid);

स्थिर काष्ठा पूर्णांकel_pinctrl_soc_data *पूर्णांकel_pinctrl_get_soc_data(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा पूर्णांकel_pinctrl_soc_data *data = शून्य;
	स्थिर काष्ठा पूर्णांकel_pinctrl_soc_data **table;
	काष्ठा acpi_device *adev;
	अचिन्हित पूर्णांक i;

	adev = ACPI_COMPANION(&pdev->dev);
	अगर (adev) अणु
		स्थिर व्योम *match = device_get_match_data(&pdev->dev);

		table = (स्थिर काष्ठा पूर्णांकel_pinctrl_soc_data **)match;
		क्रम (i = 0; table[i]; i++) अणु
			अगर (!म_भेद(adev->pnp.unique_id, table[i]->uid)) अणु
				data = table[i];
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		स्थिर काष्ठा platक्रमm_device_id *id;

		id = platक्रमm_get_device_id(pdev);
		अगर (!id)
			वापस ERR_PTR(-ENODEV);

		table = (स्थिर काष्ठा पूर्णांकel_pinctrl_soc_data **)id->driver_data;
		data = table[pdev->id];
	पूर्ण

	वापस data ?: ERR_PTR(-ENODATA);
पूर्ण
EXPORT_SYMBOL_GPL(पूर्णांकel_pinctrl_get_soc_data);

#अगर_घोषित CONFIG_PM_SLEEP
अटल bool पूर्णांकel_pinctrl_should_save(काष्ठा पूर्णांकel_pinctrl *pctrl, अचिन्हित पूर्णांक pin)
अणु
	स्थिर काष्ठा pin_desc *pd = pin_desc_get(pctrl->pctldev, pin);

	अगर (!pd || !पूर्णांकel_pad_usable(pctrl, pin))
		वापस false;

	/*
	 * Only restore the pin अगर it is actually in use by the kernel (or
	 * by userspace). It is possible that some pins are used by the
	 * BIOS during resume and those are not always locked करोwn so leave
	 * them alone.
	 */
	अगर (pd->mux_owner || pd->gpio_owner ||
	    gpiochip_line_is_irq(&pctrl->chip, पूर्णांकel_pin_to_gpio(pctrl, pin)))
		वापस true;

	वापस false;
पूर्ण

पूर्णांक पूर्णांकel_pinctrl_suspend_noirq(काष्ठा device *dev)
अणु
	काष्ठा पूर्णांकel_pinctrl *pctrl = dev_get_drvdata(dev);
	काष्ठा पूर्णांकel_community_context *communities;
	काष्ठा पूर्णांकel_pad_context *pads;
	पूर्णांक i;

	pads = pctrl->context.pads;
	क्रम (i = 0; i < pctrl->soc->npins; i++) अणु
		स्थिर काष्ठा pinctrl_pin_desc *desc = &pctrl->soc->pins[i];
		व्योम __iomem *padcfg;
		u32 val;

		अगर (!पूर्णांकel_pinctrl_should_save(pctrl, desc->number))
			जारी;

		val = पढ़ोl(पूर्णांकel_get_padcfg(pctrl, desc->number, PADCFG0));
		pads[i].padcfg0 = val & ~PADCFG0_GPIORXSTATE;
		val = पढ़ोl(पूर्णांकel_get_padcfg(pctrl, desc->number, PADCFG1));
		pads[i].padcfg1 = val;

		padcfg = पूर्णांकel_get_padcfg(pctrl, desc->number, PADCFG2);
		अगर (padcfg)
			pads[i].padcfg2 = पढ़ोl(padcfg);
	पूर्ण

	communities = pctrl->context.communities;
	क्रम (i = 0; i < pctrl->ncommunities; i++) अणु
		काष्ठा पूर्णांकel_community *community = &pctrl->communities[i];
		व्योम __iomem *base;
		अचिन्हित पूर्णांक gpp;

		base = community->regs + community->ie_offset;
		क्रम (gpp = 0; gpp < community->ngpps; gpp++)
			communities[i].पूर्णांकmask[gpp] = पढ़ोl(base + gpp * 4);

		base = community->regs + community->hostown_offset;
		क्रम (gpp = 0; gpp < community->ngpps; gpp++)
			communities[i].hostown[gpp] = पढ़ोl(base + gpp * 4);
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(पूर्णांकel_pinctrl_suspend_noirq);

अटल व्योम पूर्णांकel_gpio_irq_init(काष्ठा पूर्णांकel_pinctrl *pctrl)
अणु
	माप_प्रकार i;

	क्रम (i = 0; i < pctrl->ncommunities; i++) अणु
		स्थिर काष्ठा पूर्णांकel_community *community;
		व्योम __iomem *base;
		अचिन्हित पूर्णांक gpp;

		community = &pctrl->communities[i];
		base = community->regs;

		क्रम (gpp = 0; gpp < community->ngpps; gpp++) अणु
			/* Mask and clear all पूर्णांकerrupts */
			ग_लिखोl(0, base + community->ie_offset + gpp * 4);
			ग_लिखोl(0xffff, base + community->is_offset + gpp * 4);
		पूर्ण
	पूर्ण
पूर्ण

अटल bool पूर्णांकel_gpio_update_reg(व्योम __iomem *reg, u32 mask, u32 value)
अणु
	u32 curr, updated;

	curr = पढ़ोl(reg);

	updated = (curr & ~mask) | (value & mask);
	अगर (curr == updated)
		वापस false;

	ग_लिखोl(updated, reg);
	वापस true;
पूर्ण

अटल व्योम पूर्णांकel_restore_hostown(काष्ठा पूर्णांकel_pinctrl *pctrl, अचिन्हित पूर्णांक c,
				  व्योम __iomem *base, अचिन्हित पूर्णांक gpp, u32 saved)
अणु
	स्थिर काष्ठा पूर्णांकel_community *community = &pctrl->communities[c];
	स्थिर काष्ठा पूर्णांकel_padgroup *padgrp = &community->gpps[gpp];
	काष्ठा device *dev = pctrl->dev;
	स्थिर अक्षर *dummy;
	u32 requested = 0;
	अचिन्हित पूर्णांक i;

	अगर (padgrp->gpio_base == INTEL_GPIO_BASE_NOMAP)
		वापस;

	क्रम_each_requested_gpio_in_range(&pctrl->chip, i, padgrp->gpio_base, padgrp->size, dummy)
		requested |= BIT(i);

	अगर (!पूर्णांकel_gpio_update_reg(base + gpp * 4, requested, saved))
		वापस;

	dev_dbg(dev, "restored hostown %u/%u %#08x\n", c, gpp, पढ़ोl(base + gpp * 4));
पूर्ण

अटल व्योम पूर्णांकel_restore_पूर्णांकmask(काष्ठा पूर्णांकel_pinctrl *pctrl, अचिन्हित पूर्णांक c,
				  व्योम __iomem *base, अचिन्हित पूर्णांक gpp, u32 saved)
अणु
	काष्ठा device *dev = pctrl->dev;

	अगर (!पूर्णांकel_gpio_update_reg(base + gpp * 4, ~0U, saved))
		वापस;

	dev_dbg(dev, "restored mask %u/%u %#08x\n", c, gpp, पढ़ोl(base + gpp * 4));
पूर्ण

अटल व्योम पूर्णांकel_restore_padcfg(काष्ठा पूर्णांकel_pinctrl *pctrl, अचिन्हित पूर्णांक pin,
				 अचिन्हित पूर्णांक reg, u32 saved)
अणु
	u32 mask = (reg == PADCFG0) ? PADCFG0_GPIORXSTATE : 0;
	अचिन्हित पूर्णांक n = reg / माप(u32);
	काष्ठा device *dev = pctrl->dev;
	व्योम __iomem *padcfg;

	padcfg = पूर्णांकel_get_padcfg(pctrl, pin, reg);
	अगर (!padcfg)
		वापस;

	अगर (!पूर्णांकel_gpio_update_reg(padcfg, ~mask, saved))
		वापस;

	dev_dbg(dev, "restored pin %u padcfg%u %#08x\n", pin, n, पढ़ोl(padcfg));
पूर्ण

पूर्णांक पूर्णांकel_pinctrl_resume_noirq(काष्ठा device *dev)
अणु
	काष्ठा पूर्णांकel_pinctrl *pctrl = dev_get_drvdata(dev);
	स्थिर काष्ठा पूर्णांकel_community_context *communities;
	स्थिर काष्ठा पूर्णांकel_pad_context *pads;
	पूर्णांक i;

	/* Mask all पूर्णांकerrupts */
	पूर्णांकel_gpio_irq_init(pctrl);

	pads = pctrl->context.pads;
	क्रम (i = 0; i < pctrl->soc->npins; i++) अणु
		स्थिर काष्ठा pinctrl_pin_desc *desc = &pctrl->soc->pins[i];

		अगर (!पूर्णांकel_pinctrl_should_save(pctrl, desc->number))
			जारी;

		पूर्णांकel_restore_padcfg(pctrl, desc->number, PADCFG0, pads[i].padcfg0);
		पूर्णांकel_restore_padcfg(pctrl, desc->number, PADCFG1, pads[i].padcfg1);
		पूर्णांकel_restore_padcfg(pctrl, desc->number, PADCFG2, pads[i].padcfg2);
	पूर्ण

	communities = pctrl->context.communities;
	क्रम (i = 0; i < pctrl->ncommunities; i++) अणु
		काष्ठा पूर्णांकel_community *community = &pctrl->communities[i];
		व्योम __iomem *base;
		अचिन्हित पूर्णांक gpp;

		base = community->regs + community->ie_offset;
		क्रम (gpp = 0; gpp < community->ngpps; gpp++)
			पूर्णांकel_restore_पूर्णांकmask(pctrl, i, base, gpp, communities[i].पूर्णांकmask[gpp]);

		base = community->regs + community->hostown_offset;
		क्रम (gpp = 0; gpp < community->ngpps; gpp++)
			पूर्णांकel_restore_hostown(pctrl, i, base, gpp, communities[i].hostown[gpp]);
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(पूर्णांकel_pinctrl_resume_noirq);
#पूर्ण_अगर

MODULE_AUTHOR("Mathias Nyman <mathias.nyman@linux.intel.com>");
MODULE_AUTHOR("Mika Westerberg <mika.westerberg@linux.intel.com>");
MODULE_DESCRIPTION("Intel pinctrl/GPIO core driver");
MODULE_LICENSE("GPL v2");
