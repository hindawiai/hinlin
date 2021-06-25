<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * 16550 serial console support.
 *
 * Original copied from <file:arch/ppc/boot/common/ns16550.c>
 * (which had no copyright)
 * Modअगरications: 2006 (c) MontaVista Software, Inc.
 *
 * Modअगरied by: Mark A. Greer <mgreer@mvista.com>
 */
#समावेश <मानकतर्क.स>
#समावेश <मानकघोष.स>
#समावेश "types.h"
#समावेश "string.h"
#समावेश "stdio.h"
#समावेश "io.h"
#समावेश "ops.h"

#घोषणा UART_DLL	0	/* Out: Divisor Latch Low */
#घोषणा UART_DLM	1	/* Out: Divisor Latch High */
#घोषणा UART_FCR	2	/* Out: FIFO Control Register */
#घोषणा UART_LCR	3	/* Out: Line Control Register */
#घोषणा UART_MCR	4	/* Out: Modem Control Register */
#घोषणा UART_LSR	5	/* In:  Line Status Register */
#घोषणा UART_LSR_THRE	0x20	/* Transmit-hold-रेजिस्टर empty */
#घोषणा UART_LSR_DR	0x01	/* Receiver data पढ़ोy */
#घोषणा UART_MSR	6	/* In:  Modem Status Register */
#घोषणा UART_SCR	7	/* I/O: Scratch Register */

अटल अचिन्हित अक्षर *reg_base;
अटल u32 reg_shअगरt;

अटल पूर्णांक ns16550_खोलो(व्योम)
अणु
	out_8(reg_base + (UART_FCR << reg_shअगरt), 0x06);
	वापस 0;
पूर्ण

अटल व्योम ns16550_अ_दो(अचिन्हित अक्षर c)
अणु
	जबतक ((in_8(reg_base + (UART_LSR << reg_shअगरt)) & UART_LSR_THRE) == 0);
	out_8(reg_base, c);
पूर्ण

अटल अचिन्हित अक्षर ns16550_अ_लो(व्योम)
अणु
	जबतक ((in_8(reg_base + (UART_LSR << reg_shअगरt)) & UART_LSR_DR) == 0);
	वापस in_8(reg_base);
पूर्ण

अटल u8 ns16550_tstc(व्योम)
अणु
	वापस ((in_8(reg_base + (UART_LSR << reg_shअगरt)) & UART_LSR_DR) != 0);
पूर्ण

पूर्णांक ns16550_console_init(व्योम *devp, काष्ठा serial_console_data *scdp)
अणु
	पूर्णांक n;
	u32 reg_offset;

	अगर (dt_get_भव_reg(devp, (व्योम **)&reg_base, 1) < 1)
		वापस -1;

	n = getprop(devp, "reg-offset", &reg_offset, माप(reg_offset));
	अगर (n == माप(reg_offset))
		reg_base += reg_offset;

	n = getprop(devp, "reg-shift", &reg_shअगरt, माप(reg_shअगरt));
	अगर (n != माप(reg_shअगरt))
		reg_shअगरt = 0;

	scdp->खोलो = ns16550_खोलो;
	scdp->अ_दो = ns16550_अ_दो;
	scdp->अ_लो = ns16550_अ_लो;
	scdp->tstc = ns16550_tstc;
	scdp->बंद = शून्य;

	वापस 0;
पूर्ण
