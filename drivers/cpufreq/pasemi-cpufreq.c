<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2007 PA Semi, Inc
 *
 * Authors: Egor Martovetsky <egor@pasemi.com>
 *	    Olof Johansson <olof@lixom.net>
 *
 * Maपूर्णांकained by: Olof Johansson <olof@lixom.net>
 *
 * Based on arch/घातerpc/platक्रमms/cell/cbe_cpufreq.c:
 * (C) Copyright IBM Deutschland Entwicklung GmbH 2005
 */

#समावेश <linux/cpufreq.h>
#समावेश <linux/समयr.h>
#समावेश <linux/module.h>
#समावेश <linux/of_address.h>

#समावेश <यंत्र/hw_irq.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/समय.स>
#समावेश <यंत्र/smp.h>

#समावेश <platक्रमms/pasemi/pasemi.h>

#घोषणा SDCASR_REG		0x0100
#घोषणा SDCASR_REG_STRIDE	0x1000
#घोषणा SDCPWR_CFGA0_REG	0x0100
#घोषणा SDCPWR_PWST0_REG	0x0000
#घोषणा SDCPWR_GIZTIME_REG	0x0440

/* SDCPWR_GIZTIME_REG fields */
#घोषणा SDCPWR_GIZTIME_GR	0x80000000
#घोषणा SDCPWR_GIZTIME_LONGLOCK	0x000000ff

/* Offset of ASR रेजिस्टरs from SDC base */
#घोषणा SDCASR_OFFSET		0x120000

अटल व्योम __iomem *sdcpwr_mapbase;
अटल व्योम __iomem *sdcasr_mapbase;

/* Current astate, is used when waking up from घातer savings on
 * one core, in हाल the other core has चयनed states during
 * the idle समय.
 */
अटल पूर्णांक current_astate;

/* We support 5(A0-A4) घातer states excluding turbo(A5-A6) modes */
अटल काष्ठा cpufreq_frequency_table pas_freqs[] = अणु
	अणु0, 0,	0पूर्ण,
	अणु0, 1,	0पूर्ण,
	अणु0, 2,	0पूर्ण,
	अणु0, 3,	0पूर्ण,
	अणु0, 4,	0पूर्ण,
	अणु0, 0,	CPUFREQ_TABLE_ENDपूर्ण,
पूर्ण;

/*
 * hardware specअगरic functions
 */

अटल पूर्णांक get_astate_freq(पूर्णांक astate)
अणु
	u32 ret;
	ret = in_le32(sdcpwr_mapbase + SDCPWR_CFGA0_REG + (astate * 0x10));

	वापस ret & 0x3f;
पूर्ण

अटल पूर्णांक get_cur_astate(पूर्णांक cpu)
अणु
	u32 ret;

	ret = in_le32(sdcpwr_mapbase + SDCPWR_PWST0_REG);
	ret = (ret >> (cpu * 4)) & 0x7;

	वापस ret;
पूर्ण

अटल पूर्णांक get_gizmo_latency(व्योम)
अणु
	u32 gizसमय, ret;

	gizसमय = in_le32(sdcpwr_mapbase + SDCPWR_GIZTIME_REG);

	/* just provide the upper bound */
	अगर (gizसमय & SDCPWR_GIZTIME_GR)
		ret = (gizसमय & SDCPWR_GIZTIME_LONGLOCK) * 128000;
	अन्यथा
		ret = (gizसमय & SDCPWR_GIZTIME_LONGLOCK) * 1000;

	वापस ret;
पूर्ण

अटल व्योम set_astate(पूर्णांक cpu, अचिन्हित पूर्णांक astate)
अणु
	अचिन्हित दीर्घ flags;

	/* Return अगर called beक्रमe init has run */
	अगर (unlikely(!sdcasr_mapbase))
		वापस;

	local_irq_save(flags);

	out_le32(sdcasr_mapbase + SDCASR_REG + SDCASR_REG_STRIDE*cpu, astate);

	local_irq_restore(flags);
पूर्ण

पूर्णांक check_astate(व्योम)
अणु
	वापस get_cur_astate(hard_smp_processor_id());
पूर्ण

व्योम restore_astate(पूर्णांक cpu)
अणु
	set_astate(cpu, current_astate);
पूर्ण

/*
 * cpufreq functions
 */

अटल पूर्णांक pas_cpufreq_cpu_init(काष्ठा cpufreq_policy *policy)
अणु
	काष्ठा cpufreq_frequency_table *pos;
	स्थिर u32 *max_freqp;
	u32 max_freq;
	पूर्णांक cur_astate, idx;
	काष्ठा resource res;
	काष्ठा device_node *cpu, *dn;
	पूर्णांक err = -ENODEV;

	cpu = of_get_cpu_node(policy->cpu, शून्य);
	अगर (!cpu)
		जाओ out;

	max_freqp = of_get_property(cpu, "clock-frequency", शून्य);
	of_node_put(cpu);
	अगर (!max_freqp) अणु
		err = -EINVAL;
		जाओ out;
	पूर्ण

	/* we need the freq in kHz */
	max_freq = *max_freqp / 1000;

	dn = of_find_compatible_node(शून्य, शून्य, "1682m-sdc");
	अगर (!dn)
		dn = of_find_compatible_node(शून्य, शून्य,
					     "pasemi,pwrficient-sdc");
	अगर (!dn)
		जाओ out;
	err = of_address_to_resource(dn, 0, &res);
	of_node_put(dn);
	अगर (err)
		जाओ out;
	sdcasr_mapbase = ioremap(res.start + SDCASR_OFFSET, 0x2000);
	अगर (!sdcasr_mapbase) अणु
		err = -EINVAL;
		जाओ out;
	पूर्ण

	dn = of_find_compatible_node(शून्य, शून्य, "1682m-gizmo");
	अगर (!dn)
		dn = of_find_compatible_node(शून्य, शून्य,
					     "pasemi,pwrficient-gizmo");
	अगर (!dn) अणु
		err = -ENODEV;
		जाओ out_unmap_sdcasr;
	पूर्ण
	err = of_address_to_resource(dn, 0, &res);
	of_node_put(dn);
	अगर (err)
		जाओ out_unmap_sdcasr;
	sdcpwr_mapbase = ioremap(res.start, 0x1000);
	अगर (!sdcpwr_mapbase) अणु
		err = -EINVAL;
		जाओ out_unmap_sdcasr;
	पूर्ण

	pr_debug("init cpufreq on CPU %d\n", policy->cpu);
	pr_debug("max clock-frequency is at %u kHz\n", max_freq);
	pr_debug("initializing frequency table\n");

	/* initialize frequency table */
	cpufreq_क्रम_each_entry_idx(pos, pas_freqs, idx) अणु
		pos->frequency = get_astate_freq(pos->driver_data) * 100000;
		pr_debug("%d: %d\n", idx, pos->frequency);
	पूर्ण

	cur_astate = get_cur_astate(policy->cpu);
	pr_debug("current astate is at %d\n",cur_astate);

	policy->cur = pas_freqs[cur_astate].frequency;
	ppc_proc_freq = policy->cur * 1000ul;

	cpufreq_generic_init(policy, pas_freqs, get_gizmo_latency());
	वापस 0;

out_unmap_sdcasr:
	iounmap(sdcasr_mapbase);
out:
	वापस err;
पूर्ण

अटल पूर्णांक pas_cpufreq_cpu_निकास(काष्ठा cpufreq_policy *policy)
अणु
	/*
	 * We करोn't support CPU hotplug. Don't unmap after the प्रणाली
	 * has alपढ़ोy made it to a running state.
	 */
	अगर (प्रणाली_state >= SYSTEM_RUNNING)
		वापस 0;

	अगर (sdcasr_mapbase)
		iounmap(sdcasr_mapbase);
	अगर (sdcpwr_mapbase)
		iounmap(sdcpwr_mapbase);

	वापस 0;
पूर्ण

अटल पूर्णांक pas_cpufreq_target(काष्ठा cpufreq_policy *policy,
			      अचिन्हित पूर्णांक pas_astate_new)
अणु
	पूर्णांक i;

	pr_debug("setting frequency for cpu %d to %d kHz, 1/%d of max frequency\n",
		 policy->cpu,
		 pas_freqs[pas_astate_new].frequency,
		 pas_freqs[pas_astate_new].driver_data);

	current_astate = pas_astate_new;

	क्रम_each_online_cpu(i)
		set_astate(i, pas_astate_new);

	ppc_proc_freq = pas_freqs[pas_astate_new].frequency * 1000ul;
	वापस 0;
पूर्ण

अटल काष्ठा cpufreq_driver pas_cpufreq_driver = अणु
	.name		= "pas-cpufreq",
	.flags		= CPUFREQ_CONST_LOOPS,
	.init		= pas_cpufreq_cpu_init,
	.निकास		= pas_cpufreq_cpu_निकास,
	.verअगरy		= cpufreq_generic_frequency_table_verअगरy,
	.target_index	= pas_cpufreq_target,
	.attr		= cpufreq_generic_attr,
पूर्ण;

/*
 * module init and destoy
 */

अटल पूर्णांक __init pas_cpufreq_init(व्योम)
अणु
	अगर (!of_machine_is_compatible("PA6T-1682M") &&
	    !of_machine_is_compatible("pasemi,pwrficient"))
		वापस -ENODEV;

	वापस cpufreq_रेजिस्टर_driver(&pas_cpufreq_driver);
पूर्ण

अटल व्योम __निकास pas_cpufreq_निकास(व्योम)
अणु
	cpufreq_unरेजिस्टर_driver(&pas_cpufreq_driver);
पूर्ण

module_init(pas_cpufreq_init);
module_निकास(pas_cpufreq_निकास);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Egor Martovetsky <egor@pasemi.com>, Olof Johansson <olof@lixom.net>");
