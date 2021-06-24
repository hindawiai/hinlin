<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _IPX_H_
#घोषणा _IPX_H_
#समावेश <linux/libc-compat.h>	/* क्रम compatibility with glibc netipx/ipx.h */
#समावेश <linux/types.h>
#समावेश <linux/sockios.h>
#समावेश <linux/socket.h>
#घोषणा IPX_NODE_LEN	6
#घोषणा IPX_MTU		576

#अगर __UAPI_DEF_SOCKADDR_IPX
काष्ठा sockaddr_ipx अणु
	__kernel_sa_family_t sipx_family;
	__be16		sipx_port;
	__be32		sipx_network;
	अचिन्हित अक्षर 	sipx_node[IPX_NODE_LEN];
	__u8		sipx_type;
	अचिन्हित अक्षर	sipx_zero;	/* 16 byte fill */
पूर्ण;
#पूर्ण_अगर /* __UAPI_DEF_SOCKADDR_IPX */

/*
 * So we can fit the extra info क्रम SIOCSIFADDR पूर्णांकo the address nicely
 */
#घोषणा sipx_special	sipx_port
#घोषणा sipx_action	sipx_zero
#घोषणा IPX_DLTITF	0
#घोषणा IPX_CRTITF	1

#अगर __UAPI_DEF_IPX_ROUTE_DEFINITION
काष्ठा ipx_route_definition अणु
	__be32        ipx_network;
	__be32        ipx_router_network;
	अचिन्हित अक्षर ipx_router_node[IPX_NODE_LEN];
पूर्ण;
#पूर्ण_अगर /* __UAPI_DEF_IPX_ROUTE_DEFINITION */

#अगर __UAPI_DEF_IPX_INTERFACE_DEFINITION
काष्ठा ipx_पूर्णांकerface_definition अणु
	__be32        ipx_network;
	अचिन्हित अक्षर ipx_device[16];
	अचिन्हित अक्षर ipx_dlink_type;
#घोषणा IPX_FRAME_NONE		0
#घोषणा IPX_FRAME_SNAP		1
#घोषणा IPX_FRAME_8022		2
#घोषणा IPX_FRAME_ETHERII	3
#घोषणा IPX_FRAME_8023		4
#घोषणा IPX_FRAME_TR_8022       5 /* obsolete */
	अचिन्हित अक्षर ipx_special;
#घोषणा IPX_SPECIAL_NONE	0
#घोषणा IPX_PRIMARY		1
#घोषणा IPX_INTERNAL		2
	अचिन्हित अक्षर ipx_node[IPX_NODE_LEN];
पूर्ण;
#पूर्ण_अगर /* __UAPI_DEF_IPX_INTERFACE_DEFINITION */

#अगर __UAPI_DEF_IPX_CONFIG_DATA
काष्ठा ipx_config_data अणु
	अचिन्हित अक्षर	ipxcfg_स्वतः_select_primary;
	अचिन्हित अक्षर	ipxcfg_स्वतः_create_पूर्णांकerfaces;
पूर्ण;
#पूर्ण_अगर /* __UAPI_DEF_IPX_CONFIG_DATA */

/*
 * OLD Route Definition क्रम backward compatibility.
 */

#अगर __UAPI_DEF_IPX_ROUTE_DEF
काष्ठा ipx_route_def अणु
	__be32		ipx_network;
	__be32		ipx_router_network;
#घोषणा IPX_ROUTE_NO_ROUTER	0
	अचिन्हित अक्षर	ipx_router_node[IPX_NODE_LEN];
	अचिन्हित अक्षर	ipx_device[16];
	अचिन्हित लघु	ipx_flags;
#घोषणा IPX_RT_SNAP		8
#घोषणा IPX_RT_8022		4
#घोषणा IPX_RT_BLUEBOOK		2
#घोषणा IPX_RT_ROUTED		1
पूर्ण;
#पूर्ण_अगर /* __UAPI_DEF_IPX_ROUTE_DEF */

#घोषणा SIOCAIPXITFCRT		(SIOCPROTOPRIVATE)
#घोषणा SIOCAIPXPRISLT		(SIOCPROTOPRIVATE + 1)
#घोषणा SIOCIPXCFGDATA		(SIOCPROTOPRIVATE + 2)
#घोषणा SIOCIPXNCPCONN		(SIOCPROTOPRIVATE + 3)
#पूर्ण_अगर /* _IPX_H_ */
