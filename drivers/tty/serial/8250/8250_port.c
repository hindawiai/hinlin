<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 *  Base port operations क्रम 8250/16550-type serial ports
 *
 *  Based on drivers/अक्षर/serial.c, by Linus Torvalds, Theoकरोre Ts'o.
 *  Split from 8250_core.c, Copyright (C) 2001 Russell King.
 *
 * A note about mapbase / membase
 *
 *  mapbase is the physical address of the IO port.
 *  membase is an 'ioremapped' cookie.
 */

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/ioport.h>
#समावेश <linux/init.h>
#समावेश <linux/console.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/sysrq.h>
#समावेश <linux/delay.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/tty.h>
#समावेश <linux/ratelimit.h>
#समावेश <linux/tty_flip.h>
#समावेश <linux/serial.h>
#समावेश <linux/serial_8250.h>
#समावेश <linux/nmi.h>
#समावेश <linux/mutex.h>
#समावेश <linux/slab.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/kसमय.स>

#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/irq.h>

#समावेश "8250.h"

/* Nuvoton NPCM समयout रेजिस्टर */
#घोषणा UART_NPCM_TOR          7
#घोषणा UART_NPCM_TOIE         BIT(7)  /* Timeout Interrupt Enable */

/*
 * Debugging.
 */
#अगर 0
#घोषणा DEBUG_AUTOCONF(fmt...)	prपूर्णांकk(fmt)
#अन्यथा
#घोषणा DEBUG_AUTOCONF(fmt...)	करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर

#घोषणा BOTH_EMPTY	(UART_LSR_TEMT | UART_LSR_THRE)

/*
 * Here we define the शेष xmit fअगरo size used क्रम each type of UART.
 */
अटल स्थिर काष्ठा serial8250_config uart_config[] = अणु
	[PORT_UNKNOWN] = अणु
		.name		= "unknown",
		.fअगरo_size	= 1,
		.tx_loadsz	= 1,
	पूर्ण,
	[PORT_8250] = अणु
		.name		= "8250",
		.fअगरo_size	= 1,
		.tx_loadsz	= 1,
	पूर्ण,
	[PORT_16450] = अणु
		.name		= "16450",
		.fअगरo_size	= 1,
		.tx_loadsz	= 1,
	पूर्ण,
	[PORT_16550] = अणु
		.name		= "16550",
		.fअगरo_size	= 1,
		.tx_loadsz	= 1,
	पूर्ण,
	[PORT_16550A] = अणु
		.name		= "16550A",
		.fअगरo_size	= 16,
		.tx_loadsz	= 16,
		.fcr		= UART_FCR_ENABLE_FIFO | UART_FCR_R_TRIG_10,
		.rxtrig_bytes	= अणु1, 4, 8, 14पूर्ण,
		.flags		= UART_CAP_FIFO,
	पूर्ण,
	[PORT_CIRRUS] = अणु
		.name		= "Cirrus",
		.fअगरo_size	= 1,
		.tx_loadsz	= 1,
	पूर्ण,
	[PORT_16650] = अणु
		.name		= "ST16650",
		.fअगरo_size	= 1,
		.tx_loadsz	= 1,
		.flags		= UART_CAP_FIFO | UART_CAP_EFR | UART_CAP_SLEEP,
	पूर्ण,
	[PORT_16650V2] = अणु
		.name		= "ST16650V2",
		.fअगरo_size	= 32,
		.tx_loadsz	= 16,
		.fcr		= UART_FCR_ENABLE_FIFO | UART_FCR_R_TRIG_01 |
				  UART_FCR_T_TRIG_00,
		.rxtrig_bytes	= अणु8, 16, 24, 28पूर्ण,
		.flags		= UART_CAP_FIFO | UART_CAP_EFR | UART_CAP_SLEEP,
	पूर्ण,
	[PORT_16750] = अणु
		.name		= "TI16750",
		.fअगरo_size	= 64,
		.tx_loadsz	= 64,
		.fcr		= UART_FCR_ENABLE_FIFO | UART_FCR_R_TRIG_10 |
				  UART_FCR7_64BYTE,
		.rxtrig_bytes	= अणु1, 16, 32, 56पूर्ण,
		.flags		= UART_CAP_FIFO | UART_CAP_SLEEP | UART_CAP_AFE,
	पूर्ण,
	[PORT_STARTECH] = अणु
		.name		= "Startech",
		.fअगरo_size	= 1,
		.tx_loadsz	= 1,
	पूर्ण,
	[PORT_16C950] = अणु
		.name		= "16C950/954",
		.fअगरo_size	= 128,
		.tx_loadsz	= 128,
		.fcr		= UART_FCR_ENABLE_FIFO | UART_FCR_R_TRIG_10,
		/* UART_CAP_EFR अवरोधs billionon CF bluetooth card. */
		.flags		= UART_CAP_FIFO | UART_CAP_SLEEP,
	पूर्ण,
	[PORT_16654] = अणु
		.name		= "ST16654",
		.fअगरo_size	= 64,
		.tx_loadsz	= 32,
		.fcr		= UART_FCR_ENABLE_FIFO | UART_FCR_R_TRIG_01 |
				  UART_FCR_T_TRIG_10,
		.rxtrig_bytes	= अणु8, 16, 56, 60पूर्ण,
		.flags		= UART_CAP_FIFO | UART_CAP_EFR | UART_CAP_SLEEP,
	पूर्ण,
	[PORT_16850] = अणु
		.name		= "XR16850",
		.fअगरo_size	= 128,
		.tx_loadsz	= 128,
		.fcr		= UART_FCR_ENABLE_FIFO | UART_FCR_R_TRIG_10,
		.flags		= UART_CAP_FIFO | UART_CAP_EFR | UART_CAP_SLEEP,
	पूर्ण,
	[PORT_RSA] = अणु
		.name		= "RSA",
		.fअगरo_size	= 2048,
		.tx_loadsz	= 2048,
		.fcr		= UART_FCR_ENABLE_FIFO | UART_FCR_R_TRIG_11,
		.flags		= UART_CAP_FIFO,
	पूर्ण,
	[PORT_NS16550A] = अणु
		.name		= "NS16550A",
		.fअगरo_size	= 16,
		.tx_loadsz	= 16,
		.fcr		= UART_FCR_ENABLE_FIFO | UART_FCR_R_TRIG_10,
		.flags		= UART_CAP_FIFO | UART_NATSEMI,
	पूर्ण,
	[PORT_XSCALE] = अणु
		.name		= "XScale",
		.fअगरo_size	= 32,
		.tx_loadsz	= 32,
		.fcr		= UART_FCR_ENABLE_FIFO | UART_FCR_R_TRIG_10,
		.flags		= UART_CAP_FIFO | UART_CAP_UUE | UART_CAP_RTOIE,
	पूर्ण,
	[PORT_OCTEON] = अणु
		.name		= "OCTEON",
		.fअगरo_size	= 64,
		.tx_loadsz	= 64,
		.fcr		= UART_FCR_ENABLE_FIFO | UART_FCR_R_TRIG_10,
		.flags		= UART_CAP_FIFO,
	पूर्ण,
	[PORT_AR7] = अणु
		.name		= "AR7",
		.fअगरo_size	= 16,
		.tx_loadsz	= 16,
		.fcr		= UART_FCR_ENABLE_FIFO | UART_FCR_R_TRIG_00,
		.flags		= UART_CAP_FIFO /* | UART_CAP_AFE */,
	पूर्ण,
	[PORT_U6_16550A] = अणु
		.name		= "U6_16550A",
		.fअगरo_size	= 64,
		.tx_loadsz	= 64,
		.fcr		= UART_FCR_ENABLE_FIFO | UART_FCR_R_TRIG_10,
		.flags		= UART_CAP_FIFO | UART_CAP_AFE,
	पूर्ण,
	[PORT_TEGRA] = अणु
		.name		= "Tegra",
		.fअगरo_size	= 32,
		.tx_loadsz	= 8,
		.fcr		= UART_FCR_ENABLE_FIFO | UART_FCR_R_TRIG_01 |
				  UART_FCR_T_TRIG_01,
		.rxtrig_bytes	= अणु1, 4, 8, 14पूर्ण,
		.flags		= UART_CAP_FIFO | UART_CAP_RTOIE,
	पूर्ण,
	[PORT_XR17D15X] = अणु
		.name		= "XR17D15X",
		.fअगरo_size	= 64,
		.tx_loadsz	= 64,
		.fcr		= UART_FCR_ENABLE_FIFO | UART_FCR_R_TRIG_10,
		.flags		= UART_CAP_FIFO | UART_CAP_AFE | UART_CAP_EFR |
				  UART_CAP_SLEEP,
	पूर्ण,
	[PORT_XR17V35X] = अणु
		.name		= "XR17V35X",
		.fअगरo_size	= 256,
		.tx_loadsz	= 256,
		.fcr		= UART_FCR_ENABLE_FIFO | UART_FCR_R_TRIG_11 |
				  UART_FCR_T_TRIG_11,
		.flags		= UART_CAP_FIFO | UART_CAP_AFE | UART_CAP_EFR |
				  UART_CAP_SLEEP,
	पूर्ण,
	[PORT_LPC3220] = अणु
		.name		= "LPC3220",
		.fअगरo_size	= 64,
		.tx_loadsz	= 32,
		.fcr		= UART_FCR_DMA_SELECT | UART_FCR_ENABLE_FIFO |
				  UART_FCR_R_TRIG_00 | UART_FCR_T_TRIG_00,
		.flags		= UART_CAP_FIFO,
	पूर्ण,
	[PORT_BRCM_TRUMANAGE] = अणु
		.name		= "TruManage",
		.fअगरo_size	= 1,
		.tx_loadsz	= 1024,
		.flags		= UART_CAP_HFIFO,
	पूर्ण,
	[PORT_8250_CIR] = अणु
		.name		= "CIR port"
	पूर्ण,
	[PORT_ALTR_16550_F32] = अणु
		.name		= "Altera 16550 FIFO32",
		.fअगरo_size	= 32,
		.tx_loadsz	= 32,
		.fcr		= UART_FCR_ENABLE_FIFO | UART_FCR_R_TRIG_10,
		.rxtrig_bytes	= अणु1, 8, 16, 30पूर्ण,
		.flags		= UART_CAP_FIFO | UART_CAP_AFE,
	पूर्ण,
	[PORT_ALTR_16550_F64] = अणु
		.name		= "Altera 16550 FIFO64",
		.fअगरo_size	= 64,
		.tx_loadsz	= 64,
		.fcr		= UART_FCR_ENABLE_FIFO | UART_FCR_R_TRIG_10,
		.rxtrig_bytes	= अणु1, 16, 32, 62पूर्ण,
		.flags		= UART_CAP_FIFO | UART_CAP_AFE,
	पूर्ण,
	[PORT_ALTR_16550_F128] = अणु
		.name		= "Altera 16550 FIFO128",
		.fअगरo_size	= 128,
		.tx_loadsz	= 128,
		.fcr		= UART_FCR_ENABLE_FIFO | UART_FCR_R_TRIG_10,
		.rxtrig_bytes	= अणु1, 32, 64, 126पूर्ण,
		.flags		= UART_CAP_FIFO | UART_CAP_AFE,
	पूर्ण,
	/*
	 * tx_loadsz is set to 63-bytes instead of 64-bytes to implement
	 * workaround of errata A-008006 which states that tx_loadsz should
	 * be configured less than Maximum supported fअगरo bytes.
	 */
	[PORT_16550A_FSL64] = अणु
		.name		= "16550A_FSL64",
		.fअगरo_size	= 64,
		.tx_loadsz	= 63,
		.fcr		= UART_FCR_ENABLE_FIFO | UART_FCR_R_TRIG_10 |
				  UART_FCR7_64BYTE,
		.flags		= UART_CAP_FIFO,
	पूर्ण,
	[PORT_RT2880] = अणु
		.name		= "Palmchip BK-3103",
		.fअगरo_size	= 16,
		.tx_loadsz	= 16,
		.fcr		= UART_FCR_ENABLE_FIFO | UART_FCR_R_TRIG_10,
		.rxtrig_bytes	= अणु1, 4, 8, 14पूर्ण,
		.flags		= UART_CAP_FIFO,
	पूर्ण,
	[PORT_DA830] = अणु
		.name		= "TI DA8xx/66AK2x",
		.fअगरo_size	= 16,
		.tx_loadsz	= 16,
		.fcr		= UART_FCR_DMA_SELECT | UART_FCR_ENABLE_FIFO |
				  UART_FCR_R_TRIG_10,
		.rxtrig_bytes	= अणु1, 4, 8, 14पूर्ण,
		.flags		= UART_CAP_FIFO | UART_CAP_AFE,
	पूर्ण,
	[PORT_MTK_BTIF] = अणु
		.name		= "MediaTek BTIF",
		.fअगरo_size	= 16,
		.tx_loadsz	= 16,
		.fcr		= UART_FCR_ENABLE_FIFO |
				  UART_FCR_CLEAR_RCVR | UART_FCR_CLEAR_XMIT,
		.flags		= UART_CAP_FIFO,
	पूर्ण,
	[PORT_NPCM] = अणु
		.name		= "Nuvoton 16550",
		.fअगरo_size	= 16,
		.tx_loadsz	= 16,
		.fcr		= UART_FCR_ENABLE_FIFO | UART_FCR_R_TRIG_10 |
				  UART_FCR_CLEAR_RCVR | UART_FCR_CLEAR_XMIT,
		.rxtrig_bytes	= अणु1, 4, 8, 14पूर्ण,
		.flags		= UART_CAP_FIFO,
	पूर्ण,
	[PORT_SUNIX] = अणु
		.name		= "Sunix",
		.fअगरo_size	= 128,
		.tx_loadsz	= 128,
		.fcr		= UART_FCR_ENABLE_FIFO | UART_FCR_R_TRIG_10,
		.rxtrig_bytes	= अणु1, 32, 64, 112पूर्ण,
		.flags		= UART_CAP_FIFO | UART_CAP_SLEEP,
	पूर्ण,
पूर्ण;

/* Uart भागisor latch पढ़ो */
अटल पूर्णांक शेष_serial_dl_पढ़ो(काष्ठा uart_8250_port *up)
अणु
	वापस serial_in(up, UART_DLL) | serial_in(up, UART_DLM) << 8;
पूर्ण

/* Uart भागisor latch ग_लिखो */
अटल व्योम शेष_serial_dl_ग_लिखो(काष्ठा uart_8250_port *up, पूर्णांक value)
अणु
	serial_out(up, UART_DLL, value & 0xff);
	serial_out(up, UART_DLM, value >> 8 & 0xff);
पूर्ण

#अगर_घोषित CONFIG_SERIAL_8250_RT288X

/* Au1x00/RT288x UART hardware has a weird रेजिस्टर layout */
अटल स्थिर s8 au_io_in_map[8] = अणु
	 0,	/* UART_RX  */
	 2,	/* UART_IER */
	 3,	/* UART_IIR */
	 5,	/* UART_LCR */
	 6,	/* UART_MCR */
	 7,	/* UART_LSR */
	 8,	/* UART_MSR */
	-1,	/* UART_SCR (unmapped) */
पूर्ण;

अटल स्थिर s8 au_io_out_map[8] = अणु
	 1,	/* UART_TX  */
	 2,	/* UART_IER */
	 4,	/* UART_FCR */
	 5,	/* UART_LCR */
	 6,	/* UART_MCR */
	-1,	/* UART_LSR (unmapped) */
	-1,	/* UART_MSR (unmapped) */
	-1,	/* UART_SCR (unmapped) */
पूर्ण;

अचिन्हित पूर्णांक au_serial_in(काष्ठा uart_port *p, पूर्णांक offset)
अणु
	अगर (offset >= ARRAY_SIZE(au_io_in_map))
		वापस अच_पूर्णांक_उच्च;
	offset = au_io_in_map[offset];
	अगर (offset < 0)
		वापस अच_पूर्णांक_उच्च;
	वापस __raw_पढ़ोl(p->membase + (offset << p->regshअगरt));
पूर्ण

व्योम au_serial_out(काष्ठा uart_port *p, पूर्णांक offset, पूर्णांक value)
अणु
	अगर (offset >= ARRAY_SIZE(au_io_out_map))
		वापस;
	offset = au_io_out_map[offset];
	अगर (offset < 0)
		वापस;
	__raw_ग_लिखोl(value, p->membase + (offset << p->regshअगरt));
पूर्ण

/* Au1x00 haven't got a standard भागisor latch */
अटल पूर्णांक au_serial_dl_पढ़ो(काष्ठा uart_8250_port *up)
अणु
	वापस __raw_पढ़ोl(up->port.membase + 0x28);
पूर्ण

अटल व्योम au_serial_dl_ग_लिखो(काष्ठा uart_8250_port *up, पूर्णांक value)
अणु
	__raw_ग_लिखोl(value, up->port.membase + 0x28);
पूर्ण

#पूर्ण_अगर

अटल अचिन्हित पूर्णांक hub6_serial_in(काष्ठा uart_port *p, पूर्णांक offset)
अणु
	offset = offset << p->regshअगरt;
	outb(p->hub6 - 1 + offset, p->iobase);
	वापस inb(p->iobase + 1);
पूर्ण

अटल व्योम hub6_serial_out(काष्ठा uart_port *p, पूर्णांक offset, पूर्णांक value)
अणु
	offset = offset << p->regshअगरt;
	outb(p->hub6 - 1 + offset, p->iobase);
	outb(value, p->iobase + 1);
पूर्ण

अटल अचिन्हित पूर्णांक mem_serial_in(काष्ठा uart_port *p, पूर्णांक offset)
अणु
	offset = offset << p->regshअगरt;
	वापस पढ़ोb(p->membase + offset);
पूर्ण

अटल व्योम mem_serial_out(काष्ठा uart_port *p, पूर्णांक offset, पूर्णांक value)
अणु
	offset = offset << p->regshअगरt;
	ग_लिखोb(value, p->membase + offset);
पूर्ण

अटल व्योम mem16_serial_out(काष्ठा uart_port *p, पूर्णांक offset, पूर्णांक value)
अणु
	offset = offset << p->regshअगरt;
	ग_लिखोw(value, p->membase + offset);
पूर्ण

अटल अचिन्हित पूर्णांक mem16_serial_in(काष्ठा uart_port *p, पूर्णांक offset)
अणु
	offset = offset << p->regshअगरt;
	वापस पढ़ोw(p->membase + offset);
पूर्ण

अटल व्योम mem32_serial_out(काष्ठा uart_port *p, पूर्णांक offset, पूर्णांक value)
अणु
	offset = offset << p->regshअगरt;
	ग_लिखोl(value, p->membase + offset);
पूर्ण

अटल अचिन्हित पूर्णांक mem32_serial_in(काष्ठा uart_port *p, पूर्णांक offset)
अणु
	offset = offset << p->regshअगरt;
	वापस पढ़ोl(p->membase + offset);
पूर्ण

अटल व्योम mem32be_serial_out(काष्ठा uart_port *p, पूर्णांक offset, पूर्णांक value)
अणु
	offset = offset << p->regshअगरt;
	ioग_लिखो32be(value, p->membase + offset);
पूर्ण

अटल अचिन्हित पूर्णांक mem32be_serial_in(काष्ठा uart_port *p, पूर्णांक offset)
अणु
	offset = offset << p->regshअगरt;
	वापस ioपढ़ो32be(p->membase + offset);
पूर्ण

अटल अचिन्हित पूर्णांक io_serial_in(काष्ठा uart_port *p, पूर्णांक offset)
अणु
	offset = offset << p->regshअगरt;
	वापस inb(p->iobase + offset);
पूर्ण

अटल व्योम io_serial_out(काष्ठा uart_port *p, पूर्णांक offset, पूर्णांक value)
अणु
	offset = offset << p->regshअगरt;
	outb(value, p->iobase + offset);
पूर्ण

अटल पूर्णांक serial8250_शेष_handle_irq(काष्ठा uart_port *port);

अटल व्योम set_io_from_upio(काष्ठा uart_port *p)
अणु
	काष्ठा uart_8250_port *up = up_to_u8250p(p);

	up->dl_पढ़ो = शेष_serial_dl_पढ़ो;
	up->dl_ग_लिखो = शेष_serial_dl_ग_लिखो;

	चयन (p->iotype) अणु
	हाल UPIO_HUB6:
		p->serial_in = hub6_serial_in;
		p->serial_out = hub6_serial_out;
		अवरोध;

	हाल UPIO_MEM:
		p->serial_in = mem_serial_in;
		p->serial_out = mem_serial_out;
		अवरोध;

	हाल UPIO_MEM16:
		p->serial_in = mem16_serial_in;
		p->serial_out = mem16_serial_out;
		अवरोध;

	हाल UPIO_MEM32:
		p->serial_in = mem32_serial_in;
		p->serial_out = mem32_serial_out;
		अवरोध;

	हाल UPIO_MEM32BE:
		p->serial_in = mem32be_serial_in;
		p->serial_out = mem32be_serial_out;
		अवरोध;

#अगर_घोषित CONFIG_SERIAL_8250_RT288X
	हाल UPIO_AU:
		p->serial_in = au_serial_in;
		p->serial_out = au_serial_out;
		up->dl_पढ़ो = au_serial_dl_पढ़ो;
		up->dl_ग_लिखो = au_serial_dl_ग_लिखो;
		अवरोध;
#पूर्ण_अगर

	शेष:
		p->serial_in = io_serial_in;
		p->serial_out = io_serial_out;
		अवरोध;
	पूर्ण
	/* Remember loaded iotype */
	up->cur_iotype = p->iotype;
	p->handle_irq = serial8250_शेष_handle_irq;
पूर्ण

अटल व्योम
serial_port_out_sync(काष्ठा uart_port *p, पूर्णांक offset, पूर्णांक value)
अणु
	चयन (p->iotype) अणु
	हाल UPIO_MEM:
	हाल UPIO_MEM16:
	हाल UPIO_MEM32:
	हाल UPIO_MEM32BE:
	हाल UPIO_AU:
		p->serial_out(p, offset, value);
		p->serial_in(p, UART_LCR);	/* safe, no side-effects */
		अवरोध;
	शेष:
		p->serial_out(p, offset, value);
	पूर्ण
पूर्ण

/*
 * For the 16C950
 */
अटल व्योम serial_icr_ग_लिखो(काष्ठा uart_8250_port *up, पूर्णांक offset, पूर्णांक value)
अणु
	serial_out(up, UART_SCR, offset);
	serial_out(up, UART_ICR, value);
पूर्ण

अटल अचिन्हित पूर्णांक serial_icr_पढ़ो(काष्ठा uart_8250_port *up, पूर्णांक offset)
अणु
	अचिन्हित पूर्णांक value;

	serial_icr_ग_लिखो(up, UART_ACR, up->acr | UART_ACR_ICRRD);
	serial_out(up, UART_SCR, offset);
	value = serial_in(up, UART_ICR);
	serial_icr_ग_लिखो(up, UART_ACR, up->acr);

	वापस value;
पूर्ण

/*
 * FIFO support.
 */
अटल व्योम serial8250_clear_fअगरos(काष्ठा uart_8250_port *p)
अणु
	अगर (p->capabilities & UART_CAP_FIFO) अणु
		serial_out(p, UART_FCR, UART_FCR_ENABLE_FIFO);
		serial_out(p, UART_FCR, UART_FCR_ENABLE_FIFO |
			       UART_FCR_CLEAR_RCVR | UART_FCR_CLEAR_XMIT);
		serial_out(p, UART_FCR, 0);
	पूर्ण
पूर्ण

अटल क्रमागत hrसमयr_restart serial8250_em485_handle_start_tx(काष्ठा hrसमयr *t);
अटल क्रमागत hrसमयr_restart serial8250_em485_handle_stop_tx(काष्ठा hrसमयr *t);

व्योम serial8250_clear_and_reinit_fअगरos(काष्ठा uart_8250_port *p)
अणु
	serial8250_clear_fअगरos(p);
	serial_out(p, UART_FCR, p->fcr);
पूर्ण
EXPORT_SYMBOL_GPL(serial8250_clear_and_reinit_fअगरos);

व्योम serial8250_rpm_get(काष्ठा uart_8250_port *p)
अणु
	अगर (!(p->capabilities & UART_CAP_RPM))
		वापस;
	pm_runसमय_get_sync(p->port.dev);
पूर्ण
EXPORT_SYMBOL_GPL(serial8250_rpm_get);

व्योम serial8250_rpm_put(काष्ठा uart_8250_port *p)
अणु
	अगर (!(p->capabilities & UART_CAP_RPM))
		वापस;
	pm_runसमय_mark_last_busy(p->port.dev);
	pm_runसमय_put_स्वतःsuspend(p->port.dev);
पूर्ण
EXPORT_SYMBOL_GPL(serial8250_rpm_put);

/**
 *	serial8250_em485_init() - put uart_8250_port पूर्णांकo rs485 emulating
 *	@p:	uart_8250_port port instance
 *
 *	The function is used to start rs485 software emulating on the
 *	&काष्ठा uart_8250_port* @p. Namely, RTS is चयनed beक्रमe/after
 *	transmission. The function is idempotent, so it is safe to call it
 *	multiple बार.
 *
 *	The caller MUST enable पूर्णांकerrupt on empty shअगरt रेजिस्टर beक्रमe
 *	calling serial8250_em485_init(). This पूर्णांकerrupt is not a part of
 *	8250 standard, but implementation defined.
 *
 *	The function is supposed to be called from .rs485_config callback
 *	or from any other callback रक्षित with p->port.lock spinlock.
 *
 *	See also serial8250_em485_destroy()
 *
 *	Return 0 - success, -त्रुटि_सं - otherwise
 */
अटल पूर्णांक serial8250_em485_init(काष्ठा uart_8250_port *p)
अणु
	अगर (p->em485)
		वापस 0;

	p->em485 = kदो_स्मृति(माप(काष्ठा uart_8250_em485), GFP_ATOMIC);
	अगर (!p->em485)
		वापस -ENOMEM;

	hrसमयr_init(&p->em485->stop_tx_समयr, CLOCK_MONOTONIC,
		     HRTIMER_MODE_REL);
	hrसमयr_init(&p->em485->start_tx_समयr, CLOCK_MONOTONIC,
		     HRTIMER_MODE_REL);
	p->em485->stop_tx_समयr.function = &serial8250_em485_handle_stop_tx;
	p->em485->start_tx_समयr.function = &serial8250_em485_handle_start_tx;
	p->em485->port = p;
	p->em485->active_समयr = शून्य;
	p->em485->tx_stopped = true;

	p->rs485_stop_tx(p);

	वापस 0;
पूर्ण

/**
 *	serial8250_em485_destroy() - put uart_8250_port पूर्णांकo normal state
 *	@p:	uart_8250_port port instance
 *
 *	The function is used to stop rs485 software emulating on the
 *	&काष्ठा uart_8250_port* @p. The function is idempotent, so it is safe to
 *	call it multiple बार.
 *
 *	The function is supposed to be called from .rs485_config callback
 *	or from any other callback रक्षित with p->port.lock spinlock.
 *
 *	See also serial8250_em485_init()
 */
व्योम serial8250_em485_destroy(काष्ठा uart_8250_port *p)
अणु
	अगर (!p->em485)
		वापस;

	hrसमयr_cancel(&p->em485->start_tx_समयr);
	hrसमयr_cancel(&p->em485->stop_tx_समयr);

	kमुक्त(p->em485);
	p->em485 = शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(serial8250_em485_destroy);

/**
 * serial8250_em485_config() - generic ->rs485_config() callback
 * @port: uart port
 * @rs485: rs485 settings
 *
 * Generic callback usable by 8250 uart drivers to activate rs485 settings
 * अगर the uart is incapable of driving RTS as a Transmit Enable संकेत in
 * hardware, relying on software emulation instead.
 */
पूर्णांक serial8250_em485_config(काष्ठा uart_port *port, काष्ठा serial_rs485 *rs485)
अणु
	काष्ठा uart_8250_port *up = up_to_u8250p(port);

	/* pick sane settings अगर the user hasn't */
	अगर (!!(rs485->flags & SER_RS485_RTS_ON_SEND) ==
	    !!(rs485->flags & SER_RS485_RTS_AFTER_SEND)) अणु
		rs485->flags |= SER_RS485_RTS_ON_SEND;
		rs485->flags &= ~SER_RS485_RTS_AFTER_SEND;
	पूर्ण

	/* clamp the delays to [0, 100ms] */
	rs485->delay_rts_beक्रमe_send = min(rs485->delay_rts_beक्रमe_send, 100U);
	rs485->delay_rts_after_send  = min(rs485->delay_rts_after_send, 100U);

	स_रखो(rs485->padding, 0, माप(rs485->padding));
	port->rs485 = *rs485;

	gpiod_set_value(port->rs485_term_gpio,
			rs485->flags & SER_RS485_TERMINATE_BUS);

	/*
	 * Both serial8250_em485_init() and serial8250_em485_destroy()
	 * are idempotent.
	 */
	अगर (rs485->flags & SER_RS485_ENABLED) अणु
		पूर्णांक ret = serial8250_em485_init(up);

		अगर (ret) अणु
			rs485->flags &= ~SER_RS485_ENABLED;
			port->rs485.flags &= ~SER_RS485_ENABLED;
		पूर्ण
		वापस ret;
	पूर्ण

	serial8250_em485_destroy(up);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(serial8250_em485_config);

/*
 * These two wrappers ensure that enable_runसमय_pm_tx() can be called more than
 * once and disable_runसमय_pm_tx() will still disable RPM because the fअगरo is
 * empty and the HW can idle again.
 */
व्योम serial8250_rpm_get_tx(काष्ठा uart_8250_port *p)
अणु
	अचिन्हित अक्षर rpm_active;

	अगर (!(p->capabilities & UART_CAP_RPM))
		वापस;

	rpm_active = xchg(&p->rpm_tx_active, 1);
	अगर (rpm_active)
		वापस;
	pm_runसमय_get_sync(p->port.dev);
पूर्ण
EXPORT_SYMBOL_GPL(serial8250_rpm_get_tx);

व्योम serial8250_rpm_put_tx(काष्ठा uart_8250_port *p)
अणु
	अचिन्हित अक्षर rpm_active;

	अगर (!(p->capabilities & UART_CAP_RPM))
		वापस;

	rpm_active = xchg(&p->rpm_tx_active, 0);
	अगर (!rpm_active)
		वापस;
	pm_runसमय_mark_last_busy(p->port.dev);
	pm_runसमय_put_स्वतःsuspend(p->port.dev);
पूर्ण
EXPORT_SYMBOL_GPL(serial8250_rpm_put_tx);

/*
 * IER sleep support.  UARTs which have EFRs need the "extended
 * capability" bit enabled.  Note that on XR16C850s, we need to
 * reset LCR to ग_लिखो to IER.
 */
अटल व्योम serial8250_set_sleep(काष्ठा uart_8250_port *p, पूर्णांक sleep)
अणु
	अचिन्हित अक्षर lcr = 0, efr = 0;

	serial8250_rpm_get(p);

	अगर (p->capabilities & UART_CAP_SLEEP) अणु
		अगर (p->capabilities & UART_CAP_EFR) अणु
			lcr = serial_in(p, UART_LCR);
			efr = serial_in(p, UART_EFR);
			serial_out(p, UART_LCR, UART_LCR_CONF_MODE_B);
			serial_out(p, UART_EFR, UART_EFR_ECB);
			serial_out(p, UART_LCR, 0);
		पूर्ण
		serial_out(p, UART_IER, sleep ? UART_IERX_SLEEP : 0);
		अगर (p->capabilities & UART_CAP_EFR) अणु
			serial_out(p, UART_LCR, UART_LCR_CONF_MODE_B);
			serial_out(p, UART_EFR, efr);
			serial_out(p, UART_LCR, lcr);
		पूर्ण
	पूर्ण

	serial8250_rpm_put(p);
पूर्ण

#अगर_घोषित CONFIG_SERIAL_8250_RSA
/*
 * Attempts to turn on the RSA FIFO.  Returns zero on failure.
 * We set the port uart घड़ी rate अगर we succeed.
 */
अटल पूर्णांक __enable_rsa(काष्ठा uart_8250_port *up)
अणु
	अचिन्हित अक्षर mode;
	पूर्णांक result;

	mode = serial_in(up, UART_RSA_MSR);
	result = mode & UART_RSA_MSR_FIFO;

	अगर (!result) अणु
		serial_out(up, UART_RSA_MSR, mode | UART_RSA_MSR_FIFO);
		mode = serial_in(up, UART_RSA_MSR);
		result = mode & UART_RSA_MSR_FIFO;
	पूर्ण

	अगर (result)
		up->port.uartclk = SERIAL_RSA_BAUD_BASE * 16;

	वापस result;
पूर्ण

अटल व्योम enable_rsa(काष्ठा uart_8250_port *up)
अणु
	अगर (up->port.type == PORT_RSA) अणु
		अगर (up->port.uartclk != SERIAL_RSA_BAUD_BASE * 16) अणु
			spin_lock_irq(&up->port.lock);
			__enable_rsa(up);
			spin_unlock_irq(&up->port.lock);
		पूर्ण
		अगर (up->port.uartclk == SERIAL_RSA_BAUD_BASE * 16)
			serial_out(up, UART_RSA_FRR, 0);
	पूर्ण
पूर्ण

/*
 * Attempts to turn off the RSA FIFO.  Returns zero on failure.
 * It is unknown why पूर्णांकerrupts were disabled in here.  However,
 * the caller is expected to preserve this behaviour by grabbing
 * the spinlock beक्रमe calling this function.
 */
अटल व्योम disable_rsa(काष्ठा uart_8250_port *up)
अणु
	अचिन्हित अक्षर mode;
	पूर्णांक result;

	अगर (up->port.type == PORT_RSA &&
	    up->port.uartclk == SERIAL_RSA_BAUD_BASE * 16) अणु
		spin_lock_irq(&up->port.lock);

		mode = serial_in(up, UART_RSA_MSR);
		result = !(mode & UART_RSA_MSR_FIFO);

		अगर (!result) अणु
			serial_out(up, UART_RSA_MSR, mode & ~UART_RSA_MSR_FIFO);
			mode = serial_in(up, UART_RSA_MSR);
			result = !(mode & UART_RSA_MSR_FIFO);
		पूर्ण

		अगर (result)
			up->port.uartclk = SERIAL_RSA_BAUD_BASE_LO * 16;
		spin_unlock_irq(&up->port.lock);
	पूर्ण
पूर्ण
#पूर्ण_अगर /* CONFIG_SERIAL_8250_RSA */

/*
 * This is a quickie test to see how big the FIFO is.
 * It करोesn't work at all the time, more's the pity.
 */
अटल पूर्णांक size_fअगरo(काष्ठा uart_8250_port *up)
अणु
	अचिन्हित अक्षर old_fcr, old_mcr, old_lcr;
	अचिन्हित लघु old_dl;
	पूर्णांक count;

	old_lcr = serial_in(up, UART_LCR);
	serial_out(up, UART_LCR, 0);
	old_fcr = serial_in(up, UART_FCR);
	old_mcr = serial8250_in_MCR(up);
	serial_out(up, UART_FCR, UART_FCR_ENABLE_FIFO |
		    UART_FCR_CLEAR_RCVR | UART_FCR_CLEAR_XMIT);
	serial8250_out_MCR(up, UART_MCR_LOOP);
	serial_out(up, UART_LCR, UART_LCR_CONF_MODE_A);
	old_dl = serial_dl_पढ़ो(up);
	serial_dl_ग_लिखो(up, 0x0001);
	serial_out(up, UART_LCR, 0x03);
	क्रम (count = 0; count < 256; count++)
		serial_out(up, UART_TX, count);
	mdelay(20);/* FIXME - schedule_समयout */
	क्रम (count = 0; (serial_in(up, UART_LSR) & UART_LSR_DR) &&
	     (count < 256); count++)
		serial_in(up, UART_RX);
	serial_out(up, UART_FCR, old_fcr);
	serial8250_out_MCR(up, old_mcr);
	serial_out(up, UART_LCR, UART_LCR_CONF_MODE_A);
	serial_dl_ग_लिखो(up, old_dl);
	serial_out(up, UART_LCR, old_lcr);

	वापस count;
पूर्ण

/*
 * Read UART ID using the भागisor method - set DLL and DLM to zero
 * and the revision will be in DLL and device type in DLM.  We
 * preserve the device state across this.
 */
अटल अचिन्हित पूर्णांक स्वतःconfig_पढ़ो_भागisor_id(काष्ठा uart_8250_port *p)
अणु
	अचिन्हित अक्षर old_lcr;
	अचिन्हित पूर्णांक id, old_dl;

	old_lcr = serial_in(p, UART_LCR);
	serial_out(p, UART_LCR, UART_LCR_CONF_MODE_A);
	old_dl = serial_dl_पढ़ो(p);
	serial_dl_ग_लिखो(p, 0);
	id = serial_dl_पढ़ो(p);
	serial_dl_ग_लिखो(p, old_dl);

	serial_out(p, UART_LCR, old_lcr);

	वापस id;
पूर्ण

/*
 * This is a helper routine to स्वतःdetect StarTech/Exar/Oxsemi UART's.
 * When this function is called we know it is at least a StarTech
 * 16650 V2, but it might be one of several StarTech UARTs, or one of
 * its clones.  (We treat the broken original StarTech 16650 V1 as a
 * 16550, and why not?  Startech करोesn't seem to even acknowledge its
 * existence.)
 *
 * What evil have men's minds wrought...
 */
अटल व्योम स्वतःconfig_has_efr(काष्ठा uart_8250_port *up)
अणु
	अचिन्हित पूर्णांक id1, id2, id3, rev;

	/*
	 * Everything with an EFR has SLEEP
	 */
	up->capabilities |= UART_CAP_EFR | UART_CAP_SLEEP;

	/*
	 * First we check to see अगर it's an Oxक्रमd Semiconductor UART.
	 *
	 * If we have to करो this here because some non-National
	 * Semiconductor clone chips lock up अगर you try writing to the
	 * LSR रेजिस्टर (which serial_icr_पढ़ो करोes)
	 */

	/*
	 * Check क्रम Oxक्रमd Semiconductor 16C950.
	 *
	 * EFR [4] must be set अन्यथा this test fails.
	 *
	 * This shouldn't be necessary, but Mike Hudson (Exoray@isys.ca)
	 * claims that it's needed for 952 dual UART's (which are not
	 * recommended क्रम new designs).
	 */
	up->acr = 0;
	serial_out(up, UART_LCR, UART_LCR_CONF_MODE_B);
	serial_out(up, UART_EFR, UART_EFR_ECB);
	serial_out(up, UART_LCR, 0x00);
	id1 = serial_icr_पढ़ो(up, UART_ID1);
	id2 = serial_icr_पढ़ो(up, UART_ID2);
	id3 = serial_icr_पढ़ो(up, UART_ID3);
	rev = serial_icr_पढ़ो(up, UART_REV);

	DEBUG_AUTOCONF("950id=%02x:%02x:%02x:%02x ", id1, id2, id3, rev);

	अगर (id1 == 0x16 && id2 == 0xC9 &&
	    (id3 == 0x50 || id3 == 0x52 || id3 == 0x54)) अणु
		up->port.type = PORT_16C950;

		/*
		 * Enable work around क्रम the Oxक्रमd Semiconductor 952 rev B
		 * chip which causes it to seriously miscalculate baud rates
		 * when DLL is 0.
		 */
		अगर (id3 == 0x52 && rev == 0x01)
			up->bugs |= UART_BUG_QUOT;
		वापस;
	पूर्ण

	/*
	 * We check क्रम a XR16C850 by setting DLL and DLM to 0, and then
	 * पढ़ोing back DLL and DLM.  The chip type depends on the DLM
	 * value पढ़ो back:
	 *  0x10 - XR16C850 and the DLL contains the chip revision.
	 *  0x12 - XR16C2850.
	 *  0x14 - XR16C854.
	 */
	id1 = स्वतःconfig_पढ़ो_भागisor_id(up);
	DEBUG_AUTOCONF("850id=%04x ", id1);

	id2 = id1 >> 8;
	अगर (id2 == 0x10 || id2 == 0x12 || id2 == 0x14) अणु
		up->port.type = PORT_16850;
		वापस;
	पूर्ण

	/*
	 * It wasn't an XR16C850.
	 *
	 * We distinguish between the '654 and the '650 by counting
	 * how many bytes are in the FIFO.  I'm using this क्रम now,
	 * since that's the technique that was sent to me in the
	 * serial driver update, but I'm not convinced this works.
	 * I've had problems करोing this in the past.  -TYT
	 */
	अगर (size_fअगरo(up) == 64)
		up->port.type = PORT_16654;
	अन्यथा
		up->port.type = PORT_16650V2;
पूर्ण

/*
 * We detected a chip without a FIFO.  Only two fall पूर्णांकo
 * this category - the original 8250 and the 16450.  The
 * 16450 has a scratch रेजिस्टर (accessible with LCR=0)
 */
अटल व्योम स्वतःconfig_8250(काष्ठा uart_8250_port *up)
अणु
	अचिन्हित अक्षर scratch, status1, status2;

	up->port.type = PORT_8250;

	scratch = serial_in(up, UART_SCR);
	serial_out(up, UART_SCR, 0xa5);
	status1 = serial_in(up, UART_SCR);
	serial_out(up, UART_SCR, 0x5a);
	status2 = serial_in(up, UART_SCR);
	serial_out(up, UART_SCR, scratch);

	अगर (status1 == 0xa5 && status2 == 0x5a)
		up->port.type = PORT_16450;
पूर्ण

अटल पूर्णांक broken_efr(काष्ठा uart_8250_port *up)
अणु
	/*
	 * Exar ST16C2550 "A2" devices incorrectly detect as
	 * having an EFR, and report an ID of 0x0201.  See
	 * http://linux.derkeiler.com/Mailing-Lists/Kernel/2004-11/4812.hपंचांगl
	 */
	अगर (स्वतःconfig_पढ़ो_भागisor_id(up) == 0x0201 && size_fअगरo(up) == 16)
		वापस 1;

	वापस 0;
पूर्ण

/*
 * We know that the chip has FIFOs.  Does it have an EFR?  The
 * EFR is located in the same रेजिस्टर position as the IIR and
 * we know the top two bits of the IIR are currently set.  The
 * EFR should contain zero.  Try to पढ़ो the EFR.
 */
अटल व्योम स्वतःconfig_16550a(काष्ठा uart_8250_port *up)
अणु
	अचिन्हित अक्षर status1, status2;
	अचिन्हित पूर्णांक iersave;

	up->port.type = PORT_16550A;
	up->capabilities |= UART_CAP_FIFO;

	अगर (!IS_ENABLED(CONFIG_SERIAL_8250_16550A_VARIANTS))
		वापस;

	/*
	 * Check क्रम presence of the EFR when DLAB is set.
	 * Only ST16C650V1 UARTs pass this test.
	 */
	serial_out(up, UART_LCR, UART_LCR_CONF_MODE_A);
	अगर (serial_in(up, UART_EFR) == 0) अणु
		serial_out(up, UART_EFR, 0xA8);
		अगर (serial_in(up, UART_EFR) != 0) अणु
			DEBUG_AUTOCONF("EFRv1 ");
			up->port.type = PORT_16650;
			up->capabilities |= UART_CAP_EFR | UART_CAP_SLEEP;
		पूर्ण अन्यथा अणु
			serial_out(up, UART_LCR, 0);
			serial_out(up, UART_FCR, UART_FCR_ENABLE_FIFO |
				   UART_FCR7_64BYTE);
			status1 = serial_in(up, UART_IIR) >> 5;
			serial_out(up, UART_FCR, 0);
			serial_out(up, UART_LCR, 0);

			अगर (status1 == 7)
				up->port.type = PORT_16550A_FSL64;
			अन्यथा
				DEBUG_AUTOCONF("Motorola 8xxx DUART ");
		पूर्ण
		serial_out(up, UART_EFR, 0);
		वापस;
	पूर्ण

	/*
	 * Maybe it requires 0xbf to be written to the LCR.
	 * (other ST16C650V2 UARTs, TI16C752A, etc)
	 */
	serial_out(up, UART_LCR, UART_LCR_CONF_MODE_B);
	अगर (serial_in(up, UART_EFR) == 0 && !broken_efr(up)) अणु
		DEBUG_AUTOCONF("EFRv2 ");
		स्वतःconfig_has_efr(up);
		वापस;
	पूर्ण

	/*
	 * Check क्रम a National Semiconductor SuperIO chip.
	 * Attempt to चयन to bank 2, पढ़ो the value of the LOOP bit
	 * from EXCR1. Switch back to bank 0, change it in MCR. Then
	 * चयन back to bank 2, पढ़ो it from EXCR1 again and check
	 * it's changed. If so, set baud_base in EXCR2 to 921600. -- dwmw2
	 */
	serial_out(up, UART_LCR, 0);
	status1 = serial8250_in_MCR(up);
	serial_out(up, UART_LCR, 0xE0);
	status2 = serial_in(up, 0x02); /* EXCR1 */

	अगर (!((status2 ^ status1) & UART_MCR_LOOP)) अणु
		serial_out(up, UART_LCR, 0);
		serial8250_out_MCR(up, status1 ^ UART_MCR_LOOP);
		serial_out(up, UART_LCR, 0xE0);
		status2 = serial_in(up, 0x02); /* EXCR1 */
		serial_out(up, UART_LCR, 0);
		serial8250_out_MCR(up, status1);

		अगर ((status2 ^ status1) & UART_MCR_LOOP) अणु
			अचिन्हित लघु quot;

			serial_out(up, UART_LCR, 0xE0);

			quot = serial_dl_पढ़ो(up);
			quot <<= 3;

			अगर (ns16550a_जाओ_highspeed(up))
				serial_dl_ग_लिखो(up, quot);

			serial_out(up, UART_LCR, 0);

			up->port.uartclk = 921600*16;
			up->port.type = PORT_NS16550A;
			up->capabilities |= UART_NATSEMI;
			वापस;
		पूर्ण
	पूर्ण

	/*
	 * No EFR.  Try to detect a TI16750, which only sets bit 5 of
	 * the IIR when 64 byte FIFO mode is enabled when DLAB is set.
	 * Try setting it with and without DLAB set.  Cheap clones
	 * set bit 5 without DLAB set.
	 */
	serial_out(up, UART_LCR, 0);
	serial_out(up, UART_FCR, UART_FCR_ENABLE_FIFO | UART_FCR7_64BYTE);
	status1 = serial_in(up, UART_IIR) >> 5;
	serial_out(up, UART_FCR, UART_FCR_ENABLE_FIFO);
	serial_out(up, UART_LCR, UART_LCR_CONF_MODE_A);
	serial_out(up, UART_FCR, UART_FCR_ENABLE_FIFO | UART_FCR7_64BYTE);
	status2 = serial_in(up, UART_IIR) >> 5;
	serial_out(up, UART_FCR, UART_FCR_ENABLE_FIFO);
	serial_out(up, UART_LCR, 0);

	DEBUG_AUTOCONF("iir1=%d iir2=%d ", status1, status2);

	अगर (status1 == 6 && status2 == 7) अणु
		up->port.type = PORT_16750;
		up->capabilities |= UART_CAP_AFE | UART_CAP_SLEEP;
		वापस;
	पूर्ण

	/*
	 * Try writing and पढ़ोing the UART_IER_UUE bit (b6).
	 * If it works, this is probably one of the Xscale platक्रमm's
	 * पूर्णांकernal UARTs.
	 * We're going to explicitly set the UUE bit to 0 beक्रमe
	 * trying to ग_लिखो and पढ़ो a 1 just to make sure it's not
	 * alपढ़ोy a 1 and maybe locked there beक्रमe we even start start.
	 */
	iersave = serial_in(up, UART_IER);
	serial_out(up, UART_IER, iersave & ~UART_IER_UUE);
	अगर (!(serial_in(up, UART_IER) & UART_IER_UUE)) अणु
		/*
		 * OK it's in a known zero state, try writing and पढ़ोing
		 * without disturbing the current state of the other bits.
		 */
		serial_out(up, UART_IER, iersave | UART_IER_UUE);
		अगर (serial_in(up, UART_IER) & UART_IER_UUE) अणु
			/*
			 * It's an Xscale.
			 * We'll leave the UART_IER_UUE bit set to 1 (enabled).
			 */
			DEBUG_AUTOCONF("Xscale ");
			up->port.type = PORT_XSCALE;
			up->capabilities |= UART_CAP_UUE | UART_CAP_RTOIE;
			वापस;
		पूर्ण
	पूर्ण अन्यथा अणु
		/*
		 * If we got here we couldn't क्रमce the IER_UUE bit to 0.
		 * Log it and जारी.
		 */
		DEBUG_AUTOCONF("Couldn't force IER_UUE to 0 ");
	पूर्ण
	serial_out(up, UART_IER, iersave);

	/*
	 * We distinguish between 16550A and U6 16550A by counting
	 * how many bytes are in the FIFO.
	 */
	अगर (up->port.type == PORT_16550A && size_fअगरo(up) == 64) अणु
		up->port.type = PORT_U6_16550A;
		up->capabilities |= UART_CAP_AFE;
	पूर्ण
पूर्ण

/*
 * This routine is called by rs_init() to initialize a specअगरic serial
 * port.  It determines what type of UART chip this serial port is
 * using: 8250, 16450, 16550, 16550A.  The important question is
 * whether or not this UART is a 16550A or not, since this will
 * determine whether or not we can use its FIFO features or not.
 */
अटल व्योम स्वतःconfig(काष्ठा uart_8250_port *up)
अणु
	अचिन्हित अक्षर status1, scratch, scratch2, scratch3;
	अचिन्हित अक्षर save_lcr, save_mcr;
	काष्ठा uart_port *port = &up->port;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक old_capabilities;

	अगर (!port->iobase && !port->mapbase && !port->membase)
		वापस;

	DEBUG_AUTOCONF("%s: autoconf (0x%04lx, 0x%p): ",
		       port->name, port->iobase, port->membase);

	/*
	 * We really करो need global IRQs disabled here - we're going to
	 * be frobbing the chips IRQ enable रेजिस्टर to see अगर it exists.
	 */
	spin_lock_irqsave(&port->lock, flags);

	up->capabilities = 0;
	up->bugs = 0;

	अगर (!(port->flags & UPF_BUGGY_UART)) अणु
		/*
		 * Do a simple existence test first; अगर we fail this,
		 * there's no poपूर्णांक trying anything अन्यथा.
		 *
		 * 0x80 is used as a nonsense port to prevent against
		 * false positives due to ISA bus भग्न.  The
		 * assumption is that 0x80 is a non-existent port;
		 * which should be safe since include/यंत्र/पन.स also
		 * makes this assumption.
		 *
		 * Note: this is safe as दीर्घ as MCR bit 4 is clear
		 * and the device is in "PC" mode.
		 */
		scratch = serial_in(up, UART_IER);
		serial_out(up, UART_IER, 0);
#अगर_घोषित __i386__
		outb(0xff, 0x080);
#पूर्ण_अगर
		/*
		 * Mask out IER[7:4] bits क्रम test as some UARTs (e.g. TL
		 * 16C754B) allow only to modअगरy them अगर an EFR bit is set.
		 */
		scratch2 = serial_in(up, UART_IER) & 0x0f;
		serial_out(up, UART_IER, 0x0F);
#अगर_घोषित __i386__
		outb(0, 0x080);
#पूर्ण_अगर
		scratch3 = serial_in(up, UART_IER) & 0x0f;
		serial_out(up, UART_IER, scratch);
		अगर (scratch2 != 0 || scratch3 != 0x0F) अणु
			/*
			 * We failed; there's nothing here
			 */
			spin_unlock_irqrestore(&port->lock, flags);
			DEBUG_AUTOCONF("IER test failed (%02x, %02x) ",
				       scratch2, scratch3);
			जाओ out;
		पूर्ण
	पूर्ण

	save_mcr = serial8250_in_MCR(up);
	save_lcr = serial_in(up, UART_LCR);

	/*
	 * Check to see अगर a UART is really there.  Certain broken
	 * पूर्णांकernal modems based on the Rockwell chipset fail this
	 * test, because they apparently करोn't implement the loopback
	 * test mode.  So this test is skipped on the COM 1 through
	 * COM 4 ports.  This *should* be safe, since no board
	 * manufacturer would be stupid enough to design a board
	 * that conflicts with COM 1-4 --- we hope!
	 */
	अगर (!(port->flags & UPF_SKIP_TEST)) अणु
		serial8250_out_MCR(up, UART_MCR_LOOP | 0x0A);
		status1 = serial_in(up, UART_MSR) & 0xF0;
		serial8250_out_MCR(up, save_mcr);
		अगर (status1 != 0x90) अणु
			spin_unlock_irqrestore(&port->lock, flags);
			DEBUG_AUTOCONF("LOOP test failed (%02x) ",
				       status1);
			जाओ out;
		पूर्ण
	पूर्ण

	/*
	 * We're pretty sure there's a port here.  Lets find out what
	 * type of port it is.  The IIR top two bits allows us to find
	 * out अगर it's 8250 or 16450, 16550, 16550A or later.  This
	 * determines what we test क्रम next.
	 *
	 * We also initialise the EFR (अगर any) to zero क्रम later.  The
	 * EFR occupies the same रेजिस्टर location as the FCR and IIR.
	 */
	serial_out(up, UART_LCR, UART_LCR_CONF_MODE_B);
	serial_out(up, UART_EFR, 0);
	serial_out(up, UART_LCR, 0);

	serial_out(up, UART_FCR, UART_FCR_ENABLE_FIFO);
	scratch = serial_in(up, UART_IIR) >> 6;

	चयन (scratch) अणु
	हाल 0:
		स्वतःconfig_8250(up);
		अवरोध;
	हाल 1:
		port->type = PORT_UNKNOWN;
		अवरोध;
	हाल 2:
		port->type = PORT_16550;
		अवरोध;
	हाल 3:
		स्वतःconfig_16550a(up);
		अवरोध;
	पूर्ण

#अगर_घोषित CONFIG_SERIAL_8250_RSA
	/*
	 * Only probe क्रम RSA ports अगर we got the region.
	 */
	अगर (port->type == PORT_16550A && up->probe & UART_PROBE_RSA &&
	    __enable_rsa(up))
		port->type = PORT_RSA;
#पूर्ण_अगर

	serial_out(up, UART_LCR, save_lcr);

	port->fअगरosize = uart_config[up->port.type].fअगरo_size;
	old_capabilities = up->capabilities;
	up->capabilities = uart_config[port->type].flags;
	up->tx_loadsz = uart_config[port->type].tx_loadsz;

	अगर (port->type == PORT_UNKNOWN)
		जाओ out_lock;

	/*
	 * Reset the UART.
	 */
#अगर_घोषित CONFIG_SERIAL_8250_RSA
	अगर (port->type == PORT_RSA)
		serial_out(up, UART_RSA_FRR, 0);
#पूर्ण_अगर
	serial8250_out_MCR(up, save_mcr);
	serial8250_clear_fअगरos(up);
	serial_in(up, UART_RX);
	अगर (up->capabilities & UART_CAP_UUE)
		serial_out(up, UART_IER, UART_IER_UUE);
	अन्यथा
		serial_out(up, UART_IER, 0);

out_lock:
	spin_unlock_irqrestore(&port->lock, flags);

	/*
	 * Check अगर the device is a Fपूर्णांकek F81216A
	 */
	अगर (port->type == PORT_16550A && port->iotype == UPIO_PORT)
		fपूर्णांकek_8250_probe(up);

	अगर (up->capabilities != old_capabilities) अणु
		dev_warn(port->dev, "detected caps %08x should be %08x\n",
			 old_capabilities, up->capabilities);
	पूर्ण
out:
	DEBUG_AUTOCONF("iir=%d ", scratch);
	DEBUG_AUTOCONF("type=%s\n", uart_config[port->type].name);
पूर्ण

अटल व्योम स्वतःconfig_irq(काष्ठा uart_8250_port *up)
अणु
	काष्ठा uart_port *port = &up->port;
	अचिन्हित अक्षर save_mcr, save_ier;
	अचिन्हित अक्षर save_ICP = 0;
	अचिन्हित पूर्णांक ICP = 0;
	अचिन्हित दीर्घ irqs;
	पूर्णांक irq;

	अगर (port->flags & UPF_FOURPORT) अणु
		ICP = (port->iobase & 0xfe0) | 0x1f;
		save_ICP = inb_p(ICP);
		outb_p(0x80, ICP);
		inb_p(ICP);
	पूर्ण

	अगर (uart_console(port))
		console_lock();

	/* क्रमget possible initially masked and pending IRQ */
	probe_irq_off(probe_irq_on());
	save_mcr = serial8250_in_MCR(up);
	save_ier = serial_in(up, UART_IER);
	serial8250_out_MCR(up, UART_MCR_OUT1 | UART_MCR_OUT2);

	irqs = probe_irq_on();
	serial8250_out_MCR(up, 0);
	udelay(10);
	अगर (port->flags & UPF_FOURPORT) अणु
		serial8250_out_MCR(up, UART_MCR_DTR | UART_MCR_RTS);
	पूर्ण अन्यथा अणु
		serial8250_out_MCR(up,
			UART_MCR_DTR | UART_MCR_RTS | UART_MCR_OUT2);
	पूर्ण
	serial_out(up, UART_IER, 0x0f);	/* enable all पूर्णांकrs */
	serial_in(up, UART_LSR);
	serial_in(up, UART_RX);
	serial_in(up, UART_IIR);
	serial_in(up, UART_MSR);
	serial_out(up, UART_TX, 0xFF);
	udelay(20);
	irq = probe_irq_off(irqs);

	serial8250_out_MCR(up, save_mcr);
	serial_out(up, UART_IER, save_ier);

	अगर (port->flags & UPF_FOURPORT)
		outb_p(save_ICP, ICP);

	अगर (uart_console(port))
		console_unlock();

	port->irq = (irq > 0) ? irq : 0;
पूर्ण

अटल व्योम serial8250_stop_rx(काष्ठा uart_port *port)
अणु
	काष्ठा uart_8250_port *up = up_to_u8250p(port);

	serial8250_rpm_get(up);

	up->ier &= ~(UART_IER_RLSI | UART_IER_RDI);
	up->port.पढ़ो_status_mask &= ~UART_LSR_DR;
	serial_port_out(port, UART_IER, up->ier);

	serial8250_rpm_put(up);
पूर्ण

/**
 * serial8250_em485_stop_tx() - generic ->rs485_stop_tx() callback
 * @p: uart 8250 port
 *
 * Generic callback usable by 8250 uart drivers to stop rs485 transmission.
 */
व्योम serial8250_em485_stop_tx(काष्ठा uart_8250_port *p)
अणु
	अचिन्हित अक्षर mcr = serial8250_in_MCR(p);

	अगर (p->port.rs485.flags & SER_RS485_RTS_AFTER_SEND)
		mcr |= UART_MCR_RTS;
	अन्यथा
		mcr &= ~UART_MCR_RTS;
	serial8250_out_MCR(p, mcr);

	/*
	 * Empty the RX FIFO, we are not पूर्णांकerested in anything
	 * received during the half-duplex transmission.
	 * Enable previously disabled RX पूर्णांकerrupts.
	 */
	अगर (!(p->port.rs485.flags & SER_RS485_RX_DURING_TX)) अणु
		serial8250_clear_and_reinit_fअगरos(p);

		p->ier |= UART_IER_RLSI | UART_IER_RDI;
		serial_port_out(&p->port, UART_IER, p->ier);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(serial8250_em485_stop_tx);

अटल क्रमागत hrसमयr_restart serial8250_em485_handle_stop_tx(काष्ठा hrसमयr *t)
अणु
	काष्ठा uart_8250_em485 *em485 = container_of(t, काष्ठा uart_8250_em485,
			stop_tx_समयr);
	काष्ठा uart_8250_port *p = em485->port;
	अचिन्हित दीर्घ flags;

	serial8250_rpm_get(p);
	spin_lock_irqsave(&p->port.lock, flags);
	अगर (em485->active_समयr == &em485->stop_tx_समयr) अणु
		p->rs485_stop_tx(p);
		em485->active_समयr = शून्य;
		em485->tx_stopped = true;
	पूर्ण
	spin_unlock_irqrestore(&p->port.lock, flags);
	serial8250_rpm_put(p);

	वापस HRTIMER_NORESTART;
पूर्ण

अटल व्योम start_hrसमयr_ms(काष्ठा hrसमयr *hrt, अचिन्हित दीर्घ msec)
अणु
	hrसमयr_start(hrt, ms_to_kसमय(msec), HRTIMER_MODE_REL);
पूर्ण

अटल व्योम __stop_tx_rs485(काष्ठा uart_8250_port *p)
अणु
	काष्ठा uart_8250_em485 *em485 = p->em485;

	/*
	 * rs485_stop_tx() is going to set RTS according to config
	 * AND flush RX FIFO अगर required.
	 */
	अगर (p->port.rs485.delay_rts_after_send > 0) अणु
		em485->active_समयr = &em485->stop_tx_समयr;
		start_hrसमयr_ms(&em485->stop_tx_समयr,
				   p->port.rs485.delay_rts_after_send);
	पूर्ण अन्यथा अणु
		p->rs485_stop_tx(p);
		em485->active_समयr = शून्य;
		em485->tx_stopped = true;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम __करो_stop_tx(काष्ठा uart_8250_port *p)
अणु
	अगर (serial8250_clear_THRI(p))
		serial8250_rpm_put_tx(p);
पूर्ण

अटल अंतरभूत व्योम __stop_tx(काष्ठा uart_8250_port *p)
अणु
	काष्ठा uart_8250_em485 *em485 = p->em485;

	अगर (em485) अणु
		अचिन्हित अक्षर lsr = serial_in(p, UART_LSR);
		/*
		 * To provide required समयing and allow FIFO transfer,
		 * __stop_tx_rs485() must be called only when both FIFO and
		 * shअगरt रेजिस्टर are empty. It is क्रम device driver to enable
		 * पूर्णांकerrupt on TEMT.
		 */
		अगर ((lsr & BOTH_EMPTY) != BOTH_EMPTY)
			वापस;

		__stop_tx_rs485(p);
	पूर्ण
	__करो_stop_tx(p);
पूर्ण

अटल व्योम serial8250_stop_tx(काष्ठा uart_port *port)
अणु
	काष्ठा uart_8250_port *up = up_to_u8250p(port);

	serial8250_rpm_get(up);
	__stop_tx(up);

	/*
	 * We really want to stop the transmitter from sending.
	 */
	अगर (port->type == PORT_16C950) अणु
		up->acr |= UART_ACR_TXDIS;
		serial_icr_ग_लिखो(up, UART_ACR, up->acr);
	पूर्ण
	serial8250_rpm_put(up);
पूर्ण

अटल अंतरभूत व्योम __start_tx(काष्ठा uart_port *port)
अणु
	काष्ठा uart_8250_port *up = up_to_u8250p(port);

	अगर (up->dma && !up->dma->tx_dma(up))
		वापस;

	अगर (serial8250_set_THRI(up)) अणु
		अगर (up->bugs & UART_BUG_TXEN) अणु
			अचिन्हित अक्षर lsr;

			lsr = serial_in(up, UART_LSR);
			up->lsr_saved_flags |= lsr & LSR_SAVE_FLAGS;
			अगर (lsr & UART_LSR_THRE)
				serial8250_tx_अक्षरs(up);
		पूर्ण
	पूर्ण

	/*
	 * Re-enable the transmitter अगर we disabled it.
	 */
	अगर (port->type == PORT_16C950 && up->acr & UART_ACR_TXDIS) अणु
		up->acr &= ~UART_ACR_TXDIS;
		serial_icr_ग_लिखो(up, UART_ACR, up->acr);
	पूर्ण
पूर्ण

/**
 * serial8250_em485_start_tx() - generic ->rs485_start_tx() callback
 * @up: uart 8250 port
 *
 * Generic callback usable by 8250 uart drivers to start rs485 transmission.
 * Assumes that setting the RTS bit in the MCR रेजिस्टर means RTS is high.
 * (Some chips use inverse semantics.)  Further assumes that reception is
 * stoppable by disabling the UART_IER_RDI पूर्णांकerrupt.  (Some chips set the
 * UART_LSR_DR bit even when UART_IER_RDI is disabled, foiling this approach.)
 */
व्योम serial8250_em485_start_tx(काष्ठा uart_8250_port *up)
अणु
	अचिन्हित अक्षर mcr = serial8250_in_MCR(up);

	अगर (!(up->port.rs485.flags & SER_RS485_RX_DURING_TX))
		serial8250_stop_rx(&up->port);

	अगर (up->port.rs485.flags & SER_RS485_RTS_ON_SEND)
		mcr |= UART_MCR_RTS;
	अन्यथा
		mcr &= ~UART_MCR_RTS;
	serial8250_out_MCR(up, mcr);
पूर्ण
EXPORT_SYMBOL_GPL(serial8250_em485_start_tx);

अटल अंतरभूत व्योम start_tx_rs485(काष्ठा uart_port *port)
अणु
	काष्ठा uart_8250_port *up = up_to_u8250p(port);
	काष्ठा uart_8250_em485 *em485 = up->em485;

	em485->active_समयr = शून्य;

	अगर (em485->tx_stopped) अणु
		em485->tx_stopped = false;

		up->rs485_start_tx(up);

		अगर (up->port.rs485.delay_rts_beक्रमe_send > 0) अणु
			em485->active_समयr = &em485->start_tx_समयr;
			start_hrसमयr_ms(&em485->start_tx_समयr,
					 up->port.rs485.delay_rts_beक्रमe_send);
			वापस;
		पूर्ण
	पूर्ण

	__start_tx(port);
पूर्ण

अटल क्रमागत hrसमयr_restart serial8250_em485_handle_start_tx(काष्ठा hrसमयr *t)
अणु
	काष्ठा uart_8250_em485 *em485 = container_of(t, काष्ठा uart_8250_em485,
			start_tx_समयr);
	काष्ठा uart_8250_port *p = em485->port;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&p->port.lock, flags);
	अगर (em485->active_समयr == &em485->start_tx_समयr) अणु
		__start_tx(&p->port);
		em485->active_समयr = शून्य;
	पूर्ण
	spin_unlock_irqrestore(&p->port.lock, flags);

	वापस HRTIMER_NORESTART;
पूर्ण

अटल व्योम serial8250_start_tx(काष्ठा uart_port *port)
अणु
	काष्ठा uart_8250_port *up = up_to_u8250p(port);
	काष्ठा uart_8250_em485 *em485 = up->em485;

	serial8250_rpm_get_tx(up);

	अगर (em485 &&
	    em485->active_समयr == &em485->start_tx_समयr)
		वापस;

	अगर (em485)
		start_tx_rs485(port);
	अन्यथा
		__start_tx(port);
पूर्ण

अटल व्योम serial8250_throttle(काष्ठा uart_port *port)
अणु
	port->throttle(port);
पूर्ण

अटल व्योम serial8250_unthrottle(काष्ठा uart_port *port)
अणु
	port->unthrottle(port);
पूर्ण

अटल व्योम serial8250_disable_ms(काष्ठा uart_port *port)
अणु
	काष्ठा uart_8250_port *up = up_to_u8250p(port);

	/* no MSR capabilities */
	अगर (up->bugs & UART_BUG_NOMSR)
		वापस;

	mctrl_gpio_disable_ms(up->gpios);

	up->ier &= ~UART_IER_MSI;
	serial_port_out(port, UART_IER, up->ier);
पूर्ण

अटल व्योम serial8250_enable_ms(काष्ठा uart_port *port)
अणु
	काष्ठा uart_8250_port *up = up_to_u8250p(port);

	/* no MSR capabilities */
	अगर (up->bugs & UART_BUG_NOMSR)
		वापस;

	mctrl_gpio_enable_ms(up->gpios);

	up->ier |= UART_IER_MSI;

	serial8250_rpm_get(up);
	serial_port_out(port, UART_IER, up->ier);
	serial8250_rpm_put(up);
पूर्ण

व्योम serial8250_पढ़ो_अक्षर(काष्ठा uart_8250_port *up, अचिन्हित अक्षर lsr)
अणु
	काष्ठा uart_port *port = &up->port;
	अचिन्हित अक्षर ch;
	अक्षर flag = TTY_NORMAL;

	अगर (likely(lsr & UART_LSR_DR))
		ch = serial_in(up, UART_RX);
	अन्यथा
		/*
		 * Intel 82571 has a Serial Over Lan device that will
		 * set UART_LSR_BI without setting UART_LSR_DR when
		 * it receives a अवरोध. To aव्योम पढ़ोing from the
		 * receive buffer without UART_LSR_DR bit set, we
		 * just क्रमce the पढ़ो अक्षरacter to be 0
		 */
		ch = 0;

	port->icount.rx++;

	lsr |= up->lsr_saved_flags;
	up->lsr_saved_flags = 0;

	अगर (unlikely(lsr & UART_LSR_BRK_ERROR_BITS)) अणु
		अगर (lsr & UART_LSR_BI) अणु
			lsr &= ~(UART_LSR_FE | UART_LSR_PE);
			port->icount.brk++;
			/*
			 * We करो the SysRQ and SAK checking
			 * here because otherwise the अवरोध
			 * may get masked by ignore_status_mask
			 * or पढ़ो_status_mask.
			 */
			अगर (uart_handle_अवरोध(port))
				वापस;
		पूर्ण अन्यथा अगर (lsr & UART_LSR_PE)
			port->icount.parity++;
		अन्यथा अगर (lsr & UART_LSR_FE)
			port->icount.frame++;
		अगर (lsr & UART_LSR_OE)
			port->icount.overrun++;

		/*
		 * Mask off conditions which should be ignored.
		 */
		lsr &= port->पढ़ो_status_mask;

		अगर (lsr & UART_LSR_BI) अणु
			dev_dbg(port->dev, "handling break\n");
			flag = TTY_BREAK;
		पूर्ण अन्यथा अगर (lsr & UART_LSR_PE)
			flag = TTY_PARITY;
		अन्यथा अगर (lsr & UART_LSR_FE)
			flag = TTY_FRAME;
	पूर्ण
	अगर (uart_prepare_sysrq_अक्षर(port, ch))
		वापस;

	uart_insert_अक्षर(port, lsr, UART_LSR_OE, ch, flag);
पूर्ण
EXPORT_SYMBOL_GPL(serial8250_पढ़ो_अक्षर);

/*
 * serial8250_rx_अक्षरs: processes according to the passed in LSR
 * value, and वापसs the reमुख्यing LSR bits not handled
 * by this Rx routine.
 */
अचिन्हित अक्षर serial8250_rx_अक्षरs(काष्ठा uart_8250_port *up, अचिन्हित अक्षर lsr)
अणु
	काष्ठा uart_port *port = &up->port;
	पूर्णांक max_count = 256;

	करो अणु
		serial8250_पढ़ो_अक्षर(up, lsr);
		अगर (--max_count == 0)
			अवरोध;
		lsr = serial_in(up, UART_LSR);
	पूर्ण जबतक (lsr & (UART_LSR_DR | UART_LSR_BI));

	tty_flip_buffer_push(&port->state->port);
	वापस lsr;
पूर्ण
EXPORT_SYMBOL_GPL(serial8250_rx_अक्षरs);

व्योम serial8250_tx_अक्षरs(काष्ठा uart_8250_port *up)
अणु
	काष्ठा uart_port *port = &up->port;
	काष्ठा circ_buf *xmit = &port->state->xmit;
	पूर्णांक count;

	अगर (port->x_अक्षर) अणु
		serial_out(up, UART_TX, port->x_अक्षर);
		port->icount.tx++;
		port->x_अक्षर = 0;
		वापस;
	पूर्ण
	अगर (uart_tx_stopped(port)) अणु
		serial8250_stop_tx(port);
		वापस;
	पूर्ण
	अगर (uart_circ_empty(xmit)) अणु
		__stop_tx(up);
		वापस;
	पूर्ण

	count = up->tx_loadsz;
	करो अणु
		serial_out(up, UART_TX, xmit->buf[xmit->tail]);
		अगर (up->bugs & UART_BUG_TXRACE) अणु
			/*
			 * The Aspeed BMC भव UARTs have a bug where data
			 * may get stuck in the BMC's Tx FIFO from bursts of
			 * ग_लिखोs on the APB पूर्णांकerface.
			 *
			 * Delay back-to-back ग_लिखोs by a पढ़ो cycle to aव्योम
			 * stalling the VUART. Read a रेजिस्टर that won't have
			 * side-effects and discard the result.
			 */
			serial_in(up, UART_SCR);
		पूर्ण
		xmit->tail = (xmit->tail + 1) & (UART_XMIT_SIZE - 1);
		port->icount.tx++;
		अगर (uart_circ_empty(xmit))
			अवरोध;
		अगर ((up->capabilities & UART_CAP_HFIFO) &&
		    (serial_in(up, UART_LSR) & BOTH_EMPTY) != BOTH_EMPTY)
			अवरोध;
		/* The BCM2835 MINI UART THRE bit is really a not-full bit. */
		अगर ((up->capabilities & UART_CAP_MINI) &&
		    !(serial_in(up, UART_LSR) & UART_LSR_THRE))
			अवरोध;
	पूर्ण जबतक (--count > 0);

	अगर (uart_circ_अक्षरs_pending(xmit) < WAKEUP_CHARS)
		uart_ग_लिखो_wakeup(port);

	/*
	 * With RPM enabled, we have to रुको until the FIFO is empty beक्रमe the
	 * HW can go idle. So we get here once again with empty FIFO and disable
	 * the पूर्णांकerrupt and RPM in __stop_tx()
	 */
	अगर (uart_circ_empty(xmit) && !(up->capabilities & UART_CAP_RPM))
		__stop_tx(up);
पूर्ण
EXPORT_SYMBOL_GPL(serial8250_tx_अक्षरs);

/* Caller holds uart port lock */
अचिन्हित पूर्णांक serial8250_modem_status(काष्ठा uart_8250_port *up)
अणु
	काष्ठा uart_port *port = &up->port;
	अचिन्हित पूर्णांक status = serial_in(up, UART_MSR);

	status |= up->msr_saved_flags;
	up->msr_saved_flags = 0;
	अगर (status & UART_MSR_ANY_DELTA && up->ier & UART_IER_MSI &&
	    port->state != शून्य) अणु
		अगर (status & UART_MSR_TERI)
			port->icount.rng++;
		अगर (status & UART_MSR_DDSR)
			port->icount.dsr++;
		अगर (status & UART_MSR_DDCD)
			uart_handle_dcd_change(port, status & UART_MSR_DCD);
		अगर (status & UART_MSR_DCTS)
			uart_handle_cts_change(port, status & UART_MSR_CTS);

		wake_up_पूर्णांकerruptible(&port->state->port.delta_msr_रुको);
	पूर्ण

	वापस status;
पूर्ण
EXPORT_SYMBOL_GPL(serial8250_modem_status);

अटल bool handle_rx_dma(काष्ठा uart_8250_port *up, अचिन्हित पूर्णांक iir)
अणु
	चयन (iir & 0x3f) अणु
	हाल UART_IIR_RX_TIMEOUT:
		serial8250_rx_dma_flush(up);
		fallthrough;
	हाल UART_IIR_RLSI:
		वापस true;
	पूर्ण
	वापस up->dma->rx_dma(up);
पूर्ण

/*
 * This handles the पूर्णांकerrupt from one port.
 */
पूर्णांक serial8250_handle_irq(काष्ठा uart_port *port, अचिन्हित पूर्णांक iir)
अणु
	अचिन्हित अक्षर status;
	काष्ठा uart_8250_port *up = up_to_u8250p(port);
	bool skip_rx = false;

	अगर (iir & UART_IIR_NO_INT)
		वापस 0;

	spin_lock(&port->lock);

	status = serial_port_in(port, UART_LSR);

	/*
	 * If port is stopped and there are no error conditions in the
	 * FIFO, then करोn't drain the FIFO, as this may lead to TTY buffer
	 * overflow. Not servicing, RX FIFO would trigger स्वतः HW flow
	 * control when FIFO occupancy reaches preset threshold, thus
	 * halting RX. This only works when स्वतः HW flow control is
	 * available.
	 */
	अगर (!(status & (UART_LSR_FIFOE | UART_LSR_BRK_ERROR_BITS)) &&
	    (port->status & (UPSTAT_AUTOCTS | UPSTAT_AUTORTS)) &&
	    !(port->पढ़ो_status_mask & UART_LSR_DR))
		skip_rx = true;

	अगर (status & (UART_LSR_DR | UART_LSR_BI) && !skip_rx) अणु
		अगर (!up->dma || handle_rx_dma(up, iir))
			status = serial8250_rx_अक्षरs(up, status);
	पूर्ण
	serial8250_modem_status(up);
	अगर ((!up->dma || up->dma->tx_err) && (status & UART_LSR_THRE) &&
		(up->ier & UART_IER_THRI))
		serial8250_tx_अक्षरs(up);

	uart_unlock_and_check_sysrq(port);

	वापस 1;
पूर्ण
EXPORT_SYMBOL_GPL(serial8250_handle_irq);

अटल पूर्णांक serial8250_शेष_handle_irq(काष्ठा uart_port *port)
अणु
	काष्ठा uart_8250_port *up = up_to_u8250p(port);
	अचिन्हित पूर्णांक iir;
	पूर्णांक ret;

	serial8250_rpm_get(up);

	iir = serial_port_in(port, UART_IIR);
	ret = serial8250_handle_irq(port, iir);

	serial8250_rpm_put(up);
	वापस ret;
पूर्ण

/*
 * Newer 16550 compatible parts such as the SC16C650 & Altera 16550 Soft IP
 * have a programmable TX threshold that triggers the THRE पूर्णांकerrupt in
 * the IIR रेजिस्टर. In this हाल, the THRE पूर्णांकerrupt indicates the FIFO
 * has space available. Load it up with tx_loadsz bytes.
 */
अटल पूर्णांक serial8250_tx_threshold_handle_irq(काष्ठा uart_port *port)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक iir = serial_port_in(port, UART_IIR);

	/* TX Threshold IRQ triggered so load up FIFO */
	अगर ((iir & UART_IIR_ID) == UART_IIR_THRI) अणु
		काष्ठा uart_8250_port *up = up_to_u8250p(port);

		spin_lock_irqsave(&port->lock, flags);
		serial8250_tx_अक्षरs(up);
		spin_unlock_irqrestore(&port->lock, flags);
	पूर्ण

	iir = serial_port_in(port, UART_IIR);
	वापस serial8250_handle_irq(port, iir);
पूर्ण

अटल अचिन्हित पूर्णांक serial8250_tx_empty(काष्ठा uart_port *port)
अणु
	काष्ठा uart_8250_port *up = up_to_u8250p(port);
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक lsr;

	serial8250_rpm_get(up);

	spin_lock_irqsave(&port->lock, flags);
	lsr = serial_port_in(port, UART_LSR);
	up->lsr_saved_flags |= lsr & LSR_SAVE_FLAGS;
	spin_unlock_irqrestore(&port->lock, flags);

	serial8250_rpm_put(up);

	वापस (lsr & BOTH_EMPTY) == BOTH_EMPTY ? TIOCSER_TEMT : 0;
पूर्ण

अचिन्हित पूर्णांक serial8250_करो_get_mctrl(काष्ठा uart_port *port)
अणु
	काष्ठा uart_8250_port *up = up_to_u8250p(port);
	अचिन्हित पूर्णांक status;
	अचिन्हित पूर्णांक val;

	serial8250_rpm_get(up);
	status = serial8250_modem_status(up);
	serial8250_rpm_put(up);

	val = serial8250_MSR_to_TIOCM(status);
	अगर (up->gpios)
		वापस mctrl_gpio_get(up->gpios, &val);

	वापस val;
पूर्ण
EXPORT_SYMBOL_GPL(serial8250_करो_get_mctrl);

अटल अचिन्हित पूर्णांक serial8250_get_mctrl(काष्ठा uart_port *port)
अणु
	अगर (port->get_mctrl)
		वापस port->get_mctrl(port);
	वापस serial8250_करो_get_mctrl(port);
पूर्ण

व्योम serial8250_करो_set_mctrl(काष्ठा uart_port *port, अचिन्हित पूर्णांक mctrl)
अणु
	काष्ठा uart_8250_port *up = up_to_u8250p(port);
	अचिन्हित अक्षर mcr;

	अगर (port->rs485.flags & SER_RS485_ENABLED) अणु
		अगर (serial8250_in_MCR(up) & UART_MCR_RTS)
			mctrl |= TIOCM_RTS;
		अन्यथा
			mctrl &= ~TIOCM_RTS;
	पूर्ण

	mcr = serial8250_TIOCM_to_MCR(mctrl);

	mcr = (mcr & up->mcr_mask) | up->mcr_क्रमce | up->mcr;

	serial8250_out_MCR(up, mcr);
पूर्ण
EXPORT_SYMBOL_GPL(serial8250_करो_set_mctrl);

अटल व्योम serial8250_set_mctrl(काष्ठा uart_port *port, अचिन्हित पूर्णांक mctrl)
अणु
	अगर (port->set_mctrl)
		port->set_mctrl(port, mctrl);
	अन्यथा
		serial8250_करो_set_mctrl(port, mctrl);
पूर्ण

अटल व्योम serial8250_अवरोध_ctl(काष्ठा uart_port *port, पूर्णांक अवरोध_state)
अणु
	काष्ठा uart_8250_port *up = up_to_u8250p(port);
	अचिन्हित दीर्घ flags;

	serial8250_rpm_get(up);
	spin_lock_irqsave(&port->lock, flags);
	अगर (अवरोध_state == -1)
		up->lcr |= UART_LCR_SBC;
	अन्यथा
		up->lcr &= ~UART_LCR_SBC;
	serial_port_out(port, UART_LCR, up->lcr);
	spin_unlock_irqrestore(&port->lock, flags);
	serial8250_rpm_put(up);
पूर्ण

/*
 *	Wait क्रम transmitter & holding रेजिस्टर to empty
 */
अटल व्योम रुको_क्रम_xmitr(काष्ठा uart_8250_port *up, पूर्णांक bits)
अणु
	अचिन्हित पूर्णांक status, पंचांगout = 10000;

	/* Wait up to 10ms क्रम the अक्षरacter(s) to be sent. */
	क्रम (;;) अणु
		status = serial_in(up, UART_LSR);

		up->lsr_saved_flags |= status & LSR_SAVE_FLAGS;

		अगर ((status & bits) == bits)
			अवरोध;
		अगर (--पंचांगout == 0)
			अवरोध;
		udelay(1);
		touch_nmi_watchकरोg();
	पूर्ण

	/* Wait up to 1s क्रम flow control अगर necessary */
	अगर (up->port.flags & UPF_CONS_FLOW) अणु
		क्रम (पंचांगout = 1000000; पंचांगout; पंचांगout--) अणु
			अचिन्हित पूर्णांक msr = serial_in(up, UART_MSR);
			up->msr_saved_flags |= msr & MSR_SAVE_FLAGS;
			अगर (msr & UART_MSR_CTS)
				अवरोध;
			udelay(1);
			touch_nmi_watchकरोg();
		पूर्ण
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_CONSOLE_POLL
/*
 * Console polling routines क्रम writing and पढ़ोing from the uart जबतक
 * in an पूर्णांकerrupt or debug context.
 */

अटल पूर्णांक serial8250_get_poll_अक्षर(काष्ठा uart_port *port)
अणु
	काष्ठा uart_8250_port *up = up_to_u8250p(port);
	अचिन्हित अक्षर lsr;
	पूर्णांक status;

	serial8250_rpm_get(up);

	lsr = serial_port_in(port, UART_LSR);

	अगर (!(lsr & UART_LSR_DR)) अणु
		status = NO_POLL_CHAR;
		जाओ out;
	पूर्ण

	status = serial_port_in(port, UART_RX);
out:
	serial8250_rpm_put(up);
	वापस status;
पूर्ण


अटल व्योम serial8250_put_poll_अक्षर(काष्ठा uart_port *port,
			 अचिन्हित अक्षर c)
अणु
	अचिन्हित पूर्णांक ier;
	काष्ठा uart_8250_port *up = up_to_u8250p(port);

	serial8250_rpm_get(up);
	/*
	 *	First save the IER then disable the पूर्णांकerrupts
	 */
	ier = serial_port_in(port, UART_IER);
	अगर (up->capabilities & UART_CAP_UUE)
		serial_port_out(port, UART_IER, UART_IER_UUE);
	अन्यथा
		serial_port_out(port, UART_IER, 0);

	रुको_क्रम_xmitr(up, BOTH_EMPTY);
	/*
	 *	Send the अक्षरacter out.
	 */
	serial_port_out(port, UART_TX, c);

	/*
	 *	Finally, रुको क्रम transmitter to become empty
	 *	and restore the IER
	 */
	रुको_क्रम_xmitr(up, BOTH_EMPTY);
	serial_port_out(port, UART_IER, ier);
	serial8250_rpm_put(up);
पूर्ण

#पूर्ण_अगर /* CONFIG_CONSOLE_POLL */

पूर्णांक serial8250_करो_startup(काष्ठा uart_port *port)
अणु
	काष्ठा uart_8250_port *up = up_to_u8250p(port);
	अचिन्हित दीर्घ flags;
	अचिन्हित अक्षर lsr, iir;
	पूर्णांक retval;

	अगर (!port->fअगरosize)
		port->fअगरosize = uart_config[port->type].fअगरo_size;
	अगर (!up->tx_loadsz)
		up->tx_loadsz = uart_config[port->type].tx_loadsz;
	अगर (!up->capabilities)
		up->capabilities = uart_config[port->type].flags;
	up->mcr = 0;

	अगर (port->iotype != up->cur_iotype)
		set_io_from_upio(port);

	serial8250_rpm_get(up);
	अगर (port->type == PORT_16C950) अणु
		/* Wake up and initialize UART */
		up->acr = 0;
		serial_port_out(port, UART_LCR, UART_LCR_CONF_MODE_B);
		serial_port_out(port, UART_EFR, UART_EFR_ECB);
		serial_port_out(port, UART_IER, 0);
		serial_port_out(port, UART_LCR, 0);
		serial_icr_ग_लिखो(up, UART_CSR, 0); /* Reset the UART */
		serial_port_out(port, UART_LCR, UART_LCR_CONF_MODE_B);
		serial_port_out(port, UART_EFR, UART_EFR_ECB);
		serial_port_out(port, UART_LCR, 0);
	पूर्ण

	अगर (port->type == PORT_DA830) अणु
		/* Reset the port */
		serial_port_out(port, UART_IER, 0);
		serial_port_out(port, UART_DA830_PWREMU_MGMT, 0);
		mdelay(10);

		/* Enable Tx, Rx and मुक्त run mode */
		serial_port_out(port, UART_DA830_PWREMU_MGMT,
				UART_DA830_PWREMU_MGMT_UTRST |
				UART_DA830_PWREMU_MGMT_URRST |
				UART_DA830_PWREMU_MGMT_FREE);
	पूर्ण

	अगर (port->type == PORT_NPCM) अणु
		/*
		 * Nuvoton calls the scratch रेजिस्टर 'UART_TOR' (समयout
		 * रेजिस्टर). Enable it, and set TIOC (समयout पूर्णांकerrupt
		 * comparator) to be 0x20 क्रम correct operation.
		 */
		serial_port_out(port, UART_NPCM_TOR, UART_NPCM_TOIE | 0x20);
	पूर्ण

#अगर_घोषित CONFIG_SERIAL_8250_RSA
	/*
	 * If this is an RSA port, see अगर we can kick it up to the
	 * higher speed घड़ी.
	 */
	enable_rsa(up);
#पूर्ण_अगर

	/*
	 * Clear the FIFO buffers and disable them.
	 * (they will be reenabled in set_termios())
	 */
	serial8250_clear_fअगरos(up);

	/*
	 * Clear the पूर्णांकerrupt रेजिस्टरs.
	 */
	serial_port_in(port, UART_LSR);
	serial_port_in(port, UART_RX);
	serial_port_in(port, UART_IIR);
	serial_port_in(port, UART_MSR);

	/*
	 * At this poपूर्णांक, there's no way the LSR could still be 0xff;
	 * अगर it is, then bail out, because there's likely no UART
	 * here.
	 */
	अगर (!(port->flags & UPF_BUGGY_UART) &&
	    (serial_port_in(port, UART_LSR) == 0xff)) अणु
		dev_info_ratelimited(port->dev, "LSR safety check engaged!\n");
		retval = -ENODEV;
		जाओ out;
	पूर्ण

	/*
	 * For a XR16C850, we need to set the trigger levels
	 */
	अगर (port->type == PORT_16850) अणु
		अचिन्हित अक्षर fctr;

		serial_out(up, UART_LCR, UART_LCR_CONF_MODE_B);

		fctr = serial_in(up, UART_FCTR) & ~(UART_FCTR_RX|UART_FCTR_TX);
		serial_port_out(port, UART_FCTR,
				fctr | UART_FCTR_TRGD | UART_FCTR_RX);
		serial_port_out(port, UART_TRG, UART_TRG_96);
		serial_port_out(port, UART_FCTR,
				fctr | UART_FCTR_TRGD | UART_FCTR_TX);
		serial_port_out(port, UART_TRG, UART_TRG_96);

		serial_port_out(port, UART_LCR, 0);
	पूर्ण

	/*
	 * For the Altera 16550 variants, set TX threshold trigger level.
	 */
	अगर (((port->type == PORT_ALTR_16550_F32) ||
	     (port->type == PORT_ALTR_16550_F64) ||
	     (port->type == PORT_ALTR_16550_F128)) && (port->fअगरosize > 1)) अणु
		/* Bounds checking of TX threshold (valid 0 to fअगरosize-2) */
		अगर ((up->tx_loadsz < 2) || (up->tx_loadsz > port->fअगरosize)) अणु
			dev_err(port->dev, "TX FIFO Threshold errors, skipping\n");
		पूर्ण अन्यथा अणु
			serial_port_out(port, UART_ALTR_AFR,
					UART_ALTR_EN_TXFIFO_LW);
			serial_port_out(port, UART_ALTR_TX_LOW,
					port->fअगरosize - up->tx_loadsz);
			port->handle_irq = serial8250_tx_threshold_handle_irq;
		पूर्ण
	पूर्ण

	/* Check अगर we need to have shared IRQs */
	अगर (port->irq && (up->port.flags & UPF_SHARE_IRQ))
		up->port.irqflags |= IRQF_SHARED;

	अगर (port->irq && !(up->port.flags & UPF_NO_THRE_TEST)) अणु
		अचिन्हित अक्षर iir1;

		अगर (port->irqflags & IRQF_SHARED)
			disable_irq_nosync(port->irq);

		/*
		 * Test क्रम UARTs that करो not reनिश्चित THRE when the
		 * transmitter is idle and the पूर्णांकerrupt has alपढ़ोy
		 * been cleared.  Real 16550s should always reनिश्चित
		 * this पूर्णांकerrupt whenever the transmitter is idle and
		 * the पूर्णांकerrupt is enabled.  Delays are necessary to
		 * allow रेजिस्टर changes to become visible.
		 */
		spin_lock_irqsave(&port->lock, flags);

		रुको_क्रम_xmitr(up, UART_LSR_THRE);
		serial_port_out_sync(port, UART_IER, UART_IER_THRI);
		udelay(1); /* allow THRE to set */
		iir1 = serial_port_in(port, UART_IIR);
		serial_port_out(port, UART_IER, 0);
		serial_port_out_sync(port, UART_IER, UART_IER_THRI);
		udelay(1); /* allow a working UART समय to re-निश्चित THRE */
		iir = serial_port_in(port, UART_IIR);
		serial_port_out(port, UART_IER, 0);

		spin_unlock_irqrestore(&port->lock, flags);

		अगर (port->irqflags & IRQF_SHARED)
			enable_irq(port->irq);

		/*
		 * If the पूर्णांकerrupt is not reनिश्चितed, or we otherwise
		 * करोn't trust the iir, setup a समयr to kick the UART
		 * on a regular basis.
		 */
		अगर ((!(iir1 & UART_IIR_NO_INT) && (iir & UART_IIR_NO_INT)) ||
		    up->port.flags & UPF_BUG_THRE) अणु
			up->bugs |= UART_BUG_THRE;
		पूर्ण
	पूर्ण

	retval = up->ops->setup_irq(up);
	अगर (retval)
		जाओ out;

	/*
	 * Now, initialize the UART
	 */
	serial_port_out(port, UART_LCR, UART_LCR_WLEN8);

	spin_lock_irqsave(&port->lock, flags);
	अगर (up->port.flags & UPF_FOURPORT) अणु
		अगर (!up->port.irq)
			up->port.mctrl |= TIOCM_OUT1;
	पूर्ण अन्यथा
		/*
		 * Most PC uarts need OUT2 उठाओd to enable पूर्णांकerrupts.
		 */
		अगर (port->irq)
			up->port.mctrl |= TIOCM_OUT2;

	serial8250_set_mctrl(port, port->mctrl);

	/*
	 * Serial over Lan (SoL) hack:
	 * Intel 8257x Gigabit ethernet chips have a 16550 emulation, to be
	 * used क्रम Serial Over Lan.  Those chips take a दीर्घer समय than a
	 * normal serial device to संकेतize that a transmission data was
	 * queued. Due to that, the above test generally fails. One solution
	 * would be to delay the पढ़ोing of iir. However, this is not
	 * reliable, since the समयout is variable. So, let's just don't
	 * test अगर we receive TX irq.  This way, we'll never enable
	 * UART_BUG_TXEN.
	 */
	अगर (up->port.quirks & UPQ_NO_TXEN_TEST)
		जाओ करोnt_test_tx_en;

	/*
	 * Do a quick test to see अगर we receive an पूर्णांकerrupt when we enable
	 * the TX irq.
	 */
	serial_port_out(port, UART_IER, UART_IER_THRI);
	lsr = serial_port_in(port, UART_LSR);
	iir = serial_port_in(port, UART_IIR);
	serial_port_out(port, UART_IER, 0);

	अगर (lsr & UART_LSR_TEMT && iir & UART_IIR_NO_INT) अणु
		अगर (!(up->bugs & UART_BUG_TXEN)) अणु
			up->bugs |= UART_BUG_TXEN;
			dev_dbg(port->dev, "enabling bad tx status workarounds\n");
		पूर्ण
	पूर्ण अन्यथा अणु
		up->bugs &= ~UART_BUG_TXEN;
	पूर्ण

करोnt_test_tx_en:
	spin_unlock_irqrestore(&port->lock, flags);

	/*
	 * Clear the पूर्णांकerrupt रेजिस्टरs again क्रम luck, and clear the
	 * saved flags to aव्योम getting false values from polling
	 * routines or the previous session.
	 */
	serial_port_in(port, UART_LSR);
	serial_port_in(port, UART_RX);
	serial_port_in(port, UART_IIR);
	serial_port_in(port, UART_MSR);
	up->lsr_saved_flags = 0;
	up->msr_saved_flags = 0;

	/*
	 * Request DMA channels क्रम both RX and TX.
	 */
	अगर (up->dma) अणु
		स्थिर अक्षर *msg = शून्य;

		अगर (uart_console(port))
			msg = "forbid DMA for kernel console";
		अन्यथा अगर (serial8250_request_dma(up))
			msg = "failed to request DMA";
		अगर (msg) अणु
			dev_warn_ratelimited(port->dev, "%s\n", msg);
			up->dma = शून्य;
		पूर्ण
	पूर्ण

	/*
	 * Set the IER shaकरोw क्रम rx पूर्णांकerrupts but defer actual पूर्णांकerrupt
	 * enable until after the FIFOs are enabled; otherwise, an alपढ़ोy-
	 * active sender can swamp the पूर्णांकerrupt handler with "too much work".
	 */
	up->ier = UART_IER_RLSI | UART_IER_RDI;

	अगर (port->flags & UPF_FOURPORT) अणु
		अचिन्हित पूर्णांक icp;
		/*
		 * Enable पूर्णांकerrupts on the AST Fourport board
		 */
		icp = (port->iobase & 0xfe0) | 0x01f;
		outb_p(0x80, icp);
		inb_p(icp);
	पूर्ण
	retval = 0;
out:
	serial8250_rpm_put(up);
	वापस retval;
पूर्ण
EXPORT_SYMBOL_GPL(serial8250_करो_startup);

अटल पूर्णांक serial8250_startup(काष्ठा uart_port *port)
अणु
	अगर (port->startup)
		वापस port->startup(port);
	वापस serial8250_करो_startup(port);
पूर्ण

व्योम serial8250_करो_shutकरोwn(काष्ठा uart_port *port)
अणु
	काष्ठा uart_8250_port *up = up_to_u8250p(port);
	अचिन्हित दीर्घ flags;

	serial8250_rpm_get(up);
	/*
	 * Disable पूर्णांकerrupts from this port
	 */
	spin_lock_irqsave(&port->lock, flags);
	up->ier = 0;
	serial_port_out(port, UART_IER, 0);
	spin_unlock_irqrestore(&port->lock, flags);

	synchronize_irq(port->irq);

	अगर (up->dma)
		serial8250_release_dma(up);

	spin_lock_irqsave(&port->lock, flags);
	अगर (port->flags & UPF_FOURPORT) अणु
		/* reset पूर्णांकerrupts on the AST Fourport board */
		inb((port->iobase & 0xfe0) | 0x1f);
		port->mctrl |= TIOCM_OUT1;
	पूर्ण अन्यथा
		port->mctrl &= ~TIOCM_OUT2;

	serial8250_set_mctrl(port, port->mctrl);
	spin_unlock_irqrestore(&port->lock, flags);

	/*
	 * Disable अवरोध condition and FIFOs
	 */
	serial_port_out(port, UART_LCR,
			serial_port_in(port, UART_LCR) & ~UART_LCR_SBC);
	serial8250_clear_fअगरos(up);

#अगर_घोषित CONFIG_SERIAL_8250_RSA
	/*
	 * Reset the RSA board back to 115kbps compat mode.
	 */
	disable_rsa(up);
#पूर्ण_अगर

	/*
	 * Read data port to reset things, and then unlink from
	 * the IRQ chain.
	 */
	serial_port_in(port, UART_RX);
	serial8250_rpm_put(up);

	up->ops->release_irq(up);
पूर्ण
EXPORT_SYMBOL_GPL(serial8250_करो_shutकरोwn);

अटल व्योम serial8250_shutकरोwn(काष्ठा uart_port *port)
अणु
	अगर (port->shutकरोwn)
		port->shutकरोwn(port);
	अन्यथा
		serial8250_करो_shutकरोwn(port);
पूर्ण

/* Nuvoton NPCM UARTs have a custom भागisor calculation */
अटल अचिन्हित पूर्णांक npcm_get_भागisor(काष्ठा uart_8250_port *up,
		अचिन्हित पूर्णांक baud)
अणु
	काष्ठा uart_port *port = &up->port;

	वापस DIV_ROUND_CLOSEST(port->uartclk, 16 * baud + 2) - 2;
पूर्ण

अटल अचिन्हित पूर्णांक serial8250_करो_get_भागisor(काष्ठा uart_port *port,
					      अचिन्हित पूर्णांक baud,
					      अचिन्हित पूर्णांक *frac)
अणु
	काष्ठा uart_8250_port *up = up_to_u8250p(port);
	अचिन्हित पूर्णांक quot;

	/*
	 * Handle magic भागisors क्रम baud rates above baud_base on
	 * SMSC SuperIO chips.
	 *
	 */
	अगर ((port->flags & UPF_MAGIC_MULTIPLIER) &&
	    baud == (port->uartclk/4))
		quot = 0x8001;
	अन्यथा अगर ((port->flags & UPF_MAGIC_MULTIPLIER) &&
		 baud == (port->uartclk/8))
		quot = 0x8002;
	अन्यथा अगर (up->port.type == PORT_NPCM)
		quot = npcm_get_भागisor(up, baud);
	अन्यथा
		quot = uart_get_भागisor(port, baud);

	/*
	 * Oxक्रमd Semi 952 rev B workaround
	 */
	अगर (up->bugs & UART_BUG_QUOT && (quot & 0xff) == 0)
		quot++;

	वापस quot;
पूर्ण

अटल अचिन्हित पूर्णांक serial8250_get_भागisor(काष्ठा uart_port *port,
					   अचिन्हित पूर्णांक baud,
					   अचिन्हित पूर्णांक *frac)
अणु
	अगर (port->get_भागisor)
		वापस port->get_भागisor(port, baud, frac);

	वापस serial8250_करो_get_भागisor(port, baud, frac);
पूर्ण

अटल अचिन्हित अक्षर serial8250_compute_lcr(काष्ठा uart_8250_port *up,
					    tcflag_t c_cflag)
अणु
	अचिन्हित अक्षर cval;

	चयन (c_cflag & CSIZE) अणु
	हाल CS5:
		cval = UART_LCR_WLEN5;
		अवरोध;
	हाल CS6:
		cval = UART_LCR_WLEN6;
		अवरोध;
	हाल CS7:
		cval = UART_LCR_WLEN7;
		अवरोध;
	शेष:
	हाल CS8:
		cval = UART_LCR_WLEN8;
		अवरोध;
	पूर्ण

	अगर (c_cflag & CSTOPB)
		cval |= UART_LCR_STOP;
	अगर (c_cflag & PARENB) अणु
		cval |= UART_LCR_PARITY;
		अगर (up->bugs & UART_BUG_PARITY)
			up->fअगरo_bug = true;
	पूर्ण
	अगर (!(c_cflag & PARODD))
		cval |= UART_LCR_EPAR;
#अगर_घोषित CMSPAR
	अगर (c_cflag & CMSPAR)
		cval |= UART_LCR_SPAR;
#पूर्ण_अगर

	वापस cval;
पूर्ण

व्योम serial8250_करो_set_भागisor(काष्ठा uart_port *port, अचिन्हित पूर्णांक baud,
			       अचिन्हित पूर्णांक quot, अचिन्हित पूर्णांक quot_frac)
अणु
	काष्ठा uart_8250_port *up = up_to_u8250p(port);

	/* Workaround to enable 115200 baud on OMAP1510 पूर्णांकernal ports */
	अगर (is_omap1510_8250(up)) अणु
		अगर (baud == 115200) अणु
			quot = 1;
			serial_port_out(port, UART_OMAP_OSC_12M_SEL, 1);
		पूर्ण अन्यथा
			serial_port_out(port, UART_OMAP_OSC_12M_SEL, 0);
	पूर्ण

	/*
	 * For NatSemi, चयन to bank 2 not bank 1, to aव्योम resetting EXCR2,
	 * otherwise just set DLAB
	 */
	अगर (up->capabilities & UART_NATSEMI)
		serial_port_out(port, UART_LCR, 0xe0);
	अन्यथा
		serial_port_out(port, UART_LCR, up->lcr | UART_LCR_DLAB);

	serial_dl_ग_लिखो(up, quot);
पूर्ण
EXPORT_SYMBOL_GPL(serial8250_करो_set_भागisor);

अटल व्योम serial8250_set_भागisor(काष्ठा uart_port *port, अचिन्हित पूर्णांक baud,
				   अचिन्हित पूर्णांक quot, अचिन्हित पूर्णांक quot_frac)
अणु
	अगर (port->set_भागisor)
		port->set_भागisor(port, baud, quot, quot_frac);
	अन्यथा
		serial8250_करो_set_भागisor(port, baud, quot, quot_frac);
पूर्ण

अटल अचिन्हित पूर्णांक serial8250_get_baud_rate(काष्ठा uart_port *port,
					     काष्ठा ktermios *termios,
					     काष्ठा ktermios *old)
अणु
	अचिन्हित पूर्णांक tolerance = port->uartclk / 100;

	/*
	 * Ask the core to calculate the भागisor क्रम us.
	 * Allow 1% tolerance at the upper limit so uart clks marginally
	 * slower than nominal still match standard baud rates without
	 * causing transmission errors.
	 */
	वापस uart_get_baud_rate(port, termios, old,
				  port->uartclk / 16 / UART_DIV_MAX,
				  (port->uartclk + tolerance) / 16);
पूर्ण

/*
 * Note in order to aव्योम the tty port mutex deadlock करोn't use the next method
 * within the uart port callbacks. Primarily it's supposed to be utilized to
 * handle a sudden reference घड़ी rate change.
 */
व्योम serial8250_update_uartclk(काष्ठा uart_port *port, अचिन्हित पूर्णांक uartclk)
अणु
	काष्ठा uart_8250_port *up = up_to_u8250p(port);
	अचिन्हित पूर्णांक baud, quot, frac = 0;
	काष्ठा ktermios *termios;
	अचिन्हित दीर्घ flags;

	mutex_lock(&port->state->port.mutex);

	अगर (port->uartclk == uartclk)
		जाओ out_lock;

	port->uartclk = uartclk;

	अगर (!tty_port_initialized(&port->state->port))
		जाओ out_lock;

	termios = &port->state->port.tty->termios;

	baud = serial8250_get_baud_rate(port, termios, शून्य);
	quot = serial8250_get_भागisor(port, baud, &frac);

	serial8250_rpm_get(up);
	spin_lock_irqsave(&port->lock, flags);

	uart_update_समयout(port, termios->c_cflag, baud);

	serial8250_set_भागisor(port, baud, quot, frac);
	serial_port_out(port, UART_LCR, up->lcr);

	spin_unlock_irqrestore(&port->lock, flags);
	serial8250_rpm_put(up);

out_lock:
	mutex_unlock(&port->state->port.mutex);
पूर्ण
EXPORT_SYMBOL_GPL(serial8250_update_uartclk);

व्योम
serial8250_करो_set_termios(काष्ठा uart_port *port, काष्ठा ktermios *termios,
			  काष्ठा ktermios *old)
अणु
	काष्ठा uart_8250_port *up = up_to_u8250p(port);
	अचिन्हित अक्षर cval;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक baud, quot, frac = 0;

	अगर (up->capabilities & UART_CAP_MINI) अणु
		termios->c_cflag &= ~(CSTOPB | PARENB | PARODD | CMSPAR);
		अगर ((termios->c_cflag & CSIZE) == CS5 ||
		    (termios->c_cflag & CSIZE) == CS6)
			termios->c_cflag = (termios->c_cflag & ~CSIZE) | CS7;
	पूर्ण
	cval = serial8250_compute_lcr(up, termios->c_cflag);

	baud = serial8250_get_baud_rate(port, termios, old);
	quot = serial8250_get_भागisor(port, baud, &frac);

	/*
	 * Ok, we're now changing the port state.  Do it with
	 * पूर्णांकerrupts disabled.
	 */
	serial8250_rpm_get(up);
	spin_lock_irqsave(&port->lock, flags);

	up->lcr = cval;					/* Save computed LCR */

	अगर (up->capabilities & UART_CAP_FIFO && port->fअगरosize > 1) अणु
		/* NOTE: If fअगरo_bug is not set, a user can set RX_trigger. */
		अगर ((baud < 2400 && !up->dma) || up->fअगरo_bug) अणु
			up->fcr &= ~UART_FCR_TRIGGER_MASK;
			up->fcr |= UART_FCR_TRIGGER_1;
		पूर्ण
	पूर्ण

	/*
	 * MCR-based स्वतः flow control.  When AFE is enabled, RTS will be
	 * deनिश्चितed when the receive FIFO contains more अक्षरacters than
	 * the trigger, or the MCR RTS bit is cleared.
	 */
	अगर (up->capabilities & UART_CAP_AFE) अणु
		up->mcr &= ~UART_MCR_AFE;
		अगर (termios->c_cflag & CRTSCTS)
			up->mcr |= UART_MCR_AFE;
	पूर्ण

	/*
	 * Update the per-port समयout.
	 */
	uart_update_समयout(port, termios->c_cflag, baud);

	port->पढ़ो_status_mask = UART_LSR_OE | UART_LSR_THRE | UART_LSR_DR;
	अगर (termios->c_अगरlag & INPCK)
		port->पढ़ो_status_mask |= UART_LSR_FE | UART_LSR_PE;
	अगर (termios->c_अगरlag & (IGNBRK | BRKINT | PARMRK))
		port->पढ़ो_status_mask |= UART_LSR_BI;

	/*
	 * Characteres to ignore
	 */
	port->ignore_status_mask = 0;
	अगर (termios->c_अगरlag & IGNPAR)
		port->ignore_status_mask |= UART_LSR_PE | UART_LSR_FE;
	अगर (termios->c_अगरlag & IGNBRK) अणु
		port->ignore_status_mask |= UART_LSR_BI;
		/*
		 * If we're ignoring parity and अवरोध indicators,
		 * ignore overruns too (क्रम real raw support).
		 */
		अगर (termios->c_अगरlag & IGNPAR)
			port->ignore_status_mask |= UART_LSR_OE;
	पूर्ण

	/*
	 * ignore all अक्षरacters अगर CREAD is not set
	 */
	अगर ((termios->c_cflag & CREAD) == 0)
		port->ignore_status_mask |= UART_LSR_DR;

	/*
	 * CTS flow control flag and modem status पूर्णांकerrupts
	 */
	up->ier &= ~UART_IER_MSI;
	अगर (!(up->bugs & UART_BUG_NOMSR) &&
			UART_ENABLE_MS(&up->port, termios->c_cflag))
		up->ier |= UART_IER_MSI;
	अगर (up->capabilities & UART_CAP_UUE)
		up->ier |= UART_IER_UUE;
	अगर (up->capabilities & UART_CAP_RTOIE)
		up->ier |= UART_IER_RTOIE;

	serial_port_out(port, UART_IER, up->ier);

	अगर (up->capabilities & UART_CAP_EFR) अणु
		अचिन्हित अक्षर efr = 0;
		/*
		 * TI16C752/Startech hardware flow control.  FIXME:
		 * - TI16C752 requires control thresholds to be set.
		 * - UART_MCR_RTS is ineffective अगर स्वतः-RTS mode is enabled.
		 */
		अगर (termios->c_cflag & CRTSCTS)
			efr |= UART_EFR_CTS;

		serial_port_out(port, UART_LCR, UART_LCR_CONF_MODE_B);
		अगर (port->flags & UPF_EXAR_EFR)
			serial_port_out(port, UART_XR_EFR, efr);
		अन्यथा
			serial_port_out(port, UART_EFR, efr);
	पूर्ण

	serial8250_set_भागisor(port, baud, quot, frac);

	/*
	 * LCR DLAB must be set to enable 64-byte FIFO mode. If the FCR
	 * is written without DLAB set, this mode will be disabled.
	 */
	अगर (port->type == PORT_16750)
		serial_port_out(port, UART_FCR, up->fcr);

	serial_port_out(port, UART_LCR, up->lcr);	/* reset DLAB */
	अगर (port->type != PORT_16750) अणु
		/* emulated UARTs (Lucent Venus 167x) need two steps */
		अगर (up->fcr & UART_FCR_ENABLE_FIFO)
			serial_port_out(port, UART_FCR, UART_FCR_ENABLE_FIFO);
		serial_port_out(port, UART_FCR, up->fcr);	/* set fcr */
	पूर्ण
	serial8250_set_mctrl(port, port->mctrl);
	spin_unlock_irqrestore(&port->lock, flags);
	serial8250_rpm_put(up);

	/* Don't reग_लिखो B0 */
	अगर (tty_termios_baud_rate(termios))
		tty_termios_encode_baud_rate(termios, baud, baud);
पूर्ण
EXPORT_SYMBOL(serial8250_करो_set_termios);

अटल व्योम
serial8250_set_termios(काष्ठा uart_port *port, काष्ठा ktermios *termios,
		       काष्ठा ktermios *old)
अणु
	अगर (port->set_termios)
		port->set_termios(port, termios, old);
	अन्यथा
		serial8250_करो_set_termios(port, termios, old);
पूर्ण

व्योम serial8250_करो_set_ldisc(काष्ठा uart_port *port, काष्ठा ktermios *termios)
अणु
	अगर (termios->c_line == N_PPS) अणु
		port->flags |= UPF_HARDPPS_CD;
		spin_lock_irq(&port->lock);
		serial8250_enable_ms(port);
		spin_unlock_irq(&port->lock);
	पूर्ण अन्यथा अणु
		port->flags &= ~UPF_HARDPPS_CD;
		अगर (!UART_ENABLE_MS(port, termios->c_cflag)) अणु
			spin_lock_irq(&port->lock);
			serial8250_disable_ms(port);
			spin_unlock_irq(&port->lock);
		पूर्ण
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(serial8250_करो_set_ldisc);

अटल व्योम
serial8250_set_ldisc(काष्ठा uart_port *port, काष्ठा ktermios *termios)
अणु
	अगर (port->set_ldisc)
		port->set_ldisc(port, termios);
	अन्यथा
		serial8250_करो_set_ldisc(port, termios);
पूर्ण

व्योम serial8250_करो_pm(काष्ठा uart_port *port, अचिन्हित पूर्णांक state,
		      अचिन्हित पूर्णांक oldstate)
अणु
	काष्ठा uart_8250_port *p = up_to_u8250p(port);

	serial8250_set_sleep(p, state != 0);
पूर्ण
EXPORT_SYMBOL(serial8250_करो_pm);

अटल व्योम
serial8250_pm(काष्ठा uart_port *port, अचिन्हित पूर्णांक state,
	      अचिन्हित पूर्णांक oldstate)
अणु
	अगर (port->pm)
		port->pm(port, state, oldstate);
	अन्यथा
		serial8250_करो_pm(port, state, oldstate);
पूर्ण

अटल अचिन्हित पूर्णांक serial8250_port_size(काष्ठा uart_8250_port *pt)
अणु
	अगर (pt->port.mapsize)
		वापस pt->port.mapsize;
	अगर (pt->port.iotype == UPIO_AU) अणु
		अगर (pt->port.type == PORT_RT2880)
			वापस 0x100;
		वापस 0x1000;
	पूर्ण
	अगर (is_omap1_8250(pt))
		वापस 0x16 << pt->port.regshअगरt;

	वापस 8 << pt->port.regshअगरt;
पूर्ण

/*
 * Resource handling.
 */
अटल पूर्णांक serial8250_request_std_resource(काष्ठा uart_8250_port *up)
अणु
	अचिन्हित पूर्णांक size = serial8250_port_size(up);
	काष्ठा uart_port *port = &up->port;
	पूर्णांक ret = 0;

	चयन (port->iotype) अणु
	हाल UPIO_AU:
	हाल UPIO_TSI:
	हाल UPIO_MEM32:
	हाल UPIO_MEM32BE:
	हाल UPIO_MEM16:
	हाल UPIO_MEM:
		अगर (!port->mapbase)
			अवरोध;

		अगर (!request_mem_region(port->mapbase, size, "serial")) अणु
			ret = -EBUSY;
			अवरोध;
		पूर्ण

		अगर (port->flags & UPF_IOREMAP) अणु
			port->membase = ioremap(port->mapbase, size);
			अगर (!port->membase) अणु
				release_mem_region(port->mapbase, size);
				ret = -ENOMEM;
			पूर्ण
		पूर्ण
		अवरोध;

	हाल UPIO_HUB6:
	हाल UPIO_PORT:
		अगर (!request_region(port->iobase, size, "serial"))
			ret = -EBUSY;
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

अटल व्योम serial8250_release_std_resource(काष्ठा uart_8250_port *up)
अणु
	अचिन्हित पूर्णांक size = serial8250_port_size(up);
	काष्ठा uart_port *port = &up->port;

	चयन (port->iotype) अणु
	हाल UPIO_AU:
	हाल UPIO_TSI:
	हाल UPIO_MEM32:
	हाल UPIO_MEM32BE:
	हाल UPIO_MEM16:
	हाल UPIO_MEM:
		अगर (!port->mapbase)
			अवरोध;

		अगर (port->flags & UPF_IOREMAP) अणु
			iounmap(port->membase);
			port->membase = शून्य;
		पूर्ण

		release_mem_region(port->mapbase, size);
		अवरोध;

	हाल UPIO_HUB6:
	हाल UPIO_PORT:
		release_region(port->iobase, size);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम serial8250_release_port(काष्ठा uart_port *port)
अणु
	काष्ठा uart_8250_port *up = up_to_u8250p(port);

	serial8250_release_std_resource(up);
पूर्ण

अटल पूर्णांक serial8250_request_port(काष्ठा uart_port *port)
अणु
	काष्ठा uart_8250_port *up = up_to_u8250p(port);

	वापस serial8250_request_std_resource(up);
पूर्ण

अटल पूर्णांक fcr_get_rxtrig_bytes(काष्ठा uart_8250_port *up)
अणु
	स्थिर काष्ठा serial8250_config *conf_type = &uart_config[up->port.type];
	अचिन्हित अक्षर bytes;

	bytes = conf_type->rxtrig_bytes[UART_FCR_R_TRIG_BITS(up->fcr)];

	वापस bytes ? bytes : -EOPNOTSUPP;
पूर्ण

अटल पूर्णांक bytes_to_fcr_rxtrig(काष्ठा uart_8250_port *up, अचिन्हित अक्षर bytes)
अणु
	स्थिर काष्ठा serial8250_config *conf_type = &uart_config[up->port.type];
	पूर्णांक i;

	अगर (!conf_type->rxtrig_bytes[UART_FCR_R_TRIG_BITS(UART_FCR_R_TRIG_00)])
		वापस -EOPNOTSUPP;

	क्रम (i = 1; i < UART_FCR_R_TRIG_MAX_STATE; i++) अणु
		अगर (bytes < conf_type->rxtrig_bytes[i])
			/* Use the nearest lower value */
			वापस (--i) << UART_FCR_R_TRIG_SHIFT;
	पूर्ण

	वापस UART_FCR_R_TRIG_11;
पूर्ण

अटल पूर्णांक करो_get_rxtrig(काष्ठा tty_port *port)
अणु
	काष्ठा uart_state *state = container_of(port, काष्ठा uart_state, port);
	काष्ठा uart_port *uport = state->uart_port;
	काष्ठा uart_8250_port *up = up_to_u8250p(uport);

	अगर (!(up->capabilities & UART_CAP_FIFO) || uport->fअगरosize <= 1)
		वापस -EINVAL;

	वापस fcr_get_rxtrig_bytes(up);
पूर्ण

अटल पूर्णांक करो_serial8250_get_rxtrig(काष्ठा tty_port *port)
अणु
	पूर्णांक rxtrig_bytes;

	mutex_lock(&port->mutex);
	rxtrig_bytes = करो_get_rxtrig(port);
	mutex_unlock(&port->mutex);

	वापस rxtrig_bytes;
पूर्ण

अटल sमाप_प्रकार rx_trig_bytes_show(काष्ठा device *dev,
	काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा tty_port *port = dev_get_drvdata(dev);
	पूर्णांक rxtrig_bytes;

	rxtrig_bytes = करो_serial8250_get_rxtrig(port);
	अगर (rxtrig_bytes < 0)
		वापस rxtrig_bytes;

	वापस snम_लिखो(buf, PAGE_SIZE, "%d\n", rxtrig_bytes);
पूर्ण

अटल पूर्णांक करो_set_rxtrig(काष्ठा tty_port *port, अचिन्हित अक्षर bytes)
अणु
	काष्ठा uart_state *state = container_of(port, काष्ठा uart_state, port);
	काष्ठा uart_port *uport = state->uart_port;
	काष्ठा uart_8250_port *up = up_to_u8250p(uport);
	पूर्णांक rxtrig;

	अगर (!(up->capabilities & UART_CAP_FIFO) || uport->fअगरosize <= 1 ||
	    up->fअगरo_bug)
		वापस -EINVAL;

	rxtrig = bytes_to_fcr_rxtrig(up, bytes);
	अगर (rxtrig < 0)
		वापस rxtrig;

	serial8250_clear_fअगरos(up);
	up->fcr &= ~UART_FCR_TRIGGER_MASK;
	up->fcr |= (अचिन्हित अक्षर)rxtrig;
	serial_out(up, UART_FCR, up->fcr);
	वापस 0;
पूर्ण

अटल पूर्णांक करो_serial8250_set_rxtrig(काष्ठा tty_port *port, अचिन्हित अक्षर bytes)
अणु
	पूर्णांक ret;

	mutex_lock(&port->mutex);
	ret = करो_set_rxtrig(port, bytes);
	mutex_unlock(&port->mutex);

	वापस ret;
पूर्ण

अटल sमाप_प्रकार rx_trig_bytes_store(काष्ठा device *dev,
	काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा tty_port *port = dev_get_drvdata(dev);
	अचिन्हित अक्षर bytes;
	पूर्णांक ret;

	अगर (!count)
		वापस -EINVAL;

	ret = kstrtou8(buf, 10, &bytes);
	अगर (ret < 0)
		वापस ret;

	ret = करो_serial8250_set_rxtrig(port, bytes);
	अगर (ret < 0)
		वापस ret;

	वापस count;
पूर्ण

अटल DEVICE_ATTR_RW(rx_trig_bytes);

अटल काष्ठा attribute *serial8250_dev_attrs[] = अणु
	&dev_attr_rx_trig_bytes.attr,
	शून्य
पूर्ण;

अटल काष्ठा attribute_group serial8250_dev_attr_group = अणु
	.attrs = serial8250_dev_attrs,
पूर्ण;

अटल व्योम रेजिस्टर_dev_spec_attr_grp(काष्ठा uart_8250_port *up)
अणु
	स्थिर काष्ठा serial8250_config *conf_type = &uart_config[up->port.type];

	अगर (conf_type->rxtrig_bytes[0])
		up->port.attr_group = &serial8250_dev_attr_group;
पूर्ण

अटल व्योम serial8250_config_port(काष्ठा uart_port *port, पूर्णांक flags)
अणु
	काष्ठा uart_8250_port *up = up_to_u8250p(port);
	पूर्णांक ret;

	/*
	 * Find the region that we can probe क्रम.  This in turn
	 * tells us whether we can probe क्रम the type of port.
	 */
	ret = serial8250_request_std_resource(up);
	अगर (ret < 0)
		वापस;

	अगर (port->iotype != up->cur_iotype)
		set_io_from_upio(port);

	अगर (flags & UART_CONFIG_TYPE)
		स्वतःconfig(up);

	अगर (port->rs485.flags & SER_RS485_ENABLED)
		port->rs485_config(port, &port->rs485);

	/* अगर access method is AU, it is a 16550 with a quirk */
	अगर (port->type == PORT_16550A && port->iotype == UPIO_AU)
		up->bugs |= UART_BUG_NOMSR;

	/* HW bugs may trigger IRQ जबतक IIR == NO_INT */
	अगर (port->type == PORT_TEGRA)
		up->bugs |= UART_BUG_NOMSR;

	अगर (port->type != PORT_UNKNOWN && flags & UART_CONFIG_IRQ)
		स्वतःconfig_irq(up);

	अगर (port->type == PORT_UNKNOWN)
		serial8250_release_std_resource(up);

	रेजिस्टर_dev_spec_attr_grp(up);
	up->fcr = uart_config[up->port.type].fcr;
पूर्ण

अटल पूर्णांक
serial8250_verअगरy_port(काष्ठा uart_port *port, काष्ठा serial_काष्ठा *ser)
अणु
	अगर (ser->irq >= nr_irqs || ser->irq < 0 ||
	    ser->baud_base < 9600 || ser->type < PORT_UNKNOWN ||
	    ser->type >= ARRAY_SIZE(uart_config) || ser->type == PORT_CIRRUS ||
	    ser->type == PORT_STARTECH)
		वापस -EINVAL;
	वापस 0;
पूर्ण

अटल स्थिर अक्षर *serial8250_type(काष्ठा uart_port *port)
अणु
	पूर्णांक type = port->type;

	अगर (type >= ARRAY_SIZE(uart_config))
		type = 0;
	वापस uart_config[type].name;
पूर्ण

अटल स्थिर काष्ठा uart_ops serial8250_pops = अणु
	.tx_empty	= serial8250_tx_empty,
	.set_mctrl	= serial8250_set_mctrl,
	.get_mctrl	= serial8250_get_mctrl,
	.stop_tx	= serial8250_stop_tx,
	.start_tx	= serial8250_start_tx,
	.throttle	= serial8250_throttle,
	.unthrottle	= serial8250_unthrottle,
	.stop_rx	= serial8250_stop_rx,
	.enable_ms	= serial8250_enable_ms,
	.अवरोध_ctl	= serial8250_अवरोध_ctl,
	.startup	= serial8250_startup,
	.shutकरोwn	= serial8250_shutकरोwn,
	.set_termios	= serial8250_set_termios,
	.set_ldisc	= serial8250_set_ldisc,
	.pm		= serial8250_pm,
	.type		= serial8250_type,
	.release_port	= serial8250_release_port,
	.request_port	= serial8250_request_port,
	.config_port	= serial8250_config_port,
	.verअगरy_port	= serial8250_verअगरy_port,
#अगर_घोषित CONFIG_CONSOLE_POLL
	.poll_get_अक्षर = serial8250_get_poll_अक्षर,
	.poll_put_अक्षर = serial8250_put_poll_अक्षर,
#पूर्ण_अगर
पूर्ण;

व्योम serial8250_init_port(काष्ठा uart_8250_port *up)
अणु
	काष्ठा uart_port *port = &up->port;

	spin_lock_init(&port->lock);
	port->ops = &serial8250_pops;
	port->has_sysrq = IS_ENABLED(CONFIG_SERIAL_8250_CONSOLE);

	up->cur_iotype = 0xFF;
पूर्ण
EXPORT_SYMBOL_GPL(serial8250_init_port);

व्योम serial8250_set_शेषs(काष्ठा uart_8250_port *up)
अणु
	काष्ठा uart_port *port = &up->port;

	अगर (up->port.flags & UPF_FIXED_TYPE) अणु
		अचिन्हित पूर्णांक type = up->port.type;

		अगर (!up->port.fअगरosize)
			up->port.fअगरosize = uart_config[type].fअगरo_size;
		अगर (!up->tx_loadsz)
			up->tx_loadsz = uart_config[type].tx_loadsz;
		अगर (!up->capabilities)
			up->capabilities = uart_config[type].flags;
	पूर्ण

	set_io_from_upio(port);

	/* शेष dma handlers */
	अगर (up->dma) अणु
		अगर (!up->dma->tx_dma)
			up->dma->tx_dma = serial8250_tx_dma;
		अगर (!up->dma->rx_dma)
			up->dma->rx_dma = serial8250_rx_dma;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(serial8250_set_शेषs);

#अगर_घोषित CONFIG_SERIAL_8250_CONSOLE

अटल व्योम serial8250_console_अक्षर_दो(काष्ठा uart_port *port, पूर्णांक ch)
अणु
	काष्ठा uart_8250_port *up = up_to_u8250p(port);

	रुको_क्रम_xmitr(up, UART_LSR_THRE);
	serial_port_out(port, UART_TX, ch);
पूर्ण

/*
 *	Restore serial console when h/w घातer-off detected
 */
अटल व्योम serial8250_console_restore(काष्ठा uart_8250_port *up)
अणु
	काष्ठा uart_port *port = &up->port;
	काष्ठा ktermios termios;
	अचिन्हित पूर्णांक baud, quot, frac = 0;

	termios.c_cflag = port->cons->cflag;
	अगर (port->state->port.tty && termios.c_cflag == 0)
		termios.c_cflag = port->state->port.tty->termios.c_cflag;

	baud = serial8250_get_baud_rate(port, &termios, शून्य);
	quot = serial8250_get_भागisor(port, baud, &frac);

	serial8250_set_भागisor(port, baud, quot, frac);
	serial_port_out(port, UART_LCR, up->lcr);
	serial8250_out_MCR(up, UART_MCR_DTR | UART_MCR_RTS);
पूर्ण

/*
 *	Prपूर्णांक a string to the serial port trying not to disturb
 *	any possible real use of the port...
 *
 *	The console_lock must be held when we get here.
 *
 *	Doing runसमय PM is really a bad idea क्रम the kernel console.
 *	Thus, we assume the function is called when device is घातered up.
 */
व्योम serial8250_console_ग_लिखो(काष्ठा uart_8250_port *up, स्थिर अक्षर *s,
			      अचिन्हित पूर्णांक count)
अणु
	काष्ठा uart_8250_em485 *em485 = up->em485;
	काष्ठा uart_port *port = &up->port;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक ier;
	पूर्णांक locked = 1;

	touch_nmi_watchकरोg();

	अगर (oops_in_progress)
		locked = spin_trylock_irqsave(&port->lock, flags);
	अन्यथा
		spin_lock_irqsave(&port->lock, flags);

	/*
	 *	First save the IER then disable the पूर्णांकerrupts
	 */
	ier = serial_port_in(port, UART_IER);

	अगर (up->capabilities & UART_CAP_UUE)
		serial_port_out(port, UART_IER, UART_IER_UUE);
	अन्यथा
		serial_port_out(port, UART_IER, 0);

	/* check scratch reg to see अगर port घातered off during प्रणाली sleep */
	अगर (up->canary && (up->canary != serial_port_in(port, UART_SCR))) अणु
		serial8250_console_restore(up);
		up->canary = 0;
	पूर्ण

	अगर (em485) अणु
		अगर (em485->tx_stopped)
			up->rs485_start_tx(up);
		mdelay(port->rs485.delay_rts_beक्रमe_send);
	पूर्ण

	uart_console_ग_लिखो(port, s, count, serial8250_console_अक्षर_दो);

	/*
	 *	Finally, रुको क्रम transmitter to become empty
	 *	and restore the IER
	 */
	रुको_क्रम_xmitr(up, BOTH_EMPTY);

	अगर (em485) अणु
		mdelay(port->rs485.delay_rts_after_send);
		अगर (em485->tx_stopped)
			up->rs485_stop_tx(up);
	पूर्ण

	serial_port_out(port, UART_IER, ier);

	/*
	 *	The receive handling will happen properly because the
	 *	receive पढ़ोy bit will still be set; it is not cleared
	 *	on पढ़ो.  However, modem control will not, we must
	 *	call it अगर we have saved something in the saved flags
	 *	जबतक processing with पूर्णांकerrupts off.
	 */
	अगर (up->msr_saved_flags)
		serial8250_modem_status(up);

	अगर (locked)
		spin_unlock_irqrestore(&port->lock, flags);
पूर्ण

अटल अचिन्हित पूर्णांक probe_baud(काष्ठा uart_port *port)
अणु
	अचिन्हित अक्षर lcr, dll, dlm;
	अचिन्हित पूर्णांक quot;

	lcr = serial_port_in(port, UART_LCR);
	serial_port_out(port, UART_LCR, lcr | UART_LCR_DLAB);
	dll = serial_port_in(port, UART_DLL);
	dlm = serial_port_in(port, UART_DLM);
	serial_port_out(port, UART_LCR, lcr);

	quot = (dlm << 8) | dll;
	वापस (port->uartclk / 16) / quot;
पूर्ण

पूर्णांक serial8250_console_setup(काष्ठा uart_port *port, अक्षर *options, bool probe)
अणु
	पूर्णांक baud = 9600;
	पूर्णांक bits = 8;
	पूर्णांक parity = 'n';
	पूर्णांक flow = 'n';
	पूर्णांक ret;

	अगर (!port->iobase && !port->membase)
		वापस -ENODEV;

	अगर (options)
		uart_parse_options(options, &baud, &parity, &bits, &flow);
	अन्यथा अगर (probe)
		baud = probe_baud(port);

	ret = uart_set_options(port, port->cons, baud, parity, bits, flow);
	अगर (ret)
		वापस ret;

	अगर (port->dev)
		pm_runसमय_get_sync(port->dev);

	वापस 0;
पूर्ण

पूर्णांक serial8250_console_निकास(काष्ठा uart_port *port)
अणु
	अगर (port->dev)
		pm_runसमय_put_sync(port->dev);

	वापस 0;
पूर्ण

#पूर्ण_अगर /* CONFIG_SERIAL_8250_CONSOLE */

MODULE_LICENSE("GPL");
