<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *
 * Copyright (C) 2013 Citrix Systems
 *
 * Author: Stefano Stabellini <stefano.stabellini@eu.citrix.com>
 */

#समावेश <linux/export.h>
#समावेश <linux/jump_label.h>
#समावेश <linux/types.h>
#समावेश <linux/अटल_call.h>
#समावेश <यंत्र/paravirt.h>

काष्ठा अटल_key paravirt_steal_enabled;
काष्ठा अटल_key paravirt_steal_rq_enabled;

अटल u64 native_steal_घड़ी(पूर्णांक cpu)
अणु
	वापस 0;
पूर्ण

DEFINE_STATIC_CALL(pv_steal_घड़ी, native_steal_घड़ी);
