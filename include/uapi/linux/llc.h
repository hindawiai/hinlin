<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-1.0+ WITH Linux-syscall-note */
/*
 * IEEE 802.2 User Interface SAPs क्रम Linux, data काष्ठाures and indicators.
 *
 * Copyright (c) 2001 by Jay Schulist <jschlst@samba.org>
 *
 * This program can be redistributed or modअगरied under the terms of the
 * GNU General Public License as published by the Free Software Foundation.
 * This program is distributed without any warranty or implied warranty
 * of merchantability or fitness क्रम a particular purpose.
 *
 * See the GNU General Public License क्रम more details.
 */
#अगर_अघोषित _UAPI__LINUX_LLC_H
#घोषणा _UAPI__LINUX_LLC_H

#समावेश <linux/socket.h>
#समावेश <linux/अगर.h> 		/* For IFHWADDRLEN. */

#घोषणा __LLC_SOCK_SIZE__ 16	/* माप(sockaddr_llc), word align. */
काष्ठा sockaddr_llc अणु
	__kernel_sa_family_t sllc_family; /* AF_LLC */
	__kernel_sa_family_t sllc_arphrd; /* ARPHRD_ETHER */
	अचिन्हित अक्षर   sllc_test;
	अचिन्हित अक्षर   sllc_xid;
	अचिन्हित अक्षर	sllc_ua;	/* UA data, only क्रम SOCK_STREAM. */
	अचिन्हित अक्षर   sllc_sap;
	अचिन्हित अक्षर   sllc_mac[IFHWADDRLEN];
	अचिन्हित अक्षर   __pad[__LLC_SOCK_SIZE__ -
			      माप(__kernel_sa_family_t) * 2 -
			      माप(अचिन्हित अक्षर) * 4 - IFHWADDRLEN];
पूर्ण;

/* sockopt definitions. */
क्रमागत llc_sockopts अणु
	LLC_OPT_UNKNOWN = 0,
	LLC_OPT_RETRY,		/* max retrans attempts. */
	LLC_OPT_SIZE,		/* max PDU size (octets). */
	LLC_OPT_ACK_TMR_EXP,	/* ack expire समय (secs). */
	LLC_OPT_P_TMR_EXP,	/* pf cycle expire समय (secs). */
	LLC_OPT_REJ_TMR_EXP,	/* rej sent expire समय (secs). */
	LLC_OPT_BUSY_TMR_EXP,	/* busy state expire समय (secs). */
	LLC_OPT_TX_WIN,		/* tx winकरोw size. */
	LLC_OPT_RX_WIN,		/* rx winकरोw size. */
	LLC_OPT_PKTINFO,	/* ancillary packet inक्रमmation. */
	LLC_OPT_MAX
पूर्ण;

#घोषणा LLC_OPT_MAX_RETRY	 100
#घोषणा LLC_OPT_MAX_SIZE	4196
#घोषणा LLC_OPT_MAX_WIN		 127
#घोषणा LLC_OPT_MAX_ACK_TMR_EXP	  60
#घोषणा LLC_OPT_MAX_P_TMR_EXP	  60
#घोषणा LLC_OPT_MAX_REJ_TMR_EXP	  60
#घोषणा LLC_OPT_MAX_BUSY_TMR_EXP  60

/* LLC SAP types. */
#घोषणा LLC_SAP_शून्य	0x00		/* शून्य SAP. 			*/
#घोषणा LLC_SAP_LLC	0x02		/* LLC Sublayer Management. 	*/
#घोषणा LLC_SAP_SNA	0x04		/* SNA Path Control. 		*/
#घोषणा LLC_SAP_PNM	0x0E		/* Proway Network Management.	*/	
#घोषणा LLC_SAP_IP	0x06		/* TCP/IP. 			*/
#घोषणा LLC_SAP_BSPAN	0x42		/* Bridge Spanning Tree Proto	*/
#घोषणा LLC_SAP_MMS	0x4E		/* Manufacturing Message Srv.	*/
#घोषणा LLC_SAP_8208	0x7E		/* ISO 8208			*/
#घोषणा LLC_SAP_3COM	0x80		/* 3COM. 			*/
#घोषणा LLC_SAP_PRO	0x8E		/* Proway Active Station List	*/
#घोषणा LLC_SAP_SNAP	0xAA		/* SNAP. 			*/
#घोषणा LLC_SAP_BANYAN	0xBC		/* Banyan. 			*/
#घोषणा LLC_SAP_IPX	0xE0		/* IPX/SPX. 			*/
#घोषणा LLC_SAP_NETBEUI	0xF0		/* NetBEUI. 			*/
#घोषणा LLC_SAP_LANMGR	0xF4		/* LanManager. 			*/
#घोषणा LLC_SAP_IMPL	0xF8		/* IMPL				*/
#घोषणा LLC_SAP_DISC	0xFC		/* Discovery			*/
#घोषणा LLC_SAP_OSI	0xFE		/* OSI Network Layers. 		*/
#घोषणा LLC_SAP_LAR	0xDC		/* LAN Address Resolution 	*/
#घोषणा LLC_SAP_RM	0xD4		/* Resource Management 		*/
#घोषणा LLC_SAP_GLOBAL	0xFF		/* Global SAP. 			*/

काष्ठा llc_pktinfo अणु
	पूर्णांक lpi_अगरindex;
	अचिन्हित अक्षर lpi_sap;
	अचिन्हित अक्षर lpi_mac[IFHWADDRLEN];
पूर्ण;

#पूर्ण_अगर /* _UAPI__LINUX_LLC_H */
