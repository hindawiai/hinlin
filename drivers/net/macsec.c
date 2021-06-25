<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * drivers/net/macsec.c - MACsec device
 *
 * Copyright (c) 2015 Sabrina Dubroca <sd@queasysnail.net>
 */

#समावेश <linux/types.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/socket.h>
#समावेश <linux/module.h>
#समावेश <crypto/aead.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/refcount.h>
#समावेश <net/genetlink.h>
#समावेश <net/sock.h>
#समावेश <net/gro_cells.h>
#समावेश <net/macsec.h>
#समावेश <linux/phy.h>
#समावेश <linux/byteorder/generic.h>
#समावेश <linux/अगर_arp.h>

#समावेश <uapi/linux/अगर_macsec.h>

#घोषणा MACSEC_SCI_LEN 8

/* SecTAG length = macsec_eth_header without the optional SCI */
#घोषणा MACSEC_TAG_LEN 6

काष्ठा macsec_eth_header अणु
	काष्ठा ethhdr eth;
	/* SecTAG */
	u8  tci_an;
#अगर defined(__LITTLE_ENDIAN_BITFIELD)
	u8  लघु_length:6,
		  unused:2;
#या_अगर defined(__BIG_ENDIAN_BITFIELD)
	u8        unused:2,
	    लघु_length:6;
#अन्यथा
#त्रुटि	"Please fix <asm/byteorder.h>"
#पूर्ण_अगर
	__be32 packet_number;
	u8 secure_channel_id[8]; /* optional */
पूर्ण __packed;

#घोषणा MACSEC_TCI_VERSION 0x80
#घोषणा MACSEC_TCI_ES      0x40 /* end station */
#घोषणा MACSEC_TCI_SC      0x20 /* SCI present */
#घोषणा MACSEC_TCI_SCB     0x10 /* epon */
#घोषणा MACSEC_TCI_E       0x08 /* encryption */
#घोषणा MACSEC_TCI_C       0x04 /* changed text */
#घोषणा MACSEC_AN_MASK     0x03 /* association number */
#घोषणा MACSEC_TCI_CONFID  (MACSEC_TCI_E | MACSEC_TCI_C)

/* minimum secure data length deemed "not short", see IEEE 802.1AE-2006 9.7 */
#घोषणा MIN_NON_SHORT_LEN 48

#घोषणा GCM_AES_IV_LEN 12
#घोषणा DEFAULT_ICV_LEN 16

#घोषणा क्रम_each_rxsc(secy, sc)				\
	क्रम (sc = rcu_dereference_bh(secy->rx_sc);	\
	     sc;					\
	     sc = rcu_dereference_bh(sc->next))
#घोषणा क्रम_each_rxsc_rtnl(secy, sc)			\
	क्रम (sc = rtnl_dereference(secy->rx_sc);	\
	     sc;					\
	     sc = rtnl_dereference(sc->next))

#घोषणा pn_same_half(pn1, pn2) (!(((pn1) >> 31) ^ ((pn2) >> 31)))

काष्ठा gcm_iv_xpn अणु
	जोड़ अणु
		u8 लघु_secure_channel_id[4];
		ssci_t ssci;
	पूर्ण;
	__be64 pn;
पूर्ण __packed;

काष्ठा gcm_iv अणु
	जोड़ अणु
		u8 secure_channel_id[8];
		sci_t sci;
	पूर्ण;
	__be32 pn;
पूर्ण;

#घोषणा MACSEC_VALIDATE_DEFAULT MACSEC_VALIDATE_STRICT

काष्ठा pcpu_secy_stats अणु
	काष्ठा macsec_dev_stats stats;
	काष्ठा u64_stats_sync syncp;
पूर्ण;

/**
 * काष्ठा macsec_dev - निजी data
 * @secy: SecY config
 * @real_dev: poपूर्णांकer to underlying netdevice
 * @stats: MACsec device stats
 * @secys: linked list of SecY's on the underlying device
 * @gro_cells: poपूर्णांकer to the Generic Receive Offload cell
 * @offload: status of offloading on the MACsec device
 */
काष्ठा macsec_dev अणु
	काष्ठा macsec_secy secy;
	काष्ठा net_device *real_dev;
	काष्ठा pcpu_secy_stats __percpu *stats;
	काष्ठा list_head secys;
	काष्ठा gro_cells gro_cells;
	क्रमागत macsec_offload offload;
पूर्ण;

/**
 * काष्ठा macsec_rxh_data - rx_handler निजी argument
 * @secys: linked list of SecY's on this underlying device
 */
काष्ठा macsec_rxh_data अणु
	काष्ठा list_head secys;
पूर्ण;

अटल काष्ठा macsec_dev *macsec_priv(स्थिर काष्ठा net_device *dev)
अणु
	वापस (काष्ठा macsec_dev *)netdev_priv(dev);
पूर्ण

अटल काष्ठा macsec_rxh_data *macsec_data_rcu(स्थिर काष्ठा net_device *dev)
अणु
	वापस rcu_dereference_bh(dev->rx_handler_data);
पूर्ण

अटल काष्ठा macsec_rxh_data *macsec_data_rtnl(स्थिर काष्ठा net_device *dev)
अणु
	वापस rtnl_dereference(dev->rx_handler_data);
पूर्ण

काष्ठा macsec_cb अणु
	काष्ठा aead_request *req;
	जोड़ अणु
		काष्ठा macsec_tx_sa *tx_sa;
		काष्ठा macsec_rx_sa *rx_sa;
	पूर्ण;
	u8 assoc_num;
	bool valid;
	bool has_sci;
पूर्ण;

अटल काष्ठा macsec_rx_sa *macsec_rxsa_get(काष्ठा macsec_rx_sa __rcu *ptr)
अणु
	काष्ठा macsec_rx_sa *sa = rcu_dereference_bh(ptr);

	अगर (!sa || !sa->active)
		वापस शून्य;

	अगर (!refcount_inc_not_zero(&sa->refcnt))
		वापस शून्य;

	वापस sa;
पूर्ण

अटल व्योम मुक्त_rx_sc_rcu(काष्ठा rcu_head *head)
अणु
	काष्ठा macsec_rx_sc *rx_sc = container_of(head, काष्ठा macsec_rx_sc, rcu_head);

	मुक्त_percpu(rx_sc->stats);
	kमुक्त(rx_sc);
पूर्ण

अटल काष्ठा macsec_rx_sc *macsec_rxsc_get(काष्ठा macsec_rx_sc *sc)
अणु
	वापस refcount_inc_not_zero(&sc->refcnt) ? sc : शून्य;
पूर्ण

अटल व्योम macsec_rxsc_put(काष्ठा macsec_rx_sc *sc)
अणु
	अगर (refcount_dec_and_test(&sc->refcnt))
		call_rcu(&sc->rcu_head, मुक्त_rx_sc_rcu);
पूर्ण

अटल व्योम मुक्त_rxsa(काष्ठा rcu_head *head)
अणु
	काष्ठा macsec_rx_sa *sa = container_of(head, काष्ठा macsec_rx_sa, rcu);

	crypto_मुक्त_aead(sa->key.tfm);
	मुक्त_percpu(sa->stats);
	kमुक्त(sa);
पूर्ण

अटल व्योम macsec_rxsa_put(काष्ठा macsec_rx_sa *sa)
अणु
	अगर (refcount_dec_and_test(&sa->refcnt))
		call_rcu(&sa->rcu, मुक्त_rxsa);
पूर्ण

अटल काष्ठा macsec_tx_sa *macsec_txsa_get(काष्ठा macsec_tx_sa __rcu *ptr)
अणु
	काष्ठा macsec_tx_sa *sa = rcu_dereference_bh(ptr);

	अगर (!sa || !sa->active)
		वापस शून्य;

	अगर (!refcount_inc_not_zero(&sa->refcnt))
		वापस शून्य;

	वापस sa;
पूर्ण

अटल व्योम मुक्त_txsa(काष्ठा rcu_head *head)
अणु
	काष्ठा macsec_tx_sa *sa = container_of(head, काष्ठा macsec_tx_sa, rcu);

	crypto_मुक्त_aead(sa->key.tfm);
	मुक्त_percpu(sa->stats);
	kमुक्त(sa);
पूर्ण

अटल व्योम macsec_txsa_put(काष्ठा macsec_tx_sa *sa)
अणु
	अगर (refcount_dec_and_test(&sa->refcnt))
		call_rcu(&sa->rcu, मुक्त_txsa);
पूर्ण

अटल काष्ठा macsec_cb *macsec_skb_cb(काष्ठा sk_buff *skb)
अणु
	BUILD_BUG_ON(माप(काष्ठा macsec_cb) > माप(skb->cb));
	वापस (काष्ठा macsec_cb *)skb->cb;
पूर्ण

#घोषणा MACSEC_PORT_ES (htons(0x0001))
#घोषणा MACSEC_PORT_SCB (0x0000)
#घोषणा MACSEC_UNDEF_SCI ((__क्रमce sci_t)0xffffffffffffffffULL)
#घोषणा MACSEC_UNDEF_SSCI ((__क्रमce ssci_t)0xffffffff)

#घोषणा MACSEC_GCM_AES_128_SAK_LEN 16
#घोषणा MACSEC_GCM_AES_256_SAK_LEN 32

#घोषणा DEFAULT_SAK_LEN MACSEC_GCM_AES_128_SAK_LEN
#घोषणा DEFAULT_XPN false
#घोषणा DEFAULT_SEND_SCI true
#घोषणा DEFAULT_ENCRYPT false
#घोषणा DEFAULT_ENCODING_SA 0

अटल bool send_sci(स्थिर काष्ठा macsec_secy *secy)
अणु
	स्थिर काष्ठा macsec_tx_sc *tx_sc = &secy->tx_sc;

	वापस tx_sc->send_sci ||
		(secy->n_rx_sc > 1 && !tx_sc->end_station && !tx_sc->scb);
पूर्ण

अटल sci_t make_sci(u8 *addr, __be16 port)
अणु
	sci_t sci;

	स_नकल(&sci, addr, ETH_ALEN);
	स_नकल(((अक्षर *)&sci) + ETH_ALEN, &port, माप(port));

	वापस sci;
पूर्ण

अटल sci_t macsec_frame_sci(काष्ठा macsec_eth_header *hdr, bool sci_present)
अणु
	sci_t sci;

	अगर (sci_present)
		स_नकल(&sci, hdr->secure_channel_id,
		       माप(hdr->secure_channel_id));
	अन्यथा
		sci = make_sci(hdr->eth.h_source, MACSEC_PORT_ES);

	वापस sci;
पूर्ण

अटल अचिन्हित पूर्णांक macsec_sectag_len(bool sci_present)
अणु
	वापस MACSEC_TAG_LEN + (sci_present ? MACSEC_SCI_LEN : 0);
पूर्ण

अटल अचिन्हित पूर्णांक macsec_hdr_len(bool sci_present)
अणु
	वापस macsec_sectag_len(sci_present) + ETH_HLEN;
पूर्ण

अटल अचिन्हित पूर्णांक macsec_extra_len(bool sci_present)
अणु
	वापस macsec_sectag_len(sci_present) + माप(__be16);
पूर्ण

/* Fill SecTAG according to IEEE 802.1AE-2006 10.5.3 */
अटल व्योम macsec_fill_sectag(काष्ठा macsec_eth_header *h,
			       स्थिर काष्ठा macsec_secy *secy, u32 pn,
			       bool sci_present)
अणु
	स्थिर काष्ठा macsec_tx_sc *tx_sc = &secy->tx_sc;

	स_रखो(&h->tci_an, 0, macsec_sectag_len(sci_present));
	h->eth.h_proto = htons(ETH_P_MACSEC);

	अगर (sci_present) अणु
		h->tci_an |= MACSEC_TCI_SC;
		स_नकल(&h->secure_channel_id, &secy->sci,
		       माप(h->secure_channel_id));
	पूर्ण अन्यथा अणु
		अगर (tx_sc->end_station)
			h->tci_an |= MACSEC_TCI_ES;
		अगर (tx_sc->scb)
			h->tci_an |= MACSEC_TCI_SCB;
	पूर्ण

	h->packet_number = htonl(pn);

	/* with GCM, C/E clear क्रम !encrypt, both set क्रम encrypt */
	अगर (tx_sc->encrypt)
		h->tci_an |= MACSEC_TCI_CONFID;
	अन्यथा अगर (secy->icv_len != DEFAULT_ICV_LEN)
		h->tci_an |= MACSEC_TCI_C;

	h->tci_an |= tx_sc->encoding_sa;
पूर्ण

अटल व्योम macsec_set_लघुlen(काष्ठा macsec_eth_header *h, माप_प्रकार data_len)
अणु
	अगर (data_len < MIN_NON_SHORT_LEN)
		h->लघु_length = data_len;
पूर्ण

/* Checks अगर a MACsec पूर्णांकerface is being offloaded to an hardware engine */
अटल bool macsec_is_offloaded(काष्ठा macsec_dev *macsec)
अणु
	अगर (macsec->offload == MACSEC_OFFLOAD_MAC ||
	    macsec->offload == MACSEC_OFFLOAD_PHY)
		वापस true;

	वापस false;
पूर्ण

/* Checks अगर underlying layers implement MACsec offloading functions. */
अटल bool macsec_check_offload(क्रमागत macsec_offload offload,
				 काष्ठा macsec_dev *macsec)
अणु
	अगर (!macsec || !macsec->real_dev)
		वापस false;

	अगर (offload == MACSEC_OFFLOAD_PHY)
		वापस macsec->real_dev->phydev &&
		       macsec->real_dev->phydev->macsec_ops;
	अन्यथा अगर (offload == MACSEC_OFFLOAD_MAC)
		वापस macsec->real_dev->features & NETIF_F_HW_MACSEC &&
		       macsec->real_dev->macsec_ops;

	वापस false;
पूर्ण

अटल स्थिर काष्ठा macsec_ops *__macsec_get_ops(क्रमागत macsec_offload offload,
						 काष्ठा macsec_dev *macsec,
						 काष्ठा macsec_context *ctx)
अणु
	अगर (ctx) अणु
		स_रखो(ctx, 0, माप(*ctx));
		ctx->offload = offload;

		अगर (offload == MACSEC_OFFLOAD_PHY)
			ctx->phydev = macsec->real_dev->phydev;
		अन्यथा अगर (offload == MACSEC_OFFLOAD_MAC)
			ctx->netdev = macsec->real_dev;
	पूर्ण

	अगर (offload == MACSEC_OFFLOAD_PHY)
		वापस macsec->real_dev->phydev->macsec_ops;
	अन्यथा
		वापस macsec->real_dev->macsec_ops;
पूर्ण

/* Returns a poपूर्णांकer to the MACsec ops काष्ठा अगर any and updates the MACsec
 * context device reference अगर provided.
 */
अटल स्थिर काष्ठा macsec_ops *macsec_get_ops(काष्ठा macsec_dev *macsec,
					       काष्ठा macsec_context *ctx)
अणु
	अगर (!macsec_check_offload(macsec->offload, macsec))
		वापस शून्य;

	वापस __macsec_get_ops(macsec->offload, macsec, ctx);
पूर्ण

/* validate MACsec packet according to IEEE 802.1AE-2018 9.12 */
अटल bool macsec_validate_skb(काष्ठा sk_buff *skb, u16 icv_len, bool xpn)
अणु
	काष्ठा macsec_eth_header *h = (काष्ठा macsec_eth_header *)skb->data;
	पूर्णांक len = skb->len - 2 * ETH_ALEN;
	पूर्णांक extra_len = macsec_extra_len(!!(h->tci_an & MACSEC_TCI_SC)) + icv_len;

	/* a) It comprises at least 17 octets */
	अगर (skb->len <= 16)
		वापस false;

	/* b) MACsec EtherType: alपढ़ोy checked */

	/* c) V bit is clear */
	अगर (h->tci_an & MACSEC_TCI_VERSION)
		वापस false;

	/* d) ES or SCB => !SC */
	अगर ((h->tci_an & MACSEC_TCI_ES || h->tci_an & MACSEC_TCI_SCB) &&
	    (h->tci_an & MACSEC_TCI_SC))
		वापस false;

	/* e) Bits 7 and 8 of octet 4 of the SecTAG are clear */
	अगर (h->unused)
		वापस false;

	/* rx.pn != 0 अगर not XPN (figure 10-5 with 802.11AEbw-2013 amendment) */
	अगर (!h->packet_number && !xpn)
		वापस false;

	/* length check, f) g) h) i) */
	अगर (h->लघु_length)
		वापस len == extra_len + h->लघु_length;
	वापस len >= extra_len + MIN_NON_SHORT_LEN;
पूर्ण

#घोषणा MACSEC_NEEDED_HEADROOM (macsec_extra_len(true))
#घोषणा MACSEC_NEEDED_TAILROOM MACSEC_STD_ICV_LEN

अटल व्योम macsec_fill_iv_xpn(अचिन्हित अक्षर *iv, ssci_t ssci, u64 pn,
			       salt_t salt)
अणु
	काष्ठा gcm_iv_xpn *gcm_iv = (काष्ठा gcm_iv_xpn *)iv;

	gcm_iv->ssci = ssci ^ salt.ssci;
	gcm_iv->pn = cpu_to_be64(pn) ^ salt.pn;
पूर्ण

अटल व्योम macsec_fill_iv(अचिन्हित अक्षर *iv, sci_t sci, u32 pn)
अणु
	काष्ठा gcm_iv *gcm_iv = (काष्ठा gcm_iv *)iv;

	gcm_iv->sci = sci;
	gcm_iv->pn = htonl(pn);
पूर्ण

अटल काष्ठा macsec_eth_header *macsec_ethhdr(काष्ठा sk_buff *skb)
अणु
	वापस (काष्ठा macsec_eth_header *)skb_mac_header(skb);
पूर्ण

अटल sci_t dev_to_sci(काष्ठा net_device *dev, __be16 port)
अणु
	वापस make_sci(dev->dev_addr, port);
पूर्ण

अटल व्योम __macsec_pn_wrapped(काष्ठा macsec_secy *secy,
				काष्ठा macsec_tx_sa *tx_sa)
अणु
	pr_debug("PN wrapped, transitioning to !oper\n");
	tx_sa->active = false;
	अगर (secy->protect_frames)
		secy->operational = false;
पूर्ण

व्योम macsec_pn_wrapped(काष्ठा macsec_secy *secy, काष्ठा macsec_tx_sa *tx_sa)
अणु
	spin_lock_bh(&tx_sa->lock);
	__macsec_pn_wrapped(secy, tx_sa);
	spin_unlock_bh(&tx_sa->lock);
पूर्ण
EXPORT_SYMBOL_GPL(macsec_pn_wrapped);

अटल pn_t tx_sa_update_pn(काष्ठा macsec_tx_sa *tx_sa,
			    काष्ठा macsec_secy *secy)
अणु
	pn_t pn;

	spin_lock_bh(&tx_sa->lock);

	pn = tx_sa->next_pn_halves;
	अगर (secy->xpn)
		tx_sa->next_pn++;
	अन्यथा
		tx_sa->next_pn_halves.lower++;

	अगर (tx_sa->next_pn == 0)
		__macsec_pn_wrapped(secy, tx_sa);
	spin_unlock_bh(&tx_sa->lock);

	वापस pn;
पूर्ण

अटल व्योम macsec_encrypt_finish(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा macsec_dev *macsec = netdev_priv(dev);

	skb->dev = macsec->real_dev;
	skb_reset_mac_header(skb);
	skb->protocol = eth_hdr(skb)->h_proto;
पूर्ण

अटल व्योम macsec_count_tx(काष्ठा sk_buff *skb, काष्ठा macsec_tx_sc *tx_sc,
			    काष्ठा macsec_tx_sa *tx_sa)
अणु
	काष्ठा pcpu_tx_sc_stats *txsc_stats = this_cpu_ptr(tx_sc->stats);

	u64_stats_update_begin(&txsc_stats->syncp);
	अगर (tx_sc->encrypt) अणु
		txsc_stats->stats.OutOctetsEncrypted += skb->len;
		txsc_stats->stats.OutPktsEncrypted++;
		this_cpu_inc(tx_sa->stats->OutPktsEncrypted);
	पूर्ण अन्यथा अणु
		txsc_stats->stats.OutOctetsProtected += skb->len;
		txsc_stats->stats.OutPktsProtected++;
		this_cpu_inc(tx_sa->stats->OutPktsProtected);
	पूर्ण
	u64_stats_update_end(&txsc_stats->syncp);
पूर्ण

अटल व्योम count_tx(काष्ठा net_device *dev, पूर्णांक ret, पूर्णांक len)
अणु
	अगर (likely(ret == NET_XMIT_SUCCESS || ret == NET_XMIT_CN)) अणु
		काष्ठा pcpu_sw_netstats *stats = this_cpu_ptr(dev->tstats);

		u64_stats_update_begin(&stats->syncp);
		stats->tx_packets++;
		stats->tx_bytes += len;
		u64_stats_update_end(&stats->syncp);
	पूर्ण
पूर्ण

अटल व्योम macsec_encrypt_करोne(काष्ठा crypto_async_request *base, पूर्णांक err)
अणु
	काष्ठा sk_buff *skb = base->data;
	काष्ठा net_device *dev = skb->dev;
	काष्ठा macsec_dev *macsec = macsec_priv(dev);
	काष्ठा macsec_tx_sa *sa = macsec_skb_cb(skb)->tx_sa;
	पूर्णांक len, ret;

	aead_request_मुक्त(macsec_skb_cb(skb)->req);

	rcu_पढ़ो_lock_bh();
	macsec_encrypt_finish(skb, dev);
	macsec_count_tx(skb, &macsec->secy.tx_sc, macsec_skb_cb(skb)->tx_sa);
	len = skb->len;
	ret = dev_queue_xmit(skb);
	count_tx(dev, ret, len);
	rcu_पढ़ो_unlock_bh();

	macsec_txsa_put(sa);
	dev_put(dev);
पूर्ण

अटल काष्ठा aead_request *macsec_alloc_req(काष्ठा crypto_aead *tfm,
					     अचिन्हित अक्षर **iv,
					     काष्ठा scatterlist **sg,
					     पूर्णांक num_frags)
अणु
	माप_प्रकार size, iv_offset, sg_offset;
	काष्ठा aead_request *req;
	व्योम *पंचांगp;

	size = माप(काष्ठा aead_request) + crypto_aead_reqsize(tfm);
	iv_offset = size;
	size += GCM_AES_IV_LEN;

	size = ALIGN(size, __alignof__(काष्ठा scatterlist));
	sg_offset = size;
	size += माप(काष्ठा scatterlist) * num_frags;

	पंचांगp = kदो_स्मृति(size, GFP_ATOMIC);
	अगर (!पंचांगp)
		वापस शून्य;

	*iv = (अचिन्हित अक्षर *)(पंचांगp + iv_offset);
	*sg = (काष्ठा scatterlist *)(पंचांगp + sg_offset);
	req = पंचांगp;

	aead_request_set_tfm(req, tfm);

	वापस req;
पूर्ण

अटल काष्ठा sk_buff *macsec_encrypt(काष्ठा sk_buff *skb,
				      काष्ठा net_device *dev)
अणु
	पूर्णांक ret;
	काष्ठा scatterlist *sg;
	काष्ठा sk_buff *trailer;
	अचिन्हित अक्षर *iv;
	काष्ठा ethhdr *eth;
	काष्ठा macsec_eth_header *hh;
	माप_प्रकार unरक्षित_len;
	काष्ठा aead_request *req;
	काष्ठा macsec_secy *secy;
	काष्ठा macsec_tx_sc *tx_sc;
	काष्ठा macsec_tx_sa *tx_sa;
	काष्ठा macsec_dev *macsec = macsec_priv(dev);
	bool sci_present;
	pn_t pn;

	secy = &macsec->secy;
	tx_sc = &secy->tx_sc;

	/* 10.5.1 TX SA assignment */
	tx_sa = macsec_txsa_get(tx_sc->sa[tx_sc->encoding_sa]);
	अगर (!tx_sa) अणु
		secy->operational = false;
		kमुक्त_skb(skb);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	अगर (unlikely(skb_headroom(skb) < MACSEC_NEEDED_HEADROOM ||
		     skb_tailroom(skb) < MACSEC_NEEDED_TAILROOM)) अणु
		काष्ठा sk_buff *nskb = skb_copy_expand(skb,
						       MACSEC_NEEDED_HEADROOM,
						       MACSEC_NEEDED_TAILROOM,
						       GFP_ATOMIC);
		अगर (likely(nskb)) अणु
			consume_skb(skb);
			skb = nskb;
		पूर्ण अन्यथा अणु
			macsec_txsa_put(tx_sa);
			kमुक्त_skb(skb);
			वापस ERR_PTR(-ENOMEM);
		पूर्ण
	पूर्ण अन्यथा अणु
		skb = skb_unshare(skb, GFP_ATOMIC);
		अगर (!skb) अणु
			macsec_txsa_put(tx_sa);
			वापस ERR_PTR(-ENOMEM);
		पूर्ण
	पूर्ण

	unरक्षित_len = skb->len;
	eth = eth_hdr(skb);
	sci_present = send_sci(secy);
	hh = skb_push(skb, macsec_extra_len(sci_present));
	स_हटाओ(hh, eth, 2 * ETH_ALEN);

	pn = tx_sa_update_pn(tx_sa, secy);
	अगर (pn.full64 == 0) अणु
		macsec_txsa_put(tx_sa);
		kमुक्त_skb(skb);
		वापस ERR_PTR(-ENOLINK);
	पूर्ण
	macsec_fill_sectag(hh, secy, pn.lower, sci_present);
	macsec_set_लघुlen(hh, unरक्षित_len - 2 * ETH_ALEN);

	skb_put(skb, secy->icv_len);

	अगर (skb->len - ETH_HLEN > macsec_priv(dev)->real_dev->mtu) अणु
		काष्ठा pcpu_secy_stats *secy_stats = this_cpu_ptr(macsec->stats);

		u64_stats_update_begin(&secy_stats->syncp);
		secy_stats->stats.OutPktsTooLong++;
		u64_stats_update_end(&secy_stats->syncp);

		macsec_txsa_put(tx_sa);
		kमुक्त_skb(skb);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	ret = skb_cow_data(skb, 0, &trailer);
	अगर (unlikely(ret < 0)) अणु
		macsec_txsa_put(tx_sa);
		kमुक्त_skb(skb);
		वापस ERR_PTR(ret);
	पूर्ण

	req = macsec_alloc_req(tx_sa->key.tfm, &iv, &sg, ret);
	अगर (!req) अणु
		macsec_txsa_put(tx_sa);
		kमुक्त_skb(skb);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	अगर (secy->xpn)
		macsec_fill_iv_xpn(iv, tx_sa->ssci, pn.full64, tx_sa->key.salt);
	अन्यथा
		macsec_fill_iv(iv, secy->sci, pn.lower);

	sg_init_table(sg, ret);
	ret = skb_to_sgvec(skb, sg, 0, skb->len);
	अगर (unlikely(ret < 0)) अणु
		aead_request_मुक्त(req);
		macsec_txsa_put(tx_sa);
		kमुक्त_skb(skb);
		वापस ERR_PTR(ret);
	पूर्ण

	अगर (tx_sc->encrypt) अणु
		पूर्णांक len = skb->len - macsec_hdr_len(sci_present) -
			  secy->icv_len;
		aead_request_set_crypt(req, sg, sg, len, iv);
		aead_request_set_ad(req, macsec_hdr_len(sci_present));
	पूर्ण अन्यथा अणु
		aead_request_set_crypt(req, sg, sg, 0, iv);
		aead_request_set_ad(req, skb->len - secy->icv_len);
	पूर्ण

	macsec_skb_cb(skb)->req = req;
	macsec_skb_cb(skb)->tx_sa = tx_sa;
	aead_request_set_callback(req, 0, macsec_encrypt_करोne, skb);

	dev_hold(skb->dev);
	ret = crypto_aead_encrypt(req);
	अगर (ret == -EINPROGRESS) अणु
		वापस ERR_PTR(ret);
	पूर्ण अन्यथा अगर (ret != 0) अणु
		dev_put(skb->dev);
		kमुक्त_skb(skb);
		aead_request_मुक्त(req);
		macsec_txsa_put(tx_sa);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	dev_put(skb->dev);
	aead_request_मुक्त(req);
	macsec_txsa_put(tx_sa);

	वापस skb;
पूर्ण

अटल bool macsec_post_decrypt(काष्ठा sk_buff *skb, काष्ठा macsec_secy *secy, u32 pn)
अणु
	काष्ठा macsec_rx_sa *rx_sa = macsec_skb_cb(skb)->rx_sa;
	काष्ठा pcpu_rx_sc_stats *rxsc_stats = this_cpu_ptr(rx_sa->sc->stats);
	काष्ठा macsec_eth_header *hdr = macsec_ethhdr(skb);
	u32 lowest_pn = 0;

	spin_lock(&rx_sa->lock);
	अगर (rx_sa->next_pn_halves.lower >= secy->replay_winकरोw)
		lowest_pn = rx_sa->next_pn_halves.lower - secy->replay_winकरोw;

	/* Now perक्रमm replay protection check again
	 * (see IEEE 802.1AE-2006 figure 10-5)
	 */
	अगर (secy->replay_protect && pn < lowest_pn &&
	    (!secy->xpn || pn_same_half(pn, lowest_pn))) अणु
		spin_unlock(&rx_sa->lock);
		u64_stats_update_begin(&rxsc_stats->syncp);
		rxsc_stats->stats.InPktsLate++;
		u64_stats_update_end(&rxsc_stats->syncp);
		वापस false;
	पूर्ण

	अगर (secy->validate_frames != MACSEC_VALIDATE_DISABLED) अणु
		u64_stats_update_begin(&rxsc_stats->syncp);
		अगर (hdr->tci_an & MACSEC_TCI_E)
			rxsc_stats->stats.InOctetsDecrypted += skb->len;
		अन्यथा
			rxsc_stats->stats.InOctetsValidated += skb->len;
		u64_stats_update_end(&rxsc_stats->syncp);
	पूर्ण

	अगर (!macsec_skb_cb(skb)->valid) अणु
		spin_unlock(&rx_sa->lock);

		/* 10.6.5 */
		अगर (hdr->tci_an & MACSEC_TCI_C ||
		    secy->validate_frames == MACSEC_VALIDATE_STRICT) अणु
			u64_stats_update_begin(&rxsc_stats->syncp);
			rxsc_stats->stats.InPktsNotValid++;
			u64_stats_update_end(&rxsc_stats->syncp);
			वापस false;
		पूर्ण

		u64_stats_update_begin(&rxsc_stats->syncp);
		अगर (secy->validate_frames == MACSEC_VALIDATE_CHECK) अणु
			rxsc_stats->stats.InPktsInvalid++;
			this_cpu_inc(rx_sa->stats->InPktsInvalid);
		पूर्ण अन्यथा अगर (pn < lowest_pn) अणु
			rxsc_stats->stats.InPktsDelayed++;
		पूर्ण अन्यथा अणु
			rxsc_stats->stats.InPktsUnchecked++;
		पूर्ण
		u64_stats_update_end(&rxsc_stats->syncp);
	पूर्ण अन्यथा अणु
		u64_stats_update_begin(&rxsc_stats->syncp);
		अगर (pn < lowest_pn) अणु
			rxsc_stats->stats.InPktsDelayed++;
		पूर्ण अन्यथा अणु
			rxsc_stats->stats.InPktsOK++;
			this_cpu_inc(rx_sa->stats->InPktsOK);
		पूर्ण
		u64_stats_update_end(&rxsc_stats->syncp);

		// Instead of "pn >=" - to support pn overflow in xpn
		अगर (pn + 1 > rx_sa->next_pn_halves.lower) अणु
			rx_sa->next_pn_halves.lower = pn + 1;
		पूर्ण अन्यथा अगर (secy->xpn &&
			   !pn_same_half(pn, rx_sa->next_pn_halves.lower)) अणु
			rx_sa->next_pn_halves.upper++;
			rx_sa->next_pn_halves.lower = pn + 1;
		पूर्ण

		spin_unlock(&rx_sa->lock);
	पूर्ण

	वापस true;
पूर्ण

अटल व्योम macsec_reset_skb(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	skb->pkt_type = PACKET_HOST;
	skb->protocol = eth_type_trans(skb, dev);

	skb_reset_network_header(skb);
	अगर (!skb_transport_header_was_set(skb))
		skb_reset_transport_header(skb);
	skb_reset_mac_len(skb);
पूर्ण

अटल व्योम macsec_finalize_skb(काष्ठा sk_buff *skb, u8 icv_len, u8 hdr_len)
अणु
	skb->ip_summed = CHECKSUM_NONE;
	स_हटाओ(skb->data + hdr_len, skb->data, 2 * ETH_ALEN);
	skb_pull(skb, hdr_len);
	pskb_trim_unique(skb, skb->len - icv_len);
पूर्ण

अटल व्योम count_rx(काष्ठा net_device *dev, पूर्णांक len)
अणु
	काष्ठा pcpu_sw_netstats *stats = this_cpu_ptr(dev->tstats);

	u64_stats_update_begin(&stats->syncp);
	stats->rx_packets++;
	stats->rx_bytes += len;
	u64_stats_update_end(&stats->syncp);
पूर्ण

अटल व्योम macsec_decrypt_करोne(काष्ठा crypto_async_request *base, पूर्णांक err)
अणु
	काष्ठा sk_buff *skb = base->data;
	काष्ठा net_device *dev = skb->dev;
	काष्ठा macsec_dev *macsec = macsec_priv(dev);
	काष्ठा macsec_rx_sa *rx_sa = macsec_skb_cb(skb)->rx_sa;
	काष्ठा macsec_rx_sc *rx_sc = rx_sa->sc;
	पूर्णांक len;
	u32 pn;

	aead_request_मुक्त(macsec_skb_cb(skb)->req);

	अगर (!err)
		macsec_skb_cb(skb)->valid = true;

	rcu_पढ़ो_lock_bh();
	pn = ntohl(macsec_ethhdr(skb)->packet_number);
	अगर (!macsec_post_decrypt(skb, &macsec->secy, pn)) अणु
		rcu_पढ़ो_unlock_bh();
		kमुक्त_skb(skb);
		जाओ out;
	पूर्ण

	macsec_finalize_skb(skb, macsec->secy.icv_len,
			    macsec_extra_len(macsec_skb_cb(skb)->has_sci));
	macsec_reset_skb(skb, macsec->secy.netdev);

	len = skb->len;
	अगर (gro_cells_receive(&macsec->gro_cells, skb) == NET_RX_SUCCESS)
		count_rx(dev, len);

	rcu_पढ़ो_unlock_bh();

out:
	macsec_rxsa_put(rx_sa);
	macsec_rxsc_put(rx_sc);
	dev_put(dev);
पूर्ण

अटल काष्ठा sk_buff *macsec_decrypt(काष्ठा sk_buff *skb,
				      काष्ठा net_device *dev,
				      काष्ठा macsec_rx_sa *rx_sa,
				      sci_t sci,
				      काष्ठा macsec_secy *secy)
अणु
	पूर्णांक ret;
	काष्ठा scatterlist *sg;
	काष्ठा sk_buff *trailer;
	अचिन्हित अक्षर *iv;
	काष्ठा aead_request *req;
	काष्ठा macsec_eth_header *hdr;
	u32 hdr_pn;
	u16 icv_len = secy->icv_len;

	macsec_skb_cb(skb)->valid = false;
	skb = skb_share_check(skb, GFP_ATOMIC);
	अगर (!skb)
		वापस ERR_PTR(-ENOMEM);

	ret = skb_cow_data(skb, 0, &trailer);
	अगर (unlikely(ret < 0)) अणु
		kमुक्त_skb(skb);
		वापस ERR_PTR(ret);
	पूर्ण
	req = macsec_alloc_req(rx_sa->key.tfm, &iv, &sg, ret);
	अगर (!req) अणु
		kमुक्त_skb(skb);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	hdr = (काष्ठा macsec_eth_header *)skb->data;
	hdr_pn = ntohl(hdr->packet_number);

	अगर (secy->xpn) अणु
		pn_t recovered_pn = rx_sa->next_pn_halves;

		recovered_pn.lower = hdr_pn;
		अगर (hdr_pn < rx_sa->next_pn_halves.lower &&
		    !pn_same_half(hdr_pn, rx_sa->next_pn_halves.lower))
			recovered_pn.upper++;

		macsec_fill_iv_xpn(iv, rx_sa->ssci, recovered_pn.full64,
				   rx_sa->key.salt);
	पूर्ण अन्यथा अणु
		macsec_fill_iv(iv, sci, hdr_pn);
	पूर्ण

	sg_init_table(sg, ret);
	ret = skb_to_sgvec(skb, sg, 0, skb->len);
	अगर (unlikely(ret < 0)) अणु
		aead_request_मुक्त(req);
		kमुक्त_skb(skb);
		वापस ERR_PTR(ret);
	पूर्ण

	अगर (hdr->tci_an & MACSEC_TCI_E) अणु
		/* confidentiality: ethernet + macsec header
		 * authenticated, encrypted payload
		 */
		पूर्णांक len = skb->len - macsec_hdr_len(macsec_skb_cb(skb)->has_sci);

		aead_request_set_crypt(req, sg, sg, len, iv);
		aead_request_set_ad(req, macsec_hdr_len(macsec_skb_cb(skb)->has_sci));
		skb = skb_unshare(skb, GFP_ATOMIC);
		अगर (!skb) अणु
			aead_request_मुक्त(req);
			वापस ERR_PTR(-ENOMEM);
		पूर्ण
	पूर्ण अन्यथा अणु
		/* पूर्णांकegrity only: all headers + data authenticated */
		aead_request_set_crypt(req, sg, sg, icv_len, iv);
		aead_request_set_ad(req, skb->len - icv_len);
	पूर्ण

	macsec_skb_cb(skb)->req = req;
	skb->dev = dev;
	aead_request_set_callback(req, 0, macsec_decrypt_करोne, skb);

	dev_hold(dev);
	ret = crypto_aead_decrypt(req);
	अगर (ret == -EINPROGRESS) अणु
		वापस ERR_PTR(ret);
	पूर्ण अन्यथा अगर (ret != 0) अणु
		/* decryption/authentication failed
		 * 10.6 अगर validateFrames is disabled, deliver anyway
		 */
		अगर (ret != -EBADMSG) अणु
			kमुक्त_skb(skb);
			skb = ERR_PTR(ret);
		पूर्ण
	पूर्ण अन्यथा अणु
		macsec_skb_cb(skb)->valid = true;
	पूर्ण
	dev_put(dev);

	aead_request_मुक्त(req);

	वापस skb;
पूर्ण

अटल काष्ठा macsec_rx_sc *find_rx_sc(काष्ठा macsec_secy *secy, sci_t sci)
अणु
	काष्ठा macsec_rx_sc *rx_sc;

	क्रम_each_rxsc(secy, rx_sc) अणु
		अगर (rx_sc->sci == sci)
			वापस rx_sc;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल काष्ठा macsec_rx_sc *find_rx_sc_rtnl(काष्ठा macsec_secy *secy, sci_t sci)
अणु
	काष्ठा macsec_rx_sc *rx_sc;

	क्रम_each_rxsc_rtnl(secy, rx_sc) अणु
		अगर (rx_sc->sci == sci)
			वापस rx_sc;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल क्रमागत rx_handler_result handle_not_macsec(काष्ठा sk_buff *skb)
अणु
	/* Deliver to the uncontrolled port by शेष */
	क्रमागत rx_handler_result ret = RX_HANDLER_PASS;
	काष्ठा ethhdr *hdr = eth_hdr(skb);
	काष्ठा macsec_rxh_data *rxd;
	काष्ठा macsec_dev *macsec;

	rcu_पढ़ो_lock();
	rxd = macsec_data_rcu(skb->dev);

	list_क्रम_each_entry_rcu(macsec, &rxd->secys, secys) अणु
		काष्ठा sk_buff *nskb;
		काष्ठा pcpu_secy_stats *secy_stats = this_cpu_ptr(macsec->stats);
		काष्ठा net_device *ndev = macsec->secy.netdev;

		/* If h/w offloading is enabled, HW decodes frames and strips
		 * the SecTAG, so we have to deduce which port to deliver to.
		 */
		अगर (macsec_is_offloaded(macsec) && netअगर_running(ndev)) अणु
			अगर (ether_addr_equal_64bits(hdr->h_dest,
						    ndev->dev_addr)) अणु
				/* exact match, भागert skb to this port */
				skb->dev = ndev;
				skb->pkt_type = PACKET_HOST;
				ret = RX_HANDLER_ANOTHER;
				जाओ out;
			पूर्ण अन्यथा अगर (is_multicast_ether_addr_64bits(
					   hdr->h_dest)) अणु
				/* multicast frame, deliver on this port too */
				nskb = skb_clone(skb, GFP_ATOMIC);
				अगर (!nskb)
					अवरोध;

				nskb->dev = ndev;
				अगर (ether_addr_equal_64bits(hdr->h_dest,
							    ndev->broadcast))
					nskb->pkt_type = PACKET_BROADCAST;
				अन्यथा
					nskb->pkt_type = PACKET_MULTICAST;

				netअगर_rx(nskb);
			पूर्ण
			जारी;
		पूर्ण

		/* 10.6 If the management control validateFrames is not
		 * Strict, frames without a SecTAG are received, counted, and
		 * delivered to the Controlled Port
		 */
		अगर (macsec->secy.validate_frames == MACSEC_VALIDATE_STRICT) अणु
			u64_stats_update_begin(&secy_stats->syncp);
			secy_stats->stats.InPktsNoTag++;
			u64_stats_update_end(&secy_stats->syncp);
			जारी;
		पूर्ण

		/* deliver on this port */
		nskb = skb_clone(skb, GFP_ATOMIC);
		अगर (!nskb)
			अवरोध;

		nskb->dev = ndev;

		अगर (netअगर_rx(nskb) == NET_RX_SUCCESS) अणु
			u64_stats_update_begin(&secy_stats->syncp);
			secy_stats->stats.InPktsUntagged++;
			u64_stats_update_end(&secy_stats->syncp);
		पूर्ण
	पूर्ण

out:
	rcu_पढ़ो_unlock();
	वापस ret;
पूर्ण

अटल rx_handler_result_t macsec_handle_frame(काष्ठा sk_buff **pskb)
अणु
	काष्ठा sk_buff *skb = *pskb;
	काष्ठा net_device *dev = skb->dev;
	काष्ठा macsec_eth_header *hdr;
	काष्ठा macsec_secy *secy = शून्य;
	काष्ठा macsec_rx_sc *rx_sc;
	काष्ठा macsec_rx_sa *rx_sa;
	काष्ठा macsec_rxh_data *rxd;
	काष्ठा macsec_dev *macsec;
	अचिन्हित पूर्णांक len;
	sci_t sci;
	u32 hdr_pn;
	bool cbit;
	काष्ठा pcpu_rx_sc_stats *rxsc_stats;
	काष्ठा pcpu_secy_stats *secy_stats;
	bool pulled_sci;
	पूर्णांक ret;

	अगर (skb_headroom(skb) < ETH_HLEN)
		जाओ drop_direct;

	hdr = macsec_ethhdr(skb);
	अगर (hdr->eth.h_proto != htons(ETH_P_MACSEC))
		वापस handle_not_macsec(skb);

	skb = skb_unshare(skb, GFP_ATOMIC);
	*pskb = skb;
	अगर (!skb)
		वापस RX_HANDLER_CONSUMED;

	pulled_sci = pskb_may_pull(skb, macsec_extra_len(true));
	अगर (!pulled_sci) अणु
		अगर (!pskb_may_pull(skb, macsec_extra_len(false)))
			जाओ drop_direct;
	पूर्ण

	hdr = macsec_ethhdr(skb);

	/* Frames with a SecTAG that has the TCI E bit set but the C
	 * bit clear are discarded, as this reserved encoding is used
	 * to identअगरy frames with a SecTAG that are not to be
	 * delivered to the Controlled Port.
	 */
	अगर ((hdr->tci_an & (MACSEC_TCI_C | MACSEC_TCI_E)) == MACSEC_TCI_E)
		वापस RX_HANDLER_PASS;

	/* now, pull the extra length */
	अगर (hdr->tci_an & MACSEC_TCI_SC) अणु
		अगर (!pulled_sci)
			जाओ drop_direct;
	पूर्ण

	/* ethernet header is part of crypto processing */
	skb_push(skb, ETH_HLEN);

	macsec_skb_cb(skb)->has_sci = !!(hdr->tci_an & MACSEC_TCI_SC);
	macsec_skb_cb(skb)->assoc_num = hdr->tci_an & MACSEC_AN_MASK;
	sci = macsec_frame_sci(hdr, macsec_skb_cb(skb)->has_sci);

	rcu_पढ़ो_lock();
	rxd = macsec_data_rcu(skb->dev);

	list_क्रम_each_entry_rcu(macsec, &rxd->secys, secys) अणु
		काष्ठा macsec_rx_sc *sc = find_rx_sc(&macsec->secy, sci);

		sc = sc ? macsec_rxsc_get(sc) : शून्य;

		अगर (sc) अणु
			secy = &macsec->secy;
			rx_sc = sc;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!secy)
		जाओ nosci;

	dev = secy->netdev;
	macsec = macsec_priv(dev);
	secy_stats = this_cpu_ptr(macsec->stats);
	rxsc_stats = this_cpu_ptr(rx_sc->stats);

	अगर (!macsec_validate_skb(skb, secy->icv_len, secy->xpn)) अणु
		u64_stats_update_begin(&secy_stats->syncp);
		secy_stats->stats.InPktsBadTag++;
		u64_stats_update_end(&secy_stats->syncp);
		जाओ drop_nosa;
	पूर्ण

	rx_sa = macsec_rxsa_get(rx_sc->sa[macsec_skb_cb(skb)->assoc_num]);
	अगर (!rx_sa) अणु
		/* 10.6.1 अगर the SA is not in use */

		/* If validateFrames is Strict or the C bit in the
		 * SecTAG is set, discard
		 */
		अगर (hdr->tci_an & MACSEC_TCI_C ||
		    secy->validate_frames == MACSEC_VALIDATE_STRICT) अणु
			u64_stats_update_begin(&rxsc_stats->syncp);
			rxsc_stats->stats.InPktsNotUsingSA++;
			u64_stats_update_end(&rxsc_stats->syncp);
			जाओ drop_nosa;
		पूर्ण

		/* not Strict, the frame (with the SecTAG and ICV
		 * हटाओd) is delivered to the Controlled Port.
		 */
		u64_stats_update_begin(&rxsc_stats->syncp);
		rxsc_stats->stats.InPktsUnusedSA++;
		u64_stats_update_end(&rxsc_stats->syncp);
		जाओ deliver;
	पूर्ण

	/* First, PN check to aव्योम decrypting obviously wrong packets */
	hdr_pn = ntohl(hdr->packet_number);
	अगर (secy->replay_protect) अणु
		bool late;

		spin_lock(&rx_sa->lock);
		late = rx_sa->next_pn_halves.lower >= secy->replay_winकरोw &&
		       hdr_pn < (rx_sa->next_pn_halves.lower - secy->replay_winकरोw);

		अगर (secy->xpn)
			late = late && pn_same_half(rx_sa->next_pn_halves.lower, hdr_pn);
		spin_unlock(&rx_sa->lock);

		अगर (late) अणु
			u64_stats_update_begin(&rxsc_stats->syncp);
			rxsc_stats->stats.InPktsLate++;
			u64_stats_update_end(&rxsc_stats->syncp);
			जाओ drop;
		पूर्ण
	पूर्ण

	macsec_skb_cb(skb)->rx_sa = rx_sa;

	/* Disabled && !changed text => skip validation */
	अगर (hdr->tci_an & MACSEC_TCI_C ||
	    secy->validate_frames != MACSEC_VALIDATE_DISABLED)
		skb = macsec_decrypt(skb, dev, rx_sa, sci, secy);

	अगर (IS_ERR(skb)) अणु
		/* the decrypt callback needs the reference */
		अगर (PTR_ERR(skb) != -EINPROGRESS) अणु
			macsec_rxsa_put(rx_sa);
			macsec_rxsc_put(rx_sc);
		पूर्ण
		rcu_पढ़ो_unlock();
		*pskb = शून्य;
		वापस RX_HANDLER_CONSUMED;
	पूर्ण

	अगर (!macsec_post_decrypt(skb, secy, hdr_pn))
		जाओ drop;

deliver:
	macsec_finalize_skb(skb, secy->icv_len,
			    macsec_extra_len(macsec_skb_cb(skb)->has_sci));
	macsec_reset_skb(skb, secy->netdev);

	अगर (rx_sa)
		macsec_rxsa_put(rx_sa);
	macsec_rxsc_put(rx_sc);

	skb_orphan(skb);
	len = skb->len;
	ret = gro_cells_receive(&macsec->gro_cells, skb);
	अगर (ret == NET_RX_SUCCESS)
		count_rx(dev, len);
	अन्यथा
		macsec->secy.netdev->stats.rx_dropped++;

	rcu_पढ़ो_unlock();

	*pskb = शून्य;
	वापस RX_HANDLER_CONSUMED;

drop:
	macsec_rxsa_put(rx_sa);
drop_nosa:
	macsec_rxsc_put(rx_sc);
	rcu_पढ़ो_unlock();
drop_direct:
	kमुक्त_skb(skb);
	*pskb = शून्य;
	वापस RX_HANDLER_CONSUMED;

nosci:
	/* 10.6.1 अगर the SC is not found */
	cbit = !!(hdr->tci_an & MACSEC_TCI_C);
	अगर (!cbit)
		macsec_finalize_skb(skb, DEFAULT_ICV_LEN,
				    macsec_extra_len(macsec_skb_cb(skb)->has_sci));

	list_क्रम_each_entry_rcu(macsec, &rxd->secys, secys) अणु
		काष्ठा sk_buff *nskb;

		secy_stats = this_cpu_ptr(macsec->stats);

		/* If validateFrames is Strict or the C bit in the
		 * SecTAG is set, discard
		 */
		अगर (cbit ||
		    macsec->secy.validate_frames == MACSEC_VALIDATE_STRICT) अणु
			u64_stats_update_begin(&secy_stats->syncp);
			secy_stats->stats.InPktsNoSCI++;
			u64_stats_update_end(&secy_stats->syncp);
			जारी;
		पूर्ण

		/* not strict, the frame (with the SecTAG and ICV
		 * हटाओd) is delivered to the Controlled Port.
		 */
		nskb = skb_clone(skb, GFP_ATOMIC);
		अगर (!nskb)
			अवरोध;

		macsec_reset_skb(nskb, macsec->secy.netdev);

		ret = netअगर_rx(nskb);
		अगर (ret == NET_RX_SUCCESS) अणु
			u64_stats_update_begin(&secy_stats->syncp);
			secy_stats->stats.InPktsUnknownSCI++;
			u64_stats_update_end(&secy_stats->syncp);
		पूर्ण अन्यथा अणु
			macsec->secy.netdev->stats.rx_dropped++;
		पूर्ण
	पूर्ण

	rcu_पढ़ो_unlock();
	*pskb = skb;
	वापस RX_HANDLER_PASS;
पूर्ण

अटल काष्ठा crypto_aead *macsec_alloc_tfm(अक्षर *key, पूर्णांक key_len, पूर्णांक icv_len)
अणु
	काष्ठा crypto_aead *tfm;
	पूर्णांक ret;

	/* Pick a sync gcm(aes) cipher to ensure order is preserved. */
	tfm = crypto_alloc_aead("gcm(aes)", 0, CRYPTO_ALG_ASYNC);

	अगर (IS_ERR(tfm))
		वापस tfm;

	ret = crypto_aead_setkey(tfm, key, key_len);
	अगर (ret < 0)
		जाओ fail;

	ret = crypto_aead_setauthsize(tfm, icv_len);
	अगर (ret < 0)
		जाओ fail;

	वापस tfm;
fail:
	crypto_मुक्त_aead(tfm);
	वापस ERR_PTR(ret);
पूर्ण

अटल पूर्णांक init_rx_sa(काष्ठा macsec_rx_sa *rx_sa, अक्षर *sak, पूर्णांक key_len,
		      पूर्णांक icv_len)
अणु
	rx_sa->stats = alloc_percpu(काष्ठा macsec_rx_sa_stats);
	अगर (!rx_sa->stats)
		वापस -ENOMEM;

	rx_sa->key.tfm = macsec_alloc_tfm(sak, key_len, icv_len);
	अगर (IS_ERR(rx_sa->key.tfm)) अणु
		मुक्त_percpu(rx_sa->stats);
		वापस PTR_ERR(rx_sa->key.tfm);
	पूर्ण

	rx_sa->ssci = MACSEC_UNDEF_SSCI;
	rx_sa->active = false;
	rx_sa->next_pn = 1;
	refcount_set(&rx_sa->refcnt, 1);
	spin_lock_init(&rx_sa->lock);

	वापस 0;
पूर्ण

अटल व्योम clear_rx_sa(काष्ठा macsec_rx_sa *rx_sa)
अणु
	rx_sa->active = false;

	macsec_rxsa_put(rx_sa);
पूर्ण

अटल व्योम मुक्त_rx_sc(काष्ठा macsec_rx_sc *rx_sc)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < MACSEC_NUM_AN; i++) अणु
		काष्ठा macsec_rx_sa *sa = rtnl_dereference(rx_sc->sa[i]);

		RCU_INIT_POINTER(rx_sc->sa[i], शून्य);
		अगर (sa)
			clear_rx_sa(sa);
	पूर्ण

	macsec_rxsc_put(rx_sc);
पूर्ण

अटल काष्ठा macsec_rx_sc *del_rx_sc(काष्ठा macsec_secy *secy, sci_t sci)
अणु
	काष्ठा macsec_rx_sc *rx_sc, __rcu **rx_scp;

	क्रम (rx_scp = &secy->rx_sc, rx_sc = rtnl_dereference(*rx_scp);
	     rx_sc;
	     rx_scp = &rx_sc->next, rx_sc = rtnl_dereference(*rx_scp)) अणु
		अगर (rx_sc->sci == sci) अणु
			अगर (rx_sc->active)
				secy->n_rx_sc--;
			rcu_assign_poपूर्णांकer(*rx_scp, rx_sc->next);
			वापस rx_sc;
		पूर्ण
	पूर्ण

	वापस शून्य;
पूर्ण

अटल काष्ठा macsec_rx_sc *create_rx_sc(काष्ठा net_device *dev, sci_t sci)
अणु
	काष्ठा macsec_rx_sc *rx_sc;
	काष्ठा macsec_dev *macsec;
	काष्ठा net_device *real_dev = macsec_priv(dev)->real_dev;
	काष्ठा macsec_rxh_data *rxd = macsec_data_rtnl(real_dev);
	काष्ठा macsec_secy *secy;

	list_क्रम_each_entry(macsec, &rxd->secys, secys) अणु
		अगर (find_rx_sc_rtnl(&macsec->secy, sci))
			वापस ERR_PTR(-EEXIST);
	पूर्ण

	rx_sc = kzalloc(माप(*rx_sc), GFP_KERNEL);
	अगर (!rx_sc)
		वापस ERR_PTR(-ENOMEM);

	rx_sc->stats = netdev_alloc_pcpu_stats(काष्ठा pcpu_rx_sc_stats);
	अगर (!rx_sc->stats) अणु
		kमुक्त(rx_sc);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	rx_sc->sci = sci;
	rx_sc->active = true;
	refcount_set(&rx_sc->refcnt, 1);

	secy = &macsec_priv(dev)->secy;
	rcu_assign_poपूर्णांकer(rx_sc->next, secy->rx_sc);
	rcu_assign_poपूर्णांकer(secy->rx_sc, rx_sc);

	अगर (rx_sc->active)
		secy->n_rx_sc++;

	वापस rx_sc;
पूर्ण

अटल पूर्णांक init_tx_sa(काष्ठा macsec_tx_sa *tx_sa, अक्षर *sak, पूर्णांक key_len,
		      पूर्णांक icv_len)
अणु
	tx_sa->stats = alloc_percpu(काष्ठा macsec_tx_sa_stats);
	अगर (!tx_sa->stats)
		वापस -ENOMEM;

	tx_sa->key.tfm = macsec_alloc_tfm(sak, key_len, icv_len);
	अगर (IS_ERR(tx_sa->key.tfm)) अणु
		मुक्त_percpu(tx_sa->stats);
		वापस PTR_ERR(tx_sa->key.tfm);
	पूर्ण

	tx_sa->ssci = MACSEC_UNDEF_SSCI;
	tx_sa->active = false;
	refcount_set(&tx_sa->refcnt, 1);
	spin_lock_init(&tx_sa->lock);

	वापस 0;
पूर्ण

अटल व्योम clear_tx_sa(काष्ठा macsec_tx_sa *tx_sa)
अणु
	tx_sa->active = false;

	macsec_txsa_put(tx_sa);
पूर्ण

अटल काष्ठा genl_family macsec_fam;

अटल काष्ठा net_device *get_dev_from_nl(काष्ठा net *net,
					  काष्ठा nlattr **attrs)
अणु
	पूर्णांक अगरindex = nla_get_u32(attrs[MACSEC_ATTR_IFINDEX]);
	काष्ठा net_device *dev;

	dev = __dev_get_by_index(net, अगरindex);
	अगर (!dev)
		वापस ERR_PTR(-ENODEV);

	अगर (!netअगर_is_macsec(dev))
		वापस ERR_PTR(-ENODEV);

	वापस dev;
पूर्ण

अटल क्रमागत macsec_offload nla_get_offload(स्थिर काष्ठा nlattr *nla)
अणु
	वापस (__क्रमce क्रमागत macsec_offload)nla_get_u8(nla);
पूर्ण

अटल sci_t nla_get_sci(स्थिर काष्ठा nlattr *nla)
अणु
	वापस (__क्रमce sci_t)nla_get_u64(nla);
पूर्ण

अटल पूर्णांक nla_put_sci(काष्ठा sk_buff *skb, पूर्णांक attrtype, sci_t value,
		       पूर्णांक padattr)
अणु
	वापस nla_put_u64_64bit(skb, attrtype, (__क्रमce u64)value, padattr);
पूर्ण

अटल ssci_t nla_get_ssci(स्थिर काष्ठा nlattr *nla)
अणु
	वापस (__क्रमce ssci_t)nla_get_u32(nla);
पूर्ण

अटल पूर्णांक nla_put_ssci(काष्ठा sk_buff *skb, पूर्णांक attrtype, ssci_t value)
अणु
	वापस nla_put_u32(skb, attrtype, (__क्रमce u64)value);
पूर्ण

अटल काष्ठा macsec_tx_sa *get_txsa_from_nl(काष्ठा net *net,
					     काष्ठा nlattr **attrs,
					     काष्ठा nlattr **tb_sa,
					     काष्ठा net_device **devp,
					     काष्ठा macsec_secy **secyp,
					     काष्ठा macsec_tx_sc **scp,
					     u8 *assoc_num)
अणु
	काष्ठा net_device *dev;
	काष्ठा macsec_secy *secy;
	काष्ठा macsec_tx_sc *tx_sc;
	काष्ठा macsec_tx_sa *tx_sa;

	अगर (!tb_sa[MACSEC_SA_ATTR_AN])
		वापस ERR_PTR(-EINVAL);

	*assoc_num = nla_get_u8(tb_sa[MACSEC_SA_ATTR_AN]);

	dev = get_dev_from_nl(net, attrs);
	अगर (IS_ERR(dev))
		वापस ERR_CAST(dev);

	अगर (*assoc_num >= MACSEC_NUM_AN)
		वापस ERR_PTR(-EINVAL);

	secy = &macsec_priv(dev)->secy;
	tx_sc = &secy->tx_sc;

	tx_sa = rtnl_dereference(tx_sc->sa[*assoc_num]);
	अगर (!tx_sa)
		वापस ERR_PTR(-ENODEV);

	*devp = dev;
	*scp = tx_sc;
	*secyp = secy;
	वापस tx_sa;
पूर्ण

अटल काष्ठा macsec_rx_sc *get_rxsc_from_nl(काष्ठा net *net,
					     काष्ठा nlattr **attrs,
					     काष्ठा nlattr **tb_rxsc,
					     काष्ठा net_device **devp,
					     काष्ठा macsec_secy **secyp)
अणु
	काष्ठा net_device *dev;
	काष्ठा macsec_secy *secy;
	काष्ठा macsec_rx_sc *rx_sc;
	sci_t sci;

	dev = get_dev_from_nl(net, attrs);
	अगर (IS_ERR(dev))
		वापस ERR_CAST(dev);

	secy = &macsec_priv(dev)->secy;

	अगर (!tb_rxsc[MACSEC_RXSC_ATTR_SCI])
		वापस ERR_PTR(-EINVAL);

	sci = nla_get_sci(tb_rxsc[MACSEC_RXSC_ATTR_SCI]);
	rx_sc = find_rx_sc_rtnl(secy, sci);
	अगर (!rx_sc)
		वापस ERR_PTR(-ENODEV);

	*secyp = secy;
	*devp = dev;

	वापस rx_sc;
पूर्ण

अटल काष्ठा macsec_rx_sa *get_rxsa_from_nl(काष्ठा net *net,
					     काष्ठा nlattr **attrs,
					     काष्ठा nlattr **tb_rxsc,
					     काष्ठा nlattr **tb_sa,
					     काष्ठा net_device **devp,
					     काष्ठा macsec_secy **secyp,
					     काष्ठा macsec_rx_sc **scp,
					     u8 *assoc_num)
अणु
	काष्ठा macsec_rx_sc *rx_sc;
	काष्ठा macsec_rx_sa *rx_sa;

	अगर (!tb_sa[MACSEC_SA_ATTR_AN])
		वापस ERR_PTR(-EINVAL);

	*assoc_num = nla_get_u8(tb_sa[MACSEC_SA_ATTR_AN]);
	अगर (*assoc_num >= MACSEC_NUM_AN)
		वापस ERR_PTR(-EINVAL);

	rx_sc = get_rxsc_from_nl(net, attrs, tb_rxsc, devp, secyp);
	अगर (IS_ERR(rx_sc))
		वापस ERR_CAST(rx_sc);

	rx_sa = rtnl_dereference(rx_sc->sa[*assoc_num]);
	अगर (!rx_sa)
		वापस ERR_PTR(-ENODEV);

	*scp = rx_sc;
	वापस rx_sa;
पूर्ण

अटल स्थिर काष्ठा nla_policy macsec_genl_policy[NUM_MACSEC_ATTR] = अणु
	[MACSEC_ATTR_IFINDEX] = अणु .type = NLA_U32 पूर्ण,
	[MACSEC_ATTR_RXSC_CONFIG] = अणु .type = NLA_NESTED पूर्ण,
	[MACSEC_ATTR_SA_CONFIG] = अणु .type = NLA_NESTED पूर्ण,
	[MACSEC_ATTR_OFFLOAD] = अणु .type = NLA_NESTED पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा nla_policy macsec_genl_rxsc_policy[NUM_MACSEC_RXSC_ATTR] = अणु
	[MACSEC_RXSC_ATTR_SCI] = अणु .type = NLA_U64 पूर्ण,
	[MACSEC_RXSC_ATTR_ACTIVE] = अणु .type = NLA_U8 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा nla_policy macsec_genl_sa_policy[NUM_MACSEC_SA_ATTR] = अणु
	[MACSEC_SA_ATTR_AN] = अणु .type = NLA_U8 पूर्ण,
	[MACSEC_SA_ATTR_ACTIVE] = अणु .type = NLA_U8 पूर्ण,
	[MACSEC_SA_ATTR_PN] = NLA_POLICY_MIN_LEN(4),
	[MACSEC_SA_ATTR_KEYID] = अणु .type = NLA_BINARY,
				   .len = MACSEC_KEYID_LEN, पूर्ण,
	[MACSEC_SA_ATTR_KEY] = अणु .type = NLA_BINARY,
				 .len = MACSEC_MAX_KEY_LEN, पूर्ण,
	[MACSEC_SA_ATTR_SSCI] = अणु .type = NLA_U32 पूर्ण,
	[MACSEC_SA_ATTR_SALT] = अणु .type = NLA_BINARY,
				  .len = MACSEC_SALT_LEN, पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा nla_policy macsec_genl_offload_policy[NUM_MACSEC_OFFLOAD_ATTR] = अणु
	[MACSEC_OFFLOAD_ATTR_TYPE] = अणु .type = NLA_U8 पूर्ण,
पूर्ण;

/* Offloads an operation to a device driver */
अटल पूर्णांक macsec_offload(पूर्णांक (* स्थिर func)(काष्ठा macsec_context *),
			  काष्ठा macsec_context *ctx)
अणु
	पूर्णांक ret;

	अगर (unlikely(!func))
		वापस 0;

	अगर (ctx->offload == MACSEC_OFFLOAD_PHY)
		mutex_lock(&ctx->phydev->lock);

	/* Phase I: prepare. The drive should fail here अगर there are going to be
	 * issues in the commit phase.
	 */
	ctx->prepare = true;
	ret = (*func)(ctx);
	अगर (ret)
		जाओ phy_unlock;

	/* Phase II: commit. This step cannot fail. */
	ctx->prepare = false;
	ret = (*func)(ctx);
	/* This should never happen: commit is not allowed to fail */
	अगर (unlikely(ret))
		WARN(1, "MACsec offloading commit failed (%d)\n", ret);

phy_unlock:
	अगर (ctx->offload == MACSEC_OFFLOAD_PHY)
		mutex_unlock(&ctx->phydev->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक parse_sa_config(काष्ठा nlattr **attrs, काष्ठा nlattr **tb_sa)
अणु
	अगर (!attrs[MACSEC_ATTR_SA_CONFIG])
		वापस -EINVAL;

	अगर (nla_parse_nested_deprecated(tb_sa, MACSEC_SA_ATTR_MAX, attrs[MACSEC_ATTR_SA_CONFIG], macsec_genl_sa_policy, शून्य))
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक parse_rxsc_config(काष्ठा nlattr **attrs, काष्ठा nlattr **tb_rxsc)
अणु
	अगर (!attrs[MACSEC_ATTR_RXSC_CONFIG])
		वापस -EINVAL;

	अगर (nla_parse_nested_deprecated(tb_rxsc, MACSEC_RXSC_ATTR_MAX, attrs[MACSEC_ATTR_RXSC_CONFIG], macsec_genl_rxsc_policy, शून्य))
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल bool validate_add_rxsa(काष्ठा nlattr **attrs)
अणु
	अगर (!attrs[MACSEC_SA_ATTR_AN] ||
	    !attrs[MACSEC_SA_ATTR_KEY] ||
	    !attrs[MACSEC_SA_ATTR_KEYID])
		वापस false;

	अगर (nla_get_u8(attrs[MACSEC_SA_ATTR_AN]) >= MACSEC_NUM_AN)
		वापस false;

	अगर (attrs[MACSEC_SA_ATTR_PN] &&
	    *(u64 *)nla_data(attrs[MACSEC_SA_ATTR_PN]) == 0)
		वापस false;

	अगर (attrs[MACSEC_SA_ATTR_ACTIVE]) अणु
		अगर (nla_get_u8(attrs[MACSEC_SA_ATTR_ACTIVE]) > 1)
			वापस false;
	पूर्ण

	अगर (nla_len(attrs[MACSEC_SA_ATTR_KEYID]) != MACSEC_KEYID_LEN)
		वापस false;

	वापस true;
पूर्ण

अटल पूर्णांक macsec_add_rxsa(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा net_device *dev;
	काष्ठा nlattr **attrs = info->attrs;
	काष्ठा macsec_secy *secy;
	काष्ठा macsec_rx_sc *rx_sc;
	काष्ठा macsec_rx_sa *rx_sa;
	अचिन्हित अक्षर assoc_num;
	पूर्णांक pn_len;
	काष्ठा nlattr *tb_rxsc[MACSEC_RXSC_ATTR_MAX + 1];
	काष्ठा nlattr *tb_sa[MACSEC_SA_ATTR_MAX + 1];
	पूर्णांक err;

	अगर (!attrs[MACSEC_ATTR_IFINDEX])
		वापस -EINVAL;

	अगर (parse_sa_config(attrs, tb_sa))
		वापस -EINVAL;

	अगर (parse_rxsc_config(attrs, tb_rxsc))
		वापस -EINVAL;

	अगर (!validate_add_rxsa(tb_sa))
		वापस -EINVAL;

	rtnl_lock();
	rx_sc = get_rxsc_from_nl(genl_info_net(info), attrs, tb_rxsc, &dev, &secy);
	अगर (IS_ERR(rx_sc)) अणु
		rtnl_unlock();
		वापस PTR_ERR(rx_sc);
	पूर्ण

	assoc_num = nla_get_u8(tb_sa[MACSEC_SA_ATTR_AN]);

	अगर (nla_len(tb_sa[MACSEC_SA_ATTR_KEY]) != secy->key_len) अणु
		pr_notice("macsec: nl: add_rxsa: bad key length: %d != %d\n",
			  nla_len(tb_sa[MACSEC_SA_ATTR_KEY]), secy->key_len);
		rtnl_unlock();
		वापस -EINVAL;
	पूर्ण

	pn_len = secy->xpn ? MACSEC_XPN_PN_LEN : MACSEC_DEFAULT_PN_LEN;
	अगर (nla_len(tb_sa[MACSEC_SA_ATTR_PN]) != pn_len) अणु
		pr_notice("macsec: nl: add_rxsa: bad pn length: %d != %d\n",
			  nla_len(tb_sa[MACSEC_SA_ATTR_PN]), pn_len);
		rtnl_unlock();
		वापस -EINVAL;
	पूर्ण

	अगर (secy->xpn) अणु
		अगर (!tb_sa[MACSEC_SA_ATTR_SSCI] || !tb_sa[MACSEC_SA_ATTR_SALT]) अणु
			rtnl_unlock();
			वापस -EINVAL;
		पूर्ण

		अगर (nla_len(tb_sa[MACSEC_SA_ATTR_SALT]) != MACSEC_SALT_LEN) अणु
			pr_notice("macsec: nl: add_rxsa: bad salt length: %d != %d\n",
				  nla_len(tb_sa[MACSEC_SA_ATTR_SALT]),
				  MACSEC_SA_ATTR_SALT);
			rtnl_unlock();
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	rx_sa = rtnl_dereference(rx_sc->sa[assoc_num]);
	अगर (rx_sa) अणु
		rtnl_unlock();
		वापस -EBUSY;
	पूर्ण

	rx_sa = kदो_स्मृति(माप(*rx_sa), GFP_KERNEL);
	अगर (!rx_sa) अणु
		rtnl_unlock();
		वापस -ENOMEM;
	पूर्ण

	err = init_rx_sa(rx_sa, nla_data(tb_sa[MACSEC_SA_ATTR_KEY]),
			 secy->key_len, secy->icv_len);
	अगर (err < 0) अणु
		kमुक्त(rx_sa);
		rtnl_unlock();
		वापस err;
	पूर्ण

	अगर (tb_sa[MACSEC_SA_ATTR_PN]) अणु
		spin_lock_bh(&rx_sa->lock);
		rx_sa->next_pn = nla_get_u64(tb_sa[MACSEC_SA_ATTR_PN]);
		spin_unlock_bh(&rx_sa->lock);
	पूर्ण

	अगर (tb_sa[MACSEC_SA_ATTR_ACTIVE])
		rx_sa->active = !!nla_get_u8(tb_sa[MACSEC_SA_ATTR_ACTIVE]);

	rx_sa->sc = rx_sc;

	/* If h/w offloading is available, propagate to the device */
	अगर (macsec_is_offloaded(netdev_priv(dev))) अणु
		स्थिर काष्ठा macsec_ops *ops;
		काष्ठा macsec_context ctx;

		ops = macsec_get_ops(netdev_priv(dev), &ctx);
		अगर (!ops) अणु
			err = -EOPNOTSUPP;
			जाओ cleanup;
		पूर्ण

		ctx.sa.assoc_num = assoc_num;
		ctx.sa.rx_sa = rx_sa;
		ctx.secy = secy;
		स_नकल(ctx.sa.key, nla_data(tb_sa[MACSEC_SA_ATTR_KEY]),
		       MACSEC_KEYID_LEN);

		err = macsec_offload(ops->mकरो_add_rxsa, &ctx);
		अगर (err)
			जाओ cleanup;
	पूर्ण

	अगर (secy->xpn) अणु
		rx_sa->ssci = nla_get_ssci(tb_sa[MACSEC_SA_ATTR_SSCI]);
		nla_स_नकल(rx_sa->key.salt.bytes, tb_sa[MACSEC_SA_ATTR_SALT],
			   MACSEC_SALT_LEN);
	पूर्ण

	nla_स_नकल(rx_sa->key.id, tb_sa[MACSEC_SA_ATTR_KEYID], MACSEC_KEYID_LEN);
	rcu_assign_poपूर्णांकer(rx_sc->sa[assoc_num], rx_sa);

	rtnl_unlock();

	वापस 0;

cleanup:
	kमुक्त(rx_sa);
	rtnl_unlock();
	वापस err;
पूर्ण

अटल bool validate_add_rxsc(काष्ठा nlattr **attrs)
अणु
	अगर (!attrs[MACSEC_RXSC_ATTR_SCI])
		वापस false;

	अगर (attrs[MACSEC_RXSC_ATTR_ACTIVE]) अणु
		अगर (nla_get_u8(attrs[MACSEC_RXSC_ATTR_ACTIVE]) > 1)
			वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल पूर्णांक macsec_add_rxsc(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा net_device *dev;
	sci_t sci = MACSEC_UNDEF_SCI;
	काष्ठा nlattr **attrs = info->attrs;
	काष्ठा macsec_rx_sc *rx_sc;
	काष्ठा nlattr *tb_rxsc[MACSEC_RXSC_ATTR_MAX + 1];
	काष्ठा macsec_secy *secy;
	bool was_active;
	पूर्णांक ret;

	अगर (!attrs[MACSEC_ATTR_IFINDEX])
		वापस -EINVAL;

	अगर (parse_rxsc_config(attrs, tb_rxsc))
		वापस -EINVAL;

	अगर (!validate_add_rxsc(tb_rxsc))
		वापस -EINVAL;

	rtnl_lock();
	dev = get_dev_from_nl(genl_info_net(info), attrs);
	अगर (IS_ERR(dev)) अणु
		rtnl_unlock();
		वापस PTR_ERR(dev);
	पूर्ण

	secy = &macsec_priv(dev)->secy;
	sci = nla_get_sci(tb_rxsc[MACSEC_RXSC_ATTR_SCI]);

	rx_sc = create_rx_sc(dev, sci);
	अगर (IS_ERR(rx_sc)) अणु
		rtnl_unlock();
		वापस PTR_ERR(rx_sc);
	पूर्ण

	was_active = rx_sc->active;
	अगर (tb_rxsc[MACSEC_RXSC_ATTR_ACTIVE])
		rx_sc->active = !!nla_get_u8(tb_rxsc[MACSEC_RXSC_ATTR_ACTIVE]);

	अगर (macsec_is_offloaded(netdev_priv(dev))) अणु
		स्थिर काष्ठा macsec_ops *ops;
		काष्ठा macsec_context ctx;

		ops = macsec_get_ops(netdev_priv(dev), &ctx);
		अगर (!ops) अणु
			ret = -EOPNOTSUPP;
			जाओ cleanup;
		पूर्ण

		ctx.rx_sc = rx_sc;
		ctx.secy = secy;

		ret = macsec_offload(ops->mकरो_add_rxsc, &ctx);
		अगर (ret)
			जाओ cleanup;
	पूर्ण

	rtnl_unlock();

	वापस 0;

cleanup:
	rx_sc->active = was_active;
	rtnl_unlock();
	वापस ret;
पूर्ण

अटल bool validate_add_txsa(काष्ठा nlattr **attrs)
अणु
	अगर (!attrs[MACSEC_SA_ATTR_AN] ||
	    !attrs[MACSEC_SA_ATTR_PN] ||
	    !attrs[MACSEC_SA_ATTR_KEY] ||
	    !attrs[MACSEC_SA_ATTR_KEYID])
		वापस false;

	अगर (nla_get_u8(attrs[MACSEC_SA_ATTR_AN]) >= MACSEC_NUM_AN)
		वापस false;

	अगर (nla_get_u32(attrs[MACSEC_SA_ATTR_PN]) == 0)
		वापस false;

	अगर (attrs[MACSEC_SA_ATTR_ACTIVE]) अणु
		अगर (nla_get_u8(attrs[MACSEC_SA_ATTR_ACTIVE]) > 1)
			वापस false;
	पूर्ण

	अगर (nla_len(attrs[MACSEC_SA_ATTR_KEYID]) != MACSEC_KEYID_LEN)
		वापस false;

	वापस true;
पूर्ण

अटल पूर्णांक macsec_add_txsa(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा net_device *dev;
	काष्ठा nlattr **attrs = info->attrs;
	काष्ठा macsec_secy *secy;
	काष्ठा macsec_tx_sc *tx_sc;
	काष्ठा macsec_tx_sa *tx_sa;
	अचिन्हित अक्षर assoc_num;
	पूर्णांक pn_len;
	काष्ठा nlattr *tb_sa[MACSEC_SA_ATTR_MAX + 1];
	bool was_operational;
	पूर्णांक err;

	अगर (!attrs[MACSEC_ATTR_IFINDEX])
		वापस -EINVAL;

	अगर (parse_sa_config(attrs, tb_sa))
		वापस -EINVAL;

	अगर (!validate_add_txsa(tb_sa))
		वापस -EINVAL;

	rtnl_lock();
	dev = get_dev_from_nl(genl_info_net(info), attrs);
	अगर (IS_ERR(dev)) अणु
		rtnl_unlock();
		वापस PTR_ERR(dev);
	पूर्ण

	secy = &macsec_priv(dev)->secy;
	tx_sc = &secy->tx_sc;

	assoc_num = nla_get_u8(tb_sa[MACSEC_SA_ATTR_AN]);

	अगर (nla_len(tb_sa[MACSEC_SA_ATTR_KEY]) != secy->key_len) अणु
		pr_notice("macsec: nl: add_txsa: bad key length: %d != %d\n",
			  nla_len(tb_sa[MACSEC_SA_ATTR_KEY]), secy->key_len);
		rtnl_unlock();
		वापस -EINVAL;
	पूर्ण

	pn_len = secy->xpn ? MACSEC_XPN_PN_LEN : MACSEC_DEFAULT_PN_LEN;
	अगर (nla_len(tb_sa[MACSEC_SA_ATTR_PN]) != pn_len) अणु
		pr_notice("macsec: nl: add_txsa: bad pn length: %d != %d\n",
			  nla_len(tb_sa[MACSEC_SA_ATTR_PN]), pn_len);
		rtnl_unlock();
		वापस -EINVAL;
	पूर्ण

	अगर (secy->xpn) अणु
		अगर (!tb_sa[MACSEC_SA_ATTR_SSCI] || !tb_sa[MACSEC_SA_ATTR_SALT]) अणु
			rtnl_unlock();
			वापस -EINVAL;
		पूर्ण

		अगर (nla_len(tb_sa[MACSEC_SA_ATTR_SALT]) != MACSEC_SALT_LEN) अणु
			pr_notice("macsec: nl: add_txsa: bad salt length: %d != %d\n",
				  nla_len(tb_sa[MACSEC_SA_ATTR_SALT]),
				  MACSEC_SA_ATTR_SALT);
			rtnl_unlock();
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	tx_sa = rtnl_dereference(tx_sc->sa[assoc_num]);
	अगर (tx_sa) अणु
		rtnl_unlock();
		वापस -EBUSY;
	पूर्ण

	tx_sa = kदो_स्मृति(माप(*tx_sa), GFP_KERNEL);
	अगर (!tx_sa) अणु
		rtnl_unlock();
		वापस -ENOMEM;
	पूर्ण

	err = init_tx_sa(tx_sa, nla_data(tb_sa[MACSEC_SA_ATTR_KEY]),
			 secy->key_len, secy->icv_len);
	अगर (err < 0) अणु
		kमुक्त(tx_sa);
		rtnl_unlock();
		वापस err;
	पूर्ण

	spin_lock_bh(&tx_sa->lock);
	tx_sa->next_pn = nla_get_u64(tb_sa[MACSEC_SA_ATTR_PN]);
	spin_unlock_bh(&tx_sa->lock);

	अगर (tb_sa[MACSEC_SA_ATTR_ACTIVE])
		tx_sa->active = !!nla_get_u8(tb_sa[MACSEC_SA_ATTR_ACTIVE]);

	was_operational = secy->operational;
	अगर (assoc_num == tx_sc->encoding_sa && tx_sa->active)
		secy->operational = true;

	/* If h/w offloading is available, propagate to the device */
	अगर (macsec_is_offloaded(netdev_priv(dev))) अणु
		स्थिर काष्ठा macsec_ops *ops;
		काष्ठा macsec_context ctx;

		ops = macsec_get_ops(netdev_priv(dev), &ctx);
		अगर (!ops) अणु
			err = -EOPNOTSUPP;
			जाओ cleanup;
		पूर्ण

		ctx.sa.assoc_num = assoc_num;
		ctx.sa.tx_sa = tx_sa;
		ctx.secy = secy;
		स_नकल(ctx.sa.key, nla_data(tb_sa[MACSEC_SA_ATTR_KEY]),
		       MACSEC_KEYID_LEN);

		err = macsec_offload(ops->mकरो_add_txsa, &ctx);
		अगर (err)
			जाओ cleanup;
	पूर्ण

	अगर (secy->xpn) अणु
		tx_sa->ssci = nla_get_ssci(tb_sa[MACSEC_SA_ATTR_SSCI]);
		nla_स_नकल(tx_sa->key.salt.bytes, tb_sa[MACSEC_SA_ATTR_SALT],
			   MACSEC_SALT_LEN);
	पूर्ण

	nla_स_नकल(tx_sa->key.id, tb_sa[MACSEC_SA_ATTR_KEYID], MACSEC_KEYID_LEN);
	rcu_assign_poपूर्णांकer(tx_sc->sa[assoc_num], tx_sa);

	rtnl_unlock();

	वापस 0;

cleanup:
	secy->operational = was_operational;
	kमुक्त(tx_sa);
	rtnl_unlock();
	वापस err;
पूर्ण

अटल पूर्णांक macsec_del_rxsa(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा nlattr **attrs = info->attrs;
	काष्ठा net_device *dev;
	काष्ठा macsec_secy *secy;
	काष्ठा macsec_rx_sc *rx_sc;
	काष्ठा macsec_rx_sa *rx_sa;
	u8 assoc_num;
	काष्ठा nlattr *tb_rxsc[MACSEC_RXSC_ATTR_MAX + 1];
	काष्ठा nlattr *tb_sa[MACSEC_SA_ATTR_MAX + 1];
	पूर्णांक ret;

	अगर (!attrs[MACSEC_ATTR_IFINDEX])
		वापस -EINVAL;

	अगर (parse_sa_config(attrs, tb_sa))
		वापस -EINVAL;

	अगर (parse_rxsc_config(attrs, tb_rxsc))
		वापस -EINVAL;

	rtnl_lock();
	rx_sa = get_rxsa_from_nl(genl_info_net(info), attrs, tb_rxsc, tb_sa,
				 &dev, &secy, &rx_sc, &assoc_num);
	अगर (IS_ERR(rx_sa)) अणु
		rtnl_unlock();
		वापस PTR_ERR(rx_sa);
	पूर्ण

	अगर (rx_sa->active) अणु
		rtnl_unlock();
		वापस -EBUSY;
	पूर्ण

	/* If h/w offloading is available, propagate to the device */
	अगर (macsec_is_offloaded(netdev_priv(dev))) अणु
		स्थिर काष्ठा macsec_ops *ops;
		काष्ठा macsec_context ctx;

		ops = macsec_get_ops(netdev_priv(dev), &ctx);
		अगर (!ops) अणु
			ret = -EOPNOTSUPP;
			जाओ cleanup;
		पूर्ण

		ctx.sa.assoc_num = assoc_num;
		ctx.sa.rx_sa = rx_sa;
		ctx.secy = secy;

		ret = macsec_offload(ops->mकरो_del_rxsa, &ctx);
		अगर (ret)
			जाओ cleanup;
	पूर्ण

	RCU_INIT_POINTER(rx_sc->sa[assoc_num], शून्य);
	clear_rx_sa(rx_sa);

	rtnl_unlock();

	वापस 0;

cleanup:
	rtnl_unlock();
	वापस ret;
पूर्ण

अटल पूर्णांक macsec_del_rxsc(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा nlattr **attrs = info->attrs;
	काष्ठा net_device *dev;
	काष्ठा macsec_secy *secy;
	काष्ठा macsec_rx_sc *rx_sc;
	sci_t sci;
	काष्ठा nlattr *tb_rxsc[MACSEC_RXSC_ATTR_MAX + 1];
	पूर्णांक ret;

	अगर (!attrs[MACSEC_ATTR_IFINDEX])
		वापस -EINVAL;

	अगर (parse_rxsc_config(attrs, tb_rxsc))
		वापस -EINVAL;

	अगर (!tb_rxsc[MACSEC_RXSC_ATTR_SCI])
		वापस -EINVAL;

	rtnl_lock();
	dev = get_dev_from_nl(genl_info_net(info), info->attrs);
	अगर (IS_ERR(dev)) अणु
		rtnl_unlock();
		वापस PTR_ERR(dev);
	पूर्ण

	secy = &macsec_priv(dev)->secy;
	sci = nla_get_sci(tb_rxsc[MACSEC_RXSC_ATTR_SCI]);

	rx_sc = del_rx_sc(secy, sci);
	अगर (!rx_sc) अणु
		rtnl_unlock();
		वापस -ENODEV;
	पूर्ण

	/* If h/w offloading is available, propagate to the device */
	अगर (macsec_is_offloaded(netdev_priv(dev))) अणु
		स्थिर काष्ठा macsec_ops *ops;
		काष्ठा macsec_context ctx;

		ops = macsec_get_ops(netdev_priv(dev), &ctx);
		अगर (!ops) अणु
			ret = -EOPNOTSUPP;
			जाओ cleanup;
		पूर्ण

		ctx.rx_sc = rx_sc;
		ctx.secy = secy;
		ret = macsec_offload(ops->mकरो_del_rxsc, &ctx);
		अगर (ret)
			जाओ cleanup;
	पूर्ण

	मुक्त_rx_sc(rx_sc);
	rtnl_unlock();

	वापस 0;

cleanup:
	rtnl_unlock();
	वापस ret;
पूर्ण

अटल पूर्णांक macsec_del_txsa(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा nlattr **attrs = info->attrs;
	काष्ठा net_device *dev;
	काष्ठा macsec_secy *secy;
	काष्ठा macsec_tx_sc *tx_sc;
	काष्ठा macsec_tx_sa *tx_sa;
	u8 assoc_num;
	काष्ठा nlattr *tb_sa[MACSEC_SA_ATTR_MAX + 1];
	पूर्णांक ret;

	अगर (!attrs[MACSEC_ATTR_IFINDEX])
		वापस -EINVAL;

	अगर (parse_sa_config(attrs, tb_sa))
		वापस -EINVAL;

	rtnl_lock();
	tx_sa = get_txsa_from_nl(genl_info_net(info), attrs, tb_sa,
				 &dev, &secy, &tx_sc, &assoc_num);
	अगर (IS_ERR(tx_sa)) अणु
		rtnl_unlock();
		वापस PTR_ERR(tx_sa);
	पूर्ण

	अगर (tx_sa->active) अणु
		rtnl_unlock();
		वापस -EBUSY;
	पूर्ण

	/* If h/w offloading is available, propagate to the device */
	अगर (macsec_is_offloaded(netdev_priv(dev))) अणु
		स्थिर काष्ठा macsec_ops *ops;
		काष्ठा macsec_context ctx;

		ops = macsec_get_ops(netdev_priv(dev), &ctx);
		अगर (!ops) अणु
			ret = -EOPNOTSUPP;
			जाओ cleanup;
		पूर्ण

		ctx.sa.assoc_num = assoc_num;
		ctx.sa.tx_sa = tx_sa;
		ctx.secy = secy;

		ret = macsec_offload(ops->mकरो_del_txsa, &ctx);
		अगर (ret)
			जाओ cleanup;
	पूर्ण

	RCU_INIT_POINTER(tx_sc->sa[assoc_num], शून्य);
	clear_tx_sa(tx_sa);

	rtnl_unlock();

	वापस 0;

cleanup:
	rtnl_unlock();
	वापस ret;
पूर्ण

अटल bool validate_upd_sa(काष्ठा nlattr **attrs)
अणु
	अगर (!attrs[MACSEC_SA_ATTR_AN] ||
	    attrs[MACSEC_SA_ATTR_KEY] ||
	    attrs[MACSEC_SA_ATTR_KEYID] ||
	    attrs[MACSEC_SA_ATTR_SSCI] ||
	    attrs[MACSEC_SA_ATTR_SALT])
		वापस false;

	अगर (nla_get_u8(attrs[MACSEC_SA_ATTR_AN]) >= MACSEC_NUM_AN)
		वापस false;

	अगर (attrs[MACSEC_SA_ATTR_PN] && nla_get_u32(attrs[MACSEC_SA_ATTR_PN]) == 0)
		वापस false;

	अगर (attrs[MACSEC_SA_ATTR_ACTIVE]) अणु
		अगर (nla_get_u8(attrs[MACSEC_SA_ATTR_ACTIVE]) > 1)
			वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल पूर्णांक macsec_upd_txsa(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा nlattr **attrs = info->attrs;
	काष्ठा net_device *dev;
	काष्ठा macsec_secy *secy;
	काष्ठा macsec_tx_sc *tx_sc;
	काष्ठा macsec_tx_sa *tx_sa;
	u8 assoc_num;
	काष्ठा nlattr *tb_sa[MACSEC_SA_ATTR_MAX + 1];
	bool was_operational, was_active;
	pn_t prev_pn;
	पूर्णांक ret = 0;

	prev_pn.full64 = 0;

	अगर (!attrs[MACSEC_ATTR_IFINDEX])
		वापस -EINVAL;

	अगर (parse_sa_config(attrs, tb_sa))
		वापस -EINVAL;

	अगर (!validate_upd_sa(tb_sa))
		वापस -EINVAL;

	rtnl_lock();
	tx_sa = get_txsa_from_nl(genl_info_net(info), attrs, tb_sa,
				 &dev, &secy, &tx_sc, &assoc_num);
	अगर (IS_ERR(tx_sa)) अणु
		rtnl_unlock();
		वापस PTR_ERR(tx_sa);
	पूर्ण

	अगर (tb_sa[MACSEC_SA_ATTR_PN]) अणु
		पूर्णांक pn_len;

		pn_len = secy->xpn ? MACSEC_XPN_PN_LEN : MACSEC_DEFAULT_PN_LEN;
		अगर (nla_len(tb_sa[MACSEC_SA_ATTR_PN]) != pn_len) अणु
			pr_notice("macsec: nl: upd_txsa: bad pn length: %d != %d\n",
				  nla_len(tb_sa[MACSEC_SA_ATTR_PN]), pn_len);
			rtnl_unlock();
			वापस -EINVAL;
		पूर्ण

		spin_lock_bh(&tx_sa->lock);
		prev_pn = tx_sa->next_pn_halves;
		tx_sa->next_pn = nla_get_u64(tb_sa[MACSEC_SA_ATTR_PN]);
		spin_unlock_bh(&tx_sa->lock);
	पूर्ण

	was_active = tx_sa->active;
	अगर (tb_sa[MACSEC_SA_ATTR_ACTIVE])
		tx_sa->active = nla_get_u8(tb_sa[MACSEC_SA_ATTR_ACTIVE]);

	was_operational = secy->operational;
	अगर (assoc_num == tx_sc->encoding_sa)
		secy->operational = tx_sa->active;

	/* If h/w offloading is available, propagate to the device */
	अगर (macsec_is_offloaded(netdev_priv(dev))) अणु
		स्थिर काष्ठा macsec_ops *ops;
		काष्ठा macsec_context ctx;

		ops = macsec_get_ops(netdev_priv(dev), &ctx);
		अगर (!ops) अणु
			ret = -EOPNOTSUPP;
			जाओ cleanup;
		पूर्ण

		ctx.sa.assoc_num = assoc_num;
		ctx.sa.tx_sa = tx_sa;
		ctx.secy = secy;

		ret = macsec_offload(ops->mकरो_upd_txsa, &ctx);
		अगर (ret)
			जाओ cleanup;
	पूर्ण

	rtnl_unlock();

	वापस 0;

cleanup:
	अगर (tb_sa[MACSEC_SA_ATTR_PN]) अणु
		spin_lock_bh(&tx_sa->lock);
		tx_sa->next_pn_halves = prev_pn;
		spin_unlock_bh(&tx_sa->lock);
	पूर्ण
	tx_sa->active = was_active;
	secy->operational = was_operational;
	rtnl_unlock();
	वापस ret;
पूर्ण

अटल पूर्णांक macsec_upd_rxsa(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा nlattr **attrs = info->attrs;
	काष्ठा net_device *dev;
	काष्ठा macsec_secy *secy;
	काष्ठा macsec_rx_sc *rx_sc;
	काष्ठा macsec_rx_sa *rx_sa;
	u8 assoc_num;
	काष्ठा nlattr *tb_rxsc[MACSEC_RXSC_ATTR_MAX + 1];
	काष्ठा nlattr *tb_sa[MACSEC_SA_ATTR_MAX + 1];
	bool was_active;
	pn_t prev_pn;
	पूर्णांक ret = 0;

	prev_pn.full64 = 0;

	अगर (!attrs[MACSEC_ATTR_IFINDEX])
		वापस -EINVAL;

	अगर (parse_rxsc_config(attrs, tb_rxsc))
		वापस -EINVAL;

	अगर (parse_sa_config(attrs, tb_sa))
		वापस -EINVAL;

	अगर (!validate_upd_sa(tb_sa))
		वापस -EINVAL;

	rtnl_lock();
	rx_sa = get_rxsa_from_nl(genl_info_net(info), attrs, tb_rxsc, tb_sa,
				 &dev, &secy, &rx_sc, &assoc_num);
	अगर (IS_ERR(rx_sa)) अणु
		rtnl_unlock();
		वापस PTR_ERR(rx_sa);
	पूर्ण

	अगर (tb_sa[MACSEC_SA_ATTR_PN]) अणु
		पूर्णांक pn_len;

		pn_len = secy->xpn ? MACSEC_XPN_PN_LEN : MACSEC_DEFAULT_PN_LEN;
		अगर (nla_len(tb_sa[MACSEC_SA_ATTR_PN]) != pn_len) अणु
			pr_notice("macsec: nl: upd_rxsa: bad pn length: %d != %d\n",
				  nla_len(tb_sa[MACSEC_SA_ATTR_PN]), pn_len);
			rtnl_unlock();
			वापस -EINVAL;
		पूर्ण

		spin_lock_bh(&rx_sa->lock);
		prev_pn = rx_sa->next_pn_halves;
		rx_sa->next_pn = nla_get_u64(tb_sa[MACSEC_SA_ATTR_PN]);
		spin_unlock_bh(&rx_sa->lock);
	पूर्ण

	was_active = rx_sa->active;
	अगर (tb_sa[MACSEC_SA_ATTR_ACTIVE])
		rx_sa->active = nla_get_u8(tb_sa[MACSEC_SA_ATTR_ACTIVE]);

	/* If h/w offloading is available, propagate to the device */
	अगर (macsec_is_offloaded(netdev_priv(dev))) अणु
		स्थिर काष्ठा macsec_ops *ops;
		काष्ठा macsec_context ctx;

		ops = macsec_get_ops(netdev_priv(dev), &ctx);
		अगर (!ops) अणु
			ret = -EOPNOTSUPP;
			जाओ cleanup;
		पूर्ण

		ctx.sa.assoc_num = assoc_num;
		ctx.sa.rx_sa = rx_sa;
		ctx.secy = secy;

		ret = macsec_offload(ops->mकरो_upd_rxsa, &ctx);
		अगर (ret)
			जाओ cleanup;
	पूर्ण

	rtnl_unlock();
	वापस 0;

cleanup:
	अगर (tb_sa[MACSEC_SA_ATTR_PN]) अणु
		spin_lock_bh(&rx_sa->lock);
		rx_sa->next_pn_halves = prev_pn;
		spin_unlock_bh(&rx_sa->lock);
	पूर्ण
	rx_sa->active = was_active;
	rtnl_unlock();
	वापस ret;
पूर्ण

अटल पूर्णांक macsec_upd_rxsc(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा nlattr **attrs = info->attrs;
	काष्ठा net_device *dev;
	काष्ठा macsec_secy *secy;
	काष्ठा macsec_rx_sc *rx_sc;
	काष्ठा nlattr *tb_rxsc[MACSEC_RXSC_ATTR_MAX + 1];
	अचिन्हित पूर्णांक prev_n_rx_sc;
	bool was_active;
	पूर्णांक ret;

	अगर (!attrs[MACSEC_ATTR_IFINDEX])
		वापस -EINVAL;

	अगर (parse_rxsc_config(attrs, tb_rxsc))
		वापस -EINVAL;

	अगर (!validate_add_rxsc(tb_rxsc))
		वापस -EINVAL;

	rtnl_lock();
	rx_sc = get_rxsc_from_nl(genl_info_net(info), attrs, tb_rxsc, &dev, &secy);
	अगर (IS_ERR(rx_sc)) अणु
		rtnl_unlock();
		वापस PTR_ERR(rx_sc);
	पूर्ण

	was_active = rx_sc->active;
	prev_n_rx_sc = secy->n_rx_sc;
	अगर (tb_rxsc[MACSEC_RXSC_ATTR_ACTIVE]) अणु
		bool new = !!nla_get_u8(tb_rxsc[MACSEC_RXSC_ATTR_ACTIVE]);

		अगर (rx_sc->active != new)
			secy->n_rx_sc += new ? 1 : -1;

		rx_sc->active = new;
	पूर्ण

	/* If h/w offloading is available, propagate to the device */
	अगर (macsec_is_offloaded(netdev_priv(dev))) अणु
		स्थिर काष्ठा macsec_ops *ops;
		काष्ठा macsec_context ctx;

		ops = macsec_get_ops(netdev_priv(dev), &ctx);
		अगर (!ops) अणु
			ret = -EOPNOTSUPP;
			जाओ cleanup;
		पूर्ण

		ctx.rx_sc = rx_sc;
		ctx.secy = secy;

		ret = macsec_offload(ops->mकरो_upd_rxsc, &ctx);
		अगर (ret)
			जाओ cleanup;
	पूर्ण

	rtnl_unlock();

	वापस 0;

cleanup:
	secy->n_rx_sc = prev_n_rx_sc;
	rx_sc->active = was_active;
	rtnl_unlock();
	वापस ret;
पूर्ण

अटल bool macsec_is_configured(काष्ठा macsec_dev *macsec)
अणु
	काष्ठा macsec_secy *secy = &macsec->secy;
	काष्ठा macsec_tx_sc *tx_sc = &secy->tx_sc;
	पूर्णांक i;

	अगर (secy->n_rx_sc > 0)
		वापस true;

	क्रम (i = 0; i < MACSEC_NUM_AN; i++)
		अगर (tx_sc->sa[i])
			वापस true;

	वापस false;
पूर्ण

अटल पूर्णांक macsec_upd_offload(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा nlattr *tb_offload[MACSEC_OFFLOAD_ATTR_MAX + 1];
	क्रमागत macsec_offload offload, prev_offload;
	पूर्णांक (*func)(काष्ठा macsec_context *ctx);
	काष्ठा nlattr **attrs = info->attrs;
	काष्ठा net_device *dev;
	स्थिर काष्ठा macsec_ops *ops;
	काष्ठा macsec_context ctx;
	काष्ठा macsec_dev *macsec;
	पूर्णांक ret;

	अगर (!attrs[MACSEC_ATTR_IFINDEX])
		वापस -EINVAL;

	अगर (!attrs[MACSEC_ATTR_OFFLOAD])
		वापस -EINVAL;

	अगर (nla_parse_nested_deprecated(tb_offload, MACSEC_OFFLOAD_ATTR_MAX,
					attrs[MACSEC_ATTR_OFFLOAD],
					macsec_genl_offload_policy, शून्य))
		वापस -EINVAL;

	dev = get_dev_from_nl(genl_info_net(info), attrs);
	अगर (IS_ERR(dev))
		वापस PTR_ERR(dev);
	macsec = macsec_priv(dev);

	अगर (!tb_offload[MACSEC_OFFLOAD_ATTR_TYPE])
		वापस -EINVAL;

	offload = nla_get_u8(tb_offload[MACSEC_OFFLOAD_ATTR_TYPE]);
	अगर (macsec->offload == offload)
		वापस 0;

	/* Check अगर the offloading mode is supported by the underlying layers */
	अगर (offload != MACSEC_OFFLOAD_OFF &&
	    !macsec_check_offload(offload, macsec))
		वापस -EOPNOTSUPP;

	/* Check अगर the net device is busy. */
	अगर (netअगर_running(dev))
		वापस -EBUSY;

	rtnl_lock();

	prev_offload = macsec->offload;
	macsec->offload = offload;

	/* Check अगर the device alपढ़ोy has rules configured: we करो not support
	 * rules migration.
	 */
	अगर (macsec_is_configured(macsec)) अणु
		ret = -EBUSY;
		जाओ rollback;
	पूर्ण

	ops = __macsec_get_ops(offload == MACSEC_OFFLOAD_OFF ? prev_offload : offload,
			       macsec, &ctx);
	अगर (!ops) अणु
		ret = -EOPNOTSUPP;
		जाओ rollback;
	पूर्ण

	अगर (prev_offload == MACSEC_OFFLOAD_OFF)
		func = ops->mकरो_add_secy;
	अन्यथा
		func = ops->mकरो_del_secy;

	ctx.secy = &macsec->secy;
	ret = macsec_offload(func, &ctx);
	अगर (ret)
		जाओ rollback;

	/* Force features update, since they are dअगरferent क्रम SW MACSec and
	 * HW offloading हालs.
	 */
	netdev_update_features(dev);

	rtnl_unlock();
	वापस 0;

rollback:
	macsec->offload = prev_offload;

	rtnl_unlock();
	वापस ret;
पूर्ण

अटल व्योम get_tx_sa_stats(काष्ठा net_device *dev, पूर्णांक an,
			    काष्ठा macsec_tx_sa *tx_sa,
			    काष्ठा macsec_tx_sa_stats *sum)
अणु
	काष्ठा macsec_dev *macsec = macsec_priv(dev);
	पूर्णांक cpu;

	/* If h/w offloading is available, propagate to the device */
	अगर (macsec_is_offloaded(macsec)) अणु
		स्थिर काष्ठा macsec_ops *ops;
		काष्ठा macsec_context ctx;

		ops = macsec_get_ops(macsec, &ctx);
		अगर (ops) अणु
			ctx.sa.assoc_num = an;
			ctx.sa.tx_sa = tx_sa;
			ctx.stats.tx_sa_stats = sum;
			ctx.secy = &macsec_priv(dev)->secy;
			macsec_offload(ops->mकरो_get_tx_sa_stats, &ctx);
		पूर्ण
		वापस;
	पूर्ण

	क्रम_each_possible_cpu(cpu) अणु
		स्थिर काष्ठा macsec_tx_sa_stats *stats =
			per_cpu_ptr(tx_sa->stats, cpu);

		sum->OutPktsProtected += stats->OutPktsProtected;
		sum->OutPktsEncrypted += stats->OutPktsEncrypted;
	पूर्ण
पूर्ण

अटल पूर्णांक copy_tx_sa_stats(काष्ठा sk_buff *skb, काष्ठा macsec_tx_sa_stats *sum)
अणु
	अगर (nla_put_u32(skb, MACSEC_SA_STATS_ATTR_OUT_PKTS_PROTECTED,
			sum->OutPktsProtected) ||
	    nla_put_u32(skb, MACSEC_SA_STATS_ATTR_OUT_PKTS_ENCRYPTED,
			sum->OutPktsEncrypted))
		वापस -EMSGSIZE;

	वापस 0;
पूर्ण

अटल व्योम get_rx_sa_stats(काष्ठा net_device *dev,
			    काष्ठा macsec_rx_sc *rx_sc, पूर्णांक an,
			    काष्ठा macsec_rx_sa *rx_sa,
			    काष्ठा macsec_rx_sa_stats *sum)
अणु
	काष्ठा macsec_dev *macsec = macsec_priv(dev);
	पूर्णांक cpu;

	/* If h/w offloading is available, propagate to the device */
	अगर (macsec_is_offloaded(macsec)) अणु
		स्थिर काष्ठा macsec_ops *ops;
		काष्ठा macsec_context ctx;

		ops = macsec_get_ops(macsec, &ctx);
		अगर (ops) अणु
			ctx.sa.assoc_num = an;
			ctx.sa.rx_sa = rx_sa;
			ctx.stats.rx_sa_stats = sum;
			ctx.secy = &macsec_priv(dev)->secy;
			ctx.rx_sc = rx_sc;
			macsec_offload(ops->mकरो_get_rx_sa_stats, &ctx);
		पूर्ण
		वापस;
	पूर्ण

	क्रम_each_possible_cpu(cpu) अणु
		स्थिर काष्ठा macsec_rx_sa_stats *stats =
			per_cpu_ptr(rx_sa->stats, cpu);

		sum->InPktsOK         += stats->InPktsOK;
		sum->InPktsInvalid    += stats->InPktsInvalid;
		sum->InPktsNotValid   += stats->InPktsNotValid;
		sum->InPktsNotUsingSA += stats->InPktsNotUsingSA;
		sum->InPktsUnusedSA   += stats->InPktsUnusedSA;
	पूर्ण
पूर्ण

अटल पूर्णांक copy_rx_sa_stats(काष्ठा sk_buff *skb,
			    काष्ठा macsec_rx_sa_stats *sum)
अणु
	अगर (nla_put_u32(skb, MACSEC_SA_STATS_ATTR_IN_PKTS_OK, sum->InPktsOK) ||
	    nla_put_u32(skb, MACSEC_SA_STATS_ATTR_IN_PKTS_INVALID,
			sum->InPktsInvalid) ||
	    nla_put_u32(skb, MACSEC_SA_STATS_ATTR_IN_PKTS_NOT_VALID,
			sum->InPktsNotValid) ||
	    nla_put_u32(skb, MACSEC_SA_STATS_ATTR_IN_PKTS_NOT_USING_SA,
			sum->InPktsNotUsingSA) ||
	    nla_put_u32(skb, MACSEC_SA_STATS_ATTR_IN_PKTS_UNUSED_SA,
			sum->InPktsUnusedSA))
		वापस -EMSGSIZE;

	वापस 0;
पूर्ण

अटल व्योम get_rx_sc_stats(काष्ठा net_device *dev,
			    काष्ठा macsec_rx_sc *rx_sc,
			    काष्ठा macsec_rx_sc_stats *sum)
अणु
	काष्ठा macsec_dev *macsec = macsec_priv(dev);
	पूर्णांक cpu;

	/* If h/w offloading is available, propagate to the device */
	अगर (macsec_is_offloaded(macsec)) अणु
		स्थिर काष्ठा macsec_ops *ops;
		काष्ठा macsec_context ctx;

		ops = macsec_get_ops(macsec, &ctx);
		अगर (ops) अणु
			ctx.stats.rx_sc_stats = sum;
			ctx.secy = &macsec_priv(dev)->secy;
			ctx.rx_sc = rx_sc;
			macsec_offload(ops->mकरो_get_rx_sc_stats, &ctx);
		पूर्ण
		वापस;
	पूर्ण

	क्रम_each_possible_cpu(cpu) अणु
		स्थिर काष्ठा pcpu_rx_sc_stats *stats;
		काष्ठा macsec_rx_sc_stats पंचांगp;
		अचिन्हित पूर्णांक start;

		stats = per_cpu_ptr(rx_sc->stats, cpu);
		करो अणु
			start = u64_stats_fetch_begin_irq(&stats->syncp);
			स_नकल(&पंचांगp, &stats->stats, माप(पंचांगp));
		पूर्ण जबतक (u64_stats_fetch_retry_irq(&stats->syncp, start));

		sum->InOctetsValidated += पंचांगp.InOctetsValidated;
		sum->InOctetsDecrypted += पंचांगp.InOctetsDecrypted;
		sum->InPktsUnchecked   += पंचांगp.InPktsUnchecked;
		sum->InPktsDelayed     += पंचांगp.InPktsDelayed;
		sum->InPktsOK          += पंचांगp.InPktsOK;
		sum->InPktsInvalid     += पंचांगp.InPktsInvalid;
		sum->InPktsLate        += पंचांगp.InPktsLate;
		sum->InPktsNotValid    += पंचांगp.InPktsNotValid;
		sum->InPktsNotUsingSA  += पंचांगp.InPktsNotUsingSA;
		sum->InPktsUnusedSA    += पंचांगp.InPktsUnusedSA;
	पूर्ण
पूर्ण

अटल पूर्णांक copy_rx_sc_stats(काष्ठा sk_buff *skb, काष्ठा macsec_rx_sc_stats *sum)
अणु
	अगर (nla_put_u64_64bit(skb, MACSEC_RXSC_STATS_ATTR_IN_OCTETS_VALIDATED,
			      sum->InOctetsValidated,
			      MACSEC_RXSC_STATS_ATTR_PAD) ||
	    nla_put_u64_64bit(skb, MACSEC_RXSC_STATS_ATTR_IN_OCTETS_DECRYPTED,
			      sum->InOctetsDecrypted,
			      MACSEC_RXSC_STATS_ATTR_PAD) ||
	    nla_put_u64_64bit(skb, MACSEC_RXSC_STATS_ATTR_IN_PKTS_UNCHECKED,
			      sum->InPktsUnchecked,
			      MACSEC_RXSC_STATS_ATTR_PAD) ||
	    nla_put_u64_64bit(skb, MACSEC_RXSC_STATS_ATTR_IN_PKTS_DELAYED,
			      sum->InPktsDelayed,
			      MACSEC_RXSC_STATS_ATTR_PAD) ||
	    nla_put_u64_64bit(skb, MACSEC_RXSC_STATS_ATTR_IN_PKTS_OK,
			      sum->InPktsOK,
			      MACSEC_RXSC_STATS_ATTR_PAD) ||
	    nla_put_u64_64bit(skb, MACSEC_RXSC_STATS_ATTR_IN_PKTS_INVALID,
			      sum->InPktsInvalid,
			      MACSEC_RXSC_STATS_ATTR_PAD) ||
	    nla_put_u64_64bit(skb, MACSEC_RXSC_STATS_ATTR_IN_PKTS_LATE,
			      sum->InPktsLate,
			      MACSEC_RXSC_STATS_ATTR_PAD) ||
	    nla_put_u64_64bit(skb, MACSEC_RXSC_STATS_ATTR_IN_PKTS_NOT_VALID,
			      sum->InPktsNotValid,
			      MACSEC_RXSC_STATS_ATTR_PAD) ||
	    nla_put_u64_64bit(skb, MACSEC_RXSC_STATS_ATTR_IN_PKTS_NOT_USING_SA,
			      sum->InPktsNotUsingSA,
			      MACSEC_RXSC_STATS_ATTR_PAD) ||
	    nla_put_u64_64bit(skb, MACSEC_RXSC_STATS_ATTR_IN_PKTS_UNUSED_SA,
			      sum->InPktsUnusedSA,
			      MACSEC_RXSC_STATS_ATTR_PAD))
		वापस -EMSGSIZE;

	वापस 0;
पूर्ण

अटल व्योम get_tx_sc_stats(काष्ठा net_device *dev,
			    काष्ठा macsec_tx_sc_stats *sum)
अणु
	काष्ठा macsec_dev *macsec = macsec_priv(dev);
	पूर्णांक cpu;

	/* If h/w offloading is available, propagate to the device */
	अगर (macsec_is_offloaded(macsec)) अणु
		स्थिर काष्ठा macsec_ops *ops;
		काष्ठा macsec_context ctx;

		ops = macsec_get_ops(macsec, &ctx);
		अगर (ops) अणु
			ctx.stats.tx_sc_stats = sum;
			ctx.secy = &macsec_priv(dev)->secy;
			macsec_offload(ops->mकरो_get_tx_sc_stats, &ctx);
		पूर्ण
		वापस;
	पूर्ण

	क्रम_each_possible_cpu(cpu) अणु
		स्थिर काष्ठा pcpu_tx_sc_stats *stats;
		काष्ठा macsec_tx_sc_stats पंचांगp;
		अचिन्हित पूर्णांक start;

		stats = per_cpu_ptr(macsec_priv(dev)->secy.tx_sc.stats, cpu);
		करो अणु
			start = u64_stats_fetch_begin_irq(&stats->syncp);
			स_नकल(&पंचांगp, &stats->stats, माप(पंचांगp));
		पूर्ण जबतक (u64_stats_fetch_retry_irq(&stats->syncp, start));

		sum->OutPktsProtected   += पंचांगp.OutPktsProtected;
		sum->OutPktsEncrypted   += पंचांगp.OutPktsEncrypted;
		sum->OutOctetsProtected += पंचांगp.OutOctetsProtected;
		sum->OutOctetsEncrypted += पंचांगp.OutOctetsEncrypted;
	पूर्ण
पूर्ण

अटल पूर्णांक copy_tx_sc_stats(काष्ठा sk_buff *skb, काष्ठा macsec_tx_sc_stats *sum)
अणु
	अगर (nla_put_u64_64bit(skb, MACSEC_TXSC_STATS_ATTR_OUT_PKTS_PROTECTED,
			      sum->OutPktsProtected,
			      MACSEC_TXSC_STATS_ATTR_PAD) ||
	    nla_put_u64_64bit(skb, MACSEC_TXSC_STATS_ATTR_OUT_PKTS_ENCRYPTED,
			      sum->OutPktsEncrypted,
			      MACSEC_TXSC_STATS_ATTR_PAD) ||
	    nla_put_u64_64bit(skb, MACSEC_TXSC_STATS_ATTR_OUT_OCTETS_PROTECTED,
			      sum->OutOctetsProtected,
			      MACSEC_TXSC_STATS_ATTR_PAD) ||
	    nla_put_u64_64bit(skb, MACSEC_TXSC_STATS_ATTR_OUT_OCTETS_ENCRYPTED,
			      sum->OutOctetsEncrypted,
			      MACSEC_TXSC_STATS_ATTR_PAD))
		वापस -EMSGSIZE;

	वापस 0;
पूर्ण

अटल व्योम get_secy_stats(काष्ठा net_device *dev, काष्ठा macsec_dev_stats *sum)
अणु
	काष्ठा macsec_dev *macsec = macsec_priv(dev);
	पूर्णांक cpu;

	/* If h/w offloading is available, propagate to the device */
	अगर (macsec_is_offloaded(macsec)) अणु
		स्थिर काष्ठा macsec_ops *ops;
		काष्ठा macsec_context ctx;

		ops = macsec_get_ops(macsec, &ctx);
		अगर (ops) अणु
			ctx.stats.dev_stats = sum;
			ctx.secy = &macsec_priv(dev)->secy;
			macsec_offload(ops->mकरो_get_dev_stats, &ctx);
		पूर्ण
		वापस;
	पूर्ण

	क्रम_each_possible_cpu(cpu) अणु
		स्थिर काष्ठा pcpu_secy_stats *stats;
		काष्ठा macsec_dev_stats पंचांगp;
		अचिन्हित पूर्णांक start;

		stats = per_cpu_ptr(macsec_priv(dev)->stats, cpu);
		करो अणु
			start = u64_stats_fetch_begin_irq(&stats->syncp);
			स_नकल(&पंचांगp, &stats->stats, माप(पंचांगp));
		पूर्ण जबतक (u64_stats_fetch_retry_irq(&stats->syncp, start));

		sum->OutPktsUntagged  += पंचांगp.OutPktsUntagged;
		sum->InPktsUntagged   += पंचांगp.InPktsUntagged;
		sum->OutPktsTooLong   += पंचांगp.OutPktsTooLong;
		sum->InPktsNoTag      += पंचांगp.InPktsNoTag;
		sum->InPktsBadTag     += पंचांगp.InPktsBadTag;
		sum->InPktsUnknownSCI += पंचांगp.InPktsUnknownSCI;
		sum->InPktsNoSCI      += पंचांगp.InPktsNoSCI;
		sum->InPktsOverrun    += पंचांगp.InPktsOverrun;
	पूर्ण
पूर्ण

अटल पूर्णांक copy_secy_stats(काष्ठा sk_buff *skb, काष्ठा macsec_dev_stats *sum)
अणु
	अगर (nla_put_u64_64bit(skb, MACSEC_SECY_STATS_ATTR_OUT_PKTS_UNTAGGED,
			      sum->OutPktsUntagged,
			      MACSEC_SECY_STATS_ATTR_PAD) ||
	    nla_put_u64_64bit(skb, MACSEC_SECY_STATS_ATTR_IN_PKTS_UNTAGGED,
			      sum->InPktsUntagged,
			      MACSEC_SECY_STATS_ATTR_PAD) ||
	    nla_put_u64_64bit(skb, MACSEC_SECY_STATS_ATTR_OUT_PKTS_TOO_LONG,
			      sum->OutPktsTooLong,
			      MACSEC_SECY_STATS_ATTR_PAD) ||
	    nla_put_u64_64bit(skb, MACSEC_SECY_STATS_ATTR_IN_PKTS_NO_TAG,
			      sum->InPktsNoTag,
			      MACSEC_SECY_STATS_ATTR_PAD) ||
	    nla_put_u64_64bit(skb, MACSEC_SECY_STATS_ATTR_IN_PKTS_BAD_TAG,
			      sum->InPktsBadTag,
			      MACSEC_SECY_STATS_ATTR_PAD) ||
	    nla_put_u64_64bit(skb, MACSEC_SECY_STATS_ATTR_IN_PKTS_UNKNOWN_SCI,
			      sum->InPktsUnknownSCI,
			      MACSEC_SECY_STATS_ATTR_PAD) ||
	    nla_put_u64_64bit(skb, MACSEC_SECY_STATS_ATTR_IN_PKTS_NO_SCI,
			      sum->InPktsNoSCI,
			      MACSEC_SECY_STATS_ATTR_PAD) ||
	    nla_put_u64_64bit(skb, MACSEC_SECY_STATS_ATTR_IN_PKTS_OVERRUN,
			      sum->InPktsOverrun,
			      MACSEC_SECY_STATS_ATTR_PAD))
		वापस -EMSGSIZE;

	वापस 0;
पूर्ण

अटल पूर्णांक nla_put_secy(काष्ठा macsec_secy *secy, काष्ठा sk_buff *skb)
अणु
	काष्ठा macsec_tx_sc *tx_sc = &secy->tx_sc;
	काष्ठा nlattr *secy_nest = nla_nest_start_noflag(skb,
							 MACSEC_ATTR_SECY);
	u64 csid;

	अगर (!secy_nest)
		वापस 1;

	चयन (secy->key_len) अणु
	हाल MACSEC_GCM_AES_128_SAK_LEN:
		csid = secy->xpn ? MACSEC_CIPHER_ID_GCM_AES_XPN_128 : MACSEC_DEFAULT_CIPHER_ID;
		अवरोध;
	हाल MACSEC_GCM_AES_256_SAK_LEN:
		csid = secy->xpn ? MACSEC_CIPHER_ID_GCM_AES_XPN_256 : MACSEC_CIPHER_ID_GCM_AES_256;
		अवरोध;
	शेष:
		जाओ cancel;
	पूर्ण

	अगर (nla_put_sci(skb, MACSEC_SECY_ATTR_SCI, secy->sci,
			MACSEC_SECY_ATTR_PAD) ||
	    nla_put_u64_64bit(skb, MACSEC_SECY_ATTR_CIPHER_SUITE,
			      csid, MACSEC_SECY_ATTR_PAD) ||
	    nla_put_u8(skb, MACSEC_SECY_ATTR_ICV_LEN, secy->icv_len) ||
	    nla_put_u8(skb, MACSEC_SECY_ATTR_OPER, secy->operational) ||
	    nla_put_u8(skb, MACSEC_SECY_ATTR_PROTECT, secy->protect_frames) ||
	    nla_put_u8(skb, MACSEC_SECY_ATTR_REPLAY, secy->replay_protect) ||
	    nla_put_u8(skb, MACSEC_SECY_ATTR_VALIDATE, secy->validate_frames) ||
	    nla_put_u8(skb, MACSEC_SECY_ATTR_ENCRYPT, tx_sc->encrypt) ||
	    nla_put_u8(skb, MACSEC_SECY_ATTR_INC_SCI, tx_sc->send_sci) ||
	    nla_put_u8(skb, MACSEC_SECY_ATTR_ES, tx_sc->end_station) ||
	    nla_put_u8(skb, MACSEC_SECY_ATTR_SCB, tx_sc->scb) ||
	    nla_put_u8(skb, MACSEC_SECY_ATTR_ENCODING_SA, tx_sc->encoding_sa))
		जाओ cancel;

	अगर (secy->replay_protect) अणु
		अगर (nla_put_u32(skb, MACSEC_SECY_ATTR_WINDOW, secy->replay_winकरोw))
			जाओ cancel;
	पूर्ण

	nla_nest_end(skb, secy_nest);
	वापस 0;

cancel:
	nla_nest_cancel(skb, secy_nest);
	वापस 1;
पूर्ण

अटल noअंतरभूत_क्रम_stack पूर्णांक
dump_secy(काष्ठा macsec_secy *secy, काष्ठा net_device *dev,
	  काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb)
अणु
	काष्ठा macsec_tx_sc_stats tx_sc_stats = अणु0, पूर्ण;
	काष्ठा macsec_tx_sa_stats tx_sa_stats = अणु0, पूर्ण;
	काष्ठा macsec_rx_sc_stats rx_sc_stats = अणु0, पूर्ण;
	काष्ठा macsec_rx_sa_stats rx_sa_stats = अणु0, पूर्ण;
	काष्ठा macsec_dev *macsec = netdev_priv(dev);
	काष्ठा macsec_dev_stats dev_stats = अणु0, पूर्ण;
	काष्ठा macsec_tx_sc *tx_sc = &secy->tx_sc;
	काष्ठा nlattr *txsa_list, *rxsc_list;
	काष्ठा macsec_rx_sc *rx_sc;
	काष्ठा nlattr *attr;
	व्योम *hdr;
	पूर्णांक i, j;

	hdr = genlmsg_put(skb, NETLINK_CB(cb->skb).portid, cb->nlh->nlmsg_seq,
			  &macsec_fam, NLM_F_MULTI, MACSEC_CMD_GET_TXSC);
	अगर (!hdr)
		वापस -EMSGSIZE;

	genl_dump_check_consistent(cb, hdr);

	अगर (nla_put_u32(skb, MACSEC_ATTR_IFINDEX, dev->अगरindex))
		जाओ nla_put_failure;

	attr = nla_nest_start_noflag(skb, MACSEC_ATTR_OFFLOAD);
	अगर (!attr)
		जाओ nla_put_failure;
	अगर (nla_put_u8(skb, MACSEC_OFFLOAD_ATTR_TYPE, macsec->offload))
		जाओ nla_put_failure;
	nla_nest_end(skb, attr);

	अगर (nla_put_secy(secy, skb))
		जाओ nla_put_failure;

	attr = nla_nest_start_noflag(skb, MACSEC_ATTR_TXSC_STATS);
	अगर (!attr)
		जाओ nla_put_failure;

	get_tx_sc_stats(dev, &tx_sc_stats);
	अगर (copy_tx_sc_stats(skb, &tx_sc_stats)) अणु
		nla_nest_cancel(skb, attr);
		जाओ nla_put_failure;
	पूर्ण
	nla_nest_end(skb, attr);

	attr = nla_nest_start_noflag(skb, MACSEC_ATTR_SECY_STATS);
	अगर (!attr)
		जाओ nla_put_failure;
	get_secy_stats(dev, &dev_stats);
	अगर (copy_secy_stats(skb, &dev_stats)) अणु
		nla_nest_cancel(skb, attr);
		जाओ nla_put_failure;
	पूर्ण
	nla_nest_end(skb, attr);

	txsa_list = nla_nest_start_noflag(skb, MACSEC_ATTR_TXSA_LIST);
	अगर (!txsa_list)
		जाओ nla_put_failure;
	क्रम (i = 0, j = 1; i < MACSEC_NUM_AN; i++) अणु
		काष्ठा macsec_tx_sa *tx_sa = rtnl_dereference(tx_sc->sa[i]);
		काष्ठा nlattr *txsa_nest;
		u64 pn;
		पूर्णांक pn_len;

		अगर (!tx_sa)
			जारी;

		txsa_nest = nla_nest_start_noflag(skb, j++);
		अगर (!txsa_nest) अणु
			nla_nest_cancel(skb, txsa_list);
			जाओ nla_put_failure;
		पूर्ण

		attr = nla_nest_start_noflag(skb, MACSEC_SA_ATTR_STATS);
		अगर (!attr) अणु
			nla_nest_cancel(skb, txsa_nest);
			nla_nest_cancel(skb, txsa_list);
			जाओ nla_put_failure;
		पूर्ण
		स_रखो(&tx_sa_stats, 0, माप(tx_sa_stats));
		get_tx_sa_stats(dev, i, tx_sa, &tx_sa_stats);
		अगर (copy_tx_sa_stats(skb, &tx_sa_stats)) अणु
			nla_nest_cancel(skb, attr);
			nla_nest_cancel(skb, txsa_nest);
			nla_nest_cancel(skb, txsa_list);
			जाओ nla_put_failure;
		पूर्ण
		nla_nest_end(skb, attr);

		अगर (secy->xpn) अणु
			pn = tx_sa->next_pn;
			pn_len = MACSEC_XPN_PN_LEN;
		पूर्ण अन्यथा अणु
			pn = tx_sa->next_pn_halves.lower;
			pn_len = MACSEC_DEFAULT_PN_LEN;
		पूर्ण

		अगर (nla_put_u8(skb, MACSEC_SA_ATTR_AN, i) ||
		    nla_put(skb, MACSEC_SA_ATTR_PN, pn_len, &pn) ||
		    nla_put(skb, MACSEC_SA_ATTR_KEYID, MACSEC_KEYID_LEN, tx_sa->key.id) ||
		    (secy->xpn && nla_put_ssci(skb, MACSEC_SA_ATTR_SSCI, tx_sa->ssci)) ||
		    nla_put_u8(skb, MACSEC_SA_ATTR_ACTIVE, tx_sa->active)) अणु
			nla_nest_cancel(skb, txsa_nest);
			nla_nest_cancel(skb, txsa_list);
			जाओ nla_put_failure;
		पूर्ण

		nla_nest_end(skb, txsa_nest);
	पूर्ण
	nla_nest_end(skb, txsa_list);

	rxsc_list = nla_nest_start_noflag(skb, MACSEC_ATTR_RXSC_LIST);
	अगर (!rxsc_list)
		जाओ nla_put_failure;

	j = 1;
	क्रम_each_rxsc_rtnl(secy, rx_sc) अणु
		पूर्णांक k;
		काष्ठा nlattr *rxsa_list;
		काष्ठा nlattr *rxsc_nest = nla_nest_start_noflag(skb, j++);

		अगर (!rxsc_nest) अणु
			nla_nest_cancel(skb, rxsc_list);
			जाओ nla_put_failure;
		पूर्ण

		अगर (nla_put_u8(skb, MACSEC_RXSC_ATTR_ACTIVE, rx_sc->active) ||
		    nla_put_sci(skb, MACSEC_RXSC_ATTR_SCI, rx_sc->sci,
				MACSEC_RXSC_ATTR_PAD)) अणु
			nla_nest_cancel(skb, rxsc_nest);
			nla_nest_cancel(skb, rxsc_list);
			जाओ nla_put_failure;
		पूर्ण

		attr = nla_nest_start_noflag(skb, MACSEC_RXSC_ATTR_STATS);
		अगर (!attr) अणु
			nla_nest_cancel(skb, rxsc_nest);
			nla_nest_cancel(skb, rxsc_list);
			जाओ nla_put_failure;
		पूर्ण
		स_रखो(&rx_sc_stats, 0, माप(rx_sc_stats));
		get_rx_sc_stats(dev, rx_sc, &rx_sc_stats);
		अगर (copy_rx_sc_stats(skb, &rx_sc_stats)) अणु
			nla_nest_cancel(skb, attr);
			nla_nest_cancel(skb, rxsc_nest);
			nla_nest_cancel(skb, rxsc_list);
			जाओ nla_put_failure;
		पूर्ण
		nla_nest_end(skb, attr);

		rxsa_list = nla_nest_start_noflag(skb,
						  MACSEC_RXSC_ATTR_SA_LIST);
		अगर (!rxsa_list) अणु
			nla_nest_cancel(skb, rxsc_nest);
			nla_nest_cancel(skb, rxsc_list);
			जाओ nla_put_failure;
		पूर्ण

		क्रम (i = 0, k = 1; i < MACSEC_NUM_AN; i++) अणु
			काष्ठा macsec_rx_sa *rx_sa = rtnl_dereference(rx_sc->sa[i]);
			काष्ठा nlattr *rxsa_nest;
			u64 pn;
			पूर्णांक pn_len;

			अगर (!rx_sa)
				जारी;

			rxsa_nest = nla_nest_start_noflag(skb, k++);
			अगर (!rxsa_nest) अणु
				nla_nest_cancel(skb, rxsa_list);
				nla_nest_cancel(skb, rxsc_nest);
				nla_nest_cancel(skb, rxsc_list);
				जाओ nla_put_failure;
			पूर्ण

			attr = nla_nest_start_noflag(skb,
						     MACSEC_SA_ATTR_STATS);
			अगर (!attr) अणु
				nla_nest_cancel(skb, rxsa_list);
				nla_nest_cancel(skb, rxsc_nest);
				nla_nest_cancel(skb, rxsc_list);
				जाओ nla_put_failure;
			पूर्ण
			स_रखो(&rx_sa_stats, 0, माप(rx_sa_stats));
			get_rx_sa_stats(dev, rx_sc, i, rx_sa, &rx_sa_stats);
			अगर (copy_rx_sa_stats(skb, &rx_sa_stats)) अणु
				nla_nest_cancel(skb, attr);
				nla_nest_cancel(skb, rxsa_list);
				nla_nest_cancel(skb, rxsc_nest);
				nla_nest_cancel(skb, rxsc_list);
				जाओ nla_put_failure;
			पूर्ण
			nla_nest_end(skb, attr);

			अगर (secy->xpn) अणु
				pn = rx_sa->next_pn;
				pn_len = MACSEC_XPN_PN_LEN;
			पूर्ण अन्यथा अणु
				pn = rx_sa->next_pn_halves.lower;
				pn_len = MACSEC_DEFAULT_PN_LEN;
			पूर्ण

			अगर (nla_put_u8(skb, MACSEC_SA_ATTR_AN, i) ||
			    nla_put(skb, MACSEC_SA_ATTR_PN, pn_len, &pn) ||
			    nla_put(skb, MACSEC_SA_ATTR_KEYID, MACSEC_KEYID_LEN, rx_sa->key.id) ||
			    (secy->xpn && nla_put_ssci(skb, MACSEC_SA_ATTR_SSCI, rx_sa->ssci)) ||
			    nla_put_u8(skb, MACSEC_SA_ATTR_ACTIVE, rx_sa->active)) अणु
				nla_nest_cancel(skb, rxsa_nest);
				nla_nest_cancel(skb, rxsc_nest);
				nla_nest_cancel(skb, rxsc_list);
				जाओ nla_put_failure;
			पूर्ण
			nla_nest_end(skb, rxsa_nest);
		पूर्ण

		nla_nest_end(skb, rxsa_list);
		nla_nest_end(skb, rxsc_nest);
	पूर्ण

	nla_nest_end(skb, rxsc_list);

	genlmsg_end(skb, hdr);

	वापस 0;

nla_put_failure:
	genlmsg_cancel(skb, hdr);
	वापस -EMSGSIZE;
पूर्ण

अटल पूर्णांक macsec_generation = 1; /* रक्षित by RTNL */

अटल पूर्णांक macsec_dump_txsc(काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb)
अणु
	काष्ठा net *net = sock_net(skb->sk);
	काष्ठा net_device *dev;
	पूर्णांक dev_idx, d;

	dev_idx = cb->args[0];

	d = 0;
	rtnl_lock();

	cb->seq = macsec_generation;

	क्रम_each_netdev(net, dev) अणु
		काष्ठा macsec_secy *secy;

		अगर (d < dev_idx)
			जाओ next;

		अगर (!netअगर_is_macsec(dev))
			जाओ next;

		secy = &macsec_priv(dev)->secy;
		अगर (dump_secy(secy, dev, skb, cb) < 0)
			जाओ करोne;
next:
		d++;
	पूर्ण

करोne:
	rtnl_unlock();
	cb->args[0] = d;
	वापस skb->len;
पूर्ण

अटल स्थिर काष्ठा genl_small_ops macsec_genl_ops[] = अणु
	अणु
		.cmd = MACSEC_CMD_GET_TXSC,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.dumpit = macsec_dump_txsc,
	पूर्ण,
	अणु
		.cmd = MACSEC_CMD_ADD_RXSC,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = macsec_add_rxsc,
		.flags = GENL_ADMIN_PERM,
	पूर्ण,
	अणु
		.cmd = MACSEC_CMD_DEL_RXSC,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = macsec_del_rxsc,
		.flags = GENL_ADMIN_PERM,
	पूर्ण,
	अणु
		.cmd = MACSEC_CMD_UPD_RXSC,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = macsec_upd_rxsc,
		.flags = GENL_ADMIN_PERM,
	पूर्ण,
	अणु
		.cmd = MACSEC_CMD_ADD_TXSA,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = macsec_add_txsa,
		.flags = GENL_ADMIN_PERM,
	पूर्ण,
	अणु
		.cmd = MACSEC_CMD_DEL_TXSA,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = macsec_del_txsa,
		.flags = GENL_ADMIN_PERM,
	पूर्ण,
	अणु
		.cmd = MACSEC_CMD_UPD_TXSA,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = macsec_upd_txsa,
		.flags = GENL_ADMIN_PERM,
	पूर्ण,
	अणु
		.cmd = MACSEC_CMD_ADD_RXSA,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = macsec_add_rxsa,
		.flags = GENL_ADMIN_PERM,
	पूर्ण,
	अणु
		.cmd = MACSEC_CMD_DEL_RXSA,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = macsec_del_rxsa,
		.flags = GENL_ADMIN_PERM,
	पूर्ण,
	अणु
		.cmd = MACSEC_CMD_UPD_RXSA,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = macsec_upd_rxsa,
		.flags = GENL_ADMIN_PERM,
	पूर्ण,
	अणु
		.cmd = MACSEC_CMD_UPD_OFFLOAD,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = macsec_upd_offload,
		.flags = GENL_ADMIN_PERM,
	पूर्ण,
पूर्ण;

अटल काष्ठा genl_family macsec_fam __ro_after_init = अणु
	.name		= MACSEC_GENL_NAME,
	.hdrsize	= 0,
	.version	= MACSEC_GENL_VERSION,
	.maxattr	= MACSEC_ATTR_MAX,
	.policy = macsec_genl_policy,
	.netnsok	= true,
	.module		= THIS_MODULE,
	.small_ops	= macsec_genl_ops,
	.n_small_ops	= ARRAY_SIZE(macsec_genl_ops),
पूर्ण;

अटल netdev_tx_t macsec_start_xmit(काष्ठा sk_buff *skb,
				     काष्ठा net_device *dev)
अणु
	काष्ठा macsec_dev *macsec = netdev_priv(dev);
	काष्ठा macsec_secy *secy = &macsec->secy;
	काष्ठा pcpu_secy_stats *secy_stats;
	पूर्णांक ret, len;

	अगर (macsec_is_offloaded(netdev_priv(dev))) अणु
		skb->dev = macsec->real_dev;
		वापस dev_queue_xmit(skb);
	पूर्ण

	/* 10.5 */
	अगर (!secy->protect_frames) अणु
		secy_stats = this_cpu_ptr(macsec->stats);
		u64_stats_update_begin(&secy_stats->syncp);
		secy_stats->stats.OutPktsUntagged++;
		u64_stats_update_end(&secy_stats->syncp);
		skb->dev = macsec->real_dev;
		len = skb->len;
		ret = dev_queue_xmit(skb);
		count_tx(dev, ret, len);
		वापस ret;
	पूर्ण

	अगर (!secy->operational) अणु
		kमुक्त_skb(skb);
		dev->stats.tx_dropped++;
		वापस NETDEV_TX_OK;
	पूर्ण

	skb = macsec_encrypt(skb, dev);
	अगर (IS_ERR(skb)) अणु
		अगर (PTR_ERR(skb) != -EINPROGRESS)
			dev->stats.tx_dropped++;
		वापस NETDEV_TX_OK;
	पूर्ण

	macsec_count_tx(skb, &macsec->secy.tx_sc, macsec_skb_cb(skb)->tx_sa);

	macsec_encrypt_finish(skb, dev);
	len = skb->len;
	ret = dev_queue_xmit(skb);
	count_tx(dev, ret, len);
	वापस ret;
पूर्ण

#घोषणा SW_MACSEC_FEATURES \
	(NETIF_F_SG | NETIF_F_HIGHDMA | NETIF_F_FRAGLIST)

/* If h/w offloading is enabled, use real device features save क्रम
 *   VLAN_FEATURES - they require additional ops
 *   HW_MACSEC - no reason to report it
 */
#घोषणा REAL_DEV_FEATURES(dev) \
	((dev)->features & ~(NETIF_F_VLAN_FEATURES | NETIF_F_HW_MACSEC))

अटल पूर्णांक macsec_dev_init(काष्ठा net_device *dev)
अणु
	काष्ठा macsec_dev *macsec = macsec_priv(dev);
	काष्ठा net_device *real_dev = macsec->real_dev;
	पूर्णांक err;

	dev->tstats = netdev_alloc_pcpu_stats(काष्ठा pcpu_sw_netstats);
	अगर (!dev->tstats)
		वापस -ENOMEM;

	err = gro_cells_init(&macsec->gro_cells, dev);
	अगर (err) अणु
		मुक्त_percpu(dev->tstats);
		वापस err;
	पूर्ण

	अगर (macsec_is_offloaded(macsec)) अणु
		dev->features = REAL_DEV_FEATURES(real_dev);
	पूर्ण अन्यथा अणु
		dev->features = real_dev->features & SW_MACSEC_FEATURES;
		dev->features |= NETIF_F_LLTX | NETIF_F_GSO_SOFTWARE;
	पूर्ण

	dev->needed_headroom = real_dev->needed_headroom +
			       MACSEC_NEEDED_HEADROOM;
	dev->needed_tailroom = real_dev->needed_tailroom +
			       MACSEC_NEEDED_TAILROOM;

	अगर (is_zero_ether_addr(dev->dev_addr))
		eth_hw_addr_inherit(dev, real_dev);
	अगर (is_zero_ether_addr(dev->broadcast))
		स_नकल(dev->broadcast, real_dev->broadcast, dev->addr_len);

	वापस 0;
पूर्ण

अटल व्योम macsec_dev_uninit(काष्ठा net_device *dev)
अणु
	काष्ठा macsec_dev *macsec = macsec_priv(dev);

	gro_cells_destroy(&macsec->gro_cells);
	मुक्त_percpu(dev->tstats);
पूर्ण

अटल netdev_features_t macsec_fix_features(काष्ठा net_device *dev,
					     netdev_features_t features)
अणु
	काष्ठा macsec_dev *macsec = macsec_priv(dev);
	काष्ठा net_device *real_dev = macsec->real_dev;

	अगर (macsec_is_offloaded(macsec))
		वापस REAL_DEV_FEATURES(real_dev);

	features &= (real_dev->features & SW_MACSEC_FEATURES) |
		    NETIF_F_GSO_SOFTWARE | NETIF_F_SOFT_FEATURES;
	features |= NETIF_F_LLTX;

	वापस features;
पूर्ण

अटल पूर्णांक macsec_dev_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा macsec_dev *macsec = macsec_priv(dev);
	काष्ठा net_device *real_dev = macsec->real_dev;
	पूर्णांक err;

	err = dev_uc_add(real_dev, dev->dev_addr);
	अगर (err < 0)
		वापस err;

	अगर (dev->flags & IFF_ALLMULTI) अणु
		err = dev_set_allmulti(real_dev, 1);
		अगर (err < 0)
			जाओ del_unicast;
	पूर्ण

	अगर (dev->flags & IFF_PROMISC) अणु
		err = dev_set_promiscuity(real_dev, 1);
		अगर (err < 0)
			जाओ clear_allmulti;
	पूर्ण

	/* If h/w offloading is available, propagate to the device */
	अगर (macsec_is_offloaded(macsec)) अणु
		स्थिर काष्ठा macsec_ops *ops;
		काष्ठा macsec_context ctx;

		ops = macsec_get_ops(netdev_priv(dev), &ctx);
		अगर (!ops) अणु
			err = -EOPNOTSUPP;
			जाओ clear_allmulti;
		पूर्ण

		ctx.secy = &macsec->secy;
		err = macsec_offload(ops->mकरो_dev_खोलो, &ctx);
		अगर (err)
			जाओ clear_allmulti;
	पूर्ण

	अगर (netअगर_carrier_ok(real_dev))
		netअगर_carrier_on(dev);

	वापस 0;
clear_allmulti:
	अगर (dev->flags & IFF_ALLMULTI)
		dev_set_allmulti(real_dev, -1);
del_unicast:
	dev_uc_del(real_dev, dev->dev_addr);
	netअगर_carrier_off(dev);
	वापस err;
पूर्ण

अटल पूर्णांक macsec_dev_stop(काष्ठा net_device *dev)
अणु
	काष्ठा macsec_dev *macsec = macsec_priv(dev);
	काष्ठा net_device *real_dev = macsec->real_dev;

	netअगर_carrier_off(dev);

	/* If h/w offloading is available, propagate to the device */
	अगर (macsec_is_offloaded(macsec)) अणु
		स्थिर काष्ठा macsec_ops *ops;
		काष्ठा macsec_context ctx;

		ops = macsec_get_ops(macsec, &ctx);
		अगर (ops) अणु
			ctx.secy = &macsec->secy;
			macsec_offload(ops->mकरो_dev_stop, &ctx);
		पूर्ण
	पूर्ण

	dev_mc_unsync(real_dev, dev);
	dev_uc_unsync(real_dev, dev);

	अगर (dev->flags & IFF_ALLMULTI)
		dev_set_allmulti(real_dev, -1);

	अगर (dev->flags & IFF_PROMISC)
		dev_set_promiscuity(real_dev, -1);

	dev_uc_del(real_dev, dev->dev_addr);

	वापस 0;
पूर्ण

अटल व्योम macsec_dev_change_rx_flags(काष्ठा net_device *dev, पूर्णांक change)
अणु
	काष्ठा net_device *real_dev = macsec_priv(dev)->real_dev;

	अगर (!(dev->flags & IFF_UP))
		वापस;

	अगर (change & IFF_ALLMULTI)
		dev_set_allmulti(real_dev, dev->flags & IFF_ALLMULTI ? 1 : -1);

	अगर (change & IFF_PROMISC)
		dev_set_promiscuity(real_dev,
				    dev->flags & IFF_PROMISC ? 1 : -1);
पूर्ण

अटल व्योम macsec_dev_set_rx_mode(काष्ठा net_device *dev)
अणु
	काष्ठा net_device *real_dev = macsec_priv(dev)->real_dev;

	dev_mc_sync(real_dev, dev);
	dev_uc_sync(real_dev, dev);
पूर्ण

अटल पूर्णांक macsec_set_mac_address(काष्ठा net_device *dev, व्योम *p)
अणु
	काष्ठा macsec_dev *macsec = macsec_priv(dev);
	काष्ठा net_device *real_dev = macsec->real_dev;
	काष्ठा sockaddr *addr = p;
	पूर्णांक err;

	अगर (!is_valid_ether_addr(addr->sa_data))
		वापस -EADDRNOTAVAIL;

	अगर (!(dev->flags & IFF_UP))
		जाओ out;

	err = dev_uc_add(real_dev, addr->sa_data);
	अगर (err < 0)
		वापस err;

	dev_uc_del(real_dev, dev->dev_addr);

out:
	ether_addr_copy(dev->dev_addr, addr->sa_data);
	macsec->secy.sci = dev_to_sci(dev, MACSEC_PORT_ES);

	/* If h/w offloading is available, propagate to the device */
	अगर (macsec_is_offloaded(macsec)) अणु
		स्थिर काष्ठा macsec_ops *ops;
		काष्ठा macsec_context ctx;

		ops = macsec_get_ops(macsec, &ctx);
		अगर (ops) अणु
			ctx.secy = &macsec->secy;
			macsec_offload(ops->mकरो_upd_secy, &ctx);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक macsec_change_mtu(काष्ठा net_device *dev, पूर्णांक new_mtu)
अणु
	काष्ठा macsec_dev *macsec = macsec_priv(dev);
	अचिन्हित पूर्णांक extra = macsec->secy.icv_len + macsec_extra_len(true);

	अगर (macsec->real_dev->mtu - extra < new_mtu)
		वापस -दुस्फल;

	dev->mtu = new_mtu;

	वापस 0;
पूर्ण

अटल व्योम macsec_get_stats64(काष्ठा net_device *dev,
			       काष्ठा rtnl_link_stats64 *s)
अणु
	अगर (!dev->tstats)
		वापस;

	dev_fetch_sw_netstats(s, dev->tstats);

	s->rx_dropped = dev->stats.rx_dropped;
	s->tx_dropped = dev->stats.tx_dropped;
पूर्ण

अटल पूर्णांक macsec_get_अगरlink(स्थिर काष्ठा net_device *dev)
अणु
	वापस macsec_priv(dev)->real_dev->अगरindex;
पूर्ण

अटल स्थिर काष्ठा net_device_ops macsec_netdev_ops = अणु
	.nकरो_init		= macsec_dev_init,
	.nकरो_uninit		= macsec_dev_uninit,
	.nकरो_खोलो		= macsec_dev_खोलो,
	.nकरो_stop		= macsec_dev_stop,
	.nकरो_fix_features	= macsec_fix_features,
	.nकरो_change_mtu		= macsec_change_mtu,
	.nकरो_set_rx_mode	= macsec_dev_set_rx_mode,
	.nकरो_change_rx_flags	= macsec_dev_change_rx_flags,
	.nकरो_set_mac_address	= macsec_set_mac_address,
	.nकरो_start_xmit		= macsec_start_xmit,
	.nकरो_get_stats64	= macsec_get_stats64,
	.nकरो_get_अगरlink		= macsec_get_अगरlink,
पूर्ण;

अटल स्थिर काष्ठा device_type macsec_type = अणु
	.name = "macsec",
पूर्ण;

अटल स्थिर काष्ठा nla_policy macsec_rtnl_policy[IFLA_MACSEC_MAX + 1] = अणु
	[IFLA_MACSEC_SCI] = अणु .type = NLA_U64 पूर्ण,
	[IFLA_MACSEC_PORT] = अणु .type = NLA_U16 पूर्ण,
	[IFLA_MACSEC_ICV_LEN] = अणु .type = NLA_U8 पूर्ण,
	[IFLA_MACSEC_CIPHER_SUITE] = अणु .type = NLA_U64 पूर्ण,
	[IFLA_MACSEC_WINDOW] = अणु .type = NLA_U32 पूर्ण,
	[IFLA_MACSEC_ENCODING_SA] = अणु .type = NLA_U8 पूर्ण,
	[IFLA_MACSEC_ENCRYPT] = अणु .type = NLA_U8 पूर्ण,
	[IFLA_MACSEC_PROTECT] = अणु .type = NLA_U8 पूर्ण,
	[IFLA_MACSEC_INC_SCI] = अणु .type = NLA_U8 पूर्ण,
	[IFLA_MACSEC_ES] = अणु .type = NLA_U8 पूर्ण,
	[IFLA_MACSEC_SCB] = अणु .type = NLA_U8 पूर्ण,
	[IFLA_MACSEC_REPLAY_PROTECT] = अणु .type = NLA_U8 पूर्ण,
	[IFLA_MACSEC_VALIDATION] = अणु .type = NLA_U8 पूर्ण,
पूर्ण;

अटल व्योम macsec_मुक्त_netdev(काष्ठा net_device *dev)
अणु
	काष्ठा macsec_dev *macsec = macsec_priv(dev);

	मुक्त_percpu(macsec->stats);
	मुक्त_percpu(macsec->secy.tx_sc.stats);

पूर्ण

अटल व्योम macsec_setup(काष्ठा net_device *dev)
अणु
	ether_setup(dev);
	dev->min_mtu = 0;
	dev->max_mtu = ETH_MAX_MTU;
	dev->priv_flags |= IFF_NO_QUEUE;
	dev->netdev_ops = &macsec_netdev_ops;
	dev->needs_मुक्त_netdev = true;
	dev->priv_deकाष्ठाor = macsec_मुक्त_netdev;
	SET_NETDEV_DEVTYPE(dev, &macsec_type);

	eth_zero_addr(dev->broadcast);
पूर्ण

अटल पूर्णांक macsec_changelink_common(काष्ठा net_device *dev,
				    काष्ठा nlattr *data[])
अणु
	काष्ठा macsec_secy *secy;
	काष्ठा macsec_tx_sc *tx_sc;

	secy = &macsec_priv(dev)->secy;
	tx_sc = &secy->tx_sc;

	अगर (data[IFLA_MACSEC_ENCODING_SA]) अणु
		काष्ठा macsec_tx_sa *tx_sa;

		tx_sc->encoding_sa = nla_get_u8(data[IFLA_MACSEC_ENCODING_SA]);
		tx_sa = rtnl_dereference(tx_sc->sa[tx_sc->encoding_sa]);

		secy->operational = tx_sa && tx_sa->active;
	पूर्ण

	अगर (data[IFLA_MACSEC_WINDOW])
		secy->replay_winकरोw = nla_get_u32(data[IFLA_MACSEC_WINDOW]);

	अगर (data[IFLA_MACSEC_ENCRYPT])
		tx_sc->encrypt = !!nla_get_u8(data[IFLA_MACSEC_ENCRYPT]);

	अगर (data[IFLA_MACSEC_PROTECT])
		secy->protect_frames = !!nla_get_u8(data[IFLA_MACSEC_PROTECT]);

	अगर (data[IFLA_MACSEC_INC_SCI])
		tx_sc->send_sci = !!nla_get_u8(data[IFLA_MACSEC_INC_SCI]);

	अगर (data[IFLA_MACSEC_ES])
		tx_sc->end_station = !!nla_get_u8(data[IFLA_MACSEC_ES]);

	अगर (data[IFLA_MACSEC_SCB])
		tx_sc->scb = !!nla_get_u8(data[IFLA_MACSEC_SCB]);

	अगर (data[IFLA_MACSEC_REPLAY_PROTECT])
		secy->replay_protect = !!nla_get_u8(data[IFLA_MACSEC_REPLAY_PROTECT]);

	अगर (data[IFLA_MACSEC_VALIDATION])
		secy->validate_frames = nla_get_u8(data[IFLA_MACSEC_VALIDATION]);

	अगर (data[IFLA_MACSEC_CIPHER_SUITE]) अणु
		चयन (nla_get_u64(data[IFLA_MACSEC_CIPHER_SUITE])) अणु
		हाल MACSEC_CIPHER_ID_GCM_AES_128:
		हाल MACSEC_DEFAULT_CIPHER_ID:
			secy->key_len = MACSEC_GCM_AES_128_SAK_LEN;
			secy->xpn = false;
			अवरोध;
		हाल MACSEC_CIPHER_ID_GCM_AES_256:
			secy->key_len = MACSEC_GCM_AES_256_SAK_LEN;
			secy->xpn = false;
			अवरोध;
		हाल MACSEC_CIPHER_ID_GCM_AES_XPN_128:
			secy->key_len = MACSEC_GCM_AES_128_SAK_LEN;
			secy->xpn = true;
			अवरोध;
		हाल MACSEC_CIPHER_ID_GCM_AES_XPN_256:
			secy->key_len = MACSEC_GCM_AES_256_SAK_LEN;
			secy->xpn = true;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक macsec_changelink(काष्ठा net_device *dev, काष्ठा nlattr *tb[],
			     काष्ठा nlattr *data[],
			     काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा macsec_dev *macsec = macsec_priv(dev);
	काष्ठा macsec_tx_sc tx_sc;
	काष्ठा macsec_secy secy;
	पूर्णांक ret;

	अगर (!data)
		वापस 0;

	अगर (data[IFLA_MACSEC_CIPHER_SUITE] ||
	    data[IFLA_MACSEC_ICV_LEN] ||
	    data[IFLA_MACSEC_SCI] ||
	    data[IFLA_MACSEC_PORT])
		वापस -EINVAL;

	/* Keep a copy of unmodअगरied secy and tx_sc, in हाल the offload
	 * propagation fails, to revert macsec_changelink_common.
	 */
	स_नकल(&secy, &macsec->secy, माप(secy));
	स_नकल(&tx_sc, &macsec->secy.tx_sc, माप(tx_sc));

	ret = macsec_changelink_common(dev, data);
	अगर (ret)
		वापस ret;

	/* If h/w offloading is available, propagate to the device */
	अगर (macsec_is_offloaded(macsec)) अणु
		स्थिर काष्ठा macsec_ops *ops;
		काष्ठा macsec_context ctx;
		पूर्णांक ret;

		ops = macsec_get_ops(netdev_priv(dev), &ctx);
		अगर (!ops) अणु
			ret = -EOPNOTSUPP;
			जाओ cleanup;
		पूर्ण

		ctx.secy = &macsec->secy;
		ret = macsec_offload(ops->mकरो_upd_secy, &ctx);
		अगर (ret)
			जाओ cleanup;
	पूर्ण

	वापस 0;

cleanup:
	स_नकल(&macsec->secy.tx_sc, &tx_sc, माप(tx_sc));
	स_नकल(&macsec->secy, &secy, माप(secy));

	वापस ret;
पूर्ण

अटल व्योम macsec_del_dev(काष्ठा macsec_dev *macsec)
अणु
	पूर्णांक i;

	जबतक (macsec->secy.rx_sc) अणु
		काष्ठा macsec_rx_sc *rx_sc = rtnl_dereference(macsec->secy.rx_sc);

		rcu_assign_poपूर्णांकer(macsec->secy.rx_sc, rx_sc->next);
		मुक्त_rx_sc(rx_sc);
	पूर्ण

	क्रम (i = 0; i < MACSEC_NUM_AN; i++) अणु
		काष्ठा macsec_tx_sa *sa = rtnl_dereference(macsec->secy.tx_sc.sa[i]);

		अगर (sa) अणु
			RCU_INIT_POINTER(macsec->secy.tx_sc.sa[i], शून्य);
			clear_tx_sa(sa);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम macsec_common_dellink(काष्ठा net_device *dev, काष्ठा list_head *head)
अणु
	काष्ठा macsec_dev *macsec = macsec_priv(dev);
	काष्ठा net_device *real_dev = macsec->real_dev;

	unरेजिस्टर_netdevice_queue(dev, head);
	list_del_rcu(&macsec->secys);
	macsec_del_dev(macsec);
	netdev_upper_dev_unlink(real_dev, dev);

	macsec_generation++;
पूर्ण

अटल व्योम macsec_dellink(काष्ठा net_device *dev, काष्ठा list_head *head)
अणु
	काष्ठा macsec_dev *macsec = macsec_priv(dev);
	काष्ठा net_device *real_dev = macsec->real_dev;
	काष्ठा macsec_rxh_data *rxd = macsec_data_rtnl(real_dev);

	/* If h/w offloading is available, propagate to the device */
	अगर (macsec_is_offloaded(macsec)) अणु
		स्थिर काष्ठा macsec_ops *ops;
		काष्ठा macsec_context ctx;

		ops = macsec_get_ops(netdev_priv(dev), &ctx);
		अगर (ops) अणु
			ctx.secy = &macsec->secy;
			macsec_offload(ops->mकरो_del_secy, &ctx);
		पूर्ण
	पूर्ण

	macsec_common_dellink(dev, head);

	अगर (list_empty(&rxd->secys)) अणु
		netdev_rx_handler_unरेजिस्टर(real_dev);
		kमुक्त(rxd);
	पूर्ण
पूर्ण

अटल पूर्णांक रेजिस्टर_macsec_dev(काष्ठा net_device *real_dev,
			       काष्ठा net_device *dev)
अणु
	काष्ठा macsec_dev *macsec = macsec_priv(dev);
	काष्ठा macsec_rxh_data *rxd = macsec_data_rtnl(real_dev);

	अगर (!rxd) अणु
		पूर्णांक err;

		rxd = kदो_स्मृति(माप(*rxd), GFP_KERNEL);
		अगर (!rxd)
			वापस -ENOMEM;

		INIT_LIST_HEAD(&rxd->secys);

		err = netdev_rx_handler_रेजिस्टर(real_dev, macsec_handle_frame,
						 rxd);
		अगर (err < 0) अणु
			kमुक्त(rxd);
			वापस err;
		पूर्ण
	पूर्ण

	list_add_tail_rcu(&macsec->secys, &rxd->secys);
	वापस 0;
पूर्ण

अटल bool sci_exists(काष्ठा net_device *dev, sci_t sci)
अणु
	काष्ठा macsec_rxh_data *rxd = macsec_data_rtnl(dev);
	काष्ठा macsec_dev *macsec;

	list_क्रम_each_entry(macsec, &rxd->secys, secys) अणु
		अगर (macsec->secy.sci == sci)
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल पूर्णांक macsec_add_dev(काष्ठा net_device *dev, sci_t sci, u8 icv_len)
अणु
	काष्ठा macsec_dev *macsec = macsec_priv(dev);
	काष्ठा macsec_secy *secy = &macsec->secy;

	macsec->stats = netdev_alloc_pcpu_stats(काष्ठा pcpu_secy_stats);
	अगर (!macsec->stats)
		वापस -ENOMEM;

	secy->tx_sc.stats = netdev_alloc_pcpu_stats(काष्ठा pcpu_tx_sc_stats);
	अगर (!secy->tx_sc.stats) अणु
		मुक्त_percpu(macsec->stats);
		वापस -ENOMEM;
	पूर्ण

	अगर (sci == MACSEC_UNDEF_SCI)
		sci = dev_to_sci(dev, MACSEC_PORT_ES);

	secy->netdev = dev;
	secy->operational = true;
	secy->key_len = DEFAULT_SAK_LEN;
	secy->icv_len = icv_len;
	secy->validate_frames = MACSEC_VALIDATE_DEFAULT;
	secy->protect_frames = true;
	secy->replay_protect = false;
	secy->xpn = DEFAULT_XPN;

	secy->sci = sci;
	secy->tx_sc.active = true;
	secy->tx_sc.encoding_sa = DEFAULT_ENCODING_SA;
	secy->tx_sc.encrypt = DEFAULT_ENCRYPT;
	secy->tx_sc.send_sci = DEFAULT_SEND_SCI;
	secy->tx_sc.end_station = false;
	secy->tx_sc.scb = false;

	वापस 0;
पूर्ण

अटल काष्ठा lock_class_key macsec_netdev_addr_lock_key;

अटल पूर्णांक macsec_newlink(काष्ठा net *net, काष्ठा net_device *dev,
			  काष्ठा nlattr *tb[], काष्ठा nlattr *data[],
			  काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा macsec_dev *macsec = macsec_priv(dev);
	rx_handler_func_t *rx_handler;
	u8 icv_len = DEFAULT_ICV_LEN;
	काष्ठा net_device *real_dev;
	पूर्णांक err, mtu;
	sci_t sci;

	अगर (!tb[IFLA_LINK])
		वापस -EINVAL;
	real_dev = __dev_get_by_index(net, nla_get_u32(tb[IFLA_LINK]));
	अगर (!real_dev)
		वापस -ENODEV;
	अगर (real_dev->type != ARPHRD_ETHER)
		वापस -EINVAL;

	dev->priv_flags |= IFF_MACSEC;

	macsec->real_dev = real_dev;

	अगर (data && data[IFLA_MACSEC_OFFLOAD])
		macsec->offload = nla_get_offload(data[IFLA_MACSEC_OFFLOAD]);
	अन्यथा
		/* MACsec offloading is off by शेष */
		macsec->offload = MACSEC_OFFLOAD_OFF;

	/* Check अगर the offloading mode is supported by the underlying layers */
	अगर (macsec->offload != MACSEC_OFFLOAD_OFF &&
	    !macsec_check_offload(macsec->offload, macsec))
		वापस -EOPNOTSUPP;

	अगर (data && data[IFLA_MACSEC_ICV_LEN])
		icv_len = nla_get_u8(data[IFLA_MACSEC_ICV_LEN]);
	mtu = real_dev->mtu - icv_len - macsec_extra_len(true);
	अगर (mtu < 0)
		dev->mtu = 0;
	अन्यथा
		dev->mtu = mtu;

	rx_handler = rtnl_dereference(real_dev->rx_handler);
	अगर (rx_handler && rx_handler != macsec_handle_frame)
		वापस -EBUSY;

	err = रेजिस्टर_netdevice(dev);
	अगर (err < 0)
		वापस err;

	netdev_lockdep_set_classes(dev);
	lockdep_set_class(&dev->addr_list_lock,
			  &macsec_netdev_addr_lock_key);

	err = netdev_upper_dev_link(real_dev, dev, extack);
	अगर (err < 0)
		जाओ unरेजिस्टर;

	/* need to be alपढ़ोy रेजिस्टरed so that ->init has run and
	 * the MAC addr is set
	 */
	अगर (data && data[IFLA_MACSEC_SCI])
		sci = nla_get_sci(data[IFLA_MACSEC_SCI]);
	अन्यथा अगर (data && data[IFLA_MACSEC_PORT])
		sci = dev_to_sci(dev, nla_get_be16(data[IFLA_MACSEC_PORT]));
	अन्यथा
		sci = dev_to_sci(dev, MACSEC_PORT_ES);

	अगर (rx_handler && sci_exists(real_dev, sci)) अणु
		err = -EBUSY;
		जाओ unlink;
	पूर्ण

	err = macsec_add_dev(dev, sci, icv_len);
	अगर (err)
		जाओ unlink;

	अगर (data) अणु
		err = macsec_changelink_common(dev, data);
		अगर (err)
			जाओ del_dev;
	पूर्ण

	/* If h/w offloading is available, propagate to the device */
	अगर (macsec_is_offloaded(macsec)) अणु
		स्थिर काष्ठा macsec_ops *ops;
		काष्ठा macsec_context ctx;

		ops = macsec_get_ops(macsec, &ctx);
		अगर (ops) अणु
			ctx.secy = &macsec->secy;
			err = macsec_offload(ops->mकरो_add_secy, &ctx);
			अगर (err)
				जाओ del_dev;
		पूर्ण
	पूर्ण

	err = रेजिस्टर_macsec_dev(real_dev, dev);
	अगर (err < 0)
		जाओ del_dev;

	netअगर_stacked_transfer_operstate(real_dev, dev);
	linkwatch_fire_event(dev);

	macsec_generation++;

	वापस 0;

del_dev:
	macsec_del_dev(macsec);
unlink:
	netdev_upper_dev_unlink(real_dev, dev);
unरेजिस्टर:
	unरेजिस्टर_netdevice(dev);
	वापस err;
पूर्ण

अटल पूर्णांक macsec_validate_attr(काष्ठा nlattr *tb[], काष्ठा nlattr *data[],
				काष्ठा netlink_ext_ack *extack)
अणु
	u64 csid = MACSEC_DEFAULT_CIPHER_ID;
	u8 icv_len = DEFAULT_ICV_LEN;
	पूर्णांक flag;
	bool es, scb, sci;

	अगर (!data)
		वापस 0;

	अगर (data[IFLA_MACSEC_CIPHER_SUITE])
		csid = nla_get_u64(data[IFLA_MACSEC_CIPHER_SUITE]);

	अगर (data[IFLA_MACSEC_ICV_LEN]) अणु
		icv_len = nla_get_u8(data[IFLA_MACSEC_ICV_LEN]);
		अगर (icv_len != DEFAULT_ICV_LEN) अणु
			अक्षर dummy_key[DEFAULT_SAK_LEN] = अणु 0 पूर्ण;
			काष्ठा crypto_aead *dummy_tfm;

			dummy_tfm = macsec_alloc_tfm(dummy_key,
						     DEFAULT_SAK_LEN,
						     icv_len);
			अगर (IS_ERR(dummy_tfm))
				वापस PTR_ERR(dummy_tfm);
			crypto_मुक्त_aead(dummy_tfm);
		पूर्ण
	पूर्ण

	चयन (csid) अणु
	हाल MACSEC_CIPHER_ID_GCM_AES_128:
	हाल MACSEC_CIPHER_ID_GCM_AES_256:
	हाल MACSEC_CIPHER_ID_GCM_AES_XPN_128:
	हाल MACSEC_CIPHER_ID_GCM_AES_XPN_256:
	हाल MACSEC_DEFAULT_CIPHER_ID:
		अगर (icv_len < MACSEC_MIN_ICV_LEN ||
		    icv_len > MACSEC_STD_ICV_LEN)
			वापस -EINVAL;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (data[IFLA_MACSEC_ENCODING_SA]) अणु
		अगर (nla_get_u8(data[IFLA_MACSEC_ENCODING_SA]) >= MACSEC_NUM_AN)
			वापस -EINVAL;
	पूर्ण

	क्रम (flag = IFLA_MACSEC_ENCODING_SA + 1;
	     flag < IFLA_MACSEC_VALIDATION;
	     flag++) अणु
		अगर (data[flag]) अणु
			अगर (nla_get_u8(data[flag]) > 1)
				वापस -EINVAL;
		पूर्ण
	पूर्ण

	es  = data[IFLA_MACSEC_ES] ? nla_get_u8(data[IFLA_MACSEC_ES]) : false;
	sci = data[IFLA_MACSEC_INC_SCI] ? nla_get_u8(data[IFLA_MACSEC_INC_SCI]) : false;
	scb = data[IFLA_MACSEC_SCB] ? nla_get_u8(data[IFLA_MACSEC_SCB]) : false;

	अगर ((sci && (scb || es)) || (scb && es))
		वापस -EINVAL;

	अगर (data[IFLA_MACSEC_VALIDATION] &&
	    nla_get_u8(data[IFLA_MACSEC_VALIDATION]) > MACSEC_VALIDATE_MAX)
		वापस -EINVAL;

	अगर ((data[IFLA_MACSEC_REPLAY_PROTECT] &&
	     nla_get_u8(data[IFLA_MACSEC_REPLAY_PROTECT])) &&
	    !data[IFLA_MACSEC_WINDOW])
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल काष्ठा net *macsec_get_link_net(स्थिर काष्ठा net_device *dev)
अणु
	वापस dev_net(macsec_priv(dev)->real_dev);
पूर्ण

अटल माप_प्रकार macsec_get_size(स्थिर काष्ठा net_device *dev)
अणु
	वापस  nla_total_size_64bit(8) + /* IFLA_MACSEC_SCI */
		nla_total_size(1) + /* IFLA_MACSEC_ICV_LEN */
		nla_total_size_64bit(8) + /* IFLA_MACSEC_CIPHER_SUITE */
		nla_total_size(4) + /* IFLA_MACSEC_WINDOW */
		nla_total_size(1) + /* IFLA_MACSEC_ENCODING_SA */
		nla_total_size(1) + /* IFLA_MACSEC_ENCRYPT */
		nla_total_size(1) + /* IFLA_MACSEC_PROTECT */
		nla_total_size(1) + /* IFLA_MACSEC_INC_SCI */
		nla_total_size(1) + /* IFLA_MACSEC_ES */
		nla_total_size(1) + /* IFLA_MACSEC_SCB */
		nla_total_size(1) + /* IFLA_MACSEC_REPLAY_PROTECT */
		nla_total_size(1) + /* IFLA_MACSEC_VALIDATION */
		0;
पूर्ण

अटल पूर्णांक macsec_fill_info(काष्ठा sk_buff *skb,
			    स्थिर काष्ठा net_device *dev)
अणु
	काष्ठा macsec_secy *secy = &macsec_priv(dev)->secy;
	काष्ठा macsec_tx_sc *tx_sc = &secy->tx_sc;
	u64 csid;

	चयन (secy->key_len) अणु
	हाल MACSEC_GCM_AES_128_SAK_LEN:
		csid = secy->xpn ? MACSEC_CIPHER_ID_GCM_AES_XPN_128 : MACSEC_DEFAULT_CIPHER_ID;
		अवरोध;
	हाल MACSEC_GCM_AES_256_SAK_LEN:
		csid = secy->xpn ? MACSEC_CIPHER_ID_GCM_AES_XPN_256 : MACSEC_CIPHER_ID_GCM_AES_256;
		अवरोध;
	शेष:
		जाओ nla_put_failure;
	पूर्ण

	अगर (nla_put_sci(skb, IFLA_MACSEC_SCI, secy->sci,
			IFLA_MACSEC_PAD) ||
	    nla_put_u8(skb, IFLA_MACSEC_ICV_LEN, secy->icv_len) ||
	    nla_put_u64_64bit(skb, IFLA_MACSEC_CIPHER_SUITE,
			      csid, IFLA_MACSEC_PAD) ||
	    nla_put_u8(skb, IFLA_MACSEC_ENCODING_SA, tx_sc->encoding_sa) ||
	    nla_put_u8(skb, IFLA_MACSEC_ENCRYPT, tx_sc->encrypt) ||
	    nla_put_u8(skb, IFLA_MACSEC_PROTECT, secy->protect_frames) ||
	    nla_put_u8(skb, IFLA_MACSEC_INC_SCI, tx_sc->send_sci) ||
	    nla_put_u8(skb, IFLA_MACSEC_ES, tx_sc->end_station) ||
	    nla_put_u8(skb, IFLA_MACSEC_SCB, tx_sc->scb) ||
	    nla_put_u8(skb, IFLA_MACSEC_REPLAY_PROTECT, secy->replay_protect) ||
	    nla_put_u8(skb, IFLA_MACSEC_VALIDATION, secy->validate_frames) ||
	    0)
		जाओ nla_put_failure;

	अगर (secy->replay_protect) अणु
		अगर (nla_put_u32(skb, IFLA_MACSEC_WINDOW, secy->replay_winकरोw))
			जाओ nla_put_failure;
	पूर्ण

	वापस 0;

nla_put_failure:
	वापस -EMSGSIZE;
पूर्ण

अटल काष्ठा rtnl_link_ops macsec_link_ops __पढ़ो_mostly = अणु
	.kind		= "macsec",
	.priv_size	= माप(काष्ठा macsec_dev),
	.maxtype	= IFLA_MACSEC_MAX,
	.policy		= macsec_rtnl_policy,
	.setup		= macsec_setup,
	.validate	= macsec_validate_attr,
	.newlink	= macsec_newlink,
	.changelink	= macsec_changelink,
	.dellink	= macsec_dellink,
	.get_size	= macsec_get_size,
	.fill_info	= macsec_fill_info,
	.get_link_net	= macsec_get_link_net,
पूर्ण;

अटल bool is_macsec_master(काष्ठा net_device *dev)
अणु
	वापस rcu_access_poपूर्णांकer(dev->rx_handler) == macsec_handle_frame;
पूर्ण

अटल पूर्णांक macsec_notअगरy(काष्ठा notअगरier_block *this, अचिन्हित दीर्घ event,
			 व्योम *ptr)
अणु
	काष्ठा net_device *real_dev = netdev_notअगरier_info_to_dev(ptr);
	LIST_HEAD(head);

	अगर (!is_macsec_master(real_dev))
		वापस NOTIFY_DONE;

	चयन (event) अणु
	हाल NETDEV_DOWN:
	हाल NETDEV_UP:
	हाल NETDEV_CHANGE: अणु
		काष्ठा macsec_dev *m, *n;
		काष्ठा macsec_rxh_data *rxd;

		rxd = macsec_data_rtnl(real_dev);
		list_क्रम_each_entry_safe(m, n, &rxd->secys, secys) अणु
			काष्ठा net_device *dev = m->secy.netdev;

			netअगर_stacked_transfer_operstate(real_dev, dev);
		पूर्ण
		अवरोध;
	पूर्ण
	हाल NETDEV_UNREGISTER: अणु
		काष्ठा macsec_dev *m, *n;
		काष्ठा macsec_rxh_data *rxd;

		rxd = macsec_data_rtnl(real_dev);
		list_क्रम_each_entry_safe(m, n, &rxd->secys, secys) अणु
			macsec_common_dellink(m->secy.netdev, &head);
		पूर्ण

		netdev_rx_handler_unरेजिस्टर(real_dev);
		kमुक्त(rxd);

		unरेजिस्टर_netdevice_many(&head);
		अवरोध;
	पूर्ण
	हाल NETDEV_CHANGEMTU: अणु
		काष्ठा macsec_dev *m;
		काष्ठा macsec_rxh_data *rxd;

		rxd = macsec_data_rtnl(real_dev);
		list_क्रम_each_entry(m, &rxd->secys, secys) अणु
			काष्ठा net_device *dev = m->secy.netdev;
			अचिन्हित पूर्णांक mtu = real_dev->mtu - (m->secy.icv_len +
							    macsec_extra_len(true));

			अगर (dev->mtu > mtu)
				dev_set_mtu(dev, mtu);
		पूर्ण
	पूर्ण
	पूर्ण

	वापस NOTIFY_OK;
पूर्ण

अटल काष्ठा notअगरier_block macsec_notअगरier = अणु
	.notअगरier_call = macsec_notअगरy,
पूर्ण;

अटल पूर्णांक __init macsec_init(व्योम)
अणु
	पूर्णांक err;

	pr_info("MACsec IEEE 802.1AE\n");
	err = रेजिस्टर_netdevice_notअगरier(&macsec_notअगरier);
	अगर (err)
		वापस err;

	err = rtnl_link_रेजिस्टर(&macsec_link_ops);
	अगर (err)
		जाओ notअगरier;

	err = genl_रेजिस्टर_family(&macsec_fam);
	अगर (err)
		जाओ rtnl;

	वापस 0;

rtnl:
	rtnl_link_unरेजिस्टर(&macsec_link_ops);
notअगरier:
	unरेजिस्टर_netdevice_notअगरier(&macsec_notअगरier);
	वापस err;
पूर्ण

अटल व्योम __निकास macsec_निकास(व्योम)
अणु
	genl_unरेजिस्टर_family(&macsec_fam);
	rtnl_link_unरेजिस्टर(&macsec_link_ops);
	unरेजिस्टर_netdevice_notअगरier(&macsec_notअगरier);
	rcu_barrier();
पूर्ण

module_init(macsec_init);
module_निकास(macsec_निकास);

MODULE_ALIAS_RTNL_LINK("macsec");
MODULE_ALIAS_GENL_FAMILY("macsec");

MODULE_DESCRIPTION("MACsec IEEE 802.1AE");
MODULE_LICENSE("GPL v2");
