<शैली गुरु>
/* SPDX-License-Identअगरier: ISC */
/*
 * Copyright (C) 2018 Lorenzo Bianconi <lorenzo.bianconi83@gmail.com>
 */

#अगर_अघोषित __MT76x02_USB_H
#घोषणा __MT76x02_USB_H

#समावेश "mt76x02.h"

पूर्णांक mt76x02u_mac_start(काष्ठा mt76x02_dev *dev);
व्योम mt76x02u_init_mcu(काष्ठा mt76_dev *dev);
व्योम mt76x02u_mcu_fw_reset(काष्ठा mt76x02_dev *dev);
पूर्णांक mt76x02u_mcu_fw_send_data(काष्ठा mt76x02_dev *dev, स्थिर व्योम *data,
			      पूर्णांक data_len, u32 max_payload, u32 offset);

पूर्णांक mt76x02u_skb_dma_info(काष्ठा sk_buff *skb, पूर्णांक port, u32 flags);
पूर्णांक mt76x02u_tx_prepare_skb(काष्ठा mt76_dev *mdev, व्योम *data,
			    क्रमागत mt76_txq_id qid, काष्ठा mt76_wcid *wcid,
			    काष्ठा ieee80211_sta *sta,
			    काष्ठा mt76_tx_info *tx_info);
व्योम mt76x02u_tx_complete_skb(काष्ठा mt76_dev *mdev, काष्ठा mt76_queue_entry *e);
व्योम mt76x02u_init_beacon_config(काष्ठा mt76x02_dev *dev);
व्योम mt76x02u_निकास_beacon_config(काष्ठा mt76x02_dev *dev);
#पूर्ण_अगर /* __MT76x02_USB_H */
