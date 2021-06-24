<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Original code based on Host AP (software wireless LAN access poपूर्णांक) driver
 * क्रम Intersil Prism2/2.5/3.
 *
 * Copyright (c) 2001-2002, SSH Communications Security Corp and Jouni Malinen
 * <jkmaline@cc.hut.fi>
 * Copyright (c) 2002-2003, Jouni Malinen <jkmaline@cc.hut.fi>
 *
 * Adaption to a generic IEEE 802.11 stack by James Ketrenos
 * <jketreno@linux.पूर्णांकel.com>
 *
 * Copyright (c) 2004, Intel Corporation
 */

/*
 * This file defines the पूर्णांकerface to the ieee80211 crypto module.
 */
#अगर_अघोषित IEEE80211_CRYPT_H
#घोषणा IEEE80211_CRYPT_H

#समावेश <linux/skbuff.h>

काष्ठा ieee80211_crypto_ops अणु
	स्थिर अक्षर *name;

	/* init new crypto context (e.g., allocate निजी data space,
	 * select IV, etc.); वापसs शून्य on failure or poपूर्णांकer to allocated
	 * निजी data on success
	 */
	व्योम * (*init)(पूर्णांक keyidx);

	/* deinitialize crypto context and मुक्त allocated निजी data */
	व्योम (*deinit)(व्योम *priv);

	/* encrypt/decrypt वापस < 0 on error or >= 0 on success. The वापस
	 * value from decrypt_mpdu is passed as the keyidx value क्रम
	 * decrypt_msdu. skb must have enough head and tail room क्रम the
	 * encryption; अगर not, error will be वापसed; these functions are
	 * called क्रम all MPDUs (i.e., fragments).
	 */
	पूर्णांक (*encrypt_mpdu)(काष्ठा sk_buff *skb, पूर्णांक hdr_len, व्योम *priv);
	पूर्णांक (*decrypt_mpdu)(काष्ठा sk_buff *skb, पूर्णांक hdr_len, व्योम *priv);

	/* These functions are called क्रम full MSDUs, i.e. full frames.
	 * These can be शून्य अगर full MSDU operations are not needed.
	 */
	पूर्णांक (*encrypt_msdu)(काष्ठा sk_buff *skb, पूर्णांक hdr_len, व्योम *priv);
	पूर्णांक (*decrypt_msdu)(काष्ठा sk_buff *skb, पूर्णांक keyidx, पूर्णांक hdr_len,
			    व्योम *priv);

	पूर्णांक (*set_key)(व्योम *key, पूर्णांक len, u8 *seq, व्योम *priv);
	पूर्णांक (*get_key)(व्योम *key, पूर्णांक len, u8 *seq, व्योम *priv);

	/* procfs handler क्रम prपूर्णांकing out key inक्रमmation and possible
	 * statistics
	 */
	अक्षर * (*prपूर्णांक_stats)(अक्षर *p, व्योम *priv);

	/* maximum number of bytes added by encryption; encrypt buf is
	 * allocated with extra_prefix_len bytes, copy of in_buf, and
	 * extra_postfix_len; encrypt need not use all this space, but
	 * the result must start at the beginning of the buffer and correct
	 * length must be वापसed
	 */
	पूर्णांक extra_prefix_len, extra_postfix_len;

	काष्ठा module *owner;
पूर्ण;

काष्ठा ieee80211_crypt_data अणु
	काष्ठा list_head list; /* delayed deletion list */
	काष्ठा ieee80211_crypto_ops *ops;
	व्योम *priv;
	atomic_t refcnt;
पूर्ण;

पूर्णांक ieee80211_रेजिस्टर_crypto_ops(काष्ठा ieee80211_crypto_ops *ops);
पूर्णांक ieee80211_unरेजिस्टर_crypto_ops(काष्ठा ieee80211_crypto_ops *ops);
काष्ठा ieee80211_crypto_ops *ieee80211_get_crypto_ops(स्थिर अक्षर *name);
व्योम ieee80211_crypt_deinit_entries(काष्ठा ieee80211_device *ieee, पूर्णांक क्रमce);
व्योम ieee80211_crypt_deinit_handler(काष्ठा समयr_list *t);
व्योम ieee80211_crypt_delayed_deinit(काष्ठा ieee80211_device *ieee,
				    काष्ठा ieee80211_crypt_data **crypt);

#पूर्ण_अगर
