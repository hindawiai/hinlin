<शैली गुरु>
/* $Id: capiutil.h,v 1.5.6.2 2001/09/23 22:24:33 kai Exp $
 *
 * CAPI 2.0 defines & types
 *
 * From CAPI 2.0 Development Kit AVM 1995 (msg.c)
 * Rewritten क्रम Linux 1996 by Carsten Paeth <calle@calle.de>
 *
 * This software may be used and distributed according to the terms
 * of the GNU General Public License, incorporated herein by reference.
 *
 */

#अगर_अघोषित __CAPIUTIL_H__
#घोषणा __CAPIUTIL_H__

#समावेश <यंत्र/types.h>

#घोषणा CAPIMSG_BASELEN		8
#घोषणा CAPIMSG_U8(m, off)	(m[off])
#घोषणा CAPIMSG_U16(m, off)	(m[off]|(m[(off)+1]<<8))
#घोषणा CAPIMSG_U32(m, off)	(m[off]|(m[(off)+1]<<8)|(m[(off)+2]<<16)|(m[(off)+3]<<24))
#घोषणा	CAPIMSG_LEN(m)		CAPIMSG_U16(m,0)
#घोषणा	CAPIMSG_APPID(m)	CAPIMSG_U16(m,2)
#घोषणा	CAPIMSG_COMMAND(m)	CAPIMSG_U8(m,4)
#घोषणा	CAPIMSG_SUBCOMMAND(m)	CAPIMSG_U8(m,5)
#घोषणा CAPIMSG_CMD(m)		(((m[4])<<8)|(m[5]))
#घोषणा	CAPIMSG_MSGID(m)	CAPIMSG_U16(m,6)
#घोषणा CAPIMSG_CONTROLLER(m)	(m[8] & 0x7f)
#घोषणा CAPIMSG_CONTROL(m)	CAPIMSG_U32(m, 8)
#घोषणा CAPIMSG_NCCI(m)		CAPIMSG_CONTROL(m)
#घोषणा CAPIMSG_DATALEN(m)	CAPIMSG_U16(m,16) /* DATA_B3_REQ */

अटल अंतरभूत व्योम capimsg_setu8(व्योम *m, पूर्णांक off, __u8 val)
अणु
	((__u8 *)m)[off] = val;
पूर्ण

अटल अंतरभूत व्योम capimsg_setu16(व्योम *m, पूर्णांक off, __u16 val)
अणु
	((__u8 *)m)[off] = val & 0xff;
	((__u8 *)m)[off+1] = (val >> 8) & 0xff;
पूर्ण

अटल अंतरभूत व्योम capimsg_setu32(व्योम *m, पूर्णांक off, __u32 val)
अणु
	((__u8 *)m)[off] = val & 0xff;
	((__u8 *)m)[off+1] = (val >> 8) & 0xff;
	((__u8 *)m)[off+2] = (val >> 16) & 0xff;
	((__u8 *)m)[off+3] = (val >> 24) & 0xff;
पूर्ण

#घोषणा	CAPIMSG_SETLEN(m, len)		capimsg_setu16(m, 0, len)
#घोषणा	CAPIMSG_SETAPPID(m, applid)	capimsg_setu16(m, 2, applid)
#घोषणा	CAPIMSG_SETCOMMAND(m,cmd)	capimsg_setu8(m, 4, cmd)
#घोषणा	CAPIMSG_SETSUBCOMMAND(m, cmd)	capimsg_setu8(m, 5, cmd)
#घोषणा	CAPIMSG_SETMSGID(m, msgid)	capimsg_setu16(m, 6, msgid)
#घोषणा	CAPIMSG_SETCONTROL(m, contr)	capimsg_setu32(m, 8, contr)
#घोषणा	CAPIMSG_SETDATALEN(m, len)	capimsg_setu16(m, 16, len)

#पूर्ण_अगर				/* __CAPIUTIL_H__ */
