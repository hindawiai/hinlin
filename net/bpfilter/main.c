<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#घोषणा _GNU_SOURCE
#समावेश <sys/uपन.स>
#समावेश <त्रुटिसं.स>
#समावेश <मानकपन.स>
#समावेश <sys/socket.h>
#समावेश <fcntl.h>
#समावेश <unistd.h>
#समावेश "../../include/uapi/linux/bpf.h"
#समावेश <यंत्र/unistd.h>
#समावेश "msgfmt.h"

खाता *debug_f;

अटल पूर्णांक handle_get_cmd(काष्ठा mbox_request *cmd)
अणु
	चयन (cmd->cmd) अणु
	हाल 0:
		वापस 0;
	शेष:
		अवरोध;
	पूर्ण
	वापस -ENOPROTOOPT;
पूर्ण

अटल पूर्णांक handle_set_cmd(काष्ठा mbox_request *cmd)
अणु
	वापस -ENOPROTOOPT;
पूर्ण

अटल व्योम loop(व्योम)
अणु
	जबतक (1) अणु
		काष्ठा mbox_request req;
		काष्ठा mbox_reply reply;
		पूर्णांक n;

		n = पढ़ो(0, &req, माप(req));
		अगर (n != माप(req)) अणु
			ख_लिखो(debug_f, "invalid request %d\n", n);
			वापस;
		पूर्ण

		reply.status = req.is_set ?
			handle_set_cmd(&req) :
			handle_get_cmd(&req);

		n = ग_लिखो(1, &reply, माप(reply));
		अगर (n != माप(reply)) अणु
			ख_लिखो(debug_f, "reply failed %d\n", n);
			वापस;
		पूर्ण
	पूर्ण
पूर्ण

पूर्णांक मुख्य(व्योम)
अणु
	debug_f = ख_खोलो("/dev/kmsg", "w");
	रखो_भबफ(debug_f, 0, _IOLBF, 0);
	ख_लिखो(debug_f, "Started bpfilter\n");
	loop();
	ख_बंद(debug_f);
	वापस 0;
पूर्ण
