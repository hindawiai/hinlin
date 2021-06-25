<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __MMU_H
#घोषणा __MMU_H

#समावेश <linux/स्थिर.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/hypervisor.h>

#घोषणा CTX_NR_BITS		13

#घोषणा TAG_CONTEXT_BITS	((_AC(1,UL) << CTX_NR_BITS) - _AC(1,UL))

/* UltraSPARC-III+ and later have a feature whereby you can
 * select what page size the various Data-TLB instances in the
 * chip.  In order to gracefully support this, we put the version
 * field in a spot outside of the areas of the context रेजिस्टर
 * where this parameter is specअगरied.
 */
#घोषणा CTX_VERSION_SHIFT	22
#घोषणा CTX_VERSION_MASK	((~0UL) << CTX_VERSION_SHIFT)

#घोषणा CTX_PGSZ_8KB		_AC(0x0,UL)
#घोषणा CTX_PGSZ_64KB		_AC(0x1,UL)
#घोषणा CTX_PGSZ_512KB		_AC(0x2,UL)
#घोषणा CTX_PGSZ_4MB		_AC(0x3,UL)
#घोषणा CTX_PGSZ_BITS		_AC(0x7,UL)
#घोषणा CTX_PGSZ0_NUC_SHIFT	61
#घोषणा CTX_PGSZ1_NUC_SHIFT	58
#घोषणा CTX_PGSZ0_SHIFT		16
#घोषणा CTX_PGSZ1_SHIFT		19
#घोषणा CTX_PGSZ_MASK		((CTX_PGSZ_BITS << CTX_PGSZ0_SHIFT) | \
				 (CTX_PGSZ_BITS << CTX_PGSZ1_SHIFT))

#घोषणा CTX_PGSZ_BASE	CTX_PGSZ_8KB
#घोषणा CTX_PGSZ_HUGE	CTX_PGSZ_4MB
#घोषणा CTX_PGSZ_KERN	CTX_PGSZ_4MB

/* Thus, when running on UltraSPARC-III+ and later, we use the following
 * PRIMARY_CONTEXT रेजिस्टर values क्रम the kernel context.
 */
#घोषणा CTX_CHEETAH_PLUS_NUC \
	((CTX_PGSZ_KERN << CTX_PGSZ0_NUC_SHIFT) | \
	 (CTX_PGSZ_BASE << CTX_PGSZ1_NUC_SHIFT))

#घोषणा CTX_CHEETAH_PLUS_CTX0 \
	((CTX_PGSZ_KERN << CTX_PGSZ0_SHIFT) | \
	 (CTX_PGSZ_BASE << CTX_PGSZ1_SHIFT))

/* If you want "the TLB context number" use CTX_NR_MASK.  If you
 * want "the bits I program into the context registers" use
 * CTX_HW_MASK.
 */
#घोषणा CTX_NR_MASK		TAG_CONTEXT_BITS
#घोषणा CTX_HW_MASK		(CTX_NR_MASK | CTX_PGSZ_MASK)

#घोषणा CTX_FIRST_VERSION	BIT(CTX_VERSION_SHIFT)
#घोषणा CTX_VALID(__ctx)	\
	 (!(((__ctx.sparc64_ctx_val) ^ tlb_context_cache) & CTX_VERSION_MASK))
#घोषणा CTX_HWBITS(__ctx)	((__ctx.sparc64_ctx_val) & CTX_HW_MASK)
#घोषणा CTX_NRBITS(__ctx)	((__ctx.sparc64_ctx_val) & CTX_NR_MASK)

#अगर_अघोषित __ASSEMBLY__

#घोषणा TSB_ENTRY_ALIGNMENT	16

काष्ठा tsb अणु
	अचिन्हित दीर्घ tag;
	अचिन्हित दीर्घ pte;
पूर्ण __attribute__((aligned(TSB_ENTRY_ALIGNMENT)));

व्योम __tsb_insert(अचिन्हित दीर्घ ent, अचिन्हित दीर्घ tag, अचिन्हित दीर्घ pte);
व्योम tsb_flush(अचिन्हित दीर्घ ent, अचिन्हित दीर्घ tag);
व्योम tsb_init(काष्ठा tsb *tsb, अचिन्हित दीर्घ size);

काष्ठा tsb_config अणु
	काष्ठा tsb		*tsb;
	अचिन्हित दीर्घ		tsb_rss_limit;
	अचिन्हित दीर्घ		tsb_nentries;
	अचिन्हित दीर्घ		tsb_reg_val;
	अचिन्हित दीर्घ		tsb_map_vaddr;
	अचिन्हित दीर्घ		tsb_map_pte;
पूर्ण;

#घोषणा MM_TSB_BASE	0

#अगर defined(CONFIG_HUGETLB_PAGE) || defined(CONFIG_TRANSPARENT_HUGEPAGE)
#घोषणा MM_TSB_HUGE	1
#घोषणा MM_NUM_TSBS	2
#अन्यथा
#घोषणा MM_NUM_TSBS	1
#पूर्ण_अगर

/* ADI tags are stored when a page is swapped out and the storage क्रम
 * tags is allocated dynamically. There is a tag storage descriptor
 * associated with each set of tag storage pages. Tag storage descriptors
 * are allocated dynamically. Since kernel will allocate a full page क्रम
 * each tag storage descriptor, we can store up to
 * PAGE_SIZE/माप(tag storage descriptor) descriptors on that page.
 */
प्रकार काष्ठा अणु
	अचिन्हित दीर्घ	start;		/* Start address क्रम this tag storage */
	अचिन्हित दीर्घ	end;		/* Last address क्रम tag storage */
	अचिन्हित अक्षर	*tags;		/* Where the tags are */
	अचिन्हित दीर्घ	tag_users;	/* number of references to descriptor */
पूर्ण tag_storage_desc_t;

प्रकार काष्ठा अणु
	spinlock_t		lock;
	अचिन्हित दीर्घ		sparc64_ctx_val;
	अचिन्हित दीर्घ		hugetlb_pte_count;
	अचिन्हित दीर्घ		thp_pte_count;
	काष्ठा tsb_config	tsb_block[MM_NUM_TSBS];
	काष्ठा hv_tsb_descr	tsb_descr[MM_NUM_TSBS];
	व्योम			*vdso;
	bool			adi;
	tag_storage_desc_t	*tag_store;
	spinlock_t		tag_lock;
पूर्ण mm_context_t;

#पूर्ण_अगर /* !__ASSEMBLY__ */

#घोषणा TSB_CONFIG_TSB		0x00
#घोषणा TSB_CONFIG_RSS_LIMIT	0x08
#घोषणा TSB_CONFIG_NENTRIES	0x10
#घोषणा TSB_CONFIG_REG_VAL	0x18
#घोषणा TSB_CONFIG_MAP_VADDR	0x20
#घोषणा TSB_CONFIG_MAP_PTE	0x28

#पूर्ण_अगर /* __MMU_H */
