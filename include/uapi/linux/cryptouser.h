<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * Crypto user configuration API.
 *
 * Copyright (C) 2011 secunet Security Networks AG
 * Copyright (C) 2011 Steffen Klनिश्चित <steffen.klनिश्चित@secunet.com>
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License क्रम
 * more details.
 *
 * You should have received a copy of the GNU General Public License aदीर्घ with
 * this program; अगर not, ग_लिखो to the Free Software Foundation, Inc.,
 * 51 Franklin St - Fअगरth Floor, Boston, MA 02110-1301 USA.
 */

#अगर_अघोषित _UAPI_LINUX_CRYPTOUSER_H
#घोषणा _UAPI_LINUX_CRYPTOUSER_H

#समावेश <linux/types.h>

/* Netlink configuration messages.  */
क्रमागत अणु
	CRYPTO_MSG_BASE = 0x10,
	CRYPTO_MSG_NEWALG = 0x10,
	CRYPTO_MSG_DELALG,
	CRYPTO_MSG_UPDATEALG,
	CRYPTO_MSG_GETALG,
	CRYPTO_MSG_DELRNG,
	CRYPTO_MSG_GETSTAT,
	__CRYPTO_MSG_MAX
पूर्ण;
#घोषणा CRYPTO_MSG_MAX (__CRYPTO_MSG_MAX - 1)
#घोषणा CRYPTO_NR_MSGTYPES (CRYPTO_MSG_MAX + 1 - CRYPTO_MSG_BASE)

#घोषणा CRYPTO_MAX_NAME 64

/* Netlink message attributes.  */
क्रमागत crypto_attr_type_t अणु
	CRYPTOCFGA_UNSPEC,
	CRYPTOCFGA_PRIORITY_VAL,	/* __u32 */
	CRYPTOCFGA_REPORT_LARVAL,	/* काष्ठा crypto_report_larval */
	CRYPTOCFGA_REPORT_HASH,		/* काष्ठा crypto_report_hash */
	CRYPTOCFGA_REPORT_BLKCIPHER,	/* काष्ठा crypto_report_blkcipher */
	CRYPTOCFGA_REPORT_AEAD,		/* काष्ठा crypto_report_aead */
	CRYPTOCFGA_REPORT_COMPRESS,	/* काष्ठा crypto_report_comp */
	CRYPTOCFGA_REPORT_RNG,		/* काष्ठा crypto_report_rng */
	CRYPTOCFGA_REPORT_CIPHER,	/* काष्ठा crypto_report_cipher */
	CRYPTOCFGA_REPORT_AKCIPHER,	/* काष्ठा crypto_report_akcipher */
	CRYPTOCFGA_REPORT_KPP,		/* काष्ठा crypto_report_kpp */
	CRYPTOCFGA_REPORT_ACOMP,	/* काष्ठा crypto_report_acomp */
	CRYPTOCFGA_STAT_LARVAL,		/* काष्ठा crypto_stat */
	CRYPTOCFGA_STAT_HASH,		/* काष्ठा crypto_stat */
	CRYPTOCFGA_STAT_BLKCIPHER,	/* काष्ठा crypto_stat */
	CRYPTOCFGA_STAT_AEAD,		/* काष्ठा crypto_stat */
	CRYPTOCFGA_STAT_COMPRESS,	/* काष्ठा crypto_stat */
	CRYPTOCFGA_STAT_RNG,		/* काष्ठा crypto_stat */
	CRYPTOCFGA_STAT_CIPHER,		/* काष्ठा crypto_stat */
	CRYPTOCFGA_STAT_AKCIPHER,	/* काष्ठा crypto_stat */
	CRYPTOCFGA_STAT_KPP,		/* काष्ठा crypto_stat */
	CRYPTOCFGA_STAT_ACOMP,		/* काष्ठा crypto_stat */
	__CRYPTOCFGA_MAX

#घोषणा CRYPTOCFGA_MAX (__CRYPTOCFGA_MAX - 1)
पूर्ण;

काष्ठा crypto_user_alg अणु
	अक्षर cru_name[CRYPTO_MAX_NAME];
	अक्षर cru_driver_name[CRYPTO_MAX_NAME];
	अक्षर cru_module_name[CRYPTO_MAX_NAME];
	__u32 cru_type;
	__u32 cru_mask;
	__u32 cru_refcnt;
	__u32 cru_flags;
पूर्ण;

काष्ठा crypto_stat_aead अणु
	अक्षर type[CRYPTO_MAX_NAME];
	__u64 stat_encrypt_cnt;
	__u64 stat_encrypt_tlen;
	__u64 stat_decrypt_cnt;
	__u64 stat_decrypt_tlen;
	__u64 stat_err_cnt;
पूर्ण;

काष्ठा crypto_stat_akcipher अणु
	अक्षर type[CRYPTO_MAX_NAME];
	__u64 stat_encrypt_cnt;
	__u64 stat_encrypt_tlen;
	__u64 stat_decrypt_cnt;
	__u64 stat_decrypt_tlen;
	__u64 stat_verअगरy_cnt;
	__u64 stat_sign_cnt;
	__u64 stat_err_cnt;
पूर्ण;

काष्ठा crypto_stat_cipher अणु
	अक्षर type[CRYPTO_MAX_NAME];
	__u64 stat_encrypt_cnt;
	__u64 stat_encrypt_tlen;
	__u64 stat_decrypt_cnt;
	__u64 stat_decrypt_tlen;
	__u64 stat_err_cnt;
पूर्ण;

काष्ठा crypto_stat_compress अणु
	अक्षर type[CRYPTO_MAX_NAME];
	__u64 stat_compress_cnt;
	__u64 stat_compress_tlen;
	__u64 stat_decompress_cnt;
	__u64 stat_decompress_tlen;
	__u64 stat_err_cnt;
पूर्ण;

काष्ठा crypto_stat_hash अणु
	अक्षर type[CRYPTO_MAX_NAME];
	__u64 stat_hash_cnt;
	__u64 stat_hash_tlen;
	__u64 stat_err_cnt;
पूर्ण;

काष्ठा crypto_stat_kpp अणु
	अक्षर type[CRYPTO_MAX_NAME];
	__u64 stat_setsecret_cnt;
	__u64 stat_generate_खुला_key_cnt;
	__u64 stat_compute_shared_secret_cnt;
	__u64 stat_err_cnt;
पूर्ण;

काष्ठा crypto_stat_rng अणु
	अक्षर type[CRYPTO_MAX_NAME];
	__u64 stat_generate_cnt;
	__u64 stat_generate_tlen;
	__u64 stat_seed_cnt;
	__u64 stat_err_cnt;
पूर्ण;

काष्ठा crypto_stat_larval अणु
	अक्षर type[CRYPTO_MAX_NAME];
पूर्ण;

काष्ठा crypto_report_larval अणु
	अक्षर type[CRYPTO_MAX_NAME];
पूर्ण;

काष्ठा crypto_report_hash अणु
	अक्षर type[CRYPTO_MAX_NAME];
	अचिन्हित पूर्णांक blocksize;
	अचिन्हित पूर्णांक digestsize;
पूर्ण;

काष्ठा crypto_report_cipher अणु
	अक्षर type[CRYPTO_MAX_NAME];
	अचिन्हित पूर्णांक blocksize;
	अचिन्हित पूर्णांक min_keysize;
	अचिन्हित पूर्णांक max_keysize;
पूर्ण;

काष्ठा crypto_report_blkcipher अणु
	अक्षर type[CRYPTO_MAX_NAME];
	अक्षर geniv[CRYPTO_MAX_NAME];
	अचिन्हित पूर्णांक blocksize;
	अचिन्हित पूर्णांक min_keysize;
	अचिन्हित पूर्णांक max_keysize;
	अचिन्हित पूर्णांक ivsize;
पूर्ण;

काष्ठा crypto_report_aead अणु
	अक्षर type[CRYPTO_MAX_NAME];
	अक्षर geniv[CRYPTO_MAX_NAME];
	अचिन्हित पूर्णांक blocksize;
	अचिन्हित पूर्णांक maxauthsize;
	अचिन्हित पूर्णांक ivsize;
पूर्ण;

काष्ठा crypto_report_comp अणु
	अक्षर type[CRYPTO_MAX_NAME];
पूर्ण;

काष्ठा crypto_report_rng अणु
	अक्षर type[CRYPTO_MAX_NAME];
	अचिन्हित पूर्णांक seedsize;
पूर्ण;

काष्ठा crypto_report_akcipher अणु
	अक्षर type[CRYPTO_MAX_NAME];
पूर्ण;

काष्ठा crypto_report_kpp अणु
	अक्षर type[CRYPTO_MAX_NAME];
पूर्ण;

काष्ठा crypto_report_acomp अणु
	अक्षर type[CRYPTO_MAX_NAME];
पूर्ण;

#घोषणा CRYPTO_REPORT_MAXSIZE (माप(काष्ठा crypto_user_alg) + \
			       माप(काष्ठा crypto_report_blkcipher))

#पूर्ण_अगर /* _UAPI_LINUX_CRYPTOUSER_H */
