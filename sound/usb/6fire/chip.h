<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Linux driver क्रम TerraTec DMX 6Fire USB
 *
 * Author:	Torsten Schenk <torsten.schenk@zoho.com>
 * Created:	Jan 01, 2011
 * Copyright:	(C) Torsten Schenk
 */
#अगर_अघोषित USB6FIRE_CHIP_H
#घोषणा USB6FIRE_CHIP_H

#समावेश "common.h"

काष्ठा sfire_chip अणु
	काष्ठा usb_device *dev;
	काष्ठा snd_card *card;
	पूर्णांक पूर्णांकf_count; /* number of रेजिस्टरed पूर्णांकerfaces */
	पूर्णांक regidx; /* index in module parameter arrays */
	bool shutकरोwn;

	काष्ठा midi_runसमय *midi;
	काष्ठा pcm_runसमय *pcm;
	काष्ठा control_runसमय *control;
	काष्ठा comm_runसमय *comm;
पूर्ण;
#पूर्ण_अगर /* USB6FIRE_CHIP_H */

