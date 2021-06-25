<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#समावेश <मानककोष.स>
#समावेश <मानकपन.स>
#समावेश <linux/unistd.h>
#समावेश <unistd.h>
#समावेश <माला.स>
#समावेश <त्रुटिसं.स>
#समावेश <linux/अगर_ether.h>
#समावेश <net/अगर.h>
#समावेश <linux/अगर_packet.h>
#समावेश <arpa/inet.h>

अटल अंतरभूत पूर्णांक खोलो_raw_sock(स्थिर अक्षर *name)
अणु
	काष्ठा sockaddr_ll sll;
	पूर्णांक sock;

	sock = socket(PF_PACKET, SOCK_RAW | SOCK_NONBLOCK | SOCK_CLOEXEC, htons(ETH_P_ALL));
	अगर (sock < 0) अणु
		म_लिखो("cannot create raw socket\n");
		वापस -1;
	पूर्ण

	स_रखो(&sll, 0, माप(sll));
	sll.sll_family = AF_PACKET;
	sll.sll_अगरindex = अगर_nametoindex(name);
	sll.sll_protocol = htons(ETH_P_ALL);
	अगर (bind(sock, (काष्ठा sockaddr *)&sll, माप(sll)) < 0) अणु
		म_लिखो("bind to %s: %s\n", name, म_त्रुटि(त्रुटि_सं));
		बंद(sock);
		वापस -1;
	पूर्ण

	वापस sock;
पूर्ण
