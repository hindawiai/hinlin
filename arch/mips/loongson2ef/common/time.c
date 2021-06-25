<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2007 Lemote, Inc. & Institute of Computing Technology
 * Author: Fuxin Zhang, zhangfx@lemote.com
 *
 * Copyright (C) 2009 Lemote Inc.
 * Author: Wu Zhangjin, wuzhangjin@gmail.com
 */
#समावेश <यंत्र/mc146818-समय.स>
#समावेश <यंत्र/समय.स>
#समावेश <यंत्र/hpet.h>

#समावेश <loongson.h>
#समावेश <cs5536/cs5536_mfgpt.h>

व्योम __init plat_समय_init(व्योम)
अणु
	/* setup mips r4k समयr */
	mips_hpt_frequency = cpu_घड़ी_freq / 2;

	setup_mfgpt0_समयr();
पूर्ण

व्योम पढ़ो_persistent_घड़ी64(काष्ठा बारpec64 *ts)
अणु
	ts->tv_sec = mc146818_get_cmos_समय();
	ts->tv_nsec = 0;
पूर्ण
