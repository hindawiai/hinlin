<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Generic driver क्रम NXP NCI NFC chips
 *
 * Copyright (C) 2014  NXP Semiconductors  All rights reserved.
 *
 * Authors: Clथऊment Perrochaud <clement.perrochaud@nxp.com>
 *
 * Derived from PN544 device driver:
 * Copyright (C) 2012  Intel Corporation. All rights reserved.
 */

#समावेश <linux/delay.h>
#समावेश <linux/module.h>
#समावेश <linux/nfc.h>

#समावेश <net/nfc/nci_core.h>

#समावेश "nxp-nci.h"

#घोषणा NXP_NCI_HDR_LEN	4

#घोषणा NXP_NCI_NFC_PROTOCOLS (NFC_PROTO_JEWEL_MASK | \
			       NFC_PROTO_MIFARE_MASK | \
			       NFC_PROTO_FELICA_MASK | \
			       NFC_PROTO_ISO14443_MASK | \
			       NFC_PROTO_ISO14443_B_MASK | \
			       NFC_PROTO_NFC_DEP_MASK)

अटल पूर्णांक nxp_nci_खोलो(काष्ठा nci_dev *ndev)
अणु
	काष्ठा nxp_nci_info *info = nci_get_drvdata(ndev);
	पूर्णांक r = 0;

	mutex_lock(&info->info_lock);

	अगर (info->mode != NXP_NCI_MODE_COLD) अणु
		r = -EBUSY;
		जाओ खोलो_निकास;
	पूर्ण

	अगर (info->phy_ops->set_mode)
		r = info->phy_ops->set_mode(info->phy_id, NXP_NCI_MODE_NCI);

	info->mode = NXP_NCI_MODE_NCI;

खोलो_निकास:
	mutex_unlock(&info->info_lock);
	वापस r;
पूर्ण

अटल पूर्णांक nxp_nci_बंद(काष्ठा nci_dev *ndev)
अणु
	काष्ठा nxp_nci_info *info = nci_get_drvdata(ndev);
	पूर्णांक r = 0;

	mutex_lock(&info->info_lock);

	अगर (info->phy_ops->set_mode)
		r = info->phy_ops->set_mode(info->phy_id, NXP_NCI_MODE_COLD);

	info->mode = NXP_NCI_MODE_COLD;

	mutex_unlock(&info->info_lock);
	वापस r;
पूर्ण

अटल पूर्णांक nxp_nci_send(काष्ठा nci_dev *ndev, काष्ठा sk_buff *skb)
अणु
	काष्ठा nxp_nci_info *info = nci_get_drvdata(ndev);
	पूर्णांक r;

	अगर (!info->phy_ops->ग_लिखो) अणु
		r = -ENOTSUPP;
		जाओ send_निकास;
	पूर्ण

	अगर (info->mode != NXP_NCI_MODE_NCI) अणु
		r = -EINVAL;
		जाओ send_निकास;
	पूर्ण

	r = info->phy_ops->ग_लिखो(info->phy_id, skb);
	अगर (r < 0)
		kमुक्त_skb(skb);

send_निकास:
	वापस r;
पूर्ण

अटल काष्ठा nci_ops nxp_nci_ops = अणु
	.खोलो = nxp_nci_खोलो,
	.बंद = nxp_nci_बंद,
	.send = nxp_nci_send,
	.fw_करोwnload = nxp_nci_fw_करोwnload,
पूर्ण;

पूर्णांक nxp_nci_probe(व्योम *phy_id, काष्ठा device *pdev,
		  स्थिर काष्ठा nxp_nci_phy_ops *phy_ops,
		  अचिन्हित पूर्णांक max_payload,
		  काष्ठा nci_dev **ndev)
अणु
	काष्ठा nxp_nci_info *info;
	पूर्णांक r;

	info = devm_kzalloc(pdev, माप(काष्ठा nxp_nci_info), GFP_KERNEL);
	अगर (!info) अणु
		r = -ENOMEM;
		जाओ probe_निकास;
	पूर्ण

	info->phy_id = phy_id;
	info->pdev = pdev;
	info->phy_ops = phy_ops;
	info->max_payload = max_payload;
	INIT_WORK(&info->fw_info.work, nxp_nci_fw_work);
	init_completion(&info->fw_info.cmd_completion);
	mutex_init(&info->info_lock);

	अगर (info->phy_ops->set_mode) अणु
		r = info->phy_ops->set_mode(info->phy_id, NXP_NCI_MODE_COLD);
		अगर (r < 0)
			जाओ probe_निकास;
	पूर्ण

	info->mode = NXP_NCI_MODE_COLD;

	info->ndev = nci_allocate_device(&nxp_nci_ops, NXP_NCI_NFC_PROTOCOLS,
					 NXP_NCI_HDR_LEN, 0);
	अगर (!info->ndev) अणु
		r = -ENOMEM;
		जाओ probe_निकास;
	पूर्ण

	nci_set_parent_dev(info->ndev, pdev);
	nci_set_drvdata(info->ndev, info);
	r = nci_रेजिस्टर_device(info->ndev);
	अगर (r < 0)
		जाओ probe_निकास_मुक्त_nci;

	*ndev = info->ndev;

	जाओ probe_निकास;

probe_निकास_मुक्त_nci:
	nci_मुक्त_device(info->ndev);
probe_निकास:
	वापस r;
पूर्ण
EXPORT_SYMBOL(nxp_nci_probe);

व्योम nxp_nci_हटाओ(काष्ठा nci_dev *ndev)
अणु
	काष्ठा nxp_nci_info *info = nci_get_drvdata(ndev);

	अगर (info->mode == NXP_NCI_MODE_FW)
		nxp_nci_fw_work_complete(info, -ESHUTDOWN);
	cancel_work_sync(&info->fw_info.work);

	mutex_lock(&info->info_lock);

	अगर (info->phy_ops->set_mode)
		info->phy_ops->set_mode(info->phy_id, NXP_NCI_MODE_COLD);

	nci_unरेजिस्टर_device(ndev);
	nci_मुक्त_device(ndev);

	mutex_unlock(&info->info_lock);
पूर्ण
EXPORT_SYMBOL(nxp_nci_हटाओ);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("NXP NCI NFC driver");
MODULE_AUTHOR("Clथऊment Perrochaud <clement.perrochaud@nxp.com>");
