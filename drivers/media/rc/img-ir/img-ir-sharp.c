<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * ImgTec IR Decoder setup क्रम Sharp protocol.
 *
 * Copyright 2012-2014 Imagination Technologies Ltd.
 */

#समावेश "img-ir-hw.h"

/* Convert Sharp data to a scancode */
अटल पूर्णांक img_ir_sharp_scancode(पूर्णांक len, u64 raw, u64 enabled_protocols,
				 काष्ठा img_ir_scancode_req *request)
अणु
	अचिन्हित पूर्णांक addr, cmd, exp, chk;

	अगर (len != 15)
		वापस -EINVAL;

	addr = (raw >>   0) & 0x1f;
	cmd  = (raw >>   5) & 0xff;
	exp  = (raw >>  13) &  0x1;
	chk  = (raw >>  14) &  0x1;

	/* validate data */
	अगर (!exp)
		वापस -EINVAL;
	अगर (chk)
		/* probably the second half of the message */
		वापस -EINVAL;

	request->protocol = RC_PROTO_SHARP;
	request->scancode = addr << 8 | cmd;
	वापस IMG_IR_SCANCODE;
पूर्ण

/* Convert Sharp scancode to Sharp data filter */
अटल पूर्णांक img_ir_sharp_filter(स्थिर काष्ठा rc_scancode_filter *in,
			       काष्ठा img_ir_filter *out, u64 protocols)
अणु
	अचिन्हित पूर्णांक addr, cmd, exp = 0, chk = 0;
	अचिन्हित पूर्णांक addr_m, cmd_m, exp_m = 0, chk_m = 0;

	addr   = (in->data >> 8) & 0x1f;
	addr_m = (in->mask >> 8) & 0x1f;
	cmd    = (in->data >> 0) & 0xff;
	cmd_m  = (in->mask >> 0) & 0xff;
	अगर (cmd_m) अणु
		/* अगर filtering commands, we can only match the first part */
		exp   = 1;
		exp_m = 1;
		chk   = 0;
		chk_m = 1;
	पूर्ण

	out->data = addr        |
		    cmd   <<  5 |
		    exp   << 13 |
		    chk   << 14;
	out->mask = addr_m      |
		    cmd_m <<  5 |
		    exp_m << 13 |
		    chk_m << 14;

	वापस 0;
पूर्ण

/*
 * Sharp decoder
 * See also http://www.sbprojects.com/knowledge/ir/sharp.php
 */
काष्ठा img_ir_decoder img_ir_sharp = अणु
	.type = RC_PROTO_BIT_SHARP,
	.control = अणु
		.decoden = 0,
		.decodend2 = 1,
		.code_type = IMG_IR_CODETYPE_PULSEDIST,
		.d1validsel = 1,
	पूर्ण,
	/* मुख्य timings */
	.tolerance = 20,	/* 20% */
	.timings = अणु
		/* 0 symbol */
		.s10 = अणु
			.pulse = अणु 320	/* 320 us */ पूर्ण,
			.space = अणु 680	/* 1 ms period */ पूर्ण,
		पूर्ण,
		/* 1 symbol */
		.s11 = अणु
			.pulse = अणु 320	/* 320 us */ पूर्ण,
			.space = अणु 1680	/* 2 ms period */ पूर्ण,
		पूर्ण,
		/* मुक्त समय */
		.ft = अणु
			.minlen = 15,
			.maxlen = 15,
			.ft_min = 5000,	/* 5 ms */
		पूर्ण,
	पूर्ण,
	/* scancode logic */
	.scancode = img_ir_sharp_scancode,
	.filter = img_ir_sharp_filter,
पूर्ण;
