<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

/* Copyright (c) 2012-2018, The Linux Foundation. All rights reserved.
 * Copyright (C) 2019-2020 Linaro Ltd.
 */
#अगर_अघोषित _IPA_GSI_TRANS_H_
#घोषणा _IPA_GSI_TRANS_H_

#समावेश <linux/types.h>

काष्ठा gsi;
काष्ठा gsi_trans;
काष्ठा ipa_gsi_endpoपूर्णांक_data;

/**
 * ipa_gsi_trans_complete() - GSI transaction completion callback
 * @trans:	Transaction that has completed
 *
 * This called from the GSI layer to notअगरy the IPA layer that a
 * transaction has completed.
 */
व्योम ipa_gsi_trans_complete(काष्ठा gsi_trans *trans);

/**
 * ipa_gsi_trans_release() - GSI transaction release callback
 * @trans:	Transaction whose resources should be मुक्तd
 *
 * This called from the GSI layer to notअगरy the IPA layer that a
 * transaction is about to be मुक्तd, so any resources associated
 * with it should be released.
 */
व्योम ipa_gsi_trans_release(काष्ठा gsi_trans *trans);

/**
 * ipa_gsi_channel_tx_queued() - GSI queued to hardware notअगरication
 * @gsi:	GSI poपूर्णांकer
 * @channel_id:	Channel number
 * @count:	Number of transactions queued
 * @byte_count:	Number of bytes to transfer represented by transactions
 *
 * This called from the GSI layer to notअगरy the IPA layer that some
 * number of transactions have been queued to hardware क्रम execution.
 */
व्योम ipa_gsi_channel_tx_queued(काष्ठा gsi *gsi, u32 channel_id, u32 count,
			       u32 byte_count);

/**
 * ipa_gsi_channel_tx_completed() - GSI transaction completion callback
 * @gsi:	GSI poपूर्णांकer
 * @channel_id:	Channel number
 * @count:	Number of transactions completed since last report
 * @byte_count:	Number of bytes transferred represented by transactions
 *
 * This called from the GSI layer to notअगरy the IPA layer that the hardware
 * has reported the completion of some number of transactions.
 */
व्योम ipa_gsi_channel_tx_completed(काष्ठा gsi *gsi, u32 channel_id, u32 count,
				  u32 byte_count);

/* ipa_gsi_endpoपूर्णांक_data_empty() - Empty endpoपूर्णांक config data test
 * @data:	endpoपूर्णांक configuration data
 *
 * Determines whether an endpoपूर्णांक configuration data entry is empty,
 * meaning it contains no valid configuration inक्रमmation and should
 * be ignored.
 *
 * Return:	true अगर empty; false otherwise
 */
bool ipa_gsi_endpoपूर्णांक_data_empty(स्थिर काष्ठा ipa_gsi_endpoपूर्णांक_data *data);

#पूर्ण_अगर /* _IPA_GSI_TRANS_H_ */
