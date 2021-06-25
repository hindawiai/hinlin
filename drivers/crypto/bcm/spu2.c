<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright 2016 Broadcom
 */

/*
 * This file works with the SPU2 version of the SPU. SPU2 has dअगरferent message
 * क्रमmats than the previous version of the SPU. All SPU message क्रमmat
 * dअगरferences should be hidden in the spux.c,h files.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>

#समावेश "util.h"
#समावेश "spu.h"
#समावेश "spu2.h"

#घोषणा SPU2_TX_STATUS_LEN  0	/* SPU2 has no STATUS in input packet */

/*
 * Controlled by pkt_stat_cnt field in CRYPTO_SS_SPU0_CORE_SPU2_CONTROL0
 * रेजिस्टर. Defaults to 2.
 */
#घोषणा SPU2_RX_STATUS_LEN  2

क्रमागत spu2_proto_sel अणु
	SPU2_PROTO_RESV = 0,
	SPU2_MACSEC_SECTAG8_ECB = 1,
	SPU2_MACSEC_SECTAG8_SCB = 2,
	SPU2_MACSEC_SECTAG16 = 3,
	SPU2_MACSEC_SECTAG16_8_XPN = 4,
	SPU2_IPSEC = 5,
	SPU2_IPSEC_ESN = 6,
	SPU2_TLS_CIPHER = 7,
	SPU2_TLS_AEAD = 8,
	SPU2_DTLS_CIPHER = 9,
	SPU2_DTLS_AEAD = 10
पूर्ण;

अटल अक्षर *spu2_cipher_type_names[] = अणु "None", "AES128", "AES192", "AES256",
	"DES", "3DES"
पूर्ण;

अटल अक्षर *spu2_cipher_mode_names[] = अणु "ECB", "CBC", "CTR", "CFB", "OFB",
	"XTS", "CCM", "GCM"
पूर्ण;

अटल अक्षर *spu2_hash_type_names[] = अणु "None", "AES128", "AES192", "AES256",
	"Reserved", "Reserved", "MD5", "SHA1", "SHA224", "SHA256", "SHA384",
	"SHA512", "SHA512/224", "SHA512/256", "SHA3-224", "SHA3-256",
	"SHA3-384", "SHA3-512"
पूर्ण;

अटल अक्षर *spu2_hash_mode_names[] = अणु "CMAC", "CBC-MAC", "XCBC-MAC", "HMAC",
	"Rabin", "CCM", "GCM", "Reserved"
पूर्ण;

अटल अक्षर *spu2_ciph_type_name(क्रमागत spu2_cipher_type cipher_type)
अणु
	अगर (cipher_type >= SPU2_CIPHER_TYPE_LAST)
		वापस "Reserved";
	वापस spu2_cipher_type_names[cipher_type];
पूर्ण

अटल अक्षर *spu2_ciph_mode_name(क्रमागत spu2_cipher_mode cipher_mode)
अणु
	अगर (cipher_mode >= SPU2_CIPHER_MODE_LAST)
		वापस "Reserved";
	वापस spu2_cipher_mode_names[cipher_mode];
पूर्ण

अटल अक्षर *spu2_hash_type_name(क्रमागत spu2_hash_type hash_type)
अणु
	अगर (hash_type >= SPU2_HASH_TYPE_LAST)
		वापस "Reserved";
	वापस spu2_hash_type_names[hash_type];
पूर्ण

अटल अक्षर *spu2_hash_mode_name(क्रमागत spu2_hash_mode hash_mode)
अणु
	अगर (hash_mode >= SPU2_HASH_MODE_LAST)
		वापस "Reserved";
	वापस spu2_hash_mode_names[hash_mode];
पूर्ण

/*
 * Convert from a software cipher mode value to the corresponding value
 * क्रम SPU2.
 */
अटल पूर्णांक spu2_cipher_mode_xlate(क्रमागत spu_cipher_mode cipher_mode,
				  क्रमागत spu2_cipher_mode *spu2_mode)
अणु
	चयन (cipher_mode) अणु
	हाल CIPHER_MODE_ECB:
		*spu2_mode = SPU2_CIPHER_MODE_ECB;
		अवरोध;
	हाल CIPHER_MODE_CBC:
		*spu2_mode = SPU2_CIPHER_MODE_CBC;
		अवरोध;
	हाल CIPHER_MODE_OFB:
		*spu2_mode = SPU2_CIPHER_MODE_OFB;
		अवरोध;
	हाल CIPHER_MODE_CFB:
		*spu2_mode = SPU2_CIPHER_MODE_CFB;
		अवरोध;
	हाल CIPHER_MODE_CTR:
		*spu2_mode = SPU2_CIPHER_MODE_CTR;
		अवरोध;
	हाल CIPHER_MODE_CCM:
		*spu2_mode = SPU2_CIPHER_MODE_CCM;
		अवरोध;
	हाल CIPHER_MODE_GCM:
		*spu2_mode = SPU2_CIPHER_MODE_GCM;
		अवरोध;
	हाल CIPHER_MODE_XTS:
		*spu2_mode = SPU2_CIPHER_MODE_XTS;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

/**
 * spu2_cipher_xlate() - Convert a cipher अणुalg/mode/typeपूर्ण triple to a SPU2
 * cipher type and mode.
 * @cipher_alg:  [in]  cipher algorithm value from software क्रमागतeration
 * @cipher_mode: [in]  cipher mode value from software क्रमागतeration
 * @cipher_type: [in]  cipher type value from software क्रमागतeration
 * @spu2_type:   [out] cipher type value used by spu2 hardware
 * @spu2_mode:   [out] cipher mode value used by spu2 hardware
 *
 * Return:  0 अगर successful
 */
अटल पूर्णांक spu2_cipher_xlate(क्रमागत spu_cipher_alg cipher_alg,
			     क्रमागत spu_cipher_mode cipher_mode,
			     क्रमागत spu_cipher_type cipher_type,
			     क्रमागत spu2_cipher_type *spu2_type,
			     क्रमागत spu2_cipher_mode *spu2_mode)
अणु
	पूर्णांक err;

	err = spu2_cipher_mode_xlate(cipher_mode, spu2_mode);
	अगर (err) अणु
		flow_log("Invalid cipher mode %d\n", cipher_mode);
		वापस err;
	पूर्ण

	चयन (cipher_alg) अणु
	हाल CIPHER_ALG_NONE:
		*spu2_type = SPU2_CIPHER_TYPE_NONE;
		अवरोध;
	हाल CIPHER_ALG_RC4:
		/* SPU2 करोes not support RC4 */
		err = -EINVAL;
		*spu2_type = SPU2_CIPHER_TYPE_NONE;
		अवरोध;
	हाल CIPHER_ALG_DES:
		*spu2_type = SPU2_CIPHER_TYPE_DES;
		अवरोध;
	हाल CIPHER_ALG_3DES:
		*spu2_type = SPU2_CIPHER_TYPE_3DES;
		अवरोध;
	हाल CIPHER_ALG_AES:
		चयन (cipher_type) अणु
		हाल CIPHER_TYPE_AES128:
			*spu2_type = SPU2_CIPHER_TYPE_AES128;
			अवरोध;
		हाल CIPHER_TYPE_AES192:
			*spu2_type = SPU2_CIPHER_TYPE_AES192;
			अवरोध;
		हाल CIPHER_TYPE_AES256:
			*spu2_type = SPU2_CIPHER_TYPE_AES256;
			अवरोध;
		शेष:
			err = -EINVAL;
		पूर्ण
		अवरोध;
	हाल CIPHER_ALG_LAST:
	शेष:
		err = -EINVAL;
		अवरोध;
	पूर्ण

	अगर (err)
		flow_log("Invalid cipher alg %d or type %d\n",
			 cipher_alg, cipher_type);
	वापस err;
पूर्ण

/*
 * Convert from a software hash mode value to the corresponding value
 * क्रम SPU2. Note that HASH_MODE_NONE and HASH_MODE_XCBC have the same value.
 */
अटल पूर्णांक spu2_hash_mode_xlate(क्रमागत hash_mode hash_mode,
				क्रमागत spu2_hash_mode *spu2_mode)
अणु
	चयन (hash_mode) अणु
	हाल HASH_MODE_XCBC:
		*spu2_mode = SPU2_HASH_MODE_XCBC_MAC;
		अवरोध;
	हाल HASH_MODE_CMAC:
		*spu2_mode = SPU2_HASH_MODE_CMAC;
		अवरोध;
	हाल HASH_MODE_HMAC:
		*spu2_mode = SPU2_HASH_MODE_HMAC;
		अवरोध;
	हाल HASH_MODE_CCM:
		*spu2_mode = SPU2_HASH_MODE_CCM;
		अवरोध;
	हाल HASH_MODE_GCM:
		*spu2_mode = SPU2_HASH_MODE_GCM;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

/**
 * spu2_hash_xlate() - Convert a hash अणुalg/mode/typeपूर्ण triple to a SPU2 hash type
 * and mode.
 * @hash_alg:  [in] hash algorithm value from software क्रमागतeration
 * @hash_mode: [in] hash mode value from software क्रमागतeration
 * @hash_type: [in] hash type value from software क्रमागतeration
 * @ciph_type: [in] cipher type value from software क्रमागतeration
 * @spu2_type: [out] hash type value used by SPU2 hardware
 * @spu2_mode: [out] hash mode value used by SPU2 hardware
 *
 * Return:  0 अगर successful
 */
अटल पूर्णांक
spu2_hash_xlate(क्रमागत hash_alg hash_alg, क्रमागत hash_mode hash_mode,
		क्रमागत hash_type hash_type, क्रमागत spu_cipher_type ciph_type,
		क्रमागत spu2_hash_type *spu2_type, क्रमागत spu2_hash_mode *spu2_mode)
अणु
	पूर्णांक err;

	err = spu2_hash_mode_xlate(hash_mode, spu2_mode);
	अगर (err) अणु
		flow_log("Invalid hash mode %d\n", hash_mode);
		वापस err;
	पूर्ण

	चयन (hash_alg) अणु
	हाल HASH_ALG_NONE:
		*spu2_type = SPU2_HASH_TYPE_NONE;
		अवरोध;
	हाल HASH_ALG_MD5:
		*spu2_type = SPU2_HASH_TYPE_MD5;
		अवरोध;
	हाल HASH_ALG_SHA1:
		*spu2_type = SPU2_HASH_TYPE_SHA1;
		अवरोध;
	हाल HASH_ALG_SHA224:
		*spu2_type = SPU2_HASH_TYPE_SHA224;
		अवरोध;
	हाल HASH_ALG_SHA256:
		*spu2_type = SPU2_HASH_TYPE_SHA256;
		अवरोध;
	हाल HASH_ALG_SHA384:
		*spu2_type = SPU2_HASH_TYPE_SHA384;
		अवरोध;
	हाल HASH_ALG_SHA512:
		*spu2_type = SPU2_HASH_TYPE_SHA512;
		अवरोध;
	हाल HASH_ALG_AES:
		चयन (ciph_type) अणु
		हाल CIPHER_TYPE_AES128:
			*spu2_type = SPU2_HASH_TYPE_AES128;
			अवरोध;
		हाल CIPHER_TYPE_AES192:
			*spu2_type = SPU2_HASH_TYPE_AES192;
			अवरोध;
		हाल CIPHER_TYPE_AES256:
			*spu2_type = SPU2_HASH_TYPE_AES256;
			अवरोध;
		शेष:
			err = -EINVAL;
		पूर्ण
		अवरोध;
	हाल HASH_ALG_SHA3_224:
		*spu2_type = SPU2_HASH_TYPE_SHA3_224;
		अवरोध;
	हाल HASH_ALG_SHA3_256:
		*spu2_type = SPU2_HASH_TYPE_SHA3_256;
		अवरोध;
	हाल HASH_ALG_SHA3_384:
		*spu2_type = SPU2_HASH_TYPE_SHA3_384;
		अवरोध;
	हाल HASH_ALG_SHA3_512:
		*spu2_type = SPU2_HASH_TYPE_SHA3_512;
		अवरोध;
	हाल HASH_ALG_LAST:
	शेष:
		err = -EINVAL;
		अवरोध;
	पूर्ण

	अगर (err)
		flow_log("Invalid hash alg %d or type %d\n",
			 hash_alg, hash_type);
	वापस err;
पूर्ण

/* Dump FMD ctrl0. The ctrl0 input is in host byte order */
अटल व्योम spu2_dump_fmd_ctrl0(u64 ctrl0)
अणु
	क्रमागत spu2_cipher_type ciph_type;
	क्रमागत spu2_cipher_mode ciph_mode;
	क्रमागत spu2_hash_type hash_type;
	क्रमागत spu2_hash_mode hash_mode;
	अक्षर *ciph_name;
	अक्षर *ciph_mode_name;
	अक्षर *hash_name;
	अक्षर *hash_mode_name;
	u8 cfb;
	u8 proto;

	packet_log(" FMD CTRL0 %#16llx\n", ctrl0);
	अगर (ctrl0 & SPU2_CIPH_ENCRYPT_EN)
		packet_log("  encrypt\n");
	अन्यथा
		packet_log("  decrypt\n");

	ciph_type = (ctrl0 & SPU2_CIPH_TYPE) >> SPU2_CIPH_TYPE_SHIFT;
	ciph_name = spu2_ciph_type_name(ciph_type);
	packet_log("  Cipher type: %s\n", ciph_name);

	अगर (ciph_type != SPU2_CIPHER_TYPE_NONE) अणु
		ciph_mode = (ctrl0 & SPU2_CIPH_MODE) >> SPU2_CIPH_MODE_SHIFT;
		ciph_mode_name = spu2_ciph_mode_name(ciph_mode);
		packet_log("  Cipher mode: %s\n", ciph_mode_name);
	पूर्ण

	cfb = (ctrl0 & SPU2_CFB_MASK) >> SPU2_CFB_MASK_SHIFT;
	packet_log("  CFB %#x\n", cfb);

	proto = (ctrl0 & SPU2_PROTO_SEL) >> SPU2_PROTO_SEL_SHIFT;
	packet_log("  protocol %#x\n", proto);

	अगर (ctrl0 & SPU2_HASH_FIRST)
		packet_log("  hash first\n");
	अन्यथा
		packet_log("  cipher first\n");

	अगर (ctrl0 & SPU2_CHK_TAG)
		packet_log("  check tag\n");

	hash_type = (ctrl0 & SPU2_HASH_TYPE) >> SPU2_HASH_TYPE_SHIFT;
	hash_name = spu2_hash_type_name(hash_type);
	packet_log("  Hash type: %s\n", hash_name);

	अगर (hash_type != SPU2_HASH_TYPE_NONE) अणु
		hash_mode = (ctrl0 & SPU2_HASH_MODE) >> SPU2_HASH_MODE_SHIFT;
		hash_mode_name = spu2_hash_mode_name(hash_mode);
		packet_log("  Hash mode: %s\n", hash_mode_name);
	पूर्ण

	अगर (ctrl0 & SPU2_CIPH_PAD_EN) अणु
		packet_log("  Cipher pad: %#2llx\n",
			   (ctrl0 & SPU2_CIPH_PAD) >> SPU2_CIPH_PAD_SHIFT);
	पूर्ण
पूर्ण

/* Dump FMD ctrl1. The ctrl1 input is in host byte order */
अटल व्योम spu2_dump_fmd_ctrl1(u64 ctrl1)
अणु
	u8 hash_key_len;
	u8 ciph_key_len;
	u8 ret_iv_len;
	u8 iv_offset;
	u8 iv_len;
	u8 hash_tag_len;
	u8 ret_md;

	packet_log(" FMD CTRL1 %#16llx\n", ctrl1);
	अगर (ctrl1 & SPU2_TAG_LOC)
		packet_log("  Tag after payload\n");

	packet_log("  Msg includes ");
	अगर (ctrl1 & SPU2_HAS_FR_DATA)
		packet_log("FD ");
	अगर (ctrl1 & SPU2_HAS_AAD1)
		packet_log("AAD1 ");
	अगर (ctrl1 & SPU2_HAS_NAAD)
		packet_log("NAAD ");
	अगर (ctrl1 & SPU2_HAS_AAD2)
		packet_log("AAD2 ");
	अगर (ctrl1 & SPU2_HAS_ESN)
		packet_log("ESN ");
	packet_log("\n");

	hash_key_len = (ctrl1 & SPU2_HASH_KEY_LEN) >> SPU2_HASH_KEY_LEN_SHIFT;
	packet_log("  Hash key len %u\n", hash_key_len);

	ciph_key_len = (ctrl1 & SPU2_CIPH_KEY_LEN) >> SPU2_CIPH_KEY_LEN_SHIFT;
	packet_log("  Cipher key len %u\n", ciph_key_len);

	अगर (ctrl1 & SPU2_GENIV)
		packet_log("  Generate IV\n");

	अगर (ctrl1 & SPU2_HASH_IV)
		packet_log("  IV included in hash\n");

	अगर (ctrl1 & SPU2_RET_IV)
		packet_log("  Return IV in output before payload\n");

	ret_iv_len = (ctrl1 & SPU2_RET_IV_LEN) >> SPU2_RET_IV_LEN_SHIFT;
	packet_log("  Length of returned IV %u bytes\n",
		   ret_iv_len ? ret_iv_len : 16);

	iv_offset = (ctrl1 & SPU2_IV_OFFSET) >> SPU2_IV_OFFSET_SHIFT;
	packet_log("  IV offset %u\n", iv_offset);

	iv_len = (ctrl1 & SPU2_IV_LEN) >> SPU2_IV_LEN_SHIFT;
	packet_log("  Input IV len %u bytes\n", iv_len);

	hash_tag_len = (ctrl1 & SPU2_HASH_TAG_LEN) >> SPU2_HASH_TAG_LEN_SHIFT;
	packet_log("  Hash tag length %u bytes\n", hash_tag_len);

	packet_log("  Return ");
	ret_md = (ctrl1 & SPU2_RETURN_MD) >> SPU2_RETURN_MD_SHIFT;
	अगर (ret_md)
		packet_log("FMD ");
	अगर (ret_md == SPU2_RET_FMD_OMD)
		packet_log("OMD ");
	अन्यथा अगर (ret_md == SPU2_RET_FMD_OMD_IV)
		packet_log("OMD IV ");
	अगर (ctrl1 & SPU2_RETURN_FD)
		packet_log("FD ");
	अगर (ctrl1 & SPU2_RETURN_AAD1)
		packet_log("AAD1 ");
	अगर (ctrl1 & SPU2_RETURN_NAAD)
		packet_log("NAAD ");
	अगर (ctrl1 & SPU2_RETURN_AAD2)
		packet_log("AAD2 ");
	अगर (ctrl1 & SPU2_RETURN_PAY)
		packet_log("Payload");
	packet_log("\n");
पूर्ण

/* Dump FMD ctrl2. The ctrl2 input is in host byte order */
अटल व्योम spu2_dump_fmd_ctrl2(u64 ctrl2)
अणु
	packet_log(" FMD CTRL2 %#16llx\n", ctrl2);

	packet_log("  AAD1 offset %llu length %llu bytes\n",
		   ctrl2 & SPU2_AAD1_OFFSET,
		   (ctrl2 & SPU2_AAD1_LEN) >> SPU2_AAD1_LEN_SHIFT);
	packet_log("  AAD2 offset %llu\n",
		   (ctrl2 & SPU2_AAD2_OFFSET) >> SPU2_AAD2_OFFSET_SHIFT);
	packet_log("  Payload offset %llu\n",
		   (ctrl2 & SPU2_PL_OFFSET) >> SPU2_PL_OFFSET_SHIFT);
पूर्ण

/* Dump FMD ctrl3. The ctrl3 input is in host byte order */
अटल व्योम spu2_dump_fmd_ctrl3(u64 ctrl3)
अणु
	packet_log(" FMD CTRL3 %#16llx\n", ctrl3);

	packet_log("  Payload length %llu bytes\n", ctrl3 & SPU2_PL_LEN);
	packet_log("  TLS length %llu bytes\n",
		   (ctrl3 & SPU2_TLS_LEN) >> SPU2_TLS_LEN_SHIFT);
पूर्ण

अटल व्योम spu2_dump_fmd(काष्ठा SPU2_FMD *fmd)
अणु
	spu2_dump_fmd_ctrl0(le64_to_cpu(fmd->ctrl0));
	spu2_dump_fmd_ctrl1(le64_to_cpu(fmd->ctrl1));
	spu2_dump_fmd_ctrl2(le64_to_cpu(fmd->ctrl2));
	spu2_dump_fmd_ctrl3(le64_to_cpu(fmd->ctrl3));
पूर्ण

अटल व्योम spu2_dump_omd(u8 *omd, u16 hash_key_len, u16 ciph_key_len,
			  u16 hash_iv_len, u16 ciph_iv_len)
अणु
	u8 *ptr = omd;

	packet_log(" OMD:\n");

	अगर (hash_key_len) अणु
		packet_log("  Hash Key Length %u bytes\n", hash_key_len);
		packet_dump("  KEY: ", ptr, hash_key_len);
		ptr += hash_key_len;
	पूर्ण

	अगर (ciph_key_len) अणु
		packet_log("  Cipher Key Length %u bytes\n", ciph_key_len);
		packet_dump("  KEY: ", ptr, ciph_key_len);
		ptr += ciph_key_len;
	पूर्ण

	अगर (hash_iv_len) अणु
		packet_log("  Hash IV Length %u bytes\n", hash_iv_len);
		packet_dump("  hash IV: ", ptr, hash_iv_len);
		ptr += ciph_key_len;
	पूर्ण

	अगर (ciph_iv_len) अणु
		packet_log("  Cipher IV Length %u bytes\n", ciph_iv_len);
		packet_dump("  cipher IV: ", ptr, ciph_iv_len);
	पूर्ण
पूर्ण

/* Dump a SPU2 header क्रम debug */
व्योम spu2_dump_msg_hdr(u8 *buf, अचिन्हित पूर्णांक buf_len)
अणु
	काष्ठा SPU2_FMD *fmd = (काष्ठा SPU2_FMD *)buf;
	u8 *omd;
	u64 ctrl1;
	u16 hash_key_len;
	u16 ciph_key_len;
	u16 hash_iv_len;
	u16 ciph_iv_len;
	u16 omd_len;

	packet_log("\n");
	packet_log("SPU2 message header %p len: %u\n", buf, buf_len);

	spu2_dump_fmd(fmd);
	omd = (u8 *)(fmd + 1);

	ctrl1 = le64_to_cpu(fmd->ctrl1);
	hash_key_len = (ctrl1 & SPU2_HASH_KEY_LEN) >> SPU2_HASH_KEY_LEN_SHIFT;
	ciph_key_len = (ctrl1 & SPU2_CIPH_KEY_LEN) >> SPU2_CIPH_KEY_LEN_SHIFT;
	hash_iv_len = 0;
	ciph_iv_len = (ctrl1 & SPU2_IV_LEN) >> SPU2_IV_LEN_SHIFT;
	spu2_dump_omd(omd, hash_key_len, ciph_key_len, hash_iv_len,
		      ciph_iv_len);

	/* Double check sanity */
	omd_len = hash_key_len + ciph_key_len + hash_iv_len + ciph_iv_len;
	अगर (FMD_SIZE + omd_len != buf_len) अणु
		packet_log
		    (" Packet parsed incorrectly. buf_len %u, sum of MD %zu\n",
		     buf_len, FMD_SIZE + omd_len);
	पूर्ण
	packet_log("\n");
पूर्ण

/**
 * spu2_fmd_init() - At setkey समय, initialize the fixed meta data क्रम
 * subsequent skcipher requests क्रम this context.
 * @fmd:               Start of FMD field to be written
 * @spu2_type:         Cipher algorithm
 * @spu2_mode:         Cipher mode
 * @cipher_key_len:    Length of cipher key, in bytes
 * @cipher_iv_len:     Length of cipher initialization vector, in bytes
 *
 * Return:  0 (success)
 */
अटल पूर्णांक spu2_fmd_init(काष्ठा SPU2_FMD *fmd,
			 क्रमागत spu2_cipher_type spu2_type,
			 क्रमागत spu2_cipher_mode spu2_mode,
			 u32 cipher_key_len, u32 cipher_iv_len)
अणु
	u64 ctrl0;
	u64 ctrl1;
	u64 ctrl2;
	u64 ctrl3;
	u32 aad1_offset;
	u32 aad2_offset;
	u16 aad1_len = 0;
	u64 payload_offset;

	ctrl0 = (spu2_type << SPU2_CIPH_TYPE_SHIFT) |
	    (spu2_mode << SPU2_CIPH_MODE_SHIFT);

	ctrl1 = (cipher_key_len << SPU2_CIPH_KEY_LEN_SHIFT) |
	    ((u64)cipher_iv_len << SPU2_IV_LEN_SHIFT) |
	    ((u64)SPU2_RET_FMD_ONLY << SPU2_RETURN_MD_SHIFT) | SPU2_RETURN_PAY;

	/*
	 * AAD1 offset is from start of FD. FD length is always 0 क्रम this
	 * driver. So AAD1_offset is always 0.
	 */
	aad1_offset = 0;
	aad2_offset = aad1_offset;
	payload_offset = 0;
	ctrl2 = aad1_offset |
	    (aad1_len << SPU2_AAD1_LEN_SHIFT) |
	    (aad2_offset << SPU2_AAD2_OFFSET_SHIFT) |
	    (payload_offset << SPU2_PL_OFFSET_SHIFT);

	ctrl3 = 0;

	fmd->ctrl0 = cpu_to_le64(ctrl0);
	fmd->ctrl1 = cpu_to_le64(ctrl1);
	fmd->ctrl2 = cpu_to_le64(ctrl2);
	fmd->ctrl3 = cpu_to_le64(ctrl3);

	वापस 0;
पूर्ण

/**
 * spu2_fmd_ctrl0_ग_लिखो() - Write ctrl0 field in fixed metadata (FMD) field of
 * SPU request packet.
 * @fmd:            Start of FMD field to be written
 * @is_inbound:     true अगर decrypting. false अगर encrypting.
 * @auth_first:     true अगर alg authenticates beक्रमe encrypting
 * @protocol:       protocol selector
 * @cipher_type:    cipher algorithm
 * @cipher_mode:    cipher mode
 * @auth_type:      authentication type
 * @auth_mode:      authentication mode
 */
अटल व्योम spu2_fmd_ctrl0_ग_लिखो(काष्ठा SPU2_FMD *fmd,
				 bool is_inbound, bool auth_first,
				 क्रमागत spu2_proto_sel protocol,
				 क्रमागत spu2_cipher_type cipher_type,
				 क्रमागत spu2_cipher_mode cipher_mode,
				 क्रमागत spu2_hash_type auth_type,
				 क्रमागत spu2_hash_mode auth_mode)
अणु
	u64 ctrl0 = 0;

	अगर ((cipher_type != SPU2_CIPHER_TYPE_NONE) && !is_inbound)
		ctrl0 |= SPU2_CIPH_ENCRYPT_EN;

	ctrl0 |= ((u64)cipher_type << SPU2_CIPH_TYPE_SHIFT) |
	    ((u64)cipher_mode << SPU2_CIPH_MODE_SHIFT);

	अगर (protocol)
		ctrl0 |= (u64)protocol << SPU2_PROTO_SEL_SHIFT;

	अगर (auth_first)
		ctrl0 |= SPU2_HASH_FIRST;

	अगर (is_inbound && (auth_type != SPU2_HASH_TYPE_NONE))
		ctrl0 |= SPU2_CHK_TAG;

	ctrl0 |= (((u64)auth_type << SPU2_HASH_TYPE_SHIFT) |
		  ((u64)auth_mode << SPU2_HASH_MODE_SHIFT));

	fmd->ctrl0 = cpu_to_le64(ctrl0);
पूर्ण

/**
 * spu2_fmd_ctrl1_ग_लिखो() - Write ctrl1 field in fixed metadata (FMD) field of
 * SPU request packet.
 * @fmd:            Start of FMD field to be written
 * @is_inbound:     true अगर decrypting. false अगर encrypting.
 * @assoc_size:     Length of additional associated data, in bytes
 * @auth_key_len:   Length of authentication key, in bytes
 * @cipher_key_len: Length of cipher key, in bytes
 * @gen_iv:         If true, hw generates IV and वापसs in response
 * @hash_iv:        IV participates in hash. Used क्रम IPSEC and TLS.
 * @वापस_iv:      Return IV in output packet beक्रमe payload
 * @ret_iv_len:     Length of IV वापसed from SPU, in bytes
 * @ret_iv_offset:  Offset पूर्णांकo full IV of start of वापसed IV
 * @cipher_iv_len:  Length of input cipher IV, in bytes
 * @digest_size:    Length of digest (aka, hash tag or ICV), in bytes
 * @वापस_payload: Return payload in SPU response
 * @वापस_md : वापस metadata in SPU response
 *
 * Packet can have AAD2 w/o AAD1. For algorithms currently supported,
 * associated data goes in AAD2.
 */
अटल व्योम spu2_fmd_ctrl1_ग_लिखो(काष्ठा SPU2_FMD *fmd, bool is_inbound,
				 u64 assoc_size,
				 u64 auth_key_len, u64 cipher_key_len,
				 bool gen_iv, bool hash_iv, bool वापस_iv,
				 u64 ret_iv_len, u64 ret_iv_offset,
				 u64 cipher_iv_len, u64 digest_size,
				 bool वापस_payload, bool वापस_md)
अणु
	u64 ctrl1 = 0;

	अगर (is_inbound && digest_size)
		ctrl1 |= SPU2_TAG_LOC;

	अगर (assoc_size) अणु
		ctrl1 |= SPU2_HAS_AAD2;
		ctrl1 |= SPU2_RETURN_AAD2;  /* need aad2 क्रम gcm aes esp */
	पूर्ण

	अगर (auth_key_len)
		ctrl1 |= ((auth_key_len << SPU2_HASH_KEY_LEN_SHIFT) &
			  SPU2_HASH_KEY_LEN);

	अगर (cipher_key_len)
		ctrl1 |= ((cipher_key_len << SPU2_CIPH_KEY_LEN_SHIFT) &
			  SPU2_CIPH_KEY_LEN);

	अगर (gen_iv)
		ctrl1 |= SPU2_GENIV;

	अगर (hash_iv)
		ctrl1 |= SPU2_HASH_IV;

	अगर (वापस_iv) अणु
		ctrl1 |= SPU2_RET_IV;
		ctrl1 |= ret_iv_len << SPU2_RET_IV_LEN_SHIFT;
		ctrl1 |= ret_iv_offset << SPU2_IV_OFFSET_SHIFT;
	पूर्ण

	ctrl1 |= ((cipher_iv_len << SPU2_IV_LEN_SHIFT) & SPU2_IV_LEN);

	अगर (digest_size)
		ctrl1 |= ((digest_size << SPU2_HASH_TAG_LEN_SHIFT) &
			  SPU2_HASH_TAG_LEN);

	/* Let's ask for the output pkt to include FMD, but don't need to
	 * get keys and IVs back in OMD.
	 */
	अगर (वापस_md)
		ctrl1 |= ((u64)SPU2_RET_FMD_ONLY << SPU2_RETURN_MD_SHIFT);
	अन्यथा
		ctrl1 |= ((u64)SPU2_RET_NO_MD << SPU2_RETURN_MD_SHIFT);

	/* Crypto API करोes not get assoc data back. So no need क्रम AAD2. */

	अगर (वापस_payload)
		ctrl1 |= SPU2_RETURN_PAY;

	fmd->ctrl1 = cpu_to_le64(ctrl1);
पूर्ण

/**
 * spu2_fmd_ctrl2_ग_लिखो() - Set the ctrl2 field in the fixed metadata field of
 * SPU2 header.
 * @fmd:            Start of FMD field to be written
 * @cipher_offset:  Number of bytes from Start of Packet (end of FD field) where
 *                  data to be encrypted or decrypted begins
 * @auth_key_len:   Length of authentication key, in bytes
 * @auth_iv_len:    Length of authentication initialization vector, in bytes
 * @cipher_key_len: Length of cipher key, in bytes
 * @cipher_iv_len:  Length of cipher IV, in bytes
 */
अटल व्योम spu2_fmd_ctrl2_ग_लिखो(काष्ठा SPU2_FMD *fmd, u64 cipher_offset,
				 u64 auth_key_len, u64 auth_iv_len,
				 u64 cipher_key_len, u64 cipher_iv_len)
अणु
	u64 ctrl2;
	u64 aad1_offset;
	u64 aad2_offset;
	u16 aad1_len = 0;
	u64 payload_offset;

	/* AAD1 offset is from start of FD. FD length always 0. */
	aad1_offset = 0;

	aad2_offset = aad1_offset;
	payload_offset = cipher_offset;
	ctrl2 = aad1_offset |
	    (aad1_len << SPU2_AAD1_LEN_SHIFT) |
	    (aad2_offset << SPU2_AAD2_OFFSET_SHIFT) |
	    (payload_offset << SPU2_PL_OFFSET_SHIFT);

	fmd->ctrl2 = cpu_to_le64(ctrl2);
पूर्ण

/**
 * spu2_fmd_ctrl3_ग_लिखो() - Set the ctrl3 field in FMD
 * @fmd:          Fixed meta data. First field in SPU2 msg header.
 * @payload_len:  Length of payload, in bytes
 */
अटल व्योम spu2_fmd_ctrl3_ग_लिखो(काष्ठा SPU2_FMD *fmd, u64 payload_len)
अणु
	u64 ctrl3;

	ctrl3 = payload_len & SPU2_PL_LEN;

	fmd->ctrl3 = cpu_to_le64(ctrl3);
पूर्ण

/**
 * spu2_ctx_max_payload() - Determine the maximum length of the payload क्रम a
 * SPU message क्रम a given cipher and hash alg context.
 * @cipher_alg:		The cipher algorithm
 * @cipher_mode:	The cipher mode
 * @blocksize:		The size of a block of data क्रम this algo
 *
 * For SPU2, the hardware generally ignores the PayloadLen field in ctrl3 of
 * FMD and just keeps computing until it receives a DMA descriptor with the खातापूर्ण
 * flag set. So we consider the max payload to be infinite. AES CCM is an
 * exception.
 *
 * Return: Max payload length in bytes
 */
u32 spu2_ctx_max_payload(क्रमागत spu_cipher_alg cipher_alg,
			 क्रमागत spu_cipher_mode cipher_mode,
			 अचिन्हित पूर्णांक blocksize)
अणु
	अगर ((cipher_alg == CIPHER_ALG_AES) &&
	    (cipher_mode == CIPHER_MODE_CCM)) अणु
		u32 excess = SPU2_MAX_PAYLOAD % blocksize;

		वापस SPU2_MAX_PAYLOAD - excess;
	पूर्ण अन्यथा अणु
		वापस SPU_MAX_PAYLOAD_INF;
	पूर्ण
पूर्ण

/**
 * spu2_payload_length() -  Given a SPU2 message header, extract the payload
 * length.
 * @spu_hdr:  Start of SPU message header (FMD)
 *
 * Return: payload length, in bytes
 */
u32 spu2_payload_length(u8 *spu_hdr)
अणु
	काष्ठा SPU2_FMD *fmd = (काष्ठा SPU2_FMD *)spu_hdr;
	u32 pl_len;
	u64 ctrl3;

	ctrl3 = le64_to_cpu(fmd->ctrl3);
	pl_len = ctrl3 & SPU2_PL_LEN;

	वापस pl_len;
पूर्ण

/**
 * spu2_response_hdr_len() - Determine the expected length of a SPU response
 * header.
 * @auth_key_len:  Length of authentication key, in bytes
 * @enc_key_len:   Length of encryption key, in bytes
 * @is_hash:       Unused
 *
 * For SPU2, includes just FMD. OMD is never requested.
 *
 * Return: Length of FMD, in bytes
 */
u16 spu2_response_hdr_len(u16 auth_key_len, u16 enc_key_len, bool is_hash)
अणु
	वापस FMD_SIZE;
पूर्ण

/**
 * spu2_hash_pad_len() - Calculate the length of hash padding required to extend
 * data to a full block size.
 * @hash_alg:        hash algorithm
 * @hash_mode:       hash mode
 * @chunksize:       length of data, in bytes
 * @hash_block_size: size of a hash block, in bytes
 *
 * SPU2 hardware करोes all hash padding
 *
 * Return:  length of hash pad in bytes
 */
u16 spu2_hash_pad_len(क्रमागत hash_alg hash_alg, क्रमागत hash_mode hash_mode,
		      u32 chunksize, u16 hash_block_size)
अणु
	वापस 0;
पूर्ण

/**
 * spu2_gcm_ccm_pad_len() -  Determine the length of GCM/CCM padding क्रम either
 * the AAD field or the data.
 * @cipher_mode:  Unused
 * @data_size:    Unused
 *
 * Return:  0. Unlike SPU-M, SPU2 hardware करोes any GCM/CCM padding required.
 */
u32 spu2_gcm_ccm_pad_len(क्रमागत spu_cipher_mode cipher_mode,
			 अचिन्हित पूर्णांक data_size)
अणु
	वापस 0;
पूर्ण

/**
 * spu2_assoc_resp_len() - Determine the size of the AAD2 buffer needed to catch
 * associated data in a SPU2 output packet.
 * @cipher_mode:   cipher mode
 * @assoc_len:     length of additional associated data, in bytes
 * @iv_len:        length of initialization vector, in bytes
 * @is_encrypt:    true अगर encrypting. false अगर decrypt.
 *
 * Return: Length of buffer to catch associated data in response
 */
u32 spu2_assoc_resp_len(क्रमागत spu_cipher_mode cipher_mode,
			अचिन्हित पूर्णांक assoc_len, अचिन्हित पूर्णांक iv_len,
			bool is_encrypt)
अणु
	u32 resp_len = assoc_len;

	अगर (is_encrypt)
		/* gcm aes esp has to ग_लिखो 8-byte IV in response */
		resp_len += iv_len;
	वापस resp_len;
पूर्ण

/**
 * spu2_aead_ivlen() - Calculate the length of the AEAD IV to be included
 * in a SPU request after the AAD and beक्रमe the payload.
 * @cipher_mode:  cipher mode
 * @iv_len:   initialization vector length in bytes
 *
 * For SPU2, AEAD IV is included in OMD and करोes not need to be repeated
 * prior to the payload.
 *
 * Return: Length of AEAD IV in bytes
 */
u8 spu2_aead_ivlen(क्रमागत spu_cipher_mode cipher_mode, u16 iv_len)
अणु
	वापस 0;
पूर्ण

/**
 * spu2_hash_type() - Determine the type of hash operation.
 * @src_sent:  The number of bytes in the current request that have alपढ़ोy
 *             been sent to the SPU to be hashed.
 *
 * SPU2 always करोes a FULL hash operation
 */
क्रमागत hash_type spu2_hash_type(u32 src_sent)
अणु
	वापस HASH_TYPE_FULL;
पूर्ण

/**
 * spu2_digest_size() - Determine the size of a hash digest to expect the SPU to
 * वापस.
 * @alg_digest_size: Number of bytes in the final digest क्रम the given algo
 * @alg:             The hash algorithm
 * @htype:           Type of hash operation (init, update, full, etc)
 *
 */
u32 spu2_digest_size(u32 alg_digest_size, क्रमागत hash_alg alg,
		     क्रमागत hash_type htype)
अणु
	वापस alg_digest_size;
पूर्ण

/**
 * spu2_create_request() - Build a SPU2 request message header, includपूर्णांक FMD and
 * OMD.
 * @spu_hdr: Start of buffer where SPU request header is to be written
 * @req_opts: SPU request message options
 * @cipher_parms: Parameters related to cipher algorithm
 * @hash_parms:   Parameters related to hash algorithm
 * @aead_parms:   Parameters related to AEAD operation
 * @data_size:    Length of data to be encrypted or authenticated. If AEAD, करोes
 *		  not include length of AAD.
 *
 * Conकाष्ठा the message starting at spu_hdr. Caller should allocate this buffer
 * in DMA-able memory at least SPU_HEADER_ALLOC_LEN bytes दीर्घ.
 *
 * Return: the length of the SPU header in bytes. 0 अगर an error occurs.
 */
u32 spu2_create_request(u8 *spu_hdr,
			काष्ठा spu_request_opts *req_opts,
			काष्ठा spu_cipher_parms *cipher_parms,
			काष्ठा spu_hash_parms *hash_parms,
			काष्ठा spu_aead_parms *aead_parms,
			अचिन्हित पूर्णांक data_size)
अणु
	काष्ठा SPU2_FMD *fmd;
	u8 *ptr;
	अचिन्हित पूर्णांक buf_len;
	पूर्णांक err;
	क्रमागत spu2_cipher_type spu2_ciph_type = SPU2_CIPHER_TYPE_NONE;
	क्रमागत spu2_cipher_mode spu2_ciph_mode;
	क्रमागत spu2_hash_type spu2_auth_type = SPU2_HASH_TYPE_NONE;
	क्रमागत spu2_hash_mode spu2_auth_mode;
	bool वापस_md = true;
	क्रमागत spu2_proto_sel proto = SPU2_PROTO_RESV;

	/* size of the payload */
	अचिन्हित पूर्णांक payload_len =
	    hash_parms->prebuf_len + data_size + hash_parms->pad_len -
	    ((req_opts->is_aead && req_opts->is_inbound) ?
	     hash_parms->digestsize : 0);

	/* offset of prebuf or data from start of AAD2 */
	अचिन्हित पूर्णांक cipher_offset = aead_parms->assoc_size +
			aead_parms->aad_pad_len + aead_parms->iv_len;

	/* total size of the data following OMD (without STAT word padding) */
	अचिन्हित पूर्णांक real_db_size = spu_real_db_size(aead_parms->assoc_size,
						 aead_parms->iv_len,
						 hash_parms->prebuf_len,
						 data_size,
						 aead_parms->aad_pad_len,
						 aead_parms->data_pad_len,
						 hash_parms->pad_len);
	अचिन्हित पूर्णांक assoc_size = aead_parms->assoc_size;

	अगर (req_opts->is_aead &&
	    (cipher_parms->alg == CIPHER_ALG_AES) &&
	    (cipher_parms->mode == CIPHER_MODE_GCM))
		/*
		 * On SPU 2, aes gcm cipher first on encrypt, auth first on
		 * decrypt
		 */
		req_opts->auth_first = req_opts->is_inbound;

	/* and करो opposite क्रम ccm (auth 1st on encrypt) */
	अगर (req_opts->is_aead &&
	    (cipher_parms->alg == CIPHER_ALG_AES) &&
	    (cipher_parms->mode == CIPHER_MODE_CCM))
		req_opts->auth_first = !req_opts->is_inbound;

	flow_log("%s()\n", __func__);
	flow_log("  in:%u authFirst:%u\n",
		 req_opts->is_inbound, req_opts->auth_first);
	flow_log("  cipher alg:%u mode:%u type %u\n", cipher_parms->alg,
		 cipher_parms->mode, cipher_parms->type);
	flow_log("  is_esp: %s\n", req_opts->is_esp ? "yes" : "no");
	flow_log("    key: %d\n", cipher_parms->key_len);
	flow_dump("    key: ", cipher_parms->key_buf, cipher_parms->key_len);
	flow_log("    iv: %d\n", cipher_parms->iv_len);
	flow_dump("    iv: ", cipher_parms->iv_buf, cipher_parms->iv_len);
	flow_log("  auth alg:%u mode:%u type %u\n",
		 hash_parms->alg, hash_parms->mode, hash_parms->type);
	flow_log("  digestsize: %u\n", hash_parms->digestsize);
	flow_log("  authkey: %d\n", hash_parms->key_len);
	flow_dump("  authkey: ", hash_parms->key_buf, hash_parms->key_len);
	flow_log("  assoc_size:%u\n", assoc_size);
	flow_log("  prebuf_len:%u\n", hash_parms->prebuf_len);
	flow_log("  data_size:%u\n", data_size);
	flow_log("  hash_pad_len:%u\n", hash_parms->pad_len);
	flow_log("  real_db_size:%u\n", real_db_size);
	flow_log("  cipher_offset:%u payload_len:%u\n",
		 cipher_offset, payload_len);
	flow_log("  aead_iv: %u\n", aead_parms->iv_len);

	/* Convert to spu2 values क्रम cipher alg, hash alg */
	err = spu2_cipher_xlate(cipher_parms->alg, cipher_parms->mode,
				cipher_parms->type,
				&spu2_ciph_type, &spu2_ciph_mode);

	/* If we are करोing GCM hashing only - either via rfc4543 transक्रमm
	 * or because we happen to करो GCM with AAD only and no payload - we
	 * need to configure hardware to use hash key rather than cipher key
	 * and put data पूर्णांकo payload.  This is because unlike SPU-M, running
	 * GCM cipher with 0 size payload is not permitted.
	 */
	अगर ((req_opts->is_rfc4543) ||
	    ((spu2_ciph_mode == SPU2_CIPHER_MODE_GCM) &&
	    (payload_len == 0))) अणु
		/* Use hashing (only) and set up hash key */
		spu2_ciph_type = SPU2_CIPHER_TYPE_NONE;
		hash_parms->key_len = cipher_parms->key_len;
		स_नकल(hash_parms->key_buf, cipher_parms->key_buf,
		       cipher_parms->key_len);
		cipher_parms->key_len = 0;

		अगर (req_opts->is_rfc4543)
			payload_len += assoc_size;
		अन्यथा
			payload_len = assoc_size;
		cipher_offset = 0;
		assoc_size = 0;
	पूर्ण

	अगर (err)
		वापस 0;

	flow_log("spu2 cipher type %s, cipher mode %s\n",
		 spu2_ciph_type_name(spu2_ciph_type),
		 spu2_ciph_mode_name(spu2_ciph_mode));

	err = spu2_hash_xlate(hash_parms->alg, hash_parms->mode,
			      hash_parms->type,
			      cipher_parms->type,
			      &spu2_auth_type, &spu2_auth_mode);
	अगर (err)
		वापस 0;

	flow_log("spu2 hash type %s, hash mode %s\n",
		 spu2_hash_type_name(spu2_auth_type),
		 spu2_hash_mode_name(spu2_auth_mode));

	fmd = (काष्ठा SPU2_FMD *)spu_hdr;

	spu2_fmd_ctrl0_ग_लिखो(fmd, req_opts->is_inbound, req_opts->auth_first,
			     proto, spu2_ciph_type, spu2_ciph_mode,
			     spu2_auth_type, spu2_auth_mode);

	spu2_fmd_ctrl1_ग_लिखो(fmd, req_opts->is_inbound, assoc_size,
			     hash_parms->key_len, cipher_parms->key_len,
			     false, false,
			     aead_parms->वापस_iv, aead_parms->ret_iv_len,
			     aead_parms->ret_iv_off,
			     cipher_parms->iv_len, hash_parms->digestsize,
			     !req_opts->bd_suppress, वापस_md);

	spu2_fmd_ctrl2_ग_लिखो(fmd, cipher_offset, hash_parms->key_len, 0,
			     cipher_parms->key_len, cipher_parms->iv_len);

	spu2_fmd_ctrl3_ग_लिखो(fmd, payload_len);

	ptr = (u8 *)(fmd + 1);
	buf_len = माप(काष्ठा SPU2_FMD);

	/* Write OMD */
	अगर (hash_parms->key_len) अणु
		स_नकल(ptr, hash_parms->key_buf, hash_parms->key_len);
		ptr += hash_parms->key_len;
		buf_len += hash_parms->key_len;
	पूर्ण
	अगर (cipher_parms->key_len) अणु
		स_नकल(ptr, cipher_parms->key_buf, cipher_parms->key_len);
		ptr += cipher_parms->key_len;
		buf_len += cipher_parms->key_len;
	पूर्ण
	अगर (cipher_parms->iv_len) अणु
		स_नकल(ptr, cipher_parms->iv_buf, cipher_parms->iv_len);
		ptr += cipher_parms->iv_len;
		buf_len += cipher_parms->iv_len;
	पूर्ण

	packet_dump("  SPU request header: ", spu_hdr, buf_len);

	वापस buf_len;
पूर्ण

/**
 * spu2_cipher_req_init() - Build an skcipher SPU2 request message header,
 * including FMD and OMD.
 * @spu_hdr:       Location of start of SPU request (FMD field)
 * @cipher_parms:  Parameters describing cipher request
 *
 * Called at setkey समय to initialize a msg header that can be reused क्रम all
 * subsequent skcipher requests. Conकाष्ठा the message starting at spu_hdr.
 * Caller should allocate this buffer in DMA-able memory at least
 * SPU_HEADER_ALLOC_LEN bytes दीर्घ.
 *
 * Return: the total length of the SPU header (FMD and OMD) in bytes. 0 अगर an
 * error occurs.
 */
u16 spu2_cipher_req_init(u8 *spu_hdr, काष्ठा spu_cipher_parms *cipher_parms)
अणु
	काष्ठा SPU2_FMD *fmd;
	u8 *omd;
	क्रमागत spu2_cipher_type spu2_type = SPU2_CIPHER_TYPE_NONE;
	क्रमागत spu2_cipher_mode spu2_mode;
	पूर्णांक err;

	flow_log("%s()\n", __func__);
	flow_log("  cipher alg:%u mode:%u type %u\n", cipher_parms->alg,
		 cipher_parms->mode, cipher_parms->type);
	flow_log("  cipher_iv_len: %u\n", cipher_parms->iv_len);
	flow_log("    key: %d\n", cipher_parms->key_len);
	flow_dump("    key: ", cipher_parms->key_buf, cipher_parms->key_len);

	/* Convert to spu2 values */
	err = spu2_cipher_xlate(cipher_parms->alg, cipher_parms->mode,
				cipher_parms->type, &spu2_type, &spu2_mode);
	अगर (err)
		वापस 0;

	flow_log("spu2 cipher type %s, cipher mode %s\n",
		 spu2_ciph_type_name(spu2_type),
		 spu2_ciph_mode_name(spu2_mode));

	/* Conकाष्ठा the FMD header */
	fmd = (काष्ठा SPU2_FMD *)spu_hdr;
	err = spu2_fmd_init(fmd, spu2_type, spu2_mode, cipher_parms->key_len,
			    cipher_parms->iv_len);
	अगर (err)
		वापस 0;

	/* Write cipher key to OMD */
	omd = (u8 *)(fmd + 1);
	अगर (cipher_parms->key_buf && cipher_parms->key_len)
		स_नकल(omd, cipher_parms->key_buf, cipher_parms->key_len);

	packet_dump("  SPU request header: ", spu_hdr,
		    FMD_SIZE + cipher_parms->key_len + cipher_parms->iv_len);

	वापस FMD_SIZE + cipher_parms->key_len + cipher_parms->iv_len;
पूर्ण

/**
 * spu2_cipher_req_finish() - Finish building a SPU request message header क्रम a
 * block cipher request.
 * @spu_hdr:         Start of the request message header (MH field)
 * @spu_req_hdr_len: Length in bytes of the SPU request header
 * @is_inbound:      0 encrypt, 1 decrypt
 * @cipher_parms:    Parameters describing cipher operation to be perक्रमmed
 * @data_size:       Length of the data in the BD field
 *
 * Assumes much of the header was alपढ़ोy filled in at setkey() समय in
 * spu_cipher_req_init().
 * spu_cipher_req_init() fills in the encryption key.
 */
व्योम spu2_cipher_req_finish(u8 *spu_hdr,
			    u16 spu_req_hdr_len,
			    अचिन्हित पूर्णांक is_inbound,
			    काष्ठा spu_cipher_parms *cipher_parms,
			    अचिन्हित पूर्णांक data_size)
अणु
	काष्ठा SPU2_FMD *fmd;
	u8 *omd;		/* start of optional metadata */
	u64 ctrl0;
	u64 ctrl3;

	flow_log("%s()\n", __func__);
	flow_log(" in: %u\n", is_inbound);
	flow_log(" cipher alg: %u, cipher_type: %u\n", cipher_parms->alg,
		 cipher_parms->type);
	flow_log(" iv len: %d\n", cipher_parms->iv_len);
	flow_dump("    iv: ", cipher_parms->iv_buf, cipher_parms->iv_len);
	flow_log(" data_size: %u\n", data_size);

	fmd = (काष्ठा SPU2_FMD *)spu_hdr;
	omd = (u8 *)(fmd + 1);

	/*
	 * FMD ctrl0 was initialized at setkey समय. update it to indicate
	 * whether we are encrypting or decrypting.
	 */
	ctrl0 = le64_to_cpu(fmd->ctrl0);
	अगर (is_inbound)
		ctrl0 &= ~SPU2_CIPH_ENCRYPT_EN;	/* decrypt */
	अन्यथा
		ctrl0 |= SPU2_CIPH_ENCRYPT_EN;	/* encrypt */
	fmd->ctrl0 = cpu_to_le64(ctrl0);

	अगर (cipher_parms->alg && cipher_parms->iv_buf && cipher_parms->iv_len) अणु
		/* cipher iv provided so put it in here */
		स_नकल(omd + cipher_parms->key_len, cipher_parms->iv_buf,
		       cipher_parms->iv_len);
	पूर्ण

	ctrl3 = le64_to_cpu(fmd->ctrl3);
	data_size &= SPU2_PL_LEN;
	ctrl3 |= data_size;
	fmd->ctrl3 = cpu_to_le64(ctrl3);

	packet_dump("  SPU request header: ", spu_hdr, spu_req_hdr_len);
पूर्ण

/**
 * spu2_request_pad() - Create pad bytes at the end of the data.
 * @pad_start:      Start of buffer where pad bytes are to be written
 * @gcm_padding:    Length of GCM padding, in bytes
 * @hash_pad_len:   Number of bytes of padding extend data to full block
 * @auth_alg:       Authentication algorithm
 * @auth_mode:      Authentication mode
 * @total_sent:     Length inserted at end of hash pad
 * @status_padding: Number of bytes of padding to align STATUS word
 *
 * There may be three क्रमms of pad:
 *  1. GCM pad - क्रम GCM mode ciphers, pad to 16-byte alignment
 *  2. hash pad - pad to a block length, with 0x80 data terminator and
 *                size at the end
 *  3. STAT pad - to ensure the STAT field is 4-byte aligned
 */
व्योम spu2_request_pad(u8 *pad_start, u32 gcm_padding, u32 hash_pad_len,
		      क्रमागत hash_alg auth_alg, क्रमागत hash_mode auth_mode,
		      अचिन्हित पूर्णांक total_sent, u32 status_padding)
अणु
	u8 *ptr = pad_start;

	/* fix data alignent क्रम GCM */
	अगर (gcm_padding > 0) अणु
		flow_log("  GCM: padding to 16 byte alignment: %u bytes\n",
			 gcm_padding);
		स_रखो(ptr, 0, gcm_padding);
		ptr += gcm_padding;
	पूर्ण

	अगर (hash_pad_len > 0) अणु
		/* clear the padding section */
		स_रखो(ptr, 0, hash_pad_len);

		/* terminate the data */
		*ptr = 0x80;
		ptr += (hash_pad_len - माप(u64));

		/* add the size at the end as required per alg */
		अगर (auth_alg == HASH_ALG_MD5)
			*(__le64 *)ptr = cpu_to_le64(total_sent * 8ull);
		अन्यथा		/* SHA1, SHA2-224, SHA2-256 */
			*(__be64 *)ptr = cpu_to_be64(total_sent * 8ull);
		ptr += माप(u64);
	पूर्ण

	/* pad to a 4byte alignment क्रम STAT */
	अगर (status_padding > 0) अणु
		flow_log("  STAT: padding to 4 byte alignment: %u bytes\n",
			 status_padding);

		स_रखो(ptr, 0, status_padding);
		ptr += status_padding;
	पूर्ण
पूर्ण

/**
 * spu2_xts_tweak_in_payload() - Indicate that SPU2 करोes NOT place the XTS
 * tweak field in the packet payload (it uses IV instead)
 *
 * Return: 0
 */
u8 spu2_xts_tweak_in_payload(व्योम)
अणु
	वापस 0;
पूर्ण

/**
 * spu2_tx_status_len() - Return the length of the STATUS field in a SPU
 * response message.
 *
 * Return: Length of STATUS field in bytes.
 */
u8 spu2_tx_status_len(व्योम)
अणु
	वापस SPU2_TX_STATUS_LEN;
पूर्ण

/**
 * spu2_rx_status_len() - Return the length of the STATUS field in a SPU
 * response message.
 *
 * Return: Length of STATUS field in bytes.
 */
u8 spu2_rx_status_len(व्योम)
अणु
	वापस SPU2_RX_STATUS_LEN;
पूर्ण

/**
 * spu2_status_process() - Process the status from a SPU response message.
 * @statp:  start of STATUS word
 *
 * Return:  0 - अगर status is good and response should be processed
 *         !0 - status indicates an error and response is invalid
 */
पूर्णांक spu2_status_process(u8 *statp)
अणु
	/* SPU2 status is 2 bytes by शेष - SPU_RX_STATUS_LEN */
	u16 status = le16_to_cpu(*(__le16 *)statp);

	अगर (status == 0)
		वापस 0;

	flow_log("rx status is %#x\n", status);
	अगर (status == SPU2_INVALID_ICV)
		वापस SPU_INVALID_ICV;

	वापस -EBADMSG;
पूर्ण

/**
 * spu2_ccm_update_iv() - Update the IV as per the requirements क्रम CCM mode.
 *
 * @digestsize:		Digest size of this request
 * @cipher_parms:	(poपूर्णांकer to) cipher parmaeters, includes IV buf & IV len
 * @assoclen:		Length of AAD data
 * @chunksize:		length of input data to be sent in this req
 * @is_encrypt:		true अगर this is an output/encrypt operation
 * @is_esp:		true अगर this is an ESP / RFC4309 operation
 *
 */
व्योम spu2_ccm_update_iv(अचिन्हित पूर्णांक digestsize,
			काष्ठा spu_cipher_parms *cipher_parms,
			अचिन्हित पूर्णांक assoclen, अचिन्हित पूर्णांक chunksize,
			bool is_encrypt, bool is_esp)
अणु
	पूर्णांक L;  /* size of length field, in bytes */

	/*
	 * In RFC4309 mode, L is fixed at 4 bytes; otherwise, IV from
	 * tesपंचांगgr contains (L-1) in bottom 3 bits of first byte,
	 * per RFC 3610.
	 */
	अगर (is_esp)
		L = CCM_ESP_L_VALUE;
	अन्यथा
		L = ((cipher_parms->iv_buf[0] & CCM_B0_L_PRIME) >>
		      CCM_B0_L_PRIME_SHIFT) + 1;

	/* SPU2 करोesn't want these length bytes nor the first byte... */
	cipher_parms->iv_len -= (1 + L);
	स_हटाओ(cipher_parms->iv_buf, &cipher_parms->iv_buf[1],
		cipher_parms->iv_len);
पूर्ण

/**
 * spu2_wordalign_padlen() - SPU2 करोes not require padding.
 * @data_size: length of data field in bytes
 *
 * Return: length of status field padding, in bytes (always 0 on SPU2)
 */
u32 spu2_wordalign_padlen(u32 data_size)
अणु
	वापस 0;
पूर्ण
