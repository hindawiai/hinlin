<शैली गुरु>
/*
 *  This program is मुक्त software; you can redistribute  it and/or modअगरy it
 *  under  the terms of  the GNU General  Public License as published by the
 *  Free Software Foundation;  either version 2 of the  License, or (at your
 *  option) any later version.
 *
 *  THIS  SOFTWARE  IS PROVIDED   ``AS  IS'' AND   ANY  EXPRESS OR IMPLIED
 *  WARRANTIES,   INCLUDING, BUT NOT  LIMITED  TO, THE IMPLIED WARRANTIES OF
 *  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN
 *  NO  EVENT  SHALL   THE AUTHOR  BE    LIABLE FOR ANY   सूचीECT, INसूचीECT,
 *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 *  NOT LIMITED   TO, PROCUREMENT OF  SUBSTITUTE GOODS  OR SERVICES; LOSS OF
 *  USE, DATA,  OR PROFITS; OR  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 *  ANY THEORY OF LIABILITY, WHETHER IN  CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 *  THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *  You should have received a copy of the  GNU General Public License aदीर्घ
 *  with this program; अगर not, ग_लिखो  to the Free Software Foundation, Inc.,
 *  675 Mass Ave, Cambridge, MA 02139, USA.
 *
 * Copyright 2004 IDT Inc. (rischelp@idt.com)
 *
 * Initial Release
 */

#अगर_अघोषित _ASM_RC32434_PCI_H_
#घोषणा _ASM_RC32434_PCI_H_

#घोषणा epld_mask ((अस्थिर अचिन्हित अक्षर *)0xB900000d)

#घोषणा PCI0_BASE_ADDR		0x18080000
#घोषणा PCI_LBA_COUNT		4

काष्ठा pci_map अणु
	u32 address;		/* Address. */
	u32 control;		/* Control. */
	u32 mapping;		/* mapping. */
पूर्ण;

काष्ठा pci_reg अणु
	u32 pcic;
	u32 pcis;
	u32 pcism;
	u32 pcicfga;
	u32 pcicfgd;
	अस्थिर काष्ठा pci_map pcilba[PCI_LBA_COUNT];
	u32 pcidac;
	u32 pcidas;
	u32 pcidयंत्र;
	u32 pcidad;
	u32 pcidma8c;
	u32 pcidma9c;
	u32 pcitc;
पूर्ण;

#घोषणा PCI_MSU_COUNT		2

काष्ठा pci_msu अणु
	u32 pciim[PCI_MSU_COUNT];
	u32 pciom[PCI_MSU_COUNT];
	u32 pciid;
	u32 pciiic;
	u32 pciiim;
	u32 pciiod;
	u32 pciioic;
	u32 pciioim;
पूर्ण;

/*
 * PCI Control Register
 */

#घोषणा PCI_CTL_EN		(1 << 0)
#घोषणा PCI_CTL_TNR		(1 << 1)
#घोषणा PCI_CTL_SCE		(1 << 2)
#घोषणा PCI_CTL_IEN		(1 << 3)
#घोषणा PCI_CTL_AAA		(1 << 4)
#घोषणा PCI_CTL_EAP		(1 << 5)
#घोषणा PCI_CTL_PCIM_BIT	6
#घोषणा PCI_CTL_PCIM		0x000001c0

#घोषणा PCI_CTL_PCIM_DIS	0
#घोषणा PCI_CTL_PCIM_TNR	1 /* Satellite - target not पढ़ोy */
#घोषणा PCI_CTL_PCIM_SUS	2 /* Satellite - suspended CPU. */
#घोषणा PCI_CTL_PCIM_EXT	3 /* Host - बाह्यal arbiter. */
#घोषणा PCI_CTL PCIM_PRIO	4 /* Host - fixed priority arb. */
#घोषणा PCI_CTL_PCIM_RR		5 /* Host - round robin priority. */
#घोषणा PCI_CTL_PCIM_RSVD6	6
#घोषणा PCI_CTL_PCIM_RSVD7	7

#घोषणा PCI_CTL_IGM		(1 << 9)

/*
 * PCI Status Register
 */

#घोषणा PCI_STAT_EED		(1 << 0)
#घोषणा PCI_STAT_WR		(1 << 1)
#घोषणा PCI_STAT_NMI		(1 << 2)
#घोषणा PCI_STAT_II		(1 << 3)
#घोषणा PCI_STAT_CWE		(1 << 4)
#घोषणा PCI_STAT_CRE		(1 << 5)
#घोषणा PCI_STAT_MDPE		(1 << 6)
#घोषणा PCI_STAT_STA		(1 << 7)
#घोषणा PCI_STAT_RTA		(1 << 8)
#घोषणा PCI_STAT_RMA		(1 << 9)
#घोषणा PCI_STAT_SSE		(1 << 10)
#घोषणा PCI_STAT_OSE		(1 << 11)
#घोषणा PCI_STAT_PE		(1 << 12)
#घोषणा PCI_STAT_TAE		(1 << 13)
#घोषणा PCI_STAT_RLE		(1 << 14)
#घोषणा PCI_STAT_BME		(1 << 15)
#घोषणा PCI_STAT_PRD		(1 << 16)
#घोषणा PCI_STAT_RIP		(1 << 17)

/*
 * PCI Status Mask Register
 */

#घोषणा PCI_STATM_EED		PCI_STAT_EED
#घोषणा PCI_STATM_WR		PCI_STAT_WR
#घोषणा PCI_STATM_NMI		PCI_STAT_NMI
#घोषणा PCI_STATM_II		PCI_STAT_II
#घोषणा PCI_STATM_CWE		PCI_STAT_CWE
#घोषणा PCI_STATM_CRE		PCI_STAT_CRE
#घोषणा PCI_STATM_MDPE		PCI_STAT_MDPE
#घोषणा PCI_STATM_STA		PCI_STAT_STA
#घोषणा PCI_STATM_RTA		PCI_STAT_RTA
#घोषणा PCI_STATM_RMA		PCI_STAT_RMA
#घोषणा PCI_STATM_SSE		PCI_STAT_SSE
#घोषणा PCI_STATM_OSE		PCI_STAT_OSE
#घोषणा PCI_STATM_PE		PCI_STAT_PE
#घोषणा PCI_STATM_TAE		PCI_STAT_TAE
#घोषणा PCI_STATM_RLE		PCI_STAT_RLE
#घोषणा PCI_STATM_BME		PCI_STAT_BME
#घोषणा PCI_STATM_PRD		PCI_STAT_PRD
#घोषणा PCI_STATM_RIP		PCI_STAT_RIP

/*
 * PCI Configuration Address Register
 */
#घोषणा PCI_CFGA_REG_BIT	2
#घोषणा PCI_CFGA_REG		0x000000fc
#घोषणा	 PCI_CFGA_REG_ID	(0x00 >> 2)	/* use PCFGID */
#घोषणा	 PCI_CFGA_REG_04	(0x04 >> 2)	/* use PCFG04_ */
#घोषणा	 PCI_CFGA_REG_08	(0x08 >> 2)	/* use PCFG08_ */
#घोषणा	 PCI_CFGA_REG_0C	(0x0C >> 2)	/* use PCFG0C_ */
#घोषणा	 PCI_CFGA_REG_PBA0	(0x10 >> 2)	/* use PCIPBA_ */
#घोषणा	 PCI_CFGA_REG_PBA1	(0x14 >> 2)	/* use PCIPBA_ */
#घोषणा	 PCI_CFGA_REG_PBA2	(0x18 >> 2)	/* use PCIPBA_ */
#घोषणा	 PCI_CFGA_REG_PBA3	(0x1c >> 2)	/* use PCIPBA_ */
#घोषणा	 PCI_CFGA_REG_SUBSYS	(0x2c >> 2)	/* use PCFGSS_ */
#घोषणा	 PCI_CFGA_REG_3C	(0x3C >> 2)	/* use PCFG3C_ */
#घोषणा	 PCI_CFGA_REG_PBBA0C	(0x44 >> 2)	/* use PCIPBAC_ */
#घोषणा	 PCI_CFGA_REG_PBA0M	(0x48 >> 2)
#घोषणा	 PCI_CFGA_REG_PBA1C	(0x4c >> 2)	/* use PCIPBAC_ */
#घोषणा	 PCI_CFGA_REG_PBA1M	(0x50 >> 2)
#घोषणा	 PCI_CFGA_REG_PBA2C	(0x54 >> 2)	/* use PCIPBAC_ */
#घोषणा	 PCI_CFGA_REG_PBA2M	(0x58 >> 2)
#घोषणा	 PCI_CFGA_REG_PBA3C	(0x5c >> 2)	/* use PCIPBAC_ */
#घोषणा	 PCI_CFGA_REG_PBA3M	(0x60 >> 2)
#घोषणा	 PCI_CFGA_REG_PMGT	(0x64 >> 2)
#घोषणा PCI_CFGA_FUNC_BIT	8
#घोषणा PCI_CFGA_FUNC		0x00000700
#घोषणा PCI_CFGA_DEV_BIT	11
#घोषणा PCI_CFGA_DEV		0x0000f800
#घोषणा PCI_CFGA_DEV_INTERN	0
#घोषणा PCI_CFGA_BUS_BIT	16
#घोषणा PCI CFGA_BUS		0x00ff0000
#घोषणा PCI_CFGA_BUS_TYPE0	0
#घोषणा PCI_CFGA_EN		(1 << 31)

/* PCI CFG04 commands */
#घोषणा PCI_CFG04_CMD_IO_ENA	(1 << 0)
#घोषणा PCI_CFG04_CMD_MEM_ENA	(1 << 1)
#घोषणा PCI_CFG04_CMD_BM_ENA	(1 << 2)
#घोषणा PCI_CFG04_CMD_MW_INV	(1 << 4)
#घोषणा PCI_CFG04_CMD_PAR_ENA	(1 << 6)
#घोषणा PCI_CFG04_CMD_SER_ENA	(1 << 8)
#घोषणा PCI_CFG04_CMD_FAST_ENA	(1 << 9)

/* PCI CFG04 status fields */
#घोषणा PCI_CFG04_STAT_BIT	16
#घोषणा PCI_CFG04_STAT		0xffff0000
#घोषणा PCI_CFG04_STAT_66_MHZ	(1 << 21)
#घोषणा PCI_CFG04_STAT_FBB	(1 << 23)
#घोषणा PCI_CFG04_STAT_MDPE	(1 << 24)
#घोषणा PCI_CFG04_STAT_DST	(1 << 25)
#घोषणा PCI_CFG04_STAT_STA	(1 << 27)
#घोषणा PCI_CFG04_STAT_RTA	(1 << 28)
#घोषणा PCI_CFG04_STAT_RMA	(1 << 29)
#घोषणा PCI_CFG04_STAT_SSE	(1 << 30)
#घोषणा PCI_CFG04_STAT_PE	(1 << 31)

#घोषणा PCI_PBA_MSI		(1 << 0)
#घोषणा PCI_PBA_P		(1 << 2)

/* PCI PBAC रेजिस्टरs */
#घोषणा PCI_PBAC_MSI		(1 << 0)
#घोषणा PCI_PBAC_P		(1 << 1)
#घोषणा PCI_PBAC_SIZE_BIT	2
#घोषणा PCI_PBAC_SIZE		0x0000007c
#घोषणा PCI_PBAC_SB		(1 << 7)
#घोषणा PCI_PBAC_PP		(1 << 8)
#घोषणा PCI_PBAC_MR_BIT		9
#घोषणा PCI_PBAC_MR		0x00000600
#घोषणा	 PCI_PBAC_MR_RD		0
#घोषणा	 PCI_PBAC_MR_RD_LINE	1
#घोषणा	 PCI_PBAC_MR_RD_MULT	2
#घोषणा PCI_PBAC_MRL		(1 << 11)
#घोषणा PCI_PBAC_MRM		(1 << 12)
#घोषणा PCI_PBAC_TRP		(1 << 13)

#घोषणा PCI_CFG40_TRDY_TIM	0x000000ff
#घोषणा PCI_CFG40_RET_LIM	0x0000ff00

/*
 * PCI Local Base Address [0|1|2|3] Register
 */

#घोषणा PCI_LBA_BADDR_BIT	0
#घोषणा PCI_LBA_BADDR		0xffffff00

/*
 * PCI Local Base Address Control Register
 */

#घोषणा PCI_LBAC_MSI		(1 << 0)
#घोषणा	 PCI_LBAC_MSI_MEM	0
#घोषणा	 PCI_LBAC_MSI_IO	1
#घोषणा PCI_LBAC_SIZE_BIT	2
#घोषणा PCI_LBAC_SIZE		0x0000007c
#घोषणा PCI_LBAC_SB		(1 << 7)
#घोषणा PCI_LBAC_RT		(1 << 8)
#घोषणा	 PCI_LBAC_RT_NO_PREF	0
#घोषणा	 PCI_LBAC_RT_PREF	1

/*
 * PCI Local Base Address [0|1|2|3] Mapping Register
 */
#घोषणा PCI_LBAM_MADDR_BIT	8
#घोषणा PCI_LBAM_MADDR		0xffffff00

/*
 * PCI Decoupled Access Control Register
 */
#घोषणा PCI_DAC_DEN		(1 << 0)

/*
 * PCI Decoupled Access Status Register
 */
#घोषणा PCI_DAS_D		(1 << 0)
#घोषणा PCI_DAS_B		(1 << 1)
#घोषणा PCI_DAS_E		(1 << 2)
#घोषणा PCI_DAS_OFE		(1 << 3)
#घोषणा PCI_DAS_OFF		(1 << 4)
#घोषणा PCI_DAS_IFE		(1 << 5)
#घोषणा PCI_DAS_IFF		(1 << 6)

/*
 * PCI DMA Channel 8 Configuration Register
 */
#घोषणा PCI_DMA8C_MBS_BIT	0
#घोषणा PCI_DMA8C_MBS		0x00000fff /* Maximum Burst Size. */
#घोषणा PCI_DMA8C_OUR		(1 << 12)

/*
 * PCI DMA Channel 9 Configuration Register
 */
#घोषणा PCI_DMA9C_MBS_BIT	0	/* Maximum Burst Size. */
#घोषणा PCI_DMA9C_MBS		0x00000fff

/*
 * PCI to Memory(DMA Channel 8) AND Memory to PCI DMA(DMA Channel 9)Descriptors
 */

#घोषणा PCI_DMAD_PT_BIT		22		/* in DEVCMD field (descriptor) */
#घोषणा PCI_DMAD_PT		0x00c00000	/* preferred transaction field */
/* These are क्रम पढ़ोs (DMA channel 8) */
#घोषणा PCI_DMAD_DEVCMD_MR	0		/* memory पढ़ो */
#घोषणा PCI_DMAD_DEVCMD_MRL	1		/* memory पढ़ो line */
#घोषणा PCI_DMAD_DEVCMD_MRM	2		/* memory पढ़ो multiple */
#घोषणा PCI_DMAD_DEVCMD_IOR	3		/* I/O पढ़ो */
/* These are क्रम ग_लिखोs (DMA channel 9) */
#घोषणा PCI_DMAD_DEVCMD_MW	0		/* memory ग_लिखो */
#घोषणा PCI_DMAD_DEVCMD_MWI	1		/* memory ग_लिखो invalidate */
#घोषणा PCI_DMAD_DEVCMD_IOW	3		/* I/O ग_लिखो */

/* Swap byte field applies to both DMA channel 8 and 9 */
#घोषणा PCI_DMAD_SB		(1 << 24)	/* swap byte field */


/*
 * PCI Target Control Register
 */

#घोषणा PCI_TC_RTIMER_BIT	0
#घोषणा PCI_TC_RTIMER		0x000000ff
#घोषणा PCI_TC_DTIMER_BIT	8
#घोषणा PCI_TC_DTIMER		0x0000ff00
#घोषणा PCI_TC_RDR		(1 << 18)
#घोषणा PCI_TC_DDT		(1 << 19)

/*
 * PCI messaging unit [applies to both inbound and outbound रेजिस्टरs ]
 */
#घोषणा PCI_MSU_M0		(1 << 0)
#घोषणा PCI_MSU_M1		(1 << 1)
#घोषणा PCI_MSU_DB		(1 << 2)

#घोषणा PCI_MSG_ADDR		0xB8088010
#घोषणा PCI0_ADDR		0xB8080000
#घोषणा rc32434_pci ((काष्ठा pci_reg *) PCI0_ADDR)
#घोषणा rc32434_pci_msg ((काष्ठा pci_msu *) PCI_MSG_ADDR)

#घोषणा PCIM_SHFT		0x6
#घोषणा PCIM_BIT_LEN		0x7
#घोषणा PCIM_H_EA		0x3
#घोषणा PCIM_H_IA_FIX		0x4
#घोषणा PCIM_H_IA_RR		0x5

#घोषणा PCI_ADDR_START		0x50000000

#घोषणा CPUTOPCI_MEM_WIN	0x02000000
#घोषणा CPUTOPCI_IO_WIN		0x00100000
#घोषणा PCILBA_SIZE_SHFT	2
#घोषणा PCILBA_SIZE_MASK	0x1F
#घोषणा SIZE_256MB		0x1C
#घोषणा SIZE_128MB		0x1B
#घोषणा SIZE_64MB		0x1A
#घोषणा SIZE_32MB		0x19
#घोषणा SIZE_16MB		0x18
#घोषणा SIZE_4MB		0x16
#घोषणा SIZE_2MB		0x15
#घोषणा SIZE_1MB		0x14
#घोषणा KORINA_CONFIG0_ADDR	0x80000000
#घोषणा KORINA_CONFIG1_ADDR	0x80000004
#घोषणा KORINA_CONFIG2_ADDR	0x80000008
#घोषणा KORINA_CONFIG3_ADDR	0x8000000C
#घोषणा KORINA_CONFIG4_ADDR	0x80000010
#घोषणा KORINA_CONFIG5_ADDR	0x80000014
#घोषणा KORINA_CONFIG6_ADDR	0x80000018
#घोषणा KORINA_CONFIG7_ADDR	0x8000001C
#घोषणा KORINA_CONFIG8_ADDR	0x80000020
#घोषणा KORINA_CONFIG9_ADDR	0x80000024
#घोषणा KORINA_CONFIG10_ADDR	0x80000028
#घोषणा KORINA_CONFIG11_ADDR	0x8000002C
#घोषणा KORINA_CONFIG12_ADDR	0x80000030
#घोषणा KORINA_CONFIG13_ADDR	0x80000034
#घोषणा KORINA_CONFIG14_ADDR	0x80000038
#घोषणा KORINA_CONFIG15_ADDR	0x8000003C
#घोषणा KORINA_CONFIG16_ADDR	0x80000040
#घोषणा KORINA_CONFIG17_ADDR	0x80000044
#घोषणा KORINA_CONFIG18_ADDR	0x80000048
#घोषणा KORINA_CONFIG19_ADDR	0x8000004C
#घोषणा KORINA_CONFIG20_ADDR	0x80000050
#घोषणा KORINA_CONFIG21_ADDR	0x80000054
#घोषणा KORINA_CONFIG22_ADDR	0x80000058
#घोषणा KORINA_CONFIG23_ADDR	0x8000005C
#घोषणा KORINA_CONFIG24_ADDR	0x80000060
#घोषणा KORINA_CONFIG25_ADDR	0x80000064
#घोषणा KORINA_CMD		(PCI_CFG04_CMD_IO_ENA | \
				 PCI_CFG04_CMD_MEM_ENA | \
				 PCI_CFG04_CMD_BM_ENA | \
				 PCI_CFG04_CMD_MW_INV | \
				 PCI_CFG04_CMD_PAR_ENA | \
				 PCI_CFG04_CMD_SER_ENA)

#घोषणा KORINA_STAT		(PCI_CFG04_STAT_MDPE | \
				 PCI_CFG04_STAT_STA | \
				 PCI_CFG04_STAT_RTA | \
				 PCI_CFG04_STAT_RMA | \
				 PCI_CFG04_STAT_SSE | \
				 PCI_CFG04_STAT_PE)

#घोषणा KORINA_CNFG1		((KORINA_STAT<<16)|KORINA_CMD)

#घोषणा KORINA_REVID		0
#घोषणा KORINA_CLASS_CODE	0
#घोषणा KORINA_CNFG2		((KORINA_CLASS_CODE<<8) | \
				  KORINA_REVID)

#घोषणा KORINA_CACHE_LINE_SIZE	4
#घोषणा KORINA_MASTER_LAT	0x3c
#घोषणा KORINA_HEADER_TYPE	0
#घोषणा KORINA_BIST		0

#घोषणा KORINA_CNFG3 ((KORINA_BIST << 24) | \
		      (KORINA_HEADER_TYPE<<16) | \
		      (KORINA_MASTER_LAT<<8) | \
		      KORINA_CACHE_LINE_SIZE)

#घोषणा KORINA_BAR0	0x00000008	/* 128 MB Memory */
#घोषणा KORINA_BAR1	0x18800001	/* 1 MB IO */
#घोषणा KORINA_BAR2	0x18000001	/* 2 MB IO winकरोw क्रम Korina
					   पूर्णांकernal Registers */
#घोषणा KORINA_BAR3	0x48000008	/* Spare 128 MB Memory */

#घोषणा KORINA_CNFG4	KORINA_BAR0
#घोषणा KORINA_CNFG5	KORINA_BAR1
#घोषणा KORINA_CNFG6	KORINA_BAR2
#घोषणा KORINA_CNFG7	KORINA_BAR3

#घोषणा KORINA_SUBSYS_VENDOR_ID 0x011d
#घोषणा KORINA_SUBSYSTEM_ID	0x0214
#घोषणा KORINA_CNFG8		0
#घोषणा KORINA_CNFG9		0
#घोषणा KORINA_CNFG10		0
#घोषणा KORINA_CNFG11	((KORINA_SUBSYS_VENDOR_ID<<16) | \
			  KORINA_SUBSYSTEM_ID)
#घोषणा KORINA_INT_LINE		1
#घोषणा KORINA_INT_PIN		1
#घोषणा KORINA_MIN_GNT		8
#घोषणा KORINA_MAX_LAT		0x38
#घोषणा KORINA_CNFG12		0
#घोषणा KORINA_CNFG13		0
#घोषणा KORINA_CNFG14		0
#घोषणा KORINA_CNFG15	((KORINA_MAX_LAT<<24) | \
			 (KORINA_MIN_GNT<<16) | \
			 (KORINA_INT_PIN<<8)  | \
			  KORINA_INT_LINE)
#घोषणा KORINA_RETRY_LIMIT	0x80
#घोषणा KORINA_TRDY_LIMIT	0x80
#घोषणा KORINA_CNFG16 ((KORINA_RETRY_LIMIT<<8) | \
			KORINA_TRDY_LIMIT)
#घोषणा PCI_PBAxC_R		0x0
#घोषणा PCI_PBAxC_RL		0x1
#घोषणा PCI_PBAxC_RM		0x2
#घोषणा SIZE_SHFT		2

#अगर defined(__MIPSEB__)
#घोषणा KORINA_PBA0C	(PCI_PBAC_MRL | PCI_PBAC_SB | \
			  ((PCI_PBAxC_RM & 0x3) << PCI_PBAC_MR_BIT) | \
			  PCI_PBAC_PP | \
			  (SIZE_128MB<<SIZE_SHFT) | \
			   PCI_PBAC_P)
#अन्यथा
#घोषणा KORINA_PBA0C	(PCI_PBAC_MRL | \
			  ((PCI_PBAxC_RM & 0x3) << PCI_PBAC_MR_BIT) | \
			  PCI_PBAC_PP | \
			  (SIZE_128MB<<SIZE_SHFT) | \
			   PCI_PBAC_P)
#पूर्ण_अगर
#घोषणा KORINA_CNFG17	KORINA_PBA0C
#घोषणा KORINA_PBA0M	0x0
#घोषणा KORINA_CNFG18	KORINA_PBA0M

#अगर defined(__MIPSEB__)
#घोषणा KORINA_PBA1C	((SIZE_1MB<<SIZE_SHFT) | PCI_PBAC_SB | \
			  PCI_PBAC_MSI)
#अन्यथा
#घोषणा KORINA_PBA1C	((SIZE_1MB<<SIZE_SHFT) | \
			  PCI_PBAC_MSI)
#पूर्ण_अगर
#घोषणा KORINA_CNFG19	KORINA_PBA1C
#घोषणा KORINA_PBA1M	0x0
#घोषणा KORINA_CNFG20	KORINA_PBA1M

#अगर defined(__MIPSEB__)
#घोषणा KORINA_PBA2C	((SIZE_2MB<<SIZE_SHFT) | PCI_PBAC_SB | \
			  PCI_PBAC_MSI)
#अन्यथा
#घोषणा KORINA_PBA2C	((SIZE_2MB<<SIZE_SHFT) | \
			  PCI_PBAC_MSI)
#पूर्ण_अगर
#घोषणा KORINA_CNFG21	KORINA_PBA2C
#घोषणा KORINA_PBA2M	0x18000000
#घोषणा KORINA_CNFG22	KORINA_PBA2M
#घोषणा KORINA_PBA3C	0
#घोषणा KORINA_CNFG23	KORINA_PBA3C
#घोषणा KORINA_PBA3M	0
#घोषणा KORINA_CNFG24	KORINA_PBA3M

#घोषणा PCITC_DTIMER_VAL	8
#घोषणा PCITC_RTIMER_VAL	0x10

#पूर्ण_अगर	/* __ASM_RC32434_PCI_H */
