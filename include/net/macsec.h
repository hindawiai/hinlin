<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * MACsec netdev header, used क्रम h/w accelerated implementations.
 *
 * Copyright (c) 2015 Sabrina Dubroca <sd@queasysnail.net>
 */
#अगर_अघोषित _NET_MACSEC_H_
#घोषणा _NET_MACSEC_H_

#समावेश <linux/u64_stats_sync.h>
#समावेश <uapi/linux/अगर_link.h>
#समावेश <uapi/linux/अगर_macsec.h>

#घोषणा MACSEC_DEFAULT_PN_LEN 4
#घोषणा MACSEC_XPN_PN_LEN 8

#घोषणा MACSEC_SALT_LEN 12
#घोषणा MACSEC_NUM_AN 4 /* 2 bits क्रम the association number */

प्रकार u64 __bitwise sci_t;
प्रकार u32 __bitwise ssci_t;

प्रकार जोड़ salt अणु
	काष्ठा अणु
		u32 ssci;
		u64 pn;
	पूर्ण __packed;
	u8 bytes[MACSEC_SALT_LEN];
पूर्ण __packed salt_t;

प्रकार जोड़ pn अणु
	काष्ठा अणु
#अगर defined(__LITTLE_ENDIAN_BITFIELD)
		u32 lower;
		u32 upper;
#या_अगर defined(__BIG_ENDIAN_BITFIELD)
		u32 upper;
		u32 lower;
#अन्यथा
#त्रुटि	"Please fix <asm/byteorder.h>"
#पूर्ण_अगर
	पूर्ण;
	u64 full64;
पूर्ण pn_t;

/**
 * काष्ठा macsec_key - SA key
 * @id: user-provided key identअगरier
 * @tfm: crypto काष्ठा, key storage
 * @salt: salt used to generate IV in XPN cipher suites
 */
काष्ठा macsec_key अणु
	u8 id[MACSEC_KEYID_LEN];
	काष्ठा crypto_aead *tfm;
	salt_t salt;
पूर्ण;

काष्ठा macsec_rx_sc_stats अणु
	__u64 InOctetsValidated;
	__u64 InOctetsDecrypted;
	__u64 InPktsUnchecked;
	__u64 InPktsDelayed;
	__u64 InPktsOK;
	__u64 InPktsInvalid;
	__u64 InPktsLate;
	__u64 InPktsNotValid;
	__u64 InPktsNotUsingSA;
	__u64 InPktsUnusedSA;
पूर्ण;

काष्ठा macsec_rx_sa_stats अणु
	__u32 InPktsOK;
	__u32 InPktsInvalid;
	__u32 InPktsNotValid;
	__u32 InPktsNotUsingSA;
	__u32 InPktsUnusedSA;
पूर्ण;

काष्ठा macsec_tx_sa_stats अणु
	__u32 OutPktsProtected;
	__u32 OutPktsEncrypted;
पूर्ण;

काष्ठा macsec_tx_sc_stats अणु
	__u64 OutPktsProtected;
	__u64 OutPktsEncrypted;
	__u64 OutOctetsProtected;
	__u64 OutOctetsEncrypted;
पूर्ण;

काष्ठा macsec_dev_stats अणु
	__u64 OutPktsUntagged;
	__u64 InPktsUntagged;
	__u64 OutPktsTooLong;
	__u64 InPktsNoTag;
	__u64 InPktsBadTag;
	__u64 InPktsUnknownSCI;
	__u64 InPktsNoSCI;
	__u64 InPktsOverrun;
पूर्ण;

/**
 * काष्ठा macsec_rx_sa - receive secure association
 * @active:
 * @next_pn: packet number expected क्रम the next packet
 * @lock: protects next_pn manipulations
 * @key: key काष्ठाure
 * @ssci: लघु secure channel identअगरier
 * @stats: per-SA stats
 */
काष्ठा macsec_rx_sa अणु
	काष्ठा macsec_key key;
	ssci_t ssci;
	spinlock_t lock;
	जोड़ अणु
		pn_t next_pn_halves;
		u64 next_pn;
	पूर्ण;
	refcount_t refcnt;
	bool active;
	काष्ठा macsec_rx_sa_stats __percpu *stats;
	काष्ठा macsec_rx_sc *sc;
	काष्ठा rcu_head rcu;
पूर्ण;

काष्ठा pcpu_rx_sc_stats अणु
	काष्ठा macsec_rx_sc_stats stats;
	काष्ठा u64_stats_sync syncp;
पूर्ण;

काष्ठा pcpu_tx_sc_stats अणु
	काष्ठा macsec_tx_sc_stats stats;
	काष्ठा u64_stats_sync syncp;
पूर्ण;

/**
 * काष्ठा macsec_rx_sc - receive secure channel
 * @sci: secure channel identअगरier क्रम this SC
 * @active: channel is active
 * @sa: array of secure associations
 * @stats: per-SC stats
 */
काष्ठा macsec_rx_sc अणु
	काष्ठा macsec_rx_sc __rcu *next;
	sci_t sci;
	bool active;
	काष्ठा macsec_rx_sa __rcu *sa[MACSEC_NUM_AN];
	काष्ठा pcpu_rx_sc_stats __percpu *stats;
	refcount_t refcnt;
	काष्ठा rcu_head rcu_head;
पूर्ण;

/**
 * काष्ठा macsec_tx_sa - transmit secure association
 * @active:
 * @next_pn: packet number to use क्रम the next packet
 * @lock: protects next_pn manipulations
 * @key: key काष्ठाure
 * @ssci: लघु secure channel identअगरier
 * @stats: per-SA stats
 */
काष्ठा macsec_tx_sa अणु
	काष्ठा macsec_key key;
	ssci_t ssci;
	spinlock_t lock;
	जोड़ अणु
		pn_t next_pn_halves;
		u64 next_pn;
	पूर्ण;
	refcount_t refcnt;
	bool active;
	काष्ठा macsec_tx_sa_stats __percpu *stats;
	काष्ठा rcu_head rcu;
पूर्ण;

/**
 * काष्ठा macsec_tx_sc - transmit secure channel
 * @active:
 * @encoding_sa: association number of the SA currently in use
 * @encrypt: encrypt packets on transmit, or authenticate only
 * @send_sci: always include the SCI in the SecTAG
 * @end_station:
 * @scb: single copy broadcast flag
 * @sa: array of secure associations
 * @stats: stats क्रम this TXSC
 */
काष्ठा macsec_tx_sc अणु
	bool active;
	u8 encoding_sa;
	bool encrypt;
	bool send_sci;
	bool end_station;
	bool scb;
	काष्ठा macsec_tx_sa __rcu *sa[MACSEC_NUM_AN];
	काष्ठा pcpu_tx_sc_stats __percpu *stats;
पूर्ण;

/**
 * काष्ठा macsec_secy - MACsec Security Entity
 * @netdev: netdevice क्रम this SecY
 * @n_rx_sc: number of receive secure channels configured on this SecY
 * @sci: secure channel identअगरier used क्रम tx
 * @key_len: length of keys used by the cipher suite
 * @icv_len: length of ICV used by the cipher suite
 * @validate_frames: validation mode
 * @xpn: enable XPN क्रम this SecY
 * @operational: MAC_Operational flag
 * @protect_frames: enable protection क्रम this SecY
 * @replay_protect: enable packet number checks on receive
 * @replay_winकरोw: size of the replay winकरोw
 * @tx_sc: transmit secure channel
 * @rx_sc: linked list of receive secure channels
 */
काष्ठा macsec_secy अणु
	काष्ठा net_device *netdev;
	अचिन्हित पूर्णांक n_rx_sc;
	sci_t sci;
	u16 key_len;
	u16 icv_len;
	क्रमागत macsec_validation_type validate_frames;
	bool xpn;
	bool operational;
	bool protect_frames;
	bool replay_protect;
	u32 replay_winकरोw;
	काष्ठा macsec_tx_sc tx_sc;
	काष्ठा macsec_rx_sc __rcu *rx_sc;
पूर्ण;

/**
 * काष्ठा macsec_context - MACsec context क्रम hardware offloading
 */
काष्ठा macsec_context अणु
	जोड़ अणु
		काष्ठा net_device *netdev;
		काष्ठा phy_device *phydev;
	पूर्ण;
	क्रमागत macsec_offload offload;

	काष्ठा macsec_secy *secy;
	काष्ठा macsec_rx_sc *rx_sc;
	काष्ठा अणु
		अचिन्हित अक्षर assoc_num;
		u8 key[MACSEC_KEYID_LEN];
		जोड़ अणु
			काष्ठा macsec_rx_sa *rx_sa;
			काष्ठा macsec_tx_sa *tx_sa;
		पूर्ण;
	पूर्ण sa;
	जोड़ अणु
		काष्ठा macsec_tx_sc_stats *tx_sc_stats;
		काष्ठा macsec_tx_sa_stats *tx_sa_stats;
		काष्ठा macsec_rx_sc_stats *rx_sc_stats;
		काष्ठा macsec_rx_sa_stats *rx_sa_stats;
		काष्ठा macsec_dev_stats  *dev_stats;
	पूर्ण stats;

	u8 prepare:1;
पूर्ण;

/**
 * काष्ठा macsec_ops - MACsec offloading operations
 */
काष्ठा macsec_ops अणु
	/* Device wide */
	पूर्णांक (*mकरो_dev_खोलो)(काष्ठा macsec_context *ctx);
	पूर्णांक (*mकरो_dev_stop)(काष्ठा macsec_context *ctx);
	/* SecY */
	पूर्णांक (*mकरो_add_secy)(काष्ठा macsec_context *ctx);
	पूर्णांक (*mकरो_upd_secy)(काष्ठा macsec_context *ctx);
	पूर्णांक (*mकरो_del_secy)(काष्ठा macsec_context *ctx);
	/* Security channels */
	पूर्णांक (*mकरो_add_rxsc)(काष्ठा macsec_context *ctx);
	पूर्णांक (*mकरो_upd_rxsc)(काष्ठा macsec_context *ctx);
	पूर्णांक (*mकरो_del_rxsc)(काष्ठा macsec_context *ctx);
	/* Security associations */
	पूर्णांक (*mकरो_add_rxsa)(काष्ठा macsec_context *ctx);
	पूर्णांक (*mकरो_upd_rxsa)(काष्ठा macsec_context *ctx);
	पूर्णांक (*mकरो_del_rxsa)(काष्ठा macsec_context *ctx);
	पूर्णांक (*mकरो_add_txsa)(काष्ठा macsec_context *ctx);
	पूर्णांक (*mकरो_upd_txsa)(काष्ठा macsec_context *ctx);
	पूर्णांक (*mकरो_del_txsa)(काष्ठा macsec_context *ctx);
	/* Statistics */
	पूर्णांक (*mकरो_get_dev_stats)(काष्ठा macsec_context *ctx);
	पूर्णांक (*mकरो_get_tx_sc_stats)(काष्ठा macsec_context *ctx);
	पूर्णांक (*mकरो_get_tx_sa_stats)(काष्ठा macsec_context *ctx);
	पूर्णांक (*mकरो_get_rx_sc_stats)(काष्ठा macsec_context *ctx);
	पूर्णांक (*mकरो_get_rx_sa_stats)(काष्ठा macsec_context *ctx);
पूर्ण;

व्योम macsec_pn_wrapped(काष्ठा macsec_secy *secy, काष्ठा macsec_tx_sa *tx_sa);

#पूर्ण_अगर /* _NET_MACSEC_H_ */
