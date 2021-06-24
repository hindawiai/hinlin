<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2007 Luca Bigliardi (shammash@artha.org).
 */

#अगर_अघोषित __UM_VDE_H__
#घोषणा __UM_VDE_H__

काष्ठा vde_data अणु
	अक्षर *vde_चयन;
	अक्षर *descr;
	व्योम *args;
	व्योम *conn;
	व्योम *dev;
पूर्ण;

काष्ठा vde_init अणु
	अक्षर *vde_चयन;
	अक्षर *descr;
	पूर्णांक port;
	अक्षर *group;
	पूर्णांक mode;
पूर्ण;

बाह्य स्थिर काष्ठा net_user_info vde_user_info;

बाह्य व्योम vde_init_libstuff(काष्ठा vde_data *vpri, काष्ठा vde_init *init);

बाह्य पूर्णांक vde_user_पढ़ो(व्योम *conn, व्योम *buf, पूर्णांक len);
बाह्य पूर्णांक vde_user_ग_लिखो(व्योम *conn, व्योम *buf, पूर्णांक len);

#पूर्ण_अगर
