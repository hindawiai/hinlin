<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/***************************************************************************
 *           WT रेजिस्टर offsets.
 *
 *  Wed Oct 22 13:50:20 2003
 *  Copyright  2003  mjander
 *  mjander@users.sourceक्रमge.org
 ****************************************************************************/
#अगर_अघोषित _AU88X0_WT_H
#घोषणा _AU88X0_WT_H

/* WT channels are grouped in banks. Each bank has 0x20 channels. */
/* Bank रेजिस्टर address boundary is 0x8000 */

#घोषणा NR_WT_PB 0x20

/* WT bank base रेजिस्टर (as dword address). */
#घोषणा WT_BAR(x) (((x)&0xffe0)<<0x8)
#घोषणा WT_BANK(x) (x>>5)
/* WT Bank रेजिस्टरs */
#घोषणा WT_CTRL(bank)	(((((bank)&1)<<0xd) + 0x00)<<2)	/* 0x0000 */
#घोषणा WT_SRAMP(bank)	(((((bank)&1)<<0xd) + 0x01)<<2)	/* 0x0004 */
#घोषणा WT_DSREG(bank)	(((((bank)&1)<<0xd) + 0x02)<<2)	/* 0x0008 */
#घोषणा WT_MRAMP(bank)	(((((bank)&1)<<0xd) + 0x03)<<2)	/* 0x000c */
#घोषणा WT_GMODE(bank)	(((((bank)&1)<<0xd) + 0x04)<<2)	/* 0x0010 */
#घोषणा WT_ARAMP(bank)	(((((bank)&1)<<0xd) + 0x05)<<2)	/* 0x0014 */
/* WT Voice रेजिस्टरs */
#घोषणा WT_STEREO(voice)	((WT_BAR(voice)+ 0x20 +(((voice)&0x1f)>>1))<<2)	/* 0x0080 */
#घोषणा WT_MUTE(voice)		((WT_BAR(voice)+ 0x40 +((voice)&0x1f))<<2)	/* 0x0100 */
#घोषणा WT_RUN(voice)		((WT_BAR(voice)+ 0x60 +((voice)&0x1f))<<2)	/* 0x0180 */
/* Some kind of parameters. */
/* PARM0, PARM1 : Filter (0xFF000000), SampleRate (0x0000FFFF) */
/* PARM2, PARM3 : Still unknown */
#घोषणा WT_PARM(x,y)	(((WT_BAR(x))+ 0x80 +(((x)&0x1f)<<2)+(y))<<2)	/* 0x0200 */
#घोषणा WT_DELAY(x,y)	(((WT_BAR(x))+ 0x100 +(((x)&0x1f)<<2)+(y))<<2)	/* 0x0400 */

/* Numeric indexes used by SetReg() and GetReg() */
#अगर 0
क्रमागत अणु
	run = 0,		/* 0  W 1:run 0:stop */
	parm0,			/* 1  W filter, samplerate */
	parm1,			/* 2  W filter, samplerate */
	parm2,			/* 3  W  */
	parm3,			/* 4  RW volume. This value is calculated using भग्नing poपूर्णांक ops. */
	sramp,			/* 5  W */
	mute,			/* 6  W 1:mute, 0:unmute */
	gmode,			/* 7  RO Looks like only bit0 is used. */
	aramp,			/* 8  W */
	mramp,			/* 9  W */
	ctrl,			/* a  W */
	delay,			/* b  W All 4 values are written at once with same value. */
	dsreg,			/* c  (R)W */
पूर्ण wt_reg;
#पूर्ण_अगर

प्रकार काष्ठा अणु
	u32 parm0;	/* this_1E4 */
	u32 parm1;	/* this_1E8 */
	u32 parm2;	/* this_1EC */
	u32 parm3;	/* this_1F0 */
	u32 this_1D0;
पूर्ण wt_voice_t;

#पूर्ण_अगर				/* _AU88X0_WT_H */

/* End of file */
