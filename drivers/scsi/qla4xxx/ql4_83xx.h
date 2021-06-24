<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * QLogic iSCSI HBA Driver
 * Copyright (c)  2003-2013 QLogic Corporation
 */

#अगर_अघोषित __QL483XX_H
#घोषणा __QL483XX_H

/* Indirectly Mapped Registers */
#घोषणा QLA83XX_FLASH_SPI_STATUS	0x2808E010
#घोषणा QLA83XX_FLASH_SPI_CONTROL	0x2808E014
#घोषणा QLA83XX_FLASH_STATUS		0x42100004
#घोषणा QLA83XX_FLASH_CONTROL		0x42110004
#घोषणा QLA83XX_FLASH_ADDR		0x42110008
#घोषणा QLA83XX_FLASH_WRDATA		0x4211000C
#घोषणा QLA83XX_FLASH_RDDATA		0x42110018
#घोषणा QLA83XX_FLASH_सूचीECT_WINDOW	0x42110030
#घोषणा QLA83XX_FLASH_सूचीECT_DATA(DATA) (0x42150000 | (0x0000FFFF&DATA))

/* Directly Mapped Registers in 83xx रेजिस्टर table */

/* Flash access regs */
#घोषणा QLA83XX_FLASH_LOCK		0x3850
#घोषणा QLA83XX_FLASH_UNLOCK		0x3854
#घोषणा QLA83XX_FLASH_LOCK_ID		0x3500

/* Driver Lock regs */
#घोषणा QLA83XX_DRV_LOCK		0x3868
#घोषणा QLA83XX_DRV_UNLOCK		0x386C
#घोषणा QLA83XX_DRV_LOCK_ID		0x3504
#घोषणा QLA83XX_DRV_LOCKRECOVERY	0x379C

/* IDC version */
#घोषणा QLA83XX_IDC_VER_MAJ_VALUE       0x1
#घोषणा QLA83XX_IDC_VER_MIN_VALUE       0x0

/* IDC Registers : Driver Coexistence Defines */
#घोषणा QLA83XX_CRB_IDC_VER_MAJOR	0x3780
#घोषणा QLA83XX_CRB_IDC_VER_MINOR	0x3798
#घोषणा QLA83XX_IDC_DRV_CTRL		0x3790
#घोषणा QLA83XX_IDC_DRV_AUDIT		0x3794
#घोषणा QLA83XX_SRE_SHIM_CONTROL	0x0D200284
#घोषणा QLA83XX_PORT0_RXB_PAUSE_THRS	0x0B2003A4
#घोषणा QLA83XX_PORT1_RXB_PAUSE_THRS	0x0B2013A4
#घोषणा QLA83XX_PORT0_RXB_TC_MAX_CELL	0x0B200388
#घोषणा QLA83XX_PORT1_RXB_TC_MAX_CELL	0x0B201388
#घोषणा QLA83XX_PORT0_RXB_TC_STATS	0x0B20039C
#घोषणा QLA83XX_PORT1_RXB_TC_STATS	0x0B20139C
#घोषणा QLA83XX_PORT2_IFB_PAUSE_THRS	0x0B200704
#घोषणा QLA83XX_PORT3_IFB_PAUSE_THRS	0x0B201704

/* set value to छोड़ो threshold value */
#घोषणा QLA83XX_SET_PAUSE_VAL		0x0
#घोषणा QLA83XX_SET_TC_MAX_CELL_VAL	0x03FF03FF

#घोषणा QLA83XX_RESET_CONTROL		0x28084E50
#घोषणा QLA83XX_RESET_REG		0x28084E60
#घोषणा QLA83XX_RESET_PORT0		0x28084E70
#घोषणा QLA83XX_RESET_PORT1		0x28084E80
#घोषणा QLA83XX_RESET_PORT2		0x28084E90
#घोषणा QLA83XX_RESET_PORT3		0x28084EA0
#घोषणा QLA83XX_RESET_SRE_SHIM		0x28084EB0
#घोषणा QLA83XX_RESET_EPG_SHIM		0x28084EC0
#घोषणा QLA83XX_RESET_ETHER_PCS		0x28084ED0

/* qla_83xx_reg_tbl रेजिस्टरs */
#घोषणा QLA83XX_PEG_HALT_STATUS1	0x34A8
#घोषणा QLA83XX_PEG_HALT_STATUS2	0x34AC
#घोषणा QLA83XX_PEG_ALIVE_COUNTER	0x34B0 /* FW_HEARTBEAT */
#घोषणा QLA83XX_FW_CAPABILITIES		0x3528
#घोषणा QLA83XX_CRB_DRV_ACTIVE		0x3788 /* IDC_DRV_PRESENCE */
#घोषणा QLA83XX_CRB_DEV_STATE		0x3784 /* IDC_DEV_STATE */
#घोषणा QLA83XX_CRB_DRV_STATE		0x378C /* IDC_DRV_ACK */
#घोषणा QLA83XX_CRB_DRV_SCRATCH		0x3548
#घोषणा QLA83XX_CRB_DEV_PART_INFO1	0x37E0
#घोषणा QLA83XX_CRB_DEV_PART_INFO2	0x37E4

#घोषणा QLA83XX_FW_VER_MAJOR		0x3550
#घोषणा QLA83XX_FW_VER_MINOR		0x3554
#घोषणा QLA83XX_FW_VER_SUB		0x3558
#घोषणा QLA83XX_NPAR_STATE		0x359C
#घोषणा QLA83XX_FW_IMAGE_VALID		0x35FC
#घोषणा QLA83XX_CMDPEG_STATE		0x3650
#घोषणा QLA83XX_ASIC_TEMP		0x37B4
#घोषणा QLA83XX_FW_API			0x356C
#घोषणा QLA83XX_DRV_OP_MODE		0x3570

#घोषणा QLA83XX_CRB_WIN_BASE		0x3800
#घोषणा QLA83XX_CRB_WIN_FUNC(f)		(QLA83XX_CRB_WIN_BASE+((f)*4))
#घोषणा QLA83XX_SEM_LOCK_BASE		0x3840
#घोषणा QLA83XX_SEM_UNLOCK_BASE		0x3844
#घोषणा QLA83XX_SEM_LOCK_FUNC(f)	(QLA83XX_SEM_LOCK_BASE+((f)*8))
#घोषणा QLA83XX_SEM_UNLOCK_FUNC(f)	(QLA83XX_SEM_UNLOCK_BASE+((f)*8))
#घोषणा QLA83XX_LINK_STATE(f)		(0x3698+((f) > 7 ? 4 : 0))
#घोषणा QLA83XX_LINK_SPEED(f)		(0x36E0+(((f) >> 2) * 4))
#घोषणा QLA83XX_MAX_LINK_SPEED(f)       (0x36F0+(((f) / 4) * 4))
#घोषणा QLA83XX_LINK_SPEED_FACTOR	10

/* FLASH API Defines */
#घोषणा QLA83xx_FLASH_MAX_WAIT_USEC	100
#घोषणा QLA83XX_FLASH_LOCK_TIMEOUT	10000
#घोषणा QLA83XX_FLASH_SECTOR_SIZE	65536
#घोषणा QLA83XX_DRV_LOCK_TIMEOUT	2000
#घोषणा QLA83XX_FLASH_SECTOR_ERASE_CMD	0xdeadbeef
#घोषणा QLA83XX_FLASH_WRITE_CMD		0xdacdacda
#घोषणा QLA83XX_FLASH_BUFFER_WRITE_CMD	0xcadcadca
#घोषणा QLA83XX_FLASH_READ_RETRY_COUNT	2000
#घोषणा QLA83XX_FLASH_STATUS_READY	0x6
#घोषणा QLA83XX_FLASH_BUFFER_WRITE_MIN	2
#घोषणा QLA83XX_FLASH_BUFFER_WRITE_MAX	64
#घोषणा QLA83XX_FLASH_STATUS_REG_POLL_DELAY 1
#घोषणा QLA83XX_ERASE_MODE		1
#घोषणा QLA83XX_WRITE_MODE		2
#घोषणा QLA83XX_DWORD_WRITE_MODE	3

#घोषणा QLA83XX_GLOBAL_RESET		0x38CC
#घोषणा QLA83XX_WILDCARD		0x38F0
#घोषणा QLA83XX_INFORMANT		0x38FC
#घोषणा QLA83XX_HOST_MBX_CTRL		0x3038
#घोषणा QLA83XX_FW_MBX_CTRL		0x303C
#घोषणा QLA83XX_BOOTLOADER_ADDR		0x355C
#घोषणा QLA83XX_BOOTLOADER_SIZE		0x3560
#घोषणा QLA83XX_FW_IMAGE_ADDR		0x3564
#घोषणा QLA83XX_MBX_INTR_ENABLE		0x1000
#घोषणा QLA83XX_MBX_INTR_MASK		0x1200

/* IDC Control Register bit defines */
#घोषणा DONTRESET_BIT0		0x1
#घोषणा GRACEFUL_RESET_BIT1	0x2

#घोषणा QLA83XX_HALT_STATUS_INFORMATIONAL	(0x1 << 29)
#घोषणा QLA83XX_HALT_STATUS_FW_RESET		(0x2 << 29)
#घोषणा QLA83XX_HALT_STATUS_UNRECOVERABLE	(0x4 << 29)

/* Firmware image definitions */
#घोषणा QLA83XX_BOOTLOADER_FLASH_ADDR	0x10000
#घोषणा QLA83XX_BOOT_FROM_FLASH		0

#घोषणा QLA83XX_IDC_PARAM_ADDR		0x3e8020
/* Reset ढाँचा definitions */
#घोषणा QLA83XX_MAX_RESET_SEQ_ENTRIES	16
#घोषणा QLA83XX_RESTART_TEMPLATE_SIZE	0x2000
#घोषणा QLA83XX_RESET_TEMPLATE_ADDR	0x4F0000
#घोषणा QLA83XX_RESET_SEQ_VERSION	0x0101

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
काष्ठा qla4_83xx_reset_ढाँचा_hdr अणु
	__le16	version;
	__le16	signature;
	__le16	size;
	__le16	entries;
	__le16	hdr_size;
	__le16	checksum;
	__le16	init_seq_offset;
	__le16	start_seq_offset;
पूर्ण __packed;

/* Common Entry Header. */
काष्ठा qla4_83xx_reset_entry_hdr अणु
	__le16 cmd;
	__le16 size;
	__le16 count;
	__le16 delay;
पूर्ण __packed;

/* Generic poll entry type. */
काष्ठा qla4_83xx_poll अणु
	__le32  test_mask;
	__le32  test_value;
पूर्ण __packed;

/* Read modअगरy ग_लिखो entry type. */
काष्ठा qla4_83xx_rmw अणु
	__le32  test_mask;
	__le32  xor_value;
	__le32  or_value;
	uपूर्णांक8_t shl;
	uपूर्णांक8_t shr;
	uपूर्णांक8_t index_a;
	uपूर्णांक8_t rsvd;
पूर्ण __packed;

/* Generic Entry Item with 2 DWords. */
काष्ठा qla4_83xx_entry अणु
	__le32 arg1;
	__le32 arg2;
पूर्ण __packed;

/* Generic Entry Item with 4 DWords.*/
काष्ठा qla4_83xx_quad_entry अणु
	__le32 dr_addr;
	__le32 dr_value;
	__le32 ar_addr;
	__le32 ar_value;
पूर्ण __packed;

काष्ठा qla4_83xx_reset_ढाँचा अणु
	पूर्णांक seq_index;
	पूर्णांक seq_error;
	पूर्णांक array_index;
	uपूर्णांक32_t array[QLA83XX_MAX_RESET_SEQ_ENTRIES];
	uपूर्णांक8_t *buff;
	uपूर्णांक8_t *stop_offset;
	uपूर्णांक8_t *start_offset;
	uपूर्णांक8_t *init_offset;
	काष्ठा qla4_83xx_reset_ढाँचा_hdr *hdr;
	uपूर्णांक8_t seq_end;
	uपूर्णांक8_t ढाँचा_end;
पूर्ण;

/* POLLRD Entry */
काष्ठा qla83xx_minidump_entry_pollrd अणु
	काष्ठा qla8xxx_minidump_entry_hdr h;
	uपूर्णांक32_t select_addr;
	uपूर्णांक32_t पढ़ो_addr;
	uपूर्णांक32_t select_value;
	uपूर्णांक16_t select_value_stride;
	uपूर्णांक16_t op_count;
	uपूर्णांक32_t poll_रुको;
	uपूर्णांक32_t poll_mask;
	uपूर्णांक32_t data_size;
	uपूर्णांक32_t rsvd_1;
पूर्ण;

काष्ठा qla8044_minidump_entry_rddfe अणु
	काष्ठा qla8xxx_minidump_entry_hdr h;
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
	काष्ठा qla8xxx_minidump_entry_hdr h;

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
	काष्ठा qla8xxx_minidump_entry_hdr h;
	uपूर्णांक32_t addr_1;
	uपूर्णांक32_t addr_2;
	uपूर्णांक32_t value_1;
	uपूर्णांक32_t value_2;
	uपूर्णांक32_t poll;
	uपूर्णांक32_t mask;
	uपूर्णांक32_t data_size;
	uपूर्णांक32_t rsvd;

पूर्ण __packed;

/* RDMUX2 Entry */
काष्ठा qla83xx_minidump_entry_rdmux2 अणु
	काष्ठा qla8xxx_minidump_entry_hdr h;
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
पूर्ण;

/* POLLRDMWR Entry */
काष्ठा qla83xx_minidump_entry_pollrdmwr अणु
	काष्ठा qla8xxx_minidump_entry_hdr h;
	uपूर्णांक32_t addr_1;
	uपूर्णांक32_t addr_2;
	uपूर्णांक32_t value_1;
	uपूर्णांक32_t value_2;
	uपूर्णांक32_t poll_रुको;
	uपूर्णांक32_t poll_mask;
	uपूर्णांक32_t modअगरy_mask;
	uपूर्णांक32_t data_size;
पूर्ण;

/* IDC additional inक्रमmation */
काष्ठा qla4_83xx_idc_inक्रमmation अणु
	uपूर्णांक32_t request_desc;  /* IDC request descriptor */
	uपूर्णांक32_t info1; /* IDC additional info */
	uपूर्णांक32_t info2; /* IDC additional info */
	uपूर्णांक32_t info3; /* IDC additional info */
पूर्ण;

#घोषणा QLA83XX_PEX_DMA_ENGINE_INDEX		8
#घोषणा QLA83XX_PEX_DMA_BASE_ADDRESS		0x77320000
#घोषणा QLA83XX_PEX_DMA_NUM_OFFSET		0x10000
#घोषणा QLA83XX_PEX_DMA_CMD_ADDR_LOW		0x0
#घोषणा QLA83XX_PEX_DMA_CMD_ADDR_HIGH		0x04
#घोषणा QLA83XX_PEX_DMA_CMD_STS_AND_CNTRL	0x08

#घोषणा QLA83XX_PEX_DMA_READ_SIZE	(16 * 1024)
#घोषणा QLA83XX_PEX_DMA_MAX_WAIT	(100 * 100) /* Max रुको of 100 msecs */

/* Read Memory: For Pex-DMA */
काष्ठा qla4_83xx_minidump_entry_rdmem_pex_dma अणु
	काष्ठा qla8xxx_minidump_entry_hdr h;
	uपूर्णांक32_t desc_card_addr;
	uपूर्णांक16_t dma_desc_cmd;
	uपूर्णांक8_t rsvd[2];
	uपूर्णांक32_t start_dma_cmd;
	uपूर्णांक8_t rsvd2[12];
	uपूर्णांक32_t पढ़ो_addr;
	uपूर्णांक32_t पढ़ो_data_size;
पूर्ण;

काष्ठा qla4_83xx_pex_dma_descriptor अणु
	काष्ठा अणु
		uपूर्णांक32_t पढ़ो_data_size; /* 0-23: size, 24-31: rsvd */
		uपूर्णांक8_t rsvd[2];
		uपूर्णांक16_t dma_desc_cmd;
	पूर्ण cmd;
	uपूर्णांक64_t src_addr;
	uपूर्णांक64_t dma_bus_addr; /* 0-3: desc-cmd, 4-7: pci-func,
				* 8-15: desc-cmd */
	uपूर्णांक8_t rsvd[24];
पूर्ण __packed;

#पूर्ण_अगर
