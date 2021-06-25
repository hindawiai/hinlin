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
#समावेश <crypto/hash.h>
#समावेश <crypto/sha1.h>

#समावेश "s3fwrn5.h"
#समावेश "firmware.h"

काष्ठा s3fwrn5_fw_version अणु
	__u8 major;
	__u8 build1;
	__u8 build2;
	__u8 target;
पूर्ण;

अटल पूर्णांक s3fwrn5_fw_send_msg(काष्ठा s3fwrn5_fw_info *fw_info,
	काष्ठा sk_buff *msg, काष्ठा sk_buff **rsp)
अणु
	काष्ठा s3fwrn5_info *info =
		container_of(fw_info, काष्ठा s3fwrn5_info, fw_info);
	दीर्घ ret;

	reinit_completion(&fw_info->completion);

	ret = s3fwrn5_ग_लिखो(info, msg);
	अगर (ret < 0)
		वापस ret;

	ret = रुको_क्रम_completion_पूर्णांकerruptible_समयout(
		&fw_info->completion, msecs_to_jअगरfies(1000));
	अगर (ret < 0)
		वापस ret;
	अन्यथा अगर (ret == 0)
		वापस -ENXIO;

	अगर (!fw_info->rsp)
		वापस -EINVAL;

	*rsp = fw_info->rsp;
	fw_info->rsp = शून्य;

	वापस 0;
पूर्ण

अटल पूर्णांक s3fwrn5_fw_prep_msg(काष्ठा s3fwrn5_fw_info *fw_info,
	काष्ठा sk_buff **msg, u8 type, u8 code, स्थिर व्योम *data, u16 len)
अणु
	काष्ठा s3fwrn5_fw_header hdr;
	काष्ठा sk_buff *skb;

	hdr.type = type | fw_info->parity;
	fw_info->parity ^= 0x80;
	hdr.code = code;
	hdr.len = len;

	skb = alloc_skb(S3FWRN5_FW_HDR_SIZE + len, GFP_KERNEL);
	अगर (!skb)
		वापस -ENOMEM;

	skb_put_data(skb, &hdr, S3FWRN5_FW_HDR_SIZE);
	अगर (len)
		skb_put_data(skb, data, len);

	*msg = skb;

	वापस 0;
पूर्ण

अटल पूर्णांक s3fwrn5_fw_get_bootinfo(काष्ठा s3fwrn5_fw_info *fw_info,
	काष्ठा s3fwrn5_fw_cmd_get_bootinfo_rsp *bootinfo)
अणु
	काष्ठा sk_buff *msg, *rsp = शून्य;
	काष्ठा s3fwrn5_fw_header *hdr;
	पूर्णांक ret;

	/* Send GET_BOOTINFO command */

	ret = s3fwrn5_fw_prep_msg(fw_info, &msg, S3FWRN5_FW_MSG_CMD,
		S3FWRN5_FW_CMD_GET_BOOTINFO, शून्य, 0);
	अगर (ret < 0)
		वापस ret;

	ret = s3fwrn5_fw_send_msg(fw_info, msg, &rsp);
	kमुक्त_skb(msg);
	अगर (ret < 0)
		वापस ret;

	hdr = (काष्ठा s3fwrn5_fw_header *) rsp->data;
	अगर (hdr->code != S3FWRN5_FW_RET_SUCCESS) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	स_नकल(bootinfo, rsp->data + S3FWRN5_FW_HDR_SIZE, 10);

out:
	kमुक्त_skb(rsp);
	वापस ret;
पूर्ण

अटल पूर्णांक s3fwrn5_fw_enter_update_mode(काष्ठा s3fwrn5_fw_info *fw_info,
	स्थिर व्योम *hash_data, u16 hash_size,
	स्थिर व्योम *sig_data, u16 sig_size)
अणु
	काष्ठा s3fwrn5_fw_cmd_enter_updatemode args;
	काष्ठा sk_buff *msg, *rsp = शून्य;
	काष्ठा s3fwrn5_fw_header *hdr;
	पूर्णांक ret;

	/* Send ENTER_UPDATE_MODE command */

	args.hashcode_size = hash_size;
	args.signature_size = sig_size;

	ret = s3fwrn5_fw_prep_msg(fw_info, &msg, S3FWRN5_FW_MSG_CMD,
		S3FWRN5_FW_CMD_ENTER_UPDATE_MODE, &args, माप(args));
	अगर (ret < 0)
		वापस ret;

	ret = s3fwrn5_fw_send_msg(fw_info, msg, &rsp);
	kमुक्त_skb(msg);
	अगर (ret < 0)
		वापस ret;

	hdr = (काष्ठा s3fwrn5_fw_header *) rsp->data;
	अगर (hdr->code != S3FWRN5_FW_RET_SUCCESS) अणु
		ret = -EPROTO;
		जाओ out;
	पूर्ण

	kमुक्त_skb(rsp);

	/* Send hashcode data */

	ret = s3fwrn5_fw_prep_msg(fw_info, &msg, S3FWRN5_FW_MSG_DATA, 0,
		hash_data, hash_size);
	अगर (ret < 0)
		वापस ret;

	ret = s3fwrn5_fw_send_msg(fw_info, msg, &rsp);
	kमुक्त_skb(msg);
	अगर (ret < 0)
		वापस ret;

	hdr = (काष्ठा s3fwrn5_fw_header *) rsp->data;
	अगर (hdr->code != S3FWRN5_FW_RET_SUCCESS) अणु
		ret = -EPROTO;
		जाओ out;
	पूर्ण

	kमुक्त_skb(rsp);

	/* Send signature data */

	ret = s3fwrn5_fw_prep_msg(fw_info, &msg, S3FWRN5_FW_MSG_DATA, 0,
		sig_data, sig_size);
	अगर (ret < 0)
		वापस ret;

	ret = s3fwrn5_fw_send_msg(fw_info, msg, &rsp);
	kमुक्त_skb(msg);
	अगर (ret < 0)
		वापस ret;

	hdr = (काष्ठा s3fwrn5_fw_header *) rsp->data;
	अगर (hdr->code != S3FWRN5_FW_RET_SUCCESS)
		ret = -EPROTO;

out:
	kमुक्त_skb(rsp);
	वापस ret;
पूर्ण

अटल पूर्णांक s3fwrn5_fw_update_sector(काष्ठा s3fwrn5_fw_info *fw_info,
	u32 base_addr, स्थिर व्योम *data)
अणु
	काष्ठा s3fwrn5_fw_cmd_update_sector args;
	काष्ठा sk_buff *msg, *rsp = शून्य;
	काष्ठा s3fwrn5_fw_header *hdr;
	पूर्णांक ret, i;

	/* Send UPDATE_SECTOR command */

	args.base_address = base_addr;

	ret = s3fwrn5_fw_prep_msg(fw_info, &msg, S3FWRN5_FW_MSG_CMD,
		S3FWRN5_FW_CMD_UPDATE_SECTOR, &args, माप(args));
	अगर (ret < 0)
		वापस ret;

	ret = s3fwrn5_fw_send_msg(fw_info, msg, &rsp);
	kमुक्त_skb(msg);
	अगर (ret < 0)
		वापस ret;

	hdr = (काष्ठा s3fwrn5_fw_header *) rsp->data;
	अगर (hdr->code != S3FWRN5_FW_RET_SUCCESS) अणु
		ret = -EPROTO;
		जाओ err;
	पूर्ण

	kमुक्त_skb(rsp);

	/* Send data split पूर्णांकo 256-byte packets */

	क्रम (i = 0; i < 16; ++i) अणु
		ret = s3fwrn5_fw_prep_msg(fw_info, &msg,
			S3FWRN5_FW_MSG_DATA, 0, data+256*i, 256);
		अगर (ret < 0)
			अवरोध;

		ret = s3fwrn5_fw_send_msg(fw_info, msg, &rsp);
		kमुक्त_skb(msg);
		अगर (ret < 0)
			अवरोध;

		hdr = (काष्ठा s3fwrn5_fw_header *) rsp->data;
		अगर (hdr->code != S3FWRN5_FW_RET_SUCCESS) अणु
			ret = -EPROTO;
			जाओ err;
		पूर्ण

		kमुक्त_skb(rsp);
	पूर्ण

	वापस ret;

err:
	kमुक्त_skb(rsp);
	वापस ret;
पूर्ण

अटल पूर्णांक s3fwrn5_fw_complete_update_mode(काष्ठा s3fwrn5_fw_info *fw_info)
अणु
	काष्ठा sk_buff *msg, *rsp = शून्य;
	काष्ठा s3fwrn5_fw_header *hdr;
	पूर्णांक ret;

	/* Send COMPLETE_UPDATE_MODE command */

	ret = s3fwrn5_fw_prep_msg(fw_info, &msg, S3FWRN5_FW_MSG_CMD,
		S3FWRN5_FW_CMD_COMPLETE_UPDATE_MODE, शून्य, 0);
	अगर (ret < 0)
		वापस ret;

	ret = s3fwrn5_fw_send_msg(fw_info, msg, &rsp);
	kमुक्त_skb(msg);
	अगर (ret < 0)
		वापस ret;

	hdr = (काष्ठा s3fwrn5_fw_header *) rsp->data;
	अगर (hdr->code != S3FWRN5_FW_RET_SUCCESS)
		ret = -EPROTO;

	kमुक्त_skb(rsp);

	वापस ret;
पूर्ण

/*
 * Firmware header काष्ठाure:
 *
 * 0x00 - 0x0B : Date and समय string (w/o NUL termination)
 * 0x10 - 0x13 : Firmware version
 * 0x14 - 0x17 : Signature address
 * 0x18 - 0x1B : Signature size
 * 0x1C - 0x1F : Firmware image address
 * 0x20 - 0x23 : Firmware sectors count
 * 0x24 - 0x27 : Custom signature address
 * 0x28 - 0x2B : Custom signature size
 */

#घोषणा S3FWRN5_FW_IMAGE_HEADER_SIZE 44

पूर्णांक s3fwrn5_fw_request_firmware(काष्ठा s3fwrn5_fw_info *fw_info)
अणु
	काष्ठा s3fwrn5_fw_image *fw = &fw_info->fw;
	u32 sig_off;
	u32 image_off;
	u32 custom_sig_off;
	पूर्णांक ret;

	ret = request_firmware(&fw->fw, fw_info->fw_name,
		&fw_info->ndev->nfc_dev->dev);
	अगर (ret < 0)
		वापस ret;

	अगर (fw->fw->size < S3FWRN5_FW_IMAGE_HEADER_SIZE) अणु
		release_firmware(fw->fw);
		वापस -EINVAL;
	पूर्ण

	स_नकल(fw->date, fw->fw->data + 0x00, 12);
	fw->date[12] = '\0';

	स_नकल(&fw->version, fw->fw->data + 0x10, 4);

	स_नकल(&sig_off, fw->fw->data + 0x14, 4);
	fw->sig = fw->fw->data + sig_off;
	स_नकल(&fw->sig_size, fw->fw->data + 0x18, 4);

	स_नकल(&image_off, fw->fw->data + 0x1C, 4);
	fw->image = fw->fw->data + image_off;
	स_नकल(&fw->image_sectors, fw->fw->data + 0x20, 4);

	स_नकल(&custom_sig_off, fw->fw->data + 0x24, 4);
	fw->custom_sig = fw->fw->data + custom_sig_off;
	स_नकल(&fw->custom_sig_size, fw->fw->data + 0x28, 4);

	वापस 0;
पूर्ण

अटल व्योम s3fwrn5_fw_release_firmware(काष्ठा s3fwrn5_fw_info *fw_info)
अणु
	release_firmware(fw_info->fw.fw);
पूर्ण

अटल पूर्णांक s3fwrn5_fw_get_base_addr(
	काष्ठा s3fwrn5_fw_cmd_get_bootinfo_rsp *bootinfo, u32 *base_addr)
अणु
	पूर्णांक i;
	अटल स्थिर काष्ठा अणु
		u8 version[4];
		u32 base_addr;
	पूर्ण match[] = अणु
		अणुअणु0x05, 0x00, 0x00, 0x00पूर्ण, 0x00005000पूर्ण,
		अणुअणु0x05, 0x00, 0x00, 0x01पूर्ण, 0x00003000पूर्ण,
		अणुअणु0x05, 0x00, 0x00, 0x02पूर्ण, 0x00003000पूर्ण,
		अणुअणु0x05, 0x00, 0x00, 0x03पूर्ण, 0x00003000पूर्ण,
		अणुअणु0x05, 0x00, 0x00, 0x05पूर्ण, 0x00003000पूर्ण
	पूर्ण;

	क्रम (i = 0; i < ARRAY_SIZE(match); ++i)
		अगर (bootinfo->hw_version[0] == match[i].version[0] &&
			bootinfo->hw_version[1] == match[i].version[1] &&
			bootinfo->hw_version[3] == match[i].version[3]) अणु
			*base_addr = match[i].base_addr;
			वापस 0;
		पूर्ण

	वापस -EINVAL;
पूर्ण

अटल अंतरभूत bool
s3fwrn5_fw_is_custom(स्थिर काष्ठा s3fwrn5_fw_cmd_get_bootinfo_rsp *bootinfo)
अणु
	वापस !!bootinfo->hw_version[2];
पूर्ण

पूर्णांक s3fwrn5_fw_setup(काष्ठा s3fwrn5_fw_info *fw_info)
अणु
	काष्ठा s3fwrn5_fw_cmd_get_bootinfo_rsp bootinfo;
	पूर्णांक ret;

	/* Get bootloader info */

	ret = s3fwrn5_fw_get_bootinfo(fw_info, &bootinfo);
	अगर (ret < 0) अणु
		dev_err(&fw_info->ndev->nfc_dev->dev,
			"Failed to get bootinfo, ret=%02x\n", ret);
		जाओ err;
	पूर्ण

	/* Match hardware version to obtain firmware base address */

	ret = s3fwrn5_fw_get_base_addr(&bootinfo, &fw_info->base_addr);
	अगर (ret < 0) अणु
		dev_err(&fw_info->ndev->nfc_dev->dev,
			"Unknown hardware version\n");
		जाओ err;
	पूर्ण

	fw_info->sector_size = bootinfo.sector_size;

	fw_info->sig_size = s3fwrn5_fw_is_custom(&bootinfo) ?
		fw_info->fw.custom_sig_size : fw_info->fw.sig_size;
	fw_info->sig = s3fwrn5_fw_is_custom(&bootinfo) ?
		fw_info->fw.custom_sig : fw_info->fw.sig;

	वापस 0;

err:
	s3fwrn5_fw_release_firmware(fw_info);
	वापस ret;
पूर्ण

bool s3fwrn5_fw_check_version(स्थिर काष्ठा s3fwrn5_fw_info *fw_info, u32 version)
अणु
	काष्ठा s3fwrn5_fw_version *new = (व्योम *) &fw_info->fw.version;
	काष्ठा s3fwrn5_fw_version *old = (व्योम *) &version;

	अगर (new->major > old->major)
		वापस true;
	अगर (new->build1 > old->build1)
		वापस true;
	अगर (new->build2 > old->build2)
		वापस true;

	वापस false;
पूर्ण

पूर्णांक s3fwrn5_fw_करोwnload(काष्ठा s3fwrn5_fw_info *fw_info)
अणु
	काष्ठा s3fwrn5_fw_image *fw = &fw_info->fw;
	u8 hash_data[SHA1_DIGEST_SIZE];
	काष्ठा crypto_shash *tfm;
	u32 image_size, off;
	पूर्णांक ret;

	image_size = fw_info->sector_size * fw->image_sectors;

	/* Compute SHA of firmware data */

	tfm = crypto_alloc_shash("sha1", 0, 0);
	अगर (IS_ERR(tfm)) अणु
		ret = PTR_ERR(tfm);
		dev_err(&fw_info->ndev->nfc_dev->dev,
			"Cannot allocate shash (code=%d)\n", ret);
		जाओ out;
	पूर्ण

	ret = crypto_shash_tfm_digest(tfm, fw->image, image_size, hash_data);

	crypto_मुक्त_shash(tfm);
	अगर (ret) अणु
		dev_err(&fw_info->ndev->nfc_dev->dev,
			"Cannot compute hash (code=%d)\n", ret);
		जाओ out;
	पूर्ण

	/* Firmware update process */

	dev_info(&fw_info->ndev->nfc_dev->dev,
		"Firmware update: %s\n", fw_info->fw_name);

	ret = s3fwrn5_fw_enter_update_mode(fw_info, hash_data,
		SHA1_DIGEST_SIZE, fw_info->sig, fw_info->sig_size);
	अगर (ret < 0) अणु
		dev_err(&fw_info->ndev->nfc_dev->dev,
			"Unable to enter update mode\n");
		जाओ out;
	पूर्ण

	क्रम (off = 0; off < image_size; off += fw_info->sector_size) अणु
		ret = s3fwrn5_fw_update_sector(fw_info,
			fw_info->base_addr + off, fw->image + off);
		अगर (ret < 0) अणु
			dev_err(&fw_info->ndev->nfc_dev->dev,
				"Firmware update error (code=%d)\n", ret);
			जाओ out;
		पूर्ण
	पूर्ण

	ret = s3fwrn5_fw_complete_update_mode(fw_info);
	अगर (ret < 0) अणु
		dev_err(&fw_info->ndev->nfc_dev->dev,
			"Unable to complete update mode\n");
		जाओ out;
	पूर्ण

	dev_info(&fw_info->ndev->nfc_dev->dev,
		"Firmware update: success\n");

out:
	वापस ret;
पूर्ण

व्योम s3fwrn5_fw_init(काष्ठा s3fwrn5_fw_info *fw_info, स्थिर अक्षर *fw_name)
अणु
	fw_info->parity = 0x00;
	fw_info->rsp = शून्य;
	fw_info->fw.fw = शून्य;
	म_नकल(fw_info->fw_name, fw_name);
	init_completion(&fw_info->completion);
पूर्ण

व्योम s3fwrn5_fw_cleanup(काष्ठा s3fwrn5_fw_info *fw_info)
अणु
	s3fwrn5_fw_release_firmware(fw_info);
पूर्ण

पूर्णांक s3fwrn5_fw_recv_frame(काष्ठा nci_dev *ndev, काष्ठा sk_buff *skb)
अणु
	काष्ठा s3fwrn5_info *info = nci_get_drvdata(ndev);
	काष्ठा s3fwrn5_fw_info *fw_info = &info->fw_info;

	अगर (WARN_ON(fw_info->rsp)) अणु
		kमुक्त_skb(skb);
		वापस -EINVAL;
	पूर्ण

	fw_info->rsp = skb;

	complete(&fw_info->completion);

	वापस 0;
पूर्ण
