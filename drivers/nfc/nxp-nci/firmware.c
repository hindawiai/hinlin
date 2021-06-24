<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Generic driver क्रम NXP NCI NFC chips
 *
 * Copyright (C) 2014  NXP Semiconductors  All rights reserved.
 *
 * Author: Clथऊment Perrochaud <clement.perrochaud@nxp.com>
 *
 * Derived from PN544 device driver:
 * Copyright (C) 2012  Intel Corporation. All rights reserved.
 */

#समावेश <linux/completion.h>
#समावेश <linux/firmware.h>
#समावेश <linux/nfc.h>
#समावेश <यंत्र/unaligned.h>

#समावेश "nxp-nci.h"

/* Crypto operations can take up to 30 seconds */
#घोषणा NXP_NCI_FW_ANSWER_TIMEOUT	msecs_to_jअगरfies(30000)

#घोषणा NXP_NCI_FW_CMD_RESET		0xF0
#घोषणा NXP_NCI_FW_CMD_GETVERSION	0xF1
#घोषणा NXP_NCI_FW_CMD_CHECKINTEGRITY	0xE0
#घोषणा NXP_NCI_FW_CMD_WRITE		0xC0
#घोषणा NXP_NCI_FW_CMD_READ		0xA2
#घोषणा NXP_NCI_FW_CMD_GETSESSIONSTATE	0xF2
#घोषणा NXP_NCI_FW_CMD_LOG		0xA7
#घोषणा NXP_NCI_FW_CMD_FORCE		0xD0
#घोषणा NXP_NCI_FW_CMD_GET_DIE_ID	0xF4

#घोषणा NXP_NCI_FW_CHUNK_FLAG	0x0400

#घोषणा NXP_NCI_FW_RESULT_OK				0x00
#घोषणा NXP_NCI_FW_RESULT_INVALID_ADDR			0x01
#घोषणा NXP_NCI_FW_RESULT_GENERIC_ERROR			0x02
#घोषणा NXP_NCI_FW_RESULT_UNKNOWN_CMD			0x0B
#घोषणा NXP_NCI_FW_RESULT_ABORTED_CMD			0x0C
#घोषणा NXP_NCI_FW_RESULT_PLL_ERROR			0x0D
#घोषणा NXP_NCI_FW_RESULT_ADDR_RANGE_OFL_ERROR		0x1E
#घोषणा NXP_NCI_FW_RESULT_BUFFER_OFL_ERROR		0x1F
#घोषणा NXP_NCI_FW_RESULT_MEM_BSY			0x20
#घोषणा NXP_NCI_FW_RESULT_SIGNATURE_ERROR		0x21
#घोषणा NXP_NCI_FW_RESULT_FIRMWARE_VERSION_ERROR	0x24
#घोषणा NXP_NCI_FW_RESULT_PROTOCOL_ERROR		0x28
#घोषणा NXP_NCI_FW_RESULT_SFWU_DEGRADED			0x2A
#घोषणा NXP_NCI_FW_RESULT_PH_STATUS_FIRST_CHUNK		0x2D
#घोषणा NXP_NCI_FW_RESULT_PH_STATUS_NEXT_CHUNK		0x2E
#घोषणा NXP_NCI_FW_RESULT_PH_STATUS_INTERNAL_ERROR_5	0xC5

व्योम nxp_nci_fw_work_complete(काष्ठा nxp_nci_info *info, पूर्णांक result)
अणु
	काष्ठा nxp_nci_fw_info *fw_info = &info->fw_info;
	पूर्णांक r;

	अगर (info->phy_ops->set_mode) अणु
		r = info->phy_ops->set_mode(info->phy_id, NXP_NCI_MODE_COLD);
		अगर (r < 0 && result == 0)
			result = -r;
	पूर्ण

	info->mode = NXP_NCI_MODE_COLD;

	अगर (fw_info->fw) अणु
		release_firmware(fw_info->fw);
		fw_info->fw = शून्य;
	पूर्ण

	nfc_fw_करोwnload_करोne(info->ndev->nfc_dev, fw_info->name, (u32) -result);
पूर्ण

/* crc_ccitt cannot be used since it is computed MSB first and not LSB first */
अटल u16 nxp_nci_fw_crc(u8 स्थिर *buffer, माप_प्रकार len)
अणु
	u16 crc = 0xffff;

	जबतक (len--) अणु
		crc = ((crc >> 8) | (crc << 8)) ^ *buffer++;
		crc ^= (crc & 0xff) >> 4;
		crc ^= (crc & 0xff) << 12;
		crc ^= (crc & 0xff) << 5;
	पूर्ण

	वापस crc;
पूर्ण

अटल पूर्णांक nxp_nci_fw_send_chunk(काष्ठा nxp_nci_info *info)
अणु
	काष्ठा nxp_nci_fw_info *fw_info = &info->fw_info;
	u16 header, crc;
	काष्ठा sk_buff *skb;
	माप_प्रकार chunk_len;
	माप_प्रकार reमुख्यing_len;
	पूर्णांक r;

	skb = nci_skb_alloc(info->ndev, info->max_payload, GFP_KERNEL);
	अगर (!skb) अणु
		r = -ENOMEM;
		जाओ chunk_निकास;
	पूर्ण

	chunk_len = info->max_payload - NXP_NCI_FW_HDR_LEN - NXP_NCI_FW_CRC_LEN;
	reमुख्यing_len = fw_info->frame_size - fw_info->written;

	अगर (reमुख्यing_len > chunk_len) अणु
		header = NXP_NCI_FW_CHUNK_FLAG;
	पूर्ण अन्यथा अणु
		chunk_len = reमुख्यing_len;
		header = 0x0000;
	पूर्ण

	header |= chunk_len & NXP_NCI_FW_FRAME_LEN_MASK;
	put_unaligned_be16(header, skb_put(skb, NXP_NCI_FW_HDR_LEN));

	skb_put_data(skb, fw_info->data + fw_info->written, chunk_len);

	crc = nxp_nci_fw_crc(skb->data, chunk_len + NXP_NCI_FW_HDR_LEN);
	put_unaligned_be16(crc, skb_put(skb, NXP_NCI_FW_CRC_LEN));

	r = info->phy_ops->ग_लिखो(info->phy_id, skb);
	अगर (r >= 0)
		r = chunk_len;

	kमुक्त_skb(skb);

chunk_निकास:
	वापस r;
पूर्ण

अटल पूर्णांक nxp_nci_fw_send(काष्ठा nxp_nci_info *info)
अणु
	काष्ठा nxp_nci_fw_info *fw_info = &info->fw_info;
	दीर्घ completion_rc;
	पूर्णांक r;

	reinit_completion(&fw_info->cmd_completion);

	अगर (fw_info->written == 0) अणु
		fw_info->frame_size = get_unaligned_be16(fw_info->data) &
				      NXP_NCI_FW_FRAME_LEN_MASK;
		fw_info->data += NXP_NCI_FW_HDR_LEN;
		fw_info->size -= NXP_NCI_FW_HDR_LEN;
	पूर्ण

	अगर (fw_info->frame_size > fw_info->size)
		वापस -EMSGSIZE;

	r = nxp_nci_fw_send_chunk(info);
	अगर (r < 0)
		वापस r;

	fw_info->written += r;

	अगर (*fw_info->data == NXP_NCI_FW_CMD_RESET) अणु
		fw_info->cmd_result = 0;
		अगर (fw_info->fw)
			schedule_work(&fw_info->work);
	पूर्ण अन्यथा अणु
		completion_rc = रुको_क्रम_completion_पूर्णांकerruptible_समयout(
			&fw_info->cmd_completion, NXP_NCI_FW_ANSWER_TIMEOUT);
		अगर (completion_rc == 0)
			वापस -ETIMEDOUT;
	पूर्ण

	वापस 0;
पूर्ण

व्योम nxp_nci_fw_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा nxp_nci_info *info;
	काष्ठा nxp_nci_fw_info *fw_info;
	पूर्णांक r;

	fw_info = container_of(work, काष्ठा nxp_nci_fw_info, work);
	info = container_of(fw_info, काष्ठा nxp_nci_info, fw_info);

	mutex_lock(&info->info_lock);

	r = fw_info->cmd_result;
	अगर (r < 0)
		जाओ निकास_work;

	अगर (fw_info->written == fw_info->frame_size) अणु
		fw_info->data += fw_info->frame_size;
		fw_info->size -= fw_info->frame_size;
		fw_info->written = 0;
	पूर्ण

	अगर (fw_info->size > 0)
		r = nxp_nci_fw_send(info);

निकास_work:
	अगर (r < 0 || fw_info->size == 0)
		nxp_nci_fw_work_complete(info, r);
	mutex_unlock(&info->info_lock);
पूर्ण

पूर्णांक nxp_nci_fw_करोwnload(काष्ठा nci_dev *ndev, स्थिर अक्षर *firmware_name)
अणु
	काष्ठा nxp_nci_info *info = nci_get_drvdata(ndev);
	काष्ठा nxp_nci_fw_info *fw_info = &info->fw_info;
	पूर्णांक r;

	mutex_lock(&info->info_lock);

	अगर (!info->phy_ops->set_mode || !info->phy_ops->ग_लिखो) अणु
		r = -ENOTSUPP;
		जाओ fw_करोwnload_निकास;
	पूर्ण

	अगर (!firmware_name || firmware_name[0] == '\0') अणु
		r = -EINVAL;
		जाओ fw_करोwnload_निकास;
	पूर्ण

	म_नकल(fw_info->name, firmware_name);

	r = request_firmware(&fw_info->fw, firmware_name,
			     ndev->nfc_dev->dev.parent);
	अगर (r < 0)
		जाओ fw_करोwnload_निकास;

	r = info->phy_ops->set_mode(info->phy_id, NXP_NCI_MODE_FW);
	अगर (r < 0) अणु
		release_firmware(fw_info->fw);
		जाओ fw_करोwnload_निकास;
	पूर्ण

	info->mode = NXP_NCI_MODE_FW;

	fw_info->data = fw_info->fw->data;
	fw_info->size = fw_info->fw->size;
	fw_info->written = 0;
	fw_info->frame_size = 0;
	fw_info->cmd_result = 0;

	schedule_work(&fw_info->work);

fw_करोwnload_निकास:
	mutex_unlock(&info->info_lock);
	वापस r;
पूर्ण

अटल पूर्णांक nxp_nci_fw_पढ़ो_status(u8 stat)
अणु
	चयन (stat) अणु
	हाल NXP_NCI_FW_RESULT_OK:
		वापस 0;
	हाल NXP_NCI_FW_RESULT_INVALID_ADDR:
		वापस -EINVAL;
	हाल NXP_NCI_FW_RESULT_UNKNOWN_CMD:
		वापस -EINVAL;
	हाल NXP_NCI_FW_RESULT_ABORTED_CMD:
		वापस -EMSGSIZE;
	हाल NXP_NCI_FW_RESULT_ADDR_RANGE_OFL_ERROR:
		वापस -EADDRNOTAVAIL;
	हाल NXP_NCI_FW_RESULT_BUFFER_OFL_ERROR:
		वापस -ENOBUFS;
	हाल NXP_NCI_FW_RESULT_MEM_BSY:
		वापस -ENOKEY;
	हाल NXP_NCI_FW_RESULT_SIGNATURE_ERROR:
		वापस -EKEYREJECTED;
	हाल NXP_NCI_FW_RESULT_FIRMWARE_VERSION_ERROR:
		वापस -EALREADY;
	हाल NXP_NCI_FW_RESULT_PROTOCOL_ERROR:
		वापस -EPROTO;
	हाल NXP_NCI_FW_RESULT_SFWU_DEGRADED:
		वापस -EHWPOISON;
	हाल NXP_NCI_FW_RESULT_PH_STATUS_FIRST_CHUNK:
		वापस 0;
	हाल NXP_NCI_FW_RESULT_PH_STATUS_NEXT_CHUNK:
		वापस 0;
	हाल NXP_NCI_FW_RESULT_PH_STATUS_INTERNAL_ERROR_5:
		वापस -EINVAL;
	शेष:
		वापस -EIO;
	पूर्ण
पूर्ण

अटल u16 nxp_nci_fw_check_crc(काष्ठा sk_buff *skb)
अणु
	u16 crc, frame_crc;
	माप_प्रकार len = skb->len - NXP_NCI_FW_CRC_LEN;

	crc = nxp_nci_fw_crc(skb->data, len);
	frame_crc = get_unaligned_be16(skb->data + len);

	वापस (crc ^ frame_crc);
पूर्ण

व्योम nxp_nci_fw_recv_frame(काष्ठा nci_dev *ndev, काष्ठा sk_buff *skb)
अणु
	काष्ठा nxp_nci_info *info = nci_get_drvdata(ndev);
	काष्ठा nxp_nci_fw_info *fw_info = &info->fw_info;

	complete(&fw_info->cmd_completion);

	अगर (skb) अणु
		अगर (nxp_nci_fw_check_crc(skb) != 0x00)
			fw_info->cmd_result = -EBADMSG;
		अन्यथा
			fw_info->cmd_result = nxp_nci_fw_पढ़ो_status(*(u8 *)skb_pull(skb, NXP_NCI_FW_HDR_LEN));
		kमुक्त_skb(skb);
	पूर्ण अन्यथा अणु
		fw_info->cmd_result = -EIO;
	पूर्ण

	अगर (fw_info->fw)
		schedule_work(&fw_info->work);
पूर्ण
EXPORT_SYMBOL(nxp_nci_fw_recv_frame);
