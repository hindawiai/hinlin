<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *
 * Copyright IBM Corp. 2008
 *
 * Authors: Hollis Blanअक्षरd <hollisb@us.ibm.com>
 */

#अगर_अघोषित __POWERPC_KVM_PPC_H__
#घोषणा __POWERPC_KVM_PPC_H__

/* This file exists just so we can dereference kvm_vcpu, aव्योमing nested header
 * dependencies. */

#समावेश <linux/mutex.h>
#समावेश <linux/समयr.h>
#समावेश <linux/types.h>
#समावेश <linux/kvm_types.h>
#समावेश <linux/kvm_host.h>
#समावेश <linux/bug.h>
#अगर_घोषित CONFIG_PPC_BOOK3S
#समावेश <यंत्र/kvm_book3s.h>
#अन्यथा
#समावेश <यंत्र/kvm_booke.h>
#पूर्ण_अगर
#अगर_घोषित CONFIG_KVM_BOOK3S_64_HANDLER
#समावेश <यंत्र/paca.h>
#समावेश <यंत्र/xive.h>
#समावेश <यंत्र/cpu_has_feature.h>
#पूर्ण_अगर

/*
 * KVMPPC_INST_SW_BREAKPOINT is debug Inकाष्ठाion
 * क्रम supporting software अवरोधpoपूर्णांक.
 */
#घोषणा KVMPPC_INST_SW_BREAKPOINT	0x00dddd00

क्रमागत emulation_result अणु
	EMULATE_DONE,         /* no further processing */
	EMULATE_DO_MMIO,      /* kvm_run filled with MMIO request */
	EMULATE_FAIL,         /* can't emulate this inकाष्ठाion */
	EMULATE_AGAIN,        /* something went wrong. go again */
	EMULATE_EXIT_USER,    /* emulation requires निकास to user-space */
पूर्ण;

क्रमागत inकाष्ठाion_fetch_type अणु
	INST_GENERIC,
	INST_SC,		/* प्रणाली call */
पूर्ण;

क्रमागत xlate_instdata अणु
	XLATE_INST,		/* translate inकाष्ठाion address */
	XLATE_DATA		/* translate data address */
पूर्ण;

क्रमागत xlate_पढ़ोग_लिखो अणु
	XLATE_READ,		/* check क्रम पढ़ो permissions */
	XLATE_WRITE		/* check क्रम ग_लिखो permissions */
पूर्ण;

बाह्य पूर्णांक kvmppc_vcpu_run(काष्ठा kvm_vcpu *vcpu);
बाह्य पूर्णांक __kvmppc_vcpu_run(काष्ठा kvm_vcpu *vcpu);
बाह्य व्योम kvmppc_handler_highmem(व्योम);

बाह्य व्योम kvmppc_dump_vcpu(काष्ठा kvm_vcpu *vcpu);
बाह्य पूर्णांक kvmppc_handle_load(काष्ठा kvm_vcpu *vcpu,
                              अचिन्हित पूर्णांक rt, अचिन्हित पूर्णांक bytes,
			      पूर्णांक is_शेष_endian);
बाह्य पूर्णांक kvmppc_handle_loads(काष्ठा kvm_vcpu *vcpu,
                               अचिन्हित पूर्णांक rt, अचिन्हित पूर्णांक bytes,
			       पूर्णांक is_शेष_endian);
बाह्य पूर्णांक kvmppc_handle_vsx_load(काष्ठा kvm_vcpu *vcpu,
				अचिन्हित पूर्णांक rt, अचिन्हित पूर्णांक bytes,
			पूर्णांक is_शेष_endian, पूर्णांक mmio_sign_extend);
बाह्य पूर्णांक kvmppc_handle_vmx_load(काष्ठा kvm_vcpu *vcpu,
		अचिन्हित पूर्णांक rt, अचिन्हित पूर्णांक bytes, पूर्णांक is_शेष_endian);
बाह्य पूर्णांक kvmppc_handle_vmx_store(काष्ठा kvm_vcpu *vcpu,
		अचिन्हित पूर्णांक rs, अचिन्हित पूर्णांक bytes, पूर्णांक is_शेष_endian);
बाह्य पूर्णांक kvmppc_handle_store(काष्ठा kvm_vcpu *vcpu,
			       u64 val, अचिन्हित पूर्णांक bytes,
			       पूर्णांक is_शेष_endian);
बाह्य पूर्णांक kvmppc_handle_vsx_store(काष्ठा kvm_vcpu *vcpu,
				पूर्णांक rs, अचिन्हित पूर्णांक bytes,
				पूर्णांक is_शेष_endian);

बाह्य पूर्णांक kvmppc_load_last_inst(काष्ठा kvm_vcpu *vcpu,
				 क्रमागत inकाष्ठाion_fetch_type type, u32 *inst);

बाह्य पूर्णांक kvmppc_ld(काष्ठा kvm_vcpu *vcpu, uदीर्घ *eaddr, पूर्णांक size, व्योम *ptr,
		     bool data);
बाह्य पूर्णांक kvmppc_st(काष्ठा kvm_vcpu *vcpu, uदीर्घ *eaddr, पूर्णांक size, व्योम *ptr,
		     bool data);
बाह्य पूर्णांक kvmppc_emulate_inकाष्ठाion(काष्ठा kvm_vcpu *vcpu);
बाह्य पूर्णांक kvmppc_emulate_loadstore(काष्ठा kvm_vcpu *vcpu);
बाह्य पूर्णांक kvmppc_emulate_mmio(काष्ठा kvm_vcpu *vcpu);
बाह्य व्योम kvmppc_emulate_dec(काष्ठा kvm_vcpu *vcpu);
बाह्य u32 kvmppc_get_dec(काष्ठा kvm_vcpu *vcpu, u64 tb);
बाह्य व्योम kvmppc_decrementer_func(काष्ठा kvm_vcpu *vcpu);
बाह्य पूर्णांक kvmppc_sanity_check(काष्ठा kvm_vcpu *vcpu);
बाह्य पूर्णांक kvmppc_subarch_vcpu_init(काष्ठा kvm_vcpu *vcpu);
बाह्य व्योम kvmppc_subarch_vcpu_uninit(काष्ठा kvm_vcpu *vcpu);

/* Core-specअगरic hooks */

बाह्य व्योम kvmppc_mmu_map(काष्ठा kvm_vcpu *vcpu, u64 gvaddr, gpa_t gpaddr,
                           अचिन्हित पूर्णांक gtlb_idx);
बाह्य व्योम kvmppc_mmu_priv_चयन(काष्ठा kvm_vcpu *vcpu, पूर्णांक usermode);
बाह्य व्योम kvmppc_mmu_चयन_pid(काष्ठा kvm_vcpu *vcpu, u32 pid);
बाह्य पूर्णांक kvmppc_mmu_dtlb_index(काष्ठा kvm_vcpu *vcpu, gva_t eaddr);
बाह्य पूर्णांक kvmppc_mmu_itlb_index(काष्ठा kvm_vcpu *vcpu, gva_t eaddr);
बाह्य gpa_t kvmppc_mmu_xlate(काष्ठा kvm_vcpu *vcpu, अचिन्हित पूर्णांक gtlb_index,
                              gva_t eaddr);
बाह्य व्योम kvmppc_mmu_dtlb_miss(काष्ठा kvm_vcpu *vcpu);
बाह्य व्योम kvmppc_mmu_itlb_miss(काष्ठा kvm_vcpu *vcpu);
बाह्य पूर्णांक kvmppc_xlate(काष्ठा kvm_vcpu *vcpu, uदीर्घ eaddr,
			क्रमागत xlate_instdata xlid, क्रमागत xlate_पढ़ोग_लिखो xlrw,
			काष्ठा kvmppc_pte *pte);

बाह्य पूर्णांक kvmppc_core_vcpu_create(काष्ठा kvm_vcpu *vcpu);
बाह्य व्योम kvmppc_core_vcpu_मुक्त(काष्ठा kvm_vcpu *vcpu);
बाह्य पूर्णांक kvmppc_core_vcpu_setup(काष्ठा kvm_vcpu *vcpu);
बाह्य पूर्णांक kvmppc_core_check_processor_compat(व्योम);
बाह्य पूर्णांक kvmppc_core_vcpu_translate(काष्ठा kvm_vcpu *vcpu,
                                      काष्ठा kvm_translation *tr);

बाह्य व्योम kvmppc_core_vcpu_load(काष्ठा kvm_vcpu *vcpu, पूर्णांक cpu);
बाह्य व्योम kvmppc_core_vcpu_put(काष्ठा kvm_vcpu *vcpu);

बाह्य पूर्णांक kvmppc_core_prepare_to_enter(काष्ठा kvm_vcpu *vcpu);
बाह्य पूर्णांक kvmppc_core_pending_dec(काष्ठा kvm_vcpu *vcpu);
बाह्य व्योम kvmppc_core_queue_machine_check(काष्ठा kvm_vcpu *vcpu, uदीर्घ flags);
बाह्य व्योम kvmppc_core_queue_program(काष्ठा kvm_vcpu *vcpu, uदीर्घ flags);
बाह्य व्योम kvmppc_core_queue_fpunavail(काष्ठा kvm_vcpu *vcpu);
बाह्य व्योम kvmppc_core_queue_vec_unavail(काष्ठा kvm_vcpu *vcpu);
बाह्य व्योम kvmppc_core_queue_vsx_unavail(काष्ठा kvm_vcpu *vcpu);
बाह्य व्योम kvmppc_core_queue_dec(काष्ठा kvm_vcpu *vcpu);
बाह्य व्योम kvmppc_core_dequeue_dec(काष्ठा kvm_vcpu *vcpu);
बाह्य व्योम kvmppc_core_queue_बाह्यal(काष्ठा kvm_vcpu *vcpu,
                                       काष्ठा kvm_पूर्णांकerrupt *irq);
बाह्य व्योम kvmppc_core_dequeue_बाह्यal(काष्ठा kvm_vcpu *vcpu);
बाह्य व्योम kvmppc_core_queue_dtlb_miss(काष्ठा kvm_vcpu *vcpu, uदीर्घ dear_flags,
					uदीर्घ esr_flags);
बाह्य व्योम kvmppc_core_queue_data_storage(काष्ठा kvm_vcpu *vcpu,
					   uदीर्घ dear_flags,
					   uदीर्घ esr_flags);
बाह्य व्योम kvmppc_core_queue_itlb_miss(काष्ठा kvm_vcpu *vcpu);
बाह्य व्योम kvmppc_core_queue_inst_storage(काष्ठा kvm_vcpu *vcpu,
					   uदीर्घ esr_flags);
बाह्य व्योम kvmppc_core_flush_tlb(काष्ठा kvm_vcpu *vcpu);
बाह्य पूर्णांक kvmppc_core_check_requests(काष्ठा kvm_vcpu *vcpu);

बाह्य पूर्णांक kvmppc_booke_init(व्योम);
बाह्य व्योम kvmppc_booke_निकास(व्योम);

बाह्य व्योम kvmppc_core_destroy_mmu(काष्ठा kvm_vcpu *vcpu);
बाह्य पूर्णांक kvmppc_kvm_pv(काष्ठा kvm_vcpu *vcpu);
बाह्य व्योम kvmppc_map_magic(काष्ठा kvm_vcpu *vcpu);

बाह्य पूर्णांक kvmppc_allocate_hpt(काष्ठा kvm_hpt_info *info, u32 order);
बाह्य व्योम kvmppc_set_hpt(काष्ठा kvm *kvm, काष्ठा kvm_hpt_info *info);
बाह्य दीर्घ kvmppc_alloc_reset_hpt(काष्ठा kvm *kvm, पूर्णांक order);
बाह्य व्योम kvmppc_मुक्त_hpt(काष्ठा kvm_hpt_info *info);
बाह्य व्योम kvmppc_rmap_reset(काष्ठा kvm *kvm);
बाह्य दीर्घ kvmppc_prepare_vrma(काष्ठा kvm *kvm,
				काष्ठा kvm_userspace_memory_region *mem);
बाह्य व्योम kvmppc_map_vrma(काष्ठा kvm_vcpu *vcpu,
			काष्ठा kvm_memory_slot *memslot, अचिन्हित दीर्घ porder);
बाह्य पूर्णांक kvmppc_pseries_करो_hcall(काष्ठा kvm_vcpu *vcpu);
बाह्य दीर्घ kvm_spapr_tce_attach_iommu_group(काष्ठा kvm *kvm, पूर्णांक tablefd,
		काष्ठा iommu_group *grp);
बाह्य व्योम kvm_spapr_tce_release_iommu_group(काष्ठा kvm *kvm,
		काष्ठा iommu_group *grp);
बाह्य पूर्णांक kvmppc_चयन_mmu_to_hpt(काष्ठा kvm *kvm);
बाह्य पूर्णांक kvmppc_चयन_mmu_to_radix(काष्ठा kvm *kvm);
बाह्य व्योम kvmppc_setup_partition_table(काष्ठा kvm *kvm);

बाह्य दीर्घ kvm_vm_ioctl_create_spapr_tce(काष्ठा kvm *kvm,
				काष्ठा kvm_create_spapr_tce_64 *args);
बाह्य काष्ठा kvmppc_spapr_tce_table *kvmppc_find_table(
		काष्ठा kvm *kvm, अचिन्हित दीर्घ liobn);
#घोषणा kvmppc_ioba_validate(stt, ioba, npages)                         \
		(iommu_tce_check_ioba((stt)->page_shअगरt, (stt)->offset, \
				(stt)->size, (ioba), (npages)) ?        \
				H_PARAMETER : H_SUCCESS)
बाह्य दीर्घ kvmppc_h_put_tce(काष्ठा kvm_vcpu *vcpu, अचिन्हित दीर्घ liobn,
			     अचिन्हित दीर्घ ioba, अचिन्हित दीर्घ tce);
बाह्य दीर्घ kvmppc_h_put_tce_indirect(काष्ठा kvm_vcpu *vcpu,
		अचिन्हित दीर्घ liobn, अचिन्हित दीर्घ ioba,
		अचिन्हित दीर्घ tce_list, अचिन्हित दीर्घ npages);
बाह्य दीर्घ kvmppc_h_stuff_tce(काष्ठा kvm_vcpu *vcpu,
		अचिन्हित दीर्घ liobn, अचिन्हित दीर्घ ioba,
		अचिन्हित दीर्घ tce_value, अचिन्हित दीर्घ npages);
बाह्य दीर्घ kvmppc_h_get_tce(काष्ठा kvm_vcpu *vcpu, अचिन्हित दीर्घ liobn,
			     अचिन्हित दीर्घ ioba);
बाह्य काष्ठा page *kvm_alloc_hpt_cma(अचिन्हित दीर्घ nr_pages);
बाह्य व्योम kvm_मुक्त_hpt_cma(काष्ठा page *page, अचिन्हित दीर्घ nr_pages);
बाह्य पूर्णांक kvmppc_core_init_vm(काष्ठा kvm *kvm);
बाह्य व्योम kvmppc_core_destroy_vm(काष्ठा kvm *kvm);
बाह्य व्योम kvmppc_core_मुक्त_memslot(काष्ठा kvm *kvm,
				     काष्ठा kvm_memory_slot *slot);
बाह्य पूर्णांक kvmppc_core_prepare_memory_region(काष्ठा kvm *kvm,
				काष्ठा kvm_memory_slot *memslot,
				स्थिर काष्ठा kvm_userspace_memory_region *mem,
				क्रमागत kvm_mr_change change);
बाह्य व्योम kvmppc_core_commit_memory_region(काष्ठा kvm *kvm,
				स्थिर काष्ठा kvm_userspace_memory_region *mem,
				स्थिर काष्ठा kvm_memory_slot *old,
				स्थिर काष्ठा kvm_memory_slot *new,
				क्रमागत kvm_mr_change change);
बाह्य पूर्णांक kvm_vm_ioctl_get_smmu_info(काष्ठा kvm *kvm,
				      काष्ठा kvm_ppc_smmu_info *info);
बाह्य व्योम kvmppc_core_flush_memslot(काष्ठा kvm *kvm,
				      काष्ठा kvm_memory_slot *memslot);

बाह्य पूर्णांक kvmppc_bookehv_init(व्योम);
बाह्य व्योम kvmppc_bookehv_निकास(व्योम);

बाह्य पूर्णांक kvmppc_prepare_to_enter(काष्ठा kvm_vcpu *vcpu);

बाह्य पूर्णांक kvm_vm_ioctl_get_htab_fd(काष्ठा kvm *kvm, काष्ठा kvm_get_htab_fd *);
बाह्य दीर्घ kvm_vm_ioctl_resize_hpt_prepare(काष्ठा kvm *kvm,
					    काष्ठा kvm_ppc_resize_hpt *rhpt);
बाह्य दीर्घ kvm_vm_ioctl_resize_hpt_commit(काष्ठा kvm *kvm,
					   काष्ठा kvm_ppc_resize_hpt *rhpt);

पूर्णांक kvm_vcpu_ioctl_पूर्णांकerrupt(काष्ठा kvm_vcpu *vcpu, काष्ठा kvm_पूर्णांकerrupt *irq);

बाह्य पूर्णांक kvm_vm_ioctl_rtas_define_token(काष्ठा kvm *kvm, व्योम __user *argp);
बाह्य पूर्णांक kvmppc_rtas_hcall(काष्ठा kvm_vcpu *vcpu);
बाह्य व्योम kvmppc_rtas_tokens_मुक्त(काष्ठा kvm *kvm);

बाह्य पूर्णांक kvmppc_xics_set_xive(काष्ठा kvm *kvm, u32 irq, u32 server,
				u32 priority);
बाह्य पूर्णांक kvmppc_xics_get_xive(काष्ठा kvm *kvm, u32 irq, u32 *server,
				u32 *priority);
बाह्य पूर्णांक kvmppc_xics_पूर्णांक_on(काष्ठा kvm *kvm, u32 irq);
बाह्य पूर्णांक kvmppc_xics_पूर्णांक_off(काष्ठा kvm *kvm, u32 irq);

व्योम kvmppc_core_dequeue_debug(काष्ठा kvm_vcpu *vcpu);
व्योम kvmppc_core_queue_debug(काष्ठा kvm_vcpu *vcpu);

जोड़ kvmppc_one_reg अणु
	u32	wval;
	u64	dval;
	vector128 vval;
	u64	vsxval[2];
	u32	vsx32val[4];
	u16	vsx16val[8];
	u8	vsx8val[16];
	काष्ठा अणु
		u64	addr;
		u64	length;
	पूर्ण	vpaval;
	u64	xive_timaval[2];
पूर्ण;

काष्ठा kvmppc_ops अणु
	काष्ठा module *owner;
	पूर्णांक (*get_sregs)(काष्ठा kvm_vcpu *vcpu, काष्ठा kvm_sregs *sregs);
	पूर्णांक (*set_sregs)(काष्ठा kvm_vcpu *vcpu, काष्ठा kvm_sregs *sregs);
	पूर्णांक (*get_one_reg)(काष्ठा kvm_vcpu *vcpu, u64 id,
			   जोड़ kvmppc_one_reg *val);
	पूर्णांक (*set_one_reg)(काष्ठा kvm_vcpu *vcpu, u64 id,
			   जोड़ kvmppc_one_reg *val);
	व्योम (*vcpu_load)(काष्ठा kvm_vcpu *vcpu, पूर्णांक cpu);
	व्योम (*vcpu_put)(काष्ठा kvm_vcpu *vcpu);
	व्योम (*inject_पूर्णांकerrupt)(काष्ठा kvm_vcpu *vcpu, पूर्णांक vec, u64 srr1_flags);
	व्योम (*set_msr)(काष्ठा kvm_vcpu *vcpu, u64 msr);
	पूर्णांक (*vcpu_run)(काष्ठा kvm_vcpu *vcpu);
	पूर्णांक (*vcpu_create)(काष्ठा kvm_vcpu *vcpu);
	व्योम (*vcpu_मुक्त)(काष्ठा kvm_vcpu *vcpu);
	पूर्णांक (*check_requests)(काष्ठा kvm_vcpu *vcpu);
	पूर्णांक (*get_dirty_log)(काष्ठा kvm *kvm, काष्ठा kvm_dirty_log *log);
	व्योम (*flush_memslot)(काष्ठा kvm *kvm, काष्ठा kvm_memory_slot *memslot);
	पूर्णांक (*prepare_memory_region)(काष्ठा kvm *kvm,
				     काष्ठा kvm_memory_slot *memslot,
				     स्थिर काष्ठा kvm_userspace_memory_region *mem,
				     क्रमागत kvm_mr_change change);
	व्योम (*commit_memory_region)(काष्ठा kvm *kvm,
				     स्थिर काष्ठा kvm_userspace_memory_region *mem,
				     स्थिर काष्ठा kvm_memory_slot *old,
				     स्थिर काष्ठा kvm_memory_slot *new,
				     क्रमागत kvm_mr_change change);
	bool (*unmap_gfn_range)(काष्ठा kvm *kvm, काष्ठा kvm_gfn_range *range);
	bool (*age_gfn)(काष्ठा kvm *kvm, काष्ठा kvm_gfn_range *range);
	bool (*test_age_gfn)(काष्ठा kvm *kvm, काष्ठा kvm_gfn_range *range);
	bool (*set_spte_gfn)(काष्ठा kvm *kvm, काष्ठा kvm_gfn_range *range);
	व्योम (*मुक्त_memslot)(काष्ठा kvm_memory_slot *slot);
	पूर्णांक (*init_vm)(काष्ठा kvm *kvm);
	व्योम (*destroy_vm)(काष्ठा kvm *kvm);
	पूर्णांक (*get_smmu_info)(काष्ठा kvm *kvm, काष्ठा kvm_ppc_smmu_info *info);
	पूर्णांक (*emulate_op)(काष्ठा kvm_vcpu *vcpu,
			  अचिन्हित पूर्णांक inst, पूर्णांक *advance);
	पूर्णांक (*emulate_mtspr)(काष्ठा kvm_vcpu *vcpu, पूर्णांक sprn, uदीर्घ spr_val);
	पूर्णांक (*emulate_mfspr)(काष्ठा kvm_vcpu *vcpu, पूर्णांक sprn, uदीर्घ *spr_val);
	व्योम (*fast_vcpu_kick)(काष्ठा kvm_vcpu *vcpu);
	दीर्घ (*arch_vm_ioctl)(काष्ठा file *filp, अचिन्हित पूर्णांक ioctl,
			      अचिन्हित दीर्घ arg);
	पूर्णांक (*hcall_implemented)(अचिन्हित दीर्घ hcall);
	पूर्णांक (*irq_bypass_add_producer)(काष्ठा irq_bypass_consumer *,
				       काष्ठा irq_bypass_producer *);
	व्योम (*irq_bypass_del_producer)(काष्ठा irq_bypass_consumer *,
					काष्ठा irq_bypass_producer *);
	पूर्णांक (*configure_mmu)(काष्ठा kvm *kvm, काष्ठा kvm_ppc_mmuv3_cfg *cfg);
	पूर्णांक (*get_rmmu_info)(काष्ठा kvm *kvm, काष्ठा kvm_ppc_rmmu_info *info);
	पूर्णांक (*set_smt_mode)(काष्ठा kvm *kvm, अचिन्हित दीर्घ mode,
			    अचिन्हित दीर्घ flags);
	व्योम (*giveup_ext)(काष्ठा kvm_vcpu *vcpu, uदीर्घ msr);
	पूर्णांक (*enable_nested)(काष्ठा kvm *kvm);
	पूर्णांक (*load_from_eaddr)(काष्ठा kvm_vcpu *vcpu, uदीर्घ *eaddr, व्योम *ptr,
			       पूर्णांक size);
	पूर्णांक (*store_to_eaddr)(काष्ठा kvm_vcpu *vcpu, uदीर्घ *eaddr, व्योम *ptr,
			      पूर्णांक size);
	पूर्णांक (*enable_svm)(काष्ठा kvm *kvm);
	पूर्णांक (*svm_off)(काष्ठा kvm *kvm);
	पूर्णांक (*enable_dawr1)(काष्ठा kvm *kvm);
	bool (*hash_v3_possible)(व्योम);
पूर्ण;

बाह्य काष्ठा kvmppc_ops *kvmppc_hv_ops;
बाह्य काष्ठा kvmppc_ops *kvmppc_pr_ops;

अटल अंतरभूत पूर्णांक kvmppc_get_last_inst(काष्ठा kvm_vcpu *vcpu,
				क्रमागत inकाष्ठाion_fetch_type type, u32 *inst)
अणु
	पूर्णांक ret = EMULATE_DONE;
	u32 fetched_inst;

	/* Load the inकाष्ठाion manually अगर it failed to करो so in the
	 * निकास path */
	अगर (vcpu->arch.last_inst == KVM_INST_FETCH_FAILED)
		ret = kvmppc_load_last_inst(vcpu, type, &vcpu->arch.last_inst);

	/*  Write fetch_failed unswapped अगर the fetch failed */
	अगर (ret == EMULATE_DONE)
		fetched_inst = kvmppc_need_byteswap(vcpu) ?
				swab32(vcpu->arch.last_inst) :
				vcpu->arch.last_inst;
	अन्यथा
		fetched_inst = vcpu->arch.last_inst;

	*inst = fetched_inst;
	वापस ret;
पूर्ण

अटल अंतरभूत bool is_kvmppc_hv_enabled(काष्ठा kvm *kvm)
अणु
	वापस kvm->arch.kvm_ops == kvmppc_hv_ops;
पूर्ण

बाह्य पूर्णांक kvmppc_hwrng_present(व्योम);

/*
 * Cuts out inst bits with ordering according to spec.
 * That means the lefपंचांगost bit is zero. All given bits are included.
 */
अटल अंतरभूत u32 kvmppc_get_field(u64 inst, पूर्णांक msb, पूर्णांक lsb)
अणु
	u32 r;
	u32 mask;

	BUG_ON(msb > lsb);

	mask = (1 << (lsb - msb + 1)) - 1;
	r = (inst >> (63 - lsb)) & mask;

	वापस r;
पूर्ण

/*
 * Replaces inst bits with ordering according to spec.
 */
अटल अंतरभूत u32 kvmppc_set_field(u64 inst, पूर्णांक msb, पूर्णांक lsb, पूर्णांक value)
अणु
	u32 r;
	u32 mask;

	BUG_ON(msb > lsb);

	mask = ((1 << (lsb - msb + 1)) - 1) << (63 - lsb);
	r = (inst & ~mask) | ((value << (63 - lsb)) & mask);

	वापस r;
पूर्ण

#घोषणा one_reg_size(id)	\
	(1ul << (((id) & KVM_REG_SIZE_MASK) >> KVM_REG_SIZE_SHIFT))

#घोषणा get_reg_val(id, reg)	(अणु		\
	जोड़ kvmppc_one_reg __u;		\
	चयन (one_reg_size(id)) अणु		\
	हाल 4: __u.wval = (reg); अवरोध;	\
	हाल 8: __u.dval = (reg); अवरोध;	\
	शेष: BUG();				\
	पूर्ण					\
	__u;					\
पूर्ण)


#घोषणा set_reg_val(id, val)	(अणु		\
	u64 __v;				\
	चयन (one_reg_size(id)) अणु		\
	हाल 4: __v = (val).wval; अवरोध;	\
	हाल 8: __v = (val).dval; अवरोध;	\
	शेष: BUG();				\
	पूर्ण					\
	__v;					\
पूर्ण)

पूर्णांक kvmppc_core_get_sregs(काष्ठा kvm_vcpu *vcpu, काष्ठा kvm_sregs *sregs);
पूर्णांक kvmppc_core_set_sregs(काष्ठा kvm_vcpu *vcpu, काष्ठा kvm_sregs *sregs);

पूर्णांक kvmppc_get_sregs_ivor(काष्ठा kvm_vcpu *vcpu, काष्ठा kvm_sregs *sregs);
पूर्णांक kvmppc_set_sregs_ivor(काष्ठा kvm_vcpu *vcpu, काष्ठा kvm_sregs *sregs);

पूर्णांक kvm_vcpu_ioctl_get_one_reg(काष्ठा kvm_vcpu *vcpu, काष्ठा kvm_one_reg *reg);
पूर्णांक kvm_vcpu_ioctl_set_one_reg(काष्ठा kvm_vcpu *vcpu, काष्ठा kvm_one_reg *reg);
पूर्णांक kvmppc_get_one_reg(काष्ठा kvm_vcpu *vcpu, u64 id, जोड़ kvmppc_one_reg *);
पूर्णांक kvmppc_set_one_reg(काष्ठा kvm_vcpu *vcpu, u64 id, जोड़ kvmppc_one_reg *);

व्योम kvmppc_set_pid(काष्ठा kvm_vcpu *vcpu, u32 pid);

काष्ठा खोलोpic;

#अगर_घोषित CONFIG_KVM_BOOK3S_HV_POSSIBLE
बाह्य व्योम kvm_cma_reserve(व्योम) __init;
अटल अंतरभूत व्योम kvmppc_set_xics_phys(पूर्णांक cpu, अचिन्हित दीर्घ addr)
अणु
	paca_ptrs[cpu]->kvm_hstate.xics_phys = (व्योम __iomem *)addr;
पूर्ण

अटल अंतरभूत व्योम kvmppc_set_xive_tima(पूर्णांक cpu,
					अचिन्हित दीर्घ phys_addr,
					व्योम __iomem *virt_addr)
अणु
	paca_ptrs[cpu]->kvm_hstate.xive_tima_phys = (व्योम __iomem *)phys_addr;
	paca_ptrs[cpu]->kvm_hstate.xive_tima_virt = virt_addr;
पूर्ण

अटल अंतरभूत u32 kvmppc_get_xics_latch(व्योम)
अणु
	u32 xirr;

	xirr = get_paca()->kvm_hstate.saved_xirr;
	get_paca()->kvm_hstate.saved_xirr = 0;
	वापस xirr;
पूर्ण

/*
 * To aव्योम the need to unnecessarily निकास fully to the host kernel, an IPI to
 * a CPU thपढ़ो that's running/napping inside of a guest is by शेष regarded
 * as a request to wake the CPU (अगर needed) and जारी execution within the
 * guest, potentially to process new state like बाह्यally-generated
 * पूर्णांकerrupts or IPIs sent from within the guest itself (e.g. H_PROD/H_IPI).
 *
 * To क्रमce an निकास to the host kernel, kvmppc_set_host_ipi() must be called
 * prior to issuing the IPI to set the corresponding 'host_ipi' flag in the
 * target CPU's PACA. To aव्योम unnecessary निकासs to the host, this flag should
 * be immediately cleared via kvmppc_clear_host_ipi() by the IPI handler on
 * the receiving side prior to processing the IPI work.
 *
 * NOTE:
 *
 * We currently issue an smp_mb() at the beginning of kvmppc_set_host_ipi().
 * This is to guard against sequences such as the following:
 *
 *      CPU
 *        X: smp_muxed_ipi_set_message():
 *        X:   smp_mb()
 *        X:   message[RESCHEDULE] = 1
 *        X: करोorbell_global_ipi(42):
 *        X:   kvmppc_set_host_ipi(42)
 *        X:   ppc_msgsnd_sync()/smp_mb()
 *        X:   ppc_msgsnd() -> 42
 *       42: करोorbell_exception(): // from CPU X
 *       42:   ppc_msgsync()
 *      105: smp_muxed_ipi_set_message():
 *      105:   smb_mb()
 *           // STORE DEFERRED DUE TO RE-ORDERING
 *    --105:   message[CALL_FUNCTION] = 1
 *    | 105: करोorbell_global_ipi(42):
 *    | 105:   kvmppc_set_host_ipi(42)
 *    |  42:   kvmppc_clear_host_ipi(42)
 *    |  42: smp_ipi_demux_relaxed()
 *    |  42: // वापसs to executing guest
 *    |      // RE-ORDERED STORE COMPLETES
 *    ->105:   message[CALL_FUNCTION] = 1
 *      105:   ppc_msgsnd_sync()/smp_mb()
 *      105:   ppc_msgsnd() -> 42
 *       42: local_paca->kvm_hstate.host_ipi == 0 // IPI ignored
 *      105: // hangs रुकोing on 42 to process messages/call_single_queue
 *
 * We also issue an smp_mb() at the end of kvmppc_clear_host_ipi(). This is
 * to guard against sequences such as the following (as well as to create
 * a पढ़ो-side pairing with the barrier in kvmppc_set_host_ipi()):
 *
 *      CPU
 *        X: smp_muxed_ipi_set_message():
 *        X:   smp_mb()
 *        X:   message[RESCHEDULE] = 1
 *        X: करोorbell_global_ipi(42):
 *        X:   kvmppc_set_host_ipi(42)
 *        X:   ppc_msgsnd_sync()/smp_mb()
 *        X:   ppc_msgsnd() -> 42
 *       42: करोorbell_exception(): // from CPU X
 *       42:   ppc_msgsync()
 *           // STORE DEFERRED DUE TO RE-ORDERING
 *    -- 42:   kvmppc_clear_host_ipi(42)
 *    |  42: smp_ipi_demux_relaxed()
 *    | 105: smp_muxed_ipi_set_message():
 *    | 105:   smb_mb()
 *    | 105:   message[CALL_FUNCTION] = 1
 *    | 105: करोorbell_global_ipi(42):
 *    | 105:   kvmppc_set_host_ipi(42)
 *    |      // RE-ORDERED STORE COMPLETES
 *    -> 42:   kvmppc_clear_host_ipi(42)
 *       42: // वापसs to executing guest
 *      105:   ppc_msgsnd_sync()/smp_mb()
 *      105:   ppc_msgsnd() -> 42
 *       42: local_paca->kvm_hstate.host_ipi == 0 // IPI ignored
 *      105: // hangs रुकोing on 42 to process messages/call_single_queue
 */
अटल अंतरभूत व्योम kvmppc_set_host_ipi(पूर्णांक cpu)
अणु
	/*
	 * order stores of IPI messages vs. setting of host_ipi flag
	 *
	 * pairs with the barrier in kvmppc_clear_host_ipi()
	 */
	smp_mb();
	paca_ptrs[cpu]->kvm_hstate.host_ipi = 1;
पूर्ण

अटल अंतरभूत व्योम kvmppc_clear_host_ipi(पूर्णांक cpu)
अणु
	paca_ptrs[cpu]->kvm_hstate.host_ipi = 0;
	/*
	 * order clearing of host_ipi flag vs. processing of IPI messages
	 *
	 * pairs with the barrier in kvmppc_set_host_ipi()
	 */
	smp_mb();
पूर्ण

अटल अंतरभूत व्योम kvmppc_fast_vcpu_kick(काष्ठा kvm_vcpu *vcpu)
अणु
	vcpu->kvm->arch.kvm_ops->fast_vcpu_kick(vcpu);
पूर्ण

बाह्य व्योम kvm_hv_vm_activated(व्योम);
बाह्य व्योम kvm_hv_vm_deactivated(व्योम);
बाह्य bool kvm_hv_mode_active(व्योम);

बाह्य व्योम kvmppc_check_need_tlb_flush(काष्ठा kvm *kvm, पूर्णांक pcpu,
					काष्ठा kvm_nested_guest *nested);

#अन्यथा
अटल अंतरभूत व्योम __init kvm_cma_reserve(व्योम)
अणुपूर्ण

अटल अंतरभूत व्योम kvmppc_set_xics_phys(पूर्णांक cpu, अचिन्हित दीर्घ addr)
अणुपूर्ण

अटल अंतरभूत व्योम kvmppc_set_xive_tima(पूर्णांक cpu,
					अचिन्हित दीर्घ phys_addr,
					व्योम __iomem *virt_addr)
अणुपूर्ण

अटल अंतरभूत u32 kvmppc_get_xics_latch(व्योम)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम kvmppc_set_host_ipi(पूर्णांक cpu)
अणुपूर्ण

अटल अंतरभूत व्योम kvmppc_clear_host_ipi(पूर्णांक cpu)
अणुपूर्ण

अटल अंतरभूत व्योम kvmppc_fast_vcpu_kick(काष्ठा kvm_vcpu *vcpu)
अणु
	kvm_vcpu_kick(vcpu);
पूर्ण

अटल अंतरभूत bool kvm_hv_mode_active(व्योम)		अणु वापस false; पूर्ण

#पूर्ण_अगर

#अगर_घोषित CONFIG_KVM_XICS
अटल अंतरभूत पूर्णांक kvmppc_xics_enabled(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस vcpu->arch.irq_type == KVMPPC_IRQ_XICS;
पूर्ण

अटल अंतरभूत काष्ठा kvmppc_passthru_irqmap *kvmppc_get_passthru_irqmap(
				काष्ठा kvm *kvm)
अणु
	अगर (kvm && kvm_irq_bypass)
		वापस kvm->arch.pimap;
	वापस शून्य;
पूर्ण

बाह्य व्योम kvmppc_alloc_host_rm_ops(व्योम);
बाह्य व्योम kvmppc_मुक्त_host_rm_ops(व्योम);
बाह्य व्योम kvmppc_मुक्त_pimap(काष्ठा kvm *kvm);
बाह्य पूर्णांक kvmppc_xics_rm_complete(काष्ठा kvm_vcpu *vcpu, u32 hcall);
बाह्य व्योम kvmppc_xics_मुक्त_icp(काष्ठा kvm_vcpu *vcpu);
बाह्य पूर्णांक kvmppc_xics_hcall(काष्ठा kvm_vcpu *vcpu, u32 cmd);
बाह्य u64 kvmppc_xics_get_icp(काष्ठा kvm_vcpu *vcpu);
बाह्य पूर्णांक kvmppc_xics_set_icp(काष्ठा kvm_vcpu *vcpu, u64 icpval);
बाह्य पूर्णांक kvmppc_xics_connect_vcpu(काष्ठा kvm_device *dev,
			काष्ठा kvm_vcpu *vcpu, u32 cpu);
बाह्य व्योम kvmppc_xics_ipi_action(व्योम);
बाह्य व्योम kvmppc_xics_set_mapped(काष्ठा kvm *kvm, अचिन्हित दीर्घ guest_irq,
				   अचिन्हित दीर्घ host_irq);
बाह्य व्योम kvmppc_xics_clr_mapped(काष्ठा kvm *kvm, अचिन्हित दीर्घ guest_irq,
				   अचिन्हित दीर्घ host_irq);
बाह्य दीर्घ kvmppc_deliver_irq_passthru(काष्ठा kvm_vcpu *vcpu, __be32 xirr,
					काष्ठा kvmppc_irq_map *irq_map,
					काष्ठा kvmppc_passthru_irqmap *pimap,
					bool *again);

बाह्य पूर्णांक kvmppc_xics_set_irq(काष्ठा kvm *kvm, पूर्णांक irq_source_id, u32 irq,
			       पूर्णांक level, bool line_status);

बाह्य पूर्णांक h_ipi_redirect;
#अन्यथा
अटल अंतरभूत काष्ठा kvmppc_passthru_irqmap *kvmppc_get_passthru_irqmap(
				काष्ठा kvm *kvm)
	अणु वापस शून्य; पूर्ण
अटल अंतरभूत व्योम kvmppc_alloc_host_rm_ops(व्योम) अणुपूर्ण
अटल अंतरभूत व्योम kvmppc_मुक्त_host_rm_ops(व्योम) अणुपूर्ण
अटल अंतरभूत व्योम kvmppc_मुक्त_pimap(काष्ठा kvm *kvm) अणुपूर्ण
अटल अंतरभूत पूर्णांक kvmppc_xics_rm_complete(काष्ठा kvm_vcpu *vcpu, u32 hcall)
	अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक kvmppc_xics_enabled(काष्ठा kvm_vcpu *vcpu)
	अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम kvmppc_xics_मुक्त_icp(काष्ठा kvm_vcpu *vcpu) अणु पूर्ण
अटल अंतरभूत पूर्णांक kvmppc_xics_hcall(काष्ठा kvm_vcpu *vcpu, u32 cmd)
	अणु वापस 0; पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_KVM_XIVE
/*
 * Below the first "xive" is the "eXternal Interrupt Virtualization Engine"
 * ie. P9 new पूर्णांकerrupt controller, जबतक the second "xive" is the legacy
 * "eXternal Interrupt Vector Entry" which is the configuration of an
 * पूर्णांकerrupt on the "xics" पूर्णांकerrupt controller on P8 and earlier. Those
 * two function consume or produce a legacy "XIVE" state from the
 * new "XIVE" पूर्णांकerrupt controller.
 */
बाह्य पूर्णांक kvmppc_xive_set_xive(काष्ठा kvm *kvm, u32 irq, u32 server,
				u32 priority);
बाह्य पूर्णांक kvmppc_xive_get_xive(काष्ठा kvm *kvm, u32 irq, u32 *server,
				u32 *priority);
बाह्य पूर्णांक kvmppc_xive_पूर्णांक_on(काष्ठा kvm *kvm, u32 irq);
बाह्य पूर्णांक kvmppc_xive_पूर्णांक_off(काष्ठा kvm *kvm, u32 irq);
बाह्य व्योम kvmppc_xive_init_module(व्योम);
बाह्य व्योम kvmppc_xive_निकास_module(व्योम);

बाह्य पूर्णांक kvmppc_xive_connect_vcpu(काष्ठा kvm_device *dev,
				    काष्ठा kvm_vcpu *vcpu, u32 cpu);
बाह्य व्योम kvmppc_xive_cleanup_vcpu(काष्ठा kvm_vcpu *vcpu);
बाह्य पूर्णांक kvmppc_xive_set_mapped(काष्ठा kvm *kvm, अचिन्हित दीर्घ guest_irq,
				  काष्ठा irq_desc *host_desc);
बाह्य पूर्णांक kvmppc_xive_clr_mapped(काष्ठा kvm *kvm, अचिन्हित दीर्घ guest_irq,
				  काष्ठा irq_desc *host_desc);
बाह्य u64 kvmppc_xive_get_icp(काष्ठा kvm_vcpu *vcpu);
बाह्य पूर्णांक kvmppc_xive_set_icp(काष्ठा kvm_vcpu *vcpu, u64 icpval);

बाह्य पूर्णांक kvmppc_xive_set_irq(काष्ठा kvm *kvm, पूर्णांक irq_source_id, u32 irq,
			       पूर्णांक level, bool line_status);
बाह्य व्योम kvmppc_xive_push_vcpu(काष्ठा kvm_vcpu *vcpu);

अटल अंतरभूत पूर्णांक kvmppc_xive_enabled(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस vcpu->arch.irq_type == KVMPPC_IRQ_XIVE;
पूर्ण

बाह्य पूर्णांक kvmppc_xive_native_connect_vcpu(काष्ठा kvm_device *dev,
					   काष्ठा kvm_vcpu *vcpu, u32 cpu);
बाह्य व्योम kvmppc_xive_native_cleanup_vcpu(काष्ठा kvm_vcpu *vcpu);
बाह्य व्योम kvmppc_xive_native_init_module(व्योम);
बाह्य व्योम kvmppc_xive_native_निकास_module(व्योम);
बाह्य पूर्णांक kvmppc_xive_native_get_vp(काष्ठा kvm_vcpu *vcpu,
				     जोड़ kvmppc_one_reg *val);
बाह्य पूर्णांक kvmppc_xive_native_set_vp(काष्ठा kvm_vcpu *vcpu,
				     जोड़ kvmppc_one_reg *val);
बाह्य bool kvmppc_xive_native_supported(व्योम);

#अन्यथा
अटल अंतरभूत पूर्णांक kvmppc_xive_set_xive(काष्ठा kvm *kvm, u32 irq, u32 server,
				       u32 priority) अणु वापस -1; पूर्ण
अटल अंतरभूत पूर्णांक kvmppc_xive_get_xive(काष्ठा kvm *kvm, u32 irq, u32 *server,
				       u32 *priority) अणु वापस -1; पूर्ण
अटल अंतरभूत पूर्णांक kvmppc_xive_पूर्णांक_on(काष्ठा kvm *kvm, u32 irq) अणु वापस -1; पूर्ण
अटल अंतरभूत पूर्णांक kvmppc_xive_पूर्णांक_off(काष्ठा kvm *kvm, u32 irq) अणु वापस -1; पूर्ण
अटल अंतरभूत व्योम kvmppc_xive_init_module(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम kvmppc_xive_निकास_module(व्योम) अणु पूर्ण

अटल अंतरभूत पूर्णांक kvmppc_xive_connect_vcpu(काष्ठा kvm_device *dev,
					   काष्ठा kvm_vcpu *vcpu, u32 cpu) अणु वापस -EBUSY; पूर्ण
अटल अंतरभूत व्योम kvmppc_xive_cleanup_vcpu(काष्ठा kvm_vcpu *vcpu) अणु पूर्ण
अटल अंतरभूत पूर्णांक kvmppc_xive_set_mapped(काष्ठा kvm *kvm, अचिन्हित दीर्घ guest_irq,
					 काष्ठा irq_desc *host_desc) अणु वापस -ENODEV; पूर्ण
अटल अंतरभूत पूर्णांक kvmppc_xive_clr_mapped(काष्ठा kvm *kvm, अचिन्हित दीर्घ guest_irq,
					 काष्ठा irq_desc *host_desc) अणु वापस -ENODEV; पूर्ण
अटल अंतरभूत u64 kvmppc_xive_get_icp(काष्ठा kvm_vcpu *vcpu) अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक kvmppc_xive_set_icp(काष्ठा kvm_vcpu *vcpu, u64 icpval) अणु वापस -ENOENT; पूर्ण

अटल अंतरभूत पूर्णांक kvmppc_xive_set_irq(काष्ठा kvm *kvm, पूर्णांक irq_source_id, u32 irq,
				      पूर्णांक level, bool line_status) अणु वापस -ENODEV; पूर्ण
अटल अंतरभूत व्योम kvmppc_xive_push_vcpu(काष्ठा kvm_vcpu *vcpu) अणु पूर्ण

अटल अंतरभूत पूर्णांक kvmppc_xive_enabled(काष्ठा kvm_vcpu *vcpu)
	अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक kvmppc_xive_native_connect_vcpu(काष्ठा kvm_device *dev,
			  काष्ठा kvm_vcpu *vcpu, u32 cpu) अणु वापस -EBUSY; पूर्ण
अटल अंतरभूत व्योम kvmppc_xive_native_cleanup_vcpu(काष्ठा kvm_vcpu *vcpu) अणु पूर्ण
अटल अंतरभूत व्योम kvmppc_xive_native_init_module(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम kvmppc_xive_native_निकास_module(व्योम) अणु पूर्ण
अटल अंतरभूत पूर्णांक kvmppc_xive_native_get_vp(काष्ठा kvm_vcpu *vcpu,
					    जोड़ kvmppc_one_reg *val)
अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक kvmppc_xive_native_set_vp(काष्ठा kvm_vcpu *vcpu,
					    जोड़ kvmppc_one_reg *val)
अणु वापस -ENOENT; पूर्ण

#पूर्ण_अगर /* CONFIG_KVM_XIVE */

#अगर defined(CONFIG_PPC_POWERNV) && defined(CONFIG_KVM_BOOK3S_64_HANDLER)
अटल अंतरभूत bool xics_on_xive(व्योम)
अणु
	वापस xive_enabled() && cpu_has_feature(CPU_FTR_HVMODE);
पूर्ण
#अन्यथा
अटल अंतरभूत bool xics_on_xive(व्योम)
अणु
	वापस false;
पूर्ण
#पूर्ण_अगर

/*
 * Prototypes क्रम functions called only from assembler code.
 * Having prototypes reduces sparse errors.
 */
दीर्घ kvmppc_rm_h_put_tce(काष्ठा kvm_vcpu *vcpu, अचिन्हित दीर्घ liobn,
			 अचिन्हित दीर्घ ioba, अचिन्हित दीर्घ tce);
दीर्घ kvmppc_rm_h_put_tce_indirect(काष्ठा kvm_vcpu *vcpu,
				  अचिन्हित दीर्घ liobn, अचिन्हित दीर्घ ioba,
				  अचिन्हित दीर्घ tce_list, अचिन्हित दीर्घ npages);
दीर्घ kvmppc_rm_h_stuff_tce(काष्ठा kvm_vcpu *vcpu,
			   अचिन्हित दीर्घ liobn, अचिन्हित दीर्घ ioba,
			   अचिन्हित दीर्घ tce_value, अचिन्हित दीर्घ npages);
दीर्घ पूर्णांक kvmppc_rm_h_confer(काष्ठा kvm_vcpu *vcpu, पूर्णांक target,
                            अचिन्हित पूर्णांक yield_count);
दीर्घ kvmppc_h_अक्रमom(काष्ठा kvm_vcpu *vcpu);
व्योम kvmhv_commence_निकास(पूर्णांक trap);
व्योम kvmppc_realmode_machine_check(काष्ठा kvm_vcpu *vcpu);
व्योम kvmppc_subcore_enter_guest(व्योम);
व्योम kvmppc_subcore_निकास_guest(व्योम);
दीर्घ kvmppc_realmode_hmi_handler(व्योम);
दीर्घ kvmppc_h_enter(काष्ठा kvm_vcpu *vcpu, अचिन्हित दीर्घ flags,
                    दीर्घ pte_index, अचिन्हित दीर्घ pteh, अचिन्हित दीर्घ ptel);
दीर्घ kvmppc_h_हटाओ(काष्ठा kvm_vcpu *vcpu, अचिन्हित दीर्घ flags,
                     अचिन्हित दीर्घ pte_index, अचिन्हित दीर्घ avpn);
दीर्घ kvmppc_h_bulk_हटाओ(काष्ठा kvm_vcpu *vcpu);
दीर्घ kvmppc_h_protect(काष्ठा kvm_vcpu *vcpu, अचिन्हित दीर्घ flags,
                      अचिन्हित दीर्घ pte_index, अचिन्हित दीर्घ avpn);
दीर्घ kvmppc_h_पढ़ो(काष्ठा kvm_vcpu *vcpu, अचिन्हित दीर्घ flags,
                   अचिन्हित दीर्घ pte_index);
दीर्घ kvmppc_h_clear_ref(काष्ठा kvm_vcpu *vcpu, अचिन्हित दीर्घ flags,
                        अचिन्हित दीर्घ pte_index);
दीर्घ kvmppc_h_clear_mod(काष्ठा kvm_vcpu *vcpu, अचिन्हित दीर्घ flags,
                        अचिन्हित दीर्घ pte_index);
दीर्घ kvmppc_rm_h_page_init(काष्ठा kvm_vcpu *vcpu, अचिन्हित दीर्घ flags,
			   अचिन्हित दीर्घ dest, अचिन्हित दीर्घ src);
दीर्घ kvmppc_hpte_hv_fault(काष्ठा kvm_vcpu *vcpu, अचिन्हित दीर्घ addr,
                          अचिन्हित दीर्घ slb_v, अचिन्हित पूर्णांक status, bool data);
अचिन्हित दीर्घ kvmppc_rm_h_xirr(काष्ठा kvm_vcpu *vcpu);
अचिन्हित दीर्घ kvmppc_rm_h_xirr_x(काष्ठा kvm_vcpu *vcpu);
अचिन्हित दीर्घ kvmppc_rm_h_ipoll(काष्ठा kvm_vcpu *vcpu, अचिन्हित दीर्घ server);
पूर्णांक kvmppc_rm_h_ipi(काष्ठा kvm_vcpu *vcpu, अचिन्हित दीर्घ server,
                    अचिन्हित दीर्घ mfrr);
पूर्णांक kvmppc_rm_h_cppr(काष्ठा kvm_vcpu *vcpu, अचिन्हित दीर्घ cppr);
पूर्णांक kvmppc_rm_h_eoi(काष्ठा kvm_vcpu *vcpu, अचिन्हित दीर्घ xirr);
व्योम kvmppc_guest_entry_inject_पूर्णांक(काष्ठा kvm_vcpu *vcpu);

/*
 * Host-side operations we want to set up जबतक running in real
 * mode in the guest operating on the xics.
 * Currently only VCPU wakeup is supported.
 */

जोड़ kvmppc_rm_state अणु
	अचिन्हित दीर्घ raw;
	काष्ठा अणु
		u32 in_host;
		u32 rm_action;
	पूर्ण;
पूर्ण;

काष्ठा kvmppc_host_rm_core अणु
	जोड़ kvmppc_rm_state rm_state;
	व्योम *rm_data;
	अक्षर pad[112];
पूर्ण;

काष्ठा kvmppc_host_rm_ops अणु
	काष्ठा kvmppc_host_rm_core	*rm_core;
	व्योम		(*vcpu_kick)(काष्ठा kvm_vcpu *vcpu);
पूर्ण;

बाह्य काष्ठा kvmppc_host_rm_ops *kvmppc_host_rm_ops_hv;

अटल अंतरभूत अचिन्हित दीर्घ kvmppc_get_epr(काष्ठा kvm_vcpu *vcpu)
अणु
#अगर_घोषित CONFIG_KVM_BOOKE_HV
	वापस mfspr(SPRN_GEPR);
#या_अगर defined(CONFIG_BOOKE)
	वापस vcpu->arch.epr;
#अन्यथा
	वापस 0;
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत व्योम kvmppc_set_epr(काष्ठा kvm_vcpu *vcpu, u32 epr)
अणु
#अगर_घोषित CONFIG_KVM_BOOKE_HV
	mtspr(SPRN_GEPR, epr);
#या_अगर defined(CONFIG_BOOKE)
	vcpu->arch.epr = epr;
#पूर्ण_अगर
पूर्ण

#अगर_घोषित CONFIG_KVM_MPIC

व्योम kvmppc_mpic_set_epr(काष्ठा kvm_vcpu *vcpu);
पूर्णांक kvmppc_mpic_connect_vcpu(काष्ठा kvm_device *dev, काष्ठा kvm_vcpu *vcpu,
			     u32 cpu);
व्योम kvmppc_mpic_disconnect_vcpu(काष्ठा खोलोpic *opp, काष्ठा kvm_vcpu *vcpu);

#अन्यथा

अटल अंतरभूत व्योम kvmppc_mpic_set_epr(काष्ठा kvm_vcpu *vcpu)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक kvmppc_mpic_connect_vcpu(काष्ठा kvm_device *dev,
		काष्ठा kvm_vcpu *vcpu, u32 cpu)
अणु
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत व्योम kvmppc_mpic_disconnect_vcpu(काष्ठा खोलोpic *opp,
		काष्ठा kvm_vcpu *vcpu)
अणु
पूर्ण

#पूर्ण_अगर /* CONFIG_KVM_MPIC */

पूर्णांक kvm_vcpu_ioctl_config_tlb(काष्ठा kvm_vcpu *vcpu,
			      काष्ठा kvm_config_tlb *cfg);
पूर्णांक kvm_vcpu_ioctl_dirty_tlb(काष्ठा kvm_vcpu *vcpu,
			     काष्ठा kvm_dirty_tlb *cfg);

दीर्घ kvmppc_alloc_lpid(व्योम);
व्योम kvmppc_claim_lpid(दीर्घ lpid);
व्योम kvmppc_मुक्त_lpid(दीर्घ lpid);
व्योम kvmppc_init_lpid(अचिन्हित दीर्घ nr_lpids);

अटल अंतरभूत व्योम kvmppc_mmu_flush_icache(kvm_pfn_t pfn)
अणु
	काष्ठा page *page;
	/*
	 * We can only access pages that the kernel maps
	 * as memory. Bail out क्रम unmapped ones.
	 */
	अगर (!pfn_valid(pfn))
		वापस;

	/* Clear i-cache क्रम new pages */
	page = pfn_to_page(pfn);
	अगर (!test_bit(PG_dcache_clean, &page->flags)) अणु
		flush_dcache_icache_page(page);
		set_bit(PG_dcache_clean, &page->flags);
	पूर्ण
पूर्ण

/*
 * Shared काष्ठा helpers. The shared काष्ठा can be little or big endian,
 * depending on the guest endianness. So expose helpers to all of them.
 */
अटल अंतरभूत bool kvmppc_shared_big_endian(काष्ठा kvm_vcpu *vcpu)
अणु
#अगर defined(CONFIG_PPC_BOOK3S_64) && defined(CONFIG_KVM_BOOK3S_PR_POSSIBLE)
	/* Only Book3S_64 PR supports bi-endian क्रम now */
	वापस vcpu->arch.shared_big_endian;
#या_अगर defined(CONFIG_PPC_BOOK3S_64) && defined(__LITTLE_ENDIAN__)
	/* Book3s_64 HV on little endian is always little endian */
	वापस false;
#अन्यथा
	वापस true;
#पूर्ण_अगर
पूर्ण

#घोषणा SPRNG_WRAPPER_GET(reg, bookehv_spr)				\
अटल अंतरभूत uदीर्घ kvmppc_get_##reg(काष्ठा kvm_vcpu *vcpu)		\
अणु									\
	वापस mfspr(bookehv_spr);					\
पूर्ण									\

#घोषणा SPRNG_WRAPPER_SET(reg, bookehv_spr)				\
अटल अंतरभूत व्योम kvmppc_set_##reg(काष्ठा kvm_vcpu *vcpu, uदीर्घ val)	\
अणु									\
	mtspr(bookehv_spr, val);						\
पूर्ण									\

#घोषणा SHARED_WRAPPER_GET(reg, size)					\
अटल अंतरभूत u##size kvmppc_get_##reg(काष्ठा kvm_vcpu *vcpu)		\
अणु									\
	अगर (kvmppc_shared_big_endian(vcpu))				\
	       वापस be##size##_to_cpu(vcpu->arch.shared->reg);	\
	अन्यथा								\
	       वापस le##size##_to_cpu(vcpu->arch.shared->reg);	\
पूर्ण									\

#घोषणा SHARED_WRAPPER_SET(reg, size)					\
अटल अंतरभूत व्योम kvmppc_set_##reg(काष्ठा kvm_vcpu *vcpu, u##size val)	\
अणु									\
	अगर (kvmppc_shared_big_endian(vcpu))				\
	       vcpu->arch.shared->reg = cpu_to_be##size(val);		\
	अन्यथा								\
	       vcpu->arch.shared->reg = cpu_to_le##size(val);		\
पूर्ण									\

#घोषणा SHARED_WRAPPER(reg, size)					\
	SHARED_WRAPPER_GET(reg, size)					\
	SHARED_WRAPPER_SET(reg, size)					\

#घोषणा SPRNG_WRAPPER(reg, bookehv_spr)					\
	SPRNG_WRAPPER_GET(reg, bookehv_spr)				\
	SPRNG_WRAPPER_SET(reg, bookehv_spr)				\

#अगर_घोषित CONFIG_KVM_BOOKE_HV

#घोषणा SHARED_SPRNG_WRAPPER(reg, size, bookehv_spr)			\
	SPRNG_WRAPPER(reg, bookehv_spr)					\

#अन्यथा

#घोषणा SHARED_SPRNG_WRAPPER(reg, size, bookehv_spr)			\
	SHARED_WRAPPER(reg, size)					\

#पूर्ण_अगर

SHARED_WRAPPER(critical, 64)
SHARED_SPRNG_WRAPPER(sprg0, 64, SPRN_GSPRG0)
SHARED_SPRNG_WRAPPER(sprg1, 64, SPRN_GSPRG1)
SHARED_SPRNG_WRAPPER(sprg2, 64, SPRN_GSPRG2)
SHARED_SPRNG_WRAPPER(sprg3, 64, SPRN_GSPRG3)
SHARED_SPRNG_WRAPPER(srr0, 64, SPRN_GSRR0)
SHARED_SPRNG_WRAPPER(srr1, 64, SPRN_GSRR1)
SHARED_SPRNG_WRAPPER(dar, 64, SPRN_GDEAR)
SHARED_SPRNG_WRAPPER(esr, 64, SPRN_GESR)
SHARED_WRAPPER_GET(msr, 64)
अटल अंतरभूत व्योम kvmppc_set_msr_fast(काष्ठा kvm_vcpu *vcpu, u64 val)
अणु
	अगर (kvmppc_shared_big_endian(vcpu))
	       vcpu->arch.shared->msr = cpu_to_be64(val);
	अन्यथा
	       vcpu->arch.shared->msr = cpu_to_le64(val);
पूर्ण
SHARED_WRAPPER(dsisr, 32)
SHARED_WRAPPER(पूर्णांक_pending, 32)
SHARED_WRAPPER(sprg4, 64)
SHARED_WRAPPER(sprg5, 64)
SHARED_WRAPPER(sprg6, 64)
SHARED_WRAPPER(sprg7, 64)

अटल अंतरभूत u32 kvmppc_get_sr(काष्ठा kvm_vcpu *vcpu, पूर्णांक nr)
अणु
	अगर (kvmppc_shared_big_endian(vcpu))
	       वापस be32_to_cpu(vcpu->arch.shared->sr[nr]);
	अन्यथा
	       वापस le32_to_cpu(vcpu->arch.shared->sr[nr]);
पूर्ण

अटल अंतरभूत व्योम kvmppc_set_sr(काष्ठा kvm_vcpu *vcpu, पूर्णांक nr, u32 val)
अणु
	अगर (kvmppc_shared_big_endian(vcpu))
	       vcpu->arch.shared->sr[nr] = cpu_to_be32(val);
	अन्यथा
	       vcpu->arch.shared->sr[nr] = cpu_to_le32(val);
पूर्ण

/*
 * Please call after prepare_to_enter. This function माला_दो the lazy ee and irq
 * disabled tracking state back to normal mode, without actually enabling
 * पूर्णांकerrupts.
 */
अटल अंतरभूत व्योम kvmppc_fix_ee_beक्रमe_entry(व्योम)
अणु
	trace_hardirqs_on();

#अगर_घोषित CONFIG_PPC64
	/*
	 * To aव्योम races, the caller must have gone directly from having
	 * पूर्णांकerrupts fully-enabled to hard-disabled.
	 */
	WARN_ON(local_paca->irq_happened != PACA_IRQ_HARD_DIS);

	/* Only need to enable IRQs by hard enabling them after this */
	local_paca->irq_happened = 0;
	irq_soft_mask_set(IRQS_ENABLED);
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत uदीर्घ kvmppc_get_ea_indexed(काष्ठा kvm_vcpu *vcpu, पूर्णांक ra, पूर्णांक rb)
अणु
	uदीर्घ ea;
	uदीर्घ msr_64bit = 0;

	ea = kvmppc_get_gpr(vcpu, rb);
	अगर (ra)
		ea += kvmppc_get_gpr(vcpu, ra);

#अगर defined(CONFIG_PPC_BOOK3E_64)
	msr_64bit = MSR_CM;
#या_अगर defined(CONFIG_PPC_BOOK3S_64)
	msr_64bit = MSR_SF;
#पूर्ण_अगर

	अगर (!(kvmppc_get_msr(vcpu) & msr_64bit))
		ea = (uपूर्णांक32_t)ea;

	वापस ea;
पूर्ण

बाह्य व्योम xics_wake_cpu(पूर्णांक cpu);

#पूर्ण_अगर /* __POWERPC_KVM_PPC_H__ */
