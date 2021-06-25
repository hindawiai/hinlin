<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * QLogic Fibre Channel HBA Driver
 * Copyright (c)  2003-2014 QLogic Corporation
 */

#अगर_अघोषित __QLA_NX2_H
#घोषणा __QLA_NX2_H

#घोषणा QSNT_ACK_TOV				30
#घोषणा INTENT_TO_RECOVER			0x01
#घोषणा PROCEED_TO_RECOVER			0x02
#घोषणा IDC_LOCK_RECOVERY_OWNER_MASK		0x3C
#घोषणा IDC_LOCK_RECOVERY_STATE_MASK		0x3
#घोषणा IDC_LOCK_RECOVERY_STATE_SHIFT_BITS	2

#घोषणा QLA8044_DRV_LOCK_MSLEEP		200
#घोषणा QLA8044_ADDR_DDR_NET		(0x0000000000000000ULL)
#घोषणा QLA8044_ADDR_DDR_NET_MAX	(0x000000000fffffffULL)

#घोषणा MD_MIU_TEST_AGT_WRDATA_LO		0x410000A0
#घोषणा MD_MIU_TEST_AGT_WRDATA_HI		0x410000A4
#घोषणा MD_MIU_TEST_AGT_WRDATA_ULO		0x410000B0
#घोषणा MD_MIU_TEST_AGT_WRDATA_UHI		0x410000B4

/* MIU_TEST_AGT_CTRL flags. work क्रम SIU as well */
#घोषणा MIU_TA_CTL_WRITE_ENABLE	(MIU_TA_CTL_WRITE | MIU_TA_CTL_ENABLE)
#घोषणा MIU_TA_CTL_WRITE_START	(MIU_TA_CTL_WRITE | MIU_TA_CTL_ENABLE |	\
				 MIU_TA_CTL_START)
#घोषणा MIU_TA_CTL_START_ENABLE	(MIU_TA_CTL_START | MIU_TA_CTL_ENABLE)

/* Imbus address bit used to indicate a host address. This bit is
 * eliminated by the pcie bar and bar select beक्रमe presentation
 * over pcie. */
/* host memory via IMBUS */
#घोषणा QLA8044_P2_ADDR_PCIE	(0x0000000800000000ULL)
#घोषणा QLA8044_P3_ADDR_PCIE	(0x0000008000000000ULL)
#घोषणा QLA8044_ADDR_PCIE_MAX	(0x0000000FFFFFFFFFULL)
#घोषणा QLA8044_ADDR_OCM0	(0x0000000200000000ULL)
#घोषणा QLA8044_ADDR_OCM0_MAX	(0x00000002000fffffULL)
#घोषणा QLA8044_ADDR_OCM1	(0x0000000200400000ULL)
#घोषणा QLA8044_ADDR_OCM1_MAX	(0x00000002004fffffULL)
#घोषणा QLA8044_ADDR_QDR_NET	(0x0000000300000000ULL)
#घोषणा QLA8044_P2_ADDR_QDR_NET_MAX	(0x00000003001fffffULL)
#घोषणा QLA8044_P3_ADDR_QDR_NET_MAX	(0x0000000303ffffffULL)
#घोषणा QLA8044_ADDR_QDR_NET_MAX	(0x0000000307ffffffULL)
#घोषणा QLA8044_PCI_CRBSPACE		((अचिन्हित दीर्घ)0x06000000)
#घोषणा QLA8044_PCI_सूचीECT_CRB		((अचिन्हित दीर्घ)0x04400000)
#घोषणा QLA8044_PCI_CAMQM		((अचिन्हित दीर्घ)0x04800000)
#घोषणा QLA8044_PCI_CAMQM_MAX		((अचिन्हित दीर्घ)0x04ffffff)
#घोषणा QLA8044_PCI_DDR_NET		((अचिन्हित दीर्घ)0x00000000)
#घोषणा QLA8044_PCI_QDR_NET		((अचिन्हित दीर्घ)0x04000000)
#घोषणा QLA8044_PCI_QDR_NET_MAX		((अचिन्हित दीर्घ)0x043fffff)

/*  PCI Winकरोwing क्रम DDR regions.  */
अटल अंतरभूत bool addr_in_range(u64 addr, u64 low, u64 high)
अणु
	वापस addr <= high && addr >= low;
पूर्ण

/* Indirectly Mapped Registers */
#घोषणा QLA8044_FLASH_SPI_STATUS	0x2808E010
#घोषणा QLA8044_FLASH_SPI_CONTROL	0x2808E014
#घोषणा QLA8044_FLASH_STATUS		0x42100004
#घोषणा QLA8044_FLASH_CONTROL		0x42110004
#घोषणा QLA8044_FLASH_ADDR		0x42110008
#घोषणा QLA8044_FLASH_WRDATA		0x4211000C
#घोषणा QLA8044_FLASH_RDDATA		0x42110018
#घोषणा QLA8044_FLASH_सूचीECT_WINDOW	0x42110030
#घोषणा QLA8044_FLASH_सूचीECT_DATA(DATA) (0x42150000 | (0x0000FFFF&DATA))

/* Flash access regs */
#घोषणा QLA8044_FLASH_LOCK		0x3850
#घोषणा QLA8044_FLASH_UNLOCK		0x3854
#घोषणा QLA8044_FLASH_LOCK_ID		0x3500

/* Driver Lock regs */
#घोषणा QLA8044_DRV_LOCK		0x3868
#घोषणा QLA8044_DRV_UNLOCK		0x386C
#घोषणा QLA8044_DRV_LOCK_ID		0x3504
#घोषणा QLA8044_DRV_LOCKRECOVERY	0x379C

/* IDC version */
#घोषणा QLA8044_IDC_VER_MAJ_VALUE       0x1
#घोषणा QLA8044_IDC_VER_MIN_VALUE       0x0

/* IDC Registers : Driver Coexistence Defines */
#घोषणा QLA8044_CRB_IDC_VER_MAJOR	0x3780
#घोषणा QLA8044_CRB_IDC_VER_MINOR	0x3798
#घोषणा QLA8044_IDC_DRV_AUDIT		0x3794
#घोषणा QLA8044_SRE_SHIM_CONTROL	0x0D200284
#घोषणा QLA8044_PORT0_RXB_PAUSE_THRS	0x0B2003A4
#घोषणा QLA8044_PORT1_RXB_PAUSE_THRS	0x0B2013A4
#घोषणा QLA8044_PORT0_RXB_TC_MAX_CELL	0x0B200388
#घोषणा QLA8044_PORT1_RXB_TC_MAX_CELL	0x0B201388
#घोषणा QLA8044_PORT0_RXB_TC_STATS	0x0B20039C
#घोषणा QLA8044_PORT1_RXB_TC_STATS	0x0B20139C
#घोषणा QLA8044_PORT2_IFB_PAUSE_THRS	0x0B200704
#घोषणा QLA8044_PORT3_IFB_PAUSE_THRS	0x0B201704

/* set value to छोड़ो threshold value */
#घोषणा QLA8044_SET_PAUSE_VAL		0x0
#घोषणा QLA8044_SET_TC_MAX_CELL_VAL	0x03FF03FF
#घोषणा QLA8044_PEG_HALT_STATUS1	0x34A8
#घोषणा QLA8044_PEG_HALT_STATUS2	0x34AC
#घोषणा QLA8044_PEG_ALIVE_COUNTER	0x34B0 /* FW_HEARTBEAT */
#घोषणा QLA8044_FW_CAPABILITIES		0x3528
#घोषणा QLA8044_CRB_DRV_ACTIVE		0x3788 /* IDC_DRV_PRESENCE */
#घोषणा QLA8044_CRB_DEV_STATE		0x3784 /* IDC_DEV_STATE */
#घोषणा QLA8044_CRB_DRV_STATE		0x378C /* IDC_DRV_ACK */
#घोषणा QLA8044_CRB_DRV_SCRATCH		0x3548
#घोषणा QLA8044_CRB_DEV_PART_INFO1	0x37E0
#घोषणा QLA8044_CRB_DEV_PART_INFO2	0x37E4
#घोषणा QLA8044_FW_VER_MAJOR		0x3550
#घोषणा QLA8044_FW_VER_MINOR		0x3554
#घोषणा QLA8044_FW_VER_SUB		0x3558
#घोषणा QLA8044_NPAR_STATE		0x359C
#घोषणा QLA8044_FW_IMAGE_VALID		0x35FC
#घोषणा QLA8044_CMDPEG_STATE		0x3650
#घोषणा QLA8044_ASIC_TEMP		0x37B4
#घोषणा QLA8044_FW_API			0x356C
#घोषणा QLA8044_DRV_OP_MODE		0x3570
#घोषणा QLA8044_CRB_WIN_BASE		0x3800
#घोषणा QLA8044_CRB_WIN_FUNC(f)		(QLA8044_CRB_WIN_BASE+((f)*4))
#घोषणा QLA8044_SEM_LOCK_BASE		0x3840
#घोषणा QLA8044_SEM_UNLOCK_BASE		0x3844
#घोषणा QLA8044_SEM_LOCK_FUNC(f)	(QLA8044_SEM_LOCK_BASE+((f)*8))
#घोषणा QLA8044_SEM_UNLOCK_FUNC(f)	(QLA8044_SEM_UNLOCK_BASE+((f)*8))
#घोषणा QLA8044_LINK_STATE(f)		(0x3698+((f) > 7 ? 4 : 0))
#घोषणा QLA8044_LINK_SPEED(f)		(0x36E0+(((f) >> 2) * 4))
#घोषणा QLA8044_MAX_LINK_SPEED(f)       (0x36F0+(((f) / 4) * 4))
#घोषणा QLA8044_LINK_SPEED_FACTOR	10
#घोषणा QLA8044_FUN7_ACTIVE_INDEX	0x80

/* FLASH API Defines */
#घोषणा QLA8044_FLASH_MAX_WAIT_USEC	100
#घोषणा QLA8044_FLASH_LOCK_TIMEOUT	10000
#घोषणा QLA8044_FLASH_SECTOR_SIZE	65536
#घोषणा QLA8044_DRV_LOCK_TIMEOUT	2000
#घोषणा QLA8044_FLASH_SECTOR_ERASE_CMD	0xdeadbeef
#घोषणा QLA8044_FLASH_WRITE_CMD		0xdacdacda
#घोषणा QLA8044_FLASH_BUFFER_WRITE_CMD	0xcadcadca
#घोषणा QLA8044_FLASH_READ_RETRY_COUNT	2000
#घोषणा QLA8044_FLASH_STATUS_READY	0x6
#घोषणा QLA8044_FLASH_BUFFER_WRITE_MIN	2
#घोषणा QLA8044_FLASH_BUFFER_WRITE_MAX	64
#घोषणा QLA8044_FLASH_STATUS_REG_POLL_DELAY 1
#घोषणा QLA8044_ERASE_MODE		1
#घोषणा QLA8044_WRITE_MODE		2
#घोषणा QLA8044_DWORD_WRITE_MODE	3
#घोषणा QLA8044_GLOBAL_RESET		0x38CC
#घोषणा QLA8044_WILDCARD		0x38F0
#घोषणा QLA8044_INFORMANT		0x38FC
#घोषणा QLA8044_HOST_MBX_CTRL		0x3038
#घोषणा QLA8044_FW_MBX_CTRL		0x303C
#घोषणा QLA8044_BOOTLOADER_ADDR		0x355C
#घोषणा QLA8044_BOOTLOADER_SIZE		0x3560
#घोषणा QLA8044_FW_IMAGE_ADDR		0x3564
#घोषणा QLA8044_MBX_INTR_ENABLE		0x1000
#घोषणा QLA8044_MBX_INTR_MASK		0x1200

/* IDC Control Register bit defines */
#घोषणा DONTRESET_BIT0		0x1
#घोषणा GRACEFUL_RESET_BIT1	0x2

/* ISP8044 PEG_HALT_STATUS1 bits */
#घोषणा QLA8044_HALT_STATUS_INFORMATIONAL (0x1 << 29)
#घोषणा QLA8044_HALT_STATUS_FW_RESET	  (0x2 << 29)
#घोषणा QLA8044_HALT_STATUS_UNRECOVERABLE (0x4 << 29)

/* Firmware image definitions */
#घोषणा QLA8044_BOOTLOADER_FLASH_ADDR	0x10000
#घोषणा QLA8044_BOOT_FROM_FLASH		0
#घोषणा QLA8044_IDC_PARAM_ADDR		0x3e8020

/* FLASH related definitions */
#घोषणा QLA8044_OPTROM_BURST_SIZE		0x100
#घोषणा QLA8044_MAX_OPTROM_BURST_DWORDS		(QLA8044_OPTROM_BURST_SIZE / 4)
#घोषणा QLA8044_MIN_OPTROM_BURST_DWORDS		2
#घोषणा QLA8044_SECTOR_SIZE			(64 * 1024)

#घोषणा QLA8044_FLASH_SPI_CTL			0x4
#घोषणा QLA8044_FLASH_FIRST_TEMP_VAL		0x00800000
#घोषणा QLA8044_FLASH_SECOND_TEMP_VAL		0x00800001
#घोषणा QLA8044_FLASH_FIRST_MS_PATTERN		0x43
#घोषणा QLA8044_FLASH_SECOND_MS_PATTERN		0x7F
#घोषणा QLA8044_FLASH_LAST_MS_PATTERN		0x7D
#घोषणा QLA8044_FLASH_STATUS_WRITE_DEF_SIG	0xFD0100
#घोषणा QLA8044_FLASH_SECOND_ERASE_MS_VAL	0x5
#घोषणा QLA8044_FLASH_ERASE_SIG			0xFD0300
#घोषणा QLA8044_FLASH_LAST_ERASE_MS_VAL		0x3D

/* Reset ढाँचा definitions */
#घोषणा QLA8044_MAX_RESET_SEQ_ENTRIES	16
#घोषणा QLA8044_RESTART_TEMPLATE_SIZE	0x2000
#घोषणा QLA8044_RESET_TEMPLATE_ADDR	0x4F0000
#घोषणा QLA8044_RESET_SEQ_VERSION	0x0101

/* Reset ढाँचा entry opcodes */
#घोषणा OPCODE_NOP			0x0000
#घोषणा OPCODE_WRITE_LIST		0x0001
#घोषणा OPCODE_READ_WRITE_LIST		0x0002
#घोषणा OPCODE_POLL_LIST		0x0004
#घोषणा OPCODE_POLL_WRITE_LIST		0x0008
#घोषणा OPCODE_READ_MODIFY_WRITE	0x0010
#घोषणा OPCODE_SEQ_PAUSE		0x0020
#घोषणा OPCODE_SEQ_END			0x0040
#घोषणा OPCODE_TMPL_END			0x0080
#घोषणा OPCODE_POLL_READ_LIST		0x0100

/* Template Header */
#घोषणा RESET_TMPLT_HDR_SIGNATURE	0xCAFE
#घोषणा QLA8044_IDC_DRV_CTRL            0x3790
#घोषणा AF_8044_NO_FW_DUMP              27 /* 0x08000000 */

#घोषणा MINIDUMP_SIZE_36K		36864

काष्ठा qla8044_reset_ढाँचा_hdr अणु
	uपूर्णांक16_t	version;
	uपूर्णांक16_t	signature;
	uपूर्णांक16_t	size;
	uपूर्णांक16_t	entries;
	uपूर्णांक16_t	hdr_size;
	uपूर्णांक16_t	checksum;
	uपूर्णांक16_t	init_seq_offset;
	uपूर्णांक16_t	start_seq_offset;
पूर्ण __packed;

/* Common Entry Header. */
काष्ठा qla8044_reset_entry_hdr अणु
	uपूर्णांक16_t cmd;
	uपूर्णांक16_t size;
	uपूर्णांक16_t count;
	uपूर्णांक16_t delay;
पूर्ण __packed;

/* Generic poll entry type. */
काष्ठा qla8044_poll अणु
	uपूर्णांक32_t  test_mask;
	uपूर्णांक32_t  test_value;
पूर्ण __packed;

/* Read modअगरy ग_लिखो entry type. */
काष्ठा qla8044_rmw अणु
	uपूर्णांक32_t test_mask;
	uपूर्णांक32_t xor_value;
	uपूर्णांक32_t  or_value;
	uपूर्णांक8_t shl;
	uपूर्णांक8_t shr;
	uपूर्णांक8_t index_a;
	uपूर्णांक8_t rsvd;
पूर्ण __packed;

/* Generic Entry Item with 2 DWords. */
काष्ठा qla8044_entry अणु
	uपूर्णांक32_t arg1;
	uपूर्णांक32_t arg2;
पूर्ण __packed;

/* Generic Entry Item with 4 DWords.*/
काष्ठा qla8044_quad_entry अणु
	uपूर्णांक32_t dr_addr;
	uपूर्णांक32_t dr_value;
	uपूर्णांक32_t ar_addr;
	uपूर्णांक32_t ar_value;
पूर्ण __packed;

काष्ठा qla8044_reset_ढाँचा अणु
	पूर्णांक seq_index;
	पूर्णांक seq_error;
	पूर्णांक array_index;
	uपूर्णांक32_t array[QLA8044_MAX_RESET_SEQ_ENTRIES];
	uपूर्णांक8_t *buff;
	uपूर्णांक8_t *stop_offset;
	uपूर्णांक8_t *start_offset;
	uपूर्णांक8_t *init_offset;
	काष्ठा qla8044_reset_ढाँचा_hdr *hdr;
	uपूर्णांक8_t seq_end;
	uपूर्णांक8_t ढाँचा_end;
पूर्ण;

/* Driver_code is क्रम driver to ग_लिखो some info about the entry
 * currently not used.
 */
काष्ठा qla8044_minidump_entry_hdr अणु
	uपूर्णांक32_t entry_type;
	uपूर्णांक32_t entry_size;
	uपूर्णांक32_t entry_capture_size;
	काष्ठा अणु
		uपूर्णांक8_t entry_capture_mask;
		uपूर्णांक8_t entry_code;
		uपूर्णांक8_t driver_code;
		uपूर्णांक8_t driver_flags;
	पूर्ण d_ctrl;
पूर्ण __packed;

/*  Read CRB entry header */
काष्ठा qla8044_minidump_entry_crb अणु
	काष्ठा qla8044_minidump_entry_hdr h;
	uपूर्णांक32_t addr;
	काष्ठा अणु
		uपूर्णांक8_t addr_stride;
		uपूर्णांक8_t state_index_a;
		uपूर्णांक16_t poll_समयout;
	पूर्ण crb_strd;
	uपूर्णांक32_t data_size;
	uपूर्णांक32_t op_count;

	काष्ठा अणु
		uपूर्णांक8_t opcode;
		uपूर्णांक8_t state_index_v;
		uपूर्णांक8_t shl;
		uपूर्णांक8_t shr;
	पूर्ण crb_ctrl;

	uपूर्णांक32_t value_1;
	uपूर्णांक32_t value_2;
	uपूर्णांक32_t value_3;
पूर्ण __packed;

काष्ठा qla8044_minidump_entry_cache अणु
	काष्ठा qla8044_minidump_entry_hdr h;
	uपूर्णांक32_t tag_reg_addr;
	काष्ठा अणु
		uपूर्णांक16_t tag_value_stride;
		uपूर्णांक16_t init_tag_value;
	पूर्ण addr_ctrl;
	uपूर्णांक32_t data_size;
	uपूर्णांक32_t op_count;
	uपूर्णांक32_t control_addr;
	काष्ठा अणु
		uपूर्णांक16_t ग_लिखो_value;
		uपूर्णांक8_t poll_mask;
		uपूर्णांक8_t poll_रुको;
	पूर्ण cache_ctrl;
	uपूर्णांक32_t पढ़ो_addr;
	काष्ठा अणु
		uपूर्णांक8_t पढ़ो_addr_stride;
		uपूर्णांक8_t पढ़ो_addr_cnt;
		uपूर्णांक16_t rsvd_1;
	पूर्ण पढ़ो_ctrl;
पूर्ण __packed;

/* Read OCM */
काष्ठा qla8044_minidump_entry_rकरोcm अणु
	काष्ठा qla8044_minidump_entry_hdr h;
	uपूर्णांक32_t rsvd_0;
	uपूर्णांक32_t rsvd_1;
	uपूर्णांक32_t data_size;
	uपूर्णांक32_t op_count;
	uपूर्णांक32_t rsvd_2;
	uपूर्णांक32_t rsvd_3;
	uपूर्णांक32_t पढ़ो_addr;
	uपूर्णांक32_t पढ़ो_addr_stride;
पूर्ण __packed;

/* Read Memory */
काष्ठा qla8044_minidump_entry_rdmem अणु
	काष्ठा qla8044_minidump_entry_hdr h;
	uपूर्णांक32_t rsvd[6];
	uपूर्णांक32_t पढ़ो_addr;
	uपूर्णांक32_t पढ़ो_data_size;
पूर्ण;

/* Read Memory: For Pex-DMA */
काष्ठा qla8044_minidump_entry_rdmem_pex_dma अणु
	काष्ठा qla8044_minidump_entry_hdr h;
	uपूर्णांक32_t desc_card_addr;
	uपूर्णांक16_t dma_desc_cmd;
	uपूर्णांक8_t rsvd[2];
	uपूर्णांक32_t start_dma_cmd;
	uपूर्णांक8_t rsvd2[12];
	uपूर्णांक32_t पढ़ो_addr;
	uपूर्णांक32_t पढ़ो_data_size;
पूर्ण __packed;

/* Read ROM */
काष्ठा qla8044_minidump_entry_rdrom अणु
	काष्ठा qla8044_minidump_entry_hdr h;
	uपूर्णांक32_t rsvd[6];
	uपूर्णांक32_t पढ़ो_addr;
	uपूर्णांक32_t पढ़ो_data_size;
पूर्ण __packed;

/* Mux entry */
काष्ठा qla8044_minidump_entry_mux अणु
	काष्ठा qla8044_minidump_entry_hdr h;
	uपूर्णांक32_t select_addr;
	uपूर्णांक32_t rsvd_0;
	uपूर्णांक32_t data_size;
	uपूर्णांक32_t op_count;
	uपूर्णांक32_t select_value;
	uपूर्णांक32_t select_value_stride;
	uपूर्णांक32_t पढ़ो_addr;
	uपूर्णांक32_t rsvd_1;
पूर्ण __packed;

/* Queue entry */
काष्ठा qla8044_minidump_entry_queue अणु
	काष्ठा qla8044_minidump_entry_hdr h;
	uपूर्णांक32_t select_addr;
	काष्ठा अणु
		uपूर्णांक16_t queue_id_stride;
		uपूर्णांक16_t rsvd_0;
	पूर्ण q_strd;
	uपूर्णांक32_t data_size;
	uपूर्णांक32_t op_count;
	uपूर्णांक32_t rsvd_1;
	uपूर्णांक32_t rsvd_2;
	uपूर्णांक32_t पढ़ो_addr;
	काष्ठा अणु
		uपूर्णांक8_t पढ़ो_addr_stride;
		uपूर्णांक8_t पढ़ो_addr_cnt;
		uपूर्णांक16_t rsvd_3;
	पूर्ण rd_strd;
पूर्ण __packed;

/* POLLRD Entry */
काष्ठा qla8044_minidump_entry_pollrd अणु
	काष्ठा qla8044_minidump_entry_hdr h;
	uपूर्णांक32_t select_addr;
	uपूर्णांक32_t पढ़ो_addr;
	uपूर्णांक32_t select_value;
	uपूर्णांक16_t select_value_stride;
	uपूर्णांक16_t op_count;
	uपूर्णांक32_t poll_रुको;
	uपूर्णांक32_t poll_mask;
	uपूर्णांक32_t data_size;
	uपूर्णांक32_t rsvd_1;
पूर्ण __packed;

काष्ठा qla8044_minidump_entry_rddfe अणु
	काष्ठा qla8044_minidump_entry_hdr h;
	uपूर्णांक32_t addr_1;
	uपूर्णांक32_t value;
	uपूर्णांक8_t stride;
	uपूर्णांक8_t stride2;
	uपूर्णांक16_t count;
	uपूर्णांक32_t poll;
	uपूर्णांक32_t mask;
	uपूर्णांक32_t modअगरy_mask;
	uपूर्णांक32_t data_size;
	uपूर्णांक32_t rsvd;

पूर्ण __packed;

काष्ठा qla8044_minidump_entry_rdmdio अणु
	काष्ठा qla8044_minidump_entry_hdr h;

	uपूर्णांक32_t addr_1;
	uपूर्णांक32_t addr_2;
	uपूर्णांक32_t value_1;
	uपूर्णांक8_t stride_1;
	uपूर्णांक8_t stride_2;
	uपूर्णांक16_t count;
	uपूर्णांक32_t poll;
	uपूर्णांक32_t mask;
	uपूर्णांक32_t value_2;
	uपूर्णांक32_t data_size;

पूर्ण __packed;

काष्ठा qla8044_minidump_entry_pollwr अणु
	काष्ठा qla8044_minidump_entry_hdr h;
	uपूर्णांक32_t addr_1;
	uपूर्णांक32_t addr_2;
	uपूर्णांक32_t value_1;
	uपूर्णांक32_t value_2;
	uपूर्णांक32_t poll;
	uपूर्णांक32_t mask;
	uपूर्णांक32_t data_size;
	uपूर्णांक32_t rsvd;

पूर्ण  __packed;

/* RDMUX2 Entry */
काष्ठा qla8044_minidump_entry_rdmux2 अणु
	काष्ठा qla8044_minidump_entry_hdr h;
	uपूर्णांक32_t select_addr_1;
	uपूर्णांक32_t select_addr_2;
	uपूर्णांक32_t select_value_1;
	uपूर्णांक32_t select_value_2;
	uपूर्णांक32_t op_count;
	uपूर्णांक32_t select_value_mask;
	uपूर्णांक32_t पढ़ो_addr;
	uपूर्णांक8_t select_value_stride;
	uपूर्णांक8_t data_size;
	uपूर्णांक8_t rsvd[2];
पूर्ण __packed;

/* POLLRDMWR Entry */
काष्ठा qla8044_minidump_entry_pollrdmwr अणु
	काष्ठा qla8044_minidump_entry_hdr h;
	uपूर्णांक32_t addr_1;
	uपूर्णांक32_t addr_2;
	uपूर्णांक32_t value_1;
	uपूर्णांक32_t value_2;
	uपूर्णांक32_t poll_रुको;
	uपूर्णांक32_t poll_mask;
	uपूर्णांक32_t modअगरy_mask;
	uपूर्णांक32_t data_size;
पूर्ण __packed;

/* IDC additional inक्रमmation */
काष्ठा qla8044_idc_inक्रमmation अणु
	uपूर्णांक32_t request_desc;  /* IDC request descriptor */
	uपूर्णांक32_t info1; /* IDC additional info */
	uपूर्णांक32_t info2; /* IDC additional info */
	uपूर्णांक32_t info3; /* IDC additional info */
पूर्ण __packed;

क्रमागत qla_regs अणु
	QLA8044_PEG_HALT_STATUS1_INDEX = 0,
	QLA8044_PEG_HALT_STATUS2_INDEX,
	QLA8044_PEG_ALIVE_COUNTER_INDEX,
	QLA8044_CRB_DRV_ACTIVE_INDEX,
	QLA8044_CRB_DEV_STATE_INDEX,
	QLA8044_CRB_DRV_STATE_INDEX,
	QLA8044_CRB_DRV_SCRATCH_INDEX,
	QLA8044_CRB_DEV_PART_INFO_INDEX,
	QLA8044_CRB_DRV_IDC_VERSION_INDEX,
	QLA8044_FW_VERSION_MAJOR_INDEX,
	QLA8044_FW_VERSION_MINOR_INDEX,
	QLA8044_FW_VERSION_SUB_INDEX,
	QLA8044_CRB_CMDPEG_STATE_INDEX,
	QLA8044_CRB_TEMP_STATE_INDEX,
पूर्ण __packed;

#घोषणा CRB_REG_INDEX_MAX	14
#घोषणा CRB_CMDPEG_CHECK_RETRY_COUNT    60
#घोषणा CRB_CMDPEG_CHECK_DELAY          500

/* MiniDump Structures */

/* Driver_code is क्रम driver to ग_लिखो some info about the entry
 * currently not used.
 */
#घोषणा QLA8044_SS_OCM_WNDREG_INDEX             3
#घोषणा QLA8044_DBG_STATE_ARRAY_LEN             16
#घोषणा QLA8044_DBG_CAP_SIZE_ARRAY_LEN          8
#घोषणा QLA8044_DBG_RSVD_ARRAY_LEN              8
#घोषणा QLA8044_DBG_OCM_WNDREG_ARRAY_LEN        16
#घोषणा QLA8044_SS_PCI_INDEX                    0
#घोषणा QLA8044_RDDFE          38
#घोषणा QLA8044_RDMDIO         39
#घोषणा QLA8044_POLLWR         40

काष्ठा qla8044_minidump_ढाँचा_hdr अणु
	uपूर्णांक32_t entry_type;
	uपूर्णांक32_t first_entry_offset;
	uपूर्णांक32_t size_of_ढाँचा;
	uपूर्णांक32_t capture_debug_level;
	uपूर्णांक32_t num_of_entries;
	uपूर्णांक32_t version;
	uपूर्णांक32_t driver_बारtamp;
	uपूर्णांक32_t checksum;

	uपूर्णांक32_t driver_capture_mask;
	uपूर्णांक32_t driver_info_word2;
	uपूर्णांक32_t driver_info_word3;
	uपूर्णांक32_t driver_info_word4;

	uपूर्णांक32_t saved_state_array[QLA8044_DBG_STATE_ARRAY_LEN];
	uपूर्णांक32_t capture_size_array[QLA8044_DBG_CAP_SIZE_ARRAY_LEN];
	uपूर्णांक32_t ocm_winकरोw_reg[QLA8044_DBG_OCM_WNDREG_ARRAY_LEN];
पूर्ण;

काष्ठा qla8044_pex_dma_descriptor अणु
	काष्ठा अणु
		uपूर्णांक32_t पढ़ो_data_size; /* 0-23: size, 24-31: rsvd */
		uपूर्णांक8_t rsvd[2];
		uपूर्णांक16_t dma_desc_cmd;
	पूर्ण cmd;
	uपूर्णांक64_t src_addr;
	uपूर्णांक64_t dma_bus_addr; /*0-3: desc-cmd, 4-7: pci-func, 8-15: desc-cmd*/
	uपूर्णांक8_t rsvd[24];
पूर्ण __packed;

#पूर्ण_अगर
