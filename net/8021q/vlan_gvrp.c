<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * 	IEEE 802.1Q GARP VLAN Registration Protocol (GVRP)
 *
 * 	Copyright (c) 2008 Patrick McHardy <kaber@trash.net>
 */
#समावेश <linux/types.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <net/garp.h>
#समावेश "vlan.h"

#घोषणा GARP_GVRP_ADDRESS	अणु 0x01, 0x80, 0xc2, 0x00, 0x00, 0x21 पूर्ण

क्रमागत gvrp_attributes अणु
	GVRP_ATTR_INVALID,
	GVRP_ATTR_VID,
	__GVRP_ATTR_MAX
पूर्ण;
#घोषणा GVRP_ATTR_MAX	(__GVRP_ATTR_MAX - 1)

अटल काष्ठा garp_application vlan_gvrp_app __पढ़ो_mostly = अणु
	.proto.group_address	= GARP_GVRP_ADDRESS,
	.maxattr		= GVRP_ATTR_MAX,
	.type			= GARP_APPLICATION_GVRP,
पूर्ण;

पूर्णांक vlan_gvrp_request_join(स्थिर काष्ठा net_device *dev)
अणु
	स्थिर काष्ठा vlan_dev_priv *vlan = vlan_dev_priv(dev);
	__be16 vlan_id = htons(vlan->vlan_id);

	अगर (vlan->vlan_proto != htons(ETH_P_8021Q))
		वापस 0;
	वापस garp_request_join(vlan->real_dev, &vlan_gvrp_app,
				 &vlan_id, माप(vlan_id), GVRP_ATTR_VID);
पूर्ण

व्योम vlan_gvrp_request_leave(स्थिर काष्ठा net_device *dev)
अणु
	स्थिर काष्ठा vlan_dev_priv *vlan = vlan_dev_priv(dev);
	__be16 vlan_id = htons(vlan->vlan_id);

	अगर (vlan->vlan_proto != htons(ETH_P_8021Q))
		वापस;
	garp_request_leave(vlan->real_dev, &vlan_gvrp_app,
			   &vlan_id, माप(vlan_id), GVRP_ATTR_VID);
पूर्ण

पूर्णांक vlan_gvrp_init_applicant(काष्ठा net_device *dev)
अणु
	वापस garp_init_applicant(dev, &vlan_gvrp_app);
पूर्ण

व्योम vlan_gvrp_uninit_applicant(काष्ठा net_device *dev)
अणु
	garp_uninit_applicant(dev, &vlan_gvrp_app);
पूर्ण

पूर्णांक __init vlan_gvrp_init(व्योम)
अणु
	वापस garp_रेजिस्टर_application(&vlan_gvrp_app);
पूर्ण

व्योम vlan_gvrp_uninit(व्योम)
अणु
	garp_unरेजिस्टर_application(&vlan_gvrp_app);
पूर्ण
