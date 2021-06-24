<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-3-Clause)
/* QLogic qed NIC Driver
 * Copyright (c) 2015 QLogic Corporation
 * Copyright (c) 2019-2020 Marvell International Ltd.
 */

#समावेश <linux/module.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/crc32.h>
#समावेश "qed.h"
#समावेश "qed_cxt.h"
#समावेश "qed_hsi.h"
#समावेश "qed_hw.h"
#समावेश "qed_mcp.h"
#समावेश "qed_reg_addr.h"

/* Memory groups क्रमागत */
क्रमागत mem_groups अणु
	MEM_GROUP_PXP_MEM,
	MEM_GROUP_DMAE_MEM,
	MEM_GROUP_CM_MEM,
	MEM_GROUP_QM_MEM,
	MEM_GROUP_DORQ_MEM,
	MEM_GROUP_BRB_RAM,
	MEM_GROUP_BRB_MEM,
	MEM_GROUP_PRS_MEM,
	MEM_GROUP_SDM_MEM,
	MEM_GROUP_PBUF,
	MEM_GROUP_IOR,
	MEM_GROUP_RAM,
	MEM_GROUP_BTB_RAM,
	MEM_GROUP_RDIF_CTX,
	MEM_GROUP_TDIF_CTX,
	MEM_GROUP_CFC_MEM,
	MEM_GROUP_CONN_CFC_MEM,
	MEM_GROUP_CAU_PI,
	MEM_GROUP_CAU_MEM,
	MEM_GROUP_CAU_MEM_EXT,
	MEM_GROUP_PXP_ILT,
	MEM_GROUP_MULD_MEM,
	MEM_GROUP_BTB_MEM,
	MEM_GROUP_IGU_MEM,
	MEM_GROUP_IGU_MSIX,
	MEM_GROUP_CAU_SB,
	MEM_GROUP_BMB_RAM,
	MEM_GROUP_BMB_MEM,
	MEM_GROUP_TM_MEM,
	MEM_GROUP_TASK_CFC_MEM,
	MEM_GROUPS_NUM
पूर्ण;

/* Memory groups names */
अटल स्थिर अक्षर * स्थिर s_mem_group_names[] = अणु
	"PXP_MEM",
	"DMAE_MEM",
	"CM_MEM",
	"QM_MEM",
	"DORQ_MEM",
	"BRB_RAM",
	"BRB_MEM",
	"PRS_MEM",
	"SDM_MEM",
	"PBUF",
	"IOR",
	"RAM",
	"BTB_RAM",
	"RDIF_CTX",
	"TDIF_CTX",
	"CFC_MEM",
	"CONN_CFC_MEM",
	"CAU_PI",
	"CAU_MEM",
	"CAU_MEM_EXT",
	"PXP_ILT",
	"MULD_MEM",
	"BTB_MEM",
	"IGU_MEM",
	"IGU_MSIX",
	"CAU_SB",
	"BMB_RAM",
	"BMB_MEM",
	"TM_MEM",
	"TASK_CFC_MEM",
पूर्ण;

/* Idle check conditions */

अटल u32 cond5(स्थिर u32 *r, स्थिर u32 *imm)
अणु
	वापस ((r[0] & imm[0]) != imm[1]) && ((r[1] & imm[2]) != imm[3]);
पूर्ण

अटल u32 cond7(स्थिर u32 *r, स्थिर u32 *imm)
अणु
	वापस ((r[0] >> imm[0]) & imm[1]) != imm[2];
पूर्ण

अटल u32 cond6(स्थिर u32 *r, स्थिर u32 *imm)
अणु
	वापस (r[0] & imm[0]) != imm[1];
पूर्ण

अटल u32 cond9(स्थिर u32 *r, स्थिर u32 *imm)
अणु
	वापस ((r[0] & imm[0]) >> imm[1]) !=
	    (((r[0] & imm[2]) >> imm[3]) | ((r[1] & imm[4]) << imm[5]));
पूर्ण

अटल u32 cond10(स्थिर u32 *r, स्थिर u32 *imm)
अणु
	वापस ((r[0] & imm[0]) >> imm[1]) != (r[0] & imm[2]);
पूर्ण

अटल u32 cond4(स्थिर u32 *r, स्थिर u32 *imm)
अणु
	वापस (r[0] & ~imm[0]) != imm[1];
पूर्ण

अटल u32 cond0(स्थिर u32 *r, स्थिर u32 *imm)
अणु
	वापस (r[0] & ~r[1]) != imm[0];
पूर्ण

अटल u32 cond1(स्थिर u32 *r, स्थिर u32 *imm)
अणु
	वापस r[0] != imm[0];
पूर्ण

अटल u32 cond11(स्थिर u32 *r, स्थिर u32 *imm)
अणु
	वापस r[0] != r[1] && r[2] == imm[0];
पूर्ण

अटल u32 cond12(स्थिर u32 *r, स्थिर u32 *imm)
अणु
	वापस r[0] != r[1] && r[2] > imm[0];
पूर्ण

अटल u32 cond3(स्थिर u32 *r, स्थिर u32 *imm)
अणु
	वापस r[0] != r[1];
पूर्ण

अटल u32 cond13(स्थिर u32 *r, स्थिर u32 *imm)
अणु
	वापस r[0] & imm[0];
पूर्ण

अटल u32 cond8(स्थिर u32 *r, स्थिर u32 *imm)
अणु
	वापस r[0] < (r[1] - imm[0]);
पूर्ण

अटल u32 cond2(स्थिर u32 *r, स्थिर u32 *imm)
अणु
	वापस r[0] > imm[0];
पूर्ण

/* Array of Idle Check conditions */
अटल u32(*cond_arr[]) (स्थिर u32 *r, स्थिर u32 *imm) = अणु
	cond0,
	cond1,
	cond2,
	cond3,
	cond4,
	cond5,
	cond6,
	cond7,
	cond8,
	cond9,
	cond10,
	cond11,
	cond12,
	cond13,
पूर्ण;

#घोषणा NUM_PHYS_BLOCKS 84

#घोषणा NUM_DBG_RESET_REGS 8

/******************************* Data Types **********************************/

क्रमागत hw_types अणु
	HW_TYPE_ASIC,
	PLATFORM_RESERVED,
	PLATFORM_RESERVED2,
	PLATFORM_RESERVED3,
	PLATFORM_RESERVED4,
	MAX_HW_TYPES
पूर्ण;

/* CM context types */
क्रमागत cm_ctx_types अणु
	CM_CTX_CONN_AG,
	CM_CTX_CONN_ST,
	CM_CTX_TASK_AG,
	CM_CTX_TASK_ST,
	NUM_CM_CTX_TYPES
पूर्ण;

/* Debug bus frame modes */
क्रमागत dbg_bus_frame_modes अणु
	DBG_BUS_FRAME_MODE_4ST = 0,	/* 4 Storm dwords (no HW) */
	DBG_BUS_FRAME_MODE_2ST_2HW = 1,	/* 2 Storm dwords, 2 HW dwords */
	DBG_BUS_FRAME_MODE_1ST_3HW = 2,	/* 1 Storm dwords, 3 HW dwords */
	DBG_BUS_FRAME_MODE_4HW = 3,	/* 4 HW dwords (no Storms) */
	DBG_BUS_FRAME_MODE_8HW = 4,	/* 8 HW dwords (no Storms) */
	DBG_BUS_NUM_FRAME_MODES
पूर्ण;

/* Chip स्थिरant definitions */
काष्ठा chip_defs अणु
	स्थिर अक्षर *name;
	u32 num_ilt_pages;
पूर्ण;

/* HW type स्थिरant definitions */
काष्ठा hw_type_defs अणु
	स्थिर अक्षर *name;
	u32 delay_factor;
	u32 dmae_thresh;
	u32 log_thresh;
पूर्ण;

/* RBC reset definitions */
काष्ठा rbc_reset_defs अणु
	u32 reset_reg_addr;
	u32 reset_val[MAX_CHIP_IDS];
पूर्ण;

/* Storm स्थिरant definitions.
 * Addresses are in bytes, sizes are in quad-regs.
 */
काष्ठा storm_defs अणु
	अक्षर letter;
	क्रमागत block_id sem_block_id;
	क्रमागत dbg_bus_clients dbg_client_id[MAX_CHIP_IDS];
	bool has_vfc;
	u32 sem_fast_mem_addr;
	u32 sem_frame_mode_addr;
	u32 sem_slow_enable_addr;
	u32 sem_slow_mode_addr;
	u32 sem_slow_mode1_conf_addr;
	u32 sem_sync_dbg_empty_addr;
	u32 sem_gpre_vect_addr;
	u32 cm_ctx_wr_addr;
	u32 cm_ctx_rd_addr[NUM_CM_CTX_TYPES];
	u32 cm_ctx_lid_sizes[MAX_CHIP_IDS][NUM_CM_CTX_TYPES];
पूर्ण;

/* Debug Bus Constraपूर्णांक operation स्थिरant definitions */
काष्ठा dbg_bus_स्थिरraपूर्णांक_op_defs अणु
	u8 hw_op_val;
	bool is_cyclic;
पूर्ण;

/* Storm Mode definitions */
काष्ठा storm_mode_defs अणु
	स्थिर अक्षर *name;
	bool is_fast_dbg;
	u8 id_in_hw;
	u32 src_disable_reg_addr;
	u32 src_enable_val;
	bool exists[MAX_CHIP_IDS];
पूर्ण;

काष्ठा grc_param_defs अणु
	u32 शेष_val[MAX_CHIP_IDS];
	u32 min;
	u32 max;
	bool is_preset;
	bool is_persistent;
	u32 exclude_all_preset_val;
	u32 crash_preset_val[MAX_CHIP_IDS];
पूर्ण;

/* Address is in 128b units. Width is in bits. */
काष्ठा rss_mem_defs अणु
	स्थिर अक्षर *mem_name;
	स्थिर अक्षर *type_name;
	u32 addr;
	u32 entry_width;
	u32 num_entries[MAX_CHIP_IDS];
पूर्ण;

काष्ठा vfc_ram_defs अणु
	स्थिर अक्षर *mem_name;
	स्थिर अक्षर *type_name;
	u32 base_row;
	u32 num_rows;
पूर्ण;

काष्ठा big_ram_defs अणु
	स्थिर अक्षर *instance_name;
	क्रमागत mem_groups mem_group_id;
	क्रमागत mem_groups ram_mem_group_id;
	क्रमागत dbg_grc_params grc_param;
	u32 addr_reg_addr;
	u32 data_reg_addr;
	u32 is_256b_reg_addr;
	u32 is_256b_bit_offset[MAX_CHIP_IDS];
	u32 ram_size[MAX_CHIP_IDS]; /* In dwords */
पूर्ण;

काष्ठा phy_defs अणु
	स्थिर अक्षर *phy_name;

	/* PHY base GRC address */
	u32 base_addr;

	/* Relative address of indirect TBUS address रेजिस्टर (bits 0..7) */
	u32 tbus_addr_lo_addr;

	/* Relative address of indirect TBUS address रेजिस्टर (bits 8..10) */
	u32 tbus_addr_hi_addr;

	/* Relative address of indirect TBUS data रेजिस्टर (bits 0..7) */
	u32 tbus_data_lo_addr;

	/* Relative address of indirect TBUS data रेजिस्टर (bits 8..11) */
	u32 tbus_data_hi_addr;
पूर्ण;

/* Split type definitions */
काष्ठा split_type_defs अणु
	स्थिर अक्षर *name;
पूर्ण;

/******************************** Constants **********************************/

#घोषणा BYTES_IN_DWORD			माप(u32)
/* In the macros below, size and offset are specअगरied in bits */
#घोषणा CEIL_DWORDS(size)		DIV_ROUND_UP(size, 32)
#घोषणा FIELD_BIT_OFFSET(type, field)	type ## _ ## field ## _ ## OFFSET
#घोषणा FIELD_BIT_SIZE(type, field)	type ## _ ## field ## _ ## SIZE
#घोषणा FIELD_DWORD_OFFSET(type, field) \
	 (पूर्णांक)(FIELD_BIT_OFFSET(type, field) / 32)
#घोषणा FIELD_DWORD_SHIFT(type, field)	(FIELD_BIT_OFFSET(type, field) % 32)
#घोषणा FIELD_BIT_MASK(type, field) \
	(((1 << FIELD_BIT_SIZE(type, field)) - 1) << \
	 FIELD_DWORD_SHIFT(type, field))

#घोषणा SET_VAR_FIELD(var, type, field, val) \
	करो अणु \
		var[FIELD_DWORD_OFFSET(type, field)] &=	\
		(~FIELD_BIT_MASK(type, field));	\
		var[FIELD_DWORD_OFFSET(type, field)] |= \
		(val) << FIELD_DWORD_SHIFT(type, field); \
	पूर्ण जबतक (0)

#घोषणा ARR_REG_WR(dev, ptt, addr, arr, arr_size) \
	करो अणु \
		क्रम (i = 0; i < (arr_size); i++) \
			qed_wr(dev, ptt, addr,	(arr)[i]); \
	पूर्ण जबतक (0)

#घोषणा DWORDS_TO_BYTES(dwords)		((dwords) * BYTES_IN_DWORD)
#घोषणा BYTES_TO_DWORDS(bytes)		((bytes) / BYTES_IN_DWORD)

/* extra lines include a signature line + optional latency events line */
#घोषणा NUM_EXTRA_DBG_LINES(block) \
	(GET_FIELD((block)->flags, DBG_BLOCK_CHIP_HAS_LATENCY_EVENTS) ? 2 : 1)
#घोषणा NUM_DBG_LINES(block) \
	((block)->num_of_dbg_bus_lines + NUM_EXTRA_DBG_LINES(block))

#घोषणा USE_DMAE			true
#घोषणा PROTECT_WIDE_BUS		true

#घोषणा RAM_LINES_TO_DWORDS(lines)	((lines) * 2)
#घोषणा RAM_LINES_TO_BYTES(lines) \
	DWORDS_TO_BYTES(RAM_LINES_TO_DWORDS(lines))

#घोषणा REG_DUMP_LEN_SHIFT		24
#घोषणा MEM_DUMP_ENTRY_SIZE_DWORDS \
	BYTES_TO_DWORDS(माप(काष्ठा dbg_dump_mem))

#घोषणा IDLE_CHK_RULE_SIZE_DWORDS \
	BYTES_TO_DWORDS(माप(काष्ठा dbg_idle_chk_rule))

#घोषणा IDLE_CHK_RESULT_HDR_DWORDS \
	BYTES_TO_DWORDS(माप(काष्ठा dbg_idle_chk_result_hdr))

#घोषणा IDLE_CHK_RESULT_REG_HDR_DWORDS \
	BYTES_TO_DWORDS(माप(काष्ठा dbg_idle_chk_result_reg_hdr))

#घोषणा PAGE_MEM_DESC_SIZE_DWORDS \
	BYTES_TO_DWORDS(माप(काष्ठा phys_mem_desc))

#घोषणा IDLE_CHK_MAX_ENTRIES_SIZE	32

/* The sizes and offsets below are specअगरied in bits */
#घोषणा VFC_CAM_CMD_STRUCT_SIZE		64
#घोषणा VFC_CAM_CMD_ROW_OFFSET		48
#घोषणा VFC_CAM_CMD_ROW_SIZE		9
#घोषणा VFC_CAM_ADDR_STRUCT_SIZE	16
#घोषणा VFC_CAM_ADDR_OP_OFFSET		0
#घोषणा VFC_CAM_ADDR_OP_SIZE		4
#घोषणा VFC_CAM_RESP_STRUCT_SIZE	256
#घोषणा VFC_RAM_ADDR_STRUCT_SIZE	16
#घोषणा VFC_RAM_ADDR_OP_OFFSET		0
#घोषणा VFC_RAM_ADDR_OP_SIZE		2
#घोषणा VFC_RAM_ADDR_ROW_OFFSET		2
#घोषणा VFC_RAM_ADDR_ROW_SIZE		10
#घोषणा VFC_RAM_RESP_STRUCT_SIZE	256

#घोषणा VFC_CAM_CMD_DWORDS		CEIL_DWORDS(VFC_CAM_CMD_STRUCT_SIZE)
#घोषणा VFC_CAM_ADDR_DWORDS		CEIL_DWORDS(VFC_CAM_ADDR_STRUCT_SIZE)
#घोषणा VFC_CAM_RESP_DWORDS		CEIL_DWORDS(VFC_CAM_RESP_STRUCT_SIZE)
#घोषणा VFC_RAM_CMD_DWORDS		VFC_CAM_CMD_DWORDS
#घोषणा VFC_RAM_ADDR_DWORDS		CEIL_DWORDS(VFC_RAM_ADDR_STRUCT_SIZE)
#घोषणा VFC_RAM_RESP_DWORDS		CEIL_DWORDS(VFC_RAM_RESP_STRUCT_SIZE)

#घोषणा NUM_VFC_RAM_TYPES		4

#घोषणा VFC_CAM_NUM_ROWS		512

#घोषणा VFC_OPCODE_CAM_RD		14
#घोषणा VFC_OPCODE_RAM_RD		0

#घोषणा NUM_RSS_MEM_TYPES		5

#घोषणा NUM_BIG_RAM_TYPES		3
#घोषणा BIG_RAM_NAME_LEN		3

#घोषणा NUM_PHY_TBUS_ADDRESSES		2048
#घोषणा PHY_DUMP_SIZE_DWORDS		(NUM_PHY_TBUS_ADDRESSES / 2)

#घोषणा RESET_REG_UNRESET_OFFSET	4

#घोषणा STALL_DELAY_MS			500

#घोषणा STATIC_DEBUG_LINE_DWORDS	9

#घोषणा NUM_COMMON_GLOBAL_PARAMS	9

#घोषणा MAX_RECURSION_DEPTH		10

#घोषणा FW_IMG_MAIN			1

#घोषणा REG_FIFO_ELEMENT_DWORDS		2
#घोषणा REG_FIFO_DEPTH_ELEMENTS		32
#घोषणा REG_FIFO_DEPTH_DWORDS \
	(REG_FIFO_ELEMENT_DWORDS * REG_FIFO_DEPTH_ELEMENTS)

#घोषणा IGU_FIFO_ELEMENT_DWORDS		4
#घोषणा IGU_FIFO_DEPTH_ELEMENTS		64
#घोषणा IGU_FIFO_DEPTH_DWORDS \
	(IGU_FIFO_ELEMENT_DWORDS * IGU_FIFO_DEPTH_ELEMENTS)

#घोषणा PROTECTION_OVERRIDE_ELEMENT_DWORDS	2
#घोषणा PROTECTION_OVERRIDE_DEPTH_ELEMENTS	20
#घोषणा PROTECTION_OVERRIDE_DEPTH_DWORDS \
	(PROTECTION_OVERRIDE_DEPTH_ELEMENTS * \
	 PROTECTION_OVERRIDE_ELEMENT_DWORDS)

#घोषणा MCP_SPAD_TRACE_OFFSIZE_ADDR \
	(MCP_REG_SCRATCH + \
	 दुरत्व(काष्ठा अटल_init, sections[SPAD_SECTION_TRACE]))

#घोषणा MAX_SW_PLTAFORM_STR_SIZE	64

#घोषणा EMPTY_FW_VERSION_STR		"???_???_???_???"
#घोषणा EMPTY_FW_IMAGE_STR		"???????????????"

/***************************** Constant Arrays *******************************/

/* Chip स्थिरant definitions array */
अटल काष्ठा chip_defs s_chip_defs[MAX_CHIP_IDS] = अणु
	अणु"bb", PSWRQ2_REG_ILT_MEMORY_SIZE_BB / 2पूर्ण,
	अणु"ah", PSWRQ2_REG_ILT_MEMORY_SIZE_K2 / 2पूर्ण
पूर्ण;

/* Storm स्थिरant definitions array */
अटल काष्ठा storm_defs s_storm_defs[] = अणु
	/* Tstorm */
	अणु'T', BLOCK_TSEM,
		अणुDBG_BUS_CLIENT_RBCT, DBG_BUS_CLIENT_RBCTपूर्ण,
		true,
		TSEM_REG_FAST_MEMORY,
		TSEM_REG_DBG_FRAME_MODE_BB_K2, TSEM_REG_SLOW_DBG_ACTIVE_BB_K2,
		TSEM_REG_SLOW_DBG_MODE_BB_K2, TSEM_REG_DBG_MODE1_CFG_BB_K2,
		TSEM_REG_SYNC_DBG_EMPTY, TSEM_REG_DBG_GPRE_VECT,
		TCM_REG_CTX_RBC_ACCS,
		अणुTCM_REG_AGG_CON_CTX, TCM_REG_SM_CON_CTX, TCM_REG_AGG_TASK_CTX,
		 TCM_REG_SM_TASK_CTXपूर्ण,
		अणुअणु4, 16, 2, 4पूर्ण, अणु4, 16, 2, 4पूर्णपूर्ण /* अणुbbपूर्ण अणुk2पूर्ण */
	पूर्ण,

	/* Mstorm */
	अणु'M', BLOCK_MSEM,
		अणुDBG_BUS_CLIENT_RBCT, DBG_BUS_CLIENT_RBCMपूर्ण,
		false,
		MSEM_REG_FAST_MEMORY,
		MSEM_REG_DBG_FRAME_MODE_BB_K2,
		MSEM_REG_SLOW_DBG_ACTIVE_BB_K2,
		MSEM_REG_SLOW_DBG_MODE_BB_K2,
		MSEM_REG_DBG_MODE1_CFG_BB_K2,
		MSEM_REG_SYNC_DBG_EMPTY,
		MSEM_REG_DBG_GPRE_VECT,
		MCM_REG_CTX_RBC_ACCS,
		अणुMCM_REG_AGG_CON_CTX, MCM_REG_SM_CON_CTX, MCM_REG_AGG_TASK_CTX,
		 MCM_REG_SM_TASK_CTX पूर्ण,
		अणुअणु1, 10, 2, 7पूर्ण, अणु1, 10, 2, 7पूर्णपूर्ण /* अणुbbपूर्ण अणुk2पूर्ण*/
	पूर्ण,

	/* Ustorm */
	अणु'U', BLOCK_USEM,
		अणुDBG_BUS_CLIENT_RBCU, DBG_BUS_CLIENT_RBCUपूर्ण,
		false,
		USEM_REG_FAST_MEMORY,
		USEM_REG_DBG_FRAME_MODE_BB_K2,
		USEM_REG_SLOW_DBG_ACTIVE_BB_K2,
		USEM_REG_SLOW_DBG_MODE_BB_K2,
		USEM_REG_DBG_MODE1_CFG_BB_K2,
		USEM_REG_SYNC_DBG_EMPTY,
		USEM_REG_DBG_GPRE_VECT,
		UCM_REG_CTX_RBC_ACCS,
		अणुUCM_REG_AGG_CON_CTX, UCM_REG_SM_CON_CTX, UCM_REG_AGG_TASK_CTX,
		 UCM_REG_SM_TASK_CTXपूर्ण,
		अणुअणु2, 13, 3, 3पूर्ण, अणु2, 13, 3, 3पूर्णपूर्ण /* अणुbbपूर्ण अणुk2पूर्ण */
	पूर्ण,

	/* Xstorm */
	अणु'X', BLOCK_XSEM,
		अणुDBG_BUS_CLIENT_RBCX, DBG_BUS_CLIENT_RBCXपूर्ण,
		false,
		XSEM_REG_FAST_MEMORY,
		XSEM_REG_DBG_FRAME_MODE_BB_K2,
		XSEM_REG_SLOW_DBG_ACTIVE_BB_K2,
		XSEM_REG_SLOW_DBG_MODE_BB_K2,
		XSEM_REG_DBG_MODE1_CFG_BB_K2,
		XSEM_REG_SYNC_DBG_EMPTY,
		XSEM_REG_DBG_GPRE_VECT,
		XCM_REG_CTX_RBC_ACCS,
		अणुXCM_REG_AGG_CON_CTX, XCM_REG_SM_CON_CTX, 0, 0पूर्ण,
		अणुअणु9, 15, 0, 0पूर्ण, अणु9, 15,	0, 0पूर्णपूर्ण /* अणुbbपूर्ण अणुk2पूर्ण */
	पूर्ण,

	/* Ystorm */
	अणु'Y', BLOCK_YSEM,
		अणुDBG_BUS_CLIENT_RBCX, DBG_BUS_CLIENT_RBCYपूर्ण,
		false,
		YSEM_REG_FAST_MEMORY,
		YSEM_REG_DBG_FRAME_MODE_BB_K2,
		YSEM_REG_SLOW_DBG_ACTIVE_BB_K2,
		YSEM_REG_SLOW_DBG_MODE_BB_K2,
		YSEM_REG_DBG_MODE1_CFG_BB_K2,
		YSEM_REG_SYNC_DBG_EMPTY,
		YSEM_REG_DBG_GPRE_VECT,
		YCM_REG_CTX_RBC_ACCS,
		अणुYCM_REG_AGG_CON_CTX, YCM_REG_SM_CON_CTX, YCM_REG_AGG_TASK_CTX,
		 YCM_REG_SM_TASK_CTXपूर्ण,
		अणुअणु2, 3, 2, 12पूर्ण, अणु2, 3, 2, 12पूर्णपूर्ण /* अणुbbपूर्ण अणुk2पूर्ण */
	पूर्ण,

	/* Pstorm */
	अणु'P', BLOCK_PSEM,
		अणुDBG_BUS_CLIENT_RBCS, DBG_BUS_CLIENT_RBCSपूर्ण,
		true,
		PSEM_REG_FAST_MEMORY,
		PSEM_REG_DBG_FRAME_MODE_BB_K2,
		PSEM_REG_SLOW_DBG_ACTIVE_BB_K2,
		PSEM_REG_SLOW_DBG_MODE_BB_K2,
		PSEM_REG_DBG_MODE1_CFG_BB_K2,
		PSEM_REG_SYNC_DBG_EMPTY,
		PSEM_REG_DBG_GPRE_VECT,
		PCM_REG_CTX_RBC_ACCS,
		अणु0, PCM_REG_SM_CON_CTX, 0, 0पूर्ण,
		अणुअणु0, 10, 0, 0पूर्ण, अणु0, 10, 0, 0पूर्णपूर्ण /* अणुbbपूर्ण अणुk2पूर्ण */
	पूर्ण,
पूर्ण;

अटल काष्ठा hw_type_defs s_hw_type_defs[] = अणु
	/* HW_TYPE_ASIC */
	अणु"asic", 1, 256, 32768पूर्ण,
	अणु"reserved", 0, 0, 0पूर्ण,
	अणु"reserved2", 0, 0, 0पूर्ण,
	अणु"reserved3", 0, 0, 0पूर्ण
पूर्ण;

अटल काष्ठा grc_param_defs s_grc_param_defs[] = अणु
	/* DBG_GRC_PARAM_DUMP_TSTORM */
	अणुअणु1, 1पूर्ण, 0, 1, false, false, 1, अणु1, 1पूर्णपूर्ण,

	/* DBG_GRC_PARAM_DUMP_MSTORM */
	अणुअणु1, 1पूर्ण, 0, 1, false, false, 1, अणु1, 1पूर्णपूर्ण,

	/* DBG_GRC_PARAM_DUMP_USTORM */
	अणुअणु1, 1पूर्ण, 0, 1, false, false, 1, अणु1, 1पूर्णपूर्ण,

	/* DBG_GRC_PARAM_DUMP_XSTORM */
	अणुअणु1, 1पूर्ण, 0, 1, false, false, 1, अणु1, 1पूर्णपूर्ण,

	/* DBG_GRC_PARAM_DUMP_YSTORM */
	अणुअणु1, 1पूर्ण, 0, 1, false, false, 1, अणु1, 1पूर्णपूर्ण,

	/* DBG_GRC_PARAM_DUMP_PSTORM */
	अणुअणु1, 1पूर्ण, 0, 1, false, false, 1, अणु1, 1पूर्णपूर्ण,

	/* DBG_GRC_PARAM_DUMP_REGS */
	अणुअणु1, 1पूर्ण, 0, 1, false, false, 0, अणु1, 1पूर्णपूर्ण,

	/* DBG_GRC_PARAM_DUMP_RAM */
	अणुअणु1, 1पूर्ण, 0, 1, false, false, 0, अणु1, 1पूर्णपूर्ण,

	/* DBG_GRC_PARAM_DUMP_PBUF */
	अणुअणु1, 1पूर्ण, 0, 1, false, false, 0, अणु1, 1पूर्णपूर्ण,

	/* DBG_GRC_PARAM_DUMP_IOR */
	अणुअणु0, 0पूर्ण, 0, 1, false, false, 0, अणु1, 1पूर्णपूर्ण,

	/* DBG_GRC_PARAM_DUMP_VFC */
	अणुअणु0, 0पूर्ण, 0, 1, false, false, 0, अणु1, 1पूर्णपूर्ण,

	/* DBG_GRC_PARAM_DUMP_CM_CTX */
	अणुअणु1, 1पूर्ण, 0, 1, false, false, 0, अणु1, 1पूर्णपूर्ण,

	/* DBG_GRC_PARAM_DUMP_ILT */
	अणुअणु1, 1पूर्ण, 0, 1, false, false, 0, अणु1, 1पूर्णपूर्ण,

	/* DBG_GRC_PARAM_DUMP_RSS */
	अणुअणु1, 1पूर्ण, 0, 1, false, false, 0, अणु1, 1पूर्णपूर्ण,

	/* DBG_GRC_PARAM_DUMP_CAU */
	अणुअणु1, 1पूर्ण, 0, 1, false, false, 0, अणु1, 1पूर्णपूर्ण,

	/* DBG_GRC_PARAM_DUMP_QM */
	अणुअणु1, 1पूर्ण, 0, 1, false, false, 0, अणु1, 1पूर्णपूर्ण,

	/* DBG_GRC_PARAM_DUMP_MCP */
	अणुअणु1, 1पूर्ण, 0, 1, false, false, 0, अणु1, 1पूर्णपूर्ण,

	/* DBG_GRC_PARAM_DUMP_DORQ */
	अणुअणु1, 1पूर्ण, 0, 1, false, false, 0, अणु1, 1पूर्णपूर्ण,

	/* DBG_GRC_PARAM_DUMP_CFC */
	अणुअणु1, 1पूर्ण, 0, 1, false, false, 0, अणु1, 1पूर्णपूर्ण,

	/* DBG_GRC_PARAM_DUMP_IGU */
	अणुअणु1, 1पूर्ण, 0, 1, false, false, 0, अणु1, 1पूर्णपूर्ण,

	/* DBG_GRC_PARAM_DUMP_BRB */
	अणुअणु0, 0पूर्ण, 0, 1, false, false, 0, अणु1, 1पूर्णपूर्ण,

	/* DBG_GRC_PARAM_DUMP_BTB */
	अणुअणु0, 0पूर्ण, 0, 1, false, false, 0, अणु1, 1पूर्णपूर्ण,

	/* DBG_GRC_PARAM_DUMP_BMB */
	अणुअणु0, 0पूर्ण, 0, 1, false, false, 0, अणु0, 0पूर्णपूर्ण,

	/* DBG_GRC_PARAM_RESERVED1 */
	अणुअणु0, 0पूर्ण, 0, 1, false, false, 0, अणु0, 0पूर्णपूर्ण,

	/* DBG_GRC_PARAM_DUMP_MULD */
	अणुअणु1, 1पूर्ण, 0, 1, false, false, 0, अणु1, 1पूर्णपूर्ण,

	/* DBG_GRC_PARAM_DUMP_PRS */
	अणुअणु1, 1पूर्ण, 0, 1, false, false, 0, अणु1, 1पूर्णपूर्ण,

	/* DBG_GRC_PARAM_DUMP_DMAE */
	अणुअणु1, 1पूर्ण, 0, 1, false, false, 0, अणु1, 1पूर्णपूर्ण,

	/* DBG_GRC_PARAM_DUMP_TM */
	अणुअणु1, 1पूर्ण, 0, 1, false, false, 0, अणु1, 1पूर्णपूर्ण,

	/* DBG_GRC_PARAM_DUMP_SDM */
	अणुअणु1, 1पूर्ण, 0, 1, false, false, 0, अणु1, 1पूर्णपूर्ण,

	/* DBG_GRC_PARAM_DUMP_DIF */
	अणुअणु1, 1पूर्ण, 0, 1, false, false, 0, अणु1, 1पूर्णपूर्ण,

	/* DBG_GRC_PARAM_DUMP_STATIC */
	अणुअणु1, 1पूर्ण, 0, 1, false, false, 0, अणु1, 1पूर्णपूर्ण,

	/* DBG_GRC_PARAM_UNSTALL */
	अणुअणु0, 0पूर्ण, 0, 1, false, false, 0, अणु0, 0पूर्णपूर्ण,

	/* DBG_GRC_PARAM_RESERVED2 */
	अणुअणु0, 0पूर्ण, 0, 1, false, false, 0, अणु0, 0पूर्णपूर्ण,

	/* DBG_GRC_PARAM_MCP_TRACE_META_SIZE */
	अणुअणु0, 0पूर्ण, 1, 0xffffffff, false, true, 0, अणु0, 0पूर्णपूर्ण,

	/* DBG_GRC_PARAM_EXCLUDE_ALL */
	अणुअणु0, 0पूर्ण, 0, 1, true, false, 0, अणु0, 0पूर्णपूर्ण,

	/* DBG_GRC_PARAM_CRASH */
	अणुअणु0, 0पूर्ण, 0, 1, true, false, 0, अणु0, 0पूर्णपूर्ण,

	/* DBG_GRC_PARAM_PARITY_SAFE */
	अणुअणु0, 0पूर्ण, 0, 1, false, false, 0, अणु0, 0पूर्णपूर्ण,

	/* DBG_GRC_PARAM_DUMP_CM */
	अणुअणु1, 1पूर्ण, 0, 1, false, false, 0, अणु1, 1पूर्णपूर्ण,

	/* DBG_GRC_PARAM_DUMP_PHY */
	अणुअणु0, 0पूर्ण, 0, 1, false, false, 0, अणु0, 0पूर्णपूर्ण,

	/* DBG_GRC_PARAM_NO_MCP */
	अणुअणु0, 0पूर्ण, 0, 1, false, false, 0, अणु0, 0पूर्णपूर्ण,

	/* DBG_GRC_PARAM_NO_FW_VER */
	अणुअणु0, 0पूर्ण, 0, 1, false, false, 0, अणु0, 0पूर्णपूर्ण,

	/* DBG_GRC_PARAM_RESERVED3 */
	अणुअणु0, 0पूर्ण, 0, 1, false, false, 0, अणु0, 0पूर्णपूर्ण,

	/* DBG_GRC_PARAM_DUMP_MCP_HW_DUMP */
	अणुअणु0, 1पूर्ण, 0, 1, false, false, 0, अणु0, 1पूर्णपूर्ण,

	/* DBG_GRC_PARAM_DUMP_ILT_CDUC */
	अणुअणु1, 1पूर्ण, 0, 1, false, false, 0, अणु0, 0पूर्णपूर्ण,

	/* DBG_GRC_PARAM_DUMP_ILT_CDUT */
	अणुअणु1, 1पूर्ण, 0, 1, false, false, 0, अणु0, 0पूर्णपूर्ण,

	/* DBG_GRC_PARAM_DUMP_CAU_EXT */
	अणुअणु0, 0पूर्ण, 0, 1, false, false, 0, अणु1, 1पूर्णपूर्ण
पूर्ण;

अटल काष्ठा rss_mem_defs s_rss_mem_defs[] = अणु
	अणु"rss_mem_cid", "rss_cid", 0, 32,
	 अणु256, 320पूर्णपूर्ण,

	अणु"rss_mem_key_msb", "rss_key", 1024, 256,
	 अणु128, 208पूर्णपूर्ण,

	अणु"rss_mem_key_lsb", "rss_key", 2048, 64,
	 अणु128, 208पूर्णपूर्ण,

	अणु"rss_mem_info", "rss_info", 3072, 16,
	 अणु128, 208पूर्णपूर्ण,

	अणु"rss_mem_ind", "rss_ind", 4096, 16,
	 अणु16384, 26624पूर्णपूर्ण
पूर्ण;

अटल काष्ठा vfc_ram_defs s_vfc_ram_defs[] = अणु
	अणु"vfc_ram_tt1", "vfc_ram", 0, 512पूर्ण,
	अणु"vfc_ram_mtt2", "vfc_ram", 512, 128पूर्ण,
	अणु"vfc_ram_stt2", "vfc_ram", 640, 32पूर्ण,
	अणु"vfc_ram_ro_vect", "vfc_ram", 672, 32पूर्ण
पूर्ण;

अटल काष्ठा big_ram_defs s_big_ram_defs[] = अणु
	अणु"BRB", MEM_GROUP_BRB_MEM, MEM_GROUP_BRB_RAM, DBG_GRC_PARAM_DUMP_BRB,
	 BRB_REG_BIG_RAM_ADDRESS, BRB_REG_BIG_RAM_DATA,
	 MISC_REG_BLOCK_256B_EN, अणु0, 0पूर्ण,
	 अणु153600, 180224पूर्णपूर्ण,

	अणु"BTB", MEM_GROUP_BTB_MEM, MEM_GROUP_BTB_RAM, DBG_GRC_PARAM_DUMP_BTB,
	 BTB_REG_BIG_RAM_ADDRESS, BTB_REG_BIG_RAM_DATA,
	 MISC_REG_BLOCK_256B_EN, अणु0, 1पूर्ण,
	 अणु92160, 117760पूर्णपूर्ण,

	अणु"BMB", MEM_GROUP_BMB_MEM, MEM_GROUP_BMB_RAM, DBG_GRC_PARAM_DUMP_BMB,
	 BMB_REG_BIG_RAM_ADDRESS, BMB_REG_BIG_RAM_DATA,
	 MISCS_REG_BLOCK_256B_EN, अणु0, 0पूर्ण,
	 अणु36864, 36864पूर्णपूर्ण
पूर्ण;

अटल काष्ठा rbc_reset_defs s_rbc_reset_defs[] = अणु
	अणुMISCS_REG_RESET_PL_HV,
	 अणु0x0, 0x400पूर्णपूर्ण,
	अणुMISC_REG_RESET_PL_PDA_VMAIN_1,
	 अणु0x4404040, 0x4404040पूर्णपूर्ण,
	अणुMISC_REG_RESET_PL_PDA_VMAIN_2,
	 अणु0x7, 0x7c00007पूर्णपूर्ण,
	अणुMISC_REG_RESET_PL_PDA_VAUX,
	 अणु0x2, 0x2पूर्णपूर्ण,
पूर्ण;

अटल काष्ठा phy_defs s_phy_defs[] = अणु
	अणु"nw_phy", NWS_REG_NWS_CMU_K2,
	 PHY_NW_IP_REG_PHY0_TOP_TBUS_ADDR_7_0_K2_E5,
	 PHY_NW_IP_REG_PHY0_TOP_TBUS_ADDR_15_8_K2_E5,
	 PHY_NW_IP_REG_PHY0_TOP_TBUS_DATA_7_0_K2_E5,
	 PHY_NW_IP_REG_PHY0_TOP_TBUS_DATA_11_8_K2_E5पूर्ण,
	अणु"sgmii_phy", MS_REG_MS_CMU_K2_E5,
	 PHY_SGMII_IP_REG_AHB_CMU_CSR_0_X132_K2_E5,
	 PHY_SGMII_IP_REG_AHB_CMU_CSR_0_X133_K2_E5,
	 PHY_SGMII_IP_REG_AHB_CMU_CSR_0_X130_K2_E5,
	 PHY_SGMII_IP_REG_AHB_CMU_CSR_0_X131_K2_E5पूर्ण,
	अणु"pcie_phy0", PHY_PCIE_REG_PHY0_K2_E5,
	 PHY_PCIE_IP_REG_AHB_CMU_CSR_0_X132_K2_E5,
	 PHY_PCIE_IP_REG_AHB_CMU_CSR_0_X133_K2_E5,
	 PHY_PCIE_IP_REG_AHB_CMU_CSR_0_X130_K2_E5,
	 PHY_PCIE_IP_REG_AHB_CMU_CSR_0_X131_K2_E5पूर्ण,
	अणु"pcie_phy1", PHY_PCIE_REG_PHY1_K2_E5,
	 PHY_PCIE_IP_REG_AHB_CMU_CSR_0_X132_K2_E5,
	 PHY_PCIE_IP_REG_AHB_CMU_CSR_0_X133_K2_E5,
	 PHY_PCIE_IP_REG_AHB_CMU_CSR_0_X130_K2_E5,
	 PHY_PCIE_IP_REG_AHB_CMU_CSR_0_X131_K2_E5पूर्ण,
पूर्ण;

अटल काष्ठा split_type_defs s_split_type_defs[] = अणु
	/* SPLIT_TYPE_NONE */
	अणु"eng"पूर्ण,

	/* SPLIT_TYPE_PORT */
	अणु"port"पूर्ण,

	/* SPLIT_TYPE_PF */
	अणु"pf"पूर्ण,

	/* SPLIT_TYPE_PORT_PF */
	अणु"port"पूर्ण,

	/* SPLIT_TYPE_VF */
	अणु"vf"पूर्ण
पूर्ण;

/**************************** Private Functions ******************************/

/* Reads and वापसs a single dword from the specअगरied unaligned buffer */
अटल u32 qed_पढ़ो_unaligned_dword(u8 *buf)
अणु
	u32 dword;

	स_नकल((u8 *)&dword, buf, माप(dword));
	वापस dword;
पूर्ण

/* Sets the value of the specअगरied GRC param */
अटल व्योम qed_grc_set_param(काष्ठा qed_hwfn *p_hwfn,
			      क्रमागत dbg_grc_params grc_param, u32 val)
अणु
	काष्ठा dbg_tools_data *dev_data = &p_hwfn->dbg_info;

	dev_data->grc.param_val[grc_param] = val;
पूर्ण

/* Returns the value of the specअगरied GRC param */
अटल u32 qed_grc_get_param(काष्ठा qed_hwfn *p_hwfn,
			     क्रमागत dbg_grc_params grc_param)
अणु
	काष्ठा dbg_tools_data *dev_data = &p_hwfn->dbg_info;

	वापस dev_data->grc.param_val[grc_param];
पूर्ण

/* Initializes the GRC parameters */
अटल व्योम qed_dbg_grc_init_params(काष्ठा qed_hwfn *p_hwfn)
अणु
	काष्ठा dbg_tools_data *dev_data = &p_hwfn->dbg_info;

	अगर (!dev_data->grc.params_initialized) अणु
		qed_dbg_grc_set_params_शेष(p_hwfn);
		dev_data->grc.params_initialized = 1;
	पूर्ण
पूर्ण

/* Sets poपूर्णांकer and size क्रम the specअगरied binary buffer type */
अटल व्योम qed_set_dbg_bin_buf(काष्ठा qed_hwfn *p_hwfn,
				क्रमागत bin_dbg_buffer_type buf_type,
				स्थिर u32 *ptr, u32 size)
अणु
	काष्ठा virt_mem_desc *buf = &p_hwfn->dbg_arrays[buf_type];

	buf->ptr = (व्योम *)ptr;
	buf->size = size;
पूर्ण

/* Initializes debug data क्रम the specअगरied device */
अटल क्रमागत dbg_status qed_dbg_dev_init(काष्ठा qed_hwfn *p_hwfn)
अणु
	काष्ठा dbg_tools_data *dev_data = &p_hwfn->dbg_info;
	u8 num_pfs = 0, max_pfs_per_port = 0;

	अगर (dev_data->initialized)
		वापस DBG_STATUS_OK;

	/* Set chip */
	अगर (QED_IS_K2(p_hwfn->cdev)) अणु
		dev_data->chip_id = CHIP_K2;
		dev_data->mode_enable[MODE_K2] = 1;
		dev_data->num_vfs = MAX_NUM_VFS_K2;
		num_pfs = MAX_NUM_PFS_K2;
		max_pfs_per_port = MAX_NUM_PFS_K2 / 2;
	पूर्ण अन्यथा अगर (QED_IS_BB_B0(p_hwfn->cdev)) अणु
		dev_data->chip_id = CHIP_BB;
		dev_data->mode_enable[MODE_BB] = 1;
		dev_data->num_vfs = MAX_NUM_VFS_BB;
		num_pfs = MAX_NUM_PFS_BB;
		max_pfs_per_port = MAX_NUM_PFS_BB;
	पूर्ण अन्यथा अणु
		वापस DBG_STATUS_UNKNOWN_CHIP;
	पूर्ण

	/* Set HW type */
	dev_data->hw_type = HW_TYPE_ASIC;
	dev_data->mode_enable[MODE_ASIC] = 1;

	/* Set port mode */
	चयन (p_hwfn->cdev->num_ports_in_engine) अणु
	हाल 1:
		dev_data->mode_enable[MODE_PORTS_PER_ENG_1] = 1;
		अवरोध;
	हाल 2:
		dev_data->mode_enable[MODE_PORTS_PER_ENG_2] = 1;
		अवरोध;
	हाल 4:
		dev_data->mode_enable[MODE_PORTS_PER_ENG_4] = 1;
		अवरोध;
	पूर्ण

	/* Set 100G mode */
	अगर (QED_IS_CMT(p_hwfn->cdev))
		dev_data->mode_enable[MODE_100G] = 1;

	/* Set number of ports */
	अगर (dev_data->mode_enable[MODE_PORTS_PER_ENG_1] ||
	    dev_data->mode_enable[MODE_100G])
		dev_data->num_ports = 1;
	अन्यथा अगर (dev_data->mode_enable[MODE_PORTS_PER_ENG_2])
		dev_data->num_ports = 2;
	अन्यथा अगर (dev_data->mode_enable[MODE_PORTS_PER_ENG_4])
		dev_data->num_ports = 4;

	/* Set number of PFs per port */
	dev_data->num_pfs_per_port = min_t(u32,
					   num_pfs / dev_data->num_ports,
					   max_pfs_per_port);

	/* Initializes the GRC parameters */
	qed_dbg_grc_init_params(p_hwfn);

	dev_data->use_dmae = true;
	dev_data->initialized = 1;

	वापस DBG_STATUS_OK;
पूर्ण

अटल स्थिर काष्ठा dbg_block *get_dbg_block(काष्ठा qed_hwfn *p_hwfn,
					     क्रमागत block_id block_id)
अणु
	स्थिर काष्ठा dbg_block *dbg_block;

	dbg_block = p_hwfn->dbg_arrays[BIN_BUF_DBG_BLOCKS].ptr;
	वापस dbg_block + block_id;
पूर्ण

अटल स्थिर काष्ठा dbg_block_chip *qed_get_dbg_block_per_chip(काष्ठा qed_hwfn
							       *p_hwfn,
							       क्रमागत block_id
							       block_id)
अणु
	काष्ठा dbg_tools_data *dev_data = &p_hwfn->dbg_info;

	वापस (स्थिर काष्ठा dbg_block_chip *)
	    p_hwfn->dbg_arrays[BIN_BUF_DBG_BLOCKS_CHIP_DATA].ptr +
	    block_id * MAX_CHIP_IDS + dev_data->chip_id;
पूर्ण

अटल स्थिर काष्ठा dbg_reset_reg *qed_get_dbg_reset_reg(काष्ठा qed_hwfn
							 *p_hwfn,
							 u8 reset_reg_id)
अणु
	काष्ठा dbg_tools_data *dev_data = &p_hwfn->dbg_info;

	वापस (स्थिर काष्ठा dbg_reset_reg *)
	    p_hwfn->dbg_arrays[BIN_BUF_DBG_RESET_REGS].ptr +
	    reset_reg_id * MAX_CHIP_IDS + dev_data->chip_id;
पूर्ण

/* Reads the FW info काष्ठाure क्रम the specअगरied Storm from the chip,
 * and ग_लिखोs it to the specअगरied fw_info poपूर्णांकer.
 */
अटल व्योम qed_पढ़ो_storm_fw_info(काष्ठा qed_hwfn *p_hwfn,
				   काष्ठा qed_ptt *p_ptt,
				   u8 storm_id, काष्ठा fw_info *fw_info)
अणु
	काष्ठा storm_defs *storm = &s_storm_defs[storm_id];
	काष्ठा fw_info_location fw_info_location;
	u32 addr, i, size, *dest;

	स_रखो(&fw_info_location, 0, माप(fw_info_location));
	स_रखो(fw_info, 0, माप(*fw_info));

	/* Read first the address that poपूर्णांकs to fw_info location.
	 * The address is located in the last line of the Storm RAM.
	 */
	addr = storm->sem_fast_mem_addr + SEM_FAST_REG_INT_RAM +
	    DWORDS_TO_BYTES(SEM_FAST_REG_INT_RAM_SIZE) -
	    माप(fw_info_location);

	dest = (u32 *)&fw_info_location;
	size = BYTES_TO_DWORDS(माप(fw_info_location));

	क्रम (i = 0; i < size; i++, addr += BYTES_IN_DWORD)
		dest[i] = qed_rd(p_hwfn, p_ptt, addr);

	/* qed_rq() fetches data in CPU byteorder. Swap it back to
	 * the device's to get right काष्ठाure layout.
	 */
	cpu_to_le32_array(dest, size);

	/* Read FW version info from Storm RAM */
	size = le32_to_cpu(fw_info_location.size);
	अगर (!size || size > माप(*fw_info))
		वापस;

	addr = le32_to_cpu(fw_info_location.grc_addr);
	dest = (u32 *)fw_info;
	size = BYTES_TO_DWORDS(size);

	क्रम (i = 0; i < size; i++, addr += BYTES_IN_DWORD)
		dest[i] = qed_rd(p_hwfn, p_ptt, addr);

	cpu_to_le32_array(dest, size);
पूर्ण

/* Dumps the specअगरied string to the specअगरied buffer.
 * Returns the dumped size in bytes.
 */
अटल u32 qed_dump_str(अक्षर *dump_buf, bool dump, स्थिर अक्षर *str)
अणु
	अगर (dump)
		म_नकल(dump_buf, str);

	वापस (u32)म_माप(str) + 1;
पूर्ण

/* Dumps zeros to align the specअगरied buffer to dwords.
 * Returns the dumped size in bytes.
 */
अटल u32 qed_dump_align(अक्षर *dump_buf, bool dump, u32 byte_offset)
अणु
	u8 offset_in_dword, align_size;

	offset_in_dword = (u8)(byte_offset & 0x3);
	align_size = offset_in_dword ? BYTES_IN_DWORD - offset_in_dword : 0;

	अगर (dump && align_size)
		स_रखो(dump_buf, 0, align_size);

	वापस align_size;
पूर्ण

/* Writes the specअगरied string param to the specअगरied buffer.
 * Returns the dumped size in dwords.
 */
अटल u32 qed_dump_str_param(u32 *dump_buf,
			      bool dump,
			      स्थिर अक्षर *param_name, स्थिर अक्षर *param_val)
अणु
	अक्षर *अक्षर_buf = (अक्षर *)dump_buf;
	u32 offset = 0;

	/* Dump param name */
	offset += qed_dump_str(अक्षर_buf + offset, dump, param_name);

	/* Indicate a string param value */
	अगर (dump)
		*(अक्षर_buf + offset) = 1;
	offset++;

	/* Dump param value */
	offset += qed_dump_str(अक्षर_buf + offset, dump, param_val);

	/* Align buffer to next dword */
	offset += qed_dump_align(अक्षर_buf + offset, dump, offset);

	वापस BYTES_TO_DWORDS(offset);
पूर्ण

/* Writes the specअगरied numeric param to the specअगरied buffer.
 * Returns the dumped size in dwords.
 */
अटल u32 qed_dump_num_param(u32 *dump_buf,
			      bool dump, स्थिर अक्षर *param_name, u32 param_val)
अणु
	अक्षर *अक्षर_buf = (अक्षर *)dump_buf;
	u32 offset = 0;

	/* Dump param name */
	offset += qed_dump_str(अक्षर_buf + offset, dump, param_name);

	/* Indicate a numeric param value */
	अगर (dump)
		*(अक्षर_buf + offset) = 0;
	offset++;

	/* Align buffer to next dword */
	offset += qed_dump_align(अक्षर_buf + offset, dump, offset);

	/* Dump param value (and change offset from bytes to dwords) */
	offset = BYTES_TO_DWORDS(offset);
	अगर (dump)
		*(dump_buf + offset) = param_val;
	offset++;

	वापस offset;
पूर्ण

/* Reads the FW version and ग_लिखोs it as a param to the specअगरied buffer.
 * Returns the dumped size in dwords.
 */
अटल u32 qed_dump_fw_ver_param(काष्ठा qed_hwfn *p_hwfn,
				 काष्ठा qed_ptt *p_ptt,
				 u32 *dump_buf, bool dump)
अणु
	अक्षर fw_ver_str[16] = EMPTY_FW_VERSION_STR;
	अक्षर fw_img_str[16] = EMPTY_FW_IMAGE_STR;
	काष्ठा fw_info fw_info = अणु अणु0पूर्ण, अणु0पूर्ण पूर्ण;
	u32 offset = 0;

	अगर (dump && !qed_grc_get_param(p_hwfn, DBG_GRC_PARAM_NO_FW_VER)) अणु
		/* Read FW info from chip */
		qed_पढ़ो_fw_info(p_hwfn, p_ptt, &fw_info);

		/* Create FW version/image strings */
		अगर (snम_लिखो(fw_ver_str, माप(fw_ver_str),
			     "%d_%d_%d_%d", fw_info.ver.num.major,
			     fw_info.ver.num.minor, fw_info.ver.num.rev,
			     fw_info.ver.num.eng) < 0)
			DP_NOTICE(p_hwfn,
				  "Unexpected debug error: invalid FW version string\n");
		चयन (fw_info.ver.image_id) अणु
		हाल FW_IMG_MAIN:
			म_नकल(fw_img_str, "main");
			अवरोध;
		शेष:
			म_नकल(fw_img_str, "unknown");
			अवरोध;
		पूर्ण
	पूर्ण

	/* Dump FW version, image and बारtamp */
	offset += qed_dump_str_param(dump_buf + offset,
				     dump, "fw-version", fw_ver_str);
	offset += qed_dump_str_param(dump_buf + offset,
				     dump, "fw-image", fw_img_str);
	offset += qed_dump_num_param(dump_buf + offset, dump, "fw-timestamp",
				     le32_to_cpu(fw_info.ver.बारtamp));

	वापस offset;
पूर्ण

/* Reads the MFW version and ग_लिखोs it as a param to the specअगरied buffer.
 * Returns the dumped size in dwords.
 */
अटल u32 qed_dump_mfw_ver_param(काष्ठा qed_hwfn *p_hwfn,
				  काष्ठा qed_ptt *p_ptt,
				  u32 *dump_buf, bool dump)
अणु
	अक्षर mfw_ver_str[16] = EMPTY_FW_VERSION_STR;

	अगर (dump &&
	    !qed_grc_get_param(p_hwfn, DBG_GRC_PARAM_NO_FW_VER)) अणु
		u32 global_section_offsize, global_section_addr, mfw_ver;
		u32 खुला_data_addr, global_section_offsize_addr;

		/* Find MCP खुला data GRC address. Needs to be ORed with
		 * MCP_REG_SCRATCH due to a HW bug.
		 */
		खुला_data_addr = qed_rd(p_hwfn,
					  p_ptt,
					  MISC_REG_SHARED_MEM_ADDR) |
				   MCP_REG_SCRATCH;

		/* Find MCP खुला global section offset */
		global_section_offsize_addr = खुला_data_addr +
					      दुरत्व(काष्ठा mcp_खुला_data,
						       sections) +
					      माप(offमाप_प्रकार) * PUBLIC_GLOBAL;
		global_section_offsize = qed_rd(p_hwfn, p_ptt,
						global_section_offsize_addr);
		global_section_addr =
			MCP_REG_SCRATCH +
			(global_section_offsize & OFFSIZE_OFFSET_MASK) * 4;

		/* Read MFW version from MCP खुला global section */
		mfw_ver = qed_rd(p_hwfn, p_ptt,
				 global_section_addr +
				 दुरत्व(काष्ठा खुला_global, mfw_ver));

		/* Dump MFW version param */
		अगर (snम_लिखो(mfw_ver_str, माप(mfw_ver_str), "%d_%d_%d_%d",
			     (u8)(mfw_ver >> 24), (u8)(mfw_ver >> 16),
			     (u8)(mfw_ver >> 8), (u8)mfw_ver) < 0)
			DP_NOTICE(p_hwfn,
				  "Unexpected debug error: invalid MFW version string\n");
	पूर्ण

	वापस qed_dump_str_param(dump_buf, dump, "mfw-version", mfw_ver_str);
पूर्ण

/* Reads the chip revision from the chip and ग_लिखोs it as a param to the
 * specअगरied buffer. Returns the dumped size in dwords.
 */
अटल u32 qed_dump_chip_revision_param(काष्ठा qed_hwfn *p_hwfn,
					काष्ठा qed_ptt *p_ptt,
					u32 *dump_buf, bool dump)
अणु
	काष्ठा dbg_tools_data *dev_data = &p_hwfn->dbg_info;
	अक्षर param_str[3] = "??";

	अगर (dev_data->hw_type == HW_TYPE_ASIC) अणु
		u32 chip_rev, chip_metal;

		chip_rev = qed_rd(p_hwfn, p_ptt, MISCS_REG_CHIP_REV);
		chip_metal = qed_rd(p_hwfn, p_ptt, MISCS_REG_CHIP_METAL);

		param_str[0] = 'a' + (u8)chip_rev;
		param_str[1] = '0' + (u8)chip_metal;
	पूर्ण

	वापस qed_dump_str_param(dump_buf, dump, "chip-revision", param_str);
पूर्ण

/* Writes a section header to the specअगरied buffer.
 * Returns the dumped size in dwords.
 */
अटल u32 qed_dump_section_hdr(u32 *dump_buf,
				bool dump, स्थिर अक्षर *name, u32 num_params)
अणु
	वापस qed_dump_num_param(dump_buf, dump, name, num_params);
पूर्ण

/* Writes the common global params to the specअगरied buffer.
 * Returns the dumped size in dwords.
 */
अटल u32 qed_dump_common_global_params(काष्ठा qed_hwfn *p_hwfn,
					 काष्ठा qed_ptt *p_ptt,
					 u32 *dump_buf,
					 bool dump,
					 u8 num_specअगरic_global_params)
अणु
	काष्ठा dbg_tools_data *dev_data = &p_hwfn->dbg_info;
	u32 offset = 0;
	u8 num_params;

	/* Dump global params section header */
	num_params = NUM_COMMON_GLOBAL_PARAMS + num_specअगरic_global_params +
		(dev_data->chip_id == CHIP_BB ? 1 : 0);
	offset += qed_dump_section_hdr(dump_buf + offset,
				       dump, "global_params", num_params);

	/* Store params */
	offset += qed_dump_fw_ver_param(p_hwfn, p_ptt, dump_buf + offset, dump);
	offset += qed_dump_mfw_ver_param(p_hwfn,
					 p_ptt, dump_buf + offset, dump);
	offset += qed_dump_chip_revision_param(p_hwfn,
					       p_ptt, dump_buf + offset, dump);
	offset += qed_dump_num_param(dump_buf + offset,
				     dump, "tools-version", TOOLS_VERSION);
	offset += qed_dump_str_param(dump_buf + offset,
				     dump,
				     "chip",
				     s_chip_defs[dev_data->chip_id].name);
	offset += qed_dump_str_param(dump_buf + offset,
				     dump,
				     "platform",
				     s_hw_type_defs[dev_data->hw_type].name);
	offset += qed_dump_num_param(dump_buf + offset,
				     dump, "pci-func", p_hwfn->असल_pf_id);
	अगर (dev_data->chip_id == CHIP_BB)
		offset += qed_dump_num_param(dump_buf + offset,
					     dump, "path", QED_PATH_ID(p_hwfn));

	वापस offset;
पूर्ण

/* Writes the "last" section (including CRC) to the specअगरied buffer at the
 * given offset. Returns the dumped size in dwords.
 */
अटल u32 qed_dump_last_section(u32 *dump_buf, u32 offset, bool dump)
अणु
	u32 start_offset = offset;

	/* Dump CRC section header */
	offset += qed_dump_section_hdr(dump_buf + offset, dump, "last", 0);

	/* Calculate CRC32 and add it to the dword after the "last" section */
	अगर (dump)
		*(dump_buf + offset) = ~crc32(0xffffffff,
					      (u8 *)dump_buf,
					      DWORDS_TO_BYTES(offset));

	offset++;

	वापस offset - start_offset;
पूर्ण

/* Update blocks reset state  */
अटल व्योम qed_update_blocks_reset_state(काष्ठा qed_hwfn *p_hwfn,
					  काष्ठा qed_ptt *p_ptt)
अणु
	काष्ठा dbg_tools_data *dev_data = &p_hwfn->dbg_info;
	u32 reg_val[NUM_DBG_RESET_REGS] = अणु 0 पूर्ण;
	u8 rst_reg_id;
	u32 blk_id;

	/* Read reset रेजिस्टरs */
	क्रम (rst_reg_id = 0; rst_reg_id < NUM_DBG_RESET_REGS; rst_reg_id++) अणु
		स्थिर काष्ठा dbg_reset_reg *rst_reg;
		bool rst_reg_हटाओd;
		u32 rst_reg_addr;

		rst_reg = qed_get_dbg_reset_reg(p_hwfn, rst_reg_id);
		rst_reg_हटाओd = GET_FIELD(rst_reg->data,
					    DBG_RESET_REG_IS_REMOVED);
		rst_reg_addr = DWORDS_TO_BYTES(GET_FIELD(rst_reg->data,
							 DBG_RESET_REG_ADDR));

		अगर (!rst_reg_हटाओd)
			reg_val[rst_reg_id] = qed_rd(p_hwfn, p_ptt,
						     rst_reg_addr);
	पूर्ण

	/* Check अगर blocks are in reset */
	क्रम (blk_id = 0; blk_id < NUM_PHYS_BLOCKS; blk_id++) अणु
		स्थिर काष्ठा dbg_block_chip *blk;
		bool has_rst_reg;
		bool is_हटाओd;

		blk = qed_get_dbg_block_per_chip(p_hwfn, (क्रमागत block_id)blk_id);
		is_हटाओd = GET_FIELD(blk->flags, DBG_BLOCK_CHIP_IS_REMOVED);
		has_rst_reg = GET_FIELD(blk->flags,
					DBG_BLOCK_CHIP_HAS_RESET_REG);

		अगर (!is_हटाओd && has_rst_reg)
			dev_data->block_in_reset[blk_id] =
			    !(reg_val[blk->reset_reg_id] &
			      BIT(blk->reset_reg_bit_offset));
	पूर्ण
पूर्ण

/* is_mode_match recursive function */
अटल bool qed_is_mode_match_rec(काष्ठा qed_hwfn *p_hwfn,
				  u16 *modes_buf_offset, u8 rec_depth)
अणु
	काष्ठा dbg_tools_data *dev_data = &p_hwfn->dbg_info;
	u8 *dbg_array;
	bool arg1, arg2;
	u8 tree_val;

	अगर (rec_depth > MAX_RECURSION_DEPTH) अणु
		DP_NOTICE(p_hwfn,
			  "Unexpected error: is_mode_match_rec exceeded the max recursion depth. This is probably due to a corrupt init/debug buffer.\n");
		वापस false;
	पूर्ण

	/* Get next element from modes tree buffer */
	dbg_array = p_hwfn->dbg_arrays[BIN_BUF_DBG_MODE_TREE].ptr;
	tree_val = dbg_array[(*modes_buf_offset)++];

	चयन (tree_val) अणु
	हाल INIT_MODE_OP_NOT:
		वापस !qed_is_mode_match_rec(p_hwfn,
					      modes_buf_offset, rec_depth + 1);
	हाल INIT_MODE_OP_OR:
	हाल INIT_MODE_OP_AND:
		arg1 = qed_is_mode_match_rec(p_hwfn,
					     modes_buf_offset, rec_depth + 1);
		arg2 = qed_is_mode_match_rec(p_hwfn,
					     modes_buf_offset, rec_depth + 1);
		वापस (tree_val == INIT_MODE_OP_OR) ? (arg1 ||
							arg2) : (arg1 && arg2);
	शेष:
		वापस dev_data->mode_enable[tree_val - MAX_INIT_MODE_OPS] > 0;
	पूर्ण
पूर्ण

/* Returns true अगर the mode (specअगरied using modes_buf_offset) is enabled */
अटल bool qed_is_mode_match(काष्ठा qed_hwfn *p_hwfn, u16 *modes_buf_offset)
अणु
	वापस qed_is_mode_match_rec(p_hwfn, modes_buf_offset, 0);
पूर्ण

/* Enable / disable the Debug block */
अटल व्योम qed_bus_enable_dbg_block(काष्ठा qed_hwfn *p_hwfn,
				     काष्ठा qed_ptt *p_ptt, bool enable)
अणु
	qed_wr(p_hwfn, p_ptt, DBG_REG_DBG_BLOCK_ON, enable ? 1 : 0);
पूर्ण

/* Resets the Debug block */
अटल व्योम qed_bus_reset_dbg_block(काष्ठा qed_hwfn *p_hwfn,
				    काष्ठा qed_ptt *p_ptt)
अणु
	u32 reset_reg_addr, old_reset_reg_val, new_reset_reg_val;
	स्थिर काष्ठा dbg_reset_reg *reset_reg;
	स्थिर काष्ठा dbg_block_chip *block;

	block = qed_get_dbg_block_per_chip(p_hwfn, BLOCK_DBG);
	reset_reg = qed_get_dbg_reset_reg(p_hwfn, block->reset_reg_id);
	reset_reg_addr =
	    DWORDS_TO_BYTES(GET_FIELD(reset_reg->data, DBG_RESET_REG_ADDR));

	old_reset_reg_val = qed_rd(p_hwfn, p_ptt, reset_reg_addr);
	new_reset_reg_val =
	    old_reset_reg_val & ~BIT(block->reset_reg_bit_offset);

	qed_wr(p_hwfn, p_ptt, reset_reg_addr, new_reset_reg_val);
	qed_wr(p_hwfn, p_ptt, reset_reg_addr, old_reset_reg_val);
पूर्ण

/* Enable / disable Debug Bus clients according to the specअगरied mask
 * (1 = enable, 0 = disable).
 */
अटल व्योम qed_bus_enable_clients(काष्ठा qed_hwfn *p_hwfn,
				   काष्ठा qed_ptt *p_ptt, u32 client_mask)
अणु
	qed_wr(p_hwfn, p_ptt, DBG_REG_CLIENT_ENABLE, client_mask);
पूर्ण

अटल व्योम qed_bus_config_dbg_line(काष्ठा qed_hwfn *p_hwfn,
				    काष्ठा qed_ptt *p_ptt,
				    क्रमागत block_id block_id,
				    u8 line_id,
				    u8 enable_mask,
				    u8 right_shअगरt,
				    u8 क्रमce_valid_mask, u8 क्रमce_frame_mask)
अणु
	स्थिर काष्ठा dbg_block_chip *block =
		qed_get_dbg_block_per_chip(p_hwfn, block_id);

	qed_wr(p_hwfn, p_ptt, DWORDS_TO_BYTES(block->dbg_select_reg_addr),
	       line_id);
	qed_wr(p_hwfn, p_ptt, DWORDS_TO_BYTES(block->dbg_dword_enable_reg_addr),
	       enable_mask);
	qed_wr(p_hwfn, p_ptt, DWORDS_TO_BYTES(block->dbg_shअगरt_reg_addr),
	       right_shअगरt);
	qed_wr(p_hwfn, p_ptt, DWORDS_TO_BYTES(block->dbg_क्रमce_valid_reg_addr),
	       क्रमce_valid_mask);
	qed_wr(p_hwfn, p_ptt, DWORDS_TO_BYTES(block->dbg_क्रमce_frame_reg_addr),
	       क्रमce_frame_mask);
पूर्ण

/* Disable debug bus in all blocks */
अटल व्योम qed_bus_disable_blocks(काष्ठा qed_hwfn *p_hwfn,
				   काष्ठा qed_ptt *p_ptt)
अणु
	काष्ठा dbg_tools_data *dev_data = &p_hwfn->dbg_info;
	u32 block_id;

	/* Disable all blocks */
	क्रम (block_id = 0; block_id < MAX_BLOCK_ID; block_id++) अणु
		स्थिर काष्ठा dbg_block_chip *block_per_chip =
		    qed_get_dbg_block_per_chip(p_hwfn,
					       (क्रमागत block_id)block_id);

		अगर (GET_FIELD(block_per_chip->flags,
			      DBG_BLOCK_CHIP_IS_REMOVED) ||
		    dev_data->block_in_reset[block_id])
			जारी;

		/* Disable debug bus */
		अगर (GET_FIELD(block_per_chip->flags,
			      DBG_BLOCK_CHIP_HAS_DBG_BUS)) अणु
			u32 dbg_en_addr =
				block_per_chip->dbg_dword_enable_reg_addr;
			u16 modes_buf_offset =
			    GET_FIELD(block_per_chip->dbg_bus_mode.data,
				      DBG_MODE_HDR_MODES_BUF_OFFSET);
			bool eval_mode =
			    GET_FIELD(block_per_chip->dbg_bus_mode.data,
				      DBG_MODE_HDR_EVAL_MODE) > 0;

			अगर (!eval_mode ||
			    qed_is_mode_match(p_hwfn, &modes_buf_offset))
				qed_wr(p_hwfn, p_ptt,
				       DWORDS_TO_BYTES(dbg_en_addr),
				       0);
		पूर्ण
	पूर्ण
पूर्ण

/* Returns true अगर the specअगरied entity (indicated by GRC param) should be
 * included in the dump, false otherwise.
 */
अटल bool qed_grc_is_included(काष्ठा qed_hwfn *p_hwfn,
				क्रमागत dbg_grc_params grc_param)
अणु
	वापस qed_grc_get_param(p_hwfn, grc_param) > 0;
पूर्ण

/* Returns the storm_id that matches the specअगरied Storm letter,
 * or MAX_DBG_STORMS अगर invalid storm letter.
 */
अटल क्रमागत dbg_storms qed_get_id_from_letter(अक्षर storm_letter)
अणु
	u8 storm_id;

	क्रम (storm_id = 0; storm_id < MAX_DBG_STORMS; storm_id++)
		अगर (s_storm_defs[storm_id].letter == storm_letter)
			वापस (क्रमागत dbg_storms)storm_id;

	वापस MAX_DBG_STORMS;
पूर्ण

/* Returns true of the specअगरied Storm should be included in the dump, false
 * otherwise.
 */
अटल bool qed_grc_is_storm_included(काष्ठा qed_hwfn *p_hwfn,
				      क्रमागत dbg_storms storm)
अणु
	वापस qed_grc_get_param(p_hwfn, (क्रमागत dbg_grc_params)storm) > 0;
पूर्ण

/* Returns true अगर the specअगरied memory should be included in the dump, false
 * otherwise.
 */
अटल bool qed_grc_is_mem_included(काष्ठा qed_hwfn *p_hwfn,
				    क्रमागत block_id block_id, u8 mem_group_id)
अणु
	स्थिर काष्ठा dbg_block *block;
	u8 i;

	block = get_dbg_block(p_hwfn, block_id);

	/* If the block is associated with a Storm, check Storm match */
	अगर (block->associated_storm_letter) अणु
		क्रमागत dbg_storms associated_storm_id =
		    qed_get_id_from_letter(block->associated_storm_letter);

		अगर (associated_storm_id == MAX_DBG_STORMS ||
		    !qed_grc_is_storm_included(p_hwfn, associated_storm_id))
			वापस false;
	पूर्ण

	क्रम (i = 0; i < NUM_BIG_RAM_TYPES; i++) अणु
		काष्ठा big_ram_defs *big_ram = &s_big_ram_defs[i];

		अगर (mem_group_id == big_ram->mem_group_id ||
		    mem_group_id == big_ram->ram_mem_group_id)
			वापस qed_grc_is_included(p_hwfn, big_ram->grc_param);
	पूर्ण

	चयन (mem_group_id) अणु
	हाल MEM_GROUP_PXP_ILT:
	हाल MEM_GROUP_PXP_MEM:
		वापस qed_grc_is_included(p_hwfn, DBG_GRC_PARAM_DUMP_PXP);
	हाल MEM_GROUP_RAM:
		वापस qed_grc_is_included(p_hwfn, DBG_GRC_PARAM_DUMP_RAM);
	हाल MEM_GROUP_PBUF:
		वापस qed_grc_is_included(p_hwfn, DBG_GRC_PARAM_DUMP_PBUF);
	हाल MEM_GROUP_CAU_MEM:
	हाल MEM_GROUP_CAU_SB:
	हाल MEM_GROUP_CAU_PI:
		वापस qed_grc_is_included(p_hwfn, DBG_GRC_PARAM_DUMP_CAU);
	हाल MEM_GROUP_CAU_MEM_EXT:
		वापस qed_grc_is_included(p_hwfn, DBG_GRC_PARAM_DUMP_CAU_EXT);
	हाल MEM_GROUP_QM_MEM:
		वापस qed_grc_is_included(p_hwfn, DBG_GRC_PARAM_DUMP_QM);
	हाल MEM_GROUP_CFC_MEM:
	हाल MEM_GROUP_CONN_CFC_MEM:
	हाल MEM_GROUP_TASK_CFC_MEM:
		वापस qed_grc_is_included(p_hwfn, DBG_GRC_PARAM_DUMP_CFC) ||
		       qed_grc_is_included(p_hwfn, DBG_GRC_PARAM_DUMP_CM_CTX);
	हाल MEM_GROUP_DORQ_MEM:
		वापस qed_grc_is_included(p_hwfn, DBG_GRC_PARAM_DUMP_DORQ);
	हाल MEM_GROUP_IGU_MEM:
	हाल MEM_GROUP_IGU_MSIX:
		वापस qed_grc_is_included(p_hwfn, DBG_GRC_PARAM_DUMP_IGU);
	हाल MEM_GROUP_MULD_MEM:
		वापस qed_grc_is_included(p_hwfn, DBG_GRC_PARAM_DUMP_MULD);
	हाल MEM_GROUP_PRS_MEM:
		वापस qed_grc_is_included(p_hwfn, DBG_GRC_PARAM_DUMP_PRS);
	हाल MEM_GROUP_DMAE_MEM:
		वापस qed_grc_is_included(p_hwfn, DBG_GRC_PARAM_DUMP_DMAE);
	हाल MEM_GROUP_TM_MEM:
		वापस qed_grc_is_included(p_hwfn, DBG_GRC_PARAM_DUMP_TM);
	हाल MEM_GROUP_SDM_MEM:
		वापस qed_grc_is_included(p_hwfn, DBG_GRC_PARAM_DUMP_SDM);
	हाल MEM_GROUP_TDIF_CTX:
	हाल MEM_GROUP_RDIF_CTX:
		वापस qed_grc_is_included(p_hwfn, DBG_GRC_PARAM_DUMP_DIF);
	हाल MEM_GROUP_CM_MEM:
		वापस qed_grc_is_included(p_hwfn, DBG_GRC_PARAM_DUMP_CM);
	हाल MEM_GROUP_IOR:
		वापस qed_grc_is_included(p_hwfn, DBG_GRC_PARAM_DUMP_IOR);
	शेष:
		वापस true;
	पूर्ण
पूर्ण

/* Stalls all Storms */
अटल व्योम qed_grc_stall_storms(काष्ठा qed_hwfn *p_hwfn,
				 काष्ठा qed_ptt *p_ptt, bool stall)
अणु
	u32 reg_addr;
	u8 storm_id;

	क्रम (storm_id = 0; storm_id < MAX_DBG_STORMS; storm_id++) अणु
		अगर (!qed_grc_is_storm_included(p_hwfn,
					       (क्रमागत dbg_storms)storm_id))
			जारी;

		reg_addr = s_storm_defs[storm_id].sem_fast_mem_addr +
		    SEM_FAST_REG_STALL_0_BB_K2;
		qed_wr(p_hwfn, p_ptt, reg_addr, stall ? 1 : 0);
	पूर्ण

	msleep(STALL_DELAY_MS);
पूर्ण

/* Takes all blocks out of reset. If rbc_only is true, only RBC clients are
 * taken out of reset.
 */
अटल व्योम qed_grc_unreset_blocks(काष्ठा qed_hwfn *p_hwfn,
				   काष्ठा qed_ptt *p_ptt, bool rbc_only)
अणु
	काष्ठा dbg_tools_data *dev_data = &p_hwfn->dbg_info;
	u8 chip_id = dev_data->chip_id;
	u32 i;

	/* Take RBCs out of reset */
	क्रम (i = 0; i < ARRAY_SIZE(s_rbc_reset_defs); i++)
		अगर (s_rbc_reset_defs[i].reset_val[dev_data->chip_id])
			qed_wr(p_hwfn,
			       p_ptt,
			       s_rbc_reset_defs[i].reset_reg_addr +
			       RESET_REG_UNRESET_OFFSET,
			       s_rbc_reset_defs[i].reset_val[chip_id]);

	अगर (!rbc_only) अणु
		u32 reg_val[NUM_DBG_RESET_REGS] = अणु 0 पूर्ण;
		u8 reset_reg_id;
		u32 block_id;

		/* Fill reset regs values */
		क्रम (block_id = 0; block_id < NUM_PHYS_BLOCKS; block_id++) अणु
			bool is_हटाओd, has_reset_reg, unreset_beक्रमe_dump;
			स्थिर काष्ठा dbg_block_chip *block;

			block = qed_get_dbg_block_per_chip(p_hwfn,
							   (क्रमागत block_id)
							   block_id);
			is_हटाओd =
			    GET_FIELD(block->flags, DBG_BLOCK_CHIP_IS_REMOVED);
			has_reset_reg =
			    GET_FIELD(block->flags,
				      DBG_BLOCK_CHIP_HAS_RESET_REG);
			unreset_beक्रमe_dump =
			    GET_FIELD(block->flags,
				      DBG_BLOCK_CHIP_UNRESET_BEFORE_DUMP);

			अगर (!is_हटाओd && has_reset_reg && unreset_beक्रमe_dump)
				reg_val[block->reset_reg_id] |=
				    BIT(block->reset_reg_bit_offset);
		पूर्ण

		/* Write reset रेजिस्टरs */
		क्रम (reset_reg_id = 0; reset_reg_id < NUM_DBG_RESET_REGS;
		     reset_reg_id++) अणु
			स्थिर काष्ठा dbg_reset_reg *reset_reg;
			u32 reset_reg_addr;

			reset_reg = qed_get_dbg_reset_reg(p_hwfn, reset_reg_id);

			अगर (GET_FIELD
			    (reset_reg->data, DBG_RESET_REG_IS_REMOVED))
				जारी;

			अगर (reg_val[reset_reg_id]) अणु
				reset_reg_addr =
				    GET_FIELD(reset_reg->data,
					      DBG_RESET_REG_ADDR);
				qed_wr(p_hwfn,
				       p_ptt,
				       DWORDS_TO_BYTES(reset_reg_addr) +
				       RESET_REG_UNRESET_OFFSET,
				       reg_val[reset_reg_id]);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

/* Returns the attention block data of the specअगरied block */
अटल स्थिर काष्ठा dbg_attn_block_type_data *
qed_get_block_attn_data(काष्ठा qed_hwfn *p_hwfn,
			क्रमागत block_id block_id, क्रमागत dbg_attn_type attn_type)
अणु
	स्थिर काष्ठा dbg_attn_block *base_attn_block_arr =
	    (स्थिर काष्ठा dbg_attn_block *)
	    p_hwfn->dbg_arrays[BIN_BUF_DBG_ATTN_BLOCKS].ptr;

	वापस &base_attn_block_arr[block_id].per_type_data[attn_type];
पूर्ण

/* Returns the attention रेजिस्टरs of the specअगरied block */
अटल स्थिर काष्ठा dbg_attn_reg *
qed_get_block_attn_regs(काष्ठा qed_hwfn *p_hwfn,
			क्रमागत block_id block_id, क्रमागत dbg_attn_type attn_type,
			u8 *num_attn_regs)
अणु
	स्थिर काष्ठा dbg_attn_block_type_data *block_type_data =
	    qed_get_block_attn_data(p_hwfn, block_id, attn_type);

	*num_attn_regs = block_type_data->num_regs;

	वापस (स्थिर काष्ठा dbg_attn_reg *)
		p_hwfn->dbg_arrays[BIN_BUF_DBG_ATTN_REGS].ptr +
		block_type_data->regs_offset;
पूर्ण

/* For each block, clear the status of all parities */
अटल व्योम qed_grc_clear_all_prty(काष्ठा qed_hwfn *p_hwfn,
				   काष्ठा qed_ptt *p_ptt)
अणु
	काष्ठा dbg_tools_data *dev_data = &p_hwfn->dbg_info;
	स्थिर काष्ठा dbg_attn_reg *attn_reg_arr;
	u8 reg_idx, num_attn_regs;
	u32 block_id;

	क्रम (block_id = 0; block_id < NUM_PHYS_BLOCKS; block_id++) अणु
		अगर (dev_data->block_in_reset[block_id])
			जारी;

		attn_reg_arr = qed_get_block_attn_regs(p_hwfn,
						       (क्रमागत block_id)block_id,
						       ATTN_TYPE_PARITY,
						       &num_attn_regs);

		क्रम (reg_idx = 0; reg_idx < num_attn_regs; reg_idx++) अणु
			स्थिर काष्ठा dbg_attn_reg *reg_data =
				&attn_reg_arr[reg_idx];
			u16 modes_buf_offset;
			bool eval_mode;

			/* Check mode */
			eval_mode = GET_FIELD(reg_data->mode.data,
					      DBG_MODE_HDR_EVAL_MODE) > 0;
			modes_buf_offset =
				GET_FIELD(reg_data->mode.data,
					  DBG_MODE_HDR_MODES_BUF_OFFSET);

			/* If Mode match: clear parity status */
			अगर (!eval_mode ||
			    qed_is_mode_match(p_hwfn, &modes_buf_offset))
				qed_rd(p_hwfn, p_ptt,
				       DWORDS_TO_BYTES(reg_data->
						       sts_clr_address));
		पूर्ण
	पूर्ण
पूर्ण

/* Dumps GRC रेजिस्टरs section header. Returns the dumped size in dwords.
 * the following parameters are dumped:
 * - count: no. of dumped entries
 * - split_type: split type
 * - split_id: split ID (dumped only अगर split_id != SPLIT_TYPE_NONE)
 * - reg_type_name: रेजिस्टर type name (dumped only अगर reg_type_name != शून्य)
 */
अटल u32 qed_grc_dump_regs_hdr(u32 *dump_buf,
				 bool dump,
				 u32 num_reg_entries,
				 क्रमागत init_split_types split_type,
				 u8 split_id, स्थिर अक्षर *reg_type_name)
अणु
	u8 num_params = 2 +
	    (split_type != SPLIT_TYPE_NONE ? 1 : 0) + (reg_type_name ? 1 : 0);
	u32 offset = 0;

	offset += qed_dump_section_hdr(dump_buf + offset,
				       dump, "grc_regs", num_params);
	offset += qed_dump_num_param(dump_buf + offset,
				     dump, "count", num_reg_entries);
	offset += qed_dump_str_param(dump_buf + offset,
				     dump, "split",
				     s_split_type_defs[split_type].name);
	अगर (split_type != SPLIT_TYPE_NONE)
		offset += qed_dump_num_param(dump_buf + offset,
					     dump, "id", split_id);
	अगर (reg_type_name)
		offset += qed_dump_str_param(dump_buf + offset,
					     dump, "type", reg_type_name);

	वापस offset;
पूर्ण

/* Reads the specअगरied रेजिस्टरs पूर्णांकo the specअगरied buffer.
 * The addr and len arguments are specअगरied in dwords.
 */
व्योम qed_पढ़ो_regs(काष्ठा qed_hwfn *p_hwfn,
		   काष्ठा qed_ptt *p_ptt, u32 *buf, u32 addr, u32 len)
अणु
	u32 i;

	क्रम (i = 0; i < len; i++)
		buf[i] = qed_rd(p_hwfn, p_ptt, DWORDS_TO_BYTES(addr + i));
पूर्ण

/* Dumps the GRC रेजिस्टरs in the specअगरied address range.
 * Returns the dumped size in dwords.
 * The addr and len arguments are specअगरied in dwords.
 */
अटल u32 qed_grc_dump_addr_range(काष्ठा qed_hwfn *p_hwfn,
				   काष्ठा qed_ptt *p_ptt,
				   u32 *dump_buf,
				   bool dump, u32 addr, u32 len, bool wide_bus,
				   क्रमागत init_split_types split_type,
				   u8 split_id)
अणु
	काष्ठा dbg_tools_data *dev_data = &p_hwfn->dbg_info;
	u8 port_id = 0, pf_id = 0, vf_id = 0, fid = 0;
	bool पढ़ो_using_dmae = false;
	u32 thresh;

	अगर (!dump)
		वापस len;

	चयन (split_type) अणु
	हाल SPLIT_TYPE_PORT:
		port_id = split_id;
		अवरोध;
	हाल SPLIT_TYPE_PF:
		pf_id = split_id;
		अवरोध;
	हाल SPLIT_TYPE_PORT_PF:
		port_id = split_id / dev_data->num_pfs_per_port;
		pf_id = port_id + dev_data->num_ports *
		    (split_id % dev_data->num_pfs_per_port);
		अवरोध;
	हाल SPLIT_TYPE_VF:
		vf_id = split_id;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	/* Try पढ़ोing using DMAE */
	अगर (dev_data->use_dmae && split_type != SPLIT_TYPE_VF &&
	    (len >= s_hw_type_defs[dev_data->hw_type].dmae_thresh ||
	     (PROTECT_WIDE_BUS && wide_bus))) अणु
		काष्ठा qed_dmae_params dmae_params;

		/* Set DMAE params */
		स_रखो(&dmae_params, 0, माप(dmae_params));
		SET_FIELD(dmae_params.flags, QED_DMAE_PARAMS_COMPLETION_DST, 1);
		चयन (split_type) अणु
		हाल SPLIT_TYPE_PORT:
			SET_FIELD(dmae_params.flags, QED_DMAE_PARAMS_PORT_VALID,
				  1);
			dmae_params.port_id = port_id;
			अवरोध;
		हाल SPLIT_TYPE_PF:
			SET_FIELD(dmae_params.flags,
				  QED_DMAE_PARAMS_SRC_PF_VALID, 1);
			dmae_params.src_pfid = pf_id;
			अवरोध;
		हाल SPLIT_TYPE_PORT_PF:
			SET_FIELD(dmae_params.flags, QED_DMAE_PARAMS_PORT_VALID,
				  1);
			SET_FIELD(dmae_params.flags,
				  QED_DMAE_PARAMS_SRC_PF_VALID, 1);
			dmae_params.port_id = port_id;
			dmae_params.src_pfid = pf_id;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण

		/* Execute DMAE command */
		पढ़ो_using_dmae = !qed_dmae_grc2host(p_hwfn,
						     p_ptt,
						     DWORDS_TO_BYTES(addr),
						     (u64)(uपूर्णांकptr_t)(dump_buf),
						     len, &dmae_params);
		अगर (!पढ़ो_using_dmae) अणु
			dev_data->use_dmae = 0;
			DP_VERBOSE(p_hwfn,
				   QED_MSG_DEBUG,
				   "Failed reading from chip using DMAE, using GRC instead\n");
		पूर्ण
	पूर्ण

	अगर (पढ़ो_using_dmae)
		जाओ prपूर्णांक_log;

	/* If not पढ़ो using DMAE, पढ़ो using GRC */

	/* Set pretend */
	अगर (split_type != dev_data->pretend.split_type ||
	    split_id != dev_data->pretend.split_id) अणु
		चयन (split_type) अणु
		हाल SPLIT_TYPE_PORT:
			qed_port_pretend(p_hwfn, p_ptt, port_id);
			अवरोध;
		हाल SPLIT_TYPE_PF:
			fid = FIELD_VALUE(PXP_PRETEND_CONCRETE_FID_PFID,
					  pf_id);
			qed_fid_pretend(p_hwfn, p_ptt, fid);
			अवरोध;
		हाल SPLIT_TYPE_PORT_PF:
			fid = FIELD_VALUE(PXP_PRETEND_CONCRETE_FID_PFID,
					  pf_id);
			qed_port_fid_pretend(p_hwfn, p_ptt, port_id, fid);
			अवरोध;
		हाल SPLIT_TYPE_VF:
			fid = FIELD_VALUE(PXP_PRETEND_CONCRETE_FID_VFVALID, 1)
			      | FIELD_VALUE(PXP_PRETEND_CONCRETE_FID_VFID,
					  vf_id);
			qed_fid_pretend(p_hwfn, p_ptt, fid);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण

		dev_data->pretend.split_type = (u8)split_type;
		dev_data->pretend.split_id = split_id;
	पूर्ण

	/* Read रेजिस्टरs using GRC */
	qed_पढ़ो_regs(p_hwfn, p_ptt, dump_buf, addr, len);

prपूर्णांक_log:
	/* Prपूर्णांक log */
	dev_data->num_regs_पढ़ो += len;
	thresh = s_hw_type_defs[dev_data->hw_type].log_thresh;
	अगर ((dev_data->num_regs_पढ़ो / thresh) >
	    ((dev_data->num_regs_पढ़ो - len) / thresh))
		DP_VERBOSE(p_hwfn,
			   QED_MSG_DEBUG,
			   "Dumped %d registers...\n", dev_data->num_regs_पढ़ो);

	वापस len;
पूर्ण

/* Dumps GRC रेजिस्टरs sequence header. Returns the dumped size in dwords.
 * The addr and len arguments are specअगरied in dwords.
 */
अटल u32 qed_grc_dump_reg_entry_hdr(u32 *dump_buf,
				      bool dump, u32 addr, u32 len)
अणु
	अगर (dump)
		*dump_buf = addr | (len << REG_DUMP_LEN_SHIFT);

	वापस 1;
पूर्ण

/* Dumps GRC रेजिस्टरs sequence. Returns the dumped size in dwords.
 * The addr and len arguments are specअगरied in dwords.
 */
अटल u32 qed_grc_dump_reg_entry(काष्ठा qed_hwfn *p_hwfn,
				  काष्ठा qed_ptt *p_ptt,
				  u32 *dump_buf,
				  bool dump, u32 addr, u32 len, bool wide_bus,
				  क्रमागत init_split_types split_type, u8 split_id)
अणु
	u32 offset = 0;

	offset += qed_grc_dump_reg_entry_hdr(dump_buf, dump, addr, len);
	offset += qed_grc_dump_addr_range(p_hwfn,
					  p_ptt,
					  dump_buf + offset,
					  dump, addr, len, wide_bus,
					  split_type, split_id);

	वापस offset;
पूर्ण

/* Dumps GRC रेजिस्टरs sequence with skip cycle.
 * Returns the dumped size in dwords.
 * - addr:	start GRC address in dwords
 * - total_len:	total no. of dwords to dump
 * - पढ़ो_len:	no. consecutive dwords to पढ़ो
 * - skip_len:	no. of dwords to skip (and fill with zeros)
 */
अटल u32 qed_grc_dump_reg_entry_skip(काष्ठा qed_hwfn *p_hwfn,
				       काष्ठा qed_ptt *p_ptt,
				       u32 *dump_buf,
				       bool dump,
				       u32 addr,
				       u32 total_len,
				       u32 पढ़ो_len, u32 skip_len)
अणु
	u32 offset = 0, reg_offset = 0;

	offset += qed_grc_dump_reg_entry_hdr(dump_buf, dump, addr, total_len);

	अगर (!dump)
		वापस offset + total_len;

	जबतक (reg_offset < total_len) अणु
		u32 curr_len = min_t(u32, पढ़ो_len, total_len - reg_offset);

		offset += qed_grc_dump_addr_range(p_hwfn,
						  p_ptt,
						  dump_buf + offset,
						  dump,  addr, curr_len, false,
						  SPLIT_TYPE_NONE, 0);
		reg_offset += curr_len;
		addr += curr_len;

		अगर (reg_offset < total_len) अणु
			curr_len = min_t(u32, skip_len, total_len - skip_len);
			स_रखो(dump_buf + offset, 0, DWORDS_TO_BYTES(curr_len));
			offset += curr_len;
			reg_offset += curr_len;
			addr += curr_len;
		पूर्ण
	पूर्ण

	वापस offset;
पूर्ण

/* Dumps GRC रेजिस्टरs entries. Returns the dumped size in dwords. */
अटल u32 qed_grc_dump_regs_entries(काष्ठा qed_hwfn *p_hwfn,
				     काष्ठा qed_ptt *p_ptt,
				     काष्ठा virt_mem_desc input_regs_arr,
				     u32 *dump_buf,
				     bool dump,
				     क्रमागत init_split_types split_type,
				     u8 split_id,
				     bool block_enable[MAX_BLOCK_ID],
				     u32 *num_dumped_reg_entries)
अणु
	u32 i, offset = 0, input_offset = 0;
	bool mode_match = true;

	*num_dumped_reg_entries = 0;

	जबतक (input_offset < BYTES_TO_DWORDS(input_regs_arr.size)) अणु
		स्थिर काष्ठा dbg_dump_cond_hdr *cond_hdr =
		    (स्थिर काष्ठा dbg_dump_cond_hdr *)
		    input_regs_arr.ptr + input_offset++;
		u16 modes_buf_offset;
		bool eval_mode;

		/* Check mode/block */
		eval_mode = GET_FIELD(cond_hdr->mode.data,
				      DBG_MODE_HDR_EVAL_MODE) > 0;
		अगर (eval_mode) अणु
			modes_buf_offset =
				GET_FIELD(cond_hdr->mode.data,
					  DBG_MODE_HDR_MODES_BUF_OFFSET);
			mode_match = qed_is_mode_match(p_hwfn,
						       &modes_buf_offset);
		पूर्ण

		अगर (!mode_match || !block_enable[cond_hdr->block_id]) अणु
			input_offset += cond_hdr->data_size;
			जारी;
		पूर्ण

		क्रम (i = 0; i < cond_hdr->data_size; i++, input_offset++) अणु
			स्थिर काष्ठा dbg_dump_reg *reg =
			    (स्थिर काष्ठा dbg_dump_reg *)
			    input_regs_arr.ptr + input_offset;
			u32 addr, len;
			bool wide_bus;

			addr = GET_FIELD(reg->data, DBG_DUMP_REG_ADDRESS);
			len = GET_FIELD(reg->data, DBG_DUMP_REG_LENGTH);
			wide_bus = GET_FIELD(reg->data, DBG_DUMP_REG_WIDE_BUS);
			offset += qed_grc_dump_reg_entry(p_hwfn,
							 p_ptt,
							 dump_buf + offset,
							 dump,
							 addr,
							 len,
							 wide_bus,
							 split_type, split_id);
			(*num_dumped_reg_entries)++;
		पूर्ण
	पूर्ण

	वापस offset;
पूर्ण

/* Dumps GRC रेजिस्टरs entries. Returns the dumped size in dwords. */
अटल u32 qed_grc_dump_split_data(काष्ठा qed_hwfn *p_hwfn,
				   काष्ठा qed_ptt *p_ptt,
				   काष्ठा virt_mem_desc input_regs_arr,
				   u32 *dump_buf,
				   bool dump,
				   bool block_enable[MAX_BLOCK_ID],
				   क्रमागत init_split_types split_type,
				   u8 split_id, स्थिर अक्षर *reg_type_name)
अणु
	काष्ठा dbg_tools_data *dev_data = &p_hwfn->dbg_info;
	क्रमागत init_split_types hdr_split_type = split_type;
	u32 num_dumped_reg_entries, offset;
	u8 hdr_split_id = split_id;

	/* In PORT_PF split type, prपूर्णांक a port split header */
	अगर (split_type == SPLIT_TYPE_PORT_PF) अणु
		hdr_split_type = SPLIT_TYPE_PORT;
		hdr_split_id = split_id / dev_data->num_pfs_per_port;
	पूर्ण

	/* Calculate रेजिस्टर dump header size (and skip it क्रम now) */
	offset = qed_grc_dump_regs_hdr(dump_buf,
				       false,
				       0,
				       hdr_split_type,
				       hdr_split_id, reg_type_name);

	/* Dump रेजिस्टरs */
	offset += qed_grc_dump_regs_entries(p_hwfn,
					    p_ptt,
					    input_regs_arr,
					    dump_buf + offset,
					    dump,
					    split_type,
					    split_id,
					    block_enable,
					    &num_dumped_reg_entries);

	/* Write रेजिस्टर dump header */
	अगर (dump && num_dumped_reg_entries > 0)
		qed_grc_dump_regs_hdr(dump_buf,
				      dump,
				      num_dumped_reg_entries,
				      hdr_split_type,
				      hdr_split_id, reg_type_name);

	वापस num_dumped_reg_entries > 0 ? offset : 0;
पूर्ण

/* Dumps रेजिस्टरs according to the input रेजिस्टरs array. Returns the dumped
 * size in dwords.
 */
अटल u32 qed_grc_dump_रेजिस्टरs(काष्ठा qed_hwfn *p_hwfn,
				  काष्ठा qed_ptt *p_ptt,
				  u32 *dump_buf,
				  bool dump,
				  bool block_enable[MAX_BLOCK_ID],
				  स्थिर अक्षर *reg_type_name)
अणु
	काष्ठा virt_mem_desc *dbg_buf =
	    &p_hwfn->dbg_arrays[BIN_BUF_DBG_DUMP_REG];
	काष्ठा dbg_tools_data *dev_data = &p_hwfn->dbg_info;
	u32 offset = 0, input_offset = 0;

	जबतक (input_offset < BYTES_TO_DWORDS(dbg_buf->size)) अणु
		स्थिर काष्ठा dbg_dump_split_hdr *split_hdr;
		काष्ठा virt_mem_desc curr_input_regs_arr;
		क्रमागत init_split_types split_type;
		u16 split_count = 0;
		u32 split_data_size;
		u8 split_id;

		split_hdr =
		    (स्थिर काष्ठा dbg_dump_split_hdr *)
		    dbg_buf->ptr + input_offset++;
		split_type =
		    GET_FIELD(split_hdr->hdr,
			      DBG_DUMP_SPLIT_HDR_SPLIT_TYPE_ID);
		split_data_size = GET_FIELD(split_hdr->hdr,
					    DBG_DUMP_SPLIT_HDR_DATA_SIZE);
		curr_input_regs_arr.ptr =
		    (u32 *)p_hwfn->dbg_arrays[BIN_BUF_DBG_DUMP_REG].ptr +
		    input_offset;
		curr_input_regs_arr.size = DWORDS_TO_BYTES(split_data_size);

		चयन (split_type) अणु
		हाल SPLIT_TYPE_NONE:
			split_count = 1;
			अवरोध;
		हाल SPLIT_TYPE_PORT:
			split_count = dev_data->num_ports;
			अवरोध;
		हाल SPLIT_TYPE_PF:
		हाल SPLIT_TYPE_PORT_PF:
			split_count = dev_data->num_ports *
			    dev_data->num_pfs_per_port;
			अवरोध;
		हाल SPLIT_TYPE_VF:
			split_count = dev_data->num_vfs;
			अवरोध;
		शेष:
			वापस 0;
		पूर्ण

		क्रम (split_id = 0; split_id < split_count; split_id++)
			offset += qed_grc_dump_split_data(p_hwfn, p_ptt,
							  curr_input_regs_arr,
							  dump_buf + offset,
							  dump, block_enable,
							  split_type,
							  split_id,
							  reg_type_name);

		input_offset += split_data_size;
	पूर्ण

	/* Cancel pretends (pretend to original PF) */
	अगर (dump) अणु
		qed_fid_pretend(p_hwfn, p_ptt,
				FIELD_VALUE(PXP_PRETEND_CONCRETE_FID_PFID,
					    p_hwfn->rel_pf_id));
		dev_data->pretend.split_type = SPLIT_TYPE_NONE;
		dev_data->pretend.split_id = 0;
	पूर्ण

	वापस offset;
पूर्ण

/* Dump reset रेजिस्टरs. Returns the dumped size in dwords. */
अटल u32 qed_grc_dump_reset_regs(काष्ठा qed_hwfn *p_hwfn,
				   काष्ठा qed_ptt *p_ptt,
				   u32 *dump_buf, bool dump)
अणु
	u32 offset = 0, num_regs = 0;
	u8 reset_reg_id;

	/* Calculate header size */
	offset += qed_grc_dump_regs_hdr(dump_buf,
					false,
					0, SPLIT_TYPE_NONE, 0, "RESET_REGS");

	/* Write reset रेजिस्टरs */
	क्रम (reset_reg_id = 0; reset_reg_id < NUM_DBG_RESET_REGS;
	     reset_reg_id++) अणु
		स्थिर काष्ठा dbg_reset_reg *reset_reg;
		u32 reset_reg_addr;

		reset_reg = qed_get_dbg_reset_reg(p_hwfn, reset_reg_id);

		अगर (GET_FIELD(reset_reg->data, DBG_RESET_REG_IS_REMOVED))
			जारी;

		reset_reg_addr = GET_FIELD(reset_reg->data, DBG_RESET_REG_ADDR);
		offset += qed_grc_dump_reg_entry(p_hwfn,
						 p_ptt,
						 dump_buf + offset,
						 dump,
						 reset_reg_addr,
						 1, false, SPLIT_TYPE_NONE, 0);
		num_regs++;
	पूर्ण

	/* Write header */
	अगर (dump)
		qed_grc_dump_regs_hdr(dump_buf,
				      true, num_regs, SPLIT_TYPE_NONE,
				      0, "RESET_REGS");

	वापस offset;
पूर्ण

/* Dump रेजिस्टरs that are modअगरied during GRC Dump and thereक्रमe must be
 * dumped first. Returns the dumped size in dwords.
 */
अटल u32 qed_grc_dump_modअगरied_regs(काष्ठा qed_hwfn *p_hwfn,
				      काष्ठा qed_ptt *p_ptt,
				      u32 *dump_buf, bool dump)
अणु
	काष्ठा dbg_tools_data *dev_data = &p_hwfn->dbg_info;
	u32 block_id, offset = 0, stall_regs_offset;
	स्थिर काष्ठा dbg_attn_reg *attn_reg_arr;
	u8 storm_id, reg_idx, num_attn_regs;
	u32 num_reg_entries = 0;

	/* Write empty header क्रम attention रेजिस्टरs */
	offset += qed_grc_dump_regs_hdr(dump_buf,
					false,
					0, SPLIT_TYPE_NONE, 0, "ATTN_REGS");

	/* Write parity रेजिस्टरs */
	क्रम (block_id = 0; block_id < NUM_PHYS_BLOCKS; block_id++) अणु
		अगर (dev_data->block_in_reset[block_id] && dump)
			जारी;

		attn_reg_arr = qed_get_block_attn_regs(p_hwfn,
						       (क्रमागत block_id)block_id,
						       ATTN_TYPE_PARITY,
						       &num_attn_regs);

		क्रम (reg_idx = 0; reg_idx < num_attn_regs; reg_idx++) अणु
			स्थिर काष्ठा dbg_attn_reg *reg_data =
				&attn_reg_arr[reg_idx];
			u16 modes_buf_offset;
			bool eval_mode;
			u32 addr;

			/* Check mode */
			eval_mode = GET_FIELD(reg_data->mode.data,
					      DBG_MODE_HDR_EVAL_MODE) > 0;
			modes_buf_offset =
				GET_FIELD(reg_data->mode.data,
					  DBG_MODE_HDR_MODES_BUF_OFFSET);
			अगर (eval_mode &&
			    !qed_is_mode_match(p_hwfn, &modes_buf_offset))
				जारी;

			/* Mode match: पढ़ो & dump रेजिस्टरs */
			addr = reg_data->mask_address;
			offset += qed_grc_dump_reg_entry(p_hwfn,
							 p_ptt,
							 dump_buf + offset,
							 dump,
							 addr,
							 1, false,
							 SPLIT_TYPE_NONE, 0);
			addr = GET_FIELD(reg_data->data,
					 DBG_ATTN_REG_STS_ADDRESS);
			offset += qed_grc_dump_reg_entry(p_hwfn,
							 p_ptt,
							 dump_buf + offset,
							 dump,
							 addr,
							 1, false,
							 SPLIT_TYPE_NONE, 0);
			num_reg_entries += 2;
		पूर्ण
	पूर्ण

	/* Overग_लिखो header क्रम attention रेजिस्टरs */
	अगर (dump)
		qed_grc_dump_regs_hdr(dump_buf,
				      true,
				      num_reg_entries,
				      SPLIT_TYPE_NONE, 0, "ATTN_REGS");

	/* Write empty header क्रम stall रेजिस्टरs */
	stall_regs_offset = offset;
	offset += qed_grc_dump_regs_hdr(dump_buf,
					false, 0, SPLIT_TYPE_NONE, 0, "REGS");

	/* Write Storm stall status रेजिस्टरs */
	क्रम (storm_id = 0, num_reg_entries = 0; storm_id < MAX_DBG_STORMS;
	     storm_id++) अणु
		काष्ठा storm_defs *storm = &s_storm_defs[storm_id];
		u32 addr;

		अगर (dev_data->block_in_reset[storm->sem_block_id] && dump)
			जारी;

		addr =
		    BYTES_TO_DWORDS(storm->sem_fast_mem_addr +
				    SEM_FAST_REG_STALLED);
		offset += qed_grc_dump_reg_entry(p_hwfn,
						 p_ptt,
						 dump_buf + offset,
						 dump,
						 addr,
						 1,
						 false, SPLIT_TYPE_NONE, 0);
		num_reg_entries++;
	पूर्ण

	/* Overग_लिखो header क्रम stall रेजिस्टरs */
	अगर (dump)
		qed_grc_dump_regs_hdr(dump_buf + stall_regs_offset,
				      true,
				      num_reg_entries,
				      SPLIT_TYPE_NONE, 0, "REGS");

	वापस offset;
पूर्ण

/* Dumps रेजिस्टरs that can't be represented in the debug arrays */
अटल u32 qed_grc_dump_special_regs(काष्ठा qed_hwfn *p_hwfn,
				     काष्ठा qed_ptt *p_ptt,
				     u32 *dump_buf, bool dump)
अणु
	u32 offset = 0, addr;

	offset += qed_grc_dump_regs_hdr(dump_buf,
					dump, 2, SPLIT_TYPE_NONE, 0, "REGS");

	/* Dump R/TDIF_REG_DEBUG_ERROR_INFO_SIZE (every 8'th रेजिस्टर should be
	 * skipped).
	 */
	addr = BYTES_TO_DWORDS(RDIF_REG_DEBUG_ERROR_INFO);
	offset += qed_grc_dump_reg_entry_skip(p_hwfn,
					      p_ptt,
					      dump_buf + offset,
					      dump,
					      addr,
					      RDIF_REG_DEBUG_ERROR_INFO_SIZE,
					      7,
					      1);
	addr = BYTES_TO_DWORDS(TDIF_REG_DEBUG_ERROR_INFO);
	offset +=
	    qed_grc_dump_reg_entry_skip(p_hwfn,
					p_ptt,
					dump_buf + offset,
					dump,
					addr,
					TDIF_REG_DEBUG_ERROR_INFO_SIZE,
					7,
					1);

	वापस offset;
पूर्ण

/* Dumps a GRC memory header (section and params). Returns the dumped size in
 * dwords. The following parameters are dumped:
 * - name:	   dumped only अगर it's not शून्य.
 * - addr:	   in dwords, dumped only अगर name is शून्य.
 * - len:	   in dwords, always dumped.
 * - width:	   dumped अगर it's not zero.
 * - packed:	   dumped only अगर it's not false.
 * - mem_group:	   always dumped.
 * - is_storm:	   true only अगर the memory is related to a Storm.
 * - storm_letter: valid only अगर is_storm is true.
 *
 */
अटल u32 qed_grc_dump_mem_hdr(काष्ठा qed_hwfn *p_hwfn,
				u32 *dump_buf,
				bool dump,
				स्थिर अक्षर *name,
				u32 addr,
				u32 len,
				u32 bit_width,
				bool packed,
				स्थिर अक्षर *mem_group, अक्षर storm_letter)
अणु
	u8 num_params = 3;
	u32 offset = 0;
	अक्षर buf[64];

	अगर (!len)
		DP_NOTICE(p_hwfn,
			  "Unexpected GRC Dump error: dumped memory size must be non-zero\n");

	अगर (bit_width)
		num_params++;
	अगर (packed)
		num_params++;

	/* Dump section header */
	offset += qed_dump_section_hdr(dump_buf + offset,
				       dump, "grc_mem", num_params);

	अगर (name) अणु
		/* Dump name */
		अगर (storm_letter) अणु
			म_नकल(buf, "?STORM_");
			buf[0] = storm_letter;
			म_नकल(buf + म_माप(buf), name);
		पूर्ण अन्यथा अणु
			म_नकल(buf, name);
		पूर्ण

		offset += qed_dump_str_param(dump_buf + offset,
					     dump, "name", buf);
	पूर्ण अन्यथा अणु
		/* Dump address */
		u32 addr_in_bytes = DWORDS_TO_BYTES(addr);

		offset += qed_dump_num_param(dump_buf + offset,
					     dump, "addr", addr_in_bytes);
	पूर्ण

	/* Dump len */
	offset += qed_dump_num_param(dump_buf + offset, dump, "len", len);

	/* Dump bit width */
	अगर (bit_width)
		offset += qed_dump_num_param(dump_buf + offset,
					     dump, "width", bit_width);

	/* Dump packed */
	अगर (packed)
		offset += qed_dump_num_param(dump_buf + offset,
					     dump, "packed", 1);

	/* Dump reg type */
	अगर (storm_letter) अणु
		म_नकल(buf, "?STORM_");
		buf[0] = storm_letter;
		म_नकल(buf + म_माप(buf), mem_group);
	पूर्ण अन्यथा अणु
		म_नकल(buf, mem_group);
	पूर्ण

	offset += qed_dump_str_param(dump_buf + offset, dump, "type", buf);

	वापस offset;
पूर्ण

/* Dumps a single GRC memory. If name is शून्य, the memory is stored by address.
 * Returns the dumped size in dwords.
 * The addr and len arguments are specअगरied in dwords.
 */
अटल u32 qed_grc_dump_mem(काष्ठा qed_hwfn *p_hwfn,
			    काष्ठा qed_ptt *p_ptt,
			    u32 *dump_buf,
			    bool dump,
			    स्थिर अक्षर *name,
			    u32 addr,
			    u32 len,
			    bool wide_bus,
			    u32 bit_width,
			    bool packed,
			    स्थिर अक्षर *mem_group, अक्षर storm_letter)
अणु
	u32 offset = 0;

	offset += qed_grc_dump_mem_hdr(p_hwfn,
				       dump_buf + offset,
				       dump,
				       name,
				       addr,
				       len,
				       bit_width,
				       packed, mem_group, storm_letter);
	offset += qed_grc_dump_addr_range(p_hwfn,
					  p_ptt,
					  dump_buf + offset,
					  dump, addr, len, wide_bus,
					  SPLIT_TYPE_NONE, 0);

	वापस offset;
पूर्ण

/* Dumps GRC memories entries. Returns the dumped size in dwords. */
अटल u32 qed_grc_dump_mem_entries(काष्ठा qed_hwfn *p_hwfn,
				    काष्ठा qed_ptt *p_ptt,
				    काष्ठा virt_mem_desc input_mems_arr,
				    u32 *dump_buf, bool dump)
अणु
	u32 i, offset = 0, input_offset = 0;
	bool mode_match = true;

	जबतक (input_offset < BYTES_TO_DWORDS(input_mems_arr.size)) अणु
		स्थिर काष्ठा dbg_dump_cond_hdr *cond_hdr;
		u16 modes_buf_offset;
		u32 num_entries;
		bool eval_mode;

		cond_hdr =
		    (स्थिर काष्ठा dbg_dump_cond_hdr *)input_mems_arr.ptr +
		    input_offset++;
		num_entries = cond_hdr->data_size / MEM_DUMP_ENTRY_SIZE_DWORDS;

		/* Check required mode */
		eval_mode = GET_FIELD(cond_hdr->mode.data,
				      DBG_MODE_HDR_EVAL_MODE) > 0;
		अगर (eval_mode) अणु
			modes_buf_offset =
				GET_FIELD(cond_hdr->mode.data,
					  DBG_MODE_HDR_MODES_BUF_OFFSET);
			mode_match = qed_is_mode_match(p_hwfn,
						       &modes_buf_offset);
		पूर्ण

		अगर (!mode_match) अणु
			input_offset += cond_hdr->data_size;
			जारी;
		पूर्ण

		क्रम (i = 0; i < num_entries;
		     i++, input_offset += MEM_DUMP_ENTRY_SIZE_DWORDS) अणु
			स्थिर काष्ठा dbg_dump_mem *mem =
			    (स्थिर काष्ठा dbg_dump_mem *)((u32 *)
							  input_mems_arr.ptr
							  + input_offset);
			स्थिर काष्ठा dbg_block *block;
			अक्षर storm_letter = 0;
			u32 mem_addr, mem_len;
			bool mem_wide_bus;
			u8 mem_group_id;

			mem_group_id = GET_FIELD(mem->dword0,
						 DBG_DUMP_MEM_MEM_GROUP_ID);
			अगर (mem_group_id >= MEM_GROUPS_NUM) अणु
				DP_NOTICE(p_hwfn, "Invalid mem_group_id\n");
				वापस 0;
			पूर्ण

			अगर (!qed_grc_is_mem_included(p_hwfn,
						     (क्रमागत block_id)
						     cond_hdr->block_id,
						     mem_group_id))
				जारी;

			mem_addr = GET_FIELD(mem->dword0, DBG_DUMP_MEM_ADDRESS);
			mem_len = GET_FIELD(mem->dword1, DBG_DUMP_MEM_LENGTH);
			mem_wide_bus = GET_FIELD(mem->dword1,
						 DBG_DUMP_MEM_WIDE_BUS);

			block = get_dbg_block(p_hwfn,
					      cond_hdr->block_id);

			/* If memory is associated with Storm,
			 * update storm details
			 */
			अगर (block->associated_storm_letter)
				storm_letter = block->associated_storm_letter;

			/* Dump memory */
			offset += qed_grc_dump_mem(p_hwfn,
						p_ptt,
						dump_buf + offset,
						dump,
						शून्य,
						mem_addr,
						mem_len,
						mem_wide_bus,
						0,
						false,
						s_mem_group_names[mem_group_id],
						storm_letter);
		पूर्ण
	पूर्ण

	वापस offset;
पूर्ण

/* Dumps GRC memories according to the input array dump_mem.
 * Returns the dumped size in dwords.
 */
अटल u32 qed_grc_dump_memories(काष्ठा qed_hwfn *p_hwfn,
				 काष्ठा qed_ptt *p_ptt,
				 u32 *dump_buf, bool dump)
अणु
	काष्ठा virt_mem_desc *dbg_buf =
	    &p_hwfn->dbg_arrays[BIN_BUF_DBG_DUMP_MEM];
	u32 offset = 0, input_offset = 0;

	जबतक (input_offset < BYTES_TO_DWORDS(dbg_buf->size)) अणु
		स्थिर काष्ठा dbg_dump_split_hdr *split_hdr;
		काष्ठा virt_mem_desc curr_input_mems_arr;
		क्रमागत init_split_types split_type;
		u32 split_data_size;

		split_hdr =
		    (स्थिर काष्ठा dbg_dump_split_hdr *)dbg_buf->ptr +
		    input_offset++;
		split_type = GET_FIELD(split_hdr->hdr,
				       DBG_DUMP_SPLIT_HDR_SPLIT_TYPE_ID);
		split_data_size = GET_FIELD(split_hdr->hdr,
					    DBG_DUMP_SPLIT_HDR_DATA_SIZE);
		curr_input_mems_arr.ptr = (u32 *)dbg_buf->ptr + input_offset;
		curr_input_mems_arr.size = DWORDS_TO_BYTES(split_data_size);

		अगर (split_type == SPLIT_TYPE_NONE)
			offset += qed_grc_dump_mem_entries(p_hwfn,
							   p_ptt,
							   curr_input_mems_arr,
							   dump_buf + offset,
							   dump);
		अन्यथा
			DP_NOTICE(p_hwfn,
				  "Dumping split memories is currently not supported\n");

		input_offset += split_data_size;
	पूर्ण

	वापस offset;
पूर्ण

/* Dumps GRC context data क्रम the specअगरied Storm.
 * Returns the dumped size in dwords.
 * The lid_size argument is specअगरied in quad-regs.
 */
अटल u32 qed_grc_dump_ctx_data(काष्ठा qed_hwfn *p_hwfn,
				 काष्ठा qed_ptt *p_ptt,
				 u32 *dump_buf,
				 bool dump,
				 स्थिर अक्षर *name,
				 u32 num_lids,
				 क्रमागत cm_ctx_types ctx_type, u8 storm_id)
अणु
	काष्ठा dbg_tools_data *dev_data = &p_hwfn->dbg_info;
	काष्ठा storm_defs *storm = &s_storm_defs[storm_id];
	u32 i, lid, lid_size, total_size;
	u32 rd_reg_addr, offset = 0;

	/* Convert quad-regs to dwords */
	lid_size = storm->cm_ctx_lid_sizes[dev_data->chip_id][ctx_type] * 4;

	अगर (!lid_size)
		वापस 0;

	total_size = num_lids * lid_size;

	offset += qed_grc_dump_mem_hdr(p_hwfn,
				       dump_buf + offset,
				       dump,
				       name,
				       0,
				       total_size,
				       lid_size * 32,
				       false, name, storm->letter);

	अगर (!dump)
		वापस offset + total_size;

	rd_reg_addr = BYTES_TO_DWORDS(storm->cm_ctx_rd_addr[ctx_type]);

	/* Dump context data */
	क्रम (lid = 0; lid < num_lids; lid++) अणु
		क्रम (i = 0; i < lid_size; i++) अणु
			qed_wr(p_hwfn,
			       p_ptt, storm->cm_ctx_wr_addr, (i << 9) | lid);
			offset += qed_grc_dump_addr_range(p_hwfn,
							  p_ptt,
							  dump_buf + offset,
							  dump,
							  rd_reg_addr,
							  1,
							  false,
							  SPLIT_TYPE_NONE, 0);
		पूर्ण
	पूर्ण

	वापस offset;
पूर्ण

/* Dumps GRC contexts. Returns the dumped size in dwords. */
अटल u32 qed_grc_dump_ctx(काष्ठा qed_hwfn *p_hwfn,
			    काष्ठा qed_ptt *p_ptt, u32 *dump_buf, bool dump)
अणु
	u32 offset = 0;
	u8 storm_id;

	क्रम (storm_id = 0; storm_id < MAX_DBG_STORMS; storm_id++) अणु
		अगर (!qed_grc_is_storm_included(p_hwfn,
					       (क्रमागत dbg_storms)storm_id))
			जारी;

		/* Dump Conn AG context size */
		offset += qed_grc_dump_ctx_data(p_hwfn,
						p_ptt,
						dump_buf + offset,
						dump,
						"CONN_AG_CTX",
						NUM_OF_LCIDS,
						CM_CTX_CONN_AG, storm_id);

		/* Dump Conn ST context size */
		offset += qed_grc_dump_ctx_data(p_hwfn,
						p_ptt,
						dump_buf + offset,
						dump,
						"CONN_ST_CTX",
						NUM_OF_LCIDS,
						CM_CTX_CONN_ST, storm_id);

		/* Dump Task AG context size */
		offset += qed_grc_dump_ctx_data(p_hwfn,
						p_ptt,
						dump_buf + offset,
						dump,
						"TASK_AG_CTX",
						NUM_OF_LTIDS,
						CM_CTX_TASK_AG, storm_id);

		/* Dump Task ST context size */
		offset += qed_grc_dump_ctx_data(p_hwfn,
						p_ptt,
						dump_buf + offset,
						dump,
						"TASK_ST_CTX",
						NUM_OF_LTIDS,
						CM_CTX_TASK_ST, storm_id);
	पूर्ण

	वापस offset;
पूर्ण

#घोषणा VFC_STATUS_RESP_READY_BIT	0
#घोषणा VFC_STATUS_BUSY_BIT		1
#घोषणा VFC_STATUS_SENDING_CMD_BIT	2

#घोषणा VFC_POLLING_DELAY_MS	1
#घोषणा VFC_POLLING_COUNT		20

/* Reads data from VFC. Returns the number of dwords पढ़ो (0 on error).
 * Sizes are specअगरied in dwords.
 */
अटल u32 qed_grc_dump_पढ़ो_from_vfc(काष्ठा qed_hwfn *p_hwfn,
				      काष्ठा qed_ptt *p_ptt,
				      काष्ठा storm_defs *storm,
				      u32 *cmd_data,
				      u32 cmd_size,
				      u32 *addr_data,
				      u32 addr_size,
				      u32 resp_size, u32 *dump_buf)
अणु
	काष्ठा dbg_tools_data *dev_data = &p_hwfn->dbg_info;
	u32 vfc_status, polling_ms, polling_count = 0, i;
	u32 reg_addr, sem_base;
	bool is_पढ़ोy = false;

	sem_base = storm->sem_fast_mem_addr;
	polling_ms = VFC_POLLING_DELAY_MS *
	    s_hw_type_defs[dev_data->hw_type].delay_factor;

	/* Write VFC command */
	ARR_REG_WR(p_hwfn,
		   p_ptt,
		   sem_base + SEM_FAST_REG_VFC_DATA_WR,
		   cmd_data, cmd_size);

	/* Write VFC address */
	ARR_REG_WR(p_hwfn,
		   p_ptt,
		   sem_base + SEM_FAST_REG_VFC_ADDR,
		   addr_data, addr_size);

	/* Read response */
	क्रम (i = 0; i < resp_size; i++) अणु
		/* Poll until पढ़ोy */
		करो अणु
			reg_addr = sem_base + SEM_FAST_REG_VFC_STATUS;
			qed_grc_dump_addr_range(p_hwfn,
						p_ptt,
						&vfc_status,
						true,
						BYTES_TO_DWORDS(reg_addr),
						1,
						false, SPLIT_TYPE_NONE, 0);
			is_पढ़ोy = vfc_status & BIT(VFC_STATUS_RESP_READY_BIT);

			अगर (!is_पढ़ोy) अणु
				अगर (polling_count++ == VFC_POLLING_COUNT)
					वापस 0;

				msleep(polling_ms);
			पूर्ण
		पूर्ण जबतक (!is_पढ़ोy);

		reg_addr = sem_base + SEM_FAST_REG_VFC_DATA_RD;
		qed_grc_dump_addr_range(p_hwfn,
					p_ptt,
					dump_buf + i,
					true,
					BYTES_TO_DWORDS(reg_addr),
					1, false, SPLIT_TYPE_NONE, 0);
	पूर्ण

	वापस resp_size;
पूर्ण

/* Dump VFC CAM. Returns the dumped size in dwords. */
अटल u32 qed_grc_dump_vfc_cam(काष्ठा qed_hwfn *p_hwfn,
				काष्ठा qed_ptt *p_ptt,
				u32 *dump_buf, bool dump, u8 storm_id)
अणु
	u32 total_size = VFC_CAM_NUM_ROWS * VFC_CAM_RESP_DWORDS;
	काष्ठा storm_defs *storm = &s_storm_defs[storm_id];
	u32 cam_addr[VFC_CAM_ADDR_DWORDS] = अणु 0 पूर्ण;
	u32 cam_cmd[VFC_CAM_CMD_DWORDS] = अणु 0 पूर्ण;
	u32 row, offset = 0;

	offset += qed_grc_dump_mem_hdr(p_hwfn,
				       dump_buf + offset,
				       dump,
				       "vfc_cam",
				       0,
				       total_size,
				       256,
				       false, "vfc_cam", storm->letter);

	अगर (!dump)
		वापस offset + total_size;

	/* Prepare CAM address */
	SET_VAR_FIELD(cam_addr, VFC_CAM_ADDR, OP, VFC_OPCODE_CAM_RD);

	/* Read VFC CAM data */
	क्रम (row = 0; row < VFC_CAM_NUM_ROWS; row++) अणु
		SET_VAR_FIELD(cam_cmd, VFC_CAM_CMD, ROW, row);
		offset += qed_grc_dump_पढ़ो_from_vfc(p_hwfn,
						     p_ptt,
						     storm,
						     cam_cmd,
						     VFC_CAM_CMD_DWORDS,
						     cam_addr,
						     VFC_CAM_ADDR_DWORDS,
						     VFC_CAM_RESP_DWORDS,
						     dump_buf + offset);
	पूर्ण

	वापस offset;
पूर्ण

/* Dump VFC RAM. Returns the dumped size in dwords. */
अटल u32 qed_grc_dump_vfc_ram(काष्ठा qed_hwfn *p_hwfn,
				काष्ठा qed_ptt *p_ptt,
				u32 *dump_buf,
				bool dump,
				u8 storm_id, काष्ठा vfc_ram_defs *ram_defs)
अणु
	u32 total_size = ram_defs->num_rows * VFC_RAM_RESP_DWORDS;
	काष्ठा storm_defs *storm = &s_storm_defs[storm_id];
	u32 ram_addr[VFC_RAM_ADDR_DWORDS] = अणु 0 पूर्ण;
	u32 ram_cmd[VFC_RAM_CMD_DWORDS] = अणु 0 पूर्ण;
	u32 row, offset = 0;

	offset += qed_grc_dump_mem_hdr(p_hwfn,
				       dump_buf + offset,
				       dump,
				       ram_defs->mem_name,
				       0,
				       total_size,
				       256,
				       false,
				       ram_defs->type_name,
				       storm->letter);

	अगर (!dump)
		वापस offset + total_size;

	/* Prepare RAM address */
	SET_VAR_FIELD(ram_addr, VFC_RAM_ADDR, OP, VFC_OPCODE_RAM_RD);

	/* Read VFC RAM data */
	क्रम (row = ram_defs->base_row;
	     row < ram_defs->base_row + ram_defs->num_rows; row++) अणु
		SET_VAR_FIELD(ram_addr, VFC_RAM_ADDR, ROW, row);
		offset += qed_grc_dump_पढ़ो_from_vfc(p_hwfn,
						     p_ptt,
						     storm,
						     ram_cmd,
						     VFC_RAM_CMD_DWORDS,
						     ram_addr,
						     VFC_RAM_ADDR_DWORDS,
						     VFC_RAM_RESP_DWORDS,
						     dump_buf + offset);
	पूर्ण

	वापस offset;
पूर्ण

/* Dumps GRC VFC data. Returns the dumped size in dwords. */
अटल u32 qed_grc_dump_vfc(काष्ठा qed_hwfn *p_hwfn,
			    काष्ठा qed_ptt *p_ptt, u32 *dump_buf, bool dump)
अणु
	u8 storm_id, i;
	u32 offset = 0;

	क्रम (storm_id = 0; storm_id < MAX_DBG_STORMS; storm_id++) अणु
		अगर (!qed_grc_is_storm_included(p_hwfn,
					       (क्रमागत dbg_storms)storm_id) ||
		    !s_storm_defs[storm_id].has_vfc)
			जारी;

		/* Read CAM */
		offset += qed_grc_dump_vfc_cam(p_hwfn,
					       p_ptt,
					       dump_buf + offset,
					       dump, storm_id);

		/* Read RAM */
		क्रम (i = 0; i < NUM_VFC_RAM_TYPES; i++)
			offset += qed_grc_dump_vfc_ram(p_hwfn,
						       p_ptt,
						       dump_buf + offset,
						       dump,
						       storm_id,
						       &s_vfc_ram_defs[i]);
	पूर्ण

	वापस offset;
पूर्ण

/* Dumps GRC RSS data. Returns the dumped size in dwords. */
अटल u32 qed_grc_dump_rss(काष्ठा qed_hwfn *p_hwfn,
			    काष्ठा qed_ptt *p_ptt, u32 *dump_buf, bool dump)
अणु
	काष्ठा dbg_tools_data *dev_data = &p_hwfn->dbg_info;
	u32 offset = 0;
	u8 rss_mem_id;

	क्रम (rss_mem_id = 0; rss_mem_id < NUM_RSS_MEM_TYPES; rss_mem_id++) अणु
		u32 rss_addr, num_entries, total_dwords;
		काष्ठा rss_mem_defs *rss_defs;
		u32 addr, num_dwords_to_पढ़ो;
		bool packed;

		rss_defs = &s_rss_mem_defs[rss_mem_id];
		rss_addr = rss_defs->addr;
		num_entries = rss_defs->num_entries[dev_data->chip_id];
		total_dwords = (num_entries * rss_defs->entry_width) / 32;
		packed = (rss_defs->entry_width == 16);

		offset += qed_grc_dump_mem_hdr(p_hwfn,
					       dump_buf + offset,
					       dump,
					       rss_defs->mem_name,
					       0,
					       total_dwords,
					       rss_defs->entry_width,
					       packed,
					       rss_defs->type_name, 0);

		/* Dump RSS data */
		अगर (!dump) अणु
			offset += total_dwords;
			जारी;
		पूर्ण

		addr = BYTES_TO_DWORDS(RSS_REG_RSS_RAM_DATA);
		जबतक (total_dwords) अणु
			num_dwords_to_पढ़ो = min_t(u32,
						   RSS_REG_RSS_RAM_DATA_SIZE,
						   total_dwords);
			qed_wr(p_hwfn, p_ptt, RSS_REG_RSS_RAM_ADDR, rss_addr);
			offset += qed_grc_dump_addr_range(p_hwfn,
							  p_ptt,
							  dump_buf + offset,
							  dump,
							  addr,
							  num_dwords_to_पढ़ो,
							  false,
							  SPLIT_TYPE_NONE, 0);
			total_dwords -= num_dwords_to_पढ़ो;
			rss_addr++;
		पूर्ण
	पूर्ण

	वापस offset;
पूर्ण

/* Dumps GRC Big RAM. Returns the dumped size in dwords. */
अटल u32 qed_grc_dump_big_ram(काष्ठा qed_hwfn *p_hwfn,
				काष्ठा qed_ptt *p_ptt,
				u32 *dump_buf, bool dump, u8 big_ram_id)
अणु
	काष्ठा dbg_tools_data *dev_data = &p_hwfn->dbg_info;
	u32 block_size, ram_size, offset = 0, reg_val, i;
	अक्षर mem_name[12] = "???_BIG_RAM";
	अक्षर type_name[8] = "???_RAM";
	काष्ठा big_ram_defs *big_ram;

	big_ram = &s_big_ram_defs[big_ram_id];
	ram_size = big_ram->ram_size[dev_data->chip_id];

	reg_val = qed_rd(p_hwfn, p_ptt, big_ram->is_256b_reg_addr);
	block_size = reg_val &
		     BIT(big_ram->is_256b_bit_offset[dev_data->chip_id]) ? 256
									 : 128;

	म_नकलन(type_name, big_ram->instance_name, BIG_RAM_NAME_LEN);
	म_नकलन(mem_name, big_ram->instance_name, BIG_RAM_NAME_LEN);

	/* Dump memory header */
	offset += qed_grc_dump_mem_hdr(p_hwfn,
				       dump_buf + offset,
				       dump,
				       mem_name,
				       0,
				       ram_size,
				       block_size * 8,
				       false, type_name, 0);

	/* Read and dump Big RAM data */
	अगर (!dump)
		वापस offset + ram_size;

	/* Dump Big RAM */
	क्रम (i = 0; i < DIV_ROUND_UP(ram_size, BRB_REG_BIG_RAM_DATA_SIZE);
	     i++) अणु
		u32 addr, len;

		qed_wr(p_hwfn, p_ptt, big_ram->addr_reg_addr, i);
		addr = BYTES_TO_DWORDS(big_ram->data_reg_addr);
		len = BRB_REG_BIG_RAM_DATA_SIZE;
		offset += qed_grc_dump_addr_range(p_hwfn,
						  p_ptt,
						  dump_buf + offset,
						  dump,
						  addr,
						  len,
						  false, SPLIT_TYPE_NONE, 0);
	पूर्ण

	वापस offset;
पूर्ण

/* Dumps MCP scratchpad. Returns the dumped size in dwords. */
अटल u32 qed_grc_dump_mcp(काष्ठा qed_hwfn *p_hwfn,
			    काष्ठा qed_ptt *p_ptt, u32 *dump_buf, bool dump)
अणु
	bool block_enable[MAX_BLOCK_ID] = अणु 0 पूर्ण;
	u32 offset = 0, addr;
	bool halted = false;

	/* Halt MCP */
	अगर (dump && !qed_grc_get_param(p_hwfn, DBG_GRC_PARAM_NO_MCP)) अणु
		halted = !qed_mcp_halt(p_hwfn, p_ptt);
		अगर (!halted)
			DP_NOTICE(p_hwfn, "MCP halt failed!\n");
	पूर्ण

	/* Dump MCP scratchpad */
	offset += qed_grc_dump_mem(p_hwfn,
				   p_ptt,
				   dump_buf + offset,
				   dump,
				   शून्य,
				   BYTES_TO_DWORDS(MCP_REG_SCRATCH),
				   MCP_REG_SCRATCH_SIZE,
				   false, 0, false, "MCP", 0);

	/* Dump MCP cpu_reg_file */
	offset += qed_grc_dump_mem(p_hwfn,
				   p_ptt,
				   dump_buf + offset,
				   dump,
				   शून्य,
				   BYTES_TO_DWORDS(MCP_REG_CPU_REG_खाता),
				   MCP_REG_CPU_REG_खाता_SIZE,
				   false, 0, false, "MCP", 0);

	/* Dump MCP रेजिस्टरs */
	block_enable[BLOCK_MCP] = true;
	offset += qed_grc_dump_रेजिस्टरs(p_hwfn,
					 p_ptt,
					 dump_buf + offset,
					 dump, block_enable, "MCP");

	/* Dump required non-MCP रेजिस्टरs */
	offset += qed_grc_dump_regs_hdr(dump_buf + offset,
					dump, 1, SPLIT_TYPE_NONE, 0,
					"MCP");
	addr = BYTES_TO_DWORDS(MISC_REG_SHARED_MEM_ADDR);
	offset += qed_grc_dump_reg_entry(p_hwfn,
					 p_ptt,
					 dump_buf + offset,
					 dump,
					 addr,
					 1,
					 false, SPLIT_TYPE_NONE, 0);

	/* Release MCP */
	अगर (halted && qed_mcp_resume(p_hwfn, p_ptt))
		DP_NOTICE(p_hwfn, "Failed to resume MCP after halt!\n");

	वापस offset;
पूर्ण

/* Dumps the tbus indirect memory क्रम all PHYs.
 * Returns the dumped size in dwords.
 */
अटल u32 qed_grc_dump_phy(काष्ठा qed_hwfn *p_hwfn,
			    काष्ठा qed_ptt *p_ptt, u32 *dump_buf, bool dump)
अणु
	u32 offset = 0, tbus_lo_offset, tbus_hi_offset;
	अक्षर mem_name[32];
	u8 phy_id;

	क्रम (phy_id = 0; phy_id < ARRAY_SIZE(s_phy_defs); phy_id++) अणु
		u32 addr_lo_addr, addr_hi_addr, data_lo_addr, data_hi_addr;
		काष्ठा phy_defs *phy_defs;
		u8 *bytes_buf;

		phy_defs = &s_phy_defs[phy_id];
		addr_lo_addr = phy_defs->base_addr +
			       phy_defs->tbus_addr_lo_addr;
		addr_hi_addr = phy_defs->base_addr +
			       phy_defs->tbus_addr_hi_addr;
		data_lo_addr = phy_defs->base_addr +
			       phy_defs->tbus_data_lo_addr;
		data_hi_addr = phy_defs->base_addr +
			       phy_defs->tbus_data_hi_addr;

		अगर (snम_लिखो(mem_name, माप(mem_name), "tbus_%s",
			     phy_defs->phy_name) < 0)
			DP_NOTICE(p_hwfn,
				  "Unexpected debug error: invalid PHY memory name\n");

		offset += qed_grc_dump_mem_hdr(p_hwfn,
					       dump_buf + offset,
					       dump,
					       mem_name,
					       0,
					       PHY_DUMP_SIZE_DWORDS,
					       16, true, mem_name, 0);

		अगर (!dump) अणु
			offset += PHY_DUMP_SIZE_DWORDS;
			जारी;
		पूर्ण

		bytes_buf = (u8 *)(dump_buf + offset);
		क्रम (tbus_hi_offset = 0;
		     tbus_hi_offset < (NUM_PHY_TBUS_ADDRESSES >> 8);
		     tbus_hi_offset++) अणु
			qed_wr(p_hwfn, p_ptt, addr_hi_addr, tbus_hi_offset);
			क्रम (tbus_lo_offset = 0; tbus_lo_offset < 256;
			     tbus_lo_offset++) अणु
				qed_wr(p_hwfn,
				       p_ptt, addr_lo_addr, tbus_lo_offset);
				*(bytes_buf++) = (u8)qed_rd(p_hwfn,
							    p_ptt,
							    data_lo_addr);
				*(bytes_buf++) = (u8)qed_rd(p_hwfn,
							    p_ptt,
							    data_hi_addr);
			पूर्ण
		पूर्ण

		offset += PHY_DUMP_SIZE_DWORDS;
	पूर्ण

	वापस offset;
पूर्ण

अटल क्रमागत dbg_status qed_find_nvram_image(काष्ठा qed_hwfn *p_hwfn,
					    काष्ठा qed_ptt *p_ptt,
					    u32 image_type,
					    u32 *nvram_offset_bytes,
					    u32 *nvram_size_bytes);

अटल क्रमागत dbg_status qed_nvram_पढ़ो(काष्ठा qed_hwfn *p_hwfn,
				      काष्ठा qed_ptt *p_ptt,
				      u32 nvram_offset_bytes,
				      u32 nvram_size_bytes, u32 *ret_buf);

/* Dumps the MCP HW dump from NVRAM. Returns the dumped size in dwords. */
अटल u32 qed_grc_dump_mcp_hw_dump(काष्ठा qed_hwfn *p_hwfn,
				    काष्ठा qed_ptt *p_ptt,
				    u32 *dump_buf, bool dump)
अणु
	u32 hw_dump_offset_bytes = 0, hw_dump_size_bytes = 0;
	u32 hw_dump_size_dwords = 0, offset = 0;
	क्रमागत dbg_status status;

	/* Read HW dump image from NVRAM */
	status = qed_find_nvram_image(p_hwfn,
				      p_ptt,
				      NVM_TYPE_HW_DUMP_OUT,
				      &hw_dump_offset_bytes,
				      &hw_dump_size_bytes);
	अगर (status != DBG_STATUS_OK)
		वापस 0;

	hw_dump_size_dwords = BYTES_TO_DWORDS(hw_dump_size_bytes);

	/* Dump HW dump image section */
	offset += qed_dump_section_hdr(dump_buf + offset,
				       dump, "mcp_hw_dump", 1);
	offset += qed_dump_num_param(dump_buf + offset,
				     dump, "size", hw_dump_size_dwords);

	/* Read MCP HW dump image पूर्णांकo dump buffer */
	अगर (dump && hw_dump_size_dwords) अणु
		status = qed_nvram_पढ़ो(p_hwfn,
					p_ptt,
					hw_dump_offset_bytes,
					hw_dump_size_bytes, dump_buf + offset);
		अगर (status != DBG_STATUS_OK) अणु
			DP_NOTICE(p_hwfn,
				  "Failed to read MCP HW Dump image from NVRAM\n");
			वापस 0;
		पूर्ण
	पूर्ण
	offset += hw_dump_size_dwords;

	वापस offset;
पूर्ण

/* Dumps Static Debug data. Returns the dumped size in dwords. */
अटल u32 qed_grc_dump_अटल_debug(काष्ठा qed_hwfn *p_hwfn,
				     काष्ठा qed_ptt *p_ptt,
				     u32 *dump_buf, bool dump)
अणु
	काष्ठा dbg_tools_data *dev_data = &p_hwfn->dbg_info;
	u32 block_id, line_id, offset = 0, addr, len;

	/* Don't dump अटल debug अगर a debug bus recording is in progress */
	अगर (dump && qed_rd(p_hwfn, p_ptt, DBG_REG_DBG_BLOCK_ON))
		वापस 0;

	अगर (dump) अणु
		/* Disable debug bus in all blocks */
		qed_bus_disable_blocks(p_hwfn, p_ptt);

		qed_bus_reset_dbg_block(p_hwfn, p_ptt);
		qed_wr(p_hwfn,
		       p_ptt, DBG_REG_FRAMING_MODE, DBG_BUS_FRAME_MODE_8HW);
		qed_wr(p_hwfn,
		       p_ptt, DBG_REG_DEBUG_TARGET, DBG_BUS_TARGET_ID_INT_BUF);
		qed_wr(p_hwfn, p_ptt, DBG_REG_FULL_MODE, 1);
		qed_bus_enable_dbg_block(p_hwfn, p_ptt, true);
	पूर्ण

	/* Dump all अटल debug lines क्रम each relevant block */
	क्रम (block_id = 0; block_id < MAX_BLOCK_ID; block_id++) अणु
		स्थिर काष्ठा dbg_block_chip *block_per_chip;
		स्थिर काष्ठा dbg_block *block;
		bool is_हटाओd, has_dbg_bus;
		u16 modes_buf_offset;
		u32 block_dwords;

		block_per_chip =
		    qed_get_dbg_block_per_chip(p_hwfn, (क्रमागत block_id)block_id);
		is_हटाओd = GET_FIELD(block_per_chip->flags,
				       DBG_BLOCK_CHIP_IS_REMOVED);
		has_dbg_bus = GET_FIELD(block_per_chip->flags,
					DBG_BLOCK_CHIP_HAS_DBG_BUS);

		/* पढ़ो+clear क्रम NWS parity is not working, skip NWS block */
		अगर (block_id == BLOCK_NWS)
			जारी;

		अगर (!is_हटाओd && has_dbg_bus &&
		    GET_FIELD(block_per_chip->dbg_bus_mode.data,
			      DBG_MODE_HDR_EVAL_MODE) > 0) अणु
			modes_buf_offset =
			    GET_FIELD(block_per_chip->dbg_bus_mode.data,
				      DBG_MODE_HDR_MODES_BUF_OFFSET);
			अगर (!qed_is_mode_match(p_hwfn, &modes_buf_offset))
				has_dbg_bus = false;
		पूर्ण

		अगर (is_हटाओd || !has_dbg_bus)
			जारी;

		block_dwords = NUM_DBG_LINES(block_per_chip) *
			       STATIC_DEBUG_LINE_DWORDS;

		/* Dump अटल section params */
		block = get_dbg_block(p_hwfn, (क्रमागत block_id)block_id);
		offset += qed_grc_dump_mem_hdr(p_hwfn,
					       dump_buf + offset,
					       dump,
					       block->name,
					       0,
					       block_dwords,
					       32, false, "STATIC", 0);

		अगर (!dump) अणु
			offset += block_dwords;
			जारी;
		पूर्ण

		/* If all lines are invalid - dump zeros */
		अगर (dev_data->block_in_reset[block_id]) अणु
			स_रखो(dump_buf + offset, 0,
			       DWORDS_TO_BYTES(block_dwords));
			offset += block_dwords;
			जारी;
		पूर्ण

		/* Enable block's client */
		qed_bus_enable_clients(p_hwfn,
				       p_ptt,
				       BIT(block_per_chip->dbg_client_id));

		addr = BYTES_TO_DWORDS(DBG_REG_CALENDAR_OUT_DATA);
		len = STATIC_DEBUG_LINE_DWORDS;
		क्रम (line_id = 0; line_id < (u32)NUM_DBG_LINES(block_per_chip);
		     line_id++) अणु
			/* Configure debug line ID */
			qed_bus_config_dbg_line(p_hwfn,
						p_ptt,
						(क्रमागत block_id)block_id,
						(u8)line_id, 0xf, 0, 0, 0);

			/* Read debug line info */
			offset += qed_grc_dump_addr_range(p_hwfn,
							  p_ptt,
							  dump_buf + offset,
							  dump,
							  addr,
							  len,
							  true, SPLIT_TYPE_NONE,
							  0);
		पूर्ण

		/* Disable block's client and debug output */
		qed_bus_enable_clients(p_hwfn, p_ptt, 0);
		qed_bus_config_dbg_line(p_hwfn, p_ptt,
					(क्रमागत block_id)block_id, 0, 0, 0, 0, 0);
	पूर्ण

	अगर (dump) अणु
		qed_bus_enable_dbg_block(p_hwfn, p_ptt, false);
		qed_bus_enable_clients(p_hwfn, p_ptt, 0);
	पूर्ण

	वापस offset;
पूर्ण

/* Perक्रमms GRC Dump to the specअगरied buffer.
 * Returns the dumped size in dwords.
 */
अटल क्रमागत dbg_status qed_grc_dump(काष्ठा qed_hwfn *p_hwfn,
				    काष्ठा qed_ptt *p_ptt,
				    u32 *dump_buf,
				    bool dump, u32 *num_dumped_dwords)
अणु
	काष्ठा dbg_tools_data *dev_data = &p_hwfn->dbg_info;
	u32 dwords_पढ़ो, offset = 0;
	bool parities_masked = false;
	u8 i;

	*num_dumped_dwords = 0;
	dev_data->num_regs_पढ़ो = 0;

	/* Update reset state */
	अगर (dump)
		qed_update_blocks_reset_state(p_hwfn, p_ptt);

	/* Dump global params */
	offset += qed_dump_common_global_params(p_hwfn,
						p_ptt,
						dump_buf + offset, dump, 4);
	offset += qed_dump_str_param(dump_buf + offset,
				     dump, "dump-type", "grc-dump");
	offset += qed_dump_num_param(dump_buf + offset,
				     dump,
				     "num-lcids",
				     NUM_OF_LCIDS);
	offset += qed_dump_num_param(dump_buf + offset,
				     dump,
				     "num-ltids",
				     NUM_OF_LTIDS);
	offset += qed_dump_num_param(dump_buf + offset,
				     dump, "num-ports", dev_data->num_ports);

	/* Dump reset रेजिस्टरs (dumped beक्रमe taking blocks out of reset ) */
	अगर (qed_grc_is_included(p_hwfn, DBG_GRC_PARAM_DUMP_REGS))
		offset += qed_grc_dump_reset_regs(p_hwfn,
						  p_ptt,
						  dump_buf + offset, dump);

	/* Take all blocks out of reset (using reset रेजिस्टरs) */
	अगर (dump) अणु
		qed_grc_unreset_blocks(p_hwfn, p_ptt, false);
		qed_update_blocks_reset_state(p_hwfn, p_ptt);
	पूर्ण

	/* Disable all parities using MFW command */
	अगर (dump &&
	    !qed_grc_get_param(p_hwfn, DBG_GRC_PARAM_NO_MCP)) अणु
		parities_masked = !qed_mcp_mask_parities(p_hwfn, p_ptt, 1);
		अगर (!parities_masked) अणु
			DP_NOTICE(p_hwfn,
				  "Failed to mask parities using MFW\n");
			अगर (qed_grc_get_param
			    (p_hwfn, DBG_GRC_PARAM_PARITY_SAFE))
				वापस DBG_STATUS_MCP_COULD_NOT_MASK_PRTY;
		पूर्ण
	पूर्ण

	/* Dump modअगरied रेजिस्टरs (dumped beक्रमe modअगरying them) */
	अगर (qed_grc_is_included(p_hwfn, DBG_GRC_PARAM_DUMP_REGS))
		offset += qed_grc_dump_modअगरied_regs(p_hwfn,
						     p_ptt,
						     dump_buf + offset, dump);

	/* Stall storms */
	अगर (dump &&
	    (qed_grc_is_included(p_hwfn,
				 DBG_GRC_PARAM_DUMP_IOR) ||
	     qed_grc_is_included(p_hwfn, DBG_GRC_PARAM_DUMP_VFC)))
		qed_grc_stall_storms(p_hwfn, p_ptt, true);

	/* Dump all regs  */
	अगर (qed_grc_is_included(p_hwfn, DBG_GRC_PARAM_DUMP_REGS)) अणु
		bool block_enable[MAX_BLOCK_ID];

		/* Dump all blocks except MCP */
		क्रम (i = 0; i < MAX_BLOCK_ID; i++)
			block_enable[i] = true;
		block_enable[BLOCK_MCP] = false;
		offset += qed_grc_dump_रेजिस्टरs(p_hwfn,
						 p_ptt,
						 dump_buf +
						 offset,
						 dump,
						 block_enable, शून्य);

		/* Dump special रेजिस्टरs */
		offset += qed_grc_dump_special_regs(p_hwfn,
						    p_ptt,
						    dump_buf + offset, dump);
	पूर्ण

	/* Dump memories */
	offset += qed_grc_dump_memories(p_hwfn, p_ptt, dump_buf + offset, dump);

	/* Dump MCP */
	अगर (qed_grc_is_included(p_hwfn, DBG_GRC_PARAM_DUMP_MCP))
		offset += qed_grc_dump_mcp(p_hwfn,
					   p_ptt, dump_buf + offset, dump);

	/* Dump context */
	अगर (qed_grc_is_included(p_hwfn, DBG_GRC_PARAM_DUMP_CM_CTX))
		offset += qed_grc_dump_ctx(p_hwfn,
					   p_ptt, dump_buf + offset, dump);

	/* Dump RSS memories */
	अगर (qed_grc_is_included(p_hwfn, DBG_GRC_PARAM_DUMP_RSS))
		offset += qed_grc_dump_rss(p_hwfn,
					   p_ptt, dump_buf + offset, dump);

	/* Dump Big RAM */
	क्रम (i = 0; i < NUM_BIG_RAM_TYPES; i++)
		अगर (qed_grc_is_included(p_hwfn, s_big_ram_defs[i].grc_param))
			offset += qed_grc_dump_big_ram(p_hwfn,
						       p_ptt,
						       dump_buf + offset,
						       dump, i);

	/* Dump VFC */
	अगर (qed_grc_is_included(p_hwfn, DBG_GRC_PARAM_DUMP_VFC)) अणु
		dwords_पढ़ो = qed_grc_dump_vfc(p_hwfn,
					       p_ptt, dump_buf + offset, dump);
		offset += dwords_पढ़ो;
		अगर (!dwords_पढ़ो)
			वापस DBG_STATUS_VFC_READ_ERROR;
	पूर्ण

	/* Dump PHY tbus */
	अगर (qed_grc_is_included(p_hwfn,
				DBG_GRC_PARAM_DUMP_PHY) && dev_data->chip_id ==
	    CHIP_K2 && dev_data->hw_type == HW_TYPE_ASIC)
		offset += qed_grc_dump_phy(p_hwfn,
					   p_ptt, dump_buf + offset, dump);

	/* Dump MCP HW Dump */
	अगर (qed_grc_is_included(p_hwfn, DBG_GRC_PARAM_DUMP_MCP_HW_DUMP) &&
	    !qed_grc_get_param(p_hwfn, DBG_GRC_PARAM_NO_MCP) && 1)
		offset += qed_grc_dump_mcp_hw_dump(p_hwfn,
						   p_ptt,
						   dump_buf + offset, dump);

	/* Dump अटल debug data (only अगर not during debug bus recording) */
	अगर (qed_grc_is_included(p_hwfn,
				DBG_GRC_PARAM_DUMP_STATIC) &&
	    (!dump || dev_data->bus.state == DBG_BUS_STATE_IDLE))
		offset += qed_grc_dump_अटल_debug(p_hwfn,
						    p_ptt,
						    dump_buf + offset, dump);

	/* Dump last section */
	offset += qed_dump_last_section(dump_buf, offset, dump);

	अगर (dump) अणु
		/* Unstall storms */
		अगर (qed_grc_get_param(p_hwfn, DBG_GRC_PARAM_UNSTALL))
			qed_grc_stall_storms(p_hwfn, p_ptt, false);

		/* Clear parity status */
		qed_grc_clear_all_prty(p_hwfn, p_ptt);

		/* Enable all parities using MFW command */
		अगर (parities_masked)
			qed_mcp_mask_parities(p_hwfn, p_ptt, 0);
	पूर्ण

	*num_dumped_dwords = offset;

	वापस DBG_STATUS_OK;
पूर्ण

/* Writes the specअगरied failing Idle Check rule to the specअगरied buffer.
 * Returns the dumped size in dwords.
 */
अटल u32 qed_idle_chk_dump_failure(काष्ठा qed_hwfn *p_hwfn,
				     काष्ठा qed_ptt *p_ptt,
				     u32 *
				     dump_buf,
				     bool dump,
				     u16 rule_id,
				     स्थिर काष्ठा dbg_idle_chk_rule *rule,
				     u16 fail_entry_id, u32 *cond_reg_values)
अणु
	काष्ठा dbg_tools_data *dev_data = &p_hwfn->dbg_info;
	स्थिर काष्ठा dbg_idle_chk_cond_reg *cond_regs;
	स्थिर काष्ठा dbg_idle_chk_info_reg *info_regs;
	u32 i, next_reg_offset = 0, offset = 0;
	काष्ठा dbg_idle_chk_result_hdr *hdr;
	स्थिर जोड़ dbg_idle_chk_reg *regs;
	u8 reg_id;

	hdr = (काष्ठा dbg_idle_chk_result_hdr *)dump_buf;
	regs = (स्थिर जोड़ dbg_idle_chk_reg *)
		p_hwfn->dbg_arrays[BIN_BUF_DBG_IDLE_CHK_REGS].ptr +
		rule->reg_offset;
	cond_regs = &regs[0].cond_reg;
	info_regs = &regs[rule->num_cond_regs].info_reg;

	/* Dump rule data */
	अगर (dump) अणु
		स_रखो(hdr, 0, माप(*hdr));
		hdr->rule_id = rule_id;
		hdr->mem_entry_id = fail_entry_id;
		hdr->severity = rule->severity;
		hdr->num_dumped_cond_regs = rule->num_cond_regs;
	पूर्ण

	offset += IDLE_CHK_RESULT_HDR_DWORDS;

	/* Dump condition रेजिस्टर values */
	क्रम (reg_id = 0; reg_id < rule->num_cond_regs; reg_id++) अणु
		स्थिर काष्ठा dbg_idle_chk_cond_reg *reg = &cond_regs[reg_id];
		काष्ठा dbg_idle_chk_result_reg_hdr *reg_hdr;

		reg_hdr =
		    (काष्ठा dbg_idle_chk_result_reg_hdr *)(dump_buf + offset);

		/* Write रेजिस्टर header */
		अगर (!dump) अणु
			offset += IDLE_CHK_RESULT_REG_HDR_DWORDS +
			    reg->entry_size;
			जारी;
		पूर्ण

		offset += IDLE_CHK_RESULT_REG_HDR_DWORDS;
		स_रखो(reg_hdr, 0, माप(*reg_hdr));
		reg_hdr->start_entry = reg->start_entry;
		reg_hdr->size = reg->entry_size;
		SET_FIELD(reg_hdr->data,
			  DBG_IDLE_CHK_RESULT_REG_HDR_IS_MEM,
			  reg->num_entries > 1 || reg->start_entry > 0 ? 1 : 0);
		SET_FIELD(reg_hdr->data,
			  DBG_IDLE_CHK_RESULT_REG_HDR_REG_ID, reg_id);

		/* Write रेजिस्टर values */
		क्रम (i = 0; i < reg_hdr->size; i++, next_reg_offset++, offset++)
			dump_buf[offset] = cond_reg_values[next_reg_offset];
	पूर्ण

	/* Dump info रेजिस्टर values */
	क्रम (reg_id = 0; reg_id < rule->num_info_regs; reg_id++) अणु
		स्थिर काष्ठा dbg_idle_chk_info_reg *reg = &info_regs[reg_id];
		u32 block_id;

		/* Check अगर रेजिस्टर's block is in reset */
		अगर (!dump) अणु
			offset += IDLE_CHK_RESULT_REG_HDR_DWORDS + reg->size;
			जारी;
		पूर्ण

		block_id = GET_FIELD(reg->data, DBG_IDLE_CHK_INFO_REG_BLOCK_ID);
		अगर (block_id >= MAX_BLOCK_ID) अणु
			DP_NOTICE(p_hwfn, "Invalid block_id\n");
			वापस 0;
		पूर्ण

		अगर (!dev_data->block_in_reset[block_id]) अणु
			काष्ठा dbg_idle_chk_result_reg_hdr *reg_hdr;
			bool wide_bus, eval_mode, mode_match = true;
			u16 modes_buf_offset;
			u32 addr;

			reg_hdr = (काष्ठा dbg_idle_chk_result_reg_hdr *)
				  (dump_buf + offset);

			/* Check mode */
			eval_mode = GET_FIELD(reg->mode.data,
					      DBG_MODE_HDR_EVAL_MODE) > 0;
			अगर (eval_mode) अणु
				modes_buf_offset =
				    GET_FIELD(reg->mode.data,
					      DBG_MODE_HDR_MODES_BUF_OFFSET);
				mode_match =
					qed_is_mode_match(p_hwfn,
							  &modes_buf_offset);
			पूर्ण

			अगर (!mode_match)
				जारी;

			addr = GET_FIELD(reg->data,
					 DBG_IDLE_CHK_INFO_REG_ADDRESS);
			wide_bus = GET_FIELD(reg->data,
					     DBG_IDLE_CHK_INFO_REG_WIDE_BUS);

			/* Write रेजिस्टर header */
			offset += IDLE_CHK_RESULT_REG_HDR_DWORDS;
			hdr->num_dumped_info_regs++;
			स_रखो(reg_hdr, 0, माप(*reg_hdr));
			reg_hdr->size = reg->size;
			SET_FIELD(reg_hdr->data,
				  DBG_IDLE_CHK_RESULT_REG_HDR_REG_ID,
				  rule->num_cond_regs + reg_id);

			/* Write रेजिस्टर values */
			offset += qed_grc_dump_addr_range(p_hwfn,
							  p_ptt,
							  dump_buf + offset,
							  dump,
							  addr,
							  reg->size, wide_bus,
							  SPLIT_TYPE_NONE, 0);
		पूर्ण
	पूर्ण

	वापस offset;
पूर्ण

/* Dumps idle check rule entries. Returns the dumped size in dwords. */
अटल u32
qed_idle_chk_dump_rule_entries(काष्ठा qed_hwfn *p_hwfn, काष्ठा qed_ptt *p_ptt,
			       u32 *dump_buf, bool dump,
			       स्थिर काष्ठा dbg_idle_chk_rule *input_rules,
			       u32 num_input_rules, u32 *num_failing_rules)
अणु
	काष्ठा dbg_tools_data *dev_data = &p_hwfn->dbg_info;
	u32 cond_reg_values[IDLE_CHK_MAX_ENTRIES_SIZE];
	u32 i, offset = 0;
	u16 entry_id;
	u8 reg_id;

	*num_failing_rules = 0;

	क्रम (i = 0; i < num_input_rules; i++) अणु
		स्थिर काष्ठा dbg_idle_chk_cond_reg *cond_regs;
		स्थिर काष्ठा dbg_idle_chk_rule *rule;
		स्थिर जोड़ dbg_idle_chk_reg *regs;
		u16 num_reg_entries = 1;
		bool check_rule = true;
		स्थिर u32 *imm_values;

		rule = &input_rules[i];
		regs = (स्थिर जोड़ dbg_idle_chk_reg *)
			p_hwfn->dbg_arrays[BIN_BUF_DBG_IDLE_CHK_REGS].ptr +
			rule->reg_offset;
		cond_regs = &regs[0].cond_reg;
		imm_values =
		    (u32 *)p_hwfn->dbg_arrays[BIN_BUF_DBG_IDLE_CHK_IMMS].ptr +
		    rule->imm_offset;

		/* Check अगर all condition रेजिस्टर blocks are out of reset, and
		 * find maximal number of entries (all condition रेजिस्टरs that
		 * are memories must have the same size, which is > 1).
		 */
		क्रम (reg_id = 0; reg_id < rule->num_cond_regs && check_rule;
		     reg_id++) अणु
			u32 block_id =
				GET_FIELD(cond_regs[reg_id].data,
					  DBG_IDLE_CHK_COND_REG_BLOCK_ID);

			अगर (block_id >= MAX_BLOCK_ID) अणु
				DP_NOTICE(p_hwfn, "Invalid block_id\n");
				वापस 0;
			पूर्ण

			check_rule = !dev_data->block_in_reset[block_id];
			अगर (cond_regs[reg_id].num_entries > num_reg_entries)
				num_reg_entries = cond_regs[reg_id].num_entries;
		पूर्ण

		अगर (!check_rule && dump)
			जारी;

		अगर (!dump) अणु
			u32 entry_dump_size =
				qed_idle_chk_dump_failure(p_hwfn,
							  p_ptt,
							  dump_buf + offset,
							  false,
							  rule->rule_id,
							  rule,
							  0,
							  शून्य);

			offset += num_reg_entries * entry_dump_size;
			(*num_failing_rules) += num_reg_entries;
			जारी;
		पूर्ण

		/* Go over all रेजिस्टर entries (number of entries is the same
		 * क्रम all condition रेजिस्टरs).
		 */
		क्रम (entry_id = 0; entry_id < num_reg_entries; entry_id++) अणु
			u32 next_reg_offset = 0;

			/* Read current entry of all condition रेजिस्टरs */
			क्रम (reg_id = 0; reg_id < rule->num_cond_regs;
			     reg_id++) अणु
				स्थिर काष्ठा dbg_idle_chk_cond_reg *reg =
					&cond_regs[reg_id];
				u32 padded_entry_size, addr;
				bool wide_bus;

				/* Find GRC address (अगर it's a memory, the
				 * address of the specअगरic entry is calculated).
				 */
				addr = GET_FIELD(reg->data,
						 DBG_IDLE_CHK_COND_REG_ADDRESS);
				wide_bus =
				    GET_FIELD(reg->data,
					      DBG_IDLE_CHK_COND_REG_WIDE_BUS);
				अगर (reg->num_entries > 1 ||
				    reg->start_entry > 0) अणु
					padded_entry_size =
					   reg->entry_size > 1 ?
					   roundup_घात_of_two(reg->entry_size) :
					   1;
					addr += (reg->start_entry + entry_id) *
						padded_entry_size;
				पूर्ण

				/* Read रेजिस्टरs */
				अगर (next_reg_offset + reg->entry_size >=
				    IDLE_CHK_MAX_ENTRIES_SIZE) अणु
					DP_NOTICE(p_hwfn,
						  "idle check registers entry is too large\n");
					वापस 0;
				पूर्ण

				next_reg_offset +=
				    qed_grc_dump_addr_range(p_hwfn, p_ptt,
							    cond_reg_values +
							    next_reg_offset,
							    dump, addr,
							    reg->entry_size,
							    wide_bus,
							    SPLIT_TYPE_NONE, 0);
			पूर्ण

			/* Call rule condition function.
			 * If वापसs true, it's a failure.
			 */
			अगर ((*cond_arr[rule->cond_id]) (cond_reg_values,
							imm_values)) अणु
				offset += qed_idle_chk_dump_failure(p_hwfn,
							p_ptt,
							dump_buf + offset,
							dump,
							rule->rule_id,
							rule,
							entry_id,
							cond_reg_values);
				(*num_failing_rules)++;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस offset;
पूर्ण

/* Perक्रमms Idle Check Dump to the specअगरied buffer.
 * Returns the dumped size in dwords.
 */
अटल u32 qed_idle_chk_dump(काष्ठा qed_hwfn *p_hwfn,
			     काष्ठा qed_ptt *p_ptt, u32 *dump_buf, bool dump)
अणु
	काष्ठा virt_mem_desc *dbg_buf =
	    &p_hwfn->dbg_arrays[BIN_BUF_DBG_IDLE_CHK_RULES];
	u32 num_failing_rules_offset, offset = 0,
	    input_offset = 0, num_failing_rules = 0;

	/* Dump global params  - 1 must match below amount of params */
	offset += qed_dump_common_global_params(p_hwfn,
						p_ptt,
						dump_buf + offset, dump, 1);
	offset += qed_dump_str_param(dump_buf + offset,
				     dump, "dump-type", "idle-chk");

	/* Dump idle check section header with a single parameter */
	offset += qed_dump_section_hdr(dump_buf + offset, dump, "idle_chk", 1);
	num_failing_rules_offset = offset;
	offset += qed_dump_num_param(dump_buf + offset, dump, "num_rules", 0);

	जबतक (input_offset < BYTES_TO_DWORDS(dbg_buf->size)) अणु
		स्थिर काष्ठा dbg_idle_chk_cond_hdr *cond_hdr =
		    (स्थिर काष्ठा dbg_idle_chk_cond_hdr *)dbg_buf->ptr +
		    input_offset++;
		bool eval_mode, mode_match = true;
		u32 curr_failing_rules;
		u16 modes_buf_offset;

		/* Check mode */
		eval_mode = GET_FIELD(cond_hdr->mode.data,
				      DBG_MODE_HDR_EVAL_MODE) > 0;
		अगर (eval_mode) अणु
			modes_buf_offset =
				GET_FIELD(cond_hdr->mode.data,
					  DBG_MODE_HDR_MODES_BUF_OFFSET);
			mode_match = qed_is_mode_match(p_hwfn,
						       &modes_buf_offset);
		पूर्ण

		अगर (mode_match) अणु
			स्थिर काष्ठा dbg_idle_chk_rule *rule =
			    (स्थिर काष्ठा dbg_idle_chk_rule *)((u32 *)
							       dbg_buf->ptr
							       + input_offset);
			u32 num_input_rules =
				cond_hdr->data_size / IDLE_CHK_RULE_SIZE_DWORDS;
			offset +=
			    qed_idle_chk_dump_rule_entries(p_hwfn,
							   p_ptt,
							   dump_buf +
							   offset,
							   dump,
							   rule,
							   num_input_rules,
							   &curr_failing_rules);
			num_failing_rules += curr_failing_rules;
		पूर्ण

		input_offset += cond_hdr->data_size;
	पूर्ण

	/* Overग_लिखो num_rules parameter */
	अगर (dump)
		qed_dump_num_param(dump_buf + num_failing_rules_offset,
				   dump, "num_rules", num_failing_rules);

	/* Dump last section */
	offset += qed_dump_last_section(dump_buf, offset, dump);

	वापस offset;
पूर्ण

/* Finds the meta data image in NVRAM */
अटल क्रमागत dbg_status qed_find_nvram_image(काष्ठा qed_hwfn *p_hwfn,
					    काष्ठा qed_ptt *p_ptt,
					    u32 image_type,
					    u32 *nvram_offset_bytes,
					    u32 *nvram_size_bytes)
अणु
	u32 ret_mcp_resp, ret_mcp_param, ret_txn_size;
	काष्ठा mcp_file_att file_att;
	पूर्णांक nvm_result;

	/* Call NVRAM get file command */
	nvm_result = qed_mcp_nvm_rd_cmd(p_hwfn,
					p_ptt,
					DRV_MSG_CODE_NVM_GET_खाता_ATT,
					image_type,
					&ret_mcp_resp,
					&ret_mcp_param,
					&ret_txn_size, (u32 *)&file_att);

	/* Check response */
	अगर (nvm_result ||
	    (ret_mcp_resp & FW_MSG_CODE_MASK) != FW_MSG_CODE_NVM_OK)
		वापस DBG_STATUS_NVRAM_GET_IMAGE_FAILED;

	/* Update वापस values */
	*nvram_offset_bytes = file_att.nvm_start_addr;
	*nvram_size_bytes = file_att.len;

	DP_VERBOSE(p_hwfn,
		   QED_MSG_DEBUG,
		   "find_nvram_image: found NVRAM image of type %d in NVRAM offset %d bytes with size %d bytes\n",
		   image_type, *nvram_offset_bytes, *nvram_size_bytes);

	/* Check alignment */
	अगर (*nvram_size_bytes & 0x3)
		वापस DBG_STATUS_NON_ALIGNED_NVRAM_IMAGE;

	वापस DBG_STATUS_OK;
पूर्ण

/* Reads data from NVRAM */
अटल क्रमागत dbg_status qed_nvram_पढ़ो(काष्ठा qed_hwfn *p_hwfn,
				      काष्ठा qed_ptt *p_ptt,
				      u32 nvram_offset_bytes,
				      u32 nvram_size_bytes, u32 *ret_buf)
अणु
	u32 ret_mcp_resp, ret_mcp_param, ret_पढ़ो_size, bytes_to_copy;
	s32 bytes_left = nvram_size_bytes;
	u32 पढ़ो_offset = 0, param = 0;

	DP_VERBOSE(p_hwfn,
		   QED_MSG_DEBUG,
		   "nvram_read: reading image of size %d bytes from NVRAM\n",
		   nvram_size_bytes);

	करो अणु
		bytes_to_copy =
		    (bytes_left >
		     MCP_DRV_NVM_BUF_LEN) ? MCP_DRV_NVM_BUF_LEN : bytes_left;

		/* Call NVRAM पढ़ो command */
		SET_MFW_FIELD(param,
			      DRV_MB_PARAM_NVM_OFFSET,
			      nvram_offset_bytes + पढ़ो_offset);
		SET_MFW_FIELD(param, DRV_MB_PARAM_NVM_LEN, bytes_to_copy);
		अगर (qed_mcp_nvm_rd_cmd(p_hwfn, p_ptt,
				       DRV_MSG_CODE_NVM_READ_NVRAM, param,
				       &ret_mcp_resp,
				       &ret_mcp_param, &ret_पढ़ो_size,
				       (u32 *)((u8 *)ret_buf + पढ़ो_offset)))
			वापस DBG_STATUS_NVRAM_READ_FAILED;

		/* Check response */
		अगर ((ret_mcp_resp & FW_MSG_CODE_MASK) != FW_MSG_CODE_NVM_OK)
			वापस DBG_STATUS_NVRAM_READ_FAILED;

		/* Update पढ़ो offset */
		पढ़ो_offset += ret_पढ़ो_size;
		bytes_left -= ret_पढ़ो_size;
	पूर्ण जबतक (bytes_left > 0);

	वापस DBG_STATUS_OK;
पूर्ण

/* Get info on the MCP Trace data in the scratchpad:
 * - trace_data_grc_addr (OUT): trace data GRC address in bytes
 * - trace_data_size (OUT): trace data size in bytes (without the header)
 */
अटल क्रमागत dbg_status qed_mcp_trace_get_data_info(काष्ठा qed_hwfn *p_hwfn,
						   काष्ठा qed_ptt *p_ptt,
						   u32 *trace_data_grc_addr,
						   u32 *trace_data_size)
अणु
	u32 spad_trace_offsize, signature;

	/* Read trace section offsize काष्ठाure from MCP scratchpad */
	spad_trace_offsize = qed_rd(p_hwfn, p_ptt, MCP_SPAD_TRACE_OFFSIZE_ADDR);

	/* Extract trace section address from offsize (in scratchpad) */
	*trace_data_grc_addr =
		MCP_REG_SCRATCH + SECTION_OFFSET(spad_trace_offsize);

	/* Read signature from MCP trace section */
	signature = qed_rd(p_hwfn, p_ptt,
			   *trace_data_grc_addr +
			   दुरत्व(काष्ठा mcp_trace, signature));

	अगर (signature != MFW_TRACE_SIGNATURE)
		वापस DBG_STATUS_INVALID_TRACE_SIGNATURE;

	/* Read trace size from MCP trace section */
	*trace_data_size = qed_rd(p_hwfn,
				  p_ptt,
				  *trace_data_grc_addr +
				  दुरत्व(काष्ठा mcp_trace, size));

	वापस DBG_STATUS_OK;
पूर्ण

/* Reads MCP trace meta data image from NVRAM
 * - running_bundle_id (OUT): running bundle ID (invalid when loaded from file)
 * - trace_meta_offset (OUT): trace meta offset in NVRAM in bytes (invalid when
 *			      loaded from file).
 * - trace_meta_size (OUT):   size in bytes of the trace meta data.
 */
अटल क्रमागत dbg_status qed_mcp_trace_get_meta_info(काष्ठा qed_hwfn *p_hwfn,
						   काष्ठा qed_ptt *p_ptt,
						   u32 trace_data_size_bytes,
						   u32 *running_bundle_id,
						   u32 *trace_meta_offset,
						   u32 *trace_meta_size)
अणु
	u32 spad_trace_offsize, nvram_image_type, running_mfw_addr;

	/* Read MCP trace section offsize काष्ठाure from MCP scratchpad */
	spad_trace_offsize = qed_rd(p_hwfn, p_ptt, MCP_SPAD_TRACE_OFFSIZE_ADDR);

	/* Find running bundle ID */
	running_mfw_addr =
		MCP_REG_SCRATCH + SECTION_OFFSET(spad_trace_offsize) +
		QED_SECTION_SIZE(spad_trace_offsize) + trace_data_size_bytes;
	*running_bundle_id = qed_rd(p_hwfn, p_ptt, running_mfw_addr);
	अगर (*running_bundle_id > 1)
		वापस DBG_STATUS_INVALID_NVRAM_BUNDLE;

	/* Find image in NVRAM */
	nvram_image_type =
	    (*running_bundle_id ==
	     सूची_ID_1) ? NVM_TYPE_MFW_TRACE1 : NVM_TYPE_MFW_TRACE2;
	वापस qed_find_nvram_image(p_hwfn,
				    p_ptt,
				    nvram_image_type,
				    trace_meta_offset, trace_meta_size);
पूर्ण

/* Reads the MCP Trace meta data from NVRAM पूर्णांकo the specअगरied buffer */
अटल क्रमागत dbg_status qed_mcp_trace_पढ़ो_meta(काष्ठा qed_hwfn *p_hwfn,
					       काष्ठा qed_ptt *p_ptt,
					       u32 nvram_offset_in_bytes,
					       u32 size_in_bytes, u32 *buf)
अणु
	u8 modules_num, module_len, i, *byte_buf = (u8 *)buf;
	क्रमागत dbg_status status;
	u32 signature;

	/* Read meta data from NVRAM */
	status = qed_nvram_पढ़ो(p_hwfn,
				p_ptt,
				nvram_offset_in_bytes, size_in_bytes, buf);
	अगर (status != DBG_STATUS_OK)
		वापस status;

	/* Extract and check first signature */
	signature = qed_पढ़ो_unaligned_dword(byte_buf);
	byte_buf += माप(signature);
	अगर (signature != NVM_MAGIC_VALUE)
		वापस DBG_STATUS_INVALID_TRACE_SIGNATURE;

	/* Extract number of modules */
	modules_num = *(byte_buf++);

	/* Skip all modules */
	क्रम (i = 0; i < modules_num; i++) अणु
		module_len = *(byte_buf++);
		byte_buf += module_len;
	पूर्ण

	/* Extract and check second signature */
	signature = qed_पढ़ो_unaligned_dword(byte_buf);
	byte_buf += माप(signature);
	अगर (signature != NVM_MAGIC_VALUE)
		वापस DBG_STATUS_INVALID_TRACE_SIGNATURE;

	वापस DBG_STATUS_OK;
पूर्ण

/* Dump MCP Trace */
अटल क्रमागत dbg_status qed_mcp_trace_dump(काष्ठा qed_hwfn *p_hwfn,
					  काष्ठा qed_ptt *p_ptt,
					  u32 *dump_buf,
					  bool dump, u32 *num_dumped_dwords)
अणु
	u32 trace_data_grc_addr, trace_data_size_bytes, trace_data_size_dwords;
	u32 trace_meta_size_dwords = 0, running_bundle_id, offset = 0;
	u32 trace_meta_offset_bytes = 0, trace_meta_size_bytes = 0;
	क्रमागत dbg_status status;
	पूर्णांक halted = 0;
	bool use_mfw;

	*num_dumped_dwords = 0;

	use_mfw = !qed_grc_get_param(p_hwfn, DBG_GRC_PARAM_NO_MCP);

	/* Get trace data info */
	status = qed_mcp_trace_get_data_info(p_hwfn,
					     p_ptt,
					     &trace_data_grc_addr,
					     &trace_data_size_bytes);
	अगर (status != DBG_STATUS_OK)
		वापस status;

	/* Dump global params */
	offset += qed_dump_common_global_params(p_hwfn,
						p_ptt,
						dump_buf + offset, dump, 1);
	offset += qed_dump_str_param(dump_buf + offset,
				     dump, "dump-type", "mcp-trace");

	/* Halt MCP जबतक पढ़ोing from scratchpad so the पढ़ो data will be
	 * consistent. अगर halt fails, MCP trace is taken anyway, with a small
	 * risk that it may be corrupt.
	 */
	अगर (dump && use_mfw) अणु
		halted = !qed_mcp_halt(p_hwfn, p_ptt);
		अगर (!halted)
			DP_NOTICE(p_hwfn, "MCP halt failed!\n");
	पूर्ण

	/* Find trace data size */
	trace_data_size_dwords =
	    DIV_ROUND_UP(trace_data_size_bytes + माप(काष्ठा mcp_trace),
			 BYTES_IN_DWORD);

	/* Dump trace data section header and param */
	offset += qed_dump_section_hdr(dump_buf + offset,
				       dump, "mcp_trace_data", 1);
	offset += qed_dump_num_param(dump_buf + offset,
				     dump, "size", trace_data_size_dwords);

	/* Read trace data from scratchpad पूर्णांकo dump buffer */
	offset += qed_grc_dump_addr_range(p_hwfn,
					  p_ptt,
					  dump_buf + offset,
					  dump,
					  BYTES_TO_DWORDS(trace_data_grc_addr),
					  trace_data_size_dwords, false,
					  SPLIT_TYPE_NONE, 0);

	/* Resume MCP (only अगर halt succeeded) */
	अगर (halted && qed_mcp_resume(p_hwfn, p_ptt))
		DP_NOTICE(p_hwfn, "Failed to resume MCP after halt!\n");

	/* Dump trace meta section header */
	offset += qed_dump_section_hdr(dump_buf + offset,
				       dump, "mcp_trace_meta", 1);

	/* If MCP Trace meta size parameter was set, use it.
	 * Otherwise, पढ़ो trace meta.
	 * trace_meta_size_bytes is dword-aligned.
	 */
	trace_meta_size_bytes =
		qed_grc_get_param(p_hwfn, DBG_GRC_PARAM_MCP_TRACE_META_SIZE);
	अगर ((!trace_meta_size_bytes || dump) && use_mfw)
		status = qed_mcp_trace_get_meta_info(p_hwfn,
						     p_ptt,
						     trace_data_size_bytes,
						     &running_bundle_id,
						     &trace_meta_offset_bytes,
						     &trace_meta_size_bytes);
	अगर (status == DBG_STATUS_OK)
		trace_meta_size_dwords = BYTES_TO_DWORDS(trace_meta_size_bytes);

	/* Dump trace meta size param */
	offset += qed_dump_num_param(dump_buf + offset,
				     dump, "size", trace_meta_size_dwords);

	/* Read trace meta image पूर्णांकo dump buffer */
	अगर (dump && trace_meta_size_dwords)
		status = qed_mcp_trace_पढ़ो_meta(p_hwfn,
						 p_ptt,
						 trace_meta_offset_bytes,
						 trace_meta_size_bytes,
						 dump_buf + offset);
	अगर (status == DBG_STATUS_OK)
		offset += trace_meta_size_dwords;

	/* Dump last section */
	offset += qed_dump_last_section(dump_buf, offset, dump);

	*num_dumped_dwords = offset;

	/* If no mcp access, indicate that the dump करोesn't contain the meta
	 * data from NVRAM.
	 */
	वापस use_mfw ? status : DBG_STATUS_NVRAM_GET_IMAGE_FAILED;
पूर्ण

/* Dump GRC FIFO */
अटल क्रमागत dbg_status qed_reg_fअगरo_dump(काष्ठा qed_hwfn *p_hwfn,
					 काष्ठा qed_ptt *p_ptt,
					 u32 *dump_buf,
					 bool dump, u32 *num_dumped_dwords)
अणु
	u32 dwords_पढ़ो, size_param_offset, offset = 0, addr, len;
	bool fअगरo_has_data;

	*num_dumped_dwords = 0;

	/* Dump global params */
	offset += qed_dump_common_global_params(p_hwfn,
						p_ptt,
						dump_buf + offset, dump, 1);
	offset += qed_dump_str_param(dump_buf + offset,
				     dump, "dump-type", "reg-fifo");

	/* Dump fअगरo data section header and param. The size param is 0 क्रम
	 * now, and is overwritten after पढ़ोing the FIFO.
	 */
	offset += qed_dump_section_hdr(dump_buf + offset,
				       dump, "reg_fifo_data", 1);
	size_param_offset = offset;
	offset += qed_dump_num_param(dump_buf + offset, dump, "size", 0);

	अगर (!dump) अणु
		/* FIFO max size is REG_FIFO_DEPTH_DWORDS. There is no way to
		 * test how much data is available, except क्रम पढ़ोing it.
		 */
		offset += REG_FIFO_DEPTH_DWORDS;
		जाओ out;
	पूर्ण

	fअगरo_has_data = qed_rd(p_hwfn, p_ptt,
			       GRC_REG_TRACE_FIFO_VALID_DATA) > 0;

	/* Pull available data from fअगरo. Use DMAE since this is widebus memory
	 * and must be accessed atomically. Test क्रम dwords_पढ़ो not passing
	 * buffer size since more entries could be added to the buffer as we are
	 * emptying it.
	 */
	addr = BYTES_TO_DWORDS(GRC_REG_TRACE_FIFO);
	len = REG_FIFO_ELEMENT_DWORDS;
	क्रम (dwords_पढ़ो = 0;
	     fअगरo_has_data && dwords_पढ़ो < REG_FIFO_DEPTH_DWORDS;
	     dwords_पढ़ो += REG_FIFO_ELEMENT_DWORDS) अणु
		offset += qed_grc_dump_addr_range(p_hwfn,
						  p_ptt,
						  dump_buf + offset,
						  true,
						  addr,
						  len,
						  true, SPLIT_TYPE_NONE,
						  0);
		fअगरo_has_data = qed_rd(p_hwfn, p_ptt,
				       GRC_REG_TRACE_FIFO_VALID_DATA) > 0;
	पूर्ण

	qed_dump_num_param(dump_buf + size_param_offset, dump, "size",
			   dwords_पढ़ो);
out:
	/* Dump last section */
	offset += qed_dump_last_section(dump_buf, offset, dump);

	*num_dumped_dwords = offset;

	वापस DBG_STATUS_OK;
पूर्ण

/* Dump IGU FIFO */
अटल क्रमागत dbg_status qed_igu_fअगरo_dump(काष्ठा qed_hwfn *p_hwfn,
					 काष्ठा qed_ptt *p_ptt,
					 u32 *dump_buf,
					 bool dump, u32 *num_dumped_dwords)
अणु
	u32 dwords_पढ़ो, size_param_offset, offset = 0, addr, len;
	bool fअगरo_has_data;

	*num_dumped_dwords = 0;

	/* Dump global params */
	offset += qed_dump_common_global_params(p_hwfn,
						p_ptt,
						dump_buf + offset, dump, 1);
	offset += qed_dump_str_param(dump_buf + offset,
				     dump, "dump-type", "igu-fifo");

	/* Dump fअगरo data section header and param. The size param is 0 क्रम
	 * now, and is overwritten after पढ़ोing the FIFO.
	 */
	offset += qed_dump_section_hdr(dump_buf + offset,
				       dump, "igu_fifo_data", 1);
	size_param_offset = offset;
	offset += qed_dump_num_param(dump_buf + offset, dump, "size", 0);

	अगर (!dump) अणु
		/* FIFO max size is IGU_FIFO_DEPTH_DWORDS. There is no way to
		 * test how much data is available, except क्रम पढ़ोing it.
		 */
		offset += IGU_FIFO_DEPTH_DWORDS;
		जाओ out;
	पूर्ण

	fअगरo_has_data = qed_rd(p_hwfn, p_ptt,
			       IGU_REG_ERROR_HANDLING_DATA_VALID) > 0;

	/* Pull available data from fअगरo. Use DMAE since this is widebus memory
	 * and must be accessed atomically. Test क्रम dwords_पढ़ो not passing
	 * buffer size since more entries could be added to the buffer as we are
	 * emptying it.
	 */
	addr = BYTES_TO_DWORDS(IGU_REG_ERROR_HANDLING_MEMORY);
	len = IGU_FIFO_ELEMENT_DWORDS;
	क्रम (dwords_पढ़ो = 0;
	     fअगरo_has_data && dwords_पढ़ो < IGU_FIFO_DEPTH_DWORDS;
	     dwords_पढ़ो += IGU_FIFO_ELEMENT_DWORDS) अणु
		offset += qed_grc_dump_addr_range(p_hwfn,
						  p_ptt,
						  dump_buf + offset,
						  true,
						  addr,
						  len,
						  true, SPLIT_TYPE_NONE,
						  0);
		fअगरo_has_data = qed_rd(p_hwfn, p_ptt,
				       IGU_REG_ERROR_HANDLING_DATA_VALID) > 0;
	पूर्ण

	qed_dump_num_param(dump_buf + size_param_offset, dump, "size",
			   dwords_पढ़ो);
out:
	/* Dump last section */
	offset += qed_dump_last_section(dump_buf, offset, dump);

	*num_dumped_dwords = offset;

	वापस DBG_STATUS_OK;
पूर्ण

/* Protection Override dump */
अटल क्रमागत dbg_status qed_protection_override_dump(काष्ठा qed_hwfn *p_hwfn,
						    काष्ठा qed_ptt *p_ptt,
						    u32 *dump_buf,
						    bool dump,
						    u32 *num_dumped_dwords)
अणु
	u32 size_param_offset, override_winकरोw_dwords, offset = 0, addr;

	*num_dumped_dwords = 0;

	/* Dump global params */
	offset += qed_dump_common_global_params(p_hwfn,
						p_ptt,
						dump_buf + offset, dump, 1);
	offset += qed_dump_str_param(dump_buf + offset,
				     dump, "dump-type", "protection-override");

	/* Dump data section header and param. The size param is 0 क्रम now,
	 * and is overwritten after पढ़ोing the data.
	 */
	offset += qed_dump_section_hdr(dump_buf + offset,
				       dump, "protection_override_data", 1);
	size_param_offset = offset;
	offset += qed_dump_num_param(dump_buf + offset, dump, "size", 0);

	अगर (!dump) अणु
		offset += PROTECTION_OVERRIDE_DEPTH_DWORDS;
		जाओ out;
	पूर्ण

	/* Add override winकरोw info to buffer */
	override_winकरोw_dwords =
		qed_rd(p_hwfn, p_ptt, GRC_REG_NUMBER_VALID_OVERRIDE_WINDOW) *
		PROTECTION_OVERRIDE_ELEMENT_DWORDS;
	अगर (override_winकरोw_dwords) अणु
		addr = BYTES_TO_DWORDS(GRC_REG_PROTECTION_OVERRIDE_WINDOW);
		offset += qed_grc_dump_addr_range(p_hwfn,
						  p_ptt,
						  dump_buf + offset,
						  true,
						  addr,
						  override_winकरोw_dwords,
						  true, SPLIT_TYPE_NONE, 0);
		qed_dump_num_param(dump_buf + size_param_offset, dump, "size",
				   override_winकरोw_dwords);
	पूर्ण
out:
	/* Dump last section */
	offset += qed_dump_last_section(dump_buf, offset, dump);

	*num_dumped_dwords = offset;

	वापस DBG_STATUS_OK;
पूर्ण

/* Perक्रमms FW Asserts Dump to the specअगरied buffer.
 * Returns the dumped size in dwords.
 */
अटल u32 qed_fw_निश्चितs_dump(काष्ठा qed_hwfn *p_hwfn,
			       काष्ठा qed_ptt *p_ptt, u32 *dump_buf, bool dump)
अणु
	काष्ठा dbg_tools_data *dev_data = &p_hwfn->dbg_info;
	काष्ठा fw_निश्चितs_ram_section *निश्चितs;
	अक्षर storm_letter_str[2] = "?";
	काष्ठा fw_info fw_info;
	u32 offset = 0;
	u8 storm_id;

	/* Dump global params */
	offset += qed_dump_common_global_params(p_hwfn,
						p_ptt,
						dump_buf + offset, dump, 1);
	offset += qed_dump_str_param(dump_buf + offset,
				     dump, "dump-type", "fw-asserts");

	/* Find Storm dump size */
	क्रम (storm_id = 0; storm_id < MAX_DBG_STORMS; storm_id++) अणु
		u32 fw_निश्चितs_section_addr, next_list_idx_addr, next_list_idx;
		काष्ठा storm_defs *storm = &s_storm_defs[storm_id];
		u32 last_list_idx, addr;

		अगर (dev_data->block_in_reset[storm->sem_block_id])
			जारी;

		/* Read FW info क्रम the current Storm */
		qed_पढ़ो_storm_fw_info(p_hwfn, p_ptt, storm_id, &fw_info);

		निश्चितs = &fw_info.fw_निश्चितs_section;

		/* Dump FW Asserts section header and params */
		storm_letter_str[0] = storm->letter;
		offset += qed_dump_section_hdr(dump_buf + offset,
					       dump, "fw_asserts", 2);
		offset += qed_dump_str_param(dump_buf + offset,
					     dump, "storm", storm_letter_str);
		offset += qed_dump_num_param(dump_buf + offset,
					     dump,
					     "size",
					     निश्चितs->list_element_dword_size);

		/* Read and dump FW Asserts data */
		अगर (!dump) अणु
			offset += निश्चितs->list_element_dword_size;
			जारी;
		पूर्ण

		addr = le16_to_cpu(निश्चितs->section_ram_line_offset);
		fw_निश्चितs_section_addr = storm->sem_fast_mem_addr +
					  SEM_FAST_REG_INT_RAM +
					  RAM_LINES_TO_BYTES(addr);

		next_list_idx_addr = fw_निश्चितs_section_addr +
			DWORDS_TO_BYTES(निश्चितs->list_next_index_dword_offset);
		next_list_idx = qed_rd(p_hwfn, p_ptt, next_list_idx_addr);
		last_list_idx = (next_list_idx > 0 ?
				 next_list_idx :
				 निश्चितs->list_num_elements) - 1;
		addr = BYTES_TO_DWORDS(fw_निश्चितs_section_addr) +
		       निश्चितs->list_dword_offset +
		       last_list_idx * निश्चितs->list_element_dword_size;
		offset +=
		    qed_grc_dump_addr_range(p_hwfn, p_ptt,
					    dump_buf + offset,
					    dump, addr,
					    निश्चितs->list_element_dword_size,
						  false, SPLIT_TYPE_NONE, 0);
	पूर्ण

	/* Dump last section */
	offset += qed_dump_last_section(dump_buf, offset, dump);

	वापस offset;
पूर्ण

/* Dumps the specअगरied ILT pages to the specअगरied buffer.
 * Returns the dumped size in dwords.
 */
अटल u32 qed_ilt_dump_pages_range(u32 *dump_buf,
				    bool dump,
				    u32 start_page_id,
				    u32 num_pages,
				    काष्ठा phys_mem_desc *ilt_pages,
				    bool dump_page_ids)
अणु
	u32 page_id, end_page_id, offset = 0;

	अगर (num_pages == 0)
		वापस offset;

	end_page_id = start_page_id + num_pages - 1;

	क्रम (page_id = start_page_id; page_id <= end_page_id; page_id++) अणु
		काष्ठा phys_mem_desc *mem_desc = &ilt_pages[page_id];

		/**
		 *
		 * अगर (page_id >= ->p_cxt_mngr->ilt_shaकरोw_size)
		 *     अवरोध;
		 */

		अगर (!ilt_pages[page_id].virt_addr)
			जारी;

		अगर (dump_page_ids) अणु
			/* Copy page ID to dump buffer */
			अगर (dump)
				*(dump_buf + offset) = page_id;
			offset++;
		पूर्ण अन्यथा अणु
			/* Copy page memory to dump buffer */
			अगर (dump)
				स_नकल(dump_buf + offset,
				       mem_desc->virt_addr, mem_desc->size);
			offset += BYTES_TO_DWORDS(mem_desc->size);
		पूर्ण
	पूर्ण

	वापस offset;
पूर्ण

/* Dumps a section containing the dumped ILT pages.
 * Returns the dumped size in dwords.
 */
अटल u32 qed_ilt_dump_pages_section(काष्ठा qed_hwfn *p_hwfn,
				      u32 *dump_buf,
				      bool dump,
				      u32 valid_conn_pf_pages,
				      u32 valid_conn_vf_pages,
				      काष्ठा phys_mem_desc *ilt_pages,
				      bool dump_page_ids)
अणु
	काष्ठा qed_ilt_client_cfg *clients = p_hwfn->p_cxt_mngr->clients;
	u32 pf_start_line, start_page_id, offset = 0;
	u32 cdut_pf_init_pages, cdut_vf_init_pages;
	u32 cdut_pf_work_pages, cdut_vf_work_pages;
	u32 base_data_offset, size_param_offset;
	u32 cdut_pf_pages, cdut_vf_pages;
	स्थिर अक्षर *section_name;
	u8 i;

	section_name = dump_page_ids ? "ilt_page_ids" : "ilt_page_mem";
	cdut_pf_init_pages = qed_get_cdut_num_pf_init_pages(p_hwfn);
	cdut_vf_init_pages = qed_get_cdut_num_vf_init_pages(p_hwfn);
	cdut_pf_work_pages = qed_get_cdut_num_pf_work_pages(p_hwfn);
	cdut_vf_work_pages = qed_get_cdut_num_vf_work_pages(p_hwfn);
	cdut_pf_pages = cdut_pf_init_pages + cdut_pf_work_pages;
	cdut_vf_pages = cdut_vf_init_pages + cdut_vf_work_pages;
	pf_start_line = p_hwfn->p_cxt_mngr->pf_start_line;

	offset +=
	    qed_dump_section_hdr(dump_buf + offset, dump, section_name, 1);

	/* Dump size parameter (0 क्रम now, overwritten with real size later) */
	size_param_offset = offset;
	offset += qed_dump_num_param(dump_buf + offset, dump, "size", 0);
	base_data_offset = offset;

	/* CDUC pages are ordered as follows:
	 * - PF pages - valid section (included in PF connection type mapping)
	 * - PF pages - invalid section (not dumped)
	 * - For each VF in the PF:
	 *   - VF pages - valid section (included in VF connection type mapping)
	 *   - VF pages - invalid section (not dumped)
	 */
	अगर (qed_grc_get_param(p_hwfn, DBG_GRC_PARAM_DUMP_ILT_CDUC)) अणु
		/* Dump connection PF pages */
		start_page_id = clients[ILT_CLI_CDUC].first.val - pf_start_line;
		offset += qed_ilt_dump_pages_range(dump_buf + offset,
						   dump,
						   start_page_id,
						   valid_conn_pf_pages,
						   ilt_pages, dump_page_ids);

		/* Dump connection VF pages */
		start_page_id += clients[ILT_CLI_CDUC].pf_total_lines;
		क्रम (i = 0; i < p_hwfn->p_cxt_mngr->vf_count;
		     i++, start_page_id += clients[ILT_CLI_CDUC].vf_total_lines)
			offset += qed_ilt_dump_pages_range(dump_buf + offset,
							   dump,
							   start_page_id,
							   valid_conn_vf_pages,
							   ilt_pages,
							   dump_page_ids);
	पूर्ण

	/* CDUT pages are ordered as follows:
	 * - PF init pages (not dumped)
	 * - PF work pages
	 * - For each VF in the PF:
	 *   - VF init pages (not dumped)
	 *   - VF work pages
	 */
	अगर (qed_grc_get_param(p_hwfn, DBG_GRC_PARAM_DUMP_ILT_CDUT)) अणु
		/* Dump task PF pages */
		start_page_id = clients[ILT_CLI_CDUT].first.val +
		    cdut_pf_init_pages - pf_start_line;
		offset += qed_ilt_dump_pages_range(dump_buf + offset,
						   dump,
						   start_page_id,
						   cdut_pf_work_pages,
						   ilt_pages, dump_page_ids);

		/* Dump task VF pages */
		start_page_id = clients[ILT_CLI_CDUT].first.val +
		    cdut_pf_pages + cdut_vf_init_pages - pf_start_line;
		क्रम (i = 0; i < p_hwfn->p_cxt_mngr->vf_count;
		     i++, start_page_id += cdut_vf_pages)
			offset += qed_ilt_dump_pages_range(dump_buf + offset,
							   dump,
							   start_page_id,
							   cdut_vf_work_pages,
							   ilt_pages,
							   dump_page_ids);
	पूर्ण

	/* Overग_लिखो size param */
	अगर (dump)
		qed_dump_num_param(dump_buf + size_param_offset,
				   dump, "size", offset - base_data_offset);

	वापस offset;
पूर्ण

/* Perक्रमms ILT Dump to the specअगरied buffer.
 * Returns the dumped size in dwords.
 */
अटल u32 qed_ilt_dump(काष्ठा qed_hwfn *p_hwfn,
			काष्ठा qed_ptt *p_ptt, u32 *dump_buf, bool dump)
अणु
	काष्ठा qed_ilt_client_cfg *clients = p_hwfn->p_cxt_mngr->clients;
	u32 valid_conn_vf_cids, valid_conn_vf_pages, offset = 0;
	u32 valid_conn_pf_cids, valid_conn_pf_pages, num_pages;
	u32 num_cids_per_page, conn_ctx_size;
	u32 cduc_page_size, cdut_page_size;
	काष्ठा phys_mem_desc *ilt_pages;
	u8 conn_type;

	cduc_page_size = 1 <<
	    (clients[ILT_CLI_CDUC].p_size.val + PXP_ILT_PAGE_SIZE_NUM_BITS_MIN);
	cdut_page_size = 1 <<
	    (clients[ILT_CLI_CDUT].p_size.val + PXP_ILT_PAGE_SIZE_NUM_BITS_MIN);
	conn_ctx_size = p_hwfn->p_cxt_mngr->conn_ctx_size;
	num_cids_per_page = (पूर्णांक)(cduc_page_size / conn_ctx_size);
	ilt_pages = p_hwfn->p_cxt_mngr->ilt_shaकरोw;

	/* Dump global params - 22 must match number of params below */
	offset += qed_dump_common_global_params(p_hwfn, p_ptt,
						dump_buf + offset, dump, 22);
	offset += qed_dump_str_param(dump_buf + offset,
				     dump, "dump-type", "ilt-dump");
	offset += qed_dump_num_param(dump_buf + offset,
				     dump,
				     "cduc-page-size", cduc_page_size);
	offset += qed_dump_num_param(dump_buf + offset,
				     dump,
				     "cduc-first-page-id",
				     clients[ILT_CLI_CDUC].first.val);
	offset += qed_dump_num_param(dump_buf + offset,
				     dump,
				     "cduc-last-page-id",
				     clients[ILT_CLI_CDUC].last.val);
	offset += qed_dump_num_param(dump_buf + offset,
				     dump,
				     "cduc-num-pf-pages",
				     clients
				     [ILT_CLI_CDUC].pf_total_lines);
	offset += qed_dump_num_param(dump_buf + offset,
				     dump,
				     "cduc-num-vf-pages",
				     clients
				     [ILT_CLI_CDUC].vf_total_lines);
	offset += qed_dump_num_param(dump_buf + offset,
				     dump,
				     "max-conn-ctx-size",
				     conn_ctx_size);
	offset += qed_dump_num_param(dump_buf + offset,
				     dump,
				     "cdut-page-size", cdut_page_size);
	offset += qed_dump_num_param(dump_buf + offset,
				     dump,
				     "cdut-first-page-id",
				     clients[ILT_CLI_CDUT].first.val);
	offset += qed_dump_num_param(dump_buf + offset,
				     dump,
				     "cdut-last-page-id",
				     clients[ILT_CLI_CDUT].last.val);
	offset += qed_dump_num_param(dump_buf + offset,
				     dump,
				     "cdut-num-pf-init-pages",
				     qed_get_cdut_num_pf_init_pages(p_hwfn));
	offset += qed_dump_num_param(dump_buf + offset,
				     dump,
				     "cdut-num-vf-init-pages",
				     qed_get_cdut_num_vf_init_pages(p_hwfn));
	offset += qed_dump_num_param(dump_buf + offset,
				     dump,
				     "cdut-num-pf-work-pages",
				     qed_get_cdut_num_pf_work_pages(p_hwfn));
	offset += qed_dump_num_param(dump_buf + offset,
				     dump,
				     "cdut-num-vf-work-pages",
				     qed_get_cdut_num_vf_work_pages(p_hwfn));
	offset += qed_dump_num_param(dump_buf + offset,
				     dump,
				     "max-task-ctx-size",
				     p_hwfn->p_cxt_mngr->task_ctx_size);
	offset += qed_dump_num_param(dump_buf + offset,
				     dump,
				     "task-type-id",
				     p_hwfn->p_cxt_mngr->task_type_id);
	offset += qed_dump_num_param(dump_buf + offset,
				     dump,
				     "first-vf-id-in-pf",
				     p_hwfn->p_cxt_mngr->first_vf_in_pf);
	offset += /* 18 */ qed_dump_num_param(dump_buf + offset,
					      dump,
					      "num-vfs-in-pf",
					      p_hwfn->p_cxt_mngr->vf_count);
	offset += qed_dump_num_param(dump_buf + offset,
				     dump,
				     "ptr-size-bytes", माप(व्योम *));
	offset += qed_dump_num_param(dump_buf + offset,
				     dump,
				     "pf-start-line",
				     p_hwfn->p_cxt_mngr->pf_start_line);
	offset += qed_dump_num_param(dump_buf + offset,
				     dump,
				     "page-mem-desc-size-dwords",
				     PAGE_MEM_DESC_SIZE_DWORDS);
	offset += qed_dump_num_param(dump_buf + offset,
				     dump,
				     "ilt-shadow-size",
				     p_hwfn->p_cxt_mngr->ilt_shaकरोw_size);
	/* Additional/Less parameters require matching of number in call to
	 * dump_common_global_params()
	 */

	/* Dump section containing number of PF CIDs per connection type */
	offset += qed_dump_section_hdr(dump_buf + offset,
				       dump, "num_pf_cids_per_conn_type", 1);
	offset += qed_dump_num_param(dump_buf + offset,
				     dump, "size", NUM_OF_CONNECTION_TYPES_E4);
	क्रम (conn_type = 0, valid_conn_pf_cids = 0;
	     conn_type < NUM_OF_CONNECTION_TYPES_E4; conn_type++, offset++) अणु
		u32 num_pf_cids =
		    p_hwfn->p_cxt_mngr->conn_cfg[conn_type].cid_count;

		अगर (dump)
			*(dump_buf + offset) = num_pf_cids;
		valid_conn_pf_cids += num_pf_cids;
	पूर्ण

	/* Dump section containing number of VF CIDs per connection type */
	offset += qed_dump_section_hdr(dump_buf + offset,
				       dump, "num_vf_cids_per_conn_type", 1);
	offset += qed_dump_num_param(dump_buf + offset,
				     dump, "size", NUM_OF_CONNECTION_TYPES_E4);
	क्रम (conn_type = 0, valid_conn_vf_cids = 0;
	     conn_type < NUM_OF_CONNECTION_TYPES_E4; conn_type++, offset++) अणु
		u32 num_vf_cids =
		    p_hwfn->p_cxt_mngr->conn_cfg[conn_type].cids_per_vf;

		अगर (dump)
			*(dump_buf + offset) = num_vf_cids;
		valid_conn_vf_cids += num_vf_cids;
	पूर्ण

	/* Dump section containing physical memory descs क्रम each ILT page */
	num_pages = p_hwfn->p_cxt_mngr->ilt_shaकरोw_size;
	offset += qed_dump_section_hdr(dump_buf + offset,
				       dump, "ilt_page_desc", 1);
	offset += qed_dump_num_param(dump_buf + offset,
				     dump,
				     "size",
				     num_pages * PAGE_MEM_DESC_SIZE_DWORDS);

	/* Copy memory descriptors to dump buffer */
	अगर (dump) अणु
		u32 page_id;

		क्रम (page_id = 0; page_id < num_pages;
		     page_id++, offset += PAGE_MEM_DESC_SIZE_DWORDS)
			स_नकल(dump_buf + offset,
			       &ilt_pages[page_id],
			       DWORDS_TO_BYTES(PAGE_MEM_DESC_SIZE_DWORDS));
	पूर्ण अन्यथा अणु
		offset += num_pages * PAGE_MEM_DESC_SIZE_DWORDS;
	पूर्ण

	valid_conn_pf_pages = DIV_ROUND_UP(valid_conn_pf_cids,
					   num_cids_per_page);
	valid_conn_vf_pages = DIV_ROUND_UP(valid_conn_vf_cids,
					   num_cids_per_page);

	/* Dump ILT pages IDs */
	offset += qed_ilt_dump_pages_section(p_hwfn,
					     dump_buf + offset,
					     dump,
					     valid_conn_pf_pages,
					     valid_conn_vf_pages,
					     ilt_pages, true);

	/* Dump ILT pages memory */
	offset += qed_ilt_dump_pages_section(p_hwfn,
					     dump_buf + offset,
					     dump,
					     valid_conn_pf_pages,
					     valid_conn_vf_pages,
					     ilt_pages, false);

	/* Dump last section */
	offset += qed_dump_last_section(dump_buf, offset, dump);

	वापस offset;
पूर्ण

/***************************** Public Functions *******************************/

क्रमागत dbg_status qed_dbg_set_bin_ptr(काष्ठा qed_hwfn *p_hwfn,
				    स्थिर u8 * स्थिर bin_ptr)
अणु
	काष्ठा bin_buffer_hdr *buf_hdrs = (काष्ठा bin_buffer_hdr *)bin_ptr;
	u8 buf_id;

	/* Convert binary data to debug arrays */
	क्रम (buf_id = 0; buf_id < MAX_BIN_DBG_BUFFER_TYPE; buf_id++)
		qed_set_dbg_bin_buf(p_hwfn,
				    buf_id,
				    (u32 *)(bin_ptr + buf_hdrs[buf_id].offset),
				    buf_hdrs[buf_id].length);

	वापस DBG_STATUS_OK;
पूर्ण

bool qed_पढ़ो_fw_info(काष्ठा qed_hwfn *p_hwfn,
		      काष्ठा qed_ptt *p_ptt, काष्ठा fw_info *fw_info)
अणु
	काष्ठा dbg_tools_data *dev_data = &p_hwfn->dbg_info;
	u8 storm_id;

	क्रम (storm_id = 0; storm_id < MAX_DBG_STORMS; storm_id++) अणु
		काष्ठा storm_defs *storm = &s_storm_defs[storm_id];

		/* Skip Storm अगर it's in reset */
		अगर (dev_data->block_in_reset[storm->sem_block_id])
			जारी;

		/* Read FW info क्रम the current Storm */
		qed_पढ़ो_storm_fw_info(p_hwfn, p_ptt, storm_id, fw_info);

		वापस true;
	पूर्ण

	वापस false;
पूर्ण

क्रमागत dbg_status qed_dbg_grc_config(काष्ठा qed_hwfn *p_hwfn,
				   क्रमागत dbg_grc_params grc_param, u32 val)
अणु
	काष्ठा dbg_tools_data *dev_data = &p_hwfn->dbg_info;
	क्रमागत dbg_status status;
	पूर्णांक i;

	DP_VERBOSE(p_hwfn,
		   QED_MSG_DEBUG,
		   "dbg_grc_config: paramId = %d, val = %d\n", grc_param, val);

	status = qed_dbg_dev_init(p_hwfn);
	अगर (status != DBG_STATUS_OK)
		वापस status;

	/* Initializes the GRC parameters (अगर not initialized). Needed in order
	 * to set the शेष parameter values क्रम the first समय.
	 */
	qed_dbg_grc_init_params(p_hwfn);

	अगर (grc_param >= MAX_DBG_GRC_PARAMS)
		वापस DBG_STATUS_INVALID_ARGS;
	अगर (val < s_grc_param_defs[grc_param].min ||
	    val > s_grc_param_defs[grc_param].max)
		वापस DBG_STATUS_INVALID_ARGS;

	अगर (s_grc_param_defs[grc_param].is_preset) अणु
		/* Preset param */

		/* Disabling a preset is not allowed. Call
		 * dbg_grc_set_params_शेष instead.
		 */
		अगर (!val)
			वापस DBG_STATUS_INVALID_ARGS;

		/* Update all params with the preset values */
		क्रम (i = 0; i < MAX_DBG_GRC_PARAMS; i++) अणु
			काष्ठा grc_param_defs *defs = &s_grc_param_defs[i];
			u32 preset_val;
			/* Skip persistent params */
			अगर (defs->is_persistent)
				जारी;

			/* Find preset value */
			अगर (grc_param == DBG_GRC_PARAM_EXCLUDE_ALL)
				preset_val =
				    defs->exclude_all_preset_val;
			अन्यथा अगर (grc_param == DBG_GRC_PARAM_CRASH)
				preset_val =
				    defs->crash_preset_val[dev_data->chip_id];
			अन्यथा
				वापस DBG_STATUS_INVALID_ARGS;

			qed_grc_set_param(p_hwfn, i, preset_val);
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Regular param - set its value */
		qed_grc_set_param(p_hwfn, grc_param, val);
	पूर्ण

	वापस DBG_STATUS_OK;
पूर्ण

/* Assign शेष GRC param values */
व्योम qed_dbg_grc_set_params_शेष(काष्ठा qed_hwfn *p_hwfn)
अणु
	काष्ठा dbg_tools_data *dev_data = &p_hwfn->dbg_info;
	u32 i;

	क्रम (i = 0; i < MAX_DBG_GRC_PARAMS; i++)
		अगर (!s_grc_param_defs[i].is_persistent)
			dev_data->grc.param_val[i] =
			    s_grc_param_defs[i].शेष_val[dev_data->chip_id];
पूर्ण

क्रमागत dbg_status qed_dbg_grc_get_dump_buf_size(काष्ठा qed_hwfn *p_hwfn,
					      काष्ठा qed_ptt *p_ptt,
					      u32 *buf_size)
अणु
	क्रमागत dbg_status status = qed_dbg_dev_init(p_hwfn);

	*buf_size = 0;

	अगर (status != DBG_STATUS_OK)
		वापस status;

	अगर (!p_hwfn->dbg_arrays[BIN_BUF_DBG_MODE_TREE].ptr ||
	    !p_hwfn->dbg_arrays[BIN_BUF_DBG_DUMP_REG].ptr ||
	    !p_hwfn->dbg_arrays[BIN_BUF_DBG_DUMP_MEM].ptr ||
	    !p_hwfn->dbg_arrays[BIN_BUF_DBG_ATTN_BLOCKS].ptr ||
	    !p_hwfn->dbg_arrays[BIN_BUF_DBG_ATTN_REGS].ptr)
		वापस DBG_STATUS_DBG_ARRAY_NOT_SET;

	वापस qed_grc_dump(p_hwfn, p_ptt, शून्य, false, buf_size);
पूर्ण

क्रमागत dbg_status qed_dbg_grc_dump(काष्ठा qed_hwfn *p_hwfn,
				 काष्ठा qed_ptt *p_ptt,
				 u32 *dump_buf,
				 u32 buf_size_in_dwords,
				 u32 *num_dumped_dwords)
अणु
	u32 needed_buf_size_in_dwords;
	क्रमागत dbg_status status;

	*num_dumped_dwords = 0;

	status = qed_dbg_grc_get_dump_buf_size(p_hwfn,
					       p_ptt,
					       &needed_buf_size_in_dwords);
	अगर (status != DBG_STATUS_OK)
		वापस status;

	अगर (buf_size_in_dwords < needed_buf_size_in_dwords)
		वापस DBG_STATUS_DUMP_BUF_TOO_SMALL;

	/* GRC Dump */
	status = qed_grc_dump(p_hwfn, p_ptt, dump_buf, true, num_dumped_dwords);

	/* Revert GRC params to their शेष */
	qed_dbg_grc_set_params_शेष(p_hwfn);

	वापस status;
पूर्ण

क्रमागत dbg_status qed_dbg_idle_chk_get_dump_buf_size(काष्ठा qed_hwfn *p_hwfn,
						   काष्ठा qed_ptt *p_ptt,
						   u32 *buf_size)
अणु
	काष्ठा dbg_tools_data *dev_data = &p_hwfn->dbg_info;
	काष्ठा idle_chk_data *idle_chk = &dev_data->idle_chk;
	क्रमागत dbg_status status;

	*buf_size = 0;

	status = qed_dbg_dev_init(p_hwfn);
	अगर (status != DBG_STATUS_OK)
		वापस status;

	अगर (!p_hwfn->dbg_arrays[BIN_BUF_DBG_MODE_TREE].ptr ||
	    !p_hwfn->dbg_arrays[BIN_BUF_DBG_IDLE_CHK_REGS].ptr ||
	    !p_hwfn->dbg_arrays[BIN_BUF_DBG_IDLE_CHK_IMMS].ptr ||
	    !p_hwfn->dbg_arrays[BIN_BUF_DBG_IDLE_CHK_RULES].ptr)
		वापस DBG_STATUS_DBG_ARRAY_NOT_SET;

	अगर (!idle_chk->buf_size_set) अणु
		idle_chk->buf_size = qed_idle_chk_dump(p_hwfn,
						       p_ptt, शून्य, false);
		idle_chk->buf_size_set = true;
	पूर्ण

	*buf_size = idle_chk->buf_size;

	वापस DBG_STATUS_OK;
पूर्ण

क्रमागत dbg_status qed_dbg_idle_chk_dump(काष्ठा qed_hwfn *p_hwfn,
				      काष्ठा qed_ptt *p_ptt,
				      u32 *dump_buf,
				      u32 buf_size_in_dwords,
				      u32 *num_dumped_dwords)
अणु
	u32 needed_buf_size_in_dwords;
	क्रमागत dbg_status status;

	*num_dumped_dwords = 0;

	status = qed_dbg_idle_chk_get_dump_buf_size(p_hwfn,
						    p_ptt,
						    &needed_buf_size_in_dwords);
	अगर (status != DBG_STATUS_OK)
		वापस status;

	अगर (buf_size_in_dwords < needed_buf_size_in_dwords)
		वापस DBG_STATUS_DUMP_BUF_TOO_SMALL;

	/* Update reset state */
	qed_grc_unreset_blocks(p_hwfn, p_ptt, true);
	qed_update_blocks_reset_state(p_hwfn, p_ptt);

	/* Idle Check Dump */
	*num_dumped_dwords = qed_idle_chk_dump(p_hwfn, p_ptt, dump_buf, true);

	/* Revert GRC params to their शेष */
	qed_dbg_grc_set_params_शेष(p_hwfn);

	वापस DBG_STATUS_OK;
पूर्ण

क्रमागत dbg_status qed_dbg_mcp_trace_get_dump_buf_size(काष्ठा qed_hwfn *p_hwfn,
						    काष्ठा qed_ptt *p_ptt,
						    u32 *buf_size)
अणु
	क्रमागत dbg_status status = qed_dbg_dev_init(p_hwfn);

	*buf_size = 0;

	अगर (status != DBG_STATUS_OK)
		वापस status;

	वापस qed_mcp_trace_dump(p_hwfn, p_ptt, शून्य, false, buf_size);
पूर्ण

क्रमागत dbg_status qed_dbg_mcp_trace_dump(काष्ठा qed_hwfn *p_hwfn,
				       काष्ठा qed_ptt *p_ptt,
				       u32 *dump_buf,
				       u32 buf_size_in_dwords,
				       u32 *num_dumped_dwords)
अणु
	u32 needed_buf_size_in_dwords;
	क्रमागत dbg_status status;

	status =
		qed_dbg_mcp_trace_get_dump_buf_size(p_hwfn,
						    p_ptt,
						    &needed_buf_size_in_dwords);
	अगर (status != DBG_STATUS_OK && status !=
	    DBG_STATUS_NVRAM_GET_IMAGE_FAILED)
		वापस status;

	अगर (buf_size_in_dwords < needed_buf_size_in_dwords)
		वापस DBG_STATUS_DUMP_BUF_TOO_SMALL;

	/* Update reset state */
	qed_update_blocks_reset_state(p_hwfn, p_ptt);

	/* Perक्रमm dump */
	status = qed_mcp_trace_dump(p_hwfn,
				    p_ptt, dump_buf, true, num_dumped_dwords);

	/* Revert GRC params to their शेष */
	qed_dbg_grc_set_params_शेष(p_hwfn);

	वापस status;
पूर्ण

क्रमागत dbg_status qed_dbg_reg_fअगरo_get_dump_buf_size(काष्ठा qed_hwfn *p_hwfn,
						   काष्ठा qed_ptt *p_ptt,
						   u32 *buf_size)
अणु
	क्रमागत dbg_status status = qed_dbg_dev_init(p_hwfn);

	*buf_size = 0;

	अगर (status != DBG_STATUS_OK)
		वापस status;

	वापस qed_reg_fअगरo_dump(p_hwfn, p_ptt, शून्य, false, buf_size);
पूर्ण

क्रमागत dbg_status qed_dbg_reg_fअगरo_dump(काष्ठा qed_hwfn *p_hwfn,
				      काष्ठा qed_ptt *p_ptt,
				      u32 *dump_buf,
				      u32 buf_size_in_dwords,
				      u32 *num_dumped_dwords)
अणु
	u32 needed_buf_size_in_dwords;
	क्रमागत dbg_status status;

	*num_dumped_dwords = 0;

	status = qed_dbg_reg_fअगरo_get_dump_buf_size(p_hwfn,
						    p_ptt,
						    &needed_buf_size_in_dwords);
	अगर (status != DBG_STATUS_OK)
		वापस status;

	अगर (buf_size_in_dwords < needed_buf_size_in_dwords)
		वापस DBG_STATUS_DUMP_BUF_TOO_SMALL;

	/* Update reset state */
	qed_update_blocks_reset_state(p_hwfn, p_ptt);

	status = qed_reg_fअगरo_dump(p_hwfn,
				   p_ptt, dump_buf, true, num_dumped_dwords);

	/* Revert GRC params to their शेष */
	qed_dbg_grc_set_params_शेष(p_hwfn);

	वापस status;
पूर्ण

क्रमागत dbg_status qed_dbg_igu_fअगरo_get_dump_buf_size(काष्ठा qed_hwfn *p_hwfn,
						   काष्ठा qed_ptt *p_ptt,
						   u32 *buf_size)
अणु
	क्रमागत dbg_status status = qed_dbg_dev_init(p_hwfn);

	*buf_size = 0;

	अगर (status != DBG_STATUS_OK)
		वापस status;

	वापस qed_igu_fअगरo_dump(p_hwfn, p_ptt, शून्य, false, buf_size);
पूर्ण

क्रमागत dbg_status qed_dbg_igu_fअगरo_dump(काष्ठा qed_hwfn *p_hwfn,
				      काष्ठा qed_ptt *p_ptt,
				      u32 *dump_buf,
				      u32 buf_size_in_dwords,
				      u32 *num_dumped_dwords)
अणु
	u32 needed_buf_size_in_dwords;
	क्रमागत dbg_status status;

	*num_dumped_dwords = 0;

	status = qed_dbg_igu_fअगरo_get_dump_buf_size(p_hwfn,
						    p_ptt,
						    &needed_buf_size_in_dwords);
	अगर (status != DBG_STATUS_OK)
		वापस status;

	अगर (buf_size_in_dwords < needed_buf_size_in_dwords)
		वापस DBG_STATUS_DUMP_BUF_TOO_SMALL;

	/* Update reset state */
	qed_update_blocks_reset_state(p_hwfn, p_ptt);

	status = qed_igu_fअगरo_dump(p_hwfn,
				   p_ptt, dump_buf, true, num_dumped_dwords);
	/* Revert GRC params to their शेष */
	qed_dbg_grc_set_params_शेष(p_hwfn);

	वापस status;
पूर्ण

क्रमागत dbg_status
qed_dbg_protection_override_get_dump_buf_size(काष्ठा qed_hwfn *p_hwfn,
					      काष्ठा qed_ptt *p_ptt,
					      u32 *buf_size)
अणु
	क्रमागत dbg_status status = qed_dbg_dev_init(p_hwfn);

	*buf_size = 0;

	अगर (status != DBG_STATUS_OK)
		वापस status;

	वापस qed_protection_override_dump(p_hwfn,
					    p_ptt, शून्य, false, buf_size);
पूर्ण

क्रमागत dbg_status qed_dbg_protection_override_dump(काष्ठा qed_hwfn *p_hwfn,
						 काष्ठा qed_ptt *p_ptt,
						 u32 *dump_buf,
						 u32 buf_size_in_dwords,
						 u32 *num_dumped_dwords)
अणु
	u32 needed_buf_size_in_dwords, *p_size = &needed_buf_size_in_dwords;
	क्रमागत dbg_status status;

	*num_dumped_dwords = 0;

	status =
		qed_dbg_protection_override_get_dump_buf_size(p_hwfn,
							      p_ptt,
							      p_size);
	अगर (status != DBG_STATUS_OK)
		वापस status;

	अगर (buf_size_in_dwords < needed_buf_size_in_dwords)
		वापस DBG_STATUS_DUMP_BUF_TOO_SMALL;

	/* Update reset state */
	qed_update_blocks_reset_state(p_hwfn, p_ptt);

	status = qed_protection_override_dump(p_hwfn,
					      p_ptt,
					      dump_buf,
					      true, num_dumped_dwords);

	/* Revert GRC params to their शेष */
	qed_dbg_grc_set_params_शेष(p_hwfn);

	वापस status;
पूर्ण

क्रमागत dbg_status qed_dbg_fw_निश्चितs_get_dump_buf_size(काष्ठा qed_hwfn *p_hwfn,
						     काष्ठा qed_ptt *p_ptt,
						     u32 *buf_size)
अणु
	क्रमागत dbg_status status = qed_dbg_dev_init(p_hwfn);

	*buf_size = 0;

	अगर (status != DBG_STATUS_OK)
		वापस status;

	/* Update reset state */
	qed_update_blocks_reset_state(p_hwfn, p_ptt);

	*buf_size = qed_fw_निश्चितs_dump(p_hwfn, p_ptt, शून्य, false);

	वापस DBG_STATUS_OK;
पूर्ण

क्रमागत dbg_status qed_dbg_fw_निश्चितs_dump(काष्ठा qed_hwfn *p_hwfn,
					काष्ठा qed_ptt *p_ptt,
					u32 *dump_buf,
					u32 buf_size_in_dwords,
					u32 *num_dumped_dwords)
अणु
	u32 needed_buf_size_in_dwords, *p_size = &needed_buf_size_in_dwords;
	क्रमागत dbg_status status;

	*num_dumped_dwords = 0;

	status =
		qed_dbg_fw_निश्चितs_get_dump_buf_size(p_hwfn,
						     p_ptt,
						     p_size);
	अगर (status != DBG_STATUS_OK)
		वापस status;

	अगर (buf_size_in_dwords < needed_buf_size_in_dwords)
		वापस DBG_STATUS_DUMP_BUF_TOO_SMALL;

	*num_dumped_dwords = qed_fw_निश्चितs_dump(p_hwfn, p_ptt, dump_buf, true);

	/* Revert GRC params to their शेष */
	qed_dbg_grc_set_params_शेष(p_hwfn);

	वापस DBG_STATUS_OK;
पूर्ण

अटल क्रमागत dbg_status qed_dbg_ilt_get_dump_buf_size(काष्ठा qed_hwfn *p_hwfn,
						     काष्ठा qed_ptt *p_ptt,
						     u32 *buf_size)
अणु
	क्रमागत dbg_status status = qed_dbg_dev_init(p_hwfn);

	*buf_size = 0;

	अगर (status != DBG_STATUS_OK)
		वापस status;

	*buf_size = qed_ilt_dump(p_hwfn, p_ptt, शून्य, false);

	वापस DBG_STATUS_OK;
पूर्ण

अटल क्रमागत dbg_status qed_dbg_ilt_dump(काष्ठा qed_hwfn *p_hwfn,
					काष्ठा qed_ptt *p_ptt,
					u32 *dump_buf,
					u32 buf_size_in_dwords,
					u32 *num_dumped_dwords)
अणु
	u32 needed_buf_size_in_dwords;
	क्रमागत dbg_status status;

	*num_dumped_dwords = 0;

	status = qed_dbg_ilt_get_dump_buf_size(p_hwfn,
					       p_ptt,
					       &needed_buf_size_in_dwords);
	अगर (status != DBG_STATUS_OK)
		वापस status;

	अगर (buf_size_in_dwords < needed_buf_size_in_dwords)
		वापस DBG_STATUS_DUMP_BUF_TOO_SMALL;

	*num_dumped_dwords = qed_ilt_dump(p_hwfn, p_ptt, dump_buf, true);

	/* Reveret GRC params to their शेष */
	qed_dbg_grc_set_params_शेष(p_hwfn);

	वापस DBG_STATUS_OK;
पूर्ण

क्रमागत dbg_status qed_dbg_पढ़ो_attn(काष्ठा qed_hwfn *p_hwfn,
				  काष्ठा qed_ptt *p_ptt,
				  क्रमागत block_id block_id,
				  क्रमागत dbg_attn_type attn_type,
				  bool clear_status,
				  काष्ठा dbg_attn_block_result *results)
अणु
	क्रमागत dbg_status status = qed_dbg_dev_init(p_hwfn);
	u8 reg_idx, num_attn_regs, num_result_regs = 0;
	स्थिर काष्ठा dbg_attn_reg *attn_reg_arr;

	अगर (status != DBG_STATUS_OK)
		वापस status;

	अगर (!p_hwfn->dbg_arrays[BIN_BUF_DBG_MODE_TREE].ptr ||
	    !p_hwfn->dbg_arrays[BIN_BUF_DBG_ATTN_BLOCKS].ptr ||
	    !p_hwfn->dbg_arrays[BIN_BUF_DBG_ATTN_REGS].ptr)
		वापस DBG_STATUS_DBG_ARRAY_NOT_SET;

	attn_reg_arr = qed_get_block_attn_regs(p_hwfn,
					       block_id,
					       attn_type, &num_attn_regs);

	क्रम (reg_idx = 0; reg_idx < num_attn_regs; reg_idx++) अणु
		स्थिर काष्ठा dbg_attn_reg *reg_data = &attn_reg_arr[reg_idx];
		काष्ठा dbg_attn_reg_result *reg_result;
		u32 sts_addr, sts_val;
		u16 modes_buf_offset;
		bool eval_mode;

		/* Check mode */
		eval_mode = GET_FIELD(reg_data->mode.data,
				      DBG_MODE_HDR_EVAL_MODE) > 0;
		modes_buf_offset = GET_FIELD(reg_data->mode.data,
					     DBG_MODE_HDR_MODES_BUF_OFFSET);
		अगर (eval_mode && !qed_is_mode_match(p_hwfn, &modes_buf_offset))
			जारी;

		/* Mode match - पढ़ो attention status रेजिस्टर */
		sts_addr = DWORDS_TO_BYTES(clear_status ?
					   reg_data->sts_clr_address :
					   GET_FIELD(reg_data->data,
						     DBG_ATTN_REG_STS_ADDRESS));
		sts_val = qed_rd(p_hwfn, p_ptt, sts_addr);
		अगर (!sts_val)
			जारी;

		/* Non-zero attention status - add to results */
		reg_result = &results->reg_results[num_result_regs];
		SET_FIELD(reg_result->data,
			  DBG_ATTN_REG_RESULT_STS_ADDRESS, sts_addr);
		SET_FIELD(reg_result->data,
			  DBG_ATTN_REG_RESULT_NUM_REG_ATTN,
			  GET_FIELD(reg_data->data, DBG_ATTN_REG_NUM_REG_ATTN));
		reg_result->block_attn_offset = reg_data->block_attn_offset;
		reg_result->sts_val = sts_val;
		reg_result->mask_val = qed_rd(p_hwfn,
					      p_ptt,
					      DWORDS_TO_BYTES
					      (reg_data->mask_address));
		num_result_regs++;
	पूर्ण

	results->block_id = (u8)block_id;
	results->names_offset =
	    qed_get_block_attn_data(p_hwfn, block_id, attn_type)->names_offset;
	SET_FIELD(results->data, DBG_ATTN_BLOCK_RESULT_ATTN_TYPE, attn_type);
	SET_FIELD(results->data,
		  DBG_ATTN_BLOCK_RESULT_NUM_REGS, num_result_regs);

	वापस DBG_STATUS_OK;
पूर्ण

/******************************* Data Types **********************************/

/* REG fअगरo element */
काष्ठा reg_fअगरo_element अणु
	u64 data;
#घोषणा REG_FIFO_ELEMENT_ADDRESS_SHIFT		0
#घोषणा REG_FIFO_ELEMENT_ADDRESS_MASK		0x7fffff
#घोषणा REG_FIFO_ELEMENT_ACCESS_SHIFT		23
#घोषणा REG_FIFO_ELEMENT_ACCESS_MASK		0x1
#घोषणा REG_FIFO_ELEMENT_PF_SHIFT		24
#घोषणा REG_FIFO_ELEMENT_PF_MASK		0xf
#घोषणा REG_FIFO_ELEMENT_VF_SHIFT		28
#घोषणा REG_FIFO_ELEMENT_VF_MASK		0xff
#घोषणा REG_FIFO_ELEMENT_PORT_SHIFT		36
#घोषणा REG_FIFO_ELEMENT_PORT_MASK		0x3
#घोषणा REG_FIFO_ELEMENT_PRIVILEGE_SHIFT	38
#घोषणा REG_FIFO_ELEMENT_PRIVILEGE_MASK		0x3
#घोषणा REG_FIFO_ELEMENT_PROTECTION_SHIFT	40
#घोषणा REG_FIFO_ELEMENT_PROTECTION_MASK	0x7
#घोषणा REG_FIFO_ELEMENT_MASTER_SHIFT		43
#घोषणा REG_FIFO_ELEMENT_MASTER_MASK		0xf
#घोषणा REG_FIFO_ELEMENT_ERROR_SHIFT		47
#घोषणा REG_FIFO_ELEMENT_ERROR_MASK		0x1f
पूर्ण;

/* REG fअगरo error element */
काष्ठा reg_fअगरo_err अणु
	u32 err_code;
	स्थिर अक्षर *err_msg;
पूर्ण;

/* IGU fअगरo element */
काष्ठा igu_fअगरo_element अणु
	u32 dword0;
#घोषणा IGU_FIFO_ELEMENT_DWORD0_FID_SHIFT		0
#घोषणा IGU_FIFO_ELEMENT_DWORD0_FID_MASK		0xff
#घोषणा IGU_FIFO_ELEMENT_DWORD0_IS_PF_SHIFT		8
#घोषणा IGU_FIFO_ELEMENT_DWORD0_IS_PF_MASK		0x1
#घोषणा IGU_FIFO_ELEMENT_DWORD0_SOURCE_SHIFT		9
#घोषणा IGU_FIFO_ELEMENT_DWORD0_SOURCE_MASK		0xf
#घोषणा IGU_FIFO_ELEMENT_DWORD0_ERR_TYPE_SHIFT		13
#घोषणा IGU_FIFO_ELEMENT_DWORD0_ERR_TYPE_MASK		0xf
#घोषणा IGU_FIFO_ELEMENT_DWORD0_CMD_ADDR_SHIFT		17
#घोषणा IGU_FIFO_ELEMENT_DWORD0_CMD_ADDR_MASK		0x7fff
	u32 dword1;
	u32 dword2;
#घोषणा IGU_FIFO_ELEMENT_DWORD12_IS_WR_CMD_SHIFT	0
#घोषणा IGU_FIFO_ELEMENT_DWORD12_IS_WR_CMD_MASK		0x1
#घोषणा IGU_FIFO_ELEMENT_DWORD12_WR_DATA_SHIFT		1
#घोषणा IGU_FIFO_ELEMENT_DWORD12_WR_DATA_MASK		0xffffffff
	u32 reserved;
पूर्ण;

काष्ठा igu_fअगरo_wr_data अणु
	u32 data;
#घोषणा IGU_FIFO_WR_DATA_PROD_CONS_SHIFT		0
#घोषणा IGU_FIFO_WR_DATA_PROD_CONS_MASK			0xffffff
#घोषणा IGU_FIFO_WR_DATA_UPDATE_FLAG_SHIFT		24
#घोषणा IGU_FIFO_WR_DATA_UPDATE_FLAG_MASK		0x1
#घोषणा IGU_FIFO_WR_DATA_EN_DIS_INT_FOR_SB_SHIFT	25
#घोषणा IGU_FIFO_WR_DATA_EN_DIS_INT_FOR_SB_MASK		0x3
#घोषणा IGU_FIFO_WR_DATA_SEGMENT_SHIFT			27
#घोषणा IGU_FIFO_WR_DATA_SEGMENT_MASK			0x1
#घोषणा IGU_FIFO_WR_DATA_TIMER_MASK_SHIFT		28
#घोषणा IGU_FIFO_WR_DATA_TIMER_MASK_MASK		0x1
#घोषणा IGU_FIFO_WR_DATA_CMD_TYPE_SHIFT			31
#घोषणा IGU_FIFO_WR_DATA_CMD_TYPE_MASK			0x1
पूर्ण;

काष्ठा igu_fअगरo_cleanup_wr_data अणु
	u32 data;
#घोषणा IGU_FIFO_CLEANUP_WR_DATA_RESERVED_SHIFT		0
#घोषणा IGU_FIFO_CLEANUP_WR_DATA_RESERVED_MASK		0x7ffffff
#घोषणा IGU_FIFO_CLEANUP_WR_DATA_CLEANUP_VAL_SHIFT	27
#घोषणा IGU_FIFO_CLEANUP_WR_DATA_CLEANUP_VAL_MASK	0x1
#घोषणा IGU_FIFO_CLEANUP_WR_DATA_CLEANUP_TYPE_SHIFT	28
#घोषणा IGU_FIFO_CLEANUP_WR_DATA_CLEANUP_TYPE_MASK	0x7
#घोषणा IGU_FIFO_CLEANUP_WR_DATA_CMD_TYPE_SHIFT		31
#घोषणा IGU_FIFO_CLEANUP_WR_DATA_CMD_TYPE_MASK		0x1
पूर्ण;

/* Protection override element */
काष्ठा protection_override_element अणु
	u64 data;
#घोषणा PROTECTION_OVERRIDE_ELEMENT_ADDRESS_SHIFT		0
#घोषणा PROTECTION_OVERRIDE_ELEMENT_ADDRESS_MASK		0x7fffff
#घोषणा PROTECTION_OVERRIDE_ELEMENT_WINDOW_SIZE_SHIFT		23
#घोषणा PROTECTION_OVERRIDE_ELEMENT_WINDOW_SIZE_MASK		0xffffff
#घोषणा PROTECTION_OVERRIDE_ELEMENT_READ_SHIFT			47
#घोषणा PROTECTION_OVERRIDE_ELEMENT_READ_MASK			0x1
#घोषणा PROTECTION_OVERRIDE_ELEMENT_WRITE_SHIFT			48
#घोषणा PROTECTION_OVERRIDE_ELEMENT_WRITE_MASK			0x1
#घोषणा PROTECTION_OVERRIDE_ELEMENT_READ_PROTECTION_SHIFT	49
#घोषणा PROTECTION_OVERRIDE_ELEMENT_READ_PROTECTION_MASK	0x7
#घोषणा PROTECTION_OVERRIDE_ELEMENT_WRITE_PROTECTION_SHIFT	52
#घोषणा PROTECTION_OVERRIDE_ELEMENT_WRITE_PROTECTION_MASK	0x7
पूर्ण;

क्रमागत igu_fअगरo_sources अणु
	IGU_SRC_PXP0,
	IGU_SRC_PXP1,
	IGU_SRC_PXP2,
	IGU_SRC_PXP3,
	IGU_SRC_PXP4,
	IGU_SRC_PXP5,
	IGU_SRC_PXP6,
	IGU_SRC_PXP7,
	IGU_SRC_CAU,
	IGU_SRC_ATTN,
	IGU_SRC_GRC
पूर्ण;

क्रमागत igu_fअगरo_addr_types अणु
	IGU_ADDR_TYPE_MSIX_MEM,
	IGU_ADDR_TYPE_WRITE_PBA,
	IGU_ADDR_TYPE_WRITE_INT_ACK,
	IGU_ADDR_TYPE_WRITE_ATTN_BITS,
	IGU_ADDR_TYPE_READ_INT,
	IGU_ADDR_TYPE_WRITE_PROD_UPDATE,
	IGU_ADDR_TYPE_RESERVED
पूर्ण;

काष्ठा igu_fअगरo_addr_data अणु
	u16 start_addr;
	u16 end_addr;
	अक्षर *desc;
	अक्षर *vf_desc;
	क्रमागत igu_fअगरo_addr_types type;
पूर्ण;

/******************************** Constants **********************************/

#घोषणा MAX_MSG_LEN				1024

#घोषणा MCP_TRACE_MAX_MODULE_LEN		8
#घोषणा MCP_TRACE_FORMAT_MAX_PARAMS		3
#घोषणा MCP_TRACE_FORMAT_PARAM_WIDTH \
	(MCP_TRACE_FORMAT_P2_SIZE_OFFSET - MCP_TRACE_FORMAT_P1_SIZE_OFFSET)

#घोषणा REG_FIFO_ELEMENT_ADDR_FACTOR		4
#घोषणा REG_FIFO_ELEMENT_IS_PF_VF_VAL		127

#घोषणा PROTECTION_OVERRIDE_ELEMENT_ADDR_FACTOR	4

/***************************** Constant Arrays *******************************/

/* Status string array */
अटल स्थिर अक्षर * स्थिर s_status_str[] = अणु
	/* DBG_STATUS_OK */
	"Operation completed successfully",

	/* DBG_STATUS_APP_VERSION_NOT_SET */
	"Debug application version wasn't set",

	/* DBG_STATUS_UNSUPPORTED_APP_VERSION */
	"Unsupported debug application version",

	/* DBG_STATUS_DBG_BLOCK_NOT_RESET */
	"The debug block wasn't reset since the last recording",

	/* DBG_STATUS_INVALID_ARGS */
	"Invalid arguments",

	/* DBG_STATUS_OUTPUT_ALREADY_SET */
	"The debug output was already set",

	/* DBG_STATUS_INVALID_PCI_BUF_SIZE */
	"Invalid PCI buffer size",

	/* DBG_STATUS_PCI_BUF_ALLOC_FAILED */
	"PCI buffer allocation failed",

	/* DBG_STATUS_PCI_BUF_NOT_ALLOCATED */
	"A PCI buffer wasn't allocated",

	/* DBG_STATUS_INVALID_FILTER_TRIGGER_DWORDS */
	"The filter/trigger constraint dword offsets are not enabled for recording",
	/* DBG_STATUS_NO_MATCHING_FRAMING_MODE */
	"No matching framing mode",

	/* DBG_STATUS_VFC_READ_ERROR */
	"Error reading from VFC",

	/* DBG_STATUS_STORM_ALREADY_ENABLED */
	"The Storm was already enabled",

	/* DBG_STATUS_STORM_NOT_ENABLED */
	"The specified Storm wasn't enabled",

	/* DBG_STATUS_BLOCK_ALREADY_ENABLED */
	"The block was already enabled",

	/* DBG_STATUS_BLOCK_NOT_ENABLED */
	"The specified block wasn't enabled",

	/* DBG_STATUS_NO_INPUT_ENABLED */
	"No input was enabled for recording",

	/* DBG_STATUS_NO_FILTER_TRIGGER_256B */
	"Filters and triggers are not allowed in E4 256-bit mode",

	/* DBG_STATUS_FILTER_ALREADY_ENABLED */
	"The filter was already enabled",

	/* DBG_STATUS_TRIGGER_ALREADY_ENABLED */
	"The trigger was already enabled",

	/* DBG_STATUS_TRIGGER_NOT_ENABLED */
	"The trigger wasn't enabled",

	/* DBG_STATUS_CANT_ADD_CONSTRAINT */
	"A constraint can be added only after a filter was enabled or a trigger state was added",

	/* DBG_STATUS_TOO_MANY_TRIGGER_STATES */
	"Cannot add more than 3 trigger states",

	/* DBG_STATUS_TOO_MANY_CONSTRAINTS */
	"Cannot add more than 4 constraints per filter or trigger state",

	/* DBG_STATUS_RECORDING_NOT_STARTED */
	"The recording wasn't started",

	/* DBG_STATUS_DATA_DIDNT_TRIGGER */
	"A trigger was configured, but it didn't trigger",

	/* DBG_STATUS_NO_DATA_RECORDED */
	"No data was recorded",

	/* DBG_STATUS_DUMP_BUF_TOO_SMALL */
	"Dump buffer is too small",

	/* DBG_STATUS_DUMP_NOT_CHUNK_ALIGNED */
	"Dumped data is not aligned to chunks",

	/* DBG_STATUS_UNKNOWN_CHIP */
	"Unknown chip",

	/* DBG_STATUS_VIRT_MEM_ALLOC_FAILED */
	"Failed allocating virtual memory",

	/* DBG_STATUS_BLOCK_IN_RESET */
	"The input block is in reset",

	/* DBG_STATUS_INVALID_TRACE_SIGNATURE */
	"Invalid MCP trace signature found in NVRAM",

	/* DBG_STATUS_INVALID_NVRAM_BUNDLE */
	"Invalid bundle ID found in NVRAM",

	/* DBG_STATUS_NVRAM_GET_IMAGE_FAILED */
	"Failed getting NVRAM image",

	/* DBG_STATUS_NON_ALIGNED_NVRAM_IMAGE */
	"NVRAM image is not dword-aligned",

	/* DBG_STATUS_NVRAM_READ_FAILED */
	"Failed reading from NVRAM",

	/* DBG_STATUS_IDLE_CHK_PARSE_FAILED */
	"Idle check parsing failed",

	/* DBG_STATUS_MCP_TRACE_BAD_DATA */
	"MCP Trace data is corrupt",

	/* DBG_STATUS_MCP_TRACE_NO_META */
	"Dump doesn't contain meta data - it must be provided in image file",

	/* DBG_STATUS_MCP_COULD_NOT_HALT */
	"Failed to halt MCP",

	/* DBG_STATUS_MCP_COULD_NOT_RESUME */
	"Failed to resume MCP after halt",

	/* DBG_STATUS_RESERVED0 */
	"",

	/* DBG_STATUS_SEMI_FIFO_NOT_EMPTY */
	"Failed to empty SEMI sync FIFO",

	/* DBG_STATUS_IGU_FIFO_BAD_DATA */
	"IGU FIFO data is corrupt",

	/* DBG_STATUS_MCP_COULD_NOT_MASK_PRTY */
	"MCP failed to mask parities",

	/* DBG_STATUS_FW_ASSERTS_PARSE_FAILED */
	"FW Asserts parsing failed",

	/* DBG_STATUS_REG_FIFO_BAD_DATA */
	"GRC FIFO data is corrupt",

	/* DBG_STATUS_PROTECTION_OVERRIDE_BAD_DATA */
	"Protection Override data is corrupt",

	/* DBG_STATUS_DBG_ARRAY_NOT_SET */
	"Debug arrays were not set (when using binary files, dbg_set_bin_ptr must be called)",

	/* DBG_STATUS_RESERVED1 */
	"",

	/* DBG_STATUS_NON_MATCHING_LINES */
	"Non-matching debug lines - in E4, all lines must be of the same type (either 128b or 256b)",

	/* DBG_STATUS_INSUFFICIENT_HW_IDS */
	"Insufficient HW IDs. Try to record less Storms/blocks",

	/* DBG_STATUS_DBG_BUS_IN_USE */
	"The debug bus is in use",

	/* DBG_STATUS_INVALID_STORM_DBG_MODE */
	"The storm debug mode is not supported in the current chip",

	/* DBG_STATUS_OTHER_ENGINE_BB_ONLY */
	"Other engine is supported only in BB",

	/* DBG_STATUS_FILTER_SINGLE_HW_ID */
	"The configured filter mode requires a single Storm/block input",

	/* DBG_STATUS_TRIGGER_SINGLE_HW_ID */
	"The configured filter mode requires that all the constraints of a single trigger state will be defined on a single Storm/block input",

	/* DBG_STATUS_MISSING_TRIGGER_STATE_STORM */
	"When triggering on Storm data, the Storm to trigger on must be specified"
पूर्ण;

/* Idle check severity names array */
अटल स्थिर अक्षर * स्थिर s_idle_chk_severity_str[] = अणु
	"Error",
	"Error if no traffic",
	"Warning"
पूर्ण;

/* MCP Trace level names array */
अटल स्थिर अक्षर * स्थिर s_mcp_trace_level_str[] = अणु
	"ERROR",
	"TRACE",
	"DEBUG"
पूर्ण;

/* Access type names array */
अटल स्थिर अक्षर * स्थिर s_access_strs[] = अणु
	"read",
	"write"
पूर्ण;

/* Privilege type names array */
अटल स्थिर अक्षर * स्थिर s_privilege_strs[] = अणु
	"VF",
	"PDA",
	"HV",
	"UA"
पूर्ण;

/* Protection type names array */
अटल स्थिर अक्षर * स्थिर s_protection_strs[] = अणु
	"(default)",
	"(default)",
	"(default)",
	"(default)",
	"override VF",
	"override PDA",
	"override HV",
	"override UA"
पूर्ण;

/* Master type names array */
अटल स्थिर अक्षर * स्थिर s_master_strs[] = अणु
	"???",
	"pxp",
	"mcp",
	"msdm",
	"psdm",
	"ysdm",
	"usdm",
	"tsdm",
	"xsdm",
	"dbu",
	"dmae",
	"jdap",
	"???",
	"???",
	"???",
	"???"
पूर्ण;

/* REG FIFO error messages array */
अटल काष्ठा reg_fअगरo_err s_reg_fअगरo_errors[] = अणु
	अणु1, "grc timeout"पूर्ण,
	अणु2, "address doesn't belong to any block"पूर्ण,
	अणु4, "reserved address in block or write to read-only address"पूर्ण,
	अणु8, "privilege/protection mismatch"पूर्ण,
	अणु16, "path isolation error"पूर्ण,
	अणु17, "RSL error"पूर्ण
पूर्ण;

/* IGU FIFO sources array */
अटल स्थिर अक्षर * स्थिर s_igu_fअगरo_source_strs[] = अणु
	"TSTORM",
	"MSTORM",
	"USTORM",
	"XSTORM",
	"YSTORM",
	"PSTORM",
	"PCIE",
	"NIG_QM_PBF",
	"CAU",
	"ATTN",
	"GRC",
पूर्ण;

/* IGU FIFO error messages */
अटल स्थिर अक्षर * स्थिर s_igu_fअगरo_error_strs[] = अणु
	"no error",
	"length error",
	"function disabled",
	"VF sent command to attention address",
	"host sent prod update command",
	"read of during interrupt register while in MIMD mode",
	"access to PXP BAR reserved address",
	"producer update command to attention index",
	"unknown error",
	"SB index not valid",
	"SB relative index and FID not found",
	"FID not match",
	"command with error flag asserted (PCI error or CAU discard)",
	"VF sent cleanup and RF cleanup is disabled",
	"cleanup command on type bigger than 4"
पूर्ण;

/* IGU FIFO address data */
अटल स्थिर काष्ठा igu_fअगरo_addr_data s_igu_fअगरo_addr_data[] = अणु
	अणु0x0, 0x101, "MSI-X Memory", शून्य,
	 IGU_ADDR_TYPE_MSIX_MEMपूर्ण,
	अणु0x102, 0x1ff, "reserved", शून्य,
	 IGU_ADDR_TYPE_RESERVEDपूर्ण,
	अणु0x200, 0x200, "Write PBA[0:63]", शून्य,
	 IGU_ADDR_TYPE_WRITE_PBAपूर्ण,
	अणु0x201, 0x201, "Write PBA[64:127]", "reserved",
	 IGU_ADDR_TYPE_WRITE_PBAपूर्ण,
	अणु0x202, 0x202, "Write PBA[128]", "reserved",
	 IGU_ADDR_TYPE_WRITE_PBAपूर्ण,
	अणु0x203, 0x3ff, "reserved", शून्य,
	 IGU_ADDR_TYPE_RESERVEDपूर्ण,
	अणु0x400, 0x5ef, "Write interrupt acknowledgment", शून्य,
	 IGU_ADDR_TYPE_WRITE_INT_ACKपूर्ण,
	अणु0x5f0, 0x5f0, "Attention bits update", शून्य,
	 IGU_ADDR_TYPE_WRITE_ATTN_BITSपूर्ण,
	अणु0x5f1, 0x5f1, "Attention bits set", शून्य,
	 IGU_ADDR_TYPE_WRITE_ATTN_BITSपूर्ण,
	अणु0x5f2, 0x5f2, "Attention bits clear", शून्य,
	 IGU_ADDR_TYPE_WRITE_ATTN_BITSपूर्ण,
	अणु0x5f3, 0x5f3, "Read interrupt 0:63 with mask", शून्य,
	 IGU_ADDR_TYPE_READ_INTपूर्ण,
	अणु0x5f4, 0x5f4, "Read interrupt 0:31 with mask", शून्य,
	 IGU_ADDR_TYPE_READ_INTपूर्ण,
	अणु0x5f5, 0x5f5, "Read interrupt 32:63 with mask", शून्य,
	 IGU_ADDR_TYPE_READ_INTपूर्ण,
	अणु0x5f6, 0x5f6, "Read interrupt 0:63 without mask", शून्य,
	 IGU_ADDR_TYPE_READ_INTपूर्ण,
	अणु0x5f7, 0x5ff, "reserved", शून्य,
	 IGU_ADDR_TYPE_RESERVEDपूर्ण,
	अणु0x600, 0x7ff, "Producer update", शून्य,
	 IGU_ADDR_TYPE_WRITE_PROD_UPDATEपूर्ण
पूर्ण;

/******************************** Variables **********************************/

/* Temporary buffer, used क्रम prपूर्णांक size calculations */
अटल अक्षर s_temp_buf[MAX_MSG_LEN];

/**************************** Private Functions ******************************/

अटल u32 qed_cyclic_add(u32 a, u32 b, u32 size)
अणु
	वापस (a + b) % size;
पूर्ण

अटल u32 qed_cyclic_sub(u32 a, u32 b, u32 size)
अणु
	वापस (size + a - b) % size;
पूर्ण

/* Reads the specअगरied number of bytes from the specअगरied cyclic buffer (up to 4
 * bytes) and वापसs them as a dword value. the specअगरied buffer offset is
 * updated.
 */
अटल u32 qed_पढ़ो_from_cyclic_buf(व्योम *buf,
				    u32 *offset,
				    u32 buf_size, u8 num_bytes_to_पढ़ो)
अणु
	u8 i, *val_ptr, *bytes_buf = (u8 *)buf;
	u32 val = 0;

	val_ptr = (u8 *)&val;

	/* Assume running on a LITTLE ENDIAN and the buffer is network order
	 * (BIG ENDIAN), as high order bytes are placed in lower memory address.
	 */
	क्रम (i = 0; i < num_bytes_to_पढ़ो; i++) अणु
		val_ptr[i] = bytes_buf[*offset];
		*offset = qed_cyclic_add(*offset, 1, buf_size);
	पूर्ण

	वापस val;
पूर्ण

/* Reads and वापसs the next byte from the specअगरied buffer.
 * The specअगरied buffer offset is updated.
 */
अटल u8 qed_पढ़ो_byte_from_buf(व्योम *buf, u32 *offset)
अणु
	वापस ((u8 *)buf)[(*offset)++];
पूर्ण

/* Reads and वापसs the next dword from the specअगरied buffer.
 * The specअगरied buffer offset is updated.
 */
अटल u32 qed_पढ़ो_dword_from_buf(व्योम *buf, u32 *offset)
अणु
	u32 dword_val = *(u32 *)&((u8 *)buf)[*offset];

	*offset += 4;

	वापस dword_val;
पूर्ण

/* Reads the next string from the specअगरied buffer, and copies it to the
 * specअगरied poपूर्णांकer. The specअगरied buffer offset is updated.
 */
अटल व्योम qed_पढ़ो_str_from_buf(व्योम *buf, u32 *offset, u32 size, अक्षर *dest)
अणु
	स्थिर अक्षर *source_str = &((स्थिर अक्षर *)buf)[*offset];

	म_नकलन(dest, source_str, size);
	dest[size - 1] = '\0';
	*offset += size;
पूर्ण

/* Returns a poपूर्णांकer to the specअगरied offset (in bytes) of the specअगरied buffer.
 * If the specअगरied buffer in शून्य, a temporary buffer poपूर्णांकer is वापसed.
 */
अटल अक्षर *qed_get_buf_ptr(व्योम *buf, u32 offset)
अणु
	वापस buf ? (अक्षर *)buf + offset : s_temp_buf;
पूर्ण

/* Reads a param from the specअगरied buffer. Returns the number of dwords पढ़ो.
 * If the वापसed str_param is शून्य, the param is numeric and its value is
 * वापसed in num_param.
 * Otheriwise, the param is a string and its poपूर्णांकer is वापसed in str_param.
 */
अटल u32 qed_पढ़ो_param(u32 *dump_buf,
			  स्थिर अक्षर **param_name,
			  स्थिर अक्षर **param_str_val, u32 *param_num_val)
अणु
	अक्षर *अक्षर_buf = (अक्षर *)dump_buf;
	माप_प्रकार offset = 0;

	/* Extract param name */
	*param_name = अक्षर_buf;
	offset += म_माप(*param_name) + 1;

	/* Check param type */
	अगर (*(अक्षर_buf + offset++)) अणु
		/* String param */
		*param_str_val = अक्षर_buf + offset;
		*param_num_val = 0;
		offset += म_माप(*param_str_val) + 1;
		अगर (offset & 0x3)
			offset += (4 - (offset & 0x3));
	पूर्ण अन्यथा अणु
		/* Numeric param */
		*param_str_val = शून्य;
		अगर (offset & 0x3)
			offset += (4 - (offset & 0x3));
		*param_num_val = *(u32 *)(अक्षर_buf + offset);
		offset += 4;
	पूर्ण

	वापस (u32)offset / 4;
पूर्ण

/* Reads a section header from the specअगरied buffer.
 * Returns the number of dwords पढ़ो.
 */
अटल u32 qed_पढ़ो_section_hdr(u32 *dump_buf,
				स्थिर अक्षर **section_name,
				u32 *num_section_params)
अणु
	स्थिर अक्षर *param_str_val;

	वापस qed_पढ़ो_param(dump_buf,
			      section_name, &param_str_val, num_section_params);
पूर्ण

/* Reads section params from the specअगरied buffer and prपूर्णांकs them to the results
 * buffer. Returns the number of dwords पढ़ो.
 */
अटल u32 qed_prपूर्णांक_section_params(u32 *dump_buf,
				    u32 num_section_params,
				    अक्षर *results_buf, u32 *num_अक्षरs_prपूर्णांकed)
अणु
	u32 i, dump_offset = 0, results_offset = 0;

	क्रम (i = 0; i < num_section_params; i++) अणु
		स्थिर अक्षर *param_name, *param_str_val;
		u32 param_num_val = 0;

		dump_offset += qed_पढ़ो_param(dump_buf + dump_offset,
					      &param_name,
					      &param_str_val, &param_num_val);

		अगर (param_str_val)
			results_offset +=
				प्र_लिखो(qed_get_buf_ptr(results_buf,
							results_offset),
					"%s: %s\n", param_name, param_str_val);
		अन्यथा अगर (म_भेद(param_name, "fw-timestamp"))
			results_offset +=
				प्र_लिखो(qed_get_buf_ptr(results_buf,
							results_offset),
					"%s: %d\n", param_name, param_num_val);
	पूर्ण

	results_offset += प्र_लिखो(qed_get_buf_ptr(results_buf, results_offset),
				  "\n");

	*num_अक्षरs_prपूर्णांकed = results_offset;

	वापस dump_offset;
पूर्ण

/* Returns the block name that matches the specअगरied block ID,
 * or शून्य अगर not found.
 */
अटल स्थिर अक्षर *qed_dbg_get_block_name(काष्ठा qed_hwfn *p_hwfn,
					  क्रमागत block_id block_id)
अणु
	स्थिर काष्ठा dbg_block_user *block =
	    (स्थिर काष्ठा dbg_block_user *)
	    p_hwfn->dbg_arrays[BIN_BUF_DBG_BLOCKS_USER_DATA].ptr + block_id;

	वापस (स्थिर अक्षर *)block->name;
पूर्ण

अटल काष्ठा dbg_tools_user_data *qed_dbg_get_user_data(काष्ठा qed_hwfn
							 *p_hwfn)
अणु
	वापस (काष्ठा dbg_tools_user_data *)p_hwfn->dbg_user_info;
पूर्ण

/* Parses the idle check rules and वापसs the number of अक्षरacters prपूर्णांकed.
 * In हाल of parsing error, वापसs 0.
 */
अटल u32 qed_parse_idle_chk_dump_rules(काष्ठा qed_hwfn *p_hwfn,
					 u32 *dump_buf,
					 u32 *dump_buf_end,
					 u32 num_rules,
					 bool prपूर्णांक_fw_idle_chk,
					 अक्षर *results_buf,
					 u32 *num_errors, u32 *num_warnings)
अणु
	/* Offset in results_buf in bytes */
	u32 results_offset = 0;

	u32 rule_idx;
	u16 i, j;

	*num_errors = 0;
	*num_warnings = 0;

	/* Go over dumped results */
	क्रम (rule_idx = 0; rule_idx < num_rules && dump_buf < dump_buf_end;
	     rule_idx++) अणु
		स्थिर काष्ठा dbg_idle_chk_rule_parsing_data *rule_parsing_data;
		काष्ठा dbg_idle_chk_result_hdr *hdr;
		स्थिर अक्षर *parsing_str, *lsi_msg;
		u32 parsing_str_offset;
		bool has_fw_msg;
		u8 curr_reg_id;

		hdr = (काष्ठा dbg_idle_chk_result_hdr *)dump_buf;
		rule_parsing_data =
		    (स्थिर काष्ठा dbg_idle_chk_rule_parsing_data *)
		    p_hwfn->dbg_arrays[BIN_BUF_DBG_IDLE_CHK_PARSING_DATA].ptr +
		    hdr->rule_id;
		parsing_str_offset =
		    GET_FIELD(rule_parsing_data->data,
			      DBG_IDLE_CHK_RULE_PARSING_DATA_STR_OFFSET);
		has_fw_msg =
		    GET_FIELD(rule_parsing_data->data,
			      DBG_IDLE_CHK_RULE_PARSING_DATA_HAS_FW_MSG) > 0;
		parsing_str = (स्थिर अक्षर *)
		    p_hwfn->dbg_arrays[BIN_BUF_DBG_PARSING_STRINGS].ptr +
		    parsing_str_offset;
		lsi_msg = parsing_str;
		curr_reg_id = 0;

		अगर (hdr->severity >= MAX_DBG_IDLE_CHK_SEVERITY_TYPES)
			वापस 0;

		/* Skip rule header */
		dump_buf += BYTES_TO_DWORDS(माप(*hdr));

		/* Update errors/warnings count */
		अगर (hdr->severity == IDLE_CHK_SEVERITY_ERROR ||
		    hdr->severity == IDLE_CHK_SEVERITY_ERROR_NO_TRAFFIC)
			(*num_errors)++;
		अन्यथा
			(*num_warnings)++;

		/* Prपूर्णांक rule severity */
		results_offset +=
		    प्र_लिखो(qed_get_buf_ptr(results_buf,
					    results_offset), "%s: ",
			    s_idle_chk_severity_str[hdr->severity]);

		/* Prपूर्णांक rule message */
		अगर (has_fw_msg)
			parsing_str += म_माप(parsing_str) + 1;
		results_offset +=
		    प्र_लिखो(qed_get_buf_ptr(results_buf,
					    results_offset), "%s.",
			    has_fw_msg &&
			    prपूर्णांक_fw_idle_chk ? parsing_str : lsi_msg);
		parsing_str += म_माप(parsing_str) + 1;

		/* Prपूर्णांक रेजिस्टर values */
		results_offset +=
		    प्र_लिखो(qed_get_buf_ptr(results_buf,
					    results_offset), " Registers:");
		क्रम (i = 0;
		     i < hdr->num_dumped_cond_regs + hdr->num_dumped_info_regs;
		     i++) अणु
			काष्ठा dbg_idle_chk_result_reg_hdr *reg_hdr;
			bool is_mem;
			u8 reg_id;

			reg_hdr =
				(काष्ठा dbg_idle_chk_result_reg_hdr *)dump_buf;
			is_mem = GET_FIELD(reg_hdr->data,
					   DBG_IDLE_CHK_RESULT_REG_HDR_IS_MEM);
			reg_id = GET_FIELD(reg_hdr->data,
					   DBG_IDLE_CHK_RESULT_REG_HDR_REG_ID);

			/* Skip reg header */
			dump_buf += BYTES_TO_DWORDS(माप(*reg_hdr));

			/* Skip रेजिस्टर names until the required reg_id is
			 * reached.
			 */
			क्रम (; reg_id > curr_reg_id;
			     curr_reg_id++,
			     parsing_str += म_माप(parsing_str) + 1);

			results_offset +=
			    प्र_लिखो(qed_get_buf_ptr(results_buf,
						    results_offset), " %s",
				    parsing_str);
			अगर (i < hdr->num_dumped_cond_regs && is_mem)
				results_offset +=
				    प्र_लिखो(qed_get_buf_ptr(results_buf,
							    results_offset),
					    "[%d]", hdr->mem_entry_id +
					    reg_hdr->start_entry);
			results_offset +=
			    प्र_लिखो(qed_get_buf_ptr(results_buf,
						    results_offset), "=");
			क्रम (j = 0; j < reg_hdr->size; j++, dump_buf++) अणु
				results_offset +=
				    प्र_लिखो(qed_get_buf_ptr(results_buf,
							    results_offset),
					    "0x%x", *dump_buf);
				अगर (j < reg_hdr->size - 1)
					results_offset +=
					    प्र_लिखो(qed_get_buf_ptr
						    (results_buf,
						     results_offset), ",");
			पूर्ण
		पूर्ण

		results_offset +=
		    प्र_लिखो(qed_get_buf_ptr(results_buf, results_offset), "\n");
	पूर्ण

	/* Check अगर end of dump buffer was exceeded */
	अगर (dump_buf > dump_buf_end)
		वापस 0;

	वापस results_offset;
पूर्ण

/* Parses an idle check dump buffer.
 * If result_buf is not शून्य, the idle check results are prपूर्णांकed to it.
 * In any हाल, the required results buffer size is asचिन्हित to
 * parsed_results_bytes.
 * The parsing status is वापसed.
 */
अटल क्रमागत dbg_status qed_parse_idle_chk_dump(काष्ठा qed_hwfn *p_hwfn,
					       u32 *dump_buf,
					       u32 num_dumped_dwords,
					       अक्षर *results_buf,
					       u32 *parsed_results_bytes,
					       u32 *num_errors,
					       u32 *num_warnings)
अणु
	स्थिर अक्षर *section_name, *param_name, *param_str_val;
	u32 *dump_buf_end = dump_buf + num_dumped_dwords;
	u32 num_section_params = 0, num_rules;

	/* Offset in results_buf in bytes */
	u32 results_offset = 0;

	*parsed_results_bytes = 0;
	*num_errors = 0;
	*num_warnings = 0;

	अगर (!p_hwfn->dbg_arrays[BIN_BUF_DBG_PARSING_STRINGS].ptr ||
	    !p_hwfn->dbg_arrays[BIN_BUF_DBG_IDLE_CHK_PARSING_DATA].ptr)
		वापस DBG_STATUS_DBG_ARRAY_NOT_SET;

	/* Read global_params section */
	dump_buf += qed_पढ़ो_section_hdr(dump_buf,
					 &section_name, &num_section_params);
	अगर (म_भेद(section_name, "global_params"))
		वापस DBG_STATUS_IDLE_CHK_PARSE_FAILED;

	/* Prपूर्णांक global params */
	dump_buf += qed_prपूर्णांक_section_params(dump_buf,
					     num_section_params,
					     results_buf, &results_offset);

	/* Read idle_chk section */
	dump_buf += qed_पढ़ो_section_hdr(dump_buf,
					 &section_name, &num_section_params);
	अगर (म_भेद(section_name, "idle_chk") || num_section_params != 1)
		वापस DBG_STATUS_IDLE_CHK_PARSE_FAILED;
	dump_buf += qed_पढ़ो_param(dump_buf,
				   &param_name, &param_str_val, &num_rules);
	अगर (म_भेद(param_name, "num_rules"))
		वापस DBG_STATUS_IDLE_CHK_PARSE_FAILED;

	अगर (num_rules) अणु
		u32 rules_prपूर्णांक_size;

		/* Prपूर्णांक FW output */
		results_offset +=
		    प्र_लिखो(qed_get_buf_ptr(results_buf,
					    results_offset),
			    "FW_IDLE_CHECK:\n");
		rules_prपूर्णांक_size =
			qed_parse_idle_chk_dump_rules(p_hwfn,
						      dump_buf,
						      dump_buf_end,
						      num_rules,
						      true,
						      results_buf ?
						      results_buf +
						      results_offset :
						      शून्य,
						      num_errors,
						      num_warnings);
		results_offset += rules_prपूर्णांक_size;
		अगर (!rules_prपूर्णांक_size)
			वापस DBG_STATUS_IDLE_CHK_PARSE_FAILED;

		/* Prपूर्णांक LSI output */
		results_offset +=
		    प्र_लिखो(qed_get_buf_ptr(results_buf,
					    results_offset),
			    "\nLSI_IDLE_CHECK:\n");
		rules_prपूर्णांक_size =
			qed_parse_idle_chk_dump_rules(p_hwfn,
						      dump_buf,
						      dump_buf_end,
						      num_rules,
						      false,
						      results_buf ?
						      results_buf +
						      results_offset :
						      शून्य,
						      num_errors,
						      num_warnings);
		results_offset += rules_prपूर्णांक_size;
		अगर (!rules_prपूर्णांक_size)
			वापस DBG_STATUS_IDLE_CHK_PARSE_FAILED;
	पूर्ण

	/* Prपूर्णांक errors/warnings count */
	अगर (*num_errors)
		results_offset +=
		    प्र_लिखो(qed_get_buf_ptr(results_buf,
					    results_offset),
			    "\nIdle Check failed!!! (with %d errors and %d warnings)\n",
			    *num_errors, *num_warnings);
	अन्यथा अगर (*num_warnings)
		results_offset +=
		    प्र_लिखो(qed_get_buf_ptr(results_buf,
					    results_offset),
			    "\nIdle Check completed successfully (with %d warnings)\n",
			    *num_warnings);
	अन्यथा
		results_offset +=
		    प्र_लिखो(qed_get_buf_ptr(results_buf,
					    results_offset),
			    "\nIdle Check completed successfully\n");

	/* Add 1 क्रम string शून्य termination */
	*parsed_results_bytes = results_offset + 1;

	वापस DBG_STATUS_OK;
पूर्ण

/* Allocates and fills MCP Trace meta data based on the specअगरied meta data
 * dump buffer.
 * Returns debug status code.
 */
अटल क्रमागत dbg_status
qed_mcp_trace_alloc_meta_data(काष्ठा qed_hwfn *p_hwfn,
			      स्थिर u32 *meta_buf)
अणु
	काष्ठा dbg_tools_user_data *dev_user_data;
	u32 offset = 0, signature, i;
	काष्ठा mcp_trace_meta *meta;
	u8 *meta_buf_bytes;

	dev_user_data = qed_dbg_get_user_data(p_hwfn);
	meta = &dev_user_data->mcp_trace_meta;
	meta_buf_bytes = (u8 *)meta_buf;

	/* Free the previous meta beक्रमe loading a new one. */
	अगर (meta->is_allocated)
		qed_mcp_trace_मुक्त_meta_data(p_hwfn);

	स_रखो(meta, 0, माप(*meta));

	/* Read first signature */
	signature = qed_पढ़ो_dword_from_buf(meta_buf_bytes, &offset);
	अगर (signature != NVM_MAGIC_VALUE)
		वापस DBG_STATUS_INVALID_TRACE_SIGNATURE;

	/* Read no. of modules and allocate memory क्रम their poपूर्णांकers */
	meta->modules_num = qed_पढ़ो_byte_from_buf(meta_buf_bytes, &offset);
	meta->modules = kसुस्मृति(meta->modules_num, माप(अक्षर *),
				GFP_KERNEL);
	अगर (!meta->modules)
		वापस DBG_STATUS_VIRT_MEM_ALLOC_FAILED;

	/* Allocate and पढ़ो all module strings */
	क्रम (i = 0; i < meta->modules_num; i++) अणु
		u8 module_len = qed_पढ़ो_byte_from_buf(meta_buf_bytes, &offset);

		*(meta->modules + i) = kzalloc(module_len, GFP_KERNEL);
		अगर (!(*(meta->modules + i))) अणु
			/* Update number of modules to be released */
			meta->modules_num = i ? i - 1 : 0;
			वापस DBG_STATUS_VIRT_MEM_ALLOC_FAILED;
		पूर्ण

		qed_पढ़ो_str_from_buf(meta_buf_bytes, &offset, module_len,
				      *(meta->modules + i));
		अगर (module_len > MCP_TRACE_MAX_MODULE_LEN)
			(*(meta->modules + i))[MCP_TRACE_MAX_MODULE_LEN] = '\0';
	पूर्ण

	/* Read second signature */
	signature = qed_पढ़ो_dword_from_buf(meta_buf_bytes, &offset);
	अगर (signature != NVM_MAGIC_VALUE)
		वापस DBG_STATUS_INVALID_TRACE_SIGNATURE;

	/* Read number of क्रमmats and allocate memory क्रम all क्रमmats */
	meta->क्रमmats_num = qed_पढ़ो_dword_from_buf(meta_buf_bytes, &offset);
	meta->क्रमmats = kसुस्मृति(meta->क्रमmats_num,
				माप(काष्ठा mcp_trace_क्रमmat),
				GFP_KERNEL);
	अगर (!meta->क्रमmats)
		वापस DBG_STATUS_VIRT_MEM_ALLOC_FAILED;

	/* Allocate and पढ़ो all strings */
	क्रम (i = 0; i < meta->क्रमmats_num; i++) अणु
		काष्ठा mcp_trace_क्रमmat *क्रमmat_ptr = &meta->क्रमmats[i];
		u8 क्रमmat_len;

		क्रमmat_ptr->data = qed_पढ़ो_dword_from_buf(meta_buf_bytes,
							   &offset);
		क्रमmat_len = GET_MFW_FIELD(क्रमmat_ptr->data,
					   MCP_TRACE_FORMAT_LEN);
		क्रमmat_ptr->क्रमmat_str = kzalloc(क्रमmat_len, GFP_KERNEL);
		अगर (!क्रमmat_ptr->क्रमmat_str) अणु
			/* Update number of modules to be released */
			meta->क्रमmats_num = i ? i - 1 : 0;
			वापस DBG_STATUS_VIRT_MEM_ALLOC_FAILED;
		पूर्ण

		qed_पढ़ो_str_from_buf(meta_buf_bytes,
				      &offset,
				      क्रमmat_len, क्रमmat_ptr->क्रमmat_str);
	पूर्ण

	meta->is_allocated = true;
	वापस DBG_STATUS_OK;
पूर्ण

/* Parses an MCP trace buffer. If result_buf is not शून्य, the MCP Trace results
 * are prपूर्णांकed to it. The parsing status is वापसed.
 * Arguments:
 * trace_buf - MCP trace cyclic buffer
 * trace_buf_size - MCP trace cyclic buffer size in bytes
 * data_offset - offset in bytes of the data to parse in the MCP trace cyclic
 *		 buffer.
 * data_size - size in bytes of data to parse.
 * parsed_buf - destination buffer क्रम parsed data.
 * parsed_results_bytes - size of parsed data in bytes.
 */
अटल क्रमागत dbg_status qed_parse_mcp_trace_buf(काष्ठा qed_hwfn *p_hwfn,
					       u8 *trace_buf,
					       u32 trace_buf_size,
					       u32 data_offset,
					       u32 data_size,
					       अक्षर *parsed_buf,
					       u32 *parsed_results_bytes)
अणु
	काष्ठा dbg_tools_user_data *dev_user_data;
	काष्ठा mcp_trace_meta *meta;
	u32 param_mask, param_shअगरt;
	क्रमागत dbg_status status;

	dev_user_data = qed_dbg_get_user_data(p_hwfn);
	meta = &dev_user_data->mcp_trace_meta;
	*parsed_results_bytes = 0;

	अगर (!meta->is_allocated)
		वापस DBG_STATUS_MCP_TRACE_BAD_DATA;

	status = DBG_STATUS_OK;

	जबतक (data_size) अणु
		काष्ठा mcp_trace_क्रमmat *क्रमmat_ptr;
		u8 क्रमmat_level, क्रमmat_module;
		u32 params[3] = अणु 0, 0, 0 पूर्ण;
		u32 header, क्रमmat_idx, i;

		अगर (data_size < MFW_TRACE_ENTRY_SIZE)
			वापस DBG_STATUS_MCP_TRACE_BAD_DATA;

		header = qed_पढ़ो_from_cyclic_buf(trace_buf,
						  &data_offset,
						  trace_buf_size,
						  MFW_TRACE_ENTRY_SIZE);
		data_size -= MFW_TRACE_ENTRY_SIZE;
		क्रमmat_idx = header & MFW_TRACE_EVENTID_MASK;

		/* Skip message अगर its index करोesn't exist in the meta data */
		अगर (क्रमmat_idx >= meta->क्रमmats_num) अणु
			u8 क्रमmat_size = (u8)GET_MFW_FIELD(header,
							   MFW_TRACE_PRM_SIZE);

			अगर (data_size < क्रमmat_size)
				वापस DBG_STATUS_MCP_TRACE_BAD_DATA;

			data_offset = qed_cyclic_add(data_offset,
						     क्रमmat_size,
						     trace_buf_size);
			data_size -= क्रमmat_size;
			जारी;
		पूर्ण

		क्रमmat_ptr = &meta->क्रमmats[क्रमmat_idx];

		क्रम (i = 0,
		     param_mask = MCP_TRACE_FORMAT_P1_SIZE_MASK, param_shअगरt =
		     MCP_TRACE_FORMAT_P1_SIZE_OFFSET;
		     i < MCP_TRACE_FORMAT_MAX_PARAMS;
		     i++, param_mask <<= MCP_TRACE_FORMAT_PARAM_WIDTH,
		     param_shअगरt += MCP_TRACE_FORMAT_PARAM_WIDTH) अणु
			/* Extract param size (0..3) */
			u8 param_size = (u8)((क्रमmat_ptr->data & param_mask) >>
					     param_shअगरt);

			/* If the param size is zero, there are no other
			 * parameters.
			 */
			अगर (!param_size)
				अवरोध;

			/* Size is encoded using 2 bits, where 3 is used to
			 * encode 4.
			 */
			अगर (param_size == 3)
				param_size = 4;

			अगर (data_size < param_size)
				वापस DBG_STATUS_MCP_TRACE_BAD_DATA;

			params[i] = qed_पढ़ो_from_cyclic_buf(trace_buf,
							     &data_offset,
							     trace_buf_size,
							     param_size);
			data_size -= param_size;
		पूर्ण

		क्रमmat_level = (u8)GET_MFW_FIELD(क्रमmat_ptr->data,
						 MCP_TRACE_FORMAT_LEVEL);
		क्रमmat_module = (u8)GET_MFW_FIELD(क्रमmat_ptr->data,
						  MCP_TRACE_FORMAT_MODULE);
		अगर (क्रमmat_level >= ARRAY_SIZE(s_mcp_trace_level_str))
			वापस DBG_STATUS_MCP_TRACE_BAD_DATA;

		/* Prपूर्णांक current message to results buffer */
		*parsed_results_bytes +=
			प्र_लिखो(qed_get_buf_ptr(parsed_buf,
						*parsed_results_bytes),
				"%s %-8s: ",
				s_mcp_trace_level_str[क्रमmat_level],
				meta->modules[क्रमmat_module]);
		*parsed_results_bytes +=
		    प्र_लिखो(qed_get_buf_ptr(parsed_buf, *parsed_results_bytes),
			    क्रमmat_ptr->क्रमmat_str,
			    params[0], params[1], params[2]);
	पूर्ण

	/* Add string शून्य terminator */
	(*parsed_results_bytes)++;

	वापस status;
पूर्ण

/* Parses an MCP Trace dump buffer.
 * If result_buf is not शून्य, the MCP Trace results are prपूर्णांकed to it.
 * In any हाल, the required results buffer size is asचिन्हित to
 * parsed_results_bytes.
 * The parsing status is वापसed.
 */
अटल क्रमागत dbg_status qed_parse_mcp_trace_dump(काष्ठा qed_hwfn *p_hwfn,
						u32 *dump_buf,
						अक्षर *results_buf,
						u32 *parsed_results_bytes,
						bool मुक्त_meta_data)
अणु
	स्थिर अक्षर *section_name, *param_name, *param_str_val;
	u32 data_size, trace_data_dwords, trace_meta_dwords;
	u32 offset, results_offset, results_buf_bytes;
	u32 param_num_val, num_section_params;
	काष्ठा mcp_trace *trace;
	क्रमागत dbg_status status;
	स्थिर u32 *meta_buf;
	u8 *trace_buf;

	*parsed_results_bytes = 0;

	/* Read global_params section */
	dump_buf += qed_पढ़ो_section_hdr(dump_buf,
					 &section_name, &num_section_params);
	अगर (म_भेद(section_name, "global_params"))
		वापस DBG_STATUS_MCP_TRACE_BAD_DATA;

	/* Prपूर्णांक global params */
	dump_buf += qed_prपूर्णांक_section_params(dump_buf,
					     num_section_params,
					     results_buf, &results_offset);

	/* Read trace_data section */
	dump_buf += qed_पढ़ो_section_hdr(dump_buf,
					 &section_name, &num_section_params);
	अगर (म_भेद(section_name, "mcp_trace_data") || num_section_params != 1)
		वापस DBG_STATUS_MCP_TRACE_BAD_DATA;
	dump_buf += qed_पढ़ो_param(dump_buf,
				   &param_name, &param_str_val, &param_num_val);
	अगर (म_भेद(param_name, "size"))
		वापस DBG_STATUS_MCP_TRACE_BAD_DATA;
	trace_data_dwords = param_num_val;

	/* Prepare trace info */
	trace = (काष्ठा mcp_trace *)dump_buf;
	अगर (trace->signature != MFW_TRACE_SIGNATURE || !trace->size)
		वापस DBG_STATUS_MCP_TRACE_BAD_DATA;

	trace_buf = (u8 *)dump_buf + माप(*trace);
	offset = trace->trace_oldest;
	data_size = qed_cyclic_sub(trace->trace_prod, offset, trace->size);
	dump_buf += trace_data_dwords;

	/* Read meta_data section */
	dump_buf += qed_पढ़ो_section_hdr(dump_buf,
					 &section_name, &num_section_params);
	अगर (म_भेद(section_name, "mcp_trace_meta"))
		वापस DBG_STATUS_MCP_TRACE_BAD_DATA;
	dump_buf += qed_पढ़ो_param(dump_buf,
				   &param_name, &param_str_val, &param_num_val);
	अगर (म_भेद(param_name, "size"))
		वापस DBG_STATUS_MCP_TRACE_BAD_DATA;
	trace_meta_dwords = param_num_val;

	/* Choose meta data buffer */
	अगर (!trace_meta_dwords) अणु
		/* Dump करोesn't include meta data */
		काष्ठा dbg_tools_user_data *dev_user_data =
			qed_dbg_get_user_data(p_hwfn);

		अगर (!dev_user_data->mcp_trace_user_meta_buf)
			वापस DBG_STATUS_MCP_TRACE_NO_META;

		meta_buf = dev_user_data->mcp_trace_user_meta_buf;
	पूर्ण अन्यथा अणु
		/* Dump includes meta data */
		meta_buf = dump_buf;
	पूर्ण

	/* Allocate meta data memory */
	status = qed_mcp_trace_alloc_meta_data(p_hwfn, meta_buf);
	अगर (status != DBG_STATUS_OK)
		वापस status;

	status = qed_parse_mcp_trace_buf(p_hwfn,
					 trace_buf,
					 trace->size,
					 offset,
					 data_size,
					 results_buf ?
					 results_buf + results_offset :
					 शून्य,
					 &results_buf_bytes);
	अगर (status != DBG_STATUS_OK)
		वापस status;

	अगर (मुक्त_meta_data)
		qed_mcp_trace_मुक्त_meta_data(p_hwfn);

	*parsed_results_bytes = results_offset + results_buf_bytes;

	वापस DBG_STATUS_OK;
पूर्ण

/* Parses a Reg FIFO dump buffer.
 * If result_buf is not शून्य, the Reg FIFO results are prपूर्णांकed to it.
 * In any हाल, the required results buffer size is asचिन्हित to
 * parsed_results_bytes.
 * The parsing status is वापसed.
 */
अटल क्रमागत dbg_status qed_parse_reg_fअगरo_dump(u32 *dump_buf,
					       अक्षर *results_buf,
					       u32 *parsed_results_bytes)
अणु
	स्थिर अक्षर *section_name, *param_name, *param_str_val;
	u32 param_num_val, num_section_params, num_elements;
	काष्ठा reg_fअगरo_element *elements;
	u8 i, j, err_code, vf_val;
	u32 results_offset = 0;
	अक्षर vf_str[4];

	/* Read global_params section */
	dump_buf += qed_पढ़ो_section_hdr(dump_buf,
					 &section_name, &num_section_params);
	अगर (म_भेद(section_name, "global_params"))
		वापस DBG_STATUS_REG_FIFO_BAD_DATA;

	/* Prपूर्णांक global params */
	dump_buf += qed_prपूर्णांक_section_params(dump_buf,
					     num_section_params,
					     results_buf, &results_offset);

	/* Read reg_fअगरo_data section */
	dump_buf += qed_पढ़ो_section_hdr(dump_buf,
					 &section_name, &num_section_params);
	अगर (म_भेद(section_name, "reg_fifo_data"))
		वापस DBG_STATUS_REG_FIFO_BAD_DATA;
	dump_buf += qed_पढ़ो_param(dump_buf,
				   &param_name, &param_str_val, &param_num_val);
	अगर (म_भेद(param_name, "size"))
		वापस DBG_STATUS_REG_FIFO_BAD_DATA;
	अगर (param_num_val % REG_FIFO_ELEMENT_DWORDS)
		वापस DBG_STATUS_REG_FIFO_BAD_DATA;
	num_elements = param_num_val / REG_FIFO_ELEMENT_DWORDS;
	elements = (काष्ठा reg_fअगरo_element *)dump_buf;

	/* Decode elements */
	क्रम (i = 0; i < num_elements; i++) अणु
		स्थिर अक्षर *err_msg = शून्य;

		/* Discover अगर element beदीर्घs to a VF or a PF */
		vf_val = GET_FIELD(elements[i].data, REG_FIFO_ELEMENT_VF);
		अगर (vf_val == REG_FIFO_ELEMENT_IS_PF_VF_VAL)
			प्र_लिखो(vf_str, "%s", "N/A");
		अन्यथा
			प्र_लिखो(vf_str, "%d", vf_val);

		/* Find error message */
		err_code = GET_FIELD(elements[i].data, REG_FIFO_ELEMENT_ERROR);
		क्रम (j = 0; j < ARRAY_SIZE(s_reg_fअगरo_errors) && !err_msg; j++)
			अगर (err_code == s_reg_fअगरo_errors[j].err_code)
				err_msg = s_reg_fअगरo_errors[j].err_msg;

		/* Add parsed element to parsed buffer */
		results_offset +=
		    प्र_लिखो(qed_get_buf_ptr(results_buf,
					    results_offset),
			    "raw: 0x%016llx, address: 0x%07x, access: %-5s, pf: %2d, vf: %s, port: %d, privilege: %-3s, protection: %-12s, master: %-4s, error: %s\n",
			    elements[i].data,
			    (u32)GET_FIELD(elements[i].data,
					   REG_FIFO_ELEMENT_ADDRESS) *
			    REG_FIFO_ELEMENT_ADDR_FACTOR,
			    s_access_strs[GET_FIELD(elements[i].data,
						    REG_FIFO_ELEMENT_ACCESS)],
			    (u32)GET_FIELD(elements[i].data,
					   REG_FIFO_ELEMENT_PF),
			    vf_str,
			    (u32)GET_FIELD(elements[i].data,
					   REG_FIFO_ELEMENT_PORT),
			    s_privilege_strs[GET_FIELD(elements[i].data,
						REG_FIFO_ELEMENT_PRIVILEGE)],
			    s_protection_strs[GET_FIELD(elements[i].data,
						REG_FIFO_ELEMENT_PROTECTION)],
			    s_master_strs[GET_FIELD(elements[i].data,
						    REG_FIFO_ELEMENT_MASTER)],
			    err_msg ? err_msg : "unknown error code");
	पूर्ण

	results_offset += प्र_लिखो(qed_get_buf_ptr(results_buf,
						  results_offset),
				  "fifo contained %d elements", num_elements);

	/* Add 1 क्रम string शून्य termination */
	*parsed_results_bytes = results_offset + 1;

	वापस DBG_STATUS_OK;
पूर्ण

अटल क्रमागत dbg_status qed_parse_igu_fअगरo_element(काष्ठा igu_fअगरo_element
						  *element, अक्षर
						  *results_buf,
						  u32 *results_offset)
अणु
	स्थिर काष्ठा igu_fअगरo_addr_data *found_addr = शून्य;
	u8 source, err_type, i, is_cleanup;
	अक्षर parsed_addr_data[32];
	अक्षर parsed_wr_data[256];
	u32 wr_data, prod_cons;
	bool is_wr_cmd, is_pf;
	u16 cmd_addr;
	u64 dword12;

	/* Dword12 (dword index 1 and 2) contains bits 32..95 of the
	 * FIFO element.
	 */
	dword12 = ((u64)element->dword2 << 32) | element->dword1;
	is_wr_cmd = GET_FIELD(dword12, IGU_FIFO_ELEMENT_DWORD12_IS_WR_CMD);
	is_pf = GET_FIELD(element->dword0, IGU_FIFO_ELEMENT_DWORD0_IS_PF);
	cmd_addr = GET_FIELD(element->dword0, IGU_FIFO_ELEMENT_DWORD0_CMD_ADDR);
	source = GET_FIELD(element->dword0, IGU_FIFO_ELEMENT_DWORD0_SOURCE);
	err_type = GET_FIELD(element->dword0, IGU_FIFO_ELEMENT_DWORD0_ERR_TYPE);

	अगर (source >= ARRAY_SIZE(s_igu_fअगरo_source_strs))
		वापस DBG_STATUS_IGU_FIFO_BAD_DATA;
	अगर (err_type >= ARRAY_SIZE(s_igu_fअगरo_error_strs))
		वापस DBG_STATUS_IGU_FIFO_BAD_DATA;

	/* Find address data */
	क्रम (i = 0; i < ARRAY_SIZE(s_igu_fअगरo_addr_data) && !found_addr; i++) अणु
		स्थिर काष्ठा igu_fअगरo_addr_data *curr_addr =
			&s_igu_fअगरo_addr_data[i];

		अगर (cmd_addr >= curr_addr->start_addr && cmd_addr <=
		    curr_addr->end_addr)
			found_addr = curr_addr;
	पूर्ण

	अगर (!found_addr)
		वापस DBG_STATUS_IGU_FIFO_BAD_DATA;

	/* Prepare parsed address data */
	चयन (found_addr->type) अणु
	हाल IGU_ADDR_TYPE_MSIX_MEM:
		प्र_लिखो(parsed_addr_data, " vector_num = 0x%x", cmd_addr / 2);
		अवरोध;
	हाल IGU_ADDR_TYPE_WRITE_INT_ACK:
	हाल IGU_ADDR_TYPE_WRITE_PROD_UPDATE:
		प्र_लिखो(parsed_addr_data,
			" SB = 0x%x", cmd_addr - found_addr->start_addr);
		अवरोध;
	शेष:
		parsed_addr_data[0] = '\0';
	पूर्ण

	अगर (!is_wr_cmd) अणु
		parsed_wr_data[0] = '\0';
		जाओ out;
	पूर्ण

	/* Prepare parsed ग_लिखो data */
	wr_data = GET_FIELD(dword12, IGU_FIFO_ELEMENT_DWORD12_WR_DATA);
	prod_cons = GET_FIELD(wr_data, IGU_FIFO_WR_DATA_PROD_CONS);
	is_cleanup = GET_FIELD(wr_data, IGU_FIFO_WR_DATA_CMD_TYPE);

	अगर (source == IGU_SRC_ATTN) अणु
		प्र_लिखो(parsed_wr_data, "prod: 0x%x, ", prod_cons);
	पूर्ण अन्यथा अणु
		अगर (is_cleanup) अणु
			u8 cleanup_val, cleanup_type;

			cleanup_val =
				GET_FIELD(wr_data,
					  IGU_FIFO_CLEANUP_WR_DATA_CLEANUP_VAL);
			cleanup_type =
			    GET_FIELD(wr_data,
				      IGU_FIFO_CLEANUP_WR_DATA_CLEANUP_TYPE);

			प्र_लिखो(parsed_wr_data,
				"cmd_type: cleanup, cleanup_val: %s, cleanup_type : %d, ",
				cleanup_val ? "set" : "clear",
				cleanup_type);
		पूर्ण अन्यथा अणु
			u8 update_flag, en_dis_पूर्णांक_क्रम_sb, segment;
			u8 समयr_mask;

			update_flag = GET_FIELD(wr_data,
						IGU_FIFO_WR_DATA_UPDATE_FLAG);
			en_dis_पूर्णांक_क्रम_sb =
				GET_FIELD(wr_data,
					  IGU_FIFO_WR_DATA_EN_DIS_INT_FOR_SB);
			segment = GET_FIELD(wr_data,
					    IGU_FIFO_WR_DATA_SEGMENT);
			समयr_mask = GET_FIELD(wr_data,
					       IGU_FIFO_WR_DATA_TIMER_MASK);

			प्र_लिखो(parsed_wr_data,
				"cmd_type: prod/cons update, prod/cons: 0x%x, update_flag: %s, en_dis_int_for_sb : %s, segment : %s, timer_mask = %d, ",
				prod_cons,
				update_flag ? "update" : "nop",
				en_dis_पूर्णांक_क्रम_sb ?
				(en_dis_पूर्णांक_क्रम_sb == 1 ? "disable" : "nop") :
				"enable",
				segment ? "attn" : "regular",
				समयr_mask);
		पूर्ण
	पूर्ण
out:
	/* Add parsed element to parsed buffer */
	*results_offset += प्र_लिखो(qed_get_buf_ptr(results_buf,
						   *results_offset),
				   "raw: 0x%01x%08x%08x, %s: %d, source : %s, type : %s, cmd_addr : 0x%x(%s%s), %serror: %s\n",
				   element->dword2, element->dword1,
				   element->dword0,
				   is_pf ? "pf" : "vf",
				   GET_FIELD(element->dword0,
					     IGU_FIFO_ELEMENT_DWORD0_FID),
				   s_igu_fअगरo_source_strs[source],
				   is_wr_cmd ? "wr" : "rd",
				   cmd_addr,
				   (!is_pf && found_addr->vf_desc)
				   ? found_addr->vf_desc
				   : found_addr->desc,
				   parsed_addr_data,
				   parsed_wr_data,
				   s_igu_fअगरo_error_strs[err_type]);

	वापस DBG_STATUS_OK;
पूर्ण

/* Parses an IGU FIFO dump buffer.
 * If result_buf is not शून्य, the IGU FIFO results are prपूर्णांकed to it.
 * In any हाल, the required results buffer size is asचिन्हित to
 * parsed_results_bytes.
 * The parsing status is वापसed.
 */
अटल क्रमागत dbg_status qed_parse_igu_fअगरo_dump(u32 *dump_buf,
					       अक्षर *results_buf,
					       u32 *parsed_results_bytes)
अणु
	स्थिर अक्षर *section_name, *param_name, *param_str_val;
	u32 param_num_val, num_section_params, num_elements;
	काष्ठा igu_fअगरo_element *elements;
	क्रमागत dbg_status status;
	u32 results_offset = 0;
	u8 i;

	/* Read global_params section */
	dump_buf += qed_पढ़ो_section_hdr(dump_buf,
					 &section_name, &num_section_params);
	अगर (म_भेद(section_name, "global_params"))
		वापस DBG_STATUS_IGU_FIFO_BAD_DATA;

	/* Prपूर्णांक global params */
	dump_buf += qed_prपूर्णांक_section_params(dump_buf,
					     num_section_params,
					     results_buf, &results_offset);

	/* Read igu_fअगरo_data section */
	dump_buf += qed_पढ़ो_section_hdr(dump_buf,
					 &section_name, &num_section_params);
	अगर (म_भेद(section_name, "igu_fifo_data"))
		वापस DBG_STATUS_IGU_FIFO_BAD_DATA;
	dump_buf += qed_पढ़ो_param(dump_buf,
				   &param_name, &param_str_val, &param_num_val);
	अगर (म_भेद(param_name, "size"))
		वापस DBG_STATUS_IGU_FIFO_BAD_DATA;
	अगर (param_num_val % IGU_FIFO_ELEMENT_DWORDS)
		वापस DBG_STATUS_IGU_FIFO_BAD_DATA;
	num_elements = param_num_val / IGU_FIFO_ELEMENT_DWORDS;
	elements = (काष्ठा igu_fअगरo_element *)dump_buf;

	/* Decode elements */
	क्रम (i = 0; i < num_elements; i++) अणु
		status = qed_parse_igu_fअगरo_element(&elements[i],
						    results_buf,
						    &results_offset);
		अगर (status != DBG_STATUS_OK)
			वापस status;
	पूर्ण

	results_offset += प्र_लिखो(qed_get_buf_ptr(results_buf,
						  results_offset),
				  "fifo contained %d elements", num_elements);

	/* Add 1 क्रम string शून्य termination */
	*parsed_results_bytes = results_offset + 1;

	वापस DBG_STATUS_OK;
पूर्ण

अटल क्रमागत dbg_status
qed_parse_protection_override_dump(u32 *dump_buf,
				   अक्षर *results_buf,
				   u32 *parsed_results_bytes)
अणु
	स्थिर अक्षर *section_name, *param_name, *param_str_val;
	u32 param_num_val, num_section_params, num_elements;
	काष्ठा protection_override_element *elements;
	u32 results_offset = 0;
	u8 i;

	/* Read global_params section */
	dump_buf += qed_पढ़ो_section_hdr(dump_buf,
					 &section_name, &num_section_params);
	अगर (म_भेद(section_name, "global_params"))
		वापस DBG_STATUS_PROTECTION_OVERRIDE_BAD_DATA;

	/* Prपूर्णांक global params */
	dump_buf += qed_prपूर्णांक_section_params(dump_buf,
					     num_section_params,
					     results_buf, &results_offset);

	/* Read protection_override_data section */
	dump_buf += qed_पढ़ो_section_hdr(dump_buf,
					 &section_name, &num_section_params);
	अगर (म_भेद(section_name, "protection_override_data"))
		वापस DBG_STATUS_PROTECTION_OVERRIDE_BAD_DATA;
	dump_buf += qed_पढ़ो_param(dump_buf,
				   &param_name, &param_str_val, &param_num_val);
	अगर (म_भेद(param_name, "size"))
		वापस DBG_STATUS_PROTECTION_OVERRIDE_BAD_DATA;
	अगर (param_num_val % PROTECTION_OVERRIDE_ELEMENT_DWORDS)
		वापस DBG_STATUS_PROTECTION_OVERRIDE_BAD_DATA;
	num_elements = param_num_val / PROTECTION_OVERRIDE_ELEMENT_DWORDS;
	elements = (काष्ठा protection_override_element *)dump_buf;

	/* Decode elements */
	क्रम (i = 0; i < num_elements; i++) अणु
		u32 address = GET_FIELD(elements[i].data,
					PROTECTION_OVERRIDE_ELEMENT_ADDRESS) *
			      PROTECTION_OVERRIDE_ELEMENT_ADDR_FACTOR;

		results_offset +=
		    प्र_लिखो(qed_get_buf_ptr(results_buf,
					    results_offset),
			    "window %2d, address: 0x%07x, size: %7d regs, read: %d, write: %d, read protection: %-12s, write protection: %-12s\n",
			    i, address,
			    (u32)GET_FIELD(elements[i].data,
				      PROTECTION_OVERRIDE_ELEMENT_WINDOW_SIZE),
			    (u32)GET_FIELD(elements[i].data,
				      PROTECTION_OVERRIDE_ELEMENT_READ),
			    (u32)GET_FIELD(elements[i].data,
				      PROTECTION_OVERRIDE_ELEMENT_WRITE),
			    s_protection_strs[GET_FIELD(elements[i].data,
				PROTECTION_OVERRIDE_ELEMENT_READ_PROTECTION)],
			    s_protection_strs[GET_FIELD(elements[i].data,
				PROTECTION_OVERRIDE_ELEMENT_WRITE_PROTECTION)]);
	पूर्ण

	results_offset += प्र_लिखो(qed_get_buf_ptr(results_buf,
						  results_offset),
				  "protection override contained %d elements",
				  num_elements);

	/* Add 1 क्रम string शून्य termination */
	*parsed_results_bytes = results_offset + 1;

	वापस DBG_STATUS_OK;
पूर्ण

/* Parses a FW Asserts dump buffer.
 * If result_buf is not शून्य, the FW Asserts results are prपूर्णांकed to it.
 * In any हाल, the required results buffer size is asचिन्हित to
 * parsed_results_bytes.
 * The parsing status is वापसed.
 */
अटल क्रमागत dbg_status qed_parse_fw_निश्चितs_dump(u32 *dump_buf,
						 अक्षर *results_buf,
						 u32 *parsed_results_bytes)
अणु
	u32 num_section_params, param_num_val, i, results_offset = 0;
	स्थिर अक्षर *param_name, *param_str_val, *section_name;
	bool last_section_found = false;

	*parsed_results_bytes = 0;

	/* Read global_params section */
	dump_buf += qed_पढ़ो_section_hdr(dump_buf,
					 &section_name, &num_section_params);
	अगर (म_भेद(section_name, "global_params"))
		वापस DBG_STATUS_FW_ASSERTS_PARSE_FAILED;

	/* Prपूर्णांक global params */
	dump_buf += qed_prपूर्णांक_section_params(dump_buf,
					     num_section_params,
					     results_buf, &results_offset);

	जबतक (!last_section_found) अणु
		dump_buf += qed_पढ़ो_section_hdr(dump_buf,
						 &section_name,
						 &num_section_params);
		अगर (!म_भेद(section_name, "fw_asserts")) अणु
			/* Extract params */
			स्थिर अक्षर *storm_letter = शून्य;
			u32 storm_dump_size = 0;

			क्रम (i = 0; i < num_section_params; i++) अणु
				dump_buf += qed_पढ़ो_param(dump_buf,
							   &param_name,
							   &param_str_val,
							   &param_num_val);
				अगर (!म_भेद(param_name, "storm"))
					storm_letter = param_str_val;
				अन्यथा अगर (!म_भेद(param_name, "size"))
					storm_dump_size = param_num_val;
				अन्यथा
					वापस
					    DBG_STATUS_FW_ASSERTS_PARSE_FAILED;
			पूर्ण

			अगर (!storm_letter || !storm_dump_size)
				वापस DBG_STATUS_FW_ASSERTS_PARSE_FAILED;

			/* Prपूर्णांक data */
			results_offset +=
			    प्र_लिखो(qed_get_buf_ptr(results_buf,
						    results_offset),
				    "\n%sSTORM_ASSERT: size=%d\n",
				    storm_letter, storm_dump_size);
			क्रम (i = 0; i < storm_dump_size; i++, dump_buf++)
				results_offset +=
				    प्र_लिखो(qed_get_buf_ptr(results_buf,
							    results_offset),
					    "%08x\n", *dump_buf);
		पूर्ण अन्यथा अगर (!म_भेद(section_name, "last")) अणु
			last_section_found = true;
		पूर्ण अन्यथा अणु
			वापस DBG_STATUS_FW_ASSERTS_PARSE_FAILED;
		पूर्ण
	पूर्ण

	/* Add 1 क्रम string शून्य termination */
	*parsed_results_bytes = results_offset + 1;

	वापस DBG_STATUS_OK;
पूर्ण

/***************************** Public Functions *******************************/

क्रमागत dbg_status qed_dbg_user_set_bin_ptr(काष्ठा qed_hwfn *p_hwfn,
					 स्थिर u8 * स्थिर bin_ptr)
अणु
	काष्ठा bin_buffer_hdr *buf_hdrs = (काष्ठा bin_buffer_hdr *)bin_ptr;
	u8 buf_id;

	/* Convert binary data to debug arrays */
	क्रम (buf_id = 0; buf_id < MAX_BIN_DBG_BUFFER_TYPE; buf_id++)
		qed_set_dbg_bin_buf(p_hwfn,
				    (क्रमागत bin_dbg_buffer_type)buf_id,
				    (u32 *)(bin_ptr + buf_hdrs[buf_id].offset),
				    buf_hdrs[buf_id].length);

	वापस DBG_STATUS_OK;
पूर्ण

क्रमागत dbg_status qed_dbg_alloc_user_data(काष्ठा qed_hwfn *p_hwfn,
					व्योम **user_data_ptr)
अणु
	*user_data_ptr = kzalloc(माप(काष्ठा dbg_tools_user_data),
				 GFP_KERNEL);
	अगर (!(*user_data_ptr))
		वापस DBG_STATUS_VIRT_MEM_ALLOC_FAILED;

	वापस DBG_STATUS_OK;
पूर्ण

स्थिर अक्षर *qed_dbg_get_status_str(क्रमागत dbg_status status)
अणु
	वापस (status <
		MAX_DBG_STATUS) ? s_status_str[status] : "Invalid debug status";
पूर्ण

क्रमागत dbg_status qed_get_idle_chk_results_buf_size(काष्ठा qed_hwfn *p_hwfn,
						  u32 *dump_buf,
						  u32 num_dumped_dwords,
						  u32 *results_buf_size)
अणु
	u32 num_errors, num_warnings;

	वापस qed_parse_idle_chk_dump(p_hwfn,
				       dump_buf,
				       num_dumped_dwords,
				       शून्य,
				       results_buf_size,
				       &num_errors, &num_warnings);
पूर्ण

क्रमागत dbg_status qed_prपूर्णांक_idle_chk_results(काष्ठा qed_hwfn *p_hwfn,
					   u32 *dump_buf,
					   u32 num_dumped_dwords,
					   अक्षर *results_buf,
					   u32 *num_errors,
					   u32 *num_warnings)
अणु
	u32 parsed_buf_size;

	वापस qed_parse_idle_chk_dump(p_hwfn,
				       dump_buf,
				       num_dumped_dwords,
				       results_buf,
				       &parsed_buf_size,
				       num_errors, num_warnings);
पूर्ण

व्योम qed_dbg_mcp_trace_set_meta_data(काष्ठा qed_hwfn *p_hwfn,
				     स्थिर u32 *meta_buf)
अणु
	काष्ठा dbg_tools_user_data *dev_user_data =
		qed_dbg_get_user_data(p_hwfn);

	dev_user_data->mcp_trace_user_meta_buf = meta_buf;
पूर्ण

क्रमागत dbg_status qed_get_mcp_trace_results_buf_size(काष्ठा qed_hwfn *p_hwfn,
						   u32 *dump_buf,
						   u32 num_dumped_dwords,
						   u32 *results_buf_size)
अणु
	वापस qed_parse_mcp_trace_dump(p_hwfn,
					dump_buf, शून्य, results_buf_size, true);
पूर्ण

क्रमागत dbg_status qed_prपूर्णांक_mcp_trace_results(काष्ठा qed_hwfn *p_hwfn,
					    u32 *dump_buf,
					    u32 num_dumped_dwords,
					    अक्षर *results_buf)
अणु
	u32 parsed_buf_size;

	वापस qed_parse_mcp_trace_dump(p_hwfn,
					dump_buf,
					results_buf, &parsed_buf_size, true);
पूर्ण

क्रमागत dbg_status qed_prपूर्णांक_mcp_trace_results_cont(काष्ठा qed_hwfn *p_hwfn,
						 u32 *dump_buf,
						 अक्षर *results_buf)
अणु
	u32 parsed_buf_size;

	वापस qed_parse_mcp_trace_dump(p_hwfn, dump_buf, results_buf,
					&parsed_buf_size, false);
पूर्ण

क्रमागत dbg_status qed_prपूर्णांक_mcp_trace_line(काष्ठा qed_hwfn *p_hwfn,
					 u8 *dump_buf,
					 u32 num_dumped_bytes,
					 अक्षर *results_buf)
अणु
	u32 parsed_results_bytes;

	वापस qed_parse_mcp_trace_buf(p_hwfn,
				       dump_buf,
				       num_dumped_bytes,
				       0,
				       num_dumped_bytes,
				       results_buf, &parsed_results_bytes);
पूर्ण

/* Frees the specअगरied MCP Trace meta data */
व्योम qed_mcp_trace_मुक्त_meta_data(काष्ठा qed_hwfn *p_hwfn)
अणु
	काष्ठा dbg_tools_user_data *dev_user_data;
	काष्ठा mcp_trace_meta *meta;
	u32 i;

	dev_user_data = qed_dbg_get_user_data(p_hwfn);
	meta = &dev_user_data->mcp_trace_meta;
	अगर (!meta->is_allocated)
		वापस;

	/* Release modules */
	अगर (meta->modules) अणु
		क्रम (i = 0; i < meta->modules_num; i++)
			kमुक्त(meta->modules[i]);
		kमुक्त(meta->modules);
	पूर्ण

	/* Release क्रमmats */
	अगर (meta->क्रमmats) अणु
		क्रम (i = 0; i < meta->क्रमmats_num; i++)
			kमुक्त(meta->क्रमmats[i].क्रमmat_str);
		kमुक्त(meta->क्रमmats);
	पूर्ण

	meta->is_allocated = false;
पूर्ण

क्रमागत dbg_status qed_get_reg_fअगरo_results_buf_size(काष्ठा qed_hwfn *p_hwfn,
						  u32 *dump_buf,
						  u32 num_dumped_dwords,
						  u32 *results_buf_size)
अणु
	वापस qed_parse_reg_fअगरo_dump(dump_buf, शून्य, results_buf_size);
पूर्ण

क्रमागत dbg_status qed_prपूर्णांक_reg_fअगरo_results(काष्ठा qed_hwfn *p_hwfn,
					   u32 *dump_buf,
					   u32 num_dumped_dwords,
					   अक्षर *results_buf)
अणु
	u32 parsed_buf_size;

	वापस qed_parse_reg_fअगरo_dump(dump_buf, results_buf, &parsed_buf_size);
पूर्ण

क्रमागत dbg_status qed_get_igu_fअगरo_results_buf_size(काष्ठा qed_hwfn *p_hwfn,
						  u32 *dump_buf,
						  u32 num_dumped_dwords,
						  u32 *results_buf_size)
अणु
	वापस qed_parse_igu_fअगरo_dump(dump_buf, शून्य, results_buf_size);
पूर्ण

क्रमागत dbg_status qed_prपूर्णांक_igu_fअगरo_results(काष्ठा qed_hwfn *p_hwfn,
					   u32 *dump_buf,
					   u32 num_dumped_dwords,
					   अक्षर *results_buf)
अणु
	u32 parsed_buf_size;

	वापस qed_parse_igu_fअगरo_dump(dump_buf, results_buf, &parsed_buf_size);
पूर्ण

क्रमागत dbg_status
qed_get_protection_override_results_buf_size(काष्ठा qed_hwfn *p_hwfn,
					     u32 *dump_buf,
					     u32 num_dumped_dwords,
					     u32 *results_buf_size)
अणु
	वापस qed_parse_protection_override_dump(dump_buf,
						  शून्य, results_buf_size);
पूर्ण

क्रमागत dbg_status qed_prपूर्णांक_protection_override_results(काष्ठा qed_hwfn *p_hwfn,
						      u32 *dump_buf,
						      u32 num_dumped_dwords,
						      अक्षर *results_buf)
अणु
	u32 parsed_buf_size;

	वापस qed_parse_protection_override_dump(dump_buf,
						  results_buf,
						  &parsed_buf_size);
पूर्ण

क्रमागत dbg_status qed_get_fw_निश्चितs_results_buf_size(काष्ठा qed_hwfn *p_hwfn,
						    u32 *dump_buf,
						    u32 num_dumped_dwords,
						    u32 *results_buf_size)
अणु
	वापस qed_parse_fw_निश्चितs_dump(dump_buf, शून्य, results_buf_size);
पूर्ण

क्रमागत dbg_status qed_prपूर्णांक_fw_निश्चितs_results(काष्ठा qed_hwfn *p_hwfn,
					     u32 *dump_buf,
					     u32 num_dumped_dwords,
					     अक्षर *results_buf)
अणु
	u32 parsed_buf_size;

	वापस qed_parse_fw_निश्चितs_dump(dump_buf,
					 results_buf, &parsed_buf_size);
पूर्ण

क्रमागत dbg_status qed_dbg_parse_attn(काष्ठा qed_hwfn *p_hwfn,
				   काष्ठा dbg_attn_block_result *results)
अणु
	स्थिर u32 *block_attn_name_offsets;
	स्थिर अक्षर *attn_name_base;
	स्थिर अक्षर *block_name;
	क्रमागत dbg_attn_type attn_type;
	u8 num_regs, i, j;

	num_regs = GET_FIELD(results->data, DBG_ATTN_BLOCK_RESULT_NUM_REGS);
	attn_type = GET_FIELD(results->data, DBG_ATTN_BLOCK_RESULT_ATTN_TYPE);
	block_name = qed_dbg_get_block_name(p_hwfn, results->block_id);
	अगर (!block_name)
		वापस DBG_STATUS_INVALID_ARGS;

	अगर (!p_hwfn->dbg_arrays[BIN_BUF_DBG_ATTN_INDEXES].ptr ||
	    !p_hwfn->dbg_arrays[BIN_BUF_DBG_ATTN_NAME_OFFSETS].ptr ||
	    !p_hwfn->dbg_arrays[BIN_BUF_DBG_PARSING_STRINGS].ptr)
		वापस DBG_STATUS_DBG_ARRAY_NOT_SET;

	block_attn_name_offsets =
	    (u32 *)p_hwfn->dbg_arrays[BIN_BUF_DBG_ATTN_NAME_OFFSETS].ptr +
	    results->names_offset;

	attn_name_base = p_hwfn->dbg_arrays[BIN_BUF_DBG_PARSING_STRINGS].ptr;

	/* Go over रेजिस्टरs with a non-zero attention status */
	क्रम (i = 0; i < num_regs; i++) अणु
		काष्ठा dbg_attn_bit_mapping *bit_mapping;
		काष्ठा dbg_attn_reg_result *reg_result;
		u8 num_reg_attn, bit_idx = 0;

		reg_result = &results->reg_results[i];
		num_reg_attn = GET_FIELD(reg_result->data,
					 DBG_ATTN_REG_RESULT_NUM_REG_ATTN);
		bit_mapping = (काष्ठा dbg_attn_bit_mapping *)
		    p_hwfn->dbg_arrays[BIN_BUF_DBG_ATTN_INDEXES].ptr +
		    reg_result->block_attn_offset;

		/* Go over attention status bits */
		क्रम (j = 0; j < num_reg_attn; j++, bit_idx++) अणु
			u16 attn_idx_val = GET_FIELD(bit_mapping[j].data,
						     DBG_ATTN_BIT_MAPPING_VAL);
			स्थिर अक्षर *attn_name, *attn_type_str, *masked_str;
			u32 attn_name_offset;
			u32 sts_addr;

			/* Check अगर bit mask should be advanced (due to unused
			 * bits).
			 */
			अगर (GET_FIELD(bit_mapping[j].data,
				      DBG_ATTN_BIT_MAPPING_IS_UNUSED_BIT_CNT)) अणु
				bit_idx += (u8)attn_idx_val;
				जारी;
			पूर्ण

			/* Check current bit index */
			अगर (!(reg_result->sts_val & BIT(bit_idx)))
				जारी;

			/* An attention bit with value=1 was found
			 * Find attention name
			 */
			attn_name_offset =
				block_attn_name_offsets[attn_idx_val];
			attn_name = attn_name_base + attn_name_offset;
			attn_type_str =
				(attn_type ==
				 ATTN_TYPE_INTERRUPT ? "Interrupt" :
				 "Parity");
			masked_str = reg_result->mask_val & BIT(bit_idx) ?
				     " [masked]" : "";
			sts_addr = GET_FIELD(reg_result->data,
					     DBG_ATTN_REG_RESULT_STS_ADDRESS);
			DP_NOTICE(p_hwfn,
				  "%s (%s) : %s [address 0x%08x, bit %d]%s\n",
				  block_name, attn_type_str, attn_name,
				  sts_addr * 4, bit_idx, masked_str);
		पूर्ण
	पूर्ण

	वापस DBG_STATUS_OK;
पूर्ण

अटल DEFINE_MUTEX(qed_dbg_lock);

/* Wrapper क्रम unअगरying the idle_chk and mcp_trace api */
अटल क्रमागत dbg_status
qed_prपूर्णांक_idle_chk_results_wrapper(काष्ठा qed_hwfn *p_hwfn,
				   u32 *dump_buf,
				   u32 num_dumped_dwords,
				   अक्षर *results_buf)
अणु
	u32 num_errors, num_warnnings;

	वापस qed_prपूर्णांक_idle_chk_results(p_hwfn, dump_buf, num_dumped_dwords,
					  results_buf, &num_errors,
					  &num_warnnings);
पूर्ण

/* Feature meta data lookup table */
अटल काष्ठा अणु
	अक्षर *name;
	क्रमागत dbg_status (*get_size)(काष्ठा qed_hwfn *p_hwfn,
				    काष्ठा qed_ptt *p_ptt, u32 *size);
	क्रमागत dbg_status (*perक्रमm_dump)(काष्ठा qed_hwfn *p_hwfn,
					काष्ठा qed_ptt *p_ptt, u32 *dump_buf,
					u32 buf_size, u32 *dumped_dwords);
	क्रमागत dbg_status (*prपूर्णांक_results)(काष्ठा qed_hwfn *p_hwfn,
					 u32 *dump_buf, u32 num_dumped_dwords,
					 अक्षर *results_buf);
	क्रमागत dbg_status (*results_buf_size)(काष्ठा qed_hwfn *p_hwfn,
					    u32 *dump_buf,
					    u32 num_dumped_dwords,
					    u32 *results_buf_size);
पूर्ण qed_features_lookup[] = अणु
	अणु
	"grc", qed_dbg_grc_get_dump_buf_size,
		    qed_dbg_grc_dump, शून्य, शून्यपूर्ण, अणु
	"idle_chk",
		    qed_dbg_idle_chk_get_dump_buf_size,
		    qed_dbg_idle_chk_dump,
		    qed_prपूर्णांक_idle_chk_results_wrapper,
		    qed_get_idle_chk_results_buf_sizeपूर्ण, अणु
	"mcp_trace",
		    qed_dbg_mcp_trace_get_dump_buf_size,
		    qed_dbg_mcp_trace_dump, qed_prपूर्णांक_mcp_trace_results,
		    qed_get_mcp_trace_results_buf_sizeपूर्ण, अणु
	"reg_fifo",
		    qed_dbg_reg_fअगरo_get_dump_buf_size,
		    qed_dbg_reg_fअगरo_dump, qed_prपूर्णांक_reg_fअगरo_results,
		    qed_get_reg_fअगरo_results_buf_sizeपूर्ण, अणु
	"igu_fifo",
		    qed_dbg_igu_fअगरo_get_dump_buf_size,
		    qed_dbg_igu_fअगरo_dump, qed_prपूर्णांक_igu_fअगरo_results,
		    qed_get_igu_fअगरo_results_buf_sizeपूर्ण, अणु
	"protection_override",
		    qed_dbg_protection_override_get_dump_buf_size,
		    qed_dbg_protection_override_dump,
		    qed_prपूर्णांक_protection_override_results,
		    qed_get_protection_override_results_buf_sizeपूर्ण, अणु
	"fw_asserts",
		    qed_dbg_fw_निश्चितs_get_dump_buf_size,
		    qed_dbg_fw_निश्चितs_dump,
		    qed_prपूर्णांक_fw_निश्चितs_results,
		    qed_get_fw_निश्चितs_results_buf_sizeपूर्ण, अणु
	"ilt",
		    qed_dbg_ilt_get_dump_buf_size,
		    qed_dbg_ilt_dump, शून्य, शून्यपूर्ण,पूर्ण;

अटल व्योम qed_dbg_prपूर्णांक_feature(u8 *p_text_buf, u32 text_size)
अणु
	u32 i, precision = 80;

	अगर (!p_text_buf)
		वापस;

	pr_notice("\n%.*s", precision, p_text_buf);
	क्रम (i = precision; i < text_size; i += precision)
		pr_cont("%.*s", precision, p_text_buf + i);
	pr_cont("\n");
पूर्ण

#घोषणा QED_RESULTS_BUF_MIN_SIZE 16
/* Generic function क्रम decoding debug feature info */
अटल क्रमागत dbg_status क्रमmat_feature(काष्ठा qed_hwfn *p_hwfn,
				      क्रमागत qed_dbg_features feature_idx)
अणु
	काष्ठा qed_dbg_feature *feature =
	    &p_hwfn->cdev->dbg_features[feature_idx];
	u32 text_size_bytes, null_अक्षर_pos, i;
	क्रमागत dbg_status rc;
	अक्षर *text_buf;

	/* Check अगर feature supports क्रमmatting capability */
	अगर (!qed_features_lookup[feature_idx].results_buf_size)
		वापस DBG_STATUS_OK;

	/* Obtain size of क्रमmatted output */
	rc = qed_features_lookup[feature_idx].
		results_buf_size(p_hwfn, (u32 *)feature->dump_buf,
				 feature->dumped_dwords, &text_size_bytes);
	अगर (rc != DBG_STATUS_OK)
		वापस rc;

	/* Make sure that the allocated size is a multiple of dword (4 bytes) */
	null_अक्षर_pos = text_size_bytes - 1;
	text_size_bytes = (text_size_bytes + 3) & ~0x3;

	अगर (text_size_bytes < QED_RESULTS_BUF_MIN_SIZE) अणु
		DP_NOTICE(p_hwfn->cdev,
			  "formatted size of feature was too small %d. Aborting\n",
			  text_size_bytes);
		वापस DBG_STATUS_INVALID_ARGS;
	पूर्ण

	/* Allocate temp text buf */
	text_buf = vzalloc(text_size_bytes);
	अगर (!text_buf)
		वापस DBG_STATUS_VIRT_MEM_ALLOC_FAILED;

	/* Decode feature opcodes to string on temp buf */
	rc = qed_features_lookup[feature_idx].
		prपूर्णांक_results(p_hwfn, (u32 *)feature->dump_buf,
			      feature->dumped_dwords, text_buf);
	अगर (rc != DBG_STATUS_OK) अणु
		vमुक्त(text_buf);
		वापस rc;
	पूर्ण

	/* Replace the original null अक्षरacter with a '\n' अक्षरacter.
	 * The bytes that were added as a result of the dword alignment are also
	 * padded with '\n' अक्षरacters.
	 */
	क्रम (i = null_अक्षर_pos; i < text_size_bytes; i++)
		text_buf[i] = '\n';

	/* Dump prपूर्णांकable feature to log */
	अगर (p_hwfn->cdev->prपूर्णांक_dbg_data)
		qed_dbg_prपूर्णांक_feature(text_buf, text_size_bytes);

	/* Just वापस the original binary buffer अगर requested */
	अगर (p_hwfn->cdev->dbg_bin_dump) अणु
		vमुक्त(text_buf);
		वापस DBG_STATUS_OK;
	पूर्ण

	/* Free the old dump_buf and poपूर्णांक the dump_buf to the newly allocagted
	 * and क्रमmatted text buffer.
	 */
	vमुक्त(feature->dump_buf);
	feature->dump_buf = text_buf;
	feature->buf_size = text_size_bytes;
	feature->dumped_dwords = text_size_bytes / 4;
	वापस rc;
पूर्ण

#घोषणा MAX_DBG_FEATURE_SIZE_DWORDS	0x3FFFFFFF

/* Generic function क्रम perक्रमming the dump of a debug feature. */
अटल क्रमागत dbg_status qed_dbg_dump(काष्ठा qed_hwfn *p_hwfn,
				    काष्ठा qed_ptt *p_ptt,
				    क्रमागत qed_dbg_features feature_idx)
अणु
	काष्ठा qed_dbg_feature *feature =
	    &p_hwfn->cdev->dbg_features[feature_idx];
	u32 buf_size_dwords;
	क्रमागत dbg_status rc;

	DP_NOTICE(p_hwfn->cdev, "Collecting a debug feature [\"%s\"]\n",
		  qed_features_lookup[feature_idx].name);

	/* Dump_buf was alपढ़ोy allocated need to मुक्त (this can happen अगर dump
	 * was called but file was never पढ़ो).
	 * We can't use the buffer as is since size may have changed.
	 */
	अगर (feature->dump_buf) अणु
		vमुक्त(feature->dump_buf);
		feature->dump_buf = शून्य;
	पूर्ण

	/* Get buffer size from hsi, allocate accordingly, and perक्रमm the
	 * dump.
	 */
	rc = qed_features_lookup[feature_idx].get_size(p_hwfn, p_ptt,
						       &buf_size_dwords);
	अगर (rc != DBG_STATUS_OK && rc != DBG_STATUS_NVRAM_GET_IMAGE_FAILED)
		वापस rc;

	अगर (buf_size_dwords > MAX_DBG_FEATURE_SIZE_DWORDS) अणु
		feature->buf_size = 0;
		DP_NOTICE(p_hwfn->cdev,
			  "Debug feature [\"%s\"] size (0x%x dwords) exceeds maximum size (0x%x dwords)\n",
			  qed_features_lookup[feature_idx].name,
			  buf_size_dwords, MAX_DBG_FEATURE_SIZE_DWORDS);

		वापस DBG_STATUS_OK;
	पूर्ण

	feature->buf_size = buf_size_dwords * माप(u32);
	feature->dump_buf = vदो_स्मृति(feature->buf_size);
	अगर (!feature->dump_buf)
		वापस DBG_STATUS_VIRT_MEM_ALLOC_FAILED;

	rc = qed_features_lookup[feature_idx].
		perक्रमm_dump(p_hwfn, p_ptt, (u32 *)feature->dump_buf,
			     feature->buf_size / माप(u32),
			     &feature->dumped_dwords);

	/* If mcp is stuck we get DBG_STATUS_NVRAM_GET_IMAGE_FAILED error.
	 * In this हाल the buffer holds valid binary data, but we wont able
	 * to parse it (since parsing relies on data in NVRAM which is only
	 * accessible when MFW is responsive). skip the क्रमmatting but वापस
	 * success so that binary data is provided.
	 */
	अगर (rc == DBG_STATUS_NVRAM_GET_IMAGE_FAILED)
		वापस DBG_STATUS_OK;

	अगर (rc != DBG_STATUS_OK)
		वापस rc;

	/* Format output */
	rc = क्रमmat_feature(p_hwfn, feature_idx);
	वापस rc;
पूर्ण

पूर्णांक qed_dbg_grc(काष्ठा qed_dev *cdev, व्योम *buffer, u32 *num_dumped_bytes)
अणु
	वापस qed_dbg_feature(cdev, buffer, DBG_FEATURE_GRC, num_dumped_bytes);
पूर्ण

पूर्णांक qed_dbg_grc_size(काष्ठा qed_dev *cdev)
अणु
	वापस qed_dbg_feature_size(cdev, DBG_FEATURE_GRC);
पूर्ण

पूर्णांक qed_dbg_idle_chk(काष्ठा qed_dev *cdev, व्योम *buffer, u32 *num_dumped_bytes)
अणु
	वापस qed_dbg_feature(cdev, buffer, DBG_FEATURE_IDLE_CHK,
			       num_dumped_bytes);
पूर्ण

पूर्णांक qed_dbg_idle_chk_size(काष्ठा qed_dev *cdev)
अणु
	वापस qed_dbg_feature_size(cdev, DBG_FEATURE_IDLE_CHK);
पूर्ण

पूर्णांक qed_dbg_reg_fअगरo(काष्ठा qed_dev *cdev, व्योम *buffer, u32 *num_dumped_bytes)
अणु
	वापस qed_dbg_feature(cdev, buffer, DBG_FEATURE_REG_FIFO,
			       num_dumped_bytes);
पूर्ण

पूर्णांक qed_dbg_reg_fअगरo_size(काष्ठा qed_dev *cdev)
अणु
	वापस qed_dbg_feature_size(cdev, DBG_FEATURE_REG_FIFO);
पूर्ण

पूर्णांक qed_dbg_igu_fअगरo(काष्ठा qed_dev *cdev, व्योम *buffer, u32 *num_dumped_bytes)
अणु
	वापस qed_dbg_feature(cdev, buffer, DBG_FEATURE_IGU_FIFO,
			       num_dumped_bytes);
पूर्ण

पूर्णांक qed_dbg_igu_fअगरo_size(काष्ठा qed_dev *cdev)
अणु
	वापस qed_dbg_feature_size(cdev, DBG_FEATURE_IGU_FIFO);
पूर्ण

अटल पूर्णांक qed_dbg_nvm_image_length(काष्ठा qed_hwfn *p_hwfn,
				    क्रमागत qed_nvm_images image_id, u32 *length)
अणु
	काष्ठा qed_nvm_image_att image_att;
	पूर्णांक rc;

	*length = 0;
	rc = qed_mcp_get_nvm_image_att(p_hwfn, image_id, &image_att);
	अगर (rc)
		वापस rc;

	*length = image_att.length;

	वापस rc;
पूर्ण

अटल पूर्णांक qed_dbg_nvm_image(काष्ठा qed_dev *cdev, व्योम *buffer,
			     u32 *num_dumped_bytes,
			     क्रमागत qed_nvm_images image_id)
अणु
	काष्ठा qed_hwfn *p_hwfn =
		&cdev->hwfns[cdev->engine_क्रम_debug];
	u32 len_rounded;
	पूर्णांक rc;

	*num_dumped_bytes = 0;
	rc = qed_dbg_nvm_image_length(p_hwfn, image_id, &len_rounded);
	अगर (rc)
		वापस rc;

	DP_NOTICE(p_hwfn->cdev,
		  "Collecting a debug feature [\"nvram image %d\"]\n",
		  image_id);

	len_rounded = roundup(len_rounded, माप(u32));
	rc = qed_mcp_get_nvm_image(p_hwfn, image_id, buffer, len_rounded);
	अगर (rc)
		वापस rc;

	/* QED_NVM_IMAGE_NVM_META image is not swapped like other images */
	अगर (image_id != QED_NVM_IMAGE_NVM_META)
		cpu_to_be32_array((__क्रमce __be32 *)buffer,
				  (स्थिर u32 *)buffer,
				  len_rounded / माप(u32));

	*num_dumped_bytes = len_rounded;

	वापस rc;
पूर्ण

पूर्णांक qed_dbg_protection_override(काष्ठा qed_dev *cdev, व्योम *buffer,
				u32 *num_dumped_bytes)
अणु
	वापस qed_dbg_feature(cdev, buffer, DBG_FEATURE_PROTECTION_OVERRIDE,
			       num_dumped_bytes);
पूर्ण

पूर्णांक qed_dbg_protection_override_size(काष्ठा qed_dev *cdev)
अणु
	वापस qed_dbg_feature_size(cdev, DBG_FEATURE_PROTECTION_OVERRIDE);
पूर्ण

पूर्णांक qed_dbg_fw_निश्चितs(काष्ठा qed_dev *cdev, व्योम *buffer,
		       u32 *num_dumped_bytes)
अणु
	वापस qed_dbg_feature(cdev, buffer, DBG_FEATURE_FW_ASSERTS,
			       num_dumped_bytes);
पूर्ण

पूर्णांक qed_dbg_fw_निश्चितs_size(काष्ठा qed_dev *cdev)
अणु
	वापस qed_dbg_feature_size(cdev, DBG_FEATURE_FW_ASSERTS);
पूर्ण

पूर्णांक qed_dbg_ilt(काष्ठा qed_dev *cdev, व्योम *buffer, u32 *num_dumped_bytes)
अणु
	वापस qed_dbg_feature(cdev, buffer, DBG_FEATURE_ILT, num_dumped_bytes);
पूर्ण

पूर्णांक qed_dbg_ilt_size(काष्ठा qed_dev *cdev)
अणु
	वापस qed_dbg_feature_size(cdev, DBG_FEATURE_ILT);
पूर्ण

पूर्णांक qed_dbg_mcp_trace(काष्ठा qed_dev *cdev, व्योम *buffer,
		      u32 *num_dumped_bytes)
अणु
	वापस qed_dbg_feature(cdev, buffer, DBG_FEATURE_MCP_TRACE,
			       num_dumped_bytes);
पूर्ण

पूर्णांक qed_dbg_mcp_trace_size(काष्ठा qed_dev *cdev)
अणु
	वापस qed_dbg_feature_size(cdev, DBG_FEATURE_MCP_TRACE);
पूर्ण

/* Defines the amount of bytes allocated क्रम recording the length of debugfs
 * feature buffer.
 */
#घोषणा REGDUMP_HEADER_SIZE			माप(u32)
#घोषणा REGDUMP_HEADER_SIZE_SHIFT		0
#घोषणा REGDUMP_HEADER_SIZE_MASK		0xffffff
#घोषणा REGDUMP_HEADER_FEATURE_SHIFT		24
#घोषणा REGDUMP_HEADER_FEATURE_MASK		0x1f
#घोषणा REGDUMP_HEADER_BIN_DUMP_SHIFT		29
#घोषणा REGDUMP_HEADER_BIN_DUMP_MASK		0x1
#घोषणा REGDUMP_HEADER_OMIT_ENGINE_SHIFT	30
#घोषणा REGDUMP_HEADER_OMIT_ENGINE_MASK		0x1
#घोषणा REGDUMP_HEADER_ENGINE_SHIFT		31
#घोषणा REGDUMP_HEADER_ENGINE_MASK		0x1
#घोषणा REGDUMP_MAX_SIZE			0x1000000
#घोषणा ILT_DUMP_MAX_SIZE			(1024 * 1024 * 15)

क्रमागत debug_prपूर्णांक_features अणु
	OLD_MODE = 0,
	IDLE_CHK = 1,
	GRC_DUMP = 2,
	MCP_TRACE = 3,
	REG_FIFO = 4,
	PROTECTION_OVERRIDE = 5,
	IGU_FIFO = 6,
	PHY = 7,
	FW_ASSERTS = 8,
	NVM_CFG1 = 9,
	DEFAULT_CFG = 10,
	NVM_META = 11,
	MDUMP = 12,
	ILT_DUMP = 13,
पूर्ण;

अटल u32 qed_calc_regdump_header(काष्ठा qed_dev *cdev,
				   क्रमागत debug_prपूर्णांक_features feature,
				   पूर्णांक engine, u32 feature_size, u8 omit_engine)
अणु
	u32 res = 0;

	SET_FIELD(res, REGDUMP_HEADER_SIZE, feature_size);
	अगर (res != feature_size)
		DP_NOTICE(cdev,
			  "Feature %d is too large (size 0x%x) and will corrupt the dump\n",
			  feature, feature_size);

	SET_FIELD(res, REGDUMP_HEADER_FEATURE, feature);
	SET_FIELD(res, REGDUMP_HEADER_BIN_DUMP, 1);
	SET_FIELD(res, REGDUMP_HEADER_OMIT_ENGINE, omit_engine);
	SET_FIELD(res, REGDUMP_HEADER_ENGINE, engine);

	वापस res;
पूर्ण

पूर्णांक qed_dbg_all_data(काष्ठा qed_dev *cdev, व्योम *buffer)
अणु
	u8 cur_engine, omit_engine = 0, org_engine;
	काष्ठा qed_hwfn *p_hwfn =
		&cdev->hwfns[cdev->engine_क्रम_debug];
	काष्ठा dbg_tools_data *dev_data = &p_hwfn->dbg_info;
	पूर्णांक grc_params[MAX_DBG_GRC_PARAMS], i;
	u32 offset = 0, feature_size;
	पूर्णांक rc;

	क्रम (i = 0; i < MAX_DBG_GRC_PARAMS; i++)
		grc_params[i] = dev_data->grc.param_val[i];

	अगर (!QED_IS_CMT(cdev))
		omit_engine = 1;

	mutex_lock(&qed_dbg_lock);
	cdev->dbg_bin_dump = true;

	org_engine = qed_get_debug_engine(cdev);
	क्रम (cur_engine = 0; cur_engine < cdev->num_hwfns; cur_engine++) अणु
		/* Collect idle_chks and grcDump क्रम each hw function */
		DP_VERBOSE(cdev, QED_MSG_DEBUG,
			   "obtaining idle_chk and grcdump for current engine\n");
		qed_set_debug_engine(cdev, cur_engine);

		/* First idle_chk */
		rc = qed_dbg_idle_chk(cdev, (u8 *)buffer + offset +
				      REGDUMP_HEADER_SIZE, &feature_size);
		अगर (!rc) अणु
			*(u32 *)((u8 *)buffer + offset) =
			    qed_calc_regdump_header(cdev, IDLE_CHK, cur_engine,
						    feature_size, omit_engine);
			offset += (feature_size + REGDUMP_HEADER_SIZE);
		पूर्ण अन्यथा अणु
			DP_ERR(cdev, "qed_dbg_idle_chk failed. rc = %d\n", rc);
		पूर्ण

		/* Second idle_chk */
		rc = qed_dbg_idle_chk(cdev, (u8 *)buffer + offset +
				      REGDUMP_HEADER_SIZE, &feature_size);
		अगर (!rc) अणु
			*(u32 *)((u8 *)buffer + offset) =
			    qed_calc_regdump_header(cdev, IDLE_CHK, cur_engine,
						    feature_size, omit_engine);
			offset += (feature_size + REGDUMP_HEADER_SIZE);
		पूर्ण अन्यथा अणु
			DP_ERR(cdev, "qed_dbg_idle_chk failed. rc = %d\n", rc);
		पूर्ण

		/* reg_fअगरo dump */
		rc = qed_dbg_reg_fअगरo(cdev, (u8 *)buffer + offset +
				      REGDUMP_HEADER_SIZE, &feature_size);
		अगर (!rc) अणु
			*(u32 *)((u8 *)buffer + offset) =
			    qed_calc_regdump_header(cdev, REG_FIFO, cur_engine,
						    feature_size, omit_engine);
			offset += (feature_size + REGDUMP_HEADER_SIZE);
		पूर्ण अन्यथा अणु
			DP_ERR(cdev, "qed_dbg_reg_fifo failed. rc = %d\n", rc);
		पूर्ण

		/* igu_fअगरo dump */
		rc = qed_dbg_igu_fअगरo(cdev, (u8 *)buffer + offset +
				      REGDUMP_HEADER_SIZE, &feature_size);
		अगर (!rc) अणु
			*(u32 *)((u8 *)buffer + offset) =
			    qed_calc_regdump_header(cdev, IGU_FIFO, cur_engine,
						    feature_size, omit_engine);
			offset += (feature_size + REGDUMP_HEADER_SIZE);
		पूर्ण अन्यथा अणु
			DP_ERR(cdev, "qed_dbg_igu_fifo failed. rc = %d", rc);
		पूर्ण

		/* protection_override dump */
		rc = qed_dbg_protection_override(cdev, (u8 *)buffer + offset +
						 REGDUMP_HEADER_SIZE,
						 &feature_size);
		अगर (!rc) अणु
			*(u32 *)((u8 *)buffer + offset) =
			    qed_calc_regdump_header(cdev, PROTECTION_OVERRIDE,
						    cur_engine,
						    feature_size, omit_engine);
			offset += (feature_size + REGDUMP_HEADER_SIZE);
		पूर्ण अन्यथा अणु
			DP_ERR(cdev,
			       "qed_dbg_protection_override failed. rc = %d\n",
			       rc);
		पूर्ण

		/* fw_निश्चितs dump */
		rc = qed_dbg_fw_निश्चितs(cdev, (u8 *)buffer + offset +
					REGDUMP_HEADER_SIZE, &feature_size);
		अगर (!rc) अणु
			*(u32 *)((u8 *)buffer + offset) =
			    qed_calc_regdump_header(cdev, FW_ASSERTS,
						    cur_engine, feature_size,
						    omit_engine);
			offset += (feature_size + REGDUMP_HEADER_SIZE);
		पूर्ण अन्यथा अणु
			DP_ERR(cdev, "qed_dbg_fw_asserts failed. rc = %d\n",
			       rc);
		पूर्ण

		feature_size = qed_dbg_ilt_size(cdev);
		अगर (!cdev->disable_ilt_dump &&
		    feature_size < ILT_DUMP_MAX_SIZE) अणु
			rc = qed_dbg_ilt(cdev, (u8 *)buffer + offset +
					 REGDUMP_HEADER_SIZE, &feature_size);
			अगर (!rc) अणु
				*(u32 *)((u8 *)buffer + offset) =
				    qed_calc_regdump_header(cdev, ILT_DUMP,
							    cur_engine,
							    feature_size,
							    omit_engine);
				offset += feature_size + REGDUMP_HEADER_SIZE;
			पूर्ण अन्यथा अणु
				DP_ERR(cdev, "qed_dbg_ilt failed. rc = %d\n",
				       rc);
			पूर्ण
		पूर्ण

		/* GRC dump - must be last because when mcp stuck it will
		 * clutter idle_chk, reg_fअगरo, ...
		 */
		क्रम (i = 0; i < MAX_DBG_GRC_PARAMS; i++)
			dev_data->grc.param_val[i] = grc_params[i];

		rc = qed_dbg_grc(cdev, (u8 *)buffer + offset +
				 REGDUMP_HEADER_SIZE, &feature_size);
		अगर (!rc) अणु
			*(u32 *)((u8 *)buffer + offset) =
			    qed_calc_regdump_header(cdev, GRC_DUMP,
						    cur_engine,
						    feature_size, omit_engine);
			offset += (feature_size + REGDUMP_HEADER_SIZE);
		पूर्ण अन्यथा अणु
			DP_ERR(cdev, "qed_dbg_grc failed. rc = %d", rc);
		पूर्ण
	पूर्ण

	qed_set_debug_engine(cdev, org_engine);

	/* mcp_trace */
	rc = qed_dbg_mcp_trace(cdev, (u8 *)buffer + offset +
			       REGDUMP_HEADER_SIZE, &feature_size);
	अगर (!rc) अणु
		*(u32 *)((u8 *)buffer + offset) =
		    qed_calc_regdump_header(cdev, MCP_TRACE, cur_engine,
					    feature_size, omit_engine);
		offset += (feature_size + REGDUMP_HEADER_SIZE);
	पूर्ण अन्यथा अणु
		DP_ERR(cdev, "qed_dbg_mcp_trace failed. rc = %d\n", rc);
	पूर्ण

	/* Re-populate nvm attribute info */
	qed_mcp_nvm_info_मुक्त(p_hwfn);
	qed_mcp_nvm_info_populate(p_hwfn);

	/* nvm cfg1 */
	rc = qed_dbg_nvm_image(cdev,
			       (u8 *)buffer + offset +
			       REGDUMP_HEADER_SIZE, &feature_size,
			       QED_NVM_IMAGE_NVM_CFG1);
	अगर (!rc) अणु
		*(u32 *)((u8 *)buffer + offset) =
		    qed_calc_regdump_header(cdev, NVM_CFG1, cur_engine,
					    feature_size, omit_engine);
		offset += (feature_size + REGDUMP_HEADER_SIZE);
	पूर्ण अन्यथा अगर (rc != -ENOENT) अणु
		DP_ERR(cdev,
		       "qed_dbg_nvm_image failed for image  %d (%s), rc = %d\n",
		       QED_NVM_IMAGE_NVM_CFG1, "QED_NVM_IMAGE_NVM_CFG1", rc);
	पूर्ण

	/* nvm शेष */
	rc = qed_dbg_nvm_image(cdev,
			       (u8 *)buffer + offset + REGDUMP_HEADER_SIZE,
			       &feature_size, QED_NVM_IMAGE_DEFAULT_CFG);
	अगर (!rc) अणु
		*(u32 *)((u8 *)buffer + offset) =
		    qed_calc_regdump_header(cdev, DEFAULT_CFG, cur_engine,
					    feature_size, omit_engine);
		offset += (feature_size + REGDUMP_HEADER_SIZE);
	पूर्ण अन्यथा अगर (rc != -ENOENT) अणु
		DP_ERR(cdev,
		       "qed_dbg_nvm_image failed for image %d (%s), rc = %d\n",
		       QED_NVM_IMAGE_DEFAULT_CFG, "QED_NVM_IMAGE_DEFAULT_CFG",
		       rc);
	पूर्ण

	/* nvm meta */
	rc = qed_dbg_nvm_image(cdev,
			       (u8 *)buffer + offset + REGDUMP_HEADER_SIZE,
			       &feature_size, QED_NVM_IMAGE_NVM_META);
	अगर (!rc) अणु
		*(u32 *)((u8 *)buffer + offset) =
			qed_calc_regdump_header(cdev, NVM_META, cur_engine,
						feature_size, omit_engine);
		offset += (feature_size + REGDUMP_HEADER_SIZE);
	पूर्ण अन्यथा अगर (rc != -ENOENT) अणु
		DP_ERR(cdev,
		       "qed_dbg_nvm_image failed for image %d (%s), rc = %d\n",
		       QED_NVM_IMAGE_NVM_META, "QED_NVM_IMAGE_NVM_META", rc);
	पूर्ण

	/* nvm mdump */
	rc = qed_dbg_nvm_image(cdev, (u8 *)buffer + offset +
			       REGDUMP_HEADER_SIZE, &feature_size,
			       QED_NVM_IMAGE_MDUMP);
	अगर (!rc) अणु
		*(u32 *)((u8 *)buffer + offset) =
			qed_calc_regdump_header(cdev, MDUMP, cur_engine,
						feature_size, omit_engine);
		offset += (feature_size + REGDUMP_HEADER_SIZE);
	पूर्ण अन्यथा अगर (rc != -ENOENT) अणु
		DP_ERR(cdev,
		       "qed_dbg_nvm_image failed for image %d (%s), rc = %d\n",
		       QED_NVM_IMAGE_MDUMP, "QED_NVM_IMAGE_MDUMP", rc);
	पूर्ण

	cdev->dbg_bin_dump = false;
	mutex_unlock(&qed_dbg_lock);

	वापस 0;
पूर्ण

पूर्णांक qed_dbg_all_data_size(काष्ठा qed_dev *cdev)
अणु
	काष्ठा qed_hwfn *p_hwfn =
		&cdev->hwfns[cdev->engine_क्रम_debug];
	u32 regs_len = 0, image_len = 0, ilt_len = 0, total_ilt_len = 0;
	u8 cur_engine, org_engine;

	cdev->disable_ilt_dump = false;
	org_engine = qed_get_debug_engine(cdev);
	क्रम (cur_engine = 0; cur_engine < cdev->num_hwfns; cur_engine++) अणु
		/* Engine specअगरic */
		DP_VERBOSE(cdev, QED_MSG_DEBUG,
			   "calculating idle_chk and grcdump register length for current engine\n");
		qed_set_debug_engine(cdev, cur_engine);
		regs_len += REGDUMP_HEADER_SIZE + qed_dbg_idle_chk_size(cdev) +
			    REGDUMP_HEADER_SIZE + qed_dbg_idle_chk_size(cdev) +
			    REGDUMP_HEADER_SIZE + qed_dbg_grc_size(cdev) +
			    REGDUMP_HEADER_SIZE + qed_dbg_reg_fअगरo_size(cdev) +
			    REGDUMP_HEADER_SIZE + qed_dbg_igu_fअगरo_size(cdev) +
			    REGDUMP_HEADER_SIZE +
			    qed_dbg_protection_override_size(cdev) +
			    REGDUMP_HEADER_SIZE + qed_dbg_fw_निश्चितs_size(cdev);

		ilt_len = REGDUMP_HEADER_SIZE + qed_dbg_ilt_size(cdev);
		अगर (ilt_len < ILT_DUMP_MAX_SIZE) अणु
			total_ilt_len += ilt_len;
			regs_len += ilt_len;
		पूर्ण
	पूर्ण

	qed_set_debug_engine(cdev, org_engine);

	/* Engine common */
	regs_len += REGDUMP_HEADER_SIZE + qed_dbg_mcp_trace_size(cdev);
	qed_dbg_nvm_image_length(p_hwfn, QED_NVM_IMAGE_NVM_CFG1, &image_len);
	अगर (image_len)
		regs_len += REGDUMP_HEADER_SIZE + image_len;
	qed_dbg_nvm_image_length(p_hwfn, QED_NVM_IMAGE_DEFAULT_CFG, &image_len);
	अगर (image_len)
		regs_len += REGDUMP_HEADER_SIZE + image_len;
	qed_dbg_nvm_image_length(p_hwfn, QED_NVM_IMAGE_NVM_META, &image_len);
	अगर (image_len)
		regs_len += REGDUMP_HEADER_SIZE + image_len;
	qed_dbg_nvm_image_length(p_hwfn, QED_NVM_IMAGE_MDUMP, &image_len);
	अगर (image_len)
		regs_len += REGDUMP_HEADER_SIZE + image_len;

	अगर (regs_len > REGDUMP_MAX_SIZE) अणु
		DP_VERBOSE(cdev, QED_MSG_DEBUG,
			   "Dump exceeds max size 0x%x, disable ILT dump\n",
			   REGDUMP_MAX_SIZE);
		cdev->disable_ilt_dump = true;
		regs_len -= total_ilt_len;
	पूर्ण

	वापस regs_len;
पूर्ण

पूर्णांक qed_dbg_feature(काष्ठा qed_dev *cdev, व्योम *buffer,
		    क्रमागत qed_dbg_features feature, u32 *num_dumped_bytes)
अणु
	काष्ठा qed_hwfn *p_hwfn =
		&cdev->hwfns[cdev->engine_क्रम_debug];
	काष्ठा qed_dbg_feature *qed_feature =
		&cdev->dbg_features[feature];
	क्रमागत dbg_status dbg_rc;
	काष्ठा qed_ptt *p_ptt;
	पूर्णांक rc = 0;

	/* Acquire ptt */
	p_ptt = qed_ptt_acquire(p_hwfn);
	अगर (!p_ptt)
		वापस -EINVAL;

	/* Get dump */
	dbg_rc = qed_dbg_dump(p_hwfn, p_ptt, feature);
	अगर (dbg_rc != DBG_STATUS_OK) अणु
		DP_VERBOSE(cdev, QED_MSG_DEBUG, "%s\n",
			   qed_dbg_get_status_str(dbg_rc));
		*num_dumped_bytes = 0;
		rc = -EINVAL;
		जाओ out;
	पूर्ण

	DP_VERBOSE(cdev, QED_MSG_DEBUG,
		   "copying debugfs feature to external buffer\n");
	स_नकल(buffer, qed_feature->dump_buf, qed_feature->buf_size);
	*num_dumped_bytes = cdev->dbg_features[feature].dumped_dwords *
			    4;

out:
	qed_ptt_release(p_hwfn, p_ptt);
	वापस rc;
पूर्ण

पूर्णांक qed_dbg_feature_size(काष्ठा qed_dev *cdev, क्रमागत qed_dbg_features feature)
अणु
	काष्ठा qed_hwfn *p_hwfn =
		&cdev->hwfns[cdev->engine_क्रम_debug];
	काष्ठा qed_dbg_feature *qed_feature = &cdev->dbg_features[feature];
	काष्ठा qed_ptt *p_ptt = qed_ptt_acquire(p_hwfn);
	u32 buf_size_dwords;
	क्रमागत dbg_status rc;

	अगर (!p_ptt)
		वापस -EINVAL;

	rc = qed_features_lookup[feature].get_size(p_hwfn, p_ptt,
						   &buf_size_dwords);
	अगर (rc != DBG_STATUS_OK)
		buf_size_dwords = 0;

	/* Feature will not be dumped अगर it exceeds maximum size */
	अगर (buf_size_dwords > MAX_DBG_FEATURE_SIZE_DWORDS)
		buf_size_dwords = 0;

	qed_ptt_release(p_hwfn, p_ptt);
	qed_feature->buf_size = buf_size_dwords * माप(u32);
	वापस qed_feature->buf_size;
पूर्ण

u8 qed_get_debug_engine(काष्ठा qed_dev *cdev)
अणु
	वापस cdev->engine_क्रम_debug;
पूर्ण

व्योम qed_set_debug_engine(काष्ठा qed_dev *cdev, पूर्णांक engine_number)
अणु
	DP_VERBOSE(cdev, QED_MSG_DEBUG, "set debug engine to %d\n",
		   engine_number);
	cdev->engine_क्रम_debug = engine_number;
पूर्ण

व्योम qed_dbg_pf_init(काष्ठा qed_dev *cdev)
अणु
	स्थिर u8 *dbg_values = शून्य;
	पूर्णांक i;

	/* Debug values are after init values.
	 * The offset is the first dword of the file.
	 */
	dbg_values = cdev->firmware->data + *(u32 *)cdev->firmware->data;

	क्रम_each_hwfn(cdev, i) अणु
		qed_dbg_set_bin_ptr(&cdev->hwfns[i], dbg_values);
		qed_dbg_user_set_bin_ptr(&cdev->hwfns[i], dbg_values);
	पूर्ण

	/* Set the hwfn to be 0 as शेष */
	cdev->engine_क्रम_debug = 0;
पूर्ण

व्योम qed_dbg_pf_निकास(काष्ठा qed_dev *cdev)
अणु
	काष्ठा qed_dbg_feature *feature = शून्य;
	क्रमागत qed_dbg_features feature_idx;

	/* debug features' buffers may be allocated अगर debug feature was used
	 * but dump wasn't called
	 */
	क्रम (feature_idx = 0; feature_idx < DBG_FEATURE_NUM; feature_idx++) अणु
		feature = &cdev->dbg_features[feature_idx];
		अगर (feature->dump_buf) अणु
			vमुक्त(feature->dump_buf);
			feature->dump_buf = शून्य;
		पूर्ण
	पूर्ण
पूर्ण
