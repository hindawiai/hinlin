<शैली गुरु>
#अगर_अघोषित __LINUX_ERSPAN_H
#घोषणा __LINUX_ERSPAN_H

/*
 * GRE header क्रम ERSPAN type I encapsulation (4 octets [34:37])
 *      0                   1                   2                   3
 *      0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
 *     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *     |0|0|0|0|0|00000|000000000|00000|    Protocol Type क्रम ERSPAN   |
 *     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *
 *  The Type I ERSPAN frame क्रमmat is based on the barebones IP + GRE
 *  encapsulation (as described above) on top of the raw mirrored frame.
 *  There is no extra ERSPAN header.
 *
 *
 * GRE header क्रम ERSPAN type II and II encapsulation (8 octets [34:41])
 *       0                   1                   2                   3
 *      0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
 *     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *     |0|0|0|1|0|00000|000000000|00000|    Protocol Type क्रम ERSPAN   |
 *     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *     |      Sequence Number (increments per packet per session)      |
 *     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *
 *  Note that in the above GRE header [RFC1701] out of the C, R, K, S,
 *  s, Recur, Flags, Version fields only S (bit 03) is set to 1. The
 *  other fields are set to zero, so only a sequence number follows.
 *
 *  ERSPAN Version 1 (Type II) header (8 octets [42:49])
 *  0                   1                   2                   3
 *  0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |  Ver  |          VLAN         | COS | En|T|    Session ID     |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |      Reserved         |                  Index                |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *
 *
 *  ERSPAN Version 2 (Type III) header (12 octets [42:49])
 *  0                   1                   2                   3
 *  0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |  Ver  |          VLAN         | COS |BSO|T|     Session ID    |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |                          Timestamp                            |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |             SGT               |P|    FT   |   Hw ID   |D|Gra|O|
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *
 *      Platक्रमm Specअगरic SubHeader (8 octets, optional)
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |  Platf ID |               Platक्रमm Specअगरic Info              |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |                  Platक्रमm Specअगरic Info                       |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *
 * GRE proto ERSPAN type I/II = 0x88BE, type III = 0x22EB
 */

#समावेश <uapi/linux/erspan.h>

#घोषणा ERSPAN_VERSION	0x1	/* ERSPAN type II */
#घोषणा VER_MASK	0xf000
#घोषणा VLAN_MASK	0x0fff
#घोषणा COS_MASK	0xe000
#घोषणा EN_MASK		0x1800
#घोषणा T_MASK		0x0400
#घोषणा ID_MASK		0x03ff
#घोषणा INDEX_MASK	0xfffff

#घोषणा ERSPAN_VERSION2	0x2	/* ERSPAN type III*/
#घोषणा BSO_MASK	EN_MASK
#घोषणा SGT_MASK	0xffff0000
#घोषणा P_MASK		0x8000
#घोषणा FT_MASK		0x7c00
#घोषणा HWID_MASK	0x03f0
#घोषणा सूची_MASK	0x0008
#घोषणा GRA_MASK	0x0006
#घोषणा O_MASK		0x0001

#घोषणा HWID_OFFSET    4
#घोषणा सूची_OFFSET     3

क्रमागत erspan_encap_type अणु
	ERSPAN_ENCAP_NOVLAN = 0x0,	/* originally without VLAN tag */
	ERSPAN_ENCAP_ISL = 0x1,		/* originally ISL encapsulated */
	ERSPAN_ENCAP_8021Q = 0x2,	/* originally 802.1Q encapsulated */
	ERSPAN_ENCAP_INFRAME = 0x3,	/* VLAN tag perserved in frame */
पूर्ण;

#घोषणा ERSPAN_V1_MDSIZE	4
#घोषणा ERSPAN_V2_MDSIZE	8

काष्ठा erspan_base_hdr अणु
#अगर defined(__LITTLE_ENDIAN_BITFIELD)
	__u8	vlan_upper:4,
		ver:4;
	__u8	vlan:8;
	__u8	session_id_upper:2,
		t:1,
		en:2,
		cos:3;
	__u8	session_id:8;
#या_अगर defined(__BIG_ENDIAN_BITFIELD)
	__u8	ver: 4,
		vlan_upper:4;
	__u8	vlan:8;
	__u8	cos:3,
		en:2,
		t:1,
		session_id_upper:2;
	__u8	session_id:8;
#अन्यथा
#त्रुटि "Please fix <asm/byteorder.h>"
#पूर्ण_अगर
पूर्ण;

अटल अंतरभूत व्योम set_session_id(काष्ठा erspan_base_hdr *ershdr, u16 id)
अणु
	ershdr->session_id = id & 0xff;
	ershdr->session_id_upper = (id >> 8) & 0x3;
पूर्ण

अटल अंतरभूत u16 get_session_id(स्थिर काष्ठा erspan_base_hdr *ershdr)
अणु
	वापस (ershdr->session_id_upper << 8) + ershdr->session_id;
पूर्ण

अटल अंतरभूत व्योम set_vlan(काष्ठा erspan_base_hdr *ershdr, u16 vlan)
अणु
	ershdr->vlan = vlan & 0xff;
	ershdr->vlan_upper = (vlan >> 8) & 0xf;
पूर्ण

अटल अंतरभूत u16 get_vlan(स्थिर काष्ठा erspan_base_hdr *ershdr)
अणु
	वापस (ershdr->vlan_upper << 8) + ershdr->vlan;
पूर्ण

अटल अंतरभूत व्योम set_hwid(काष्ठा erspan_md2 *md2, u8 hwid)
अणु
	md2->hwid = hwid & 0xf;
	md2->hwid_upper = (hwid >> 4) & 0x3;
पूर्ण

अटल अंतरभूत u8 get_hwid(स्थिर काष्ठा erspan_md2 *md2)
अणु
	वापस (md2->hwid_upper << 4) + md2->hwid;
पूर्ण

अटल अंतरभूत पूर्णांक erspan_hdr_len(पूर्णांक version)
अणु
	अगर (version == 0)
		वापस 0;

	वापस माप(काष्ठा erspan_base_hdr) +
	       (version == 1 ? ERSPAN_V1_MDSIZE : ERSPAN_V2_MDSIZE);
पूर्ण

अटल अंतरभूत u8 tos_to_cos(u8 tos)
अणु
	u8 dscp, cos;

	dscp = tos >> 2;
	cos = dscp >> 3;
	वापस cos;
पूर्ण

अटल अंतरभूत व्योम erspan_build_header(काष्ठा sk_buff *skb,
				u32 id, u32 index,
				bool truncate, bool is_ipv4)
अणु
	काष्ठा ethhdr *eth = (काष्ठा ethhdr *)skb->data;
	क्रमागत erspan_encap_type enc_type;
	काष्ठा erspan_base_hdr *ershdr;
	काष्ठा qtag_prefix अणु
		__be16 eth_type;
		__be16 tci;
	पूर्ण *qp;
	u16 vlan_tci = 0;
	u8 tos;
	__be32 *idx;

	tos = is_ipv4 ? ip_hdr(skb)->tos :
			(ipv6_hdr(skb)->priority << 4) +
			(ipv6_hdr(skb)->flow_lbl[0] >> 4);

	enc_type = ERSPAN_ENCAP_NOVLAN;

	/* If mirrored packet has vlan tag, extract tci and
	 *  perserve vlan header in the mirrored frame.
	 */
	अगर (eth->h_proto == htons(ETH_P_8021Q)) अणु
		qp = (काष्ठा qtag_prefix *)(skb->data + 2 * ETH_ALEN);
		vlan_tci = ntohs(qp->tci);
		enc_type = ERSPAN_ENCAP_INFRAME;
	पूर्ण

	skb_push(skb, माप(*ershdr) + ERSPAN_V1_MDSIZE);
	ershdr = (काष्ठा erspan_base_hdr *)skb->data;
	स_रखो(ershdr, 0, माप(*ershdr) + ERSPAN_V1_MDSIZE);

	/* Build base header */
	ershdr->ver = ERSPAN_VERSION;
	ershdr->cos = tos_to_cos(tos);
	ershdr->en = enc_type;
	ershdr->t = truncate;
	set_vlan(ershdr, vlan_tci);
	set_session_id(ershdr, id);

	/* Build metadata */
	idx = (__be32 *)(ershdr + 1);
	*idx = htonl(index & INDEX_MASK);
पूर्ण

/* ERSPAN GRA: बारtamp granularity
 *   00b --> granularity = 100 microseconds
 *   01b --> granularity = 100 nanoseconds
 *   10b --> granularity = IEEE 1588
 * Here we only support 100 microseconds.
 */
अटल अंतरभूत __be32 erspan_get_बारtamp(व्योम)
अणु
	u64 h_usecs;
	kसमय_प्रकार kt;

	kt = kसमय_get_real();
	h_usecs = kसमय_भागns(kt, 100 * NSEC_PER_USEC);

	/* ERSPAN base header only has 32-bit,
	 * so it wraps around 4 days.
	 */
	वापस htonl((u32)h_usecs);
पूर्ण

/* ERSPAN BSO (Bad/Short/Oversized), see RFC1757
 *   00b --> Good frame with no error, or unknown पूर्णांकegrity
 *   01b --> Payload is a Short Frame
 *   10b --> Payload is an Oversized Frame
 *   11b --> Payload is a Bad Frame with CRC or Alignment Error
 */
क्रमागत erspan_bso अणु
	BSO_NOERROR = 0x0,
	BSO_SHORT = 0x1,
	BSO_OVERSIZED = 0x2,
	BSO_BAD = 0x3,
पूर्ण;

अटल अंतरभूत u8 erspan_detect_bso(काष्ठा sk_buff *skb)
अणु
	/* BSO_BAD is not handled because the frame CRC
	 * or alignment error inक्रमmation is in FCS.
	 */
	अगर (skb->len < ETH_ZLEN)
		वापस BSO_SHORT;

	अगर (skb->len > ETH_FRAME_LEN)
		वापस BSO_OVERSIZED;

	वापस BSO_NOERROR;
पूर्ण

अटल अंतरभूत व्योम erspan_build_header_v2(काष्ठा sk_buff *skb,
					  u32 id, u8 direction, u16 hwid,
					  bool truncate, bool is_ipv4)
अणु
	काष्ठा ethhdr *eth = (काष्ठा ethhdr *)skb->data;
	काष्ठा erspan_base_hdr *ershdr;
	काष्ठा erspan_md2 *md2;
	काष्ठा qtag_prefix अणु
		__be16 eth_type;
		__be16 tci;
	पूर्ण *qp;
	u16 vlan_tci = 0;
	u8 gra = 0; /* 100 usec */
	u8 bso = 0; /* Bad/Short/Oversized */
	u8 sgt = 0;
	u8 tos;

	tos = is_ipv4 ? ip_hdr(skb)->tos :
			(ipv6_hdr(skb)->priority << 4) +
			(ipv6_hdr(skb)->flow_lbl[0] >> 4);

	/* Unlike v1, v2 करोes not have En field,
	 * so only extract vlan tci field.
	 */
	अगर (eth->h_proto == htons(ETH_P_8021Q)) अणु
		qp = (काष्ठा qtag_prefix *)(skb->data + 2 * ETH_ALEN);
		vlan_tci = ntohs(qp->tci);
	पूर्ण

	bso = erspan_detect_bso(skb);
	skb_push(skb, माप(*ershdr) + ERSPAN_V2_MDSIZE);
	ershdr = (काष्ठा erspan_base_hdr *)skb->data;
	स_रखो(ershdr, 0, माप(*ershdr) + ERSPAN_V2_MDSIZE);

	/* Build base header */
	ershdr->ver = ERSPAN_VERSION2;
	ershdr->cos = tos_to_cos(tos);
	ershdr->en = bso;
	ershdr->t = truncate;
	set_vlan(ershdr, vlan_tci);
	set_session_id(ershdr, id);

	/* Build metadata */
	md2 = (काष्ठा erspan_md2 *)(ershdr + 1);
	md2->बारtamp = erspan_get_बारtamp();
	md2->sgt = htons(sgt);
	md2->p = 1;
	md2->ft = 0;
	md2->dir = direction;
	md2->gra = gra;
	md2->o = 0;
	set_hwid(md2, hwid);
पूर्ण

#पूर्ण_अगर
