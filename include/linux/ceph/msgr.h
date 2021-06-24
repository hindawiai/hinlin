<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित CEPH_MSGR_H
#घोषणा CEPH_MSGR_H

/*
 * Data types क्रम message passing layer used by Ceph.
 */

#घोषणा CEPH_MON_PORT    6789  /* शेष monitor port */

/*
 * tcp connection banner.  include a protocol version. and adjust
 * whenever the wire protocol changes.  try to keep this string length
 * स्थिरant.
 */
#घोषणा CEPH_BANNER "ceph v027"
#घोषणा CEPH_BANNER_LEN 9
#घोषणा CEPH_BANNER_MAX_LEN 30


/*
 * messenger V2 connection banner prefix.
 * The full banner string should have the क्रमm: "ceph v2\n<le16>"
 * the 2 bytes are the length of the reमुख्यing banner.
 */
#घोषणा CEPH_BANNER_V2 "ceph v2\n"
#घोषणा CEPH_BANNER_V2_LEN 8
#घोषणा CEPH_BANNER_V2_PREFIX_LEN (CEPH_BANNER_V2_LEN + माप(__le16))

/*
 * messenger V2 features
 */
#घोषणा CEPH_MSGR2_INCARNATION_1 (0ull)

#घोषणा DEFINE_MSGR2_FEATURE(bit, incarnation, name)               \
	अटल स्थिर uपूर्णांक64_t __maybe_unused CEPH_MSGR2_FEATURE_##name = (1ULL << bit); \
	अटल स्थिर uपूर्णांक64_t __maybe_unused CEPH_MSGR2_FEATUREMASK_##name =            \
			(1ULL << bit | CEPH_MSGR2_INCARNATION_##incarnation);

#घोषणा HAVE_MSGR2_FEATURE(x, name) \
	(((x) & (CEPH_MSGR2_FEATUREMASK_##name)) == (CEPH_MSGR2_FEATUREMASK_##name))

DEFINE_MSGR2_FEATURE( 0, 1, REVISION_1)   // msgr2.1

#घोषणा CEPH_MSGR2_SUPPORTED_FEATURES (CEPH_MSGR2_FEATURE_REVISION_1)

#घोषणा CEPH_MSGR2_REQUIRED_FEATURES  (CEPH_MSGR2_FEATURE_REVISION_1)


/*
 * Rollover-safe type and comparator क्रम 32-bit sequence numbers.
 * Comparator वापसs -1, 0, or 1.
 */
प्रकार __u32 ceph_seq_t;

अटल अंतरभूत __s32 ceph_seq_cmp(__u32 a, __u32 b)
अणु
       वापस (__s32)a - (__s32)b;
पूर्ण


/*
 * entity_name -- logical name क्रम a process participating in the
 * network, e.g. 'mds0' or 'osd3'.
 */
काष्ठा ceph_entity_name अणु
	__u8 type;      /* CEPH_ENTITY_TYPE_* */
	__le64 num;
पूर्ण __attribute__ ((packed));

#घोषणा CEPH_ENTITY_TYPE_MON    0x01
#घोषणा CEPH_ENTITY_TYPE_MDS    0x02
#घोषणा CEPH_ENTITY_TYPE_OSD    0x04
#घोषणा CEPH_ENTITY_TYPE_CLIENT 0x08
#घोषणा CEPH_ENTITY_TYPE_AUTH   0x20

#घोषणा CEPH_ENTITY_TYPE_ANY    0xFF

बाह्य स्थिर अक्षर *ceph_entity_type_name(पूर्णांक type);

/*
 * entity_addr -- network address
 */
काष्ठा ceph_entity_addr अणु
	__le32 type;  /* CEPH_ENTITY_ADDR_TYPE_* */
	__le32 nonce;  /* unique id क्रम process (e.g. pid) */
	काष्ठा sockaddr_storage in_addr;
पूर्ण __attribute__ ((packed));

अटल अंतरभूत bool ceph_addr_equal_no_type(स्थिर काष्ठा ceph_entity_addr *lhs,
					   स्थिर काष्ठा ceph_entity_addr *rhs)
अणु
	वापस !स_भेद(&lhs->in_addr, &rhs->in_addr, माप(lhs->in_addr)) &&
	       lhs->nonce == rhs->nonce;
पूर्ण

काष्ठा ceph_entity_inst अणु
	काष्ठा ceph_entity_name name;
	काष्ठा ceph_entity_addr addr;
पूर्ण __attribute__ ((packed));


/* used by message exchange protocol */
#घोषणा CEPH_MSGR_TAG_READY         1  /* server->client: पढ़ोy क्रम messages */
#घोषणा CEPH_MSGR_TAG_RESETSESSION  2  /* server->client: reset, try again */
#घोषणा CEPH_MSGR_TAG_WAIT          3  /* server->client: रुको क्रम racing
					  incoming connection */
#घोषणा CEPH_MSGR_TAG_RETRY_SESSION 4  /* server->client + cseq: try again
					  with higher cseq */
#घोषणा CEPH_MSGR_TAG_RETRY_GLOBAL  5  /* server->client + gseq: try again
					  with higher gseq */
#घोषणा CEPH_MSGR_TAG_CLOSE         6  /* closing pipe */
#घोषणा CEPH_MSGR_TAG_MSG           7  /* message */
#घोषणा CEPH_MSGR_TAG_ACK           8  /* message ack */
#घोषणा CEPH_MSGR_TAG_KEEPALIVE     9  /* just a keepalive byte! */
#घोषणा CEPH_MSGR_TAG_BADPROTOVER   10 /* bad protocol version */
#घोषणा CEPH_MSGR_TAG_BADAUTHORIZER 11 /* bad authorizer */
#घोषणा CEPH_MSGR_TAG_FEATURES      12 /* insufficient features */
#घोषणा CEPH_MSGR_TAG_SEQ           13 /* 64-bit पूर्णांक follows with seen seq number */
#घोषणा CEPH_MSGR_TAG_KEEPALIVE2    14 /* keepalive2 byte + ceph_बारpec */
#घोषणा CEPH_MSGR_TAG_KEEPALIVE2_ACK 15 /* keepalive2 reply */
#घोषणा CEPH_MSGR_TAG_CHALLENGE_AUTHORIZER 16  /* cephx v2 करोing server challenge */

/*
 * connection negotiation
 */
काष्ठा ceph_msg_connect अणु
	__le64 features;     /* supported feature bits */
	__le32 host_type;    /* CEPH_ENTITY_TYPE_* */
	__le32 global_seq;   /* count connections initiated by this host */
	__le32 connect_seq;  /* count connections initiated in this session */
	__le32 protocol_version;
	__le32 authorizer_protocol;
	__le32 authorizer_len;
	__u8  flags;         /* CEPH_MSG_CONNECT_* */
पूर्ण __attribute__ ((packed));

काष्ठा ceph_msg_connect_reply अणु
	__u8 tag;
	__le64 features;     /* feature bits क्रम this session */
	__le32 global_seq;
	__le32 connect_seq;
	__le32 protocol_version;
	__le32 authorizer_len;
	__u8 flags;
पूर्ण __attribute__ ((packed));

#घोषणा CEPH_MSG_CONNECT_LOSSY  1  /* messages i send may be safely dropped */


/*
 * message header
 */
काष्ठा ceph_msg_header_old अणु
	__le64 seq;       /* message seq# क्रम this session */
	__le64 tid;       /* transaction id */
	__le16 type;      /* message type */
	__le16 priority;  /* priority.  higher value == higher priority */
	__le16 version;   /* version of message encoding */

	__le32 front_len; /* bytes in मुख्य payload */
	__le32 middle_len;/* bytes in middle payload */
	__le32 data_len;  /* bytes of data payload */
	__le16 data_off;  /* sender: include full offset;
			     receiver: mask against ~PAGE_MASK */

	काष्ठा ceph_entity_inst src, orig_src;
	__le32 reserved;
	__le32 crc;       /* header crc32c */
पूर्ण __attribute__ ((packed));

काष्ठा ceph_msg_header अणु
	__le64 seq;       /* message seq# क्रम this session */
	__le64 tid;       /* transaction id */
	__le16 type;      /* message type */
	__le16 priority;  /* priority.  higher value == higher priority */
	__le16 version;   /* version of message encoding */

	__le32 front_len; /* bytes in मुख्य payload */
	__le32 middle_len;/* bytes in middle payload */
	__le32 data_len;  /* bytes of data payload */
	__le16 data_off;  /* sender: include full offset;
			     receiver: mask against ~PAGE_MASK */

	काष्ठा ceph_entity_name src;
	__le16 compat_version;
	__le16 reserved;
	__le32 crc;       /* header crc32c */
पूर्ण __attribute__ ((packed));

काष्ठा ceph_msg_header2 अणु
	__le64 seq;       /* message seq# क्रम this session */
	__le64 tid;       /* transaction id */
	__le16 type;      /* message type */
	__le16 priority;  /* priority.  higher value == higher priority */
	__le16 version;   /* version of message encoding */

	__le32 data_pre_padding_len;
	__le16 data_off;  /* sender: include full offset;
			     receiver: mask against ~PAGE_MASK */

	__le64 ack_seq;
	__u8 flags;
	/* oldest code we think can decode this.  unknown अगर zero. */
	__le16 compat_version;
	__le16 reserved;
पूर्ण __attribute__ ((packed));

#घोषणा CEPH_MSG_PRIO_LOW     64
#घोषणा CEPH_MSG_PRIO_DEFAULT 127
#घोषणा CEPH_MSG_PRIO_HIGH    196
#घोषणा CEPH_MSG_PRIO_HIGHEST 255

/*
 * follows data payload
 */
काष्ठा ceph_msg_footer_old अणु
	__le32 front_crc, middle_crc, data_crc;
	__u8 flags;
पूर्ण __attribute__ ((packed));

काष्ठा ceph_msg_footer अणु
	__le32 front_crc, middle_crc, data_crc;
	// sig holds the 64 bits of the digital signature क्रम the message PLR
	__le64  sig;
	__u8 flags;
पूर्ण __attribute__ ((packed));

#घोषणा CEPH_MSG_FOOTER_COMPLETE  (1<<0)   /* msg wasn't पातed */
#घोषणा CEPH_MSG_FOOTER_NOCRC     (1<<1)   /* no data crc */
#घोषणा CEPH_MSG_FOOTER_SIGNED	  (1<<2)   /* msg was चिन्हित */


#पूर्ण_अगर
