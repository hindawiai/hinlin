<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Gas Gauge driver क्रम SBS Compliant Gas Gauges
 *
 * Copyright (c) 2010, NVIDIA Corporation.
 */

#अगर_अघोषित __LINUX_POWER_SBS_BATTERY_H_
#घोषणा __LINUX_POWER_SBS_BATTERY_H_

#समावेश <linux/घातer_supply.h>
#समावेश <linux/types.h>

/**
 * काष्ठा sbs_platक्रमm_data - platक्रमm data क्रम sbs devices
 * @i2c_retry_count:		# of बार to retry on i2c IO failure
 * @poll_retry_count:		# of बार to retry looking क्रम new status after
 *				बाह्यal change notअगरication
 */
काष्ठा sbs_platक्रमm_data अणु
	u32 i2c_retry_count;
	u32 poll_retry_count;
पूर्ण;

#पूर्ण_अगर
