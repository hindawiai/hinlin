<शैली गुरु>
/*
 * Copyright 2001 MontaVista Software Inc.
 * Author: MontaVista Software, Inc.
 *              ahennessy@mvista.com
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2000-2001 Toshiba Corporation
 *
 *  This program is मुक्त software; you can redistribute  it and/or modअगरy it
 *  under  the terms of  the GNU General  Public License as published by the
 *  Free Software Foundation;  either version 2 of the  License, or (at your
 *  option) any later version.
 *
 *  THIS  SOFTWARE  IS PROVIDED   ``AS  IS'' AND   ANY  EXPRESS OR IMPLIED
 *  WARRANTIES,   INCLUDING, BUT NOT  LIMITED  TO, THE IMPLIED WARRANTIES OF
 *  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN
 *  NO  EVENT  SHALL   THE AUTHOR  BE    LIABLE FOR ANY   सूचीECT, INसूचीECT,
 *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 *  NOT LIMITED   TO, PROCUREMENT OF  SUBSTITUTE GOODS  OR SERVICES; LOSS OF
 *  USE, DATA,  OR PROFITS; OR  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 *  ANY THEORY OF LIABILITY, WHETHER IN  CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 *  THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *  You should have received a copy of the  GNU General Public License aदीर्घ
 *  with this program; अगर not, ग_लिखो  to the Free Software Foundation, Inc.,
 *  675 Mass Ave, Cambridge, MA 02139, USA.
 */
#समावेश <linux/init.h>
#समावेश <linux/types.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>

#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/mipsregs.h>
#समावेश <यंत्र/txx9/generic.h>
#समावेश <यंत्र/txx9/jmr3927.h>

#अगर JMR3927_IRQ_END > NR_IRQS
#त्रुटि JMR3927_IRQ_END > NR_IRQS
#पूर्ण_अगर

/*
 * CP0_STATUS is a thपढ़ो's resource (saved/restored on context चयन).
 * So disable_irq/enable_irq MUST handle IOC/IRC रेजिस्टरs.
 */
अटल व्योम mask_irq_ioc(काष्ठा irq_data *d)
अणु
	/* 0: mask */
	अचिन्हित पूर्णांक irq_nr = d->irq - JMR3927_IRQ_IOC;
	अचिन्हित अक्षर imask = jmr3927_ioc_reg_in(JMR3927_IOC_INTM_ADDR);
	अचिन्हित पूर्णांक bit = 1 << irq_nr;
	jmr3927_ioc_reg_out(imask & ~bit, JMR3927_IOC_INTM_ADDR);
	/* flush ग_लिखो buffer */
	(व्योम)jmr3927_ioc_reg_in(JMR3927_IOC_REV_ADDR);
पूर्ण
अटल व्योम unmask_irq_ioc(काष्ठा irq_data *d)
अणु
	/* 0: mask */
	अचिन्हित पूर्णांक irq_nr = d->irq - JMR3927_IRQ_IOC;
	अचिन्हित अक्षर imask = jmr3927_ioc_reg_in(JMR3927_IOC_INTM_ADDR);
	अचिन्हित पूर्णांक bit = 1 << irq_nr;
	jmr3927_ioc_reg_out(imask | bit, JMR3927_IOC_INTM_ADDR);
	/* flush ग_लिखो buffer */
	(व्योम)jmr3927_ioc_reg_in(JMR3927_IOC_REV_ADDR);
पूर्ण

अटल पूर्णांक jmr3927_ioc_irqroute(व्योम)
अणु
	अचिन्हित अक्षर istat = jmr3927_ioc_reg_in(JMR3927_IOC_INTS2_ADDR);
	पूर्णांक i;

	क्रम (i = 0; i < JMR3927_NR_IRQ_IOC; i++) अणु
		अगर (istat & (1 << i))
			वापस JMR3927_IRQ_IOC + i;
	पूर्ण
	वापस -1;
पूर्ण

अटल पूर्णांक jmr3927_irq_dispatch(पूर्णांक pending)
अणु
	पूर्णांक irq;

	अगर ((pending & CAUSEF_IP7) == 0)
		वापस -1;
	irq = (pending >> CAUSEB_IP2) & 0x0f;
	irq += JMR3927_IRQ_IRC;
	अगर (irq == JMR3927_IRQ_IOCINT)
		irq = jmr3927_ioc_irqroute();
	वापस irq;
पूर्ण

अटल काष्ठा irq_chip jmr3927_irq_ioc = अणु
	.name = "jmr3927_ioc",
	.irq_mask = mask_irq_ioc,
	.irq_unmask = unmask_irq_ioc,
पूर्ण;

व्योम __init jmr3927_irq_setup(व्योम)
अणु
	पूर्णांक i;

	txx9_irq_dispatch = jmr3927_irq_dispatch;
	/* Now, पूर्णांकerrupt control disabled, */
	/* all IRC पूर्णांकerrupts are masked, */
	/* all IRC पूर्णांकerrupt mode are Low Active. */

	/* mask all IOC पूर्णांकerrupts */
	jmr3927_ioc_reg_out(0, JMR3927_IOC_INTM_ADDR);
	/* setup IOC पूर्णांकerrupt mode (SOFT:High Active, Others:Low Active) */
	jmr3927_ioc_reg_out(JMR3927_IOC_INTF_SOFT, JMR3927_IOC_INTP_ADDR);

	/* clear PCI Soft पूर्णांकerrupts */
	jmr3927_ioc_reg_out(0, JMR3927_IOC_INTS1_ADDR);
	/* clear PCI Reset पूर्णांकerrupts */
	jmr3927_ioc_reg_out(0, JMR3927_IOC_RESET_ADDR);

	tx3927_irq_init();
	क्रम (i = JMR3927_IRQ_IOC; i < JMR3927_IRQ_IOC + JMR3927_NR_IRQ_IOC; i++)
		irq_set_chip_and_handler(i, &jmr3927_irq_ioc,
					 handle_level_irq);

	/* setup IOC पूर्णांकerrupt 1 (PCI, MODEM) */
	irq_set_chained_handler(JMR3927_IRQ_IOCINT, handle_simple_irq);
पूर्ण
