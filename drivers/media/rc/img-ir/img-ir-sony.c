<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * ImgTec IR Decoder setup क्रम Sony (SIRC) protocol.
 *
 * Copyright 2012-2014 Imagination Technologies Ltd.
 */

#समावेश "img-ir-hw.h"

/* Convert Sony data to a scancode */
अटल पूर्णांक img_ir_sony_scancode(पूर्णांक len, u64 raw, u64 enabled_protocols,
				काष्ठा img_ir_scancode_req *request)
अणु
	अचिन्हित पूर्णांक dev, subdev, func;

	चयन (len) अणु
	हाल 12:
		अगर (!(enabled_protocols & RC_PROTO_BIT_SONY12))
			वापस -EINVAL;
		func   = raw & 0x7f;	/* first 7 bits */
		raw    >>= 7;
		dev    = raw & 0x1f;	/* next 5 bits */
		subdev = 0;
		request->protocol = RC_PROTO_SONY12;
		अवरोध;
	हाल 15:
		अगर (!(enabled_protocols & RC_PROTO_BIT_SONY15))
			वापस -EINVAL;
		func   = raw & 0x7f;	/* first 7 bits */
		raw    >>= 7;
		dev    = raw & 0xff;	/* next 8 bits */
		subdev = 0;
		request->protocol = RC_PROTO_SONY15;
		अवरोध;
	हाल 20:
		अगर (!(enabled_protocols & RC_PROTO_BIT_SONY20))
			वापस -EINVAL;
		func   = raw & 0x7f;	/* first 7 bits */
		raw    >>= 7;
		dev    = raw & 0x1f;	/* next 5 bits */
		raw    >>= 5;
		subdev = raw & 0xff;	/* next 8 bits */
		request->protocol = RC_PROTO_SONY20;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	request->scancode = dev << 16 | subdev << 8 | func;
	वापस IMG_IR_SCANCODE;
पूर्ण

/* Convert NEC scancode to NEC data filter */
अटल पूर्णांक img_ir_sony_filter(स्थिर काष्ठा rc_scancode_filter *in,
			      काष्ठा img_ir_filter *out, u64 protocols)
अणु
	अचिन्हित पूर्णांक dev, subdev, func;
	अचिन्हित पूर्णांक dev_m, subdev_m, func_m;
	अचिन्हित पूर्णांक len = 0;

	dev      = (in->data >> 16) & 0xff;
	dev_m    = (in->mask >> 16) & 0xff;
	subdev   = (in->data >> 8)  & 0xff;
	subdev_m = (in->mask >> 8)  & 0xff;
	func     = (in->data >> 0)  & 0x7f;
	func_m   = (in->mask >> 0)  & 0x7f;

	protocols &= RC_PROTO_BIT_SONY12 | RC_PROTO_BIT_SONY15 |
							RC_PROTO_BIT_SONY20;

	/*
	 * If only one bit is set, we were requested to करो an exact
	 * protocol. This should be the हाल क्रम wakeup filters; क्रम
	 * normal filters, guess the protocol from the scancode.
	 */
	अगर (!is_घातer_of_2(protocols)) अणु
		अगर (subdev & subdev_m)
			protocols = RC_PROTO_BIT_SONY20;
		अन्यथा अगर (dev & dev_m & 0xe0)
			protocols = RC_PROTO_BIT_SONY15;
		अन्यथा
			protocols = RC_PROTO_BIT_SONY12;
	पूर्ण

	अगर (protocols == RC_PROTO_BIT_SONY20) अणु
		/* can't encode subdev and higher device bits */
		अगर (dev & dev_m & 0xe0)
			वापस -EINVAL;
		len = 20;
		dev_m &= 0x1f;
	पूर्ण अन्यथा अगर (protocols == RC_PROTO_BIT_SONY15) अणु
		len = 15;
		subdev_m = 0;
	पूर्ण अन्यथा अणु
		/*
		 * The hardware mask cannot distinguish high device bits and low
		 * extended bits, so logically AND those bits of the masks
		 * together.
		 */
		subdev_m &= (dev_m >> 5) | 0xf8;
		dev_m &= 0x1f;
	पूर्ण

	/* ensure there aren't any bits straying between fields */
	dev &= dev_m;
	subdev &= subdev_m;

	/* ग_लिखो the hardware filter */
	out->data = func          |
		    dev      << 7 |
		    subdev   << 15;
	out->mask = func_m        |
		    dev_m    << 7 |
		    subdev_m << 15;

	अगर (len) अणु
		out->minlen = len;
		out->maxlen = len;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Sony SIRC decoder
 * See also http://www.sbprojects.com/knowledge/ir/sirc.php
 *          http://picprojects.org.uk/projects/sirc/sonysirc.pdf
 */
काष्ठा img_ir_decoder img_ir_sony = अणु
	.type = RC_PROTO_BIT_SONY12 | RC_PROTO_BIT_SONY15 | RC_PROTO_BIT_SONY20,
	.control = अणु
		.decoden = 1,
		.code_type = IMG_IR_CODETYPE_PULSELEN,
	पूर्ण,
	/* मुख्य timings */
	.unit = 600000, /* 600 us */
	.timings = अणु
		/* leader symbol */
		.ldr = अणु
			.pulse = अणु 4	/* 2.4 ms */ पूर्ण,
			.space = अणु 1	/* 600 us */ पूर्ण,
		पूर्ण,
		/* 0 symbol */
		.s00 = अणु
			.pulse = अणु 1	/* 600 us */ पूर्ण,
			.space = अणु 1	/* 600 us */ पूर्ण,
		पूर्ण,
		/* 1 symbol */
		.s01 = अणु
			.pulse = अणु 2	/* 1.2 ms */ पूर्ण,
			.space = अणु 1	/* 600 us */ पूर्ण,
		पूर्ण,
		/* मुक्त समय */
		.ft = अणु
			.minlen = 12,
			.maxlen = 20,
			.ft_min = 10,	/* 6 ms */
		पूर्ण,
	पूर्ण,
	/* scancode logic */
	.scancode = img_ir_sony_scancode,
	.filter = img_ir_sony_filter,
पूर्ण;
