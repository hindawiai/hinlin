<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/**
 * ipoctal.h
 *
 * driver क्रम the IPOCTAL boards

 * Copyright (C) 2009-2012 CERN (www.cern.ch)
 * Author: Nicolas Serafini, EIC2 SA
 * Author: Samuel Iglesias Gonsalvez <siglesias@igalia.com>
 */

#अगर_अघोषित _IPOCTAL_H_
#घोषणा _IPOCTAL_H_

#घोषणा NR_CHANNELS		8
#घोषणा IPOCTAL_MAX_BOARDS	16
#घोषणा MAX_DEVICES		(NR_CHANNELS * IPOCTAL_MAX_BOARDS)

/**
 * काष्ठा ipoctal_stats -- Stats since last reset
 *
 * @tx: Number of transmitted bytes
 * @rx: Number of received bytes
 * @overrun: Number of overrun errors
 * @parity_err: Number of parity errors
 * @framing_err: Number of framing errors
 * @rcv_अवरोध: Number of अवरोध received
 */
काष्ठा ipoctal_stats अणु
	अचिन्हित दीर्घ tx;
	अचिन्हित दीर्घ rx;
	अचिन्हित दीर्घ overrun_err;
	अचिन्हित दीर्घ parity_err;
	अचिन्हित दीर्घ framing_err;
	अचिन्हित दीर्घ rcv_अवरोध;
पूर्ण;

#पूर्ण_अगर /* _IPOCTAL_H_ */
