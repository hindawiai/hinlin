<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _UAPI__LINUX_MROUTE_H
#घोषणा _UAPI__LINUX_MROUTE_H

#समावेश <linux/sockios.h>
#समावेश <linux/types.h>
#समावेश <linux/in.h>		/* For काष्ठा in_addr. */

/* Based on the MROUTING 3.5 defines primarily to keep
 * source compatibility with BSD.
 *
 * See the mrouted code क्रम the original history.
 *
 * Protocol Independent Multicast (PIM) data काष्ठाures included
 * Carlos Picoto (cap@di.fc.ul.pt)
 */

#घोषणा MRT_BASE	200
#घोषणा MRT_INIT	(MRT_BASE)	/* Activate the kernel mroute code 	*/
#घोषणा MRT_DONE	(MRT_BASE+1)	/* Shutकरोwn the kernel mroute		*/
#घोषणा MRT_ADD_VIF	(MRT_BASE+2)	/* Add a भव पूर्णांकerface		*/
#घोषणा MRT_DEL_VIF	(MRT_BASE+3)	/* Delete a भव पूर्णांकerface		*/
#घोषणा MRT_ADD_MFC	(MRT_BASE+4)	/* Add a multicast क्रमwarding entry	*/
#घोषणा MRT_DEL_MFC	(MRT_BASE+5)	/* Delete a multicast क्रमwarding entry	*/
#घोषणा MRT_VERSION	(MRT_BASE+6)	/* Get the kernel multicast version	*/
#घोषणा MRT_ASSERT	(MRT_BASE+7)	/* Activate PIM निश्चित mode		*/
#घोषणा MRT_PIM		(MRT_BASE+8)	/* enable PIM code			*/
#घोषणा MRT_TABLE	(MRT_BASE+9)	/* Specअगरy mroute table ID		*/
#घोषणा MRT_ADD_MFC_PROXY	(MRT_BASE+10)	/* Add a (*,*|G) mfc entry	*/
#घोषणा MRT_DEL_MFC_PROXY	(MRT_BASE+11)	/* Del a (*,*|G) mfc entry	*/
#घोषणा MRT_FLUSH	(MRT_BASE+12)	/* Flush all mfc entries and/or vअगरs	*/
#घोषणा MRT_MAX		(MRT_BASE+12)

#घोषणा SIOCGETVIFCNT	SIOCPROTOPRIVATE	/* IP protocol निजीs */
#घोषणा SIOCGETSGCNT	(SIOCPROTOPRIVATE+1)
#घोषणा SIOCGETRPF	(SIOCPROTOPRIVATE+2)

/* MRT_FLUSH optional flags */
#घोषणा MRT_FLUSH_MFC	1	/* Flush multicast entries */
#घोषणा MRT_FLUSH_MFC_STATIC	2	/* Flush अटल multicast entries */
#घोषणा MRT_FLUSH_VIFS	4	/* Flush multicast vअगरs */
#घोषणा MRT_FLUSH_VIFS_STATIC	8	/* Flush अटल multicast vअगरs */

#घोषणा MAXVIFS		32
प्रकार अचिन्हित दीर्घ vअगरbiपंचांगap_t;	/* User mode code depends on this lot */
प्रकार अचिन्हित लघु vअगरi_t;
#घोषणा ALL_VIFS	((vअगरi_t)(-1))

/* Same idea as select */

#घोषणा VIFM_SET(n,m)	((m)|=(1<<(n)))
#घोषणा VIFM_CLR(n,m)	((m)&=~(1<<(n)))
#घोषणा VIFM_ISSET(n,m)	((m)&(1<<(n)))
#घोषणा VIFM_CLRALL(m)	((m)=0)
#घोषणा VIFM_COPY(mfrom,mto)	((mto)=(mfrom))
#घोषणा VIFM_SAME(m1,m2)	((m1)==(m2))

/* Passed by mrouted क्रम an MRT_ADD_VIF - again we use the
 * mrouted 3.6 काष्ठाures क्रम compatibility
 */
काष्ठा vअगरctl अणु
	vअगरi_t	vअगरc_vअगरi;		/* Index of VIF */
	अचिन्हित अक्षर vअगरc_flags;	/* VIFF_ flags */
	अचिन्हित अक्षर vअगरc_threshold;	/* ttl limit */
	अचिन्हित पूर्णांक vअगरc_rate_limit;	/* Rate limiter values (NI) */
	जोड़ अणु
		काष्ठा in_addr vअगरc_lcl_addr;     /* Local पूर्णांकerface address */
		पूर्णांक            vअगरc_lcl_अगरindex;  /* Local पूर्णांकerface index   */
	पूर्ण;
	काष्ठा in_addr vअगरc_rmt_addr;	/* IPIP tunnel addr */
पूर्ण;

#घोषणा VIFF_TUNNEL		0x1	/* IPIP tunnel */
#घोषणा VIFF_SRCRT		0x2	/* NI */
#घोषणा VIFF_REGISTER		0x4	/* रेजिस्टर vअगर	*/
#घोषणा VIFF_USE_IFINDEX	0x8	/* use vअगरc_lcl_अगरindex instead of
					   vअगरc_lcl_addr to find an पूर्णांकerface */

/* Cache manipulation काष्ठाures क्रम mrouted and PIMd */
काष्ठा mfcctl अणु
	काष्ठा in_addr mfcc_origin;		/* Origin of mcast	*/
	काष्ठा in_addr mfcc_mcastgrp;		/* Group in question	*/
	vअगरi_t	mfcc_parent;			/* Where it arrived	*/
	अचिन्हित अक्षर mfcc_ttls[MAXVIFS];	/* Where it is going	*/
	अचिन्हित पूर्णांक mfcc_pkt_cnt;		/* pkt count क्रम src-grp */
	अचिन्हित पूर्णांक mfcc_byte_cnt;
	अचिन्हित पूर्णांक mfcc_wrong_अगर;
	पूर्णांक	     mfcc_expire;
पूर्ण;

/*  Group count retrieval क्रम mrouted */
काष्ठा sioc_sg_req अणु
	काष्ठा in_addr src;
	काष्ठा in_addr grp;
	अचिन्हित दीर्घ pktcnt;
	अचिन्हित दीर्घ bytecnt;
	अचिन्हित दीर्घ wrong_अगर;
पूर्ण;

/* To get vअगर packet counts */
काष्ठा sioc_vअगर_req अणु
	vअगरi_t	vअगरi;		/* Which अगरace */
	अचिन्हित दीर्घ icount;	/* In packets */
	अचिन्हित दीर्घ ocount;	/* Out packets */
	अचिन्हित दीर्घ ibytes;	/* In bytes */
	अचिन्हित दीर्घ obytes;	/* Out bytes */
पूर्ण;

/* This is the क्रमmat the mroute daemon expects to see IGMP control
 * data. Magically happens to be like an IP packet as per the original
 */
काष्ठा igmpmsg अणु
	__u32 unused1,unused2;
	अचिन्हित अक्षर im_msgtype;		/* What is this */
	अचिन्हित अक्षर im_mbz;			/* Must be zero */
	अचिन्हित अक्षर im_vअगर;			/* Low 8 bits of Interface */
	अचिन्हित अक्षर im_vअगर_hi;		/* High 8 bits of Interface */
	काष्ठा in_addr im_src,im_dst;
पूर्ण;

/* ipmr netlink table attributes */
क्रमागत अणु
	IPMRA_TABLE_UNSPEC,
	IPMRA_TABLE_ID,
	IPMRA_TABLE_CACHE_RES_QUEUE_LEN,
	IPMRA_TABLE_MROUTE_REG_VIF_NUM,
	IPMRA_TABLE_MROUTE_DO_ASSERT,
	IPMRA_TABLE_MROUTE_DO_PIM,
	IPMRA_TABLE_VIFS,
	IPMRA_TABLE_MROUTE_DO_WRVIFWHOLE,
	__IPMRA_TABLE_MAX
पूर्ण;
#घोषणा IPMRA_TABLE_MAX (__IPMRA_TABLE_MAX - 1)

/* ipmr netlink vअगर attribute क्रमmat
 * [ IPMRA_TABLE_VIFS ] - nested attribute
 *   [ IPMRA_VIF ] - nested attribute
 *     [ IPMRA_VIFA_xxx ]
 */
क्रमागत अणु
	IPMRA_VIF_UNSPEC,
	IPMRA_VIF,
	__IPMRA_VIF_MAX
पूर्ण;
#घोषणा IPMRA_VIF_MAX (__IPMRA_VIF_MAX - 1)

/* vअगर-specअगरic attributes */
क्रमागत अणु
	IPMRA_VIFA_UNSPEC,
	IPMRA_VIFA_IFINDEX,
	IPMRA_VIFA_VIF_ID,
	IPMRA_VIFA_FLAGS,
	IPMRA_VIFA_BYTES_IN,
	IPMRA_VIFA_BYTES_OUT,
	IPMRA_VIFA_PACKETS_IN,
	IPMRA_VIFA_PACKETS_OUT,
	IPMRA_VIFA_LOCAL_ADDR,
	IPMRA_VIFA_REMOTE_ADDR,
	IPMRA_VIFA_PAD,
	__IPMRA_VIFA_MAX
पूर्ण;
#घोषणा IPMRA_VIFA_MAX (__IPMRA_VIFA_MAX - 1)

/* ipmr netlink cache report attributes */
क्रमागत अणु
	IPMRA_CREPORT_UNSPEC,
	IPMRA_CREPORT_MSGTYPE,
	IPMRA_CREPORT_VIF_ID,
	IPMRA_CREPORT_SRC_ADDR,
	IPMRA_CREPORT_DST_ADDR,
	IPMRA_CREPORT_PKT,
	IPMRA_CREPORT_TABLE,
	__IPMRA_CREPORT_MAX
पूर्ण;
#घोषणा IPMRA_CREPORT_MAX (__IPMRA_CREPORT_MAX - 1)

/* That's all usermode folks */

#घोषणा MFC_ASSERT_THRESH (3*HZ)		/* Maximal freq. of निश्चितs */

/* Pseuकरो messages used by mrouted */
#घोषणा IGMPMSG_NOCACHE		1		/* Kern cache fill request to mrouted */
#घोषणा IGMPMSG_WRONGVIF	2		/* For PIM निश्चित processing (unused) */
#घोषणा IGMPMSG_WHOLEPKT	3		/* For PIM Register processing */
#घोषणा IGMPMSG_WRVIFWHOLE	4		/* For PIM Register and निश्चित processing */

#पूर्ण_अगर /* _UAPI__LINUX_MROUTE_H */
