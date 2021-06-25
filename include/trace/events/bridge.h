<शैली गुरु>
#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM bridge

#अगर !defined(_TRACE_BRIDGE_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _TRACE_BRIDGE_H

#समावेश <linux/netdevice.h>
#समावेश <linux/tracepoपूर्णांक.h>

#समावेश "../../../net/bridge/br_private.h"

TRACE_EVENT(br_fdb_add,

	TP_PROTO(काष्ठा ndmsg *ndm, काष्ठा net_device *dev,
		 स्थिर अचिन्हित अक्षर *addr, u16 vid, u16 nlh_flags),

	TP_ARGS(ndm, dev, addr, vid, nlh_flags),

	TP_STRUCT__entry(
		__field(u8, ndm_flags)
		__string(dev, dev->name)
		__array(अचिन्हित अक्षर, addr, ETH_ALEN)
		__field(u16, vid)
		__field(u16, nlh_flags)
	),

	TP_fast_assign(
		__assign_str(dev, dev->name);
		स_नकल(__entry->addr, addr, ETH_ALEN);
		__entry->vid = vid;
		__entry->nlh_flags = nlh_flags;
		__entry->ndm_flags = ndm->ndm_flags;
	),

	TP_prपूर्णांकk("dev %s addr %02x:%02x:%02x:%02x:%02x:%02x vid %u nlh_flags %04x ndm_flags %02x",
		  __get_str(dev), __entry->addr[0], __entry->addr[1],
		  __entry->addr[2], __entry->addr[3], __entry->addr[4],
		  __entry->addr[5], __entry->vid,
		  __entry->nlh_flags, __entry->ndm_flags)
);

TRACE_EVENT(br_fdb_बाह्यal_learn_add,

	TP_PROTO(काष्ठा net_bridge *br, काष्ठा net_bridge_port *p,
		 स्थिर अचिन्हित अक्षर *addr, u16 vid),

	TP_ARGS(br, p, addr, vid),

	TP_STRUCT__entry(
		__string(br_dev, br->dev->name)
		__string(dev, p ? p->dev->name : "null")
		__array(अचिन्हित अक्षर, addr, ETH_ALEN)
		__field(u16, vid)
	),

	TP_fast_assign(
		__assign_str(br_dev, br->dev->name);
		__assign_str(dev, p ? p->dev->name : "null");
		स_नकल(__entry->addr, addr, ETH_ALEN);
		__entry->vid = vid;
	),

	TP_prपूर्णांकk("br_dev %s port %s addr %02x:%02x:%02x:%02x:%02x:%02x vid %u",
		  __get_str(br_dev), __get_str(dev), __entry->addr[0],
		  __entry->addr[1], __entry->addr[2], __entry->addr[3],
		  __entry->addr[4], __entry->addr[5], __entry->vid)
);

TRACE_EVENT(fdb_delete,

	TP_PROTO(काष्ठा net_bridge *br, काष्ठा net_bridge_fdb_entry *f),

	TP_ARGS(br, f),

	TP_STRUCT__entry(
		__string(br_dev, br->dev->name)
		__string(dev, f->dst ? f->dst->dev->name : "null")
		__array(अचिन्हित अक्षर, addr, ETH_ALEN)
		__field(u16, vid)
	),

	TP_fast_assign(
		__assign_str(br_dev, br->dev->name);
		__assign_str(dev, f->dst ? f->dst->dev->name : "null");
		स_नकल(__entry->addr, f->key.addr.addr, ETH_ALEN);
		__entry->vid = f->key.vlan_id;
	),

	TP_prपूर्णांकk("br_dev %s dev %s addr %02x:%02x:%02x:%02x:%02x:%02x vid %u",
		  __get_str(br_dev), __get_str(dev), __entry->addr[0],
		  __entry->addr[1], __entry->addr[2], __entry->addr[3],
		  __entry->addr[4], __entry->addr[5], __entry->vid)
);

TRACE_EVENT(br_fdb_update,

	TP_PROTO(काष्ठा net_bridge *br, काष्ठा net_bridge_port *source,
		 स्थिर अचिन्हित अक्षर *addr, u16 vid, अचिन्हित दीर्घ flags),

	TP_ARGS(br, source, addr, vid, flags),

	TP_STRUCT__entry(
		__string(br_dev, br->dev->name)
		__string(dev, source->dev->name)
		__array(अचिन्हित अक्षर, addr, ETH_ALEN)
		__field(u16, vid)
		__field(अचिन्हित दीर्घ, flags)
	),

	TP_fast_assign(
		__assign_str(br_dev, br->dev->name);
		__assign_str(dev, source->dev->name);
		स_नकल(__entry->addr, addr, ETH_ALEN);
		__entry->vid = vid;
		__entry->flags = flags;
	),

	TP_prपूर्णांकk("br_dev %s source %s addr %02x:%02x:%02x:%02x:%02x:%02x vid %u flags 0x%lx",
		  __get_str(br_dev), __get_str(dev), __entry->addr[0],
		  __entry->addr[1], __entry->addr[2], __entry->addr[3],
		  __entry->addr[4], __entry->addr[5], __entry->vid,
		  __entry->flags)
);


#पूर्ण_अगर /* _TRACE_BRIDGE_H */

/* This part must be outside protection */
#समावेश <trace/define_trace.h>
