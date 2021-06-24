<शैली गुरु>
/*
 * This file is part of the Chelsio T6 Crypto driver क्रम Linux.
 *
 * Copyright (c) 2003-2017 Chelsio Communications, Inc. All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary क्रमms, with or
 *     without modअगरication, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary क्रमm must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the करोcumentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * Written and Maपूर्णांकained by:
 *	Atul Gupta (atul.gupta@chelsio.com)
 */

#घोषणा pr_fmt(fmt) "ch_ipsec: " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/crypto.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/ip.h>
#समावेश <linux/netdevice.h>
#समावेश <net/esp.h>
#समावेश <net/xfrm.h>
#समावेश <crypto/aes.h>
#समावेश <crypto/algapi.h>
#समावेश <crypto/hash.h>
#समावेश <crypto/sha1.h>
#समावेश <crypto/sha2.h>
#समावेश <crypto/authenc.h>
#समावेश <crypto/पूर्णांकernal/aead.h>
#समावेश <crypto/null.h>
#समावेश <crypto/पूर्णांकernal/skcipher.h>
#समावेश <crypto/aead.h>
#समावेश <crypto/scatterwalk.h>
#समावेश <crypto/पूर्णांकernal/hash.h>

#समावेश "chcr_ipsec.h"

/*
 * Max Tx descriptor space we allow क्रम an Ethernet packet to be अंतरभूतd
 * पूर्णांकo a WR.
 */
#घोषणा MAX_IMM_TX_PKT_LEN 256
#घोषणा GCM_ESP_IV_SIZE     8

अटल LIST_HEAD(uld_ctx_list);
अटल DEFINE_MUTEX(dev_mutex);

अटल bool ch_ipsec_offload_ok(काष्ठा sk_buff *skb, काष्ठा xfrm_state *x);
अटल पूर्णांक ch_ipsec_uld_state_change(व्योम *handle, क्रमागत cxgb4_state new_state);
अटल पूर्णांक ch_ipsec_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev);
अटल व्योम *ch_ipsec_uld_add(स्थिर काष्ठा cxgb4_lld_info *infop);
अटल व्योम ch_ipsec_advance_esn_state(काष्ठा xfrm_state *x);
अटल व्योम ch_ipsec_xfrm_मुक्त_state(काष्ठा xfrm_state *x);
अटल व्योम ch_ipsec_xfrm_del_state(काष्ठा xfrm_state *x);
अटल पूर्णांक ch_ipsec_xfrm_add_state(काष्ठा xfrm_state *x);

अटल स्थिर काष्ठा xfrmdev_ops ch_ipsec_xfrmdev_ops = अणु
	.xकरो_dev_state_add      = ch_ipsec_xfrm_add_state,
	.xकरो_dev_state_delete   = ch_ipsec_xfrm_del_state,
	.xकरो_dev_state_मुक्त     = ch_ipsec_xfrm_मुक्त_state,
	.xकरो_dev_offload_ok     = ch_ipsec_offload_ok,
	.xकरो_dev_state_advance_esn = ch_ipsec_advance_esn_state,
पूर्ण;

अटल काष्ठा cxgb4_uld_info ch_ipsec_uld_info = अणु
	.name = CHIPSEC_DRV_MODULE_NAME,
	.add = ch_ipsec_uld_add,
	.state_change = ch_ipsec_uld_state_change,
	.tx_handler = ch_ipsec_xmit,
	.xfrmdev_ops = &ch_ipsec_xfrmdev_ops,
पूर्ण;

अटल व्योम *ch_ipsec_uld_add(स्थिर काष्ठा cxgb4_lld_info *infop)
अणु
	काष्ठा ipsec_uld_ctx *u_ctx;

	pr_info_once("%s - version %s\n", CHIPSEC_DRV_DESC,
		     CHIPSEC_DRV_VERSION);
	u_ctx = kzalloc(माप(*u_ctx), GFP_KERNEL);
	अगर (!u_ctx) अणु
		u_ctx = ERR_PTR(-ENOMEM);
		जाओ out;
	पूर्ण
	u_ctx->lldi = *infop;
out:
	वापस u_ctx;
पूर्ण

अटल पूर्णांक ch_ipsec_uld_state_change(व्योम *handle, क्रमागत cxgb4_state new_state)
अणु
	काष्ठा ipsec_uld_ctx *u_ctx = handle;

	pr_debug("new_state %u\n", new_state);
	चयन (new_state) अणु
	हाल CXGB4_STATE_UP:
		pr_info("%s: Up\n", pci_name(u_ctx->lldi.pdev));
		mutex_lock(&dev_mutex);
		list_add_tail(&u_ctx->entry, &uld_ctx_list);
		mutex_unlock(&dev_mutex);
		अवरोध;
	हाल CXGB4_STATE_START_RECOVERY:
	हाल CXGB4_STATE_DOWN:
	हाल CXGB4_STATE_DETACH:
		pr_info("%s: Down\n", pci_name(u_ctx->lldi.pdev));
		list_del(&u_ctx->entry);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ch_ipsec_setauthsize(काष्ठा xfrm_state *x,
				काष्ठा ipsec_sa_entry *sa_entry)
अणु
	पूर्णांक hmac_ctrl;
	पूर्णांक authsize = x->aead->alg_icv_len / 8;

	sa_entry->authsize = authsize;

	चयन (authsize) अणु
	हाल ICV_8:
		hmac_ctrl = CHCR_SCMD_HMAC_CTRL_DIV2;
		अवरोध;
	हाल ICV_12:
		hmac_ctrl = CHCR_SCMD_HMAC_CTRL_IPSEC_96BIT;
		अवरोध;
	हाल ICV_16:
		hmac_ctrl = CHCR_SCMD_HMAC_CTRL_NO_TRUNC;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस hmac_ctrl;
पूर्ण

अटल पूर्णांक ch_ipsec_setkey(काष्ठा xfrm_state *x,
			   काष्ठा ipsec_sa_entry *sa_entry)
अणु
	पूर्णांक keylen = (x->aead->alg_key_len + 7) / 8;
	अचिन्हित अक्षर *key = x->aead->alg_key;
	पूर्णांक ck_size, key_ctx_size = 0;
	अचिन्हित अक्षर ghash_h[AEAD_H_SIZE];
	काष्ठा crypto_aes_ctx aes;
	पूर्णांक ret = 0;

	अगर (keylen > 3) अणु
		keylen -= 4;  /* nonce/salt is present in the last 4 bytes */
		स_नकल(sa_entry->salt, key + keylen, 4);
	पूर्ण

	अगर (keylen == AES_KEYSIZE_128) अणु
		ck_size = CHCR_KEYCTX_CIPHER_KEY_SIZE_128;
	पूर्ण अन्यथा अगर (keylen == AES_KEYSIZE_192) अणु
		ck_size = CHCR_KEYCTX_CIPHER_KEY_SIZE_192;
	पूर्ण अन्यथा अगर (keylen == AES_KEYSIZE_256) अणु
		ck_size = CHCR_KEYCTX_CIPHER_KEY_SIZE_256;
	पूर्ण अन्यथा अणु
		pr_err("GCM: Invalid key length %d\n", keylen);
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	स_नकल(sa_entry->key, key, keylen);
	sa_entry->enckey_len = keylen;
	key_ctx_size = माप(काष्ठा _key_ctx) +
			      ((DIV_ROUND_UP(keylen, 16)) << 4) +
			      AEAD_H_SIZE;

	sa_entry->key_ctx_hdr = FILL_KEY_CTX_HDR(ck_size,
						 CHCR_KEYCTX_MAC_KEY_SIZE_128,
						 0, 0,
						 key_ctx_size >> 4);

	/* Calculate the H = CIPH(K, 0 repeated 16 बार).
	 * It will go in key context
	 */
	ret = aes_expandkey(&aes, key, keylen);
	अगर (ret) अणु
		sa_entry->enckey_len = 0;
		जाओ out;
	पूर्ण
	स_रखो(ghash_h, 0, AEAD_H_SIZE);
	aes_encrypt(&aes, ghash_h, ghash_h);
	memzero_explicit(&aes, माप(aes));

	स_नकल(sa_entry->key + (DIV_ROUND_UP(sa_entry->enckey_len, 16) *
	       16), ghash_h, AEAD_H_SIZE);
	sa_entry->kctx_len = ((DIV_ROUND_UP(sa_entry->enckey_len, 16)) << 4) +
			      AEAD_H_SIZE;
out:
	वापस ret;
पूर्ण

/*
 * ch_ipsec_xfrm_add_state
 * वापसs 0 on success, negative error अगर failed to send message to FPGA
 * positive error अगर FPGA वापसed a bad response
 */
अटल पूर्णांक ch_ipsec_xfrm_add_state(काष्ठा xfrm_state *x)
अणु
	काष्ठा ipsec_sa_entry *sa_entry;
	पूर्णांक res = 0;

	अगर (x->props.aalgo != SADB_AALG_NONE) अणु
		pr_debug("Cannot offload authenticated xfrm states\n");
		वापस -EINVAL;
	पूर्ण
	अगर (x->props.calgo != SADB_X_CALG_NONE) अणु
		pr_debug("Cannot offload compressed xfrm states\n");
		वापस -EINVAL;
	पूर्ण
	अगर (x->props.family != AF_INET &&
	    x->props.family != AF_INET6) अणु
		pr_debug("Only IPv4/6 xfrm state offloaded\n");
		वापस -EINVAL;
	पूर्ण
	अगर (x->props.mode != XFRM_MODE_TRANSPORT &&
	    x->props.mode != XFRM_MODE_TUNNEL) अणु
		pr_debug("Only transport and tunnel xfrm offload\n");
		वापस -EINVAL;
	पूर्ण
	अगर (x->id.proto != IPPROTO_ESP) अणु
		pr_debug("Only ESP xfrm state offloaded\n");
		वापस -EINVAL;
	पूर्ण
	अगर (x->encap) अणु
		pr_debug("Encapsulated xfrm state not offloaded\n");
		वापस -EINVAL;
	पूर्ण
	अगर (!x->aead) अणु
		pr_debug("Cannot offload xfrm states without aead\n");
		वापस -EINVAL;
	पूर्ण
	अगर (x->aead->alg_icv_len != 128 &&
	    x->aead->alg_icv_len != 96) अणु
		pr_debug("Cannot offload xfrm states with AEAD ICV length other than 96b & 128b\n");
	वापस -EINVAL;
	पूर्ण
	अगर ((x->aead->alg_key_len != 128 + 32) &&
	    (x->aead->alg_key_len != 256 + 32)) अणु
		pr_debug("cannot offload xfrm states with AEAD key length other than 128/256 bit\n");
		वापस -EINVAL;
	पूर्ण
	अगर (x->tfcpad) अणु
		pr_debug("Cannot offload xfrm states with tfc padding\n");
		वापस -EINVAL;
	पूर्ण
	अगर (!x->geniv) अणु
		pr_debug("Cannot offload xfrm states without geniv\n");
		वापस -EINVAL;
	पूर्ण
	अगर (म_भेद(x->geniv, "seqiv")) अणु
		pr_debug("Cannot offload xfrm states with geniv other than seqiv\n");
		वापस -EINVAL;
	पूर्ण

	sa_entry = kzalloc(माप(*sa_entry), GFP_KERNEL);
	अगर (!sa_entry) अणु
		res = -ENOMEM;
		जाओ out;
	पूर्ण

	sa_entry->hmac_ctrl = ch_ipsec_setauthsize(x, sa_entry);
	अगर (x->props.flags & XFRM_STATE_ESN)
		sa_entry->esn = 1;
	ch_ipsec_setkey(x, sa_entry);
	x->xso.offload_handle = (अचिन्हित दीर्घ)sa_entry;
	try_module_get(THIS_MODULE);
out:
	वापस res;
पूर्ण

अटल व्योम ch_ipsec_xfrm_del_state(काष्ठा xfrm_state *x)
अणु
	/* करो nothing */
	अगर (!x->xso.offload_handle)
		वापस;
पूर्ण

अटल व्योम ch_ipsec_xfrm_मुक्त_state(काष्ठा xfrm_state *x)
अणु
	काष्ठा ipsec_sa_entry *sa_entry;

	अगर (!x->xso.offload_handle)
		वापस;

	sa_entry = (काष्ठा ipsec_sa_entry *)x->xso.offload_handle;
	kमुक्त(sa_entry);
	module_put(THIS_MODULE);
पूर्ण

अटल bool ch_ipsec_offload_ok(काष्ठा sk_buff *skb, काष्ठा xfrm_state *x)
अणु
	अगर (x->props.family == AF_INET) अणु
		/* Offload with IP options is not supported yet */
		अगर (ip_hdr(skb)->ihl > 5)
			वापस false;
	पूर्ण अन्यथा अणु
		/* Offload with IPv6 extension headers is not support yet */
		अगर (ipv6_ext_hdr(ipv6_hdr(skb)->nexthdr))
			वापस false;
	पूर्ण
	वापस true;
पूर्ण

अटल व्योम ch_ipsec_advance_esn_state(काष्ठा xfrm_state *x)
अणु
	/* करो nothing */
	अगर (!x->xso.offload_handle)
		वापस;
पूर्ण

अटल पूर्णांक is_eth_imm(स्थिर काष्ठा sk_buff *skb,
		      काष्ठा ipsec_sa_entry *sa_entry)
अणु
	अचिन्हित पूर्णांक kctx_len;
	पूर्णांक hdrlen;

	kctx_len = sa_entry->kctx_len;
	hdrlen = माप(काष्ठा fw_ulptx_wr) +
		 माप(काष्ठा chcr_ipsec_req) + kctx_len;

	hdrlen += माप(काष्ठा cpl_tx_pkt);
	अगर (sa_entry->esn)
		hdrlen += (DIV_ROUND_UP(माप(काष्ठा chcr_ipsec_aaभाग), 16)
			   << 4);
	अगर (skb->len <= MAX_IMM_TX_PKT_LEN - hdrlen)
		वापस hdrlen;
	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक calc_tx_sec_flits(स्थिर काष्ठा sk_buff *skb,
				      काष्ठा ipsec_sa_entry *sa_entry,
				      bool *immediate)
अणु
	अचिन्हित पूर्णांक kctx_len;
	अचिन्हित पूर्णांक flits;
	पूर्णांक aaभागlen;
	पूर्णांक hdrlen;

	kctx_len = sa_entry->kctx_len;
	hdrlen = is_eth_imm(skb, sa_entry);
	aaभागlen = sa_entry->esn ? DIV_ROUND_UP(माप(काष्ठा chcr_ipsec_aaभाग),
						16) : 0;
	aaभागlen <<= 4;

	/* If the skb is small enough, we can pump it out as a work request
	 * with only immediate data.  In that हाल we just have to have the
	 * TX Packet header plus the skb data in the Work Request.
	 */

	अगर (hdrlen) अणु
		*immediate = true;
		वापस DIV_ROUND_UP(skb->len + hdrlen, माप(__be64));
	पूर्ण

	flits = sgl_len(skb_shinfo(skb)->nr_frags + 1);

	/* Otherwise, we're going to have to स्थिरruct a Scatter gather list
	 * of the skb body and fragments.  We also include the flits necessary
	 * क्रम the TX Packet Work Request and CPL.  We always have a firmware
	 * Write Header (incorporated as part of the cpl_tx_pkt_lso and
	 * cpl_tx_pkt काष्ठाures), followed by either a TX Packet Write CPL
	 * message or, अगर we're करोing a Large Send Offload, an LSO CPL message
	 * with an embedded TX Packet Write CPL message.
	 */
	flits += (माप(काष्ठा fw_ulptx_wr) +
		  माप(काष्ठा chcr_ipsec_req) +
		  kctx_len +
		  माप(काष्ठा cpl_tx_pkt_core) +
		  aaभागlen) / माप(__be64);
	वापस flits;
पूर्ण

अटल व्योम *copy_esn_pktxt(काष्ठा sk_buff *skb,
			    काष्ठा net_device *dev,
			    व्योम *pos,
			    काष्ठा ipsec_sa_entry *sa_entry)
अणु
	काष्ठा chcr_ipsec_aaभाग *aaभाग;
	काष्ठा ulptx_idata *sc_imm;
	काष्ठा ip_esp_hdr *esphdr;
	काष्ठा xfrm_offload *xo;
	काष्ठा sge_eth_txq *q;
	काष्ठा adapter *adap;
	काष्ठा port_info *pi;
	__be64 seqno;
	u32 qidx;
	u32 seqlo;
	u8 *iv;
	पूर्णांक eoq;
	पूर्णांक len;

	pi = netdev_priv(dev);
	adap = pi->adapter;
	qidx = skb->queue_mapping;
	q = &adap->sge.ethtxq[qidx + pi->first_qset];

	/* end of queue, reset pos to start of queue */
	eoq = (व्योम *)q->q.stat - pos;
	अगर (!eoq)
		pos = q->q.desc;

	len = DIV_ROUND_UP(माप(काष्ठा chcr_ipsec_aaभाग), 16) << 4;
	स_रखो(pos, 0, len);
	aaभाग = (काष्ठा chcr_ipsec_aaभाग *)pos;
	esphdr = (काष्ठा ip_esp_hdr *)skb_transport_header(skb);
	iv = skb_transport_header(skb) + माप(काष्ठा ip_esp_hdr);
	xo = xfrm_offload(skb);

	aaभाग->spi = (esphdr->spi);
	seqlo = ntohl(esphdr->seq_no);
	seqno = cpu_to_be64(seqlo + ((u64)xo->seq.hi << 32));
	स_नकल(aaभाग->seq_no, &seqno, 8);
	iv = skb_transport_header(skb) + माप(काष्ठा ip_esp_hdr);
	स_नकल(aaभाग->iv, iv, 8);

	अगर (is_eth_imm(skb, sa_entry) && !skb_is_nonlinear(skb)) अणु
		sc_imm = (काष्ठा ulptx_idata *)(pos +
			  (DIV_ROUND_UP(माप(काष्ठा chcr_ipsec_aaभाग),
					माप(__be64)) << 3));
		sc_imm->cmd_more = FILL_CMD_MORE(0);
		sc_imm->len = cpu_to_be32(skb->len);
	पूर्ण
	pos += len;
	वापस pos;
पूर्ण

अटल व्योम *copy_cpltx_pktxt(काष्ठा sk_buff *skb,
			      काष्ठा net_device *dev,
			      व्योम *pos,
			      काष्ठा ipsec_sa_entry *sa_entry)
अणु
	काष्ठा cpl_tx_pkt_core *cpl;
	काष्ठा sge_eth_txq *q;
	काष्ठा adapter *adap;
	काष्ठा port_info *pi;
	u32 ctrl0, qidx;
	u64 cntrl = 0;
	पूर्णांक left;

	pi = netdev_priv(dev);
	adap = pi->adapter;
	qidx = skb->queue_mapping;
	q = &adap->sge.ethtxq[qidx + pi->first_qset];

	left = (व्योम *)q->q.stat - pos;
	अगर (!left)
		pos = q->q.desc;

	cpl = (काष्ठा cpl_tx_pkt_core *)pos;

	cntrl = TXPKT_L4CSUM_DIS_F | TXPKT_IPCSUM_DIS_F;
	ctrl0 = TXPKT_OPCODE_V(CPL_TX_PKT_XT) | TXPKT_INTF_V(pi->tx_chan) |
			       TXPKT_PF_V(adap->pf);
	अगर (skb_vlan_tag_present(skb)) अणु
		q->vlan_ins++;
		cntrl |= TXPKT_VLAN_VLD_F | TXPKT_VLAN_V(skb_vlan_tag_get(skb));
	पूर्ण

	cpl->ctrl0 = htonl(ctrl0);
	cpl->pack = htons(0);
	cpl->len = htons(skb->len);
	cpl->ctrl1 = cpu_to_be64(cntrl);

	pos += माप(काष्ठा cpl_tx_pkt_core);
	/* Copy ESN info क्रम HW */
	अगर (sa_entry->esn)
		pos = copy_esn_pktxt(skb, dev, pos, sa_entry);
	वापस pos;
पूर्ण

अटल व्योम *copy_key_cpltx_pktxt(काष्ठा sk_buff *skb,
				  काष्ठा net_device *dev,
				  व्योम *pos,
				  काष्ठा ipsec_sa_entry *sa_entry)
अणु
	काष्ठा _key_ctx *key_ctx;
	पूर्णांक left, eoq, key_len;
	काष्ठा sge_eth_txq *q;
	काष्ठा adapter *adap;
	काष्ठा port_info *pi;
	अचिन्हित पूर्णांक qidx;

	pi = netdev_priv(dev);
	adap = pi->adapter;
	qidx = skb->queue_mapping;
	q = &adap->sge.ethtxq[qidx + pi->first_qset];
	key_len = sa_entry->kctx_len;

	/* end of queue, reset pos to start of queue */
	eoq = (व्योम *)q->q.stat - pos;
	left = eoq;
	अगर (!eoq) अणु
		pos = q->q.desc;
		left = 64 * q->q.size;
	पूर्ण

	/* Copy the Key context header */
	key_ctx = (काष्ठा _key_ctx *)pos;
	key_ctx->ctx_hdr = sa_entry->key_ctx_hdr;
	स_नकल(key_ctx->salt, sa_entry->salt, MAX_SALT);
	pos += माप(काष्ठा _key_ctx);
	left -= माप(काष्ठा _key_ctx);

	अगर (likely(key_len <= left)) अणु
		स_नकल(key_ctx->key, sa_entry->key, key_len);
		pos += key_len;
	पूर्ण अन्यथा अणु
		स_नकल(pos, sa_entry->key, left);
		स_नकल(q->q.desc, sa_entry->key + left,
		       key_len - left);
		pos = (u8 *)q->q.desc + (key_len - left);
	पूर्ण
	/* Copy CPL TX PKT XT */
	pos = copy_cpltx_pktxt(skb, dev, pos, sa_entry);

	वापस pos;
पूर्ण

अटल व्योम *ch_ipsec_crypto_wreq(काष्ठा sk_buff *skb,
				  काष्ठा net_device *dev,
				  व्योम *pos,
				  पूर्णांक credits,
				  काष्ठा ipsec_sa_entry *sa_entry)
अणु
	काष्ठा port_info *pi = netdev_priv(dev);
	काष्ठा adapter *adap = pi->adapter;
	अचिन्हित पूर्णांक ivsize = GCM_ESP_IV_SIZE;
	काष्ठा chcr_ipsec_wr *wr;
	bool immediate = false;
	u16 immdatalen = 0;
	अचिन्हित पूर्णांक flits;
	u32 ivinoffset;
	u32 aadstart;
	u32 aadstop;
	u32 ciphstart;
	u16 sc_more = 0;
	u32 ivdrop = 0;
	u32 esnlen = 0;
	u32 wr_mid;
	u16 ndesc;
	पूर्णांक qidx = skb_get_queue_mapping(skb);
	काष्ठा sge_eth_txq *q = &adap->sge.ethtxq[qidx + pi->first_qset];
	अचिन्हित पूर्णांक kctx_len = sa_entry->kctx_len;
	पूर्णांक qid = q->q.cntxt_id;

	atomic_inc(&adap->ch_ipsec_stats.ipsec_cnt);

	flits = calc_tx_sec_flits(skb, sa_entry, &immediate);
	ndesc = DIV_ROUND_UP(flits, 2);
	अगर (sa_entry->esn)
		ivdrop = 1;

	अगर (immediate)
		immdatalen = skb->len;

	अगर (sa_entry->esn) अणु
		esnlen = माप(काष्ठा chcr_ipsec_aaभाग);
		अगर (!skb_is_nonlinear(skb))
			sc_more  = 1;
	पूर्ण

	/* WR Header */
	wr = (काष्ठा chcr_ipsec_wr *)pos;
	wr->wreq.op_to_compl = htonl(FW_WR_OP_V(FW_ULPTX_WR));
	wr_mid = FW_CRYPTO_LOOKASIDE_WR_LEN16_V(ndesc);

	अगर (unlikely(credits < ETHTXQ_STOP_THRES)) अणु
		netअगर_tx_stop_queue(q->txq);
		q->q.stops++;
		अगर (!q->dbqt)
			wr_mid |= FW_WR_EQUEQ_F | FW_WR_EQUIQ_F;
	पूर्ण
	wr_mid |= FW_ULPTX_WR_DATA_F;
	wr->wreq.flowid_len16 = htonl(wr_mid);

	/* ULPTX */
	wr->req.ulptx.cmd_dest = FILL_ULPTX_CMD_DEST(pi->port_id, qid);
	wr->req.ulptx.len = htonl(ndesc - 1);

	/* Sub-command */
	wr->req.sc_imm.cmd_more = FILL_CMD_MORE(!immdatalen || sc_more);
	wr->req.sc_imm.len = cpu_to_be32(माप(काष्ठा cpl_tx_sec_pdu) +
					 माप(wr->req.key_ctx) +
					 kctx_len +
					 माप(काष्ठा cpl_tx_pkt_core) +
					 esnlen +
					 (esnlen ? 0 : immdatalen));

	/* CPL_SEC_PDU */
	ivinoffset = sa_entry->esn ? (ESN_IV_INSERT_OFFSET + 1) :
				     (skb_transport_offset(skb) +
				      माप(काष्ठा ip_esp_hdr) + 1);
	wr->req.sec_cpl.op_ivinsrtofst = htonl(
				CPL_TX_SEC_PDU_OPCODE_V(CPL_TX_SEC_PDU) |
				CPL_TX_SEC_PDU_CPLLEN_V(2) |
				CPL_TX_SEC_PDU_PLACEHOLDER_V(1) |
				CPL_TX_SEC_PDU_IVINSRTOFST_V(
							     ivinoffset));

	wr->req.sec_cpl.pldlen = htonl(skb->len + esnlen);
	aadstart = sa_entry->esn ? 1 : (skb_transport_offset(skb) + 1);
	aadstop = sa_entry->esn ? ESN_IV_INSERT_OFFSET :
				  (skb_transport_offset(skb) +
				   माप(काष्ठा ip_esp_hdr));
	ciphstart = skb_transport_offset(skb) + माप(काष्ठा ip_esp_hdr) +
		    GCM_ESP_IV_SIZE + 1;
	ciphstart += sa_entry->esn ?  esnlen : 0;

	wr->req.sec_cpl.aadstart_cipherstop_hi = FILL_SEC_CPL_CIPHERSTOP_HI(
							aadstart,
							aadstop,
							ciphstart, 0);

	wr->req.sec_cpl.cipherstop_lo_authinsert =
		FILL_SEC_CPL_AUTHINSERT(0, ciphstart,
					sa_entry->authsize,
					 sa_entry->authsize);
	wr->req.sec_cpl.seqno_numivs =
		FILL_SEC_CPL_SCMD0_SEQNO(CHCR_ENCRYPT_OP, 1,
					 CHCR_SCMD_CIPHER_MODE_AES_GCM,
					 CHCR_SCMD_AUTH_MODE_GHASH,
					 sa_entry->hmac_ctrl,
					 ivsize >> 1);
	wr->req.sec_cpl.ivgen_hdrlen =  FILL_SEC_CPL_IVGEN_HDRLEN(0, 0, 1,
								  0, ivdrop, 0);

	pos += माप(काष्ठा fw_ulptx_wr) +
	       माप(काष्ठा ulp_txpkt) +
	       माप(काष्ठा ulptx_idata) +
	       माप(काष्ठा cpl_tx_sec_pdu);

	pos = copy_key_cpltx_pktxt(skb, dev, pos, sa_entry);

	वापस pos;
पूर्ण

/**
 *      flits_to_desc - वापसs the num of Tx descriptors क्रम the given flits
 *      @n: the number of flits
 *
 *      Returns the number of Tx descriptors needed क्रम the supplied number
 *      of flits.
 */
अटल अचिन्हित पूर्णांक flits_to_desc(अचिन्हित पूर्णांक n)
अणु
	WARN_ON(n > SGE_MAX_WR_LEN / 8);
	वापस DIV_ROUND_UP(n, 8);
पूर्ण

अटल अचिन्हित पूर्णांक txq_avail(स्थिर काष्ठा sge_txq *q)
अणु
	वापस q->size - 1 - q->in_use;
पूर्ण

अटल व्योम eth_txq_stop(काष्ठा sge_eth_txq *q)
अणु
	netअगर_tx_stop_queue(q->txq);
	q->q.stops++;
पूर्ण

अटल व्योम txq_advance(काष्ठा sge_txq *q, अचिन्हित पूर्णांक n)
अणु
	q->in_use += n;
	q->pidx += n;
	अगर (q->pidx >= q->size)
		q->pidx -= q->size;
पूर्ण

/*
 *      ch_ipsec_xmit called from ULD Tx handler
 */
पूर्णांक ch_ipsec_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा xfrm_state *x = xfrm_input_state(skb);
	अचिन्हित पूर्णांक last_desc, ndesc, flits = 0;
	काष्ठा ipsec_sa_entry *sa_entry;
	u64 *pos, *end, *beक्रमe, *sgl;
	काष्ठा tx_sw_desc *sgl_sdesc;
	पूर्णांक qidx, left, credits;
	bool immediate = false;
	काष्ठा sge_eth_txq *q;
	काष्ठा adapter *adap;
	काष्ठा port_info *pi;
	काष्ठा sec_path *sp;

	अगर (!x->xso.offload_handle)
		वापस NETDEV_TX_BUSY;

	sa_entry = (काष्ठा ipsec_sa_entry *)x->xso.offload_handle;

	sp = skb_sec_path(skb);
	अगर (sp->len != 1) अणु
out_मुक्त:       dev_kमुक्त_skb_any(skb);
		वापस NETDEV_TX_OK;
	पूर्ण

	pi = netdev_priv(dev);
	adap = pi->adapter;
	qidx = skb->queue_mapping;
	q = &adap->sge.ethtxq[qidx + pi->first_qset];

	cxgb4_reclaim_completed_tx(adap, &q->q, true);

	flits = calc_tx_sec_flits(skb, sa_entry, &immediate);
	ndesc = flits_to_desc(flits);
	credits = txq_avail(&q->q) - ndesc;

	अगर (unlikely(credits < 0)) अणु
		eth_txq_stop(q);
		dev_err(adap->pdev_dev,
			"%s: Tx ring %u full while queue awake! cred:%d %d %d flits:%d\n",
			dev->name, qidx, credits, ndesc, txq_avail(&q->q),
			flits);
		वापस NETDEV_TX_BUSY;
	पूर्ण

	last_desc = q->q.pidx + ndesc - 1;
	अगर (last_desc >= q->q.size)
		last_desc -= q->q.size;
	sgl_sdesc = &q->q.sdesc[last_desc];

	अगर (!immediate &&
	    unlikely(cxgb4_map_skb(adap->pdev_dev, skb, sgl_sdesc->addr) < 0)) अणु
		स_रखो(sgl_sdesc->addr, 0, माप(sgl_sdesc->addr));
		q->mapping_err++;
		जाओ out_मुक्त;
	पूर्ण

	pos = (u64 *)&q->q.desc[q->q.pidx];
	beक्रमe = (u64 *)pos;
	end = (u64 *)pos + flits;
	/* Setup IPSec CPL */
	pos = (व्योम *)ch_ipsec_crypto_wreq(skb, dev, (व्योम *)pos,
					   credits, sa_entry);
	अगर (beक्रमe > (u64 *)pos) अणु
		left = (u8 *)end - (u8 *)q->q.stat;
		end = (व्योम *)q->q.desc + left;
	पूर्ण
	अगर (pos == (u64 *)q->q.stat) अणु
		left = (u8 *)end - (u8 *)q->q.stat;
		end = (व्योम *)q->q.desc + left;
		pos = (व्योम *)q->q.desc;
	पूर्ण

	sgl = (व्योम *)pos;
	अगर (immediate) अणु
		cxgb4_अंतरभूत_tx_skb(skb, &q->q, sgl);
		dev_consume_skb_any(skb);
	पूर्ण अन्यथा अणु
		cxgb4_ग_लिखो_sgl(skb, &q->q, (व्योम *)sgl, end,
				0, sgl_sdesc->addr);
		skb_orphan(skb);
		sgl_sdesc->skb = skb;
	पूर्ण
	txq_advance(&q->q, ndesc);

	cxgb4_ring_tx_db(adap, &q->q, ndesc);
	वापस NETDEV_TX_OK;
पूर्ण

अटल पूर्णांक __init ch_ipsec_init(व्योम)
अणु
	cxgb4_रेजिस्टर_uld(CXGB4_ULD_IPSEC, &ch_ipsec_uld_info);

	वापस 0;
पूर्ण

अटल व्योम __निकास ch_ipsec_निकास(व्योम)
अणु
	काष्ठा ipsec_uld_ctx *u_ctx, *पंचांगp;
	काष्ठा adapter *adap;

	mutex_lock(&dev_mutex);
	list_क्रम_each_entry_safe(u_ctx, पंचांगp, &uld_ctx_list, entry) अणु
		adap = pci_get_drvdata(u_ctx->lldi.pdev);
		atomic_set(&adap->ch_ipsec_stats.ipsec_cnt, 0);
		list_del(&u_ctx->entry);
		kमुक्त(u_ctx);
	पूर्ण
	mutex_unlock(&dev_mutex);
	cxgb4_unरेजिस्टर_uld(CXGB4_ULD_IPSEC);
पूर्ण

module_init(ch_ipsec_init);
module_निकास(ch_ipsec_निकास);

MODULE_DESCRIPTION("Crypto IPSEC for Chelsio Terminator cards.");
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Chelsio Communications");
MODULE_VERSION(CHIPSEC_DRV_VERSION);

