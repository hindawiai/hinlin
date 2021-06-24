<शैली गुरु>
/*
** यंत्र-m68k/pcmcia.c -- Amiga Linux PCMCIA support
**                      most inक्रमmation was found by disassembling card.resource
**                      I'm still looking क्रम an official करोc !
**
** Copyright 1997 by Alain Malek
**
** This file is subject to the terms and conditions of the GNU General Public
** License.  See the file COPYING in the मुख्य directory of this archive
** क्रम more details.
**
** Created: 12/10/97 by Alain Malek
*/

#समावेश <linux/types.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/समयr.h>
#समावेश <linux/module.h>

#समावेश <यंत्र/amigayle.h>
#समावेश <यंत्र/amipcmcia.h>

/* gayle config byte क्रम program voltage and access speed */
अटल अचिन्हित अक्षर cfg_byte = GAYLE_CFG_0V|GAYLE_CFG_150NS;

व्योम pcmcia_reset(व्योम)
अणु
	अचिन्हित दीर्घ reset_start_समय = jअगरfies;
	अचिन्हित अक्षर b;

	gayle_reset = 0x00;
	जबतक (समय_beक्रमe(jअगरfies, reset_start_समय + 1*HZ/100));
	b = gayle_reset;
पूर्ण
EXPORT_SYMBOL(pcmcia_reset);


/* copy a tuple, including tuple header. वापस nb bytes copied */
/* be careful as this may trigger a GAYLE_IRQ_WR पूर्णांकerrupt ! */

पूर्णांक pcmcia_copy_tuple(अचिन्हित अक्षर tuple_id, व्योम *tuple, पूर्णांक max_len)
अणु
	अचिन्हित अक्षर id, *dest;
	पूर्णांक cnt, pos, len;

	dest = tuple;
	pos = 0;

	id = gayle_attribute[pos];

	जबतक((id != CISTPL_END) && (pos < 0x10000)) अणु
		len = (पूर्णांक)gayle_attribute[pos+2] + 2;
		अगर (id == tuple_id) अणु
			len = (len > max_len)?max_len:len;
			क्रम (cnt = 0; cnt < len; cnt++) अणु
				*dest++ = gayle_attribute[pos+(cnt<<1)];
			पूर्ण

			वापस len;
		पूर्ण
		pos += len<<1;
		id = gayle_attribute[pos];
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(pcmcia_copy_tuple);

व्योम pcmcia_program_voltage(पूर्णांक voltage)
अणु
	अचिन्हित अक्षर v;

	चयन (voltage) अणु
	हाल PCMCIA_0V:
		v = GAYLE_CFG_0V;
		अवरोध;
	हाल PCMCIA_5V:
		v = GAYLE_CFG_5V;
		अवरोध;
	हाल PCMCIA_12V:
		v = GAYLE_CFG_12V;
		अवरोध;
	शेष:
		v = GAYLE_CFG_0V;
	पूर्ण

	cfg_byte = (cfg_byte & 0xfc) | v;
	gayle.config = cfg_byte;

पूर्ण
EXPORT_SYMBOL(pcmcia_program_voltage);

व्योम pcmcia_access_speed(पूर्णांक speed)
अणु
	अचिन्हित अक्षर s;

	अगर (speed <= PCMCIA_SPEED_100NS)
		s = GAYLE_CFG_100NS;
	अन्यथा अगर (speed <= PCMCIA_SPEED_150NS)
		s = GAYLE_CFG_150NS;
	अन्यथा अगर (speed <= PCMCIA_SPEED_250NS)
		s = GAYLE_CFG_250NS;
	अन्यथा
		s = GAYLE_CFG_720NS;

	cfg_byte = (cfg_byte & 0xf3) | s;
	gayle.config = cfg_byte;
पूर्ण
EXPORT_SYMBOL(pcmcia_access_speed);

व्योम pcmcia_ग_लिखो_enable(व्योम)
अणु
	gayle.cardstatus = GAYLE_CS_WR|GAYLE_CS_DA;
पूर्ण
EXPORT_SYMBOL(pcmcia_ग_लिखो_enable);

व्योम pcmcia_ग_लिखो_disable(व्योम)
अणु
	gayle.cardstatus = 0;
पूर्ण
EXPORT_SYMBOL(pcmcia_ग_लिखो_disable);

