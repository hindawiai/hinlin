<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <पूर्णांकernal/lib.h>
#समावेश <subcmd/parse-options.h>
#समावेश <api/fd/array.h>
#समावेश <api/fs/fs.h>
#समावेश <linux/zभाग.स>
#समावेश <linux/माला.स>
#समावेश <linux/सीमा.स>
#समावेश <माला.स>
#समावेश <sys/file.h>
#समावेश <संकेत.स>
#समावेश <मानककोष.स>
#समावेश <समय.स>
#समावेश <मानकपन.स>
#समावेश <unistd.h>
#समावेश <त्रुटिसं.स>
#समावेश <sys/inotअगरy.h>
#समावेश <libgen.h>
#समावेश <sys/types.h>
#समावेश <sys/socket.h>
#समावेश <sys/un.h>
#समावेश <sys/स्थिति.स>
#समावेश <sys/संकेतfd.h>
#समावेश <sys/रुको.h>
#समावेश <poll.h>
#समावेश "builtin.h"
#समावेश "perf.h"
#समावेश "debug.h"
#समावेश "config.h"
#समावेश "util.h"

#घोषणा SESSION_OUTPUT  "output"
#घोषणा SESSION_CONTROL "control"
#घोषणा SESSION_ACK     "ack"

/*
 * Session states:
 *
 *   OK       - session is up and running
 *   RECONFIG - session is pending क्रम reconfiguration,
 *              new values are alपढ़ोy loaded in session object
 *   KILL     - session is pending to be समाप्तed
 *
 * Session object lअगरe and its state is मुख्यtained by
 * following functions:
 *
 *  setup_server_config
 *    - पढ़ोs config file and setup session objects
 *      with following states:
 *
 *      OK       - no change needed
 *      RECONFIG - session needs to be changed
 *                 (run variable changed)
 *      KILL     - session needs to be समाप्तed
 *                 (session is no दीर्घer in config file)
 *
 *  daemon__reconfig
 *    - scans session objects and करोes following actions
 *      क्रम states:
 *
 *      OK       - skip
 *      RECONFIG - session is समाप्तed and re-run with new config
 *      KILL     - session is समाप्तed
 *
 *    - all sessions have OK state on the function निकास
 */
क्रमागत daemon_session_state अणु
	OK,
	RECONFIG,
	KILL,
पूर्ण;

काष्ठा daemon_session अणु
	अक्षर				*base;
	अक्षर				*name;
	अक्षर				*run;
	अक्षर				*control;
	पूर्णांक				 pid;
	काष्ठा list_head		 list;
	क्रमागत daemon_session_state	 state;
	समय_प्रकार				 start;
पूर्ण;

काष्ठा daemon अणु
	स्थिर अक्षर		*config;
	अक्षर			*config_real;
	अक्षर			*config_base;
	स्थिर अक्षर		*csv_sep;
	स्थिर अक्षर		*base_user;
	अक्षर			*base;
	काष्ठा list_head	 sessions;
	खाता			*out;
	अक्षर			 perf[PATH_MAX];
	पूर्णांक			 संकेत_fd;
	समय_प्रकार			 start;
पूर्ण;

अटल काष्ठा daemon __daemon = अणु
	.sessions = LIST_HEAD_INIT(__daemon.sessions),
पूर्ण;

अटल स्थिर अक्षर * स्थिर daemon_usage[] = अणु
	"perf daemon start [<options>]",
	"perf daemon [<options>]",
	शून्य
पूर्ण;

अटल bool करोne;

अटल व्योम sig_handler(पूर्णांक sig __maybe_unused)
अणु
	करोne = true;
पूर्ण

अटल काष्ठा daemon_session *daemon__add_session(काष्ठा daemon *config, अक्षर *name)
अणु
	काष्ठा daemon_session *session = zalloc(माप(*session));

	अगर (!session)
		वापस शून्य;

	session->name = strdup(name);
	अगर (!session->name) अणु
		मुक्त(session);
		वापस शून्य;
	पूर्ण

	session->pid = -1;
	list_add_tail(&session->list, &config->sessions);
	वापस session;
पूर्ण

अटल काष्ठा daemon_session *daemon__find_session(काष्ठा daemon *daemon, अक्षर *name)
अणु
	काष्ठा daemon_session *session;

	list_क्रम_each_entry(session, &daemon->sessions, list) अणु
		अगर (!म_भेद(session->name, name))
			वापस session;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल पूर्णांक get_session_name(स्थिर अक्षर *var, अक्षर *session, पूर्णांक len)
अणु
	स्थिर अक्षर *p = var + माप("session-") - 1;

	जबतक (*p != '.' && *p != 0x0 && len--)
		*session++ = *p++;

	*session = 0;
	वापस *p == '.' ? 0 : -EINVAL;
पूर्ण

अटल पूर्णांक session_config(काष्ठा daemon *daemon, स्थिर अक्षर *var, स्थिर अक्षर *value)
अणु
	काष्ठा daemon_session *session;
	अक्षर name[100];

	अगर (get_session_name(var, name, माप(name) - 1))
		वापस -EINVAL;

	var = म_अक्षर(var, '.');
	अगर (!var)
		वापस -EINVAL;

	var++;

	session = daemon__find_session(daemon, name);

	अगर (!session) अणु
		/* New session is defined. */
		session = daemon__add_session(daemon, name);
		अगर (!session)
			वापस -ENOMEM;

		pr_debug("reconfig: found new session %s\n", name);

		/* Trigger reconfig to start it. */
		session->state = RECONFIG;
	पूर्ण अन्यथा अगर (session->state == KILL) अणु
		/* Current session is defined, no action needed. */
		pr_debug("reconfig: found current session %s\n", name);
		session->state = OK;
	पूर्ण

	अगर (!म_भेद(var, "run")) अणु
		bool same = false;

		अगर (session->run)
			same = !म_भेद(session->run, value);

		अगर (!same) अणु
			अगर (session->run) अणु
				मुक्त(session->run);
				pr_debug("reconfig: session %s is changed\n", name);
			पूर्ण

			session->run = strdup(value);
			अगर (!session->run)
				वापस -ENOMEM;

			/*
			 * Either new or changed run value is defined,
			 * trigger reconfig क्रम the session.
			 */
			session->state = RECONFIG;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक server_config(स्थिर अक्षर *var, स्थिर अक्षर *value, व्योम *cb)
अणु
	काष्ठा daemon *daemon = cb;

	अगर (strstarts(var, "session-")) अणु
		वापस session_config(daemon, var, value);
	पूर्ण अन्यथा अगर (!म_भेद(var, "daemon.base") && !daemon->base_user) अणु
		अगर (daemon->base && म_भेद(daemon->base, value)) अणु
			pr_err("failed: can't redefine base, bailing out\n");
			वापस -EINVAL;
		पूर्ण
		daemon->base = strdup(value);
		अगर (!daemon->base)
			वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक client_config(स्थिर अक्षर *var, स्थिर अक्षर *value, व्योम *cb)
अणु
	काष्ठा daemon *daemon = cb;

	अगर (!म_भेद(var, "daemon.base") && !daemon->base_user) अणु
		daemon->base = strdup(value);
		अगर (!daemon->base)
			वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक check_base(काष्ठा daemon *daemon)
अणु
	काष्ठा stat st;

	अगर (!daemon->base) अणु
		pr_err("failed: base not defined\n");
		वापस -EINVAL;
	पूर्ण

	अगर (stat(daemon->base, &st)) अणु
		चयन (त्रुटि_सं) अणु
		हाल EACCES:
			pr_err("failed: permission denied for '%s' base\n",
			       daemon->base);
			वापस -EACCES;
		हाल ENOENT:
			pr_err("failed: base '%s' does not exists\n",
			       daemon->base);
			वापस -EACCES;
		शेष:
			pr_err("failed: can't access base '%s': %s\n",
			       daemon->base, म_त्रुटि(त्रुटि_सं));
			वापस -त्रुटि_सं;
		पूर्ण
	पूर्ण

	अगर ((st.st_mode & S_IFMT) != S_IFसूची) अणु
		pr_err("failed: base '%s' is not directory\n",
		       daemon->base);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक setup_client_config(काष्ठा daemon *daemon)
अणु
	काष्ठा perf_config_set *set = perf_config_set__load_file(daemon->config_real);
	पूर्णांक err = -ENOMEM;

	अगर (set) अणु
		err = perf_config_set(set, client_config, daemon);
		perf_config_set__delete(set);
	पूर्ण

	वापस err ?: check_base(daemon);
पूर्ण

अटल पूर्णांक setup_server_config(काष्ठा daemon *daemon)
अणु
	काष्ठा perf_config_set *set;
	काष्ठा daemon_session *session;
	पूर्णांक err = -ENOMEM;

	pr_debug("reconfig: started\n");

	/*
	 * Mark all sessions क्रम समाप्त, the server config
	 * will set following states, see explanation at
	 * क्रमागत daemon_session_state declaration.
	 */
	list_क्रम_each_entry(session, &daemon->sessions, list)
		session->state = KILL;

	set = perf_config_set__load_file(daemon->config_real);
	अगर (set) अणु
		err = perf_config_set(set, server_config, daemon);
		perf_config_set__delete(set);
	पूर्ण

	वापस err ?: check_base(daemon);
पूर्ण

अटल पूर्णांक daemon_session__run(काष्ठा daemon_session *session,
			       काष्ठा daemon *daemon)
अणु
	अक्षर buf[PATH_MAX];
	अक्षर **argv;
	पूर्णांक argc, fd;

	अगर (aप्र_लिखो(&session->base, "%s/session-%s",
		     daemon->base, session->name) < 0) अणु
		लिखो_त्रुटि("failed: asprintf");
		वापस -1;
	पूर्ण

	अगर (सूची_गढ़ो(session->base, 0755) && त्रुटि_सं != EEXIST) अणु
		लिखो_त्रुटि("failed: mkdir");
		वापस -1;
	पूर्ण

	session->start = समय(शून्य);

	session->pid = विभाजन();
	अगर (session->pid < 0)
		वापस -1;
	अगर (session->pid > 0) अणु
		pr_info("reconfig: ruining session [%s:%d]: %s\n",
			session->name, session->pid, session->run);
		वापस 0;
	पूर्ण

	अगर (स_बदलो(session->base)) अणु
		लिखो_त्रुटि("failed: chdir");
		वापस -1;
	पूर्ण

	fd = खोलो("/dev/null", O_RDONLY);
	अगर (fd < 0) अणु
		लिखो_त्रुटि("failed: open /dev/null");
		वापस -1;
	पूर्ण

	dup2(fd, 0);
	बंद(fd);

	fd = खोलो(SESSION_OUTPUT, O_RDWR|O_CREAT|O_TRUNC, 0644);
	अगर (fd < 0) अणु
		लिखो_त्रुटि("failed: open session output");
		वापस -1;
	पूर्ण

	dup2(fd, 1);
	dup2(fd, 2);
	बंद(fd);

	अगर (mkfअगरo(SESSION_CONTROL, 0600) && त्रुटि_सं != EEXIST) अणु
		लिखो_त्रुटि("failed: create control fifo");
		वापस -1;
	पूर्ण

	अगर (mkfअगरo(SESSION_ACK, 0600) && त्रुटि_सं != EEXIST) अणु
		लिखो_त्रुटि("failed: create ack fifo");
		वापस -1;
	पूर्ण

	scnम_लिखो(buf, माप(buf), "%s record --control=fifo:%s,%s %s",
		  daemon->perf, SESSION_CONTROL, SESSION_ACK, session->run);

	argv = argv_split(buf, &argc);
	अगर (!argv)
		निकास(-1);

	निकास(execve(daemon->perf, argv, शून्य));
	वापस -1;
पूर्ण

अटल pid_t handle_संकेतfd(काष्ठा daemon *daemon)
अणु
	काष्ठा daemon_session *session;
	काष्ठा संकेतfd_siginfo si;
	sमाप_प्रकार err;
	पूर्णांक status;
	pid_t pid;

	/*
	 * Take संकेत fd data as pure संकेत notअगरication and check all
	 * the sessions state. The reason is that multiple संकेतs can get
	 * coalesced in kernel and we can receive only single संकेत even
	 * अगर multiple SIGCHLD were generated.
	 */
	err = पढ़ो(daemon->संकेत_fd, &si, माप(काष्ठा संकेतfd_siginfo));
	अगर (err != माप(काष्ठा संकेतfd_siginfo)) अणु
		pr_err("failed to read signal fd\n");
		वापस -1;
	पूर्ण

	list_क्रम_each_entry(session, &daemon->sessions, list) अणु
		अगर (session->pid == -1)
			जारी;

		pid = रुकोpid(session->pid, &status, WNOHANG);
		अगर (pid <= 0)
			जारी;

		अगर (WIFEXITED(status)) अणु
			pr_info("session '%s' exited, status=%d\n",
				session->name, WEXITSTATUS(status));
		पूर्ण अन्यथा अगर (WIFSIGNALED(status)) अणु
			pr_info("session '%s' killed (signal %d)\n",
				session->name, WTERMSIG(status));
		पूर्ण अन्यथा अगर (WIFSTOPPED(status)) अणु
			pr_info("session '%s' stopped (signal %d)\n",
				session->name, WSTOPSIG(status));
		पूर्ण अन्यथा अणु
			pr_info("session '%s' Unexpected status (0x%x)\n",
				session->name, status);
		पूर्ण

		session->state = KILL;
		session->pid = -1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक daemon_session__रुको(काष्ठा daemon_session *session, काष्ठा daemon *daemon,
				पूर्णांक secs)
अणु
	काष्ठा pollfd pollfd = अणु
		.fd	= daemon->संकेत_fd,
		.events	= POLLIN,
	पूर्ण;
	समय_प्रकार start;

	start = समय(शून्य);

	करो अणु
		पूर्णांक err = poll(&pollfd, 1, 1000);

		अगर (err > 0) अणु
			handle_संकेतfd(daemon);
		पूर्ण अन्यथा अगर (err < 0) अणु
			लिखो_त्रुटि("failed: poll\n");
			वापस -1;
		पूर्ण

		अगर (start + secs < समय(शून्य))
			वापस -1;
	पूर्ण जबतक (session->pid != -1);

	वापस 0;
पूर्ण

अटल bool daemon__has_alive_session(काष्ठा daemon *daemon)
अणु
	काष्ठा daemon_session *session;

	list_क्रम_each_entry(session, &daemon->sessions, list) अणु
		अगर (session->pid != -1)
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल पूर्णांक daemon__रुको(काष्ठा daemon *daemon, पूर्णांक secs)
अणु
	काष्ठा pollfd pollfd = अणु
		.fd	= daemon->संकेत_fd,
		.events	= POLLIN,
	पूर्ण;
	समय_प्रकार start;

	start = समय(शून्य);

	करो अणु
		पूर्णांक err = poll(&pollfd, 1, 1000);

		अगर (err > 0) अणु
			handle_संकेतfd(daemon);
		पूर्ण अन्यथा अगर (err < 0) अणु
			लिखो_त्रुटि("failed: poll\n");
			वापस -1;
		पूर्ण

		अगर (start + secs < समय(शून्य))
			वापस -1;
	पूर्ण जबतक (daemon__has_alive_session(daemon));

	वापस 0;
पूर्ण

अटल पूर्णांक daemon_session__control(काष्ठा daemon_session *session,
				   स्थिर अक्षर *msg, bool करो_ack)
अणु
	काष्ठा pollfd pollfd = अणु .events = POLLIN, पूर्ण;
	अक्षर control_path[PATH_MAX];
	अक्षर ack_path[PATH_MAX];
	पूर्णांक control, ack = -1, len;
	अक्षर buf[20];
	पूर्णांक ret = -1;
	sमाप_प्रकार err;

	/* खोलो the control file */
	scnम_लिखो(control_path, माप(control_path), "%s/%s",
		  session->base, SESSION_CONTROL);

	control = खोलो(control_path, O_WRONLY|O_NONBLOCK);
	अगर (!control)
		वापस -1;

	अगर (करो_ack) अणु
		/* खोलो the ack file */
		scnम_लिखो(ack_path, माप(ack_path), "%s/%s",
			  session->base, SESSION_ACK);

		ack = खोलो(ack_path, O_RDONLY, O_NONBLOCK);
		अगर (!ack) अणु
			बंद(control);
			वापस -1;
		पूर्ण
	पूर्ण

	/* ग_लिखो the command */
	len = म_माप(msg);

	err = ग_लिखोn(control, msg, len);
	अगर (err != len) अणु
		pr_err("failed: write to control pipe: %d (%s)\n",
		       त्रुटि_सं, control_path);
		जाओ out;
	पूर्ण

	अगर (!करो_ack)
		जाओ out;

	/* रुको क्रम an ack */
	pollfd.fd = ack;

	अगर (!poll(&pollfd, 1, 2000)) अणु
		pr_err("failed: control ack timeout\n");
		जाओ out;
	पूर्ण

	अगर (!(pollfd.revents & POLLIN)) अणु
		pr_err("failed: did not received an ack\n");
		जाओ out;
	पूर्ण

	err = पढ़ो(ack, buf, माप(buf));
	अगर (err > 0)
		ret = म_भेद(buf, "ack\n");
	अन्यथा
		लिखो_त्रुटि("failed: read ack %d\n");

out:
	अगर (ack != -1)
		बंद(ack);

	बंद(control);
	वापस ret;
पूर्ण

अटल पूर्णांक setup_server_socket(काष्ठा daemon *daemon)
अणु
	काष्ठा sockaddr_un addr;
	अक्षर path[PATH_MAX];
	पूर्णांक fd = socket(AF_UNIX, SOCK_STREAM, 0);

	अगर (fd < 0) अणु
		ख_लिखो(मानक_त्रुटि, "socket: %s\n", म_त्रुटि(त्रुटि_सं));
		वापस -1;
	पूर्ण

	अगर (fcntl(fd, F_SETFD, FD_CLOEXEC)) अणु
		लिखो_त्रुटि("failed: fcntl FD_CLOEXEC");
		बंद(fd);
		वापस -1;
	पूर्ण

	scnम_लिखो(path, माप(path), "%s/control", daemon->base);

	अगर (म_माप(path) + 1 >= माप(addr.sun_path)) अणु
		pr_err("failed: control path too long '%s'\n", path);
		बंद(fd);
		वापस -1;
	पूर्ण

	स_रखो(&addr, 0, माप(addr));
	addr.sun_family = AF_UNIX;

	strlcpy(addr.sun_path, path, माप(addr.sun_path) - 1);
	unlink(path);

	अगर (bind(fd, (काष्ठा sockaddr *)&addr, माप(addr)) == -1) अणु
		लिखो_त्रुटि("failed: bind");
		बंद(fd);
		वापस -1;
	पूर्ण

	अगर (listen(fd, 1) == -1) अणु
		लिखो_त्रुटि("failed: listen");
		बंद(fd);
		वापस -1;
	पूर्ण

	वापस fd;
पूर्ण

क्रमागत अणु
	CMD_LIST   = 0,
	CMD_SIGNAL = 1,
	CMD_STOP   = 2,
	CMD_PING   = 3,
	CMD_MAX,
पूर्ण;

#घोषणा SESSION_MAX 64

जोड़ cmd अणु
	पूर्णांक cmd;

	/* CMD_LIST */
	काष्ठा अणु
		पूर्णांक	cmd;
		पूर्णांक	verbose;
		अक्षर	csv_sep;
	पूर्ण list;

	/* CMD_SIGNAL */
	काष्ठा अणु
		पूर्णांक	cmd;
		पूर्णांक	sig;
		अक्षर	name[SESSION_MAX];
	पूर्ण संकेत;

	/* CMD_PING */
	काष्ठा अणु
		पूर्णांक	cmd;
		अक्षर	name[SESSION_MAX];
	पूर्ण ping;
पूर्ण;

क्रमागत अणु
	PING_OK	  = 0,
	PING_FAIL = 1,
	PING_MAX,
पूर्ण;

अटल पूर्णांक daemon_session__ping(काष्ठा daemon_session *session)
अणु
	वापस daemon_session__control(session, "ping", true) ?  PING_FAIL : PING_OK;
पूर्ण

अटल पूर्णांक cmd_session_list(काष्ठा daemon *daemon, जोड़ cmd *cmd, खाता *out)
अणु
	अक्षर csv_sep = cmd->list.csv_sep;
	काष्ठा daemon_session *session;
	समय_प्रकार curr = समय(शून्य);

	अगर (csv_sep) अणु
		ख_लिखो(out, "%d%c%s%c%s%c%s/%s",
			/* pid daemon  */
			getpid(), csv_sep, "daemon",
			/* base */
			csv_sep, daemon->base,
			/* output */
			csv_sep, daemon->base, SESSION_OUTPUT);

		ख_लिखो(out, "%c%s/%s",
			/* lock */
			csv_sep, daemon->base, "lock");

		ख_लिखो(out, "%c%lu",
			/* session up समय */
			csv_sep, (curr - daemon->start) / 60);

		ख_लिखो(out, "\n");
	पूर्ण अन्यथा अणु
		ख_लिखो(out, "[%d:daemon] base: %s\n", getpid(), daemon->base);
		अगर (cmd->list.verbose) अणु
			ख_लिखो(out, "  output:  %s/%s\n",
				daemon->base, SESSION_OUTPUT);
			ख_लिखो(out, "  lock:    %s/lock\n",
				daemon->base);
			ख_लिखो(out, "  up:      %lu minutes\n",
				(curr - daemon->start) / 60);
		पूर्ण
	पूर्ण

	list_क्रम_each_entry(session, &daemon->sessions, list) अणु
		अगर (csv_sep) अणु
			ख_लिखो(out, "%d%c%s%c%s",
				/* pid */
				session->pid,
				/* name */
				csv_sep, session->name,
				/* base */
				csv_sep, session->run);

			ख_लिखो(out, "%c%s%c%s/%s",
				/* session dir */
				csv_sep, session->base,
				/* session output */
				csv_sep, session->base, SESSION_OUTPUT);

			ख_लिखो(out, "%c%s/%s%c%s/%s",
				/* session control */
				csv_sep, session->base, SESSION_CONTROL,
				/* session ack */
				csv_sep, session->base, SESSION_ACK);

			ख_लिखो(out, "%c%lu",
				/* session up समय */
				csv_sep, (curr - session->start) / 60);

			ख_लिखो(out, "\n");
		पूर्ण अन्यथा अणु
			ख_लिखो(out, "[%d:%s] perf record %s\n",
				session->pid, session->name, session->run);
			अगर (!cmd->list.verbose)
				जारी;
			ख_लिखो(out, "  base:    %s\n",
				session->base);
			ख_लिखो(out, "  output:  %s/%s\n",
				session->base, SESSION_OUTPUT);
			ख_लिखो(out, "  control: %s/%s\n",
				session->base, SESSION_CONTROL);
			ख_लिखो(out, "  ack:     %s/%s\n",
				session->base, SESSION_ACK);
			ख_लिखो(out, "  up:      %lu minutes\n",
				(curr - session->start) / 60);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक daemon_session__संकेत(काष्ठा daemon_session *session, पूर्णांक sig)
अणु
	अगर (session->pid < 0)
		वापस -1;
	वापस समाप्त(session->pid, sig);
पूर्ण

अटल पूर्णांक cmd_session_समाप्त(काष्ठा daemon *daemon, जोड़ cmd *cmd, खाता *out)
अणु
	काष्ठा daemon_session *session;
	bool all = false;

	all = !म_भेद(cmd->संकेत.name, "all");

	list_क्रम_each_entry(session, &daemon->sessions, list) अणु
		अगर (all || !म_भेद(cmd->संकेत.name, session->name)) अणु
			daemon_session__संकेत(session, cmd->संकेत.sig);
			ख_लिखो(out, "signal %d sent to session '%s [%d]'\n",
				cmd->संकेत.sig, session->name, session->pid);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर अक्षर *ping_str[PING_MAX] = अणु
	[PING_OK]   = "OK",
	[PING_FAIL] = "FAIL",
पूर्ण;

अटल पूर्णांक cmd_session_ping(काष्ठा daemon *daemon, जोड़ cmd *cmd, खाता *out)
अणु
	काष्ठा daemon_session *session;
	bool all = false, found = false;

	all = !म_भेद(cmd->ping.name, "all");

	list_क्रम_each_entry(session, &daemon->sessions, list) अणु
		अगर (all || !म_भेद(cmd->ping.name, session->name)) अणु
			पूर्णांक state = daemon_session__ping(session);

			ख_लिखो(out, "%-4s %s\n", ping_str[state], session->name);
			found = true;
		पूर्ण
	पूर्ण

	अगर (!found && !all) अणु
		ख_लिखो(out, "%-4s %s (not found)\n",
			ping_str[PING_FAIL], cmd->ping.name);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक handle_server_socket(काष्ठा daemon *daemon, पूर्णांक sock_fd)
अणु
	पूर्णांक ret = -1, fd;
	खाता *out = शून्य;
	जोड़ cmd cmd;

	fd = accept(sock_fd, शून्य, शून्य);
	अगर (fd < 0) अणु
		लिखो_त्रुटि("failed: accept");
		वापस -1;
	पूर्ण

	अगर (माप(cmd) != पढ़ोn(fd, &cmd, माप(cmd))) अणु
		लिखो_त्रुटि("failed: read");
		जाओ out;
	पूर्ण

	out = fकरोpen(fd, "w");
	अगर (!out) अणु
		लिखो_त्रुटि("failed: fdopen");
		जाओ out;
	पूर्ण

	चयन (cmd.cmd) अणु
	हाल CMD_LIST:
		ret = cmd_session_list(daemon, &cmd, out);
		अवरोध;
	हाल CMD_SIGNAL:
		ret = cmd_session_समाप्त(daemon, &cmd, out);
		अवरोध;
	हाल CMD_STOP:
		करोne = 1;
		ret = 0;
		pr_debug("perf daemon is exciting\n");
		अवरोध;
	हाल CMD_PING:
		ret = cmd_session_ping(daemon, &cmd, out);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	ख_बंद(out);
out:
	/* If out is defined, then fd is बंदd via ख_बंद. */
	अगर (!out)
		बंद(fd);
	वापस ret;
पूर्ण

अटल पूर्णांक setup_client_socket(काष्ठा daemon *daemon)
अणु
	काष्ठा sockaddr_un addr;
	अक्षर path[PATH_MAX];
	पूर्णांक fd = socket(AF_UNIX, SOCK_STREAM, 0);

	अगर (fd == -1) अणु
		लिखो_त्रुटि("failed: socket");
		वापस -1;
	पूर्ण

	scnम_लिखो(path, माप(path), "%s/control", daemon->base);

	अगर (म_माप(path) + 1 >= माप(addr.sun_path)) अणु
		pr_err("failed: control path too long '%s'\n", path);
		बंद(fd);
		वापस -1;
	पूर्ण

	स_रखो(&addr, 0, माप(addr));
	addr.sun_family = AF_UNIX;
	strlcpy(addr.sun_path, path, माप(addr.sun_path) - 1);

	अगर (connect(fd, (काष्ठा sockaddr *) &addr, माप(addr)) == -1) अणु
		लिखो_त्रुटि("failed: connect");
		बंद(fd);
		वापस -1;
	पूर्ण

	वापस fd;
पूर्ण

अटल व्योम daemon_session__समाप्त(काष्ठा daemon_session *session,
				 काष्ठा daemon *daemon)
अणु
	पूर्णांक how = 0;

	करो अणु
		चयन (how) अणु
		हाल 0:
			daemon_session__control(session, "stop", false);
			अवरोध;
		हाल 1:
			daemon_session__संकेत(session, संक_इति);
			अवरोध;
		हाल 2:
			daemon_session__संकेत(session, SIGKILL);
			अवरोध;
		शेष:
			pr_err("failed to wait for session %s\n",
			       session->name);
			वापस;
		पूर्ण
		how++;

	पूर्ण जबतक (daemon_session__रुको(session, daemon, 10));
पूर्ण

अटल व्योम daemon__संकेत(काष्ठा daemon *daemon, पूर्णांक sig)
अणु
	काष्ठा daemon_session *session;

	list_क्रम_each_entry(session, &daemon->sessions, list)
		daemon_session__संकेत(session, sig);
पूर्ण

अटल व्योम daemon_session__delete(काष्ठा daemon_session *session)
अणु
	मुक्त(session->base);
	मुक्त(session->name);
	मुक्त(session->run);
	मुक्त(session);
पूर्ण

अटल व्योम daemon_session__हटाओ(काष्ठा daemon_session *session)
अणु
	list_del(&session->list);
	daemon_session__delete(session);
पूर्ण

अटल व्योम daemon__stop(काष्ठा daemon *daemon)
अणु
	काष्ठा daemon_session *session;

	list_क्रम_each_entry(session, &daemon->sessions, list)
		daemon_session__control(session, "stop", false);
पूर्ण

अटल व्योम daemon__समाप्त(काष्ठा daemon *daemon)
अणु
	पूर्णांक how = 0;

	करो अणु
		चयन (how) अणु
		हाल 0:
			daemon__stop(daemon);
			अवरोध;
		हाल 1:
			daemon__संकेत(daemon, संक_इति);
			अवरोध;
		हाल 2:
			daemon__संकेत(daemon, SIGKILL);
			अवरोध;
		शेष:
			pr_err("failed to wait for sessions\n");
			वापस;
		पूर्ण
		how++;

	पूर्ण जबतक (daemon__रुको(daemon, 10));
पूर्ण

अटल व्योम daemon__निकास(काष्ठा daemon *daemon)
अणु
	काष्ठा daemon_session *session, *h;

	list_क्रम_each_entry_safe(session, h, &daemon->sessions, list)
		daemon_session__हटाओ(session);

	मुक्त(daemon->config_real);
	मुक्त(daemon->config_base);
	मुक्त(daemon->base);
पूर्ण

अटल पूर्णांक daemon__reconfig(काष्ठा daemon *daemon)
अणु
	काष्ठा daemon_session *session, *n;

	list_क्रम_each_entry_safe(session, n, &daemon->sessions, list) अणु
		/* No change. */
		अगर (session->state == OK)
			जारी;

		/* Remove session. */
		अगर (session->state == KILL) अणु
			अगर (session->pid > 0) अणु
				daemon_session__समाप्त(session, daemon);
				pr_info("reconfig: session '%s' killed\n", session->name);
			पूर्ण
			daemon_session__हटाओ(session);
			जारी;
		पूर्ण

		/* Reconfig session. */
		अगर (session->pid > 0) अणु
			daemon_session__समाप्त(session, daemon);
			pr_info("reconfig: session '%s' killed\n", session->name);
		पूर्ण
		अगर (daemon_session__run(session, daemon))
			वापस -1;

		session->state = OK;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक setup_config_changes(काष्ठा daemon *daemon)
अणु
	अक्षर *basen = strdup(daemon->config_real);
	अक्षर *dirn  = strdup(daemon->config_real);
	अक्षर *base, *dir;
	पूर्णांक fd, wd = -1;

	अगर (!dirn || !basen)
		जाओ out;

	fd = inotअगरy_init1(IN_NONBLOCK|O_CLOEXEC);
	अगर (fd < 0) अणु
		लिखो_त्रुटि("failed: inotify_init");
		जाओ out;
	पूर्ण

	dir = स_नाम(dirn);
	base = basename(basen);
	pr_debug("config file: %s, dir: %s\n", base, dir);

	wd = inotअगरy_add_watch(fd, dir, IN_CLOSE_WRITE);
	अगर (wd >= 0) अणु
		daemon->config_base = strdup(base);
		अगर (!daemon->config_base) अणु
			बंद(fd);
			wd = -1;
		पूर्ण
	पूर्ण अन्यथा अणु
		लिखो_त्रुटि("failed: inotify_add_watch");
	पूर्ण

out:
	मुक्त(basen);
	मुक्त(dirn);
	वापस wd < 0 ? -1 : fd;
पूर्ण

अटल bool process_inotअगरy_event(काष्ठा daemon *daemon, अक्षर *buf, sमाप_प्रकार len)
अणु
	अक्षर *p = buf;

	जबतक (p < (buf + len)) अणु
		काष्ठा inotअगरy_event *event = (काष्ठा inotअगरy_event *) p;

		/*
		 * We monitor config directory, check अगर our
		 * config file was changes.
		 */
		अगर ((event->mask & IN_CLOSE_WRITE) &&
		    !(event->mask & IN_ISसूची)) अणु
			अगर (!म_भेद(event->name, daemon->config_base))
				वापस true;
		पूर्ण
		p += माप(*event) + event->len;
	पूर्ण
	वापस false;
पूर्ण

अटल पूर्णांक handle_config_changes(काष्ठा daemon *daemon, पूर्णांक conf_fd,
				 bool *config_changed)
अणु
	अक्षर buf[4096];
	sमाप_प्रकार len;

	जबतक (!(*config_changed)) अणु
		len = पढ़ो(conf_fd, buf, माप(buf));
		अगर (len == -1) अणु
			अगर (त्रुटि_सं != EAGAIN) अणु
				लिखो_त्रुटि("failed: read");
				वापस -1;
			पूर्ण
			वापस 0;
		पूर्ण
		*config_changed = process_inotअगरy_event(daemon, buf, len);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक setup_config(काष्ठा daemon *daemon)
अणु
	अगर (daemon->base_user) अणु
		daemon->base = strdup(daemon->base_user);
		अगर (!daemon->base)
			वापस -ENOMEM;
	पूर्ण

	अगर (daemon->config) अणु
		अक्षर *real = realpath(daemon->config, शून्य);

		अगर (!real) अणु
			लिखो_त्रुटि("failed: realpath");
			वापस -1;
		पूर्ण
		daemon->config_real = real;
		वापस 0;
	पूर्ण

	अगर (perf_config_प्रणाली() && !access(perf_etc_perfconfig(), R_OK))
		daemon->config_real = strdup(perf_etc_perfconfig());
	अन्यथा अगर (perf_config_global() && perf_home_perfconfig())
		daemon->config_real = strdup(perf_home_perfconfig());

	वापस daemon->config_real ? 0 : -1;
पूर्ण

#अगर_अघोषित F_TLOCK
#घोषणा F_TLOCK 2

#समावेश <sys/file.h>

अटल पूर्णांक lockf(पूर्णांक fd, पूर्णांक cmd, off_t len)
अणु
	अगर (cmd != F_TLOCK || len != 0)
		वापस -1;

	वापस flock(fd, LOCK_EX | LOCK_NB);
पूर्ण
#पूर्ण_अगर // F_TLOCK

/*
 * Each daemon tries to create and lock BASE/lock file,
 * अगर it's successful we are sure we're the only daemon
 * running over the BASE.
 *
 * Once daemon is finished, file descriptor to lock file
 * is बंदd and lock is released.
 */
अटल पूर्णांक check_lock(काष्ठा daemon *daemon)
अणु
	अक्षर path[PATH_MAX];
	अक्षर buf[20];
	पूर्णांक fd, pid;
	sमाप_प्रकार len;

	scnम_लिखो(path, माप(path), "%s/lock", daemon->base);

	fd = खोलो(path, O_RDWR|O_CREAT|O_CLOEXEC, 0640);
	अगर (fd < 0)
		वापस -1;

	अगर (lockf(fd, F_TLOCK, 0) < 0) अणु
		filename__पढ़ो_पूर्णांक(path, &pid);
		ख_लिखो(मानक_त्रुटि, "failed: another perf daemon (pid %d) owns %s\n",
			pid, daemon->base);
		बंद(fd);
		वापस -1;
	पूर्ण

	scnम_लिखो(buf, माप(buf), "%d", getpid());
	len = म_माप(buf);

	अगर (ग_लिखो(fd, buf, len) != len) अणु
		लिखो_त्रुटि("failed: write");
		बंद(fd);
		वापस -1;
	पूर्ण

	अगर (ftruncate(fd, len)) अणु
		लिखो_त्रुटि("failed: ftruncate");
		बंद(fd);
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक go_background(काष्ठा daemon *daemon)
अणु
	पूर्णांक pid, fd;

	pid = विभाजन();
	अगर (pid < 0)
		वापस -1;

	अगर (pid > 0)
		वापस 1;

	अगर (setsid() < 0)
		वापस -1;

	अगर (check_lock(daemon))
		वापस -1;

	umask(0);

	अगर (स_बदलो(daemon->base)) अणु
		लिखो_त्रुटि("failed: chdir");
		वापस -1;
	पूर्ण

	fd = खोलो("output", O_RDWR|O_CREAT|O_TRUNC, 0644);
	अगर (fd < 0) अणु
		लिखो_त्रुटि("failed: open");
		वापस -1;
	पूर्ण

	अगर (fcntl(fd, F_SETFD, FD_CLOEXEC)) अणु
		लिखो_त्रुटि("failed: fcntl FD_CLOEXEC");
		बंद(fd);
		वापस -1;
	पूर्ण

	बंद(0);
	dup2(fd, 1);
	dup2(fd, 2);
	बंद(fd);

	daemon->out = fकरोpen(1, "w");
	अगर (!daemon->out) अणु
		बंद(1);
		बंद(2);
		वापस -1;
	पूर्ण

	रखो_बफ(daemon->out, शून्य);
	वापस 0;
पूर्ण

अटल पूर्णांक setup_संकेतfd(काष्ठा daemon *daemon)
अणु
	sigset_t mask;

	sigemptyset(&mask);
	sigaddset(&mask, SIGCHLD);

	अगर (sigprocmask(SIG_BLOCK, &mask, शून्य) == -1)
		वापस -1;

	daemon->संकेत_fd = संकेतfd(-1, &mask, SFD_NONBLOCK|SFD_CLOEXEC);
	वापस daemon->संकेत_fd;
पूर्ण

अटल पूर्णांक __cmd_start(काष्ठा daemon *daemon, काष्ठा option parent_options[],
		       पूर्णांक argc, स्थिर अक्षर **argv)
अणु
	bool क्रमeground = false;
	काष्ठा option start_options[] = अणु
		OPT_BOOLEAN('f', "foreground", &क्रमeground, "stay on console"),
		OPT_PARENT(parent_options),
		OPT_END()
	पूर्ण;
	पूर्णांक sock_fd = -1, conf_fd = -1, संकेत_fd = -1;
	पूर्णांक sock_pos, file_pos, संकेत_pos;
	काष्ठा fdarray fda;
	पूर्णांक err = 0;

	argc = parse_options(argc, argv, start_options, daemon_usage, 0);
	अगर (argc)
		usage_with_options(daemon_usage, start_options);

	daemon->start = समय(शून्य);

	अगर (setup_config(daemon)) अणु
		pr_err("failed: config not found\n");
		वापस -1;
	पूर्ण

	अगर (setup_server_config(daemon))
		वापस -1;

	अगर (क्रमeground && check_lock(daemon))
		वापस -1;

	अगर (!क्रमeground) अणु
		err = go_background(daemon);
		अगर (err) अणु
			/* original process, निकास normally */
			अगर (err == 1)
				err = 0;
			daemon__निकास(daemon);
			वापस err;
		पूर्ण
	पूर्ण

	debug_set_file(daemon->out);
	debug_set_display_समय(true);

	pr_info("daemon started (pid %d)\n", getpid());

	fdarray__init(&fda, 3);

	sock_fd = setup_server_socket(daemon);
	अगर (sock_fd < 0)
		जाओ out;

	conf_fd = setup_config_changes(daemon);
	अगर (conf_fd < 0)
		जाओ out;

	संकेत_fd = setup_संकेतfd(daemon);
	अगर (संकेत_fd < 0)
		जाओ out;

	sock_pos = fdarray__add(&fda, sock_fd, POLLIN|POLLERR|POLLHUP, 0);
	अगर (sock_pos < 0)
		जाओ out;

	file_pos = fdarray__add(&fda, conf_fd, POLLIN|POLLERR|POLLHUP, 0);
	अगर (file_pos < 0)
		जाओ out;

	संकेत_pos = fdarray__add(&fda, संकेत_fd, POLLIN|POLLERR|POLLHUP, 0);
	अगर (संकेत_pos < 0)
		जाओ out;

	संकेत(संक_विघ्न, sig_handler);
	संकेत(संक_इति, sig_handler);
	संकेत(SIGPIPE, संक_छोड़ो);

	जबतक (!करोne && !err) अणु
		err = daemon__reconfig(daemon);

		अगर (!err && fdarray__poll(&fda, -1)) अणु
			bool reconfig = false;

			अगर (fda.entries[sock_pos].revents & POLLIN)
				err = handle_server_socket(daemon, sock_fd);
			अगर (fda.entries[file_pos].revents & POLLIN)
				err = handle_config_changes(daemon, conf_fd, &reconfig);
			अगर (fda.entries[संकेत_pos].revents & POLLIN)
				err = handle_संकेतfd(daemon) < 0;

			अगर (reconfig)
				err = setup_server_config(daemon);
		पूर्ण
	पूर्ण

out:
	fdarray__निकास(&fda);

	daemon__समाप्त(daemon);
	daemon__निकास(daemon);

	अगर (sock_fd != -1)
		बंद(sock_fd);
	अगर (conf_fd != -1)
		बंद(conf_fd);
	अगर (संकेत_fd != -1)
		बंद(संकेत_fd);

	pr_info("daemon exited\n");
	ख_बंद(daemon->out);
	वापस err;
पूर्ण

अटल पूर्णांक send_cmd(काष्ठा daemon *daemon, जोड़ cmd *cmd)
अणु
	पूर्णांक ret = -1, fd;
	अक्षर *line = शून्य;
	माप_प्रकार len = 0;
	sमाप_प्रकार nपढ़ो;
	खाता *in = शून्य;

	अगर (setup_client_config(daemon))
		वापस -1;

	fd = setup_client_socket(daemon);
	अगर (fd < 0)
		वापस -1;

	अगर (माप(*cmd) != ग_लिखोn(fd, cmd, माप(*cmd))) अणु
		लिखो_त्रुटि("failed: write");
		जाओ out;
	पूर्ण

	in = fकरोpen(fd, "r");
	अगर (!in) अणु
		लिखो_त्रुटि("failed: fdopen");
		जाओ out;
	पूर्ण

	जबतक ((nपढ़ो = getline(&line, &len, in)) != -1) अणु
		अगर (ख_डालो(line, nपढ़ो, 1, मानक_निकास) != 1)
			जाओ out_ख_बंद;
		ख_साफ(मानक_निकास);
	पूर्ण

	ret = 0;
out_ख_बंद:
	ख_बंद(in);
	मुक्त(line);
out:
	/* If in is defined, then fd is बंदd via ख_बंद. */
	अगर (!in)
		बंद(fd);
	वापस ret;
पूर्ण

अटल पूर्णांक send_cmd_list(काष्ठा daemon *daemon)
अणु
	जोड़ cmd cmd = अणु .cmd = CMD_LIST, पूर्ण;

	cmd.list.verbose = verbose;
	cmd.list.csv_sep = daemon->csv_sep ? *daemon->csv_sep : 0;

	वापस send_cmd(daemon, &cmd);
पूर्ण

अटल पूर्णांक __cmd_संकेत(काष्ठा daemon *daemon, काष्ठा option parent_options[],
			पूर्णांक argc, स्थिर अक्षर **argv)
अणु
	स्थिर अक्षर *name = "all";
	काष्ठा option start_options[] = अणु
		OPT_STRING(0, "session", &name, "session",
			"Sent signal to specific session"),
		OPT_PARENT(parent_options),
		OPT_END()
	पूर्ण;
	जोड़ cmd cmd;

	argc = parse_options(argc, argv, start_options, daemon_usage, 0);
	अगर (argc)
		usage_with_options(daemon_usage, start_options);

	अगर (setup_config(daemon)) अणु
		pr_err("failed: config not found\n");
		वापस -1;
	पूर्ण

	cmd.संकेत.cmd = CMD_SIGNAL,
	cmd.संकेत.sig = SIGUSR2;
	म_नकलन(cmd.संकेत.name, name, माप(cmd.संकेत.name) - 1);

	वापस send_cmd(daemon, &cmd);
पूर्ण

अटल पूर्णांक __cmd_stop(काष्ठा daemon *daemon, काष्ठा option parent_options[],
			पूर्णांक argc, स्थिर अक्षर **argv)
अणु
	काष्ठा option start_options[] = अणु
		OPT_PARENT(parent_options),
		OPT_END()
	पूर्ण;
	जोड़ cmd cmd = अणु .cmd = CMD_STOP, पूर्ण;

	argc = parse_options(argc, argv, start_options, daemon_usage, 0);
	अगर (argc)
		usage_with_options(daemon_usage, start_options);

	अगर (setup_config(daemon)) अणु
		pr_err("failed: config not found\n");
		वापस -1;
	पूर्ण

	वापस send_cmd(daemon, &cmd);
पूर्ण

अटल पूर्णांक __cmd_ping(काष्ठा daemon *daemon, काष्ठा option parent_options[],
		      पूर्णांक argc, स्थिर अक्षर **argv)
अणु
	स्थिर अक्षर *name = "all";
	काष्ठा option ping_options[] = अणु
		OPT_STRING(0, "session", &name, "session",
			"Ping to specific session"),
		OPT_PARENT(parent_options),
		OPT_END()
	पूर्ण;
	जोड़ cmd cmd = अणु .cmd = CMD_PING, पूर्ण;

	argc = parse_options(argc, argv, ping_options, daemon_usage, 0);
	अगर (argc)
		usage_with_options(daemon_usage, ping_options);

	अगर (setup_config(daemon)) अणु
		pr_err("failed: config not found\n");
		वापस -1;
	पूर्ण

	scnम_लिखो(cmd.ping.name, माप(cmd.ping.name), "%s", name);
	वापस send_cmd(daemon, &cmd);
पूर्ण

पूर्णांक cmd_daemon(पूर्णांक argc, स्थिर अक्षर **argv)
अणु
	काष्ठा option daemon_options[] = अणु
		OPT_INCR('v', "verbose", &verbose, "be more verbose"),
		OPT_STRING(0, "config", &__daemon.config,
			"config file", "config file path"),
		OPT_STRING(0, "base", &__daemon.base_user,
			"directory", "base directory"),
		OPT_STRING_OPTARG('x', "field-separator", &__daemon.csv_sep,
			"field separator", "print counts with custom separator", ","),
		OPT_END()
	पूर्ण;

	perf_exe(__daemon.perf, माप(__daemon.perf));
	__daemon.out = मानक_निकास;

	argc = parse_options(argc, argv, daemon_options, daemon_usage,
			     PARSE_OPT_STOP_AT_NON_OPTION);

	अगर (argc) अणु
		अगर (!म_भेद(argv[0], "start"))
			वापस __cmd_start(&__daemon, daemon_options, argc, argv);
		अगर (!म_भेद(argv[0], "signal"))
			वापस __cmd_संकेत(&__daemon, daemon_options, argc, argv);
		अन्यथा अगर (!म_भेद(argv[0], "stop"))
			वापस __cmd_stop(&__daemon, daemon_options, argc, argv);
		अन्यथा अगर (!म_भेद(argv[0], "ping"))
			वापस __cmd_ping(&__daemon, daemon_options, argc, argv);

		pr_err("failed: unknown command '%s'\n", argv[0]);
		वापस -1;
	पूर्ण

	अगर (setup_config(&__daemon)) अणु
		pr_err("failed: config not found\n");
		वापस -1;
	पूर्ण

	वापस send_cmd_list(&__daemon);
पूर्ण
