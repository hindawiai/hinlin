<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0
 * Copyright (c) 2018 Davide Caratti, Red Hat inc.
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of version 2 of the GNU General Public
 * License as published by the Free Software Foundation.
 */

#समावेश <linux/bpf.h>
#समावेश <linux/pkt_cls.h>

__attribute__((section("action-ok"),used)) पूर्णांक action_ok(काष्ठा __sk_buff *s)
अणु
	वापस TC_ACT_OK;
पूर्ण

__attribute__((section("action-ko"),used)) पूर्णांक action_ko(काष्ठा __sk_buff *s)
अणु
	s->data = 0x0;
	वापस TC_ACT_OK;
पूर्ण

अक्षर _license[] __attribute__((section("license"),used)) = "GPL";
