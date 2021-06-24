<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Proprietary commands extension क्रम STMicroelectronics NFC NCI Chip
 *
 * Copyright (C) 2014-2015  STMicroelectronics SAS. All rights reserved.
 */

#समावेश <net/genetlink.h>
#समावेश <linux/module.h>
#समावेश <linux/nfc.h>
#समावेश <linux/delay.h>
#समावेश <net/nfc/nci_core.h>

#समावेश "st-nci.h"

#घोषणा ST_NCI_HCI_DM_GETDATA			0x10
#घोषणा ST_NCI_HCI_DM_PUTDATA			0x11
#घोषणा ST_NCI_HCI_DM_LOAD			0x12
#घोषणा ST_NCI_HCI_DM_GETINFO			0x13
#घोषणा ST_NCI_HCI_DM_FWUPD_START		0x14
#घोषणा ST_NCI_HCI_DM_FWUPD_STOP		0x15
#घोषणा ST_NCI_HCI_DM_UPDATE_AID		0x20
#घोषणा ST_NCI_HCI_DM_RESET			0x3e

#घोषणा ST_NCI_HCI_DM_FIELD_GENERATOR		0x32
#घोषणा ST_NCI_HCI_DM_VDC_MEASUREMENT_VALUE	0x33
#घोषणा ST_NCI_HCI_DM_VDC_VALUE_COMPARISON	0x34

#घोषणा ST_NCI_FACTORY_MODE_ON			1
#घोषणा ST_NCI_FACTORY_MODE_OFF			0

#घोषणा ST_NCI_EVT_POST_DATA			0x02

काष्ठा get_param_data अणु
	u8 gate;
	u8 data;
पूर्ण __packed;

अटल पूर्णांक st_nci_factory_mode(काष्ठा nfc_dev *dev, व्योम *data,
			       माप_प्रकार data_len)
अणु
	काष्ठा nci_dev *ndev = nfc_get_drvdata(dev);
	काष्ठा st_nci_info *info = nci_get_drvdata(ndev);

	अगर (data_len != 1)
		वापस -EINVAL;

	pr_debug("factory mode: %x\n", ((u8 *)data)[0]);

	चयन (((u8 *)data)[0]) अणु
	हाल ST_NCI_FACTORY_MODE_ON:
		test_and_set_bit(ST_NCI_FACTORY_MODE, &info->flags);
	अवरोध;
	हाल ST_NCI_FACTORY_MODE_OFF:
		clear_bit(ST_NCI_FACTORY_MODE, &info->flags);
	अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक st_nci_hci_clear_all_pipes(काष्ठा nfc_dev *dev, व्योम *data,
				      माप_प्रकार data_len)
अणु
	काष्ठा nci_dev *ndev = nfc_get_drvdata(dev);

	वापस nci_hci_clear_all_pipes(ndev);
पूर्ण

अटल पूर्णांक st_nci_hci_dm_put_data(काष्ठा nfc_dev *dev, व्योम *data,
				  माप_प्रकार data_len)
अणु
	काष्ठा nci_dev *ndev = nfc_get_drvdata(dev);

	वापस nci_hci_send_cmd(ndev, ST_NCI_DEVICE_MGNT_GATE,
				ST_NCI_HCI_DM_PUTDATA, data,
				data_len, शून्य);
पूर्ण

अटल पूर्णांक st_nci_hci_dm_update_aid(काष्ठा nfc_dev *dev, व्योम *data,
				    माप_प्रकार data_len)
अणु
	काष्ठा nci_dev *ndev = nfc_get_drvdata(dev);

	वापस nci_hci_send_cmd(ndev, ST_NCI_DEVICE_MGNT_GATE,
			ST_NCI_HCI_DM_UPDATE_AID, data, data_len, शून्य);
पूर्ण

अटल पूर्णांक st_nci_hci_dm_get_info(काष्ठा nfc_dev *dev, व्योम *data,
				  माप_प्रकार data_len)
अणु
	पूर्णांक r;
	काष्ठा sk_buff *msg, *skb;
	काष्ठा nci_dev *ndev = nfc_get_drvdata(dev);

	r = nci_hci_send_cmd(ndev, ST_NCI_DEVICE_MGNT_GATE, ST_NCI_HCI_DM_GETINFO,
			     data, data_len, &skb);
	अगर (r)
		जाओ निकास;

	msg = nfc_venकरोr_cmd_alloc_reply_skb(dev, ST_NCI_VENDOR_OUI,
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

अटल पूर्णांक st_nci_hci_dm_get_data(काष्ठा nfc_dev *dev, व्योम *data,
				  माप_प्रकार data_len)
अणु
	पूर्णांक r;
	काष्ठा sk_buff *msg, *skb;
	काष्ठा nci_dev *ndev = nfc_get_drvdata(dev);

	r = nci_hci_send_cmd(ndev, ST_NCI_DEVICE_MGNT_GATE, ST_NCI_HCI_DM_GETDATA,
			     data, data_len, &skb);
	अगर (r)
		जाओ निकास;

	msg = nfc_venकरोr_cmd_alloc_reply_skb(dev, ST_NCI_VENDOR_OUI,
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

अटल पूर्णांक st_nci_hci_dm_fwupd_start(काष्ठा nfc_dev *dev, व्योम *data,
				     माप_प्रकार data_len)
अणु
	पूर्णांक r;
	काष्ठा nci_dev *ndev = nfc_get_drvdata(dev);

	dev->fw_करोwnload_in_progress = true;
	r = nci_hci_send_cmd(ndev, ST_NCI_DEVICE_MGNT_GATE,
			ST_NCI_HCI_DM_FWUPD_START, data, data_len, शून्य);
	अगर (r)
		dev->fw_करोwnload_in_progress = false;

	वापस r;
पूर्ण

अटल पूर्णांक st_nci_hci_dm_fwupd_end(काष्ठा nfc_dev *dev, व्योम *data,
				   माप_प्रकार data_len)
अणु
	काष्ठा nci_dev *ndev = nfc_get_drvdata(dev);

	वापस nci_hci_send_cmd(ndev, ST_NCI_DEVICE_MGNT_GATE,
			ST_NCI_HCI_DM_FWUPD_STOP, data, data_len, शून्य);
पूर्ण

अटल पूर्णांक st_nci_hci_dm_direct_load(काष्ठा nfc_dev *dev, व्योम *data,
				     माप_प्रकार data_len)
अणु
	काष्ठा nci_dev *ndev = nfc_get_drvdata(dev);

	अगर (dev->fw_करोwnload_in_progress) अणु
		dev->fw_करोwnload_in_progress = false;
		वापस nci_hci_send_cmd(ndev, ST_NCI_DEVICE_MGNT_GATE,
				ST_NCI_HCI_DM_LOAD, data, data_len, शून्य);
	पूर्ण
	वापस -EPROTO;
पूर्ण

अटल पूर्णांक st_nci_hci_dm_reset(काष्ठा nfc_dev *dev, व्योम *data,
			       माप_प्रकार data_len)
अणु
	काष्ठा nci_dev *ndev = nfc_get_drvdata(dev);

	nci_hci_send_cmd(ndev, ST_NCI_DEVICE_MGNT_GATE,
			ST_NCI_HCI_DM_RESET, data, data_len, शून्य);
	msleep(200);

	वापस 0;
पूर्ण

अटल पूर्णांक st_nci_hci_get_param(काष्ठा nfc_dev *dev, व्योम *data,
				माप_प्रकार data_len)
अणु
	पूर्णांक r;
	काष्ठा sk_buff *msg, *skb;
	काष्ठा nci_dev *ndev = nfc_get_drvdata(dev);
	काष्ठा get_param_data *param = (काष्ठा get_param_data *)data;

	अगर (data_len < माप(काष्ठा get_param_data))
		वापस -EPROTO;

	r = nci_hci_get_param(ndev, param->gate, param->data, &skb);
	अगर (r)
		जाओ निकास;

	msg = nfc_venकरोr_cmd_alloc_reply_skb(dev, ST_NCI_VENDOR_OUI,
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

अटल पूर्णांक st_nci_hci_dm_field_generator(काष्ठा nfc_dev *dev, व्योम *data,
					 माप_प्रकार data_len)
अणु
	काष्ठा nci_dev *ndev = nfc_get_drvdata(dev);

	वापस nci_hci_send_cmd(ndev, ST_NCI_DEVICE_MGNT_GATE,
				ST_NCI_HCI_DM_FIELD_GENERATOR, data, data_len, शून्य);
पूर्ण

अटल पूर्णांक st_nci_hci_dm_vdc_measurement_value(काष्ठा nfc_dev *dev, व्योम *data,
					       माप_प्रकार data_len)
अणु
	पूर्णांक r;
	काष्ठा sk_buff *msg, *skb;
	काष्ठा nci_dev *ndev = nfc_get_drvdata(dev);

	अगर (data_len != 4)
		वापस -EPROTO;

	r = nci_hci_send_cmd(ndev, ST_NCI_DEVICE_MGNT_GATE,
			     ST_NCI_HCI_DM_VDC_MEASUREMENT_VALUE,
			     data, data_len, &skb);
	अगर (r)
		जाओ निकास;

	msg = nfc_venकरोr_cmd_alloc_reply_skb(dev, ST_NCI_VENDOR_OUI,
				HCI_DM_VDC_MEASUREMENT_VALUE, skb->len);
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

अटल पूर्णांक st_nci_hci_dm_vdc_value_comparison(काष्ठा nfc_dev *dev, व्योम *data,
					      माप_प्रकार data_len)
अणु
	पूर्णांक r;
	काष्ठा sk_buff *msg, *skb;
	काष्ठा nci_dev *ndev = nfc_get_drvdata(dev);

	अगर (data_len != 2)
		वापस -EPROTO;

	r = nci_hci_send_cmd(ndev, ST_NCI_DEVICE_MGNT_GATE,
			     ST_NCI_HCI_DM_VDC_VALUE_COMPARISON,
			     data, data_len, &skb);
	अगर (r)
		जाओ निकास;

	msg = nfc_venकरोr_cmd_alloc_reply_skb(dev, ST_NCI_VENDOR_OUI,
					HCI_DM_VDC_VALUE_COMPARISON, skb->len);
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

अटल पूर्णांक st_nci_loopback(काष्ठा nfc_dev *dev, व्योम *data,
			   माप_प्रकार data_len)
अणु
	पूर्णांक r;
	काष्ठा sk_buff *msg, *skb;
	काष्ठा nci_dev *ndev = nfc_get_drvdata(dev);

	अगर (data_len <= 0)
		वापस -EPROTO;

	r = nci_nfcc_loopback(ndev, data, data_len, &skb);
	अगर (r < 0)
		वापस r;

	msg = nfc_venकरोr_cmd_alloc_reply_skb(dev, ST_NCI_VENDOR_OUI,
					     LOOPBACK, skb->len);
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
	वापस r;
पूर्ण

अटल पूर्णांक st_nci_manufacturer_specअगरic(काष्ठा nfc_dev *dev, व्योम *data,
					माप_प्रकार data_len)
अणु
	काष्ठा sk_buff *msg;
	काष्ठा nci_dev *ndev = nfc_get_drvdata(dev);

	msg = nfc_venकरोr_cmd_alloc_reply_skb(dev, ST_NCI_VENDOR_OUI,
					MANUFACTURER_SPECIFIC,
					माप(ndev->manufact_specअगरic_info));
	अगर (!msg)
		वापस -ENOMEM;

	अगर (nla_put(msg, NFC_ATTR_VENDOR_DATA, माप(ndev->manufact_specअगरic_info),
		    &ndev->manufact_specअगरic_info)) अणु
		kमुक्त_skb(msg);
		वापस -ENOBUFS;
	पूर्ण

	वापस nfc_venकरोr_cmd_reply(msg);
पूर्ण

अटल काष्ठा nfc_venकरोr_cmd st_nci_venकरोr_cmds[] = अणु
	अणु
		.venकरोr_id = ST_NCI_VENDOR_OUI,
		.subcmd = FACTORY_MODE,
		.करोit = st_nci_factory_mode,
	पूर्ण,
	अणु
		.venकरोr_id = ST_NCI_VENDOR_OUI,
		.subcmd = HCI_CLEAR_ALL_PIPES,
		.करोit = st_nci_hci_clear_all_pipes,
	पूर्ण,
	अणु
		.venकरोr_id = ST_NCI_VENDOR_OUI,
		.subcmd = HCI_DM_PUT_DATA,
		.करोit = st_nci_hci_dm_put_data,
	पूर्ण,
	अणु
		.venकरोr_id = ST_NCI_VENDOR_OUI,
		.subcmd = HCI_DM_UPDATE_AID,
		.करोit = st_nci_hci_dm_update_aid,
	पूर्ण,
	अणु
		.venकरोr_id = ST_NCI_VENDOR_OUI,
		.subcmd = HCI_DM_GET_INFO,
		.करोit = st_nci_hci_dm_get_info,
	पूर्ण,
	अणु
		.venकरोr_id = ST_NCI_VENDOR_OUI,
		.subcmd = HCI_DM_GET_DATA,
		.करोit = st_nci_hci_dm_get_data,
	पूर्ण,
	अणु
		.venकरोr_id = ST_NCI_VENDOR_OUI,
		.subcmd = HCI_DM_सूचीECT_LOAD,
		.करोit = st_nci_hci_dm_direct_load,
	पूर्ण,
	अणु
		.venकरोr_id = ST_NCI_VENDOR_OUI,
		.subcmd = HCI_DM_RESET,
		.करोit = st_nci_hci_dm_reset,
	पूर्ण,
	अणु
		.venकरोr_id = ST_NCI_VENDOR_OUI,
		.subcmd = HCI_GET_PARAM,
		.करोit = st_nci_hci_get_param,
	पूर्ण,
	अणु
		.venकरोr_id = ST_NCI_VENDOR_OUI,
		.subcmd = HCI_DM_FIELD_GENERATOR,
		.करोit = st_nci_hci_dm_field_generator,
	पूर्ण,
	अणु
		.venकरोr_id = ST_NCI_VENDOR_OUI,
		.subcmd = HCI_DM_FWUPD_START,
		.करोit = st_nci_hci_dm_fwupd_start,
	पूर्ण,
	अणु
		.venकरोr_id = ST_NCI_VENDOR_OUI,
		.subcmd = HCI_DM_FWUPD_END,
		.करोit = st_nci_hci_dm_fwupd_end,
	पूर्ण,
	अणु
		.venकरोr_id = ST_NCI_VENDOR_OUI,
		.subcmd = LOOPBACK,
		.करोit = st_nci_loopback,
	पूर्ण,
	अणु
		.venकरोr_id = ST_NCI_VENDOR_OUI,
		.subcmd = HCI_DM_VDC_MEASUREMENT_VALUE,
		.करोit = st_nci_hci_dm_vdc_measurement_value,
	पूर्ण,
	अणु
		.venकरोr_id = ST_NCI_VENDOR_OUI,
		.subcmd = HCI_DM_VDC_VALUE_COMPARISON,
		.करोit = st_nci_hci_dm_vdc_value_comparison,
	पूर्ण,
	अणु
		.venकरोr_id = ST_NCI_VENDOR_OUI,
		.subcmd = MANUFACTURER_SPECIFIC,
		.करोit = st_nci_manufacturer_specअगरic,
	पूर्ण,
पूर्ण;

पूर्णांक st_nci_venकरोr_cmds_init(काष्ठा nci_dev *ndev)
अणु
	वापस nfc_set_venकरोr_cmds(ndev->nfc_dev, st_nci_venकरोr_cmds,
				   माप(st_nci_venकरोr_cmds));
पूर्ण
EXPORT_SYMBOL(st_nci_venकरोr_cmds_init);
