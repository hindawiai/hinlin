<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Use watch_queue API to watch क्रम notअगरications.
 *
 * Copyright (C) 2020 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */

#घोषणा _GNU_SOURCE
#समावेश <stdbool.h>
#समावेश <मानकतर्क.स>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <संकेत.स>
#समावेश <unistd.h>
#समावेश <त्रुटिसं.स>
#समावेश <sys/ioctl.h>
#समावेश <सीमा.स>
#समावेश <linux/watch_queue.h>
#समावेश <linux/unistd.h>
#समावेश <linux/keyctl.h>

#अगर_अघोषित KEYCTL_WATCH_KEY
#घोषणा KEYCTL_WATCH_KEY -1
#पूर्ण_अगर
#अगर_अघोषित __NR_keyctl
#घोषणा __NR_keyctl -1
#पूर्ण_अगर

#घोषणा BUF_SIZE 256

अटल दीर्घ keyctl_watch_key(पूर्णांक key, पूर्णांक watch_fd, पूर्णांक watch_id)
अणु
	वापस syscall(__NR_keyctl, KEYCTL_WATCH_KEY, key, watch_fd, watch_id);
पूर्ण

अटल स्थिर अक्षर *key_subtypes[256] = अणु
	[NOTIFY_KEY_INSTANTIATED]	= "instantiated",
	[NOTIFY_KEY_UPDATED]		= "updated",
	[NOTIFY_KEY_LINKED]		= "linked",
	[NOTIFY_KEY_UNLINKED]		= "unlinked",
	[NOTIFY_KEY_CLEARED]		= "cleared",
	[NOTIFY_KEY_REVOKED]		= "revoked",
	[NOTIFY_KEY_INVALIDATED]	= "invalidated",
	[NOTIFY_KEY_SETATTR]		= "setattr",
पूर्ण;

अटल व्योम saw_key_change(काष्ठा watch_notअगरication *n, माप_प्रकार len)
अणु
	काष्ठा key_notअगरication *k = (काष्ठा key_notअगरication *)n;

	अगर (len != माप(काष्ठा key_notअगरication)) अणु
		ख_लिखो(मानक_त्रुटि, "Incorrect key message length\n");
		वापस;
	पूर्ण

	म_लिखो("KEY %08x change=%u[%s] aux=%u\n",
	       k->key_id, n->subtype, key_subtypes[n->subtype], k->aux);
पूर्ण

/*
 * Consume and display events.
 */
अटल व्योम consumer(पूर्णांक fd)
अणु
	अचिन्हित अक्षर buffer[433], *p, *end;
	जोड़ अणु
		काष्ठा watch_notअगरication n;
		अचिन्हित अक्षर buf1[128];
	पूर्ण n;
	sमाप_प्रकार buf_len;

	क्रम (;;) अणु
		buf_len = पढ़ो(fd, buffer, माप(buffer));
		अगर (buf_len == -1) अणु
			लिखो_त्रुटि("read");
			निकास(1);
		पूर्ण

		अगर (buf_len == 0) अणु
			म_लिखो("-- END --\n");
			वापस;
		पूर्ण

		अगर (buf_len > माप(buffer)) अणु
			ख_लिखो(मानक_त्रुटि, "Read buffer overrun: %zd\n", buf_len);
			वापस;
		पूर्ण

		म_लिखो("read() = %zd\n", buf_len);

		p = buffer;
		end = buffer + buf_len;
		जबतक (p < end) अणु
			माप_प्रकार largest, len;

			largest = end - p;
			अगर (largest > 128)
				largest = 128;
			अगर (largest < माप(काष्ठा watch_notअगरication)) अणु
				ख_लिखो(मानक_त्रुटि, "Short message header: %zu\n", largest);
				वापस;
			पूर्ण
			स_नकल(&n, p, largest);

			म_लिखो("NOTIFY[%03zx]: ty=%06x sy=%02x i=%08x\n",
			       p - buffer, n.n.type, n.n.subtype, n.n.info);

			len = n.n.info & WATCH_INFO_LENGTH;
			अगर (len < माप(n.n) || len > largest) अणु
				ख_लिखो(मानक_त्रुटि, "Bad message length: %zu/%zu\n", len, largest);
				निकास(1);
			पूर्ण

			चयन (n.n.type) अणु
			हाल WATCH_TYPE_META:
				चयन (n.n.subtype) अणु
				हाल WATCH_META_REMOVAL_NOTIFICATION:
					म_लिखो("REMOVAL of watchpoint %08x\n",
					       (n.n.info & WATCH_INFO_ID) >>
					       WATCH_INFO_ID__SHIFT);
					अवरोध;
				हाल WATCH_META_LOSS_NOTIFICATION:
					म_लिखो("-- LOSS --\n");
					अवरोध;
				शेष:
					म_लिखो("other meta record\n");
					अवरोध;
				पूर्ण
				अवरोध;
			हाल WATCH_TYPE_KEY_NOTIFY:
				saw_key_change(&n.n, len);
				अवरोध;
			शेष:
				म_लिखो("other type\n");
				अवरोध;
			पूर्ण

			p += len;
		पूर्ण
	पूर्ण
पूर्ण

अटल काष्ठा watch_notअगरication_filter filter = अणु
	.nr_filters	= 1,
	.filters = अणु
		[0]	= अणु
			.type			= WATCH_TYPE_KEY_NOTIFY,
			.subtype_filter[0]	= अच_पूर्णांक_उच्च,
		पूर्ण,
	पूर्ण,
पूर्ण;

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	पूर्णांक pipefd[2], fd;

	अगर (pipe2(pipefd, O_NOTIFICATION_PIPE) == -1) अणु
		लिखो_त्रुटि("pipe2");
		निकास(1);
	पूर्ण
	fd = pipefd[0];

	अगर (ioctl(fd, IOC_WATCH_QUEUE_SET_SIZE, BUF_SIZE) == -1) अणु
		लिखो_त्रुटि("watch_queue(size)");
		निकास(1);
	पूर्ण

	अगर (ioctl(fd, IOC_WATCH_QUEUE_SET_FILTER, &filter) == -1) अणु
		लिखो_त्रुटि("watch_queue(filter)");
		निकास(1);
	पूर्ण

	अगर (keyctl_watch_key(KEY_SPEC_SESSION_KEYRING, fd, 0x01) == -1) अणु
		लिखो_त्रुटि("keyctl");
		निकास(1);
	पूर्ण

	अगर (keyctl_watch_key(KEY_SPEC_USER_KEYRING, fd, 0x02) == -1) अणु
		लिखो_त्रुटि("keyctl");
		निकास(1);
	पूर्ण

	consumer(fd);
	निकास(0);
पूर्ण
