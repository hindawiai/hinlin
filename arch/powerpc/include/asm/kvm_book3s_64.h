<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *
 * Copyright SUSE Linux Products GmbH 2010
 *
 * Authors: Alexander Graf <agraf@suse.de>
 */

#अगर_अघोषित __ASM_KVM_BOOK3S_64_H__
#घोषणा __ASM_KVM_BOOK3S_64_H__

#समावेश <linux/माला.स>
#समावेश <यंत्र/bitops.h>
#समावेश <यंत्र/book3s/64/mmu-hash.h>
#समावेश <यंत्र/cpu_has_feature.h>
#समावेश <यंत्र/ppc-opcode.h>
#समावेश <यंत्र/pte-walk.h>

#अगर_घोषित CONFIG_PPC_PSERIES
अटल अंतरभूत bool kvmhv_on_pseries(व्योम)
अणु
	वापस !cpu_has_feature(CPU_FTR_HVMODE);
पूर्ण
#अन्यथा
अटल अंतरभूत bool kvmhv_on_pseries(व्योम)
अणु
	वापस false;
पूर्ण
#पूर्ण_अगर

/*
 * Structure क्रम a nested guest, that is, क्रम a guest that is managed by
 * one of our guests.
 */
काष्ठा kvm_nested_guest अणु
	काष्ठा kvm *l1_host;		/* L1 VM that owns this nested guest */
	पूर्णांक l1_lpid;			/* lpid L1 guest thinks this guest is */
	पूर्णांक shaकरोw_lpid;		/* real lpid of this nested guest */
	pgd_t *shaकरोw_pgtable;		/* our page table क्रम this guest */
	u64 l1_gr_to_hr;		/* L1's addr of part'n-scoped table */
	u64 process_table;		/* process table entry क्रम this guest */
	दीर्घ refcnt;			/* number of poपूर्णांकers to this काष्ठा */
	काष्ठा mutex tlb_lock;		/* serialize page faults and tlbies */
	काष्ठा kvm_nested_guest *next;
	cpumask_t need_tlb_flush;
	cpumask_t cpu_in_guest;
	लघु prev_cpu[NR_CPUS];
	u8 radix;			/* is this nested guest radix */
पूर्ण;

/*
 * We define a nested rmap entry as a single 64-bit quantity
 * 0xFFF0000000000000	12-bit lpid field
 * 0x000FFFFFFFFFF000	40-bit guest 4k page frame number
 * 0x0000000000000001	1-bit  single entry flag
 */
#घोषणा RMAP_NESTED_LPID_MASK		0xFFF0000000000000UL
#घोषणा RMAP_NESTED_LPID_SHIFT		(52)
#घोषणा RMAP_NESTED_GPA_MASK		0x000FFFFFFFFFF000UL
#घोषणा RMAP_NESTED_IS_SINGLE_ENTRY	0x0000000000000001UL

/* Structure क्रम a nested guest rmap entry */
काष्ठा rmap_nested अणु
	काष्ठा llist_node list;
	u64 rmap;
पूर्ण;

/*
 * क्रम_each_nest_rmap_safe - iterate over the list of nested rmap entries
 *			     safe against removal of the list entry or शून्य list
 * @pos:	a (काष्ठा rmap_nested *) to use as a loop cursor
 * @node:	poपूर्णांकer to the first entry
 *		NOTE: this can be शून्य
 * @rmapp:	an (अचिन्हित दीर्घ *) in which to वापस the rmap entries on each
 *		iteration
 *		NOTE: this must poपूर्णांक to alपढ़ोy allocated memory
 *
 * The nested_rmap is a llist of (काष्ठा rmap_nested) entries poपूर्णांकed to by the
 * rmap entry in the memslot. The list is always terminated by a "single entry"
 * stored in the list element of the final entry of the llist. If there is ONLY
 * a single entry then this is itself in the rmap entry of the memslot, not a
 * llist head poपूर्णांकer.
 *
 * Note that the iterator below assumes that a nested rmap entry is always
 * non-zero.  This is true क्रम our usage because the LPID field is always
 * non-zero (zero is reserved क्रम the host).
 *
 * This should be used to iterate over the list of rmap_nested entries with
 * processing करोne on the u64 rmap value given by each iteration. This is safe
 * against removal of list entries and it is always safe to call मुक्त on (pos).
 *
 * e.g.
 * काष्ठा rmap_nested *cursor;
 * काष्ठा llist_node *first;
 * अचिन्हित दीर्घ rmap;
 * क्रम_each_nest_rmap_safe(cursor, first, &rmap) अणु
 *	करो_something(rmap);
 *	मुक्त(cursor);
 * पूर्ण
 */
#घोषणा क्रम_each_nest_rmap_safe(pos, node, rmapp)			       \
	क्रम ((pos) = llist_entry((node), typeof(*(pos)), list);		       \
	     (node) &&							       \
	     (*(rmapp) = ((RMAP_NESTED_IS_SINGLE_ENTRY & ((u64) (node))) ?     \
			  ((u64) (node)) : ((pos)->rmap))) &&		       \
	     (((node) = ((RMAP_NESTED_IS_SINGLE_ENTRY & ((u64) (node))) ?      \
			 ((काष्ठा llist_node *) ((pos) = शून्य)) :	       \
			 (pos)->list.next)), true);			       \
	     (pos) = llist_entry((node), typeof(*(pos)), list))

काष्ठा kvm_nested_guest *kvmhv_get_nested(काष्ठा kvm *kvm, पूर्णांक l1_lpid,
					  bool create);
व्योम kvmhv_put_nested(काष्ठा kvm_nested_guest *gp);
पूर्णांक kvmhv_nested_next_lpid(काष्ठा kvm *kvm, पूर्णांक lpid);

/* Encoding of first parameter क्रम H_TLB_INVALIDATE */
#घोषणा H_TLBIE_P1_ENC(ric, prs, r)	(___PPC_RIC(ric) | ___PPC_PRS(prs) | \
					 ___PPC_R(r))

/* Power architecture requires HPT is at least 256kiB, at most 64TiB */
#घोषणा PPC_MIN_HPT_ORDER	18
#घोषणा PPC_MAX_HPT_ORDER	46

#अगर_घोषित CONFIG_KVM_BOOK3S_PR_POSSIBLE
अटल अंतरभूत काष्ठा kvmppc_book3s_shaकरोw_vcpu *svcpu_get(काष्ठा kvm_vcpu *vcpu)
अणु
	preempt_disable();
	वापस &get_paca()->shaकरोw_vcpu;
पूर्ण

अटल अंतरभूत व्योम svcpu_put(काष्ठा kvmppc_book3s_shaकरोw_vcpu *svcpu)
अणु
	preempt_enable();
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_KVM_BOOK3S_HV_POSSIBLE

अटल अंतरभूत bool kvm_is_radix(काष्ठा kvm *kvm)
अणु
	वापस kvm->arch.radix;
पूर्ण

अटल अंतरभूत bool kvmhv_vcpu_is_radix(काष्ठा kvm_vcpu *vcpu)
अणु
	bool radix;

	अगर (vcpu->arch.nested)
		radix = vcpu->arch.nested->radix;
	अन्यथा
		radix = kvm_is_radix(vcpu->kvm);

	वापस radix;
पूर्ण

#घोषणा KVM_DEFAULT_HPT_ORDER	24	/* 16MB HPT by शेष */
#पूर्ण_अगर

/*
 * We use a lock bit in HPTE dword 0 to synchronize updates and
 * accesses to each HPTE, and another bit to indicate non-present
 * HPTEs.
 */
#घोषणा HPTE_V_HVLOCK	0x40UL
#घोषणा HPTE_V_ABSENT	0x20UL

/*
 * We use this bit in the guest_rpte field of the revmap entry
 * to indicate a modअगरied HPTE.
 */
#घोषणा HPTE_GR_MODIFIED	(1ul << 62)

/* These bits are reserved in the guest view of the HPTE */
#घोषणा HPTE_GR_RESERVED	HPTE_GR_MODIFIED

अटल अंतरभूत दीर्घ try_lock_hpte(__be64 *hpte, अचिन्हित दीर्घ bits)
अणु
	अचिन्हित दीर्घ पंचांगp, old;
	__be64 be_lockbit, be_bits;

	/*
	 * We load/store in native endian, but the HTAB is in big endian. If
	 * we byte swap all data we apply on the PTE we're implicitly correct
	 * again.
	 */
	be_lockbit = cpu_to_be64(HPTE_V_HVLOCK);
	be_bits = cpu_to_be64(bits);

	यंत्र अस्थिर("	ldarx	%0,0,%2\n"
		     "	and.	%1,%0,%3\n"
		     "	bne	2f\n"
		     "	or	%0,%0,%4\n"
		     "  stdcx.	%0,0,%2\n"
		     "	beq+	2f\n"
		     "	mr	%1,%3\n"
		     "2:	isync"
		     : "=&r" (पंचांगp), "=&r" (old)
		     : "r" (hpte), "r" (be_bits), "r" (be_lockbit)
		     : "cc", "memory");
	वापस old == 0;
पूर्ण

अटल अंतरभूत व्योम unlock_hpte(__be64 *hpte, अचिन्हित दीर्घ hpte_v)
अणु
	hpte_v &= ~HPTE_V_HVLOCK;
	यंत्र अस्थिर(PPC_RELEASE_BARRIER "" : : : "memory");
	hpte[0] = cpu_to_be64(hpte_v);
पूर्ण

/* Without barrier */
अटल अंतरभूत व्योम __unlock_hpte(__be64 *hpte, अचिन्हित दीर्घ hpte_v)
अणु
	hpte_v &= ~HPTE_V_HVLOCK;
	hpte[0] = cpu_to_be64(hpte_v);
पूर्ण

/*
 * These functions encode knowledge of the POWER7/8/9 hardware
 * पूर्णांकerpretations of the HPTE LP (large page size) field.
 */
अटल अंतरभूत पूर्णांक kvmppc_hpte_page_shअगरts(अचिन्हित दीर्घ h, अचिन्हित दीर्घ l)
अणु
	अचिन्हित पूर्णांक lphi;

	अगर (!(h & HPTE_V_LARGE))
		वापस 12;	/* 4kB */
	lphi = (l >> 16) & 0xf;
	चयन ((l >> 12) & 0xf) अणु
	हाल 0:
		वापस !lphi ? 24 : 0;		/* 16MB */
		अवरोध;
	हाल 1:
		वापस 16;			/* 64kB */
		अवरोध;
	हाल 3:
		वापस !lphi ? 34 : 0;		/* 16GB */
		अवरोध;
	हाल 7:
		वापस (16 << 8) + 12;		/* 64kB in 4kB */
		अवरोध;
	हाल 8:
		अगर (!lphi)
			वापस (24 << 8) + 16;	/* 16MB in 64kkB */
		अगर (lphi == 3)
			वापस (24 << 8) + 12;	/* 16MB in 4kB */
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक kvmppc_hpte_base_page_shअगरt(अचिन्हित दीर्घ h, अचिन्हित दीर्घ l)
अणु
	वापस kvmppc_hpte_page_shअगरts(h, l) & 0xff;
पूर्ण

अटल अंतरभूत पूर्णांक kvmppc_hpte_actual_page_shअगरt(अचिन्हित दीर्घ h, अचिन्हित दीर्घ l)
अणु
	पूर्णांक पंचांगp = kvmppc_hpte_page_shअगरts(h, l);

	अगर (पंचांगp >= 0x100)
		पंचांगp >>= 8;
	वापस पंचांगp;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ kvmppc_actual_pgsz(अचिन्हित दीर्घ v, अचिन्हित दीर्घ r)
अणु
	पूर्णांक shअगरt = kvmppc_hpte_actual_page_shअगरt(v, r);

	अगर (shअगरt)
		वापस 1ul << shअगरt;
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक kvmppc_pgsize_lp_encoding(पूर्णांक base_shअगरt, पूर्णांक actual_shअगरt)
अणु
	चयन (base_shअगरt) अणु
	हाल 12:
		चयन (actual_shअगरt) अणु
		हाल 12:
			वापस 0;
		हाल 16:
			वापस 7;
		हाल 24:
			वापस 0x38;
		पूर्ण
		अवरोध;
	हाल 16:
		चयन (actual_shअगरt) अणु
		हाल 16:
			वापस 1;
		हाल 24:
			वापस 8;
		पूर्ण
		अवरोध;
	हाल 24:
		वापस 0;
	पूर्ण
	वापस -1;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ compute_tlbie_rb(अचिन्हित दीर्घ v, अचिन्हित दीर्घ r,
					     अचिन्हित दीर्घ pte_index)
अणु
	पूर्णांक a_pgshअगरt, b_pgshअगरt;
	अचिन्हित दीर्घ rb = 0, va_low, sllp;

	b_pgshअगरt = a_pgshअगरt = kvmppc_hpte_page_shअगरts(v, r);
	अगर (a_pgshअगरt >= 0x100) अणु
		b_pgshअगरt &= 0xff;
		a_pgshअगरt >>= 8;
	पूर्ण

	/*
	 * Ignore the top 14 bits of va
	 * v have top two bits covering segment size, hence move
	 * by 16 bits, Also clear the lower HPTE_V_AVPN_SHIFT (7) bits.
	 * AVA field in v also have the lower 23 bits ignored.
	 * For base page size 4K we need 14 .. 65 bits (so need to
	 * collect extra 11 bits)
	 * For others we need 14..14+i
	 */
	/* This covers 14..54 bits of va*/
	rb = (v & ~0x7fUL) << 16;		/* AVA field */

	/*
	 * AVA in v had cleared lower 23 bits. We need to derive
	 * that from pteg index
	 */
	va_low = pte_index >> 3;
	अगर (v & HPTE_V_SECONDARY)
		va_low = ~va_low;
	/*
	 * get the vpn bits from va_low using reverse of hashing.
	 * In v we have va with 23 bits dropped and then left shअगरted
	 * HPTE_V_AVPN_SHIFT (7) bits. Now to find vsid we need
	 * right shअगरt it with (SID_SHIFT - (23 - 7))
	 */
	अगर (!(v & HPTE_V_1TB_SEG))
		va_low ^= v >> (SID_SHIFT - 16);
	अन्यथा
		va_low ^= v >> (SID_SHIFT_1T - 16);
	va_low &= 0x7ff;

	अगर (b_pgshअगरt <= 12) अणु
		अगर (a_pgshअगरt > 12) अणु
			sllp = (a_pgshअगरt == 16) ? 5 : 4;
			rb |= sllp << 5;	/*  AP field */
		पूर्ण
		rb |= (va_low & 0x7ff) << 12;	/* reमुख्यing 11 bits of AVA */
	पूर्ण अन्यथा अणु
		पूर्णांक aval_shअगरt;
		/*
		 * reमुख्यing bits of AVA/LP fields
		 * Also contain the rr bits of LP
		 */
		rb |= (va_low << b_pgshअगरt) & 0x7ff000;
		/*
		 * Now clear not needed LP bits based on actual psize
		 */
		rb &= ~((1ul << a_pgshअगरt) - 1);
		/*
		 * AVAL field 58..77 - base_page_shअगरt bits of va
		 * we have space क्रम 58..64 bits, Missing bits should
		 * be zero filled. +1 is to take care of L bit shअगरt
		 */
		aval_shअगरt = 64 - (77 - b_pgshअगरt) + 1;
		rb |= ((va_low << aval_shअगरt) & 0xfe);

		rb |= 1;		/* L field */
		rb |= r & 0xff000 & ((1ul << a_pgshअगरt) - 1); /* LP field */
	पूर्ण
	rb |= (v >> HPTE_V_SSIZE_SHIFT) << 8;	/* B field */
	वापस rb;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ hpte_rpn(अचिन्हित दीर्घ ptel, अचिन्हित दीर्घ psize)
अणु
	वापस ((ptel & HPTE_R_RPN) & ~(psize - 1)) >> PAGE_SHIFT;
पूर्ण

अटल अंतरभूत पूर्णांक hpte_is_writable(अचिन्हित दीर्घ ptel)
अणु
	अचिन्हित दीर्घ pp = ptel & (HPTE_R_PP0 | HPTE_R_PP);

	वापस pp != PP_RXRX && pp != PP_RXXX;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ hpte_make_पढ़ोonly(अचिन्हित दीर्घ ptel)
अणु
	अगर ((ptel & HPTE_R_PP0) || (ptel & HPTE_R_PP) == PP_RWXX)
		ptel = (ptel & ~HPTE_R_PP) | PP_RXXX;
	अन्यथा
		ptel |= PP_RXRX;
	वापस ptel;
पूर्ण

अटल अंतरभूत bool hpte_cache_flags_ok(अचिन्हित दीर्घ hptel, bool is_ci)
अणु
	अचिन्हित पूर्णांक wimg = hptel & HPTE_R_WIMG;

	/* Handle SAO */
	अगर (wimg == (HPTE_R_W | HPTE_R_I | HPTE_R_M) &&
	    cpu_has_feature(CPU_FTR_ARCH_206))
		wimg = HPTE_R_M;

	अगर (!is_ci)
		वापस wimg == HPTE_R_M;
	/*
	 * अगर host is mapped cache inhibited, make sure hptel also have
	 * cache inhibited.
	 */
	अगर (wimg & HPTE_R_W) /* FIXME!! is this ok क्रम all guest. ? */
		वापस false;
	वापस !!(wimg & HPTE_R_I);
पूर्ण

/*
 * If it's present and writable, atomically set dirty and referenced bits and
 * वापस the PTE, otherwise वापस 0.
 */
अटल अंतरभूत pte_t kvmppc_पढ़ो_update_linux_pte(pte_t *ptep, पूर्णांक writing)
अणु
	pte_t old_pte, new_pte = __pte(0);

	जबतक (1) अणु
		/*
		 * Make sure we करोn't reload from ptep
		 */
		old_pte = READ_ONCE(*ptep);
		/*
		 * रुको until H_PAGE_BUSY is clear then set it atomically
		 */
		अगर (unlikely(pte_val(old_pte) & H_PAGE_BUSY)) अणु
			cpu_relax();
			जारी;
		पूर्ण
		/* If pte is not present वापस None */
		अगर (unlikely(!pte_present(old_pte)))
			वापस __pte(0);

		new_pte = pte_mkyoung(old_pte);
		अगर (writing && pte_ग_लिखो(old_pte))
			new_pte = pte_सूची_गढ़ोty(new_pte);

		अगर (pte_xchg(ptep, old_pte, new_pte))
			अवरोध;
	पूर्ण
	वापस new_pte;
पूर्ण

अटल अंतरभूत bool hpte_पढ़ो_permission(अचिन्हित दीर्घ pp, अचिन्हित दीर्घ key)
अणु
	अगर (key)
		वापस PP_RWRX <= pp && pp <= PP_RXRX;
	वापस true;
पूर्ण

अटल अंतरभूत bool hpte_ग_लिखो_permission(अचिन्हित दीर्घ pp, अचिन्हित दीर्घ key)
अणु
	अगर (key)
		वापस pp == PP_RWRW;
	वापस pp <= PP_RWRW;
पूर्ण

अटल अंतरभूत पूर्णांक hpte_get_skey_perm(अचिन्हित दीर्घ hpte_r, अचिन्हित दीर्घ amr)
अणु
	अचिन्हित दीर्घ skey;

	skey = ((hpte_r & HPTE_R_KEY_HI) >> 57) |
		((hpte_r & HPTE_R_KEY_LO) >> 9);
	वापस (amr >> (62 - 2 * skey)) & 3;
पूर्ण

अटल अंतरभूत व्योम lock_rmap(अचिन्हित दीर्घ *rmap)
अणु
	करो अणु
		जबतक (test_bit(KVMPPC_RMAP_LOCK_BIT, rmap))
			cpu_relax();
	पूर्ण जबतक (test_and_set_bit_lock(KVMPPC_RMAP_LOCK_BIT, rmap));
पूर्ण

अटल अंतरभूत व्योम unlock_rmap(अचिन्हित दीर्घ *rmap)
अणु
	__clear_bit_unlock(KVMPPC_RMAP_LOCK_BIT, rmap);
पूर्ण

अटल अंतरभूत bool slot_is_aligned(काष्ठा kvm_memory_slot *memslot,
				   अचिन्हित दीर्घ pagesize)
अणु
	अचिन्हित दीर्घ mask = (pagesize >> PAGE_SHIFT) - 1;

	अगर (pagesize <= PAGE_SIZE)
		वापस true;
	वापस !(memslot->base_gfn & mask) && !(memslot->npages & mask);
पूर्ण

/*
 * This works क्रम 4k, 64k and 16M pages on POWER7,
 * and 4k and 16M pages on PPC970.
 */
अटल अंतरभूत अचिन्हित दीर्घ slb_pgsize_encoding(अचिन्हित दीर्घ psize)
अणु
	अचिन्हित दीर्घ senc = 0;

	अगर (psize > 0x1000) अणु
		senc = SLB_VSID_L;
		अगर (psize == 0x10000)
			senc |= SLB_VSID_LP_01;
	पूर्ण
	वापस senc;
पूर्ण

अटल अंतरभूत पूर्णांक is_vrma_hpte(अचिन्हित दीर्घ hpte_v)
अणु
	वापस (hpte_v & ~0xffffffUL) ==
		(HPTE_V_1TB_SEG | (VRMA_VSID << (40 - 16)));
पूर्ण

#अगर_घोषित CONFIG_KVM_BOOK3S_HV_POSSIBLE
/*
 * Note modअगरication of an HPTE; set the HPTE modअगरied bit
 * अगर anyone is पूर्णांकerested.
 */
अटल अंतरभूत व्योम note_hpte_modअगरication(काष्ठा kvm *kvm,
					  काष्ठा revmap_entry *rev)
अणु
	अगर (atomic_पढ़ो(&kvm->arch.hpte_mod_पूर्णांकerest))
		rev->guest_rpte |= HPTE_GR_MODIFIED;
पूर्ण

/*
 * Like kvm_memslots(), but क्रम use in real mode when we can't करो
 * any RCU stuff (since the secondary thपढ़ोs are offline from the
 * kernel's point of view), and we can't prपूर्णांक anything.
 * Thus we use rcu_dereference_raw() rather than rcu_dereference_check().
 */
अटल अंतरभूत काष्ठा kvm_memslots *kvm_memslots_raw(काष्ठा kvm *kvm)
अणु
	वापस rcu_dereference_raw_check(kvm->memslots[0]);
पूर्ण

बाह्य व्योम kvmppc_mmu_debugfs_init(काष्ठा kvm *kvm);
बाह्य व्योम kvmhv_radix_debugfs_init(काष्ठा kvm *kvm);

बाह्य व्योम kvmhv_rm_send_ipi(पूर्णांक cpu);

अटल अंतरभूत अचिन्हित दीर्घ kvmppc_hpt_npte(काष्ठा kvm_hpt_info *hpt)
अणु
	/* HPTEs are 2**4 bytes दीर्घ */
	वापस 1UL << (hpt->order - 4);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ kvmppc_hpt_mask(काष्ठा kvm_hpt_info *hpt)
अणु
	/* 128 (2**7) bytes in each HPTEG */
	वापस (1UL << (hpt->order - 7)) - 1;
पूर्ण

/* Set bits in a dirty biपंचांगap, which is in LE क्रमmat */
अटल अंतरभूत व्योम set_dirty_bits(अचिन्हित दीर्घ *map, अचिन्हित दीर्घ i,
				  अचिन्हित दीर्घ npages)
अणु

	अगर (npages >= 8)
		स_रखो((अक्षर *)map + i / 8, 0xff, npages / 8);
	अन्यथा
		क्रम (; npages; ++i, --npages)
			__set_bit_le(i, map);
पूर्ण

अटल अंतरभूत व्योम set_dirty_bits_atomic(अचिन्हित दीर्घ *map, अचिन्हित दीर्घ i,
					 अचिन्हित दीर्घ npages)
अणु
	अगर (npages >= 8)
		स_रखो((अक्षर *)map + i / 8, 0xff, npages / 8);
	अन्यथा
		क्रम (; npages; ++i, --npages)
			set_bit_le(i, map);
पूर्ण

अटल अंतरभूत u64 sanitize_msr(u64 msr)
अणु
	msr &= ~MSR_HV;
	msr |= MSR_ME;
	वापस msr;
पूर्ण

#अगर_घोषित CONFIG_PPC_TRANSACTIONAL_MEM
अटल अंतरभूत व्योम copy_from_checkpoपूर्णांक(काष्ठा kvm_vcpu *vcpu)
अणु
	vcpu->arch.regs.ccr  = vcpu->arch.cr_पंचांग;
	vcpu->arch.regs.xer = vcpu->arch.xer_पंचांग;
	vcpu->arch.regs.link  = vcpu->arch.lr_पंचांग;
	vcpu->arch.regs.ctr = vcpu->arch.ctr_पंचांग;
	vcpu->arch.amr = vcpu->arch.amr_पंचांग;
	vcpu->arch.ppr = vcpu->arch.ppr_पंचांग;
	vcpu->arch.dscr = vcpu->arch.dscr_पंचांग;
	vcpu->arch.tar = vcpu->arch.tar_पंचांग;
	स_नकल(vcpu->arch.regs.gpr, vcpu->arch.gpr_पंचांग,
	       माप(vcpu->arch.regs.gpr));
	vcpu->arch.fp  = vcpu->arch.fp_पंचांग;
	vcpu->arch.vr  = vcpu->arch.vr_पंचांग;
	vcpu->arch.vrsave = vcpu->arch.vrsave_पंचांग;
पूर्ण

अटल अंतरभूत व्योम copy_to_checkpoपूर्णांक(काष्ठा kvm_vcpu *vcpu)
अणु
	vcpu->arch.cr_पंचांग  = vcpu->arch.regs.ccr;
	vcpu->arch.xer_पंचांग = vcpu->arch.regs.xer;
	vcpu->arch.lr_पंचांग  = vcpu->arch.regs.link;
	vcpu->arch.ctr_पंचांग = vcpu->arch.regs.ctr;
	vcpu->arch.amr_पंचांग = vcpu->arch.amr;
	vcpu->arch.ppr_पंचांग = vcpu->arch.ppr;
	vcpu->arch.dscr_पंचांग = vcpu->arch.dscr;
	vcpu->arch.tar_पंचांग = vcpu->arch.tar;
	स_नकल(vcpu->arch.gpr_पंचांग, vcpu->arch.regs.gpr,
	       माप(vcpu->arch.regs.gpr));
	vcpu->arch.fp_पंचांग  = vcpu->arch.fp;
	vcpu->arch.vr_पंचांग  = vcpu->arch.vr;
	vcpu->arch.vrsave_पंचांग = vcpu->arch.vrsave;
पूर्ण
#पूर्ण_अगर /* CONFIG_PPC_TRANSACTIONAL_MEM */

बाह्य पूर्णांक kvmppc_create_pte(काष्ठा kvm *kvm, pgd_t *pgtable, pte_t pte,
			     अचिन्हित दीर्घ gpa, अचिन्हित पूर्णांक level,
			     अचिन्हित दीर्घ mmu_seq, अचिन्हित पूर्णांक lpid,
			     अचिन्हित दीर्घ *rmapp, काष्ठा rmap_nested **n_rmap);
बाह्य व्योम kvmhv_insert_nest_rmap(काष्ठा kvm *kvm, अचिन्हित दीर्घ *rmapp,
				   काष्ठा rmap_nested **n_rmap);
बाह्य व्योम kvmhv_update_nest_rmap_rc_list(काष्ठा kvm *kvm, अचिन्हित दीर्घ *rmapp,
					   अचिन्हित दीर्घ clr, अचिन्हित दीर्घ set,
					   अचिन्हित दीर्घ hpa, अचिन्हित दीर्घ nbytes);
बाह्य व्योम kvmhv_हटाओ_nest_rmap_range(काष्ठा kvm *kvm,
				स्थिर काष्ठा kvm_memory_slot *memslot,
				अचिन्हित दीर्घ gpa, अचिन्हित दीर्घ hpa,
				अचिन्हित दीर्घ nbytes);

अटल अंतरभूत pte_t *
find_kvm_secondary_pte_unlocked(काष्ठा kvm *kvm, अचिन्हित दीर्घ ea,
				अचिन्हित *hshअगरt)
अणु
	pte_t *pte;

	pte = __find_linux_pte(kvm->arch.pgtable, ea, शून्य, hshअगरt);
	वापस pte;
पूर्ण

अटल अंतरभूत pte_t *find_kvm_secondary_pte(काष्ठा kvm *kvm, अचिन्हित दीर्घ ea,
					    अचिन्हित *hshअगरt)
अणु
	pte_t *pte;

	VM_WARN(!spin_is_locked(&kvm->mmu_lock),
		"%s called with kvm mmu_lock not held \n", __func__);
	pte = __find_linux_pte(kvm->arch.pgtable, ea, शून्य, hshअगरt);

	वापस pte;
पूर्ण

अटल अंतरभूत pte_t *find_kvm_host_pte(काष्ठा kvm *kvm, अचिन्हित दीर्घ mmu_seq,
				       अचिन्हित दीर्घ ea, अचिन्हित *hshअगरt)
अणु
	pte_t *pte;

	VM_WARN(!spin_is_locked(&kvm->mmu_lock),
		"%s called with kvm mmu_lock not held \n", __func__);

	अगर (mmu_notअगरier_retry(kvm, mmu_seq))
		वापस शून्य;

	pte = __find_linux_pte(kvm->mm->pgd, ea, शून्य, hshअगरt);

	वापस pte;
पूर्ण

बाह्य pte_t *find_kvm_nested_guest_pte(काष्ठा kvm *kvm, अचिन्हित दीर्घ lpid,
					अचिन्हित दीर्घ ea, अचिन्हित *hshअगरt);

#पूर्ण_अगर /* CONFIG_KVM_BOOK3S_HV_POSSIBLE */

#पूर्ण_अगर /* __ASM_KVM_BOOK3S_64_H__ */
