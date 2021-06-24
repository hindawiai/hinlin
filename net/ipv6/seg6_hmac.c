<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  SR-IPv6 implementation -- HMAC functions
 *
 *  Author:
 *  David Lebrun <david.lebrun@uclouvain.be>
 */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/socket.h>
#समावेश <linux/sockios.h>
#समावेश <linux/net.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/in6.h>
#समावेश <linux/icmpv6.h>
#समावेश <linux/mroute6.h>
#समावेश <linux/slab.h>
#समावेश <linux/rhashtable.h>

#समावेश <linux/netfilter.h>
#समावेश <linux/netfilter_ipv6.h>

#समावेश <net/sock.h>
#समावेश <net/snmp.h>

#समावेश <net/ipv6.h>
#समावेश <net/protocol.h>
#समावेश <net/transp_v6.h>
#समावेश <net/rawv6.h>
#समावेश <net/ndisc.h>
#समावेश <net/ip6_route.h>
#समावेश <net/addrconf.h>
#समावेश <net/xfrm.h>

#समावेश <crypto/hash.h>
#समावेश <net/seg6.h>
#समावेश <net/genetlink.h>
#समावेश <net/seg6_hmac.h>
#समावेश <linux/अक्रमom.h>

अटल DEFINE_PER_CPU(अक्षर [SEG6_HMAC_RING_SIZE], hmac_ring);

अटल पूर्णांक seg6_hmac_cmpfn(काष्ठा rhashtable_compare_arg *arg, स्थिर व्योम *obj)
अणु
	स्थिर काष्ठा seg6_hmac_info *hinfo = obj;

	वापस (hinfo->hmackeyid != *(__u32 *)arg->key);
पूर्ण

अटल अंतरभूत व्योम seg6_hinfo_release(काष्ठा seg6_hmac_info *hinfo)
अणु
	kमुक्त_rcu(hinfo, rcu);
पूर्ण

अटल व्योम seg6_मुक्त_hi(व्योम *ptr, व्योम *arg)
अणु
	काष्ठा seg6_hmac_info *hinfo = (काष्ठा seg6_hmac_info *)ptr;

	अगर (hinfo)
		seg6_hinfo_release(hinfo);
पूर्ण

अटल स्थिर काष्ठा rhashtable_params rht_params = अणु
	.head_offset		= दुरत्व(काष्ठा seg6_hmac_info, node),
	.key_offset		= दुरत्व(काष्ठा seg6_hmac_info, hmackeyid),
	.key_len		= माप(u32),
	.स्वतःmatic_shrinking	= true,
	.obj_cmpfn		= seg6_hmac_cmpfn,
पूर्ण;

अटल काष्ठा seg6_hmac_algo hmac_algos[] = अणु
	अणु
		.alg_id = SEG6_HMAC_ALGO_SHA1,
		.name = "hmac(sha1)",
	पूर्ण,
	अणु
		.alg_id = SEG6_HMAC_ALGO_SHA256,
		.name = "hmac(sha256)",
	पूर्ण,
पूर्ण;

अटल काष्ठा sr6_tlv_hmac *seg6_get_tlv_hmac(काष्ठा ipv6_sr_hdr *srh)
अणु
	काष्ठा sr6_tlv_hmac *tlv;

	अगर (srh->hdrlen < (srh->first_segment + 1) * 2 + 5)
		वापस शून्य;

	अगर (!sr_has_hmac(srh))
		वापस शून्य;

	tlv = (काष्ठा sr6_tlv_hmac *)
	      ((अक्षर *)srh + ((srh->hdrlen + 1) << 3) - 40);

	अगर (tlv->tlvhdr.type != SR6_TLV_HMAC || tlv->tlvhdr.len != 38)
		वापस शून्य;

	वापस tlv;
पूर्ण

अटल काष्ठा seg6_hmac_algo *__hmac_get_algo(u8 alg_id)
अणु
	काष्ठा seg6_hmac_algo *algo;
	पूर्णांक i, alg_count;

	alg_count = ARRAY_SIZE(hmac_algos);
	क्रम (i = 0; i < alg_count; i++) अणु
		algo = &hmac_algos[i];
		अगर (algo->alg_id == alg_id)
			वापस algo;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल पूर्णांक __करो_hmac(काष्ठा seg6_hmac_info *hinfo, स्थिर अक्षर *text, u8 psize,
		     u8 *output, पूर्णांक outlen)
अणु
	काष्ठा seg6_hmac_algo *algo;
	काष्ठा crypto_shash *tfm;
	काष्ठा shash_desc *shash;
	पूर्णांक ret, dgsize;

	algo = __hmac_get_algo(hinfo->alg_id);
	अगर (!algo)
		वापस -ENOENT;

	tfm = *this_cpu_ptr(algo->tfms);

	dgsize = crypto_shash_digestsize(tfm);
	अगर (dgsize > outlen) अणु
		pr_debug("sr-ipv6: __do_hmac: digest size too big (%d / %d)\n",
			 dgsize, outlen);
		वापस -ENOMEM;
	पूर्ण

	ret = crypto_shash_setkey(tfm, hinfo->secret, hinfo->slen);
	अगर (ret < 0) अणु
		pr_debug("sr-ipv6: crypto_shash_setkey failed: err %d\n", ret);
		जाओ failed;
	पूर्ण

	shash = *this_cpu_ptr(algo->shashs);
	shash->tfm = tfm;

	ret = crypto_shash_digest(shash, text, psize, output);
	अगर (ret < 0) अणु
		pr_debug("sr-ipv6: crypto_shash_digest failed: err %d\n", ret);
		जाओ failed;
	पूर्ण

	वापस dgsize;

failed:
	वापस ret;
पूर्ण

पूर्णांक seg6_hmac_compute(काष्ठा seg6_hmac_info *hinfo, काष्ठा ipv6_sr_hdr *hdr,
		      काष्ठा in6_addr *saddr, u8 *output)
अणु
	__be32 hmackeyid = cpu_to_be32(hinfo->hmackeyid);
	u8 पंचांगp_out[SEG6_HMAC_MAX_DIGESTSIZE];
	पूर्णांक plen, i, dgsize, wrsize;
	अक्षर *ring, *off;

	/* a 160-byte buffer क्रम digest output allows to store highest known
	 * hash function (RadioGatun) with up to 1216 bits
	 */

	/* saddr(16) + first_seg(1) + flags(1) + keyid(4) + seglist(16n) */
	plen = 16 + 1 + 1 + 4 + (hdr->first_segment + 1) * 16;

	/* this limit allows क्रम 14 segments */
	अगर (plen >= SEG6_HMAC_RING_SIZE)
		वापस -EMSGSIZE;

	/* Let's build the HMAC text on the ring buffer. The text is composed
	 * as follows, in order:
	 *
	 * 1. Source IPv6 address (128 bits)
	 * 2. first_segment value (8 bits)
	 * 3. Flags (8 bits)
	 * 4. HMAC Key ID (32 bits)
	 * 5. All segments in the segments list (n * 128 bits)
	 */

	local_bh_disable();
	ring = this_cpu_ptr(hmac_ring);
	off = ring;

	/* source address */
	स_नकल(off, saddr, 16);
	off += 16;

	/* first_segment value */
	*off++ = hdr->first_segment;

	/* flags */
	*off++ = hdr->flags;

	/* HMAC Key ID */
	स_नकल(off, &hmackeyid, 4);
	off += 4;

	/* all segments in the list */
	क्रम (i = 0; i < hdr->first_segment + 1; i++) अणु
		स_नकल(off, hdr->segments + i, 16);
		off += 16;
	पूर्ण

	dgsize = __करो_hmac(hinfo, ring, plen, पंचांगp_out,
			   SEG6_HMAC_MAX_DIGESTSIZE);
	local_bh_enable();

	अगर (dgsize < 0)
		वापस dgsize;

	wrsize = SEG6_HMAC_FIELD_LEN;
	अगर (wrsize > dgsize)
		wrsize = dgsize;

	स_रखो(output, 0, SEG6_HMAC_FIELD_LEN);
	स_नकल(output, पंचांगp_out, wrsize);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(seg6_hmac_compute);

/* checks अगर an incoming SR-enabled packet's HMAC status matches
 * the incoming policy.
 *
 * called with rcu_पढ़ो_lock()
 */
bool seg6_hmac_validate_skb(काष्ठा sk_buff *skb)
अणु
	u8 hmac_output[SEG6_HMAC_FIELD_LEN];
	काष्ठा net *net = dev_net(skb->dev);
	काष्ठा seg6_hmac_info *hinfo;
	काष्ठा sr6_tlv_hmac *tlv;
	काष्ठा ipv6_sr_hdr *srh;
	काष्ठा inet6_dev *idev;

	idev = __in6_dev_get(skb->dev);

	srh = (काष्ठा ipv6_sr_hdr *)skb_transport_header(skb);

	tlv = seg6_get_tlv_hmac(srh);

	/* mandatory check but no tlv */
	अगर (idev->cnf.seg6_require_hmac > 0 && !tlv)
		वापस false;

	/* no check */
	अगर (idev->cnf.seg6_require_hmac < 0)
		वापस true;

	/* check only अगर present */
	अगर (idev->cnf.seg6_require_hmac == 0 && !tlv)
		वापस true;

	/* now, seg6_require_hmac >= 0 && tlv */

	hinfo = seg6_hmac_info_lookup(net, be32_to_cpu(tlv->hmackeyid));
	अगर (!hinfo)
		वापस false;

	अगर (seg6_hmac_compute(hinfo, srh, &ipv6_hdr(skb)->saddr, hmac_output))
		वापस false;

	अगर (स_भेद(hmac_output, tlv->hmac, SEG6_HMAC_FIELD_LEN) != 0)
		वापस false;

	वापस true;
पूर्ण
EXPORT_SYMBOL(seg6_hmac_validate_skb);

/* called with rcu_पढ़ो_lock() */
काष्ठा seg6_hmac_info *seg6_hmac_info_lookup(काष्ठा net *net, u32 key)
अणु
	काष्ठा seg6_pernet_data *sdata = seg6_pernet(net);
	काष्ठा seg6_hmac_info *hinfo;

	hinfo = rhashtable_lookup_fast(&sdata->hmac_infos, &key, rht_params);

	वापस hinfo;
पूर्ण
EXPORT_SYMBOL(seg6_hmac_info_lookup);

पूर्णांक seg6_hmac_info_add(काष्ठा net *net, u32 key, काष्ठा seg6_hmac_info *hinfo)
अणु
	काष्ठा seg6_pernet_data *sdata = seg6_pernet(net);
	पूर्णांक err;

	err = rhashtable_lookup_insert_fast(&sdata->hmac_infos, &hinfo->node,
					    rht_params);

	वापस err;
पूर्ण
EXPORT_SYMBOL(seg6_hmac_info_add);

पूर्णांक seg6_hmac_info_del(काष्ठा net *net, u32 key)
अणु
	काष्ठा seg6_pernet_data *sdata = seg6_pernet(net);
	काष्ठा seg6_hmac_info *hinfo;
	पूर्णांक err = -ENOENT;

	hinfo = rhashtable_lookup_fast(&sdata->hmac_infos, &key, rht_params);
	अगर (!hinfo)
		जाओ out;

	err = rhashtable_हटाओ_fast(&sdata->hmac_infos, &hinfo->node,
				     rht_params);
	अगर (err)
		जाओ out;

	seg6_hinfo_release(hinfo);

out:
	वापस err;
पूर्ण
EXPORT_SYMBOL(seg6_hmac_info_del);

पूर्णांक seg6_push_hmac(काष्ठा net *net, काष्ठा in6_addr *saddr,
		   काष्ठा ipv6_sr_hdr *srh)
अणु
	काष्ठा seg6_hmac_info *hinfo;
	काष्ठा sr6_tlv_hmac *tlv;
	पूर्णांक err = -ENOENT;

	tlv = seg6_get_tlv_hmac(srh);
	अगर (!tlv)
		वापस -EINVAL;

	rcu_पढ़ो_lock();

	hinfo = seg6_hmac_info_lookup(net, be32_to_cpu(tlv->hmackeyid));
	अगर (!hinfo)
		जाओ out;

	स_रखो(tlv->hmac, 0, SEG6_HMAC_FIELD_LEN);
	err = seg6_hmac_compute(hinfo, srh, saddr, tlv->hmac);

out:
	rcu_पढ़ो_unlock();
	वापस err;
पूर्ण
EXPORT_SYMBOL(seg6_push_hmac);

अटल पूर्णांक seg6_hmac_init_algo(व्योम)
अणु
	काष्ठा seg6_hmac_algo *algo;
	काष्ठा crypto_shash *tfm;
	काष्ठा shash_desc *shash;
	पूर्णांक i, alg_count, cpu;

	alg_count = ARRAY_SIZE(hmac_algos);

	क्रम (i = 0; i < alg_count; i++) अणु
		काष्ठा crypto_shash **p_tfm;
		पूर्णांक shsize;

		algo = &hmac_algos[i];
		algo->tfms = alloc_percpu(काष्ठा crypto_shash *);
		अगर (!algo->tfms)
			वापस -ENOMEM;

		क्रम_each_possible_cpu(cpu) अणु
			tfm = crypto_alloc_shash(algo->name, 0, 0);
			अगर (IS_ERR(tfm))
				वापस PTR_ERR(tfm);
			p_tfm = per_cpu_ptr(algo->tfms, cpu);
			*p_tfm = tfm;
		पूर्ण

		p_tfm = raw_cpu_ptr(algo->tfms);
		tfm = *p_tfm;

		shsize = माप(*shash) + crypto_shash_descsize(tfm);

		algo->shashs = alloc_percpu(काष्ठा shash_desc *);
		अगर (!algo->shashs)
			वापस -ENOMEM;

		क्रम_each_possible_cpu(cpu) अणु
			shash = kzalloc_node(shsize, GFP_KERNEL,
					     cpu_to_node(cpu));
			अगर (!shash)
				वापस -ENOMEM;
			*per_cpu_ptr(algo->shashs, cpu) = shash;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक __init seg6_hmac_init(व्योम)
अणु
	वापस seg6_hmac_init_algo();
पूर्ण
EXPORT_SYMBOL(seg6_hmac_init);

पूर्णांक __net_init seg6_hmac_net_init(काष्ठा net *net)
अणु
	काष्ठा seg6_pernet_data *sdata = seg6_pernet(net);

	rhashtable_init(&sdata->hmac_infos, &rht_params);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(seg6_hmac_net_init);

व्योम seg6_hmac_निकास(व्योम)
अणु
	काष्ठा seg6_hmac_algo *algo = शून्य;
	पूर्णांक i, alg_count, cpu;

	alg_count = ARRAY_SIZE(hmac_algos);
	क्रम (i = 0; i < alg_count; i++) अणु
		algo = &hmac_algos[i];
		क्रम_each_possible_cpu(cpu) अणु
			काष्ठा crypto_shash *tfm;
			काष्ठा shash_desc *shash;

			shash = *per_cpu_ptr(algo->shashs, cpu);
			kमुक्त(shash);
			tfm = *per_cpu_ptr(algo->tfms, cpu);
			crypto_मुक्त_shash(tfm);
		पूर्ण
		मुक्त_percpu(algo->tfms);
		मुक्त_percpu(algo->shashs);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(seg6_hmac_निकास);

व्योम __net_निकास seg6_hmac_net_निकास(काष्ठा net *net)
अणु
	काष्ठा seg6_pernet_data *sdata = seg6_pernet(net);

	rhashtable_मुक्त_and_destroy(&sdata->hmac_infos, seg6_मुक्त_hi, शून्य);
पूर्ण
EXPORT_SYMBOL(seg6_hmac_net_निकास);
