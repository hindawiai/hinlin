<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2012-2016, The Linux Foundation. All rights reserved.
 * Copyright (C) 2017 Linaro Ltd.
 */
#अगर_अघोषित __VENUS_HFI_CMDS_H__
#घोषणा __VENUS_HFI_CMDS_H__

#समावेश "hfi.h"

/* commands */
#घोषणा HFI_CMD_SYS_INIT			0x10001
#घोषणा HFI_CMD_SYS_PC_PREP			0x10002
#घोषणा HFI_CMD_SYS_SET_RESOURCE		0x10003
#घोषणा HFI_CMD_SYS_RELEASE_RESOURCE		0x10004
#घोषणा HFI_CMD_SYS_SET_PROPERTY		0x10005
#घोषणा HFI_CMD_SYS_GET_PROPERTY		0x10006
#घोषणा HFI_CMD_SYS_SESSION_INIT		0x10007
#घोषणा HFI_CMD_SYS_SESSION_END			0x10008
#घोषणा HFI_CMD_SYS_SET_BUFFERS			0x10009
#घोषणा HFI_CMD_SYS_TEST_SSR			0x10101

#घोषणा HFI_CMD_SESSION_SET_PROPERTY		0x11001
#घोषणा HFI_CMD_SESSION_SET_BUFFERS		0x11002
#घोषणा HFI_CMD_SESSION_GET_SEQUENCE_HEADER	0x11003

#घोषणा HFI_CMD_SYS_SESSION_ABORT		0x210001
#घोषणा HFI_CMD_SYS_PING			0x210002

#घोषणा HFI_CMD_SESSION_LOAD_RESOURCES		0x211001
#घोषणा HFI_CMD_SESSION_START			0x211002
#घोषणा HFI_CMD_SESSION_STOP			0x211003
#घोषणा HFI_CMD_SESSION_EMPTY_BUFFER		0x211004
#घोषणा HFI_CMD_SESSION_FILL_BUFFER		0x211005
#घोषणा HFI_CMD_SESSION_SUSPEND			0x211006
#घोषणा HFI_CMD_SESSION_RESUME			0x211007
#घोषणा HFI_CMD_SESSION_FLUSH			0x211008
#घोषणा HFI_CMD_SESSION_GET_PROPERTY		0x211009
#घोषणा HFI_CMD_SESSION_PARSE_SEQUENCE_HEADER	0x21100a
#घोषणा HFI_CMD_SESSION_RELEASE_BUFFERS		0x21100b
#घोषणा HFI_CMD_SESSION_RELEASE_RESOURCES	0x21100c
#घोषणा HFI_CMD_SESSION_CONTINUE		0x21100d
#घोषणा HFI_CMD_SESSION_SYNC			0x21100e

/* command packets */
काष्ठा hfi_sys_init_pkt अणु
	काष्ठा hfi_pkt_hdr hdr;
	u32 arch_type;
पूर्ण;

काष्ठा hfi_sys_pc_prep_pkt अणु
	काष्ठा hfi_pkt_hdr hdr;
पूर्ण;

काष्ठा hfi_sys_set_resource_pkt अणु
	काष्ठा hfi_pkt_hdr hdr;
	u32 resource_handle;
	u32 resource_type;
	u32 resource_data[1];
पूर्ण;

काष्ठा hfi_sys_release_resource_pkt अणु
	काष्ठा hfi_pkt_hdr hdr;
	u32 resource_type;
	u32 resource_handle;
पूर्ण;

काष्ठा hfi_sys_set_property_pkt अणु
	काष्ठा hfi_pkt_hdr hdr;
	u32 num_properties;
	u32 data[1];
पूर्ण;

काष्ठा hfi_sys_get_property_pkt अणु
	काष्ठा hfi_pkt_hdr hdr;
	u32 num_properties;
	u32 data[1];
पूर्ण;

काष्ठा hfi_sys_set_buffers_pkt अणु
	काष्ठा hfi_pkt_hdr hdr;
	u32 buffer_type;
	u32 buffer_size;
	u32 num_buffers;
	u32 buffer_addr[1];
पूर्ण;

काष्ठा hfi_sys_ping_pkt अणु
	काष्ठा hfi_pkt_hdr hdr;
	u32 client_data;
पूर्ण;

काष्ठा hfi_session_init_pkt अणु
	काष्ठा hfi_session_hdr_pkt shdr;
	u32 session_करोमुख्य;
	u32 session_codec;
पूर्ण;

काष्ठा hfi_session_end_pkt अणु
	काष्ठा hfi_session_hdr_pkt shdr;
पूर्ण;

काष्ठा hfi_session_पात_pkt अणु
	काष्ठा hfi_session_hdr_pkt shdr;
पूर्ण;

काष्ठा hfi_session_set_property_pkt अणु
	काष्ठा hfi_session_hdr_pkt shdr;
	u32 num_properties;
	u32 data[];
पूर्ण;

काष्ठा hfi_session_set_buffers_pkt अणु
	काष्ठा hfi_session_hdr_pkt shdr;
	u32 buffer_type;
	u32 buffer_size;
	u32 extradata_size;
	u32 min_buffer_size;
	u32 num_buffers;
	u32 buffer_info[1];
पूर्ण;

काष्ठा hfi_session_get_sequence_header_pkt अणु
	काष्ठा hfi_session_hdr_pkt shdr;
	u32 buffer_len;
	u32 packet_buffer;
पूर्ण;

काष्ठा hfi_session_load_resources_pkt अणु
	काष्ठा hfi_session_hdr_pkt shdr;
पूर्ण;

काष्ठा hfi_session_start_pkt अणु
	काष्ठा hfi_session_hdr_pkt shdr;
पूर्ण;

काष्ठा hfi_session_stop_pkt अणु
	काष्ठा hfi_session_hdr_pkt shdr;
पूर्ण;

काष्ठा hfi_session_empty_buffer_compressed_pkt अणु
	काष्ठा hfi_session_hdr_pkt shdr;
	u32 समय_stamp_hi;
	u32 समय_stamp_lo;
	u32 flags;
	u32 mark_target;
	u32 mark_data;
	u32 offset;
	u32 alloc_len;
	u32 filled_len;
	u32 input_tag;
	u32 packet_buffer;
	u32 extradata_buffer;
	u32 data[1];
पूर्ण;

काष्ठा hfi_session_empty_buffer_uncompressed_plane0_pkt अणु
	काष्ठा hfi_session_hdr_pkt shdr;
	u32 view_id;
	u32 समय_stamp_hi;
	u32 समय_stamp_lo;
	u32 flags;
	u32 mark_target;
	u32 mark_data;
	u32 alloc_len;
	u32 filled_len;
	u32 offset;
	u32 input_tag;
	u32 packet_buffer;
	u32 extradata_buffer;
	u32 data[1];
पूर्ण;

काष्ठा hfi_session_empty_buffer_uncompressed_plane1_pkt अणु
	u32 flags;
	u32 alloc_len;
	u32 filled_len;
	u32 offset;
	u32 packet_buffer2;
	u32 data[1];
पूर्ण;

काष्ठा hfi_session_empty_buffer_uncompressed_plane2_pkt अणु
	u32 flags;
	u32 alloc_len;
	u32 filled_len;
	u32 offset;
	u32 packet_buffer3;
	u32 data[1];
पूर्ण;

काष्ठा hfi_session_fill_buffer_pkt अणु
	काष्ठा hfi_session_hdr_pkt shdr;
	u32 stream_id;
	u32 offset;
	u32 alloc_len;
	u32 filled_len;
	u32 output_tag;
	u32 packet_buffer;
	u32 extradata_buffer;
	u32 data[1];
पूर्ण;

काष्ठा hfi_session_flush_pkt अणु
	काष्ठा hfi_session_hdr_pkt shdr;
	u32 flush_type;
पूर्ण;

काष्ठा hfi_session_suspend_pkt अणु
	काष्ठा hfi_session_hdr_pkt shdr;
पूर्ण;

काष्ठा hfi_session_resume_pkt अणु
	काष्ठा hfi_session_hdr_pkt shdr;
पूर्ण;

काष्ठा hfi_session_get_property_pkt अणु
	काष्ठा hfi_session_hdr_pkt shdr;
	u32 num_properties;
	u32 data[1];
पूर्ण;

काष्ठा hfi_session_release_buffer_pkt अणु
	काष्ठा hfi_session_hdr_pkt shdr;
	u32 buffer_type;
	u32 buffer_size;
	u32 extradata_size;
	u32 response_req;
	u32 num_buffers;
	u32 buffer_info[1];
पूर्ण;

काष्ठा hfi_session_release_resources_pkt अणु
	काष्ठा hfi_session_hdr_pkt shdr;
पूर्ण;

काष्ठा hfi_session_parse_sequence_header_pkt अणु
	काष्ठा hfi_session_hdr_pkt shdr;
	u32 header_len;
	u32 packet_buffer;
पूर्ण;

काष्ठा hfi_sfr अणु
	u32 buf_size;
	u8 data[1];
पूर्ण;

काष्ठा hfi_sys_test_ssr_pkt अणु
	काष्ठा hfi_pkt_hdr hdr;
	u32 trigger_type;
पूर्ण;

व्योम pkt_set_version(क्रमागत hfi_version version);

व्योम pkt_sys_init(काष्ठा hfi_sys_init_pkt *pkt, u32 arch_type);
व्योम pkt_sys_pc_prep(काष्ठा hfi_sys_pc_prep_pkt *pkt);
व्योम pkt_sys_idle_indicator(काष्ठा hfi_sys_set_property_pkt *pkt, u32 enable);
व्योम pkt_sys_घातer_control(काष्ठा hfi_sys_set_property_pkt *pkt, u32 enable);
पूर्णांक pkt_sys_set_resource(काष्ठा hfi_sys_set_resource_pkt *pkt, u32 id, u32 size,
			 u32 addr, व्योम *cookie);
पूर्णांक pkt_sys_unset_resource(काष्ठा hfi_sys_release_resource_pkt *pkt, u32 id,
			   u32 size, व्योम *cookie);
व्योम pkt_sys_debug_config(काष्ठा hfi_sys_set_property_pkt *pkt, u32 mode,
			  u32 config);
व्योम pkt_sys_coverage_config(काष्ठा hfi_sys_set_property_pkt *pkt, u32 mode);
व्योम pkt_sys_ping(काष्ठा hfi_sys_ping_pkt *pkt, u32 cookie);
व्योम pkt_sys_image_version(काष्ठा hfi_sys_get_property_pkt *pkt);
पूर्णांक pkt_sys_ssr_cmd(काष्ठा hfi_sys_test_ssr_pkt *pkt, u32 trigger_type);
पूर्णांक pkt_session_init(काष्ठा hfi_session_init_pkt *pkt, व्योम *cookie,
		     u32 session_type, u32 codec);
व्योम pkt_session_cmd(काष्ठा hfi_session_pkt *pkt, u32 pkt_type, व्योम *cookie);
पूर्णांक pkt_session_set_buffers(काष्ठा hfi_session_set_buffers_pkt *pkt,
			    व्योम *cookie, काष्ठा hfi_buffer_desc *bd);
पूर्णांक pkt_session_unset_buffers(काष्ठा hfi_session_release_buffer_pkt *pkt,
			      व्योम *cookie, काष्ठा hfi_buffer_desc *bd);
पूर्णांक pkt_session_etb_decoder(काष्ठा hfi_session_empty_buffer_compressed_pkt *pkt,
			    व्योम *cookie, काष्ठा hfi_frame_data *input_frame);
पूर्णांक pkt_session_etb_encoder(
		काष्ठा hfi_session_empty_buffer_uncompressed_plane0_pkt *pkt,
		व्योम *cookie, काष्ठा hfi_frame_data *input_frame);
पूर्णांक pkt_session_ftb(काष्ठा hfi_session_fill_buffer_pkt *pkt,
		    व्योम *cookie, काष्ठा hfi_frame_data *output_frame);
पूर्णांक pkt_session_parse_seq_header(
		काष्ठा hfi_session_parse_sequence_header_pkt *pkt,
		व्योम *cookie, u32 seq_hdr, u32 seq_hdr_len);
पूर्णांक pkt_session_get_seq_hdr(काष्ठा hfi_session_get_sequence_header_pkt *pkt,
			    व्योम *cookie, u32 seq_hdr, u32 seq_hdr_len);
पूर्णांक pkt_session_flush(काष्ठा hfi_session_flush_pkt *pkt, व्योम *cookie,
		      u32 flush_mode);
पूर्णांक pkt_session_get_property(काष्ठा hfi_session_get_property_pkt *pkt,
			     व्योम *cookie, u32 ptype);
पूर्णांक pkt_session_set_property(काष्ठा hfi_session_set_property_pkt *pkt,
			     व्योम *cookie, u32 ptype, व्योम *pdata);

#पूर्ण_अगर
