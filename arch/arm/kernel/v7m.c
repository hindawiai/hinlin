<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2013 Uwe Kleine-Koenig क्रम Pengutronix
 */
#समावेश <linux/पन.स>
#समावेश <linux/reboot.h>
#समावेश <यंत्र/barrier.h>
#समावेश <यंत्र/v7m.h>

व्योम armv7m_restart(क्रमागत reboot_mode mode, स्थिर अक्षर *cmd)
अणु
	dsb();
	__raw_ग_लिखोl(V7M_SCB_AIRCR_VECTKEY | V7M_SCB_AIRCR_SYSRESETREQ,
			BASEADDR_V7M_SCB + V7M_SCB_AIRCR);
	dsb();
पूर्ण
