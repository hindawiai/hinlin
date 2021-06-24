<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *  S390 version
 *    Copyright IBM Corp. 1999, 2000
 *    Author(s): Harपंचांगut Penner (hp@de.ibm.com)
 *               Ulrich Weigand (weigand@de.ibm.com)
 *               Martin Schwidefsky (schwidefsky@de.ibm.com)
 *
 *  Derived from "include/asm-i386/pgtable.h"
 */

#अगर_अघोषित _ASM_S390_PGTABLE_H
#घोषणा _ASM_S390_PGTABLE_H

#समावेश <linux/sched.h>
#समावेश <linux/mm_types.h>
#समावेश <linux/page-flags.h>
#समावेश <linux/radix-tree.h>
#समावेश <linux/atomic.h>
#समावेश <यंत्र/bug.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/uv.h>

बाह्य pgd_t swapper_pg_dir[];
बाह्य व्योम paging_init(व्योम);
बाह्य अचिन्हित दीर्घ s390_invalid_asce;

क्रमागत अणु
	PG_सूचीECT_MAP_4K = 0,
	PG_सूचीECT_MAP_1M,
	PG_सूचीECT_MAP_2G,
	PG_सूचीECT_MAP_MAX
पूर्ण;

बाह्य atomic_दीर्घ_t direct_pages_count[PG_सूचीECT_MAP_MAX];

अटल अंतरभूत व्योम update_page_count(पूर्णांक level, दीर्घ count)
अणु
	अगर (IS_ENABLED(CONFIG_PROC_FS))
		atomic_दीर्घ_add(count, &direct_pages_count[level]);
पूर्ण

काष्ठा seq_file;
व्योम arch_report_meminfo(काष्ठा seq_file *m);

/*
 * The S390 करोesn't have any बाह्यal MMU info: the kernel page
 * tables contain all the necessary inक्रमmation.
 */
#घोषणा update_mmu_cache(vma, address, ptep)     करो अणु पूर्ण जबतक (0)
#घोषणा update_mmu_cache_pmd(vma, address, ptep) करो अणु पूर्ण जबतक (0)

/*
 * ZERO_PAGE is a global shared page that is always zero; used
 * क्रम zero-mapped memory areas etc..
 */

बाह्य अचिन्हित दीर्घ empty_zero_page;
बाह्य अचिन्हित दीर्घ zero_page_mask;

#घोषणा ZERO_PAGE(vaddr) \
	(virt_to_page((व्योम *)(empty_zero_page + \
	 (((अचिन्हित दीर्घ)(vaddr)) &zero_page_mask))))
#घोषणा __HAVE_COLOR_ZERO_PAGE

/* TODO: s390 cannot support io_remap_pfn_range... */

#घोषणा FIRST_USER_ADDRESS  0UL

#घोषणा pte_ERROR(e) \
	prपूर्णांकk("%s:%d: bad pte %p.\n", __खाता__, __LINE__, (व्योम *) pte_val(e))
#घोषणा pmd_ERROR(e) \
	prपूर्णांकk("%s:%d: bad pmd %p.\n", __खाता__, __LINE__, (व्योम *) pmd_val(e))
#घोषणा pud_ERROR(e) \
	prपूर्णांकk("%s:%d: bad pud %p.\n", __खाता__, __LINE__, (व्योम *) pud_val(e))
#घोषणा p4d_ERROR(e) \
	prपूर्णांकk("%s:%d: bad p4d %p.\n", __खाता__, __LINE__, (व्योम *) p4d_val(e))
#घोषणा pgd_ERROR(e) \
	prपूर्णांकk("%s:%d: bad pgd %p.\n", __खाता__, __LINE__, (व्योम *) pgd_val(e))

/*
 * The vदो_स्मृति and module area will always be on the topmost area of the
 * kernel mapping. 512GB are reserved क्रम vदो_स्मृति by शेष.
 * At the top of the vदो_स्मृति area a 2GB area is reserved where modules
 * will reside. That makes sure that पूर्णांकer module branches always
 * happen without trampolines and in addition the placement within a
 * 2GB frame is branch prediction unit मित्रly.
 */
बाह्य अचिन्हित दीर्घ VMALLOC_START;
बाह्य अचिन्हित दीर्घ VMALLOC_END;
#घोषणा VMALLOC_DEFAULT_SIZE	((512UL << 30) - MODULES_LEN)
बाह्य काष्ठा page *vmemmap;
बाह्य अचिन्हित दीर्घ vmemmap_size;

#घोषणा VMEM_MAX_PHYS ((अचिन्हित दीर्घ) vmemmap)

बाह्य अचिन्हित दीर्घ MODULES_VADDR;
बाह्य अचिन्हित दीर्घ MODULES_END;
#घोषणा MODULES_VADDR	MODULES_VADDR
#घोषणा MODULES_END	MODULES_END
#घोषणा MODULES_LEN	(1UL << 31)

अटल अंतरभूत पूर्णांक is_module_addr(व्योम *addr)
अणु
	BUILD_BUG_ON(MODULES_LEN > (1UL << 31));
	अगर (addr < (व्योम *)MODULES_VADDR)
		वापस 0;
	अगर (addr > (व्योम *)MODULES_END)
		वापस 0;
	वापस 1;
पूर्ण

/*
 * A 64 bit pagetable entry of S390 has following क्रमmat:
 * |			 PFRA			      |0IPC|  OS  |
 * 0000000000111111111122222222223333333333444444444455555555556666
 * 0123456789012345678901234567890123456789012345678901234567890123
 *
 * I Page-Invalid Bit:    Page is not available क्रम address-translation
 * P Page-Protection Bit: Store access not possible क्रम page
 * C Change-bit override: HW is not required to set change bit
 *
 * A 64 bit segmenttable entry of S390 has following क्रमmat:
 * |        P-table origin                              |      TT
 * 0000000000111111111122222222223333333333444444444455555555556666
 * 0123456789012345678901234567890123456789012345678901234567890123
 *
 * I Segment-Invalid Bit:    Segment is not available क्रम address-translation
 * C Common-Segment Bit:     Segment is not निजी (PoP 3-30)
 * P Page-Protection Bit: Store access not possible क्रम page
 * TT Type 00
 *
 * A 64 bit region table entry of S390 has following क्रमmat:
 * |        S-table origin                             |   TF  TTTL
 * 0000000000111111111122222222223333333333444444444455555555556666
 * 0123456789012345678901234567890123456789012345678901234567890123
 *
 * I Segment-Invalid Bit:    Segment is not available क्रम address-translation
 * TT Type 01
 * TF
 * TL Table length
 *
 * The 64 bit regiontable origin of S390 has following क्रमmat:
 * |      region table origon                          |       DTTL
 * 0000000000111111111122222222223333333333444444444455555555556666
 * 0123456789012345678901234567890123456789012345678901234567890123
 *
 * X Space-Switch event:
 * G Segment-Invalid Bit:  
 * P Private-Space Bit:    
 * S Storage-Alteration:
 * R Real space
 * TL Table-Length:
 *
 * A storage key has the following क्रमmat:
 * | ACC |F|R|C|0|
 *  0   3 4 5 6 7
 * ACC: access key
 * F  : fetch protection bit
 * R  : referenced bit
 * C  : changed bit
 */

/* Hardware bits in the page table entry */
#घोषणा _PAGE_NOEXEC	0x100		/* HW no-execute bit  */
#घोषणा _PAGE_PROTECT	0x200		/* HW पढ़ो-only bit  */
#घोषणा _PAGE_INVALID	0x400		/* HW invalid bit    */
#घोषणा _PAGE_LARGE	0x800		/* Bit to mark a large pte */

/* Software bits in the page table entry */
#घोषणा _PAGE_PRESENT	0x001		/* SW pte present bit */
#घोषणा _PAGE_YOUNG	0x004		/* SW pte young bit */
#घोषणा _PAGE_सूचीTY	0x008		/* SW pte dirty bit */
#घोषणा _PAGE_READ	0x010		/* SW pte पढ़ो bit */
#घोषणा _PAGE_WRITE	0x020		/* SW pte ग_लिखो bit */
#घोषणा _PAGE_SPECIAL	0x040		/* SW associated with special page */
#घोषणा _PAGE_UNUSED	0x080		/* SW bit क्रम pgste usage state */

#अगर_घोषित CONFIG_MEM_SOFT_सूचीTY
#घोषणा _PAGE_SOFT_सूचीTY 0x002		/* SW pte soft dirty bit */
#अन्यथा
#घोषणा _PAGE_SOFT_सूचीTY 0x000
#पूर्ण_अगर

/* Set of bits not changed in pte_modअगरy */
#घोषणा _PAGE_CHG_MASK		(PAGE_MASK | _PAGE_SPECIAL | _PAGE_सूचीTY | \
				 _PAGE_YOUNG | _PAGE_SOFT_सूचीTY)

/*
 * handle_pte_fault uses pte_present and pte_none to find out the pte type
 * WITHOUT holding the page table lock. The _PAGE_PRESENT bit is used to
 * distinguish present from not-present ptes. It is changed only with the page
 * table lock held.
 *
 * The following table gives the dअगरferent possible bit combinations क्रम
 * the pte hardware and software bits in the last 12 bits of a pte
 * (. unasचिन्हित bit, x करोn't care, t swap type):
 *
 *				842100000000
 *				000084210000
 *				000000008421
 *				.IR.uswrdy.p
 * empty			.10.00000000
 * swap				.11..ttttt.0
 * prot-none, clean, old	.11.xx0000.1
 * prot-none, clean, young	.11.xx0001.1
 * prot-none, dirty, old	.11.xx0010.1
 * prot-none, dirty, young	.11.xx0011.1
 * पढ़ो-only, clean, old	.11.xx0100.1
 * पढ़ो-only, clean, young	.01.xx0101.1
 * पढ़ो-only, dirty, old	.11.xx0110.1
 * पढ़ो-only, dirty, young	.01.xx0111.1
 * पढ़ो-ग_लिखो, clean, old	.11.xx1100.1
 * पढ़ो-ग_लिखो, clean, young	.01.xx1101.1
 * पढ़ो-ग_लिखो, dirty, old	.10.xx1110.1
 * पढ़ो-ग_लिखो, dirty, young	.00.xx1111.1
 * HW-bits: R पढ़ो-only, I invalid
 * SW-bits: p present, y young, d dirty, r पढ़ो, w ग_लिखो, s special,
 *	    u unused, l large
 *
 * pte_none    is true क्रम the bit pattern .10.00000000, pte == 0x400
 * pte_swap    is true क्रम the bit pattern .11..ooooo.0, (pte & 0x201) == 0x200
 * pte_present is true क्रम the bit pattern .xx.xxxxxx.1, (pte & 0x001) == 0x001
 */

/* Bits in the segment/region table address-space-control-element */
#घोषणा _ASCE_ORIGIN		~0xfffUL/* region/segment table origin	    */
#घोषणा _ASCE_PRIVATE_SPACE	0x100	/* निजी space control	    */
#घोषणा _ASCE_ALT_EVENT		0x80	/* storage alteration event control */
#घोषणा _ASCE_SPACE_SWITCH	0x40	/* space चयन event		    */
#घोषणा _ASCE_REAL_SPACE	0x20	/* real space control		    */
#घोषणा _ASCE_TYPE_MASK		0x0c	/* asce table type mask		    */
#घोषणा _ASCE_TYPE_REGION1	0x0c	/* region first table type	    */
#घोषणा _ASCE_TYPE_REGION2	0x08	/* region second table type	    */
#घोषणा _ASCE_TYPE_REGION3	0x04	/* region third table type	    */
#घोषणा _ASCE_TYPE_SEGMENT	0x00	/* segment table type		    */
#घोषणा _ASCE_TABLE_LENGTH	0x03	/* region table length		    */

/* Bits in the region table entry */
#घोषणा _REGION_ENTRY_ORIGIN	~0xfffUL/* region/segment table origin	    */
#घोषणा _REGION_ENTRY_PROTECT	0x200	/* region protection bit	    */
#घोषणा _REGION_ENTRY_NOEXEC	0x100	/* region no-execute bit	    */
#घोषणा _REGION_ENTRY_OFFSET	0xc0	/* region table offset		    */
#घोषणा _REGION_ENTRY_INVALID	0x20	/* invalid region table entry	    */
#घोषणा _REGION_ENTRY_TYPE_MASK	0x0c	/* region table type mask	    */
#घोषणा _REGION_ENTRY_TYPE_R1	0x0c	/* region first table type	    */
#घोषणा _REGION_ENTRY_TYPE_R2	0x08	/* region second table type	    */
#घोषणा _REGION_ENTRY_TYPE_R3	0x04	/* region third table type	    */
#घोषणा _REGION_ENTRY_LENGTH	0x03	/* region third length		    */

#घोषणा _REGION1_ENTRY		(_REGION_ENTRY_TYPE_R1 | _REGION_ENTRY_LENGTH)
#घोषणा _REGION1_ENTRY_EMPTY	(_REGION_ENTRY_TYPE_R1 | _REGION_ENTRY_INVALID)
#घोषणा _REGION2_ENTRY		(_REGION_ENTRY_TYPE_R2 | _REGION_ENTRY_LENGTH)
#घोषणा _REGION2_ENTRY_EMPTY	(_REGION_ENTRY_TYPE_R2 | _REGION_ENTRY_INVALID)
#घोषणा _REGION3_ENTRY		(_REGION_ENTRY_TYPE_R3 | _REGION_ENTRY_LENGTH)
#घोषणा _REGION3_ENTRY_EMPTY	(_REGION_ENTRY_TYPE_R3 | _REGION_ENTRY_INVALID)

#घोषणा _REGION3_ENTRY_ORIGIN_LARGE ~0x7fffffffUL /* large page address	     */
#घोषणा _REGION3_ENTRY_सूचीTY	0x2000	/* SW region dirty bit */
#घोषणा _REGION3_ENTRY_YOUNG	0x1000	/* SW region young bit */
#घोषणा _REGION3_ENTRY_LARGE	0x0400	/* RTTE-क्रमmat control, large page  */
#घोषणा _REGION3_ENTRY_READ	0x0002	/* SW region पढ़ो bit */
#घोषणा _REGION3_ENTRY_WRITE	0x0001	/* SW region ग_लिखो bit */

#अगर_घोषित CONFIG_MEM_SOFT_सूचीTY
#घोषणा _REGION3_ENTRY_SOFT_सूचीTY 0x4000 /* SW region soft dirty bit */
#अन्यथा
#घोषणा _REGION3_ENTRY_SOFT_सूचीTY 0x0000 /* SW region soft dirty bit */
#पूर्ण_अगर

#घोषणा _REGION_ENTRY_BITS	 0xfffffffffffff22fUL

/* Bits in the segment table entry */
#घोषणा _SEGMENT_ENTRY_BITS			0xfffffffffffffe33UL
#घोषणा _SEGMENT_ENTRY_HARDWARE_BITS		0xfffffffffffffe30UL
#घोषणा _SEGMENT_ENTRY_HARDWARE_BITS_LARGE	0xfffffffffff00730UL
#घोषणा _SEGMENT_ENTRY_ORIGIN_LARGE ~0xfffffUL /* large page address	    */
#घोषणा _SEGMENT_ENTRY_ORIGIN	~0x7ffUL/* page table origin		    */
#घोषणा _SEGMENT_ENTRY_PROTECT	0x200	/* segment protection bit	    */
#घोषणा _SEGMENT_ENTRY_NOEXEC	0x100	/* segment no-execute bit	    */
#घोषणा _SEGMENT_ENTRY_INVALID	0x20	/* invalid segment table entry	    */
#घोषणा _SEGMENT_ENTRY_TYPE_MASK 0x0c	/* segment table type mask	    */

#घोषणा _SEGMENT_ENTRY		(0)
#घोषणा _SEGMENT_ENTRY_EMPTY	(_SEGMENT_ENTRY_INVALID)

#घोषणा _SEGMENT_ENTRY_सूचीTY	0x2000	/* SW segment dirty bit */
#घोषणा _SEGMENT_ENTRY_YOUNG	0x1000	/* SW segment young bit */
#घोषणा _SEGMENT_ENTRY_LARGE	0x0400	/* STE-क्रमmat control, large page */
#घोषणा _SEGMENT_ENTRY_WRITE	0x0002	/* SW segment ग_लिखो bit */
#घोषणा _SEGMENT_ENTRY_READ	0x0001	/* SW segment पढ़ो bit */

#अगर_घोषित CONFIG_MEM_SOFT_सूचीTY
#घोषणा _SEGMENT_ENTRY_SOFT_सूचीTY 0x4000 /* SW segment soft dirty bit */
#अन्यथा
#घोषणा _SEGMENT_ENTRY_SOFT_सूचीTY 0x0000 /* SW segment soft dirty bit */
#पूर्ण_अगर

#घोषणा _CRST_ENTRIES	2048	/* number of region/segment table entries */
#घोषणा _PAGE_ENTRIES	256	/* number of page table entries	*/

#घोषणा _CRST_TABLE_SIZE (_CRST_ENTRIES * 8)
#घोषणा _PAGE_TABLE_SIZE (_PAGE_ENTRIES * 8)

#घोषणा _REGION1_SHIFT	53
#घोषणा _REGION2_SHIFT	42
#घोषणा _REGION3_SHIFT	31
#घोषणा _SEGMENT_SHIFT	20

#घोषणा _REGION1_INDEX	(0x7ffUL << _REGION1_SHIFT)
#घोषणा _REGION2_INDEX	(0x7ffUL << _REGION2_SHIFT)
#घोषणा _REGION3_INDEX	(0x7ffUL << _REGION3_SHIFT)
#घोषणा _SEGMENT_INDEX	(0x7ffUL << _SEGMENT_SHIFT)
#घोषणा _PAGE_INDEX	(0xffUL  << _PAGE_SHIFT)

#घोषणा _REGION1_SIZE	(1UL << _REGION1_SHIFT)
#घोषणा _REGION2_SIZE	(1UL << _REGION2_SHIFT)
#घोषणा _REGION3_SIZE	(1UL << _REGION3_SHIFT)
#घोषणा _SEGMENT_SIZE	(1UL << _SEGMENT_SHIFT)

#घोषणा _REGION1_MASK	(~(_REGION1_SIZE - 1))
#घोषणा _REGION2_MASK	(~(_REGION2_SIZE - 1))
#घोषणा _REGION3_MASK	(~(_REGION3_SIZE - 1))
#घोषणा _SEGMENT_MASK	(~(_SEGMENT_SIZE - 1))

#घोषणा PMD_SHIFT	_SEGMENT_SHIFT
#घोषणा PUD_SHIFT	_REGION3_SHIFT
#घोषणा P4D_SHIFT	_REGION2_SHIFT
#घोषणा PGसूची_SHIFT	_REGION1_SHIFT

#घोषणा PMD_SIZE	_SEGMENT_SIZE
#घोषणा PUD_SIZE	_REGION3_SIZE
#घोषणा P4D_SIZE	_REGION2_SIZE
#घोषणा PGसूची_SIZE	_REGION1_SIZE

#घोषणा PMD_MASK	_SEGMENT_MASK
#घोषणा PUD_MASK	_REGION3_MASK
#घोषणा P4D_MASK	_REGION2_MASK
#घोषणा PGसूची_MASK	_REGION1_MASK

#घोषणा PTRS_PER_PTE	_PAGE_ENTRIES
#घोषणा PTRS_PER_PMD	_CRST_ENTRIES
#घोषणा PTRS_PER_PUD	_CRST_ENTRIES
#घोषणा PTRS_PER_P4D	_CRST_ENTRIES
#घोषणा PTRS_PER_PGD	_CRST_ENTRIES

#घोषणा MAX_PTRS_PER_P4D	PTRS_PER_P4D

/*
 * Segment table and region3 table entry encoding
 * (R = पढ़ो-only, I = invalid, y = young bit):
 *				dy..R...I...wr
 * prot-none, clean, old	00..1...1...00
 * prot-none, clean, young	01..1...1...00
 * prot-none, dirty, old	10..1...1...00
 * prot-none, dirty, young	11..1...1...00
 * पढ़ो-only, clean, old	00..1...1...01
 * पढ़ो-only, clean, young	01..1...0...01
 * पढ़ो-only, dirty, old	10..1...1...01
 * पढ़ो-only, dirty, young	11..1...0...01
 * पढ़ो-ग_लिखो, clean, old	00..1...1...11
 * पढ़ो-ग_लिखो, clean, young	01..1...0...11
 * पढ़ो-ग_लिखो, dirty, old	10..0...1...11
 * पढ़ो-ग_लिखो, dirty, young	11..0...0...11
 * The segment table origin is used to distinguish empty (origin==0) from
 * पढ़ो-ग_लिखो, old segment table entries (origin!=0)
 * HW-bits: R पढ़ो-only, I invalid
 * SW-bits: y young, d dirty, r पढ़ो, w ग_लिखो
 */

/* Page status table bits क्रम भवization */
#घोषणा PGSTE_ACC_BITS	0xf000000000000000UL
#घोषणा PGSTE_FP_BIT	0x0800000000000000UL
#घोषणा PGSTE_PCL_BIT	0x0080000000000000UL
#घोषणा PGSTE_HR_BIT	0x0040000000000000UL
#घोषणा PGSTE_HC_BIT	0x0020000000000000UL
#घोषणा PGSTE_GR_BIT	0x0004000000000000UL
#घोषणा PGSTE_GC_BIT	0x0002000000000000UL
#घोषणा PGSTE_UC_BIT	0x0000800000000000UL	/* user dirty (migration) */
#घोषणा PGSTE_IN_BIT	0x0000400000000000UL	/* IPTE notअगरy bit */
#घोषणा PGSTE_VSIE_BIT	0x0000200000000000UL	/* ref'd in a shaकरोw table */

/* Guest Page State used क्रम भवization */
#घोषणा _PGSTE_GPS_ZERO			0x0000000080000000UL
#घोषणा _PGSTE_GPS_NODAT		0x0000000040000000UL
#घोषणा _PGSTE_GPS_USAGE_MASK		0x0000000003000000UL
#घोषणा _PGSTE_GPS_USAGE_STABLE		0x0000000000000000UL
#घोषणा _PGSTE_GPS_USAGE_UNUSED		0x0000000001000000UL
#घोषणा _PGSTE_GPS_USAGE_POT_VOLATILE	0x0000000002000000UL
#घोषणा _PGSTE_GPS_USAGE_VOLATILE	_PGSTE_GPS_USAGE_MASK

/*
 * A user page table poपूर्णांकer has the space-चयन-event bit, the
 * निजी-space-control bit and the storage-alteration-event-control
 * bit set. A kernel page table poपूर्णांकer करोesn't need them.
 */
#घोषणा _ASCE_USER_BITS		(_ASCE_SPACE_SWITCH | _ASCE_PRIVATE_SPACE | \
				 _ASCE_ALT_EVENT)

/*
 * Page protection definitions.
 */
#घोषणा PAGE_NONE	__pgprot(_PAGE_PRESENT | _PAGE_INVALID | _PAGE_PROTECT)
#घोषणा PAGE_RO		__pgprot(_PAGE_PRESENT | _PAGE_READ | \
				 _PAGE_NOEXEC  | _PAGE_INVALID | _PAGE_PROTECT)
#घोषणा PAGE_RX		__pgprot(_PAGE_PRESENT | _PAGE_READ | \
				 _PAGE_INVALID | _PAGE_PROTECT)
#घोषणा PAGE_RW		__pgprot(_PAGE_PRESENT | _PAGE_READ | _PAGE_WRITE | \
				 _PAGE_NOEXEC  | _PAGE_INVALID | _PAGE_PROTECT)
#घोषणा PAGE_RWX	__pgprot(_PAGE_PRESENT | _PAGE_READ | _PAGE_WRITE | \
				 _PAGE_INVALID | _PAGE_PROTECT)

#घोषणा PAGE_SHARED	__pgprot(_PAGE_PRESENT | _PAGE_READ | _PAGE_WRITE | \
				 _PAGE_YOUNG | _PAGE_सूचीTY | _PAGE_NOEXEC)
#घोषणा PAGE_KERNEL	__pgprot(_PAGE_PRESENT | _PAGE_READ | _PAGE_WRITE | \
				 _PAGE_YOUNG | _PAGE_सूचीTY | _PAGE_NOEXEC)
#घोषणा PAGE_KERNEL_RO	__pgprot(_PAGE_PRESENT | _PAGE_READ | _PAGE_YOUNG | \
				 _PAGE_PROTECT | _PAGE_NOEXEC)
#घोषणा PAGE_KERNEL_EXEC __pgprot(_PAGE_PRESENT | _PAGE_READ | _PAGE_WRITE | \
				  _PAGE_YOUNG |	_PAGE_सूचीTY)

/*
 * On s390 the page table entry has an invalid bit and a पढ़ो-only bit.
 * Read permission implies execute permission and ग_लिखो permission
 * implies पढ़ो permission.
 */
         /*xwr*/
#घोषणा __P000	PAGE_NONE
#घोषणा __P001	PAGE_RO
#घोषणा __P010	PAGE_RO
#घोषणा __P011	PAGE_RO
#घोषणा __P100	PAGE_RX
#घोषणा __P101	PAGE_RX
#घोषणा __P110	PAGE_RX
#घोषणा __P111	PAGE_RX

#घोषणा __S000	PAGE_NONE
#घोषणा __S001	PAGE_RO
#घोषणा __S010	PAGE_RW
#घोषणा __S011	PAGE_RW
#घोषणा __S100	PAGE_RX
#घोषणा __S101	PAGE_RX
#घोषणा __S110	PAGE_RWX
#घोषणा __S111	PAGE_RWX

/*
 * Segment entry (large page) protection definitions.
 */
#घोषणा SEGMENT_NONE	__pgprot(_SEGMENT_ENTRY_INVALID | \
				 _SEGMENT_ENTRY_PROTECT)
#घोषणा SEGMENT_RO	__pgprot(_SEGMENT_ENTRY_PROTECT | \
				 _SEGMENT_ENTRY_READ | \
				 _SEGMENT_ENTRY_NOEXEC)
#घोषणा SEGMENT_RX	__pgprot(_SEGMENT_ENTRY_PROTECT | \
				 _SEGMENT_ENTRY_READ)
#घोषणा SEGMENT_RW	__pgprot(_SEGMENT_ENTRY_READ | \
				 _SEGMENT_ENTRY_WRITE | \
				 _SEGMENT_ENTRY_NOEXEC)
#घोषणा SEGMENT_RWX	__pgprot(_SEGMENT_ENTRY_READ | \
				 _SEGMENT_ENTRY_WRITE)
#घोषणा SEGMENT_KERNEL	__pgprot(_SEGMENT_ENTRY |	\
				 _SEGMENT_ENTRY_LARGE |	\
				 _SEGMENT_ENTRY_READ |	\
				 _SEGMENT_ENTRY_WRITE | \
				 _SEGMENT_ENTRY_YOUNG | \
				 _SEGMENT_ENTRY_सूचीTY | \
				 _SEGMENT_ENTRY_NOEXEC)
#घोषणा SEGMENT_KERNEL_RO __pgprot(_SEGMENT_ENTRY |	\
				 _SEGMENT_ENTRY_LARGE |	\
				 _SEGMENT_ENTRY_READ |	\
				 _SEGMENT_ENTRY_YOUNG |	\
				 _SEGMENT_ENTRY_PROTECT | \
				 _SEGMENT_ENTRY_NOEXEC)
#घोषणा SEGMENT_KERNEL_EXEC __pgprot(_SEGMENT_ENTRY |	\
				 _SEGMENT_ENTRY_LARGE |	\
				 _SEGMENT_ENTRY_READ |	\
				 _SEGMENT_ENTRY_WRITE | \
				 _SEGMENT_ENTRY_YOUNG |	\
				 _SEGMENT_ENTRY_सूचीTY)

/*
 * Region3 entry (large page) protection definitions.
 */

#घोषणा REGION3_KERNEL	__pgprot(_REGION_ENTRY_TYPE_R3 | \
				 _REGION3_ENTRY_LARGE |	 \
				 _REGION3_ENTRY_READ |	 \
				 _REGION3_ENTRY_WRITE |	 \
				 _REGION3_ENTRY_YOUNG |	 \
				 _REGION3_ENTRY_सूचीTY | \
				 _REGION_ENTRY_NOEXEC)
#घोषणा REGION3_KERNEL_RO __pgprot(_REGION_ENTRY_TYPE_R3 | \
				   _REGION3_ENTRY_LARGE |  \
				   _REGION3_ENTRY_READ |   \
				   _REGION3_ENTRY_YOUNG |  \
				   _REGION_ENTRY_PROTECT | \
				   _REGION_ENTRY_NOEXEC)

अटल अंतरभूत bool mm_p4d_folded(काष्ठा mm_काष्ठा *mm)
अणु
	वापस mm->context.asce_limit <= _REGION1_SIZE;
पूर्ण
#घोषणा mm_p4d_folded(mm) mm_p4d_folded(mm)

अटल अंतरभूत bool mm_pud_folded(काष्ठा mm_काष्ठा *mm)
अणु
	वापस mm->context.asce_limit <= _REGION2_SIZE;
पूर्ण
#घोषणा mm_pud_folded(mm) mm_pud_folded(mm)

अटल अंतरभूत bool mm_pmd_folded(काष्ठा mm_काष्ठा *mm)
अणु
	वापस mm->context.asce_limit <= _REGION3_SIZE;
पूर्ण
#घोषणा mm_pmd_folded(mm) mm_pmd_folded(mm)

अटल अंतरभूत पूर्णांक mm_has_pgste(काष्ठा mm_काष्ठा *mm)
अणु
#अगर_घोषित CONFIG_PGSTE
	अगर (unlikely(mm->context.has_pgste))
		वापस 1;
#पूर्ण_अगर
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक mm_is_रक्षित(काष्ठा mm_काष्ठा *mm)
अणु
#अगर_घोषित CONFIG_PGSTE
	अगर (unlikely(atomic_पढ़ो(&mm->context.is_रक्षित)))
		वापस 1;
#पूर्ण_अगर
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक mm_alloc_pgste(काष्ठा mm_काष्ठा *mm)
अणु
#अगर_घोषित CONFIG_PGSTE
	अगर (unlikely(mm->context.alloc_pgste))
		वापस 1;
#पूर्ण_अगर
	वापस 0;
पूर्ण

/*
 * In the हाल that a guest uses storage keys
 * faults should no दीर्घer be backed by zero pages
 */
#घोषणा mm_क्रमbids_zeropage mm_has_pgste
अटल अंतरभूत पूर्णांक mm_uses_skeys(काष्ठा mm_काष्ठा *mm)
अणु
#अगर_घोषित CONFIG_PGSTE
	अगर (mm->context.uses_skeys)
		वापस 1;
#पूर्ण_अगर
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम csp(अचिन्हित पूर्णांक *ptr, अचिन्हित पूर्णांक old, अचिन्हित पूर्णांक new)
अणु
	रेजिस्टर अचिन्हित दीर्घ reg2 यंत्र("2") = old;
	रेजिस्टर अचिन्हित दीर्घ reg3 यंत्र("3") = new;
	अचिन्हित दीर्घ address = (अचिन्हित दीर्घ)ptr | 1;

	यंत्र अस्थिर(
		"	csp	%0,%3"
		: "+d" (reg2), "+m" (*ptr)
		: "d" (reg3), "d" (address)
		: "cc");
पूर्ण

अटल अंतरभूत व्योम cspg(अचिन्हित दीर्घ *ptr, अचिन्हित दीर्घ old, अचिन्हित दीर्घ new)
अणु
	रेजिस्टर अचिन्हित दीर्घ reg2 यंत्र("2") = old;
	रेजिस्टर अचिन्हित दीर्घ reg3 यंत्र("3") = new;
	अचिन्हित दीर्घ address = (अचिन्हित दीर्घ)ptr | 1;

	यंत्र अस्थिर(
		"	.insn	rre,0xb98a0000,%0,%3"
		: "+d" (reg2), "+m" (*ptr)
		: "d" (reg3), "d" (address)
		: "cc");
पूर्ण

#घोषणा CRDTE_DTT_PAGE		0x00UL
#घोषणा CRDTE_DTT_SEGMENT	0x10UL
#घोषणा CRDTE_DTT_REGION3	0x14UL
#घोषणा CRDTE_DTT_REGION2	0x18UL
#घोषणा CRDTE_DTT_REGION1	0x1cUL

अटल अंतरभूत व्योम crdte(अचिन्हित दीर्घ old, अचिन्हित दीर्घ new,
			 अचिन्हित दीर्घ table, अचिन्हित दीर्घ dtt,
			 अचिन्हित दीर्घ address, अचिन्हित दीर्घ asce)
अणु
	रेजिस्टर अचिन्हित दीर्घ reg2 यंत्र("2") = old;
	रेजिस्टर अचिन्हित दीर्घ reg3 यंत्र("3") = new;
	रेजिस्टर अचिन्हित दीर्घ reg4 यंत्र("4") = table | dtt;
	रेजिस्टर अचिन्हित दीर्घ reg5 यंत्र("5") = address;

	यंत्र अस्थिर(".insn rrf,0xb98f0000,%0,%2,%4,0"
		     : "+d" (reg2)
		     : "d" (reg3), "d" (reg4), "d" (reg5), "a" (asce)
		     : "memory", "cc");
पूर्ण

/*
 * pgd/p4d/pud/pmd/pte query functions
 */
अटल अंतरभूत पूर्णांक pgd_folded(pgd_t pgd)
अणु
	वापस (pgd_val(pgd) & _REGION_ENTRY_TYPE_MASK) < _REGION_ENTRY_TYPE_R1;
पूर्ण

अटल अंतरभूत पूर्णांक pgd_present(pgd_t pgd)
अणु
	अगर (pgd_folded(pgd))
		वापस 1;
	वापस (pgd_val(pgd) & _REGION_ENTRY_ORIGIN) != 0UL;
पूर्ण

अटल अंतरभूत पूर्णांक pgd_none(pgd_t pgd)
अणु
	अगर (pgd_folded(pgd))
		वापस 0;
	वापस (pgd_val(pgd) & _REGION_ENTRY_INVALID) != 0UL;
पूर्ण

अटल अंतरभूत पूर्णांक pgd_bad(pgd_t pgd)
अणु
	अगर ((pgd_val(pgd) & _REGION_ENTRY_TYPE_MASK) < _REGION_ENTRY_TYPE_R1)
		वापस 0;
	वापस (pgd_val(pgd) & ~_REGION_ENTRY_BITS) != 0;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ pgd_pfn(pgd_t pgd)
अणु
	अचिन्हित दीर्घ origin_mask;

	origin_mask = _REGION_ENTRY_ORIGIN;
	वापस (pgd_val(pgd) & origin_mask) >> PAGE_SHIFT;
पूर्ण

अटल अंतरभूत पूर्णांक p4d_folded(p4d_t p4d)
अणु
	वापस (p4d_val(p4d) & _REGION_ENTRY_TYPE_MASK) < _REGION_ENTRY_TYPE_R2;
पूर्ण

अटल अंतरभूत पूर्णांक p4d_present(p4d_t p4d)
अणु
	अगर (p4d_folded(p4d))
		वापस 1;
	वापस (p4d_val(p4d) & _REGION_ENTRY_ORIGIN) != 0UL;
पूर्ण

अटल अंतरभूत पूर्णांक p4d_none(p4d_t p4d)
अणु
	अगर (p4d_folded(p4d))
		वापस 0;
	वापस p4d_val(p4d) == _REGION2_ENTRY_EMPTY;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ p4d_pfn(p4d_t p4d)
अणु
	अचिन्हित दीर्घ origin_mask;

	origin_mask = _REGION_ENTRY_ORIGIN;
	वापस (p4d_val(p4d) & origin_mask) >> PAGE_SHIFT;
पूर्ण

अटल अंतरभूत पूर्णांक pud_folded(pud_t pud)
अणु
	वापस (pud_val(pud) & _REGION_ENTRY_TYPE_MASK) < _REGION_ENTRY_TYPE_R3;
पूर्ण

अटल अंतरभूत पूर्णांक pud_present(pud_t pud)
अणु
	अगर (pud_folded(pud))
		वापस 1;
	वापस (pud_val(pud) & _REGION_ENTRY_ORIGIN) != 0UL;
पूर्ण

अटल अंतरभूत पूर्णांक pud_none(pud_t pud)
अणु
	अगर (pud_folded(pud))
		वापस 0;
	वापस pud_val(pud) == _REGION3_ENTRY_EMPTY;
पूर्ण

#घोषणा pud_leaf	pud_large
अटल अंतरभूत पूर्णांक pud_large(pud_t pud)
अणु
	अगर ((pud_val(pud) & _REGION_ENTRY_TYPE_MASK) != _REGION_ENTRY_TYPE_R3)
		वापस 0;
	वापस !!(pud_val(pud) & _REGION3_ENTRY_LARGE);
पूर्ण

#घोषणा pmd_leaf	pmd_large
अटल अंतरभूत पूर्णांक pmd_large(pmd_t pmd)
अणु
	वापस (pmd_val(pmd) & _SEGMENT_ENTRY_LARGE) != 0;
पूर्ण

अटल अंतरभूत पूर्णांक pmd_bad(pmd_t pmd)
अणु
	अगर ((pmd_val(pmd) & _SEGMENT_ENTRY_TYPE_MASK) > 0 || pmd_large(pmd))
		वापस 1;
	वापस (pmd_val(pmd) & ~_SEGMENT_ENTRY_BITS) != 0;
पूर्ण

अटल अंतरभूत पूर्णांक pud_bad(pud_t pud)
अणु
	अचिन्हित दीर्घ type = pud_val(pud) & _REGION_ENTRY_TYPE_MASK;

	अगर (type > _REGION_ENTRY_TYPE_R3 || pud_large(pud))
		वापस 1;
	अगर (type < _REGION_ENTRY_TYPE_R3)
		वापस 0;
	वापस (pud_val(pud) & ~_REGION_ENTRY_BITS) != 0;
पूर्ण

अटल अंतरभूत पूर्णांक p4d_bad(p4d_t p4d)
अणु
	अचिन्हित दीर्घ type = p4d_val(p4d) & _REGION_ENTRY_TYPE_MASK;

	अगर (type > _REGION_ENTRY_TYPE_R2)
		वापस 1;
	अगर (type < _REGION_ENTRY_TYPE_R2)
		वापस 0;
	वापस (p4d_val(p4d) & ~_REGION_ENTRY_BITS) != 0;
पूर्ण

अटल अंतरभूत पूर्णांक pmd_present(pmd_t pmd)
अणु
	वापस pmd_val(pmd) != _SEGMENT_ENTRY_EMPTY;
पूर्ण

अटल अंतरभूत पूर्णांक pmd_none(pmd_t pmd)
अणु
	वापस pmd_val(pmd) == _SEGMENT_ENTRY_EMPTY;
पूर्ण

#घोषणा pmd_ग_लिखो pmd_ग_लिखो
अटल अंतरभूत पूर्णांक pmd_ग_लिखो(pmd_t pmd)
अणु
	वापस (pmd_val(pmd) & _SEGMENT_ENTRY_WRITE) != 0;
पूर्ण

#घोषणा pud_ग_लिखो pud_ग_लिखो
अटल अंतरभूत पूर्णांक pud_ग_लिखो(pud_t pud)
अणु
	वापस (pud_val(pud) & _REGION3_ENTRY_WRITE) != 0;
पूर्ण

अटल अंतरभूत पूर्णांक pmd_dirty(pmd_t pmd)
अणु
	वापस (pmd_val(pmd) & _SEGMENT_ENTRY_सूचीTY) != 0;
पूर्ण

अटल अंतरभूत पूर्णांक pmd_young(pmd_t pmd)
अणु
	वापस (pmd_val(pmd) & _SEGMENT_ENTRY_YOUNG) != 0;
पूर्ण

अटल अंतरभूत पूर्णांक pte_present(pte_t pte)
अणु
	/* Bit pattern: (pte & 0x001) == 0x001 */
	वापस (pte_val(pte) & _PAGE_PRESENT) != 0;
पूर्ण

अटल अंतरभूत पूर्णांक pte_none(pte_t pte)
अणु
	/* Bit pattern: pte == 0x400 */
	वापस pte_val(pte) == _PAGE_INVALID;
पूर्ण

अटल अंतरभूत पूर्णांक pte_swap(pte_t pte)
अणु
	/* Bit pattern: (pte & 0x201) == 0x200 */
	वापस (pte_val(pte) & (_PAGE_PROTECT | _PAGE_PRESENT))
		== _PAGE_PROTECT;
पूर्ण

अटल अंतरभूत पूर्णांक pte_special(pte_t pte)
अणु
	वापस (pte_val(pte) & _PAGE_SPECIAL);
पूर्ण

#घोषणा __HAVE_ARCH_PTE_SAME
अटल अंतरभूत पूर्णांक pte_same(pte_t a, pte_t b)
अणु
	वापस pte_val(a) == pte_val(b);
पूर्ण

#अगर_घोषित CONFIG_NUMA_BALANCING
अटल अंतरभूत पूर्णांक pte_protnone(pte_t pte)
अणु
	वापस pte_present(pte) && !(pte_val(pte) & _PAGE_READ);
पूर्ण

अटल अंतरभूत पूर्णांक pmd_protnone(pmd_t pmd)
अणु
	/* pmd_large(pmd) implies pmd_present(pmd) */
	वापस pmd_large(pmd) && !(pmd_val(pmd) & _SEGMENT_ENTRY_READ);
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत पूर्णांक pte_soft_dirty(pte_t pte)
अणु
	वापस pte_val(pte) & _PAGE_SOFT_सूचीTY;
पूर्ण
#घोषणा pte_swp_soft_dirty pte_soft_dirty

अटल अंतरभूत pte_t pte_mksoft_dirty(pte_t pte)
अणु
	pte_val(pte) |= _PAGE_SOFT_सूचीTY;
	वापस pte;
पूर्ण
#घोषणा pte_swp_mksoft_dirty pte_mksoft_dirty

अटल अंतरभूत pte_t pte_clear_soft_dirty(pte_t pte)
अणु
	pte_val(pte) &= ~_PAGE_SOFT_सूचीTY;
	वापस pte;
पूर्ण
#घोषणा pte_swp_clear_soft_dirty pte_clear_soft_dirty

अटल अंतरभूत पूर्णांक pmd_soft_dirty(pmd_t pmd)
अणु
	वापस pmd_val(pmd) & _SEGMENT_ENTRY_SOFT_सूचीTY;
पूर्ण

अटल अंतरभूत pmd_t pmd_mksoft_dirty(pmd_t pmd)
अणु
	pmd_val(pmd) |= _SEGMENT_ENTRY_SOFT_सूचीTY;
	वापस pmd;
पूर्ण

अटल अंतरभूत pmd_t pmd_clear_soft_dirty(pmd_t pmd)
अणु
	pmd_val(pmd) &= ~_SEGMENT_ENTRY_SOFT_सूचीTY;
	वापस pmd;
पूर्ण

/*
 * query functions pte_ग_लिखो/pte_dirty/pte_young only work अगर
 * pte_present() is true. Undefined behaviour अगर not..
 */
अटल अंतरभूत पूर्णांक pte_ग_लिखो(pte_t pte)
अणु
	वापस (pte_val(pte) & _PAGE_WRITE) != 0;
पूर्ण

अटल अंतरभूत पूर्णांक pte_dirty(pte_t pte)
अणु
	वापस (pte_val(pte) & _PAGE_सूचीTY) != 0;
पूर्ण

अटल अंतरभूत पूर्णांक pte_young(pte_t pte)
अणु
	वापस (pte_val(pte) & _PAGE_YOUNG) != 0;
पूर्ण

#घोषणा __HAVE_ARCH_PTE_UNUSED
अटल अंतरभूत पूर्णांक pte_unused(pte_t pte)
अणु
	वापस pte_val(pte) & _PAGE_UNUSED;
पूर्ण

/*
 * pgd/pmd/pte modअगरication functions
 */

अटल अंतरभूत व्योम pgd_clear(pgd_t *pgd)
अणु
	अगर ((pgd_val(*pgd) & _REGION_ENTRY_TYPE_MASK) == _REGION_ENTRY_TYPE_R1)
		pgd_val(*pgd) = _REGION1_ENTRY_EMPTY;
पूर्ण

अटल अंतरभूत व्योम p4d_clear(p4d_t *p4d)
अणु
	अगर ((p4d_val(*p4d) & _REGION_ENTRY_TYPE_MASK) == _REGION_ENTRY_TYPE_R2)
		p4d_val(*p4d) = _REGION2_ENTRY_EMPTY;
पूर्ण

अटल अंतरभूत व्योम pud_clear(pud_t *pud)
अणु
	अगर ((pud_val(*pud) & _REGION_ENTRY_TYPE_MASK) == _REGION_ENTRY_TYPE_R3)
		pud_val(*pud) = _REGION3_ENTRY_EMPTY;
पूर्ण

अटल अंतरभूत व्योम pmd_clear(pmd_t *pmdp)
अणु
	pmd_val(*pmdp) = _SEGMENT_ENTRY_EMPTY;
पूर्ण

अटल अंतरभूत व्योम pte_clear(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr, pte_t *ptep)
अणु
	pte_val(*ptep) = _PAGE_INVALID;
पूर्ण

/*
 * The following pte modअगरication functions only work अगर
 * pte_present() is true. Undefined behaviour अगर not..
 */
अटल अंतरभूत pte_t pte_modअगरy(pte_t pte, pgprot_t newprot)
अणु
	pte_val(pte) &= _PAGE_CHG_MASK;
	pte_val(pte) |= pgprot_val(newprot);
	/*
	 * newprot क्रम PAGE_NONE, PAGE_RO, PAGE_RX, PAGE_RW and PAGE_RWX
	 * has the invalid bit set, clear it again क्रम पढ़ोable, young pages
	 */
	अगर ((pte_val(pte) & _PAGE_YOUNG) && (pte_val(pte) & _PAGE_READ))
		pte_val(pte) &= ~_PAGE_INVALID;
	/*
	 * newprot क्रम PAGE_RO, PAGE_RX, PAGE_RW and PAGE_RWX has the page
	 * protection bit set, clear it again क्रम writable, dirty pages
	 */
	अगर ((pte_val(pte) & _PAGE_सूचीTY) && (pte_val(pte) & _PAGE_WRITE))
		pte_val(pte) &= ~_PAGE_PROTECT;
	वापस pte;
पूर्ण

अटल अंतरभूत pte_t pte_wrprotect(pte_t pte)
अणु
	pte_val(pte) &= ~_PAGE_WRITE;
	pte_val(pte) |= _PAGE_PROTECT;
	वापस pte;
पूर्ण

अटल अंतरभूत pte_t pte_mkग_लिखो(pte_t pte)
अणु
	pte_val(pte) |= _PAGE_WRITE;
	अगर (pte_val(pte) & _PAGE_सूचीTY)
		pte_val(pte) &= ~_PAGE_PROTECT;
	वापस pte;
पूर्ण

अटल अंतरभूत pte_t pte_mkclean(pte_t pte)
अणु
	pte_val(pte) &= ~_PAGE_सूचीTY;
	pte_val(pte) |= _PAGE_PROTECT;
	वापस pte;
पूर्ण

अटल अंतरभूत pte_t pte_सूची_गढ़ोty(pte_t pte)
अणु
	pte_val(pte) |= _PAGE_सूचीTY | _PAGE_SOFT_सूचीTY;
	अगर (pte_val(pte) & _PAGE_WRITE)
		pte_val(pte) &= ~_PAGE_PROTECT;
	वापस pte;
पूर्ण

अटल अंतरभूत pte_t pte_mkold(pte_t pte)
अणु
	pte_val(pte) &= ~_PAGE_YOUNG;
	pte_val(pte) |= _PAGE_INVALID;
	वापस pte;
पूर्ण

अटल अंतरभूत pte_t pte_mkyoung(pte_t pte)
अणु
	pte_val(pte) |= _PAGE_YOUNG;
	अगर (pte_val(pte) & _PAGE_READ)
		pte_val(pte) &= ~_PAGE_INVALID;
	वापस pte;
पूर्ण

अटल अंतरभूत pte_t pte_mkspecial(pte_t pte)
अणु
	pte_val(pte) |= _PAGE_SPECIAL;
	वापस pte;
पूर्ण

#अगर_घोषित CONFIG_HUGETLB_PAGE
अटल अंतरभूत pte_t pte_mkhuge(pte_t pte)
अणु
	pte_val(pte) |= _PAGE_LARGE;
	वापस pte;
पूर्ण
#पूर्ण_अगर

#घोषणा IPTE_GLOBAL	0
#घोषणा	IPTE_LOCAL	1

#घोषणा IPTE_NODAT	0x400
#घोषणा IPTE_GUEST_ASCE	0x800

अटल __always_अंतरभूत व्योम __ptep_ipte(अचिन्हित दीर्घ address, pte_t *ptep,
					अचिन्हित दीर्घ opt, अचिन्हित दीर्घ asce,
					पूर्णांक local)
अणु
	अचिन्हित दीर्घ pto = (अचिन्हित दीर्घ) ptep;

	अगर (__builtin_स्थिरant_p(opt) && opt == 0) अणु
		/* Invalidation + TLB flush क्रम the pte */
		यंत्र अस्थिर(
			"	.insn	rrf,0xb2210000,%[r1],%[r2],0,%[m4]"
			: "+m" (*ptep) : [r1] "a" (pto), [r2] "a" (address),
			  [m4] "i" (local));
		वापस;
	पूर्ण

	/* Invalidate ptes with options + TLB flush of the ptes */
	opt = opt | (asce & _ASCE_ORIGIN);
	यंत्र अस्थिर(
		"	.insn	rrf,0xb2210000,%[r1],%[r2],%[r3],%[m4]"
		: [r2] "+a" (address), [r3] "+a" (opt)
		: [r1] "a" (pto), [m4] "i" (local) : "memory");
पूर्ण

अटल __always_अंतरभूत व्योम __ptep_ipte_range(अचिन्हित दीर्घ address, पूर्णांक nr,
					      pte_t *ptep, पूर्णांक local)
अणु
	अचिन्हित दीर्घ pto = (अचिन्हित दीर्घ) ptep;

	/* Invalidate a range of ptes + TLB flush of the ptes */
	करो अणु
		यंत्र अस्थिर(
			"       .insn rrf,0xb2210000,%[r1],%[r2],%[r3],%[m4]"
			: [r2] "+a" (address), [r3] "+a" (nr)
			: [r1] "a" (pto), [m4] "i" (local) : "memory");
	पूर्ण जबतक (nr != 255);
पूर्ण

/*
 * This is hard to understand. ptep_get_and_clear and ptep_clear_flush
 * both clear the TLB क्रम the unmapped pte. The reason is that
 * ptep_get_and_clear is used in common code (e.g. change_pte_range)
 * to modअगरy an active pte. The sequence is
 *   1) ptep_get_and_clear
 *   2) set_pte_at
 *   3) flush_tlb_range
 * On s390 the tlb needs to get flushed with the modअगरication of the pte
 * अगर the pte is active. The only way how this can be implemented is to
 * have ptep_get_and_clear करो the tlb flush. In exchange flush_tlb_range
 * is a nop.
 */
pte_t ptep_xchg_direct(काष्ठा mm_काष्ठा *, अचिन्हित दीर्घ, pte_t *, pte_t);
pte_t ptep_xchg_lazy(काष्ठा mm_काष्ठा *, अचिन्हित दीर्घ, pte_t *, pte_t);

#घोषणा __HAVE_ARCH_PTEP_TEST_AND_CLEAR_YOUNG
अटल अंतरभूत पूर्णांक ptep_test_and_clear_young(काष्ठा vm_area_काष्ठा *vma,
					    अचिन्हित दीर्घ addr, pte_t *ptep)
अणु
	pte_t pte = *ptep;

	pte = ptep_xchg_direct(vma->vm_mm, addr, ptep, pte_mkold(pte));
	वापस pte_young(pte);
पूर्ण

#घोषणा __HAVE_ARCH_PTEP_CLEAR_YOUNG_FLUSH
अटल अंतरभूत पूर्णांक ptep_clear_flush_young(काष्ठा vm_area_काष्ठा *vma,
					 अचिन्हित दीर्घ address, pte_t *ptep)
अणु
	वापस ptep_test_and_clear_young(vma, address, ptep);
पूर्ण

#घोषणा __HAVE_ARCH_PTEP_GET_AND_CLEAR
अटल अंतरभूत pte_t ptep_get_and_clear(काष्ठा mm_काष्ठा *mm,
				       अचिन्हित दीर्घ addr, pte_t *ptep)
अणु
	pte_t res;

	res = ptep_xchg_lazy(mm, addr, ptep, __pte(_PAGE_INVALID));
	अगर (mm_is_रक्षित(mm) && pte_present(res))
		uv_convert_from_secure(pte_val(res) & PAGE_MASK);
	वापस res;
पूर्ण

#घोषणा __HAVE_ARCH_PTEP_MODIFY_PROT_TRANSACTION
pte_t ptep_modअगरy_prot_start(काष्ठा vm_area_काष्ठा *, अचिन्हित दीर्घ, pte_t *);
व्योम ptep_modअगरy_prot_commit(काष्ठा vm_area_काष्ठा *, अचिन्हित दीर्घ,
			     pte_t *, pte_t, pte_t);

#घोषणा __HAVE_ARCH_PTEP_CLEAR_FLUSH
अटल अंतरभूत pte_t ptep_clear_flush(काष्ठा vm_area_काष्ठा *vma,
				     अचिन्हित दीर्घ addr, pte_t *ptep)
अणु
	pte_t res;

	res = ptep_xchg_direct(vma->vm_mm, addr, ptep, __pte(_PAGE_INVALID));
	अगर (mm_is_रक्षित(vma->vm_mm) && pte_present(res))
		uv_convert_from_secure(pte_val(res) & PAGE_MASK);
	वापस res;
पूर्ण

/*
 * The batched pte unmap code uses ptep_get_and_clear_full to clear the
 * ptes. Here an optimization is possible. tlb_gather_mmu flushes all
 * tlbs of an mm अगर it can guarantee that the ptes of the mm_काष्ठा
 * cannot be accessed जबतक the batched unmap is running. In this हाल
 * full==1 and a simple pte_clear is enough. See tlb.h.
 */
#घोषणा __HAVE_ARCH_PTEP_GET_AND_CLEAR_FULL
अटल अंतरभूत pte_t ptep_get_and_clear_full(काष्ठा mm_काष्ठा *mm,
					    अचिन्हित दीर्घ addr,
					    pte_t *ptep, पूर्णांक full)
अणु
	pte_t res;

	अगर (full) अणु
		res = *ptep;
		*ptep = __pte(_PAGE_INVALID);
	पूर्ण अन्यथा अणु
		res = ptep_xchg_lazy(mm, addr, ptep, __pte(_PAGE_INVALID));
	पूर्ण
	अगर (mm_is_रक्षित(mm) && pte_present(res))
		uv_convert_from_secure(pte_val(res) & PAGE_MASK);
	वापस res;
पूर्ण

#घोषणा __HAVE_ARCH_PTEP_SET_WRPROTECT
अटल अंतरभूत व्योम ptep_set_wrprotect(काष्ठा mm_काष्ठा *mm,
				      अचिन्हित दीर्घ addr, pte_t *ptep)
अणु
	pte_t pte = *ptep;

	अगर (pte_ग_लिखो(pte))
		ptep_xchg_lazy(mm, addr, ptep, pte_wrprotect(pte));
पूर्ण

#घोषणा __HAVE_ARCH_PTEP_SET_ACCESS_FLAGS
अटल अंतरभूत पूर्णांक ptep_set_access_flags(काष्ठा vm_area_काष्ठा *vma,
					अचिन्हित दीर्घ addr, pte_t *ptep,
					pte_t entry, पूर्णांक dirty)
अणु
	अगर (pte_same(*ptep, entry))
		वापस 0;
	ptep_xchg_direct(vma->vm_mm, addr, ptep, entry);
	वापस 1;
पूर्ण

/*
 * Additional functions to handle KVM guest page tables
 */
व्योम ptep_set_pte_at(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr,
		     pte_t *ptep, pte_t entry);
व्योम ptep_set_notअगरy(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr, pte_t *ptep);
व्योम ptep_notअगरy(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr,
		 pte_t *ptep, अचिन्हित दीर्घ bits);
पूर्णांक ptep_क्रमce_prot(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ gaddr,
		    pte_t *ptep, पूर्णांक prot, अचिन्हित दीर्घ bit);
व्योम ptep_zap_unused(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr,
		     pte_t *ptep , पूर्णांक reset);
व्योम ptep_zap_key(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr, pte_t *ptep);
पूर्णांक ptep_shaकरोw_pte(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ saddr,
		    pte_t *sptep, pte_t *tptep, pte_t pte);
व्योम ptep_unshaकरोw_pte(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ saddr, pte_t *ptep);

bool ptep_test_and_clear_uc(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ address,
			    pte_t *ptep);
पूर्णांक set_guest_storage_key(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr,
			  अचिन्हित अक्षर key, bool nq);
पूर्णांक cond_set_guest_storage_key(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr,
			       अचिन्हित अक्षर key, अचिन्हित अक्षर *oldkey,
			       bool nq, bool mr, bool mc);
पूर्णांक reset_guest_reference_bit(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr);
पूर्णांक get_guest_storage_key(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr,
			  अचिन्हित अक्षर *key);

पूर्णांक set_pgste_bits(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr,
				अचिन्हित दीर्घ bits, अचिन्हित दीर्घ value);
पूर्णांक get_pgste(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ hva, अचिन्हित दीर्घ *pgstep);
पूर्णांक pgste_perक्रमm_essa(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ hva, पूर्णांक orc,
			अचिन्हित दीर्घ *oldpte, अचिन्हित दीर्घ *oldpgste);
व्योम gmap_pmdp_csp(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ vmaddr);
व्योम gmap_pmdp_invalidate(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ vmaddr);
व्योम gmap_pmdp_idte_local(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ vmaddr);
व्योम gmap_pmdp_idte_global(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ vmaddr);

#घोषणा pgprot_ग_लिखोcombine	pgprot_ग_लिखोcombine
pgprot_t pgprot_ग_लिखोcombine(pgprot_t prot);

#घोषणा pgprot_ग_लिखोthrough	pgprot_ग_लिखोthrough
pgprot_t pgprot_ग_लिखोthrough(pgprot_t prot);

/*
 * Certain architectures need to करो special things when PTEs
 * within a page table are directly modअगरied.  Thus, the following
 * hook is made available.
 */
अटल अंतरभूत व्योम set_pte_at(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr,
			      pte_t *ptep, pte_t entry)
अणु
	अगर (pte_present(entry))
		pte_val(entry) &= ~_PAGE_UNUSED;
	अगर (mm_has_pgste(mm))
		ptep_set_pte_at(mm, addr, ptep, entry);
	अन्यथा
		*ptep = entry;
पूर्ण

/*
 * Conversion functions: convert a page and protection to a page entry,
 * and a page entry and page directory to the page they refer to.
 */
अटल अंतरभूत pte_t mk_pte_phys(अचिन्हित दीर्घ physpage, pgprot_t pgprot)
अणु
	pte_t __pte;

	pte_val(__pte) = physpage | pgprot_val(pgprot);
	अगर (!MACHINE_HAS_NX)
		pte_val(__pte) &= ~_PAGE_NOEXEC;
	वापस pte_mkyoung(__pte);
पूर्ण

अटल अंतरभूत pte_t mk_pte(काष्ठा page *page, pgprot_t pgprot)
अणु
	अचिन्हित दीर्घ physpage = page_to_phys(page);
	pte_t __pte = mk_pte_phys(physpage, pgprot);

	अगर (pte_ग_लिखो(__pte) && PageDirty(page))
		__pte = pte_सूची_गढ़ोty(__pte);
	वापस __pte;
पूर्ण

#घोषणा pgd_index(address) (((address) >> PGसूची_SHIFT) & (PTRS_PER_PGD-1))
#घोषणा p4d_index(address) (((address) >> P4D_SHIFT) & (PTRS_PER_P4D-1))
#घोषणा pud_index(address) (((address) >> PUD_SHIFT) & (PTRS_PER_PUD-1))
#घोषणा pmd_index(address) (((address) >> PMD_SHIFT) & (PTRS_PER_PMD-1))

#घोषणा p4d_deref(pud) ((अचिन्हित दीर्घ)__va(p4d_val(pud) & _REGION_ENTRY_ORIGIN))
#घोषणा pgd_deref(pgd) ((अचिन्हित दीर्घ)__va(pgd_val(pgd) & _REGION_ENTRY_ORIGIN))

अटल अंतरभूत अचिन्हित दीर्घ pmd_deref(pmd_t pmd)
अणु
	अचिन्हित दीर्घ origin_mask;

	origin_mask = _SEGMENT_ENTRY_ORIGIN;
	अगर (pmd_large(pmd))
		origin_mask = _SEGMENT_ENTRY_ORIGIN_LARGE;
	वापस (अचिन्हित दीर्घ)__va(pmd_val(pmd) & origin_mask);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ pmd_pfn(pmd_t pmd)
अणु
	वापस __pa(pmd_deref(pmd)) >> PAGE_SHIFT;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ pud_deref(pud_t pud)
अणु
	अचिन्हित दीर्घ origin_mask;

	origin_mask = _REGION_ENTRY_ORIGIN;
	अगर (pud_large(pud))
		origin_mask = _REGION3_ENTRY_ORIGIN_LARGE;
	वापस (अचिन्हित दीर्घ)__va(pud_val(pud) & origin_mask);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ pud_pfn(pud_t pud)
अणु
	वापस __pa(pud_deref(pud)) >> PAGE_SHIFT;
पूर्ण

/*
 * The pgd_offset function *always* adds the index क्रम the top-level
 * region/segment table. This is करोne to get a sequence like the
 * following to work:
 *	pgdp = pgd_offset(current->mm, addr);
 *	pgd = READ_ONCE(*pgdp);
 *	p4dp = p4d_offset(&pgd, addr);
 *	...
 * The subsequent p4d_offset, pud_offset and pmd_offset functions
 * only add an index अगर they dereferenced the poपूर्णांकer.
 */
अटल अंतरभूत pgd_t *pgd_offset_raw(pgd_t *pgd, अचिन्हित दीर्घ address)
अणु
	अचिन्हित दीर्घ rste;
	अचिन्हित पूर्णांक shअगरt;

	/* Get the first entry of the top level table */
	rste = pgd_val(*pgd);
	/* Pick up the shअगरt from the table type of the first entry */
	shअगरt = ((rste & _REGION_ENTRY_TYPE_MASK) >> 2) * 11 + 20;
	वापस pgd + ((address >> shअगरt) & (PTRS_PER_PGD - 1));
पूर्ण

#घोषणा pgd_offset(mm, address) pgd_offset_raw(READ_ONCE((mm)->pgd), address)

अटल अंतरभूत p4d_t *p4d_offset_lockless(pgd_t *pgdp, pgd_t pgd, अचिन्हित दीर्घ address)
अणु
	अगर ((pgd_val(pgd) & _REGION_ENTRY_TYPE_MASK) >= _REGION_ENTRY_TYPE_R1)
		वापस (p4d_t *) pgd_deref(pgd) + p4d_index(address);
	वापस (p4d_t *) pgdp;
पूर्ण
#घोषणा p4d_offset_lockless p4d_offset_lockless

अटल अंतरभूत p4d_t *p4d_offset(pgd_t *pgdp, अचिन्हित दीर्घ address)
अणु
	वापस p4d_offset_lockless(pgdp, *pgdp, address);
पूर्ण

अटल अंतरभूत pud_t *pud_offset_lockless(p4d_t *p4dp, p4d_t p4d, अचिन्हित दीर्घ address)
अणु
	अगर ((p4d_val(p4d) & _REGION_ENTRY_TYPE_MASK) >= _REGION_ENTRY_TYPE_R2)
		वापस (pud_t *) p4d_deref(p4d) + pud_index(address);
	वापस (pud_t *) p4dp;
पूर्ण
#घोषणा pud_offset_lockless pud_offset_lockless

अटल अंतरभूत pud_t *pud_offset(p4d_t *p4dp, अचिन्हित दीर्घ address)
अणु
	वापस pud_offset_lockless(p4dp, *p4dp, address);
पूर्ण
#घोषणा pud_offset pud_offset

अटल अंतरभूत pmd_t *pmd_offset_lockless(pud_t *pudp, pud_t pud, अचिन्हित दीर्घ address)
अणु
	अगर ((pud_val(pud) & _REGION_ENTRY_TYPE_MASK) >= _REGION_ENTRY_TYPE_R3)
		वापस (pmd_t *) pud_deref(pud) + pmd_index(address);
	वापस (pmd_t *) pudp;
पूर्ण
#घोषणा pmd_offset_lockless pmd_offset_lockless

अटल अंतरभूत pmd_t *pmd_offset(pud_t *pudp, अचिन्हित दीर्घ address)
अणु
	वापस pmd_offset_lockless(pudp, *pudp, address);
पूर्ण
#घोषणा pmd_offset pmd_offset

अटल अंतरभूत अचिन्हित दीर्घ pmd_page_vaddr(pmd_t pmd)
अणु
	वापस (अचिन्हित दीर्घ) pmd_deref(pmd);
पूर्ण

अटल अंतरभूत bool gup_fast_permitted(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	वापस end <= current->mm->context.asce_limit;
पूर्ण
#घोषणा gup_fast_permitted gup_fast_permitted

#घोषणा pfn_pte(pfn, pgprot)	mk_pte_phys(((pfn) << PAGE_SHIFT), (pgprot))
#घोषणा pte_pfn(x) (pte_val(x) >> PAGE_SHIFT)
#घोषणा pte_page(x) pfn_to_page(pte_pfn(x))

#घोषणा pmd_page(pmd) pfn_to_page(pmd_pfn(pmd))
#घोषणा pud_page(pud) pfn_to_page(pud_pfn(pud))
#घोषणा p4d_page(p4d) pfn_to_page(p4d_pfn(p4d))
#घोषणा pgd_page(pgd) pfn_to_page(pgd_pfn(pgd))

अटल अंतरभूत pmd_t pmd_wrprotect(pmd_t pmd)
अणु
	pmd_val(pmd) &= ~_SEGMENT_ENTRY_WRITE;
	pmd_val(pmd) |= _SEGMENT_ENTRY_PROTECT;
	वापस pmd;
पूर्ण

अटल अंतरभूत pmd_t pmd_mkग_लिखो(pmd_t pmd)
अणु
	pmd_val(pmd) |= _SEGMENT_ENTRY_WRITE;
	अगर (pmd_val(pmd) & _SEGMENT_ENTRY_सूचीTY)
		pmd_val(pmd) &= ~_SEGMENT_ENTRY_PROTECT;
	वापस pmd;
पूर्ण

अटल अंतरभूत pmd_t pmd_mkclean(pmd_t pmd)
अणु
	pmd_val(pmd) &= ~_SEGMENT_ENTRY_सूचीTY;
	pmd_val(pmd) |= _SEGMENT_ENTRY_PROTECT;
	वापस pmd;
पूर्ण

अटल अंतरभूत pmd_t pmd_सूची_गढ़ोty(pmd_t pmd)
अणु
	pmd_val(pmd) |= _SEGMENT_ENTRY_सूचीTY | _SEGMENT_ENTRY_SOFT_सूचीTY;
	अगर (pmd_val(pmd) & _SEGMENT_ENTRY_WRITE)
		pmd_val(pmd) &= ~_SEGMENT_ENTRY_PROTECT;
	वापस pmd;
पूर्ण

अटल अंतरभूत pud_t pud_wrprotect(pud_t pud)
अणु
	pud_val(pud) &= ~_REGION3_ENTRY_WRITE;
	pud_val(pud) |= _REGION_ENTRY_PROTECT;
	वापस pud;
पूर्ण

अटल अंतरभूत pud_t pud_mkग_लिखो(pud_t pud)
अणु
	pud_val(pud) |= _REGION3_ENTRY_WRITE;
	अगर (pud_val(pud) & _REGION3_ENTRY_सूचीTY)
		pud_val(pud) &= ~_REGION_ENTRY_PROTECT;
	वापस pud;
पूर्ण

अटल अंतरभूत pud_t pud_mkclean(pud_t pud)
अणु
	pud_val(pud) &= ~_REGION3_ENTRY_सूचीTY;
	pud_val(pud) |= _REGION_ENTRY_PROTECT;
	वापस pud;
पूर्ण

अटल अंतरभूत pud_t pud_सूची_गढ़ोty(pud_t pud)
अणु
	pud_val(pud) |= _REGION3_ENTRY_सूचीTY | _REGION3_ENTRY_SOFT_सूचीTY;
	अगर (pud_val(pud) & _REGION3_ENTRY_WRITE)
		pud_val(pud) &= ~_REGION_ENTRY_PROTECT;
	वापस pud;
पूर्ण

#अगर defined(CONFIG_TRANSPARENT_HUGEPAGE) || defined(CONFIG_HUGETLB_PAGE)
अटल अंतरभूत अचिन्हित दीर्घ massage_pgprot_pmd(pgprot_t pgprot)
अणु
	/*
	 * pgprot is PAGE_NONE, PAGE_RO, PAGE_RX, PAGE_RW or PAGE_RWX
	 * (see __Pxxx / __Sxxx). Convert to segment table entry क्रमmat.
	 */
	अगर (pgprot_val(pgprot) == pgprot_val(PAGE_NONE))
		वापस pgprot_val(SEGMENT_NONE);
	अगर (pgprot_val(pgprot) == pgprot_val(PAGE_RO))
		वापस pgprot_val(SEGMENT_RO);
	अगर (pgprot_val(pgprot) == pgprot_val(PAGE_RX))
		वापस pgprot_val(SEGMENT_RX);
	अगर (pgprot_val(pgprot) == pgprot_val(PAGE_RW))
		वापस pgprot_val(SEGMENT_RW);
	वापस pgprot_val(SEGMENT_RWX);
पूर्ण

अटल अंतरभूत pmd_t pmd_mkyoung(pmd_t pmd)
अणु
	pmd_val(pmd) |= _SEGMENT_ENTRY_YOUNG;
	अगर (pmd_val(pmd) & _SEGMENT_ENTRY_READ)
		pmd_val(pmd) &= ~_SEGMENT_ENTRY_INVALID;
	वापस pmd;
पूर्ण

अटल अंतरभूत pmd_t pmd_mkold(pmd_t pmd)
अणु
	pmd_val(pmd) &= ~_SEGMENT_ENTRY_YOUNG;
	pmd_val(pmd) |= _SEGMENT_ENTRY_INVALID;
	वापस pmd;
पूर्ण

अटल अंतरभूत pmd_t pmd_modअगरy(pmd_t pmd, pgprot_t newprot)
अणु
	pmd_val(pmd) &= _SEGMENT_ENTRY_ORIGIN_LARGE |
		_SEGMENT_ENTRY_सूचीTY | _SEGMENT_ENTRY_YOUNG |
		_SEGMENT_ENTRY_LARGE | _SEGMENT_ENTRY_SOFT_सूचीTY;
	pmd_val(pmd) |= massage_pgprot_pmd(newprot);
	अगर (!(pmd_val(pmd) & _SEGMENT_ENTRY_सूचीTY))
		pmd_val(pmd) |= _SEGMENT_ENTRY_PROTECT;
	अगर (!(pmd_val(pmd) & _SEGMENT_ENTRY_YOUNG))
		pmd_val(pmd) |= _SEGMENT_ENTRY_INVALID;
	वापस pmd;
पूर्ण

अटल अंतरभूत pmd_t mk_pmd_phys(अचिन्हित दीर्घ physpage, pgprot_t pgprot)
अणु
	pmd_t __pmd;
	pmd_val(__pmd) = physpage + massage_pgprot_pmd(pgprot);
	वापस __pmd;
पूर्ण

#पूर्ण_अगर /* CONFIG_TRANSPARENT_HUGEPAGE || CONFIG_HUGETLB_PAGE */

अटल अंतरभूत व्योम __pmdp_csp(pmd_t *pmdp)
अणु
	csp((अचिन्हित पूर्णांक *)pmdp + 1, pmd_val(*pmdp),
	    pmd_val(*pmdp) | _SEGMENT_ENTRY_INVALID);
पूर्ण

#घोषणा IDTE_GLOBAL	0
#घोषणा IDTE_LOCAL	1

#घोषणा IDTE_PTOA	0x0800
#घोषणा IDTE_NODAT	0x1000
#घोषणा IDTE_GUEST_ASCE	0x2000

अटल __always_अंतरभूत व्योम __pmdp_idte(अचिन्हित दीर्घ addr, pmd_t *pmdp,
					अचिन्हित दीर्घ opt, अचिन्हित दीर्घ asce,
					पूर्णांक local)
अणु
	अचिन्हित दीर्घ sto;

	sto = (अचिन्हित दीर्घ) pmdp - pmd_index(addr) * माप(pmd_t);
	अगर (__builtin_स्थिरant_p(opt) && opt == 0) अणु
		/* flush without guest asce */
		यंत्र अस्थिर(
			"	.insn	rrf,0xb98e0000,%[r1],%[r2],0,%[m4]"
			: "+m" (*pmdp)
			: [r1] "a" (sto), [r2] "a" ((addr & HPAGE_MASK)),
			  [m4] "i" (local)
			: "cc" );
	पूर्ण अन्यथा अणु
		/* flush with guest asce */
		यंत्र अस्थिर(
			"	.insn	rrf,0xb98e0000,%[r1],%[r2],%[r3],%[m4]"
			: "+m" (*pmdp)
			: [r1] "a" (sto), [r2] "a" ((addr & HPAGE_MASK) | opt),
			  [r3] "a" (asce), [m4] "i" (local)
			: "cc" );
	पूर्ण
पूर्ण

अटल __always_अंतरभूत व्योम __pudp_idte(अचिन्हित दीर्घ addr, pud_t *pudp,
					अचिन्हित दीर्घ opt, अचिन्हित दीर्घ asce,
					पूर्णांक local)
अणु
	अचिन्हित दीर्घ r3o;

	r3o = (अचिन्हित दीर्घ) pudp - pud_index(addr) * माप(pud_t);
	r3o |= _ASCE_TYPE_REGION3;
	अगर (__builtin_स्थिरant_p(opt) && opt == 0) अणु
		/* flush without guest asce */
		यंत्र अस्थिर(
			"	.insn	rrf,0xb98e0000,%[r1],%[r2],0,%[m4]"
			: "+m" (*pudp)
			: [r1] "a" (r3o), [r2] "a" ((addr & PUD_MASK)),
			  [m4] "i" (local)
			: "cc");
	पूर्ण अन्यथा अणु
		/* flush with guest asce */
		यंत्र अस्थिर(
			"	.insn	rrf,0xb98e0000,%[r1],%[r2],%[r3],%[m4]"
			: "+m" (*pudp)
			: [r1] "a" (r3o), [r2] "a" ((addr & PUD_MASK) | opt),
			  [r3] "a" (asce), [m4] "i" (local)
			: "cc" );
	पूर्ण
पूर्ण

pmd_t pmdp_xchg_direct(काष्ठा mm_काष्ठा *, अचिन्हित दीर्घ, pmd_t *, pmd_t);
pmd_t pmdp_xchg_lazy(काष्ठा mm_काष्ठा *, अचिन्हित दीर्घ, pmd_t *, pmd_t);
pud_t pudp_xchg_direct(काष्ठा mm_काष्ठा *, अचिन्हित दीर्घ, pud_t *, pud_t);

#अगर_घोषित CONFIG_TRANSPARENT_HUGEPAGE

#घोषणा __HAVE_ARCH_PGTABLE_DEPOSIT
व्योम pgtable_trans_huge_deposit(काष्ठा mm_काष्ठा *mm, pmd_t *pmdp,
				pgtable_t pgtable);

#घोषणा __HAVE_ARCH_PGTABLE_WITHDRAW
pgtable_t pgtable_trans_huge_withdraw(काष्ठा mm_काष्ठा *mm, pmd_t *pmdp);

#घोषणा  __HAVE_ARCH_PMDP_SET_ACCESS_FLAGS
अटल अंतरभूत पूर्णांक pmdp_set_access_flags(काष्ठा vm_area_काष्ठा *vma,
					अचिन्हित दीर्घ addr, pmd_t *pmdp,
					pmd_t entry, पूर्णांक dirty)
अणु
	VM_BUG_ON(addr & ~HPAGE_MASK);

	entry = pmd_mkyoung(entry);
	अगर (dirty)
		entry = pmd_सूची_गढ़ोty(entry);
	अगर (pmd_val(*pmdp) == pmd_val(entry))
		वापस 0;
	pmdp_xchg_direct(vma->vm_mm, addr, pmdp, entry);
	वापस 1;
पूर्ण

#घोषणा __HAVE_ARCH_PMDP_TEST_AND_CLEAR_YOUNG
अटल अंतरभूत पूर्णांक pmdp_test_and_clear_young(काष्ठा vm_area_काष्ठा *vma,
					    अचिन्हित दीर्घ addr, pmd_t *pmdp)
अणु
	pmd_t pmd = *pmdp;

	pmd = pmdp_xchg_direct(vma->vm_mm, addr, pmdp, pmd_mkold(pmd));
	वापस pmd_young(pmd);
पूर्ण

#घोषणा __HAVE_ARCH_PMDP_CLEAR_YOUNG_FLUSH
अटल अंतरभूत पूर्णांक pmdp_clear_flush_young(काष्ठा vm_area_काष्ठा *vma,
					 अचिन्हित दीर्घ addr, pmd_t *pmdp)
अणु
	VM_BUG_ON(addr & ~HPAGE_MASK);
	वापस pmdp_test_and_clear_young(vma, addr, pmdp);
पूर्ण

अटल अंतरभूत व्योम set_pmd_at(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr,
			      pmd_t *pmdp, pmd_t entry)
अणु
	अगर (!MACHINE_HAS_NX)
		pmd_val(entry) &= ~_SEGMENT_ENTRY_NOEXEC;
	*pmdp = entry;
पूर्ण

अटल अंतरभूत pmd_t pmd_mkhuge(pmd_t pmd)
अणु
	pmd_val(pmd) |= _SEGMENT_ENTRY_LARGE;
	pmd_val(pmd) |= _SEGMENT_ENTRY_YOUNG;
	pmd_val(pmd) |= _SEGMENT_ENTRY_PROTECT;
	वापस pmd;
पूर्ण

#घोषणा __HAVE_ARCH_PMDP_HUGE_GET_AND_CLEAR
अटल अंतरभूत pmd_t pmdp_huge_get_and_clear(काष्ठा mm_काष्ठा *mm,
					    अचिन्हित दीर्घ addr, pmd_t *pmdp)
अणु
	वापस pmdp_xchg_direct(mm, addr, pmdp, __pmd(_SEGMENT_ENTRY_EMPTY));
पूर्ण

#घोषणा __HAVE_ARCH_PMDP_HUGE_GET_AND_CLEAR_FULL
अटल अंतरभूत pmd_t pmdp_huge_get_and_clear_full(काष्ठा vm_area_काष्ठा *vma,
						 अचिन्हित दीर्घ addr,
						 pmd_t *pmdp, पूर्णांक full)
अणु
	अगर (full) अणु
		pmd_t pmd = *pmdp;
		*pmdp = __pmd(_SEGMENT_ENTRY_EMPTY);
		वापस pmd;
	पूर्ण
	वापस pmdp_xchg_lazy(vma->vm_mm, addr, pmdp, __pmd(_SEGMENT_ENTRY_EMPTY));
पूर्ण

#घोषणा __HAVE_ARCH_PMDP_HUGE_CLEAR_FLUSH
अटल अंतरभूत pmd_t pmdp_huge_clear_flush(काष्ठा vm_area_काष्ठा *vma,
					  अचिन्हित दीर्घ addr, pmd_t *pmdp)
अणु
	वापस pmdp_huge_get_and_clear(vma->vm_mm, addr, pmdp);
पूर्ण

#घोषणा __HAVE_ARCH_PMDP_INVALIDATE
अटल अंतरभूत pmd_t pmdp_invalidate(काष्ठा vm_area_काष्ठा *vma,
				   अचिन्हित दीर्घ addr, pmd_t *pmdp)
अणु
	pmd_t pmd = __pmd(pmd_val(*pmdp) | _SEGMENT_ENTRY_INVALID);

	वापस pmdp_xchg_direct(vma->vm_mm, addr, pmdp, pmd);
पूर्ण

#घोषणा __HAVE_ARCH_PMDP_SET_WRPROTECT
अटल अंतरभूत व्योम pmdp_set_wrprotect(काष्ठा mm_काष्ठा *mm,
				      अचिन्हित दीर्घ addr, pmd_t *pmdp)
अणु
	pmd_t pmd = *pmdp;

	अगर (pmd_ग_लिखो(pmd))
		pmd = pmdp_xchg_lazy(mm, addr, pmdp, pmd_wrprotect(pmd));
पूर्ण

अटल अंतरभूत pmd_t pmdp_collapse_flush(काष्ठा vm_area_काष्ठा *vma,
					अचिन्हित दीर्घ address,
					pmd_t *pmdp)
अणु
	वापस pmdp_huge_get_and_clear(vma->vm_mm, address, pmdp);
पूर्ण
#घोषणा pmdp_collapse_flush pmdp_collapse_flush

#घोषणा pfn_pmd(pfn, pgprot)	mk_pmd_phys(((pfn) << PAGE_SHIFT), (pgprot))
#घोषणा mk_pmd(page, pgprot)	pfn_pmd(page_to_pfn(page), (pgprot))

अटल अंतरभूत पूर्णांक pmd_trans_huge(pmd_t pmd)
अणु
	वापस pmd_val(pmd) & _SEGMENT_ENTRY_LARGE;
पूर्ण

#घोषणा has_transparent_hugepage has_transparent_hugepage
अटल अंतरभूत पूर्णांक has_transparent_hugepage(व्योम)
अणु
	वापस MACHINE_HAS_EDAT1 ? 1 : 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_TRANSPARENT_HUGEPAGE */

/*
 * 64 bit swap entry क्रमmat:
 * A page-table entry has some bits we have to treat in a special way.
 * Bits 52 and bit 55 have to be zero, otherwise a specअगरication
 * exception will occur instead of a page translation exception. The
 * specअगरication exception has the bad habit not to store necessary
 * inक्रमmation in the lowcore.
 * Bits 54 and 63 are used to indicate the page type.
 * A swap pte is indicated by bit pattern (pte & 0x201) == 0x200
 * This leaves the bits 0-51 and bits 56-62 to store type and offset.
 * We use the 5 bits from 57-61 क्रम the type and the 52 bits from 0-51
 * क्रम the offset.
 * |			  offset			|01100|type |00|
 * |0000000000111111111122222222223333333333444444444455|55555|55566|66|
 * |0123456789012345678901234567890123456789012345678901|23456|78901|23|
 */

#घोषणा __SWP_OFFSET_MASK	((1UL << 52) - 1)
#घोषणा __SWP_OFFSET_SHIFT	12
#घोषणा __SWP_TYPE_MASK		((1UL << 5) - 1)
#घोषणा __SWP_TYPE_SHIFT	2

अटल अंतरभूत pte_t mk_swap_pte(अचिन्हित दीर्घ type, अचिन्हित दीर्घ offset)
अणु
	pte_t pte;

	pte_val(pte) = _PAGE_INVALID | _PAGE_PROTECT;
	pte_val(pte) |= (offset & __SWP_OFFSET_MASK) << __SWP_OFFSET_SHIFT;
	pte_val(pte) |= (type & __SWP_TYPE_MASK) << __SWP_TYPE_SHIFT;
	वापस pte;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ __swp_type(swp_entry_t entry)
अणु
	वापस (entry.val >> __SWP_TYPE_SHIFT) & __SWP_TYPE_MASK;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ __swp_offset(swp_entry_t entry)
अणु
	वापस (entry.val >> __SWP_OFFSET_SHIFT) & __SWP_OFFSET_MASK;
पूर्ण

अटल अंतरभूत swp_entry_t __swp_entry(अचिन्हित दीर्घ type, अचिन्हित दीर्घ offset)
अणु
	वापस (swp_entry_t) अणु pte_val(mk_swap_pte(type, offset)) पूर्ण;
पूर्ण

#घोषणा __pte_to_swp_entry(pte)	((swp_entry_t) अणु pte_val(pte) पूर्ण)
#घोषणा __swp_entry_to_pte(x)	((pte_t) अणु (x).val पूर्ण)

#घोषणा kern_addr_valid(addr)   (1)

बाह्य पूर्णांक vmem_add_mapping(अचिन्हित दीर्घ start, अचिन्हित दीर्घ size);
बाह्य व्योम vmem_हटाओ_mapping(अचिन्हित दीर्घ start, अचिन्हित दीर्घ size);
बाह्य पूर्णांक s390_enable_sie(व्योम);
बाह्य पूर्णांक s390_enable_skey(व्योम);
बाह्य व्योम s390_reset_cmma(काष्ठा mm_काष्ठा *mm);

/* s390 has a निजी copy of get unmapped area to deal with cache synonyms */
#घोषणा HAVE_ARCH_UNMAPPED_AREA
#घोषणा HAVE_ARCH_UNMAPPED_AREA_TOPDOWN

#पूर्ण_अगर /* _S390_PAGE_H */
