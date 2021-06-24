<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित DSA_LOOP_H
#घोषणा DSA_LOOP_H

#समावेश <linux/types.h>
#समावेश <linux/ethtool.h>
#समावेश <net/dsa.h>

काष्ठा dsa_loop_vlan अणु
	u16 members;
	u16 untagged;
पूर्ण;

काष्ठा dsa_loop_mib_entry अणु
	अक्षर name[ETH_GSTRING_LEN];
	अचिन्हित दीर्घ val;
पूर्ण;

क्रमागत dsa_loop_mib_counters अणु
	DSA_LOOP_PHY_READ_OK,
	DSA_LOOP_PHY_READ_ERR,
	DSA_LOOP_PHY_WRITE_OK,
	DSA_LOOP_PHY_WRITE_ERR,
	__DSA_LOOP_CNT_MAX,
पूर्ण;

काष्ठा dsa_loop_port अणु
	काष्ठा dsa_loop_mib_entry mib[__DSA_LOOP_CNT_MAX];
	u16 pvid;
	पूर्णांक mtu;
पूर्ण;

काष्ठा dsa_loop_priv अणु
	काष्ठा mii_bus	*bus;
	अचिन्हित पूर्णांक	port_base;
	काष्ठा dsa_loop_vlan vlans[VLAN_N_VID];
	काष्ठा net_device *netdev;
	काष्ठा dsa_loop_port ports[DSA_MAX_PORTS];
पूर्ण;

#पूर्ण_अगर /* DSA_LOOP_H */
