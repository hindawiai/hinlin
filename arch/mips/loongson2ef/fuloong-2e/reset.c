<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* Board-specअगरic reboot/shutकरोwn routines
 * Copyright (c) 2009 Philippe Vachon <philippe@cowpig.ca>
 *
 * Copyright (C) 2009 Lemote Inc.
 * Author: Wu Zhangjin, wuzhangjin@gmail.com
 */

#समावेश <loongson.h>

व्योम mach_prepare_reboot(व्योम)
अणु
	LOONGSON_GENCFG &= ~(1 << 2);
	LOONGSON_GENCFG |= (1 << 2);
पूर्ण

व्योम mach_prepare_shutकरोwn(व्योम)
अणु
पूर्ण
