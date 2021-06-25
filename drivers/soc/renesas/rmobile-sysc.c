<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * rmobile घातer management support
 *
 * Copyright (C) 2012  Renesas Solutions Corp.
 * Copyright (C) 2012  Kuninori Morimoto <kuninori.morimoto.gx@renesas.com>
 * Copyright (C) 2014  Glider bvba
 *
 * based on pm-sh7372.c
 *  Copyright (C) 2011 Magnus Damm
 */
#समावेश <linux/clk/renesas.h>
#समावेश <linux/console.h>
#समावेश <linux/delay.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/pm.h>
#समावेश <linux/pm_घड़ी.h>
#समावेश <linux/pm_करोमुख्य.h>
#समावेश <linux/slab.h>

#समावेश <यंत्र/पन.स>

/* SYSC */
#घोषणा SPDCR		0x08	/* SYS Power Down Control Register */
#घोषणा SWUCR		0x14	/* SYS Wakeup Control Register */
#घोषणा PSTR		0x80	/* Power Status Register */

#घोषणा PSTR_RETRIES	100
#घोषणा PSTR_DELAY_US	10

काष्ठा rmobile_pm_करोमुख्य अणु
	काष्ठा generic_pm_करोमुख्य genpd;
	काष्ठा dev_घातer_governor *gov;
	पूर्णांक (*suspend)(व्योम);
	व्योम __iomem *base;
	अचिन्हित पूर्णांक bit_shअगरt;
पूर्ण;

अटल अंतरभूत
काष्ठा rmobile_pm_करोमुख्य *to_rmobile_pd(काष्ठा generic_pm_करोमुख्य *d)
अणु
	वापस container_of(d, काष्ठा rmobile_pm_करोमुख्य, genpd);
पूर्ण

अटल पूर्णांक rmobile_pd_घातer_करोwn(काष्ठा generic_pm_करोमुख्य *genpd)
अणु
	काष्ठा rmobile_pm_करोमुख्य *rmobile_pd = to_rmobile_pd(genpd);
	अचिन्हित पूर्णांक mask = BIT(rmobile_pd->bit_shअगरt);

	अगर (rmobile_pd->suspend) अणु
		पूर्णांक ret = rmobile_pd->suspend();

		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (पढ़ोl(rmobile_pd->base + PSTR) & mask) अणु
		अचिन्हित पूर्णांक retry_count;
		ग_लिखोl(mask, rmobile_pd->base + SPDCR);

		क्रम (retry_count = PSTR_RETRIES; retry_count; retry_count--) अणु
			अगर (!(पढ़ोl(rmobile_pd->base + SPDCR) & mask))
				अवरोध;
			cpu_relax();
		पूर्ण
	पूर्ण

	pr_debug("%s: Power off, 0x%08x -> PSTR = 0x%08x\n", genpd->name, mask,
		 पढ़ोl(rmobile_pd->base + PSTR));

	वापस 0;
पूर्ण

अटल पूर्णांक __rmobile_pd_घातer_up(काष्ठा rmobile_pm_करोमुख्य *rmobile_pd)
अणु
	अचिन्हित पूर्णांक mask = BIT(rmobile_pd->bit_shअगरt);
	अचिन्हित पूर्णांक retry_count;
	पूर्णांक ret = 0;

	अगर (पढ़ोl(rmobile_pd->base + PSTR) & mask)
		वापस ret;

	ग_लिखोl(mask, rmobile_pd->base + SWUCR);

	क्रम (retry_count = 2 * PSTR_RETRIES; retry_count; retry_count--) अणु
		अगर (!(पढ़ोl(rmobile_pd->base + SWUCR) & mask))
			अवरोध;
		अगर (retry_count > PSTR_RETRIES)
			udelay(PSTR_DELAY_US);
		अन्यथा
			cpu_relax();
	पूर्ण
	अगर (!retry_count)
		ret = -EIO;

	pr_debug("%s: Power on, 0x%08x -> PSTR = 0x%08x\n",
		 rmobile_pd->genpd.name, mask,
		 पढ़ोl(rmobile_pd->base + PSTR));

	वापस ret;
पूर्ण

अटल पूर्णांक rmobile_pd_घातer_up(काष्ठा generic_pm_करोमुख्य *genpd)
अणु
	वापस __rmobile_pd_घातer_up(to_rmobile_pd(genpd));
पूर्ण

अटल व्योम rmobile_init_pm_करोमुख्य(काष्ठा rmobile_pm_करोमुख्य *rmobile_pd)
अणु
	काष्ठा generic_pm_करोमुख्य *genpd = &rmobile_pd->genpd;
	काष्ठा dev_घातer_governor *gov = rmobile_pd->gov;

	genpd->flags |= GENPD_FLAG_PM_CLK | GENPD_FLAG_ACTIVE_WAKEUP;
	genpd->attach_dev = cpg_mstp_attach_dev;
	genpd->detach_dev = cpg_mstp_detach_dev;

	अगर (!(genpd->flags & GENPD_FLAG_ALWAYS_ON)) अणु
		genpd->घातer_off = rmobile_pd_घातer_करोwn;
		genpd->घातer_on = rmobile_pd_घातer_up;
		__rmobile_pd_घातer_up(rmobile_pd);
	पूर्ण

	pm_genpd_init(genpd, gov ? : &simple_qos_governor, false);
पूर्ण

अटल पूर्णांक rmobile_pd_suspend_console(व्योम)
अणु
	/*
	 * Serial consoles make use of SCIF hardware located in this करोमुख्य,
	 * hence keep the घातer करोमुख्य on अगर "no_console_suspend" is set.
	 */
	वापस console_suspend_enabled ? 0 : -EBUSY;
पूर्ण

क्रमागत pd_types अणु
	PD_NORMAL,
	PD_CPU,
	PD_CONSOLE,
	PD_DEBUG,
	PD_MEMCTL,
पूर्ण;

#घोषणा MAX_NUM_SPECIAL_PDS	16

अटल काष्ठा special_pd अणु
	काष्ठा device_node *pd;
	क्रमागत pd_types type;
पूर्ण special_pds[MAX_NUM_SPECIAL_PDS] __initdata;

अटल अचिन्हित पूर्णांक num_special_pds __initdata;

अटल स्थिर काष्ठा of_device_id special_ids[] __initस्थिर = अणु
	अणु .compatible = "arm,coresight-etm3x", .data = (व्योम *)PD_DEBUG पूर्ण,
	अणु .compatible = "renesas,dbsc-r8a73a4", .data = (व्योम *)PD_MEMCTL, पूर्ण,
	अणु .compatible = "renesas,dbsc3-r8a7740", .data = (व्योम *)PD_MEMCTL, पूर्ण,
	अणु .compatible = "renesas,sbsc-sh73a0", .data = (व्योम *)PD_MEMCTL, पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;

अटल व्योम __init add_special_pd(काष्ठा device_node *np, क्रमागत pd_types type)
अणु
	अचिन्हित पूर्णांक i;
	काष्ठा device_node *pd;

	pd = of_parse_phandle(np, "power-domains", 0);
	अगर (!pd)
		वापस;

	क्रम (i = 0; i < num_special_pds; i++)
		अगर (pd == special_pds[i].pd && type == special_pds[i].type) अणु
			of_node_put(pd);
			वापस;
		पूर्ण

	अगर (num_special_pds == ARRAY_SIZE(special_pds)) अणु
		pr_warn("Too many special PM domains\n");
		of_node_put(pd);
		वापस;
	पूर्ण

	pr_debug("Special PM domain %pOFn type %d for %pOF\n", pd, type, np);

	special_pds[num_special_pds].pd = pd;
	special_pds[num_special_pds].type = type;
	num_special_pds++;
पूर्ण

अटल व्योम __init get_special_pds(व्योम)
अणु
	काष्ठा device_node *np;
	स्थिर काष्ठा of_device_id *id;

	/* PM करोमुख्यs containing CPUs */
	क्रम_each_of_cpu_node(np)
		add_special_pd(np, PD_CPU);

	/* PM करोमुख्य containing console */
	अगर (of_मानक_निकास)
		add_special_pd(of_मानक_निकास, PD_CONSOLE);

	/* PM करोमुख्यs containing other special devices */
	क्रम_each_matching_node_and_match(np, special_ids, &id)
		add_special_pd(np, (क्रमागत pd_types)id->data);
पूर्ण

अटल व्योम __init put_special_pds(व्योम)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < num_special_pds; i++)
		of_node_put(special_pds[i].pd);
पूर्ण

अटल क्रमागत pd_types __init pd_type(स्थिर काष्ठा device_node *pd)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < num_special_pds; i++)
		अगर (pd == special_pds[i].pd)
			वापस special_pds[i].type;

	वापस PD_NORMAL;
पूर्ण

अटल व्योम __init rmobile_setup_pm_करोमुख्य(काष्ठा device_node *np,
					   काष्ठा rmobile_pm_करोमुख्य *pd)
अणु
	स्थिर अक्षर *name = pd->genpd.name;

	चयन (pd_type(np)) अणु
	हाल PD_CPU:
		/*
		 * This करोमुख्य contains the CPU core and thereक्रमe it should
		 * only be turned off अगर the CPU is not in use.
		 */
		pr_debug("PM domain %s contains CPU\n", name);
		pd->genpd.flags |= GENPD_FLAG_ALWAYS_ON;
		अवरोध;

	हाल PD_CONSOLE:
		pr_debug("PM domain %s contains serial console\n", name);
		pd->gov = &pm_करोमुख्य_always_on_gov;
		pd->suspend = rmobile_pd_suspend_console;
		अवरोध;

	हाल PD_DEBUG:
		/*
		 * This करोमुख्य contains the Coresight-ETM hardware block and
		 * thereक्रमe it should only be turned off अगर the debug module
		 * is not in use.
		 */
		pr_debug("PM domain %s contains Coresight-ETM\n", name);
		pd->genpd.flags |= GENPD_FLAG_ALWAYS_ON;
		अवरोध;

	हाल PD_MEMCTL:
		/*
		 * This करोमुख्य contains a memory-controller and thereक्रमe it
		 * should only be turned off अगर memory is not in use.
		 */
		pr_debug("PM domain %s contains MEMCTL\n", name);
		pd->genpd.flags |= GENPD_FLAG_ALWAYS_ON;
		अवरोध;

	हाल PD_NORMAL:
		अगर (pd->bit_shअगरt == ~0) अणु
			/* Top-level always-on करोमुख्य */
			pr_debug("PM domain %s is always-on domain\n", name);
			pd->genpd.flags |= GENPD_FLAG_ALWAYS_ON;
		पूर्ण
		अवरोध;
	पूर्ण

	rmobile_init_pm_करोमुख्य(pd);
पूर्ण

अटल पूर्णांक __init rmobile_add_pm_करोमुख्यs(व्योम __iomem *base,
					 काष्ठा device_node *parent,
					 काष्ठा generic_pm_करोमुख्य *genpd_parent)
अणु
	काष्ठा device_node *np;

	क्रम_each_child_of_node(parent, np) अणु
		काष्ठा rmobile_pm_करोमुख्य *pd;
		u32 idx = ~0;

		अगर (of_property_पढ़ो_u32(np, "reg", &idx)) अणु
			/* always-on करोमुख्य */
		पूर्ण

		pd = kzalloc(माप(*pd), GFP_KERNEL);
		अगर (!pd) अणु
			of_node_put(np);
			वापस -ENOMEM;
		पूर्ण

		pd->genpd.name = np->name;
		pd->base = base;
		pd->bit_shअगरt = idx;

		rmobile_setup_pm_करोमुख्य(np, pd);
		अगर (genpd_parent)
			pm_genpd_add_subकरोमुख्य(genpd_parent, &pd->genpd);
		of_genpd_add_provider_simple(np, &pd->genpd);

		rmobile_add_pm_करोमुख्यs(base, np, &pd->genpd);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक __init rmobile_init_pm_करोमुख्यs(व्योम)
अणु
	काष्ठा device_node *np, *pmd;
	bool scanned = false;
	व्योम __iomem *base;
	पूर्णांक ret = 0;

	क्रम_each_compatible_node(np, शून्य, "renesas,sysc-rmobile") अणु
		base = of_iomap(np, 0);
		अगर (!base) अणु
			pr_warn("%pOF cannot map reg 0\n", np);
			जारी;
		पूर्ण

		pmd = of_get_child_by_name(np, "pm-domains");
		अगर (!pmd) अणु
			iounmap(base);
			pr_warn("%pOF lacks pm-domains node\n", np);
			जारी;
		पूर्ण

		अगर (!scanned) अणु
			/* Find PM करोमुख्यs containing special blocks */
			get_special_pds();
			scanned = true;
		पूर्ण

		ret = rmobile_add_pm_करोमुख्यs(base, pmd, शून्य);
		of_node_put(pmd);
		अगर (ret) अणु
			of_node_put(np);
			अवरोध;
		पूर्ण

		fwnode_dev_initialized(&np->fwnode, true);
	पूर्ण

	put_special_pds();

	वापस ret;
पूर्ण

core_initcall(rmobile_init_pm_करोमुख्यs);
