<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// test ir decoder
//
// Copyright (C) 2018 Sean Young <sean@mess.org>

// A lirc अक्षरdev is a device representing a consumer IR (cir) device which
// can receive infrared संकेतs from remote control and/or transmit IR.
//
// IR is sent as a series of pulses and space somewhat like morse code. The
// BPF program can decode this पूर्णांकo scancodes so that rc-core can translate
// this पूर्णांकo input key codes using the rc keymap.
//
// This test works by sending IR over rc-loopback, so the IR is processed by
// BPF and then decoded पूर्णांकo scancodes. The lirc अक्षरdev must be the one
// associated with rc-loopback, see the output of ir-keytable(1).
//
// The following CONFIG options must be enabled क्रम the test to succeed:
// CONFIG_RC_CORE=y
// CONFIG_BPF_RAWIR_EVENT=y
// CONFIG_RC_LOOPBACK=y

// Steps:
// 1. Open the /dev/lircN device क्रम rc-loopback (given on command line)
// 2. Attach bpf_lirc_mode2 program which decodes some IR.
// 3. Send some IR to the same IR device; since it is loopback, this will
//    end up in the bpf program
// 4. bpf program should decode IR and report keycode
// 5. We can पढ़ो keycode from same /dev/lirc device

#समावेश <linux/bpf.h>
#समावेश <linux/lirc.h>
#समावेश <linux/input.h>
#समावेश <त्रुटिसं.स>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <unistd.h>
#समावेश <poll.h>
#समावेश <sys/types.h>
#समावेश <sys/ioctl.h>
#समावेश <sys/स्थिति.स>
#समावेश <fcntl.h>

#समावेश "bpf_util.h"
#समावेश <bpf/bpf.h>
#समावेश <bpf/libbpf.h>

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	काष्ठा bpf_object *obj;
	पूर्णांक ret, lircfd, progfd, inputfd;
	पूर्णांक testir1 = 0x1dead;
	पूर्णांक testir2 = 0x20101;
	u32 prog_ids[10], prog_flags[10], prog_cnt;

	अगर (argc != 3) अणु
		म_लिखो("Usage: %s /dev/lircN /dev/input/eventM\n", argv[0]);
		वापस 2;
	पूर्ण

	ret = bpf_prog_load("test_lirc_mode2_kern.o",
			    BPF_PROG_TYPE_LIRC_MODE2, &obj, &progfd);
	अगर (ret) अणु
		म_लिखो("Failed to load bpf program\n");
		वापस 1;
	पूर्ण

	lircfd = खोलो(argv[1], O_RDWR | O_NONBLOCK);
	अगर (lircfd == -1) अणु
		म_लिखो("failed to open lirc device %s: %m\n", argv[1]);
		वापस 1;
	पूर्ण

	/* Let's try detach it beक्रमe it was ever attached */
	ret = bpf_prog_detach2(progfd, lircfd, BPF_LIRC_MODE2);
	अगर (ret != -1 || त्रुटि_सं != ENOENT) अणु
		म_लिखो("bpf_prog_detach2 not attached should fail: %m\n");
		वापस 1;
	पूर्ण

	inputfd = खोलो(argv[2], O_RDONLY | O_NONBLOCK);
	अगर (inputfd == -1) अणु
		म_लिखो("failed to open input device %s: %m\n", argv[1]);
		वापस 1;
	पूर्ण

	prog_cnt = 10;
	ret = bpf_prog_query(lircfd, BPF_LIRC_MODE2, 0, prog_flags, prog_ids,
			     &prog_cnt);
	अगर (ret) अणु
		म_लिखो("Failed to query bpf programs on lirc device: %m\n");
		वापस 1;
	पूर्ण

	अगर (prog_cnt != 0) अणु
		म_लिखो("Expected nothing to be attached\n");
		वापस 1;
	पूर्ण

	ret = bpf_prog_attach(progfd, lircfd, BPF_LIRC_MODE2, 0);
	अगर (ret) अणु
		म_लिखो("Failed to attach bpf to lirc device: %m\n");
		वापस 1;
	पूर्ण

	/* Write raw IR */
	ret = ग_लिखो(lircfd, &testir1, माप(testir1));
	अगर (ret != माप(testir1)) अणु
		म_लिखो("Failed to send test IR message: %m\n");
		वापस 1;
	पूर्ण

	काष्ठा pollfd pfd = अणु .fd = inputfd, .events = POLLIN पूर्ण;
	काष्ठा input_event event;

	क्रम (;;) अणु
		poll(&pfd, 1, 100);

		/* Read decoded IR */
		ret = पढ़ो(inputfd, &event, माप(event));
		अगर (ret != माप(event)) अणु
			म_लिखो("Failed to read decoded IR: %m\n");
			वापस 1;
		पूर्ण

		अगर (event.type == EV_MSC && event.code == MSC_SCAN &&
		    event.value == 0xdead) अणु
			अवरोध;
		पूर्ण
	पूर्ण

	/* Write raw IR */
	ret = ग_लिखो(lircfd, &testir2, माप(testir2));
	अगर (ret != माप(testir2)) अणु
		म_लिखो("Failed to send test IR message: %m\n");
		वापस 1;
	पूर्ण

	क्रम (;;) अणु
		poll(&pfd, 1, 100);

		/* Read decoded IR */
		ret = पढ़ो(inputfd, &event, माप(event));
		अगर (ret != माप(event)) अणु
			म_लिखो("Failed to read decoded IR: %m\n");
			वापस 1;
		पूर्ण

		अगर (event.type == EV_REL && event.code == REL_Y &&
		    event.value == 1 ) अणु
			अवरोध;
		पूर्ण
	पूर्ण

	prog_cnt = 10;
	ret = bpf_prog_query(lircfd, BPF_LIRC_MODE2, 0, prog_flags, prog_ids,
			     &prog_cnt);
	अगर (ret) अणु
		म_लिखो("Failed to query bpf programs on lirc device: %m\n");
		वापस 1;
	पूर्ण

	अगर (prog_cnt != 1) अणु
		म_लिखो("Expected one program to be attached\n");
		वापस 1;
	पूर्ण

	/* Let's try detaching it now it is actually attached */
	ret = bpf_prog_detach2(progfd, lircfd, BPF_LIRC_MODE2);
	अगर (ret) अणु
		म_लिखो("bpf_prog_detach2: returned %m\n");
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण
