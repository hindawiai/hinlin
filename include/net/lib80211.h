<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * lib80211.h -- common bits क्रम IEEE802.11 wireless drivers
 *
 * Copyright (c) 2008, John W. Linville <linville@tuxdriver.com>
 *
 * Some bits copied from old ieee80211 component, w/ original copyright
 * notices below:
 *
 * Original code based on Host AP (software wireless LAN access poपूर्णांक) driver
 * क्रम Intersil Prism2/2.5/3.
 *
 * Copyright (c) 2001-2002, SSH Communications Security Corp and Jouni Malinen
 * <j@w1.fi>
 * Copyright (c) 2002-2003, Jouni Malinen <j@w1.fi>
 *
 * Adaption to a generic IEEE 802.11 stack by James Ketrenos
 * <jketreno@linux.पूर्णांकel.com>
 *
 * Copyright (c) 2004, Intel Corporation
 *
 */

#अगर_अघोषित LIB80211_H
#घोषणा LIB80211_H

#समावेश <linux/types.h>
#समावेश <linux/list.h>
#समावेश <linux/atomic.h>
#समावेश <linux/अगर.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/ieee80211.h>
#समावेश <linux/समयr.h>
#समावेश <linux/seq_file.h>

#घोषणा NUM_WEP_KEYS	4

क्रमागत अणु
	IEEE80211_CRYPTO_TKIP_COUNTERMEASURES = (1 << 0),
पूर्ण;

काष्ठा module;

काष्ठा lib80211_crypto_ops अणु
	स्थिर अक्षर *name;
	काष्ठा list_head list;

	/* init new crypto context (e.g., allocate निजी data space,
	 * select IV, etc.); वापसs शून्य on failure or poपूर्णांकer to allocated
	 * निजी data on success */
	व्योम *(*init) (पूर्णांक keyidx);

	/* deinitialize crypto context and मुक्त allocated निजी data */
	व्योम (*deinit) (व्योम *priv);

	/* encrypt/decrypt वापस < 0 on error or >= 0 on success. The वापस
	 * value from decrypt_mpdu is passed as the keyidx value क्रम
	 * decrypt_msdu. skb must have enough head and tail room क्रम the
	 * encryption; अगर not, error will be वापसed; these functions are
	 * called क्रम all MPDUs (i.e., fragments).
	 */
	पूर्णांक (*encrypt_mpdu) (काष्ठा sk_buff * skb, पूर्णांक hdr_len, व्योम *priv);
	पूर्णांक (*decrypt_mpdu) (काष्ठा sk_buff * skb, पूर्णांक hdr_len, व्योम *priv);

	/* These functions are called क्रम full MSDUs, i.e. full frames.
	 * These can be शून्य अगर full MSDU operations are not needed. */
	पूर्णांक (*encrypt_msdu) (काष्ठा sk_buff * skb, पूर्णांक hdr_len, व्योम *priv);
	पूर्णांक (*decrypt_msdu) (काष्ठा sk_buff * skb, पूर्णांक keyidx, पूर्णांक hdr_len,
			     व्योम *priv);

	पूर्णांक (*set_key) (व्योम *key, पूर्णांक len, u8 * seq, व्योम *priv);
	पूर्णांक (*get_key) (व्योम *key, पूर्णांक len, u8 * seq, व्योम *priv);

	/* procfs handler क्रम prपूर्णांकing out key inक्रमmation and possible
	 * statistics */
	व्योम (*prपूर्णांक_stats) (काष्ठा seq_file *m, व्योम *priv);

	/* Crypto specअगरic flag get/set क्रम configuration settings */
	अचिन्हित दीर्घ (*get_flags) (व्योम *priv);
	अचिन्हित दीर्घ (*set_flags) (अचिन्हित दीर्घ flags, व्योम *priv);

	/* maximum number of bytes added by encryption; encrypt buf is
	 * allocated with extra_prefix_len bytes, copy of in_buf, and
	 * extra_postfix_len; encrypt need not use all this space, but
	 * the result must start at the beginning of the buffer and correct
	 * length must be वापसed */
	पूर्णांक extra_mpdu_prefix_len, extra_mpdu_postfix_len;
	पूर्णांक extra_msdu_prefix_len, extra_msdu_postfix_len;

	काष्ठा module *owner;
पूर्ण;

काष्ठा lib80211_crypt_data अणु
	काष्ठा list_head list;	/* delayed deletion list */
	काष्ठा lib80211_crypto_ops *ops;
	व्योम *priv;
	atomic_t refcnt;
पूर्ण;

काष्ठा lib80211_crypt_info अणु
	अक्षर *name;
	/* Most clients will alपढ़ोy have a lock,
	   so just poपूर्णांक to that. */
	spinlock_t *lock;

	काष्ठा lib80211_crypt_data *crypt[NUM_WEP_KEYS];
	पूर्णांक tx_keyidx;		/* शेष TX key index (crypt[tx_keyidx]) */
	काष्ठा list_head crypt_deinit_list;
	काष्ठा समयr_list crypt_deinit_समयr;
	पूर्णांक crypt_quiesced;
पूर्ण;

पूर्णांक lib80211_crypt_info_init(काष्ठा lib80211_crypt_info *info, अक्षर *name,
                                spinlock_t *lock);
व्योम lib80211_crypt_info_मुक्त(काष्ठा lib80211_crypt_info *info);
पूर्णांक lib80211_रेजिस्टर_crypto_ops(काष्ठा lib80211_crypto_ops *ops);
पूर्णांक lib80211_unरेजिस्टर_crypto_ops(काष्ठा lib80211_crypto_ops *ops);
काष्ठा lib80211_crypto_ops *lib80211_get_crypto_ops(स्थिर अक्षर *name);
व्योम lib80211_crypt_delayed_deinit(काष्ठा lib80211_crypt_info *info,
				    काष्ठा lib80211_crypt_data **crypt);

#पूर्ण_अगर /* LIB80211_H */
