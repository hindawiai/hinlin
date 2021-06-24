<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Copyright (C) 2014 Alexander Shiyan <shc_work@mail.ru>
 */

#समावेश <linux/of_platक्रमm.h>
#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach/map.h>

#समावेश "common.h"
#समावेश "hardware.h"

#घोषणा MX1_AVIC_ADDR	0x00223000

अटल व्योम __init imx1_init_early(व्योम)
अणु
	mxc_set_cpu_type(MXC_CPU_MX1);
पूर्ण

अटल स्थिर अक्षर * स्थिर imx1_dt_board_compat[] __initस्थिर = अणु
	"fsl,imx1",
	शून्य
पूर्ण;

DT_MACHINE_START(IMX1_DT, "Freescale i.MX1 (Device Tree Support)")
	.init_early	= imx1_init_early,
	.dt_compat	= imx1_dt_board_compat,
	.restart	= mxc_restart,
MACHINE_END
