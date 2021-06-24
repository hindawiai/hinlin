<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2002 - 2007 Jeff Dike (jdike@अणुaddtoit,linux.पूर्णांकelपूर्ण.com)
 */

#अगर_अघोषित __UM_NET_USER_H__
#घोषणा __UM_NET_USER_H__

#घोषणा ETH_ADDR_LEN (6)
#घोषणा ETH_HEADER_ETHERTAP (16)
#घोषणा ETH_HEADER_OTHER (26) /* 14 क्रम ethernet + VLAN + MPLS क्रम crazy people */
#घोषणा ETH_MAX_PACKET (1500)

#घोषणा UML_NET_VERSION (4)

काष्ठा net_user_info अणु
	पूर्णांक (*init)(व्योम *, व्योम *);
	पूर्णांक (*खोलो)(व्योम *);
	व्योम (*बंद)(पूर्णांक, व्योम *);
	व्योम (*हटाओ)(व्योम *);
	व्योम (*add_address)(अचिन्हित अक्षर *, अचिन्हित अक्षर *, व्योम *);
	व्योम (*delete_address)(अचिन्हित अक्षर *, अचिन्हित अक्षर *, व्योम *);
	पूर्णांक max_packet;
	पूर्णांक mtu;
पूर्ण;

बाह्य व्योम ether_user_init(व्योम *data, व्योम *dev);
बाह्य व्योम iter_addresses(व्योम *d, व्योम (*cb)(अचिन्हित अक्षर *,
					       अचिन्हित अक्षर *, व्योम *),
			   व्योम *arg);

बाह्य व्योम *get_output_buffer(पूर्णांक *len_out);
बाह्य व्योम मुक्त_output_buffer(व्योम *buffer);

बाह्य पूर्णांक tap_खोलो_common(व्योम *dev, अक्षर *gate_addr);
बाह्य व्योम tap_check_ips(अक्षर *gate_addr, अचिन्हित अक्षर *eth_addr);

बाह्य व्योम पढ़ो_output(पूर्णांक fd, अक्षर *output_out, पूर्णांक len);

बाह्य पूर्णांक net_पढ़ो(पूर्णांक fd, व्योम *buf, पूर्णांक len);
बाह्य पूर्णांक net_recvfrom(पूर्णांक fd, व्योम *buf, पूर्णांक len);
बाह्य पूर्णांक net_ग_लिखो(पूर्णांक fd, व्योम *buf, पूर्णांक len);
बाह्य पूर्णांक net_send(पूर्णांक fd, व्योम *buf, पूर्णांक len);
बाह्य पूर्णांक net_sendto(पूर्णांक fd, व्योम *buf, पूर्णांक len, व्योम *to, पूर्णांक sock_len);

बाह्य व्योम खोलो_addr(अचिन्हित अक्षर *addr, अचिन्हित अक्षर *neपंचांगask, व्योम *arg);
बाह्य व्योम बंद_addr(अचिन्हित अक्षर *addr, अचिन्हित अक्षर *neपंचांगask, व्योम *arg);

बाह्य अक्षर *split_अगर_spec(अक्षर *str, ...);

बाह्य पूर्णांक dev_neपंचांगask(व्योम *d, व्योम *m);

#पूर्ण_अगर
