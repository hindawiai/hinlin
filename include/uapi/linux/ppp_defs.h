<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * ppp_defs.h - PPP definitions.
 *
 * Copyright 1994-2000 Paul Mackerras.
 *
 *  This program is मुक्त software; you can redistribute it and/or
 *  modअगरy it under the terms of the GNU General Public License
 *  version 2 as published by the Free Software Foundation.
 */
#समावेश <linux/types.h>

#अगर_अघोषित _UAPI_PPP_DEFS_H_
#घोषणा _UAPI_PPP_DEFS_H_

/*
 * The basic PPP frame.
 */
#घोषणा PPP_HDRLEN	4	/* octets क्रम standard ppp header */
#घोषणा PPP_FCSLEN	2	/* octets क्रम FCS */
#घोषणा PPP_MRU		1500	/* शेष MRU = max length of info field */

#घोषणा PPP_ADDRESS(p)	(((__u8 *)(p))[0])
#घोषणा PPP_CONTROL(p)	(((__u8 *)(p))[1])
#घोषणा PPP_PROTOCOL(p)	((((__u8 *)(p))[2] << 8) + ((__u8 *)(p))[3])

/*
 * Signअगरicant octet values.
 */
#घोषणा	PPP_ALLSTATIONS	0xff	/* All-Stations broadcast address */
#घोषणा	PPP_UI		0x03	/* Unnumbered Inक्रमmation */
#घोषणा	PPP_FLAG	0x7e	/* Flag Sequence */
#घोषणा	PPP_ESCAPE	0x7d	/* Asynchronous Control Escape */
#घोषणा	PPP_TRANS	0x20	/* Asynchronous transparency modअगरier */

/*
 * Protocol field values.
 */
#घोषणा PPP_IP		0x21	/* Internet Protocol */
#घोषणा PPP_AT		0x29	/* AppleTalk Protocol */
#घोषणा PPP_IPX		0x2b	/* IPX protocol */
#घोषणा	PPP_VJC_COMP	0x2d	/* VJ compressed TCP */
#घोषणा	PPP_VJC_UNCOMP	0x2f	/* VJ uncompressed TCP */
#घोषणा PPP_MP		0x3d	/* Multilink protocol */
#घोषणा PPP_IPV6	0x57	/* Internet Protocol Version 6 */
#घोषणा PPP_COMPFRAG	0xfb	/* fragment compressed below bundle */
#घोषणा PPP_COMP	0xfd	/* compressed packet */
#घोषणा PPP_MPLS_UC	0x0281	/* Multi Protocol Label Switching - Unicast */
#घोषणा PPP_MPLS_MC	0x0283	/* Multi Protocol Label Switching - Multicast */
#घोषणा PPP_IPCP	0x8021	/* IP Control Protocol */
#घोषणा PPP_ATCP	0x8029	/* AppleTalk Control Protocol */
#घोषणा PPP_IPXCP	0x802b	/* IPX Control Protocol */
#घोषणा PPP_IPV6CP	0x8057	/* IPv6 Control Protocol */
#घोषणा PPP_CCPFRAG	0x80fb	/* CCP at link level (below MP bundle) */
#घोषणा PPP_CCP		0x80fd	/* Compression Control Protocol */
#घोषणा PPP_MPLSCP	0x80fd	/* MPLS Control Protocol */
#घोषणा PPP_LCP		0xc021	/* Link Control Protocol */
#घोषणा PPP_PAP		0xc023	/* Password Authentication Protocol */
#घोषणा PPP_LQR		0xc025	/* Link Quality Report protocol */
#घोषणा PPP_CHAP	0xc223	/* Cryptographic Handshake Auth. Protocol */
#घोषणा PPP_CBCP	0xc029	/* Callback Control Protocol */

/*
 * Values क्रम FCS calculations.
 */

#घोषणा PPP_INITFCS	0xffff	/* Initial FCS value */
#घोषणा PPP_GOODFCS	0xf0b8	/* Good final FCS value */


/*
 * Extended asyncmap - allows any अक्षरacter to be escaped.
 */

प्रकार __u32		ext_accm[8];

/*
 * What to करो with network protocol (NP) packets.
 */
क्रमागत NPmode अणु
    NPMODE_PASS,		/* pass the packet through */
    NPMODE_DROP,		/* silently drop the packet */
    NPMODE_ERROR,		/* वापस an error */
    NPMODE_QUEUE		/* save it up क्रम later. */
पूर्ण;

/*
 * Statistics क्रम LQRP and pppstats
 */
काष्ठा pppstat	अणु
    __u32	ppp_discards;	/* # frames discarded */

    __u32	ppp_ibytes;	/* bytes received */
    __u32	ppp_ioctects;	/* bytes received not in error */
    __u32	ppp_ipackets;	/* packets received */
    __u32	ppp_ierrors;	/* receive errors */
    __u32	ppp_ilqrs;	/* # LQR frames received */

    __u32	ppp_obytes;	/* raw bytes sent */
    __u32	ppp_ooctects;	/* frame bytes sent */
    __u32	ppp_opackets;	/* packets sent */
    __u32	ppp_oerrors;	/* transmit errors */ 
    __u32	ppp_olqrs;	/* # LQR frames sent */
पूर्ण;

काष्ठा vjstat अणु
    __u32	vjs_packets;	/* outbound packets */
    __u32	vjs_compressed;	/* outbound compressed packets */
    __u32	vjs_searches;	/* searches क्रम connection state */
    __u32	vjs_misses;	/* बार couldn't find conn. state */
    __u32	vjs_uncompressedin; /* inbound uncompressed packets */
    __u32	vjs_compressedin;   /* inbound compressed packets */
    __u32	vjs_errorin;	/* inbound unknown type packets */
    __u32	vjs_tossed;	/* inbound packets tossed because of error */
पूर्ण;

काष्ठा compstat अणु
    __u32	unc_bytes;	/* total uncompressed bytes */
    __u32	unc_packets;	/* total uncompressed packets */
    __u32	comp_bytes;	/* compressed bytes */
    __u32	comp_packets;	/* compressed packets */
    __u32	inc_bytes;	/* incompressible bytes */
    __u32	inc_packets;	/* incompressible packets */

    /* the compression ratio is defined as in_count / bytes_out */
    __u32       in_count;	/* Bytes received */
    __u32       bytes_out;	/* Bytes transmitted */

    द्विगुन	ratio;		/* not computed in kernel. */
पूर्ण;

काष्ठा ppp_stats अणु
    काष्ठा pppstat	p;	/* basic PPP statistics */
    काष्ठा vjstat	vj;	/* VJ header compression statistics */
पूर्ण;

काष्ठा ppp_comp_stats अणु
    काष्ठा compstat	c;	/* packet compression statistics */
    काष्ठा compstat	d;	/* packet decompression statistics */
पूर्ण;

/*
 * The following काष्ठाure records the समय in seconds since
 * the last NP packet was sent or received.
 *
 * Linux implements both 32-bit and 64-bit समय_प्रकार versions
 * क्रम compatibility with user space that defines ppp_idle
 * based on the libc समय_प्रकार.
 */
काष्ठा ppp_idle अणु
    __kernel_old_समय_प्रकार xmit_idle;	/* समय since last NP packet sent */
    __kernel_old_समय_प्रकार recv_idle;	/* समय since last NP packet received */
पूर्ण;

काष्ठा ppp_idle32 अणु
    __s32 xmit_idle;		/* समय since last NP packet sent */
    __s32 recv_idle;		/* समय since last NP packet received */
पूर्ण;

काष्ठा ppp_idle64 अणु
    __s64 xmit_idle;		/* समय since last NP packet sent */
    __s64 recv_idle;		/* समय since last NP packet received */
पूर्ण;

#पूर्ण_अगर /* _UAPI_PPP_DEFS_H_ */
