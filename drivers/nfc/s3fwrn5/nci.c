<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * NCI based driver क्रम Samsung S3FWRN5 NFC chip
 *
 * Copyright (C) 2015 Samsung Electrnoics
 * Robert Baldyga <r.baldyga@samsung.com>
 */

#समावेश <linux/completion.h>
#समावेश <linux/firmware.h>

#समावेश "s3fwrn5.h"
#समावेश "nci.h"

अटल पूर्णांक s3fwrn5_nci_prop_rsp(काष्ठा nci_dev *ndev, काष्ठा sk_buff *skb)
अणु
	__u8 status = skb->data[0];

	nci_req_complete(ndev, status);
	वापस 0;
पूर्ण

अटल काष्ठा nci_driver_ops s3fwrn5_nci_prop_ops[] = अणु
	अणु
		.opcode = nci_opcode_pack(NCI_GID_PROPRIETARY,
				NCI_PROP_SET_RFREG),
		.rsp = s3fwrn5_nci_prop_rsp,
	पूर्ण,
	अणु
		.opcode = nci_opcode_pack(NCI_GID_PROPRIETARY,
				NCI_PROP_START_RFREG),
		.rsp = s3fwrn5_nci_prop_rsp,
	पूर्ण,
	अणु
		.opcode = nci_opcode_pack(NCI_GID_PROPRIETARY,
				NCI_PROP_STOP_RFREG),
		.rsp = s3fwrn5_nci_prop_rsp,
	पूर्ण,
	अणु
		.opcode = nci_opcode_pack(NCI_GID_PROPRIETARY,
				NCI_PROP_FW_CFG),
		.rsp = s3fwrn5_nci_prop_rsp,
	पूर्ण,
पूर्ण;

व्योम s3fwrn5_nci_get_prop_ops(काष्ठा nci_driver_ops **ops, माप_प्रकार *n)
अणु
	*ops = s3fwrn5_nci_prop_ops;
	*n = ARRAY_SIZE(s3fwrn5_nci_prop_ops);
पूर्ण

#घोषणा S3FWRN5_RFREG_SECTION_SIZE 252

पूर्णांक s3fwrn5_nci_rf_configure(काष्ठा s3fwrn5_info *info, स्थिर अक्षर *fw_name)
अणु
	स्थिर काष्ठा firmware *fw;
	काष्ठा nci_prop_fw_cfg_cmd fw_cfg;
	काष्ठा nci_prop_set_rfreg_cmd set_rfreg;
	काष्ठा nci_prop_stop_rfreg_cmd stop_rfreg;
	u32 checksum;
	पूर्णांक i, len;
	पूर्णांक ret;

	ret = request_firmware(&fw, fw_name, &info->ndev->nfc_dev->dev);
	अगर (ret < 0)
		वापस ret;

	/* Compute rfreg checksum */

	checksum = 0;
	क्रम (i = 0; i < fw->size; i += 4)
		checksum += *((u32 *)(fw->data+i));

	/* Set शेष घड़ी configuration क्रम बाह्यal crystal */

	fw_cfg.clk_type = 0x01;
	fw_cfg.clk_speed = 0xff;
	fw_cfg.clk_req = 0xff;
	ret = nci_prop_cmd(info->ndev, NCI_PROP_FW_CFG,
		माप(fw_cfg), (__u8 *)&fw_cfg);
	अगर (ret < 0)
		जाओ out;

	/* Start rfreg configuration */

	dev_info(&info->ndev->nfc_dev->dev,
		"rfreg configuration update: %s\n", fw_name);

	ret = nci_prop_cmd(info->ndev, NCI_PROP_START_RFREG, 0, शून्य);
	अगर (ret < 0) अणु
		dev_err(&info->ndev->nfc_dev->dev,
			"Unable to start rfreg update\n");
		जाओ out;
	पूर्ण

	/* Update rfreg */

	set_rfreg.index = 0;
	क्रम (i = 0; i < fw->size; i += S3FWRN5_RFREG_SECTION_SIZE) अणु
		len = (fw->size - i < S3FWRN5_RFREG_SECTION_SIZE) ?
			(fw->size - i) : S3FWRN5_RFREG_SECTION_SIZE;
		स_नकल(set_rfreg.data, fw->data+i, len);
		ret = nci_prop_cmd(info->ndev, NCI_PROP_SET_RFREG,
			len+1, (__u8 *)&set_rfreg);
		अगर (ret < 0) अणु
			dev_err(&info->ndev->nfc_dev->dev,
				"rfreg update error (code=%d)\n", ret);
			जाओ out;
		पूर्ण
		set_rfreg.index++;
	पूर्ण

	/* Finish rfreg configuration */

	stop_rfreg.checksum = checksum & 0xffff;
	ret = nci_prop_cmd(info->ndev, NCI_PROP_STOP_RFREG,
		माप(stop_rfreg), (__u8 *)&stop_rfreg);
	अगर (ret < 0) अणु
		dev_err(&info->ndev->nfc_dev->dev,
			"Unable to stop rfreg update\n");
		जाओ out;
	पूर्ण

	dev_info(&info->ndev->nfc_dev->dev,
		"rfreg configuration update: success\n");
out:
	release_firmware(fw);
	वापस ret;
पूर्ण
