<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2011. Freescale Inc. All rights reserved.
 *
 * Authors:
 *    Alexander Graf <agraf@suse.de>
 *    Paul Mackerras <paulus@samba.org>
 *
 * Description:
 *
 * Hypercall handling क्रम running PAPR guests in PR KVM on Book 3S
 * processors.
 */

#समावेश <linux/anon_inodes.h>

#समावेश <linux/uaccess.h>
#समावेश <यंत्र/kvm_ppc.h>
#समावेश <यंत्र/kvm_book3s.h>

#घोषणा HPTE_SIZE	16		/* bytes per HPT entry */

अटल अचिन्हित दीर्घ get_pteg_addr(काष्ठा kvm_vcpu *vcpu, दीर्घ pte_index)
अणु
	काष्ठा kvmppc_vcpu_book3s *vcpu_book3s = to_book3s(vcpu);
	अचिन्हित दीर्घ pteg_addr;

	pte_index <<= 4;
	pte_index &= ((1 << ((vcpu_book3s->sdr1 & 0x1f) + 11)) - 1) << 7 | 0x70;
	pteg_addr = vcpu_book3s->sdr1 & 0xfffffffffffc0000ULL;
	pteg_addr |= pte_index;

	वापस pteg_addr;
पूर्ण

अटल पूर्णांक kvmppc_h_pr_enter(काष्ठा kvm_vcpu *vcpu)
अणु
	दीर्घ flags = kvmppc_get_gpr(vcpu, 4);
	दीर्घ pte_index = kvmppc_get_gpr(vcpu, 5);
	__be64 pteg[2 * 8];
	__be64 *hpte;
	अचिन्हित दीर्घ pteg_addr, i;
	दीर्घ पूर्णांक ret;

	i = pte_index & 7;
	pte_index &= ~7UL;
	pteg_addr = get_pteg_addr(vcpu, pte_index);

	mutex_lock(&vcpu->kvm->arch.hpt_mutex);
	ret = H_FUNCTION;
	अगर (copy_from_user(pteg, (व्योम __user *)pteg_addr, माप(pteg)))
		जाओ करोne;
	hpte = pteg;

	ret = H_PTEG_FULL;
	अगर (likely((flags & H_EXACT) == 0)) अणु
		क्रम (i = 0; ; ++i) अणु
			अगर (i == 8)
				जाओ करोne;
			अगर ((be64_to_cpu(*hpte) & HPTE_V_VALID) == 0)
				अवरोध;
			hpte += 2;
		पूर्ण
	पूर्ण अन्यथा अणु
		hpte += i * 2;
		अगर (*hpte & HPTE_V_VALID)
			जाओ करोne;
	पूर्ण

	hpte[0] = cpu_to_be64(kvmppc_get_gpr(vcpu, 6));
	hpte[1] = cpu_to_be64(kvmppc_get_gpr(vcpu, 7));
	pteg_addr += i * HPTE_SIZE;
	ret = H_FUNCTION;
	अगर (copy_to_user((व्योम __user *)pteg_addr, hpte, HPTE_SIZE))
		जाओ करोne;
	kvmppc_set_gpr(vcpu, 4, pte_index | i);
	ret = H_SUCCESS;

 करोne:
	mutex_unlock(&vcpu->kvm->arch.hpt_mutex);
	kvmppc_set_gpr(vcpu, 3, ret);

	वापस EMULATE_DONE;
पूर्ण

अटल पूर्णांक kvmppc_h_pr_हटाओ(काष्ठा kvm_vcpu *vcpu)
अणु
	अचिन्हित दीर्घ flags= kvmppc_get_gpr(vcpu, 4);
	अचिन्हित दीर्घ pte_index = kvmppc_get_gpr(vcpu, 5);
	अचिन्हित दीर्घ avpn = kvmppc_get_gpr(vcpu, 6);
	अचिन्हित दीर्घ v = 0, pteg, rb;
	अचिन्हित दीर्घ pte[2];
	दीर्घ पूर्णांक ret;

	pteg = get_pteg_addr(vcpu, pte_index);
	mutex_lock(&vcpu->kvm->arch.hpt_mutex);
	ret = H_FUNCTION;
	अगर (copy_from_user(pte, (व्योम __user *)pteg, माप(pte)))
		जाओ करोne;
	pte[0] = be64_to_cpu((__क्रमce __be64)pte[0]);
	pte[1] = be64_to_cpu((__क्रमce __be64)pte[1]);

	ret = H_NOT_FOUND;
	अगर ((pte[0] & HPTE_V_VALID) == 0 ||
	    ((flags & H_AVPN) && (pte[0] & ~0x7fUL) != avpn) ||
	    ((flags & H_ANDCOND) && (pte[0] & avpn) != 0))
		जाओ करोne;

	ret = H_FUNCTION;
	अगर (copy_to_user((व्योम __user *)pteg, &v, माप(v)))
		जाओ करोne;

	rb = compute_tlbie_rb(pte[0], pte[1], pte_index);
	vcpu->arch.mmu.tlbie(vcpu, rb, rb & 1 ? true : false);

	ret = H_SUCCESS;
	kvmppc_set_gpr(vcpu, 4, pte[0]);
	kvmppc_set_gpr(vcpu, 5, pte[1]);

 करोne:
	mutex_unlock(&vcpu->kvm->arch.hpt_mutex);
	kvmppc_set_gpr(vcpu, 3, ret);

	वापस EMULATE_DONE;
पूर्ण

/* Request defs क्रम kvmppc_h_pr_bulk_हटाओ() */
#घोषणा H_BULK_REMOVE_TYPE             0xc000000000000000ULL
#घोषणा   H_BULK_REMOVE_REQUEST        0x4000000000000000ULL
#घोषणा   H_BULK_REMOVE_RESPONSE       0x8000000000000000ULL
#घोषणा   H_BULK_REMOVE_END            0xc000000000000000ULL
#घोषणा H_BULK_REMOVE_CODE             0x3000000000000000ULL
#घोषणा   H_BULK_REMOVE_SUCCESS        0x0000000000000000ULL
#घोषणा   H_BULK_REMOVE_NOT_FOUND      0x1000000000000000ULL
#घोषणा   H_BULK_REMOVE_PARM           0x2000000000000000ULL
#घोषणा   H_BULK_REMOVE_HW             0x3000000000000000ULL
#घोषणा H_BULK_REMOVE_RC               0x0c00000000000000ULL
#घोषणा H_BULK_REMOVE_FLAGS            0x0300000000000000ULL
#घोषणा   H_BULK_REMOVE_ABSOLUTE       0x0000000000000000ULL
#घोषणा   H_BULK_REMOVE_ANDCOND        0x0100000000000000ULL
#घोषणा   H_BULK_REMOVE_AVPN           0x0200000000000000ULL
#घोषणा H_BULK_REMOVE_PTEX             0x00ffffffffffffffULL
#घोषणा H_BULK_REMOVE_MAX_BATCH        4

अटल पूर्णांक kvmppc_h_pr_bulk_हटाओ(काष्ठा kvm_vcpu *vcpu)
अणु
	पूर्णांक i;
	पूर्णांक paramnr = 4;
	पूर्णांक ret = H_SUCCESS;

	mutex_lock(&vcpu->kvm->arch.hpt_mutex);
	क्रम (i = 0; i < H_BULK_REMOVE_MAX_BATCH; i++) अणु
		अचिन्हित दीर्घ tsh = kvmppc_get_gpr(vcpu, paramnr+(2*i));
		अचिन्हित दीर्घ tsl = kvmppc_get_gpr(vcpu, paramnr+(2*i)+1);
		अचिन्हित दीर्घ pteg, rb, flags;
		अचिन्हित दीर्घ pte[2];
		अचिन्हित दीर्घ v = 0;

		अगर ((tsh & H_BULK_REMOVE_TYPE) == H_BULK_REMOVE_END) अणु
			अवरोध; /* Exit success */
		पूर्ण अन्यथा अगर ((tsh & H_BULK_REMOVE_TYPE) !=
			   H_BULK_REMOVE_REQUEST) अणु
			ret = H_PARAMETER;
			अवरोध; /* Exit fail */
		पूर्ण

		tsh &= H_BULK_REMOVE_PTEX | H_BULK_REMOVE_FLAGS;
		tsh |= H_BULK_REMOVE_RESPONSE;

		अगर ((tsh & H_BULK_REMOVE_ANDCOND) &&
		    (tsh & H_BULK_REMOVE_AVPN)) अणु
			tsh |= H_BULK_REMOVE_PARM;
			kvmppc_set_gpr(vcpu, paramnr+(2*i), tsh);
			ret = H_PARAMETER;
			अवरोध; /* Exit fail */
		पूर्ण

		pteg = get_pteg_addr(vcpu, tsh & H_BULK_REMOVE_PTEX);
		अगर (copy_from_user(pte, (व्योम __user *)pteg, माप(pte))) अणु
			ret = H_FUNCTION;
			अवरोध;
		पूर्ण
		pte[0] = be64_to_cpu((__क्रमce __be64)pte[0]);
		pte[1] = be64_to_cpu((__क्रमce __be64)pte[1]);

		/* tsl = AVPN */
		flags = (tsh & H_BULK_REMOVE_FLAGS) >> 26;

		अगर ((pte[0] & HPTE_V_VALID) == 0 ||
		    ((flags & H_AVPN) && (pte[0] & ~0x7fUL) != tsl) ||
		    ((flags & H_ANDCOND) && (pte[0] & tsl) != 0)) अणु
			tsh |= H_BULK_REMOVE_NOT_FOUND;
		पूर्ण अन्यथा अणु
			/* Splat the pteg in (userland) hpt */
			अगर (copy_to_user((व्योम __user *)pteg, &v, माप(v))) अणु
				ret = H_FUNCTION;
				अवरोध;
			पूर्ण

			rb = compute_tlbie_rb(pte[0], pte[1],
					      tsh & H_BULK_REMOVE_PTEX);
			vcpu->arch.mmu.tlbie(vcpu, rb, rb & 1 ? true : false);
			tsh |= H_BULK_REMOVE_SUCCESS;
			tsh |= (pte[1] & (HPTE_R_C | HPTE_R_R)) << 43;
		पूर्ण
		kvmppc_set_gpr(vcpu, paramnr+(2*i), tsh);
	पूर्ण
	mutex_unlock(&vcpu->kvm->arch.hpt_mutex);
	kvmppc_set_gpr(vcpu, 3, ret);

	वापस EMULATE_DONE;
पूर्ण

अटल पूर्णांक kvmppc_h_pr_protect(काष्ठा kvm_vcpu *vcpu)
अणु
	अचिन्हित दीर्घ flags = kvmppc_get_gpr(vcpu, 4);
	अचिन्हित दीर्घ pte_index = kvmppc_get_gpr(vcpu, 5);
	अचिन्हित दीर्घ avpn = kvmppc_get_gpr(vcpu, 6);
	अचिन्हित दीर्घ rb, pteg, r, v;
	अचिन्हित दीर्घ pte[2];
	दीर्घ पूर्णांक ret;

	pteg = get_pteg_addr(vcpu, pte_index);
	mutex_lock(&vcpu->kvm->arch.hpt_mutex);
	ret = H_FUNCTION;
	अगर (copy_from_user(pte, (व्योम __user *)pteg, माप(pte)))
		जाओ करोne;
	pte[0] = be64_to_cpu((__क्रमce __be64)pte[0]);
	pte[1] = be64_to_cpu((__क्रमce __be64)pte[1]);

	ret = H_NOT_FOUND;
	अगर ((pte[0] & HPTE_V_VALID) == 0 ||
	    ((flags & H_AVPN) && (pte[0] & ~0x7fUL) != avpn))
		जाओ करोne;

	v = pte[0];
	r = pte[1];
	r &= ~(HPTE_R_PP0 | HPTE_R_PP | HPTE_R_N | HPTE_R_KEY_HI |
	       HPTE_R_KEY_LO);
	r |= (flags << 55) & HPTE_R_PP0;
	r |= (flags << 48) & HPTE_R_KEY_HI;
	r |= flags & (HPTE_R_PP | HPTE_R_N | HPTE_R_KEY_LO);

	pte[1] = r;

	rb = compute_tlbie_rb(v, r, pte_index);
	vcpu->arch.mmu.tlbie(vcpu, rb, rb & 1 ? true : false);
	pte[0] = (__क्रमce u64)cpu_to_be64(pte[0]);
	pte[1] = (__क्रमce u64)cpu_to_be64(pte[1]);
	ret = H_FUNCTION;
	अगर (copy_to_user((व्योम __user *)pteg, pte, माप(pte)))
		जाओ करोne;
	ret = H_SUCCESS;

 करोne:
	mutex_unlock(&vcpu->kvm->arch.hpt_mutex);
	kvmppc_set_gpr(vcpu, 3, ret);

	वापस EMULATE_DONE;
पूर्ण

अटल पूर्णांक kvmppc_h_pr_logical_ci_load(काष्ठा kvm_vcpu *vcpu)
अणु
	दीर्घ rc;

	rc = kvmppc_h_logical_ci_load(vcpu);
	अगर (rc == H_TOO_HARD)
		वापस EMULATE_FAIL;
	kvmppc_set_gpr(vcpu, 3, rc);
	वापस EMULATE_DONE;
पूर्ण

अटल पूर्णांक kvmppc_h_pr_logical_ci_store(काष्ठा kvm_vcpu *vcpu)
अणु
	दीर्घ rc;

	rc = kvmppc_h_logical_ci_store(vcpu);
	अगर (rc == H_TOO_HARD)
		वापस EMULATE_FAIL;
	kvmppc_set_gpr(vcpu, 3, rc);
	वापस EMULATE_DONE;
पूर्ण

#अगर_घोषित CONFIG_SPAPR_TCE_IOMMU
अटल पूर्णांक kvmppc_h_pr_put_tce(काष्ठा kvm_vcpu *vcpu)
अणु
	अचिन्हित दीर्घ liobn = kvmppc_get_gpr(vcpu, 4);
	अचिन्हित दीर्घ ioba = kvmppc_get_gpr(vcpu, 5);
	अचिन्हित दीर्घ tce = kvmppc_get_gpr(vcpu, 6);
	दीर्घ rc;

	rc = kvmppc_h_put_tce(vcpu, liobn, ioba, tce);
	अगर (rc == H_TOO_HARD)
		वापस EMULATE_FAIL;
	kvmppc_set_gpr(vcpu, 3, rc);
	वापस EMULATE_DONE;
पूर्ण

अटल पूर्णांक kvmppc_h_pr_put_tce_indirect(काष्ठा kvm_vcpu *vcpu)
अणु
	अचिन्हित दीर्घ liobn = kvmppc_get_gpr(vcpu, 4);
	अचिन्हित दीर्घ ioba = kvmppc_get_gpr(vcpu, 5);
	अचिन्हित दीर्घ tce = kvmppc_get_gpr(vcpu, 6);
	अचिन्हित दीर्घ npages = kvmppc_get_gpr(vcpu, 7);
	दीर्घ rc;

	rc = kvmppc_h_put_tce_indirect(vcpu, liobn, ioba,
			tce, npages);
	अगर (rc == H_TOO_HARD)
		वापस EMULATE_FAIL;
	kvmppc_set_gpr(vcpu, 3, rc);
	वापस EMULATE_DONE;
पूर्ण

अटल पूर्णांक kvmppc_h_pr_stuff_tce(काष्ठा kvm_vcpu *vcpu)
अणु
	अचिन्हित दीर्घ liobn = kvmppc_get_gpr(vcpu, 4);
	अचिन्हित दीर्घ ioba = kvmppc_get_gpr(vcpu, 5);
	अचिन्हित दीर्घ tce_value = kvmppc_get_gpr(vcpu, 6);
	अचिन्हित दीर्घ npages = kvmppc_get_gpr(vcpu, 7);
	दीर्घ rc;

	rc = kvmppc_h_stuff_tce(vcpu, liobn, ioba, tce_value, npages);
	अगर (rc == H_TOO_HARD)
		वापस EMULATE_FAIL;
	kvmppc_set_gpr(vcpu, 3, rc);
	वापस EMULATE_DONE;
पूर्ण

#अन्यथा /* CONFIG_SPAPR_TCE_IOMMU */
अटल पूर्णांक kvmppc_h_pr_put_tce(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस EMULATE_FAIL;
पूर्ण

अटल पूर्णांक kvmppc_h_pr_put_tce_indirect(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस EMULATE_FAIL;
पूर्ण

अटल पूर्णांक kvmppc_h_pr_stuff_tce(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस EMULATE_FAIL;
पूर्ण
#पूर्ण_अगर /* CONFIG_SPAPR_TCE_IOMMU */

अटल पूर्णांक kvmppc_h_pr_xics_hcall(काष्ठा kvm_vcpu *vcpu, u32 cmd)
अणु
	दीर्घ rc = kvmppc_xics_hcall(vcpu, cmd);
	kvmppc_set_gpr(vcpu, 3, rc);
	वापस EMULATE_DONE;
पूर्ण

पूर्णांक kvmppc_h_pr(काष्ठा kvm_vcpu *vcpu, अचिन्हित दीर्घ cmd)
अणु
	पूर्णांक rc, idx;

	अगर (cmd <= MAX_HCALL_OPCODE &&
	    !test_bit(cmd/4, vcpu->kvm->arch.enabled_hcalls))
		वापस EMULATE_FAIL;

	चयन (cmd) अणु
	हाल H_ENTER:
		वापस kvmppc_h_pr_enter(vcpu);
	हाल H_REMOVE:
		वापस kvmppc_h_pr_हटाओ(vcpu);
	हाल H_PROTECT:
		वापस kvmppc_h_pr_protect(vcpu);
	हाल H_BULK_REMOVE:
		वापस kvmppc_h_pr_bulk_हटाओ(vcpu);
	हाल H_PUT_TCE:
		वापस kvmppc_h_pr_put_tce(vcpu);
	हाल H_PUT_TCE_INसूचीECT:
		वापस kvmppc_h_pr_put_tce_indirect(vcpu);
	हाल H_STUFF_TCE:
		वापस kvmppc_h_pr_stuff_tce(vcpu);
	हाल H_CEDE:
		kvmppc_set_msr_fast(vcpu, kvmppc_get_msr(vcpu) | MSR_EE);
		kvm_vcpu_block(vcpu);
		kvm_clear_request(KVM_REQ_UNHALT, vcpu);
		vcpu->स्थिति.सalt_wakeup++;
		वापस EMULATE_DONE;
	हाल H_LOGICAL_CI_LOAD:
		वापस kvmppc_h_pr_logical_ci_load(vcpu);
	हाल H_LOGICAL_CI_STORE:
		वापस kvmppc_h_pr_logical_ci_store(vcpu);
	हाल H_XIRR:
	हाल H_CPPR:
	हाल H_EOI:
	हाल H_IPI:
	हाल H_IPOLL:
	हाल H_XIRR_X:
		अगर (kvmppc_xics_enabled(vcpu))
			वापस kvmppc_h_pr_xics_hcall(vcpu, cmd);
		अवरोध;
	हाल H_RTAS:
		अगर (list_empty(&vcpu->kvm->arch.rtas_tokens))
			अवरोध;
		idx = srcu_पढ़ो_lock(&vcpu->kvm->srcu);
		rc = kvmppc_rtas_hcall(vcpu);
		srcu_पढ़ो_unlock(&vcpu->kvm->srcu, idx);
		अगर (rc)
			अवरोध;
		kvmppc_set_gpr(vcpu, 3, 0);
		वापस EMULATE_DONE;
	पूर्ण

	वापस EMULATE_FAIL;
पूर्ण

पूर्णांक kvmppc_hcall_impl_pr(अचिन्हित दीर्घ cmd)
अणु
	चयन (cmd) अणु
	हाल H_ENTER:
	हाल H_REMOVE:
	हाल H_PROTECT:
	हाल H_BULK_REMOVE:
	हाल H_PUT_TCE:
	हाल H_PUT_TCE_INसूचीECT:
	हाल H_STUFF_TCE:
	हाल H_CEDE:
	हाल H_LOGICAL_CI_LOAD:
	हाल H_LOGICAL_CI_STORE:
#अगर_घोषित CONFIG_KVM_XICS
	हाल H_XIRR:
	हाल H_CPPR:
	हाल H_EOI:
	हाल H_IPI:
	हाल H_IPOLL:
	हाल H_XIRR_X:
#पूर्ण_अगर
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * List of hcall numbers to enable by शेष.
 * For compatibility with old userspace, we enable by शेष
 * all hcalls that were implemented beक्रमe the hcall-enabling
 * facility was added.  Note this list should not include H_RTAS.
 */
अटल अचिन्हित पूर्णांक शेष_hcall_list[] = अणु
	H_ENTER,
	H_REMOVE,
	H_PROTECT,
	H_BULK_REMOVE,
	H_PUT_TCE,
	H_CEDE,
#अगर_घोषित CONFIG_KVM_XICS
	H_XIRR,
	H_CPPR,
	H_EOI,
	H_IPI,
	H_IPOLL,
	H_XIRR_X,
#पूर्ण_अगर
	0
पूर्ण;

व्योम kvmppc_pr_init_शेष_hcalls(काष्ठा kvm *kvm)
अणु
	पूर्णांक i;
	अचिन्हित पूर्णांक hcall;

	क्रम (i = 0; शेष_hcall_list[i]; ++i) अणु
		hcall = शेष_hcall_list[i];
		WARN_ON(!kvmppc_hcall_impl_pr(hcall));
		__set_bit(hcall / 4, kvm->arch.enabled_hcalls);
	पूर्ण
पूर्ण
