<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __SUBCMD_RUN_COMMAND_H
#घोषणा __SUBCMD_RUN_COMMAND_H

#समावेश <unistd.h>

क्रमागत अणु
	ERR_RUN_COMMAND_FORK = 10000,
	ERR_RUN_COMMAND_EXEC,
	ERR_RUN_COMMAND_PIPE,
	ERR_RUN_COMMAND_WAITPID,
	ERR_RUN_COMMAND_WAITPID_WRONG_PID,
	ERR_RUN_COMMAND_WAITPID_SIGNAL,
	ERR_RUN_COMMAND_WAITPID_NOEXIT,
पूर्ण;
#घोषणा IS_RUN_COMMAND_ERR(x) (-(x) >= ERR_RUN_COMMAND_FORK)

काष्ठा child_process अणु
	स्थिर अक्षर **argv;
	pid_t pid;
	/*
	 * Using .in, .out, .err:
	 * - Specअगरy 0 क्रम no redirections (child inherits मानक_निवेश, मानक_निकास,
	 *   मानक_त्रुटि from parent).
	 * - Specअगरy -1 to have a pipe allocated as follows:
	 *     .in: वापसs the writable pipe end; parent ग_लिखोs to it,
	 *          the पढ़ोable pipe end becomes child's मानक_निवेश
	 *     .out, .err: वापसs the पढ़ोable pipe end; parent पढ़ोs from
	 *          it, the writable pipe end becomes child's मानक_निकास/मानक_त्रुटि
	 *   The caller of start_command() must बंद the वापसed FDs
	 *   after it has completed पढ़ोing from/writing to it!
	 * - Specअगरy > 0 to set a channel to a particular FD as follows:
	 *     .in: a पढ़ोable FD, becomes child's मानक_निवेश
	 *     .out: a writable FD, becomes child's मानक_निकास/मानक_त्रुटि
	 *     .err > 0 not supported
	 *   The specअगरied FD is बंदd by start_command(), even in हाल
	 *   of errors!
	 */
	पूर्णांक in;
	पूर्णांक out;
	पूर्णांक err;
	स्थिर अक्षर *dir;
	स्थिर अक्षर *स्थिर *env;
	अचिन्हित no_मानक_निवेश:1;
	अचिन्हित no_मानक_निकास:1;
	अचिन्हित no_मानक_त्रुटि:1;
	अचिन्हित exec_cmd:1; /* अगर this is to be बाह्यal sub-command */
	अचिन्हित मानक_निकास_to_मानक_त्रुटि:1;
	व्योम (*preexec_cb)(व्योम);
पूर्ण;

पूर्णांक start_command(काष्ठा child_process *);
पूर्णांक finish_command(काष्ठा child_process *);
पूर्णांक run_command(काष्ठा child_process *);

#घोषणा RUN_COMMAND_NO_STDIN 1
#घोषणा RUN_EXEC_CMD	     2	/*If this is to be बाह्यal sub-command */
#घोषणा RUN_COMMAND_STDOUT_TO_STDERR 4
पूर्णांक run_command_v_opt(स्थिर अक्षर **argv, पूर्णांक opt);

#पूर्ण_अगर /* __SUBCMD_RUN_COMMAND_H */
