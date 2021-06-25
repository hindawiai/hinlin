<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
    m52790.h - definition क्रम m52790 inमाला_दो and outमाला_दो

    Copyright (C) 2007 Hans Verkuil (hverkuil@xs4all.nl)

*/

#अगर_अघोषित _M52790_H_
#घोषणा _M52790_H_

/* Input routing चयन 1 */

#घोषणा M52790_SW1_IN_MASK	0x0003
#घोषणा M52790_SW1_IN_TUNER	0x0000
#घोषणा M52790_SW1_IN_V2	0x0001
#घोषणा M52790_SW1_IN_V3	0x0002
#घोषणा M52790_SW1_IN_V4	0x0003

/* Selects component input instead of composite */
#घोषणा M52790_SW1_YCMIX	0x0004


/* Input routing चयन 2 */

#घोषणा M52790_SW2_IN_MASK	0x0300
#घोषणा M52790_SW2_IN_TUNER	0x0000
#घोषणा M52790_SW2_IN_V2	0x0100
#घोषणा M52790_SW2_IN_V3	0x0200
#घोषणा M52790_SW2_IN_V4	0x0300

/* Selects component input instead of composite */
#घोषणा M52790_SW2_YCMIX	0x0400


/* Output routing चयन 1 */

/* Enable 6dB amplअगरier क्रम composite out */
#घोषणा M52790_SW1_V_AMP	0x0008

/* Enable 6dB amplअगरier क्रम component out */
#घोषणा M52790_SW1_YC_AMP	0x0010

/* Audio output mode */
#घोषणा M52790_SW1_AUDIO_MASK	0x00c0
#घोषणा M52790_SW1_AUDIO_MUTE	0x0000
#घोषणा M52790_SW1_AUDIO_R	0x0040
#घोषणा M52790_SW1_AUDIO_L	0x0080
#घोषणा M52790_SW1_AUDIO_STEREO 0x00c0


/* Output routing चयन 2 */

/* Enable 6dB amplअगरier क्रम composite out */
#घोषणा M52790_SW2_V_AMP	0x0800

/* Enable 6dB amplअगरier क्रम component out */
#घोषणा M52790_SW2_YC_AMP	0x1000

/* Audio output mode */
#घोषणा M52790_SW2_AUDIO_MASK	0xc000
#घोषणा M52790_SW2_AUDIO_MUTE	0x0000
#घोषणा M52790_SW2_AUDIO_R	0x4000
#घोषणा M52790_SW2_AUDIO_L	0x8000
#घोषणा M52790_SW2_AUDIO_STEREO 0xc000


/* Common values */
#घोषणा M52790_IN_TUNER (M52790_SW1_IN_TUNER | M52790_SW2_IN_TUNER)
#घोषणा M52790_IN_V2    (M52790_SW1_IN_V2 | M52790_SW2_IN_V2)
#घोषणा M52790_IN_V3    (M52790_SW1_IN_V3 | M52790_SW2_IN_V3)
#घोषणा M52790_IN_V4    (M52790_SW1_IN_V4 | M52790_SW2_IN_V4)

#घोषणा M52790_OUT_STEREO	(M52790_SW1_AUDIO_STEREO | \
				 M52790_SW2_AUDIO_STEREO)
#घोषणा M52790_OUT_AMP_STEREO	(M52790_SW1_AUDIO_STEREO | \
				 M52790_SW1_V_AMP | \
				 M52790_SW2_AUDIO_STEREO | \
				 M52790_SW2_V_AMP)

#पूर्ण_अगर
