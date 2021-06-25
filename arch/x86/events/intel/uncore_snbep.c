<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* SandyBridge-EP/IvyTown uncore support */
#समावेश "uncore.h"

/* SNB-EP pci bus to socket mapping */
#घोषणा SNBEP_CPUNODEID			0x40
#घोषणा SNBEP_GIDNIDMAP			0x54

/* SNB-EP Box level control */
#घोषणा SNBEP_PMON_BOX_CTL_RST_CTRL	(1 << 0)
#घोषणा SNBEP_PMON_BOX_CTL_RST_CTRS	(1 << 1)
#घोषणा SNBEP_PMON_BOX_CTL_FRZ		(1 << 8)
#घोषणा SNBEP_PMON_BOX_CTL_FRZ_EN	(1 << 16)
#घोषणा SNBEP_PMON_BOX_CTL_INT		(SNBEP_PMON_BOX_CTL_RST_CTRL | \
					 SNBEP_PMON_BOX_CTL_RST_CTRS | \
					 SNBEP_PMON_BOX_CTL_FRZ_EN)
/* SNB-EP event control */
#घोषणा SNBEP_PMON_CTL_EV_SEL_MASK	0x000000ff
#घोषणा SNBEP_PMON_CTL_UMASK_MASK	0x0000ff00
#घोषणा SNBEP_PMON_CTL_RST		(1 << 17)
#घोषणा SNBEP_PMON_CTL_EDGE_DET		(1 << 18)
#घोषणा SNBEP_PMON_CTL_EV_SEL_EXT	(1 << 21)
#घोषणा SNBEP_PMON_CTL_EN		(1 << 22)
#घोषणा SNBEP_PMON_CTL_INVERT		(1 << 23)
#घोषणा SNBEP_PMON_CTL_TRESH_MASK	0xff000000
#घोषणा SNBEP_PMON_RAW_EVENT_MASK	(SNBEP_PMON_CTL_EV_SEL_MASK | \
					 SNBEP_PMON_CTL_UMASK_MASK | \
					 SNBEP_PMON_CTL_EDGE_DET | \
					 SNBEP_PMON_CTL_INVERT | \
					 SNBEP_PMON_CTL_TRESH_MASK)

/* SNB-EP Ubox event control */
#घोषणा SNBEP_U_MSR_PMON_CTL_TRESH_MASK		0x1f000000
#घोषणा SNBEP_U_MSR_PMON_RAW_EVENT_MASK		\
				(SNBEP_PMON_CTL_EV_SEL_MASK | \
				 SNBEP_PMON_CTL_UMASK_MASK | \
				 SNBEP_PMON_CTL_EDGE_DET | \
				 SNBEP_PMON_CTL_INVERT | \
				 SNBEP_U_MSR_PMON_CTL_TRESH_MASK)

#घोषणा SNBEP_CBO_PMON_CTL_TID_EN		(1 << 19)
#घोषणा SNBEP_CBO_MSR_PMON_RAW_EVENT_MASK	(SNBEP_PMON_RAW_EVENT_MASK | \
						 SNBEP_CBO_PMON_CTL_TID_EN)

/* SNB-EP PCU event control */
#घोषणा SNBEP_PCU_MSR_PMON_CTL_OCC_SEL_MASK	0x0000c000
#घोषणा SNBEP_PCU_MSR_PMON_CTL_TRESH_MASK	0x1f000000
#घोषणा SNBEP_PCU_MSR_PMON_CTL_OCC_INVERT	(1 << 30)
#घोषणा SNBEP_PCU_MSR_PMON_CTL_OCC_EDGE_DET	(1 << 31)
#घोषणा SNBEP_PCU_MSR_PMON_RAW_EVENT_MASK	\
				(SNBEP_PMON_CTL_EV_SEL_MASK | \
				 SNBEP_PCU_MSR_PMON_CTL_OCC_SEL_MASK | \
				 SNBEP_PMON_CTL_EDGE_DET | \
				 SNBEP_PMON_CTL_INVERT | \
				 SNBEP_PCU_MSR_PMON_CTL_TRESH_MASK | \
				 SNBEP_PCU_MSR_PMON_CTL_OCC_INVERT | \
				 SNBEP_PCU_MSR_PMON_CTL_OCC_EDGE_DET)

#घोषणा SNBEP_QPI_PCI_PMON_RAW_EVENT_MASK	\
				(SNBEP_PMON_RAW_EVENT_MASK | \
				 SNBEP_PMON_CTL_EV_SEL_EXT)

/* SNB-EP pci control रेजिस्टर */
#घोषणा SNBEP_PCI_PMON_BOX_CTL			0xf4
#घोषणा SNBEP_PCI_PMON_CTL0			0xd8
/* SNB-EP pci counter रेजिस्टर */
#घोषणा SNBEP_PCI_PMON_CTR0			0xa0

/* SNB-EP home agent रेजिस्टर */
#घोषणा SNBEP_HA_PCI_PMON_BOX_ADDRMATCH0	0x40
#घोषणा SNBEP_HA_PCI_PMON_BOX_ADDRMATCH1	0x44
#घोषणा SNBEP_HA_PCI_PMON_BOX_OPCODEMATCH	0x48
/* SNB-EP memory controller रेजिस्टर */
#घोषणा SNBEP_MC_CHy_PCI_PMON_FIXED_CTL		0xf0
#घोषणा SNBEP_MC_CHy_PCI_PMON_FIXED_CTR		0xd0
/* SNB-EP QPI रेजिस्टर */
#घोषणा SNBEP_Q_Py_PCI_PMON_PKT_MATCH0		0x228
#घोषणा SNBEP_Q_Py_PCI_PMON_PKT_MATCH1		0x22c
#घोषणा SNBEP_Q_Py_PCI_PMON_PKT_MASK0		0x238
#घोषणा SNBEP_Q_Py_PCI_PMON_PKT_MASK1		0x23c

/* SNB-EP Ubox रेजिस्टर */
#घोषणा SNBEP_U_MSR_PMON_CTR0			0xc16
#घोषणा SNBEP_U_MSR_PMON_CTL0			0xc10

#घोषणा SNBEP_U_MSR_PMON_UCLK_FIXED_CTL		0xc08
#घोषणा SNBEP_U_MSR_PMON_UCLK_FIXED_CTR		0xc09

/* SNB-EP Cbo रेजिस्टर */
#घोषणा SNBEP_C0_MSR_PMON_CTR0			0xd16
#घोषणा SNBEP_C0_MSR_PMON_CTL0			0xd10
#घोषणा SNBEP_C0_MSR_PMON_BOX_CTL		0xd04
#घोषणा SNBEP_C0_MSR_PMON_BOX_FILTER		0xd14
#घोषणा SNBEP_CBO_MSR_OFFSET			0x20

#घोषणा SNBEP_CB0_MSR_PMON_BOX_FILTER_TID	0x1f
#घोषणा SNBEP_CB0_MSR_PMON_BOX_FILTER_NID	0x3fc00
#घोषणा SNBEP_CB0_MSR_PMON_BOX_FILTER_STATE	0x7c0000
#घोषणा SNBEP_CB0_MSR_PMON_BOX_FILTER_OPC	0xff800000

#घोषणा SNBEP_CBO_EVENT_EXTRA_REG(e, m, i) अणु	\
	.event = (e),				\
	.msr = SNBEP_C0_MSR_PMON_BOX_FILTER,	\
	.config_mask = (m),			\
	.idx = (i)				\
पूर्ण

/* SNB-EP PCU रेजिस्टर */
#घोषणा SNBEP_PCU_MSR_PMON_CTR0			0xc36
#घोषणा SNBEP_PCU_MSR_PMON_CTL0			0xc30
#घोषणा SNBEP_PCU_MSR_PMON_BOX_CTL		0xc24
#घोषणा SNBEP_PCU_MSR_PMON_BOX_FILTER		0xc34
#घोषणा SNBEP_PCU_MSR_PMON_BOX_FILTER_MASK	0xffffffff
#घोषणा SNBEP_PCU_MSR_CORE_C3_CTR		0x3fc
#घोषणा SNBEP_PCU_MSR_CORE_C6_CTR		0x3fd

/* IVBEP event control */
#घोषणा IVBEP_PMON_BOX_CTL_INT		(SNBEP_PMON_BOX_CTL_RST_CTRL | \
					 SNBEP_PMON_BOX_CTL_RST_CTRS)
#घोषणा IVBEP_PMON_RAW_EVENT_MASK		(SNBEP_PMON_CTL_EV_SEL_MASK | \
					 SNBEP_PMON_CTL_UMASK_MASK | \
					 SNBEP_PMON_CTL_EDGE_DET | \
					 SNBEP_PMON_CTL_TRESH_MASK)
/* IVBEP Ubox */
#घोषणा IVBEP_U_MSR_PMON_GLOBAL_CTL		0xc00
#घोषणा IVBEP_U_PMON_GLOBAL_FRZ_ALL		(1 << 31)
#घोषणा IVBEP_U_PMON_GLOBAL_UNFRZ_ALL		(1 << 29)

#घोषणा IVBEP_U_MSR_PMON_RAW_EVENT_MASK	\
				(SNBEP_PMON_CTL_EV_SEL_MASK | \
				 SNBEP_PMON_CTL_UMASK_MASK | \
				 SNBEP_PMON_CTL_EDGE_DET | \
				 SNBEP_U_MSR_PMON_CTL_TRESH_MASK)
/* IVBEP Cbo */
#घोषणा IVBEP_CBO_MSR_PMON_RAW_EVENT_MASK		(IVBEP_PMON_RAW_EVENT_MASK | \
						 SNBEP_CBO_PMON_CTL_TID_EN)

#घोषणा IVBEP_CB0_MSR_PMON_BOX_FILTER_TID		(0x1fULL << 0)
#घोषणा IVBEP_CB0_MSR_PMON_BOX_FILTER_LINK	(0xfULL << 5)
#घोषणा IVBEP_CB0_MSR_PMON_BOX_FILTER_STATE	(0x3fULL << 17)
#घोषणा IVBEP_CB0_MSR_PMON_BOX_FILTER_NID		(0xffffULL << 32)
#घोषणा IVBEP_CB0_MSR_PMON_BOX_FILTER_OPC		(0x1ffULL << 52)
#घोषणा IVBEP_CB0_MSR_PMON_BOX_FILTER_C6		(0x1ULL << 61)
#घोषणा IVBEP_CB0_MSR_PMON_BOX_FILTER_NC		(0x1ULL << 62)
#घोषणा IVBEP_CB0_MSR_PMON_BOX_FILTER_ISOC	(0x1ULL << 63)

/* IVBEP home agent */
#घोषणा IVBEP_HA_PCI_PMON_CTL_Q_OCC_RST		(1 << 16)
#घोषणा IVBEP_HA_PCI_PMON_RAW_EVENT_MASK		\
				(IVBEP_PMON_RAW_EVENT_MASK | \
				 IVBEP_HA_PCI_PMON_CTL_Q_OCC_RST)
/* IVBEP PCU */
#घोषणा IVBEP_PCU_MSR_PMON_RAW_EVENT_MASK	\
				(SNBEP_PMON_CTL_EV_SEL_MASK | \
				 SNBEP_PCU_MSR_PMON_CTL_OCC_SEL_MASK | \
				 SNBEP_PMON_CTL_EDGE_DET | \
				 SNBEP_PCU_MSR_PMON_CTL_TRESH_MASK | \
				 SNBEP_PCU_MSR_PMON_CTL_OCC_INVERT | \
				 SNBEP_PCU_MSR_PMON_CTL_OCC_EDGE_DET)
/* IVBEP QPI */
#घोषणा IVBEP_QPI_PCI_PMON_RAW_EVENT_MASK	\
				(IVBEP_PMON_RAW_EVENT_MASK | \
				 SNBEP_PMON_CTL_EV_SEL_EXT)

#घोषणा __BITS_VALUE(x, i, n)  ((typeof(x))(((x) >> ((i) * (n))) & \
				((1ULL << (n)) - 1)))

/* Haswell-EP Ubox */
#घोषणा HSWEP_U_MSR_PMON_CTR0			0x709
#घोषणा HSWEP_U_MSR_PMON_CTL0			0x705
#घोषणा HSWEP_U_MSR_PMON_FILTER			0x707

#घोषणा HSWEP_U_MSR_PMON_UCLK_FIXED_CTL		0x703
#घोषणा HSWEP_U_MSR_PMON_UCLK_FIXED_CTR		0x704

#घोषणा HSWEP_U_MSR_PMON_BOX_FILTER_TID		(0x1 << 0)
#घोषणा HSWEP_U_MSR_PMON_BOX_FILTER_CID		(0x1fULL << 1)
#घोषणा HSWEP_U_MSR_PMON_BOX_FILTER_MASK \
					(HSWEP_U_MSR_PMON_BOX_FILTER_TID | \
					 HSWEP_U_MSR_PMON_BOX_FILTER_CID)

/* Haswell-EP CBo */
#घोषणा HSWEP_C0_MSR_PMON_CTR0			0xe08
#घोषणा HSWEP_C0_MSR_PMON_CTL0			0xe01
#घोषणा HSWEP_C0_MSR_PMON_BOX_CTL			0xe00
#घोषणा HSWEP_C0_MSR_PMON_BOX_FILTER0		0xe05
#घोषणा HSWEP_CBO_MSR_OFFSET			0x10


#घोषणा HSWEP_CB0_MSR_PMON_BOX_FILTER_TID		(0x3fULL << 0)
#घोषणा HSWEP_CB0_MSR_PMON_BOX_FILTER_LINK	(0xfULL << 6)
#घोषणा HSWEP_CB0_MSR_PMON_BOX_FILTER_STATE	(0x7fULL << 17)
#घोषणा HSWEP_CB0_MSR_PMON_BOX_FILTER_NID		(0xffffULL << 32)
#घोषणा HSWEP_CB0_MSR_PMON_BOX_FILTER_OPC		(0x1ffULL << 52)
#घोषणा HSWEP_CB0_MSR_PMON_BOX_FILTER_C6		(0x1ULL << 61)
#घोषणा HSWEP_CB0_MSR_PMON_BOX_FILTER_NC		(0x1ULL << 62)
#घोषणा HSWEP_CB0_MSR_PMON_BOX_FILTER_ISOC	(0x1ULL << 63)


/* Haswell-EP Sbox */
#घोषणा HSWEP_S0_MSR_PMON_CTR0			0x726
#घोषणा HSWEP_S0_MSR_PMON_CTL0			0x721
#घोषणा HSWEP_S0_MSR_PMON_BOX_CTL			0x720
#घोषणा HSWEP_SBOX_MSR_OFFSET			0xa
#घोषणा HSWEP_S_MSR_PMON_RAW_EVENT_MASK		(SNBEP_PMON_RAW_EVENT_MASK | \
						 SNBEP_CBO_PMON_CTL_TID_EN)

/* Haswell-EP PCU */
#घोषणा HSWEP_PCU_MSR_PMON_CTR0			0x717
#घोषणा HSWEP_PCU_MSR_PMON_CTL0			0x711
#घोषणा HSWEP_PCU_MSR_PMON_BOX_CTL		0x710
#घोषणा HSWEP_PCU_MSR_PMON_BOX_FILTER		0x715

/* KNL Ubox */
#घोषणा KNL_U_MSR_PMON_RAW_EVENT_MASK \
					(SNBEP_U_MSR_PMON_RAW_EVENT_MASK | \
						SNBEP_CBO_PMON_CTL_TID_EN)
/* KNL CHA */
#घोषणा KNL_CHA_MSR_OFFSET			0xc
#घोषणा KNL_CHA_MSR_PMON_CTL_QOR		(1 << 16)
#घोषणा KNL_CHA_MSR_PMON_RAW_EVENT_MASK \
					(SNBEP_CBO_MSR_PMON_RAW_EVENT_MASK | \
					 KNL_CHA_MSR_PMON_CTL_QOR)
#घोषणा KNL_CHA_MSR_PMON_BOX_FILTER_TID		0x1ff
#घोषणा KNL_CHA_MSR_PMON_BOX_FILTER_STATE	(7 << 18)
#घोषणा KNL_CHA_MSR_PMON_BOX_FILTER_OP		(0xfffffe2aULL << 32)
#घोषणा KNL_CHA_MSR_PMON_BOX_FILTER_REMOTE_NODE	(0x1ULL << 32)
#घोषणा KNL_CHA_MSR_PMON_BOX_FILTER_LOCAL_NODE	(0x1ULL << 33)
#घोषणा KNL_CHA_MSR_PMON_BOX_FILTER_NNC		(0x1ULL << 37)

/* KNL EDC/MC UCLK */
#घोषणा KNL_UCLK_MSR_PMON_CTR0_LOW		0x400
#घोषणा KNL_UCLK_MSR_PMON_CTL0			0x420
#घोषणा KNL_UCLK_MSR_PMON_BOX_CTL		0x430
#घोषणा KNL_UCLK_MSR_PMON_UCLK_FIXED_LOW	0x44c
#घोषणा KNL_UCLK_MSR_PMON_UCLK_FIXED_CTL	0x454
#घोषणा KNL_PMON_FIXED_CTL_EN			0x1

/* KNL EDC */
#घोषणा KNL_EDC0_ECLK_MSR_PMON_CTR0_LOW		0xa00
#घोषणा KNL_EDC0_ECLK_MSR_PMON_CTL0		0xa20
#घोषणा KNL_EDC0_ECLK_MSR_PMON_BOX_CTL		0xa30
#घोषणा KNL_EDC0_ECLK_MSR_PMON_ECLK_FIXED_LOW	0xa3c
#घोषणा KNL_EDC0_ECLK_MSR_PMON_ECLK_FIXED_CTL	0xa44

/* KNL MC */
#घोषणा KNL_MC0_CH0_MSR_PMON_CTR0_LOW		0xb00
#घोषणा KNL_MC0_CH0_MSR_PMON_CTL0		0xb20
#घोषणा KNL_MC0_CH0_MSR_PMON_BOX_CTL		0xb30
#घोषणा KNL_MC0_CH0_MSR_PMON_FIXED_LOW		0xb3c
#घोषणा KNL_MC0_CH0_MSR_PMON_FIXED_CTL		0xb44

/* KNL IRP */
#घोषणा KNL_IRP_PCI_PMON_BOX_CTL		0xf0
#घोषणा KNL_IRP_PCI_PMON_RAW_EVENT_MASK		(SNBEP_PMON_RAW_EVENT_MASK | \
						 KNL_CHA_MSR_PMON_CTL_QOR)
/* KNL PCU */
#घोषणा KNL_PCU_PMON_CTL_EV_SEL_MASK		0x0000007f
#घोषणा KNL_PCU_PMON_CTL_USE_OCC_CTR		(1 << 7)
#घोषणा KNL_PCU_MSR_PMON_CTL_TRESH_MASK		0x3f000000
#घोषणा KNL_PCU_MSR_PMON_RAW_EVENT_MASK	\
				(KNL_PCU_PMON_CTL_EV_SEL_MASK | \
				 KNL_PCU_PMON_CTL_USE_OCC_CTR | \
				 SNBEP_PCU_MSR_PMON_CTL_OCC_SEL_MASK | \
				 SNBEP_PMON_CTL_EDGE_DET | \
				 SNBEP_CBO_PMON_CTL_TID_EN | \
				 SNBEP_PMON_CTL_INVERT | \
				 KNL_PCU_MSR_PMON_CTL_TRESH_MASK | \
				 SNBEP_PCU_MSR_PMON_CTL_OCC_INVERT | \
				 SNBEP_PCU_MSR_PMON_CTL_OCC_EDGE_DET)

/* SKX pci bus to socket mapping */
#घोषणा SKX_CPUNODEID			0xc0
#घोषणा SKX_GIDNIDMAP			0xd4

/*
 * The CPU_BUS_NUMBER MSR वापसs the values of the respective CPUBUSNO CSR
 * that BIOS programmed. MSR has package scope.
 * |  Bit  |  Default  |  Description
 * | [63]  |    00h    | VALID - When set, indicates the CPU bus
 *                       numbers have been initialized. (RO)
 * |[62:48]|    ---    | Reserved
 * |[47:40]|    00h    | BUS_NUM_5 - Return the bus number BIOS asचिन्हित
 *                       CPUBUSNO(5). (RO)
 * |[39:32]|    00h    | BUS_NUM_4 - Return the bus number BIOS asचिन्हित
 *                       CPUBUSNO(4). (RO)
 * |[31:24]|    00h    | BUS_NUM_3 - Return the bus number BIOS asचिन्हित
 *                       CPUBUSNO(3). (RO)
 * |[23:16]|    00h    | BUS_NUM_2 - Return the bus number BIOS asचिन्हित
 *                       CPUBUSNO(2). (RO)
 * |[15:8] |    00h    | BUS_NUM_1 - Return the bus number BIOS asचिन्हित
 *                       CPUBUSNO(1). (RO)
 * | [7:0] |    00h    | BUS_NUM_0 - Return the bus number BIOS asचिन्हित
 *                       CPUBUSNO(0). (RO)
 */
#घोषणा SKX_MSR_CPU_BUS_NUMBER		0x300
#घोषणा SKX_MSR_CPU_BUS_VALID_BIT	(1ULL << 63)
#घोषणा BUS_NUM_STRIDE			8

/* SKX CHA */
#घोषणा SKX_CHA_MSR_PMON_BOX_FILTER_TID		(0x1ffULL << 0)
#घोषणा SKX_CHA_MSR_PMON_BOX_FILTER_LINK	(0xfULL << 9)
#घोषणा SKX_CHA_MSR_PMON_BOX_FILTER_STATE	(0x3ffULL << 17)
#घोषणा SKX_CHA_MSR_PMON_BOX_FILTER_REM		(0x1ULL << 32)
#घोषणा SKX_CHA_MSR_PMON_BOX_FILTER_LOC		(0x1ULL << 33)
#घोषणा SKX_CHA_MSR_PMON_BOX_FILTER_ALL_OPC	(0x1ULL << 35)
#घोषणा SKX_CHA_MSR_PMON_BOX_FILTER_NM		(0x1ULL << 36)
#घोषणा SKX_CHA_MSR_PMON_BOX_FILTER_NOT_NM	(0x1ULL << 37)
#घोषणा SKX_CHA_MSR_PMON_BOX_FILTER_OPC0	(0x3ffULL << 41)
#घोषणा SKX_CHA_MSR_PMON_BOX_FILTER_OPC1	(0x3ffULL << 51)
#घोषणा SKX_CHA_MSR_PMON_BOX_FILTER_C6		(0x1ULL << 61)
#घोषणा SKX_CHA_MSR_PMON_BOX_FILTER_NC		(0x1ULL << 62)
#घोषणा SKX_CHA_MSR_PMON_BOX_FILTER_ISOC	(0x1ULL << 63)

/* SKX IIO */
#घोषणा SKX_IIO0_MSR_PMON_CTL0		0xa48
#घोषणा SKX_IIO0_MSR_PMON_CTR0		0xa41
#घोषणा SKX_IIO0_MSR_PMON_BOX_CTL	0xa40
#घोषणा SKX_IIO_MSR_OFFSET		0x20

#घोषणा SKX_PMON_CTL_TRESH_MASK		(0xff << 24)
#घोषणा SKX_PMON_CTL_TRESH_MASK_EXT	(0xf)
#घोषणा SKX_PMON_CTL_CH_MASK		(0xff << 4)
#घोषणा SKX_PMON_CTL_FC_MASK		(0x7 << 12)
#घोषणा SKX_IIO_PMON_RAW_EVENT_MASK	(SNBEP_PMON_CTL_EV_SEL_MASK | \
					 SNBEP_PMON_CTL_UMASK_MASK | \
					 SNBEP_PMON_CTL_EDGE_DET | \
					 SNBEP_PMON_CTL_INVERT | \
					 SKX_PMON_CTL_TRESH_MASK)
#घोषणा SKX_IIO_PMON_RAW_EVENT_MASK_EXT	(SKX_PMON_CTL_TRESH_MASK_EXT | \
					 SKX_PMON_CTL_CH_MASK | \
					 SKX_PMON_CTL_FC_MASK)

/* SKX IRP */
#घोषणा SKX_IRP0_MSR_PMON_CTL0		0xa5b
#घोषणा SKX_IRP0_MSR_PMON_CTR0		0xa59
#घोषणा SKX_IRP0_MSR_PMON_BOX_CTL	0xa58
#घोषणा SKX_IRP_MSR_OFFSET		0x20

/* SKX UPI */
#घोषणा SKX_UPI_PCI_PMON_CTL0		0x350
#घोषणा SKX_UPI_PCI_PMON_CTR0		0x318
#घोषणा SKX_UPI_PCI_PMON_BOX_CTL	0x378
#घोषणा SKX_UPI_CTL_UMASK_EXT		0xffefff

/* SKX M2M */
#घोषणा SKX_M2M_PCI_PMON_CTL0		0x228
#घोषणा SKX_M2M_PCI_PMON_CTR0		0x200
#घोषणा SKX_M2M_PCI_PMON_BOX_CTL	0x258

/* SNR Ubox */
#घोषणा SNR_U_MSR_PMON_CTR0			0x1f98
#घोषणा SNR_U_MSR_PMON_CTL0			0x1f91
#घोषणा SNR_U_MSR_PMON_UCLK_FIXED_CTL		0x1f93
#घोषणा SNR_U_MSR_PMON_UCLK_FIXED_CTR		0x1f94

/* SNR CHA */
#घोषणा SNR_CHA_RAW_EVENT_MASK_EXT		0x3ffffff
#घोषणा SNR_CHA_MSR_PMON_CTL0			0x1c01
#घोषणा SNR_CHA_MSR_PMON_CTR0			0x1c08
#घोषणा SNR_CHA_MSR_PMON_BOX_CTL		0x1c00
#घोषणा SNR_C0_MSR_PMON_BOX_FILTER0		0x1c05


/* SNR IIO */
#घोषणा SNR_IIO_MSR_PMON_CTL0			0x1e08
#घोषणा SNR_IIO_MSR_PMON_CTR0			0x1e01
#घोषणा SNR_IIO_MSR_PMON_BOX_CTL		0x1e00
#घोषणा SNR_IIO_MSR_OFFSET			0x10
#घोषणा SNR_IIO_PMON_RAW_EVENT_MASK_EXT		0x7ffff

/* SNR IRP */
#घोषणा SNR_IRP0_MSR_PMON_CTL0			0x1ea8
#घोषणा SNR_IRP0_MSR_PMON_CTR0			0x1ea1
#घोषणा SNR_IRP0_MSR_PMON_BOX_CTL		0x1ea0
#घोषणा SNR_IRP_MSR_OFFSET			0x10

/* SNR M2PCIE */
#घोषणा SNR_M2PCIE_MSR_PMON_CTL0		0x1e58
#घोषणा SNR_M2PCIE_MSR_PMON_CTR0		0x1e51
#घोषणा SNR_M2PCIE_MSR_PMON_BOX_CTL		0x1e50
#घोषणा SNR_M2PCIE_MSR_OFFSET			0x10

/* SNR PCU */
#घोषणा SNR_PCU_MSR_PMON_CTL0			0x1ef1
#घोषणा SNR_PCU_MSR_PMON_CTR0			0x1ef8
#घोषणा SNR_PCU_MSR_PMON_BOX_CTL		0x1ef0
#घोषणा SNR_PCU_MSR_PMON_BOX_FILTER		0x1efc

/* SNR M2M */
#घोषणा SNR_M2M_PCI_PMON_CTL0			0x468
#घोषणा SNR_M2M_PCI_PMON_CTR0			0x440
#घोषणा SNR_M2M_PCI_PMON_BOX_CTL		0x438
#घोषणा SNR_M2M_PCI_PMON_UMASK_EXT		0xff

/* SNR PCIE3 */
#घोषणा SNR_PCIE3_PCI_PMON_CTL0			0x508
#घोषणा SNR_PCIE3_PCI_PMON_CTR0			0x4e8
#घोषणा SNR_PCIE3_PCI_PMON_BOX_CTL		0x4e0

/* SNR IMC */
#घोषणा SNR_IMC_MMIO_PMON_FIXED_CTL		0x54
#घोषणा SNR_IMC_MMIO_PMON_FIXED_CTR		0x38
#घोषणा SNR_IMC_MMIO_PMON_CTL0			0x40
#घोषणा SNR_IMC_MMIO_PMON_CTR0			0x8
#घोषणा SNR_IMC_MMIO_PMON_BOX_CTL		0x22800
#घोषणा SNR_IMC_MMIO_OFFSET			0x4000
#घोषणा SNR_IMC_MMIO_SIZE			0x4000
#घोषणा SNR_IMC_MMIO_BASE_OFFSET		0xd0
#घोषणा SNR_IMC_MMIO_BASE_MASK			0x1FFFFFFF
#घोषणा SNR_IMC_MMIO_MEM0_OFFSET		0xd8
#घोषणा SNR_IMC_MMIO_MEM0_MASK			0x7FF

/* ICX CHA */
#घोषणा ICX_C34_MSR_PMON_CTR0			0xb68
#घोषणा ICX_C34_MSR_PMON_CTL0			0xb61
#घोषणा ICX_C34_MSR_PMON_BOX_CTL		0xb60
#घोषणा ICX_C34_MSR_PMON_BOX_FILTER0		0xb65

/* ICX IIO */
#घोषणा ICX_IIO_MSR_PMON_CTL0			0xa58
#घोषणा ICX_IIO_MSR_PMON_CTR0			0xa51
#घोषणा ICX_IIO_MSR_PMON_BOX_CTL		0xa50

/* ICX IRP */
#घोषणा ICX_IRP0_MSR_PMON_CTL0			0xa4d
#घोषणा ICX_IRP0_MSR_PMON_CTR0			0xa4b
#घोषणा ICX_IRP0_MSR_PMON_BOX_CTL		0xa4a

/* ICX M2PCIE */
#घोषणा ICX_M2PCIE_MSR_PMON_CTL0		0xa46
#घोषणा ICX_M2PCIE_MSR_PMON_CTR0		0xa41
#घोषणा ICX_M2PCIE_MSR_PMON_BOX_CTL		0xa40

/* ICX UPI */
#घोषणा ICX_UPI_PCI_PMON_CTL0			0x350
#घोषणा ICX_UPI_PCI_PMON_CTR0			0x320
#घोषणा ICX_UPI_PCI_PMON_BOX_CTL		0x318
#घोषणा ICX_UPI_CTL_UMASK_EXT			0xffffff

/* ICX M3UPI*/
#घोषणा ICX_M3UPI_PCI_PMON_CTL0			0xd8
#घोषणा ICX_M3UPI_PCI_PMON_CTR0			0xa8
#घोषणा ICX_M3UPI_PCI_PMON_BOX_CTL		0xa0

/* ICX IMC */
#घोषणा ICX_NUMBER_IMC_CHN			2
#घोषणा ICX_IMC_MEM_STRIDE			0x4

DEFINE_UNCORE_FORMAT_ATTR(event, event, "config:0-7");
DEFINE_UNCORE_FORMAT_ATTR(event2, event, "config:0-6");
DEFINE_UNCORE_FORMAT_ATTR(event_ext, event, "config:0-7,21");
DEFINE_UNCORE_FORMAT_ATTR(use_occ_ctr, use_occ_ctr, "config:7");
DEFINE_UNCORE_FORMAT_ATTR(umask, umask, "config:8-15");
DEFINE_UNCORE_FORMAT_ATTR(umask_ext, umask, "config:8-15,32-43,45-55");
DEFINE_UNCORE_FORMAT_ATTR(umask_ext2, umask, "config:8-15,32-57");
DEFINE_UNCORE_FORMAT_ATTR(umask_ext3, umask, "config:8-15,32-39");
DEFINE_UNCORE_FORMAT_ATTR(umask_ext4, umask, "config:8-15,32-55");
DEFINE_UNCORE_FORMAT_ATTR(qor, qor, "config:16");
DEFINE_UNCORE_FORMAT_ATTR(edge, edge, "config:18");
DEFINE_UNCORE_FORMAT_ATTR(tid_en, tid_en, "config:19");
DEFINE_UNCORE_FORMAT_ATTR(inv, inv, "config:23");
DEFINE_UNCORE_FORMAT_ATTR(thresh9, thresh, "config:24-35");
DEFINE_UNCORE_FORMAT_ATTR(thresh8, thresh, "config:24-31");
DEFINE_UNCORE_FORMAT_ATTR(thresh6, thresh, "config:24-29");
DEFINE_UNCORE_FORMAT_ATTR(thresh5, thresh, "config:24-28");
DEFINE_UNCORE_FORMAT_ATTR(occ_sel, occ_sel, "config:14-15");
DEFINE_UNCORE_FORMAT_ATTR(occ_invert, occ_invert, "config:30");
DEFINE_UNCORE_FORMAT_ATTR(occ_edge, occ_edge, "config:14-51");
DEFINE_UNCORE_FORMAT_ATTR(occ_edge_det, occ_edge_det, "config:31");
DEFINE_UNCORE_FORMAT_ATTR(ch_mask, ch_mask, "config:36-43");
DEFINE_UNCORE_FORMAT_ATTR(ch_mask2, ch_mask, "config:36-47");
DEFINE_UNCORE_FORMAT_ATTR(fc_mask, fc_mask, "config:44-46");
DEFINE_UNCORE_FORMAT_ATTR(fc_mask2, fc_mask, "config:48-50");
DEFINE_UNCORE_FORMAT_ATTR(filter_tid, filter_tid, "config1:0-4");
DEFINE_UNCORE_FORMAT_ATTR(filter_tid2, filter_tid, "config1:0");
DEFINE_UNCORE_FORMAT_ATTR(filter_tid3, filter_tid, "config1:0-5");
DEFINE_UNCORE_FORMAT_ATTR(filter_tid4, filter_tid, "config1:0-8");
DEFINE_UNCORE_FORMAT_ATTR(filter_tid5, filter_tid, "config1:0-9");
DEFINE_UNCORE_FORMAT_ATTR(filter_cid, filter_cid, "config1:5");
DEFINE_UNCORE_FORMAT_ATTR(filter_link, filter_link, "config1:5-8");
DEFINE_UNCORE_FORMAT_ATTR(filter_link2, filter_link, "config1:6-8");
DEFINE_UNCORE_FORMAT_ATTR(filter_link3, filter_link, "config1:12");
DEFINE_UNCORE_FORMAT_ATTR(filter_nid, filter_nid, "config1:10-17");
DEFINE_UNCORE_FORMAT_ATTR(filter_nid2, filter_nid, "config1:32-47");
DEFINE_UNCORE_FORMAT_ATTR(filter_state, filter_state, "config1:18-22");
DEFINE_UNCORE_FORMAT_ATTR(filter_state2, filter_state, "config1:17-22");
DEFINE_UNCORE_FORMAT_ATTR(filter_state3, filter_state, "config1:17-23");
DEFINE_UNCORE_FORMAT_ATTR(filter_state4, filter_state, "config1:18-20");
DEFINE_UNCORE_FORMAT_ATTR(filter_state5, filter_state, "config1:17-26");
DEFINE_UNCORE_FORMAT_ATTR(filter_rem, filter_rem, "config1:32");
DEFINE_UNCORE_FORMAT_ATTR(filter_loc, filter_loc, "config1:33");
DEFINE_UNCORE_FORMAT_ATTR(filter_nm, filter_nm, "config1:36");
DEFINE_UNCORE_FORMAT_ATTR(filter_not_nm, filter_not_nm, "config1:37");
DEFINE_UNCORE_FORMAT_ATTR(filter_local, filter_local, "config1:33");
DEFINE_UNCORE_FORMAT_ATTR(filter_all_op, filter_all_op, "config1:35");
DEFINE_UNCORE_FORMAT_ATTR(filter_nnm, filter_nnm, "config1:37");
DEFINE_UNCORE_FORMAT_ATTR(filter_opc, filter_opc, "config1:23-31");
DEFINE_UNCORE_FORMAT_ATTR(filter_opc2, filter_opc, "config1:52-60");
DEFINE_UNCORE_FORMAT_ATTR(filter_opc3, filter_opc, "config1:41-60");
DEFINE_UNCORE_FORMAT_ATTR(filter_opc_0, filter_opc0, "config1:41-50");
DEFINE_UNCORE_FORMAT_ATTR(filter_opc_1, filter_opc1, "config1:51-60");
DEFINE_UNCORE_FORMAT_ATTR(filter_nc, filter_nc, "config1:62");
DEFINE_UNCORE_FORMAT_ATTR(filter_c6, filter_c6, "config1:61");
DEFINE_UNCORE_FORMAT_ATTR(filter_isoc, filter_isoc, "config1:63");
DEFINE_UNCORE_FORMAT_ATTR(filter_band0, filter_band0, "config1:0-7");
DEFINE_UNCORE_FORMAT_ATTR(filter_band1, filter_band1, "config1:8-15");
DEFINE_UNCORE_FORMAT_ATTR(filter_band2, filter_band2, "config1:16-23");
DEFINE_UNCORE_FORMAT_ATTR(filter_band3, filter_band3, "config1:24-31");
DEFINE_UNCORE_FORMAT_ATTR(match_rds, match_rds, "config1:48-51");
DEFINE_UNCORE_FORMAT_ATTR(match_rnid30, match_rnid30, "config1:32-35");
DEFINE_UNCORE_FORMAT_ATTR(match_rnid4, match_rnid4, "config1:31");
DEFINE_UNCORE_FORMAT_ATTR(match_dnid, match_dnid, "config1:13-17");
DEFINE_UNCORE_FORMAT_ATTR(match_mc, match_mc, "config1:9-12");
DEFINE_UNCORE_FORMAT_ATTR(match_opc, match_opc, "config1:5-8");
DEFINE_UNCORE_FORMAT_ATTR(match_vnw, match_vnw, "config1:3-4");
DEFINE_UNCORE_FORMAT_ATTR(match0, match0, "config1:0-31");
DEFINE_UNCORE_FORMAT_ATTR(match1, match1, "config1:32-63");
DEFINE_UNCORE_FORMAT_ATTR(mask_rds, mask_rds, "config2:48-51");
DEFINE_UNCORE_FORMAT_ATTR(mask_rnid30, mask_rnid30, "config2:32-35");
DEFINE_UNCORE_FORMAT_ATTR(mask_rnid4, mask_rnid4, "config2:31");
DEFINE_UNCORE_FORMAT_ATTR(mask_dnid, mask_dnid, "config2:13-17");
DEFINE_UNCORE_FORMAT_ATTR(mask_mc, mask_mc, "config2:9-12");
DEFINE_UNCORE_FORMAT_ATTR(mask_opc, mask_opc, "config2:5-8");
DEFINE_UNCORE_FORMAT_ATTR(mask_vnw, mask_vnw, "config2:3-4");
DEFINE_UNCORE_FORMAT_ATTR(mask0, mask0, "config2:0-31");
DEFINE_UNCORE_FORMAT_ATTR(mask1, mask1, "config2:32-63");

अटल व्योम snbep_uncore_pci_disable_box(काष्ठा पूर्णांकel_uncore_box *box)
अणु
	काष्ठा pci_dev *pdev = box->pci_dev;
	पूर्णांक box_ctl = uncore_pci_box_ctl(box);
	u32 config = 0;

	अगर (!pci_पढ़ो_config_dword(pdev, box_ctl, &config)) अणु
		config |= SNBEP_PMON_BOX_CTL_FRZ;
		pci_ग_लिखो_config_dword(pdev, box_ctl, config);
	पूर्ण
पूर्ण

अटल व्योम snbep_uncore_pci_enable_box(काष्ठा पूर्णांकel_uncore_box *box)
अणु
	काष्ठा pci_dev *pdev = box->pci_dev;
	पूर्णांक box_ctl = uncore_pci_box_ctl(box);
	u32 config = 0;

	अगर (!pci_पढ़ो_config_dword(pdev, box_ctl, &config)) अणु
		config &= ~SNBEP_PMON_BOX_CTL_FRZ;
		pci_ग_लिखो_config_dword(pdev, box_ctl, config);
	पूर्ण
पूर्ण

अटल व्योम snbep_uncore_pci_enable_event(काष्ठा पूर्णांकel_uncore_box *box, काष्ठा perf_event *event)
अणु
	काष्ठा pci_dev *pdev = box->pci_dev;
	काष्ठा hw_perf_event *hwc = &event->hw;

	pci_ग_लिखो_config_dword(pdev, hwc->config_base, hwc->config | SNBEP_PMON_CTL_EN);
पूर्ण

अटल व्योम snbep_uncore_pci_disable_event(काष्ठा पूर्णांकel_uncore_box *box, काष्ठा perf_event *event)
अणु
	काष्ठा pci_dev *pdev = box->pci_dev;
	काष्ठा hw_perf_event *hwc = &event->hw;

	pci_ग_लिखो_config_dword(pdev, hwc->config_base, hwc->config);
पूर्ण

अटल u64 snbep_uncore_pci_पढ़ो_counter(काष्ठा पूर्णांकel_uncore_box *box, काष्ठा perf_event *event)
अणु
	काष्ठा pci_dev *pdev = box->pci_dev;
	काष्ठा hw_perf_event *hwc = &event->hw;
	u64 count = 0;

	pci_पढ़ो_config_dword(pdev, hwc->event_base, (u32 *)&count);
	pci_पढ़ो_config_dword(pdev, hwc->event_base + 4, (u32 *)&count + 1);

	वापस count;
पूर्ण

अटल व्योम snbep_uncore_pci_init_box(काष्ठा पूर्णांकel_uncore_box *box)
अणु
	काष्ठा pci_dev *pdev = box->pci_dev;
	पूर्णांक box_ctl = uncore_pci_box_ctl(box);

	pci_ग_लिखो_config_dword(pdev, box_ctl, SNBEP_PMON_BOX_CTL_INT);
पूर्ण

अटल व्योम snbep_uncore_msr_disable_box(काष्ठा पूर्णांकel_uncore_box *box)
अणु
	u64 config;
	अचिन्हित msr;

	msr = uncore_msr_box_ctl(box);
	अगर (msr) अणु
		rdmsrl(msr, config);
		config |= SNBEP_PMON_BOX_CTL_FRZ;
		wrmsrl(msr, config);
	पूर्ण
पूर्ण

अटल व्योम snbep_uncore_msr_enable_box(काष्ठा पूर्णांकel_uncore_box *box)
अणु
	u64 config;
	अचिन्हित msr;

	msr = uncore_msr_box_ctl(box);
	अगर (msr) अणु
		rdmsrl(msr, config);
		config &= ~SNBEP_PMON_BOX_CTL_FRZ;
		wrmsrl(msr, config);
	पूर्ण
पूर्ण

अटल व्योम snbep_uncore_msr_enable_event(काष्ठा पूर्णांकel_uncore_box *box, काष्ठा perf_event *event)
अणु
	काष्ठा hw_perf_event *hwc = &event->hw;
	काष्ठा hw_perf_event_extra *reg1 = &hwc->extra_reg;

	अगर (reg1->idx != EXTRA_REG_NONE)
		wrmsrl(reg1->reg, uncore_shared_reg_config(box, 0));

	wrmsrl(hwc->config_base, hwc->config | SNBEP_PMON_CTL_EN);
पूर्ण

अटल व्योम snbep_uncore_msr_disable_event(काष्ठा पूर्णांकel_uncore_box *box,
					काष्ठा perf_event *event)
अणु
	काष्ठा hw_perf_event *hwc = &event->hw;

	wrmsrl(hwc->config_base, hwc->config);
पूर्ण

अटल व्योम snbep_uncore_msr_init_box(काष्ठा पूर्णांकel_uncore_box *box)
अणु
	अचिन्हित msr = uncore_msr_box_ctl(box);

	अगर (msr)
		wrmsrl(msr, SNBEP_PMON_BOX_CTL_INT);
पूर्ण

अटल काष्ठा attribute *snbep_uncore_क्रमmats_attr[] = अणु
	&क्रमmat_attr_event.attr,
	&क्रमmat_attr_umask.attr,
	&क्रमmat_attr_edge.attr,
	&क्रमmat_attr_inv.attr,
	&क्रमmat_attr_thresh8.attr,
	शून्य,
पूर्ण;

अटल काष्ठा attribute *snbep_uncore_ubox_क्रमmats_attr[] = अणु
	&क्रमmat_attr_event.attr,
	&क्रमmat_attr_umask.attr,
	&क्रमmat_attr_edge.attr,
	&क्रमmat_attr_inv.attr,
	&क्रमmat_attr_thresh5.attr,
	शून्य,
पूर्ण;

अटल काष्ठा attribute *snbep_uncore_cbox_क्रमmats_attr[] = अणु
	&क्रमmat_attr_event.attr,
	&क्रमmat_attr_umask.attr,
	&क्रमmat_attr_edge.attr,
	&क्रमmat_attr_tid_en.attr,
	&क्रमmat_attr_inv.attr,
	&क्रमmat_attr_thresh8.attr,
	&क्रमmat_attr_filter_tid.attr,
	&क्रमmat_attr_filter_nid.attr,
	&क्रमmat_attr_filter_state.attr,
	&क्रमmat_attr_filter_opc.attr,
	शून्य,
पूर्ण;

अटल काष्ठा attribute *snbep_uncore_pcu_क्रमmats_attr[] = अणु
	&क्रमmat_attr_event.attr,
	&क्रमmat_attr_occ_sel.attr,
	&क्रमmat_attr_edge.attr,
	&क्रमmat_attr_inv.attr,
	&क्रमmat_attr_thresh5.attr,
	&क्रमmat_attr_occ_invert.attr,
	&क्रमmat_attr_occ_edge.attr,
	&क्रमmat_attr_filter_band0.attr,
	&क्रमmat_attr_filter_band1.attr,
	&क्रमmat_attr_filter_band2.attr,
	&क्रमmat_attr_filter_band3.attr,
	शून्य,
पूर्ण;

अटल काष्ठा attribute *snbep_uncore_qpi_क्रमmats_attr[] = अणु
	&क्रमmat_attr_event_ext.attr,
	&क्रमmat_attr_umask.attr,
	&क्रमmat_attr_edge.attr,
	&क्रमmat_attr_inv.attr,
	&क्रमmat_attr_thresh8.attr,
	&क्रमmat_attr_match_rds.attr,
	&क्रमmat_attr_match_rnid30.attr,
	&क्रमmat_attr_match_rnid4.attr,
	&क्रमmat_attr_match_dnid.attr,
	&क्रमmat_attr_match_mc.attr,
	&क्रमmat_attr_match_opc.attr,
	&क्रमmat_attr_match_vnw.attr,
	&क्रमmat_attr_match0.attr,
	&क्रमmat_attr_match1.attr,
	&क्रमmat_attr_mask_rds.attr,
	&क्रमmat_attr_mask_rnid30.attr,
	&क्रमmat_attr_mask_rnid4.attr,
	&क्रमmat_attr_mask_dnid.attr,
	&क्रमmat_attr_mask_mc.attr,
	&क्रमmat_attr_mask_opc.attr,
	&क्रमmat_attr_mask_vnw.attr,
	&क्रमmat_attr_mask0.attr,
	&क्रमmat_attr_mask1.attr,
	शून्य,
पूर्ण;

अटल काष्ठा uncore_event_desc snbep_uncore_imc_events[] = अणु
	INTEL_UNCORE_EVENT_DESC(घड़ीticks,      "event=0xff,umask=0x00"),
	INTEL_UNCORE_EVENT_DESC(cas_count_पढ़ो,  "event=0x04,umask=0x03"),
	INTEL_UNCORE_EVENT_DESC(cas_count_पढ़ो.scale, "6.103515625e-5"),
	INTEL_UNCORE_EVENT_DESC(cas_count_पढ़ो.unit, "MiB"),
	INTEL_UNCORE_EVENT_DESC(cas_count_ग_लिखो, "event=0x04,umask=0x0c"),
	INTEL_UNCORE_EVENT_DESC(cas_count_ग_लिखो.scale, "6.103515625e-5"),
	INTEL_UNCORE_EVENT_DESC(cas_count_ग_लिखो.unit, "MiB"),
	अणु /* end: all zeroes */ पूर्ण,
पूर्ण;

अटल काष्ठा uncore_event_desc snbep_uncore_qpi_events[] = अणु
	INTEL_UNCORE_EVENT_DESC(घड़ीticks,       "event=0x14"),
	INTEL_UNCORE_EVENT_DESC(txl_flits_active, "event=0x00,umask=0x06"),
	INTEL_UNCORE_EVENT_DESC(drs_data,         "event=0x102,umask=0x08"),
	INTEL_UNCORE_EVENT_DESC(ncb_data,         "event=0x103,umask=0x04"),
	अणु /* end: all zeroes */ पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा attribute_group snbep_uncore_क्रमmat_group = अणु
	.name = "format",
	.attrs = snbep_uncore_क्रमmats_attr,
पूर्ण;

अटल स्थिर काष्ठा attribute_group snbep_uncore_ubox_क्रमmat_group = अणु
	.name = "format",
	.attrs = snbep_uncore_ubox_क्रमmats_attr,
पूर्ण;

अटल स्थिर काष्ठा attribute_group snbep_uncore_cbox_क्रमmat_group = अणु
	.name = "format",
	.attrs = snbep_uncore_cbox_क्रमmats_attr,
पूर्ण;

अटल स्थिर काष्ठा attribute_group snbep_uncore_pcu_क्रमmat_group = अणु
	.name = "format",
	.attrs = snbep_uncore_pcu_क्रमmats_attr,
पूर्ण;

अटल स्थिर काष्ठा attribute_group snbep_uncore_qpi_क्रमmat_group = अणु
	.name = "format",
	.attrs = snbep_uncore_qpi_क्रमmats_attr,
पूर्ण;

#घोषणा __SNBEP_UNCORE_MSR_OPS_COMMON_INIT()			\
	.disable_box	= snbep_uncore_msr_disable_box,		\
	.enable_box	= snbep_uncore_msr_enable_box,		\
	.disable_event	= snbep_uncore_msr_disable_event,	\
	.enable_event	= snbep_uncore_msr_enable_event,	\
	.पढ़ो_counter	= uncore_msr_पढ़ो_counter

#घोषणा SNBEP_UNCORE_MSR_OPS_COMMON_INIT()			\
	__SNBEP_UNCORE_MSR_OPS_COMMON_INIT(),			\
	.init_box	= snbep_uncore_msr_init_box		\

अटल काष्ठा पूर्णांकel_uncore_ops snbep_uncore_msr_ops = अणु
	SNBEP_UNCORE_MSR_OPS_COMMON_INIT(),
पूर्ण;

#घोषणा SNBEP_UNCORE_PCI_OPS_COMMON_INIT()			\
	.init_box	= snbep_uncore_pci_init_box,		\
	.disable_box	= snbep_uncore_pci_disable_box,		\
	.enable_box	= snbep_uncore_pci_enable_box,		\
	.disable_event	= snbep_uncore_pci_disable_event,	\
	.पढ़ो_counter	= snbep_uncore_pci_पढ़ो_counter

अटल काष्ठा पूर्णांकel_uncore_ops snbep_uncore_pci_ops = अणु
	SNBEP_UNCORE_PCI_OPS_COMMON_INIT(),
	.enable_event	= snbep_uncore_pci_enable_event,	\
पूर्ण;

अटल काष्ठा event_स्थिरraपूर्णांक snbep_uncore_cbox_स्थिरraपूर्णांकs[] = अणु
	UNCORE_EVENT_CONSTRAINT(0x01, 0x1),
	UNCORE_EVENT_CONSTRAINT(0x02, 0x3),
	UNCORE_EVENT_CONSTRAINT(0x04, 0x3),
	UNCORE_EVENT_CONSTRAINT(0x05, 0x3),
	UNCORE_EVENT_CONSTRAINT(0x07, 0x3),
	UNCORE_EVENT_CONSTRAINT(0x09, 0x3),
	UNCORE_EVENT_CONSTRAINT(0x11, 0x1),
	UNCORE_EVENT_CONSTRAINT(0x12, 0x3),
	UNCORE_EVENT_CONSTRAINT(0x13, 0x3),
	UNCORE_EVENT_CONSTRAINT(0x1b, 0xc),
	UNCORE_EVENT_CONSTRAINT(0x1c, 0xc),
	UNCORE_EVENT_CONSTRAINT(0x1d, 0xc),
	UNCORE_EVENT_CONSTRAINT(0x1e, 0xc),
	UNCORE_EVENT_CONSTRAINT(0x1f, 0xe),
	UNCORE_EVENT_CONSTRAINT(0x21, 0x3),
	UNCORE_EVENT_CONSTRAINT(0x23, 0x3),
	UNCORE_EVENT_CONSTRAINT(0x31, 0x3),
	UNCORE_EVENT_CONSTRAINT(0x32, 0x3),
	UNCORE_EVENT_CONSTRAINT(0x33, 0x3),
	UNCORE_EVENT_CONSTRAINT(0x34, 0x3),
	UNCORE_EVENT_CONSTRAINT(0x35, 0x3),
	UNCORE_EVENT_CONSTRAINT(0x36, 0x1),
	UNCORE_EVENT_CONSTRAINT(0x37, 0x3),
	UNCORE_EVENT_CONSTRAINT(0x38, 0x3),
	UNCORE_EVENT_CONSTRAINT(0x39, 0x3),
	UNCORE_EVENT_CONSTRAINT(0x3b, 0x1),
	EVENT_CONSTRAINT_END
पूर्ण;

अटल काष्ठा event_स्थिरraपूर्णांक snbep_uncore_r2pcie_स्थिरraपूर्णांकs[] = अणु
	UNCORE_EVENT_CONSTRAINT(0x10, 0x3),
	UNCORE_EVENT_CONSTRAINT(0x11, 0x3),
	UNCORE_EVENT_CONSTRAINT(0x12, 0x1),
	UNCORE_EVENT_CONSTRAINT(0x23, 0x3),
	UNCORE_EVENT_CONSTRAINT(0x24, 0x3),
	UNCORE_EVENT_CONSTRAINT(0x25, 0x3),
	UNCORE_EVENT_CONSTRAINT(0x26, 0x3),
	UNCORE_EVENT_CONSTRAINT(0x32, 0x3),
	UNCORE_EVENT_CONSTRAINT(0x33, 0x3),
	UNCORE_EVENT_CONSTRAINT(0x34, 0x3),
	EVENT_CONSTRAINT_END
पूर्ण;

अटल काष्ठा event_स्थिरraपूर्णांक snbep_uncore_r3qpi_स्थिरraपूर्णांकs[] = अणु
	UNCORE_EVENT_CONSTRAINT(0x10, 0x3),
	UNCORE_EVENT_CONSTRAINT(0x11, 0x3),
	UNCORE_EVENT_CONSTRAINT(0x12, 0x3),
	UNCORE_EVENT_CONSTRAINT(0x13, 0x1),
	UNCORE_EVENT_CONSTRAINT(0x20, 0x3),
	UNCORE_EVENT_CONSTRAINT(0x21, 0x3),
	UNCORE_EVENT_CONSTRAINT(0x22, 0x3),
	UNCORE_EVENT_CONSTRAINT(0x23, 0x3),
	UNCORE_EVENT_CONSTRAINT(0x24, 0x3),
	UNCORE_EVENT_CONSTRAINT(0x25, 0x3),
	UNCORE_EVENT_CONSTRAINT(0x26, 0x3),
	UNCORE_EVENT_CONSTRAINT(0x28, 0x3),
	UNCORE_EVENT_CONSTRAINT(0x29, 0x3),
	UNCORE_EVENT_CONSTRAINT(0x2a, 0x3),
	UNCORE_EVENT_CONSTRAINT(0x2b, 0x3),
	UNCORE_EVENT_CONSTRAINT(0x2c, 0x3),
	UNCORE_EVENT_CONSTRAINT(0x2d, 0x3),
	UNCORE_EVENT_CONSTRAINT(0x2e, 0x3),
	UNCORE_EVENT_CONSTRAINT(0x2f, 0x3),
	UNCORE_EVENT_CONSTRAINT(0x30, 0x3),
	UNCORE_EVENT_CONSTRAINT(0x31, 0x3),
	UNCORE_EVENT_CONSTRAINT(0x32, 0x3),
	UNCORE_EVENT_CONSTRAINT(0x33, 0x3),
	UNCORE_EVENT_CONSTRAINT(0x34, 0x3),
	UNCORE_EVENT_CONSTRAINT(0x36, 0x3),
	UNCORE_EVENT_CONSTRAINT(0x37, 0x3),
	UNCORE_EVENT_CONSTRAINT(0x38, 0x3),
	UNCORE_EVENT_CONSTRAINT(0x39, 0x3),
	EVENT_CONSTRAINT_END
पूर्ण;

अटल काष्ठा पूर्णांकel_uncore_type snbep_uncore_ubox = अणु
	.name		= "ubox",
	.num_counters   = 2,
	.num_boxes	= 1,
	.perf_ctr_bits	= 44,
	.fixed_ctr_bits	= 48,
	.perf_ctr	= SNBEP_U_MSR_PMON_CTR0,
	.event_ctl	= SNBEP_U_MSR_PMON_CTL0,
	.event_mask	= SNBEP_U_MSR_PMON_RAW_EVENT_MASK,
	.fixed_ctr	= SNBEP_U_MSR_PMON_UCLK_FIXED_CTR,
	.fixed_ctl	= SNBEP_U_MSR_PMON_UCLK_FIXED_CTL,
	.ops		= &snbep_uncore_msr_ops,
	.क्रमmat_group	= &snbep_uncore_ubox_क्रमmat_group,
पूर्ण;

अटल काष्ठा extra_reg snbep_uncore_cbox_extra_regs[] = अणु
	SNBEP_CBO_EVENT_EXTRA_REG(SNBEP_CBO_PMON_CTL_TID_EN,
				  SNBEP_CBO_PMON_CTL_TID_EN, 0x1),
	SNBEP_CBO_EVENT_EXTRA_REG(0x0334, 0xffff, 0x4),
	SNBEP_CBO_EVENT_EXTRA_REG(0x4334, 0xffff, 0x6),
	SNBEP_CBO_EVENT_EXTRA_REG(0x0534, 0xffff, 0x4),
	SNBEP_CBO_EVENT_EXTRA_REG(0x4534, 0xffff, 0x6),
	SNBEP_CBO_EVENT_EXTRA_REG(0x0934, 0xffff, 0x4),
	SNBEP_CBO_EVENT_EXTRA_REG(0x4934, 0xffff, 0x6),
	SNBEP_CBO_EVENT_EXTRA_REG(0x4134, 0xffff, 0x6),
	SNBEP_CBO_EVENT_EXTRA_REG(0x0135, 0xffff, 0x8),
	SNBEP_CBO_EVENT_EXTRA_REG(0x0335, 0xffff, 0x8),
	SNBEP_CBO_EVENT_EXTRA_REG(0x4135, 0xffff, 0xa),
	SNBEP_CBO_EVENT_EXTRA_REG(0x4335, 0xffff, 0xa),
	SNBEP_CBO_EVENT_EXTRA_REG(0x4435, 0xffff, 0x2),
	SNBEP_CBO_EVENT_EXTRA_REG(0x4835, 0xffff, 0x2),
	SNBEP_CBO_EVENT_EXTRA_REG(0x4a35, 0xffff, 0x2),
	SNBEP_CBO_EVENT_EXTRA_REG(0x5035, 0xffff, 0x2),
	SNBEP_CBO_EVENT_EXTRA_REG(0x0136, 0xffff, 0x8),
	SNBEP_CBO_EVENT_EXTRA_REG(0x0336, 0xffff, 0x8),
	SNBEP_CBO_EVENT_EXTRA_REG(0x4136, 0xffff, 0xa),
	SNBEP_CBO_EVENT_EXTRA_REG(0x4336, 0xffff, 0xa),
	SNBEP_CBO_EVENT_EXTRA_REG(0x4436, 0xffff, 0x2),
	SNBEP_CBO_EVENT_EXTRA_REG(0x4836, 0xffff, 0x2),
	SNBEP_CBO_EVENT_EXTRA_REG(0x4a36, 0xffff, 0x2),
	SNBEP_CBO_EVENT_EXTRA_REG(0x4037, 0x40ff, 0x2),
	EVENT_EXTRA_END
पूर्ण;

अटल व्योम snbep_cbox_put_स्थिरraपूर्णांक(काष्ठा पूर्णांकel_uncore_box *box, काष्ठा perf_event *event)
अणु
	काष्ठा hw_perf_event_extra *reg1 = &event->hw.extra_reg;
	काष्ठा पूर्णांकel_uncore_extra_reg *er = &box->shared_regs[0];
	पूर्णांक i;

	अगर (uncore_box_is_fake(box))
		वापस;

	क्रम (i = 0; i < 5; i++) अणु
		अगर (reg1->alloc & (0x1 << i))
			atomic_sub(1 << (i * 6), &er->ref);
	पूर्ण
	reg1->alloc = 0;
पूर्ण

अटल काष्ठा event_स्थिरraपूर्णांक *
__snbep_cbox_get_स्थिरraपूर्णांक(काष्ठा पूर्णांकel_uncore_box *box, काष्ठा perf_event *event,
			    u64 (*cbox_filter_mask)(पूर्णांक fields))
अणु
	काष्ठा hw_perf_event_extra *reg1 = &event->hw.extra_reg;
	काष्ठा पूर्णांकel_uncore_extra_reg *er = &box->shared_regs[0];
	पूर्णांक i, alloc = 0;
	अचिन्हित दीर्घ flags;
	u64 mask;

	अगर (reg1->idx == EXTRA_REG_NONE)
		वापस शून्य;

	raw_spin_lock_irqsave(&er->lock, flags);
	क्रम (i = 0; i < 5; i++) अणु
		अगर (!(reg1->idx & (0x1 << i)))
			जारी;
		अगर (!uncore_box_is_fake(box) && (reg1->alloc & (0x1 << i)))
			जारी;

		mask = cbox_filter_mask(0x1 << i);
		अगर (!__BITS_VALUE(atomic_पढ़ो(&er->ref), i, 6) ||
		    !((reg1->config ^ er->config) & mask)) अणु
			atomic_add(1 << (i * 6), &er->ref);
			er->config &= ~mask;
			er->config |= reg1->config & mask;
			alloc |= (0x1 << i);
		पूर्ण अन्यथा अणु
			अवरोध;
		पूर्ण
	पूर्ण
	raw_spin_unlock_irqrestore(&er->lock, flags);
	अगर (i < 5)
		जाओ fail;

	अगर (!uncore_box_is_fake(box))
		reg1->alloc |= alloc;

	वापस शून्य;
fail:
	क्रम (; i >= 0; i--) अणु
		अगर (alloc & (0x1 << i))
			atomic_sub(1 << (i * 6), &er->ref);
	पूर्ण
	वापस &uncore_स्थिरraपूर्णांक_empty;
पूर्ण

अटल u64 snbep_cbox_filter_mask(पूर्णांक fields)
अणु
	u64 mask = 0;

	अगर (fields & 0x1)
		mask |= SNBEP_CB0_MSR_PMON_BOX_FILTER_TID;
	अगर (fields & 0x2)
		mask |= SNBEP_CB0_MSR_PMON_BOX_FILTER_NID;
	अगर (fields & 0x4)
		mask |= SNBEP_CB0_MSR_PMON_BOX_FILTER_STATE;
	अगर (fields & 0x8)
		mask |= SNBEP_CB0_MSR_PMON_BOX_FILTER_OPC;

	वापस mask;
पूर्ण

अटल काष्ठा event_स्थिरraपूर्णांक *
snbep_cbox_get_स्थिरraपूर्णांक(काष्ठा पूर्णांकel_uncore_box *box, काष्ठा perf_event *event)
अणु
	वापस __snbep_cbox_get_स्थिरraपूर्णांक(box, event, snbep_cbox_filter_mask);
पूर्ण

अटल पूर्णांक snbep_cbox_hw_config(काष्ठा पूर्णांकel_uncore_box *box, काष्ठा perf_event *event)
अणु
	काष्ठा hw_perf_event_extra *reg1 = &event->hw.extra_reg;
	काष्ठा extra_reg *er;
	पूर्णांक idx = 0;

	क्रम (er = snbep_uncore_cbox_extra_regs; er->msr; er++) अणु
		अगर (er->event != (event->hw.config & er->config_mask))
			जारी;
		idx |= er->idx;
	पूर्ण

	अगर (idx) अणु
		reg1->reg = SNBEP_C0_MSR_PMON_BOX_FILTER +
			SNBEP_CBO_MSR_OFFSET * box->pmu->pmu_idx;
		reg1->config = event->attr.config1 & snbep_cbox_filter_mask(idx);
		reg1->idx = idx;
	पूर्ण
	वापस 0;
पूर्ण

अटल काष्ठा पूर्णांकel_uncore_ops snbep_uncore_cbox_ops = अणु
	SNBEP_UNCORE_MSR_OPS_COMMON_INIT(),
	.hw_config		= snbep_cbox_hw_config,
	.get_स्थिरraपूर्णांक		= snbep_cbox_get_स्थिरraपूर्णांक,
	.put_स्थिरraपूर्णांक		= snbep_cbox_put_स्थिरraपूर्णांक,
पूर्ण;

अटल काष्ठा पूर्णांकel_uncore_type snbep_uncore_cbox = अणु
	.name			= "cbox",
	.num_counters		= 4,
	.num_boxes		= 8,
	.perf_ctr_bits		= 44,
	.event_ctl		= SNBEP_C0_MSR_PMON_CTL0,
	.perf_ctr		= SNBEP_C0_MSR_PMON_CTR0,
	.event_mask		= SNBEP_CBO_MSR_PMON_RAW_EVENT_MASK,
	.box_ctl		= SNBEP_C0_MSR_PMON_BOX_CTL,
	.msr_offset		= SNBEP_CBO_MSR_OFFSET,
	.num_shared_regs	= 1,
	.स्थिरraपूर्णांकs		= snbep_uncore_cbox_स्थिरraपूर्णांकs,
	.ops			= &snbep_uncore_cbox_ops,
	.क्रमmat_group		= &snbep_uncore_cbox_क्रमmat_group,
पूर्ण;

अटल u64 snbep_pcu_alter_er(काष्ठा perf_event *event, पूर्णांक new_idx, bool modअगरy)
अणु
	काष्ठा hw_perf_event *hwc = &event->hw;
	काष्ठा hw_perf_event_extra *reg1 = &hwc->extra_reg;
	u64 config = reg1->config;

	अगर (new_idx > reg1->idx)
		config <<= 8 * (new_idx - reg1->idx);
	अन्यथा
		config >>= 8 * (reg1->idx - new_idx);

	अगर (modअगरy) अणु
		hwc->config += new_idx - reg1->idx;
		reg1->config = config;
		reg1->idx = new_idx;
	पूर्ण
	वापस config;
पूर्ण

अटल काष्ठा event_स्थिरraपूर्णांक *
snbep_pcu_get_स्थिरraपूर्णांक(काष्ठा पूर्णांकel_uncore_box *box, काष्ठा perf_event *event)
अणु
	काष्ठा hw_perf_event_extra *reg1 = &event->hw.extra_reg;
	काष्ठा पूर्णांकel_uncore_extra_reg *er = &box->shared_regs[0];
	अचिन्हित दीर्घ flags;
	पूर्णांक idx = reg1->idx;
	u64 mask, config1 = reg1->config;
	bool ok = false;

	अगर (reg1->idx == EXTRA_REG_NONE ||
	    (!uncore_box_is_fake(box) && reg1->alloc))
		वापस शून्य;
again:
	mask = 0xffULL << (idx * 8);
	raw_spin_lock_irqsave(&er->lock, flags);
	अगर (!__BITS_VALUE(atomic_पढ़ो(&er->ref), idx, 8) ||
	    !((config1 ^ er->config) & mask)) अणु
		atomic_add(1 << (idx * 8), &er->ref);
		er->config &= ~mask;
		er->config |= config1 & mask;
		ok = true;
	पूर्ण
	raw_spin_unlock_irqrestore(&er->lock, flags);

	अगर (!ok) अणु
		idx = (idx + 1) % 4;
		अगर (idx != reg1->idx) अणु
			config1 = snbep_pcu_alter_er(event, idx, false);
			जाओ again;
		पूर्ण
		वापस &uncore_स्थिरraपूर्णांक_empty;
	पूर्ण

	अगर (!uncore_box_is_fake(box)) अणु
		अगर (idx != reg1->idx)
			snbep_pcu_alter_er(event, idx, true);
		reg1->alloc = 1;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल व्योम snbep_pcu_put_स्थिरraपूर्णांक(काष्ठा पूर्णांकel_uncore_box *box, काष्ठा perf_event *event)
अणु
	काष्ठा hw_perf_event_extra *reg1 = &event->hw.extra_reg;
	काष्ठा पूर्णांकel_uncore_extra_reg *er = &box->shared_regs[0];

	अगर (uncore_box_is_fake(box) || !reg1->alloc)
		वापस;

	atomic_sub(1 << (reg1->idx * 8), &er->ref);
	reg1->alloc = 0;
पूर्ण

अटल पूर्णांक snbep_pcu_hw_config(काष्ठा पूर्णांकel_uncore_box *box, काष्ठा perf_event *event)
अणु
	काष्ठा hw_perf_event *hwc = &event->hw;
	काष्ठा hw_perf_event_extra *reg1 = &hwc->extra_reg;
	पूर्णांक ev_sel = hwc->config & SNBEP_PMON_CTL_EV_SEL_MASK;

	अगर (ev_sel >= 0xb && ev_sel <= 0xe) अणु
		reg1->reg = SNBEP_PCU_MSR_PMON_BOX_FILTER;
		reg1->idx = ev_sel - 0xb;
		reg1->config = event->attr.config1 & (0xff << (reg1->idx * 8));
	पूर्ण
	वापस 0;
पूर्ण

अटल काष्ठा पूर्णांकel_uncore_ops snbep_uncore_pcu_ops = अणु
	SNBEP_UNCORE_MSR_OPS_COMMON_INIT(),
	.hw_config		= snbep_pcu_hw_config,
	.get_स्थिरraपूर्णांक		= snbep_pcu_get_स्थिरraपूर्णांक,
	.put_स्थिरraपूर्णांक		= snbep_pcu_put_स्थिरraपूर्णांक,
पूर्ण;

अटल काष्ठा पूर्णांकel_uncore_type snbep_uncore_pcu = अणु
	.name			= "pcu",
	.num_counters		= 4,
	.num_boxes		= 1,
	.perf_ctr_bits		= 48,
	.perf_ctr		= SNBEP_PCU_MSR_PMON_CTR0,
	.event_ctl		= SNBEP_PCU_MSR_PMON_CTL0,
	.event_mask		= SNBEP_PCU_MSR_PMON_RAW_EVENT_MASK,
	.box_ctl		= SNBEP_PCU_MSR_PMON_BOX_CTL,
	.num_shared_regs	= 1,
	.ops			= &snbep_uncore_pcu_ops,
	.क्रमmat_group		= &snbep_uncore_pcu_क्रमmat_group,
पूर्ण;

अटल काष्ठा पूर्णांकel_uncore_type *snbep_msr_uncores[] = अणु
	&snbep_uncore_ubox,
	&snbep_uncore_cbox,
	&snbep_uncore_pcu,
	शून्य,
पूर्ण;

व्योम snbep_uncore_cpu_init(व्योम)
अणु
	अगर (snbep_uncore_cbox.num_boxes > boot_cpu_data.x86_max_cores)
		snbep_uncore_cbox.num_boxes = boot_cpu_data.x86_max_cores;
	uncore_msr_uncores = snbep_msr_uncores;
पूर्ण

क्रमागत अणु
	SNBEP_PCI_QPI_PORT0_FILTER,
	SNBEP_PCI_QPI_PORT1_FILTER,
	BDX_PCI_QPI_PORT2_FILTER,
पूर्ण;

अटल पूर्णांक snbep_qpi_hw_config(काष्ठा पूर्णांकel_uncore_box *box, काष्ठा perf_event *event)
अणु
	काष्ठा hw_perf_event *hwc = &event->hw;
	काष्ठा hw_perf_event_extra *reg1 = &hwc->extra_reg;
	काष्ठा hw_perf_event_extra *reg2 = &hwc->branch_reg;

	अगर ((hwc->config & SNBEP_PMON_CTL_EV_SEL_MASK) == 0x38) अणु
		reg1->idx = 0;
		reg1->reg = SNBEP_Q_Py_PCI_PMON_PKT_MATCH0;
		reg1->config = event->attr.config1;
		reg2->reg = SNBEP_Q_Py_PCI_PMON_PKT_MASK0;
		reg2->config = event->attr.config2;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम snbep_qpi_enable_event(काष्ठा पूर्णांकel_uncore_box *box, काष्ठा perf_event *event)
अणु
	काष्ठा pci_dev *pdev = box->pci_dev;
	काष्ठा hw_perf_event *hwc = &event->hw;
	काष्ठा hw_perf_event_extra *reg1 = &hwc->extra_reg;
	काष्ठा hw_perf_event_extra *reg2 = &hwc->branch_reg;

	अगर (reg1->idx != EXTRA_REG_NONE) अणु
		पूर्णांक idx = box->pmu->pmu_idx + SNBEP_PCI_QPI_PORT0_FILTER;
		पूर्णांक die = box->dieid;
		काष्ठा pci_dev *filter_pdev = uncore_extra_pci_dev[die].dev[idx];

		अगर (filter_pdev) अणु
			pci_ग_लिखो_config_dword(filter_pdev, reg1->reg,
						(u32)reg1->config);
			pci_ग_लिखो_config_dword(filter_pdev, reg1->reg + 4,
						(u32)(reg1->config >> 32));
			pci_ग_लिखो_config_dword(filter_pdev, reg2->reg,
						(u32)reg2->config);
			pci_ग_लिखो_config_dword(filter_pdev, reg2->reg + 4,
						(u32)(reg2->config >> 32));
		पूर्ण
	पूर्ण

	pci_ग_लिखो_config_dword(pdev, hwc->config_base, hwc->config | SNBEP_PMON_CTL_EN);
पूर्ण

अटल काष्ठा पूर्णांकel_uncore_ops snbep_uncore_qpi_ops = अणु
	SNBEP_UNCORE_PCI_OPS_COMMON_INIT(),
	.enable_event		= snbep_qpi_enable_event,
	.hw_config		= snbep_qpi_hw_config,
	.get_स्थिरraपूर्णांक		= uncore_get_स्थिरraपूर्णांक,
	.put_स्थिरraपूर्णांक		= uncore_put_स्थिरraपूर्णांक,
पूर्ण;

#घोषणा SNBEP_UNCORE_PCI_COMMON_INIT()				\
	.perf_ctr	= SNBEP_PCI_PMON_CTR0,			\
	.event_ctl	= SNBEP_PCI_PMON_CTL0,			\
	.event_mask	= SNBEP_PMON_RAW_EVENT_MASK,		\
	.box_ctl	= SNBEP_PCI_PMON_BOX_CTL,		\
	.ops		= &snbep_uncore_pci_ops,		\
	.क्रमmat_group	= &snbep_uncore_क्रमmat_group

अटल काष्ठा पूर्णांकel_uncore_type snbep_uncore_ha = अणु
	.name		= "ha",
	.num_counters   = 4,
	.num_boxes	= 1,
	.perf_ctr_bits	= 48,
	SNBEP_UNCORE_PCI_COMMON_INIT(),
पूर्ण;

अटल काष्ठा पूर्णांकel_uncore_type snbep_uncore_imc = अणु
	.name		= "imc",
	.num_counters   = 4,
	.num_boxes	= 4,
	.perf_ctr_bits	= 48,
	.fixed_ctr_bits	= 48,
	.fixed_ctr	= SNBEP_MC_CHy_PCI_PMON_FIXED_CTR,
	.fixed_ctl	= SNBEP_MC_CHy_PCI_PMON_FIXED_CTL,
	.event_descs	= snbep_uncore_imc_events,
	SNBEP_UNCORE_PCI_COMMON_INIT(),
पूर्ण;

अटल काष्ठा पूर्णांकel_uncore_type snbep_uncore_qpi = अणु
	.name			= "qpi",
	.num_counters		= 4,
	.num_boxes		= 2,
	.perf_ctr_bits		= 48,
	.perf_ctr		= SNBEP_PCI_PMON_CTR0,
	.event_ctl		= SNBEP_PCI_PMON_CTL0,
	.event_mask		= SNBEP_QPI_PCI_PMON_RAW_EVENT_MASK,
	.box_ctl		= SNBEP_PCI_PMON_BOX_CTL,
	.num_shared_regs	= 1,
	.ops			= &snbep_uncore_qpi_ops,
	.event_descs		= snbep_uncore_qpi_events,
	.क्रमmat_group		= &snbep_uncore_qpi_क्रमmat_group,
पूर्ण;


अटल काष्ठा पूर्णांकel_uncore_type snbep_uncore_r2pcie = अणु
	.name		= "r2pcie",
	.num_counters   = 4,
	.num_boxes	= 1,
	.perf_ctr_bits	= 44,
	.स्थिरraपूर्णांकs	= snbep_uncore_r2pcie_स्थिरraपूर्णांकs,
	SNBEP_UNCORE_PCI_COMMON_INIT(),
पूर्ण;

अटल काष्ठा पूर्णांकel_uncore_type snbep_uncore_r3qpi = अणु
	.name		= "r3qpi",
	.num_counters   = 3,
	.num_boxes	= 2,
	.perf_ctr_bits	= 44,
	.स्थिरraपूर्णांकs	= snbep_uncore_r3qpi_स्थिरraपूर्णांकs,
	SNBEP_UNCORE_PCI_COMMON_INIT(),
पूर्ण;

क्रमागत अणु
	SNBEP_PCI_UNCORE_HA,
	SNBEP_PCI_UNCORE_IMC,
	SNBEP_PCI_UNCORE_QPI,
	SNBEP_PCI_UNCORE_R2PCIE,
	SNBEP_PCI_UNCORE_R3QPI,
पूर्ण;

अटल काष्ठा पूर्णांकel_uncore_type *snbep_pci_uncores[] = अणु
	[SNBEP_PCI_UNCORE_HA]		= &snbep_uncore_ha,
	[SNBEP_PCI_UNCORE_IMC]		= &snbep_uncore_imc,
	[SNBEP_PCI_UNCORE_QPI]		= &snbep_uncore_qpi,
	[SNBEP_PCI_UNCORE_R2PCIE]	= &snbep_uncore_r2pcie,
	[SNBEP_PCI_UNCORE_R3QPI]	= &snbep_uncore_r3qpi,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा pci_device_id snbep_uncore_pci_ids[] = अणु
	अणु /* Home Agent */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_UNC_HA),
		.driver_data = UNCORE_PCI_DEV_DATA(SNBEP_PCI_UNCORE_HA, 0),
	पूर्ण,
	अणु /* MC Channel 0 */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_UNC_IMC0),
		.driver_data = UNCORE_PCI_DEV_DATA(SNBEP_PCI_UNCORE_IMC, 0),
	पूर्ण,
	अणु /* MC Channel 1 */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_UNC_IMC1),
		.driver_data = UNCORE_PCI_DEV_DATA(SNBEP_PCI_UNCORE_IMC, 1),
	पूर्ण,
	अणु /* MC Channel 2 */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_UNC_IMC2),
		.driver_data = UNCORE_PCI_DEV_DATA(SNBEP_PCI_UNCORE_IMC, 2),
	पूर्ण,
	अणु /* MC Channel 3 */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_UNC_IMC3),
		.driver_data = UNCORE_PCI_DEV_DATA(SNBEP_PCI_UNCORE_IMC, 3),
	पूर्ण,
	अणु /* QPI Port 0 */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_UNC_QPI0),
		.driver_data = UNCORE_PCI_DEV_DATA(SNBEP_PCI_UNCORE_QPI, 0),
	पूर्ण,
	अणु /* QPI Port 1 */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_UNC_QPI1),
		.driver_data = UNCORE_PCI_DEV_DATA(SNBEP_PCI_UNCORE_QPI, 1),
	पूर्ण,
	अणु /* R2PCIe */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_UNC_R2PCIE),
		.driver_data = UNCORE_PCI_DEV_DATA(SNBEP_PCI_UNCORE_R2PCIE, 0),
	पूर्ण,
	अणु /* R3QPI Link 0 */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_UNC_R3QPI0),
		.driver_data = UNCORE_PCI_DEV_DATA(SNBEP_PCI_UNCORE_R3QPI, 0),
	पूर्ण,
	अणु /* R3QPI Link 1 */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_UNC_R3QPI1),
		.driver_data = UNCORE_PCI_DEV_DATA(SNBEP_PCI_UNCORE_R3QPI, 1),
	पूर्ण,
	अणु /* QPI Port 0 filter  */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, 0x3c86),
		.driver_data = UNCORE_PCI_DEV_DATA(UNCORE_EXTRA_PCI_DEV,
						   SNBEP_PCI_QPI_PORT0_FILTER),
	पूर्ण,
	अणु /* QPI Port 0 filter  */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, 0x3c96),
		.driver_data = UNCORE_PCI_DEV_DATA(UNCORE_EXTRA_PCI_DEV,
						   SNBEP_PCI_QPI_PORT1_FILTER),
	पूर्ण,
	अणु /* end: all zeroes */ पूर्ण
पूर्ण;

अटल काष्ठा pci_driver snbep_uncore_pci_driver = अणु
	.name		= "snbep_uncore",
	.id_table	= snbep_uncore_pci_ids,
पूर्ण;

#घोषणा NODE_ID_MASK	0x7

/*
 * build pci bus to socket mapping
 */
अटल पूर्णांक snbep_pci2phy_map_init(पूर्णांक devid, पूर्णांक nodeid_loc, पूर्णांक idmap_loc, bool reverse)
अणु
	काष्ठा pci_dev *ubox_dev = शून्य;
	पूर्णांक i, bus, nodeid, segment, die_id;
	काष्ठा pci2phy_map *map;
	पूर्णांक err = 0;
	u32 config = 0;

	जबतक (1) अणु
		/* find the UBOX device */
		ubox_dev = pci_get_device(PCI_VENDOR_ID_INTEL, devid, ubox_dev);
		अगर (!ubox_dev)
			अवरोध;
		bus = ubox_dev->bus->number;
		/*
		 * The nodeid and idmap रेजिस्टरs only contain enough
		 * inक्रमmation to handle 8 nodes.  On प्रणालीs with more
		 * than 8 nodes, we need to rely on NUMA inक्रमmation,
		 * filled in from BIOS supplied inक्रमmation, to determine
		 * the topology.
		 */
		अगर (nr_node_ids <= 8) अणु
			/* get the Node ID of the local रेजिस्टर */
			err = pci_पढ़ो_config_dword(ubox_dev, nodeid_loc, &config);
			अगर (err)
				अवरोध;
			nodeid = config & NODE_ID_MASK;
			/* get the Node ID mapping */
			err = pci_पढ़ो_config_dword(ubox_dev, idmap_loc, &config);
			अगर (err)
				अवरोध;

			segment = pci_करोमुख्य_nr(ubox_dev->bus);
			raw_spin_lock(&pci2phy_map_lock);
			map = __find_pci2phy_map(segment);
			अगर (!map) अणु
				raw_spin_unlock(&pci2phy_map_lock);
				err = -ENOMEM;
				अवरोध;
			पूर्ण

			/*
			 * every three bits in the Node ID mapping रेजिस्टर maps
			 * to a particular node.
			 */
			क्रम (i = 0; i < 8; i++) अणु
				अगर (nodeid == ((config >> (3 * i)) & 0x7)) अणु
					अगर (topology_max_die_per_package() > 1)
						die_id = i;
					अन्यथा
						die_id = topology_phys_to_logical_pkg(i);
					अगर (die_id < 0)
						die_id = -ENODEV;
					map->pbus_to_dieid[bus] = die_id;
					अवरोध;
				पूर्ण
			पूर्ण
			raw_spin_unlock(&pci2phy_map_lock);
		पूर्ण अन्यथा अणु
			पूर्णांक node = pcibus_to_node(ubox_dev->bus);
			पूर्णांक cpu;

			segment = pci_करोमुख्य_nr(ubox_dev->bus);
			raw_spin_lock(&pci2phy_map_lock);
			map = __find_pci2phy_map(segment);
			अगर (!map) अणु
				raw_spin_unlock(&pci2phy_map_lock);
				err = -ENOMEM;
				अवरोध;
			पूर्ण

			die_id = -1;
			क्रम_each_cpu(cpu, cpumask_of_pcibus(ubox_dev->bus)) अणु
				काष्ठा cpuinfo_x86 *c = &cpu_data(cpu);

				अगर (c->initialized && cpu_to_node(cpu) == node) अणु
					map->pbus_to_dieid[bus] = die_id = c->logical_die_id;
					अवरोध;
				पूर्ण
			पूर्ण
			raw_spin_unlock(&pci2phy_map_lock);

			अगर (WARN_ON_ONCE(die_id == -1)) अणु
				err = -EINVAL;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (!err) अणु
		/*
		 * For PCI bus with no UBOX device, find the next bus
		 * that has UBOX device and use its mapping.
		 */
		raw_spin_lock(&pci2phy_map_lock);
		list_क्रम_each_entry(map, &pci2phy_map_head, list) अणु
			i = -1;
			अगर (reverse) अणु
				क्रम (bus = 255; bus >= 0; bus--) अणु
					अगर (map->pbus_to_dieid[bus] != -1)
						i = map->pbus_to_dieid[bus];
					अन्यथा
						map->pbus_to_dieid[bus] = i;
				पूर्ण
			पूर्ण अन्यथा अणु
				क्रम (bus = 0; bus <= 255; bus++) अणु
					अगर (map->pbus_to_dieid[bus] != -1)
						i = map->pbus_to_dieid[bus];
					अन्यथा
						map->pbus_to_dieid[bus] = i;
				पूर्ण
			पूर्ण
		पूर्ण
		raw_spin_unlock(&pci2phy_map_lock);
	पूर्ण

	pci_dev_put(ubox_dev);

	वापस err ? pcibios_err_to_त्रुटि_सं(err) : 0;
पूर्ण

पूर्णांक snbep_uncore_pci_init(व्योम)
अणु
	पूर्णांक ret = snbep_pci2phy_map_init(0x3ce0, SNBEP_CPUNODEID, SNBEP_GIDNIDMAP, true);
	अगर (ret)
		वापस ret;
	uncore_pci_uncores = snbep_pci_uncores;
	uncore_pci_driver = &snbep_uncore_pci_driver;
	वापस 0;
पूर्ण
/* end of Sandy Bridge-EP uncore support */

/* IvyTown uncore support */
अटल व्योम ivbep_uncore_msr_init_box(काष्ठा पूर्णांकel_uncore_box *box)
अणु
	अचिन्हित msr = uncore_msr_box_ctl(box);
	अगर (msr)
		wrmsrl(msr, IVBEP_PMON_BOX_CTL_INT);
पूर्ण

अटल व्योम ivbep_uncore_pci_init_box(काष्ठा पूर्णांकel_uncore_box *box)
अणु
	काष्ठा pci_dev *pdev = box->pci_dev;

	pci_ग_लिखो_config_dword(pdev, SNBEP_PCI_PMON_BOX_CTL, IVBEP_PMON_BOX_CTL_INT);
पूर्ण

#घोषणा IVBEP_UNCORE_MSR_OPS_COMMON_INIT()			\
	.init_box	= ivbep_uncore_msr_init_box,		\
	.disable_box	= snbep_uncore_msr_disable_box,		\
	.enable_box	= snbep_uncore_msr_enable_box,		\
	.disable_event	= snbep_uncore_msr_disable_event,	\
	.enable_event	= snbep_uncore_msr_enable_event,	\
	.पढ़ो_counter	= uncore_msr_पढ़ो_counter

अटल काष्ठा पूर्णांकel_uncore_ops ivbep_uncore_msr_ops = अणु
	IVBEP_UNCORE_MSR_OPS_COMMON_INIT(),
पूर्ण;

अटल काष्ठा पूर्णांकel_uncore_ops ivbep_uncore_pci_ops = अणु
	.init_box	= ivbep_uncore_pci_init_box,
	.disable_box	= snbep_uncore_pci_disable_box,
	.enable_box	= snbep_uncore_pci_enable_box,
	.disable_event	= snbep_uncore_pci_disable_event,
	.enable_event	= snbep_uncore_pci_enable_event,
	.पढ़ो_counter	= snbep_uncore_pci_पढ़ो_counter,
पूर्ण;

#घोषणा IVBEP_UNCORE_PCI_COMMON_INIT()				\
	.perf_ctr	= SNBEP_PCI_PMON_CTR0,			\
	.event_ctl	= SNBEP_PCI_PMON_CTL0,			\
	.event_mask	= IVBEP_PMON_RAW_EVENT_MASK,		\
	.box_ctl	= SNBEP_PCI_PMON_BOX_CTL,		\
	.ops		= &ivbep_uncore_pci_ops,			\
	.क्रमmat_group	= &ivbep_uncore_क्रमmat_group

अटल काष्ठा attribute *ivbep_uncore_क्रमmats_attr[] = अणु
	&क्रमmat_attr_event.attr,
	&क्रमmat_attr_umask.attr,
	&क्रमmat_attr_edge.attr,
	&क्रमmat_attr_inv.attr,
	&क्रमmat_attr_thresh8.attr,
	शून्य,
पूर्ण;

अटल काष्ठा attribute *ivbep_uncore_ubox_क्रमmats_attr[] = अणु
	&क्रमmat_attr_event.attr,
	&क्रमmat_attr_umask.attr,
	&क्रमmat_attr_edge.attr,
	&क्रमmat_attr_inv.attr,
	&क्रमmat_attr_thresh5.attr,
	शून्य,
पूर्ण;

अटल काष्ठा attribute *ivbep_uncore_cbox_क्रमmats_attr[] = अणु
	&क्रमmat_attr_event.attr,
	&क्रमmat_attr_umask.attr,
	&क्रमmat_attr_edge.attr,
	&क्रमmat_attr_tid_en.attr,
	&क्रमmat_attr_thresh8.attr,
	&क्रमmat_attr_filter_tid.attr,
	&क्रमmat_attr_filter_link.attr,
	&क्रमmat_attr_filter_state2.attr,
	&क्रमmat_attr_filter_nid2.attr,
	&क्रमmat_attr_filter_opc2.attr,
	&क्रमmat_attr_filter_nc.attr,
	&क्रमmat_attr_filter_c6.attr,
	&क्रमmat_attr_filter_isoc.attr,
	शून्य,
पूर्ण;

अटल काष्ठा attribute *ivbep_uncore_pcu_क्रमmats_attr[] = अणु
	&क्रमmat_attr_event.attr,
	&क्रमmat_attr_occ_sel.attr,
	&क्रमmat_attr_edge.attr,
	&क्रमmat_attr_thresh5.attr,
	&क्रमmat_attr_occ_invert.attr,
	&क्रमmat_attr_occ_edge.attr,
	&क्रमmat_attr_filter_band0.attr,
	&क्रमmat_attr_filter_band1.attr,
	&क्रमmat_attr_filter_band2.attr,
	&क्रमmat_attr_filter_band3.attr,
	शून्य,
पूर्ण;

अटल काष्ठा attribute *ivbep_uncore_qpi_क्रमmats_attr[] = अणु
	&क्रमmat_attr_event_ext.attr,
	&क्रमmat_attr_umask.attr,
	&क्रमmat_attr_edge.attr,
	&क्रमmat_attr_thresh8.attr,
	&क्रमmat_attr_match_rds.attr,
	&क्रमmat_attr_match_rnid30.attr,
	&क्रमmat_attr_match_rnid4.attr,
	&क्रमmat_attr_match_dnid.attr,
	&क्रमmat_attr_match_mc.attr,
	&क्रमmat_attr_match_opc.attr,
	&क्रमmat_attr_match_vnw.attr,
	&क्रमmat_attr_match0.attr,
	&क्रमmat_attr_match1.attr,
	&क्रमmat_attr_mask_rds.attr,
	&क्रमmat_attr_mask_rnid30.attr,
	&क्रमmat_attr_mask_rnid4.attr,
	&क्रमmat_attr_mask_dnid.attr,
	&क्रमmat_attr_mask_mc.attr,
	&क्रमmat_attr_mask_opc.attr,
	&क्रमmat_attr_mask_vnw.attr,
	&क्रमmat_attr_mask0.attr,
	&क्रमmat_attr_mask1.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group ivbep_uncore_क्रमmat_group = अणु
	.name = "format",
	.attrs = ivbep_uncore_क्रमmats_attr,
पूर्ण;

अटल स्थिर काष्ठा attribute_group ivbep_uncore_ubox_क्रमmat_group = अणु
	.name = "format",
	.attrs = ivbep_uncore_ubox_क्रमmats_attr,
पूर्ण;

अटल स्थिर काष्ठा attribute_group ivbep_uncore_cbox_क्रमmat_group = अणु
	.name = "format",
	.attrs = ivbep_uncore_cbox_क्रमmats_attr,
पूर्ण;

अटल स्थिर काष्ठा attribute_group ivbep_uncore_pcu_क्रमmat_group = अणु
	.name = "format",
	.attrs = ivbep_uncore_pcu_क्रमmats_attr,
पूर्ण;

अटल स्थिर काष्ठा attribute_group ivbep_uncore_qpi_क्रमmat_group = अणु
	.name = "format",
	.attrs = ivbep_uncore_qpi_क्रमmats_attr,
पूर्ण;

अटल काष्ठा पूर्णांकel_uncore_type ivbep_uncore_ubox = अणु
	.name		= "ubox",
	.num_counters   = 2,
	.num_boxes	= 1,
	.perf_ctr_bits	= 44,
	.fixed_ctr_bits	= 48,
	.perf_ctr	= SNBEP_U_MSR_PMON_CTR0,
	.event_ctl	= SNBEP_U_MSR_PMON_CTL0,
	.event_mask	= IVBEP_U_MSR_PMON_RAW_EVENT_MASK,
	.fixed_ctr	= SNBEP_U_MSR_PMON_UCLK_FIXED_CTR,
	.fixed_ctl	= SNBEP_U_MSR_PMON_UCLK_FIXED_CTL,
	.ops		= &ivbep_uncore_msr_ops,
	.क्रमmat_group	= &ivbep_uncore_ubox_क्रमmat_group,
पूर्ण;

अटल काष्ठा extra_reg ivbep_uncore_cbox_extra_regs[] = अणु
	SNBEP_CBO_EVENT_EXTRA_REG(SNBEP_CBO_PMON_CTL_TID_EN,
				  SNBEP_CBO_PMON_CTL_TID_EN, 0x1),
	SNBEP_CBO_EVENT_EXTRA_REG(0x1031, 0x10ff, 0x2),
	SNBEP_CBO_EVENT_EXTRA_REG(0x1134, 0xffff, 0x4),
	SNBEP_CBO_EVENT_EXTRA_REG(0x4134, 0xffff, 0xc),
	SNBEP_CBO_EVENT_EXTRA_REG(0x5134, 0xffff, 0xc),
	SNBEP_CBO_EVENT_EXTRA_REG(0x0334, 0xffff, 0x4),
	SNBEP_CBO_EVENT_EXTRA_REG(0x4334, 0xffff, 0xc),
	SNBEP_CBO_EVENT_EXTRA_REG(0x0534, 0xffff, 0x4),
	SNBEP_CBO_EVENT_EXTRA_REG(0x4534, 0xffff, 0xc),
	SNBEP_CBO_EVENT_EXTRA_REG(0x0934, 0xffff, 0x4),
	SNBEP_CBO_EVENT_EXTRA_REG(0x4934, 0xffff, 0xc),
	SNBEP_CBO_EVENT_EXTRA_REG(0x0135, 0xffff, 0x10),
	SNBEP_CBO_EVENT_EXTRA_REG(0x0335, 0xffff, 0x10),
	SNBEP_CBO_EVENT_EXTRA_REG(0x2135, 0xffff, 0x10),
	SNBEP_CBO_EVENT_EXTRA_REG(0x2335, 0xffff, 0x10),
	SNBEP_CBO_EVENT_EXTRA_REG(0x4135, 0xffff, 0x18),
	SNBEP_CBO_EVENT_EXTRA_REG(0x4335, 0xffff, 0x18),
	SNBEP_CBO_EVENT_EXTRA_REG(0x4435, 0xffff, 0x8),
	SNBEP_CBO_EVENT_EXTRA_REG(0x4835, 0xffff, 0x8),
	SNBEP_CBO_EVENT_EXTRA_REG(0x4a35, 0xffff, 0x8),
	SNBEP_CBO_EVENT_EXTRA_REG(0x5035, 0xffff, 0x8),
	SNBEP_CBO_EVENT_EXTRA_REG(0x8135, 0xffff, 0x10),
	SNBEP_CBO_EVENT_EXTRA_REG(0x8335, 0xffff, 0x10),
	SNBEP_CBO_EVENT_EXTRA_REG(0x0136, 0xffff, 0x10),
	SNBEP_CBO_EVENT_EXTRA_REG(0x0336, 0xffff, 0x10),
	SNBEP_CBO_EVENT_EXTRA_REG(0x2136, 0xffff, 0x10),
	SNBEP_CBO_EVENT_EXTRA_REG(0x2336, 0xffff, 0x10),
	SNBEP_CBO_EVENT_EXTRA_REG(0x4136, 0xffff, 0x18),
	SNBEP_CBO_EVENT_EXTRA_REG(0x4336, 0xffff, 0x18),
	SNBEP_CBO_EVENT_EXTRA_REG(0x4436, 0xffff, 0x8),
	SNBEP_CBO_EVENT_EXTRA_REG(0x4836, 0xffff, 0x8),
	SNBEP_CBO_EVENT_EXTRA_REG(0x4a36, 0xffff, 0x8),
	SNBEP_CBO_EVENT_EXTRA_REG(0x5036, 0xffff, 0x8),
	SNBEP_CBO_EVENT_EXTRA_REG(0x8136, 0xffff, 0x10),
	SNBEP_CBO_EVENT_EXTRA_REG(0x8336, 0xffff, 0x10),
	SNBEP_CBO_EVENT_EXTRA_REG(0x4037, 0x40ff, 0x8),
	EVENT_EXTRA_END
पूर्ण;

अटल u64 ivbep_cbox_filter_mask(पूर्णांक fields)
अणु
	u64 mask = 0;

	अगर (fields & 0x1)
		mask |= IVBEP_CB0_MSR_PMON_BOX_FILTER_TID;
	अगर (fields & 0x2)
		mask |= IVBEP_CB0_MSR_PMON_BOX_FILTER_LINK;
	अगर (fields & 0x4)
		mask |= IVBEP_CB0_MSR_PMON_BOX_FILTER_STATE;
	अगर (fields & 0x8)
		mask |= IVBEP_CB0_MSR_PMON_BOX_FILTER_NID;
	अगर (fields & 0x10) अणु
		mask |= IVBEP_CB0_MSR_PMON_BOX_FILTER_OPC;
		mask |= IVBEP_CB0_MSR_PMON_BOX_FILTER_NC;
		mask |= IVBEP_CB0_MSR_PMON_BOX_FILTER_C6;
		mask |= IVBEP_CB0_MSR_PMON_BOX_FILTER_ISOC;
	पूर्ण

	वापस mask;
पूर्ण

अटल काष्ठा event_स्थिरraपूर्णांक *
ivbep_cbox_get_स्थिरraपूर्णांक(काष्ठा पूर्णांकel_uncore_box *box, काष्ठा perf_event *event)
अणु
	वापस __snbep_cbox_get_स्थिरraपूर्णांक(box, event, ivbep_cbox_filter_mask);
पूर्ण

अटल पूर्णांक ivbep_cbox_hw_config(काष्ठा पूर्णांकel_uncore_box *box, काष्ठा perf_event *event)
अणु
	काष्ठा hw_perf_event_extra *reg1 = &event->hw.extra_reg;
	काष्ठा extra_reg *er;
	पूर्णांक idx = 0;

	क्रम (er = ivbep_uncore_cbox_extra_regs; er->msr; er++) अणु
		अगर (er->event != (event->hw.config & er->config_mask))
			जारी;
		idx |= er->idx;
	पूर्ण

	अगर (idx) अणु
		reg1->reg = SNBEP_C0_MSR_PMON_BOX_FILTER +
			SNBEP_CBO_MSR_OFFSET * box->pmu->pmu_idx;
		reg1->config = event->attr.config1 & ivbep_cbox_filter_mask(idx);
		reg1->idx = idx;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम ivbep_cbox_enable_event(काष्ठा पूर्णांकel_uncore_box *box, काष्ठा perf_event *event)
अणु
	काष्ठा hw_perf_event *hwc = &event->hw;
	काष्ठा hw_perf_event_extra *reg1 = &hwc->extra_reg;

	अगर (reg1->idx != EXTRA_REG_NONE) अणु
		u64 filter = uncore_shared_reg_config(box, 0);
		wrmsrl(reg1->reg, filter & 0xffffffff);
		wrmsrl(reg1->reg + 6, filter >> 32);
	पूर्ण

	wrmsrl(hwc->config_base, hwc->config | SNBEP_PMON_CTL_EN);
पूर्ण

अटल काष्ठा पूर्णांकel_uncore_ops ivbep_uncore_cbox_ops = अणु
	.init_box		= ivbep_uncore_msr_init_box,
	.disable_box		= snbep_uncore_msr_disable_box,
	.enable_box		= snbep_uncore_msr_enable_box,
	.disable_event		= snbep_uncore_msr_disable_event,
	.enable_event		= ivbep_cbox_enable_event,
	.पढ़ो_counter		= uncore_msr_पढ़ो_counter,
	.hw_config		= ivbep_cbox_hw_config,
	.get_स्थिरraपूर्णांक		= ivbep_cbox_get_स्थिरraपूर्णांक,
	.put_स्थिरraपूर्णांक		= snbep_cbox_put_स्थिरraपूर्णांक,
पूर्ण;

अटल काष्ठा पूर्णांकel_uncore_type ivbep_uncore_cbox = अणु
	.name			= "cbox",
	.num_counters		= 4,
	.num_boxes		= 15,
	.perf_ctr_bits		= 44,
	.event_ctl		= SNBEP_C0_MSR_PMON_CTL0,
	.perf_ctr		= SNBEP_C0_MSR_PMON_CTR0,
	.event_mask		= IVBEP_CBO_MSR_PMON_RAW_EVENT_MASK,
	.box_ctl		= SNBEP_C0_MSR_PMON_BOX_CTL,
	.msr_offset		= SNBEP_CBO_MSR_OFFSET,
	.num_shared_regs	= 1,
	.स्थिरraपूर्णांकs		= snbep_uncore_cbox_स्थिरraपूर्णांकs,
	.ops			= &ivbep_uncore_cbox_ops,
	.क्रमmat_group		= &ivbep_uncore_cbox_क्रमmat_group,
पूर्ण;

अटल काष्ठा पूर्णांकel_uncore_ops ivbep_uncore_pcu_ops = अणु
	IVBEP_UNCORE_MSR_OPS_COMMON_INIT(),
	.hw_config		= snbep_pcu_hw_config,
	.get_स्थिरraपूर्णांक		= snbep_pcu_get_स्थिरraपूर्णांक,
	.put_स्थिरraपूर्णांक		= snbep_pcu_put_स्थिरraपूर्णांक,
पूर्ण;

अटल काष्ठा पूर्णांकel_uncore_type ivbep_uncore_pcu = अणु
	.name			= "pcu",
	.num_counters		= 4,
	.num_boxes		= 1,
	.perf_ctr_bits		= 48,
	.perf_ctr		= SNBEP_PCU_MSR_PMON_CTR0,
	.event_ctl		= SNBEP_PCU_MSR_PMON_CTL0,
	.event_mask		= IVBEP_PCU_MSR_PMON_RAW_EVENT_MASK,
	.box_ctl		= SNBEP_PCU_MSR_PMON_BOX_CTL,
	.num_shared_regs	= 1,
	.ops			= &ivbep_uncore_pcu_ops,
	.क्रमmat_group		= &ivbep_uncore_pcu_क्रमmat_group,
पूर्ण;

अटल काष्ठा पूर्णांकel_uncore_type *ivbep_msr_uncores[] = अणु
	&ivbep_uncore_ubox,
	&ivbep_uncore_cbox,
	&ivbep_uncore_pcu,
	शून्य,
पूर्ण;

व्योम ivbep_uncore_cpu_init(व्योम)
अणु
	अगर (ivbep_uncore_cbox.num_boxes > boot_cpu_data.x86_max_cores)
		ivbep_uncore_cbox.num_boxes = boot_cpu_data.x86_max_cores;
	uncore_msr_uncores = ivbep_msr_uncores;
पूर्ण

अटल काष्ठा पूर्णांकel_uncore_type ivbep_uncore_ha = अणु
	.name		= "ha",
	.num_counters   = 4,
	.num_boxes	= 2,
	.perf_ctr_bits	= 48,
	IVBEP_UNCORE_PCI_COMMON_INIT(),
पूर्ण;

अटल काष्ठा पूर्णांकel_uncore_type ivbep_uncore_imc = अणु
	.name		= "imc",
	.num_counters   = 4,
	.num_boxes	= 8,
	.perf_ctr_bits	= 48,
	.fixed_ctr_bits	= 48,
	.fixed_ctr	= SNBEP_MC_CHy_PCI_PMON_FIXED_CTR,
	.fixed_ctl	= SNBEP_MC_CHy_PCI_PMON_FIXED_CTL,
	.event_descs	= snbep_uncore_imc_events,
	IVBEP_UNCORE_PCI_COMMON_INIT(),
पूर्ण;

/* रेजिस्टरs in IRP boxes are not properly aligned */
अटल अचिन्हित ivbep_uncore_irp_ctls[] = अणु0xd8, 0xdc, 0xe0, 0xe4पूर्ण;
अटल अचिन्हित ivbep_uncore_irp_ctrs[] = अणु0xa0, 0xb0, 0xb8, 0xc0पूर्ण;

अटल व्योम ivbep_uncore_irp_enable_event(काष्ठा पूर्णांकel_uncore_box *box, काष्ठा perf_event *event)
अणु
	काष्ठा pci_dev *pdev = box->pci_dev;
	काष्ठा hw_perf_event *hwc = &event->hw;

	pci_ग_लिखो_config_dword(pdev, ivbep_uncore_irp_ctls[hwc->idx],
			       hwc->config | SNBEP_PMON_CTL_EN);
पूर्ण

अटल व्योम ivbep_uncore_irp_disable_event(काष्ठा पूर्णांकel_uncore_box *box, काष्ठा perf_event *event)
अणु
	काष्ठा pci_dev *pdev = box->pci_dev;
	काष्ठा hw_perf_event *hwc = &event->hw;

	pci_ग_लिखो_config_dword(pdev, ivbep_uncore_irp_ctls[hwc->idx], hwc->config);
पूर्ण

अटल u64 ivbep_uncore_irp_पढ़ो_counter(काष्ठा पूर्णांकel_uncore_box *box, काष्ठा perf_event *event)
अणु
	काष्ठा pci_dev *pdev = box->pci_dev;
	काष्ठा hw_perf_event *hwc = &event->hw;
	u64 count = 0;

	pci_पढ़ो_config_dword(pdev, ivbep_uncore_irp_ctrs[hwc->idx], (u32 *)&count);
	pci_पढ़ो_config_dword(pdev, ivbep_uncore_irp_ctrs[hwc->idx] + 4, (u32 *)&count + 1);

	वापस count;
पूर्ण

अटल काष्ठा पूर्णांकel_uncore_ops ivbep_uncore_irp_ops = अणु
	.init_box	= ivbep_uncore_pci_init_box,
	.disable_box	= snbep_uncore_pci_disable_box,
	.enable_box	= snbep_uncore_pci_enable_box,
	.disable_event	= ivbep_uncore_irp_disable_event,
	.enable_event	= ivbep_uncore_irp_enable_event,
	.पढ़ो_counter	= ivbep_uncore_irp_पढ़ो_counter,
पूर्ण;

अटल काष्ठा पूर्णांकel_uncore_type ivbep_uncore_irp = अणु
	.name			= "irp",
	.num_counters		= 4,
	.num_boxes		= 1,
	.perf_ctr_bits		= 48,
	.event_mask		= IVBEP_PMON_RAW_EVENT_MASK,
	.box_ctl		= SNBEP_PCI_PMON_BOX_CTL,
	.ops			= &ivbep_uncore_irp_ops,
	.क्रमmat_group		= &ivbep_uncore_क्रमmat_group,
पूर्ण;

अटल काष्ठा पूर्णांकel_uncore_ops ivbep_uncore_qpi_ops = अणु
	.init_box	= ivbep_uncore_pci_init_box,
	.disable_box	= snbep_uncore_pci_disable_box,
	.enable_box	= snbep_uncore_pci_enable_box,
	.disable_event	= snbep_uncore_pci_disable_event,
	.enable_event	= snbep_qpi_enable_event,
	.पढ़ो_counter	= snbep_uncore_pci_पढ़ो_counter,
	.hw_config	= snbep_qpi_hw_config,
	.get_स्थिरraपूर्णांक	= uncore_get_स्थिरraपूर्णांक,
	.put_स्थिरraपूर्णांक	= uncore_put_स्थिरraपूर्णांक,
पूर्ण;

अटल काष्ठा पूर्णांकel_uncore_type ivbep_uncore_qpi = अणु
	.name			= "qpi",
	.num_counters		= 4,
	.num_boxes		= 3,
	.perf_ctr_bits		= 48,
	.perf_ctr		= SNBEP_PCI_PMON_CTR0,
	.event_ctl		= SNBEP_PCI_PMON_CTL0,
	.event_mask		= IVBEP_QPI_PCI_PMON_RAW_EVENT_MASK,
	.box_ctl		= SNBEP_PCI_PMON_BOX_CTL,
	.num_shared_regs	= 1,
	.ops			= &ivbep_uncore_qpi_ops,
	.क्रमmat_group		= &ivbep_uncore_qpi_क्रमmat_group,
पूर्ण;

अटल काष्ठा पूर्णांकel_uncore_type ivbep_uncore_r2pcie = अणु
	.name		= "r2pcie",
	.num_counters   = 4,
	.num_boxes	= 1,
	.perf_ctr_bits	= 44,
	.स्थिरraपूर्णांकs	= snbep_uncore_r2pcie_स्थिरraपूर्णांकs,
	IVBEP_UNCORE_PCI_COMMON_INIT(),
पूर्ण;

अटल काष्ठा पूर्णांकel_uncore_type ivbep_uncore_r3qpi = अणु
	.name		= "r3qpi",
	.num_counters   = 3,
	.num_boxes	= 2,
	.perf_ctr_bits	= 44,
	.स्थिरraपूर्णांकs	= snbep_uncore_r3qpi_स्थिरraपूर्णांकs,
	IVBEP_UNCORE_PCI_COMMON_INIT(),
पूर्ण;

क्रमागत अणु
	IVBEP_PCI_UNCORE_HA,
	IVBEP_PCI_UNCORE_IMC,
	IVBEP_PCI_UNCORE_IRP,
	IVBEP_PCI_UNCORE_QPI,
	IVBEP_PCI_UNCORE_R2PCIE,
	IVBEP_PCI_UNCORE_R3QPI,
पूर्ण;

अटल काष्ठा पूर्णांकel_uncore_type *ivbep_pci_uncores[] = अणु
	[IVBEP_PCI_UNCORE_HA]	= &ivbep_uncore_ha,
	[IVBEP_PCI_UNCORE_IMC]	= &ivbep_uncore_imc,
	[IVBEP_PCI_UNCORE_IRP]	= &ivbep_uncore_irp,
	[IVBEP_PCI_UNCORE_QPI]	= &ivbep_uncore_qpi,
	[IVBEP_PCI_UNCORE_R2PCIE]	= &ivbep_uncore_r2pcie,
	[IVBEP_PCI_UNCORE_R3QPI]	= &ivbep_uncore_r3qpi,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा pci_device_id ivbep_uncore_pci_ids[] = अणु
	अणु /* Home Agent 0 */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, 0xe30),
		.driver_data = UNCORE_PCI_DEV_DATA(IVBEP_PCI_UNCORE_HA, 0),
	पूर्ण,
	अणु /* Home Agent 1 */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, 0xe38),
		.driver_data = UNCORE_PCI_DEV_DATA(IVBEP_PCI_UNCORE_HA, 1),
	पूर्ण,
	अणु /* MC0 Channel 0 */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, 0xeb4),
		.driver_data = UNCORE_PCI_DEV_DATA(IVBEP_PCI_UNCORE_IMC, 0),
	पूर्ण,
	अणु /* MC0 Channel 1 */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, 0xeb5),
		.driver_data = UNCORE_PCI_DEV_DATA(IVBEP_PCI_UNCORE_IMC, 1),
	पूर्ण,
	अणु /* MC0 Channel 3 */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, 0xeb0),
		.driver_data = UNCORE_PCI_DEV_DATA(IVBEP_PCI_UNCORE_IMC, 2),
	पूर्ण,
	अणु /* MC0 Channel 4 */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, 0xeb1),
		.driver_data = UNCORE_PCI_DEV_DATA(IVBEP_PCI_UNCORE_IMC, 3),
	पूर्ण,
	अणु /* MC1 Channel 0 */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, 0xef4),
		.driver_data = UNCORE_PCI_DEV_DATA(IVBEP_PCI_UNCORE_IMC, 4),
	पूर्ण,
	अणु /* MC1 Channel 1 */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, 0xef5),
		.driver_data = UNCORE_PCI_DEV_DATA(IVBEP_PCI_UNCORE_IMC, 5),
	पूर्ण,
	अणु /* MC1 Channel 3 */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, 0xef0),
		.driver_data = UNCORE_PCI_DEV_DATA(IVBEP_PCI_UNCORE_IMC, 6),
	पूर्ण,
	अणु /* MC1 Channel 4 */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, 0xef1),
		.driver_data = UNCORE_PCI_DEV_DATA(IVBEP_PCI_UNCORE_IMC, 7),
	पूर्ण,
	अणु /* IRP */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, 0xe39),
		.driver_data = UNCORE_PCI_DEV_DATA(IVBEP_PCI_UNCORE_IRP, 0),
	पूर्ण,
	अणु /* QPI0 Port 0 */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, 0xe32),
		.driver_data = UNCORE_PCI_DEV_DATA(IVBEP_PCI_UNCORE_QPI, 0),
	पूर्ण,
	अणु /* QPI0 Port 1 */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, 0xe33),
		.driver_data = UNCORE_PCI_DEV_DATA(IVBEP_PCI_UNCORE_QPI, 1),
	पूर्ण,
	अणु /* QPI1 Port 2 */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, 0xe3a),
		.driver_data = UNCORE_PCI_DEV_DATA(IVBEP_PCI_UNCORE_QPI, 2),
	पूर्ण,
	अणु /* R2PCIe */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, 0xe34),
		.driver_data = UNCORE_PCI_DEV_DATA(IVBEP_PCI_UNCORE_R2PCIE, 0),
	पूर्ण,
	अणु /* R3QPI0 Link 0 */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, 0xe36),
		.driver_data = UNCORE_PCI_DEV_DATA(IVBEP_PCI_UNCORE_R3QPI, 0),
	पूर्ण,
	अणु /* R3QPI0 Link 1 */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, 0xe37),
		.driver_data = UNCORE_PCI_DEV_DATA(IVBEP_PCI_UNCORE_R3QPI, 1),
	पूर्ण,
	अणु /* R3QPI1 Link 2 */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, 0xe3e),
		.driver_data = UNCORE_PCI_DEV_DATA(IVBEP_PCI_UNCORE_R3QPI, 2),
	पूर्ण,
	अणु /* QPI Port 0 filter  */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, 0xe86),
		.driver_data = UNCORE_PCI_DEV_DATA(UNCORE_EXTRA_PCI_DEV,
						   SNBEP_PCI_QPI_PORT0_FILTER),
	पूर्ण,
	अणु /* QPI Port 0 filter  */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, 0xe96),
		.driver_data = UNCORE_PCI_DEV_DATA(UNCORE_EXTRA_PCI_DEV,
						   SNBEP_PCI_QPI_PORT1_FILTER),
	पूर्ण,
	अणु /* end: all zeroes */ पूर्ण
पूर्ण;

अटल काष्ठा pci_driver ivbep_uncore_pci_driver = अणु
	.name		= "ivbep_uncore",
	.id_table	= ivbep_uncore_pci_ids,
पूर्ण;

पूर्णांक ivbep_uncore_pci_init(व्योम)
अणु
	पूर्णांक ret = snbep_pci2phy_map_init(0x0e1e, SNBEP_CPUNODEID, SNBEP_GIDNIDMAP, true);
	अगर (ret)
		वापस ret;
	uncore_pci_uncores = ivbep_pci_uncores;
	uncore_pci_driver = &ivbep_uncore_pci_driver;
	वापस 0;
पूर्ण
/* end of IvyTown uncore support */

/* KNL uncore support */
अटल काष्ठा attribute *knl_uncore_ubox_क्रमmats_attr[] = अणु
	&क्रमmat_attr_event.attr,
	&क्रमmat_attr_umask.attr,
	&क्रमmat_attr_edge.attr,
	&क्रमmat_attr_tid_en.attr,
	&क्रमmat_attr_inv.attr,
	&क्रमmat_attr_thresh5.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group knl_uncore_ubox_क्रमmat_group = अणु
	.name = "format",
	.attrs = knl_uncore_ubox_क्रमmats_attr,
पूर्ण;

अटल काष्ठा पूर्णांकel_uncore_type knl_uncore_ubox = अणु
	.name			= "ubox",
	.num_counters		= 2,
	.num_boxes		= 1,
	.perf_ctr_bits		= 48,
	.fixed_ctr_bits		= 48,
	.perf_ctr		= HSWEP_U_MSR_PMON_CTR0,
	.event_ctl		= HSWEP_U_MSR_PMON_CTL0,
	.event_mask		= KNL_U_MSR_PMON_RAW_EVENT_MASK,
	.fixed_ctr		= HSWEP_U_MSR_PMON_UCLK_FIXED_CTR,
	.fixed_ctl		= HSWEP_U_MSR_PMON_UCLK_FIXED_CTL,
	.ops			= &snbep_uncore_msr_ops,
	.क्रमmat_group		= &knl_uncore_ubox_क्रमmat_group,
पूर्ण;

अटल काष्ठा attribute *knl_uncore_cha_क्रमmats_attr[] = अणु
	&क्रमmat_attr_event.attr,
	&क्रमmat_attr_umask.attr,
	&क्रमmat_attr_qor.attr,
	&क्रमmat_attr_edge.attr,
	&क्रमmat_attr_tid_en.attr,
	&क्रमmat_attr_inv.attr,
	&क्रमmat_attr_thresh8.attr,
	&क्रमmat_attr_filter_tid4.attr,
	&क्रमmat_attr_filter_link3.attr,
	&क्रमmat_attr_filter_state4.attr,
	&क्रमmat_attr_filter_local.attr,
	&क्रमmat_attr_filter_all_op.attr,
	&क्रमmat_attr_filter_nnm.attr,
	&क्रमmat_attr_filter_opc3.attr,
	&क्रमmat_attr_filter_nc.attr,
	&क्रमmat_attr_filter_isoc.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group knl_uncore_cha_क्रमmat_group = अणु
	.name = "format",
	.attrs = knl_uncore_cha_क्रमmats_attr,
पूर्ण;

अटल काष्ठा event_स्थिरraपूर्णांक knl_uncore_cha_स्थिरraपूर्णांकs[] = अणु
	UNCORE_EVENT_CONSTRAINT(0x11, 0x1),
	UNCORE_EVENT_CONSTRAINT(0x1f, 0x1),
	UNCORE_EVENT_CONSTRAINT(0x36, 0x1),
	EVENT_CONSTRAINT_END
पूर्ण;

अटल काष्ठा extra_reg knl_uncore_cha_extra_regs[] = अणु
	SNBEP_CBO_EVENT_EXTRA_REG(SNBEP_CBO_PMON_CTL_TID_EN,
				  SNBEP_CBO_PMON_CTL_TID_EN, 0x1),
	SNBEP_CBO_EVENT_EXTRA_REG(0x3d, 0xff, 0x2),
	SNBEP_CBO_EVENT_EXTRA_REG(0x35, 0xff, 0x4),
	SNBEP_CBO_EVENT_EXTRA_REG(0x36, 0xff, 0x4),
	EVENT_EXTRA_END
पूर्ण;

अटल u64 knl_cha_filter_mask(पूर्णांक fields)
अणु
	u64 mask = 0;

	अगर (fields & 0x1)
		mask |= KNL_CHA_MSR_PMON_BOX_FILTER_TID;
	अगर (fields & 0x2)
		mask |= KNL_CHA_MSR_PMON_BOX_FILTER_STATE;
	अगर (fields & 0x4)
		mask |= KNL_CHA_MSR_PMON_BOX_FILTER_OP;
	वापस mask;
पूर्ण

अटल काष्ठा event_स्थिरraपूर्णांक *
knl_cha_get_स्थिरraपूर्णांक(काष्ठा पूर्णांकel_uncore_box *box, काष्ठा perf_event *event)
अणु
	वापस __snbep_cbox_get_स्थिरraपूर्णांक(box, event, knl_cha_filter_mask);
पूर्ण

अटल पूर्णांक knl_cha_hw_config(काष्ठा पूर्णांकel_uncore_box *box,
			     काष्ठा perf_event *event)
अणु
	काष्ठा hw_perf_event_extra *reg1 = &event->hw.extra_reg;
	काष्ठा extra_reg *er;
	पूर्णांक idx = 0;

	क्रम (er = knl_uncore_cha_extra_regs; er->msr; er++) अणु
		अगर (er->event != (event->hw.config & er->config_mask))
			जारी;
		idx |= er->idx;
	पूर्ण

	अगर (idx) अणु
		reg1->reg = HSWEP_C0_MSR_PMON_BOX_FILTER0 +
			    KNL_CHA_MSR_OFFSET * box->pmu->pmu_idx;
		reg1->config = event->attr.config1 & knl_cha_filter_mask(idx);

		reg1->config |= KNL_CHA_MSR_PMON_BOX_FILTER_REMOTE_NODE;
		reg1->config |= KNL_CHA_MSR_PMON_BOX_FILTER_LOCAL_NODE;
		reg1->config |= KNL_CHA_MSR_PMON_BOX_FILTER_NNC;
		reg1->idx = idx;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम hswep_cbox_enable_event(काष्ठा पूर्णांकel_uncore_box *box,
				    काष्ठा perf_event *event);

अटल काष्ठा पूर्णांकel_uncore_ops knl_uncore_cha_ops = अणु
	.init_box		= snbep_uncore_msr_init_box,
	.disable_box		= snbep_uncore_msr_disable_box,
	.enable_box		= snbep_uncore_msr_enable_box,
	.disable_event		= snbep_uncore_msr_disable_event,
	.enable_event		= hswep_cbox_enable_event,
	.पढ़ो_counter		= uncore_msr_पढ़ो_counter,
	.hw_config		= knl_cha_hw_config,
	.get_स्थिरraपूर्णांक		= knl_cha_get_स्थिरraपूर्णांक,
	.put_स्थिरraपूर्णांक		= snbep_cbox_put_स्थिरraपूर्णांक,
पूर्ण;

अटल काष्ठा पूर्णांकel_uncore_type knl_uncore_cha = अणु
	.name			= "cha",
	.num_counters		= 4,
	.num_boxes		= 38,
	.perf_ctr_bits		= 48,
	.event_ctl		= HSWEP_C0_MSR_PMON_CTL0,
	.perf_ctr		= HSWEP_C0_MSR_PMON_CTR0,
	.event_mask		= KNL_CHA_MSR_PMON_RAW_EVENT_MASK,
	.box_ctl		= HSWEP_C0_MSR_PMON_BOX_CTL,
	.msr_offset		= KNL_CHA_MSR_OFFSET,
	.num_shared_regs	= 1,
	.स्थिरraपूर्णांकs		= knl_uncore_cha_स्थिरraपूर्णांकs,
	.ops			= &knl_uncore_cha_ops,
	.क्रमmat_group		= &knl_uncore_cha_क्रमmat_group,
पूर्ण;

अटल काष्ठा attribute *knl_uncore_pcu_क्रमmats_attr[] = अणु
	&क्रमmat_attr_event2.attr,
	&क्रमmat_attr_use_occ_ctr.attr,
	&क्रमmat_attr_occ_sel.attr,
	&क्रमmat_attr_edge.attr,
	&क्रमmat_attr_tid_en.attr,
	&क्रमmat_attr_inv.attr,
	&क्रमmat_attr_thresh6.attr,
	&क्रमmat_attr_occ_invert.attr,
	&क्रमmat_attr_occ_edge_det.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group knl_uncore_pcu_क्रमmat_group = अणु
	.name = "format",
	.attrs = knl_uncore_pcu_क्रमmats_attr,
पूर्ण;

अटल काष्ठा पूर्णांकel_uncore_type knl_uncore_pcu = अणु
	.name			= "pcu",
	.num_counters		= 4,
	.num_boxes		= 1,
	.perf_ctr_bits		= 48,
	.perf_ctr		= HSWEP_PCU_MSR_PMON_CTR0,
	.event_ctl		= HSWEP_PCU_MSR_PMON_CTL0,
	.event_mask		= KNL_PCU_MSR_PMON_RAW_EVENT_MASK,
	.box_ctl		= HSWEP_PCU_MSR_PMON_BOX_CTL,
	.ops			= &snbep_uncore_msr_ops,
	.क्रमmat_group		= &knl_uncore_pcu_क्रमmat_group,
पूर्ण;

अटल काष्ठा पूर्णांकel_uncore_type *knl_msr_uncores[] = अणु
	&knl_uncore_ubox,
	&knl_uncore_cha,
	&knl_uncore_pcu,
	शून्य,
पूर्ण;

व्योम knl_uncore_cpu_init(व्योम)
अणु
	uncore_msr_uncores = knl_msr_uncores;
पूर्ण

अटल व्योम knl_uncore_imc_enable_box(काष्ठा पूर्णांकel_uncore_box *box)
अणु
	काष्ठा pci_dev *pdev = box->pci_dev;
	पूर्णांक box_ctl = uncore_pci_box_ctl(box);

	pci_ग_लिखो_config_dword(pdev, box_ctl, 0);
पूर्ण

अटल व्योम knl_uncore_imc_enable_event(काष्ठा पूर्णांकel_uncore_box *box,
					काष्ठा perf_event *event)
अणु
	काष्ठा pci_dev *pdev = box->pci_dev;
	काष्ठा hw_perf_event *hwc = &event->hw;

	अगर ((event->attr.config & SNBEP_PMON_CTL_EV_SEL_MASK)
							== UNCORE_FIXED_EVENT)
		pci_ग_लिखो_config_dword(pdev, hwc->config_base,
				       hwc->config | KNL_PMON_FIXED_CTL_EN);
	अन्यथा
		pci_ग_लिखो_config_dword(pdev, hwc->config_base,
				       hwc->config | SNBEP_PMON_CTL_EN);
पूर्ण

अटल काष्ठा पूर्णांकel_uncore_ops knl_uncore_imc_ops = अणु
	.init_box	= snbep_uncore_pci_init_box,
	.disable_box	= snbep_uncore_pci_disable_box,
	.enable_box	= knl_uncore_imc_enable_box,
	.पढ़ो_counter	= snbep_uncore_pci_पढ़ो_counter,
	.enable_event	= knl_uncore_imc_enable_event,
	.disable_event	= snbep_uncore_pci_disable_event,
पूर्ण;

अटल काष्ठा पूर्णांकel_uncore_type knl_uncore_imc_uclk = अणु
	.name			= "imc_uclk",
	.num_counters		= 4,
	.num_boxes		= 2,
	.perf_ctr_bits		= 48,
	.fixed_ctr_bits		= 48,
	.perf_ctr		= KNL_UCLK_MSR_PMON_CTR0_LOW,
	.event_ctl		= KNL_UCLK_MSR_PMON_CTL0,
	.event_mask		= SNBEP_PMON_RAW_EVENT_MASK,
	.fixed_ctr		= KNL_UCLK_MSR_PMON_UCLK_FIXED_LOW,
	.fixed_ctl		= KNL_UCLK_MSR_PMON_UCLK_FIXED_CTL,
	.box_ctl		= KNL_UCLK_MSR_PMON_BOX_CTL,
	.ops			= &knl_uncore_imc_ops,
	.क्रमmat_group		= &snbep_uncore_क्रमmat_group,
पूर्ण;

अटल काष्ठा पूर्णांकel_uncore_type knl_uncore_imc_dclk = अणु
	.name			= "imc",
	.num_counters		= 4,
	.num_boxes		= 6,
	.perf_ctr_bits		= 48,
	.fixed_ctr_bits		= 48,
	.perf_ctr		= KNL_MC0_CH0_MSR_PMON_CTR0_LOW,
	.event_ctl		= KNL_MC0_CH0_MSR_PMON_CTL0,
	.event_mask		= SNBEP_PMON_RAW_EVENT_MASK,
	.fixed_ctr		= KNL_MC0_CH0_MSR_PMON_FIXED_LOW,
	.fixed_ctl		= KNL_MC0_CH0_MSR_PMON_FIXED_CTL,
	.box_ctl		= KNL_MC0_CH0_MSR_PMON_BOX_CTL,
	.ops			= &knl_uncore_imc_ops,
	.क्रमmat_group		= &snbep_uncore_क्रमmat_group,
पूर्ण;

अटल काष्ठा पूर्णांकel_uncore_type knl_uncore_edc_uclk = अणु
	.name			= "edc_uclk",
	.num_counters		= 4,
	.num_boxes		= 8,
	.perf_ctr_bits		= 48,
	.fixed_ctr_bits		= 48,
	.perf_ctr		= KNL_UCLK_MSR_PMON_CTR0_LOW,
	.event_ctl		= KNL_UCLK_MSR_PMON_CTL0,
	.event_mask		= SNBEP_PMON_RAW_EVENT_MASK,
	.fixed_ctr		= KNL_UCLK_MSR_PMON_UCLK_FIXED_LOW,
	.fixed_ctl		= KNL_UCLK_MSR_PMON_UCLK_FIXED_CTL,
	.box_ctl		= KNL_UCLK_MSR_PMON_BOX_CTL,
	.ops			= &knl_uncore_imc_ops,
	.क्रमmat_group		= &snbep_uncore_क्रमmat_group,
पूर्ण;

अटल काष्ठा पूर्णांकel_uncore_type knl_uncore_edc_eclk = अणु
	.name			= "edc_eclk",
	.num_counters		= 4,
	.num_boxes		= 8,
	.perf_ctr_bits		= 48,
	.fixed_ctr_bits		= 48,
	.perf_ctr		= KNL_EDC0_ECLK_MSR_PMON_CTR0_LOW,
	.event_ctl		= KNL_EDC0_ECLK_MSR_PMON_CTL0,
	.event_mask		= SNBEP_PMON_RAW_EVENT_MASK,
	.fixed_ctr		= KNL_EDC0_ECLK_MSR_PMON_ECLK_FIXED_LOW,
	.fixed_ctl		= KNL_EDC0_ECLK_MSR_PMON_ECLK_FIXED_CTL,
	.box_ctl		= KNL_EDC0_ECLK_MSR_PMON_BOX_CTL,
	.ops			= &knl_uncore_imc_ops,
	.क्रमmat_group		= &snbep_uncore_क्रमmat_group,
पूर्ण;

अटल काष्ठा event_स्थिरraपूर्णांक knl_uncore_m2pcie_स्थिरraपूर्णांकs[] = अणु
	UNCORE_EVENT_CONSTRAINT(0x23, 0x3),
	EVENT_CONSTRAINT_END
पूर्ण;

अटल काष्ठा पूर्णांकel_uncore_type knl_uncore_m2pcie = अणु
	.name		= "m2pcie",
	.num_counters   = 4,
	.num_boxes	= 1,
	.perf_ctr_bits	= 48,
	.स्थिरraपूर्णांकs	= knl_uncore_m2pcie_स्थिरraपूर्णांकs,
	SNBEP_UNCORE_PCI_COMMON_INIT(),
पूर्ण;

अटल काष्ठा attribute *knl_uncore_irp_क्रमmats_attr[] = अणु
	&क्रमmat_attr_event.attr,
	&क्रमmat_attr_umask.attr,
	&क्रमmat_attr_qor.attr,
	&क्रमmat_attr_edge.attr,
	&क्रमmat_attr_inv.attr,
	&क्रमmat_attr_thresh8.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group knl_uncore_irp_क्रमmat_group = अणु
	.name = "format",
	.attrs = knl_uncore_irp_क्रमmats_attr,
पूर्ण;

अटल काष्ठा पूर्णांकel_uncore_type knl_uncore_irp = अणु
	.name			= "irp",
	.num_counters		= 2,
	.num_boxes		= 1,
	.perf_ctr_bits		= 48,
	.perf_ctr		= SNBEP_PCI_PMON_CTR0,
	.event_ctl		= SNBEP_PCI_PMON_CTL0,
	.event_mask		= KNL_IRP_PCI_PMON_RAW_EVENT_MASK,
	.box_ctl		= KNL_IRP_PCI_PMON_BOX_CTL,
	.ops			= &snbep_uncore_pci_ops,
	.क्रमmat_group		= &knl_uncore_irp_क्रमmat_group,
पूर्ण;

क्रमागत अणु
	KNL_PCI_UNCORE_MC_UCLK,
	KNL_PCI_UNCORE_MC_DCLK,
	KNL_PCI_UNCORE_EDC_UCLK,
	KNL_PCI_UNCORE_EDC_ECLK,
	KNL_PCI_UNCORE_M2PCIE,
	KNL_PCI_UNCORE_IRP,
पूर्ण;

अटल काष्ठा पूर्णांकel_uncore_type *knl_pci_uncores[] = अणु
	[KNL_PCI_UNCORE_MC_UCLK]	= &knl_uncore_imc_uclk,
	[KNL_PCI_UNCORE_MC_DCLK]	= &knl_uncore_imc_dclk,
	[KNL_PCI_UNCORE_EDC_UCLK]	= &knl_uncore_edc_uclk,
	[KNL_PCI_UNCORE_EDC_ECLK]	= &knl_uncore_edc_eclk,
	[KNL_PCI_UNCORE_M2PCIE]		= &knl_uncore_m2pcie,
	[KNL_PCI_UNCORE_IRP]		= &knl_uncore_irp,
	शून्य,
पूर्ण;

/*
 * KNL uses a common PCI device ID क्रम multiple instances of an Uncore PMU
 * device type. prior to KNL, each instance of a PMU device type had a unique
 * device ID.
 *
 *	PCI Device ID	Uncore PMU Devices
 *	----------------------------------
 *	0x7841		MC0 UClk, MC1 UClk
 *	0x7843		MC0 DClk CH 0, MC0 DClk CH 1, MC0 DClk CH 2,
 *			MC1 DClk CH 0, MC1 DClk CH 1, MC1 DClk CH 2
 *	0x7833		EDC0 UClk, EDC1 UClk, EDC2 UClk, EDC3 UClk,
 *			EDC4 UClk, EDC5 UClk, EDC6 UClk, EDC7 UClk
 *	0x7835		EDC0 EClk, EDC1 EClk, EDC2 EClk, EDC3 EClk,
 *			EDC4 EClk, EDC5 EClk, EDC6 EClk, EDC7 EClk
 *	0x7817		M2PCIe
 *	0x7814		IRP
*/

अटल स्थिर काष्ठा pci_device_id knl_uncore_pci_ids[] = अणु
	अणु /* MC0 UClk */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, 0x7841),
		.driver_data = UNCORE_PCI_DEV_FULL_DATA(10, 0, KNL_PCI_UNCORE_MC_UCLK, 0),
	पूर्ण,
	अणु /* MC1 UClk */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, 0x7841),
		.driver_data = UNCORE_PCI_DEV_FULL_DATA(11, 0, KNL_PCI_UNCORE_MC_UCLK, 1),
	पूर्ण,
	अणु /* MC0 DClk CH 0 */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, 0x7843),
		.driver_data = UNCORE_PCI_DEV_FULL_DATA(8, 2, KNL_PCI_UNCORE_MC_DCLK, 0),
	पूर्ण,
	अणु /* MC0 DClk CH 1 */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, 0x7843),
		.driver_data = UNCORE_PCI_DEV_FULL_DATA(8, 3, KNL_PCI_UNCORE_MC_DCLK, 1),
	पूर्ण,
	अणु /* MC0 DClk CH 2 */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, 0x7843),
		.driver_data = UNCORE_PCI_DEV_FULL_DATA(8, 4, KNL_PCI_UNCORE_MC_DCLK, 2),
	पूर्ण,
	अणु /* MC1 DClk CH 0 */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, 0x7843),
		.driver_data = UNCORE_PCI_DEV_FULL_DATA(9, 2, KNL_PCI_UNCORE_MC_DCLK, 3),
	पूर्ण,
	अणु /* MC1 DClk CH 1 */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, 0x7843),
		.driver_data = UNCORE_PCI_DEV_FULL_DATA(9, 3, KNL_PCI_UNCORE_MC_DCLK, 4),
	पूर्ण,
	अणु /* MC1 DClk CH 2 */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, 0x7843),
		.driver_data = UNCORE_PCI_DEV_FULL_DATA(9, 4, KNL_PCI_UNCORE_MC_DCLK, 5),
	पूर्ण,
	अणु /* EDC0 UClk */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, 0x7833),
		.driver_data = UNCORE_PCI_DEV_FULL_DATA(15, 0, KNL_PCI_UNCORE_EDC_UCLK, 0),
	पूर्ण,
	अणु /* EDC1 UClk */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, 0x7833),
		.driver_data = UNCORE_PCI_DEV_FULL_DATA(16, 0, KNL_PCI_UNCORE_EDC_UCLK, 1),
	पूर्ण,
	अणु /* EDC2 UClk */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, 0x7833),
		.driver_data = UNCORE_PCI_DEV_FULL_DATA(17, 0, KNL_PCI_UNCORE_EDC_UCLK, 2),
	पूर्ण,
	अणु /* EDC3 UClk */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, 0x7833),
		.driver_data = UNCORE_PCI_DEV_FULL_DATA(18, 0, KNL_PCI_UNCORE_EDC_UCLK, 3),
	पूर्ण,
	अणु /* EDC4 UClk */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, 0x7833),
		.driver_data = UNCORE_PCI_DEV_FULL_DATA(19, 0, KNL_PCI_UNCORE_EDC_UCLK, 4),
	पूर्ण,
	अणु /* EDC5 UClk */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, 0x7833),
		.driver_data = UNCORE_PCI_DEV_FULL_DATA(20, 0, KNL_PCI_UNCORE_EDC_UCLK, 5),
	पूर्ण,
	अणु /* EDC6 UClk */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, 0x7833),
		.driver_data = UNCORE_PCI_DEV_FULL_DATA(21, 0, KNL_PCI_UNCORE_EDC_UCLK, 6),
	पूर्ण,
	अणु /* EDC7 UClk */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, 0x7833),
		.driver_data = UNCORE_PCI_DEV_FULL_DATA(22, 0, KNL_PCI_UNCORE_EDC_UCLK, 7),
	पूर्ण,
	अणु /* EDC0 EClk */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, 0x7835),
		.driver_data = UNCORE_PCI_DEV_FULL_DATA(24, 2, KNL_PCI_UNCORE_EDC_ECLK, 0),
	पूर्ण,
	अणु /* EDC1 EClk */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, 0x7835),
		.driver_data = UNCORE_PCI_DEV_FULL_DATA(25, 2, KNL_PCI_UNCORE_EDC_ECLK, 1),
	पूर्ण,
	अणु /* EDC2 EClk */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, 0x7835),
		.driver_data = UNCORE_PCI_DEV_FULL_DATA(26, 2, KNL_PCI_UNCORE_EDC_ECLK, 2),
	पूर्ण,
	अणु /* EDC3 EClk */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, 0x7835),
		.driver_data = UNCORE_PCI_DEV_FULL_DATA(27, 2, KNL_PCI_UNCORE_EDC_ECLK, 3),
	पूर्ण,
	अणु /* EDC4 EClk */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, 0x7835),
		.driver_data = UNCORE_PCI_DEV_FULL_DATA(28, 2, KNL_PCI_UNCORE_EDC_ECLK, 4),
	पूर्ण,
	अणु /* EDC5 EClk */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, 0x7835),
		.driver_data = UNCORE_PCI_DEV_FULL_DATA(29, 2, KNL_PCI_UNCORE_EDC_ECLK, 5),
	पूर्ण,
	अणु /* EDC6 EClk */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, 0x7835),
		.driver_data = UNCORE_PCI_DEV_FULL_DATA(30, 2, KNL_PCI_UNCORE_EDC_ECLK, 6),
	पूर्ण,
	अणु /* EDC7 EClk */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, 0x7835),
		.driver_data = UNCORE_PCI_DEV_FULL_DATA(31, 2, KNL_PCI_UNCORE_EDC_ECLK, 7),
	पूर्ण,
	अणु /* M2PCIe */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, 0x7817),
		.driver_data = UNCORE_PCI_DEV_DATA(KNL_PCI_UNCORE_M2PCIE, 0),
	पूर्ण,
	अणु /* IRP */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, 0x7814),
		.driver_data = UNCORE_PCI_DEV_DATA(KNL_PCI_UNCORE_IRP, 0),
	पूर्ण,
	अणु /* end: all zeroes */ पूर्ण
पूर्ण;

अटल काष्ठा pci_driver knl_uncore_pci_driver = अणु
	.name		= "knl_uncore",
	.id_table	= knl_uncore_pci_ids,
पूर्ण;

पूर्णांक knl_uncore_pci_init(व्योम)
अणु
	पूर्णांक ret;

	/* All KNL PCI based PMON units are on the same PCI bus except IRP */
	ret = snb_pci2phy_map_init(0x7814); /* IRP */
	अगर (ret)
		वापस ret;
	ret = snb_pci2phy_map_init(0x7817); /* M2PCIe */
	अगर (ret)
		वापस ret;
	uncore_pci_uncores = knl_pci_uncores;
	uncore_pci_driver = &knl_uncore_pci_driver;
	वापस 0;
पूर्ण

/* end of KNL uncore support */

/* Haswell-EP uncore support */
अटल काष्ठा attribute *hswep_uncore_ubox_क्रमmats_attr[] = अणु
	&क्रमmat_attr_event.attr,
	&क्रमmat_attr_umask.attr,
	&क्रमmat_attr_edge.attr,
	&क्रमmat_attr_inv.attr,
	&क्रमmat_attr_thresh5.attr,
	&क्रमmat_attr_filter_tid2.attr,
	&क्रमmat_attr_filter_cid.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group hswep_uncore_ubox_क्रमmat_group = अणु
	.name = "format",
	.attrs = hswep_uncore_ubox_क्रमmats_attr,
पूर्ण;

अटल पूर्णांक hswep_ubox_hw_config(काष्ठा पूर्णांकel_uncore_box *box, काष्ठा perf_event *event)
अणु
	काष्ठा hw_perf_event_extra *reg1 = &event->hw.extra_reg;
	reg1->reg = HSWEP_U_MSR_PMON_FILTER;
	reg1->config = event->attr.config1 & HSWEP_U_MSR_PMON_BOX_FILTER_MASK;
	reg1->idx = 0;
	वापस 0;
पूर्ण

अटल काष्ठा पूर्णांकel_uncore_ops hswep_uncore_ubox_ops = अणु
	SNBEP_UNCORE_MSR_OPS_COMMON_INIT(),
	.hw_config		= hswep_ubox_hw_config,
	.get_स्थिरraपूर्णांक		= uncore_get_स्थिरraपूर्णांक,
	.put_स्थिरraपूर्णांक		= uncore_put_स्थिरraपूर्णांक,
पूर्ण;

अटल काष्ठा पूर्णांकel_uncore_type hswep_uncore_ubox = अणु
	.name			= "ubox",
	.num_counters		= 2,
	.num_boxes		= 1,
	.perf_ctr_bits		= 44,
	.fixed_ctr_bits		= 48,
	.perf_ctr		= HSWEP_U_MSR_PMON_CTR0,
	.event_ctl		= HSWEP_U_MSR_PMON_CTL0,
	.event_mask		= SNBEP_U_MSR_PMON_RAW_EVENT_MASK,
	.fixed_ctr		= HSWEP_U_MSR_PMON_UCLK_FIXED_CTR,
	.fixed_ctl		= HSWEP_U_MSR_PMON_UCLK_FIXED_CTL,
	.num_shared_regs	= 1,
	.ops			= &hswep_uncore_ubox_ops,
	.क्रमmat_group		= &hswep_uncore_ubox_क्रमmat_group,
पूर्ण;

अटल काष्ठा attribute *hswep_uncore_cbox_क्रमmats_attr[] = अणु
	&क्रमmat_attr_event.attr,
	&क्रमmat_attr_umask.attr,
	&क्रमmat_attr_edge.attr,
	&क्रमmat_attr_tid_en.attr,
	&क्रमmat_attr_thresh8.attr,
	&क्रमmat_attr_filter_tid3.attr,
	&क्रमmat_attr_filter_link2.attr,
	&क्रमmat_attr_filter_state3.attr,
	&क्रमmat_attr_filter_nid2.attr,
	&क्रमmat_attr_filter_opc2.attr,
	&क्रमmat_attr_filter_nc.attr,
	&क्रमmat_attr_filter_c6.attr,
	&क्रमmat_attr_filter_isoc.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group hswep_uncore_cbox_क्रमmat_group = अणु
	.name = "format",
	.attrs = hswep_uncore_cbox_क्रमmats_attr,
पूर्ण;

अटल काष्ठा event_स्थिरraपूर्णांक hswep_uncore_cbox_स्थिरraपूर्णांकs[] = अणु
	UNCORE_EVENT_CONSTRAINT(0x01, 0x1),
	UNCORE_EVENT_CONSTRAINT(0x09, 0x1),
	UNCORE_EVENT_CONSTRAINT(0x11, 0x1),
	UNCORE_EVENT_CONSTRAINT(0x36, 0x1),
	UNCORE_EVENT_CONSTRAINT(0x38, 0x3),
	UNCORE_EVENT_CONSTRAINT(0x3b, 0x1),
	UNCORE_EVENT_CONSTRAINT(0x3e, 0x1),
	EVENT_CONSTRAINT_END
पूर्ण;

अटल काष्ठा extra_reg hswep_uncore_cbox_extra_regs[] = अणु
	SNBEP_CBO_EVENT_EXTRA_REG(SNBEP_CBO_PMON_CTL_TID_EN,
				  SNBEP_CBO_PMON_CTL_TID_EN, 0x1),
	SNBEP_CBO_EVENT_EXTRA_REG(0x0334, 0xffff, 0x4),
	SNBEP_CBO_EVENT_EXTRA_REG(0x0534, 0xffff, 0x4),
	SNBEP_CBO_EVENT_EXTRA_REG(0x0934, 0xffff, 0x4),
	SNBEP_CBO_EVENT_EXTRA_REG(0x1134, 0xffff, 0x4),
	SNBEP_CBO_EVENT_EXTRA_REG(0x2134, 0xffff, 0x4),
	SNBEP_CBO_EVENT_EXTRA_REG(0x4134, 0xffff, 0x4),
	SNBEP_CBO_EVENT_EXTRA_REG(0x4037, 0x40ff, 0x8),
	SNBEP_CBO_EVENT_EXTRA_REG(0x4028, 0x40ff, 0x8),
	SNBEP_CBO_EVENT_EXTRA_REG(0x4032, 0x40ff, 0x8),
	SNBEP_CBO_EVENT_EXTRA_REG(0x4029, 0x40ff, 0x8),
	SNBEP_CBO_EVENT_EXTRA_REG(0x4033, 0x40ff, 0x8),
	SNBEP_CBO_EVENT_EXTRA_REG(0x402A, 0x40ff, 0x8),
	SNBEP_CBO_EVENT_EXTRA_REG(0x0135, 0xffff, 0x12),
	SNBEP_CBO_EVENT_EXTRA_REG(0x0335, 0xffff, 0x10),
	SNBEP_CBO_EVENT_EXTRA_REG(0x4135, 0xffff, 0x18),
	SNBEP_CBO_EVENT_EXTRA_REG(0x4435, 0xffff, 0x8),
	SNBEP_CBO_EVENT_EXTRA_REG(0x4835, 0xffff, 0x8),
	SNBEP_CBO_EVENT_EXTRA_REG(0x5035, 0xffff, 0x8),
	SNBEP_CBO_EVENT_EXTRA_REG(0x4335, 0xffff, 0x18),
	SNBEP_CBO_EVENT_EXTRA_REG(0x4a35, 0xffff, 0x8),
	SNBEP_CBO_EVENT_EXTRA_REG(0x2335, 0xffff, 0x10),
	SNBEP_CBO_EVENT_EXTRA_REG(0x8335, 0xffff, 0x10),
	SNBEP_CBO_EVENT_EXTRA_REG(0x2135, 0xffff, 0x10),
	SNBEP_CBO_EVENT_EXTRA_REG(0x8135, 0xffff, 0x10),
	SNBEP_CBO_EVENT_EXTRA_REG(0x0136, 0xffff, 0x10),
	SNBEP_CBO_EVENT_EXTRA_REG(0x0336, 0xffff, 0x10),
	SNBEP_CBO_EVENT_EXTRA_REG(0x4136, 0xffff, 0x18),
	SNBEP_CBO_EVENT_EXTRA_REG(0x4436, 0xffff, 0x8),
	SNBEP_CBO_EVENT_EXTRA_REG(0x4836, 0xffff, 0x8),
	SNBEP_CBO_EVENT_EXTRA_REG(0x4336, 0xffff, 0x18),
	SNBEP_CBO_EVENT_EXTRA_REG(0x4a36, 0xffff, 0x8),
	SNBEP_CBO_EVENT_EXTRA_REG(0x2336, 0xffff, 0x10),
	SNBEP_CBO_EVENT_EXTRA_REG(0x8336, 0xffff, 0x10),
	SNBEP_CBO_EVENT_EXTRA_REG(0x2136, 0xffff, 0x10),
	SNBEP_CBO_EVENT_EXTRA_REG(0x8136, 0xffff, 0x10),
	SNBEP_CBO_EVENT_EXTRA_REG(0x5036, 0xffff, 0x8),
	EVENT_EXTRA_END
पूर्ण;

अटल u64 hswep_cbox_filter_mask(पूर्णांक fields)
अणु
	u64 mask = 0;
	अगर (fields & 0x1)
		mask |= HSWEP_CB0_MSR_PMON_BOX_FILTER_TID;
	अगर (fields & 0x2)
		mask |= HSWEP_CB0_MSR_PMON_BOX_FILTER_LINK;
	अगर (fields & 0x4)
		mask |= HSWEP_CB0_MSR_PMON_BOX_FILTER_STATE;
	अगर (fields & 0x8)
		mask |= HSWEP_CB0_MSR_PMON_BOX_FILTER_NID;
	अगर (fields & 0x10) अणु
		mask |= HSWEP_CB0_MSR_PMON_BOX_FILTER_OPC;
		mask |= HSWEP_CB0_MSR_PMON_BOX_FILTER_NC;
		mask |= HSWEP_CB0_MSR_PMON_BOX_FILTER_C6;
		mask |= HSWEP_CB0_MSR_PMON_BOX_FILTER_ISOC;
	पूर्ण
	वापस mask;
पूर्ण

अटल काष्ठा event_स्थिरraपूर्णांक *
hswep_cbox_get_स्थिरraपूर्णांक(काष्ठा पूर्णांकel_uncore_box *box, काष्ठा perf_event *event)
अणु
	वापस __snbep_cbox_get_स्थिरraपूर्णांक(box, event, hswep_cbox_filter_mask);
पूर्ण

अटल पूर्णांक hswep_cbox_hw_config(काष्ठा पूर्णांकel_uncore_box *box, काष्ठा perf_event *event)
अणु
	काष्ठा hw_perf_event_extra *reg1 = &event->hw.extra_reg;
	काष्ठा extra_reg *er;
	पूर्णांक idx = 0;

	क्रम (er = hswep_uncore_cbox_extra_regs; er->msr; er++) अणु
		अगर (er->event != (event->hw.config & er->config_mask))
			जारी;
		idx |= er->idx;
	पूर्ण

	अगर (idx) अणु
		reg1->reg = HSWEP_C0_MSR_PMON_BOX_FILTER0 +
			    HSWEP_CBO_MSR_OFFSET * box->pmu->pmu_idx;
		reg1->config = event->attr.config1 & hswep_cbox_filter_mask(idx);
		reg1->idx = idx;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम hswep_cbox_enable_event(काष्ठा पूर्णांकel_uncore_box *box,
				  काष्ठा perf_event *event)
अणु
	काष्ठा hw_perf_event *hwc = &event->hw;
	काष्ठा hw_perf_event_extra *reg1 = &hwc->extra_reg;

	अगर (reg1->idx != EXTRA_REG_NONE) अणु
		u64 filter = uncore_shared_reg_config(box, 0);
		wrmsrl(reg1->reg, filter & 0xffffffff);
		wrmsrl(reg1->reg + 1, filter >> 32);
	पूर्ण

	wrmsrl(hwc->config_base, hwc->config | SNBEP_PMON_CTL_EN);
पूर्ण

अटल काष्ठा पूर्णांकel_uncore_ops hswep_uncore_cbox_ops = अणु
	.init_box		= snbep_uncore_msr_init_box,
	.disable_box		= snbep_uncore_msr_disable_box,
	.enable_box		= snbep_uncore_msr_enable_box,
	.disable_event		= snbep_uncore_msr_disable_event,
	.enable_event		= hswep_cbox_enable_event,
	.पढ़ो_counter		= uncore_msr_पढ़ो_counter,
	.hw_config		= hswep_cbox_hw_config,
	.get_स्थिरraपूर्णांक		= hswep_cbox_get_स्थिरraपूर्णांक,
	.put_स्थिरraपूर्णांक		= snbep_cbox_put_स्थिरraपूर्णांक,
पूर्ण;

अटल काष्ठा पूर्णांकel_uncore_type hswep_uncore_cbox = अणु
	.name			= "cbox",
	.num_counters		= 4,
	.num_boxes		= 18,
	.perf_ctr_bits		= 48,
	.event_ctl		= HSWEP_C0_MSR_PMON_CTL0,
	.perf_ctr		= HSWEP_C0_MSR_PMON_CTR0,
	.event_mask		= SNBEP_CBO_MSR_PMON_RAW_EVENT_MASK,
	.box_ctl		= HSWEP_C0_MSR_PMON_BOX_CTL,
	.msr_offset		= HSWEP_CBO_MSR_OFFSET,
	.num_shared_regs	= 1,
	.स्थिरraपूर्णांकs		= hswep_uncore_cbox_स्थिरraपूर्णांकs,
	.ops			= &hswep_uncore_cbox_ops,
	.क्रमmat_group		= &hswep_uncore_cbox_क्रमmat_group,
पूर्ण;

/*
 * Write SBOX Initialization रेजिस्टर bit by bit to aव्योम spurious #GPs
 */
अटल व्योम hswep_uncore_sbox_msr_init_box(काष्ठा पूर्णांकel_uncore_box *box)
अणु
	अचिन्हित msr = uncore_msr_box_ctl(box);

	अगर (msr) अणु
		u64 init = SNBEP_PMON_BOX_CTL_INT;
		u64 flags = 0;
		पूर्णांक i;

		क्रम_each_set_bit(i, (अचिन्हित दीर्घ *)&init, 64) अणु
			flags |= (1ULL << i);
			wrmsrl(msr, flags);
		पूर्ण
	पूर्ण
पूर्ण

अटल काष्ठा पूर्णांकel_uncore_ops hswep_uncore_sbox_msr_ops = अणु
	__SNBEP_UNCORE_MSR_OPS_COMMON_INIT(),
	.init_box		= hswep_uncore_sbox_msr_init_box
पूर्ण;

अटल काष्ठा attribute *hswep_uncore_sbox_क्रमmats_attr[] = अणु
	&क्रमmat_attr_event.attr,
	&क्रमmat_attr_umask.attr,
	&क्रमmat_attr_edge.attr,
	&क्रमmat_attr_tid_en.attr,
	&क्रमmat_attr_inv.attr,
	&क्रमmat_attr_thresh8.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group hswep_uncore_sbox_क्रमmat_group = अणु
	.name = "format",
	.attrs = hswep_uncore_sbox_क्रमmats_attr,
पूर्ण;

अटल काष्ठा पूर्णांकel_uncore_type hswep_uncore_sbox = अणु
	.name			= "sbox",
	.num_counters		= 4,
	.num_boxes		= 4,
	.perf_ctr_bits		= 44,
	.event_ctl		= HSWEP_S0_MSR_PMON_CTL0,
	.perf_ctr		= HSWEP_S0_MSR_PMON_CTR0,
	.event_mask		= HSWEP_S_MSR_PMON_RAW_EVENT_MASK,
	.box_ctl		= HSWEP_S0_MSR_PMON_BOX_CTL,
	.msr_offset		= HSWEP_SBOX_MSR_OFFSET,
	.ops			= &hswep_uncore_sbox_msr_ops,
	.क्रमmat_group		= &hswep_uncore_sbox_क्रमmat_group,
पूर्ण;

अटल पूर्णांक hswep_pcu_hw_config(काष्ठा पूर्णांकel_uncore_box *box, काष्ठा perf_event *event)
अणु
	काष्ठा hw_perf_event *hwc = &event->hw;
	काष्ठा hw_perf_event_extra *reg1 = &hwc->extra_reg;
	पूर्णांक ev_sel = hwc->config & SNBEP_PMON_CTL_EV_SEL_MASK;

	अगर (ev_sel >= 0xb && ev_sel <= 0xe) अणु
		reg1->reg = HSWEP_PCU_MSR_PMON_BOX_FILTER;
		reg1->idx = ev_sel - 0xb;
		reg1->config = event->attr.config1 & (0xff << reg1->idx);
	पूर्ण
	वापस 0;
पूर्ण

अटल काष्ठा पूर्णांकel_uncore_ops hswep_uncore_pcu_ops = अणु
	SNBEP_UNCORE_MSR_OPS_COMMON_INIT(),
	.hw_config		= hswep_pcu_hw_config,
	.get_स्थिरraपूर्णांक		= snbep_pcu_get_स्थिरraपूर्णांक,
	.put_स्थिरraपूर्णांक		= snbep_pcu_put_स्थिरraपूर्णांक,
पूर्ण;

अटल काष्ठा पूर्णांकel_uncore_type hswep_uncore_pcu = अणु
	.name			= "pcu",
	.num_counters		= 4,
	.num_boxes		= 1,
	.perf_ctr_bits		= 48,
	.perf_ctr		= HSWEP_PCU_MSR_PMON_CTR0,
	.event_ctl		= HSWEP_PCU_MSR_PMON_CTL0,
	.event_mask		= SNBEP_PCU_MSR_PMON_RAW_EVENT_MASK,
	.box_ctl		= HSWEP_PCU_MSR_PMON_BOX_CTL,
	.num_shared_regs	= 1,
	.ops			= &hswep_uncore_pcu_ops,
	.क्रमmat_group		= &snbep_uncore_pcu_क्रमmat_group,
पूर्ण;

अटल काष्ठा पूर्णांकel_uncore_type *hswep_msr_uncores[] = अणु
	&hswep_uncore_ubox,
	&hswep_uncore_cbox,
	&hswep_uncore_sbox,
	&hswep_uncore_pcu,
	शून्य,
पूर्ण;

#घोषणा HSWEP_PCU_DID			0x2fc0
#घोषणा HSWEP_PCU_CAPID4_OFFET		0x94
#घोषणा hswep_get_chop(_cap)		(((_cap) >> 6) & 0x3)

अटल bool hswep_has_limit_sbox(अचिन्हित पूर्णांक device)
अणु
	काष्ठा pci_dev *dev = pci_get_device(PCI_VENDOR_ID_INTEL, device, शून्य);
	u32 capid4;

	अगर (!dev)
		वापस false;

	pci_पढ़ो_config_dword(dev, HSWEP_PCU_CAPID4_OFFET, &capid4);
	अगर (!hswep_get_chop(capid4))
		वापस true;

	वापस false;
पूर्ण

व्योम hswep_uncore_cpu_init(व्योम)
अणु
	अगर (hswep_uncore_cbox.num_boxes > boot_cpu_data.x86_max_cores)
		hswep_uncore_cbox.num_boxes = boot_cpu_data.x86_max_cores;

	/* Detect 6-8 core प्रणालीs with only two SBOXes */
	अगर (hswep_has_limit_sbox(HSWEP_PCU_DID))
		hswep_uncore_sbox.num_boxes = 2;

	uncore_msr_uncores = hswep_msr_uncores;
पूर्ण

अटल काष्ठा पूर्णांकel_uncore_type hswep_uncore_ha = अणु
	.name		= "ha",
	.num_counters   = 4,
	.num_boxes	= 2,
	.perf_ctr_bits	= 48,
	SNBEP_UNCORE_PCI_COMMON_INIT(),
पूर्ण;

अटल काष्ठा uncore_event_desc hswep_uncore_imc_events[] = अणु
	INTEL_UNCORE_EVENT_DESC(घड़ीticks,      "event=0x00,umask=0x00"),
	INTEL_UNCORE_EVENT_DESC(cas_count_पढ़ो,  "event=0x04,umask=0x03"),
	INTEL_UNCORE_EVENT_DESC(cas_count_पढ़ो.scale, "6.103515625e-5"),
	INTEL_UNCORE_EVENT_DESC(cas_count_पढ़ो.unit, "MiB"),
	INTEL_UNCORE_EVENT_DESC(cas_count_ग_लिखो, "event=0x04,umask=0x0c"),
	INTEL_UNCORE_EVENT_DESC(cas_count_ग_लिखो.scale, "6.103515625e-5"),
	INTEL_UNCORE_EVENT_DESC(cas_count_ग_लिखो.unit, "MiB"),
	अणु /* end: all zeroes */ पूर्ण,
पूर्ण;

अटल काष्ठा पूर्णांकel_uncore_type hswep_uncore_imc = अणु
	.name		= "imc",
	.num_counters   = 4,
	.num_boxes	= 8,
	.perf_ctr_bits	= 48,
	.fixed_ctr_bits	= 48,
	.fixed_ctr	= SNBEP_MC_CHy_PCI_PMON_FIXED_CTR,
	.fixed_ctl	= SNBEP_MC_CHy_PCI_PMON_FIXED_CTL,
	.event_descs	= hswep_uncore_imc_events,
	SNBEP_UNCORE_PCI_COMMON_INIT(),
पूर्ण;

अटल अचिन्हित hswep_uncore_irp_ctrs[] = अणु0xa0, 0xa8, 0xb0, 0xb8पूर्ण;

अटल u64 hswep_uncore_irp_पढ़ो_counter(काष्ठा पूर्णांकel_uncore_box *box, काष्ठा perf_event *event)
अणु
	काष्ठा pci_dev *pdev = box->pci_dev;
	काष्ठा hw_perf_event *hwc = &event->hw;
	u64 count = 0;

	pci_पढ़ो_config_dword(pdev, hswep_uncore_irp_ctrs[hwc->idx], (u32 *)&count);
	pci_पढ़ो_config_dword(pdev, hswep_uncore_irp_ctrs[hwc->idx] + 4, (u32 *)&count + 1);

	वापस count;
पूर्ण

अटल काष्ठा पूर्णांकel_uncore_ops hswep_uncore_irp_ops = अणु
	.init_box	= snbep_uncore_pci_init_box,
	.disable_box	= snbep_uncore_pci_disable_box,
	.enable_box	= snbep_uncore_pci_enable_box,
	.disable_event	= ivbep_uncore_irp_disable_event,
	.enable_event	= ivbep_uncore_irp_enable_event,
	.पढ़ो_counter	= hswep_uncore_irp_पढ़ो_counter,
पूर्ण;

अटल काष्ठा पूर्णांकel_uncore_type hswep_uncore_irp = अणु
	.name			= "irp",
	.num_counters		= 4,
	.num_boxes		= 1,
	.perf_ctr_bits		= 48,
	.event_mask		= SNBEP_PMON_RAW_EVENT_MASK,
	.box_ctl		= SNBEP_PCI_PMON_BOX_CTL,
	.ops			= &hswep_uncore_irp_ops,
	.क्रमmat_group		= &snbep_uncore_क्रमmat_group,
पूर्ण;

अटल काष्ठा पूर्णांकel_uncore_type hswep_uncore_qpi = अणु
	.name			= "qpi",
	.num_counters		= 4,
	.num_boxes		= 3,
	.perf_ctr_bits		= 48,
	.perf_ctr		= SNBEP_PCI_PMON_CTR0,
	.event_ctl		= SNBEP_PCI_PMON_CTL0,
	.event_mask		= SNBEP_QPI_PCI_PMON_RAW_EVENT_MASK,
	.box_ctl		= SNBEP_PCI_PMON_BOX_CTL,
	.num_shared_regs	= 1,
	.ops			= &snbep_uncore_qpi_ops,
	.क्रमmat_group		= &snbep_uncore_qpi_क्रमmat_group,
पूर्ण;

अटल काष्ठा event_स्थिरraपूर्णांक hswep_uncore_r2pcie_स्थिरraपूर्णांकs[] = अणु
	UNCORE_EVENT_CONSTRAINT(0x10, 0x3),
	UNCORE_EVENT_CONSTRAINT(0x11, 0x3),
	UNCORE_EVENT_CONSTRAINT(0x13, 0x1),
	UNCORE_EVENT_CONSTRAINT(0x23, 0x1),
	UNCORE_EVENT_CONSTRAINT(0x24, 0x1),
	UNCORE_EVENT_CONSTRAINT(0x25, 0x1),
	UNCORE_EVENT_CONSTRAINT(0x26, 0x3),
	UNCORE_EVENT_CONSTRAINT(0x27, 0x1),
	UNCORE_EVENT_CONSTRAINT(0x28, 0x3),
	UNCORE_EVENT_CONSTRAINT(0x29, 0x3),
	UNCORE_EVENT_CONSTRAINT(0x2a, 0x1),
	UNCORE_EVENT_CONSTRAINT(0x2b, 0x3),
	UNCORE_EVENT_CONSTRAINT(0x2c, 0x3),
	UNCORE_EVENT_CONSTRAINT(0x2d, 0x3),
	UNCORE_EVENT_CONSTRAINT(0x32, 0x3),
	UNCORE_EVENT_CONSTRAINT(0x33, 0x3),
	UNCORE_EVENT_CONSTRAINT(0x34, 0x3),
	UNCORE_EVENT_CONSTRAINT(0x35, 0x3),
	EVENT_CONSTRAINT_END
पूर्ण;

अटल काष्ठा पूर्णांकel_uncore_type hswep_uncore_r2pcie = अणु
	.name		= "r2pcie",
	.num_counters   = 4,
	.num_boxes	= 1,
	.perf_ctr_bits	= 48,
	.स्थिरraपूर्णांकs	= hswep_uncore_r2pcie_स्थिरraपूर्णांकs,
	SNBEP_UNCORE_PCI_COMMON_INIT(),
पूर्ण;

अटल काष्ठा event_स्थिरraपूर्णांक hswep_uncore_r3qpi_स्थिरraपूर्णांकs[] = अणु
	UNCORE_EVENT_CONSTRAINT(0x01, 0x3),
	UNCORE_EVENT_CONSTRAINT(0x07, 0x7),
	UNCORE_EVENT_CONSTRAINT(0x08, 0x7),
	UNCORE_EVENT_CONSTRAINT(0x09, 0x7),
	UNCORE_EVENT_CONSTRAINT(0x0a, 0x7),
	UNCORE_EVENT_CONSTRAINT(0x0e, 0x7),
	UNCORE_EVENT_CONSTRAINT(0x10, 0x3),
	UNCORE_EVENT_CONSTRAINT(0x11, 0x3),
	UNCORE_EVENT_CONSTRAINT(0x12, 0x3),
	UNCORE_EVENT_CONSTRAINT(0x13, 0x1),
	UNCORE_EVENT_CONSTRAINT(0x14, 0x3),
	UNCORE_EVENT_CONSTRAINT(0x15, 0x3),
	UNCORE_EVENT_CONSTRAINT(0x1f, 0x3),
	UNCORE_EVENT_CONSTRAINT(0x20, 0x3),
	UNCORE_EVENT_CONSTRAINT(0x21, 0x3),
	UNCORE_EVENT_CONSTRAINT(0x22, 0x3),
	UNCORE_EVENT_CONSTRAINT(0x23, 0x3),
	UNCORE_EVENT_CONSTRAINT(0x25, 0x3),
	UNCORE_EVENT_CONSTRAINT(0x26, 0x3),
	UNCORE_EVENT_CONSTRAINT(0x28, 0x3),
	UNCORE_EVENT_CONSTRAINT(0x29, 0x3),
	UNCORE_EVENT_CONSTRAINT(0x2c, 0x3),
	UNCORE_EVENT_CONSTRAINT(0x2d, 0x3),
	UNCORE_EVENT_CONSTRAINT(0x2e, 0x3),
	UNCORE_EVENT_CONSTRAINT(0x2f, 0x3),
	UNCORE_EVENT_CONSTRAINT(0x31, 0x3),
	UNCORE_EVENT_CONSTRAINT(0x32, 0x3),
	UNCORE_EVENT_CONSTRAINT(0x33, 0x3),
	UNCORE_EVENT_CONSTRAINT(0x34, 0x3),
	UNCORE_EVENT_CONSTRAINT(0x36, 0x3),
	UNCORE_EVENT_CONSTRAINT(0x37, 0x3),
	UNCORE_EVENT_CONSTRAINT(0x38, 0x3),
	UNCORE_EVENT_CONSTRAINT(0x39, 0x3),
	EVENT_CONSTRAINT_END
पूर्ण;

अटल काष्ठा पूर्णांकel_uncore_type hswep_uncore_r3qpi = अणु
	.name		= "r3qpi",
	.num_counters   = 3,
	.num_boxes	= 3,
	.perf_ctr_bits	= 44,
	.स्थिरraपूर्णांकs	= hswep_uncore_r3qpi_स्थिरraपूर्णांकs,
	SNBEP_UNCORE_PCI_COMMON_INIT(),
पूर्ण;

क्रमागत अणु
	HSWEP_PCI_UNCORE_HA,
	HSWEP_PCI_UNCORE_IMC,
	HSWEP_PCI_UNCORE_IRP,
	HSWEP_PCI_UNCORE_QPI,
	HSWEP_PCI_UNCORE_R2PCIE,
	HSWEP_PCI_UNCORE_R3QPI,
पूर्ण;

अटल काष्ठा पूर्णांकel_uncore_type *hswep_pci_uncores[] = अणु
	[HSWEP_PCI_UNCORE_HA]	= &hswep_uncore_ha,
	[HSWEP_PCI_UNCORE_IMC]	= &hswep_uncore_imc,
	[HSWEP_PCI_UNCORE_IRP]	= &hswep_uncore_irp,
	[HSWEP_PCI_UNCORE_QPI]	= &hswep_uncore_qpi,
	[HSWEP_PCI_UNCORE_R2PCIE]	= &hswep_uncore_r2pcie,
	[HSWEP_PCI_UNCORE_R3QPI]	= &hswep_uncore_r3qpi,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा pci_device_id hswep_uncore_pci_ids[] = अणु
	अणु /* Home Agent 0 */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, 0x2f30),
		.driver_data = UNCORE_PCI_DEV_DATA(HSWEP_PCI_UNCORE_HA, 0),
	पूर्ण,
	अणु /* Home Agent 1 */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, 0x2f38),
		.driver_data = UNCORE_PCI_DEV_DATA(HSWEP_PCI_UNCORE_HA, 1),
	पूर्ण,
	अणु /* MC0 Channel 0 */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, 0x2fb0),
		.driver_data = UNCORE_PCI_DEV_DATA(HSWEP_PCI_UNCORE_IMC, 0),
	पूर्ण,
	अणु /* MC0 Channel 1 */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, 0x2fb1),
		.driver_data = UNCORE_PCI_DEV_DATA(HSWEP_PCI_UNCORE_IMC, 1),
	पूर्ण,
	अणु /* MC0 Channel 2 */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, 0x2fb4),
		.driver_data = UNCORE_PCI_DEV_DATA(HSWEP_PCI_UNCORE_IMC, 2),
	पूर्ण,
	अणु /* MC0 Channel 3 */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, 0x2fb5),
		.driver_data = UNCORE_PCI_DEV_DATA(HSWEP_PCI_UNCORE_IMC, 3),
	पूर्ण,
	अणु /* MC1 Channel 0 */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, 0x2fd0),
		.driver_data = UNCORE_PCI_DEV_DATA(HSWEP_PCI_UNCORE_IMC, 4),
	पूर्ण,
	अणु /* MC1 Channel 1 */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, 0x2fd1),
		.driver_data = UNCORE_PCI_DEV_DATA(HSWEP_PCI_UNCORE_IMC, 5),
	पूर्ण,
	अणु /* MC1 Channel 2 */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, 0x2fd4),
		.driver_data = UNCORE_PCI_DEV_DATA(HSWEP_PCI_UNCORE_IMC, 6),
	पूर्ण,
	अणु /* MC1 Channel 3 */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, 0x2fd5),
		.driver_data = UNCORE_PCI_DEV_DATA(HSWEP_PCI_UNCORE_IMC, 7),
	पूर्ण,
	अणु /* IRP */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, 0x2f39),
		.driver_data = UNCORE_PCI_DEV_DATA(HSWEP_PCI_UNCORE_IRP, 0),
	पूर्ण,
	अणु /* QPI0 Port 0 */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, 0x2f32),
		.driver_data = UNCORE_PCI_DEV_DATA(HSWEP_PCI_UNCORE_QPI, 0),
	पूर्ण,
	अणु /* QPI0 Port 1 */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, 0x2f33),
		.driver_data = UNCORE_PCI_DEV_DATA(HSWEP_PCI_UNCORE_QPI, 1),
	पूर्ण,
	अणु /* QPI1 Port 2 */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, 0x2f3a),
		.driver_data = UNCORE_PCI_DEV_DATA(HSWEP_PCI_UNCORE_QPI, 2),
	पूर्ण,
	अणु /* R2PCIe */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, 0x2f34),
		.driver_data = UNCORE_PCI_DEV_DATA(HSWEP_PCI_UNCORE_R2PCIE, 0),
	पूर्ण,
	अणु /* R3QPI0 Link 0 */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, 0x2f36),
		.driver_data = UNCORE_PCI_DEV_DATA(HSWEP_PCI_UNCORE_R3QPI, 0),
	पूर्ण,
	अणु /* R3QPI0 Link 1 */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, 0x2f37),
		.driver_data = UNCORE_PCI_DEV_DATA(HSWEP_PCI_UNCORE_R3QPI, 1),
	पूर्ण,
	अणु /* R3QPI1 Link 2 */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, 0x2f3e),
		.driver_data = UNCORE_PCI_DEV_DATA(HSWEP_PCI_UNCORE_R3QPI, 2),
	पूर्ण,
	अणु /* QPI Port 0 filter  */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, 0x2f86),
		.driver_data = UNCORE_PCI_DEV_DATA(UNCORE_EXTRA_PCI_DEV,
						   SNBEP_PCI_QPI_PORT0_FILTER),
	पूर्ण,
	अणु /* QPI Port 1 filter  */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, 0x2f96),
		.driver_data = UNCORE_PCI_DEV_DATA(UNCORE_EXTRA_PCI_DEV,
						   SNBEP_PCI_QPI_PORT1_FILTER),
	पूर्ण,
	अणु /* end: all zeroes */ पूर्ण
पूर्ण;

अटल काष्ठा pci_driver hswep_uncore_pci_driver = अणु
	.name		= "hswep_uncore",
	.id_table	= hswep_uncore_pci_ids,
पूर्ण;

पूर्णांक hswep_uncore_pci_init(व्योम)
अणु
	पूर्णांक ret = snbep_pci2phy_map_init(0x2f1e, SNBEP_CPUNODEID, SNBEP_GIDNIDMAP, true);
	अगर (ret)
		वापस ret;
	uncore_pci_uncores = hswep_pci_uncores;
	uncore_pci_driver = &hswep_uncore_pci_driver;
	वापस 0;
पूर्ण
/* end of Haswell-EP uncore support */

/* BDX uncore support */

अटल काष्ठा पूर्णांकel_uncore_type bdx_uncore_ubox = अणु
	.name			= "ubox",
	.num_counters		= 2,
	.num_boxes		= 1,
	.perf_ctr_bits		= 48,
	.fixed_ctr_bits		= 48,
	.perf_ctr		= HSWEP_U_MSR_PMON_CTR0,
	.event_ctl		= HSWEP_U_MSR_PMON_CTL0,
	.event_mask		= SNBEP_U_MSR_PMON_RAW_EVENT_MASK,
	.fixed_ctr		= HSWEP_U_MSR_PMON_UCLK_FIXED_CTR,
	.fixed_ctl		= HSWEP_U_MSR_PMON_UCLK_FIXED_CTL,
	.num_shared_regs	= 1,
	.ops			= &ivbep_uncore_msr_ops,
	.क्रमmat_group		= &ivbep_uncore_ubox_क्रमmat_group,
पूर्ण;

अटल काष्ठा event_स्थिरraपूर्णांक bdx_uncore_cbox_स्थिरraपूर्णांकs[] = अणु
	UNCORE_EVENT_CONSTRAINT(0x09, 0x3),
	UNCORE_EVENT_CONSTRAINT(0x11, 0x1),
	UNCORE_EVENT_CONSTRAINT(0x36, 0x1),
	UNCORE_EVENT_CONSTRAINT(0x3e, 0x1),
	EVENT_CONSTRAINT_END
पूर्ण;

अटल काष्ठा पूर्णांकel_uncore_type bdx_uncore_cbox = अणु
	.name			= "cbox",
	.num_counters		= 4,
	.num_boxes		= 24,
	.perf_ctr_bits		= 48,
	.event_ctl		= HSWEP_C0_MSR_PMON_CTL0,
	.perf_ctr		= HSWEP_C0_MSR_PMON_CTR0,
	.event_mask		= SNBEP_CBO_MSR_PMON_RAW_EVENT_MASK,
	.box_ctl		= HSWEP_C0_MSR_PMON_BOX_CTL,
	.msr_offset		= HSWEP_CBO_MSR_OFFSET,
	.num_shared_regs	= 1,
	.स्थिरraपूर्णांकs		= bdx_uncore_cbox_स्थिरraपूर्णांकs,
	.ops			= &hswep_uncore_cbox_ops,
	.क्रमmat_group		= &hswep_uncore_cbox_क्रमmat_group,
पूर्ण;

अटल काष्ठा पूर्णांकel_uncore_type bdx_uncore_sbox = अणु
	.name			= "sbox",
	.num_counters		= 4,
	.num_boxes		= 4,
	.perf_ctr_bits		= 48,
	.event_ctl		= HSWEP_S0_MSR_PMON_CTL0,
	.perf_ctr		= HSWEP_S0_MSR_PMON_CTR0,
	.event_mask		= HSWEP_S_MSR_PMON_RAW_EVENT_MASK,
	.box_ctl		= HSWEP_S0_MSR_PMON_BOX_CTL,
	.msr_offset		= HSWEP_SBOX_MSR_OFFSET,
	.ops			= &hswep_uncore_sbox_msr_ops,
	.क्रमmat_group		= &hswep_uncore_sbox_क्रमmat_group,
पूर्ण;

#घोषणा BDX_MSR_UNCORE_SBOX	3

अटल काष्ठा पूर्णांकel_uncore_type *bdx_msr_uncores[] = अणु
	&bdx_uncore_ubox,
	&bdx_uncore_cbox,
	&hswep_uncore_pcu,
	&bdx_uncore_sbox,
	शून्य,
पूर्ण;

/* Bit 7 'Use Occupancy' is not available क्रम counter 0 on BDX */
अटल काष्ठा event_स्थिरraपूर्णांक bdx_uncore_pcu_स्थिरraपूर्णांकs[] = अणु
	EVENT_CONSTRAINT(0x80, 0xe, 0x80),
	EVENT_CONSTRAINT_END
पूर्ण;

#घोषणा BDX_PCU_DID			0x6fc0

व्योम bdx_uncore_cpu_init(व्योम)
अणु
	अगर (bdx_uncore_cbox.num_boxes > boot_cpu_data.x86_max_cores)
		bdx_uncore_cbox.num_boxes = boot_cpu_data.x86_max_cores;
	uncore_msr_uncores = bdx_msr_uncores;

	/* Detect प्रणालीs with no SBOXes */
	अगर ((boot_cpu_data.x86_model == 86) || hswep_has_limit_sbox(BDX_PCU_DID))
		uncore_msr_uncores[BDX_MSR_UNCORE_SBOX] = शून्य;

	hswep_uncore_pcu.स्थिरraपूर्णांकs = bdx_uncore_pcu_स्थिरraपूर्णांकs;
पूर्ण

अटल काष्ठा पूर्णांकel_uncore_type bdx_uncore_ha = अणु
	.name		= "ha",
	.num_counters   = 4,
	.num_boxes	= 2,
	.perf_ctr_bits	= 48,
	SNBEP_UNCORE_PCI_COMMON_INIT(),
पूर्ण;

अटल काष्ठा पूर्णांकel_uncore_type bdx_uncore_imc = अणु
	.name		= "imc",
	.num_counters   = 4,
	.num_boxes	= 8,
	.perf_ctr_bits	= 48,
	.fixed_ctr_bits	= 48,
	.fixed_ctr	= SNBEP_MC_CHy_PCI_PMON_FIXED_CTR,
	.fixed_ctl	= SNBEP_MC_CHy_PCI_PMON_FIXED_CTL,
	.event_descs	= hswep_uncore_imc_events,
	SNBEP_UNCORE_PCI_COMMON_INIT(),
पूर्ण;

अटल काष्ठा पूर्णांकel_uncore_type bdx_uncore_irp = अणु
	.name			= "irp",
	.num_counters		= 4,
	.num_boxes		= 1,
	.perf_ctr_bits		= 48,
	.event_mask		= SNBEP_PMON_RAW_EVENT_MASK,
	.box_ctl		= SNBEP_PCI_PMON_BOX_CTL,
	.ops			= &hswep_uncore_irp_ops,
	.क्रमmat_group		= &snbep_uncore_क्रमmat_group,
पूर्ण;

अटल काष्ठा पूर्णांकel_uncore_type bdx_uncore_qpi = अणु
	.name			= "qpi",
	.num_counters		= 4,
	.num_boxes		= 3,
	.perf_ctr_bits		= 48,
	.perf_ctr		= SNBEP_PCI_PMON_CTR0,
	.event_ctl		= SNBEP_PCI_PMON_CTL0,
	.event_mask		= SNBEP_QPI_PCI_PMON_RAW_EVENT_MASK,
	.box_ctl		= SNBEP_PCI_PMON_BOX_CTL,
	.num_shared_regs	= 1,
	.ops			= &snbep_uncore_qpi_ops,
	.क्रमmat_group		= &snbep_uncore_qpi_क्रमmat_group,
पूर्ण;

अटल काष्ठा event_स्थिरraपूर्णांक bdx_uncore_r2pcie_स्थिरraपूर्णांकs[] = अणु
	UNCORE_EVENT_CONSTRAINT(0x10, 0x3),
	UNCORE_EVENT_CONSTRAINT(0x11, 0x3),
	UNCORE_EVENT_CONSTRAINT(0x13, 0x1),
	UNCORE_EVENT_CONSTRAINT(0x23, 0x1),
	UNCORE_EVENT_CONSTRAINT(0x25, 0x1),
	UNCORE_EVENT_CONSTRAINT(0x26, 0x3),
	UNCORE_EVENT_CONSTRAINT(0x28, 0x3),
	UNCORE_EVENT_CONSTRAINT(0x2c, 0x3),
	UNCORE_EVENT_CONSTRAINT(0x2d, 0x3),
	EVENT_CONSTRAINT_END
पूर्ण;

अटल काष्ठा पूर्णांकel_uncore_type bdx_uncore_r2pcie = अणु
	.name		= "r2pcie",
	.num_counters   = 4,
	.num_boxes	= 1,
	.perf_ctr_bits	= 48,
	.स्थिरraपूर्णांकs	= bdx_uncore_r2pcie_स्थिरraपूर्णांकs,
	SNBEP_UNCORE_PCI_COMMON_INIT(),
पूर्ण;

अटल काष्ठा event_स्थिरraपूर्णांक bdx_uncore_r3qpi_स्थिरraपूर्णांकs[] = अणु
	UNCORE_EVENT_CONSTRAINT(0x01, 0x7),
	UNCORE_EVENT_CONSTRAINT(0x07, 0x7),
	UNCORE_EVENT_CONSTRAINT(0x08, 0x7),
	UNCORE_EVENT_CONSTRAINT(0x09, 0x7),
	UNCORE_EVENT_CONSTRAINT(0x0a, 0x7),
	UNCORE_EVENT_CONSTRAINT(0x0e, 0x7),
	UNCORE_EVENT_CONSTRAINT(0x10, 0x3),
	UNCORE_EVENT_CONSTRAINT(0x11, 0x3),
	UNCORE_EVENT_CONSTRAINT(0x13, 0x1),
	UNCORE_EVENT_CONSTRAINT(0x14, 0x3),
	UNCORE_EVENT_CONSTRAINT(0x15, 0x3),
	UNCORE_EVENT_CONSTRAINT(0x1f, 0x3),
	UNCORE_EVENT_CONSTRAINT(0x20, 0x3),
	UNCORE_EVENT_CONSTRAINT(0x21, 0x3),
	UNCORE_EVENT_CONSTRAINT(0x22, 0x3),
	UNCORE_EVENT_CONSTRAINT(0x23, 0x3),
	UNCORE_EVENT_CONSTRAINT(0x25, 0x3),
	UNCORE_EVENT_CONSTRAINT(0x26, 0x3),
	UNCORE_EVENT_CONSTRAINT(0x28, 0x3),
	UNCORE_EVENT_CONSTRAINT(0x29, 0x3),
	UNCORE_EVENT_CONSTRAINT(0x2c, 0x3),
	UNCORE_EVENT_CONSTRAINT(0x2d, 0x3),
	UNCORE_EVENT_CONSTRAINT(0x2e, 0x3),
	UNCORE_EVENT_CONSTRAINT(0x2f, 0x3),
	UNCORE_EVENT_CONSTRAINT(0x33, 0x3),
	UNCORE_EVENT_CONSTRAINT(0x34, 0x3),
	UNCORE_EVENT_CONSTRAINT(0x36, 0x3),
	UNCORE_EVENT_CONSTRAINT(0x37, 0x3),
	UNCORE_EVENT_CONSTRAINT(0x38, 0x3),
	UNCORE_EVENT_CONSTRAINT(0x39, 0x3),
	EVENT_CONSTRAINT_END
पूर्ण;

अटल काष्ठा पूर्णांकel_uncore_type bdx_uncore_r3qpi = अणु
	.name		= "r3qpi",
	.num_counters   = 3,
	.num_boxes	= 3,
	.perf_ctr_bits	= 48,
	.स्थिरraपूर्णांकs	= bdx_uncore_r3qpi_स्थिरraपूर्णांकs,
	SNBEP_UNCORE_PCI_COMMON_INIT(),
पूर्ण;

क्रमागत अणु
	BDX_PCI_UNCORE_HA,
	BDX_PCI_UNCORE_IMC,
	BDX_PCI_UNCORE_IRP,
	BDX_PCI_UNCORE_QPI,
	BDX_PCI_UNCORE_R2PCIE,
	BDX_PCI_UNCORE_R3QPI,
पूर्ण;

अटल काष्ठा पूर्णांकel_uncore_type *bdx_pci_uncores[] = अणु
	[BDX_PCI_UNCORE_HA]	= &bdx_uncore_ha,
	[BDX_PCI_UNCORE_IMC]	= &bdx_uncore_imc,
	[BDX_PCI_UNCORE_IRP]	= &bdx_uncore_irp,
	[BDX_PCI_UNCORE_QPI]	= &bdx_uncore_qpi,
	[BDX_PCI_UNCORE_R2PCIE]	= &bdx_uncore_r2pcie,
	[BDX_PCI_UNCORE_R3QPI]	= &bdx_uncore_r3qpi,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा pci_device_id bdx_uncore_pci_ids[] = अणु
	अणु /* Home Agent 0 */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, 0x6f30),
		.driver_data = UNCORE_PCI_DEV_DATA(BDX_PCI_UNCORE_HA, 0),
	पूर्ण,
	अणु /* Home Agent 1 */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, 0x6f38),
		.driver_data = UNCORE_PCI_DEV_DATA(BDX_PCI_UNCORE_HA, 1),
	पूर्ण,
	अणु /* MC0 Channel 0 */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, 0x6fb0),
		.driver_data = UNCORE_PCI_DEV_DATA(BDX_PCI_UNCORE_IMC, 0),
	पूर्ण,
	अणु /* MC0 Channel 1 */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, 0x6fb1),
		.driver_data = UNCORE_PCI_DEV_DATA(BDX_PCI_UNCORE_IMC, 1),
	पूर्ण,
	अणु /* MC0 Channel 2 */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, 0x6fb4),
		.driver_data = UNCORE_PCI_DEV_DATA(BDX_PCI_UNCORE_IMC, 2),
	पूर्ण,
	अणु /* MC0 Channel 3 */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, 0x6fb5),
		.driver_data = UNCORE_PCI_DEV_DATA(BDX_PCI_UNCORE_IMC, 3),
	पूर्ण,
	अणु /* MC1 Channel 0 */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, 0x6fd0),
		.driver_data = UNCORE_PCI_DEV_DATA(BDX_PCI_UNCORE_IMC, 4),
	पूर्ण,
	अणु /* MC1 Channel 1 */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, 0x6fd1),
		.driver_data = UNCORE_PCI_DEV_DATA(BDX_PCI_UNCORE_IMC, 5),
	पूर्ण,
	अणु /* MC1 Channel 2 */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, 0x6fd4),
		.driver_data = UNCORE_PCI_DEV_DATA(BDX_PCI_UNCORE_IMC, 6),
	पूर्ण,
	अणु /* MC1 Channel 3 */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, 0x6fd5),
		.driver_data = UNCORE_PCI_DEV_DATA(BDX_PCI_UNCORE_IMC, 7),
	पूर्ण,
	अणु /* IRP */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, 0x6f39),
		.driver_data = UNCORE_PCI_DEV_DATA(BDX_PCI_UNCORE_IRP, 0),
	पूर्ण,
	अणु /* QPI0 Port 0 */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, 0x6f32),
		.driver_data = UNCORE_PCI_DEV_DATA(BDX_PCI_UNCORE_QPI, 0),
	पूर्ण,
	अणु /* QPI0 Port 1 */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, 0x6f33),
		.driver_data = UNCORE_PCI_DEV_DATA(BDX_PCI_UNCORE_QPI, 1),
	पूर्ण,
	अणु /* QPI1 Port 2 */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, 0x6f3a),
		.driver_data = UNCORE_PCI_DEV_DATA(BDX_PCI_UNCORE_QPI, 2),
	पूर्ण,
	अणु /* R2PCIe */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, 0x6f34),
		.driver_data = UNCORE_PCI_DEV_DATA(BDX_PCI_UNCORE_R2PCIE, 0),
	पूर्ण,
	अणु /* R3QPI0 Link 0 */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, 0x6f36),
		.driver_data = UNCORE_PCI_DEV_DATA(BDX_PCI_UNCORE_R3QPI, 0),
	पूर्ण,
	अणु /* R3QPI0 Link 1 */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, 0x6f37),
		.driver_data = UNCORE_PCI_DEV_DATA(BDX_PCI_UNCORE_R3QPI, 1),
	पूर्ण,
	अणु /* R3QPI1 Link 2 */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, 0x6f3e),
		.driver_data = UNCORE_PCI_DEV_DATA(BDX_PCI_UNCORE_R3QPI, 2),
	पूर्ण,
	अणु /* QPI Port 0 filter  */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, 0x6f86),
		.driver_data = UNCORE_PCI_DEV_DATA(UNCORE_EXTRA_PCI_DEV,
						   SNBEP_PCI_QPI_PORT0_FILTER),
	पूर्ण,
	अणु /* QPI Port 1 filter  */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, 0x6f96),
		.driver_data = UNCORE_PCI_DEV_DATA(UNCORE_EXTRA_PCI_DEV,
						   SNBEP_PCI_QPI_PORT1_FILTER),
	पूर्ण,
	अणु /* QPI Port 2 filter  */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, 0x6f46),
		.driver_data = UNCORE_PCI_DEV_DATA(UNCORE_EXTRA_PCI_DEV,
						   BDX_PCI_QPI_PORT2_FILTER),
	पूर्ण,
	अणु /* end: all zeroes */ पूर्ण
पूर्ण;

अटल काष्ठा pci_driver bdx_uncore_pci_driver = अणु
	.name		= "bdx_uncore",
	.id_table	= bdx_uncore_pci_ids,
पूर्ण;

पूर्णांक bdx_uncore_pci_init(व्योम)
अणु
	पूर्णांक ret = snbep_pci2phy_map_init(0x6f1e, SNBEP_CPUNODEID, SNBEP_GIDNIDMAP, true);

	अगर (ret)
		वापस ret;
	uncore_pci_uncores = bdx_pci_uncores;
	uncore_pci_driver = &bdx_uncore_pci_driver;
	वापस 0;
पूर्ण

/* end of BDX uncore support */

/* SKX uncore support */

अटल काष्ठा पूर्णांकel_uncore_type skx_uncore_ubox = अणु
	.name			= "ubox",
	.num_counters		= 2,
	.num_boxes		= 1,
	.perf_ctr_bits		= 48,
	.fixed_ctr_bits		= 48,
	.perf_ctr		= HSWEP_U_MSR_PMON_CTR0,
	.event_ctl		= HSWEP_U_MSR_PMON_CTL0,
	.event_mask		= SNBEP_U_MSR_PMON_RAW_EVENT_MASK,
	.fixed_ctr		= HSWEP_U_MSR_PMON_UCLK_FIXED_CTR,
	.fixed_ctl		= HSWEP_U_MSR_PMON_UCLK_FIXED_CTL,
	.ops			= &ivbep_uncore_msr_ops,
	.क्रमmat_group		= &ivbep_uncore_ubox_क्रमmat_group,
पूर्ण;

अटल काष्ठा attribute *skx_uncore_cha_क्रमmats_attr[] = अणु
	&क्रमmat_attr_event.attr,
	&क्रमmat_attr_umask.attr,
	&क्रमmat_attr_edge.attr,
	&क्रमmat_attr_tid_en.attr,
	&क्रमmat_attr_inv.attr,
	&क्रमmat_attr_thresh8.attr,
	&क्रमmat_attr_filter_tid4.attr,
	&क्रमmat_attr_filter_state5.attr,
	&क्रमmat_attr_filter_rem.attr,
	&क्रमmat_attr_filter_loc.attr,
	&क्रमmat_attr_filter_nm.attr,
	&क्रमmat_attr_filter_all_op.attr,
	&क्रमmat_attr_filter_not_nm.attr,
	&क्रमmat_attr_filter_opc_0.attr,
	&क्रमmat_attr_filter_opc_1.attr,
	&क्रमmat_attr_filter_nc.attr,
	&क्रमmat_attr_filter_isoc.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group skx_uncore_chabox_क्रमmat_group = अणु
	.name = "format",
	.attrs = skx_uncore_cha_क्रमmats_attr,
पूर्ण;

अटल काष्ठा event_स्थिरraपूर्णांक skx_uncore_chabox_स्थिरraपूर्णांकs[] = अणु
	UNCORE_EVENT_CONSTRAINT(0x11, 0x1),
	UNCORE_EVENT_CONSTRAINT(0x36, 0x1),
	EVENT_CONSTRAINT_END
पूर्ण;

अटल काष्ठा extra_reg skx_uncore_cha_extra_regs[] = अणु
	SNBEP_CBO_EVENT_EXTRA_REG(0x0334, 0xffff, 0x4),
	SNBEP_CBO_EVENT_EXTRA_REG(0x0534, 0xffff, 0x4),
	SNBEP_CBO_EVENT_EXTRA_REG(0x0934, 0xffff, 0x4),
	SNBEP_CBO_EVENT_EXTRA_REG(0x1134, 0xffff, 0x4),
	SNBEP_CBO_EVENT_EXTRA_REG(0x3134, 0xffff, 0x4),
	SNBEP_CBO_EVENT_EXTRA_REG(0x9134, 0xffff, 0x4),
	SNBEP_CBO_EVENT_EXTRA_REG(0x35, 0xff, 0x8),
	SNBEP_CBO_EVENT_EXTRA_REG(0x36, 0xff, 0x8),
	SNBEP_CBO_EVENT_EXTRA_REG(0x38, 0xff, 0x3),
	EVENT_EXTRA_END
पूर्ण;

अटल u64 skx_cha_filter_mask(पूर्णांक fields)
अणु
	u64 mask = 0;

	अगर (fields & 0x1)
		mask |= SKX_CHA_MSR_PMON_BOX_FILTER_TID;
	अगर (fields & 0x2)
		mask |= SKX_CHA_MSR_PMON_BOX_FILTER_LINK;
	अगर (fields & 0x4)
		mask |= SKX_CHA_MSR_PMON_BOX_FILTER_STATE;
	अगर (fields & 0x8) अणु
		mask |= SKX_CHA_MSR_PMON_BOX_FILTER_REM;
		mask |= SKX_CHA_MSR_PMON_BOX_FILTER_LOC;
		mask |= SKX_CHA_MSR_PMON_BOX_FILTER_ALL_OPC;
		mask |= SKX_CHA_MSR_PMON_BOX_FILTER_NM;
		mask |= SKX_CHA_MSR_PMON_BOX_FILTER_NOT_NM;
		mask |= SKX_CHA_MSR_PMON_BOX_FILTER_OPC0;
		mask |= SKX_CHA_MSR_PMON_BOX_FILTER_OPC1;
		mask |= SKX_CHA_MSR_PMON_BOX_FILTER_NC;
		mask |= SKX_CHA_MSR_PMON_BOX_FILTER_ISOC;
	पूर्ण
	वापस mask;
पूर्ण

अटल काष्ठा event_स्थिरraपूर्णांक *
skx_cha_get_स्थिरraपूर्णांक(काष्ठा पूर्णांकel_uncore_box *box, काष्ठा perf_event *event)
अणु
	वापस __snbep_cbox_get_स्थिरraपूर्णांक(box, event, skx_cha_filter_mask);
पूर्ण

अटल पूर्णांक skx_cha_hw_config(काष्ठा पूर्णांकel_uncore_box *box, काष्ठा perf_event *event)
अणु
	काष्ठा hw_perf_event_extra *reg1 = &event->hw.extra_reg;
	काष्ठा extra_reg *er;
	पूर्णांक idx = 0;

	क्रम (er = skx_uncore_cha_extra_regs; er->msr; er++) अणु
		अगर (er->event != (event->hw.config & er->config_mask))
			जारी;
		idx |= er->idx;
	पूर्ण

	अगर (idx) अणु
		reg1->reg = HSWEP_C0_MSR_PMON_BOX_FILTER0 +
			    HSWEP_CBO_MSR_OFFSET * box->pmu->pmu_idx;
		reg1->config = event->attr.config1 & skx_cha_filter_mask(idx);
		reg1->idx = idx;
	पूर्ण
	वापस 0;
पूर्ण

अटल काष्ठा पूर्णांकel_uncore_ops skx_uncore_chabox_ops = अणु
	/* There is no frz_en क्रम chabox ctl */
	.init_box		= ivbep_uncore_msr_init_box,
	.disable_box		= snbep_uncore_msr_disable_box,
	.enable_box		= snbep_uncore_msr_enable_box,
	.disable_event		= snbep_uncore_msr_disable_event,
	.enable_event		= hswep_cbox_enable_event,
	.पढ़ो_counter		= uncore_msr_पढ़ो_counter,
	.hw_config		= skx_cha_hw_config,
	.get_स्थिरraपूर्णांक		= skx_cha_get_स्थिरraपूर्णांक,
	.put_स्थिरraपूर्णांक		= snbep_cbox_put_स्थिरraपूर्णांक,
पूर्ण;

अटल काष्ठा पूर्णांकel_uncore_type skx_uncore_chabox = अणु
	.name			= "cha",
	.num_counters		= 4,
	.perf_ctr_bits		= 48,
	.event_ctl		= HSWEP_C0_MSR_PMON_CTL0,
	.perf_ctr		= HSWEP_C0_MSR_PMON_CTR0,
	.event_mask		= HSWEP_S_MSR_PMON_RAW_EVENT_MASK,
	.box_ctl		= HSWEP_C0_MSR_PMON_BOX_CTL,
	.msr_offset		= HSWEP_CBO_MSR_OFFSET,
	.num_shared_regs	= 1,
	.स्थिरraपूर्णांकs		= skx_uncore_chabox_स्थिरraपूर्णांकs,
	.ops			= &skx_uncore_chabox_ops,
	.क्रमmat_group		= &skx_uncore_chabox_क्रमmat_group,
पूर्ण;

अटल काष्ठा attribute *skx_uncore_iio_क्रमmats_attr[] = अणु
	&क्रमmat_attr_event.attr,
	&क्रमmat_attr_umask.attr,
	&क्रमmat_attr_edge.attr,
	&क्रमmat_attr_inv.attr,
	&क्रमmat_attr_thresh9.attr,
	&क्रमmat_attr_ch_mask.attr,
	&क्रमmat_attr_fc_mask.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group skx_uncore_iio_क्रमmat_group = अणु
	.name = "format",
	.attrs = skx_uncore_iio_क्रमmats_attr,
पूर्ण;

अटल काष्ठा event_स्थिरraपूर्णांक skx_uncore_iio_स्थिरraपूर्णांकs[] = अणु
	UNCORE_EVENT_CONSTRAINT(0x83, 0x3),
	UNCORE_EVENT_CONSTRAINT(0x88, 0xc),
	UNCORE_EVENT_CONSTRAINT(0x95, 0xc),
	UNCORE_EVENT_CONSTRAINT(0xc0, 0xc),
	UNCORE_EVENT_CONSTRAINT(0xc5, 0xc),
	UNCORE_EVENT_CONSTRAINT(0xd4, 0xc),
	EVENT_CONSTRAINT_END
पूर्ण;

अटल व्योम skx_iio_enable_event(काष्ठा पूर्णांकel_uncore_box *box,
				 काष्ठा perf_event *event)
अणु
	काष्ठा hw_perf_event *hwc = &event->hw;

	wrmsrl(hwc->config_base, hwc->config | SNBEP_PMON_CTL_EN);
पूर्ण

अटल काष्ठा पूर्णांकel_uncore_ops skx_uncore_iio_ops = अणु
	.init_box		= ivbep_uncore_msr_init_box,
	.disable_box		= snbep_uncore_msr_disable_box,
	.enable_box		= snbep_uncore_msr_enable_box,
	.disable_event		= snbep_uncore_msr_disable_event,
	.enable_event		= skx_iio_enable_event,
	.पढ़ो_counter		= uncore_msr_पढ़ो_counter,
पूर्ण;

अटल अंतरभूत u8 skx_iio_stack(काष्ठा पूर्णांकel_uncore_pmu *pmu, पूर्णांक die)
अणु
	वापस pmu->type->topology[die].configuration >>
	       (pmu->pmu_idx * BUS_NUM_STRIDE);
पूर्ण

अटल umode_t
skx_iio_mapping_visible(काष्ठा kobject *kobj, काष्ठा attribute *attr, पूर्णांक die)
अणु
	काष्ठा पूर्णांकel_uncore_pmu *pmu = dev_to_uncore_pmu(kobj_to_dev(kobj));

	/* Root bus 0x00 is valid only क्रम die 0 AND pmu_idx = 0. */
	वापस (!skx_iio_stack(pmu, die) && pmu->pmu_idx) ? 0 : attr->mode;
पूर्ण

अटल sमाप_प्रकार skx_iio_mapping_show(काष्ठा device *dev,
				    काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा पूर्णांकel_uncore_pmu *pmu = dev_to_uncore_pmu(dev);
	काष्ठा dev_ext_attribute *ea = to_dev_ext_attribute(attr);
	दीर्घ die = (दीर्घ)ea->var;

	वापस प्र_लिखो(buf, "%04x:%02x\n", pmu->type->topology[die].segment,
					   skx_iio_stack(pmu, die));
पूर्ण

अटल पूर्णांक skx_msr_cpu_bus_पढ़ो(पूर्णांक cpu, u64 *topology)
अणु
	u64 msr_value;

	अगर (rdmsrl_on_cpu(cpu, SKX_MSR_CPU_BUS_NUMBER, &msr_value) ||
			!(msr_value & SKX_MSR_CPU_BUS_VALID_BIT))
		वापस -ENXIO;

	*topology = msr_value;

	वापस 0;
पूर्ण

अटल पूर्णांक die_to_cpu(पूर्णांक die)
अणु
	पूर्णांक res = 0, cpu, current_die;
	/*
	 * Using cpus_पढ़ो_lock() to ensure cpu is not going करोwn between
	 * looking at cpu_online_mask.
	 */
	cpus_पढ़ो_lock();
	क्रम_each_online_cpu(cpu) अणु
		current_die = topology_logical_die_id(cpu);
		अगर (current_die == die) अणु
			res = cpu;
			अवरोध;
		पूर्ण
	पूर्ण
	cpus_पढ़ो_unlock();
	वापस res;
पूर्ण

अटल पूर्णांक skx_iio_get_topology(काष्ठा पूर्णांकel_uncore_type *type)
अणु
	पूर्णांक die, ret = -EPERM;

	type->topology = kसुस्मृति(uncore_max_dies(), माप(*type->topology),
				 GFP_KERNEL);
	अगर (!type->topology)
		वापस -ENOMEM;

	क्रम (die = 0; die < uncore_max_dies(); die++) अणु
		ret = skx_msr_cpu_bus_पढ़ो(die_to_cpu(die),
					   &type->topology[die].configuration);
		अगर (ret)
			अवरोध;

		ret = uncore_die_to_segment(die);
		अगर (ret < 0)
			अवरोध;

		type->topology[die].segment = ret;
	पूर्ण

	अगर (ret < 0) अणु
		kमुक्त(type->topology);
		type->topology = शून्य;
	पूर्ण

	वापस ret;
पूर्ण

अटल काष्ठा attribute_group skx_iio_mapping_group = अणु
	.is_visible	= skx_iio_mapping_visible,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *skx_iio_attr_update[] = अणु
	&skx_iio_mapping_group,
	शून्य,
पूर्ण;

अटल पूर्णांक skx_iio_set_mapping(काष्ठा पूर्णांकel_uncore_type *type)
अणु
	अक्षर buf[64];
	पूर्णांक ret;
	दीर्घ die = -1;
	काष्ठा attribute **attrs = शून्य;
	काष्ठा dev_ext_attribute *eas = शून्य;

	ret = skx_iio_get_topology(type);
	अगर (ret < 0)
		जाओ clear_attr_update;

	ret = -ENOMEM;

	/* One more क्रम शून्य. */
	attrs = kसुस्मृति((uncore_max_dies() + 1), माप(*attrs), GFP_KERNEL);
	अगर (!attrs)
		जाओ err;

	eas = kसुस्मृति(uncore_max_dies(), माप(*eas), GFP_KERNEL);
	अगर (!eas)
		जाओ err;

	क्रम (die = 0; die < uncore_max_dies(); die++) अणु
		प्र_लिखो(buf, "die%ld", die);
		sysfs_attr_init(&eas[die].attr.attr);
		eas[die].attr.attr.name = kstrdup(buf, GFP_KERNEL);
		अगर (!eas[die].attr.attr.name)
			जाओ err;
		eas[die].attr.attr.mode = 0444;
		eas[die].attr.show = skx_iio_mapping_show;
		eas[die].attr.store = शून्य;
		eas[die].var = (व्योम *)die;
		attrs[die] = &eas[die].attr.attr;
	पूर्ण
	skx_iio_mapping_group.attrs = attrs;

	वापस 0;
err:
	क्रम (; die >= 0; die--)
		kमुक्त(eas[die].attr.attr.name);
	kमुक्त(eas);
	kमुक्त(attrs);
	kमुक्त(type->topology);
clear_attr_update:
	type->attr_update = शून्य;
	वापस ret;
पूर्ण

अटल व्योम skx_iio_cleanup_mapping(काष्ठा पूर्णांकel_uncore_type *type)
अणु
	काष्ठा attribute **attr = skx_iio_mapping_group.attrs;

	अगर (!attr)
		वापस;

	क्रम (; *attr; attr++)
		kमुक्त((*attr)->name);
	kमुक्त(attr_to_ext_attr(*skx_iio_mapping_group.attrs));
	kमुक्त(skx_iio_mapping_group.attrs);
	skx_iio_mapping_group.attrs = शून्य;
	kमुक्त(type->topology);
पूर्ण

अटल काष्ठा पूर्णांकel_uncore_type skx_uncore_iio = अणु
	.name			= "iio",
	.num_counters		= 4,
	.num_boxes		= 6,
	.perf_ctr_bits		= 48,
	.event_ctl		= SKX_IIO0_MSR_PMON_CTL0,
	.perf_ctr		= SKX_IIO0_MSR_PMON_CTR0,
	.event_mask		= SKX_IIO_PMON_RAW_EVENT_MASK,
	.event_mask_ext		= SKX_IIO_PMON_RAW_EVENT_MASK_EXT,
	.box_ctl		= SKX_IIO0_MSR_PMON_BOX_CTL,
	.msr_offset		= SKX_IIO_MSR_OFFSET,
	.स्थिरraपूर्णांकs		= skx_uncore_iio_स्थिरraपूर्णांकs,
	.ops			= &skx_uncore_iio_ops,
	.क्रमmat_group		= &skx_uncore_iio_क्रमmat_group,
	.attr_update		= skx_iio_attr_update,
	.set_mapping		= skx_iio_set_mapping,
	.cleanup_mapping	= skx_iio_cleanup_mapping,
पूर्ण;

क्रमागत perf_uncore_iio_मुक्तrunning_type_id अणु
	SKX_IIO_MSR_IOCLK			= 0,
	SKX_IIO_MSR_BW				= 1,
	SKX_IIO_MSR_UTIL			= 2,

	SKX_IIO_FREERUNNING_TYPE_MAX,
पूर्ण;


अटल काष्ठा मुक्तrunning_counters skx_iio_मुक्तrunning[] = अणु
	[SKX_IIO_MSR_IOCLK]	= अणु 0xa45, 0x1, 0x20, 1, 36 पूर्ण,
	[SKX_IIO_MSR_BW]	= अणु 0xb00, 0x1, 0x10, 8, 36 पूर्ण,
	[SKX_IIO_MSR_UTIL]	= अणु 0xb08, 0x1, 0x10, 8, 36 पूर्ण,
पूर्ण;

अटल काष्ठा uncore_event_desc skx_uncore_iio_मुक्तrunning_events[] = अणु
	/* Free-Running IO CLOCKS Counter */
	INTEL_UNCORE_EVENT_DESC(ioclk,			"event=0xff,umask=0x10"),
	/* Free-Running IIO BANDWIDTH Counters */
	INTEL_UNCORE_EVENT_DESC(bw_in_port0,		"event=0xff,umask=0x20"),
	INTEL_UNCORE_EVENT_DESC(bw_in_port0.scale,	"3.814697266e-6"),
	INTEL_UNCORE_EVENT_DESC(bw_in_port0.unit,	"MiB"),
	INTEL_UNCORE_EVENT_DESC(bw_in_port1,		"event=0xff,umask=0x21"),
	INTEL_UNCORE_EVENT_DESC(bw_in_port1.scale,	"3.814697266e-6"),
	INTEL_UNCORE_EVENT_DESC(bw_in_port1.unit,	"MiB"),
	INTEL_UNCORE_EVENT_DESC(bw_in_port2,		"event=0xff,umask=0x22"),
	INTEL_UNCORE_EVENT_DESC(bw_in_port2.scale,	"3.814697266e-6"),
	INTEL_UNCORE_EVENT_DESC(bw_in_port2.unit,	"MiB"),
	INTEL_UNCORE_EVENT_DESC(bw_in_port3,		"event=0xff,umask=0x23"),
	INTEL_UNCORE_EVENT_DESC(bw_in_port3.scale,	"3.814697266e-6"),
	INTEL_UNCORE_EVENT_DESC(bw_in_port3.unit,	"MiB"),
	INTEL_UNCORE_EVENT_DESC(bw_out_port0,		"event=0xff,umask=0x24"),
	INTEL_UNCORE_EVENT_DESC(bw_out_port0.scale,	"3.814697266e-6"),
	INTEL_UNCORE_EVENT_DESC(bw_out_port0.unit,	"MiB"),
	INTEL_UNCORE_EVENT_DESC(bw_out_port1,		"event=0xff,umask=0x25"),
	INTEL_UNCORE_EVENT_DESC(bw_out_port1.scale,	"3.814697266e-6"),
	INTEL_UNCORE_EVENT_DESC(bw_out_port1.unit,	"MiB"),
	INTEL_UNCORE_EVENT_DESC(bw_out_port2,		"event=0xff,umask=0x26"),
	INTEL_UNCORE_EVENT_DESC(bw_out_port2.scale,	"3.814697266e-6"),
	INTEL_UNCORE_EVENT_DESC(bw_out_port2.unit,	"MiB"),
	INTEL_UNCORE_EVENT_DESC(bw_out_port3,		"event=0xff,umask=0x27"),
	INTEL_UNCORE_EVENT_DESC(bw_out_port3.scale,	"3.814697266e-6"),
	INTEL_UNCORE_EVENT_DESC(bw_out_port3.unit,	"MiB"),
	/* Free-running IIO UTILIZATION Counters */
	INTEL_UNCORE_EVENT_DESC(util_in_port0,		"event=0xff,umask=0x30"),
	INTEL_UNCORE_EVENT_DESC(util_out_port0,		"event=0xff,umask=0x31"),
	INTEL_UNCORE_EVENT_DESC(util_in_port1,		"event=0xff,umask=0x32"),
	INTEL_UNCORE_EVENT_DESC(util_out_port1,		"event=0xff,umask=0x33"),
	INTEL_UNCORE_EVENT_DESC(util_in_port2,		"event=0xff,umask=0x34"),
	INTEL_UNCORE_EVENT_DESC(util_out_port2,		"event=0xff,umask=0x35"),
	INTEL_UNCORE_EVENT_DESC(util_in_port3,		"event=0xff,umask=0x36"),
	INTEL_UNCORE_EVENT_DESC(util_out_port3,		"event=0xff,umask=0x37"),
	अणु /* end: all zeroes */ पूर्ण,
पूर्ण;

अटल काष्ठा पूर्णांकel_uncore_ops skx_uncore_iio_मुक्तrunning_ops = अणु
	.पढ़ो_counter		= uncore_msr_पढ़ो_counter,
	.hw_config		= uncore_मुक्तrunning_hw_config,
पूर्ण;

अटल काष्ठा attribute *skx_uncore_iio_मुक्तrunning_क्रमmats_attr[] = अणु
	&क्रमmat_attr_event.attr,
	&क्रमmat_attr_umask.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group skx_uncore_iio_मुक्तrunning_क्रमmat_group = अणु
	.name = "format",
	.attrs = skx_uncore_iio_मुक्तrunning_क्रमmats_attr,
पूर्ण;

अटल काष्ठा पूर्णांकel_uncore_type skx_uncore_iio_मुक्त_running = अणु
	.name			= "iio_free_running",
	.num_counters		= 17,
	.num_boxes		= 6,
	.num_मुक्तrunning_types	= SKX_IIO_FREERUNNING_TYPE_MAX,
	.मुक्तrunning		= skx_iio_मुक्तrunning,
	.ops			= &skx_uncore_iio_मुक्तrunning_ops,
	.event_descs		= skx_uncore_iio_मुक्तrunning_events,
	.क्रमmat_group		= &skx_uncore_iio_मुक्तrunning_क्रमmat_group,
पूर्ण;

अटल काष्ठा attribute *skx_uncore_क्रमmats_attr[] = अणु
	&क्रमmat_attr_event.attr,
	&क्रमmat_attr_umask.attr,
	&क्रमmat_attr_edge.attr,
	&क्रमmat_attr_inv.attr,
	&क्रमmat_attr_thresh8.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group skx_uncore_क्रमmat_group = अणु
	.name = "format",
	.attrs = skx_uncore_क्रमmats_attr,
पूर्ण;

अटल काष्ठा पूर्णांकel_uncore_type skx_uncore_irp = अणु
	.name			= "irp",
	.num_counters		= 2,
	.num_boxes		= 6,
	.perf_ctr_bits		= 48,
	.event_ctl		= SKX_IRP0_MSR_PMON_CTL0,
	.perf_ctr		= SKX_IRP0_MSR_PMON_CTR0,
	.event_mask		= SNBEP_PMON_RAW_EVENT_MASK,
	.box_ctl		= SKX_IRP0_MSR_PMON_BOX_CTL,
	.msr_offset		= SKX_IRP_MSR_OFFSET,
	.ops			= &skx_uncore_iio_ops,
	.क्रमmat_group		= &skx_uncore_क्रमmat_group,
पूर्ण;

अटल काष्ठा attribute *skx_uncore_pcu_क्रमmats_attr[] = अणु
	&क्रमmat_attr_event.attr,
	&क्रमmat_attr_umask.attr,
	&क्रमmat_attr_edge.attr,
	&क्रमmat_attr_inv.attr,
	&क्रमmat_attr_thresh8.attr,
	&क्रमmat_attr_occ_invert.attr,
	&क्रमmat_attr_occ_edge_det.attr,
	&क्रमmat_attr_filter_band0.attr,
	&क्रमmat_attr_filter_band1.attr,
	&क्रमmat_attr_filter_band2.attr,
	&क्रमmat_attr_filter_band3.attr,
	शून्य,
पूर्ण;

अटल काष्ठा attribute_group skx_uncore_pcu_क्रमmat_group = अणु
	.name = "format",
	.attrs = skx_uncore_pcu_क्रमmats_attr,
पूर्ण;

अटल काष्ठा पूर्णांकel_uncore_ops skx_uncore_pcu_ops = अणु
	IVBEP_UNCORE_MSR_OPS_COMMON_INIT(),
	.hw_config		= hswep_pcu_hw_config,
	.get_स्थिरraपूर्णांक		= snbep_pcu_get_स्थिरraपूर्णांक,
	.put_स्थिरraपूर्णांक		= snbep_pcu_put_स्थिरraपूर्णांक,
पूर्ण;

अटल काष्ठा पूर्णांकel_uncore_type skx_uncore_pcu = अणु
	.name			= "pcu",
	.num_counters		= 4,
	.num_boxes		= 1,
	.perf_ctr_bits		= 48,
	.perf_ctr		= HSWEP_PCU_MSR_PMON_CTR0,
	.event_ctl		= HSWEP_PCU_MSR_PMON_CTL0,
	.event_mask		= SNBEP_PCU_MSR_PMON_RAW_EVENT_MASK,
	.box_ctl		= HSWEP_PCU_MSR_PMON_BOX_CTL,
	.num_shared_regs	= 1,
	.ops			= &skx_uncore_pcu_ops,
	.क्रमmat_group		= &skx_uncore_pcu_क्रमmat_group,
पूर्ण;

अटल काष्ठा पूर्णांकel_uncore_type *skx_msr_uncores[] = अणु
	&skx_uncore_ubox,
	&skx_uncore_chabox,
	&skx_uncore_iio,
	&skx_uncore_iio_मुक्त_running,
	&skx_uncore_irp,
	&skx_uncore_pcu,
	शून्य,
पूर्ण;

/*
 * To determine the number of CHAs, it should पढ़ो bits 27:0 in the CAPID6
 * रेजिस्टर which located at Device 30, Function 3, Offset 0x9C. PCI ID 0x2083.
 */
#घोषणा SKX_CAPID6		0x9c
#घोषणा SKX_CHA_BIT_MASK	GENMASK(27, 0)

अटल पूर्णांक skx_count_chabox(व्योम)
अणु
	काष्ठा pci_dev *dev = शून्य;
	u32 val = 0;

	dev = pci_get_device(PCI_VENDOR_ID_INTEL, 0x2083, dev);
	अगर (!dev)
		जाओ out;

	pci_पढ़ो_config_dword(dev, SKX_CAPID6, &val);
	val &= SKX_CHA_BIT_MASK;
out:
	pci_dev_put(dev);
	वापस hweight32(val);
पूर्ण

व्योम skx_uncore_cpu_init(व्योम)
अणु
	skx_uncore_chabox.num_boxes = skx_count_chabox();
	uncore_msr_uncores = skx_msr_uncores;
पूर्ण

अटल काष्ठा पूर्णांकel_uncore_type skx_uncore_imc = अणु
	.name		= "imc",
	.num_counters   = 4,
	.num_boxes	= 6,
	.perf_ctr_bits	= 48,
	.fixed_ctr_bits	= 48,
	.fixed_ctr	= SNBEP_MC_CHy_PCI_PMON_FIXED_CTR,
	.fixed_ctl	= SNBEP_MC_CHy_PCI_PMON_FIXED_CTL,
	.event_descs	= hswep_uncore_imc_events,
	.perf_ctr	= SNBEP_PCI_PMON_CTR0,
	.event_ctl	= SNBEP_PCI_PMON_CTL0,
	.event_mask	= SNBEP_PMON_RAW_EVENT_MASK,
	.box_ctl	= SNBEP_PCI_PMON_BOX_CTL,
	.ops		= &ivbep_uncore_pci_ops,
	.क्रमmat_group	= &skx_uncore_क्रमmat_group,
पूर्ण;

अटल काष्ठा attribute *skx_upi_uncore_क्रमmats_attr[] = अणु
	&क्रमmat_attr_event.attr,
	&क्रमmat_attr_umask_ext.attr,
	&क्रमmat_attr_edge.attr,
	&क्रमmat_attr_inv.attr,
	&क्रमmat_attr_thresh8.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group skx_upi_uncore_क्रमmat_group = अणु
	.name = "format",
	.attrs = skx_upi_uncore_क्रमmats_attr,
पूर्ण;

अटल व्योम skx_upi_uncore_pci_init_box(काष्ठा पूर्णांकel_uncore_box *box)
अणु
	काष्ठा pci_dev *pdev = box->pci_dev;

	__set_bit(UNCORE_BOX_FLAG_CTL_OFFS8, &box->flags);
	pci_ग_लिखो_config_dword(pdev, SKX_UPI_PCI_PMON_BOX_CTL, IVBEP_PMON_BOX_CTL_INT);
पूर्ण

अटल काष्ठा पूर्णांकel_uncore_ops skx_upi_uncore_pci_ops = अणु
	.init_box	= skx_upi_uncore_pci_init_box,
	.disable_box	= snbep_uncore_pci_disable_box,
	.enable_box	= snbep_uncore_pci_enable_box,
	.disable_event	= snbep_uncore_pci_disable_event,
	.enable_event	= snbep_uncore_pci_enable_event,
	.पढ़ो_counter	= snbep_uncore_pci_पढ़ो_counter,
पूर्ण;

अटल काष्ठा पूर्णांकel_uncore_type skx_uncore_upi = अणु
	.name		= "upi",
	.num_counters   = 4,
	.num_boxes	= 3,
	.perf_ctr_bits	= 48,
	.perf_ctr	= SKX_UPI_PCI_PMON_CTR0,
	.event_ctl	= SKX_UPI_PCI_PMON_CTL0,
	.event_mask	= SNBEP_PMON_RAW_EVENT_MASK,
	.event_mask_ext = SKX_UPI_CTL_UMASK_EXT,
	.box_ctl	= SKX_UPI_PCI_PMON_BOX_CTL,
	.ops		= &skx_upi_uncore_pci_ops,
	.क्रमmat_group	= &skx_upi_uncore_क्रमmat_group,
पूर्ण;

अटल व्योम skx_m2m_uncore_pci_init_box(काष्ठा पूर्णांकel_uncore_box *box)
अणु
	काष्ठा pci_dev *pdev = box->pci_dev;

	__set_bit(UNCORE_BOX_FLAG_CTL_OFFS8, &box->flags);
	pci_ग_लिखो_config_dword(pdev, SKX_M2M_PCI_PMON_BOX_CTL, IVBEP_PMON_BOX_CTL_INT);
पूर्ण

अटल काष्ठा पूर्णांकel_uncore_ops skx_m2m_uncore_pci_ops = अणु
	.init_box	= skx_m2m_uncore_pci_init_box,
	.disable_box	= snbep_uncore_pci_disable_box,
	.enable_box	= snbep_uncore_pci_enable_box,
	.disable_event	= snbep_uncore_pci_disable_event,
	.enable_event	= snbep_uncore_pci_enable_event,
	.पढ़ो_counter	= snbep_uncore_pci_पढ़ो_counter,
पूर्ण;

अटल काष्ठा पूर्णांकel_uncore_type skx_uncore_m2m = अणु
	.name		= "m2m",
	.num_counters   = 4,
	.num_boxes	= 2,
	.perf_ctr_bits	= 48,
	.perf_ctr	= SKX_M2M_PCI_PMON_CTR0,
	.event_ctl	= SKX_M2M_PCI_PMON_CTL0,
	.event_mask	= SNBEP_PMON_RAW_EVENT_MASK,
	.box_ctl	= SKX_M2M_PCI_PMON_BOX_CTL,
	.ops		= &skx_m2m_uncore_pci_ops,
	.क्रमmat_group	= &skx_uncore_क्रमmat_group,
पूर्ण;

अटल काष्ठा event_स्थिरraपूर्णांक skx_uncore_m2pcie_स्थिरraपूर्णांकs[] = अणु
	UNCORE_EVENT_CONSTRAINT(0x23, 0x3),
	EVENT_CONSTRAINT_END
पूर्ण;

अटल काष्ठा पूर्णांकel_uncore_type skx_uncore_m2pcie = अणु
	.name		= "m2pcie",
	.num_counters   = 4,
	.num_boxes	= 4,
	.perf_ctr_bits	= 48,
	.स्थिरraपूर्णांकs	= skx_uncore_m2pcie_स्थिरraपूर्णांकs,
	.perf_ctr	= SNBEP_PCI_PMON_CTR0,
	.event_ctl	= SNBEP_PCI_PMON_CTL0,
	.event_mask	= SNBEP_PMON_RAW_EVENT_MASK,
	.box_ctl	= SNBEP_PCI_PMON_BOX_CTL,
	.ops		= &ivbep_uncore_pci_ops,
	.क्रमmat_group	= &skx_uncore_क्रमmat_group,
पूर्ण;

अटल काष्ठा event_स्थिरraपूर्णांक skx_uncore_m3upi_स्थिरraपूर्णांकs[] = अणु
	UNCORE_EVENT_CONSTRAINT(0x1d, 0x1),
	UNCORE_EVENT_CONSTRAINT(0x1e, 0x1),
	UNCORE_EVENT_CONSTRAINT(0x40, 0x7),
	UNCORE_EVENT_CONSTRAINT(0x4e, 0x7),
	UNCORE_EVENT_CONSTRAINT(0x4f, 0x7),
	UNCORE_EVENT_CONSTRAINT(0x50, 0x7),
	UNCORE_EVENT_CONSTRAINT(0x51, 0x7),
	UNCORE_EVENT_CONSTRAINT(0x52, 0x7),
	EVENT_CONSTRAINT_END
पूर्ण;

अटल काष्ठा पूर्णांकel_uncore_type skx_uncore_m3upi = अणु
	.name		= "m3upi",
	.num_counters   = 3,
	.num_boxes	= 3,
	.perf_ctr_bits	= 48,
	.स्थिरraपूर्णांकs	= skx_uncore_m3upi_स्थिरraपूर्णांकs,
	.perf_ctr	= SNBEP_PCI_PMON_CTR0,
	.event_ctl	= SNBEP_PCI_PMON_CTL0,
	.event_mask	= SNBEP_PMON_RAW_EVENT_MASK,
	.box_ctl	= SNBEP_PCI_PMON_BOX_CTL,
	.ops		= &ivbep_uncore_pci_ops,
	.क्रमmat_group	= &skx_uncore_क्रमmat_group,
पूर्ण;

क्रमागत अणु
	SKX_PCI_UNCORE_IMC,
	SKX_PCI_UNCORE_M2M,
	SKX_PCI_UNCORE_UPI,
	SKX_PCI_UNCORE_M2PCIE,
	SKX_PCI_UNCORE_M3UPI,
पूर्ण;

अटल काष्ठा पूर्णांकel_uncore_type *skx_pci_uncores[] = अणु
	[SKX_PCI_UNCORE_IMC]	= &skx_uncore_imc,
	[SKX_PCI_UNCORE_M2M]	= &skx_uncore_m2m,
	[SKX_PCI_UNCORE_UPI]	= &skx_uncore_upi,
	[SKX_PCI_UNCORE_M2PCIE]	= &skx_uncore_m2pcie,
	[SKX_PCI_UNCORE_M3UPI]	= &skx_uncore_m3upi,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा pci_device_id skx_uncore_pci_ids[] = अणु
	अणु /* MC0 Channel 0 */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, 0x2042),
		.driver_data = UNCORE_PCI_DEV_FULL_DATA(10, 2, SKX_PCI_UNCORE_IMC, 0),
	पूर्ण,
	अणु /* MC0 Channel 1 */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, 0x2046),
		.driver_data = UNCORE_PCI_DEV_FULL_DATA(10, 6, SKX_PCI_UNCORE_IMC, 1),
	पूर्ण,
	अणु /* MC0 Channel 2 */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, 0x204a),
		.driver_data = UNCORE_PCI_DEV_FULL_DATA(11, 2, SKX_PCI_UNCORE_IMC, 2),
	पूर्ण,
	अणु /* MC1 Channel 0 */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, 0x2042),
		.driver_data = UNCORE_PCI_DEV_FULL_DATA(12, 2, SKX_PCI_UNCORE_IMC, 3),
	पूर्ण,
	अणु /* MC1 Channel 1 */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, 0x2046),
		.driver_data = UNCORE_PCI_DEV_FULL_DATA(12, 6, SKX_PCI_UNCORE_IMC, 4),
	पूर्ण,
	अणु /* MC1 Channel 2 */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, 0x204a),
		.driver_data = UNCORE_PCI_DEV_FULL_DATA(13, 2, SKX_PCI_UNCORE_IMC, 5),
	पूर्ण,
	अणु /* M2M0 */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, 0x2066),
		.driver_data = UNCORE_PCI_DEV_FULL_DATA(8, 0, SKX_PCI_UNCORE_M2M, 0),
	पूर्ण,
	अणु /* M2M1 */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, 0x2066),
		.driver_data = UNCORE_PCI_DEV_FULL_DATA(9, 0, SKX_PCI_UNCORE_M2M, 1),
	पूर्ण,
	अणु /* UPI0 Link 0 */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, 0x2058),
		.driver_data = UNCORE_PCI_DEV_FULL_DATA(14, 0, SKX_PCI_UNCORE_UPI, 0),
	पूर्ण,
	अणु /* UPI0 Link 1 */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, 0x2058),
		.driver_data = UNCORE_PCI_DEV_FULL_DATA(15, 0, SKX_PCI_UNCORE_UPI, 1),
	पूर्ण,
	अणु /* UPI1 Link 2 */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, 0x2058),
		.driver_data = UNCORE_PCI_DEV_FULL_DATA(16, 0, SKX_PCI_UNCORE_UPI, 2),
	पूर्ण,
	अणु /* M2PCIe 0 */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, 0x2088),
		.driver_data = UNCORE_PCI_DEV_FULL_DATA(21, 1, SKX_PCI_UNCORE_M2PCIE, 0),
	पूर्ण,
	अणु /* M2PCIe 1 */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, 0x2088),
		.driver_data = UNCORE_PCI_DEV_FULL_DATA(22, 1, SKX_PCI_UNCORE_M2PCIE, 1),
	पूर्ण,
	अणु /* M2PCIe 2 */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, 0x2088),
		.driver_data = UNCORE_PCI_DEV_FULL_DATA(23, 1, SKX_PCI_UNCORE_M2PCIE, 2),
	पूर्ण,
	अणु /* M2PCIe 3 */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, 0x2088),
		.driver_data = UNCORE_PCI_DEV_FULL_DATA(21, 5, SKX_PCI_UNCORE_M2PCIE, 3),
	पूर्ण,
	अणु /* M3UPI0 Link 0 */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, 0x204D),
		.driver_data = UNCORE_PCI_DEV_FULL_DATA(18, 1, SKX_PCI_UNCORE_M3UPI, 0),
	पूर्ण,
	अणु /* M3UPI0 Link 1 */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, 0x204E),
		.driver_data = UNCORE_PCI_DEV_FULL_DATA(18, 2, SKX_PCI_UNCORE_M3UPI, 1),
	पूर्ण,
	अणु /* M3UPI1 Link 2 */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, 0x204D),
		.driver_data = UNCORE_PCI_DEV_FULL_DATA(18, 5, SKX_PCI_UNCORE_M3UPI, 2),
	पूर्ण,
	अणु /* end: all zeroes */ पूर्ण
पूर्ण;


अटल काष्ठा pci_driver skx_uncore_pci_driver = अणु
	.name		= "skx_uncore",
	.id_table	= skx_uncore_pci_ids,
पूर्ण;

पूर्णांक skx_uncore_pci_init(व्योम)
अणु
	/* need to द्विगुन check pci address */
	पूर्णांक ret = snbep_pci2phy_map_init(0x2014, SKX_CPUNODEID, SKX_GIDNIDMAP, false);

	अगर (ret)
		वापस ret;

	uncore_pci_uncores = skx_pci_uncores;
	uncore_pci_driver = &skx_uncore_pci_driver;
	वापस 0;
पूर्ण

/* end of SKX uncore support */

/* SNR uncore support */

अटल काष्ठा पूर्णांकel_uncore_type snr_uncore_ubox = अणु
	.name			= "ubox",
	.num_counters		= 2,
	.num_boxes		= 1,
	.perf_ctr_bits		= 48,
	.fixed_ctr_bits		= 48,
	.perf_ctr		= SNR_U_MSR_PMON_CTR0,
	.event_ctl		= SNR_U_MSR_PMON_CTL0,
	.event_mask		= SNBEP_PMON_RAW_EVENT_MASK,
	.fixed_ctr		= SNR_U_MSR_PMON_UCLK_FIXED_CTR,
	.fixed_ctl		= SNR_U_MSR_PMON_UCLK_FIXED_CTL,
	.ops			= &ivbep_uncore_msr_ops,
	.क्रमmat_group		= &ivbep_uncore_क्रमmat_group,
पूर्ण;

अटल काष्ठा attribute *snr_uncore_cha_क्रमmats_attr[] = अणु
	&क्रमmat_attr_event.attr,
	&क्रमmat_attr_umask_ext2.attr,
	&क्रमmat_attr_edge.attr,
	&क्रमmat_attr_tid_en.attr,
	&क्रमmat_attr_inv.attr,
	&क्रमmat_attr_thresh8.attr,
	&क्रमmat_attr_filter_tid5.attr,
	शून्य,
पूर्ण;
अटल स्थिर काष्ठा attribute_group snr_uncore_chabox_क्रमmat_group = अणु
	.name = "format",
	.attrs = snr_uncore_cha_क्रमmats_attr,
पूर्ण;

अटल पूर्णांक snr_cha_hw_config(काष्ठा पूर्णांकel_uncore_box *box, काष्ठा perf_event *event)
अणु
	काष्ठा hw_perf_event_extra *reg1 = &event->hw.extra_reg;

	reg1->reg = SNR_C0_MSR_PMON_BOX_FILTER0 +
		    box->pmu->type->msr_offset * box->pmu->pmu_idx;
	reg1->config = event->attr.config1 & SKX_CHA_MSR_PMON_BOX_FILTER_TID;
	reg1->idx = 0;

	वापस 0;
पूर्ण

अटल व्योम snr_cha_enable_event(काष्ठा पूर्णांकel_uncore_box *box,
				   काष्ठा perf_event *event)
अणु
	काष्ठा hw_perf_event *hwc = &event->hw;
	काष्ठा hw_perf_event_extra *reg1 = &hwc->extra_reg;

	अगर (reg1->idx != EXTRA_REG_NONE)
		wrmsrl(reg1->reg, reg1->config);

	wrmsrl(hwc->config_base, hwc->config | SNBEP_PMON_CTL_EN);
पूर्ण

अटल काष्ठा पूर्णांकel_uncore_ops snr_uncore_chabox_ops = अणु
	.init_box		= ivbep_uncore_msr_init_box,
	.disable_box		= snbep_uncore_msr_disable_box,
	.enable_box		= snbep_uncore_msr_enable_box,
	.disable_event		= snbep_uncore_msr_disable_event,
	.enable_event		= snr_cha_enable_event,
	.पढ़ो_counter		= uncore_msr_पढ़ो_counter,
	.hw_config		= snr_cha_hw_config,
पूर्ण;

अटल काष्ठा पूर्णांकel_uncore_type snr_uncore_chabox = अणु
	.name			= "cha",
	.num_counters		= 4,
	.num_boxes		= 6,
	.perf_ctr_bits		= 48,
	.event_ctl		= SNR_CHA_MSR_PMON_CTL0,
	.perf_ctr		= SNR_CHA_MSR_PMON_CTR0,
	.box_ctl		= SNR_CHA_MSR_PMON_BOX_CTL,
	.msr_offset		= HSWEP_CBO_MSR_OFFSET,
	.event_mask		= HSWEP_S_MSR_PMON_RAW_EVENT_MASK,
	.event_mask_ext		= SNR_CHA_RAW_EVENT_MASK_EXT,
	.ops			= &snr_uncore_chabox_ops,
	.क्रमmat_group		= &snr_uncore_chabox_क्रमmat_group,
पूर्ण;

अटल काष्ठा attribute *snr_uncore_iio_क्रमmats_attr[] = अणु
	&क्रमmat_attr_event.attr,
	&क्रमmat_attr_umask.attr,
	&क्रमmat_attr_edge.attr,
	&क्रमmat_attr_inv.attr,
	&क्रमmat_attr_thresh9.attr,
	&क्रमmat_attr_ch_mask2.attr,
	&क्रमmat_attr_fc_mask2.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group snr_uncore_iio_क्रमmat_group = अणु
	.name = "format",
	.attrs = snr_uncore_iio_क्रमmats_attr,
पूर्ण;

अटल काष्ठा पूर्णांकel_uncore_type snr_uncore_iio = अणु
	.name			= "iio",
	.num_counters		= 4,
	.num_boxes		= 5,
	.perf_ctr_bits		= 48,
	.event_ctl		= SNR_IIO_MSR_PMON_CTL0,
	.perf_ctr		= SNR_IIO_MSR_PMON_CTR0,
	.event_mask		= SNBEP_PMON_RAW_EVENT_MASK,
	.event_mask_ext		= SNR_IIO_PMON_RAW_EVENT_MASK_EXT,
	.box_ctl		= SNR_IIO_MSR_PMON_BOX_CTL,
	.msr_offset		= SNR_IIO_MSR_OFFSET,
	.ops			= &ivbep_uncore_msr_ops,
	.क्रमmat_group		= &snr_uncore_iio_क्रमmat_group,
पूर्ण;

अटल काष्ठा पूर्णांकel_uncore_type snr_uncore_irp = अणु
	.name			= "irp",
	.num_counters		= 2,
	.num_boxes		= 5,
	.perf_ctr_bits		= 48,
	.event_ctl		= SNR_IRP0_MSR_PMON_CTL0,
	.perf_ctr		= SNR_IRP0_MSR_PMON_CTR0,
	.event_mask		= SNBEP_PMON_RAW_EVENT_MASK,
	.box_ctl		= SNR_IRP0_MSR_PMON_BOX_CTL,
	.msr_offset		= SNR_IRP_MSR_OFFSET,
	.ops			= &ivbep_uncore_msr_ops,
	.क्रमmat_group		= &ivbep_uncore_क्रमmat_group,
पूर्ण;

अटल काष्ठा पूर्णांकel_uncore_type snr_uncore_m2pcie = अणु
	.name		= "m2pcie",
	.num_counters	= 4,
	.num_boxes	= 5,
	.perf_ctr_bits	= 48,
	.event_ctl	= SNR_M2PCIE_MSR_PMON_CTL0,
	.perf_ctr	= SNR_M2PCIE_MSR_PMON_CTR0,
	.box_ctl	= SNR_M2PCIE_MSR_PMON_BOX_CTL,
	.msr_offset	= SNR_M2PCIE_MSR_OFFSET,
	.event_mask	= SNBEP_PMON_RAW_EVENT_MASK,
	.ops		= &ivbep_uncore_msr_ops,
	.क्रमmat_group	= &ivbep_uncore_क्रमmat_group,
पूर्ण;

अटल पूर्णांक snr_pcu_hw_config(काष्ठा पूर्णांकel_uncore_box *box, काष्ठा perf_event *event)
अणु
	काष्ठा hw_perf_event *hwc = &event->hw;
	काष्ठा hw_perf_event_extra *reg1 = &hwc->extra_reg;
	पूर्णांक ev_sel = hwc->config & SNBEP_PMON_CTL_EV_SEL_MASK;

	अगर (ev_sel >= 0xb && ev_sel <= 0xe) अणु
		reg1->reg = SNR_PCU_MSR_PMON_BOX_FILTER;
		reg1->idx = ev_sel - 0xb;
		reg1->config = event->attr.config1 & (0xff << reg1->idx);
	पूर्ण
	वापस 0;
पूर्ण

अटल काष्ठा पूर्णांकel_uncore_ops snr_uncore_pcu_ops = अणु
	IVBEP_UNCORE_MSR_OPS_COMMON_INIT(),
	.hw_config		= snr_pcu_hw_config,
	.get_स्थिरraपूर्णांक		= snbep_pcu_get_स्थिरraपूर्णांक,
	.put_स्थिरraपूर्णांक		= snbep_pcu_put_स्थिरraपूर्णांक,
पूर्ण;

अटल काष्ठा पूर्णांकel_uncore_type snr_uncore_pcu = अणु
	.name			= "pcu",
	.num_counters		= 4,
	.num_boxes		= 1,
	.perf_ctr_bits		= 48,
	.perf_ctr		= SNR_PCU_MSR_PMON_CTR0,
	.event_ctl		= SNR_PCU_MSR_PMON_CTL0,
	.event_mask		= SNBEP_PMON_RAW_EVENT_MASK,
	.box_ctl		= SNR_PCU_MSR_PMON_BOX_CTL,
	.num_shared_regs	= 1,
	.ops			= &snr_uncore_pcu_ops,
	.क्रमmat_group		= &skx_uncore_pcu_क्रमmat_group,
पूर्ण;

क्रमागत perf_uncore_snr_iio_मुक्तrunning_type_id अणु
	SNR_IIO_MSR_IOCLK,
	SNR_IIO_MSR_BW_IN,

	SNR_IIO_FREERUNNING_TYPE_MAX,
पूर्ण;

अटल काष्ठा मुक्तrunning_counters snr_iio_मुक्तrunning[] = अणु
	[SNR_IIO_MSR_IOCLK]	= अणु 0x1eac, 0x1, 0x10, 1, 48 पूर्ण,
	[SNR_IIO_MSR_BW_IN]	= अणु 0x1f00, 0x1, 0x10, 8, 48 पूर्ण,
पूर्ण;

अटल काष्ठा uncore_event_desc snr_uncore_iio_मुक्तrunning_events[] = अणु
	/* Free-Running IIO CLOCKS Counter */
	INTEL_UNCORE_EVENT_DESC(ioclk,			"event=0xff,umask=0x10"),
	/* Free-Running IIO BANDWIDTH IN Counters */
	INTEL_UNCORE_EVENT_DESC(bw_in_port0,		"event=0xff,umask=0x20"),
	INTEL_UNCORE_EVENT_DESC(bw_in_port0.scale,	"3.814697266e-6"),
	INTEL_UNCORE_EVENT_DESC(bw_in_port0.unit,	"MiB"),
	INTEL_UNCORE_EVENT_DESC(bw_in_port1,		"event=0xff,umask=0x21"),
	INTEL_UNCORE_EVENT_DESC(bw_in_port1.scale,	"3.814697266e-6"),
	INTEL_UNCORE_EVENT_DESC(bw_in_port1.unit,	"MiB"),
	INTEL_UNCORE_EVENT_DESC(bw_in_port2,		"event=0xff,umask=0x22"),
	INTEL_UNCORE_EVENT_DESC(bw_in_port2.scale,	"3.814697266e-6"),
	INTEL_UNCORE_EVENT_DESC(bw_in_port2.unit,	"MiB"),
	INTEL_UNCORE_EVENT_DESC(bw_in_port3,		"event=0xff,umask=0x23"),
	INTEL_UNCORE_EVENT_DESC(bw_in_port3.scale,	"3.814697266e-6"),
	INTEL_UNCORE_EVENT_DESC(bw_in_port3.unit,	"MiB"),
	INTEL_UNCORE_EVENT_DESC(bw_in_port4,		"event=0xff,umask=0x24"),
	INTEL_UNCORE_EVENT_DESC(bw_in_port4.scale,	"3.814697266e-6"),
	INTEL_UNCORE_EVENT_DESC(bw_in_port4.unit,	"MiB"),
	INTEL_UNCORE_EVENT_DESC(bw_in_port5,		"event=0xff,umask=0x25"),
	INTEL_UNCORE_EVENT_DESC(bw_in_port5.scale,	"3.814697266e-6"),
	INTEL_UNCORE_EVENT_DESC(bw_in_port5.unit,	"MiB"),
	INTEL_UNCORE_EVENT_DESC(bw_in_port6,		"event=0xff,umask=0x26"),
	INTEL_UNCORE_EVENT_DESC(bw_in_port6.scale,	"3.814697266e-6"),
	INTEL_UNCORE_EVENT_DESC(bw_in_port6.unit,	"MiB"),
	INTEL_UNCORE_EVENT_DESC(bw_in_port7,		"event=0xff,umask=0x27"),
	INTEL_UNCORE_EVENT_DESC(bw_in_port7.scale,	"3.814697266e-6"),
	INTEL_UNCORE_EVENT_DESC(bw_in_port7.unit,	"MiB"),
	अणु /* end: all zeroes */ पूर्ण,
पूर्ण;

अटल काष्ठा पूर्णांकel_uncore_type snr_uncore_iio_मुक्त_running = अणु
	.name			= "iio_free_running",
	.num_counters		= 9,
	.num_boxes		= 5,
	.num_मुक्तrunning_types	= SNR_IIO_FREERUNNING_TYPE_MAX,
	.मुक्तrunning		= snr_iio_मुक्तrunning,
	.ops			= &skx_uncore_iio_मुक्तrunning_ops,
	.event_descs		= snr_uncore_iio_मुक्तrunning_events,
	.क्रमmat_group		= &skx_uncore_iio_मुक्तrunning_क्रमmat_group,
पूर्ण;

अटल काष्ठा पूर्णांकel_uncore_type *snr_msr_uncores[] = अणु
	&snr_uncore_ubox,
	&snr_uncore_chabox,
	&snr_uncore_iio,
	&snr_uncore_irp,
	&snr_uncore_m2pcie,
	&snr_uncore_pcu,
	&snr_uncore_iio_मुक्त_running,
	शून्य,
पूर्ण;

व्योम snr_uncore_cpu_init(व्योम)
अणु
	uncore_msr_uncores = snr_msr_uncores;
पूर्ण

अटल व्योम snr_m2m_uncore_pci_init_box(काष्ठा पूर्णांकel_uncore_box *box)
अणु
	काष्ठा pci_dev *pdev = box->pci_dev;
	पूर्णांक box_ctl = uncore_pci_box_ctl(box);

	__set_bit(UNCORE_BOX_FLAG_CTL_OFFS8, &box->flags);
	pci_ग_लिखो_config_dword(pdev, box_ctl, IVBEP_PMON_BOX_CTL_INT);
पूर्ण

अटल काष्ठा पूर्णांकel_uncore_ops snr_m2m_uncore_pci_ops = अणु
	.init_box	= snr_m2m_uncore_pci_init_box,
	.disable_box	= snbep_uncore_pci_disable_box,
	.enable_box	= snbep_uncore_pci_enable_box,
	.disable_event	= snbep_uncore_pci_disable_event,
	.enable_event	= snbep_uncore_pci_enable_event,
	.पढ़ो_counter	= snbep_uncore_pci_पढ़ो_counter,
पूर्ण;

अटल काष्ठा attribute *snr_m2m_uncore_क्रमmats_attr[] = अणु
	&क्रमmat_attr_event.attr,
	&क्रमmat_attr_umask_ext3.attr,
	&क्रमmat_attr_edge.attr,
	&क्रमmat_attr_inv.attr,
	&क्रमmat_attr_thresh8.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group snr_m2m_uncore_क्रमmat_group = अणु
	.name = "format",
	.attrs = snr_m2m_uncore_क्रमmats_attr,
पूर्ण;

अटल काष्ठा पूर्णांकel_uncore_type snr_uncore_m2m = अणु
	.name		= "m2m",
	.num_counters   = 4,
	.num_boxes	= 1,
	.perf_ctr_bits	= 48,
	.perf_ctr	= SNR_M2M_PCI_PMON_CTR0,
	.event_ctl	= SNR_M2M_PCI_PMON_CTL0,
	.event_mask	= SNBEP_PMON_RAW_EVENT_MASK,
	.event_mask_ext	= SNR_M2M_PCI_PMON_UMASK_EXT,
	.box_ctl	= SNR_M2M_PCI_PMON_BOX_CTL,
	.ops		= &snr_m2m_uncore_pci_ops,
	.क्रमmat_group	= &snr_m2m_uncore_क्रमmat_group,
पूर्ण;

अटल व्योम snr_uncore_pci_enable_event(काष्ठा पूर्णांकel_uncore_box *box, काष्ठा perf_event *event)
अणु
	काष्ठा pci_dev *pdev = box->pci_dev;
	काष्ठा hw_perf_event *hwc = &event->hw;

	pci_ग_लिखो_config_dword(pdev, hwc->config_base, (u32)(hwc->config | SNBEP_PMON_CTL_EN));
	pci_ग_लिखो_config_dword(pdev, hwc->config_base + 4, (u32)(hwc->config >> 32));
पूर्ण

अटल काष्ठा पूर्णांकel_uncore_ops snr_pcie3_uncore_pci_ops = अणु
	.init_box	= snr_m2m_uncore_pci_init_box,
	.disable_box	= snbep_uncore_pci_disable_box,
	.enable_box	= snbep_uncore_pci_enable_box,
	.disable_event	= snbep_uncore_pci_disable_event,
	.enable_event	= snr_uncore_pci_enable_event,
	.पढ़ो_counter	= snbep_uncore_pci_पढ़ो_counter,
पूर्ण;

अटल काष्ठा पूर्णांकel_uncore_type snr_uncore_pcie3 = अणु
	.name		= "pcie3",
	.num_counters	= 4,
	.num_boxes	= 1,
	.perf_ctr_bits	= 48,
	.perf_ctr	= SNR_PCIE3_PCI_PMON_CTR0,
	.event_ctl	= SNR_PCIE3_PCI_PMON_CTL0,
	.event_mask	= SKX_IIO_PMON_RAW_EVENT_MASK,
	.event_mask_ext	= SKX_IIO_PMON_RAW_EVENT_MASK_EXT,
	.box_ctl	= SNR_PCIE3_PCI_PMON_BOX_CTL,
	.ops		= &snr_pcie3_uncore_pci_ops,
	.क्रमmat_group	= &skx_uncore_iio_क्रमmat_group,
पूर्ण;

क्रमागत अणु
	SNR_PCI_UNCORE_M2M,
	SNR_PCI_UNCORE_PCIE3,
पूर्ण;

अटल काष्ठा पूर्णांकel_uncore_type *snr_pci_uncores[] = अणु
	[SNR_PCI_UNCORE_M2M]		= &snr_uncore_m2m,
	[SNR_PCI_UNCORE_PCIE3]		= &snr_uncore_pcie3,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा pci_device_id snr_uncore_pci_ids[] = अणु
	अणु /* M2M */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, 0x344a),
		.driver_data = UNCORE_PCI_DEV_FULL_DATA(12, 0, SNR_PCI_UNCORE_M2M, 0),
	पूर्ण,
	अणु /* end: all zeroes */ पूर्ण
पूर्ण;

अटल काष्ठा pci_driver snr_uncore_pci_driver = अणु
	.name		= "snr_uncore",
	.id_table	= snr_uncore_pci_ids,
पूर्ण;

अटल स्थिर काष्ठा pci_device_id snr_uncore_pci_sub_ids[] = अणु
	अणु /* PCIe3 RP */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, 0x334a),
		.driver_data = UNCORE_PCI_DEV_FULL_DATA(4, 0, SNR_PCI_UNCORE_PCIE3, 0),
	पूर्ण,
	अणु /* end: all zeroes */ पूर्ण
पूर्ण;

अटल काष्ठा pci_driver snr_uncore_pci_sub_driver = अणु
	.name		= "snr_uncore_sub",
	.id_table	= snr_uncore_pci_sub_ids,
पूर्ण;

पूर्णांक snr_uncore_pci_init(व्योम)
अणु
	/* SNR UBOX DID */
	पूर्णांक ret = snbep_pci2phy_map_init(0x3460, SKX_CPUNODEID,
					 SKX_GIDNIDMAP, true);

	अगर (ret)
		वापस ret;

	uncore_pci_uncores = snr_pci_uncores;
	uncore_pci_driver = &snr_uncore_pci_driver;
	uncore_pci_sub_driver = &snr_uncore_pci_sub_driver;
	वापस 0;
पूर्ण

अटल काष्ठा pci_dev *snr_uncore_get_mc_dev(पूर्णांक id)
अणु
	काष्ठा pci_dev *mc_dev = शून्य;
	पूर्णांक pkg;

	जबतक (1) अणु
		mc_dev = pci_get_device(PCI_VENDOR_ID_INTEL, 0x3451, mc_dev);
		अगर (!mc_dev)
			अवरोध;
		pkg = uncore_pcibus_to_dieid(mc_dev->bus);
		अगर (pkg == id)
			अवरोध;
	पूर्ण
	वापस mc_dev;
पूर्ण

अटल व्योम __snr_uncore_mmio_init_box(काष्ठा पूर्णांकel_uncore_box *box,
				       अचिन्हित पूर्णांक box_ctl, पूर्णांक mem_offset)
अणु
	काष्ठा pci_dev *pdev = snr_uncore_get_mc_dev(box->dieid);
	काष्ठा पूर्णांकel_uncore_type *type = box->pmu->type;
	resource_माप_प्रकार addr;
	u32 pci_dword;

	अगर (!pdev)
		वापस;

	pci_पढ़ो_config_dword(pdev, SNR_IMC_MMIO_BASE_OFFSET, &pci_dword);
	addr = (pci_dword & SNR_IMC_MMIO_BASE_MASK) << 23;

	pci_पढ़ो_config_dword(pdev, mem_offset, &pci_dword);
	addr |= (pci_dword & SNR_IMC_MMIO_MEM0_MASK) << 12;

	addr += box_ctl;

	box->io_addr = ioremap(addr, type->mmio_map_size);
	अगर (!box->io_addr) अणु
		pr_warn("perf uncore: Failed to ioremap for %s.\n", type->name);
		वापस;
	पूर्ण

	ग_लिखोl(IVBEP_PMON_BOX_CTL_INT, box->io_addr);
पूर्ण

अटल व्योम snr_uncore_mmio_init_box(काष्ठा पूर्णांकel_uncore_box *box)
अणु
	__snr_uncore_mmio_init_box(box, uncore_mmio_box_ctl(box),
				   SNR_IMC_MMIO_MEM0_OFFSET);
पूर्ण

अटल व्योम snr_uncore_mmio_disable_box(काष्ठा पूर्णांकel_uncore_box *box)
अणु
	u32 config;

	अगर (!box->io_addr)
		वापस;

	config = पढ़ोl(box->io_addr);
	config |= SNBEP_PMON_BOX_CTL_FRZ;
	ग_लिखोl(config, box->io_addr);
पूर्ण

अटल व्योम snr_uncore_mmio_enable_box(काष्ठा पूर्णांकel_uncore_box *box)
अणु
	u32 config;

	अगर (!box->io_addr)
		वापस;

	config = पढ़ोl(box->io_addr);
	config &= ~SNBEP_PMON_BOX_CTL_FRZ;
	ग_लिखोl(config, box->io_addr);
पूर्ण

अटल व्योम snr_uncore_mmio_enable_event(काष्ठा पूर्णांकel_uncore_box *box,
					   काष्ठा perf_event *event)
अणु
	काष्ठा hw_perf_event *hwc = &event->hw;

	अगर (!box->io_addr)
		वापस;

	अगर (!uncore_mmio_is_valid_offset(box, hwc->config_base))
		वापस;

	ग_लिखोl(hwc->config | SNBEP_PMON_CTL_EN,
	       box->io_addr + hwc->config_base);
पूर्ण

अटल व्योम snr_uncore_mmio_disable_event(काष्ठा पूर्णांकel_uncore_box *box,
					    काष्ठा perf_event *event)
अणु
	काष्ठा hw_perf_event *hwc = &event->hw;

	अगर (!box->io_addr)
		वापस;

	अगर (!uncore_mmio_is_valid_offset(box, hwc->config_base))
		वापस;

	ग_लिखोl(hwc->config, box->io_addr + hwc->config_base);
पूर्ण

अटल काष्ठा पूर्णांकel_uncore_ops snr_uncore_mmio_ops = अणु
	.init_box	= snr_uncore_mmio_init_box,
	.निकास_box	= uncore_mmio_निकास_box,
	.disable_box	= snr_uncore_mmio_disable_box,
	.enable_box	= snr_uncore_mmio_enable_box,
	.disable_event	= snr_uncore_mmio_disable_event,
	.enable_event	= snr_uncore_mmio_enable_event,
	.पढ़ो_counter	= uncore_mmio_पढ़ो_counter,
पूर्ण;

अटल काष्ठा uncore_event_desc snr_uncore_imc_events[] = अणु
	INTEL_UNCORE_EVENT_DESC(घड़ीticks,      "event=0x00,umask=0x00"),
	INTEL_UNCORE_EVENT_DESC(cas_count_पढ़ो,  "event=0x04,umask=0x0f"),
	INTEL_UNCORE_EVENT_DESC(cas_count_पढ़ो.scale, "6.103515625e-5"),
	INTEL_UNCORE_EVENT_DESC(cas_count_पढ़ो.unit, "MiB"),
	INTEL_UNCORE_EVENT_DESC(cas_count_ग_लिखो, "event=0x04,umask=0x30"),
	INTEL_UNCORE_EVENT_DESC(cas_count_ग_लिखो.scale, "6.103515625e-5"),
	INTEL_UNCORE_EVENT_DESC(cas_count_ग_लिखो.unit, "MiB"),
	अणु /* end: all zeroes */ पूर्ण,
पूर्ण;

अटल काष्ठा पूर्णांकel_uncore_type snr_uncore_imc = अणु
	.name		= "imc",
	.num_counters   = 4,
	.num_boxes	= 2,
	.perf_ctr_bits	= 48,
	.fixed_ctr_bits	= 48,
	.fixed_ctr	= SNR_IMC_MMIO_PMON_FIXED_CTR,
	.fixed_ctl	= SNR_IMC_MMIO_PMON_FIXED_CTL,
	.event_descs	= snr_uncore_imc_events,
	.perf_ctr	= SNR_IMC_MMIO_PMON_CTR0,
	.event_ctl	= SNR_IMC_MMIO_PMON_CTL0,
	.event_mask	= SNBEP_PMON_RAW_EVENT_MASK,
	.box_ctl	= SNR_IMC_MMIO_PMON_BOX_CTL,
	.mmio_offset	= SNR_IMC_MMIO_OFFSET,
	.mmio_map_size	= SNR_IMC_MMIO_SIZE,
	.ops		= &snr_uncore_mmio_ops,
	.क्रमmat_group	= &skx_uncore_क्रमmat_group,
पूर्ण;

क्रमागत perf_uncore_snr_imc_मुक्तrunning_type_id अणु
	SNR_IMC_DCLK,
	SNR_IMC_DDR,

	SNR_IMC_FREERUNNING_TYPE_MAX,
पूर्ण;

अटल काष्ठा मुक्तrunning_counters snr_imc_मुक्तrunning[] = अणु
	[SNR_IMC_DCLK]	= अणु 0x22b0, 0x0, 0, 1, 48 पूर्ण,
	[SNR_IMC_DDR]	= अणु 0x2290, 0x8, 0, 2, 48 पूर्ण,
पूर्ण;

अटल काष्ठा uncore_event_desc snr_uncore_imc_मुक्तrunning_events[] = अणु
	INTEL_UNCORE_EVENT_DESC(dclk,		"event=0xff,umask=0x10"),

	INTEL_UNCORE_EVENT_DESC(पढ़ो,		"event=0xff,umask=0x20"),
	INTEL_UNCORE_EVENT_DESC(पढ़ो.scale,	"6.103515625e-5"),
	INTEL_UNCORE_EVENT_DESC(पढ़ो.unit,	"MiB"),
	INTEL_UNCORE_EVENT_DESC(ग_लिखो,		"event=0xff,umask=0x21"),
	INTEL_UNCORE_EVENT_DESC(ग_लिखो.scale,	"6.103515625e-5"),
	INTEL_UNCORE_EVENT_DESC(ग_लिखो.unit,	"MiB"),
	अणु /* end: all zeroes */ पूर्ण,
पूर्ण;

अटल काष्ठा पूर्णांकel_uncore_ops snr_uncore_imc_मुक्तrunning_ops = अणु
	.init_box	= snr_uncore_mmio_init_box,
	.निकास_box	= uncore_mmio_निकास_box,
	.पढ़ो_counter	= uncore_mmio_पढ़ो_counter,
	.hw_config	= uncore_मुक्तrunning_hw_config,
पूर्ण;

अटल काष्ठा पूर्णांकel_uncore_type snr_uncore_imc_मुक्त_running = अणु
	.name			= "imc_free_running",
	.num_counters		= 3,
	.num_boxes		= 1,
	.num_मुक्तrunning_types	= SNR_IMC_FREERUNNING_TYPE_MAX,
	.mmio_map_size		= SNR_IMC_MMIO_SIZE,
	.मुक्तrunning		= snr_imc_मुक्तrunning,
	.ops			= &snr_uncore_imc_मुक्तrunning_ops,
	.event_descs		= snr_uncore_imc_मुक्तrunning_events,
	.क्रमmat_group		= &skx_uncore_iio_मुक्तrunning_क्रमmat_group,
पूर्ण;

अटल काष्ठा पूर्णांकel_uncore_type *snr_mmio_uncores[] = अणु
	&snr_uncore_imc,
	&snr_uncore_imc_मुक्त_running,
	शून्य,
पूर्ण;

व्योम snr_uncore_mmio_init(व्योम)
अणु
	uncore_mmio_uncores = snr_mmio_uncores;
पूर्ण

/* end of SNR uncore support */

/* ICX uncore support */

अटल अचिन्हित icx_cha_msr_offsets[] = अणु
	0x2a0, 0x2ae, 0x2bc, 0x2ca, 0x2d8, 0x2e6, 0x2f4, 0x302, 0x310,
	0x31e, 0x32c, 0x33a, 0x348, 0x356, 0x364, 0x372, 0x380, 0x38e,
	0x3aa, 0x3b8, 0x3c6, 0x3d4, 0x3e2, 0x3f0, 0x3fe, 0x40c, 0x41a,
	0x428, 0x436, 0x444, 0x452, 0x460, 0x46e, 0x47c, 0x0,   0xe,
	0x1c,  0x2a,  0x38,  0x46,
पूर्ण;

अटल पूर्णांक icx_cha_hw_config(काष्ठा पूर्णांकel_uncore_box *box, काष्ठा perf_event *event)
अणु
	काष्ठा hw_perf_event_extra *reg1 = &event->hw.extra_reg;
	bool tie_en = !!(event->hw.config & SNBEP_CBO_PMON_CTL_TID_EN);

	अगर (tie_en) अणु
		reg1->reg = ICX_C34_MSR_PMON_BOX_FILTER0 +
			    icx_cha_msr_offsets[box->pmu->pmu_idx];
		reg1->config = event->attr.config1 & SKX_CHA_MSR_PMON_BOX_FILTER_TID;
		reg1->idx = 0;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा पूर्णांकel_uncore_ops icx_uncore_chabox_ops = अणु
	.init_box		= ivbep_uncore_msr_init_box,
	.disable_box		= snbep_uncore_msr_disable_box,
	.enable_box		= snbep_uncore_msr_enable_box,
	.disable_event		= snbep_uncore_msr_disable_event,
	.enable_event		= snr_cha_enable_event,
	.पढ़ो_counter		= uncore_msr_पढ़ो_counter,
	.hw_config		= icx_cha_hw_config,
पूर्ण;

अटल काष्ठा पूर्णांकel_uncore_type icx_uncore_chabox = अणु
	.name			= "cha",
	.num_counters		= 4,
	.perf_ctr_bits		= 48,
	.event_ctl		= ICX_C34_MSR_PMON_CTL0,
	.perf_ctr		= ICX_C34_MSR_PMON_CTR0,
	.box_ctl		= ICX_C34_MSR_PMON_BOX_CTL,
	.msr_offsets		= icx_cha_msr_offsets,
	.event_mask		= HSWEP_S_MSR_PMON_RAW_EVENT_MASK,
	.event_mask_ext		= SNR_CHA_RAW_EVENT_MASK_EXT,
	.स्थिरraपूर्णांकs		= skx_uncore_chabox_स्थिरraपूर्णांकs,
	.ops			= &icx_uncore_chabox_ops,
	.क्रमmat_group		= &snr_uncore_chabox_क्रमmat_group,
पूर्ण;

अटल अचिन्हित icx_msr_offsets[] = अणु
	0x0, 0x20, 0x40, 0x90, 0xb0, 0xd0,
पूर्ण;

अटल काष्ठा event_स्थिरraपूर्णांक icx_uncore_iio_स्थिरraपूर्णांकs[] = अणु
	UNCORE_EVENT_CONSTRAINT(0x02, 0x3),
	UNCORE_EVENT_CONSTRAINT(0x03, 0x3),
	UNCORE_EVENT_CONSTRAINT(0x83, 0x3),
	UNCORE_EVENT_CONSTRAINT(0xc0, 0xc),
	UNCORE_EVENT_CONSTRAINT(0xc5, 0xc),
	EVENT_CONSTRAINT_END
पूर्ण;

अटल काष्ठा पूर्णांकel_uncore_type icx_uncore_iio = अणु
	.name			= "iio",
	.num_counters		= 4,
	.num_boxes		= 6,
	.perf_ctr_bits		= 48,
	.event_ctl		= ICX_IIO_MSR_PMON_CTL0,
	.perf_ctr		= ICX_IIO_MSR_PMON_CTR0,
	.event_mask		= SNBEP_PMON_RAW_EVENT_MASK,
	.event_mask_ext		= SNR_IIO_PMON_RAW_EVENT_MASK_EXT,
	.box_ctl		= ICX_IIO_MSR_PMON_BOX_CTL,
	.msr_offsets		= icx_msr_offsets,
	.स्थिरraपूर्णांकs		= icx_uncore_iio_स्थिरraपूर्णांकs,
	.ops			= &skx_uncore_iio_ops,
	.क्रमmat_group		= &snr_uncore_iio_क्रमmat_group,
पूर्ण;

अटल काष्ठा पूर्णांकel_uncore_type icx_uncore_irp = अणु
	.name			= "irp",
	.num_counters		= 2,
	.num_boxes		= 6,
	.perf_ctr_bits		= 48,
	.event_ctl		= ICX_IRP0_MSR_PMON_CTL0,
	.perf_ctr		= ICX_IRP0_MSR_PMON_CTR0,
	.event_mask		= SNBEP_PMON_RAW_EVENT_MASK,
	.box_ctl		= ICX_IRP0_MSR_PMON_BOX_CTL,
	.msr_offsets		= icx_msr_offsets,
	.ops			= &ivbep_uncore_msr_ops,
	.क्रमmat_group		= &ivbep_uncore_क्रमmat_group,
पूर्ण;

अटल काष्ठा event_स्थिरraपूर्णांक icx_uncore_m2pcie_स्थिरraपूर्णांकs[] = अणु
	UNCORE_EVENT_CONSTRAINT(0x14, 0x3),
	UNCORE_EVENT_CONSTRAINT(0x23, 0x3),
	UNCORE_EVENT_CONSTRAINT(0x2d, 0x3),
	EVENT_CONSTRAINT_END
पूर्ण;

अटल काष्ठा पूर्णांकel_uncore_type icx_uncore_m2pcie = अणु
	.name		= "m2pcie",
	.num_counters	= 4,
	.num_boxes	= 6,
	.perf_ctr_bits	= 48,
	.event_ctl	= ICX_M2PCIE_MSR_PMON_CTL0,
	.perf_ctr	= ICX_M2PCIE_MSR_PMON_CTR0,
	.box_ctl	= ICX_M2PCIE_MSR_PMON_BOX_CTL,
	.msr_offsets	= icx_msr_offsets,
	.स्थिरraपूर्णांकs	= icx_uncore_m2pcie_स्थिरraपूर्णांकs,
	.event_mask	= SNBEP_PMON_RAW_EVENT_MASK,
	.ops		= &ivbep_uncore_msr_ops,
	.क्रमmat_group	= &ivbep_uncore_क्रमmat_group,
पूर्ण;

क्रमागत perf_uncore_icx_iio_मुक्तrunning_type_id अणु
	ICX_IIO_MSR_IOCLK,
	ICX_IIO_MSR_BW_IN,

	ICX_IIO_FREERUNNING_TYPE_MAX,
पूर्ण;

अटल अचिन्हित icx_iio_clk_मुक्तrunning_box_offsets[] = अणु
	0x0, 0x20, 0x40, 0x90, 0xb0, 0xd0,
पूर्ण;

अटल अचिन्हित icx_iio_bw_मुक्तrunning_box_offsets[] = अणु
	0x0, 0x10, 0x20, 0x90, 0xa0, 0xb0,
पूर्ण;

अटल काष्ठा मुक्तrunning_counters icx_iio_मुक्तrunning[] = अणु
	[ICX_IIO_MSR_IOCLK]	= अणु 0xa55, 0x1, 0x20, 1, 48, icx_iio_clk_मुक्तrunning_box_offsets पूर्ण,
	[ICX_IIO_MSR_BW_IN]	= अणु 0xaa0, 0x1, 0x10, 8, 48, icx_iio_bw_मुक्तrunning_box_offsets पूर्ण,
पूर्ण;

अटल काष्ठा uncore_event_desc icx_uncore_iio_मुक्तrunning_events[] = अणु
	/* Free-Running IIO CLOCKS Counter */
	INTEL_UNCORE_EVENT_DESC(ioclk,			"event=0xff,umask=0x10"),
	/* Free-Running IIO BANDWIDTH IN Counters */
	INTEL_UNCORE_EVENT_DESC(bw_in_port0,		"event=0xff,umask=0x20"),
	INTEL_UNCORE_EVENT_DESC(bw_in_port0.scale,	"3.814697266e-6"),
	INTEL_UNCORE_EVENT_DESC(bw_in_port0.unit,	"MiB"),
	INTEL_UNCORE_EVENT_DESC(bw_in_port1,		"event=0xff,umask=0x21"),
	INTEL_UNCORE_EVENT_DESC(bw_in_port1.scale,	"3.814697266e-6"),
	INTEL_UNCORE_EVENT_DESC(bw_in_port1.unit,	"MiB"),
	INTEL_UNCORE_EVENT_DESC(bw_in_port2,		"event=0xff,umask=0x22"),
	INTEL_UNCORE_EVENT_DESC(bw_in_port2.scale,	"3.814697266e-6"),
	INTEL_UNCORE_EVENT_DESC(bw_in_port2.unit,	"MiB"),
	INTEL_UNCORE_EVENT_DESC(bw_in_port3,		"event=0xff,umask=0x23"),
	INTEL_UNCORE_EVENT_DESC(bw_in_port3.scale,	"3.814697266e-6"),
	INTEL_UNCORE_EVENT_DESC(bw_in_port3.unit,	"MiB"),
	INTEL_UNCORE_EVENT_DESC(bw_in_port4,		"event=0xff,umask=0x24"),
	INTEL_UNCORE_EVENT_DESC(bw_in_port4.scale,	"3.814697266e-6"),
	INTEL_UNCORE_EVENT_DESC(bw_in_port4.unit,	"MiB"),
	INTEL_UNCORE_EVENT_DESC(bw_in_port5,		"event=0xff,umask=0x25"),
	INTEL_UNCORE_EVENT_DESC(bw_in_port5.scale,	"3.814697266e-6"),
	INTEL_UNCORE_EVENT_DESC(bw_in_port5.unit,	"MiB"),
	INTEL_UNCORE_EVENT_DESC(bw_in_port6,		"event=0xff,umask=0x26"),
	INTEL_UNCORE_EVENT_DESC(bw_in_port6.scale,	"3.814697266e-6"),
	INTEL_UNCORE_EVENT_DESC(bw_in_port6.unit,	"MiB"),
	INTEL_UNCORE_EVENT_DESC(bw_in_port7,		"event=0xff,umask=0x27"),
	INTEL_UNCORE_EVENT_DESC(bw_in_port7.scale,	"3.814697266e-6"),
	INTEL_UNCORE_EVENT_DESC(bw_in_port7.unit,	"MiB"),
	अणु /* end: all zeroes */ पूर्ण,
पूर्ण;

अटल काष्ठा पूर्णांकel_uncore_type icx_uncore_iio_मुक्त_running = अणु
	.name			= "iio_free_running",
	.num_counters		= 9,
	.num_boxes		= 6,
	.num_मुक्तrunning_types	= ICX_IIO_FREERUNNING_TYPE_MAX,
	.मुक्तrunning		= icx_iio_मुक्तrunning,
	.ops			= &skx_uncore_iio_मुक्तrunning_ops,
	.event_descs		= icx_uncore_iio_मुक्तrunning_events,
	.क्रमmat_group		= &skx_uncore_iio_मुक्तrunning_क्रमmat_group,
पूर्ण;

अटल काष्ठा पूर्णांकel_uncore_type *icx_msr_uncores[] = अणु
	&skx_uncore_ubox,
	&icx_uncore_chabox,
	&icx_uncore_iio,
	&icx_uncore_irp,
	&icx_uncore_m2pcie,
	&skx_uncore_pcu,
	&icx_uncore_iio_मुक्त_running,
	शून्य,
पूर्ण;

/*
 * To determine the number of CHAs, it should पढ़ो CAPID6(Low) and CAPID7 (High)
 * रेजिस्टरs which located at Device 30, Function 3
 */
#घोषणा ICX_CAPID6		0x9c
#घोषणा ICX_CAPID7		0xa0

अटल u64 icx_count_chabox(व्योम)
अणु
	काष्ठा pci_dev *dev = शून्य;
	u64 caps = 0;

	dev = pci_get_device(PCI_VENDOR_ID_INTEL, 0x345b, dev);
	अगर (!dev)
		जाओ out;

	pci_पढ़ो_config_dword(dev, ICX_CAPID6, (u32 *)&caps);
	pci_पढ़ो_config_dword(dev, ICX_CAPID7, (u32 *)&caps + 1);
out:
	pci_dev_put(dev);
	वापस hweight64(caps);
पूर्ण

व्योम icx_uncore_cpu_init(व्योम)
अणु
	u64 num_boxes = icx_count_chabox();

	अगर (WARN_ON(num_boxes > ARRAY_SIZE(icx_cha_msr_offsets)))
		वापस;
	icx_uncore_chabox.num_boxes = num_boxes;
	uncore_msr_uncores = icx_msr_uncores;
पूर्ण

अटल काष्ठा पूर्णांकel_uncore_type icx_uncore_m2m = अणु
	.name		= "m2m",
	.num_counters   = 4,
	.num_boxes	= 4,
	.perf_ctr_bits	= 48,
	.perf_ctr	= SNR_M2M_PCI_PMON_CTR0,
	.event_ctl	= SNR_M2M_PCI_PMON_CTL0,
	.event_mask	= SNBEP_PMON_RAW_EVENT_MASK,
	.event_mask_ext	= SNR_M2M_PCI_PMON_UMASK_EXT,
	.box_ctl	= SNR_M2M_PCI_PMON_BOX_CTL,
	.ops		= &snr_m2m_uncore_pci_ops,
	.क्रमmat_group	= &snr_m2m_uncore_क्रमmat_group,
पूर्ण;

अटल काष्ठा attribute *icx_upi_uncore_क्रमmats_attr[] = अणु
	&क्रमmat_attr_event.attr,
	&क्रमmat_attr_umask_ext4.attr,
	&क्रमmat_attr_edge.attr,
	&क्रमmat_attr_inv.attr,
	&क्रमmat_attr_thresh8.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group icx_upi_uncore_क्रमmat_group = अणु
	.name = "format",
	.attrs = icx_upi_uncore_क्रमmats_attr,
पूर्ण;

अटल काष्ठा पूर्णांकel_uncore_type icx_uncore_upi = अणु
	.name		= "upi",
	.num_counters   = 4,
	.num_boxes	= 3,
	.perf_ctr_bits	= 48,
	.perf_ctr	= ICX_UPI_PCI_PMON_CTR0,
	.event_ctl	= ICX_UPI_PCI_PMON_CTL0,
	.event_mask	= SNBEP_PMON_RAW_EVENT_MASK,
	.event_mask_ext = ICX_UPI_CTL_UMASK_EXT,
	.box_ctl	= ICX_UPI_PCI_PMON_BOX_CTL,
	.ops		= &skx_upi_uncore_pci_ops,
	.क्रमmat_group	= &icx_upi_uncore_क्रमmat_group,
पूर्ण;

अटल काष्ठा event_स्थिरraपूर्णांक icx_uncore_m3upi_स्थिरraपूर्णांकs[] = अणु
	UNCORE_EVENT_CONSTRAINT(0x1c, 0x1),
	UNCORE_EVENT_CONSTRAINT(0x1d, 0x1),
	UNCORE_EVENT_CONSTRAINT(0x1e, 0x1),
	UNCORE_EVENT_CONSTRAINT(0x1f, 0x1),
	UNCORE_EVENT_CONSTRAINT(0x40, 0x7),
	UNCORE_EVENT_CONSTRAINT(0x4e, 0x7),
	UNCORE_EVENT_CONSTRAINT(0x4f, 0x7),
	UNCORE_EVENT_CONSTRAINT(0x50, 0x7),
	EVENT_CONSTRAINT_END
पूर्ण;

अटल काष्ठा पूर्णांकel_uncore_type icx_uncore_m3upi = अणु
	.name		= "m3upi",
	.num_counters   = 4,
	.num_boxes	= 3,
	.perf_ctr_bits	= 48,
	.perf_ctr	= ICX_M3UPI_PCI_PMON_CTR0,
	.event_ctl	= ICX_M3UPI_PCI_PMON_CTL0,
	.event_mask	= SNBEP_PMON_RAW_EVENT_MASK,
	.box_ctl	= ICX_M3UPI_PCI_PMON_BOX_CTL,
	.स्थिरraपूर्णांकs	= icx_uncore_m3upi_स्थिरraपूर्णांकs,
	.ops		= &ivbep_uncore_pci_ops,
	.क्रमmat_group	= &skx_uncore_क्रमmat_group,
पूर्ण;

क्रमागत अणु
	ICX_PCI_UNCORE_M2M,
	ICX_PCI_UNCORE_UPI,
	ICX_PCI_UNCORE_M3UPI,
पूर्ण;

अटल काष्ठा पूर्णांकel_uncore_type *icx_pci_uncores[] = अणु
	[ICX_PCI_UNCORE_M2M]		= &icx_uncore_m2m,
	[ICX_PCI_UNCORE_UPI]		= &icx_uncore_upi,
	[ICX_PCI_UNCORE_M3UPI]		= &icx_uncore_m3upi,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा pci_device_id icx_uncore_pci_ids[] = अणु
	अणु /* M2M 0 */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, 0x344a),
		.driver_data = UNCORE_PCI_DEV_FULL_DATA(12, 0, ICX_PCI_UNCORE_M2M, 0),
	पूर्ण,
	अणु /* M2M 1 */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, 0x344a),
		.driver_data = UNCORE_PCI_DEV_FULL_DATA(13, 0, ICX_PCI_UNCORE_M2M, 1),
	पूर्ण,
	अणु /* M2M 2 */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, 0x344a),
		.driver_data = UNCORE_PCI_DEV_FULL_DATA(14, 0, ICX_PCI_UNCORE_M2M, 2),
	पूर्ण,
	अणु /* M2M 3 */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, 0x344a),
		.driver_data = UNCORE_PCI_DEV_FULL_DATA(15, 0, ICX_PCI_UNCORE_M2M, 3),
	पूर्ण,
	अणु /* UPI Link 0 */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, 0x3441),
		.driver_data = UNCORE_PCI_DEV_FULL_DATA(2, 1, ICX_PCI_UNCORE_UPI, 0),
	पूर्ण,
	अणु /* UPI Link 1 */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, 0x3441),
		.driver_data = UNCORE_PCI_DEV_FULL_DATA(3, 1, ICX_PCI_UNCORE_UPI, 1),
	पूर्ण,
	अणु /* UPI Link 2 */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, 0x3441),
		.driver_data = UNCORE_PCI_DEV_FULL_DATA(4, 1, ICX_PCI_UNCORE_UPI, 2),
	पूर्ण,
	अणु /* M3UPI Link 0 */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, 0x3446),
		.driver_data = UNCORE_PCI_DEV_FULL_DATA(5, 1, ICX_PCI_UNCORE_M3UPI, 0),
	पूर्ण,
	अणु /* M3UPI Link 1 */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, 0x3446),
		.driver_data = UNCORE_PCI_DEV_FULL_DATA(6, 1, ICX_PCI_UNCORE_M3UPI, 1),
	पूर्ण,
	अणु /* M3UPI Link 2 */
		PCI_DEVICE(PCI_VENDOR_ID_INTEL, 0x3446),
		.driver_data = UNCORE_PCI_DEV_FULL_DATA(7, 1, ICX_PCI_UNCORE_M3UPI, 2),
	पूर्ण,
	अणु /* end: all zeroes */ पूर्ण
पूर्ण;

अटल काष्ठा pci_driver icx_uncore_pci_driver = अणु
	.name		= "icx_uncore",
	.id_table	= icx_uncore_pci_ids,
पूर्ण;

पूर्णांक icx_uncore_pci_init(व्योम)
अणु
	/* ICX UBOX DID */
	पूर्णांक ret = snbep_pci2phy_map_init(0x3450, SKX_CPUNODEID,
					 SKX_GIDNIDMAP, true);

	अगर (ret)
		वापस ret;

	uncore_pci_uncores = icx_pci_uncores;
	uncore_pci_driver = &icx_uncore_pci_driver;
	वापस 0;
पूर्ण

अटल व्योम icx_uncore_imc_init_box(काष्ठा पूर्णांकel_uncore_box *box)
अणु
	अचिन्हित पूर्णांक box_ctl = box->pmu->type->box_ctl +
			       box->pmu->type->mmio_offset * (box->pmu->pmu_idx % ICX_NUMBER_IMC_CHN);
	पूर्णांक mem_offset = (box->pmu->pmu_idx / ICX_NUMBER_IMC_CHN) * ICX_IMC_MEM_STRIDE +
			 SNR_IMC_MMIO_MEM0_OFFSET;

	__snr_uncore_mmio_init_box(box, box_ctl, mem_offset);
पूर्ण

अटल काष्ठा पूर्णांकel_uncore_ops icx_uncore_mmio_ops = अणु
	.init_box	= icx_uncore_imc_init_box,
	.निकास_box	= uncore_mmio_निकास_box,
	.disable_box	= snr_uncore_mmio_disable_box,
	.enable_box	= snr_uncore_mmio_enable_box,
	.disable_event	= snr_uncore_mmio_disable_event,
	.enable_event	= snr_uncore_mmio_enable_event,
	.पढ़ो_counter	= uncore_mmio_पढ़ो_counter,
पूर्ण;

अटल काष्ठा पूर्णांकel_uncore_type icx_uncore_imc = अणु
	.name		= "imc",
	.num_counters   = 4,
	.num_boxes	= 8,
	.perf_ctr_bits	= 48,
	.fixed_ctr_bits	= 48,
	.fixed_ctr	= SNR_IMC_MMIO_PMON_FIXED_CTR,
	.fixed_ctl	= SNR_IMC_MMIO_PMON_FIXED_CTL,
	.event_descs	= hswep_uncore_imc_events,
	.perf_ctr	= SNR_IMC_MMIO_PMON_CTR0,
	.event_ctl	= SNR_IMC_MMIO_PMON_CTL0,
	.event_mask	= SNBEP_PMON_RAW_EVENT_MASK,
	.box_ctl	= SNR_IMC_MMIO_PMON_BOX_CTL,
	.mmio_offset	= SNR_IMC_MMIO_OFFSET,
	.mmio_map_size	= SNR_IMC_MMIO_SIZE,
	.ops		= &icx_uncore_mmio_ops,
	.क्रमmat_group	= &skx_uncore_क्रमmat_group,
पूर्ण;

क्रमागत perf_uncore_icx_imc_मुक्तrunning_type_id अणु
	ICX_IMC_DCLK,
	ICX_IMC_DDR,
	ICX_IMC_DDRT,

	ICX_IMC_FREERUNNING_TYPE_MAX,
पूर्ण;

अटल काष्ठा मुक्तrunning_counters icx_imc_मुक्तrunning[] = अणु
	[ICX_IMC_DCLK]	= अणु 0x22b0, 0x0, 0, 1, 48 पूर्ण,
	[ICX_IMC_DDR]	= अणु 0x2290, 0x8, 0, 2, 48 पूर्ण,
	[ICX_IMC_DDRT]	= अणु 0x22a0, 0x8, 0, 2, 48 पूर्ण,
पूर्ण;

अटल काष्ठा uncore_event_desc icx_uncore_imc_मुक्तrunning_events[] = अणु
	INTEL_UNCORE_EVENT_DESC(dclk,			"event=0xff,umask=0x10"),

	INTEL_UNCORE_EVENT_DESC(पढ़ो,			"event=0xff,umask=0x20"),
	INTEL_UNCORE_EVENT_DESC(पढ़ो.scale,		"6.103515625e-5"),
	INTEL_UNCORE_EVENT_DESC(पढ़ो.unit,		"MiB"),
	INTEL_UNCORE_EVENT_DESC(ग_लिखो,			"event=0xff,umask=0x21"),
	INTEL_UNCORE_EVENT_DESC(ग_लिखो.scale,		"6.103515625e-5"),
	INTEL_UNCORE_EVENT_DESC(ग_लिखो.unit,		"MiB"),

	INTEL_UNCORE_EVENT_DESC(ddrt_पढ़ो,		"event=0xff,umask=0x30"),
	INTEL_UNCORE_EVENT_DESC(ddrt_पढ़ो.scale,	"6.103515625e-5"),
	INTEL_UNCORE_EVENT_DESC(ddrt_पढ़ो.unit,		"MiB"),
	INTEL_UNCORE_EVENT_DESC(ddrt_ग_लिखो,		"event=0xff,umask=0x31"),
	INTEL_UNCORE_EVENT_DESC(ddrt_ग_लिखो.scale,	"6.103515625e-5"),
	INTEL_UNCORE_EVENT_DESC(ddrt_ग_लिखो.unit,	"MiB"),
	अणु /* end: all zeroes */ पूर्ण,
पूर्ण;

अटल व्योम icx_uncore_imc_मुक्तrunning_init_box(काष्ठा पूर्णांकel_uncore_box *box)
अणु
	पूर्णांक mem_offset = box->pmu->pmu_idx * ICX_IMC_MEM_STRIDE +
			 SNR_IMC_MMIO_MEM0_OFFSET;

	__snr_uncore_mmio_init_box(box, uncore_mmio_box_ctl(box), mem_offset);
पूर्ण

अटल काष्ठा पूर्णांकel_uncore_ops icx_uncore_imc_मुक्तrunning_ops = अणु
	.init_box	= icx_uncore_imc_मुक्तrunning_init_box,
	.निकास_box	= uncore_mmio_निकास_box,
	.पढ़ो_counter	= uncore_mmio_पढ़ो_counter,
	.hw_config	= uncore_मुक्तrunning_hw_config,
पूर्ण;

अटल काष्ठा पूर्णांकel_uncore_type icx_uncore_imc_मुक्त_running = अणु
	.name			= "imc_free_running",
	.num_counters		= 5,
	.num_boxes		= 4,
	.num_मुक्तrunning_types	= ICX_IMC_FREERUNNING_TYPE_MAX,
	.mmio_map_size		= SNR_IMC_MMIO_SIZE,
	.मुक्तrunning		= icx_imc_मुक्तrunning,
	.ops			= &icx_uncore_imc_मुक्तrunning_ops,
	.event_descs		= icx_uncore_imc_मुक्तrunning_events,
	.क्रमmat_group		= &skx_uncore_iio_मुक्तrunning_क्रमmat_group,
पूर्ण;

अटल काष्ठा पूर्णांकel_uncore_type *icx_mmio_uncores[] = अणु
	&icx_uncore_imc,
	&icx_uncore_imc_मुक्त_running,
	शून्य,
पूर्ण;

व्योम icx_uncore_mmio_init(व्योम)
अणु
	uncore_mmio_uncores = icx_mmio_uncores;
पूर्ण

/* end of ICX uncore support */
