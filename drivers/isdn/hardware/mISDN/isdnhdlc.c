<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * isdnhdlc.c  --  General purpose ISDN HDLC decoder.
 *
 * Copyright (C)
 *	2009	Karsten Keil		<keil@b1-प्रणालीs.de>
 *	2002	Wolfgang Mथञes		<wolfgang@iksw-muees.de>
 *	2001	Frode Isaksen		<fisaksen@bewan.com>
 *      2001	Kai Germaschewski	<kai.germaschewski@gmx.de>
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/crc-ccitt.h>
#समावेश <linux/bitrev.h>
#समावेश "isdnhdlc.h"

/*-------------------------------------------------------------------*/

MODULE_AUTHOR("Wolfgang Mथञes <wolfgang@iksw-muees.de>, "
	      "Frode Isaksen <fisaksen@bewan.com>, "
	      "Kai Germaschewski <kai.germaschewski@gmx.de>");
MODULE_DESCRIPTION("General purpose ISDN HDLC decoder");
MODULE_LICENSE("GPL");

/*-------------------------------------------------------------------*/

क्रमागत अणु
	HDLC_FAST_IDLE, HDLC_GET_FLAG_B0, HDLC_GETFLAG_B1A6, HDLC_GETFLAG_B7,
	HDLC_GET_DATA, HDLC_FAST_FLAG
पूर्ण;

क्रमागत अणु
	HDLC_SEND_DATA, HDLC_SEND_CRC1, HDLC_SEND_FAST_FLAG,
	HDLC_SEND_FIRST_FLAG, HDLC_SEND_CRC2, HDLC_SEND_CLOSING_FLAG,
	HDLC_SEND_IDLE1, HDLC_SEND_FAST_IDLE, HDLC_SENDFLAG_B0,
	HDLC_SENDFLAG_B1A6, HDLC_SENDFLAG_B7, STOPPED, HDLC_SENDFLAG_ONE
पूर्ण;

व्योम isdnhdlc_rcv_init(काष्ठा isdnhdlc_vars *hdlc, u32 features)
अणु
	स_रखो(hdlc, 0, माप(काष्ठा isdnhdlc_vars));
	hdlc->state = HDLC_GET_DATA;
	अगर (features & HDLC_56KBIT)
		hdlc->करो_adapt56 = 1;
	अगर (features & HDLC_BITREVERSE)
		hdlc->करो_bitreverse = 1;
पूर्ण
EXPORT_SYMBOL(isdnhdlc_out_init);

व्योम isdnhdlc_out_init(काष्ठा isdnhdlc_vars *hdlc, u32 features)
अणु
	स_रखो(hdlc, 0, माप(काष्ठा isdnhdlc_vars));
	अगर (features & HDLC_DCHANNEL) अणु
		hdlc->dchannel = 1;
		hdlc->state = HDLC_SEND_FIRST_FLAG;
	पूर्ण अन्यथा अणु
		hdlc->dchannel = 0;
		hdlc->state = HDLC_SEND_FAST_FLAG;
		hdlc->ffvalue = 0x7e;
	पूर्ण
	hdlc->cbin = 0x7e;
	अगर (features & HDLC_56KBIT) अणु
		hdlc->करो_adapt56 = 1;
		hdlc->state = HDLC_SENDFLAG_B0;
	पूर्ण अन्यथा
		hdlc->data_bits = 8;
	अगर (features & HDLC_BITREVERSE)
		hdlc->करो_bitreverse = 1;
पूर्ण
EXPORT_SYMBOL(isdnhdlc_rcv_init);

अटल पूर्णांक
check_frame(काष्ठा isdnhdlc_vars *hdlc)
अणु
	पूर्णांक status;

	अगर (hdlc->dstpos < 2)	/* too small - framing error */
		status = -HDLC_FRAMING_ERROR;
	अन्यथा अगर (hdlc->crc != 0xf0b8)	/* crc error */
		status = -HDLC_CRC_ERROR;
	अन्यथा अणु
		/* हटाओ CRC */
		hdlc->dstpos -= 2;
		/* good frame */
		status = hdlc->dstpos;
	पूर्ण
	वापस status;
पूर्ण

/*
  isdnhdlc_decode - decodes HDLC frames from a transparent bit stream.

  The source buffer is scanned क्रम valid HDLC frames looking क्रम
  flags (01111110) to indicate the start of a frame. If the start of
  the frame is found, the bit stuffing is हटाओd (0 after 5 1's).
  When a new flag is found, the complete frame has been received
  and the CRC is checked.
  If a valid frame is found, the function वापसs the frame length
  excluding the CRC with the bit HDLC_END_OF_FRAME set.
  If the beginning of a valid frame is found, the function वापसs
  the length.
  If a framing error is found (too many 1s and not a flag) the function
  वापसs the length with the bit HDLC_FRAMING_ERROR set.
  If a CRC error is found the function वापसs the length with the
  bit HDLC_CRC_ERROR set.
  If the frame length exceeds the destination buffer size, the function
  वापसs the length with the bit HDLC_LENGTH_ERROR set.

  src - source buffer
  slen - source buffer length
  count - number of bytes हटाओd (decoded) from the source buffer
  dst _ destination buffer
  dsize - destination buffer size
  वापसs - number of decoded bytes in the destination buffer and status
  flag.
*/
पूर्णांक isdnhdlc_decode(काष्ठा isdnhdlc_vars *hdlc, स्थिर u8 *src, पूर्णांक slen,
		    पूर्णांक *count, u8 *dst, पूर्णांक dsize)
अणु
	पूर्णांक status = 0;

	अटल स्थिर अचिन्हित अक्षर fast_flag[] = अणु
		0x00, 0x00, 0x00, 0x20, 0x30, 0x38, 0x3c, 0x3e, 0x3f
	पूर्ण;

	अटल स्थिर अचिन्हित अक्षर fast_flag_value[] = अणु
		0x00, 0x7e, 0xfc, 0xf9, 0xf3, 0xe7, 0xcf, 0x9f, 0x3f
	पूर्ण;

	अटल स्थिर अचिन्हित अक्षर fast_पात[] = अणु
		0x00, 0x00, 0x80, 0xc0, 0xe0, 0xf0, 0xf8, 0xfc, 0xfe, 0xff
	पूर्ण;

#घोषणा handle_fast_flag(h)						\
	करो अणु								\
		अगर (h->cbin == fast_flag[h->bit_shअगरt]) अणु		\
			h->ffvalue = fast_flag_value[h->bit_shअगरt];	\
			h->state = HDLC_FAST_FLAG;			\
			h->ffbit_shअगरt = h->bit_shअगरt;			\
			h->bit_shअगरt = 1;				\
		पूर्ण अन्यथा अणु						\
			h->state = HDLC_GET_DATA;			\
			h->data_received = 0;				\
		पूर्ण							\
	पूर्ण जबतक (0)

#घोषणा handle_पात(h)						\
	करो अणु							\
		h->shअगरt_reg = fast_पात[h->ffbit_shअगरt - 1];	\
		h->hdlc_bits1 = h->ffbit_shअगरt - 2;		\
		अगर (h->hdlc_bits1 < 0)				\
			h->hdlc_bits1 = 0;			\
		h->data_bits = h->ffbit_shअगरt - 1;		\
		h->state = HDLC_GET_DATA;			\
		h->data_received = 0;				\
	पूर्ण जबतक (0)

	*count = slen;

	जबतक (slen > 0) अणु
		अगर (hdlc->bit_shअगरt == 0) अणु
			/* the code is क्रम bitreverse streams */
			अगर (hdlc->करो_bitreverse == 0)
				hdlc->cbin = bitrev8(*src++);
			अन्यथा
				hdlc->cbin = *src++;
			slen--;
			hdlc->bit_shअगरt = 8;
			अगर (hdlc->करो_adapt56)
				hdlc->bit_shअगरt--;
		पूर्ण

		चयन (hdlc->state) अणु
		हाल STOPPED:
			वापस 0;
		हाल HDLC_FAST_IDLE:
			अगर (hdlc->cbin == 0xff) अणु
				hdlc->bit_shअगरt = 0;
				अवरोध;
			पूर्ण
			hdlc->state = HDLC_GET_FLAG_B0;
			hdlc->hdlc_bits1 = 0;
			hdlc->bit_shअगरt = 8;
			अवरोध;
		हाल HDLC_GET_FLAG_B0:
			अगर (!(hdlc->cbin & 0x80)) अणु
				hdlc->state = HDLC_GETFLAG_B1A6;
				hdlc->hdlc_bits1 = 0;
			पूर्ण अन्यथा अणु
				अगर ((!hdlc->करो_adapt56) &&
				    (++hdlc->hdlc_bits1 >= 8) &&
				    (hdlc->bit_shअगरt == 1))
					hdlc->state = HDLC_FAST_IDLE;
			पूर्ण
			hdlc->cbin <<= 1;
			hdlc->bit_shअगरt--;
			अवरोध;
		हाल HDLC_GETFLAG_B1A6:
			अगर (hdlc->cbin & 0x80) अणु
				hdlc->hdlc_bits1++;
				अगर (hdlc->hdlc_bits1 == 6)
					hdlc->state = HDLC_GETFLAG_B7;
			पूर्ण अन्यथा
				hdlc->hdlc_bits1 = 0;
			hdlc->cbin <<= 1;
			hdlc->bit_shअगरt--;
			अवरोध;
		हाल HDLC_GETFLAG_B7:
			अगर (hdlc->cbin & 0x80) अणु
				hdlc->state = HDLC_GET_FLAG_B0;
			पूर्ण अन्यथा अणु
				hdlc->state = HDLC_GET_DATA;
				hdlc->crc = 0xffff;
				hdlc->shअगरt_reg = 0;
				hdlc->hdlc_bits1 = 0;
				hdlc->data_bits = 0;
				hdlc->data_received = 0;
			पूर्ण
			hdlc->cbin <<= 1;
			hdlc->bit_shअगरt--;
			अवरोध;
		हाल HDLC_GET_DATA:
			अगर (hdlc->cbin & 0x80) अणु
				hdlc->hdlc_bits1++;
				चयन (hdlc->hdlc_bits1) अणु
				हाल 6:
					अवरोध;
				हाल 7:
					अगर (hdlc->data_received)
						/* bad frame */
						status = -HDLC_FRAMING_ERROR;
					अगर (!hdlc->करो_adapt56) अणु
						अगर (hdlc->cbin == fast_पात
						    [hdlc->bit_shअगरt + 1]) अणु
							hdlc->state =
								HDLC_FAST_IDLE;
							hdlc->bit_shअगरt = 1;
							अवरोध;
						पूर्ण
					पूर्ण अन्यथा
						hdlc->state = HDLC_GET_FLAG_B0;
					अवरोध;
				शेष:
					hdlc->shअगरt_reg >>= 1;
					hdlc->shअगरt_reg |= 0x80;
					hdlc->data_bits++;
					अवरोध;
				पूर्ण
			पूर्ण अन्यथा अणु
				चयन (hdlc->hdlc_bits1) अणु
				हाल 5:
					अवरोध;
				हाल 6:
					अगर (hdlc->data_received)
						status = check_frame(hdlc);
					hdlc->crc = 0xffff;
					hdlc->shअगरt_reg = 0;
					hdlc->data_bits = 0;
					अगर (!hdlc->करो_adapt56)
						handle_fast_flag(hdlc);
					अन्यथा अणु
						hdlc->state = HDLC_GET_DATA;
						hdlc->data_received = 0;
					पूर्ण
					अवरोध;
				शेष:
					hdlc->shअगरt_reg >>= 1;
					hdlc->data_bits++;
					अवरोध;
				पूर्ण
				hdlc->hdlc_bits1 = 0;
			पूर्ण
			अगर (status) अणु
				hdlc->dstpos = 0;
				*count -= slen;
				hdlc->cbin <<= 1;
				hdlc->bit_shअगरt--;
				वापस status;
			पूर्ण
			अगर (hdlc->data_bits == 8) अणु
				hdlc->data_bits = 0;
				hdlc->data_received = 1;
				hdlc->crc = crc_ccitt_byte(hdlc->crc,
							   hdlc->shअगरt_reg);

				/* good byte received */
				अगर (hdlc->dstpos < dsize)
					dst[hdlc->dstpos++] = hdlc->shअगरt_reg;
				अन्यथा अणु
					/* frame too दीर्घ */
					status = -HDLC_LENGTH_ERROR;
					hdlc->dstpos = 0;
				पूर्ण
			पूर्ण
			hdlc->cbin <<= 1;
			hdlc->bit_shअगरt--;
			अवरोध;
		हाल HDLC_FAST_FLAG:
			अगर (hdlc->cbin == hdlc->ffvalue) अणु
				hdlc->bit_shअगरt = 0;
				अवरोध;
			पूर्ण अन्यथा अणु
				अगर (hdlc->cbin == 0xff) अणु
					hdlc->state = HDLC_FAST_IDLE;
					hdlc->bit_shअगरt = 0;
				पूर्ण अन्यथा अगर (hdlc->ffbit_shअगरt == 8) अणु
					hdlc->state = HDLC_GETFLAG_B7;
					अवरोध;
				पूर्ण अन्यथा
					handle_पात(hdlc);
			पूर्ण
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण
	*count -= slen;
	वापस 0;
पूर्ण
EXPORT_SYMBOL(isdnhdlc_decode);
/*
  isdnhdlc_encode - encodes HDLC frames to a transparent bit stream.

  The bit stream starts with a beginning flag (01111110). After
  that each byte is added to the bit stream with bit stuffing added
  (0 after 5 1's).
  When the last byte has been हटाओd from the source buffer, the
  CRC (2 bytes is added) and the frame terminates with the ending flag.
  For the dchannel, the idle अक्षरacter (all 1's) is also added at the end.
  If this function is called with empty source buffer (slen=0), flags or
  idle अक्षरacter will be generated.

  src - source buffer
  slen - source buffer length
  count - number of bytes हटाओd (encoded) from source buffer
  dst _ destination buffer
  dsize - destination buffer size
  वापसs - number of encoded bytes in the destination buffer
*/
पूर्णांक isdnhdlc_encode(काष्ठा isdnhdlc_vars *hdlc, स्थिर u8 *src, u16 slen,
		    पूर्णांक *count, u8 *dst, पूर्णांक dsize)
अणु
	अटल स्थिर अचिन्हित अक्षर xfast_flag_value[] = अणु
		0x7e, 0x3f, 0x9f, 0xcf, 0xe7, 0xf3, 0xf9, 0xfc, 0x7e
	पूर्ण;

	पूर्णांक len = 0;

	*count = slen;

	/* special handling क्रम one byte frames */
	अगर ((slen == 1) && (hdlc->state == HDLC_SEND_FAST_FLAG))
		hdlc->state = HDLC_SENDFLAG_ONE;
	जबतक (dsize > 0) अणु
		अगर (hdlc->bit_shअगरt == 0) अणु
			अगर (slen && !hdlc->करो_closing) अणु
				hdlc->shअगरt_reg = *src++;
				slen--;
				अगर (slen == 0)
					/* closing sequence, CRC + flag(s) */
					hdlc->करो_closing = 1;
				hdlc->bit_shअगरt = 8;
			पूर्ण अन्यथा अणु
				अगर (hdlc->state == HDLC_SEND_DATA) अणु
					अगर (hdlc->data_received) अणु
						hdlc->state = HDLC_SEND_CRC1;
						hdlc->crc ^= 0xffff;
						hdlc->bit_shअगरt = 8;
						hdlc->shअगरt_reg =
							hdlc->crc & 0xff;
					पूर्ण अन्यथा अगर (!hdlc->करो_adapt56)
						hdlc->state =
							HDLC_SEND_FAST_FLAG;
					अन्यथा
						hdlc->state =
							HDLC_SENDFLAG_B0;
				पूर्ण

			पूर्ण
		पूर्ण

		चयन (hdlc->state) अणु
		हाल STOPPED:
			जबतक (dsize--)
				*dst++ = 0xff;
			वापस dsize;
		हाल HDLC_SEND_FAST_FLAG:
			hdlc->करो_closing = 0;
			अगर (slen == 0) अणु
				/* the code is क्रम bitreverse streams */
				अगर (hdlc->करो_bitreverse == 0)
					*dst++ = bitrev8(hdlc->ffvalue);
				अन्यथा
					*dst++ = hdlc->ffvalue;
				len++;
				dsize--;
				अवरोध;
			पूर्ण
			fallthrough;
		हाल HDLC_SENDFLAG_ONE:
			अगर (hdlc->bit_shअगरt == 8) अणु
				hdlc->cbin = hdlc->ffvalue >>
					(8 - hdlc->data_bits);
				hdlc->state = HDLC_SEND_DATA;
				hdlc->crc = 0xffff;
				hdlc->hdlc_bits1 = 0;
				hdlc->data_received = 1;
			पूर्ण
			अवरोध;
		हाल HDLC_SENDFLAG_B0:
			hdlc->करो_closing = 0;
			hdlc->cbin <<= 1;
			hdlc->data_bits++;
			hdlc->hdlc_bits1 = 0;
			hdlc->state = HDLC_SENDFLAG_B1A6;
			अवरोध;
		हाल HDLC_SENDFLAG_B1A6:
			hdlc->cbin <<= 1;
			hdlc->data_bits++;
			hdlc->cbin++;
			अगर (++hdlc->hdlc_bits1 == 6)
				hdlc->state = HDLC_SENDFLAG_B7;
			अवरोध;
		हाल HDLC_SENDFLAG_B7:
			hdlc->cbin <<= 1;
			hdlc->data_bits++;
			अगर (slen == 0) अणु
				hdlc->state = HDLC_SENDFLAG_B0;
				अवरोध;
			पूर्ण
			अगर (hdlc->bit_shअगरt == 8) अणु
				hdlc->state = HDLC_SEND_DATA;
				hdlc->crc = 0xffff;
				hdlc->hdlc_bits1 = 0;
				hdlc->data_received = 1;
			पूर्ण
			अवरोध;
		हाल HDLC_SEND_FIRST_FLAG:
			hdlc->data_received = 1;
			अगर (hdlc->data_bits == 8) अणु
				hdlc->state = HDLC_SEND_DATA;
				hdlc->crc = 0xffff;
				hdlc->hdlc_bits1 = 0;
				अवरोध;
			पूर्ण
			hdlc->cbin <<= 1;
			hdlc->data_bits++;
			अगर (hdlc->shअगरt_reg & 0x01)
				hdlc->cbin++;
			hdlc->shअगरt_reg >>= 1;
			hdlc->bit_shअगरt--;
			अगर (hdlc->bit_shअगरt == 0) अणु
				hdlc->state = HDLC_SEND_DATA;
				hdlc->crc = 0xffff;
				hdlc->hdlc_bits1 = 0;
			पूर्ण
			अवरोध;
		हाल HDLC_SEND_DATA:
			hdlc->cbin <<= 1;
			hdlc->data_bits++;
			अगर (hdlc->hdlc_bits1 == 5) अणु
				hdlc->hdlc_bits1 = 0;
				अवरोध;
			पूर्ण
			अगर (hdlc->bit_shअगरt == 8)
				hdlc->crc = crc_ccitt_byte(hdlc->crc,
							   hdlc->shअगरt_reg);
			अगर (hdlc->shअगरt_reg & 0x01) अणु
				hdlc->hdlc_bits1++;
				hdlc->cbin++;
				hdlc->shअगरt_reg >>= 1;
				hdlc->bit_shअगरt--;
			पूर्ण अन्यथा अणु
				hdlc->hdlc_bits1 = 0;
				hdlc->shअगरt_reg >>= 1;
				hdlc->bit_shअगरt--;
			पूर्ण
			अवरोध;
		हाल HDLC_SEND_CRC1:
			hdlc->cbin <<= 1;
			hdlc->data_bits++;
			अगर (hdlc->hdlc_bits1 == 5) अणु
				hdlc->hdlc_bits1 = 0;
				अवरोध;
			पूर्ण
			अगर (hdlc->shअगरt_reg & 0x01) अणु
				hdlc->hdlc_bits1++;
				hdlc->cbin++;
				hdlc->shअगरt_reg >>= 1;
				hdlc->bit_shअगरt--;
			पूर्ण अन्यथा अणु
				hdlc->hdlc_bits1 = 0;
				hdlc->shअगरt_reg >>= 1;
				hdlc->bit_shअगरt--;
			पूर्ण
			अगर (hdlc->bit_shअगरt == 0) अणु
				hdlc->shअगरt_reg = (hdlc->crc >> 8);
				hdlc->state = HDLC_SEND_CRC2;
				hdlc->bit_shअगरt = 8;
			पूर्ण
			अवरोध;
		हाल HDLC_SEND_CRC2:
			hdlc->cbin <<= 1;
			hdlc->data_bits++;
			अगर (hdlc->hdlc_bits1 == 5) अणु
				hdlc->hdlc_bits1 = 0;
				अवरोध;
			पूर्ण
			अगर (hdlc->shअगरt_reg & 0x01) अणु
				hdlc->hdlc_bits1++;
				hdlc->cbin++;
				hdlc->shअगरt_reg >>= 1;
				hdlc->bit_shअगरt--;
			पूर्ण अन्यथा अणु
				hdlc->hdlc_bits1 = 0;
				hdlc->shअगरt_reg >>= 1;
				hdlc->bit_shअगरt--;
			पूर्ण
			अगर (hdlc->bit_shअगरt == 0) अणु
				hdlc->shअगरt_reg = 0x7e;
				hdlc->state = HDLC_SEND_CLOSING_FLAG;
				hdlc->bit_shअगरt = 8;
			पूर्ण
			अवरोध;
		हाल HDLC_SEND_CLOSING_FLAG:
			hdlc->cbin <<= 1;
			hdlc->data_bits++;
			अगर (hdlc->hdlc_bits1 == 5) अणु
				hdlc->hdlc_bits1 = 0;
				अवरोध;
			पूर्ण
			अगर (hdlc->shअगरt_reg & 0x01)
				hdlc->cbin++;
			hdlc->shअगरt_reg >>= 1;
			hdlc->bit_shअगरt--;
			अगर (hdlc->bit_shअगरt == 0) अणु
				hdlc->ffvalue =
					xfast_flag_value[hdlc->data_bits];
				अगर (hdlc->dchannel) अणु
					hdlc->ffvalue = 0x7e;
					hdlc->state = HDLC_SEND_IDLE1;
					hdlc->bit_shअगरt = 8-hdlc->data_bits;
					अगर (hdlc->bit_shअगरt == 0)
						hdlc->state =
							HDLC_SEND_FAST_IDLE;
				पूर्ण अन्यथा अणु
					अगर (!hdlc->करो_adapt56) अणु
						hdlc->state =
							HDLC_SEND_FAST_FLAG;
						hdlc->data_received = 0;
					पूर्ण अन्यथा अणु
						hdlc->state = HDLC_SENDFLAG_B0;
						hdlc->data_received = 0;
					पूर्ण
					/* Finished this frame, send flags */
					अगर (dsize > 1)
						dsize = 1;
				पूर्ण
			पूर्ण
			अवरोध;
		हाल HDLC_SEND_IDLE1:
			hdlc->करो_closing = 0;
			hdlc->cbin <<= 1;
			hdlc->cbin++;
			hdlc->data_bits++;
			hdlc->bit_shअगरt--;
			अगर (hdlc->bit_shअगरt == 0) अणु
				hdlc->state = HDLC_SEND_FAST_IDLE;
				hdlc->bit_shअगरt = 0;
			पूर्ण
			अवरोध;
		हाल HDLC_SEND_FAST_IDLE:
			hdlc->करो_closing = 0;
			hdlc->cbin = 0xff;
			hdlc->data_bits = 8;
			अगर (hdlc->bit_shअगरt == 8) अणु
				hdlc->cbin = 0x7e;
				hdlc->state = HDLC_SEND_FIRST_FLAG;
			पूर्ण अन्यथा अणु
				/* the code is क्रम bitreverse streams */
				अगर (hdlc->करो_bitreverse == 0)
					*dst++ = bitrev8(hdlc->cbin);
				अन्यथा
					*dst++ = hdlc->cbin;
				hdlc->bit_shअगरt = 0;
				hdlc->data_bits = 0;
				len++;
				dsize = 0;
			पूर्ण
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		अगर (hdlc->करो_adapt56) अणु
			अगर (hdlc->data_bits == 7) अणु
				hdlc->cbin <<= 1;
				hdlc->cbin++;
				hdlc->data_bits++;
			पूर्ण
		पूर्ण
		अगर (hdlc->data_bits == 8) अणु
			/* the code is क्रम bitreverse streams */
			अगर (hdlc->करो_bitreverse == 0)
				*dst++ = bitrev8(hdlc->cbin);
			अन्यथा
				*dst++ = hdlc->cbin;
			hdlc->data_bits = 0;
			len++;
			dsize--;
		पूर्ण
	पूर्ण
	*count -= slen;

	वापस len;
पूर्ण
EXPORT_SYMBOL(isdnhdlc_encode);
