<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *	linux/arch/alpha/kernel/pci_impl.h
 *
 * This file contains declarations and अंतरभूत functions क्रम पूर्णांकerfacing
 * with the PCI initialization routines.
 */

काष्ठा pci_dev;
काष्ठा pci_controller;
काष्ठा pci_iommu_arena;

/*
 * We can't just blindly use 64K क्रम machines with EISA busses; they
 * may also have PCI-PCI bridges present, and then we'd configure the
 * bridge incorrectly.
 *
 * Also, we start at 0x8000 or 0x9000, in hopes to get all devices'
 * IO space areas allocated *beक्रमe* 0xC000; this is because certain
 * BIOSes (Millennium क्रम one) use PCI Config space "mechanism #2"
 * accesses to probe the bus. If a device's रेजिस्टरs appear at 0xC000,
 * it may see an INx/OUTx at that address during BIOS emulation of the
 * VGA BIOS, and some cards, notably Adaptec 2940UW, take mortal offense.
 */

#घोषणा EISA_DEFAULT_IO_BASE	0x9000	/* start above 8th slot */
#घोषणा DEFAULT_IO_BASE		0x8000	/* start at 8th slot */

/*
 * We try to make the DEFAULT_MEM_BASE addresses *always* have more than
 * a single bit set. This is so that devices like the broken Myrinet card
 * will always have a PCI memory address that will never match a IDSEL
 * address in PCI Config space, which can cause problems with early rev cards.
 */

/*
 * An XL is AVANTI (APECS) family, *but* it has only 27 bits of ISA address
 * that get passed through the PCI<->ISA bridge chip. Although this causes
 * us to set the PCI->Mem winकरोw bases lower than normal, we still allocate
 * PCI bus devices' memory addresses *below* the low DMA mapping winकरोw,
 * and hope they fit below 64Mb (to aव्योम conflicts), and so that they can
 * be accessed via SPARSE space.
 *
 * We accept the risk that a broken Myrinet card will be put पूर्णांकo a true XL
 * and thus can more easily run पूर्णांकo the problem described below.
 */
#घोषणा XL_DEFAULT_MEM_BASE ((16+2)*1024*1024) /* 16M to 64M-1 is avail */

/*
 * APECS and LCA have only 34 bits क्रम physical addresses, thus limiting PCI
 * bus memory addresses क्रम SPARSE access to be less than 128Mb.
 */
#घोषणा APECS_AND_LCA_DEFAULT_MEM_BASE ((16+2)*1024*1024)

/*
 * Because MCPCIA and T2 core logic support more bits क्रम
 * physical addresses, they should allow an expanded range of SPARSE
 * memory addresses.  However, we करो not use them all, in order to
 * aव्योम the HAE manipulation that would be needed.
 */
#घोषणा MCPCIA_DEFAULT_MEM_BASE ((32+2)*1024*1024)
#घोषणा T2_DEFAULT_MEM_BASE ((16+1)*1024*1024)

/*
 * Because CIA and PYXIS have more bits क्रम physical addresses,
 * they support an expanded range of SPARSE memory addresses.
 */
#घोषणा DEFAULT_MEM_BASE ((128+16)*1024*1024)

/* ??? Experimenting with no HAE क्रम CIA.  */
#घोषणा CIA_DEFAULT_MEM_BASE ((32+2)*1024*1024)

#घोषणा IRONGATE_DEFAULT_MEM_BASE ((256*8-16)*1024*1024)

#घोषणा DEFAULT_AGP_APER_SIZE	(64*1024*1024)

/* 
 * A small note about bridges and पूर्णांकerrupts.  The DECchip 21050 (and
 * later) adheres to the PCI-PCI bridge specअगरication.  This says that
 * the पूर्णांकerrupts on the other side of a bridge are swizzled in the
 * following manner:
 *
 * Dev    Interrupt   Interrupt 
 *        Pin on      Pin on 
 *        Device      Connector
 *
 *   4    A           A
 *        B           B
 *        C           C
 *        D           D
 * 
 *   5    A           B
 *        B           C
 *        C           D
 *        D           A
 *
 *   6    A           C
 *        B           D
 *        C           A
 *        D           B
 *
 *   7    A           D
 *        B           A
 *        C           B
 *        D           C
 *
 *   Where A = pin 1, B = pin 2 and so on and pin=0 = शेष = A.
 *   Thus, each swizzle is ((pin-1) + (device#-4)) % 4
 *
 *   pci_swizzle_पूर्णांकerrupt_pin() swizzles क्रम exactly one bridge.  The routine
 *   pci_common_swizzle() handles multiple bridges.  But there are a
 *   couple boards that करो strange things.
 */


/* The following macro is used to implement the table-based irq mapping
   function क्रम all single-bus Alphas.  */

#घोषणा COMMON_TABLE_LOOKUP						\
(अणु दीर्घ _ctl_ = -1; 							\
   अगर (slot >= min_idsel && slot <= max_idsel && pin < irqs_per_slot)	\
     _ctl_ = irq_tab[slot - min_idsel][pin];				\
   _ctl_; पूर्ण)


/* A PCI IOMMU allocation arena.  There are typically two of these
   regions per bus.  */
/* ??? The 8400 has a 32-byte pte entry, and the entire table apparently
   lives directly on the host bridge (no tlb?).  We करोn't support this
   machine, but अगर we ever did, we'd need to parameterize all this quite
   a bit further.  Probably with per-bus operation tables.  */

काष्ठा pci_iommu_arena
अणु
	spinlock_t lock;
	काष्ठा pci_controller *hose;
#घोषणा IOMMU_INVALID_PTE 0x2 /* 32:63 bits MBZ */
#घोषणा IOMMU_RESERVED_PTE 0xface
	अचिन्हित दीर्घ *ptes;
	dma_addr_t dma_base;
	अचिन्हित पूर्णांक size;
	अचिन्हित पूर्णांक next_entry;
	अचिन्हित पूर्णांक align_entry;
पूर्ण;

#अगर defined(CONFIG_ALPHA_SRM) && \
    (defined(CONFIG_ALPHA_CIA) || defined(CONFIG_ALPHA_LCA) || \
     defined(CONFIG_ALPHA_AVANTI))
# define NEED_SRM_SAVE_RESTORE
#अन्यथा
# undef NEED_SRM_SAVE_RESTORE
#पूर्ण_अगर

#अगर defined(CONFIG_ALPHA_GENERIC) || defined(NEED_SRM_SAVE_RESTORE)
# define ALPHA_RESTORE_SRM_SETUP
#अन्यथा
# undef ALPHA_RESTORE_SRM_SETUP
#पूर्ण_अगर

#अगर_घोषित ALPHA_RESTORE_SRM_SETUP
बाह्य व्योम pci_restore_srm_config(व्योम);
#अन्यथा
#घोषणा pci_restore_srm_config()	करो अणुपूर्ण जबतक (0)
#पूर्ण_अगर

/* The hose list.  */
बाह्य काष्ठा pci_controller *hose_head, **hose_tail;
बाह्य काष्ठा pci_controller *pci_isa_hose;

बाह्य अचिन्हित दीर्घ alpha_agpgart_size;

बाह्य व्योम common_init_pci(व्योम);
#घोषणा common_swizzle pci_common_swizzle
बाह्य काष्ठा pci_controller *alloc_pci_controller(व्योम);
बाह्य काष्ठा resource *alloc_resource(व्योम);

बाह्य काष्ठा pci_iommu_arena *iommu_arena_new_node(पूर्णांक,
						    काष्ठा pci_controller *,
					            dma_addr_t, अचिन्हित दीर्घ,
					            अचिन्हित दीर्घ);
बाह्य काष्ठा pci_iommu_arena *iommu_arena_new(काष्ठा pci_controller *,
					       dma_addr_t, अचिन्हित दीर्घ,
					       अचिन्हित दीर्घ);
बाह्य स्थिर अक्षर *स्थिर pci_io_names[];
बाह्य स्थिर अक्षर *स्थिर pci_mem_names[];
बाह्य स्थिर अक्षर pci_hae0_name[];

बाह्य अचिन्हित दीर्घ size_क्रम_memory(अचिन्हित दीर्घ max);

बाह्य पूर्णांक iommu_reserve(काष्ठा pci_iommu_arena *, दीर्घ, दीर्घ);
बाह्य पूर्णांक iommu_release(काष्ठा pci_iommu_arena *, दीर्घ, दीर्घ);
बाह्य पूर्णांक iommu_bind(काष्ठा pci_iommu_arena *, दीर्घ, दीर्घ, काष्ठा page **);
बाह्य पूर्णांक iommu_unbind(काष्ठा pci_iommu_arena *, दीर्घ, दीर्घ);


