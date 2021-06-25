<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _UAPI__LINUX_MROUTE6_H
#घोषणा _UAPI__LINUX_MROUTE6_H

#समावेश <linux/स्थिर.h>
#समावेश <linux/types.h>
#समावेश <linux/sockios.h>
#समावेश <linux/in6.h>		/* For काष्ठा sockaddr_in6. */

/*
 *	Based on the MROUTING 3.5 defines primarily to keep
 *	source compatibility with BSD.
 *
 *	See the pim6sd code क्रम the original history.
 *
 *      Protocol Independent Multicast (PIM) data काष्ठाures included
 *      Carlos Picoto (cap@di.fc.ul.pt)
 *
 */

#घोषणा MRT6_BASE	200
#घोषणा MRT6_INIT	(MRT6_BASE)	/* Activate the kernel mroute code 	*/
#घोषणा MRT6_DONE	(MRT6_BASE+1)	/* Shutकरोwn the kernel mroute		*/
#घोषणा MRT6_ADD_MIF	(MRT6_BASE+2)	/* Add a भव पूर्णांकerface		*/
#घोषणा MRT6_DEL_MIF	(MRT6_BASE+3)	/* Delete a भव पूर्णांकerface		*/
#घोषणा MRT6_ADD_MFC	(MRT6_BASE+4)	/* Add a multicast क्रमwarding entry	*/
#घोषणा MRT6_DEL_MFC	(MRT6_BASE+5)	/* Delete a multicast क्रमwarding entry	*/
#घोषणा MRT6_VERSION	(MRT6_BASE+6)	/* Get the kernel multicast version	*/
#घोषणा MRT6_ASSERT	(MRT6_BASE+7)	/* Activate PIM निश्चित mode		*/
#घोषणा MRT6_PIM	(MRT6_BASE+8)	/* enable PIM code			*/
#घोषणा MRT6_TABLE	(MRT6_BASE+9)	/* Specअगरy mroute table ID		*/
#घोषणा MRT6_ADD_MFC_PROXY	(MRT6_BASE+10)	/* Add a (*,*|G) mfc entry	*/
#घोषणा MRT6_DEL_MFC_PROXY	(MRT6_BASE+11)	/* Del a (*,*|G) mfc entry	*/
#घोषणा MRT6_FLUSH	(MRT6_BASE+12)	/* Flush all mfc entries and/or vअगरs	*/
#घोषणा MRT6_MAX	(MRT6_BASE+12)

#घोषणा SIOCGETMIFCNT_IN6	SIOCPROTOPRIVATE	/* IP protocol निजीs */
#घोषणा SIOCGETSGCNT_IN6	(SIOCPROTOPRIVATE+1)
#घोषणा SIOCGETRPF	(SIOCPROTOPRIVATE+2)

/* MRT6_FLUSH optional flags */
#घोषणा MRT6_FLUSH_MFC	1	/* Flush multicast entries */
#घोषणा MRT6_FLUSH_MFC_STATIC	2	/* Flush अटल multicast entries */
#घोषणा MRT6_FLUSH_MIFS	4	/* Flushing multicast vअगरs */
#घोषणा MRT6_FLUSH_MIFS_STATIC	8	/* Flush अटल multicast vअगरs */

#घोषणा MAXMIFS		32
प्रकार अचिन्हित दीर्घ mअगरbiपंचांगap_t;	/* User mode code depends on this lot */
प्रकार अचिन्हित लघु mअगरi_t;
#घोषणा ALL_MIFS	((mअगरi_t)(-1))

#अगर_अघोषित IF_SETSIZE
#घोषणा IF_SETSIZE	256
#पूर्ण_अगर

प्रकार	__u32		अगर_mask;
#घोषणा NIFBITS (माप(अगर_mask) * 8)        /* bits per mask */

प्रकार काष्ठा अगर_set अणु
	अगर_mask अगरs_bits[__KERNEL_DIV_ROUND_UP(IF_SETSIZE, NIFBITS)];
पूर्ण अगर_set;

#घोषणा IF_SET(n, p)    ((p)->अगरs_bits[(n)/NIFBITS] |= (1 << ((n) % NIFBITS)))
#घोषणा IF_CLR(n, p)    ((p)->अगरs_bits[(n)/NIFBITS] &= ~(1 << ((n) % NIFBITS)))
#घोषणा IF_ISSET(n, p)  ((p)->अगरs_bits[(n)/NIFBITS] & (1 << ((n) % NIFBITS)))
#घोषणा IF_COPY(f, t)   bcopy(f, t, माप(*(f)))
#घोषणा IF_ZERO(p)      bzero(p, माप(*(p)))

/*
 *	Passed by mrouted क्रम an MRT_ADD_MIF - again we use the
 *	mrouted 3.6 काष्ठाures क्रम compatibility
 */

काष्ठा mअगर6ctl अणु
	mअगरi_t	mअगर6c_mअगरi;		/* Index of MIF */
	अचिन्हित अक्षर mअगर6c_flags;	/* MIFF_ flags */
	अचिन्हित अक्षर vअगरc_threshold;	/* ttl limit */
	__u16	 mअगर6c_pअगरi;		/* the index of the physical IF */
	अचिन्हित पूर्णांक vअगरc_rate_limit;	/* Rate limiter values (NI) */
पूर्ण;

#घोषणा MIFF_REGISTER	0x1	/* रेजिस्टर vअगर	*/

/*
 *	Cache manipulation काष्ठाures क्रम mrouted and PIMd
 */

काष्ठा mf6cctl अणु
	काष्ठा sockaddr_in6 mf6cc_origin;		/* Origin of mcast	*/
	काष्ठा sockaddr_in6 mf6cc_mcastgrp;		/* Group in question	*/
	mअगरi_t	mf6cc_parent;			/* Where it arrived	*/
	काष्ठा अगर_set mf6cc_अगरset;		/* Where it is going */
पूर्ण;

/*
 *	Group count retrieval क्रम pim6sd
 */

काष्ठा sioc_sg_req6 अणु
	काष्ठा sockaddr_in6 src;
	काष्ठा sockaddr_in6 grp;
	अचिन्हित दीर्घ pktcnt;
	अचिन्हित दीर्घ bytecnt;
	अचिन्हित दीर्घ wrong_अगर;
पूर्ण;

/*
 *	To get vअगर packet counts
 */

काष्ठा sioc_mअगर_req6 अणु
	mअगरi_t	mअगरi;		/* Which अगरace */
	अचिन्हित दीर्घ icount;	/* In packets */
	अचिन्हित दीर्घ ocount;	/* Out packets */
	अचिन्हित दीर्घ ibytes;	/* In bytes */
	अचिन्हित दीर्घ obytes;	/* Out bytes */
पूर्ण;

/*
 *	That's all usermode folks
 */



/*
 * Structure used to communicate from kernel to multicast router.
 * We'll overlay the काष्ठाure onto an MLD header (not an IPv6 heder like igmpmsgअणुपूर्ण
 * used क्रम IPv4 implementation). This is because this काष्ठाure will be passed via an
 * IPv6 raw socket, on which an application will only receiver the payload i.e the data after
 * the IPv6 header and all the extension headers. (See section 3 of RFC 3542)
 */

काष्ठा mrt6msg अणु
#घोषणा MRT6MSG_NOCACHE		1
#घोषणा MRT6MSG_WRONGMIF	2
#घोषणा MRT6MSG_WHOLEPKT	3		/* used क्रम use level encap */
	__u8		im6_mbz;		/* must be zero		   */
	__u8		im6_msgtype;		/* what type of message    */
	__u16		im6_mअगर;		/* mअगर rec'd on		   */
	__u32		im6_pad;		/* padding क्रम 64 bit arch */
	काष्ठा in6_addr	im6_src, im6_dst;
पूर्ण;

/* ip6mr netlink cache report attributes */
क्रमागत अणु
	IP6MRA_CREPORT_UNSPEC,
	IP6MRA_CREPORT_MSGTYPE,
	IP6MRA_CREPORT_MIF_ID,
	IP6MRA_CREPORT_SRC_ADDR,
	IP6MRA_CREPORT_DST_ADDR,
	IP6MRA_CREPORT_PKT,
	__IP6MRA_CREPORT_MAX
पूर्ण;
#घोषणा IP6MRA_CREPORT_MAX (__IP6MRA_CREPORT_MAX - 1)

#पूर्ण_अगर /* _UAPI__LINUX_MROUTE6_H */
