<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __UM_SLIRP_H
#घोषणा __UM_SLIRP_H

#समावेश "slip_common.h"

#घोषणा SLIRP_MAX_ARGS 100
/*
 * XXX this next definition is here because I करोn't understand why this
 * initializer करोesn't work in slirp_kern.c:
 *
 *   argv :  अणु init->argv[ 0 ... SLIRP_MAX_ARGS-1 ] पूर्ण,
 *
 * or why I can't typecast like this:
 *
 *   argv :  (अक्षर* [SLIRP_MAX_ARGS])(init->argv), 
 */
काष्ठा arg_list_dummy_wrapper अणु अक्षर *argv[SLIRP_MAX_ARGS]; पूर्ण;

काष्ठा slirp_data अणु
	व्योम *dev;
	काष्ठा arg_list_dummy_wrapper argw;
	पूर्णांक pid;
	पूर्णांक slave;
	काष्ठा slip_proto slip;
पूर्ण;

बाह्य स्थिर काष्ठा net_user_info slirp_user_info;

बाह्य पूर्णांक slirp_user_पढ़ो(पूर्णांक fd, व्योम *buf, पूर्णांक len, काष्ठा slirp_data *pri);
बाह्य पूर्णांक slirp_user_ग_लिखो(पूर्णांक fd, व्योम *buf, पूर्णांक len,
			    काष्ठा slirp_data *pri);

#पूर्ण_अगर
