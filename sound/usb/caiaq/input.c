<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *   Copyright (c) 2006,2007 Daniel Mack, Tim Ruetz
*/

#समावेश <linux/device.h>
#समावेश <linux/gfp.h>
#समावेश <linux/init.h>
#समावेश <linux/usb.h>
#समावेश <linux/usb/input.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>

#समावेश "device.h"
#समावेश "input.h"

अटल स्थिर अचिन्हित लघु keycode_ak1[] =  अणु KEY_C, KEY_B, KEY_A पूर्ण;
अटल स्थिर अचिन्हित लघु keycode_rk2[] =  अणु KEY_1, KEY_2, KEY_3, KEY_4,
					 KEY_5, KEY_6, KEY_7 पूर्ण;
अटल स्थिर अचिन्हित लघु keycode_rk3[] =  अणु KEY_1, KEY_2, KEY_3, KEY_4,
					 KEY_5, KEY_6, KEY_7, KEY_8, KEY_9 पूर्ण;

अटल स्थिर अचिन्हित लघु keycode_kore[] = अणु
	KEY_FN_F1,      /* "menu"               */
	KEY_FN_F7,      /* "lcd backlight       */
	KEY_FN_F2,      /* "control"            */
	KEY_FN_F3,      /* "enter"              */
	KEY_FN_F4,      /* "view"               */
	KEY_FN_F5,      /* "esc"                */
	KEY_FN_F6,      /* "sound"              */
	KEY_FN_F8,      /* array spacer, never triggered. */
	KEY_RIGHT,
	KEY_DOWN,
	KEY_UP,
	KEY_LEFT,
	KEY_SOUND,      /* "listen"             */
	KEY_RECORD,
	KEY_PLAYPAUSE,
	KEY_STOP,
	BTN_4,          /* 8 softkeys */
	BTN_3,
	BTN_2,
	BTN_1,
	BTN_8,
	BTN_7,
	BTN_6,
	BTN_5,
	KEY_BRL_DOT4,   /* touch sensitive knobs */
	KEY_BRL_DOT3,
	KEY_BRL_DOT2,
	KEY_BRL_DOT1,
	KEY_BRL_DOT8,
	KEY_BRL_DOT7,
	KEY_BRL_DOT6,
	KEY_BRL_DOT5
पूर्ण;

#घोषणा MASCHINE_BUTTONS   (42)
#घोषणा MASCHINE_BUTTON(X) ((X) + BTN_MISC)
#घोषणा MASCHINE_PADS      (16)
#घोषणा MASCHINE_PAD(X)    ((X) + ABS_PRESSURE)

अटल स्थिर अचिन्हित लघु keycode_maschine[] = अणु
	MASCHINE_BUTTON(40), /* mute       */
	MASCHINE_BUTTON(39), /* solo       */
	MASCHINE_BUTTON(38), /* select     */
	MASCHINE_BUTTON(37), /* duplicate  */
	MASCHINE_BUTTON(36), /* navigate   */
	MASCHINE_BUTTON(35), /* pad mode   */
	MASCHINE_BUTTON(34), /* pattern    */
	MASCHINE_BUTTON(33), /* scene      */
	KEY_RESERVED, /* spacer */

	MASCHINE_BUTTON(30), /* rec        */
	MASCHINE_BUTTON(31), /* erase      */
	MASCHINE_BUTTON(32), /* shअगरt      */
	MASCHINE_BUTTON(28), /* grid       */
	MASCHINE_BUTTON(27), /* >          */
	MASCHINE_BUTTON(26), /* <          */
	MASCHINE_BUTTON(25), /* restart    */

	MASCHINE_BUTTON(21), /* E          */
	MASCHINE_BUTTON(22), /* F          */
	MASCHINE_BUTTON(23), /* G          */
	MASCHINE_BUTTON(24), /* H          */
	MASCHINE_BUTTON(20), /* D          */
	MASCHINE_BUTTON(19), /* C          */
	MASCHINE_BUTTON(18), /* B          */
	MASCHINE_BUTTON(17), /* A          */

	MASCHINE_BUTTON(0),  /* control    */
	MASCHINE_BUTTON(2),  /* browse     */
	MASCHINE_BUTTON(4),  /* <          */
	MASCHINE_BUTTON(6),  /* snap       */
	MASCHINE_BUTTON(7),  /* स्वतःग_लिखो  */
	MASCHINE_BUTTON(5),  /* >          */
	MASCHINE_BUTTON(3),  /* sampling   */
	MASCHINE_BUTTON(1),  /* step       */

	MASCHINE_BUTTON(15), /* 8 softkeys */
	MASCHINE_BUTTON(14),
	MASCHINE_BUTTON(13),
	MASCHINE_BUTTON(12),
	MASCHINE_BUTTON(11),
	MASCHINE_BUTTON(10),
	MASCHINE_BUTTON(9),
	MASCHINE_BUTTON(8),

	MASCHINE_BUTTON(16), /* note repeat */
	MASCHINE_BUTTON(29)  /* play        */
पूर्ण;

#घोषणा KONTROLX1_INPUTS	(40)
#घोषणा KONTROLS4_BUTTONS	(12 * 8)
#घोषणा KONTROLS4_AXIS		(46)

#घोषणा KONTROLS4_BUTTON(X)	((X) + BTN_MISC)
#घोषणा KONTROLS4_ABS(X)	((X) + ABS_HAT0X)

#घोषणा DEG90		(range / 2)
#घोषणा DEG180		(range)
#घोषणा DEG270		(DEG90 + DEG180)
#घोषणा DEG360		(DEG180 * 2)
#घोषणा HIGH_PEAK	(268)
#घोषणा LOW_PEAK	(-7)

/* some of these devices have endless rotation potentiometers
 * built in which use two tapers, 90 degrees phase shअगरted.
 * this algorithm decodes them to one single value, ranging
 * from 0 to 999 */
अटल अचिन्हित पूर्णांक decode_erp(अचिन्हित अक्षर a, अचिन्हित अक्षर b)
अणु
	पूर्णांक weight_a, weight_b;
	पूर्णांक pos_a, pos_b;
	पूर्णांक ret;
	पूर्णांक range = HIGH_PEAK - LOW_PEAK;
	पूर्णांक mid_value = (HIGH_PEAK + LOW_PEAK) / 2;

	weight_b = असल(mid_value - a) - (range / 2 - 100) / 2;

	अगर (weight_b < 0)
		weight_b = 0;

	अगर (weight_b > 100)
		weight_b = 100;

	weight_a = 100 - weight_b;

	अगर (a < mid_value) अणु
		/* 0..90 and 270..360 degrees */
		pos_b = b - LOW_PEAK + DEG270;
		अगर (pos_b >= DEG360)
			pos_b -= DEG360;
	पूर्ण अन्यथा
		/* 90..270 degrees */
		pos_b = HIGH_PEAK - b + DEG90;


	अगर (b > mid_value)
		/* 0..180 degrees */
		pos_a = a - LOW_PEAK;
	अन्यथा
		/* 180..360 degrees */
		pos_a = HIGH_PEAK - a + DEG180;

	/* पूर्णांकerpolate both slider values, depending on weight factors */
	/* 0..99 x DEG360 */
	ret = pos_a * weight_a + pos_b * weight_b;

	/* normalize to 0..999 */
	ret *= 10;
	ret /= DEG360;

	अगर (ret < 0)
		ret += 1000;

	अगर (ret >= 1000)
		ret -= 1000;

	वापस ret;
पूर्ण

#अघोषित DEG90
#अघोषित DEG180
#अघोषित DEG270
#अघोषित DEG360
#अघोषित HIGH_PEAK
#अघोषित LOW_PEAK

अटल अंतरभूत व्योम snd_caiaq_input_report_असल(काष्ठा snd_usb_caiaqdev *cdev,
					      पूर्णांक axis, स्थिर अचिन्हित अक्षर *buf,
					      पूर्णांक offset)
अणु
	input_report_असल(cdev->input_dev, axis,
			 (buf[offset * 2] << 8) | buf[offset * 2 + 1]);
पूर्ण

अटल व्योम snd_caiaq_input_पढ़ो_analog(काष्ठा snd_usb_caiaqdev *cdev,
					स्थिर अचिन्हित अक्षर *buf,
					अचिन्हित पूर्णांक len)
अणु
	काष्ठा input_dev *input_dev = cdev->input_dev;

	चयन (cdev->chip.usb_id) अणु
	हाल USB_ID(USB_VID_NATIVEINSTRUMENTS, USB_PID_RIGKONTROL2):
		snd_caiaq_input_report_असल(cdev, ABS_X, buf, 2);
		snd_caiaq_input_report_असल(cdev, ABS_Y, buf, 0);
		snd_caiaq_input_report_असल(cdev, ABS_Z, buf, 1);
		अवरोध;
	हाल USB_ID(USB_VID_NATIVEINSTRUMENTS, USB_PID_RIGKONTROL3):
	हाल USB_ID(USB_VID_NATIVEINSTRUMENTS, USB_PID_KORECONTROLLER):
	हाल USB_ID(USB_VID_NATIVEINSTRUMENTS, USB_PID_KORECONTROLLER2):
		snd_caiaq_input_report_असल(cdev, ABS_X, buf, 0);
		snd_caiaq_input_report_असल(cdev, ABS_Y, buf, 1);
		snd_caiaq_input_report_असल(cdev, ABS_Z, buf, 2);
		अवरोध;
	हाल USB_ID(USB_VID_NATIVEINSTRUMENTS, USB_PID_TRAKTORKONTROLX1):
		snd_caiaq_input_report_असल(cdev, ABS_HAT0X, buf, 4);
		snd_caiaq_input_report_असल(cdev, ABS_HAT0Y, buf, 2);
		snd_caiaq_input_report_असल(cdev, ABS_HAT1X, buf, 6);
		snd_caiaq_input_report_असल(cdev, ABS_HAT1Y, buf, 1);
		snd_caiaq_input_report_असल(cdev, ABS_HAT2X, buf, 7);
		snd_caiaq_input_report_असल(cdev, ABS_HAT2Y, buf, 0);
		snd_caiaq_input_report_असल(cdev, ABS_HAT3X, buf, 5);
		snd_caiaq_input_report_असल(cdev, ABS_HAT3Y, buf, 3);
		अवरोध;
	पूर्ण

	input_sync(input_dev);
पूर्ण

अटल व्योम snd_caiaq_input_पढ़ो_erp(काष्ठा snd_usb_caiaqdev *cdev,
				     स्थिर अक्षर *buf, अचिन्हित पूर्णांक len)
अणु
	काष्ठा input_dev *input_dev = cdev->input_dev;
	पूर्णांक i;

	चयन (cdev->chip.usb_id) अणु
	हाल USB_ID(USB_VID_NATIVEINSTRUMENTS, USB_PID_AK1):
		i = decode_erp(buf[0], buf[1]);
		input_report_असल(input_dev, ABS_X, i);
		input_sync(input_dev);
		अवरोध;
	हाल USB_ID(USB_VID_NATIVEINSTRUMENTS, USB_PID_KORECONTROLLER):
	हाल USB_ID(USB_VID_NATIVEINSTRUMENTS, USB_PID_KORECONTROLLER2):
		i = decode_erp(buf[7], buf[5]);
		input_report_असल(input_dev, ABS_HAT0X, i);
		i = decode_erp(buf[12], buf[14]);
		input_report_असल(input_dev, ABS_HAT0Y, i);
		i = decode_erp(buf[15], buf[13]);
		input_report_असल(input_dev, ABS_HAT1X, i);
		i = decode_erp(buf[0], buf[2]);
		input_report_असल(input_dev, ABS_HAT1Y, i);
		i = decode_erp(buf[3], buf[1]);
		input_report_असल(input_dev, ABS_HAT2X, i);
		i = decode_erp(buf[8], buf[10]);
		input_report_असल(input_dev, ABS_HAT2Y, i);
		i = decode_erp(buf[11], buf[9]);
		input_report_असल(input_dev, ABS_HAT3X, i);
		i = decode_erp(buf[4], buf[6]);
		input_report_असल(input_dev, ABS_HAT3Y, i);
		input_sync(input_dev);
		अवरोध;

	हाल USB_ID(USB_VID_NATIVEINSTRUMENTS, USB_PID_MASCHINECONTROLLER):
		/* 4 under the left screen */
		input_report_असल(input_dev, ABS_HAT0X, decode_erp(buf[21], buf[20]));
		input_report_असल(input_dev, ABS_HAT0Y, decode_erp(buf[15], buf[14]));
		input_report_असल(input_dev, ABS_HAT1X, decode_erp(buf[9],  buf[8]));
		input_report_असल(input_dev, ABS_HAT1Y, decode_erp(buf[3],  buf[2]));

		/* 4 under the right screen */
		input_report_असल(input_dev, ABS_HAT2X, decode_erp(buf[19], buf[18]));
		input_report_असल(input_dev, ABS_HAT2Y, decode_erp(buf[13], buf[12]));
		input_report_असल(input_dev, ABS_HAT3X, decode_erp(buf[7],  buf[6]));
		input_report_असल(input_dev, ABS_HAT3Y, decode_erp(buf[1],  buf[0]));

		/* volume */
		input_report_असल(input_dev, ABS_RX, decode_erp(buf[17], buf[16]));
		/* tempo */
		input_report_असल(input_dev, ABS_RY, decode_erp(buf[11], buf[10]));
		/* swing */
		input_report_असल(input_dev, ABS_RZ, decode_erp(buf[5],  buf[4]));

		input_sync(input_dev);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम snd_caiaq_input_पढ़ो_io(काष्ठा snd_usb_caiaqdev *cdev,
				    अचिन्हित अक्षर *buf, अचिन्हित पूर्णांक len)
अणु
	काष्ठा input_dev *input_dev = cdev->input_dev;
	अचिन्हित लघु *keycode = input_dev->keycode;
	पूर्णांक i;

	अगर (!keycode)
		वापस;

	अगर (input_dev->id.product == USB_PID_RIGKONTROL2)
		क्रम (i = 0; i < len; i++)
			buf[i] = ~buf[i];

	क्रम (i = 0; i < input_dev->keycodemax && i < len * 8; i++)
		input_report_key(input_dev, keycode[i],
				 buf[i / 8] & (1 << (i % 8)));

	चयन (cdev->chip.usb_id) अणु
	हाल USB_ID(USB_VID_NATIVEINSTRUMENTS, USB_PID_KORECONTROLLER):
	हाल USB_ID(USB_VID_NATIVEINSTRUMENTS, USB_PID_KORECONTROLLER2):
		input_report_असल(cdev->input_dev, ABS_MISC, 255 - buf[4]);
		अवरोध;
	हाल USB_ID(USB_VID_NATIVEINSTRUMENTS, USB_PID_TRAKTORKONTROLX1):
		/* rotary encoders */
		input_report_असल(cdev->input_dev, ABS_X, buf[5] & 0xf);
		input_report_असल(cdev->input_dev, ABS_Y, buf[5] >> 4);
		input_report_असल(cdev->input_dev, ABS_Z, buf[6] & 0xf);
		input_report_असल(cdev->input_dev, ABS_MISC, buf[6] >> 4);
		अवरोध;
	पूर्ण

	input_sync(input_dev);
पूर्ण

#घोषणा TKS4_MSGBLOCK_SIZE	16

अटल व्योम snd_usb_caiaq_tks4_dispatch(काष्ठा snd_usb_caiaqdev *cdev,
					स्थिर अचिन्हित अक्षर *buf,
					अचिन्हित पूर्णांक len)
अणु
	काष्ठा device *dev = caiaqdev_to_dev(cdev);

	जबतक (len) अणु
		अचिन्हित पूर्णांक i, block_id = (buf[0] << 8) | buf[1];

		चयन (block_id) अणु
		हाल 0:
			/* buttons */
			क्रम (i = 0; i < KONTROLS4_BUTTONS; i++)
				input_report_key(cdev->input_dev, KONTROLS4_BUTTON(i),
						 (buf[4 + (i / 8)] >> (i % 8)) & 1);
			अवरोध;

		हाल 1:
			/* left wheel */
			input_report_असल(cdev->input_dev, KONTROLS4_ABS(36), buf[9] | ((buf[8] & 0x3) << 8));
			/* right wheel */
			input_report_असल(cdev->input_dev, KONTROLS4_ABS(37), buf[13] | ((buf[12] & 0x3) << 8));

			/* rotary encoders */
			input_report_असल(cdev->input_dev, KONTROLS4_ABS(38), buf[3] & 0xf);
			input_report_असल(cdev->input_dev, KONTROLS4_ABS(39), buf[4] >> 4);
			input_report_असल(cdev->input_dev, KONTROLS4_ABS(40), buf[4] & 0xf);
			input_report_असल(cdev->input_dev, KONTROLS4_ABS(41), buf[5] >> 4);
			input_report_असल(cdev->input_dev, KONTROLS4_ABS(42), buf[5] & 0xf);
			input_report_असल(cdev->input_dev, KONTROLS4_ABS(43), buf[6] >> 4);
			input_report_असल(cdev->input_dev, KONTROLS4_ABS(44), buf[6] & 0xf);
			input_report_असल(cdev->input_dev, KONTROLS4_ABS(45), buf[7] >> 4);
			input_report_असल(cdev->input_dev, KONTROLS4_ABS(46), buf[7] & 0xf);

			अवरोध;
		हाल 2:
			/* Volume Fader Channel D */
			snd_caiaq_input_report_असल(cdev, KONTROLS4_ABS(0), buf, 1);
			/* Volume Fader Channel B */
			snd_caiaq_input_report_असल(cdev, KONTROLS4_ABS(1), buf, 2);
			/* Volume Fader Channel A */
			snd_caiaq_input_report_असल(cdev, KONTROLS4_ABS(2), buf, 3);
			/* Volume Fader Channel C */
			snd_caiaq_input_report_असल(cdev, KONTROLS4_ABS(3), buf, 4);
			/* Loop Volume */
			snd_caiaq_input_report_असल(cdev, KONTROLS4_ABS(4), buf, 6);
			/* Crossfader */
			snd_caiaq_input_report_असल(cdev, KONTROLS4_ABS(7), buf, 7);

			अवरोध;

		हाल 3:
			/* Tempo Fader R */
			snd_caiaq_input_report_असल(cdev, KONTROLS4_ABS(6), buf, 3);
			/* Tempo Fader L */
			snd_caiaq_input_report_असल(cdev, KONTROLS4_ABS(5), buf, 4);
			/* Mic Volume */
			snd_caiaq_input_report_असल(cdev, KONTROLS4_ABS(8), buf, 6);
			/* Cue Mix */
			snd_caiaq_input_report_असल(cdev, KONTROLS4_ABS(9), buf, 7);

			अवरोध;

		हाल 4:
			/* Wheel distance sensor L */
			snd_caiaq_input_report_असल(cdev, KONTROLS4_ABS(10), buf, 1);
			/* Wheel distance sensor R */
			snd_caiaq_input_report_असल(cdev, KONTROLS4_ABS(11), buf, 2);
			/* Channel D EQ - Filter */
			snd_caiaq_input_report_असल(cdev, KONTROLS4_ABS(12), buf, 3);
			/* Channel D EQ - Low */
			snd_caiaq_input_report_असल(cdev, KONTROLS4_ABS(13), buf, 4);
			/* Channel D EQ - Mid */
			snd_caiaq_input_report_असल(cdev, KONTROLS4_ABS(14), buf, 5);
			/* Channel D EQ - Hi */
			snd_caiaq_input_report_असल(cdev, KONTROLS4_ABS(15), buf, 6);
			/* FX2 - dry/wet */
			snd_caiaq_input_report_असल(cdev, KONTROLS4_ABS(16), buf, 7);

			अवरोध;

		हाल 5:
			/* FX2 - 1 */
			snd_caiaq_input_report_असल(cdev, KONTROLS4_ABS(17), buf, 1);
			/* FX2 - 2 */
			snd_caiaq_input_report_असल(cdev, KONTROLS4_ABS(18), buf, 2);
			/* FX2 - 3 */
			snd_caiaq_input_report_असल(cdev, KONTROLS4_ABS(19), buf, 3);
			/* Channel B EQ - Filter */
			snd_caiaq_input_report_असल(cdev, KONTROLS4_ABS(20), buf, 4);
			/* Channel B EQ - Low */
			snd_caiaq_input_report_असल(cdev, KONTROLS4_ABS(21), buf, 5);
			/* Channel B EQ - Mid */
			snd_caiaq_input_report_असल(cdev, KONTROLS4_ABS(22), buf, 6);
			/* Channel B EQ - Hi */
			snd_caiaq_input_report_असल(cdev, KONTROLS4_ABS(23), buf, 7);

			अवरोध;

		हाल 6:
			/* Channel A EQ - Filter */
			snd_caiaq_input_report_असल(cdev, KONTROLS4_ABS(24), buf, 1);
			/* Channel A EQ - Low */
			snd_caiaq_input_report_असल(cdev, KONTROLS4_ABS(25), buf, 2);
			/* Channel A EQ - Mid */
			snd_caiaq_input_report_असल(cdev, KONTROLS4_ABS(26), buf, 3);
			/* Channel A EQ - Hi */
			snd_caiaq_input_report_असल(cdev, KONTROLS4_ABS(27), buf, 4);
			/* Channel C EQ - Filter */
			snd_caiaq_input_report_असल(cdev, KONTROLS4_ABS(28), buf, 5);
			/* Channel C EQ - Low */
			snd_caiaq_input_report_असल(cdev, KONTROLS4_ABS(29), buf, 6);
			/* Channel C EQ - Mid */
			snd_caiaq_input_report_असल(cdev, KONTROLS4_ABS(30), buf, 7);

			अवरोध;

		हाल 7:
			/* Channel C EQ - Hi */
			snd_caiaq_input_report_असल(cdev, KONTROLS4_ABS(31), buf, 1);
			/* FX1 - wet/dry */
			snd_caiaq_input_report_असल(cdev, KONTROLS4_ABS(32), buf, 2);
			/* FX1 - 1 */
			snd_caiaq_input_report_असल(cdev, KONTROLS4_ABS(33), buf, 3);
			/* FX1 - 2 */
			snd_caiaq_input_report_असल(cdev, KONTROLS4_ABS(34), buf, 4);
			/* FX1 - 3 */
			snd_caiaq_input_report_असल(cdev, KONTROLS4_ABS(35), buf, 5);

			अवरोध;

		शेष:
			dev_dbg(dev, "%s(): bogus block (id %d)\n",
				__func__, block_id);
			वापस;
		पूर्ण

		len -= TKS4_MSGBLOCK_SIZE;
		buf += TKS4_MSGBLOCK_SIZE;
	पूर्ण

	input_sync(cdev->input_dev);
पूर्ण

#घोषणा MASCHINE_MSGBLOCK_SIZE 2

अटल व्योम snd_usb_caiaq_maschine_dispatch(काष्ठा snd_usb_caiaqdev *cdev,
					स्थिर अचिन्हित अक्षर *buf,
					अचिन्हित पूर्णांक len)
अणु
	अचिन्हित पूर्णांक i, pad_id;
	__le16 *pressure = (__le16 *) buf;

	क्रम (i = 0; i < MASCHINE_PADS; i++) अणु
		pad_id = le16_to_cpu(*pressure) >> 12;
		input_report_असल(cdev->input_dev, MASCHINE_PAD(pad_id),
				 le16_to_cpu(*pressure) & 0xfff);
		pressure++;
	पूर्ण

	input_sync(cdev->input_dev);
पूर्ण

अटल व्योम snd_usb_caiaq_ep4_reply_dispatch(काष्ठा urb *urb)
अणु
	काष्ठा snd_usb_caiaqdev *cdev = urb->context;
	अचिन्हित अक्षर *buf = urb->transfer_buffer;
	काष्ठा device *dev = &urb->dev->dev;
	पूर्णांक ret;

	अगर (urb->status || !cdev || urb != cdev->ep4_in_urb)
		वापस;

	चयन (cdev->chip.usb_id) अणु
	हाल USB_ID(USB_VID_NATIVEINSTRUMENTS, USB_PID_TRAKTORKONTROLX1):
		अगर (urb->actual_length < 24)
			जाओ requeue;

		अगर (buf[0] & 0x3)
			snd_caiaq_input_पढ़ो_io(cdev, buf + 1, 7);

		अगर (buf[0] & 0x4)
			snd_caiaq_input_पढ़ो_analog(cdev, buf + 8, 16);

		अवरोध;

	हाल USB_ID(USB_VID_NATIVEINSTRUMENTS, USB_PID_TRAKTORKONTROLS4):
		snd_usb_caiaq_tks4_dispatch(cdev, buf, urb->actual_length);
		अवरोध;

	हाल USB_ID(USB_VID_NATIVEINSTRUMENTS, USB_PID_MASCHINECONTROLLER):
		अगर (urb->actual_length < (MASCHINE_PADS * MASCHINE_MSGBLOCK_SIZE))
			जाओ requeue;

		snd_usb_caiaq_maschine_dispatch(cdev, buf, urb->actual_length);
		अवरोध;
	पूर्ण

requeue:
	cdev->ep4_in_urb->actual_length = 0;
	ret = usb_submit_urb(cdev->ep4_in_urb, GFP_ATOMIC);
	अगर (ret < 0)
		dev_err(dev, "unable to submit urb. OOM!?\n");
पूर्ण

अटल पूर्णांक snd_usb_caiaq_input_खोलो(काष्ठा input_dev *idev)
अणु
	काष्ठा snd_usb_caiaqdev *cdev = input_get_drvdata(idev);

	अगर (!cdev)
		वापस -EINVAL;

	चयन (cdev->chip.usb_id) अणु
	हाल USB_ID(USB_VID_NATIVEINSTRUMENTS, USB_PID_TRAKTORKONTROLX1):
	हाल USB_ID(USB_VID_NATIVEINSTRUMENTS, USB_PID_TRAKTORKONTROLS4):
	हाल USB_ID(USB_VID_NATIVEINSTRUMENTS, USB_PID_MASCHINECONTROLLER):
		अगर (usb_submit_urb(cdev->ep4_in_urb, GFP_KERNEL) != 0)
			वापस -EIO;
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम snd_usb_caiaq_input_बंद(काष्ठा input_dev *idev)
अणु
	काष्ठा snd_usb_caiaqdev *cdev = input_get_drvdata(idev);

	अगर (!cdev)
		वापस;

	चयन (cdev->chip.usb_id) अणु
	हाल USB_ID(USB_VID_NATIVEINSTRUMENTS, USB_PID_TRAKTORKONTROLX1):
	हाल USB_ID(USB_VID_NATIVEINSTRUMENTS, USB_PID_TRAKTORKONTROLS4):
	हाल USB_ID(USB_VID_NATIVEINSTRUMENTS, USB_PID_MASCHINECONTROLLER):
		usb_समाप्त_urb(cdev->ep4_in_urb);
		अवरोध;
	पूर्ण
पूर्ण

व्योम snd_usb_caiaq_input_dispatch(काष्ठा snd_usb_caiaqdev *cdev,
				  अक्षर *buf,
				  अचिन्हित पूर्णांक len)
अणु
	अगर (!cdev->input_dev || len < 1)
		वापस;

	चयन (buf[0]) अणु
	हाल EP1_CMD_READ_ANALOG:
		snd_caiaq_input_पढ़ो_analog(cdev, buf + 1, len - 1);
		अवरोध;
	हाल EP1_CMD_READ_ERP:
		snd_caiaq_input_पढ़ो_erp(cdev, buf + 1, len - 1);
		अवरोध;
	हाल EP1_CMD_READ_IO:
		snd_caiaq_input_पढ़ो_io(cdev, buf + 1, len - 1);
		अवरोध;
	पूर्ण
पूर्ण

पूर्णांक snd_usb_caiaq_input_init(काष्ठा snd_usb_caiaqdev *cdev)
अणु
	काष्ठा usb_device *usb_dev = cdev->chip.dev;
	काष्ठा input_dev *input;
	पूर्णांक i, ret = 0;

	input = input_allocate_device();
	अगर (!input)
		वापस -ENOMEM;

	usb_make_path(usb_dev, cdev->phys, माप(cdev->phys));
	strlcat(cdev->phys, "/input0", माप(cdev->phys));

	input->name = cdev->product_name;
	input->phys = cdev->phys;
	usb_to_input_id(usb_dev, &input->id);
	input->dev.parent = &usb_dev->dev;

	input_set_drvdata(input, cdev);

	चयन (cdev->chip.usb_id) अणु
	हाल USB_ID(USB_VID_NATIVEINSTRUMENTS, USB_PID_RIGKONTROL2):
		input->evbit[0] = BIT_MASK(EV_KEY) | BIT_MASK(EV_ABS);
		input->असलbit[0] = BIT_MASK(ABS_X) | BIT_MASK(ABS_Y) |
			BIT_MASK(ABS_Z);
		BUILD_BUG_ON(माप(cdev->keycode) < माप(keycode_rk2));
		स_नकल(cdev->keycode, keycode_rk2, माप(keycode_rk2));
		input->keycodemax = ARRAY_SIZE(keycode_rk2);
		input_set_असल_params(input, ABS_X, 0, 4096, 0, 10);
		input_set_असल_params(input, ABS_Y, 0, 4096, 0, 10);
		input_set_असल_params(input, ABS_Z, 0, 4096, 0, 10);
		snd_usb_caiaq_set_स्वतः_msg(cdev, 1, 10, 0);
		अवरोध;
	हाल USB_ID(USB_VID_NATIVEINSTRUMENTS, USB_PID_RIGKONTROL3):
		input->evbit[0] = BIT_MASK(EV_KEY) | BIT_MASK(EV_ABS);
		input->असलbit[0] = BIT_MASK(ABS_X) | BIT_MASK(ABS_Y) |
			BIT_MASK(ABS_Z);
		BUILD_BUG_ON(माप(cdev->keycode) < माप(keycode_rk3));
		स_नकल(cdev->keycode, keycode_rk3, माप(keycode_rk3));
		input->keycodemax = ARRAY_SIZE(keycode_rk3);
		input_set_असल_params(input, ABS_X, 0, 1024, 0, 10);
		input_set_असल_params(input, ABS_Y, 0, 1024, 0, 10);
		input_set_असल_params(input, ABS_Z, 0, 1024, 0, 10);
		snd_usb_caiaq_set_स्वतः_msg(cdev, 1, 10, 0);
		अवरोध;
	हाल USB_ID(USB_VID_NATIVEINSTRUMENTS, USB_PID_AK1):
		input->evbit[0] = BIT_MASK(EV_KEY) | BIT_MASK(EV_ABS);
		input->असलbit[0] = BIT_MASK(ABS_X);
		BUILD_BUG_ON(माप(cdev->keycode) < माप(keycode_ak1));
		स_नकल(cdev->keycode, keycode_ak1, माप(keycode_ak1));
		input->keycodemax = ARRAY_SIZE(keycode_ak1);
		input_set_असल_params(input, ABS_X, 0, 999, 0, 10);
		snd_usb_caiaq_set_स्वतः_msg(cdev, 1, 0, 5);
		अवरोध;
	हाल USB_ID(USB_VID_NATIVEINSTRUMENTS, USB_PID_KORECONTROLLER):
	हाल USB_ID(USB_VID_NATIVEINSTRUMENTS, USB_PID_KORECONTROLLER2):
		input->evbit[0] = BIT_MASK(EV_KEY) | BIT_MASK(EV_ABS);
		input->असलbit[0] = BIT_MASK(ABS_HAT0X) | BIT_MASK(ABS_HAT0Y) |
				   BIT_MASK(ABS_HAT1X) | BIT_MASK(ABS_HAT1Y) |
				   BIT_MASK(ABS_HAT2X) | BIT_MASK(ABS_HAT2Y) |
				   BIT_MASK(ABS_HAT3X) | BIT_MASK(ABS_HAT3Y) |
				   BIT_MASK(ABS_X) | BIT_MASK(ABS_Y) |
				   BIT_MASK(ABS_Z);
		input->असलbit[BIT_WORD(ABS_MISC)] |= BIT_MASK(ABS_MISC);
		BUILD_BUG_ON(माप(cdev->keycode) < माप(keycode_kore));
		स_नकल(cdev->keycode, keycode_kore, माप(keycode_kore));
		input->keycodemax = ARRAY_SIZE(keycode_kore);
		input_set_असल_params(input, ABS_HAT0X, 0, 999, 0, 10);
		input_set_असल_params(input, ABS_HAT0Y, 0, 999, 0, 10);
		input_set_असल_params(input, ABS_HAT1X, 0, 999, 0, 10);
		input_set_असल_params(input, ABS_HAT1Y, 0, 999, 0, 10);
		input_set_असल_params(input, ABS_HAT2X, 0, 999, 0, 10);
		input_set_असल_params(input, ABS_HAT2Y, 0, 999, 0, 10);
		input_set_असल_params(input, ABS_HAT3X, 0, 999, 0, 10);
		input_set_असल_params(input, ABS_HAT3Y, 0, 999, 0, 10);
		input_set_असल_params(input, ABS_X, 0, 4096, 0, 10);
		input_set_असल_params(input, ABS_Y, 0, 4096, 0, 10);
		input_set_असल_params(input, ABS_Z, 0, 4096, 0, 10);
		input_set_असल_params(input, ABS_MISC, 0, 255, 0, 1);
		snd_usb_caiaq_set_स्वतः_msg(cdev, 1, 10, 5);
		अवरोध;
	हाल USB_ID(USB_VID_NATIVEINSTRUMENTS, USB_PID_TRAKTORKONTROLX1):
		input->evbit[0] = BIT_MASK(EV_KEY) | BIT_MASK(EV_ABS);
		input->असलbit[0] = BIT_MASK(ABS_HAT0X) | BIT_MASK(ABS_HAT0Y) |
				   BIT_MASK(ABS_HAT1X) | BIT_MASK(ABS_HAT1Y) |
				   BIT_MASK(ABS_HAT2X) | BIT_MASK(ABS_HAT2Y) |
				   BIT_MASK(ABS_HAT3X) | BIT_MASK(ABS_HAT3Y) |
				   BIT_MASK(ABS_X) | BIT_MASK(ABS_Y) |
				   BIT_MASK(ABS_Z);
		input->असलbit[BIT_WORD(ABS_MISC)] |= BIT_MASK(ABS_MISC);
		BUILD_BUG_ON(माप(cdev->keycode) < KONTROLX1_INPUTS);
		क्रम (i = 0; i < KONTROLX1_INPUTS; i++)
			cdev->keycode[i] = BTN_MISC + i;
		input->keycodemax = KONTROLX1_INPUTS;

		/* analog potentiometers */
		input_set_असल_params(input, ABS_HAT0X, 0, 4096, 0, 10);
		input_set_असल_params(input, ABS_HAT0Y, 0, 4096, 0, 10);
		input_set_असल_params(input, ABS_HAT1X, 0, 4096, 0, 10);
		input_set_असल_params(input, ABS_HAT1Y, 0, 4096, 0, 10);
		input_set_असल_params(input, ABS_HAT2X, 0, 4096, 0, 10);
		input_set_असल_params(input, ABS_HAT2Y, 0, 4096, 0, 10);
		input_set_असल_params(input, ABS_HAT3X, 0, 4096, 0, 10);
		input_set_असल_params(input, ABS_HAT3Y, 0, 4096, 0, 10);

		/* rotary encoders */
		input_set_असल_params(input, ABS_X, 0, 0xf, 0, 1);
		input_set_असल_params(input, ABS_Y, 0, 0xf, 0, 1);
		input_set_असल_params(input, ABS_Z, 0, 0xf, 0, 1);
		input_set_असल_params(input, ABS_MISC, 0, 0xf, 0, 1);

		cdev->ep4_in_urb = usb_alloc_urb(0, GFP_KERNEL);
		अगर (!cdev->ep4_in_urb) अणु
			ret = -ENOMEM;
			जाओ निकास_मुक्त_idev;
		पूर्ण

		usb_fill_bulk_urb(cdev->ep4_in_urb, usb_dev,
				  usb_rcvbulkpipe(usb_dev, 0x4),
				  cdev->ep4_in_buf, EP4_बफ_मानE,
				  snd_usb_caiaq_ep4_reply_dispatch, cdev);
		ret = usb_urb_ep_type_check(cdev->ep4_in_urb);
		अगर (ret < 0)
			जाओ निकास_मुक्त_idev;

		snd_usb_caiaq_set_स्वतः_msg(cdev, 1, 10, 5);

		अवरोध;

	हाल USB_ID(USB_VID_NATIVEINSTRUMENTS, USB_PID_TRAKTORKONTROLS4):
		input->evbit[0] = BIT_MASK(EV_KEY) | BIT_MASK(EV_ABS);
		BUILD_BUG_ON(माप(cdev->keycode) < KONTROLS4_BUTTONS);
		क्रम (i = 0; i < KONTROLS4_BUTTONS; i++)
			cdev->keycode[i] = KONTROLS4_BUTTON(i);
		input->keycodemax = KONTROLS4_BUTTONS;

		क्रम (i = 0; i < KONTROLS4_AXIS; i++) अणु
			पूर्णांक axis = KONTROLS4_ABS(i);
			input->असलbit[BIT_WORD(axis)] |= BIT_MASK(axis);
		पूर्ण

		/* 36 analog potentiometers and faders */
		क्रम (i = 0; i < 36; i++)
			input_set_असल_params(input, KONTROLS4_ABS(i), 0, 0xfff, 0, 10);

		/* 2 encoder wheels */
		input_set_असल_params(input, KONTROLS4_ABS(36), 0, 0x3ff, 0, 1);
		input_set_असल_params(input, KONTROLS4_ABS(37), 0, 0x3ff, 0, 1);

		/* 9 rotary encoders */
		क्रम (i = 0; i < 9; i++)
			input_set_असल_params(input, KONTROLS4_ABS(38+i), 0, 0xf, 0, 1);

		cdev->ep4_in_urb = usb_alloc_urb(0, GFP_KERNEL);
		अगर (!cdev->ep4_in_urb) अणु
			ret = -ENOMEM;
			जाओ निकास_मुक्त_idev;
		पूर्ण

		usb_fill_bulk_urb(cdev->ep4_in_urb, usb_dev,
				  usb_rcvbulkpipe(usb_dev, 0x4),
				  cdev->ep4_in_buf, EP4_बफ_मानE,
				  snd_usb_caiaq_ep4_reply_dispatch, cdev);
		ret = usb_urb_ep_type_check(cdev->ep4_in_urb);
		अगर (ret < 0)
			जाओ निकास_मुक्त_idev;

		snd_usb_caiaq_set_स्वतः_msg(cdev, 1, 10, 5);

		अवरोध;

	हाल USB_ID(USB_VID_NATIVEINSTRUMENTS, USB_PID_MASCHINECONTROLLER):
		input->evbit[0] = BIT_MASK(EV_KEY) | BIT_MASK(EV_ABS);
		input->असलbit[0] = BIT_MASK(ABS_HAT0X) | BIT_MASK(ABS_HAT0Y) |
			BIT_MASK(ABS_HAT1X) | BIT_MASK(ABS_HAT1Y) |
			BIT_MASK(ABS_HAT2X) | BIT_MASK(ABS_HAT2Y) |
			BIT_MASK(ABS_HAT3X) | BIT_MASK(ABS_HAT3Y) |
			BIT_MASK(ABS_RX) | BIT_MASK(ABS_RY) |
			BIT_MASK(ABS_RZ);

		BUILD_BUG_ON(माप(cdev->keycode) < माप(keycode_maschine));
		स_नकल(cdev->keycode, keycode_maschine, माप(keycode_maschine));
		input->keycodemax = ARRAY_SIZE(keycode_maschine);

		क्रम (i = 0; i < MASCHINE_PADS; i++) अणु
			input->असलbit[0] |= MASCHINE_PAD(i);
			input_set_असल_params(input, MASCHINE_PAD(i), 0, 0xfff, 5, 10);
		पूर्ण

		input_set_असल_params(input, ABS_HAT0X, 0, 999, 0, 10);
		input_set_असल_params(input, ABS_HAT0Y, 0, 999, 0, 10);
		input_set_असल_params(input, ABS_HAT1X, 0, 999, 0, 10);
		input_set_असल_params(input, ABS_HAT1Y, 0, 999, 0, 10);
		input_set_असल_params(input, ABS_HAT2X, 0, 999, 0, 10);
		input_set_असल_params(input, ABS_HAT2Y, 0, 999, 0, 10);
		input_set_असल_params(input, ABS_HAT3X, 0, 999, 0, 10);
		input_set_असल_params(input, ABS_HAT3Y, 0, 999, 0, 10);
		input_set_असल_params(input, ABS_RX, 0, 999, 0, 10);
		input_set_असल_params(input, ABS_RY, 0, 999, 0, 10);
		input_set_असल_params(input, ABS_RZ, 0, 999, 0, 10);

		cdev->ep4_in_urb = usb_alloc_urb(0, GFP_KERNEL);
		अगर (!cdev->ep4_in_urb) अणु
			ret = -ENOMEM;
			जाओ निकास_मुक्त_idev;
		पूर्ण

		usb_fill_bulk_urb(cdev->ep4_in_urb, usb_dev,
				  usb_rcvbulkpipe(usb_dev, 0x4),
				  cdev->ep4_in_buf, EP4_बफ_मानE,
				  snd_usb_caiaq_ep4_reply_dispatch, cdev);
		ret = usb_urb_ep_type_check(cdev->ep4_in_urb);
		अगर (ret < 0)
			जाओ निकास_मुक्त_idev;

		snd_usb_caiaq_set_स्वतः_msg(cdev, 1, 10, 5);
		अवरोध;

	शेष:
		/* no input methods supported on this device */
		जाओ निकास_मुक्त_idev;
	पूर्ण

	input->खोलो = snd_usb_caiaq_input_खोलो;
	input->बंद = snd_usb_caiaq_input_बंद;
	input->keycode = cdev->keycode;
	input->keycodesize = माप(अचिन्हित लघु);
	क्रम (i = 0; i < input->keycodemax; i++)
		__set_bit(cdev->keycode[i], input->keybit);

	cdev->input_dev = input;

	ret = input_रेजिस्टर_device(input);
	अगर (ret < 0)
		जाओ निकास_मुक्त_idev;

	वापस 0;

निकास_मुक्त_idev:
	input_मुक्त_device(input);
	cdev->input_dev = शून्य;
	वापस ret;
पूर्ण

व्योम snd_usb_caiaq_input_मुक्त(काष्ठा snd_usb_caiaqdev *cdev)
अणु
	अगर (!cdev || !cdev->input_dev)
		वापस;

	usb_समाप्त_urb(cdev->ep4_in_urb);
	usb_मुक्त_urb(cdev->ep4_in_urb);
	cdev->ep4_in_urb = शून्य;

	input_unरेजिस्टर_device(cdev->input_dev);
	cdev->input_dev = शून्य;
पूर्ण
