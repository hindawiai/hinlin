<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <test_progs.h>
#समावेश "cgroup_helpers.h"

#घोषणा SOL_CUSTOM			0xdeadbeef
#घोषणा CUSTOM_INHERIT1			0
#घोषणा CUSTOM_INHERIT2			1
#घोषणा CUSTOM_LISTENER			2

अटल पूर्णांक connect_to_server(पूर्णांक server_fd)
अणु
	काष्ठा sockaddr_storage addr;
	socklen_t len = माप(addr);
	पूर्णांक fd;

	fd = socket(AF_INET, SOCK_STREAM, 0);
	अगर (fd < 0) अणु
		log_err("Failed to create client socket");
		वापस -1;
	पूर्ण

	अगर (माला_लोockname(server_fd, (काष्ठा sockaddr *)&addr, &len)) अणु
		log_err("Failed to get server addr");
		जाओ out;
	पूर्ण

	अगर (connect(fd, (स्थिर काष्ठा sockaddr *)&addr, len) < 0) अणु
		log_err("Fail to connect to server");
		जाओ out;
	पूर्ण

	वापस fd;

out:
	बंद(fd);
	वापस -1;
पूर्ण

अटल पूर्णांक verअगरy_sockopt(पूर्णांक fd, पूर्णांक optname, स्थिर अक्षर *msg, अक्षर expected)
अणु
	socklen_t optlen = 1;
	अक्षर buf = 0;
	पूर्णांक err;

	err = माला_लोockopt(fd, SOL_CUSTOM, optname, &buf, &optlen);
	अगर (err) अणु
		log_err("%s: failed to call getsockopt", msg);
		वापस 1;
	पूर्ण

	म_लिखो("%s %d: got=0x%x ? expected=0x%x\n", msg, optname, buf, expected);

	अगर (buf != expected) अणु
		log_err("%s: unexpected getsockopt value %d != %d", msg,
			buf, expected);
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल pthपढ़ो_mutex_t server_started_mtx = PTHREAD_MUTEX_INITIALIZER;
अटल pthपढ़ो_cond_t server_started = PTHREAD_COND_INITIALIZER;

अटल व्योम *server_thपढ़ो(व्योम *arg)
अणु
	काष्ठा sockaddr_storage addr;
	socklen_t len = माप(addr);
	पूर्णांक fd = *(पूर्णांक *)arg;
	पूर्णांक client_fd;
	पूर्णांक err = 0;

	err = listen(fd, 1);

	pthपढ़ो_mutex_lock(&server_started_mtx);
	pthपढ़ो_cond_संकेत(&server_started);
	pthपढ़ो_mutex_unlock(&server_started_mtx);

	अगर (CHECK_FAIL(err < 0)) अणु
		लिखो_त्रुटि("Failed to listed on socket");
		वापस शून्य;
	पूर्ण

	err += verअगरy_sockopt(fd, CUSTOM_INHERIT1, "listen", 1);
	err += verअगरy_sockopt(fd, CUSTOM_INHERIT2, "listen", 1);
	err += verअगरy_sockopt(fd, CUSTOM_LISTENER, "listen", 1);

	client_fd = accept(fd, (काष्ठा sockaddr *)&addr, &len);
	अगर (CHECK_FAIL(client_fd < 0)) अणु
		लिखो_त्रुटि("Failed to accept client");
		वापस शून्य;
	पूर्ण

	err += verअगरy_sockopt(client_fd, CUSTOM_INHERIT1, "accept", 1);
	err += verअगरy_sockopt(client_fd, CUSTOM_INHERIT2, "accept", 1);
	err += verअगरy_sockopt(client_fd, CUSTOM_LISTENER, "accept", 0);

	बंद(client_fd);

	वापस (व्योम *)(दीर्घ)err;
पूर्ण

अटल पूर्णांक start_server(व्योम)
अणु
	काष्ठा sockaddr_in addr = अणु
		.sin_family = AF_INET,
		.sin_addr.s_addr = htonl(INADDR_LOOPBACK),
	पूर्ण;
	अक्षर buf;
	पूर्णांक err;
	पूर्णांक fd;
	पूर्णांक i;

	fd = socket(AF_INET, SOCK_STREAM, 0);
	अगर (fd < 0) अणु
		log_err("Failed to create server socket");
		वापस -1;
	पूर्ण

	क्रम (i = CUSTOM_INHERIT1; i <= CUSTOM_LISTENER; i++) अणु
		buf = 0x01;
		err = setsockopt(fd, SOL_CUSTOM, i, &buf, 1);
		अगर (err) अणु
			log_err("Failed to call setsockopt(%d)", i);
			बंद(fd);
			वापस -1;
		पूर्ण
	पूर्ण

	अगर (bind(fd, (स्थिर काष्ठा sockaddr *)&addr, माप(addr)) < 0) अणु
		log_err("Failed to bind socket");
		बंद(fd);
		वापस -1;
	पूर्ण

	वापस fd;
पूर्ण

अटल पूर्णांक prog_attach(काष्ठा bpf_object *obj, पूर्णांक cgroup_fd, स्थिर अक्षर *title)
अणु
	क्रमागत bpf_attach_type attach_type;
	क्रमागत bpf_prog_type prog_type;
	काष्ठा bpf_program *prog;
	पूर्णांक err;

	err = libbpf_prog_type_by_name(title, &prog_type, &attach_type);
	अगर (err) अणु
		log_err("Failed to deduct types for %s BPF program", title);
		वापस -1;
	पूर्ण

	prog = bpf_object__find_program_by_title(obj, title);
	अगर (!prog) अणु
		log_err("Failed to find %s BPF program", title);
		वापस -1;
	पूर्ण

	err = bpf_prog_attach(bpf_program__fd(prog), cgroup_fd,
			      attach_type, 0);
	अगर (err) अणु
		log_err("Failed to attach %s BPF program", title);
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम run_test(पूर्णांक cgroup_fd)
अणु
	काष्ठा bpf_prog_load_attr attr = अणु
		.file = "./sockopt_inherit.o",
	पूर्ण;
	पूर्णांक server_fd = -1, client_fd;
	काष्ठा bpf_object *obj;
	व्योम *server_err;
	pthपढ़ो_t tid;
	पूर्णांक ignored;
	पूर्णांक err;

	err = bpf_prog_load_xattr(&attr, &obj, &ignored);
	अगर (CHECK_FAIL(err))
		वापस;

	err = prog_attach(obj, cgroup_fd, "cgroup/getsockopt");
	अगर (CHECK_FAIL(err))
		जाओ बंद_bpf_object;

	err = prog_attach(obj, cgroup_fd, "cgroup/setsockopt");
	अगर (CHECK_FAIL(err))
		जाओ बंद_bpf_object;

	server_fd = start_server();
	अगर (CHECK_FAIL(server_fd < 0))
		जाओ बंद_bpf_object;

	pthपढ़ो_mutex_lock(&server_started_mtx);
	अगर (CHECK_FAIL(pthपढ़ो_create(&tid, शून्य, server_thपढ़ो,
				      (व्योम *)&server_fd)))
		जाओ बंद_server_fd;
	pthपढ़ो_cond_रुको(&server_started, &server_started_mtx);
	pthपढ़ो_mutex_unlock(&server_started_mtx);

	client_fd = connect_to_server(server_fd);
	अगर (CHECK_FAIL(client_fd < 0))
		जाओ बंद_server_fd;

	CHECK_FAIL(verअगरy_sockopt(client_fd, CUSTOM_INHERIT1, "connect", 0));
	CHECK_FAIL(verअगरy_sockopt(client_fd, CUSTOM_INHERIT2, "connect", 0));
	CHECK_FAIL(verअगरy_sockopt(client_fd, CUSTOM_LISTENER, "connect", 0));

	pthपढ़ो_join(tid, &server_err);

	err = (पूर्णांक)(दीर्घ)server_err;
	CHECK_FAIL(err);

	बंद(client_fd);

बंद_server_fd:
	बंद(server_fd);
बंद_bpf_object:
	bpf_object__बंद(obj);
पूर्ण

व्योम test_sockopt_inherit(व्योम)
अणु
	पूर्णांक cgroup_fd;

	cgroup_fd = test__join_cgroup("/sockopt_inherit");
	अगर (CHECK_FAIL(cgroup_fd < 0))
		वापस;

	run_test(cgroup_fd);
	बंद(cgroup_fd);
पूर्ण
