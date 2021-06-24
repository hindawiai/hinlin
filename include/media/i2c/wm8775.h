<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
    wm8775.h - definition क्रम wm8775 inमाला_दो and outमाला_दो

    Copyright (C) 2006 Hans Verkuil (hverkuil@xs4all.nl)

*/

#अगर_अघोषित _WM8775_H_
#घोषणा _WM8775_H_

/* The WM8775 has 4 inमाला_दो and one output. Zero or more inमाला_दो
   are multiplexed together to the output. Hence there are
   16 combinations.
   If only one input is active (the normal हाल) then the
   input values 1, 2, 4 or 8 should be used. */

#घोषणा WM8775_AIN1 1
#घोषणा WM8775_AIN2 2
#घोषणा WM8775_AIN3 4
#घोषणा WM8775_AIN4 8


काष्ठा wm8775_platक्रमm_data अणु
	/*
	 * FIXME: Instead, we should parametrize the params
	 * that need dअगरferent settings between ivtv, pvrusb2, and Nova-S
	 */
	bool is_nova_s;
पूर्ण;

#पूर्ण_अगर
