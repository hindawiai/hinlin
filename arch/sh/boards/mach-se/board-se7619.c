<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * arch/sh/boards/se/7619/setup.c
 *
 * Copyright (C) 2006 Yoshinori Sato
 *
 * Hitachi SH7619 SolutionEngine Support.
 */

#समावेश <linux/init.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/machvec.h>

अटल पूर्णांक se7619_mode_pins(व्योम)
अणु
	वापस MODE_PIN2 | MODE_PIN0;
पूर्ण

/*
 * The Machine Vector
 */

अटल काष्ठा sh_machine_vector mv_se __iniपंचांगv = अणु
	.mv_name		= "SolutionEngine",
	.mv_mode_pins		= se7619_mode_pins,
पूर्ण;
