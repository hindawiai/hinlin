<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Based on sound/arm/pxa2xx-ac97.c and sound/soc/pxa/pxa2xx-ac97.c
 * which contain:
 *
 * Author:	Nicolas Pitre
 * Created:	Dec 02, 2004
 * Copyright:	MontaVista Software Inc.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/module.h>
#समावेश <linux/पन.स>
#समावेश <linux/gpपन.स>
#समावेश <linux/of_gpपन.स>

#समावेश <sound/pxa2xx-lib.h>

#समावेश <mach/irqs.h>
#समावेश <mach/regs-ac97.h>
#समावेश <mach/audपन.स>

अटल DEFINE_MUTEX(car_mutex);
अटल DECLARE_WAIT_QUEUE_HEAD(gsr_wq);
अटल अस्थिर दीर्घ gsr_bits;
अटल काष्ठा clk *ac97_clk;
अटल काष्ठा clk *ac97conf_clk;
अटल पूर्णांक reset_gpio;

बाह्य व्योम pxa27x_configure_ac97reset(पूर्णांक reset_gpio, bool to_gpio);

/*
 * Beware PXA27x bugs:
 *
 *   o Slot 12 पढ़ो from modem space will hang controller.
 *   o CDONE, SDONE पूर्णांकerrupt fails after any slot 12 IO.
 *
 * We thereक्रमe have an hybrid approach क्रम रुकोing on SDONE (पूर्णांकerrupt or
 * 1 jअगरfy समयout अगर पूर्णांकerrupt never comes).
 */

पूर्णांक pxa2xx_ac97_पढ़ो(पूर्णांक slot, अचिन्हित लघु reg)
अणु
	पूर्णांक val = -ENODEV;
	अस्थिर u32 *reg_addr;

	अगर (slot > 0)
		वापस -ENODEV;

	mutex_lock(&car_mutex);

	/* set up primary or secondary codec space */
	अगर (cpu_is_pxa25x() && reg == AC97_GPIO_STATUS)
		reg_addr = slot ? &SMC_REG_BASE : &PMC_REG_BASE;
	अन्यथा
		reg_addr = slot ? &SAC_REG_BASE : &PAC_REG_BASE;
	reg_addr += (reg >> 1);

	/* start पढ़ो access across the ac97 link */
	GSR = GSR_CDONE | GSR_SDONE;
	gsr_bits = 0;
	val = (*reg_addr & 0xffff);
	अगर (reg == AC97_GPIO_STATUS)
		जाओ out;
	अगर (रुको_event_समयout(gsr_wq, (GSR | gsr_bits) & GSR_SDONE, 1) <= 0 &&
	    !((GSR | gsr_bits) & GSR_SDONE)) अणु
		prपूर्णांकk(KERN_ERR "%s: read error (ac97_reg=%d GSR=%#lx)\n",
				__func__, reg, GSR | gsr_bits);
		val = -ETIMEDOUT;
		जाओ out;
	पूर्ण

	/* valid data now */
	GSR = GSR_CDONE | GSR_SDONE;
	gsr_bits = 0;
	val = (*reg_addr & 0xffff);
	/* but we've just started another cycle... */
	रुको_event_समयout(gsr_wq, (GSR | gsr_bits) & GSR_SDONE, 1);

out:	mutex_unlock(&car_mutex);
	वापस val;
पूर्ण
EXPORT_SYMBOL_GPL(pxa2xx_ac97_पढ़ो);

पूर्णांक pxa2xx_ac97_ग_लिखो(पूर्णांक slot, अचिन्हित लघु reg, अचिन्हित लघु val)
अणु
	अस्थिर u32 *reg_addr;
	पूर्णांक ret = 0;

	mutex_lock(&car_mutex);

	/* set up primary or secondary codec space */
	अगर (cpu_is_pxa25x() && reg == AC97_GPIO_STATUS)
		reg_addr = slot ? &SMC_REG_BASE : &PMC_REG_BASE;
	अन्यथा
		reg_addr = slot ? &SAC_REG_BASE : &PAC_REG_BASE;
	reg_addr += (reg >> 1);

	GSR = GSR_CDONE | GSR_SDONE;
	gsr_bits = 0;
	*reg_addr = val;
	अगर (रुको_event_समयout(gsr_wq, (GSR | gsr_bits) & GSR_CDONE, 1) <= 0 &&
	    !((GSR | gsr_bits) & GSR_CDONE)) अणु
		prपूर्णांकk(KERN_ERR "%s: write error (ac97_reg=%d GSR=%#lx)\n",
				__func__, reg, GSR | gsr_bits);
		ret = -EIO;
	पूर्ण

	mutex_unlock(&car_mutex);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(pxa2xx_ac97_ग_लिखो);

#अगर_घोषित CONFIG_PXA25x
अटल अंतरभूत व्योम pxa_ac97_warm_pxa25x(व्योम)
अणु
	gsr_bits = 0;

	GCR |= GCR_WARM_RST;
पूर्ण

अटल अंतरभूत व्योम pxa_ac97_cold_pxa25x(व्योम)
अणु
	GCR &=  GCR_COLD_RST;  /* clear everything but nCRST */
	GCR &= ~GCR_COLD_RST;  /* then निश्चित nCRST */

	gsr_bits = 0;

	GCR = GCR_COLD_RST;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_PXA27x
अटल अंतरभूत व्योम pxa_ac97_warm_pxa27x(व्योम)
अणु
	gsr_bits = 0;

	/* warm reset broken on Bulverde, so manually keep AC97 reset high */
	pxa27x_configure_ac97reset(reset_gpio, true);
	udelay(10);
	GCR |= GCR_WARM_RST;
	pxa27x_configure_ac97reset(reset_gpio, false);
	udelay(500);
पूर्ण

अटल अंतरभूत व्योम pxa_ac97_cold_pxa27x(व्योम)
अणु
	GCR &=  GCR_COLD_RST;  /* clear everything but nCRST */
	GCR &= ~GCR_COLD_RST;  /* then निश्चित nCRST */

	gsr_bits = 0;

	/* PXA27x Developers Manual section 13.5.2.2.1 */
	clk_prepare_enable(ac97conf_clk);
	udelay(5);
	clk_disable_unprepare(ac97conf_clk);
	GCR = GCR_COLD_RST | GCR_WARM_RST;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_PXA3xx
अटल अंतरभूत व्योम pxa_ac97_warm_pxa3xx(व्योम)
अणु
	gsr_bits = 0;

	/* Can't use पूर्णांकerrupts */
	GCR |= GCR_WARM_RST;
पूर्ण

अटल अंतरभूत व्योम pxa_ac97_cold_pxa3xx(व्योम)
अणु
	/* Hold CLKBPB क्रम 100us */
	GCR = 0;
	GCR = GCR_CLKBPB;
	udelay(100);
	GCR = 0;

	GCR &=  GCR_COLD_RST;  /* clear everything but nCRST */
	GCR &= ~GCR_COLD_RST;  /* then निश्चित nCRST */

	gsr_bits = 0;

	/* Can't use पूर्णांकerrupts on PXA3xx */
	GCR &= ~(GCR_PRIRDY_IEN|GCR_SECRDY_IEN);

	GCR = GCR_WARM_RST | GCR_COLD_RST;
पूर्ण
#पूर्ण_अगर

bool pxa2xx_ac97_try_warm_reset(व्योम)
अणु
	अचिन्हित दीर्घ gsr;
	अचिन्हित पूर्णांक समयout = 100;

#अगर_घोषित CONFIG_PXA25x
	अगर (cpu_is_pxa25x())
		pxa_ac97_warm_pxa25x();
	अन्यथा
#पूर्ण_अगर
#अगर_घोषित CONFIG_PXA27x
	अगर (cpu_is_pxa27x())
		pxa_ac97_warm_pxa27x();
	अन्यथा
#पूर्ण_अगर
#अगर_घोषित CONFIG_PXA3xx
	अगर (cpu_is_pxa3xx())
		pxa_ac97_warm_pxa3xx();
	अन्यथा
#पूर्ण_अगर
		snd_BUG();

	जबतक (!((GSR | gsr_bits) & (GSR_PCR | GSR_SCR)) && समयout--)
		mdelay(1);

	gsr = GSR | gsr_bits;
	अगर (!(gsr & (GSR_PCR | GSR_SCR))) अणु
		prपूर्णांकk(KERN_INFO "%s: warm reset timeout (GSR=%#lx)\n",
				 __func__, gsr);

		वापस false;
	पूर्ण

	वापस true;
पूर्ण
EXPORT_SYMBOL_GPL(pxa2xx_ac97_try_warm_reset);

bool pxa2xx_ac97_try_cold_reset(व्योम)
अणु
	अचिन्हित दीर्घ gsr;
	अचिन्हित पूर्णांक समयout = 1000;

#अगर_घोषित CONFIG_PXA25x
	अगर (cpu_is_pxa25x())
		pxa_ac97_cold_pxa25x();
	अन्यथा
#पूर्ण_अगर
#अगर_घोषित CONFIG_PXA27x
	अगर (cpu_is_pxa27x())
		pxa_ac97_cold_pxa27x();
	अन्यथा
#पूर्ण_अगर
#अगर_घोषित CONFIG_PXA3xx
	अगर (cpu_is_pxa3xx())
		pxa_ac97_cold_pxa3xx();
	अन्यथा
#पूर्ण_अगर
		snd_BUG();

	जबतक (!((GSR | gsr_bits) & (GSR_PCR | GSR_SCR)) && समयout--)
		mdelay(1);

	gsr = GSR | gsr_bits;
	अगर (!(gsr & (GSR_PCR | GSR_SCR))) अणु
		prपूर्णांकk(KERN_INFO "%s: cold reset timeout (GSR=%#lx)\n",
				 __func__, gsr);

		वापस false;
	पूर्ण

	वापस true;
पूर्ण
EXPORT_SYMBOL_GPL(pxa2xx_ac97_try_cold_reset);


व्योम pxa2xx_ac97_finish_reset(व्योम)
अणु
	GCR &= ~(GCR_PRIRDY_IEN|GCR_SECRDY_IEN);
	GCR |= GCR_SDONE_IE|GCR_CDONE_IE;
पूर्ण
EXPORT_SYMBOL_GPL(pxa2xx_ac97_finish_reset);

अटल irqवापस_t pxa2xx_ac97_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	दीर्घ status;

	status = GSR;
	अगर (status) अणु
		GSR = status;
		gsr_bits |= status;
		wake_up(&gsr_wq);

		/* Although we करोn't use those we still need to clear them
		   since they tend to spuriously trigger when MMC is used
		   (hardware bug? go figure)... */
		अगर (cpu_is_pxa27x()) अणु
			MISR = MISR_EOC;
			PISR = PISR_EOC;
			MCSR = MCSR_EOC;
		पूर्ण

		वापस IRQ_HANDLED;
	पूर्ण

	वापस IRQ_NONE;
पूर्ण

#अगर_घोषित CONFIG_PM
पूर्णांक pxa2xx_ac97_hw_suspend(व्योम)
अणु
	GCR |= GCR_ACLINK_OFF;
	clk_disable_unprepare(ac97_clk);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(pxa2xx_ac97_hw_suspend);

पूर्णांक pxa2xx_ac97_hw_resume(व्योम)
अणु
	clk_prepare_enable(ac97_clk);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(pxa2xx_ac97_hw_resume);
#पूर्ण_अगर

पूर्णांक pxa2xx_ac97_hw_probe(काष्ठा platक्रमm_device *dev)
अणु
	पूर्णांक ret;
	pxa2xx_audio_ops_t *pdata = dev->dev.platक्रमm_data;

	अगर (pdata) अणु
		चयन (pdata->reset_gpio) अणु
		हाल 95:
		हाल 113:
			reset_gpio = pdata->reset_gpio;
			अवरोध;
		हाल 0:
			reset_gpio = 113;
			अवरोध;
		हाल -1:
			अवरोध;
		शेष:
			dev_err(&dev->dev, "Invalid reset GPIO %d\n",
				pdata->reset_gpio);
		पूर्ण
	पूर्ण अन्यथा अगर (!pdata && dev->dev.of_node) अणु
		pdata = devm_kzalloc(&dev->dev, माप(*pdata), GFP_KERNEL);
		अगर (!pdata)
			वापस -ENOMEM;
		pdata->reset_gpio = of_get_named_gpio(dev->dev.of_node,
						      "reset-gpios", 0);
		अगर (pdata->reset_gpio == -ENOENT)
			pdata->reset_gpio = -1;
		अन्यथा अगर (pdata->reset_gpio < 0)
			वापस pdata->reset_gpio;
		reset_gpio = pdata->reset_gpio;
	पूर्ण अन्यथा अणु
		अगर (cpu_is_pxa27x())
			reset_gpio = 113;
	पूर्ण

	अगर (cpu_is_pxa27x()) अणु
		/*
		 * This gpio is needed क्रम a work-around to a bug in the ac97
		 * controller during warm reset.  The direction and level is set
		 * here so that it is an output driven high when चयनing from
		 * AC97_nRESET alt function to generic gpio.
		 */
		ret = gpio_request_one(reset_gpio, GPIOF_OUT_INIT_HIGH,
				       "pxa27x ac97 reset");
		अगर (ret < 0) अणु
			pr_err("%s: gpio_request_one() failed: %d\n",
			       __func__, ret);
			जाओ err_conf;
		पूर्ण
		pxa27x_configure_ac97reset(reset_gpio, false);

		ac97conf_clk = clk_get(&dev->dev, "AC97CONFCLK");
		अगर (IS_ERR(ac97conf_clk)) अणु
			ret = PTR_ERR(ac97conf_clk);
			ac97conf_clk = शून्य;
			जाओ err_conf;
		पूर्ण
	पूर्ण

	ac97_clk = clk_get(&dev->dev, "AC97CLK");
	अगर (IS_ERR(ac97_clk)) अणु
		ret = PTR_ERR(ac97_clk);
		ac97_clk = शून्य;
		जाओ err_clk;
	पूर्ण

	ret = clk_prepare_enable(ac97_clk);
	अगर (ret)
		जाओ err_clk2;

	ret = request_irq(IRQ_AC97, pxa2xx_ac97_irq, 0, "AC97", शून्य);
	अगर (ret < 0)
		जाओ err_irq;

	वापस 0;

err_irq:
	GCR |= GCR_ACLINK_OFF;
err_clk2:
	clk_put(ac97_clk);
	ac97_clk = शून्य;
err_clk:
	अगर (ac97conf_clk) अणु
		clk_put(ac97conf_clk);
		ac97conf_clk = शून्य;
	पूर्ण
err_conf:
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(pxa2xx_ac97_hw_probe);

व्योम pxa2xx_ac97_hw_हटाओ(काष्ठा platक्रमm_device *dev)
अणु
	अगर (cpu_is_pxa27x())
		gpio_मुक्त(reset_gpio);
	GCR |= GCR_ACLINK_OFF;
	मुक्त_irq(IRQ_AC97, शून्य);
	अगर (ac97conf_clk) अणु
		clk_put(ac97conf_clk);
		ac97conf_clk = शून्य;
	पूर्ण
	clk_disable_unprepare(ac97_clk);
	clk_put(ac97_clk);
	ac97_clk = शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(pxa2xx_ac97_hw_हटाओ);

MODULE_AUTHOR("Nicolas Pitre");
MODULE_DESCRIPTION("Intel/Marvell PXA sound library");
MODULE_LICENSE("GPL");

