<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * sctp_offload - GRO/GSO Offloading क्रम SCTP
 *
 * Copyright (C) 2015, Marcelo Ricarकरो Leitner <marcelo.leitner@gmail.com>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/kprobes.h>
#समावेश <linux/socket.h>
#समावेश <linux/sctp.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/module.h>
#समावेश <linux/kfअगरo.h>
#समावेश <linux/समय.स>
#समावेश <net/net_namespace.h>

#समावेश <linux/skbuff.h>
#समावेश <net/sctp/sctp.h>
#समावेश <net/sctp/checksum.h>
#समावेश <net/protocol.h>

अटल __le32 sctp_gso_make_checksum(काष्ठा sk_buff *skb)
अणु
	skb->ip_summed = CHECKSUM_NONE;
	skb->csum_not_inet = 0;
	/* csum and csum_start in GSO CB may be needed to करो the UDP
	 * checksum when it's a UDP tunneling packet.
	 */
	SKB_GSO_CB(skb)->csum = (__क्रमce __wsum)~0;
	SKB_GSO_CB(skb)->csum_start = skb_headroom(skb) + skb->len;
	वापस sctp_compute_cksum(skb, skb_transport_offset(skb));
पूर्ण

अटल काष्ठा sk_buff *sctp_gso_segment(काष्ठा sk_buff *skb,
					netdev_features_t features)
अणु
	काष्ठा sk_buff *segs = ERR_PTR(-EINVAL);
	काष्ठा sctphdr *sh;

	अगर (!skb_is_gso_sctp(skb))
		जाओ out;

	sh = sctp_hdr(skb);
	अगर (!pskb_may_pull(skb, माप(*sh)))
		जाओ out;

	__skb_pull(skb, माप(*sh));

	अगर (skb_gso_ok(skb, features | NETIF_F_GSO_ROBUST)) अणु
		/* Packet is from an untrusted source, reset gso_segs. */
		काष्ठा skb_shared_info *pinfo = skb_shinfo(skb);
		काष्ठा sk_buff *frag_iter;

		pinfo->gso_segs = 0;
		अगर (skb->len != skb->data_len) अणु
			/* Means we have chunks in here too */
			pinfo->gso_segs++;
		पूर्ण

		skb_walk_frags(skb, frag_iter)
			pinfo->gso_segs++;

		segs = शून्य;
		जाओ out;
	पूर्ण

	segs = skb_segment(skb, (features | NETIF_F_HW_CSUM) & ~NETIF_F_SG);
	अगर (IS_ERR(segs))
		जाओ out;

	/* All that is left is update SCTP CRC अगर necessary */
	अगर (!(features & NETIF_F_SCTP_CRC)) अणु
		क्रम (skb = segs; skb; skb = skb->next) अणु
			अगर (skb->ip_summed == CHECKSUM_PARTIAL) अणु
				sh = sctp_hdr(skb);
				sh->checksum = sctp_gso_make_checksum(skb);
			पूर्ण
		पूर्ण
	पूर्ण

out:
	वापस segs;
पूर्ण

अटल स्थिर काष्ठा net_offload sctp_offload = अणु
	.callbacks = अणु
		.gso_segment = sctp_gso_segment,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा net_offload sctp6_offload = अणु
	.callbacks = अणु
		.gso_segment = sctp_gso_segment,
	पूर्ण,
पूर्ण;

पूर्णांक __init sctp_offload_init(व्योम)
अणु
	पूर्णांक ret;

	ret = inet_add_offload(&sctp_offload, IPPROTO_SCTP);
	अगर (ret)
		जाओ out;

	ret = inet6_add_offload(&sctp6_offload, IPPROTO_SCTP);
	अगर (ret)
		जाओ ipv4;

	crc32c_csum_stub = &sctp_csum_ops;
	वापस ret;

ipv4:
	inet_del_offload(&sctp_offload, IPPROTO_SCTP);
out:
	वापस ret;
पूर्ण
