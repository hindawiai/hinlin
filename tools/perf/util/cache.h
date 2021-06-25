<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __PERF_CACHE_H
#घोषणा __PERF_CACHE_H

#समावेश "strbuf.h"
#समावेश <subcmd/pager.h>
#समावेश "../ui/ui.h"

#समावेश <linux/compiler.h>
#समावेश <linux/माला.स>

#घोषणा CMD_EXEC_PATH "--exec-path"
#घोषणा CMD_DEBUGFS_सूची "--debugfs-dir="

#घोषणा EXEC_PATH_ENVIRONMENT "PERF_EXEC_PATH"
#घोषणा PERF_DEBUGFS_ENVIRONMENT "PERF_DEBUGFS_DIR"
#घोषणा PERF_TRACEFS_ENVIRONMENT "PERF_TRACEFS_DIR"
#घोषणा PERF_PAGER_ENVIRONMENT "PERF_PAGER"

पूर्णांक split_cmdline(अक्षर *cmdline, स्थिर अक्षर ***argv);

#घोषणा alloc_nr(x) (((x)+16)*3/2)

अटल अंतरभूत पूर्णांक is_असलolute_path(स्थिर अक्षर *path)
अणु
	वापस path[0] == '/';
पूर्ण

अक्षर *mkpath(स्थिर अक्षर *fmt, ...) __म_लिखो(1, 2);

#पूर्ण_अगर /* __PERF_CACHE_H */
