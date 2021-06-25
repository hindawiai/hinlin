<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *
 *  Copyright (C) 2005 Mike Isely <isely@pobox.com>
 *  Copyright (C) 2004 Aurelien Alleaume <slts@मुक्त.fr>
 */

/*

   This source file is specअगरically deचिन्हित to पूर्णांकerface with the
   wm8775.

*/

#समावेश "pvrusb2-wm8775.h"


#समावेश "pvrusb2-hdw-internal.h"
#समावेश "pvrusb2-debug.h"
#समावेश <linux/videodev2.h>
#समावेश <media/v4l2-common.h>
#समावेश <linux/त्रुटिसं.स>

व्योम pvr2_wm8775_subdev_update(काष्ठा pvr2_hdw *hdw, काष्ठा v4l2_subdev *sd)
अणु
	अगर (hdw->input_dirty || hdw->क्रमce_dirty) अणु
		u32 input;

		चयन (hdw->input_val) अणु
		हाल PVR2_CVAL_INPUT_RADIO:
			input = 1;
			अवरोध;
		शेष:
			/* All other हालs just use the second input */
			input = 2;
			अवरोध;
		पूर्ण
		pvr2_trace(PVR2_TRACE_CHIPS, "subdev wm8775 set_input(val=%d route=0x%x)",
			   hdw->input_val, input);

		sd->ops->audio->s_routing(sd, input, 0, 0);
	पूर्ण
पूर्ण
