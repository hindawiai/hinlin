<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause */
/*
 * Copyright (C) 2014, 2018-2020 Intel Corporation
 * Copyright (C) 2014-2015 Intel Mobile Communications GmbH
 * Copyright (C) 2016-2017 Intel Deutschland GmbH
 */
#अगर_अघोषित __fw_error_dump_h__
#घोषणा __fw_error_dump_h__

#समावेश <linux/types.h>
#समावेश "fw/api/cmdhdr.h"

#घोषणा IWL_FW_ERROR_DUMP_BARKER	0x14789632
#घोषणा IWL_FW_INI_ERROR_DUMP_BARKER	0x14789633

/**
 * क्रमागत iwl_fw_error_dump_type - types of data in the dump file
 * @IWL_FW_ERROR_DUMP_CSR: Control Status Registers - from offset 0
 * @IWL_FW_ERROR_DUMP_RXF:
 * @IWL_FW_ERROR_DUMP_TXCMD: last TX command data, काष्ठाured as
 *	&काष्ठा iwl_fw_error_dump_txcmd packets
 * @IWL_FW_ERROR_DUMP_DEV_FW_INFO:  काष्ठा %iwl_fw_error_dump_info
 *	info on the device / firmware.
 * @IWL_FW_ERROR_DUMP_FW_MONITOR: firmware monitor
 * @IWL_FW_ERROR_DUMP_PRPH: range of periphery रेजिस्टरs - there can be several
 *	sections like this in a single file.
 * @IWL_FW_ERROR_DUMP_FH_REGS: range of FH रेजिस्टरs
 * @IWL_FW_ERROR_DUMP_MEM: chunk of memory
 * @IWL_FW_ERROR_DUMP_ERROR_INFO: description of what triggered this dump.
 *	Structured as &काष्ठा iwl_fw_error_dump_trigger_desc.
 * @IWL_FW_ERROR_DUMP_RB: the content of an RB काष्ठाured as
 *	&काष्ठा iwl_fw_error_dump_rb
 * @IWL_FW_ERROR_PAGING: UMAC's image memory segments which were
 *	paged to the DRAM.
 * @IWL_FW_ERROR_DUMP_RADIO_REG: Dump the radio रेजिस्टरs.
 * @IWL_FW_ERROR_DUMP_EXTERNAL: used only by बाह्यal code utilities, and
 *	क्रम that reason is not in use in any other place in the Linux Wi-Fi
 *	stack.
 * @IWL_FW_ERROR_DUMP_MEM_CFG: the addresses and sizes of fअगरos in the smem,
 *	which we get from the fw after ALIVE. The content is काष्ठाured as
 *	&काष्ठा iwl_fw_error_dump_smem_cfg.
 */
क्रमागत iwl_fw_error_dump_type अणु
	/* 0 is deprecated */
	IWL_FW_ERROR_DUMP_CSR = 1,
	IWL_FW_ERROR_DUMP_RXF = 2,
	IWL_FW_ERROR_DUMP_TXCMD = 3,
	IWL_FW_ERROR_DUMP_DEV_FW_INFO = 4,
	IWL_FW_ERROR_DUMP_FW_MONITOR = 5,
	IWL_FW_ERROR_DUMP_PRPH = 6,
	IWL_FW_ERROR_DUMP_TXF = 7,
	IWL_FW_ERROR_DUMP_FH_REGS = 8,
	IWL_FW_ERROR_DUMP_MEM = 9,
	IWL_FW_ERROR_DUMP_ERROR_INFO = 10,
	IWL_FW_ERROR_DUMP_RB = 11,
	IWL_FW_ERROR_DUMP_PAGING = 12,
	IWL_FW_ERROR_DUMP_RADIO_REG = 13,
	IWL_FW_ERROR_DUMP_INTERNAL_TXF = 14,
	IWL_FW_ERROR_DUMP_EXTERNAL = 15, /* Do not move */
	IWL_FW_ERROR_DUMP_MEM_CFG = 16,
	IWL_FW_ERROR_DUMP_D3_DEBUG_DATA = 17,

	IWL_FW_ERROR_DUMP_MAX,
पूर्ण;

/**
 * काष्ठा iwl_fw_error_dump_data - data क्रम one type
 * @type: &क्रमागत iwl_fw_error_dump_type
 * @len: the length starting from %data
 * @data: the data itself
 */
काष्ठा iwl_fw_error_dump_data अणु
	__le32 type;
	__le32 len;
	__u8 data[];
पूर्ण __packed;

/**
 * काष्ठा iwl_fw_error_dump_file - the layout of the header of the file
 * @barker: must be %IWL_FW_ERROR_DUMP_BARKER
 * @file_len: the length of all the file starting from %barker
 * @data: array of &काष्ठा iwl_fw_error_dump_data
 */
काष्ठा iwl_fw_error_dump_file अणु
	__le32 barker;
	__le32 file_len;
	u8 data[0];
पूर्ण __packed;

/**
 * काष्ठा iwl_fw_error_dump_txcmd - TX command data
 * @cmdlen: original length of command
 * @caplen: captured length of command (may be less)
 * @data: captured command data, @caplen bytes
 */
काष्ठा iwl_fw_error_dump_txcmd अणु
	__le32 cmdlen;
	__le32 caplen;
	u8 data[];
पूर्ण __packed;

/**
 * काष्ठा iwl_fw_error_dump_fअगरo - RX/TX FIFO data
 * @fअगरo_num: number of FIFO (starting from 0)
 * @available_bytes: num of bytes available in FIFO (may be less than FIFO size)
 * @wr_ptr: position of ग_लिखो poपूर्णांकer
 * @rd_ptr: position of पढ़ो poपूर्णांकer
 * @fence_ptr: position of fence poपूर्णांकer
 * @fence_mode: the current mode of the fence (beक्रमe locking) -
 *	0=follow RD poपूर्णांकer ; 1 = मुक्तze
 * @data: all of the FIFO's data
 */
काष्ठा iwl_fw_error_dump_fअगरo अणु
	__le32 fअगरo_num;
	__le32 available_bytes;
	__le32 wr_ptr;
	__le32 rd_ptr;
	__le32 fence_ptr;
	__le32 fence_mode;
	u8 data[];
पूर्ण __packed;

क्रमागत iwl_fw_error_dump_family अणु
	IWL_FW_ERROR_DUMP_FAMILY_7 = 7,
	IWL_FW_ERROR_DUMP_FAMILY_8 = 8,
पूर्ण;

#घोषणा MAX_NUM_LMAC 2

/**
 * काष्ठा iwl_fw_error_dump_info - info on the device / firmware
 * @hw_type: the type of the device
 * @hw_step: the step of the device
 * @fw_human_पढ़ोable: human पढ़ोable FW version
 * @dev_human_पढ़ोable: name of the device
 * @bus_human_पढ़ोable: name of the bus used
 * @num_of_lmacs: the number of lmacs
 * @lmac_err_id: the lmac 0/1 error_id/rt_status that triggered the latest dump
 *	अगर the dump collection was not initiated by an निश्चित, the value is 0
 * @umac_err_id: the umac error_id/rt_status that triggered the latest dump
 *	अगर the dump collection was not initiated by an निश्चित, the value is 0
 */
काष्ठा iwl_fw_error_dump_info अणु
	__le32 hw_type;
	__le32 hw_step;
	u8 fw_human_पढ़ोable[FW_VER_HUMAN_READABLE_SZ];
	u8 dev_human_पढ़ोable[64];
	u8 bus_human_पढ़ोable[8];
	u8 num_of_lmacs;
	__le32 umac_err_id;
	__le32 lmac_err_id[MAX_NUM_LMAC];
पूर्ण __packed;

/**
 * काष्ठा iwl_fw_error_dump_fw_mon - FW monitor data
 * @fw_mon_wr_ptr: the position of the ग_लिखो poपूर्णांकer in the cyclic buffer
 * @fw_mon_base_ptr: base poपूर्णांकer of the data
 * @fw_mon_cycle_cnt: number of wraparounds
 * @fw_mon_base_high_ptr: used in AX210 devices, the base adderss is 64 bit
 *	so fw_mon_base_ptr holds LSB 32 bits and fw_mon_base_high_ptr hold
 *	MSB 32 bits
 * @reserved: क्रम future use
 * @data: captured data
 */
काष्ठा iwl_fw_error_dump_fw_mon अणु
	__le32 fw_mon_wr_ptr;
	__le32 fw_mon_base_ptr;
	__le32 fw_mon_cycle_cnt;
	__le32 fw_mon_base_high_ptr;
	__le32 reserved[2];
	u8 data[];
पूर्ण __packed;

#घोषणा MAX_NUM_LMAC 2
#घोषणा TX_FIFO_INTERNAL_MAX_NUM	6
#घोषणा TX_FIFO_MAX_NUM			15
/**
 * काष्ठा iwl_fw_error_dump_smem_cfg - Dump SMEM configuration
 *	This must follow &काष्ठा iwl_fwrt_shared_mem_cfg.
 * @num_lmacs: number of lmacs
 * @num_txfअगरo_entries: number of tx fअगरos
 * @lmac: sizes of lmacs txfअगरos and rxfअगरo1
 * @rxfअगरo2_size: size of rxfअगरo2
 * @पूर्णांकernal_txfअगरo_addr: address of पूर्णांकernal tx fअगरo
 * @पूर्णांकernal_txfअगरo_size: size of पूर्णांकernal tx fअगरo
 */
काष्ठा iwl_fw_error_dump_smem_cfg अणु
	__le32 num_lmacs;
	__le32 num_txfअगरo_entries;
	काष्ठा अणु
		__le32 txfअगरo_size[TX_FIFO_MAX_NUM];
		__le32 rxfअगरo1_size;
	पूर्ण lmac[MAX_NUM_LMAC];
	__le32 rxfअगरo2_size;
	__le32 पूर्णांकernal_txfअगरo_addr;
	__le32 पूर्णांकernal_txfअगरo_size[TX_FIFO_INTERNAL_MAX_NUM];
पूर्ण __packed;
/**
 * काष्ठा iwl_fw_error_dump_prph - periphery रेजिस्टरs data
 * @prph_start: address of the first रेजिस्टर in this chunk
 * @data: the content of the रेजिस्टरs
 */
काष्ठा iwl_fw_error_dump_prph अणु
	__le32 prph_start;
	__le32 data[];
पूर्ण;

क्रमागत iwl_fw_error_dump_mem_type अणु
	IWL_FW_ERROR_DUMP_MEM_SRAM,
	IWL_FW_ERROR_DUMP_MEM_SMEM,
	IWL_FW_ERROR_DUMP_MEM_NAMED_MEM = 10,
पूर्ण;

/**
 * काष्ठा iwl_fw_error_dump_mem - chunk of memory
 * @type: &क्रमागत iwl_fw_error_dump_mem_type
 * @offset: the offset from which the memory was पढ़ो
 * @data: the content of the memory
 */
काष्ठा iwl_fw_error_dump_mem अणु
	__le32 type;
	__le32 offset;
	u8 data[];
पूर्ण;

/* Dump version, used by the dump parser to dअगरferentiate between
 * dअगरferent dump क्रमmats
 */
#घोषणा IWL_INI_DUMP_VER 1

/* Use bit 31 as dump info type to aव्योम colliding with region types */
#घोषणा IWL_INI_DUMP_INFO_TYPE BIT(31)

/**
 * काष्ठा iwl_fw_ini_dump_entry
 * @list: list of dump entries
 * @size: size of the data
 * @data: entry data
 */
काष्ठा iwl_fw_ini_dump_entry अणु
	काष्ठा list_head list;
	u32 size;
	u8 data[];
पूर्ण __packed;

/**
 * काष्ठा iwl_fw_error_dump_file - header of dump file
 * @barker: must be %IWL_FW_INI_ERROR_DUMP_BARKER
 * @file_len: the length of all the file including the header
 */
काष्ठा iwl_fw_ini_dump_file_hdr अणु
	__le32 barker;
	__le32 file_len;
पूर्ण __packed;

/**
 * काष्ठा iwl_fw_ini_fअगरo_hdr - fअगरo range header
 * @fअगरo_num: the fअगरo number. In हाल of umac rx fअगरo, set BIT(31) to
 *	distinguish between lmac and umac rx fअगरos
 * @num_of_रेजिस्टरs: num of रेजिस्टरs to dump, dword size each
 */
काष्ठा iwl_fw_ini_fअगरo_hdr अणु
	__le32 fअगरo_num;
	__le32 num_of_रेजिस्टरs;
पूर्ण __packed;

/**
 * काष्ठा iwl_fw_ini_error_dump_range - range of memory
 * @range_data_size: the size of this range, in bytes
 * @पूर्णांकernal_base_addr: base address of पूर्णांकernal memory range
 * @dram_base_addr: base address of dram monitor range
 * @page_num: page number of memory range
 * @fअगरo_hdr: fअगरo header of memory range
 * @fw_pkt: FW packet header of memory range
 * @data: the actual memory
 */
काष्ठा iwl_fw_ini_error_dump_range अणु
	__le32 range_data_size;
	जोड़ अणु
		__le32 पूर्णांकernal_base_addr;
		__le64 dram_base_addr;
		__le32 page_num;
		काष्ठा iwl_fw_ini_fअगरo_hdr fअगरo_hdr;
		काष्ठा iwl_cmd_header fw_pkt_hdr;
	पूर्ण;
	__le32 data[];
पूर्ण __packed;

/**
 * काष्ठा iwl_fw_ini_error_dump_header - ini region dump header
 * @version: dump version
 * @region_id: id of the region
 * @num_of_ranges: number of ranges in this region
 * @name_len: number of bytes allocated to the name string of this region
 * @name: name of the region
 */
काष्ठा iwl_fw_ini_error_dump_header अणु
	__le32 version;
	__le32 region_id;
	__le32 num_of_ranges;
	__le32 name_len;
	u8 name[IWL_FW_INI_MAX_NAME];
पूर्ण;

/**
 * काष्ठा iwl_fw_ini_error_dump - ini region dump
 * @header: the header of this region
 * @ranges: the memory ranges of this region
 */
काष्ठा iwl_fw_ini_error_dump अणु
	काष्ठा iwl_fw_ini_error_dump_header header;
	काष्ठा iwl_fw_ini_error_dump_range ranges[];
पूर्ण __packed;

/* This bit is used to dअगरferentiate between lmac and umac rxf */
#घोषणा IWL_RXF_UMAC_BIT BIT(31)

/**
 * काष्ठा iwl_fw_ini_error_dump_रेजिस्टर - ini रेजिस्टर dump
 * @addr: address of the रेजिस्टर
 * @data: data of the रेजिस्टर
 */
काष्ठा iwl_fw_ini_error_dump_रेजिस्टर अणु
	__le32 addr;
	__le32 data;
पूर्ण __packed;

/**
 * काष्ठा iwl_fw_ini_dump_cfg_name - configuration name
 * @image_type: image type the configuration is related to
 * @cfg_name_len: length of the configuration name
 * @cfg_name: name of the configuraiton
 */
काष्ठा iwl_fw_ini_dump_cfg_name अणु
	__le32 image_type;
	__le32 cfg_name_len;
	u8 cfg_name[IWL_FW_INI_MAX_CFG_NAME];
पूर्ण __packed;

/* AX210's HW type */
#घोषणा IWL_AX210_HW_TYPE 0x42
/* How many bits to roll when adding to the HW type of AX210 HW */
#घोषणा IWL_AX210_HW_TYPE_ADDITION_SHIFT 12
/* This prph is used to tell apart HW_TYPE == 0x42 NICs */
#घोषणा WFPM_OTP_CFG1_ADDR 0xd03098
#घोषणा WFPM_OTP_CFG1_IS_JACKET_BIT BIT(4)
#घोषणा WFPM_OTP_CFG1_IS_CDB_BIT BIT(5)

/* काष्ठा iwl_fw_ini_dump_info - ini dump inक्रमmation
 * @version: dump version
 * @समय_poपूर्णांक: समय poपूर्णांक that caused the dump collection
 * @trigger_reason: reason of the trigger
 * @बाह्यal_cfg_state: &क्रमागत iwl_ini_cfg_state
 * @ver_type: FW version type
 * @ver_subtype: FW version subype
 * @hw_step: HW step
 * @hw_type: HW type
 * @rf_id_flavor: HW RF id flavor
 * @rf_id_dash: HW RF id dash
 * @rf_id_step: HW RF id step
 * @rf_id_type: HW RF id type
 * @lmac_major: lmac major version
 * @lmac_minor: lmac minor version
 * @umac_major: umac major version
 * @umac_minor: umac minor version
 * @fw_mon_mode: FW monitor mode &क्रमागत iwl_fw_ini_buffer_location
 * @regions_mask: biपंचांगap mask of regions ids in the dump
 * @build_tag_len: length of the build tag
 * @build_tag: build tag string
 * @num_of_cfg_names: number of configuration name काष्ठाs
 * @cfg_names: configuration names
 */
काष्ठा iwl_fw_ini_dump_info अणु
	__le32 version;
	__le32 समय_poपूर्णांक;
	__le32 trigger_reason;
	__le32 बाह्यal_cfg_state;
	__le32 ver_type;
	__le32 ver_subtype;
	__le32 hw_step;
	__le32 hw_type;
	__le32 rf_id_flavor;
	__le32 rf_id_dash;
	__le32 rf_id_step;
	__le32 rf_id_type;
	__le32 lmac_major;
	__le32 lmac_minor;
	__le32 umac_major;
	__le32 umac_minor;
	__le32 fw_mon_mode;
	__le64 regions_mask;
	__le32 build_tag_len;
	u8 build_tag[FW_VER_HUMAN_READABLE_SZ];
	__le32 num_of_cfg_names;
	काष्ठा iwl_fw_ini_dump_cfg_name cfg_names[];
पूर्ण __packed;

/**
 * काष्ठा iwl_fw_ini_err_table_dump - ini error table dump
 * @header: header of the region
 * @version: error table version
 * @ranges: the memory ranges of this this region
 */
काष्ठा iwl_fw_ini_err_table_dump अणु
	काष्ठा iwl_fw_ini_error_dump_header header;
	__le32 version;
	काष्ठा iwl_fw_ini_error_dump_range ranges[];
पूर्ण __packed;

/**
 * काष्ठा iwl_fw_error_dump_rb - content of an Receive Buffer
 * @index: the index of the Receive Buffer in the Rx queue
 * @rxq: the RB's Rx queue
 * @reserved:
 * @data: the content of the Receive Buffer
 */
काष्ठा iwl_fw_error_dump_rb अणु
	__le32 index;
	__le32 rxq;
	__le32 reserved;
	u8 data[];
पूर्ण;

/**
 * काष्ठा iwl_fw_ini_monitor_dump - ini monitor dump
 * @header: header of the region
 * @ग_लिखो_ptr: ग_लिखो poपूर्णांकer position in the buffer
 * @cycle_cnt: cycles count
 * @cur_frag: current fragment in use
 * @ranges: the memory ranges of this this region
 */
काष्ठा iwl_fw_ini_monitor_dump अणु
	काष्ठा iwl_fw_ini_error_dump_header header;
	__le32 ग_लिखो_ptr;
	__le32 cycle_cnt;
	__le32 cur_frag;
	काष्ठा iwl_fw_ini_error_dump_range ranges[];
पूर्ण __packed;

/**
 * काष्ठा iwl_fw_ini_special_device_memory - special device memory
 * @header: header of the region
 * @type: type of special memory
 * @version: काष्ठा special memory version
 * @ranges: the memory ranges of this this region
 */
काष्ठा iwl_fw_ini_special_device_memory अणु
	काष्ठा iwl_fw_ini_error_dump_header header;
	__le16 type;
	__le16 version;
	काष्ठा iwl_fw_ini_error_dump_range ranges[];
पूर्ण __packed;

/**
 * काष्ठा iwl_fw_error_dump_paging - content of the UMAC's image page
 *	block on DRAM
 * @index: the index of the page block
 * @reserved:
 * @data: the content of the page block
 */
काष्ठा iwl_fw_error_dump_paging अणु
	__le32 index;
	__le32 reserved;
	u8 data[];
पूर्ण;

/**
 * iwl_fw_error_next_data - advance fw error dump data poपूर्णांकer
 * @data: previous data block
 * Returns: next data block
 */
अटल अंतरभूत काष्ठा iwl_fw_error_dump_data *
iwl_fw_error_next_data(काष्ठा iwl_fw_error_dump_data *data)
अणु
	वापस (व्योम *)(data->data + le32_to_cpu(data->len));
पूर्ण

/**
 * क्रमागत iwl_fw_dbg_trigger - triggers available
 *
 * @FW_DBG_TRIGGER_USER: trigger log collection by user
 *	This should not be defined as a trigger to the driver, but a value the
 *	driver should set to indicate that the trigger was initiated by the
 *	user.
 * @FW_DBG_TRIGGER_FW_ASSERT: trigger log collection when the firmware निश्चितs
 * @FW_DBG_TRIGGER_MISSED_BEACONS: trigger log collection when beacons are
 *	missed.
 * @FW_DBG_TRIGGER_CHANNEL_SWITCH: trigger log collection upon channel चयन.
 * @FW_DBG_TRIGGER_FW_NOTIF: trigger log collection when the firmware sends a
 *	command response or a notअगरication.
 * @FW_DBG_TRIGGER_MLME: trigger log collection upon MLME event.
 * @FW_DBG_TRIGGER_STATS: trigger log collection upon statistics threshold.
 * @FW_DBG_TRIGGER_RSSI: trigger log collection when the rssi of the beacon
 *	goes below a threshold.
 * @FW_DBG_TRIGGER_TXQ_TIMERS: configures the समयrs क्रम the Tx queue hang
 *	detection.
 * @FW_DBG_TRIGGER_TIME_EVENT: trigger log collection upon समय events related
 *	events.
 * @FW_DBG_TRIGGER_BA: trigger log collection upon BlockAck related events.
 * @FW_DBG_TX_LATENCY: trigger log collection when the tx latency goes above a
 *	threshold.
 * @FW_DBG_TDLS: trigger log collection upon TDLS related events.
 * @FW_DBG_TRIGGER_TX_STATUS: trigger log collection upon tx status when
 *  the firmware sends a tx reply.
 * @FW_DBG_TRIGGER_ALIVE_TIMEOUT: trigger log collection अगर alive flow समयouts
 * @FW_DBG_TRIGGER_DRIVER: trigger log collection upon a flow failure
 *	in the driver.
 */
क्रमागत iwl_fw_dbg_trigger अणु
	FW_DBG_TRIGGER_INVALID = 0,
	FW_DBG_TRIGGER_USER,
	FW_DBG_TRIGGER_FW_ASSERT,
	FW_DBG_TRIGGER_MISSED_BEACONS,
	FW_DBG_TRIGGER_CHANNEL_SWITCH,
	FW_DBG_TRIGGER_FW_NOTIF,
	FW_DBG_TRIGGER_MLME,
	FW_DBG_TRIGGER_STATS,
	FW_DBG_TRIGGER_RSSI,
	FW_DBG_TRIGGER_TXQ_TIMERS,
	FW_DBG_TRIGGER_TIME_EVENT,
	FW_DBG_TRIGGER_BA,
	FW_DBG_TRIGGER_TX_LATENCY,
	FW_DBG_TRIGGER_TDLS,
	FW_DBG_TRIGGER_TX_STATUS,
	FW_DBG_TRIGGER_ALIVE_TIMEOUT,
	FW_DBG_TRIGGER_DRIVER,

	/* must be last */
	FW_DBG_TRIGGER_MAX,
पूर्ण;

/**
 * काष्ठा iwl_fw_error_dump_trigger_desc - describes the trigger condition
 * @type: &क्रमागत iwl_fw_dbg_trigger
 * @data: raw data about what happened
 */
काष्ठा iwl_fw_error_dump_trigger_desc अणु
	__le32 type;
	u8 data[];
पूर्ण;

#पूर्ण_अगर /* __fw_error_dump_h__ */
