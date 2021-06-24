<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright 2013 Greg Ungerer <gerg@uclinux.org>
 * Copyright 2011 Freescale Semiconductor, Inc. All Rights Reserved.
 * Copyright 2011 Linaro Ltd.
 */

#समावेश <linux/of_platक्रमm.h>
#समावेश <यंत्र/mach/arch.h>

#समावेश "common.h"

अटल स्थिर अक्षर * स्थिर imx50_dt_board_compat[] __initस्थिर = अणु
	"fsl,imx50",
	शून्य
पूर्ण;

DT_MACHINE_START(IMX50_DT, "Freescale i.MX50 (Device Tree Support)")
	.dt_compat	= imx50_dt_board_compat,
MACHINE_END
