<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Platक्रमm data क्रम MAX98088
 *
 * Copyright 2010 Maxim Integrated Products
 */

#अगर_अघोषित __SOUND_MAX98088_PDATA_H__
#घोषणा __SOUND_MAX98088_PDATA_H__

/* Equalizer filter response configuration */
काष्ठा max98088_eq_cfg अणु
       स्थिर अक्षर *name;
       अचिन्हित पूर्णांक rate;
       u16 band1[5];
       u16 band2[5];
       u16 band3[5];
       u16 band4[5];
       u16 band5[5];
पूर्ण;

/* codec platक्रमm data */
काष्ठा max98088_pdata अणु

       /* Equalizers क्रम DAI1 and DAI2 */
       काष्ठा max98088_eq_cfg *eq_cfg;
       अचिन्हित पूर्णांक eq_cfgcnt;

       /* Receiver output can be configured as घातer amplअगरier or LINE out */
       /* Set receiver_mode to:
        * 0 = amplअगरier output, or
        * 1 = LINE level output
        */
       अचिन्हित पूर्णांक receiver_mode:1;

       /* Analog/digital microphone configuration:
        * 0 = analog microphone input (normal setting)
        * 1 = digital microphone input
        */
       अचिन्हित पूर्णांक digmic_left_mode:1;
       अचिन्हित पूर्णांक digmic_right_mode:1;

पूर्ण;

#पूर्ण_अगर
