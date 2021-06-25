<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2008, Creative Technology Ltd. All Rights Reserved.
 *
 * @File	cपंचांगixer.h
 *
 * @Brief
 * This file contains the definition of the mixer device functions.
 *
 * @Author	Liu Chun
 * @Date 	Mar 28 2008
 */

#अगर_अघोषित CTMIXER_H
#घोषणा CTMIXER_H

#समावेश "ctatc.h"
#समावेश "ctresource.h"

#घोषणा INIT_VOL	0x1c00

क्रमागत MIXER_PORT_T अणु
	MIX_WAVE_FRONT,
	MIX_WAVE_REAR,
	MIX_WAVE_CENTLFE,
	MIX_WAVE_SURROUND,
	MIX_SPDIF_OUT,
	MIX_PCMO_FRONT,
	MIX_MIC_IN,
	MIX_LINE_IN,
	MIX_SPDIF_IN,
	MIX_PCMI_FRONT,
	MIX_PCMI_REAR,
	MIX_PCMI_CENTLFE,
	MIX_PCMI_SURROUND,

	NUM_MIX_PORTS
पूर्ण;

/* alsa mixer descriptor */
काष्ठा ct_mixer अणु
	काष्ठा ct_atc *atc;

	व्योम **amixers;		/* amixer resources क्रम volume control */
	व्योम **sums;		/* sum resources क्रम संकेत collection */
	अचिन्हित पूर्णांक चयन_state; /* A bit-map to indicate state of चयनes */

	पूर्णांक (*get_output_ports)(काष्ठा ct_mixer *mixer, क्रमागत MIXER_PORT_T type,
				  काष्ठा rsc **rleft, काष्ठा rsc **rright);

	पूर्णांक (*set_input_left)(काष्ठा ct_mixer *mixer,
			      क्रमागत MIXER_PORT_T type, काष्ठा rsc *rsc);
	पूर्णांक (*set_input_right)(काष्ठा ct_mixer *mixer,
			       क्रमागत MIXER_PORT_T type, काष्ठा rsc *rsc);
#अगर_घोषित CONFIG_PM_SLEEP
	पूर्णांक (*resume)(काष्ठा ct_mixer *mixer);
#पूर्ण_अगर
पूर्ण;

पूर्णांक ct_alsa_mix_create(काष्ठा ct_atc *atc,
		       क्रमागत CTALSADEVS device,
		       स्थिर अक्षर *device_name);
पूर्णांक ct_mixer_create(काष्ठा ct_atc *atc, काष्ठा ct_mixer **rmixer);
पूर्णांक ct_mixer_destroy(काष्ठा ct_mixer *mixer);

#पूर्ण_अगर /* CTMIXER_H */
