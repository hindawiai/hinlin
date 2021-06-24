<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *	IEEE 802.1Q Multiple VLAN Registration Protocol (MVRP)
 *
 *	Copyright (c) 2012 Massachusetts Institute of Technology
 *
 *	Adapted from code in net/8021q/vlan_gvrp.c
 *	Copyright (c) 2008 Patrick McHardy <kaber@trash.net>
 */
#समावेश <linux/types.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <net/mrp.h>
#समावेश "vlan.h"

#घोषणा MRP_MVRP_ADDRESS	अणु 0x01, 0x80, 0xc2, 0x00, 0x00, 0x21 पूर्ण

क्रमागत mvrp_attributes अणु
	MVRP_ATTR_INVALID,
	MVRP_ATTR_VID,
	__MVRP_ATTR_MAX
पूर्ण;
#घोषणा MVRP_ATTR_MAX	(__MVRP_ATTR_MAX - 1)

अटल काष्ठा mrp_application vlan_mrp_app __पढ़ो_mostly = अणु
	.type		= MRP_APPLICATION_MVRP,
	.maxattr	= MVRP_ATTR_MAX,
	.pkttype.type	= htons(ETH_P_MVRP),
	.group_address	= MRP_MVRP_ADDRESS,
	.version	= 0,
पूर्ण;

पूर्णांक vlan_mvrp_request_join(स्थिर काष्ठा net_device *dev)
अणु
	स्थिर काष्ठा vlan_dev_priv *vlan = vlan_dev_priv(dev);
	__be16 vlan_id = htons(vlan->vlan_id);

	अगर (vlan->vlan_proto != htons(ETH_P_8021Q))
		वापस 0;
	वापस mrp_request_join(vlan->real_dev, &vlan_mrp_app,
				&vlan_id, माप(vlan_id), MVRP_ATTR_VID);
पूर्ण

व्योम vlan_mvrp_request_leave(स्थिर काष्ठा net_device *dev)
अणु
	स्थिर काष्ठा vlan_dev_priv *vlan = vlan_dev_priv(dev);
	__be16 vlan_id = htons(vlan->vlan_id);

	अगर (vlan->vlan_proto != htons(ETH_P_8021Q))
		वापस;
	mrp_request_leave(vlan->real_dev, &vlan_mrp_app,
			  &vlan_id, माप(vlan_id), MVRP_ATTR_VID);
पूर्ण

पूर्णांक vlan_mvrp_init_applicant(काष्ठा net_device *dev)
अणु
	वापस mrp_init_applicant(dev, &vlan_mrp_app);
पूर्ण

व्योम vlan_mvrp_uninit_applicant(काष्ठा net_device *dev)
अणु
	mrp_uninit_applicant(dev, &vlan_mrp_app);
पूर्ण

पूर्णांक __init vlan_mvrp_init(व्योम)
अणु
	वापस mrp_रेजिस्टर_application(&vlan_mrp_app);
पूर्ण

व्योम vlan_mvrp_uninit(व्योम)
अणु
	mrp_unरेजिस्टर_application(&vlan_mrp_app);
पूर्ण
