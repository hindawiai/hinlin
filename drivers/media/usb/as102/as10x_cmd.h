<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Abilis Systems Single DVB-T Receiver
 * Copyright (C) 2008 Pierrick Hascoet <pierrick.hascoet@abilis.com>
 */
#अगर_अघोषित _AS10X_CMD_H_
#घोषणा _AS10X_CMD_H_

#समावेश <linux/kernel.h>

#समावेश "as102_fe_types.h"

/*********************************/
/*       MACRO DEFINITIONS       */
/*********************************/
#घोषणा AS10X_CMD_ERROR		-1

#घोषणा SERVICE_PROG_ID		0x0002
#घोषणा SERVICE_PROG_VERSION	0x0001

#घोषणा HIER_NONE		0x00
#घोषणा HIER_LOW_PRIORITY	0x01

#घोषणा HEADER_SIZE (माप(काष्ठा as10x_cmd_header_t))

/* context request types */
#घोषणा GET_CONTEXT_DATA	1
#घोषणा SET_CONTEXT_DATA	2

/* ODSP suspend modes */
#घोषणा CFG_MODE_ODSP_RESUME	0
#घोषणा CFG_MODE_ODSP_SUSPEND	1

/* Dump memory size */
#घोषणा DUMP_BLOCK_SIZE_MAX	0x20

/*********************************/
/*     TYPE DEFINITION           */
/*********************************/
क्रमागत control_proc अणु
	CONTROL_PROC_TURNON			= 0x0001,
	CONTROL_PROC_TURNON_RSP			= 0x0100,
	CONTROL_PROC_SET_REGISTER		= 0x0002,
	CONTROL_PROC_SET_REGISTER_RSP		= 0x0200,
	CONTROL_PROC_GET_REGISTER		= 0x0003,
	CONTROL_PROC_GET_REGISTER_RSP		= 0x0300,
	CONTROL_PROC_SETTUNE			= 0x000A,
	CONTROL_PROC_SETTUNE_RSP		= 0x0A00,
	CONTROL_PROC_GETTUNESTAT		= 0x000B,
	CONTROL_PROC_GETTUNESTAT_RSP		= 0x0B00,
	CONTROL_PROC_GETTPS			= 0x000D,
	CONTROL_PROC_GETTPS_RSP			= 0x0D00,
	CONTROL_PROC_SETFILTER			= 0x000E,
	CONTROL_PROC_SETFILTER_RSP		= 0x0E00,
	CONTROL_PROC_REMOVEFILTER		= 0x000F,
	CONTROL_PROC_REMOVEFILTER_RSP		= 0x0F00,
	CONTROL_PROC_GET_IMPULSE_RESP		= 0x0012,
	CONTROL_PROC_GET_IMPULSE_RESP_RSP	= 0x1200,
	CONTROL_PROC_START_STREAMING		= 0x0013,
	CONTROL_PROC_START_STREAMING_RSP	= 0x1300,
	CONTROL_PROC_STOP_STREAMING		= 0x0014,
	CONTROL_PROC_STOP_STREAMING_RSP		= 0x1400,
	CONTROL_PROC_GET_DEMOD_STATS		= 0x0015,
	CONTROL_PROC_GET_DEMOD_STATS_RSP	= 0x1500,
	CONTROL_PROC_ELNA_CHANGE_MODE		= 0x0016,
	CONTROL_PROC_ELNA_CHANGE_MODE_RSP	= 0x1600,
	CONTROL_PROC_ODSP_CHANGE_MODE		= 0x0017,
	CONTROL_PROC_ODSP_CHANGE_MODE_RSP	= 0x1700,
	CONTROL_PROC_AGC_CHANGE_MODE		= 0x0018,
	CONTROL_PROC_AGC_CHANGE_MODE_RSP	= 0x1800,

	CONTROL_PROC_CONTEXT			= 0x00FC,
	CONTROL_PROC_CONTEXT_RSP		= 0xFC00,
	CONTROL_PROC_DUMP_MEMORY		= 0x00FD,
	CONTROL_PROC_DUMP_MEMORY_RSP		= 0xFD00,
	CONTROL_PROC_DUMPLOG_MEMORY		= 0x00FE,
	CONTROL_PROC_DUMPLOG_MEMORY_RSP		= 0xFE00,
	CONTROL_PROC_TURNOFF			= 0x00FF,
	CONTROL_PROC_TURNOFF_RSP		= 0xFF00
पूर्ण;

जोड़ as10x_turn_on अणु
	/* request */
	काष्ठा अणु
		/* request identअगरier */
		__le16 proc_id;
	पूर्ण __packed req;
	/* response */
	काष्ठा अणु
		/* response identअगरier */
		__le16 proc_id;
		/* error */
		uपूर्णांक8_t error;
	पूर्ण __packed rsp;
पूर्ण __packed;

जोड़ as10x_turn_off अणु
	/* request */
	काष्ठा अणु
		/* request identअगरier */
		__le16 proc_id;
	पूर्ण __packed req;
	/* response */
	काष्ठा अणु
		/* response identअगरier */
		__le16 proc_id;
		/* error */
		uपूर्णांक8_t err;
	पूर्ण __packed rsp;
पूर्ण __packed;

जोड़ as10x_set_tune अणु
	/* request */
	काष्ठा अणु
		/* request identअगरier */
		__le16 proc_id;
		/* tune params */
		काष्ठा as10x_tune_args args;
	पूर्ण __packed req;
	/* response */
	काष्ठा अणु
		/* response identअगरier */
		__le16 proc_id;
		/* response error */
		uपूर्णांक8_t error;
	पूर्ण __packed rsp;
पूर्ण __packed;

जोड़ as10x_get_tune_status अणु
	/* request */
	काष्ठा अणु
		/* request identअगरier */
		__le16 proc_id;
	पूर्ण __packed req;
	/* response */
	काष्ठा अणु
		/* response identअगरier */
		__le16 proc_id;
		/* response error */
		uपूर्णांक8_t error;
		/* tune status */
		काष्ठा as10x_tune_status sts;
	पूर्ण __packed rsp;
पूर्ण __packed;

जोड़ as10x_get_tps अणु
	/* request */
	काष्ठा अणु
		/* request identअगरier */
		__le16 proc_id;
	पूर्ण __packed req;
	/* response */
	काष्ठा अणु
		/* response identअगरier */
		__le16 proc_id;
		/* response error */
		uपूर्णांक8_t error;
		/* tps details */
		काष्ठा as10x_tps tps;
	पूर्ण __packed rsp;
पूर्ण __packed;

जोड़ as10x_common अणु
	/* request */
	काष्ठा अणु
		/* request identअगरier */
		__le16  proc_id;
	पूर्ण __packed req;
	/* response */
	काष्ठा अणु
		/* response identअगरier */
		__le16 proc_id;
		/* response error */
		uपूर्णांक8_t error;
	पूर्ण __packed rsp;
पूर्ण __packed;

जोड़ as10x_add_pid_filter अणु
	/* request */
	काष्ठा अणु
		/* request identअगरier */
		__le16  proc_id;
		/* PID to filter */
		__le16  pid;
		/* stream type (MPE, PSI/SI or PES )*/
		uपूर्णांक8_t stream_type;
		/* PID index in filter table */
		uपूर्णांक8_t idx;
	पूर्ण __packed req;
	/* response */
	काष्ठा अणु
		/* response identअगरier */
		__le16 proc_id;
		/* response error */
		uपूर्णांक8_t error;
		/* Filter id */
		uपूर्णांक8_t filter_id;
	पूर्ण __packed rsp;
पूर्ण __packed;

जोड़ as10x_del_pid_filter अणु
	/* request */
	काष्ठा अणु
		/* request identअगरier */
		__le16  proc_id;
		/* PID to हटाओ */
		__le16  pid;
	पूर्ण __packed req;
	/* response */
	काष्ठा अणु
		/* response identअगरier */
		__le16 proc_id;
		/* response error */
		uपूर्णांक8_t error;
	पूर्ण __packed rsp;
पूर्ण __packed;

जोड़ as10x_start_streaming अणु
	/* request */
	काष्ठा अणु
		/* request identअगरier */
		__le16 proc_id;
	पूर्ण __packed req;
	/* response */
	काष्ठा अणु
		/* response identअगरier */
		__le16 proc_id;
		/* error */
		uपूर्णांक8_t error;
	पूर्ण __packed rsp;
पूर्ण __packed;

जोड़ as10x_stop_streaming अणु
	/* request */
	काष्ठा अणु
		/* request identअगरier */
		__le16 proc_id;
	पूर्ण __packed req;
	/* response */
	काष्ठा अणु
		/* response identअगरier */
		__le16 proc_id;
		/* error */
		uपूर्णांक8_t error;
	पूर्ण __packed rsp;
पूर्ण __packed;

जोड़ as10x_get_demod_stats अणु
	/* request */
	काष्ठा अणु
		/* request identअगरier */
		__le16 proc_id;
	पूर्ण __packed req;
	/* response */
	काष्ठा अणु
		/* response identअगरier */
		__le16 proc_id;
		/* error */
		uपूर्णांक8_t error;
		/* demod stats */
		काष्ठा as10x_demod_stats stats;
	पूर्ण __packed rsp;
पूर्ण __packed;

जोड़ as10x_get_impulse_resp अणु
	/* request */
	काष्ठा अणु
		/* request identअगरier */
		__le16 proc_id;
	पूर्ण __packed req;
	/* response */
	काष्ठा अणु
		/* response identअगरier */
		__le16 proc_id;
		/* error */
		uपूर्णांक8_t error;
		/* impulse response पढ़ोy */
		uपूर्णांक8_t is_पढ़ोy;
	पूर्ण __packed rsp;
पूर्ण __packed;

जोड़ as10x_fw_context अणु
	/* request */
	काष्ठा अणु
		/* request identअगरier */
		__le16 proc_id;
		/* value to ग_लिखो (क्रम set context)*/
		काष्ठा as10x_रेजिस्टर_value reg_val;
		/* context tag */
		__le16 tag;
		/* context request type */
		__le16 type;
	पूर्ण __packed req;
	/* response */
	काष्ठा अणु
		/* response identअगरier */
		__le16 proc_id;
		/* value पढ़ो (क्रम get context) */
		काष्ठा as10x_रेजिस्टर_value reg_val;
		/* context request type */
		__le16 type;
		/* error */
		uपूर्णांक8_t error;
	पूर्ण __packed rsp;
पूर्ण __packed;

जोड़ as10x_set_रेजिस्टर अणु
	/* request */
	काष्ठा अणु
		/* response identअगरier */
		__le16 proc_id;
		/* रेजिस्टर description */
		काष्ठा as10x_रेजिस्टर_addr reg_addr;
		/* रेजिस्टर content */
		काष्ठा as10x_रेजिस्टर_value reg_val;
	पूर्ण __packed req;
	/* response */
	काष्ठा अणु
		/* response identअगरier */
		__le16 proc_id;
		/* error */
		uपूर्णांक8_t error;
	पूर्ण __packed rsp;
पूर्ण __packed;

जोड़ as10x_get_रेजिस्टर अणु
	/* request */
	काष्ठा अणु
		/* response identअगरier */
		__le16 proc_id;
		/* रेजिस्टर description */
		काष्ठा as10x_रेजिस्टर_addr reg_addr;
	पूर्ण __packed req;
	/* response */
	काष्ठा अणु
		/* response identअगरier */
		__le16 proc_id;
		/* error */
		uपूर्णांक8_t error;
		/* रेजिस्टर content */
		काष्ठा as10x_रेजिस्टर_value reg_val;
	पूर्ण __packed rsp;
पूर्ण __packed;

जोड़ as10x_cfg_change_mode अणु
	/* request */
	काष्ठा अणु
		/* request identअगरier */
		__le16 proc_id;
		/* mode */
		uपूर्णांक8_t mode;
	पूर्ण __packed req;
	/* response */
	काष्ठा अणु
		/* response identअगरier */
		__le16 proc_id;
		/* error */
		uपूर्णांक8_t error;
	पूर्ण __packed rsp;
पूर्ण __packed;

काष्ठा as10x_cmd_header_t अणु
	__le16 req_id;
	__le16 prog;
	__le16 version;
	__le16 data_len;
पूर्ण __packed;

#घोषणा DUMP_BLOCK_SIZE 16

जोड़ as10x_dump_memory अणु
	/* request */
	काष्ठा अणु
		/* request identअगरier */
		__le16 proc_id;
		/* dump memory type request */
		uपूर्णांक8_t dump_req;
		/* रेजिस्टर description */
		काष्ठा as10x_रेजिस्टर_addr reg_addr;
		/* nb blocks to पढ़ो */
		__le16 num_blocks;
	पूर्ण __packed req;
	/* response */
	काष्ठा अणु
		/* response identअगरier */
		__le16 proc_id;
		/* error */
		uपूर्णांक8_t error;
		/* dump response */
		uपूर्णांक8_t dump_rsp;
		/* data */
		जोड़ अणु
			uपूर्णांक8_t  data8[DUMP_BLOCK_SIZE];
			__le16 data16[DUMP_BLOCK_SIZE / माप(__le16)];
			__le32 data32[DUMP_BLOCK_SIZE / माप(__le32)];
		पूर्ण __packed u;
	पूर्ण __packed rsp;
पूर्ण __packed;

जोड़ as10x_dumplog_memory अणु
	काष्ठा अणु
		/* request identअगरier */
		__le16 proc_id;
		/* dump memory type request */
		uपूर्णांक8_t dump_req;
	पूर्ण __packed req;
	काष्ठा अणु
		/* request identअगरier */
		__le16 proc_id;
		/* error */
		uपूर्णांक8_t error;
		/* dump response */
		uपूर्णांक8_t dump_rsp;
		/* dump data */
		uपूर्णांक8_t data[DUMP_BLOCK_SIZE];
	पूर्ण __packed rsp;
पूर्ण __packed;

जोड़ as10x_raw_data अणु
	/* request */
	काष्ठा अणु
		__le16 proc_id;
		uपूर्णांक8_t data[64 - माप(काष्ठा as10x_cmd_header_t)
			     - 2 /* proc_id */];
	पूर्ण __packed req;
	/* response */
	काष्ठा अणु
		__le16 proc_id;
		uपूर्णांक8_t error;
		uपूर्णांक8_t data[64 - माप(काष्ठा as10x_cmd_header_t)
			     - 2 /* proc_id */ - 1 /* rc */];
	पूर्ण __packed rsp;
पूर्ण __packed;

काष्ठा as10x_cmd_t अणु
	काष्ठा as10x_cmd_header_t header;
	जोड़ अणु
		जोड़ as10x_turn_on		turn_on;
		जोड़ as10x_turn_off		turn_off;
		जोड़ as10x_set_tune		set_tune;
		जोड़ as10x_get_tune_status	get_tune_status;
		जोड़ as10x_get_tps		get_tps;
		जोड़ as10x_common		common;
		जोड़ as10x_add_pid_filter	add_pid_filter;
		जोड़ as10x_del_pid_filter	del_pid_filter;
		जोड़ as10x_start_streaming	start_streaming;
		जोड़ as10x_stop_streaming	stop_streaming;
		जोड़ as10x_get_demod_stats	get_demod_stats;
		जोड़ as10x_get_impulse_resp	get_impulse_rsp;
		जोड़ as10x_fw_context		context;
		जोड़ as10x_set_रेजिस्टर	set_रेजिस्टर;
		जोड़ as10x_get_रेजिस्टर	get_रेजिस्टर;
		जोड़ as10x_cfg_change_mode	cfg_change_mode;
		जोड़ as10x_dump_memory		dump_memory;
		जोड़ as10x_dumplog_memory	dumplog_memory;
		जोड़ as10x_raw_data		raw_data;
	पूर्ण __packed body;
पूर्ण __packed;

काष्ठा as10x_token_cmd_t अणु
	/* token cmd */
	काष्ठा as10x_cmd_t c;
	/* token response */
	काष्ठा as10x_cmd_t r;
पूर्ण __packed;


/**************************/
/* FUNCTION DECLARATION   */
/**************************/

व्योम as10x_cmd_build(काष्ठा as10x_cmd_t *pcmd, uपूर्णांक16_t proc_id,
		      uपूर्णांक16_t cmd_len);
पूर्णांक as10x_rsp_parse(काष्ठा as10x_cmd_t *r, uपूर्णांक16_t proc_id);

/* as10x cmd */
पूर्णांक as10x_cmd_turn_on(काष्ठा as10x_bus_adapter_t *adap);
पूर्णांक as10x_cmd_turn_off(काष्ठा as10x_bus_adapter_t *adap);

पूर्णांक as10x_cmd_set_tune(काष्ठा as10x_bus_adapter_t *adap,
		       काष्ठा as10x_tune_args *ptune);

पूर्णांक as10x_cmd_get_tune_status(काष्ठा as10x_bus_adapter_t *adap,
			      काष्ठा as10x_tune_status *pstatus);

पूर्णांक as10x_cmd_get_tps(काष्ठा as10x_bus_adapter_t *adap,
		      काष्ठा as10x_tps *ptps);

पूर्णांक as10x_cmd_get_demod_stats(काष्ठा as10x_bus_adapter_t  *adap,
			      काष्ठा as10x_demod_stats *pdemod_stats);

पूर्णांक as10x_cmd_get_impulse_resp(काष्ठा as10x_bus_adapter_t *adap,
			       uपूर्णांक8_t *is_पढ़ोy);

/* as10x cmd stream */
पूर्णांक as10x_cmd_add_PID_filter(काष्ठा as10x_bus_adapter_t *adap,
			     काष्ठा as10x_ts_filter *filter);
पूर्णांक as10x_cmd_del_PID_filter(काष्ठा as10x_bus_adapter_t *adap,
			     uपूर्णांक16_t pid_value);

पूर्णांक as10x_cmd_start_streaming(काष्ठा as10x_bus_adapter_t *adap);
पूर्णांक as10x_cmd_stop_streaming(काष्ठा as10x_bus_adapter_t *adap);

/* as10x cmd cfg */
पूर्णांक as10x_cmd_set_context(काष्ठा as10x_bus_adapter_t *adap,
			  uपूर्णांक16_t tag,
			  uपूर्णांक32_t value);
पूर्णांक as10x_cmd_get_context(काष्ठा as10x_bus_adapter_t *adap,
			  uपूर्णांक16_t tag,
			  uपूर्णांक32_t *pvalue);

पूर्णांक as10x_cmd_eLNA_change_mode(काष्ठा as10x_bus_adapter_t *adap, uपूर्णांक8_t mode);
पूर्णांक as10x_context_rsp_parse(काष्ठा as10x_cmd_t *prsp, uपूर्णांक16_t proc_id);
#पूर्ण_अगर
