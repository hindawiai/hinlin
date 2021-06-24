<शैली गुरु>
/* SPDX-License-Identअगरier: ISC */
/*
 * Copyright (C) 2016 Felix Fietkau <nbd@nbd.name>
 */

#अगर_अघोषित __MT76x2_MAC_H
#घोषणा __MT76x2_MAC_H

#समावेश "mt76x2.h"

काष्ठा mt76x02_dev;
काष्ठा mt76x2_sta;
काष्ठा mt76x02_vअगर;

व्योम mt76x2_mac_stop(काष्ठा mt76x02_dev *dev, bool क्रमce);

अटल अंतरभूत व्योम mt76x2_mac_resume(काष्ठा mt76x02_dev *dev)
अणु
	mt76_wr(dev, MT_MAC_SYS_CTRL,
		MT_MAC_SYS_CTRL_ENABLE_TX |
		MT_MAC_SYS_CTRL_ENABLE_RX);
पूर्ण

#पूर्ण_अगर
