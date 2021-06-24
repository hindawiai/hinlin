<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _SPEAKUP_SERIAL_H
#घोषणा _SPEAKUP_SERIAL_H

#समावेश <linux/serial.h>	/* क्रम rs_table, serial स्थिरants */
#समावेश <linux/serial_reg.h>	/* क्रम more serial स्थिरants */
#समावेश <linux/serial_core.h>

#समावेश "spk_priv.h"

/*
 * this is cut&paste from 8250.h. Get rid of the काष्ठाure, the definitions
 * and this whole broken driver.
 */
काष्ठा old_serial_port अणु
	अचिन्हित पूर्णांक uart; /* unused */
	अचिन्हित पूर्णांक baud_base;
	अचिन्हित पूर्णांक port;
	अचिन्हित पूर्णांक irq;
	upf_t flags; /* unused */
पूर्ण;

/* countकरोwn values क्रम serial समयouts in us */
#घोषणा SPK_SERIAL_TIMEOUT SPK_SYNTH_TIMEOUT
/* countकरोwn values transmitter/dsr समयouts in us */
#घोषणा SPK_XMITR_TIMEOUT 100000
/* countकरोwn values cts समयouts in us */
#घोषणा SPK_CTS_TIMEOUT 100000
/* check ttyS0 ... ttyS3 */
#घोषणा SPK_LO_TTY 0
#घोषणा SPK_HI_TTY 3
/* # of समयouts permitted beक्रमe disable */
#घोषणा NUM_DISABLE_TIMEOUTS 3
/* buffer समयout in ms */
#घोषणा SPK_TIMEOUT 100
#घोषणा BOTH_EMPTY (UART_LSR_TEMT | UART_LSR_THRE)

#घोषणा spk_serial_tx_busy() \
	((inb(speakup_info.port_tts + UART_LSR) & BOTH_EMPTY) != BOTH_EMPTY)

#पूर्ण_अगर
