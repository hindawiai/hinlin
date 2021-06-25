<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2012-2016, The Linux Foundation. All rights reserved.
 * Copyright (C) 2017 Linaro Ltd.
 */
#अगर_अघोषित __HFI_H__
#घोषणा __HFI_H__

#समावेश <linux/पूर्णांकerrupt.h>

#समावेश "hfi_helper.h"

#घोषणा VIDC_SESSION_TYPE_VPE			0
#घोषणा VIDC_SESSION_TYPE_ENC			1
#घोषणा VIDC_SESSION_TYPE_DEC			2

#घोषणा VIDC_RESOURCE_NONE			0
#घोषणा VIDC_RESOURCE_OCMEM			1
#घोषणा VIDC_RESOURCE_VMEM			2

काष्ठा hfi_buffer_desc अणु
	u32 buffer_type;
	u32 buffer_size;
	u32 num_buffers;
	u32 device_addr;
	u32 extradata_addr;
	u32 extradata_size;
	u32 response_required;
पूर्ण;

काष्ठा hfi_frame_data अणु
	u32 buffer_type;
	u32 device_addr;
	u32 extradata_addr;
	u64 बारtamp;
	u32 flags;
	u32 offset;
	u32 alloc_len;
	u32 filled_len;
	u32 mark_target;
	u32 mark_data;
	u32 clnt_data;
	u32 extradata_size;
पूर्ण;

जोड़ hfi_get_property अणु
	काष्ठा hfi_profile_level profile_level;
	काष्ठा hfi_buffer_requirements bufreq[HFI_BUFFER_TYPE_MAX];
पूर्ण;

/* HFI events */
#घोषणा EVT_SYS_EVENT_CHANGE			1
#घोषणा EVT_SYS_WATCHDOG_TIMEOUT		2
#घोषणा EVT_SYS_ERROR				3
#घोषणा EVT_SESSION_ERROR			4

/* HFI event callback काष्ठाure */
काष्ठा hfi_event_data अणु
	u32 error;
	u32 height;
	u32 width;
	u32 event_type;
	u32 packet_buffer;
	u32 extradata_buffer;
	u32 tag;
	u32 profile;
	u32 level;
	/* the following properties start appear from v4 onwards */
	u32 bit_depth;
	u32 pic_काष्ठा;
	u32 colour_space;
	u32 entropy_mode;
	u32 buf_count;
	काष्ठा अणु
		u32 left, top;
		u32 width, height;
	पूर्ण input_crop;
पूर्ण;

/* define core states */
#घोषणा CORE_UNINIT				0
#घोषणा CORE_INIT				1

/* define instance states */
#घोषणा INST_UNINIT				2
#घोषणा INST_INIT				3
#घोषणा INST_LOAD_RESOURCES			4
#घोषणा INST_START				5
#घोषणा INST_STOP				6
#घोषणा INST_RELEASE_RESOURCES			7

काष्ठा venus_core;
काष्ठा venus_inst;

काष्ठा hfi_core_ops अणु
	व्योम (*event_notअगरy)(काष्ठा venus_core *core, u32 event);
पूर्ण;

काष्ठा hfi_inst_ops अणु
	व्योम (*buf_करोne)(काष्ठा venus_inst *inst, अचिन्हित पूर्णांक buf_type,
			 u32 tag, u32 bytesused, u32 data_offset, u32 flags,
			 u32 hfi_flags, u64 बारtamp_us);
	व्योम (*event_notअगरy)(काष्ठा venus_inst *inst, u32 event,
			     काष्ठा hfi_event_data *data);
	व्योम (*flush_करोne)(काष्ठा venus_inst *inst);
पूर्ण;

काष्ठा hfi_ops अणु
	पूर्णांक (*core_init)(काष्ठा venus_core *core);
	पूर्णांक (*core_deinit)(काष्ठा venus_core *core);
	पूर्णांक (*core_ping)(काष्ठा venus_core *core, u32 cookie);
	पूर्णांक (*core_trigger_ssr)(काष्ठा venus_core *core, u32 trigger_type);

	पूर्णांक (*session_init)(काष्ठा venus_inst *inst, u32 session_type,
			    u32 codec);
	पूर्णांक (*session_end)(काष्ठा venus_inst *inst);
	पूर्णांक (*session_पात)(काष्ठा venus_inst *inst);
	पूर्णांक (*session_flush)(काष्ठा venus_inst *inst, u32 flush_mode);
	पूर्णांक (*session_start)(काष्ठा venus_inst *inst);
	पूर्णांक (*session_stop)(काष्ठा venus_inst *inst);
	पूर्णांक (*session_जारी)(काष्ठा venus_inst *inst);
	पूर्णांक (*session_etb)(काष्ठा venus_inst *inst, काष्ठा hfi_frame_data *fd);
	पूर्णांक (*session_ftb)(काष्ठा venus_inst *inst, काष्ठा hfi_frame_data *fd);
	पूर्णांक (*session_set_buffers)(काष्ठा venus_inst *inst,
				   काष्ठा hfi_buffer_desc *bd);
	पूर्णांक (*session_unset_buffers)(काष्ठा venus_inst *inst,
				     काष्ठा hfi_buffer_desc *bd);
	पूर्णांक (*session_load_res)(काष्ठा venus_inst *inst);
	पूर्णांक (*session_release_res)(काष्ठा venus_inst *inst);
	पूर्णांक (*session_parse_seq_hdr)(काष्ठा venus_inst *inst, u32 seq_hdr,
				     u32 seq_hdr_len);
	पूर्णांक (*session_get_seq_hdr)(काष्ठा venus_inst *inst, u32 seq_hdr,
				   u32 seq_hdr_len);
	पूर्णांक (*session_set_property)(काष्ठा venus_inst *inst, u32 ptype,
				    व्योम *pdata);
	पूर्णांक (*session_get_property)(काष्ठा venus_inst *inst, u32 ptype);

	पूर्णांक (*resume)(काष्ठा venus_core *core);
	पूर्णांक (*suspend)(काष्ठा venus_core *core);

	/* पूर्णांकerrupt operations */
	irqवापस_t (*isr)(काष्ठा venus_core *core);
	irqवापस_t (*isr_thपढ़ो)(काष्ठा venus_core *core);
पूर्ण;

पूर्णांक hfi_create(काष्ठा venus_core *core, स्थिर काष्ठा hfi_core_ops *ops);
व्योम hfi_destroy(काष्ठा venus_core *core);
व्योम hfi_reinit(काष्ठा venus_core *core);

पूर्णांक hfi_core_init(काष्ठा venus_core *core);
पूर्णांक hfi_core_deinit(काष्ठा venus_core *core, bool blocking);
पूर्णांक hfi_core_suspend(काष्ठा venus_core *core);
पूर्णांक hfi_core_resume(काष्ठा venus_core *core, bool क्रमce);
पूर्णांक hfi_core_trigger_ssr(काष्ठा venus_core *core, u32 type);
पूर्णांक hfi_core_ping(काष्ठा venus_core *core);
पूर्णांक hfi_session_create(काष्ठा venus_inst *inst, स्थिर काष्ठा hfi_inst_ops *ops);
व्योम hfi_session_destroy(काष्ठा venus_inst *inst);
पूर्णांक hfi_session_init(काष्ठा venus_inst *inst, u32 pixfmt);
पूर्णांक hfi_session_deinit(काष्ठा venus_inst *inst);
पूर्णांक hfi_session_start(काष्ठा venus_inst *inst);
पूर्णांक hfi_session_stop(काष्ठा venus_inst *inst);
पूर्णांक hfi_session_जारी(काष्ठा venus_inst *inst);
पूर्णांक hfi_session_पात(काष्ठा venus_inst *inst);
पूर्णांक hfi_session_load_res(काष्ठा venus_inst *inst);
पूर्णांक hfi_session_unload_res(काष्ठा venus_inst *inst);
पूर्णांक hfi_session_flush(काष्ठा venus_inst *inst, u32 type, bool block);
पूर्णांक hfi_session_set_buffers(काष्ठा venus_inst *inst,
			    काष्ठा hfi_buffer_desc *bd);
पूर्णांक hfi_session_unset_buffers(काष्ठा venus_inst *inst,
			      काष्ठा hfi_buffer_desc *bd);
पूर्णांक hfi_session_get_property(काष्ठा venus_inst *inst, u32 ptype,
			     जोड़ hfi_get_property *hprop);
पूर्णांक hfi_session_set_property(काष्ठा venus_inst *inst, u32 ptype, व्योम *pdata);
पूर्णांक hfi_session_process_buf(काष्ठा venus_inst *inst, काष्ठा hfi_frame_data *f);
irqवापस_t hfi_isr_thपढ़ो(पूर्णांक irq, व्योम *dev_id);
irqवापस_t hfi_isr(पूर्णांक irq, व्योम *dev);

#पूर्ण_अगर
