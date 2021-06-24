<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Proprietary commands extension क्रम STMicroelectronics NFC Chip
 *
 * Copyright (C) 2014-2015  STMicroelectronics SAS. All rights reserved.
 */

#समावेश <net/genetlink.h>
#समावेश <linux/module.h>
#समावेश <linux/nfc.h>
#समावेश <net/nfc/hci.h>
#समावेश <net/nfc/llc.h>

#समावेश "st21nfca.h"

#घोषणा ST21NFCA_HCI_DM_GETDATA			0x10
#घोषणा ST21NFCA_HCI_DM_PUTDATA			0x11
#घोषणा ST21NFCA_HCI_DM_LOAD			0x12
#घोषणा ST21NFCA_HCI_DM_GETINFO			0x13
#घोषणा ST21NFCA_HCI_DM_UPDATE_AID		0x20
#घोषणा ST21NFCA_HCI_DM_RESET			0x3e

#घोषणा ST21NFCA_HCI_DM_FIELD_GENERATOR		0x32

#घोषणा ST21NFCA_FACTORY_MODE_ON		1
#घोषणा ST21NFCA_FACTORY_MODE_OFF		0

#घोषणा ST21NFCA_EVT_POST_DATA			0x02

काष्ठा get_param_data अणु
	u8 gate;
	u8 data;
पूर्ण __packed;

अटल पूर्णांक st21nfca_factory_mode(काष्ठा nfc_dev *dev, व्योम *data,
			       माप_प्रकार data_len)
अणु
	काष्ठा nfc_hci_dev *hdev = nfc_get_drvdata(dev);

	अगर (data_len != 1)
		वापस -EINVAL;

	pr_debug("factory mode: %x\n", ((u8 *)data)[0]);

	चयन (((u8 *)data)[0]) अणु
	हाल ST21NFCA_FACTORY_MODE_ON:
		test_and_set_bit(ST21NFCA_FACTORY_MODE, &hdev->quirks);
	अवरोध;
	हाल ST21NFCA_FACTORY_MODE_OFF:
		clear_bit(ST21NFCA_FACTORY_MODE, &hdev->quirks);
	अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक st21nfca_hci_clear_all_pipes(काष्ठा nfc_dev *dev, व्योम *data,
				      माप_प्रकार data_len)
अणु
	काष्ठा nfc_hci_dev *hdev = nfc_get_drvdata(dev);

	वापस nfc_hci_disconnect_all_gates(hdev);
पूर्ण

अटल पूर्णांक st21nfca_hci_dm_put_data(काष्ठा nfc_dev *dev, व्योम *data,
				  माप_प्रकार data_len)
अणु
	काष्ठा nfc_hci_dev *hdev = nfc_get_drvdata(dev);

	वापस nfc_hci_send_cmd(hdev, ST21NFCA_DEVICE_MGNT_GATE,
				ST21NFCA_HCI_DM_PUTDATA, data,
				data_len, शून्य);
पूर्ण

अटल पूर्णांक st21nfca_hci_dm_update_aid(काष्ठा nfc_dev *dev, व्योम *data,
				    माप_प्रकार data_len)
अणु
	काष्ठा nfc_hci_dev *hdev = nfc_get_drvdata(dev);

	वापस nfc_hci_send_cmd(hdev, ST21NFCA_DEVICE_MGNT_GATE,
			ST21NFCA_HCI_DM_UPDATE_AID, data, data_len, शून्य);
पूर्ण

अटल पूर्णांक st21nfca_hci_dm_get_info(काष्ठा nfc_dev *dev, व्योम *data,
				    माप_प्रकार data_len)
अणु
	पूर्णांक r;
	काष्ठा sk_buff *msg, *skb;
	काष्ठा nfc_hci_dev *hdev = nfc_get_drvdata(dev);

	r = nfc_hci_send_cmd(hdev,
			     ST21NFCA_DEVICE_MGNT_GATE,
			     ST21NFCA_HCI_DM_GETINFO,
			     data, data_len, &skb);
	अगर (r)
		जाओ निकास;

	msg = nfc_venकरोr_cmd_alloc_reply_skb(dev, ST21NFCA_VENDOR_OUI,
					     HCI_DM_GET_INFO, skb->len);
	अगर (!msg) अणु
		r = -ENOMEM;
		जाओ मुक्त_skb;
	पूर्ण

	अगर (nla_put(msg, NFC_ATTR_VENDOR_DATA, skb->len, skb->data)) अणु
		kमुक्त_skb(msg);
		r = -ENOBUFS;
		जाओ मुक्त_skb;
	पूर्ण

	r = nfc_venकरोr_cmd_reply(msg);

मुक्त_skb:
	kमुक्त_skb(skb);
निकास:
	वापस r;
पूर्ण

अटल पूर्णांक st21nfca_hci_dm_get_data(काष्ठा nfc_dev *dev, व्योम *data,
				    माप_प्रकार data_len)
अणु
	पूर्णांक r;
	काष्ठा sk_buff *msg, *skb;
	काष्ठा nfc_hci_dev *hdev = nfc_get_drvdata(dev);

	r = nfc_hci_send_cmd(hdev,
			     ST21NFCA_DEVICE_MGNT_GATE,
			     ST21NFCA_HCI_DM_GETDATA,
			     data, data_len, &skb);
	अगर (r)
		जाओ निकास;

	msg = nfc_venकरोr_cmd_alloc_reply_skb(dev, ST21NFCA_VENDOR_OUI,
					     HCI_DM_GET_DATA, skb->len);
	अगर (!msg) अणु
		r = -ENOMEM;
		जाओ मुक्त_skb;
	पूर्ण

	अगर (nla_put(msg, NFC_ATTR_VENDOR_DATA, skb->len, skb->data)) अणु
		kमुक्त_skb(msg);
		r = -ENOBUFS;
		जाओ मुक्त_skb;
	पूर्ण

	r = nfc_venकरोr_cmd_reply(msg);

मुक्त_skb:
	kमुक्त_skb(skb);
निकास:
	वापस r;
पूर्ण

अटल पूर्णांक st21nfca_hci_dm_load(काष्ठा nfc_dev *dev, व्योम *data,
				माप_प्रकार data_len)
अणु
	काष्ठा nfc_hci_dev *hdev = nfc_get_drvdata(dev);

	वापस nfc_hci_send_cmd(hdev, ST21NFCA_DEVICE_MGNT_GATE,
				ST21NFCA_HCI_DM_LOAD, data, data_len, शून्य);
पूर्ण

अटल पूर्णांक st21nfca_hci_dm_reset(काष्ठा nfc_dev *dev, व्योम *data,
				 माप_प्रकार data_len)
अणु
	पूर्णांक r;
	काष्ठा nfc_hci_dev *hdev = nfc_get_drvdata(dev);

	r = nfc_hci_send_cmd_async(hdev, ST21NFCA_DEVICE_MGNT_GATE,
			ST21NFCA_HCI_DM_RESET, data, data_len, शून्य, शून्य);
	अगर (r < 0)
		वापस r;

	r = nfc_llc_stop(hdev->llc);
	अगर (r < 0)
		वापस r;

	वापस nfc_llc_start(hdev->llc);
पूर्ण

अटल पूर्णांक st21nfca_hci_get_param(काष्ठा nfc_dev *dev, व्योम *data,
				  माप_प्रकार data_len)
अणु
	पूर्णांक r;
	काष्ठा sk_buff *msg, *skb;
	काष्ठा nfc_hci_dev *hdev = nfc_get_drvdata(dev);
	काष्ठा get_param_data *param = (काष्ठा get_param_data *)data;

	अगर (data_len < माप(काष्ठा get_param_data))
		वापस -EPROTO;

	r = nfc_hci_get_param(hdev, param->gate, param->data, &skb);
	अगर (r)
		जाओ निकास;

	msg = nfc_venकरोr_cmd_alloc_reply_skb(dev, ST21NFCA_VENDOR_OUI,
					     HCI_GET_PARAM, skb->len);
	अगर (!msg) अणु
		r = -ENOMEM;
		जाओ मुक्त_skb;
	पूर्ण

	अगर (nla_put(msg, NFC_ATTR_VENDOR_DATA, skb->len, skb->data)) अणु
		kमुक्त_skb(msg);
		r = -ENOBUFS;
		जाओ मुक्त_skb;
	पूर्ण

	r = nfc_venकरोr_cmd_reply(msg);

मुक्त_skb:
	kमुक्त_skb(skb);
निकास:
	वापस r;
पूर्ण

अटल पूर्णांक st21nfca_hci_dm_field_generator(काष्ठा nfc_dev *dev, व्योम *data,
					   माप_प्रकार data_len)
अणु
	काष्ठा nfc_hci_dev *hdev = nfc_get_drvdata(dev);

	वापस nfc_hci_send_cmd(hdev,
				ST21NFCA_DEVICE_MGNT_GATE,
				ST21NFCA_HCI_DM_FIELD_GENERATOR,
				data, data_len, शून्य);
पूर्ण

पूर्णांक st21nfca_hci_loopback_event_received(काष्ठा nfc_hci_dev *hdev, u8 event,
					 काष्ठा sk_buff *skb)
अणु
	काष्ठा st21nfca_hci_info *info = nfc_hci_get_clientdata(hdev);

	चयन (event) अणु
	हाल ST21NFCA_EVT_POST_DATA:
		info->venकरोr_info.rx_skb = skb;
	अवरोध;
	शेष:
		nfc_err(&hdev->ndev->dev, "Unexpected event on loopback gate\n");
	पूर्ण
	complete(&info->venकरोr_info.req_completion);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(st21nfca_hci_loopback_event_received);

अटल पूर्णांक st21nfca_hci_loopback(काष्ठा nfc_dev *dev, व्योम *data,
				 माप_प्रकार data_len)
अणु
	पूर्णांक r;
	काष्ठा sk_buff *msg;
	काष्ठा nfc_hci_dev *hdev = nfc_get_drvdata(dev);
	काष्ठा st21nfca_hci_info *info = nfc_hci_get_clientdata(hdev);

	अगर (data_len <= 0)
		वापस -EPROTO;

	reinit_completion(&info->venकरोr_info.req_completion);
	info->venकरोr_info.rx_skb = शून्य;

	r = nfc_hci_send_event(hdev, NFC_HCI_LOOPBACK_GATE,
			       ST21NFCA_EVT_POST_DATA, data, data_len);
	अगर (r < 0) अणु
		r = -EPROTO;
		जाओ निकास;
	पूर्ण

	रुको_क्रम_completion_पूर्णांकerruptible(&info->venकरोr_info.req_completion);
	अगर (!info->venकरोr_info.rx_skb ||
	    info->venकरोr_info.rx_skb->len != data_len) अणु
		r = -EPROTO;
		जाओ निकास;
	पूर्ण

	msg = nfc_venकरोr_cmd_alloc_reply_skb(hdev->ndev,
					ST21NFCA_VENDOR_OUI,
					HCI_LOOPBACK,
					info->venकरोr_info.rx_skb->len);
	अगर (!msg) अणु
		r = -ENOMEM;
		जाओ मुक्त_skb;
	पूर्ण

	अगर (nla_put(msg, NFC_ATTR_VENDOR_DATA, info->venकरोr_info.rx_skb->len,
		    info->venकरोr_info.rx_skb->data)) अणु
		kमुक्त_skb(msg);
		r = -ENOBUFS;
		जाओ मुक्त_skb;
	पूर्ण

	r = nfc_venकरोr_cmd_reply(msg);
मुक्त_skb:
	kमुक्त_skb(info->venकरोr_info.rx_skb);
निकास:
	वापस r;
पूर्ण

अटल काष्ठा nfc_venकरोr_cmd st21nfca_venकरोr_cmds[] = अणु
	अणु
		.venकरोr_id = ST21NFCA_VENDOR_OUI,
		.subcmd = FACTORY_MODE,
		.करोit = st21nfca_factory_mode,
	पूर्ण,
	अणु
		.venकरोr_id = ST21NFCA_VENDOR_OUI,
		.subcmd = HCI_CLEAR_ALL_PIPES,
		.करोit = st21nfca_hci_clear_all_pipes,
	पूर्ण,
	अणु
		.venकरोr_id = ST21NFCA_VENDOR_OUI,
		.subcmd = HCI_DM_PUT_DATA,
		.करोit = st21nfca_hci_dm_put_data,
	पूर्ण,
	अणु
		.venकरोr_id = ST21NFCA_VENDOR_OUI,
		.subcmd = HCI_DM_UPDATE_AID,
		.करोit = st21nfca_hci_dm_update_aid,
	पूर्ण,
	अणु
		.venकरोr_id = ST21NFCA_VENDOR_OUI,
		.subcmd = HCI_DM_GET_INFO,
		.करोit = st21nfca_hci_dm_get_info,
	पूर्ण,
	अणु
		.venकरोr_id = ST21NFCA_VENDOR_OUI,
		.subcmd = HCI_DM_GET_DATA,
		.करोit = st21nfca_hci_dm_get_data,
	पूर्ण,
	अणु
		.venकरोr_id = ST21NFCA_VENDOR_OUI,
		.subcmd = HCI_DM_LOAD,
		.करोit = st21nfca_hci_dm_load,
	पूर्ण,
	अणु
		.venकरोr_id = ST21NFCA_VENDOR_OUI,
		.subcmd = HCI_DM_RESET,
		.करोit = st21nfca_hci_dm_reset,
	पूर्ण,
	अणु
		.venकरोr_id = ST21NFCA_VENDOR_OUI,
		.subcmd = HCI_GET_PARAM,
		.करोit = st21nfca_hci_get_param,
	पूर्ण,
	अणु
		.venकरोr_id = ST21NFCA_VENDOR_OUI,
		.subcmd = HCI_DM_FIELD_GENERATOR,
		.करोit = st21nfca_hci_dm_field_generator,
	पूर्ण,
	अणु
		.venकरोr_id = ST21NFCA_VENDOR_OUI,
		.subcmd = HCI_LOOPBACK,
		.करोit = st21nfca_hci_loopback,
	पूर्ण,
पूर्ण;

पूर्णांक st21nfca_venकरोr_cmds_init(काष्ठा nfc_hci_dev *hdev)
अणु
	काष्ठा st21nfca_hci_info *info = nfc_hci_get_clientdata(hdev);

	init_completion(&info->venकरोr_info.req_completion);
	वापस nfc_set_venकरोr_cmds(hdev->ndev, st21nfca_venकरोr_cmds,
				   माप(st21nfca_venकरोr_cmds));
पूर्ण
EXPORT_SYMBOL(st21nfca_venकरोr_cmds_init);
