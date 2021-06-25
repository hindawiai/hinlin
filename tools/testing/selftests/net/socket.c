<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <मानकपन.स>
#समावेश <त्रुटिसं.स>
#समावेश <unistd.h>
#समावेश <माला.स>
#समावेश <sys/types.h>
#समावेश <sys/socket.h>
#समावेश <netinet/in.h>

काष्ठा socket_testहाल अणु
	पूर्णांक	करोमुख्य;
	पूर्णांक	type;
	पूर्णांक	protocol;

	/* 0    = valid file descriptor
	 * -foo = error foo
	 */
	पूर्णांक	expect;

	/* If non-zero, accept EAFNOSUPPORT to handle the हाल
	 * of the protocol not being configured पूर्णांकo the kernel.
	 */
	पूर्णांक	nosupport_ok;
पूर्ण;

अटल काष्ठा socket_testहाल tests[] = अणु
	अणु AF_MAX,  0,           0,           -EAFNOSUPPORT,    0 पूर्ण,
	अणु AF_INET, SOCK_STREAM, IPPROTO_TCP, 0,                1  पूर्ण,
	अणु AF_INET, SOCK_DGRAM,  IPPROTO_TCP, -EPROTONOSUPPORT, 1  पूर्ण,
	अणु AF_INET, SOCK_DGRAM,  IPPROTO_UDP, 0,                1  पूर्ण,
	अणु AF_INET, SOCK_STREAM, IPPROTO_UDP, -EPROTONOSUPPORT, 1  पूर्ण,
पूर्ण;

#घोषणा ARRAY_SIZE(arr) (माप(arr) / माप((arr)[0]))
#घोषणा ERR_STRING_SZ	64

अटल पूर्णांक run_tests(व्योम)
अणु
	अक्षर err_string1[ERR_STRING_SZ];
	अक्षर err_string2[ERR_STRING_SZ];
	पूर्णांक i, err;

	err = 0;
	क्रम (i = 0; i < ARRAY_SIZE(tests); i++) अणु
		काष्ठा socket_testहाल *s = &tests[i];
		पूर्णांक fd;

		fd = socket(s->करोमुख्य, s->type, s->protocol);
		अगर (fd < 0) अणु
			अगर (s->nosupport_ok &&
			    त्रुटि_सं == EAFNOSUPPORT)
				जारी;

			अगर (s->expect < 0 &&
			    त्रुटि_सं == -s->expect)
				जारी;

			म_त्रुटि_r(-s->expect, err_string1, ERR_STRING_SZ);
			म_त्रुटि_r(त्रुटि_सं, err_string2, ERR_STRING_SZ);

			ख_लिखो(मानक_त्रुटि, "socket(%d, %d, %d) expected "
				"err (%s) got (%s)\n",
				s->करोमुख्य, s->type, s->protocol,
				err_string1, err_string2);

			err = -1;
			अवरोध;
		पूर्ण अन्यथा अणु
			बंद(fd);

			अगर (s->expect < 0) अणु
				म_त्रुटि_r(त्रुटि_सं, err_string1, ERR_STRING_SZ);

				ख_लिखो(मानक_त्रुटि, "socket(%d, %d, %d) expected "
					"success got err (%s)\n",
					s->करोमुख्य, s->type, s->protocol,
					err_string1);

				err = -1;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस err;
पूर्ण

पूर्णांक मुख्य(व्योम)
अणु
	पूर्णांक err = run_tests();

	वापस err;
पूर्ण
