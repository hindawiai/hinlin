<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
//
// Security related flags and so on.
//
// Copyright 2018, Michael Ellerman, IBM Corporation.

#समावेश <linux/cpu.h>
#समावेश <linux/kernel.h>
#समावेश <linux/device.h>
#समावेश <linux/memblock.h>
#समावेश <linux/nospec.h>
#समावेश <linux/prctl.h>
#समावेश <linux/seq_buf.h>

#समावेश <यंत्र/यंत्र-prototypes.h>
#समावेश <यंत्र/code-patching.h>
#समावेश <यंत्र/debugfs.h>
#समावेश <यंत्र/security_features.h>
#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/inst.h>

#समावेश "setup.h"

u64 घातerpc_security_features __पढ़ो_mostly = SEC_FTR_DEFAULT;

क्रमागत branch_cache_flush_type अणु
	BRANCH_CACHE_FLUSH_NONE	= 0x1,
	BRANCH_CACHE_FLUSH_SW	= 0x2,
	BRANCH_CACHE_FLUSH_HW	= 0x4,
पूर्ण;
अटल क्रमागत branch_cache_flush_type count_cache_flush_type = BRANCH_CACHE_FLUSH_NONE;
अटल क्रमागत branch_cache_flush_type link_stack_flush_type = BRANCH_CACHE_FLUSH_NONE;

bool barrier_nospec_enabled;
अटल bool no_nospec;
अटल bool btb_flush_enabled;
#अगर defined(CONFIG_PPC_FSL_BOOK3E) || defined(CONFIG_PPC_BOOK3S_64)
अटल bool no_spectrev2;
#पूर्ण_अगर

अटल व्योम enable_barrier_nospec(bool enable)
अणु
	barrier_nospec_enabled = enable;
	करो_barrier_nospec_fixups(enable);
पूर्ण

व्योम setup_barrier_nospec(व्योम)
अणु
	bool enable;

	/*
	 * It would make sense to check SEC_FTR_SPEC_BAR_ORI31 below as well.
	 * But there's a good reason not to. The two flags we check below are
	 * both are enabled by शेष in the kernel, so अगर the hcall is not
	 * functional they will be enabled.
	 * On a प्रणाली where the host firmware has been updated (so the ori
	 * functions as a barrier), but on which the hypervisor (KVM/Qemu) has
	 * not been updated, we would like to enable the barrier. Dropping the
	 * check क्रम SEC_FTR_SPEC_BAR_ORI31 achieves that. The only करोwnside is
	 * we potentially enable the barrier on प्रणालीs where the host firmware
	 * is not updated, but that's harmless as it's a no-op.
	 */
	enable = security_ftr_enabled(SEC_FTR_FAVOUR_SECURITY) &&
		 security_ftr_enabled(SEC_FTR_BNDS_CHK_SPEC_BAR);

	अगर (!no_nospec && !cpu_mitigations_off())
		enable_barrier_nospec(enable);
पूर्ण

अटल पूर्णांक __init handle_nospectre_v1(अक्षर *p)
अणु
	no_nospec = true;

	वापस 0;
पूर्ण
early_param("nospectre_v1", handle_nospectre_v1);

#अगर_घोषित CONFIG_DEBUG_FS
अटल पूर्णांक barrier_nospec_set(व्योम *data, u64 val)
अणु
	चयन (val) अणु
	हाल 0:
	हाल 1:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (!!val == !!barrier_nospec_enabled)
		वापस 0;

	enable_barrier_nospec(!!val);

	वापस 0;
पूर्ण

अटल पूर्णांक barrier_nospec_get(व्योम *data, u64 *val)
अणु
	*val = barrier_nospec_enabled ? 1 : 0;
	वापस 0;
पूर्ण

DEFINE_DEBUGFS_ATTRIBUTE(fops_barrier_nospec, barrier_nospec_get,
			 barrier_nospec_set, "%llu\n");

अटल __init पूर्णांक barrier_nospec_debugfs_init(व्योम)
अणु
	debugfs_create_file_unsafe("barrier_nospec", 0600,
				   घातerpc_debugfs_root, शून्य,
				   &fops_barrier_nospec);
	वापस 0;
पूर्ण
device_initcall(barrier_nospec_debugfs_init);

अटल __init पूर्णांक security_feature_debugfs_init(व्योम)
अणु
	debugfs_create_x64("security_features", 0400, घातerpc_debugfs_root,
			   &घातerpc_security_features);
	वापस 0;
पूर्ण
device_initcall(security_feature_debugfs_init);
#पूर्ण_अगर /* CONFIG_DEBUG_FS */

#अगर defined(CONFIG_PPC_FSL_BOOK3E) || defined(CONFIG_PPC_BOOK3S_64)
अटल पूर्णांक __init handle_nospectre_v2(अक्षर *p)
अणु
	no_spectrev2 = true;

	वापस 0;
पूर्ण
early_param("nospectre_v2", handle_nospectre_v2);
#पूर्ण_अगर /* CONFIG_PPC_FSL_BOOK3E || CONFIG_PPC_BOOK3S_64 */

#अगर_घोषित CONFIG_PPC_FSL_BOOK3E
व्योम setup_spectre_v2(व्योम)
अणु
	अगर (no_spectrev2 || cpu_mitigations_off())
		करो_btb_flush_fixups();
	अन्यथा
		btb_flush_enabled = true;
पूर्ण
#पूर्ण_अगर /* CONFIG_PPC_FSL_BOOK3E */

#अगर_घोषित CONFIG_PPC_BOOK3S_64
sमाप_प्रकार cpu_show_meltकरोwn(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	bool thपढ़ो_priv;

	thपढ़ो_priv = security_ftr_enabled(SEC_FTR_L1D_THREAD_PRIV);

	अगर (rfi_flush) अणु
		काष्ठा seq_buf s;
		seq_buf_init(&s, buf, PAGE_SIZE - 1);

		seq_buf_म_लिखो(&s, "Mitigation: RFI Flush");
		अगर (thपढ़ो_priv)
			seq_buf_म_लिखो(&s, ", L1D private per thread");

		seq_buf_म_लिखो(&s, "\n");

		वापस s.len;
	पूर्ण

	अगर (thपढ़ो_priv)
		वापस प्र_लिखो(buf, "Vulnerable: L1D private per thread\n");

	अगर (!security_ftr_enabled(SEC_FTR_L1D_FLUSH_HV) &&
	    !security_ftr_enabled(SEC_FTR_L1D_FLUSH_PR))
		वापस प्र_लिखो(buf, "Not affected\n");

	वापस प्र_लिखो(buf, "Vulnerable\n");
पूर्ण

sमाप_प्रकार cpu_show_l1tf(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस cpu_show_meltकरोwn(dev, attr, buf);
पूर्ण
#पूर्ण_अगर

sमाप_प्रकार cpu_show_spectre_v1(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा seq_buf s;

	seq_buf_init(&s, buf, PAGE_SIZE - 1);

	अगर (security_ftr_enabled(SEC_FTR_BNDS_CHK_SPEC_BAR)) अणु
		अगर (barrier_nospec_enabled)
			seq_buf_म_लिखो(&s, "Mitigation: __user pointer sanitization");
		अन्यथा
			seq_buf_म_लिखो(&s, "Vulnerable");

		अगर (security_ftr_enabled(SEC_FTR_SPEC_BAR_ORI31))
			seq_buf_म_लिखो(&s, ", ori31 speculation barrier enabled");

		seq_buf_म_लिखो(&s, "\n");
	पूर्ण अन्यथा
		seq_buf_म_लिखो(&s, "Not affected\n");

	वापस s.len;
पूर्ण

sमाप_प्रकार cpu_show_spectre_v2(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा seq_buf s;
	bool bcs, ccd;

	seq_buf_init(&s, buf, PAGE_SIZE - 1);

	bcs = security_ftr_enabled(SEC_FTR_BCCTRL_SERIALISED);
	ccd = security_ftr_enabled(SEC_FTR_COUNT_CACHE_DISABLED);

	अगर (bcs || ccd) अणु
		seq_buf_म_लिखो(&s, "Mitigation: ");

		अगर (bcs)
			seq_buf_म_लिखो(&s, "Indirect branch serialisation (kernel only)");

		अगर (bcs && ccd)
			seq_buf_म_लिखो(&s, ", ");

		अगर (ccd)
			seq_buf_म_लिखो(&s, "Indirect branch cache disabled");

	पूर्ण अन्यथा अगर (count_cache_flush_type != BRANCH_CACHE_FLUSH_NONE) अणु
		seq_buf_म_लिखो(&s, "Mitigation: Software count cache flush");

		अगर (count_cache_flush_type == BRANCH_CACHE_FLUSH_HW)
			seq_buf_म_लिखो(&s, " (hardware accelerated)");

	पूर्ण अन्यथा अगर (btb_flush_enabled) अणु
		seq_buf_म_लिखो(&s, "Mitigation: Branch predictor state flush");
	पूर्ण अन्यथा अणु
		seq_buf_म_लिखो(&s, "Vulnerable");
	पूर्ण

	अगर (bcs || ccd || count_cache_flush_type != BRANCH_CACHE_FLUSH_NONE) अणु
		अगर (link_stack_flush_type != BRANCH_CACHE_FLUSH_NONE)
			seq_buf_म_लिखो(&s, ", Software link stack flush");
		अगर (link_stack_flush_type == BRANCH_CACHE_FLUSH_HW)
			seq_buf_म_लिखो(&s, " (hardware accelerated)");
	पूर्ण

	seq_buf_म_लिखो(&s, "\n");

	वापस s.len;
पूर्ण

#अगर_घोषित CONFIG_PPC_BOOK3S_64
/*
 * Store-क्रमwarding barrier support.
 */

अटल क्रमागत stf_barrier_type stf_enabled_flush_types;
अटल bool no_stf_barrier;
अटल bool stf_barrier;

अटल पूर्णांक __init handle_no_stf_barrier(अक्षर *p)
अणु
	pr_info("stf-barrier: disabled on command line.");
	no_stf_barrier = true;
	वापस 0;
पूर्ण

early_param("no_stf_barrier", handle_no_stf_barrier);

/* This is the generic flag used by other architectures */
अटल पूर्णांक __init handle_ssbd(अक्षर *p)
अणु
	अगर (!p || म_भेदन(p, "auto", 5) == 0 || म_भेदन(p, "on", 2) == 0 ) अणु
		/* Until firmware tells us, we have the barrier with स्वतः */
		वापस 0;
	पूर्ण अन्यथा अगर (म_भेदन(p, "off", 3) == 0) अणु
		handle_no_stf_barrier(शून्य);
		वापस 0;
	पूर्ण अन्यथा
		वापस 1;

	वापस 0;
पूर्ण
early_param("spec_store_bypass_disable", handle_ssbd);

/* This is the generic flag used by other architectures */
अटल पूर्णांक __init handle_no_ssbd(अक्षर *p)
अणु
	handle_no_stf_barrier(शून्य);
	वापस 0;
पूर्ण
early_param("nospec_store_bypass_disable", handle_no_ssbd);

अटल व्योम stf_barrier_enable(bool enable)
अणु
	अगर (enable)
		करो_stf_barrier_fixups(stf_enabled_flush_types);
	अन्यथा
		करो_stf_barrier_fixups(STF_BARRIER_NONE);

	stf_barrier = enable;
पूर्ण

व्योम setup_stf_barrier(व्योम)
अणु
	क्रमागत stf_barrier_type type;
	bool enable, hv;

	hv = cpu_has_feature(CPU_FTR_HVMODE);

	/* Default to fallback in हाल fw-features are not available */
	अगर (cpu_has_feature(CPU_FTR_ARCH_300))
		type = STF_BARRIER_EIEIO;
	अन्यथा अगर (cpu_has_feature(CPU_FTR_ARCH_207S))
		type = STF_BARRIER_SYNC_ORI;
	अन्यथा अगर (cpu_has_feature(CPU_FTR_ARCH_206))
		type = STF_BARRIER_FALLBACK;
	अन्यथा
		type = STF_BARRIER_NONE;

	enable = security_ftr_enabled(SEC_FTR_FAVOUR_SECURITY) &&
		(security_ftr_enabled(SEC_FTR_L1D_FLUSH_PR) ||
		 (security_ftr_enabled(SEC_FTR_L1D_FLUSH_HV) && hv));

	अगर (type == STF_BARRIER_FALLBACK) अणु
		pr_info("stf-barrier: fallback barrier available\n");
	पूर्ण अन्यथा अगर (type == STF_BARRIER_SYNC_ORI) अणु
		pr_info("stf-barrier: hwsync barrier available\n");
	पूर्ण अन्यथा अगर (type == STF_BARRIER_EIEIO) अणु
		pr_info("stf-barrier: eieio barrier available\n");
	पूर्ण

	stf_enabled_flush_types = type;

	अगर (!no_stf_barrier && !cpu_mitigations_off())
		stf_barrier_enable(enable);
पूर्ण

sमाप_प्रकार cpu_show_spec_store_bypass(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	अगर (stf_barrier && stf_enabled_flush_types != STF_BARRIER_NONE) अणु
		स्थिर अक्षर *type;
		चयन (stf_enabled_flush_types) अणु
		हाल STF_BARRIER_EIEIO:
			type = "eieio";
			अवरोध;
		हाल STF_BARRIER_SYNC_ORI:
			type = "hwsync";
			अवरोध;
		हाल STF_BARRIER_FALLBACK:
			type = "fallback";
			अवरोध;
		शेष:
			type = "unknown";
		पूर्ण
		वापस प्र_लिखो(buf, "Mitigation: Kernel entry/exit barrier (%s)\n", type);
	पूर्ण

	अगर (!security_ftr_enabled(SEC_FTR_L1D_FLUSH_HV) &&
	    !security_ftr_enabled(SEC_FTR_L1D_FLUSH_PR))
		वापस प्र_लिखो(buf, "Not affected\n");

	वापस प्र_लिखो(buf, "Vulnerable\n");
पूर्ण

अटल पूर्णांक ssb_prctl_get(काष्ठा task_काष्ठा *task)
अणु
	अगर (stf_enabled_flush_types == STF_BARRIER_NONE)
		/*
		 * We करोn't have an explicit signal from firmware that we're
		 * vulnerable or not, we only have certain CPU revisions that
		 * are known to be vulnerable.
		 *
		 * We assume that अगर we're on another CPU, where the barrier is
		 * NONE, then we are not vulnerable.
		 */
		वापस PR_SPEC_NOT_AFFECTED;
	अन्यथा
		/*
		 * If we करो have a barrier type then we are vulnerable. The
		 * barrier is not a global or per-process mitigation, so the
		 * only value we can report here is PR_SPEC_ENABLE, which
		 * appears as "vulnerable" in /proc.
		 */
		वापस PR_SPEC_ENABLE;

	वापस -EINVAL;
पूर्ण

पूर्णांक arch_prctl_spec_ctrl_get(काष्ठा task_काष्ठा *task, अचिन्हित दीर्घ which)
अणु
	चयन (which) अणु
	हाल PR_SPEC_STORE_BYPASS:
		वापस ssb_prctl_get(task);
	शेष:
		वापस -ENODEV;
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_DEBUG_FS
अटल पूर्णांक stf_barrier_set(व्योम *data, u64 val)
अणु
	bool enable;

	अगर (val == 1)
		enable = true;
	अन्यथा अगर (val == 0)
		enable = false;
	अन्यथा
		वापस -EINVAL;

	/* Only करो anything अगर we're changing state */
	अगर (enable != stf_barrier)
		stf_barrier_enable(enable);

	वापस 0;
पूर्ण

अटल पूर्णांक stf_barrier_get(व्योम *data, u64 *val)
अणु
	*val = stf_barrier ? 1 : 0;
	वापस 0;
पूर्ण

DEFINE_DEBUGFS_ATTRIBUTE(fops_stf_barrier, stf_barrier_get, stf_barrier_set,
			 "%llu\n");

अटल __init पूर्णांक stf_barrier_debugfs_init(व्योम)
अणु
	debugfs_create_file_unsafe("stf_barrier", 0600, घातerpc_debugfs_root,
				   शून्य, &fops_stf_barrier);
	वापस 0;
पूर्ण
device_initcall(stf_barrier_debugfs_init);
#पूर्ण_अगर /* CONFIG_DEBUG_FS */

अटल व्योम update_branch_cache_flush(व्योम)
अणु
	u32 *site;

#अगर_घोषित CONFIG_KVM_BOOK3S_HV_POSSIBLE
	site = &patch__call_kvm_flush_link_stack;
	// This controls the branch from guest_निकास_cont to kvm_flush_link_stack
	अगर (link_stack_flush_type == BRANCH_CACHE_FLUSH_NONE) अणु
		patch_inकाष्ठाion_site(site, ppc_inst(PPC_INST_NOP));
	पूर्ण अन्यथा अणु
		// Could use HW flush, but that could also flush count cache
		patch_branch_site(site, (u64)&kvm_flush_link_stack, BRANCH_SET_LINK);
	पूर्ण
#पूर्ण_अगर

	// Patch out the bcctr first, then nop the rest
	site = &patch__call_flush_branch_caches3;
	patch_inकाष्ठाion_site(site, ppc_inst(PPC_INST_NOP));
	site = &patch__call_flush_branch_caches2;
	patch_inकाष्ठाion_site(site, ppc_inst(PPC_INST_NOP));
	site = &patch__call_flush_branch_caches1;
	patch_inकाष्ठाion_site(site, ppc_inst(PPC_INST_NOP));

	// This controls the branch from _चयन to flush_branch_caches
	अगर (count_cache_flush_type == BRANCH_CACHE_FLUSH_NONE &&
	    link_stack_flush_type == BRANCH_CACHE_FLUSH_NONE) अणु
		// Nothing to be करोne

	पूर्ण अन्यथा अगर (count_cache_flush_type == BRANCH_CACHE_FLUSH_HW &&
		   link_stack_flush_type == BRANCH_CACHE_FLUSH_HW) अणु
		// Patch in the bcctr last
		site = &patch__call_flush_branch_caches1;
		patch_inकाष्ठाion_site(site, ppc_inst(0x39207fff)); // li r9,0x7fff
		site = &patch__call_flush_branch_caches2;
		patch_inकाष्ठाion_site(site, ppc_inst(0x7d2903a6)); // mtctr r9
		site = &patch__call_flush_branch_caches3;
		patch_inकाष्ठाion_site(site, ppc_inst(PPC_INST_BCCTR_FLUSH));

	पूर्ण अन्यथा अणु
		patch_branch_site(site, (u64)&flush_branch_caches, BRANCH_SET_LINK);

		// If we just need to flush the link stack, early वापस
		अगर (count_cache_flush_type == BRANCH_CACHE_FLUSH_NONE) अणु
			patch_inकाष्ठाion_site(&patch__flush_link_stack_वापस,
					       ppc_inst(PPC_INST_BLR));

		// If we have flush inकाष्ठाion, early वापस
		पूर्ण अन्यथा अगर (count_cache_flush_type == BRANCH_CACHE_FLUSH_HW) अणु
			patch_inकाष्ठाion_site(&patch__flush_count_cache_वापस,
					       ppc_inst(PPC_INST_BLR));
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम toggle_branch_cache_flush(bool enable)
अणु
	अगर (!enable || !security_ftr_enabled(SEC_FTR_FLUSH_COUNT_CACHE)) अणु
		अगर (count_cache_flush_type != BRANCH_CACHE_FLUSH_NONE)
			count_cache_flush_type = BRANCH_CACHE_FLUSH_NONE;

		pr_info("count-cache-flush: flush disabled.\n");
	पूर्ण अन्यथा अणु
		अगर (security_ftr_enabled(SEC_FTR_BCCTR_FLUSH_ASSIST)) अणु
			count_cache_flush_type = BRANCH_CACHE_FLUSH_HW;
			pr_info("count-cache-flush: hardware flush enabled.\n");
		पूर्ण अन्यथा अणु
			count_cache_flush_type = BRANCH_CACHE_FLUSH_SW;
			pr_info("count-cache-flush: software flush enabled.\n");
		पूर्ण
	पूर्ण

	अगर (!enable || !security_ftr_enabled(SEC_FTR_FLUSH_LINK_STACK)) अणु
		अगर (link_stack_flush_type != BRANCH_CACHE_FLUSH_NONE)
			link_stack_flush_type = BRANCH_CACHE_FLUSH_NONE;

		pr_info("link-stack-flush: flush disabled.\n");
	पूर्ण अन्यथा अणु
		अगर (security_ftr_enabled(SEC_FTR_BCCTR_LINK_FLUSH_ASSIST)) अणु
			link_stack_flush_type = BRANCH_CACHE_FLUSH_HW;
			pr_info("link-stack-flush: hardware flush enabled.\n");
		पूर्ण अन्यथा अणु
			link_stack_flush_type = BRANCH_CACHE_FLUSH_SW;
			pr_info("link-stack-flush: software flush enabled.\n");
		पूर्ण
	पूर्ण

	update_branch_cache_flush();
पूर्ण

व्योम setup_count_cache_flush(व्योम)
अणु
	bool enable = true;

	अगर (no_spectrev2 || cpu_mitigations_off()) अणु
		अगर (security_ftr_enabled(SEC_FTR_BCCTRL_SERIALISED) ||
		    security_ftr_enabled(SEC_FTR_COUNT_CACHE_DISABLED))
			pr_warn("Spectre v2 mitigations not fully under software control, can't disable\n");

		enable = false;
	पूर्ण

	/*
	 * There's no firmware feature flag/hypervisor bit to tell us we need to
	 * flush the link stack on context चयन. So we set it here अगर we see
	 * either of the Spectre v2 mitigations that aim to protect userspace.
	 */
	अगर (security_ftr_enabled(SEC_FTR_COUNT_CACHE_DISABLED) ||
	    security_ftr_enabled(SEC_FTR_FLUSH_COUNT_CACHE))
		security_ftr_set(SEC_FTR_FLUSH_LINK_STACK);

	toggle_branch_cache_flush(enable);
पूर्ण

अटल क्रमागत l1d_flush_type enabled_flush_types;
अटल व्योम *l1d_flush_fallback_area;
अटल bool no_rfi_flush;
अटल bool no_entry_flush;
अटल bool no_uaccess_flush;
bool rfi_flush;
अटल bool entry_flush;
अटल bool uaccess_flush;
DEFINE_STATIC_KEY_FALSE(uaccess_flush_key);
EXPORT_SYMBOL(uaccess_flush_key);

अटल पूर्णांक __init handle_no_rfi_flush(अक्षर *p)
अणु
	pr_info("rfi-flush: disabled on command line.");
	no_rfi_flush = true;
	वापस 0;
पूर्ण
early_param("no_rfi_flush", handle_no_rfi_flush);

अटल पूर्णांक __init handle_no_entry_flush(अक्षर *p)
अणु
	pr_info("entry-flush: disabled on command line.");
	no_entry_flush = true;
	वापस 0;
पूर्ण
early_param("no_entry_flush", handle_no_entry_flush);

अटल पूर्णांक __init handle_no_uaccess_flush(अक्षर *p)
अणु
	pr_info("uaccess-flush: disabled on command line.");
	no_uaccess_flush = true;
	वापस 0;
पूर्ण
early_param("no_uaccess_flush", handle_no_uaccess_flush);

/*
 * The RFI flush is not KPTI, but because users will see करोco that says to use
 * nopti we hijack that option here to also disable the RFI flush.
 */
अटल पूर्णांक __init handle_no_pti(अक्षर *p)
अणु
	pr_info("rfi-flush: disabling due to 'nopti' on command line.\n");
	handle_no_rfi_flush(शून्य);
	वापस 0;
पूर्ण
early_param("nopti", handle_no_pti);

अटल व्योम करो_nothing(व्योम *unused)
अणु
	/*
	 * We करोn't need to करो the flush explicitly, just enter+निकास kernel is
	 * sufficient, the RFI निकास handlers will करो the right thing.
	 */
पूर्ण

व्योम rfi_flush_enable(bool enable)
अणु
	अगर (enable) अणु
		करो_rfi_flush_fixups(enabled_flush_types);
		on_each_cpu(करो_nothing, शून्य, 1);
	पूर्ण अन्यथा
		करो_rfi_flush_fixups(L1D_FLUSH_NONE);

	rfi_flush = enable;
पूर्ण

अटल व्योम entry_flush_enable(bool enable)
अणु
	अगर (enable) अणु
		करो_entry_flush_fixups(enabled_flush_types);
		on_each_cpu(करो_nothing, शून्य, 1);
	पूर्ण अन्यथा अणु
		करो_entry_flush_fixups(L1D_FLUSH_NONE);
	पूर्ण

	entry_flush = enable;
पूर्ण

अटल व्योम uaccess_flush_enable(bool enable)
अणु
	अगर (enable) अणु
		करो_uaccess_flush_fixups(enabled_flush_types);
		अटल_branch_enable(&uaccess_flush_key);
		on_each_cpu(करो_nothing, शून्य, 1);
	पूर्ण अन्यथा अणु
		अटल_branch_disable(&uaccess_flush_key);
		करो_uaccess_flush_fixups(L1D_FLUSH_NONE);
	पूर्ण

	uaccess_flush = enable;
पूर्ण

अटल व्योम __ref init_fallback_flush(व्योम)
अणु
	u64 l1d_size, limit;
	पूर्णांक cpu;

	/* Only allocate the fallback flush area once (at boot समय). */
	अगर (l1d_flush_fallback_area)
		वापस;

	l1d_size = ppc64_caches.l1d.size;

	/*
	 * If there is no d-cache-size property in the device tree, l1d_size
	 * could be zero. That leads to the loop in the यंत्र wrapping around to
	 * 2^64-1, and then walking off the end of the fallback area and
	 * eventually causing a page fault which is fatal. Just शेष to
	 * something vaguely sane.
	 */
	अगर (!l1d_size)
		l1d_size = (64 * 1024);

	limit = min(ppc64_bolted_size(), ppc64_rma_size);

	/*
	 * Align to L1d size, and size it at 2x L1d size, to catch possible
	 * hardware prefetch runoff. We करोn't have a recipe क्रम load patterns to
	 * reliably aव्योम the prefetcher.
	 */
	l1d_flush_fallback_area = memblock_alloc_try_nid(l1d_size * 2,
						l1d_size, MEMBLOCK_LOW_LIMIT,
						limit, NUMA_NO_NODE);
	अगर (!l1d_flush_fallback_area)
		panic("%s: Failed to allocate %llu bytes align=0x%llx max_addr=%pa\n",
		      __func__, l1d_size * 2, l1d_size, &limit);


	क्रम_each_possible_cpu(cpu) अणु
		काष्ठा paca_काष्ठा *paca = paca_ptrs[cpu];
		paca->rfi_flush_fallback_area = l1d_flush_fallback_area;
		paca->l1d_flush_size = l1d_size;
	पूर्ण
पूर्ण

व्योम setup_rfi_flush(क्रमागत l1d_flush_type types, bool enable)
अणु
	अगर (types & L1D_FLUSH_FALLBACK) अणु
		pr_info("rfi-flush: fallback displacement flush available\n");
		init_fallback_flush();
	पूर्ण

	अगर (types & L1D_FLUSH_ORI)
		pr_info("rfi-flush: ori type flush available\n");

	अगर (types & L1D_FLUSH_MTTRIG)
		pr_info("rfi-flush: mttrig type flush available\n");

	enabled_flush_types = types;

	अगर (!cpu_mitigations_off() && !no_rfi_flush)
		rfi_flush_enable(enable);
पूर्ण

व्योम setup_entry_flush(bool enable)
अणु
	अगर (cpu_mitigations_off())
		वापस;

	अगर (!no_entry_flush)
		entry_flush_enable(enable);
पूर्ण

व्योम setup_uaccess_flush(bool enable)
अणु
	अगर (cpu_mitigations_off())
		वापस;

	अगर (!no_uaccess_flush)
		uaccess_flush_enable(enable);
पूर्ण

#अगर_घोषित CONFIG_DEBUG_FS
अटल पूर्णांक count_cache_flush_set(व्योम *data, u64 val)
अणु
	bool enable;

	अगर (val == 1)
		enable = true;
	अन्यथा अगर (val == 0)
		enable = false;
	अन्यथा
		वापस -EINVAL;

	toggle_branch_cache_flush(enable);

	वापस 0;
पूर्ण

अटल पूर्णांक count_cache_flush_get(व्योम *data, u64 *val)
अणु
	अगर (count_cache_flush_type == BRANCH_CACHE_FLUSH_NONE)
		*val = 0;
	अन्यथा
		*val = 1;

	वापस 0;
पूर्ण

DEFINE_DEBUGFS_ATTRIBUTE(fops_count_cache_flush, count_cache_flush_get,
			 count_cache_flush_set, "%llu\n");

अटल __init पूर्णांक count_cache_flush_debugfs_init(व्योम)
अणु
	debugfs_create_file_unsafe("count_cache_flush", 0600,
				   घातerpc_debugfs_root, शून्य,
				   &fops_count_cache_flush);
	वापस 0;
पूर्ण
device_initcall(count_cache_flush_debugfs_init);

अटल पूर्णांक rfi_flush_set(व्योम *data, u64 val)
अणु
	bool enable;

	अगर (val == 1)
		enable = true;
	अन्यथा अगर (val == 0)
		enable = false;
	अन्यथा
		वापस -EINVAL;

	/* Only करो anything अगर we're changing state */
	अगर (enable != rfi_flush)
		rfi_flush_enable(enable);

	वापस 0;
पूर्ण

अटल पूर्णांक rfi_flush_get(व्योम *data, u64 *val)
अणु
	*val = rfi_flush ? 1 : 0;
	वापस 0;
पूर्ण

DEFINE_SIMPLE_ATTRIBUTE(fops_rfi_flush, rfi_flush_get, rfi_flush_set, "%llu\n");

अटल पूर्णांक entry_flush_set(व्योम *data, u64 val)
अणु
	bool enable;

	अगर (val == 1)
		enable = true;
	अन्यथा अगर (val == 0)
		enable = false;
	अन्यथा
		वापस -EINVAL;

	/* Only करो anything अगर we're changing state */
	अगर (enable != entry_flush)
		entry_flush_enable(enable);

	वापस 0;
पूर्ण

अटल पूर्णांक entry_flush_get(व्योम *data, u64 *val)
अणु
	*val = entry_flush ? 1 : 0;
	वापस 0;
पूर्ण

DEFINE_SIMPLE_ATTRIBUTE(fops_entry_flush, entry_flush_get, entry_flush_set, "%llu\n");

अटल पूर्णांक uaccess_flush_set(व्योम *data, u64 val)
अणु
	bool enable;

	अगर (val == 1)
		enable = true;
	अन्यथा अगर (val == 0)
		enable = false;
	अन्यथा
		वापस -EINVAL;

	/* Only करो anything अगर we're changing state */
	अगर (enable != uaccess_flush)
		uaccess_flush_enable(enable);

	वापस 0;
पूर्ण

अटल पूर्णांक uaccess_flush_get(व्योम *data, u64 *val)
अणु
	*val = uaccess_flush ? 1 : 0;
	वापस 0;
पूर्ण

DEFINE_SIMPLE_ATTRIBUTE(fops_uaccess_flush, uaccess_flush_get, uaccess_flush_set, "%llu\n");

अटल __init पूर्णांक rfi_flush_debugfs_init(व्योम)
अणु
	debugfs_create_file("rfi_flush", 0600, घातerpc_debugfs_root, शून्य, &fops_rfi_flush);
	debugfs_create_file("entry_flush", 0600, घातerpc_debugfs_root, शून्य, &fops_entry_flush);
	debugfs_create_file("uaccess_flush", 0600, घातerpc_debugfs_root, शून्य, &fops_uaccess_flush);
	वापस 0;
पूर्ण
device_initcall(rfi_flush_debugfs_init);
#पूर्ण_अगर /* CONFIG_DEBUG_FS */
#पूर्ण_अगर /* CONFIG_PPC_BOOK3S_64 */
