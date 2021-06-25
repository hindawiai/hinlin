<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * mmu_audit.c:
 *
 * Audit code क्रम KVM MMU
 *
 * Copyright (C) 2006 Qumranet, Inc.
 * Copyright 2010 Red Hat, Inc. and/or its affiliates.
 *
 * Authors:
 *   Yaniv Kamay  <yaniv@qumranet.com>
 *   Avi Kivity   <avi@qumranet.com>
 *   Marcelo Tosatti <mtosatti@redhat.com>
 *   Xiao Guangrong <xiaoguangrong@cn.fujitsu.com>
 */

#समावेश <linux/ratelimit.h>

अटल अक्षर स्थिर *audit_poपूर्णांक_name[] = अणु
	"pre page fault",
	"post page fault",
	"pre pte write",
	"post pte write",
	"pre sync",
	"post sync"
पूर्ण;

#घोषणा audit_prपूर्णांकk(kvm, fmt, args...)		\
	prपूर्णांकk(KERN_ERR "audit: (%s) error: "	\
		fmt, audit_poपूर्णांक_name[kvm->arch.audit_poपूर्णांक], ##args)

प्रकार व्योम (*inspect_spte_fn) (काष्ठा kvm_vcpu *vcpu, u64 *sptep, पूर्णांक level);

अटल व्योम __mmu_spte_walk(काष्ठा kvm_vcpu *vcpu, काष्ठा kvm_mmu_page *sp,
			    inspect_spte_fn fn, पूर्णांक level)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < PT64_ENT_PER_PAGE; ++i) अणु
		u64 *ent = sp->spt;

		fn(vcpu, ent + i, level);

		अगर (is_shaकरोw_present_pte(ent[i]) &&
		      !is_last_spte(ent[i], level)) अणु
			काष्ठा kvm_mmu_page *child;

			child = to_shaकरोw_page(ent[i] & PT64_BASE_ADDR_MASK);
			__mmu_spte_walk(vcpu, child, fn, level - 1);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम mmu_spte_walk(काष्ठा kvm_vcpu *vcpu, inspect_spte_fn fn)
अणु
	पूर्णांक i;
	काष्ठा kvm_mmu_page *sp;

	अगर (!VALID_PAGE(vcpu->arch.mmu->root_hpa))
		वापस;

	अगर (vcpu->arch.mmu->root_level >= PT64_ROOT_4LEVEL) अणु
		hpa_t root = vcpu->arch.mmu->root_hpa;

		sp = to_shaकरोw_page(root);
		__mmu_spte_walk(vcpu, sp, fn, vcpu->arch.mmu->root_level);
		वापस;
	पूर्ण

	क्रम (i = 0; i < 4; ++i) अणु
		hpa_t root = vcpu->arch.mmu->pae_root[i];

		अगर (IS_VALID_PAE_ROOT(root)) अणु
			root &= PT64_BASE_ADDR_MASK;
			sp = to_shaकरोw_page(root);
			__mmu_spte_walk(vcpu, sp, fn, 2);
		पूर्ण
	पूर्ण

	वापस;
पूर्ण

प्रकार व्योम (*sp_handler) (काष्ठा kvm *kvm, काष्ठा kvm_mmu_page *sp);

अटल व्योम walk_all_active_sps(काष्ठा kvm *kvm, sp_handler fn)
अणु
	काष्ठा kvm_mmu_page *sp;

	list_क्रम_each_entry(sp, &kvm->arch.active_mmu_pages, link)
		fn(kvm, sp);
पूर्ण

अटल व्योम audit_mappings(काष्ठा kvm_vcpu *vcpu, u64 *sptep, पूर्णांक level)
अणु
	काष्ठा kvm_mmu_page *sp;
	gfn_t gfn;
	kvm_pfn_t pfn;
	hpa_t hpa;

	sp = sptep_to_sp(sptep);

	अगर (sp->unsync) अणु
		अगर (level != PG_LEVEL_4K) अणु
			audit_prपूर्णांकk(vcpu->kvm, "unsync sp: %p "
				     "level = %d\n", sp, level);
			वापस;
		पूर्ण
	पूर्ण

	अगर (!is_shaकरोw_present_pte(*sptep) || !is_last_spte(*sptep, level))
		वापस;

	gfn = kvm_mmu_page_get_gfn(sp, sptep - sp->spt);
	pfn = kvm_vcpu_gfn_to_pfn_atomic(vcpu, gfn);

	अगर (is_error_pfn(pfn))
		वापस;

	hpa =  pfn << PAGE_SHIFT;
	अगर ((*sptep & PT64_BASE_ADDR_MASK) != hpa)
		audit_prपूर्णांकk(vcpu->kvm, "levels %d pfn %llx hpa %llx "
			     "ent %llxn", vcpu->arch.mmu->root_level, pfn,
			     hpa, *sptep);
पूर्ण

अटल व्योम inspect_spte_has_rmap(काष्ठा kvm *kvm, u64 *sptep)
अणु
	अटल DEFINE_RATELIMIT_STATE(ratelimit_state, 5 * HZ, 10);
	काष्ठा kvm_rmap_head *rmap_head;
	काष्ठा kvm_mmu_page *rev_sp;
	काष्ठा kvm_memslots *slots;
	काष्ठा kvm_memory_slot *slot;
	gfn_t gfn;

	rev_sp = sptep_to_sp(sptep);
	gfn = kvm_mmu_page_get_gfn(rev_sp, sptep - rev_sp->spt);

	slots = kvm_memslots_क्रम_spte_role(kvm, rev_sp->role);
	slot = __gfn_to_memslot(slots, gfn);
	अगर (!slot) अणु
		अगर (!__ratelimit(&ratelimit_state))
			वापस;
		audit_prपूर्णांकk(kvm, "no memslot for gfn %llx\n", gfn);
		audit_prपूर्णांकk(kvm, "index %ld of sp (gfn=%llx)\n",
		       (दीर्घ पूर्णांक)(sptep - rev_sp->spt), rev_sp->gfn);
		dump_stack();
		वापस;
	पूर्ण

	rmap_head = __gfn_to_rmap(gfn, rev_sp->role.level, slot);
	अगर (!rmap_head->val) अणु
		अगर (!__ratelimit(&ratelimit_state))
			वापस;
		audit_prपूर्णांकk(kvm, "no rmap for writable spte %llx\n",
			     *sptep);
		dump_stack();
	पूर्ण
पूर्ण

अटल व्योम audit_sptes_have_rmaps(काष्ठा kvm_vcpu *vcpu, u64 *sptep, पूर्णांक level)
अणु
	अगर (is_shaकरोw_present_pte(*sptep) && is_last_spte(*sptep, level))
		inspect_spte_has_rmap(vcpu->kvm, sptep);
पूर्ण

अटल व्योम audit_spte_after_sync(काष्ठा kvm_vcpu *vcpu, u64 *sptep, पूर्णांक level)
अणु
	काष्ठा kvm_mmu_page *sp = sptep_to_sp(sptep);

	अगर (vcpu->kvm->arch.audit_poपूर्णांक == AUDIT_POST_SYNC && sp->unsync)
		audit_prपूर्णांकk(vcpu->kvm, "meet unsync sp(%p) after sync "
			     "root.\n", sp);
पूर्ण

अटल व्योम check_mappings_rmap(काष्ठा kvm *kvm, काष्ठा kvm_mmu_page *sp)
अणु
	पूर्णांक i;

	अगर (sp->role.level != PG_LEVEL_4K)
		वापस;

	क्रम (i = 0; i < PT64_ENT_PER_PAGE; ++i) अणु
		अगर (!is_shaकरोw_present_pte(sp->spt[i]))
			जारी;

		inspect_spte_has_rmap(kvm, sp->spt + i);
	पूर्ण
पूर्ण

अटल व्योम audit_ग_लिखो_protection(काष्ठा kvm *kvm, काष्ठा kvm_mmu_page *sp)
अणु
	काष्ठा kvm_rmap_head *rmap_head;
	u64 *sptep;
	काष्ठा rmap_iterator iter;
	काष्ठा kvm_memslots *slots;
	काष्ठा kvm_memory_slot *slot;

	अगर (sp->role.direct || sp->unsync || sp->role.invalid)
		वापस;

	slots = kvm_memslots_क्रम_spte_role(kvm, sp->role);
	slot = __gfn_to_memslot(slots, sp->gfn);
	rmap_head = __gfn_to_rmap(sp->gfn, PG_LEVEL_4K, slot);

	क्रम_each_rmap_spte(rmap_head, &iter, sptep) अणु
		अगर (is_writable_pte(*sptep))
			audit_prपूर्णांकk(kvm, "shadow page has writable "
				     "mappings: gfn %llx role %x\n",
				     sp->gfn, sp->role.word);
	पूर्ण
पूर्ण

अटल व्योम audit_sp(काष्ठा kvm *kvm, काष्ठा kvm_mmu_page *sp)
अणु
	check_mappings_rmap(kvm, sp);
	audit_ग_लिखो_protection(kvm, sp);
पूर्ण

अटल व्योम audit_all_active_sps(काष्ठा kvm *kvm)
अणु
	walk_all_active_sps(kvm, audit_sp);
पूर्ण

अटल व्योम audit_spte(काष्ठा kvm_vcpu *vcpu, u64 *sptep, पूर्णांक level)
अणु
	audit_sptes_have_rmaps(vcpu, sptep, level);
	audit_mappings(vcpu, sptep, level);
	audit_spte_after_sync(vcpu, sptep, level);
पूर्ण

अटल व्योम audit_vcpu_spte(काष्ठा kvm_vcpu *vcpu)
अणु
	mmu_spte_walk(vcpu, audit_spte);
पूर्ण

अटल bool mmu_audit;
अटल DEFINE_STATIC_KEY_FALSE(mmu_audit_key);

अटल व्योम __kvm_mmu_audit(काष्ठा kvm_vcpu *vcpu, पूर्णांक poपूर्णांक)
अणु
	अटल DEFINE_RATELIMIT_STATE(ratelimit_state, 5 * HZ, 10);

	अगर (!__ratelimit(&ratelimit_state))
		वापस;

	vcpu->kvm->arch.audit_poपूर्णांक = poपूर्णांक;
	audit_all_active_sps(vcpu->kvm);
	audit_vcpu_spte(vcpu);
पूर्ण

अटल अंतरभूत व्योम kvm_mmu_audit(काष्ठा kvm_vcpu *vcpu, पूर्णांक poपूर्णांक)
अणु
	अगर (अटल_branch_unlikely((&mmu_audit_key)))
		__kvm_mmu_audit(vcpu, poपूर्णांक);
पूर्ण

अटल व्योम mmu_audit_enable(व्योम)
अणु
	अगर (mmu_audit)
		वापस;

	अटल_branch_inc(&mmu_audit_key);
	mmu_audit = true;
पूर्ण

अटल व्योम mmu_audit_disable(व्योम)
अणु
	अगर (!mmu_audit)
		वापस;

	अटल_branch_dec(&mmu_audit_key);
	mmu_audit = false;
पूर्ण

अटल पूर्णांक mmu_audit_set(स्थिर अक्षर *val, स्थिर काष्ठा kernel_param *kp)
अणु
	पूर्णांक ret;
	अचिन्हित दीर्घ enable;

	ret = kम_से_अदीर्घ(val, 10, &enable);
	अगर (ret < 0)
		वापस -EINVAL;

	चयन (enable) अणु
	हाल 0:
		mmu_audit_disable();
		अवरोध;
	हाल 1:
		mmu_audit_enable();
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा kernel_param_ops audit_param_ops = अणु
	.set = mmu_audit_set,
	.get = param_get_bool,
पूर्ण;

arch_param_cb(mmu_audit, &audit_param_ops, &mmu_audit, 0644);
