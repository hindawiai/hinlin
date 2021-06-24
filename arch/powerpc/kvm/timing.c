<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *
 * Copyright IBM Corp. 2008
 *
 * Authors: Hollis Blanअक्षरd <hollisb@us.ibm.com>
 *          Christian Ehrhardt <ehrhardt@linux.vnet.ibm.com>
 */

#समावेश <linux/kvm_host.h>
#समावेश <linux/fs.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/module.h>

#समावेश <यंत्र/समय.स>
#समावेश <यंत्र-generic/भाग64.h>

#समावेश "timing.h"

व्योम kvmppc_init_timing_stats(काष्ठा kvm_vcpu *vcpu)
अणु
	पूर्णांक i;

	/* Take a lock to aव्योम concurrent updates */
	mutex_lock(&vcpu->arch.निकास_timing_lock);

	vcpu->arch.last_निकास_type = 0xDEAD;
	क्रम (i = 0; i < __NUMBER_OF_KVM_EXIT_TYPES; i++) अणु
		vcpu->arch.timing_count_type[i] = 0;
		vcpu->arch.timing_max_duration[i] = 0;
		vcpu->arch.timing_min_duration[i] = 0xFFFFFFFF;
		vcpu->arch.timing_sum_duration[i] = 0;
		vcpu->arch.timing_sum_quad_duration[i] = 0;
	पूर्ण
	vcpu->arch.timing_last_निकास = 0;
	vcpu->arch.timing_निकास.tv64 = 0;
	vcpu->arch.timing_last_enter.tv64 = 0;

	mutex_unlock(&vcpu->arch.निकास_timing_lock);
पूर्ण

अटल व्योम add_निकास_timing(काष्ठा kvm_vcpu *vcpu, u64 duration, पूर्णांक type)
अणु
	u64 old;

	mutex_lock(&vcpu->arch.निकास_timing_lock);

	vcpu->arch.timing_count_type[type]++;

	/* sum */
	old = vcpu->arch.timing_sum_duration[type];
	vcpu->arch.timing_sum_duration[type] += duration;
	अगर (unlikely(old > vcpu->arch.timing_sum_duration[type])) अणु
		prपूर्णांकk(KERN_ERR"%s - wrap adding sum of durations"
			" old %lld new %lld type %d exit # of type %d\n",
			__func__, old, vcpu->arch.timing_sum_duration[type],
			type, vcpu->arch.timing_count_type[type]);
	पूर्ण

	/* square sum */
	old = vcpu->arch.timing_sum_quad_duration[type];
	vcpu->arch.timing_sum_quad_duration[type] += (duration*duration);
	अगर (unlikely(old > vcpu->arch.timing_sum_quad_duration[type])) अणु
		prपूर्णांकk(KERN_ERR"%s - wrap adding sum of squared durations"
			" old %lld new %lld type %d exit # of type %d\n",
			__func__, old,
			vcpu->arch.timing_sum_quad_duration[type],
			type, vcpu->arch.timing_count_type[type]);
	पूर्ण

	/* set min/max */
	अगर (unlikely(duration < vcpu->arch.timing_min_duration[type]))
		vcpu->arch.timing_min_duration[type] = duration;
	अगर (unlikely(duration > vcpu->arch.timing_max_duration[type]))
		vcpu->arch.timing_max_duration[type] = duration;

	mutex_unlock(&vcpu->arch.निकास_timing_lock);
पूर्ण

व्योम kvmppc_update_timing_stats(काष्ठा kvm_vcpu *vcpu)
अणु
	u64 निकास = vcpu->arch.timing_last_निकास;
	u64 enter = vcpu->arch.timing_last_enter.tv64;

	/* save निकास समय, used next निकास when the reenter समय is known */
	vcpu->arch.timing_last_निकास = vcpu->arch.timing_निकास.tv64;

	अगर (unlikely(vcpu->arch.last_निकास_type == 0xDEAD || निकास == 0))
		वापस; /* skip incomplete cycle (e.g. after reset) */

	/* update statistics क्रम average and standard deviation */
	add_निकास_timing(vcpu, (enter - निकास), vcpu->arch.last_निकास_type);
	/* enter -> timing_last_निकास is समय spent in guest - log this too */
	add_निकास_timing(vcpu, (vcpu->arch.timing_last_निकास - enter),
			TIMEINGUEST);
पूर्ण

अटल स्थिर अक्षर *kvm_निकास_names[__NUMBER_OF_KVM_EXIT_TYPES] = अणु
	[MMIO_EXITS] =              "MMIO",
	[SIGNAL_EXITS] =            "SIGNAL",
	[ITLB_REAL_MISS_EXITS] =    "ITLBREAL",
	[ITLB_VIRT_MISS_EXITS] =    "ITLBVIRT",
	[DTLB_REAL_MISS_EXITS] =    "DTLBREAL",
	[DTLB_VIRT_MISS_EXITS] =    "DTLBVIRT",
	[SYSCALL_EXITS] =           "SYSCALL",
	[ISI_EXITS] =               "ISI",
	[DSI_EXITS] =               "DSI",
	[EMULATED_INST_EXITS] =     "EMULINST",
	[EMULATED_MTMSRWE_EXITS] =  "EMUL_WAIT",
	[EMULATED_WRTEE_EXITS] =    "EMUL_WRTEE",
	[EMULATED_MTSPR_EXITS] =    "EMUL_MTSPR",
	[EMULATED_MFSPR_EXITS] =    "EMUL_MFSPR",
	[EMULATED_MTMSR_EXITS] =    "EMUL_MTMSR",
	[EMULATED_MFMSR_EXITS] =    "EMUL_MFMSR",
	[EMULATED_TLBSX_EXITS] =    "EMUL_TLBSX",
	[EMULATED_TLBWE_EXITS] =    "EMUL_TLBWE",
	[EMULATED_RFI_EXITS] =      "EMUL_RFI",
	[DEC_EXITS] =               "DEC",
	[EXT_INTR_EXITS] =          "EXTINT",
	[HALT_WAKEUP] =             "HALT",
	[USR_PR_INST] =             "USR_PR_INST",
	[FP_UNAVAIL] =              "FP_UNAVAIL",
	[DEBUG_EXITS] =             "DEBUG",
	[TIMEINGUEST] =             "TIMEINGUEST"
पूर्ण;

अटल पूर्णांक kvmppc_निकास_timing_show(काष्ठा seq_file *m, व्योम *निजी)
अणु
	काष्ठा kvm_vcpu *vcpu = m->निजी;
	पूर्णांक i;
	u64 min, max, sum, sum_quad;

	seq_माला_दो(m, "type	count	min	max	sum	sum_squared\n");

	क्रम (i = 0; i < __NUMBER_OF_KVM_EXIT_TYPES; i++) अणु

		min = vcpu->arch.timing_min_duration[i];
		करो_भाग(min, tb_ticks_per_usec);
		max = vcpu->arch.timing_max_duration[i];
		करो_भाग(max, tb_ticks_per_usec);
		sum = vcpu->arch.timing_sum_duration[i];
		करो_भाग(sum, tb_ticks_per_usec);
		sum_quad = vcpu->arch.timing_sum_quad_duration[i];
		करो_भाग(sum_quad, tb_ticks_per_usec);

		seq_म_लिखो(m, "%12s	%10d	%10lld	%10lld	%20lld	%20lld\n",
			kvm_निकास_names[i],
			vcpu->arch.timing_count_type[i],
			min,
			max,
			sum,
			sum_quad);

	पूर्ण
	वापस 0;
पूर्ण

/* Write 'c' to clear the timing statistics. */
अटल sमाप_प्रकार kvmppc_निकास_timing_ग_लिखो(काष्ठा file *file,
				       स्थिर अक्षर __user *user_buf,
				       माप_प्रकार count, loff_t *ppos)
अणु
	पूर्णांक err = -EINVAL;
	अक्षर c;

	अगर (count > 1) अणु
		जाओ करोne;
	पूर्ण

	अगर (get_user(c, user_buf)) अणु
		err = -EFAULT;
		जाओ करोne;
	पूर्ण

	अगर (c == 'c') अणु
		काष्ठा seq_file *seqf = file->निजी_data;
		काष्ठा kvm_vcpu *vcpu = seqf->निजी;
		/* Write करोes not affect our buffers previously generated with
		 * show. seq_file is locked here to prevent races of init with
		 * a show call */
		mutex_lock(&seqf->lock);
		kvmppc_init_timing_stats(vcpu);
		mutex_unlock(&seqf->lock);
		err = count;
	पूर्ण

करोne:
	वापस err;
पूर्ण

अटल पूर्णांक kvmppc_निकास_timing_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस single_खोलो(file, kvmppc_निकास_timing_show, inode->i_निजी);
पूर्ण

अटल स्थिर काष्ठा file_operations kvmppc_निकास_timing_fops = अणु
	.owner   = THIS_MODULE,
	.खोलो    = kvmppc_निकास_timing_खोलो,
	.पढ़ो    = seq_पढ़ो,
	.ग_लिखो   = kvmppc_निकास_timing_ग_लिखो,
	.llseek  = seq_lseek,
	.release = single_release,
पूर्ण;

व्योम kvmppc_create_vcpu_debugfs(काष्ठा kvm_vcpu *vcpu, अचिन्हित पूर्णांक id)
अणु
	अटल अक्षर dbg_fname[50];
	काष्ठा dentry *debugfs_file;

	snम_लिखो(dbg_fname, माप(dbg_fname), "vm%u_vcpu%u_timing",
		 current->pid, id);
	debugfs_file = debugfs_create_file(dbg_fname, 0666, kvm_debugfs_dir,
						vcpu, &kvmppc_निकास_timing_fops);

	vcpu->arch.debugfs_निकास_timing = debugfs_file;
पूर्ण

व्योम kvmppc_हटाओ_vcpu_debugfs(काष्ठा kvm_vcpu *vcpu)
अणु
	debugfs_हटाओ(vcpu->arch.debugfs_निकास_timing);
	vcpu->arch.debugfs_निकास_timing = शून्य;
पूर्ण
