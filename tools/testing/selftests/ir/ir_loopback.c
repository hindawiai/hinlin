<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// test ir decoder
//
// Copyright (C) 2018 Sean Young <sean@mess.org>

// When sending LIRC_MODE_SCANCODE, the IR will be encoded. rc-loopback
// will send this IR to the receiver side, where we try to पढ़ो the decoded
// IR. Decoding happens in a separate kernel thपढ़ो, so we will need to
// रुको until that is scheduled, hence we use poll to check क्रम पढ़ो
// पढ़ोiness.

#समावेश <linux/lirc.h>
#समावेश <त्रुटिसं.स>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <stdbool.h>
#समावेश <माला.स>
#समावेश <unistd.h>
#समावेश <poll.h>
#समावेश <समय.स>
#समावेश <sys/types.h>
#समावेश <sys/ioctl.h>
#समावेश <dirent.h>
#समावेश <sys/स्थिति.स>
#समावेश <fcntl.h>
#समावेश "../kselftest.h"

#घोषणा TEST_SCANCODES	10
#घोषणा ARRAY_SIZE(arr) (माप(arr) / माप((arr)[0]))
#घोषणा SYSFS_PATH_MAX 256
#घोषणा DNAME_PATH_MAX 256

अटल स्थिर काष्ठा अणु
	क्रमागत rc_proto proto;
	स्थिर अक्षर *name;
	अचिन्हित पूर्णांक mask;
	स्थिर अक्षर *decoder;
पूर्ण protocols[] = अणु
	अणु RC_PROTO_RC5, "rc-5", 0x1f7f, "rc-5" पूर्ण,
	अणु RC_PROTO_RC5X_20, "rc-5x-20", 0x1f7f3f, "rc-5" पूर्ण,
	अणु RC_PROTO_RC5_SZ, "rc-5-sz", 0x2fff, "rc-5-sz" पूर्ण,
	अणु RC_PROTO_JVC, "jvc", 0xffff, "jvc" पूर्ण,
	अणु RC_PROTO_SONY12, "sony-12", 0x1f007f, "sony" पूर्ण,
	अणु RC_PROTO_SONY15, "sony-15", 0xff007f, "sony" पूर्ण,
	अणु RC_PROTO_SONY20, "sony-20", 0x1fff7f, "sony" पूर्ण,
	अणु RC_PROTO_NEC, "nec", 0xffff, "nec" पूर्ण,
	अणु RC_PROTO_NECX, "nec-x", 0xffffff, "nec" पूर्ण,
	अणु RC_PROTO_NEC32, "nec-32", 0xffffffff, "nec" पूर्ण,
	अणु RC_PROTO_SANYO, "sanyo", 0x1fffff, "sanyo" पूर्ण,
	अणु RC_PROTO_RC6_0, "rc-6-0", 0xffff, "rc-6" पूर्ण,
	अणु RC_PROTO_RC6_6A_20, "rc-6-6a-20", 0xfffff, "rc-6" पूर्ण,
	अणु RC_PROTO_RC6_6A_24, "rc-6-6a-24", 0xffffff, "rc-6" पूर्ण,
	अणु RC_PROTO_RC6_6A_32, "rc-6-6a-32", 0xffffffff, "rc-6" पूर्ण,
	अणु RC_PROTO_RC6_MCE, "rc-6-mce", 0x00007fff, "rc-6" पूर्ण,
	अणु RC_PROTO_SHARP, "sharp", 0x1fff, "sharp" पूर्ण,
	अणु RC_PROTO_IMON, "imon", 0x7fffffff, "imon" पूर्ण,
	अणु RC_PROTO_RCMM12, "rcmm-12", 0x00000fff, "rc-mm" पूर्ण,
	अणु RC_PROTO_RCMM24, "rcmm-24", 0x00ffffff, "rc-mm" पूर्ण,
	अणु RC_PROTO_RCMM32, "rcmm-32", 0xffffffff, "rc-mm" पूर्ण,
पूर्ण;

पूर्णांक lirc_खोलो(स्थिर अक्षर *rc)
अणु
	काष्ठा dirent *dent;
	अक्षर buf[SYSFS_PATH_MAX + DNAME_PATH_MAX];
	सूची *d;
	पूर्णांक fd;

	snम_लिखो(buf, माप(buf), "/sys/class/rc/%s", rc);

	d = सूची_खोलो(buf);
	अगर (!d)
		ksft_निकास_fail_msg("cannot open %s: %m\n", buf);

	जबतक ((dent = सूची_पढ़ो(d)) != शून्य) अणु
		अगर (!म_भेदन(dent->d_name, "lirc", 4)) अणु
			snम_लिखो(buf, माप(buf), "/dev/%s", dent->d_name);
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!dent)
		ksft_निकास_skip("cannot find lirc device for %s\n", rc);

	बंद_सूची(d);

	fd = खोलो(buf, O_RDWR | O_NONBLOCK);
	अगर (fd == -1)
		ksft_निकास_fail_msg("cannot open: %s: %m\n", buf);

	वापस fd;
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	अचिन्हित पूर्णांक mode;
	अक्षर buf[100];
	पूर्णांक rlircfd, wlircfd, protocolfd, i, n;

	बेक्रम(समय(शून्य));

	अगर (argc != 3)
		ksft_निकास_fail_msg("Usage: %s <write rcN> <read rcN>\n",
				   argv[0]);

	rlircfd = lirc_खोलो(argv[2]);
	mode = LIRC_MODE_SCANCODE;
	अगर (ioctl(rlircfd, LIRC_SET_REC_MODE, &mode))
		ksft_निकास_fail_msg("failed to set scancode rec mode %s: %m\n",
				   argv[2]);

	wlircfd = lirc_खोलो(argv[1]);
	अगर (ioctl(wlircfd, LIRC_SET_SEND_MODE, &mode))
		ksft_निकास_fail_msg("failed to set scancode send mode %s: %m\n",
				   argv[1]);

	snम_लिखो(buf, माप(buf), "/sys/class/rc/%s/protocols", argv[2]);
	protocolfd = खोलो(buf, O_WRONLY);
	अगर (protocolfd == -1)
		ksft_निकास_fail_msg("failed to open %s: %m\n", buf);

	म_लिखो("Sending IR on %s and receiving IR on %s.\n", argv[1], argv[2]);

	क्रम (i = 0; i < ARRAY_SIZE(protocols); i++) अणु
		अगर (ग_लिखो(protocolfd, protocols[i].decoder,
			  म_माप(protocols[i].decoder)) == -1)
			ksft_निकास_fail_msg("failed to set write decoder\n");

		म_लिखो("Testing protocol %s for decoder %s (%d/%d)...\n",
		       protocols[i].name, protocols[i].decoder,
		       i + 1, (पूर्णांक)ARRAY_SIZE(protocols));

		क्रम (n = 0; n < TEST_SCANCODES; n++) अणु
			अचिन्हित पूर्णांक scancode = अक्रम() & protocols[i].mask;
			अचिन्हित पूर्णांक rc_proto = protocols[i].proto;

			अगर (rc_proto == RC_PROTO_RC6_MCE)
				scancode |= 0x800f0000;

			अगर (rc_proto == RC_PROTO_NECX &&
			    (((scancode >> 16) ^ ~(scancode >> 8)) & 0xff) == 0)
				जारी;

			अगर (rc_proto == RC_PROTO_NEC32 &&
			    (((scancode >> 8) ^ ~scancode) & 0xff) == 0)
				जारी;

			अगर (rc_proto == RC_PROTO_RCMM32 &&
			    (scancode & 0x000c0000) != 0x000c0000 &&
			    scancode & 0x00008000)
				जारी;

			काष्ठा lirc_scancode lsc = अणु
				.rc_proto = rc_proto,
				.scancode = scancode
			पूर्ण;

			म_लिखो("Testing scancode:%x\n", scancode);

			जबतक (ग_लिखो(wlircfd, &lsc, माप(lsc)) < 0) अणु
				अगर (त्रुटि_सं == EINTR)
					जारी;

				ksft_निकास_fail_msg("failed to send ir: %m\n");
			पूर्ण

			काष्ठा pollfd pfd = अणु .fd = rlircfd, .events = POLLIN पूर्ण;
			काष्ठा lirc_scancode lsc2;

			poll(&pfd, 1, 1000);

			bool decoded = true;

			जबतक (पढ़ो(rlircfd, &lsc2, माप(lsc2)) < 0) अणु
				अगर (त्रुटि_सं == EINTR)
					जारी;

				ksft_test_result_error("no scancode decoded: %m\n");
				decoded = false;
				अवरोध;
			पूर्ण

			अगर (!decoded)
				जारी;

			अगर (lsc.rc_proto != lsc2.rc_proto)
				ksft_test_result_error("decoded protocol is different: %d\n",
						       lsc2.rc_proto);

			अन्यथा अगर (lsc.scancode != lsc2.scancode)
				ksft_test_result_error("decoded scancode is different: %llx\n",
						       lsc2.scancode);
			अन्यथा
				ksft_inc_pass_cnt();
		पूर्ण

		म_लिखो("OK\n");
	पूर्ण

	बंद(rlircfd);
	बंद(wlircfd);
	बंद(protocolfd);

	अगर (ksft_get_fail_cnt() > 0)
		ksft_निकास_fail();
	अन्यथा
		ksft_निकास_pass();

	वापस 0;
पूर्ण
