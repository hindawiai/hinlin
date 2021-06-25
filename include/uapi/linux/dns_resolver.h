<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ WITH Linux-syscall-note */
/* DNS resolver पूर्णांकerface definitions.
 *
 * Copyright (C) 2018 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public Licence
 * as published by the Free Software Foundation; either version
 * 2 of the Licence, or (at your option) any later version.
 */

#अगर_अघोषित _UAPI_LINUX_DNS_RESOLVER_H
#घोषणा _UAPI_LINUX_DNS_RESOLVER_H

#समावेश <linux/types.h>

/*
 * Type of payload.
 */
क्रमागत dns_payload_content_type अणु
	DNS_PAYLOAD_IS_SERVER_LIST	= 0, /* List of servers, requested by srv=1 */
पूर्ण;

/*
 * Type of address that might be found in an address record.
 */
क्रमागत dns_payload_address_type अणु
	DNS_ADDRESS_IS_IPV4		= 0, /* 4-byte AF_INET address */
	DNS_ADDRESS_IS_IPV6		= 1, /* 16-byte AF_INET6 address */
पूर्ण;

/*
 * Type of protocol used to access a server.
 */
क्रमागत dns_payload_protocol_type अणु
	DNS_SERVER_PROTOCOL_UNSPECIFIED	= 0,
	DNS_SERVER_PROTOCOL_UDP		= 1, /* Use UDP to talk to the server */
	DNS_SERVER_PROTOCOL_TCP		= 2, /* Use TCP to talk to the server */
पूर्ण;

/*
 * Source of record included in DNS resolver payload.
 */
क्रमागत dns_record_source अणु
	DNS_RECORD_UNAVAILABLE		= 0, /* No source available (empty record) */
	DNS_RECORD_FROM_CONFIG		= 1, /* From local configuration data */
	DNS_RECORD_FROM_DNS_A		= 2, /* From DNS A or AAAA record */
	DNS_RECORD_FROM_DNS_AFSDB	= 3, /* From DNS AFSDB record */
	DNS_RECORD_FROM_DNS_SRV		= 4, /* From DNS SRV record */
	DNS_RECORD_FROM_NSS		= 5, /* From NSS */
	NR__dns_record_source
पूर्ण;

/*
 * Status of record included in DNS resolver payload.
 */
क्रमागत dns_lookup_status अणु
	DNS_LOOKUP_NOT_DONE		= 0, /* No lookup has been made */
	DNS_LOOKUP_GOOD			= 1, /* Good records obtained */
	DNS_LOOKUP_GOOD_WITH_BAD	= 2, /* Good records, some decoding errors */
	DNS_LOOKUP_BAD			= 3, /* Couldn't decode results */
	DNS_LOOKUP_GOT_NOT_FOUND	= 4, /* Got a "Not Found" result */
	DNS_LOOKUP_GOT_LOCAL_FAILURE	= 5, /* Local failure during lookup */
	DNS_LOOKUP_GOT_TEMP_FAILURE	= 6, /* Temporary failure during lookup */
	DNS_LOOKUP_GOT_NS_FAILURE	= 7, /* Name server failure */
	NR__dns_lookup_status
पूर्ण;

/*
 * Header at the beginning of binary क्रमmat payload.
 */
काष्ठा dns_payload_header अणु
	__u8		zero;		/* Zero byte: marks this as not being text */
	__u8		content;	/* क्रमागत dns_payload_content_type */
	__u8		version;	/* Encoding version */
पूर्ण __packed;

/*
 * Header at the beginning of a V1 server list.  This is followed directly by
 * the server records.  Each server records begins with a काष्ठा of type
 * dns_server_list_v1_server.
 */
काष्ठा dns_server_list_v1_header अणु
	काष्ठा dns_payload_header hdr;
	__u8		source;		/* क्रमागत dns_record_source */
	__u8		status;		/* क्रमागत dns_lookup_status */
	__u8		nr_servers;	/* Number of server records following this */
पूर्ण __packed;

/*
 * Header at the beginning of each V1 server record.  This is followed by the
 * अक्षरacters of the name with no NUL-terminator, followed by the address
 * records क्रम that server.  Each address record begins with a काष्ठा of type
 * काष्ठा dns_server_list_v1_address.
 */
काष्ठा dns_server_list_v1_server अणु
	__u16		name_len;	/* Length of name (LE) */
	__u16		priority;	/* Priority (as SRV record) (LE) */
	__u16		weight;		/* Weight (as SRV record) (LE) */
	__u16		port;		/* UDP/TCP port number (LE) */
	__u8		source;		/* क्रमागत dns_record_source */
	__u8		status;		/* क्रमागत dns_lookup_status */
	__u8		protocol;	/* क्रमागत dns_payload_protocol_type */
	__u8		nr_addrs;
पूर्ण __packed;

/*
 * Header at the beginning of each V1 address record.  This is followed by the
 * bytes of the address, 4 क्रम IPV4 and 16 क्रम IPV6.
 */
काष्ठा dns_server_list_v1_address अणु
	__u8		address_type;	/* क्रमागत dns_payload_address_type */
पूर्ण __packed;

#पूर्ण_अगर /* _UAPI_LINUX_DNS_RESOLVER_H */
