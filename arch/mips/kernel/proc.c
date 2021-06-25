<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  Copyright (C) 1995, 1996, 2001  Ralf Baechle
 *  Copyright (C) 2001, 2004  MIPS Technologies, Inc.
 *  Copyright (C) 2004	Maciej W. Rozycki
 */
#समावेश <linux/delay.h>
#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <linux/seq_file.h>
#समावेश <यंत्र/bootinfo.h>
#समावेश <यंत्र/cpu.h>
#समावेश <यंत्र/cpu-features.h>
#समावेश <यंत्र/idle.h>
#समावेश <यंत्र/mipsregs.h>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/prom.h>

अचिन्हित पूर्णांक vced_count, vcei_count;

/*
 *  * No lock; only written during early bootup by CPU 0.
 *   */
अटल RAW_NOTIFIER_HEAD(proc_cpuinfo_chain);

पूर्णांक __ref रेजिस्टर_proc_cpuinfo_notअगरier(काष्ठा notअगरier_block *nb)
अणु
	वापस raw_notअगरier_chain_रेजिस्टर(&proc_cpuinfo_chain, nb);
पूर्ण

पूर्णांक proc_cpuinfo_notअगरier_call_chain(अचिन्हित दीर्घ val, व्योम *v)
अणु
	वापस raw_notअगरier_call_chain(&proc_cpuinfo_chain, val, v);
पूर्ण

अटल पूर्णांक show_cpuinfo(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा proc_cpuinfo_notअगरier_args proc_cpuinfo_notअगरier_args;
	अचिन्हित दीर्घ n = (अचिन्हित दीर्घ) v - 1;
	अचिन्हित पूर्णांक version = cpu_data[n].processor_id;
	अचिन्हित पूर्णांक fp_vers = cpu_data[n].fpu_id;
	अक्षर fmt [64];
	पूर्णांक i;

#अगर_घोषित CONFIG_SMP
	अगर (!cpu_online(n))
		वापस 0;
#पूर्ण_अगर

	/*
	 * For the first processor also prपूर्णांक the प्रणाली type
	 */
	अगर (n == 0) अणु
		seq_म_लिखो(m, "system type\t\t: %s\n", get_प्रणाली_type());
		अगर (mips_get_machine_name())
			seq_म_लिखो(m, "machine\t\t\t: %s\n",
				   mips_get_machine_name());
	पूर्ण

	seq_म_लिखो(m, "processor\t\t: %ld\n", n);
	प्र_लिखो(fmt, "cpu model\t\t: %%s V%%d.%%d%s\n",
		      cpu_data[n].options & MIPS_CPU_FPU ? "  FPU V%d.%d" : "");
	seq_म_लिखो(m, fmt, __cpu_name[n],
		      (version >> 4) & 0x0f, version & 0x0f,
		      (fp_vers >> 4) & 0x0f, fp_vers & 0x0f);
	seq_म_लिखो(m, "BogoMIPS\t\t: %u.%02u\n",
		      cpu_data[n].udelay_val / (500000/HZ),
		      (cpu_data[n].udelay_val / (5000/HZ)) % 100);
	seq_म_लिखो(m, "wait instruction\t: %s\n", cpu_रुको ? "yes" : "no");
	seq_म_लिखो(m, "microsecond timers\t: %s\n",
		      cpu_has_counter ? "yes" : "no");
	seq_म_लिखो(m, "tlb_entries\t\t: %d\n", cpu_data[n].tlbsize);
	seq_म_लिखो(m, "extra interrupt vector\t: %s\n",
		      cpu_has_भागec ? "yes" : "no");
	seq_म_लिखो(m, "hardware watchpoint\t: %s",
		      cpu_has_watch ? "yes, " : "no\n");
	अगर (cpu_has_watch) अणु
		seq_म_लिखो(m, "count: %d, address/irw mask: [",
		      cpu_data[n].watch_reg_count);
		क्रम (i = 0; i < cpu_data[n].watch_reg_count; i++)
			seq_म_लिखो(m, "%s0x%04x", i ? ", " : "" ,
				cpu_data[n].watch_reg_masks[i]);
		seq_म_लिखो(m, "]\n");
	पूर्ण

	seq_म_लिखो(m, "isa\t\t\t:"); 
	अगर (cpu_has_mips_1)
		seq_म_लिखो(m, " mips1");
	अगर (cpu_has_mips_2)
		seq_म_लिखो(m, "%s", " mips2");
	अगर (cpu_has_mips_3)
		seq_म_लिखो(m, "%s", " mips3");
	अगर (cpu_has_mips_4)
		seq_म_लिखो(m, "%s", " mips4");
	अगर (cpu_has_mips_5)
		seq_म_लिखो(m, "%s", " mips5");
	अगर (cpu_has_mips32r1)
		seq_म_लिखो(m, "%s", " mips32r1");
	अगर (cpu_has_mips32r2)
		seq_म_लिखो(m, "%s", " mips32r2");
	अगर (cpu_has_mips32r5)
		seq_म_लिखो(m, "%s", " mips32r5");
	अगर (cpu_has_mips32r6)
		seq_म_लिखो(m, "%s", " mips32r6");
	अगर (cpu_has_mips64r1)
		seq_म_लिखो(m, "%s", " mips64r1");
	अगर (cpu_has_mips64r2)
		seq_म_लिखो(m, "%s", " mips64r2");
	अगर (cpu_has_mips64r5)
		seq_म_लिखो(m, "%s", " mips64r5");
	अगर (cpu_has_mips64r6)
		seq_म_लिखो(m, "%s", " mips64r6");
	seq_म_लिखो(m, "\n");

	seq_म_लिखो(m, "ASEs implemented\t:");
	अगर (cpu_has_mips16)	seq_म_लिखो(m, "%s", " mips16");
	अगर (cpu_has_mips16e2)	seq_म_लिखो(m, "%s", " mips16e2");
	अगर (cpu_has_mdmx)	seq_म_लिखो(m, "%s", " mdmx");
	अगर (cpu_has_mips3d)	seq_म_लिखो(m, "%s", " mips3d");
	अगर (cpu_has_smarपंचांगips)	seq_म_लिखो(m, "%s", " smartmips");
	अगर (cpu_has_dsp)	seq_म_लिखो(m, "%s", " dsp");
	अगर (cpu_has_dsp2)	seq_म_लिखो(m, "%s", " dsp2");
	अगर (cpu_has_dsp3)	seq_म_लिखो(m, "%s", " dsp3");
	अगर (cpu_has_mipsmt)	seq_म_लिखो(m, "%s", " mt");
	अगर (cpu_has_mmips)	seq_म_लिखो(m, "%s", " micromips");
	अगर (cpu_has_vz)		seq_म_लिखो(m, "%s", " vz");
	अगर (cpu_has_msa)	seq_म_लिखो(m, "%s", " msa");
	अगर (cpu_has_eva)	seq_म_लिखो(m, "%s", " eva");
	अगर (cpu_has_htw)	seq_म_लिखो(m, "%s", " htw");
	अगर (cpu_has_xpa)	seq_म_लिखो(m, "%s", " xpa");
	अगर (cpu_has_loongson_mmi)	seq_म_लिखो(m, "%s", " loongson-mmi");
	अगर (cpu_has_loongson_cam)	seq_म_लिखो(m, "%s", " loongson-cam");
	अगर (cpu_has_loongson_ext)	seq_म_लिखो(m, "%s", " loongson-ext");
	अगर (cpu_has_loongson_ext2)	seq_म_लिखो(m, "%s", " loongson-ext2");
	seq_म_लिखो(m, "\n");

	अगर (cpu_has_mmips) अणु
		seq_म_लिखो(m, "micromips kernel\t: %s\n",
		      (पढ़ो_c0_config3() & MIPS_CONF3_ISA_OE) ?  "yes" : "no");
	पूर्ण
	seq_म_लिखो(m, "shadow register sets\t: %d\n",
		      cpu_data[n].srsets);
	seq_म_लिखो(m, "kscratch registers\t: %d\n",
		      hweight8(cpu_data[n].kscratch_mask));
	seq_म_लिखो(m, "package\t\t\t: %d\n", cpu_data[n].package);
	seq_म_लिखो(m, "core\t\t\t: %d\n", cpu_core(&cpu_data[n]));

#अगर defined(CONFIG_MIPS_MT_SMP) || defined(CONFIG_CPU_MIPSR6)
	अगर (cpu_has_mipsmt)
		seq_म_लिखो(m, "VPE\t\t\t: %d\n", cpu_vpe_id(&cpu_data[n]));
	अन्यथा अगर (cpu_has_vp)
		seq_म_लिखो(m, "VP\t\t\t: %d\n", cpu_vpe_id(&cpu_data[n]));
#पूर्ण_अगर

	प्र_लिखो(fmt, "VCE%%c exceptions\t\t: %s\n",
		      cpu_has_vce ? "%u" : "not available");
	seq_म_लिखो(m, fmt, 'D', vced_count);
	seq_म_लिखो(m, fmt, 'I', vcei_count);

	proc_cpuinfo_notअगरier_args.m = m;
	proc_cpuinfo_notअगरier_args.n = n;

	raw_notअगरier_call_chain(&proc_cpuinfo_chain, 0,
				&proc_cpuinfo_notअगरier_args);

	seq_म_लिखो(m, "\n");

	वापस 0;
पूर्ण

अटल व्योम *c_start(काष्ठा seq_file *m, loff_t *pos)
अणु
	अचिन्हित दीर्घ i = *pos;

	वापस i < NR_CPUS ? (व्योम *) (i + 1) : शून्य;
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
