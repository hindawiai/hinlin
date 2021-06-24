<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2014  NXP Semiconductors  All rights reserved.
 *
 * Authors: Clथऊment Perrochaud <clement.perrochaud@nxp.com>
 *
 * Derived from PN544 device driver:
 * Copyright (C) 2012  Intel Corporation. All rights reserved.
*/

#अगर_अघोषित __LOCAL_NXP_NCI_H_
#घोषणा __LOCAL_NXP_NCI_H_

#समावेश <linux/completion.h>
#समावेश <linux/firmware.h>
#समावेश <linux/nfc.h>

#समावेश <net/nfc/nci_core.h>

#घोषणा NXP_NCI_FW_HDR_LEN	2
#घोषणा NXP_NCI_FW_CRC_LEN	2

#घोषणा NXP_NCI_FW_FRAME_LEN_MASK	0x03FF

क्रमागत nxp_nci_mode अणु
	NXP_NCI_MODE_COLD,
	NXP_NCI_MODE_NCI,
	NXP_NCI_MODE_FW
पूर्ण;

काष्ठा nxp_nci_phy_ops अणु
	पूर्णांक (*set_mode)(व्योम *id, क्रमागत nxp_nci_mode mode);
	पूर्णांक (*ग_लिखो)(व्योम *id, काष्ठा sk_buff *skb);
पूर्ण;

काष्ठा nxp_nci_fw_info अणु
	अक्षर name[NFC_FIRMWARE_NAME_MAXSIZE + 1];
	स्थिर काष्ठा firmware *fw;

	माप_प्रकार size;
	माप_प्रकार written;

	स्थिर u8 *data;
	माप_प्रकार frame_size;

	काष्ठा work_काष्ठा work;
	काष्ठा completion cmd_completion;

	पूर्णांक cmd_result;
पूर्ण;

काष्ठा nxp_nci_info अणु
	काष्ठा nci_dev *ndev;
	व्योम *phy_id;
	काष्ठा device *pdev;

	क्रमागत nxp_nci_mode mode;

	स्थिर काष्ठा nxp_nci_phy_ops *phy_ops;
	अचिन्हित पूर्णांक max_payload;

	काष्ठा mutex info_lock;

	काष्ठा nxp_nci_fw_info fw_info;
पूर्ण;

पूर्णांक nxp_nci_fw_करोwnload(काष्ठा nci_dev *ndev, स्थिर अक्षर *firmware_name);
व्योम nxp_nci_fw_work(काष्ठा work_काष्ठा *work);
व्योम nxp_nci_fw_recv_frame(काष्ठा nci_dev *ndev, काष्ठा sk_buff *skb);
व्योम nxp_nci_fw_work_complete(काष्ठा nxp_nci_info *info, पूर्णांक result);

पूर्णांक nxp_nci_probe(व्योम *phy_id, काष्ठा device *pdev,
		  स्थिर काष्ठा nxp_nci_phy_ops *phy_ops,
		  अचिन्हित पूर्णांक max_payload,
		  काष्ठा nci_dev **ndev);
व्योम nxp_nci_हटाओ(काष्ठा nci_dev *ndev);

#पूर्ण_अगर /* __LOCAL_NXP_NCI_H_ */
