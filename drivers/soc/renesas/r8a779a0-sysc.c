<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Renesas R-Car V3U System Controller
 *
 * Copyright (C) 2020 Renesas Electronics Corp.
 */

#समावेश <linux/bits.h>
#समावेश <linux/clk/renesas.h>
#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/iopoll.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/of_address.h>
#समावेश <linux/pm_करोमुख्य.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/types.h>

#समावेश <dt-bindings/घातer/r8a779a0-sysc.h>

/*
 * Power Doमुख्य flags
 */
#घोषणा PD_CPU		BIT(0)	/* Area contains मुख्य CPU core */
#घोषणा PD_SCU		BIT(1)	/* Area contains SCU and L2 cache */
#घोषणा PD_NO_CR	BIT(2)	/* Area lacks PWRअणुON,OFFपूर्णCR रेजिस्टरs */

#घोषणा PD_CPU_NOCR	PD_CPU | PD_NO_CR /* CPU area lacks CR */
#घोषणा PD_ALWAYS_ON	PD_NO_CR	  /* Always-on area */

/*
 * Description of a Power Area
 */
काष्ठा r8a779a0_sysc_area अणु
	स्थिर अक्षर *name;
	u8 pdr;			/* PDRn */
	पूर्णांक parent;		/* -1 अगर none */
	अचिन्हित पूर्णांक flags;	/* See PD_* */
पूर्ण;

/*
 * SoC-specअगरic Power Area Description
 */
काष्ठा r8a779a0_sysc_info अणु
	स्थिर काष्ठा r8a779a0_sysc_area *areas;
	अचिन्हित पूर्णांक num_areas;
पूर्ण;

अटल काष्ठा r8a779a0_sysc_area r8a779a0_areas[] __initdata = अणु
	अणु "always-on",	R8A779A0_PD_ALWAYS_ON, -1, PD_ALWAYS_ON पूर्ण,
	अणु "a3e0",	R8A779A0_PD_A3E0, R8A779A0_PD_ALWAYS_ON, PD_SCU पूर्ण,
	अणु "a3e1",	R8A779A0_PD_A3E1, R8A779A0_PD_ALWAYS_ON, PD_SCU पूर्ण,
	अणु "a2e0d0",	R8A779A0_PD_A2E0D0, R8A779A0_PD_A3E0, PD_SCU पूर्ण,
	अणु "a2e0d1",	R8A779A0_PD_A2E0D1, R8A779A0_PD_A3E0, PD_SCU पूर्ण,
	अणु "a2e1d0",	R8A779A0_PD_A2E1D0, R8A779A0_PD_A3E1, PD_SCU पूर्ण,
	अणु "a2e1d1",	R8A779A0_PD_A2E1D1, R8A779A0_PD_A3E1, PD_SCU पूर्ण,
	अणु "a1e0d0c0",	R8A779A0_PD_A1E0D0C0, R8A779A0_PD_A2E0D0, PD_CPU_NOCR पूर्ण,
	अणु "a1e0d0c1",	R8A779A0_PD_A1E0D0C1, R8A779A0_PD_A2E0D0, PD_CPU_NOCR पूर्ण,
	अणु "a1e0d1c0",	R8A779A0_PD_A1E0D1C0, R8A779A0_PD_A2E0D1, PD_CPU_NOCR पूर्ण,
	अणु "a1e0d1c1",	R8A779A0_PD_A1E0D1C1, R8A779A0_PD_A2E0D1, PD_CPU_NOCR पूर्ण,
	अणु "a1e1d0c0",	R8A779A0_PD_A1E1D0C0, R8A779A0_PD_A2E1D0, PD_CPU_NOCR पूर्ण,
	अणु "a1e1d0c1",	R8A779A0_PD_A1E1D0C1, R8A779A0_PD_A2E1D0, PD_CPU_NOCR पूर्ण,
	अणु "a1e1d1c0",	R8A779A0_PD_A1E1D1C0, R8A779A0_PD_A2E1D1, PD_CPU_NOCR पूर्ण,
	अणु "a1e1d1c1",	R8A779A0_PD_A1E1D1C1, R8A779A0_PD_A2E1D1, PD_CPU_NOCR पूर्ण,
	अणु "3dg-a",	R8A779A0_PD_3DG_A, R8A779A0_PD_ALWAYS_ON पूर्ण,
	अणु "3dg-b",	R8A779A0_PD_3DG_B, R8A779A0_PD_3DG_A पूर्ण,
	अणु "a3vip0",	R8A779A0_PD_A3VIP0, R8A779A0_PD_ALWAYS_ON पूर्ण,
	अणु "a3vip1",	R8A779A0_PD_A3VIP1, R8A779A0_PD_ALWAYS_ON पूर्ण,
	अणु "a3vip3",	R8A779A0_PD_A3VIP3, R8A779A0_PD_ALWAYS_ON पूर्ण,
	अणु "a3vip2",	R8A779A0_PD_A3VIP2, R8A779A0_PD_ALWAYS_ON पूर्ण,
	अणु "a3isp01",	R8A779A0_PD_A3ISP01, R8A779A0_PD_ALWAYS_ON पूर्ण,
	अणु "a3isp23",	R8A779A0_PD_A3ISP23, R8A779A0_PD_ALWAYS_ON पूर्ण,
	अणु "a3ir",	R8A779A0_PD_A3IR, R8A779A0_PD_ALWAYS_ON पूर्ण,
	अणु "a2cn0",	R8A779A0_PD_A2CN0, R8A779A0_PD_A3IR पूर्ण,
	अणु "a2imp01",	R8A779A0_PD_A2IMP01, R8A779A0_PD_A3IR पूर्ण,
	अणु "a2dp0",	R8A779A0_PD_A2DP0, R8A779A0_PD_A3IR पूर्ण,
	अणु "a2cv0",	R8A779A0_PD_A2CV0, R8A779A0_PD_A3IR पूर्ण,
	अणु "a2cv1",	R8A779A0_PD_A2CV1, R8A779A0_PD_A3IR पूर्ण,
	अणु "a2cv4",	R8A779A0_PD_A2CV4, R8A779A0_PD_A3IR पूर्ण,
	अणु "a2cv6",	R8A779A0_PD_A2CV6, R8A779A0_PD_A3IR पूर्ण,
	अणु "a2cn2",	R8A779A0_PD_A2CN2, R8A779A0_PD_A3IR पूर्ण,
	अणु "a2imp23",	R8A779A0_PD_A2IMP23, R8A779A0_PD_A3IR पूर्ण,
	अणु "a2dp1",	R8A779A0_PD_A2DP0, R8A779A0_PD_A3IR पूर्ण,
	अणु "a2cv2",	R8A779A0_PD_A2CV0, R8A779A0_PD_A3IR पूर्ण,
	अणु "a2cv3",	R8A779A0_PD_A2CV1, R8A779A0_PD_A3IR पूर्ण,
	अणु "a2cv5",	R8A779A0_PD_A2CV4, R8A779A0_PD_A3IR पूर्ण,
	अणु "a2cv7",	R8A779A0_PD_A2CV6, R8A779A0_PD_A3IR पूर्ण,
	अणु "a2cn1",	R8A779A0_PD_A2CN1, R8A779A0_PD_A3IR पूर्ण,
	अणु "a1cnn0",	R8A779A0_PD_A1CNN0, R8A779A0_PD_A2CN0 पूर्ण,
	अणु "a1cnn2",	R8A779A0_PD_A1CNN2, R8A779A0_PD_A2CN2 पूर्ण,
	अणु "a1dsp0",	R8A779A0_PD_A1DSP0, R8A779A0_PD_A2CN2 पूर्ण,
	अणु "a1cnn1",	R8A779A0_PD_A1CNN1, R8A779A0_PD_A2CN1 पूर्ण,
	अणु "a1dsp1",	R8A779A0_PD_A1DSP1, R8A779A0_PD_A2CN1 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा r8a779a0_sysc_info r8a779a0_sysc_info __initस्थिर = अणु
	.areas = r8a779a0_areas,
	.num_areas = ARRAY_SIZE(r8a779a0_areas),
पूर्ण;

/* SYSC Common */
#घोषणा SYSCSR		0x000	/* SYSC Status Register */
#घोषणा SYSCPONSR(x)	(0x800 + ((x) * 0x4)) /* Power-ON Status Register 0 */
#घोषणा SYSCPOFFSR(x)	(0x808 + ((x) * 0x4)) /* Power-OFF Status Register */
#घोषणा SYSCISCR(x)	(0x810 + ((x) * 0x4)) /* Interrupt Status/Clear Register */
#घोषणा SYSCIER(x)	(0x820 + ((x) * 0x4)) /* Interrupt Enable Register */
#घोषणा SYSCIMR(x)	(0x830 + ((x) * 0x4)) /* Interrupt Mask Register */

/* Power Doमुख्य Registers */
#घोषणा PDRSR(n)	(0x1000 + ((n) * 0x40))
#घोषणा PDRONCR(n)	(0x1004 + ((n) * 0x40))
#घोषणा PDROFFCR(n)	(0x1008 + ((n) * 0x40))
#घोषणा PDRESR(n)	(0x100C + ((n) * 0x40))

/* PWRON/PWROFF */
#घोषणा PWRON_PWROFF		BIT(0)	/* Power-ON/OFF request */

/* PDRESR */
#घोषणा PDRESR_ERR		BIT(0)

/* PDRSR */
#घोषणा PDRSR_OFF		BIT(0)	/* Power-OFF state */
#घोषणा PDRSR_ON		BIT(4)	/* Power-ON state */
#घोषणा PDRSR_OFF_STATE		BIT(8)  /* Processing Power-OFF sequence */
#घोषणा PDRSR_ON_STATE		BIT(12) /* Processing Power-ON sequence */

#घोषणा SYSCSR_BUSY		GENMASK(1, 0)	/* All bit sets is not busy */

#घोषणा SYSCSR_TIMEOUT		10000
#घोषणा SYSCSR_DELAY_US		10

#घोषणा PDRESR_RETRIES		1000
#घोषणा PDRESR_DELAY_US		10

#घोषणा SYSCISR_TIMEOUT		10000
#घोषणा SYSCISR_DELAY_US	10

#घोषणा NUM_DOMAINS_EACH_REG	BITS_PER_TYPE(u32)

अटल व्योम __iomem *r8a779a0_sysc_base;
अटल DEFINE_SPINLOCK(r8a779a0_sysc_lock); /* SMP CPUs + I/O devices */

अटल पूर्णांक r8a779a0_sysc_pwr_on_off(u8 pdr, bool on)
अणु
	अचिन्हित पूर्णांक reg_offs;
	u32 val;
	पूर्णांक ret;

	अगर (on)
		reg_offs = PDRONCR(pdr);
	अन्यथा
		reg_offs = PDROFFCR(pdr);

	/* Wait until SYSC is पढ़ोy to accept a घातer request */
	ret = पढ़ोl_poll_समयout_atomic(r8a779a0_sysc_base + SYSCSR, val,
					(val & SYSCSR_BUSY) == SYSCSR_BUSY,
					SYSCSR_DELAY_US, SYSCSR_TIMEOUT);
	अगर (ret < 0)
		वापस -EAGAIN;

	/* Submit घातer shutoff or घातer resume request */
	ioग_लिखो32(PWRON_PWROFF, r8a779a0_sysc_base + reg_offs);

	वापस 0;
पूर्ण

अटल पूर्णांक clear_irq_flags(अचिन्हित पूर्णांक reg_idx, अचिन्हित पूर्णांक isr_mask)
अणु
	u32 val;
	पूर्णांक ret;

	ioग_लिखो32(isr_mask, r8a779a0_sysc_base + SYSCISCR(reg_idx));

	ret = पढ़ोl_poll_समयout_atomic(r8a779a0_sysc_base + SYSCISCR(reg_idx),
					val, !(val & isr_mask),
					SYSCISR_DELAY_US, SYSCISR_TIMEOUT);
	अगर (ret < 0) अणु
		pr_err("\n %s : Can not clear IRQ flags in SYSCISCR", __func__);
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक r8a779a0_sysc_घातer(u8 pdr, bool on)
अणु
	अचिन्हित पूर्णांक isr_mask;
	अचिन्हित पूर्णांक reg_idx, bit_idx;
	अचिन्हित पूर्णांक status;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;
	u32 val;
	पूर्णांक k;

	spin_lock_irqsave(&r8a779a0_sysc_lock, flags);

	reg_idx = pdr / NUM_DOMAINS_EACH_REG;
	bit_idx = pdr % NUM_DOMAINS_EACH_REG;

	isr_mask = BIT(bit_idx);

	/*
	 * The पूर्णांकerrupt source needs to be enabled, but masked, to prevent the
	 * CPU from receiving it.
	 */
	ioग_लिखो32(ioपढ़ो32(r8a779a0_sysc_base + SYSCIER(reg_idx)) | isr_mask,
		  r8a779a0_sysc_base + SYSCIER(reg_idx));
	ioग_लिखो32(ioपढ़ो32(r8a779a0_sysc_base + SYSCIMR(reg_idx)) | isr_mask,
		  r8a779a0_sysc_base + SYSCIMR(reg_idx));

	ret = clear_irq_flags(reg_idx, isr_mask);
	अगर (ret)
		जाओ out;

	/* Submit घातer shutoff or resume request until it was accepted */
	क्रम (k = 0; k < PDRESR_RETRIES; k++) अणु
		ret = r8a779a0_sysc_pwr_on_off(pdr, on);
		अगर (ret)
			जाओ out;

		status = ioपढ़ो32(r8a779a0_sysc_base + PDRESR(pdr));
		अगर (!(status & PDRESR_ERR))
			अवरोध;

		udelay(PDRESR_DELAY_US);
	पूर्ण

	अगर (k == PDRESR_RETRIES) अणु
		ret = -EIO;
		जाओ out;
	पूर्ण

	/* Wait until the घातer shutoff or resume request has completed * */
	ret = पढ़ोl_poll_समयout_atomic(r8a779a0_sysc_base + SYSCISCR(reg_idx),
					val, (val & isr_mask),
					SYSCISR_DELAY_US, SYSCISR_TIMEOUT);
	अगर (ret < 0) अणु
		ret = -EIO;
		जाओ out;
	पूर्ण

	/* Clear पूर्णांकerrupt flags */
	ret = clear_irq_flags(reg_idx, isr_mask);
	अगर (ret)
		जाओ out;

 out:
	spin_unlock_irqrestore(&r8a779a0_sysc_lock, flags);

	pr_debug("sysc power %s domain %d: %08x -> %d\n", on ? "on" : "off",
		 pdr, ioपढ़ो32(r8a779a0_sysc_base + SYSCISCR(reg_idx)), ret);
	वापस ret;
पूर्ण

अटल bool r8a779a0_sysc_घातer_is_off(u8 pdr)
अणु
	अचिन्हित पूर्णांक st;

	st = ioपढ़ो32(r8a779a0_sysc_base + PDRSR(pdr));

	अगर (st & PDRSR_OFF)
		वापस true;

	वापस false;
पूर्ण

काष्ठा r8a779a0_sysc_pd अणु
	काष्ठा generic_pm_करोमुख्य genpd;
	u8 pdr;
	अचिन्हित पूर्णांक flags;
	अक्षर name[];
पूर्ण;

अटल अंतरभूत काष्ठा r8a779a0_sysc_pd *to_r8a779a0_pd(काष्ठा generic_pm_करोमुख्य *d)
अणु
	वापस container_of(d, काष्ठा r8a779a0_sysc_pd, genpd);
पूर्ण

अटल पूर्णांक r8a779a0_sysc_pd_घातer_off(काष्ठा generic_pm_करोमुख्य *genpd)
अणु
	काष्ठा r8a779a0_sysc_pd *pd = to_r8a779a0_pd(genpd);

	pr_debug("%s: %s\n", __func__, genpd->name);
	वापस r8a779a0_sysc_घातer(pd->pdr, false);
पूर्ण

अटल पूर्णांक r8a779a0_sysc_pd_घातer_on(काष्ठा generic_pm_करोमुख्य *genpd)
अणु
	काष्ठा r8a779a0_sysc_pd *pd = to_r8a779a0_pd(genpd);

	pr_debug("%s: %s\n", __func__, genpd->name);
	वापस r8a779a0_sysc_घातer(pd->pdr, true);
पूर्ण

अटल पूर्णांक __init r8a779a0_sysc_pd_setup(काष्ठा r8a779a0_sysc_pd *pd)
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
		genpd->attach_dev = cpg_mssr_attach_dev;
		genpd->detach_dev = cpg_mssr_detach_dev;
	पूर्ण

	genpd->घातer_off = r8a779a0_sysc_pd_घातer_off;
	genpd->घातer_on = r8a779a0_sysc_pd_घातer_on;

	अगर (pd->flags & (PD_CPU | PD_NO_CR)) अणु
		/* Skip CPUs (handled by SMP code) and areas without control */
		pr_debug("%s: Not touching %s\n", __func__, genpd->name);
		जाओ finalize;
	पूर्ण

	अगर (!r8a779a0_sysc_घातer_is_off(pd->pdr)) अणु
		pr_debug("%s: %s is already powered\n", __func__, genpd->name);
		जाओ finalize;
	पूर्ण

	r8a779a0_sysc_घातer(pd->pdr, true);

finalize:
	error = pm_genpd_init(genpd, &simple_qos_governor, false);
	अगर (error)
		pr_err("Failed to init PM domain %s: %d\n", name, error);

	वापस error;
पूर्ण

अटल स्थिर काष्ठा of_device_id r8a779a0_sysc_matches[] __initस्थिर = अणु
	अणु .compatible = "renesas,r8a779a0-sysc", .data = &r8a779a0_sysc_info पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;

काष्ठा r8a779a0_pm_करोमुख्यs अणु
	काष्ठा genpd_onecell_data onecell_data;
	काष्ठा generic_pm_करोमुख्य *करोमुख्यs[R8A779A0_PD_ALWAYS_ON + 1];
पूर्ण;

अटल काष्ठा genpd_onecell_data *r8a779a0_sysc_onecell_data;

अटल पूर्णांक __init r8a779a0_sysc_pd_init(व्योम)
अणु
	स्थिर काष्ठा r8a779a0_sysc_info *info;
	स्थिर काष्ठा of_device_id *match;
	काष्ठा r8a779a0_pm_करोमुख्यs *करोमुख्यs;
	काष्ठा device_node *np;
	व्योम __iomem *base;
	अचिन्हित पूर्णांक i;
	पूर्णांक error;

	np = of_find_matching_node_and_match(शून्य, r8a779a0_sysc_matches, &match);
	अगर (!np)
		वापस -ENODEV;

	info = match->data;

	base = of_iomap(np, 0);
	अगर (!base) अणु
		pr_warn("%pOF: Cannot map regs\n", np);
		error = -ENOMEM;
		जाओ out_put;
	पूर्ण

	r8a779a0_sysc_base = base;

	करोमुख्यs = kzalloc(माप(*करोमुख्यs), GFP_KERNEL);
	अगर (!करोमुख्यs) अणु
		error = -ENOMEM;
		जाओ out_put;
	पूर्ण

	करोमुख्यs->onecell_data.करोमुख्यs = करोमुख्यs->करोमुख्यs;
	करोमुख्यs->onecell_data.num_करोमुख्यs = ARRAY_SIZE(करोमुख्यs->करोमुख्यs);
	r8a779a0_sysc_onecell_data = &करोमुख्यs->onecell_data;

	क्रम (i = 0; i < info->num_areas; i++) अणु
		स्थिर काष्ठा r8a779a0_sysc_area *area = &info->areas[i];
		काष्ठा r8a779a0_sysc_pd *pd;

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
		pd->pdr = area->pdr;
		pd->flags = area->flags;

		error = r8a779a0_sysc_pd_setup(pd);
		अगर (error)
			जाओ out_put;

		करोमुख्यs->करोमुख्यs[area->pdr] = &pd->genpd;

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

out_put:
	of_node_put(np);
	वापस error;
पूर्ण
early_initcall(r8a779a0_sysc_pd_init);
