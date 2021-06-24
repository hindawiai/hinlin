<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *  Author: Nicolas Pitre
 *
 * Moved and changed lots, Russell King
 *
 * Low level machine dependent UART functions.
 */
#अगर_अघोषित SA11X0_SERIAL_H
#घोषणा SA11X0_SERIAL_H

काष्ठा uart_port;
काष्ठा uart_info;

/*
 * This is a temporary काष्ठाure क्रम रेजिस्टरing these
 * functions; it is पूर्णांकended to be discarded after boot.
 */
काष्ठा sa1100_port_fns अणु
	व्योम	(*set_mctrl)(काष्ठा uart_port *, u_पूर्णांक);
	u_पूर्णांक	(*get_mctrl)(काष्ठा uart_port *);
	व्योम	(*pm)(काष्ठा uart_port *, u_पूर्णांक, u_पूर्णांक);
	पूर्णांक	(*set_wake)(काष्ठा uart_port *, u_पूर्णांक);
पूर्ण;

#अगर_घोषित CONFIG_SERIAL_SA1100
व्योम sa1100_रेजिस्टर_uart_fns(काष्ठा sa1100_port_fns *fns);
व्योम sa1100_रेजिस्टर_uart(पूर्णांक idx, पूर्णांक port);
#अन्यथा
अटल अंतरभूत व्योम sa1100_रेजिस्टर_uart_fns(काष्ठा sa1100_port_fns *fns)
अणु
पूर्ण
अटल अंतरभूत व्योम sa1100_रेजिस्टर_uart(पूर्णांक idx, पूर्णांक port)
अणु
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर
