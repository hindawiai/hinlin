<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *
 * Authors:
 * (C) 2016 Pengutronix, Alexander Aring <aar@pengutronix.de>
 */

#समावेश <net/6lowpan.h>
#समावेश <net/addrconf.h>
#समावेश <net/ndisc.h>

#समावेश "6lowpan_i.h"

अटल पूर्णांक lowpan_ndisc_is_useropt(u8 nd_opt_type)
अणु
	वापस nd_opt_type == ND_OPT_6CO;
पूर्ण

#अगर IS_ENABLED(CONFIG_IEEE802154_6LOWPAN)
#घोषणा NDISC_802154_SHORT_ADDR_LENGTH	1
अटल पूर्णांक lowpan_ndisc_parse_802154_options(स्थिर काष्ठा net_device *dev,
					     काष्ठा nd_opt_hdr *nd_opt,
					     काष्ठा ndisc_options *nकरोpts)
अणु
	चयन (nd_opt->nd_opt_len) अणु
	हाल NDISC_802154_SHORT_ADDR_LENGTH:
		अगर (nकरोpts->nd_802154_opt_array[nd_opt->nd_opt_type])
			ND_PRINTK(2, warn,
				  "%s: duplicated short addr ND6 option found: type=%d\n",
				  __func__, nd_opt->nd_opt_type);
		अन्यथा
			nकरोpts->nd_802154_opt_array[nd_opt->nd_opt_type] = nd_opt;
		वापस 1;
	शेष:
		/* all others will be handled by ndisc IPv6 option parsing */
		वापस 0;
	पूर्ण
पूर्ण

अटल पूर्णांक lowpan_ndisc_parse_options(स्थिर काष्ठा net_device *dev,
				      काष्ठा nd_opt_hdr *nd_opt,
				      काष्ठा ndisc_options *nकरोpts)
अणु
	अगर (!lowpan_is_ll(dev, LOWPAN_LLTYPE_IEEE802154))
		वापस 0;

	चयन (nd_opt->nd_opt_type) अणु
	हाल ND_OPT_SOURCE_LL_ADDR:
	हाल ND_OPT_TARGET_LL_ADDR:
		वापस lowpan_ndisc_parse_802154_options(dev, nd_opt, nकरोpts);
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल व्योम lowpan_ndisc_802154_update(काष्ठा neighbour *n, u32 flags,
				       u8 icmp6_type,
				       स्थिर काष्ठा ndisc_options *nकरोpts)
अणु
	काष्ठा lowpan_802154_neigh *neigh = lowpan_802154_neigh(neighbour_priv(n));
	u8 *lladdr_लघु = शून्य;

	चयन (icmp6_type) अणु
	हाल NDISC_ROUTER_SOLICITATION:
	हाल NDISC_ROUTER_ADVERTISEMENT:
	हाल NDISC_NEIGHBOUR_SOLICITATION:
		अगर (nकरोpts->nd_802154_opts_src_lladdr) अणु
			lladdr_लघु = __ndisc_opt_addr_data(nकरोpts->nd_802154_opts_src_lladdr,
							     IEEE802154_SHORT_ADDR_LEN, 0);
			अगर (!lladdr_लघु) अणु
				ND_PRINTK(2, warn,
					  "NA: invalid short link-layer address length\n");
				वापस;
			पूर्ण
		पूर्ण
		अवरोध;
	हाल NDISC_REसूचीECT:
	हाल NDISC_NEIGHBOUR_ADVERTISEMENT:
		अगर (nकरोpts->nd_802154_opts_tgt_lladdr) अणु
			lladdr_लघु = __ndisc_opt_addr_data(nकरोpts->nd_802154_opts_tgt_lladdr,
							     IEEE802154_SHORT_ADDR_LEN, 0);
			अगर (!lladdr_लघु) अणु
				ND_PRINTK(2, warn,
					  "NA: invalid short link-layer address length\n");
				वापस;
			पूर्ण
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	ग_लिखो_lock_bh(&n->lock);
	अगर (lladdr_लघु) अणु
		ieee802154_be16_to_le16(&neigh->लघु_addr, lladdr_लघु);
		अगर (!lowpan_802154_is_valid_src_लघु_addr(neigh->लघु_addr))
			neigh->लघु_addr = cpu_to_le16(IEEE802154_ADDR_SHORT_UNSPEC);
	पूर्ण
	ग_लिखो_unlock_bh(&n->lock);
पूर्ण

अटल व्योम lowpan_ndisc_update(स्थिर काष्ठा net_device *dev,
				काष्ठा neighbour *n, u32 flags, u8 icmp6_type,
				स्थिर काष्ठा ndisc_options *nकरोpts)
अणु
	अगर (!lowpan_is_ll(dev, LOWPAN_LLTYPE_IEEE802154))
		वापस;

	/* react on overrides only. TODO check अगर this is really right. */
	अगर (flags & NEIGH_UPDATE_F_OVERRIDE)
		lowpan_ndisc_802154_update(n, flags, icmp6_type, nकरोpts);
पूर्ण

अटल पूर्णांक lowpan_ndisc_opt_addr_space(स्थिर काष्ठा net_device *dev,
				       u8 icmp6_type, काष्ठा neighbour *neigh,
				       u8 *ha_buf, u8 **ha)
अणु
	काष्ठा lowpan_802154_neigh *n;
	काष्ठा wpan_dev *wpan_dev;
	पूर्णांक addr_space = 0;

	अगर (!lowpan_is_ll(dev, LOWPAN_LLTYPE_IEEE802154))
		वापस 0;

	चयन (icmp6_type) अणु
	हाल NDISC_REसूचीECT:
		n = lowpan_802154_neigh(neighbour_priv(neigh));

		पढ़ो_lock_bh(&neigh->lock);
		अगर (lowpan_802154_is_valid_src_लघु_addr(n->लघु_addr)) अणु
			स_नकल(ha_buf, &n->लघु_addr,
			       IEEE802154_SHORT_ADDR_LEN);
			पढ़ो_unlock_bh(&neigh->lock);
			addr_space += __ndisc_opt_addr_space(IEEE802154_SHORT_ADDR_LEN, 0);
			*ha = ha_buf;
		पूर्ण अन्यथा अणु
			पढ़ो_unlock_bh(&neigh->lock);
		पूर्ण
		अवरोध;
	हाल NDISC_NEIGHBOUR_ADVERTISEMENT:
	हाल NDISC_NEIGHBOUR_SOLICITATION:
	हाल NDISC_ROUTER_SOLICITATION:
		wpan_dev = lowpan_802154_dev(dev)->wdev->ieee802154_ptr;

		अगर (lowpan_802154_is_valid_src_लघु_addr(wpan_dev->लघु_addr))
			addr_space = __ndisc_opt_addr_space(IEEE802154_SHORT_ADDR_LEN, 0);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस addr_space;
पूर्ण

अटल व्योम lowpan_ndisc_fill_addr_option(स्थिर काष्ठा net_device *dev,
					  काष्ठा sk_buff *skb, u8 icmp6_type,
					  स्थिर u8 *ha)
अणु
	काष्ठा wpan_dev *wpan_dev;
	__be16 लघु_addr;
	u8 opt_type;

	अगर (!lowpan_is_ll(dev, LOWPAN_LLTYPE_IEEE802154))
		वापस;

	चयन (icmp6_type) अणु
	हाल NDISC_REसूचीECT:
		अगर (ha) अणु
			ieee802154_le16_to_be16(&लघु_addr, ha);
			__ndisc_fill_addr_option(skb, ND_OPT_TARGET_LL_ADDR,
						 &लघु_addr,
						 IEEE802154_SHORT_ADDR_LEN, 0);
		पूर्ण
		वापस;
	हाल NDISC_NEIGHBOUR_ADVERTISEMENT:
		opt_type = ND_OPT_TARGET_LL_ADDR;
		अवरोध;
	हाल NDISC_ROUTER_SOLICITATION:
	हाल NDISC_NEIGHBOUR_SOLICITATION:
		opt_type = ND_OPT_SOURCE_LL_ADDR;
		अवरोध;
	शेष:
		वापस;
	पूर्ण

	wpan_dev = lowpan_802154_dev(dev)->wdev->ieee802154_ptr;

	अगर (lowpan_802154_is_valid_src_लघु_addr(wpan_dev->लघु_addr)) अणु
		ieee802154_le16_to_be16(&लघु_addr,
					&wpan_dev->लघु_addr);
		__ndisc_fill_addr_option(skb, opt_type, &लघु_addr,
					 IEEE802154_SHORT_ADDR_LEN, 0);
	पूर्ण
पूर्ण

अटल व्योम lowpan_ndisc_prefix_rcv_add_addr(काष्ठा net *net,
					     काष्ठा net_device *dev,
					     स्थिर काष्ठा prefix_info *pinfo,
					     काष्ठा inet6_dev *in6_dev,
					     काष्ठा in6_addr *addr,
					     पूर्णांक addr_type, u32 addr_flags,
					     bool sllao, bool tokenized,
					     __u32 valid_lft,
					     u32 prefered_lft,
					     bool dev_addr_generated)
अणु
	पूर्णांक err;

	/* generates लघु based address क्रम RA PIO's */
	अगर (lowpan_is_ll(dev, LOWPAN_LLTYPE_IEEE802154) && dev_addr_generated &&
	    !addrconf_अगरid_802154_6lowpan(addr->s6_addr + 8, dev)) अणु
		err = addrconf_prefix_rcv_add_addr(net, dev, pinfo, in6_dev,
						   addr, addr_type, addr_flags,
						   sllao, tokenized, valid_lft,
						   prefered_lft);
		अगर (err)
			ND_PRINTK(2, warn,
				  "RA: could not add a short address based address for prefix: %pI6c\n",
				  &pinfo->prefix);
	पूर्ण
पूर्ण
#पूर्ण_अगर

स्थिर काष्ठा ndisc_ops lowpan_ndisc_ops = अणु
	.is_useropt		= lowpan_ndisc_is_useropt,
#अगर IS_ENABLED(CONFIG_IEEE802154_6LOWPAN)
	.parse_options		= lowpan_ndisc_parse_options,
	.update			= lowpan_ndisc_update,
	.opt_addr_space		= lowpan_ndisc_opt_addr_space,
	.fill_addr_option	= lowpan_ndisc_fill_addr_option,
	.prefix_rcv_add_addr	= lowpan_ndisc_prefix_rcv_add_addr,
#पूर्ण_अगर
पूर्ण;
