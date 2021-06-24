<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2020, Red Hat, Inc.
 */
#समावेश "kvm_util.h"

काष्ठा guest_mode अणु
	bool supported;
	bool enabled;
पूर्ण;

बाह्य काष्ठा guest_mode guest_modes[NUM_VM_MODES];

#घोषणा guest_mode_append(mode, supported, enabled) (अणु \
	guest_modes[mode] = (काष्ठा guest_mode)अणु supported, enabled पूर्ण; \
पूर्ण)

व्योम guest_modes_append_शेष(व्योम);
व्योम क्रम_each_guest_mode(व्योम (*func)(क्रमागत vm_guest_mode, व्योम *), व्योम *arg);
व्योम guest_modes_help(व्योम);
व्योम guest_modes_cmdline(स्थिर अक्षर *arg);
