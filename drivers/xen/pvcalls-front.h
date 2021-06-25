<शैली गुरु>
#अगर_अघोषित __PVCALLS_FRONT_H__
#घोषणा __PVCALLS_FRONT_H__

#समावेश <linux/net.h>

पूर्णांक pvcalls_front_socket(काष्ठा socket *sock);
पूर्णांक pvcalls_front_connect(काष्ठा socket *sock, काष्ठा sockaddr *addr,
			  पूर्णांक addr_len, पूर्णांक flags);
पूर्णांक pvcalls_front_bind(काष्ठा socket *sock,
		       काष्ठा sockaddr *addr,
		       पूर्णांक addr_len);
पूर्णांक pvcalls_front_listen(काष्ठा socket *sock, पूर्णांक backlog);
पूर्णांक pvcalls_front_accept(काष्ठा socket *sock,
			 काष्ठा socket *newsock,
			 पूर्णांक flags);
पूर्णांक pvcalls_front_sendmsg(काष्ठा socket *sock,
			  काष्ठा msghdr *msg,
			  माप_प्रकार len);
पूर्णांक pvcalls_front_recvmsg(काष्ठा socket *sock,
			  काष्ठा msghdr *msg,
			  माप_प्रकार len,
			  पूर्णांक flags);
__poll_t pvcalls_front_poll(काष्ठा file *file,
				काष्ठा socket *sock,
				poll_table *रुको);
पूर्णांक pvcalls_front_release(काष्ठा socket *sock);

#पूर्ण_अगर
