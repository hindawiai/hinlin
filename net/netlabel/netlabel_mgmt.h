<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * NetLabel Management Support
 *
 * This file defines the management functions क्रम the NetLabel प्रणाली.  The
 * NetLabel प्रणाली manages अटल and dynamic label mappings क्रम network
 * protocols such as CIPSO and RIPSO.
 *
 * Author: Paul Moore <paul@paul-moore.com>
 */

/*
 * (c) Copyright Hewlett-Packard Development Company, L.P., 2006
 */

#अगर_अघोषित _NETLABEL_MGMT_H
#घोषणा _NETLABEL_MGMT_H

#समावेश <net/netlabel.h>
#समावेश <linux/atomic.h>

/*
 * The following NetLabel payloads are supported by the management पूर्णांकerface.
 *
 * o ADD:
 *   Sent by an application to add a करोमुख्य mapping to the NetLabel प्रणाली.
 *
 *   Required attributes:
 *
 *     NLBL_MGMT_A_DOMAIN
 *     NLBL_MGMT_A_PROTOCOL
 *
 *   If IPv4 is specअगरied the following attributes are required:
 *
 *     NLBL_MGMT_A_IPV4ADDR
 *     NLBL_MGMT_A_IPV4MASK
 *
 *   If IPv6 is specअगरied the following attributes are required:
 *
 *     NLBL_MGMT_A_IPV6ADDR
 *     NLBL_MGMT_A_IPV6MASK
 *
 *   If using NETLBL_NLTYPE_CIPSOV4 the following attributes are required:
 *
 *     NLBL_MGMT_A_CV4DOI
 *
 *   If using NETLBL_NLTYPE_UNLABELED no other attributes are required,
 *   however the following attribute may optionally be sent:
 *
 *     NLBL_MGMT_A_FAMILY
 *
 * o REMOVE:
 *   Sent by an application to हटाओ a करोमुख्य mapping from the NetLabel
 *   प्रणाली.
 *
 *   Required attributes:
 *
 *     NLBL_MGMT_A_DOMAIN
 *
 * o LISTALL:
 *   This message can be sent either from an application or by the kernel in
 *   response to an application generated LISTALL message.  When sent by an
 *   application there is no payload and the NLM_F_DUMP flag should be set.
 *   The kernel should respond with a series of the following messages.
 *
 *   Required attributes:
 *
 *     NLBL_MGMT_A_DOMAIN
 *     NLBL_MGMT_A_FAMILY
 *
 *   If the IP address selectors are not used the following attribute is
 *   required:
 *
 *     NLBL_MGMT_A_PROTOCOL
 *
 *   If the IP address selectors are used then the following attritbute is
 *   required:
 *
 *     NLBL_MGMT_A_SELECTORLIST
 *
 *   If the mapping is using the NETLBL_NLTYPE_CIPSOV4 type then the following
 *   attributes are required:
 *
 *     NLBL_MGMT_A_CV4DOI
 *
 *   If the mapping is using the NETLBL_NLTYPE_UNLABELED type no other
 *   attributes are required.
 *
 * o ADDDEF:
 *   Sent by an application to set the शेष करोमुख्य mapping क्रम the NetLabel
 *   प्रणाली.
 *
 *   Required attributes:
 *
 *     NLBL_MGMT_A_PROTOCOL
 *
 *   If using NETLBL_NLTYPE_CIPSOV4 the following attributes are required:
 *
 *     NLBL_MGMT_A_CV4DOI
 *
 *   If using NETLBL_NLTYPE_UNLABELED no other attributes are required,
 *   however the following attribute may optionally be sent:
 *
 *     NLBL_MGMT_A_FAMILY
 *
 * o REMOVEDEF:
 *   Sent by an application to हटाओ the शेष करोमुख्य mapping from the
 *   NetLabel प्रणाली, there is no payload.
 *
 * o LISTDEF:
 *   This message can be sent either from an application or by the kernel in
 *   response to an application generated LISTDEF message.  When sent by an
 *   application there may be an optional payload.
 *
 *     NLBL_MGMT_A_FAMILY
 *
 *   On success the kernel should send a response using the following क्रमmat:
 *
 *   If the IP address selectors are not used the following attributes are
 *   required:
 *
 *     NLBL_MGMT_A_PROTOCOL
 *     NLBL_MGMT_A_FAMILY
 *
 *   If the IP address selectors are used then the following attritbute is
 *   required:
 *
 *     NLBL_MGMT_A_SELECTORLIST
 *
 *   If the mapping is using the NETLBL_NLTYPE_CIPSOV4 type then the following
 *   attributes are required:
 *
 *     NLBL_MGMT_A_CV4DOI
 *
 *   If the mapping is using the NETLBL_NLTYPE_UNLABELED type no other
 *   attributes are required.
 *
 * o PROTOCOLS:
 *   Sent by an application to request a list of configured NetLabel protocols
 *   in the kernel.  When sent by an application there is no payload and the
 *   NLM_F_DUMP flag should be set.  The kernel should respond with a series of
 *   the following messages.
 *
 *   Required attributes:
 *
 *     NLBL_MGMT_A_PROTOCOL
 *
 * o VERSION:
 *   Sent by an application to request the NetLabel version.  When sent by an
 *   application there is no payload.  This message type is also used by the
 *   kernel to respond to an VERSION request.
 *
 *   Required attributes:
 *
 *     NLBL_MGMT_A_VERSION
 *
 */

/* NetLabel Management commands */
क्रमागत अणु
	NLBL_MGMT_C_UNSPEC,
	NLBL_MGMT_C_ADD,
	NLBL_MGMT_C_REMOVE,
	NLBL_MGMT_C_LISTALL,
	NLBL_MGMT_C_ADDDEF,
	NLBL_MGMT_C_REMOVEDEF,
	NLBL_MGMT_C_LISTDEF,
	NLBL_MGMT_C_PROTOCOLS,
	NLBL_MGMT_C_VERSION,
	__NLBL_MGMT_C_MAX,
पूर्ण;

/* NetLabel Management attributes */
क्रमागत अणु
	NLBL_MGMT_A_UNSPEC,
	NLBL_MGMT_A_DOMAIN,
	/* (NLA_NUL_STRING)
	 * the शून्य terminated LSM करोमुख्य string */
	NLBL_MGMT_A_PROTOCOL,
	/* (NLA_U32)
	 * the NetLabel protocol type (defined by NETLBL_NLTYPE_*) */
	NLBL_MGMT_A_VERSION,
	/* (NLA_U32)
	 * the NetLabel protocol version number (defined by
	 * NETLBL_PROTO_VERSION) */
	NLBL_MGMT_A_CV4DOI,
	/* (NLA_U32)
	 * the CIPSOv4 DOI value */
	NLBL_MGMT_A_IPV6ADDR,
	/* (NLA_BINARY, काष्ठा in6_addr)
	 * an IPv6 address */
	NLBL_MGMT_A_IPV6MASK,
	/* (NLA_BINARY, काष्ठा in6_addr)
	 * an IPv6 address mask */
	NLBL_MGMT_A_IPV4ADDR,
	/* (NLA_BINARY, काष्ठा in_addr)
	 * an IPv4 address */
	NLBL_MGMT_A_IPV4MASK,
	/* (NLA_BINARY, काष्ठा in_addr)
	 * and IPv4 address mask */
	NLBL_MGMT_A_ADDRSELECTOR,
	/* (NLA_NESTED)
	 * an IP address selector, must contain an address, mask, and protocol
	 * attribute plus any protocol specअगरic attributes */
	NLBL_MGMT_A_SELECTORLIST,
	/* (NLA_NESTED)
	 * the selector list, there must be at least one
	 * NLBL_MGMT_A_ADDRSELECTOR attribute */
	NLBL_MGMT_A_FAMILY,
	/* (NLA_U16)
	 * The address family */
	NLBL_MGMT_A_CLPDOI,
	/* (NLA_U32)
	 * the CALIPSO DOI value */
	__NLBL_MGMT_A_MAX,
पूर्ण;
#घोषणा NLBL_MGMT_A_MAX (__NLBL_MGMT_A_MAX - 1)

/* NetLabel protocol functions */
पूर्णांक netlbl_mgmt_genl_init(व्योम);

/* NetLabel configured protocol reference counter */
बाह्य atomic_t netlabel_mgmt_protocount;

#पूर्ण_अगर
