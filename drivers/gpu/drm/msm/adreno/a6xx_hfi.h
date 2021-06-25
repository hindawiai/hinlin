<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright (c) 2017 The Linux Foundation. All rights reserved. */

#अगर_अघोषित _A6XX_HFI_H_
#घोषणा _A6XX_HFI_H_

काष्ठा a6xx_hfi_queue_table_header अणु
	u32 version;
	u32 size;		/* Size of the queue table in dwords */
	u32 qhdr0_offset;	/* Offset of the first queue header */
	u32 qhdr_size;		/* Size of the queue headers */
	u32 num_queues;		/* Number of total queues */
	u32 active_queues;	/* Number of active queues */
पूर्ण;

काष्ठा a6xx_hfi_queue_header अणु
	u32 status;
	u32 iova;
	u32 type;
	u32 size;
	u32 msg_size;
	u32 dropped;
	u32 rx_watermark;
	u32 tx_watermark;
	u32 rx_request;
	u32 tx_request;
	u32 पढ़ो_index;
	u32 ग_लिखो_index;
पूर्ण;

काष्ठा a6xx_hfi_queue अणु
	काष्ठा a6xx_hfi_queue_header *header;
	spinlock_t lock;
	u32 *data;
	atomic_t seqnum;
पूर्ण;

/* This is the outgoing queue to the GMU */
#घोषणा HFI_COMMAND_QUEUE 0

/* THis is the incoming response queue from the GMU */
#घोषणा HFI_RESPONSE_QUEUE 1

#घोषणा HFI_HEADER_ID(msg) ((msg) & 0xff)
#घोषणा HFI_HEADER_SIZE(msg) (((msg) >> 8) & 0xff)
#घोषणा HFI_HEADER_SEQNUM(msg) (((msg) >> 20) & 0xfff)

/* FIXME: Do we need this or can we use ARRAY_SIZE? */
#घोषणा HFI_RESPONSE_PAYLOAD_SIZE 16

/* HFI message types */

#घोषणा HFI_MSG_CMD 0
#घोषणा HFI_MSG_ACK 1
#घोषणा HFI_MSG_ACK_V1 2

#घोषणा HFI_F2H_MSG_ACK 126

काष्ठा a6xx_hfi_msg_response अणु
	u32 header;
	u32 ret_header;
	u32 error;
	u32 payload[HFI_RESPONSE_PAYLOAD_SIZE];
पूर्ण;

#घोषणा HFI_F2H_MSG_ERROR 100

काष्ठा a6xx_hfi_msg_error अणु
	u32 header;
	u32 code;
	u32 payload[2];
पूर्ण;

#घोषणा HFI_H2F_MSG_INIT 0

काष्ठा a6xx_hfi_msg_gmu_init_cmd अणु
	u32 header;
	u32 seg_id;
	u32 dbg_buffer_addr;
	u32 dbg_buffer_size;
	u32 boot_state;
पूर्ण;

#घोषणा HFI_H2F_MSG_FW_VERSION 1

काष्ठा a6xx_hfi_msg_fw_version अणु
	u32 header;
	u32 supported_version;
पूर्ण;

#घोषणा HFI_H2F_MSG_PERF_TABLE 4

काष्ठा perf_level अणु
	u32 vote;
	u32 freq;
पूर्ण;

काष्ठा perf_gx_level अणु
	u32 vote;
	u32 acd;
	u32 freq;
पूर्ण;

काष्ठा a6xx_hfi_msg_perf_table_v1 अणु
	u32 header;
	u32 num_gpu_levels;
	u32 num_gmu_levels;

	काष्ठा perf_level gx_votes[16];
	काष्ठा perf_level cx_votes[4];
पूर्ण;

काष्ठा a6xx_hfi_msg_perf_table अणु
	u32 header;
	u32 num_gpu_levels;
	u32 num_gmu_levels;

	काष्ठा perf_gx_level gx_votes[16];
	काष्ठा perf_level cx_votes[4];
पूर्ण;

#घोषणा HFI_H2F_MSG_BW_TABLE 3

काष्ठा a6xx_hfi_msg_bw_table अणु
	u32 header;
	u32 bw_level_num;
	u32 cnoc_cmds_num;
	u32 ddr_cmds_num;
	u32 cnoc_रुको_biपंचांगask;
	u32 ddr_रुको_biपंचांगask;
	u32 cnoc_cmds_addrs[6];
	u32 cnoc_cmds_data[2][6];
	u32 ddr_cmds_addrs[8];
	u32 ddr_cmds_data[16][8];
पूर्ण;

#घोषणा HFI_H2F_MSG_TEST 5

काष्ठा a6xx_hfi_msg_test अणु
	u32 header;
पूर्ण;

#घोषणा HFI_H2F_MSG_START 10

काष्ठा a6xx_hfi_msg_start अणु
	u32 header;
पूर्ण;

#घोषणा HFI_H2F_MSG_CORE_FW_START 14

काष्ठा a6xx_hfi_msg_core_fw_start अणु
	u32 header;
	u32 handle;
पूर्ण;

#घोषणा HFI_H2F_MSG_GX_BW_PERF_VOTE 30

काष्ठा a6xx_hfi_gx_bw_perf_vote_cmd अणु
	u32 header;
	u32 ack_type;
	u32 freq;
	u32 bw;
पूर्ण;

#घोषणा HFI_H2F_MSG_PREPARE_SLUMBER 33

काष्ठा a6xx_hfi_prep_slumber_cmd अणु
	u32 header;
	u32 bw;
	u32 freq;
पूर्ण;

#पूर्ण_अगर
