<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __FS_CEPH_AUTH_X_PROTOCOL
#घोषणा __FS_CEPH_AUTH_X_PROTOCOL

#घोषणा CEPHX_GET_AUTH_SESSION_KEY      0x0100
#घोषणा CEPHX_GET_PRINCIPAL_SESSION_KEY 0x0200
#घोषणा CEPHX_GET_ROTATING_KEY          0x0400

/* common bits */
काष्ठा ceph_x_ticket_blob अणु
	__u8 काष्ठा_v;
	__le64 secret_id;
	__le32 blob_len;
	अक्षर blob[];
पूर्ण __attribute__ ((packed));


/* common request/reply headers */
काष्ठा ceph_x_request_header अणु
	__le16 op;
पूर्ण __attribute__ ((packed));

काष्ठा ceph_x_reply_header अणु
	__le16 op;
	__le32 result;
पूर्ण __attribute__ ((packed));


/* authenticate handshake */

/* initial hello (no reply header) */
काष्ठा ceph_x_server_challenge अणु
	__u8 काष्ठा_v;
	__le64 server_challenge;
पूर्ण __attribute__ ((packed));

काष्ठा ceph_x_authenticate अणु
	__u8 काष्ठा_v;
	__le64 client_challenge;
	__le64 key;
	/* old_ticket blob */
	/* nautilus+: other_keys */
पूर्ण __attribute__ ((packed));

काष्ठा ceph_x_service_ticket_request अणु
	__u8 काष्ठा_v;
	__le32 keys;
पूर्ण __attribute__ ((packed));

काष्ठा ceph_x_challenge_blob अणु
	__le64 server_challenge;
	__le64 client_challenge;
पूर्ण __attribute__ ((packed));



/* authorize handshake */

/*
 * The authorizer consists of two pieces:
 *  a - service id, ticket blob
 *  b - encrypted with session key
 */
काष्ठा ceph_x_authorize_a अणु
	__u8 काष्ठा_v;
	__le64 global_id;
	__le32 service_id;
	काष्ठा ceph_x_ticket_blob ticket_blob;
पूर्ण __attribute__ ((packed));

काष्ठा ceph_x_authorize_b अणु
	__u8 काष्ठा_v;
	__le64 nonce;
	__u8 have_challenge;
	__le64 server_challenge_plus_one;
पूर्ण __attribute__ ((packed));

काष्ठा ceph_x_authorize_challenge अणु
	__u8 काष्ठा_v;
	__le64 server_challenge;
पूर्ण __attribute__ ((packed));

काष्ठा ceph_x_authorize_reply अणु
	__u8 काष्ठा_v;
	__le64 nonce_plus_one;
पूर्ण __attribute__ ((packed));


/*
 * encyption bundle
 */
#घोषणा CEPHX_ENC_MAGIC 0xff009cad8826aa55ull

काष्ठा ceph_x_encrypt_header अणु
	__u8 काष्ठा_v;
	__le64 magic;
पूर्ण __attribute__ ((packed));

#पूर्ण_अगर
