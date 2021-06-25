<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *	ipddp.h: Header क्रम IP-over-DDP driver क्रम Linux.
 */

#अगर_अघोषित __LINUX_IPDDP_H
#घोषणा __LINUX_IPDDP_H

#अगर_घोषित __KERNEL__

#घोषणा SIOCADDIPDDPRT   (SIOCDEVPRIVATE)
#घोषणा SIOCDELIPDDPRT   (SIOCDEVPRIVATE+1)
#घोषणा SIOCFINDIPDDPRT  (SIOCDEVPRIVATE+2)

काष्ठा ipddp_route
अणु
        काष्ठा net_device *dev;             /* Carrier device */
        __be32 ip;                       /* IP address */
        काष्ठा atalk_addr at;              /* Gateway appletalk address */
        पूर्णांक flags;
        काष्ठा ipddp_route *next;
पूर्ण;

#घोषणा IPDDP_ENCAP	1
#घोषणा IPDDP_DECAP	2

#पूर्ण_अगर	/* __KERNEL__ */
#पूर्ण_अगर	/* __LINUX_IPDDP_H */
