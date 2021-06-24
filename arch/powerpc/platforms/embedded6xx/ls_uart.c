<शैली गुरु>
/*
 * AVR घातer-management chip पूर्णांकerface क्रम the Buffalo Linkstation /
 * Kurobox Platक्रमm.
 *
 * Author: 2006 (c) G. Liakhovetski
 *	 g.liakhovetski@gmx.de
 *
 * This file is licensed under the terms of the GNU General Public License
 * version 2.  This program is licensed "as is" without any warranty of
 * any kind, whether express or implied.
 */
#समावेश <linux/workqueue.h>
#समावेश <linux/माला.स>
#समावेश <linux/delay.h>
#समावेश <linux/serial_reg.h>
#समावेश <linux/serial_8250.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/termbits.h>

#समावेश "mpc10x.h"

अटल व्योम __iomem *avr_addr;
अटल अचिन्हित दीर्घ avr_घड़ी;

अटल काष्ठा work_काष्ठा wd_work;

अटल व्योम wd_stop(काष्ठा work_काष्ठा *unused)
अणु
	स्थिर अक्षर string[] = "AAAAFFFFJJJJ>>>>VVVV>>>>ZZZZVVVVKKKK";
	पूर्णांक i = 0, rescue = 8;
	पूर्णांक len = म_माप(string);

	जबतक (rescue--) अणु
		पूर्णांक j;
		अक्षर lsr = in_8(avr_addr + UART_LSR);

		अगर (lsr & (UART_LSR_THRE | UART_LSR_TEMT)) अणु
			क्रम (j = 0; j < 16 && i < len; j++, i++)
				out_8(avr_addr + UART_TX, string[i]);
			अगर (i == len) अणु
				/* Read "OK" back: 4ms क्रम the last "KKKK"
				   plus a couple bytes back */
				msleep(7);
				prपूर्णांकk("linkstation: disarming the AVR watchdog: ");
				जबतक (in_8(avr_addr + UART_LSR) & UART_LSR_DR)
					prपूर्णांकk("%c", in_8(avr_addr + UART_RX));
				अवरोध;
			पूर्ण
		पूर्ण
		msleep(17);
	पूर्ण
	prपूर्णांकk("\n");
पूर्ण

#घोषणा AVR_QUOT(घड़ी) ((घड़ी) + 8 * 9600) / (16 * 9600)

व्योम avr_uart_configure(व्योम)
अणु
	अचिन्हित अक्षर cval = UART_LCR_WLEN8;
	अचिन्हित पूर्णांक quot = AVR_QUOT(avr_घड़ी);

	अगर (!avr_addr || !avr_घड़ी)
		वापस;

	out_8(avr_addr + UART_LCR, cval);			/* initialise UART */
	out_8(avr_addr + UART_MCR, 0);
	out_8(avr_addr + UART_IER, 0);

	cval |= UART_LCR_STOP | UART_LCR_PARITY | UART_LCR_EPAR;

	out_8(avr_addr + UART_LCR, cval);			/* Set अक्षरacter क्रमmat */

	out_8(avr_addr + UART_LCR, cval | UART_LCR_DLAB);	/* set DLAB */
	out_8(avr_addr + UART_DLL, quot & 0xff);		/* LS of भागisor */
	out_8(avr_addr + UART_DLM, quot >> 8);			/* MS of भागisor */
	out_8(avr_addr + UART_LCR, cval);			/* reset DLAB */
	out_8(avr_addr + UART_FCR, UART_FCR_ENABLE_FIFO);	/* enable FIFO */
पूर्ण

व्योम avr_uart_send(स्थिर अक्षर c)
अणु
	अगर (!avr_addr || !avr_घड़ी)
		वापस;

	out_8(avr_addr + UART_TX, c);
	out_8(avr_addr + UART_TX, c);
	out_8(avr_addr + UART_TX, c);
	out_8(avr_addr + UART_TX, c);
पूर्ण

अटल व्योम __init ls_uart_init(व्योम)
अणु
	local_irq_disable();

#अगर_अघोषित CONFIG_SERIAL_8250
	out_8(avr_addr + UART_FCR, UART_FCR_ENABLE_FIFO);	/* enable FIFO */
	out_8(avr_addr + UART_FCR, UART_FCR_ENABLE_FIFO |
	      UART_FCR_CLEAR_RCVR | UART_FCR_CLEAR_XMIT);	/* clear FIFOs */
	out_8(avr_addr + UART_FCR, 0);
	out_8(avr_addr + UART_IER, 0);

	/* Clear up पूर्णांकerrupts */
	(व्योम) in_8(avr_addr + UART_LSR);
	(व्योम) in_8(avr_addr + UART_RX);
	(व्योम) in_8(avr_addr + UART_IIR);
	(व्योम) in_8(avr_addr + UART_MSR);
#पूर्ण_अगर
	avr_uart_configure();

	local_irq_enable();
पूर्ण

अटल पूर्णांक __init ls_uarts_init(व्योम)
अणु
	काष्ठा device_node *avr;
	phys_addr_t phys_addr;
	पूर्णांक len;

	avr = of_find_node_by_path("/soc10x/serial@80004500");
	अगर (!avr)
		वापस -EINVAL;

	avr_घड़ी = *(u32*)of_get_property(avr, "clock-frequency", &len);
	phys_addr = ((u32*)of_get_property(avr, "reg", &len))[0];

	अगर (!avr_घड़ी || !phys_addr)
		वापस -EINVAL;

	avr_addr = ioremap(phys_addr, 32);
	अगर (!avr_addr)
		वापस -EFAULT;

	ls_uart_init();

	INIT_WORK(&wd_work, wd_stop);
	schedule_work(&wd_work);

	वापस 0;
पूर्ण

machine_late_initcall(linkstation, ls_uarts_init);
