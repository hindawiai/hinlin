<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ WITH Linux-syscall-note */
/*
 * INET		An implementation of the TCP/IP protocol suite क्रम the LINUX
 *		operating प्रणाली.  INET is implemented using the  BSD Socket
 *		पूर्णांकerface as the means of communication with the user level.
 *
 *		Global definitions क्रम the IP router पूर्णांकerface.
 *
 * Version:	@(#)route.h	1.0.3	05/27/93
 *
 * Authors:	Original taken from Berkeley UNIX 4.3, (c) UCB 1986-1988
 *		क्रम the purposes of compatibility only.
 *
 *		Fred N. van Kempen, <waltje@uWalt.NL.Mugnet.ORG>
 *
 * Changes:
 *              Mike McLagan    :       Routing by source
 *
 *		This program is मुक्त software; you can redistribute it and/or
 *		modअगरy it under the terms of the GNU General Public License
 *		as published by the Free Software Foundation; either version
 *		2 of the License, or (at your option) any later version.
 */
#अगर_अघोषित _LINUX_ROUTE_H
#घोषणा _LINUX_ROUTE_H

#समावेश <linux/अगर.h>
#समावेश <linux/compiler.h>

/* This काष्ठाure माला_लो passed by the SIOCADDRT and SIOCDELRT calls. */
काष्ठा rtentry अणु
	अचिन्हित दीर्घ	rt_pad1;
	काष्ठा sockaddr	rt_dst;		/* target address		*/
	काष्ठा sockaddr	rt_gateway;	/* gateway addr (RTF_GATEWAY)	*/
	काष्ठा sockaddr	rt_genmask;	/* target network mask (IP)	*/
	अचिन्हित लघु	rt_flags;
	लघु		rt_pad2;
	अचिन्हित दीर्घ	rt_pad3;
	व्योम		*rt_pad4;
	लघु		rt_metric;	/* +1 क्रम binary compatibility!	*/
	अक्षर __user	*rt_dev;	/* क्रमcing the device at add	*/
	अचिन्हित दीर्घ	rt_mtu;		/* per route MTU/Winकरोw 	*/
#अगर_अघोषित __KERNEL__
#घोषणा rt_mss	rt_mtu			/* Compatibility :-(            */
#पूर्ण_अगर
	अचिन्हित दीर्घ	rt_winकरोw;	/* Winकरोw clamping 		*/
	अचिन्हित लघु	rt_irtt;	/* Initial RTT			*/
पूर्ण;


#घोषणा	RTF_UP		0x0001		/* route usable		  	*/
#घोषणा	RTF_GATEWAY	0x0002		/* destination is a gateway	*/
#घोषणा	RTF_HOST	0x0004		/* host entry (net otherwise)	*/
#घोषणा RTF_REINSTATE	0x0008		/* reinstate route after पंचांगout	*/
#घोषणा	RTF_DYNAMIC	0x0010		/* created dyn. (by redirect)	*/
#घोषणा	RTF_MODIFIED	0x0020		/* modअगरied dyn. (by redirect)	*/
#घोषणा RTF_MTU		0x0040		/* specअगरic MTU क्रम this route	*/
#घोषणा RTF_MSS		RTF_MTU		/* Compatibility :-(		*/
#घोषणा RTF_WINDOW	0x0080		/* per route winकरोw clamping	*/
#घोषणा RTF_IRTT	0x0100		/* Initial round trip समय	*/
#घोषणा RTF_REJECT	0x0200		/* Reject route			*/

/*
 *	<linux/ipv6_route.h> uses RTF values >= 64k
 */



#पूर्ण_अगर	/* _LINUX_ROUTE_H */

