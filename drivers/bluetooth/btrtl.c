<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Bluetooth support क्रम Realtek devices
 *
 *  Copyright (C) 2015 Endless Mobile, Inc.
 */

#समावेश <linux/module.h>
#समावेश <linux/firmware.h>
#समावेश <यंत्र/unaligned.h>
#समावेश <linux/usb.h>

#समावेश <net/bluetooth/bluetooth.h>
#समावेश <net/bluetooth/hci_core.h>

#समावेश "btrtl.h"

#घोषणा VERSION "0.1"

#घोषणा RTL_EPATCH_SIGNATURE	"Realtech"
#घोषणा RTL_ROM_LMP_8723A	0x1200
#घोषणा RTL_ROM_LMP_8723B	0x8723
#घोषणा RTL_ROM_LMP_8821A	0x8821
#घोषणा RTL_ROM_LMP_8761A	0x8761
#घोषणा RTL_ROM_LMP_8822B	0x8822
#घोषणा RTL_ROM_LMP_8852A	0x8852
#घोषणा RTL_CONFIG_MAGIC	0x8723ab55

#घोषणा IC_MATCH_FL_LMPSUBV	(1 << 0)
#घोषणा IC_MATCH_FL_HCIREV	(1 << 1)
#घोषणा IC_MATCH_FL_HCIVER	(1 << 2)
#घोषणा IC_MATCH_FL_HCIBUS	(1 << 3)
#घोषणा IC_INFO(lmps, hcir, hciv, bus) \
	.match_flags = IC_MATCH_FL_LMPSUBV | IC_MATCH_FL_HCIREV | \
		       IC_MATCH_FL_HCIVER | IC_MATCH_FL_HCIBUS, \
	.lmp_subver = (lmps), \
	.hci_rev = (hcir), \
	.hci_ver = (hciv), \
	.hci_bus = (bus)

क्रमागत btrtl_chip_id अणु
	CHIP_ID_8723A,
	CHIP_ID_8723B,
	CHIP_ID_8821A,
	CHIP_ID_8761A,
	CHIP_ID_8822B = 8,
	CHIP_ID_8723D,
	CHIP_ID_8821C,
	CHIP_ID_8822C = 13,
	CHIP_ID_8761B,
	CHIP_ID_8852A = 18,
पूर्ण;

काष्ठा id_table अणु
	__u16 match_flags;
	__u16 lmp_subver;
	__u16 hci_rev;
	__u8 hci_ver;
	__u8 hci_bus;
	bool config_needed;
	bool has_rom_version;
	अक्षर *fw_name;
	अक्षर *cfg_name;
पूर्ण;

काष्ठा btrtl_device_info अणु
	स्थिर काष्ठा id_table *ic_info;
	u8 rom_version;
	u8 *fw_data;
	पूर्णांक fw_len;
	u8 *cfg_data;
	पूर्णांक cfg_len;
	bool drop_fw;
	पूर्णांक project_id;
पूर्ण;

अटल स्थिर काष्ठा id_table ic_id_table[] = अणु
	/* 8723A */
	अणु IC_INFO(RTL_ROM_LMP_8723A, 0xb, 0x6, HCI_USB),
	  .config_needed = false,
	  .has_rom_version = false,
	  .fw_name = "rtl_bt/rtl8723a_fw.bin",
	  .cfg_name = शून्य पूर्ण,

	/* 8723BS */
	अणु IC_INFO(RTL_ROM_LMP_8723B, 0xb, 0x6, HCI_UART),
	  .config_needed = true,
	  .has_rom_version = true,
	  .fw_name  = "rtl_bt/rtl8723bs_fw.bin",
	  .cfg_name = "rtl_bt/rtl8723bs_config" पूर्ण,

	/* 8723B */
	अणु IC_INFO(RTL_ROM_LMP_8723B, 0xb, 0x6, HCI_USB),
	  .config_needed = false,
	  .has_rom_version = true,
	  .fw_name  = "rtl_bt/rtl8723b_fw.bin",
	  .cfg_name = "rtl_bt/rtl8723b_config" पूर्ण,

	/* 8723D */
	अणु IC_INFO(RTL_ROM_LMP_8723B, 0xd, 0x8, HCI_USB),
	  .config_needed = true,
	  .has_rom_version = true,
	  .fw_name  = "rtl_bt/rtl8723d_fw.bin",
	  .cfg_name = "rtl_bt/rtl8723d_config" पूर्ण,

	/* 8723DS */
	अणु IC_INFO(RTL_ROM_LMP_8723B, 0xd, 0x8, HCI_UART),
	  .config_needed = true,
	  .has_rom_version = true,
	  .fw_name  = "rtl_bt/rtl8723ds_fw.bin",
	  .cfg_name = "rtl_bt/rtl8723ds_config" पूर्ण,

	/* 8821A */
	अणु IC_INFO(RTL_ROM_LMP_8821A, 0xa, 0x6, HCI_USB),
	  .config_needed = false,
	  .has_rom_version = true,
	  .fw_name  = "rtl_bt/rtl8821a_fw.bin",
	  .cfg_name = "rtl_bt/rtl8821a_config" पूर्ण,

	/* 8821C */
	अणु IC_INFO(RTL_ROM_LMP_8821A, 0xc, 0x8, HCI_USB),
	  .config_needed = false,
	  .has_rom_version = true,
	  .fw_name  = "rtl_bt/rtl8821c_fw.bin",
	  .cfg_name = "rtl_bt/rtl8821c_config" पूर्ण,

	/* 8761A */
	अणु IC_INFO(RTL_ROM_LMP_8761A, 0xa, 0x6, HCI_USB),
	  .config_needed = false,
	  .has_rom_version = true,
	  .fw_name  = "rtl_bt/rtl8761a_fw.bin",
	  .cfg_name = "rtl_bt/rtl8761a_config" पूर्ण,

	/* 8761B */
	अणु IC_INFO(RTL_ROM_LMP_8761A, 0xb, 0xa, HCI_USB),
	  .config_needed = false,
	  .has_rom_version = true,
	  .fw_name  = "rtl_bt/rtl8761b_fw.bin",
	  .cfg_name = "rtl_bt/rtl8761b_config" पूर्ण,

	/* 8822C with UART पूर्णांकerface */
	अणु IC_INFO(RTL_ROM_LMP_8822B, 0xc, 0xa, HCI_UART),
	  .config_needed = true,
	  .has_rom_version = true,
	  .fw_name  = "rtl_bt/rtl8822cs_fw.bin",
	  .cfg_name = "rtl_bt/rtl8822cs_config" पूर्ण,

	/* 8822C with USB पूर्णांकerface */
	अणु IC_INFO(RTL_ROM_LMP_8822B, 0xc, 0xa, HCI_USB),
	  .config_needed = false,
	  .has_rom_version = true,
	  .fw_name  = "rtl_bt/rtl8822cu_fw.bin",
	  .cfg_name = "rtl_bt/rtl8822cu_config" पूर्ण,

	/* 8822B */
	अणु IC_INFO(RTL_ROM_LMP_8822B, 0xb, 0x7, HCI_USB),
	  .config_needed = true,
	  .has_rom_version = true,
	  .fw_name  = "rtl_bt/rtl8822b_fw.bin",
	  .cfg_name = "rtl_bt/rtl8822b_config" पूर्ण,

	/* 8852A */
	अणु IC_INFO(RTL_ROM_LMP_8852A, 0xa, 0xb, HCI_USB),
	  .config_needed = false,
	  .has_rom_version = true,
	  .fw_name  = "rtl_bt/rtl8852au_fw.bin",
	  .cfg_name = "rtl_bt/rtl8852au_config" पूर्ण,
	पूर्ण;

अटल स्थिर काष्ठा id_table *btrtl_match_ic(u16 lmp_subver, u16 hci_rev,
					     u8 hci_ver, u8 hci_bus)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(ic_id_table); i++) अणु
		अगर ((ic_id_table[i].match_flags & IC_MATCH_FL_LMPSUBV) &&
		    (ic_id_table[i].lmp_subver != lmp_subver))
			जारी;
		अगर ((ic_id_table[i].match_flags & IC_MATCH_FL_HCIREV) &&
		    (ic_id_table[i].hci_rev != hci_rev))
			जारी;
		अगर ((ic_id_table[i].match_flags & IC_MATCH_FL_HCIVER) &&
		    (ic_id_table[i].hci_ver != hci_ver))
			जारी;
		अगर ((ic_id_table[i].match_flags & IC_MATCH_FL_HCIBUS) &&
		    (ic_id_table[i].hci_bus != hci_bus))
			जारी;

		अवरोध;
	पूर्ण
	अगर (i >= ARRAY_SIZE(ic_id_table))
		वापस शून्य;

	वापस &ic_id_table[i];
पूर्ण

अटल काष्ठा sk_buff *btrtl_पढ़ो_local_version(काष्ठा hci_dev *hdev)
अणु
	काष्ठा sk_buff *skb;

	skb = __hci_cmd_sync(hdev, HCI_OP_READ_LOCAL_VERSION, 0, शून्य,
			     HCI_INIT_TIMEOUT);
	अगर (IS_ERR(skb)) अणु
		rtl_dev_err(hdev, "HCI_OP_READ_LOCAL_VERSION failed (%ld)",
			    PTR_ERR(skb));
		वापस skb;
	पूर्ण

	अगर (skb->len != माप(काष्ठा hci_rp_पढ़ो_local_version)) अणु
		rtl_dev_err(hdev, "HCI_OP_READ_LOCAL_VERSION event length mismatch");
		kमुक्त_skb(skb);
		वापस ERR_PTR(-EIO);
	पूर्ण

	वापस skb;
पूर्ण

अटल पूर्णांक rtl_पढ़ो_rom_version(काष्ठा hci_dev *hdev, u8 *version)
अणु
	काष्ठा rtl_rom_version_evt *rom_version;
	काष्ठा sk_buff *skb;

	/* Read RTL ROM version command */
	skb = __hci_cmd_sync(hdev, 0xfc6d, 0, शून्य, HCI_INIT_TIMEOUT);
	अगर (IS_ERR(skb)) अणु
		rtl_dev_err(hdev, "Read ROM version failed (%ld)",
			    PTR_ERR(skb));
		वापस PTR_ERR(skb);
	पूर्ण

	अगर (skb->len != माप(*rom_version)) अणु
		rtl_dev_err(hdev, "version event length mismatch");
		kमुक्त_skb(skb);
		वापस -EIO;
	पूर्ण

	rom_version = (काष्ठा rtl_rom_version_evt *)skb->data;
	rtl_dev_info(hdev, "rom_version status=%x version=%x",
		     rom_version->status, rom_version->version);

	*version = rom_version->version;

	kमुक्त_skb(skb);
	वापस 0;
पूर्ण

अटल पूर्णांक rtlbt_parse_firmware(काष्ठा hci_dev *hdev,
				काष्ठा btrtl_device_info *btrtl_dev,
				अचिन्हित अक्षर **_buf)
अणु
	अटल स्थिर u8 extension_sig[] = अणु 0x51, 0x04, 0xfd, 0x77 पूर्ण;
	काष्ठा rtl_epatch_header *epatch_info;
	अचिन्हित अक्षर *buf;
	पूर्णांक i, len;
	माप_प्रकार min_size;
	u8 opcode, length, data;
	पूर्णांक project_id = -1;
	स्थिर अचिन्हित अक्षर *fwptr, *chip_id_base;
	स्थिर अचिन्हित अक्षर *patch_length_base, *patch_offset_base;
	u32 patch_offset = 0;
	u16 patch_length, num_patches;
	अटल स्थिर काष्ठा अणु
		__u16 lmp_subver;
		__u8 id;
	पूर्ण project_id_to_lmp_subver[] = अणु
		अणु RTL_ROM_LMP_8723A, 0 पूर्ण,
		अणु RTL_ROM_LMP_8723B, 1 पूर्ण,
		अणु RTL_ROM_LMP_8821A, 2 पूर्ण,
		अणु RTL_ROM_LMP_8761A, 3 पूर्ण,
		अणु RTL_ROM_LMP_8822B, 8 पूर्ण,
		अणु RTL_ROM_LMP_8723B, 9 पूर्ण,	/* 8723D */
		अणु RTL_ROM_LMP_8821A, 10 पूर्ण,	/* 8821C */
		अणु RTL_ROM_LMP_8822B, 13 पूर्ण,	/* 8822C */
		अणु RTL_ROM_LMP_8761A, 14 पूर्ण,	/* 8761B */
		अणु RTL_ROM_LMP_8852A, 18 पूर्ण,	/* 8852A */
	पूर्ण;

	min_size = माप(काष्ठा rtl_epatch_header) + माप(extension_sig) + 3;
	अगर (btrtl_dev->fw_len < min_size)
		वापस -EINVAL;

	fwptr = btrtl_dev->fw_data + btrtl_dev->fw_len - माप(extension_sig);
	अगर (स_भेद(fwptr, extension_sig, माप(extension_sig)) != 0) अणु
		rtl_dev_err(hdev, "extension section signature mismatch");
		वापस -EINVAL;
	पूर्ण

	/* Loop from the end of the firmware parsing inकाष्ठाions, until
	 * we find an inकाष्ठाion that identअगरies the "project ID" क्रम the
	 * hardware supported by this firwmare file.
	 * Once we have that, we द्विगुन-check that that project_id is suitable
	 * क्रम the hardware we are working with.
	 */
	जबतक (fwptr >= btrtl_dev->fw_data + (माप(*epatch_info) + 3)) अणु
		opcode = *--fwptr;
		length = *--fwptr;
		data = *--fwptr;

		BT_DBG("check op=%x len=%x data=%x", opcode, length, data);

		अगर (opcode == 0xff) /* खातापूर्ण */
			अवरोध;

		अगर (length == 0) अणु
			rtl_dev_err(hdev, "found instruction with length 0");
			वापस -EINVAL;
		पूर्ण

		अगर (opcode == 0 && length == 1) अणु
			project_id = data;
			अवरोध;
		पूर्ण

		fwptr -= length;
	पूर्ण

	अगर (project_id < 0) अणु
		rtl_dev_err(hdev, "failed to find version instruction");
		वापस -EINVAL;
	पूर्ण

	/* Find project_id in table */
	क्रम (i = 0; i < ARRAY_SIZE(project_id_to_lmp_subver); i++) अणु
		अगर (project_id == project_id_to_lmp_subver[i].id) अणु
			btrtl_dev->project_id = project_id;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (i >= ARRAY_SIZE(project_id_to_lmp_subver)) अणु
		rtl_dev_err(hdev, "unknown project id %d", project_id);
		वापस -EINVAL;
	पूर्ण

	अगर (btrtl_dev->ic_info->lmp_subver !=
				project_id_to_lmp_subver[i].lmp_subver) अणु
		rtl_dev_err(hdev, "firmware is for %x but this is a %x",
			    project_id_to_lmp_subver[i].lmp_subver,
			    btrtl_dev->ic_info->lmp_subver);
		वापस -EINVAL;
	पूर्ण

	epatch_info = (काष्ठा rtl_epatch_header *)btrtl_dev->fw_data;
	अगर (स_भेद(epatch_info->signature, RTL_EPATCH_SIGNATURE, 8) != 0) अणु
		rtl_dev_err(hdev, "bad EPATCH signature");
		वापस -EINVAL;
	पूर्ण

	num_patches = le16_to_cpu(epatch_info->num_patches);
	BT_DBG("fw_version=%x, num_patches=%d",
	       le32_to_cpu(epatch_info->fw_version), num_patches);

	/* After the rtl_epatch_header there is a funky patch metadata section.
	 * Assuming 2 patches, the layout is:
	 * ChipID1 ChipID2 PatchLength1 PatchLength2 PatchOffset1 PatchOffset2
	 *
	 * Find the right patch क्रम this chip.
	 */
	min_size += 8 * num_patches;
	अगर (btrtl_dev->fw_len < min_size)
		वापस -EINVAL;

	chip_id_base = btrtl_dev->fw_data + माप(काष्ठा rtl_epatch_header);
	patch_length_base = chip_id_base + (माप(u16) * num_patches);
	patch_offset_base = patch_length_base + (माप(u16) * num_patches);
	क्रम (i = 0; i < num_patches; i++) अणु
		u16 chip_id = get_unaligned_le16(chip_id_base +
						 (i * माप(u16)));
		अगर (chip_id == btrtl_dev->rom_version + 1) अणु
			patch_length = get_unaligned_le16(patch_length_base +
							  (i * माप(u16)));
			patch_offset = get_unaligned_le32(patch_offset_base +
							  (i * माप(u32)));
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!patch_offset) अणु
		rtl_dev_err(hdev, "didn't find patch for chip id %d",
			    btrtl_dev->rom_version);
		वापस -EINVAL;
	पूर्ण

	BT_DBG("length=%x offset=%x index %d", patch_length, patch_offset, i);
	min_size = patch_offset + patch_length;
	अगर (btrtl_dev->fw_len < min_size)
		वापस -EINVAL;

	/* Copy the firmware पूर्णांकo a new buffer and ग_लिखो the version at
	 * the end.
	 */
	len = patch_length;
	buf = kvदो_स्मृति(patch_length, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	स_नकल(buf, btrtl_dev->fw_data + patch_offset, patch_length - 4);
	स_नकल(buf + patch_length - 4, &epatch_info->fw_version, 4);

	*_buf = buf;
	वापस len;
पूर्ण

अटल पूर्णांक rtl_करोwnload_firmware(काष्ठा hci_dev *hdev,
				 स्थिर अचिन्हित अक्षर *data, पूर्णांक fw_len)
अणु
	काष्ठा rtl_करोwnload_cmd *dl_cmd;
	पूर्णांक frag_num = fw_len / RTL_FRAG_LEN + 1;
	पूर्णांक frag_len = RTL_FRAG_LEN;
	पूर्णांक ret = 0;
	पूर्णांक i;
	काष्ठा sk_buff *skb;
	काष्ठा hci_rp_पढ़ो_local_version *rp;

	dl_cmd = kदो_स्मृति(माप(काष्ठा rtl_करोwnload_cmd), GFP_KERNEL);
	अगर (!dl_cmd)
		वापस -ENOMEM;

	क्रम (i = 0; i < frag_num; i++) अणु
		काष्ठा sk_buff *skb;

		BT_DBG("download fw (%d/%d)", i, frag_num);

		अगर (i > 0x7f)
			dl_cmd->index = (i & 0x7f) + 1;
		अन्यथा
			dl_cmd->index = i;

		अगर (i == (frag_num - 1)) अणु
			dl_cmd->index |= 0x80; /* data end */
			frag_len = fw_len % RTL_FRAG_LEN;
		पूर्ण
		स_नकल(dl_cmd->data, data, frag_len);

		/* Send करोwnload command */
		skb = __hci_cmd_sync(hdev, 0xfc20, frag_len + 1, dl_cmd,
				     HCI_INIT_TIMEOUT);
		अगर (IS_ERR(skb)) अणु
			rtl_dev_err(hdev, "download fw command failed (%ld)",
				    PTR_ERR(skb));
			ret = PTR_ERR(skb);
			जाओ out;
		पूर्ण

		अगर (skb->len != माप(काष्ठा rtl_करोwnload_response)) अणु
			rtl_dev_err(hdev, "download fw event length mismatch");
			kमुक्त_skb(skb);
			ret = -EIO;
			जाओ out;
		पूर्ण

		kमुक्त_skb(skb);
		data += RTL_FRAG_LEN;
	पूर्ण

	skb = btrtl_पढ़ो_local_version(hdev);
	अगर (IS_ERR(skb)) अणु
		ret = PTR_ERR(skb);
		rtl_dev_err(hdev, "read local version failed");
		जाओ out;
	पूर्ण

	rp = (काष्ठा hci_rp_पढ़ो_local_version *)skb->data;
	rtl_dev_info(hdev, "fw version 0x%04x%04x",
		     __le16_to_cpu(rp->hci_rev), __le16_to_cpu(rp->lmp_subver));
	kमुक्त_skb(skb);

out:
	kमुक्त(dl_cmd);
	वापस ret;
पूर्ण

अटल पूर्णांक rtl_load_file(काष्ठा hci_dev *hdev, स्थिर अक्षर *name, u8 **buff)
अणु
	स्थिर काष्ठा firmware *fw;
	पूर्णांक ret;

	rtl_dev_info(hdev, "loading %s", name);
	ret = request_firmware(&fw, name, &hdev->dev);
	अगर (ret < 0)
		वापस ret;
	ret = fw->size;
	*buff = kvदो_स्मृति(fw->size, GFP_KERNEL);
	अगर (*buff)
		स_नकल(*buff, fw->data, ret);
	अन्यथा
		ret = -ENOMEM;

	release_firmware(fw);

	वापस ret;
पूर्ण

अटल पूर्णांक btrtl_setup_rtl8723a(काष्ठा hci_dev *hdev,
				काष्ठा btrtl_device_info *btrtl_dev)
अणु
	अगर (btrtl_dev->fw_len < 8)
		वापस -EINVAL;

	/* Check that the firmware करोesn't have the epatch signature
	 * (which is only क्रम RTL8723B and newer).
	 */
	अगर (!स_भेद(btrtl_dev->fw_data, RTL_EPATCH_SIGNATURE, 8)) अणु
		rtl_dev_err(hdev, "unexpected EPATCH signature!");
		वापस -EINVAL;
	पूर्ण

	वापस rtl_करोwnload_firmware(hdev, btrtl_dev->fw_data,
				     btrtl_dev->fw_len);
पूर्ण

अटल पूर्णांक btrtl_setup_rtl8723b(काष्ठा hci_dev *hdev,
				काष्ठा btrtl_device_info *btrtl_dev)
अणु
	अचिन्हित अक्षर *fw_data = शून्य;
	पूर्णांक ret;
	u8 *tbuff;

	ret = rtlbt_parse_firmware(hdev, btrtl_dev, &fw_data);
	अगर (ret < 0)
		जाओ out;

	अगर (btrtl_dev->cfg_len > 0) अणु
		tbuff = kvzalloc(ret + btrtl_dev->cfg_len, GFP_KERNEL);
		अगर (!tbuff) अणु
			ret = -ENOMEM;
			जाओ out;
		पूर्ण

		स_नकल(tbuff, fw_data, ret);
		kvमुक्त(fw_data);

		स_नकल(tbuff + ret, btrtl_dev->cfg_data, btrtl_dev->cfg_len);
		ret += btrtl_dev->cfg_len;

		fw_data = tbuff;
	पूर्ण

	rtl_dev_info(hdev, "cfg_sz %d, total sz %d", btrtl_dev->cfg_len, ret);

	ret = rtl_करोwnload_firmware(hdev, fw_data, ret);

out:
	kvमुक्त(fw_data);
	वापस ret;
पूर्ण

व्योम btrtl_मुक्त(काष्ठा btrtl_device_info *btrtl_dev)
अणु
	kvमुक्त(btrtl_dev->fw_data);
	kvमुक्त(btrtl_dev->cfg_data);
	kमुक्त(btrtl_dev);
पूर्ण
EXPORT_SYMBOL_GPL(btrtl_मुक्त);

काष्ठा btrtl_device_info *btrtl_initialize(काष्ठा hci_dev *hdev,
					   स्थिर अक्षर *postfix)
अणु
	काष्ठा btrtl_device_info *btrtl_dev;
	काष्ठा sk_buff *skb;
	काष्ठा hci_rp_पढ़ो_local_version *resp;
	अक्षर cfg_name[40];
	u16 hci_rev, lmp_subver;
	u8 hci_ver;
	पूर्णांक ret;
	u16 opcode;
	u8 cmd[2];

	btrtl_dev = kzalloc(माप(*btrtl_dev), GFP_KERNEL);
	अगर (!btrtl_dev) अणु
		ret = -ENOMEM;
		जाओ err_alloc;
	पूर्ण

	skb = btrtl_पढ़ो_local_version(hdev);
	अगर (IS_ERR(skb)) अणु
		ret = PTR_ERR(skb);
		जाओ err_मुक्त;
	पूर्ण

	resp = (काष्ठा hci_rp_पढ़ो_local_version *)skb->data;
	rtl_dev_info(hdev, "examining hci_ver=%02x hci_rev=%04x lmp_ver=%02x lmp_subver=%04x",
		     resp->hci_ver, resp->hci_rev,
		     resp->lmp_ver, resp->lmp_subver);

	hci_ver = resp->hci_ver;
	hci_rev = le16_to_cpu(resp->hci_rev);
	lmp_subver = le16_to_cpu(resp->lmp_subver);

	अगर (resp->hci_ver == 0x8 && le16_to_cpu(resp->hci_rev) == 0x826c &&
	    resp->lmp_ver == 0x8 && le16_to_cpu(resp->lmp_subver) == 0xa99e)
		btrtl_dev->drop_fw = true;

	अगर (btrtl_dev->drop_fw) अणु
		opcode = hci_opcode_pack(0x3f, 0x66);
		cmd[0] = opcode & 0xff;
		cmd[1] = opcode >> 8;

		skb = bt_skb_alloc(माप(cmd), GFP_KERNEL);
		अगर (!skb)
			जाओ out_मुक्त;

		skb_put_data(skb, cmd, माप(cmd));
		hci_skb_pkt_type(skb) = HCI_COMMAND_PKT;

		hdev->send(hdev, skb);

		/* Ensure the above venकरोr command is sent to controller and
		 * process has करोne.
		 */
		msleep(200);

		/* Read the local version again. Expect to have the vanilla
		 * version as cold boot.
		 */
		skb = btrtl_पढ़ो_local_version(hdev);
		अगर (IS_ERR(skb)) अणु
			ret = PTR_ERR(skb);
			जाओ err_मुक्त;
		पूर्ण

		resp = (काष्ठा hci_rp_पढ़ो_local_version *)skb->data;
		rtl_dev_info(hdev, "examining hci_ver=%02x hci_rev=%04x lmp_ver=%02x lmp_subver=%04x",
			     resp->hci_ver, resp->hci_rev,
			     resp->lmp_ver, resp->lmp_subver);

		hci_ver = resp->hci_ver;
		hci_rev = le16_to_cpu(resp->hci_rev);
		lmp_subver = le16_to_cpu(resp->lmp_subver);
	पूर्ण
out_मुक्त:
	kमुक्त_skb(skb);

	btrtl_dev->ic_info = btrtl_match_ic(lmp_subver, hci_rev, hci_ver,
					    hdev->bus);

	अगर (!btrtl_dev->ic_info) अणु
		rtl_dev_info(hdev, "unknown IC info, lmp subver %04x, hci rev %04x, hci ver %04x",
			    lmp_subver, hci_rev, hci_ver);
		वापस btrtl_dev;
	पूर्ण

	अगर (btrtl_dev->ic_info->has_rom_version) अणु
		ret = rtl_पढ़ो_rom_version(hdev, &btrtl_dev->rom_version);
		अगर (ret)
			जाओ err_मुक्त;
	पूर्ण

	btrtl_dev->fw_len = rtl_load_file(hdev, btrtl_dev->ic_info->fw_name,
					  &btrtl_dev->fw_data);
	अगर (btrtl_dev->fw_len < 0) अणु
		rtl_dev_err(hdev, "firmware file %s not found",
			    btrtl_dev->ic_info->fw_name);
		ret = btrtl_dev->fw_len;
		जाओ err_मुक्त;
	पूर्ण

	अगर (btrtl_dev->ic_info->cfg_name) अणु
		अगर (postfix) अणु
			snम_लिखो(cfg_name, माप(cfg_name), "%s-%s.bin",
				 btrtl_dev->ic_info->cfg_name, postfix);
		पूर्ण अन्यथा अणु
			snम_लिखो(cfg_name, माप(cfg_name), "%s.bin",
				 btrtl_dev->ic_info->cfg_name);
		पूर्ण
		btrtl_dev->cfg_len = rtl_load_file(hdev, cfg_name,
						   &btrtl_dev->cfg_data);
		अगर (btrtl_dev->ic_info->config_needed &&
		    btrtl_dev->cfg_len <= 0) अणु
			rtl_dev_err(hdev, "mandatory config file %s not found",
				    btrtl_dev->ic_info->cfg_name);
			ret = btrtl_dev->cfg_len;
			जाओ err_मुक्त;
		पूर्ण
	पूर्ण

	/* RTL8822CE supports the Microsoft venकरोr extension and uses 0xFCF0
	 * क्रम VsMsftOpCode.
	 */
	अगर (lmp_subver == RTL_ROM_LMP_8822B)
		hci_set_msft_opcode(hdev, 0xFCF0);

	वापस btrtl_dev;

err_मुक्त:
	btrtl_मुक्त(btrtl_dev);
err_alloc:
	वापस ERR_PTR(ret);
पूर्ण
EXPORT_SYMBOL_GPL(btrtl_initialize);

पूर्णांक btrtl_करोwnload_firmware(काष्ठा hci_dev *hdev,
			    काष्ठा btrtl_device_info *btrtl_dev)
अणु
	/* Match a set of subver values that correspond to stock firmware,
	 * which is not compatible with standard btusb.
	 * If matched, upload an alternative firmware that करोes conक्रमm to
	 * standard btusb. Once that firmware is uploaded, the subver changes
	 * to a dअगरferent value.
	 */
	अगर (!btrtl_dev->ic_info) अणु
		rtl_dev_info(hdev, "assuming no firmware upload needed");
		वापस 0;
	पूर्ण

	चयन (btrtl_dev->ic_info->lmp_subver) अणु
	हाल RTL_ROM_LMP_8723A:
		वापस btrtl_setup_rtl8723a(hdev, btrtl_dev);
	हाल RTL_ROM_LMP_8723B:
	हाल RTL_ROM_LMP_8821A:
	हाल RTL_ROM_LMP_8761A:
	हाल RTL_ROM_LMP_8822B:
	हाल RTL_ROM_LMP_8852A:
		वापस btrtl_setup_rtl8723b(hdev, btrtl_dev);
	शेष:
		rtl_dev_info(hdev, "assuming no firmware upload needed");
		वापस 0;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(btrtl_करोwnload_firmware);

पूर्णांक btrtl_setup_realtek(काष्ठा hci_dev *hdev)
अणु
	काष्ठा btrtl_device_info *btrtl_dev;
	पूर्णांक ret;

	btrtl_dev = btrtl_initialize(hdev, शून्य);
	अगर (IS_ERR(btrtl_dev))
		वापस PTR_ERR(btrtl_dev);

	ret = btrtl_करोwnload_firmware(hdev, btrtl_dev);

	/* Enable controller to करो both LE scan and BR/EDR inquiry
	 * simultaneously.
	 */
	set_bit(HCI_QUIRK_SIMULTANEOUS_DISCOVERY, &hdev->quirks);

	/* Enable central-peripheral role (able to create new connections with
	 * an existing connection in slave role).
	 */
	/* Enable WBS supported क्रम the specअगरic Realtek devices. */
	चयन (btrtl_dev->project_id) अणु
	हाल CHIP_ID_8822C:
	हाल CHIP_ID_8852A:
		set_bit(HCI_QUIRK_VALID_LE_STATES, &hdev->quirks);
		set_bit(HCI_QUIRK_WIDEBAND_SPEECH_SUPPORTED, &hdev->quirks);
		अवरोध;
	शेष:
		rtl_dev_dbg(hdev, "Central-peripheral role not enabled.");
		rtl_dev_dbg(hdev, "WBS supported not enabled.");
		अवरोध;
	पूर्ण

	btrtl_मुक्त(btrtl_dev);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(btrtl_setup_realtek);

पूर्णांक btrtl_shutकरोwn_realtek(काष्ठा hci_dev *hdev)
अणु
	काष्ठा sk_buff *skb;
	पूर्णांक ret;

	/* According to the venकरोr driver, BT must be reset on बंद to aव्योम
	 * firmware crash.
	 */
	skb = __hci_cmd_sync(hdev, HCI_OP_RESET, 0, शून्य, HCI_INIT_TIMEOUT);
	अगर (IS_ERR(skb)) अणु
		ret = PTR_ERR(skb);
		bt_dev_err(hdev, "HCI reset during shutdown failed");
		वापस ret;
	पूर्ण
	kमुक्त_skb(skb);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(btrtl_shutकरोwn_realtek);

अटल अचिन्हित पूर्णांक btrtl_convert_baudrate(u32 device_baudrate)
अणु
	चयन (device_baudrate) अणु
	हाल 0x0252a00a:
		वापस 230400;

	हाल 0x05f75004:
		वापस 921600;

	हाल 0x00005004:
		वापस 1000000;

	हाल 0x04928002:
	हाल 0x01128002:
		वापस 1500000;

	हाल 0x00005002:
		वापस 2000000;

	हाल 0x0000b001:
		वापस 2500000;

	हाल 0x04928001:
		वापस 3000000;

	हाल 0x052a6001:
		वापस 3500000;

	हाल 0x00005001:
		वापस 4000000;

	हाल 0x0252c014:
	शेष:
		वापस 115200;
	पूर्ण
पूर्ण

पूर्णांक btrtl_get_uart_settings(काष्ठा hci_dev *hdev,
			    काष्ठा btrtl_device_info *btrtl_dev,
			    अचिन्हित पूर्णांक *controller_baudrate,
			    u32 *device_baudrate, bool *flow_control)
अणु
	काष्ठा rtl_venकरोr_config *config;
	काष्ठा rtl_venकरोr_config_entry *entry;
	पूर्णांक i, total_data_len;
	bool found = false;

	total_data_len = btrtl_dev->cfg_len - माप(*config);
	अगर (total_data_len <= 0) अणु
		rtl_dev_warn(hdev, "no config loaded");
		वापस -EINVAL;
	पूर्ण

	config = (काष्ठा rtl_venकरोr_config *)btrtl_dev->cfg_data;
	अगर (le32_to_cpu(config->signature) != RTL_CONFIG_MAGIC) अणु
		rtl_dev_err(hdev, "invalid config magic");
		वापस -EINVAL;
	पूर्ण

	अगर (total_data_len < le16_to_cpu(config->total_len)) अणु
		rtl_dev_err(hdev, "config is too short");
		वापस -EINVAL;
	पूर्ण

	क्रम (i = 0; i < total_data_len; ) अणु
		entry = ((व्योम *)config->entry) + i;

		चयन (le16_to_cpu(entry->offset)) अणु
		हाल 0xc:
			अगर (entry->len < माप(*device_baudrate)) अणु
				rtl_dev_err(hdev, "invalid UART config entry");
				वापस -EINVAL;
			पूर्ण

			*device_baudrate = get_unaligned_le32(entry->data);
			*controller_baudrate = btrtl_convert_baudrate(
							*device_baudrate);

			अगर (entry->len >= 13)
				*flow_control = !!(entry->data[12] & BIT(2));
			अन्यथा
				*flow_control = false;

			found = true;
			अवरोध;

		शेष:
			rtl_dev_dbg(hdev, "skipping config entry 0x%x (len %u)",
				   le16_to_cpu(entry->offset), entry->len);
			अवरोध;
		पूर्ण

		i += माप(*entry) + entry->len;
	पूर्ण

	अगर (!found) अणु
		rtl_dev_err(hdev, "no UART config entry found");
		वापस -ENOENT;
	पूर्ण

	rtl_dev_dbg(hdev, "device baudrate = 0x%08x", *device_baudrate);
	rtl_dev_dbg(hdev, "controller baudrate = %u", *controller_baudrate);
	rtl_dev_dbg(hdev, "flow control %d", *flow_control);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(btrtl_get_uart_settings);

MODULE_AUTHOR("Daniel Drake <drake@endlessm.com>");
MODULE_DESCRIPTION("Bluetooth support for Realtek devices ver " VERSION);
MODULE_VERSION(VERSION);
MODULE_LICENSE("GPL");
MODULE_FIRMWARE("rtl_bt/rtl8723a_fw.bin");
MODULE_FIRMWARE("rtl_bt/rtl8723b_fw.bin");
MODULE_FIRMWARE("rtl_bt/rtl8723b_config.bin");
MODULE_FIRMWARE("rtl_bt/rtl8723bs_fw.bin");
MODULE_FIRMWARE("rtl_bt/rtl8723bs_config.bin");
MODULE_FIRMWARE("rtl_bt/rtl8723ds_fw.bin");
MODULE_FIRMWARE("rtl_bt/rtl8723ds_config.bin");
MODULE_FIRMWARE("rtl_bt/rtl8761a_fw.bin");
MODULE_FIRMWARE("rtl_bt/rtl8761a_config.bin");
MODULE_FIRMWARE("rtl_bt/rtl8821a_fw.bin");
MODULE_FIRMWARE("rtl_bt/rtl8821a_config.bin");
MODULE_FIRMWARE("rtl_bt/rtl8822b_fw.bin");
MODULE_FIRMWARE("rtl_bt/rtl8822b_config.bin");
MODULE_FIRMWARE("rtl_bt/rtl8852au_fw.bin");
MODULE_FIRMWARE("rtl_bt/rtl8852au_config.bin");
