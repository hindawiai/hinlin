<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * include/net/9p/transport.h
 *
 * Transport Definition
 *
 *  Copyright (C) 2005 by Latchesar Ionkov <lucho@ionkov.net>
 *  Copyright (C) 2004-2008 by Eric Van Hensbergen <ericvh@gmail.com>
 */

#अगर_अघोषित NET_9P_TRANSPORT_H
#घोषणा NET_9P_TRANSPORT_H

#घोषणा P9_DEF_MIN_RESVPORT	(665U)
#घोषणा P9_DEF_MAX_RESVPORT	(1023U)

/**
 * काष्ठा p9_trans_module - transport module पूर्णांकerface
 * @list: used to मुख्यtain a list of currently available transports
 * @name: the human-पढ़ोable name of the transport
 * @maxsize: transport provided maximum packet size
 * @def: set अगर this transport should be considered the शेष
 * @create: member function to create a new connection on this transport
 * @बंद: member function to discard a connection on this transport
 * @request: member function to issue a request to the transport
 * @cancel: member function to cancel a request (अगर it hasn't been sent)
 * @cancelled: member function to notअगरy that a cancelled request will not
 *             receive a reply
 *
 * This is the basic API क्रम a transport module which is रेजिस्टरed by the
 * transport module with the 9P core network module and used by the client
 * to instantiate a new connection on a transport.
 *
 * The transport module list is रक्षित by v9fs_trans_lock.
 */

काष्ठा p9_trans_module अणु
	काष्ठा list_head list;
	अक्षर *name;		/* name of transport */
	पूर्णांक maxsize;		/* max message size of transport */
	पूर्णांक def;		/* this transport should be शेष */
	काष्ठा module *owner;
	पूर्णांक (*create)(काष्ठा p9_client *, स्थिर अक्षर *, अक्षर *);
	व्योम (*बंद) (काष्ठा p9_client *);
	पूर्णांक (*request) (काष्ठा p9_client *, काष्ठा p9_req_t *req);
	पूर्णांक (*cancel) (काष्ठा p9_client *, काष्ठा p9_req_t *req);
	पूर्णांक (*cancelled)(काष्ठा p9_client *, काष्ठा p9_req_t *req);
	पूर्णांक (*zc_request)(काष्ठा p9_client *, काष्ठा p9_req_t *,
			  काष्ठा iov_iter *, काष्ठा iov_iter *, पूर्णांक , पूर्णांक, पूर्णांक);
	पूर्णांक (*show_options)(काष्ठा seq_file *, काष्ठा p9_client *);
पूर्ण;

व्योम v9fs_रेजिस्टर_trans(काष्ठा p9_trans_module *m);
व्योम v9fs_unरेजिस्टर_trans(काष्ठा p9_trans_module *m);
काष्ठा p9_trans_module *v9fs_get_trans_by_name(अक्षर *s);
काष्ठा p9_trans_module *v9fs_get_शेष_trans(व्योम);
व्योम v9fs_put_trans(काष्ठा p9_trans_module *m);
#पूर्ण_अगर /* NET_9P_TRANSPORT_H */
