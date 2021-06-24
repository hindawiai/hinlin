<शैली गुरु>
/*
 * Copyright (C) 2015, Marvell International Ltd.
 *
 * This software file (the "File") is distributed by Marvell International
 * Ltd. under the terms of the GNU General Public License Version 2, June 1991
 * (the "License").  You may use, redistribute and/or modअगरy this File in
 * accordance with the terms and conditions of the License, a copy of which
 * is available on the worldwide web at
 * http://www.gnu.org/licenses/old-licenses/gpl-2.0.txt.
 *
 * THE खाता IS DISTRIBUTED AS-IS, WITHOUT WARRANTY OF ANY KIND, AND THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE
 * ARE EXPRESSLY DISCLAIMED.  The License provides additional details about
 * this warranty disclaimer.
 */

#अगर_अघोषित _NFCMRVL_PTF_H_
#घोषणा _NFCMRVL_PTF_H_

काष्ठा nfcmrvl_platक्रमm_data अणु
	/*
	 * Generic
	 */

	/* GPIO that is wired to RESET_N संकेत */
	पूर्णांक reset_n_io;
	/* Tell अगर transport is muxed in HCI one */
	अचिन्हित पूर्णांक hci_muxed;

	/*
	 * UART specअगरic
	 */

	/* Tell अगर UART needs flow control at init */
	अचिन्हित पूर्णांक flow_control;
	/* Tell अगर firmware supports अवरोध control क्रम घातer management */
	अचिन्हित पूर्णांक अवरोध_control;


	/*
	 * I2C specअगरic
	 */

	अचिन्हित पूर्णांक irq;
	अचिन्हित पूर्णांक irq_polarity;
पूर्ण;

#पूर्ण_अगर /* _NFCMRVL_PTF_H_ */
