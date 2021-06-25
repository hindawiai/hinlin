<शैली गुरु>
/*
 * Copyright 2003-2011 NetLogic Microप्रणालीs, Inc. (NetLogic). All rights
 * reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the NetLogic
 * license below:
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary क्रमm must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the करोcumentation and/or other materials provided with the
 *    distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY NETLOGIC ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL NETLOGIC OR CONTRIBUTORS BE LIABLE
 * FOR ANY सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 * BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
 * IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#अगर_अघोषित __XLP_HAL_UART_H__
#घोषणा __XLP_HAL_UART_H__

/* UART Specअगरic रेजिस्टरs */
#घोषणा UART_RX_DATA		0x00
#घोषणा UART_TX_DATA		0x00

#घोषणा UART_INT_EN		0x01
#घोषणा UART_INT_ID		0x02
#घोषणा UART_FIFO_CTL		0x02
#घोषणा UART_LINE_CTL		0x03
#घोषणा UART_MODEM_CTL		0x04
#घोषणा UART_LINE_STS		0x05
#घोषणा UART_MODEM_STS		0x06

#घोषणा UART_DIVISOR0		0x00
#घोषणा UART_DIVISOR1		0x01

#घोषणा BASE_BAUD		(XLP_IO_CLK/16)
#घोषणा BAUD_DIVISOR(baud)	(BASE_BAUD / baud)

/* LCR mask values */
#घोषणा LCR_5BITS		0x00
#घोषणा LCR_6BITS		0x01
#घोषणा LCR_7BITS		0x02
#घोषणा LCR_8BITS		0x03
#घोषणा LCR_STOPB		0x04
#घोषणा LCR_PENAB		0x08
#घोषणा LCR_PODD		0x00
#घोषणा LCR_PEVEN		0x10
#घोषणा LCR_PONE		0x20
#घोषणा LCR_PZERO		0x30
#घोषणा LCR_SBREAK		0x40
#घोषणा LCR_EFR_ENABLE		0xbf
#घोषणा LCR_DLAB		0x80

/* MCR mask values */
#घोषणा MCR_DTR			0x01
#घोषणा MCR_RTS			0x02
#घोषणा MCR_DRS			0x04
#घोषणा MCR_IE			0x08
#घोषणा MCR_LOOPBACK		0x10

/* FCR mask values */
#घोषणा FCR_RCV_RST		0x02
#घोषणा FCR_XMT_RST		0x04
#घोषणा FCR_RX_LOW		0x00
#घोषणा FCR_RX_MEDL		0x40
#घोषणा FCR_RX_MEDH		0x80
#घोषणा FCR_RX_HIGH		0xc0

/* IER mask values */
#घोषणा IER_ERXRDY		0x1
#घोषणा IER_ETXRDY		0x2
#घोषणा IER_ERLS		0x4
#घोषणा IER_EMSC		0x8

#अगर !defined(LOCORE) && !defined(__ASSEMBLY__)

#घोषणा nlm_पढ़ो_uart_reg(b, r)		nlm_पढ़ो_reg(b, r)
#घोषणा nlm_ग_लिखो_uart_reg(b, r, v)	nlm_ग_लिखो_reg(b, r, v)
#घोषणा nlm_get_uart_pcibase(node, inst)	\
	nlm_pcicfg_base(cpu_is_xlp9xx() ?  XLP9XX_IO_UART_OFFSET(node) : \
						XLP_IO_UART_OFFSET(node, inst))
#घोषणा nlm_get_uart_regbase(node, inst)	\
			(nlm_get_uart_pcibase(node, inst) + XLP_IO_PCI_HDRSZ)

अटल अंतरभूत व्योम
nlm_uart_set_baudrate(uपूर्णांक64_t base, पूर्णांक baud)
अणु
	uपूर्णांक32_t lcr;

	lcr = nlm_पढ़ो_uart_reg(base, UART_LINE_CTL);

	/* enable भागisor रेजिस्टर, and ग_लिखो baud values */
	nlm_ग_लिखो_uart_reg(base, UART_LINE_CTL, lcr | (1 << 7));
	nlm_ग_लिखो_uart_reg(base, UART_DIVISOR0,
			(BAUD_DIVISOR(baud) & 0xff));
	nlm_ग_लिखो_uart_reg(base, UART_DIVISOR1,
			((BAUD_DIVISOR(baud) >> 8) & 0xff));

	/* restore शेष lcr */
	nlm_ग_लिखो_uart_reg(base, UART_LINE_CTL, lcr);
पूर्ण

अटल अंतरभूत व्योम
nlm_uart_outbyte(uपूर्णांक64_t base, अक्षर c)
अणु
	uपूर्णांक32_t lsr;

	क्रम (;;) अणु
		lsr = nlm_पढ़ो_uart_reg(base, UART_LINE_STS);
		अगर (lsr & 0x20)
			अवरोध;
	पूर्ण

	nlm_ग_लिखो_uart_reg(base, UART_TX_DATA, (पूर्णांक)c);
पूर्ण

अटल अंतरभूत अक्षर
nlm_uart_inbyte(uपूर्णांक64_t base)
अणु
	पूर्णांक data, lsr;

	क्रम (;;) अणु
		lsr = nlm_पढ़ो_uart_reg(base, UART_LINE_STS);
		अगर (lsr & 0x80) अणु /* parity/frame/अवरोध-error - push a zero */
			data = 0;
			अवरोध;
		पूर्ण
		अगर (lsr & 0x01) अणु	/* Rx data */
			data = nlm_पढ़ो_uart_reg(base, UART_RX_DATA);
			अवरोध;
		पूर्ण
	पूर्ण

	वापस (अक्षर)data;
पूर्ण

अटल अंतरभूत पूर्णांक
nlm_uart_init(uपूर्णांक64_t base, पूर्णांक baud, पूर्णांक databits, पूर्णांक stopbits,
	पूर्णांक parity, पूर्णांक पूर्णांक_en, पूर्णांक loopback)
अणु
	uपूर्णांक32_t lcr;

	lcr = 0;
	अगर (databits >= 8)
		lcr |= LCR_8BITS;
	अन्यथा अगर (databits == 7)
		lcr |= LCR_7BITS;
	अन्यथा अगर (databits == 6)
		lcr |= LCR_6BITS;
	अन्यथा
		lcr |= LCR_5BITS;

	अगर (stopbits > 1)
		lcr |= LCR_STOPB;

	lcr |= parity << 3;

	/* setup शेष lcr */
	nlm_ग_लिखो_uart_reg(base, UART_LINE_CTL, lcr);

	/* Reset the FIFOs */
	nlm_ग_लिखो_uart_reg(base, UART_LINE_CTL, FCR_RCV_RST | FCR_XMT_RST);

	nlm_uart_set_baudrate(base, baud);

	अगर (loopback)
		nlm_ग_लिखो_uart_reg(base, UART_MODEM_CTL, 0x1f);

	अगर (पूर्णांक_en)
		nlm_ग_लिखो_uart_reg(base, UART_INT_EN, IER_ERXRDY | IER_ETXRDY);

	वापस 0;
पूर्ण
#पूर्ण_अगर /* !LOCORE && !__ASSEMBLY__ */
#पूर्ण_अगर /* __XLP_HAL_UART_H__ */
