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

#अगर_अघोषित _ZCRYPT_CEX2A_H_
#घोषणा _ZCRYPT_CEX2A_H_

/**
 * The type 50 message family is associated with CEXxA cards.
 *
 * The four members of the family are described below.
 *
 * Note that all अचिन्हित अक्षर arrays are right-justअगरied and left-padded
 * with zeroes.
 *
 * Note that all reserved fields must be zeroes.
 */
काष्ठा type50_hdr अणु
	अचिन्हित अक्षर	reserved1;
	अचिन्हित अक्षर	msg_type_code;	/* 0x50 */
	अचिन्हित लघु	msg_len;
	अचिन्हित अक्षर	reserved2;
	अचिन्हित अक्षर	ignored;
	अचिन्हित लघु	reserved3;
पूर्ण __packed;

#घोषणा TYPE50_TYPE_CODE	0x50

#घोषणा TYPE50_MEB1_FMT		0x0001
#घोषणा TYPE50_MEB2_FMT		0x0002
#घोषणा TYPE50_MEB3_FMT		0x0003
#घोषणा TYPE50_CRB1_FMT		0x0011
#घोषणा TYPE50_CRB2_FMT		0x0012
#घोषणा TYPE50_CRB3_FMT		0x0013

/* Mod-Exp, with a small modulus */
काष्ठा type50_meb1_msg अणु
	काष्ठा type50_hdr header;
	अचिन्हित लघु	keyblock_type;	/* 0x0001 */
	अचिन्हित अक्षर	reserved[6];
	अचिन्हित अक्षर	exponent[128];
	अचिन्हित अक्षर	modulus[128];
	अचिन्हित अक्षर	message[128];
पूर्ण __packed;

/* Mod-Exp, with a large modulus */
काष्ठा type50_meb2_msg अणु
	काष्ठा type50_hdr header;
	अचिन्हित लघु	keyblock_type;	/* 0x0002 */
	अचिन्हित अक्षर	reserved[6];
	अचिन्हित अक्षर	exponent[256];
	अचिन्हित अक्षर	modulus[256];
	अचिन्हित अक्षर	message[256];
पूर्ण __packed;

/* Mod-Exp, with a larger modulus */
काष्ठा type50_meb3_msg अणु
	काष्ठा type50_hdr header;
	अचिन्हित लघु	keyblock_type;	/* 0x0003 */
	अचिन्हित अक्षर	reserved[6];
	अचिन्हित अक्षर	exponent[512];
	अचिन्हित अक्षर	modulus[512];
	अचिन्हित अक्षर	message[512];
पूर्ण __packed;

/* CRT, with a small modulus */
काष्ठा type50_crb1_msg अणु
	काष्ठा type50_hdr header;
	अचिन्हित लघु	keyblock_type;	/* 0x0011 */
	अचिन्हित अक्षर	reserved[6];
	अचिन्हित अक्षर	p[64];
	अचिन्हित अक्षर	q[64];
	अचिन्हित अक्षर	dp[64];
	अचिन्हित अक्षर	dq[64];
	अचिन्हित अक्षर	u[64];
	अचिन्हित अक्षर	message[128];
पूर्ण __packed;

/* CRT, with a large modulus */
काष्ठा type50_crb2_msg अणु
	काष्ठा type50_hdr header;
	अचिन्हित लघु	keyblock_type;	/* 0x0012 */
	अचिन्हित अक्षर	reserved[6];
	अचिन्हित अक्षर	p[128];
	अचिन्हित अक्षर	q[128];
	अचिन्हित अक्षर	dp[128];
	अचिन्हित अक्षर	dq[128];
	अचिन्हित अक्षर	u[128];
	अचिन्हित अक्षर	message[256];
पूर्ण __packed;

/* CRT, with a larger modulus */
काष्ठा type50_crb3_msg अणु
	काष्ठा type50_hdr header;
	अचिन्हित लघु	keyblock_type;	/* 0x0013 */
	अचिन्हित अक्षर	reserved[6];
	अचिन्हित अक्षर	p[256];
	अचिन्हित अक्षर	q[256];
	अचिन्हित अक्षर	dp[256];
	अचिन्हित अक्षर	dq[256];
	अचिन्हित अक्षर	u[256];
	अचिन्हित अक्षर	message[512];
पूर्ण __packed;

/**
 * The type 80 response family is associated with a CEXxA cards.
 *
 * Note that all अचिन्हित अक्षर arrays are right-justअगरied and left-padded
 * with zeroes.
 *
 * Note that all reserved fields must be zeroes.
 */

#घोषणा TYPE80_RSP_CODE 0x80

काष्ठा type80_hdr अणु
	अचिन्हित अक्षर	reserved1;
	अचिन्हित अक्षर	type;		/* 0x80 */
	अचिन्हित लघु	len;
	अचिन्हित अक्षर	code;		/* 0x00 */
	अचिन्हित अक्षर	reserved2[3];
	अचिन्हित अक्षर	reserved3[8];
पूर्ण __packed;

पूर्णांक zcrypt_cex2a_init(व्योम);
व्योम zcrypt_cex2a_निकास(व्योम);

#पूर्ण_अगर /* _ZCRYPT_CEX2A_H_ */
