<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Backtrace support क्रम Microblaze
 *
 * Copyright (C) 2010  Digital Design Corporation
 */

#अगर_अघोषित __MICROBLAZE_UNWIND_H
#घोषणा __MICROBLAZE_UNWIND_H

काष्ठा stack_trace;

काष्ठा trap_handler_info अणु
	अचिन्हित दीर्घ start_addr;
	अचिन्हित दीर्घ end_addr;
	स्थिर अक्षर    *trap_name;
पूर्ण;
बाह्य काष्ठा trap_handler_info microblaze_trap_handlers;

बाह्य स्थिर अक्षर _hw_exception_handler;
बाह्य स्थिर अक्षर ex_handler_unhandled;

व्योम microblaze_unwind(काष्ठा task_काष्ठा *task, काष्ठा stack_trace *trace,
		       स्थिर अक्षर *loglvl);

#पूर्ण_अगर	/* __MICROBLAZE_UNWIND_H */

