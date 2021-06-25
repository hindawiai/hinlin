<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __NET_GUE_H
#घोषणा __NET_GUE_H

/* Definitions क्रम the GUE header, standard and निजी flags, lengths
 * of optional fields are below.
 *
 * Diagram of GUE header:
 *
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |Ver|C|  Hlen   | Proto/ctype   |        Standard flags       |P|
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |                                                               |
 * ~                      Fields (optional)                        ~
 * |                                                               |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |            Private flags (optional, P bit is set)             |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |                                                               |
 * ~                   Private fields (optional)                   ~
 * |                                                               |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *
 * C bit indicates control message when set, data message when unset.
 * For a control message, proto/ctype is पूर्णांकerpreted as a type of
 * control message. For data messages, proto/ctype is the IP protocol
 * of the next header.
 *
 * P bit indicates निजी flags field is present. The निजी flags
 * may refer to options placed after this field.
 */

काष्ठा guehdr अणु
	जोड़ अणु
		काष्ठा अणु
#अगर defined(__LITTLE_ENDIAN_BITFIELD)
			__u8	hlen:5,
				control:1,
				version:2;
#या_अगर defined (__BIG_ENDIAN_BITFIELD)
			__u8	version:2,
				control:1,
				hlen:5;
#अन्यथा
#त्रुटि  "Please fix <asm/byteorder.h>"
#पूर्ण_अगर
			__u8	proto_ctype;
			__be16	flags;
		पूर्ण;
		__be32	word;
	पूर्ण;
पूर्ण;

/* Standard flags in GUE header */

#घोषणा GUE_FLAG_PRIV	htons(1<<0)	/* Private flags are in options */
#घोषणा GUE_LEN_PRIV	4

#घोषणा GUE_FLAGS_ALL	(GUE_FLAG_PRIV)

/* Private flags in the निजी option extension */

#घोषणा GUE_PFLAG_REMCSUM	htonl(1U << 31)
#घोषणा GUE_PLEN_REMCSUM	4

#घोषणा GUE_PFLAGS_ALL	(GUE_PFLAG_REMCSUM)

/* Functions to compute options length corresponding to flags.
 * If we ever have a lot of flags this can be potentially be
 * converted to a more optimized algorithm (table lookup
 * क्रम instance).
 */
अटल अंतरभूत माप_प्रकार guehdr_flags_len(__be16 flags)
अणु
	वापस ((flags & GUE_FLAG_PRIV) ? GUE_LEN_PRIV : 0);
पूर्ण

अटल अंतरभूत माप_प्रकार guehdr_priv_flags_len(__be32 flags)
अणु
	वापस 0;
पूर्ण

/* Validate standard and निजी flags. Returns non-zero (meaning invalid)
 * अगर there is an unknown standard or निजी flags, or the options length क्रम
 * the flags exceeds the options length specअगरic in hlen of the GUE header.
 */
अटल अंतरभूत पूर्णांक validate_gue_flags(काष्ठा guehdr *guehdr, माप_प्रकार optlen)
अणु
	__be16 flags = guehdr->flags;
	माप_प्रकार len;

	अगर (flags & ~GUE_FLAGS_ALL)
		वापस 1;

	len = guehdr_flags_len(flags);
	अगर (len > optlen)
		वापस 1;

	अगर (flags & GUE_FLAG_PRIV) अणु
		/* Private flags are last four bytes accounted in
		 * guehdr_flags_len
		 */
		__be32 pflags = *(__be32 *)((व्योम *)&guehdr[1] +
					    len - GUE_LEN_PRIV);

		अगर (pflags & ~GUE_PFLAGS_ALL)
			वापस 1;

		len += guehdr_priv_flags_len(pflags);
		अगर (len > optlen)
			वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

#पूर्ण_अगर
