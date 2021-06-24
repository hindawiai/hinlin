<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/* Synopsys DesignWare 8250 library. */

#समावेश <linux/bitops.h>
#समावेश <linux/device.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/serial_8250.h>
#समावेश <linux/serial_core.h>

#समावेश "8250_dwlib.h"

/* Offsets क्रम the DesignWare specअगरic रेजिस्टरs */
#घोषणा DW_UART_DLF	0xc0 /* Divisor Latch Fraction Register */
#घोषणा DW_UART_CPR	0xf4 /* Component Parameter Register */
#घोषणा DW_UART_UCV	0xf8 /* UART Component Version */

/* Component Parameter Register bits */
#घोषणा DW_UART_CPR_ABP_DATA_WIDTH	(3 << 0)
#घोषणा DW_UART_CPR_AFCE_MODE		(1 << 4)
#घोषणा DW_UART_CPR_THRE_MODE		(1 << 5)
#घोषणा DW_UART_CPR_SIR_MODE		(1 << 6)
#घोषणा DW_UART_CPR_SIR_LP_MODE		(1 << 7)
#घोषणा DW_UART_CPR_ADDITIONAL_FEATURES	(1 << 8)
#घोषणा DW_UART_CPR_FIFO_ACCESS		(1 << 9)
#घोषणा DW_UART_CPR_FIFO_STAT		(1 << 10)
#घोषणा DW_UART_CPR_SHADOW		(1 << 11)
#घोषणा DW_UART_CPR_ENCODED_PARMS	(1 << 12)
#घोषणा DW_UART_CPR_DMA_EXTRA		(1 << 13)
#घोषणा DW_UART_CPR_FIFO_MODE		(0xff << 16)

/* Helper क्रम FIFO size calculation */
#घोषणा DW_UART_CPR_FIFO_SIZE(a)	(((a >> 16) & 0xff) * 16)

अटल अंतरभूत u32 dw8250_पढ़ोl_ext(काष्ठा uart_port *p, पूर्णांक offset)
अणु
	अगर (p->iotype == UPIO_MEM32BE)
		वापस ioपढ़ो32be(p->membase + offset);
	वापस पढ़ोl(p->membase + offset);
पूर्ण

अटल अंतरभूत व्योम dw8250_ग_लिखोl_ext(काष्ठा uart_port *p, पूर्णांक offset, u32 reg)
अणु
	अगर (p->iotype == UPIO_MEM32BE)
		ioग_लिखो32be(reg, p->membase + offset);
	अन्यथा
		ग_लिखोl(reg, p->membase + offset);
पूर्ण

/*
 * भागisor = भाग(I) + भाग(F)
 * "I" means पूर्णांकeger, "F" means fractional
 * quot = भाग(I) = clk / (16 * baud)
 * frac = भाग(F) * 2^dlf_size
 *
 * let rem = clk % (16 * baud)
 * we have: भाग(F) * (16 * baud) = rem
 * so frac = 2^dlf_size * rem / (16 * baud) = (rem << dlf_size) / (16 * baud)
 */
अटल अचिन्हित पूर्णांक dw8250_get_भागisor(काष्ठा uart_port *p, अचिन्हित पूर्णांक baud,
				       अचिन्हित पूर्णांक *frac)
अणु
	अचिन्हित पूर्णांक quot, rem, base_baud = baud * 16;
	काष्ठा dw8250_port_data *d = p->निजी_data;

	quot = p->uartclk / base_baud;
	rem = p->uartclk % base_baud;
	*frac = DIV_ROUND_CLOSEST(rem << d->dlf_size, base_baud);

	वापस quot;
पूर्ण

अटल व्योम dw8250_set_भागisor(काष्ठा uart_port *p, अचिन्हित पूर्णांक baud,
			       अचिन्हित पूर्णांक quot, अचिन्हित पूर्णांक quot_frac)
अणु
	dw8250_ग_लिखोl_ext(p, DW_UART_DLF, quot_frac);
	serial8250_करो_set_भागisor(p, baud, quot, quot_frac);
पूर्ण

व्योम dw8250_setup_port(काष्ठा uart_port *p)
अणु
	काष्ठा uart_8250_port *up = up_to_u8250p(p);
	u32 reg;

	/*
	 * If the Component Version Register वापसs zero, we know that
	 * ADDITIONAL_FEATURES are not enabled. No need to go any further.
	 */
	reg = dw8250_पढ़ोl_ext(p, DW_UART_UCV);
	अगर (!reg)
		वापस;

	dev_dbg(p->dev, "Designware UART version %c.%c%c\n",
		(reg >> 24) & 0xff, (reg >> 16) & 0xff, (reg >> 8) & 0xff);

	dw8250_ग_लिखोl_ext(p, DW_UART_DLF, ~0U);
	reg = dw8250_पढ़ोl_ext(p, DW_UART_DLF);
	dw8250_ग_लिखोl_ext(p, DW_UART_DLF, 0);

	अगर (reg) अणु
		काष्ठा dw8250_port_data *d = p->निजी_data;

		d->dlf_size = fls(reg);
		p->get_भागisor = dw8250_get_भागisor;
		p->set_भागisor = dw8250_set_भागisor;
	पूर्ण

	reg = dw8250_पढ़ोl_ext(p, DW_UART_CPR);
	अगर (!reg)
		वापस;

	/* Select the type based on FIFO */
	अगर (reg & DW_UART_CPR_FIFO_MODE) अणु
		p->type = PORT_16550A;
		p->flags |= UPF_FIXED_TYPE;
		p->fअगरosize = DW_UART_CPR_FIFO_SIZE(reg);
		up->capabilities = UART_CAP_FIFO;
	पूर्ण

	अगर (reg & DW_UART_CPR_AFCE_MODE)
		up->capabilities |= UART_CAP_AFE;

	अगर (reg & DW_UART_CPR_SIR_MODE)
		up->capabilities |= UART_CAP_IRDA;
पूर्ण
EXPORT_SYMBOL_GPL(dw8250_setup_port);
