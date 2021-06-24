<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *  cx18 functions to query card hardware
 *
 *  Derived from ivtv-cards.c
 *
 *  Copyright (C) 2007  Hans Verkuil <hverkuil@xs4all.nl>
 *  Copyright (C) 2008  Andy Walls <awalls@md.metrocast.net>
 */

/* hardware flags */
#घोषणा CX18_HW_TUNER			(1 << 0)
#घोषणा CX18_HW_TVEEPROM		(1 << 1)
#घोषणा CX18_HW_CS5345			(1 << 2)
#घोषणा CX18_HW_DVB			(1 << 3)
#घोषणा CX18_HW_418_AV			(1 << 4)
#घोषणा CX18_HW_GPIO_MUX		(1 << 5)
#घोषणा CX18_HW_GPIO_RESET_CTRL		(1 << 6)
#घोषणा CX18_HW_Z8F0811_IR_HAUP		(1 << 7)

/* video inमाला_दो */
#घोषणा	CX18_CARD_INPUT_VID_TUNER	1
#घोषणा	CX18_CARD_INPUT_SVIDEO1		2
#घोषणा	CX18_CARD_INPUT_SVIDEO2		3
#घोषणा	CX18_CARD_INPUT_COMPOSITE1	4
#घोषणा	CX18_CARD_INPUT_COMPOSITE2	5
#घोषणा	CX18_CARD_INPUT_COMPONENT1	6

/* audio inमाला_दो */
#घोषणा	CX18_CARD_INPUT_AUD_TUNER	1
#घोषणा	CX18_CARD_INPUT_LINE_IN1	2
#घोषणा	CX18_CARD_INPUT_LINE_IN2	3

#घोषणा CX18_CARD_MAX_VIDEO_INPUTS 6
#घोषणा CX18_CARD_MAX_AUDIO_INPUTS 3
#घोषणा CX18_CARD_MAX_TUNERS	   2

/* V4L2 capability aliases */
#घोषणा CX18_CAP_ENCODER (V4L2_CAP_VIDEO_CAPTURE | V4L2_CAP_TUNER | \
			  V4L2_CAP_AUDIO | V4L2_CAP_READWRITE | \
			  V4L2_CAP_STREAMING | V4L2_CAP_VBI_CAPTURE | \
			  V4L2_CAP_SLICED_VBI_CAPTURE)

काष्ठा cx18_card_video_input अणु
	u8  video_type;		/* video input type */
	u8  audio_index;	/* index in cx18_card_audio_input array */
	u32 video_input;	/* hardware video input */
पूर्ण;

काष्ठा cx18_card_audio_input अणु
	u8  audio_type;		/* audio input type */
	u32 audio_input;	/* hardware audio input */
	u16 muxer_input;	/* hardware muxer input क्रम boards with a
				   multiplexer chip */
पूर्ण;

काष्ठा cx18_card_pci_info अणु
	u16 device;
	u16 subप्रणाली_venकरोr;
	u16 subप्रणाली_device;
पूर्ण;

/* GPIO definitions */

/* The mask is the set of bits used by the operation */

काष्ठा cx18_gpio_init अणु /* set initial GPIO सूची and OUT values */
	u32 direction;	/* सूची setting. Leave to 0 अगर no init is needed */
	u32 initial_value;
पूर्ण;

काष्ठा cx18_gpio_i2c_slave_reset अणु
	u32 active_lo_mask; /* GPIO outमाला_दो that reset i2c chips when low */
	u32 active_hi_mask; /* GPIO outमाला_दो that reset i2c chips when high */
	पूर्णांक msecs_निश्चितed; /* समय period reset must reमुख्य निश्चितed */
	पूर्णांक msecs_recovery; /* समय after deनिश्चित क्रम chips to be पढ़ोy */
	u32 ir_reset_mask;  /* GPIO to reset the Zilog Z8F0811 IR controller */
पूर्ण;

काष्ठा cx18_gpio_audio_input अणु	/* select tuner/line in input */
	u32 mask;		/* leave to 0 अगर not supported */
	u32 tuner;
	u32 linein;
	u32 radio;
पूर्ण;

काष्ठा cx18_card_tuner अणु
	v4l2_std_id std;	/* standard क्रम which the tuner is suitable */
	पूर्णांक	    tuner;	/* tuner ID (from tuner.h) */
पूर्ण;

काष्ठा cx18_card_tuner_i2c अणु
	अचिन्हित लघु radio[2];/* radio tuner i2c address to probe */
	अचिन्हित लघु demod[3];/* demodulator i2c address to probe */
	अचिन्हित लघु tv[4];	/* tv tuner i2c addresses to probe */
पूर्ण;

काष्ठा cx18_ddr अणु		/* DDR config data */
	u32 chip_config;
	u32 refresh;
	u32 timing1;
	u32 timing2;
	u32 tune_lane;
	u32 initial_emrs;
पूर्ण;

/* क्रम card inक्रमmation/parameters */
काष्ठा cx18_card अणु
	पूर्णांक type;
	अक्षर *name;
	अक्षर *comment;
	u32 v4l2_capabilities;
	u32 hw_audio_ctrl;	/* hardware used क्रम the V4L2 controls (only
				   1 dev allowed currently) */
	u32 hw_muxer;		/* hardware used to multiplex audio input */
	u32 hw_all;		/* all hardware used by the board */
	काष्ठा cx18_card_video_input video_inमाला_दो[CX18_CARD_MAX_VIDEO_INPUTS];
	काष्ठा cx18_card_audio_input audio_inमाला_दो[CX18_CARD_MAX_AUDIO_INPUTS];
	काष्ठा cx18_card_audio_input radio_input;

	/* GPIO card-specअगरic settings */
	u8 xceive_pin;		/* XCeive tuner GPIO reset pin */
	काष्ठा cx18_gpio_init		 gpio_init;
	काष्ठा cx18_gpio_i2c_slave_reset gpio_i2c_slave_reset;
	काष्ठा cx18_gpio_audio_input    gpio_audio_input;

	काष्ठा cx18_card_tuner tuners[CX18_CARD_MAX_TUNERS];
	काष्ठा cx18_card_tuner_i2c *i2c;

	काष्ठा cx18_ddr ddr;

	/* list of device and subप्रणाली venकरोr/devices that
	   correspond to this card type. */
	स्थिर काष्ठा cx18_card_pci_info *pci_list;
पूर्ण;

पूर्णांक cx18_get_input(काष्ठा cx18 *cx, u16 index, काष्ठा v4l2_input *input);
पूर्णांक cx18_get_audio_input(काष्ठा cx18 *cx, u16 index, काष्ठा v4l2_audio *input);
स्थिर काष्ठा cx18_card *cx18_get_card(u16 index);
