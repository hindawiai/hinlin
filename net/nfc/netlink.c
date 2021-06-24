<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2011 Instituto Nokia de Tecnologia
 *
 * Authors:
 *    Lauro Ramos Venancio <lauro.venancio@खोलोbossa.org>
 *    Aloisio Almeida Jr <aloisio.almeida@खोलोbossa.org>
 *
 * Venकरोr commands implementation based on net/wireless/nl80211.c
 * which is:
 *
 * Copyright 2006-2010	Johannes Berg <johannes@sipsolutions.net>
 * Copyright 2013-2014  Intel Mobile Communications GmbH
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": %s: " fmt, __func__

#समावेश <net/genetlink.h>
#समावेश <linux/nfc.h>
#समावेश <linux/slab.h>

#समावेश "nfc.h"
#समावेश "llcp.h"

अटल स्थिर काष्ठा genl_multicast_group nfc_genl_mcgrps[] = अणु
	अणु .name = NFC_GENL_MCAST_EVENT_NAME, पूर्ण,
पूर्ण;

अटल काष्ठा genl_family nfc_genl_family;
अटल स्थिर काष्ठा nla_policy nfc_genl_policy[NFC_ATTR_MAX + 1] = अणु
	[NFC_ATTR_DEVICE_INDEX] = अणु .type = NLA_U32 पूर्ण,
	[NFC_ATTR_DEVICE_NAME] = अणु .type = NLA_STRING,
				.len = NFC_DEVICE_NAME_MAXSIZE पूर्ण,
	[NFC_ATTR_PROTOCOLS] = अणु .type = NLA_U32 पूर्ण,
	[NFC_ATTR_TARGET_INDEX] = अणु .type = NLA_U32 पूर्ण,
	[NFC_ATTR_COMM_MODE] = अणु .type = NLA_U8 पूर्ण,
	[NFC_ATTR_RF_MODE] = अणु .type = NLA_U8 पूर्ण,
	[NFC_ATTR_DEVICE_POWERED] = अणु .type = NLA_U8 पूर्ण,
	[NFC_ATTR_IM_PROTOCOLS] = अणु .type = NLA_U32 पूर्ण,
	[NFC_ATTR_TM_PROTOCOLS] = अणु .type = NLA_U32 पूर्ण,
	[NFC_ATTR_LLC_PARAM_LTO] = अणु .type = NLA_U8 पूर्ण,
	[NFC_ATTR_LLC_PARAM_RW] = अणु .type = NLA_U8 पूर्ण,
	[NFC_ATTR_LLC_PARAM_MIUX] = अणु .type = NLA_U16 पूर्ण,
	[NFC_ATTR_LLC_SDP] = अणु .type = NLA_NESTED पूर्ण,
	[NFC_ATTR_FIRMWARE_NAME] = अणु .type = NLA_STRING,
				     .len = NFC_FIRMWARE_NAME_MAXSIZE पूर्ण,
	[NFC_ATTR_SE_INDEX] = अणु .type = NLA_U32 पूर्ण,
	[NFC_ATTR_SE_APDU] = अणु .type = NLA_BINARY पूर्ण,
	[NFC_ATTR_VENDOR_ID] = अणु .type = NLA_U32 पूर्ण,
	[NFC_ATTR_VENDOR_SUBCMD] = अणु .type = NLA_U32 पूर्ण,
	[NFC_ATTR_VENDOR_DATA] = अणु .type = NLA_BINARY पूर्ण,

पूर्ण;

अटल स्थिर काष्ठा nla_policy nfc_sdp_genl_policy[NFC_SDP_ATTR_MAX + 1] = अणु
	[NFC_SDP_ATTR_URI] = अणु .type = NLA_STRING,
			       .len = U8_MAX - 4 पूर्ण,
	[NFC_SDP_ATTR_SAP] = अणु .type = NLA_U8 पूर्ण,
पूर्ण;

अटल पूर्णांक nfc_genl_send_target(काष्ठा sk_buff *msg, काष्ठा nfc_target *target,
				काष्ठा netlink_callback *cb, पूर्णांक flags)
अणु
	व्योम *hdr;

	hdr = genlmsg_put(msg, NETLINK_CB(cb->skb).portid, cb->nlh->nlmsg_seq,
			  &nfc_genl_family, flags, NFC_CMD_GET_TARGET);
	अगर (!hdr)
		वापस -EMSGSIZE;

	genl_dump_check_consistent(cb, hdr);

	अगर (nla_put_u32(msg, NFC_ATTR_TARGET_INDEX, target->idx) ||
	    nla_put_u32(msg, NFC_ATTR_PROTOCOLS, target->supported_protocols) ||
	    nla_put_u16(msg, NFC_ATTR_TARGET_SENS_RES, target->sens_res) ||
	    nla_put_u8(msg, NFC_ATTR_TARGET_SEL_RES, target->sel_res))
		जाओ nla_put_failure;
	अगर (target->nfcid1_len > 0 &&
	    nla_put(msg, NFC_ATTR_TARGET_NFCID1, target->nfcid1_len,
		    target->nfcid1))
		जाओ nla_put_failure;
	अगर (target->sensb_res_len > 0 &&
	    nla_put(msg, NFC_ATTR_TARGET_SENSB_RES, target->sensb_res_len,
		    target->sensb_res))
		जाओ nla_put_failure;
	अगर (target->sensf_res_len > 0 &&
	    nla_put(msg, NFC_ATTR_TARGET_SENSF_RES, target->sensf_res_len,
		    target->sensf_res))
		जाओ nla_put_failure;

	अगर (target->is_iso15693) अणु
		अगर (nla_put_u8(msg, NFC_ATTR_TARGET_ISO15693_DSFID,
			       target->iso15693_dsfid) ||
		    nla_put(msg, NFC_ATTR_TARGET_ISO15693_UID,
			    माप(target->iso15693_uid), target->iso15693_uid))
			जाओ nla_put_failure;
	पूर्ण

	genlmsg_end(msg, hdr);
	वापस 0;

nla_put_failure:
	genlmsg_cancel(msg, hdr);
	वापस -EMSGSIZE;
पूर्ण

अटल काष्ठा nfc_dev *__get_device_from_cb(काष्ठा netlink_callback *cb)
अणु
	स्थिर काष्ठा genl_dumpit_info *info = genl_dumpit_info(cb);
	काष्ठा nfc_dev *dev;
	u32 idx;

	अगर (!info->attrs[NFC_ATTR_DEVICE_INDEX])
		वापस ERR_PTR(-EINVAL);

	idx = nla_get_u32(info->attrs[NFC_ATTR_DEVICE_INDEX]);

	dev = nfc_get_device(idx);
	अगर (!dev)
		वापस ERR_PTR(-ENODEV);

	वापस dev;
पूर्ण

अटल पूर्णांक nfc_genl_dump_tarमाला_लो(काष्ठा sk_buff *skb,
				 काष्ठा netlink_callback *cb)
अणु
	पूर्णांक i = cb->args[0];
	काष्ठा nfc_dev *dev = (काष्ठा nfc_dev *) cb->args[1];
	पूर्णांक rc;

	अगर (!dev) अणु
		dev = __get_device_from_cb(cb);
		अगर (IS_ERR(dev))
			वापस PTR_ERR(dev);

		cb->args[1] = (दीर्घ) dev;
	पूर्ण

	device_lock(&dev->dev);

	cb->seq = dev->tarमाला_लो_generation;

	जबतक (i < dev->n_tarमाला_लो) अणु
		rc = nfc_genl_send_target(skb, &dev->tarमाला_लो[i], cb,
					  NLM_F_MULTI);
		अगर (rc < 0)
			अवरोध;

		i++;
	पूर्ण

	device_unlock(&dev->dev);

	cb->args[0] = i;

	वापस skb->len;
पूर्ण

अटल पूर्णांक nfc_genl_dump_tarमाला_लो_करोne(काष्ठा netlink_callback *cb)
अणु
	काष्ठा nfc_dev *dev = (काष्ठा nfc_dev *) cb->args[1];

	अगर (dev)
		nfc_put_device(dev);

	वापस 0;
पूर्ण

पूर्णांक nfc_genl_tarमाला_लो_found(काष्ठा nfc_dev *dev)
अणु
	काष्ठा sk_buff *msg;
	व्योम *hdr;

	dev->genl_data.poll_req_portid = 0;

	msg = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_ATOMIC);
	अगर (!msg)
		वापस -ENOMEM;

	hdr = genlmsg_put(msg, 0, 0, &nfc_genl_family, 0,
			  NFC_EVENT_TARGETS_FOUND);
	अगर (!hdr)
		जाओ मुक्त_msg;

	अगर (nla_put_u32(msg, NFC_ATTR_DEVICE_INDEX, dev->idx))
		जाओ nla_put_failure;

	genlmsg_end(msg, hdr);

	वापस genlmsg_multicast(&nfc_genl_family, msg, 0, 0, GFP_ATOMIC);

nla_put_failure:
मुक्त_msg:
	nlmsg_मुक्त(msg);
	वापस -EMSGSIZE;
पूर्ण

पूर्णांक nfc_genl_target_lost(काष्ठा nfc_dev *dev, u32 target_idx)
अणु
	काष्ठा sk_buff *msg;
	व्योम *hdr;

	msg = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	अगर (!msg)
		वापस -ENOMEM;

	hdr = genlmsg_put(msg, 0, 0, &nfc_genl_family, 0,
			  NFC_EVENT_TARGET_LOST);
	अगर (!hdr)
		जाओ मुक्त_msg;

	अगर (nla_put_string(msg, NFC_ATTR_DEVICE_NAME, nfc_device_name(dev)) ||
	    nla_put_u32(msg, NFC_ATTR_TARGET_INDEX, target_idx))
		जाओ nla_put_failure;

	genlmsg_end(msg, hdr);

	genlmsg_multicast(&nfc_genl_family, msg, 0, 0, GFP_KERNEL);

	वापस 0;

nla_put_failure:
मुक्त_msg:
	nlmsg_मुक्त(msg);
	वापस -EMSGSIZE;
पूर्ण

पूर्णांक nfc_genl_पंचांग_activated(काष्ठा nfc_dev *dev, u32 protocol)
अणु
	काष्ठा sk_buff *msg;
	व्योम *hdr;

	msg = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	अगर (!msg)
		वापस -ENOMEM;

	hdr = genlmsg_put(msg, 0, 0, &nfc_genl_family, 0,
			  NFC_EVENT_TM_ACTIVATED);
	अगर (!hdr)
		जाओ मुक्त_msg;

	अगर (nla_put_u32(msg, NFC_ATTR_DEVICE_INDEX, dev->idx))
		जाओ nla_put_failure;
	अगर (nla_put_u32(msg, NFC_ATTR_TM_PROTOCOLS, protocol))
		जाओ nla_put_failure;

	genlmsg_end(msg, hdr);

	genlmsg_multicast(&nfc_genl_family, msg, 0, 0, GFP_KERNEL);

	वापस 0;

nla_put_failure:
मुक्त_msg:
	nlmsg_मुक्त(msg);
	वापस -EMSGSIZE;
पूर्ण

पूर्णांक nfc_genl_पंचांग_deactivated(काष्ठा nfc_dev *dev)
अणु
	काष्ठा sk_buff *msg;
	व्योम *hdr;

	msg = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	अगर (!msg)
		वापस -ENOMEM;

	hdr = genlmsg_put(msg, 0, 0, &nfc_genl_family, 0,
			  NFC_EVENT_TM_DEACTIVATED);
	अगर (!hdr)
		जाओ मुक्त_msg;

	अगर (nla_put_u32(msg, NFC_ATTR_DEVICE_INDEX, dev->idx))
		जाओ nla_put_failure;

	genlmsg_end(msg, hdr);

	genlmsg_multicast(&nfc_genl_family, msg, 0, 0, GFP_KERNEL);

	वापस 0;

nla_put_failure:
मुक्त_msg:
	nlmsg_मुक्त(msg);
	वापस -EMSGSIZE;
पूर्ण

अटल पूर्णांक nfc_genl_setup_device_added(काष्ठा nfc_dev *dev, काष्ठा sk_buff *msg)
अणु
	अगर (nla_put_string(msg, NFC_ATTR_DEVICE_NAME, nfc_device_name(dev)) ||
	    nla_put_u32(msg, NFC_ATTR_DEVICE_INDEX, dev->idx) ||
	    nla_put_u32(msg, NFC_ATTR_PROTOCOLS, dev->supported_protocols) ||
	    nla_put_u8(msg, NFC_ATTR_DEVICE_POWERED, dev->dev_up) ||
	    nla_put_u8(msg, NFC_ATTR_RF_MODE, dev->rf_mode))
		वापस -1;
	वापस 0;
पूर्ण

पूर्णांक nfc_genl_device_added(काष्ठा nfc_dev *dev)
अणु
	काष्ठा sk_buff *msg;
	व्योम *hdr;

	msg = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	अगर (!msg)
		वापस -ENOMEM;

	hdr = genlmsg_put(msg, 0, 0, &nfc_genl_family, 0,
			  NFC_EVENT_DEVICE_ADDED);
	अगर (!hdr)
		जाओ मुक्त_msg;

	अगर (nfc_genl_setup_device_added(dev, msg))
		जाओ nla_put_failure;

	genlmsg_end(msg, hdr);

	genlmsg_multicast(&nfc_genl_family, msg, 0, 0, GFP_KERNEL);

	वापस 0;

nla_put_failure:
मुक्त_msg:
	nlmsg_मुक्त(msg);
	वापस -EMSGSIZE;
पूर्ण

पूर्णांक nfc_genl_device_हटाओd(काष्ठा nfc_dev *dev)
अणु
	काष्ठा sk_buff *msg;
	व्योम *hdr;

	msg = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	अगर (!msg)
		वापस -ENOMEM;

	hdr = genlmsg_put(msg, 0, 0, &nfc_genl_family, 0,
			  NFC_EVENT_DEVICE_REMOVED);
	अगर (!hdr)
		जाओ मुक्त_msg;

	अगर (nla_put_u32(msg, NFC_ATTR_DEVICE_INDEX, dev->idx))
		जाओ nla_put_failure;

	genlmsg_end(msg, hdr);

	genlmsg_multicast(&nfc_genl_family, msg, 0, 0, GFP_KERNEL);

	वापस 0;

nla_put_failure:
मुक्त_msg:
	nlmsg_मुक्त(msg);
	वापस -EMSGSIZE;
पूर्ण

पूर्णांक nfc_genl_llc_send_sdres(काष्ठा nfc_dev *dev, काष्ठा hlist_head *sdres_list)
अणु
	काष्ठा sk_buff *msg;
	काष्ठा nlattr *sdp_attr, *uri_attr;
	काष्ठा nfc_llcp_sdp_tlv *sdres;
	काष्ठा hlist_node *n;
	व्योम *hdr;
	पूर्णांक rc = -EMSGSIZE;
	पूर्णांक i;

	msg = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	अगर (!msg)
		वापस -ENOMEM;

	hdr = genlmsg_put(msg, 0, 0, &nfc_genl_family, 0,
			  NFC_EVENT_LLC_SDRES);
	अगर (!hdr)
		जाओ मुक्त_msg;

	अगर (nla_put_u32(msg, NFC_ATTR_DEVICE_INDEX, dev->idx))
		जाओ nla_put_failure;

	sdp_attr = nla_nest_start_noflag(msg, NFC_ATTR_LLC_SDP);
	अगर (sdp_attr == शून्य) अणु
		rc = -ENOMEM;
		जाओ nla_put_failure;
	पूर्ण

	i = 1;
	hlist_क्रम_each_entry_safe(sdres, n, sdres_list, node) अणु
		pr_debug("uri: %s, sap: %d\n", sdres->uri, sdres->sap);

		uri_attr = nla_nest_start_noflag(msg, i++);
		अगर (uri_attr == शून्य) अणु
			rc = -ENOMEM;
			जाओ nla_put_failure;
		पूर्ण

		अगर (nla_put_u8(msg, NFC_SDP_ATTR_SAP, sdres->sap))
			जाओ nla_put_failure;

		अगर (nla_put_string(msg, NFC_SDP_ATTR_URI, sdres->uri))
			जाओ nla_put_failure;

		nla_nest_end(msg, uri_attr);

		hlist_del(&sdres->node);

		nfc_llcp_मुक्त_sdp_tlv(sdres);
	पूर्ण

	nla_nest_end(msg, sdp_attr);

	genlmsg_end(msg, hdr);

	वापस genlmsg_multicast(&nfc_genl_family, msg, 0, 0, GFP_ATOMIC);

nla_put_failure:
मुक्त_msg:
	nlmsg_मुक्त(msg);

	nfc_llcp_मुक्त_sdp_tlv_list(sdres_list);

	वापस rc;
पूर्ण

पूर्णांक nfc_genl_se_added(काष्ठा nfc_dev *dev, u32 se_idx, u16 type)
अणु
	काष्ठा sk_buff *msg;
	व्योम *hdr;

	msg = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	अगर (!msg)
		वापस -ENOMEM;

	hdr = genlmsg_put(msg, 0, 0, &nfc_genl_family, 0,
			  NFC_EVENT_SE_ADDED);
	अगर (!hdr)
		जाओ मुक्त_msg;

	अगर (nla_put_u32(msg, NFC_ATTR_DEVICE_INDEX, dev->idx) ||
	    nla_put_u32(msg, NFC_ATTR_SE_INDEX, se_idx) ||
	    nla_put_u8(msg, NFC_ATTR_SE_TYPE, type))
		जाओ nla_put_failure;

	genlmsg_end(msg, hdr);

	genlmsg_multicast(&nfc_genl_family, msg, 0, 0, GFP_KERNEL);

	वापस 0;

nla_put_failure:
मुक्त_msg:
	nlmsg_मुक्त(msg);
	वापस -EMSGSIZE;
पूर्ण

पूर्णांक nfc_genl_se_हटाओd(काष्ठा nfc_dev *dev, u32 se_idx)
अणु
	काष्ठा sk_buff *msg;
	व्योम *hdr;

	msg = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	अगर (!msg)
		वापस -ENOMEM;

	hdr = genlmsg_put(msg, 0, 0, &nfc_genl_family, 0,
			  NFC_EVENT_SE_REMOVED);
	अगर (!hdr)
		जाओ मुक्त_msg;

	अगर (nla_put_u32(msg, NFC_ATTR_DEVICE_INDEX, dev->idx) ||
	    nla_put_u32(msg, NFC_ATTR_SE_INDEX, se_idx))
		जाओ nla_put_failure;

	genlmsg_end(msg, hdr);

	genlmsg_multicast(&nfc_genl_family, msg, 0, 0, GFP_KERNEL);

	वापस 0;

nla_put_failure:
मुक्त_msg:
	nlmsg_मुक्त(msg);
	वापस -EMSGSIZE;
पूर्ण

पूर्णांक nfc_genl_se_transaction(काष्ठा nfc_dev *dev, u8 se_idx,
			    काष्ठा nfc_evt_transaction *evt_transaction)
अणु
	काष्ठा nfc_se *se;
	काष्ठा sk_buff *msg;
	व्योम *hdr;

	msg = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	अगर (!msg)
		वापस -ENOMEM;

	hdr = genlmsg_put(msg, 0, 0, &nfc_genl_family, 0,
			  NFC_EVENT_SE_TRANSACTION);
	अगर (!hdr)
		जाओ मुक्त_msg;

	se = nfc_find_se(dev, se_idx);
	अगर (!se)
		जाओ मुक्त_msg;

	अगर (nla_put_u32(msg, NFC_ATTR_DEVICE_INDEX, dev->idx) ||
	    nla_put_u32(msg, NFC_ATTR_SE_INDEX, se_idx) ||
	    nla_put_u8(msg, NFC_ATTR_SE_TYPE, se->type) ||
	    nla_put(msg, NFC_ATTR_SE_AID, evt_transaction->aid_len,
		    evt_transaction->aid) ||
	    nla_put(msg, NFC_ATTR_SE_PARAMS, evt_transaction->params_len,
		    evt_transaction->params))
		जाओ nla_put_failure;

	/* evt_transaction is no more used */
	devm_kमुक्त(&dev->dev, evt_transaction);

	genlmsg_end(msg, hdr);

	genlmsg_multicast(&nfc_genl_family, msg, 0, 0, GFP_KERNEL);

	वापस 0;

nla_put_failure:
मुक्त_msg:
	/* evt_transaction is no more used */
	devm_kमुक्त(&dev->dev, evt_transaction);
	nlmsg_मुक्त(msg);
	वापस -EMSGSIZE;
पूर्ण

पूर्णांक nfc_genl_se_connectivity(काष्ठा nfc_dev *dev, u8 se_idx)
अणु
	काष्ठा nfc_se *se;
	काष्ठा sk_buff *msg;
	व्योम *hdr;

	msg = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	अगर (!msg)
		वापस -ENOMEM;

	hdr = genlmsg_put(msg, 0, 0, &nfc_genl_family, 0,
			  NFC_EVENT_SE_CONNECTIVITY);
	अगर (!hdr)
		जाओ मुक्त_msg;

	se = nfc_find_se(dev, se_idx);
	अगर (!se)
		जाओ मुक्त_msg;

	अगर (nla_put_u32(msg, NFC_ATTR_DEVICE_INDEX, dev->idx) ||
	    nla_put_u32(msg, NFC_ATTR_SE_INDEX, se_idx) ||
	    nla_put_u8(msg, NFC_ATTR_SE_TYPE, se->type))
		जाओ nla_put_failure;

	genlmsg_end(msg, hdr);

	genlmsg_multicast(&nfc_genl_family, msg, 0, 0, GFP_KERNEL);

	वापस 0;

nla_put_failure:
मुक्त_msg:
	nlmsg_मुक्त(msg);
	वापस -EMSGSIZE;
पूर्ण

अटल पूर्णांक nfc_genl_send_device(काष्ठा sk_buff *msg, काष्ठा nfc_dev *dev,
				u32 portid, u32 seq,
				काष्ठा netlink_callback *cb,
				पूर्णांक flags)
अणु
	व्योम *hdr;

	hdr = genlmsg_put(msg, portid, seq, &nfc_genl_family, flags,
			  NFC_CMD_GET_DEVICE);
	अगर (!hdr)
		वापस -EMSGSIZE;

	अगर (cb)
		genl_dump_check_consistent(cb, hdr);

	अगर (nfc_genl_setup_device_added(dev, msg))
		जाओ nla_put_failure;

	genlmsg_end(msg, hdr);
	वापस 0;

nla_put_failure:
	genlmsg_cancel(msg, hdr);
	वापस -EMSGSIZE;
पूर्ण

अटल पूर्णांक nfc_genl_dump_devices(काष्ठा sk_buff *skb,
				 काष्ठा netlink_callback *cb)
अणु
	काष्ठा class_dev_iter *iter = (काष्ठा class_dev_iter *) cb->args[0];
	काष्ठा nfc_dev *dev = (काष्ठा nfc_dev *) cb->args[1];
	bool first_call = false;

	अगर (!iter) अणु
		first_call = true;
		iter = kदो_स्मृति(माप(काष्ठा class_dev_iter), GFP_KERNEL);
		अगर (!iter)
			वापस -ENOMEM;
		cb->args[0] = (दीर्घ) iter;
	पूर्ण

	mutex_lock(&nfc_devlist_mutex);

	cb->seq = nfc_devlist_generation;

	अगर (first_call) अणु
		nfc_device_iter_init(iter);
		dev = nfc_device_iter_next(iter);
	पूर्ण

	जबतक (dev) अणु
		पूर्णांक rc;

		rc = nfc_genl_send_device(skb, dev, NETLINK_CB(cb->skb).portid,
					  cb->nlh->nlmsg_seq, cb, NLM_F_MULTI);
		अगर (rc < 0)
			अवरोध;

		dev = nfc_device_iter_next(iter);
	पूर्ण

	mutex_unlock(&nfc_devlist_mutex);

	cb->args[1] = (दीर्घ) dev;

	वापस skb->len;
पूर्ण

अटल पूर्णांक nfc_genl_dump_devices_करोne(काष्ठा netlink_callback *cb)
अणु
	काष्ठा class_dev_iter *iter = (काष्ठा class_dev_iter *) cb->args[0];

	nfc_device_iter_निकास(iter);
	kमुक्त(iter);

	वापस 0;
पूर्ण

पूर्णांक nfc_genl_dep_link_up_event(काष्ठा nfc_dev *dev, u32 target_idx,
			       u8 comm_mode, u8 rf_mode)
अणु
	काष्ठा sk_buff *msg;
	व्योम *hdr;

	pr_debug("DEP link is up\n");

	msg = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_ATOMIC);
	अगर (!msg)
		वापस -ENOMEM;

	hdr = genlmsg_put(msg, 0, 0, &nfc_genl_family, 0, NFC_CMD_DEP_LINK_UP);
	अगर (!hdr)
		जाओ मुक्त_msg;

	अगर (nla_put_u32(msg, NFC_ATTR_DEVICE_INDEX, dev->idx))
		जाओ nla_put_failure;
	अगर (rf_mode == NFC_RF_INITIATOR &&
	    nla_put_u32(msg, NFC_ATTR_TARGET_INDEX, target_idx))
		जाओ nla_put_failure;
	अगर (nla_put_u8(msg, NFC_ATTR_COMM_MODE, comm_mode) ||
	    nla_put_u8(msg, NFC_ATTR_RF_MODE, rf_mode))
		जाओ nla_put_failure;

	genlmsg_end(msg, hdr);

	dev->dep_link_up = true;

	genlmsg_multicast(&nfc_genl_family, msg, 0, 0, GFP_ATOMIC);

	वापस 0;

nla_put_failure:
मुक्त_msg:
	nlmsg_मुक्त(msg);
	वापस -EMSGSIZE;
पूर्ण

पूर्णांक nfc_genl_dep_link_करोwn_event(काष्ठा nfc_dev *dev)
अणु
	काष्ठा sk_buff *msg;
	व्योम *hdr;

	pr_debug("DEP link is down\n");

	msg = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_ATOMIC);
	अगर (!msg)
		वापस -ENOMEM;

	hdr = genlmsg_put(msg, 0, 0, &nfc_genl_family, 0,
			  NFC_CMD_DEP_LINK_DOWN);
	अगर (!hdr)
		जाओ मुक्त_msg;

	अगर (nla_put_u32(msg, NFC_ATTR_DEVICE_INDEX, dev->idx))
		जाओ nla_put_failure;

	genlmsg_end(msg, hdr);

	genlmsg_multicast(&nfc_genl_family, msg, 0, 0, GFP_ATOMIC);

	वापस 0;

nla_put_failure:
मुक्त_msg:
	nlmsg_मुक्त(msg);
	वापस -EMSGSIZE;
पूर्ण

अटल पूर्णांक nfc_genl_get_device(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा sk_buff *msg;
	काष्ठा nfc_dev *dev;
	u32 idx;
	पूर्णांक rc = -ENOBUFS;

	अगर (!info->attrs[NFC_ATTR_DEVICE_INDEX])
		वापस -EINVAL;

	idx = nla_get_u32(info->attrs[NFC_ATTR_DEVICE_INDEX]);

	dev = nfc_get_device(idx);
	अगर (!dev)
		वापस -ENODEV;

	msg = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	अगर (!msg) अणु
		rc = -ENOMEM;
		जाओ out_putdev;
	पूर्ण

	rc = nfc_genl_send_device(msg, dev, info->snd_portid, info->snd_seq,
				  शून्य, 0);
	अगर (rc < 0)
		जाओ out_मुक्त;

	nfc_put_device(dev);

	वापस genlmsg_reply(msg, info);

out_मुक्त:
	nlmsg_मुक्त(msg);
out_putdev:
	nfc_put_device(dev);
	वापस rc;
पूर्ण

अटल पूर्णांक nfc_genl_dev_up(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा nfc_dev *dev;
	पूर्णांक rc;
	u32 idx;

	अगर (!info->attrs[NFC_ATTR_DEVICE_INDEX])
		वापस -EINVAL;

	idx = nla_get_u32(info->attrs[NFC_ATTR_DEVICE_INDEX]);

	dev = nfc_get_device(idx);
	अगर (!dev)
		वापस -ENODEV;

	rc = nfc_dev_up(dev);

	nfc_put_device(dev);
	वापस rc;
पूर्ण

अटल पूर्णांक nfc_genl_dev_करोwn(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा nfc_dev *dev;
	पूर्णांक rc;
	u32 idx;

	अगर (!info->attrs[NFC_ATTR_DEVICE_INDEX])
		वापस -EINVAL;

	idx = nla_get_u32(info->attrs[NFC_ATTR_DEVICE_INDEX]);

	dev = nfc_get_device(idx);
	अगर (!dev)
		वापस -ENODEV;

	rc = nfc_dev_करोwn(dev);

	nfc_put_device(dev);
	वापस rc;
पूर्ण

अटल पूर्णांक nfc_genl_start_poll(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा nfc_dev *dev;
	पूर्णांक rc;
	u32 idx;
	u32 im_protocols = 0, पंचांग_protocols = 0;

	pr_debug("Poll start\n");

	अगर (!info->attrs[NFC_ATTR_DEVICE_INDEX] ||
	    ((!info->attrs[NFC_ATTR_IM_PROTOCOLS] &&
	      !info->attrs[NFC_ATTR_PROTOCOLS]) &&
	      !info->attrs[NFC_ATTR_TM_PROTOCOLS]))
		वापस -EINVAL;

	idx = nla_get_u32(info->attrs[NFC_ATTR_DEVICE_INDEX]);

	अगर (info->attrs[NFC_ATTR_TM_PROTOCOLS])
		पंचांग_protocols = nla_get_u32(info->attrs[NFC_ATTR_TM_PROTOCOLS]);

	अगर (info->attrs[NFC_ATTR_IM_PROTOCOLS])
		im_protocols = nla_get_u32(info->attrs[NFC_ATTR_IM_PROTOCOLS]);
	अन्यथा अगर (info->attrs[NFC_ATTR_PROTOCOLS])
		im_protocols = nla_get_u32(info->attrs[NFC_ATTR_PROTOCOLS]);

	dev = nfc_get_device(idx);
	अगर (!dev)
		वापस -ENODEV;

	mutex_lock(&dev->genl_data.genl_data_mutex);

	rc = nfc_start_poll(dev, im_protocols, पंचांग_protocols);
	अगर (!rc)
		dev->genl_data.poll_req_portid = info->snd_portid;

	mutex_unlock(&dev->genl_data.genl_data_mutex);

	nfc_put_device(dev);
	वापस rc;
पूर्ण

अटल पूर्णांक nfc_genl_stop_poll(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा nfc_dev *dev;
	पूर्णांक rc;
	u32 idx;

	अगर (!info->attrs[NFC_ATTR_DEVICE_INDEX])
		वापस -EINVAL;

	idx = nla_get_u32(info->attrs[NFC_ATTR_DEVICE_INDEX]);

	dev = nfc_get_device(idx);
	अगर (!dev)
		वापस -ENODEV;

	device_lock(&dev->dev);

	अगर (!dev->polling) अणु
		device_unlock(&dev->dev);
		nfc_put_device(dev);
		वापस -EINVAL;
	पूर्ण

	device_unlock(&dev->dev);

	mutex_lock(&dev->genl_data.genl_data_mutex);

	अगर (dev->genl_data.poll_req_portid != info->snd_portid) अणु
		rc = -EBUSY;
		जाओ out;
	पूर्ण

	rc = nfc_stop_poll(dev);
	dev->genl_data.poll_req_portid = 0;

out:
	mutex_unlock(&dev->genl_data.genl_data_mutex);
	nfc_put_device(dev);
	वापस rc;
पूर्ण

अटल पूर्णांक nfc_genl_activate_target(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा nfc_dev *dev;
	u32 device_idx, target_idx, protocol;
	पूर्णांक rc;

	अगर (!info->attrs[NFC_ATTR_DEVICE_INDEX] ||
	    !info->attrs[NFC_ATTR_TARGET_INDEX] ||
	    !info->attrs[NFC_ATTR_PROTOCOLS])
		वापस -EINVAL;

	device_idx = nla_get_u32(info->attrs[NFC_ATTR_DEVICE_INDEX]);

	dev = nfc_get_device(device_idx);
	अगर (!dev)
		वापस -ENODEV;

	target_idx = nla_get_u32(info->attrs[NFC_ATTR_TARGET_INDEX]);
	protocol = nla_get_u32(info->attrs[NFC_ATTR_PROTOCOLS]);

	nfc_deactivate_target(dev, target_idx, NFC_TARGET_MODE_SLEEP);
	rc = nfc_activate_target(dev, target_idx, protocol);

	nfc_put_device(dev);
	वापस rc;
पूर्ण

अटल पूर्णांक nfc_genl_deactivate_target(काष्ठा sk_buff *skb,
				      काष्ठा genl_info *info)
अणु
	काष्ठा nfc_dev *dev;
	u32 device_idx, target_idx;
	पूर्णांक rc;

	अगर (!info->attrs[NFC_ATTR_DEVICE_INDEX] ||
	    !info->attrs[NFC_ATTR_TARGET_INDEX])
		वापस -EINVAL;

	device_idx = nla_get_u32(info->attrs[NFC_ATTR_DEVICE_INDEX]);

	dev = nfc_get_device(device_idx);
	अगर (!dev)
		वापस -ENODEV;

	target_idx = nla_get_u32(info->attrs[NFC_ATTR_TARGET_INDEX]);

	rc = nfc_deactivate_target(dev, target_idx, NFC_TARGET_MODE_SLEEP);

	nfc_put_device(dev);
	वापस rc;
पूर्ण

अटल पूर्णांक nfc_genl_dep_link_up(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा nfc_dev *dev;
	पूर्णांक rc, tgt_idx;
	u32 idx;
	u8 comm;

	pr_debug("DEP link up\n");

	अगर (!info->attrs[NFC_ATTR_DEVICE_INDEX] ||
	    !info->attrs[NFC_ATTR_COMM_MODE])
		वापस -EINVAL;

	idx = nla_get_u32(info->attrs[NFC_ATTR_DEVICE_INDEX]);
	अगर (!info->attrs[NFC_ATTR_TARGET_INDEX])
		tgt_idx = NFC_TARGET_IDX_ANY;
	अन्यथा
		tgt_idx = nla_get_u32(info->attrs[NFC_ATTR_TARGET_INDEX]);

	comm = nla_get_u8(info->attrs[NFC_ATTR_COMM_MODE]);

	अगर (comm != NFC_COMM_ACTIVE && comm != NFC_COMM_PASSIVE)
		वापस -EINVAL;

	dev = nfc_get_device(idx);
	अगर (!dev)
		वापस -ENODEV;

	rc = nfc_dep_link_up(dev, tgt_idx, comm);

	nfc_put_device(dev);

	वापस rc;
पूर्ण

अटल पूर्णांक nfc_genl_dep_link_करोwn(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा nfc_dev *dev;
	पूर्णांक rc;
	u32 idx;

	अगर (!info->attrs[NFC_ATTR_DEVICE_INDEX] ||
	    !info->attrs[NFC_ATTR_TARGET_INDEX])
		वापस -EINVAL;

	idx = nla_get_u32(info->attrs[NFC_ATTR_DEVICE_INDEX]);

	dev = nfc_get_device(idx);
	अगर (!dev)
		वापस -ENODEV;

	rc = nfc_dep_link_करोwn(dev);

	nfc_put_device(dev);
	वापस rc;
पूर्ण

अटल पूर्णांक nfc_genl_send_params(काष्ठा sk_buff *msg,
				काष्ठा nfc_llcp_local *local,
				u32 portid, u32 seq)
अणु
	व्योम *hdr;

	hdr = genlmsg_put(msg, portid, seq, &nfc_genl_family, 0,
			  NFC_CMD_LLC_GET_PARAMS);
	अगर (!hdr)
		वापस -EMSGSIZE;

	अगर (nla_put_u32(msg, NFC_ATTR_DEVICE_INDEX, local->dev->idx) ||
	    nla_put_u8(msg, NFC_ATTR_LLC_PARAM_LTO, local->lto) ||
	    nla_put_u8(msg, NFC_ATTR_LLC_PARAM_RW, local->rw) ||
	    nla_put_u16(msg, NFC_ATTR_LLC_PARAM_MIUX, be16_to_cpu(local->miux)))
		जाओ nla_put_failure;

	genlmsg_end(msg, hdr);
	वापस 0;

nla_put_failure:
	genlmsg_cancel(msg, hdr);
	वापस -EMSGSIZE;
पूर्ण

अटल पूर्णांक nfc_genl_llc_get_params(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा nfc_dev *dev;
	काष्ठा nfc_llcp_local *local;
	पूर्णांक rc = 0;
	काष्ठा sk_buff *msg = शून्य;
	u32 idx;

	अगर (!info->attrs[NFC_ATTR_DEVICE_INDEX] ||
	    !info->attrs[NFC_ATTR_FIRMWARE_NAME])
		वापस -EINVAL;

	idx = nla_get_u32(info->attrs[NFC_ATTR_DEVICE_INDEX]);

	dev = nfc_get_device(idx);
	अगर (!dev)
		वापस -ENODEV;

	device_lock(&dev->dev);

	local = nfc_llcp_find_local(dev);
	अगर (!local) अणु
		rc = -ENODEV;
		जाओ निकास;
	पूर्ण

	msg = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	अगर (!msg) अणु
		rc = -ENOMEM;
		जाओ निकास;
	पूर्ण

	rc = nfc_genl_send_params(msg, local, info->snd_portid, info->snd_seq);

निकास:
	device_unlock(&dev->dev);

	nfc_put_device(dev);

	अगर (rc < 0) अणु
		अगर (msg)
			nlmsg_मुक्त(msg);

		वापस rc;
	पूर्ण

	वापस genlmsg_reply(msg, info);
पूर्ण

अटल पूर्णांक nfc_genl_llc_set_params(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा nfc_dev *dev;
	काष्ठा nfc_llcp_local *local;
	u8 rw = 0;
	u16 miux = 0;
	u32 idx;
	पूर्णांक rc = 0;

	अगर (!info->attrs[NFC_ATTR_DEVICE_INDEX] ||
	    (!info->attrs[NFC_ATTR_LLC_PARAM_LTO] &&
	     !info->attrs[NFC_ATTR_LLC_PARAM_RW] &&
	     !info->attrs[NFC_ATTR_LLC_PARAM_MIUX]))
		वापस -EINVAL;

	अगर (info->attrs[NFC_ATTR_LLC_PARAM_RW]) अणु
		rw = nla_get_u8(info->attrs[NFC_ATTR_LLC_PARAM_RW]);

		अगर (rw > LLCP_MAX_RW)
			वापस -EINVAL;
	पूर्ण

	अगर (info->attrs[NFC_ATTR_LLC_PARAM_MIUX]) अणु
		miux = nla_get_u16(info->attrs[NFC_ATTR_LLC_PARAM_MIUX]);

		अगर (miux > LLCP_MAX_MIUX)
			वापस -EINVAL;
	पूर्ण

	idx = nla_get_u32(info->attrs[NFC_ATTR_DEVICE_INDEX]);

	dev = nfc_get_device(idx);
	अगर (!dev)
		वापस -ENODEV;

	device_lock(&dev->dev);

	local = nfc_llcp_find_local(dev);
	अगर (!local) अणु
		rc = -ENODEV;
		जाओ निकास;
	पूर्ण

	अगर (info->attrs[NFC_ATTR_LLC_PARAM_LTO]) अणु
		अगर (dev->dep_link_up) अणु
			rc = -EINPROGRESS;
			जाओ निकास;
		पूर्ण

		local->lto = nla_get_u8(info->attrs[NFC_ATTR_LLC_PARAM_LTO]);
	पूर्ण

	अगर (info->attrs[NFC_ATTR_LLC_PARAM_RW])
		local->rw = rw;

	अगर (info->attrs[NFC_ATTR_LLC_PARAM_MIUX])
		local->miux = cpu_to_be16(miux);

निकास:
	device_unlock(&dev->dev);

	nfc_put_device(dev);

	वापस rc;
पूर्ण

अटल पूर्णांक nfc_genl_llc_sdreq(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा nfc_dev *dev;
	काष्ठा nfc_llcp_local *local;
	काष्ठा nlattr *attr, *sdp_attrs[NFC_SDP_ATTR_MAX+1];
	u32 idx;
	u8 tid;
	अक्षर *uri;
	पूर्णांक rc = 0, rem;
	माप_प्रकार uri_len, tlvs_len;
	काष्ठा hlist_head sdreq_list;
	काष्ठा nfc_llcp_sdp_tlv *sdreq;

	अगर (!info->attrs[NFC_ATTR_DEVICE_INDEX] ||
	    !info->attrs[NFC_ATTR_LLC_SDP])
		वापस -EINVAL;

	idx = nla_get_u32(info->attrs[NFC_ATTR_DEVICE_INDEX]);

	dev = nfc_get_device(idx);
	अगर (!dev)
		वापस -ENODEV;

	device_lock(&dev->dev);

	अगर (dev->dep_link_up == false) अणु
		rc = -ENOLINK;
		जाओ निकास;
	पूर्ण

	local = nfc_llcp_find_local(dev);
	अगर (!local) अणु
		rc = -ENODEV;
		जाओ निकास;
	पूर्ण

	INIT_HLIST_HEAD(&sdreq_list);

	tlvs_len = 0;

	nla_क्रम_each_nested(attr, info->attrs[NFC_ATTR_LLC_SDP], rem) अणु
		rc = nla_parse_nested_deprecated(sdp_attrs, NFC_SDP_ATTR_MAX,
						 attr, nfc_sdp_genl_policy,
						 info->extack);

		अगर (rc != 0) अणु
			rc = -EINVAL;
			जाओ निकास;
		पूर्ण

		अगर (!sdp_attrs[NFC_SDP_ATTR_URI])
			जारी;

		uri_len = nla_len(sdp_attrs[NFC_SDP_ATTR_URI]);
		अगर (uri_len == 0)
			जारी;

		uri = nla_data(sdp_attrs[NFC_SDP_ATTR_URI]);
		अगर (uri == शून्य || *uri == 0)
			जारी;

		tid = local->sdreq_next_tid++;

		sdreq = nfc_llcp_build_sdreq_tlv(tid, uri, uri_len);
		अगर (sdreq == शून्य) अणु
			rc = -ENOMEM;
			जाओ निकास;
		पूर्ण

		tlvs_len += sdreq->tlv_len;

		hlist_add_head(&sdreq->node, &sdreq_list);
	पूर्ण

	अगर (hlist_empty(&sdreq_list)) अणु
		rc = -EINVAL;
		जाओ निकास;
	पूर्ण

	rc = nfc_llcp_send_snl_sdreq(local, &sdreq_list, tlvs_len);
निकास:
	device_unlock(&dev->dev);

	nfc_put_device(dev);

	वापस rc;
पूर्ण

अटल पूर्णांक nfc_genl_fw_करोwnload(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा nfc_dev *dev;
	पूर्णांक rc;
	u32 idx;
	अक्षर firmware_name[NFC_FIRMWARE_NAME_MAXSIZE + 1];

	अगर (!info->attrs[NFC_ATTR_DEVICE_INDEX] || !info->attrs[NFC_ATTR_FIRMWARE_NAME])
		वापस -EINVAL;

	idx = nla_get_u32(info->attrs[NFC_ATTR_DEVICE_INDEX]);

	dev = nfc_get_device(idx);
	अगर (!dev)
		वापस -ENODEV;

	nla_strscpy(firmware_name, info->attrs[NFC_ATTR_FIRMWARE_NAME],
		    माप(firmware_name));

	rc = nfc_fw_करोwnload(dev, firmware_name);

	nfc_put_device(dev);
	वापस rc;
पूर्ण

पूर्णांक nfc_genl_fw_करोwnload_करोne(काष्ठा nfc_dev *dev, स्थिर अक्षर *firmware_name,
			      u32 result)
अणु
	काष्ठा sk_buff *msg;
	व्योम *hdr;

	msg = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	अगर (!msg)
		वापस -ENOMEM;

	hdr = genlmsg_put(msg, 0, 0, &nfc_genl_family, 0,
			  NFC_CMD_FW_DOWNLOAD);
	अगर (!hdr)
		जाओ मुक्त_msg;

	अगर (nla_put_string(msg, NFC_ATTR_FIRMWARE_NAME, firmware_name) ||
	    nla_put_u32(msg, NFC_ATTR_FIRMWARE_DOWNLOAD_STATUS, result) ||
	    nla_put_u32(msg, NFC_ATTR_DEVICE_INDEX, dev->idx))
		जाओ nla_put_failure;

	genlmsg_end(msg, hdr);

	genlmsg_multicast(&nfc_genl_family, msg, 0, 0, GFP_KERNEL);

	वापस 0;

nla_put_failure:
मुक्त_msg:
	nlmsg_मुक्त(msg);
	वापस -EMSGSIZE;
पूर्ण

अटल पूर्णांक nfc_genl_enable_se(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा nfc_dev *dev;
	पूर्णांक rc;
	u32 idx, se_idx;

	अगर (!info->attrs[NFC_ATTR_DEVICE_INDEX] ||
	    !info->attrs[NFC_ATTR_SE_INDEX])
		वापस -EINVAL;

	idx = nla_get_u32(info->attrs[NFC_ATTR_DEVICE_INDEX]);
	se_idx = nla_get_u32(info->attrs[NFC_ATTR_SE_INDEX]);

	dev = nfc_get_device(idx);
	अगर (!dev)
		वापस -ENODEV;

	rc = nfc_enable_se(dev, se_idx);

	nfc_put_device(dev);
	वापस rc;
पूर्ण

अटल पूर्णांक nfc_genl_disable_se(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा nfc_dev *dev;
	पूर्णांक rc;
	u32 idx, se_idx;

	अगर (!info->attrs[NFC_ATTR_DEVICE_INDEX] ||
	    !info->attrs[NFC_ATTR_SE_INDEX])
		वापस -EINVAL;

	idx = nla_get_u32(info->attrs[NFC_ATTR_DEVICE_INDEX]);
	se_idx = nla_get_u32(info->attrs[NFC_ATTR_SE_INDEX]);

	dev = nfc_get_device(idx);
	अगर (!dev)
		वापस -ENODEV;

	rc = nfc_disable_se(dev, se_idx);

	nfc_put_device(dev);
	वापस rc;
पूर्ण

अटल पूर्णांक nfc_genl_send_se(काष्ठा sk_buff *msg, काष्ठा nfc_dev *dev,
				u32 portid, u32 seq,
				काष्ठा netlink_callback *cb,
				पूर्णांक flags)
अणु
	व्योम *hdr;
	काष्ठा nfc_se *se, *n;

	list_क्रम_each_entry_safe(se, n, &dev->secure_elements, list) अणु
		hdr = genlmsg_put(msg, portid, seq, &nfc_genl_family, flags,
				  NFC_CMD_GET_SE);
		अगर (!hdr)
			जाओ nla_put_failure;

		अगर (cb)
			genl_dump_check_consistent(cb, hdr);

		अगर (nla_put_u32(msg, NFC_ATTR_DEVICE_INDEX, dev->idx) ||
		    nla_put_u32(msg, NFC_ATTR_SE_INDEX, se->idx) ||
		    nla_put_u8(msg, NFC_ATTR_SE_TYPE, se->type))
			जाओ nla_put_failure;

		genlmsg_end(msg, hdr);
	पूर्ण

	वापस 0;

nla_put_failure:
	genlmsg_cancel(msg, hdr);
	वापस -EMSGSIZE;
पूर्ण

अटल पूर्णांक nfc_genl_dump_ses(काष्ठा sk_buff *skb,
				 काष्ठा netlink_callback *cb)
अणु
	काष्ठा class_dev_iter *iter = (काष्ठा class_dev_iter *) cb->args[0];
	काष्ठा nfc_dev *dev = (काष्ठा nfc_dev *) cb->args[1];
	bool first_call = false;

	अगर (!iter) अणु
		first_call = true;
		iter = kदो_स्मृति(माप(काष्ठा class_dev_iter), GFP_KERNEL);
		अगर (!iter)
			वापस -ENOMEM;
		cb->args[0] = (दीर्घ) iter;
	पूर्ण

	mutex_lock(&nfc_devlist_mutex);

	cb->seq = nfc_devlist_generation;

	अगर (first_call) अणु
		nfc_device_iter_init(iter);
		dev = nfc_device_iter_next(iter);
	पूर्ण

	जबतक (dev) अणु
		पूर्णांक rc;

		rc = nfc_genl_send_se(skb, dev, NETLINK_CB(cb->skb).portid,
					  cb->nlh->nlmsg_seq, cb, NLM_F_MULTI);
		अगर (rc < 0)
			अवरोध;

		dev = nfc_device_iter_next(iter);
	पूर्ण

	mutex_unlock(&nfc_devlist_mutex);

	cb->args[1] = (दीर्घ) dev;

	वापस skb->len;
पूर्ण

अटल पूर्णांक nfc_genl_dump_ses_करोne(काष्ठा netlink_callback *cb)
अणु
	काष्ठा class_dev_iter *iter = (काष्ठा class_dev_iter *) cb->args[0];

	nfc_device_iter_निकास(iter);
	kमुक्त(iter);

	वापस 0;
पूर्ण

अटल पूर्णांक nfc_se_io(काष्ठा nfc_dev *dev, u32 se_idx,
		     u8 *apdu, माप_प्रकार apdu_length,
		     se_io_cb_t cb, व्योम *cb_context)
अणु
	काष्ठा nfc_se *se;
	पूर्णांक rc;

	pr_debug("%s se index %d\n", dev_name(&dev->dev), se_idx);

	device_lock(&dev->dev);

	अगर (!device_is_रेजिस्टरed(&dev->dev)) अणु
		rc = -ENODEV;
		जाओ error;
	पूर्ण

	अगर (!dev->dev_up) अणु
		rc = -ENODEV;
		जाओ error;
	पूर्ण

	अगर (!dev->ops->se_io) अणु
		rc = -EOPNOTSUPP;
		जाओ error;
	पूर्ण

	se = nfc_find_se(dev, se_idx);
	अगर (!se) अणु
		rc = -EINVAL;
		जाओ error;
	पूर्ण

	अगर (se->state != NFC_SE_ENABLED) अणु
		rc = -ENODEV;
		जाओ error;
	पूर्ण

	rc = dev->ops->se_io(dev, se_idx, apdu,
			apdu_length, cb, cb_context);

error:
	device_unlock(&dev->dev);
	वापस rc;
पूर्ण

काष्ठा se_io_ctx अणु
	u32 dev_idx;
	u32 se_idx;
पूर्ण;

अटल व्योम se_io_cb(व्योम *context, u8 *apdu, माप_प्रकार apdu_len, पूर्णांक err)
अणु
	काष्ठा se_io_ctx *ctx = context;
	काष्ठा sk_buff *msg;
	व्योम *hdr;

	msg = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	अगर (!msg) अणु
		kमुक्त(ctx);
		वापस;
	पूर्ण

	hdr = genlmsg_put(msg, 0, 0, &nfc_genl_family, 0,
			  NFC_CMD_SE_IO);
	अगर (!hdr)
		जाओ मुक्त_msg;

	अगर (nla_put_u32(msg, NFC_ATTR_DEVICE_INDEX, ctx->dev_idx) ||
	    nla_put_u32(msg, NFC_ATTR_SE_INDEX, ctx->se_idx) ||
	    nla_put(msg, NFC_ATTR_SE_APDU, apdu_len, apdu))
		जाओ nla_put_failure;

	genlmsg_end(msg, hdr);

	genlmsg_multicast(&nfc_genl_family, msg, 0, 0, GFP_KERNEL);

	kमुक्त(ctx);

	वापस;

nla_put_failure:
मुक्त_msg:
	nlmsg_मुक्त(msg);
	kमुक्त(ctx);

	वापस;
पूर्ण

अटल पूर्णांक nfc_genl_se_io(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा nfc_dev *dev;
	काष्ठा se_io_ctx *ctx;
	u32 dev_idx, se_idx;
	u8 *apdu;
	माप_प्रकार apdu_len;

	अगर (!info->attrs[NFC_ATTR_DEVICE_INDEX] ||
	    !info->attrs[NFC_ATTR_SE_INDEX] ||
	    !info->attrs[NFC_ATTR_SE_APDU])
		वापस -EINVAL;

	dev_idx = nla_get_u32(info->attrs[NFC_ATTR_DEVICE_INDEX]);
	se_idx = nla_get_u32(info->attrs[NFC_ATTR_SE_INDEX]);

	dev = nfc_get_device(dev_idx);
	अगर (!dev)
		वापस -ENODEV;

	अगर (!dev->ops || !dev->ops->se_io)
		वापस -ENOTSUPP;

	apdu_len = nla_len(info->attrs[NFC_ATTR_SE_APDU]);
	अगर (apdu_len == 0)
		वापस -EINVAL;

	apdu = nla_data(info->attrs[NFC_ATTR_SE_APDU]);
	अगर (!apdu)
		वापस -EINVAL;

	ctx = kzalloc(माप(काष्ठा se_io_ctx), GFP_KERNEL);
	अगर (!ctx)
		वापस -ENOMEM;

	ctx->dev_idx = dev_idx;
	ctx->se_idx = se_idx;

	वापस nfc_se_io(dev, se_idx, apdu, apdu_len, se_io_cb, ctx);
पूर्ण

अटल पूर्णांक nfc_genl_venकरोr_cmd(काष्ठा sk_buff *skb,
			       काष्ठा genl_info *info)
अणु
	काष्ठा nfc_dev *dev;
	काष्ठा nfc_venकरोr_cmd *cmd;
	u32 dev_idx, vid, subcmd;
	u8 *data;
	माप_प्रकार data_len;
	पूर्णांक i, err;

	अगर (!info->attrs[NFC_ATTR_DEVICE_INDEX] ||
	    !info->attrs[NFC_ATTR_VENDOR_ID] ||
	    !info->attrs[NFC_ATTR_VENDOR_SUBCMD])
		वापस -EINVAL;

	dev_idx = nla_get_u32(info->attrs[NFC_ATTR_DEVICE_INDEX]);
	vid = nla_get_u32(info->attrs[NFC_ATTR_VENDOR_ID]);
	subcmd = nla_get_u32(info->attrs[NFC_ATTR_VENDOR_SUBCMD]);

	dev = nfc_get_device(dev_idx);
	अगर (!dev || !dev->venकरोr_cmds || !dev->n_venकरोr_cmds)
		वापस -ENODEV;

	अगर (info->attrs[NFC_ATTR_VENDOR_DATA]) अणु
		data = nla_data(info->attrs[NFC_ATTR_VENDOR_DATA]);
		data_len = nla_len(info->attrs[NFC_ATTR_VENDOR_DATA]);
		अगर (data_len == 0)
			वापस -EINVAL;
	पूर्ण अन्यथा अणु
		data = शून्य;
		data_len = 0;
	पूर्ण

	क्रम (i = 0; i < dev->n_venकरोr_cmds; i++) अणु
		cmd = &dev->venकरोr_cmds[i];

		अगर (cmd->venकरोr_id != vid || cmd->subcmd != subcmd)
			जारी;

		dev->cur_cmd_info = info;
		err = cmd->करोit(dev, data, data_len);
		dev->cur_cmd_info = शून्य;
		वापस err;
	पूर्ण

	वापस -EOPNOTSUPP;
पूर्ण

/* message building helper */
अटल अंतरभूत व्योम *nfc_hdr_put(काष्ठा sk_buff *skb, u32 portid, u32 seq,
				पूर्णांक flags, u8 cmd)
अणु
	/* since there is no निजी header just add the generic one */
	वापस genlmsg_put(skb, portid, seq, &nfc_genl_family, flags, cmd);
पूर्ण

अटल काष्ठा sk_buff *
__nfc_alloc_venकरोr_cmd_skb(काष्ठा nfc_dev *dev, पूर्णांक approxlen,
			   u32 portid, u32 seq,
			   क्रमागत nfc_attrs attr,
			   u32 oui, u32 subcmd, gfp_t gfp)
अणु
	काष्ठा sk_buff *skb;
	व्योम *hdr;

	skb = nlmsg_new(approxlen + 100, gfp);
	अगर (!skb)
		वापस शून्य;

	hdr = nfc_hdr_put(skb, portid, seq, 0, NFC_CMD_VENDOR);
	अगर (!hdr) अणु
		kमुक्त_skb(skb);
		वापस शून्य;
	पूर्ण

	अगर (nla_put_u32(skb, NFC_ATTR_DEVICE_INDEX, dev->idx))
		जाओ nla_put_failure;
	अगर (nla_put_u32(skb, NFC_ATTR_VENDOR_ID, oui))
		जाओ nla_put_failure;
	अगर (nla_put_u32(skb, NFC_ATTR_VENDOR_SUBCMD, subcmd))
		जाओ nla_put_failure;

	((व्योम **)skb->cb)[0] = dev;
	((व्योम **)skb->cb)[1] = hdr;

	वापस skb;

nla_put_failure:
	kमुक्त_skb(skb);
	वापस शून्य;
पूर्ण

काष्ठा sk_buff *__nfc_alloc_venकरोr_cmd_reply_skb(काष्ठा nfc_dev *dev,
						 क्रमागत nfc_attrs attr,
						 u32 oui, u32 subcmd,
						 पूर्णांक approxlen)
अणु
	अगर (WARN_ON(!dev->cur_cmd_info))
		वापस शून्य;

	वापस __nfc_alloc_venकरोr_cmd_skb(dev, approxlen,
					  dev->cur_cmd_info->snd_portid,
					  dev->cur_cmd_info->snd_seq, attr,
					  oui, subcmd, GFP_KERNEL);
पूर्ण
EXPORT_SYMBOL(__nfc_alloc_venकरोr_cmd_reply_skb);

पूर्णांक nfc_venकरोr_cmd_reply(काष्ठा sk_buff *skb)
अणु
	काष्ठा nfc_dev *dev = ((व्योम **)skb->cb)[0];
	व्योम *hdr = ((व्योम **)skb->cb)[1];

	/* clear CB data क्रम netlink core to own from now on */
	स_रखो(skb->cb, 0, माप(skb->cb));

	अगर (WARN_ON(!dev->cur_cmd_info)) अणु
		kमुक्त_skb(skb);
		वापस -EINVAL;
	पूर्ण

	genlmsg_end(skb, hdr);
	वापस genlmsg_reply(skb, dev->cur_cmd_info);
पूर्ण
EXPORT_SYMBOL(nfc_venकरोr_cmd_reply);

अटल स्थिर काष्ठा genl_ops nfc_genl_ops[] = अणु
	अणु
		.cmd = NFC_CMD_GET_DEVICE,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = nfc_genl_get_device,
		.dumpit = nfc_genl_dump_devices,
		.करोne = nfc_genl_dump_devices_करोne,
	पूर्ण,
	अणु
		.cmd = NFC_CMD_DEV_UP,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = nfc_genl_dev_up,
	पूर्ण,
	अणु
		.cmd = NFC_CMD_DEV_DOWN,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = nfc_genl_dev_करोwn,
	पूर्ण,
	अणु
		.cmd = NFC_CMD_START_POLL,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = nfc_genl_start_poll,
	पूर्ण,
	अणु
		.cmd = NFC_CMD_STOP_POLL,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = nfc_genl_stop_poll,
	पूर्ण,
	अणु
		.cmd = NFC_CMD_DEP_LINK_UP,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = nfc_genl_dep_link_up,
	पूर्ण,
	अणु
		.cmd = NFC_CMD_DEP_LINK_DOWN,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = nfc_genl_dep_link_करोwn,
	पूर्ण,
	अणु
		.cmd = NFC_CMD_GET_TARGET,
		.validate = GENL_DONT_VALIDATE_STRICT |
			    GENL_DONT_VALIDATE_DUMP_STRICT,
		.dumpit = nfc_genl_dump_tarमाला_लो,
		.करोne = nfc_genl_dump_tarमाला_लो_करोne,
	पूर्ण,
	अणु
		.cmd = NFC_CMD_LLC_GET_PARAMS,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = nfc_genl_llc_get_params,
	पूर्ण,
	अणु
		.cmd = NFC_CMD_LLC_SET_PARAMS,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = nfc_genl_llc_set_params,
	पूर्ण,
	अणु
		.cmd = NFC_CMD_LLC_SDREQ,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = nfc_genl_llc_sdreq,
	पूर्ण,
	अणु
		.cmd = NFC_CMD_FW_DOWNLOAD,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = nfc_genl_fw_करोwnload,
	पूर्ण,
	अणु
		.cmd = NFC_CMD_ENABLE_SE,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = nfc_genl_enable_se,
	पूर्ण,
	अणु
		.cmd = NFC_CMD_DISABLE_SE,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = nfc_genl_disable_se,
	पूर्ण,
	अणु
		.cmd = NFC_CMD_GET_SE,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.dumpit = nfc_genl_dump_ses,
		.करोne = nfc_genl_dump_ses_करोne,
	पूर्ण,
	अणु
		.cmd = NFC_CMD_SE_IO,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = nfc_genl_se_io,
	पूर्ण,
	अणु
		.cmd = NFC_CMD_ACTIVATE_TARGET,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = nfc_genl_activate_target,
	पूर्ण,
	अणु
		.cmd = NFC_CMD_VENDOR,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = nfc_genl_venकरोr_cmd,
	पूर्ण,
	अणु
		.cmd = NFC_CMD_DEACTIVATE_TARGET,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = nfc_genl_deactivate_target,
	पूर्ण,
पूर्ण;

अटल काष्ठा genl_family nfc_genl_family __ro_after_init = अणु
	.hdrsize = 0,
	.name = NFC_GENL_NAME,
	.version = NFC_GENL_VERSION,
	.maxattr = NFC_ATTR_MAX,
	.policy = nfc_genl_policy,
	.module = THIS_MODULE,
	.ops = nfc_genl_ops,
	.n_ops = ARRAY_SIZE(nfc_genl_ops),
	.mcgrps = nfc_genl_mcgrps,
	.n_mcgrps = ARRAY_SIZE(nfc_genl_mcgrps),
पूर्ण;


काष्ठा urelease_work अणु
	काष्ठा	work_काष्ठा w;
	u32	portid;
पूर्ण;

अटल व्योम nfc_urelease_event_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा urelease_work *w = container_of(work, काष्ठा urelease_work, w);
	काष्ठा class_dev_iter iter;
	काष्ठा nfc_dev *dev;

	pr_debug("portid %d\n", w->portid);

	mutex_lock(&nfc_devlist_mutex);

	nfc_device_iter_init(&iter);
	dev = nfc_device_iter_next(&iter);

	जबतक (dev) अणु
		mutex_lock(&dev->genl_data.genl_data_mutex);

		अगर (dev->genl_data.poll_req_portid == w->portid) अणु
			nfc_stop_poll(dev);
			dev->genl_data.poll_req_portid = 0;
		पूर्ण

		mutex_unlock(&dev->genl_data.genl_data_mutex);

		dev = nfc_device_iter_next(&iter);
	पूर्ण

	nfc_device_iter_निकास(&iter);

	mutex_unlock(&nfc_devlist_mutex);

	kमुक्त(w);
पूर्ण

अटल पूर्णांक nfc_genl_rcv_nl_event(काष्ठा notअगरier_block *this,
				 अचिन्हित दीर्घ event, व्योम *ptr)
अणु
	काष्ठा netlink_notअगरy *n = ptr;
	काष्ठा urelease_work *w;

	अगर (event != NETLINK_URELEASE || n->protocol != NETLINK_GENERIC)
		जाओ out;

	pr_debug("NETLINK_URELEASE event from id %d\n", n->portid);

	w = kदो_स्मृति(माप(*w), GFP_ATOMIC);
	अगर (w) अणु
		INIT_WORK(&w->w, nfc_urelease_event_work);
		w->portid = n->portid;
		schedule_work(&w->w);
	पूर्ण

out:
	वापस NOTIFY_DONE;
पूर्ण

व्योम nfc_genl_data_init(काष्ठा nfc_genl_data *genl_data)
अणु
	genl_data->poll_req_portid = 0;
	mutex_init(&genl_data->genl_data_mutex);
पूर्ण

व्योम nfc_genl_data_निकास(काष्ठा nfc_genl_data *genl_data)
अणु
	mutex_destroy(&genl_data->genl_data_mutex);
पूर्ण

अटल काष्ठा notअगरier_block nl_notअगरier = अणु
	.notअगरier_call  = nfc_genl_rcv_nl_event,
पूर्ण;

/**
 * nfc_genl_init() - Initialize netlink पूर्णांकerface
 *
 * This initialization function रेजिस्टरs the nfc netlink family.
 */
पूर्णांक __init nfc_genl_init(व्योम)
अणु
	पूर्णांक rc;

	rc = genl_रेजिस्टर_family(&nfc_genl_family);
	अगर (rc)
		वापस rc;

	netlink_रेजिस्टर_notअगरier(&nl_notअगरier);

	वापस 0;
पूर्ण

/**
 * nfc_genl_निकास() - Deinitialize netlink पूर्णांकerface
 *
 * This निकास function unरेजिस्टरs the nfc netlink family.
 */
व्योम nfc_genl_निकास(व्योम)
अणु
	netlink_unरेजिस्टर_notअगरier(&nl_notअगरier);
	genl_unरेजिस्टर_family(&nfc_genl_family);
पूर्ण
