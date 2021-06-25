<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-2-Clause) */
/* Copyright (C) 2016-2019 Netronome Systems, Inc. */

#अगर_अघोषित NFP_CCM_H
#घोषणा NFP_CCM_H 1

#समावेश <linux/biपंचांगap.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/रुको.h>

काष्ठा nfp_app;
काष्ठा nfp_net;

/* Firmware ABI */

क्रमागत nfp_ccm_type अणु
	NFP_CCM_TYPE_BPF_MAP_ALLOC	= 1,
	NFP_CCM_TYPE_BPF_MAP_FREE	= 2,
	NFP_CCM_TYPE_BPF_MAP_LOOKUP	= 3,
	NFP_CCM_TYPE_BPF_MAP_UPDATE	= 4,
	NFP_CCM_TYPE_BPF_MAP_DELETE	= 5,
	NFP_CCM_TYPE_BPF_MAP_GETNEXT	= 6,
	NFP_CCM_TYPE_BPF_MAP_GETFIRST	= 7,
	NFP_CCM_TYPE_BPF_BPF_EVENT	= 8,
	NFP_CCM_TYPE_CRYPTO_RESET	= 9,
	NFP_CCM_TYPE_CRYPTO_ADD		= 10,
	NFP_CCM_TYPE_CRYPTO_DEL		= 11,
	NFP_CCM_TYPE_CRYPTO_UPDATE	= 12,
	NFP_CCM_TYPE_CRYPTO_RESYNC	= 13,
	__NFP_CCM_TYPE_MAX,
पूर्ण;

#घोषणा NFP_CCM_ABI_VERSION		1

#घोषणा NFP_CCM_TYPE_REPLY_BIT		7
#घोषणा __NFP_CCM_REPLY(req)		(BIT(NFP_CCM_TYPE_REPLY_BIT) | (req))

काष्ठा nfp_ccm_hdr अणु
	जोड़ अणु
		काष्ठा अणु
			u8 type;
			u8 ver;
			__be16 tag;
		पूर्ण;
		__be32 raw;
	पूर्ण;
पूर्ण;

अटल अंतरभूत u8 nfp_ccm_get_type(काष्ठा sk_buff *skb)
अणु
	काष्ठा nfp_ccm_hdr *hdr;

	hdr = (काष्ठा nfp_ccm_hdr *)skb->data;

	वापस hdr->type;
पूर्ण

अटल अंतरभूत __be16 __nfp_ccm_get_tag(काष्ठा sk_buff *skb)
अणु
	काष्ठा nfp_ccm_hdr *hdr;

	hdr = (काष्ठा nfp_ccm_hdr *)skb->data;

	वापस hdr->tag;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक nfp_ccm_get_tag(काष्ठा sk_buff *skb)
अणु
	वापस be16_to_cpu(__nfp_ccm_get_tag(skb));
पूर्ण

#घोषणा NFP_NET_MBOX_TLV_TYPE		GENMASK(31, 16)
#घोषणा NFP_NET_MBOX_TLV_LEN		GENMASK(15, 0)

क्रमागत nfp_ccm_mbox_tlv_type अणु
	NFP_NET_MBOX_TLV_TYPE_UNKNOWN	= 0,
	NFP_NET_MBOX_TLV_TYPE_END	= 1,
	NFP_NET_MBOX_TLV_TYPE_MSG	= 2,
	NFP_NET_MBOX_TLV_TYPE_MSG_NOSUP	= 3,
	NFP_NET_MBOX_TLV_TYPE_RESV	= 4,
पूर्ण;

/* Implementation */

/**
 * काष्ठा nfp_ccm - common control message handling
 * @app:		APP handle
 *
 * @tag_allocator:	biपंचांगap of control message tags in use
 * @tag_alloc_next:	next tag bit to allocate
 * @tag_alloc_last:	next tag bit to be मुक्तd
 *
 * @replies:		received cmsg replies रुकोing to be consumed
 * @wq:			work queue क्रम रुकोing क्रम cmsg replies
 */
काष्ठा nfp_ccm अणु
	काष्ठा nfp_app *app;

	DECLARE_BITMAP(tag_allocator, U16_MAX + 1);
	u16 tag_alloc_next;
	u16 tag_alloc_last;

	काष्ठा sk_buff_head replies;
	रुको_queue_head_t wq;
पूर्ण;

पूर्णांक nfp_ccm_init(काष्ठा nfp_ccm *ccm, काष्ठा nfp_app *app);
व्योम nfp_ccm_clean(काष्ठा nfp_ccm *ccm);
व्योम nfp_ccm_rx(काष्ठा nfp_ccm *ccm, काष्ठा sk_buff *skb);
काष्ठा sk_buff *
nfp_ccm_communicate(काष्ठा nfp_ccm *ccm, काष्ठा sk_buff *skb,
		    क्रमागत nfp_ccm_type type, अचिन्हित पूर्णांक reply_size);

पूर्णांक nfp_ccm_mbox_alloc(काष्ठा nfp_net *nn);
व्योम nfp_ccm_mbox_मुक्त(काष्ठा nfp_net *nn);
पूर्णांक nfp_ccm_mbox_init(काष्ठा nfp_net *nn);
व्योम nfp_ccm_mbox_clean(काष्ठा nfp_net *nn);
bool nfp_ccm_mbox_fits(काष्ठा nfp_net *nn, अचिन्हित पूर्णांक size);
काष्ठा sk_buff *
nfp_ccm_mbox_msg_alloc(काष्ठा nfp_net *nn, अचिन्हित पूर्णांक req_size,
		       अचिन्हित पूर्णांक reply_size, gfp_t flags);
पूर्णांक __nfp_ccm_mbox_communicate(काष्ठा nfp_net *nn, काष्ठा sk_buff *skb,
			       क्रमागत nfp_ccm_type type,
			       अचिन्हित पूर्णांक reply_size,
			       अचिन्हित पूर्णांक max_reply_size, bool critical);
पूर्णांक nfp_ccm_mbox_communicate(काष्ठा nfp_net *nn, काष्ठा sk_buff *skb,
			     क्रमागत nfp_ccm_type type,
			     अचिन्हित पूर्णांक reply_size,
			     अचिन्हित पूर्णांक max_reply_size);
पूर्णांक nfp_ccm_mbox_post(काष्ठा nfp_net *nn, काष्ठा sk_buff *skb,
		      क्रमागत nfp_ccm_type type, अचिन्हित पूर्णांक max_reply_size);
#पूर्ण_अगर
