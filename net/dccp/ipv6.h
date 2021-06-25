<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
#अगर_अघोषित _DCCP_IPV6_H
#घोषणा _DCCP_IPV6_H
/*
 *  net/dccp/ipv6.h
 *
 *  An implementation of the DCCP protocol
 *  Copyright (c) 2005 Arnalकरो Carvalho de Melo <acme@ghostprotocols.net>
 */

#समावेश <linux/dccp.h>
#समावेश <linux/ipv6.h>

काष्ठा dccp6_sock अणु
	काष्ठा dccp_sock  dccp;
	/*
	 * ipv6_pinfo has to be the last member of dccp6_sock,
	 * see inet6_sk_generic.
	 */
	काष्ठा ipv6_pinfo inet6;
पूर्ण;

काष्ठा dccp6_request_sock अणु
	काष्ठा dccp_request_sock  dccp;
पूर्ण;

काष्ठा dccp6_समयरुको_sock अणु
	काष्ठा inet_समयरुको_sock   inet;
पूर्ण;

#पूर्ण_अगर /* _DCCP_IPV6_H */
