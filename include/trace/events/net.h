<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM net

#अगर !defined(_TRACE_NET_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _TRACE_NET_H

#समावेश <linux/skbuff.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/ip.h>
#समावेश <linux/tracepoपूर्णांक.h>

TRACE_EVENT(net_dev_start_xmit,

	TP_PROTO(स्थिर काष्ठा sk_buff *skb, स्थिर काष्ठा net_device *dev),

	TP_ARGS(skb, dev),

	TP_STRUCT__entry(
		__string(	name,			dev->name	)
		__field(	u16,			queue_mapping	)
		__field(	स्थिर व्योम *,		skbaddr		)
		__field(	bool,			vlan_tagged	)
		__field(	u16,			vlan_proto	)
		__field(	u16,			vlan_tci	)
		__field(	u16,			protocol	)
		__field(	u8,			ip_summed	)
		__field(	अचिन्हित पूर्णांक,		len		)
		__field(	अचिन्हित पूर्णांक,		data_len	)
		__field(	पूर्णांक,			network_offset	)
		__field(	bool,			transport_offset_valid)
		__field(	पूर्णांक,			transport_offset)
		__field(	u8,			tx_flags	)
		__field(	u16,			gso_size	)
		__field(	u16,			gso_segs	)
		__field(	u16,			gso_type	)
	),

	TP_fast_assign(
		__assign_str(name, dev->name);
		__entry->queue_mapping = skb->queue_mapping;
		__entry->skbaddr = skb;
		__entry->vlan_tagged = skb_vlan_tag_present(skb);
		__entry->vlan_proto = ntohs(skb->vlan_proto);
		__entry->vlan_tci = skb_vlan_tag_get(skb);
		__entry->protocol = ntohs(skb->protocol);
		__entry->ip_summed = skb->ip_summed;
		__entry->len = skb->len;
		__entry->data_len = skb->data_len;
		__entry->network_offset = skb_network_offset(skb);
		__entry->transport_offset_valid =
			skb_transport_header_was_set(skb);
		__entry->transport_offset = skb_transport_offset(skb);
		__entry->tx_flags = skb_shinfo(skb)->tx_flags;
		__entry->gso_size = skb_shinfo(skb)->gso_size;
		__entry->gso_segs = skb_shinfo(skb)->gso_segs;
		__entry->gso_type = skb_shinfo(skb)->gso_type;
	),

	TP_prपूर्णांकk("dev=%s queue_mapping=%u skbaddr=%p vlan_tagged=%d vlan_proto=0x%04x vlan_tci=0x%04x protocol=0x%04x ip_summed=%d len=%u data_len=%u network_offset=%d transport_offset_valid=%d transport_offset=%d tx_flags=%d gso_size=%d gso_segs=%d gso_type=%#x",
		  __get_str(name), __entry->queue_mapping, __entry->skbaddr,
		  __entry->vlan_tagged, __entry->vlan_proto, __entry->vlan_tci,
		  __entry->protocol, __entry->ip_summed, __entry->len,
		  __entry->data_len,
		  __entry->network_offset, __entry->transport_offset_valid,
		  __entry->transport_offset, __entry->tx_flags,
		  __entry->gso_size, __entry->gso_segs, __entry->gso_type)
);

TRACE_EVENT(net_dev_xmit,

	TP_PROTO(काष्ठा sk_buff *skb,
		 पूर्णांक rc,
		 काष्ठा net_device *dev,
		 अचिन्हित पूर्णांक skb_len),

	TP_ARGS(skb, rc, dev, skb_len),

	TP_STRUCT__entry(
		__field(	व्योम *,		skbaddr		)
		__field(	अचिन्हित पूर्णांक,	len		)
		__field(	पूर्णांक,		rc		)
		__string(	name,		dev->name	)
	),

	TP_fast_assign(
		__entry->skbaddr = skb;
		__entry->len = skb_len;
		__entry->rc = rc;
		__assign_str(name, dev->name);
	),

	TP_prपूर्णांकk("dev=%s skbaddr=%p len=%u rc=%d",
		__get_str(name), __entry->skbaddr, __entry->len, __entry->rc)
);

TRACE_EVENT(net_dev_xmit_समयout,

	TP_PROTO(काष्ठा net_device *dev,
		 पूर्णांक queue_index),

	TP_ARGS(dev, queue_index),

	TP_STRUCT__entry(
		__string(	name,		dev->name	)
		__string(	driver,		netdev_drivername(dev))
		__field(	पूर्णांक,		queue_index	)
	),

	TP_fast_assign(
		__assign_str(name, dev->name);
		__assign_str(driver, netdev_drivername(dev));
		__entry->queue_index = queue_index;
	),

	TP_prपूर्णांकk("dev=%s driver=%s queue=%d",
		__get_str(name), __get_str(driver), __entry->queue_index)
);

DECLARE_EVENT_CLASS(net_dev_ढाँचा,

	TP_PROTO(काष्ठा sk_buff *skb),

	TP_ARGS(skb),

	TP_STRUCT__entry(
		__field(	व्योम *,		skbaddr		)
		__field(	अचिन्हित पूर्णांक,	len		)
		__string(	name,		skb->dev->name	)
	),

	TP_fast_assign(
		__entry->skbaddr = skb;
		__entry->len = skb->len;
		__assign_str(name, skb->dev->name);
	),

	TP_prपूर्णांकk("dev=%s skbaddr=%p len=%u",
		__get_str(name), __entry->skbaddr, __entry->len)
)

DEFINE_EVENT(net_dev_ढाँचा, net_dev_queue,

	TP_PROTO(काष्ठा sk_buff *skb),

	TP_ARGS(skb)
);

DEFINE_EVENT(net_dev_ढाँचा, netअगर_receive_skb,

	TP_PROTO(काष्ठा sk_buff *skb),

	TP_ARGS(skb)
);

DEFINE_EVENT(net_dev_ढाँचा, netअगर_rx,

	TP_PROTO(काष्ठा sk_buff *skb),

	TP_ARGS(skb)
);

DECLARE_EVENT_CLASS(net_dev_rx_verbose_ढाँचा,

	TP_PROTO(स्थिर काष्ठा sk_buff *skb),

	TP_ARGS(skb),

	TP_STRUCT__entry(
		__string(	name,			skb->dev->name	)
		__field(	अचिन्हित पूर्णांक,		napi_id		)
		__field(	u16,			queue_mapping	)
		__field(	स्थिर व्योम *,		skbaddr		)
		__field(	bool,			vlan_tagged	)
		__field(	u16,			vlan_proto	)
		__field(	u16,			vlan_tci	)
		__field(	u16,			protocol	)
		__field(	u8,			ip_summed	)
		__field(	u32,			hash		)
		__field(	bool,			l4_hash		)
		__field(	अचिन्हित पूर्णांक,		len		)
		__field(	अचिन्हित पूर्णांक,		data_len	)
		__field(	अचिन्हित पूर्णांक,		truesize	)
		__field(	bool,			mac_header_valid)
		__field(	पूर्णांक,			mac_header	)
		__field(	अचिन्हित अक्षर,		nr_frags	)
		__field(	u16,			gso_size	)
		__field(	u16,			gso_type	)
	),

	TP_fast_assign(
		__assign_str(name, skb->dev->name);
#अगर_घोषित CONFIG_NET_RX_BUSY_POLL
		__entry->napi_id = skb->napi_id;
#अन्यथा
		__entry->napi_id = 0;
#पूर्ण_अगर
		__entry->queue_mapping = skb->queue_mapping;
		__entry->skbaddr = skb;
		__entry->vlan_tagged = skb_vlan_tag_present(skb);
		__entry->vlan_proto = ntohs(skb->vlan_proto);
		__entry->vlan_tci = skb_vlan_tag_get(skb);
		__entry->protocol = ntohs(skb->protocol);
		__entry->ip_summed = skb->ip_summed;
		__entry->hash = skb->hash;
		__entry->l4_hash = skb->l4_hash;
		__entry->len = skb->len;
		__entry->data_len = skb->data_len;
		__entry->truesize = skb->truesize;
		__entry->mac_header_valid = skb_mac_header_was_set(skb);
		__entry->mac_header = skb_mac_header(skb) - skb->data;
		__entry->nr_frags = skb_shinfo(skb)->nr_frags;
		__entry->gso_size = skb_shinfo(skb)->gso_size;
		__entry->gso_type = skb_shinfo(skb)->gso_type;
	),

	TP_prपूर्णांकk("dev=%s napi_id=%#x queue_mapping=%u skbaddr=%p vlan_tagged=%d vlan_proto=0x%04x vlan_tci=0x%04x protocol=0x%04x ip_summed=%d hash=0x%08x l4_hash=%d len=%u data_len=%u truesize=%u mac_header_valid=%d mac_header=%d nr_frags=%d gso_size=%d gso_type=%#x",
		  __get_str(name), __entry->napi_id, __entry->queue_mapping,
		  __entry->skbaddr, __entry->vlan_tagged, __entry->vlan_proto,
		  __entry->vlan_tci, __entry->protocol, __entry->ip_summed,
		  __entry->hash, __entry->l4_hash, __entry->len,
		  __entry->data_len, __entry->truesize,
		  __entry->mac_header_valid, __entry->mac_header,
		  __entry->nr_frags, __entry->gso_size, __entry->gso_type)
);

DEFINE_EVENT(net_dev_rx_verbose_ढाँचा, napi_gro_frags_entry,

	TP_PROTO(स्थिर काष्ठा sk_buff *skb),

	TP_ARGS(skb)
);

DEFINE_EVENT(net_dev_rx_verbose_ढाँचा, napi_gro_receive_entry,

	TP_PROTO(स्थिर काष्ठा sk_buff *skb),

	TP_ARGS(skb)
);

DEFINE_EVENT(net_dev_rx_verbose_ढाँचा, netअगर_receive_skb_entry,

	TP_PROTO(स्थिर काष्ठा sk_buff *skb),

	TP_ARGS(skb)
);

DEFINE_EVENT(net_dev_rx_verbose_ढाँचा, netअगर_receive_skb_list_entry,

	TP_PROTO(स्थिर काष्ठा sk_buff *skb),

	TP_ARGS(skb)
);

DEFINE_EVENT(net_dev_rx_verbose_ढाँचा, netअगर_rx_entry,

	TP_PROTO(स्थिर काष्ठा sk_buff *skb),

	TP_ARGS(skb)
);

DEFINE_EVENT(net_dev_rx_verbose_ढाँचा, netअगर_rx_ni_entry,

	TP_PROTO(स्थिर काष्ठा sk_buff *skb),

	TP_ARGS(skb)
);

DECLARE_EVENT_CLASS(net_dev_rx_निकास_ढाँचा,

	TP_PROTO(पूर्णांक ret),

	TP_ARGS(ret),

	TP_STRUCT__entry(
		__field(पूर्णांक,	ret)
	),

	TP_fast_assign(
		__entry->ret = ret;
	),

	TP_prपूर्णांकk("ret=%d", __entry->ret)
);

DEFINE_EVENT(net_dev_rx_निकास_ढाँचा, napi_gro_frags_निकास,

	TP_PROTO(पूर्णांक ret),

	TP_ARGS(ret)
);

DEFINE_EVENT(net_dev_rx_निकास_ढाँचा, napi_gro_receive_निकास,

	TP_PROTO(पूर्णांक ret),

	TP_ARGS(ret)
);

DEFINE_EVENT(net_dev_rx_निकास_ढाँचा, netअगर_receive_skb_निकास,

	TP_PROTO(पूर्णांक ret),

	TP_ARGS(ret)
);

DEFINE_EVENT(net_dev_rx_निकास_ढाँचा, netअगर_rx_निकास,

	TP_PROTO(पूर्णांक ret),

	TP_ARGS(ret)
);

DEFINE_EVENT(net_dev_rx_निकास_ढाँचा, netअगर_rx_ni_निकास,

	TP_PROTO(पूर्णांक ret),

	TP_ARGS(ret)
);

DEFINE_EVENT(net_dev_rx_निकास_ढाँचा, netअगर_receive_skb_list_निकास,

	TP_PROTO(पूर्णांक ret),

	TP_ARGS(ret)
);

#पूर्ण_अगर /* _TRACE_NET_H */

/* This part must be outside protection */
#समावेश <trace/define_trace.h>
