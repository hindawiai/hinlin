<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  cx18 video पूर्णांकerface functions
 *
 *  Copyright (C) 2007  Hans Verkuil <hverkuil@xs4all.nl>
 */

#समावेश "cx18-driver.h"
#समावेश "cx18-video.h"
#समावेश "cx18-cards.h"

व्योम cx18_video_set_io(काष्ठा cx18 *cx)
अणु
	पूर्णांक inp = cx->active_input;

	v4l2_subdev_call(cx->sd_av, video, s_routing,
			cx->card->video_inमाला_दो[inp].video_input, 0, 0);
पूर्ण
