<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ WITH Linux-syscall-note */
/*
 * VLAN		An implementation of 802.1Q VLAN tagging.
 *
 * Authors:	Ben Greear <greearb@candelatech.com>
 *
 *		This program is मुक्त software; you can redistribute it and/or
 *		modअगरy it under the terms of the GNU General Public License
 *		as published by the Free Software Foundation; either version
 *		2 of the License, or (at your option) any later version.
 *
 */

#अगर_अघोषित _UAPI_LINUX_IF_VLAN_H_
#घोषणा _UAPI_LINUX_IF_VLAN_H_


/* VLAN IOCTLs are found in sockios.h */

/* Passed in vlan_ioctl_args काष्ठाure to determine behaviour. */
क्रमागत vlan_ioctl_cmds अणु
	ADD_VLAN_CMD,
	DEL_VLAN_CMD,
	SET_VLAN_INGRESS_PRIORITY_CMD,
	SET_VLAN_EGRESS_PRIORITY_CMD,
	GET_VLAN_INGRESS_PRIORITY_CMD,
	GET_VLAN_EGRESS_PRIORITY_CMD,
	SET_VLAN_NAME_TYPE_CMD,
	SET_VLAN_FLAG_CMD,
	GET_VLAN_REALDEV_NAME_CMD, /* If this works, you know it's a VLAN device, btw */
	GET_VLAN_VID_CMD /* Get the VID of this VLAN (specअगरied by name) */
पूर्ण;

क्रमागत vlan_flags अणु
	VLAN_FLAG_REORDER_HDR		= 0x1,
	VLAN_FLAG_GVRP			= 0x2,
	VLAN_FLAG_LOOSE_BINDING		= 0x4,
	VLAN_FLAG_MVRP			= 0x8,
	VLAN_FLAG_BRIDGE_BINDING	= 0x10,
पूर्ण;

क्रमागत vlan_name_types अणु
	VLAN_NAME_TYPE_PLUS_VID, /* Name will look like:  vlan0005 */
	VLAN_NAME_TYPE_RAW_PLUS_VID, /* name will look like:  eth1.0005 */
	VLAN_NAME_TYPE_PLUS_VID_NO_PAD, /* Name will look like:  vlan5 */
	VLAN_NAME_TYPE_RAW_PLUS_VID_NO_PAD, /* Name will look like:  eth0.5 */
	VLAN_NAME_TYPE_HIGHEST
पूर्ण;

काष्ठा vlan_ioctl_args अणु
	पूर्णांक cmd; /* Should be one of the vlan_ioctl_cmds क्रमागत above. */
	अक्षर device1[24];

        जोड़ अणु
		अक्षर device2[24];
		पूर्णांक VID;
		अचिन्हित पूर्णांक skb_priority;
		अचिन्हित पूर्णांक name_type;
		अचिन्हित पूर्णांक bind_type;
		अचिन्हित पूर्णांक flag; /* Matches vlan_dev_priv flags */
        पूर्ण u;

	लघु vlan_qos;   
पूर्ण;

#पूर्ण_अगर /* _UAPI_LINUX_IF_VLAN_H_ */
