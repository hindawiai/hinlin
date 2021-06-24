<शैली गुरु>
/*
 * Copyright (c) 2013, Cisco Systems, Inc. All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the
 * BSD license below:
 *
 *     Redistribution and use in source and binary क्रमms, with or
 *     without modअगरication, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary क्रमm must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the करोcumentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */
#समावेश <linux/biपंचांगap.h>
#समावेश <linux/file.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <net/inet_sock.h>

#समावेश "usnic_transport.h"
#समावेश "usnic_log.h"

/* ROCE */
अटल अचिन्हित दीर्घ *roce_biपंचांगap;
अटल u16 roce_next_port = 1;
#घोषणा ROCE_BITMAP_SZ ((1 << (8 /*अक्षर_बिट*/ * माप(u16)))/8 /*CHAR BIT*/)
अटल DEFINE_SPINLOCK(roce_biपंचांगap_lock);

स्थिर अक्षर *usnic_transport_to_str(क्रमागत usnic_transport_type type)
अणु
	चयन (type) अणु
	हाल USNIC_TRANSPORT_UNKNOWN:
		वापस "Unknown";
	हाल USNIC_TRANSPORT_ROCE_CUSTOM:
		वापस "roce custom";
	हाल USNIC_TRANSPORT_IPV4_UDP:
		वापस "IPv4 UDP";
	हाल USNIC_TRANSPORT_MAX:
		वापस "Max?";
	शेष:
		वापस "Not known";
	पूर्ण
पूर्ण

पूर्णांक usnic_transport_sock_to_str(अक्षर *buf, पूर्णांक buf_sz,
					काष्ठा socket *sock)
अणु
	पूर्णांक err;
	uपूर्णांक32_t addr;
	uपूर्णांक16_t port;
	पूर्णांक proto;

	स_रखो(buf, 0, buf_sz);
	err = usnic_transport_sock_get_addr(sock, &proto, &addr, &port);
	अगर (err)
		वापस 0;

	वापस scnम_लिखो(buf, buf_sz, "Proto:%u Addr:%pI4h Port:%hu",
			proto, &addr, port);
पूर्ण

/*
 * reserve a port number.  अगर "0" specअगरied, we will try to pick one
 * starting at roce_next_port.  roce_next_port will take on the values
 * 1..4096
 */
u16 usnic_transport_rsrv_port(क्रमागत usnic_transport_type type, u16 port_num)
अणु
	अगर (type == USNIC_TRANSPORT_ROCE_CUSTOM) अणु
		spin_lock(&roce_biपंचांगap_lock);
		अगर (!port_num) अणु
			port_num = biपंचांगap_find_next_zero_area(roce_biपंचांगap,
						ROCE_BITMAP_SZ,
						roce_next_port /* start */,
						1 /* nr */,
						0 /* align */);
			roce_next_port = (port_num & 4095) + 1;
		पूर्ण अन्यथा अगर (test_bit(port_num, roce_biपंचांगap)) अणु
			usnic_err("Failed to allocate port for %s\n",
					usnic_transport_to_str(type));
			spin_unlock(&roce_biपंचांगap_lock);
			जाओ out_fail;
		पूर्ण
		biपंचांगap_set(roce_biपंचांगap, port_num, 1);
		spin_unlock(&roce_biपंचांगap_lock);
	पूर्ण अन्यथा अणु
		usnic_err("Failed to allocate port - transport %s unsupported\n",
				usnic_transport_to_str(type));
		जाओ out_fail;
	पूर्ण

	usnic_dbg("Allocating port %hu for %s\n", port_num,
			usnic_transport_to_str(type));
	वापस port_num;

out_fail:
	वापस 0;
पूर्ण

व्योम usnic_transport_unrsrv_port(क्रमागत usnic_transport_type type, u16 port_num)
अणु
	अगर (type == USNIC_TRANSPORT_ROCE_CUSTOM) अणु
		spin_lock(&roce_biपंचांगap_lock);
		अगर (!port_num) अणु
			usnic_err("Unreserved invalid port num 0 for %s\n",
					usnic_transport_to_str(type));
			जाओ out_roce_custom;
		पूर्ण

		अगर (!test_bit(port_num, roce_biपंचांगap)) अणु
			usnic_err("Unreserving invalid %hu for %s\n",
					port_num,
					usnic_transport_to_str(type));
			जाओ out_roce_custom;
		पूर्ण
		biपंचांगap_clear(roce_biपंचांगap, port_num, 1);
		usnic_dbg("Freeing port %hu for %s\n", port_num,
				usnic_transport_to_str(type));
out_roce_custom:
		spin_unlock(&roce_biपंचांगap_lock);
	पूर्ण अन्यथा अणु
		usnic_err("Freeing invalid port %hu for %d\n", port_num, type);
	पूर्ण
पूर्ण

काष्ठा socket *usnic_transport_get_socket(पूर्णांक sock_fd)
अणु
	काष्ठा socket *sock;
	पूर्णांक err;
	अक्षर buf[25];

	/* sockfd_lookup will पूर्णांकernally करो a fget */
	sock = sockfd_lookup(sock_fd, &err);
	अगर (!sock) अणु
		usnic_err("Unable to lookup socket for fd %d with err %d\n",
				sock_fd, err);
		वापस ERR_PTR(-ENOENT);
	पूर्ण

	usnic_transport_sock_to_str(buf, माप(buf), sock);
	usnic_dbg("Get sock %s\n", buf);

	वापस sock;
पूर्ण

व्योम usnic_transport_put_socket(काष्ठा socket *sock)
अणु
	अक्षर buf[100];

	usnic_transport_sock_to_str(buf, माप(buf), sock);
	usnic_dbg("Put sock %s\n", buf);
	sockfd_put(sock);
पूर्ण

पूर्णांक usnic_transport_sock_get_addr(काष्ठा socket *sock, पूर्णांक *proto,
					uपूर्णांक32_t *addr, uपूर्णांक16_t *port)
अणु
	पूर्णांक err;
	काष्ठा sockaddr_in sock_addr;

	err = sock->ops->getname(sock,
				(काष्ठा sockaddr *)&sock_addr,
				0);
	अगर (err < 0)
		वापस err;

	अगर (sock_addr.sin_family != AF_INET)
		वापस -EINVAL;

	अगर (proto)
		*proto = sock->sk->sk_protocol;
	अगर (port)
		*port = ntohs(((काष्ठा sockaddr_in *)&sock_addr)->sin_port);
	अगर (addr)
		*addr = ntohl(((काष्ठा sockaddr_in *)
					&sock_addr)->sin_addr.s_addr);

	वापस 0;
पूर्ण

पूर्णांक usnic_transport_init(व्योम)
अणु
	roce_biपंचांगap = kzalloc(ROCE_BITMAP_SZ, GFP_KERNEL);
	अगर (!roce_biपंचांगap)
		वापस -ENOMEM;

	/* Do not ever allocate bit 0, hence set it here */
	biपंचांगap_set(roce_biपंचांगap, 0, 1);
	वापस 0;
पूर्ण

व्योम usnic_transport_fini(व्योम)
अणु
	kमुक्त(roce_biपंचांगap);
पूर्ण
