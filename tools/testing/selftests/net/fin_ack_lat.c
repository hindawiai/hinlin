<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#समावेश <arpa/inet.h>
#समावेश <त्रुटिसं.स>
#समावेश <error.h>
#समावेश <netinet/in.h>
#समावेश <netinet/tcp.h>
#समावेश <संकेत.स>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <sys/socket.h>
#समावेश <sys/समय.स>
#समावेश <unistd.h>

अटल पूर्णांक child_pid;

अटल अचिन्हित दीर्घ समयdअगरf(काष्ठा समयval s, काष्ठा समयval e)
अणु
	अचिन्हित दीर्घ s_us, e_us;

	s_us = s.tv_sec * 1000000 + s.tv_usec;
	e_us = e.tv_sec * 1000000 + e.tv_usec;
	अगर (s_us > e_us)
		वापस 0;
	वापस e_us - s_us;
पूर्ण

अटल व्योम client(पूर्णांक port)
अणु
	पूर्णांक sock = 0;
	काष्ठा sockaddr_in addr, laddr;
	socklen_t len = माप(laddr);
	काष्ठा linger sl;
	पूर्णांक flag = 1;
	पूर्णांक buffer;
	काष्ठा समयval start, end;
	अचिन्हित दीर्घ lat, sum_lat = 0, nr_lat = 0;

	जबतक (1) अणु
		समय_लोofday(&start, शून्य);

		sock = socket(AF_INET, SOCK_STREAM, 0);
		अगर (sock < 0)
			error(-1, त्रुटि_सं, "socket creation");

		sl.l_onoff = 1;
		sl.l_linger = 0;
		अगर (setsockopt(sock, SOL_SOCKET, SO_LINGER, &sl, माप(sl)))
			error(-1, त्रुटि_सं, "setsockopt(linger)");

		अगर (setsockopt(sock, IPPROTO_TCP, TCP_NODELAY,
					&flag, माप(flag)))
			error(-1, त्रुटि_सं, "setsockopt(nodelay)");

		addr.sin_family = AF_INET;
		addr.sin_port = htons(port);

		अगर (inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr) <= 0)
			error(-1, त्रुटि_सं, "inet_pton");

		अगर (connect(sock, (काष्ठा sockaddr *)&addr, माप(addr)) < 0)
			error(-1, त्रुटि_सं, "connect");

		send(sock, &buffer, माप(buffer), 0);
		अगर (पढ़ो(sock, &buffer, माप(buffer)) == -1)
			error(-1, त्रुटि_सं, "waiting read");

		समय_लोofday(&end, शून्य);
		lat = समयdअगरf(start, end);
		sum_lat += lat;
		nr_lat++;
		अगर (lat < 100000)
			जाओ बंद;

		अगर (माला_लोockname(sock, (काष्ठा sockaddr *)&laddr, &len) == -1)
			error(-1, त्रुटि_सं, "getsockname");
		म_लिखो("port: %d, lat: %lu, avg: %lu, nr: %lu\n",
				ntohs(laddr.sin_port), lat,
				sum_lat / nr_lat, nr_lat);
बंद:
		ख_साफ(मानक_निकास);
		बंद(sock);
	पूर्ण
पूर्ण

अटल व्योम server(पूर्णांक sock, काष्ठा sockaddr_in address)
अणु
	पूर्णांक accepted;
	पूर्णांक addrlen = माप(address);
	पूर्णांक buffer;

	जबतक (1) अणु
		accepted = accept(sock, (काष्ठा sockaddr *)&address,
				(socklen_t *)&addrlen);
		अगर (accepted < 0)
			error(-1, त्रुटि_सं, "accept");

		अगर (पढ़ो(accepted, &buffer, माप(buffer)) == -1)
			error(-1, त्रुटि_सं, "read");
		बंद(accepted);
	पूर्ण
पूर्ण

अटल व्योम sig_handler(पूर्णांक signum)
अणु
	समाप्त(संक_इति, child_pid);
	निकास(0);
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर स्थिर *argv[])
अणु
	पूर्णांक sock;
	पूर्णांक opt = 1;
	काष्ठा sockaddr_in address;
	काष्ठा sockaddr_in laddr;
	socklen_t len = माप(laddr);

	अगर (संकेत(संक_इति, sig_handler) == संक_त्रुटि)
		error(-1, त्रुटि_सं, "signal");

	sock = socket(AF_INET, SOCK_STREAM, 0);
	अगर (sock < 0)
		error(-1, त्रुटि_सं, "socket");

	अगर (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
				&opt, माप(opt)) == -1)
		error(-1, त्रुटि_सं, "setsockopt");

	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	/* dynamically allocate unused port */
	address.sin_port = 0;

	अगर (bind(sock, (काष्ठा sockaddr *)&address, माप(address)) < 0)
		error(-1, त्रुटि_सं, "bind");

	अगर (listen(sock, 3) < 0)
		error(-1, त्रुटि_सं, "listen");

	अगर (माला_लोockname(sock, (काष्ठा sockaddr *)&laddr, &len) == -1)
		error(-1, त्रुटि_सं, "getsockname");

	ख_लिखो(मानक_त्रुटि, "server port: %d\n", ntohs(laddr.sin_port));
	child_pid = विभाजन();
	अगर (!child_pid)
		client(ntohs(laddr.sin_port));
	अन्यथा
		server(sock, laddr);

	वापस 0;
पूर्ण
