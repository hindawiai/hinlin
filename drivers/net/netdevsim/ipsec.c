<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 2018 Oracle and/or its affiliates. All rights reserved. */

#समावेश <crypto/aead.h>
#समावेश <linux/debugfs.h>
#समावेश <net/xfrm.h>

#समावेश "netdevsim.h"

#घोषणा NSIM_IPSEC_AUTH_BITS	128

अटल sमाप_प्रकार nsim_dbg_netdev_ops_पढ़ो(काष्ठा file *filp,
					अक्षर __user *buffer,
					माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा netdevsim *ns = filp->निजी_data;
	काष्ठा nsim_ipsec *ipsec = &ns->ipsec;
	माप_प्रकार bufsize;
	अक्षर *buf, *p;
	पूर्णांक len;
	पूर्णांक i;

	/* the buffer needed is
	 * (num SAs * 3 lines each * ~60 bytes per line) + one more line
	 */
	bufsize = (ipsec->count * 4 * 60) + 60;
	buf = kzalloc(bufsize, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	p = buf;
	p += scnम_लिखो(p, bufsize - (p - buf),
		       "SA count=%u tx=%u\n",
		       ipsec->count, ipsec->tx);

	क्रम (i = 0; i < NSIM_IPSEC_MAX_SA_COUNT; i++) अणु
		काष्ठा nsim_sa *sap = &ipsec->sa[i];

		अगर (!sap->used)
			जारी;

		p += scnम_लिखो(p, bufsize - (p - buf),
			       "sa[%i] %cx ipaddr=0x%08x %08x %08x %08x\n",
			       i, (sap->rx ? 'r' : 't'), sap->ipaddr[0],
			       sap->ipaddr[1], sap->ipaddr[2], sap->ipaddr[3]);
		p += scnम_लिखो(p, bufsize - (p - buf),
			       "sa[%i]    spi=0x%08x proto=0x%x salt=0x%08x crypt=%d\n",
			       i, be32_to_cpu(sap->xs->id.spi),
			       sap->xs->id.proto, sap->salt, sap->crypt);
		p += scnम_लिखो(p, bufsize - (p - buf),
			       "sa[%i]    key=0x%08x %08x %08x %08x\n",
			       i, sap->key[0], sap->key[1],
			       sap->key[2], sap->key[3]);
	पूर्ण

	len = simple_पढ़ो_from_buffer(buffer, count, ppos, buf, p - buf);

	kमुक्त(buf);
	वापस len;
पूर्ण

अटल स्थिर काष्ठा file_operations ipsec_dbg_fops = अणु
	.owner = THIS_MODULE,
	.खोलो = simple_खोलो,
	.पढ़ो = nsim_dbg_netdev_ops_पढ़ो,
पूर्ण;

अटल पूर्णांक nsim_ipsec_find_empty_idx(काष्ठा nsim_ipsec *ipsec)
अणु
	u32 i;

	अगर (ipsec->count == NSIM_IPSEC_MAX_SA_COUNT)
		वापस -ENOSPC;

	/* search sa table */
	क्रम (i = 0; i < NSIM_IPSEC_MAX_SA_COUNT; i++) अणु
		अगर (!ipsec->sa[i].used)
			वापस i;
	पूर्ण

	वापस -ENOSPC;
पूर्ण

अटल पूर्णांक nsim_ipsec_parse_proto_keys(काष्ठा xfrm_state *xs,
				       u32 *mykey, u32 *mysalt)
अणु
	स्थिर अक्षर aes_gcm_name[] = "rfc4106(gcm(aes))";
	काष्ठा net_device *dev = xs->xso.dev;
	अचिन्हित अक्षर *key_data;
	अक्षर *alg_name = शून्य;
	पूर्णांक key_len;

	अगर (!xs->aead) अणु
		netdev_err(dev, "Unsupported IPsec algorithm\n");
		वापस -EINVAL;
	पूर्ण

	अगर (xs->aead->alg_icv_len != NSIM_IPSEC_AUTH_BITS) अणु
		netdev_err(dev, "IPsec offload requires %d bit authentication\n",
			   NSIM_IPSEC_AUTH_BITS);
		वापस -EINVAL;
	पूर्ण

	key_data = &xs->aead->alg_key[0];
	key_len = xs->aead->alg_key_len;
	alg_name = xs->aead->alg_name;

	अगर (म_भेद(alg_name, aes_gcm_name)) अणु
		netdev_err(dev, "Unsupported IPsec algorithm - please use %s\n",
			   aes_gcm_name);
		वापस -EINVAL;
	पूर्ण

	/* 160 accounts क्रम 16 byte key and 4 byte salt */
	अगर (key_len > NSIM_IPSEC_AUTH_BITS) अणु
		*mysalt = ((u32 *)key_data)[4];
	पूर्ण अन्यथा अगर (key_len == NSIM_IPSEC_AUTH_BITS) अणु
		*mysalt = 0;
	पूर्ण अन्यथा अणु
		netdev_err(dev, "IPsec hw offload only supports 128 bit keys with optional 32 bit salt\n");
		वापस -EINVAL;
	पूर्ण
	स_नकल(mykey, key_data, 16);

	वापस 0;
पूर्ण

अटल पूर्णांक nsim_ipsec_add_sa(काष्ठा xfrm_state *xs)
अणु
	काष्ठा nsim_ipsec *ipsec;
	काष्ठा net_device *dev;
	काष्ठा netdevsim *ns;
	काष्ठा nsim_sa sa;
	u16 sa_idx;
	पूर्णांक ret;

	dev = xs->xso.dev;
	ns = netdev_priv(dev);
	ipsec = &ns->ipsec;

	अगर (xs->id.proto != IPPROTO_ESP && xs->id.proto != IPPROTO_AH) अणु
		netdev_err(dev, "Unsupported protocol 0x%04x for ipsec offload\n",
			   xs->id.proto);
		वापस -EINVAL;
	पूर्ण

	अगर (xs->calg) अणु
		netdev_err(dev, "Compression offload not supported\n");
		वापस -EINVAL;
	पूर्ण

	/* find the first unused index */
	ret = nsim_ipsec_find_empty_idx(ipsec);
	अगर (ret < 0) अणु
		netdev_err(dev, "No space for SA in Rx table!\n");
		वापस ret;
	पूर्ण
	sa_idx = (u16)ret;

	स_रखो(&sa, 0, माप(sa));
	sa.used = true;
	sa.xs = xs;

	अगर (sa.xs->id.proto & IPPROTO_ESP)
		sa.crypt = xs->ealg || xs->aead;

	/* get the key and salt */
	ret = nsim_ipsec_parse_proto_keys(xs, sa.key, &sa.salt);
	अगर (ret) अणु
		netdev_err(dev, "Failed to get key data for SA table\n");
		वापस ret;
	पूर्ण

	अगर (xs->xso.flags & XFRM_OFFLOAD_INBOUND) अणु
		sa.rx = true;

		अगर (xs->props.family == AF_INET6)
			स_नकल(sa.ipaddr, &xs->id.daddr.a6, 16);
		अन्यथा
			स_नकल(&sa.ipaddr[3], &xs->id.daddr.a4, 4);
	पूर्ण

	/* the preparations worked, so save the info */
	स_नकल(&ipsec->sa[sa_idx], &sa, माप(sa));

	/* the XFRM stack करोesn't like offload_handle == 0,
	 * so add a bitflag in हाल our array index is 0
	 */
	xs->xso.offload_handle = sa_idx | NSIM_IPSEC_VALID;
	ipsec->count++;

	वापस 0;
पूर्ण

अटल व्योम nsim_ipsec_del_sa(काष्ठा xfrm_state *xs)
अणु
	काष्ठा netdevsim *ns = netdev_priv(xs->xso.dev);
	काष्ठा nsim_ipsec *ipsec = &ns->ipsec;
	u16 sa_idx;

	sa_idx = xs->xso.offload_handle & ~NSIM_IPSEC_VALID;
	अगर (!ipsec->sa[sa_idx].used) अणु
		netdev_err(ns->netdev, "Invalid SA for delete sa_idx=%d\n",
			   sa_idx);
		वापस;
	पूर्ण

	स_रखो(&ipsec->sa[sa_idx], 0, माप(काष्ठा nsim_sa));
	ipsec->count--;
पूर्ण

अटल bool nsim_ipsec_offload_ok(काष्ठा sk_buff *skb, काष्ठा xfrm_state *xs)
अणु
	काष्ठा netdevsim *ns = netdev_priv(xs->xso.dev);
	काष्ठा nsim_ipsec *ipsec = &ns->ipsec;

	ipsec->ok++;

	वापस true;
पूर्ण

अटल स्थिर काष्ठा xfrmdev_ops nsim_xfrmdev_ops = अणु
	.xकरो_dev_state_add	= nsim_ipsec_add_sa,
	.xकरो_dev_state_delete	= nsim_ipsec_del_sa,
	.xकरो_dev_offload_ok	= nsim_ipsec_offload_ok,
पूर्ण;

bool nsim_ipsec_tx(काष्ठा netdevsim *ns, काष्ठा sk_buff *skb)
अणु
	काष्ठा sec_path *sp = skb_sec_path(skb);
	काष्ठा nsim_ipsec *ipsec = &ns->ipsec;
	काष्ठा xfrm_state *xs;
	काष्ठा nsim_sa *tsa;
	u32 sa_idx;

	/* करो we even need to check this packet? */
	अगर (!sp)
		वापस true;

	अगर (unlikely(!sp->len)) अणु
		netdev_err(ns->netdev, "no xfrm state len = %d\n",
			   sp->len);
		वापस false;
	पूर्ण

	xs = xfrm_input_state(skb);
	अगर (unlikely(!xs)) अणु
		netdev_err(ns->netdev, "no xfrm_input_state() xs = %p\n", xs);
		वापस false;
	पूर्ण

	sa_idx = xs->xso.offload_handle & ~NSIM_IPSEC_VALID;
	अगर (unlikely(sa_idx >= NSIM_IPSEC_MAX_SA_COUNT)) अणु
		netdev_err(ns->netdev, "bad sa_idx=%d max=%d\n",
			   sa_idx, NSIM_IPSEC_MAX_SA_COUNT);
		वापस false;
	पूर्ण

	tsa = &ipsec->sa[sa_idx];
	अगर (unlikely(!tsa->used)) अणु
		netdev_err(ns->netdev, "unused sa_idx=%d\n", sa_idx);
		वापस false;
	पूर्ण

	अगर (xs->id.proto != IPPROTO_ESP && xs->id.proto != IPPROTO_AH) अणु
		netdev_err(ns->netdev, "unexpected proto=%d\n", xs->id.proto);
		वापस false;
	पूर्ण

	ipsec->tx++;

	वापस true;
पूर्ण

व्योम nsim_ipsec_init(काष्ठा netdevsim *ns)
अणु
	ns->netdev->xfrmdev_ops = &nsim_xfrmdev_ops;

#घोषणा NSIM_ESP_FEATURES	(NETIF_F_HW_ESP | \
				 NETIF_F_HW_ESP_TX_CSUM | \
				 NETIF_F_GSO_ESP)

	ns->netdev->features |= NSIM_ESP_FEATURES;
	ns->netdev->hw_enc_features |= NSIM_ESP_FEATURES;

	ns->ipsec.pfile = debugfs_create_file("ipsec", 0400,
					      ns->nsim_dev_port->ddir, ns,
					      &ipsec_dbg_fops);
पूर्ण

व्योम nsim_ipsec_tearकरोwn(काष्ठा netdevsim *ns)
अणु
	काष्ठा nsim_ipsec *ipsec = &ns->ipsec;

	अगर (ipsec->count)
		netdev_err(ns->netdev, "tearing down IPsec offload with %d SAs left\n",
			   ipsec->count);
	debugfs_हटाओ_recursive(ipsec->pfile);
पूर्ण
