<शैली गुरु>
#अगर_अघोषित _ASM_POWERPC_FSP_DCR_H_
#घोषणा _ASM_POWERPC_FSP_DCR_H_
#अगर_घोषित __KERNEL__
#समावेश <यंत्र/dcr.h>

#घोषणा DCRN_CMU_ADDR		0x00C	/* Chip management unic addr */
#घोषणा DCRN_CMU_DATA		0x00D	/* Chip management unic data */

/* PLB4 Arbiter */
#घोषणा DCRN_PLB4_PCBI		0x010	/* PLB Crossbar ID/Rev Register */
#घोषणा DCRN_PLB4_P0ACR		0x011	/* PLB0 Arbiter Control Register */
#घोषणा DCRN_PLB4_P0ESRL	0x012	/* PLB0 Error Status Register Low */
#घोषणा DCRN_PLB4_P0ESRH	0x013	/* PLB0 Error Status Register High */
#घोषणा DCRN_PLB4_P0EARL	0x014	/* PLB0 Error Address Register Low */
#घोषणा DCRN_PLB4_P0EARH	0x015	/* PLB0 Error Address Register High */
#घोषणा DCRN_PLB4_P0ESRLS	0x016	/* PLB0 Error Status Register Low Set*/
#घोषणा DCRN_PLB4_P0ESRHS	0x017	/* PLB0 Error Status Register High */
#घोषणा DCRN_PLB4_PCBC		0x018	/* PLB Crossbar Control Register */
#घोषणा DCRN_PLB4_P1ACR		0x019	/* PLB1 Arbiter Control Register */
#घोषणा DCRN_PLB4_P1ESRL	0x01A	/* PLB1 Error Status Register Low */
#घोषणा DCRN_PLB4_P1ESRH	0x01B	/* PLB1 Error Status Register High */
#घोषणा DCRN_PLB4_P1EARL	0x01C	/* PLB1 Error Address Register Low */
#घोषणा DCRN_PLB4_P1EARH	0x01D	/* PLB1 Error Address Register High */
#घोषणा DCRN_PLB4_P1ESRLS	0x01E	/* PLB1 Error Status Register Low Set*/
#घोषणा DCRN_PLB4_P1ESRHS	0x01F	/*PLB1 Error Status Register High Set*/

/* PLB4/OPB bridge 0, 1, 2, 3 */
#घोषणा DCRN_PLB4OPB0_BASE	0x020
#घोषणा DCRN_PLB4OPB1_BASE	0x030
#घोषणा DCRN_PLB4OPB2_BASE	0x040
#घोषणा DCRN_PLB4OPB3_BASE	0x050

#घोषणा PLB4OPB_GESR0		0x0	/* Error status 0: Master Dev 0-3 */
#घोषणा PLB4OPB_GEAR		0x2	/* Error Address Register */
#घोषणा PLB4OPB_GEARU		0x3	/* Error Upper Address Register */
#घोषणा PLB4OPB_GESR1		0x4	/* Error Status 1: Master Dev 4-7 */
#घोषणा PLB4OPB_GESR2		0xC	/* Error Status 2: Master Dev 8-11 */

/* PLB4-to-AHB Bridge */
#घोषणा DCRN_PLB4AHB_BASE	0x400
#घोषणा DCRN_PLB4AHB_SEUAR	(DCRN_PLB4AHB_BASE + 1)
#घोषणा DCRN_PLB4AHB_SELAR	(DCRN_PLB4AHB_BASE + 2)
#घोषणा DCRN_PLB4AHB_ESR	(DCRN_PLB4AHB_BASE + 3)
#घोषणा DCRN_AHBPLB4_ESR	(DCRN_PLB4AHB_BASE + 8)
#घोषणा DCRN_AHBPLB4_EAR	(DCRN_PLB4AHB_BASE + 9)

/* PLB6 Controller */
#घोषणा DCRN_PLB6_BASE		0x11111300
#घोषणा DCRN_PLB6_CR0		(DCRN_PLB6_BASE)
#घोषणा DCRN_PLB6_ERR		(DCRN_PLB6_BASE + 0x0B)
#घोषणा DCRN_PLB6_HD		(DCRN_PLB6_BASE + 0x0E)
#घोषणा DCRN_PLB6_SHD		(DCRN_PLB6_BASE + 0x10)

/* PLB4-to-PLB6 Bridge */
#घोषणा DCRN_PLB4PLB6_BASE	0x11111320
#घोषणा DCRN_PLB4PLB6_ESR	(DCRN_PLB4PLB6_BASE + 1)
#घोषणा DCRN_PLB4PLB6_EARH	(DCRN_PLB4PLB6_BASE + 3)
#घोषणा DCRN_PLB4PLB6_EARL	(DCRN_PLB4PLB6_BASE + 4)

/* PLB6-to-PLB4 Bridge */
#घोषणा DCRN_PLB6PLB4_BASE	0x11111350
#घोषणा DCRN_PLB6PLB4_ESR	(DCRN_PLB6PLB4_BASE + 1)
#घोषणा DCRN_PLB6PLB4_EARH	(DCRN_PLB6PLB4_BASE + 3)
#घोषणा DCRN_PLB6PLB4_EARL	(DCRN_PLB6PLB4_BASE + 4)

/* PLB6-to-MCIF Bridge */
#घोषणा DCRN_PLB6MCIF_BASE	0x11111380
#घोषणा DCRN_PLB6MCIF_BESR0	(DCRN_PLB6MCIF_BASE + 0)
#घोषणा DCRN_PLB6MCIF_BESR1	(DCRN_PLB6MCIF_BASE + 1)
#घोषणा DCRN_PLB6MCIF_BEARL	(DCRN_PLB6MCIF_BASE + 2)
#घोषणा DCRN_PLB6MCIF_BEARH	(DCRN_PLB6MCIF_BASE + 3)

/* Configuration Logic Registers */
#घोषणा DCRN_CONF_BASE		0x11111400
#घोषणा DCRN_CONF_FIR_RWC	(DCRN_CONF_BASE + 0x3A)
#घोषणा DCRN_CONF_EIR_RS	(DCRN_CONF_BASE + 0x3E)
#घोषणा DCRN_CONF_RPERR0	(DCRN_CONF_BASE + 0x4D)
#घोषणा DCRN_CONF_RPERR1	(DCRN_CONF_BASE + 0x4E)

#घोषणा DCRN_L2CDCRAI		0x11111100
#घोषणा DCRN_L2CDCRDI		0x11111104
/* L2 indirect addresses */
#घोषणा L2MCK		0x120
#घोषणा L2MCKEN		0x130
#घोषणा L2INT		0x150
#घोषणा L2INTEN		0x160
#घोषणा L2LOG0		0x180
#घोषणा L2LOG1		0x184
#घोषणा L2LOG2		0x188
#घोषणा L2LOG3		0x18C
#घोषणा L2LOG4		0x190
#घोषणा L2LOG5		0x194
#घोषणा L2PLBSTAT0	0x300
#घोषणा L2PLBSTAT1	0x304
#घोषणा L2PLBMCKEN0	0x330
#घोषणा L2PLBMCKEN1	0x334
#घोषणा L2PLBINTEN0	0x360
#घोषणा L2PLBINTEN1	0x364
#घोषणा L2ARRSTAT0	0x500
#घोषणा L2ARRSTAT1	0x504
#घोषणा L2ARRSTAT2	0x508
#घोषणा L2ARRMCKEN0	0x530
#घोषणा L2ARRMCKEN1	0x534
#घोषणा L2ARRMCKEN2	0x538
#घोषणा L2ARRINTEN0	0x560
#घोषणा L2ARRINTEN1	0x564
#घोषणा L2ARRINTEN2	0x568
#घोषणा L2CPUSTAT	0x700
#घोषणा L2CPUMCKEN	0x730
#घोषणा L2CPUINTEN	0x760
#घोषणा L2RACSTAT0	0x900
#घोषणा L2RACMCKEN0	0x930
#घोषणा L2RACINTEN0	0x960
#घोषणा L2WACSTAT0	0xD00
#घोषणा L2WACSTAT1	0xD04
#घोषणा L2WACSTAT2	0xD08
#घोषणा L2WACMCKEN0	0xD30
#घोषणा L2WACMCKEN1	0xD34
#घोषणा L2WACMCKEN2	0xD38
#घोषणा L2WACINTEN0	0xD60
#घोषणा L2WACINTEN1	0xD64
#घोषणा L2WACINTEN2	0xD68
#घोषणा L2WDFSTAT	0xF00
#घोषणा L2WDFMCKEN	0xF30
#घोषणा L2WDFINTEN	0xF60

/* DDR3/4 Memory Controller */
#घोषणा DCRN_DDR34_BASE			0x11120000
#घोषणा DCRN_DDR34_MCSTAT		0x10
#घोषणा DCRN_DDR34_MCOPT1		0x20
#घोषणा DCRN_DDR34_MCOPT2		0x21
#घोषणा DCRN_DDR34_PHYSTAT		0x32
#घोषणा DCRN_DDR34_CFGR0		0x40
#घोषणा DCRN_DDR34_CFGR1		0x41
#घोषणा DCRN_DDR34_CFGR2		0x42
#घोषणा DCRN_DDR34_CFGR3		0x43
#घोषणा DCRN_DDR34_SCRUB_CNTL		0xAA
#घोषणा DCRN_DDR34_SCRUB_INT		0xAB
#घोषणा DCRN_DDR34_SCRUB_START_ADDR	0xB0
#घोषणा DCRN_DDR34_SCRUB_END_ADDR	0xD0
#घोषणा DCRN_DDR34_ECCERR_ADDR_PORT0	0xE0
#घोषणा DCRN_DDR34_ECCERR_ADDR_PORT1	0xE1
#घोषणा DCRN_DDR34_ECCERR_ADDR_PORT2	0xE2
#घोषणा DCRN_DDR34_ECCERR_ADDR_PORT3	0xE3
#घोषणा DCRN_DDR34_ECCERR_COUNT_PORT0	0xE4
#घोषणा DCRN_DDR34_ECCERR_COUNT_PORT1	0xE5
#घोषणा DCRN_DDR34_ECCERR_COUNT_PORT2	0xE6
#घोषणा DCRN_DDR34_ECCERR_COUNT_PORT3	0xE7
#घोषणा DCRN_DDR34_ECCERR_PORT0		0xF0
#घोषणा DCRN_DDR34_ECCERR_PORT1		0xF2
#घोषणा DCRN_DDR34_ECCERR_PORT2		0xF4
#घोषणा DCRN_DDR34_ECCERR_PORT3		0xF6
#घोषणा DCRN_DDR34_ECC_CHECK_PORT0	0xF8
#घोषणा DCRN_DDR34_ECC_CHECK_PORT1	0xF9
#घोषणा DCRN_DDR34_ECC_CHECK_PORT2	0xF9
#घोषणा DCRN_DDR34_ECC_CHECK_PORT3	0xFB

#घोषणा DDR34_SCRUB_CNTL_STOP		0x00000000
#घोषणा DDR34_SCRUB_CNTL_SCRUB		0x80000000
#घोषणा DDR34_SCRUB_CNTL_UE_STOP	0x20000000
#घोषणा DDR34_SCRUB_CNTL_CE_STOP	0x10000000
#घोषणा DDR34_SCRUB_CNTL_RANK_EN	0x00008000

/* PLB-Attached DDR3/4 Core Wrapper */
#घोषणा DCRN_CW_BASE			0x11111800
#घोषणा DCRN_CW_MCER0			0x00
#घोषणा DCRN_CW_MCER1			0x01
#घोषणा DCRN_CW_MCER_AND0		0x02
#घोषणा DCRN_CW_MCER_AND1		0x03
#घोषणा DCRN_CW_MCER_OR0		0x04
#घोषणा DCRN_CW_MCER_OR1		0x05
#घोषणा DCRN_CW_MCER_MASK0		0x06
#घोषणा DCRN_CW_MCER_MASK1		0x07
#घोषणा DCRN_CW_MCER_MASK_AND0		0x08
#घोषणा DCRN_CW_MCER_MASK_AND1		0x09
#घोषणा DCRN_CW_MCER_MASK_OR0		0x0A
#घोषणा DCRN_CW_MCER_MASK_OR1		0x0B
#घोषणा DCRN_CW_MCER_ACTION0		0x0C
#घोषणा DCRN_CW_MCER_ACTION1		0x0D
#घोषणा DCRN_CW_MCER_WOF0		0x0E
#घोषणा DCRN_CW_MCER_WOF1		0x0F
#घोषणा DCRN_CW_LFIR			0x10
#घोषणा DCRN_CW_LFIR_AND		0x11
#घोषणा DCRN_CW_LFIR_OR			0x12
#घोषणा DCRN_CW_LFIR_MASK		0x13
#घोषणा DCRN_CW_LFIR_MASK_AND		0x14
#घोषणा DCRN_CW_LFIR_MASK_OR		0x15

#घोषणा CW_MCER0_MEM_CE			0x00020000
/* CMU addresses */
#घोषणा CMUN_CRCS		0x00 /* Chip Reset Control/Status */
#घोषणा CMUN_CONFFIR0		0x20 /* Config Reg Parity FIR 0 */
#घोषणा CMUN_CONFFIR1		0x21 /* Config Reg Parity FIR 1 */
#घोषणा CMUN_CONFFIR2		0x22 /* Config Reg Parity FIR 2 */
#घोषणा CMUN_CONFFIR3		0x23 /* Config Reg Parity FIR 3 */
#घोषणा CMUN_URCR3_RS		0x24 /* Unit Reset Control Reg 3 Set */
#घोषणा CMUN_URCR3_C		0x25 /* Unit Reset Control Reg 3 Clear */
#घोषणा CMUN_URCR3_P		0x26 /* Unit Reset Control Reg 3 Pulse */
#घोषणा CMUN_PW0		0x2C /* Pulse Width Register */
#घोषणा CMUN_URCR0_P		0x2D /* Unit Reset Control Reg 0 Pulse */
#घोषणा CMUN_URCR1_P		0x2E /* Unit Reset Control Reg 1 Pulse */
#घोषणा CMUN_URCR2_P		0x2F /* Unit Reset Control Reg 2 Pulse */
#घोषणा CMUN_CLS_RW		0x30 /* Code Load Status (Read/Write) */
#घोषणा CMUN_CLS_S		0x31 /* Code Load Status (Set) */
#घोषणा CMUN_CLS_C		0x32 /* Code Load Status (Clear */
#घोषणा CMUN_URCR2_RS		0x33 /* Unit Reset Control Reg 2 Set */
#घोषणा CMUN_URCR2_C		0x34 /* Unit Reset Control Reg 2 Clear */
#घोषणा CMUN_CLKEN0		0x35 /* Clock Enable 0 */
#घोषणा CMUN_CLKEN1		0x36 /* Clock Enable 1 */
#घोषणा CMUN_PCD0		0x37 /* PSI घड़ी भागider 0 */
#घोषणा CMUN_PCD1		0x38 /* PSI घड़ी भागider 1 */
#घोषणा CMUN_TMR0		0x39 /* Reset Timer */
#घोषणा CMUN_TVS0		0x3A /* TV Sense Reg 0 */
#घोषणा CMUN_TVS1		0x3B /* TV Sense Reg 1 */
#घोषणा CMUN_MCCR		0x3C /* DRAM Configuration Reg */
#घोषणा CMUN_FIR0		0x3D /* Fault Isolation Reg 0 */
#घोषणा CMUN_FMR0		0x3E /* FIR Mask Reg 0 */
#घोषणा CMUN_ETDRB		0x3F /* ETDR Backकरोor */

/* CRCS bit fields */
#घोषणा CRCS_STAT_MASK		0xF0000000
#घोषणा CRCS_STAT_POR		0x10000000
#घोषणा CRCS_STAT_PHR		0x20000000
#घोषणा CRCS_STAT_PCIE		0x30000000
#घोषणा CRCS_STAT_CRCS_SYS	0x40000000
#घोषणा CRCS_STAT_DBCR_SYS	0x50000000
#घोषणा CRCS_STAT_HOST_SYS	0x60000000
#घोषणा CRCS_STAT_CHIP_RST_B	0x70000000
#घोषणा CRCS_STAT_CRCS_CHIP	0x80000000
#घोषणा CRCS_STAT_DBCR_CHIP	0x90000000
#घोषणा CRCS_STAT_HOST_CHIP	0xA0000000
#घोषणा CRCS_STAT_PSI_CHIP	0xB0000000
#घोषणा CRCS_STAT_CRCS_CORE	0xC0000000
#घोषणा CRCS_STAT_DBCR_CORE	0xD0000000
#घोषणा CRCS_STAT_HOST_CORE	0xE0000000
#घोषणा CRCS_STAT_PCIE_HOT	0xF0000000
#घोषणा CRCS_STAT_SELF_CORE	0x40000000
#घोषणा CRCS_STAT_SELF_CHIP	0x50000000
#घोषणा CRCS_WATCHE		0x08000000
#घोषणा CRCS_CORE		0x04000000 /* Reset PPC440 core */
#घोषणा CRCS_CHIP		0x02000000 /* Chip Reset */
#घोषणा CRCS_SYS		0x01000000 /* System Reset */
#घोषणा CRCS_WRCR		0x00800000 /* Watchकरोg reset on core reset */
#घोषणा CRCS_EXTCR		0x00080000 /* CHIP_RST_B triggers chip reset */
#घोषणा CRCS_PLOCK		0x00000002 /* PLL Locked */

#घोषणा mtcmu(reg, data)		\
करो अणु					\
	mtdcr(DCRN_CMU_ADDR, reg);	\
	mtdcr(DCRN_CMU_DATA, data);	\
पूर्ण जबतक (0)

#घोषणा mfcmu(reg)\
	(अणुu32 data;			\
	mtdcr(DCRN_CMU_ADDR, reg);	\
	data = mfdcr(DCRN_CMU_DATA);	\
	data; पूर्ण)

#घोषणा mtl2(reg, data)			\
करो अणु					\
	mtdcr(DCRN_L2CDCRAI, reg);	\
	mtdcr(DCRN_L2CDCRDI, data);	\
पूर्ण जबतक (0)

#घोषणा mfl2(reg)			\
	(अणुu32 data;			\
	mtdcr(DCRN_L2CDCRAI, reg);	\
	data = mfdcr(DCRN_L2CDCRDI);	\
	data; पूर्ण)

#पूर्ण_अगर /* __KERNEL__ */
#पूर्ण_अगर /* _ASM_POWERPC_FSP2_DCR_H_ */
