<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *
 * Copyright (c) 2003 by Karsten Wiese <annabellesgarden@yahoo.de>
 */

क्रमागत E_In84अणु
	eFader0 = 0,
	eFader1,
	eFader2,
	eFader3,
	eFader4,
	eFader5,
	eFader6,
	eFader7,
	eFaderM,
	eTransport,
	eModअगरier = 10,
	eFilterSelect,
	eSelect,
	eMute,

	eSwitch   = 15,
	eWheelGain,
	eWheelFreq,
	eWheelQ,
	eWheelPan,
	eWheel    = 20
पूर्ण;

#घोषणा T_RECORD   1
#घोषणा T_PLAY     2
#घोषणा T_STOP     4
#घोषणा T_F_FWD    8
#घोषणा T_REW   0x10
#घोषणा T_SOLO  0x20
#घोषणा T_REC   0x40
#घोषणा T_शून्य  0x80


काष्ठा us428_ctls अणु
	अचिन्हित अक्षर   Fader[9];
	अचिन्हित अक्षर 	Transport;
	अचिन्हित अक्षर 	Modअगरier;
	अचिन्हित अक्षर 	FilterSelect;
	अचिन्हित अक्षर 	Select;
	अचिन्हित अक्षर   Mute;
	अचिन्हित अक्षर   UNKNOWN;
	अचिन्हित अक्षर   Switch;	     
	अचिन्हित अक्षर   Wheel[5];
पूर्ण;

काष्ठा us428_setByte अणु
	अचिन्हित अक्षर Offset,
		Value;
पूर्ण;

क्रमागत अणु
	eLT_Volume = 0,
	eLT_Light
पूर्ण;

काष्ठा usX2Y_volume अणु
	अचिन्हित अक्षर Channel,
		LH,
		LL,
		RH,
		RL;
पूर्ण;

काष्ठा us428_lights अणु
	काष्ठा us428_setByte Light[7];
पूर्ण;

काष्ठा us428_p4out अणु
	अक्षर type;
	जोड़ अणु
		काष्ठा usX2Y_volume vol;
		काष्ठा us428_lights lights;
	पूर्ण val;
पूर्ण;

#घोषणा N_us428_ctl_BUFS 16
#घोषणा N_us428_p4out_BUFS 16
काष्ठा us428ctls_sharedmemअणु
	काष्ठा us428_ctls	CtlSnapShot[N_us428_ctl_BUFS];
	पूर्णांक			CtlSnapShotDअगरfersAt[N_us428_ctl_BUFS];
	पूर्णांक			CtlSnapShotLast, CtlSnapShotRed;
	काष्ठा us428_p4out	p4out[N_us428_p4out_BUFS];
	पूर्णांक			p4outLast, p4outSent;
पूर्ण;
