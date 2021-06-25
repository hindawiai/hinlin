<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright(c) 2009 Intel Corporation. All rights reserved.
 *
 * Maपूर्णांकained at www.Open-FCoE.org
 */

#अगर_अघोषित _FCOE_H_
#घोषणा _FCOE_H_

#समावेश <linux/skbuff.h>
#समावेश <linux/kthपढ़ो.h>

#घोषणा FCOE_MAX_QUEUE_DEPTH	256
#घोषणा FCOE_MIN_QUEUE_DEPTH	32

#घोषणा FCOE_WORD_TO_BYTE	4

#घोषणा FCOE_VERSION	"0.1"
#घोषणा FCOE_NAME	"fcoe"
#घोषणा FCOE_VENDOR	"Open-FCoE.org"

#घोषणा FCOE_MAX_LUN		0xFFFF
#घोषणा FCOE_MAX_FCP_TARGET	256

#घोषणा FCOE_MAX_OUTSTANDING_COMMANDS	1024

#घोषणा FCOE_MIN_XID		0x0000	/* the min xid supported by fcoe_sw */
#घोषणा FCOE_MAX_XID		0x0FFF	/* the max xid supported by fcoe_sw */

बाह्य अचिन्हित पूर्णांक fcoe_debug_logging;

#घोषणा FCOE_LOGGING	    0x01 /* General logging, not categorized */
#घोषणा FCOE_NETDEV_LOGGING 0x02 /* Netdevice logging */

#घोषणा FCOE_CHECK_LOGGING(LEVEL, CMD)					\
करो अणु                                                            	\
	अगर (unlikely(fcoe_debug_logging & LEVEL))			\
		करो अणु							\
			CMD;						\
		पूर्ण जबतक (0);						\
पूर्ण जबतक (0)

#घोषणा FCOE_DBG(fmt, args...)						\
	FCOE_CHECK_LOGGING(FCOE_LOGGING,				\
			   pr_info("fcoe: " fmt, ##args);)

#घोषणा FCOE_NETDEV_DBG(netdev, fmt, args...)			\
	FCOE_CHECK_LOGGING(FCOE_NETDEV_LOGGING,			\
			   pr_info("fcoe: %s: " fmt,		\
				   netdev->name, ##args);)

/**
 * काष्ठा fcoe_पूर्णांकerface - A FCoE पूर्णांकerface
 * @list:	      Handle क्रम a list of FCoE पूर्णांकerfaces
 * @netdev:	      The associated net device
 * @fcoe_packet_type: FCoE packet type
 * @fip_packet_type:  FIP packet type
 * @oem:	      The offload exchange manager क्रम all local port
 *		      instances associated with this port
 * @हटाओd:	      Indicates fcoe पूर्णांकerface हटाओd from net device
 * @priority:	      Priority क्रम the FCoE packet (DCB)
 * This काष्ठाure is 1:1 with a net device.
 */
काष्ठा fcoe_पूर्णांकerface अणु
	काष्ठा list_head   list;
	काष्ठा net_device  *netdev;
	काष्ठा net_device  *realdev;
	काष्ठा packet_type fcoe_packet_type;
	काष्ठा packet_type fip_packet_type;
	काष्ठा packet_type fip_vlan_packet_type;
	काष्ठा fc_exch_mgr *oem;
	u8	हटाओd;
	u8	priority;
पूर्ण;

#घोषणा fcoe_to_ctlr(x)						\
	(काष्ठा fcoe_ctlr *)(((काष्ठा fcoe_ctlr *)(x)) - 1)

#घोषणा fcoe_from_ctlr(x)			\
	((काष्ठा fcoe_पूर्णांकerface *)((x) + 1))

/**
 * fcoe_netdev() - Return the net device associated with a local port
 * @lport: The local port to get the net device from
 */
अटल अंतरभूत काष्ठा net_device *fcoe_netdev(स्थिर काष्ठा fc_lport *lport)
अणु
	वापस ((काष्ठा fcoe_पूर्णांकerface *)
			((काष्ठा fcoe_port *)lport_priv(lport))->priv)->netdev;
पूर्ण

#पूर्ण_अगर /* _FCOE_H_ */
