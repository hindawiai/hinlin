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

#समावेश <linux/types.h>
#समावेश <linux/serial_reg.h>

#समावेश <यंत्र/mipsregs.h>
#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/netlogic/haldefs.h>
#समावेश <यंत्र/netlogic/common.h>

#अगर defined(CONFIG_CPU_XLP)
#समावेश <यंत्र/netlogic/xlp-hal/iomap.h>
#समावेश <यंत्र/netlogic/xlp-hal/xlp.h>
#समावेश <यंत्र/netlogic/xlp-hal/uart.h>
#या_अगर defined(CONFIG_CPU_XLR)
#समावेश <यंत्र/netlogic/xlr/iomap.h>
#पूर्ण_अगर

व्योम prom_अक्षर_दो(अक्षर c)
अणु
	uपूर्णांक64_t uartbase;

#अगर defined(CONFIG_CPU_XLP)
	uartbase = nlm_get_uart_regbase(0, 0);
#या_अगर defined(CONFIG_CPU_XLR)
	uartbase = nlm_mmio_base(NETLOGIC_IO_UART_0_OFFSET);
#पूर्ण_अगर
	जबतक ((nlm_पढ़ो_reg(uartbase, UART_LSR) & UART_LSR_THRE) == 0)
		;
	nlm_ग_लिखो_reg(uartbase, UART_TX, c);
पूर्ण
