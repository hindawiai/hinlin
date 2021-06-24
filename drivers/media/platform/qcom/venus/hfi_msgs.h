<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2012-2016, The Linux Foundation. All rights reserved.
 * Copyright (C) 2017 Linaro Ltd.
 */
#अगर_अघोषित __VENUS_HFI_MSGS_H__
#घोषणा __VENUS_HFI_MSGS_H__

/* message calls */
#घोषणा HFI_MSG_SYS_INIT			0x20001
#घोषणा HFI_MSG_SYS_PC_PREP			0x20002
#घोषणा HFI_MSG_SYS_RELEASE_RESOURCE		0x20003
#घोषणा HFI_MSG_SYS_DEBUG			0x20004
#घोषणा HFI_MSG_SYS_SESSION_INIT		0x20006
#घोषणा HFI_MSG_SYS_SESSION_END			0x20007
#घोषणा HFI_MSG_SYS_IDLE			0x20008
#घोषणा HFI_MSG_SYS_COV				0x20009
#घोषणा HFI_MSG_SYS_PROPERTY_INFO		0x2000a

#घोषणा HFI_MSG_EVENT_NOTIFY			0x21001
#घोषणा HFI_MSG_SESSION_GET_SEQUENCE_HEADER	0x21002

#घोषणा HFI_MSG_SYS_PING_ACK			0x220002
#घोषणा HFI_MSG_SYS_SESSION_ABORT		0x220004

#घोषणा HFI_MSG_SESSION_LOAD_RESOURCES		0x221001
#घोषणा HFI_MSG_SESSION_START			0x221002
#घोषणा HFI_MSG_SESSION_STOP			0x221003
#घोषणा HFI_MSG_SESSION_SUSPEND			0x221004
#घोषणा HFI_MSG_SESSION_RESUME			0x221005
#घोषणा HFI_MSG_SESSION_FLUSH			0x221006
#घोषणा HFI_MSG_SESSION_EMPTY_BUFFER		0x221007
#घोषणा HFI_MSG_SESSION_FILL_BUFFER		0x221008
#घोषणा HFI_MSG_SESSION_PROPERTY_INFO		0x221009
#घोषणा HFI_MSG_SESSION_RELEASE_RESOURCES	0x22100a
#घोषणा HFI_MSG_SESSION_PARSE_SEQUENCE_HEADER	0x22100b
#घोषणा HFI_MSG_SESSION_RELEASE_BUFFERS		0x22100c

#घोषणा HFI_PICTURE_I				0x00000001
#घोषणा HFI_PICTURE_P				0x00000002
#घोषणा HFI_PICTURE_B				0x00000004
#घोषणा HFI_PICTURE_IDR				0x00000008
#घोषणा HFI_FRAME_NOTCODED			0x7f002000
#घोषणा HFI_FRAME_YUV				0x7f004000
#घोषणा HFI_UNUSED_PICT				0x10000000

/* message packets */
काष्ठा hfi_msg_event_notअगरy_pkt अणु
	काष्ठा hfi_session_hdr_pkt shdr;
	u32 event_id;
	u32 event_data1;
	u32 event_data2;
	u32 ext_event_data[1];
पूर्ण;

काष्ठा hfi_msg_event_release_buffer_ref_pkt अणु
	u32 packet_buffer;
	u32 extradata_buffer;
	u32 output_tag;
पूर्ण;

काष्ठा hfi_msg_sys_init_करोne_pkt अणु
	काष्ठा hfi_pkt_hdr hdr;
	u32 error_type;
	u32 num_properties;
	u32 data[1];
पूर्ण;

काष्ठा hfi_msg_sys_pc_prep_करोne_pkt अणु
	काष्ठा hfi_pkt_hdr hdr;
	u32 error_type;
पूर्ण;

काष्ठा hfi_msg_sys_release_resource_करोne_pkt अणु
	काष्ठा hfi_pkt_hdr hdr;
	u32 resource_handle;
	u32 error_type;
पूर्ण;

काष्ठा hfi_msg_session_init_करोne_pkt अणु
	काष्ठा hfi_session_hdr_pkt shdr;
	u32 error_type;
	u32 num_properties;
	u32 data[1];
पूर्ण;

काष्ठा hfi_msg_session_end_करोne_pkt अणु
	काष्ठा hfi_session_hdr_pkt shdr;
	u32 error_type;
पूर्ण;

काष्ठा hfi_msg_session_get_sequence_hdr_करोne_pkt अणु
	काष्ठा hfi_session_hdr_pkt shdr;
	u32 error_type;
	u32 header_len;
	u32 sequence_header;
पूर्ण;

काष्ठा hfi_msg_sys_session_पात_करोne_pkt अणु
	काष्ठा hfi_session_hdr_pkt shdr;
	u32 error_type;
पूर्ण;

काष्ठा hfi_msg_sys_idle_pkt अणु
	काष्ठा hfi_pkt_hdr hdr;
पूर्ण;

काष्ठा hfi_msg_sys_ping_ack_pkt अणु
	काष्ठा hfi_pkt_hdr hdr;
	u32 client_data;
पूर्ण;

काष्ठा hfi_msg_sys_property_info_pkt अणु
	काष्ठा hfi_pkt_hdr hdr;
	u32 num_properties;
	u32 data[1];
पूर्ण;

काष्ठा hfi_msg_session_load_resources_करोne_pkt अणु
	काष्ठा hfi_session_hdr_pkt shdr;
	u32 error_type;
पूर्ण;

काष्ठा hfi_msg_session_start_करोne_pkt अणु
	काष्ठा hfi_session_hdr_pkt shdr;
	u32 error_type;
पूर्ण;

काष्ठा hfi_msg_session_stop_करोne_pkt अणु
	काष्ठा hfi_session_hdr_pkt shdr;
	u32 error_type;
पूर्ण;

काष्ठा hfi_msg_session_suspend_करोne_pkt अणु
	काष्ठा hfi_session_hdr_pkt shdr;
	u32 error_type;
पूर्ण;

काष्ठा hfi_msg_session_resume_करोne_pkt अणु
	काष्ठा hfi_session_hdr_pkt shdr;
	u32 error_type;
पूर्ण;

काष्ठा hfi_msg_session_flush_करोne_pkt अणु
	काष्ठा hfi_session_hdr_pkt shdr;
	u32 error_type;
	u32 flush_type;
पूर्ण;

काष्ठा hfi_msg_session_empty_buffer_करोne_pkt अणु
	काष्ठा hfi_session_hdr_pkt shdr;
	u32 error_type;
	u32 offset;
	u32 filled_len;
	u32 input_tag;
	u32 packet_buffer;
	u32 extradata_buffer;
	u32 data[];
पूर्ण;

काष्ठा hfi_msg_session_fbd_compressed_pkt अणु
	काष्ठा hfi_session_hdr_pkt shdr;
	u32 समय_stamp_hi;
	u32 समय_stamp_lo;
	u32 error_type;
	u32 flags;
	u32 mark_target;
	u32 mark_data;
	u32 stats;
	u32 offset;
	u32 alloc_len;
	u32 filled_len;
	u32 input_tag;
	u32 output_tag;
	u32 picture_type;
	u32 packet_buffer;
	u32 extradata_buffer;
	u32 data[];
पूर्ण;

काष्ठा hfi_msg_session_fbd_uncompressed_plane0_pkt अणु
	काष्ठा hfi_session_hdr_pkt shdr;
	u32 stream_id;
	u32 view_id;
	u32 error_type;
	u32 समय_stamp_hi;
	u32 समय_stamp_lo;
	u32 flags;
	u32 mark_target;
	u32 mark_data;
	u32 stats;
	u32 alloc_len;
	u32 filled_len;
	u32 offset;
	u32 frame_width;
	u32 frame_height;
	u32 start_x_coord;
	u32 start_y_coord;
	u32 input_tag;
	u32 input_tag2;
	u32 output_tag;
	u32 picture_type;
	u32 packet_buffer;
	u32 extradata_buffer;
	u32 data[];
पूर्ण;

काष्ठा hfi_msg_session_fbd_uncompressed_plane1_pkt अणु
	u32 flags;
	u32 alloc_len;
	u32 filled_len;
	u32 offset;
	u32 packet_buffer2;
	u32 data[];
पूर्ण;

काष्ठा hfi_msg_session_fbd_uncompressed_plane2_pkt अणु
	u32 flags;
	u32 alloc_len;
	u32 filled_len;
	u32 offset;
	u32 packet_buffer3;
	u32 data[];
पूर्ण;

काष्ठा hfi_msg_session_parse_sequence_header_करोne_pkt अणु
	काष्ठा hfi_session_hdr_pkt shdr;
	u32 error_type;
	u32 num_properties;
	u32 data[1];
पूर्ण;

काष्ठा hfi_msg_session_property_info_pkt अणु
	काष्ठा hfi_session_hdr_pkt shdr;
	u32 num_properties;
	u32 data[1];
पूर्ण;

काष्ठा hfi_msg_session_release_resources_करोne_pkt अणु
	काष्ठा hfi_session_hdr_pkt shdr;
	u32 error_type;
पूर्ण;

काष्ठा hfi_msg_session_release_buffers_करोne_pkt अणु
	काष्ठा hfi_session_hdr_pkt shdr;
	u32 error_type;
	u32 num_buffers;
	u32 buffer_info[1];
पूर्ण;

काष्ठा hfi_msg_sys_debug_pkt अणु
	काष्ठा hfi_pkt_hdr hdr;
	u32 msg_type;
	u32 msg_size;
	u32 समय_stamp_hi;
	u32 समय_stamp_lo;
	u8 msg_data[1];
पूर्ण;

काष्ठा hfi_msg_sys_coverage_pkt अणु
	काष्ठा hfi_pkt_hdr hdr;
	u32 msg_size;
	u32 समय_stamp_hi;
	u32 समय_stamp_lo;
	u8 msg_data[1];
पूर्ण;

काष्ठा venus_core;
काष्ठा hfi_pkt_hdr;

व्योम hfi_process_watchकरोg_समयout(काष्ठा venus_core *core);
u32 hfi_process_msg_packet(काष्ठा venus_core *core, काष्ठा hfi_pkt_hdr *hdr);

#पूर्ण_अगर
