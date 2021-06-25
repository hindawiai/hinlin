<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * R-Car SYSC Power management support
 *
 * Copyright (C) 2014  Magnus Damm
 * Copyright (C) 2015-2017 Glider bvba
 */

#समावेश <linux/clk/renesas.h>
#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/mm.h>
#समावेश <linux/of_address.h>
#समावेश <linux/pm_करोमुख्य.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/पन.स>
#समावेश <linux/iopoll.h>
#समावेश <linux/soc/renesas/rcar-sysc.h>

#समावेश "rcar-sysc.h"

/* SYSC Common */
#घोषणा SYSCSR			0x00	/* SYSC Status Register */
#घोषणा SYSCISR			0x04	/* Interrupt Status Register */
#घोषणा SYSCISCR		0x08	/* Interrupt Status Clear Register */
#घोषणा SYSCIER			0x0c	/* Interrupt Enable Register */
#घोषणा SYSCIMR			0x10	/* Interrupt Mask Register */

/* SYSC Status Register */
#घोषणा SYSCSR_PONENB		1	/* Ready क्रम घातer resume requests */
#घोषणा SYSCSR_POFFENB		0	/* Ready क्रम घातer shutoff requests */

/*
 * Power Control Register Offsets inside the रेजिस्टर block क्रम each करोमुख्य
 * Note: The "CR" रेजिस्टरs क्रम ARM cores exist on H1 only
 *	 Use WFI to घातer off, CPG/APMU to resume ARM cores on R-Car Gen2
 *	 Use PSCI on R-Car Gen3
 */
#घोषणा PWRSR_OFFS		0x00	/* Power Status Register */
#घोषणा PWROFFCR_OFFS		0x04	/* Power Shutoff Control Register */
#घोषणा PWROFFSR_OFFS		0x08	/* Power Shutoff Status Register */
#घोषणा PWRONCR_OFFS		0x0c	/* Power Resume Control Register */
#घोषणा PWRONSR_OFFS		0x10	/* Power Resume Status Register */
#घोषणा PWRER_OFFS		0x14	/* Power Shutoff/Resume Error */


#घोषणा SYSCSR_TIMEOUT		100
#घोषणा SYSCSR_DELAY_US		1

#घोषणा PWRER_RETRIES		100
#घोषणा PWRER_DELAY_US		1

#घोषणा SYSCISR_TIMEOUT		1000
#घोषणा SYSCISR_DELAY_US	1

#घोषणा RCAR_PD_ALWAYS_ON	32	/* Always-on घातer area */

काष्ठा rcar_sysc_ch अणु
	u16 chan_offs;
	u8 chan_bit;
	u8 isr_bit;
पूर्ण;

अटल व्योम __iomem *rcar_sysc_base;
अटल DEFINE_SPINLOCK(rcar_sysc_lock); /* SMP CPUs + I/O devices */
अटल u32 rcar_sysc_exपंचांगask_offs, rcar_sysc_exपंचांगask_val;

अटल पूर्णांक rcar_sysc_pwr_on_off(स्थिर काष्ठा rcar_sysc_ch *sysc_ch, bool on)
अणु
	अचिन्हित पूर्णांक sr_bit, reg_offs;
	u32 val;
	पूर्णांक ret;

	अगर (on) अणु
		sr_bit = SYSCSR_PONENB;
		reg_offs = PWRONCR_OFFS;
	पूर्ण अन्यथा अणु
		sr_bit = SYSCSR_POFFENB;
		reg_offs = PWROFFCR_OFFS;
	पूर्ण

	/* Wait until SYSC is पढ़ोy to accept a घातer request */
	ret = पढ़ोl_poll_समयout_atomic(rcar_sysc_base + SYSCSR, val,
					val & BIT(sr_bit), SYSCSR_DELAY_US,
					SYSCSR_TIMEOUT);
	अगर (ret)
		वापस -EAGAIN;

	/* Submit घातer shutoff or घातer resume request */
	ioग_लिखो32(BIT(sysc_ch->chan_bit),
		  rcar_sysc_base + sysc_ch->chan_offs + reg_offs);

	वापस 0;
पूर्ण

अटल पूर्णांक rcar_sysc_घातer(स्थिर काष्ठा rcar_sysc_ch *sysc_ch, bool on)
अणु
	अचिन्हित पूर्णांक isr_mask = BIT(sysc_ch->isr_bit);
	अचिन्हित पूर्णांक chan_mask = BIT(sysc_ch->chan_bit);
	अचिन्हित पूर्णांक status, k;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	spin_lock_irqsave(&rcar_sysc_lock, flags);

	/*
	 * Mask बाह्यal घातer requests क्रम CPU or 3DG करोमुख्यs
	 */
	अगर (rcar_sysc_exपंचांगask_val) अणु
		ioग_लिखो32(rcar_sysc_exपंचांगask_val,
			  rcar_sysc_base + rcar_sysc_exपंचांगask_offs);
	पूर्ण

	/*
	 * The पूर्णांकerrupt source needs to be enabled, but masked, to prevent the
	 * CPU from receiving it.
	 */
	ioग_लिखो32(ioपढ़ो32(rcar_sysc_base + SYSCIMR) | isr_mask,
		  rcar_sysc_base + SYSCIMR);
	ioग_लिखो32(ioपढ़ो32(rcar_sysc_base + SYSCIER) | isr_mask,
		  rcar_sysc_base + SYSCIER);

	ioग_लिखो32(isr_mask, rcar_sysc_base + SYSCISCR);

	/* Submit घातer shutoff or resume request until it was accepted */
	क्रम (k = 0; k < PWRER_RETRIES; k++) अणु
		ret = rcar_sysc_pwr_on_off(sysc_ch, on);
		अगर (ret)
			जाओ out;

		status = ioपढ़ो32(rcar_sysc_base +
				  sysc_ch->chan_offs + PWRER_OFFS);
		अगर (!(status & chan_mask))
			अवरोध;

		udelay(PWRER_DELAY_US);
	पूर्ण

	अगर (k == PWRER_RETRIES) अणु
		ret = -EIO;
		जाओ out;
	पूर्ण

	/* Wait until the घातer shutoff or resume request has completed * */
	ret = पढ़ोl_poll_समयout_atomic(rcar_sysc_base + SYSCISR, status,
					status & isr_mask, SYSCISR_DELAY_US,
					SYSCISR_TIMEOUT);
	अगर (ret)
		ret = -EIO;

	ioग_लिखो32(isr_mask, rcar_sysc_base + SYSCISCR);

 out:
	अगर (rcar_sysc_exपंचांगask_val)
		ioग_लिखो32(0, rcar_sysc_base + rcar_sysc_exपंचांगask_offs);

	spin_unlock_irqrestore(&rcar_sysc_lock, flags);

	pr_debug("sysc power %s domain %d: %08x -> %d\n", on ? "on" : "off",
		 sysc_ch->isr_bit, ioपढ़ो32(rcar_sysc_base + SYSCISR), ret);
	वापस ret;
पूर्ण

अटल bool rcar_sysc_घातer_is_off(स्थिर काष्ठा rcar_sysc_ch *sysc_ch)
अणु
	अचिन्हित पूर्णांक st;

	st = ioपढ़ो32(rcar_sysc_base + sysc_ch->chan_offs + PWRSR_OFFS);
	अगर (st & BIT(sysc_ch->chan_bit))
		वापस true;

	वापस false;
पूर्ण

काष्ठा rcar_sysc_pd अणु
	काष्ठा generic_pm_करोमुख्य genpd;
	काष्ठा rcar_sysc_ch ch;
	अचिन्हित पूर्णांक flags;
	अक्षर name[];
पूर्ण;

अटल अंतरभूत काष्ठा rcar_sysc_pd *to_rcar_pd(काष्ठा generic_pm_करोमुख्य *d)
अणु
	वापस container_of(d, काष्ठा rcar_sysc_pd, genpd);
पूर्ण

अटल पूर्णांक rcar_sysc_pd_घातer_off(काष्ठा generic_pm_करोमुख्य *genpd)
अणु
	काष्ठा rcar_sysc_pd *pd = to_rcar_pd(genpd);

	pr_debug("%s: %s\n", __func__, genpd->name);
	वापस rcar_sysc_घातer(&pd->ch, false);
पूर्ण

अटल पूर्णांक rcar_sysc_pd_घातer_on(काष्ठा generic_pm_करोमुख्य *genpd)
अणु
	काष्ठा rcar_sysc_pd *pd = to_rcar_pd(genpd);

	pr_debug("%s: %s\n", __func__, genpd->name);
	वापस rcar_sysc_घातer(&pd->ch, true);
पूर्ण

अटल bool has_cpg_mstp;

अटल पूर्णांक __init rcar_sysc_pd_setup(काष्ठा rcar_sysc_pd *pd)
अणु
	काष्ठा generic_pm_करोमुख्य *genpd = &pd->genpd;
	स्थिर अक्षर *name = pd->genpd.name;
	पूर्णांक error;

	अगर (pd->flags & PD_CPU) अणु
		/*
		 * This करोमुख्य contains a CPU core and thereक्रमe it should
		 * only be turned off अगर the CPU is not in use.
		 */
		pr_debug("PM domain %s contains %s\n", name, "CPU");
		genpd->flags |= GENPD_FLAG_ALWAYS_ON;
	पूर्ण अन्यथा अगर (pd->flags & PD_SCU) अणु
		/*
		 * This करोमुख्य contains an SCU and cache-controller, and
		 * thereक्रमe it should only be turned off अगर the CPU cores are
		 * not in use.
		 */
		pr_debug("PM domain %s contains %s\n", name, "SCU");
		genpd->flags |= GENPD_FLAG_ALWAYS_ON;
	पूर्ण अन्यथा अगर (pd->flags & PD_NO_CR) अणु
		/*
		 * This करोमुख्य cannot be turned off.
		 */
		genpd->flags |= GENPD_FLAG_ALWAYS_ON;
	पूर्ण

	अगर (!(pd->flags & (PD_CPU | PD_SCU))) अणु
		/* Enable Clock Doमुख्य क्रम I/O devices */
		genpd->flags |= GENPD_FLAG_PM_CLK | GENPD_FLAG_ACTIVE_WAKEUP;
		अगर (has_cpg_mstp) अणु
			genpd->attach_dev = cpg_mstp_attach_dev;
			genpd->detach_dev = cpg_mstp_detach_dev;
		पूर्ण अन्यथा अणु
			genpd->attach_dev = cpg_mssr_attach_dev;
			genpd->detach_dev = cpg_mssr_detach_dev;
		पूर्ण
	पूर्ण

	genpd->घातer_off = rcar_sysc_pd_घातer_off;
	genpd->घातer_on = rcar_sysc_pd_घातer_on;

	अगर (pd->flags & (PD_CPU | PD_NO_CR)) अणु
		/* Skip CPUs (handled by SMP code) and areas without control */
		pr_debug("%s: Not touching %s\n", __func__, genpd->name);
		जाओ finalize;
	पूर्ण

	अगर (!rcar_sysc_घातer_is_off(&pd->ch)) अणु
		pr_debug("%s: %s is already powered\n", __func__, genpd->name);
		जाओ finalize;
	पूर्ण

	rcar_sysc_घातer(&pd->ch, true);

finalize:
	error = pm_genpd_init(genpd, &simple_qos_governor, false);
	अगर (error)
		pr_err("Failed to init PM domain %s: %d\n", name, error);

	वापस error;
पूर्ण

अटल स्थिर काष्ठा of_device_id rcar_sysc_matches[] __initस्थिर = अणु
#अगर_घोषित CONFIG_SYSC_R8A7742
	अणु .compatible = "renesas,r8a7742-sysc", .data = &r8a7742_sysc_info पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_SYSC_R8A7743
	अणु .compatible = "renesas,r8a7743-sysc", .data = &r8a7743_sysc_info पूर्ण,
	/* RZ/G1N is identical to RZ/G2M w.r.t. घातer करोमुख्यs. */
	अणु .compatible = "renesas,r8a7744-sysc", .data = &r8a7743_sysc_info पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_SYSC_R8A7745
	अणु .compatible = "renesas,r8a7745-sysc", .data = &r8a7745_sysc_info पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_SYSC_R8A77470
	अणु .compatible = "renesas,r8a77470-sysc", .data = &r8a77470_sysc_info पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_SYSC_R8A774A1
	अणु .compatible = "renesas,r8a774a1-sysc", .data = &r8a774a1_sysc_info पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_SYSC_R8A774B1
	अणु .compatible = "renesas,r8a774b1-sysc", .data = &r8a774b1_sysc_info पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_SYSC_R8A774C0
	अणु .compatible = "renesas,r8a774c0-sysc", .data = &r8a774c0_sysc_info पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_SYSC_R8A774E1
	अणु .compatible = "renesas,r8a774e1-sysc", .data = &r8a774e1_sysc_info पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_SYSC_R8A7779
	अणु .compatible = "renesas,r8a7779-sysc", .data = &r8a7779_sysc_info पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_SYSC_R8A7790
	अणु .compatible = "renesas,r8a7790-sysc", .data = &r8a7790_sysc_info पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_SYSC_R8A7791
	अणु .compatible = "renesas,r8a7791-sysc", .data = &r8a7791_sysc_info पूर्ण,
	/* R-Car M2-N is identical to R-Car M2-W w.r.t. घातer करोमुख्यs. */
	अणु .compatible = "renesas,r8a7793-sysc", .data = &r8a7791_sysc_info पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_SYSC_R8A7792
	अणु .compatible = "renesas,r8a7792-sysc", .data = &r8a7792_sysc_info पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_SYSC_R8A7794
	अणु .compatible = "renesas,r8a7794-sysc", .data = &r8a7794_sysc_info पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_SYSC_R8A7795
	अणु .compatible = "renesas,r8a7795-sysc", .data = &r8a7795_sysc_info पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_SYSC_R8A77960
	अणु .compatible = "renesas,r8a7796-sysc", .data = &r8a77960_sysc_info पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_SYSC_R8A77961
	अणु .compatible = "renesas,r8a77961-sysc", .data = &r8a77961_sysc_info पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_SYSC_R8A77965
	अणु .compatible = "renesas,r8a77965-sysc", .data = &r8a77965_sysc_info पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_SYSC_R8A77970
	अणु .compatible = "renesas,r8a77970-sysc", .data = &r8a77970_sysc_info पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_SYSC_R8A77980
	अणु .compatible = "renesas,r8a77980-sysc", .data = &r8a77980_sysc_info पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_SYSC_R8A77990
	अणु .compatible = "renesas,r8a77990-sysc", .data = &r8a77990_sysc_info पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_SYSC_R8A77995
	अणु .compatible = "renesas,r8a77995-sysc", .data = &r8a77995_sysc_info पूर्ण,
#पूर्ण_अगर
	अणु /* sentinel */ पूर्ण
पूर्ण;

काष्ठा rcar_pm_करोमुख्यs अणु
	काष्ठा genpd_onecell_data onecell_data;
	काष्ठा generic_pm_करोमुख्य *करोमुख्यs[RCAR_PD_ALWAYS_ON + 1];
पूर्ण;

अटल काष्ठा genpd_onecell_data *rcar_sysc_onecell_data;

अटल पूर्णांक __init rcar_sysc_pd_init(व्योम)
अणु
	स्थिर काष्ठा rcar_sysc_info *info;
	स्थिर काष्ठा of_device_id *match;
	काष्ठा rcar_pm_करोमुख्यs *करोमुख्यs;
	काष्ठा device_node *np;
	व्योम __iomem *base;
	अचिन्हित पूर्णांक i;
	पूर्णांक error;

	np = of_find_matching_node_and_match(शून्य, rcar_sysc_matches, &match);
	अगर (!np)
		वापस -ENODEV;

	info = match->data;

	अगर (info->init) अणु
		error = info->init();
		अगर (error)
			जाओ out_put;
	पूर्ण

	has_cpg_mstp = of_find_compatible_node(शून्य, शून्य,
					       "renesas,cpg-mstp-clocks");

	base = of_iomap(np, 0);
	अगर (!base) अणु
		pr_warn("%pOF: Cannot map regs\n", np);
		error = -ENOMEM;
		जाओ out_put;
	पूर्ण

	rcar_sysc_base = base;

	/* Optional External Request Mask Register */
	rcar_sysc_exपंचांगask_offs = info->exपंचांगask_offs;
	rcar_sysc_exपंचांगask_val = info->exपंचांगask_val;

	करोमुख्यs = kzalloc(माप(*करोमुख्यs), GFP_KERNEL);
	अगर (!करोमुख्यs) अणु
		error = -ENOMEM;
		जाओ out_put;
	पूर्ण

	करोमुख्यs->onecell_data.करोमुख्यs = करोमुख्यs->करोमुख्यs;
	करोमुख्यs->onecell_data.num_करोमुख्यs = ARRAY_SIZE(करोमुख्यs->करोमुख्यs);
	rcar_sysc_onecell_data = &करोमुख्यs->onecell_data;

	क्रम (i = 0; i < info->num_areas; i++) अणु
		स्थिर काष्ठा rcar_sysc_area *area = &info->areas[i];
		काष्ठा rcar_sysc_pd *pd;

		अगर (!area->name) अणु
			/* Skip शून्यअगरied area */
			जारी;
		पूर्ण

		pd = kzalloc(माप(*pd) + म_माप(area->name) + 1, GFP_KERNEL);
		अगर (!pd) अणु
			error = -ENOMEM;
			जाओ out_put;
		पूर्ण

		म_नकल(pd->name, area->name);
		pd->genpd.name = pd->name;
		pd->ch.chan_offs = area->chan_offs;
		pd->ch.chan_bit = area->chan_bit;
		pd->ch.isr_bit = area->isr_bit;
		pd->flags = area->flags;

		error = rcar_sysc_pd_setup(pd);
		अगर (error)
			जाओ out_put;

		करोमुख्यs->करोमुख्यs[area->isr_bit] = &pd->genpd;

		अगर (area->parent < 0)
			जारी;

		error = pm_genpd_add_subकरोमुख्य(करोमुख्यs->करोमुख्यs[area->parent],
					       &pd->genpd);
		अगर (error) अणु
			pr_warn("Failed to add PM subdomain %s to parent %u\n",
				area->name, area->parent);
			जाओ out_put;
		पूर्ण
	पूर्ण

	error = of_genpd_add_provider_onecell(np, &करोमुख्यs->onecell_data);
	अगर (!error)
		of_node_set_flag(np, OF_POPULATED);

out_put:
	of_node_put(np);
	वापस error;
पूर्ण
early_initcall(rcar_sysc_pd_init);

व्योम __init rcar_sysc_nullअगरy(काष्ठा rcar_sysc_area *areas,
			      अचिन्हित पूर्णांक num_areas, u8 id)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < num_areas; i++)
		अगर (areas[i].isr_bit == id) अणु
			areas[i].name = शून्य;
			वापस;
		पूर्ण
पूर्ण

#अगर_घोषित CONFIG_ARCH_R8A7779
अटल पूर्णांक rcar_sysc_घातer_cpu(अचिन्हित पूर्णांक idx, bool on)
अणु
	काष्ठा generic_pm_करोमुख्य *genpd;
	काष्ठा rcar_sysc_pd *pd;
	अचिन्हित पूर्णांक i;

	अगर (!rcar_sysc_onecell_data)
		वापस -ENODEV;

	क्रम (i = 0; i < rcar_sysc_onecell_data->num_करोमुख्यs; i++) अणु
		genpd = rcar_sysc_onecell_data->करोमुख्यs[i];
		अगर (!genpd)
			जारी;

		pd = to_rcar_pd(genpd);
		अगर (!(pd->flags & PD_CPU) || pd->ch.chan_bit != idx)
			जारी;

		वापस rcar_sysc_घातer(&pd->ch, on);
	पूर्ण

	वापस -ENOENT;
पूर्ण

पूर्णांक rcar_sysc_घातer_करोwn_cpu(अचिन्हित पूर्णांक cpu)
अणु
	वापस rcar_sysc_घातer_cpu(cpu, false);
पूर्ण

पूर्णांक rcar_sysc_घातer_up_cpu(अचिन्हित पूर्णांक cpu)
अणु
	वापस rcar_sysc_घातer_cpu(cpu, true);
पूर्ण
#पूर्ण_अगर /* CONFIG_ARCH_R8A7779 */
