<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * arch/arm/mach-at91/pm.c
 * AT91 Power Management
 *
 * Copyright (C) 2005 David Brownell
 */

#समावेश <linux/genभाग.स>
#समावेश <linux/पन.स>
#समावेश <linux/of_address.h>
#समावेश <linux/of.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/parser.h>
#समावेश <linux/suspend.h>

#समावेश <linux/clk/at91_pmc.h>
#समावेश <linux/platक्रमm_data/aपंचांगel.h>

#समावेश <soc/at91/pm.h>

#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/fncpy.h>
#समावेश <यंत्र/प्रणाली_misc.h>
#समावेश <यंत्र/suspend.h>

#समावेश "generic.h"
#समावेश "pm.h"

काष्ठा at91_soc_pm अणु
	पूर्णांक (*config_shdwc_ws)(व्योम __iomem *shdwc, u32 *mode, u32 *polarity);
	पूर्णांक (*config_pmc_ws)(व्योम __iomem *pmc, u32 mode, u32 polarity);
	स्थिर काष्ठा of_device_id *ws_ids;
	काष्ठा at91_pm_data data;
पूर्ण;

अटल काष्ठा at91_soc_pm soc_pm = अणु
	.data = अणु
		.standby_mode = AT91_PM_STANDBY,
		.suspend_mode = AT91_PM_ULP0,
	पूर्ण,
पूर्ण;

अटल स्थिर match_table_t pm_modes __initस्थिर = अणु
	अणु AT91_PM_STANDBY,	"standby" पूर्ण,
	अणु AT91_PM_ULP0,		"ulp0" पूर्ण,
	अणु AT91_PM_ULP0_FAST,    "ulp0-fast" पूर्ण,
	अणु AT91_PM_ULP1,		"ulp1" पूर्ण,
	अणु AT91_PM_BACKUP,	"backup" पूर्ण,
	अणु -1, शून्य पूर्ण,
पूर्ण;

#घोषणा at91_ramc_पढ़ो(id, field) \
	__raw_पढ़ोl(soc_pm.data.ramc[id] + field)

#घोषणा at91_ramc_ग_लिखो(id, field, value) \
	__raw_ग_लिखोl(value, soc_pm.data.ramc[id] + field)

अटल पूर्णांक at91_pm_valid_state(suspend_state_t state)
अणु
	चयन (state) अणु
		हाल PM_SUSPEND_ON:
		हाल PM_SUSPEND_STANDBY:
		हाल PM_SUSPEND_MEM:
			वापस 1;

		शेष:
			वापस 0;
	पूर्ण
पूर्ण

अटल पूर्णांक canary = 0xA5A5A5A5;

अटल काष्ठा at91_pm_bu अणु
	पूर्णांक suspended;
	अचिन्हित दीर्घ reserved;
	phys_addr_t canary;
	phys_addr_t resume;
पूर्ण *pm_bu;

काष्ठा wakeup_source_info अणु
	अचिन्हित पूर्णांक pmc_fsmr_bit;
	अचिन्हित पूर्णांक shdwc_mr_bit;
	bool set_polarity;
पूर्ण;

अटल स्थिर काष्ठा wakeup_source_info ws_info[] = अणु
	अणु .pmc_fsmr_bit = AT91_PMC_FSTT(10),	.set_polarity = true पूर्ण,
	अणु .pmc_fsmr_bit = AT91_PMC_RTCAL,	.shdwc_mr_bit = BIT(17) पूर्ण,
	अणु .pmc_fsmr_bit = AT91_PMC_USBAL पूर्ण,
	अणु .pmc_fsmr_bit = AT91_PMC_SDMMC_CD पूर्ण,
	अणु .pmc_fsmr_bit = AT91_PMC_RTTAL पूर्ण,
	अणु .pmc_fsmr_bit = AT91_PMC_RXLP_MCE पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा of_device_id sama5d2_ws_ids[] = अणु
	अणु .compatible = "atmel,sama5d2-gem",		.data = &ws_info[0] पूर्ण,
	अणु .compatible = "atmel,at91rm9200-rtc",		.data = &ws_info[1] पूर्ण,
	अणु .compatible = "atmel,sama5d3-udc",		.data = &ws_info[2] पूर्ण,
	अणु .compatible = "atmel,at91rm9200-ohci",	.data = &ws_info[2] पूर्ण,
	अणु .compatible = "usb-ohci",			.data = &ws_info[2] पूर्ण,
	अणु .compatible = "atmel,at91sam9g45-ehci",	.data = &ws_info[2] पूर्ण,
	अणु .compatible = "usb-ehci",			.data = &ws_info[2] पूर्ण,
	अणु .compatible = "atmel,sama5d2-sdhci",		.data = &ws_info[3] पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;

अटल स्थिर काष्ठा of_device_id sam9x60_ws_ids[] = अणु
	अणु .compatible = "atmel,at91sam9x5-rtc",		.data = &ws_info[1] पूर्ण,
	अणु .compatible = "atmel,at91rm9200-ohci",	.data = &ws_info[2] पूर्ण,
	अणु .compatible = "usb-ohci",			.data = &ws_info[2] पूर्ण,
	अणु .compatible = "atmel,at91sam9g45-ehci",	.data = &ws_info[2] पूर्ण,
	अणु .compatible = "usb-ehci",			.data = &ws_info[2] पूर्ण,
	अणु .compatible = "atmel,at91sam9260-rtt",	.data = &ws_info[4] पूर्ण,
	अणु .compatible = "cdns,sam9x60-macb",		.data = &ws_info[5] पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;

अटल पूर्णांक at91_pm_config_ws(अचिन्हित पूर्णांक pm_mode, bool set)
अणु
	स्थिर काष्ठा wakeup_source_info *wsi;
	स्थिर काष्ठा of_device_id *match;
	काष्ठा platक्रमm_device *pdev;
	काष्ठा device_node *np;
	अचिन्हित पूर्णांक mode = 0, polarity = 0, val = 0;

	अगर (pm_mode != AT91_PM_ULP1)
		वापस 0;

	अगर (!soc_pm.data.pmc || !soc_pm.data.shdwc || !soc_pm.ws_ids)
		वापस -EPERM;

	अगर (!set) अणु
		ग_लिखोl(mode, soc_pm.data.pmc + AT91_PMC_FSMR);
		वापस 0;
	पूर्ण

	अगर (soc_pm.config_shdwc_ws)
		soc_pm.config_shdwc_ws(soc_pm.data.shdwc, &mode, &polarity);

	/* SHDWC.MR */
	val = पढ़ोl(soc_pm.data.shdwc + 0x04);

	/* Loop through defined wakeup sources. */
	क्रम_each_matching_node_and_match(np, soc_pm.ws_ids, &match) अणु
		pdev = of_find_device_by_node(np);
		अगर (!pdev)
			जारी;

		अगर (device_may_wakeup(&pdev->dev)) अणु
			wsi = match->data;

			/* Check अगर enabled on SHDWC. */
			अगर (wsi->shdwc_mr_bit && !(val & wsi->shdwc_mr_bit))
				जाओ put_device;

			mode |= wsi->pmc_fsmr_bit;
			अगर (wsi->set_polarity)
				polarity |= wsi->pmc_fsmr_bit;
		पूर्ण

put_device:
		put_device(&pdev->dev);
	पूर्ण

	अगर (mode) अणु
		अगर (soc_pm.config_pmc_ws)
			soc_pm.config_pmc_ws(soc_pm.data.pmc, mode, polarity);
	पूर्ण अन्यथा अणु
		pr_err("AT91: PM: no ULP1 wakeup sources found!");
	पूर्ण

	वापस mode ? 0 : -EPERM;
पूर्ण

अटल पूर्णांक at91_sama5d2_config_shdwc_ws(व्योम __iomem *shdwc, u32 *mode,
					u32 *polarity)
अणु
	u32 val;

	/* SHDWC.WUIR */
	val = पढ़ोl(shdwc + 0x0c);
	*mode |= (val & 0x3ff);
	*polarity |= ((val >> 16) & 0x3ff);

	वापस 0;
पूर्ण

अटल पूर्णांक at91_sama5d2_config_pmc_ws(व्योम __iomem *pmc, u32 mode, u32 polarity)
अणु
	ग_लिखोl(mode, pmc + AT91_PMC_FSMR);
	ग_लिखोl(polarity, pmc + AT91_PMC_FSPR);

	वापस 0;
पूर्ण

अटल पूर्णांक at91_sam9x60_config_pmc_ws(व्योम __iomem *pmc, u32 mode, u32 polarity)
अणु
	ग_लिखोl(mode, pmc + AT91_PMC_FSMR);

	वापस 0;
पूर्ण

/*
 * Called after processes are frozen, but beक्रमe we shutकरोwn devices.
 */
अटल पूर्णांक at91_pm_begin(suspend_state_t state)
अणु
	चयन (state) अणु
	हाल PM_SUSPEND_MEM:
		soc_pm.data.mode = soc_pm.data.suspend_mode;
		अवरोध;

	हाल PM_SUSPEND_STANDBY:
		soc_pm.data.mode = soc_pm.data.standby_mode;
		अवरोध;

	शेष:
		soc_pm.data.mode = -1;
	पूर्ण

	वापस at91_pm_config_ws(soc_pm.data.mode, true);
पूर्ण

/*
 * Verअगरy that all the घड़ीs are correct beक्रमe entering
 * slow-घड़ी mode.
 */
अटल पूर्णांक at91_pm_verअगरy_घड़ीs(व्योम)
अणु
	अचिन्हित दीर्घ scsr;
	पूर्णांक i;

	scsr = पढ़ोl(soc_pm.data.pmc + AT91_PMC_SCSR);

	/* USB must not be using PLLB */
	अगर ((scsr & soc_pm.data.uhp_udp_mask) != 0) अणु
		pr_err("AT91: PM - Suspend-to-RAM with USB still active\n");
		वापस 0;
	पूर्ण

	/* PCK0..PCK3 must be disabled, or configured to use clk32k */
	क्रम (i = 0; i < 4; i++) अणु
		u32 css;

		अगर ((scsr & (AT91_PMC_PCK0 << i)) == 0)
			जारी;
		css = पढ़ोl(soc_pm.data.pmc + AT91_PMC_PCKR(i)) & AT91_PMC_CSS;
		अगर (css != AT91_PMC_CSS_SLOW) अणु
			pr_err("AT91: PM - Suspend-to-RAM with PCK%d src %d\n", i, css);
			वापस 0;
		पूर्ण
	पूर्ण

	वापस 1;
पूर्ण

/*
 * Call this from platक्रमm driver suspend() to see how deeply to suspend.
 * For example, some controllers (like OHCI) need one of the PLL घड़ीs
 * in order to act as a wakeup source, and those are not available when
 * going पूर्णांकo slow घड़ी mode.
 *
 * REVISIT: generalize as clk_will_be_available(clk)?  Other platक्रमms have
 * the very same problem (but not using at91 मुख्य_clk), and it'd be better
 * to add one generic API rather than lots of platक्रमm-specअगरic ones.
 */
पूर्णांक at91_suspend_entering_slow_घड़ी(व्योम)
अणु
	वापस (soc_pm.data.mode >= AT91_PM_ULP0);
पूर्ण
EXPORT_SYMBOL(at91_suspend_entering_slow_घड़ी);

अटल व्योम (*at91_suspend_sram_fn)(काष्ठा at91_pm_data *);
बाह्य व्योम at91_pm_suspend_in_sram(काष्ठा at91_pm_data *pm_data);
बाह्य u32 at91_pm_suspend_in_sram_sz;

अटल पूर्णांक at91_suspend_finish(अचिन्हित दीर्घ val)
अणु
	flush_cache_all();
	outer_disable();

	at91_suspend_sram_fn(&soc_pm.data);

	वापस 0;
पूर्ण

अटल व्योम at91_pm_suspend(suspend_state_t state)
अणु
	अगर (soc_pm.data.mode == AT91_PM_BACKUP) अणु
		pm_bu->suspended = 1;

		cpu_suspend(0, at91_suspend_finish);

		/* The SRAM is lost between suspend cycles */
		at91_suspend_sram_fn = fncpy(at91_suspend_sram_fn,
					     &at91_pm_suspend_in_sram,
					     at91_pm_suspend_in_sram_sz);
	पूर्ण अन्यथा अणु
		at91_suspend_finish(0);
	पूर्ण

	outer_resume();
पूर्ण

/*
 * STANDBY mode has *all* drivers suspended; ignores irqs not marked as 'wakeup'
 * event sources; and reduces DRAM घातer.  But otherwise it's identical to
 * PM_SUSPEND_ON: cpu idle, and nothing fancy करोne with मुख्य or cpu घड़ीs.
 *
 * AT91_PM_ULP0 is like STANDBY plus slow घड़ी mode, so drivers must
 * suspend more deeply, the master घड़ी चयनes to the clk32k and turns off
 * the मुख्य oscillator
 *
 * AT91_PM_BACKUP turns off the whole SoC after placing the DDR in self refresh
 */
अटल पूर्णांक at91_pm_enter(suspend_state_t state)
अणु
#अगर_घोषित CONFIG_PINCTRL_AT91
	/*
	 * FIXME: this is needed to communicate between the pinctrl driver and
	 * the PM implementation in the machine. Possibly part of the PM
	 * implementation should be moved करोwn पूर्णांकo the pinctrl driver and get
	 * called as part of the generic suspend/resume path.
	 */
	at91_pinctrl_gpio_suspend();
#पूर्ण_अगर

	चयन (state) अणु
	हाल PM_SUSPEND_MEM:
	हाल PM_SUSPEND_STANDBY:
		/*
		 * Ensure that घड़ीs are in a valid state.
		 */
		अगर (soc_pm.data.mode >= AT91_PM_ULP0 &&
		    !at91_pm_verअगरy_घड़ीs())
			जाओ error;

		at91_pm_suspend(state);

		अवरोध;

	हाल PM_SUSPEND_ON:
		cpu_करो_idle();
		अवरोध;

	शेष:
		pr_debug("AT91: PM - bogus suspend state %d\n", state);
		जाओ error;
	पूर्ण

error:
#अगर_घोषित CONFIG_PINCTRL_AT91
	at91_pinctrl_gpio_resume();
#पूर्ण_अगर
	वापस 0;
पूर्ण

/*
 * Called right prior to thawing processes.
 */
अटल व्योम at91_pm_end(व्योम)
अणु
	at91_pm_config_ws(soc_pm.data.mode, false);
पूर्ण


अटल स्थिर काष्ठा platक्रमm_suspend_ops at91_pm_ops = अणु
	.valid	= at91_pm_valid_state,
	.begin	= at91_pm_begin,
	.enter	= at91_pm_enter,
	.end	= at91_pm_end,
पूर्ण;

अटल काष्ठा platक्रमm_device at91_cpuidle_device = अणु
	.name = "cpuidle-at91",
पूर्ण;

/*
 * The AT91RM9200 goes पूर्णांकo self-refresh mode with this command, and will
 * terminate self-refresh स्वतःmatically on the next SDRAM access.
 *
 * Self-refresh mode is निकासed as soon as a memory access is made, but we करोn't
 * know क्रम sure when that happens. However, we need to restore the low-घातer
 * mode अगर it was enabled beक्रमe going idle. Restoring low-घातer mode जबतक
 * still in self-refresh is "not recommended", but seems to work.
 */
अटल व्योम at91rm9200_standby(व्योम)
अणु
	यंत्र अस्थिर(
		"b    1f\n\t"
		".align    5\n\t"
		"1:  mcr    p15, 0, %0, c7, c10, 4\n\t"
		"    str    %2, [%1, %3]\n\t"
		"    mcr    p15, 0, %0, c7, c0, 4\n\t"
		:
		: "r" (0), "r" (soc_pm.data.ramc[0]),
		  "r" (1), "r" (AT91_MC_SDRAMC_SRR));
पूर्ण

/* We manage both DDRAM/SDRAM controllers, we need more than one value to
 * remember.
 */
अटल व्योम at91_ddr_standby(व्योम)
अणु
	/* Those two values allow us to delay self-refresh activation
	 * to the maximum. */
	u32 lpr0, lpr1 = 0;
	u32 mdr, saved_mdr0, saved_mdr1 = 0;
	u32 saved_lpr0, saved_lpr1 = 0;

	/* LPDDR1 --> क्रमce DDR2 mode during self-refresh */
	saved_mdr0 = at91_ramc_पढ़ो(0, AT91_DDRSDRC_MDR);
	अगर ((saved_mdr0 & AT91_DDRSDRC_MD) == AT91_DDRSDRC_MD_LOW_POWER_DDR) अणु
		mdr = saved_mdr0 & ~AT91_DDRSDRC_MD;
		mdr |= AT91_DDRSDRC_MD_DDR2;
		at91_ramc_ग_लिखो(0, AT91_DDRSDRC_MDR, mdr);
	पूर्ण

	अगर (soc_pm.data.ramc[1]) अणु
		saved_lpr1 = at91_ramc_पढ़ो(1, AT91_DDRSDRC_LPR);
		lpr1 = saved_lpr1 & ~AT91_DDRSDRC_LPCB;
		lpr1 |= AT91_DDRSDRC_LPCB_SELF_REFRESH;
		saved_mdr1 = at91_ramc_पढ़ो(1, AT91_DDRSDRC_MDR);
		अगर ((saved_mdr1 & AT91_DDRSDRC_MD) == AT91_DDRSDRC_MD_LOW_POWER_DDR) अणु
			mdr = saved_mdr1 & ~AT91_DDRSDRC_MD;
			mdr |= AT91_DDRSDRC_MD_DDR2;
			at91_ramc_ग_लिखो(1, AT91_DDRSDRC_MDR, mdr);
		पूर्ण
	पूर्ण

	saved_lpr0 = at91_ramc_पढ़ो(0, AT91_DDRSDRC_LPR);
	lpr0 = saved_lpr0 & ~AT91_DDRSDRC_LPCB;
	lpr0 |= AT91_DDRSDRC_LPCB_SELF_REFRESH;

	/* self-refresh mode now */
	at91_ramc_ग_लिखो(0, AT91_DDRSDRC_LPR, lpr0);
	अगर (soc_pm.data.ramc[1])
		at91_ramc_ग_लिखो(1, AT91_DDRSDRC_LPR, lpr1);

	cpu_करो_idle();

	at91_ramc_ग_लिखो(0, AT91_DDRSDRC_MDR, saved_mdr0);
	at91_ramc_ग_लिखो(0, AT91_DDRSDRC_LPR, saved_lpr0);
	अगर (soc_pm.data.ramc[1]) अणु
		at91_ramc_ग_लिखो(0, AT91_DDRSDRC_MDR, saved_mdr1);
		at91_ramc_ग_लिखो(1, AT91_DDRSDRC_LPR, saved_lpr1);
	पूर्ण
पूर्ण

अटल व्योम sama5d3_ddr_standby(व्योम)
अणु
	u32 lpr0;
	u32 saved_lpr0;

	saved_lpr0 = at91_ramc_पढ़ो(0, AT91_DDRSDRC_LPR);
	lpr0 = saved_lpr0 & ~AT91_DDRSDRC_LPCB;
	lpr0 |= AT91_DDRSDRC_LPCB_POWER_DOWN;

	at91_ramc_ग_लिखो(0, AT91_DDRSDRC_LPR, lpr0);

	cpu_करो_idle();

	at91_ramc_ग_लिखो(0, AT91_DDRSDRC_LPR, saved_lpr0);
पूर्ण

/* We manage both DDRAM/SDRAM controllers, we need more than one value to
 * remember.
 */
अटल व्योम at91sam9_sdram_standby(व्योम)
अणु
	u32 lpr0, lpr1 = 0;
	u32 saved_lpr0, saved_lpr1 = 0;

	अगर (soc_pm.data.ramc[1]) अणु
		saved_lpr1 = at91_ramc_पढ़ो(1, AT91_SDRAMC_LPR);
		lpr1 = saved_lpr1 & ~AT91_SDRAMC_LPCB;
		lpr1 |= AT91_SDRAMC_LPCB_SELF_REFRESH;
	पूर्ण

	saved_lpr0 = at91_ramc_पढ़ो(0, AT91_SDRAMC_LPR);
	lpr0 = saved_lpr0 & ~AT91_SDRAMC_LPCB;
	lpr0 |= AT91_SDRAMC_LPCB_SELF_REFRESH;

	/* self-refresh mode now */
	at91_ramc_ग_लिखो(0, AT91_SDRAMC_LPR, lpr0);
	अगर (soc_pm.data.ramc[1])
		at91_ramc_ग_लिखो(1, AT91_SDRAMC_LPR, lpr1);

	cpu_करो_idle();

	at91_ramc_ग_लिखो(0, AT91_SDRAMC_LPR, saved_lpr0);
	अगर (soc_pm.data.ramc[1])
		at91_ramc_ग_लिखो(1, AT91_SDRAMC_LPR, saved_lpr1);
पूर्ण

काष्ठा ramc_info अणु
	व्योम (*idle)(व्योम);
	अचिन्हित पूर्णांक memctrl;
पूर्ण;

अटल स्थिर काष्ठा ramc_info ramc_infos[] __initस्थिर = अणु
	अणु .idle = at91rm9200_standby, .memctrl = AT91_MEMCTRL_MCपूर्ण,
	अणु .idle = at91sam9_sdram_standby, .memctrl = AT91_MEMCTRL_SDRAMCपूर्ण,
	अणु .idle = at91_ddr_standby, .memctrl = AT91_MEMCTRL_DDRSDRपूर्ण,
	अणु .idle = sama5d3_ddr_standby, .memctrl = AT91_MEMCTRL_DDRSDRपूर्ण,
पूर्ण;

अटल स्थिर काष्ठा of_device_id ramc_ids[] __initस्थिर = अणु
	अणु .compatible = "atmel,at91rm9200-sdramc", .data = &ramc_infos[0] पूर्ण,
	अणु .compatible = "atmel,at91sam9260-sdramc", .data = &ramc_infos[1] पूर्ण,
	अणु .compatible = "atmel,at91sam9g45-ddramc", .data = &ramc_infos[2] पूर्ण,
	अणु .compatible = "atmel,sama5d3-ddramc", .data = &ramc_infos[3] पूर्ण,
	अणु /*sentinel*/ पूर्ण
पूर्ण;

अटल __init व्योम at91_dt_ramc(व्योम)
अणु
	काष्ठा device_node *np;
	स्थिर काष्ठा of_device_id *of_id;
	पूर्णांक idx = 0;
	व्योम *standby = शून्य;
	स्थिर काष्ठा ramc_info *ramc;

	क्रम_each_matching_node_and_match(np, ramc_ids, &of_id) अणु
		soc_pm.data.ramc[idx] = of_iomap(np, 0);
		अगर (!soc_pm.data.ramc[idx])
			panic(pr_fmt("unable to map ramc[%d] cpu registers\n"), idx);

		ramc = of_id->data;
		अगर (!standby)
			standby = ramc->idle;
		soc_pm.data.memctrl = ramc->memctrl;

		idx++;
	पूर्ण

	अगर (!idx)
		panic(pr_fmt("unable to find compatible ram controller node in dtb\n"));

	अगर (!standby) अणु
		pr_warn("ramc no standby function available\n");
		वापस;
	पूर्ण

	at91_cpuidle_device.dev.platक्रमm_data = standby;
पूर्ण

अटल व्योम at91rm9200_idle(व्योम)
अणु
	/*
	 * Disable the processor घड़ी.  The processor will be स्वतःmatically
	 * re-enabled by an पूर्णांकerrupt or by a reset.
	 */
	ग_लिखोl(AT91_PMC_PCK, soc_pm.data.pmc + AT91_PMC_SCDR);
पूर्ण

अटल व्योम at91sam9_idle(व्योम)
अणु
	ग_लिखोl(AT91_PMC_PCK, soc_pm.data.pmc + AT91_PMC_SCDR);
	cpu_करो_idle();
पूर्ण

अटल व्योम __init at91_pm_sram_init(व्योम)
अणु
	काष्ठा gen_pool *sram_pool;
	phys_addr_t sram_pbase;
	अचिन्हित दीर्घ sram_base;
	काष्ठा device_node *node;
	काष्ठा platक्रमm_device *pdev = शून्य;

	क्रम_each_compatible_node(node, शून्य, "mmio-sram") अणु
		pdev = of_find_device_by_node(node);
		अगर (pdev) अणु
			of_node_put(node);
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!pdev) अणु
		pr_warn("%s: failed to find sram device!\n", __func__);
		वापस;
	पूर्ण

	sram_pool = gen_pool_get(&pdev->dev, शून्य);
	अगर (!sram_pool) अणु
		pr_warn("%s: sram pool unavailable!\n", __func__);
		जाओ out_put_device;
	पूर्ण

	sram_base = gen_pool_alloc(sram_pool, at91_pm_suspend_in_sram_sz);
	अगर (!sram_base) अणु
		pr_warn("%s: unable to alloc sram!\n", __func__);
		जाओ out_put_device;
	पूर्ण

	sram_pbase = gen_pool_virt_to_phys(sram_pool, sram_base);
	at91_suspend_sram_fn = __arm_ioremap_exec(sram_pbase,
					at91_pm_suspend_in_sram_sz, false);
	अगर (!at91_suspend_sram_fn) अणु
		pr_warn("SRAM: Could not map\n");
		जाओ out_put_device;
	पूर्ण

	/* Copy the pm suspend handler to SRAM */
	at91_suspend_sram_fn = fncpy(at91_suspend_sram_fn,
			&at91_pm_suspend_in_sram, at91_pm_suspend_in_sram_sz);
	वापस;

out_put_device:
	put_device(&pdev->dev);
	वापस;
पूर्ण

अटल bool __init at91_is_pm_mode_active(पूर्णांक pm_mode)
अणु
	वापस (soc_pm.data.standby_mode == pm_mode ||
		soc_pm.data.suspend_mode == pm_mode);
पूर्ण

अटल पूर्णांक __init at91_pm_backup_init(व्योम)
अणु
	काष्ठा gen_pool *sram_pool;
	काष्ठा device_node *np;
	काष्ठा platक्रमm_device *pdev = शून्य;
	पूर्णांक ret = -ENODEV;

	अगर (!IS_ENABLED(CONFIG_SOC_SAMA5D2))
		वापस -EPERM;

	अगर (!at91_is_pm_mode_active(AT91_PM_BACKUP))
		वापस 0;

	np = of_find_compatible_node(शून्य, शून्य, "atmel,sama5d2-sfrbu");
	अगर (!np) अणु
		pr_warn("%s: failed to find sfrbu!\n", __func__);
		वापस ret;
	पूर्ण

	soc_pm.data.sfrbu = of_iomap(np, 0);
	of_node_put(np);

	np = of_find_compatible_node(शून्य, शून्य, "atmel,sama5d2-securam");
	अगर (!np)
		जाओ securam_fail_no_ref_dev;

	pdev = of_find_device_by_node(np);
	of_node_put(np);
	अगर (!pdev) अणु
		pr_warn("%s: failed to find securam device!\n", __func__);
		जाओ securam_fail_no_ref_dev;
	पूर्ण

	sram_pool = gen_pool_get(&pdev->dev, शून्य);
	अगर (!sram_pool) अणु
		pr_warn("%s: securam pool unavailable!\n", __func__);
		जाओ securam_fail;
	पूर्ण

	pm_bu = (व्योम *)gen_pool_alloc(sram_pool, माप(काष्ठा at91_pm_bu));
	अगर (!pm_bu) अणु
		pr_warn("%s: unable to alloc securam!\n", __func__);
		ret = -ENOMEM;
		जाओ securam_fail;
	पूर्ण

	pm_bu->suspended = 0;
	pm_bu->canary = __pa_symbol(&canary);
	pm_bu->resume = __pa_symbol(cpu_resume);

	वापस 0;

securam_fail:
	put_device(&pdev->dev);
securam_fail_no_ref_dev:
	iounmap(soc_pm.data.sfrbu);
	soc_pm.data.sfrbu = शून्य;
	वापस ret;
पूर्ण

अटल व्योम __init at91_pm_use_शेष_mode(पूर्णांक pm_mode)
अणु
	अगर (pm_mode != AT91_PM_ULP1 && pm_mode != AT91_PM_BACKUP)
		वापस;

	अगर (soc_pm.data.standby_mode == pm_mode)
		soc_pm.data.standby_mode = AT91_PM_ULP0;
	अगर (soc_pm.data.suspend_mode == pm_mode)
		soc_pm.data.suspend_mode = AT91_PM_ULP0;
पूर्ण

अटल स्थिर काष्ठा of_device_id aपंचांगel_shdwc_ids[] = अणु
	अणु .compatible = "atmel,sama5d2-shdwc" पूर्ण,
	अणु .compatible = "microchip,sam9x60-shdwc" पूर्ण,
	अणु /* sentinel. */ पूर्ण
पूर्ण;

अटल व्योम __init at91_pm_modes_init(व्योम)
अणु
	काष्ठा device_node *np;
	पूर्णांक ret;

	अगर (!at91_is_pm_mode_active(AT91_PM_BACKUP) &&
	    !at91_is_pm_mode_active(AT91_PM_ULP1))
		वापस;

	np = of_find_matching_node(शून्य, aपंचांगel_shdwc_ids);
	अगर (!np) अणु
		pr_warn("%s: failed to find shdwc!\n", __func__);
		जाओ ulp1_शेष;
	पूर्ण

	soc_pm.data.shdwc = of_iomap(np, 0);
	of_node_put(np);

	ret = at91_pm_backup_init();
	अगर (ret) अणु
		अगर (!at91_is_pm_mode_active(AT91_PM_ULP1))
			जाओ unmap;
		अन्यथा
			जाओ backup_शेष;
	पूर्ण

	वापस;

unmap:
	iounmap(soc_pm.data.shdwc);
	soc_pm.data.shdwc = शून्य;
ulp1_शेष:
	at91_pm_use_शेष_mode(AT91_PM_ULP1);
backup_शेष:
	at91_pm_use_शेष_mode(AT91_PM_BACKUP);
पूर्ण

काष्ठा pmc_info अणु
	अचिन्हित दीर्घ uhp_udp_mask;
	अचिन्हित दीर्घ mckr;
	अचिन्हित दीर्घ version;
पूर्ण;

अटल स्थिर काष्ठा pmc_info pmc_infos[] __initस्थिर = अणु
	अणु
		.uhp_udp_mask = AT91RM9200_PMC_UHP | AT91RM9200_PMC_UDP,
		.mckr = 0x30,
		.version = AT91_PMC_V1,
	पूर्ण,

	अणु
		.uhp_udp_mask = AT91SAM926x_PMC_UHP | AT91SAM926x_PMC_UDP,
		.mckr = 0x30,
		.version = AT91_PMC_V1,
	पूर्ण,
	अणु
		.uhp_udp_mask = AT91SAM926x_PMC_UHP,
		.mckr = 0x30,
		.version = AT91_PMC_V1,
	पूर्ण,
	अणु	.uhp_udp_mask = 0,
		.mckr = 0x30,
		.version = AT91_PMC_V1,
	पूर्ण,
	अणु
		.uhp_udp_mask = AT91SAM926x_PMC_UHP | AT91SAM926x_PMC_UDP,
		.mckr = 0x28,
		.version = AT91_PMC_V2,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा of_device_id aपंचांगel_pmc_ids[] __initस्थिर = अणु
	अणु .compatible = "atmel,at91rm9200-pmc", .data = &pmc_infos[0] पूर्ण,
	अणु .compatible = "atmel,at91sam9260-pmc", .data = &pmc_infos[1] पूर्ण,
	अणु .compatible = "atmel,at91sam9261-pmc", .data = &pmc_infos[1] पूर्ण,
	अणु .compatible = "atmel,at91sam9263-pmc", .data = &pmc_infos[1] पूर्ण,
	अणु .compatible = "atmel,at91sam9g45-pmc", .data = &pmc_infos[2] पूर्ण,
	अणु .compatible = "atmel,at91sam9n12-pmc", .data = &pmc_infos[1] पूर्ण,
	अणु .compatible = "atmel,at91sam9rl-pmc", .data = &pmc_infos[3] पूर्ण,
	अणु .compatible = "atmel,at91sam9x5-pmc", .data = &pmc_infos[1] पूर्ण,
	अणु .compatible = "atmel,sama5d3-pmc", .data = &pmc_infos[1] पूर्ण,
	अणु .compatible = "atmel,sama5d4-pmc", .data = &pmc_infos[1] पूर्ण,
	अणु .compatible = "atmel,sama5d2-pmc", .data = &pmc_infos[1] पूर्ण,
	अणु .compatible = "microchip,sam9x60-pmc", .data = &pmc_infos[4] पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;

अटल व्योम __init at91_pm_modes_validate(स्थिर पूर्णांक *modes, पूर्णांक len)
अणु
	u8 i, standby = 0, suspend = 0;
	पूर्णांक mode;

	क्रम (i = 0; i < len; i++) अणु
		अगर (standby && suspend)
			अवरोध;

		अगर (modes[i] == soc_pm.data.standby_mode && !standby) अणु
			standby = 1;
			जारी;
		पूर्ण

		अगर (modes[i] == soc_pm.data.suspend_mode && !suspend) अणु
			suspend = 1;
			जारी;
		पूर्ण
	पूर्ण

	अगर (!standby) अणु
		अगर (soc_pm.data.suspend_mode == AT91_PM_STANDBY)
			mode = AT91_PM_ULP0;
		अन्यथा
			mode = AT91_PM_STANDBY;

		pr_warn("AT91: PM: %s mode not supported! Using %s.\n",
			pm_modes[soc_pm.data.standby_mode].pattern,
			pm_modes[mode].pattern);
		soc_pm.data.standby_mode = mode;
	पूर्ण

	अगर (!suspend) अणु
		अगर (soc_pm.data.standby_mode == AT91_PM_ULP0)
			mode = AT91_PM_STANDBY;
		अन्यथा
			mode = AT91_PM_ULP0;

		pr_warn("AT91: PM: %s mode not supported! Using %s.\n",
			pm_modes[soc_pm.data.suspend_mode].pattern,
			pm_modes[mode].pattern);
		soc_pm.data.suspend_mode = mode;
	पूर्ण
पूर्ण

अटल व्योम __init at91_pm_init(व्योम (*pm_idle)(व्योम))
अणु
	काष्ठा device_node *pmc_np;
	स्थिर काष्ठा of_device_id *of_id;
	स्थिर काष्ठा pmc_info *pmc;

	अगर (at91_cpuidle_device.dev.platक्रमm_data)
		platक्रमm_device_रेजिस्टर(&at91_cpuidle_device);

	pmc_np = of_find_matching_node_and_match(शून्य, aपंचांगel_pmc_ids, &of_id);
	soc_pm.data.pmc = of_iomap(pmc_np, 0);
	of_node_put(pmc_np);
	अगर (!soc_pm.data.pmc) अणु
		pr_err("AT91: PM not supported, PMC not found\n");
		वापस;
	पूर्ण

	pmc = of_id->data;
	soc_pm.data.uhp_udp_mask = pmc->uhp_udp_mask;
	soc_pm.data.pmc_mckr_offset = pmc->mckr;
	soc_pm.data.pmc_version = pmc->version;

	अगर (pm_idle)
		arm_pm_idle = pm_idle;

	at91_pm_sram_init();

	अगर (at91_suspend_sram_fn) अणु
		suspend_set_ops(&at91_pm_ops);
		pr_info("AT91: PM: standby: %s, suspend: %s\n",
			pm_modes[soc_pm.data.standby_mode].pattern,
			pm_modes[soc_pm.data.suspend_mode].pattern);
	पूर्ण अन्यथा अणु
		pr_info("AT91: PM not supported, due to no SRAM allocated\n");
	पूर्ण
पूर्ण

व्योम __init at91rm9200_pm_init(व्योम)
अणु
	अगर (!IS_ENABLED(CONFIG_SOC_AT91RM9200))
		वापस;

	/*
	 * Force STANDBY and ULP0 mode to aव्योम calling
	 * at91_pm_modes_validate() which may increase booting समय.
	 * Platक्रमm supports anyway only STANDBY and ULP0 modes.
	 */
	soc_pm.data.standby_mode = AT91_PM_STANDBY;
	soc_pm.data.suspend_mode = AT91_PM_ULP0;

	at91_dt_ramc();

	/*
	 * AT91RM9200 SDRAM low-घातer mode cannot be used with self-refresh.
	 */
	at91_ramc_ग_लिखो(0, AT91_MC_SDRAMC_LPR, 0);

	at91_pm_init(at91rm9200_idle);
पूर्ण

व्योम __init sam9x60_pm_init(व्योम)
अणु
	अटल स्थिर पूर्णांक modes[] __initस्थिर = अणु
		AT91_PM_STANDBY, AT91_PM_ULP0, AT91_PM_ULP0_FAST, AT91_PM_ULP1,
	पूर्ण;

	अगर (!IS_ENABLED(CONFIG_SOC_SAM9X60))
		वापस;

	at91_pm_modes_validate(modes, ARRAY_SIZE(modes));
	at91_pm_modes_init();
	at91_dt_ramc();
	at91_pm_init(शून्य);

	soc_pm.ws_ids = sam9x60_ws_ids;
	soc_pm.config_pmc_ws = at91_sam9x60_config_pmc_ws;
पूर्ण

व्योम __init at91sam9_pm_init(व्योम)
अणु
	अगर (!IS_ENABLED(CONFIG_SOC_AT91SAM9))
		वापस;

	/*
	 * Force STANDBY and ULP0 mode to aव्योम calling
	 * at91_pm_modes_validate() which may increase booting समय.
	 * Platक्रमm supports anyway only STANDBY and ULP0 modes.
	 */
	soc_pm.data.standby_mode = AT91_PM_STANDBY;
	soc_pm.data.suspend_mode = AT91_PM_ULP0;

	at91_dt_ramc();
	at91_pm_init(at91sam9_idle);
पूर्ण

व्योम __init sama5_pm_init(व्योम)
अणु
	अटल स्थिर पूर्णांक modes[] __initस्थिर = अणु
		AT91_PM_STANDBY, AT91_PM_ULP0, AT91_PM_ULP0_FAST,
	पूर्ण;

	अगर (!IS_ENABLED(CONFIG_SOC_SAMA5))
		वापस;

	at91_pm_modes_validate(modes, ARRAY_SIZE(modes));
	at91_dt_ramc();
	at91_pm_init(शून्य);
पूर्ण

व्योम __init sama5d2_pm_init(व्योम)
अणु
	अटल स्थिर पूर्णांक modes[] __initस्थिर = अणु
		AT91_PM_STANDBY, AT91_PM_ULP0, AT91_PM_ULP0_FAST, AT91_PM_ULP1,
		AT91_PM_BACKUP,
	पूर्ण;

	अगर (!IS_ENABLED(CONFIG_SOC_SAMA5D2))
		वापस;

	at91_pm_modes_validate(modes, ARRAY_SIZE(modes));
	at91_pm_modes_init();
	at91_dt_ramc();
	at91_pm_init(शून्य);

	soc_pm.ws_ids = sama5d2_ws_ids;
	soc_pm.config_shdwc_ws = at91_sama5d2_config_shdwc_ws;
	soc_pm.config_pmc_ws = at91_sama5d2_config_pmc_ws;
पूर्ण

अटल पूर्णांक __init at91_pm_modes_select(अक्षर *str)
अणु
	अक्षर *s;
	substring_t args[MAX_OPT_ARGS];
	पूर्णांक standby, suspend;

	अगर (!str)
		वापस 0;

	s = strsep(&str, ",");
	standby = match_token(s, pm_modes, args);
	अगर (standby < 0)
		वापस 0;

	suspend = match_token(str, pm_modes, args);
	अगर (suspend < 0)
		वापस 0;

	soc_pm.data.standby_mode = standby;
	soc_pm.data.suspend_mode = suspend;

	वापस 0;
पूर्ण
early_param("atmel.pm_modes", at91_pm_modes_select);
