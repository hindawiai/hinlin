<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

/* Copyright (c) 2012-2018, The Linux Foundation. All rights reserved.
 * Copyright (C) 2019-2020 Linaro Ltd.
 */

#समावेश <linux/types.h>

#समावेश "ipa_gsi.h"
#समावेश "gsi_trans.h"
#समावेश "ipa.h"
#समावेश "ipa_endpoint.h"
#समावेश "ipa_data.h"

व्योम ipa_gsi_trans_complete(काष्ठा gsi_trans *trans)
अणु
	काष्ठा ipa *ipa = container_of(trans->gsi, काष्ठा ipa, gsi);

	ipa_endpoपूर्णांक_trans_complete(ipa->channel_map[trans->channel_id], trans);
पूर्ण

व्योम ipa_gsi_trans_release(काष्ठा gsi_trans *trans)
अणु
	काष्ठा ipa *ipa = container_of(trans->gsi, काष्ठा ipa, gsi);

	ipa_endpoपूर्णांक_trans_release(ipa->channel_map[trans->channel_id], trans);
पूर्ण

व्योम ipa_gsi_channel_tx_queued(काष्ठा gsi *gsi, u32 channel_id, u32 count,
			       u32 byte_count)
अणु
	काष्ठा ipa *ipa = container_of(gsi, काष्ठा ipa, gsi);
	काष्ठा ipa_endpoपूर्णांक *endpoपूर्णांक;

	endpoपूर्णांक = ipa->channel_map[channel_id];
	अगर (endpoपूर्णांक->netdev)
		netdev_sent_queue(endpoपूर्णांक->netdev, byte_count);
पूर्ण

व्योम ipa_gsi_channel_tx_completed(काष्ठा gsi *gsi, u32 channel_id, u32 count,
				  u32 byte_count)
अणु
	काष्ठा ipa *ipa = container_of(gsi, काष्ठा ipa, gsi);
	काष्ठा ipa_endpoपूर्णांक *endpoपूर्णांक;

	endpoपूर्णांक = ipa->channel_map[channel_id];
	अगर (endpoपूर्णांक->netdev)
		netdev_completed_queue(endpoपूर्णांक->netdev, count, byte_count);
पूर्ण

/* Indicate whether an endpoपूर्णांक config data entry is "empty" */
bool ipa_gsi_endpoपूर्णांक_data_empty(स्थिर काष्ठा ipa_gsi_endpoपूर्णांक_data *data)
अणु
	वापस data->ee_id == GSI_EE_AP && !data->channel.tlv_count;
पूर्ण
