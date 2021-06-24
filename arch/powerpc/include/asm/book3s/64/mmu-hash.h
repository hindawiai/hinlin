<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
#अगर_अघोषित _ASM_POWERPC_BOOK3S_64_MMU_HASH_H_
#घोषणा _ASM_POWERPC_BOOK3S_64_MMU_HASH_H_
/*
 * PowerPC64 memory management काष्ठाures
 *
 * Dave Engebretsen & Mike Corrigan <अणुengebret|mikejcपूर्ण@us.ibm.com>
 *   PPC64 rework.
 */

#समावेश <यंत्र/page.h>
#समावेश <यंत्र/bug.h>
#समावेश <यंत्र/यंत्र-स्थिर.h>

/*
 * This is necessary to get the definition of PGTABLE_RANGE which we
 * need क्रम various slices related matters. Note that this isn't the
 * complete pgtable.h but only a portion of it.
 */
#समावेश <यंत्र/book3s/64/pgtable.h>
#समावेश <यंत्र/task_size_64.h>
#समावेश <यंत्र/cpu_has_feature.h>

/*
 * SLB
 */

#घोषणा SLB_NUM_BOLTED		2
#घोषणा SLB_CACHE_ENTRIES	8
#घोषणा SLB_MIN_SIZE		32

/* Bits in the SLB ESID word */
#घोषणा SLB_ESID_V		ASM_CONST(0x0000000008000000) /* valid */

/* Bits in the SLB VSID word */
#घोषणा SLB_VSID_SHIFT		12
#घोषणा SLB_VSID_SHIFT_256M	SLB_VSID_SHIFT
#घोषणा SLB_VSID_SHIFT_1T	24
#घोषणा SLB_VSID_SSIZE_SHIFT	62
#घोषणा SLB_VSID_B		ASM_CONST(0xc000000000000000)
#घोषणा SLB_VSID_B_256M		ASM_CONST(0x0000000000000000)
#घोषणा SLB_VSID_B_1T		ASM_CONST(0x4000000000000000)
#घोषणा SLB_VSID_KS		ASM_CONST(0x0000000000000800)
#घोषणा SLB_VSID_KP		ASM_CONST(0x0000000000000400)
#घोषणा SLB_VSID_N		ASM_CONST(0x0000000000000200) /* no-execute */
#घोषणा SLB_VSID_L		ASM_CONST(0x0000000000000100)
#घोषणा SLB_VSID_C		ASM_CONST(0x0000000000000080) /* class */
#घोषणा SLB_VSID_LP		ASM_CONST(0x0000000000000030)
#घोषणा SLB_VSID_LP_00		ASM_CONST(0x0000000000000000)
#घोषणा SLB_VSID_LP_01		ASM_CONST(0x0000000000000010)
#घोषणा SLB_VSID_LP_10		ASM_CONST(0x0000000000000020)
#घोषणा SLB_VSID_LP_11		ASM_CONST(0x0000000000000030)
#घोषणा SLB_VSID_LLP		(SLB_VSID_L|SLB_VSID_LP)

#घोषणा SLB_VSID_KERNEL		(SLB_VSID_KP)
#घोषणा SLB_VSID_USER		(SLB_VSID_KP|SLB_VSID_KS|SLB_VSID_C)

#घोषणा SLBIE_C			(0x08000000)
#घोषणा SLBIE_SSIZE_SHIFT	25

/*
 * Hash table
 */

#घोषणा HPTES_PER_GROUP 8

#घोषणा HPTE_V_SSIZE_SHIFT	62
#घोषणा HPTE_V_AVPN_SHIFT	7
#घोषणा HPTE_V_COMMON_BITS	ASM_CONST(0x000fffffffffffff)
#घोषणा HPTE_V_AVPN		ASM_CONST(0x3fffffffffffff80)
#घोषणा HPTE_V_AVPN_3_0		ASM_CONST(0x000fffffffffff80)
#घोषणा HPTE_V_AVPN_VAL(x)	(((x) & HPTE_V_AVPN) >> HPTE_V_AVPN_SHIFT)
#घोषणा HPTE_V_COMPARE(x,y)	(!(((x) ^ (y)) & 0xffffffffffffff80UL))
#घोषणा HPTE_V_BOLTED		ASM_CONST(0x0000000000000010)
#घोषणा HPTE_V_LOCK		ASM_CONST(0x0000000000000008)
#घोषणा HPTE_V_LARGE		ASM_CONST(0x0000000000000004)
#घोषणा HPTE_V_SECONDARY	ASM_CONST(0x0000000000000002)
#घोषणा HPTE_V_VALID		ASM_CONST(0x0000000000000001)

/*
 * ISA 3.0 has a dअगरferent HPTE क्रमmat.
 */
#घोषणा HPTE_R_3_0_SSIZE_SHIFT	58
#घोषणा HPTE_R_3_0_SSIZE_MASK	(3ull << HPTE_R_3_0_SSIZE_SHIFT)
#घोषणा HPTE_R_PP0		ASM_CONST(0x8000000000000000)
#घोषणा HPTE_R_TS		ASM_CONST(0x4000000000000000)
#घोषणा HPTE_R_KEY_HI		ASM_CONST(0x3000000000000000)
#घोषणा HPTE_R_KEY_BIT4		ASM_CONST(0x2000000000000000)
#घोषणा HPTE_R_KEY_BIT3		ASM_CONST(0x1000000000000000)
#घोषणा HPTE_R_RPN_SHIFT	12
#घोषणा HPTE_R_RPN		ASM_CONST(0x0ffffffffffff000)
#घोषणा HPTE_R_RPN_3_0		ASM_CONST(0x01fffffffffff000)
#घोषणा HPTE_R_PP		ASM_CONST(0x0000000000000003)
#घोषणा HPTE_R_PPP		ASM_CONST(0x8000000000000003)
#घोषणा HPTE_R_N		ASM_CONST(0x0000000000000004)
#घोषणा HPTE_R_G		ASM_CONST(0x0000000000000008)
#घोषणा HPTE_R_M		ASM_CONST(0x0000000000000010)
#घोषणा HPTE_R_I		ASM_CONST(0x0000000000000020)
#घोषणा HPTE_R_W		ASM_CONST(0x0000000000000040)
#घोषणा HPTE_R_WIMG		ASM_CONST(0x0000000000000078)
#घोषणा HPTE_R_C		ASM_CONST(0x0000000000000080)
#घोषणा HPTE_R_R		ASM_CONST(0x0000000000000100)
#घोषणा HPTE_R_KEY_LO		ASM_CONST(0x0000000000000e00)
#घोषणा HPTE_R_KEY_BIT2		ASM_CONST(0x0000000000000800)
#घोषणा HPTE_R_KEY_BIT1		ASM_CONST(0x0000000000000400)
#घोषणा HPTE_R_KEY_BIT0		ASM_CONST(0x0000000000000200)
#घोषणा HPTE_R_KEY		(HPTE_R_KEY_LO | HPTE_R_KEY_HI)

#घोषणा HPTE_V_1TB_SEG		ASM_CONST(0x4000000000000000)
#घोषणा HPTE_V_VRMA_MASK	ASM_CONST(0x4001ffffff000000)

/* Values क्रम PP (assumes Ks=0, Kp=1) */
#घोषणा PP_RWXX	0	/* Supervisor पढ़ो/ग_लिखो, User none */
#घोषणा PP_RWRX 1	/* Supervisor पढ़ो/ग_लिखो, User पढ़ो */
#घोषणा PP_RWRW 2	/* Supervisor पढ़ो/ग_लिखो, User पढ़ो/ग_लिखो */
#घोषणा PP_RXRX 3	/* Supervisor पढ़ो,       User पढ़ो */
#घोषणा PP_RXXX	(HPTE_R_PP0 | 2)	/* Supervisor पढ़ो, user none */

/* Fields क्रम tlbiel inकाष्ठाion in architecture 2.06 */
#घोषणा TLBIEL_INVAL_SEL_MASK	0xc00	/* invalidation selector */
#घोषणा  TLBIEL_INVAL_PAGE	0x000	/* invalidate a single page */
#घोषणा  TLBIEL_INVAL_SET_LPID	0x800	/* invalidate a set क्रम current LPID */
#घोषणा  TLBIEL_INVAL_SET	0xc00	/* invalidate a set क्रम all LPIDs */
#घोषणा TLBIEL_INVAL_SET_MASK	0xfff000	/* set number to inval. */
#घोषणा TLBIEL_INVAL_SET_SHIFT	12

#घोषणा POWER7_TLB_SETS		128	/* # sets in POWER7 TLB */
#घोषणा POWER8_TLB_SETS		512	/* # sets in POWER8 TLB */
#घोषणा POWER9_TLB_SETS_HASH	256	/* # sets in POWER9 TLB Hash mode */
#घोषणा POWER9_TLB_SETS_RADIX	128	/* # sets in POWER9 TLB Radix mode */

#अगर_अघोषित __ASSEMBLY__

काष्ठा mmu_hash_ops अणु
	व्योम            (*hpte_invalidate)(अचिन्हित दीर्घ slot,
					   अचिन्हित दीर्घ vpn,
					   पूर्णांक bpsize, पूर्णांक apsize,
					   पूर्णांक ssize, पूर्णांक local);
	दीर्घ		(*hpte_updatepp)(अचिन्हित दीर्घ slot,
					 अचिन्हित दीर्घ newpp,
					 अचिन्हित दीर्घ vpn,
					 पूर्णांक bpsize, पूर्णांक apsize,
					 पूर्णांक ssize, अचिन्हित दीर्घ flags);
	व्योम            (*hpte_updateboltedpp)(अचिन्हित दीर्घ newpp,
					       अचिन्हित दीर्घ ea,
					       पूर्णांक psize, पूर्णांक ssize);
	दीर्घ		(*hpte_insert)(अचिन्हित दीर्घ hpte_group,
				       अचिन्हित दीर्घ vpn,
				       अचिन्हित दीर्घ prpn,
				       अचिन्हित दीर्घ rflags,
				       अचिन्हित दीर्घ vflags,
				       पूर्णांक psize, पूर्णांक apsize,
				       पूर्णांक ssize);
	दीर्घ		(*hpte_हटाओ)(अचिन्हित दीर्घ hpte_group);
	पूर्णांक             (*hpte_हटाओbolted)(अचिन्हित दीर्घ ea,
					     पूर्णांक psize, पूर्णांक ssize);
	व्योम		(*flush_hash_range)(अचिन्हित दीर्घ number, पूर्णांक local);
	व्योम		(*hugepage_invalidate)(अचिन्हित दीर्घ vsid,
					       अचिन्हित दीर्घ addr,
					       अचिन्हित अक्षर *hpte_slot_array,
					       पूर्णांक psize, पूर्णांक ssize, पूर्णांक local);
	पूर्णांक		(*resize_hpt)(अचिन्हित दीर्घ shअगरt);
	/*
	 * Special क्रम kexec.
	 * To be called in real mode with पूर्णांकerrupts disabled. No locks are
	 * taken as such, concurrent access on pre POWER5 hardware could result
	 * in a deadlock.
	 * The linear mapping is destroyed as well.
	 */
	व्योम		(*hpte_clear_all)(व्योम);
पूर्ण;
बाह्य काष्ठा mmu_hash_ops mmu_hash_ops;

काष्ठा hash_pte अणु
	__be64 v;
	__be64 r;
पूर्ण;

बाह्य काष्ठा hash_pte *htab_address;
बाह्य अचिन्हित दीर्घ htab_size_bytes;
बाह्य अचिन्हित दीर्घ htab_hash_mask;


अटल अंतरभूत पूर्णांक shअगरt_to_mmu_psize(अचिन्हित पूर्णांक shअगरt)
अणु
	पूर्णांक psize;

	क्रम (psize = 0; psize < MMU_PAGE_COUNT; ++psize)
		अगर (mmu_psize_defs[psize].shअगरt == shअगरt)
			वापस psize;
	वापस -1;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक mmu_pमाप_प्रकारo_shअगरt(अचिन्हित पूर्णांक mmu_psize)
अणु
	अगर (mmu_psize_defs[mmu_psize].shअगरt)
		वापस mmu_psize_defs[mmu_psize].shअगरt;
	BUG();
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक ap_to_shअगरt(अचिन्हित दीर्घ ap)
अणु
	पूर्णांक psize;

	क्रम (psize = 0; psize < MMU_PAGE_COUNT; psize++) अणु
		अगर (mmu_psize_defs[psize].ap == ap)
			वापस mmu_psize_defs[psize].shअगरt;
	पूर्ण

	वापस -1;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ get_sllp_encoding(पूर्णांक psize)
अणु
	अचिन्हित दीर्घ sllp;

	sllp = ((mmu_psize_defs[psize].sllp & SLB_VSID_L) >> 6) |
		((mmu_psize_defs[psize].sllp & SLB_VSID_LP) >> 4);
	वापस sllp;
पूर्ण

#पूर्ण_अगर /* __ASSEMBLY__ */

/*
 * Segment sizes.
 * These are the values used by hardware in the B field of
 * SLB entries and the first dword of MMU hashtable entries.
 * The B field is 2 bits; the values 2 and 3 are unused and reserved.
 */
#घोषणा MMU_SEGSIZE_256M	0
#घोषणा MMU_SEGSIZE_1T		1

/*
 * encode page number shअगरt.
 * in order to fit the 78 bit va in a 64 bit variable we shअगरt the va by
 * 12 bits. This enable us to address upto 76 bit va.
 * For hpt hash from a va we can ignore the page size bits of va and क्रम
 * hpte encoding we ignore up to 23 bits of va. So ignoring lower 12 bits ensure
 * we work in all हालs including 4k page size.
 */
#घोषणा VPN_SHIFT	12

/*
 * HPTE Large Page (LP) details
 */
#घोषणा LP_SHIFT	12
#घोषणा LP_BITS		8
#घोषणा LP_MASK(i)	((0xFF >> (i)) << LP_SHIFT)

#अगर_अघोषित __ASSEMBLY__

अटल अंतरभूत पूर्णांक slb_vsid_shअगरt(पूर्णांक ssize)
अणु
	अगर (ssize == MMU_SEGSIZE_256M)
		वापस SLB_VSID_SHIFT;
	वापस SLB_VSID_SHIFT_1T;
पूर्ण

अटल अंतरभूत पूर्णांक segment_shअगरt(पूर्णांक ssize)
अणु
	अगर (ssize == MMU_SEGSIZE_256M)
		वापस SID_SHIFT;
	वापस SID_SHIFT_1T;
पूर्ण

/*
 * This array is indexed by the LP field of the HPTE second dword.
 * Since this field may contain some RPN bits, some entries are
 * replicated so that we get the same value irrespective of RPN.
 * The top 4 bits are the page size index (MMU_PAGE_*) क्रम the
 * actual page size, the bottom 4 bits are the base page size.
 */
बाह्य u8 hpte_page_sizes[1 << LP_BITS];

अटल अंतरभूत अचिन्हित दीर्घ __hpte_page_size(अचिन्हित दीर्घ h, अचिन्हित दीर्घ l,
					     bool is_base_size)
अणु
	अचिन्हित पूर्णांक i, lp;

	अगर (!(h & HPTE_V_LARGE))
		वापस 1ul << 12;

	/* Look at the 8 bit LP value */
	lp = (l >> LP_SHIFT) & ((1 << LP_BITS) - 1);
	i = hpte_page_sizes[lp];
	अगर (!i)
		वापस 0;
	अगर (!is_base_size)
		i >>= 4;
	वापस 1ul << mmu_psize_defs[i & 0xf].shअगरt;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ hpte_page_size(अचिन्हित दीर्घ h, अचिन्हित दीर्घ l)
अणु
	वापस __hpte_page_size(h, l, 0);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ hpte_base_page_size(अचिन्हित दीर्घ h, अचिन्हित दीर्घ l)
अणु
	वापस __hpte_page_size(h, l, 1);
पूर्ण

/*
 * The current प्रणाली page and segment sizes
 */
बाह्य पूर्णांक mmu_kernel_ssize;
बाह्य पूर्णांक mmu_highuser_ssize;
बाह्य u16 mmu_slb_size;
बाह्य अचिन्हित दीर्घ tce_alloc_start, tce_alloc_end;

/*
 * If the processor supports 64k normal pages but not 64k cache
 * inhibited pages, we have to be prepared to चयन processes
 * to use 4k pages when they create cache-inhibited mappings.
 * If this is the हाल, mmu_ci_restrictions will be set to 1.
 */
बाह्य पूर्णांक mmu_ci_restrictions;

/*
 * This computes the AVPN and B fields of the first dword of a HPTE,
 * क्रम use when we want to match an existing PTE.  The bottom 7 bits
 * of the वापसed value are zero.
 */
अटल अंतरभूत अचिन्हित दीर्घ hpte_encode_avpn(अचिन्हित दीर्घ vpn, पूर्णांक psize,
					     पूर्णांक ssize)
अणु
	अचिन्हित दीर्घ v;
	/*
	 * The AVA field omits the low-order 23 bits of the 78 bits VA.
	 * These bits are not needed in the PTE, because the
	 * low-order b of these bits are part of the byte offset
	 * पूर्णांकo the भव page and, अगर b < 23, the high-order
	 * 23-b of these bits are always used in selecting the
	 * PTEGs to be searched
	 */
	v = (vpn >> (23 - VPN_SHIFT)) & ~(mmu_psize_defs[psize].avpnm);
	v <<= HPTE_V_AVPN_SHIFT;
	v |= ((अचिन्हित दीर्घ) ssize) << HPTE_V_SSIZE_SHIFT;
	वापस v;
पूर्ण

/*
 * ISA v3.0 defines a new HPTE क्रमmat, which dअगरfers from the old
 * क्रमmat in having smaller AVPN and ARPN fields, and the B field
 * in the second dword instead of the first.
 */
अटल अंतरभूत अचिन्हित दीर्घ hpte_old_to_new_v(अचिन्हित दीर्घ v)
अणु
	/* trim AVPN, drop B */
	वापस v & HPTE_V_COMMON_BITS;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ hpte_old_to_new_r(अचिन्हित दीर्घ v, अचिन्हित दीर्घ r)
अणु
	/* move B field from 1st to 2nd dword, trim ARPN */
	वापस (r & ~HPTE_R_3_0_SSIZE_MASK) |
		(((v) >> HPTE_V_SSIZE_SHIFT) << HPTE_R_3_0_SSIZE_SHIFT);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ hpte_new_to_old_v(अचिन्हित दीर्घ v, अचिन्हित दीर्घ r)
अणु
	/* insert B field */
	वापस (v & HPTE_V_COMMON_BITS) |
		((r & HPTE_R_3_0_SSIZE_MASK) <<
		 (HPTE_V_SSIZE_SHIFT - HPTE_R_3_0_SSIZE_SHIFT));
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ hpte_new_to_old_r(अचिन्हित दीर्घ r)
अणु
	/* clear out B field */
	वापस r & ~HPTE_R_3_0_SSIZE_MASK;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ hpte_get_old_v(काष्ठा hash_pte *hptep)
अणु
	अचिन्हित दीर्घ hpte_v;

	hpte_v = be64_to_cpu(hptep->v);
	अगर (cpu_has_feature(CPU_FTR_ARCH_300))
		hpte_v = hpte_new_to_old_v(hpte_v, be64_to_cpu(hptep->r));
	वापस hpte_v;
पूर्ण

/*
 * This function sets the AVPN and L fields of the HPTE  appropriately
 * using the base page size and actual page size.
 */
अटल अंतरभूत अचिन्हित दीर्घ hpte_encode_v(अचिन्हित दीर्घ vpn, पूर्णांक base_psize,
					  पूर्णांक actual_psize, पूर्णांक ssize)
अणु
	अचिन्हित दीर्घ v;
	v = hpte_encode_avpn(vpn, base_psize, ssize);
	अगर (actual_psize != MMU_PAGE_4K)
		v |= HPTE_V_LARGE;
	वापस v;
पूर्ण

/*
 * This function sets the ARPN, and LP fields of the HPTE appropriately
 * क्रम the page size. We assume the pa is alपढ़ोy "clean" that is properly
 * aligned क्रम the requested page size
 */
अटल अंतरभूत अचिन्हित दीर्घ hpte_encode_r(अचिन्हित दीर्घ pa, पूर्णांक base_psize,
					  पूर्णांक actual_psize)
अणु
	/* A 4K page needs no special encoding */
	अगर (actual_psize == MMU_PAGE_4K)
		वापस pa & HPTE_R_RPN;
	अन्यथा अणु
		अचिन्हित पूर्णांक penc = mmu_psize_defs[base_psize].penc[actual_psize];
		अचिन्हित पूर्णांक shअगरt = mmu_psize_defs[actual_psize].shअगरt;
		वापस (pa & ~((1ul << shअगरt) - 1)) | (penc << LP_SHIFT);
	पूर्ण
पूर्ण

/*
 * Build a VPN_SHIFT bit shअगरted va given VSID, EA and segment size.
 */
अटल अंतरभूत अचिन्हित दीर्घ hpt_vpn(अचिन्हित दीर्घ ea,
				    अचिन्हित दीर्घ vsid, पूर्णांक ssize)
अणु
	अचिन्हित दीर्घ mask;
	पूर्णांक s_shअगरt = segment_shअगरt(ssize);

	mask = (1ul << (s_shअगरt - VPN_SHIFT)) - 1;
	वापस (vsid << (s_shअगरt - VPN_SHIFT)) | ((ea >> VPN_SHIFT) & mask);
पूर्ण

/*
 * This hashes a भव address
 */
अटल अंतरभूत अचिन्हित दीर्घ hpt_hash(अचिन्हित दीर्घ vpn,
				     अचिन्हित पूर्णांक shअगरt, पूर्णांक ssize)
अणु
	अचिन्हित दीर्घ mask;
	अचिन्हित दीर्घ hash, vsid;

	/* VPN_SHIFT can be aपंचांगost 12 */
	अगर (ssize == MMU_SEGSIZE_256M) अणु
		mask = (1ul << (SID_SHIFT - VPN_SHIFT)) - 1;
		hash = (vpn >> (SID_SHIFT - VPN_SHIFT)) ^
			((vpn & mask) >> (shअगरt - VPN_SHIFT));
	पूर्ण अन्यथा अणु
		mask = (1ul << (SID_SHIFT_1T - VPN_SHIFT)) - 1;
		vsid = vpn >> (SID_SHIFT_1T - VPN_SHIFT);
		hash = vsid ^ (vsid << 25) ^
			((vpn & mask) >> (shअगरt - VPN_SHIFT)) ;
	पूर्ण
	वापस hash & 0x7fffffffffUL;
पूर्ण

#घोषणा HPTE_LOCAL_UPDATE	0x1
#घोषणा HPTE_NOHPTE_UPDATE	0x2
#घोषणा HPTE_USE_KERNEL_KEY	0x4

दीर्घ hpte_insert_repeating(अचिन्हित दीर्घ hash, अचिन्हित दीर्घ vpn, अचिन्हित दीर्घ pa,
			   अचिन्हित दीर्घ rlags, अचिन्हित दीर्घ vflags, पूर्णांक psize, पूर्णांक ssize);
बाह्य पूर्णांक __hash_page_4K(अचिन्हित दीर्घ ea, अचिन्हित दीर्घ access,
			  अचिन्हित दीर्घ vsid, pte_t *ptep, अचिन्हित दीर्घ trap,
			  अचिन्हित दीर्घ flags, पूर्णांक ssize, पूर्णांक subpage_prot);
बाह्य पूर्णांक __hash_page_64K(अचिन्हित दीर्घ ea, अचिन्हित दीर्घ access,
			   अचिन्हित दीर्घ vsid, pte_t *ptep, अचिन्हित दीर्घ trap,
			   अचिन्हित दीर्घ flags, पूर्णांक ssize);
काष्ठा mm_काष्ठा;
अचिन्हित पूर्णांक hash_page_करो_lazy_icache(अचिन्हित पूर्णांक pp, pte_t pte, पूर्णांक trap);
बाह्य पूर्णांक hash_page_mm(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ ea,
			अचिन्हित दीर्घ access, अचिन्हित दीर्घ trap,
			अचिन्हित दीर्घ flags);
बाह्य पूर्णांक hash_page(अचिन्हित दीर्घ ea, अचिन्हित दीर्घ access, अचिन्हित दीर्घ trap,
		     अचिन्हित दीर्घ dsisr);
व्योम low_hash_fault(काष्ठा pt_regs *regs, अचिन्हित दीर्घ address, पूर्णांक rc);
पूर्णांक __hash_page(अचिन्हित दीर्घ trap, अचिन्हित दीर्घ ea, अचिन्हित दीर्घ dsisr, अचिन्हित दीर्घ msr);
पूर्णांक __hash_page_huge(अचिन्हित दीर्घ ea, अचिन्हित दीर्घ access, अचिन्हित दीर्घ vsid,
		     pte_t *ptep, अचिन्हित दीर्घ trap, अचिन्हित दीर्घ flags,
		     पूर्णांक ssize, अचिन्हित पूर्णांक shअगरt, अचिन्हित पूर्णांक mmu_psize);
#अगर_घोषित CONFIG_TRANSPARENT_HUGEPAGE
बाह्य पूर्णांक __hash_page_thp(अचिन्हित दीर्घ ea, अचिन्हित दीर्घ access,
			   अचिन्हित दीर्घ vsid, pmd_t *pmdp, अचिन्हित दीर्घ trap,
			   अचिन्हित दीर्घ flags, पूर्णांक ssize, अचिन्हित पूर्णांक psize);
#अन्यथा
अटल अंतरभूत पूर्णांक __hash_page_thp(अचिन्हित दीर्घ ea, अचिन्हित दीर्घ access,
				  अचिन्हित दीर्घ vsid, pmd_t *pmdp,
				  अचिन्हित दीर्घ trap, अचिन्हित दीर्घ flags,
				  पूर्णांक ssize, अचिन्हित पूर्णांक psize)
अणु
	BUG();
	वापस -1;
पूर्ण
#पूर्ण_अगर
बाह्य व्योम hash_failure_debug(अचिन्हित दीर्घ ea, अचिन्हित दीर्घ access,
			       अचिन्हित दीर्घ vsid, अचिन्हित दीर्घ trap,
			       पूर्णांक ssize, पूर्णांक psize, पूर्णांक lpsize,
			       अचिन्हित दीर्घ pte);
बाह्य पूर्णांक htab_bolt_mapping(अचिन्हित दीर्घ vstart, अचिन्हित दीर्घ vend,
			     अचिन्हित दीर्घ pstart, अचिन्हित दीर्घ prot,
			     पूर्णांक psize, पूर्णांक ssize);
पूर्णांक htab_हटाओ_mapping(अचिन्हित दीर्घ vstart, अचिन्हित दीर्घ vend,
			पूर्णांक psize, पूर्णांक ssize);
बाह्य व्योम pseries_add_gpage(u64 addr, u64 page_size, अचिन्हित दीर्घ number_of_pages);
बाह्य व्योम demote_segment_4k(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr);

बाह्य व्योम hash__setup_new_exec(व्योम);

#अगर_घोषित CONFIG_PPC_PSERIES
व्योम hpte_init_pseries(व्योम);
#अन्यथा
अटल अंतरभूत व्योम hpte_init_pseries(व्योम) अणु पूर्ण
#पूर्ण_अगर

बाह्य व्योम hpte_init_native(व्योम);

काष्ठा slb_entry अणु
	u64	esid;
	u64	vsid;
पूर्ण;

बाह्य व्योम slb_initialize(व्योम);
व्योम slb_flush_and_restore_bolted(व्योम);
व्योम slb_flush_all_realmode(व्योम);
व्योम __slb_restore_bolted_realmode(व्योम);
व्योम slb_restore_bolted_realmode(व्योम);
व्योम slb_save_contents(काष्ठा slb_entry *slb_ptr);
व्योम slb_dump_contents(काष्ठा slb_entry *slb_ptr);

बाह्य व्योम slb_vदो_स्मृति_update(व्योम);
बाह्य व्योम slb_set_size(u16 size);
व्योम preload_new_slb_context(अचिन्हित दीर्घ start, अचिन्हित दीर्घ sp);
#पूर्ण_अगर /* __ASSEMBLY__ */

/*
 * VSID allocation (256MB segment)
 *
 * We first generate a 37-bit "proto-VSID". Proto-VSIDs are generated
 * from mmu context id and effective segment id of the address.
 *
 * For user processes max context id is limited to MAX_USER_CONTEXT.
 * more details in get_user_context
 *
 * For kernel space get_kernel_context
 *
 * The proto-VSIDs are then scrambled पूर्णांकo real VSIDs with the
 * multiplicative hash:
 *
 *	VSID = (proto-VSID * VSID_MULTIPLIER) % VSID_MODULUS
 *
 * VSID_MULTIPLIER is prime, so in particular it is
 * co-prime to VSID_MODULUS, making this a 1:1 scrambling function.
 * Because the modulus is 2^n-1 we can compute it efficiently without
 * a भागide or extra multiply (see below). The scramble function gives
 * robust scattering in the hash table (at least based on some initial
 * results).
 *
 * We use VSID 0 to indicate an invalid VSID. The means we can't use context id
 * 0, because a context id of 0 and an EA of 0 gives a proto-VSID of 0, which
 * will produce a VSID of 0.
 *
 * We also need to aव्योम the last segment of the last context, because that
 * would give a protovsid of 0x1fffffffff. That will result in a VSID 0
 * because of the modulo operation in vsid scramble.
 */

/*
 * Max Va bits we support as of now is 68 bits. We want 19 bit
 * context ID.
 * Restrictions:
 * GPU has restrictions of not able to access beyond 128TB
 * (47 bit effective address). We also cannot करो more than 20bit PID.
 * For p4 and p5 which can only करो 65 bit VA, we restrict our CONTEXT_BITS
 * to 16 bits (ie, we can only have 2^16 pids at the same समय).
 */
#घोषणा VA_BITS			68
#घोषणा CONTEXT_BITS		19
#घोषणा ESID_BITS		(VA_BITS - (SID_SHIFT + CONTEXT_BITS))
#घोषणा ESID_BITS_1T		(VA_BITS - (SID_SHIFT_1T + CONTEXT_BITS))

#घोषणा ESID_BITS_MASK		((1 << ESID_BITS) - 1)
#घोषणा ESID_BITS_1T_MASK	((1 << ESID_BITS_1T) - 1)

/*
 * Now certain config support MAX_PHYSMEM more than 512TB. Hence we will need
 * to use more than one context क्रम linear mapping the kernel.
 * For vदो_स्मृति and memmap, we use just one context with 512TB. With 64 byte
 * काष्ठा page size, we need ony 32 TB in memmap क्रम 2PB (51 bits (MAX_PHYSMEM_BITS)).
 */
#अगर (H_MAX_PHYSMEM_BITS > MAX_EA_BITS_PER_CONTEXT)
#घोषणा MAX_KERNEL_CTX_CNT	(1UL << (H_MAX_PHYSMEM_BITS - MAX_EA_BITS_PER_CONTEXT))
#अन्यथा
#घोषणा MAX_KERNEL_CTX_CNT	1
#पूर्ण_अगर

#घोषणा MAX_VMALLOC_CTX_CNT	1
#घोषणा MAX_IO_CTX_CNT		1
#घोषणा MAX_VMEMMAP_CTX_CNT	1

/*
 * 256MB segment
 * The proto-VSID space has 2^(CONTEX_BITS + ESID_BITS) - 1 segments
 * available क्रम user + kernel mapping. VSID 0 is reserved as invalid, contexts
 * 1-4 are used क्रम kernel mapping. Each segment contains 2^28 bytes. Each
 * context maps 2^49 bytes (512TB).
 *
 * We also need to aव्योम the last segment of the last context, because that
 * would give a protovsid of 0x1fffffffff. That will result in a VSID 0
 * because of the modulo operation in vsid scramble.
 *
 */
#घोषणा MAX_USER_CONTEXT	((ASM_CONST(1) << CONTEXT_BITS) - 2)

// The + 2 accounts क्रम INVALID_REGION and 1 more to aव्योम overlap with kernel
#घोषणा MIN_USER_CONTEXT	(MAX_KERNEL_CTX_CNT + MAX_VMALLOC_CTX_CNT + \
				 MAX_IO_CTX_CNT + MAX_VMEMMAP_CTX_CNT + 2)

/*
 * For platक्रमms that support on 65bit VA we limit the context bits
 */
#घोषणा MAX_USER_CONTEXT_65BIT_VA ((ASM_CONST(1) << (65 - (SID_SHIFT + ESID_BITS))) - 2)

/*
 * This should be computed such that protovosid * vsid_mulitplier
 * करोesn't overflow 64 bits. The vsid_mutliplier should also be
 * co-prime to vsid_modulus. We also need to make sure that number
 * of bits in multiplied result (भागidend) is less than twice the number of
 * protovsid bits क्रम our modulus opपंचांगization to work.
 *
 * The below table shows the current values used.
 * |-------+------------+----------------------+------------+-------------------|
 * |       | Prime Bits | proto VSID_BITS_65VA | Total Bits | 2* prot VSID_BITS |
 * |-------+------------+----------------------+------------+-------------------|
 * | 1T    |         24 |                   25 |         49 |                50 |
 * |-------+------------+----------------------+------------+-------------------|
 * | 256MB |         24 |                   37 |         61 |                74 |
 * |-------+------------+----------------------+------------+-------------------|
 *
 * |-------+------------+----------------------+------------+--------------------|
 * |       | Prime Bits | proto VSID_BITS_68VA | Total Bits | 2* proto VSID_BITS |
 * |-------+------------+----------------------+------------+--------------------|
 * | 1T    |         24 |                   28 |         52 |                 56 |
 * |-------+------------+----------------------+------------+--------------------|
 * | 256MB |         24 |                   40 |         64 |                 80 |
 * |-------+------------+----------------------+------------+--------------------|
 *
 */
#घोषणा VSID_MULTIPLIER_256M	ASM_CONST(12538073)	/* 24-bit prime */
#घोषणा VSID_BITS_256M		(VA_BITS - SID_SHIFT)
#घोषणा VSID_BITS_65_256M	(65 - SID_SHIFT)
/*
 * Modular multiplicative inverse of VSID_MULTIPLIER under modulo VSID_MODULUS
 */
#घोषणा VSID_MULINV_256M	ASM_CONST(665548017062)

#घोषणा VSID_MULTIPLIER_1T	ASM_CONST(12538073)	/* 24-bit prime */
#घोषणा VSID_BITS_1T		(VA_BITS - SID_SHIFT_1T)
#घोषणा VSID_BITS_65_1T		(65 - SID_SHIFT_1T)
#घोषणा VSID_MULINV_1T		ASM_CONST(209034062)

/* 1TB VSID reserved क्रम VRMA */
#घोषणा VRMA_VSID	0x1ffffffUL
#घोषणा USER_VSID_RANGE	(1UL << (ESID_BITS + SID_SHIFT))

/* 4 bits per slice and we have one slice per 1TB */
#घोषणा SLICE_ARRAY_SIZE	(H_PGTABLE_RANGE >> 41)
#घोषणा LOW_SLICE_ARRAY_SZ	(BITS_PER_LONG / BITS_PER_BYTE)
#घोषणा TASK_SLICE_ARRAY_SZ(x)	((x)->hash_context->slb_addr_limit >> 41)
#अगर_अघोषित __ASSEMBLY__

#अगर_घोषित CONFIG_PPC_SUBPAGE_PROT
/*
 * For the sub-page protection option, we extend the PGD with one of
 * these.  Basically we have a 3-level tree, with the top level being
 * the protptrs array.  To optimize speed and memory consumption when
 * only addresses < 4GB are being रक्षित, poपूर्णांकers to the first
 * four pages of sub-page protection words are stored in the low_prot
 * array.
 * Each page of sub-page protection words protects 1GB (4 bytes
 * protects 64k).  For the 3-level tree, each page of poपूर्णांकers then
 * protects 8TB.
 */
काष्ठा subpage_prot_table अणु
	अचिन्हित दीर्घ maxaddr;	/* only addresses < this are रक्षित */
	अचिन्हित पूर्णांक **protptrs[(TASK_SIZE_USER64 >> 43)];
	अचिन्हित पूर्णांक *low_prot[4];
पूर्ण;

#घोषणा SBP_L1_BITS		(PAGE_SHIFT - 2)
#घोषणा SBP_L2_BITS		(PAGE_SHIFT - 3)
#घोषणा SBP_L1_COUNT		(1 << SBP_L1_BITS)
#घोषणा SBP_L2_COUNT		(1 << SBP_L2_BITS)
#घोषणा SBP_L2_SHIFT		(PAGE_SHIFT + SBP_L1_BITS)
#घोषणा SBP_L3_SHIFT		(SBP_L2_SHIFT + SBP_L2_BITS)

बाह्य व्योम subpage_prot_मुक्त(काष्ठा mm_काष्ठा *mm);
#अन्यथा
अटल अंतरभूत व्योम subpage_prot_मुक्त(काष्ठा mm_काष्ठा *mm) अणुपूर्ण
#पूर्ण_अगर /* CONFIG_PPC_SUBPAGE_PROT */

/*
 * One bit per slice. We have lower slices which cover 256MB segments
 * upto 4G range. That माला_लो us 16 low slices. For the rest we track slices
 * in 1TB size.
 */
काष्ठा slice_mask अणु
	u64 low_slices;
	DECLARE_BITMAP(high_slices, SLICE_NUM_HIGH);
पूर्ण;

काष्ठा hash_mm_context अणु
	u16 user_psize; /* page size index */

	/* SLB page size encodings*/
	अचिन्हित अक्षर low_slices_psize[LOW_SLICE_ARRAY_SZ];
	अचिन्हित अक्षर high_slices_psize[SLICE_ARRAY_SIZE];
	अचिन्हित दीर्घ slb_addr_limit;
#अगर_घोषित CONFIG_PPC_64K_PAGES
	काष्ठा slice_mask mask_64k;
#पूर्ण_अगर
	काष्ठा slice_mask mask_4k;
#अगर_घोषित CONFIG_HUGETLB_PAGE
	काष्ठा slice_mask mask_16m;
	काष्ठा slice_mask mask_16g;
#पूर्ण_अगर

#अगर_घोषित CONFIG_PPC_SUBPAGE_PROT
	काष्ठा subpage_prot_table *spt;
#पूर्ण_अगर /* CONFIG_PPC_SUBPAGE_PROT */
पूर्ण;

#अगर 0
/*
 * The code below is equivalent to this function क्रम arguments
 * < 2^VSID_BITS, which is all this should ever be called
 * with.  However gcc is not clever enough to compute the
 * modulus (2^n-1) without a second multiply.
 */
#घोषणा vsid_scramble(protovsid, size) \
	((((protovsid) * VSID_MULTIPLIER_##size) % VSID_MODULUS_##size))

/* simplअगरied क्रमm aव्योमing mod operation */
#घोषणा vsid_scramble(protovsid, size) \
	(अणु								 \
		अचिन्हित दीर्घ x;					 \
		x = (protovsid) * VSID_MULTIPLIER_##size;		 \
		x = (x >> VSID_BITS_##size) + (x & VSID_MODULUS_##size); \
		(x + ((x+1) >> VSID_BITS_##size)) & VSID_MODULUS_##size; \
	पूर्ण)

#अन्यथा /* 1 */
अटल अंतरभूत अचिन्हित दीर्घ vsid_scramble(अचिन्हित दीर्घ protovsid,
				  अचिन्हित दीर्घ vsid_multiplier, पूर्णांक vsid_bits)
अणु
	अचिन्हित दीर्घ vsid;
	अचिन्हित दीर्घ vsid_modulus = ((1UL << vsid_bits) - 1);
	/*
	 * We have same multipler क्रम both 256 and 1T segements now
	 */
	vsid = protovsid * vsid_multiplier;
	vsid = (vsid >> vsid_bits) + (vsid & vsid_modulus);
	वापस (vsid + ((vsid + 1) >> vsid_bits)) & vsid_modulus;
पूर्ण

#पूर्ण_अगर /* 1 */

/* Returns the segment size indicator क्रम a user address */
अटल अंतरभूत पूर्णांक user_segment_size(अचिन्हित दीर्घ addr)
अणु
	/* Use 1T segments अगर possible क्रम addresses >= 1T */
	अगर (addr >= (1UL << SID_SHIFT_1T))
		वापस mmu_highuser_ssize;
	वापस MMU_SEGSIZE_256M;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ get_vsid(अचिन्हित दीर्घ context, अचिन्हित दीर्घ ea,
				     पूर्णांक ssize)
अणु
	अचिन्हित दीर्घ va_bits = VA_BITS;
	अचिन्हित दीर्घ vsid_bits;
	अचिन्हित दीर्घ protovsid;

	/*
	 * Bad address. We वापस VSID 0 क्रम that
	 */
	अगर ((ea & EA_MASK)  >= H_PGTABLE_RANGE)
		वापस 0;

	अगर (!mmu_has_feature(MMU_FTR_68_BIT_VA))
		va_bits = 65;

	अगर (ssize == MMU_SEGSIZE_256M) अणु
		vsid_bits = va_bits - SID_SHIFT;
		protovsid = (context << ESID_BITS) |
			((ea >> SID_SHIFT) & ESID_BITS_MASK);
		वापस vsid_scramble(protovsid, VSID_MULTIPLIER_256M, vsid_bits);
	पूर्ण
	/* 1T segment */
	vsid_bits = va_bits - SID_SHIFT_1T;
	protovsid = (context << ESID_BITS_1T) |
		((ea >> SID_SHIFT_1T) & ESID_BITS_1T_MASK);
	वापस vsid_scramble(protovsid, VSID_MULTIPLIER_1T, vsid_bits);
पूर्ण

/*
 * For kernel space, we use context ids as
 * below. Range is 512TB per context.
 *
 * 0x00001 -  [ 0xc000000000000000 - 0xc001ffffffffffff]
 * 0x00002 -  [ 0xc002000000000000 - 0xc003ffffffffffff]
 * 0x00003 -  [ 0xc004000000000000 - 0xc005ffffffffffff]
 * 0x00004 -  [ 0xc006000000000000 - 0xc007ffffffffffff]
 *
 * vmap, IO, vmemap
 *
 * 0x00005 -  [ 0xc008000000000000 - 0xc009ffffffffffff]
 * 0x00006 -  [ 0xc00a000000000000 - 0xc00bffffffffffff]
 * 0x00007 -  [ 0xc00c000000000000 - 0xc00dffffffffffff]
 *
 */
अटल अंतरभूत अचिन्हित दीर्घ get_kernel_context(अचिन्हित दीर्घ ea)
अणु
	अचिन्हित दीर्घ region_id = get_region_id(ea);
	अचिन्हित दीर्घ ctx;
	/*
	 * Depending on Kernel config, kernel region can have one context
	 * or more.
	 */
	अगर (region_id == LINEAR_MAP_REGION_ID) अणु
		/*
		 * We alपढ़ोy verअगरied ea to be not beyond the addr limit.
		 */
		ctx =  1 + ((ea & EA_MASK) >> MAX_EA_BITS_PER_CONTEXT);
	पूर्ण अन्यथा
		ctx = region_id + MAX_KERNEL_CTX_CNT - 1;
	वापस ctx;
पूर्ण

/*
 * This is only valid क्रम addresses >= PAGE_OFFSET
 */
अटल अंतरभूत अचिन्हित दीर्घ get_kernel_vsid(अचिन्हित दीर्घ ea, पूर्णांक ssize)
अणु
	अचिन्हित दीर्घ context;

	अगर (!is_kernel_addr(ea))
		वापस 0;

	context = get_kernel_context(ea);
	वापस get_vsid(context, ea, ssize);
पूर्ण

अचिन्हित htab_shअगरt_क्रम_mem_size(अचिन्हित दीर्घ mem_size);

क्रमागत slb_index अणु
	LINEAR_INDEX	= 0, /* Kernel linear map  (0xc000000000000000) */
	KSTACK_INDEX	= 1, /* Kernel stack map */
पूर्ण;

#घोषणा slb_esid_mask(ssize)	\
	(((ssize) == MMU_SEGSIZE_256M) ? ESID_MASK : ESID_MASK_1T)

अटल अंतरभूत अचिन्हित दीर्घ mk_esid_data(अचिन्हित दीर्घ ea, पूर्णांक ssize,
					 क्रमागत slb_index index)
अणु
	वापस (ea & slb_esid_mask(ssize)) | SLB_ESID_V | index;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ __mk_vsid_data(अचिन्हित दीर्घ vsid, पूर्णांक ssize,
					   अचिन्हित दीर्घ flags)
अणु
	वापस (vsid << slb_vsid_shअगरt(ssize)) | flags |
		((अचिन्हित दीर्घ)ssize << SLB_VSID_SSIZE_SHIFT);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ mk_vsid_data(अचिन्हित दीर्घ ea, पूर्णांक ssize,
					 अचिन्हित दीर्घ flags)
अणु
	वापस __mk_vsid_data(get_kernel_vsid(ea, ssize), ssize, flags);
पूर्ण

#पूर्ण_अगर /* __ASSEMBLY__ */
#पूर्ण_अगर /* _ASM_POWERPC_BOOK3S_64_MMU_HASH_H_ */
