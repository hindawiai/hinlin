<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* 
 * Copyright (C) 2002 Jeff Dike (jdike@karaya.com)
 */

#समावेश <net_user.h>

काष्ठा pcap_data अणु
	अक्षर *host_अगर;
	पूर्णांक promisc;
	पूर्णांक optimize;
	अक्षर *filter;
	व्योम *compiled;
	व्योम *pcap;
	व्योम *dev;
पूर्ण;

बाह्य स्थिर काष्ठा net_user_info pcap_user_info;

बाह्य पूर्णांक pcap_user_पढ़ो(पूर्णांक fd, व्योम *buf, पूर्णांक len, काष्ठा pcap_data *pri);

