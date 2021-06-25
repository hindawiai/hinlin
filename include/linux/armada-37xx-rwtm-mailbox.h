<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * rWTM BIU Mailbox driver क्रम Armada 37xx
 *
 * Author: Marek Behथजn <kabel@kernel.org>
 */

#अगर_अघोषित _LINUX_ARMADA_37XX_RWTM_MAILBOX_H_
#घोषणा _LINUX_ARMADA_37XX_RWTM_MAILBOX_H_

#समावेश <linux/types.h>

काष्ठा armada_37xx_rwपंचांग_tx_msg अणु
	u16 command;
	u32 args[16];
पूर्ण;

काष्ठा armada_37xx_rwपंचांग_rx_msg अणु
	u32 retval;
	u32 status[16];
पूर्ण;

#पूर्ण_अगर /* _LINUX_ARMADA_37XX_RWTM_MAILBOX_H_ */
