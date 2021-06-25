<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* 
 * Copyright (C) 2001 Jeff Dike (jdike@karaya.com)
 */

#अगर_अघोषित __PORT_H__
#घोषणा __PORT_H__

बाह्य व्योम *port_data(पूर्णांक port);
बाह्य पूर्णांक port_रुको(व्योम *data);
बाह्य व्योम port_kern_बंद(व्योम *d);
बाह्य पूर्णांक port_connection(पूर्णांक fd, पूर्णांक *socket_out, पूर्णांक *pid_out);
बाह्य पूर्णांक port_listen_fd(पूर्णांक port);
बाह्य व्योम port_पढ़ो(पूर्णांक fd, व्योम *data);
बाह्य व्योम port_kern_मुक्त(व्योम *d);
बाह्य पूर्णांक port_rcv_fd(पूर्णांक fd);
बाह्य व्योम port_हटाओ_dev(व्योम *d);

#पूर्ण_अगर

