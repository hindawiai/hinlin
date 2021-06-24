<शैली गुरु>
/* SPDX-License-Identअगरier: ISC */
/*
 * Copyright (C) 2018 Lorenzo Bianconi <lorenzo.bianconi83@gmail.com>
 */

#अगर_अघोषित __MT76x2U_H
#घोषणा __MT76x2U_H

#समावेश <linux/device.h>

#समावेश "mt76x2.h"
#समावेश "mcu.h"

#घोषणा MT7612U_EEPROM_SIZE		512

#घोषणा MT_USB_AGGR_SIZE_LIMIT		21 /* 1024B unit */
#घोषणा MT_USB_AGGR_TIMEOUT		0x80 /* 33ns unit */

बाह्य स्थिर काष्ठा ieee80211_ops mt76x2u_ops;

पूर्णांक mt76x2u_रेजिस्टर_device(काष्ठा mt76x02_dev *dev);
पूर्णांक mt76x2u_init_hardware(काष्ठा mt76x02_dev *dev);
व्योम mt76x2u_cleanup(काष्ठा mt76x02_dev *dev);
व्योम mt76x2u_stop_hw(काष्ठा mt76x02_dev *dev);

पूर्णांक mt76x2u_mac_reset(काष्ठा mt76x02_dev *dev);
पूर्णांक mt76x2u_mac_stop(काष्ठा mt76x02_dev *dev);

पूर्णांक mt76x2u_phy_set_channel(काष्ठा mt76x02_dev *dev,
			    काष्ठा cfg80211_chan_def *chandef);
व्योम mt76x2u_phy_calibrate(काष्ठा work_काष्ठा *work);

व्योम mt76x2u_mcu_complete_urb(काष्ठा urb *urb);
पूर्णांक mt76x2u_mcu_init(काष्ठा mt76x02_dev *dev);
पूर्णांक mt76x2u_mcu_fw_init(काष्ठा mt76x02_dev *dev);

पूर्णांक mt76x2u_alloc_queues(काष्ठा mt76x02_dev *dev);
व्योम mt76x2u_queues_deinit(काष्ठा mt76x02_dev *dev);
व्योम mt76x2u_stop_queues(काष्ठा mt76x02_dev *dev);
पूर्णांक mt76x2u_skb_dma_info(काष्ठा sk_buff *skb, क्रमागत dma_msg_port port,
			 u32 flags);

#पूर्ण_अगर /* __MT76x2U_H */
