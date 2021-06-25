<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *
 *  Bluetooth support क्रम Broadcom devices
 *
 *  Copyright (C) 2015  Intel Corporation
 */

#समावेश <linux/module.h>
#समावेश <linux/firmware.h>
#समावेश <यंत्र/unaligned.h>

#समावेश <net/bluetooth/bluetooth.h>
#समावेश <net/bluetooth/hci_core.h>

#समावेश "btbcm.h"

#घोषणा VERSION "0.1"

#घोषणा BDADDR_BCM20702A0 (&(bdaddr_t) अणुअणु0x00, 0xa0, 0x02, 0x70, 0x20, 0x00पूर्णपूर्ण)
#घोषणा BDADDR_BCM20702A1 (&(bdaddr_t) अणुअणु0x00, 0x00, 0xa0, 0x02, 0x70, 0x20पूर्णपूर्ण)
#घोषणा BDADDR_BCM2076B1 (&(bdaddr_t) अणुअणु0x79, 0x56, 0x00, 0xa0, 0x76, 0x20पूर्णपूर्ण)
#घोषणा BDADDR_BCM43430A0 (&(bdaddr_t) अणुअणु0xac, 0x1f, 0x12, 0xa0, 0x43, 0x43पूर्णपूर्ण)
#घोषणा BDADDR_BCM4324B3 (&(bdaddr_t) अणुअणु0x00, 0x00, 0x00, 0xb3, 0x24, 0x43पूर्णपूर्ण)
#घोषणा BDADDR_BCM4330B1 (&(bdaddr_t) अणुअणु0x00, 0x00, 0x00, 0xb1, 0x30, 0x43पूर्णपूर्ण)
#घोषणा BDADDR_BCM4334B0 (&(bdaddr_t) अणुअणु0x00, 0x00, 0x00, 0xb0, 0x34, 0x43पूर्णपूर्ण)
#घोषणा BDADDR_BCM4345C5 (&(bdaddr_t) अणुअणु0xac, 0x1f, 0x00, 0xc5, 0x45, 0x43पूर्णपूर्ण)
#घोषणा BDADDR_BCM43341B (&(bdaddr_t) अणुअणु0xac, 0x1f, 0x00, 0x1b, 0x34, 0x43पूर्णपूर्ण)

#घोषणा BCM_FW_NAME_LEN			64
#घोषणा BCM_FW_NAME_COUNT_MAX		2
/* For kदो_स्मृति-ing the fw-name array instead of putting it on the stack */
प्रकार अक्षर bcm_fw_name[BCM_FW_NAME_LEN];

पूर्णांक btbcm_check_bdaddr(काष्ठा hci_dev *hdev)
अणु
	काष्ठा hci_rp_पढ़ो_bd_addr *bda;
	काष्ठा sk_buff *skb;

	skb = __hci_cmd_sync(hdev, HCI_OP_READ_BD_ADDR, 0, शून्य,
			     HCI_INIT_TIMEOUT);
	अगर (IS_ERR(skb)) अणु
		पूर्णांक err = PTR_ERR(skb);

		bt_dev_err(hdev, "BCM: Reading device address failed (%d)", err);
		वापस err;
	पूर्ण

	अगर (skb->len != माप(*bda)) अणु
		bt_dev_err(hdev, "BCM: Device address length mismatch");
		kमुक्त_skb(skb);
		वापस -EIO;
	पूर्ण

	bda = (काष्ठा hci_rp_पढ़ो_bd_addr *)skb->data;

	/* Check अगर the address indicates a controller with either an
	 * invalid or शेष address. In both हालs the device needs
	 * to be marked as not having a valid address.
	 *
	 * The address 00:20:70:02:A0:00 indicates a BCM20702A0 controller
	 * with no configured address.
	 *
	 * The address 20:70:02:A0:00:00 indicates a BCM20702A1 controller
	 * with no configured address.
	 *
	 * The address 20:76:A0:00:56:79 indicates a BCM2076B1 controller
	 * with no configured address.
	 *
	 * The address 43:24:B3:00:00:00 indicates a BCM4324B3 controller
	 * with रुकोing क्रम configuration state.
	 *
	 * The address 43:30:B1:00:00:00 indicates a BCM4330B1 controller
	 * with रुकोing क्रम configuration state.
	 *
	 * The address 43:43:A0:12:1F:AC indicates a BCM43430A0 controller
	 * with no configured address.
	 */
	अगर (!bacmp(&bda->bdaddr, BDADDR_BCM20702A0) ||
	    !bacmp(&bda->bdaddr, BDADDR_BCM20702A1) ||
	    !bacmp(&bda->bdaddr, BDADDR_BCM2076B1) ||
	    !bacmp(&bda->bdaddr, BDADDR_BCM4324B3) ||
	    !bacmp(&bda->bdaddr, BDADDR_BCM4330B1) ||
	    !bacmp(&bda->bdaddr, BDADDR_BCM4334B0) ||
	    !bacmp(&bda->bdaddr, BDADDR_BCM4345C5) ||
	    !bacmp(&bda->bdaddr, BDADDR_BCM43430A0) ||
	    !bacmp(&bda->bdaddr, BDADDR_BCM43341B)) अणु
		bt_dev_info(hdev, "BCM: Using default device address (%pMR)",
			    &bda->bdaddr);
		set_bit(HCI_QUIRK_INVALID_BDADDR, &hdev->quirks);
	पूर्ण

	kमुक्त_skb(skb);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(btbcm_check_bdaddr);

पूर्णांक btbcm_set_bdaddr(काष्ठा hci_dev *hdev, स्थिर bdaddr_t *bdaddr)
अणु
	काष्ठा sk_buff *skb;
	पूर्णांक err;

	skb = __hci_cmd_sync(hdev, 0xfc01, 6, bdaddr, HCI_INIT_TIMEOUT);
	अगर (IS_ERR(skb)) अणु
		err = PTR_ERR(skb);
		bt_dev_err(hdev, "BCM: Change address command failed (%d)", err);
		वापस err;
	पूर्ण
	kमुक्त_skb(skb);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(btbcm_set_bdaddr);

पूर्णांक btbcm_पढ़ो_pcm_पूर्णांक_params(काष्ठा hci_dev *hdev,
			      काष्ठा bcm_set_pcm_पूर्णांक_params *params)
अणु
	काष्ठा sk_buff *skb;
	पूर्णांक err = 0;

	skb = __hci_cmd_sync(hdev, 0xfc1d, 0, शून्य, HCI_INIT_TIMEOUT);
	अगर (IS_ERR(skb)) अणु
		err = PTR_ERR(skb);
		bt_dev_err(hdev, "BCM: Read PCM int params failed (%d)", err);
		वापस err;
	पूर्ण

	अगर (skb->len != 6 || skb->data[0]) अणु
		bt_dev_err(hdev, "BCM: Read PCM int params length mismatch");
		kमुक्त_skb(skb);
		वापस -EIO;
	पूर्ण

	अगर (params)
		स_नकल(params, skb->data + 1, 5);

	kमुक्त_skb(skb);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(btbcm_पढ़ो_pcm_पूर्णांक_params);

पूर्णांक btbcm_ग_लिखो_pcm_पूर्णांक_params(काष्ठा hci_dev *hdev,
			       स्थिर काष्ठा bcm_set_pcm_पूर्णांक_params *params)
अणु
	काष्ठा sk_buff *skb;
	पूर्णांक err;

	skb = __hci_cmd_sync(hdev, 0xfc1c, 5, params, HCI_INIT_TIMEOUT);
	अगर (IS_ERR(skb)) अणु
		err = PTR_ERR(skb);
		bt_dev_err(hdev, "BCM: Write PCM int params failed (%d)", err);
		वापस err;
	पूर्ण
	kमुक्त_skb(skb);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(btbcm_ग_लिखो_pcm_पूर्णांक_params);

पूर्णांक btbcm_patchram(काष्ठा hci_dev *hdev, स्थिर काष्ठा firmware *fw)
अणु
	स्थिर काष्ठा hci_command_hdr *cmd;
	स्थिर u8 *fw_ptr;
	माप_प्रकार fw_size;
	काष्ठा sk_buff *skb;
	u16 opcode;
	पूर्णांक err = 0;

	/* Start Download */
	skb = __hci_cmd_sync(hdev, 0xfc2e, 0, शून्य, HCI_INIT_TIMEOUT);
	अगर (IS_ERR(skb)) अणु
		err = PTR_ERR(skb);
		bt_dev_err(hdev, "BCM: Download Minidrv command failed (%d)",
			   err);
		जाओ करोne;
	पूर्ण
	kमुक्त_skb(skb);

	/* 50 msec delay after Download Minidrv completes */
	msleep(50);

	fw_ptr = fw->data;
	fw_size = fw->size;

	जबतक (fw_size >= माप(*cmd)) अणु
		स्थिर u8 *cmd_param;

		cmd = (काष्ठा hci_command_hdr *)fw_ptr;
		fw_ptr += माप(*cmd);
		fw_size -= माप(*cmd);

		अगर (fw_size < cmd->plen) अणु
			bt_dev_err(hdev, "BCM: Patch is corrupted");
			err = -EINVAL;
			जाओ करोne;
		पूर्ण

		cmd_param = fw_ptr;
		fw_ptr += cmd->plen;
		fw_size -= cmd->plen;

		opcode = le16_to_cpu(cmd->opcode);

		skb = __hci_cmd_sync(hdev, opcode, cmd->plen, cmd_param,
				     HCI_INIT_TIMEOUT);
		अगर (IS_ERR(skb)) अणु
			err = PTR_ERR(skb);
			bt_dev_err(hdev, "BCM: Patch command %04x failed (%d)",
				   opcode, err);
			जाओ करोne;
		पूर्ण
		kमुक्त_skb(skb);
	पूर्ण

	/* 250 msec delay after Launch Ram completes */
	msleep(250);

करोne:
	वापस err;
पूर्ण
EXPORT_SYMBOL(btbcm_patchram);

अटल पूर्णांक btbcm_reset(काष्ठा hci_dev *hdev)
अणु
	काष्ठा sk_buff *skb;

	skb = __hci_cmd_sync(hdev, HCI_OP_RESET, 0, शून्य, HCI_INIT_TIMEOUT);
	अगर (IS_ERR(skb)) अणु
		पूर्णांक err = PTR_ERR(skb);

		bt_dev_err(hdev, "BCM: Reset failed (%d)", err);
		वापस err;
	पूर्ण
	kमुक्त_skb(skb);

	/* 100 msec delay क्रम module to complete reset process */
	msleep(100);

	वापस 0;
पूर्ण

अटल काष्ठा sk_buff *btbcm_पढ़ो_local_name(काष्ठा hci_dev *hdev)
अणु
	काष्ठा sk_buff *skb;

	skb = __hci_cmd_sync(hdev, HCI_OP_READ_LOCAL_NAME, 0, शून्य,
			     HCI_INIT_TIMEOUT);
	अगर (IS_ERR(skb)) अणु
		bt_dev_err(hdev, "BCM: Reading local name failed (%ld)",
			   PTR_ERR(skb));
		वापस skb;
	पूर्ण

	अगर (skb->len != माप(काष्ठा hci_rp_पढ़ो_local_name)) अणु
		bt_dev_err(hdev, "BCM: Local name length mismatch");
		kमुक्त_skb(skb);
		वापस ERR_PTR(-EIO);
	पूर्ण

	वापस skb;
पूर्ण

अटल काष्ठा sk_buff *btbcm_पढ़ो_local_version(काष्ठा hci_dev *hdev)
अणु
	काष्ठा sk_buff *skb;

	skb = __hci_cmd_sync(hdev, HCI_OP_READ_LOCAL_VERSION, 0, शून्य,
			     HCI_INIT_TIMEOUT);
	अगर (IS_ERR(skb)) अणु
		bt_dev_err(hdev, "BCM: Reading local version info failed (%ld)",
			   PTR_ERR(skb));
		वापस skb;
	पूर्ण

	अगर (skb->len != माप(काष्ठा hci_rp_पढ़ो_local_version)) अणु
		bt_dev_err(hdev, "BCM: Local version length mismatch");
		kमुक्त_skb(skb);
		वापस ERR_PTR(-EIO);
	पूर्ण

	वापस skb;
पूर्ण

अटल काष्ठा sk_buff *btbcm_पढ़ो_verbose_config(काष्ठा hci_dev *hdev)
अणु
	काष्ठा sk_buff *skb;

	skb = __hci_cmd_sync(hdev, 0xfc79, 0, शून्य, HCI_INIT_TIMEOUT);
	अगर (IS_ERR(skb)) अणु
		bt_dev_err(hdev, "BCM: Read verbose config info failed (%ld)",
			   PTR_ERR(skb));
		वापस skb;
	पूर्ण

	अगर (skb->len != 7) अणु
		bt_dev_err(hdev, "BCM: Verbose config length mismatch");
		kमुक्त_skb(skb);
		वापस ERR_PTR(-EIO);
	पूर्ण

	वापस skb;
पूर्ण

अटल काष्ठा sk_buff *btbcm_पढ़ो_controller_features(काष्ठा hci_dev *hdev)
अणु
	काष्ठा sk_buff *skb;

	skb = __hci_cmd_sync(hdev, 0xfc6e, 0, शून्य, HCI_INIT_TIMEOUT);
	अगर (IS_ERR(skb)) अणु
		bt_dev_err(hdev, "BCM: Read controller features failed (%ld)",
			   PTR_ERR(skb));
		वापस skb;
	पूर्ण

	अगर (skb->len != 9) अणु
		bt_dev_err(hdev, "BCM: Controller features length mismatch");
		kमुक्त_skb(skb);
		वापस ERR_PTR(-EIO);
	पूर्ण

	वापस skb;
पूर्ण

अटल काष्ठा sk_buff *btbcm_पढ़ो_usb_product(काष्ठा hci_dev *hdev)
अणु
	काष्ठा sk_buff *skb;

	skb = __hci_cmd_sync(hdev, 0xfc5a, 0, शून्य, HCI_INIT_TIMEOUT);
	अगर (IS_ERR(skb)) अणु
		bt_dev_err(hdev, "BCM: Read USB product info failed (%ld)",
			   PTR_ERR(skb));
		वापस skb;
	पूर्ण

	अगर (skb->len != 5) अणु
		bt_dev_err(hdev, "BCM: USB product length mismatch");
		kमुक्त_skb(skb);
		वापस ERR_PTR(-EIO);
	पूर्ण

	वापस skb;
पूर्ण

अटल पूर्णांक btbcm_पढ़ो_info(काष्ठा hci_dev *hdev)
अणु
	काष्ठा sk_buff *skb;

	/* Read Verbose Config Version Info */
	skb = btbcm_पढ़ो_verbose_config(hdev);
	अगर (IS_ERR(skb))
		वापस PTR_ERR(skb);

	bt_dev_info(hdev, "BCM: chip id %u", skb->data[1]);
	kमुक्त_skb(skb);

	/* Read Controller Features */
	skb = btbcm_पढ़ो_controller_features(hdev);
	अगर (IS_ERR(skb))
		वापस PTR_ERR(skb);

	bt_dev_info(hdev, "BCM: features 0x%2.2x", skb->data[1]);
	kमुक्त_skb(skb);

	वापस 0;
पूर्ण

अटल पूर्णांक btbcm_prपूर्णांक_local_name(काष्ठा hci_dev *hdev)
अणु
	काष्ठा sk_buff *skb;

	/* Read Local Name */
	skb = btbcm_पढ़ो_local_name(hdev);
	अगर (IS_ERR(skb))
		वापस PTR_ERR(skb);

	bt_dev_info(hdev, "%s", (अक्षर *)(skb->data + 1));
	kमुक्त_skb(skb);

	वापस 0;
पूर्ण

काष्ठा bcm_subver_table अणु
	u16 subver;
	स्थिर अक्षर *name;
पूर्ण;

अटल स्थिर काष्ठा bcm_subver_table bcm_uart_subver_table[] = अणु
	अणु 0x4103, "BCM4330B1"	पूर्ण,	/* 002.001.003 */
	अणु 0x410d, "BCM4334B0"	पूर्ण,	/* 002.001.013 */
	अणु 0x410e, "BCM43341B0"	पूर्ण,	/* 002.001.014 */
	अणु 0x4204, "BCM2076B1"	पूर्ण,	/* 002.002.004 */
	अणु 0x4406, "BCM4324B3"	पूर्ण,	/* 002.004.006 */
	अणु 0x4606, "BCM4324B5"	पूर्ण,	/* 002.006.006 */
	अणु 0x6109, "BCM4335C0"	पूर्ण,	/* 003.001.009 */
	अणु 0x610c, "BCM4354"	पूर्ण,	/* 003.001.012 */
	अणु 0x2122, "BCM4343A0"	पूर्ण,	/* 001.001.034 */
	अणु 0x2209, "BCM43430A1"  पूर्ण,	/* 001.002.009 */
	अणु 0x6119, "BCM4345C0"	पूर्ण,	/* 003.001.025 */
	अणु 0x6606, "BCM4345C5"	पूर्ण,	/* 003.006.006 */
	अणु 0x230f, "BCM4356A2"	पूर्ण,	/* 001.003.015 */
	अणु 0x220e, "BCM20702A1"  पूर्ण,	/* 001.002.014 */
	अणु 0x4217, "BCM4329B1"   पूर्ण,	/* 002.002.023 */
	अणु 0x6106, "BCM4359C0"	पूर्ण,	/* 003.001.006 */
	अणु 0x4106, "BCM4335A0"	पूर्ण,	/* 002.001.006 */
	अणु पूर्ण
पूर्ण;

अटल स्थिर काष्ठा bcm_subver_table bcm_usb_subver_table[] = अणु
	अणु 0x2105, "BCM20703A1"	पूर्ण,	/* 001.001.005 */
	अणु 0x210b, "BCM43142A0"	पूर्ण,	/* 001.001.011 */
	अणु 0x2112, "BCM4314A0"	पूर्ण,	/* 001.001.018 */
	अणु 0x2118, "BCM20702A0"	पूर्ण,	/* 001.001.024 */
	अणु 0x2126, "BCM4335A0"	पूर्ण,	/* 001.001.038 */
	अणु 0x220e, "BCM20702A1"	पूर्ण,	/* 001.002.014 */
	अणु 0x230f, "BCM4356A2"	पूर्ण,	/* 001.003.015 */
	अणु 0x4106, "BCM4335B0"	पूर्ण,	/* 002.001.006 */
	अणु 0x410e, "BCM20702B0"	पूर्ण,	/* 002.001.014 */
	अणु 0x6109, "BCM4335C0"	पूर्ण,	/* 003.001.009 */
	अणु 0x610c, "BCM4354"	पूर्ण,	/* 003.001.012 */
	अणु 0x6607, "BCM4350C5"	पूर्ण,	/* 003.006.007 */
	अणु पूर्ण
पूर्ण;

पूर्णांक btbcm_initialize(काष्ठा hci_dev *hdev, bool *fw_load_करोne)
अणु
	u16 subver, rev, pid, vid;
	काष्ठा sk_buff *skb;
	काष्ठा hci_rp_पढ़ो_local_version *ver;
	स्थिर काष्ठा bcm_subver_table *bcm_subver_table;
	स्थिर अक्षर *hw_name = शून्य;
	अक्षर postfix[16] = "";
	पूर्णांक fw_name_count = 0;
	bcm_fw_name *fw_name;
	स्थिर काष्ठा firmware *fw;
	पूर्णांक i, err;

	/* Reset */
	err = btbcm_reset(hdev);
	अगर (err)
		वापस err;

	/* Read Local Version Info */
	skb = btbcm_पढ़ो_local_version(hdev);
	अगर (IS_ERR(skb))
		वापस PTR_ERR(skb);

	ver = (काष्ठा hci_rp_पढ़ो_local_version *)skb->data;
	rev = le16_to_cpu(ver->hci_rev);
	subver = le16_to_cpu(ver->lmp_subver);
	kमुक्त_skb(skb);

	/* Read controller inक्रमmation */
	अगर (!(*fw_load_करोne)) अणु
		err = btbcm_पढ़ो_info(hdev);
		अगर (err)
			वापस err;
	पूर्ण
	err = btbcm_prपूर्णांक_local_name(hdev);
	अगर (err)
		वापस err;

	bcm_subver_table = (hdev->bus == HCI_USB) ? bcm_usb_subver_table :
						    bcm_uart_subver_table;

	क्रम (i = 0; bcm_subver_table[i].name; i++) अणु
		अगर (subver == bcm_subver_table[i].subver) अणु
			hw_name = bcm_subver_table[i].name;
			अवरोध;
		पूर्ण
	पूर्ण

	bt_dev_info(hdev, "%s (%3.3u.%3.3u.%3.3u) build %4.4u",
		    hw_name ? hw_name : "BCM", (subver & 0xe000) >> 13,
		    (subver & 0x1f00) >> 8, (subver & 0x00ff), rev & 0x0fff);

	अगर (*fw_load_करोne)
		वापस 0;

	अगर (hdev->bus == HCI_USB) अणु
		/* Read USB Product Info */
		skb = btbcm_पढ़ो_usb_product(hdev);
		अगर (IS_ERR(skb))
			वापस PTR_ERR(skb);

		vid = get_unaligned_le16(skb->data + 1);
		pid = get_unaligned_le16(skb->data + 3);
		kमुक्त_skb(skb);

		snम_लिखो(postfix, माप(postfix), "-%4.4x-%4.4x", vid, pid);
	पूर्ण

	fw_name = kदो_स्मृति(BCM_FW_NAME_COUNT_MAX * BCM_FW_NAME_LEN, GFP_KERNEL);
	अगर (!fw_name)
		वापस -ENOMEM;

	अगर (hw_name) अणु
		snम_लिखो(fw_name[fw_name_count], BCM_FW_NAME_LEN,
			 "brcm/%s%s.hcd", hw_name, postfix);
		fw_name_count++;
	पूर्ण

	snम_लिखो(fw_name[fw_name_count], BCM_FW_NAME_LEN,
		 "brcm/BCM%s.hcd", postfix);
	fw_name_count++;

	क्रम (i = 0; i < fw_name_count; i++) अणु
		err = firmware_request_nowarn(&fw, fw_name[i], &hdev->dev);
		अगर (err == 0) अणु
			bt_dev_info(hdev, "%s '%s' Patch",
				    hw_name ? hw_name : "BCM", fw_name[i]);
			*fw_load_करोne = true;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (*fw_load_करोne) अणु
		err = btbcm_patchram(hdev, fw);
		अगर (err)
			bt_dev_info(hdev, "BCM: Patch failed (%d)", err);

		release_firmware(fw);
	पूर्ण अन्यथा अणु
		bt_dev_err(hdev, "BCM: firmware Patch file not found, tried:");
		क्रम (i = 0; i < fw_name_count; i++)
			bt_dev_err(hdev, "BCM: '%s'", fw_name[i]);
	पूर्ण

	kमुक्त(fw_name);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(btbcm_initialize);

पूर्णांक btbcm_finalize(काष्ठा hci_dev *hdev, bool *fw_load_करोne)
अणु
	पूर्णांक err;

	/* Re-initialize अगर necessary */
	अगर (*fw_load_करोne) अणु
		err = btbcm_initialize(hdev, fw_load_करोne);
		अगर (err)
			वापस err;
	पूर्ण

	btbcm_check_bdaddr(hdev);

	set_bit(HCI_QUIRK_STRICT_DUPLICATE_FILTER, &hdev->quirks);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(btbcm_finalize);

पूर्णांक btbcm_setup_patchram(काष्ठा hci_dev *hdev)
अणु
	bool fw_load_करोne = false;
	पूर्णांक err;

	/* Initialize */
	err = btbcm_initialize(hdev, &fw_load_करोne);
	अगर (err)
		वापस err;

	/* Re-initialize after loading Patch */
	वापस btbcm_finalize(hdev, &fw_load_करोne);
पूर्ण
EXPORT_SYMBOL_GPL(btbcm_setup_patchram);

पूर्णांक btbcm_setup_apple(काष्ठा hci_dev *hdev)
अणु
	काष्ठा sk_buff *skb;
	पूर्णांक err;

	/* Reset */
	err = btbcm_reset(hdev);
	अगर (err)
		वापस err;

	/* Read Verbose Config Version Info */
	skb = btbcm_पढ़ो_verbose_config(hdev);
	अगर (!IS_ERR(skb)) अणु
		bt_dev_info(hdev, "BCM: chip id %u build %4.4u",
			    skb->data[1], get_unaligned_le16(skb->data + 5));
		kमुक्त_skb(skb);
	पूर्ण

	/* Read USB Product Info */
	skb = btbcm_पढ़ो_usb_product(hdev);
	अगर (!IS_ERR(skb)) अणु
		bt_dev_info(hdev, "BCM: product %4.4x:%4.4x",
			    get_unaligned_le16(skb->data + 1),
			    get_unaligned_le16(skb->data + 3));
		kमुक्त_skb(skb);
	पूर्ण

	/* Read Controller Features */
	skb = btbcm_पढ़ो_controller_features(hdev);
	अगर (!IS_ERR(skb)) अणु
		bt_dev_info(hdev, "BCM: features 0x%2.2x", skb->data[1]);
		kमुक्त_skb(skb);
	पूर्ण

	/* Read Local Name */
	skb = btbcm_पढ़ो_local_name(hdev);
	अगर (!IS_ERR(skb)) अणु
		bt_dev_info(hdev, "%s", (अक्षर *)(skb->data + 1));
		kमुक्त_skb(skb);
	पूर्ण

	set_bit(HCI_QUIRK_STRICT_DUPLICATE_FILTER, &hdev->quirks);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(btbcm_setup_apple);

MODULE_AUTHOR("Marcel Holtmann <marcel@holtmann.org>");
MODULE_DESCRIPTION("Bluetooth support for Broadcom devices ver " VERSION);
MODULE_VERSION(VERSION);
MODULE_LICENSE("GPL");
