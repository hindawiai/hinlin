<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *	6LoWPAN next header compression
 *
 *	Authors:
 *	Alexander Aring		<aar@pengutronix.de>
 */

#समावेश <linux/netdevice.h>

#समावेश <net/ipv6.h>

#समावेश "nhc.h"

अटल काष्ठा rb_root rb_root = RB_ROOT;
अटल काष्ठा lowpan_nhc *lowpan_nexthdr_nhcs[NEXTHDR_MAX + 1];
अटल DEFINE_SPINLOCK(lowpan_nhc_lock);

अटल पूर्णांक lowpan_nhc_insert(काष्ठा lowpan_nhc *nhc)
अणु
	काष्ठा rb_node **new = &rb_root.rb_node, *parent = शून्य;

	/* Figure out where to put new node */
	जबतक (*new) अणु
		काष्ठा lowpan_nhc *this = rb_entry(*new, काष्ठा lowpan_nhc,
						   node);
		पूर्णांक result, len_dअगर, len;

		len_dअगर = nhc->idlen - this->idlen;

		अगर (nhc->idlen < this->idlen)
			len = nhc->idlen;
		अन्यथा
			len = this->idlen;

		result = स_भेद(nhc->id, this->id, len);
		अगर (!result)
			result = len_dअगर;

		parent = *new;
		अगर (result < 0)
			new = &((*new)->rb_left);
		अन्यथा अगर (result > 0)
			new = &((*new)->rb_right);
		अन्यथा
			वापस -EEXIST;
	पूर्ण

	/* Add new node and rebalance tree. */
	rb_link_node(&nhc->node, parent, new);
	rb_insert_color(&nhc->node, &rb_root);

	वापस 0;
पूर्ण

अटल व्योम lowpan_nhc_हटाओ(काष्ठा lowpan_nhc *nhc)
अणु
	rb_erase(&nhc->node, &rb_root);
पूर्ण

अटल काष्ठा lowpan_nhc *lowpan_nhc_by_nhcid(स्थिर काष्ठा sk_buff *skb)
अणु
	काष्ठा rb_node *node = rb_root.rb_node;
	स्थिर u8 *nhcid_skb_ptr = skb->data;

	जबतक (node) अणु
		काष्ठा lowpan_nhc *nhc = rb_entry(node, काष्ठा lowpan_nhc,
						  node);
		u8 nhcid_skb_ptr_masked[LOWPAN_NHC_MAX_ID_LEN];
		पूर्णांक result, i;

		अगर (nhcid_skb_ptr + nhc->idlen > skb->data + skb->len)
			वापस शून्य;

		/* copy and mask afterwards the nhid value from skb */
		स_नकल(nhcid_skb_ptr_masked, nhcid_skb_ptr, nhc->idlen);
		क्रम (i = 0; i < nhc->idlen; i++)
			nhcid_skb_ptr_masked[i] &= nhc->idmask[i];

		result = स_भेद(nhcid_skb_ptr_masked, nhc->id, nhc->idlen);
		अगर (result < 0)
			node = node->rb_left;
		अन्यथा अगर (result > 0)
			node = node->rb_right;
		अन्यथा
			वापस nhc;
	पूर्ण

	वापस शून्य;
पूर्ण

पूर्णांक lowpan_nhc_check_compression(काष्ठा sk_buff *skb,
				 स्थिर काष्ठा ipv6hdr *hdr, u8 **hc_ptr)
अणु
	काष्ठा lowpan_nhc *nhc;
	पूर्णांक ret = 0;

	spin_lock_bh(&lowpan_nhc_lock);

	nhc = lowpan_nexthdr_nhcs[hdr->nexthdr];
	अगर (!(nhc && nhc->compress))
		ret = -ENOENT;

	spin_unlock_bh(&lowpan_nhc_lock);

	वापस ret;
पूर्ण

पूर्णांक lowpan_nhc_करो_compression(काष्ठा sk_buff *skb, स्थिर काष्ठा ipv6hdr *hdr,
			      u8 **hc_ptr)
अणु
	पूर्णांक ret;
	काष्ठा lowpan_nhc *nhc;

	spin_lock_bh(&lowpan_nhc_lock);

	nhc = lowpan_nexthdr_nhcs[hdr->nexthdr];
	/* check अगर the nhc module was हटाओd in unlocked part.
	 * TODO: this is a workaround we should prevent unloading
	 * of nhc modules जबतक unlocked part, this will always drop
	 * the lowpan packet but it's very unlikely.
	 *
	 * Solution isn't easy because we need to decide at
	 * lowpan_nhc_check_compression अगर we करो a compression or not.
	 * Because the अंतरभूत data which is added to skb, we can't move this
	 * handling.
	 */
	अगर (unlikely(!nhc || !nhc->compress)) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	/* In the हाल of RAW sockets the transport header is not set by
	 * the ip6 stack so we must set it ourselves
	 */
	अगर (skb->transport_header == skb->network_header)
		skb_set_transport_header(skb, माप(काष्ठा ipv6hdr));

	ret = nhc->compress(skb, hc_ptr);
	अगर (ret < 0)
		जाओ out;

	/* skip the transport header */
	skb_pull(skb, nhc->nexthdrlen);

out:
	spin_unlock_bh(&lowpan_nhc_lock);

	वापस ret;
पूर्ण

पूर्णांक lowpan_nhc_करो_uncompression(काष्ठा sk_buff *skb,
				स्थिर काष्ठा net_device *dev,
				काष्ठा ipv6hdr *hdr)
अणु
	काष्ठा lowpan_nhc *nhc;
	पूर्णांक ret;

	spin_lock_bh(&lowpan_nhc_lock);

	nhc = lowpan_nhc_by_nhcid(skb);
	अगर (nhc) अणु
		अगर (nhc->uncompress) अणु
			ret = nhc->uncompress(skb, माप(काष्ठा ipv6hdr) +
					      nhc->nexthdrlen);
			अगर (ret < 0) अणु
				spin_unlock_bh(&lowpan_nhc_lock);
				वापस ret;
			पूर्ण
		पूर्ण अन्यथा अणु
			spin_unlock_bh(&lowpan_nhc_lock);
			netdev_warn(dev, "received nhc id for %s which is not implemented.\n",
				    nhc->name);
			वापस -ENOTSUPP;
		पूर्ण
	पूर्ण अन्यथा अणु
		spin_unlock_bh(&lowpan_nhc_lock);
		netdev_warn(dev, "received unknown nhc id which was not found.\n");
		वापस -ENOENT;
	पूर्ण

	hdr->nexthdr = nhc->nexthdr;
	skb_reset_transport_header(skb);
	raw_dump_table(__func__, "raw transport header dump",
		       skb_transport_header(skb), nhc->nexthdrlen);

	spin_unlock_bh(&lowpan_nhc_lock);

	वापस 0;
पूर्ण

पूर्णांक lowpan_nhc_add(काष्ठा lowpan_nhc *nhc)
अणु
	पूर्णांक ret;

	अगर (!nhc->idlen || !nhc->idsetup)
		वापस -EINVAL;

	WARN_ONCE(nhc->idlen > LOWPAN_NHC_MAX_ID_LEN,
		  "LOWPAN_NHC_MAX_ID_LEN should be updated to %zd.\n",
		  nhc->idlen);

	nhc->idsetup(nhc);

	spin_lock_bh(&lowpan_nhc_lock);

	अगर (lowpan_nexthdr_nhcs[nhc->nexthdr]) अणु
		ret = -EEXIST;
		जाओ out;
	पूर्ण

	ret = lowpan_nhc_insert(nhc);
	अगर (ret < 0)
		जाओ out;

	lowpan_nexthdr_nhcs[nhc->nexthdr] = nhc;
out:
	spin_unlock_bh(&lowpan_nhc_lock);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(lowpan_nhc_add);

व्योम lowpan_nhc_del(काष्ठा lowpan_nhc *nhc)
अणु
	spin_lock_bh(&lowpan_nhc_lock);

	lowpan_nhc_हटाओ(nhc);
	lowpan_nexthdr_nhcs[nhc->nexthdr] = शून्य;

	spin_unlock_bh(&lowpan_nhc_lock);

	synchronize_net();
पूर्ण
EXPORT_SYMBOL(lowpan_nhc_del);
