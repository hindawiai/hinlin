<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/* -------------------------------------------------------------------------
 * Copyright (C) 2014-2016, Intel Corporation
 *
 * -------------------------------------------------------------------------
 */

#अगर_अघोषित __LOCAL_FDP_H_
#घोषणा __LOCAL_FDP_H_

#समावेश <net/nfc/nci_core.h>
#समावेश <linux/gpio/consumer.h>

काष्ठा fdp_i2c_phy अणु
	काष्ठा i2c_client *i2c_dev;
	काष्ठा gpio_desc *घातer_gpio;
	काष्ठा nci_dev *ndev;

	/* < 0 अगर i2c error occurred */
	पूर्णांक hard_fault;
	uपूर्णांक16_t next_पढ़ो_size;
पूर्ण;

पूर्णांक fdp_nci_probe(काष्ठा fdp_i2c_phy *phy, काष्ठा nfc_phy_ops *phy_ops,
		  काष्ठा nci_dev **ndev, पूर्णांक tx_headroom, पूर्णांक tx_tailroom,
		  u8 घड़ी_प्रकारype, u32 घड़ी_freq, u8 *fw_vsc_cfg);
व्योम fdp_nci_हटाओ(काष्ठा nci_dev *ndev);
पूर्णांक fdp_nci_recv_frame(काष्ठा nci_dev *ndev, काष्ठा sk_buff *skb);

#पूर्ण_अगर /* __LOCAL_FDP_H_ */
