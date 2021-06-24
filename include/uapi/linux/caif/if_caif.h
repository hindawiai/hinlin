<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * Copyright (C) ST-Ericsson AB 2010
 * Author:	Sjur Brendeland
 * License terms: GNU General Public License (GPL) version 2
 */

#अगर_अघोषित IF_CAIF_H_
#घोषणा IF_CAIF_H_
#समावेश <linux/sockios.h>
#समावेश <linux/types.h>
#समावेश <linux/socket.h>

/**
 * क्रमागत अगरla_caअगर - CAIF NetlinkRT parameters.
 * @IFLA_CAIF_IPV4_CONNID:  Connection ID क्रम IPv4 PDP Context.
 *			    The type of attribute is NLA_U32.
 * @IFLA_CAIF_IPV6_CONNID:  Connection ID क्रम IPv6 PDP Context.
 *			    The type of attribute is NLA_U32.
 * @IFLA_CAIF_LOOPBACK:	    If dअगरferent from zero, device is करोing loopback
 *			    The type of attribute is NLA_U8.
 *
 * When using RT Netlink to create, destroy or configure a CAIF IP पूर्णांकerface,
 * क्रमागत अगरla_caअगर is used to specअगरy the configuration attributes.
 */
क्रमागत अगरla_caअगर अणु
	__IFLA_CAIF_UNSPEC,
	IFLA_CAIF_IPV4_CONNID,
	IFLA_CAIF_IPV6_CONNID,
	IFLA_CAIF_LOOPBACK,
	__IFLA_CAIF_MAX
पूर्ण;
#घोषणा	IFLA_CAIF_MAX (__IFLA_CAIF_MAX-1)

#पूर्ण_अगर /*IF_CAIF_H_*/
