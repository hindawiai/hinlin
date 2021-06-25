<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ALPHA_CIA__H__
#घोषणा __ALPHA_CIA__H__

/* Define to experiment with fitting everything पूर्णांकo one 512MB HAE winकरोw.  */
#घोषणा CIA_ONE_HAE_WINDOW 1

#समावेश <linux/types.h>
#समावेश <यंत्र/compiler.h>

/*
 * CIA is the पूर्णांकernal name क्रम the 21171 chipset which provides
 * memory controller and PCI access क्रम the 21164 chip based प्रणालीs.
 * Also supported here is the 21172 (CIA-2) and 21174 (PYXIS).
 *
 * The lineage is a bit confused, since the 21174 was reportedly started
 * from the 21171 Pass 1 mask, and so is missing bug fixes that appear
 * in 21171 Pass 2 and 21172, but it also contains additional features.
 *
 * This file is based on:
 *
 * DECchip 21171 Core Logic Chipset
 * Technical Reference Manual
 *
 * EC-QE18B-TE
 *
 * david.rusling@reo.mts.dec.com Initial Version.
 *
 */

/*
 * CIA ADDRESS BIT DEFINITIONS
 *
 *  3333 3333 3322 2222 2222 1111 1111 11
 *  9876 5432 1098 7654 3210 9876 5432 1098 7654 3210
 *  ---- ---- ---- ---- ---- ---- ---- ---- ---- ----
 *  1                                             000
 *  ---- ---- ---- ---- ---- ---- ---- ---- ---- ----
 *  |                                             |\|
 *  |                               Byte Enable --+ |
 *  |                             Transfer Length --+
 *  +-- IO space, not cached
 *
 *   Byte      Transfer
 *   Enable    Length    Transfer  Byte    Address
 *   adr<6:5>  adr<4:3>  Length    Enable  Adder
 *   ---------------------------------------------
 *      00        00      Byte      1110   0x000
 *      01        00      Byte      1101   0x020
 *      10        00      Byte      1011   0x040
 *      11        00      Byte      0111   0x060
 *
 *      00        01      Word      1100   0x008
 *      01        01      Word      1001   0x028 <= Not supported in this code.
 *      10        01      Word      0011   0x048
 *
 *      00        10      Tribyte   1000   0x010
 *      01        10      Tribyte   0001   0x030
 *
 *      10        11      Longword  0000   0x058
 *
 *      Note that byte enables are निश्चितed low.
 *
 */

#घोषणा CIA_MEM_R1_MASK 0x1fffffff  /* SPARSE Mem region 1 mask is 29 bits */
#घोषणा CIA_MEM_R2_MASK 0x07ffffff  /* SPARSE Mem region 2 mask is 27 bits */
#घोषणा CIA_MEM_R3_MASK 0x03ffffff  /* SPARSE Mem region 3 mask is 26 bits */

/*
 * 21171-CA Control and Status Registers
 */
#घोषणा CIA_IOC_CIA_REV			(IDENT_ADDR + 0x8740000080UL)
#  define CIA_REV_MASK			0xff
#घोषणा CIA_IOC_PCI_LAT			(IDENT_ADDR + 0x87400000C0UL)
#घोषणा CIA_IOC_CIA_CTRL		(IDENT_ADDR + 0x8740000100UL)
#  define CIA_CTRL_PCI_EN		(1 << 0)
#  define CIA_CTRL_PCI_LOCK_EN		(1 << 1)
#  define CIA_CTRL_PCI_LOOP_EN		(1 << 2)
#  define CIA_CTRL_FST_BB_EN		(1 << 3)
#  define CIA_CTRL_PCI_MST_EN		(1 << 4)
#  define CIA_CTRL_PCI_MEM_EN		(1 << 5)
#  define CIA_CTRL_PCI_REQ64_EN		(1 << 6)
#  define CIA_CTRL_PCI_ACK64_EN		(1 << 7)
#  define CIA_CTRL_ADDR_PE_EN		(1 << 8)
#  define CIA_CTRL_PERR_EN		(1 << 9)
#  define CIA_CTRL_FILL_ERR_EN		(1 << 10)
#  define CIA_CTRL_MCHK_ERR_EN		(1 << 11)
#  define CIA_CTRL_ECC_CHK_EN		(1 << 12)
#  define CIA_CTRL_ASSERT_IDLE_BC	(1 << 13)
#  define CIA_CTRL_COM_IDLE_BC		(1 << 14)
#  define CIA_CTRL_CSR_IOA_BYPASS	(1 << 15)
#  define CIA_CTRL_IO_FLUSHREQ_EN	(1 << 16)
#  define CIA_CTRL_CPU_FLUSHREQ_EN	(1 << 17)
#  define CIA_CTRL_ARB_CPU_EN		(1 << 18)
#  define CIA_CTRL_EN_ARB_LINK		(1 << 19)
#  define CIA_CTRL_RD_TYPE_SHIFT	20
#  define CIA_CTRL_RL_TYPE_SHIFT	24
#  define CIA_CTRL_RM_TYPE_SHIFT	28
#  define CIA_CTRL_EN_DMA_RD_PERF	(1 << 31)
#घोषणा CIA_IOC_CIA_CNFG		(IDENT_ADDR + 0x8740000140UL)
#  define CIA_CNFG_IOA_BWEN		(1 << 0)
#  define CIA_CNFG_PCI_MWEN		(1 << 4)
#  define CIA_CNFG_PCI_DWEN		(1 << 5)
#  define CIA_CNFG_PCI_WLEN		(1 << 8)
#घोषणा CIA_IOC_FLASH_CTRL		(IDENT_ADDR + 0x8740000200UL)
#घोषणा CIA_IOC_HAE_MEM			(IDENT_ADDR + 0x8740000400UL)
#घोषणा CIA_IOC_HAE_IO			(IDENT_ADDR + 0x8740000440UL)
#घोषणा CIA_IOC_CFG			(IDENT_ADDR + 0x8740000480UL)
#घोषणा CIA_IOC_CACK_EN			(IDENT_ADDR + 0x8740000600UL)
#  define CIA_CACK_EN_LOCK_EN		(1 << 0)
#  define CIA_CACK_EN_MB_EN		(1 << 1)
#  define CIA_CACK_EN_SET_सूचीTY_EN	(1 << 2)
#  define CIA_CACK_EN_BC_VICTIM_EN	(1 << 3)


/*
 * 21171-CA Diagnostic Registers
 */
#घोषणा CIA_IOC_CIA_DIAG		(IDENT_ADDR + 0x8740002000UL)
#घोषणा CIA_IOC_DIAG_CHECK		(IDENT_ADDR + 0x8740003000UL)

/*
 * 21171-CA Perक्रमmance Monitor रेजिस्टरs
 */
#घोषणा CIA_IOC_PERF_MONITOR		(IDENT_ADDR + 0x8740004000UL)
#घोषणा CIA_IOC_PERF_CONTROL		(IDENT_ADDR + 0x8740004040UL)

/*
 * 21171-CA Error रेजिस्टरs
 */
#घोषणा CIA_IOC_CPU_ERR0		(IDENT_ADDR + 0x8740008000UL)
#घोषणा CIA_IOC_CPU_ERR1		(IDENT_ADDR + 0x8740008040UL)
#घोषणा CIA_IOC_CIA_ERR			(IDENT_ADDR + 0x8740008200UL)
#  define CIA_ERR_COR_ERR		(1 << 0)
#  define CIA_ERR_UN_COR_ERR		(1 << 1)
#  define CIA_ERR_CPU_PE		(1 << 2)
#  define CIA_ERR_MEM_NEM		(1 << 3)
#  define CIA_ERR_PCI_SERR		(1 << 4)
#  define CIA_ERR_PERR			(1 << 5)
#  define CIA_ERR_PCI_ADDR_PE		(1 << 6)
#  define CIA_ERR_RCVD_MAS_ABT		(1 << 7)
#  define CIA_ERR_RCVD_TAR_ABT		(1 << 8)
#  define CIA_ERR_PA_PTE_INV		(1 << 9)
#  define CIA_ERR_FROM_WRT_ERR		(1 << 10)
#  define CIA_ERR_IOA_TIMEOUT		(1 << 11)
#  define CIA_ERR_LOST_CORR_ERR		(1 << 16)
#  define CIA_ERR_LOST_UN_CORR_ERR	(1 << 17)
#  define CIA_ERR_LOST_CPU_PE		(1 << 18)
#  define CIA_ERR_LOST_MEM_NEM		(1 << 19)
#  define CIA_ERR_LOST_PERR		(1 << 21)
#  define CIA_ERR_LOST_PCI_ADDR_PE	(1 << 22)
#  define CIA_ERR_LOST_RCVD_MAS_ABT	(1 << 23)
#  define CIA_ERR_LOST_RCVD_TAR_ABT	(1 << 24)
#  define CIA_ERR_LOST_PA_PTE_INV	(1 << 25)
#  define CIA_ERR_LOST_FROM_WRT_ERR	(1 << 26)
#  define CIA_ERR_LOST_IOA_TIMEOUT	(1 << 27)
#  define CIA_ERR_VALID			(1 << 31)
#घोषणा CIA_IOC_CIA_STAT		(IDENT_ADDR + 0x8740008240UL)
#घोषणा CIA_IOC_ERR_MASK		(IDENT_ADDR + 0x8740008280UL)
#घोषणा CIA_IOC_CIA_SYN			(IDENT_ADDR + 0x8740008300UL)
#घोषणा CIA_IOC_MEM_ERR0		(IDENT_ADDR + 0x8740008400UL)
#घोषणा CIA_IOC_MEM_ERR1		(IDENT_ADDR + 0x8740008440UL)
#घोषणा CIA_IOC_PCI_ERR0		(IDENT_ADDR + 0x8740008800UL)
#घोषणा CIA_IOC_PCI_ERR1		(IDENT_ADDR + 0x8740008840UL)
#घोषणा CIA_IOC_PCI_ERR3		(IDENT_ADDR + 0x8740008880UL)

/*
 * 21171-CA System configuration रेजिस्टरs
 */
#घोषणा CIA_IOC_MCR			(IDENT_ADDR + 0x8750000000UL)
#घोषणा CIA_IOC_MBA0			(IDENT_ADDR + 0x8750000600UL)
#घोषणा CIA_IOC_MBA2			(IDENT_ADDR + 0x8750000680UL)
#घोषणा CIA_IOC_MBA4			(IDENT_ADDR + 0x8750000700UL)
#घोषणा CIA_IOC_MBA6			(IDENT_ADDR + 0x8750000780UL)
#घोषणा CIA_IOC_MBA8			(IDENT_ADDR + 0x8750000800UL)
#घोषणा CIA_IOC_MBAA			(IDENT_ADDR + 0x8750000880UL)
#घोषणा CIA_IOC_MBAC			(IDENT_ADDR + 0x8750000900UL)
#घोषणा CIA_IOC_MBAE			(IDENT_ADDR + 0x8750000980UL)
#घोषणा CIA_IOC_TMG0			(IDENT_ADDR + 0x8750000B00UL)
#घोषणा CIA_IOC_TMG1			(IDENT_ADDR + 0x8750000B40UL)
#घोषणा CIA_IOC_TMG2			(IDENT_ADDR + 0x8750000B80UL)

/*
 * 2117A-CA PCI Address and Scatter-Gather Registers.
 */
#घोषणा CIA_IOC_PCI_TBIA		(IDENT_ADDR + 0x8760000100UL)

#घोषणा CIA_IOC_PCI_W0_BASE		(IDENT_ADDR + 0x8760000400UL)
#घोषणा CIA_IOC_PCI_W0_MASK		(IDENT_ADDR + 0x8760000440UL)
#घोषणा CIA_IOC_PCI_T0_BASE		(IDENT_ADDR + 0x8760000480UL)

#घोषणा CIA_IOC_PCI_W1_BASE		(IDENT_ADDR + 0x8760000500UL)
#घोषणा CIA_IOC_PCI_W1_MASK		(IDENT_ADDR + 0x8760000540UL)
#घोषणा CIA_IOC_PCI_T1_BASE		(IDENT_ADDR + 0x8760000580UL)

#घोषणा CIA_IOC_PCI_W2_BASE		(IDENT_ADDR + 0x8760000600UL)
#घोषणा CIA_IOC_PCI_W2_MASK		(IDENT_ADDR + 0x8760000640UL)
#घोषणा CIA_IOC_PCI_T2_BASE		(IDENT_ADDR + 0x8760000680UL)

#घोषणा CIA_IOC_PCI_W3_BASE		(IDENT_ADDR + 0x8760000700UL)
#घोषणा CIA_IOC_PCI_W3_MASK		(IDENT_ADDR + 0x8760000740UL)
#घोषणा CIA_IOC_PCI_T3_BASE		(IDENT_ADDR + 0x8760000780UL)

#घोषणा CIA_IOC_PCI_Wn_BASE(N)	(IDENT_ADDR + 0x8760000400UL + (N)*0x100) 
#घोषणा CIA_IOC_PCI_Wn_MASK(N)	(IDENT_ADDR + 0x8760000440UL + (N)*0x100) 
#घोषणा CIA_IOC_PCI_Tn_BASE(N)	(IDENT_ADDR + 0x8760000480UL + (N)*0x100) 

#घोषणा CIA_IOC_PCI_W_DAC		(IDENT_ADDR + 0x87600007C0UL)

/*
 * 2117A-CA Address Translation Registers.
 */

/* 8 tag रेजिस्टरs, the first 4 of which are lockable.  */
#घोषणा CIA_IOC_TB_TAGn(n) \
	(IDENT_ADDR + 0x8760000800UL + (n)*0x40)

/* 4 page रेजिस्टरs per tag रेजिस्टर.  */
#घोषणा CIA_IOC_TBn_PAGEm(n,m) \
	(IDENT_ADDR + 0x8760001000UL + (n)*0x100 + (m)*0x40)

/*
 * Memory spaces:
 */
#घोषणा CIA_IACK_SC			(IDENT_ADDR + 0x8720000000UL)
#घोषणा CIA_CONF			(IDENT_ADDR + 0x8700000000UL)
#घोषणा CIA_IO				(IDENT_ADDR + 0x8580000000UL)
#घोषणा CIA_SPARSE_MEM			(IDENT_ADDR + 0x8000000000UL)
#घोषणा CIA_SPARSE_MEM_R2		(IDENT_ADDR + 0x8400000000UL)
#घोषणा CIA_SPARSE_MEM_R3		(IDENT_ADDR + 0x8500000000UL)
#घोषणा CIA_DENSE_MEM		        (IDENT_ADDR + 0x8600000000UL)
#घोषणा CIA_BW_MEM			(IDENT_ADDR + 0x8800000000UL)
#घोषणा CIA_BW_IO			(IDENT_ADDR + 0x8900000000UL)
#घोषणा CIA_BW_CFG_0			(IDENT_ADDR + 0x8a00000000UL)
#घोषणा CIA_BW_CFG_1			(IDENT_ADDR + 0x8b00000000UL)

/*
 * ALCOR's GRU ASIC रेजिस्टरs
 */
#घोषणा GRU_INT_REQ			(IDENT_ADDR + 0x8780000000UL)
#घोषणा GRU_INT_MASK			(IDENT_ADDR + 0x8780000040UL)
#घोषणा GRU_INT_EDGE			(IDENT_ADDR + 0x8780000080UL)
#घोषणा GRU_INT_HILO			(IDENT_ADDR + 0x87800000C0UL)
#घोषणा GRU_INT_CLEAR			(IDENT_ADDR + 0x8780000100UL)

#घोषणा GRU_CACHE_CNFG			(IDENT_ADDR + 0x8780000200UL)
#घोषणा GRU_SCR				(IDENT_ADDR + 0x8780000300UL)
#घोषणा GRU_LED				(IDENT_ADDR + 0x8780000800UL)
#घोषणा GRU_RESET			(IDENT_ADDR + 0x8780000900UL)

#घोषणा ALCOR_GRU_INT_REQ_BITS		0x800fffffUL
#घोषणा XLT_GRU_INT_REQ_BITS		0x80003fffUL
#घोषणा GRU_INT_REQ_BITS		(alpha_mv.sys.cia.gru_पूर्णांक_req_bits+0)

/*
 * PYXIS पूर्णांकerrupt control रेजिस्टरs
 */
#घोषणा PYXIS_INT_REQ			(IDENT_ADDR + 0x87A0000000UL)
#घोषणा PYXIS_INT_MASK			(IDENT_ADDR + 0x87A0000040UL)
#घोषणा PYXIS_INT_HILO			(IDENT_ADDR + 0x87A00000C0UL)
#घोषणा PYXIS_INT_ROUTE			(IDENT_ADDR + 0x87A0000140UL)
#घोषणा PYXIS_GPO			(IDENT_ADDR + 0x87A0000180UL)
#घोषणा PYXIS_INT_CNFG			(IDENT_ADDR + 0x87A00001C0UL)
#घोषणा PYXIS_RT_COUNT			(IDENT_ADDR + 0x87A0000200UL)
#घोषणा PYXIS_INT_TIME			(IDENT_ADDR + 0x87A0000240UL)
#घोषणा PYXIS_IIC_CTRL			(IDENT_ADDR + 0x87A00002C0UL)
#घोषणा PYXIS_RESET			(IDENT_ADDR + 0x8780000900UL)

/* Offset between ram physical addresses and pci64 DAC bus addresses.  */
#घोषणा PYXIS_DAC_OFFSET		(1UL << 40)

/*
 * Data काष्ठाure क्रम handling CIA machine checks.
 */

/* System-specअगरic info.  */
काष्ठा el_CIA_sysdata_mcheck अणु
	अचिन्हित दीर्घ	cpu_err0;
	अचिन्हित दीर्घ	cpu_err1;
	अचिन्हित दीर्घ	cia_err;
	अचिन्हित दीर्घ	cia_stat;
	अचिन्हित दीर्घ	err_mask;
	अचिन्हित दीर्घ	cia_syn;
	अचिन्हित दीर्घ	mem_err0;
	अचिन्हित दीर्घ	mem_err1;
	अचिन्हित दीर्घ	pci_err0;
	अचिन्हित दीर्घ	pci_err1;
	अचिन्हित दीर्घ	pci_err2;
पूर्ण;


#अगर_घोषित __KERNEL__

#अगर_अघोषित __EXTERN_INLINE
/* Do not touch, this should *NOT* be अटल अंतरभूत */
#घोषणा __EXTERN_INLINE बाह्य अंतरभूत
#घोषणा __IO_EXTERN_INLINE
#पूर्ण_अगर

/*
 * I/O functions:
 *
 * CIA (the 2117x PCI/memory support chipset क्रम the EV5 (21164)
 * series of processors uses a sparse address mapping scheme to
 * get at PCI memory and I/O.
 */

/*
 * Memory functions.  64-bit and 32-bit accesses are करोne through
 * dense memory space, everything अन्यथा through sparse space.
 *
 * For पढ़ोing and writing 8 and 16 bit quantities we need to
 * go through one of the three sparse address mapping regions
 * and use the HAE_MEM CSR to provide some bits of the address.
 * The following few routines use only sparse address region 1
 * which gives 1Gbyte of accessible space which relates exactly
 * to the amount of PCI memory mapping *पूर्णांकo* प्रणाली address space.
 * See p 6-17 of the specअगरication but it looks something like this:
 *
 * 21164 Address:
 *
 *          3         2         1
 * 9876543210987654321098765432109876543210
 * 1ZZZZ0.PCI.QW.Address............BBLL
 *
 * ZZ = SBZ
 * BB = Byte offset
 * LL = Transfer length
 *
 * PCI Address:
 *
 * 3         2         1
 * 10987654321098765432109876543210
 * HHH....PCI.QW.Address........ 00
 *
 * HHH = 31:29 HAE_MEM CSR
 *
 */

#घोषणा vip	अस्थिर पूर्णांक __क्रमce *
#घोषणा vuip	अस्थिर अचिन्हित पूर्णांक __क्रमce *
#घोषणा vulp	अस्थिर अचिन्हित दीर्घ __क्रमce *

__EXTERN_INLINE अचिन्हित पूर्णांक cia_ioपढ़ो8(स्थिर व्योम __iomem *xaddr)
अणु
	अचिन्हित दीर्घ addr = (अचिन्हित दीर्घ) xaddr;
	अचिन्हित दीर्घ result, base_and_type;

	अगर (addr >= CIA_DENSE_MEM)
		base_and_type = CIA_SPARSE_MEM + 0x00;
	अन्यथा
		base_and_type = CIA_IO + 0x00;

	/* We can use CIA_MEM_R1_MASK क्रम io ports too, since it is large
	   enough to cover all io ports, and smaller than CIA_IO.  */
	addr &= CIA_MEM_R1_MASK;
	result = *(vip) ((addr << 5) + base_and_type);
	वापस __kernel_extbl(result, addr & 3);
पूर्ण

__EXTERN_INLINE व्योम cia_ioग_लिखो8(u8 b, व्योम __iomem *xaddr)
अणु
	अचिन्हित दीर्घ addr = (अचिन्हित दीर्घ) xaddr;
	अचिन्हित दीर्घ w, base_and_type;

	अगर (addr >= CIA_DENSE_MEM)
		base_and_type = CIA_SPARSE_MEM + 0x00;
	अन्यथा
		base_and_type = CIA_IO + 0x00;

	addr &= CIA_MEM_R1_MASK;
	w = __kernel_insbl(b, addr & 3);
	*(vuip) ((addr << 5) + base_and_type) = w;
पूर्ण

__EXTERN_INLINE अचिन्हित पूर्णांक cia_ioपढ़ो16(स्थिर व्योम __iomem *xaddr)
अणु
	अचिन्हित दीर्घ addr = (अचिन्हित दीर्घ) xaddr;
	अचिन्हित दीर्घ result, base_and_type;

	अगर (addr >= CIA_DENSE_MEM)
		base_and_type = CIA_SPARSE_MEM + 0x08;
	अन्यथा
		base_and_type = CIA_IO + 0x08;

	addr &= CIA_MEM_R1_MASK;
	result = *(vip) ((addr << 5) + base_and_type);
	वापस __kernel_extwl(result, addr & 3);
पूर्ण

__EXTERN_INLINE व्योम cia_ioग_लिखो16(u16 b, व्योम __iomem *xaddr)
अणु
	अचिन्हित दीर्घ addr = (अचिन्हित दीर्घ) xaddr;
	अचिन्हित दीर्घ w, base_and_type;

	अगर (addr >= CIA_DENSE_MEM)
		base_and_type = CIA_SPARSE_MEM + 0x08;
	अन्यथा
		base_and_type = CIA_IO + 0x08;

	addr &= CIA_MEM_R1_MASK;
	w = __kernel_inswl(b, addr & 3);
	*(vuip) ((addr << 5) + base_and_type) = w;
पूर्ण

__EXTERN_INLINE अचिन्हित पूर्णांक cia_ioपढ़ो32(स्थिर व्योम __iomem *xaddr)
अणु
	अचिन्हित दीर्घ addr = (अचिन्हित दीर्घ) xaddr;
	अगर (addr < CIA_DENSE_MEM)
		addr = ((addr - CIA_IO) << 5) + CIA_IO + 0x18;
	वापस *(vuip)addr;
पूर्ण

__EXTERN_INLINE व्योम cia_ioग_लिखो32(u32 b, व्योम __iomem *xaddr)
अणु
	अचिन्हित दीर्घ addr = (अचिन्हित दीर्घ) xaddr;
	अगर (addr < CIA_DENSE_MEM)
		addr = ((addr - CIA_IO) << 5) + CIA_IO + 0x18;
	*(vuip)addr = b;
पूर्ण

__EXTERN_INLINE व्योम __iomem *cia_ioporपंचांगap(अचिन्हित दीर्घ addr)
अणु
	वापस (व्योम __iomem *)(addr + CIA_IO);
पूर्ण

__EXTERN_INLINE व्योम __iomem *cia_ioremap(अचिन्हित दीर्घ addr,
					  अचिन्हित दीर्घ size)
अणु
	वापस (व्योम __iomem *)(addr + CIA_DENSE_MEM);
पूर्ण

__EXTERN_INLINE पूर्णांक cia_is_ioaddr(अचिन्हित दीर्घ addr)
अणु
	वापस addr >= IDENT_ADDR + 0x8000000000UL;
पूर्ण

__EXTERN_INLINE पूर्णांक cia_is_mmio(स्थिर अस्थिर व्योम __iomem *addr)
अणु
	वापस (अचिन्हित दीर्घ)addr >= CIA_DENSE_MEM;
पूर्ण

__EXTERN_INLINE व्योम __iomem *cia_bwx_ioporपंचांगap(अचिन्हित दीर्घ addr)
अणु
	वापस (व्योम __iomem *)(addr + CIA_BW_IO);
पूर्ण

__EXTERN_INLINE व्योम __iomem *cia_bwx_ioremap(अचिन्हित दीर्घ addr,
					      अचिन्हित दीर्घ size)
अणु
	वापस (व्योम __iomem *)(addr + CIA_BW_MEM);
पूर्ण

__EXTERN_INLINE पूर्णांक cia_bwx_is_ioaddr(अचिन्हित दीर्घ addr)
अणु
	वापस addr >= IDENT_ADDR + 0x8000000000UL;
पूर्ण

__EXTERN_INLINE पूर्णांक cia_bwx_is_mmio(स्थिर अस्थिर व्योम __iomem *addr)
अणु
	वापस (अचिन्हित दीर्घ)addr < CIA_BW_IO;
पूर्ण

#अघोषित vip
#अघोषित vuip
#अघोषित vulp

#अघोषित __IO_PREFIX
#घोषणा __IO_PREFIX		cia
#घोषणा cia_trivial_rw_bw	2
#घोषणा cia_trivial_rw_lq	1
#घोषणा cia_trivial_io_bw	0
#घोषणा cia_trivial_io_lq	0
#घोषणा cia_trivial_iounmap	1
#समावेश <यंत्र/io_trivial.h>

#अघोषित __IO_PREFIX
#घोषणा __IO_PREFIX		cia_bwx
#घोषणा cia_bwx_trivial_rw_bw	1
#घोषणा cia_bwx_trivial_rw_lq	1
#घोषणा cia_bwx_trivial_io_bw	1
#घोषणा cia_bwx_trivial_io_lq	1
#घोषणा cia_bwx_trivial_iounmap	1
#समावेश <यंत्र/io_trivial.h>

#अघोषित __IO_PREFIX
#अगर_घोषित CONFIG_ALPHA_PYXIS
#घोषणा __IO_PREFIX		cia_bwx
#अन्यथा
#घोषणा __IO_PREFIX		cia
#पूर्ण_अगर

#अगर_घोषित __IO_EXTERN_INLINE
#अघोषित __EXTERN_INLINE
#अघोषित __IO_EXTERN_INLINE
#पूर्ण_अगर

#पूर्ण_अगर /* __KERNEL__ */

#पूर्ण_अगर /* __ALPHA_CIA__H__ */
