<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 *  Copyright IBM Corp. 2001, 2006
 *  Author(s): Robert Burroughs
 *	       Eric Rossman (edrossma@us.ibm.com)
 *
 *  Hotplug & misc device support: Jochen Roehrig (roehrig@de.ibm.com)
 *  Major cleanup & driver split: Martin Schwidefsky <schwidefsky@de.ibm.com>
 */

#अगर_अघोषित _ZCRYPT_CCA_KEY_H_
#घोषणा _ZCRYPT_CCA_KEY_H_

काष्ठा T6_keyBlock_hdr अणु
	अचिन्हित लघु blen;
	अचिन्हित लघु ulen;
	अचिन्हित लघु flags;
पूर्ण;

/**
 * mapping क्रम the cca निजी ME key token.
 * Three parts of पूर्णांकerest here: the header, the निजी section and
 * the खुला section.
 *
 * mapping क्रम the cca key token header
 */
काष्ठा cca_token_hdr अणु
	अचिन्हित अक्षर  token_identअगरier;
	अचिन्हित अक्षर  version;
	अचिन्हित लघु token_length;
	अचिन्हित अक्षर  reserved[4];
पूर्ण __packed;

#घोषणा CCA_TKN_HDR_ID_EXT 0x1E

#घोषणा CCA_PVT_USAGE_ALL 0x80

/**
 * mapping क्रम the cca खुला section
 * In a निजी key, the modulus करोesn't appear in the खुला
 * section. So, an arbitrary खुला exponent of 0x010001 will be
 * used, क्रम a section length of 0x0F always.
 */
काष्ठा cca_खुला_sec अणु
	अचिन्हित अक्षर  section_identअगरier;
	अचिन्हित अक्षर  version;
	अचिन्हित लघु section_length;
	अचिन्हित अक्षर  reserved[2];
	अचिन्हित लघु exponent_len;
	अचिन्हित लघु modulus_bit_len;
	अचिन्हित लघु modulus_byte_len;    /* In a निजी key, this is 0 */
पूर्ण __packed;

/**
 * mapping क्रम the cca निजी CRT key 'token'
 * The first three parts (the only parts considered in this release)
 * are: the header, the निजी section and the खुला section.
 * The header and खुला section are the same as क्रम the
 * काष्ठा cca_निजी_ext_ME
 *
 * Following the काष्ठाure are the quantities p, q, dp, dq, u, pad,
 * and modulus, in that order, where pad_len is the modulo 8
 * complement of the residue modulo 8 of the sum of
 * (p_len + q_len + dp_len + dq_len + u_len).
 */
काष्ठा cca_pvt_ext_CRT_sec अणु
	अचिन्हित अक्षर  section_identअगरier;
	अचिन्हित अक्षर  version;
	अचिन्हित लघु section_length;
	अचिन्हित अक्षर  निजी_key_hash[20];
	अचिन्हित अक्षर  reserved1[4];
	अचिन्हित अक्षर  key_क्रमmat;
	अचिन्हित अक्षर  reserved2;
	अचिन्हित अक्षर  key_name_hash[20];
	अचिन्हित अक्षर  key_use_flags[4];
	अचिन्हित लघु p_len;
	अचिन्हित लघु q_len;
	अचिन्हित लघु dp_len;
	अचिन्हित लघु dq_len;
	अचिन्हित लघु u_len;
	अचिन्हित लघु mod_len;
	अचिन्हित अक्षर  reserved3[4];
	अचिन्हित लघु pad_len;
	अचिन्हित अक्षर  reserved4[52];
	अचिन्हित अक्षर  confounder[8];
पूर्ण __packed;

#घोषणा CCA_PVT_EXT_CRT_SEC_ID_PVT 0x08
#घोषणा CCA_PVT_EXT_CRT_SEC_FMT_CL 0x40

/**
 * Set up निजी key fields of a type6 MEX message. The _pad variant
 * strips leading zeroes from the b_key.
 * Note that all numerics in the key token are big-endian,
 * जबतक the entries in the key block header are little-endian.
 *
 * @mex: poपूर्णांकer to user input data
 * @p: poपूर्णांकer to memory area क्रम the key
 *
 * Returns the size of the key area or negative त्रुटि_सं value.
 */
अटल अंतरभूत पूर्णांक zcrypt_type6_mex_key_en(काष्ठा ica_rsa_modexpo *mex, व्योम *p)
अणु
	अटल काष्ठा cca_token_hdr अटल_pub_hdr = अणु
		.token_identअगरier	=  0x1E,
	पूर्ण;
	अटल काष्ठा cca_खुला_sec अटल_pub_sec = अणु
		.section_identअगरier	=  0x04,
	पूर्ण;
	काष्ठा अणु
		काष्ठा T6_keyBlock_hdr t6_hdr;
		काष्ठा cca_token_hdr pubHdr;
		काष्ठा cca_खुला_sec pubSec;
		अक्षर exponent[0];
	पूर्ण __packed *key = p;
	अचिन्हित अक्षर *temp;
	पूर्णांक i;

	/*
	 * The inputdatalength was a selection criteria in the dispatching
	 * function zcrypt_rsa_modexpo(). However, करो a plausibility check
	 * here to make sure the following copy_from_user() can't be utilized
	 * to compromise the प्रणाली.
	 */
	अगर (WARN_ON_ONCE(mex->inputdatalength > 512))
		वापस -EINVAL;

	स_रखो(key, 0, माप(*key));

	key->pubHdr = अटल_pub_hdr;
	key->pubSec = अटल_pub_sec;

	/* key parameter block */
	temp = key->exponent;
	अगर (copy_from_user(temp, mex->b_key, mex->inputdatalength))
		वापस -EFAULT;
	/* Strip leading zeroes from b_key. */
	क्रम (i = 0; i < mex->inputdatalength; i++)
		अगर (temp[i])
			अवरोध;
	अगर (i >= mex->inputdatalength)
		वापस -EINVAL;
	स_हटाओ(temp, temp + i, mex->inputdatalength - i);
	temp += mex->inputdatalength - i;
	/* modulus */
	अगर (copy_from_user(temp, mex->n_modulus, mex->inputdatalength))
		वापस -EFAULT;

	key->pubSec.modulus_bit_len = 8 * mex->inputdatalength;
	key->pubSec.modulus_byte_len = mex->inputdatalength;
	key->pubSec.exponent_len = mex->inputdatalength - i;
	key->pubSec.section_length = माप(key->pubSec) +
					2*mex->inputdatalength - i;
	key->pubHdr.token_length =
		key->pubSec.section_length + माप(key->pubHdr);
	key->t6_hdr.ulen = key->pubHdr.token_length + 4;
	key->t6_hdr.blen = key->pubHdr.token_length + 6;
	वापस माप(*key) + 2*mex->inputdatalength - i;
पूर्ण

/**
 * Set up निजी key fields of a type6 CRT message.
 * Note that all numerics in the key token are big-endian,
 * जबतक the entries in the key block header are little-endian.
 *
 * @mex: poपूर्णांकer to user input data
 * @p: poपूर्णांकer to memory area क्रम the key
 *
 * Returns the size of the key area or -EFAULT
 */
अटल अंतरभूत पूर्णांक zcrypt_type6_crt_key(काष्ठा ica_rsa_modexpo_crt *crt, व्योम *p)
अणु
	अटल काष्ठा cca_खुला_sec अटल_cca_pub_sec = अणु
		.section_identअगरier = 4,
		.section_length = 0x000f,
		.exponent_len = 0x0003,
	पूर्ण;
	अटल अक्षर pk_exponent[3] = अणु 0x01, 0x00, 0x01 पूर्ण;
	काष्ठा अणु
		काष्ठा T6_keyBlock_hdr t6_hdr;
		काष्ठा cca_token_hdr token;
		काष्ठा cca_pvt_ext_CRT_sec pvt;
		अक्षर key_parts[0];
	पूर्ण __packed *key = p;
	काष्ठा cca_खुला_sec *pub;
	पूर्णांक लघु_len, दीर्घ_len, pad_len, key_len, size;

	/*
	 * The inputdatalength was a selection criteria in the dispatching
	 * function zcrypt_rsa_crt(). However, करो a plausibility check
	 * here to make sure the following copy_from_user() can't be utilized
	 * to compromise the प्रणाली.
	 */
	अगर (WARN_ON_ONCE(crt->inputdatalength > 512))
		वापस -EINVAL;

	स_रखो(key, 0, माप(*key));

	लघु_len = (crt->inputdatalength + 1) / 2;
	दीर्घ_len = लघु_len + 8;
	pad_len = -(3*दीर्घ_len + 2*लघु_len) & 7;
	key_len = 3*दीर्घ_len + 2*लघु_len + pad_len + crt->inputdatalength;
	size = माप(*key) + key_len + माप(*pub) + 3;

	/* parameter block.key block */
	key->t6_hdr.blen = size;
	key->t6_hdr.ulen = size - 2;

	/* key token header */
	key->token.token_identअगरier = CCA_TKN_HDR_ID_EXT;
	key->token.token_length = size - 6;

	/* निजी section */
	key->pvt.section_identअगरier = CCA_PVT_EXT_CRT_SEC_ID_PVT;
	key->pvt.section_length = माप(key->pvt) + key_len;
	key->pvt.key_क्रमmat = CCA_PVT_EXT_CRT_SEC_FMT_CL;
	key->pvt.key_use_flags[0] = CCA_PVT_USAGE_ALL;
	key->pvt.p_len = key->pvt.dp_len = key->pvt.u_len = दीर्घ_len;
	key->pvt.q_len = key->pvt.dq_len = लघु_len;
	key->pvt.mod_len = crt->inputdatalength;
	key->pvt.pad_len = pad_len;

	/* key parts */
	अगर (copy_from_user(key->key_parts, crt->np_prime, दीर्घ_len) ||
	    copy_from_user(key->key_parts + दीर्घ_len,
					crt->nq_prime, लघु_len) ||
	    copy_from_user(key->key_parts + दीर्घ_len + लघु_len,
					crt->bp_key, दीर्घ_len) ||
	    copy_from_user(key->key_parts + 2*दीर्घ_len + लघु_len,
					crt->bq_key, लघु_len) ||
	    copy_from_user(key->key_parts + 2*दीर्घ_len + 2*लघु_len,
					crt->u_mult_inv, दीर्घ_len))
		वापस -EFAULT;
	स_रखो(key->key_parts + 3*दीर्घ_len + 2*लघु_len + pad_len,
	       0xff, crt->inputdatalength);
	pub = (काष्ठा cca_खुला_sec *)(key->key_parts + key_len);
	*pub = अटल_cca_pub_sec;
	pub->modulus_bit_len = 8 * crt->inputdatalength;
	/*
	 * In a निजी key, the modulus करोesn't appear in the खुला
	 * section. So, an arbitrary खुला exponent of 0x010001 will be
	 * used.
	 */
	स_नकल((अक्षर *) (pub + 1), pk_exponent, 3);
	वापस size;
पूर्ण

#पूर्ण_अगर /* _ZCRYPT_CCA_KEY_H_ */
