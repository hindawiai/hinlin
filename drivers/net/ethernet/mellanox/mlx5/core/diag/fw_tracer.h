<शैली गुरु>
/*
 * Copyright (c) 2018, Mellanox Technologies. All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary क्रमms, with or
 *     without modअगरication, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary क्रमm must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the करोcumentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#अगर_अघोषित __LIB_TRACER_H__
#घोषणा __LIB_TRACER_H__

#समावेश <linux/mlx5/driver.h>
#समावेश "mlx5_core.h"

#घोषणा STRINGS_DB_SECTIONS_NUM 8
#घोषणा STRINGS_DB_READ_SIZE_BYTES 256
#घोषणा STRINGS_DB_LEFTOVER_SIZE_BYTES 64
#घोषणा TRACER_BUFFER_PAGE_NUM 64
#घोषणा TRACER_BUFFER_CHUNK 4096
#घोषणा TRACE_BUFFER_SIZE_BYTE (TRACER_BUFFER_PAGE_NUM * TRACER_BUFFER_CHUNK)

#घोषणा TRACER_BLOCK_SIZE_BYTE 256
#घोषणा TRACES_PER_BLOCK 32

#घोषणा TRACE_STR_MSG 256
#घोषणा SAVED_TRACES_NUM 8192

#घोषणा TRACER_MAX_PARAMS 7
#घोषणा MESSAGE_HASH_BITS 6
#घोषणा MESSAGE_HASH_SIZE BIT(MESSAGE_HASH_BITS)

#घोषणा MASK_52_7 (0x1FFFFFFFFFFF80)
#घोषणा MASK_6_0  (0x7F)

काष्ठा mlx5_fw_trace_data अणु
	u64 बारtamp;
	bool lost;
	u8 event_id;
	अक्षर msg[TRACE_STR_MSG];
पूर्ण;

काष्ठा mlx5_fw_tracer अणु
	काष्ठा mlx5_core_dev *dev;
	काष्ठा mlx5_nb        nb;
	bool owner;
	u8   trc_ver;
	काष्ठा workqueue_काष्ठा *work_queue;
	काष्ठा work_काष्ठा ownership_change_work;
	काष्ठा work_काष्ठा पढ़ो_fw_strings_work;

	/* Strings DB */
	काष्ठा अणु
		u8 first_string_trace;
		u8 num_string_trace;
		u32 num_string_db;
		u32 base_address_out[STRINGS_DB_SECTIONS_NUM];
		u32 size_out[STRINGS_DB_SECTIONS_NUM];
		व्योम *buffer[STRINGS_DB_SECTIONS_NUM];
		bool loaded;
	पूर्ण str_db;

	/* Log Buffer */
	काष्ठा अणु
		u32 pdn;
		व्योम *log_buf;
		dma_addr_t dma;
		u32 size;
		काष्ठा mlx5_core_mkey mkey;
		u32 consumer_index;
	पूर्ण buff;

	/* Saved Traces Array */
	काष्ठा अणु
		काष्ठा mlx5_fw_trace_data straces[SAVED_TRACES_NUM];
		u32 saved_traces_index;
		काष्ठा mutex lock; /* Protect st_arr access */
	पूर्ण st_arr;

	u64 last_बारtamp;
	काष्ठा work_काष्ठा handle_traces_work;
	काष्ठा hlist_head hash[MESSAGE_HASH_SIZE];
	काष्ठा list_head पढ़ोy_strings_list;
पूर्ण;

काष्ठा tracer_string_क्रमmat अणु
	अक्षर *string;
	पूर्णांक params[TRACER_MAX_PARAMS];
	पूर्णांक num_of_params;
	पूर्णांक last_param_num;
	u8 event_id;
	u32 पंचांगsn;
	काष्ठा hlist_node hlist;
	काष्ठा list_head list;
	u32 बारtamp;
	bool lost;
पूर्ण;

क्रमागत mlx5_fw_tracer_ownership_state अणु
	MLX5_FW_TRACER_RELEASE_OWNERSHIP,
	MLX5_FW_TRACER_ACQUIRE_OWNERSHIP,
पूर्ण;

क्रमागत tracer_ctrl_fields_select अणु
	TRACE_STATUS = 1 << 0,
पूर्ण;

क्रमागत tracer_event_type अणु
	TRACER_EVENT_TYPE_STRING,
	TRACER_EVENT_TYPE_TIMESTAMP = 0xFF,
	TRACER_EVENT_TYPE_UNRECOGNIZED,
पूर्ण;

क्रमागत tracing_mode अणु
	TRACE_TO_MEMORY = 1 << 0,
पूर्ण;

काष्ठा tracer_बारtamp_event अणु
	u64        बारtamp;
	u8         unreliable;
पूर्ण;

काष्ठा tracer_string_event अणु
	u32        बारtamp;
	u32        पंचांगsn;
	u32        tdsn;
	u32        string_param;
पूर्ण;

काष्ठा tracer_event अणु
	bool      lost_event;
	u32       type;
	u8        event_id;
	जोड़ अणु
		काष्ठा tracer_string_event string_event;
		काष्ठा tracer_बारtamp_event बारtamp_event;
	पूर्ण;
पूर्ण;

काष्ठा mlx5_अगरc_tracer_event_bits अणु
	u8         lost[0x1];
	u8         बारtamp[0x7];
	u8         event_id[0x8];
	u8         event_data[0x30];
पूर्ण;

काष्ठा mlx5_अगरc_tracer_string_event_bits अणु
	u8         lost[0x1];
	u8         बारtamp[0x7];
	u8         event_id[0x8];
	u8         पंचांगsn[0xd];
	u8         tdsn[0x3];
	u8         string_param[0x20];
पूर्ण;

काष्ठा mlx5_अगरc_tracer_बारtamp_event_bits अणु
	u8         बारtamp7_0[0x8];
	u8         event_id[0x8];
	u8         urts[0x3];
	u8         बारtamp52_40[0xd];
	u8         बारtamp39_8[0x20];
पूर्ण;

काष्ठा mlx5_fw_tracer *mlx5_fw_tracer_create(काष्ठा mlx5_core_dev *dev);
पूर्णांक mlx5_fw_tracer_init(काष्ठा mlx5_fw_tracer *tracer);
व्योम mlx5_fw_tracer_cleanup(काष्ठा mlx5_fw_tracer *tracer);
व्योम mlx5_fw_tracer_destroy(काष्ठा mlx5_fw_tracer *tracer);
पूर्णांक mlx5_fw_tracer_trigger_core_dump_general(काष्ठा mlx5_core_dev *dev);
पूर्णांक mlx5_fw_tracer_get_saved_traces_objects(काष्ठा mlx5_fw_tracer *tracer,
					    काष्ठा devlink_fmsg *fmsg);
पूर्णांक mlx5_fw_tracer_reload(काष्ठा mlx5_fw_tracer *tracer);

#पूर्ण_अगर
