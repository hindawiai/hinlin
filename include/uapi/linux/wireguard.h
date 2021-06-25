<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0 WITH Linux-syscall-note) OR MIT */
/*
 * Copyright (C) 2015-2019 Jason A. Donenfeld <Jason@zx2c4.com>. All Rights Reserved.
 *
 * Documentation
 * =============
 *
 * The below क्रमागतs and macros are क्रम पूर्णांकerfacing with WireGuard, using generic
 * netlink, with family WG_GENL_NAME and version WG_GENL_VERSION. It defines two
 * methods: get and set. Note that जबतक they share many common attributes,
 * these two functions actually accept a slightly dअगरferent set of inमाला_दो and
 * outमाला_दो.
 *
 * WG_CMD_GET_DEVICE
 * -----------------
 *
 * May only be called via NLM_F_REQUEST | NLM_F_DUMP. The command should contain
 * one but not both of:
 *
 *    WGDEVICE_A_IFINDEX: NLA_U32
 *    WGDEVICE_A_IFNAME: NLA_NUL_STRING, maxlen IFNAMSIZ - 1
 *
 * The kernel will then वापस several messages (NLM_F_MULTI) containing the
 * following tree of nested items:
 *
 *    WGDEVICE_A_IFINDEX: NLA_U32
 *    WGDEVICE_A_IFNAME: NLA_NUL_STRING, maxlen IFNAMSIZ - 1
 *    WGDEVICE_A_PRIVATE_KEY: NLA_EXACT_LEN, len WG_KEY_LEN
 *    WGDEVICE_A_PUBLIC_KEY: NLA_EXACT_LEN, len WG_KEY_LEN
 *    WGDEVICE_A_LISTEN_PORT: NLA_U16
 *    WGDEVICE_A_FWMARK: NLA_U32
 *    WGDEVICE_A_PEERS: NLA_NESTED
 *        0: NLA_NESTED
 *            WGPEER_A_PUBLIC_KEY: NLA_EXACT_LEN, len WG_KEY_LEN
 *            WGPEER_A_PRESHARED_KEY: NLA_EXACT_LEN, len WG_KEY_LEN
 *            WGPEER_A_ENDPOINT: NLA_MIN_LEN(काष्ठा sockaddr), काष्ठा sockaddr_in or काष्ठा sockaddr_in6
 *            WGPEER_A_PERSISTENT_KEEPALIVE_INTERVAL: NLA_U16
 *            WGPEER_A_LAST_HANDSHAKE_TIME: NLA_EXACT_LEN, काष्ठा __kernel_बारpec
 *            WGPEER_A_RX_BYTES: NLA_U64
 *            WGPEER_A_TX_BYTES: NLA_U64
 *            WGPEER_A_ALLOWEDIPS: NLA_NESTED
 *                0: NLA_NESTED
 *                    WGALLOWEDIP_A_FAMILY: NLA_U16
 *                    WGALLOWEDIP_A_IPADDR: NLA_MIN_LEN(काष्ठा in_addr), काष्ठा in_addr or काष्ठा in6_addr
 *                    WGALLOWEDIP_A_CIDR_MASK: NLA_U8
 *                0: NLA_NESTED
 *                    ...
 *                0: NLA_NESTED
 *                    ...
 *                ...
 *            WGPEER_A_PROTOCOL_VERSION: NLA_U32
 *        0: NLA_NESTED
 *            ...
 *        ...
 *
 * It is possible that all of the allowed IPs of a single peer will not
 * fit within a single netlink message. In that हाल, the same peer will
 * be written in the following message, except it will only contain
 * WGPEER_A_PUBLIC_KEY and WGPEER_A_ALLOWEDIPS. This may occur several
 * बार in a row क्रम the same peer. It is then up to the receiver to
 * coalesce adjacent peers. Likewise, it is possible that all peers will
 * not fit within a single message. So, subsequent peers will be sent
 * in following messages, except those will only contain WGDEVICE_A_IFNAME
 * and WGDEVICE_A_PEERS. It is then up to the receiver to coalesce these
 * messages to क्रमm the complete list of peers.
 *
 * Since this is an NLA_F_DUMP command, the final message will always be
 * NLMSG_DONE, even अगर an error occurs. However, this NLMSG_DONE message
 * contains an पूर्णांकeger error code. It is either zero or a negative error
 * code corresponding to the त्रुटि_सं.
 *
 * WG_CMD_SET_DEVICE
 * -----------------
 *
 * May only be called via NLM_F_REQUEST. The command should contain the
 * following tree of nested items, containing one but not both of
 * WGDEVICE_A_IFINDEX and WGDEVICE_A_IFNAME:
 *
 *    WGDEVICE_A_IFINDEX: NLA_U32
 *    WGDEVICE_A_IFNAME: NLA_NUL_STRING, maxlen IFNAMSIZ - 1
 *    WGDEVICE_A_FLAGS: NLA_U32, 0 or WGDEVICE_F_REPLACE_PEERS अगर all current
 *                      peers should be हटाओd prior to adding the list below.
 *    WGDEVICE_A_PRIVATE_KEY: len WG_KEY_LEN, all zeros to हटाओ
 *    WGDEVICE_A_LISTEN_PORT: NLA_U16, 0 to choose अक्रमomly
 *    WGDEVICE_A_FWMARK: NLA_U32, 0 to disable
 *    WGDEVICE_A_PEERS: NLA_NESTED
 *        0: NLA_NESTED
 *            WGPEER_A_PUBLIC_KEY: len WG_KEY_LEN
 *            WGPEER_A_FLAGS: NLA_U32, 0 and/or WGPEER_F_REMOVE_ME अगर the
 *                            specअगरied peer should not exist at the end of the
 *                            operation, rather than added/updated and/or
 *                            WGPEER_F_REPLACE_ALLOWEDIPS अगर all current allowed
 *                            IPs of this peer should be हटाओd prior to adding
 *                            the list below and/or WGPEER_F_UPDATE_ONLY अगर the
 *                            peer should only be set अगर it alपढ़ोy exists.
 *            WGPEER_A_PRESHARED_KEY: len WG_KEY_LEN, all zeros to हटाओ
 *            WGPEER_A_ENDPOINT: काष्ठा sockaddr_in or काष्ठा sockaddr_in6
 *            WGPEER_A_PERSISTENT_KEEPALIVE_INTERVAL: NLA_U16, 0 to disable
 *            WGPEER_A_ALLOWEDIPS: NLA_NESTED
 *                0: NLA_NESTED
 *                    WGALLOWEDIP_A_FAMILY: NLA_U16
 *                    WGALLOWEDIP_A_IPADDR: काष्ठा in_addr or काष्ठा in6_addr
 *                    WGALLOWEDIP_A_CIDR_MASK: NLA_U8
 *                0: NLA_NESTED
 *                    ...
 *                0: NLA_NESTED
 *                    ...
 *                ...
 *            WGPEER_A_PROTOCOL_VERSION: NLA_U32, should not be set or used at
 *                                       all by most users of this API, as the
 *                                       most recent protocol will be used when
 *                                       this is unset. Otherwise, must be set
 *                                       to 1.
 *        0: NLA_NESTED
 *            ...
 *        ...
 *
 * It is possible that the amount of configuration data exceeds that of
 * the maximum message length accepted by the kernel. In that हाल, several
 * messages should be sent one after another, with each successive one
 * filling in inक्रमmation not contained in the prior. Note that अगर
 * WGDEVICE_F_REPLACE_PEERS is specअगरied in the first message, it probably
 * should not be specअगरied in fragments that come after, so that the list
 * of peers is only cleared the first समय but appended after. Likewise क्रम
 * peers, अगर WGPEER_F_REPLACE_ALLOWEDIPS is specअगरied in the first message
 * of a peer, it likely should not be specअगरied in subsequent fragments.
 *
 * If an error occurs, NLMSG_ERROR will reply containing an त्रुटि_सं.
 */

#अगर_अघोषित _WG_UAPI_WIREGUARD_H
#घोषणा _WG_UAPI_WIREGUARD_H

#घोषणा WG_GENL_NAME "wireguard"
#घोषणा WG_GENL_VERSION 1

#घोषणा WG_KEY_LEN 32

क्रमागत wg_cmd अणु
	WG_CMD_GET_DEVICE,
	WG_CMD_SET_DEVICE,
	__WG_CMD_MAX
पूर्ण;
#घोषणा WG_CMD_MAX (__WG_CMD_MAX - 1)

क्रमागत wgdevice_flag अणु
	WGDEVICE_F_REPLACE_PEERS = 1U << 0,
	__WGDEVICE_F_ALL = WGDEVICE_F_REPLACE_PEERS
पूर्ण;
क्रमागत wgdevice_attribute अणु
	WGDEVICE_A_UNSPEC,
	WGDEVICE_A_IFINDEX,
	WGDEVICE_A_IFNAME,
	WGDEVICE_A_PRIVATE_KEY,
	WGDEVICE_A_PUBLIC_KEY,
	WGDEVICE_A_FLAGS,
	WGDEVICE_A_LISTEN_PORT,
	WGDEVICE_A_FWMARK,
	WGDEVICE_A_PEERS,
	__WGDEVICE_A_LAST
पूर्ण;
#घोषणा WGDEVICE_A_MAX (__WGDEVICE_A_LAST - 1)

क्रमागत wgpeer_flag अणु
	WGPEER_F_REMOVE_ME = 1U << 0,
	WGPEER_F_REPLACE_ALLOWEDIPS = 1U << 1,
	WGPEER_F_UPDATE_ONLY = 1U << 2,
	__WGPEER_F_ALL = WGPEER_F_REMOVE_ME | WGPEER_F_REPLACE_ALLOWEDIPS |
			 WGPEER_F_UPDATE_ONLY
पूर्ण;
क्रमागत wgpeer_attribute अणु
	WGPEER_A_UNSPEC,
	WGPEER_A_PUBLIC_KEY,
	WGPEER_A_PRESHARED_KEY,
	WGPEER_A_FLAGS,
	WGPEER_A_ENDPOINT,
	WGPEER_A_PERSISTENT_KEEPALIVE_INTERVAL,
	WGPEER_A_LAST_HANDSHAKE_TIME,
	WGPEER_A_RX_BYTES,
	WGPEER_A_TX_BYTES,
	WGPEER_A_ALLOWEDIPS,
	WGPEER_A_PROTOCOL_VERSION,
	__WGPEER_A_LAST
पूर्ण;
#घोषणा WGPEER_A_MAX (__WGPEER_A_LAST - 1)

क्रमागत wgallowedip_attribute अणु
	WGALLOWEDIP_A_UNSPEC,
	WGALLOWEDIP_A_FAMILY,
	WGALLOWEDIP_A_IPADDR,
	WGALLOWEDIP_A_CIDR_MASK,
	__WGALLOWEDIP_A_LAST
पूर्ण;
#घोषणा WGALLOWEDIP_A_MAX (__WGALLOWEDIP_A_LAST - 1)

#पूर्ण_अगर /* _WG_UAPI_WIREGUARD_H */
