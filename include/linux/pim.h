<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __LINUX_PIM_H
#घोषणा __LINUX_PIM_H

#समावेश <linux/skbuff.h>
#समावेश <यंत्र/byteorder.h>

/* Message types - V1 */
#घोषणा PIM_V1_VERSION		cpu_to_be32(0x10000000)
#घोषणा PIM_V1_REGISTER		1

/* Message types - V2 */
#घोषणा PIM_VERSION		2

/* RFC7761, sec 4.9:
 *  Type
 *        Types क्रम specअगरic PIM messages.  PIM Types are:
 *
 *  Message Type                          Destination
 *  ---------------------------------------------------------------------
 *  0 = Hello                             Multicast to ALL-PIM-ROUTERS
 *  1 = Register                          Unicast to RP
 *  2 = Register-Stop                     Unicast to source of Register
 *                                        packet
 *  3 = Join/Prune                        Multicast to ALL-PIM-ROUTERS
 *  4 = Bootstrap                         Multicast to ALL-PIM-ROUTERS
 *  5 = Assert                            Multicast to ALL-PIM-ROUTERS
 *  6 = Graft (used in PIM-DM only)       Unicast to RPF'(S)
 *  7 = Graft-Ack (used in PIM-DM only)   Unicast to source of Graft
 *                                        packet
 *  8 = Candidate-RP-Advertisement        Unicast to Doमुख्य's BSR
 */
क्रमागत अणु
	PIM_TYPE_HELLO,
	PIM_TYPE_REGISTER,
	PIM_TYPE_REGISTER_STOP,
	PIM_TYPE_JOIN_PRUNE,
	PIM_TYPE_BOOTSTRAP,
	PIM_TYPE_ASSERT,
	PIM_TYPE_GRAFT,
	PIM_TYPE_GRAFT_ACK,
	PIM_TYPE_CANDIDATE_RP_ADV
पूर्ण;

#घोषणा PIM_शून्य_REGISTER	cpu_to_be32(0x40000000)

/* RFC7761, sec 4.9:
 * The PIM header common to all PIM messages is:
 *   0                   1                   2                   3
 *   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
 *  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *  |PIM Ver| Type  |   Reserved    |           Checksum            |
 *  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 */
काष्ठा pimhdr अणु
	__u8	type;
	__u8	reserved;
	__be16	csum;
पूर्ण;

/* PIMv2 रेजिस्टर message header layout (ietf-draft-idmr-pimvsm-v2-00.ps */
काष्ठा pimreghdr अणु
	__u8	type;
	__u8	reserved;
	__be16	csum;
	__be32	flags;
पूर्ण;

पूर्णांक pim_rcv_v1(काष्ठा sk_buff *skb);

अटल अंतरभूत bool ipmr_pimsm_enabled(व्योम)
अणु
	वापस IS_BUILTIN(CONFIG_IP_PIMSM_V1) || IS_BUILTIN(CONFIG_IP_PIMSM_V2);
पूर्ण

अटल अंतरभूत काष्ठा pimhdr *pim_hdr(स्थिर काष्ठा sk_buff *skb)
अणु
	वापस (काष्ठा pimhdr *)skb_transport_header(skb);
पूर्ण

अटल अंतरभूत u8 pim_hdr_version(स्थिर काष्ठा pimhdr *pimhdr)
अणु
	वापस pimhdr->type >> 4;
पूर्ण

अटल अंतरभूत u8 pim_hdr_type(स्थिर काष्ठा pimhdr *pimhdr)
अणु
	वापस pimhdr->type & 0xf;
पूर्ण

/* check अगर the address is 224.0.0.13, RFC7761 sec 4.3.1 */
अटल अंतरभूत bool pim_ipv4_all_pim_routers(__be32 addr)
अणु
	वापस addr == htonl(0xE000000D);
पूर्ण
#पूर्ण_अगर
