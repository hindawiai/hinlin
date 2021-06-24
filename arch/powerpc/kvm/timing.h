<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *
 * Copyright IBM Corp. 2008
 *
 * Authors: Christian Ehrhardt <ehrhardt@linux.vnet.ibm.com>
 */

#अगर_अघोषित __POWERPC_KVM_EXITTIMING_H__
#घोषणा __POWERPC_KVM_EXITTIMING_H__

#समावेश <linux/kvm_host.h>

#अगर_घोषित CONFIG_KVM_EXIT_TIMING
व्योम kvmppc_init_timing_stats(काष्ठा kvm_vcpu *vcpu);
व्योम kvmppc_update_timing_stats(काष्ठा kvm_vcpu *vcpu);
व्योम kvmppc_create_vcpu_debugfs(काष्ठा kvm_vcpu *vcpu, अचिन्हित पूर्णांक id);
व्योम kvmppc_हटाओ_vcpu_debugfs(काष्ठा kvm_vcpu *vcpu);

अटल अंतरभूत व्योम kvmppc_set_निकास_type(काष्ठा kvm_vcpu *vcpu, पूर्णांक type)
अणु
	vcpu->arch.last_निकास_type = type;
पूर्ण

#अन्यथा
/* अगर निकास timing is not configured there is no need to build the c file */
अटल अंतरभूत व्योम kvmppc_init_timing_stats(काष्ठा kvm_vcpu *vcpu) अणुपूर्ण
अटल अंतरभूत व्योम kvmppc_update_timing_stats(काष्ठा kvm_vcpu *vcpu) अणुपूर्ण
अटल अंतरभूत व्योम kvmppc_create_vcpu_debugfs(काष्ठा kvm_vcpu *vcpu,
						अचिन्हित पूर्णांक id) अणुपूर्ण
अटल अंतरभूत व्योम kvmppc_हटाओ_vcpu_debugfs(काष्ठा kvm_vcpu *vcpu) अणुपूर्ण
अटल अंतरभूत व्योम kvmppc_set_निकास_type(काष्ठा kvm_vcpu *vcpu, पूर्णांक type) अणुपूर्ण
#पूर्ण_अगर /* CONFIG_KVM_EXIT_TIMING */

/* account the निकास in kvm_stats */
अटल अंतरभूत व्योम kvmppc_account_निकास_stat(काष्ठा kvm_vcpu *vcpu, पूर्णांक type)
अणु
	/* type has to be known at build समय क्रम optimization */

	/* The BUILD_BUG_ON below अवरोधs in funny ways, commented out
	 * क्रम now ... -BenH
	BUILD_BUG_ON(!__builtin_स्थिरant_p(type));
	*/
	चयन (type) अणु
	हाल EXT_INTR_EXITS:
		vcpu->stat.ext_पूर्णांकr_निकासs++;
		अवरोध;
	हाल DEC_EXITS:
		vcpu->stat.dec_निकासs++;
		अवरोध;
	हाल EMULATED_INST_EXITS:
		vcpu->stat.emulated_inst_निकासs++;
		अवरोध;
	हाल DSI_EXITS:
		vcpu->stat.dsi_निकासs++;
		अवरोध;
	हाल ISI_EXITS:
		vcpu->stat.isi_निकासs++;
		अवरोध;
	हाल SYSCALL_EXITS:
		vcpu->stat.syscall_निकासs++;
		अवरोध;
	हाल DTLB_REAL_MISS_EXITS:
		vcpu->stat.dtlb_real_miss_निकासs++;
		अवरोध;
	हाल DTLB_VIRT_MISS_EXITS:
		vcpu->stat.dtlb_virt_miss_निकासs++;
		अवरोध;
	हाल MMIO_EXITS:
		vcpu->stat.mmio_निकासs++;
		अवरोध;
	हाल ITLB_REAL_MISS_EXITS:
		vcpu->stat.itlb_real_miss_निकासs++;
		अवरोध;
	हाल ITLB_VIRT_MISS_EXITS:
		vcpu->stat.itlb_virt_miss_निकासs++;
		अवरोध;
	हाल SIGNAL_EXITS:
		vcpu->stat.संकेत_निकासs++;
		अवरोध;
	हाल DBELL_EXITS:
		vcpu->stat.dbell_निकासs++;
		अवरोध;
	हाल GDBELL_EXITS:
		vcpu->stat.gdbell_निकासs++;
		अवरोध;
	पूर्ण
पूर्ण

/* wrapper to set निकास समय and account क्रम it in kvm_stats */
अटल अंतरभूत व्योम kvmppc_account_निकास(काष्ठा kvm_vcpu *vcpu, पूर्णांक type)
अणु
	kvmppc_set_निकास_type(vcpu, type);
	kvmppc_account_निकास_stat(vcpu, type);
पूर्ण

#पूर्ण_अगर /* __POWERPC_KVM_EXITTIMING_H__ */
