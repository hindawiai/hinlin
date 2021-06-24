<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause */
/*
 * Copyright (C) 2005-2014, 2018-2021 Intel Corporation
 * Copyright (C) 2013-2014 Intel Mobile Communications GmbH
 * Copyright (C) 2015 Intel Deutschland GmbH
 */
#अगर_अघोषित __iwl_op_mode_h__
#घोषणा __iwl_op_mode_h__

#समावेश <linux/netdevice.h>
#समावेश <linux/debugfs.h>
#समावेश "iwl-dbg-tlv.h"

काष्ठा iwl_op_mode;
काष्ठा iwl_trans;
काष्ठा sk_buff;
काष्ठा iwl_device_cmd;
काष्ठा iwl_rx_cmd_buffer;
काष्ठा iwl_fw;
काष्ठा iwl_cfg;

/**
 * DOC: Operational mode - what is it ?
 *
 * The operational mode (a.k.a. op_mode) is the layer that implements
 * mac80211's handlers. It knows two APIs: mac80211's and the fw's. It uses
 * the transport API to access the HW. The op_mode करोesn't need to know how the
 * underlying HW works, since the transport layer takes care of that.
 *
 * There can be several op_mode: i.e. dअगरferent fw APIs will require two
 * dअगरferent op_modes. This is why the op_mode is भवized.
 */

/**
 * DOC: Lअगरe cycle of the Operational mode
 *
 * The operational mode has a very simple lअगरe cycle.
 *
 *	1) The driver layer (iwl-drv.c) chooses the op_mode based on the
 *	   capabilities advertised by the fw file (in TLV क्रमmat).
 *	2) The driver layer starts the op_mode (ops->start)
 *	3) The op_mode रेजिस्टरs mac80211
 *	4) The op_mode is governed by mac80211
 *	5) The driver layer stops the op_mode
 */

/**
 * काष्ठा iwl_op_mode_ops - op_mode specअगरic operations
 *
 * The op_mode exports its ops so that बाह्यal components can start it and
 * पूर्णांकeract with it. The driver layer typically calls the start and stop
 * handlers, the transport layer calls the others.
 *
 * All the handlers MUST be implemented, except @rx_rss which can be left
 * out *अगरf* the opmode will never run on hardware with multi-queue capability.
 *
 * @start: start the op_mode. The transport layer is alपढ़ोy allocated.
 *	May sleep
 * @stop: stop the op_mode. Must मुक्त all the memory allocated.
 *	May sleep
 * @rx: Rx notअगरication to the op_mode. rxb is the Rx buffer itself. Cmd is the
 *	HCMD this Rx responds to. Can't sleep.
 * @rx_rss: data queue RX notअगरication to the op_mode, क्रम (data) notअगरications
 *	received on the RSS queue(s). The queue parameter indicates which of the
 *	RSS queues received this frame; it will always be non-zero.
 *	This method must not sleep.
 * @async_cb: called when an ASYNC command with CMD_WANT_ASYNC_CALLBACK set
 *	completes. Must be atomic.
 * @queue_full: notअगरies that a HW queue is full.
 *	Must be atomic and called with BH disabled.
 * @queue_not_full: notअगरies that a HW queue is not full any more.
 *	Must be atomic and called with BH disabled.
 * @hw_rf_समाप्त:notअगरies of a change in the HW rf समाप्त चयन. True means that
 *	the radio is समाप्तed. Return %true अगर the device should be stopped by
 *	the transport immediately after the call. May sleep.
 * @मुक्त_skb: allows the transport layer to मुक्त skbs that haven't been
 *	reclaimed by the op_mode. This can happen when the driver is मुक्तd and
 *	there are Tx packets pending in the transport layer.
 *	Must be atomic
 * @nic_error: error notअगरication. Must be atomic and must be called with BH
 *	disabled.
 * @cmd_queue_full: Called when the command queue माला_लो full. Must be atomic and
 *	called with BH disabled.
 * @nic_config: configure NIC, called beक्रमe firmware is started.
 *	May sleep
 * @wimax_active: invoked when WiMax becomes active. May sleep
 * @समय_poपूर्णांक: called when transport layer wants to collect debug data
 */
काष्ठा iwl_op_mode_ops अणु
	काष्ठा iwl_op_mode *(*start)(काष्ठा iwl_trans *trans,
				     स्थिर काष्ठा iwl_cfg *cfg,
				     स्थिर काष्ठा iwl_fw *fw,
				     काष्ठा dentry *dbgfs_dir);
	व्योम (*stop)(काष्ठा iwl_op_mode *op_mode);
	व्योम (*rx)(काष्ठा iwl_op_mode *op_mode, काष्ठा napi_काष्ठा *napi,
		   काष्ठा iwl_rx_cmd_buffer *rxb);
	व्योम (*rx_rss)(काष्ठा iwl_op_mode *op_mode, काष्ठा napi_काष्ठा *napi,
		       काष्ठा iwl_rx_cmd_buffer *rxb, अचिन्हित पूर्णांक queue);
	व्योम (*async_cb)(काष्ठा iwl_op_mode *op_mode,
			 स्थिर काष्ठा iwl_device_cmd *cmd);
	व्योम (*queue_full)(काष्ठा iwl_op_mode *op_mode, पूर्णांक queue);
	व्योम (*queue_not_full)(काष्ठा iwl_op_mode *op_mode, पूर्णांक queue);
	bool (*hw_rf_समाप्त)(काष्ठा iwl_op_mode *op_mode, bool state);
	व्योम (*मुक्त_skb)(काष्ठा iwl_op_mode *op_mode, काष्ठा sk_buff *skb);
	व्योम (*nic_error)(काष्ठा iwl_op_mode *op_mode);
	व्योम (*cmd_queue_full)(काष्ठा iwl_op_mode *op_mode);
	व्योम (*nic_config)(काष्ठा iwl_op_mode *op_mode);
	व्योम (*wimax_active)(काष्ठा iwl_op_mode *op_mode);
	व्योम (*समय_poपूर्णांक)(काष्ठा iwl_op_mode *op_mode,
			   क्रमागत iwl_fw_ini_समय_poपूर्णांक tp_id,
			   जोड़ iwl_dbg_tlv_tp_data *tp_data);
पूर्ण;

पूर्णांक iwl_opmode_रेजिस्टर(स्थिर अक्षर *name, स्थिर काष्ठा iwl_op_mode_ops *ops);
व्योम iwl_opmode_deरेजिस्टर(स्थिर अक्षर *name);

/**
 * काष्ठा iwl_op_mode - operational mode
 * @ops: poपूर्णांकer to its own ops
 *
 * This holds an implementation of the mac80211 / fw API.
 */
काष्ठा iwl_op_mode अणु
	स्थिर काष्ठा iwl_op_mode_ops *ops;

	अक्षर op_mode_specअगरic[] __aligned(माप(व्योम *));
पूर्ण;

अटल अंतरभूत व्योम iwl_op_mode_stop(काष्ठा iwl_op_mode *op_mode)
अणु
	might_sleep();
	op_mode->ops->stop(op_mode);
पूर्ण

अटल अंतरभूत व्योम iwl_op_mode_rx(काष्ठा iwl_op_mode *op_mode,
				  काष्ठा napi_काष्ठा *napi,
				  काष्ठा iwl_rx_cmd_buffer *rxb)
अणु
	वापस op_mode->ops->rx(op_mode, napi, rxb);
पूर्ण

अटल अंतरभूत व्योम iwl_op_mode_rx_rss(काष्ठा iwl_op_mode *op_mode,
				      काष्ठा napi_काष्ठा *napi,
				      काष्ठा iwl_rx_cmd_buffer *rxb,
				      अचिन्हित पूर्णांक queue)
अणु
	op_mode->ops->rx_rss(op_mode, napi, rxb, queue);
पूर्ण

अटल अंतरभूत व्योम iwl_op_mode_async_cb(काष्ठा iwl_op_mode *op_mode,
					स्थिर काष्ठा iwl_device_cmd *cmd)
अणु
	अगर (op_mode->ops->async_cb)
		op_mode->ops->async_cb(op_mode, cmd);
पूर्ण

अटल अंतरभूत व्योम iwl_op_mode_queue_full(काष्ठा iwl_op_mode *op_mode,
					  पूर्णांक queue)
अणु
	op_mode->ops->queue_full(op_mode, queue);
पूर्ण

अटल अंतरभूत व्योम iwl_op_mode_queue_not_full(काष्ठा iwl_op_mode *op_mode,
					      पूर्णांक queue)
अणु
	op_mode->ops->queue_not_full(op_mode, queue);
पूर्ण

अटल अंतरभूत bool __must_check
iwl_op_mode_hw_rf_समाप्त(काष्ठा iwl_op_mode *op_mode, bool state)
अणु
	might_sleep();
	वापस op_mode->ops->hw_rf_समाप्त(op_mode, state);
पूर्ण

अटल अंतरभूत व्योम iwl_op_mode_मुक्त_skb(काष्ठा iwl_op_mode *op_mode,
					काष्ठा sk_buff *skb)
अणु
	अगर (WARN_ON_ONCE(!op_mode))
		वापस;
	op_mode->ops->मुक्त_skb(op_mode, skb);
पूर्ण

अटल अंतरभूत व्योम iwl_op_mode_nic_error(काष्ठा iwl_op_mode *op_mode)
अणु
	op_mode->ops->nic_error(op_mode);
पूर्ण

अटल अंतरभूत व्योम iwl_op_mode_cmd_queue_full(काष्ठा iwl_op_mode *op_mode)
अणु
	op_mode->ops->cmd_queue_full(op_mode);
पूर्ण

अटल अंतरभूत व्योम iwl_op_mode_nic_config(काष्ठा iwl_op_mode *op_mode)
अणु
	might_sleep();
	op_mode->ops->nic_config(op_mode);
पूर्ण

अटल अंतरभूत व्योम iwl_op_mode_wimax_active(काष्ठा iwl_op_mode *op_mode)
अणु
	might_sleep();
	op_mode->ops->wimax_active(op_mode);
पूर्ण

अटल अंतरभूत व्योम iwl_op_mode_समय_poपूर्णांक(काष्ठा iwl_op_mode *op_mode,
					  क्रमागत iwl_fw_ini_समय_poपूर्णांक tp_id,
					  जोड़ iwl_dbg_tlv_tp_data *tp_data)
अणु
	अगर (!op_mode || !op_mode->ops || !op_mode->ops->समय_poपूर्णांक)
		वापस;
	op_mode->ops->समय_poपूर्णांक(op_mode, tp_id, tp_data);
पूर्ण

#पूर्ण_अगर /* __iwl_op_mode_h__ */
