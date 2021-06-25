<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_POWERPC_BOOK3S_32_MMU_HASH_H_
#घोषणा _ASM_POWERPC_BOOK3S_32_MMU_HASH_H_

/*
 * 32-bit hash table MMU support
 */

/*
 * BATs
 */

/* Block size masks */
#घोषणा BL_128K	0x000
#घोषणा BL_256K 0x001
#घोषणा BL_512K 0x003
#घोषणा BL_1M   0x007
#घोषणा BL_2M   0x00F
#घोषणा BL_4M   0x01F
#घोषणा BL_8M   0x03F
#घोषणा BL_16M  0x07F
#घोषणा BL_32M  0x0FF
#घोषणा BL_64M  0x1FF
#घोषणा BL_128M 0x3FF
#घोषणा BL_256M 0x7FF

/* BAT Access Protection */
#घोषणा BPP_XX	0x00		/* No access */
#घोषणा BPP_RX	0x01		/* Read only */
#घोषणा BPP_RW	0x02		/* Read/ग_लिखो */

#अगर_अघोषित __ASSEMBLY__
/* Contort a phys_addr_t पूर्णांकo the right क्रमmat/bits क्रम a BAT */
#अगर_घोषित CONFIG_PHYS_64BIT
#घोषणा BAT_PHYS_ADDR(x) ((u32)((x & 0x00000000fffe0000ULL) | \
				((x & 0x0000000e00000000ULL) >> 24) | \
				((x & 0x0000000100000000ULL) >> 30)))
#घोषणा PHYS_BAT_ADDR(x) (((u64)(x) & 0x00000000fffe0000ULL) | \
			  (((u64)(x) << 24) & 0x0000000e00000000ULL) | \
			  (((u64)(x) << 30) & 0x0000000100000000ULL))
#अन्यथा
#घोषणा BAT_PHYS_ADDR(x) (x)
#घोषणा PHYS_BAT_ADDR(x) ((x) & 0xfffe0000)
#पूर्ण_अगर

काष्ठा ppc_bat अणु
	u32 batu;
	u32 batl;
पूर्ण;
#पूर्ण_अगर /* !__ASSEMBLY__ */

/*
 * Hash table
 */

/* Values क्रम PP (assumes Ks=0, Kp=1) */
#घोषणा PP_RWXX	0	/* Supervisor पढ़ो/ग_लिखो, User none */
#घोषणा PP_RWRX 1	/* Supervisor पढ़ो/ग_लिखो, User पढ़ो */
#घोषणा PP_RWRW 2	/* Supervisor पढ़ो/ग_लिखो, User पढ़ो/ग_लिखो */
#घोषणा PP_RXRX 3	/* Supervisor पढ़ो,       User पढ़ो */

/* Values क्रम Segment Registers */
#घोषणा SR_NX	0x10000000	/* No Execute */
#घोषणा SR_KP	0x20000000	/* User key */
#घोषणा SR_KS	0x40000000	/* Supervisor key */

#अगर_अघोषित __ASSEMBLY__

/*
 * Hardware Page Table Entry
 * Note that the xpn and x bitfields are used only by processors that
 * support extended addressing; otherwise, those bits are reserved.
 */
काष्ठा hash_pte अणु
	अचिन्हित दीर्घ v:1;	/* Entry is valid */
	अचिन्हित दीर्घ vsid:24;	/* Virtual segment identअगरier */
	अचिन्हित दीर्घ h:1;	/* Hash algorithm indicator */
	अचिन्हित दीर्घ api:6;	/* Abbreviated page index */
	अचिन्हित दीर्घ rpn:20;	/* Real (physical) page number */
	अचिन्हित दीर्घ xpn:3;	/* Real page number bits 0-2, optional */
	अचिन्हित दीर्घ r:1;	/* Referenced */
	अचिन्हित दीर्घ c:1;	/* Changed */
	अचिन्हित दीर्घ w:1;	/* Write-thru cache mode */
	अचिन्हित दीर्घ i:1;	/* Cache inhibited */
	अचिन्हित दीर्घ m:1;	/* Memory coherence */
	अचिन्हित दीर्घ g:1;	/* Guarded */
	अचिन्हित दीर्घ x:1;	/* Real page number bit 3, optional */
	अचिन्हित दीर्घ pp:2;	/* Page protection */
पूर्ण;

प्रकार काष्ठा अणु
	अचिन्हित दीर्घ id;
	व्योम __user *vdso;
पूर्ण mm_context_t;

व्योम update_bats(व्योम);
अटल अंतरभूत व्योम cleanup_cpu_mmu_context(व्योम) अणु पूर्ण

/* patch sites */
बाह्य s32 patch__hash_page_A0, patch__hash_page_A1, patch__hash_page_A2;
बाह्य s32 patch__hash_page_B, patch__hash_page_C;
बाह्य s32 patch__flush_hash_A0, patch__flush_hash_A1, patch__flush_hash_A2;
बाह्य s32 patch__flush_hash_B;

#पूर्ण_अगर /* !__ASSEMBLY__ */

/* We happily ignore the smaller BATs on 601, we करोn't actually use
 * those definitions on hash32 at the moment anyway
 */
#घोषणा mmu_भव_psize	MMU_PAGE_4K
#घोषणा mmu_linear_psize	MMU_PAGE_256M

#पूर्ण_अगर /* _ASM_POWERPC_BOOK3S_32_MMU_HASH_H_ */
