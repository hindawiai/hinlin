<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Linux driver क्रम TerraTec DMX 6Fire USB
 *
 * Author:	Torsten Schenk <torsten.schenk@zoho.com>
 * Created:	Jan 01, 2011
 * Copyright:	(C) Torsten Schenk
 */

#अगर_अघोषित USB6FIRE_CONTROL_H
#घोषणा USB6FIRE_CONTROL_H

#समावेश "common.h"

क्रमागत अणु
	CONTROL_MAX_ELEMENTS = 32
पूर्ण;

क्रमागत अणु
	CONTROL_RATE_44KHZ,
	CONTROL_RATE_48KHZ,
	CONTROL_RATE_88KHZ,
	CONTROL_RATE_96KHZ,
	CONTROL_RATE_176KHZ,
	CONTROL_RATE_192KHZ,
	CONTROL_N_RATES
पूर्ण;

काष्ठा control_runसमय अणु
	पूर्णांक (*update_streaming)(काष्ठा control_runसमय *rt);
	पूर्णांक (*set_rate)(काष्ठा control_runसमय *rt, पूर्णांक rate);
	पूर्णांक (*set_channels)(काष्ठा control_runसमय *rt, पूर्णांक n_analog_out,
		पूर्णांक n_analog_in, bool spdअगर_out, bool spdअगर_in);

	काष्ठा sfire_chip *chip;

	काष्ठा snd_kcontrol *element[CONTROL_MAX_ELEMENTS];
	bool opt_coax_चयन;
	bool line_phono_चयन;
	bool digital_thru_चयन;
	bool usb_streaming;
	u8 output_vol[6];
	u8 ovol_updated;
	u8 output_mute;
	s8 input_vol[2];
	u8 ivol_updated;
पूर्ण;

पूर्णांक usb6fire_control_init(काष्ठा sfire_chip *chip);
व्योम usb6fire_control_पात(काष्ठा sfire_chip *chip);
व्योम usb6fire_control_destroy(काष्ठा sfire_chip *chip);
#पूर्ण_अगर /* USB6FIRE_CONTROL_H */

