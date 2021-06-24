<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later
 *
 * Link Layer क्रम Samsung S3FWRN5 NCI based Driver
 *
 * Copyright (C) 2015 Samsung Electrnoics
 * Robert Baldyga <r.baldyga@samsung.com>
 * Copyright (C) 2020 Samsung Electrnoics
 * Bongsu Jeon <bongsu.jeon@samsung.com>
 */

#अगर_अघोषित __NFC_S3FWRN5_PHY_COMMON_H
#घोषणा __NFC_S3FWRN5_PHY_COMMON_H

#समावेश <linux/mutex.h>
#समावेश <net/nfc/nci_core.h>

#समावेश "s3fwrn5.h"

#घोषणा S3FWRN5_EN_WAIT_TIME 20

काष्ठा phy_common अणु
	काष्ठा nci_dev *ndev;

	पूर्णांक gpio_en;
	पूर्णांक gpio_fw_wake;

	काष्ठा mutex mutex;

	क्रमागत s3fwrn5_mode mode;
पूर्ण;

व्योम s3fwrn5_phy_set_wake(व्योम *phy_id, bool wake);
bool s3fwrn5_phy_घातer_ctrl(काष्ठा phy_common *phy, क्रमागत s3fwrn5_mode mode);
व्योम s3fwrn5_phy_set_mode(व्योम *phy_id, क्रमागत s3fwrn5_mode mode);
क्रमागत s3fwrn5_mode s3fwrn5_phy_get_mode(व्योम *phy_id);

#पूर्ण_अगर /* __NFC_S3FWRN5_PHY_COMMON_H */
