<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *
 *  Bluetooth support क्रम Intel devices
 *
 *  Copyright (C) 2015  Intel Corporation
 */

#समावेश <linux/module.h>
#समावेश <linux/firmware.h>
#समावेश <linux/regmap.h>
#समावेश <यंत्र/unaligned.h>

#समावेश <net/bluetooth/bluetooth.h>
#समावेश <net/bluetooth/hci_core.h>

#समावेश "btintel.h"

#घोषणा VERSION "0.1"

#घोषणा BDADDR_INTEL		(&(bdaddr_t)अणुअणु0x00, 0x8b, 0x9e, 0x19, 0x03, 0x00पूर्णपूर्ण)
#घोषणा RSA_HEADER_LEN		644
#घोषणा CSS_HEADER_OFFSET	8
#घोषणा ECDSA_OFFSET		644
#घोषणा ECDSA_HEADER_LEN	320

#घोषणा CMD_WRITE_BOOT_PARAMS	0xfc0e
काष्ठा cmd_ग_लिखो_boot_params अणु
	u32 boot_addr;
	u8  fw_build_num;
	u8  fw_build_ww;
	u8  fw_build_yy;
पूर्ण __packed;

पूर्णांक btपूर्णांकel_check_bdaddr(काष्ठा hci_dev *hdev)
अणु
	काष्ठा hci_rp_पढ़ो_bd_addr *bda;
	काष्ठा sk_buff *skb;

	skb = __hci_cmd_sync(hdev, HCI_OP_READ_BD_ADDR, 0, शून्य,
			     HCI_INIT_TIMEOUT);
	अगर (IS_ERR(skb)) अणु
		पूर्णांक err = PTR_ERR(skb);
		bt_dev_err(hdev, "Reading Intel device address failed (%d)",
			   err);
		वापस err;
	पूर्ण

	अगर (skb->len != माप(*bda)) अणु
		bt_dev_err(hdev, "Intel device address length mismatch");
		kमुक्त_skb(skb);
		वापस -EIO;
	पूर्ण

	bda = (काष्ठा hci_rp_पढ़ो_bd_addr *)skb->data;

	/* For some Intel based controllers, the शेष Bluetooth device
	 * address 00:03:19:9E:8B:00 can be found. These controllers are
	 * fully operational, but have the danger of duplicate addresses
	 * and that in turn can cause problems with Bluetooth operation.
	 */
	अगर (!bacmp(&bda->bdaddr, BDADDR_INTEL)) अणु
		bt_dev_err(hdev, "Found Intel default device address (%pMR)",
			   &bda->bdaddr);
		set_bit(HCI_QUIRK_INVALID_BDADDR, &hdev->quirks);
	पूर्ण

	kमुक्त_skb(skb);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(btपूर्णांकel_check_bdaddr);

पूर्णांक btपूर्णांकel_enter_mfg(काष्ठा hci_dev *hdev)
अणु
	अटल स्थिर u8 param[] = अणु 0x01, 0x00 पूर्ण;
	काष्ठा sk_buff *skb;

	skb = __hci_cmd_sync(hdev, 0xfc11, 2, param, HCI_CMD_TIMEOUT);
	अगर (IS_ERR(skb)) अणु
		bt_dev_err(hdev, "Entering manufacturer mode failed (%ld)",
			   PTR_ERR(skb));
		वापस PTR_ERR(skb);
	पूर्ण
	kमुक्त_skb(skb);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(btपूर्णांकel_enter_mfg);

पूर्णांक btपूर्णांकel_निकास_mfg(काष्ठा hci_dev *hdev, bool reset, bool patched)
अणु
	u8 param[] = अणु 0x00, 0x00 पूर्ण;
	काष्ठा sk_buff *skb;

	/* The 2nd command parameter specअगरies the manufacturing निकास method:
	 * 0x00: Just disable the manufacturing mode (0x00).
	 * 0x01: Disable manufacturing mode and reset with patches deactivated.
	 * 0x02: Disable manufacturing mode and reset with patches activated.
	 */
	अगर (reset)
		param[1] |= patched ? 0x02 : 0x01;

	skb = __hci_cmd_sync(hdev, 0xfc11, 2, param, HCI_CMD_TIMEOUT);
	अगर (IS_ERR(skb)) अणु
		bt_dev_err(hdev, "Exiting manufacturer mode failed (%ld)",
			   PTR_ERR(skb));
		वापस PTR_ERR(skb);
	पूर्ण
	kमुक्त_skb(skb);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(btपूर्णांकel_निकास_mfg);

पूर्णांक btपूर्णांकel_set_bdaddr(काष्ठा hci_dev *hdev, स्थिर bdaddr_t *bdaddr)
अणु
	काष्ठा sk_buff *skb;
	पूर्णांक err;

	skb = __hci_cmd_sync(hdev, 0xfc31, 6, bdaddr, HCI_INIT_TIMEOUT);
	अगर (IS_ERR(skb)) अणु
		err = PTR_ERR(skb);
		bt_dev_err(hdev, "Changing Intel device address failed (%d)",
			   err);
		वापस err;
	पूर्ण
	kमुक्त_skb(skb);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(btपूर्णांकel_set_bdaddr);

पूर्णांक btपूर्णांकel_set_diag(काष्ठा hci_dev *hdev, bool enable)
अणु
	काष्ठा sk_buff *skb;
	u8 param[3];
	पूर्णांक err;

	अगर (enable) अणु
		param[0] = 0x03;
		param[1] = 0x03;
		param[2] = 0x03;
	पूर्ण अन्यथा अणु
		param[0] = 0x00;
		param[1] = 0x00;
		param[2] = 0x00;
	पूर्ण

	skb = __hci_cmd_sync(hdev, 0xfc43, 3, param, HCI_INIT_TIMEOUT);
	अगर (IS_ERR(skb)) अणु
		err = PTR_ERR(skb);
		अगर (err == -ENODATA)
			जाओ करोne;
		bt_dev_err(hdev, "Changing Intel diagnostic mode failed (%d)",
			   err);
		वापस err;
	पूर्ण
	kमुक्त_skb(skb);

करोne:
	btपूर्णांकel_set_event_mask(hdev, enable);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(btपूर्णांकel_set_diag);

पूर्णांक btपूर्णांकel_set_diag_mfg(काष्ठा hci_dev *hdev, bool enable)
अणु
	पूर्णांक err, ret;

	err = btपूर्णांकel_enter_mfg(hdev);
	अगर (err)
		वापस err;

	ret = btपूर्णांकel_set_diag(hdev, enable);

	err = btपूर्णांकel_निकास_mfg(hdev, false, false);
	अगर (err)
		वापस err;

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(btपूर्णांकel_set_diag_mfg);

व्योम btपूर्णांकel_hw_error(काष्ठा hci_dev *hdev, u8 code)
अणु
	काष्ठा sk_buff *skb;
	u8 type = 0x00;

	bt_dev_err(hdev, "Hardware error 0x%2.2x", code);

	skb = __hci_cmd_sync(hdev, HCI_OP_RESET, 0, शून्य, HCI_INIT_TIMEOUT);
	अगर (IS_ERR(skb)) अणु
		bt_dev_err(hdev, "Reset after hardware error failed (%ld)",
			   PTR_ERR(skb));
		वापस;
	पूर्ण
	kमुक्त_skb(skb);

	skb = __hci_cmd_sync(hdev, 0xfc22, 1, &type, HCI_INIT_TIMEOUT);
	अगर (IS_ERR(skb)) अणु
		bt_dev_err(hdev, "Retrieving Intel exception info failed (%ld)",
			   PTR_ERR(skb));
		वापस;
	पूर्ण

	अगर (skb->len != 13) अणु
		bt_dev_err(hdev, "Exception info size mismatch");
		kमुक्त_skb(skb);
		वापस;
	पूर्ण

	bt_dev_err(hdev, "Exception info %s", (अक्षर *)(skb->data + 1));

	kमुक्त_skb(skb);
पूर्ण
EXPORT_SYMBOL_GPL(btपूर्णांकel_hw_error);

पूर्णांक btपूर्णांकel_version_info(काष्ठा hci_dev *hdev, काष्ठा पूर्णांकel_version *ver)
अणु
	स्थिर अक्षर *variant;

	/* The hardware platक्रमm number has a fixed value of 0x37 and
	 * क्रम now only accept this single value.
	 */
	अगर (ver->hw_platक्रमm != 0x37) अणु
		bt_dev_err(hdev, "Unsupported Intel hardware platform (%u)",
			   ver->hw_platक्रमm);
		वापस -EINVAL;
	पूर्ण

	/* Check क्रम supported iBT hardware variants of this firmware
	 * loading method.
	 *
	 * This check has been put in place to ensure correct क्रमward
	 * compatibility options when newer hardware variants come aदीर्घ.
	 */
	चयन (ver->hw_variant) अणु
	हाल 0x0b:      /* SfP */
	हाल 0x0c:      /* WsP */
	हाल 0x11:      /* JfP */
	हाल 0x12:      /* ThP */
	हाल 0x13:      /* HrP */
	हाल 0x14:      /* CcP */
		अवरोध;
	शेष:
		bt_dev_err(hdev, "Unsupported Intel hardware variant (%u)",
			   ver->hw_variant);
		वापस -EINVAL;
	पूर्ण

	चयन (ver->fw_variant) अणु
	हाल 0x06:
		variant = "Bootloader";
		अवरोध;
	हाल 0x23:
		variant = "Firmware";
		अवरोध;
	शेष:
		bt_dev_err(hdev, "Unsupported firmware variant(%02x)", ver->fw_variant);
		वापस -EINVAL;
	पूर्ण

	bt_dev_info(hdev, "%s revision %u.%u build %u week %u %u",
		    variant, ver->fw_revision >> 4, ver->fw_revision & 0x0f,
		    ver->fw_build_num, ver->fw_build_ww,
		    2000 + ver->fw_build_yy);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(btपूर्णांकel_version_info);

पूर्णांक btपूर्णांकel_secure_send(काष्ठा hci_dev *hdev, u8 fragment_type, u32 plen,
			स्थिर व्योम *param)
अणु
	जबतक (plen > 0) अणु
		काष्ठा sk_buff *skb;
		u8 cmd_param[253], fragment_len = (plen > 252) ? 252 : plen;

		cmd_param[0] = fragment_type;
		स_नकल(cmd_param + 1, param, fragment_len);

		skb = __hci_cmd_sync(hdev, 0xfc09, fragment_len + 1,
				     cmd_param, HCI_INIT_TIMEOUT);
		अगर (IS_ERR(skb))
			वापस PTR_ERR(skb);

		kमुक्त_skb(skb);

		plen -= fragment_len;
		param += fragment_len;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(btपूर्णांकel_secure_send);

पूर्णांक btपूर्णांकel_load_ddc_config(काष्ठा hci_dev *hdev, स्थिर अक्षर *ddc_name)
अणु
	स्थिर काष्ठा firmware *fw;
	काष्ठा sk_buff *skb;
	स्थिर u8 *fw_ptr;
	पूर्णांक err;

	err = request_firmware_direct(&fw, ddc_name, &hdev->dev);
	अगर (err < 0) अणु
		bt_dev_err(hdev, "Failed to load Intel DDC file %s (%d)",
			   ddc_name, err);
		वापस err;
	पूर्ण

	bt_dev_info(hdev, "Found Intel DDC parameters: %s", ddc_name);

	fw_ptr = fw->data;

	/* DDC file contains one or more DDC काष्ठाure which has
	 * Length (1 byte), DDC ID (2 bytes), and DDC value (Length - 2).
	 */
	जबतक (fw->size > fw_ptr - fw->data) अणु
		u8 cmd_plen = fw_ptr[0] + माप(u8);

		skb = __hci_cmd_sync(hdev, 0xfc8b, cmd_plen, fw_ptr,
				     HCI_INIT_TIMEOUT);
		अगर (IS_ERR(skb)) अणु
			bt_dev_err(hdev, "Failed to send Intel_Write_DDC (%ld)",
				   PTR_ERR(skb));
			release_firmware(fw);
			वापस PTR_ERR(skb);
		पूर्ण

		fw_ptr += cmd_plen;
		kमुक्त_skb(skb);
	पूर्ण

	release_firmware(fw);

	bt_dev_info(hdev, "Applying Intel DDC parameters completed");

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(btपूर्णांकel_load_ddc_config);

पूर्णांक btपूर्णांकel_set_event_mask(काष्ठा hci_dev *hdev, bool debug)
अणु
	u8 mask[8] = अणु 0x87, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 पूर्ण;
	काष्ठा sk_buff *skb;
	पूर्णांक err;

	अगर (debug)
		mask[1] |= 0x62;

	skb = __hci_cmd_sync(hdev, 0xfc52, 8, mask, HCI_INIT_TIMEOUT);
	अगर (IS_ERR(skb)) अणु
		err = PTR_ERR(skb);
		bt_dev_err(hdev, "Setting Intel event mask failed (%d)", err);
		वापस err;
	पूर्ण
	kमुक्त_skb(skb);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(btपूर्णांकel_set_event_mask);

पूर्णांक btपूर्णांकel_set_event_mask_mfg(काष्ठा hci_dev *hdev, bool debug)
अणु
	पूर्णांक err, ret;

	err = btपूर्णांकel_enter_mfg(hdev);
	अगर (err)
		वापस err;

	ret = btपूर्णांकel_set_event_mask(hdev, debug);

	err = btपूर्णांकel_निकास_mfg(hdev, false, false);
	अगर (err)
		वापस err;

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(btपूर्णांकel_set_event_mask_mfg);

पूर्णांक btपूर्णांकel_पढ़ो_version(काष्ठा hci_dev *hdev, काष्ठा पूर्णांकel_version *ver)
अणु
	काष्ठा sk_buff *skb;

	skb = __hci_cmd_sync(hdev, 0xfc05, 0, शून्य, HCI_CMD_TIMEOUT);
	अगर (IS_ERR(skb)) अणु
		bt_dev_err(hdev, "Reading Intel version information failed (%ld)",
			   PTR_ERR(skb));
		वापस PTR_ERR(skb);
	पूर्ण

	अगर (skb->len != माप(*ver)) अणु
		bt_dev_err(hdev, "Intel version event size mismatch");
		kमुक्त_skb(skb);
		वापस -EILSEQ;
	पूर्ण

	स_नकल(ver, skb->data, माप(*ver));

	kमुक्त_skb(skb);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(btपूर्णांकel_पढ़ो_version);

पूर्णांक btपूर्णांकel_version_info_tlv(काष्ठा hci_dev *hdev, काष्ठा पूर्णांकel_version_tlv *version)
अणु
	स्थिर अक्षर *variant;

	/* The hardware platक्रमm number has a fixed value of 0x37 and
	 * क्रम now only accept this single value.
	 */
	अगर (INTEL_HW_PLATFORM(version->cnvi_bt) != 0x37) अणु
		bt_dev_err(hdev, "Unsupported Intel hardware platform (0x%2x)",
			   INTEL_HW_PLATFORM(version->cnvi_bt));
		वापस -EINVAL;
	पूर्ण

	/* Check क्रम supported iBT hardware variants of this firmware
	 * loading method.
	 *
	 * This check has been put in place to ensure correct क्रमward
	 * compatibility options when newer hardware variants come aदीर्घ.
	 */
	चयन (INTEL_HW_VARIANT(version->cnvi_bt)) अणु
	हाल 0x17:	/* TyP */
	हाल 0x18:	/* Slr */
	हाल 0x19:	/* Slr-F */
		अवरोध;
	शेष:
		bt_dev_err(hdev, "Unsupported Intel hardware variant (0x%x)",
			   INTEL_HW_VARIANT(version->cnvi_bt));
		वापस -EINVAL;
	पूर्ण

	चयन (version->img_type) अणु
	हाल 0x01:
		variant = "Bootloader";
		/* It is required that every single firmware fragment is acknowledged
		 * with a command complete event. If the boot parameters indicate
		 * that this bootloader करोes not send them, then पात the setup.
		 */
		अगर (version->limited_cce != 0x00) अणु
			bt_dev_err(hdev, "Unsupported Intel firmware loading method (0x%x)",
				   version->limited_cce);
			वापस -EINVAL;
		पूर्ण

		/* Secure boot engine type should be either 1 (ECDSA) or 0 (RSA) */
		अगर (version->sbe_type > 0x01) अणु
			bt_dev_err(hdev, "Unsupported Intel secure boot engine type (0x%x)",
				   version->sbe_type);
			वापस -EINVAL;
		पूर्ण

		bt_dev_info(hdev, "Device revision is %u", version->dev_rev_id);
		bt_dev_info(hdev, "Secure boot is %s",
			    version->secure_boot ? "enabled" : "disabled");
		bt_dev_info(hdev, "OTP lock is %s",
			    version->otp_lock ? "enabled" : "disabled");
		bt_dev_info(hdev, "API lock is %s",
			    version->api_lock ? "enabled" : "disabled");
		bt_dev_info(hdev, "Debug lock is %s",
			    version->debug_lock ? "enabled" : "disabled");
		bt_dev_info(hdev, "Minimum firmware build %u week %u %u",
			    version->min_fw_build_nn, version->min_fw_build_cw,
			    2000 + version->min_fw_build_yy);
		अवरोध;
	हाल 0x03:
		variant = "Firmware";
		अवरोध;
	शेष:
		bt_dev_err(hdev, "Unsupported image type(%02x)", version->img_type);
		वापस -EINVAL;
	पूर्ण

	bt_dev_info(hdev, "%s timestamp %u.%u buildtype %u build %u", variant,
		    2000 + (version->बारtamp >> 8), version->बारtamp & 0xff,
		    version->build_type, version->build_num);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(btपूर्णांकel_version_info_tlv);

पूर्णांक btपूर्णांकel_पढ़ो_version_tlv(काष्ठा hci_dev *hdev, काष्ठा पूर्णांकel_version_tlv *version)
अणु
	काष्ठा sk_buff *skb;
	स्थिर u8 param[1] = अणु 0xFF पूर्ण;

	अगर (!version)
		वापस -EINVAL;

	skb = __hci_cmd_sync(hdev, 0xfc05, 1, param, HCI_CMD_TIMEOUT);
	अगर (IS_ERR(skb)) अणु
		bt_dev_err(hdev, "Reading Intel version information failed (%ld)",
			   PTR_ERR(skb));
		वापस PTR_ERR(skb);
	पूर्ण

	अगर (skb->data[0]) अणु
		bt_dev_err(hdev, "Intel Read Version command failed (%02x)",
			   skb->data[0]);
		kमुक्त_skb(skb);
		वापस -EIO;
	पूर्ण

	/* Consume Command Complete Status field */
	skb_pull(skb, 1);

	/* Event parameters contatin multiple TLVs. Read each of them
	 * and only keep the required data. Also, it use existing legacy
	 * version field like hw_platक्रमm, hw_variant, and fw_variant
	 * to keep the existing setup flow
	 */
	जबतक (skb->len) अणु
		काष्ठा पूर्णांकel_tlv *tlv;

		tlv = (काष्ठा पूर्णांकel_tlv *)skb->data;
		चयन (tlv->type) अणु
		हाल INTEL_TLV_CNVI_TOP:
			version->cnvi_top = get_unaligned_le32(tlv->val);
			अवरोध;
		हाल INTEL_TLV_CNVR_TOP:
			version->cnvr_top = get_unaligned_le32(tlv->val);
			अवरोध;
		हाल INTEL_TLV_CNVI_BT:
			version->cnvi_bt = get_unaligned_le32(tlv->val);
			अवरोध;
		हाल INTEL_TLV_CNVR_BT:
			version->cnvr_bt = get_unaligned_le32(tlv->val);
			अवरोध;
		हाल INTEL_TLV_DEV_REV_ID:
			version->dev_rev_id = get_unaligned_le16(tlv->val);
			अवरोध;
		हाल INTEL_TLV_IMAGE_TYPE:
			version->img_type = tlv->val[0];
			अवरोध;
		हाल INTEL_TLV_TIME_STAMP:
			/* If image type is Operational firmware (0x03), then
			 * running FW Calendar Week and Year inक्रमmation can
			 * be extracted from Timestamp inक्रमmation
			 */
			version->min_fw_build_cw = tlv->val[0];
			version->min_fw_build_yy = tlv->val[1];
			version->बारtamp = get_unaligned_le16(tlv->val);
			अवरोध;
		हाल INTEL_TLV_BUILD_TYPE:
			version->build_type = tlv->val[0];
			अवरोध;
		हाल INTEL_TLV_BUILD_NUM:
			/* If image type is Operational firmware (0x03), then
			 * running FW build number can be extracted from the
			 * Build inक्रमmation
			 */
			version->min_fw_build_nn = tlv->val[0];
			version->build_num = get_unaligned_le32(tlv->val);
			अवरोध;
		हाल INTEL_TLV_SECURE_BOOT:
			version->secure_boot = tlv->val[0];
			अवरोध;
		हाल INTEL_TLV_OTP_LOCK:
			version->otp_lock = tlv->val[0];
			अवरोध;
		हाल INTEL_TLV_API_LOCK:
			version->api_lock = tlv->val[0];
			अवरोध;
		हाल INTEL_TLV_DEBUG_LOCK:
			version->debug_lock = tlv->val[0];
			अवरोध;
		हाल INTEL_TLV_MIN_FW:
			version->min_fw_build_nn = tlv->val[0];
			version->min_fw_build_cw = tlv->val[1];
			version->min_fw_build_yy = tlv->val[2];
			अवरोध;
		हाल INTEL_TLV_LIMITED_CCE:
			version->limited_cce = tlv->val[0];
			अवरोध;
		हाल INTEL_TLV_SBE_TYPE:
			version->sbe_type = tlv->val[0];
			अवरोध;
		हाल INTEL_TLV_OTP_BDADDR:
			स_नकल(&version->otp_bd_addr, tlv->val, tlv->len);
			अवरोध;
		शेष:
			/* Ignore rest of inक्रमmation */
			अवरोध;
		पूर्ण
		/* consume the current tlv and move to next*/
		skb_pull(skb, tlv->len + माप(*tlv));
	पूर्ण

	kमुक्त_skb(skb);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(btपूर्णांकel_पढ़ो_version_tlv);

/* ------- REGMAP IBT SUPPORT ------- */

#घोषणा IBT_REG_MODE_8BIT  0x00
#घोषणा IBT_REG_MODE_16BIT 0x01
#घोषणा IBT_REG_MODE_32BIT 0x02

काष्ठा regmap_ibt_context अणु
	काष्ठा hci_dev *hdev;
	__u16 op_ग_लिखो;
	__u16 op_पढ़ो;
पूर्ण;

काष्ठा ibt_cp_reg_access अणु
	__le32  addr;
	__u8    mode;
	__u8    len;
	__u8    data[];
पूर्ण __packed;

काष्ठा ibt_rp_reg_access अणु
	__u8    status;
	__le32  addr;
	__u8    data[];
पूर्ण __packed;

अटल पूर्णांक regmap_ibt_पढ़ो(व्योम *context, स्थिर व्योम *addr, माप_प्रकार reg_size,
			   व्योम *val, माप_प्रकार val_size)
अणु
	काष्ठा regmap_ibt_context *ctx = context;
	काष्ठा ibt_cp_reg_access cp;
	काष्ठा ibt_rp_reg_access *rp;
	काष्ठा sk_buff *skb;
	पूर्णांक err = 0;

	अगर (reg_size != माप(__le32))
		वापस -EINVAL;

	चयन (val_size) अणु
	हाल 1:
		cp.mode = IBT_REG_MODE_8BIT;
		अवरोध;
	हाल 2:
		cp.mode = IBT_REG_MODE_16BIT;
		अवरोध;
	हाल 4:
		cp.mode = IBT_REG_MODE_32BIT;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* regmap provides a little-endian क्रमmatted addr */
	cp.addr = *(__le32 *)addr;
	cp.len = val_size;

	bt_dev_dbg(ctx->hdev, "Register (0x%x) read", le32_to_cpu(cp.addr));

	skb = hci_cmd_sync(ctx->hdev, ctx->op_पढ़ो, माप(cp), &cp,
			   HCI_CMD_TIMEOUT);
	अगर (IS_ERR(skb)) अणु
		err = PTR_ERR(skb);
		bt_dev_err(ctx->hdev, "regmap: Register (0x%x) read error (%d)",
			   le32_to_cpu(cp.addr), err);
		वापस err;
	पूर्ण

	अगर (skb->len != माप(*rp) + val_size) अणु
		bt_dev_err(ctx->hdev, "regmap: Register (0x%x) read error, bad len",
			   le32_to_cpu(cp.addr));
		err = -EINVAL;
		जाओ करोne;
	पूर्ण

	rp = (काष्ठा ibt_rp_reg_access *)skb->data;

	अगर (rp->addr != cp.addr) अणु
		bt_dev_err(ctx->hdev, "regmap: Register (0x%x) read error, bad addr",
			   le32_to_cpu(rp->addr));
		err = -EINVAL;
		जाओ करोne;
	पूर्ण

	स_नकल(val, rp->data, val_size);

करोne:
	kमुक्त_skb(skb);
	वापस err;
पूर्ण

अटल पूर्णांक regmap_ibt_gather_ग_लिखो(व्योम *context,
				   स्थिर व्योम *addr, माप_प्रकार reg_size,
				   स्थिर व्योम *val, माप_प्रकार val_size)
अणु
	काष्ठा regmap_ibt_context *ctx = context;
	काष्ठा ibt_cp_reg_access *cp;
	काष्ठा sk_buff *skb;
	पूर्णांक plen = माप(*cp) + val_size;
	u8 mode;
	पूर्णांक err = 0;

	अगर (reg_size != माप(__le32))
		वापस -EINVAL;

	चयन (val_size) अणु
	हाल 1:
		mode = IBT_REG_MODE_8BIT;
		अवरोध;
	हाल 2:
		mode = IBT_REG_MODE_16BIT;
		अवरोध;
	हाल 4:
		mode = IBT_REG_MODE_32BIT;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	cp = kदो_स्मृति(plen, GFP_KERNEL);
	अगर (!cp)
		वापस -ENOMEM;

	/* regmap provides a little-endian क्रमmatted addr/value */
	cp->addr = *(__le32 *)addr;
	cp->mode = mode;
	cp->len = val_size;
	स_नकल(&cp->data, val, val_size);

	bt_dev_dbg(ctx->hdev, "Register (0x%x) write", le32_to_cpu(cp->addr));

	skb = hci_cmd_sync(ctx->hdev, ctx->op_ग_लिखो, plen, cp, HCI_CMD_TIMEOUT);
	अगर (IS_ERR(skb)) अणु
		err = PTR_ERR(skb);
		bt_dev_err(ctx->hdev, "regmap: Register (0x%x) write error (%d)",
			   le32_to_cpu(cp->addr), err);
		जाओ करोne;
	पूर्ण
	kमुक्त_skb(skb);

करोne:
	kमुक्त(cp);
	वापस err;
पूर्ण

अटल पूर्णांक regmap_ibt_ग_लिखो(व्योम *context, स्थिर व्योम *data, माप_प्रकार count)
अणु
	/* data contains रेजिस्टर+value, since we only support 32bit addr,
	 * minimum data size is 4 bytes.
	 */
	अगर (WARN_ONCE(count < 4, "Invalid register access"))
		वापस -EINVAL;

	वापस regmap_ibt_gather_ग_लिखो(context, data, 4, data + 4, count - 4);
पूर्ण

अटल व्योम regmap_ibt_मुक्त_context(व्योम *context)
अणु
	kमुक्त(context);
पूर्ण

अटल काष्ठा regmap_bus regmap_ibt = अणु
	.पढ़ो = regmap_ibt_पढ़ो,
	.ग_लिखो = regmap_ibt_ग_लिखो,
	.gather_ग_लिखो = regmap_ibt_gather_ग_लिखो,
	.मुक्त_context = regmap_ibt_मुक्त_context,
	.reg_क्रमmat_endian_शेष = REGMAP_ENDIAN_LITTLE,
	.val_क्रमmat_endian_शेष = REGMAP_ENDIAN_LITTLE,
पूर्ण;

/* Config is the same क्रम all रेजिस्टर regions */
अटल स्थिर काष्ठा regmap_config regmap_ibt_cfg = अणु
	.name      = "btintel_regmap",
	.reg_bits  = 32,
	.val_bits  = 32,
पूर्ण;

काष्ठा regmap *btपूर्णांकel_regmap_init(काष्ठा hci_dev *hdev, u16 opcode_पढ़ो,
				   u16 opcode_ग_लिखो)
अणु
	काष्ठा regmap_ibt_context *ctx;

	bt_dev_info(hdev, "regmap: Init R%x-W%x region", opcode_पढ़ो,
		    opcode_ग_लिखो);

	ctx = kzalloc(माप(*ctx), GFP_KERNEL);
	अगर (!ctx)
		वापस ERR_PTR(-ENOMEM);

	ctx->op_पढ़ो = opcode_पढ़ो;
	ctx->op_ग_लिखो = opcode_ग_लिखो;
	ctx->hdev = hdev;

	वापस regmap_init(&hdev->dev, &regmap_ibt, ctx, &regmap_ibt_cfg);
पूर्ण
EXPORT_SYMBOL_GPL(btपूर्णांकel_regmap_init);

पूर्णांक btपूर्णांकel_send_पूर्णांकel_reset(काष्ठा hci_dev *hdev, u32 boot_param)
अणु
	काष्ठा पूर्णांकel_reset params = अणु 0x00, 0x01, 0x00, 0x01, 0x00000000 पूर्ण;
	काष्ठा sk_buff *skb;

	params.boot_param = cpu_to_le32(boot_param);

	skb = __hci_cmd_sync(hdev, 0xfc01, माप(params), &params,
			     HCI_INIT_TIMEOUT);
	अगर (IS_ERR(skb)) अणु
		bt_dev_err(hdev, "Failed to send Intel Reset command");
		वापस PTR_ERR(skb);
	पूर्ण

	kमुक्त_skb(skb);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(btपूर्णांकel_send_पूर्णांकel_reset);

पूर्णांक btपूर्णांकel_पढ़ो_boot_params(काष्ठा hci_dev *hdev,
			     काष्ठा पूर्णांकel_boot_params *params)
अणु
	काष्ठा sk_buff *skb;

	skb = __hci_cmd_sync(hdev, 0xfc0d, 0, शून्य, HCI_INIT_TIMEOUT);
	अगर (IS_ERR(skb)) अणु
		bt_dev_err(hdev, "Reading Intel boot parameters failed (%ld)",
			   PTR_ERR(skb));
		वापस PTR_ERR(skb);
	पूर्ण

	अगर (skb->len != माप(*params)) अणु
		bt_dev_err(hdev, "Intel boot parameters size mismatch");
		kमुक्त_skb(skb);
		वापस -EILSEQ;
	पूर्ण

	स_नकल(params, skb->data, माप(*params));

	kमुक्त_skb(skb);

	अगर (params->status) अणु
		bt_dev_err(hdev, "Intel boot parameters command failed (%02x)",
			   params->status);
		वापस -bt_to_त्रुटि_सं(params->status);
	पूर्ण

	bt_dev_info(hdev, "Device revision is %u",
		    le16_to_cpu(params->dev_revid));

	bt_dev_info(hdev, "Secure boot is %s",
		    params->secure_boot ? "enabled" : "disabled");

	bt_dev_info(hdev, "OTP lock is %s",
		    params->otp_lock ? "enabled" : "disabled");

	bt_dev_info(hdev, "API lock is %s",
		    params->api_lock ? "enabled" : "disabled");

	bt_dev_info(hdev, "Debug lock is %s",
		    params->debug_lock ? "enabled" : "disabled");

	bt_dev_info(hdev, "Minimum firmware build %u week %u %u",
		    params->min_fw_build_nn, params->min_fw_build_cw,
		    2000 + params->min_fw_build_yy);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(btपूर्णांकel_पढ़ो_boot_params);

अटल पूर्णांक btपूर्णांकel_sfi_rsa_header_secure_send(काष्ठा hci_dev *hdev,
					      स्थिर काष्ठा firmware *fw)
अणु
	पूर्णांक err;

	/* Start the firmware करोwnload transaction with the Init fragment
	 * represented by the 128 bytes of CSS header.
	 */
	err = btपूर्णांकel_secure_send(hdev, 0x00, 128, fw->data);
	अगर (err < 0) अणु
		bt_dev_err(hdev, "Failed to send firmware header (%d)", err);
		जाओ करोne;
	पूर्ण

	/* Send the 256 bytes of खुला key inक्रमmation from the firmware
	 * as the PKey fragment.
	 */
	err = btपूर्णांकel_secure_send(hdev, 0x03, 256, fw->data + 128);
	अगर (err < 0) अणु
		bt_dev_err(hdev, "Failed to send firmware pkey (%d)", err);
		जाओ करोne;
	पूर्ण

	/* Send the 256 bytes of signature inक्रमmation from the firmware
	 * as the Sign fragment.
	 */
	err = btपूर्णांकel_secure_send(hdev, 0x02, 256, fw->data + 388);
	अगर (err < 0) अणु
		bt_dev_err(hdev, "Failed to send firmware signature (%d)", err);
		जाओ करोne;
	पूर्ण

करोne:
	वापस err;
पूर्ण

अटल पूर्णांक btपूर्णांकel_sfi_ecdsa_header_secure_send(काष्ठा hci_dev *hdev,
						स्थिर काष्ठा firmware *fw)
अणु
	पूर्णांक err;

	/* Start the firmware करोwnload transaction with the Init fragment
	 * represented by the 128 bytes of CSS header.
	 */
	err = btपूर्णांकel_secure_send(hdev, 0x00, 128, fw->data + 644);
	अगर (err < 0) अणु
		bt_dev_err(hdev, "Failed to send firmware header (%d)", err);
		वापस err;
	पूर्ण

	/* Send the 96 bytes of खुला key inक्रमmation from the firmware
	 * as the PKey fragment.
	 */
	err = btपूर्णांकel_secure_send(hdev, 0x03, 96, fw->data + 644 + 128);
	अगर (err < 0) अणु
		bt_dev_err(hdev, "Failed to send firmware pkey (%d)", err);
		वापस err;
	पूर्ण

	/* Send the 96 bytes of signature inक्रमmation from the firmware
	 * as the Sign fragment
	 */
	err = btपूर्णांकel_secure_send(hdev, 0x02, 96, fw->data + 644 + 224);
	अगर (err < 0) अणु
		bt_dev_err(hdev, "Failed to send firmware signature (%d)",
			   err);
		वापस err;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक btपूर्णांकel_करोwnload_firmware_payload(काष्ठा hci_dev *hdev,
					     स्थिर काष्ठा firmware *fw,
					     माप_प्रकार offset)
अणु
	पूर्णांक err;
	स्थिर u8 *fw_ptr;
	u32 frag_len;

	fw_ptr = fw->data + offset;
	frag_len = 0;
	err = -EINVAL;

	जबतक (fw_ptr - fw->data < fw->size) अणु
		काष्ठा hci_command_hdr *cmd = (व्योम *)(fw_ptr + frag_len);

		frag_len += माप(*cmd) + cmd->plen;

		/* The parameter length of the secure send command requires
		 * a 4 byte alignment. It happens so that the firmware file
		 * contains proper Intel_NOP commands to align the fragments
		 * as needed.
		 *
		 * Send set of commands with 4 byte alignment from the
		 * firmware data buffer as a single Data fragement.
		 */
		अगर (!(frag_len % 4)) अणु
			err = btपूर्णांकel_secure_send(hdev, 0x01, frag_len, fw_ptr);
			अगर (err < 0) अणु
				bt_dev_err(hdev,
					   "Failed to send firmware data (%d)",
					   err);
				जाओ करोne;
			पूर्ण

			fw_ptr += frag_len;
			frag_len = 0;
		पूर्ण
	पूर्ण

करोne:
	वापस err;
पूर्ण

अटल bool btपूर्णांकel_firmware_version(काष्ठा hci_dev *hdev,
				     u8 num, u8 ww, u8 yy,
				     स्थिर काष्ठा firmware *fw,
				     u32 *boot_addr)
अणु
	स्थिर u8 *fw_ptr;

	fw_ptr = fw->data;

	जबतक (fw_ptr - fw->data < fw->size) अणु
		काष्ठा hci_command_hdr *cmd = (व्योम *)(fw_ptr);

		/* Each SKU has a dअगरferent reset parameter to use in the
		 * HCI_Intel_Reset command and it is embedded in the firmware
		 * data. So, instead of using अटल value per SKU, check
		 * the firmware data and save it क्रम later use.
		 */
		अगर (le16_to_cpu(cmd->opcode) == CMD_WRITE_BOOT_PARAMS) अणु
			काष्ठा cmd_ग_लिखो_boot_params *params;

			params = (व्योम *)(fw_ptr + माप(*cmd));

			bt_dev_info(hdev, "Boot Address: 0x%x",
				    le32_to_cpu(params->boot_addr));

			bt_dev_info(hdev, "Firmware Version: %u-%u.%u",
				    params->fw_build_num, params->fw_build_ww,
				    params->fw_build_yy);

			वापस (num == params->fw_build_num &&
				ww == params->fw_build_ww &&
				yy == params->fw_build_yy);
		पूर्ण

		fw_ptr += माप(*cmd) + cmd->plen;
	पूर्ण

	वापस false;
पूर्ण

पूर्णांक btपूर्णांकel_करोwnload_firmware(काष्ठा hci_dev *hdev,
			      काष्ठा पूर्णांकel_version *ver,
			      स्थिर काष्ठा firmware *fw,
			      u32 *boot_param)
अणु
	पूर्णांक err;

	/* SfP and WsP करोn't seem to update the firmware version on file
	 * so version checking is currently not possible.
	 */
	चयन (ver->hw_variant) अणु
	हाल 0x0b:	/* SfP */
	हाल 0x0c:	/* WsP */
		/* Skip version checking */
		अवरोध;
	शेष:
		/* Skip पढ़ोing firmware file version in bootloader mode */
		अगर (ver->fw_variant == 0x06)
			अवरोध;

		/* Skip करोwnload अगर firmware has the same version */
		अगर (btपूर्णांकel_firmware_version(hdev, ver->fw_build_num,
					     ver->fw_build_ww, ver->fw_build_yy,
					     fw, boot_param)) अणु
			bt_dev_info(hdev, "Firmware already loaded");
			/* Return -EALREADY to indicate that the firmware has
			 * alपढ़ोy been loaded.
			 */
			वापस -EALREADY;
		पूर्ण
	पूर्ण

	/* The firmware variant determines अगर the device is in bootloader
	 * mode or is running operational firmware. The value 0x06 identअगरies
	 * the bootloader and the value 0x23 identअगरies the operational
	 * firmware.
	 *
	 * If the firmware version has changed that means it needs to be reset
	 * to bootloader when operational so the new firmware can be loaded.
	 */
	अगर (ver->fw_variant == 0x23)
		वापस -EINVAL;

	err = btपूर्णांकel_sfi_rsa_header_secure_send(hdev, fw);
	अगर (err)
		वापस err;

	वापस btपूर्णांकel_करोwnload_firmware_payload(hdev, fw, RSA_HEADER_LEN);
पूर्ण
EXPORT_SYMBOL_GPL(btपूर्णांकel_करोwnload_firmware);

पूर्णांक btपूर्णांकel_करोwnload_firmware_newgen(काष्ठा hci_dev *hdev,
				     काष्ठा पूर्णांकel_version_tlv *ver,
				     स्थिर काष्ठा firmware *fw, u32 *boot_param,
				     u8 hw_variant, u8 sbe_type)
अणु
	पूर्णांक err;
	u32 css_header_ver;

	/* Skip पढ़ोing firmware file version in bootloader mode */
	अगर (ver->img_type != 0x01) अणु
		/* Skip करोwnload अगर firmware has the same version */
		अगर (btपूर्णांकel_firmware_version(hdev, ver->min_fw_build_nn,
					     ver->min_fw_build_cw,
					     ver->min_fw_build_yy,
					     fw, boot_param)) अणु
			bt_dev_info(hdev, "Firmware already loaded");
			/* Return -EALREADY to indicate that firmware has
			 * alपढ़ोy been loaded.
			 */
			वापस -EALREADY;
		पूर्ण
	पूर्ण

	/* The firmware variant determines अगर the device is in bootloader
	 * mode or is running operational firmware. The value 0x01 identअगरies
	 * the bootloader and the value 0x03 identअगरies the operational
	 * firmware.
	 *
	 * If the firmware version has changed that means it needs to be reset
	 * to bootloader when operational so the new firmware can be loaded.
	 */
	अगर (ver->img_type == 0x03)
		वापस -EINVAL;

	/* iBT hardware variants 0x0b, 0x0c, 0x11, 0x12, 0x13, 0x14 support
	 * only RSA secure boot engine. Hence, the corresponding sfi file will
	 * have RSA header of 644 bytes followed by Command Buffer.
	 *
	 * iBT hardware variants 0x17, 0x18 onwards support both RSA and ECDSA
	 * secure boot engine. As a result, the corresponding sfi file will
	 * have RSA header of 644, ECDSA header of 320 bytes followed by
	 * Command Buffer.
	 *
	 * CSS Header byte positions 0x08 to 0x0B represent the CSS Header
	 * version: RSA(0x00010000) , ECDSA (0x00020000)
	 */
	css_header_ver = get_unaligned_le32(fw->data + CSS_HEADER_OFFSET);
	अगर (css_header_ver != 0x00010000) अणु
		bt_dev_err(hdev, "Invalid CSS Header version");
		वापस -EINVAL;
	पूर्ण

	अगर (hw_variant <= 0x14) अणु
		अगर (sbe_type != 0x00) अणु
			bt_dev_err(hdev, "Invalid SBE type for hardware variant (%d)",
				   hw_variant);
			वापस -EINVAL;
		पूर्ण

		err = btपूर्णांकel_sfi_rsa_header_secure_send(hdev, fw);
		अगर (err)
			वापस err;

		err = btपूर्णांकel_करोwnload_firmware_payload(hdev, fw, RSA_HEADER_LEN);
		अगर (err)
			वापस err;
	पूर्ण अन्यथा अगर (hw_variant >= 0x17) अणु
		/* Check अगर CSS header क्रम ECDSA follows the RSA header */
		अगर (fw->data[ECDSA_OFFSET] != 0x06)
			वापस -EINVAL;

		/* Check अगर the CSS Header version is ECDSA(0x00020000) */
		css_header_ver = get_unaligned_le32(fw->data + ECDSA_OFFSET + CSS_HEADER_OFFSET);
		अगर (css_header_ver != 0x00020000) अणु
			bt_dev_err(hdev, "Invalid CSS Header version");
			वापस -EINVAL;
		पूर्ण

		अगर (sbe_type == 0x00) अणु
			err = btपूर्णांकel_sfi_rsa_header_secure_send(hdev, fw);
			अगर (err)
				वापस err;

			err = btपूर्णांकel_करोwnload_firmware_payload(hdev, fw,
								RSA_HEADER_LEN + ECDSA_HEADER_LEN);
			अगर (err)
				वापस err;
		पूर्ण अन्यथा अगर (sbe_type == 0x01) अणु
			err = btपूर्णांकel_sfi_ecdsa_header_secure_send(hdev, fw);
			अगर (err)
				वापस err;

			err = btपूर्णांकel_करोwnload_firmware_payload(hdev, fw,
								RSA_HEADER_LEN + ECDSA_HEADER_LEN);
			अगर (err)
				वापस err;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(btपूर्णांकel_करोwnload_firmware_newgen);

व्योम btपूर्णांकel_reset_to_bootloader(काष्ठा hci_dev *hdev)
अणु
	काष्ठा पूर्णांकel_reset params;
	काष्ठा sk_buff *skb;

	/* Send Intel Reset command. This will result in
	 * re-क्रमागतeration of BT controller.
	 *
	 * Intel Reset parameter description:
	 * reset_type :   0x00 (Soft reset),
	 *		  0x01 (Hard reset)
	 * patch_enable : 0x00 (Do not enable),
	 *		  0x01 (Enable)
	 * ddc_reload :   0x00 (Do not reload),
	 *		  0x01 (Reload)
	 * boot_option:   0x00 (Current image),
	 *                0x01 (Specअगरied boot address)
	 * boot_param:    Boot address
	 *
	 */
	params.reset_type = 0x01;
	params.patch_enable = 0x01;
	params.ddc_reload = 0x01;
	params.boot_option = 0x00;
	params.boot_param = cpu_to_le32(0x00000000);

	skb = __hci_cmd_sync(hdev, 0xfc01, माप(params),
			     &params, HCI_INIT_TIMEOUT);
	अगर (IS_ERR(skb)) अणु
		bt_dev_err(hdev, "FW download error recovery failed (%ld)",
			   PTR_ERR(skb));
		वापस;
	पूर्ण
	bt_dev_info(hdev, "Intel reset sent to retry FW download");
	kमुक्त_skb(skb);

	/* Current Intel BT controllers(ThP/JfP) hold the USB reset
	 * lines क्रम 2ms when it receives Intel Reset in bootloader mode.
	 * Whereas, the upcoming Intel BT controllers will hold USB reset
	 * क्रम 150ms. To keep the delay generic, 150ms is chosen here.
	 */
	msleep(150);
पूर्ण
EXPORT_SYMBOL_GPL(btपूर्णांकel_reset_to_bootloader);

पूर्णांक btपूर्णांकel_पढ़ो_debug_features(काष्ठा hci_dev *hdev,
				काष्ठा पूर्णांकel_debug_features *features)
अणु
	काष्ठा sk_buff *skb;
	u8 page_no = 1;

	/* Intel controller supports two pages, each page is of 128-bit
	 * feature bit mask. And each bit defines specअगरic feature support
	 */
	skb = __hci_cmd_sync(hdev, 0xfca6, माप(page_no), &page_no,
			     HCI_INIT_TIMEOUT);
	अगर (IS_ERR(skb)) अणु
		bt_dev_err(hdev, "Reading supported features failed (%ld)",
			   PTR_ERR(skb));
		वापस PTR_ERR(skb);
	पूर्ण

	अगर (skb->len != (माप(features->page1) + 3)) अणु
		bt_dev_err(hdev, "Supported features event size mismatch");
		kमुक्त_skb(skb);
		वापस -EILSEQ;
	पूर्ण

	स_नकल(features->page1, skb->data + 3, माप(features->page1));

	/* Read the supported features page2 अगर required in future.
	 */
	kमुक्त_skb(skb);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(btपूर्णांकel_पढ़ो_debug_features);

पूर्णांक btपूर्णांकel_set_debug_features(काष्ठा hci_dev *hdev,
			       स्थिर काष्ठा पूर्णांकel_debug_features *features)
अणु
	u8 mask[11] = अणु 0x0a, 0x92, 0x02, 0x07, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00 पूर्ण;
	काष्ठा sk_buff *skb;

	अगर (!features)
		वापस -EINVAL;

	अगर (!(features->page1[0] & 0x3f)) अणु
		bt_dev_info(hdev, "Telemetry exception format not supported");
		वापस 0;
	पूर्ण

	skb = __hci_cmd_sync(hdev, 0xfc8b, 11, mask, HCI_INIT_TIMEOUT);
	अगर (IS_ERR(skb)) अणु
		bt_dev_err(hdev, "Setting Intel telemetry ddc write event mask failed (%ld)",
			   PTR_ERR(skb));
		वापस PTR_ERR(skb);
	पूर्ण

	kमुक्त_skb(skb);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(btपूर्णांकel_set_debug_features);

MODULE_AUTHOR("Marcel Holtmann <marcel@holtmann.org>");
MODULE_DESCRIPTION("Bluetooth support for Intel devices ver " VERSION);
MODULE_VERSION(VERSION);
MODULE_LICENSE("GPL");
MODULE_FIRMWARE("intel/ibt-11-5.sfi");
MODULE_FIRMWARE("intel/ibt-11-5.ddc");
MODULE_FIRMWARE("intel/ibt-12-16.sfi");
MODULE_FIRMWARE("intel/ibt-12-16.ddc");
