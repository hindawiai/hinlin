<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/***************************************************************************
 *            au88x0_cxtalk.h
 *
 *  Wed Nov 19 19:07:17 2003
 *  Copyright  2003  mjander
 *  mjander@users.sourceक्रमge.org
 ****************************************************************************/

/*
 */

/* The crosstalk canceler supports 5 stereo input channels. The result is 
   available at one single output route pair (stereo). */

#अगर_अघोषित _AU88X0_CXTALK_H
#घोषणा _AU88X0_CXTALK_H

#समावेश "au88x0.h"

#घोषणा XTDLINE_SZ 32
#घोषणा XTGAINS_SZ 10
#घोषणा XTINST_SZ 4

#घोषणा XT_HEADPHONE	1
#घोषणा XT_SPEAKER0		2
#घोषणा XT_SPEAKER1		3
#घोषणा XT_DIAMOND		4

प्रकार u32 xtalk_dline_t[XTDLINE_SZ];
प्रकार u16 xtalk_gains_t[XTGAINS_SZ];
प्रकार u16 xtalk_instate_t[XTINST_SZ];
प्रकार u16 xtalk_coefs_t[5][5];
प्रकार u16 xtalk_state_t[5][4];

अटल व्योम vortex_XtalkHw_SetGains(vortex_t * vortex,
				    xtalk_gains_t स्थिर gains);
अटल व्योम vortex_XtalkHw_SetGainsAllChan(vortex_t * vortex);
अटल व्योम vortex_XtalkHw_SetSampleRate(vortex_t * vortex, u32 sr);
अटल व्योम vortex_XtalkHw_ProgramPipe(vortex_t * vortex);
अटल व्योम vortex_XtalkHw_ProgramPipe(vortex_t * vortex);
अटल व्योम vortex_XtalkHw_ProgramXtalkWide(vortex_t * vortex);
अटल व्योम vortex_XtalkHw_ProgramXtalkNarrow(vortex_t * vortex);
अटल व्योम vortex_XtalkHw_ProgramDiamondXtalk(vortex_t * vortex);
अटल व्योम vortex_XtalkHw_Enable(vortex_t * vortex);
अटल व्योम vortex_XtalkHw_Disable(vortex_t * vortex);
अटल व्योम vortex_XtalkHw_init(vortex_t * vortex);

#पूर्ण_अगर				/* _AU88X0_CXTALK_H */
