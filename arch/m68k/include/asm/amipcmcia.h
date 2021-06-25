<शैली गुरु>
/*
** यंत्र-m68k/pcmcia.h -- Amiga Linux PCMCIA Definitions
**
** Copyright 1997 by Alain Malek
**
** This file is subject to the terms and conditions of the GNU General Public
** License.  See the file COPYING in the मुख्य directory of this archive
** क्रम more details.
**
** Created: 12/10/97 by Alain Malek
*/

#अगर_अघोषित __AMIGA_PCMCIA_H__
#घोषणा __AMIGA_PCMCIA_H__

#समावेश <यंत्र/amigayle.h>

/* prototypes */

व्योम pcmcia_reset(व्योम);
पूर्णांक pcmcia_copy_tuple(अचिन्हित अक्षर tuple_id, व्योम *tuple, पूर्णांक max_len);
व्योम pcmcia_program_voltage(पूर्णांक voltage);
व्योम pcmcia_access_speed(पूर्णांक speed);
व्योम pcmcia_ग_लिखो_enable(व्योम);
व्योम pcmcia_ग_लिखो_disable(व्योम);

अटल अंतरभूत u_अक्षर pcmcia_पढ़ो_status(व्योम)
अणु
	वापस (gayle.cardstatus & 0x7c);
पूर्ण

अटल अंतरभूत u_अक्षर pcmcia_get_पूर्णांकreq(व्योम)
अणु
	वापस (gayle.पूर्णांकreq);
पूर्ण

अटल अंतरभूत व्योम pcmcia_ack_पूर्णांक(u_अक्षर पूर्णांकreq)
अणु
	gayle.पूर्णांकreq = 0xf8;
पूर्ण

अटल अंतरभूत व्योम pcmcia_enable_irq(व्योम)
अणु
	gayle.पूर्णांकen |= GAYLE_IRQ_IRQ;
पूर्ण

अटल अंतरभूत व्योम pcmcia_disable_irq(व्योम)
अणु
	gayle.पूर्णांकen &= ~GAYLE_IRQ_IRQ;
पूर्ण

#घोषणा PCMCIA_INSERTED	(gayle.cardstatus & GAYLE_CS_CCDET)

/* valid voltages क्रम pcmcia_ProgramVoltage */

#घोषणा PCMCIA_0V	0
#घोषणा PCMCIA_5V	5
#घोषणा PCMCIA_12V	12

/* valid speeds क्रम pcmcia_AccessSpeed */

#घोषणा PCMCIA_SPEED_100NS	100
#घोषणा PCMCIA_SPEED_150NS	150
#घोषणा PCMCIA_SPEED_250NS	250
#घोषणा PCMCIA_SPEED_720NS	720

/* PCMCIA Tuple codes */

#घोषणा CISTPL_शून्य		0x00
#घोषणा CISTPL_DEVICE		0x01
#घोषणा CISTPL_LONGLINK_CB	0x02
#घोषणा CISTPL_CONFIG_CB	0x04
#घोषणा CISTPL_CFTABLE_ENTRY_CB	0x05
#घोषणा CISTPL_LONGLINK_MFC	0x06
#घोषणा CISTPL_BAR		0x07
#घोषणा CISTPL_CHECKSUM		0x10
#घोषणा CISTPL_LONGLINK_A	0x11
#घोषणा CISTPL_LONGLINK_C	0x12
#घोषणा CISTPL_LINKTARGET	0x13
#घोषणा CISTPL_NO_LINK		0x14
#घोषणा CISTPL_VERS_1		0x15
#घोषणा CISTPL_ALTSTR		0x16
#घोषणा CISTPL_DEVICE_A		0x17
#घोषणा CISTPL_JEDEC_C		0x18
#घोषणा CISTPL_JEDEC_A		0x19
#घोषणा CISTPL_CONFIG		0x1a
#घोषणा CISTPL_CFTABLE_ENTRY	0x1b
#घोषणा CISTPL_DEVICE_OC	0x1c
#घोषणा CISTPL_DEVICE_OA	0x1d
#घोषणा CISTPL_DEVICE_GEO	0x1e
#घोषणा CISTPL_DEVICE_GEO_A	0x1f
#घोषणा CISTPL_MANFID		0x20
#घोषणा CISTPL_FUNCID		0x21
#घोषणा CISTPL_FUNCE		0x22
#घोषणा CISTPL_SWIL		0x23
#घोषणा CISTPL_END		0xff

/* FUNCID */

#घोषणा CISTPL_FUNCID_MULTI	0x00
#घोषणा CISTPL_FUNCID_MEMORY	0x01
#घोषणा CISTPL_FUNCID_SERIAL	0x02
#घोषणा CISTPL_FUNCID_PARALLEL	0x03
#घोषणा CISTPL_FUNCID_FIXED	0x04
#घोषणा CISTPL_FUNCID_VIDEO	0x05
#घोषणा CISTPL_FUNCID_NETWORK	0x06
#घोषणा CISTPL_FUNCID_AIMS	0x07
#घोषणा CISTPL_FUNCID_SCSI	0x08

#पूर्ण_अगर
