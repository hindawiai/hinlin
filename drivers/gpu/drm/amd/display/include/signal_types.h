<शैली गुरु>
/*
 * Copyright 2012-15 Advanced Micro Devices, Inc.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * Authors: AMD
 *
 */

#अगर_अघोषित __DC_SIGNAL_TYPES_H__
#घोषणा __DC_SIGNAL_TYPES_H__

/* Minimum pixel घड़ी, in KHz. For TMDS संकेत is 25.00 MHz */
#घोषणा TMDS_MIN_PIXEL_CLOCK 25000
/* Maximum pixel घड़ी, in KHz. For TMDS संकेत is 165.00 MHz */
#घोषणा TMDS_MAX_PIXEL_CLOCK 165000

क्रमागत संकेत_type अणु
	SIGNAL_TYPE_NONE		= 0L,		/* no संकेत */
	SIGNAL_TYPE_DVI_SINGLE_LINK	= (1 << 0),
	SIGNAL_TYPE_DVI_DUAL_LINK	= (1 << 1),
	SIGNAL_TYPE_HDMI_TYPE_A		= (1 << 2),
	SIGNAL_TYPE_LVDS		= (1 << 3),
	SIGNAL_TYPE_RGB			= (1 << 4),
	SIGNAL_TYPE_DISPLAY_PORT	= (1 << 5),
	SIGNAL_TYPE_DISPLAY_PORT_MST	= (1 << 6),
	SIGNAL_TYPE_EDP			= (1 << 7),
	SIGNAL_TYPE_VIRTUAL		= (1 << 9),	/* Virtual Display */
पूर्ण;

/* help functions क्रम संकेत types manipulation */
अटल अंतरभूत bool dc_is_hdmi_पंचांगds_संकेत(क्रमागत संकेत_type संकेत)
अणु
	वापस (संकेत == SIGNAL_TYPE_HDMI_TYPE_A);
पूर्ण

अटल अंतरभूत bool dc_is_hdmi_संकेत(क्रमागत संकेत_type संकेत)
अणु
	वापस (संकेत == SIGNAL_TYPE_HDMI_TYPE_A);
पूर्ण

अटल अंतरभूत bool dc_is_dp_sst_संकेत(क्रमागत संकेत_type संकेत)
अणु
	वापस (संकेत == SIGNAL_TYPE_DISPLAY_PORT ||
		संकेत == SIGNAL_TYPE_EDP);
पूर्ण

अटल अंतरभूत bool dc_is_dp_संकेत(क्रमागत संकेत_type संकेत)
अणु
	वापस (संकेत == SIGNAL_TYPE_DISPLAY_PORT ||
		संकेत == SIGNAL_TYPE_EDP ||
		संकेत == SIGNAL_TYPE_DISPLAY_PORT_MST);
पूर्ण

अटल अंतरभूत bool dc_is_embedded_संकेत(क्रमागत संकेत_type संकेत)
अणु
	वापस (संकेत == SIGNAL_TYPE_EDP || संकेत == SIGNAL_TYPE_LVDS);
पूर्ण

अटल अंतरभूत bool dc_is_lvds_संकेत(क्रमागत संकेत_type संकेत)
अणु
	वापस (संकेत == SIGNAL_TYPE_LVDS);
पूर्ण

अटल अंतरभूत bool dc_is_dvi_संकेत(क्रमागत संकेत_type संकेत)
अणु
	चयन (संकेत) अणु
	हाल SIGNAL_TYPE_DVI_SINGLE_LINK:
	हाल SIGNAL_TYPE_DVI_DUAL_LINK:
		वापस true;
	अवरोध;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल अंतरभूत bool dc_is_dvi_single_link_संकेत(क्रमागत संकेत_type संकेत)
अणु
	वापस (संकेत == SIGNAL_TYPE_DVI_SINGLE_LINK);
पूर्ण

अटल अंतरभूत bool dc_is_dual_link_संकेत(क्रमागत संकेत_type संकेत)
अणु
	वापस (संकेत == SIGNAL_TYPE_DVI_DUAL_LINK);
पूर्ण

अटल अंतरभूत bool dc_is_audio_capable_संकेत(क्रमागत संकेत_type संकेत)
अणु
	वापस (संकेत == SIGNAL_TYPE_DISPLAY_PORT ||
		संकेत == SIGNAL_TYPE_DISPLAY_PORT_MST ||
		dc_is_hdmi_संकेत(संकेत));
पूर्ण

अटल अंतरभूत bool dc_is_भव_संकेत(क्रमागत संकेत_type संकेत)
अणु
	वापस (संकेत == SIGNAL_TYPE_VIRTUAL);
पूर्ण

#पूर्ण_अगर
