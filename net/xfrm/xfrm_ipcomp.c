<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * IP Payload Compression Protocol (IPComp) - RFC3173.
 *
 * Copyright (c) 2003 James Morris <jmorris@पूर्णांकercode.com.au>
 * Copyright (c) 2003-2008 Herbert Xu <herbert@gonकरोr.apana.org.au>
 *
 * Toकरो:
 *   - Tunable compression parameters.
 *   - Compression stats.
 *   - Adaptive compression.
 */

#समावेश <linux/crypto.h>
#समावेश <linux/err.h>
#समावेश <linux/list.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/percpu.h>
#समावेश <linux/slab.h>
#समावेश <linux/smp.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <net/ip.h>
#समावेश <net/ipcomp.h>
#समावेश <net/xfrm.h>

काष्ठा ipcomp_tfms अणु
	काष्ठा list_head list;
	काष्ठा crypto_comp * __percpu *tfms;
	पूर्णांक users;
पूर्ण;

अटल DEFINE_MUTEX(ipcomp_resource_mutex);
अटल व्योम * __percpu *ipcomp_scratches;
अटल पूर्णांक ipcomp_scratch_users;
अटल LIST_HEAD(ipcomp_tfms_list);

अटल पूर्णांक ipcomp_decompress(काष्ठा xfrm_state *x, काष्ठा sk_buff *skb)
अणु
	काष्ठा ipcomp_data *ipcd = x->data;
	स्थिर पूर्णांक plen = skb->len;
	पूर्णांक dlen = IPCOMP_SCRATCH_SIZE;
	स्थिर u8 *start = skb->data;
	u8 *scratch = *this_cpu_ptr(ipcomp_scratches);
	काष्ठा crypto_comp *tfm = *this_cpu_ptr(ipcd->tfms);
	पूर्णांक err = crypto_comp_decompress(tfm, start, plen, scratch, &dlen);
	पूर्णांक len;

	अगर (err)
		वापस err;

	अगर (dlen < (plen + माप(काष्ठा ip_comp_hdr)))
		वापस -EINVAL;

	len = dlen - plen;
	अगर (len > skb_tailroom(skb))
		len = skb_tailroom(skb);

	__skb_put(skb, len);

	len += plen;
	skb_copy_to_linear_data(skb, scratch, len);

	जबतक ((scratch += len, dlen -= len) > 0) अणु
		skb_frag_t *frag;
		काष्ठा page *page;

		अगर (WARN_ON(skb_shinfo(skb)->nr_frags >= MAX_SKB_FRAGS))
			वापस -EMSGSIZE;

		frag = skb_shinfo(skb)->frags + skb_shinfo(skb)->nr_frags;
		page = alloc_page(GFP_ATOMIC);

		अगर (!page)
			वापस -ENOMEM;

		__skb_frag_set_page(frag, page);

		len = PAGE_SIZE;
		अगर (dlen < len)
			len = dlen;

		skb_frag_off_set(frag, 0);
		skb_frag_size_set(frag, len);
		स_नकल(skb_frag_address(frag), scratch, len);

		skb->truesize += len;
		skb->data_len += len;
		skb->len += len;

		skb_shinfo(skb)->nr_frags++;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक ipcomp_input(काष्ठा xfrm_state *x, काष्ठा sk_buff *skb)
अणु
	पूर्णांक nexthdr;
	पूर्णांक err = -ENOMEM;
	काष्ठा ip_comp_hdr *ipch;

	अगर (skb_linearize_cow(skb))
		जाओ out;

	skb->ip_summed = CHECKSUM_NONE;

	/* Remove ipcomp header and decompress original payload */
	ipch = (व्योम *)skb->data;
	nexthdr = ipch->nexthdr;

	skb->transport_header = skb->network_header + माप(*ipch);
	__skb_pull(skb, माप(*ipch));
	err = ipcomp_decompress(x, skb);
	अगर (err)
		जाओ out;

	err = nexthdr;

out:
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(ipcomp_input);

अटल पूर्णांक ipcomp_compress(काष्ठा xfrm_state *x, काष्ठा sk_buff *skb)
अणु
	काष्ठा ipcomp_data *ipcd = x->data;
	स्थिर पूर्णांक plen = skb->len;
	पूर्णांक dlen = IPCOMP_SCRATCH_SIZE;
	u8 *start = skb->data;
	काष्ठा crypto_comp *tfm;
	u8 *scratch;
	पूर्णांक err;

	local_bh_disable();
	scratch = *this_cpu_ptr(ipcomp_scratches);
	tfm = *this_cpu_ptr(ipcd->tfms);
	err = crypto_comp_compress(tfm, start, plen, scratch, &dlen);
	अगर (err)
		जाओ out;

	अगर ((dlen + माप(काष्ठा ip_comp_hdr)) >= plen) अणु
		err = -EMSGSIZE;
		जाओ out;
	पूर्ण

	स_नकल(start + माप(काष्ठा ip_comp_hdr), scratch, dlen);
	local_bh_enable();

	pskb_trim(skb, dlen + माप(काष्ठा ip_comp_hdr));
	वापस 0;

out:
	local_bh_enable();
	वापस err;
पूर्ण

पूर्णांक ipcomp_output(काष्ठा xfrm_state *x, काष्ठा sk_buff *skb)
अणु
	पूर्णांक err;
	काष्ठा ip_comp_hdr *ipch;
	काष्ठा ipcomp_data *ipcd = x->data;

	अगर (skb->len < ipcd->threshold) अणु
		/* Don't bother compressing */
		जाओ out_ok;
	पूर्ण

	अगर (skb_linearize_cow(skb))
		जाओ out_ok;

	err = ipcomp_compress(x, skb);

	अगर (err) अणु
		जाओ out_ok;
	पूर्ण

	/* Install ipcomp header, convert पूर्णांकo ipcomp datagram. */
	ipch = ip_comp_hdr(skb);
	ipch->nexthdr = *skb_mac_header(skb);
	ipch->flags = 0;
	ipch->cpi = htons((u16 )ntohl(x->id.spi));
	*skb_mac_header(skb) = IPPROTO_COMP;
out_ok:
	skb_push(skb, -skb_network_offset(skb));
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(ipcomp_output);

अटल व्योम ipcomp_मुक्त_scratches(व्योम)
अणु
	पूर्णांक i;
	व्योम * __percpu *scratches;

	अगर (--ipcomp_scratch_users)
		वापस;

	scratches = ipcomp_scratches;
	अगर (!scratches)
		वापस;

	क्रम_each_possible_cpu(i)
		vमुक्त(*per_cpu_ptr(scratches, i));

	मुक्त_percpu(scratches);
पूर्ण

अटल व्योम * __percpu *ipcomp_alloc_scratches(व्योम)
अणु
	व्योम * __percpu *scratches;
	पूर्णांक i;

	अगर (ipcomp_scratch_users++)
		वापस ipcomp_scratches;

	scratches = alloc_percpu(व्योम *);
	अगर (!scratches)
		वापस शून्य;

	ipcomp_scratches = scratches;

	क्रम_each_possible_cpu(i) अणु
		व्योम *scratch;

		scratch = vदो_स्मृति_node(IPCOMP_SCRATCH_SIZE, cpu_to_node(i));
		अगर (!scratch)
			वापस शून्य;
		*per_cpu_ptr(scratches, i) = scratch;
	पूर्ण

	वापस scratches;
पूर्ण

अटल व्योम ipcomp_मुक्त_tfms(काष्ठा crypto_comp * __percpu *tfms)
अणु
	काष्ठा ipcomp_tfms *pos;
	पूर्णांक cpu;

	list_क्रम_each_entry(pos, &ipcomp_tfms_list, list) अणु
		अगर (pos->tfms == tfms)
			अवरोध;
	पूर्ण

	WARN_ON(!pos);

	अगर (--pos->users)
		वापस;

	list_del(&pos->list);
	kमुक्त(pos);

	अगर (!tfms)
		वापस;

	क्रम_each_possible_cpu(cpu) अणु
		काष्ठा crypto_comp *tfm = *per_cpu_ptr(tfms, cpu);
		crypto_मुक्त_comp(tfm);
	पूर्ण
	मुक्त_percpu(tfms);
पूर्ण

अटल काष्ठा crypto_comp * __percpu *ipcomp_alloc_tfms(स्थिर अक्षर *alg_name)
अणु
	काष्ठा ipcomp_tfms *pos;
	काष्ठा crypto_comp * __percpu *tfms;
	पूर्णांक cpu;


	list_क्रम_each_entry(pos, &ipcomp_tfms_list, list) अणु
		काष्ठा crypto_comp *tfm;

		/* This can be any valid CPU ID so we करोn't need locking. */
		tfm = this_cpu_पढ़ो(*pos->tfms);

		अगर (!म_भेद(crypto_comp_name(tfm), alg_name)) अणु
			pos->users++;
			वापस pos->tfms;
		पूर्ण
	पूर्ण

	pos = kदो_स्मृति(माप(*pos), GFP_KERNEL);
	अगर (!pos)
		वापस शून्य;

	pos->users = 1;
	INIT_LIST_HEAD(&pos->list);
	list_add(&pos->list, &ipcomp_tfms_list);

	pos->tfms = tfms = alloc_percpu(काष्ठा crypto_comp *);
	अगर (!tfms)
		जाओ error;

	क्रम_each_possible_cpu(cpu) अणु
		काष्ठा crypto_comp *tfm = crypto_alloc_comp(alg_name, 0,
							    CRYPTO_ALG_ASYNC);
		अगर (IS_ERR(tfm))
			जाओ error;
		*per_cpu_ptr(tfms, cpu) = tfm;
	पूर्ण

	वापस tfms;

error:
	ipcomp_मुक्त_tfms(tfms);
	वापस शून्य;
पूर्ण

अटल व्योम ipcomp_मुक्त_data(काष्ठा ipcomp_data *ipcd)
अणु
	अगर (ipcd->tfms)
		ipcomp_मुक्त_tfms(ipcd->tfms);
	ipcomp_मुक्त_scratches();
पूर्ण

व्योम ipcomp_destroy(काष्ठा xfrm_state *x)
अणु
	काष्ठा ipcomp_data *ipcd = x->data;
	अगर (!ipcd)
		वापस;
	xfrm_state_delete_tunnel(x);
	mutex_lock(&ipcomp_resource_mutex);
	ipcomp_मुक्त_data(ipcd);
	mutex_unlock(&ipcomp_resource_mutex);
	kमुक्त(ipcd);
पूर्ण
EXPORT_SYMBOL_GPL(ipcomp_destroy);

पूर्णांक ipcomp_init_state(काष्ठा xfrm_state *x)
अणु
	पूर्णांक err;
	काष्ठा ipcomp_data *ipcd;
	काष्ठा xfrm_algo_desc *calg_desc;

	err = -EINVAL;
	अगर (!x->calg)
		जाओ out;

	अगर (x->encap)
		जाओ out;

	err = -ENOMEM;
	ipcd = kzalloc(माप(*ipcd), GFP_KERNEL);
	अगर (!ipcd)
		जाओ out;

	mutex_lock(&ipcomp_resource_mutex);
	अगर (!ipcomp_alloc_scratches())
		जाओ error;

	ipcd->tfms = ipcomp_alloc_tfms(x->calg->alg_name);
	अगर (!ipcd->tfms)
		जाओ error;
	mutex_unlock(&ipcomp_resource_mutex);

	calg_desc = xfrm_calg_get_byname(x->calg->alg_name, 0);
	BUG_ON(!calg_desc);
	ipcd->threshold = calg_desc->uinfo.comp.threshold;
	x->data = ipcd;
	err = 0;
out:
	वापस err;

error:
	ipcomp_मुक्त_data(ipcd);
	mutex_unlock(&ipcomp_resource_mutex);
	kमुक्त(ipcd);
	जाओ out;
पूर्ण
EXPORT_SYMBOL_GPL(ipcomp_init_state);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("IP Payload Compression Protocol (IPComp) - RFC3173");
MODULE_AUTHOR("James Morris <jmorris@intercode.com.au>");
