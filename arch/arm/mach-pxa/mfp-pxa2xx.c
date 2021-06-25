<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/arch/arm/mach-pxa/mfp-pxa2xx.c
 *
 *  PXA2xx pin mux configuration support
 *
 *  The GPIOs on PXA2xx can be configured as one of many alternate
 *  functions, this is by concept samilar to the MFP configuration
 *  on PXA3xx,  what's more important, the low घातer pin state and
 *  wakeup detection are also supported by the same framework.
 */
#समावेश <linux/gpपन.स>
#समावेश <linux/gpio-pxa.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/syscore_ops.h>

#समावेश <mach/pxa2xx-regs.h>
#समावेश "mfp-pxa2xx.h"

#समावेश "generic.h"

#घोषणा PGSR(x)		__REG2(0x40F00020, (x) << 2)
#घोषणा __GAFR(u, x)	__REG2((u) ? 0x40E00058 : 0x40E00054, (x) << 3)
#घोषणा GAFR_L(x)	__GAFR(0, x)
#घोषणा GAFR_U(x)	__GAFR(1, x)

#घोषणा BANK_OFF(n)	(((n) < 3) ? (n) << 2 : 0x100 + (((n) - 3) << 2))
#घोषणा GPLR(x)		__REG2(0x40E00000, BANK_OFF((x) >> 5))
#घोषणा GPDR(x)		__REG2(0x40E00000, BANK_OFF((x) >> 5) + 0x0c)
#घोषणा GPSR(x)		__REG2(0x40E00000, BANK_OFF((x) >> 5) + 0x18)
#घोषणा GPCR(x)		__REG2(0x40E00000, BANK_OFF((x) >> 5) + 0x24)

#घोषणा PWER_WE35	(1 << 24)

काष्ठा gpio_desc अणु
	अचिन्हित	valid		: 1;
	अचिन्हित	can_wakeup	: 1;
	अचिन्हित	keypad_gpio	: 1;
	अचिन्हित	dir_inverted	: 1;
	अचिन्हित पूर्णांक	mask; /* bit mask in PWER or PKWR */
	अचिन्हित पूर्णांक	mux_mask; /* bit mask of muxed gpio bits, 0 अगर no mux */
	अचिन्हित दीर्घ	config;
पूर्ण;

अटल काष्ठा gpio_desc gpio_desc[MFP_PIN_GPIO127 + 1];

अटल अचिन्हित दीर्घ gpdr_lpm[4];

अटल पूर्णांक __mfp_config_gpio(अचिन्हित gpio, अचिन्हित दीर्घ c)
अणु
	अचिन्हित दीर्घ gafr, mask = GPIO_bit(gpio);
	पूर्णांक bank = gpio_to_bank(gpio);
	पूर्णांक uorl = !!(gpio & 0x10); /* GAFRx_U or GAFRx_L ? */
	पूर्णांक shft = (gpio & 0xf) << 1;
	पूर्णांक fn = MFP_AF(c);
	पूर्णांक is_out = (c & MFP_सूची_OUT) ? 1 : 0;

	अगर (fn > 3)
		वापस -EINVAL;

	/* alternate function and direction at run-समय */
	gafr = (uorl == 0) ? GAFR_L(bank) : GAFR_U(bank);
	gafr = (gafr & ~(0x3 << shft)) | (fn << shft);

	अगर (uorl == 0)
		GAFR_L(bank) = gafr;
	अन्यथा
		GAFR_U(bank) = gafr;

	अगर (is_out ^ gpio_desc[gpio].dir_inverted)
		GPDR(gpio) |= mask;
	अन्यथा
		GPDR(gpio) &= ~mask;

	/* alternate function and direction at low घातer mode */
	चयन (c & MFP_LPM_STATE_MASK) अणु
	हाल MFP_LPM_DRIVE_HIGH:
		PGSR(bank) |= mask;
		is_out = 1;
		अवरोध;
	हाल MFP_LPM_DRIVE_LOW:
		PGSR(bank) &= ~mask;
		is_out = 1;
		अवरोध;
	हाल MFP_LPM_INPUT:
	हाल MFP_LPM_DEFAULT:
		अवरोध;
	शेष:
		/* warning and fall through, treat as MFP_LPM_DEFAULT */
		pr_warn("%s: GPIO%d: unsupported low power mode\n",
			__func__, gpio);
		अवरोध;
	पूर्ण

	अगर (is_out ^ gpio_desc[gpio].dir_inverted)
		gpdr_lpm[bank] |= mask;
	अन्यथा
		gpdr_lpm[bank] &= ~mask;

	/* give early warning अगर MFP_LPM_CAN_WAKEUP is set on the
	 * configurations of those pins not able to wakeup
	 */
	अगर ((c & MFP_LPM_CAN_WAKEUP) && !gpio_desc[gpio].can_wakeup) अणु
		pr_warn("%s: GPIO%d unable to wakeup\n", __func__, gpio);
		वापस -EINVAL;
	पूर्ण

	अगर ((c & MFP_LPM_CAN_WAKEUP) && is_out) अणु
		pr_warn("%s: output GPIO%d unable to wakeup\n", __func__, gpio);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक __mfp_validate(पूर्णांक mfp)
अणु
	पूर्णांक gpio = mfp_to_gpio(mfp);

	अगर ((mfp > MFP_PIN_GPIO127) || !gpio_desc[gpio].valid) अणु
		pr_warn("%s: GPIO%d is invalid pin\n", __func__, gpio);
		वापस -1;
	पूर्ण

	वापस gpio;
पूर्ण

व्योम pxa2xx_mfp_config(अचिन्हित दीर्घ *mfp_cfgs, पूर्णांक num)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ *c;
	पूर्णांक i, gpio;

	क्रम (i = 0, c = mfp_cfgs; i < num; i++, c++) अणु

		gpio = __mfp_validate(MFP_PIN(*c));
		अगर (gpio < 0)
			जारी;

		local_irq_save(flags);

		gpio_desc[gpio].config = *c;
		__mfp_config_gpio(gpio, *c);

		local_irq_restore(flags);
	पूर्ण
पूर्ण

व्योम pxa2xx_mfp_set_lpm(पूर्णांक mfp, अचिन्हित दीर्घ lpm)
अणु
	अचिन्हित दीर्घ flags, c;
	पूर्णांक gpio;

	gpio = __mfp_validate(mfp);
	अगर (gpio < 0)
		वापस;

	local_irq_save(flags);

	c = gpio_desc[gpio].config;
	c = (c & ~MFP_LPM_STATE_MASK) | lpm;
	__mfp_config_gpio(gpio, c);

	local_irq_restore(flags);
पूर्ण

पूर्णांक gpio_set_wake(अचिन्हित पूर्णांक gpio, अचिन्हित पूर्णांक on)
अणु
	काष्ठा gpio_desc *d;
	अचिन्हित दीर्घ c, mux_taken;

	अगर (gpio > mfp_to_gpio(MFP_PIN_GPIO127))
		वापस -EINVAL;

	d = &gpio_desc[gpio];
	c = d->config;

	अगर (!d->valid)
		वापस -EINVAL;

	/* Allow keypad GPIOs to wakeup प्रणाली when
	 * configured as generic GPIOs.
	 */
	अगर (d->keypad_gpio && (MFP_AF(d->config) == 0) &&
	    (d->config & MFP_LPM_CAN_WAKEUP)) अणु
		अगर (on)
			PKWR |= d->mask;
		अन्यथा
			PKWR &= ~d->mask;
		वापस 0;
	पूर्ण

	mux_taken = (PWER & d->mux_mask) & (~d->mask);
	अगर (on && mux_taken)
		वापस -EBUSY;

	अगर (d->can_wakeup && (c & MFP_LPM_CAN_WAKEUP)) अणु
		अगर (on) अणु
			PWER = (PWER & ~d->mux_mask) | d->mask;

			अगर (c & MFP_LPM_EDGE_RISE)
				PRER |= d->mask;
			अन्यथा
				PRER &= ~d->mask;

			अगर (c & MFP_LPM_EDGE_FALL)
				PFER |= d->mask;
			अन्यथा
				PFER &= ~d->mask;
		पूर्ण अन्यथा अणु
			PWER &= ~d->mask;
			PRER &= ~d->mask;
			PFER &= ~d->mask;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PXA25x
अटल व्योम __init pxa25x_mfp_init(व्योम)
अणु
	पूर्णांक i;

	/* running beक्रमe pxa_gpio_probe() */
#अगर_घोषित CONFIG_CPU_PXA26x
	pxa_last_gpio = 89;
#अन्यथा
	pxa_last_gpio = 84;
#पूर्ण_अगर
	क्रम (i = 0; i <= pxa_last_gpio; i++)
		gpio_desc[i].valid = 1;

	क्रम (i = 0; i <= 15; i++) अणु
		gpio_desc[i].can_wakeup = 1;
		gpio_desc[i].mask = GPIO_bit(i);
	पूर्ण

	/* PXA26x has additional 4 GPIOs (86/87/88/89) which has the
	 * direction bit inverted in GPDR2. See PXA26x DM 4.1.1.
	 */
	क्रम (i = 86; i <= pxa_last_gpio; i++)
		gpio_desc[i].dir_inverted = 1;
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम pxa25x_mfp_init(व्योम) अणुपूर्ण
#पूर्ण_अगर /* CONFIG_PXA25x */

#अगर_घोषित CONFIG_PXA27x
अटल पूर्णांक pxa27x_pkwr_gpio[] = अणु
	13, 16, 17, 34, 36, 37, 38, 39, 90, 91, 93, 94,
	95, 96, 97, 98, 99, 100, 101, 102
पूर्ण;

पूर्णांक keypad_set_wake(अचिन्हित पूर्णांक on)
अणु
	अचिन्हित पूर्णांक i, gpio, mask = 0;
	काष्ठा gpio_desc *d;

	क्रम (i = 0; i < ARRAY_SIZE(pxa27x_pkwr_gpio); i++) अणु

		gpio = pxa27x_pkwr_gpio[i];
		d = &gpio_desc[gpio];

		/* skip अगर configured as generic GPIO */
		अगर (MFP_AF(d->config) == 0)
			जारी;

		अगर (d->config & MFP_LPM_CAN_WAKEUP)
			mask |= gpio_desc[gpio].mask;
	पूर्ण

	अगर (on)
		PKWR |= mask;
	अन्यथा
		PKWR &= ~mask;
	वापस 0;
पूर्ण

#घोषणा PWER_WEMUX2_GPIO38	(1 << 16)
#घोषणा PWER_WEMUX2_GPIO53	(2 << 16)
#घोषणा PWER_WEMUX2_GPIO40	(3 << 16)
#घोषणा PWER_WEMUX2_GPIO36	(4 << 16)
#घोषणा PWER_WEMUX2_MASK	(7 << 16)
#घोषणा PWER_WEMUX3_GPIO31	(1 << 19)
#घोषणा PWER_WEMUX3_GPIO113	(2 << 19)
#घोषणा PWER_WEMUX3_MASK	(3 << 19)

#घोषणा INIT_GPIO_DESC_MUXED(mux, gpio)				\
करो अणु								\
	gpio_desc[(gpio)].can_wakeup = 1;			\
	gpio_desc[(gpio)].mask = PWER_ ## mux ## _GPIO ##gpio;	\
	gpio_desc[(gpio)].mux_mask = PWER_ ## mux ## _MASK;	\
पूर्ण जबतक (0)

अटल व्योम __init pxa27x_mfp_init(व्योम)
अणु
	पूर्णांक i, gpio;

	pxa_last_gpio = 120;	/* running beक्रमe pxa_gpio_probe() */
	क्रम (i = 0; i <= pxa_last_gpio; i++) अणु
		/* skip GPIO2, 5, 6, 7, 8, they are not
		 * valid pins allow configuration
		 */
		अगर (i == 2 || i == 5 || i == 6 || i == 7 || i == 8)
			जारी;

		gpio_desc[i].valid = 1;
	पूर्ण

	/* Keypad GPIOs */
	क्रम (i = 0; i < ARRAY_SIZE(pxa27x_pkwr_gpio); i++) अणु
		gpio = pxa27x_pkwr_gpio[i];
		gpio_desc[gpio].can_wakeup = 1;
		gpio_desc[gpio].keypad_gpio = 1;
		gpio_desc[gpio].mask = 1 << i;
	पूर्ण

	/* Overग_लिखो GPIO13 as a PWER wakeup source */
	क्रम (i = 0; i <= 15; i++) अणु
		/* skip GPIO2, 5, 6, 7, 8 */
		अगर (GPIO_bit(i) & 0x1e4)
			जारी;

		gpio_desc[i].can_wakeup = 1;
		gpio_desc[i].mask = GPIO_bit(i);
	पूर्ण

	gpio_desc[35].can_wakeup = 1;
	gpio_desc[35].mask = PWER_WE35;

	INIT_GPIO_DESC_MUXED(WEMUX3, 31);
	INIT_GPIO_DESC_MUXED(WEMUX3, 113);
	INIT_GPIO_DESC_MUXED(WEMUX2, 38);
	INIT_GPIO_DESC_MUXED(WEMUX2, 53);
	INIT_GPIO_DESC_MUXED(WEMUX2, 40);
	INIT_GPIO_DESC_MUXED(WEMUX2, 36);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम pxa27x_mfp_init(व्योम) अणुपूर्ण
#पूर्ण_अगर /* CONFIG_PXA27x */

#अगर_घोषित CONFIG_PM
अटल अचिन्हित दीर्घ saved_gafr[2][4];
अटल अचिन्हित दीर्घ saved_gpdr[4];
अटल अचिन्हित दीर्घ saved_gplr[4];
अटल अचिन्हित दीर्घ saved_pgsr[4];

अटल पूर्णांक pxa2xx_mfp_suspend(व्योम)
अणु
	पूर्णांक i;

	/* set corresponding PGSR bit of those marked MFP_LPM_KEEP_OUTPUT */
	क्रम (i = 0; i < pxa_last_gpio; i++) अणु
		अगर ((gpio_desc[i].config & MFP_LPM_KEEP_OUTPUT) &&
		    (GPDR(i) & GPIO_bit(i))) अणु
			अगर (GPLR(i) & GPIO_bit(i))
				PGSR(gpio_to_bank(i)) |= GPIO_bit(i);
			अन्यथा
				PGSR(gpio_to_bank(i)) &= ~GPIO_bit(i);
		पूर्ण
	पूर्ण

	क्रम (i = 0; i <= gpio_to_bank(pxa_last_gpio); i++) अणु
		saved_gafr[0][i] = GAFR_L(i);
		saved_gafr[1][i] = GAFR_U(i);
		saved_gpdr[i] = GPDR(i * 32);
		saved_gplr[i] = GPLR(i * 32);
		saved_pgsr[i] = PGSR(i);

		GPSR(i * 32) = PGSR(i);
		GPCR(i * 32) = ~PGSR(i);
	पूर्ण

	/* set GPDR bits taking पूर्णांकo account MFP_LPM_KEEP_OUTPUT */
	क्रम (i = 0; i < pxa_last_gpio; i++) अणु
		अगर ((gpdr_lpm[gpio_to_bank(i)] & GPIO_bit(i)) ||
		    ((gpio_desc[i].config & MFP_LPM_KEEP_OUTPUT) &&
		     (saved_gpdr[gpio_to_bank(i)] & GPIO_bit(i))))
			GPDR(i) |= GPIO_bit(i);
		अन्यथा
			GPDR(i) &= ~GPIO_bit(i);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम pxa2xx_mfp_resume(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i <= gpio_to_bank(pxa_last_gpio); i++) अणु
		GAFR_L(i) = saved_gafr[0][i];
		GAFR_U(i) = saved_gafr[1][i];
		GPSR(i * 32) = saved_gplr[i];
		GPCR(i * 32) = ~saved_gplr[i];
		GPDR(i * 32) = saved_gpdr[i];
		PGSR(i) = saved_pgsr[i];
	पूर्ण
	PSSR = PSSR_RDH | PSSR_PH;
पूर्ण
#अन्यथा
#घोषणा pxa2xx_mfp_suspend	शून्य
#घोषणा pxa2xx_mfp_resume	शून्य
#पूर्ण_अगर

काष्ठा syscore_ops pxa2xx_mfp_syscore_ops = अणु
	.suspend	= pxa2xx_mfp_suspend,
	.resume		= pxa2xx_mfp_resume,
पूर्ण;

अटल पूर्णांक __init pxa2xx_mfp_init(व्योम)
अणु
	पूर्णांक i;

	अगर (!cpu_is_pxa2xx())
		वापस 0;

	अगर (cpu_is_pxa25x())
		pxa25x_mfp_init();

	अगर (cpu_is_pxa27x())
		pxa27x_mfp_init();

	/* clear RDH bit to enable GPIO receivers after reset/sleep निकास */
	PSSR = PSSR_RDH;

	/* initialize gafr_run[], pgsr_lpm[] from existing values */
	क्रम (i = 0; i <= gpio_to_bank(pxa_last_gpio); i++)
		gpdr_lpm[i] = GPDR(i * 32);

	वापस 0;
पूर्ण
postcore_initcall(pxa2xx_mfp_init);
