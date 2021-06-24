<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
	Mantis PCI bridge driver

	Copyright (C) Manu Abraham (abraham.manu@gmail.com)

*/

#समावेश <linux/kernel.h>
#समावेश <linux/spinlock.h>
#समावेश <यंत्र/पन.स>

#समावेश <linux/संकेत.स>
#समावेश <linux/sched.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/pci.h>

#समावेश <media/dmxdev.h>
#समावेश <media/dvbdev.h>
#समावेश <media/dvb_demux.h>
#समावेश <media/dvb_frontend.h>
#समावेश <media/dvb_net.h>

#समावेश "mantis_common.h"
#समावेश "mantis_reg.h"
#समावेश "mantis_uart.h"
#समावेश "mantis_input.h"

काष्ठा mantis_uart_params अणु
	क्रमागत mantis_baud	baud_rate;
	क्रमागत mantis_parity	parity;
पूर्ण;

अटल काष्ठा अणु
	अक्षर string[7];
पूर्ण rates[5] = अणु
	अणु "9600" पूर्ण,
	अणु "19200" पूर्ण,
	अणु "38400" पूर्ण,
	अणु "57600" पूर्ण,
	अणु "115200" पूर्ण
पूर्ण;

अटल काष्ठा अणु
	अक्षर string[5];
पूर्ण parity[3] = अणु
	अणु "NONE" पूर्ण,
	अणु "ODD" पूर्ण,
	अणु "EVEN" पूर्ण
पूर्ण;

अटल व्योम mantis_uart_पढ़ो(काष्ठा mantis_pci *mantis)
अणु
	काष्ठा mantis_hwconfig *config = mantis->hwconfig;
	पूर्णांक i, scancode = 0, err = 0;

	/* get data */
	dprपूर्णांकk(MANTIS_DEBUG, 1, "UART Reading ...");
	क्रम (i = 0; i < (config->bytes + 1); i++) अणु
		पूर्णांक data = mmपढ़ो(MANTIS_UART_RXD);

		dprपूर्णांकk(MANTIS_DEBUG, 0, " <%02x>", data);

		scancode = (scancode << 8) | (data & 0x3f);
		err |= data;

		अगर (data & (1 << 7))
			dprपूर्णांकk(MANTIS_ERROR, 1, "UART framing error");

		अगर (data & (1 << 6))
			dprपूर्णांकk(MANTIS_ERROR, 1, "UART parity error");
	पूर्ण
	dprपूर्णांकk(MANTIS_DEBUG, 0, "\n");

	अगर ((err & 0xC0) == 0)
		mantis_input_process(mantis, scancode);
पूर्ण

अटल व्योम mantis_uart_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा mantis_pci *mantis = container_of(work, काष्ठा mantis_pci, uart_work);
	u32 stat;
	अचिन्हित दीर्घ समयout;

	stat = mmपढ़ो(MANTIS_UART_STAT);

	अगर (stat & MANTIS_UART_RXFIFO_FULL)
		dprपूर्णांकk(MANTIS_ERROR, 1, "RX Fifo FULL");

	/*
	 * MANTIS_UART_RXFIFO_DATA is only set अगर at least
	 * config->bytes + 1 bytes are in the FIFO.
	 */

	/* FIXME: is 10ms good enough ? */
	समयout = jअगरfies +  msecs_to_jअगरfies(10);
	जबतक (stat & MANTIS_UART_RXFIFO_DATA) अणु
		mantis_uart_पढ़ो(mantis);
		stat = mmपढ़ो(MANTIS_UART_STAT);

		अगर (!समय_is_after_jअगरfies(समयout))
			अवरोध;
	पूर्ण

	/* re-enable UART (RX) पूर्णांकerrupt */
	mantis_unmask_पूर्णांकs(mantis, MANTIS_INT_IRQ1);
पूर्ण

अटल पूर्णांक mantis_uart_setup(काष्ठा mantis_pci *mantis,
			     काष्ठा mantis_uart_params *params)
अणु
	u32 reg;

	mmग_लिखो((mmपढ़ो(MANTIS_UART_CTL) | (params->parity & 0x3)), MANTIS_UART_CTL);

	reg = mmपढ़ो(MANTIS_UART_BAUD);

	चयन (params->baud_rate) अणु
	हाल MANTIS_BAUD_9600:
		reg |= 0xd8;
		अवरोध;
	हाल MANTIS_BAUD_19200:
		reg |= 0x6c;
		अवरोध;
	हाल MANTIS_BAUD_38400:
		reg |= 0x36;
		अवरोध;
	हाल MANTIS_BAUD_57600:
		reg |= 0x23;
		अवरोध;
	हाल MANTIS_BAUD_115200:
		reg |= 0x11;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	mmग_लिखो(reg, MANTIS_UART_BAUD);

	वापस 0;
पूर्ण

पूर्णांक mantis_uart_init(काष्ठा mantis_pci *mantis)
अणु
	काष्ठा mantis_hwconfig *config = mantis->hwconfig;
	काष्ठा mantis_uart_params params;

	/* शेष parity: */
	params.baud_rate = config->baud_rate;
	params.parity = config->parity;
	dprपूर्णांकk(MANTIS_INFO, 1, "Initializing UART @ %sbps parity:%s",
		rates[params.baud_rate].string,
		parity[params.parity].string);

	INIT_WORK(&mantis->uart_work, mantis_uart_work);

	/* disable पूर्णांकerrupt */
	mmग_लिखो(mmपढ़ो(MANTIS_UART_CTL) & 0xffef, MANTIS_UART_CTL);

	mantis_uart_setup(mantis, &params);

	/* शेष 1 byte */
	mmग_लिखो((mmपढ़ो(MANTIS_UART_BAUD) | (config->bytes << 8)), MANTIS_UART_BAUD);

	/* flush buffer */
	mmग_लिखो((mmपढ़ो(MANTIS_UART_CTL) | MANTIS_UART_RXFLUSH), MANTIS_UART_CTL);

	/* enable पूर्णांकerrupt */
	mmग_लिखो(mmपढ़ो(MANTIS_UART_CTL) | MANTIS_UART_RXINT, MANTIS_UART_CTL);
	mantis_unmask_पूर्णांकs(mantis, MANTIS_INT_IRQ1);

	schedule_work(&mantis->uart_work);
	dprपूर्णांकk(MANTIS_DEBUG, 1, "UART successfully initialized");

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(mantis_uart_init);

व्योम mantis_uart_निकास(काष्ठा mantis_pci *mantis)
अणु
	/* disable पूर्णांकerrupt */
	mantis_mask_पूर्णांकs(mantis, MANTIS_INT_IRQ1);
	mmग_लिखो(mmपढ़ो(MANTIS_UART_CTL) & 0xffef, MANTIS_UART_CTL);
	flush_work(&mantis->uart_work);
पूर्ण
EXPORT_SYMBOL_GPL(mantis_uart_निकास);
