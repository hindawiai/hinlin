<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2014 Carlo Caione <carlo@caione.org>
 */

#समावेश <linux/of_platक्रमm.h>
#समावेश <यंत्र/mach/arch.h>

अटल स्थिर अक्षर * स्थिर meson_common_board_compat[] = अणु
	"amlogic,meson6",
	"amlogic,meson8",
	"amlogic,meson8b",
	"amlogic,meson8m2",
	शून्य,
पूर्ण;

DT_MACHINE_START(MESON, "Amlogic Meson platform")
	.dt_compat	= meson_common_board_compat,
	.l2c_aux_val	= 0,
	.l2c_aux_mask	= ~0,
MACHINE_END
