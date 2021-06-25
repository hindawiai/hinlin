<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0 OR MIT) */
/*
 * Microsemi Ocelot Switch driver
 *
 * Copyright (c) 2017 Microsemi Corporation
 */

#अगर_अघोषित _MSCC_OCELOT_H_
#घोषणा _MSCC_OCELOT_H_

#समावेश <linux/bitops.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/net_tstamp.h>
#समावेश <linux/phy.h>
#समावेश <linux/phy/phy.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>

#समावेश <soc/mscc/ocelot_qsys.h>
#समावेश <soc/mscc/ocelot_sys.h>
#समावेश <soc/mscc/ocelot_dev.h>
#समावेश <soc/mscc/ocelot_ana.h>
#समावेश <soc/mscc/ocelot_ptp.h>
#समावेश <soc/mscc/ocelot.h>
#समावेश "ocelot_rew.h"
#समावेश "ocelot_qs.h"

#घोषणा OCELOT_BUFFER_CELL_SZ 60

#घोषणा OCELOT_STATS_CHECK_DELAY (2 * HZ)

#घोषणा OCELOT_PTP_QUEUE_SZ	128

काष्ठा ocelot_port_tc अणु
	bool block_shared;
	अचिन्हित दीर्घ offload_cnt;

	अचिन्हित दीर्घ police_id;
पूर्ण;

काष्ठा ocelot_port_निजी अणु
	काष्ठा ocelot_port port;
	काष्ठा net_device *dev;
	काष्ठा phy_device *phy;
	u8 chip_port;

	काष्ठा phy *serdes;

	काष्ठा ocelot_port_tc tc;
पूर्ण;

काष्ठा ocelot_dump_ctx अणु
	काष्ठा net_device *dev;
	काष्ठा sk_buff *skb;
	काष्ठा netlink_callback *cb;
	पूर्णांक idx;
पूर्ण;

/* MAC table entry types.
 * ENTRYTYPE_NORMAL is subject to aging.
 * ENTRYTYPE_LOCKED is not subject to aging.
 * ENTRYTYPE_MACv4 is not subject to aging. For IPv4 multicast.
 * ENTRYTYPE_MACv6 is not subject to aging. For IPv6 multicast.
 */
क्रमागत macaccess_entry_type अणु
	ENTRYTYPE_NORMAL = 0,
	ENTRYTYPE_LOCKED,
	ENTRYTYPE_MACv4,
	ENTRYTYPE_MACv6,
पूर्ण;

/* A (PGID) port mask काष्ठाure, encoding the 2^ocelot->num_phys_ports
 * possibilities of egress port masks क्रम L2 multicast traffic.
 * For a चयन with 9 user ports, there are 512 possible port masks, but the
 * hardware only has 46 inभागidual PGIDs that it can क्रमward multicast traffic
 * to. So we need a काष्ठाure that maps the limited PGID indices to the port
 * destinations requested by the user क्रम L2 multicast.
 */
काष्ठा ocelot_pgid अणु
	अचिन्हित दीर्घ ports;
	पूर्णांक index;
	refcount_t refcount;
	काष्ठा list_head list;
पूर्ण;

काष्ठा ocelot_multicast अणु
	काष्ठा list_head list;
	क्रमागत macaccess_entry_type entry_type;
	अचिन्हित अक्षर addr[ETH_ALEN];
	u16 vid;
	u16 ports;
	काष्ठा ocelot_pgid *pgid;
पूर्ण;

पूर्णांक ocelot_port_fdb_करो_dump(स्थिर अचिन्हित अक्षर *addr, u16 vid,
			    bool is_अटल, व्योम *data);
पूर्णांक ocelot_mact_learn(काष्ठा ocelot *ocelot, पूर्णांक port,
		      स्थिर अचिन्हित अक्षर mac[ETH_ALEN],
		      अचिन्हित पूर्णांक vid, क्रमागत macaccess_entry_type type);
पूर्णांक ocelot_mact_क्रमget(काष्ठा ocelot *ocelot,
		       स्थिर अचिन्हित अक्षर mac[ETH_ALEN], अचिन्हित पूर्णांक vid);
काष्ठा net_device *ocelot_port_to_netdev(काष्ठा ocelot *ocelot, पूर्णांक port);
पूर्णांक ocelot_netdev_to_port(काष्ठा net_device *dev);

u32 ocelot_port_पढ़ोl(काष्ठा ocelot_port *port, u32 reg);
व्योम ocelot_port_ग_लिखोl(काष्ठा ocelot_port *port, u32 val, u32 reg);

पूर्णांक ocelot_probe_port(काष्ठा ocelot *ocelot, पूर्णांक port, काष्ठा regmap *target,
		      काष्ठा phy_device *phy);
व्योम ocelot_release_port(काष्ठा ocelot_port *ocelot_port);
पूर्णांक ocelot_devlink_init(काष्ठा ocelot *ocelot);
व्योम ocelot_devlink_tearकरोwn(काष्ठा ocelot *ocelot);
पूर्णांक ocelot_port_devlink_init(काष्ठा ocelot *ocelot, पूर्णांक port,
			     क्रमागत devlink_port_flavour flavour);
व्योम ocelot_port_devlink_tearकरोwn(काष्ठा ocelot *ocelot, पूर्णांक port);

बाह्य काष्ठा notअगरier_block ocelot_netdevice_nb;
बाह्य काष्ठा notअगरier_block ocelot_चयनdev_nb;
बाह्य काष्ठा notअगरier_block ocelot_चयनdev_blocking_nb;
बाह्य स्थिर काष्ठा devlink_ops ocelot_devlink_ops;

#पूर्ण_अगर
