<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

/*
 * Linux-specअगरic definitions क्रम managing पूर्णांकeractions with Microsoft's
 * Hyper-V hypervisor. The definitions in this file are architecture
 * independent. See arch/<arch>/include/यंत्र/mshyperv.h क्रम definitions
 * that are specअगरic to architecture <arch>.
 *
 * Definitions that are specअगरied in the Hyper-V Top Level Functional
 * Spec (TLFS) should not go in this file, but should instead go in
 * hyperv-tlfs.h.
 *
 * Copyright (C) 2019, Microsoft, Inc.
 *
 * Author : Michael Kelley <mikelley@microsoft.com>
 */

#अगर_अघोषित _ASM_GENERIC_MSHYPERV_H
#घोषणा _ASM_GENERIC_MSHYPERV_H

#समावेश <linux/types.h>
#समावेश <linux/atomic.h>
#समावेश <linux/bitops.h>
#समावेश <linux/cpumask.h>
#समावेश <यंत्र/ptrace.h>
#समावेश <यंत्र/hyperv-tlfs.h>

काष्ठा ms_hyperv_info अणु
	u32 features;
	u32 priv_high;
	u32 misc_features;
	u32 hपूर्णांकs;
	u32 nested_features;
	u32 max_vp_index;
	u32 max_lp_index;
	u32 isolation_config_a;
	u32 isolation_config_b;
पूर्ण;
बाह्य काष्ठा ms_hyperv_info ms_hyperv;

बाह्य u64 hv_करो_hypercall(u64 control, व्योम *inputaddr, व्योम *outputaddr);
बाह्य u64 hv_करो_fast_hypercall8(u16 control, u64 input8);

/* Helper functions that provide a consistent pattern क्रम checking Hyper-V hypercall status. */
अटल अंतरभूत पूर्णांक hv_result(u64 status)
अणु
	वापस status & HV_HYPERCALL_RESULT_MASK;
पूर्ण

अटल अंतरभूत bool hv_result_success(u64 status)
अणु
	वापस hv_result(status) == HV_STATUS_SUCCESS;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक hv_repcomp(u64 status)
अणु
	/* Bits [43:32] of status have 'Reps completed' data. */
	वापस (status & HV_HYPERCALL_REP_COMP_MASK) >>
			 HV_HYPERCALL_REP_COMP_OFFSET;
पूर्ण

/*
 * Rep hypercalls. Callers of this functions are supposed to ensure that
 * rep_count and varhead_size comply with Hyper-V hypercall definition.
 */
अटल अंतरभूत u64 hv_करो_rep_hypercall(u16 code, u16 rep_count, u16 varhead_size,
				      व्योम *input, व्योम *output)
अणु
	u64 control = code;
	u64 status;
	u16 rep_comp;

	control |= (u64)varhead_size << HV_HYPERCALL_VARHEAD_OFFSET;
	control |= (u64)rep_count << HV_HYPERCALL_REP_COMP_OFFSET;

	करो अणु
		status = hv_करो_hypercall(control, input, output);
		अगर (!hv_result_success(status))
			वापस status;

		rep_comp = hv_repcomp(status);

		control &= ~HV_HYPERCALL_REP_START_MASK;
		control |= (u64)rep_comp << HV_HYPERCALL_REP_START_OFFSET;

		touch_nmi_watchकरोg();
	पूर्ण जबतक (rep_comp < rep_count);

	वापस status;
पूर्ण

/* Generate the guest OS identअगरier as described in the Hyper-V TLFS */
अटल अंतरभूत  __u64 generate_guest_id(__u64 d_info1, __u64 kernel_version,
				       __u64 d_info2)
अणु
	__u64 guest_id = 0;

	guest_id = (((__u64)HV_LINUX_VENDOR_ID) << 48);
	guest_id |= (d_info1 << 48);
	guest_id |= (kernel_version << 16);
	guest_id |= d_info2;

	वापस guest_id;
पूर्ण

/* Free the message slot and संकेत end-of-message अगर required */
अटल अंतरभूत व्योम vmbus_संकेत_eom(काष्ठा hv_message *msg, u32 old_msg_type)
अणु
	/*
	 * On crash we're reading some other CPU's message page and we need
	 * to be careful: this other CPU may alपढ़ोy had cleared the header
	 * and the host may alपढ़ोy had delivered some other message there.
	 * In हाल we blindly ग_लिखो msg->header.message_type we're going
	 * to lose it. We can still lose a message of the same type but
	 * we count on the fact that there can only be one
	 * CHANNELMSG_UNLOAD_RESPONSE and we करोn't care about other messages
	 * on crash.
	 */
	अगर (cmpxchg(&msg->header.message_type, old_msg_type,
		    HVMSG_NONE) != old_msg_type)
		वापस;

	/*
	 * The cmxchg() above करोes an implicit memory barrier to
	 * ensure the ग_लिखो to MessageType (ie set to
	 * HVMSG_NONE) happens beक्रमe we पढ़ो the
	 * MessagePending and EOMing. Otherwise, the EOMing
	 * will not deliver any more messages since there is
	 * no empty slot
	 */
	अगर (msg->header.message_flags.msg_pending) अणु
		/*
		 * This will cause message queue rescan to
		 * possibly deliver another msg from the
		 * hypervisor
		 */
		hv_set_रेजिस्टर(HV_REGISTER_EOM, 0);
	पूर्ण
पूर्ण

व्योम hv_setup_vmbus_handler(व्योम (*handler)(व्योम));
व्योम hv_हटाओ_vmbus_handler(व्योम);
व्योम hv_setup_sसमयr0_handler(व्योम (*handler)(व्योम));
व्योम hv_हटाओ_sसमयr0_handler(व्योम);

व्योम hv_setup_kexec_handler(व्योम (*handler)(व्योम));
व्योम hv_हटाओ_kexec_handler(व्योम);
व्योम hv_setup_crash_handler(व्योम (*handler)(काष्ठा pt_regs *regs));
व्योम hv_हटाओ_crash_handler(व्योम);

बाह्य पूर्णांक vmbus_पूर्णांकerrupt;
बाह्य पूर्णांक vmbus_irq;

#अगर IS_ENABLED(CONFIG_HYPERV)
/*
 * Hypervisor's notion of भव processor ID is dअगरferent from
 * Linux' notion of CPU ID. This inक्रमmation can only be retrieved
 * in the context of the calling CPU. Setup a map क्रम easy access
 * to this inक्रमmation.
 */
बाह्य u32 *hv_vp_index;
बाह्य u32 hv_max_vp_index;

/* Sentinel value क्रम an uninitialized entry in hv_vp_index array */
#घोषणा VP_INVAL	U32_MAX

व्योम *hv_alloc_hyperv_page(व्योम);
व्योम *hv_alloc_hyperv_zeroed_page(व्योम);
व्योम hv_मुक्त_hyperv_page(अचिन्हित दीर्घ addr);

/**
 * hv_cpu_number_to_vp_number() - Map CPU to VP.
 * @cpu_number: CPU number in Linux terms
 *
 * This function वापसs the mapping between the Linux processor
 * number and the hypervisor's भव processor number, useful
 * in making hypercalls and such that talk about specअगरic
 * processors.
 *
 * Return: Virtual processor number in Hyper-V terms
 */
अटल अंतरभूत पूर्णांक hv_cpu_number_to_vp_number(पूर्णांक cpu_number)
अणु
	वापस hv_vp_index[cpu_number];
पूर्ण

अटल अंतरभूत पूर्णांक cpumask_to_vpset(काष्ठा hv_vpset *vpset,
				    स्थिर काष्ठा cpumask *cpus)
अणु
	पूर्णांक cpu, vcpu, vcpu_bank, vcpu_offset, nr_bank = 1;

	/* valid_bank_mask can represent up to 64 banks */
	अगर (hv_max_vp_index / 64 >= 64)
		वापस 0;

	/*
	 * Clear all banks up to the maximum possible bank as hv_tlb_flush_ex
	 * काष्ठाs are not cleared between calls, we risk flushing unneeded
	 * vCPUs otherwise.
	 */
	क्रम (vcpu_bank = 0; vcpu_bank <= hv_max_vp_index / 64; vcpu_bank++)
		vpset->bank_contents[vcpu_bank] = 0;

	/*
	 * Some banks may end up being empty but this is acceptable.
	 */
	क्रम_each_cpu(cpu, cpus) अणु
		vcpu = hv_cpu_number_to_vp_number(cpu);
		अगर (vcpu == VP_INVAL)
			वापस -1;
		vcpu_bank = vcpu / 64;
		vcpu_offset = vcpu % 64;
		__set_bit(vcpu_offset, (अचिन्हित दीर्घ *)
			  &vpset->bank_contents[vcpu_bank]);
		अगर (vcpu_bank >= nr_bank)
			nr_bank = vcpu_bank + 1;
	पूर्ण
	vpset->valid_bank_mask = GENMASK_ULL(nr_bank - 1, 0);
	वापस nr_bank;
पूर्ण

व्योम hyperv_report_panic(काष्ठा pt_regs *regs, दीर्घ err, bool in_die);
bool hv_is_hyperv_initialized(व्योम);
bool hv_is_hibernation_supported(व्योम);
क्रमागत hv_isolation_type hv_get_isolation_type(व्योम);
bool hv_is_isolation_supported(व्योम);
व्योम hyperv_cleanup(व्योम);
bool hv_query_ext_cap(u64 cap_query);
#अन्यथा /* CONFIG_HYPERV */
अटल अंतरभूत bool hv_is_hyperv_initialized(व्योम) अणु वापस false; पूर्ण
अटल अंतरभूत bool hv_is_hibernation_supported(व्योम) अणु वापस false; पूर्ण
अटल अंतरभूत व्योम hyperv_cleanup(व्योम) अणुपूर्ण
#पूर्ण_अगर /* CONFIG_HYPERV */

#पूर्ण_अगर
