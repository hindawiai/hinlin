<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * NetLabel Unlabeled Support
 *
 * This file defines functions क्रम dealing with unlabeled packets क्रम the
 * NetLabel प्रणाली.  The NetLabel प्रणाली manages अटल and dynamic label
 * mappings क्रम network protocols such as CIPSO and RIPSO.
 *
 * Author: Paul Moore <paul@paul-moore.com>
 */

/*
 * (c) Copyright Hewlett-Packard Development Company, L.P., 2006
 */

#अगर_अघोषित _NETLABEL_UNLABELED_H
#घोषणा _NETLABEL_UNLABELED_H

#समावेश <net/netlabel.h>

/*
 * The following NetLabel payloads are supported by the Unlabeled subप्रणाली.
 *
 * o STATICADD
 *   This message is sent from an application to add a new अटल label क्रम
 *   incoming unlabeled connections.
 *
 *   Required attributes:
 *
 *     NLBL_UNLABEL_A_IFACE
 *     NLBL_UNLABEL_A_SECCTX
 *
 *   If IPv4 is specअगरied the following attributes are required:
 *
 *     NLBL_UNLABEL_A_IPV4ADDR
 *     NLBL_UNLABEL_A_IPV4MASK
 *
 *   If IPv6 is specअगरied the following attributes are required:
 *
 *     NLBL_UNLABEL_A_IPV6ADDR
 *     NLBL_UNLABEL_A_IPV6MASK
 *
 * o STATICREMOVE
 *   This message is sent from an application to हटाओ an existing अटल
 *   label क्रम incoming unlabeled connections.
 *
 *   Required attributes:
 *
 *     NLBL_UNLABEL_A_IFACE
 *
 *   If IPv4 is specअगरied the following attributes are required:
 *
 *     NLBL_UNLABEL_A_IPV4ADDR
 *     NLBL_UNLABEL_A_IPV4MASK
 *
 *   If IPv6 is specअगरied the following attributes are required:
 *
 *     NLBL_UNLABEL_A_IPV6ADDR
 *     NLBL_UNLABEL_A_IPV6MASK
 *
 * o STATICLIST
 *   This message can be sent either from an application or by the kernel in
 *   response to an application generated STATICLIST message.  When sent by an
 *   application there is no payload and the NLM_F_DUMP flag should be set.
 *   The kernel should response with a series of the following messages.
 *
 *   Required attributes:
 *
 *     NLBL_UNLABEL_A_IFACE
 *     NLBL_UNLABEL_A_SECCTX
 *
 *   If IPv4 is specअगरied the following attributes are required:
 *
 *     NLBL_UNLABEL_A_IPV4ADDR
 *     NLBL_UNLABEL_A_IPV4MASK
 *
 *   If IPv6 is specअगरied the following attributes are required:
 *
 *     NLBL_UNLABEL_A_IPV6ADDR
 *     NLBL_UNLABEL_A_IPV6MASK
 *
 * o STATICADDDEF
 *   This message is sent from an application to set the शेष अटल
 *   label क्रम incoming unlabeled connections.
 *
 *   Required attribute:
 *
 *     NLBL_UNLABEL_A_SECCTX
 *
 *   If IPv4 is specअगरied the following attributes are required:
 *
 *     NLBL_UNLABEL_A_IPV4ADDR
 *     NLBL_UNLABEL_A_IPV4MASK
 *
 *   If IPv6 is specअगरied the following attributes are required:
 *
 *     NLBL_UNLABEL_A_IPV6ADDR
 *     NLBL_UNLABEL_A_IPV6MASK
 *
 * o STATICREMOVEDEF
 *   This message is sent from an application to हटाओ the existing शेष
 *   अटल label क्रम incoming unlabeled connections.
 *
 *   If IPv4 is specअगरied the following attributes are required:
 *
 *     NLBL_UNLABEL_A_IPV4ADDR
 *     NLBL_UNLABEL_A_IPV4MASK
 *
 *   If IPv6 is specअगरied the following attributes are required:
 *
 *     NLBL_UNLABEL_A_IPV6ADDR
 *     NLBL_UNLABEL_A_IPV6MASK
 *
 * o STATICLISTDEF
 *   This message can be sent either from an application or by the kernel in
 *   response to an application generated STATICLISTDEF message.  When sent by
 *   an application there is no payload and the NLM_F_DUMP flag should be set.
 *   The kernel should response with the following message.
 *
 *   Required attribute:
 *
 *     NLBL_UNLABEL_A_SECCTX
 *
 *   If IPv4 is specअगरied the following attributes are required:
 *
 *     NLBL_UNLABEL_A_IPV4ADDR
 *     NLBL_UNLABEL_A_IPV4MASK
 *
 *   If IPv6 is specअगरied the following attributes are required:
 *
 *     NLBL_UNLABEL_A_IPV6ADDR
 *     NLBL_UNLABEL_A_IPV6MASK
 *
 * o ACCEPT
 *   This message is sent from an application to specअगरy अगर the kernel should
 *   allow unlabled packets to pass अगर they करो not match any of the अटल
 *   mappings defined in the unlabeled module.
 *
 *   Required attributes:
 *
 *     NLBL_UNLABEL_A_ACPTFLG
 *
 * o LIST
 *   This message can be sent either from an application or by the kernel in
 *   response to an application generated LIST message.  When sent by an
 *   application there is no payload.  The kernel should respond to a LIST
 *   message with a LIST message on success.
 *
 *   Required attributes:
 *
 *     NLBL_UNLABEL_A_ACPTFLG
 *
 */

/* NetLabel Unlabeled commands */
क्रमागत अणु
	NLBL_UNLABEL_C_UNSPEC,
	NLBL_UNLABEL_C_ACCEPT,
	NLBL_UNLABEL_C_LIST,
	NLBL_UNLABEL_C_STATICADD,
	NLBL_UNLABEL_C_STATICREMOVE,
	NLBL_UNLABEL_C_STATICLIST,
	NLBL_UNLABEL_C_STATICADDDEF,
	NLBL_UNLABEL_C_STATICREMOVEDEF,
	NLBL_UNLABEL_C_STATICLISTDEF,
	__NLBL_UNLABEL_C_MAX,
पूर्ण;

/* NetLabel Unlabeled attributes */
क्रमागत अणु
	NLBL_UNLABEL_A_UNSPEC,
	NLBL_UNLABEL_A_ACPTFLG,
	/* (NLA_U8)
	 * अगर true then unlabeled packets are allowed to pass, अन्यथा unlabeled
	 * packets are rejected */
	NLBL_UNLABEL_A_IPV6ADDR,
	/* (NLA_BINARY, काष्ठा in6_addr)
	 * an IPv6 address */
	NLBL_UNLABEL_A_IPV6MASK,
	/* (NLA_BINARY, काष्ठा in6_addr)
	 * an IPv6 address mask */
	NLBL_UNLABEL_A_IPV4ADDR,
	/* (NLA_BINARY, काष्ठा in_addr)
	 * an IPv4 address */
	NLBL_UNLABEL_A_IPV4MASK,
	/* (NLA_BINARY, काष्ठा in_addr)
	 * and IPv4 address mask */
	NLBL_UNLABEL_A_IFACE,
	/* (NLA_शून्य_STRING)
	 * network पूर्णांकerface */
	NLBL_UNLABEL_A_SECCTX,
	/* (NLA_BINARY)
	 * a LSM specअगरic security context */
	__NLBL_UNLABEL_A_MAX,
पूर्ण;
#घोषणा NLBL_UNLABEL_A_MAX (__NLBL_UNLABEL_A_MAX - 1)

/* NetLabel protocol functions */
पूर्णांक netlbl_unlabel_genl_init(व्योम);

/* Unlabeled connection hash table size */
/* XXX - currently this number is an uneducated guess */
#घोषणा NETLBL_UNLHSH_BITSIZE       7

/* General Unlabeled init function */
पूर्णांक netlbl_unlabel_init(u32 size);

/* Static/Fallback label management functions */
पूर्णांक netlbl_unlhsh_add(काष्ठा net *net,
		      स्थिर अक्षर *dev_name,
		      स्थिर व्योम *addr,
		      स्थिर व्योम *mask,
		      u32 addr_len,
		      u32 secid,
		      काष्ठा netlbl_audit *audit_info);
पूर्णांक netlbl_unlhsh_हटाओ(काष्ठा net *net,
			 स्थिर अक्षर *dev_name,
			 स्थिर व्योम *addr,
			 स्थिर व्योम *mask,
			 u32 addr_len,
			 काष्ठा netlbl_audit *audit_info);

/* Process Unlabeled incoming network packets */
पूर्णांक netlbl_unlabel_getattr(स्थिर काष्ठा sk_buff *skb,
			   u16 family,
			   काष्ठा netlbl_lsm_secattr *secattr);

/* Set the शेष configuration to allow Unlabeled packets */
पूर्णांक netlbl_unlabel_defconf(व्योम);

#पूर्ण_अगर
