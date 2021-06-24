<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * NCI based driver क्रम Samsung S3FWRN5 NFC chip
 *
 * Copyright (C) 2015 Samsung Electrnoics
 * Robert Baldyga <r.baldyga@samsung.com>
 */

#अगर_अघोषित __LOCAL_S3FWRN5_H_
#घोषणा __LOCAL_S3FWRN5_H_

#समावेश <linux/nfc.h>

#समावेश <net/nfc/nci_core.h>

#समावेश "firmware.h"

क्रमागत s3fwrn5_mode अणु
	S3FWRN5_MODE_COLD,
	S3FWRN5_MODE_NCI,
	S3FWRN5_MODE_FW,
पूर्ण;

काष्ठा s3fwrn5_phy_ops अणु
	व्योम (*set_wake)(व्योम *id, bool sleep);
	व्योम (*set_mode)(व्योम *id, क्रमागत s3fwrn5_mode);
	क्रमागत s3fwrn5_mode (*get_mode)(व्योम *id);
	पूर्णांक (*ग_लिखो)(व्योम *id, काष्ठा sk_buff *skb);
पूर्ण;

काष्ठा s3fwrn5_info अणु
	काष्ठा nci_dev *ndev;
	व्योम *phy_id;
	काष्ठा device *pdev;

	स्थिर काष्ठा s3fwrn5_phy_ops *phy_ops;

	काष्ठा s3fwrn5_fw_info fw_info;

	काष्ठा mutex mutex;
पूर्ण;

अटल अंतरभूत पूर्णांक s3fwrn5_set_mode(काष्ठा s3fwrn5_info *info,
	क्रमागत s3fwrn5_mode mode)
अणु
	अगर (!info->phy_ops->set_mode)
		वापस -EOPNOTSUPP;

	info->phy_ops->set_mode(info->phy_id, mode);

	वापस 0;
पूर्ण

अटल अंतरभूत क्रमागत s3fwrn5_mode s3fwrn5_get_mode(काष्ठा s3fwrn5_info *info)
अणु
	अगर (!info->phy_ops->get_mode)
		वापस -EOPNOTSUPP;

	वापस info->phy_ops->get_mode(info->phy_id);
पूर्ण

अटल अंतरभूत पूर्णांक s3fwrn5_set_wake(काष्ठा s3fwrn5_info *info, bool wake)
अणु
	अगर (!info->phy_ops->set_wake)
		वापस -EOPNOTSUPP;

	info->phy_ops->set_wake(info->phy_id, wake);

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक s3fwrn5_ग_लिखो(काष्ठा s3fwrn5_info *info, काष्ठा sk_buff *skb)
अणु
	अगर (!info->phy_ops->ग_लिखो)
		वापस -EOPNOTSUPP;

	वापस info->phy_ops->ग_लिखो(info->phy_id, skb);
पूर्ण

पूर्णांक s3fwrn5_probe(काष्ठा nci_dev **ndev, व्योम *phy_id, काष्ठा device *pdev,
	स्थिर काष्ठा s3fwrn5_phy_ops *phy_ops);
व्योम s3fwrn5_हटाओ(काष्ठा nci_dev *ndev);

पूर्णांक s3fwrn5_recv_frame(काष्ठा nci_dev *ndev, काष्ठा sk_buff *skb,
	क्रमागत s3fwrn5_mode mode);

#पूर्ण_अगर /* __LOCAL_S3FWRN5_H_ */
