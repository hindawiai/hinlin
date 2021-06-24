<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright 2014, Michael Ellerman, IBM Corp.
 */

#अगर_अघोषित _SELFTESTS_POWERPC_PMU_EBB_TRACE_H
#घोषणा _SELFTESTS_POWERPC_PMU_EBB_TRACE_H

#समावेश "utils.h"

#घोषणा TRACE_TYPE_REG		1
#घोषणा TRACE_TYPE_COUNTER	2
#घोषणा TRACE_TYPE_STRING	3
#घोषणा TRACE_TYPE_INDENT	4
#घोषणा TRACE_TYPE_OUTDENT	5

काष्ठा trace_entry
अणु
	u8 type;
	u8 length;
	u8 data[];
पूर्ण;

काष्ठा trace_buffer
अणु
	u64  size;
	bool overflow;
	व्योम *tail;
	u8   data[];
पूर्ण;

काष्ठा trace_buffer *trace_buffer_allocate(u64 size);
पूर्णांक trace_log_reg(काष्ठा trace_buffer *tb, u64 reg, u64 value);
पूर्णांक trace_log_counter(काष्ठा trace_buffer *tb, u64 value);
पूर्णांक trace_log_string(काष्ठा trace_buffer *tb, अक्षर *str);
पूर्णांक trace_log_indent(काष्ठा trace_buffer *tb);
पूर्णांक trace_log_outdent(काष्ठा trace_buffer *tb);
व्योम trace_buffer_prपूर्णांक(काष्ठा trace_buffer *tb);
व्योम trace_prपूर्णांक_location(काष्ठा trace_buffer *tb);

#पूर्ण_अगर /* _SELFTESTS_POWERPC_PMU_EBB_TRACE_H */
