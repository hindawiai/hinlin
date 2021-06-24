<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __SUBCMD_EXEC_CMD_H
#घोषणा __SUBCMD_EXEC_CMD_H

बाह्य व्योम exec_cmd_init(स्थिर अक्षर *exec_name, स्थिर अक्षर *prefix,
			  स्थिर अक्षर *exec_path, स्थिर अक्षर *exec_path_env);

बाह्य व्योम set_argv_exec_path(स्थिर अक्षर *exec_path);
बाह्य स्थिर अक्षर *extract_argv0_path(स्थिर अक्षर *path);
बाह्य व्योम setup_path(व्योम);
बाह्य पूर्णांक execv_cmd(स्थिर अक्षर **argv); /* शून्य terminated */
बाह्य पूर्णांक execl_cmd(स्थिर अक्षर *cmd, ...);
/* get_argv_exec_path and प्रणाली_path वापस दो_स्मृति'd string, caller must मुक्त it */
बाह्य अक्षर *get_argv_exec_path(व्योम);
बाह्य अक्षर *प्रणाली_path(स्थिर अक्षर *path);

#पूर्ण_अगर /* __SUBCMD_EXEC_CMD_H */
