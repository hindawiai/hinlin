<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * udbg क्रम NS16550 compatible serial ports
 *
 * Copyright (C) 2001-2005 PPC 64 Team, IBM Corp
 */
#समावेश <linux/types.h>
#समावेश <यंत्र/udbg.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/reg_a2.h>

बाह्य u8 real_पढ़ोb(अस्थिर u8 __iomem  *addr);
बाह्य व्योम real_ग_लिखोb(u8 data, अस्थिर u8 __iomem *addr);
बाह्य u8 real_205_पढ़ोb(अस्थिर u8 __iomem  *addr);
बाह्य व्योम real_205_ग_लिखोb(u8 data, अस्थिर u8 __iomem *addr);

#घोषणा UART_RBR	0
#घोषणा UART_IER	1
#घोषणा UART_FCR	2
#घोषणा UART_LCR	3
#घोषणा UART_MCR	4
#घोषणा UART_LSR	5
#घोषणा UART_MSR	6
#घोषणा UART_SCR	7
#घोषणा UART_THR	UART_RBR
#घोषणा UART_IIR	UART_FCR
#घोषणा UART_DLL	UART_RBR
#घोषणा UART_DLM	UART_IER
#घोषणा UART_DLAB	UART_LCR

#घोषणा LSR_DR   0x01  /* Data पढ़ोy */
#घोषणा LSR_OE   0x02  /* Overrun */
#घोषणा LSR_PE   0x04  /* Parity error */
#घोषणा LSR_FE   0x08  /* Framing error */
#घोषणा LSR_BI   0x10  /* Break */
#घोषणा LSR_THRE 0x20  /* Xmit holding रेजिस्टर empty */
#घोषणा LSR_TEMT 0x40  /* Xmitter empty */
#घोषणा LSR_ERR  0x80  /* Error */

#घोषणा LCR_DLAB 0x80

अटल u8 (*udbg_uart_in)(अचिन्हित पूर्णांक reg);
अटल व्योम (*udbg_uart_out)(अचिन्हित पूर्णांक reg, u8 data);

अटल व्योम udbg_uart_flush(व्योम)
अणु
	अगर (!udbg_uart_in)
		वापस;

	/* रुको क्रम idle */
	जबतक ((udbg_uart_in(UART_LSR) & LSR_THRE) == 0)
		cpu_relax();
पूर्ण

अटल व्योम udbg_uart_अ_दो(अक्षर c)
अणु
	अगर (!udbg_uart_out)
		वापस;

	अगर (c == '\n')
		udbg_uart_अ_दो('\r');
	udbg_uart_flush();
	udbg_uart_out(UART_THR, c);
पूर्ण

अटल पूर्णांक udbg_uart_अ_लो_poll(व्योम)
अणु
	अगर (!udbg_uart_in)
		वापस -1;

	अगर (!(udbg_uart_in(UART_LSR) & LSR_DR))
		वापस udbg_uart_in(UART_RBR);

	वापस -1;
पूर्ण

अटल पूर्णांक udbg_uart_अ_लो(व्योम)
अणु
	अगर (!udbg_uart_in)
		वापस -1;
	/* रुको क्रम अक्षर */
	जबतक (!(udbg_uart_in(UART_LSR) & LSR_DR))
		cpu_relax();
	वापस udbg_uart_in(UART_RBR);
पूर्ण

अटल व्योम udbg_use_uart(व्योम)
अणु
	udbg_अ_दो = udbg_uart_अ_दो;
	udbg_flush = udbg_uart_flush;
	udbg_अ_लो = udbg_uart_अ_लो;
	udbg_अ_लो_poll = udbg_uart_अ_लो_poll;
पूर्ण

व्योम udbg_uart_setup(अचिन्हित पूर्णांक speed, अचिन्हित पूर्णांक घड़ी)
अणु
	अचिन्हित पूर्णांक dll, base_bauds;

	अगर (!udbg_uart_out)
		वापस;

	अगर (घड़ी == 0)
		घड़ी = 1843200;
	अगर (speed == 0)
		speed = 9600;

	base_bauds = घड़ी / 16;
	dll = base_bauds / speed;

	udbg_uart_out(UART_LCR, 0x00);
	udbg_uart_out(UART_IER, 0xff);
	udbg_uart_out(UART_IER, 0x00);
	udbg_uart_out(UART_LCR, LCR_DLAB);
	udbg_uart_out(UART_DLL, dll & 0xff);
	udbg_uart_out(UART_DLM, dll >> 8);
	/* 8 data, 1 stop, no parity */
	udbg_uart_out(UART_LCR, 0x3);
	/* RTS/DTR */
	udbg_uart_out(UART_MCR, 0x3);
	/* Clear & enable FIFOs */
	udbg_uart_out(UART_FCR, 0x7);
पूर्ण

अचिन्हित पूर्णांक udbg_probe_uart_speed(अचिन्हित पूर्णांक घड़ी)
अणु
	अचिन्हित पूर्णांक dll, dlm, भागisor, prescaler, speed;
	u8 old_lcr;

	old_lcr = udbg_uart_in(UART_LCR);

	/* select भागisor latch रेजिस्टरs.  */
	udbg_uart_out(UART_LCR, old_lcr | LCR_DLAB);

	/* now, पढ़ो the भागisor */
	dll = udbg_uart_in(UART_DLL);
	dlm = udbg_uart_in(UART_DLM);
	भागisor = dlm << 8 | dll;

	/* check prescaling */
	अगर (udbg_uart_in(UART_MCR) & 0x80)
		prescaler = 4;
	अन्यथा
		prescaler = 1;

	/* restore the LCR */
	udbg_uart_out(UART_LCR, old_lcr);

	/* calculate speed */
	speed = (घड़ी / prescaler) / (भागisor * 16);

	/* sanity check */
	अगर (speed > (घड़ी / 16))
		speed = 9600;

	वापस speed;
पूर्ण

अटल जोड़ अणु
	अचिन्हित अक्षर __iomem *mmio_base;
	अचिन्हित दीर्घ pio_base;
पूर्ण udbg_uart;

अटल अचिन्हित पूर्णांक udbg_uart_stride = 1;

अटल u8 udbg_uart_in_pio(अचिन्हित पूर्णांक reg)
अणु
	वापस inb(udbg_uart.pio_base + (reg * udbg_uart_stride));
पूर्ण

अटल व्योम udbg_uart_out_pio(अचिन्हित पूर्णांक reg, u8 data)
अणु
	outb(data, udbg_uart.pio_base + (reg * udbg_uart_stride));
पूर्ण

व्योम udbg_uart_init_pio(अचिन्हित दीर्घ port, अचिन्हित पूर्णांक stride)
अणु
	अगर (!port)
		वापस;
	udbg_uart.pio_base = port;
	udbg_uart_stride = stride;
	udbg_uart_in = udbg_uart_in_pio;
	udbg_uart_out = udbg_uart_out_pio;
	udbg_use_uart();
पूर्ण

अटल u8 udbg_uart_in_mmio(अचिन्हित पूर्णांक reg)
अणु
	वापस in_8(udbg_uart.mmio_base + (reg * udbg_uart_stride));
पूर्ण

अटल व्योम udbg_uart_out_mmio(अचिन्हित पूर्णांक reg, u8 data)
अणु
	out_8(udbg_uart.mmio_base + (reg * udbg_uart_stride), data);
पूर्ण


व्योम udbg_uart_init_mmio(व्योम __iomem *addr, अचिन्हित पूर्णांक stride)
अणु
	अगर (!addr)
		वापस;
	udbg_uart.mmio_base = addr;
	udbg_uart_stride = stride;
	udbg_uart_in = udbg_uart_in_mmio;
	udbg_uart_out = udbg_uart_out_mmio;
	udbg_use_uart();
पूर्ण

#अगर_घोषित CONFIG_PPC_MAPLE

#घोषणा UDBG_UART_MAPLE_ADDR	((व्योम __iomem *)0xf40003f8)

अटल u8 udbg_uart_in_maple(अचिन्हित पूर्णांक reg)
अणु
	वापस real_पढ़ोb(UDBG_UART_MAPLE_ADDR + reg);
पूर्ण

अटल व्योम udbg_uart_out_maple(अचिन्हित पूर्णांक reg, u8 val)
अणु
	real_ग_लिखोb(val, UDBG_UART_MAPLE_ADDR + reg);
पूर्ण

व्योम __init udbg_init_maple_realmode(व्योम)
अणु
	udbg_uart_in = udbg_uart_in_maple;
	udbg_uart_out = udbg_uart_out_maple;
	udbg_use_uart();
पूर्ण

#पूर्ण_अगर /* CONFIG_PPC_MAPLE */

#अगर_घोषित CONFIG_PPC_PASEMI

#घोषणा UDBG_UART_PAS_ADDR	((व्योम __iomem *)0xfcff03f8UL)

अटल u8 udbg_uart_in_pas(अचिन्हित पूर्णांक reg)
अणु
	वापस real_205_पढ़ोb(UDBG_UART_PAS_ADDR + reg);
पूर्ण

अटल व्योम udbg_uart_out_pas(अचिन्हित पूर्णांक reg, u8 val)
अणु
	real_205_ग_लिखोb(val, UDBG_UART_PAS_ADDR + reg);
पूर्ण

व्योम __init udbg_init_pas_realmode(व्योम)
अणु
	udbg_uart_in = udbg_uart_in_pas;
	udbg_uart_out = udbg_uart_out_pas;
	udbg_use_uart();
पूर्ण

#पूर्ण_अगर /* CONFIG_PPC_PASEMI */

#अगर_घोषित CONFIG_PPC_EARLY_DEBUG_44x

#समावेश <platक्रमms/44x/44x.h>

अटल u8 udbg_uart_in_44x_as1(अचिन्हित पूर्णांक reg)
अणु
	वापस as1_पढ़ोb((व्योम __iomem *)PPC44x_EARLY_DEBUG_VIRTADDR + reg);
पूर्ण

अटल व्योम udbg_uart_out_44x_as1(अचिन्हित पूर्णांक reg, u8 val)
अणु
	as1_ग_लिखोb(val, (व्योम __iomem *)PPC44x_EARLY_DEBUG_VIRTADDR + reg);
पूर्ण

व्योम __init udbg_init_44x_as1(व्योम)
अणु
	udbg_uart_in = udbg_uart_in_44x_as1;
	udbg_uart_out = udbg_uart_out_44x_as1;
	udbg_use_uart();
पूर्ण

#पूर्ण_अगर /* CONFIG_PPC_EARLY_DEBUG_44x */

#अगर_घोषित CONFIG_PPC_EARLY_DEBUG_40x

अटल u8 udbg_uart_in_40x(अचिन्हित पूर्णांक reg)
अणु
	वापस real_पढ़ोb((व्योम __iomem *)CONFIG_PPC_EARLY_DEBUG_40x_PHYSADDR
			  + reg);
पूर्ण

अटल व्योम udbg_uart_out_40x(अचिन्हित पूर्णांक reg, u8 val)
अणु
	real_ग_लिखोb(val, (व्योम __iomem *)CONFIG_PPC_EARLY_DEBUG_40x_PHYSADDR
		    + reg);
पूर्ण

व्योम __init udbg_init_40x_realmode(व्योम)
अणु
	udbg_uart_in = udbg_uart_in_40x;
	udbg_uart_out = udbg_uart_out_40x;
	udbg_use_uart();
पूर्ण

#पूर्ण_अगर /* CONFIG_PPC_EARLY_DEBUG_40x */
