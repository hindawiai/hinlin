<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// test ir decoder
//
// Copyright (C) 2018 Sean Young <sean@mess.org>

#समावेश <linux/bpf.h>
#समावेश <linux/lirc.h>
#समावेश <bpf/bpf_helpers.h>

SEC("lirc_mode2")
पूर्णांक bpf_decoder(अचिन्हित पूर्णांक *sample)
अणु
	अगर (LIRC_IS_PULSE(*sample)) अणु
		अचिन्हित पूर्णांक duration = LIRC_VALUE(*sample);

		अगर (duration & 0x10000)
			bpf_rc_keyकरोwn(sample, 0x40, duration & 0xffff, 0);
		अगर (duration & 0x20000)
			bpf_rc_poपूर्णांकer_rel(sample, (duration >> 8) & 0xff,
					   duration & 0xff);
	पूर्ण

	वापस 0;
पूर्ण

अक्षर _license[] SEC("license") = "GPL";
