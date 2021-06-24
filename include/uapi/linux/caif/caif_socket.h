<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/* linux/caअगर_socket.h
 * CAIF Definitions क्रम CAIF socket and network layer
 * Copyright (C) ST-Ericsson AB 2010
 * Author:	 Sjur Brendeland
 * License terms: GNU General Public License (GPL) version 2
 */

#अगर_अघोषित _LINUX_CAIF_SOCKET_H
#घोषणा _LINUX_CAIF_SOCKET_H

#समावेश <linux/types.h>
#समावेश <linux/socket.h>

/**
 * क्रमागत caअगर_link_selector -    Physical Link Selection.
 * @CAIF_LINK_HIGH_BANDW:	Physical पूर्णांकerface क्रम high-bandwidth
 *				traffic.
 * @CAIF_LINK_LOW_LATENCY:	Physical पूर्णांकerface क्रम low-latency
 *				traffic.
 *
 * CAIF Link Layers can रेजिस्टर their link properties.
 * This क्रमागत is used क्रम choosing between CAIF Link Layers when
 * setting up CAIF Channels when multiple CAIF Link Layers exists.
 */
क्रमागत caअगर_link_selector अणु
	CAIF_LINK_HIGH_BANDW,
	CAIF_LINK_LOW_LATENCY
पूर्ण;

/**
 * क्रमागत caअगर_channel_priority - CAIF channel priorities.
 *
 * @CAIF_PRIO_MIN:	Min priority क्रम a channel.
 * @CAIF_PRIO_LOW:	Low-priority channel.
 * @CAIF_PRIO_NORMAL:	Normal/शेष priority level.
 * @CAIF_PRIO_HIGH:	High priority level
 * @CAIF_PRIO_MAX:	Max priority क्रम channel
 *
 * Priority can be set on CAIF Channels in order to
 * prioritize between traffic on dअगरferent CAIF Channels.
 * These priority levels are recommended, but the priority value
 * is not restricted to the values defined in this क्रमागत, any value
 * between CAIF_PRIO_MIN and CAIF_PRIO_MAX could be used.
 */
क्रमागत caअगर_channel_priority अणु
	CAIF_PRIO_MIN	 = 0x01,
	CAIF_PRIO_LOW	 = 0x04,
	CAIF_PRIO_NORMAL = 0x0f,
	CAIF_PRIO_HIGH	 = 0x14,
	CAIF_PRIO_MAX	 = 0x1F
पूर्ण;

/**
 * क्रमागत caअगर_protocol_type  -	CAIF Channel type.
 * @CAIFPROTO_AT:		Classic AT channel.
 * @CAIFPROTO_DATAGRAM:	Datagram channel.
 * @CAIFPROTO_DATAGRAM_LOOP:	Datagram loopback channel, used क्रम testing.
 * @CAIFPROTO_UTIL:		Utility (Psock) channel.
 * @CAIFPROTO_RFM:		Remote File Manager
 * @CAIFPROTO_DEBUG:		Debug link
 *
 * This क्रमागत defines the CAIF Channel type to be used. This defines
 * the service to connect to on the modem.
 */
क्रमागत caअगर_protocol_type अणु
	CAIFPROTO_AT,
	CAIFPROTO_DATAGRAM,
	CAIFPROTO_DATAGRAM_LOOP,
	CAIFPROTO_UTIL,
	CAIFPROTO_RFM,
	CAIFPROTO_DEBUG,
	_CAIFPROTO_MAX
पूर्ण;
#घोषणा	CAIFPROTO_MAX _CAIFPROTO_MAX

/**
 * क्रमागत caअगर_at_type - AT Service Endpoपूर्णांक
 * @CAIF_ATTYPE_PLAIN:	     Connects to a plain vanilla AT channel.
 */
क्रमागत caअगर_at_type अणु
	CAIF_ATTYPE_PLAIN = 2
पूर्ण;
 /**
 * क्रमागत caअगर_debug_type - Content selection क्रम debug connection
 * @CAIF_DEBUG_TRACE_INTERACTIVE: Connection will contain
 *				both trace and पूर्णांकeractive debug.
 * @CAIF_DEBUG_TRACE:		Connection contains trace only.
 * @CAIF_DEBUG_INTERACTIVE:	Connection to पूर्णांकeractive debug.
 */
क्रमागत caअगर_debug_type अणु
	CAIF_DEBUG_TRACE_INTERACTIVE = 0,
	CAIF_DEBUG_TRACE,
	CAIF_DEBUG_INTERACTIVE,
पूर्ण;

/**
 * क्रमागत caअगर_debug_service - Debug Service Endpoपूर्णांक
 * @CAIF_RADIO_DEBUG_SERVICE:	Debug service on the Radio sub-प्रणाली
 * @CAIF_APP_DEBUG_SERVICE:	Debug क्रम the applications sub-प्रणाली
 */
क्रमागत caअगर_debug_service अणु
	CAIF_RADIO_DEBUG_SERVICE = 1,
	CAIF_APP_DEBUG_SERVICE
पूर्ण;

/**
 * काष्ठा sockaddr_caअगर - the sockaddr काष्ठाure क्रम CAIF sockets.
 * @family:		     Address family number, must be AF_CAIF.
 * @u:			     Union of address data 'switched' by family.
 * :
 * @u.at:                    Applies when family = CAIFPROTO_AT.
 *
 * @u.at.type:               Type of AT link to set up (क्रमागत caअगर_at_type).
 *
 * @u.util:                  Applies when family = CAIFPROTO_UTIL
 *
 * @u.util.service:          Utility service name.
 *
 * @u.dgm:                   Applies when family = CAIFPROTO_DATAGRAM
 *
 * @u.dgm.connection_id:     Datagram connection id.
 *
 * @u.dgm.nsapi:             NSAPI of the PDP-Context.
 *
 * @u.rfm:                   Applies when family = CAIFPROTO_RFM
 *
 * @u.rfm.connection_id:     Connection ID क्रम RFM.
 *
 * @u.rfm.volume:            Volume to mount.
 *
 * @u.dbg:		      Applies when family = CAIFPROTO_DEBUG.
 *
 * @u.dbg.type:			     Type of debug connection to set up
 *			      (caअगर_debug_type).
 *
 * @u.dbg.service:	      Service sub-प्रणाली to connect (caअगर_debug_service
 * Description:
 * This काष्ठाure holds the connect parameters used क्रम setting up a
 * CAIF Channel. It defines the service to connect to on the modem.
 */
काष्ठा sockaddr_caअगर अणु
	__kernel_sa_family_t  family;
	जोड़ अणु
		काष्ठा अणु
			__u8  type;		/* type: क्रमागत caअगर_at_type */
		पूर्ण at;				/* CAIFPROTO_AT */
		काष्ठा अणु
			अक्षर	  service[16];
		पूर्ण util;				/* CAIFPROTO_UTIL */
		जोड़ अणु
			__u32 connection_id;
			__u8  nsapi;
		पूर्ण dgm;				/* CAIFPROTO_DATAGRAM(_LOOP)*/
		काष्ठा अणु
			__u32 connection_id;
			अक्षर	  volume[16];
		पूर्ण rfm;				/* CAIFPROTO_RFM */
		काष्ठा अणु
			__u8  type;		/* type:क्रमागत caअगर_debug_type */
			__u8  service;		/* service:caअगर_debug_service */
		पूर्ण dbg;				/* CAIFPROTO_DEBUG */
	पूर्ण u;
पूर्ण;

/**
 * क्रमागत caअगर_socket_opts - CAIF option values क्रम माला_लोockopt and setsockopt.
 *
 * @CAIFSO_LINK_SELECT:		Selector used अगर multiple CAIF Link layers are
 *				available. Either a high bandwidth
 *				link can be selected (CAIF_LINK_HIGH_BANDW) or
 *				a low latency link (CAIF_LINK_LOW_LATENCY).
 *                              This option is of type __u32.
 *				Alternatively SO_BINDTODEVICE can be used.
 *
 * @CAIFSO_REQ_PARAM:		Used to set the request parameters क्रम a
 *				utility channel. (maximum 256 bytes). This
 *				option must be set beक्रमe connecting.
 *
 * @CAIFSO_RSP_PARAM:		Gets the response parameters क्रम a utility
 *				channel. (maximum 256 bytes). This option
 *				is valid after a successful connect.
 *
 *
 * This क्रमागत defines the CAIF Socket options to be used on a socket
 * of type PF_CAIF.
 *
 */
क्रमागत caअगर_socket_opts अणु
	CAIFSO_LINK_SELECT	= 127,
	CAIFSO_REQ_PARAM	= 128,
	CAIFSO_RSP_PARAM	= 129,
पूर्ण;

#पूर्ण_अगर /* _LINUX_CAIF_SOCKET_H */
