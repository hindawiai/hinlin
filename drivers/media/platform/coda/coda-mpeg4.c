<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Coda multi-standard codec IP - MPEG-4 helper functions
 *
 * Copyright (C) 2019 Pengutronix, Philipp Zabel
 */

#समावेश <linux/kernel.h>
#समावेश <linux/videodev2.h>

#समावेश "coda.h"

पूर्णांक coda_mpeg4_profile(पूर्णांक profile_idc)
अणु
	चयन (profile_idc) अणु
	हाल 0:
		वापस V4L2_MPEG_VIDEO_MPEG4_PROखाता_SIMPLE;
	हाल 15:
		वापस V4L2_MPEG_VIDEO_MPEG4_PROखाता_ADVANCED_SIMPLE;
	हाल 2:
		वापस V4L2_MPEG_VIDEO_MPEG4_PROखाता_CORE;
	हाल 1:
		वापस V4L2_MPEG_VIDEO_MPEG4_PROखाता_SIMPLE_SCALABLE;
	हाल 11:
		वापस V4L2_MPEG_VIDEO_MPEG4_PROखाता_ADVANCED_CODING_EFFICIENCY;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

पूर्णांक coda_mpeg4_level(पूर्णांक level_idc)
अणु
	चयन (level_idc) अणु
	हाल 0:
		वापस V4L2_MPEG_VIDEO_MPEG4_LEVEL_0;
	हाल 1:
		वापस V4L2_MPEG_VIDEO_MPEG4_LEVEL_1;
	हाल 2:
		वापस V4L2_MPEG_VIDEO_MPEG4_LEVEL_2;
	हाल 3:
		वापस V4L2_MPEG_VIDEO_MPEG4_LEVEL_3;
	हाल 4:
		वापस V4L2_MPEG_VIDEO_MPEG4_LEVEL_4;
	हाल 5:
		वापस V4L2_MPEG_VIDEO_MPEG4_LEVEL_5;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

/*
 * Check अगर the buffer starts with the MPEG-4 visual object sequence and visual
 * object headers, क्रम example:
 *
 *   00 00 01 b0 f1
 *   00 00 01 b5 a9 13 00 00 01 00 00 00 01 20 08
 *               d4 8d 88 00 f5 04 04 08 14 30 3f
 *
 * Returns the detected header size in bytes or 0.
 */
u32 coda_mpeg4_parse_headers(काष्ठा coda_ctx *ctx, u8 *buf, u32 size)
अणु
	अटल स्थिर u8 vos_start[4] = अणु 0x00, 0x00, 0x01, 0xb0 पूर्ण;
	अटल स्थिर जोड़ अणु
		u8 vo_start[4];
		u8 start_code_prefix[3];
	पूर्ण u = अणु अणु 0x00, 0x00, 0x01, 0xb5 पूर्ण पूर्ण;

	अगर (size < 30 ||
	    स_भेद(buf, vos_start, 4) != 0 ||
	    स_भेद(buf + 5, u.vo_start, 4) != 0)
		वापस 0;

	अगर (size == 30 ||
	    (size >= 33 && स_भेद(buf + 30, u.start_code_prefix, 3) == 0))
		वापस 30;

	अगर (size == 31 ||
	    (size >= 34 && स_भेद(buf + 31, u.start_code_prefix, 3) == 0))
		वापस 31;

	अगर (size == 32 ||
	    (size >= 35 && स_भेद(buf + 32, u.start_code_prefix, 3) == 0))
		वापस 32;

	वापस 0;
पूर्ण
