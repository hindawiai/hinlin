<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright 2007-2012 Siemens AG
 *
 * Written by:
 * Dmitry Eremin-Solenikov <dbaryshkov@gmail.com>
 * Sergey Lapin <slapin@ossfans.org>
 * Maxim Gorbachyov <maxim.gorbachev@siemens.com>
 * Alexander Smirnov <alex.bluesman.smirnov@gmail.com>
 */

#समावेश <linux/netdevice.h>
#समावेश <linux/module.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/ieee802154.h>

#समावेश <net/nl802154.h>
#समावेश <net/mac802154.h>
#समावेश <net/ieee802154_netdev.h>
#समावेश <net/cfg802154.h>

#समावेश "ieee802154_i.h"
#समावेश "driver-ops.h"

पूर्णांक mac802154_wpan_update_llsec(काष्ठा net_device *dev)
अणु
	काष्ठा ieee802154_sub_अगर_data *sdata = IEEE802154_DEV_TO_SUB_IF(dev);
	काष्ठा ieee802154_mlme_ops *ops = ieee802154_mlme_ops(dev);
	काष्ठा wpan_dev *wpan_dev = &sdata->wpan_dev;
	पूर्णांक rc = 0;

	अगर (ops->llsec) अणु
		काष्ठा ieee802154_llsec_params params;
		पूर्णांक changed = 0;

		params.pan_id = wpan_dev->pan_id;
		changed |= IEEE802154_LLSEC_PARAM_PAN_ID;

		params.hwaddr = wpan_dev->extended_addr;
		changed |= IEEE802154_LLSEC_PARAM_HWADDR;

		rc = ops->llsec->set_params(dev, &params, changed);
	पूर्ण

	वापस rc;
पूर्ण

अटल पूर्णांक
mac802154_wpan_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *अगरr, पूर्णांक cmd)
अणु
	काष्ठा ieee802154_sub_अगर_data *sdata = IEEE802154_DEV_TO_SUB_IF(dev);
	काष्ठा wpan_dev *wpan_dev = &sdata->wpan_dev;
	काष्ठा sockaddr_ieee802154 *sa =
		(काष्ठा sockaddr_ieee802154 *)&अगरr->अगरr_addr;
	पूर्णांक err = -ENOIOCTLCMD;

	अगर (cmd != SIOCGIFADDR && cmd != SIOCSIFADDR)
		वापस err;

	rtnl_lock();

	चयन (cmd) अणु
	हाल SIOCGIFADDR:
	अणु
		u16 pan_id, लघु_addr;

		pan_id = le16_to_cpu(wpan_dev->pan_id);
		लघु_addr = le16_to_cpu(wpan_dev->लघु_addr);
		अगर (pan_id == IEEE802154_PANID_BROADCAST ||
		    लघु_addr == IEEE802154_ADDR_BROADCAST) अणु
			err = -EADDRNOTAVAIL;
			अवरोध;
		पूर्ण

		sa->family = AF_IEEE802154;
		sa->addr.addr_type = IEEE802154_ADDR_SHORT;
		sa->addr.pan_id = pan_id;
		sa->addr.लघु_addr = लघु_addr;

		err = 0;
		अवरोध;
	पूर्ण
	हाल SIOCSIFADDR:
		अगर (netअगर_running(dev)) अणु
			rtnl_unlock();
			वापस -EBUSY;
		पूर्ण

		dev_warn(&dev->dev,
			 "Using DEBUGing ioctl SIOCSIFADDR isn't recommended!\n");
		अगर (sa->family != AF_IEEE802154 ||
		    sa->addr.addr_type != IEEE802154_ADDR_SHORT ||
		    sa->addr.pan_id == IEEE802154_PANID_BROADCAST ||
		    sa->addr.लघु_addr == IEEE802154_ADDR_BROADCAST ||
		    sa->addr.लघु_addr == IEEE802154_ADDR_UNDEF) अणु
			err = -EINVAL;
			अवरोध;
		पूर्ण

		wpan_dev->pan_id = cpu_to_le16(sa->addr.pan_id);
		wpan_dev->लघु_addr = cpu_to_le16(sa->addr.लघु_addr);

		err = mac802154_wpan_update_llsec(dev);
		अवरोध;
	पूर्ण

	rtnl_unlock();
	वापस err;
पूर्ण

अटल पूर्णांक mac802154_wpan_mac_addr(काष्ठा net_device *dev, व्योम *p)
अणु
	काष्ठा ieee802154_sub_अगर_data *sdata = IEEE802154_DEV_TO_SUB_IF(dev);
	काष्ठा sockaddr *addr = p;
	__le64 extended_addr;

	अगर (netअगर_running(dev))
		वापस -EBUSY;

	/* lowpan need to be करोwn क्रम update
	 * SLAAC address after अगरup
	 */
	अगर (sdata->wpan_dev.lowpan_dev) अणु
		अगर (netअगर_running(sdata->wpan_dev.lowpan_dev))
			वापस -EBUSY;
	पूर्ण

	ieee802154_be64_to_le64(&extended_addr, addr->sa_data);
	अगर (!ieee802154_is_valid_extended_unicast_addr(extended_addr))
		वापस -EINVAL;

	स_नकल(dev->dev_addr, addr->sa_data, dev->addr_len);
	sdata->wpan_dev.extended_addr = extended_addr;

	/* update lowpan पूर्णांकerface mac address when
	 * wpan mac has been changed
	 */
	अगर (sdata->wpan_dev.lowpan_dev)
		स_नकल(sdata->wpan_dev.lowpan_dev->dev_addr, dev->dev_addr,
		       dev->addr_len);

	वापस mac802154_wpan_update_llsec(dev);
पूर्ण

अटल पूर्णांक ieee802154_setup_hw(काष्ठा ieee802154_sub_अगर_data *sdata)
अणु
	काष्ठा ieee802154_local *local = sdata->local;
	काष्ठा wpan_dev *wpan_dev = &sdata->wpan_dev;
	पूर्णांक ret;

	अगर (local->hw.flags & IEEE802154_HW_PROMISCUOUS) अणु
		ret = drv_set_promiscuous_mode(local,
					       wpan_dev->promiscuous_mode);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	अगर (local->hw.flags & IEEE802154_HW_AFILT) अणु
		ret = drv_set_pan_id(local, wpan_dev->pan_id);
		अगर (ret < 0)
			वापस ret;

		ret = drv_set_extended_addr(local, wpan_dev->extended_addr);
		अगर (ret < 0)
			वापस ret;

		ret = drv_set_लघु_addr(local, wpan_dev->लघु_addr);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	अगर (local->hw.flags & IEEE802154_HW_LBT) अणु
		ret = drv_set_lbt_mode(local, wpan_dev->lbt);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	अगर (local->hw.flags & IEEE802154_HW_CSMA_PARAMS) अणु
		ret = drv_set_csma_params(local, wpan_dev->min_be,
					  wpan_dev->max_be,
					  wpan_dev->csma_retries);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	अगर (local->hw.flags & IEEE802154_HW_FRAME_RETRIES) अणु
		ret = drv_set_max_frame_retries(local, wpan_dev->frame_retries);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mac802154_slave_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा ieee802154_sub_अगर_data *sdata = IEEE802154_DEV_TO_SUB_IF(dev);
	काष्ठा ieee802154_local *local = sdata->local;
	पूर्णांक res;

	ASSERT_RTNL();

	set_bit(SDATA_STATE_RUNNING, &sdata->state);

	अगर (!local->खोलो_count) अणु
		res = ieee802154_setup_hw(sdata);
		अगर (res)
			जाओ err;

		res = drv_start(local);
		अगर (res)
			जाओ err;
	पूर्ण

	local->खोलो_count++;
	netअगर_start_queue(dev);
	वापस 0;
err:
	/* might alपढ़ोy be clear but that करोesn't matter */
	clear_bit(SDATA_STATE_RUNNING, &sdata->state);

	वापस res;
पूर्ण

अटल पूर्णांक
ieee802154_check_mac_settings(काष्ठा ieee802154_local *local,
			      काष्ठा wpan_dev *wpan_dev,
			      काष्ठा wpan_dev *nwpan_dev)
अणु
	ASSERT_RTNL();

	अगर (local->hw.flags & IEEE802154_HW_PROMISCUOUS) अणु
		अगर (wpan_dev->promiscuous_mode != nwpan_dev->promiscuous_mode)
			वापस -EBUSY;
	पूर्ण

	अगर (local->hw.flags & IEEE802154_HW_AFILT) अणु
		अगर (wpan_dev->pan_id != nwpan_dev->pan_id ||
		    wpan_dev->लघु_addr != nwpan_dev->लघु_addr ||
		    wpan_dev->extended_addr != nwpan_dev->extended_addr)
			वापस -EBUSY;
	पूर्ण

	अगर (local->hw.flags & IEEE802154_HW_CSMA_PARAMS) अणु
		अगर (wpan_dev->min_be != nwpan_dev->min_be ||
		    wpan_dev->max_be != nwpan_dev->max_be ||
		    wpan_dev->csma_retries != nwpan_dev->csma_retries)
			वापस -EBUSY;
	पूर्ण

	अगर (local->hw.flags & IEEE802154_HW_FRAME_RETRIES) अणु
		अगर (wpan_dev->frame_retries != nwpan_dev->frame_retries)
			वापस -EBUSY;
	पूर्ण

	अगर (local->hw.flags & IEEE802154_HW_LBT) अणु
		अगर (wpan_dev->lbt != nwpan_dev->lbt)
			वापस -EBUSY;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
ieee802154_check_concurrent_अगरace(काष्ठा ieee802154_sub_अगर_data *sdata,
				  क्रमागत nl802154_अगरtype अगरtype)
अणु
	काष्ठा ieee802154_local *local = sdata->local;
	काष्ठा wpan_dev *wpan_dev = &sdata->wpan_dev;
	काष्ठा ieee802154_sub_अगर_data *nsdata;

	/* we hold the RTNL here so can safely walk the list */
	list_क्रम_each_entry(nsdata, &local->पूर्णांकerfaces, list) अणु
		अगर (nsdata != sdata && ieee802154_sdata_running(nsdata)) अणु
			पूर्णांक ret;

			/* TODO currently we करोn't support multiple node types
			 * we need to run skb_clone at rx path. Check अगर there
			 * exist really an use हाल अगर we need to support
			 * multiple node types at the same समय.
			 */
			अगर (wpan_dev->अगरtype == NL802154_IFTYPE_NODE &&
			    nsdata->wpan_dev.अगरtype == NL802154_IFTYPE_NODE)
				वापस -EBUSY;

			/* check all phy mac sublayer settings are the same.
			 * We have only one phy, dअगरferent values makes trouble.
			 */
			ret = ieee802154_check_mac_settings(local, wpan_dev,
							    &nsdata->wpan_dev);
			अगर (ret < 0)
				वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mac802154_wpan_खोलो(काष्ठा net_device *dev)
अणु
	पूर्णांक rc;
	काष्ठा ieee802154_sub_अगर_data *sdata = IEEE802154_DEV_TO_SUB_IF(dev);
	काष्ठा wpan_dev *wpan_dev = &sdata->wpan_dev;

	rc = ieee802154_check_concurrent_अगरace(sdata, wpan_dev->अगरtype);
	अगर (rc < 0)
		वापस rc;

	वापस mac802154_slave_खोलो(dev);
पूर्ण

अटल पूर्णांक mac802154_slave_बंद(काष्ठा net_device *dev)
अणु
	काष्ठा ieee802154_sub_अगर_data *sdata = IEEE802154_DEV_TO_SUB_IF(dev);
	काष्ठा ieee802154_local *local = sdata->local;

	ASSERT_RTNL();

	netअगर_stop_queue(dev);
	local->खोलो_count--;

	clear_bit(SDATA_STATE_RUNNING, &sdata->state);

	अगर (!local->खोलो_count)
		ieee802154_stop_device(local);

	वापस 0;
पूर्ण

अटल पूर्णांक mac802154_set_header_security(काष्ठा ieee802154_sub_अगर_data *sdata,
					 काष्ठा ieee802154_hdr *hdr,
					 स्थिर काष्ठा ieee802154_mac_cb *cb)
अणु
	काष्ठा ieee802154_llsec_params params;
	u8 level;

	mac802154_llsec_get_params(&sdata->sec, &params);

	अगर (!params.enabled && cb->secen_override && cb->secen)
		वापस -EINVAL;
	अगर (!params.enabled ||
	    (cb->secen_override && !cb->secen) ||
	    !params.out_level)
		वापस 0;
	अगर (cb->seclevel_override && !cb->seclevel)
		वापस -EINVAL;

	level = cb->seclevel_override ? cb->seclevel : params.out_level;

	hdr->fc.security_enabled = 1;
	hdr->sec.level = level;
	hdr->sec.key_id_mode = params.out_key.mode;
	अगर (params.out_key.mode == IEEE802154_SCF_KEY_SHORT_INDEX)
		hdr->sec.लघु_src = params.out_key.लघु_source;
	अन्यथा अगर (params.out_key.mode == IEEE802154_SCF_KEY_HW_INDEX)
		hdr->sec.extended_src = params.out_key.extended_source;
	hdr->sec.key_id = params.out_key.id;

	वापस 0;
पूर्ण

अटल पूर्णांक ieee802154_header_create(काष्ठा sk_buff *skb,
				    काष्ठा net_device *dev,
				    स्थिर काष्ठा ieee802154_addr *daddr,
				    स्थिर काष्ठा ieee802154_addr *saddr,
				    अचिन्हित len)
अणु
	काष्ठा ieee802154_hdr hdr;
	काष्ठा ieee802154_sub_अगर_data *sdata = IEEE802154_DEV_TO_SUB_IF(dev);
	काष्ठा wpan_dev *wpan_dev = &sdata->wpan_dev;
	काष्ठा ieee802154_mac_cb *cb = mac_cb(skb);
	पूर्णांक hlen;

	अगर (!daddr)
		वापस -EINVAL;

	स_रखो(&hdr.fc, 0, माप(hdr.fc));
	hdr.fc.type = cb->type;
	hdr.fc.security_enabled = cb->secen;
	hdr.fc.ack_request = cb->ackreq;
	hdr.seq = atomic_inc_वापस(&dev->ieee802154_ptr->dsn) & 0xFF;

	अगर (mac802154_set_header_security(sdata, &hdr, cb) < 0)
		वापस -EINVAL;

	अगर (!saddr) अणु
		अगर (wpan_dev->लघु_addr == cpu_to_le16(IEEE802154_ADDR_BROADCAST) ||
		    wpan_dev->लघु_addr == cpu_to_le16(IEEE802154_ADDR_UNDEF) ||
		    wpan_dev->pan_id == cpu_to_le16(IEEE802154_PANID_BROADCAST)) अणु
			hdr.source.mode = IEEE802154_ADDR_LONG;
			hdr.source.extended_addr = wpan_dev->extended_addr;
		पूर्ण अन्यथा अणु
			hdr.source.mode = IEEE802154_ADDR_SHORT;
			hdr.source.लघु_addr = wpan_dev->लघु_addr;
		पूर्ण

		hdr.source.pan_id = wpan_dev->pan_id;
	पूर्ण अन्यथा अणु
		hdr.source = *(स्थिर काष्ठा ieee802154_addr *)saddr;
	पूर्ण

	hdr.dest = *(स्थिर काष्ठा ieee802154_addr *)daddr;

	hlen = ieee802154_hdr_push(skb, &hdr);
	अगर (hlen < 0)
		वापस -EINVAL;

	skb_reset_mac_header(skb);
	skb->mac_len = hlen;

	अगर (len > ieee802154_max_payload(&hdr))
		वापस -EMSGSIZE;

	वापस hlen;
पूर्ण

अटल स्थिर काष्ठा wpan_dev_header_ops ieee802154_header_ops = अणु
	.create		= ieee802154_header_create,
पूर्ण;

/* This header create functionality assumes a 8 byte array क्रम
 * source and destination poपूर्णांकer at maximum. To adapt this क्रम
 * the 802.15.4 dataframe header we use extended address handling
 * here only and पूर्णांकra pan connection. fc fields are mostly fallback
 * handling. For provide dev_hard_header क्रम dgram sockets.
 */
अटल पूर्णांक mac802154_header_create(काष्ठा sk_buff *skb,
				   काष्ठा net_device *dev,
				   अचिन्हित लघु type,
				   स्थिर व्योम *daddr,
				   स्थिर व्योम *saddr,
				   अचिन्हित len)
अणु
	काष्ठा ieee802154_hdr hdr;
	काष्ठा ieee802154_sub_अगर_data *sdata = IEEE802154_DEV_TO_SUB_IF(dev);
	काष्ठा wpan_dev *wpan_dev = &sdata->wpan_dev;
	काष्ठा ieee802154_mac_cb cb = अणु पूर्ण;
	पूर्णांक hlen;

	अगर (!daddr)
		वापस -EINVAL;

	स_रखो(&hdr.fc, 0, माप(hdr.fc));
	hdr.fc.type = IEEE802154_FC_TYPE_DATA;
	hdr.fc.ack_request = wpan_dev->ackreq;
	hdr.seq = atomic_inc_वापस(&dev->ieee802154_ptr->dsn) & 0xFF;

	/* TODO currently a workaround to give zero cb block to set
	 * security parameters शेषs according MIB.
	 */
	अगर (mac802154_set_header_security(sdata, &hdr, &cb) < 0)
		वापस -EINVAL;

	hdr.dest.pan_id = wpan_dev->pan_id;
	hdr.dest.mode = IEEE802154_ADDR_LONG;
	ieee802154_be64_to_le64(&hdr.dest.extended_addr, daddr);

	hdr.source.pan_id = hdr.dest.pan_id;
	hdr.source.mode = IEEE802154_ADDR_LONG;

	अगर (!saddr)
		hdr.source.extended_addr = wpan_dev->extended_addr;
	अन्यथा
		ieee802154_be64_to_le64(&hdr.source.extended_addr, saddr);

	hlen = ieee802154_hdr_push(skb, &hdr);
	अगर (hlen < 0)
		वापस -EINVAL;

	skb_reset_mac_header(skb);
	skb->mac_len = hlen;

	अगर (len > ieee802154_max_payload(&hdr))
		वापस -EMSGSIZE;

	वापस hlen;
पूर्ण

अटल पूर्णांक
mac802154_header_parse(स्थिर काष्ठा sk_buff *skb, अचिन्हित अक्षर *haddr)
अणु
	काष्ठा ieee802154_hdr hdr;

	अगर (ieee802154_hdr_peek_addrs(skb, &hdr) < 0) अणु
		pr_debug("malformed packet\n");
		वापस 0;
	पूर्ण

	अगर (hdr.source.mode == IEEE802154_ADDR_LONG) अणु
		ieee802154_le64_to_be64(haddr, &hdr.source.extended_addr);
		वापस IEEE802154_EXTENDED_ADDR_LEN;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा header_ops mac802154_header_ops = अणु
	.create         = mac802154_header_create,
	.parse          = mac802154_header_parse,
पूर्ण;

अटल स्थिर काष्ठा net_device_ops mac802154_wpan_ops = अणु
	.nकरो_खोलो		= mac802154_wpan_खोलो,
	.nकरो_stop		= mac802154_slave_बंद,
	.nकरो_start_xmit		= ieee802154_subअगर_start_xmit,
	.nकरो_करो_ioctl		= mac802154_wpan_ioctl,
	.nकरो_set_mac_address	= mac802154_wpan_mac_addr,
पूर्ण;

अटल स्थिर काष्ठा net_device_ops mac802154_monitor_ops = अणु
	.nकरो_खोलो		= mac802154_wpan_खोलो,
	.nकरो_stop		= mac802154_slave_बंद,
	.nकरो_start_xmit		= ieee802154_monitor_start_xmit,
पूर्ण;

अटल व्योम mac802154_wpan_मुक्त(काष्ठा net_device *dev)
अणु
	काष्ठा ieee802154_sub_अगर_data *sdata = IEEE802154_DEV_TO_SUB_IF(dev);

	mac802154_llsec_destroy(&sdata->sec);
पूर्ण

अटल व्योम ieee802154_अगर_setup(काष्ठा net_device *dev)
अणु
	dev->addr_len		= IEEE802154_EXTENDED_ADDR_LEN;
	स_रखो(dev->broadcast, 0xff, IEEE802154_EXTENDED_ADDR_LEN);

	/* Let hard_header_len set to IEEE802154_MIN_HEADER_LEN. AF_PACKET
	 * will not send frames without any payload, but ack frames
	 * has no payload, so substract one that we can send a 3 bytes
	 * frame. The xmit callback assumes at least a hard header where two
	 * bytes fc and sequence field are set.
	 */
	dev->hard_header_len	= IEEE802154_MIN_HEADER_LEN - 1;
	/* The auth_tag header is क्रम security and places in निजी payload
	 * room of mac frame which stucks between payload and FCS field.
	 */
	dev->needed_tailroom	= IEEE802154_MAX_AUTH_TAG_LEN +
				  IEEE802154_FCS_LEN;
	/* The mtu size is the payload without mac header in this हाल.
	 * We have a dynamic length header with a minimum header length
	 * which is hard_header_len. In this हाल we let mtu to the size
	 * of maximum payload which is IEEE802154_MTU - IEEE802154_FCS_LEN -
	 * hard_header_len. The FCS which is set by hardware or nकरो_start_xmit
	 * and the minimum mac header which can be evaluated inside driver
	 * layer. The rest of mac header will be part of payload अगर greater
	 * than hard_header_len.
	 */
	dev->mtu		= IEEE802154_MTU - IEEE802154_FCS_LEN -
				  dev->hard_header_len;
	dev->tx_queue_len	= 300;
	dev->flags		= IFF_NOARP | IFF_BROADCAST;
पूर्ण

अटल पूर्णांक
ieee802154_setup_sdata(काष्ठा ieee802154_sub_अगर_data *sdata,
		       क्रमागत nl802154_अगरtype type)
अणु
	काष्ठा wpan_dev *wpan_dev = &sdata->wpan_dev;
	पूर्णांक ret;
	u8 पंचांगp;

	/* set some type-dependent values */
	sdata->wpan_dev.अगरtype = type;

	get_अक्रमom_bytes(&पंचांगp, माप(पंचांगp));
	atomic_set(&wpan_dev->bsn, पंचांगp);
	get_अक्रमom_bytes(&पंचांगp, माप(पंचांगp));
	atomic_set(&wpan_dev->dsn, पंचांगp);

	/* शेषs per 802.15.4-2011 */
	wpan_dev->min_be = 3;
	wpan_dev->max_be = 5;
	wpan_dev->csma_retries = 4;
	wpan_dev->frame_retries = 3;

	wpan_dev->pan_id = cpu_to_le16(IEEE802154_PANID_BROADCAST);
	wpan_dev->लघु_addr = cpu_to_le16(IEEE802154_ADDR_BROADCAST);

	चयन (type) अणु
	हाल NL802154_IFTYPE_NODE:
		ieee802154_be64_to_le64(&wpan_dev->extended_addr,
					sdata->dev->dev_addr);

		sdata->dev->header_ops = &mac802154_header_ops;
		sdata->dev->needs_मुक्त_netdev = true;
		sdata->dev->priv_deकाष्ठाor = mac802154_wpan_मुक्त;
		sdata->dev->netdev_ops = &mac802154_wpan_ops;
		sdata->dev->ml_priv = &mac802154_mlme_wpan;
		wpan_dev->promiscuous_mode = false;
		wpan_dev->header_ops = &ieee802154_header_ops;

		mutex_init(&sdata->sec_mtx);

		mac802154_llsec_init(&sdata->sec);
		ret = mac802154_wpan_update_llsec(sdata->dev);
		अगर (ret < 0)
			वापस ret;

		अवरोध;
	हाल NL802154_IFTYPE_MONITOR:
		sdata->dev->needs_मुक्त_netdev = true;
		sdata->dev->netdev_ops = &mac802154_monitor_ops;
		wpan_dev->promiscuous_mode = true;
		अवरोध;
	शेष:
		BUG();
	पूर्ण

	वापस 0;
पूर्ण

काष्ठा net_device *
ieee802154_अगर_add(काष्ठा ieee802154_local *local, स्थिर अक्षर *name,
		  अचिन्हित अक्षर name_assign_type, क्रमागत nl802154_अगरtype type,
		  __le64 extended_addr)
अणु
	काष्ठा net_device *ndev = शून्य;
	काष्ठा ieee802154_sub_अगर_data *sdata = शून्य;
	पूर्णांक ret = -ENOMEM;

	ASSERT_RTNL();

	ndev = alloc_netdev(माप(*sdata), name,
			    name_assign_type, ieee802154_अगर_setup);
	अगर (!ndev)
		वापस ERR_PTR(-ENOMEM);

	ndev->needed_headroom = local->hw.extra_tx_headroom +
				IEEE802154_MAX_HEADER_LEN;

	ret = dev_alloc_name(ndev, ndev->name);
	अगर (ret < 0)
		जाओ err;

	ieee802154_le64_to_be64(ndev->perm_addr,
				&local->hw.phy->perm_extended_addr);
	चयन (type) अणु
	हाल NL802154_IFTYPE_NODE:
		ndev->type = ARPHRD_IEEE802154;
		अगर (ieee802154_is_valid_extended_unicast_addr(extended_addr))
			ieee802154_le64_to_be64(ndev->dev_addr, &extended_addr);
		अन्यथा
			स_नकल(ndev->dev_addr, ndev->perm_addr,
			       IEEE802154_EXTENDED_ADDR_LEN);
		अवरोध;
	हाल NL802154_IFTYPE_MONITOR:
		ndev->type = ARPHRD_IEEE802154_MONITOR;
		अवरोध;
	शेष:
		ret = -EINVAL;
		जाओ err;
	पूर्ण

	/* TODO check this */
	SET_NETDEV_DEV(ndev, &local->phy->dev);
	dev_net_set(ndev, wpan_phy_net(local->hw.phy));
	sdata = netdev_priv(ndev);
	ndev->ieee802154_ptr = &sdata->wpan_dev;
	स_नकल(sdata->name, ndev->name, IFNAMSIZ);
	sdata->dev = ndev;
	sdata->wpan_dev.wpan_phy = local->hw.phy;
	sdata->local = local;

	/* setup type-dependent data */
	ret = ieee802154_setup_sdata(sdata, type);
	अगर (ret)
		जाओ err;

	ret = रेजिस्टर_netdevice(ndev);
	अगर (ret < 0)
		जाओ err;

	mutex_lock(&local->अगरlist_mtx);
	list_add_tail_rcu(&sdata->list, &local->पूर्णांकerfaces);
	mutex_unlock(&local->अगरlist_mtx);

	वापस ndev;

err:
	मुक्त_netdev(ndev);
	वापस ERR_PTR(ret);
पूर्ण

व्योम ieee802154_अगर_हटाओ(काष्ठा ieee802154_sub_अगर_data *sdata)
अणु
	ASSERT_RTNL();

	mutex_lock(&sdata->local->अगरlist_mtx);
	list_del_rcu(&sdata->list);
	mutex_unlock(&sdata->local->अगरlist_mtx);

	synchronize_rcu();
	unरेजिस्टर_netdevice(sdata->dev);
पूर्ण

व्योम ieee802154_हटाओ_पूर्णांकerfaces(काष्ठा ieee802154_local *local)
अणु
	काष्ठा ieee802154_sub_अगर_data *sdata, *पंचांगp;

	mutex_lock(&local->अगरlist_mtx);
	list_क्रम_each_entry_safe(sdata, पंचांगp, &local->पूर्णांकerfaces, list) अणु
		list_del(&sdata->list);

		unरेजिस्टर_netdevice(sdata->dev);
	पूर्ण
	mutex_unlock(&local->अगरlist_mtx);
पूर्ण

अटल पूर्णांक netdev_notअगरy(काष्ठा notअगरier_block *nb,
			 अचिन्हित दीर्घ state, व्योम *ptr)
अणु
	काष्ठा net_device *dev = netdev_notअगरier_info_to_dev(ptr);
	काष्ठा ieee802154_sub_अगर_data *sdata;

	अगर (state != NETDEV_CHANGENAME)
		वापस NOTIFY_DONE;

	अगर (!dev->ieee802154_ptr || !dev->ieee802154_ptr->wpan_phy)
		वापस NOTIFY_DONE;

	अगर (dev->ieee802154_ptr->wpan_phy->privid != mac802154_wpan_phy_privid)
		वापस NOTIFY_DONE;

	sdata = IEEE802154_DEV_TO_SUB_IF(dev);
	स_नकल(sdata->name, dev->name, IFNAMSIZ);

	वापस NOTIFY_OK;
पूर्ण

अटल काष्ठा notअगरier_block mac802154_netdev_notअगरier = अणु
	.notअगरier_call = netdev_notअगरy,
पूर्ण;

पूर्णांक ieee802154_अगरace_init(व्योम)
अणु
	वापस रेजिस्टर_netdevice_notअगरier(&mac802154_netdev_notअगरier);
पूर्ण

व्योम ieee802154_अगरace_निकास(व्योम)
अणु
	unरेजिस्टर_netdevice_notअगरier(&mac802154_netdev_notअगरier);
पूर्ण
