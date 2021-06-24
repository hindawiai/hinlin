<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *
 *  Bluetooth HCI UART driver क्रम Intel/AG6xx devices
 *
 *  Copyright (C) 2016  Intel Corporation
 */

#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/skbuff.h>
#समावेश <linux/firmware.h>
#समावेश <linux/module.h>
#समावेश <linux/tty.h>

#समावेश <net/bluetooth/bluetooth.h>
#समावेश <net/bluetooth/hci_core.h>

#समावेश "hci_uart.h"
#समावेश "btintel.h"

काष्ठा ag6xx_data अणु
	काष्ठा sk_buff *rx_skb;
	काष्ठा sk_buff_head txq;
पूर्ण;

काष्ठा pbn_entry अणु
	__le32 addr;
	__le32 plen;
	__u8 data[];
पूर्ण __packed;

अटल पूर्णांक ag6xx_खोलो(काष्ठा hci_uart *hu)
अणु
	काष्ठा ag6xx_data *ag6xx;

	BT_DBG("hu %p", hu);

	ag6xx = kzalloc(माप(*ag6xx), GFP_KERNEL);
	अगर (!ag6xx)
		वापस -ENOMEM;

	skb_queue_head_init(&ag6xx->txq);

	hu->priv = ag6xx;
	वापस 0;
पूर्ण

अटल पूर्णांक ag6xx_बंद(काष्ठा hci_uart *hu)
अणु
	काष्ठा ag6xx_data *ag6xx = hu->priv;

	BT_DBG("hu %p", hu);

	skb_queue_purge(&ag6xx->txq);
	kमुक्त_skb(ag6xx->rx_skb);
	kमुक्त(ag6xx);

	hu->priv = शून्य;
	वापस 0;
पूर्ण

अटल पूर्णांक ag6xx_flush(काष्ठा hci_uart *hu)
अणु
	काष्ठा ag6xx_data *ag6xx = hu->priv;

	BT_DBG("hu %p", hu);

	skb_queue_purge(&ag6xx->txq);
	वापस 0;
पूर्ण

अटल काष्ठा sk_buff *ag6xx_dequeue(काष्ठा hci_uart *hu)
अणु
	काष्ठा ag6xx_data *ag6xx = hu->priv;
	काष्ठा sk_buff *skb;

	skb = skb_dequeue(&ag6xx->txq);
	अगर (!skb)
		वापस skb;

	/* Prepend skb with frame type */
	स_नकल(skb_push(skb, 1), &bt_cb(skb)->pkt_type, 1);
	वापस skb;
पूर्ण

अटल पूर्णांक ag6xx_enqueue(काष्ठा hci_uart *hu, काष्ठा sk_buff *skb)
अणु
	काष्ठा ag6xx_data *ag6xx = hu->priv;

	skb_queue_tail(&ag6xx->txq, skb);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा h4_recv_pkt ag6xx_recv_pkts[] = अणु
	अणु H4_RECV_ACL,    .recv = hci_recv_frame   पूर्ण,
	अणु H4_RECV_SCO,    .recv = hci_recv_frame   पूर्ण,
	अणु H4_RECV_EVENT,  .recv = hci_recv_frame   पूर्ण,
पूर्ण;

अटल पूर्णांक ag6xx_recv(काष्ठा hci_uart *hu, स्थिर व्योम *data, पूर्णांक count)
अणु
	काष्ठा ag6xx_data *ag6xx = hu->priv;

	अगर (!test_bit(HCI_UART_REGISTERED, &hu->flags))
		वापस -EUNATCH;

	ag6xx->rx_skb = h4_recv_buf(hu->hdev, ag6xx->rx_skb, data, count,
				    ag6xx_recv_pkts,
				    ARRAY_SIZE(ag6xx_recv_pkts));
	अगर (IS_ERR(ag6xx->rx_skb)) अणु
		पूर्णांक err = PTR_ERR(ag6xx->rx_skb);
		bt_dev_err(hu->hdev, "Frame reassembly failed (%d)", err);
		ag6xx->rx_skb = शून्य;
		वापस err;
	पूर्ण

	वापस count;
पूर्ण

अटल पूर्णांक पूर्णांकel_mem_ग_लिखो(काष्ठा hci_dev *hdev, u32 addr, u32 plen,
			   स्थिर व्योम *data)
अणु
	/* Can ग_लिखो a maximum of 247 bytes per HCI command.
	 * HCI cmd Header (3), Intel mem ग_लिखो header (6), data (247).
	 */
	जबतक (plen > 0) अणु
		काष्ठा sk_buff *skb;
		u8 cmd_param[253], fragment_len = (plen > 247) ? 247 : plen;
		__le32 leaddr = cpu_to_le32(addr);

		स_नकल(cmd_param, &leaddr, 4);
		cmd_param[4] = 0;
		cmd_param[5] = fragment_len;
		स_नकल(cmd_param + 6, data, fragment_len);

		skb = __hci_cmd_sync(hdev, 0xfc8e, fragment_len + 6, cmd_param,
				     HCI_INIT_TIMEOUT);
		अगर (IS_ERR(skb))
			वापस PTR_ERR(skb);
		kमुक्त_skb(skb);

		plen -= fragment_len;
		data += fragment_len;
		addr += fragment_len;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ag6xx_setup(काष्ठा hci_uart *hu)
अणु
	काष्ठा hci_dev *hdev = hu->hdev;
	काष्ठा sk_buff *skb;
	काष्ठा पूर्णांकel_version ver;
	स्थिर काष्ठा firmware *fw;
	स्थिर u8 *fw_ptr;
	अक्षर fwname[64];
	bool patched = false;
	पूर्णांक err;

	hu->hdev->set_diag = btपूर्णांकel_set_diag;
	hu->hdev->set_bdaddr = btपूर्णांकel_set_bdaddr;

	err = btपूर्णांकel_enter_mfg(hdev);
	अगर (err)
		वापस err;

	err = btपूर्णांकel_पढ़ो_version(hdev, &ver);
	अगर (err)
		वापस err;

	btपूर्णांकel_version_info(hdev, &ver);

	/* The hardware platक्रमm number has a fixed value of 0x37 and
	 * क्रम now only accept this single value.
	 */
	अगर (ver.hw_platक्रमm != 0x37) अणु
		bt_dev_err(hdev, "Unsupported Intel hardware platform: 0x%X",
			   ver.hw_platक्रमm);
		वापस -EINVAL;
	पूर्ण

	/* Only the hardware variant iBT 2.1 (AG6XX) is supported by this
	 * firmware setup method.
	 */
	अगर (ver.hw_variant != 0x0a) अणु
		bt_dev_err(hdev, "Unsupported Intel hardware variant: 0x%x",
			   ver.hw_variant);
		वापस -EINVAL;
	पूर्ण

	snम_लिखो(fwname, माप(fwname), "intel/ibt-hw-%x.%x.bddata",
		 ver.hw_platक्रमm, ver.hw_variant);

	err = request_firmware(&fw, fwname, &hdev->dev);
	अगर (err < 0) अणु
		bt_dev_err(hdev, "Failed to open Intel bddata file: %s (%d)",
			   fwname, err);
		जाओ patch;
	पूर्ण
	fw_ptr = fw->data;

	bt_dev_info(hdev, "Applying bddata (%s)", fwname);

	skb = __hci_cmd_sync_ev(hdev, 0xfc2f, fw->size, fw->data,
				HCI_EV_CMD_STATUS, HCI_CMD_TIMEOUT);
	अगर (IS_ERR(skb)) अणु
		bt_dev_err(hdev, "Applying bddata failed (%ld)", PTR_ERR(skb));
		release_firmware(fw);
		वापस PTR_ERR(skb);
	पूर्ण
	kमुक्त_skb(skb);

	release_firmware(fw);

patch:
	/* If there is no applied patch, fw_patch_num is always 0x00. In other
	 * हालs, current firmware is alपढ़ोy patched. No need to patch it.
	 */
	अगर (ver.fw_patch_num) अणु
		bt_dev_info(hdev, "Device is already patched. patch num: %02x",
			    ver.fw_patch_num);
		patched = true;
		जाओ complete;
	पूर्ण

	snम_लिखो(fwname, माप(fwname),
		 "intel/ibt-hw-%x.%x.%x-fw-%x.%x.%x.%x.%x.pbn",
		 ver.hw_platक्रमm, ver.hw_variant, ver.hw_revision,
		 ver.fw_variant,  ver.fw_revision, ver.fw_build_num,
		 ver.fw_build_ww, ver.fw_build_yy);

	err = request_firmware(&fw, fwname, &hdev->dev);
	अगर (err < 0) अणु
		bt_dev_err(hdev, "Failed to open Intel patch file: %s(%d)",
			   fwname, err);
		जाओ complete;
	पूर्ण
	fw_ptr = fw->data;

	bt_dev_info(hdev, "Patching firmware file (%s)", fwname);

	/* PBN patch file contains a list of binary patches to be applied on top
	 * of the embedded firmware. Each patch entry header contains the target
	 * address and patch size.
	 *
	 * Patch entry:
	 * | addr(le) | patch_len(le) | patch_data |
	 * | 4 Bytes  |    4 Bytes    |   n Bytes  |
	 *
	 * PBN file is terminated by a patch entry whose address is 0xffffffff.
	 */
	जबतक (fw->size > fw_ptr - fw->data) अणु
		काष्ठा pbn_entry *pbn = (व्योम *)fw_ptr;
		u32 addr, plen;

		अगर (pbn->addr == 0xffffffff) अणु
			bt_dev_info(hdev, "Patching complete");
			patched = true;
			अवरोध;
		पूर्ण

		addr = le32_to_cpu(pbn->addr);
		plen = le32_to_cpu(pbn->plen);

		अगर (fw->data + fw->size <= pbn->data + plen) अणु
			bt_dev_info(hdev, "Invalid patch len (%d)", plen);
			अवरोध;
		पूर्ण

		bt_dev_info(hdev, "Patching %td/%zu", (fw_ptr - fw->data),
			    fw->size);

		err = पूर्णांकel_mem_ग_लिखो(hdev, addr, plen, pbn->data);
		अगर (err) अणु
			bt_dev_err(hdev, "Patching failed");
			अवरोध;
		पूर्ण

		fw_ptr = pbn->data + plen;
	पूर्ण

	release_firmware(fw);

complete:
	/* Exit manufacturing mode and reset */
	err = btपूर्णांकel_निकास_mfg(hdev, true, patched);
	अगर (err)
		वापस err;

	/* Set the event mask क्रम Intel specअगरic venकरोr events. This enables
	 * a few extra events that are useful during general operation.
	 */
	btपूर्णांकel_set_event_mask_mfg(hdev, false);

	btपूर्णांकel_check_bdaddr(hdev);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा hci_uart_proto ag6xx_proto = अणु
	.id		= HCI_UART_AG6XX,
	.name		= "AG6XX",
	.manufacturer	= 2,
	.खोलो		= ag6xx_खोलो,
	.बंद		= ag6xx_बंद,
	.flush		= ag6xx_flush,
	.setup		= ag6xx_setup,
	.recv		= ag6xx_recv,
	.enqueue	= ag6xx_enqueue,
	.dequeue	= ag6xx_dequeue,
पूर्ण;

पूर्णांक __init ag6xx_init(व्योम)
अणु
	वापस hci_uart_रेजिस्टर_proto(&ag6xx_proto);
पूर्ण

पूर्णांक __निकास ag6xx_deinit(व्योम)
अणु
	वापस hci_uart_unरेजिस्टर_proto(&ag6xx_proto);
पूर्ण
