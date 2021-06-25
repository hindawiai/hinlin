<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित	__BPQETHER_H
#घोषणा	__BPQETHER_H

/*
 * 	Defines क्रम the BPQETHER pseuकरो device driver
 */

#समावेश <linux/अगर_ether.h>

#घोषणा SIOCSBPQETHOPT		(SIOCDEVPRIVATE+0)	/* reserved */
#घोषणा SIOCSBPQETHADDR		(SIOCDEVPRIVATE+1)
 
काष्ठा bpq_ethaddr अणु
	अचिन्हित अक्षर destination[ETH_ALEN];
	अचिन्हित अक्षर accept[ETH_ALEN];
पूर्ण;

/* 
 * For SIOCSBPQETHOPT - this is compatible with PI2/PacketTwin card drivers,
 * currently not implemented, though. If someone wants to hook a radio
 * to his Ethernet card he may find this useful. ;-)
 */

#घोषणा SIOCGBPQETHPARAM	0x5000  /* get Level 1 parameters */
#घोषणा SIOCSBPQETHPARAM	0x5001  /* set */

काष्ठा bpq_req  अणु
    पूर्णांक cmd;
    पूर्णांक speed;			/* unused */
    पूर्णांक घड़ीmode;		/* unused */
    पूर्णांक txdelay;
    अचिन्हित अक्षर persist;	/* unused */
    पूर्णांक sloसमय;		/* unused */
    पूर्णांक squeldelay;
    पूर्णांक dmachan;		/* unused */
    पूर्णांक irq;			/* unused */
पूर्ण;

#पूर्ण_अगर
