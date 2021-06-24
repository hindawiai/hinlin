<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause */
/*
 * Copyright (C) 2005-2014, 2018-2020 Intel Corporation
 * Copyright (C) 2013-2015 Intel Mobile Communications GmbH
 * Copyright (C) 2016-2017 Intel Deutschland GmbH
 */
#अगर_अघोषित __iwl_fw_api_debug_h__
#घोषणा __iwl_fw_api_debug_h__

/**
 * क्रमागत iwl_debug_cmds - debug commands
 */
क्रमागत iwl_debug_cmds अणु
	/**
	 * @LMAC_RD_WR:
	 * LMAC memory पढ़ो/ग_लिखो, using &काष्ठा iwl_dbg_mem_access_cmd and
	 * &काष्ठा iwl_dbg_mem_access_rsp
	 */
	LMAC_RD_WR = 0x0,
	/**
	 * @UMAC_RD_WR:
	 * UMAC memory पढ़ो/ग_लिखो, using &काष्ठा iwl_dbg_mem_access_cmd and
	 * &काष्ठा iwl_dbg_mem_access_rsp
	 */
	UMAC_RD_WR = 0x1,
	/**
	 * @HOST_EVENT_CFG:
	 * updates the enabled event severities
	 * &काष्ठा iwl_dbg_host_event_cfg_cmd
	 */
	HOST_EVENT_CFG = 0x3,
	/**
	 * @DBGC_SUSPEND_RESUME:
	 * DBGC suspend/resume commad. Uses a single dword as data:
	 * 0 - resume DBGC recording
	 * 1 - suspend DBGC recording
	 */
	DBGC_SUSPEND_RESUME = 0x7,
	/**
	 * @BUFFER_ALLOCATION:
	 * passes DRAM buffers to a DBGC
	 * &काष्ठा iwl_buf_alloc_cmd
	 */
	BUFFER_ALLOCATION = 0x8,
	/**
	 * @MFU_ASSERT_DUMP_NTF:
	 * &काष्ठा iwl_mfu_निश्चित_dump_notअगर
	 */
	MFU_ASSERT_DUMP_NTF = 0xFE,
पूर्ण;

/* Error response/notअगरication */
क्रमागत अणु
	FW_ERR_UNKNOWN_CMD = 0x0,
	FW_ERR_INVALID_CMD_PARAM = 0x1,
	FW_ERR_SERVICE = 0x2,
	FW_ERR_ARC_MEMORY = 0x3,
	FW_ERR_ARC_CODE = 0x4,
	FW_ERR_WATCH_DOG = 0x5,
	FW_ERR_WEP_GRP_KEY_INDX = 0x10,
	FW_ERR_WEP_KEY_SIZE = 0x11,
	FW_ERR_OBSOLETE_FUNC = 0x12,
	FW_ERR_UNEXPECTED = 0xFE,
	FW_ERR_FATAL = 0xFF
पूर्ण;

/** क्रमागत iwl_dbg_suspend_resume_cmds - dbgc suspend resume operations
 * dbgc suspend resume command operations
 * @DBGC_RESUME_CMD: resume dbgc recording
 * @DBGC_SUSPEND_CMD: stop dbgc recording
 */
क्रमागत iwl_dbg_suspend_resume_cmds अणु
	DBGC_RESUME_CMD,
	DBGC_SUSPEND_CMD,
पूर्ण;

/**
 * काष्ठा iwl_error_resp - FW error indication
 * ( REPLY_ERROR = 0x2 )
 * @error_type: one of FW_ERR_*
 * @cmd_id: the command ID क्रम which the error occurred
 * @reserved1: reserved
 * @bad_cmd_seq_num: sequence number of the erroneous command
 * @error_service: which service created the error, applicable only अगर
 *     error_type = 2, otherwise 0
 * @बारtamp: TSF in usecs.
 */
काष्ठा iwl_error_resp अणु
	__le32 error_type;
	u8 cmd_id;
	u8 reserved1;
	__le16 bad_cmd_seq_num;
	__le32 error_service;
	__le64 बारtamp;
पूर्ण __packed;

#घोषणा TX_FIFO_MAX_NUM_9000		8
#घोषणा TX_FIFO_MAX_NUM			15
#घोषणा RX_FIFO_MAX_NUM			2
#घोषणा TX_FIFO_INTERNAL_MAX_NUM	6

/**
 * काष्ठा iwl_shared_mem_cfg_v2 - Shared memory configuration inक्रमmation
 *
 * @shared_mem_addr: shared memory addr (pre 8000 HW set to 0x0 as MARBH is not
 *	accessible)
 * @shared_mem_size: shared memory size
 * @sample_buff_addr: पूर्णांकernal sample (mon/adc) buff addr (pre 8000 HW set to
 *	0x0 as accessible only via DBGM RDAT)
 * @sample_buff_size: पूर्णांकernal sample buff size
 * @txfअगरo_addr: start addr of TXF0 (excluding the context table 0.5KB), (pre
 *	8000 HW set to 0x0 as not accessible)
 * @txfअगरo_size: size of TXF0 ... TXF7
 * @rxfअगरo_size: RXF1, RXF2 sizes. If there is no RXF2, it'll have a value of 0
 * @page_buff_addr: used by UMAC and perक्रमmance debug (page miss analysis),
 *	when paging is not supported this should be 0
 * @page_buff_size: size of %page_buff_addr
 * @rxfअगरo_addr: Start address of rxFअगरo
 * @पूर्णांकernal_txfअगरo_addr: start address of पूर्णांकernalFअगरo
 * @पूर्णांकernal_txfअगरo_size: पूर्णांकernal fअगरos' size
 *
 * NOTE: on firmware that करोn't have IWL_UCODE_TLV_CAPA_EXTEND_SHARED_MEM_CFG
 *	 set, the last 3 members करोn't exist.
 */
काष्ठा iwl_shared_mem_cfg_v2 अणु
	__le32 shared_mem_addr;
	__le32 shared_mem_size;
	__le32 sample_buff_addr;
	__le32 sample_buff_size;
	__le32 txfअगरo_addr;
	__le32 txfअगरo_size[TX_FIFO_MAX_NUM_9000];
	__le32 rxfअगरo_size[RX_FIFO_MAX_NUM];
	__le32 page_buff_addr;
	__le32 page_buff_size;
	__le32 rxfअगरo_addr;
	__le32 पूर्णांकernal_txfअगरo_addr;
	__le32 पूर्णांकernal_txfअगरo_size[TX_FIFO_INTERNAL_MAX_NUM];
पूर्ण __packed; /* SHARED_MEM_ALLOC_API_S_VER_2 */

/**
 * काष्ठा iwl_shared_mem_lmac_cfg - LMAC shared memory configuration
 *
 * @txfअगरo_addr: start addr of TXF0 (excluding the context table 0.5KB)
 * @txfअगरo_size: size of TX FIFOs
 * @rxfअगरo1_addr: RXF1 addr
 * @rxfअगरo1_size: RXF1 size
 */
काष्ठा iwl_shared_mem_lmac_cfg अणु
	__le32 txfअगरo_addr;
	__le32 txfअगरo_size[TX_FIFO_MAX_NUM];
	__le32 rxfअगरo1_addr;
	__le32 rxfअगरo1_size;

पूर्ण __packed; /* SHARED_MEM_ALLOC_LMAC_API_S_VER_1 */

/**
 * काष्ठा iwl_shared_mem_cfg - Shared memory configuration inक्रमmation
 *
 * @shared_mem_addr: shared memory address
 * @shared_mem_size: shared memory size
 * @sample_buff_addr: पूर्णांकernal sample (mon/adc) buff addr
 * @sample_buff_size: पूर्णांकernal sample buff size
 * @rxfअगरo2_addr: start addr of RXF2
 * @rxfअगरo2_size: size of RXF2
 * @page_buff_addr: used by UMAC and perक्रमmance debug (page miss analysis),
 *	when paging is not supported this should be 0
 * @page_buff_size: size of %page_buff_addr
 * @lmac_num: number of LMACs (1 or 2)
 * @lmac_smem: per - LMAC smem data
 * @rxfअगरo2_control_addr: start addr of RXF2C
 * @rxfअगरo2_control_size: size of RXF2C
 */
काष्ठा iwl_shared_mem_cfg अणु
	__le32 shared_mem_addr;
	__le32 shared_mem_size;
	__le32 sample_buff_addr;
	__le32 sample_buff_size;
	__le32 rxfअगरo2_addr;
	__le32 rxfअगरo2_size;
	__le32 page_buff_addr;
	__le32 page_buff_size;
	__le32 lmac_num;
	काष्ठा iwl_shared_mem_lmac_cfg lmac_smem[3];
	__le32 rxfअगरo2_control_addr;
	__le32 rxfअगरo2_control_size;
पूर्ण __packed; /* SHARED_MEM_ALLOC_API_S_VER_4 */

/**
 * काष्ठा iwl_mfuart_load_notअगर_v1 - mfuart image version & status
 * ( MFUART_LOAD_NOTIFICATION = 0xb1 )
 * @installed_ver: installed image version
 * @बाह्यal_ver: बाह्यal image version
 * @status: MFUART loading status
 * @duration: MFUART loading समय
*/
काष्ठा iwl_mfuart_load_notअगर_v1 अणु
	__le32 installed_ver;
	__le32 बाह्यal_ver;
	__le32 status;
	__le32 duration;
पूर्ण __packed; /* MFU_LOADER_NTFY_API_S_VER_1 */

/**
 * काष्ठा iwl_mfuart_load_notअगर - mfuart image version & status
 * ( MFUART_LOAD_NOTIFICATION = 0xb1 )
 * @installed_ver: installed image version
 * @बाह्यal_ver: बाह्यal image version
 * @status: MFUART loading status
 * @duration: MFUART loading समय
 * @image_size: MFUART image size in bytes
*/
काष्ठा iwl_mfuart_load_notअगर अणु
	__le32 installed_ver;
	__le32 बाह्यal_ver;
	__le32 status;
	__le32 duration;
	/* image size valid only in v2 of the command */
	__le32 image_size;
पूर्ण __packed; /* MFU_LOADER_NTFY_API_S_VER_2 */

/**
 * काष्ठा iwl_mfu_निश्चित_dump_notअगर - mfuart dump logs
 * ( MFU_ASSERT_DUMP_NTF = 0xfe )
 * @निश्चित_id: mfuart निश्चित id that cause the notअगर
 * @curr_reset_num: number of निश्चितs since upसमय
 * @index_num: current chunk id
 * @parts_num: total number of chunks
 * @data_size: number of data bytes sent
 * @data: data buffer
 */
काष्ठा iwl_mfu_निश्चित_dump_notअगर अणु
	__le32   निश्चित_id;
	__le32   curr_reset_num;
	__le16   index_num;
	__le16   parts_num;
	__le32   data_size;
	__le32   data[0];
पूर्ण __packed; /* MFU_DUMP_ASSERT_API_S_VER_1 */

/**
 * क्रमागत iwl_mvm_marker_id - marker ids
 *
 * The ids क्रम dअगरferent type of markers to insert पूर्णांकo the usnअगरfer logs
 *
 * @MARKER_ID_TX_FRAME_LATENCY: TX latency marker
 * @MARKER_ID_SYNC_CLOCK: sync FW समय and sysसमय
 */
क्रमागत iwl_mvm_marker_id अणु
	MARKER_ID_TX_FRAME_LATENCY = 1,
	MARKER_ID_SYNC_CLOCK = 2,
पूर्ण; /* MARKER_ID_API_E_VER_2 */

/**
 * काष्ठा iwl_mvm_marker - mark info पूर्णांकo the usnअगरfer logs
 *
 * (MARKER_CMD = 0xcb)
 *
 * Mark the UTC समय stamp पूर्णांकo the usnअगरfer logs together with additional
 * metadata, so the usnअगरfer output can be parsed.
 * In the command response the ucode will वापस the GP2 समय.
 *
 * @dw_len: The amount of dwords following this byte including this byte.
 * @marker_id: A unique marker id (iwl_mvm_marker_id).
 * @reserved: reserved.
 * @बारtamp: in milliseconds since 1970-01-01 00:00:00 UTC
 * @metadata: additional meta data that will be written to the unsअगरfer log
 */
काष्ठा iwl_mvm_marker अणु
	u8 dw_len;
	u8 marker_id;
	__le16 reserved;
	__le64 बारtamp;
	__le32 metadata[0];
पूर्ण __packed; /* MARKER_API_S_VER_1 */

/**
 * काष्ठा iwl_mvm_marker_rsp - Response to marker cmd
 *
 * @gp2: The gp2 घड़ी value in the FW
 */
काष्ठा iwl_mvm_marker_rsp अणु
	__le32 gp2;
पूर्ण __packed;

/* Operation types क्रम the debug mem access */
क्रमागत अणु
	DEBUG_MEM_OP_READ = 0,
	DEBUG_MEM_OP_WRITE = 1,
	DEBUG_MEM_OP_WRITE_BYTES = 2,
पूर्ण;

#घोषणा DEBUG_MEM_MAX_SIZE_DWORDS 32

/**
 * काष्ठा iwl_dbg_mem_access_cmd - Request the device to पढ़ो/ग_लिखो memory
 * @op: DEBUG_MEM_OP_*
 * @addr: address to पढ़ो/ग_लिखो from/to
 * @len: in dwords, to पढ़ो/ग_लिखो
 * @data: क्रम ग_लिखो opeations, contains the source buffer
 */
काष्ठा iwl_dbg_mem_access_cmd अणु
	__le32 op;
	__le32 addr;
	__le32 len;
	__le32 data[];
पूर्ण __packed; /* DEBUG_(U|L)MAC_RD_WR_CMD_API_S_VER_1 */

/* Status responses क्रम the debug mem access */
क्रमागत अणु
	DEBUG_MEM_STATUS_SUCCESS = 0x0,
	DEBUG_MEM_STATUS_FAILED = 0x1,
	DEBUG_MEM_STATUS_LOCKED = 0x2,
	DEBUG_MEM_STATUS_HIDDEN = 0x3,
	DEBUG_MEM_STATUS_LENGTH = 0x4,
पूर्ण;

/**
 * काष्ठा iwl_dbg_mem_access_rsp - Response to debug mem commands
 * @status: DEBUG_MEM_STATUS_*
 * @len: पढ़ो dwords (0 क्रम ग_लिखो operations)
 * @data: contains the पढ़ो DWs
 */
काष्ठा iwl_dbg_mem_access_rsp अणु
	__le32 status;
	__le32 len;
	__le32 data[];
पूर्ण __packed; /* DEBUG_(U|L)MAC_RD_WR_RSP_API_S_VER_1 */

/**
 * काष्ठा iwl_dbg_suspend_resume_cmd - dbgc suspend resume command
 * @operation: suspend or resume operation, uses
 *	&क्रमागत iwl_dbg_suspend_resume_cmds
 */
काष्ठा iwl_dbg_suspend_resume_cmd अणु
	__le32 operation;
पूर्ण __packed;

#घोषणा BUF_ALLOC_MAX_NUM_FRAGS 16

/**
 * काष्ठा iwl_buf_alloc_frag - a DBGC fragment
 * @addr: base address of the fragment
 * @size: size of the fragment
 */
काष्ठा iwl_buf_alloc_frag अणु
	__le64 addr;
	__le32 size;
पूर्ण __packed; /* FRAGMENT_STRUCTURE_API_S_VER_1 */

/**
 * काष्ठा iwl_buf_alloc_cmd - buffer allocation command
 * @alloc_id: &क्रमागत iwl_fw_ini_allocation_id
 * @buf_location: &क्रमागत iwl_fw_ini_buffer_location
 * @num_frags: number of fragments
 * @frags: fragments array
 */
काष्ठा iwl_buf_alloc_cmd अणु
	__le32 alloc_id;
	__le32 buf_location;
	__le32 num_frags;
	काष्ठा iwl_buf_alloc_frag frags[BUF_ALLOC_MAX_NUM_FRAGS];
पूर्ण __packed; /* BUFFER_ALLOCATION_CMD_API_S_VER_2 */

/**
 * काष्ठा iwl_dbg_host_event_cfg_cmd
 * @enabled_severities: enabled severities
 */
काष्ठा iwl_dbg_host_event_cfg_cmd अणु
	__le32 enabled_severities;
पूर्ण __packed; /* DEBUG_HOST_EVENT_CFG_CMD_API_S_VER_1 */

#पूर्ण_अगर /* __iwl_fw_api_debug_h__ */
