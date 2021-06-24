<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Host1x init क्रम Tegra124 SoCs
 *
 * Copyright (c) 2013 NVIDIA Corporation.
 */

/* include hw specअगरication */
#समावेश "host1x04.h"
#समावेश "host1x04_hardware.h"

/* include code */
#घोषणा HOST1X_HW 4

#समावेश "cdma_hw.c"
#समावेश "channel_hw.c"
#समावेश "debug_hw.c"
#समावेश "intr_hw.c"
#समावेश "syncpt_hw.c"

#समावेश "../dev.h"

पूर्णांक host1x04_init(काष्ठा host1x *host)
अणु
	host->channel_op = &host1x_channel_ops;
	host->cdma_op = &host1x_cdma_ops;
	host->cdma_pb_op = &host1x_pushbuffer_ops;
	host->syncpt_op = &host1x_syncpt_ops;
	host->पूर्णांकr_op = &host1x_पूर्णांकr_ops;
	host->debug_op = &host1x_debug_ops;

	वापस 0;
पूर्ण
