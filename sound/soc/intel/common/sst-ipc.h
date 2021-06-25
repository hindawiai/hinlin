<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Intel SST generic IPC Support
 *
 * Copyright (C) 2015, Intel Corporation. All rights reserved.
 */

#अगर_अघोषित __SST_GENERIC_IPC_H
#घोषणा __SST_GENERIC_IPC_H

#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/रुको.h>
#समावेश <linux/list.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/sched.h>

काष्ठा sst_ipc_message अणु
	u64 header;
	व्योम *data;
	माप_प्रकार size;
पूर्ण;

काष्ठा ipc_message अणु
	काष्ठा list_head list;
	काष्ठा sst_ipc_message tx;
	काष्ठा sst_ipc_message rx;

	रुको_queue_head_t रुकोq;
	bool pending;
	bool complete;
	bool रुको;
	पूर्णांक त्रुटि_सं;
पूर्ण;

काष्ठा sst_generic_ipc;
काष्ठा sst_dsp;

काष्ठा sst_plat_ipc_ops अणु
	व्योम (*tx_msg)(काष्ठा sst_generic_ipc *, काष्ठा ipc_message *);
	व्योम (*shim_dbg)(काष्ठा sst_generic_ipc *, स्थिर अक्षर *);
	व्योम (*tx_data_copy)(काष्ठा ipc_message *, अक्षर *, माप_प्रकार);
	u64  (*reply_msg_match)(u64 header, u64 *mask);
	bool (*is_dsp_busy)(काष्ठा sst_dsp *dsp);
	पूर्णांक (*check_dsp_lp_on)(काष्ठा sst_dsp *dsp, bool state);
पूर्ण;

/* SST generic IPC data */
काष्ठा sst_generic_ipc अणु
	काष्ठा device *dev;
	काष्ठा sst_dsp *dsp;

	/* IPC messaging */
	काष्ठा list_head tx_list;
	काष्ठा list_head rx_list;
	काष्ठा list_head empty_list;
	रुको_queue_head_t रुको_txq;
	काष्ठा task_काष्ठा *tx_thपढ़ो;
	काष्ठा work_काष्ठा kwork;
	bool pending;
	काष्ठा ipc_message *msg;
	पूर्णांक tx_data_max_size;
	पूर्णांक rx_data_max_size;

	काष्ठा sst_plat_ipc_ops ops;
पूर्ण;

पूर्णांक sst_ipc_tx_message_रुको(काष्ठा sst_generic_ipc *ipc,
	काष्ठा sst_ipc_message request, काष्ठा sst_ipc_message *reply);

पूर्णांक sst_ipc_tx_message_noरुको(काष्ठा sst_generic_ipc *ipc,
	काष्ठा sst_ipc_message request);

पूर्णांक sst_ipc_tx_message_nopm(काष्ठा sst_generic_ipc *ipc,
	काष्ठा sst_ipc_message request, काष्ठा sst_ipc_message *reply);

काष्ठा ipc_message *sst_ipc_reply_find_msg(काष्ठा sst_generic_ipc *ipc,
	u64 header);

व्योम sst_ipc_tx_msg_reply_complete(काष्ठा sst_generic_ipc *ipc,
	काष्ठा ipc_message *msg);

पूर्णांक sst_ipc_init(काष्ठा sst_generic_ipc *ipc);
व्योम sst_ipc_fini(काष्ठा sst_generic_ipc *ipc);

#पूर्ण_अगर
