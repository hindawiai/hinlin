<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/* ASN.1 BER/DER/CER parsing state machine पूर्णांकernal definitions
 *
 * Copyright (C) 2012 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */

#अगर_अघोषित _LINUX_ASN1_BER_BYTECODE_H
#घोषणा _LINUX_ASN1_BER_BYTECODE_H

#अगर_घोषित __KERNEL__
#समावेश <linux/types.h>
#पूर्ण_अगर
#समावेश <linux/asn1.h>

प्रकार पूर्णांक (*asn1_action_t)(व्योम *context,
			     माप_प्रकार hdrlen, /* In हाल of ANY type */
			     अचिन्हित अक्षर tag, /* In हाल of ANY type */
			     स्थिर व्योम *value, माप_प्रकार vlen);

काष्ठा asn1_decoder अणु
	स्थिर अचिन्हित अक्षर *machine;
	माप_प्रकार machlen;
	स्थिर asn1_action_t *actions;
पूर्ण;

क्रमागत asn1_opcode अणु
	/* The tag-matching ops come first and the odd-numbered slots
	 * are क्रम OR_SKIP ops.
	 */
#घोषणा ASN1_OP_MATCH__SKIP		  0x01
#घोषणा ASN1_OP_MATCH__ACT		  0x02
#घोषणा ASN1_OP_MATCH__JUMP		  0x04
#घोषणा ASN1_OP_MATCH__ANY		  0x08
#घोषणा ASN1_OP_MATCH__COND		  0x10

	ASN1_OP_MATCH			= 0x00,
	ASN1_OP_MATCH_OR_SKIP		= 0x01,
	ASN1_OP_MATCH_ACT		= 0x02,
	ASN1_OP_MATCH_ACT_OR_SKIP	= 0x03,
	ASN1_OP_MATCH_JUMP		= 0x04,
	ASN1_OP_MATCH_JUMP_OR_SKIP	= 0x05,
	ASN1_OP_MATCH_ANY		= 0x08,
	ASN1_OP_MATCH_ANY_OR_SKIP	= 0x09,
	ASN1_OP_MATCH_ANY_ACT		= 0x0a,
	ASN1_OP_MATCH_ANY_ACT_OR_SKIP	= 0x0b,
	/* Everything beक्रमe here matches unconditionally */

	ASN1_OP_COND_MATCH_OR_SKIP	= 0x11,
	ASN1_OP_COND_MATCH_ACT_OR_SKIP	= 0x13,
	ASN1_OP_COND_MATCH_JUMP_OR_SKIP	= 0x15,
	ASN1_OP_COND_MATCH_ANY		= 0x18,
	ASN1_OP_COND_MATCH_ANY_OR_SKIP	= 0x19,
	ASN1_OP_COND_MATCH_ANY_ACT	= 0x1a,
	ASN1_OP_COND_MATCH_ANY_ACT_OR_SKIP = 0x1b,

	/* Everything beक्रमe here will want a tag from the data */
#घोषणा ASN1_OP__MATCHES_TAG ASN1_OP_COND_MATCH_ANY_ACT_OR_SKIP

	/* These are here to help fill up space */
	ASN1_OP_COND_FAIL		= 0x1c,
	ASN1_OP_COMPLETE		= 0x1d,
	ASN1_OP_ACT			= 0x1e,
	ASN1_OP_MAYBE_ACT		= 0x1f,

	/* The following eight have bit 0 -> SET, 1 -> OF, 2 -> ACT */
	ASN1_OP_END_SEQ			= 0x20,
	ASN1_OP_END_SET			= 0x21,
	ASN1_OP_END_SEQ_OF		= 0x22,
	ASN1_OP_END_SET_OF		= 0x23,
	ASN1_OP_END_SEQ_ACT		= 0x24,
	ASN1_OP_END_SET_ACT		= 0x25,
	ASN1_OP_END_SEQ_OF_ACT		= 0x26,
	ASN1_OP_END_SET_OF_ACT		= 0x27,
#घोषणा ASN1_OP_END__SET		  0x01
#घोषणा ASN1_OP_END__OF			  0x02
#घोषणा ASN1_OP_END__ACT		  0x04

	ASN1_OP_RETURN			= 0x28,

	ASN1_OP__NR
पूर्ण;

#घोषणा _tag(CLASS, CP, TAG) ((ASN1_##CLASS << 6) | (ASN1_##CP << 5) | ASN1_##TAG)
#घोषणा _tagn(CLASS, CP, TAG) ((ASN1_##CLASS << 6) | (ASN1_##CP << 5) | TAG)
#घोषणा _jump_target(N) (N)
#घोषणा _action(N) (N)

#पूर्ण_अगर /* _LINUX_ASN1_BER_BYTECODE_H */
