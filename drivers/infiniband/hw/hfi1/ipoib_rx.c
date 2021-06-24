<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0 OR BSD-3-Clause)
/*
 * Copyright(c) 2020 Intel Corporation.
 *
 */

#समावेश "netdev.h"
#समावेश "ipoib.h"

#घोषणा HFI1_IPOIB_SKB_PAD ((NET_SKB_PAD) + (NET_IP_ALIGN))

अटल व्योम copy_ipoib_buf(काष्ठा sk_buff *skb, व्योम *data, पूर्णांक size)
अणु
	व्योम *dst_data;

	skb_checksum_none_निश्चित(skb);
	skb->protocol = *((__be16 *)data);

	dst_data = skb_put(skb, size);
	स_नकल(dst_data, data, size);
	skb->mac_header = HFI1_IPOIB_PSEUDO_LEN;
	skb_pull(skb, HFI1_IPOIB_ENCAP_LEN);
पूर्ण

अटल काष्ठा sk_buff *prepare_frag_skb(काष्ठा napi_काष्ठा *napi, पूर्णांक size)
अणु
	काष्ठा sk_buff *skb;
	पूर्णांक skb_size = SKB_DATA_ALIGN(size + HFI1_IPOIB_SKB_PAD);
	व्योम *frag;

	skb_size += SKB_DATA_ALIGN(माप(काष्ठा skb_shared_info));
	skb_size = SKB_DATA_ALIGN(skb_size);
	frag = napi_alloc_frag(skb_size);

	अगर (unlikely(!frag))
		वापस napi_alloc_skb(napi, size);

	skb = build_skb(frag, skb_size);

	अगर (unlikely(!skb)) अणु
		skb_मुक्त_frag(frag);
		वापस शून्य;
	पूर्ण

	skb_reserve(skb, HFI1_IPOIB_SKB_PAD);
	वापस skb;
पूर्ण

काष्ठा sk_buff *hfi1_ipoib_prepare_skb(काष्ठा hfi1_netdev_rxq *rxq,
				       पूर्णांक size, व्योम *data)
अणु
	काष्ठा napi_काष्ठा *napi = &rxq->napi;
	पूर्णांक skb_size = size + HFI1_IPOIB_ENCAP_LEN;
	काष्ठा sk_buff *skb;

	/*
	 * For smaller(4k + skb overhead) allocations we will go using
	 * napi cache. Otherwise we will try to use napi frag cache.
	 */
	अगर (size <= SKB_WITH_OVERHEAD(PAGE_SIZE))
		skb = napi_alloc_skb(napi, skb_size);
	अन्यथा
		skb = prepare_frag_skb(napi, skb_size);

	अगर (unlikely(!skb))
		वापस शून्य;

	copy_ipoib_buf(skb, data, size);

	वापस skb;
पूर्ण

पूर्णांक hfi1_ipoib_rxq_init(काष्ठा net_device *netdev)
अणु
	काष्ठा hfi1_ipoib_dev_priv *ipoib_priv = hfi1_ipoib_priv(netdev);
	काष्ठा hfi1_devdata *dd = ipoib_priv->dd;
	पूर्णांक ret;

	ret = hfi1_netdev_rx_init(dd);
	अगर (ret)
		वापस ret;

	hfi1_init_aip_rsm(dd);

	वापस ret;
पूर्ण

व्योम hfi1_ipoib_rxq_deinit(काष्ठा net_device *netdev)
अणु
	काष्ठा hfi1_ipoib_dev_priv *ipoib_priv = hfi1_ipoib_priv(netdev);
	काष्ठा hfi1_devdata *dd = ipoib_priv->dd;

	hfi1_deinit_aip_rsm(dd);
	hfi1_netdev_rx_destroy(dd);
पूर्ण
