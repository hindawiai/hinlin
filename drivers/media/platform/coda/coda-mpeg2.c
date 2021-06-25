<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Coda multi-standard codec IP - MPEG-2 helper functions
 *
 * Copyright (C) 2019 Pengutronix, Philipp Zabel
 */

#समावेश <linux/kernel.h>
#समावेश <linux/videodev2.h>
#समावेश "coda.h"

पूर्णांक coda_mpeg2_profile(पूर्णांक profile_idc)
अणु
	चयन (profile_idc) अणु
	हाल 5:
		वापस V4L2_MPEG_VIDEO_MPEG2_PROखाता_SIMPLE;
	हाल 4:
		वापस V4L2_MPEG_VIDEO_MPEG2_PROखाता_MAIN;
	हाल 3:
		वापस V4L2_MPEG_VIDEO_MPEG2_PROखाता_SNR_SCALABLE;
	हाल 2:
		वापस V4L2_MPEG_VIDEO_MPEG2_PROखाता_SPATIALLY_SCALABLE;
	हाल 1:
		वापस V4L2_MPEG_VIDEO_MPEG2_PROखाता_HIGH;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

पूर्णांक coda_mpeg2_level(पूर्णांक level_idc)
अणु
	चयन (level_idc) अणु
	हाल 10:
		वापस V4L2_MPEG_VIDEO_MPEG2_LEVEL_LOW;
	हाल 8:
		वापस V4L2_MPEG_VIDEO_MPEG2_LEVEL_MAIN;
	हाल 6:
		वापस V4L2_MPEG_VIDEO_MPEG2_LEVEL_HIGH_1440;
	हाल 4:
		वापस V4L2_MPEG_VIDEO_MPEG2_LEVEL_HIGH;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

/*
 * Check अगर the buffer starts with the MPEG-2 sequence header (with or without
 * quantization matrix) and extension header, क्रम example:
 *
 *   00 00 01 b3 2d 01 e0 34 08 8b a3 81
 *               10 11 11 12 12 12 13 13 13 13 14 14 14 14 14 15
 *               15 15 15 15 15 16 16 16 16 16 16 16 17 17 17 17
 *               17 17 17 17 18 18 18 19 18 18 18 19 1a 1a 1a 1a
 *               19 1b 1b 1b 1b 1b 1c 1c 1c 1c 1e 1e 1e 1f 1f 21
 *   00 00 01 b5 14 8a 00 01 00 00
 *
 * or:
 *
 *   00 00 01 b3 08 00 40 15 ff ff e0 28
 *   00 00 01 b5 14 8a 00 01 00 00
 *
 * Returns the detected header size in bytes or 0.
 */
u32 coda_mpeg2_parse_headers(काष्ठा coda_ctx *ctx, u8 *buf, u32 size)
अणु
	अटल स्थिर u8 sequence_header_start[4] = अणु 0x00, 0x00, 0x01, 0xb3 पूर्ण;
	अटल स्थिर जोड़ अणु
		u8 extension_start[4];
		u8 start_code_prefix[3];
	पूर्ण u = अणु अणु 0x00, 0x00, 0x01, 0xb5 पूर्ण पूर्ण;

	अगर (size < 22 ||
	    स_भेद(buf, sequence_header_start, 4) != 0)
		वापस 0;

	अगर ((size == 22 ||
	     (size >= 25 && स_भेद(buf + 22, u.start_code_prefix, 3) == 0)) &&
	    स_भेद(buf + 12, u.extension_start, 4) == 0)
		वापस 22;

	अगर ((size == 86 ||
	     (size > 89 && स_भेद(buf + 86, u.start_code_prefix, 3) == 0)) &&
	    स_भेद(buf + 76, u.extension_start, 4) == 0)
		वापस 86;

	वापस 0;
पूर्ण
