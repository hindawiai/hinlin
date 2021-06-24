<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/**
 * file phonet.h
 *
 * Phonet sockets kernel पूर्णांकerface
 *
 * Copyright (C) 2008 Nokia Corporation. All rights reserved.
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License क्रम more details.
 *
 * You should have received a copy of the GNU General Public License
 * aदीर्घ with this program; अगर not, ग_लिखो to the Free Software
 * Foundation, Inc., 51 Franklin St, Fअगरth Floor, Boston, MA
 * 02110-1301 USA
 */

#अगर_अघोषित _UAPILINUX_PHONET_H
#घोषणा _UAPILINUX_PHONET_H

#समावेश <linux/types.h>
#समावेश <linux/socket.h>

/* Automatic protocol selection */
#घोषणा PN_PROTO_TRANSPORT	0
/* Phonet datagram socket */
#घोषणा PN_PROTO_PHONET		1
/* Phonet pipe */
#घोषणा PN_PROTO_PIPE		2
#घोषणा PHONET_NPROTO		3

/* Socket options क्रम SOL_PNPIPE level */
#घोषणा PNPIPE_ENCAP		1
#घोषणा PNPIPE_IFINDEX		2
#घोषणा PNPIPE_HANDLE		3
#घोषणा PNPIPE_INITSTATE	4

#घोषणा PNADDR_ANY		0
#घोषणा PNADDR_BROADCAST	0xFC
#घोषणा PNPORT_RESOURCE_ROUTING	0

/* Values क्रम PNPIPE_ENCAP option */
#घोषणा PNPIPE_ENCAP_NONE	0
#घोषणा PNPIPE_ENCAP_IP		1

/* ioctls */
#घोषणा SIOCPNGETOBJECT		(SIOCPROTOPRIVATE + 0)
#घोषणा SIOCPNENABLEPIPE	(SIOCPROTOPRIVATE + 13)
#घोषणा SIOCPNADDRESOURCE	(SIOCPROTOPRIVATE + 14)
#घोषणा SIOCPNDELRESOURCE	(SIOCPROTOPRIVATE + 15)

/* Phonet protocol header */
काष्ठा phonethdr अणु
	__u8	pn_rdev;
	__u8	pn_sdev;
	__u8	pn_res;
	__be16	pn_length;
	__u8	pn_robj;
	__u8	pn_sobj;
पूर्ण __attribute__((packed));

/* Common Phonet payload header */
काष्ठा phoneपंचांगsg अणु
	__u8	pn_trans_id;	/* transaction ID */
	__u8	pn_msg_id;	/* message type */
	जोड़ अणु
		काष्ठा अणु
			__u8	pn_submsg_id;	/* message subtype */
			__u8	pn_data[5];
		पूर्ण base;
		काष्ठा अणु
			__u16	pn_e_res_id;	/* extended resource ID */
			__u8	pn_e_submsg_id;	/* message subtype */
			__u8	pn_e_data[3];
		पूर्ण ext;
	पूर्ण pn_msg_u;
पूर्ण;
#घोषणा PN_COMMON_MESSAGE	0xF0
#घोषणा PN_COMMGR		0x10
#घोषणा PN_PREFIX		0xE0 /* resource क्रम extended messages */
#घोषणा pn_submsg_id		pn_msg_u.base.pn_submsg_id
#घोषणा pn_e_submsg_id		pn_msg_u.ext.pn_e_submsg_id
#घोषणा pn_e_res_id		pn_msg_u.ext.pn_e_res_id
#घोषणा pn_data			pn_msg_u.base.pn_data
#घोषणा pn_e_data		pn_msg_u.ext.pn_e_data

/* data क्रम unreachable errors */
#घोषणा PN_COMM_SERVICE_NOT_IDENTIFIED_RESP	0x01
#घोषणा PN_COMM_ISA_ENTITY_NOT_REACHABLE_RESP	0x14
#घोषणा pn_orig_msg_id		pn_data[0]
#घोषणा pn_status		pn_data[1]
#घोषणा pn_e_orig_msg_id	pn_e_data[0]
#घोषणा pn_e_status		pn_e_data[1]

/* Phonet socket address काष्ठाure */
काष्ठा sockaddr_pn अणु
	__kernel_sa_family_t spn_family;
	__u8 spn_obj;
	__u8 spn_dev;
	__u8 spn_resource;
	__u8 spn_zero[माप(काष्ठा sockaddr) - माप(__kernel_sa_family_t) - 3];
पूर्ण __attribute__((packed));

/* Well known address */
#घोषणा PN_DEV_PC	0x10

अटल अंतरभूत __u16 pn_object(__u8 addr, __u16 port)
अणु
	वापस (addr << 8) | (port & 0x3ff);
पूर्ण

अटल अंतरभूत __u8 pn_obj(__u16 handle)
अणु
	वापस handle & 0xff;
पूर्ण

अटल अंतरभूत __u8 pn_dev(__u16 handle)
अणु
	वापस handle >> 8;
पूर्ण

अटल अंतरभूत __u16 pn_port(__u16 handle)
अणु
	वापस handle & 0x3ff;
पूर्ण

अटल अंतरभूत __u8 pn_addr(__u16 handle)
अणु
	वापस (handle >> 8) & 0xfc;
पूर्ण

अटल अंतरभूत व्योम pn_sockaddr_set_addr(काष्ठा sockaddr_pn *spn, __u8 addr)
अणु
	spn->spn_dev &= 0x03;
	spn->spn_dev |= addr & 0xfc;
पूर्ण

अटल अंतरभूत व्योम pn_sockaddr_set_port(काष्ठा sockaddr_pn *spn, __u16 port)
अणु
	spn->spn_dev &= 0xfc;
	spn->spn_dev |= (port >> 8) & 0x03;
	spn->spn_obj = port & 0xff;
पूर्ण

अटल अंतरभूत व्योम pn_sockaddr_set_object(काष्ठा sockaddr_pn *spn,
						__u16 handle)
अणु
	spn->spn_dev = pn_dev(handle);
	spn->spn_obj = pn_obj(handle);
पूर्ण

अटल अंतरभूत व्योम pn_sockaddr_set_resource(काष्ठा sockaddr_pn *spn,
						__u8 resource)
अणु
	spn->spn_resource = resource;
पूर्ण

अटल अंतरभूत __u8 pn_sockaddr_get_addr(स्थिर काष्ठा sockaddr_pn *spn)
अणु
	वापस spn->spn_dev & 0xfc;
पूर्ण

अटल अंतरभूत __u16 pn_sockaddr_get_port(स्थिर काष्ठा sockaddr_pn *spn)
अणु
	वापस ((spn->spn_dev & 0x03) << 8) | spn->spn_obj;
पूर्ण

अटल अंतरभूत __u16 pn_sockaddr_get_object(स्थिर काष्ठा sockaddr_pn *spn)
अणु
	वापस pn_object(spn->spn_dev, spn->spn_obj);
पूर्ण

अटल अंतरभूत __u8 pn_sockaddr_get_resource(स्थिर काष्ठा sockaddr_pn *spn)
अणु
	वापस spn->spn_resource;
पूर्ण

/* Phonet device ioctl requests */

#पूर्ण_अगर /* _UAPILINUX_PHONET_H */
