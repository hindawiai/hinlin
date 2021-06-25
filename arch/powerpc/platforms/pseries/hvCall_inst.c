<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2006 Mike Kravetz IBM Corporation
 *
 * Hypervisor Call Instrumentation
 */

#समावेश <linux/kernel.h>
#समावेश <linux/percpu.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/cpumask.h>
#समावेश <यंत्र/hvcall.h>
#समावेश <यंत्र/firmware.h>
#समावेश <यंत्र/cputable.h>
#समावेश <यंत्र/trace.h>
#समावेश <यंत्र/machdep.h>

/* For hcall instrumentation. One काष्ठाure per-hcall, per-CPU */
काष्ठा hcall_stats अणु
	अचिन्हित दीर्घ	num_calls;	/* number of calls (on this CPU) */
	अचिन्हित दीर्घ	tb_total;	/* total wall समय (mftb) of calls. */
	अचिन्हित दीर्घ	purr_total;	/* total cpu समय (PURR) of calls. */
	अचिन्हित दीर्घ	tb_start;
	अचिन्हित दीर्घ	purr_start;
पूर्ण;
#घोषणा HCALL_STAT_ARRAY_SIZE	((MAX_HCALL_OPCODE >> 2) + 1)

अटल DEFINE_PER_CPU(काष्ठा hcall_stats[HCALL_STAT_ARRAY_SIZE], hcall_stats);

/*
 * Routines क्रम displaying the statistics in debugfs
 */
अटल व्योम *hc_start(काष्ठा seq_file *m, loff_t *pos)
अणु
	अगर ((पूर्णांक)*pos < (HCALL_STAT_ARRAY_SIZE-1))
		वापस (व्योम *)(अचिन्हित दीर्घ)(*pos + 1);

	वापस शून्य;
पूर्ण

अटल व्योम *hc_next(काष्ठा seq_file *m, व्योम *p, loff_t * pos)
अणु
	++*pos;

	वापस hc_start(m, pos);
पूर्ण

अटल व्योम hc_stop(काष्ठा seq_file *m, व्योम *p)
अणु
पूर्ण

अटल पूर्णांक hc_show(काष्ठा seq_file *m, व्योम *p)
अणु
	अचिन्हित दीर्घ h_num = (अचिन्हित दीर्घ)p;
	काष्ठा hcall_stats *hs = m->निजी;

	अगर (hs[h_num].num_calls) अणु
		अगर (cpu_has_feature(CPU_FTR_PURR))
			seq_म_लिखो(m, "%lu %lu %lu %lu\n", h_num<<2,
				   hs[h_num].num_calls,
				   hs[h_num].tb_total,
				   hs[h_num].purr_total);
		अन्यथा
			seq_म_लिखो(m, "%lu %lu %lu\n", h_num<<2,
				   hs[h_num].num_calls,
				   hs[h_num].tb_total);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा seq_operations hcall_inst_sops = अणु
        .start = hc_start,
        .next  = hc_next,
        .stop  = hc_stop,
        .show  = hc_show
पूर्ण;

DEFINE_SEQ_ATTRIBUTE(hcall_inst);

#घोषणा	HCALL_ROOT_सूची		"hcall_inst"
#घोषणा CPU_NAME_BUF_SIZE	32


अटल व्योम probe_hcall_entry(व्योम *ignored, अचिन्हित दीर्घ opcode, अचिन्हित दीर्घ *args)
अणु
	काष्ठा hcall_stats *h;

	अगर (opcode > MAX_HCALL_OPCODE)
		वापस;

	h = this_cpu_ptr(&hcall_stats[opcode / 4]);
	h->tb_start = mftb();
	h->purr_start = mfspr(SPRN_PURR);
पूर्ण

अटल व्योम probe_hcall_निकास(व्योम *ignored, अचिन्हित दीर्घ opcode, दीर्घ retval,
			     अचिन्हित दीर्घ *retbuf)
अणु
	काष्ठा hcall_stats *h;

	अगर (opcode > MAX_HCALL_OPCODE)
		वापस;

	h = this_cpu_ptr(&hcall_stats[opcode / 4]);
	h->num_calls++;
	h->tb_total += mftb() - h->tb_start;
	h->purr_total += mfspr(SPRN_PURR) - h->purr_start;
पूर्ण

अटल पूर्णांक __init hcall_inst_init(व्योम)
अणु
	काष्ठा dentry *hcall_root;
	अक्षर cpu_name_buf[CPU_NAME_BUF_SIZE];
	पूर्णांक cpu;

	अगर (!firmware_has_feature(FW_FEATURE_LPAR))
		वापस 0;

	अगर (रेजिस्टर_trace_hcall_entry(probe_hcall_entry, शून्य))
		वापस -EINVAL;

	अगर (रेजिस्टर_trace_hcall_निकास(probe_hcall_निकास, शून्य)) अणु
		unरेजिस्टर_trace_hcall_entry(probe_hcall_entry, शून्य);
		वापस -EINVAL;
	पूर्ण

	hcall_root = debugfs_create_dir(HCALL_ROOT_सूची, शून्य);

	क्रम_each_possible_cpu(cpu) अणु
		snम_लिखो(cpu_name_buf, CPU_NAME_BUF_SIZE, "cpu%d", cpu);
		debugfs_create_file(cpu_name_buf, 0444, hcall_root,
				    per_cpu(hcall_stats, cpu),
				    &hcall_inst_fops);
	पूर्ण

	वापस 0;
पूर्ण
machine_device_initcall(pseries, hcall_inst_init);
