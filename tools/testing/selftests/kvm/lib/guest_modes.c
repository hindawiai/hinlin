<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2020, Red Hat, Inc.
 */
#समावेश "guest_modes.h"

काष्ठा guest_mode guest_modes[NUM_VM_MODES];

व्योम guest_modes_append_शेष(व्योम)
अणु
	guest_mode_append(VM_MODE_DEFAULT, true, true);

#अगर_घोषित __aarch64__
	guest_mode_append(VM_MODE_P40V48_64K, true, true);
	अणु
		अचिन्हित पूर्णांक limit = kvm_check_cap(KVM_CAP_ARM_VM_IPA_SIZE);
		अगर (limit >= 52)
			guest_mode_append(VM_MODE_P52V48_64K, true, true);
		अगर (limit >= 48) अणु
			guest_mode_append(VM_MODE_P48V48_4K, true, true);
			guest_mode_append(VM_MODE_P48V48_64K, true, true);
		पूर्ण
	पूर्ण
#पूर्ण_अगर
पूर्ण

व्योम क्रम_each_guest_mode(व्योम (*func)(क्रमागत vm_guest_mode, व्योम *), व्योम *arg)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < NUM_VM_MODES; ++i) अणु
		अगर (!guest_modes[i].enabled)
			जारी;
		TEST_ASSERT(guest_modes[i].supported,
			    "Guest mode ID %d (%s) not supported.",
			    i, vm_guest_mode_string(i));
		func(i, arg);
	पूर्ण
पूर्ण

व्योम guest_modes_help(व्योम)
अणु
	पूर्णांक i;

	म_लिखो(" -m: specify the guest mode ID to test\n"
	       "     (default: test all supported modes)\n"
	       "     This option may be used multiple times.\n"
	       "     Guest mode IDs:\n");
	क्रम (i = 0; i < NUM_VM_MODES; ++i) अणु
		म_लिखो("         %d:    %s%s\n", i, vm_guest_mode_string(i),
		       guest_modes[i].supported ? " (supported)" : "");
	पूर्ण
पूर्ण

व्योम guest_modes_cmdline(स्थिर अक्षर *arg)
अणु
	अटल bool mode_selected;
	अचिन्हित पूर्णांक mode;
	पूर्णांक i;

	अगर (!mode_selected) अणु
		क्रम (i = 0; i < NUM_VM_MODES; ++i)
			guest_modes[i].enabled = false;
		mode_selected = true;
	पूर्ण

	mode = म_से_अदीर्घ(optarg, शून्य, 10);
	TEST_ASSERT(mode < NUM_VM_MODES, "Guest mode ID %d too big", mode);
	guest_modes[mode].enabled = true;
पूर्ण
