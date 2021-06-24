<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Intel SKL IPC Support
 *
 * Copyright (C) 2014-15, Intel Corporation.
 */

#अगर_अघोषित __SKL_IPC_H
#घोषणा __SKL_IPC_H

#समावेश <linux/irqवापस.h>
#समावेश "../common/sst-ipc.h"
#समावेश "skl-sst-dsp.h"

काष्ठा sst_dsp;
काष्ठा sst_generic_ipc;

क्रमागत skl_ipc_pipeline_state अणु
	PPL_INVALID_STATE =	0,
	PPL_UNINITIALIZED =	1,
	PPL_RESET =		2,
	PPL_PAUSED =		3,
	PPL_RUNNING =		4,
	PPL_ERROR_STOP =	5,
	PPL_SAVED =		6,
	PPL_RESTORED =		7
पूर्ण;

काष्ठा skl_ipc_dxstate_info अणु
	u32 core_mask;
	u32 dx_mask;
पूर्ण;

काष्ठा skl_ipc_header अणु
	u32 primary;
	u32 extension;
पूर्ण;

काष्ठा skl_dsp_cores अणु
	अचिन्हित पूर्णांक count;
	क्रमागत skl_dsp_states *state;
	पूर्णांक *usage_count;
पूर्ण;

/**
 * skl_d0i3_data: skl D0i3 counters data काष्ठा
 *
 * @streaming: Count of useहालs that can attempt streaming D0i3
 * @non_streaming: Count of useहालs that can attempt non-streaming D0i3
 * @non_d0i3: Count of useहालs that cannot attempt D0i3
 * @state: current state
 * @work: D0i3 worker thपढ़ो
 */
काष्ठा skl_d0i3_data अणु
	पूर्णांक streaming;
	पूर्णांक non_streaming;
	पूर्णांक non_d0i3;
	क्रमागत skl_dsp_d0i3_states state;
	काष्ठा delayed_work work;
पूर्ण;

#घोषणा SKL_LIB_NAME_LENGTH 128
#घोषणा SKL_MAX_LIB 16

काष्ठा skl_lib_info अणु
	अक्षर name[SKL_LIB_NAME_LENGTH];
	स्थिर काष्ठा firmware *fw;
पूर्ण;

काष्ठा skl_ipc_init_instance_msg अणु
	u32 module_id;
	u32 instance_id;
	u16 param_data_size;
	u8 ppl_instance_id;
	u8 core_id;
	u8 करोमुख्य;
पूर्ण;

काष्ठा skl_ipc_bind_unbind_msg अणु
	u32 module_id;
	u32 instance_id;
	u32 dst_module_id;
	u32 dst_instance_id;
	u8 src_queue;
	u8 dst_queue;
	bool bind;
पूर्ण;

काष्ठा skl_ipc_large_config_msg अणु
	u32 module_id;
	u32 instance_id;
	u32 large_param_id;
	u32 param_data_size;
पूर्ण;

काष्ठा skl_ipc_d0ix_msg अणु
	u32 module_id;
	u32 instance_id;
	u8 streaming;
	u8 wake;
पूर्ण;

#घोषणा SKL_IPC_BOOT_MSECS		3000

#घोषणा SKL_IPC_D3_MASK	0
#घोषणा SKL_IPC_D0_MASK	3

irqवापस_t skl_dsp_irq_thपढ़ो_handler(पूर्णांक irq, व्योम *context);

पूर्णांक skl_ipc_create_pipeline(काष्ठा sst_generic_ipc *ipc,
		u16 ppl_mem_size, u8 ppl_type, u8 instance_id, u8 lp_mode);

पूर्णांक skl_ipc_delete_pipeline(काष्ठा sst_generic_ipc *ipc, u8 instance_id);

पूर्णांक skl_ipc_set_pipeline_state(काष्ठा sst_generic_ipc *ipc,
		u8 instance_id,	क्रमागत skl_ipc_pipeline_state state);

पूर्णांक skl_ipc_save_pipeline(काष्ठा sst_generic_ipc *ipc,
		u8 instance_id, पूर्णांक dma_id);

पूर्णांक skl_ipc_restore_pipeline(काष्ठा sst_generic_ipc *ipc, u8 instance_id);

पूर्णांक skl_ipc_init_instance(काष्ठा sst_generic_ipc *ipc,
		काष्ठा skl_ipc_init_instance_msg *msg, व्योम *param_data);

पूर्णांक skl_ipc_bind_unbind(काष्ठा sst_generic_ipc *ipc,
		काष्ठा skl_ipc_bind_unbind_msg *msg);

पूर्णांक skl_ipc_load_modules(काष्ठा sst_generic_ipc *ipc,
				u8 module_cnt, व्योम *data);

पूर्णांक skl_ipc_unload_modules(काष्ठा sst_generic_ipc *ipc,
				u8 module_cnt, व्योम *data);

पूर्णांक skl_ipc_set_dx(काष्ठा sst_generic_ipc *ipc,
		u8 instance_id, u16 module_id, काष्ठा skl_ipc_dxstate_info *dx);

पूर्णांक skl_ipc_set_large_config(काष्ठा sst_generic_ipc *ipc,
		काष्ठा skl_ipc_large_config_msg *msg, u32 *param);

पूर्णांक skl_ipc_get_large_config(काष्ठा sst_generic_ipc *ipc,
		काष्ठा skl_ipc_large_config_msg *msg,
		u32 **payload, माप_प्रकार *bytes);

पूर्णांक skl_sst_ipc_load_library(काष्ठा sst_generic_ipc *ipc,
			u8 dma_id, u8 table_id, bool रुको);

पूर्णांक skl_ipc_set_d0ix(काष्ठा sst_generic_ipc *ipc,
		काष्ठा skl_ipc_d0ix_msg *msg);

पूर्णांक skl_ipc_check_D0i0(काष्ठा sst_dsp *dsp, bool state);

व्योम skl_ipc_पूर्णांक_enable(काष्ठा sst_dsp *ctx);
व्योम skl_ipc_op_पूर्णांक_enable(काष्ठा sst_dsp *ctx);
व्योम skl_ipc_op_पूर्णांक_disable(काष्ठा sst_dsp *ctx);
व्योम skl_ipc_पूर्णांक_disable(काष्ठा sst_dsp *ctx);

bool skl_ipc_पूर्णांक_status(काष्ठा sst_dsp *ctx);
व्योम skl_ipc_मुक्त(काष्ठा sst_generic_ipc *ipc);
पूर्णांक skl_ipc_init(काष्ठा device *dev, काष्ठा skl_dev *skl);
व्योम skl_clear_module_cnt(काष्ठा sst_dsp *ctx);

व्योम skl_ipc_process_reply(काष्ठा sst_generic_ipc *ipc,
		काष्ठा skl_ipc_header header);
पूर्णांक skl_ipc_process_notअगरication(काष्ठा sst_generic_ipc *ipc,
		काष्ठा skl_ipc_header header);
व्योम skl_ipc_tx_data_copy(काष्ठा ipc_message *msg, अक्षर *tx_data,
		माप_प्रकार tx_size);
#पूर्ण_अगर /* __SKL_IPC_H */
