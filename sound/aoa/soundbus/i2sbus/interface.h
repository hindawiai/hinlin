<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * i2sbus driver -- पूर्णांकerface रेजिस्टर definitions
 *
 * Copyright 2006 Johannes Berg <johannes@sipsolutions.net>
 */
#अगर_अघोषित __I2SBUS_INTERFACE_H
#घोषणा __I2SBUS_INTERFACE_H

/* i2s bus control रेजिस्टरs, at least what we know about them */

#घोषणा __PAD(m,n) u8 __pad##m[n]
#घोषणा _PAD(line, n) __PAD(line, n)
#घोषणा PAD(n) _PAD(__LINE__, (n))
काष्ठा i2s_पूर्णांकerface_regs अणु
	__le32 पूर्णांकr_ctl;	/* 0x00 */
	PAD(12);
	__le32 serial_क्रमmat;	/* 0x10 */
	PAD(12);
	__le32 codec_msg_out;	/* 0x20 */
	PAD(12);
	__le32 codec_msg_in;	/* 0x30 */
	PAD(12);
	__le32 frame_count;	/* 0x40 */
	PAD(12);
	__le32 frame_match;	/* 0x50 */
	PAD(12);
	__le32 data_word_sizes;	/* 0x60 */
	PAD(12);
	__le32 peak_level_sel;	/* 0x70 */
	PAD(12);
	__le32 peak_level_in0;	/* 0x80 */
	PAD(12);
	__le32 peak_level_in1;	/* 0x90 */
	PAD(12);
	/* total size: 0x100 bytes */
पूर्ण  __attribute__((__packed__));

/* पूर्णांकerrupt रेजिस्टर is just a bitfield with
 * पूर्णांकerrupt enable and pending bits */
#घोषणा I2S_REG_INTR_CTL		0x00
#	define I2S_INT_FRAME_COUNT		(1<<31)
#	define I2S_PENDING_FRAME_COUNT		(1<<30)
#	define I2S_INT_MESSAGE_FLAG		(1<<29)
#	define I2S_PENDING_MESSAGE_FLAG		(1<<28)
#	define I2S_INT_NEW_PEAK			(1<<27)
#	define I2S_PENDING_NEW_PEAK		(1<<26)
#	define I2S_INT_CLOCKS_STOPPED		(1<<25)
#	define I2S_PENDING_CLOCKS_STOPPED	(1<<24)
#	define I2S_INT_EXTERNAL_SYNC_ERROR	(1<<23)
#	define I2S_PENDING_EXTERNAL_SYNC_ERROR	(1<<22)
#	define I2S_INT_EXTERNAL_SYNC_OK		(1<<21)
#	define I2S_PENDING_EXTERNAL_SYNC_OK	(1<<20)
#	define I2S_INT_NEW_SAMPLE_RATE		(1<<19)
#	define I2S_PENDING_NEW_SAMPLE_RATE	(1<<18)
#	define I2S_INT_STATUS_FLAG		(1<<17)
#	define I2S_PENDING_STATUS_FLAG		(1<<16)

/* serial क्रमmat रेजिस्टर is more पूर्णांकeresting :)
 * It contains:
 *  - घड़ी source
 *  - MClk भागisor
 *  - SClk भागisor
 *  - SClk master flag
 *  - serial क्रमmat (sony, i2s 64x, i2s 32x, dav, siद_असल)
 *  - बाह्यal sample frequency पूर्णांकerrupt (करोn't understand)
 *  - बाह्यal sample frequency
 */
#घोषणा I2S_REG_SERIAL_FORMAT		0x10
/* घड़ी source. You get either 18.432, 45.1584 or 49.1520 MHz */
#	define I2S_SF_CLOCK_SOURCE_SHIFT	30
#	define I2S_SF_CLOCK_SOURCE_MASK		(3<<I2S_SF_CLOCK_SOURCE_SHIFT)
#	define I2S_SF_CLOCK_SOURCE_18MHz	(0<<I2S_SF_CLOCK_SOURCE_SHIFT)
#	define I2S_SF_CLOCK_SOURCE_45MHz	(1<<I2S_SF_CLOCK_SOURCE_SHIFT)
#	define I2S_SF_CLOCK_SOURCE_49MHz	(2<<I2S_SF_CLOCK_SOURCE_SHIFT)
/* also, let's define the exact घड़ी speeds here, in Hz */
#घोषणा I2S_CLOCK_SPEED_18MHz	18432000
#घोषणा I2S_CLOCK_SPEED_45MHz	45158400
#घोषणा I2S_CLOCK_SPEED_49MHz	49152000
/* MClk is the घड़ी that drives the codec, usually called its 'system clock'.
 * It is derived by taking only every 'divisor' tick of the घड़ी.
 */
#	define I2S_SF_MCLKDIV_SHIFT		24
#	define I2S_SF_MCLKDIV_MASK		(0x1F<<I2S_SF_MCLKDIV_SHIFT)
#	define I2S_SF_MCLKDIV_1			(0x14<<I2S_SF_MCLKDIV_SHIFT)
#	define I2S_SF_MCLKDIV_3			(0x13<<I2S_SF_MCLKDIV_SHIFT)
#	define I2S_SF_MCLKDIV_5			(0x12<<I2S_SF_MCLKDIV_SHIFT)
#	define I2S_SF_MCLKDIV_14		(0x0E<<I2S_SF_MCLKDIV_SHIFT)
#	define I2S_SF_MCLKDIV_OTHER(भाग)	(((भाग/2-1)<<I2S_SF_MCLKDIV_SHIFT)&I2S_SF_MCLKDIV_MASK)
अटल अंतरभूत पूर्णांक i2s_sf_mclkभाग(पूर्णांक भाग, पूर्णांक *out)
अणु
	पूर्णांक d;

	चयन(भाग) अणु
	हाल 1: *out |= I2S_SF_MCLKDIV_1; वापस 0;
	हाल 3: *out |= I2S_SF_MCLKDIV_3; वापस 0;
	हाल 5: *out |= I2S_SF_MCLKDIV_5; वापस 0;
	हाल 14: *out |= I2S_SF_MCLKDIV_14; वापस 0;
	शेष:
		अगर (भाग%2) वापस -1;
		d = भाग/2-1;
		अगर (d == 0x14 || d == 0x13 || d == 0x12 || d == 0x0E)
			वापस -1;
		*out |= I2S_SF_MCLKDIV_OTHER(भाग);
		वापस 0;
	पूर्ण
पूर्ण
/* SClk is the घड़ी that drives the i2s wire bus. Note that it is
 * derived from the MClk above by taking only every 'divisor' tick
 * of MClk.
 */
#	define I2S_SF_SCLKDIV_SHIFT		20
#	define I2S_SF_SCLKDIV_MASK		(0xF<<I2S_SF_SCLKDIV_SHIFT)
#	define I2S_SF_SCLKDIV_1			(8<<I2S_SF_SCLKDIV_SHIFT)
#	define I2S_SF_SCLKDIV_3			(9<<I2S_SF_SCLKDIV_SHIFT)
#	define I2S_SF_SCLKDIV_OTHER(भाग)	(((भाग/2-1)<<I2S_SF_SCLKDIV_SHIFT)&I2S_SF_SCLKDIV_MASK)
अटल अंतरभूत पूर्णांक i2s_sf_sclkभाग(पूर्णांक भाग, पूर्णांक *out)
अणु
	पूर्णांक d;

	चयन(भाग) अणु
	हाल 1: *out |= I2S_SF_SCLKDIV_1; वापस 0;
	हाल 3: *out |= I2S_SF_SCLKDIV_3; वापस 0;
	शेष:
		अगर (भाग%2) वापस -1;
		d = भाग/2-1;
		अगर (d == 8 || d == 9) वापस -1;
		*out |= I2S_SF_SCLKDIV_OTHER(भाग);
		वापस 0;
	पूर्ण
पूर्ण
#	define I2S_SF_SCLK_MASTER		(1<<19)
/* serial क्रमmat is the way the data is put to the i2s wire bus */
#	define I2S_SF_SERIAL_FORMAT_SHIFT	16
#	define I2S_SF_SERIAL_FORMAT_MASK	(7<<I2S_SF_SERIAL_FORMAT_SHIFT)
#	define I2S_SF_SERIAL_FORMAT_SONY	(0<<I2S_SF_SERIAL_FORMAT_SHIFT)
#	define I2S_SF_SERIAL_FORMAT_I2S_64X	(1<<I2S_SF_SERIAL_FORMAT_SHIFT)
#	define I2S_SF_SERIAL_FORMAT_I2S_32X	(2<<I2S_SF_SERIAL_FORMAT_SHIFT)
#	define I2S_SF_SERIAL_FORMAT_I2S_DAV	(4<<I2S_SF_SERIAL_FORMAT_SHIFT)
#	define I2S_SF_SERIAL_FORMAT_I2S_SILABS	(5<<I2S_SF_SERIAL_FORMAT_SHIFT)
/* unknown */
#	define I2S_SF_EXT_SAMPLE_FREQ_INT_SHIFT	12
#	define I2S_SF_EXT_SAMPLE_FREQ_INT_MASK	(0xF<<I2S_SF_SAMPLE_FREQ_INT_SHIFT)
/* probably gives बाह्यal frequency? */
#	define I2S_SF_EXT_SAMPLE_FREQ_MASK	0xFFF

/* used to send codec messages, but how isn't clear */
#घोषणा I2S_REG_CODEC_MSG_OUT		0x20

/* used to receive codec messages, but how isn't clear */
#घोषणा I2S_REG_CODEC_MSG_IN		0x30

/* frame count reg isn't clear to me yet, but probably useful */
#घोषणा I2S_REG_FRAME_COUNT		0x40

/* program to some value, and get पूर्णांकerrupt अगर frame count reaches it */
#घोषणा I2S_REG_FRAME_MATCH		0x50

/* this रेजिस्टर describes how the bus transfers data */
#घोषणा I2S_REG_DATA_WORD_SIZES		0x60
/* number of पूर्णांकerleaved input channels */
#	define I2S_DWS_NUM_CHANNELS_IN_SHIFT	24
#	define I2S_DWS_NUM_CHANNELS_IN_MASK	(0x1F<<I2S_DWS_NUM_CHANNELS_IN_SHIFT)
/* word size of input data */
#	define I2S_DWS_DATA_IN_SIZE_SHIFT	16
#	define I2S_DWS_DATA_IN_16BIT		(0<<I2S_DWS_DATA_IN_SIZE_SHIFT)
#	define I2S_DWS_DATA_IN_24BIT		(3<<I2S_DWS_DATA_IN_SIZE_SHIFT)
/* number of पूर्णांकerleaved output channels */
#	define I2S_DWS_NUM_CHANNELS_OUT_SHIFT	8
#	define I2S_DWS_NUM_CHANNELS_OUT_MASK	(0x1F<<I2S_DWS_NUM_CHANNELS_OUT_SHIFT)
/* word size of output data */
#	define I2S_DWS_DATA_OUT_SIZE_SHIFT	0
#	define I2S_DWS_DATA_OUT_16BIT		(0<<I2S_DWS_DATA_OUT_SIZE_SHIFT)
#	define I2S_DWS_DATA_OUT_24BIT		(3<<I2S_DWS_DATA_OUT_SIZE_SHIFT)


/* unknown */
#घोषणा I2S_REG_PEAK_LEVEL_SEL		0x70

/* unknown */
#घोषणा I2S_REG_PEAK_LEVEL_IN0		0x80

/* unknown */
#घोषणा I2S_REG_PEAK_LEVEL_IN1		0x90

#पूर्ण_अगर /* __I2SBUS_INTERFACE_H */
