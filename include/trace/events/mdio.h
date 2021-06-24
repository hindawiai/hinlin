<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM mdio

#अगर !defined(_TRACE_MDIO_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _TRACE_MDIO_H

#समावेश <linux/tracepoपूर्णांक.h>

TRACE_EVENT_CONDITION(mdio_access,

	TP_PROTO(काष्ठा mii_bus *bus, अक्षर पढ़ो,
		 u8 addr, अचिन्हित regnum, u16 val, पूर्णांक err),

	TP_ARGS(bus, पढ़ो, addr, regnum, val, err),

	TP_CONDITION(err >= 0),

	TP_STRUCT__entry(
		__array(अक्षर, busid, MII_BUS_ID_SIZE)
		__field(अक्षर, पढ़ो)
		__field(u8, addr)
		__field(u16, val)
		__field(अचिन्हित, regnum)
	),

	TP_fast_assign(
		म_नकलन(__entry->busid, bus->id, MII_BUS_ID_SIZE);
		__entry->पढ़ो = पढ़ो;
		__entry->addr = addr;
		__entry->regnum = regnum;
		__entry->val = val;
	),

	TP_prपूर्णांकk("%s %-5s phy:0x%02hhx reg:0x%02x val:0x%04hx",
		  __entry->busid, __entry->पढ़ो ? "read" : "write",
		  __entry->addr, __entry->regnum, __entry->val)
);

#पूर्ण_अगर /* अगर !defined(_TRACE_MDIO_H) || defined(TRACE_HEADER_MULTI_READ) */

/* This part must be outside protection */
#समावेश <trace/define_trace.h>
