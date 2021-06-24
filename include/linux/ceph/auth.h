<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _FS_CEPH_AUTH_H
#घोषणा _FS_CEPH_AUTH_H

#समावेश <linux/ceph/types.h>
#समावेश <linux/ceph/buffer.h>

/*
 * Abstract पूर्णांकerface क्रम communicating with the authenticate module.
 * There is some handshake that takes place between us and the monitor
 * to acquire the necessary keys.  These are used to generate an
 * 'authorizer' that we use when connecting to a service (mds, osd).
 */

काष्ठा ceph_auth_client;
काष्ठा ceph_msg;

काष्ठा ceph_authorizer अणु
	व्योम (*destroy)(काष्ठा ceph_authorizer *);
पूर्ण;

काष्ठा ceph_auth_handshake अणु
	काष्ठा ceph_authorizer *authorizer;
	व्योम *authorizer_buf;
	माप_प्रकार authorizer_buf_len;
	व्योम *authorizer_reply_buf;
	माप_प्रकार authorizer_reply_buf_len;
	पूर्णांक (*sign_message)(काष्ठा ceph_auth_handshake *auth,
			    काष्ठा ceph_msg *msg);
	पूर्णांक (*check_message_signature)(काष्ठा ceph_auth_handshake *auth,
				       काष्ठा ceph_msg *msg);
पूर्ण;

काष्ठा ceph_auth_client_ops अणु
	/*
	 * true अगर we are authenticated and can connect to
	 * services.
	 */
	पूर्णांक (*is_authenticated)(काष्ठा ceph_auth_client *ac);

	/*
	 * true अगर we should (re)authenticate, e.g., when our tickets
	 * are getting old and crusty.
	 */
	पूर्णांक (*should_authenticate)(काष्ठा ceph_auth_client *ac);

	/*
	 * build requests and process replies during monitor
	 * handshake.  अगर handle_reply वापसs -EAGAIN, we build
	 * another request.
	 */
	पूर्णांक (*build_request)(काष्ठा ceph_auth_client *ac, व्योम *buf, व्योम *end);
	पूर्णांक (*handle_reply)(काष्ठा ceph_auth_client *ac, पूर्णांक result,
			    व्योम *buf, व्योम *end, u8 *session_key,
			    पूर्णांक *session_key_len, u8 *con_secret,
			    पूर्णांक *con_secret_len);

	/*
	 * Create authorizer क्रम connecting to a service, and verअगरy
	 * the response to authenticate the service.
	 */
	पूर्णांक (*create_authorizer)(काष्ठा ceph_auth_client *ac, पूर्णांक peer_type,
				 काष्ठा ceph_auth_handshake *auth);
	/* ensure that an existing authorizer is up to date */
	पूर्णांक (*update_authorizer)(काष्ठा ceph_auth_client *ac, पूर्णांक peer_type,
				 काष्ठा ceph_auth_handshake *auth);
	पूर्णांक (*add_authorizer_challenge)(काष्ठा ceph_auth_client *ac,
					काष्ठा ceph_authorizer *a,
					व्योम *challenge_buf,
					पूर्णांक challenge_buf_len);
	पूर्णांक (*verअगरy_authorizer_reply)(काष्ठा ceph_auth_client *ac,
				       काष्ठा ceph_authorizer *a,
				       व्योम *reply, पूर्णांक reply_len,
				       u8 *session_key, पूर्णांक *session_key_len,
				       u8 *con_secret, पूर्णांक *con_secret_len);
	व्योम (*invalidate_authorizer)(काष्ठा ceph_auth_client *ac,
				      पूर्णांक peer_type);

	/* reset when we (re)connect to a monitor */
	व्योम (*reset)(काष्ठा ceph_auth_client *ac);

	व्योम (*destroy)(काष्ठा ceph_auth_client *ac);

	पूर्णांक (*sign_message)(काष्ठा ceph_auth_handshake *auth,
			    काष्ठा ceph_msg *msg);
	पूर्णांक (*check_message_signature)(काष्ठा ceph_auth_handshake *auth,
				       काष्ठा ceph_msg *msg);
पूर्ण;

काष्ठा ceph_auth_client अणु
	u32 protocol;           /* CEPH_AUTH_* */
	व्योम *निजी;          /* क्रम use by protocol implementation */
	स्थिर काष्ठा ceph_auth_client_ops *ops;  /* null अगरf protocol==0 */

	bool negotiating;       /* true अगर negotiating protocol */
	स्थिर अक्षर *name;       /* entity name */
	u64 global_id;          /* our unique id in प्रणाली */
	स्थिर काष्ठा ceph_crypto_key *key;     /* our secret key */
	अचिन्हित want_keys;     /* which services we want */

	पूर्णांक preferred_mode;	/* CEPH_CON_MODE_* */
	पूर्णांक fallback_mode;	/* ditto */

	काष्ठा mutex mutex;
पूर्ण;

काष्ठा ceph_auth_client *ceph_auth_init(स्थिर अक्षर *name,
					स्थिर काष्ठा ceph_crypto_key *key,
					स्थिर पूर्णांक *con_modes);
बाह्य व्योम ceph_auth_destroy(काष्ठा ceph_auth_client *ac);

बाह्य व्योम ceph_auth_reset(काष्ठा ceph_auth_client *ac);

बाह्य पूर्णांक ceph_auth_build_hello(काष्ठा ceph_auth_client *ac,
				 व्योम *buf, माप_प्रकार len);
बाह्य पूर्णांक ceph_handle_auth_reply(काष्ठा ceph_auth_client *ac,
				  व्योम *buf, माप_प्रकार len,
				  व्योम *reply_buf, माप_प्रकार reply_len);
पूर्णांक ceph_auth_entity_name_encode(स्थिर अक्षर *name, व्योम **p, व्योम *end);

बाह्य पूर्णांक ceph_build_auth(काष्ठा ceph_auth_client *ac,
		    व्योम *msg_buf, माप_प्रकार msg_len);
बाह्य पूर्णांक ceph_auth_is_authenticated(काष्ठा ceph_auth_client *ac);

पूर्णांक __ceph_auth_get_authorizer(काष्ठा ceph_auth_client *ac,
			       काष्ठा ceph_auth_handshake *auth,
			       पूर्णांक peer_type, bool क्रमce_new,
			       पूर्णांक *proto, पूर्णांक *pref_mode, पूर्णांक *fallb_mode);
व्योम ceph_auth_destroy_authorizer(काष्ठा ceph_authorizer *a);
पूर्णांक ceph_auth_add_authorizer_challenge(काष्ठा ceph_auth_client *ac,
				       काष्ठा ceph_authorizer *a,
				       व्योम *challenge_buf,
				       पूर्णांक challenge_buf_len);
पूर्णांक ceph_auth_verअगरy_authorizer_reply(काष्ठा ceph_auth_client *ac,
				      काष्ठा ceph_authorizer *a,
				      व्योम *reply, पूर्णांक reply_len,
				      u8 *session_key, पूर्णांक *session_key_len,
				      u8 *con_secret, पूर्णांक *con_secret_len);
बाह्य व्योम ceph_auth_invalidate_authorizer(काष्ठा ceph_auth_client *ac,
					    पूर्णांक peer_type);

अटल अंतरभूत पूर्णांक ceph_auth_sign_message(काष्ठा ceph_auth_handshake *auth,
					 काष्ठा ceph_msg *msg)
अणु
	अगर (auth->sign_message)
		वापस auth->sign_message(auth, msg);
	वापस 0;
पूर्ण

अटल अंतरभूत
पूर्णांक ceph_auth_check_message_signature(काष्ठा ceph_auth_handshake *auth,
				      काष्ठा ceph_msg *msg)
अणु
	अगर (auth->check_message_signature)
		वापस auth->check_message_signature(auth, msg);
	वापस 0;
पूर्ण

पूर्णांक ceph_auth_get_request(काष्ठा ceph_auth_client *ac, व्योम *buf, पूर्णांक buf_len);
पूर्णांक ceph_auth_handle_reply_more(काष्ठा ceph_auth_client *ac, व्योम *reply,
				पूर्णांक reply_len, व्योम *buf, पूर्णांक buf_len);
पूर्णांक ceph_auth_handle_reply_करोne(काष्ठा ceph_auth_client *ac,
				u64 global_id, व्योम *reply, पूर्णांक reply_len,
				u8 *session_key, पूर्णांक *session_key_len,
				u8 *con_secret, पूर्णांक *con_secret_len);
bool ceph_auth_handle_bad_method(काष्ठा ceph_auth_client *ac,
				 पूर्णांक used_proto, पूर्णांक result,
				 स्थिर पूर्णांक *allowed_protos, पूर्णांक proto_cnt,
				 स्थिर पूर्णांक *allowed_modes, पूर्णांक mode_cnt);

पूर्णांक ceph_auth_get_authorizer(काष्ठा ceph_auth_client *ac,
			     काष्ठा ceph_auth_handshake *auth,
			     पूर्णांक peer_type, व्योम *buf, पूर्णांक *buf_len);
पूर्णांक ceph_auth_handle_svc_reply_more(काष्ठा ceph_auth_client *ac,
				    काष्ठा ceph_auth_handshake *auth,
				    व्योम *reply, पूर्णांक reply_len,
				    व्योम *buf, पूर्णांक *buf_len);
पूर्णांक ceph_auth_handle_svc_reply_करोne(काष्ठा ceph_auth_client *ac,
				    काष्ठा ceph_auth_handshake *auth,
				    व्योम *reply, पूर्णांक reply_len,
				    u8 *session_key, पूर्णांक *session_key_len,
				    u8 *con_secret, पूर्णांक *con_secret_len);
bool ceph_auth_handle_bad_authorizer(काष्ठा ceph_auth_client *ac,
				     पूर्णांक peer_type, पूर्णांक used_proto, पूर्णांक result,
				     स्थिर पूर्णांक *allowed_protos, पूर्णांक proto_cnt,
				     स्थिर पूर्णांक *allowed_modes, पूर्णांक mode_cnt);

#पूर्ण_अगर
