<शैली गुरु>
/**********************************************************************
 * Author: Cavium, Inc.
 *
 * Contact: support@cavium.com
 *          Please include "LiquidIO" in the subject.
 *
 * Copyright (c) 2003-2016 Cavium, Inc.
 *
 * This file is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License, Version 2, as
 * published by the Free Software Foundation.
 *
 * This file is distributed in the hope that it will be useful, but
 * AS-IS and WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE, TITLE, or
 * NONINFRINGEMENT.  See the GNU General Public License क्रम more details.
 ***********************************************************************/
/*! \पile cn68xx_regs.h
 *  \मrief Host Driver: Register Address and Register Mask values क्रम
 *  Octeon CN68XX devices. The रेजिस्टर map क्रम CN66XX is the same
 *  क्रम most रेजिस्टरs. This file has the other रेजिस्टरs that are
 *  68XX-specअगरic.
 */

#अगर_अघोषित __CN68XX_REGS_H__
#घोषणा __CN68XX_REGS_H__

/*###################### REQUEST QUEUE #########################*/

#घोषणा    CN68XX_SLI_IQ_PORT0_PKIND             0x0800

#घोषणा    CN68XX_SLI_IQ_PORT_PKIND(iq)           \
	(CN68XX_SLI_IQ_PORT0_PKIND + ((iq) * CN6XXX_IQ_OFFSET))

/*############################ OUTPUT QUEUE #########################*/

/* Starting pipe number and number of pipes used by the SLI packet output. */
#घोषणा    CN68XX_SLI_TX_PIPE                    0x1230

/*######################## INTERRUPTS #########################*/

/*------------------ Interrupt Masks ----------------*/
#घोषणा    CN68XX_INTR_PIPE_ERR                  BIT_ULL(61)

#पूर्ण_अगर
