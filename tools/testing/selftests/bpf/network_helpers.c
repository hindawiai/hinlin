<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
#समावेश <त्रुटिसं.स>
#समावेश <stdbool.h>
#समावेश <मानकपन.स>
#समावेश <माला.स>
#समावेश <unistd.h>

#समावेश <arpa/inet.h>

#समावेश <linux/err.h>
#समावेश <linux/in.h>
#समावेश <linux/in6.h>

#समावेश "bpf_util.h"
#समावेश "network_helpers.h"

#घोषणा clean_त्रुटि_सं() (त्रुटि_सं == 0 ? "None" : म_त्रुटि(त्रुटि_सं))
#घोषणा log_err(MSG, ...) (अणु						\
			पूर्णांक __save = त्रुटि_सं;				\
			ख_लिखो(मानक_त्रुटि, "(%s:%d: errno: %s) " MSG "\n", \
				__खाता__, __LINE__, clean_त्रुटि_सं(),	\
				##__VA_ARGS__);				\
			त्रुटि_सं = __save;					\
पूर्ण)

काष्ठा ipv4_packet pkt_v4 = अणु
	.eth.h_proto = __bpf_स्थिरant_htons(ETH_P_IP),
	.iph.ihl = 5,
	.iph.protocol = IPPROTO_TCP,
	.iph.tot_len = __bpf_स्थिरant_htons(MAGIC_BYTES),
	.tcp.urg_ptr = 123,
	.tcp.करोff = 5,
पूर्ण;

काष्ठा ipv6_packet pkt_v6 = अणु
	.eth.h_proto = __bpf_स्थिरant_htons(ETH_P_IPV6),
	.iph.nexthdr = IPPROTO_TCP,
	.iph.payload_len = __bpf_स्थिरant_htons(MAGIC_BYTES),
	.tcp.urg_ptr = 123,
	.tcp.करोff = 5,
पूर्ण;

पूर्णांक समय_रखोo(पूर्णांक fd, पूर्णांक समयout_ms)
अणु
	काष्ठा समयval समयout = अणु .tv_sec = 3 पूर्ण;

	अगर (समयout_ms > 0) अणु
		समयout.tv_sec = समयout_ms / 1000;
		समयout.tv_usec = (समयout_ms % 1000) * 1000;
	पूर्ण

	अगर (setsockopt(fd, SOL_SOCKET, SO_RCVTIMEO, &समयout,
		       माप(समयout))) अणु
		log_err("Failed to set SO_RCVTIMEO");
		वापस -1;
	पूर्ण

	अगर (setsockopt(fd, SOL_SOCKET, SO_SNDTIMEO, &समयout,
		       माप(समयout))) अणु
		log_err("Failed to set SO_SNDTIMEO");
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

#घोषणा save_त्रुटि_सं_बंद(fd) (अणु पूर्णांक __save = त्रुटि_सं; बंद(fd); त्रुटि_सं = __save; पूर्ण)

पूर्णांक start_server(पूर्णांक family, पूर्णांक type, स्थिर अक्षर *addr_str, __u16 port,
		 पूर्णांक समयout_ms)
अणु
	काष्ठा sockaddr_storage addr = अणुपूर्ण;
	socklen_t len;
	पूर्णांक fd;

	अगर (make_sockaddr(family, addr_str, port, &addr, &len))
		वापस -1;

	fd = socket(family, type, 0);
	अगर (fd < 0) अणु
		log_err("Failed to create server socket");
		वापस -1;
	पूर्ण

	अगर (समय_रखोo(fd, समयout_ms))
		जाओ error_बंद;

	अगर (bind(fd, (स्थिर काष्ठा sockaddr *)&addr, len) < 0) अणु
		log_err("Failed to bind socket");
		जाओ error_बंद;
	पूर्ण

	अगर (type == SOCK_STREAM) अणु
		अगर (listen(fd, 1) < 0) अणु
			log_err("Failed to listed on socket");
			जाओ error_बंद;
		पूर्ण
	पूर्ण

	वापस fd;

error_बंद:
	save_त्रुटि_सं_बंद(fd);
	वापस -1;
पूर्ण

पूर्णांक fastखोलो_connect(पूर्णांक server_fd, स्थिर अक्षर *data, अचिन्हित पूर्णांक data_len,
		     पूर्णांक समयout_ms)
अणु
	काष्ठा sockaddr_storage addr;
	socklen_t addrlen = माप(addr);
	काष्ठा sockaddr_in *addr_in;
	पूर्णांक fd, ret;

	अगर (माला_लोockname(server_fd, (काष्ठा sockaddr *)&addr, &addrlen)) अणु
		log_err("Failed to get server addr");
		वापस -1;
	पूर्ण

	addr_in = (काष्ठा sockaddr_in *)&addr;
	fd = socket(addr_in->sin_family, SOCK_STREAM, 0);
	अगर (fd < 0) अणु
		log_err("Failed to create client socket");
		वापस -1;
	पूर्ण

	अगर (समय_रखोo(fd, समयout_ms))
		जाओ error_बंद;

	ret = sendto(fd, data, data_len, MSG_FASTOPEN, (काष्ठा sockaddr *)&addr,
		     addrlen);
	अगर (ret != data_len) अणु
		log_err("sendto(data, %u) != %d\n", data_len, ret);
		जाओ error_बंद;
	पूर्ण

	वापस fd;

error_बंद:
	save_त्रुटि_सं_बंद(fd);
	वापस -1;
पूर्ण

अटल पूर्णांक connect_fd_to_addr(पूर्णांक fd,
			      स्थिर काष्ठा sockaddr_storage *addr,
			      socklen_t addrlen)
अणु
	अगर (connect(fd, (स्थिर काष्ठा sockaddr *)addr, addrlen)) अणु
		log_err("Failed to connect to server");
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक connect_to_fd(पूर्णांक server_fd, पूर्णांक समयout_ms)
अणु
	काष्ठा sockaddr_storage addr;
	काष्ठा sockaddr_in *addr_in;
	socklen_t addrlen, optlen;
	पूर्णांक fd, type;

	optlen = माप(type);
	अगर (माला_लोockopt(server_fd, SOL_SOCKET, SO_TYPE, &type, &optlen)) अणु
		log_err("getsockopt(SOL_TYPE)");
		वापस -1;
	पूर्ण

	addrlen = माप(addr);
	अगर (माला_लोockname(server_fd, (काष्ठा sockaddr *)&addr, &addrlen)) अणु
		log_err("Failed to get server addr");
		वापस -1;
	पूर्ण

	addr_in = (काष्ठा sockaddr_in *)&addr;
	fd = socket(addr_in->sin_family, type, 0);
	अगर (fd < 0) अणु
		log_err("Failed to create client socket");
		वापस -1;
	पूर्ण

	अगर (समय_रखोo(fd, समयout_ms))
		जाओ error_बंद;

	अगर (connect_fd_to_addr(fd, &addr, addrlen))
		जाओ error_बंद;

	वापस fd;

error_बंद:
	save_त्रुटि_सं_बंद(fd);
	वापस -1;
पूर्ण

पूर्णांक connect_fd_to_fd(पूर्णांक client_fd, पूर्णांक server_fd, पूर्णांक समयout_ms)
अणु
	काष्ठा sockaddr_storage addr;
	socklen_t len = माप(addr);

	अगर (समय_रखोo(client_fd, समयout_ms))
		वापस -1;

	अगर (माला_लोockname(server_fd, (काष्ठा sockaddr *)&addr, &len)) अणु
		log_err("Failed to get server addr");
		वापस -1;
	पूर्ण

	अगर (connect_fd_to_addr(client_fd, &addr, len))
		वापस -1;

	वापस 0;
पूर्ण

पूर्णांक make_sockaddr(पूर्णांक family, स्थिर अक्षर *addr_str, __u16 port,
		  काष्ठा sockaddr_storage *addr, socklen_t *len)
अणु
	अगर (family == AF_INET) अणु
		काष्ठा sockaddr_in *sin = (व्योम *)addr;

		sin->sin_family = AF_INET;
		sin->sin_port = htons(port);
		अगर (addr_str &&
		    inet_pton(AF_INET, addr_str, &sin->sin_addr) != 1) अणु
			log_err("inet_pton(AF_INET, %s)", addr_str);
			वापस -1;
		पूर्ण
		अगर (len)
			*len = माप(*sin);
		वापस 0;
	पूर्ण अन्यथा अगर (family == AF_INET6) अणु
		काष्ठा sockaddr_in6 *sin6 = (व्योम *)addr;

		sin6->sin6_family = AF_INET6;
		sin6->sin6_port = htons(port);
		अगर (addr_str &&
		    inet_pton(AF_INET6, addr_str, &sin6->sin6_addr) != 1) अणु
			log_err("inet_pton(AF_INET6, %s)", addr_str);
			वापस -1;
		पूर्ण
		अगर (len)
			*len = माप(*sin6);
		वापस 0;
	पूर्ण
	वापस -1;
पूर्ण
