<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) STMicroelectronics SA 2015
 * Authors: Yannick Fertre <yannick.fertre@st.com>
 *          Hugues Fruchet <hugues.fruchet@st.com>
 */

#समावेश <linux/debugfs.h>

#समावेश "hva.h"
#समावेश "hva-hw.h"

अटल व्योम क्रमmat_ctx(काष्ठा seq_file *s, काष्ठा hva_ctx *ctx)
अणु
	काष्ठा hva_streaminfo *stream = &ctx->streaminfo;
	काष्ठा hva_frameinfo *frame = &ctx->frameinfo;
	काष्ठा hva_controls *ctrls = &ctx->ctrls;
	काष्ठा hva_ctx_dbg *dbg = &ctx->dbg;
	u32 bitrate_mode, aspect, entropy, vui_sar, sei_fp;

	seq_म_लिखो(s, "|-%s\n  |\n", ctx->name);

	seq_म_लिखो(s, "  |-[%sframe info]\n",
		   ctx->flags & HVA_FLAG_FRAMEINFO ? "" : "default ");
	seq_म_लिखो(s, "  | |- pixel format=%4.4s\n"
		      "  | |- wxh=%dx%d\n"
		      "  | |- wxh (w/ encoder alignment constraint)=%dx%d\n"
		      "  |\n",
		      (अक्षर *)&frame->pixelक्रमmat,
		      frame->width, frame->height,
		      frame->aligned_width, frame->aligned_height);

	seq_म_लिखो(s, "  |-[%sstream info]\n",
		   ctx->flags & HVA_FLAG_STREAMINFO ? "" : "default ");
	seq_म_लिखो(s, "  | |- stream format=%4.4s\n"
		      "  | |- wxh=%dx%d\n"
		      "  | |- %s\n"
		      "  | |- %s\n"
		      "  |\n",
		      (अक्षर *)&stream->streamक्रमmat,
		      stream->width, stream->height,
		      stream->profile, stream->level);

	bitrate_mode = V4L2_CID_MPEG_VIDEO_BITRATE_MODE;
	aspect = V4L2_CID_MPEG_VIDEO_ASPECT;
	seq_माला_दो(s, "  |-[parameters]\n");
	seq_म_लिखो(s, "  | |- %s\n"
		      "  | |- bitrate=%d bps\n"
		      "  | |- GOP size=%d\n"
		      "  | |- video aspect=%s\n"
		      "  | |- framerate=%d/%d\n",
		      v4l2_ctrl_get_menu(bitrate_mode)[ctrls->bitrate_mode],
		      ctrls->bitrate,
		      ctrls->gop_size,
		      v4l2_ctrl_get_menu(aspect)[ctrls->aspect],
		      ctrls->समय_per_frame.denominator,
		      ctrls->समय_per_frame.numerator);

	entropy = V4L2_CID_MPEG_VIDEO_H264_ENTROPY_MODE;
	vui_sar = V4L2_CID_MPEG_VIDEO_H264_VUI_SAR_IDC;
	sei_fp =  V4L2_CID_MPEG_VIDEO_H264_SEI_FP_ARRANGEMENT_TYPE;
	अगर (stream->streamक्रमmat == V4L2_PIX_FMT_H264) अणु
		seq_म_लिखो(s, "  | |- %s entropy mode\n"
			      "  | |- CPB size=%d kB\n"
			      "  | |- DCT8x8 enable=%s\n"
			      "  | |- qpmin=%d\n"
			      "  | |- qpmax=%d\n"
			      "  | |- PAR enable=%s\n"
			      "  | |- PAR id=%s\n"
			      "  | |- SEI frame packing enable=%s\n"
			      "  | |- SEI frame packing type=%s\n",
			      v4l2_ctrl_get_menu(entropy)[ctrls->entropy_mode],
			      ctrls->cpb_size,
			      ctrls->dct8x8 ? "true" : "false",
			      ctrls->qpmin,
			      ctrls->qpmax,
			      ctrls->vui_sar ? "true" : "false",
			      v4l2_ctrl_get_menu(vui_sar)[ctrls->vui_sar_idc],
			      ctrls->sei_fp ? "true" : "false",
			      v4l2_ctrl_get_menu(sei_fp)[ctrls->sei_fp_type]);
	पूर्ण

	अगर (ctx->sys_errors || ctx->encode_errors || ctx->frame_errors) अणु
		seq_माला_दो(s, "  |\n  |-[errors]\n");
		seq_म_लिखो(s, "  | |- system=%d\n"
			      "  | |- encoding=%d\n"
			      "  | |- frame=%d\n",
			      ctx->sys_errors,
			      ctx->encode_errors,
			      ctx->frame_errors);
	पूर्ण

	seq_माला_दो(s, "  |\n  |-[performances]\n");
	seq_म_लिखो(s, "  | |- frames encoded=%d\n"
		      "  | |- avg HW processing duration (0.1ms)=%d [min=%d, max=%d]\n"
		      "  | |- avg encoding period (0.1ms)=%d [min=%d, max=%d]\n"
		      "  | |- avg fps (0.1Hz)=%d\n"
		      "  | |- max reachable fps (0.1Hz)=%d\n"
		      "  | |- avg bitrate (kbps)=%d [min=%d, max=%d]\n"
		      "  | |- last bitrate (kbps)=%d\n",
		      dbg->cnt_duration,
		      dbg->avg_duration,
		      dbg->min_duration,
		      dbg->max_duration,
		      dbg->avg_period,
		      dbg->min_period,
		      dbg->max_period,
		      dbg->avg_fps,
		      dbg->max_fps,
		      dbg->avg_bitrate,
		      dbg->min_bitrate,
		      dbg->max_bitrate,
		      dbg->last_bitrate);
पूर्ण

/*
 * perक्रमmance debug info
 */
व्योम hva_dbg_perf_begin(काष्ठा hva_ctx *ctx)
अणु
	u64 भाग;
	u32 period;
	u32 bitrate;
	काष्ठा hva_ctx_dbg *dbg = &ctx->dbg;
	kसमय_प्रकार prev = dbg->begin;

	dbg->begin = kसमय_get();

	अगर (dbg->is_valid_period) अणु
		/* encoding period */
		भाग = (u64)kसमय_us_delta(dbg->begin, prev);
		करो_भाग(भाग, 100);
		period = (u32)भाग;
		dbg->min_period = min(period, dbg->min_period);
		dbg->max_period = max(period, dbg->max_period);
		dbg->total_period += period;
		dbg->cnt_period++;

		/*
		 * minimum and maximum bitrates are based on the
		 * encoding period values upon a winकरोw of 32 samples
		 */
		dbg->winकरोw_duration += period;
		dbg->cnt_winकरोw++;
		अगर (dbg->cnt_winकरोw >= 32) अणु
			/*
			 * bitrate in kbps = (size * 8 / 1000) /
			 *                   (duration / 10000)
			 *                 = size * 80 / duration
			 */
			अगर (dbg->winकरोw_duration > 0) अणु
				भाग = (u64)dbg->winकरोw_stream_size * 80;
				करो_भाग(भाग, dbg->winकरोw_duration);
				bitrate = (u32)भाग;
				dbg->last_bitrate = bitrate;
				dbg->min_bitrate = min(bitrate,
						       dbg->min_bitrate);
				dbg->max_bitrate = max(bitrate,
						       dbg->max_bitrate);
			पूर्ण
			dbg->winकरोw_stream_size = 0;
			dbg->winकरोw_duration = 0;
			dbg->cnt_winकरोw = 0;
		पूर्ण
	पूर्ण

	/*
	 * filter sequences valid क्रम perक्रमmance:
	 * - begin/begin (no stream available) is an invalid sequence
	 * - begin/end is a valid sequence
	 */
	dbg->is_valid_period = false;
पूर्ण

व्योम hva_dbg_perf_end(काष्ठा hva_ctx *ctx, काष्ठा hva_stream *stream)
अणु
	काष्ठा device *dev = ctx_to_dev(ctx);
	u64 भाग;
	u32 duration;
	u32 bytesused;
	u32 बारtamp;
	काष्ठा hva_ctx_dbg *dbg = &ctx->dbg;
	kसमय_प्रकार end = kसमय_get();

	/* stream bytesused and बारtamp in us */
	bytesused = vb2_get_plane_payload(&stream->vbuf.vb2_buf, 0);
	भाग = stream->vbuf.vb2_buf.बारtamp;
	करो_भाग(भाग, 1000);
	बारtamp = (u32)भाग;

	/* encoding duration */
	भाग = (u64)kसमय_us_delta(end, dbg->begin);

	dev_dbg(dev,
		"%s perf stream[%d] dts=%d encoded using %d bytes in %d us",
		ctx->name,
		stream->vbuf.sequence,
		बारtamp,
		bytesused, (u32)भाग);

	करो_भाग(भाग, 100);
	duration = (u32)भाग;

	dbg->min_duration = min(duration, dbg->min_duration);
	dbg->max_duration = max(duration, dbg->max_duration);
	dbg->total_duration += duration;
	dbg->cnt_duration++;

	/*
	 * the average bitrate is based on the total stream size
	 * and the total encoding periods
	 */
	dbg->total_stream_size += bytesused;
	dbg->winकरोw_stream_size += bytesused;

	dbg->is_valid_period = true;
पूर्ण

अटल व्योम hva_dbg_perf_compute(काष्ठा hva_ctx *ctx)
अणु
	u64 भाग;
	काष्ठा hva_ctx_dbg *dbg = &ctx->dbg;

	अगर (dbg->cnt_duration > 0) अणु
		भाग = (u64)dbg->total_duration;
		करो_भाग(भाग, dbg->cnt_duration);
		dbg->avg_duration = (u32)भाग;
	पूर्ण अन्यथा अणु
		dbg->avg_duration = 0;
	पूर्ण

	अगर (dbg->total_duration > 0) अणु
		भाग = (u64)dbg->cnt_duration * 100000;
		करो_भाग(भाग, dbg->total_duration);
		dbg->max_fps = (u32)भाग;
	पूर्ण अन्यथा अणु
		dbg->max_fps = 0;
	पूर्ण

	अगर (dbg->cnt_period > 0) अणु
		भाग = (u64)dbg->total_period;
		करो_भाग(भाग, dbg->cnt_period);
		dbg->avg_period = (u32)भाग;
	पूर्ण अन्यथा अणु
		dbg->avg_period = 0;
	पूर्ण

	अगर (dbg->total_period > 0) अणु
		भाग = (u64)dbg->cnt_period * 100000;
		करो_भाग(भाग, dbg->total_period);
		dbg->avg_fps = (u32)भाग;
	पूर्ण अन्यथा अणु
		dbg->avg_fps = 0;
	पूर्ण

	अगर (dbg->total_period > 0) अणु
		/*
		 * bitrate in kbps = (video size * 8 / 1000) /
		 *                   (video duration / 10000)
		 *                 = video size * 80 / video duration
		 */
		भाग = (u64)dbg->total_stream_size * 80;
		करो_भाग(भाग, dbg->total_period);
		dbg->avg_bitrate = (u32)भाग;
	पूर्ण अन्यथा अणु
		dbg->avg_bitrate = 0;
	पूर्ण
पूर्ण

/*
 * device debug info
 */

अटल पूर्णांक device_show(काष्ठा seq_file *s, व्योम *data)
अणु
	काष्ठा hva_dev *hva = s->निजी;

	seq_म_लिखो(s, "[%s]\n", hva->v4l2_dev.name);
	seq_म_लिखो(s, "registered as /dev/video%d\n", hva->vdev->num);

	वापस 0;
पूर्ण

अटल पूर्णांक encoders_show(काष्ठा seq_file *s, व्योम *data)
अणु
	काष्ठा hva_dev *hva = s->निजी;
	अचिन्हित पूर्णांक i = 0;

	seq_म_लिखो(s, "[encoders]\n|- %d registered encoders:\n",
		   hva->nb_of_encoders);

	जबतक (hva->encoders[i]) अणु
		seq_म_लिखो(s, "|- %s: %4.4s => %4.4s\n", hva->encoders[i]->name,
			   (अक्षर *)&hva->encoders[i]->pixelक्रमmat,
			   (अक्षर *)&hva->encoders[i]->streamक्रमmat);
		i++;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक last_show(काष्ठा seq_file *s, व्योम *data)
अणु
	काष्ठा hva_dev *hva = s->निजी;
	काष्ठा hva_ctx *last_ctx = &hva->dbg.last_ctx;

	अगर (last_ctx->flags & HVA_FLAG_STREAMINFO) अणु
		seq_माला_दो(s, "[last encoding]\n");

		hva_dbg_perf_compute(last_ctx);
		क्रमmat_ctx(s, last_ctx);
	पूर्ण अन्यथा अणु
		seq_माला_दो(s, "[no information recorded about last encoding]\n");
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक regs_show(काष्ठा seq_file *s, व्योम *data)
अणु
	काष्ठा hva_dev *hva = s->निजी;

	hva_hw_dump_regs(hva, s);

	वापस 0;
पूर्ण

#घोषणा hva_dbg_create_entry(name)					 \
	debugfs_create_file(#name, 0444, hva->dbg.debugfs_entry, hva, \
			    &name##_fops)

DEFINE_SHOW_ATTRIBUTE(device);
DEFINE_SHOW_ATTRIBUTE(encoders);
DEFINE_SHOW_ATTRIBUTE(last);
DEFINE_SHOW_ATTRIBUTE(regs);

व्योम hva_debugfs_create(काष्ठा hva_dev *hva)
अणु
	hva->dbg.debugfs_entry = debugfs_create_dir(HVA_NAME, शून्य);

	hva_dbg_create_entry(device);
	hva_dbg_create_entry(encoders);
	hva_dbg_create_entry(last);
	hva_dbg_create_entry(regs);
पूर्ण

व्योम hva_debugfs_हटाओ(काष्ठा hva_dev *hva)
अणु
	debugfs_हटाओ_recursive(hva->dbg.debugfs_entry);
	hva->dbg.debugfs_entry = शून्य;
पूर्ण

/*
 * context (instance) debug info
 */

अटल पूर्णांक ctx_show(काष्ठा seq_file *s, व्योम *data)
अणु
	काष्ठा hva_ctx *ctx = s->निजी;

	seq_म_लिखो(s, "[running encoding %d]\n", ctx->id);

	hva_dbg_perf_compute(ctx);
	क्रमmat_ctx(s, ctx);

	वापस 0;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(ctx);

व्योम hva_dbg_ctx_create(काष्ठा hva_ctx *ctx)
अणु
	काष्ठा hva_dev *hva = ctx->hva_dev;
	अक्षर name[4] = "";

	ctx->dbg.min_duration = अच_पूर्णांक_उच्च;
	ctx->dbg.min_period = अच_पूर्णांक_उच्च;
	ctx->dbg.min_bitrate = अच_पूर्णांक_उच्च;

	snम_लिखो(name, माप(name), "%d", hva->instance_id);

	ctx->dbg.debugfs_entry = debugfs_create_file(name, 0444,
						     hva->dbg.debugfs_entry,
						     ctx, &ctx_fops);
पूर्ण

व्योम hva_dbg_ctx_हटाओ(काष्ठा hva_ctx *ctx)
अणु
	काष्ठा hva_dev *hva = ctx->hva_dev;

	अगर (ctx->flags & HVA_FLAG_STREAMINFO)
		/* save context beक्रमe removing */
		स_नकल(&hva->dbg.last_ctx, ctx, माप(*ctx));

	debugfs_हटाओ(ctx->dbg.debugfs_entry);
पूर्ण
