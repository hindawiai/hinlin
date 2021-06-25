<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/seq_file.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <यंत्र/machvec.h>
#समावेश <यंत्र/processor.h>

अटल स्थिर अक्षर *cpu_name[] = अणु
	[CPU_SH7201]	= "SH7201",
	[CPU_SH7203]	= "SH7203",	[CPU_SH7263]	= "SH7263",
	[CPU_SH7264]	= "SH7264",	[CPU_SH7269]	= "SH7269",
	[CPU_SH7206]	= "SH7206",	[CPU_SH7619]	= "SH7619",
	[CPU_SH7705]	= "SH7705",	[CPU_SH7706]	= "SH7706",
	[CPU_SH7707]	= "SH7707",	[CPU_SH7708]	= "SH7708",
	[CPU_SH7709]	= "SH7709",	[CPU_SH7710]	= "SH7710",
	[CPU_SH7712]	= "SH7712",	[CPU_SH7720]	= "SH7720",
	[CPU_SH7721]	= "SH7721",	[CPU_SH7729]	= "SH7729",
	[CPU_SH7750]	= "SH7750",	[CPU_SH7750S]	= "SH7750S",
	[CPU_SH7750R]	= "SH7750R",	[CPU_SH7751]	= "SH7751",
	[CPU_SH7751R]	= "SH7751R",	[CPU_SH7760]	= "SH7760",
	[CPU_SH4_202]	= "SH4-202",	[CPU_SH4_501]	= "SH4-501",
	[CPU_SH7763]	= "SH7763",	[CPU_SH7770]	= "SH7770",
	[CPU_SH7780]	= "SH7780",	[CPU_SH7781]	= "SH7781",
	[CPU_SH7343]	= "SH7343",	[CPU_SH7785]	= "SH7785",
	[CPU_SH7786]	= "SH7786",	[CPU_SH7757]	= "SH7757",
	[CPU_SH7722]	= "SH7722",	[CPU_SHX3]	= "SH-X3",
	[CPU_MXG]	= "MX-G",	[CPU_SH7723]	= "SH7723",
	[CPU_SH7366]	= "SH7366",	[CPU_SH7724]	= "SH7724",
	[CPU_SH7372]	= "SH7372",	[CPU_SH7734]	= "SH7734",
	[CPU_J2]	= "J2",
	[CPU_SH_NONE]	= "Unknown"
पूर्ण;

स्थिर अक्षर *get_cpu_subtype(काष्ठा sh_cpuinfo *c)
अणु
	वापस cpu_name[c->type];
पूर्ण
EXPORT_SYMBOL(get_cpu_subtype);

#अगर_घोषित CONFIG_PROC_FS
/* Symbolic CPU flags, keep in sync with यंत्र/cpu-features.h */
अटल स्थिर अक्षर *cpu_flags[] = अणु
	"none", "fpu", "p2flush", "mmuassoc", "dsp", "perfctr",
	"ptea", "llsc", "l2", "op32", "pteaex", शून्य
पूर्ण;

अटल व्योम show_cpuflags(काष्ठा seq_file *m, काष्ठा sh_cpuinfo *c)
अणु
	अचिन्हित दीर्घ i;

	seq_म_लिखो(m, "cpu flags\t:");

	अगर (!c->flags) अणु
		seq_म_लिखो(m, " %s\n", cpu_flags[0]);
		वापस;
	पूर्ण

	क्रम (i = 0; cpu_flags[i]; i++)
		अगर ((c->flags & (1 << i)))
			seq_म_लिखो(m, " %s", cpu_flags[i+1]);

	seq_म_लिखो(m, "\n");
पूर्ण

अटल व्योम show_cacheinfo(काष्ठा seq_file *m, स्थिर अक्षर *type,
			   काष्ठा cache_info info)
अणु
	अचिन्हित पूर्णांक cache_size;

	cache_size = info.ways * info.sets * info.linesz;

	seq_म_लिखो(m, "%s size\t: %2dKiB (%d-way)\n",
		   type, cache_size >> 10, info.ways);
पूर्ण

/*
 *	Get CPU inक्रमmation क्रम use by the procfs.
 */
अटल पूर्णांक show_cpuinfo(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा sh_cpuinfo *c = v;
	अचिन्हित पूर्णांक cpu = c - cpu_data;

	अगर (!cpu_online(cpu))
		वापस 0;

	अगर (cpu == 0)
		seq_म_लिखो(m, "machine\t\t: %s\n", get_प्रणाली_type());
	अन्यथा
		seq_म_लिखो(m, "\n");

	seq_म_लिखो(m, "processor\t: %d\n", cpu);
	seq_म_लिखो(m, "cpu family\t: %s\n", init_utsname()->machine);
	seq_म_लिखो(m, "cpu type\t: %s\n", get_cpu_subtype(c));
	अगर (c->cut_major == -1)
		seq_म_लिखो(m, "cut\t\t: unknown\n");
	अन्यथा अगर (c->cut_minor == -1)
		seq_म_लिखो(m, "cut\t\t: %d.x\n", c->cut_major);
	अन्यथा
		seq_म_लिखो(m, "cut\t\t: %d.%d\n", c->cut_major, c->cut_minor);

	show_cpuflags(m, c);

	seq_म_लिखो(m, "cache type\t: ");

	/*
	 * Check क्रम what type of cache we have, we support both the
	 * unअगरied cache on the SH-2 and SH-3, as well as the harvard
	 * style cache on the SH-4.
	 */
	अगर (c->icache.flags & SH_CACHE_COMBINED) अणु
		seq_म_लिखो(m, "unified\n");
		show_cacheinfo(m, "cache", c->icache);
	पूर्ण अन्यथा अणु
		seq_म_लिखो(m, "split (harvard)\n");
		show_cacheinfo(m, "icache", c->icache);
		show_cacheinfo(m, "dcache", c->dcache);
	पूर्ण

	/* Optional secondary cache */
	अगर (c->flags & CPU_HAS_L2_CACHE)
		show_cacheinfo(m, "scache", c->scache);

	seq_म_लिखो(m, "address sizes\t: %u bits physical\n", c->phys_bits);

	seq_म_लिखो(m, "bogomips\t: %lu.%02lu\n",
		     c->loops_per_jअगरfy/(500000/HZ),
		     (c->loops_per_jअगरfy/(5000/HZ)) % 100);

	वापस 0;
पूर्ण

अटल व्योम *c_start(काष्ठा seq_file *m, loff_t *pos)
अणु
	वापस *pos < NR_CPUS ? cpu_data + *pos : शून्य;
पूर्ण
अटल व्योम *c_next(काष्ठा seq_file *m, व्योम *v, loff_t *pos)
अणु
	++*pos;
	वापस c_start(m, pos);
पूर्ण
अटल व्योम c_stop(काष्ठा seq_file *m, व्योम *v)
अणु
पूर्ण
स्थिर काष्ठा seq_operations cpuinfo_op = अणु
	.start	= c_start,
	.next	= c_next,
	.stop	= c_stop,
	.show	= show_cpuinfo,
पूर्ण;
#पूर्ण_अगर /* CONFIG_PROC_FS */
