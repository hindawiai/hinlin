<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2001 - 2007 Jeff Dike (jdike@अणुaddtoit,linux.पूर्णांकelपूर्ण.com)
 */

#अगर_अघोषित __DAEMON_H__
#घोषणा __DAEMON_H__

#समावेश <net_user.h>

#घोषणा SWITCH_VERSION 3

काष्ठा daemon_data अणु
	अक्षर *sock_type;
	अक्षर *ctl_sock;
	व्योम *ctl_addr;
	व्योम *data_addr;
	व्योम *local_addr;
	पूर्णांक fd;
	पूर्णांक control;
	व्योम *dev;
पूर्ण;

बाह्य स्थिर काष्ठा net_user_info daemon_user_info;

बाह्य पूर्णांक daemon_user_ग_लिखो(पूर्णांक fd, व्योम *buf, पूर्णांक len,
			     काष्ठा daemon_data *pri);

#पूर्ण_अगर
