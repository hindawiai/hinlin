<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) ST-Ericsson SA 2010
 * Author: Shujuan Chen <shujuan.chen@stericsson.com> क्रम ST-Ericsson.
 * Author: Jonas Linde <jonas.linde@stericsson.com> क्रम ST-Ericsson.
 * Author: Joakim Bech <joakim.xx.bech@stericsson.com> क्रम ST-Ericsson.
 * Author: Berne Hebark <berne.herbark@stericsson.com> क्रम ST-Ericsson.
 * Author: Niklas Hernaeus <niklas.hernaeus@stericsson.com> क्रम ST-Ericsson.
 */

#अगर_अघोषित _CRYP_IRQ_H_
#घोषणा _CRYP_IRQ_H_

#समावेश "cryp.h"

क्रमागत cryp_irq_src_id अणु
	CRYP_IRQ_SRC_INPUT_FIFO = 0x1,
	CRYP_IRQ_SRC_OUTPUT_FIFO = 0x2,
	CRYP_IRQ_SRC_ALL = 0x3
पूर्ण;

/*
 * M0 Funtions
 */
व्योम cryp_enable_irq_src(काष्ठा cryp_device_data *device_data, u32 irq_src);

व्योम cryp_disable_irq_src(काष्ठा cryp_device_data *device_data, u32 irq_src);

bool cryp_pending_irq_src(काष्ठा cryp_device_data *device_data, u32 irq_src);

#पूर्ण_अगर				/* _CRYP_IRQ_H_ */
