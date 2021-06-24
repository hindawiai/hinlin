<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) ST-Ericsson SA 2010
 * Author: Shujuan Chen <shujuan.chen@stericsson.com> क्रम ST-Ericsson.
 * Author: Jonas Linde <jonas.linde@stericsson.com> क्रम ST-Ericsson.
 * Author: Joakim Bech <joakim.xx.bech@stericsson.com> क्रम ST-Ericsson.
 * Author: Berne Hebark <berne.herbark@stericsson.com> क्रम ST-Ericsson.
 * Author: Niklas Hernaeus <niklas.hernaeus@stericsson.com> क्रम ST-Ericsson.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/biपंचांगap.h>
#समावेश <linux/device.h>

#समावेश "cryp.h"
#समावेश "cryp_p.h"
#समावेश "cryp_irq.h"
#समावेश "cryp_irqp.h"

व्योम cryp_enable_irq_src(काष्ठा cryp_device_data *device_data, u32 irq_src)
अणु
	u32 i;

	dev_dbg(device_data->dev, "[%s]", __func__);

	i = पढ़ोl_relaxed(&device_data->base->imsc);
	i = i | irq_src;
	ग_लिखोl_relaxed(i, &device_data->base->imsc);
पूर्ण

व्योम cryp_disable_irq_src(काष्ठा cryp_device_data *device_data, u32 irq_src)
अणु
	u32 i;

	dev_dbg(device_data->dev, "[%s]", __func__);

	i = पढ़ोl_relaxed(&device_data->base->imsc);
	i = i & ~irq_src;
	ग_लिखोl_relaxed(i, &device_data->base->imsc);
पूर्ण

bool cryp_pending_irq_src(काष्ठा cryp_device_data *device_data, u32 irq_src)
अणु
	वापस (पढ़ोl_relaxed(&device_data->base->mis) & irq_src) > 0;
पूर्ण
