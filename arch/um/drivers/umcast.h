<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2001 - 2007 Jeff Dike (jdike@अणुaddtoit,linux.पूर्णांकelपूर्ण.com)
 */

#अगर_अघोषित __DRIVERS_UMCAST_H
#घोषणा __DRIVERS_UMCAST_H

#समावेश <net_user.h>

काष्ठा umcast_data अणु
	अक्षर *addr;
	अचिन्हित लघु lport;
	अचिन्हित लघु rport;
	व्योम *listen_addr;
	व्योम *remote_addr;
	पूर्णांक ttl;
	पूर्णांक unicast;
	व्योम *dev;
पूर्ण;

बाह्य स्थिर काष्ठा net_user_info umcast_user_info;

बाह्य पूर्णांक umcast_user_ग_लिखो(पूर्णांक fd, व्योम *buf, पूर्णांक len,
			     काष्ठा umcast_data *pri);

#पूर्ण_अगर
