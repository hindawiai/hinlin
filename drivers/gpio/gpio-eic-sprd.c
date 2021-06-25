<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2018 Spपढ़ोtrum Communications Inc.
 * Copyright (C) 2018 Linaro Ltd.
 */

#समावेश <linux/bitops.h>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/spinlock.h>

/* EIC रेजिस्टरs definition */
#घोषणा SPRD_EIC_DBNC_DATA		0x0
#घोषणा SPRD_EIC_DBNC_DMSK		0x4
#घोषणा SPRD_EIC_DBNC_IEV		0x14
#घोषणा SPRD_EIC_DBNC_IE		0x18
#घोषणा SPRD_EIC_DBNC_RIS		0x1c
#घोषणा SPRD_EIC_DBNC_MIS		0x20
#घोषणा SPRD_EIC_DBNC_IC		0x24
#घोषणा SPRD_EIC_DBNC_TRIG		0x28
#घोषणा SPRD_EIC_DBNC_CTRL0		0x40

#घोषणा SPRD_EIC_LATCH_INTEN		0x0
#घोषणा SPRD_EIC_LATCH_INTRAW		0x4
#घोषणा SPRD_EIC_LATCH_INTMSK		0x8
#घोषणा SPRD_EIC_LATCH_INTCLR		0xc
#घोषणा SPRD_EIC_LATCH_INTPOL		0x10
#घोषणा SPRD_EIC_LATCH_INTMODE		0x14

#घोषणा SPRD_EIC_ASYNC_INTIE		0x0
#घोषणा SPRD_EIC_ASYNC_INTRAW		0x4
#घोषणा SPRD_EIC_ASYNC_INTMSK		0x8
#घोषणा SPRD_EIC_ASYNC_INTCLR		0xc
#घोषणा SPRD_EIC_ASYNC_INTMODE		0x10
#घोषणा SPRD_EIC_ASYNC_INTBOTH		0x14
#घोषणा SPRD_EIC_ASYNC_INTPOL		0x18
#घोषणा SPRD_EIC_ASYNC_DATA		0x1c

#घोषणा SPRD_EIC_SYNC_INTIE		0x0
#घोषणा SPRD_EIC_SYNC_INTRAW		0x4
#घोषणा SPRD_EIC_SYNC_INTMSK		0x8
#घोषणा SPRD_EIC_SYNC_INTCLR		0xc
#घोषणा SPRD_EIC_SYNC_INTMODE		0x10
#घोषणा SPRD_EIC_SYNC_INTBOTH		0x14
#घोषणा SPRD_EIC_SYNC_INTPOL		0x18
#घोषणा SPRD_EIC_SYNC_DATA		0x1c

/*
 * The digital-chip EIC controller can support maximum 3 banks, and each bank
 * contains 8 EICs.
 */
#घोषणा SPRD_EIC_MAX_BANK		3
#घोषणा SPRD_EIC_PER_BANK_NR		8
#घोषणा SPRD_EIC_DATA_MASK		GENMASK(7, 0)
#घोषणा SPRD_EIC_BIT(x)			((x) & (SPRD_EIC_PER_BANK_NR - 1))
#घोषणा SPRD_EIC_DBNC_MASK		GENMASK(11, 0)

/*
 * The Spपढ़ोtrum EIC (बाह्यal पूर्णांकerrupt controller) can be used only in
 * input mode to generate पूर्णांकerrupts अगर detecting input संकेतs.
 *
 * The Spपढ़ोtrum digital-chip EIC controller contains 4 sub-modules:
 * debounce EIC, latch EIC, async EIC and sync EIC,
 *
 * The debounce EIC is used to capture the input संकेतs' stable status
 * (millisecond resolution) and a single-trigger mechanism is पूर्णांकroduced
 * पूर्णांकo this sub-module to enhance the input event detection reliability.
 * The debounce range is from 1ms to 4s with a step size of 1ms.
 *
 * The latch EIC is used to latch some special घातer करोwn संकेतs and
 * generate पूर्णांकerrupts, since the latch EIC करोes not depend on the APB घड़ी
 * to capture संकेतs.
 *
 * The async EIC uses a 32k घड़ी to capture the लघु संकेतs (microsecond
 * resolution) to generate पूर्णांकerrupts by level or edge trigger.
 *
 * The EIC-sync is similar with GPIO's input function, which is a synchronized
 * संकेत input रेजिस्टर.
 */
क्रमागत sprd_eic_type अणु
	SPRD_EIC_DEBOUNCE,
	SPRD_EIC_LATCH,
	SPRD_EIC_ASYNC,
	SPRD_EIC_SYNC,
	SPRD_EIC_MAX,
पूर्ण;

काष्ठा sprd_eic अणु
	काष्ठा gpio_chip chip;
	काष्ठा irq_chip पूर्णांकc;
	व्योम __iomem *base[SPRD_EIC_MAX_BANK];
	क्रमागत sprd_eic_type type;
	spinlock_t lock;
	पूर्णांक irq;
पूर्ण;

काष्ठा sprd_eic_variant_data अणु
	क्रमागत sprd_eic_type type;
	u32 num_eics;
पूर्ण;

अटल स्थिर अक्षर *sprd_eic_label_name[SPRD_EIC_MAX] = अणु
	"eic-debounce", "eic-latch", "eic-async",
	"eic-sync",
पूर्ण;

अटल स्थिर काष्ठा sprd_eic_variant_data sc9860_eic_dbnc_data = अणु
	.type = SPRD_EIC_DEBOUNCE,
	.num_eics = 8,
पूर्ण;

अटल स्थिर काष्ठा sprd_eic_variant_data sc9860_eic_latch_data = अणु
	.type = SPRD_EIC_LATCH,
	.num_eics = 8,
पूर्ण;

अटल स्थिर काष्ठा sprd_eic_variant_data sc9860_eic_async_data = अणु
	.type = SPRD_EIC_ASYNC,
	.num_eics = 8,
पूर्ण;

अटल स्थिर काष्ठा sprd_eic_variant_data sc9860_eic_sync_data = अणु
	.type = SPRD_EIC_SYNC,
	.num_eics = 8,
पूर्ण;

अटल अंतरभूत व्योम __iomem *sprd_eic_offset_base(काष्ठा sprd_eic *sprd_eic,
						 अचिन्हित पूर्णांक bank)
अणु
	अगर (bank >= SPRD_EIC_MAX_BANK)
		वापस शून्य;

	वापस sprd_eic->base[bank];
पूर्ण

अटल व्योम sprd_eic_update(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset,
			    u16 reg, अचिन्हित पूर्णांक val)
अणु
	काष्ठा sprd_eic *sprd_eic = gpiochip_get_data(chip);
	व्योम __iomem *base =
		sprd_eic_offset_base(sprd_eic, offset / SPRD_EIC_PER_BANK_NR);
	अचिन्हित दीर्घ flags;
	u32 पंचांगp;

	spin_lock_irqsave(&sprd_eic->lock, flags);
	पंचांगp = पढ़ोl_relaxed(base + reg);

	अगर (val)
		पंचांगp |= BIT(SPRD_EIC_BIT(offset));
	अन्यथा
		पंचांगp &= ~BIT(SPRD_EIC_BIT(offset));

	ग_लिखोl_relaxed(पंचांगp, base + reg);
	spin_unlock_irqrestore(&sprd_eic->lock, flags);
पूर्ण

अटल पूर्णांक sprd_eic_पढ़ो(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset, u16 reg)
अणु
	काष्ठा sprd_eic *sprd_eic = gpiochip_get_data(chip);
	व्योम __iomem *base =
		sprd_eic_offset_base(sprd_eic, offset / SPRD_EIC_PER_BANK_NR);

	वापस !!(पढ़ोl_relaxed(base + reg) & BIT(SPRD_EIC_BIT(offset)));
पूर्ण

अटल पूर्णांक sprd_eic_request(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset)
अणु
	sprd_eic_update(chip, offset, SPRD_EIC_DBNC_DMSK, 1);
	वापस 0;
पूर्ण

अटल व्योम sprd_eic_मुक्त(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset)
अणु
	sprd_eic_update(chip, offset, SPRD_EIC_DBNC_DMSK, 0);
पूर्ण

अटल पूर्णांक sprd_eic_get(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset)
अणु
	काष्ठा sprd_eic *sprd_eic = gpiochip_get_data(chip);

	चयन (sprd_eic->type) अणु
	हाल SPRD_EIC_DEBOUNCE:
		वापस sprd_eic_पढ़ो(chip, offset, SPRD_EIC_DBNC_DATA);
	हाल SPRD_EIC_ASYNC:
		वापस sprd_eic_पढ़ो(chip, offset, SPRD_EIC_ASYNC_DATA);
	हाल SPRD_EIC_SYNC:
		वापस sprd_eic_पढ़ो(chip, offset, SPRD_EIC_SYNC_DATA);
	शेष:
		वापस -ENOTSUPP;
	पूर्ण
पूर्ण

अटल पूर्णांक sprd_eic_direction_input(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset)
अणु
	/* EICs are always input, nothing need to करो here. */
	वापस 0;
पूर्ण

अटल व्योम sprd_eic_set(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset, पूर्णांक value)
अणु
	/* EICs are always input, nothing need to करो here. */
पूर्ण

अटल पूर्णांक sprd_eic_set_debounce(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset,
				 अचिन्हित पूर्णांक debounce)
अणु
	काष्ठा sprd_eic *sprd_eic = gpiochip_get_data(chip);
	व्योम __iomem *base =
		sprd_eic_offset_base(sprd_eic, offset / SPRD_EIC_PER_BANK_NR);
	u32 reg = SPRD_EIC_DBNC_CTRL0 + SPRD_EIC_BIT(offset) * 0x4;
	u32 value = पढ़ोl_relaxed(base + reg) & ~SPRD_EIC_DBNC_MASK;

	value |= (debounce / 1000) & SPRD_EIC_DBNC_MASK;
	ग_लिखोl_relaxed(value, base + reg);

	वापस 0;
पूर्ण

अटल पूर्णांक sprd_eic_set_config(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset,
			       अचिन्हित दीर्घ config)
अणु
	अचिन्हित दीर्घ param = pinconf_to_config_param(config);
	u32 arg = pinconf_to_config_argument(config);

	अगर (param == PIN_CONFIG_INPUT_DEBOUNCE)
		वापस sprd_eic_set_debounce(chip, offset, arg);

	वापस -ENOTSUPP;
पूर्ण

अटल व्योम sprd_eic_irq_mask(काष्ठा irq_data *data)
अणु
	काष्ठा gpio_chip *chip = irq_data_get_irq_chip_data(data);
	काष्ठा sprd_eic *sprd_eic = gpiochip_get_data(chip);
	u32 offset = irqd_to_hwirq(data);

	चयन (sprd_eic->type) अणु
	हाल SPRD_EIC_DEBOUNCE:
		sprd_eic_update(chip, offset, SPRD_EIC_DBNC_IE, 0);
		sprd_eic_update(chip, offset, SPRD_EIC_DBNC_TRIG, 0);
		अवरोध;
	हाल SPRD_EIC_LATCH:
		sprd_eic_update(chip, offset, SPRD_EIC_LATCH_INTEN, 0);
		अवरोध;
	हाल SPRD_EIC_ASYNC:
		sprd_eic_update(chip, offset, SPRD_EIC_ASYNC_INTIE, 0);
		अवरोध;
	हाल SPRD_EIC_SYNC:
		sprd_eic_update(chip, offset, SPRD_EIC_SYNC_INTIE, 0);
		अवरोध;
	शेष:
		dev_err(chip->parent, "Unsupported EIC type.\n");
	पूर्ण
पूर्ण

अटल व्योम sprd_eic_irq_unmask(काष्ठा irq_data *data)
अणु
	काष्ठा gpio_chip *chip = irq_data_get_irq_chip_data(data);
	काष्ठा sprd_eic *sprd_eic = gpiochip_get_data(chip);
	u32 offset = irqd_to_hwirq(data);

	चयन (sprd_eic->type) अणु
	हाल SPRD_EIC_DEBOUNCE:
		sprd_eic_update(chip, offset, SPRD_EIC_DBNC_IE, 1);
		sprd_eic_update(chip, offset, SPRD_EIC_DBNC_TRIG, 1);
		अवरोध;
	हाल SPRD_EIC_LATCH:
		sprd_eic_update(chip, offset, SPRD_EIC_LATCH_INTEN, 1);
		अवरोध;
	हाल SPRD_EIC_ASYNC:
		sprd_eic_update(chip, offset, SPRD_EIC_ASYNC_INTIE, 1);
		अवरोध;
	हाल SPRD_EIC_SYNC:
		sprd_eic_update(chip, offset, SPRD_EIC_SYNC_INTIE, 1);
		अवरोध;
	शेष:
		dev_err(chip->parent, "Unsupported EIC type.\n");
	पूर्ण
पूर्ण

अटल व्योम sprd_eic_irq_ack(काष्ठा irq_data *data)
अणु
	काष्ठा gpio_chip *chip = irq_data_get_irq_chip_data(data);
	काष्ठा sprd_eic *sprd_eic = gpiochip_get_data(chip);
	u32 offset = irqd_to_hwirq(data);

	चयन (sprd_eic->type) अणु
	हाल SPRD_EIC_DEBOUNCE:
		sprd_eic_update(chip, offset, SPRD_EIC_DBNC_IC, 1);
		अवरोध;
	हाल SPRD_EIC_LATCH:
		sprd_eic_update(chip, offset, SPRD_EIC_LATCH_INTCLR, 1);
		अवरोध;
	हाल SPRD_EIC_ASYNC:
		sprd_eic_update(chip, offset, SPRD_EIC_ASYNC_INTCLR, 1);
		अवरोध;
	हाल SPRD_EIC_SYNC:
		sprd_eic_update(chip, offset, SPRD_EIC_SYNC_INTCLR, 1);
		अवरोध;
	शेष:
		dev_err(chip->parent, "Unsupported EIC type.\n");
	पूर्ण
पूर्ण

अटल पूर्णांक sprd_eic_irq_set_type(काष्ठा irq_data *data, अचिन्हित पूर्णांक flow_type)
अणु
	काष्ठा gpio_chip *chip = irq_data_get_irq_chip_data(data);
	काष्ठा sprd_eic *sprd_eic = gpiochip_get_data(chip);
	u32 offset = irqd_to_hwirq(data);
	पूर्णांक state;

	चयन (sprd_eic->type) अणु
	हाल SPRD_EIC_DEBOUNCE:
		चयन (flow_type) अणु
		हाल IRQ_TYPE_LEVEL_HIGH:
			sprd_eic_update(chip, offset, SPRD_EIC_DBNC_IEV, 1);
			अवरोध;
		हाल IRQ_TYPE_LEVEL_LOW:
			sprd_eic_update(chip, offset, SPRD_EIC_DBNC_IEV, 0);
			अवरोध;
		हाल IRQ_TYPE_EDGE_RISING:
		हाल IRQ_TYPE_EDGE_FALLING:
		हाल IRQ_TYPE_EDGE_BOTH:
			state = sprd_eic_get(chip, offset);
			अगर (state)
				sprd_eic_update(chip, offset,
						SPRD_EIC_DBNC_IEV, 0);
			अन्यथा
				sprd_eic_update(chip, offset,
						SPRD_EIC_DBNC_IEV, 1);
			अवरोध;
		शेष:
			वापस -ENOTSUPP;
		पूर्ण

		irq_set_handler_locked(data, handle_level_irq);
		अवरोध;
	हाल SPRD_EIC_LATCH:
		चयन (flow_type) अणु
		हाल IRQ_TYPE_LEVEL_HIGH:
			sprd_eic_update(chip, offset, SPRD_EIC_LATCH_INTPOL, 0);
			अवरोध;
		हाल IRQ_TYPE_LEVEL_LOW:
			sprd_eic_update(chip, offset, SPRD_EIC_LATCH_INTPOL, 1);
			अवरोध;
		हाल IRQ_TYPE_EDGE_RISING:
		हाल IRQ_TYPE_EDGE_FALLING:
		हाल IRQ_TYPE_EDGE_BOTH:
			state = sprd_eic_get(chip, offset);
			अगर (state)
				sprd_eic_update(chip, offset,
						SPRD_EIC_LATCH_INTPOL, 0);
			अन्यथा
				sprd_eic_update(chip, offset,
						SPRD_EIC_LATCH_INTPOL, 1);
			अवरोध;
		शेष:
			वापस -ENOTSUPP;
		पूर्ण

		irq_set_handler_locked(data, handle_level_irq);
		अवरोध;
	हाल SPRD_EIC_ASYNC:
		चयन (flow_type) अणु
		हाल IRQ_TYPE_EDGE_RISING:
			sprd_eic_update(chip, offset, SPRD_EIC_ASYNC_INTBOTH, 0);
			sprd_eic_update(chip, offset, SPRD_EIC_ASYNC_INTMODE, 0);
			sprd_eic_update(chip, offset, SPRD_EIC_ASYNC_INTPOL, 1);
			irq_set_handler_locked(data, handle_edge_irq);
			अवरोध;
		हाल IRQ_TYPE_EDGE_FALLING:
			sprd_eic_update(chip, offset, SPRD_EIC_ASYNC_INTBOTH, 0);
			sprd_eic_update(chip, offset, SPRD_EIC_ASYNC_INTMODE, 0);
			sprd_eic_update(chip, offset, SPRD_EIC_ASYNC_INTPOL, 0);
			irq_set_handler_locked(data, handle_edge_irq);
			अवरोध;
		हाल IRQ_TYPE_EDGE_BOTH:
			sprd_eic_update(chip, offset, SPRD_EIC_ASYNC_INTMODE, 0);
			sprd_eic_update(chip, offset, SPRD_EIC_ASYNC_INTBOTH, 1);
			irq_set_handler_locked(data, handle_edge_irq);
			अवरोध;
		हाल IRQ_TYPE_LEVEL_HIGH:
			sprd_eic_update(chip, offset, SPRD_EIC_ASYNC_INTBOTH, 0);
			sprd_eic_update(chip, offset, SPRD_EIC_ASYNC_INTMODE, 1);
			sprd_eic_update(chip, offset, SPRD_EIC_ASYNC_INTPOL, 1);
			irq_set_handler_locked(data, handle_level_irq);
			अवरोध;
		हाल IRQ_TYPE_LEVEL_LOW:
			sprd_eic_update(chip, offset, SPRD_EIC_ASYNC_INTBOTH, 0);
			sprd_eic_update(chip, offset, SPRD_EIC_ASYNC_INTMODE, 1);
			sprd_eic_update(chip, offset, SPRD_EIC_ASYNC_INTPOL, 0);
			irq_set_handler_locked(data, handle_level_irq);
			अवरोध;
		शेष:
			वापस -ENOTSUPP;
		पूर्ण
		अवरोध;
	हाल SPRD_EIC_SYNC:
		चयन (flow_type) अणु
		हाल IRQ_TYPE_EDGE_RISING:
			sprd_eic_update(chip, offset, SPRD_EIC_SYNC_INTBOTH, 0);
			sprd_eic_update(chip, offset, SPRD_EIC_SYNC_INTMODE, 0);
			sprd_eic_update(chip, offset, SPRD_EIC_SYNC_INTPOL, 1);
			irq_set_handler_locked(data, handle_edge_irq);
			अवरोध;
		हाल IRQ_TYPE_EDGE_FALLING:
			sprd_eic_update(chip, offset, SPRD_EIC_SYNC_INTBOTH, 0);
			sprd_eic_update(chip, offset, SPRD_EIC_SYNC_INTMODE, 0);
			sprd_eic_update(chip, offset, SPRD_EIC_SYNC_INTPOL, 0);
			irq_set_handler_locked(data, handle_edge_irq);
			अवरोध;
		हाल IRQ_TYPE_EDGE_BOTH:
			sprd_eic_update(chip, offset, SPRD_EIC_SYNC_INTMODE, 0);
			sprd_eic_update(chip, offset, SPRD_EIC_SYNC_INTBOTH, 1);
			irq_set_handler_locked(data, handle_edge_irq);
			अवरोध;
		हाल IRQ_TYPE_LEVEL_HIGH:
			sprd_eic_update(chip, offset, SPRD_EIC_SYNC_INTBOTH, 0);
			sprd_eic_update(chip, offset, SPRD_EIC_SYNC_INTMODE, 1);
			sprd_eic_update(chip, offset, SPRD_EIC_SYNC_INTPOL, 1);
			irq_set_handler_locked(data, handle_level_irq);
			अवरोध;
		हाल IRQ_TYPE_LEVEL_LOW:
			sprd_eic_update(chip, offset, SPRD_EIC_SYNC_INTBOTH, 0);
			sprd_eic_update(chip, offset, SPRD_EIC_SYNC_INTMODE, 1);
			sprd_eic_update(chip, offset, SPRD_EIC_SYNC_INTPOL, 0);
			irq_set_handler_locked(data, handle_level_irq);
			अवरोध;
		शेष:
			वापस -ENOTSUPP;
		पूर्ण
		अवरोध;
	शेष:
		dev_err(chip->parent, "Unsupported EIC type.\n");
		वापस -ENOTSUPP;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम sprd_eic_toggle_trigger(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक irq,
				    अचिन्हित पूर्णांक offset)
अणु
	काष्ठा sprd_eic *sprd_eic = gpiochip_get_data(chip);
	काष्ठा irq_data *data = irq_get_irq_data(irq);
	u32 trigger = irqd_get_trigger_type(data);
	पूर्णांक state, post_state;

	/*
	 * The debounce EIC and latch EIC can only support level trigger, so we
	 * can toggle the level trigger to emulate the edge trigger.
	 */
	अगर ((sprd_eic->type != SPRD_EIC_DEBOUNCE &&
	     sprd_eic->type != SPRD_EIC_LATCH) ||
	    !(trigger & IRQ_TYPE_EDGE_BOTH))
		वापस;

	sprd_eic_irq_mask(data);
	state = sprd_eic_get(chip, offset);

retry:
	चयन (sprd_eic->type) अणु
	हाल SPRD_EIC_DEBOUNCE:
		अगर (state)
			sprd_eic_update(chip, offset, SPRD_EIC_DBNC_IEV, 0);
		अन्यथा
			sprd_eic_update(chip, offset, SPRD_EIC_DBNC_IEV, 1);
		अवरोध;
	हाल SPRD_EIC_LATCH:
		अगर (state)
			sprd_eic_update(chip, offset, SPRD_EIC_LATCH_INTPOL, 0);
		अन्यथा
			sprd_eic_update(chip, offset, SPRD_EIC_LATCH_INTPOL, 1);
		अवरोध;
	शेष:
		sprd_eic_irq_unmask(data);
		वापस;
	पूर्ण

	post_state = sprd_eic_get(chip, offset);
	अगर (state != post_state) अणु
		dev_warn(chip->parent, "EIC level was changed.\n");
		state = post_state;
		जाओ retry;
	पूर्ण

	sprd_eic_irq_unmask(data);
पूर्ण

अटल पूर्णांक sprd_eic_match_chip_by_type(काष्ठा gpio_chip *chip, व्योम *data)
अणु
	क्रमागत sprd_eic_type type = *(क्रमागत sprd_eic_type *)data;

	वापस !म_भेद(chip->label, sprd_eic_label_name[type]);
पूर्ण

अटल व्योम sprd_eic_handle_one_type(काष्ठा gpio_chip *chip)
अणु
	काष्ठा sprd_eic *sprd_eic = gpiochip_get_data(chip);
	u32 bank, n, girq;

	क्रम (bank = 0; bank * SPRD_EIC_PER_BANK_NR < chip->ngpio; bank++) अणु
		व्योम __iomem *base = sprd_eic_offset_base(sprd_eic, bank);
		अचिन्हित दीर्घ reg;

		चयन (sprd_eic->type) अणु
		हाल SPRD_EIC_DEBOUNCE:
			reg = पढ़ोl_relaxed(base + SPRD_EIC_DBNC_MIS) &
				SPRD_EIC_DATA_MASK;
			अवरोध;
		हाल SPRD_EIC_LATCH:
			reg = पढ़ोl_relaxed(base + SPRD_EIC_LATCH_INTMSK) &
				SPRD_EIC_DATA_MASK;
			अवरोध;
		हाल SPRD_EIC_ASYNC:
			reg = पढ़ोl_relaxed(base + SPRD_EIC_ASYNC_INTMSK) &
				SPRD_EIC_DATA_MASK;
			अवरोध;
		हाल SPRD_EIC_SYNC:
			reg = पढ़ोl_relaxed(base + SPRD_EIC_SYNC_INTMSK) &
				SPRD_EIC_DATA_MASK;
			अवरोध;
		शेष:
			dev_err(chip->parent, "Unsupported EIC type.\n");
			वापस;
		पूर्ण

		क्रम_each_set_bit(n, &reg, SPRD_EIC_PER_BANK_NR) अणु
			u32 offset = bank * SPRD_EIC_PER_BANK_NR + n;

			girq = irq_find_mapping(chip->irq.करोमुख्य, offset);

			generic_handle_irq(girq);
			sprd_eic_toggle_trigger(chip, girq, offset);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम sprd_eic_irq_handler(काष्ठा irq_desc *desc)
अणु
	काष्ठा irq_chip *ic = irq_desc_get_chip(desc);
	काष्ठा gpio_chip *chip;
	क्रमागत sprd_eic_type type;

	chained_irq_enter(ic, desc);

	/*
	 * Since the digital-chip EIC 4 sub-modules (debounce, latch, async
	 * and sync) share one same पूर्णांकerrupt line, we should iterate each
	 * EIC module to check अगर there are EIC पूर्णांकerrupts were triggered.
	 */
	क्रम (type = SPRD_EIC_DEBOUNCE; type < SPRD_EIC_MAX; type++) अणु
		chip = gpiochip_find(&type, sprd_eic_match_chip_by_type);
		अगर (!chip)
			जारी;

		sprd_eic_handle_one_type(chip);
	पूर्ण

	chained_irq_निकास(ic, desc);
पूर्ण

अटल पूर्णांक sprd_eic_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा sprd_eic_variant_data *pdata;
	काष्ठा gpio_irq_chip *irq;
	काष्ठा sprd_eic *sprd_eic;
	काष्ठा resource *res;
	पूर्णांक ret, i;

	pdata = of_device_get_match_data(&pdev->dev);
	अगर (!pdata) अणु
		dev_err(&pdev->dev, "No matching driver data found.\n");
		वापस -EINVAL;
	पूर्ण

	sprd_eic = devm_kzalloc(&pdev->dev, माप(*sprd_eic), GFP_KERNEL);
	अगर (!sprd_eic)
		वापस -ENOMEM;

	spin_lock_init(&sprd_eic->lock);
	sprd_eic->type = pdata->type;

	sprd_eic->irq = platक्रमm_get_irq(pdev, 0);
	अगर (sprd_eic->irq < 0)
		वापस sprd_eic->irq;

	क्रम (i = 0; i < SPRD_EIC_MAX_BANK; i++) अणु
		/*
		 * We can have maximum 3 banks EICs, and each EIC has
		 * its own base address. But some platक्रमm maybe only
		 * have one bank EIC, thus base[1] and base[2] can be
		 * optional.
		 */
		res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, i);
		अगर (!res)
			अवरोध;

		sprd_eic->base[i] = devm_ioremap_resource(&pdev->dev, res);
		अगर (IS_ERR(sprd_eic->base[i]))
			वापस PTR_ERR(sprd_eic->base[i]);
	पूर्ण

	sprd_eic->chip.label = sprd_eic_label_name[sprd_eic->type];
	sprd_eic->chip.ngpio = pdata->num_eics;
	sprd_eic->chip.base = -1;
	sprd_eic->chip.parent = &pdev->dev;
	sprd_eic->chip.of_node = pdev->dev.of_node;
	sprd_eic->chip.direction_input = sprd_eic_direction_input;
	चयन (sprd_eic->type) अणु
	हाल SPRD_EIC_DEBOUNCE:
		sprd_eic->chip.request = sprd_eic_request;
		sprd_eic->chip.मुक्त = sprd_eic_मुक्त;
		sprd_eic->chip.set_config = sprd_eic_set_config;
		sprd_eic->chip.set = sprd_eic_set;
		fallthrough;
	हाल SPRD_EIC_ASYNC:
	हाल SPRD_EIC_SYNC:
		sprd_eic->chip.get = sprd_eic_get;
		अवरोध;
	हाल SPRD_EIC_LATCH:
	शेष:
		अवरोध;
	पूर्ण

	sprd_eic->पूर्णांकc.name = dev_name(&pdev->dev);
	sprd_eic->पूर्णांकc.irq_ack = sprd_eic_irq_ack;
	sprd_eic->पूर्णांकc.irq_mask = sprd_eic_irq_mask;
	sprd_eic->पूर्णांकc.irq_unmask = sprd_eic_irq_unmask;
	sprd_eic->पूर्णांकc.irq_set_type = sprd_eic_irq_set_type;
	sprd_eic->पूर्णांकc.flags = IRQCHIP_SKIP_SET_WAKE;

	irq = &sprd_eic->chip.irq;
	irq->chip = &sprd_eic->पूर्णांकc;
	irq->handler = handle_bad_irq;
	irq->शेष_type = IRQ_TYPE_NONE;
	irq->parent_handler = sprd_eic_irq_handler;
	irq->parent_handler_data = sprd_eic;
	irq->num_parents = 1;
	irq->parents = &sprd_eic->irq;

	ret = devm_gpiochip_add_data(&pdev->dev, &sprd_eic->chip, sprd_eic);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "Could not register gpiochip %d.\n", ret);
		वापस ret;
	पूर्ण

	platक्रमm_set_drvdata(pdev, sprd_eic);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id sprd_eic_of_match[] = अणु
	अणु
		.compatible = "sprd,sc9860-eic-debounce",
		.data = &sc9860_eic_dbnc_data,
	पूर्ण,
	अणु
		.compatible = "sprd,sc9860-eic-latch",
		.data = &sc9860_eic_latch_data,
	पूर्ण,
	अणु
		.compatible = "sprd,sc9860-eic-async",
		.data = &sc9860_eic_async_data,
	पूर्ण,
	अणु
		.compatible = "sprd,sc9860-eic-sync",
		.data = &sc9860_eic_sync_data,
	पूर्ण,
	अणु
		/* end of list */
	पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, sprd_eic_of_match);

अटल काष्ठा platक्रमm_driver sprd_eic_driver = अणु
	.probe = sprd_eic_probe,
	.driver = अणु
		.name = "sprd-eic",
		.of_match_table	= sprd_eic_of_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(sprd_eic_driver);

MODULE_DESCRIPTION("Spreadtrum EIC driver");
MODULE_LICENSE("GPL v2");
