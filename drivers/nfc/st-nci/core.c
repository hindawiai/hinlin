<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * NCI based Driver क्रम STMicroelectronics NFC Chip
 *
 * Copyright (C) 2014-2015  STMicroelectronics SAS. All rights reserved.
 */

#समावेश <linux/module.h>
#समावेश <linux/nfc.h>
#समावेश <net/nfc/nci.h>
#समावेश <net/nfc/nci_core.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/delay.h>

#समावेश "st-nci.h"

#घोषणा DRIVER_DESC "NCI NFC driver for ST_NCI"

#घोषणा ST_NCI1_X_PROPRIETARY_ISO15693 0x83

अटल पूर्णांक st_nci_init(काष्ठा nci_dev *ndev)
अणु
	काष्ठा nci_mode_set_cmd cmd;

	cmd.cmd_type = ST_NCI_SET_NFC_MODE;
	cmd.mode = 1;

	वापस nci_prop_cmd(ndev, ST_NCI_CORE_PROP,
			माप(काष्ठा nci_mode_set_cmd), (__u8 *)&cmd);
पूर्ण

अटल पूर्णांक st_nci_खोलो(काष्ठा nci_dev *ndev)
अणु
	काष्ठा st_nci_info *info = nci_get_drvdata(ndev);
	पूर्णांक r;

	अगर (test_and_set_bit(ST_NCI_RUNNING, &info->flags))
		वापस 0;

	r = ndlc_खोलो(info->ndlc);
	अगर (r)
		clear_bit(ST_NCI_RUNNING, &info->flags);

	वापस r;
पूर्ण

अटल पूर्णांक st_nci_बंद(काष्ठा nci_dev *ndev)
अणु
	काष्ठा st_nci_info *info = nci_get_drvdata(ndev);

	अगर (!test_bit(ST_NCI_RUNNING, &info->flags))
		वापस 0;

	ndlc_बंद(info->ndlc);

	clear_bit(ST_NCI_RUNNING, &info->flags);

	वापस 0;
पूर्ण

अटल पूर्णांक st_nci_send(काष्ठा nci_dev *ndev, काष्ठा sk_buff *skb)
अणु
	काष्ठा st_nci_info *info = nci_get_drvdata(ndev);

	skb->dev = (व्योम *)ndev;

	अगर (!test_bit(ST_NCI_RUNNING, &info->flags))
		वापस -EBUSY;

	वापस ndlc_send(info->ndlc, skb);
पूर्ण

अटल __u32 st_nci_get_rfprotocol(काष्ठा nci_dev *ndev,
					 __u8 rf_protocol)
अणु
	वापस rf_protocol == ST_NCI1_X_PROPRIETARY_ISO15693 ?
		NFC_PROTO_ISO15693_MASK : 0;
पूर्ण

अटल पूर्णांक st_nci_prop_rsp_packet(काष्ठा nci_dev *ndev,
					काष्ठा sk_buff *skb)
अणु
	__u8 status = skb->data[0];

	nci_req_complete(ndev, status);
	वापस 0;
पूर्ण

अटल काष्ठा nci_driver_ops st_nci_prop_ops[] = अणु
	अणु
		.opcode = nci_opcode_pack(NCI_GID_PROPRIETARY,
					  ST_NCI_CORE_PROP),
		.rsp = st_nci_prop_rsp_packet,
	पूर्ण,
पूर्ण;

अटल काष्ठा nci_ops st_nci_ops = अणु
	.init = st_nci_init,
	.खोलो = st_nci_खोलो,
	.बंद = st_nci_बंद,
	.send = st_nci_send,
	.get_rfprotocol = st_nci_get_rfprotocol,
	.discover_se = st_nci_discover_se,
	.enable_se = st_nci_enable_se,
	.disable_se = st_nci_disable_se,
	.se_io = st_nci_se_io,
	.hci_load_session = st_nci_hci_load_session,
	.hci_event_received = st_nci_hci_event_received,
	.hci_cmd_received = st_nci_hci_cmd_received,
	.prop_ops = st_nci_prop_ops,
	.n_prop_ops = ARRAY_SIZE(st_nci_prop_ops),
पूर्ण;

पूर्णांक st_nci_probe(काष्ठा llt_ndlc *ndlc, पूर्णांक phy_headroom,
		 पूर्णांक phy_tailroom, काष्ठा st_nci_se_status *se_status)
अणु
	काष्ठा st_nci_info *info;
	पूर्णांक r;
	u32 protocols;

	info = devm_kzalloc(ndlc->dev,
			माप(काष्ठा st_nci_info), GFP_KERNEL);
	अगर (!info)
		वापस -ENOMEM;

	protocols = NFC_PROTO_JEWEL_MASK
		| NFC_PROTO_MIFARE_MASK
		| NFC_PROTO_FELICA_MASK
		| NFC_PROTO_ISO14443_MASK
		| NFC_PROTO_ISO14443_B_MASK
		| NFC_PROTO_ISO15693_MASK
		| NFC_PROTO_NFC_DEP_MASK;

	ndlc->ndev = nci_allocate_device(&st_nci_ops, protocols,
					phy_headroom, phy_tailroom);
	अगर (!ndlc->ndev) अणु
		pr_err("Cannot allocate nfc ndev\n");
		वापस -ENOMEM;
	पूर्ण
	info->ndlc = ndlc;

	nci_set_drvdata(ndlc->ndev, info);

	r = st_nci_venकरोr_cmds_init(ndlc->ndev);
	अगर (r) अणु
		pr_err("Cannot register proprietary vendor cmds\n");
		जाओ err_reg_dev;
	पूर्ण

	r = nci_रेजिस्टर_device(ndlc->ndev);
	अगर (r) अणु
		pr_err("Cannot register nfc device to nci core\n");
		जाओ err_reg_dev;
	पूर्ण

	वापस st_nci_se_init(ndlc->ndev, se_status);

err_reg_dev:
	nci_मुक्त_device(ndlc->ndev);
	वापस r;
पूर्ण
EXPORT_SYMBOL_GPL(st_nci_probe);

व्योम st_nci_हटाओ(काष्ठा nci_dev *ndev)
अणु
	काष्ठा st_nci_info *info = nci_get_drvdata(ndev);

	ndlc_बंद(info->ndlc);

	nci_unरेजिस्टर_device(ndev);
	nci_मुक्त_device(ndev);
पूर्ण
EXPORT_SYMBOL_GPL(st_nci_हटाओ);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION(DRIVER_DESC);
