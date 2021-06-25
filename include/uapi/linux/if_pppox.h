<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ WITH Linux-syscall-note */
/***************************************************************************
 * Linux PPP over X - Generic PPP transport layer sockets
 * Linux PPP over Ethernet (PPPoE) Socket Implementation (RFC 2516) 
 *
 * This file supplies definitions required by the PPP over Ethernet driver
 * (pppox.c).  All version inक्रमmation wrt this file is located in pppox.c
 *
 * License:
 *		This program is मुक्त software; you can redistribute it and/or
 *		modअगरy it under the terms of the GNU General Public License
 *		as published by the Free Software Foundation; either version
 *		2 of the License, or (at your option) any later version.
 *
 */

#अगर_अघोषित _UAPI__LINUX_IF_PPPOX_H
#घोषणा _UAPI__LINUX_IF_PPPOX_H


#समावेश <linux/types.h>
#समावेश <यंत्र/byteorder.h>

#समावेश <linux/socket.h>
#समावेश <linux/अगर.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/अगर_pppol2tp.h>
#समावेश <linux/in.h>
#समावेश <linux/in6.h>

/* For user-space programs to pick up these definitions
 * which they wouldn't get otherwise without defining __KERNEL__
 */
#अगर_अघोषित AF_PPPOX
#घोषणा AF_PPPOX	24
#घोषणा PF_PPPOX	AF_PPPOX
#पूर्ण_अगर /* !(AF_PPPOX) */

/************************************************************************ 
 * PPPoE addressing definition 
 */ 
प्रकार __be16 sid_t;
काष्ठा pppoe_addr अणु
	sid_t         sid;                    /* Session identअगरier */
	अचिन्हित अक्षर remote[ETH_ALEN];       /* Remote address */
	अक्षर          dev[IFNAMSIZ];          /* Local device to use */
पूर्ण; 
 
/************************************************************************ 
 * PPTP addressing definition
 */
काष्ठा pptp_addr अणु
	__u16		call_id;
	काष्ठा in_addr	sin_addr;
पूर्ण;

/************************************************************************
 * Protocols supported by AF_PPPOX
 */
#घोषणा PX_PROTO_OE    0 /* Currently just PPPoE */
#घोषणा PX_PROTO_OL2TP 1 /* Now L2TP also */
#घोषणा PX_PROTO_PPTP  2
#घोषणा PX_MAX_PROTO   3

काष्ठा sockaddr_pppox अणु
	__kernel_sa_family_t sa_family;       /* address family, AF_PPPOX */
	अचिन्हित पूर्णांक    sa_protocol;          /* protocol identअगरier */
	जोड़ अणु
		काष्ठा pppoe_addr  pppoe;
		काष्ठा pptp_addr   pptp;
	पूर्ण sa_addr;
पूर्ण __packed;

/* The use of the above जोड़ isn't viable because the size of this
 * काष्ठा must stay fixed over समय -- applications use माप(काष्ठा
 * sockaddr_pppox) to fill it. We use a protocol specअगरic sockaddr
 * type instead.
 */
काष्ठा sockaddr_pppol2tp अणु
	__kernel_sa_family_t sa_family; /* address family, AF_PPPOX */
	अचिन्हित पूर्णांक    sa_protocol;    /* protocol identअगरier */
	काष्ठा pppol2tp_addr pppol2tp;
पूर्ण __packed;

काष्ठा sockaddr_pppol2tpin6 अणु
	__kernel_sa_family_t sa_family; /* address family, AF_PPPOX */
	अचिन्हित पूर्णांक    sa_protocol;    /* protocol identअगरier */
	काष्ठा pppol2tpin6_addr pppol2tp;
पूर्ण __packed;

/* The L2TPv3 protocol changes tunnel and session ids from 16 to 32
 * bits. So we need a dअगरferent sockaddr काष्ठाure.
 */
काष्ठा sockaddr_pppol2tpv3 अणु
	__kernel_sa_family_t sa_family; /* address family, AF_PPPOX */
	अचिन्हित पूर्णांक    sa_protocol;    /* protocol identअगरier */
	काष्ठा pppol2tpv3_addr pppol2tp;
पूर्ण __packed;

काष्ठा sockaddr_pppol2tpv3in6 अणु
	__kernel_sa_family_t sa_family; /* address family, AF_PPPOX */
	अचिन्हित पूर्णांक    sa_protocol;    /* protocol identअगरier */
	काष्ठा pppol2tpv3in6_addr pppol2tp;
पूर्ण __packed;

/*********************************************************************
 *
 * ioctl पूर्णांकerface क्रम defining क्रमwarding of connections
 *
 ********************************************************************/

#घोषणा PPPOEIOCSFWD	_IOW(0xB1 ,0, माप_प्रकार)
#घोषणा PPPOEIOCDFWD	_IO(0xB1 ,1)
/*#घोषणा PPPOEIOCGFWD	_IOWR(0xB1,2, माप_प्रकार)*/

/* Codes to identअगरy message types */
#घोषणा PADI_CODE	0x09
#घोषणा PADO_CODE	0x07
#घोषणा PADR_CODE	0x19
#घोषणा PADS_CODE	0x65
#घोषणा PADT_CODE	0xa7
काष्ठा pppoe_tag अणु
	__be16 tag_type;
	__be16 tag_len;
	अक्षर tag_data[0];
पूर्ण __attribute__ ((packed));

/* Tag identअगरiers */
#घोषणा PTT_EOL		__cpu_to_be16(0x0000)
#घोषणा PTT_SRV_NAME	__cpu_to_be16(0x0101)
#घोषणा PTT_AC_NAME	__cpu_to_be16(0x0102)
#घोषणा PTT_HOST_UNIQ	__cpu_to_be16(0x0103)
#घोषणा PTT_AC_COOKIE	__cpu_to_be16(0x0104)
#घोषणा PTT_VENDOR 	__cpu_to_be16(0x0105)
#घोषणा PTT_RELAY_SID	__cpu_to_be16(0x0110)
#घोषणा PTT_SRV_ERR     __cpu_to_be16(0x0201)
#घोषणा PTT_SYS_ERR  	__cpu_to_be16(0x0202)
#घोषणा PTT_GEN_ERR  	__cpu_to_be16(0x0203)

काष्ठा pppoe_hdr अणु
#अगर defined(__LITTLE_ENDIAN_BITFIELD)
	__u8 type : 4;
	__u8 ver : 4;
#या_अगर defined(__BIG_ENDIAN_BITFIELD)
	__u8 ver : 4;
	__u8 type : 4;
#अन्यथा
#त्रुटि	"Please fix <asm/byteorder.h>"
#पूर्ण_अगर
	__u8 code;
	__be16 sid;
	__be16 length;
	काष्ठा pppoe_tag tag[0];
पूर्ण __packed;

/* Length of entire PPPoE + PPP header */
#घोषणा PPPOE_SES_HLEN	8


#पूर्ण_अगर /* _UAPI__LINUX_IF_PPPOX_H */
