<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *
 * Copyright (C) 2013 Freescale Semiconductor, Inc.
 */

#अगर_अघोषित __FSL_PAMU_H
#घोषणा __FSL_PAMU_H

#समावेश <linux/iommu.h>
#समावेश <linux/pci.h>

#समावेश <यंत्र/fsl_pamu_stash.h>

/* Bit Field macros
 *	v = bit field variable; m = mask, m##_SHIFT = shअगरt, x = value to load
 */
#घोषणा set_bf(v, m, x)		(v = ((v) & ~(m)) | (((x) << m##_SHIFT) & (m)))
#घोषणा get_bf(v, m)		(((v) & (m)) >> m##_SHIFT)

/* PAMU CCSR space */
#घोषणा PAMU_PGC 0x00000000     /* Allows all peripheral accesses */
#घोषणा PAMU_PE 0x40000000      /* enable PAMU                    */

/* PAMU_OFFSET to the next pamu space in ccsr */
#घोषणा PAMU_OFFSET 0x1000

#घोषणा PAMU_MMAP_REGS_BASE 0

काष्ठा pamu_mmap_regs अणु
	u32 ppbah;
	u32 ppbal;
	u32 pplah;
	u32 pplal;
	u32 spbah;
	u32 spbal;
	u32 splah;
	u32 splal;
	u32 obah;
	u32 obal;
	u32 olah;
	u32 olal;
पूर्ण;

/* PAMU Error Registers */
#घोषणा PAMU_POES1 0x0040
#घोषणा PAMU_POES2 0x0044
#घोषणा PAMU_POEAH 0x0048
#घोषणा PAMU_POEAL 0x004C
#घोषणा PAMU_AVS1  0x0050
#घोषणा PAMU_AVS1_AV    0x1
#घोषणा PAMU_AVS1_OTV   0x6
#घोषणा PAMU_AVS1_APV   0x78
#घोषणा PAMU_AVS1_WAV   0x380
#घोषणा PAMU_AVS1_LAV   0x1c00
#घोषणा PAMU_AVS1_GCV   0x2000
#घोषणा PAMU_AVS1_PDV   0x4000
#घोषणा PAMU_AV_MASK    (PAMU_AVS1_AV | PAMU_AVS1_OTV | PAMU_AVS1_APV | PAMU_AVS1_WAV \
			 | PAMU_AVS1_LAV | PAMU_AVS1_GCV | PAMU_AVS1_PDV)
#घोषणा PAMU_AVS1_LIODN_SHIFT 16
#घोषणा PAMU_LAV_LIODN_NOT_IN_PPAACT 0x400

#घोषणा PAMU_AVS2  0x0054
#घोषणा PAMU_AVAH  0x0058
#घोषणा PAMU_AVAL  0x005C
#घोषणा PAMU_EECTL 0x0060
#घोषणा PAMU_EEDIS 0x0064
#घोषणा PAMU_EEINTEN 0x0068
#घोषणा PAMU_EEDET 0x006C
#घोषणा PAMU_EEATTR 0x0070
#घोषणा PAMU_EEAHI 0x0074
#घोषणा PAMU_EEALO 0x0078
#घोषणा PAMU_EEDHI 0X007C
#घोषणा PAMU_EEDLO 0x0080
#घोषणा PAMU_EECC  0x0084
#घोषणा PAMU_UDAD  0x0090

/* PAMU Revision Registers */
#घोषणा PAMU_PR1 0x0BF8
#घोषणा PAMU_PR2 0x0BFC

/* PAMU version mask */
#घोषणा PAMU_PR1_MASK 0xffff

/* PAMU Capabilities Registers */
#घोषणा PAMU_PC1 0x0C00
#घोषणा PAMU_PC2 0x0C04
#घोषणा PAMU_PC3 0x0C08
#घोषणा PAMU_PC4 0x0C0C

/* PAMU Control Register */
#घोषणा PAMU_PC 0x0C10

/* PAMU control defs */
#घोषणा PAMU_CONTROL 0x0C10
#घोषणा PAMU_PC_PGC 0x80000000  /* PAMU gate बंदd bit */
#घोषणा PAMU_PC_PE   0x40000000 /* PAMU enable bit */
#घोषणा PAMU_PC_SPCC 0x00000010 /* sPAACE cache enable */
#घोषणा PAMU_PC_PPCC 0x00000001 /* pPAACE cache enable */
#घोषणा PAMU_PC_OCE  0x00001000 /* OMT cache enable */

#घोषणा PAMU_PFA1 0x0C14
#घोषणा PAMU_PFA2 0x0C18

#घोषणा PAMU_PC2_MLIODN(X) ((X) >> 16)
#घोषणा PAMU_PC3_MWCE(X) (((X) >> 21) & 0xf)

/* PAMU Interrupt control and Status Register */
#घोषणा PAMU_PICS 0x0C1C
#घोषणा PAMU_ACCESS_VIOLATION_STAT   0x8
#घोषणा PAMU_ACCESS_VIOLATION_ENABLE 0x4

/* PAMU Debug Registers */
#घोषणा PAMU_PD1 0x0F00
#घोषणा PAMU_PD2 0x0F04
#घोषणा PAMU_PD3 0x0F08
#घोषणा PAMU_PD4 0x0F0C

#घोषणा PAACE_AP_PERMS_DENIED  0x0
#घोषणा PAACE_AP_PERMS_QUERY   0x1
#घोषणा PAACE_AP_PERMS_UPDATE  0x2
#घोषणा PAACE_AP_PERMS_ALL     0x3

#घोषणा PAACE_DD_TO_HOST       0x0
#घोषणा PAACE_DD_TO_IO         0x1
#घोषणा PAACE_PT_PRIMARY       0x0
#घोषणा PAACE_PT_SECONDARY     0x1
#घोषणा PAACE_V_INVALID        0x0
#घोषणा PAACE_V_VALID          0x1
#घोषणा PAACE_MW_SUBWINDOWS    0x1

#घोषणा PAACE_WSE_4K           0xB
#घोषणा PAACE_WSE_8K           0xC
#घोषणा PAACE_WSE_16K          0xD
#घोषणा PAACE_WSE_32K          0xE
#घोषणा PAACE_WSE_64K          0xF
#घोषणा PAACE_WSE_128K         0x10
#घोषणा PAACE_WSE_256K         0x11
#घोषणा PAACE_WSE_512K         0x12
#घोषणा PAACE_WSE_1M           0x13
#घोषणा PAACE_WSE_2M           0x14
#घोषणा PAACE_WSE_4M           0x15
#घोषणा PAACE_WSE_8M           0x16
#घोषणा PAACE_WSE_16M          0x17
#घोषणा PAACE_WSE_32M          0x18
#घोषणा PAACE_WSE_64M          0x19
#घोषणा PAACE_WSE_128M         0x1A
#घोषणा PAACE_WSE_256M         0x1B
#घोषणा PAACE_WSE_512M         0x1C
#घोषणा PAACE_WSE_1G           0x1D
#घोषणा PAACE_WSE_2G           0x1E
#घोषणा PAACE_WSE_4G           0x1F

#घोषणा PAACE_DID_PCI_EXPRESS_1 0x00
#घोषणा PAACE_DID_PCI_EXPRESS_2 0x01
#घोषणा PAACE_DID_PCI_EXPRESS_3 0x02
#घोषणा PAACE_DID_PCI_EXPRESS_4 0x03
#घोषणा PAACE_DID_LOCAL_BUS     0x04
#घोषणा PAACE_DID_SRIO          0x0C
#घोषणा PAACE_DID_MEM_1         0x10
#घोषणा PAACE_DID_MEM_2         0x11
#घोषणा PAACE_DID_MEM_3         0x12
#घोषणा PAACE_DID_MEM_4         0x13
#घोषणा PAACE_DID_MEM_1_2       0x14
#घोषणा PAACE_DID_MEM_3_4       0x15
#घोषणा PAACE_DID_MEM_1_4       0x16
#घोषणा PAACE_DID_BM_SW_PORTAL  0x18
#घोषणा PAACE_DID_PAMU          0x1C
#घोषणा PAACE_DID_CAAM          0x21
#घोषणा PAACE_DID_QM_SW_PORTAL  0x3C
#घोषणा PAACE_DID_CORE0_INST    0x80
#घोषणा PAACE_DID_CORE0_DATA    0x81
#घोषणा PAACE_DID_CORE1_INST    0x82
#घोषणा PAACE_DID_CORE1_DATA    0x83
#घोषणा PAACE_DID_CORE2_INST    0x84
#घोषणा PAACE_DID_CORE2_DATA    0x85
#घोषणा PAACE_DID_CORE3_INST    0x86
#घोषणा PAACE_DID_CORE3_DATA    0x87
#घोषणा PAACE_DID_CORE4_INST    0x88
#घोषणा PAACE_DID_CORE4_DATA    0x89
#घोषणा PAACE_DID_CORE5_INST    0x8A
#घोषणा PAACE_DID_CORE5_DATA    0x8B
#घोषणा PAACE_DID_CORE6_INST    0x8C
#घोषणा PAACE_DID_CORE6_DATA    0x8D
#घोषणा PAACE_DID_CORE7_INST    0x8E
#घोषणा PAACE_DID_CORE7_DATA    0x8F
#घोषणा PAACE_DID_BROADCAST     0xFF

#घोषणा PAACE_ATM_NO_XLATE      0x00
#घोषणा PAACE_ATM_WINDOW_XLATE  0x01
#घोषणा PAACE_ATM_PAGE_XLATE    0x02
#घोषणा PAACE_ATM_WIN_PG_XLATE  (PAACE_ATM_WINDOW_XLATE | PAACE_ATM_PAGE_XLATE)
#घोषणा PAACE_OTM_NO_XLATE      0x00
#घोषणा PAACE_OTM_IMMEDIATE     0x01
#घोषणा PAACE_OTM_INDEXED       0x02
#घोषणा PAACE_OTM_RESERVED      0x03

#घोषणा PAACE_M_COHERENCE_REQ   0x01

#घोषणा PAACE_PID_0             0x0
#घोषणा PAACE_PID_1             0x1
#घोषणा PAACE_PID_2             0x2
#घोषणा PAACE_PID_3             0x3
#घोषणा PAACE_PID_4             0x4
#घोषणा PAACE_PID_5             0x5
#घोषणा PAACE_PID_6             0x6
#घोषणा PAACE_PID_7             0x7

#घोषणा PAACE_TCEF_FORMAT0_8B   0x00
#घोषणा PAACE_TCEF_FORMAT1_RSVD 0x01
/*
 * Hard coded value क्रम the PAACT size to accommodate
 * maximum LIODN value generated by u-boot.
 */
#घोषणा PAACE_NUMBER_ENTRIES    0x500
/* Hard coded value क्रम the SPAACT size */
#घोषणा SPAACE_NUMBER_ENTRIES	0x800

#घोषणा	OME_NUMBER_ENTRIES      16

/* PAACE Bit Field Defines */
#घोषणा PPAACE_AF_WBAL			0xfffff000
#घोषणा PPAACE_AF_WBAL_SHIFT		12
#घोषणा PPAACE_AF_WSE			0x00000fc0
#घोषणा PPAACE_AF_WSE_SHIFT		6
#घोषणा PPAACE_AF_MW			0x00000020
#घोषणा PPAACE_AF_MW_SHIFT		5

#घोषणा SPAACE_AF_LIODN			0xffff0000
#घोषणा SPAACE_AF_LIODN_SHIFT		16

#घोषणा PAACE_AF_AP			0x00000018
#घोषणा PAACE_AF_AP_SHIFT		3
#घोषणा PAACE_AF_DD			0x00000004
#घोषणा PAACE_AF_DD_SHIFT		2
#घोषणा PAACE_AF_PT			0x00000002
#घोषणा PAACE_AF_PT_SHIFT		1
#घोषणा PAACE_AF_V			0x00000001
#घोषणा PAACE_AF_V_SHIFT		0

#घोषणा PAACE_DA_HOST_CR		0x80
#घोषणा PAACE_DA_HOST_CR_SHIFT		7

#घोषणा PAACE_IA_CID			0x00FF0000
#घोषणा PAACE_IA_CID_SHIFT		16
#घोषणा PAACE_IA_WCE			0x000000F0
#घोषणा PAACE_IA_WCE_SHIFT		4
#घोषणा PAACE_IA_ATM			0x0000000C
#घोषणा PAACE_IA_ATM_SHIFT		2
#घोषणा PAACE_IA_OTM			0x00000003
#घोषणा PAACE_IA_OTM_SHIFT		0

#घोषणा PAACE_WIN_TWBAL			0xfffff000
#घोषणा PAACE_WIN_TWBAL_SHIFT		12
#घोषणा PAACE_WIN_SWSE			0x00000fc0
#घोषणा PAACE_WIN_SWSE_SHIFT		6

/* PAMU Data Structures */
/* primary / secondary paact काष्ठाure */
काष्ठा paace अणु
	/* PAACE Offset 0x00 */
	u32 wbah;				/* only valid क्रम Primary PAACE */
	u32 addr_bitfields;		/* See P/S PAACE_AF_* */

	/* PAACE Offset 0x08 */
	/* Interpretation of first 32 bits dependent on DD above */
	जोड़ अणु
		काष्ठा अणु
			/* Destination ID, see PAACE_DID_* defines */
			u8 did;
			/* Partition ID */
			u8 pid;
			/* Snoop ID */
			u8 snpid;
			/* coherency_required : 1 reserved : 7 */
			u8 coherency_required; /* See PAACE_DA_* */
		पूर्ण to_host;
		काष्ठा अणु
			/* Destination ID, see PAACE_DID_* defines */
			u8  did;
			u8  reserved1;
			u16 reserved2;
		पूर्ण to_io;
	पूर्ण करोमुख्य_attr;

	/* Implementation attributes + winकरोw count + address & operation translation modes */
	u32 impl_attr;			/* See PAACE_IA_* */

	/* PAACE Offset 0x10 */
	/* Translated winकरोw base address */
	u32 twbah;
	u32 win_bitfields;			/* See PAACE_WIN_* */

	/* PAACE Offset 0x18 */
	/* first secondary paace entry */
	u32 fspi;				/* only valid क्रम Primary PAACE */
	जोड़ अणु
		काष्ठा अणु
			u8 ioea;
			u8 moea;
			u8 ioeb;
			u8 moeb;
		पूर्ण immed_ot;
		काष्ठा अणु
			u16 reserved;
			u16 omi;
		पूर्ण index_ot;
	पूर्ण op_encode;

	/* PAACE Offsets 0x20-0x38 */
	u32 reserved[8];			/* not currently implemented */
पूर्ण;

/* OME : Operation mapping entry
 * MOE : Mapped Operation Encodings
 * The operation mapping table is table containing operation mapping entries (OME).
 * The index of a particular OME is programmed in the PAACE entry क्रम translation
 * in bound I/O operations corresponding to an LIODN. The OMT is used क्रम translation
 * specअगरically in हाल of the indexed translation mode. Each OME contains a 128
 * byte mapped operation encoding (MOE), where each byte represents an MOE.
 */
#घोषणा NUM_MOE 128
काष्ठा ome अणु
	u8 moe[NUM_MOE];
पूर्ण __packed;

#घोषणा PAACT_SIZE              (माप(काष्ठा paace) * PAACE_NUMBER_ENTRIES)
#घोषणा SPAACT_SIZE              (माप(काष्ठा paace) * SPAACE_NUMBER_ENTRIES)
#घोषणा OMT_SIZE                (माप(काष्ठा ome) * OME_NUMBER_ENTRIES)

#घोषणा PAMU_PAGE_SHIFT 12
#घोषणा PAMU_PAGE_SIZE  4096ULL

#घोषणा IOE_READ        0x00
#घोषणा IOE_READ_IDX    0x00
#घोषणा IOE_WRITE       0x81
#घोषणा IOE_WRITE_IDX   0x01
#घोषणा IOE_EREAD0      0x82    /* Enhanced पढ़ो type 0 */
#घोषणा IOE_EREAD0_IDX  0x02    /* Enhanced पढ़ो type 0 */
#घोषणा IOE_EWRITE0     0x83    /* Enhanced ग_लिखो type 0 */
#घोषणा IOE_EWRITE0_IDX 0x03    /* Enhanced ग_लिखो type 0 */
#घोषणा IOE_सूचीECT0     0x84    /* Directive type 0 */
#घोषणा IOE_सूचीECT0_IDX 0x04    /* Directive type 0 */
#घोषणा IOE_EREAD1      0x85    /* Enhanced पढ़ो type 1 */
#घोषणा IOE_EREAD1_IDX  0x05    /* Enhanced पढ़ो type 1 */
#घोषणा IOE_EWRITE1     0x86    /* Enhanced ग_लिखो type 1 */
#घोषणा IOE_EWRITE1_IDX 0x06    /* Enhanced ग_लिखो type 1 */
#घोषणा IOE_सूचीECT1     0x87    /* Directive type 1 */
#घोषणा IOE_सूचीECT1_IDX 0x07    /* Directive type 1 */
#घोषणा IOE_RAC         0x8c    /* Read with Atomic clear */
#घोषणा IOE_RAC_IDX     0x0c    /* Read with Atomic clear */
#घोषणा IOE_RAS         0x8d    /* Read with Atomic set */
#घोषणा IOE_RAS_IDX     0x0d    /* Read with Atomic set */
#घोषणा IOE_RAD         0x8e    /* Read with Atomic decrement */
#घोषणा IOE_RAD_IDX     0x0e    /* Read with Atomic decrement */
#घोषणा IOE_RAI         0x8f    /* Read with Atomic increment */
#घोषणा IOE_RAI_IDX     0x0f    /* Read with Atomic increment */

#घोषणा EOE_READ        0x00
#घोषणा EOE_WRITE       0x01
#घोषणा EOE_RAC         0x0c    /* Read with Atomic clear */
#घोषणा EOE_RAS         0x0d    /* Read with Atomic set */
#घोषणा EOE_RAD         0x0e    /* Read with Atomic decrement */
#घोषणा EOE_RAI         0x0f    /* Read with Atomic increment */
#घोषणा EOE_LDEC        0x10    /* Load बाह्यal cache */
#घोषणा EOE_LDECL       0x11    /* Load बाह्यal cache with stash lock */
#घोषणा EOE_LDECPE      0x12    /* Load बाह्यal cache with preferred exclusive */
#घोषणा EOE_LDECPEL     0x13    /* Load बाह्यal cache with preferred exclusive and lock */
#घोषणा EOE_LDECFE      0x14    /* Load बाह्यal cache with क्रमced exclusive */
#घोषणा EOE_LDECFEL     0x15    /* Load बाह्यal cache with क्रमced exclusive and lock */
#घोषणा EOE_RSA         0x16    /* Read with stash allocate */
#घोषणा EOE_RSAU        0x17    /* Read with stash allocate and unlock */
#घोषणा EOE_READI       0x18    /* Read with invalidate */
#घोषणा EOE_RWNITC      0x19    /* Read with no पूर्णांकention to cache */
#घोषणा EOE_WCI         0x1a    /* Write cache inhibited */
#घोषणा EOE_WWSA        0x1b    /* Write with stash allocate */
#घोषणा EOE_WWSAL       0x1c    /* Write with stash allocate and lock */
#घोषणा EOE_WWSAO       0x1d    /* Write with stash allocate only */
#घोषणा EOE_WWSAOL      0x1e    /* Write with stash allocate only and lock */
#घोषणा EOE_VALID       0x80

/* Function prototypes */
पूर्णांक pamu_करोमुख्य_init(व्योम);
पूर्णांक pamu_enable_liodn(पूर्णांक liodn);
पूर्णांक pamu_disable_liodn(पूर्णांक liodn);
पूर्णांक pamu_config_ppaace(पूर्णांक liodn, u32 omi, uपूर्णांक32_t stashid, पूर्णांक prot);

u32 get_stash_id(u32 stash_dest_hपूर्णांक, u32 vcpu);
व्योम get_ome_index(u32 *omi_index, काष्ठा device *dev);
पूर्णांक  pamu_update_paace_stash(पूर्णांक liodn, u32 value);

#पूर्ण_अगर  /* __FSL_PAMU_H */
