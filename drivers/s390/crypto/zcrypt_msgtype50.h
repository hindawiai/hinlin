<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 *  Copyright IBM Corp. 2001, 2012
 *  Author(s): Robert Burroughs
 *	       Eric Rossman (edrossma@us.ibm.com)
 *
 *  Hotplug & misc device support: Jochen Roehrig (roehrig@de.ibm.com)
 *  Major cleanup & driver split: Martin Schwidefsky <schwidefsky@de.ibm.com>
 *  MSGTYPE reकाष्ठा:		  Holger Dengler <hd@linux.vnet.ibm.com>
 */

#अगर_अघोषित _ZCRYPT_MSGTYPE50_H_
#घोषणा _ZCRYPT_MSGTYPE50_H_

#घोषणा MSGTYPE50_NAME			"zcrypt_msgtype50"
#घोषणा MSGTYPE50_VARIANT_DEFAULT	0

#घोषणा MSGTYPE50_CRB2_MAX_MSG_SIZE 0x390 /* माप(काष्ठा type50_crb2_msg) */
#घोषणा MSGTYPE50_CRB3_MAX_MSG_SIZE 0x710 /* माप(काष्ठा type50_crb3_msg) */

#घोषणा MSGTYPE_ADJUSTMENT 0x08  /* type04 extension (not needed in type50) */

अचिन्हित पूर्णांक get_rsa_modex_fc(काष्ठा ica_rsa_modexpo *, पूर्णांक *);
अचिन्हित पूर्णांक get_rsa_crt_fc(काष्ठा ica_rsa_modexpo_crt *, पूर्णांक *);

व्योम zcrypt_msgtype50_init(व्योम);
व्योम zcrypt_msgtype50_निकास(व्योम);

#पूर्ण_अगर /* _ZCRYPT_MSGTYPE50_H_ */
