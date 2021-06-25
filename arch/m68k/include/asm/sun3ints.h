<शैली गुरु>
/*
 * sun3पूर्णांकs.h -- Linux/Sun3 पूर्णांकerrupt handling code definitions
 *
 * Erik Verbruggen (erik@bigmama.xtdnet.nl)
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file COPYING in the मुख्य directory of this archive क्रम
 * more details.
 */

#अगर_अघोषित SUN3INTS_H
#घोषणा SUN3INTS_H

#समावेश <linux/types.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <यंत्र/पूर्णांकersil.h>
#समावेश <यंत्र/oplib.h>
#समावेश <यंत्र/traps.h>
#समावेश <यंत्र/irq.h>

#घोषणा SUN3_INT_VECS 192

व्योम sun3_enable_irq(अचिन्हित पूर्णांक irq);
व्योम sun3_disable_irq(अचिन्हित पूर्णांक irq);
बाह्य व्योम sun3_init_IRQ (व्योम);
बाह्य व्योम sun3_enable_पूर्णांकerrupts (व्योम);
बाह्य व्योम sun3_disable_पूर्णांकerrupts (व्योम);
बाह्य अस्थिर अचिन्हित अक्षर* sun3_पूर्णांकreg;

/* master list of VME vectors -- करोn't fuck with this */
#घोषणा SUN3_VEC_FLOPPY		(IRQ_USER+0)
#घोषणा SUN3_VEC_VMESCSI0	(IRQ_USER+0)
#घोषणा SUN3_VEC_VMESCSI1	(IRQ_USER+1)
#घोषणा SUN3_VEC_CG		(IRQ_USER+104)


#पूर्ण_अगर /* SUN3INTS_H */
