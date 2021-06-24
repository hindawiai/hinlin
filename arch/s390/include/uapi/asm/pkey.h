<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * Userspace पूर्णांकerface to the pkey device driver
 *
 * Copyright IBM Corp. 2017, 2019
 *
 * Author: Harald Freudenberger <freude@de.ibm.com>
 *
 */

#अगर_अघोषित _UAPI_PKEY_H
#घोषणा _UAPI_PKEY_H

#समावेश <linux/ioctl.h>
#समावेश <linux/types.h>

/*
 * Ioctl calls supported by the pkey device driver
 */

#घोषणा PKEY_IOCTL_MAGIC 'p'

#घोषणा SECKEYBLOBSIZE	64	   /* secure key blob size is always 64 bytes */
#घोषणा PROTKEYBLOBSIZE 80	/* रक्षित key blob size is always 80 bytes */
#घोषणा MAXPROTKEYSIZE	64	/* a रक्षित key blob may be up to 64 bytes */
#घोषणा MAXCLRKEYSIZE	32	   /* a clear key value may be up to 32 bytes */
#घोषणा MAXAESCIPHERKEYSIZE 136  /* our aes cipher keys have always 136 bytes */
#घोषणा MINEP11AESKEYBLOBSIZE 256  /* min EP11 AES key blob size  */
#घोषणा MAXEP11AESKEYBLOBSIZE 320  /* max EP11 AES key blob size */

/* Minimum size of a key blob */
#घोषणा MINKEYBLOBSIZE	SECKEYBLOBSIZE

/* defines क्रम the type field within the pkey_protkey काष्ठा */
#घोषणा PKEY_KEYTYPE_AES_128		      1
#घोषणा PKEY_KEYTYPE_AES_192		      2
#घोषणा PKEY_KEYTYPE_AES_256		      3
#घोषणा PKEY_KEYTYPE_ECC		      4

/* the newer ioctls use a pkey_key_type क्रमागत क्रम type inक्रमmation */
क्रमागत pkey_key_type अणु
	PKEY_TYPE_CCA_DATA   = (__u32) 1,
	PKEY_TYPE_CCA_CIPHER = (__u32) 2,
	PKEY_TYPE_EP11	     = (__u32) 3,
	PKEY_TYPE_CCA_ECC    = (__u32) 0x1f,
	PKEY_TYPE_EP11_AES   = (__u32) 6,
	PKEY_TYPE_EP11_ECC   = (__u32) 7,
पूर्ण;

/* the newer ioctls use a pkey_key_size क्रमागत क्रम key size inक्रमmation */
क्रमागत pkey_key_size अणु
	PKEY_SIZE_AES_128 = (__u32) 128,
	PKEY_SIZE_AES_192 = (__u32) 192,
	PKEY_SIZE_AES_256 = (__u32) 256,
	PKEY_SIZE_UNKNOWN = (__u32) 0xFFFFFFFF,
पूर्ण;

/* some of the newer ioctls use these flags */
#घोषणा PKEY_FLAGS_MATCH_CUR_MKVP  0x00000002
#घोषणा PKEY_FLAGS_MATCH_ALT_MKVP  0x00000004

/* keygenflags defines क्रम CCA AES cipher keys */
#घोषणा PKEY_KEYGEN_XPRT_SYM  0x00008000
#घोषणा PKEY_KEYGEN_XPRT_UASY 0x00004000
#घोषणा PKEY_KEYGEN_XPRT_AASY 0x00002000
#घोषणा PKEY_KEYGEN_XPRT_RAW  0x00001000
#घोषणा PKEY_KEYGEN_XPRT_CPAC 0x00000800
#घोषणा PKEY_KEYGEN_XPRT_DES  0x00000080
#घोषणा PKEY_KEYGEN_XPRT_AES  0x00000040
#घोषणा PKEY_KEYGEN_XPRT_RSA  0x00000008

/* Struct to hold apqn target info (card/करोमुख्य pair) */
काष्ठा pkey_apqn अणु
	__u16 card;
	__u16 करोमुख्य;
पूर्ण;

/* Struct to hold a CCA AES secure key blob */
काष्ठा pkey_seckey अणु
	__u8  seckey[SECKEYBLOBSIZE];		  /* the secure key blob */
पूर्ण;

/* Struct to hold रक्षित key and length info */
काष्ठा pkey_protkey अणु
	__u32 type;	 /* key type, one of the PKEY_KEYTYPE_AES values */
	__u32 len;		/* bytes actually stored in protkey[]	 */
	__u8  protkey[MAXPROTKEYSIZE];	       /* the रक्षित key blob */
पूर्ण;

/* Struct to hold an AES clear key value */
काष्ठा pkey_clrkey अणु
	__u8  clrkey[MAXCLRKEYSIZE]; /* 16, 24, or 32 byte clear key value */
पूर्ण;

/*
 * EP11 key blobs of type PKEY_TYPE_EP11_AES and PKEY_TYPE_EP11_ECC
 * are ep11 blobs prepended by this header:
 */
काष्ठा ep11kblob_header अणु
	__u8  type;	/* always 0x00 */
	__u8  hver;	/* header version,  currently needs to be 0x00 */
	__u16 len;	/* total length in bytes (including this header) */
	__u8  version;	/* PKEY_TYPE_EP11_AES or PKEY_TYPE_EP11_ECC */
	__u8  res0;	/* unused */
	__u16 bitlen;	/* clear key bit len, 0 क्रम unknown */
	__u8  res1[8];	/* unused */
पूर्ण __packed;

/*
 * Generate CCA AES secure key.
 */
काष्ठा pkey_genseck अणु
	__u16 cardnr;		    /* in: card to use or FFFF क्रम any	 */
	__u16 करोमुख्य;		    /* in: करोमुख्य or FFFF क्रम any	 */
	__u32 keytype;		    /* in: key type to generate		 */
	काष्ठा pkey_seckey seckey;  /* out: the secure key blob		 */
पूर्ण;
#घोषणा PKEY_GENSECK _IOWR(PKEY_IOCTL_MAGIC, 0x01, काष्ठा pkey_genseck)

/*
 * Conकाष्ठा CCA AES secure key from clear key value
 */
काष्ठा pkey_clr2seck अणु
	__u16 cardnr;		    /* in: card to use or FFFF क्रम any	 */
	__u16 करोमुख्य;		    /* in: करोमुख्य or FFFF क्रम any	 */
	__u32 keytype;		    /* in: key type to generate		 */
	काष्ठा pkey_clrkey clrkey;  /* in: the clear key value		 */
	काष्ठा pkey_seckey seckey;  /* out: the secure key blob		 */
पूर्ण;
#घोषणा PKEY_CLR2SECK _IOWR(PKEY_IOCTL_MAGIC, 0x02, काष्ठा pkey_clr2seck)

/*
 * Fabricate AES रक्षित key from a CCA AES secure key
 */
काष्ठा pkey_sec2protk अणु
	__u16 cardnr;		     /* in: card to use or FFFF क्रम any   */
	__u16 करोमुख्य;		     /* in: करोमुख्य or FFFF क्रम any	  */
	काष्ठा pkey_seckey seckey;   /* in: the secure key blob		  */
	काष्ठा pkey_protkey protkey; /* out: the रक्षित key		  */
पूर्ण;
#घोषणा PKEY_SEC2PROTK _IOWR(PKEY_IOCTL_MAGIC, 0x03, काष्ठा pkey_sec2protk)

/*
 * Fabricate AES रक्षित key from clear key value
 */
काष्ठा pkey_clr2protk अणु
	__u32 keytype;		     /* in: key type to generate	  */
	काष्ठा pkey_clrkey clrkey;   /* in: the clear key value		  */
	काष्ठा pkey_protkey protkey; /* out: the रक्षित key		  */
पूर्ण;
#घोषणा PKEY_CLR2PROTK _IOWR(PKEY_IOCTL_MAGIC, 0x04, काष्ठा pkey_clr2protk)

/*
 * Search क्रम matching crypto card based on the Master Key
 * Verअगरication Pattern provided inside a CCA AES secure key.
 */
काष्ठा pkey_findcard अणु
	काष्ठा pkey_seckey seckey;	       /* in: the secure key blob */
	__u16  cardnr;			       /* out: card number	  */
	__u16  करोमुख्य;			       /* out: करोमुख्य number	  */
पूर्ण;
#घोषणा PKEY_FINDCARD _IOWR(PKEY_IOCTL_MAGIC, 0x05, काष्ठा pkey_findcard)

/*
 * Combined together: findcard + sec2prot
 */
काष्ठा pkey_skey2pkey अणु
	काष्ठा pkey_seckey seckey;   /* in: the secure key blob		  */
	काष्ठा pkey_protkey protkey; /* out: the रक्षित key		  */
पूर्ण;
#घोषणा PKEY_SKEY2PKEY _IOWR(PKEY_IOCTL_MAGIC, 0x06, काष्ठा pkey_skey2pkey)

/*
 * Verअगरy the given CCA AES secure key क्रम being able to be useable with
 * the pkey module. Check क्रम correct key type and check क्रम having at
 * least one crypto card being able to handle this key (master key
 * or old master key verअगरication pattern matches).
 * Return some info about the key: keysize in bits, keytype (currently
 * only AES), flag अगर key is wrapped with an old MKVP.
 */
काष्ठा pkey_verअगरykey अणु
	काष्ठा pkey_seckey seckey;	       /* in: the secure key blob */
	__u16  cardnr;			       /* out: card number	  */
	__u16  करोमुख्य;			       /* out: करोमुख्य number	  */
	__u16  keysize;			       /* out: key size in bits   */
	__u32  attributes;		       /* out: attribute bits	  */
पूर्ण;
#घोषणा PKEY_VERIFYKEY _IOWR(PKEY_IOCTL_MAGIC, 0x07, काष्ठा pkey_verअगरykey)
#घोषणा PKEY_VERIFY_ATTR_AES	   0x00000001  /* key is an AES key */
#घोषणा PKEY_VERIFY_ATTR_OLD_MKVP  0x00000100  /* key has old MKVP value */

/*
 * Generate AES अक्रमom रक्षित key.
 */
काष्ठा pkey_genprotk अणु
	__u32 keytype;			       /* in: key type to generate */
	काष्ठा pkey_protkey protkey;	       /* out: the रक्षित key   */
पूर्ण;

#घोषणा PKEY_GENPROTK _IOWR(PKEY_IOCTL_MAGIC, 0x08, काष्ठा pkey_genprotk)

/*
 * Verअगरy an AES रक्षित key.
 */
काष्ठा pkey_verअगरyprotk अणु
	काष्ठा pkey_protkey protkey;	/* in: the रक्षित key to verअगरy */
पूर्ण;

#घोषणा PKEY_VERIFYPROTK _IOW(PKEY_IOCTL_MAGIC, 0x09, काष्ठा pkey_verअगरyprotk)

/*
 * Transक्रमm an key blob (of any type) पूर्णांकo a रक्षित key
 */
काष्ठा pkey_kblob2pkey अणु
	__u8 __user *key;		/* in: the key blob	   */
	__u32 keylen;			/* in: the key blob length */
	काष्ठा pkey_protkey protkey;	/* out: the रक्षित key  */
पूर्ण;
#घोषणा PKEY_KBLOB2PROTK _IOWR(PKEY_IOCTL_MAGIC, 0x0A, काष्ठा pkey_kblob2pkey)

/*
 * Generate secure key, version 2.
 * Generate CCA AES secure key, CCA AES cipher key or EP11 AES secure key.
 * There needs to be a list of apqns given with at least one entry in there.
 * All apqns in the list need to be exact apqns, 0xFFFF as ANY card or करोमुख्य
 * is not supported. The implementation walks through the list of apqns and
 * tries to send the request to each apqn without any further checking (like
 * card type or online state). If the apqn fails, simple the next one in the
 * list is tried until success (वापस 0) or the end of the list is reached
 * (वापस -1 with त्रुटि_सं ENODEV). You may use the PKEY_APQNS4KT ioctl to
 * generate a list of apqns based on the key type to generate.
 * The keygenflags argument is passed to the low level generation functions
 * inभागidual क्रम the key type and has a key type specअगरic meaning. When
 * generating CCA cipher keys you can use one or more of the PKEY_KEYGEN_*
 * flags to widen the export possibilities. By शेष a cipher key is
 * only exportable क्रम CPACF (PKEY_KEYGEN_XPRT_CPAC).
 * The keygenflag argument क्रम generating an EP11 AES key should either be 0
 * to use the शेषs which are XCP_BLOB_ENCRYPT, XCP_BLOB_DECRYPT and
 * XCP_BLOB_PROTKEY_EXTRACTABLE or a valid combination of XCP_BLOB_* flags.
 */
काष्ठा pkey_genseck2 अणु
	काष्ठा pkey_apqn __user *apqns; /* in: ptr to list of apqn tarमाला_लो*/
	__u32 apqn_entries;	    /* in: # of apqn target list entries  */
	क्रमागत pkey_key_type type;    /* in: key type to generate		  */
	क्रमागत pkey_key_size size;    /* in: key size to generate		  */
	__u32 keygenflags;	    /* in: key generation flags		  */
	__u8 __user *key;	    /* in: poपूर्णांकer to key blob buffer	  */
	__u32 keylen;		    /* in: available key blob buffer size */
				    /* out: actual key blob size	  */
पूर्ण;
#घोषणा PKEY_GENSECK2 _IOWR(PKEY_IOCTL_MAGIC, 0x11, काष्ठा pkey_genseck2)

/*
 * Generate secure key from clear key value, version 2.
 * Conकाष्ठा an CCA AES secure key, CCA AES cipher key or EP11 AES secure
 * key from a given clear key value.
 * There needs to be a list of apqns given with at least one entry in there.
 * All apqns in the list need to be exact apqns, 0xFFFF as ANY card or करोमुख्य
 * is not supported. The implementation walks through the list of apqns and
 * tries to send the request to each apqn without any further checking (like
 * card type or online state). If the apqn fails, simple the next one in the
 * list is tried until success (वापस 0) or the end of the list is reached
 * (वापस -1 with त्रुटि_सं ENODEV). You may use the PKEY_APQNS4KT ioctl to
 * generate a list of apqns based on the key type to generate.
 * The keygenflags argument is passed to the low level generation functions
 * inभागidual क्रम the key type and has a key type specअगरic meaning. When
 * generating CCA cipher keys you can use one or more of the PKEY_KEYGEN_*
 * flags to widen the export possibilities. By शेष a cipher key is
 * only exportable क्रम CPACF (PKEY_KEYGEN_XPRT_CPAC).
 * The keygenflag argument क्रम generating an EP11 AES key should either be 0
 * to use the शेषs which are XCP_BLOB_ENCRYPT, XCP_BLOB_DECRYPT and
 * XCP_BLOB_PROTKEY_EXTRACTABLE or a valid combination of XCP_BLOB_* flags.
 */
काष्ठा pkey_clr2seck2 अणु
	काष्ठा pkey_apqn __user *apqns; /* in: ptr to list of apqn tarमाला_लो */
	__u32 apqn_entries;	    /* in: # of apqn target list entries   */
	क्रमागत pkey_key_type type;    /* in: key type to generate		   */
	क्रमागत pkey_key_size size;    /* in: key size to generate		   */
	__u32 keygenflags;	    /* in: key generation flags		   */
	काष्ठा pkey_clrkey clrkey;  /* in: the clear key value		   */
	__u8 __user *key;	    /* in: poपूर्णांकer to key blob buffer	   */
	__u32 keylen;		    /* in: available key blob buffer size  */
				    /* out: actual key blob size	   */
पूर्ण;
#घोषणा PKEY_CLR2SECK2 _IOWR(PKEY_IOCTL_MAGIC, 0x12, काष्ठा pkey_clr2seck2)

/*
 * Verअगरy the given secure key, version 2.
 * Check क्रम correct key type. If cardnr and करोमुख्य are given (are not
 * 0xFFFF) also check अगर this apqn is able to handle this type of key.
 * If cardnr and/or करोमुख्य is 0xFFFF, on वापस these values are filled
 * with one apqn able to handle this key.
 * The function also checks क्रम the master key verअगरication patterns
 * of the key matching to the current or alternate mkvp of the apqn.
 * For CCA AES secure keys and CCA AES cipher keys this means to check
 * the key's mkvp against the current or old mkvp of the apqns. The flags
 * field is updated with some additional info about the apqn mkvp
 * match: If the current mkvp matches to the key's mkvp then the
 * PKEY_FLAGS_MATCH_CUR_MKVP bit is set, अगर the alternate mkvp matches to
 * the key's mkvp the PKEY_FLAGS_MATCH_ALT_MKVP is set. For CCA keys the
 * alternate mkvp is the old master key verअगरication pattern.
 * CCA AES secure keys are also checked to have the CPACF export allowed
 * bit enabled (XPRTCPAC) in the kmf1 field.
 * EP11 keys are also supported and the wkvp of the key is checked against
 * the current wkvp of the apqns. There is no alternate क्रम this type of
 * key and so on a match the flag PKEY_FLAGS_MATCH_CUR_MKVP always is set.
 * EP11 keys are also checked to have XCP_BLOB_PROTKEY_EXTRACTABLE set.
 * The ioctl वापसs 0 as दीर्घ as the given or found apqn matches to
 * matches with the current or alternate mkvp to the key's mkvp. If the given
 * apqn करोes not match or there is no such apqn found, -1 with त्रुटि_सं
 * ENODEV is वापसed.
 */
काष्ठा pkey_verअगरykey2 अणु
	__u8 __user *key;	    /* in: poपूर्णांकer to key blob		 */
	__u32 keylen;		    /* in: key blob size		 */
	__u16 cardnr;		    /* in/out: card number		 */
	__u16 करोमुख्य;		    /* in/out: करोमुख्य number		 */
	क्रमागत pkey_key_type type;    /* out: the key type		 */
	क्रमागत pkey_key_size size;    /* out: the key size		 */
	__u32 flags;		    /* out: additional key info flags	 */
पूर्ण;
#घोषणा PKEY_VERIFYKEY2 _IOWR(PKEY_IOCTL_MAGIC, 0x17, काष्ठा pkey_verअगरykey2)

/*
 * Transक्रमm a key blob पूर्णांकo a रक्षित key, version 2.
 * There needs to be a list of apqns given with at least one entry in there.
 * All apqns in the list need to be exact apqns, 0xFFFF as ANY card or करोमुख्य
 * is not supported. The implementation walks through the list of apqns and
 * tries to send the request to each apqn without any further checking (like
 * card type or online state). If the apqn fails, simple the next one in the
 * list is tried until success (वापस 0) or the end of the list is reached
 * (वापस -1 with त्रुटि_सं ENODEV). You may use the PKEY_APQNS4K ioctl to
 * generate a list of apqns based on the key.
 * Deriving ECC रक्षित keys from ECC secure keys is not supported with
 * this ioctl, use PKEY_KBLOB2PROTK3 क्रम this purpose.
 */
काष्ठा pkey_kblob2pkey2 अणु
	__u8 __user *key;	     /* in: poपूर्णांकer to key blob		   */
	__u32 keylen;		     /* in: key blob size		   */
	काष्ठा pkey_apqn __user *apqns; /* in: ptr to list of apqn tarमाला_लो */
	__u32 apqn_entries;	     /* in: # of apqn target list entries  */
	काष्ठा pkey_protkey protkey; /* out: the रक्षित key		   */
पूर्ण;
#घोषणा PKEY_KBLOB2PROTK2 _IOWR(PKEY_IOCTL_MAGIC, 0x1A, काष्ठा pkey_kblob2pkey2)

/*
 * Build a list of APQNs based on a key blob given.
 * Is able to find out which type of secure key is given (CCA AES secure
 * key, CCA AES cipher key, CCA ECC निजी key, EP11 AES key, EP11 ECC निजी
 * key) and tries to find all matching crypto cards based on the MKVP and maybe
 * other criterias (like CCA AES cipher keys need a CEX5C or higher, EP11 keys
 * with BLOB_PKEY_EXTRACTABLE need a CEX7 and EP11 api version 4). The list of
 * APQNs is further filtered by the key's mkvp which needs to match to either
 * the current mkvp (CCA and EP11) or the alternate mkvp (old mkvp, CCA adapters
 * only) of the apqns. The flags argument may be used to limit the matching
 * apqns. If the PKEY_FLAGS_MATCH_CUR_MKVP is given, only the current mkvp of
 * each apqn is compared. Likewise with the PKEY_FLAGS_MATCH_ALT_MKVP. If both
 * are given, it is assumed to वापस apqns where either the current or the
 * alternate mkvp matches. At least one of the matching flags needs to be given.
 * The flags argument क्रम EP11 keys has no further action and is currently
 * ignored (but needs to be given as PKEY_FLAGS_MATCH_CUR_MKVP) as there is only
 * the wkvp from the key to match against the apqn's wkvp.
 * The list of matching apqns is stored पूर्णांकo the space given by the apqns
 * argument and the number of stored entries goes पूर्णांकo apqn_entries. If the list
 * is empty (apqn_entries is 0) the apqn_entries field is updated to the number
 * of apqn tarमाला_लो found and the ioctl वापसs with 0. If apqn_entries is > 0
 * but the number of apqn tarमाला_लो करोes not fit पूर्णांकo the list, the apqn_tarमाला_लो
 * field is updatedd with the number of reqired entries but there are no apqn
 * values stored in the list and the ioctl वापसs with ENOSPC. If no matching
 * APQN is found, the ioctl वापसs with 0 but the apqn_entries value is 0.
 */
काष्ठा pkey_apqns4key अणु
	__u8 __user *key;	   /* in: poपूर्णांकer to key blob		      */
	__u32 keylen;		   /* in: key blob size			      */
	__u32 flags;		   /* in: match controlling flags	      */
	काष्ठा pkey_apqn __user *apqns; /* in/out: ptr to list of apqn tarमाला_लो*/
	__u32 apqn_entries;	   /* in: max # of apqn entries in the list   */
				   /* out: # apqns stored पूर्णांकo the list	      */
पूर्ण;
#घोषणा PKEY_APQNS4K _IOWR(PKEY_IOCTL_MAGIC, 0x1B, काष्ठा pkey_apqns4key)

/*
 * Build a list of APQNs based on a key type given.
 * Build a list of APQNs based on a given key type and maybe further
 * restrict the list by given master key verअगरication patterns.
 * For dअगरferent key types there may be dअगरferent ways to match the
 * master key verअगरication patterns. For CCA keys (CCA data key and CCA
 * cipher key) the first 8 bytes of cur_mkvp refer to the current AES mkvp value
 * of the apqn and the first 8 bytes of the alt_mkvp refer to the old AES mkvp.
 * For CCA ECC keys it is similar but the match is against the APKA current/old
 * mkvp. The flags argument controls अगर the apqns current and/or alternate mkvp
 * should match. If the PKEY_FLAGS_MATCH_CUR_MKVP is given, only the current
 * mkvp of each apqn is compared. Likewise with the PKEY_FLAGS_MATCH_ALT_MKVP.
 * If both are given, it is assumed to वापस apqns where either the
 * current or the alternate mkvp matches. If no match flag is given
 * (flags is 0) the mkvp values are ignored क्रम the match process.
 * For EP11 keys there is only the current wkvp. So अगर the apqns should also
 * match to a given wkvp, then the PKEY_FLAGS_MATCH_CUR_MKVP flag should be
 * set. The wkvp value is 32 bytes but only the lefपंचांगost 16 bytes are compared
 * against the lefपंचांगost 16 byte of the wkvp of the apqn.
 * The list of matching apqns is stored पूर्णांकo the space given by the apqns
 * argument and the number of stored entries goes पूर्णांकo apqn_entries. If the list
 * is empty (apqn_entries is 0) the apqn_entries field is updated to the number
 * of apqn tarमाला_लो found and the ioctl वापसs with 0. If apqn_entries is > 0
 * but the number of apqn tarमाला_लो करोes not fit पूर्णांकo the list, the apqn_tarमाला_लो
 * field is updatedd with the number of reqired entries but there are no apqn
 * values stored in the list and the ioctl वापसs with ENOSPC. If no matching
 * APQN is found, the ioctl वापसs with 0 but the apqn_entries value is 0.
 */
काष्ठा pkey_apqns4keytype अणु
	क्रमागत pkey_key_type type;   /* in: key type			      */
	__u8  cur_mkvp[32];	   /* in: current mkvp			      */
	__u8  alt_mkvp[32];	   /* in: alternate mkvp		      */
	__u32 flags;		   /* in: match controlling flags	      */
	काष्ठा pkey_apqn __user *apqns; /* in/out: ptr to list of apqn tarमाला_लो*/
	__u32 apqn_entries;	   /* in: max # of apqn entries in the list   */
				   /* out: # apqns stored पूर्णांकo the list	      */
पूर्ण;
#घोषणा PKEY_APQNS4KT _IOWR(PKEY_IOCTL_MAGIC, 0x1C, काष्ठा pkey_apqns4keytype)

/*
 * Transक्रमm a key blob पूर्णांकo a रक्षित key, version 3.
 * The dअगरference to version 2 of this ioctl is that the रक्षित key
 * buffer is now explicitly and not within a काष्ठा pkey_protkey any more.
 * So this ioctl is also able to handle EP11 and CCA ECC secure keys and
 * provide ECC रक्षित keys.
 * There needs to be a list of apqns given with at least one entry in there.
 * All apqns in the list need to be exact apqns, 0xFFFF as ANY card or करोमुख्य
 * is not supported. The implementation walks through the list of apqns and
 * tries to send the request to each apqn without any further checking (like
 * card type or online state). If the apqn fails, simple the next one in the
 * list is tried until success (वापस 0) or the end of the list is reached
 * (वापस -1 with त्रुटि_सं ENODEV). You may use the PKEY_APQNS4K ioctl to
 * generate a list of apqns based on the key.
 */
काष्ठा pkey_kblob2pkey3 अणु
	__u8 __user *key;	     /* in: poपूर्णांकer to key blob		   */
	__u32 keylen;		     /* in: key blob size		   */
	काष्ठा pkey_apqn __user *apqns; /* in: ptr to list of apqn tarमाला_लो */
	__u32 apqn_entries;	     /* in: # of apqn target list entries  */
	__u32 pkeytype;		/* out: prot key type (क्रमागत pkey_key_type) */
	__u32 pkeylen;	 /* in/out: size of pkey buffer/actual len of pkey */
	__u8 __user *pkey;		 /* in: pkey blob buffer space ptr */
पूर्ण;
#घोषणा PKEY_KBLOB2PROTK3 _IOWR(PKEY_IOCTL_MAGIC, 0x1D, काष्ठा pkey_kblob2pkey3)

#पूर्ण_अगर /* _UAPI_PKEY_H */
