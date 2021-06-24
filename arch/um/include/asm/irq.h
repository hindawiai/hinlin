<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __UM_IRQ_H
#घोषणा __UM_IRQ_H

#घोषणा TIMER_IRQ		0
#घोषणा UMN_IRQ			1
#घोषणा CONSOLE_IRQ		2
#घोषणा CONSOLE_WRITE_IRQ	3
#घोषणा UBD_IRQ			4
#घोषणा UM_ETH_IRQ		5
#घोषणा SSL_IRQ			6
#घोषणा SSL_WRITE_IRQ		7
#घोषणा ACCEPT_IRQ		8
#घोषणा MCONSOLE_IRQ		9
#घोषणा WINCH_IRQ		10
#घोषणा SIGIO_WRITE_IRQ 	11
#घोषणा TELNETD_IRQ 		12
#घोषणा XTERM_IRQ 		13
#घोषणा RANDOM_IRQ 		14

#अगर_घोषित CONFIG_UML_NET_VECTOR

#घोषणा VECTOR_BASE_IRQ		(RANDOM_IRQ + 1)
#घोषणा VECTOR_IRQ_SPACE	8

#घोषणा UM_FIRST_DYN_IRQ (VECTOR_IRQ_SPACE + VECTOR_BASE_IRQ)

#अन्यथा

#घोषणा UM_FIRST_DYN_IRQ (RANDOM_IRQ + 1)

#पूर्ण_अगर

#घोषणा NR_IRQS			64

#समावेश <यंत्र-generic/irq.h>
#पूर्ण_अगर
