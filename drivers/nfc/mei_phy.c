<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2013, Intel Corporation.
 *
 * MEI Library क्रम mei bus nfc device access
 */
#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/nfc.h>

#समावेश "mei_phy.h"

काष्ठा mei_nfc_hdr अणु
	u8 cmd;
	u8 status;
	u16 req_id;
	u32 reserved;
	u16 data_size;
पूर्ण __packed;

काष्ठा mei_nfc_cmd अणु
	काष्ठा mei_nfc_hdr hdr;
	u8 sub_command;
	u8 data[];
पूर्ण __packed;

काष्ठा mei_nfc_reply अणु
	काष्ठा mei_nfc_hdr hdr;
	u8 sub_command;
	u8 reply_status;
	u8 data[];
पूर्ण __packed;

काष्ठा mei_nfc_अगर_version अणु
	u8 radio_version_sw[3];
	u8 reserved[3];
	u8 radio_version_hw[3];
	u8 i2c_addr;
	u8 fw_ivn;
	u8 venकरोr_id;
	u8 radio_type;
पूर्ण __packed;

काष्ठा mei_nfc_connect अणु
	u8 fw_ivn;
	u8 venकरोr_id;
पूर्ण __packed;

काष्ठा mei_nfc_connect_resp अणु
	u8 fw_ivn;
	u8 venकरोr_id;
	u16 me_major;
	u16 me_minor;
	u16 me_hotfix;
	u16 me_build;
पूर्ण __packed;


#घोषणा MEI_NFC_CMD_MAINTEन_अंकCE 0x00
#घोषणा MEI_NFC_CMD_HCI_SEND 0x01
#घोषणा MEI_NFC_CMD_HCI_RECV 0x02

#घोषणा MEI_NFC_SUBCMD_CONNECT    0x00
#घोषणा MEI_NFC_SUBCMD_IF_VERSION 0x01

#घोषणा MEI_NFC_MAX_READ (MEI_NFC_HEADER_SIZE + MEI_NFC_MAX_HCI_PAYLOAD)

#घोषणा MEI_DUMP_SKB_IN(info, skb)				\
करो अणु								\
	pr_debug("%s:\n", info);				\
	prपूर्णांक_hex_dump_debug("mei in : ", DUMP_PREFIX_OFFSET,	\
			16, 1, (skb)->data, (skb)->len, false);	\
पूर्ण जबतक (0)

#घोषणा MEI_DUMP_SKB_OUT(info, skb)				\
करो अणु								\
	pr_debug("%s:\n", info);				\
	prपूर्णांक_hex_dump_debug("mei out: ", DUMP_PREFIX_OFFSET,	\
			16, 1, (skb)->data, (skb)->len, false);	\
पूर्ण जबतक (0)

#घोषणा MEI_DUMP_NFC_HDR(info, _hdr)                                \
करो अणु                                                                \
	pr_debug("%s:\n", info);                                    \
	pr_debug("cmd=%02d status=%d req_id=%d rsvd=%d size=%d\n",  \
		 (_hdr)->cmd, (_hdr)->status, (_hdr)->req_id,       \
		 (_hdr)->reserved, (_hdr)->data_size);              \
पूर्ण जबतक (0)

अटल पूर्णांक mei_nfc_अगर_version(काष्ठा nfc_mei_phy *phy)
अणु

	काष्ठा mei_nfc_cmd cmd;
	काष्ठा mei_nfc_reply *reply = शून्य;
	काष्ठा mei_nfc_अगर_version *version;
	माप_प्रकार अगर_version_length;
	पूर्णांक bytes_recv, r;

	pr_info("%s\n", __func__);

	स_रखो(&cmd, 0, माप(काष्ठा mei_nfc_cmd));
	cmd.hdr.cmd = MEI_NFC_CMD_MAINTEन_अंकCE;
	cmd.hdr.data_size = 1;
	cmd.sub_command = MEI_NFC_SUBCMD_IF_VERSION;

	MEI_DUMP_NFC_HDR("version", &cmd.hdr);
	r = mei_cldev_send(phy->cldev, (u8 *)&cmd, माप(काष्ठा mei_nfc_cmd));
	अगर (r < 0) अणु
		pr_err("Could not send IF version cmd\n");
		वापस r;
	पूर्ण

	/* to be sure on the stack we alloc memory */
	अगर_version_length = माप(काष्ठा mei_nfc_reply) +
		माप(काष्ठा mei_nfc_अगर_version);

	reply = kzalloc(अगर_version_length, GFP_KERNEL);
	अगर (!reply)
		वापस -ENOMEM;

	bytes_recv = mei_cldev_recv(phy->cldev, (u8 *)reply, अगर_version_length);
	अगर (bytes_recv < 0 || bytes_recv < अगर_version_length) अणु
		pr_err("Could not read IF version\n");
		r = -EIO;
		जाओ err;
	पूर्ण

	version = (काष्ठा mei_nfc_अगर_version *)reply->data;

	phy->fw_ivn = version->fw_ivn;
	phy->venकरोr_id = version->venकरोr_id;
	phy->radio_type = version->radio_type;

err:
	kमुक्त(reply);
	वापस r;
पूर्ण

अटल पूर्णांक mei_nfc_connect(काष्ठा nfc_mei_phy *phy)
अणु
	काष्ठा mei_nfc_cmd *cmd, *reply;
	काष्ठा mei_nfc_connect *connect;
	काष्ठा mei_nfc_connect_resp *connect_resp;
	माप_प्रकार connect_length, connect_resp_length;
	पूर्णांक bytes_recv, r;

	pr_info("%s\n", __func__);

	connect_length = माप(काष्ठा mei_nfc_cmd) +
			माप(काष्ठा mei_nfc_connect);

	connect_resp_length = माप(काष्ठा mei_nfc_cmd) +
			माप(काष्ठा mei_nfc_connect_resp);

	cmd = kzalloc(connect_length, GFP_KERNEL);
	अगर (!cmd)
		वापस -ENOMEM;
	connect = (काष्ठा mei_nfc_connect *)cmd->data;

	reply = kzalloc(connect_resp_length, GFP_KERNEL);
	अगर (!reply) अणु
		kमुक्त(cmd);
		वापस -ENOMEM;
	पूर्ण

	connect_resp = (काष्ठा mei_nfc_connect_resp *)reply->data;

	cmd->hdr.cmd = MEI_NFC_CMD_MAINTEन_अंकCE;
	cmd->hdr.data_size = 3;
	cmd->sub_command = MEI_NFC_SUBCMD_CONNECT;
	connect->fw_ivn = phy->fw_ivn;
	connect->venकरोr_id = phy->venकरोr_id;

	MEI_DUMP_NFC_HDR("connect request", &cmd->hdr);
	r = mei_cldev_send(phy->cldev, (u8 *)cmd, connect_length);
	अगर (r < 0) अणु
		pr_err("Could not send connect cmd %d\n", r);
		जाओ err;
	पूर्ण

	bytes_recv = mei_cldev_recv(phy->cldev, (u8 *)reply,
				    connect_resp_length);
	अगर (bytes_recv < 0) अणु
		r = bytes_recv;
		pr_err("Could not read connect response %d\n", r);
		जाओ err;
	पूर्ण

	MEI_DUMP_NFC_HDR("connect reply", &reply->hdr);

	pr_info("IVN 0x%x Vendor ID 0x%x\n",
		 connect_resp->fw_ivn, connect_resp->venकरोr_id);

	pr_info("ME FW %d.%d.%d.%d\n",
		connect_resp->me_major, connect_resp->me_minor,
		connect_resp->me_hotfix, connect_resp->me_build);

	r = 0;

err:
	kमुक्त(reply);
	kमुक्त(cmd);

	वापस r;
पूर्ण

अटल पूर्णांक mei_nfc_send(काष्ठा nfc_mei_phy *phy, u8 *buf, माप_प्रकार length)
अणु
	काष्ठा mei_nfc_hdr *hdr;
	u8 *mei_buf;
	पूर्णांक err;

	err = -ENOMEM;
	mei_buf = kzalloc(length + MEI_NFC_HEADER_SIZE, GFP_KERNEL);
	अगर (!mei_buf)
		जाओ out;

	hdr = (काष्ठा mei_nfc_hdr *)mei_buf;
	hdr->cmd = MEI_NFC_CMD_HCI_SEND;
	hdr->status = 0;
	hdr->req_id = phy->req_id;
	hdr->reserved = 0;
	hdr->data_size = length;

	MEI_DUMP_NFC_HDR("send", hdr);

	स_नकल(mei_buf + MEI_NFC_HEADER_SIZE, buf, length);
	err = mei_cldev_send(phy->cldev, mei_buf, length + MEI_NFC_HEADER_SIZE);
	अगर (err < 0)
		जाओ out;

	अगर (!रुको_event_पूर्णांकerruptible_समयout(phy->send_wq,
				phy->recv_req_id == phy->req_id, HZ)) अणु
		pr_err("NFC MEI command timeout\n");
		err = -ETIME;
	पूर्ण अन्यथा अणु
		phy->req_id++;
	पूर्ण
out:
	kमुक्त(mei_buf);
	वापस err;
पूर्ण

/*
 * Writing a frame must not वापस the number of written bytes.
 * It must वापस either zero क्रम success, or <0 क्रम error.
 * In addition, it must not alter the skb
 */
अटल पूर्णांक nfc_mei_phy_ग_लिखो(व्योम *phy_id, काष्ठा sk_buff *skb)
अणु
	काष्ठा nfc_mei_phy *phy = phy_id;
	पूर्णांक r;

	MEI_DUMP_SKB_OUT("mei frame sent", skb);

	r = mei_nfc_send(phy, skb->data, skb->len);
	अगर (r > 0)
		r = 0;

	वापस r;
पूर्ण

अटल पूर्णांक mei_nfc_recv(काष्ठा nfc_mei_phy *phy, u8 *buf, माप_प्रकार length)
अणु
	काष्ठा mei_nfc_hdr *hdr;
	पूर्णांक received_length;

	received_length = mei_cldev_recv(phy->cldev, buf, length);
	अगर (received_length < 0)
		वापस received_length;

	hdr = (काष्ठा mei_nfc_hdr *) buf;

	MEI_DUMP_NFC_HDR("receive", hdr);
	अगर (hdr->cmd == MEI_NFC_CMD_HCI_SEND) अणु
		phy->recv_req_id = hdr->req_id;
		wake_up(&phy->send_wq);

		वापस 0;
	पूर्ण

	वापस received_length;
पूर्ण


अटल व्योम nfc_mei_rx_cb(काष्ठा mei_cl_device *cldev)
अणु
	काष्ठा nfc_mei_phy *phy = mei_cldev_get_drvdata(cldev);
	काष्ठा sk_buff *skb;
	पूर्णांक reply_size;

	अगर (!phy)
		वापस;

	अगर (phy->hard_fault != 0)
		वापस;

	skb = alloc_skb(MEI_NFC_MAX_READ, GFP_KERNEL);
	अगर (!skb)
		वापस;

	reply_size = mei_nfc_recv(phy, skb->data, MEI_NFC_MAX_READ);
	अगर (reply_size < MEI_NFC_HEADER_SIZE) अणु
		kमुक्त_skb(skb);
		वापस;
	पूर्ण

	skb_put(skb, reply_size);
	skb_pull(skb, MEI_NFC_HEADER_SIZE);

	MEI_DUMP_SKB_IN("mei frame read", skb);

	nfc_hci_recv_frame(phy->hdev, skb);
पूर्ण

अटल पूर्णांक nfc_mei_phy_enable(व्योम *phy_id)
अणु
	पूर्णांक r;
	काष्ठा nfc_mei_phy *phy = phy_id;

	pr_info("%s\n", __func__);

	अगर (phy->घातered == 1)
		वापस 0;

	r = mei_cldev_enable(phy->cldev);
	अगर (r < 0) अणु
		pr_err("Could not enable device %d\n", r);
		वापस r;
	पूर्ण

	r = mei_nfc_अगर_version(phy);
	अगर (r < 0) अणु
		pr_err("Could not enable device %d\n", r);
		जाओ err;
	पूर्ण

	r = mei_nfc_connect(phy);
	अगर (r < 0) अणु
		pr_err("Could not connect to device %d\n", r);
		जाओ err;
	पूर्ण

	r = mei_cldev_रेजिस्टर_rx_cb(phy->cldev, nfc_mei_rx_cb);
	अगर (r) अणु
		pr_err("Event cb registration failed %d\n", r);
		जाओ err;
	पूर्ण

	phy->घातered = 1;

	वापस 0;

err:
	phy->घातered = 0;
	mei_cldev_disable(phy->cldev);
	वापस r;
पूर्ण

अटल व्योम nfc_mei_phy_disable(व्योम *phy_id)
अणु
	काष्ठा nfc_mei_phy *phy = phy_id;

	pr_info("%s\n", __func__);

	mei_cldev_disable(phy->cldev);

	phy->घातered = 0;
पूर्ण

काष्ठा nfc_phy_ops mei_phy_ops = अणु
	.ग_लिखो = nfc_mei_phy_ग_लिखो,
	.enable = nfc_mei_phy_enable,
	.disable = nfc_mei_phy_disable,
पूर्ण;
EXPORT_SYMBOL_GPL(mei_phy_ops);

काष्ठा nfc_mei_phy *nfc_mei_phy_alloc(काष्ठा mei_cl_device *cldev)
अणु
	काष्ठा nfc_mei_phy *phy;

	phy = kzalloc(माप(काष्ठा nfc_mei_phy), GFP_KERNEL);
	अगर (!phy)
		वापस शून्य;

	phy->cldev = cldev;
	init_रुकोqueue_head(&phy->send_wq);
	mei_cldev_set_drvdata(cldev, phy);

	वापस phy;
पूर्ण
EXPORT_SYMBOL_GPL(nfc_mei_phy_alloc);

व्योम nfc_mei_phy_मुक्त(काष्ठा nfc_mei_phy *phy)
अणु
	mei_cldev_disable(phy->cldev);
	kमुक्त(phy);
पूर्ण
EXPORT_SYMBOL_GPL(nfc_mei_phy_मुक्त);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("mei bus NFC device interface");
