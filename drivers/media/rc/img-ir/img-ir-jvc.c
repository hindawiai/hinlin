<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * ImgTec IR Decoder setup क्रम JVC protocol.
 *
 * Copyright 2012-2014 Imagination Technologies Ltd.
 */

#समावेश "img-ir-hw.h"

/* Convert JVC data to a scancode */
अटल पूर्णांक img_ir_jvc_scancode(पूर्णांक len, u64 raw, u64 enabled_protocols,
			       काष्ठा img_ir_scancode_req *request)
अणु
	अचिन्हित पूर्णांक cust, data;

	अगर (len != 16)
		वापस -EINVAL;

	cust = (raw >> 0) & 0xff;
	data = (raw >> 8) & 0xff;

	request->protocol = RC_PROTO_JVC;
	request->scancode = cust << 8 | data;
	वापस IMG_IR_SCANCODE;
पूर्ण

/* Convert JVC scancode to JVC data filter */
अटल पूर्णांक img_ir_jvc_filter(स्थिर काष्ठा rc_scancode_filter *in,
			     काष्ठा img_ir_filter *out, u64 protocols)
अणु
	अचिन्हित पूर्णांक cust, data;
	अचिन्हित पूर्णांक cust_m, data_m;

	cust   = (in->data >> 8) & 0xff;
	cust_m = (in->mask >> 8) & 0xff;
	data   = (in->data >> 0) & 0xff;
	data_m = (in->mask >> 0) & 0xff;

	out->data = cust   | data << 8;
	out->mask = cust_m | data_m << 8;

	वापस 0;
पूर्ण

/*
 * JVC decoder
 * See also http://www.sbprojects.com/knowledge/ir/jvc.php
 *          http://support.jvc.com/consumer/support/करोcuments/RemoteCodes.pdf
 */
काष्ठा img_ir_decoder img_ir_jvc = अणु
	.type = RC_PROTO_BIT_JVC,
	.control = अणु
		.decoden = 1,
		.code_type = IMG_IR_CODETYPE_PULSEDIST,
	पूर्ण,
	/* मुख्य timings */
	.unit = 527500, /* 527.5 us */
	.timings = अणु
		/* leader symbol */
		.ldr = अणु
			.pulse = अणु 16	/* 8.44 ms */ पूर्ण,
			.space = अणु 8	/* 4.22 ms */ पूर्ण,
		पूर्ण,
		/* 0 symbol */
		.s00 = अणु
			.pulse = अणु 1	/* 527.5 us +-60 us */ पूर्ण,
			.space = अणु 1	/* 527.5 us */ पूर्ण,
		पूर्ण,
		/* 1 symbol */
		.s01 = अणु
			.pulse = अणु 1	/* 527.5 us +-60 us */ पूर्ण,
			.space = अणु 3	/* 1.5825 ms +-40 us */ पूर्ण,
		पूर्ण,
		/* मुक्त समय */
		.ft = अणु
			.minlen = 16,
			.maxlen = 16,
			.ft_min = 10,	/* 5.275 ms */
		पूर्ण,
	पूर्ण,
	/* scancode logic */
	.scancode = img_ir_jvc_scancode,
	.filter = img_ir_jvc_filter,
पूर्ण;
