<शैली गुरु>
/*
 * cn_proc.h - process events connector
 *
 * Copyright (C) Matt Helsley, IBM Corp. 2005
 * Based on cn_विभाजन.h by Nguyen Anh Quynh and Guillaume Thouvenin
 * Copyright (C) 2005 Nguyen Anh Quynh <aquynh@gmail.com>
 * Copyright (C) 2005 Guillaume Thouvenin <guillaume.thouvenin@bull.net>
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy it
 * under the terms of version 2.1 of the GNU Lesser General Public License
 * as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it would be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */
#अगर_अघोषित CN_PROC_H
#घोषणा CN_PROC_H

#समावेश <uapi/linux/cn_proc.h>

#अगर_घोषित CONFIG_PROC_EVENTS
व्योम proc_विभाजन_connector(काष्ठा task_काष्ठा *task);
व्योम proc_exec_connector(काष्ठा task_काष्ठा *task);
व्योम proc_id_connector(काष्ठा task_काष्ठा *task, पूर्णांक which_id);
व्योम proc_sid_connector(काष्ठा task_काष्ठा *task);
व्योम proc_ptrace_connector(काष्ठा task_काष्ठा *task, पूर्णांक which_id);
व्योम proc_comm_connector(काष्ठा task_काष्ठा *task);
व्योम proc_coredump_connector(काष्ठा task_काष्ठा *task);
व्योम proc_निकास_connector(काष्ठा task_काष्ठा *task);
#अन्यथा
अटल अंतरभूत व्योम proc_विभाजन_connector(काष्ठा task_काष्ठा *task)
अणुपूर्ण

अटल अंतरभूत व्योम proc_exec_connector(काष्ठा task_काष्ठा *task)
अणुपूर्ण

अटल अंतरभूत व्योम proc_id_connector(काष्ठा task_काष्ठा *task,
				     पूर्णांक which_id)
अणुपूर्ण

अटल अंतरभूत व्योम proc_sid_connector(काष्ठा task_काष्ठा *task)
अणुपूर्ण

अटल अंतरभूत व्योम proc_comm_connector(काष्ठा task_काष्ठा *task)
अणुपूर्ण

अटल अंतरभूत व्योम proc_ptrace_connector(काष्ठा task_काष्ठा *task,
					 पूर्णांक ptrace_id)
अणुपूर्ण

अटल अंतरभूत व्योम proc_coredump_connector(काष्ठा task_काष्ठा *task)
अणुपूर्ण

अटल अंतरभूत व्योम proc_निकास_connector(काष्ठा task_काष्ठा *task)
अणुपूर्ण
#पूर्ण_अगर	/* CONFIG_PROC_EVENTS */
#पूर्ण_अगर	/* CN_PROC_H */
