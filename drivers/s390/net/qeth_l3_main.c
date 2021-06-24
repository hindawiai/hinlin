<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *    Copyright IBM Corp. 2007, 2009
 *    Author(s): Utz Bacher <utz.bacher@de.ibm.com>,
 *		 Frank Pavlic <fpavlic@de.ibm.com>,
 *		 Thomas Spatzier <tspat@de.ibm.com>,
 *		 Frank Blaschka <frank.blaschka@de.ibm.com>
 */

#घोषणा KMSG_COMPONENT "qeth"
#घोषणा pr_fmt(fmt) KMSG_COMPONENT ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/bitops.h>
#समावेश <linux/माला.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/ip.h>
#समावेश <linux/in.h>
#समावेश <linux/ipv6.h>
#समावेश <linux/inetdevice.h>
#समावेश <linux/igmp.h>
#समावेश <linux/slab.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/skbuff.h>

#समावेश <net/ip.h>
#समावेश <net/arp.h>
#समावेश <net/route.h>
#समावेश <net/ipv6.h>
#समावेश <net/ip6_route.h>
#समावेश <net/iucv/af_iucv.h>
#समावेश <linux/hashtable.h>

#समावेश "qeth_l3.h"

अटल पूर्णांक qeth_l3_रेजिस्टर_addr_entry(काष्ठा qeth_card *,
		काष्ठा qeth_ipaddr *);
अटल पूर्णांक qeth_l3_deरेजिस्टर_addr_entry(काष्ठा qeth_card *,
		काष्ठा qeth_ipaddr *);

पूर्णांक qeth_l3_ipaddr_to_string(क्रमागत qeth_prot_versions proto, स्थिर u8 *addr,
			     अक्षर *buf)
अणु
	अगर (proto == QETH_PROT_IPV4)
		वापस प्र_लिखो(buf, "%pI4", addr);
	अन्यथा
		वापस प्र_लिखो(buf, "%pI6", addr);
पूर्ण

अटल काष्ठा qeth_ipaddr *qeth_l3_find_addr_by_ip(काष्ठा qeth_card *card,
						   काष्ठा qeth_ipaddr *query)
अणु
	u32 key = qeth_l3_ipaddr_hash(query);
	काष्ठा qeth_ipaddr *addr;

	अगर (query->is_multicast) अणु
		hash_क्रम_each_possible(card->rx_mode_addrs, addr, hnode, key)
			अगर (qeth_l3_addr_match_ip(addr, query))
				वापस addr;
	पूर्ण अन्यथा अणु
		hash_क्रम_each_possible(card->ip_htable,  addr, hnode, key)
			अगर (qeth_l3_addr_match_ip(addr, query))
				वापस addr;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल व्योम qeth_l3_convert_addr_to_bits(u8 *addr, u8 *bits, पूर्णांक len)
अणु
	पूर्णांक i, j;
	u8 octet;

	क्रम (i = 0; i < len; ++i) अणु
		octet = addr[i];
		क्रम (j = 7; j >= 0; --j) अणु
			bits[i*8 + j] = octet & 1;
			octet >>= 1;
		पूर्ण
	पूर्ण
पूर्ण

अटल bool qeth_l3_is_addr_covered_by_ipato(काष्ठा qeth_card *card,
					     काष्ठा qeth_ipaddr *addr)
अणु
	काष्ठा qeth_ipato_entry *ipatoe;
	u8 addr_bits[128] = अणु0, पूर्ण;
	u8 ipatoe_bits[128] = अणु0, पूर्ण;
	पूर्णांक rc = 0;

	अगर (!card->ipato.enabled)
		वापस false;
	अगर (addr->type != QETH_IP_TYPE_NORMAL)
		वापस false;

	qeth_l3_convert_addr_to_bits((u8 *) &addr->u, addr_bits,
				     (addr->proto == QETH_PROT_IPV4) ? 4 : 16);
	list_क्रम_each_entry(ipatoe, &card->ipato.entries, entry) अणु
		अगर (addr->proto != ipatoe->proto)
			जारी;
		qeth_l3_convert_addr_to_bits(ipatoe->addr, ipatoe_bits,
					  (ipatoe->proto == QETH_PROT_IPV4) ?
					  4 : 16);
		rc = !स_भेद(addr_bits, ipatoe_bits, ipatoe->mask_bits);
		अगर (rc)
			अवरोध;
	पूर्ण
	/* invert? */
	अगर ((addr->proto == QETH_PROT_IPV4) && card->ipato.invert4)
		rc = !rc;
	अन्यथा अगर ((addr->proto == QETH_PROT_IPV6) && card->ipato.invert6)
		rc = !rc;

	वापस rc;
पूर्ण

अटल पूर्णांक qeth_l3_delete_ip(काष्ठा qeth_card *card,
			     काष्ठा qeth_ipaddr *पंचांगp_addr)
अणु
	पूर्णांक rc = 0;
	काष्ठा qeth_ipaddr *addr;

	अगर (पंचांगp_addr->type == QETH_IP_TYPE_RXIP)
		QETH_CARD_TEXT(card, 2, "delrxip");
	अन्यथा अगर (पंचांगp_addr->type == QETH_IP_TYPE_VIPA)
		QETH_CARD_TEXT(card, 2, "delvipa");
	अन्यथा
		QETH_CARD_TEXT(card, 2, "delip");

	अगर (पंचांगp_addr->proto == QETH_PROT_IPV4)
		QETH_CARD_HEX(card, 4, &पंचांगp_addr->u.a4.addr, 4);
	अन्यथा अणु
		QETH_CARD_HEX(card, 4, &पंचांगp_addr->u.a6.addr, 8);
		QETH_CARD_HEX(card, 4, ((अक्षर *)&पंचांगp_addr->u.a6.addr) + 8, 8);
	पूर्ण

	addr = qeth_l3_find_addr_by_ip(card, पंचांगp_addr);
	अगर (!addr || !qeth_l3_addr_match_all(addr, पंचांगp_addr))
		वापस -ENOENT;

	addr->ref_counter--;
	अगर (addr->type == QETH_IP_TYPE_NORMAL && addr->ref_counter > 0)
		वापस rc;

	अगर (qeth_card_hw_is_reachable(card))
		rc = qeth_l3_deरेजिस्टर_addr_entry(card, addr);

	hash_del(&addr->hnode);
	kमुक्त(addr);

	वापस rc;
पूर्ण

अटल पूर्णांक qeth_l3_add_ip(काष्ठा qeth_card *card, काष्ठा qeth_ipaddr *पंचांगp_addr)
अणु
	पूर्णांक rc = 0;
	काष्ठा qeth_ipaddr *addr;
	अक्षर buf[40];

	अगर (पंचांगp_addr->type == QETH_IP_TYPE_RXIP)
		QETH_CARD_TEXT(card, 2, "addrxip");
	अन्यथा अगर (पंचांगp_addr->type == QETH_IP_TYPE_VIPA)
		QETH_CARD_TEXT(card, 2, "addvipa");
	अन्यथा
		QETH_CARD_TEXT(card, 2, "addip");

	अगर (पंचांगp_addr->proto == QETH_PROT_IPV4)
		QETH_CARD_HEX(card, 4, &पंचांगp_addr->u.a4.addr, 4);
	अन्यथा अणु
		QETH_CARD_HEX(card, 4, &पंचांगp_addr->u.a6.addr, 8);
		QETH_CARD_HEX(card, 4, ((अक्षर *)&पंचांगp_addr->u.a6.addr) + 8, 8);
	पूर्ण

	addr = qeth_l3_find_addr_by_ip(card, पंचांगp_addr);
	अगर (addr) अणु
		अगर (पंचांगp_addr->type != QETH_IP_TYPE_NORMAL)
			वापस -EADDRINUSE;
		अगर (qeth_l3_addr_match_all(addr, पंचांगp_addr)) अणु
			addr->ref_counter++;
			वापस 0;
		पूर्ण
		qeth_l3_ipaddr_to_string(पंचांगp_addr->proto, (u8 *)&पंचांगp_addr->u,
					 buf);
		dev_warn(&card->gdev->dev,
			 "Registering IP address %s failed\n", buf);
		वापस -EADDRINUSE;
	पूर्ण अन्यथा अणु
		addr = kmemdup(पंचांगp_addr, माप(*पंचांगp_addr), GFP_KERNEL);
		अगर (!addr)
			वापस -ENOMEM;

		अगर (qeth_l3_is_addr_covered_by_ipato(card, addr)) अणु
			QETH_CARD_TEXT(card, 2, "tkovaddr");
			addr->ipato = 1;
		पूर्ण
		hash_add(card->ip_htable, &addr->hnode,
				qeth_l3_ipaddr_hash(addr));

		अगर (!qeth_card_hw_is_reachable(card)) अणु
			addr->disp_flag = QETH_DISP_ADDR_ADD;
			वापस 0;
		पूर्ण

		rc = qeth_l3_रेजिस्टर_addr_entry(card, addr);

		अगर (!rc || rc == -EADDRINUSE || rc == -ENETDOWN) अणु
			addr->disp_flag = QETH_DISP_ADDR_DO_NOTHING;
		पूर्ण अन्यथा अणु
			hash_del(&addr->hnode);
			kमुक्त(addr);
		पूर्ण
	पूर्ण
	वापस rc;
पूर्ण

अटल पूर्णांक qeth_l3_modअगरy_ip(काष्ठा qeth_card *card, काष्ठा qeth_ipaddr *addr,
			     bool add)
अणु
	पूर्णांक rc;

	mutex_lock(&card->ip_lock);
	rc = add ? qeth_l3_add_ip(card, addr) : qeth_l3_delete_ip(card, addr);
	mutex_unlock(&card->ip_lock);

	वापस rc;
पूर्ण

अटल व्योम qeth_l3_drain_rx_mode_cache(काष्ठा qeth_card *card)
अणु
	काष्ठा qeth_ipaddr *addr;
	काष्ठा hlist_node *पंचांगp;
	पूर्णांक i;

	hash_क्रम_each_safe(card->rx_mode_addrs, i, पंचांगp, addr, hnode) अणु
		hash_del(&addr->hnode);
		kमुक्त(addr);
	पूर्ण
पूर्ण

अटल व्योम qeth_l3_clear_ip_htable(काष्ठा qeth_card *card, पूर्णांक recover)
अणु
	काष्ठा qeth_ipaddr *addr;
	काष्ठा hlist_node *पंचांगp;
	पूर्णांक i;

	QETH_CARD_TEXT(card, 4, "clearip");

	mutex_lock(&card->ip_lock);

	hash_क्रम_each_safe(card->ip_htable, i, पंचांगp, addr, hnode) अणु
		अगर (!recover) अणु
			hash_del(&addr->hnode);
			kमुक्त(addr);
			जारी;
		पूर्ण
		addr->disp_flag = QETH_DISP_ADDR_ADD;
	पूर्ण

	mutex_unlock(&card->ip_lock);
पूर्ण

अटल व्योम qeth_l3_recover_ip(काष्ठा qeth_card *card)
अणु
	काष्ठा qeth_ipaddr *addr;
	काष्ठा hlist_node *पंचांगp;
	पूर्णांक i;
	पूर्णांक rc;

	QETH_CARD_TEXT(card, 4, "recovrip");

	mutex_lock(&card->ip_lock);

	hash_क्रम_each_safe(card->ip_htable, i, पंचांगp, addr, hnode) अणु
		अगर (addr->disp_flag == QETH_DISP_ADDR_ADD) अणु
			rc = qeth_l3_रेजिस्टर_addr_entry(card, addr);

			अगर (!rc) अणु
				addr->disp_flag = QETH_DISP_ADDR_DO_NOTHING;
			पूर्ण अन्यथा अणु
				hash_del(&addr->hnode);
				kमुक्त(addr);
			पूर्ण
		पूर्ण
	पूर्ण

	mutex_unlock(&card->ip_lock);
पूर्ण

अटल पूर्णांक qeth_l3_setdelip_cb(काष्ठा qeth_card *card, काष्ठा qeth_reply *reply,
			       अचिन्हित दीर्घ data)
अणु
	काष्ठा qeth_ipa_cmd *cmd = (काष्ठा qeth_ipa_cmd *) data;

	चयन (cmd->hdr.वापस_code) अणु
	हाल IPA_RC_SUCCESS:
		वापस 0;
	हाल IPA_RC_DUPLICATE_IP_ADDRESS:
		वापस -EADDRINUSE;
	हाल IPA_RC_MC_ADDR_NOT_FOUND:
		वापस -ENOENT;
	हाल IPA_RC_LAN_OFFLINE:
		वापस -ENETDOWN;
	शेष:
		वापस -EIO;
	पूर्ण
पूर्ण

अटल पूर्णांक qeth_l3_send_setdelmc(काष्ठा qeth_card *card,
				 काष्ठा qeth_ipaddr *addr,
				 क्रमागत qeth_ipa_cmds ipacmd)
अणु
	काष्ठा qeth_cmd_buffer *iob;
	काष्ठा qeth_ipa_cmd *cmd;

	QETH_CARD_TEXT(card, 4, "setdelmc");

	iob = qeth_ipa_alloc_cmd(card, ipacmd, addr->proto,
				 IPA_DATA_SIZखातापूर्ण(setdelipm));
	अगर (!iob)
		वापस -ENOMEM;
	cmd = __ipa_cmd(iob);
	अगर (addr->proto == QETH_PROT_IPV6) अणु
		cmd->data.setdelipm.ip = addr->u.a6.addr;
		ipv6_eth_mc_map(&addr->u.a6.addr, cmd->data.setdelipm.mac);
	पूर्ण अन्यथा अणु
		cmd->data.setdelipm.ip.s6_addr32[3] = addr->u.a4.addr;
		ip_eth_mc_map(addr->u.a4.addr, cmd->data.setdelipm.mac);
	पूर्ण

	वापस qeth_send_ipa_cmd(card, iob, qeth_l3_setdelip_cb, शून्य);
पूर्ण

अटल व्योम qeth_l3_set_ipv6_prefix(काष्ठा in6_addr *prefix, अचिन्हित पूर्णांक len)
अणु
	अचिन्हित पूर्णांक i = 0;

	जबतक (len && i < 4) अणु
		पूर्णांक mask_len = min_t(पूर्णांक, len, 32);

		prefix->s6_addr32[i] = inet_make_mask(mask_len);
		len -= mask_len;
		i++;
	पूर्ण
पूर्ण

अटल u32 qeth_l3_get_setdelip_flags(काष्ठा qeth_ipaddr *addr, bool set)
अणु
	चयन (addr->type) अणु
	हाल QETH_IP_TYPE_RXIP:
		वापस (set) ? QETH_IPA_SETIP_TAKEOVER_FLAG : 0;
	हाल QETH_IP_TYPE_VIPA:
		वापस (set) ? QETH_IPA_SETIP_VIPA_FLAG :
			       QETH_IPA_DELIP_VIPA_FLAG;
	शेष:
		वापस (set && addr->ipato) ? QETH_IPA_SETIP_TAKEOVER_FLAG : 0;
	पूर्ण
पूर्ण

अटल पूर्णांक qeth_l3_send_setdelip(काष्ठा qeth_card *card,
				 काष्ठा qeth_ipaddr *addr,
				 क्रमागत qeth_ipa_cmds ipacmd)
अणु
	काष्ठा qeth_cmd_buffer *iob;
	काष्ठा qeth_ipa_cmd *cmd;
	u32 flags;

	QETH_CARD_TEXT(card, 4, "setdelip");

	iob = qeth_ipa_alloc_cmd(card, ipacmd, addr->proto,
				 IPA_DATA_SIZखातापूर्ण(setdelip6));
	अगर (!iob)
		वापस -ENOMEM;
	cmd = __ipa_cmd(iob);

	flags = qeth_l3_get_setdelip_flags(addr, ipacmd == IPA_CMD_SETIP);
	QETH_CARD_TEXT_(card, 4, "flags%02X", flags);

	अगर (addr->proto == QETH_PROT_IPV6) अणु
		cmd->data.setdelip6.addr = addr->u.a6.addr;
		qeth_l3_set_ipv6_prefix(&cmd->data.setdelip6.prefix,
					addr->u.a6.pfxlen);
		cmd->data.setdelip6.flags = flags;
	पूर्ण अन्यथा अणु
		cmd->data.setdelip4.addr = addr->u.a4.addr;
		cmd->data.setdelip4.mask = addr->u.a4.mask;
		cmd->data.setdelip4.flags = flags;
	पूर्ण

	वापस qeth_send_ipa_cmd(card, iob, qeth_l3_setdelip_cb, शून्य);
पूर्ण

अटल पूर्णांक qeth_l3_send_setrouting(काष्ठा qeth_card *card,
	क्रमागत qeth_routing_types type, क्रमागत qeth_prot_versions prot)
अणु
	पूर्णांक rc;
	काष्ठा qeth_ipa_cmd *cmd;
	काष्ठा qeth_cmd_buffer *iob;

	QETH_CARD_TEXT(card, 4, "setroutg");
	iob = qeth_ipa_alloc_cmd(card, IPA_CMD_SETRTG, prot,
				 IPA_DATA_SIZखातापूर्ण(setrtg));
	अगर (!iob)
		वापस -ENOMEM;
	cmd = __ipa_cmd(iob);
	cmd->data.setrtg.type = (type);
	rc = qeth_send_ipa_cmd(card, iob, शून्य, शून्य);

	वापस rc;
पूर्ण

अटल पूर्णांक qeth_l3_correct_routing_type(काष्ठा qeth_card *card,
		क्रमागत qeth_routing_types *type, क्रमागत qeth_prot_versions prot)
अणु
	अगर (IS_IQD(card)) अणु
		चयन (*type) अणु
		हाल NO_ROUTER:
		हाल PRIMARY_CONNECTOR:
		हाल SECONDARY_CONNECTOR:
		हाल MULTICAST_ROUTER:
			वापस 0;
		शेष:
			जाओ out_inval;
		पूर्ण
	पूर्ण अन्यथा अणु
		चयन (*type) अणु
		हाल NO_ROUTER:
		हाल PRIMARY_ROUTER:
		हाल SECONDARY_ROUTER:
			वापस 0;
		हाल MULTICAST_ROUTER:
			अगर (qeth_is_ipafunc_supported(card, prot,
						      IPA_OSA_MC_ROUTER))
				वापस 0;
		शेष:
			जाओ out_inval;
		पूर्ण
	पूर्ण
out_inval:
	*type = NO_ROUTER;
	वापस -EINVAL;
पूर्ण

पूर्णांक qeth_l3_setrouting_v4(काष्ठा qeth_card *card)
अणु
	पूर्णांक rc;

	QETH_CARD_TEXT(card, 3, "setrtg4");

	rc = qeth_l3_correct_routing_type(card, &card->options.route4.type,
				  QETH_PROT_IPV4);
	अगर (rc)
		वापस rc;

	rc = qeth_l3_send_setrouting(card, card->options.route4.type,
				  QETH_PROT_IPV4);
	अगर (rc) अणु
		card->options.route4.type = NO_ROUTER;
		QETH_DBF_MESSAGE(2, "Error (%#06x) while setting routing type on device %x. Type set to 'no router'.\n",
				 rc, CARD_DEVID(card));
	पूर्ण
	वापस rc;
पूर्ण

पूर्णांक qeth_l3_setrouting_v6(काष्ठा qeth_card *card)
अणु
	पूर्णांक rc = 0;

	QETH_CARD_TEXT(card, 3, "setrtg6");

	अगर (!qeth_is_supported(card, IPA_IPV6))
		वापस 0;
	rc = qeth_l3_correct_routing_type(card, &card->options.route6.type,
				  QETH_PROT_IPV6);
	अगर (rc)
		वापस rc;

	rc = qeth_l3_send_setrouting(card, card->options.route6.type,
				  QETH_PROT_IPV6);
	अगर (rc) अणु
		card->options.route6.type = NO_ROUTER;
		QETH_DBF_MESSAGE(2, "Error (%#06x) while setting routing type on device %x. Type set to 'no router'.\n",
				 rc, CARD_DEVID(card));
	पूर्ण
	वापस rc;
पूर्ण

/*
 * IP address takeover related functions
 */

/**
 * qeth_l3_update_ipato() - Update 'takeover' property, क्रम all NORMAL IPs.
 *
 * Caller must hold ip_lock.
 */
व्योम qeth_l3_update_ipato(काष्ठा qeth_card *card)
अणु
	काष्ठा qeth_ipaddr *addr;
	अचिन्हित पूर्णांक i;

	hash_क्रम_each(card->ip_htable, i, addr, hnode) अणु
		अगर (addr->type != QETH_IP_TYPE_NORMAL)
			जारी;
		addr->ipato = qeth_l3_is_addr_covered_by_ipato(card, addr);
	पूर्ण
पूर्ण

अटल व्योम qeth_l3_clear_ipato_list(काष्ठा qeth_card *card)
अणु
	काष्ठा qeth_ipato_entry *ipatoe, *पंचांगp;

	mutex_lock(&card->ip_lock);

	list_क्रम_each_entry_safe(ipatoe, पंचांगp, &card->ipato.entries, entry) अणु
		list_del(&ipatoe->entry);
		kमुक्त(ipatoe);
	पूर्ण

	qeth_l3_update_ipato(card);
	mutex_unlock(&card->ip_lock);
पूर्ण

पूर्णांक qeth_l3_add_ipato_entry(काष्ठा qeth_card *card,
				काष्ठा qeth_ipato_entry *new)
अणु
	काष्ठा qeth_ipato_entry *ipatoe;
	पूर्णांक rc = 0;

	QETH_CARD_TEXT(card, 2, "addipato");

	mutex_lock(&card->ip_lock);

	list_क्रम_each_entry(ipatoe, &card->ipato.entries, entry) अणु
		अगर (ipatoe->proto != new->proto)
			जारी;
		अगर (!स_भेद(ipatoe->addr, new->addr,
			    (ipatoe->proto == QETH_PROT_IPV4) ? 4 : 16) &&
		    (ipatoe->mask_bits == new->mask_bits)) अणु
			rc = -EEXIST;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!rc) अणु
		list_add_tail(&new->entry, &card->ipato.entries);
		qeth_l3_update_ipato(card);
	पूर्ण

	mutex_unlock(&card->ip_lock);

	वापस rc;
पूर्ण

पूर्णांक qeth_l3_del_ipato_entry(काष्ठा qeth_card *card,
			    क्रमागत qeth_prot_versions proto, u8 *addr,
			    अचिन्हित पूर्णांक mask_bits)
अणु
	काष्ठा qeth_ipato_entry *ipatoe, *पंचांगp;
	पूर्णांक rc = -ENOENT;

	QETH_CARD_TEXT(card, 2, "delipato");

	mutex_lock(&card->ip_lock);

	list_क्रम_each_entry_safe(ipatoe, पंचांगp, &card->ipato.entries, entry) अणु
		अगर (ipatoe->proto != proto)
			जारी;
		अगर (!स_भेद(ipatoe->addr, addr,
			    (proto == QETH_PROT_IPV4) ? 4 : 16) &&
		    (ipatoe->mask_bits == mask_bits)) अणु
			list_del(&ipatoe->entry);
			qeth_l3_update_ipato(card);
			kमुक्त(ipatoe);
			rc = 0;
		पूर्ण
	पूर्ण

	mutex_unlock(&card->ip_lock);

	वापस rc;
पूर्ण

पूर्णांक qeth_l3_modअगरy_rxip_vipa(काष्ठा qeth_card *card, bool add, स्थिर u8 *ip,
			     क्रमागत qeth_ip_types type,
			     क्रमागत qeth_prot_versions proto)
अणु
	काष्ठा qeth_ipaddr addr;

	qeth_l3_init_ipaddr(&addr, type, proto);
	अगर (proto == QETH_PROT_IPV4)
		स_नकल(&addr.u.a4.addr, ip, 4);
	अन्यथा
		स_नकल(&addr.u.a6.addr, ip, 16);

	वापस qeth_l3_modअगरy_ip(card, &addr, add);
पूर्ण

पूर्णांक qeth_l3_modअगरy_hsuid(काष्ठा qeth_card *card, bool add)
अणु
	काष्ठा qeth_ipaddr addr;
	अचिन्हित पूर्णांक i;

	qeth_l3_init_ipaddr(&addr, QETH_IP_TYPE_NORMAL, QETH_PROT_IPV6);
	addr.u.a6.addr.s6_addr[0] = 0xfe;
	addr.u.a6.addr.s6_addr[1] = 0x80;
	क्रम (i = 0; i < 8; i++)
		addr.u.a6.addr.s6_addr[8+i] = card->options.hsuid[i];

	वापस qeth_l3_modअगरy_ip(card, &addr, add);
पूर्ण

अटल पूर्णांक qeth_l3_रेजिस्टर_addr_entry(काष्ठा qeth_card *card,
				काष्ठा qeth_ipaddr *addr)
अणु
	अक्षर buf[50];
	पूर्णांक rc = 0;
	पूर्णांक cnt = 3;

	अगर (card->options.snअगरfer)
		वापस 0;

	अगर (addr->proto == QETH_PROT_IPV4) अणु
		QETH_CARD_TEXT(card, 2, "setaddr4");
		QETH_CARD_HEX(card, 3, &addr->u.a4.addr, माप(पूर्णांक));
	पूर्ण अन्यथा अगर (addr->proto == QETH_PROT_IPV6) अणु
		QETH_CARD_TEXT(card, 2, "setaddr6");
		QETH_CARD_HEX(card, 3, &addr->u.a6.addr, 8);
		QETH_CARD_HEX(card, 3, ((अक्षर *)&addr->u.a6.addr) + 8, 8);
	पूर्ण अन्यथा अणु
		QETH_CARD_TEXT(card, 2, "setaddr?");
		QETH_CARD_HEX(card, 3, addr, माप(काष्ठा qeth_ipaddr));
	पूर्ण
	करो अणु
		अगर (addr->is_multicast)
			rc =  qeth_l3_send_setdelmc(card, addr, IPA_CMD_SETIPM);
		अन्यथा
			rc = qeth_l3_send_setdelip(card, addr, IPA_CMD_SETIP);
		अगर (rc)
			QETH_CARD_TEXT(card, 2, "failed");
	पूर्ण जबतक ((--cnt > 0) && rc);
	अगर (rc) अणु
		QETH_CARD_TEXT(card, 2, "FAILED");
		qeth_l3_ipaddr_to_string(addr->proto, (u8 *)&addr->u, buf);
		dev_warn(&card->gdev->dev,
			"Registering IP address %s failed\n", buf);
	पूर्ण
	वापस rc;
पूर्ण

अटल पूर्णांक qeth_l3_deरेजिस्टर_addr_entry(काष्ठा qeth_card *card,
						काष्ठा qeth_ipaddr *addr)
अणु
	पूर्णांक rc = 0;

	अगर (card->options.snअगरfer)
		वापस 0;

	अगर (addr->proto == QETH_PROT_IPV4) अणु
		QETH_CARD_TEXT(card, 2, "deladdr4");
		QETH_CARD_HEX(card, 3, &addr->u.a4.addr, माप(पूर्णांक));
	पूर्ण अन्यथा अगर (addr->proto == QETH_PROT_IPV6) अणु
		QETH_CARD_TEXT(card, 2, "deladdr6");
		QETH_CARD_HEX(card, 3, &addr->u.a6.addr, 8);
		QETH_CARD_HEX(card, 3, ((अक्षर *)&addr->u.a6.addr) + 8, 8);
	पूर्ण अन्यथा अणु
		QETH_CARD_TEXT(card, 2, "deladdr?");
		QETH_CARD_HEX(card, 3, addr, माप(काष्ठा qeth_ipaddr));
	पूर्ण
	अगर (addr->is_multicast)
		rc = qeth_l3_send_setdelmc(card, addr, IPA_CMD_DELIPM);
	अन्यथा
		rc = qeth_l3_send_setdelip(card, addr, IPA_CMD_DELIP);
	अगर (rc)
		QETH_CARD_TEXT(card, 2, "failed");

	वापस rc;
पूर्ण

अटल पूर्णांक qeth_l3_setadapter_parms(काष्ठा qeth_card *card)
अणु
	पूर्णांक rc = 0;

	QETH_CARD_TEXT(card, 2, "setadprm");

	अगर (qeth_adp_supported(card, IPA_SETADP_ALTER_MAC_ADDRESS)) अणु
		rc = qeth_setadpparms_change_macaddr(card);
		अगर (rc)
			dev_warn(&card->gdev->dev, "Reading the adapter MAC"
				" address failed\n");
	पूर्ण

	वापस rc;
पूर्ण

अटल पूर्णांक qeth_l3_start_ipa_arp_processing(काष्ठा qeth_card *card)
अणु
	पूर्णांक rc;

	QETH_CARD_TEXT(card, 3, "ipaarp");

	अगर (!qeth_is_supported(card, IPA_ARP_PROCESSING)) अणु
		dev_info(&card->gdev->dev,
			 "ARP processing not supported on %s!\n",
			 netdev_name(card->dev));
		वापस 0;
	पूर्ण
	rc = qeth_send_simple_setassparms(card, IPA_ARP_PROCESSING,
					  IPA_CMD_ASS_START, शून्य);
	अगर (rc) अणु
		dev_warn(&card->gdev->dev,
			 "Starting ARP processing support for %s failed\n",
			 netdev_name(card->dev));
	पूर्ण
	वापस rc;
पूर्ण

अटल पूर्णांक qeth_l3_start_ipa_source_mac(काष्ठा qeth_card *card)
अणु
	पूर्णांक rc;

	QETH_CARD_TEXT(card, 3, "stsrcmac");

	अगर (!qeth_is_supported(card, IPA_SOURCE_MAC)) अणु
		dev_info(&card->gdev->dev,
			 "Inbound source MAC-address not supported on %s\n",
			 netdev_name(card->dev));
		वापस -EOPNOTSUPP;
	पूर्ण

	rc = qeth_send_simple_setassparms(card, IPA_SOURCE_MAC,
					  IPA_CMD_ASS_START, शून्य);
	अगर (rc)
		dev_warn(&card->gdev->dev,
			 "Starting source MAC-address support for %s failed\n",
			 netdev_name(card->dev));
	वापस rc;
पूर्ण

अटल पूर्णांक qeth_l3_start_ipa_vlan(काष्ठा qeth_card *card)
अणु
	पूर्णांक rc = 0;

	QETH_CARD_TEXT(card, 3, "strtvlan");

	अगर (!qeth_is_supported(card, IPA_FULL_VLAN)) अणु
		dev_info(&card->gdev->dev,
			 "VLAN not supported on %s\n", netdev_name(card->dev));
		वापस -EOPNOTSUPP;
	पूर्ण

	rc = qeth_send_simple_setassparms(card, IPA_VLAN_PRIO,
					  IPA_CMD_ASS_START, शून्य);
	अगर (rc) अणु
		dev_warn(&card->gdev->dev,
			 "Starting VLAN support for %s failed\n",
			 netdev_name(card->dev));
	पूर्ण अन्यथा अणु
		dev_info(&card->gdev->dev, "VLAN enabled\n");
	पूर्ण
	वापस rc;
पूर्ण

अटल पूर्णांक qeth_l3_start_ipa_multicast(काष्ठा qeth_card *card)
अणु
	पूर्णांक rc;

	QETH_CARD_TEXT(card, 3, "stmcast");

	अगर (!qeth_is_supported(card, IPA_MULTICASTING)) अणु
		dev_info(&card->gdev->dev,
			 "Multicast not supported on %s\n",
			 netdev_name(card->dev));
		वापस -EOPNOTSUPP;
	पूर्ण

	rc = qeth_send_simple_setassparms(card, IPA_MULTICASTING,
					  IPA_CMD_ASS_START, शून्य);
	अगर (rc) अणु
		dev_warn(&card->gdev->dev,
			 "Starting multicast support for %s failed\n",
			 netdev_name(card->dev));
	पूर्ण अन्यथा अणु
		dev_info(&card->gdev->dev, "Multicast enabled\n");
		card->dev->flags |= IFF_MULTICAST;
	पूर्ण
	वापस rc;
पूर्ण

अटल पूर्णांक qeth_l3_softsetup_ipv6(काष्ठा qeth_card *card)
अणु
	u32 ipv6_data = 3;
	पूर्णांक rc;

	QETH_CARD_TEXT(card, 3, "softipv6");

	अगर (IS_IQD(card))
		जाओ out;

	rc = qeth_send_simple_setassparms(card, IPA_IPV6, IPA_CMD_ASS_START,
					  &ipv6_data);
	अगर (rc) अणु
		dev_err(&card->gdev->dev,
			"Activating IPv6 support for %s failed\n",
			netdev_name(card->dev));
		वापस rc;
	पूर्ण
	rc = qeth_send_simple_setassparms_v6(card, IPA_IPV6, IPA_CMD_ASS_START,
					     शून्य);
	अगर (rc) अणु
		dev_err(&card->gdev->dev,
			"Activating IPv6 support for %s failed\n",
			 netdev_name(card->dev));
		वापस rc;
	पूर्ण
	rc = qeth_send_simple_setassparms_v6(card, IPA_PASSTHRU,
					     IPA_CMD_ASS_START, शून्य);
	अगर (rc) अणु
		dev_warn(&card->gdev->dev,
			 "Enabling the passthrough mode for %s failed\n",
			 netdev_name(card->dev));
		वापस rc;
	पूर्ण
out:
	dev_info(&card->gdev->dev, "IPV6 enabled\n");
	वापस 0;
पूर्ण

अटल पूर्णांक qeth_l3_start_ipa_ipv6(काष्ठा qeth_card *card)
अणु
	QETH_CARD_TEXT(card, 3, "strtipv6");

	अगर (!qeth_is_supported(card, IPA_IPV6)) अणु
		dev_info(&card->gdev->dev,
			 "IPv6 not supported on %s\n", netdev_name(card->dev));
		वापस 0;
	पूर्ण
	वापस qeth_l3_softsetup_ipv6(card);
पूर्ण

अटल पूर्णांक qeth_l3_start_ipa_broadcast(काष्ठा qeth_card *card)
अणु
	u32 filter_data = 1;
	पूर्णांक rc;

	QETH_CARD_TEXT(card, 3, "stbrdcst");
	card->info.broadcast_capable = 0;
	अगर (!qeth_is_supported(card, IPA_FILTERING)) अणु
		dev_info(&card->gdev->dev,
			 "Broadcast not supported on %s\n",
			 netdev_name(card->dev));
		rc = -EOPNOTSUPP;
		जाओ out;
	पूर्ण
	rc = qeth_send_simple_setassparms(card, IPA_FILTERING,
					  IPA_CMD_ASS_START, शून्य);
	अगर (rc) अणु
		dev_warn(&card->gdev->dev,
			 "Enabling broadcast filtering for %s failed\n",
			 netdev_name(card->dev));
		जाओ out;
	पूर्ण

	rc = qeth_send_simple_setassparms(card, IPA_FILTERING,
					  IPA_CMD_ASS_CONFIGURE, &filter_data);
	अगर (rc) अणु
		dev_warn(&card->gdev->dev,
			 "Setting up broadcast filtering for %s failed\n",
			 netdev_name(card->dev));
		जाओ out;
	पूर्ण
	card->info.broadcast_capable = QETH_BROADCAST_WITH_ECHO;
	dev_info(&card->gdev->dev, "Broadcast enabled\n");
	rc = qeth_send_simple_setassparms(card, IPA_FILTERING,
					  IPA_CMD_ASS_ENABLE, &filter_data);
	अगर (rc) अणु
		dev_warn(&card->gdev->dev,
			 "Setting up broadcast echo filtering for %s failed\n",
			 netdev_name(card->dev));
		जाओ out;
	पूर्ण
	card->info.broadcast_capable = QETH_BROADCAST_WITHOUT_ECHO;
out:
	अगर (card->info.broadcast_capable)
		card->dev->flags |= IFF_BROADCAST;
	अन्यथा
		card->dev->flags &= ~IFF_BROADCAST;
	वापस rc;
पूर्ण

अटल व्योम qeth_l3_start_ipassists(काष्ठा qeth_card *card)
अणु
	QETH_CARD_TEXT(card, 3, "strtipas");

	qeth_l3_start_ipa_arp_processing(card);	/* go on*/
	qeth_l3_start_ipa_source_mac(card);	/* go on*/
	qeth_l3_start_ipa_vlan(card);		/* go on*/
	qeth_l3_start_ipa_multicast(card);		/* go on*/
	qeth_l3_start_ipa_ipv6(card);		/* go on*/
	qeth_l3_start_ipa_broadcast(card);		/* go on*/
पूर्ण

अटल पूर्णांक qeth_l3_iqd_पढ़ो_initial_mac_cb(काष्ठा qeth_card *card,
		काष्ठा qeth_reply *reply, अचिन्हित दीर्घ data)
अणु
	काष्ठा qeth_ipa_cmd *cmd = (काष्ठा qeth_ipa_cmd *) data;

	अगर (cmd->hdr.वापस_code)
		वापस -EIO;
	अगर (!is_valid_ether_addr(cmd->data.create_destroy_addr.mac_addr))
		वापस -EADDRNOTAVAIL;

	ether_addr_copy(card->dev->dev_addr,
			cmd->data.create_destroy_addr.mac_addr);
	वापस 0;
पूर्ण

अटल पूर्णांक qeth_l3_iqd_पढ़ो_initial_mac(काष्ठा qeth_card *card)
अणु
	पूर्णांक rc = 0;
	काष्ठा qeth_cmd_buffer *iob;

	QETH_CARD_TEXT(card, 2, "hsrmac");

	iob = qeth_ipa_alloc_cmd(card, IPA_CMD_CREATE_ADDR, QETH_PROT_IPV6,
				 IPA_DATA_SIZखातापूर्ण(create_destroy_addr));
	अगर (!iob)
		वापस -ENOMEM;

	rc = qeth_send_ipa_cmd(card, iob, qeth_l3_iqd_पढ़ो_initial_mac_cb,
				शून्य);
	वापस rc;
पूर्ण

अटल पूर्णांक qeth_l3_get_unique_id_cb(काष्ठा qeth_card *card,
		काष्ठा qeth_reply *reply, अचिन्हित दीर्घ data)
अणु
	काष्ठा qeth_ipa_cmd *cmd = (काष्ठा qeth_ipa_cmd *) data;
	u16 *uid = reply->param;

	अगर (cmd->hdr.वापस_code == 0) अणु
		*uid = cmd->data.create_destroy_addr.uid;
		वापस 0;
	पूर्ण

	dev_warn(&card->gdev->dev, "The network adapter failed to generate a unique ID\n");
	वापस -EIO;
पूर्ण

अटल u16 qeth_l3_get_unique_id(काष्ठा qeth_card *card, u16 uid)
अणु
	काष्ठा qeth_cmd_buffer *iob;

	QETH_CARD_TEXT(card, 2, "guniqeid");

	अगर (!qeth_is_supported(card, IPA_IPV6))
		जाओ out;

	iob = qeth_ipa_alloc_cmd(card, IPA_CMD_CREATE_ADDR, QETH_PROT_IPV6,
				 IPA_DATA_SIZखातापूर्ण(create_destroy_addr));
	अगर (!iob)
		जाओ out;

	__ipa_cmd(iob)->data.create_destroy_addr.uid = uid;
	qeth_send_ipa_cmd(card, iob, qeth_l3_get_unique_id_cb, &uid);

out:
	वापस uid;
पूर्ण

अटल पूर्णांक
qeth_diags_trace_cb(काष्ठा qeth_card *card, काष्ठा qeth_reply *reply,
			    अचिन्हित दीर्घ data)
अणु
	काष्ठा qeth_ipa_cmd	   *cmd;
	__u16 rc;

	QETH_CARD_TEXT(card, 2, "diastrcb");

	cmd = (काष्ठा qeth_ipa_cmd *)data;
	rc = cmd->hdr.वापस_code;
	अगर (rc)
		QETH_CARD_TEXT_(card, 2, "dxter%x", rc);
	चयन (cmd->data.diagass.action) अणु
	हाल QETH_DIAGS_CMD_TRACE_QUERY:
		अवरोध;
	हाल QETH_DIAGS_CMD_TRACE_DISABLE:
		चयन (rc) अणु
		हाल 0:
		हाल IPA_RC_INVALID_SUBCMD:
			card->info.promisc_mode = SET_PROMISC_MODE_OFF;
			dev_info(&card->gdev->dev, "The HiperSockets network "
				"traffic analyzer is deactivated\n");
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;
	हाल QETH_DIAGS_CMD_TRACE_ENABLE:
		चयन (rc) अणु
		हाल 0:
			card->info.promisc_mode = SET_PROMISC_MODE_ON;
			dev_info(&card->gdev->dev, "The HiperSockets network "
				"traffic analyzer is activated\n");
			अवरोध;
		हाल IPA_RC_HARDWARE_AUTH_ERROR:
			dev_warn(&card->gdev->dev, "The device is not "
				"authorized to run as a HiperSockets network "
				"traffic analyzer\n");
			अवरोध;
		हाल IPA_RC_TRACE_ALREADY_ACTIVE:
			dev_warn(&card->gdev->dev, "A HiperSockets "
				"network traffic analyzer is already "
				"active in the HiperSockets LAN\n");
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;
	शेष:
		QETH_DBF_MESSAGE(2, "Unknown sniffer action (%#06x) on device %x\n",
				 cmd->data.diagass.action, CARD_DEVID(card));
	पूर्ण

	वापस rc ? -EIO : 0;
पूर्ण

अटल पूर्णांक
qeth_diags_trace(काष्ठा qeth_card *card, क्रमागत qeth_diags_trace_cmds diags_cmd)
अणु
	काष्ठा qeth_cmd_buffer *iob;
	काष्ठा qeth_ipa_cmd    *cmd;

	QETH_CARD_TEXT(card, 2, "diagtrac");

	iob = qeth_get_diag_cmd(card, QETH_DIAGS_CMD_TRACE, 0);
	अगर (!iob)
		वापस -ENOMEM;
	cmd = __ipa_cmd(iob);
	cmd->data.diagass.type = QETH_DIAGS_TYPE_HIPERSOCKET;
	cmd->data.diagass.action = diags_cmd;
	वापस qeth_send_ipa_cmd(card, iob, qeth_diags_trace_cb, शून्य);
पूर्ण

अटल पूर्णांक qeth_l3_add_mcast_rtnl(काष्ठा net_device *dev, पूर्णांक vid, व्योम *arg)
अणु
	काष्ठा qeth_card *card = arg;
	काष्ठा inet6_dev *in6_dev;
	काष्ठा in_device *in4_dev;
	काष्ठा qeth_ipaddr *ipm;
	काष्ठा qeth_ipaddr पंचांगp;
	काष्ठा ip_mc_list *im4;
	काष्ठा अगरmcaddr6 *im6;

	QETH_CARD_TEXT(card, 4, "addmc");

	अगर (!dev || !(dev->flags & IFF_UP))
		जाओ out;

	in4_dev = __in_dev_get_rtnl(dev);
	अगर (!in4_dev)
		जाओ walk_ipv6;

	qeth_l3_init_ipaddr(&पंचांगp, QETH_IP_TYPE_NORMAL, QETH_PROT_IPV4);
	पंचांगp.disp_flag = QETH_DISP_ADDR_ADD;
	पंचांगp.is_multicast = 1;

	क्रम (im4 = rtnl_dereference(in4_dev->mc_list); im4 != शून्य;
	     im4 = rtnl_dereference(im4->next_rcu)) अणु
		पंचांगp.u.a4.addr = im4->multiaddr;

		ipm = qeth_l3_find_addr_by_ip(card, &पंचांगp);
		अगर (ipm) अणु
			/* क्रम mcast, by-IP match means full match */
			ipm->disp_flag = QETH_DISP_ADDR_DO_NOTHING;
			जारी;
		पूर्ण

		ipm = kmemdup(&पंचांगp, माप(पंचांगp), GFP_KERNEL);
		अगर (!ipm)
			जारी;

		hash_add(card->rx_mode_addrs, &ipm->hnode,
			 qeth_l3_ipaddr_hash(ipm));
	पूर्ण

walk_ipv6:
	अगर (!qeth_is_supported(card, IPA_IPV6))
		जाओ out;

	in6_dev = __in6_dev_get(dev);
	अगर (!in6_dev)
		जाओ out;

	qeth_l3_init_ipaddr(&पंचांगp, QETH_IP_TYPE_NORMAL, QETH_PROT_IPV6);
	पंचांगp.disp_flag = QETH_DISP_ADDR_ADD;
	पंचांगp.is_multicast = 1;

	क्रम (im6 = rtnl_dereference(in6_dev->mc_list);
	     im6;
	     im6 = rtnl_dereference(im6->next)) अणु
		पंचांगp.u.a6.addr = im6->mca_addr;

		ipm = qeth_l3_find_addr_by_ip(card, &पंचांगp);
		अगर (ipm) अणु
			/* क्रम mcast, by-IP match means full match */
			ipm->disp_flag = QETH_DISP_ADDR_DO_NOTHING;
			जारी;
		पूर्ण

		ipm = kmemdup(&पंचांगp, माप(पंचांगp), GFP_ATOMIC);
		अगर (!ipm)
			जारी;

		hash_add(card->rx_mode_addrs, &ipm->hnode,
			 qeth_l3_ipaddr_hash(ipm));

	पूर्ण

out:
	वापस 0;
पूर्ण

अटल व्योम qeth_l3_set_promisc_mode(काष्ठा qeth_card *card)
अणु
	bool enable = card->dev->flags & IFF_PROMISC;

	अगर (card->info.promisc_mode == enable)
		वापस;

	अगर (IS_VM_NIC(card)) अणु		/* Guestlan trace */
		अगर (qeth_adp_supported(card, IPA_SETADP_SET_PROMISC_MODE))
			qeth_setadp_promisc_mode(card, enable);
	पूर्ण अन्यथा अगर (card->options.snअगरfer &&	/* HiperSockets trace */
		   qeth_adp_supported(card, IPA_SETADP_SET_DIAG_ASSIST)) अणु
		अगर (enable) अणु
			QETH_CARD_TEXT(card, 3, "+promisc");
			qeth_diags_trace(card, QETH_DIAGS_CMD_TRACE_ENABLE);
		पूर्ण अन्यथा अणु
			QETH_CARD_TEXT(card, 3, "-promisc");
			qeth_diags_trace(card, QETH_DIAGS_CMD_TRACE_DISABLE);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम qeth_l3_rx_mode_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा qeth_card *card = container_of(work, काष्ठा qeth_card,
					      rx_mode_work);
	काष्ठा qeth_ipaddr *addr;
	काष्ठा hlist_node *पंचांगp;
	पूर्णांक i, rc;

	QETH_CARD_TEXT(card, 3, "setmulti");

	अगर (!card->options.snअगरfer) अणु
		rtnl_lock();
		qeth_l3_add_mcast_rtnl(card->dev, 0, card);
		अगर (qeth_is_supported(card, IPA_FULL_VLAN))
			vlan_क्रम_each(card->dev, qeth_l3_add_mcast_rtnl, card);
		rtnl_unlock();

		hash_क्रम_each_safe(card->rx_mode_addrs, i, पंचांगp, addr, hnode) अणु
			चयन (addr->disp_flag) अणु
			हाल QETH_DISP_ADDR_DELETE:
				rc = qeth_l3_deरेजिस्टर_addr_entry(card, addr);
				अगर (!rc || rc == -ENOENT) अणु
					hash_del(&addr->hnode);
					kमुक्त(addr);
				पूर्ण
				अवरोध;
			हाल QETH_DISP_ADDR_ADD:
				rc = qeth_l3_रेजिस्टर_addr_entry(card, addr);
				अगर (rc && rc != -ENETDOWN) अणु
					hash_del(&addr->hnode);
					kमुक्त(addr);
					अवरोध;
				पूर्ण
				fallthrough;
			शेष:
				/* क्रम next call to set_rx_mode(): */
				addr->disp_flag = QETH_DISP_ADDR_DELETE;
			पूर्ण
		पूर्ण
	पूर्ण

	qeth_l3_set_promisc_mode(card);
पूर्ण

अटल पूर्णांक qeth_l3_arp_makerc(u16 rc)
अणु
	चयन (rc) अणु
	हाल IPA_RC_SUCCESS:
		वापस 0;
	हाल QETH_IPA_ARP_RC_NOTSUPP:
	हाल QETH_IPA_ARP_RC_Q_NOTSUPP:
		वापस -EOPNOTSUPP;
	हाल QETH_IPA_ARP_RC_OUT_OF_RANGE:
		वापस -EINVAL;
	हाल QETH_IPA_ARP_RC_Q_NO_DATA:
		वापस -ENOENT;
	शेष:
		वापस -EIO;
	पूर्ण
पूर्ण

अटल पूर्णांक qeth_l3_arp_cmd_cb(काष्ठा qeth_card *card, काष्ठा qeth_reply *reply,
			      अचिन्हित दीर्घ data)
अणु
	काष्ठा qeth_ipa_cmd *cmd = (काष्ठा qeth_ipa_cmd *) data;

	qeth_setassparms_cb(card, reply, data);
	वापस qeth_l3_arp_makerc(cmd->hdr.वापस_code);
पूर्ण

अटल पूर्णांक qeth_l3_arp_set_no_entries(काष्ठा qeth_card *card, पूर्णांक no_entries)
अणु
	काष्ठा qeth_cmd_buffer *iob;
	पूर्णांक rc;

	QETH_CARD_TEXT(card, 3, "arpstnoe");

	/*
	 * currently GuestLAN only supports the ARP assist function
	 * IPA_CMD_ASS_ARP_QUERY_INFO, but not IPA_CMD_ASS_ARP_SET_NO_ENTRIES;
	 * thus we say EOPNOTSUPP क्रम this ARP function
	 */
	अगर (IS_VM_NIC(card))
		वापस -EOPNOTSUPP;
	अगर (!qeth_is_supported(card, IPA_ARP_PROCESSING)) अणु
		वापस -EOPNOTSUPP;
	पूर्ण

	iob = qeth_get_setassparms_cmd(card, IPA_ARP_PROCESSING,
				       IPA_CMD_ASS_ARP_SET_NO_ENTRIES,
				       SETASS_DATA_SIZखातापूर्ण(flags_32bit),
				       QETH_PROT_IPV4);
	अगर (!iob)
		वापस -ENOMEM;

	__ipa_cmd(iob)->data.setassparms.data.flags_32bit = (u32) no_entries;
	rc = qeth_send_ipa_cmd(card, iob, qeth_l3_arp_cmd_cb, शून्य);
	अगर (rc)
		QETH_DBF_MESSAGE(2, "Could not set number of ARP entries on device %x: %#x\n",
				 CARD_DEVID(card), rc);
	वापस rc;
पूर्ण

अटल __u32 get_arp_entry_size(काष्ठा qeth_card *card,
			काष्ठा qeth_arp_query_data *qdata,
			काष्ठा qeth_arp_entrytype *type, __u8 strip_entries)
अणु
	__u32 rc;
	__u8 is_hsi;

	is_hsi = qdata->reply_bits == 5;
	अगर (type->ip == QETHARP_IP_ADDR_V4) अणु
		QETH_CARD_TEXT(card, 4, "arpev4");
		अगर (strip_entries) अणु
			rc = is_hsi ? माप(काष्ठा qeth_arp_qi_entry5_लघु) :
				माप(काष्ठा qeth_arp_qi_entry7_लघु);
		पूर्ण अन्यथा अणु
			rc = is_hsi ? माप(काष्ठा qeth_arp_qi_entry5) :
				माप(काष्ठा qeth_arp_qi_entry7);
		पूर्ण
	पूर्ण अन्यथा अगर (type->ip == QETHARP_IP_ADDR_V6) अणु
		QETH_CARD_TEXT(card, 4, "arpev6");
		अगर (strip_entries) अणु
			rc = is_hsi ?
				माप(काष्ठा qeth_arp_qi_entry5_लघु_ipv6) :
				माप(काष्ठा qeth_arp_qi_entry7_लघु_ipv6);
		पूर्ण अन्यथा अणु
			rc = is_hsi ?
				माप(काष्ठा qeth_arp_qi_entry5_ipv6) :
				माप(काष्ठा qeth_arp_qi_entry7_ipv6);
		पूर्ण
	पूर्ण अन्यथा अणु
		QETH_CARD_TEXT(card, 4, "arpinv");
		rc = 0;
	पूर्ण

	वापस rc;
पूर्ण

अटल पूर्णांक arpentry_matches_prot(काष्ठा qeth_arp_entrytype *type, __u16 prot)
अणु
	वापस (type->ip == QETHARP_IP_ADDR_V4 && prot == QETH_PROT_IPV4) ||
		(type->ip == QETHARP_IP_ADDR_V6 && prot == QETH_PROT_IPV6);
पूर्ण

अटल पूर्णांक qeth_l3_arp_query_cb(काष्ठा qeth_card *card,
		काष्ठा qeth_reply *reply, अचिन्हित दीर्घ data)
अणु
	काष्ठा qeth_ipa_cmd *cmd;
	काष्ठा qeth_arp_query_data *qdata;
	काष्ठा qeth_arp_query_info *qinfo;
	पूर्णांक e;
	पूर्णांक entrybytes_करोne;
	पूर्णांक stripped_bytes;
	__u8 करो_strip_entries;

	QETH_CARD_TEXT(card, 3, "arpquecb");

	qinfo = (काष्ठा qeth_arp_query_info *) reply->param;
	cmd = (काष्ठा qeth_ipa_cmd *) data;
	QETH_CARD_TEXT_(card, 4, "%i", cmd->hdr.prot_version);
	अगर (cmd->hdr.वापस_code) अणु
		QETH_CARD_TEXT(card, 4, "arpcberr");
		QETH_CARD_TEXT_(card, 4, "%i", cmd->hdr.वापस_code);
		वापस qeth_l3_arp_makerc(cmd->hdr.वापस_code);
	पूर्ण
	अगर (cmd->data.setassparms.hdr.वापस_code) अणु
		cmd->hdr.वापस_code = cmd->data.setassparms.hdr.वापस_code;
		QETH_CARD_TEXT(card, 4, "setaperr");
		QETH_CARD_TEXT_(card, 4, "%i", cmd->hdr.वापस_code);
		वापस qeth_l3_arp_makerc(cmd->hdr.वापस_code);
	पूर्ण
	qdata = &cmd->data.setassparms.data.query_arp;
	QETH_CARD_TEXT_(card, 4, "anoen%i", qdata->no_entries);

	करो_strip_entries = (qinfo->mask_bits & QETH_QARP_STRIP_ENTRIES) > 0;
	stripped_bytes = करो_strip_entries ? QETH_QARP_MEDIASPECIFIC_BYTES : 0;
	entrybytes_करोne = 0;
	क्रम (e = 0; e < qdata->no_entries; ++e) अणु
		अक्षर *cur_entry;
		__u32 esize;
		काष्ठा qeth_arp_entrytype *etype;

		cur_entry = &qdata->data + entrybytes_करोne;
		etype = &((काष्ठा qeth_arp_qi_entry5 *) cur_entry)->type;
		अगर (!arpentry_matches_prot(etype, cmd->hdr.prot_version)) अणु
			QETH_CARD_TEXT(card, 4, "pmis");
			QETH_CARD_TEXT_(card, 4, "%i", etype->ip);
			अवरोध;
		पूर्ण
		esize = get_arp_entry_size(card, qdata, etype,
			करो_strip_entries);
		QETH_CARD_TEXT_(card, 5, "esz%i", esize);
		अगर (!esize)
			अवरोध;

		अगर ((qinfo->udata_len - qinfo->udata_offset) < esize) अणु
			QETH_CARD_TEXT_(card, 4, "qaer3%i", -ENOSPC);
			स_रखो(qinfo->udata, 0, 4);
			वापस -ENOSPC;
		पूर्ण

		स_नकल(qinfo->udata + qinfo->udata_offset,
			&qdata->data + entrybytes_करोne + stripped_bytes,
			esize);
		entrybytes_करोne += esize + stripped_bytes;
		qinfo->udata_offset += esize;
		++qinfo->no_entries;
	पूर्ण
	/* check अगर all replies received ... */
	अगर (cmd->data.setassparms.hdr.seq_no <
	    cmd->data.setassparms.hdr.number_of_replies)
		वापस 1;
	QETH_CARD_TEXT_(card, 4, "nove%i", qinfo->no_entries);
	स_नकल(qinfo->udata, &qinfo->no_entries, 4);
	/* keep STRIP_ENTRIES flag so the user program can distinguish
	 * stripped entries from normal ones */
	अगर (qinfo->mask_bits & QETH_QARP_STRIP_ENTRIES)
		qdata->reply_bits |= QETH_QARP_STRIP_ENTRIES;
	स_नकल(qinfo->udata + QETH_QARP_MASK_OFFSET, &qdata->reply_bits, 2);
	QETH_CARD_TEXT_(card, 4, "rc%i", 0);
	वापस 0;
पूर्ण

अटल पूर्णांक qeth_l3_query_arp_cache_info(काष्ठा qeth_card *card,
	क्रमागत qeth_prot_versions prot,
	काष्ठा qeth_arp_query_info *qinfo)
अणु
	काष्ठा qeth_cmd_buffer *iob;
	काष्ठा qeth_ipa_cmd *cmd;
	पूर्णांक rc;

	QETH_CARD_TEXT_(card, 3, "qarpipv%i", prot);

	iob = qeth_get_setassparms_cmd(card, IPA_ARP_PROCESSING,
				       IPA_CMD_ASS_ARP_QUERY_INFO,
				       SETASS_DATA_SIZखातापूर्ण(query_arp), prot);
	अगर (!iob)
		वापस -ENOMEM;
	cmd = __ipa_cmd(iob);
	cmd->data.setassparms.data.query_arp.request_bits = 0x000F;
	rc = qeth_send_ipa_cmd(card, iob, qeth_l3_arp_query_cb, qinfo);
	अगर (rc)
		QETH_DBF_MESSAGE(2, "Error while querying ARP cache on device %x: %#x\n",
				 CARD_DEVID(card), rc);
	वापस rc;
पूर्ण

अटल पूर्णांक qeth_l3_arp_query(काष्ठा qeth_card *card, अक्षर __user *udata)
अणु
	काष्ठा qeth_arp_query_info qinfo = अणु0, पूर्ण;
	पूर्णांक rc;

	QETH_CARD_TEXT(card, 3, "arpquery");

	अगर (!qeth_is_supported(card,/*IPA_QUERY_ARP_ADDR_INFO*/
			       IPA_ARP_PROCESSING)) अणु
		QETH_CARD_TEXT(card, 3, "arpqnsup");
		rc = -EOPNOTSUPP;
		जाओ out;
	पूर्ण
	/* get size of userspace buffer and mask_bits -> 6 bytes */
	अगर (copy_from_user(&qinfo, udata, 6)) अणु
		rc = -EFAULT;
		जाओ out;
	पूर्ण
	qinfo.udata = kzalloc(qinfo.udata_len, GFP_KERNEL);
	अगर (!qinfo.udata) अणु
		rc = -ENOMEM;
		जाओ out;
	पूर्ण
	qinfo.udata_offset = QETH_QARP_ENTRIES_OFFSET;
	rc = qeth_l3_query_arp_cache_info(card, QETH_PROT_IPV4, &qinfo);
	अगर (rc) अणु
		अगर (copy_to_user(udata, qinfo.udata, 4))
			rc = -EFAULT;
		जाओ मुक्त_and_out;
	पूर्ण
	अगर (qinfo.mask_bits & QETH_QARP_WITH_IPV6) अणु
		/* fails in हाल of GuestLAN QDIO mode */
		qeth_l3_query_arp_cache_info(card, QETH_PROT_IPV6, &qinfo);
	पूर्ण
	अगर (copy_to_user(udata, qinfo.udata, qinfo.udata_len)) अणु
		QETH_CARD_TEXT(card, 4, "qactf");
		rc = -EFAULT;
		जाओ मुक्त_and_out;
	पूर्ण
	QETH_CARD_TEXT(card, 4, "qacts");

मुक्त_and_out:
	kमुक्त(qinfo.udata);
out:
	वापस rc;
पूर्ण

अटल पूर्णांक qeth_l3_arp_modअगरy_entry(काष्ठा qeth_card *card,
				    काष्ठा qeth_arp_cache_entry *entry,
				    क्रमागत qeth_arp_process_subcmds arp_cmd)
अणु
	काष्ठा qeth_arp_cache_entry *cmd_entry;
	काष्ठा qeth_cmd_buffer *iob;
	पूर्णांक rc;

	अगर (arp_cmd == IPA_CMD_ASS_ARP_ADD_ENTRY)
		QETH_CARD_TEXT(card, 3, "arpadd");
	अन्यथा
		QETH_CARD_TEXT(card, 3, "arpdel");

	/*
	 * currently GuestLAN only supports the ARP assist function
	 * IPA_CMD_ASS_ARP_QUERY_INFO, but not IPA_CMD_ASS_ARP_ADD_ENTRY;
	 * thus we say EOPNOTSUPP क्रम this ARP function
	 */
	अगर (IS_VM_NIC(card))
		वापस -EOPNOTSUPP;
	अगर (!qeth_is_supported(card, IPA_ARP_PROCESSING)) अणु
		वापस -EOPNOTSUPP;
	पूर्ण

	iob = qeth_get_setassparms_cmd(card, IPA_ARP_PROCESSING, arp_cmd,
				       SETASS_DATA_SIZखातापूर्ण(arp_entry),
				       QETH_PROT_IPV4);
	अगर (!iob)
		वापस -ENOMEM;

	cmd_entry = &__ipa_cmd(iob)->data.setassparms.data.arp_entry;
	ether_addr_copy(cmd_entry->macaddr, entry->macaddr);
	स_नकल(cmd_entry->ipaddr, entry->ipaddr, 4);
	rc = qeth_send_ipa_cmd(card, iob, qeth_l3_arp_cmd_cb, शून्य);
	अगर (rc)
		QETH_DBF_MESSAGE(2, "Could not modify (cmd: %#x) ARP entry on device %x: %#x\n",
				 arp_cmd, CARD_DEVID(card), rc);
	वापस rc;
पूर्ण

अटल पूर्णांक qeth_l3_arp_flush_cache(काष्ठा qeth_card *card)
अणु
	काष्ठा qeth_cmd_buffer *iob;
	पूर्णांक rc;

	QETH_CARD_TEXT(card, 3, "arpflush");

	/*
	 * currently GuestLAN only supports the ARP assist function
	 * IPA_CMD_ASS_ARP_QUERY_INFO, but not IPA_CMD_ASS_ARP_FLUSH_CACHE;
	 * thus we say EOPNOTSUPP क्रम this ARP function
	*/
	अगर (IS_VM_NIC(card) || IS_IQD(card))
		वापस -EOPNOTSUPP;
	अगर (!qeth_is_supported(card, IPA_ARP_PROCESSING)) अणु
		वापस -EOPNOTSUPP;
	पूर्ण

	iob = qeth_get_setassparms_cmd(card, IPA_ARP_PROCESSING,
				       IPA_CMD_ASS_ARP_FLUSH_CACHE, 0,
				       QETH_PROT_IPV4);
	अगर (!iob)
		वापस -ENOMEM;

	rc = qeth_send_ipa_cmd(card, iob, qeth_l3_arp_cmd_cb, शून्य);
	अगर (rc)
		QETH_DBF_MESSAGE(2, "Could not flush ARP cache on device %x: %#x\n",
				 CARD_DEVID(card), rc);
	वापस rc;
पूर्ण

अटल पूर्णांक qeth_l3_करो_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *rq, पूर्णांक cmd)
अणु
	काष्ठा qeth_card *card = dev->ml_priv;
	काष्ठा qeth_arp_cache_entry arp_entry;
	क्रमागत qeth_arp_process_subcmds arp_cmd;
	पूर्णांक rc = 0;

	चयन (cmd) अणु
	हाल SIOC_QETH_ARP_SET_NO_ENTRIES:
		अगर (!capable(CAP_NET_ADMIN)) अणु
			rc = -EPERM;
			अवरोध;
		पूर्ण
		rc = qeth_l3_arp_set_no_entries(card, rq->अगरr_अगरru.अगरru_ivalue);
		अवरोध;
	हाल SIOC_QETH_ARP_QUERY_INFO:
		अगर (!capable(CAP_NET_ADMIN)) अणु
			rc = -EPERM;
			अवरोध;
		पूर्ण
		rc = qeth_l3_arp_query(card, rq->अगरr_अगरru.अगरru_data);
		अवरोध;
	हाल SIOC_QETH_ARP_ADD_ENTRY:
	हाल SIOC_QETH_ARP_REMOVE_ENTRY:
		अगर (!capable(CAP_NET_ADMIN))
			वापस -EPERM;
		अगर (copy_from_user(&arp_entry, rq->अगरr_data, माप(arp_entry)))
			वापस -EFAULT;

		arp_cmd = (cmd == SIOC_QETH_ARP_ADD_ENTRY) ?
				IPA_CMD_ASS_ARP_ADD_ENTRY :
				IPA_CMD_ASS_ARP_REMOVE_ENTRY;
		वापस qeth_l3_arp_modअगरy_entry(card, &arp_entry, arp_cmd);
	हाल SIOC_QETH_ARP_FLUSH_CACHE:
		अगर (!capable(CAP_NET_ADMIN)) अणु
			rc = -EPERM;
			अवरोध;
		पूर्ण
		rc = qeth_l3_arp_flush_cache(card);
		अवरोध;
	शेष:
		rc = -EOPNOTSUPP;
	पूर्ण
	वापस rc;
पूर्ण

अटल पूर्णांक qeth_l3_get_cast_type_rcu(काष्ठा sk_buff *skb, काष्ठा dst_entry *dst,
				     __be16 proto)
अणु
	काष्ठा neighbour *n = शून्य;

	अगर (dst)
		n = dst_neigh_lookup_skb(dst, skb);

	अगर (n) अणु
		पूर्णांक cast_type = n->type;

		neigh_release(n);
		अगर ((cast_type == RTN_BROADCAST) ||
		    (cast_type == RTN_MULTICAST) ||
		    (cast_type == RTN_ANYCAST))
			वापस cast_type;
		वापस RTN_UNICAST;
	पूर्ण

	/* no neighbour (eg AF_PACKET), fall back to target's IP address ... */
	चयन (proto) अणु
	हाल htons(ETH_P_IP):
		अगर (ipv4_is_lbcast(ip_hdr(skb)->daddr))
			वापस RTN_BROADCAST;
		वापस ipv4_is_multicast(ip_hdr(skb)->daddr) ?
				RTN_MULTICAST : RTN_UNICAST;
	हाल htons(ETH_P_IPV6):
		वापस ipv6_addr_is_multicast(&ipv6_hdr(skb)->daddr) ?
				RTN_MULTICAST : RTN_UNICAST;
	हाल htons(ETH_P_AF_IUCV):
		वापस RTN_UNICAST;
	शेष:
		/* OSA only: ... and MAC address */
		वापस qeth_get_ether_cast_type(skb);
	पूर्ण
पूर्ण

अटल पूर्णांक qeth_l3_get_cast_type(काष्ठा sk_buff *skb, __be16 proto)
अणु
	काष्ठा dst_entry *dst;
	पूर्णांक cast_type;

	rcu_पढ़ो_lock();
	dst = qeth_dst_check_rcu(skb, proto);
	cast_type = qeth_l3_get_cast_type_rcu(skb, dst, proto);
	rcu_पढ़ो_unlock();

	वापस cast_type;
पूर्ण

अटल u8 qeth_l3_cast_type_to_flag(पूर्णांक cast_type)
अणु
	अगर (cast_type == RTN_MULTICAST)
		वापस QETH_CAST_MULTICAST;
	अगर (cast_type == RTN_ANYCAST)
		वापस QETH_CAST_ANYCAST;
	अगर (cast_type == RTN_BROADCAST)
		वापस QETH_CAST_BROADCAST;
	वापस QETH_CAST_UNICAST;
पूर्ण

अटल व्योम qeth_l3_fill_header(काष्ठा qeth_qdio_out_q *queue,
				काष्ठा qeth_hdr *hdr, काष्ठा sk_buff *skb,
				__be16 proto, अचिन्हित पूर्णांक data_len)
अणु
	काष्ठा qeth_hdr_layer3 *l3_hdr = &hdr->hdr.l3;
	काष्ठा vlan_ethhdr *veth = vlan_eth_hdr(skb);
	काष्ठा qeth_card *card = queue->card;
	काष्ठा dst_entry *dst;
	पूर्णांक cast_type;

	hdr->hdr.l3.length = data_len;

	अगर (skb_is_gso(skb)) अणु
		hdr->hdr.l3.id = QETH_HEADER_TYPE_L3_TSO;
	पूर्ण अन्यथा अणु
		hdr->hdr.l3.id = QETH_HEADER_TYPE_LAYER3;

		अगर (skb->ip_summed == CHECKSUM_PARTIAL) अणु
			qeth_tx_csum(skb, &hdr->hdr.l3.ext_flags, proto);
			/* some HW requires combined L3+L4 csum offload: */
			अगर (proto == htons(ETH_P_IP))
				hdr->hdr.l3.ext_flags |= QETH_HDR_EXT_CSUM_HDR_REQ;
		पूर्ण
	पूर्ण

	अगर (proto == htons(ETH_P_IP) || IS_IQD(card)) अणु
		/* NETIF_F_HW_VLAN_CTAG_TX */
		अगर (skb_vlan_tag_present(skb)) अणु
			hdr->hdr.l3.ext_flags |= QETH_HDR_EXT_VLAN_FRAME;
			hdr->hdr.l3.vlan_id = skb_vlan_tag_get(skb);
		पूर्ण
	पूर्ण अन्यथा अगर (veth->h_vlan_proto == htons(ETH_P_8021Q)) अणु
		hdr->hdr.l3.ext_flags |= QETH_HDR_EXT_INCLUDE_VLAN_TAG;
		hdr->hdr.l3.vlan_id = ntohs(veth->h_vlan_TCI);
	पूर्ण

	rcu_पढ़ो_lock();
	dst = qeth_dst_check_rcu(skb, proto);

	अगर (IS_IQD(card) && skb_get_queue_mapping(skb) != QETH_IQD_MCAST_TXQ)
		cast_type = RTN_UNICAST;
	अन्यथा
		cast_type = qeth_l3_get_cast_type_rcu(skb, dst, proto);
	l3_hdr->flags |= qeth_l3_cast_type_to_flag(cast_type);

	चयन (proto) अणु
	हाल htons(ETH_P_IP):
		l3_hdr->next_hop.addr.s6_addr32[3] =
					qeth_next_hop_v4_rcu(skb, dst);
		अवरोध;
	हाल htons(ETH_P_IPV6):
		l3_hdr->next_hop.addr = *qeth_next_hop_v6_rcu(skb, dst);

		hdr->hdr.l3.flags |= QETH_HDR_IPV6;
		अगर (!IS_IQD(card))
			hdr->hdr.l3.flags |= QETH_HDR_PASSTHRU;
		अवरोध;
	हाल htons(ETH_P_AF_IUCV):
		l3_hdr->next_hop.addr.s6_addr16[0] = htons(0xfe80);
		स_नकल(&l3_hdr->next_hop.addr.s6_addr32[2],
		       iucv_trans_hdr(skb)->destUserID, 8);
		l3_hdr->flags |= QETH_HDR_IPV6;
		अवरोध;
	शेष:
		/* OSA only: */
		l3_hdr->flags |= QETH_HDR_PASSTHRU;
	पूर्ण
	rcu_पढ़ो_unlock();
पूर्ण

अटल व्योम qeth_l3_fixup_headers(काष्ठा sk_buff *skb)
अणु
	काष्ठा iphdr *iph = ip_hdr(skb);

	/* this is safe, IPv6 traffic takes a dअगरferent path */
	अगर (skb->ip_summed == CHECKSUM_PARTIAL)
		iph->check = 0;
	अगर (skb_is_gso(skb)) अणु
		iph->tot_len = 0;
		tcp_hdr(skb)->check = ~tcp_v4_check(0, iph->saddr,
						    iph->daddr, 0);
	पूर्ण
पूर्ण

अटल पूर्णांक qeth_l3_xmit(काष्ठा qeth_card *card, काष्ठा sk_buff *skb,
			काष्ठा qeth_qdio_out_q *queue, __be16 proto)
अणु
	अचिन्हित पूर्णांक hw_hdr_len;
	पूर्णांक rc;

	/* re-use the L2 header area क्रम the HW header: */
	hw_hdr_len = skb_is_gso(skb) ? माप(काष्ठा qeth_hdr_tso) :
				       माप(काष्ठा qeth_hdr);
	rc = skb_cow_head(skb, hw_hdr_len - ETH_HLEN);
	अगर (rc)
		वापस rc;
	skb_pull(skb, ETH_HLEN);

	qeth_l3_fixup_headers(skb);
	वापस qeth_xmit(card, skb, queue, proto, qeth_l3_fill_header);
पूर्ण

अटल netdev_tx_t qeth_l3_hard_start_xmit(काष्ठा sk_buff *skb,
					   काष्ठा net_device *dev)
अणु
	काष्ठा qeth_card *card = dev->ml_priv;
	__be16 proto = vlan_get_protocol(skb);
	u16 txq = skb_get_queue_mapping(skb);
	काष्ठा qeth_qdio_out_q *queue;
	पूर्णांक rc;

	अगर (!skb_is_gso(skb))
		qdisc_skb_cb(skb)->pkt_len = skb->len;
	अगर (IS_IQD(card)) अणु
		queue = card->qdio.out_qs[qeth_iqd_translate_txq(dev, txq)];

		अगर (card->options.snअगरfer)
			जाओ tx_drop;

		चयन (proto) अणु
		हाल htons(ETH_P_AF_IUCV):
			अगर (card->options.cq != QETH_CQ_ENABLED)
				जाओ tx_drop;
			अवरोध;
		हाल htons(ETH_P_IP):
		हाल htons(ETH_P_IPV6):
			अगर (card->options.cq == QETH_CQ_ENABLED)
				जाओ tx_drop;
			अवरोध;
		शेष:
			जाओ tx_drop;
		पूर्ण
	पूर्ण अन्यथा अणु
		queue = card->qdio.out_qs[txq];
	पूर्ण

	अगर (!(dev->flags & IFF_BROADCAST) &&
	    qeth_l3_get_cast_type(skb, proto) == RTN_BROADCAST)
		जाओ tx_drop;

	अगर (proto == htons(ETH_P_IP) || IS_IQD(card))
		rc = qeth_l3_xmit(card, skb, queue, proto);
	अन्यथा
		rc = qeth_xmit(card, skb, queue, proto, qeth_l3_fill_header);

	अगर (!rc)
		वापस NETDEV_TX_OK;

tx_drop:
	QETH_TXQ_STAT_INC(queue, tx_dropped);
	kमुक्त_skb(skb);
	वापस NETDEV_TX_OK;
पूर्ण

अटल व्योम qeth_l3_set_rx_mode(काष्ठा net_device *dev)
अणु
	काष्ठा qeth_card *card = dev->ml_priv;

	schedule_work(&card->rx_mode_work);
पूर्ण

/*
 * we need NOARP क्रम IPv4 but we want neighbor solicitation क्रम IPv6. Setting
 * NOARP on the netdevice is no option because it also turns off neighbor
 * solicitation. For IPv4 we install a neighbor_setup function. We करोn't want
 * arp resolution but we want the hard header (packet socket will work
 * e.g. tcpdump)
 */
अटल पूर्णांक qeth_l3_neigh_setup_noarp(काष्ठा neighbour *n)
अणु
	n->nud_state = NUD_NOARP;
	स_नकल(n->ha, "FAKELL", 6);
	n->output = n->ops->connected_output;
	वापस 0;
पूर्ण

अटल पूर्णांक
qeth_l3_neigh_setup(काष्ठा net_device *dev, काष्ठा neigh_parms *np)
अणु
	अगर (np->tbl->family == AF_INET)
		np->neigh_setup = qeth_l3_neigh_setup_noarp;

	वापस 0;
पूर्ण

अटल netdev_features_t qeth_l3_osa_features_check(काष्ठा sk_buff *skb,
						    काष्ठा net_device *dev,
						    netdev_features_t features)
अणु
	अगर (vlan_get_protocol(skb) != htons(ETH_P_IP))
		features &= ~NETIF_F_HW_VLAN_CTAG_TX;
	वापस qeth_features_check(skb, dev, features);
पूर्ण

अटल u16 qeth_l3_iqd_select_queue(काष्ठा net_device *dev, काष्ठा sk_buff *skb,
				    काष्ठा net_device *sb_dev)
अणु
	__be16 proto = vlan_get_protocol(skb);

	वापस qeth_iqd_select_queue(dev, skb,
				     qeth_l3_get_cast_type(skb, proto), sb_dev);
पूर्ण

अटल u16 qeth_l3_osa_select_queue(काष्ठा net_device *dev, काष्ठा sk_buff *skb,
				    काष्ठा net_device *sb_dev)
अणु
	काष्ठा qeth_card *card = dev->ml_priv;

	अगर (qeth_uses_tx_prio_queueing(card))
		वापस qeth_get_priority_queue(card, skb);

	वापस netdev_pick_tx(dev, skb, sb_dev);
पूर्ण

अटल स्थिर काष्ठा net_device_ops qeth_l3_netdev_ops = अणु
	.nकरो_खोलो		= qeth_खोलो,
	.nकरो_stop		= qeth_stop,
	.nकरो_get_stats64	= qeth_get_stats64,
	.nकरो_start_xmit		= qeth_l3_hard_start_xmit,
	.nकरो_select_queue	= qeth_l3_iqd_select_queue,
	.nकरो_validate_addr	= eth_validate_addr,
	.nकरो_set_rx_mode	= qeth_l3_set_rx_mode,
	.nकरो_करो_ioctl		= qeth_करो_ioctl,
	.nकरो_fix_features	= qeth_fix_features,
	.nकरो_set_features	= qeth_set_features,
	.nकरो_tx_समयout		= qeth_tx_समयout,
पूर्ण;

अटल स्थिर काष्ठा net_device_ops qeth_l3_osa_netdev_ops = अणु
	.nकरो_खोलो		= qeth_खोलो,
	.nकरो_stop		= qeth_stop,
	.nकरो_get_stats64	= qeth_get_stats64,
	.nकरो_start_xmit		= qeth_l3_hard_start_xmit,
	.nकरो_features_check	= qeth_l3_osa_features_check,
	.nकरो_select_queue	= qeth_l3_osa_select_queue,
	.nकरो_validate_addr	= eth_validate_addr,
	.nकरो_set_rx_mode	= qeth_l3_set_rx_mode,
	.nकरो_करो_ioctl		= qeth_करो_ioctl,
	.nकरो_fix_features	= qeth_fix_features,
	.nकरो_set_features	= qeth_set_features,
	.nकरो_tx_समयout		= qeth_tx_समयout,
	.nकरो_neigh_setup	= qeth_l3_neigh_setup,
पूर्ण;

अटल पूर्णांक qeth_l3_setup_netdev(काष्ठा qeth_card *card)
अणु
	काष्ठा net_device *dev = card->dev;
	अचिन्हित पूर्णांक headroom;
	पूर्णांक rc;

	अगर (IS_OSD(card) || IS_OSX(card)) अणु
		card->dev->netdev_ops = &qeth_l3_osa_netdev_ops;

		/*IPv6 address स्वतःconfiguration stuff*/
		dev->dev_id = qeth_l3_get_unique_id(card, dev->dev_id);

		अगर (!IS_VM_NIC(card)) अणु
			card->dev->features |= NETIF_F_SG;
			card->dev->hw_features |= NETIF_F_TSO |
				NETIF_F_RXCSUM | NETIF_F_IP_CSUM;
			card->dev->vlan_features |= NETIF_F_TSO |
				NETIF_F_RXCSUM | NETIF_F_IP_CSUM;
		पूर्ण

		अगर (qeth_is_supported6(card, IPA_OUTBOUND_CHECKSUM_V6)) अणु
			card->dev->hw_features |= NETIF_F_IPV6_CSUM;
			card->dev->vlan_features |= NETIF_F_IPV6_CSUM;
		पूर्ण
		अगर (qeth_is_supported6(card, IPA_OUTBOUND_TSO)) अणु
			card->dev->hw_features |= NETIF_F_TSO6;
			card->dev->vlan_features |= NETIF_F_TSO6;
		पूर्ण

		/* allow क्रम de-acceleration of NETIF_F_HW_VLAN_CTAG_TX: */
		अगर (card->dev->hw_features & NETIF_F_TSO6)
			headroom = माप(काष्ठा qeth_hdr_tso) + VLAN_HLEN;
		अन्यथा अगर (card->dev->hw_features & NETIF_F_TSO)
			headroom = माप(काष्ठा qeth_hdr_tso);
		अन्यथा
			headroom = माप(काष्ठा qeth_hdr) + VLAN_HLEN;
	पूर्ण अन्यथा अगर (IS_IQD(card)) अणु
		card->dev->flags |= IFF_NOARP;
		card->dev->netdev_ops = &qeth_l3_netdev_ops;
		headroom = माप(काष्ठा qeth_hdr) - ETH_HLEN;

		rc = qeth_l3_iqd_पढ़ो_initial_mac(card);
		अगर (rc)
			वापस rc;
	पूर्ण अन्यथा
		वापस -ENODEV;

	card->dev->needed_headroom = headroom;
	card->dev->features |=	NETIF_F_HW_VLAN_CTAG_TX |
				NETIF_F_HW_VLAN_CTAG_RX;

	netअगर_keep_dst(card->dev);
	अगर (card->dev->hw_features & (NETIF_F_TSO | NETIF_F_TSO6))
		netअगर_set_gso_max_size(card->dev,
				       PAGE_SIZE * (QETH_MAX_BUFFER_ELEMENTS(card) - 1));

	netअगर_napi_add(card->dev, &card->napi, qeth_poll, QETH_NAPI_WEIGHT);
	वापस रेजिस्टर_netdev(card->dev);
पूर्ण

अटल स्थिर काष्ठा device_type qeth_l3_devtype = अणु
	.name = "qeth_layer3",
	.groups = qeth_l3_attr_groups,
पूर्ण;

अटल पूर्णांक qeth_l3_probe_device(काष्ठा ccwgroup_device *gdev)
अणु
	काष्ठा qeth_card *card = dev_get_drvdata(&gdev->dev);
	पूर्णांक rc;

	hash_init(card->ip_htable);
	mutex_init(&card->ip_lock);
	card->cmd_wq = alloc_ordered_workqueue("%s_cmd", 0,
					       dev_name(&gdev->dev));
	अगर (!card->cmd_wq)
		वापस -ENOMEM;

	अगर (gdev->dev.type == &qeth_generic_devtype) अणु
		rc = device_add_groups(&gdev->dev, qeth_l3_attr_groups);
		अगर (rc) अणु
			destroy_workqueue(card->cmd_wq);
			वापस rc;
		पूर्ण
	पूर्ण

	INIT_WORK(&card->rx_mode_work, qeth_l3_rx_mode_work);
	वापस 0;
पूर्ण

अटल व्योम qeth_l3_हटाओ_device(काष्ठा ccwgroup_device *cgdev)
अणु
	काष्ठा qeth_card *card = dev_get_drvdata(&cgdev->dev);

	अगर (cgdev->dev.type == &qeth_generic_devtype)
		device_हटाओ_groups(&cgdev->dev, qeth_l3_attr_groups);

	qeth_set_allowed_thपढ़ोs(card, 0, 1);
	रुको_event(card->रुको_q, qeth_thपढ़ोs_running(card, 0xffffffff) == 0);

	अगर (cgdev->state == CCWGROUP_ONLINE)
		qeth_set_offline(card, card->discipline, false);

	cancel_work_sync(&card->बंद_dev_work);
	अगर (card->dev->reg_state == NETREG_REGISTERED)
		unरेजिस्टर_netdev(card->dev);

	flush_workqueue(card->cmd_wq);
	destroy_workqueue(card->cmd_wq);
	qeth_l3_clear_ip_htable(card, 0);
	qeth_l3_clear_ipato_list(card);
पूर्ण

अटल पूर्णांक qeth_l3_set_online(काष्ठा qeth_card *card, bool carrier_ok)
अणु
	काष्ठा net_device *dev = card->dev;
	पूर्णांक rc = 0;

	/* softsetup */
	QETH_CARD_TEXT(card, 2, "softsetp");

	rc = qeth_l3_setadapter_parms(card);
	अगर (rc)
		QETH_CARD_TEXT_(card, 2, "2err%04x", rc);
	अगर (!card->options.snअगरfer) अणु
		qeth_l3_start_ipassists(card);

		rc = qeth_l3_setrouting_v4(card);
		अगर (rc)
			QETH_CARD_TEXT_(card, 2, "4err%04x", rc);
		rc = qeth_l3_setrouting_v6(card);
		अगर (rc)
			QETH_CARD_TEXT_(card, 2, "5err%04x", rc);
	पूर्ण

	card->state = CARD_STATE_SOFTSETUP;

	qeth_set_allowed_thपढ़ोs(card, 0xffffffff, 0);
	qeth_l3_recover_ip(card);

	अगर (dev->reg_state != NETREG_REGISTERED) अणु
		rc = qeth_l3_setup_netdev(card);
		अगर (rc)
			जाओ err_setup;

		अगर (carrier_ok)
			netअगर_carrier_on(dev);
	पूर्ण अन्यथा अणु
		rtnl_lock();
		rc = qeth_set_real_num_tx_queues(card,
						 qeth_tx_actual_queues(card));
		अगर (rc) अणु
			rtnl_unlock();
			जाओ err_set_queues;
		पूर्ण

		अगर (carrier_ok)
			netअगर_carrier_on(dev);
		अन्यथा
			netअगर_carrier_off(dev);

		netअगर_device_attach(dev);
		qeth_enable_hw_features(dev);

		अगर (card->info.खोलो_when_online) अणु
			card->info.खोलो_when_online = 0;
			dev_खोलो(dev, शून्य);
		पूर्ण
		rtnl_unlock();
	पूर्ण
	वापस 0;

err_set_queues:
err_setup:
	qeth_set_allowed_thपढ़ोs(card, 0, 1);
	card->state = CARD_STATE_DOWN;
	qeth_l3_clear_ip_htable(card, 1);
	वापस rc;
पूर्ण

अटल व्योम qeth_l3_set_offline(काष्ठा qeth_card *card)
अणु
	qeth_set_allowed_thपढ़ोs(card, 0, 1);
	qeth_l3_drain_rx_mode_cache(card);

	अगर (card->options.snअगरfer &&
	    (card->info.promisc_mode == SET_PROMISC_MODE_ON))
		qeth_diags_trace(card, QETH_DIAGS_CMD_TRACE_DISABLE);

	अगर (card->state == CARD_STATE_SOFTSETUP) अणु
		card->state = CARD_STATE_DOWN;
		qeth_l3_clear_ip_htable(card, 1);
	पूर्ण
पूर्ण

/* Returns zero अगर the command is successfully "consumed" */
अटल पूर्णांक qeth_l3_control_event(काष्ठा qeth_card *card,
					काष्ठा qeth_ipa_cmd *cmd)
अणु
	वापस 1;
पूर्ण

स्थिर काष्ठा qeth_discipline qeth_l3_discipline = अणु
	.devtype = &qeth_l3_devtype,
	.setup = qeth_l3_probe_device,
	.हटाओ = qeth_l3_हटाओ_device,
	.set_online = qeth_l3_set_online,
	.set_offline = qeth_l3_set_offline,
	.करो_ioctl = qeth_l3_करो_ioctl,
	.control_event_handler = qeth_l3_control_event,
पूर्ण;
EXPORT_SYMBOL_GPL(qeth_l3_discipline);

अटल पूर्णांक qeth_l3_handle_ip_event(काष्ठा qeth_card *card,
				   काष्ठा qeth_ipaddr *addr,
				   अचिन्हित दीर्घ event)
अणु
	चयन (event) अणु
	हाल NETDEV_UP:
		qeth_l3_modअगरy_ip(card, addr, true);
		वापस NOTIFY_OK;
	हाल NETDEV_DOWN:
		qeth_l3_modअगरy_ip(card, addr, false);
		वापस NOTIFY_OK;
	शेष:
		वापस NOTIFY_DONE;
	पूर्ण
पूर्ण

काष्ठा qeth_l3_ip_event_work अणु
	काष्ठा work_काष्ठा work;
	काष्ठा qeth_card *card;
	काष्ठा qeth_ipaddr addr;
पूर्ण;

#घोषणा to_ip_work(w) container_of((w), काष्ठा qeth_l3_ip_event_work, work)

अटल व्योम qeth_l3_add_ip_worker(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा qeth_l3_ip_event_work *ip_work = to_ip_work(work);

	qeth_l3_modअगरy_ip(ip_work->card, &ip_work->addr, true);
	kमुक्त(work);
पूर्ण

अटल व्योम qeth_l3_delete_ip_worker(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा qeth_l3_ip_event_work *ip_work = to_ip_work(work);

	qeth_l3_modअगरy_ip(ip_work->card, &ip_work->addr, false);
	kमुक्त(work);
पूर्ण

अटल काष्ठा qeth_card *qeth_l3_get_card_from_dev(काष्ठा net_device *dev)
अणु
	अगर (is_vlan_dev(dev))
		dev = vlan_dev_real_dev(dev);
	अगर (dev->netdev_ops == &qeth_l3_osa_netdev_ops ||
	    dev->netdev_ops == &qeth_l3_netdev_ops)
		वापस (काष्ठा qeth_card *) dev->ml_priv;
	वापस शून्य;
पूर्ण

अटल पूर्णांक qeth_l3_ip_event(काष्ठा notअगरier_block *this,
			    अचिन्हित दीर्घ event, व्योम *ptr)
अणु
	काष्ठा in_अगरaddr *अगरa = (काष्ठा in_अगरaddr *)ptr;
	काष्ठा net_device *dev = अगरa->अगरa_dev->dev;
	काष्ठा qeth_ipaddr addr;
	काष्ठा qeth_card *card;

	card = qeth_l3_get_card_from_dev(dev);
	अगर (!card)
		वापस NOTIFY_DONE;
	QETH_CARD_TEXT(card, 3, "ipevent");

	qeth_l3_init_ipaddr(&addr, QETH_IP_TYPE_NORMAL, QETH_PROT_IPV4);
	addr.u.a4.addr = अगरa->अगरa_address;
	addr.u.a4.mask = अगरa->अगरa_mask;

	वापस qeth_l3_handle_ip_event(card, &addr, event);
पूर्ण

अटल काष्ठा notअगरier_block qeth_l3_ip_notअगरier = अणु
	qeth_l3_ip_event,
	शून्य,
पूर्ण;

अटल पूर्णांक qeth_l3_ip6_event(काष्ठा notअगरier_block *this,
			     अचिन्हित दीर्घ event, व्योम *ptr)
अणु
	काष्ठा inet6_अगरaddr *अगरa = (काष्ठा inet6_अगरaddr *)ptr;
	काष्ठा net_device *dev = अगरa->idev->dev;
	काष्ठा qeth_l3_ip_event_work *ip_work;
	काष्ठा qeth_card *card;

	अगर (event != NETDEV_UP && event != NETDEV_DOWN)
		वापस NOTIFY_DONE;

	card = qeth_l3_get_card_from_dev(dev);
	अगर (!card)
		वापस NOTIFY_DONE;
	QETH_CARD_TEXT(card, 3, "ip6event");
	अगर (!qeth_is_supported(card, IPA_IPV6))
		वापस NOTIFY_DONE;

	ip_work = kदो_स्मृति(माप(*ip_work), GFP_ATOMIC);
	अगर (!ip_work)
		वापस NOTIFY_DONE;

	अगर (event == NETDEV_UP)
		INIT_WORK(&ip_work->work, qeth_l3_add_ip_worker);
	अन्यथा
		INIT_WORK(&ip_work->work, qeth_l3_delete_ip_worker);

	ip_work->card = card;
	qeth_l3_init_ipaddr(&ip_work->addr, QETH_IP_TYPE_NORMAL,
			    QETH_PROT_IPV6);
	ip_work->addr.u.a6.addr = अगरa->addr;
	ip_work->addr.u.a6.pfxlen = अगरa->prefix_len;

	queue_work(card->cmd_wq, &ip_work->work);
	वापस NOTIFY_OK;
पूर्ण

अटल काष्ठा notअगरier_block qeth_l3_ip6_notअगरier = अणु
	qeth_l3_ip6_event,
	शून्य,
पूर्ण;

अटल पूर्णांक qeth_l3_रेजिस्टर_notअगरiers(व्योम)
अणु
	पूर्णांक rc;

	QETH_DBF_TEXT(SETUP, 5, "regnotif");
	rc = रेजिस्टर_inetaddr_notअगरier(&qeth_l3_ip_notअगरier);
	अगर (rc)
		वापस rc;
	rc = रेजिस्टर_inet6addr_notअगरier(&qeth_l3_ip6_notअगरier);
	अगर (rc) अणु
		unरेजिस्टर_inetaddr_notअगरier(&qeth_l3_ip_notअगरier);
		वापस rc;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम qeth_l3_unरेजिस्टर_notअगरiers(व्योम)
अणु
	QETH_DBF_TEXT(SETUP, 5, "unregnot");
	WARN_ON(unरेजिस्टर_inetaddr_notअगरier(&qeth_l3_ip_notअगरier));
	WARN_ON(unरेजिस्टर_inet6addr_notअगरier(&qeth_l3_ip6_notअगरier));
पूर्ण

अटल पूर्णांक __init qeth_l3_init(व्योम)
अणु
	pr_info("register layer 3 discipline\n");
	वापस qeth_l3_रेजिस्टर_notअगरiers();
पूर्ण

अटल व्योम __निकास qeth_l3_निकास(व्योम)
अणु
	qeth_l3_unरेजिस्टर_notअगरiers();
	pr_info("unregister layer 3 discipline\n");
पूर्ण

module_init(qeth_l3_init);
module_निकास(qeth_l3_निकास);
MODULE_AUTHOR("Frank Blaschka <frank.blaschka@de.ibm.com>");
MODULE_DESCRIPTION("qeth layer 3 discipline");
MODULE_LICENSE("GPL");
