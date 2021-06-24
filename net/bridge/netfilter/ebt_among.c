<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  ebt_among
 *
 *	Authors:
 *	Grzegorz Borowiak <grzes@gnu.univ.gda.pl>
 *
 *  August, 2003
 *
 */
#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt
#समावेश <linux/ip.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/module.h>
#समावेश <linux/netfilter/x_tables.h>
#समावेश <linux/netfilter_bridge/ebtables.h>
#समावेश <linux/netfilter_bridge/ebt_among.h>

अटल bool ebt_mac_wormhash_contains(स्थिर काष्ठा ebt_mac_wormhash *wh,
				      स्थिर अक्षर *mac, __be32 ip)
अणु
	/* You may be puzzled as to how this code works.
	 * Some tricks were used, refer to
	 * 	include/linux/netfilter_bridge/ebt_among.h
	 * as there you can find a solution of this mystery.
	 */
	स्थिर काष्ठा ebt_mac_wormhash_tuple *p;
	पूर्णांक start, limit, i;
	uपूर्णांक32_t cmp[2] = अणु 0, 0 पूर्ण;
	पूर्णांक key = ((स्थिर अचिन्हित अक्षर *)mac)[5];

	ether_addr_copy(((अक्षर *) cmp) + 2, mac);
	start = wh->table[key];
	limit = wh->table[key + 1];
	अगर (ip) अणु
		क्रम (i = start; i < limit; i++) अणु
			p = &wh->pool[i];
			अगर (cmp[1] == p->cmp[1] && cmp[0] == p->cmp[0])
				अगर (p->ip == 0 || p->ip == ip)
					वापस true;
		पूर्ण
	पूर्ण अन्यथा अणु
		क्रम (i = start; i < limit; i++) अणु
			p = &wh->pool[i];
			अगर (cmp[1] == p->cmp[1] && cmp[0] == p->cmp[0])
				अगर (p->ip == 0)
					वापस true;
		पूर्ण
	पूर्ण
	वापस false;
पूर्ण

अटल पूर्णांक ebt_mac_wormhash_check_पूर्णांकegrity(स्थिर काष्ठा ebt_mac_wormhash
					    *wh)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 256; i++) अणु
		अगर (wh->table[i] > wh->table[i + 1])
			वापस -0x100 - i;
		अगर (wh->table[i] < 0)
			वापस -0x200 - i;
		अगर (wh->table[i] > wh->poolsize)
			वापस -0x300 - i;
	पूर्ण
	अगर (wh->table[256] > wh->poolsize)
		वापस -0xc00;
	वापस 0;
पूर्ण

अटल पूर्णांक get_ip_dst(स्थिर काष्ठा sk_buff *skb, __be32 *addr)
अणु
	अगर (eth_hdr(skb)->h_proto == htons(ETH_P_IP)) अणु
		स्थिर काष्ठा iphdr *ih;
		काष्ठा iphdr _iph;

		ih = skb_header_poपूर्णांकer(skb, 0, माप(_iph), &_iph);
		अगर (ih == शून्य)
			वापस -1;
		*addr = ih->daddr;
	पूर्ण अन्यथा अगर (eth_hdr(skb)->h_proto == htons(ETH_P_ARP)) अणु
		स्थिर काष्ठा arphdr *ah;
		काष्ठा arphdr _arph;
		स्थिर __be32 *bp;
		__be32 buf;

		ah = skb_header_poपूर्णांकer(skb, 0, माप(_arph), &_arph);
		अगर (ah == शून्य ||
		    ah->ar_pln != माप(__be32) ||
		    ah->ar_hln != ETH_ALEN)
			वापस -1;
		bp = skb_header_poपूर्णांकer(skb, माप(काष्ठा arphdr) +
					2 * ETH_ALEN + माप(__be32),
					माप(__be32), &buf);
		अगर (bp == शून्य)
			वापस -1;
		*addr = *bp;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक get_ip_src(स्थिर काष्ठा sk_buff *skb, __be32 *addr)
अणु
	अगर (eth_hdr(skb)->h_proto == htons(ETH_P_IP)) अणु
		स्थिर काष्ठा iphdr *ih;
		काष्ठा iphdr _iph;

		ih = skb_header_poपूर्णांकer(skb, 0, माप(_iph), &_iph);
		अगर (ih == शून्य)
			वापस -1;
		*addr = ih->saddr;
	पूर्ण अन्यथा अगर (eth_hdr(skb)->h_proto == htons(ETH_P_ARP)) अणु
		स्थिर काष्ठा arphdr *ah;
		काष्ठा arphdr _arph;
		स्थिर __be32 *bp;
		__be32 buf;

		ah = skb_header_poपूर्णांकer(skb, 0, माप(_arph), &_arph);
		अगर (ah == शून्य ||
		    ah->ar_pln != माप(__be32) ||
		    ah->ar_hln != ETH_ALEN)
			वापस -1;
		bp = skb_header_poपूर्णांकer(skb, माप(काष्ठा arphdr) +
					ETH_ALEN, माप(__be32), &buf);
		अगर (bp == शून्य)
			वापस -1;
		*addr = *bp;
	पूर्ण
	वापस 0;
पूर्ण

अटल bool
ebt_among_mt(स्थिर काष्ठा sk_buff *skb, काष्ठा xt_action_param *par)
अणु
	स्थिर काष्ठा ebt_among_info *info = par->matchinfo;
	स्थिर अक्षर *dmac, *smac;
	स्थिर काष्ठा ebt_mac_wormhash *wh_dst, *wh_src;
	__be32 dip = 0, sip = 0;

	wh_dst = ebt_among_wh_dst(info);
	wh_src = ebt_among_wh_src(info);

	अगर (wh_src) अणु
		smac = eth_hdr(skb)->h_source;
		अगर (get_ip_src(skb, &sip))
			वापस false;
		अगर (!(info->biपंचांगask & EBT_AMONG_SRC_NEG)) अणु
			/* we match only अगर it contains */
			अगर (!ebt_mac_wormhash_contains(wh_src, smac, sip))
				वापस false;
		पूर्ण अन्यथा अणु
			/* we match only अगर it DOES NOT contain */
			अगर (ebt_mac_wormhash_contains(wh_src, smac, sip))
				वापस false;
		पूर्ण
	पूर्ण

	अगर (wh_dst) अणु
		dmac = eth_hdr(skb)->h_dest;
		अगर (get_ip_dst(skb, &dip))
			वापस false;
		अगर (!(info->biपंचांगask & EBT_AMONG_DST_NEG)) अणु
			/* we match only अगर it contains */
			अगर (!ebt_mac_wormhash_contains(wh_dst, dmac, dip))
				वापस false;
		पूर्ण अन्यथा अणु
			/* we match only अगर it DOES NOT contain */
			अगर (ebt_mac_wormhash_contains(wh_dst, dmac, dip))
				वापस false;
		पूर्ण
	पूर्ण

	वापस true;
पूर्ण

अटल bool poolsize_invalid(स्थिर काष्ठा ebt_mac_wormhash *w)
अणु
	वापस w && w->poolsize >= (पूर्णांक_उच्च / माप(काष्ठा ebt_mac_wormhash_tuple));
पूर्ण

अटल bool wormhash_offset_invalid(पूर्णांक off, अचिन्हित पूर्णांक len)
अणु
	अगर (off == 0) /* not present */
		वापस false;

	अगर (off < (पूर्णांक)माप(काष्ठा ebt_among_info) ||
	    off % __alignof__(काष्ठा ebt_mac_wormhash))
		वापस true;

	off += माप(काष्ठा ebt_mac_wormhash);

	वापस off > len;
पूर्ण

अटल bool wormhash_sizes_valid(स्थिर काष्ठा ebt_mac_wormhash *wh, पूर्णांक a, पूर्णांक b)
अणु
	अगर (a == 0)
		a = माप(काष्ठा ebt_among_info);

	वापस ebt_mac_wormhash_size(wh) + a == b;
पूर्ण

अटल पूर्णांक ebt_among_mt_check(स्थिर काष्ठा xt_mtchk_param *par)
अणु
	स्थिर काष्ठा ebt_among_info *info = par->matchinfo;
	स्थिर काष्ठा ebt_entry_match *em =
		container_of(par->matchinfo, स्थिर काष्ठा ebt_entry_match, data);
	अचिन्हित पूर्णांक expected_length = माप(काष्ठा ebt_among_info);
	स्थिर काष्ठा ebt_mac_wormhash *wh_dst, *wh_src;
	पूर्णांक err;

	अगर (expected_length > em->match_size)
		वापस -EINVAL;

	अगर (wormhash_offset_invalid(info->wh_dst_ofs, em->match_size) ||
	    wormhash_offset_invalid(info->wh_src_ofs, em->match_size))
		वापस -EINVAL;

	wh_dst = ebt_among_wh_dst(info);
	अगर (poolsize_invalid(wh_dst))
		वापस -EINVAL;

	expected_length += ebt_mac_wormhash_size(wh_dst);
	अगर (expected_length > em->match_size)
		वापस -EINVAL;

	wh_src = ebt_among_wh_src(info);
	अगर (poolsize_invalid(wh_src))
		वापस -EINVAL;

	अगर (info->wh_src_ofs < info->wh_dst_ofs) अणु
		अगर (!wormhash_sizes_valid(wh_src, info->wh_src_ofs, info->wh_dst_ofs))
			वापस -EINVAL;
	पूर्ण अन्यथा अणु
		अगर (!wormhash_sizes_valid(wh_dst, info->wh_dst_ofs, info->wh_src_ofs))
			वापस -EINVAL;
	पूर्ण

	expected_length += ebt_mac_wormhash_size(wh_src);

	अगर (em->match_size != EBT_ALIGN(expected_length)) अणु
		pr_err_ratelimited("wrong size: %d against expected %d, rounded to %zd\n",
				   em->match_size, expected_length,
				   EBT_ALIGN(expected_length));
		वापस -EINVAL;
	पूर्ण
	अगर (wh_dst && (err = ebt_mac_wormhash_check_पूर्णांकegrity(wh_dst))) अणु
		pr_err_ratelimited("dst integrity fail: %x\n", -err);
		वापस -EINVAL;
	पूर्ण
	अगर (wh_src && (err = ebt_mac_wormhash_check_पूर्णांकegrity(wh_src))) अणु
		pr_err_ratelimited("src integrity fail: %x\n", -err);
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल काष्ठा xt_match ebt_among_mt_reg __पढ़ो_mostly = अणु
	.name		= "among",
	.revision	= 0,
	.family		= NFPROTO_BRIDGE,
	.match		= ebt_among_mt,
	.checkentry	= ebt_among_mt_check,
	.matchsize	= -1, /* special हाल */
	.me		= THIS_MODULE,
पूर्ण;

अटल पूर्णांक __init ebt_among_init(व्योम)
अणु
	वापस xt_रेजिस्टर_match(&ebt_among_mt_reg);
पूर्ण

अटल व्योम __निकास ebt_among_fini(व्योम)
अणु
	xt_unरेजिस्टर_match(&ebt_among_mt_reg);
पूर्ण

module_init(ebt_among_init);
module_निकास(ebt_among_fini);
MODULE_DESCRIPTION("Ebtables: Combined MAC/IP address list matching");
MODULE_LICENSE("GPL");
