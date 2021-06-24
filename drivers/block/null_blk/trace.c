<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * null_blk trace related helpers.
 *
 * Copyright (C) 2020 Western Digital Corporation or its affiliates.
 */
#समावेश "trace.h"

/*
 * Helper to use क्रम all null_blk traces to extract disk name.
 */
स्थिर अक्षर *nullb_trace_disk_name(काष्ठा trace_seq *p, अक्षर *name)
अणु
	स्थिर अक्षर *ret = trace_seq_buffer_ptr(p);

	अगर (name && *name)
		trace_seq_म_लिखो(p, "disk=%s, ", name);
	trace_seq_अ_दो(p, 0);

	वापस ret;
पूर्ण
