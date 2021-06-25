<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ WITH Linux-syscall-note */
/*
 * INET		An implementation of the TCP/IP protocol suite क्रम the LINUX
 *		operating प्रणाली.  INET is implemented using the  BSD Socket
 *		पूर्णांकerface as the means of communication with the user level.
 *
 *		Definitions क्रम the ICMP protocol.
 *
 * Version:	@(#)icmp.h	1.0.3	04/28/93
 *
 * Author:	Fred N. van Kempen, <waltje@uWalt.NL.Mugnet.ORG>
 *
 *		This program is मुक्त software; you can redistribute it and/or
 *		modअगरy it under the terms of the GNU General Public License
 *		as published by the Free Software Foundation; either version
 *		2 of the License, or (at your option) any later version.
 */
#अगर_अघोषित _UAPI_LINUX_ICMP_H
#घोषणा _UAPI_LINUX_ICMP_H

#समावेश <linux/types.h>
#समावेश <यंत्र/byteorder.h>
#समावेश <linux/in.h>
#समावेश <linux/अगर.h>
#समावेश <linux/in6.h>

#घोषणा ICMP_ECHOREPLY		0	/* Echo Reply			*/
#घोषणा ICMP_DEST_UNREACH	3	/* Destination Unreachable	*/
#घोषणा ICMP_SOURCE_QUENCH	4	/* Source Quench		*/
#घोषणा ICMP_REसूचीECT		5	/* Redirect (change route)	*/
#घोषणा ICMP_ECHO		8	/* Echo Request			*/
#घोषणा ICMP_TIME_EXCEEDED	11	/* Time Exceeded		*/
#घोषणा ICMP_PARAMETERPROB	12	/* Parameter Problem		*/
#घोषणा ICMP_TIMESTAMP		13	/* Timestamp Request		*/
#घोषणा ICMP_TIMESTAMPREPLY	14	/* Timestamp Reply		*/
#घोषणा ICMP_INFO_REQUEST	15	/* Inक्रमmation Request		*/
#घोषणा ICMP_INFO_REPLY		16	/* Inक्रमmation Reply		*/
#घोषणा ICMP_ADDRESS		17	/* Address Mask Request		*/
#घोषणा ICMP_ADDRESSREPLY	18	/* Address Mask Reply		*/
#घोषणा NR_ICMP_TYPES		18


/* Codes क्रम UNREACH. */
#घोषणा ICMP_NET_UNREACH	0	/* Network Unreachable		*/
#घोषणा ICMP_HOST_UNREACH	1	/* Host Unreachable		*/
#घोषणा ICMP_PROT_UNREACH	2	/* Protocol Unreachable		*/
#घोषणा ICMP_PORT_UNREACH	3	/* Port Unreachable		*/
#घोषणा ICMP_FRAG_NEEDED	4	/* Fragmentation Needed/DF set	*/
#घोषणा ICMP_SR_FAILED		5	/* Source Route failed		*/
#घोषणा ICMP_NET_UNKNOWN	6
#घोषणा ICMP_HOST_UNKNOWN	7
#घोषणा ICMP_HOST_ISOLATED	8
#घोषणा ICMP_NET_ANO		9
#घोषणा ICMP_HOST_ANO		10
#घोषणा ICMP_NET_UNR_TOS	11
#घोषणा ICMP_HOST_UNR_TOS	12
#घोषणा ICMP_PKT_FILTERED	13	/* Packet filtered */
#घोषणा ICMP_PREC_VIOLATION	14	/* Precedence violation */
#घोषणा ICMP_PREC_CUTOFF	15	/* Precedence cut off */
#घोषणा NR_ICMP_UNREACH		15	/* instead of hardcoding immediate value */

/* Codes क्रम REसूचीECT. */
#घोषणा ICMP_REसूची_NET		0	/* Redirect Net			*/
#घोषणा ICMP_REसूची_HOST		1	/* Redirect Host		*/
#घोषणा ICMP_REसूची_NETTOS	2	/* Redirect Net क्रम TOS		*/
#घोषणा ICMP_REसूची_HOSTTOS	3	/* Redirect Host क्रम TOS	*/

/* Codes क्रम TIME_EXCEEDED. */
#घोषणा ICMP_EXC_TTL		0	/* TTL count exceeded		*/
#घोषणा ICMP_EXC_FRAGTIME	1	/* Fragment Reass समय exceeded	*/

/* Codes क्रम EXT_ECHO (PROBE) */
#घोषणा ICMP_EXT_ECHO			42
#घोषणा ICMP_EXT_ECHOREPLY		43
#घोषणा ICMP_EXT_CODE_MAL_QUERY		1	/* Malक्रमmed Query */
#घोषणा ICMP_EXT_CODE_NO_IF		2	/* No such Interface */
#घोषणा ICMP_EXT_CODE_NO_TABLE_ENT	3	/* No such Table Entry */
#घोषणा ICMP_EXT_CODE_MULT_IFS		4	/* Multiple Interfaces Satisfy Query */

/* Constants क्रम EXT_ECHO (PROBE) */
#घोषणा ICMP_EXT_ECHOREPLY_ACTIVE	(1 << 2)/* active bit in reply message */
#घोषणा ICMP_EXT_ECHOREPLY_IPV4		(1 << 1)/* ipv4 bit in reply message */
#घोषणा ICMP_EXT_ECHOREPLY_IPV6		1	/* ipv6 bit in reply message */
#घोषणा ICMP_EXT_ECHO_CTYPE_NAME	1
#घोषणा ICMP_EXT_ECHO_CTYPE_INDEX	2
#घोषणा ICMP_EXT_ECHO_CTYPE_ADDR	3
#घोषणा ICMP_AFI_IP			1	/* Address Family Identअगरier क्रम ipv4 */
#घोषणा ICMP_AFI_IP6			2	/* Address Family Identअगरier क्रम ipv6 */

काष्ठा icmphdr अणु
  __u8		type;
  __u8		code;
  __sum16	checksum;
  जोड़ अणु
	काष्ठा अणु
		__be16	id;
		__be16	sequence;
	पूर्ण echo;
	__be32	gateway;
	काष्ठा अणु
		__be16	__unused;
		__be16	mtu;
	पूर्ण frag;
	__u8	reserved[4];
  पूर्ण un;
पूर्ण;


/*
 *	स्थिरants क्रम (set|get)sockopt
 */

#घोषणा ICMP_FILTER			1

काष्ठा icmp_filter अणु
	__u32		data;
पूर्ण;

/* RFC 4884 extension काष्ठा: one per message */
काष्ठा icmp_ext_hdr अणु
#अगर defined(__LITTLE_ENDIAN_BITFIELD)
	__u8		reserved1:4,
			version:4;
#या_अगर defined(__BIG_ENDIAN_BITFIELD)
	__u8		version:4,
			reserved1:4;
#अन्यथा
#त्रुटि	"Please fix <asm/byteorder.h>"
#पूर्ण_अगर
	__u8		reserved2;
	__sum16		checksum;
पूर्ण;

/* RFC 4884 extension object header: one क्रम each object */
काष्ठा icmp_extobj_hdr अणु
	__be16		length;
	__u8		class_num;
	__u8		class_type;
पूर्ण;

/* RFC 8335: 2.1 Header क्रम c-type 3 payload */
काष्ठा icmp_ext_echo_ctype3_hdr अणु
	__be16		afi;
	__u8		addrlen;
	__u8		reserved;
पूर्ण;

/* RFC 8335: 2.1 Interface Identअगरication Object */
काष्ठा icmp_ext_echo_iio अणु
	काष्ठा icmp_extobj_hdr extobj_hdr;
	जोड़ अणु
		अक्षर name[IFNAMSIZ];
		__be32 अगरindex;
		काष्ठा अणु
			काष्ठा icmp_ext_echo_ctype3_hdr ctype3_hdr;
			जोड़ अणु
				काष्ठा in_addr	ipv4_addr;
				काष्ठा in6_addr	ipv6_addr;
			पूर्ण ip_addr;
		पूर्ण addr;
	पूर्ण ident;
पूर्ण;
#पूर्ण_अगर /* _UAPI_LINUX_ICMP_H */
