<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *   Copyright (c) 2007 Daniel Mack
 *   मित्रly supported by NI.
 */

#समावेश <linux/device.h>
#समावेश <linux/init.h>
#समावेश <linux/usb.h>
#समावेश <sound/control.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>

#समावेश "device.h"
#समावेश "control.h"

#घोषणा CNT_INTVAL 0x10000
#घोषणा MASCHINE_BANK_SIZE 32

अटल पूर्णांक control_info(काष्ठा snd_kcontrol *kcontrol,
			काष्ठा snd_ctl_elem_info *uinfo)
अणु
	काष्ठा snd_usb_audio *chip = snd_kcontrol_chip(kcontrol);
	काष्ठा snd_usb_caiaqdev *cdev = caiaqdev(chip->card);
	पूर्णांक pos = kcontrol->निजी_value;
	पूर्णांक is_पूर्णांकval = pos & CNT_INTVAL;
	पूर्णांक maxval = 63;

	uinfo->count = 1;
	pos &= ~CNT_INTVAL;

	चयन (cdev->chip.usb_id) अणु
	हाल USB_ID(USB_VID_NATIVEINSTRUMENTS, USB_PID_AUDIO8DJ):
	हाल USB_ID(USB_VID_NATIVEINSTRUMENTS, USB_PID_AUDIO4DJ):
		अगर (pos == 0) अणु
			/* current input mode of A8DJ and A4DJ */
			uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
			uinfo->value.पूर्णांकeger.min = 0;
			uinfo->value.पूर्णांकeger.max = 2;
			वापस 0;
		पूर्ण
		अवरोध;

	हाल USB_ID(USB_VID_NATIVEINSTRUMENTS, USB_PID_TRAKTORKONTROLX1):
		maxval = 127;
		अवरोध;

	हाल USB_ID(USB_VID_NATIVEINSTRUMENTS, USB_PID_TRAKTORKONTROLS4):
		maxval = 31;
		अवरोध;
	पूर्ण

	अगर (is_पूर्णांकval) अणु
		uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
		uinfo->value.पूर्णांकeger.min = 0;
		uinfo->value.पूर्णांकeger.max = maxval;
	पूर्ण अन्यथा अणु
		uinfo->type = SNDRV_CTL_ELEM_TYPE_BOOLEAN;
		uinfo->value.पूर्णांकeger.min = 0;
		uinfo->value.पूर्णांकeger.max = 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक control_get(काष्ठा snd_kcontrol *kcontrol,
		       काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_usb_audio *chip = snd_kcontrol_chip(kcontrol);
	काष्ठा snd_usb_caiaqdev *cdev = caiaqdev(chip->card);
	पूर्णांक pos = kcontrol->निजी_value;

	अगर (pos & CNT_INTVAL)
		ucontrol->value.पूर्णांकeger.value[0]
			= cdev->control_state[pos & ~CNT_INTVAL];
	अन्यथा
		ucontrol->value.पूर्णांकeger.value[0]
			= !!(cdev->control_state[pos / 8] & (1 << pos % 8));

	वापस 0;
पूर्ण

अटल पूर्णांक control_put(काष्ठा snd_kcontrol *kcontrol,
		       काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_usb_audio *chip = snd_kcontrol_chip(kcontrol);
	काष्ठा snd_usb_caiaqdev *cdev = caiaqdev(chip->card);
	पूर्णांक pos = kcontrol->निजी_value;
	पूर्णांक v = ucontrol->value.पूर्णांकeger.value[0];
	अचिन्हित अक्षर cmd;

	चयन (cdev->chip.usb_id) अणु
	हाल USB_ID(USB_VID_NATIVEINSTRUMENTS, USB_PID_MASCHINECONTROLLER):
	हाल USB_ID(USB_VID_NATIVEINSTRUMENTS, USB_PID_TRAKTORKONTROLX1):
	हाल USB_ID(USB_VID_NATIVEINSTRUMENTS, USB_PID_KORECONTROLLER2):
	हाल USB_ID(USB_VID_NATIVEINSTRUMENTS, USB_PID_KORECONTROLLER):
		cmd = EP1_CMD_DIMM_LEDS;
		अवरोध;
	शेष:
		cmd = EP1_CMD_WRITE_IO;
		अवरोध;
	पूर्ण

	अगर (pos & CNT_INTVAL) अणु
		पूर्णांक i = pos & ~CNT_INTVAL;

		cdev->control_state[i] = v;

		अगर (cdev->chip.usb_id ==
			USB_ID(USB_VID_NATIVEINSTRUMENTS, USB_PID_TRAKTORKONTROLS4)) अणु
			पूर्णांक actual_len;

			cdev->ep8_out_buf[0] = i;
			cdev->ep8_out_buf[1] = v;

			usb_bulk_msg(cdev->chip.dev,
				     usb_sndbulkpipe(cdev->chip.dev, 8),
				     cdev->ep8_out_buf, माप(cdev->ep8_out_buf),
				     &actual_len, 200);
		पूर्ण अन्यथा अगर (cdev->chip.usb_id ==
			USB_ID(USB_VID_NATIVEINSTRUMENTS, USB_PID_MASCHINECONTROLLER)) अणु

			पूर्णांक bank = 0;
			पूर्णांक offset = 0;

			अगर (i >= MASCHINE_BANK_SIZE) अणु
				bank = 0x1e;
				offset = MASCHINE_BANK_SIZE;
			पूर्ण

			snd_usb_caiaq_send_command_bank(cdev, cmd, bank,
					cdev->control_state + offset,
					MASCHINE_BANK_SIZE);
		पूर्ण अन्यथा अणु
			snd_usb_caiaq_send_command(cdev, cmd,
					cdev->control_state, माप(cdev->control_state));
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (v)
			cdev->control_state[pos / 8] |= 1 << (pos % 8);
		अन्यथा
			cdev->control_state[pos / 8] &= ~(1 << (pos % 8));

		snd_usb_caiaq_send_command(cdev, cmd,
				cdev->control_state, माप(cdev->control_state));
	पूर्ण

	वापस 1;
पूर्ण

अटल काष्ठा snd_kcontrol_new kcontrol_ढाँचा = अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_HWDEP,
	.access = SNDRV_CTL_ELEM_ACCESS_READWRITE,
	.index = 0,
	.info = control_info,
	.get  = control_get,
	.put  = control_put,
	/* name and निजी_value filled later */
पूर्ण;

काष्ठा caiaq_controller अणु
	अक्षर *name;
	पूर्णांक index;
पूर्ण;

अटल स्थिर काष्ठा caiaq_controller ak1_controller[] = अणु
	अणु "LED left", 	2 पूर्ण,
	अणु "LED middle", 1 पूर्ण,
	अणु "LED right", 	0 पूर्ण,
	अणु "LED ring", 	3 पूर्ण
पूर्ण;

अटल स्थिर काष्ठा caiaq_controller rk2_controller[] = अणु
	अणु "LED 1",		5  पूर्ण,
	अणु "LED 2",		4  पूर्ण,
	अणु "LED 3",		3  पूर्ण,
	अणु "LED 4",		2  पूर्ण,
	अणु "LED 5",		1  पूर्ण,
	अणु "LED 6",		0  पूर्ण,
	अणु "LED pedal",		6  पूर्ण,
	अणु "LED 7seg_1b",	8  पूर्ण,
	अणु "LED 7seg_1c",	9  पूर्ण,
	अणु "LED 7seg_2a",	10 पूर्ण,
	अणु "LED 7seg_2b",	11 पूर्ण,
	अणु "LED 7seg_2c",	12 पूर्ण,
	अणु "LED 7seg_2d",	13 पूर्ण,
	अणु "LED 7seg_2e",	14 पूर्ण,
	अणु "LED 7seg_2f",	15 पूर्ण,
	अणु "LED 7seg_2g",	16 पूर्ण,
	अणु "LED 7seg_3a",	17 पूर्ण,
	अणु "LED 7seg_3b",	18 पूर्ण,
	अणु "LED 7seg_3c",	19 पूर्ण,
	अणु "LED 7seg_3d",	20 पूर्ण,
	अणु "LED 7seg_3e",	21 पूर्ण,
	अणु "LED 7seg_3f",	22 पूर्ण,
	अणु "LED 7seg_3g",	23 पूर्ण
पूर्ण;

अटल स्थिर काष्ठा caiaq_controller rk3_controller[] = अणु
	अणु "LED 7seg_1a",        0 + 0 पूर्ण,
	अणु "LED 7seg_1b",        0 + 1 पूर्ण,
	अणु "LED 7seg_1c",        0 + 2 पूर्ण,
	अणु "LED 7seg_1d",        0 + 3 पूर्ण,
	अणु "LED 7seg_1e",        0 + 4 पूर्ण,
	अणु "LED 7seg_1f",        0 + 5 पूर्ण,
	अणु "LED 7seg_1g",        0 + 6 पूर्ण,
	अणु "LED 7seg_1p",        0 + 7 पूर्ण,

	अणु "LED 7seg_2a",        8 + 0 पूर्ण,
	अणु "LED 7seg_2b",        8 + 1 पूर्ण,
	अणु "LED 7seg_2c",        8 + 2 पूर्ण,
	अणु "LED 7seg_2d",        8 + 3 पूर्ण,
	अणु "LED 7seg_2e",        8 + 4 पूर्ण,
	अणु "LED 7seg_2f",        8 + 5 पूर्ण,
	अणु "LED 7seg_2g",        8 + 6 पूर्ण,
	अणु "LED 7seg_2p",        8 + 7 पूर्ण,

	अणु "LED 7seg_3a",        16 + 0 पूर्ण,
	अणु "LED 7seg_3b",        16 + 1 पूर्ण,
	अणु "LED 7seg_3c",        16 + 2 पूर्ण,
	अणु "LED 7seg_3d",        16 + 3 पूर्ण,
	अणु "LED 7seg_3e",        16 + 4 पूर्ण,
	अणु "LED 7seg_3f",        16 + 5 पूर्ण,
	अणु "LED 7seg_3g",        16 + 6 पूर्ण,
	अणु "LED 7seg_3p",        16 + 7 पूर्ण,

	अणु "LED 7seg_4a",        24 + 0 पूर्ण,
	अणु "LED 7seg_4b",        24 + 1 पूर्ण,
	अणु "LED 7seg_4c",        24 + 2 पूर्ण,
	अणु "LED 7seg_4d",        24 + 3 पूर्ण,
	अणु "LED 7seg_4e",        24 + 4 पूर्ण,
	अणु "LED 7seg_4f",        24 + 5 पूर्ण,
	अणु "LED 7seg_4g",        24 + 6 पूर्ण,
	अणु "LED 7seg_4p",        24 + 7 पूर्ण,

	अणु "LED 1",		32 + 0 पूर्ण,
	अणु "LED 2",		32 + 1 पूर्ण,
	अणु "LED 3",		32 + 2 पूर्ण,
	अणु "LED 4",		32 + 3 पूर्ण,
	अणु "LED 5",		32 + 4 पूर्ण,
	अणु "LED 6",		32 + 5 पूर्ण,
	अणु "LED 7",		32 + 6 पूर्ण,
	अणु "LED 8",		32 + 7 पूर्ण,
	अणु "LED pedal",		32 + 8 पूर्ण
पूर्ण;

अटल स्थिर काष्ठा caiaq_controller kore_controller[] = अणु
	अणु "LED F1",		8   | CNT_INTVAL पूर्ण,
	अणु "LED F2",		12  | CNT_INTVAL पूर्ण,
	अणु "LED F3",		0   | CNT_INTVAL पूर्ण,
	अणु "LED F4",		4   | CNT_INTVAL पूर्ण,
	अणु "LED F5",		11  | CNT_INTVAL पूर्ण,
	अणु "LED F6",		15  | CNT_INTVAL पूर्ण,
	अणु "LED F7",		3   | CNT_INTVAL पूर्ण,
	अणु "LED F8",		7   | CNT_INTVAL पूर्ण,
	अणु "LED touch1",	     	10  | CNT_INTVAL पूर्ण,
	अणु "LED touch2",	     	14  | CNT_INTVAL पूर्ण,
	अणु "LED touch3",	     	2   | CNT_INTVAL पूर्ण,
	अणु "LED touch4",	     	6   | CNT_INTVAL पूर्ण,
	अणु "LED touch5",	     	9   | CNT_INTVAL पूर्ण,
	अणु "LED touch6",	     	13  | CNT_INTVAL पूर्ण,
	अणु "LED touch7",	     	1   | CNT_INTVAL पूर्ण,
	अणु "LED touch8",	     	5   | CNT_INTVAL पूर्ण,
	अणु "LED left",	       	18  | CNT_INTVAL पूर्ण,
	अणु "LED right",	     	22  | CNT_INTVAL पूर्ण,
	अणु "LED up",		16  | CNT_INTVAL पूर्ण,
	अणु "LED down",	       	20  | CNT_INTVAL पूर्ण,
	अणु "LED stop",	       	23  | CNT_INTVAL पूर्ण,
	अणु "LED play",	       	21  | CNT_INTVAL पूर्ण,
	अणु "LED record",	     	19  | CNT_INTVAL पूर्ण,
	अणु "LED listen",		17  | CNT_INTVAL पूर्ण,
	अणु "LED lcd",		30  | CNT_INTVAL पूर्ण,
	अणु "LED menu",		28  | CNT_INTVAL पूर्ण,
	अणु "LED sound",	 	31  | CNT_INTVAL पूर्ण,
	अणु "LED esc",		29  | CNT_INTVAL पूर्ण,
	अणु "LED view",		27  | CNT_INTVAL पूर्ण,
	अणु "LED enter",		24  | CNT_INTVAL पूर्ण,
	अणु "LED control",	26  | CNT_INTVAL पूर्ण
पूर्ण;

अटल स्थिर काष्ठा caiaq_controller a8dj_controller[] = अणु
	अणु "Current input mode",			0 | CNT_INTVAL 	पूर्ण,
	अणु "GND lift for TC Vinyl mode", 	24 + 0 		पूर्ण,
	अणु "GND lift for TC CD/Line mode", 	24 + 1 		पूर्ण,
	अणु "GND lift for phono mode", 		24 + 2 		पूर्ण,
	अणु "Software lock", 			40 		पूर्ण
पूर्ण;

अटल स्थिर काष्ठा caiaq_controller a4dj_controller[] = अणु
	अणु "Current input mode",	0 | CNT_INTVAL 	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा caiaq_controller kontrolx1_controller[] = अणु
	अणु "LED FX A: ON",		7 | CNT_INTVAL	पूर्ण,
	अणु "LED FX A: 1",		6 | CNT_INTVAL	पूर्ण,
	अणु "LED FX A: 2",		5 | CNT_INTVAL	पूर्ण,
	अणु "LED FX A: 3",		4 | CNT_INTVAL	पूर्ण,
	अणु "LED FX B: ON",		3 | CNT_INTVAL	पूर्ण,
	अणु "LED FX B: 1",		2 | CNT_INTVAL	पूर्ण,
	अणु "LED FX B: 2",		1 | CNT_INTVAL	पूर्ण,
	अणु "LED FX B: 3",		0 | CNT_INTVAL	पूर्ण,

	अणु "LED Hotcue",			28 | CNT_INTVAL	पूर्ण,
	अणु "LED Shift (white)",		29 | CNT_INTVAL	पूर्ण,
	अणु "LED Shift (green)",		30 | CNT_INTVAL	पूर्ण,

	अणु "LED Deck A: FX1",		24 | CNT_INTVAL	पूर्ण,
	अणु "LED Deck A: FX2",		25 | CNT_INTVAL	पूर्ण,
	अणु "LED Deck A: IN",		17 | CNT_INTVAL	पूर्ण,
	अणु "LED Deck A: OUT",		16 | CNT_INTVAL	पूर्ण,
	अणु "LED Deck A: < BEAT",		19 | CNT_INTVAL	पूर्ण,
	अणु "LED Deck A: BEAT >",		18 | CNT_INTVAL	पूर्ण,
	अणु "LED Deck A: CUE/ABS",	21 | CNT_INTVAL	पूर्ण,
	अणु "LED Deck A: CUP/REL",	20 | CNT_INTVAL	पूर्ण,
	अणु "LED Deck A: PLAY",		23 | CNT_INTVAL	पूर्ण,
	अणु "LED Deck A: SYNC",		22 | CNT_INTVAL	पूर्ण,

	अणु "LED Deck B: FX1",		26 | CNT_INTVAL	पूर्ण,
	अणु "LED Deck B: FX2",		27 | CNT_INTVAL	पूर्ण,
	अणु "LED Deck B: IN",		15 | CNT_INTVAL	पूर्ण,
	अणु "LED Deck B: OUT",		14 | CNT_INTVAL	पूर्ण,
	अणु "LED Deck B: < BEAT",		13 | CNT_INTVAL	पूर्ण,
	अणु "LED Deck B: BEAT >",		12 | CNT_INTVAL	पूर्ण,
	अणु "LED Deck B: CUE/ABS",	11 | CNT_INTVAL	पूर्ण,
	अणु "LED Deck B: CUP/REL",	10 | CNT_INTVAL	पूर्ण,
	अणु "LED Deck B: PLAY",		9  | CNT_INTVAL	पूर्ण,
	अणु "LED Deck B: SYNC",		8  | CNT_INTVAL	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा caiaq_controller kontrols4_controller[] = अणु
	अणु "LED: Master: Quant",			10  | CNT_INTVAL पूर्ण,
	अणु "LED: Master: Headphone",		11  | CNT_INTVAL पूर्ण,
	अणु "LED: Master: Master",		12  | CNT_INTVAL पूर्ण,
	अणु "LED: Master: Snap",			14  | CNT_INTVAL पूर्ण,
	अणु "LED: Master: Warning",		15  | CNT_INTVAL पूर्ण,
	अणु "LED: Master: Master button",		112 | CNT_INTVAL पूर्ण,
	अणु "LED: Master: Snap button",		113 | CNT_INTVAL पूर्ण,
	अणु "LED: Master: Rec",			118 | CNT_INTVAL पूर्ण,
	अणु "LED: Master: Size",			119 | CNT_INTVAL पूर्ण,
	अणु "LED: Master: Quant button",		120 | CNT_INTVAL पूर्ण,
	अणु "LED: Master: Browser button",	121 | CNT_INTVAL पूर्ण,
	अणु "LED: Master: Play button",		126 | CNT_INTVAL पूर्ण,
	अणु "LED: Master: Undo button",		127 | CNT_INTVAL पूर्ण,

	अणु "LED: Channel A: >",			4   | CNT_INTVAL पूर्ण,
	अणु "LED: Channel A: <",			5   | CNT_INTVAL पूर्ण,
	अणु "LED: Channel A: Meter 1",		97  | CNT_INTVAL पूर्ण,
	अणु "LED: Channel A: Meter 2",		98  | CNT_INTVAL पूर्ण,
	अणु "LED: Channel A: Meter 3",		99  | CNT_INTVAL पूर्ण,
	अणु "LED: Channel A: Meter 4",		100 | CNT_INTVAL पूर्ण,
	अणु "LED: Channel A: Meter 5",		101 | CNT_INTVAL पूर्ण,
	अणु "LED: Channel A: Meter 6",		102 | CNT_INTVAL पूर्ण,
	अणु "LED: Channel A: Meter clip",		103 | CNT_INTVAL पूर्ण,
	अणु "LED: Channel A: Active",		114 | CNT_INTVAL पूर्ण,
	अणु "LED: Channel A: Cue",		116 | CNT_INTVAL पूर्ण,
	अणु "LED: Channel A: FX1",		149 | CNT_INTVAL पूर्ण,
	अणु "LED: Channel A: FX2",		148 | CNT_INTVAL पूर्ण,

	अणु "LED: Channel B: >",			2   | CNT_INTVAL पूर्ण,
	अणु "LED: Channel B: <",			3   | CNT_INTVAL पूर्ण,
	अणु "LED: Channel B: Meter 1",		89  | CNT_INTVAL पूर्ण,
	अणु "LED: Channel B: Meter 2",		90  | CNT_INTVAL पूर्ण,
	अणु "LED: Channel B: Meter 3",		91  | CNT_INTVAL पूर्ण,
	अणु "LED: Channel B: Meter 4",		92  | CNT_INTVAL पूर्ण,
	अणु "LED: Channel B: Meter 5",		93  | CNT_INTVAL पूर्ण,
	अणु "LED: Channel B: Meter 6",		94  | CNT_INTVAL पूर्ण,
	अणु "LED: Channel B: Meter clip",		95  | CNT_INTVAL पूर्ण,
	अणु "LED: Channel B: Active",		122 | CNT_INTVAL पूर्ण,
	अणु "LED: Channel B: Cue",		125 | CNT_INTVAL पूर्ण,
	अणु "LED: Channel B: FX1",		147 | CNT_INTVAL पूर्ण,
	अणु "LED: Channel B: FX2",		146 | CNT_INTVAL पूर्ण,

	अणु "LED: Channel C: >",			6   | CNT_INTVAL पूर्ण,
	अणु "LED: Channel C: <",			7   | CNT_INTVAL पूर्ण,
	अणु "LED: Channel C: Meter 1",		105 | CNT_INTVAL पूर्ण,
	अणु "LED: Channel C: Meter 2",		106 | CNT_INTVAL पूर्ण,
	अणु "LED: Channel C: Meter 3",		107 | CNT_INTVAL पूर्ण,
	अणु "LED: Channel C: Meter 4",		108 | CNT_INTVAL पूर्ण,
	अणु "LED: Channel C: Meter 5",		109 | CNT_INTVAL पूर्ण,
	अणु "LED: Channel C: Meter 6",		110 | CNT_INTVAL पूर्ण,
	अणु "LED: Channel C: Meter clip",		111 | CNT_INTVAL पूर्ण,
	अणु "LED: Channel C: Active",		115 | CNT_INTVAL पूर्ण,
	अणु "LED: Channel C: Cue",		117 | CNT_INTVAL पूर्ण,
	अणु "LED: Channel C: FX1",		151 | CNT_INTVAL पूर्ण,
	अणु "LED: Channel C: FX2",		150 | CNT_INTVAL पूर्ण,

	अणु "LED: Channel D: >",			0   | CNT_INTVAL पूर्ण,
	अणु "LED: Channel D: <",			1   | CNT_INTVAL पूर्ण,
	अणु "LED: Channel D: Meter 1",		81  | CNT_INTVAL पूर्ण,
	अणु "LED: Channel D: Meter 2",		82  | CNT_INTVAL पूर्ण,
	अणु "LED: Channel D: Meter 3",		83  | CNT_INTVAL पूर्ण,
	अणु "LED: Channel D: Meter 4",		84  | CNT_INTVAL पूर्ण,
	अणु "LED: Channel D: Meter 5",		85  | CNT_INTVAL पूर्ण,
	अणु "LED: Channel D: Meter 6",		86  | CNT_INTVAL पूर्ण,
	अणु "LED: Channel D: Meter clip",		87  | CNT_INTVAL पूर्ण,
	अणु "LED: Channel D: Active",		123 | CNT_INTVAL पूर्ण,
	अणु "LED: Channel D: Cue",		124 | CNT_INTVAL पूर्ण,
	अणु "LED: Channel D: FX1",		145 | CNT_INTVAL पूर्ण,
	अणु "LED: Channel D: FX2",		144 | CNT_INTVAL पूर्ण,

	अणु "LED: Deck A: 1 (blue)",		22  | CNT_INTVAL पूर्ण,
	अणु "LED: Deck A: 1 (green)",		23  | CNT_INTVAL पूर्ण,
	अणु "LED: Deck A: 2 (blue)",		20  | CNT_INTVAL पूर्ण,
	अणु "LED: Deck A: 2 (green)",		21  | CNT_INTVAL पूर्ण,
	अणु "LED: Deck A: 3 (blue)",		18  | CNT_INTVAL पूर्ण,
	अणु "LED: Deck A: 3 (green)",		19  | CNT_INTVAL पूर्ण,
	अणु "LED: Deck A: 4 (blue)",		16  | CNT_INTVAL पूर्ण,
	अणु "LED: Deck A: 4 (green)",		17  | CNT_INTVAL पूर्ण,
	अणु "LED: Deck A: Load",			44  | CNT_INTVAL पूर्ण,
	अणु "LED: Deck A: Deck C button",		45  | CNT_INTVAL पूर्ण,
	अणु "LED: Deck A: In",			47  | CNT_INTVAL पूर्ण,
	अणु "LED: Deck A: Out",			46  | CNT_INTVAL पूर्ण,
	अणु "LED: Deck A: Shift",			24  | CNT_INTVAL पूर्ण,
	अणु "LED: Deck A: Sync",			27  | CNT_INTVAL पूर्ण,
	अणु "LED: Deck A: Cue",			26  | CNT_INTVAL पूर्ण,
	अणु "LED: Deck A: Play",			25  | CNT_INTVAL पूर्ण,
	अणु "LED: Deck A: Tempo up",		33  | CNT_INTVAL पूर्ण,
	अणु "LED: Deck A: Tempo down",		32  | CNT_INTVAL पूर्ण,
	अणु "LED: Deck A: Master",		34  | CNT_INTVAL पूर्ण,
	अणु "LED: Deck A: Keylock",		35  | CNT_INTVAL पूर्ण,
	अणु "LED: Deck A: Deck A",		37  | CNT_INTVAL पूर्ण,
	अणु "LED: Deck A: Deck C",		36  | CNT_INTVAL पूर्ण,
	अणु "LED: Deck A: Samples",		38  | CNT_INTVAL पूर्ण,
	अणु "LED: Deck A: On Air",		39  | CNT_INTVAL पूर्ण,
	अणु "LED: Deck A: Sample 1",		31  | CNT_INTVAL पूर्ण,
	अणु "LED: Deck A: Sample 2",		30  | CNT_INTVAL पूर्ण,
	अणु "LED: Deck A: Sample 3",		29  | CNT_INTVAL पूर्ण,
	अणु "LED: Deck A: Sample 4",		28  | CNT_INTVAL पूर्ण,
	अणु "LED: Deck A: Digit 1 - A",		55  | CNT_INTVAL पूर्ण,
	अणु "LED: Deck A: Digit 1 - B",		54  | CNT_INTVAL पूर्ण,
	अणु "LED: Deck A: Digit 1 - C",		53  | CNT_INTVAL पूर्ण,
	अणु "LED: Deck A: Digit 1 - D",		52  | CNT_INTVAL पूर्ण,
	अणु "LED: Deck A: Digit 1 - E",		51  | CNT_INTVAL पूर्ण,
	अणु "LED: Deck A: Digit 1 - F",		50  | CNT_INTVAL पूर्ण,
	अणु "LED: Deck A: Digit 1 - G",		49  | CNT_INTVAL पूर्ण,
	अणु "LED: Deck A: Digit 1 - dot",		48  | CNT_INTVAL पूर्ण,
	अणु "LED: Deck A: Digit 2 - A",		63  | CNT_INTVAL पूर्ण,
	अणु "LED: Deck A: Digit 2 - B",		62  | CNT_INTVAL पूर्ण,
	अणु "LED: Deck A: Digit 2 - C",		61  | CNT_INTVAL पूर्ण,
	अणु "LED: Deck A: Digit 2 - D",		60  | CNT_INTVAL पूर्ण,
	अणु "LED: Deck A: Digit 2 - E",		59  | CNT_INTVAL पूर्ण,
	अणु "LED: Deck A: Digit 2 - F",		58  | CNT_INTVAL पूर्ण,
	अणु "LED: Deck A: Digit 2 - G",		57  | CNT_INTVAL पूर्ण,
	अणु "LED: Deck A: Digit 2 - dot",		56  | CNT_INTVAL पूर्ण,

	अणु "LED: Deck B: 1 (blue)",		78  | CNT_INTVAL पूर्ण,
	अणु "LED: Deck B: 1 (green)",		79  | CNT_INTVAL पूर्ण,
	अणु "LED: Deck B: 2 (blue)",		76  | CNT_INTVAL पूर्ण,
	अणु "LED: Deck B: 2 (green)",		77  | CNT_INTVAL पूर्ण,
	अणु "LED: Deck B: 3 (blue)",		74  | CNT_INTVAL पूर्ण,
	अणु "LED: Deck B: 3 (green)",		75  | CNT_INTVAL पूर्ण,
	अणु "LED: Deck B: 4 (blue)",		72  | CNT_INTVAL पूर्ण,
	अणु "LED: Deck B: 4 (green)",		73  | CNT_INTVAL पूर्ण,
	अणु "LED: Deck B: Load",			180 | CNT_INTVAL पूर्ण,
	अणु "LED: Deck B: Deck D button",		181 | CNT_INTVAL पूर्ण,
	अणु "LED: Deck B: In",			183 | CNT_INTVAL पूर्ण,
	अणु "LED: Deck B: Out",			182 | CNT_INTVAL पूर्ण,
	अणु "LED: Deck B: Shift",			64  | CNT_INTVAL पूर्ण,
	अणु "LED: Deck B: Sync",			67  | CNT_INTVAL पूर्ण,
	अणु "LED: Deck B: Cue",			66  | CNT_INTVAL पूर्ण,
	अणु "LED: Deck B: Play",			65  | CNT_INTVAL पूर्ण,
	अणु "LED: Deck B: Tempo up",		185 | CNT_INTVAL पूर्ण,
	अणु "LED: Deck B: Tempo down",		184 | CNT_INTVAL पूर्ण,
	अणु "LED: Deck B: Master",		186 | CNT_INTVAL पूर्ण,
	अणु "LED: Deck B: Keylock",		187 | CNT_INTVAL पूर्ण,
	अणु "LED: Deck B: Deck B",		189 | CNT_INTVAL पूर्ण,
	अणु "LED: Deck B: Deck D",		188 | CNT_INTVAL पूर्ण,
	अणु "LED: Deck B: Samples",		190 | CNT_INTVAL पूर्ण,
	अणु "LED: Deck B: On Air",		191 | CNT_INTVAL पूर्ण,
	अणु "LED: Deck B: Sample 1",		71  | CNT_INTVAL पूर्ण,
	अणु "LED: Deck B: Sample 2",		70  | CNT_INTVAL पूर्ण,
	अणु "LED: Deck B: Sample 3",		69  | CNT_INTVAL पूर्ण,
	अणु "LED: Deck B: Sample 4",		68  | CNT_INTVAL पूर्ण,
	अणु "LED: Deck B: Digit 1 - A",		175 | CNT_INTVAL पूर्ण,
	अणु "LED: Deck B: Digit 1 - B",		174 | CNT_INTVAL पूर्ण,
	अणु "LED: Deck B: Digit 1 - C",		173 | CNT_INTVAL पूर्ण,
	अणु "LED: Deck B: Digit 1 - D",		172 | CNT_INTVAL पूर्ण,
	अणु "LED: Deck B: Digit 1 - E",		171 | CNT_INTVAL पूर्ण,
	अणु "LED: Deck B: Digit 1 - F",		170 | CNT_INTVAL पूर्ण,
	अणु "LED: Deck B: Digit 1 - G",		169 | CNT_INTVAL पूर्ण,
	अणु "LED: Deck B: Digit 1 - dot",		168 | CNT_INTVAL पूर्ण,
	अणु "LED: Deck B: Digit 2 - A",		167 | CNT_INTVAL पूर्ण,
	अणु "LED: Deck B: Digit 2 - B",		166 | CNT_INTVAL पूर्ण,
	अणु "LED: Deck B: Digit 2 - C",		165 | CNT_INTVAL पूर्ण,
	अणु "LED: Deck B: Digit 2 - D",		164 | CNT_INTVAL पूर्ण,
	अणु "LED: Deck B: Digit 2 - E",		163 | CNT_INTVAL पूर्ण,
	अणु "LED: Deck B: Digit 2 - F",		162 | CNT_INTVAL पूर्ण,
	अणु "LED: Deck B: Digit 2 - G",		161 | CNT_INTVAL पूर्ण,
	अणु "LED: Deck B: Digit 2 - dot",		160 | CNT_INTVAL पूर्ण,

	अणु "LED: FX1: dry/wet",			153 | CNT_INTVAL पूर्ण,
	अणु "LED: FX1: 1",			154 | CNT_INTVAL पूर्ण,
	अणु "LED: FX1: 2",			155 | CNT_INTVAL पूर्ण,
	अणु "LED: FX1: 3",			156 | CNT_INTVAL पूर्ण,
	अणु "LED: FX1: Mode",			157 | CNT_INTVAL पूर्ण,
	अणु "LED: FX2: dry/wet",			129 | CNT_INTVAL पूर्ण,
	अणु "LED: FX2: 1",			130 | CNT_INTVAL पूर्ण,
	अणु "LED: FX2: 2",			131 | CNT_INTVAL पूर्ण,
	अणु "LED: FX2: 3",			132 | CNT_INTVAL पूर्ण,
	अणु "LED: FX2: Mode",			133 | CNT_INTVAL पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा caiaq_controller maschine_controller[] = अणु
	अणु "LED: Pad 1",				3  | CNT_INTVAL पूर्ण,
	अणु "LED: Pad 2",				2  | CNT_INTVAL पूर्ण,
	अणु "LED: Pad 3",				1  | CNT_INTVAL पूर्ण,
	अणु "LED: Pad 4",				0  | CNT_INTVAL पूर्ण,
	अणु "LED: Pad 5",				7  | CNT_INTVAL पूर्ण,
	अणु "LED: Pad 6",				6  | CNT_INTVAL पूर्ण,
	अणु "LED: Pad 7",				5  | CNT_INTVAL पूर्ण,
	अणु "LED: Pad 8",				4  | CNT_INTVAL पूर्ण,
	अणु "LED: Pad 9",				11 | CNT_INTVAL पूर्ण,
	अणु "LED: Pad 10",			10 | CNT_INTVAL पूर्ण,
	अणु "LED: Pad 11",			9  | CNT_INTVAL पूर्ण,
	अणु "LED: Pad 12",			8  | CNT_INTVAL पूर्ण,
	अणु "LED: Pad 13",			15 | CNT_INTVAL पूर्ण,
	अणु "LED: Pad 14",			14 | CNT_INTVAL पूर्ण,
	अणु "LED: Pad 15",			13 | CNT_INTVAL पूर्ण,
	अणु "LED: Pad 16",			12 | CNT_INTVAL पूर्ण,

	अणु "LED: Mute",				16 | CNT_INTVAL पूर्ण,
	अणु "LED: Solo",				17 | CNT_INTVAL पूर्ण,
	अणु "LED: Select",			18 | CNT_INTVAL पूर्ण,
	अणु "LED: Duplicate",			19 | CNT_INTVAL पूर्ण,
	अणु "LED: Navigate",			20 | CNT_INTVAL पूर्ण,
	अणु "LED: Pad Mode",			21 | CNT_INTVAL पूर्ण,
	अणु "LED: Pattern",			22 | CNT_INTVAL पूर्ण,
	अणु "LED: Scene",				23 | CNT_INTVAL पूर्ण,

	अणु "LED: Shift",				24 | CNT_INTVAL पूर्ण,
	अणु "LED: Erase",				25 | CNT_INTVAL पूर्ण,
	अणु "LED: Grid",				26 | CNT_INTVAL पूर्ण,
	अणु "LED: Right Bottom",			27 | CNT_INTVAL पूर्ण,
	अणु "LED: Rec",				28 | CNT_INTVAL पूर्ण,
	अणु "LED: Play",				29 | CNT_INTVAL पूर्ण,
	अणु "LED: Left Bottom",			32 | CNT_INTVAL पूर्ण,
	अणु "LED: Restart",			33 | CNT_INTVAL पूर्ण,

	अणु "LED: Group A",			41 | CNT_INTVAL पूर्ण,
	अणु "LED: Group B",			40 | CNT_INTVAL पूर्ण,
	अणु "LED: Group C",			37 | CNT_INTVAL पूर्ण,
	अणु "LED: Group D",			36 | CNT_INTVAL पूर्ण,
	अणु "LED: Group E",			39 | CNT_INTVAL पूर्ण,
	अणु "LED: Group F",			38 | CNT_INTVAL पूर्ण,
	अणु "LED: Group G",			35 | CNT_INTVAL पूर्ण,
	अणु "LED: Group H",			34 | CNT_INTVAL पूर्ण,

	अणु "LED: Auto Write",			42 | CNT_INTVAL पूर्ण,
	अणु "LED: Snap",				43 | CNT_INTVAL पूर्ण,
	अणु "LED: Right Top",			44 | CNT_INTVAL पूर्ण,
	अणु "LED: Left Top",			45 | CNT_INTVAL पूर्ण,
	अणु "LED: Sampling",			46 | CNT_INTVAL पूर्ण,
	अणु "LED: Browse",			47 | CNT_INTVAL पूर्ण,
	अणु "LED: Step",				48 | CNT_INTVAL पूर्ण,
	अणु "LED: Control",			49 | CNT_INTVAL पूर्ण,

	अणु "LED: Top Button 1",			57 | CNT_INTVAL पूर्ण,
	अणु "LED: Top Button 2",			56 | CNT_INTVAL पूर्ण,
	अणु "LED: Top Button 3",			55 | CNT_INTVAL पूर्ण,
	अणु "LED: Top Button 4",			54 | CNT_INTVAL पूर्ण,
	अणु "LED: Top Button 5",			53 | CNT_INTVAL पूर्ण,
	अणु "LED: Top Button 6",			52 | CNT_INTVAL पूर्ण,
	अणु "LED: Top Button 7",			51 | CNT_INTVAL पूर्ण,
	अणु "LED: Top Button 8",			50 | CNT_INTVAL पूर्ण,

	अणु "LED: Note Repeat",			58 | CNT_INTVAL पूर्ण,

	अणु "Backlight Display",			59 | CNT_INTVAL पूर्ण
पूर्ण;

अटल पूर्णांक add_controls(स्थिर काष्ठा caiaq_controller *c, पूर्णांक num,
			काष्ठा snd_usb_caiaqdev *cdev)
अणु
	पूर्णांक i, ret;
	काष्ठा snd_kcontrol *kc;

	क्रम (i = 0; i < num; i++, c++) अणु
		kcontrol_ढाँचा.name = c->name;
		kcontrol_ढाँचा.निजी_value = c->index;
		kc = snd_ctl_new1(&kcontrol_ढाँचा, cdev);
		ret = snd_ctl_add(cdev->chip.card, kc);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक snd_usb_caiaq_control_init(काष्ठा snd_usb_caiaqdev *cdev)
अणु
	पूर्णांक ret = 0;

	चयन (cdev->chip.usb_id) अणु
	हाल USB_ID(USB_VID_NATIVEINSTRUMENTS, USB_PID_AK1):
		ret = add_controls(ak1_controller,
			ARRAY_SIZE(ak1_controller), cdev);
		अवरोध;

	हाल USB_ID(USB_VID_NATIVEINSTRUMENTS, USB_PID_RIGKONTROL2):
		ret = add_controls(rk2_controller,
			ARRAY_SIZE(rk2_controller), cdev);
		अवरोध;

	हाल USB_ID(USB_VID_NATIVEINSTRUMENTS, USB_PID_RIGKONTROL3):
		ret = add_controls(rk3_controller,
			ARRAY_SIZE(rk3_controller), cdev);
		अवरोध;

	हाल USB_ID(USB_VID_NATIVEINSTRUMENTS, USB_PID_KORECONTROLLER):
	हाल USB_ID(USB_VID_NATIVEINSTRUMENTS, USB_PID_KORECONTROLLER2):
		ret = add_controls(kore_controller,
			ARRAY_SIZE(kore_controller), cdev);
		अवरोध;

	हाल USB_ID(USB_VID_NATIVEINSTRUMENTS, USB_PID_AUDIO8DJ):
		ret = add_controls(a8dj_controller,
			ARRAY_SIZE(a8dj_controller), cdev);
		अवरोध;

	हाल USB_ID(USB_VID_NATIVEINSTRUMENTS, USB_PID_AUDIO4DJ):
		ret = add_controls(a4dj_controller,
			ARRAY_SIZE(a4dj_controller), cdev);
		अवरोध;

	हाल USB_ID(USB_VID_NATIVEINSTRUMENTS, USB_PID_TRAKTORKONTROLX1):
		ret = add_controls(kontrolx1_controller,
			ARRAY_SIZE(kontrolx1_controller), cdev);
		अवरोध;

	हाल USB_ID(USB_VID_NATIVEINSTRUMENTS, USB_PID_TRAKTORKONTROLS4):
		ret = add_controls(kontrols4_controller,
			ARRAY_SIZE(kontrols4_controller), cdev);
		अवरोध;

	हाल USB_ID(USB_VID_NATIVEINSTRUMENTS, USB_PID_MASCHINECONTROLLER):
		ret = add_controls(maschine_controller,
			ARRAY_SIZE(maschine_controller), cdev);
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

