<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *
 *  Copyright (C) 2005 Mike Isely <isely@pobox.com>
 *  Copyright (C) 2004 Aurelien Alleaume <slts@मुक्त.fr>
 */

/*

   This source file is specअगरically deचिन्हित to पूर्णांकerface with the
   v4l-dvb cs53l32a module.

*/

#समावेश "pvrusb2-cs53l32a.h"


#समावेश "pvrusb2-hdw-internal.h"
#समावेश "pvrusb2-debug.h"
#समावेश <linux/videodev2.h>
#समावेश <media/v4l2-common.h>
#समावेश <linux/त्रुटिसं.स>

काष्ठा routing_scheme अणु
	स्थिर पूर्णांक *def;
	अचिन्हित पूर्णांक cnt;
पूर्ण;


अटल स्थिर पूर्णांक routing_scheme1[] = अणु
	[PVR2_CVAL_INPUT_TV] = 2,  /* 1 or 2 seems to work here */
	[PVR2_CVAL_INPUT_RADIO] = 2,
	[PVR2_CVAL_INPUT_COMPOSITE] = 0,
	[PVR2_CVAL_INPUT_SVIDEO] =  0,
पूर्ण;

अटल स्थिर काष्ठा routing_scheme routing_def1 = अणु
	.def = routing_scheme1,
	.cnt = ARRAY_SIZE(routing_scheme1),
पूर्ण;

अटल स्थिर काष्ठा routing_scheme *routing_schemes[] = अणु
	[PVR2_ROUTING_SCHEME_ONAIR] = &routing_def1,
पूर्ण;


व्योम pvr2_cs53l32a_subdev_update(काष्ठा pvr2_hdw *hdw, काष्ठा v4l2_subdev *sd)
अणु
	अगर (hdw->input_dirty || hdw->क्रमce_dirty) अणु
		स्थिर काष्ठा routing_scheme *sp;
		अचिन्हित पूर्णांक sid = hdw->hdw_desc->संकेत_routing_scheme;
		u32 input;
		pvr2_trace(PVR2_TRACE_CHIPS, "subdev v4l2 set_input(%d)",
			   hdw->input_val);
		sp = (sid < ARRAY_SIZE(routing_schemes)) ?
			routing_schemes[sid] : शून्य;
		अगर ((sp == शून्य) ||
		    (hdw->input_val < 0) ||
		    (hdw->input_val >= sp->cnt)) अणु
			pvr2_trace(PVR2_TRACE_ERROR_LEGS,
				   "*** WARNING *** subdev v4l2 set_input: Invalid routing scheme (%u) and/or input (%d)",
				   sid, hdw->input_val);
			वापस;
		पूर्ण
		input = sp->def[hdw->input_val];
		sd->ops->audio->s_routing(sd, input, 0, 0);
	पूर्ण
पूर्ण
