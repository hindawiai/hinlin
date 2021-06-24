<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *
 *  Copyright (C) 2005 Mike Isely <isely@pobox.com>
 *  Copyright (C) 2004 Aurelien Alleaume <slts@मुक्त.fr>
 */

#समावेश "pvrusb2-audio.h"
#समावेश "pvrusb2-hdw-internal.h"
#समावेश "pvrusb2-debug.h"
#समावेश <linux/videodev2.h>
#समावेश <media/drv-पूर्णांकf/msp3400.h>
#समावेश <media/v4l2-common.h>


काष्ठा routing_scheme अणु
	स्थिर पूर्णांक *def;
	अचिन्हित पूर्णांक cnt;
पूर्ण;

अटल स्थिर पूर्णांक routing_scheme0[] = अणु
	[PVR2_CVAL_INPUT_TV]        = MSP_INPUT_DEFAULT,
	[PVR2_CVAL_INPUT_RADIO]     = MSP_INPUT(MSP_IN_SCART2,
						MSP_IN_TUNER1,
						MSP_DSP_IN_SCART,
						MSP_DSP_IN_SCART),
	[PVR2_CVAL_INPUT_COMPOSITE] = MSP_INPUT(MSP_IN_SCART1,
						MSP_IN_TUNER1,
						MSP_DSP_IN_SCART,
						MSP_DSP_IN_SCART),
	[PVR2_CVAL_INPUT_SVIDEO]    = MSP_INPUT(MSP_IN_SCART1,
						MSP_IN_TUNER1,
						MSP_DSP_IN_SCART,
						MSP_DSP_IN_SCART),
पूर्ण;

अटल स्थिर काष्ठा routing_scheme routing_def0 = अणु
	.def = routing_scheme0,
	.cnt = ARRAY_SIZE(routing_scheme0),
पूर्ण;

अटल स्थिर काष्ठा routing_scheme *routing_schemes[] = अणु
	[PVR2_ROUTING_SCHEME_HAUPPAUGE] = &routing_def0,
पूर्ण;

व्योम pvr2_msp3400_subdev_update(काष्ठा pvr2_hdw *hdw, काष्ठा v4l2_subdev *sd)
अणु
	अगर (hdw->input_dirty || hdw->क्रमce_dirty) अणु
		स्थिर काष्ठा routing_scheme *sp;
		अचिन्हित पूर्णांक sid = hdw->hdw_desc->संकेत_routing_scheme;
		u32 input;

		pvr2_trace(PVR2_TRACE_CHIPS, "subdev msp3400 v4l2 set_stereo");
		sp = (sid < ARRAY_SIZE(routing_schemes)) ?
			routing_schemes[sid] : शून्य;

		अगर ((sp != शून्य) &&
		    (hdw->input_val >= 0) &&
		    (hdw->input_val < sp->cnt)) अणु
			input = sp->def[hdw->input_val];
		पूर्ण अन्यथा अणु
			pvr2_trace(PVR2_TRACE_ERROR_LEGS,
				   "*** WARNING *** subdev msp3400 set_input: Invalid routing scheme (%u) and/or input (%d)",
				   sid, hdw->input_val);
			वापस;
		पूर्ण
		sd->ops->audio->s_routing(sd, input,
			MSP_OUTPUT(MSP_SC_IN_DSP_SCART1), 0);
	पूर्ण
पूर्ण
