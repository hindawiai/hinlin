<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * RapidIO पूर्णांकerconnect services
 *
 * Copyright 2005 MontaVista Software, Inc.
 * Matt Porter <mporter@kernel.crashing.org>
 */

#समावेश <linux/device.h>
#समावेश <linux/list.h>
#समावेश <linux/rपन.स>

#घोषणा RIO_MAX_CHK_RETRY	3
#घोषणा RIO_MPORT_ANY		(-1)

/* Functions पूर्णांकernal to the RIO core code */

बाह्य u32 rio_mport_get_feature(काष्ठा rio_mport *mport, पूर्णांक local, u16 destid,
				 u8 hopcount, पूर्णांक ftr);
बाह्य u32 rio_mport_get_physefb(काष्ठा rio_mport *port, पूर्णांक local,
				 u16 destid, u8 hopcount, u32 *rmap);
बाह्य u32 rio_mport_get_efb(काष्ठा rio_mport *port, पूर्णांक local, u16 destid,
			     u8 hopcount, u32 from);
बाह्य पूर्णांक rio_mport_chk_dev_access(काष्ठा rio_mport *mport, u16 destid,
				    u8 hopcount);
बाह्य पूर्णांक rio_lock_device(काष्ठा rio_mport *port, u16 destid,
			u8 hopcount, पूर्णांक रुको_ms);
बाह्य पूर्णांक rio_unlock_device(काष्ठा rio_mport *port, u16 destid, u8 hopcount);
बाह्य पूर्णांक rio_route_add_entry(काष्ठा rio_dev *rdev,
			u16 table, u16 route_destid, u8 route_port, पूर्णांक lock);
बाह्य पूर्णांक rio_route_get_entry(काष्ठा rio_dev *rdev, u16 table,
			u16 route_destid, u8 *route_port, पूर्णांक lock);
बाह्य पूर्णांक rio_route_clr_table(काष्ठा rio_dev *rdev, u16 table, पूर्णांक lock);
बाह्य पूर्णांक rio_set_port_lockout(काष्ठा rio_dev *rdev, u32 pnum, पूर्णांक lock);
बाह्य काष्ठा rio_dev *rio_get_comptag(u32 comp_tag, काष्ठा rio_dev *from);
बाह्य काष्ठा rio_net *rio_alloc_net(काष्ठा rio_mport *mport);
बाह्य पूर्णांक rio_add_net(काष्ठा rio_net *net);
बाह्य व्योम rio_मुक्त_net(काष्ठा rio_net *net);
बाह्य पूर्णांक rio_add_device(काष्ठा rio_dev *rdev);
बाह्य व्योम rio_del_device(काष्ठा rio_dev *rdev, क्रमागत rio_device_state state);
बाह्य पूर्णांक rio_enable_rx_tx_port(काष्ठा rio_mport *port, पूर्णांक local, u16 destid,
				 u8 hopcount, u8 port_num);
बाह्य पूर्णांक rio_रेजिस्टर_scan(पूर्णांक mport_id, काष्ठा rio_scan *scan_ops);
बाह्य पूर्णांक rio_unरेजिस्टर_scan(पूर्णांक mport_id, काष्ठा rio_scan *scan_ops);
बाह्य व्योम rio_attach_device(काष्ठा rio_dev *rdev);
बाह्य काष्ठा rio_mport *rio_find_mport(पूर्णांक mport_id);
बाह्य पूर्णांक rio_mport_scan(पूर्णांक mport_id);

/* Structures पूर्णांकernal to the RIO core code */
बाह्य स्थिर काष्ठा attribute_group *rio_dev_groups[];
बाह्य स्थिर काष्ठा attribute_group *rio_bus_groups[];
बाह्य स्थिर काष्ठा attribute_group *rio_mport_groups[];

#घोषणा RIO_GET_DID(size, x)	(size ? (x & 0xffff) : ((x & 0x00ff0000) >> 16))
#घोषणा RIO_SET_DID(size, x)	(size ? (x & 0xffff) : ((x & 0x000000ff) << 16))
