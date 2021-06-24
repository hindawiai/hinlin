<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *
 *  Copyright (C) 2005 Mike Isely <isely@pobox.com>
 *  Copyright (C) 2004 Aurelien Alleaume <slts@मुक्त.fr>
 */

/*

   This source file is specअगरically deचिन्हित to पूर्णांकerface with the
   cx2584x, in kernels 2.6.16 or newer.

*/

#समावेश "pvrusb2-cx2584x-v4l.h"


#समावेश "pvrusb2-hdw-internal.h"
#समावेश "pvrusb2-debug.h"
#समावेश <media/drv-पूर्णांकf/cx25840.h>
#समावेश <linux/videodev2.h>
#समावेश <media/v4l2-common.h>
#समावेश <linux/त्रुटिसं.स>


काष्ठा routing_scheme_item अणु
	पूर्णांक vid;
	पूर्णांक aud;
पूर्ण;

काष्ठा routing_scheme अणु
	स्थिर काष्ठा routing_scheme_item *def;
	अचिन्हित पूर्णांक cnt;
पूर्ण;

अटल स्थिर काष्ठा routing_scheme_item routing_scheme0[] = अणु
	[PVR2_CVAL_INPUT_TV] = अणु
		.vid = CX25840_COMPOSITE7,
		.aud = CX25840_AUDIO8,
	पूर्ण,
	[PVR2_CVAL_INPUT_RADIO] = अणु /* Treat the same as composite */
		.vid = CX25840_COMPOSITE3,
		.aud = CX25840_AUDIO_SERIAL,
	पूर्ण,
	[PVR2_CVAL_INPUT_COMPOSITE] = अणु
		.vid = CX25840_COMPOSITE3,
		.aud = CX25840_AUDIO_SERIAL,
	पूर्ण,
	[PVR2_CVAL_INPUT_SVIDEO] = अणु
		.vid = CX25840_SVIDEO1,
		.aud = CX25840_AUDIO_SERIAL,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा routing_scheme routing_def0 = अणु
	.def = routing_scheme0,
	.cnt = ARRAY_SIZE(routing_scheme0),
पूर्ण;

/* Specअगरic to gotview device */
अटल स्थिर काष्ठा routing_scheme_item routing_schemegv[] = अणु
	[PVR2_CVAL_INPUT_TV] = अणु
		.vid = CX25840_COMPOSITE2,
		.aud = CX25840_AUDIO5,
	पूर्ण,
	[PVR2_CVAL_INPUT_RADIO] = अणु
		/* line-in is used क्रम radio and composite.  A GPIO is
		   used to चयन between the two choices. */
		.vid = CX25840_COMPOSITE1,
		.aud = CX25840_AUDIO_SERIAL,
	पूर्ण,
	[PVR2_CVAL_INPUT_COMPOSITE] = अणु
		.vid = CX25840_COMPOSITE1,
		.aud = CX25840_AUDIO_SERIAL,
	पूर्ण,
	[PVR2_CVAL_INPUT_SVIDEO] = अणु
		.vid = (CX25840_SVIDEO_LUMA3|CX25840_SVIDEO_CHROMA4),
		.aud = CX25840_AUDIO_SERIAL,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा routing_scheme routing_defgv = अणु
	.def = routing_schemegv,
	.cnt = ARRAY_SIZE(routing_schemegv),
पूर्ण;

/* Specअगरic to grअसलter av400 device */
अटल स्थिर काष्ठा routing_scheme_item routing_schemeav400[] = अणु
	[PVR2_CVAL_INPUT_COMPOSITE] = अणु
		.vid = CX25840_COMPOSITE1,
		.aud = CX25840_AUDIO_SERIAL,
	पूर्ण,
	[PVR2_CVAL_INPUT_SVIDEO] = अणु
		.vid = (CX25840_SVIDEO_LUMA2|CX25840_SVIDEO_CHROMA4),
		.aud = CX25840_AUDIO_SERIAL,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा routing_scheme routing_defav400 = अणु
	.def = routing_schemeav400,
	.cnt = ARRAY_SIZE(routing_schemeav400),
पूर्ण;

अटल स्थिर काष्ठा routing_scheme_item routing_scheme160xxx[] = अणु
	[PVR2_CVAL_INPUT_TV] = अणु
		.vid = CX25840_COMPOSITE7,
		.aud = CX25840_AUDIO8,
	पूर्ण,
	[PVR2_CVAL_INPUT_RADIO] = अणु
		.vid = CX25840_COMPOSITE4,
		.aud = CX25840_AUDIO6,
	पूर्ण,
	[PVR2_CVAL_INPUT_COMPOSITE] = अणु
		.vid = CX25840_COMPOSITE3,
		.aud = CX25840_AUDIO_SERIAL,
	पूर्ण,
	[PVR2_CVAL_INPUT_SVIDEO] = अणु
		.vid = CX25840_SVIDEO1,
		.aud = CX25840_AUDIO_SERIAL,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा routing_scheme routing_def160xxx = अणु
	.def = routing_scheme160xxx,
	.cnt = ARRAY_SIZE(routing_scheme160xxx),
पूर्ण;

अटल स्थिर काष्ठा routing_scheme *routing_schemes[] = अणु
	[PVR2_ROUTING_SCHEME_HAUPPAUGE] = &routing_def0,
	[PVR2_ROUTING_SCHEME_GOTVIEW] = &routing_defgv,
	[PVR2_ROUTING_SCHEME_AV400] = &routing_defav400,
	[PVR2_ROUTING_SCHEME_HAUP160XXX] = &routing_def160xxx,
पूर्ण;

व्योम pvr2_cx25840_subdev_update(काष्ठा pvr2_hdw *hdw, काष्ठा v4l2_subdev *sd)
अणु
	pvr2_trace(PVR2_TRACE_CHIPS, "subdev cx2584x update...");
	अगर (hdw->input_dirty || hdw->क्रमce_dirty) अणु
		क्रमागत cx25840_video_input vid_input;
		क्रमागत cx25840_audio_input aud_input;
		स्थिर काष्ठा routing_scheme *sp;
		अचिन्हित पूर्णांक sid = hdw->hdw_desc->संकेत_routing_scheme;

		sp = (sid < ARRAY_SIZE(routing_schemes)) ?
			routing_schemes[sid] : शून्य;
		अगर ((sp == शून्य) ||
		    (hdw->input_val < 0) ||
		    (hdw->input_val >= sp->cnt)) अणु
			pvr2_trace(PVR2_TRACE_ERROR_LEGS,
				   "*** WARNING *** subdev cx2584x set_input: Invalid routing scheme (%u) and/or input (%d)",
				   sid, hdw->input_val);
			वापस;
		पूर्ण
		vid_input = sp->def[hdw->input_val].vid;
		aud_input = sp->def[hdw->input_val].aud;
		pvr2_trace(PVR2_TRACE_CHIPS,
			   "subdev cx2584x set_input vid=0x%x aud=0x%x",
			   vid_input, aud_input);
		sd->ops->video->s_routing(sd, (u32)vid_input, 0, 0);
		sd->ops->audio->s_routing(sd, (u32)aud_input, 0, 0);
	पूर्ण
पूर्ण
