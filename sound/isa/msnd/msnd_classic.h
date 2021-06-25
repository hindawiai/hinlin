<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*********************************************************************
 *
 * msnd_classic.h
 *
 * Turtle Beach MultiSound Sound Card Driver क्रम Linux
 *
 * Some parts of this header file were derived from the Turtle Beach
 * MultiSound Driver Development Kit.
 *
 * Copyright (C) 1998 Andrew Veliath
 * Copyright (C) 1993 Turtle Beach Systems, Inc.
 *
 ********************************************************************/
#अगर_अघोषित __MSND_CLASSIC_H
#घोषणा __MSND_CLASSIC_H

#घोषणा DSP_NUMIO				0x10

#घोषणा	HP_MEMM					0x08

#घोषणा	HP_BITM					0x0E
#घोषणा	HP_WAIT					0x0D
#घोषणा	HP_DSPR					0x0A
#घोषणा	HP_PROR					0x0B
#घोषणा	HP_BLKS					0x0C

#घोषणा	HPPRORESET_OFF				0
#घोषणा HPPRORESET_ON				1

#घोषणा HPDSPRESET_OFF				0
#घोषणा HPDSPRESET_ON				1

#घोषणा HPBLKSEL_0				0
#घोषणा HPBLKSEL_1				1

#घोषणा HPWAITSTATE_0				0
#घोषणा HPWAITSTATE_1				1

#घोषणा HPBITMODE_16				0
#घोषणा HPBITMODE_8				1

#घोषणा	HIDSP_INT_PLAY_UNDER			0x00
#घोषणा	HIDSP_INT_RECORD_OVER			0x01
#घोषणा	HIDSP_INPUT_CLIPPING			0x02
#घोषणा	HIDSP_MIDI_IN_OVER			0x10
#घोषणा	HIDSP_MIDI_OVERRUN_ERR  0x13

#घोषणा TIME_PRO_RESET_DONE			0x028A
#घोषणा TIME_PRO_SYSEX				0x0040
#घोषणा TIME_PRO_RESET				0x0032

#घोषणा DAR_BUFF_SIZE				0x2000

#घोषणा MIDQ_BUFF_SIZE				0x200
#घोषणा DSPQ_BUFF_SIZE				0x40

#घोषणा DSPQ_DATA_BUFF				0x7260

#घोषणा MOP_SYNTH				0x10
#घोषणा MOP_EXTOUT				0x32
#घोषणा MOP_EXTTHRU				0x02
#घोषणा MOP_OUTMASK				0x01

#घोषणा MIP_EXTIN				0x01
#घोषणा MIP_SYNTH				0x00
#घोषणा MIP_INMASK				0x32

/* Classic SMA Common Data */
#घोषणा SMA_wCurrPlayBytes			0x0000
#घोषणा SMA_wCurrRecordBytes			0x0002
#घोषणा SMA_wCurrPlayVolLeft			0x0004
#घोषणा SMA_wCurrPlayVolRight			0x0006
#घोषणा SMA_wCurrInVolLeft			0x0008
#घोषणा SMA_wCurrInVolRight			0x000a
#घोषणा SMA_wUser_3				0x000c
#घोषणा SMA_wUser_4				0x000e
#घोषणा SMA_dwUser_5				0x0010
#घोषणा SMA_dwUser_6				0x0014
#घोषणा SMA_wUser_7				0x0018
#घोषणा SMA_wReserved_A				0x001a
#घोषणा SMA_wReserved_B				0x001c
#घोषणा SMA_wReserved_C				0x001e
#घोषणा SMA_wReserved_D				0x0020
#घोषणा SMA_wReserved_E				0x0022
#घोषणा SMA_wReserved_F				0x0024
#घोषणा SMA_wReserved_G				0x0026
#घोषणा SMA_wReserved_H				0x0028
#घोषणा SMA_wCurrDSPStatusFlags			0x002a
#घोषणा SMA_wCurrHostStatusFlags		0x002c
#घोषणा SMA_wCurrInputTagBits			0x002e
#घोषणा SMA_wCurrLeftPeak			0x0030
#घोषणा SMA_wCurrRightPeak			0x0032
#घोषणा SMA_wExtDSPbits				0x0034
#घोषणा SMA_bExtHostbits			0x0036
#घोषणा SMA_bBoardLevel				0x0037
#घोषणा SMA_bInPotPosRight			0x0038
#घोषणा SMA_bInPotPosLeft			0x0039
#घोषणा SMA_bAuxPotPosRight			0x003a
#घोषणा SMA_bAuxPotPosLeft			0x003b
#घोषणा SMA_wCurrMastVolLeft			0x003c
#घोषणा SMA_wCurrMastVolRight			0x003e
#घोषणा SMA_bUser_12				0x0040
#घोषणा SMA_bUser_13				0x0041
#घोषणा SMA_wUser_14				0x0042
#घोषणा SMA_wUser_15				0x0044
#घोषणा SMA_wCalFreqAtoD			0x0046
#घोषणा SMA_wUser_16				0x0048
#घोषणा SMA_wUser_17				0x004a
#घोषणा SMA__size				0x004c

#घोषणा INITCODEखाता		"turtlebeach/msndinit.bin"
#घोषणा PERMCODEखाता		"turtlebeach/msndperm.bin"
#घोषणा LONGNAME		"MultiSound (Classic/Monterey/Tahiti)"

#पूर्ण_अगर /* __MSND_CLASSIC_H */
