<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*********************************************************************
 *
 * msnd_pinnacle.h
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
#अगर_अघोषित __MSND_PINNACLE_H
#घोषणा __MSND_PINNACLE_H

#घोषणा DSP_NUMIO				0x08

#घोषणा IREG_LOGDEVICE				0x07
#घोषणा IREG_ACTIVATE				0x30
#घोषणा LD_ACTIVATE				0x01
#घोषणा LD_DISACTIVATE				0x00
#घोषणा IREG_EECONTROL				0x3F
#घोषणा IREG_MEMBASEHI				0x40
#घोषणा IREG_MEMBASELO				0x41
#घोषणा IREG_MEMCONTROL				0x42
#घोषणा IREG_MEMRANGEHI				0x43
#घोषणा IREG_MEMRANGELO				0x44
#घोषणा MEMTYPE_8BIT				0x00
#घोषणा MEMTYPE_16BIT				0x02
#घोषणा MEMTYPE_RANGE				0x00
#घोषणा MEMTYPE_HIADDR				0x01
#घोषणा IREG_IO0_BASEHI				0x60
#घोषणा IREG_IO0_BASELO				0x61
#घोषणा IREG_IO1_BASEHI				0x62
#घोषणा IREG_IO1_BASELO				0x63
#घोषणा IREG_IRQ_NUMBER				0x70
#घोषणा IREG_IRQ_TYPE				0x71
#घोषणा IRQTYPE_HIGH				0x02
#घोषणा IRQTYPE_LOW				0x00
#घोषणा IRQTYPE_LEVEL				0x01
#घोषणा IRQTYPE_EDGE				0x00

#घोषणा	HP_DSPR					0x04
#घोषणा	HP_BLKS					0x04

#घोषणा HPDSPRESET_OFF				2
#घोषणा HPDSPRESET_ON				0

#घोषणा HPBLKSEL_0				2
#घोषणा HPBLKSEL_1				3

#घोषणा	HIMT_DAT_OFF				0x03

#घोषणा	HIDSP_PLAY_UNDER			0x00
#घोषणा	HIDSP_INT_PLAY_UNDER			0x01
#घोषणा	HIDSP_SSI_TX_UNDER  			0x02
#घोषणा HIDSP_RECQ_OVERFLOW			0x08
#घोषणा HIDSP_INT_RECORD_OVER			0x09
#घोषणा HIDSP_SSI_RX_OVERFLOW			0x0a

#घोषणा	HIDSP_MIDI_IN_OVER			0x10

#घोषणा	HIDSP_MIDI_FRAME_ERR			0x11
#घोषणा	HIDSP_MIDI_PARITY_ERR			0x12
#घोषणा	HIDSP_MIDI_OVERRUN_ERR			0x13

#घोषणा HIDSP_INPUT_CLIPPING			0x20
#घोषणा	HIDSP_MIX_CLIPPING			0x30
#घोषणा HIDSP_DAT_IN_OFF			0x21

#घोषणा TIME_PRO_RESET_DONE			0x028A
#घोषणा TIME_PRO_SYSEX				0x001E
#घोषणा TIME_PRO_RESET				0x0032

#घोषणा DAR_BUFF_SIZE				0x1000

#घोषणा MIDQ_BUFF_SIZE				0x800
#घोषणा DSPQ_BUFF_SIZE				0x5A0

#घोषणा DSPQ_DATA_BUFF				0x7860

#घोषणा MOP_WAVEHDR				0
#घोषणा MOP_EXTOUT				1
#घोषणा MOP_HWINIT				0xfe
#घोषणा MOP_NONE				0xff
#घोषणा MOP_MAX					1

#घोषणा MIP_EXTIN				0
#घोषणा MIP_WAVEHDR				1
#घोषणा MIP_HWINIT				0xfe
#घोषणा MIP_MAX					1

/* Pinnacle/Fiji SMA Common Data */
#घोषणा SMA_wCurrPlayBytes			0x0000
#घोषणा SMA_wCurrRecordBytes			0x0002
#घोषणा SMA_wCurrPlayVolLeft			0x0004
#घोषणा SMA_wCurrPlayVolRight			0x0006
#घोषणा SMA_wCurrInVolLeft			0x0008
#घोषणा SMA_wCurrInVolRight			0x000a
#घोषणा SMA_wCurrMHdrVolLeft			0x000c
#घोषणा SMA_wCurrMHdrVolRight			0x000e
#घोषणा SMA_dwCurrPlayPitch			0x0010
#घोषणा SMA_dwCurrPlayRate			0x0014
#घोषणा SMA_wCurrMIDIIOPatch			0x0018
#घोषणा SMA_wCurrPlayFormat			0x001a
#घोषणा SMA_wCurrPlaySampleSize			0x001c
#घोषणा SMA_wCurrPlayChannels			0x001e
#घोषणा SMA_wCurrPlaySampleRate			0x0020
#घोषणा SMA_wCurrRecordFormat			0x0022
#घोषणा SMA_wCurrRecordSampleSize		0x0024
#घोषणा SMA_wCurrRecordChannels			0x0026
#घोषणा SMA_wCurrRecordSampleRate		0x0028
#घोषणा SMA_wCurrDSPStatusFlags			0x002a
#घोषणा SMA_wCurrHostStatusFlags		0x002c
#घोषणा SMA_wCurrInputTagBits			0x002e
#घोषणा SMA_wCurrLeftPeak			0x0030
#घोषणा SMA_wCurrRightPeak			0x0032
#घोषणा SMA_bMicPotPosLeft			0x0034
#घोषणा SMA_bMicPotPosRight			0x0035
#घोषणा SMA_bMicPotMaxLeft			0x0036
#घोषणा SMA_bMicPotMaxRight			0x0037
#घोषणा SMA_bInPotPosLeft			0x0038
#घोषणा SMA_bInPotPosRight			0x0039
#घोषणा SMA_bAuxPotPosLeft			0x003a
#घोषणा SMA_bAuxPotPosRight			0x003b
#घोषणा SMA_bInPotMaxLeft			0x003c
#घोषणा SMA_bInPotMaxRight			0x003d
#घोषणा SMA_bAuxPotMaxLeft			0x003e
#घोषणा SMA_bAuxPotMaxRight			0x003f
#घोषणा SMA_bInPotMaxMethod			0x0040
#घोषणा SMA_bAuxPotMaxMethod			0x0041
#घोषणा SMA_wCurrMastVolLeft			0x0042
#घोषणा SMA_wCurrMastVolRight			0x0044
#घोषणा SMA_wCalFreqAtoD			0x0046
#घोषणा SMA_wCurrAuxVolLeft			0x0048
#घोषणा SMA_wCurrAuxVolRight			0x004a
#घोषणा SMA_wCurrPlay1VolLeft			0x004c
#घोषणा SMA_wCurrPlay1VolRight			0x004e
#घोषणा SMA_wCurrPlay2VolLeft			0x0050
#घोषणा SMA_wCurrPlay2VolRight			0x0052
#घोषणा SMA_wCurrPlay3VolLeft			0x0054
#घोषणा SMA_wCurrPlay3VolRight			0x0056
#घोषणा SMA_wCurrPlay4VolLeft			0x0058
#घोषणा SMA_wCurrPlay4VolRight			0x005a
#घोषणा SMA_wCurrPlay1PeakLeft			0x005c
#घोषणा SMA_wCurrPlay1PeakRight			0x005e
#घोषणा SMA_wCurrPlay2PeakLeft			0x0060
#घोषणा SMA_wCurrPlay2PeakRight			0x0062
#घोषणा SMA_wCurrPlay3PeakLeft			0x0064
#घोषणा SMA_wCurrPlay3PeakRight			0x0066
#घोषणा SMA_wCurrPlay4PeakLeft			0x0068
#घोषणा SMA_wCurrPlay4PeakRight			0x006a
#घोषणा SMA_wCurrPlayPeakLeft			0x006c
#घोषणा SMA_wCurrPlayPeakRight			0x006e
#घोषणा SMA_wCurrDATSR				0x0070
#घोषणा SMA_wCurrDATRXCHNL			0x0072
#घोषणा SMA_wCurrDATTXCHNL			0x0074
#घोषणा SMA_wCurrDATRXRate			0x0076
#घोषणा SMA_dwDSPPlayCount			0x0078
#घोषणा SMA__size				0x007c

#घोषणा INITCODEखाता		"turtlebeach/pndspini.bin"
#घोषणा PERMCODEखाता		"turtlebeach/pndsperm.bin"
#घोषणा LONGNAME		"MultiSound (Pinnacle/Fiji)"

#पूर्ण_अगर /* __MSND_PINNACLE_H */
