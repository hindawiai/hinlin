<शैली गुरु>
/**
 * Copyright (c) 2017 Redpine Signals Inc.
 *
 * Permission to use, copy, modअगरy, and/or distribute this software क्रम any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, सूचीECT, INसूचीECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <net/bluetooth/bluetooth.h>
#समावेश <net/bluetooth/hci_core.h>
#समावेश <यंत्र/unaligned.h>
#समावेश <net/rsi_91x.h>
#समावेश <net/genetlink.h>

#घोषणा RSI_DMA_ALIGN	8
#घोषणा RSI_FRAME_DESC_SIZE	16
#घोषणा RSI_HEADROOM_FOR_BT_HAL	(RSI_FRAME_DESC_SIZE + RSI_DMA_ALIGN)

काष्ठा rsi_hci_adapter अणु
	व्योम *priv;
	काष्ठा rsi_proto_ops *proto_ops;
	काष्ठा hci_dev *hdev;
पूर्ण;

अटल पूर्णांक rsi_hci_खोलो(काष्ठा hci_dev *hdev)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक rsi_hci_बंद(काष्ठा hci_dev *hdev)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक rsi_hci_flush(काष्ठा hci_dev *hdev)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक rsi_hci_send_pkt(काष्ठा hci_dev *hdev, काष्ठा sk_buff *skb)
अणु
	काष्ठा rsi_hci_adapter *h_adapter = hci_get_drvdata(hdev);
	काष्ठा sk_buff *new_skb = शून्य;

	चयन (hci_skb_pkt_type(skb)) अणु
	हाल HCI_COMMAND_PKT:
		hdev->stat.cmd_tx++;
		अवरोध;
	हाल HCI_ACLDATA_PKT:
		hdev->stat.acl_tx++;
		अवरोध;
	हाल HCI_SCODATA_PKT:
		hdev->stat.sco_tx++;
		अवरोध;
	पूर्ण

	अगर (skb_headroom(skb) < RSI_HEADROOM_FOR_BT_HAL) अणु
		/* Insufficient skb headroom - allocate a new skb */
		new_skb = skb_पुनः_स्मृति_headroom(skb, RSI_HEADROOM_FOR_BT_HAL);
		अगर (unlikely(!new_skb))
			वापस -ENOMEM;
		bt_cb(new_skb)->pkt_type = hci_skb_pkt_type(skb);
		kमुक्त_skb(skb);
		skb = new_skb;
		अगर (!IS_ALIGNED((अचिन्हित दीर्घ)skb->data, RSI_DMA_ALIGN)) अणु
			u8 *skb_data = skb->data;
			पूर्णांक skb_len = skb->len;

			skb_push(skb, RSI_DMA_ALIGN);
			skb_pull(skb, PTR_ALIGN(skb->data,
						RSI_DMA_ALIGN) - skb->data);
			स_हटाओ(skb->data, skb_data, skb_len);
			skb_trim(skb, skb_len);
		पूर्ण
	पूर्ण

	वापस h_adapter->proto_ops->coex_send_pkt(h_adapter->priv, skb,
						   RSI_BT_Q);
पूर्ण

अटल पूर्णांक rsi_hci_recv_pkt(व्योम *priv, स्थिर u8 *pkt)
अणु
	काष्ठा rsi_hci_adapter *h_adapter = priv;
	काष्ठा hci_dev *hdev = h_adapter->hdev;
	काष्ठा sk_buff *skb;
	पूर्णांक pkt_len = get_unaligned_le16(pkt) & 0x0fff;

	skb = dev_alloc_skb(pkt_len);
	अगर (!skb)
		वापस -ENOMEM;

	स_नकल(skb->data, pkt + RSI_FRAME_DESC_SIZE, pkt_len);
	skb_put(skb, pkt_len);
	h_adapter->hdev->stat.byte_rx += skb->len;

	hci_skb_pkt_type(skb) = pkt[14];

	वापस hci_recv_frame(hdev, skb);
पूर्ण

अटल पूर्णांक rsi_hci_attach(व्योम *priv, काष्ठा rsi_proto_ops *ops)
अणु
	काष्ठा rsi_hci_adapter *h_adapter = शून्य;
	काष्ठा hci_dev *hdev;
	पूर्णांक err = 0;

	h_adapter = kzalloc(माप(*h_adapter), GFP_KERNEL);
	अगर (!h_adapter)
		वापस -ENOMEM;

	h_adapter->priv = priv;
	ops->set_bt_context(priv, h_adapter);
	h_adapter->proto_ops = ops;

	hdev = hci_alloc_dev();
	अगर (!hdev) अणु
		BT_ERR("Failed to alloc HCI device");
		जाओ err;
	पूर्ण

	h_adapter->hdev = hdev;

	अगर (ops->get_host_पूर्णांकf(priv) == RSI_HOST_INTF_SDIO)
		hdev->bus = HCI_SDIO;
	अन्यथा
		hdev->bus = HCI_USB;

	hci_set_drvdata(hdev, h_adapter);
	hdev->dev_type = HCI_PRIMARY;
	hdev->खोलो = rsi_hci_खोलो;
	hdev->बंद = rsi_hci_बंद;
	hdev->flush = rsi_hci_flush;
	hdev->send = rsi_hci_send_pkt;

	err = hci_रेजिस्टर_dev(hdev);
	अगर (err < 0) अणु
		BT_ERR("HCI registration failed with errcode %d", err);
		hci_मुक्त_dev(hdev);
		जाओ err;
	पूर्ण

	वापस 0;
err:
	h_adapter->hdev = शून्य;
	kमुक्त(h_adapter);
	वापस -EINVAL;
पूर्ण

अटल व्योम rsi_hci_detach(व्योम *priv)
अणु
	काष्ठा rsi_hci_adapter *h_adapter = priv;
	काष्ठा hci_dev *hdev;

	अगर (!h_adapter)
		वापस;

	hdev = h_adapter->hdev;
	अगर (hdev) अणु
		hci_unरेजिस्टर_dev(hdev);
		hci_मुक्त_dev(hdev);
		h_adapter->hdev = शून्य;
	पूर्ण

	kमुक्त(h_adapter);
पूर्ण

स्थिर काष्ठा rsi_mod_ops rsi_bt_ops = अणु
	.attach	= rsi_hci_attach,
	.detach	= rsi_hci_detach,
	.recv_pkt = rsi_hci_recv_pkt,
पूर्ण;
EXPORT_SYMBOL(rsi_bt_ops);

अटल पूर्णांक rsi_91x_bt_module_init(व्योम)
अणु
	वापस 0;
पूर्ण

अटल व्योम rsi_91x_bt_module_निकास(व्योम)
अणु
	वापस;
पूर्ण

module_init(rsi_91x_bt_module_init);
module_निकास(rsi_91x_bt_module_निकास);
MODULE_AUTHOR("Redpine Signals Inc");
MODULE_DESCRIPTION("RSI BT driver");
MODULE_LICENSE("Dual BSD/GPL");
