<शैली गुरु>
/* SPDX-License-Identअगरier: ISC */
/*
 * Copyright (c) 2005-2011 Atheros Communications Inc.
 * Copyright (c) 2011-2014,2016 Qualcomm Atheros, Inc.
 */
#अगर_अघोषित _TXRX_H_
#घोषणा _TXRX_H_

#समावेश "htt.h"

पूर्णांक ath10k_txrx_tx_unref(काष्ठा ath10k_htt *htt,
			 स्थिर काष्ठा htt_tx_करोne *tx_करोne);

काष्ठा ath10k_peer *ath10k_peer_find(काष्ठा ath10k *ar, पूर्णांक vdev_id,
				     स्थिर u8 *addr);
काष्ठा ath10k_peer *ath10k_peer_find_by_id(काष्ठा ath10k *ar, पूर्णांक peer_id);
पूर्णांक ath10k_रुको_क्रम_peer_created(काष्ठा ath10k *ar, पूर्णांक vdev_id,
				 स्थिर u8 *addr);
पूर्णांक ath10k_रुको_क्रम_peer_deleted(काष्ठा ath10k *ar, पूर्णांक vdev_id,
				 स्थिर u8 *addr);

व्योम ath10k_peer_map_event(काष्ठा ath10k_htt *htt,
			   काष्ठा htt_peer_map_event *ev);
व्योम ath10k_peer_unmap_event(काष्ठा ath10k_htt *htt,
			     काष्ठा htt_peer_unmap_event *ev);

#पूर्ण_अगर
