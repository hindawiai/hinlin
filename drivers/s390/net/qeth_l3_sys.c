<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *    Copyright IBM Corp. 2007
 *    Author(s): Utz Bacher <utz.bacher@de.ibm.com>,
 *		 Frank Pavlic <fpavlic@de.ibm.com>,
 *		 Thomas Spatzier <tspat@de.ibm.com>,
 *		 Frank Blaschka <frank.blaschka@de.ibm.com>
 */

#समावेश <linux/slab.h>
#समावेश <यंत्र/ebcdic.h>
#समावेश <linux/hashtable.h>
#समावेश <linux/inet.h>
#समावेश "qeth_l3.h"

#घोषणा QETH_DEVICE_ATTR(_id, _name, _mode, _show, _store) \
काष्ठा device_attribute dev_attr_##_id = __ATTR(_name, _mode, _show, _store)

अटल पूर्णांक qeth_l3_string_to_ipaddr(स्थिर अक्षर *buf,
				    क्रमागत qeth_prot_versions proto, u8 *addr)
अणु
	स्थिर अक्षर *end;

	अगर ((proto == QETH_PROT_IPV4 && !in4_pton(buf, -1, addr, -1, &end)) ||
	    (proto == QETH_PROT_IPV6 && !in6_pton(buf, -1, addr, -1, &end)))
		वापस -EINVAL;
	वापस 0;
पूर्ण

अटल sमाप_प्रकार qeth_l3_dev_route_show(काष्ठा qeth_card *card,
			काष्ठा qeth_routing_info *route, अक्षर *buf)
अणु
	चयन (route->type) अणु
	हाल PRIMARY_ROUTER:
		वापस प्र_लिखो(buf, "%s\n", "primary router");
	हाल SECONDARY_ROUTER:
		वापस प्र_लिखो(buf, "%s\n", "secondary router");
	हाल MULTICAST_ROUTER:
		अगर (card->info.broadcast_capable == QETH_BROADCAST_WITHOUT_ECHO)
			वापस प्र_लिखो(buf, "%s\n", "multicast router+");
		अन्यथा
			वापस प्र_लिखो(buf, "%s\n", "multicast router");
	हाल PRIMARY_CONNECTOR:
		अगर (card->info.broadcast_capable == QETH_BROADCAST_WITHOUT_ECHO)
			वापस प्र_लिखो(buf, "%s\n", "primary connector+");
		अन्यथा
			वापस प्र_लिखो(buf, "%s\n", "primary connector");
	हाल SECONDARY_CONNECTOR:
		अगर (card->info.broadcast_capable == QETH_BROADCAST_WITHOUT_ECHO)
			वापस प्र_लिखो(buf, "%s\n", "secondary connector+");
		अन्यथा
			वापस प्र_लिखो(buf, "%s\n", "secondary connector");
	शेष:
		वापस प्र_लिखो(buf, "%s\n", "no");
	पूर्ण
पूर्ण

अटल sमाप_प्रकार qeth_l3_dev_route4_show(काष्ठा device *dev,
			काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा qeth_card *card = dev_get_drvdata(dev);

	वापस qeth_l3_dev_route_show(card, &card->options.route4, buf);
पूर्ण

अटल sमाप_प्रकार qeth_l3_dev_route_store(काष्ठा qeth_card *card,
		काष्ठा qeth_routing_info *route, क्रमागत qeth_prot_versions prot,
		स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	क्रमागत qeth_routing_types old_route_type = route->type;
	पूर्णांक rc = 0;

	mutex_lock(&card->conf_mutex);
	अगर (sysfs_streq(buf, "no_router")) अणु
		route->type = NO_ROUTER;
	पूर्ण अन्यथा अगर (sysfs_streq(buf, "primary_connector")) अणु
		route->type = PRIMARY_CONNECTOR;
	पूर्ण अन्यथा अगर (sysfs_streq(buf, "secondary_connector")) अणु
		route->type = SECONDARY_CONNECTOR;
	पूर्ण अन्यथा अगर (sysfs_streq(buf, "primary_router")) अणु
		route->type = PRIMARY_ROUTER;
	पूर्ण अन्यथा अगर (sysfs_streq(buf, "secondary_router")) अणु
		route->type = SECONDARY_ROUTER;
	पूर्ण अन्यथा अगर (sysfs_streq(buf, "multicast_router")) अणु
		route->type = MULTICAST_ROUTER;
	पूर्ण अन्यथा अणु
		rc = -EINVAL;
		जाओ out;
	पूर्ण
	अगर (qeth_card_hw_is_reachable(card) &&
	    (old_route_type != route->type)) अणु
		अगर (prot == QETH_PROT_IPV4)
			rc = qeth_l3_setrouting_v4(card);
		अन्यथा अगर (prot == QETH_PROT_IPV6)
			rc = qeth_l3_setrouting_v6(card);
	पूर्ण
out:
	अगर (rc)
		route->type = old_route_type;
	mutex_unlock(&card->conf_mutex);
	वापस rc ? rc : count;
पूर्ण

अटल sमाप_प्रकार qeth_l3_dev_route4_store(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा qeth_card *card = dev_get_drvdata(dev);

	वापस qeth_l3_dev_route_store(card, &card->options.route4,
				QETH_PROT_IPV4, buf, count);
पूर्ण

अटल DEVICE_ATTR(route4, 0644, qeth_l3_dev_route4_show,
			qeth_l3_dev_route4_store);

अटल sमाप_प्रकार qeth_l3_dev_route6_show(काष्ठा device *dev,
			काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा qeth_card *card = dev_get_drvdata(dev);

	वापस qeth_l3_dev_route_show(card, &card->options.route6, buf);
पूर्ण

अटल sमाप_प्रकार qeth_l3_dev_route6_store(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा qeth_card *card = dev_get_drvdata(dev);

	वापस qeth_l3_dev_route_store(card, &card->options.route6,
				QETH_PROT_IPV6, buf, count);
पूर्ण

अटल DEVICE_ATTR(route6, 0644, qeth_l3_dev_route6_show,
			qeth_l3_dev_route6_store);

अटल sमाप_प्रकार qeth_l3_dev_snअगरfer_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा qeth_card *card = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%i\n", card->options.snअगरfer ? 1 : 0);
पूर्ण

अटल sमाप_प्रकार qeth_l3_dev_snअगरfer_store(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा qeth_card *card = dev_get_drvdata(dev);
	पूर्णांक rc = 0;
	अचिन्हित दीर्घ i;

	अगर (!IS_IQD(card))
		वापस -EPERM;
	अगर (card->options.cq == QETH_CQ_ENABLED)
		वापस -EPERM;

	mutex_lock(&card->conf_mutex);
	अगर (card->state != CARD_STATE_DOWN) अणु
		rc = -EPERM;
		जाओ out;
	पूर्ण

	rc = kम_से_अदीर्घ(buf, 16, &i);
	अगर (rc) अणु
		rc = -EINVAL;
		जाओ out;
	पूर्ण
	चयन (i) अणु
	हाल 0:
		card->options.snअगरfer = i;
		अवरोध;
	हाल 1:
		qdio_get_ssqd_desc(CARD_DDEV(card), &card->ssqd);
		अगर (card->ssqd.qdioac2 & CHSC_AC2_SNIFFER_AVAILABLE) अणु
			card->options.snअगरfer = i;
			qeth_resize_buffer_pool(card, QETH_IN_BUF_COUNT_MAX);
		पूर्ण अन्यथा अणु
			rc = -EPERM;
		पूर्ण

		अवरोध;
	शेष:
		rc = -EINVAL;
	पूर्ण
out:
	mutex_unlock(&card->conf_mutex);
	वापस rc ? rc : count;
पूर्ण

अटल DEVICE_ATTR(snअगरfer, 0644, qeth_l3_dev_snअगरfer_show,
		qeth_l3_dev_snअगरfer_store);

अटल sमाप_प्रकार qeth_l3_dev_hsuid_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा qeth_card *card = dev_get_drvdata(dev);
	अक्षर पंचांगp_hsuid[9];

	अगर (!IS_IQD(card))
		वापस -EPERM;

	स_नकल(पंचांगp_hsuid, card->options.hsuid, माप(पंचांगp_hsuid));
	EBCASC(पंचांगp_hsuid, 8);
	वापस प्र_लिखो(buf, "%s\n", पंचांगp_hsuid);
पूर्ण

अटल sमाप_प्रकार qeth_l3_dev_hsuid_store(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा qeth_card *card = dev_get_drvdata(dev);
	पूर्णांक rc = 0;
	अक्षर *पंचांगp;

	अगर (!IS_IQD(card))
		वापस -EPERM;

	mutex_lock(&card->conf_mutex);
	अगर (card->state != CARD_STATE_DOWN) अणु
		rc = -EPERM;
		जाओ out;
	पूर्ण

	अगर (card->options.snअगरfer) अणु
		rc = -EPERM;
		जाओ out;
	पूर्ण

	अगर (card->options.cq == QETH_CQ_NOTAVAILABLE) अणु
		rc = -EPERM;
		जाओ out;
	पूर्ण

	पंचांगp = strsep((अक्षर **)&buf, "\n");
	अगर (म_माप(पंचांगp) > 8) अणु
		rc = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (card->options.hsuid[0])
		/* delete old ip address */
		qeth_l3_modअगरy_hsuid(card, false);

	अगर (म_माप(पंचांगp) == 0) अणु
		/* delete ip address only */
		card->options.hsuid[0] = '\0';
		स_नकल(card->dev->perm_addr, card->options.hsuid, 9);
		qeth_configure_cq(card, QETH_CQ_DISABLED);
		जाओ out;
	पूर्ण

	अगर (qeth_configure_cq(card, QETH_CQ_ENABLED)) अणु
		rc = -EPERM;
		जाओ out;
	पूर्ण

	snम_लिखो(card->options.hsuid, माप(card->options.hsuid),
		 "%-8s", पंचांगp);
	ASCEBC(card->options.hsuid, 8);
	स_नकल(card->dev->perm_addr, card->options.hsuid, 9);

	rc = qeth_l3_modअगरy_hsuid(card, true);

out:
	mutex_unlock(&card->conf_mutex);
	वापस rc ? rc : count;
पूर्ण

अटल DEVICE_ATTR(hsuid, 0644, qeth_l3_dev_hsuid_show,
		   qeth_l3_dev_hsuid_store);


अटल काष्ठा attribute *qeth_l3_device_attrs[] = अणु
	&dev_attr_route4.attr,
	&dev_attr_route6.attr,
	&dev_attr_snअगरfer.attr,
	&dev_attr_hsuid.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group qeth_l3_device_attr_group = अणु
	.attrs = qeth_l3_device_attrs,
पूर्ण;

अटल sमाप_प्रकार qeth_l3_dev_ipato_enable_show(काष्ठा device *dev,
			काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा qeth_card *card = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%u\n", card->ipato.enabled ? 1 : 0);
पूर्ण

अटल sमाप_प्रकार qeth_l3_dev_ipato_enable_store(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा qeth_card *card = dev_get_drvdata(dev);
	bool enable;
	पूर्णांक rc = 0;

	mutex_lock(&card->conf_mutex);
	अगर (card->state != CARD_STATE_DOWN) अणु
		rc = -EPERM;
		जाओ out;
	पूर्ण

	mutex_lock(&card->ip_lock);
	अगर (sysfs_streq(buf, "toggle")) अणु
		enable = !card->ipato.enabled;
	पूर्ण अन्यथा अगर (kstrtobool(buf, &enable)) अणु
		rc = -EINVAL;
		जाओ unlock_ip;
	पूर्ण

	अगर (card->ipato.enabled != enable) अणु
		card->ipato.enabled = enable;
		qeth_l3_update_ipato(card);
	पूर्ण

unlock_ip:
	mutex_unlock(&card->ip_lock);
out:
	mutex_unlock(&card->conf_mutex);
	वापस rc ? rc : count;
पूर्ण

अटल QETH_DEVICE_ATTR(ipato_enable, enable, 0644,
			qeth_l3_dev_ipato_enable_show,
			qeth_l3_dev_ipato_enable_store);

अटल sमाप_प्रकार qeth_l3_dev_ipato_invert4_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा qeth_card *card = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%u\n", card->ipato.invert4 ? 1 : 0);
पूर्ण

अटल sमाप_प्रकार qeth_l3_dev_ipato_invert4_store(काष्ठा device *dev,
				काष्ठा device_attribute *attr,
				स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा qeth_card *card = dev_get_drvdata(dev);
	bool invert;
	पूर्णांक rc = 0;

	mutex_lock(&card->ip_lock);
	अगर (sysfs_streq(buf, "toggle")) अणु
		invert = !card->ipato.invert4;
	पूर्ण अन्यथा अगर (kstrtobool(buf, &invert)) अणु
		rc = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (card->ipato.invert4 != invert) अणु
		card->ipato.invert4 = invert;
		qeth_l3_update_ipato(card);
	पूर्ण

out:
	mutex_unlock(&card->ip_lock);
	वापस rc ? rc : count;
पूर्ण

अटल QETH_DEVICE_ATTR(ipato_invert4, invert4, 0644,
			qeth_l3_dev_ipato_invert4_show,
			qeth_l3_dev_ipato_invert4_store);

अटल sमाप_प्रकार qeth_l3_dev_ipato_add_show(अक्षर *buf, काष्ठा qeth_card *card,
			क्रमागत qeth_prot_versions proto)
अणु
	काष्ठा qeth_ipato_entry *ipatoe;
	पूर्णांक str_len = 0;

	mutex_lock(&card->ip_lock);
	list_क्रम_each_entry(ipatoe, &card->ipato.entries, entry) अणु
		अक्षर addr_str[40];
		पूर्णांक entry_len;

		अगर (ipatoe->proto != proto)
			जारी;

		entry_len = qeth_l3_ipaddr_to_string(proto, ipatoe->addr,
						     addr_str);
		अगर (entry_len < 0)
			जारी;

		/* Append /%mask to the entry: */
		entry_len += 1 + ((proto == QETH_PROT_IPV4) ? 2 : 3);
		/* Enough room to क्रमmat %entry\न पूर्णांकo null terminated page? */
		अगर (entry_len + 1 > PAGE_SIZE - str_len - 1)
			अवरोध;

		entry_len = scnम_लिखो(buf, PAGE_SIZE - str_len,
				      "%s/%i\n", addr_str, ipatoe->mask_bits);
		str_len += entry_len;
		buf += entry_len;
	पूर्ण
	mutex_unlock(&card->ip_lock);

	वापस str_len ? str_len : scnम_लिखो(buf, PAGE_SIZE, "\n");
पूर्ण

अटल sमाप_प्रकार qeth_l3_dev_ipato_add4_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा qeth_card *card = dev_get_drvdata(dev);

	वापस qeth_l3_dev_ipato_add_show(buf, card, QETH_PROT_IPV4);
पूर्ण

अटल पूर्णांक qeth_l3_parse_ipatoe(स्थिर अक्षर *buf, क्रमागत qeth_prot_versions proto,
				u8 *addr, अचिन्हित पूर्णांक *mask_bits)
अणु
	अक्षर *sep;
	पूर्णांक rc;

	/* Expected input pattern: %addr/%mask */
	sep = strnchr(buf, 40, '/');
	अगर (!sep)
		वापस -EINVAL;

	/* Terminate the %addr sub-string, and parse it: */
	*sep = '\0';
	rc = qeth_l3_string_to_ipaddr(buf, proto, addr);
	अगर (rc)
		वापस rc;

	rc = kstrtouपूर्णांक(sep + 1, 10, mask_bits);
	अगर (rc)
		वापस rc;

	अगर (*mask_bits > ((proto == QETH_PROT_IPV4) ? 32 : 128))
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल sमाप_प्रकार qeth_l3_dev_ipato_add_store(स्थिर अक्षर *buf, माप_प्रकार count,
			 काष्ठा qeth_card *card, क्रमागत qeth_prot_versions proto)
अणु
	काष्ठा qeth_ipato_entry *ipatoe;
	अचिन्हित पूर्णांक mask_bits;
	u8 addr[16];
	पूर्णांक rc = 0;

	rc = qeth_l3_parse_ipatoe(buf, proto, addr, &mask_bits);
	अगर (rc)
		वापस rc;

	ipatoe = kzalloc(माप(काष्ठा qeth_ipato_entry), GFP_KERNEL);
	अगर (!ipatoe)
		वापस -ENOMEM;

	ipatoe->proto = proto;
	स_नकल(ipatoe->addr, addr, (proto == QETH_PROT_IPV4) ? 4 : 16);
	ipatoe->mask_bits = mask_bits;

	rc = qeth_l3_add_ipato_entry(card, ipatoe);
	अगर (rc)
		kमुक्त(ipatoe);

	वापस rc ? rc : count;
पूर्ण

अटल sमाप_प्रकार qeth_l3_dev_ipato_add4_store(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा qeth_card *card = dev_get_drvdata(dev);

	वापस qeth_l3_dev_ipato_add_store(buf, count, card, QETH_PROT_IPV4);
पूर्ण

अटल QETH_DEVICE_ATTR(ipato_add4, add4, 0644,
			qeth_l3_dev_ipato_add4_show,
			qeth_l3_dev_ipato_add4_store);

अटल sमाप_प्रकार qeth_l3_dev_ipato_del_store(स्थिर अक्षर *buf, माप_प्रकार count,
			 काष्ठा qeth_card *card, क्रमागत qeth_prot_versions proto)
अणु
	अचिन्हित पूर्णांक mask_bits;
	u8 addr[16];
	पूर्णांक rc = 0;

	rc = qeth_l3_parse_ipatoe(buf, proto, addr, &mask_bits);
	अगर (!rc)
		rc = qeth_l3_del_ipato_entry(card, proto, addr, mask_bits);
	वापस rc ? rc : count;
पूर्ण

अटल sमाप_प्रकार qeth_l3_dev_ipato_del4_store(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा qeth_card *card = dev_get_drvdata(dev);

	वापस qeth_l3_dev_ipato_del_store(buf, count, card, QETH_PROT_IPV4);
पूर्ण

अटल QETH_DEVICE_ATTR(ipato_del4, del4, 0200, शून्य,
			qeth_l3_dev_ipato_del4_store);

अटल sमाप_प्रकार qeth_l3_dev_ipato_invert6_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा qeth_card *card = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%u\n", card->ipato.invert6 ? 1 : 0);
पूर्ण

अटल sमाप_प्रकार qeth_l3_dev_ipato_invert6_store(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा qeth_card *card = dev_get_drvdata(dev);
	bool invert;
	पूर्णांक rc = 0;

	mutex_lock(&card->ip_lock);
	अगर (sysfs_streq(buf, "toggle")) अणु
		invert = !card->ipato.invert6;
	पूर्ण अन्यथा अगर (kstrtobool(buf, &invert)) अणु
		rc = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (card->ipato.invert6 != invert) अणु
		card->ipato.invert6 = invert;
		qeth_l3_update_ipato(card);
	पूर्ण

out:
	mutex_unlock(&card->ip_lock);
	वापस rc ? rc : count;
पूर्ण

अटल QETH_DEVICE_ATTR(ipato_invert6, invert6, 0644,
			qeth_l3_dev_ipato_invert6_show,
			qeth_l3_dev_ipato_invert6_store);


अटल sमाप_प्रकार qeth_l3_dev_ipato_add6_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा qeth_card *card = dev_get_drvdata(dev);

	वापस qeth_l3_dev_ipato_add_show(buf, card, QETH_PROT_IPV6);
पूर्ण

अटल sमाप_प्रकार qeth_l3_dev_ipato_add6_store(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा qeth_card *card = dev_get_drvdata(dev);

	वापस qeth_l3_dev_ipato_add_store(buf, count, card, QETH_PROT_IPV6);
पूर्ण

अटल QETH_DEVICE_ATTR(ipato_add6, add6, 0644,
			qeth_l3_dev_ipato_add6_show,
			qeth_l3_dev_ipato_add6_store);

अटल sमाप_प्रकार qeth_l3_dev_ipato_del6_store(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा qeth_card *card = dev_get_drvdata(dev);

	वापस qeth_l3_dev_ipato_del_store(buf, count, card, QETH_PROT_IPV6);
पूर्ण

अटल QETH_DEVICE_ATTR(ipato_del6, del6, 0200, शून्य,
			qeth_l3_dev_ipato_del6_store);

अटल काष्ठा attribute *qeth_ipato_device_attrs[] = अणु
	&dev_attr_ipato_enable.attr,
	&dev_attr_ipato_invert4.attr,
	&dev_attr_ipato_add4.attr,
	&dev_attr_ipato_del4.attr,
	&dev_attr_ipato_invert6.attr,
	&dev_attr_ipato_add6.attr,
	&dev_attr_ipato_del6.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group qeth_device_ipato_group = अणु
	.name = "ipa_takeover",
	.attrs = qeth_ipato_device_attrs,
पूर्ण;

अटल sमाप_प्रकार qeth_l3_dev_ip_add_show(काष्ठा device *dev, अक्षर *buf,
				       क्रमागत qeth_prot_versions proto,
				       क्रमागत qeth_ip_types type)
अणु
	काष्ठा qeth_card *card = dev_get_drvdata(dev);
	काष्ठा qeth_ipaddr *ipaddr;
	पूर्णांक str_len = 0;
	पूर्णांक i;

	mutex_lock(&card->ip_lock);
	hash_क्रम_each(card->ip_htable, i, ipaddr, hnode) अणु
		अक्षर addr_str[40];
		पूर्णांक entry_len;

		अगर (ipaddr->proto != proto || ipaddr->type != type)
			जारी;

		entry_len = qeth_l3_ipaddr_to_string(proto, (u8 *)&ipaddr->u,
						     addr_str);
		अगर (entry_len < 0)
			जारी;

		/* Enough room to क्रमmat %addr\न पूर्णांकo null terminated page? */
		अगर (entry_len + 1 > PAGE_SIZE - str_len - 1)
			अवरोध;

		entry_len = scnम_लिखो(buf, PAGE_SIZE - str_len, "%s\n",
				      addr_str);
		str_len += entry_len;
		buf += entry_len;
	पूर्ण
	mutex_unlock(&card->ip_lock);

	वापस str_len ? str_len : scnम_लिखो(buf, PAGE_SIZE, "\n");
पूर्ण

अटल sमाप_प्रकार qeth_l3_dev_vipa_add4_show(काष्ठा device *dev,
					  काष्ठा device_attribute *attr,
					  अक्षर *buf)
अणु
	वापस qeth_l3_dev_ip_add_show(dev, buf, QETH_PROT_IPV4,
				       QETH_IP_TYPE_VIPA);
पूर्ण

अटल sमाप_प्रकार qeth_l3_vipa_store(काष्ठा device *dev, स्थिर अक्षर *buf, bool add,
				  माप_प्रकार count, क्रमागत qeth_prot_versions proto)
अणु
	काष्ठा qeth_card *card = dev_get_drvdata(dev);
	u8 addr[16] = अणु0, पूर्ण;
	पूर्णांक rc;

	rc = qeth_l3_string_to_ipaddr(buf, proto, addr);
	अगर (!rc)
		rc = qeth_l3_modअगरy_rxip_vipa(card, add, addr,
					      QETH_IP_TYPE_VIPA, proto);
	वापस rc ? rc : count;
पूर्ण

अटल sमाप_प्रकार qeth_l3_dev_vipa_add4_store(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	वापस qeth_l3_vipa_store(dev, buf, true, count, QETH_PROT_IPV4);
पूर्ण

अटल QETH_DEVICE_ATTR(vipa_add4, add4, 0644,
			qeth_l3_dev_vipa_add4_show,
			qeth_l3_dev_vipa_add4_store);

अटल sमाप_प्रकार qeth_l3_dev_vipa_del4_store(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	वापस qeth_l3_vipa_store(dev, buf, true, count, QETH_PROT_IPV4);
पूर्ण

अटल QETH_DEVICE_ATTR(vipa_del4, del4, 0200, शून्य,
			qeth_l3_dev_vipa_del4_store);

अटल sमाप_प्रकार qeth_l3_dev_vipa_add6_show(काष्ठा device *dev,
					  काष्ठा device_attribute *attr,
					  अक्षर *buf)
अणु
	वापस qeth_l3_dev_ip_add_show(dev, buf, QETH_PROT_IPV6,
				       QETH_IP_TYPE_VIPA);
पूर्ण

अटल sमाप_प्रकार qeth_l3_dev_vipa_add6_store(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	वापस qeth_l3_vipa_store(dev, buf, true, count, QETH_PROT_IPV6);
पूर्ण

अटल QETH_DEVICE_ATTR(vipa_add6, add6, 0644,
			qeth_l3_dev_vipa_add6_show,
			qeth_l3_dev_vipa_add6_store);

अटल sमाप_प्रकार qeth_l3_dev_vipa_del6_store(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	वापस qeth_l3_vipa_store(dev, buf, false, count, QETH_PROT_IPV6);
पूर्ण

अटल QETH_DEVICE_ATTR(vipa_del6, del6, 0200, शून्य,
			qeth_l3_dev_vipa_del6_store);

अटल काष्ठा attribute *qeth_vipa_device_attrs[] = अणु
	&dev_attr_vipa_add4.attr,
	&dev_attr_vipa_del4.attr,
	&dev_attr_vipa_add6.attr,
	&dev_attr_vipa_del6.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group qeth_device_vipa_group = अणु
	.name = "vipa",
	.attrs = qeth_vipa_device_attrs,
पूर्ण;

अटल sमाप_प्रकार qeth_l3_dev_rxip_add4_show(काष्ठा device *dev,
					  काष्ठा device_attribute *attr,
					  अक्षर *buf)
अणु
	वापस qeth_l3_dev_ip_add_show(dev, buf, QETH_PROT_IPV4,
				       QETH_IP_TYPE_RXIP);
पूर्ण

अटल पूर्णांक qeth_l3_parse_rxipe(स्थिर अक्षर *buf, क्रमागत qeth_prot_versions proto,
		 u8 *addr)
अणु
	__be32 ipv4_addr;
	काष्ठा in6_addr ipv6_addr;

	अगर (qeth_l3_string_to_ipaddr(buf, proto, addr)) अणु
		वापस -EINVAL;
	पूर्ण
	अगर (proto == QETH_PROT_IPV4) अणु
		स_नकल(&ipv4_addr, addr, माप(ipv4_addr));
		अगर (ipv4_is_multicast(ipv4_addr)) अणु
			QETH_DBF_MESSAGE(2, "multicast rxip not supported.\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अगर (proto == QETH_PROT_IPV6) अणु
		स_नकल(&ipv6_addr, addr, माप(ipv6_addr));
		अगर (ipv6_addr_is_multicast(&ipv6_addr)) अणु
			QETH_DBF_MESSAGE(2, "multicast rxip not supported.\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल sमाप_प्रकार qeth_l3_rxip_store(काष्ठा device *dev, स्थिर अक्षर *buf, bool add,
				  माप_प्रकार count, क्रमागत qeth_prot_versions proto)
अणु
	काष्ठा qeth_card *card = dev_get_drvdata(dev);
	u8 addr[16] = अणु0, पूर्ण;
	पूर्णांक rc;

	rc = qeth_l3_parse_rxipe(buf, proto, addr);
	अगर (!rc)
		rc = qeth_l3_modअगरy_rxip_vipa(card, add, addr,
					      QETH_IP_TYPE_RXIP, proto);
	वापस rc ? rc : count;
पूर्ण

अटल sमाप_प्रकार qeth_l3_dev_rxip_add4_store(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	वापस qeth_l3_rxip_store(dev, buf, true, count, QETH_PROT_IPV4);
पूर्ण

अटल QETH_DEVICE_ATTR(rxip_add4, add4, 0644,
			qeth_l3_dev_rxip_add4_show,
			qeth_l3_dev_rxip_add4_store);

अटल sमाप_प्रकार qeth_l3_dev_rxip_del4_store(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	वापस qeth_l3_rxip_store(dev, buf, false, count, QETH_PROT_IPV4);
पूर्ण

अटल QETH_DEVICE_ATTR(rxip_del4, del4, 0200, शून्य,
			qeth_l3_dev_rxip_del4_store);

अटल sमाप_प्रकार qeth_l3_dev_rxip_add6_show(काष्ठा device *dev,
					  काष्ठा device_attribute *attr,
					  अक्षर *buf)
अणु
	वापस qeth_l3_dev_ip_add_show(dev, buf, QETH_PROT_IPV6,
				       QETH_IP_TYPE_RXIP);
पूर्ण

अटल sमाप_प्रकार qeth_l3_dev_rxip_add6_store(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	वापस qeth_l3_rxip_store(dev, buf, true, count, QETH_PROT_IPV6);
पूर्ण

अटल QETH_DEVICE_ATTR(rxip_add6, add6, 0644,
			qeth_l3_dev_rxip_add6_show,
			qeth_l3_dev_rxip_add6_store);

अटल sमाप_प्रकार qeth_l3_dev_rxip_del6_store(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	वापस qeth_l3_rxip_store(dev, buf, false, count, QETH_PROT_IPV6);
पूर्ण

अटल QETH_DEVICE_ATTR(rxip_del6, del6, 0200, शून्य,
			qeth_l3_dev_rxip_del6_store);

अटल काष्ठा attribute *qeth_rxip_device_attrs[] = अणु
	&dev_attr_rxip_add4.attr,
	&dev_attr_rxip_del4.attr,
	&dev_attr_rxip_add6.attr,
	&dev_attr_rxip_del6.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group qeth_device_rxip_group = अणु
	.name = "rxip",
	.attrs = qeth_rxip_device_attrs,
पूर्ण;

स्थिर काष्ठा attribute_group *qeth_l3_attr_groups[] = अणु
	&qeth_l3_device_attr_group,
	&qeth_device_ipato_group,
	&qeth_device_vipa_group,
	&qeth_device_rxip_group,
	शून्य,
पूर्ण;
