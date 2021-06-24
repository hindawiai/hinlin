<शैली गुरु>
/*
 * Test क्रम the regression पूर्णांकroduced by
 *
 * b9470c27607b ("inet: kill smallest_size and smallest_port")
 *
 * If we खोलो an ipv4 socket on a port with reuseaddr we shouldn't reset the tb
 * when we खोलो the ipv6 conterpart, which is what was happening previously.
 */
#समावेश <त्रुटिसं.स>
#समावेश <error.h>
#समावेश <arpa/inet.h>
#समावेश <netinet/in.h>
#समावेश <stdbool.h>
#समावेश <मानकपन.स>
#समावेश <sys/socket.h>
#समावेश <sys/types.h>
#समावेश <unistd.h>

#घोषणा PORT 9999

पूर्णांक खोलो_port(पूर्णांक ipv6, पूर्णांक any)
अणु
	पूर्णांक fd = -1;
	पूर्णांक reuseaddr = 1;
	पूर्णांक v6only = 1;
	पूर्णांक addrlen;
	पूर्णांक ret = -1;
	काष्ठा sockaddr *addr;
	पूर्णांक family = ipv6 ? AF_INET6 : AF_INET;

	काष्ठा sockaddr_in6 addr6 = अणु
		.sin6_family = AF_INET6,
		.sin6_port = htons(PORT),
		.sin6_addr = in6addr_any
	पूर्ण;
	काष्ठा sockaddr_in addr4 = अणु
		.sin_family = AF_INET,
		.sin_port = htons(PORT),
		.sin_addr.s_addr = any ? htonl(INADDR_ANY) : inet_addr("127.0.0.1"),
	पूर्ण;


	अगर (ipv6) अणु
		addr = (काष्ठा sockaddr*)&addr6;
		addrlen = माप(addr6);
	पूर्ण अन्यथा अणु
		addr = (काष्ठा sockaddr*)&addr4;
		addrlen = माप(addr4);
	पूर्ण

	अगर ((fd = socket(family, SOCK_STREAM, IPPROTO_TCP)) < 0) अणु
		लिखो_त्रुटि("socket");
		जाओ out;
	पूर्ण

	अगर (ipv6 && setsockopt(fd, IPPROTO_IPV6, IPV6_V6ONLY, (व्योम*)&v6only,
			       माप(v6only)) < 0) अणु
		लिखो_त्रुटि("setsockopt IPV6_V6ONLY");
		जाओ out;
	पूर्ण

	अगर (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &reuseaddr,
		       माप(reuseaddr)) < 0) अणु
		लिखो_त्रुटि("setsockopt SO_REUSEADDR");
		जाओ out;
	पूर्ण

	अगर (bind(fd, addr, addrlen) < 0) अणु
		लिखो_त्रुटि("bind");
		जाओ out;
	पूर्ण

	अगर (any)
		वापस fd;

	अगर (listen(fd, 1) < 0) अणु
		लिखो_त्रुटि("listen");
		जाओ out;
	पूर्ण
	वापस fd;
out:
	बंद(fd);
	वापस ret;
पूर्ण

पूर्णांक मुख्य(व्योम)
अणु
	पूर्णांक listenfd;
	पूर्णांक fd1, fd2;

	ख_लिखो(मानक_त्रुटि, "Opening 127.0.0.1:%d\n", PORT);
	listenfd = खोलो_port(0, 0);
	अगर (listenfd < 0)
		error(1, त्रुटि_सं, "Couldn't open listen socket");
	ख_लिखो(मानक_त्रुटि, "Opening INADDR_ANY:%d\n", PORT);
	fd1 = खोलो_port(0, 1);
	अगर (fd1 >= 0)
		error(1, 0, "Was allowed to create an ipv4 reuseport on a already bound non-reuseport socket");
	ख_लिखो(मानक_त्रुटि, "Opening in6addr_any:%d\n", PORT);
	fd1 = खोलो_port(1, 1);
	अगर (fd1 < 0)
		error(1, त्रुटि_सं, "Couldn't open ipv6 reuseport");
	ख_लिखो(मानक_त्रुटि, "Opening INADDR_ANY:%d\n", PORT);
	fd2 = खोलो_port(0, 1);
	अगर (fd2 >= 0)
		error(1, 0, "Was allowed to create an ipv4 reuseport on a already bound non-reuseport socket");
	बंद(fd1);
	ख_लिखो(मानक_त्रुटि, "Opening INADDR_ANY:%d after closing ipv6 socket\n", PORT);
	fd1 = खोलो_port(0, 1);
	अगर (fd1 >= 0)
		error(1, 0, "Was allowed to create an ipv4 reuseport on an already bound non-reuseport socket with no ipv6");
	ख_लिखो(मानक_त्रुटि, "Success");
	वापस 0;
पूर्ण
