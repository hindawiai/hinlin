<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/cpumask.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/fs.h>
#समावेश <linux/init.h>
#समावेश <linux/percpu.h>
#समावेश <linux/types.h>
#समावेश <यंत्र/debug.h>
#समावेश <यंत्र/fpu_emulator.h>
#समावेश <यंत्र/local.h>

DEFINE_PER_CPU(काष्ठा mips_fpu_emulator_stats, fpuemustats);

अटल पूर्णांक fpuemu_stat_get(व्योम *data, u64 *val)
अणु
	पूर्णांक cpu;
	अचिन्हित दीर्घ sum = 0;

	क्रम_each_online_cpu(cpu) अणु
		काष्ठा mips_fpu_emulator_stats *ps;
		local_t *pv;

		ps = &per_cpu(fpuemustats, cpu);
		pv = (व्योम *)ps + (अचिन्हित दीर्घ)data;
		sum += local_पढ़ो(pv);
	पूर्ण
	*val = sum;
	वापस 0;
पूर्ण
DEFINE_SIMPLE_ATTRIBUTE(fops_fpuemu_stat, fpuemu_stat_get, शून्य, "%llu\n");

/*
 * Used to obtain names क्रम a debugfs inकाष्ठाion counter, given field name
 * in fpuemustats काष्ठाure. For example, क्रम input "cmp_sueq_d", the output
 * would be "cmp.sueq.d". This is needed since करोts are not allowed to be
 * used in काष्ठाure field names, and are, on the other hand, desired to be
 * used in debugfs item names to be clearly associated to corresponding
 * MIPS FPU inकाष्ठाions.
 */
अटल व्योम adjust_inकाष्ठाion_counter_name(अक्षर *out_name, अक्षर *in_name)
अणु
	पूर्णांक i = 0;

	म_नकल(out_name, in_name);
	जबतक (in_name[i] != '\0') अणु
		अगर (out_name[i] == '_')
			out_name[i] = '.';
		i++;
	पूर्ण
पूर्ण

अटल पूर्णांक fpuemustats_clear_show(काष्ठा seq_file *s, व्योम *unused)
अणु
	__this_cpu_ग_लिखो((fpuemustats).emulated, 0);
	__this_cpu_ग_लिखो((fpuemustats).loads, 0);
	__this_cpu_ग_लिखो((fpuemustats).stores, 0);
	__this_cpu_ग_लिखो((fpuemustats).branches, 0);
	__this_cpu_ग_लिखो((fpuemustats).cp1ops, 0);
	__this_cpu_ग_लिखो((fpuemustats).cp1xops, 0);
	__this_cpu_ग_लिखो((fpuemustats).errors, 0);
	__this_cpu_ग_लिखो((fpuemustats).ieee754_inexact, 0);
	__this_cpu_ग_लिखो((fpuemustats).ieee754_underflow, 0);
	__this_cpu_ग_लिखो((fpuemustats).ieee754_overflow, 0);
	__this_cpu_ग_लिखो((fpuemustats).ieee754_zeroभाग, 0);
	__this_cpu_ग_लिखो((fpuemustats).ieee754_invaliकरोp, 0);
	__this_cpu_ग_लिखो((fpuemustats).ds_emul, 0);

	__this_cpu_ग_लिखो((fpuemustats).असल_s, 0);
	__this_cpu_ग_लिखो((fpuemustats).असल_d, 0);
	__this_cpu_ग_लिखो((fpuemustats).add_s, 0);
	__this_cpu_ग_लिखो((fpuemustats).add_d, 0);
	__this_cpu_ग_लिखो((fpuemustats).bc1eqz, 0);
	__this_cpu_ग_लिखो((fpuemustats).bc1nez, 0);
	__this_cpu_ग_लिखो((fpuemustats).उच्चमान_w_s, 0);
	__this_cpu_ग_लिखो((fpuemustats).उच्चमान_w_d, 0);
	__this_cpu_ग_लिखो((fpuemustats).उच्चमान_l_s, 0);
	__this_cpu_ग_लिखो((fpuemustats).उच्चमान_l_d, 0);
	__this_cpu_ग_लिखो((fpuemustats).class_s, 0);
	__this_cpu_ग_लिखो((fpuemustats).class_d, 0);
	__this_cpu_ग_लिखो((fpuemustats).cmp_af_s, 0);
	__this_cpu_ग_लिखो((fpuemustats).cmp_af_d, 0);
	__this_cpu_ग_लिखो((fpuemustats).cmp_eq_s, 0);
	__this_cpu_ग_लिखो((fpuemustats).cmp_eq_d, 0);
	__this_cpu_ग_लिखो((fpuemustats).cmp_le_s, 0);
	__this_cpu_ग_लिखो((fpuemustats).cmp_le_d, 0);
	__this_cpu_ग_लिखो((fpuemustats).cmp_lt_s, 0);
	__this_cpu_ग_लिखो((fpuemustats).cmp_lt_d, 0);
	__this_cpu_ग_लिखो((fpuemustats).cmp_ne_s, 0);
	__this_cpu_ग_लिखो((fpuemustats).cmp_ne_d, 0);
	__this_cpu_ग_लिखो((fpuemustats).cmp_or_s, 0);
	__this_cpu_ग_लिखो((fpuemustats).cmp_or_d, 0);
	__this_cpu_ग_लिखो((fpuemustats).cmp_ueq_s, 0);
	__this_cpu_ग_लिखो((fpuemustats).cmp_ueq_d, 0);
	__this_cpu_ग_लिखो((fpuemustats).cmp_ule_s, 0);
	__this_cpu_ग_लिखो((fpuemustats).cmp_ule_d, 0);
	__this_cpu_ग_लिखो((fpuemustats).cmp_ult_s, 0);
	__this_cpu_ग_लिखो((fpuemustats).cmp_ult_d, 0);
	__this_cpu_ग_लिखो((fpuemustats).cmp_un_s, 0);
	__this_cpu_ग_लिखो((fpuemustats).cmp_un_d, 0);
	__this_cpu_ग_लिखो((fpuemustats).cmp_une_s, 0);
	__this_cpu_ग_लिखो((fpuemustats).cmp_une_d, 0);
	__this_cpu_ग_लिखो((fpuemustats).cmp_saf_s, 0);
	__this_cpu_ग_लिखो((fpuemustats).cmp_saf_d, 0);
	__this_cpu_ग_लिखो((fpuemustats).cmp_seq_s, 0);
	__this_cpu_ग_लिखो((fpuemustats).cmp_seq_d, 0);
	__this_cpu_ग_लिखो((fpuemustats).cmp_sle_s, 0);
	__this_cpu_ग_लिखो((fpuemustats).cmp_sle_d, 0);
	__this_cpu_ग_लिखो((fpuemustats).cmp_slt_s, 0);
	__this_cpu_ग_लिखो((fpuemustats).cmp_slt_d, 0);
	__this_cpu_ग_लिखो((fpuemustats).cmp_sne_s, 0);
	__this_cpu_ग_लिखो((fpuemustats).cmp_sne_d, 0);
	__this_cpu_ग_लिखो((fpuemustats).cmp_sor_s, 0);
	__this_cpu_ग_लिखो((fpuemustats).cmp_sor_d, 0);
	__this_cpu_ग_लिखो((fpuemustats).cmp_sueq_s, 0);
	__this_cpu_ग_लिखो((fpuemustats).cmp_sueq_d, 0);
	__this_cpu_ग_लिखो((fpuemustats).cmp_sule_s, 0);
	__this_cpu_ग_लिखो((fpuemustats).cmp_sule_d, 0);
	__this_cpu_ग_लिखो((fpuemustats).cmp_sult_s, 0);
	__this_cpu_ग_लिखो((fpuemustats).cmp_sult_d, 0);
	__this_cpu_ग_लिखो((fpuemustats).cmp_sun_s, 0);
	__this_cpu_ग_लिखो((fpuemustats).cmp_sun_d, 0);
	__this_cpu_ग_लिखो((fpuemustats).cmp_sune_s, 0);
	__this_cpu_ग_लिखो((fpuemustats).cmp_sune_d, 0);
	__this_cpu_ग_लिखो((fpuemustats).cvt_d_l, 0);
	__this_cpu_ग_लिखो((fpuemustats).cvt_d_s, 0);
	__this_cpu_ग_लिखो((fpuemustats).cvt_d_w, 0);
	__this_cpu_ग_लिखो((fpuemustats).cvt_l_s, 0);
	__this_cpu_ग_लिखो((fpuemustats).cvt_l_d, 0);
	__this_cpu_ग_लिखो((fpuemustats).cvt_s_d, 0);
	__this_cpu_ग_लिखो((fpuemustats).cvt_s_l, 0);
	__this_cpu_ग_लिखो((fpuemustats).cvt_s_w, 0);
	__this_cpu_ग_लिखो((fpuemustats).cvt_w_s, 0);
	__this_cpu_ग_लिखो((fpuemustats).cvt_w_d, 0);
	__this_cpu_ग_लिखो((fpuemustats).भाग_s, 0);
	__this_cpu_ग_लिखो((fpuemustats).भाग_d, 0);
	__this_cpu_ग_लिखो((fpuemustats).न्यूनमान_w_s, 0);
	__this_cpu_ग_लिखो((fpuemustats).न्यूनमान_w_d, 0);
	__this_cpu_ग_लिखो((fpuemustats).न्यूनमान_l_s, 0);
	__this_cpu_ग_लिखो((fpuemustats).न्यूनमान_l_d, 0);
	__this_cpu_ग_लिखो((fpuemustats).maddf_s, 0);
	__this_cpu_ग_लिखो((fpuemustats).maddf_d, 0);
	__this_cpu_ग_लिखो((fpuemustats).max_s, 0);
	__this_cpu_ग_लिखो((fpuemustats).max_d, 0);
	__this_cpu_ग_लिखो((fpuemustats).maxa_s, 0);
	__this_cpu_ग_लिखो((fpuemustats).maxa_d, 0);
	__this_cpu_ग_लिखो((fpuemustats).min_s, 0);
	__this_cpu_ग_लिखो((fpuemustats).min_d, 0);
	__this_cpu_ग_लिखो((fpuemustats).mina_s, 0);
	__this_cpu_ग_लिखो((fpuemustats).mina_d, 0);
	__this_cpu_ग_लिखो((fpuemustats).mov_s, 0);
	__this_cpu_ग_लिखो((fpuemustats).mov_d, 0);
	__this_cpu_ग_लिखो((fpuemustats).msubf_s, 0);
	__this_cpu_ग_लिखो((fpuemustats).msubf_d, 0);
	__this_cpu_ग_लिखो((fpuemustats).mul_s, 0);
	__this_cpu_ग_लिखो((fpuemustats).mul_d, 0);
	__this_cpu_ग_लिखो((fpuemustats).neg_s, 0);
	__this_cpu_ग_लिखो((fpuemustats).neg_d, 0);
	__this_cpu_ग_लिखो((fpuemustats).recip_s, 0);
	__this_cpu_ग_लिखो((fpuemustats).recip_d, 0);
	__this_cpu_ग_लिखो((fpuemustats).rपूर्णांक_s, 0);
	__this_cpu_ग_लिखो((fpuemustats).rपूर्णांक_d, 0);
	__this_cpu_ग_लिखो((fpuemustats).round_w_s, 0);
	__this_cpu_ग_लिखो((fpuemustats).round_w_d, 0);
	__this_cpu_ग_लिखो((fpuemustats).round_l_s, 0);
	__this_cpu_ग_लिखो((fpuemustats).round_l_d, 0);
	__this_cpu_ग_लिखो((fpuemustats).rवर्ग_मूल_s, 0);
	__this_cpu_ग_लिखो((fpuemustats).rवर्ग_मूल_d, 0);
	__this_cpu_ग_लिखो((fpuemustats).sel_s, 0);
	__this_cpu_ग_लिखो((fpuemustats).sel_d, 0);
	__this_cpu_ग_लिखो((fpuemustats).seleqz_s, 0);
	__this_cpu_ग_लिखो((fpuemustats).seleqz_d, 0);
	__this_cpu_ग_लिखो((fpuemustats).selnez_s, 0);
	__this_cpu_ग_लिखो((fpuemustats).selnez_d, 0);
	__this_cpu_ग_लिखो((fpuemustats).वर्ग_मूल_s, 0);
	__this_cpu_ग_लिखो((fpuemustats).वर्ग_मूल_d, 0);
	__this_cpu_ग_लिखो((fpuemustats).sub_s, 0);
	__this_cpu_ग_लिखो((fpuemustats).sub_d, 0);
	__this_cpu_ग_लिखो((fpuemustats).trunc_w_s, 0);
	__this_cpu_ग_लिखो((fpuemustats).trunc_w_d, 0);
	__this_cpu_ग_लिखो((fpuemustats).trunc_l_s, 0);
	__this_cpu_ग_लिखो((fpuemustats).trunc_l_d, 0);

	वापस 0;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(fpuemustats_clear);

अटल पूर्णांक __init debugfs_fpuemu(व्योम)
अणु
	काष्ठा dentry *fpuemu_debugfs_base_dir;
	काष्ठा dentry *fpuemu_debugfs_inst_dir;
	अक्षर name[32];

	fpuemu_debugfs_base_dir = debugfs_create_dir("fpuemustats",
						     mips_debugfs_dir);

	debugfs_create_file("fpuemustats_clear", 0444, mips_debugfs_dir, शून्य,
			    &fpuemustats_clear_fops);

#घोषणा FPU_EMU_STAT_OFFSET(m)						\
	दुरत्व(काष्ठा mips_fpu_emulator_stats, m)

#घोषणा FPU_STAT_CREATE(m)						\
करो अणु									\
	debugfs_create_file(#m, 0444, fpuemu_debugfs_base_dir,		\
				(व्योम *)FPU_EMU_STAT_OFFSET(m),		\
				&fops_fpuemu_stat);			\
पूर्ण जबतक (0)

	FPU_STAT_CREATE(emulated);
	FPU_STAT_CREATE(loads);
	FPU_STAT_CREATE(stores);
	FPU_STAT_CREATE(branches);
	FPU_STAT_CREATE(cp1ops);
	FPU_STAT_CREATE(cp1xops);
	FPU_STAT_CREATE(errors);
	FPU_STAT_CREATE(ieee754_inexact);
	FPU_STAT_CREATE(ieee754_underflow);
	FPU_STAT_CREATE(ieee754_overflow);
	FPU_STAT_CREATE(ieee754_zeroभाग);
	FPU_STAT_CREATE(ieee754_invaliकरोp);
	FPU_STAT_CREATE(ds_emul);

	fpuemu_debugfs_inst_dir = debugfs_create_dir("instructions",
						     fpuemu_debugfs_base_dir);

#घोषणा FPU_STAT_CREATE_EX(m)						\
करो अणु									\
	adjust_inकाष्ठाion_counter_name(name, #m);			\
									\
	debugfs_create_file(name, 0444, fpuemu_debugfs_inst_dir,	\
				(व्योम *)FPU_EMU_STAT_OFFSET(m),		\
				&fops_fpuemu_stat);			\
पूर्ण जबतक (0)

	FPU_STAT_CREATE_EX(असल_s);
	FPU_STAT_CREATE_EX(असल_d);
	FPU_STAT_CREATE_EX(add_s);
	FPU_STAT_CREATE_EX(add_d);
	FPU_STAT_CREATE_EX(bc1eqz);
	FPU_STAT_CREATE_EX(bc1nez);
	FPU_STAT_CREATE_EX(उच्चमान_w_s);
	FPU_STAT_CREATE_EX(उच्चमान_w_d);
	FPU_STAT_CREATE_EX(उच्चमान_l_s);
	FPU_STAT_CREATE_EX(उच्चमान_l_d);
	FPU_STAT_CREATE_EX(class_s);
	FPU_STAT_CREATE_EX(class_d);
	FPU_STAT_CREATE_EX(cmp_af_s);
	FPU_STAT_CREATE_EX(cmp_af_d);
	FPU_STAT_CREATE_EX(cmp_eq_s);
	FPU_STAT_CREATE_EX(cmp_eq_d);
	FPU_STAT_CREATE_EX(cmp_le_s);
	FPU_STAT_CREATE_EX(cmp_le_d);
	FPU_STAT_CREATE_EX(cmp_lt_s);
	FPU_STAT_CREATE_EX(cmp_lt_d);
	FPU_STAT_CREATE_EX(cmp_ne_s);
	FPU_STAT_CREATE_EX(cmp_ne_d);
	FPU_STAT_CREATE_EX(cmp_or_s);
	FPU_STAT_CREATE_EX(cmp_or_d);
	FPU_STAT_CREATE_EX(cmp_ueq_s);
	FPU_STAT_CREATE_EX(cmp_ueq_d);
	FPU_STAT_CREATE_EX(cmp_ule_s);
	FPU_STAT_CREATE_EX(cmp_ule_d);
	FPU_STAT_CREATE_EX(cmp_ult_s);
	FPU_STAT_CREATE_EX(cmp_ult_d);
	FPU_STAT_CREATE_EX(cmp_un_s);
	FPU_STAT_CREATE_EX(cmp_un_d);
	FPU_STAT_CREATE_EX(cmp_une_s);
	FPU_STAT_CREATE_EX(cmp_une_d);
	FPU_STAT_CREATE_EX(cmp_saf_s);
	FPU_STAT_CREATE_EX(cmp_saf_d);
	FPU_STAT_CREATE_EX(cmp_seq_s);
	FPU_STAT_CREATE_EX(cmp_seq_d);
	FPU_STAT_CREATE_EX(cmp_sle_s);
	FPU_STAT_CREATE_EX(cmp_sle_d);
	FPU_STAT_CREATE_EX(cmp_slt_s);
	FPU_STAT_CREATE_EX(cmp_slt_d);
	FPU_STAT_CREATE_EX(cmp_sne_s);
	FPU_STAT_CREATE_EX(cmp_sne_d);
	FPU_STAT_CREATE_EX(cmp_sor_s);
	FPU_STAT_CREATE_EX(cmp_sor_d);
	FPU_STAT_CREATE_EX(cmp_sueq_s);
	FPU_STAT_CREATE_EX(cmp_sueq_d);
	FPU_STAT_CREATE_EX(cmp_sule_s);
	FPU_STAT_CREATE_EX(cmp_sule_d);
	FPU_STAT_CREATE_EX(cmp_sult_s);
	FPU_STAT_CREATE_EX(cmp_sult_d);
	FPU_STAT_CREATE_EX(cmp_sun_s);
	FPU_STAT_CREATE_EX(cmp_sun_d);
	FPU_STAT_CREATE_EX(cmp_sune_s);
	FPU_STAT_CREATE_EX(cmp_sune_d);
	FPU_STAT_CREATE_EX(cvt_d_l);
	FPU_STAT_CREATE_EX(cvt_d_s);
	FPU_STAT_CREATE_EX(cvt_d_w);
	FPU_STAT_CREATE_EX(cvt_l_s);
	FPU_STAT_CREATE_EX(cvt_l_d);
	FPU_STAT_CREATE_EX(cvt_s_d);
	FPU_STAT_CREATE_EX(cvt_s_l);
	FPU_STAT_CREATE_EX(cvt_s_w);
	FPU_STAT_CREATE_EX(cvt_w_s);
	FPU_STAT_CREATE_EX(cvt_w_d);
	FPU_STAT_CREATE_EX(भाग_s);
	FPU_STAT_CREATE_EX(भाग_d);
	FPU_STAT_CREATE_EX(न्यूनमान_w_s);
	FPU_STAT_CREATE_EX(न्यूनमान_w_d);
	FPU_STAT_CREATE_EX(न्यूनमान_l_s);
	FPU_STAT_CREATE_EX(न्यूनमान_l_d);
	FPU_STAT_CREATE_EX(maddf_s);
	FPU_STAT_CREATE_EX(maddf_d);
	FPU_STAT_CREATE_EX(max_s);
	FPU_STAT_CREATE_EX(max_d);
	FPU_STAT_CREATE_EX(maxa_s);
	FPU_STAT_CREATE_EX(maxa_d);
	FPU_STAT_CREATE_EX(min_s);
	FPU_STAT_CREATE_EX(min_d);
	FPU_STAT_CREATE_EX(mina_s);
	FPU_STAT_CREATE_EX(mina_d);
	FPU_STAT_CREATE_EX(mov_s);
	FPU_STAT_CREATE_EX(mov_d);
	FPU_STAT_CREATE_EX(msubf_s);
	FPU_STAT_CREATE_EX(msubf_d);
	FPU_STAT_CREATE_EX(mul_s);
	FPU_STAT_CREATE_EX(mul_d);
	FPU_STAT_CREATE_EX(neg_s);
	FPU_STAT_CREATE_EX(neg_d);
	FPU_STAT_CREATE_EX(recip_s);
	FPU_STAT_CREATE_EX(recip_d);
	FPU_STAT_CREATE_EX(rपूर्णांक_s);
	FPU_STAT_CREATE_EX(rपूर्णांक_d);
	FPU_STAT_CREATE_EX(round_w_s);
	FPU_STAT_CREATE_EX(round_w_d);
	FPU_STAT_CREATE_EX(round_l_s);
	FPU_STAT_CREATE_EX(round_l_d);
	FPU_STAT_CREATE_EX(rवर्ग_मूल_s);
	FPU_STAT_CREATE_EX(rवर्ग_मूल_d);
	FPU_STAT_CREATE_EX(sel_s);
	FPU_STAT_CREATE_EX(sel_d);
	FPU_STAT_CREATE_EX(seleqz_s);
	FPU_STAT_CREATE_EX(seleqz_d);
	FPU_STAT_CREATE_EX(selnez_s);
	FPU_STAT_CREATE_EX(selnez_d);
	FPU_STAT_CREATE_EX(वर्ग_मूल_s);
	FPU_STAT_CREATE_EX(वर्ग_मूल_d);
	FPU_STAT_CREATE_EX(sub_s);
	FPU_STAT_CREATE_EX(sub_d);
	FPU_STAT_CREATE_EX(trunc_w_s);
	FPU_STAT_CREATE_EX(trunc_w_d);
	FPU_STAT_CREATE_EX(trunc_l_s);
	FPU_STAT_CREATE_EX(trunc_l_d);

	वापस 0;
पूर्ण
arch_initcall(debugfs_fpuemu);
