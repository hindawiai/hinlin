<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *  Copyright (C) 1997 Martin Mares
 *
 *  Automatic IP Layer Configuration
 */

/* The following are initdata: */

बाह्य पूर्णांक ic_proto_enabled;	/* Protocols enabled (see IC_xxx) */
बाह्य पूर्णांक ic_set_manually;	/* IPconfig parameters set manually */

बाह्य __be32 ic_myaddr;		/* My IP address */
बाह्य __be32 ic_gateway;		/* Gateway IP address */

बाह्य __be32 ic_servaddr;		/* Boot server IP address */

बाह्य __be32 root_server_addr;	/* Address of NFS server */
बाह्य u8 root_server_path[];	/* Path to mount as root */


/* bits in ic_proto_अणुenabled,usedपूर्ण */
#घोषणा IC_PROTO	0xFF	/* Protocols mask: */
#घोषणा IC_BOOTP	0x01	/*   BOOTP (or DHCP, see below) */
#घोषणा IC_RARP		0x02	/*   RARP */
#घोषणा IC_USE_DHCP    0x100	/* If on, use DHCP instead of BOOTP */
