<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* Decoder क्रम ASN.1 BER/DER/CER encoded bytestream
 *
 * Copyright (C) 2012 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */

#समावेश <linux/export.h>
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/module.h>
#समावेश <linux/asn1_decoder.h>
#समावेश <linux/asn1_ber_bytecode.h>

अटल स्थिर अचिन्हित अक्षर asn1_op_lengths[ASN1_OP__NR] = अणु
	/*					OPC TAG JMP ACT */
	[ASN1_OP_MATCH]				= 1 + 1,
	[ASN1_OP_MATCH_OR_SKIP]			= 1 + 1,
	[ASN1_OP_MATCH_ACT]			= 1 + 1     + 1,
	[ASN1_OP_MATCH_ACT_OR_SKIP]		= 1 + 1     + 1,
	[ASN1_OP_MATCH_JUMP]			= 1 + 1 + 1,
	[ASN1_OP_MATCH_JUMP_OR_SKIP]		= 1 + 1 + 1,
	[ASN1_OP_MATCH_ANY]			= 1,
	[ASN1_OP_MATCH_ANY_OR_SKIP]		= 1,
	[ASN1_OP_MATCH_ANY_ACT]			= 1         + 1,
	[ASN1_OP_MATCH_ANY_ACT_OR_SKIP]		= 1         + 1,
	[ASN1_OP_COND_MATCH_OR_SKIP]		= 1 + 1,
	[ASN1_OP_COND_MATCH_ACT_OR_SKIP]	= 1 + 1     + 1,
	[ASN1_OP_COND_MATCH_JUMP_OR_SKIP]	= 1 + 1 + 1,
	[ASN1_OP_COND_MATCH_ANY]		= 1,
	[ASN1_OP_COND_MATCH_ANY_OR_SKIP]	= 1,
	[ASN1_OP_COND_MATCH_ANY_ACT]		= 1         + 1,
	[ASN1_OP_COND_MATCH_ANY_ACT_OR_SKIP]	= 1         + 1,
	[ASN1_OP_COND_FAIL]			= 1,
	[ASN1_OP_COMPLETE]			= 1,
	[ASN1_OP_ACT]				= 1         + 1,
	[ASN1_OP_MAYBE_ACT]			= 1         + 1,
	[ASN1_OP_RETURN]			= 1,
	[ASN1_OP_END_SEQ]			= 1,
	[ASN1_OP_END_SEQ_OF]			= 1     + 1,
	[ASN1_OP_END_SET]			= 1,
	[ASN1_OP_END_SET_OF]			= 1     + 1,
	[ASN1_OP_END_SEQ_ACT]			= 1         + 1,
	[ASN1_OP_END_SEQ_OF_ACT]		= 1     + 1 + 1,
	[ASN1_OP_END_SET_ACT]			= 1         + 1,
	[ASN1_OP_END_SET_OF_ACT]		= 1     + 1 + 1,
पूर्ण;

/*
 * Find the length of an indefinite length object
 * @data: The data buffer
 * @datalen: The end of the innermost containing element in the buffer
 * @_dp: The data parse cursor (updated beक्रमe वापसing)
 * @_len: Where to वापस the size of the element.
 * @_errmsg: Where to वापस a poपूर्णांकer to an error message on error
 */
अटल पूर्णांक asn1_find_indefinite_length(स्थिर अचिन्हित अक्षर *data, माप_प्रकार datalen,
				       माप_प्रकार *_dp, माप_प्रकार *_len,
				       स्थिर अक्षर **_errmsg)
अणु
	अचिन्हित अक्षर tag, पंचांगp;
	माप_प्रकार dp = *_dp, len, n;
	पूर्णांक indef_level = 1;

next_tag:
	अगर (unlikely(datalen - dp < 2)) अणु
		अगर (datalen == dp)
			जाओ missing_eoc;
		जाओ data_overrun_error;
	पूर्ण

	/* Extract a tag from the data */
	tag = data[dp++];
	अगर (tag == ASN1_EOC) अणु
		/* It appears to be an EOC. */
		अगर (data[dp++] != 0)
			जाओ invalid_eoc;
		अगर (--indef_level <= 0) अणु
			*_len = dp - *_dp;
			*_dp = dp;
			वापस 0;
		पूर्ण
		जाओ next_tag;
	पूर्ण

	अगर (unlikely((tag & 0x1f) == ASN1_LONG_TAG)) अणु
		करो अणु
			अगर (unlikely(datalen - dp < 2))
				जाओ data_overrun_error;
			पंचांगp = data[dp++];
		पूर्ण जबतक (पंचांगp & 0x80);
	पूर्ण

	/* Extract the length */
	len = data[dp++];
	अगर (len <= 0x7f)
		जाओ check_length;

	अगर (unlikely(len == ASN1_INDEFINITE_LENGTH)) अणु
		/* Indefinite length */
		अगर (unlikely((tag & ASN1_CONS_BIT) == ASN1_PRIM << 5))
			जाओ indefinite_len_primitive;
		indef_level++;
		जाओ next_tag;
	पूर्ण

	n = len - 0x80;
	अगर (unlikely(n > माप(len) - 1))
		जाओ length_too_दीर्घ;
	अगर (unlikely(n > datalen - dp))
		जाओ data_overrun_error;
	len = 0;
	क्रम (; n > 0; n--) अणु
		len <<= 8;
		len |= data[dp++];
	पूर्ण
check_length:
	अगर (len > datalen - dp)
		जाओ data_overrun_error;
	dp += len;
	जाओ next_tag;

length_too_दीर्घ:
	*_errmsg = "Unsupported length";
	जाओ error;
indefinite_len_primitive:
	*_errmsg = "Indefinite len primitive not permitted";
	जाओ error;
invalid_eoc:
	*_errmsg = "Invalid length EOC";
	जाओ error;
data_overrun_error:
	*_errmsg = "Data overrun error";
	जाओ error;
missing_eoc:
	*_errmsg = "Missing EOC in indefinite len cons";
error:
	*_dp = dp;
	वापस -1;
पूर्ण

/**
 * asn1_ber_decoder - Decoder BER/DER/CER ASN.1 according to pattern
 * @decoder: The decoder definition (produced by asn1_compiler)
 * @context: The caller's context (to be passed to the action functions)
 * @data: The encoded data
 * @datalen: The size of the encoded data
 *
 * Decode BER/DER/CER encoded ASN.1 data according to a bytecode pattern
 * produced by asn1_compiler.  Action functions are called on marked tags to
 * allow the caller to retrieve signअगरicant data.
 *
 * LIMITATIONS:
 *
 * To keep करोwn the amount of stack used by this function, the following limits
 * have been imposed:
 *
 *  (1) This won't handle datalen > 65535 without increasing the size of the
 *	cons stack elements and length_too_दीर्घ checking.
 *
 *  (2) The stack of स्थिरructed types is 10 deep.  If the depth of non-leaf
 *	स्थिरructed types exceeds this, the decode will fail.
 *
 *  (3) The SET type (not the SET OF type) isn't really supported as tracking
 *	what members of the set have been seen is a pain.
 */
पूर्णांक asn1_ber_decoder(स्थिर काष्ठा asn1_decoder *decoder,
		     व्योम *context,
		     स्थिर अचिन्हित अक्षर *data,
		     माप_प्रकार datalen)
अणु
	स्थिर अचिन्हित अक्षर *machine = decoder->machine;
	स्थिर asn1_action_t *actions = decoder->actions;
	माप_प्रकार machlen = decoder->machlen;
	क्रमागत asn1_opcode op;
	अचिन्हित अक्षर tag = 0, csp = 0, jsp = 0, optag = 0, hdr = 0;
	स्थिर अक्षर *errmsg;
	माप_प्रकार pc = 0, dp = 0, tdp = 0, len = 0;
	पूर्णांक ret;

	अचिन्हित अक्षर flags = 0;
#घोषणा FLAG_INDEFINITE_LENGTH	0x01
#घोषणा FLAG_MATCHED		0x02
#घोषणा FLAG_LAST_MATCHED	0x04 /* Last tag matched */
#घोषणा FLAG_CONS		0x20 /* Corresponds to CONS bit in the opcode tag
				      * - ie. whether or not we are going to parse
				      *   a compound type.
				      */

#घोषणा NR_CONS_STACK 10
	अचिन्हित लघु cons_dp_stack[NR_CONS_STACK];
	अचिन्हित लघु cons_datalen_stack[NR_CONS_STACK];
	अचिन्हित अक्षर cons_hdrlen_stack[NR_CONS_STACK];
#घोषणा NR_JUMP_STACK 10
	अचिन्हित अक्षर jump_stack[NR_JUMP_STACK];

	अगर (datalen > 65535)
		वापस -EMSGSIZE;

next_op:
	pr_debug("next_op: pc=\e[32m%zu\e[m/%zu dp=\e[33m%zu\e[m/%zu C=%d J=%d\n",
		 pc, machlen, dp, datalen, csp, jsp);
	अगर (unlikely(pc >= machlen))
		जाओ machine_overrun_error;
	op = machine[pc];
	अगर (unlikely(pc + asn1_op_lengths[op] > machlen))
		जाओ machine_overrun_error;

	/* If this command is meant to match a tag, then करो that beक्रमe
	 * evaluating the command.
	 */
	अगर (op <= ASN1_OP__MATCHES_TAG) अणु
		अचिन्हित अक्षर पंचांगp;

		/* Skip conditional matches अगर possible */
		अगर ((op & ASN1_OP_MATCH__COND && flags & FLAG_MATCHED) ||
		    (op & ASN1_OP_MATCH__SKIP && dp == datalen)) अणु
			flags &= ~FLAG_LAST_MATCHED;
			pc += asn1_op_lengths[op];
			जाओ next_op;
		पूर्ण

		flags = 0;
		hdr = 2;

		/* Extract a tag from the data */
		अगर (unlikely(datalen - dp < 2))
			जाओ data_overrun_error;
		tag = data[dp++];
		अगर (unlikely((tag & 0x1f) == ASN1_LONG_TAG))
			जाओ दीर्घ_tag_not_supported;

		अगर (op & ASN1_OP_MATCH__ANY) अणु
			pr_debug("- any %02x\n", tag);
		पूर्ण अन्यथा अणु
			/* Extract the tag from the machine
			 * - Either CONS or PRIM are permitted in the data अगर
			 *   CONS is not set in the op stream, otherwise CONS
			 *   is mandatory.
			 */
			optag = machine[pc + 1];
			flags |= optag & FLAG_CONS;

			/* Determine whether the tag matched */
			पंचांगp = optag ^ tag;
			पंचांगp &= ~(optag & ASN1_CONS_BIT);
			pr_debug("- match? %02x %02x %02x\n", tag, optag, पंचांगp);
			अगर (पंचांगp != 0) अणु
				/* All odd-numbered tags are MATCH_OR_SKIP. */
				अगर (op & ASN1_OP_MATCH__SKIP) अणु
					pc += asn1_op_lengths[op];
					dp--;
					जाओ next_op;
				पूर्ण
				जाओ tag_mismatch;
			पूर्ण
		पूर्ण
		flags |= FLAG_MATCHED;

		len = data[dp++];
		अगर (len > 0x7f) अणु
			अगर (unlikely(len == ASN1_INDEFINITE_LENGTH)) अणु
				/* Indefinite length */
				अगर (unlikely(!(tag & ASN1_CONS_BIT)))
					जाओ indefinite_len_primitive;
				flags |= FLAG_INDEFINITE_LENGTH;
				अगर (unlikely(2 > datalen - dp))
					जाओ data_overrun_error;
			पूर्ण अन्यथा अणु
				पूर्णांक n = len - 0x80;
				अगर (unlikely(n > 2))
					जाओ length_too_दीर्घ;
				अगर (unlikely(n > datalen - dp))
					जाओ data_overrun_error;
				hdr += n;
				क्रम (len = 0; n > 0; n--) अणु
					len <<= 8;
					len |= data[dp++];
				पूर्ण
				अगर (unlikely(len > datalen - dp))
					जाओ data_overrun_error;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (unlikely(len > datalen - dp))
				जाओ data_overrun_error;
		पूर्ण

		अगर (flags & FLAG_CONS) अणु
			/* For expected compound क्रमms, we stack the positions
			 * of the start and end of the data.
			 */
			अगर (unlikely(csp >= NR_CONS_STACK))
				जाओ cons_stack_overflow;
			cons_dp_stack[csp] = dp;
			cons_hdrlen_stack[csp] = hdr;
			अगर (!(flags & FLAG_INDEFINITE_LENGTH)) अणु
				cons_datalen_stack[csp] = datalen;
				datalen = dp + len;
			पूर्ण अन्यथा अणु
				cons_datalen_stack[csp] = 0;
			पूर्ण
			csp++;
		पूर्ण

		pr_debug("- TAG: %02x %zu%s\n",
			 tag, len, flags & FLAG_CONS ? " CONS" : "");
		tdp = dp;
	पूर्ण

	/* Decide how to handle the operation */
	चयन (op) अणु
	हाल ASN1_OP_MATCH:
	हाल ASN1_OP_MATCH_OR_SKIP:
	हाल ASN1_OP_MATCH_ACT:
	हाल ASN1_OP_MATCH_ACT_OR_SKIP:
	हाल ASN1_OP_MATCH_ANY:
	हाल ASN1_OP_MATCH_ANY_OR_SKIP:
	हाल ASN1_OP_MATCH_ANY_ACT:
	हाल ASN1_OP_MATCH_ANY_ACT_OR_SKIP:
	हाल ASN1_OP_COND_MATCH_OR_SKIP:
	हाल ASN1_OP_COND_MATCH_ACT_OR_SKIP:
	हाल ASN1_OP_COND_MATCH_ANY:
	हाल ASN1_OP_COND_MATCH_ANY_OR_SKIP:
	हाल ASN1_OP_COND_MATCH_ANY_ACT:
	हाल ASN1_OP_COND_MATCH_ANY_ACT_OR_SKIP:

		अगर (!(flags & FLAG_CONS)) अणु
			अगर (flags & FLAG_INDEFINITE_LENGTH) अणु
				माप_प्रकार पंचांगp = dp;

				ret = asn1_find_indefinite_length(
					data, datalen, &पंचांगp, &len, &errmsg);
				अगर (ret < 0)
					जाओ error;
			पूर्ण
			pr_debug("- LEAF: %zu\n", len);
		पूर्ण

		अगर (op & ASN1_OP_MATCH__ACT) अणु
			अचिन्हित अक्षर act;

			अगर (op & ASN1_OP_MATCH__ANY)
				act = machine[pc + 1];
			अन्यथा
				act = machine[pc + 2];
			ret = actions[act](context, hdr, tag, data + dp, len);
			अगर (ret < 0)
				वापस ret;
		पूर्ण

		अगर (!(flags & FLAG_CONS))
			dp += len;
		pc += asn1_op_lengths[op];
		जाओ next_op;

	हाल ASN1_OP_MATCH_JUMP:
	हाल ASN1_OP_MATCH_JUMP_OR_SKIP:
	हाल ASN1_OP_COND_MATCH_JUMP_OR_SKIP:
		pr_debug("- MATCH_JUMP\n");
		अगर (unlikely(jsp == NR_JUMP_STACK))
			जाओ jump_stack_overflow;
		jump_stack[jsp++] = pc + asn1_op_lengths[op];
		pc = machine[pc + 2];
		जाओ next_op;

	हाल ASN1_OP_COND_FAIL:
		अगर (unlikely(!(flags & FLAG_MATCHED)))
			जाओ tag_mismatch;
		pc += asn1_op_lengths[op];
		जाओ next_op;

	हाल ASN1_OP_COMPLETE:
		अगर (unlikely(jsp != 0 || csp != 0)) अणु
			pr_err("ASN.1 decoder error: Stacks not empty at completion (%u, %u)\n",
			       jsp, csp);
			वापस -EBADMSG;
		पूर्ण
		वापस 0;

	हाल ASN1_OP_END_SET:
	हाल ASN1_OP_END_SET_ACT:
		अगर (unlikely(!(flags & FLAG_MATCHED)))
			जाओ tag_mismatch;
		fallthrough;

	हाल ASN1_OP_END_SEQ:
	हाल ASN1_OP_END_SET_OF:
	हाल ASN1_OP_END_SEQ_OF:
	हाल ASN1_OP_END_SEQ_ACT:
	हाल ASN1_OP_END_SET_OF_ACT:
	हाल ASN1_OP_END_SEQ_OF_ACT:
		अगर (unlikely(csp <= 0))
			जाओ cons_stack_underflow;
		csp--;
		tdp = cons_dp_stack[csp];
		hdr = cons_hdrlen_stack[csp];
		len = datalen;
		datalen = cons_datalen_stack[csp];
		pr_debug("- end cons t=%zu dp=%zu l=%zu/%zu\n",
			 tdp, dp, len, datalen);
		अगर (datalen == 0) अणु
			/* Indefinite length - check क्रम the EOC. */
			datalen = len;
			अगर (unlikely(datalen - dp < 2))
				जाओ data_overrun_error;
			अगर (data[dp++] != 0) अणु
				अगर (op & ASN1_OP_END__OF) अणु
					dp--;
					csp++;
					pc = machine[pc + 1];
					pr_debug("- continue\n");
					जाओ next_op;
				पूर्ण
				जाओ missing_eoc;
			पूर्ण
			अगर (data[dp++] != 0)
				जाओ invalid_eoc;
			len = dp - tdp - 2;
		पूर्ण अन्यथा अणु
			अगर (dp < len && (op & ASN1_OP_END__OF)) अणु
				datalen = len;
				csp++;
				pc = machine[pc + 1];
				pr_debug("- continue\n");
				जाओ next_op;
			पूर्ण
			अगर (dp != len)
				जाओ cons_length_error;
			len -= tdp;
			pr_debug("- cons len l=%zu d=%zu\n", len, dp - tdp);
		पूर्ण

		अगर (op & ASN1_OP_END__ACT) अणु
			अचिन्हित अक्षर act;
			अगर (op & ASN1_OP_END__OF)
				act = machine[pc + 2];
			अन्यथा
				act = machine[pc + 1];
			ret = actions[act](context, hdr, 0, data + tdp, len);
			अगर (ret < 0)
				वापस ret;
		पूर्ण
		pc += asn1_op_lengths[op];
		जाओ next_op;

	हाल ASN1_OP_MAYBE_ACT:
		अगर (!(flags & FLAG_LAST_MATCHED)) अणु
			pc += asn1_op_lengths[op];
			जाओ next_op;
		पूर्ण
		fallthrough;

	हाल ASN1_OP_ACT:
		ret = actions[machine[pc + 1]](context, hdr, tag, data + tdp, len);
		अगर (ret < 0)
			वापस ret;
		pc += asn1_op_lengths[op];
		जाओ next_op;

	हाल ASN1_OP_RETURN:
		अगर (unlikely(jsp <= 0))
			जाओ jump_stack_underflow;
		pc = jump_stack[--jsp];
		flags |= FLAG_MATCHED | FLAG_LAST_MATCHED;
		जाओ next_op;

	शेष:
		अवरोध;
	पूर्ण

	/* Shouldn't reach here */
	pr_err("ASN.1 decoder error: Found reserved opcode (%u) pc=%zu\n",
	       op, pc);
	वापस -EBADMSG;

data_overrun_error:
	errmsg = "Data overrun error";
	जाओ error;
machine_overrun_error:
	errmsg = "Machine overrun error";
	जाओ error;
jump_stack_underflow:
	errmsg = "Jump stack underflow";
	जाओ error;
jump_stack_overflow:
	errmsg = "Jump stack overflow";
	जाओ error;
cons_stack_underflow:
	errmsg = "Cons stack underflow";
	जाओ error;
cons_stack_overflow:
	errmsg = "Cons stack overflow";
	जाओ error;
cons_length_error:
	errmsg = "Cons length error";
	जाओ error;
missing_eoc:
	errmsg = "Missing EOC in indefinite len cons";
	जाओ error;
invalid_eoc:
	errmsg = "Invalid length EOC";
	जाओ error;
length_too_दीर्घ:
	errmsg = "Unsupported length";
	जाओ error;
indefinite_len_primitive:
	errmsg = "Indefinite len primitive not permitted";
	जाओ error;
tag_mismatch:
	errmsg = "Unexpected tag";
	जाओ error;
दीर्घ_tag_not_supported:
	errmsg = "Long tag not supported";
error:
	pr_debug("\nASN1: %s [m=%zu d=%zu ot=%02x t=%02x l=%zu]\n",
		 errmsg, pc, dp, optag, tag, len);
	वापस -EBADMSG;
पूर्ण
EXPORT_SYMBOL_GPL(asn1_ber_decoder);

MODULE_LICENSE("GPL");
