<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ISCSI_CHAP_H_
#घोषणा _ISCSI_CHAP_H_

#समावेश <linux/types.h>

#घोषणा CHAP_DIGEST_UNKNOWN	0
#घोषणा CHAP_DIGEST_MD5		5
#घोषणा CHAP_DIGEST_SHA1	6
#घोषणा CHAP_DIGEST_SHA256	7
#घोषणा CHAP_DIGEST_SHA3_256	8

#घोषणा MAX_CHAP_CHALLENGE_LEN	32
#घोषणा CHAP_CHALLENGE_STR_LEN	4096
#घोषणा MAX_RESPONSE_LENGTH	128	/* sufficient क्रम SHA3 256 */
#घोषणा	MAX_CHAP_N_SIZE		512

#घोषणा MD5_SIGNATURE_SIZE	16	/* 16 bytes in a MD5 message digest */
#घोषणा SHA1_SIGNATURE_SIZE	20	/* 20 bytes in a SHA1 message digest */
#घोषणा SHA256_SIGNATURE_SIZE	32	/* 32 bytes in a SHA256 message digest */
#घोषणा SHA3_256_SIGNATURE_SIZE	32	/* 32 bytes in a SHA3 256 message digest */

#घोषणा CHAP_STAGE_CLIENT_A	1
#घोषणा CHAP_STAGE_SERVER_AIC	2
#घोषणा CHAP_STAGE_CLIENT_NR	3
#घोषणा CHAP_STAGE_CLIENT_NRIC	4
#घोषणा CHAP_STAGE_SERVER_NR	5

काष्ठा iscsi_node_auth;
काष्ठा iscsi_conn;

बाह्य u32 chap_मुख्य_loop(काष्ठा iscsi_conn *, काष्ठा iscsi_node_auth *, अक्षर *, अक्षर *,
				पूर्णांक *, पूर्णांक *);

काष्ठा iscsi_chap अणु
	अचिन्हित अक्षर	id;
	अचिन्हित अक्षर	challenge[MAX_CHAP_CHALLENGE_LEN];
	अचिन्हित पूर्णांक	challenge_len;
	अचिन्हित अक्षर	*digest_name;
	अचिन्हित पूर्णांक	digest_size;
	अचिन्हित पूर्णांक	authenticate_target;
	अचिन्हित पूर्णांक	chap_state;
पूर्ण ____cacheline_aligned;

#पूर्ण_अगर   /*** _ISCSI_CHAP_H_ ***/
