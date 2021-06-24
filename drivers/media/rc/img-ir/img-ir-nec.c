<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * ImgTec IR Decoder setup क्रम NEC protocol.
 *
 * Copyright 2010-2014 Imagination Technologies Ltd.
 */

#समावेश "img-ir-hw.h"
#समावेश <linux/bitrev.h>
#समावेश <linux/log2.h>

/* Convert NEC data to a scancode */
अटल पूर्णांक img_ir_nec_scancode(पूर्णांक len, u64 raw, u64 enabled_protocols,
			       काष्ठा img_ir_scancode_req *request)
अणु
	अचिन्हित पूर्णांक addr, addr_inv, data, data_inv;
	/* a repeat code has no data */
	अगर (!len)
		वापस IMG_IR_REPEATCODE;
	अगर (len != 32)
		वापस -EINVAL;
	/* raw encoding: ddDDaaAA */
	addr     = (raw >>  0) & 0xff;
	addr_inv = (raw >>  8) & 0xff;
	data     = (raw >> 16) & 0xff;
	data_inv = (raw >> 24) & 0xff;
	अगर ((data_inv ^ data) != 0xff) अणु
		/* 32-bit NEC (used by Apple and TiVo remotes) */
		/* scan encoding: as transmitted, MSBit = first received bit */
		request->scancode = bitrev8(addr)     << 24 |
				bitrev8(addr_inv) << 16 |
				bitrev8(data)     <<  8 |
				bitrev8(data_inv);
		request->protocol = RC_PROTO_NEC32;
	पूर्ण अन्यथा अगर ((addr_inv ^ addr) != 0xff) अणु
		/* Extended NEC */
		/* scan encoding: AAaaDD */
		request->scancode = addr     << 16 |
				addr_inv <<  8 |
				data;
		request->protocol = RC_PROTO_NECX;
	पूर्ण अन्यथा अणु
		/* Normal NEC */
		/* scan encoding: AADD */
		request->scancode = addr << 8 |
				data;
		request->protocol = RC_PROTO_NEC;
	पूर्ण
	वापस IMG_IR_SCANCODE;
पूर्ण

/* Convert NEC scancode to NEC data filter */
अटल पूर्णांक img_ir_nec_filter(स्थिर काष्ठा rc_scancode_filter *in,
			     काष्ठा img_ir_filter *out, u64 protocols)
अणु
	अचिन्हित पूर्णांक addr, addr_inv, data, data_inv;
	अचिन्हित पूर्णांक addr_m, addr_inv_m, data_m, data_inv_m;

	data       = in->data & 0xff;
	data_m     = in->mask & 0xff;

	protocols &= RC_PROTO_BIT_NEC | RC_PROTO_BIT_NECX | RC_PROTO_BIT_NEC32;

	/*
	 * If only one bit is set, we were requested to करो an exact
	 * protocol. This should be the हाल क्रम wakeup filters; क्रम
	 * normal filters, guess the protocol from the scancode.
	 */
	अगर (!is_घातer_of_2(protocols)) अणु
		अगर ((in->data | in->mask) & 0xff000000)
			protocols = RC_PROTO_BIT_NEC32;
		अन्यथा अगर ((in->data | in->mask) & 0x00ff0000)
			protocols = RC_PROTO_BIT_NECX;
		अन्यथा
			protocols = RC_PROTO_BIT_NEC;
	पूर्ण

	अगर (protocols == RC_PROTO_BIT_NEC32) अणु
		/* 32-bit NEC (used by Apple and TiVo remotes) */
		/* scan encoding: as transmitted, MSBit = first received bit */
		addr       = bitrev8(in->data >> 24);
		addr_m     = bitrev8(in->mask >> 24);
		addr_inv   = bitrev8(in->data >> 16);
		addr_inv_m = bitrev8(in->mask >> 16);
		data       = bitrev8(in->data >>  8);
		data_m     = bitrev8(in->mask >>  8);
		data_inv   = bitrev8(in->data >>  0);
		data_inv_m = bitrev8(in->mask >>  0);
	पूर्ण अन्यथा अगर (protocols == RC_PROTO_BIT_NECX) अणु
		/* Extended NEC */
		/* scan encoding AAaaDD */
		addr       = (in->data >> 16) & 0xff;
		addr_m     = (in->mask >> 16) & 0xff;
		addr_inv   = (in->data >>  8) & 0xff;
		addr_inv_m = (in->mask >>  8) & 0xff;
		data_inv   = data ^ 0xff;
		data_inv_m = data_m;
	पूर्ण अन्यथा अणु
		/* Normal NEC */
		/* scan encoding: AADD */
		addr       = (in->data >>  8) & 0xff;
		addr_m     = (in->mask >>  8) & 0xff;
		addr_inv   = addr ^ 0xff;
		addr_inv_m = addr_m;
		data_inv   = data ^ 0xff;
		data_inv_m = data_m;
	पूर्ण

	/* raw encoding: ddDDaaAA */
	out->data = data_inv << 24 |
		    data     << 16 |
		    addr_inv <<  8 |
		    addr;
	out->mask = data_inv_m << 24 |
		    data_m     << 16 |
		    addr_inv_m <<  8 |
		    addr_m;
	वापस 0;
पूर्ण

/*
 * NEC decoder
 * See also http://www.sbprojects.com/knowledge/ir/nec.php
 *        http://wiki.altium.com/display/ADOH/NEC+Infrared+Transmission+Protocol
 */
काष्ठा img_ir_decoder img_ir_nec = अणु
	.type = RC_PROTO_BIT_NEC | RC_PROTO_BIT_NECX | RC_PROTO_BIT_NEC32,
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
			.minlen = 32,
			.maxlen = 32,
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
	.scancode = img_ir_nec_scancode,
	.filter = img_ir_nec_filter,
पूर्ण;
