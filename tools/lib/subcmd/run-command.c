<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <unistd.h>
#समावेश <sys/types.h>
#समावेश <sys/स्थिति.स>
#समावेश <fcntl.h>
#समावेश <माला.स>
#समावेश <linux/माला.स>
#समावेश <त्रुटिसं.स>
#समावेश <sys/रुको.h>
#समावेश "subcmd-util.h"
#समावेश "run-command.h"
#समावेश "exec-cmd.h"

#घोषणा STRERR_बफ_मानE 128

अटल अंतरभूत व्योम बंद_pair(पूर्णांक fd[2])
अणु
	बंद(fd[0]);
	बंद(fd[1]);
पूर्ण

अटल अंतरभूत व्योम dup_devnull(पूर्णांक to)
अणु
	पूर्णांक fd = खोलो("/dev/null", O_RDWR);
	dup2(fd, to);
	बंद(fd);
पूर्ण

पूर्णांक start_command(काष्ठा child_process *cmd)
अणु
	पूर्णांक need_in, need_out, need_err;
	पूर्णांक fdin[2], fकरोut[2], fderr[2];
	अक्षर sbuf[STRERR_बफ_मानE];

	/*
	 * In हाल of errors we must keep the promise to बंद FDs
	 * that have been passed in via ->in and ->out.
	 */

	need_in = !cmd->no_मानक_निवेश && cmd->in < 0;
	अगर (need_in) अणु
		अगर (pipe(fdin) < 0) अणु
			अगर (cmd->out > 0)
				बंद(cmd->out);
			वापस -ERR_RUN_COMMAND_PIPE;
		पूर्ण
		cmd->in = fdin[1];
	पूर्ण

	need_out = !cmd->no_मानक_निकास
		&& !cmd->मानक_निकास_to_मानक_त्रुटि
		&& cmd->out < 0;
	अगर (need_out) अणु
		अगर (pipe(fकरोut) < 0) अणु
			अगर (need_in)
				बंद_pair(fdin);
			अन्यथा अगर (cmd->in)
				बंद(cmd->in);
			वापस -ERR_RUN_COMMAND_PIPE;
		पूर्ण
		cmd->out = fकरोut[0];
	पूर्ण

	need_err = !cmd->no_मानक_त्रुटि && cmd->err < 0;
	अगर (need_err) अणु
		अगर (pipe(fderr) < 0) अणु
			अगर (need_in)
				बंद_pair(fdin);
			अन्यथा अगर (cmd->in)
				बंद(cmd->in);
			अगर (need_out)
				बंद_pair(fकरोut);
			अन्यथा अगर (cmd->out)
				बंद(cmd->out);
			वापस -ERR_RUN_COMMAND_PIPE;
		पूर्ण
		cmd->err = fderr[0];
	पूर्ण

	ख_साफ(शून्य);
	cmd->pid = विभाजन();
	अगर (!cmd->pid) अणु
		अगर (cmd->no_मानक_निवेश)
			dup_devnull(0);
		अन्यथा अगर (need_in) अणु
			dup2(fdin[0], 0);
			बंद_pair(fdin);
		पूर्ण अन्यथा अगर (cmd->in) अणु
			dup2(cmd->in, 0);
			बंद(cmd->in);
		पूर्ण

		अगर (cmd->no_मानक_त्रुटि)
			dup_devnull(2);
		अन्यथा अगर (need_err) अणु
			dup2(fderr[1], 2);
			बंद_pair(fderr);
		पूर्ण

		अगर (cmd->no_मानक_निकास)
			dup_devnull(1);
		अन्यथा अगर (cmd->मानक_निकास_to_मानक_त्रुटि)
			dup2(2, 1);
		अन्यथा अगर (need_out) अणु
			dup2(fकरोut[1], 1);
			बंद_pair(fकरोut);
		पूर्ण अन्यथा अगर (cmd->out > 1) अणु
			dup2(cmd->out, 1);
			बंद(cmd->out);
		पूर्ण

		अगर (cmd->dir && स_बदलो(cmd->dir))
			die("exec %s: cd to %s failed (%s)", cmd->argv[0],
			    cmd->dir, str_error_r(त्रुटि_सं, sbuf, माप(sbuf)));
		अगर (cmd->env) अणु
			क्रम (; *cmd->env; cmd->env++) अणु
				अगर (म_अक्षर(*cmd->env, '='))
					putenv((अक्षर*)*cmd->env);
				अन्यथा
					unsetenv(*cmd->env);
			पूर्ण
		पूर्ण
		अगर (cmd->preexec_cb)
			cmd->preexec_cb();
		अगर (cmd->exec_cmd) अणु
			execv_cmd(cmd->argv);
		पूर्ण अन्यथा अणु
			execvp(cmd->argv[0], (अक्षर *स्थिर*) cmd->argv);
		पूर्ण
		निकास(127);
	पूर्ण

	अगर (cmd->pid < 0) अणु
		पूर्णांक err = त्रुटि_सं;
		अगर (need_in)
			बंद_pair(fdin);
		अन्यथा अगर (cmd->in)
			बंद(cmd->in);
		अगर (need_out)
			बंद_pair(fकरोut);
		अन्यथा अगर (cmd->out)
			बंद(cmd->out);
		अगर (need_err)
			बंद_pair(fderr);
		वापस err == ENOENT ?
			-ERR_RUN_COMMAND_EXEC :
			-ERR_RUN_COMMAND_FORK;
	पूर्ण

	अगर (need_in)
		बंद(fdin[0]);
	अन्यथा अगर (cmd->in)
		बंद(cmd->in);

	अगर (need_out)
		बंद(fकरोut[1]);
	अन्यथा अगर (cmd->out)
		बंद(cmd->out);

	अगर (need_err)
		बंद(fderr[1]);

	वापस 0;
पूर्ण

अटल पूर्णांक रुको_or_whine(pid_t pid)
अणु
	अक्षर sbuf[STRERR_बफ_मानE];

	क्रम (;;) अणु
		पूर्णांक status, code;
		pid_t रुकोing = रुकोpid(pid, &status, 0);

		अगर (रुकोing < 0) अणु
			अगर (त्रुटि_सं == EINTR)
				जारी;
			ख_लिखो(मानक_त्रुटि, " Error: waitpid failed (%s)",
				str_error_r(त्रुटि_सं, sbuf, माप(sbuf)));
			वापस -ERR_RUN_COMMAND_WAITPID;
		पूर्ण
		अगर (रुकोing != pid)
			वापस -ERR_RUN_COMMAND_WAITPID_WRONG_PID;
		अगर (WIFSIGNALED(status))
			वापस -ERR_RUN_COMMAND_WAITPID_SIGNAL;

		अगर (!WIFEXITED(status))
			वापस -ERR_RUN_COMMAND_WAITPID_NOEXIT;
		code = WEXITSTATUS(status);
		चयन (code) अणु
		हाल 127:
			वापस -ERR_RUN_COMMAND_EXEC;
		हाल 0:
			वापस 0;
		शेष:
			वापस -code;
		पूर्ण
	पूर्ण
पूर्ण

पूर्णांक finish_command(काष्ठा child_process *cmd)
अणु
	वापस रुको_or_whine(cmd->pid);
पूर्ण

पूर्णांक run_command(काष्ठा child_process *cmd)
अणु
	पूर्णांक code = start_command(cmd);
	अगर (code)
		वापस code;
	वापस finish_command(cmd);
पूर्ण

अटल व्योम prepare_run_command_v_opt(काष्ठा child_process *cmd,
				      स्थिर अक्षर **argv,
				      पूर्णांक opt)
अणु
	स_रखो(cmd, 0, माप(*cmd));
	cmd->argv = argv;
	cmd->no_मानक_निवेश = opt & RUN_COMMAND_NO_STDIN ? 1 : 0;
	cmd->exec_cmd = opt & RUN_EXEC_CMD ? 1 : 0;
	cmd->मानक_निकास_to_मानक_त्रुटि = opt & RUN_COMMAND_STDOUT_TO_STDERR ? 1 : 0;
पूर्ण

पूर्णांक run_command_v_opt(स्थिर अक्षर **argv, पूर्णांक opt)
अणु
	काष्ठा child_process cmd;
	prepare_run_command_v_opt(&cmd, argv, opt);
	वापस run_command(&cmd);
पूर्ण
