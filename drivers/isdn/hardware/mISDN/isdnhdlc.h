<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * hdlc.h  --  General purpose ISDN HDLC decoder.
 *
 * Implementation of a HDLC decoder/encoder in software.
 * Necessary because some ISDN devices करोn't have HDLC
 * controllers.
 *
 * Copyright (C)
 *	2009	Karsten Keil		<keil@b1-प्रणालीs.de>
 *	2002	Wolfgang Mथञes		<wolfgang@iksw-muees.de>
 *	2001	Frode Isaksen		<fisaksen@bewan.com>
 *	2001	Kai Germaschewski	<kai.germaschewski@gmx.de>
 */

#अगर_अघोषित __ISDNHDLC_H__
#घोषणा __ISDNHDLC_H__

काष्ठा isdnhdlc_vars अणु
	पूर्णांक bit_shअगरt;
	पूर्णांक hdlc_bits1;
	पूर्णांक data_bits;
	पूर्णांक ffbit_shअगरt;	/* encoding only */
	पूर्णांक state;
	पूर्णांक dstpos;

	u16 crc;

	u8 cbin;
	u8 shअगरt_reg;
	u8 ffvalue;

	/* set अगर transferring data */
	u32 data_received:1;
	/* set अगर D channel (send idle instead of flags) */
	u32 dchannel:1;
	/* set अगर 56K adaptation */
	u32 करो_adapt56:1;
	/* set अगर in closing phase (need to send CRC + flag) */
	u32 करो_closing:1;
	/* set अगर data is bitreverse */
	u32 करो_bitreverse:1;
पूर्ण;

/* Feature Flags */
#घोषणा HDLC_56KBIT	0x01
#घोषणा HDLC_DCHANNEL	0x02
#घोषणा HDLC_BITREVERSE	0x04

/*
  The वापस value from isdnhdlc_decode is
  the frame length, 0 अगर no complete frame was decoded,
  or a negative error number
*/
#घोषणा HDLC_FRAMING_ERROR     1
#घोषणा HDLC_CRC_ERROR         2
#घोषणा HDLC_LENGTH_ERROR      3

बाह्य व्योम	isdnhdlc_rcv_init(काष्ठा isdnhdlc_vars *hdlc, u32 features);

बाह्य पूर्णांक	isdnhdlc_decode(काष्ठा isdnhdlc_vars *hdlc, स्थिर u8 *src,
			पूर्णांक slen, पूर्णांक *count, u8 *dst, पूर्णांक dsize);

बाह्य व्योम	isdnhdlc_out_init(काष्ठा isdnhdlc_vars *hdlc, u32 features);

बाह्य पूर्णांक	isdnhdlc_encode(काष्ठा isdnhdlc_vars *hdlc, स्थिर u8 *src,
			u16 slen, पूर्णांक *count, u8 *dst, पूर्णांक dsize);

#पूर्ण_अगर /* __ISDNHDLC_H__ */
