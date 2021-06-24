<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/types.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/kernel.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/of_irq.h>

#समावेश <यंत्र/pmac_feature.h>
#समावेश <यंत्र/pmac_pfunc.h>

#अघोषित DEBUG
#अगर_घोषित DEBUG
#घोषणा DBG(fmt...)	prपूर्णांकk(fmt)
#अन्यथा
#घोषणा DBG(fmt...)
#पूर्ण_अगर

अटल irqवापस_t macio_gpio_irq(पूर्णांक irq, व्योम *data)
अणु
	pmf_करो_irq(data);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक macio_करो_gpio_irq_enable(काष्ठा pmf_function *func)
अणु
	अचिन्हित पूर्णांक irq = irq_of_parse_and_map(func->node, 0);
	अगर (!irq)
		वापस -EINVAL;
	वापस request_irq(irq, macio_gpio_irq, 0, func->node->name, func);
पूर्ण

अटल पूर्णांक macio_करो_gpio_irq_disable(काष्ठा pmf_function *func)
अणु
	अचिन्हित पूर्णांक irq = irq_of_parse_and_map(func->node, 0);
	अगर (!irq)
		वापस -EINVAL;
	मुक्त_irq(irq, func);
	वापस 0;
पूर्ण

अटल पूर्णांक macio_करो_gpio_ग_लिखो(PMF_STD_ARGS, u8 value, u8 mask)
अणु
	u8 __iomem *addr = (u8 __iomem *)func->driver_data;
	अचिन्हित दीर्घ flags;
	u8 पंचांगp;

	/* Check polarity */
	अगर (args && args->count && !args->u[0].v)
		value = ~value;

	/* Toggle the GPIO */
	raw_spin_lock_irqsave(&feature_lock, flags);
	पंचांगp = पढ़ोb(addr);
	पंचांगp = (पंचांगp & ~mask) | (value & mask);
	DBG("Do write 0x%02x to GPIO %pOF (%p)\n",
	    पंचांगp, func->node, addr);
	ग_लिखोb(पंचांगp, addr);
	raw_spin_unlock_irqrestore(&feature_lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक macio_करो_gpio_पढ़ो(PMF_STD_ARGS, u8 mask, पूर्णांक rshअगरt, u8 xor)
अणु
	u8 __iomem *addr = (u8 __iomem *)func->driver_data;
	u32 value;

	/* Check अगर we have room क्रम reply */
	अगर (args == शून्य || args->count == 0 || args->u[0].p == शून्य)
		वापस -EINVAL;

	value = पढ़ोb(addr);
	*args->u[0].p = ((value & mask) >> rshअगरt) ^ xor;

	वापस 0;
पूर्ण

अटल पूर्णांक macio_करो_delay(PMF_STD_ARGS, u32 duration)
अणु
	/* assume we can sleep ! */
	msleep((duration + 999) / 1000);
	वापस 0;
पूर्ण

अटल काष्ठा pmf_handlers macio_gpio_handlers = अणु
	.irq_enable	= macio_करो_gpio_irq_enable,
	.irq_disable	= macio_करो_gpio_irq_disable,
	.ग_लिखो_gpio	= macio_करो_gpio_ग_लिखो,
	.पढ़ो_gpio	= macio_करो_gpio_पढ़ो,
	.delay		= macio_करो_delay,
पूर्ण;

अटल व्योम macio_gpio_init_one(काष्ठा macio_chip *macio)
अणु
	काष्ठा device_node *gparent, *gp;

	/*
	 * Find the "gpio" parent node
	 */

	क्रम_each_child_of_node(macio->of_node, gparent)
		अगर (of_node_name_eq(gparent, "gpio"))
			अवरोध;
	अगर (gparent == शून्य)
		वापस;

	DBG("Installing GPIO functions for macio %pOF\n",
	    macio->of_node);

	/*
	 * Ok, got one, we करोnt need anything special to track them करोwn, so
	 * we just create them all
	 */
	क्रम_each_child_of_node(gparent, gp) अणु
		स्थिर u32 *reg = of_get_property(gp, "reg", शून्य);
		अचिन्हित दीर्घ offset;
		अगर (reg == शून्य)
			जारी;
		offset = *reg;
		/* Deal with old style device-tree. We can safely hard code the
		 * offset क्रम now too even अगर it's a bit gross ...
		 */
		अगर (offset < 0x50)
			offset += 0x50;
		offset += (अचिन्हित दीर्घ)macio->base;
		pmf_रेजिस्टर_driver(gp, &macio_gpio_handlers, (व्योम *)offset);
	पूर्ण

	DBG("Calling initial GPIO functions for macio %pOF\n",
	    macio->of_node);

	/* And now we run all the init ones */
	क्रम_each_child_of_node(gparent, gp)
		pmf_करो_functions(gp, शून्य, 0, PMF_FLAGS_ON_INIT, शून्य);

	/* Note: We करो not at this poपूर्णांक implement the "at sleep" or "at wake"
	 * functions. I yet to find any क्रम GPIOs anyway
	 */
पूर्ण

अटल पूर्णांक macio_करो_ग_लिखो_reg32(PMF_STD_ARGS, u32 offset, u32 value, u32 mask)
अणु
	काष्ठा macio_chip *macio = func->driver_data;
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&feature_lock, flags);
	MACIO_OUT32(offset, (MACIO_IN32(offset) & ~mask) | (value & mask));
	raw_spin_unlock_irqrestore(&feature_lock, flags);
	वापस 0;
पूर्ण

अटल पूर्णांक macio_करो_पढ़ो_reg32(PMF_STD_ARGS, u32 offset)
अणु
	काष्ठा macio_chip *macio = func->driver_data;

	/* Check अगर we have room क्रम reply */
	अगर (args == शून्य || args->count == 0 || args->u[0].p == शून्य)
		वापस -EINVAL;

	*args->u[0].p = MACIO_IN32(offset);
	वापस 0;
पूर्ण

अटल पूर्णांक macio_करो_ग_लिखो_reg8(PMF_STD_ARGS, u32 offset, u8 value, u8 mask)
अणु
	काष्ठा macio_chip *macio = func->driver_data;
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&feature_lock, flags);
	MACIO_OUT8(offset, (MACIO_IN8(offset) & ~mask) | (value & mask));
	raw_spin_unlock_irqrestore(&feature_lock, flags);
	वापस 0;
पूर्ण

अटल पूर्णांक macio_करो_पढ़ो_reg8(PMF_STD_ARGS, u32 offset)
अणु
	काष्ठा macio_chip *macio = func->driver_data;

	/* Check अगर we have room क्रम reply */
	अगर (args == शून्य || args->count == 0 || args->u[0].p == शून्य)
		वापस -EINVAL;

	*((u8 *)(args->u[0].p)) = MACIO_IN8(offset);
	वापस 0;
पूर्ण

अटल पूर्णांक macio_करो_पढ़ो_reg32_msrx(PMF_STD_ARGS, u32 offset, u32 mask,
				    u32 shअगरt, u32 xor)
अणु
	काष्ठा macio_chip *macio = func->driver_data;

	/* Check अगर we have room क्रम reply */
	अगर (args == शून्य || args->count == 0 || args->u[0].p == शून्य)
		वापस -EINVAL;

	*args->u[0].p = ((MACIO_IN32(offset) & mask) >> shअगरt) ^ xor;
	वापस 0;
पूर्ण

अटल पूर्णांक macio_करो_पढ़ो_reg8_msrx(PMF_STD_ARGS, u32 offset, u32 mask,
				   u32 shअगरt, u32 xor)
अणु
	काष्ठा macio_chip *macio = func->driver_data;

	/* Check अगर we have room क्रम reply */
	अगर (args == शून्य || args->count == 0 || args->u[0].p == शून्य)
		वापस -EINVAL;

	*((u8 *)(args->u[0].p)) = ((MACIO_IN8(offset) & mask) >> shअगरt) ^ xor;
	वापस 0;
पूर्ण

अटल पूर्णांक macio_करो_ग_लिखो_reg32_slm(PMF_STD_ARGS, u32 offset, u32 shअगरt,
				    u32 mask)
अणु
	काष्ठा macio_chip *macio = func->driver_data;
	अचिन्हित दीर्घ flags;
	u32 पंचांगp, val;

	/* Check args */
	अगर (args == शून्य || args->count == 0)
		वापस -EINVAL;

	raw_spin_lock_irqsave(&feature_lock, flags);
	पंचांगp = MACIO_IN32(offset);
	val = args->u[0].v << shअगरt;
	पंचांगp = (पंचांगp & ~mask) | (val & mask);
	MACIO_OUT32(offset, पंचांगp);
	raw_spin_unlock_irqrestore(&feature_lock, flags);
	वापस 0;
पूर्ण

अटल पूर्णांक macio_करो_ग_लिखो_reg8_slm(PMF_STD_ARGS, u32 offset, u32 shअगरt,
				   u32 mask)
अणु
	काष्ठा macio_chip *macio = func->driver_data;
	अचिन्हित दीर्घ flags;
	u32 पंचांगp, val;

	/* Check args */
	अगर (args == शून्य || args->count == 0)
		वापस -EINVAL;

	raw_spin_lock_irqsave(&feature_lock, flags);
	पंचांगp = MACIO_IN8(offset);
	val = args->u[0].v << shअगरt;
	पंचांगp = (पंचांगp & ~mask) | (val & mask);
	MACIO_OUT8(offset, पंचांगp);
	raw_spin_unlock_irqrestore(&feature_lock, flags);
	वापस 0;
पूर्ण

अटल काष्ठा pmf_handlers macio_mmio_handlers = अणु
	.ग_लिखो_reg32		= macio_करो_ग_लिखो_reg32,
	.पढ़ो_reg32		= macio_करो_पढ़ो_reg32,
	.ग_लिखो_reg8		= macio_करो_ग_लिखो_reg8,
	.पढ़ो_reg8		= macio_करो_पढ़ो_reg8,
	.पढ़ो_reg32_msrx	= macio_करो_पढ़ो_reg32_msrx,
	.पढ़ो_reg8_msrx		= macio_करो_पढ़ो_reg8_msrx,
	.ग_लिखो_reg32_slm	= macio_करो_ग_लिखो_reg32_slm,
	.ग_लिखो_reg8_slm		= macio_करो_ग_लिखो_reg8_slm,
	.delay			= macio_करो_delay,
पूर्ण;

अटल व्योम macio_mmio_init_one(काष्ठा macio_chip *macio)
अणु
	DBG("Installing MMIO functions for macio %pOF\n",
	    macio->of_node);

	pmf_रेजिस्टर_driver(macio->of_node, &macio_mmio_handlers, macio);
पूर्ण

अटल काष्ठा device_node *unin_hwघड़ी;

अटल पूर्णांक unin_करो_ग_लिखो_reg32(PMF_STD_ARGS, u32 offset, u32 value, u32 mask)
अणु
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&feature_lock, flags);
	/* This is fairly bogus in darwin, but it should work क्रम our needs
	 * implemeted that way:
	 */
	UN_OUT(offset, (UN_IN(offset) & ~mask) | (value & mask));
	raw_spin_unlock_irqrestore(&feature_lock, flags);
	वापस 0;
पूर्ण


अटल काष्ठा pmf_handlers unin_mmio_handlers = अणु
	.ग_लिखो_reg32		= unin_करो_ग_लिखो_reg32,
	.delay			= macio_करो_delay,
पूर्ण;

अटल व्योम uninorth_install_pfunc(व्योम)
अणु
	काष्ठा device_node *np;

	DBG("Installing functions for UniN %pOF\n",
	    uninorth_node);

	/*
	 * Install handlers क्रम the bridge itself
	 */
	pmf_रेजिस्टर_driver(uninorth_node, &unin_mmio_handlers, शून्य);
	pmf_करो_functions(uninorth_node, शून्य, 0, PMF_FLAGS_ON_INIT, शून्य);


	/*
	 * Install handlers क्रम the hwघड़ी child अगर any
	 */
	क्रम (np = शून्य; (np = of_get_next_child(uninorth_node, np)) != शून्य;)
		अगर (of_node_name_eq(np, "hw-clock")) अणु
			unin_hwघड़ी = np;
			अवरोध;
		पूर्ण
	अगर (unin_hwघड़ी) अणु
		DBG("Installing functions for UniN clock %pOF\n",
		    unin_hwघड़ी);
		pmf_रेजिस्टर_driver(unin_hwघड़ी, &unin_mmio_handlers, शून्य);
		pmf_करो_functions(unin_hwघड़ी, शून्य, 0, PMF_FLAGS_ON_INIT,
				 शून्य);
	पूर्ण
पूर्ण

/* We export this as the SMP code might init us early */
पूर्णांक __init pmac_pfunc_base_install(व्योम)
अणु
	अटल पूर्णांक pfbase_inited;
	पूर्णांक i;

	अगर (pfbase_inited)
		वापस 0;
	pfbase_inited = 1;

	अगर (!machine_is(घातermac))
		वापस 0;

	DBG("Installing base platform functions...\n");

	/*
	 * Locate mac-io chips and install handlers
	 */
	क्रम (i = 0 ; i < MAX_MACIO_CHIPS; i++) अणु
		अगर (macio_chips[i].of_node) अणु
			macio_mmio_init_one(&macio_chips[i]);
			macio_gpio_init_one(&macio_chips[i]);
		पूर्ण
	पूर्ण

	/*
	 * Install handlers क्रम northbridge and direct mapped hwघड़ी
	 * अगर any. We करो not implement the config space access callback
	 * which is only ever used क्रम functions that we करो not call in
	 * the current driver (enabling/disabling cells in U2, mostly used
	 * to restore the PCI settings, we करो that dअगरferently)
	 */
	अगर (uninorth_node && uninorth_base)
		uninorth_install_pfunc();

	DBG("All base functions installed\n");

	वापस 0;
पूर्ण
machine_arch_initcall(घातermac, pmac_pfunc_base_install);

#अगर_घोषित CONFIG_PM

/* Those can be called by pmac_feature. Ultimately, I should use a sysdev
 * or a device, but क्रम now, that's good enough until I sort out some
 * ordering issues. Also, we करो not bother with GPIOs, as so far I yet have
 * to see a हाल where a GPIO function has the on-suspend or on-resume bit
 */
व्योम pmac_pfunc_base_suspend(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0 ; i < MAX_MACIO_CHIPS; i++) अणु
		अगर (macio_chips[i].of_node)
			pmf_करो_functions(macio_chips[i].of_node, शून्य, 0,
					 PMF_FLAGS_ON_SLEEP, शून्य);
	पूर्ण
	अगर (uninorth_node)
		pmf_करो_functions(uninorth_node, शून्य, 0,
				 PMF_FLAGS_ON_SLEEP, शून्य);
	अगर (unin_hwघड़ी)
		pmf_करो_functions(unin_hwघड़ी, शून्य, 0,
				 PMF_FLAGS_ON_SLEEP, शून्य);
पूर्ण

व्योम pmac_pfunc_base_resume(व्योम)
अणु
	पूर्णांक i;

	अगर (unin_hwघड़ी)
		pmf_करो_functions(unin_hwघड़ी, शून्य, 0,
				 PMF_FLAGS_ON_WAKE, शून्य);
	अगर (uninorth_node)
		pmf_करो_functions(uninorth_node, शून्य, 0,
				 PMF_FLAGS_ON_WAKE, शून्य);
	क्रम (i = 0 ; i < MAX_MACIO_CHIPS; i++) अणु
		अगर (macio_chips[i].of_node)
			pmf_करो_functions(macio_chips[i].of_node, शून्य, 0,
					 PMF_FLAGS_ON_WAKE, शून्य);
	पूर्ण
पूर्ण

#पूर्ण_अगर /* CONFIG_PM */
