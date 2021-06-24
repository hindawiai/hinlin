<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ WITH Linux-syscall-note */
/*
 * INET		An implementation of the TCP/IP protocol suite क्रम the LINUX
 *		operating प्रणाली.  INET is implemented using the  BSD Socket
 *		पूर्णांकerface as the means of communication with the user level.
 *
 *		Definitions of the socket-level I/O control calls.
 *
 * Version:	@(#)sockios.h	1.0.2	03/09/93
 *
 * Authors:	Ross Biro
 *		Fred N. van Kempen, <waltje@uWalt.NL.Mugnet.ORG>
 *
 *		This program is मुक्त software; you can redistribute it and/or
 *		modअगरy it under the terms of the GNU General Public License
 *		as published by the Free Software Foundation; either version
 *		2 of the License, or (at your option) any later version.
 */
#अगर_अघोषित _LINUX_SOCKIOS_H
#घोषणा _LINUX_SOCKIOS_H

#समावेश <यंत्र/bitsperदीर्घ.h>
#समावेश <यंत्र/sockios.h>

/* Linux-specअगरic socket ioctls */
#घोषणा SIOCINQ		FIONREAD
#घोषणा SIOCOUTQ	TIOCOUTQ        /* output queue size (not sent + not acked) */

#घोषणा SOCK_IOC_TYPE	0x89

/*
 * the समयval/बारpec data काष्ठाure layout is defined by libc,
 * so we need to cover both possible versions on 32-bit.
 */
/* Get stamp (समयval) */
#घोषणा SIOCGSTAMP_NEW	 _IOR(SOCK_IOC_TYPE, 0x06, दीर्घ दीर्घ[2])
/* Get stamp (बारpec) */
#घोषणा SIOCGSTAMPNS_NEW _IOR(SOCK_IOC_TYPE, 0x07, दीर्घ दीर्घ[2])

#अगर __BITS_PER_LONG == 64 || (defined(__x86_64__) && defined(__ILP32__))
/* on 64-bit and x32, aव्योम the ?: चालक */
#घोषणा SIOCGSTAMP	SIOCGSTAMP_OLD
#घोषणा SIOCGSTAMPNS	SIOCGSTAMPNS_OLD
#अन्यथा
#घोषणा SIOCGSTAMP	((माप(काष्ठा समयval))  == 8 ? \
			 SIOCGSTAMP_OLD   : SIOCGSTAMP_NEW)
#घोषणा SIOCGSTAMPNS	((माप(काष्ठा बारpec)) == 8 ? \
			 SIOCGSTAMPNS_OLD : SIOCGSTAMPNS_NEW)
#पूर्ण_अगर

/* Routing table calls. */
#घोषणा SIOCADDRT	0x890B		/* add routing table entry	*/
#घोषणा SIOCDELRT	0x890C		/* delete routing table entry	*/
#घोषणा SIOCRTMSG	0x890D		/* unused			*/

/* Socket configuration controls. */
#घोषणा SIOCGIFNAME	0x8910		/* get अगरace name		*/
#घोषणा SIOCSIFLINK	0x8911		/* set अगरace channel		*/
#घोषणा SIOCGIFCONF	0x8912		/* get अगरace list		*/
#घोषणा SIOCGIFFLAGS	0x8913		/* get flags			*/
#घोषणा SIOCSIFFLAGS	0x8914		/* set flags			*/
#घोषणा SIOCGIFADDR	0x8915		/* get PA address		*/
#घोषणा SIOCSIFADDR	0x8916		/* set PA address		*/
#घोषणा SIOCGIFDSTADDR	0x8917		/* get remote PA address	*/
#घोषणा SIOCSIFDSTADDR	0x8918		/* set remote PA address	*/
#घोषणा SIOCGIFBRDADDR	0x8919		/* get broadcast PA address	*/
#घोषणा SIOCSIFBRDADDR	0x891a		/* set broadcast PA address	*/
#घोषणा SIOCGIFNETMASK	0x891b		/* get network PA mask		*/
#घोषणा SIOCSIFNETMASK	0x891c		/* set network PA mask		*/
#घोषणा SIOCGIFMETRIC	0x891d		/* get metric			*/
#घोषणा SIOCSIFMETRIC	0x891e		/* set metric			*/
#घोषणा SIOCGIFMEM	0x891f		/* get memory address (BSD)	*/
#घोषणा SIOCSIFMEM	0x8920		/* set memory address (BSD)	*/
#घोषणा SIOCGIFMTU	0x8921		/* get MTU size			*/
#घोषणा SIOCSIFMTU	0x8922		/* set MTU size			*/
#घोषणा SIOCSIFNAME	0x8923		/* set पूर्णांकerface name */
#घोषणा	SIOCSIFHWADDR	0x8924		/* set hardware address 	*/
#घोषणा SIOCGIFENCAP	0x8925		/* get/set encapsulations       */
#घोषणा SIOCSIFENCAP	0x8926		
#घोषणा SIOCGIFHWADDR	0x8927		/* Get hardware address		*/
#घोषणा SIOCGIFSLAVE	0x8929		/* Driver slaving support	*/
#घोषणा SIOCSIFSLAVE	0x8930
#घोषणा SIOCADDMULTI	0x8931		/* Multicast address lists	*/
#घोषणा SIOCDELMULTI	0x8932
#घोषणा SIOCGIFINDEX	0x8933		/* name -> अगर_index mapping	*/
#घोषणा SIOGIFINDEX	SIOCGIFINDEX	/* mहै_छाप compatibility :-)	*/
#घोषणा SIOCSIFPFLAGS	0x8934		/* set/get extended flags set	*/
#घोषणा SIOCGIFPFLAGS	0x8935
#घोषणा SIOCDIFADDR	0x8936		/* delete PA address		*/
#घोषणा	SIOCSIFHWBROADCAST	0x8937	/* set hardware broadcast addr	*/
#घोषणा SIOCGIFCOUNT	0x8938		/* get number of devices */

#घोषणा SIOCGIFBR	0x8940		/* Bridging support		*/
#घोषणा SIOCSIFBR	0x8941		/* Set bridging options 	*/

#घोषणा SIOCGIFTXQLEN	0x8942		/* Get the tx queue length	*/
#घोषणा SIOCSIFTXQLEN	0x8943		/* Set the tx queue length 	*/

/* SIOCGIFDIVERT was:	0x8944		Frame भागersion support */
/* SIOCSIFDIVERT was:	0x8945		Set frame भागersion options */

#घोषणा SIOCETHTOOL	0x8946		/* Ethtool पूर्णांकerface		*/

#घोषणा SIOCGMIIPHY	0x8947		/* Get address of MII PHY in use. */
#घोषणा SIOCGMIIREG	0x8948		/* Read MII PHY रेजिस्टर.	*/
#घोषणा SIOCSMIIREG	0x8949		/* Write MII PHY रेजिस्टर.	*/

#घोषणा SIOCWANDEV	0x894A		/* get/set netdev parameters	*/

#घोषणा SIOCOUTQNSD	0x894B		/* output queue size (not sent only) */
#घोषणा SIOCGSKNS	0x894C		/* get socket network namespace */

/* ARP cache control calls. */
		    /*  0x8950 - 0x8952  * obsolete calls, करोn't re-use */
#घोषणा SIOCDARP	0x8953		/* delete ARP table entry	*/
#घोषणा SIOCGARP	0x8954		/* get ARP table entry		*/
#घोषणा SIOCSARP	0x8955		/* set ARP table entry		*/

/* RARP cache control calls. */
#घोषणा SIOCDRARP	0x8960		/* delete RARP table entry	*/
#घोषणा SIOCGRARP	0x8961		/* get RARP table entry		*/
#घोषणा SIOCSRARP	0x8962		/* set RARP table entry		*/

/* Driver configuration calls */

#घोषणा SIOCGIFMAP	0x8970		/* Get device parameters	*/
#घोषणा SIOCSIFMAP	0x8971		/* Set device parameters	*/

/* DLCI configuration calls */

#घोषणा SIOCADDDLCI	0x8980		/* Create new DLCI device	*/
#घोषणा SIOCDELDLCI	0x8981		/* Delete DLCI device		*/

#घोषणा SIOCGIFVLAN	0x8982		/* 802.1Q VLAN support		*/
#घोषणा SIOCSIFVLAN	0x8983		/* Set 802.1Q VLAN options 	*/

/* bonding calls */

#घोषणा SIOCBONDENSLAVE	0x8990		/* enslave a device to the bond */
#घोषणा SIOCBONDRELEASE 0x8991		/* release a slave from the bond*/
#घोषणा SIOCBONDSETHWADDR      0x8992	/* set the hw addr of the bond  */
#घोषणा SIOCBONDSLAVEINFOQUERY 0x8993   /* rtn info about slave state   */
#घोषणा SIOCBONDINFOQUERY      0x8994	/* rtn info about bond state    */
#घोषणा SIOCBONDCHANGEACTIVE   0x8995   /* update to a new active slave */
			
/* bridge calls */
#घोषणा SIOCBRADDBR     0x89a0		/* create new bridge device     */
#घोषणा SIOCBRDELBR     0x89a1		/* हटाओ bridge device         */
#घोषणा SIOCBRADDIF	0x89a2		/* add पूर्णांकerface to bridge      */
#घोषणा SIOCBRDELIF	0x89a3		/* हटाओ पूर्णांकerface from bridge */

/* hardware समय stamping: parameters in linux/net_tstamp.h */
#घोषणा SIOCSHWTSTAMP	0x89b0		/* set and get config		*/
#घोषणा SIOCGHWTSTAMP	0x89b1		/* get config			*/

/* Device निजी ioctl calls */

/*
 *	These 16 ioctls are available to devices via the करो_ioctl() device
 *	vector. Each device should include this file and redefine these names
 *	as their own. Because these are device dependent it is a good idea
 *	_NOT_ to issue them to अक्रमom objects and hope.
 *
 *	THESE IOCTLS ARE _DEPRECATED_ AND WILL DISAPPEAR IN 2.5.X -DaveM
 */
 
#घोषणा SIOCDEVPRIVATE	0x89F0	/* to 89FF */

/*
 *	These 16 ioctl calls are protocol निजी
 */
 
#घोषणा SIOCPROTOPRIVATE 0x89E0 /* to 89EF */
#पूर्ण_अगर	/* _LINUX_SOCKIOS_H */
