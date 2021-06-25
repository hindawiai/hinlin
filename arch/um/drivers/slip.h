<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __UM_SLIP_H
#घोषणा __UM_SLIP_H

#समावेश "slip_common.h"

काष्ठा slip_data अणु
	व्योम *dev;
	अक्षर name[माप("slnnnnn\0")];
	अक्षर *addr;
	अक्षर *gate_addr;
	पूर्णांक slave;
	काष्ठा slip_proto slip;
पूर्ण;

बाह्य स्थिर काष्ठा net_user_info slip_user_info;

बाह्य पूर्णांक slip_user_पढ़ो(पूर्णांक fd, व्योम *buf, पूर्णांक len, काष्ठा slip_data *pri);
बाह्य पूर्णांक slip_user_ग_लिखो(पूर्णांक fd, व्योम *buf, पूर्णांक len, काष्ठा slip_data *pri);

#पूर्ण_अगर
