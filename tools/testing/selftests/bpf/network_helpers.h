<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __NETWORK_HELPERS_H
#घोषणा __NETWORK_HELPERS_H
#समावेश <sys/socket.h>
#समावेश <sys/types.h>
#समावेश <linux/types.h>
प्रकार __u16 __sum16;
#समावेश <linux/अगर_ether.h>
#समावेश <linux/अगर_packet.h>
#समावेश <linux/ip.h>
#समावेश <linux/ipv6.h>
#समावेश <netinet/tcp.h>
#समावेश <bpf/bpf_endian.h>

#घोषणा MAGIC_VAL 0x1234
#घोषणा NUM_ITER 100000
#घोषणा VIP_NUM 5
#घोषणा MAGIC_BYTES 123

/* ipv4 test vector */
काष्ठा ipv4_packet अणु
	काष्ठा ethhdr eth;
	काष्ठा iphdr iph;
	काष्ठा tcphdr tcp;
पूर्ण __packed;
बाह्य काष्ठा ipv4_packet pkt_v4;

/* ipv6 test vector */
काष्ठा ipv6_packet अणु
	काष्ठा ethhdr eth;
	काष्ठा ipv6hdr iph;
	काष्ठा tcphdr tcp;
पूर्ण __packed;
बाह्य काष्ठा ipv6_packet pkt_v6;

पूर्णांक समय_रखोo(पूर्णांक fd, पूर्णांक समयout_ms);
पूर्णांक start_server(पूर्णांक family, पूर्णांक type, स्थिर अक्षर *addr, __u16 port,
		 पूर्णांक समयout_ms);
पूर्णांक connect_to_fd(पूर्णांक server_fd, पूर्णांक समयout_ms);
पूर्णांक connect_fd_to_fd(पूर्णांक client_fd, पूर्णांक server_fd, पूर्णांक समयout_ms);
पूर्णांक fastखोलो_connect(पूर्णांक server_fd, स्थिर अक्षर *data, अचिन्हित पूर्णांक data_len,
		     पूर्णांक समयout_ms);
पूर्णांक make_sockaddr(पूर्णांक family, स्थिर अक्षर *addr_str, __u16 port,
		  काष्ठा sockaddr_storage *addr, socklen_t *len);

#पूर्ण_अगर
