<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Orb related data काष्ठाures.
 *
 * Copyright IBM Corp. 2007, 2011
 *
 * Author(s): Cornelia Huck <cornelia.huck@de.ibm.com>
 *	      Peter Oberparleiter <peter.oberparleiter@de.ibm.com>
 *	      Sebastian Ott <sebott@linux.vnet.ibm.com>
 */

#अगर_अघोषित S390_ORB_H
#घोषणा S390_ORB_H

/*
 * Command-mode operation request block
 */
काष्ठा cmd_orb अणु
	u32 पूर्णांकparm;	/* पूर्णांकerruption parameter */
	u32 key:4;	/* flags, like key, suspend control, etc. */
	u32 spnd:1;	/* suspend control */
	u32 res1:1;	/* reserved */
	u32 mod:1;	/* modअगरication control */
	u32 sync:1;	/* synchronize control */
	u32 fmt:1;	/* क्रमmat control */
	u32 pfch:1;	/* prefetch control */
	u32 isic:1;	/* initial-status-पूर्णांकerruption control */
	u32 alcc:1;	/* address-limit-checking control */
	u32 ssic:1;	/* suppress-suspended-पूर्णांकerr. control */
	u32 res2:1;	/* reserved */
	u32 c64:1;	/* IDAW/QDIO 64 bit control  */
	u32 i2k:1;	/* IDAW 2/4kB block size control */
	u32 lpm:8;	/* logical path mask */
	u32 ils:1;	/* incorrect length */
	u32 zero:6;	/* reserved zeros */
	u32 orbx:1;	/* ORB extension control */
	u32 cpa;	/* channel program address */
पूर्ण  __packed __aligned(4);

/*
 * Transport-mode operation request block
 */
काष्ठा पंचांग_orb अणु
	u32 पूर्णांकparm;
	u32 key:4;
	u32:9;
	u32 b:1;
	u32:2;
	u32 lpm:8;
	u32:7;
	u32 x:1;
	u32 tcw;
	u32 prio:8;
	u32:8;
	u32 rsvpgm:8;
	u32:8;
	u32:32;
	u32:32;
	u32:32;
	u32:32;
पूर्ण  __packed __aligned(4);

/*
 * eadm operation request block
 */
काष्ठा eadm_orb अणु
	u32 पूर्णांकparm;
	u32 key:4;
	u32:4;
	u32 compat1:1;
	u32 compat2:1;
	u32:21;
	u32 x:1;
	u32 aob;
	u32 css_prio:8;
	u32:8;
	u32 scm_prio:8;
	u32:8;
	u32:29;
	u32 fmt:3;
	u32:32;
	u32:32;
	u32:32;
पूर्ण  __packed __aligned(4);

जोड़ orb अणु
	काष्ठा cmd_orb cmd;
	काष्ठा पंचांग_orb पंचांग;
	काष्ठा eadm_orb eadm;
पूर्ण  __packed __aligned(4);

#पूर्ण_अगर /* S390_ORB_H */
