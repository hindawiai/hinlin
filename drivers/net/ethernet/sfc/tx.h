<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/****************************************************************************
 * Driver क्रम Solarflare network controllers and boards
 * Copyright 2005-2006 Fen Systems Ltd.
 * Copyright 2006-2015 Solarflare Communications Inc.
 */

#अगर_अघोषित EFX_TX_H
#घोषणा EFX_TX_H

#समावेश <linux/types.h>

/* Driver पूर्णांकernal tx-path related declarations. */

अचिन्हित पूर्णांक efx_tx_limit_len(काष्ठा efx_tx_queue *tx_queue,
			      dma_addr_t dma_addr, अचिन्हित पूर्णांक len);

u8 *efx_tx_get_copy_buffer_limited(काष्ठा efx_tx_queue *tx_queue,
				   काष्ठा efx_tx_buffer *buffer, माप_प्रकार len);

/* What TXQ type will satisfy the checksum offloads required क्रम this skb? */
अटल अंतरभूत अचिन्हित पूर्णांक efx_tx_csum_type_skb(काष्ठा sk_buff *skb)
अणु
	अगर (skb->ip_summed != CHECKSUM_PARTIAL)
		वापस 0; /* no checksum offload */

	अगर (skb->encapsulation &&
	    skb_checksum_start_offset(skb) == skb_inner_transport_offset(skb)) अणु
		/* we only advertise features क्रम IPv4 and IPv6 checksums on
		 * encapsulated packets, so अगर the checksum is क्रम the inner
		 * packet, it must be one of them; no further checking required.
		 */

		/* Do we also need to offload the outer header checksum? */
		अगर (skb_shinfo(skb)->gso_segs > 1 &&
		    !(skb_shinfo(skb)->gso_type & SKB_GSO_PARTIAL) &&
		    (skb_shinfo(skb)->gso_type & SKB_GSO_UDP_TUNNEL_CSUM))
			वापस EFX_TXQ_TYPE_OUTER_CSUM | EFX_TXQ_TYPE_INNER_CSUM;
		वापस EFX_TXQ_TYPE_INNER_CSUM;
	पूर्ण

	/* similarly, we only advertise features क्रम IPv4 and IPv6 checksums,
	 * so it must be one of them. No need क्रम further checks.
	 */
	वापस EFX_TXQ_TYPE_OUTER_CSUM;
पूर्ण
#पूर्ण_अगर /* EFX_TX_H */
