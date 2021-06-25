<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * ImgTec IR Decoder setup क्रम Philips RC-5 protocol.
 *
 * Copyright 2012-2014 Imagination Technologies Ltd.
 */

#समावेश "img-ir-hw.h"

/* Convert RC5 data to a scancode */
अटल पूर्णांक img_ir_rc5_scancode(पूर्णांक len, u64 raw, u64 enabled_protocols,
				काष्ठा img_ir_scancode_req *request)
अणु
	अचिन्हित पूर्णांक addr, cmd, tgl, start;

	/* Quirk in the decoder shअगरts everything by 2 to the left. */
	raw   >>= 2;

	start	=  (raw >> 13)	& 0x01;
	tgl	=  (raw >> 11)	& 0x01;
	addr	=  (raw >>  6)	& 0x1f;
	cmd	=   raw		& 0x3f;
	/*
	 * 12th bit is used to extend the command in extended RC5 and has
	 * no effect on standard RC5.
	 */
	cmd	+= ((raw >> 12) & 0x01) ? 0 : 0x40;

	अगर (!start)
		वापस -EINVAL;

	request->protocol = RC_PROTO_RC5;
	request->scancode = addr << 8 | cmd;
	request->toggle   = tgl;
	वापस IMG_IR_SCANCODE;
पूर्ण

/* Convert RC5 scancode to RC5 data filter */
अटल पूर्णांक img_ir_rc5_filter(स्थिर काष्ठा rc_scancode_filter *in,
				 काष्ठा img_ir_filter *out, u64 protocols)
अणु
	/* Not supported by the hw. */
	वापस -EINVAL;
पूर्ण

/*
 * RC-5 decoder
 * see http://www.sbprojects.com/knowledge/ir/rc5.php
 */
काष्ठा img_ir_decoder img_ir_rc5 = अणु
	.type      = RC_PROTO_BIT_RC5,
	.control   = अणु
		.bitoriend2	= 1,
		.code_type	= IMG_IR_CODETYPE_BIPHASE,
		.decodend2	= 1,
	पूर्ण,
	/* मुख्य timings */
	.tolerance	= 16,
	.unit		= 888888, /* 1/36k*32=888.888microseconds */
	.timings	= अणु
		/* 10 symbol */
		.s10 = अणु
			.pulse	= अणु 1 पूर्ण,
			.space	= अणु 1 पूर्ण,
		पूर्ण,

		/* 11 symbol */
		.s11 = अणु
			.pulse	= अणु 1 पूर्ण,
			.space	= अणु 1 पूर्ण,
		पूर्ण,

		/* मुक्त समय */
		.ft  = अणु
			.minlen = 14,
			.maxlen = 14,
			.ft_min = 5,
		पूर्ण,
	पूर्ण,

	/* scancode logic */
	.scancode	= img_ir_rc5_scancode,
	.filter		= img_ir_rc5_filter,
पूर्ण;
