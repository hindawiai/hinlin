<शैली गुरु>
#अगर_अघोषित __NET_NSH_H
#घोषणा __NET_NSH_H 1

#समावेश <linux/skbuff.h>

/*
 * Network Service Header:
 *  0                   1                   2                   3
 *  0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |Ver|O|U|    TTL    |   Length  |U|U|U|U|MD Type| Next Protocol |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |          Service Path Identअगरier (SPI)        | Service Index |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |                                                               |
 * ~               Mandatory/Optional Context Headers              ~
 * |                                                               |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *
 * Version: The version field is used to ensure backward compatibility
 * going क्रमward with future NSH specअगरication updates.  It MUST be set
 * to 0x0 by the sender, in this first revision of NSH.  Given the
 * widespपढ़ो implementation of existing hardware that uses the first
 * nibble after an MPLS label stack क्रम ECMP decision processing, this
 * करोcument reserves version 01b and this value MUST NOT be used in
 * future versions of the protocol.  Please see [RFC7325] क्रम further
 * discussion of MPLS-related क्रमwarding requirements.
 *
 * O bit: Setting this bit indicates an Operations, Administration, and
 * Maपूर्णांकenance (OAM) packet.  The actual क्रमmat and processing of SFC
 * OAM packets is outside the scope of this specअगरication (see क्रम
 * example [I-D.ietf-sfc-oam-framework] क्रम one approach).
 *
 * The O bit MUST be set क्रम OAM packets and MUST NOT be set क्रम non-OAM
 * packets.  The O bit MUST NOT be modअगरied aदीर्घ the SFP.
 *
 * SF/SFF/SFC Proxy/Classअगरier implementations that करो not support SFC
 * OAM procedures SHOULD discard packets with O bit set, but MAY support
 * a configurable parameter to enable क्रमwarding received SFC OAM
 * packets unmodअगरied to the next element in the chain.  Forwarding OAM
 * packets unmodअगरied by SFC elements that करो not support SFC OAM
 * procedures may be acceptable क्रम a subset of OAM functions, but can
 * result in unexpected outcomes क्रम others, thus it is recommended to
 * analyze the impact of क्रमwarding an OAM packet क्रम all OAM functions
 * prior to enabling this behavior.  The configurable parameter MUST be
 * disabled by शेष.
 *
 * TTL: Indicates the maximum SFF hops क्रम an SFP.  This field is used
 * क्रम service plane loop detection.  The initial TTL value SHOULD be
 * configurable via the control plane; the configured initial value can
 * be specअगरic to one or more SFPs.  If no initial value is explicitly
 * provided, the शेष initial TTL value of 63 MUST be used.  Each SFF
 * involved in क्रमwarding an NSH packet MUST decrement the TTL value by
 * 1 prior to NSH क्रमwarding lookup.  Decrementing by 1 from an incoming
 * value of 0 shall result in a TTL value of 63.  The packet MUST NOT be
 * क्रमwarded अगर TTL is, after decrement, 0.
 *
 * All other flag fields, marked U, are unasचिन्हित and available क्रम
 * future use, see Section 11.2.1.  Unasचिन्हित bits MUST be set to zero
 * upon origination, and MUST be ignored and preserved unmodअगरied by
 * other NSH supporting elements.  Elements which करो not understand the
 * meaning of any of these bits MUST NOT modअगरy their actions based on
 * those unknown bits.
 *
 * Length: The total length, in 4-byte words, of NSH including the Base
 * Header, the Service Path Header, the Fixed Length Context Header or
 * Variable Length Context Header(s).  The length MUST be 0x6 क्रम MD
 * Type equal to 0x1, and MUST be 0x2 or greater क्रम MD Type equal to
 * 0x2.  The length of the NSH header MUST be an पूर्णांकeger multiple of 4
 * bytes, thus variable length metadata is always padded out to a
 * multiple of 4 bytes.
 *
 * MD Type: Indicates the क्रमmat of NSH beyond the mandatory Base Header
 * and the Service Path Header.  MD Type defines the क्रमmat of the
 * metadata being carried.
 *
 * 0x0 - This is a reserved value.  Implementations SHOULD silently
 * discard packets with MD Type 0x0.
 *
 * 0x1 - This indicates that the क्रमmat of the header includes a fixed
 * length Context Header (see Figure 4 below).
 *
 * 0x2 - This करोes not mandate any headers beyond the Base Header and
 * Service Path Header, but may contain optional variable length Context
 * Header(s).  The semantics of the variable length Context Header(s)
 * are not defined in this करोcument.  The क्रमmat of the optional
 * variable length Context Headers is provided in Section 2.5.1.
 *
 * 0xF - This value is reserved क्रम experimentation and testing, as per
 * [RFC3692].  Implementations not explicitly configured to be part of
 * an experiment SHOULD silently discard packets with MD Type 0xF.
 *
 * Next Protocol: indicates the protocol type of the encapsulated data.
 * NSH करोes not alter the inner payload, and the semantics on the inner
 * protocol reमुख्य unchanged due to NSH service function chaining.
 * Please see the IANA Considerations section below, Section 11.2.5.
 *
 * This करोcument defines the following Next Protocol values:
 *
 * 0x1: IPv4
 * 0x2: IPv6
 * 0x3: Ethernet
 * 0x4: NSH
 * 0x5: MPLS
 * 0xFE: Experiment 1
 * 0xFF: Experiment 2
 *
 * Packets with Next Protocol values not supported SHOULD be silently
 * dropped by शेष, although an implementation MAY provide a
 * configuration parameter to क्रमward them.  Additionally, an
 * implementation not explicitly configured क्रम a specअगरic experiment
 * [RFC3692] SHOULD silently drop packets with Next Protocol values 0xFE
 * and 0xFF.
 *
 * Service Path Identअगरier (SPI): Identअगरies a service path.
 * Participating nodes MUST use this identअगरier क्रम Service Function
 * Path selection.  The initial classअगरier MUST set the appropriate SPI
 * क्रम a given classअगरication result.
 *
 * Service Index (SI): Provides location within the SFP.  The initial
 * classअगरier क्रम a given SFP SHOULD set the SI to 255, however the
 * control plane MAY configure the initial value of SI as appropriate
 * (i.e., taking पूर्णांकo account the length of the service function path).
 * The Service Index MUST be decremented by a value of 1 by Service
 * Functions or by SFC Proxy nodes after perक्रमming required services
 * and the new decremented SI value MUST be used in the egress packet's
 * NSH.  The initial Classअगरier MUST send the packet to the first SFF in
 * the identअगरied SFP क्रम क्रमwarding aदीर्घ an SFP.  If re-classअगरication
 * occurs, and that re-classअगरication results in a new SPI, the
 * (re)classअगरier is, in effect, the initial classअगरier क्रम the
 * resultant SPI.
 *
 * The SI is used in conjunction the with Service Path Identअगरier क्रम
 * Service Function Path Selection and क्रम determining the next SFF/SF
 * in the path.  The SI is also valuable when troubleshooting or
 * reporting service paths.  Additionally, जबतक the TTL field is the
 * मुख्य mechanism क्रम service plane loop detection, the SI can also be
 * used क्रम detecting service plane loops.
 *
 * When the Base Header specअगरies MD Type = 0x1, a Fixed Length Context
 * Header (16-bytes) MUST be present immediately following the Service
 * Path Header. The value of a Fixed Length Context
 * Header that carries no metadata MUST be set to zero.
 *
 * When the base header specअगरies MD Type = 0x2, zero or more Variable
 * Length Context Headers MAY be added, immediately following the
 * Service Path Header (see Figure 5).  Thereक्रमe, Length = 0x2,
 * indicates that only the Base Header followed by the Service Path
 * Header are present.  The optional Variable Length Context Headers
 * MUST be of an पूर्णांकeger number of 4-bytes.  The base header Length
 * field MUST be used to determine the offset to locate the original
 * packet or frame क्रम SFC nodes that require access to that
 * inक्रमmation.
 *
 * The क्रमmat of the optional variable length Context Headers
 *
 *  0                   1                   2                   3
 *  0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |          Metadata Class       |      Type     |U|    Length   |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |                      Variable Metadata                        |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *
 * Metadata Class (MD Class): Defines the scope of the 'Type' field to
 * provide a hierarchical namespace.  The IANA Considerations
 * Section 11.2.4 defines how the MD Class values can be allocated to
 * standards bodies, venकरोrs, and others.
 *
 * Type: Indicates the explicit type of metadata being carried.  The
 * definition of the Type is the responsibility of the MD Class owner.
 *
 * Unasचिन्हित bit: One unasचिन्हित bit is available क्रम future use. This
 * bit MUST NOT be set, and MUST be ignored on receipt.
 *
 * Length: Indicates the length of the variable metadata, in bytes.  In
 * हाल the metadata length is not an पूर्णांकeger number of 4-byte words,
 * the sender MUST add pad bytes immediately following the last metadata
 * byte to extend the metadata to an पूर्णांकeger number of 4-byte words.
 * The receiver MUST round up the length field to the nearest 4-byte
 * word boundary, to locate and process the next field in the packet.
 * The receiver MUST access only those bytes in the metadata indicated
 * by the length field (i.e., actual number of bytes) and MUST ignore
 * the reमुख्यing bytes up to the nearest 4-byte word boundary.  The
 * Length may be 0 or greater.
 *
 * A value of 0 denotes a Context Header without a Variable Metadata
 * field.
 *
 * [0] https://datatracker.ietf.org/करोc/draft-ietf-sfc-nsh/
 */

/**
 * काष्ठा nsh_md1_ctx - Keeps track of NSH context data
 * @nshc<1-4>: NSH Contexts.
 */
काष्ठा nsh_md1_ctx अणु
	__be32 context[4];
पूर्ण;

काष्ठा nsh_md2_tlv अणु
	__be16 md_class;
	u8 type;
	u8 length;
	u8 md_value[];
पूर्ण;

काष्ठा nshhdr अणु
	__be16 ver_flags_ttl_len;
	u8 mdtype;
	u8 np;
	__be32 path_hdr;
	जोड़ अणु
	    काष्ठा nsh_md1_ctx md1;
	    काष्ठा nsh_md2_tlv md2;
	पूर्ण;
पूर्ण;

/* Masking NSH header fields. */
#घोषणा NSH_VER_MASK       0xc000
#घोषणा NSH_VER_SHIFT      14
#घोषणा NSH_FLAGS_MASK     0x3000
#घोषणा NSH_FLAGS_SHIFT    12
#घोषणा NSH_TTL_MASK       0x0fc0
#घोषणा NSH_TTL_SHIFT      6
#घोषणा NSH_LEN_MASK       0x003f
#घोषणा NSH_LEN_SHIFT      0

#घोषणा NSH_MDTYPE_MASK    0x0f
#घोषणा NSH_MDTYPE_SHIFT   0

#घोषणा NSH_SPI_MASK       0xffffff00
#घोषणा NSH_SPI_SHIFT      8
#घोषणा NSH_SI_MASK        0x000000ff
#घोषणा NSH_SI_SHIFT       0

/* MD Type Registry. */
#घोषणा NSH_M_TYPE1     0x01
#घोषणा NSH_M_TYPE2     0x02
#घोषणा NSH_M_EXP1      0xFE
#घोषणा NSH_M_EXP2      0xFF

/* NSH Base Header Length */
#घोषणा NSH_BASE_HDR_LEN  8

/* NSH MD Type 1 header Length. */
#घोषणा NSH_M_TYPE1_LEN   24

/* NSH header maximum Length. */
#घोषणा NSH_HDR_MAX_LEN 256

/* NSH context headers maximum Length. */
#घोषणा NSH_CTX_HDRS_MAX_LEN 248

अटल अंतरभूत काष्ठा nshhdr *nsh_hdr(काष्ठा sk_buff *skb)
अणु
	वापस (काष्ठा nshhdr *)skb_network_header(skb);
पूर्ण

अटल अंतरभूत u16 nsh_hdr_len(स्थिर काष्ठा nshhdr *nsh)
अणु
	वापस ((ntohs(nsh->ver_flags_ttl_len) & NSH_LEN_MASK)
		>> NSH_LEN_SHIFT) << 2;
पूर्ण

अटल अंतरभूत u8 nsh_get_ver(स्थिर काष्ठा nshhdr *nsh)
अणु
	वापस (ntohs(nsh->ver_flags_ttl_len) & NSH_VER_MASK)
		>> NSH_VER_SHIFT;
पूर्ण

अटल अंतरभूत u8 nsh_get_flags(स्थिर काष्ठा nshhdr *nsh)
अणु
	वापस (ntohs(nsh->ver_flags_ttl_len) & NSH_FLAGS_MASK)
		>> NSH_FLAGS_SHIFT;
पूर्ण

अटल अंतरभूत u8 nsh_get_ttl(स्थिर काष्ठा nshhdr *nsh)
अणु
	वापस (ntohs(nsh->ver_flags_ttl_len) & NSH_TTL_MASK)
		>> NSH_TTL_SHIFT;
पूर्ण

अटल अंतरभूत व्योम __nsh_set_xflag(काष्ठा nshhdr *nsh, u16 xflag, u16 xmask)
अणु
	nsh->ver_flags_ttl_len
		= (nsh->ver_flags_ttl_len & ~htons(xmask)) | htons(xflag);
पूर्ण

अटल अंतरभूत व्योम nsh_set_flags_and_ttl(काष्ठा nshhdr *nsh, u8 flags, u8 ttl)
अणु
	__nsh_set_xflag(nsh, ((flags << NSH_FLAGS_SHIFT) & NSH_FLAGS_MASK) |
			     ((ttl << NSH_TTL_SHIFT) & NSH_TTL_MASK),
			NSH_FLAGS_MASK | NSH_TTL_MASK);
पूर्ण

अटल अंतरभूत व्योम nsh_set_flags_ttl_len(काष्ठा nshhdr *nsh, u8 flags,
					 u8 ttl, u8 len)
अणु
	len = len >> 2;
	__nsh_set_xflag(nsh, ((flags << NSH_FLAGS_SHIFT) & NSH_FLAGS_MASK) |
			     ((ttl << NSH_TTL_SHIFT) & NSH_TTL_MASK) |
			     ((len << NSH_LEN_SHIFT) & NSH_LEN_MASK),
			NSH_FLAGS_MASK | NSH_TTL_MASK | NSH_LEN_MASK);
पूर्ण

पूर्णांक nsh_push(काष्ठा sk_buff *skb, स्थिर काष्ठा nshhdr *pushed_nh);
पूर्णांक nsh_pop(काष्ठा sk_buff *skb);

#पूर्ण_अगर /* __NET_NSH_H */
