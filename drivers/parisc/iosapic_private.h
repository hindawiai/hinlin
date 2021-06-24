<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/* 
 *    Private काष्ठाs/स्थिरants क्रम PARISC IOSAPIC support
 *
 *    Copyright (C) 2000 Hewlett Packard (Grant Grundler)
 *    Copyright (C) 2000,2003 Grant Grundler (grundler at parisc-linux.org)
 *    Copyright (C) 2002 Matthew Wilcox (willy at parisc-linux.org)
 */

/*
** This file is निजी to iosapic driver.
** If stuff needs to be used by another driver, move it to a common file.
**
** WARNING: fields most data काष्ठाures here are ordered to make sure
**          they pack nicely क्रम 64-bit compilation. (ie माप(दीर्घ) == 8)
*/


/*
** Interrupt Routing Stuff
** -----------------------
** The पूर्णांकerrupt routing table consists of entries derived from
** MP Specअगरication Draft 1.5. There is one पूर्णांकerrupt routing 
** table per cell.  N- and L-class consist of a single cell.
*/
काष्ठा irt_entry अणु

	/* Entry Type 139 identअगरies an I/O SAPIC पूर्णांकerrupt entry */
	u8 entry_type;

	/* Entry Length 16 indicates entry is 16 bytes दीर्घ */
	u8 entry_length;

	/* 
	** Interrupt Type of 0 indicates a vectored पूर्णांकerrupt, 
	** all other values are reserved 
	*/
	u8 पूर्णांकerrupt_type;

	/* 
	** PO and EL
	** Polarity of SAPIC I/O input संकेतs: 
	**    00 = Reserved 
	**    01 = Active high 
	**    10 = Reserved 
	**    11 = Active low 
	** Trigger mode of SAPIC I/O input संकेतs: 
	**    00 = Reserved 
	**    01 = Edge-triggered 
	**    10 = Reserved 
	**    11 = Level-triggered
	*/
	u8 polarity_trigger;

	/* 
	** IRQ and DEVNO
	** irq identअगरies PCI पूर्णांकerrupt संकेत where
	**    0x0 corresponds to INT_A#, 
	**    0x1 corresponds to INT_B#, 
	**    0x2 corresponds to INT_C# 
	**    0x3 corresponds to INT_D# 
	** PCI device number where पूर्णांकerrupt originates 
	*/
	u8 src_bus_irq_devno;

	/* Source Bus ID identअगरies the bus where पूर्णांकerrupt संकेत comes from */
	u8 src_bus_id;

	/* 
	** Segment ID is unique across a protection करोमुख्य and
	** identअगरies a segment of PCI buses (reserved in 
	** MP Specअगरication Draft 1.5) 
	*/
	u8 src_seg_id;

	/* 
	** Destination I/O SAPIC INTIN# identअगरies the INTIN n pin 
	** to which the संकेत is connected 
	*/
	u8 dest_iosapic_पूर्णांकin;

	/* 
	** Destination I/O SAPIC Address identअगरies the I/O SAPIC 
	** to which the संकेत is connected 
	*/
	u64 dest_iosapic_addr;
पूर्ण;

#घोषणा IRT_IOSAPIC_TYPE   139
#घोषणा IRT_IOSAPIC_LENGTH 16

#घोषणा IRT_VECTORED_INTR  0

#घोषणा IRT_PO_MASK        0x3
#घोषणा IRT_ACTIVE_HI      1
#घोषणा IRT_ACTIVE_LO      3

#घोषणा IRT_EL_MASK        0x3
#घोषणा IRT_EL_SHIFT       2
#घोषणा IRT_EDGE_TRIG      1
#घोषणा IRT_LEVEL_TRIG     3

#घोषणा IRT_IRQ_MASK       0x3
#घोषणा IRT_DEV_MASK       0x1f
#घोषणा IRT_DEV_SHIFT      2

#घोषणा IRT_IRQ_DEVNO_MASK	((IRT_DEV_MASK << IRT_DEV_SHIFT) | IRT_IRQ_MASK)

#अगर_घोषित SUPPORT_MULTI_CELL
काष्ठा iosapic_irt अणु
        काष्ठा iosapic_irt *irt_next;  /* next routing table */
        काष्ठा irt_entry *irt_base;             /* पूर्णांकr routing table address */
        माप_प्रकार  irte_count;            /* number of entries in the table */
        माप_प्रकार  irte_size;             /* size (bytes) of each entry */
पूर्ण;
#पूर्ण_अगर

काष्ठा vector_info अणु
	काष्ठा iosapic_info *iosapic;	/* I/O SAPIC this vector is on */
	काष्ठा irt_entry *irte;		/* IRT entry */
	u32 __iomem *eoi_addr;		/* precalculate EOI reg address */
	u32	eoi_data;		/* IA64: ?       PA: swapped txn_data */
	पूर्णांक	txn_irq;		/* भव IRQ number क्रम processor */
	uदीर्घ	txn_addr;		/* IA64: id_eid  PA: partial HPA */
	u32	txn_data;		/* CPU पूर्णांकerrupt bit */
	u8	status;			/* status/flags */
	u8	irqline;		/* INTINn(IRQ) */
पूर्ण;


काष्ठा iosapic_info अणु
	काष्ठा iosapic_info *	isi_next;	/* list of I/O SAPIC */
	व्योम __iomem *		addr;		/* remapped address */
	अचिन्हित दीर्घ		isi_hpa;	/* physical base address */
	काष्ठा vector_info *	isi_vector;	/* IRdT (IRQ line) array */
	पूर्णांक			isi_num_vectors; /* size of IRdT array */
	पूर्णांक			isi_status;	/* status/flags */
	अचिन्हित पूर्णांक		isi_version;	/* DEBUG: data fr version reg */
पूर्ण;



#अगर_घोषित __IA64__
/*
** PA risc करोes NOT have any local sapics. IA64 करोes.
** PIB (Processor Interrupt Block) is handled by Astro or Dew (Stretch CEC).
**
** PA: Get id_eid from IRT and hardcode PIB to 0xfeeNNNN0
**     Emulate the data on PAT platक्रमms.
*/
काष्ठा local_sapic_info अणु
	काष्ठा local_sapic_info *lsi_next;      /* poपूर्णांक to next CPU info */
	पूर्णांक                     *lsi_cpu_id;    /* poपूर्णांक to logical CPU id */
	अचिन्हित दीर्घ           *lsi_id_eid;    /* poपूर्णांक to IA-64 CPU id */
	पूर्णांक                     *lsi_status;    /* poपूर्णांक to CPU status   */
	व्योम                    *lsi_निजी;   /* poपूर्णांक to special info */
पूर्ण;

/*
** "root" data काष्ठाure which ties everything together.
** Should always be able to start with sapic_root and locate
** the desired inक्रमmation.
*/
काष्ठा sapic_info अणु
	काष्ठा sapic_info	*si_next;	/* info is per cell */
	पूर्णांक                     si_cellid;      /* cell id */
	अचिन्हित पूर्णांक            si_status;       /* status  */
	अक्षर                    *si_pib_base;   /* पूर्णांकr blk base address */
	local_sapic_info_t      *si_local_info;
	io_sapic_info_t         *si_io_info;
	extपूर्णांक_info_t           *si_extपूर्णांक_info;/* External Intr info      */
पूर्ण;
#पूर्ण_अगर

