<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * sm2.h - SM2 asymmetric खुला-key algorithm
 * as specअगरied by OSCCA GM/T 0003.1-2012 -- 0003.5-2012 SM2 and
 * described at https://tools.ietf.org/hपंचांगl/draft-shen-sm2-ecdsa-02
 *
 * Copyright (c) 2020, Alibaba Group.
 * Written by Tianjia Zhang <tianjia.zhang@linux.alibaba.com>
 */

#अगर_अघोषित _CRYPTO_SM2_H
#घोषणा _CRYPTO_SM2_H

#समावेश <crypto/sm3.h>
#समावेश <crypto/akcipher.h>

/* The शेष user id as specअगरied in GM/T 0009-2012 */
#घोषणा SM2_DEFAULT_USERID "1234567812345678"
#घोषणा SM2_DEFAULT_USERID_LEN 16

बाह्य पूर्णांक sm2_compute_z_digest(काष्ठा crypto_akcipher *tfm,
			स्थिर अचिन्हित अक्षर *id, माप_प्रकार id_len,
			अचिन्हित अक्षर dgst[SM3_DIGEST_SIZE]);

#पूर्ण_अगर /* _CRYPTO_SM2_H */
