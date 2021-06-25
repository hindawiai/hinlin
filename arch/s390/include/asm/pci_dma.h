<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_S390_PCI_DMA_H
#घोषणा _ASM_S390_PCI_DMA_H

/* I/O Translation Anchor (IOTA) */
क्रमागत zpci_ioat_dtype अणु
	ZPCI_IOTA_STO = 0,
	ZPCI_IOTA_RTTO = 1,
	ZPCI_IOTA_RSTO = 2,
	ZPCI_IOTA_RFTO = 3,
	ZPCI_IOTA_PFAA = 4,
	ZPCI_IOTA_IOPFAA = 5,
	ZPCI_IOTA_IOPTO = 7
पूर्ण;

#घोषणा ZPCI_IOTA_IOT_ENABLED		0x800UL
#घोषणा ZPCI_IOTA_DT_ST			(ZPCI_IOTA_STO	<< 2)
#घोषणा ZPCI_IOTA_DT_RT			(ZPCI_IOTA_RTTO << 2)
#घोषणा ZPCI_IOTA_DT_RS			(ZPCI_IOTA_RSTO << 2)
#घोषणा ZPCI_IOTA_DT_RF			(ZPCI_IOTA_RFTO << 2)
#घोषणा ZPCI_IOTA_DT_PF			(ZPCI_IOTA_PFAA << 2)
#घोषणा ZPCI_IOTA_FS_4K			0
#घोषणा ZPCI_IOTA_FS_1M			1
#घोषणा ZPCI_IOTA_FS_2G			2
#घोषणा ZPCI_KEY			(PAGE_DEFAULT_KEY << 5)

#घोषणा ZPCI_TABLE_SIZE_RT	(1UL << 42)

#घोषणा ZPCI_IOTA_STO_FLAG	(ZPCI_IOTA_IOT_ENABLED | ZPCI_KEY | ZPCI_IOTA_DT_ST)
#घोषणा ZPCI_IOTA_RTTO_FLAG	(ZPCI_IOTA_IOT_ENABLED | ZPCI_KEY | ZPCI_IOTA_DT_RT)
#घोषणा ZPCI_IOTA_RSTO_FLAG	(ZPCI_IOTA_IOT_ENABLED | ZPCI_KEY | ZPCI_IOTA_DT_RS)
#घोषणा ZPCI_IOTA_RFTO_FLAG	(ZPCI_IOTA_IOT_ENABLED | ZPCI_KEY | ZPCI_IOTA_DT_RF)
#घोषणा ZPCI_IOTA_RFAA_FLAG	(ZPCI_IOTA_IOT_ENABLED | ZPCI_KEY | ZPCI_IOTA_DT_PF | ZPCI_IOTA_FS_2G)

/* I/O Region and segment tables */
#घोषणा ZPCI_INDEX_MASK			0x7ffUL

#घोषणा ZPCI_TABLE_TYPE_MASK		0xc
#घोषणा ZPCI_TABLE_TYPE_RFX		0xc
#घोषणा ZPCI_TABLE_TYPE_RSX		0x8
#घोषणा ZPCI_TABLE_TYPE_RTX		0x4
#घोषणा ZPCI_TABLE_TYPE_SX		0x0

#घोषणा ZPCI_TABLE_LEN_RFX		0x3
#घोषणा ZPCI_TABLE_LEN_RSX		0x3
#घोषणा ZPCI_TABLE_LEN_RTX		0x3

#घोषणा ZPCI_TABLE_OFFSET_MASK		0xc0
#घोषणा ZPCI_TABLE_SIZE			0x4000
#घोषणा ZPCI_TABLE_ALIGN		ZPCI_TABLE_SIZE
#घोषणा ZPCI_TABLE_ENTRY_SIZE		(माप(अचिन्हित दीर्घ))
#घोषणा ZPCI_TABLE_ENTRIES		(ZPCI_TABLE_SIZE / ZPCI_TABLE_ENTRY_SIZE)

#घोषणा ZPCI_TABLE_BITS			11
#घोषणा ZPCI_PT_BITS			8
#घोषणा ZPCI_ST_SHIFT			(ZPCI_PT_BITS + PAGE_SHIFT)
#घोषणा ZPCI_RT_SHIFT			(ZPCI_ST_SHIFT + ZPCI_TABLE_BITS)

#घोषणा ZPCI_RTE_FLAG_MASK		0x3fffUL
#घोषणा ZPCI_RTE_ADDR_MASK		(~ZPCI_RTE_FLAG_MASK)
#घोषणा ZPCI_STE_FLAG_MASK		0x7ffUL
#घोषणा ZPCI_STE_ADDR_MASK		(~ZPCI_STE_FLAG_MASK)

/* I/O Page tables */
#घोषणा ZPCI_PTE_VALID_MASK		0x400
#घोषणा ZPCI_PTE_INVALID		0x400
#घोषणा ZPCI_PTE_VALID			0x000
#घोषणा ZPCI_PT_SIZE			0x800
#घोषणा ZPCI_PT_ALIGN			ZPCI_PT_SIZE
#घोषणा ZPCI_PT_ENTRIES			(ZPCI_PT_SIZE / ZPCI_TABLE_ENTRY_SIZE)
#घोषणा ZPCI_PT_MASK			(ZPCI_PT_ENTRIES - 1)

#घोषणा ZPCI_PTE_FLAG_MASK		0xfffUL
#घोषणा ZPCI_PTE_ADDR_MASK		(~ZPCI_PTE_FLAG_MASK)

/* Shared bits */
#घोषणा ZPCI_TABLE_VALID		0x00
#घोषणा ZPCI_TABLE_INVALID		0x20
#घोषणा ZPCI_TABLE_PROTECTED		0x200
#घोषणा ZPCI_TABLE_UNPROTECTED		0x000

#घोषणा ZPCI_TABLE_VALID_MASK		0x20
#घोषणा ZPCI_TABLE_PROT_MASK		0x200

अटल अंतरभूत अचिन्हित पूर्णांक calc_rtx(dma_addr_t ptr)
अणु
	वापस ((अचिन्हित दीर्घ) ptr >> ZPCI_RT_SHIFT) & ZPCI_INDEX_MASK;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक calc_sx(dma_addr_t ptr)
अणु
	वापस ((अचिन्हित दीर्घ) ptr >> ZPCI_ST_SHIFT) & ZPCI_INDEX_MASK;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक calc_px(dma_addr_t ptr)
अणु
	वापस ((अचिन्हित दीर्घ) ptr >> PAGE_SHIFT) & ZPCI_PT_MASK;
पूर्ण

अटल अंतरभूत व्योम set_pt_pfaa(अचिन्हित दीर्घ *entry, व्योम *pfaa)
अणु
	*entry &= ZPCI_PTE_FLAG_MASK;
	*entry |= ((अचिन्हित दीर्घ) pfaa & ZPCI_PTE_ADDR_MASK);
पूर्ण

अटल अंतरभूत व्योम set_rt_sto(अचिन्हित दीर्घ *entry, व्योम *sto)
अणु
	*entry &= ZPCI_RTE_FLAG_MASK;
	*entry |= ((अचिन्हित दीर्घ) sto & ZPCI_RTE_ADDR_MASK);
	*entry |= ZPCI_TABLE_TYPE_RTX;
पूर्ण

अटल अंतरभूत व्योम set_st_pto(अचिन्हित दीर्घ *entry, व्योम *pto)
अणु
	*entry &= ZPCI_STE_FLAG_MASK;
	*entry |= ((अचिन्हित दीर्घ) pto & ZPCI_STE_ADDR_MASK);
	*entry |= ZPCI_TABLE_TYPE_SX;
पूर्ण

अटल अंतरभूत व्योम validate_rt_entry(अचिन्हित दीर्घ *entry)
अणु
	*entry &= ~ZPCI_TABLE_VALID_MASK;
	*entry &= ~ZPCI_TABLE_OFFSET_MASK;
	*entry |= ZPCI_TABLE_VALID;
	*entry |= ZPCI_TABLE_LEN_RTX;
पूर्ण

अटल अंतरभूत व्योम validate_st_entry(अचिन्हित दीर्घ *entry)
अणु
	*entry &= ~ZPCI_TABLE_VALID_MASK;
	*entry |= ZPCI_TABLE_VALID;
पूर्ण

अटल अंतरभूत व्योम invalidate_pt_entry(अचिन्हित दीर्घ *entry)
अणु
	WARN_ON_ONCE((*entry & ZPCI_PTE_VALID_MASK) == ZPCI_PTE_INVALID);
	*entry &= ~ZPCI_PTE_VALID_MASK;
	*entry |= ZPCI_PTE_INVALID;
पूर्ण

अटल अंतरभूत व्योम validate_pt_entry(अचिन्हित दीर्घ *entry)
अणु
	WARN_ON_ONCE((*entry & ZPCI_PTE_VALID_MASK) == ZPCI_PTE_VALID);
	*entry &= ~ZPCI_PTE_VALID_MASK;
	*entry |= ZPCI_PTE_VALID;
पूर्ण

अटल अंतरभूत व्योम entry_set_रक्षित(अचिन्हित दीर्घ *entry)
अणु
	*entry &= ~ZPCI_TABLE_PROT_MASK;
	*entry |= ZPCI_TABLE_PROTECTED;
पूर्ण

अटल अंतरभूत व्योम entry_clr_रक्षित(अचिन्हित दीर्घ *entry)
अणु
	*entry &= ~ZPCI_TABLE_PROT_MASK;
	*entry |= ZPCI_TABLE_UNPROTECTED;
पूर्ण

अटल अंतरभूत पूर्णांक reg_entry_isvalid(अचिन्हित दीर्घ entry)
अणु
	वापस (entry & ZPCI_TABLE_VALID_MASK) == ZPCI_TABLE_VALID;
पूर्ण

अटल अंतरभूत पूर्णांक pt_entry_isvalid(अचिन्हित दीर्घ entry)
अणु
	वापस (entry & ZPCI_PTE_VALID_MASK) == ZPCI_PTE_VALID;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ *get_rt_sto(अचिन्हित दीर्घ entry)
अणु
	वापस ((entry & ZPCI_TABLE_TYPE_MASK) == ZPCI_TABLE_TYPE_RTX)
		? (अचिन्हित दीर्घ *) (entry & ZPCI_RTE_ADDR_MASK)
		: शून्य;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ *get_st_pto(अचिन्हित दीर्घ entry)
अणु
	वापस ((entry & ZPCI_TABLE_TYPE_MASK) == ZPCI_TABLE_TYPE_SX)
		? (अचिन्हित दीर्घ *) (entry & ZPCI_STE_ADDR_MASK)
		: शून्य;
पूर्ण

/* Prototypes */
पूर्णांक zpci_dma_init_device(काष्ठा zpci_dev *);
व्योम zpci_dma_निकास_device(काष्ठा zpci_dev *);
व्योम dma_मुक्त_seg_table(अचिन्हित दीर्घ);
अचिन्हित दीर्घ *dma_alloc_cpu_table(व्योम);
व्योम dma_cleanup_tables(अचिन्हित दीर्घ *);
अचिन्हित दीर्घ *dma_walk_cpu_trans(अचिन्हित दीर्घ *rto, dma_addr_t dma_addr);
व्योम dma_update_cpu_trans(अचिन्हित दीर्घ *entry, व्योम *page_addr, पूर्णांक flags);

बाह्य स्थिर काष्ठा dma_map_ops s390_pci_dma_ops;


#पूर्ण_अगर
