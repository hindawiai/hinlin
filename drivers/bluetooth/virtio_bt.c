<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only

#समावेश <linux/module.h>
#समावेश <linux/virtपन.स>
#समावेश <linux/virtio_config.h>
#समावेश <linux/skbuff.h>

#समावेश <uapi/linux/virtio_ids.h>
#समावेश <uapi/linux/virtio_bt.h>

#समावेश <net/bluetooth/bluetooth.h>
#समावेश <net/bluetooth/hci_core.h>

#घोषणा VERSION "0.1"

क्रमागत अणु
	VIRTBT_VQ_TX,
	VIRTBT_VQ_RX,
	VIRTBT_NUM_VQS,
पूर्ण;

काष्ठा virtio_bluetooth अणु
	काष्ठा virtio_device *vdev;
	काष्ठा virtqueue *vqs[VIRTBT_NUM_VQS];
	काष्ठा work_काष्ठा rx;
	काष्ठा hci_dev *hdev;
पूर्ण;

अटल पूर्णांक virtbt_add_inbuf(काष्ठा virtio_bluetooth *vbt)
अणु
	काष्ठा virtqueue *vq = vbt->vqs[VIRTBT_VQ_RX];
	काष्ठा scatterlist sg[1];
	काष्ठा sk_buff *skb;
	पूर्णांक err;

	skb = alloc_skb(1000, GFP_KERNEL);
	sg_init_one(sg, skb->data, 1000);

	err = virtqueue_add_inbuf(vq, sg, 1, skb, GFP_KERNEL);
	अगर (err < 0) अणु
		kमुक्त_skb(skb);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक virtbt_खोलो(काष्ठा hci_dev *hdev)
अणु
	काष्ठा virtio_bluetooth *vbt = hci_get_drvdata(hdev);

	अगर (virtbt_add_inbuf(vbt) < 0)
		वापस -EIO;

	virtqueue_kick(vbt->vqs[VIRTBT_VQ_RX]);
	वापस 0;
पूर्ण

अटल पूर्णांक virtbt_बंद(काष्ठा hci_dev *hdev)
अणु
	काष्ठा virtio_bluetooth *vbt = hci_get_drvdata(hdev);
	पूर्णांक i;

	cancel_work_sync(&vbt->rx);

	क्रम (i = 0; i < ARRAY_SIZE(vbt->vqs); i++) अणु
		काष्ठा virtqueue *vq = vbt->vqs[i];
		काष्ठा sk_buff *skb;

		जबतक ((skb = virtqueue_detach_unused_buf(vq)))
			kमुक्त_skb(skb);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक virtbt_flush(काष्ठा hci_dev *hdev)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक virtbt_send_frame(काष्ठा hci_dev *hdev, काष्ठा sk_buff *skb)
अणु
	काष्ठा virtio_bluetooth *vbt = hci_get_drvdata(hdev);
	काष्ठा scatterlist sg[1];
	पूर्णांक err;

	स_नकल(skb_push(skb, 1), &hci_skb_pkt_type(skb), 1);

	sg_init_one(sg, skb->data, skb->len);
	err = virtqueue_add_outbuf(vbt->vqs[VIRTBT_VQ_TX], sg, 1, skb,
				   GFP_KERNEL);
	अगर (err) अणु
		kमुक्त_skb(skb);
		वापस err;
	पूर्ण

	virtqueue_kick(vbt->vqs[VIRTBT_VQ_TX]);
	वापस 0;
पूर्ण

अटल पूर्णांक virtbt_setup_zephyr(काष्ठा hci_dev *hdev)
अणु
	काष्ठा sk_buff *skb;

	/* Read Build Inक्रमmation */
	skb = __hci_cmd_sync(hdev, 0xfc08, 0, शून्य, HCI_INIT_TIMEOUT);
	अगर (IS_ERR(skb))
		वापस PTR_ERR(skb);

	bt_dev_info(hdev, "%s", (अक्षर *)(skb->data + 1));

	hci_set_fw_info(hdev, "%s", skb->data + 1);

	kमुक्त_skb(skb);
	वापस 0;
पूर्ण

अटल पूर्णांक virtbt_set_bdaddr_zephyr(काष्ठा hci_dev *hdev,
				    स्थिर bdaddr_t *bdaddr)
अणु
	काष्ठा sk_buff *skb;

	/* Write BD_ADDR */
	skb = __hci_cmd_sync(hdev, 0xfc06, 6, bdaddr, HCI_INIT_TIMEOUT);
	अगर (IS_ERR(skb))
		वापस PTR_ERR(skb);

	kमुक्त_skb(skb);
	वापस 0;
पूर्ण

अटल पूर्णांक virtbt_setup_पूर्णांकel(काष्ठा hci_dev *hdev)
अणु
	काष्ठा sk_buff *skb;

	/* Intel Read Version */
	skb = __hci_cmd_sync(hdev, 0xfc05, 0, शून्य, HCI_CMD_TIMEOUT);
	अगर (IS_ERR(skb))
		वापस PTR_ERR(skb);

	kमुक्त_skb(skb);
	वापस 0;
पूर्ण

अटल पूर्णांक virtbt_set_bdaddr_पूर्णांकel(काष्ठा hci_dev *hdev, स्थिर bdaddr_t *bdaddr)
अणु
	काष्ठा sk_buff *skb;

	/* Intel Write BD Address */
	skb = __hci_cmd_sync(hdev, 0xfc31, 6, bdaddr, HCI_INIT_TIMEOUT);
	अगर (IS_ERR(skb))
		वापस PTR_ERR(skb);

	kमुक्त_skb(skb);
	वापस 0;
पूर्ण

अटल पूर्णांक virtbt_setup_realtek(काष्ठा hci_dev *hdev)
अणु
	काष्ठा sk_buff *skb;

	/* Read ROM Version */
	skb = __hci_cmd_sync(hdev, 0xfc6d, 0, शून्य, HCI_INIT_TIMEOUT);
	अगर (IS_ERR(skb))
		वापस PTR_ERR(skb);

	bt_dev_info(hdev, "ROM version %u", *((__u8 *) (skb->data + 1)));

	kमुक्त_skb(skb);
	वापस 0;
पूर्ण

अटल पूर्णांक virtbt_shutकरोwn_generic(काष्ठा hci_dev *hdev)
अणु
	काष्ठा sk_buff *skb;

	/* Reset */
	skb = __hci_cmd_sync(hdev, HCI_OP_RESET, 0, शून्य, HCI_INIT_TIMEOUT);
	अगर (IS_ERR(skb))
		वापस PTR_ERR(skb);

	kमुक्त_skb(skb);
	वापस 0;
पूर्ण

अटल व्योम virtbt_rx_handle(काष्ठा virtio_bluetooth *vbt, काष्ठा sk_buff *skb)
अणु
	__u8 pkt_type;

	pkt_type = *((__u8 *) skb->data);
	skb_pull(skb, 1);

	चयन (pkt_type) अणु
	हाल HCI_EVENT_PKT:
	हाल HCI_ACLDATA_PKT:
	हाल HCI_SCODATA_PKT:
	हाल HCI_ISODATA_PKT:
		hci_skb_pkt_type(skb) = pkt_type;
		hci_recv_frame(vbt->hdev, skb);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम virtbt_rx_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा virtio_bluetooth *vbt = container_of(work,
						    काष्ठा virtio_bluetooth, rx);
	काष्ठा sk_buff *skb;
	अचिन्हित पूर्णांक len;

	skb = virtqueue_get_buf(vbt->vqs[VIRTBT_VQ_RX], &len);
	अगर (!skb)
		वापस;

	skb->len = len;
	virtbt_rx_handle(vbt, skb);

	अगर (virtbt_add_inbuf(vbt) < 0)
		वापस;

	virtqueue_kick(vbt->vqs[VIRTBT_VQ_RX]);
पूर्ण

अटल व्योम virtbt_tx_करोne(काष्ठा virtqueue *vq)
अणु
	काष्ठा sk_buff *skb;
	अचिन्हित पूर्णांक len;

	जबतक ((skb = virtqueue_get_buf(vq, &len)))
		kमुक्त_skb(skb);
पूर्ण

अटल व्योम virtbt_rx_करोne(काष्ठा virtqueue *vq)
अणु
	काष्ठा virtio_bluetooth *vbt = vq->vdev->priv;

	schedule_work(&vbt->rx);
पूर्ण

अटल पूर्णांक virtbt_probe(काष्ठा virtio_device *vdev)
अणु
	vq_callback_t *callbacks[VIRTBT_NUM_VQS] = अणु
		[VIRTBT_VQ_TX] = virtbt_tx_करोne,
		[VIRTBT_VQ_RX] = virtbt_rx_करोne,
	पूर्ण;
	स्थिर अक्षर *names[VIRTBT_NUM_VQS] = अणु
		[VIRTBT_VQ_TX] = "tx",
		[VIRTBT_VQ_RX] = "rx",
	पूर्ण;
	काष्ठा virtio_bluetooth *vbt;
	काष्ठा hci_dev *hdev;
	पूर्णांक err;
	__u8 type;

	अगर (!virtio_has_feature(vdev, VIRTIO_F_VERSION_1))
		वापस -ENODEV;

	type = virtio_cपढ़ो8(vdev, दुरत्व(काष्ठा virtio_bt_config, type));

	चयन (type) अणु
	हाल VIRTIO_BT_CONFIG_TYPE_PRIMARY:
	हाल VIRTIO_BT_CONFIG_TYPE_AMP:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	vbt = kzalloc(माप(*vbt), GFP_KERNEL);
	अगर (!vbt)
		वापस -ENOMEM;

	vdev->priv = vbt;
	vbt->vdev = vdev;

	INIT_WORK(&vbt->rx, virtbt_rx_work);

	err = virtio_find_vqs(vdev, VIRTBT_NUM_VQS, vbt->vqs, callbacks,
			      names, शून्य);
	अगर (err)
		वापस err;

	hdev = hci_alloc_dev();
	अगर (!hdev) अणु
		err = -ENOMEM;
		जाओ failed;
	पूर्ण

	vbt->hdev = hdev;

	hdev->bus = HCI_VIRTIO;
	hdev->dev_type = type;
	hci_set_drvdata(hdev, vbt);

	hdev->खोलो  = virtbt_खोलो;
	hdev->बंद = virtbt_बंद;
	hdev->flush = virtbt_flush;
	hdev->send  = virtbt_send_frame;

	अगर (virtio_has_feature(vdev, VIRTIO_BT_F_VND_HCI)) अणु
		__u16 venकरोr;

		virtio_cपढ़ो(vdev, काष्ठा virtio_bt_config, venकरोr, &venकरोr);

		चयन (venकरोr) अणु
		हाल VIRTIO_BT_CONFIG_VENDOR_ZEPHYR:
			hdev->manufacturer = 1521;
			hdev->setup = virtbt_setup_zephyr;
			hdev->shutकरोwn = virtbt_shutकरोwn_generic;
			hdev->set_bdaddr = virtbt_set_bdaddr_zephyr;
			अवरोध;

		हाल VIRTIO_BT_CONFIG_VENDOR_INTEL:
			hdev->manufacturer = 2;
			hdev->setup = virtbt_setup_पूर्णांकel;
			hdev->shutकरोwn = virtbt_shutकरोwn_generic;
			hdev->set_bdaddr = virtbt_set_bdaddr_पूर्णांकel;
			set_bit(HCI_QUIRK_STRICT_DUPLICATE_FILTER, &hdev->quirks);
			set_bit(HCI_QUIRK_SIMULTANEOUS_DISCOVERY, &hdev->quirks);
			set_bit(HCI_QUIRK_WIDEBAND_SPEECH_SUPPORTED, &hdev->quirks);
			अवरोध;

		हाल VIRTIO_BT_CONFIG_VENDOR_REALTEK:
			hdev->manufacturer = 93;
			hdev->setup = virtbt_setup_realtek;
			hdev->shutकरोwn = virtbt_shutकरोwn_generic;
			set_bit(HCI_QUIRK_SIMULTANEOUS_DISCOVERY, &hdev->quirks);
			set_bit(HCI_QUIRK_WIDEBAND_SPEECH_SUPPORTED, &hdev->quirks);
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (virtio_has_feature(vdev, VIRTIO_BT_F_MSFT_EXT)) अणु
		__u16 msft_opcode;

		virtio_cपढ़ो(vdev, काष्ठा virtio_bt_config,
			     msft_opcode, &msft_opcode);

		hci_set_msft_opcode(hdev, msft_opcode);
	पूर्ण

	अगर (virtio_has_feature(vdev, VIRTIO_BT_F_AOSP_EXT))
		hci_set_aosp_capable(hdev);

	अगर (hci_रेजिस्टर_dev(hdev) < 0) अणु
		hci_मुक्त_dev(hdev);
		err = -EBUSY;
		जाओ failed;
	पूर्ण

	वापस 0;

failed:
	vdev->config->del_vqs(vdev);
	वापस err;
पूर्ण

अटल व्योम virtbt_हटाओ(काष्ठा virtio_device *vdev)
अणु
	काष्ठा virtio_bluetooth *vbt = vdev->priv;
	काष्ठा hci_dev *hdev = vbt->hdev;

	hci_unरेजिस्टर_dev(hdev);
	vdev->config->reset(vdev);

	hci_मुक्त_dev(hdev);
	vbt->hdev = शून्य;

	vdev->config->del_vqs(vdev);
	kमुक्त(vbt);
पूर्ण

अटल काष्ठा virtio_device_id virtbt_table[] = अणु
	अणु VIRTIO_ID_BT, VIRTIO_DEV_ANY_ID पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(virtio, virtbt_table);

अटल स्थिर अचिन्हित पूर्णांक virtbt_features[] = अणु
	VIRTIO_BT_F_VND_HCI,
	VIRTIO_BT_F_MSFT_EXT,
	VIRTIO_BT_F_AOSP_EXT,
पूर्ण;

अटल काष्ठा virtio_driver virtbt_driver = अणु
	.driver.name         = KBUILD_MODNAME,
	.driver.owner        = THIS_MODULE,
	.feature_table       = virtbt_features,
	.feature_table_size  = ARRAY_SIZE(virtbt_features),
	.id_table            = virtbt_table,
	.probe               = virtbt_probe,
	.हटाओ              = virtbt_हटाओ,
पूर्ण;

module_virtio_driver(virtbt_driver);

MODULE_AUTHOR("Marcel Holtmann <marcel@holtmann.org>");
MODULE_DESCRIPTION("Generic Bluetooth VIRTIO driver ver " VERSION);
MODULE_VERSION(VERSION);
MODULE_LICENSE("GPL");
