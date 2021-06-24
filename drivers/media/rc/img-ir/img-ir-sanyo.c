<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * ImgTec IR Decoder setup क्रम Sanyo protocol.
 *
 * Copyright 2012-2014 Imagination Technologies Ltd.
 *
 * From ir-sanyo-decoder.c:
 *
 * This protocol uses the NEC protocol timings. However, data is क्रमmatted as:
 *	13 bits Custom Code
 *	13 bits NOT(Custom Code)
 *	8 bits Key data
 *	8 bits NOT(Key data)
 *
 * According with LIRC, this protocol is used on Sanyo, Aiwa and Chinon
 * Inक्रमmation क्रम this protocol is available at the Sanyo LC7461 datasheet.
 */

#समावेश "img-ir-hw.h"

/* Convert Sanyo data to a scancode */
अटल पूर्णांक img_ir_sanyo_scancode(पूर्णांक len, u64 raw, u64 enabled_protocols,
				 काष्ठा img_ir_scancode_req *request)
अणु
	अचिन्हित पूर्णांक addr, addr_inv, data, data_inv;
	/* a repeat code has no data */
	अगर (!len)
		वापस IMG_IR_REPEATCODE;
	अगर (len != 42)
		वापस -EINVAL;
	addr     = (raw >>  0) & 0x1fff;
	addr_inv = (raw >> 13) & 0x1fff;
	data     = (raw >> 26) & 0xff;
	data_inv = (raw >> 34) & 0xff;
	/* Validate data */
	अगर ((data_inv ^ data) != 0xff)
		वापस -EINVAL;
	/* Validate address */
	अगर ((addr_inv ^ addr) != 0x1fff)
		वापस -EINVAL;

	/* Normal Sanyo */
	request->protocol = RC_PROTO_SANYO;
	request->scancode = addr << 8 | data;
	वापस IMG_IR_SCANCODE;
पूर्ण

/* Convert Sanyo scancode to Sanyo data filter */
अटल पूर्णांक img_ir_sanyo_filter(स्थिर काष्ठा rc_scancode_filter *in,
			       काष्ठा img_ir_filter *out, u64 protocols)
अणु
	अचिन्हित पूर्णांक addr, addr_inv, data, data_inv;
	अचिन्हित पूर्णांक addr_m, data_m;

	data = in->data & 0xff;
	data_m = in->mask & 0xff;
	data_inv = data ^ 0xff;

	अगर (in->data & 0xff700000)
		वापस -EINVAL;

	addr       = (in->data >> 8) & 0x1fff;
	addr_m     = (in->mask >> 8) & 0x1fff;
	addr_inv   = addr ^ 0x1fff;

	out->data = (u64)data_inv << 34 |
		    (u64)data     << 26 |
			 addr_inv << 13 |
			 addr;
	out->mask = (u64)data_m << 34 |
		    (u64)data_m << 26 |
			 addr_m << 13 |
			 addr_m;
	वापस 0;
पूर्ण

/* Sanyo decoder */
काष्ठा img_ir_decoder img_ir_sanyo = अणु
	.type = RC_PROTO_BIT_SANYO,
	.control = अणु
		.decoden = 1,
		.code_type = IMG_IR_CODETYPE_PULSEDIST,
	पूर्ण,
	/* मुख्य timings */
	.unit = 562500, /* 562.5 us */
	.timings = अणु
		/* leader symbol */
		.ldr = अणु
			.pulse = अणु 16	/* 9ms */ पूर्ण,
			.space = अणु 8	/* 4.5ms */ पूर्ण,
		पूर्ण,
		/* 0 symbol */
		.s00 = अणु
			.pulse = अणु 1	/* 562.5 us */ पूर्ण,
			.space = अणु 1	/* 562.5 us */ पूर्ण,
		पूर्ण,
		/* 1 symbol */
		.s01 = अणु
			.pulse = अणु 1	/* 562.5 us */ पूर्ण,
			.space = अणु 3	/* 1687.5 us */ पूर्ण,
		पूर्ण,
		/* मुक्त समय */
		.ft = अणु
			.minlen = 42,
			.maxlen = 42,
			.ft_min = 10,	/* 5.625 ms */
		पूर्ण,
	पूर्ण,
	/* repeat codes */
	.repeat = 108,			/* 108 ms */
	.rtimings = अणु
		/* leader symbol */
		.ldr = अणु
			.space = अणु 4	/* 2.25 ms */ पूर्ण,
		पूर्ण,
		/* मुक्त समय */
		.ft = अणु
			.minlen = 0,	/* repeat code has no data */
			.maxlen = 0,
		पूर्ण,
	पूर्ण,
	/* scancode logic */
	.scancode = img_ir_sanyo_scancode,
	.filter = img_ir_sanyo_filter,
पूर्ण;
