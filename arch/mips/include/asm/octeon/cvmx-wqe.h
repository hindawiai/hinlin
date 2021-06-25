<शैली गुरु>
/***********************license start***************
 * Author: Cavium Networks
 *
 * Contact: support@caviumnetworks.com
 * This file is part of the OCTEON SDK
 *
 * Copyright (c) 2003-2008 Cavium Networks
 *
 * This file is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License, Version 2, as
 * published by the Free Software Foundation.
 *
 * This file is distributed in the hope that it will be useful, but
 * AS-IS and WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE, TITLE, or
 * NONINFRINGEMENT.  See the GNU General Public License क्रम more
 * details.
 *
 * You should have received a copy of the GNU General Public License
 * aदीर्घ with this file; अगर not, ग_लिखो to the Free Software
 * Foundation, Inc., 51 Franklin St, Fअगरth Floor, Boston, MA 02110-1301 USA
 * or visit http://www.gnu.org/licenses/.
 *
 * This file may also be available under a dअगरferent license from Cavium.
 * Contact Cavium Networks क्रम more inक्रमmation
 ***********************license end**************************************/

/**
 *
 * This header file defines the work queue entry (wqe) data काष्ठाure.
 * Since this is a commonly used काष्ठाure that depends on काष्ठाures
 * from several hardware blocks, those definitions have been placed
 * in this file to create a single poपूर्णांक of definition of the wqe
 * क्रमmat.
 * Data काष्ठाures are still named according to the block that they
 * relate to.
 *
 */

#अगर_अघोषित __CVMX_WQE_H__
#घोषणा __CVMX_WQE_H__

#समावेश <यंत्र/octeon/cvmx-packet.h>


#घोषणा OCT_TAG_TYPE_STRING(x)						\
	(((x) == CVMX_POW_TAG_TYPE_ORDERED) ?  "ORDERED" :		\
		(((x) == CVMX_POW_TAG_TYPE_ATOMIC) ?  "ATOMIC" :	\
			(((x) == CVMX_POW_TAG_TYPE_शून्य) ?  "NULL" :	\
				"NULL_NULL")))

/**
 * HW decode / err_code in work queue entry
 */
प्रकार जोड़ अणु
	uपूर्णांक64_t u64;

	/* Use this काष्ठा अगर the hardware determines that the packet is IP */
	काष्ठा अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		/* HW sets this to the number of buffers used by this packet */
		uपूर्णांक64_t bufs:8;
		/* HW sets to the number of L2 bytes prior to the IP */
		uपूर्णांक64_t ip_offset:8;
		/* set to 1 अगर we found DSA/VLAN in the L2 */
		uपूर्णांक64_t vlan_valid:1;
		/* Set to 1 अगर the DSA/VLAN tag is stacked */
		uपूर्णांक64_t vlan_stacked:1;
		uपूर्णांक64_t unasचिन्हित:1;
		/* HW sets to the DSA/VLAN CFI flag (valid when vlan_valid) */
		uपूर्णांक64_t vlan_cfi:1;
		/* HW sets to the DSA/VLAN_ID field (valid when vlan_valid) */
		uपूर्णांक64_t vlan_id:12;
		/* Ring Identअगरier (अगर PCIe). Requires PIP_GBL_CTL[RING_EN]=1 */
		uपूर्णांक64_t pr:4;
		uपूर्णांक64_t unasचिन्हित2:8;
		/* the packet needs to be decompressed */
		uपूर्णांक64_t dec_ipcomp:1;
		/* the packet is either TCP or UDP */
		uपूर्णांक64_t tcp_or_udp:1;
		/* the packet needs to be decrypted (ESP or AH) */
		uपूर्णांक64_t dec_ipsec:1;
		/* the packet is IPv6 */
		uपूर्णांक64_t is_v6:1;

		/*
		 * (rcv_error, not_IP, IP_exc, is_frag, L4_error,
		 * software, etc.).
		 */

		/*
		 * reserved क्रम software use, hardware will clear on
		 * packet creation.
		 */
		uपूर्णांक64_t software:1;
		/* exceptional conditions below */
		/* the receive पूर्णांकerface hardware detected an L4 error
		 * (only applies अगर !is_frag) (only applies अगर
		 * !rcv_error && !not_IP && !IP_exc && !is_frag)
		 * failure indicated in err_code below, decode:
		 *
		 * - 1 = Malक्रमmed L4
		 * - 2 = L4 Checksum Error: the L4 checksum value is
		 * - 3 = UDP Length Error: The UDP length field would
		 *	 make the UDP data दीर्घer than what reमुख्यs in
		 *	 the IP packet (as defined by the IP header
		 *	 length field).
		 * - 4 = Bad L4 Port: either the source or destination
		 *	 TCP/UDP port is 0.
		 * - 8 = TCP FIN Only: the packet is TCP and only the
		 *	 FIN flag set.
		 * - 9 = TCP No Flags: the packet is TCP and no flags
		 *	 are set.
		 * - 10 = TCP FIN RST: the packet is TCP and both FIN
		 *	  and RST are set.
		 * - 11 = TCP SYN URG: the packet is TCP and both SYN
		 *	  and URG are set.
		 * - 12 = TCP SYN RST: the packet is TCP and both SYN
		 *	  and RST are set.
		 * - 13 = TCP SYN FIN: the packet is TCP and both SYN
		 *	  and FIN are set.
		 */
		uपूर्णांक64_t L4_error:1;
		/* set अगर the packet is a fragment */
		uपूर्णांक64_t is_frag:1;
		/* the receive पूर्णांकerface hardware detected an IP error
		 * / exception (only applies अगर !rcv_error && !not_IP)
		 * failure indicated in err_code below, decode:
		 *
		 * - 1 = Not IP: the IP version field is neither 4 nor
		 *	 6.
		 * - 2 = IPv4 Header Checksum Error: the IPv4 header
		 *	 has a checksum violation.
		 * - 3 = IP Malक्रमmed Header: the packet is not दीर्घ
		 *	 enough to contain the IP header.
		 * - 4 = IP Malक्रमmed: the packet is not दीर्घ enough
		 *	 to contain the bytes indicated by the IP
		 *	 header. Pad is allowed.
		 * - 5 = IP TTL Hop: the IPv4 TTL field or the IPv6
		 *	 Hop Count field are zero.
		 * - 6 = IP Options
		 */
		uपूर्णांक64_t IP_exc:1;
		/*
		 * Set अगर the hardware determined that the packet is a
		 * broadcast.
		 */
		uपूर्णांक64_t is_bcast:1;
		/*
		 * St अगर the hardware determined that the packet is a
		 * multi-cast.
		 */
		uपूर्णांक64_t is_mcast:1;
		/*
		 * Set अगर the packet may not be IP (must be zero in
		 * this हाल).
		 */
		uपूर्णांक64_t not_IP:1;
		/*
		 * The receive पूर्णांकerface hardware detected a receive
		 * error (must be zero in this हाल).
		 */
		uपूर्णांक64_t rcv_error:1;
		/* lower err_code = first-level descriptor of the
		 * work */
		/* zero क्रम packet submitted by hardware that isn't on
		 * the slow path */
		/* type is cvmx_pip_err_t */
		uपूर्णांक64_t err_code:8;
#अन्यथा
	        uपूर्णांक64_t err_code:8;
	        uपूर्णांक64_t rcv_error:1;
	        uपूर्णांक64_t not_IP:1;
	        uपूर्णांक64_t is_mcast:1;
	        uपूर्णांक64_t is_bcast:1;
	        uपूर्णांक64_t IP_exc:1;
	        uपूर्णांक64_t is_frag:1;
	        uपूर्णांक64_t L4_error:1;
	        uपूर्णांक64_t software:1;
	        uपूर्णांक64_t is_v6:1;
	        uपूर्णांक64_t dec_ipsec:1;
	        uपूर्णांक64_t tcp_or_udp:1;
	        uपूर्णांक64_t dec_ipcomp:1;
	        uपूर्णांक64_t unasचिन्हित2:4;
	        uपूर्णांक64_t unasचिन्हित2a:4;
	        uपूर्णांक64_t pr:4;
	        uपूर्णांक64_t vlan_id:12;
	        uपूर्णांक64_t vlan_cfi:1;
	        uपूर्णांक64_t unasचिन्हित:1;
	        uपूर्णांक64_t vlan_stacked:1;
	        uपूर्णांक64_t vlan_valid:1;
	        uपूर्णांक64_t ip_offset:8;
	        uपूर्णांक64_t bufs:8;
#पूर्ण_अगर
	पूर्ण s;
	काष्ठा अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t bufs:8;
		uपूर्णांक64_t ip_offset:8;
		uपूर्णांक64_t vlan_valid:1;
		uपूर्णांक64_t vlan_stacked:1;
		uपूर्णांक64_t unasचिन्हित:1;
		uपूर्णांक64_t vlan_cfi:1;
		uपूर्णांक64_t vlan_id:12;
		uपूर्णांक64_t port:12;		/* MAC/PIP port number. */
		uपूर्णांक64_t dec_ipcomp:1;
		uपूर्णांक64_t tcp_or_udp:1;
		uपूर्णांक64_t dec_ipsec:1;
		uपूर्णांक64_t is_v6:1;
		uपूर्णांक64_t software:1;
		uपूर्णांक64_t L4_error:1;
		uपूर्णांक64_t is_frag:1;
		uपूर्णांक64_t IP_exc:1;
		uपूर्णांक64_t is_bcast:1;
		uपूर्णांक64_t is_mcast:1;
		uपूर्णांक64_t not_IP:1;
		uपूर्णांक64_t rcv_error:1;
		uपूर्णांक64_t err_code:8;
#अन्यथा
		uपूर्णांक64_t err_code:8;
		uपूर्णांक64_t rcv_error:1;
		uपूर्णांक64_t not_IP:1;
		uपूर्णांक64_t is_mcast:1;
		uपूर्णांक64_t is_bcast:1;
		uपूर्णांक64_t IP_exc:1;
		uपूर्णांक64_t is_frag:1;
		uपूर्णांक64_t L4_error:1;
		uपूर्णांक64_t software:1;
		uपूर्णांक64_t is_v6:1;
		uपूर्णांक64_t dec_ipsec:1;
		uपूर्णांक64_t tcp_or_udp:1;
		uपूर्णांक64_t dec_ipcomp:1;
		uपूर्णांक64_t port:12;
		uपूर्णांक64_t vlan_id:12;
		uपूर्णांक64_t vlan_cfi:1;
		uपूर्णांक64_t unasचिन्हित:1;
		uपूर्णांक64_t vlan_stacked:1;
		uपूर्णांक64_t vlan_valid:1;
		uपूर्णांक64_t ip_offset:8;
		uपूर्णांक64_t bufs:8;
#पूर्ण_अगर
	पूर्ण s_cn68xx;

	/* use this to get at the 16 vlan bits */
	काष्ठा अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t unused1:16;
		uपूर्णांक64_t vlan:16;
		uपूर्णांक64_t unused2:32;
#अन्यथा
	        uपूर्णांक64_t unused2:32;
	        uपूर्णांक64_t vlan:16;
	        uपूर्णांक64_t unused1:16;

#पूर्ण_अगर
	पूर्ण svlan;

	/*
	 * use this काष्ठा अगर the hardware could not determine that
	 * the packet is ip.
	 */
	काष्ठा अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		/*
		 * HW sets this to the number of buffers used by this
		 * packet.
		 */
		uपूर्णांक64_t bufs:8;
		uपूर्णांक64_t unused:8;
		/* set to 1 अगर we found DSA/VLAN in the L2 */
		uपूर्णांक64_t vlan_valid:1;
		/* Set to 1 अगर the DSA/VLAN tag is stacked */
		uपूर्णांक64_t vlan_stacked:1;
		uपूर्णांक64_t unasचिन्हित:1;
		/*
		 * HW sets to the DSA/VLAN CFI flag (valid when
		 * vlan_valid)
		 */
		uपूर्णांक64_t vlan_cfi:1;
		/*
		 * HW sets to the DSA/VLAN_ID field (valid when
		 * vlan_valid).
		 */
		uपूर्णांक64_t vlan_id:12;
		/*
		 * Ring Identअगरier (अगर PCIe). Requires
		 * PIP_GBL_CTL[RING_EN]=1
		 */
		uपूर्णांक64_t pr:4;
		uपूर्णांक64_t unasचिन्हित2:12;
		/*
		 * reserved क्रम software use, hardware will clear on
		 * packet creation.
		 */
		uपूर्णांक64_t software:1;
		uपूर्णांक64_t unasचिन्हित3:1;
		/*
		 * set अगर the hardware determined that the packet is
		 * rarp.
		 */
		uपूर्णांक64_t is_rarp:1;
		/*
		 * set अगर the hardware determined that the packet is
		 * arp
		 */
		uपूर्णांक64_t is_arp:1;
		/*
		 * set अगर the hardware determined that the packet is a
		 * broadcast.
		 */
		uपूर्णांक64_t is_bcast:1;
		/*
		 * set अगर the hardware determined that the packet is a
		 * multi-cast
		 */
		uपूर्णांक64_t is_mcast:1;
		/*
		 * set अगर the packet may not be IP (must be one in
		 * this हाल)
		 */
		uपूर्णांक64_t not_IP:1;
		/* The receive पूर्णांकerface hardware detected a receive
		 * error.  Failure indicated in err_code below,
		 * decode:
		 *
		 * - 1 = partial error: a packet was partially
		 *	 received, but पूर्णांकernal buffering / bandwidth
		 *	 was not adequate to receive the entire
		 *	 packet.
		 * - 2 = jabber error: the RGMII packet was too large
		 *	 and is truncated.
		 * - 3 = overrun error: the RGMII packet is दीर्घer
		 *	 than allowed and had an FCS error.
		 * - 4 = oversize error: the RGMII packet is दीर्घer
		 *	 than allowed.
		 * - 5 = alignment error: the RGMII packet is not an
		 *	 पूर्णांकeger number of bytes
		 *	 and had an FCS error (100M and 10M only).
		 * - 6 = fragment error: the RGMII packet is लघुer
		 *	 than allowed and had an FCS error.
		 * - 7 = GMX FCS error: the RGMII packet had an FCS
		 *	 error.
		 * - 8 = undersize error: the RGMII packet is लघुer
		 *	 than allowed.
		 * - 9 = extend error: the RGMII packet had an extend
		 *	 error.
		 * - 10 = length mismatch error: the RGMII packet had
		 *	  a length that did not match the length field
		 *	  in the L2 HDR.
		 * - 11 = RGMII RX error/SPI4 DIP4 Error: the RGMII
		 *	  packet had one or more data reception errors
		 *	  (RXERR) or the SPI4 packet had one or more
		 *	  DIP4 errors.
		 * - 12 = RGMII skip error/SPI4 Abort Error: the RGMII
		 *	  packet was not large enough to cover the
		 *	  skipped bytes or the SPI4 packet was
		 *	  terminated with an About EOPS.
		 * - 13 = RGMII nibble error/SPI4 Port NXA Error: the
		 *	  RGMII packet had a studder error (data not
		 *	  repeated - 10/100M only) or the SPI4 packet
		 *	  was sent to an NXA.
		 * - 16 = FCS error: a SPI4.2 packet had an FCS error.
		 * - 17 = Skip error: a packet was not large enough to
		 *	  cover the skipped bytes.
		 * - 18 = L2 header malक्रमmed: the packet is not दीर्घ
		 *	  enough to contain the L2.
		 */

		uपूर्णांक64_t rcv_error:1;
		/*
		 * lower err_code = first-level descriptor of the
		 * work
		 */
		/*
		 * zero क्रम packet submitted by hardware that isn't on
		 * the slow path
		 */
		/* type is cvmx_pip_err_t (जोड़, so can't use directly */
		uपूर्णांक64_t err_code:8;
#अन्यथा
	        uपूर्णांक64_t err_code:8;
	        uपूर्णांक64_t rcv_error:1;
	        uपूर्णांक64_t not_IP:1;
	        uपूर्णांक64_t is_mcast:1;
	        uपूर्णांक64_t is_bcast:1;
	        uपूर्णांक64_t is_arp:1;
	        uपूर्णांक64_t is_rarp:1;
	        uपूर्णांक64_t unasचिन्हित3:1;
	        uपूर्णांक64_t software:1;
	        uपूर्णांक64_t unasचिन्हित2:4;
	        uपूर्णांक64_t unasचिन्हित2a:8;
	        uपूर्णांक64_t pr:4;
	        uपूर्णांक64_t vlan_id:12;
	        uपूर्णांक64_t vlan_cfi:1;
	        uपूर्णांक64_t unasचिन्हित:1;
	        uपूर्णांक64_t vlan_stacked:1;
	        uपूर्णांक64_t vlan_valid:1;
	        uपूर्णांक64_t unused:8;
	        uपूर्णांक64_t bufs:8;
#पूर्ण_अगर
	पूर्ण snoip;

पूर्ण cvmx_pip_wqe_word2;

जोड़ cvmx_pip_wqe_word0 अणु
	काष्ठा अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		/**
		 * raw chksum result generated by the HW
		 */
		uपूर्णांक16_t hw_chksum;
		/**
		 * Field unused by hardware - available क्रम software
		 */
		uपूर्णांक8_t unused;
		/**
		 * Next poपूर्णांकer used by hardware क्रम list मुख्यtenance.
		 * May be written/पढ़ो by HW beक्रमe the work queue
		 * entry is scheduled to a PP (Only 36 bits used in
		 * Octeon 1)
		 */
		uपूर्णांक64_t next_ptr:40;
#अन्यथा
		uपूर्णांक64_t next_ptr:40;
		uपूर्णांक8_t unused;
		uपूर्णांक16_t hw_chksum;
#पूर्ण_अगर
	पूर्ण cn38xx;
	काष्ठा अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t l4ptr:8;       /* 56..63 */
		uपूर्णांक64_t unused0:8;     /* 48..55 */
		uपूर्णांक64_t l3ptr:8;       /* 40..47 */
		uपूर्णांक64_t l2ptr:8;       /* 32..39 */
		uपूर्णांक64_t unused1:18;    /* 14..31 */
		uपूर्णांक64_t bpid:6;        /* 8..13 */
		uपूर्णांक64_t unused2:2;     /* 6..7 */
		uपूर्णांक64_t pknd:6;        /* 0..5 */
#अन्यथा
		uपूर्णांक64_t pknd:6;        /* 0..5 */
		uपूर्णांक64_t unused2:2;     /* 6..7 */
		uपूर्णांक64_t bpid:6;        /* 8..13 */
		uपूर्णांक64_t unused1:18;    /* 14..31 */
		uपूर्णांक64_t l2ptr:8;       /* 32..39 */
		uपूर्णांक64_t l3ptr:8;       /* 40..47 */
		uपूर्णांक64_t unused0:8;     /* 48..55 */
		uपूर्णांक64_t l4ptr:8;       /* 56..63 */
#पूर्ण_अगर
	पूर्ण cn68xx;
पूर्ण;

जोड़ cvmx_wqe_word0 अणु
	uपूर्णांक64_t u64;
	जोड़ cvmx_pip_wqe_word0 pip;
पूर्ण;

जोड़ cvmx_wqe_word1 अणु
	uपूर्णांक64_t u64;
	काष्ठा अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t len:16;
		uपूर्णांक64_t varies:14;
		/**
		 * the type of the tag (ORDERED, ATOMIC, शून्य)
		 */
		uपूर्णांक64_t tag_type:2;
		uपूर्णांक64_t tag:32;
#अन्यथा
		uपूर्णांक64_t tag:32;
		uपूर्णांक64_t tag_type:2;
		uपूर्णांक64_t varies:14;
		uपूर्णांक64_t len:16;
#पूर्ण_अगर
	पूर्ण;
	काष्ठा अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t len:16;
		uपूर्णांक64_t zero_0:1;
		/**
		 * HW sets this to what it thought the priority of
		 * the input packet was
		 */
		uपूर्णांक64_t qos:3;

		uपूर्णांक64_t zero_1:1;
		/**
		 * the group that the work queue entry will be scheduled to
		 */
		uपूर्णांक64_t grp:6;
		uपूर्णांक64_t zero_2:3;
		uपूर्णांक64_t tag_type:2;
		uपूर्णांक64_t tag:32;
#अन्यथा
		uपूर्णांक64_t tag:32;
		uपूर्णांक64_t tag_type:2;
		uपूर्णांक64_t zero_2:3;
		uपूर्णांक64_t grp:6;
		uपूर्णांक64_t zero_1:1;
		uपूर्णांक64_t qos:3;
		uपूर्णांक64_t zero_0:1;
		uपूर्णांक64_t len:16;
#पूर्ण_अगर
	पूर्ण cn68xx;
	काष्ठा अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		/**
		 * HW sets to the total number of bytes in the packet
		 */
		uपूर्णांक64_t len:16;
		/**
		 * HW sets this to input physical port
		 */
		uपूर्णांक64_t ipprt:6;

		/**
		 * HW sets this to what it thought the priority of
		 * the input packet was
		 */
		uपूर्णांक64_t qos:3;

		/**
		 * the group that the work queue entry will be scheduled to
		 */
		uपूर्णांक64_t grp:4;
		/**
		 * the type of the tag (ORDERED, ATOMIC, शून्य)
		 */
		uपूर्णांक64_t tag_type:3;
		/**
		 * the synchronization/ordering tag
		 */
		uपूर्णांक64_t tag:32;
#अन्यथा
		uपूर्णांक64_t tag:32;
		uपूर्णांक64_t tag_type:2;
		uपूर्णांक64_t zero_2:1;
		uपूर्णांक64_t grp:4;
		uपूर्णांक64_t qos:3;
		uपूर्णांक64_t ipprt:6;
		uपूर्णांक64_t len:16;
#पूर्ण_अगर
	पूर्ण cn38xx;
पूर्ण;

/**
 * Work queue entry क्रमmat
 *
 * must be 8-byte aligned
 */
काष्ठा cvmx_wqe अणु

    /*****************************************************************
     * WORD 0
     *	HW WRITE: the following 64 bits are filled by HW when a packet arrives
     */
	जोड़ cvmx_wqe_word0 word0;

    /*****************************************************************
     * WORD 1
     *	HW WRITE: the following 64 bits are filled by HW when a packet arrives
     */
	जोड़ cvmx_wqe_word1 word1;

    /**
     * WORD 2 HW WRITE: the following 64-bits are filled in by
     *	 hardware when a packet arrives This indicates a variety of
     *	 status and error conditions.
     */
	cvmx_pip_wqe_word2 word2;

    /**
     * Poपूर्णांकer to the first segment of the packet.
     */
	जोड़ cvmx_buf_ptr packet_ptr;

    /**
     *	 HW WRITE: octeon will fill in a programmable amount from the
     *		   packet, up to (at most, but perhaps less) the amount
     *		   needed to fill the work queue entry to 128 bytes
     *
     *	 If the packet is recognized to be IP, the hardware starts
     *	 (except that the IPv4 header is padded क्रम appropriate
     *	 alignment) writing here where the IP header starts.  If the
     *	 packet is not recognized to be IP, the hardware starts
     *	 writing the beginning of the packet here.
     */
	uपूर्णांक8_t packet_data[96];

    /**
     * If desired, SW can make the work Q entry any length. For the
     * purposes of discussion here, Assume 128B always, as this is all that
     * the hardware deals with.
     *
     */

पूर्ण CVMX_CACHE_LINE_ALIGNED;

अटल अंतरभूत पूर्णांक cvmx_wqe_get_port(काष्ठा cvmx_wqe *work)
अणु
	पूर्णांक port;

	अगर (octeon_has_feature(OCTEON_FEATURE_CN68XX_WQE))
		port = work->word2.s_cn68xx.port;
	अन्यथा
		port = work->word1.cn38xx.ipprt;

	वापस port;
पूर्ण

अटल अंतरभूत व्योम cvmx_wqe_set_port(काष्ठा cvmx_wqe *work, पूर्णांक port)
अणु
	अगर (octeon_has_feature(OCTEON_FEATURE_CN68XX_WQE))
		work->word2.s_cn68xx.port = port;
	अन्यथा
		work->word1.cn38xx.ipprt = port;
पूर्ण

अटल अंतरभूत पूर्णांक cvmx_wqe_get_grp(काष्ठा cvmx_wqe *work)
अणु
	पूर्णांक grp;

	अगर (octeon_has_feature(OCTEON_FEATURE_CN68XX_WQE))
		grp = work->word1.cn68xx.grp;
	अन्यथा
		grp = work->word1.cn38xx.grp;

	वापस grp;
पूर्ण

अटल अंतरभूत व्योम cvmx_wqe_set_grp(काष्ठा cvmx_wqe *work, पूर्णांक grp)
अणु
	अगर (octeon_has_feature(OCTEON_FEATURE_CN68XX_WQE))
		work->word1.cn68xx.grp = grp;
	अन्यथा
		work->word1.cn38xx.grp = grp;
पूर्ण

अटल अंतरभूत पूर्णांक cvmx_wqe_get_qos(काष्ठा cvmx_wqe *work)
अणु
	पूर्णांक qos;

	अगर (octeon_has_feature(OCTEON_FEATURE_CN68XX_WQE))
		qos = work->word1.cn68xx.qos;
	अन्यथा
		qos = work->word1.cn38xx.qos;

	वापस qos;
पूर्ण

अटल अंतरभूत व्योम cvmx_wqe_set_qos(काष्ठा cvmx_wqe *work, पूर्णांक qos)
अणु
	अगर (octeon_has_feature(OCTEON_FEATURE_CN68XX_WQE))
		work->word1.cn68xx.qos = qos;
	अन्यथा
		work->word1.cn38xx.qos = qos;
पूर्ण

#पूर्ण_अगर /* __CVMX_WQE_H__ */
