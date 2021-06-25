<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) STMicroelectronics SA 2015
 * Authors: Hugues Fruchet <hugues.fruchet@st.com>
 *          Fabrice Lecoultre <fabrice.lecoultre@st.com>
 *          क्रम STMicroelectronics.
 */

#समावेश "delta.h"
#समावेश "delta-debug.h"

अक्षर *delta_streaminfo_str(काष्ठा delta_streaminfo *s, अक्षर *str,
			   अचिन्हित पूर्णांक len)
अणु
	अगर (!s)
		वापस शून्य;

	snम_लिखो(str, len,
		 "%4.4s %dx%d %s %s dpb=%d %s %s %s%dx%d@(%d,%d) %s%d/%d",
		 (अक्षर *)&s->streamक्रमmat, s->width, s->height,
		 s->profile, s->level, s->dpb,
		 (s->field == V4L2_FIELD_NONE) ? "progressive" : "interlaced",
		 s->other,
		 s->flags & DELTA_STREAMINFO_FLAG_CROP ? "crop=" : "",
		 s->crop.width, s->crop.height,
		 s->crop.left, s->crop.top,
		 s->flags & DELTA_STREAMINFO_FLAG_PIXELASPECT ? "par=" : "",
		 s->pixelaspect.numerator,
		 s->pixelaspect.denominator);

	वापस str;
पूर्ण

अक्षर *delta_frameinfo_str(काष्ठा delta_frameinfo *f, अक्षर *str,
			  अचिन्हित पूर्णांक len)
अणु
	अगर (!f)
		वापस शून्य;

	snम_लिखो(str, len,
		 "%4.4s %dx%d aligned %dx%d %s %s%dx%d@(%d,%d) %s%d/%d",
		 (अक्षर *)&f->pixelक्रमmat, f->width, f->height,
		 f->aligned_width, f->aligned_height,
		 (f->field == V4L2_FIELD_NONE) ? "progressive" : "interlaced",
		 f->flags & DELTA_STREAMINFO_FLAG_CROP ? "crop=" : "",
		 f->crop.width, f->crop.height,
		 f->crop.left, f->crop.top,
		 f->flags & DELTA_STREAMINFO_FLAG_PIXELASPECT ? "par=" : "",
		 f->pixelaspect.numerator,
		 f->pixelaspect.denominator);

	वापस str;
पूर्ण

व्योम delta_trace_summary(काष्ठा delta_ctx *ctx)
अणु
	काष्ठा delta_dev *delta = ctx->dev;
	काष्ठा delta_streaminfo *s = &ctx->streaminfo;
	अचिन्हित अक्षर str[100] = "";

	अगर (!(ctx->flags & DELTA_FLAG_STREAMINFO))
		वापस;

	dev_dbg(delta->dev, "%s %s, %d frames decoded, %d frames output, %d frames dropped, %d stream errors, %d decode errors",
		ctx->name,
		delta_streaminfo_str(s, str, माप(str)),
		ctx->decoded_frames,
		ctx->output_frames,
		ctx->dropped_frames,
		ctx->stream_errors,
		ctx->decode_errors);
पूर्ण
