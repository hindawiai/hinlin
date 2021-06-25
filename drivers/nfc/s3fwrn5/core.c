<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * NCI based driver क्रम Samsung S3FWRN5 NFC chip
 *
 * Copyright (C) 2015 Samsung Electrnoics
 * Robert Baldyga <r.baldyga@samsung.com>
 */

#समावेश <linux/module.h>
#समावेश <net/nfc/nci_core.h>

#समावेश "s3fwrn5.h"
#समावेश "firmware.h"
#समावेश "nci.h"

#घोषणा S3FWRN5_NFC_PROTOCOLS  (NFC_PROTO_JEWEL_MASK | \
				NFC_PROTO_MIFARE_MASK | \
				NFC_PROTO_FELICA_MASK | \
				NFC_PROTO_ISO14443_MASK | \
				NFC_PROTO_ISO14443_B_MASK | \
				NFC_PROTO_ISO15693_MASK)

अटल पूर्णांक s3fwrn5_firmware_init(काष्ठा s3fwrn5_info *info)
अणु
	काष्ठा s3fwrn5_fw_info *fw_info = &info->fw_info;
	पूर्णांक ret;

	s3fwrn5_fw_init(fw_info, "sec_s3fwrn5_firmware.bin");

	/* Get firmware data */
	ret = s3fwrn5_fw_request_firmware(fw_info);
	अगर (ret < 0)
		dev_err(&fw_info->ndev->nfc_dev->dev,
			"Failed to get fw file, ret=%02x\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक s3fwrn5_firmware_update(काष्ठा s3fwrn5_info *info)
अणु
	bool need_update;
	पूर्णांक ret;

	/* Update firmware */

	s3fwrn5_set_wake(info, false);
	s3fwrn5_set_mode(info, S3FWRN5_MODE_FW);

	ret = s3fwrn5_fw_setup(&info->fw_info);
	अगर (ret < 0)
		वापस ret;

	need_update = s3fwrn5_fw_check_version(&info->fw_info,
		info->ndev->manufact_specअगरic_info);
	अगर (!need_update)
		जाओ out;

	dev_info(&info->ndev->nfc_dev->dev, "Detected new firmware version\n");

	ret = s3fwrn5_fw_करोwnload(&info->fw_info);
	अगर (ret < 0)
		जाओ out;

	/* Update RF configuration */

	s3fwrn5_set_mode(info, S3FWRN5_MODE_NCI);

	s3fwrn5_set_wake(info, true);
	ret = s3fwrn5_nci_rf_configure(info, "sec_s3fwrn5_rfreg.bin");
	s3fwrn5_set_wake(info, false);

out:
	s3fwrn5_set_mode(info, S3FWRN5_MODE_COLD);
	s3fwrn5_fw_cleanup(&info->fw_info);
	वापस ret;
पूर्ण

अटल पूर्णांक s3fwrn5_nci_खोलो(काष्ठा nci_dev *ndev)
अणु
	काष्ठा s3fwrn5_info *info = nci_get_drvdata(ndev);

	अगर (s3fwrn5_get_mode(info) != S3FWRN5_MODE_COLD)
		वापस  -EBUSY;

	s3fwrn5_set_mode(info, S3FWRN5_MODE_NCI);
	s3fwrn5_set_wake(info, true);

	वापस 0;
पूर्ण

अटल पूर्णांक s3fwrn5_nci_बंद(काष्ठा nci_dev *ndev)
अणु
	काष्ठा s3fwrn5_info *info = nci_get_drvdata(ndev);

	s3fwrn5_set_wake(info, false);
	s3fwrn5_set_mode(info, S3FWRN5_MODE_COLD);

	वापस 0;
पूर्ण

अटल पूर्णांक s3fwrn5_nci_send(काष्ठा nci_dev *ndev, काष्ठा sk_buff *skb)
अणु
	काष्ठा s3fwrn5_info *info = nci_get_drvdata(ndev);
	पूर्णांक ret;

	mutex_lock(&info->mutex);

	अगर (s3fwrn5_get_mode(info) != S3FWRN5_MODE_NCI) अणु
		mutex_unlock(&info->mutex);
		वापस -EINVAL;
	पूर्ण

	ret = s3fwrn5_ग_लिखो(info, skb);
	अगर (ret < 0)
		kमुक्त_skb(skb);

	mutex_unlock(&info->mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक s3fwrn5_nci_post_setup(काष्ठा nci_dev *ndev)
अणु
	काष्ठा s3fwrn5_info *info = nci_get_drvdata(ndev);
	पूर्णांक ret;

	अगर (s3fwrn5_firmware_init(info)) अणु
		//skip bootloader mode
		वापस 0;
	पूर्ण

	ret = s3fwrn5_firmware_update(info);
	अगर (ret < 0)
		वापस ret;

	/* NCI core reset */

	s3fwrn5_set_mode(info, S3FWRN5_MODE_NCI);
	s3fwrn5_set_wake(info, true);

	ret = nci_core_reset(info->ndev);
	अगर (ret < 0)
		वापस ret;

	वापस nci_core_init(info->ndev);
पूर्ण

अटल काष्ठा nci_ops s3fwrn5_nci_ops = अणु
	.खोलो = s3fwrn5_nci_खोलो,
	.बंद = s3fwrn5_nci_बंद,
	.send = s3fwrn5_nci_send,
	.post_setup = s3fwrn5_nci_post_setup,
पूर्ण;

पूर्णांक s3fwrn5_probe(काष्ठा nci_dev **ndev, व्योम *phy_id, काष्ठा device *pdev,
	स्थिर काष्ठा s3fwrn5_phy_ops *phy_ops)
अणु
	काष्ठा s3fwrn5_info *info;
	पूर्णांक ret;

	info = devm_kzalloc(pdev, माप(*info), GFP_KERNEL);
	अगर (!info)
		वापस -ENOMEM;

	info->phy_id = phy_id;
	info->pdev = pdev;
	info->phy_ops = phy_ops;
	mutex_init(&info->mutex);

	s3fwrn5_set_mode(info, S3FWRN5_MODE_COLD);

	s3fwrn5_nci_get_prop_ops(&s3fwrn5_nci_ops.prop_ops,
		&s3fwrn5_nci_ops.n_prop_ops);

	info->ndev = nci_allocate_device(&s3fwrn5_nci_ops,
		S3FWRN5_NFC_PROTOCOLS, 0, 0);
	अगर (!info->ndev)
		वापस -ENOMEM;

	nci_set_parent_dev(info->ndev, pdev);
	nci_set_drvdata(info->ndev, info);

	ret = nci_रेजिस्टर_device(info->ndev);
	अगर (ret < 0) अणु
		nci_मुक्त_device(info->ndev);
		वापस ret;
	पूर्ण

	info->fw_info.ndev = info->ndev;

	*ndev = info->ndev;

	वापस ret;
पूर्ण
EXPORT_SYMBOL(s3fwrn5_probe);

व्योम s3fwrn5_हटाओ(काष्ठा nci_dev *ndev)
अणु
	काष्ठा s3fwrn5_info *info = nci_get_drvdata(ndev);

	s3fwrn5_set_mode(info, S3FWRN5_MODE_COLD);

	nci_unरेजिस्टर_device(ndev);
	nci_मुक्त_device(ndev);
पूर्ण
EXPORT_SYMBOL(s3fwrn5_हटाओ);

पूर्णांक s3fwrn5_recv_frame(काष्ठा nci_dev *ndev, काष्ठा sk_buff *skb,
	क्रमागत s3fwrn5_mode mode)
अणु
	चयन (mode) अणु
	हाल S3FWRN5_MODE_NCI:
		वापस nci_recv_frame(ndev, skb);
	हाल S3FWRN5_MODE_FW:
		वापस s3fwrn5_fw_recv_frame(ndev, skb);
	शेष:
		kमुक्त_skb(skb);
		वापस -ENODEV;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(s3fwrn5_recv_frame);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Samsung S3FWRN5 NFC driver");
MODULE_AUTHOR("Robert Baldyga <r.baldyga@samsung.com>");
