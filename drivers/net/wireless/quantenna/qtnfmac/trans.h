<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/* Copyright (c) 2015-2016 Quantenna Communications. All rights reserved. */

#अगर_अघोषित _QTN_FMAC_TRANS_H_
#घोषणा _QTN_FMAC_TRANS_H_

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/mutex.h>

#समावेश "qlink.h"

#घोषणा QTNF_CMD_FLAG_RESP_REQ		BIT(0)

#घोषणा QTNF_MAX_CMD_BUF_SIZE	2048
#घोषणा QTNF_DEF_CMD_HROOM	4

काष्ठा qtnf_bus;

काष्ठा qtnf_cmd_ctl_node अणु
	काष्ठा completion cmd_resp_completion;
	काष्ठा sk_buff *resp_skb;
	u16 seq_num;
	bool रुकोing_क्रम_resp;
	spinlock_t resp_lock; /* lock क्रम resp_skb & रुकोing_क्रम_resp changes */
पूर्ण;

काष्ठा qtnf_qlink_transport अणु
	काष्ठा qtnf_cmd_ctl_node curr_cmd;
	काष्ठा sk_buff_head event_queue;
	माप_प्रकार event_queue_max_len;
पूर्ण;

व्योम qtnf_trans_init(काष्ठा qtnf_bus *bus);
व्योम qtnf_trans_मुक्त(काष्ठा qtnf_bus *bus);

पूर्णांक qtnf_trans_send_next_cmd(काष्ठा qtnf_bus *bus);
पूर्णांक qtnf_trans_handle_rx_ctl_packet(काष्ठा qtnf_bus *bus, काष्ठा sk_buff *skb);
पूर्णांक qtnf_trans_send_cmd_with_resp(काष्ठा qtnf_bus *bus,
				  काष्ठा sk_buff *cmd_skb,
				  काष्ठा sk_buff **response_skb);

#पूर्ण_अगर /* _QTN_FMAC_TRANS_H_ */
