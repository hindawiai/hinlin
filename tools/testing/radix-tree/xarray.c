<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * xarray.c: Userspace shim क्रम XArray test-suite
 * Copyright (c) 2018 Matthew Wilcox <willy@infradead.org>
 */

#घोषणा XA_DEBUG
#समावेश "test.h"

#घोषणा module_init(x)
#घोषणा module_निकास(x)
#घोषणा MODULE_AUTHOR(x)
#घोषणा MODULE_LICENSE(x)
#घोषणा dump_stack()	निश्चित(0)

#समावेश "../../../lib/xarray.c"
#अघोषित XA_DEBUG
#समावेश "../../../lib/test_xarray.c"

व्योम xarray_tests(व्योम)
अणु
	xarray_checks();
	xarray_निकास();
पूर्ण

पूर्णांक __weak मुख्य(व्योम)
अणु
	rcu_रेजिस्टर_thपढ़ो();
	radix_tree_init();
	xarray_tests();
	radix_tree_cpu_dead(1);
	rcu_barrier();
	अगर (nr_allocated)
		म_लिखो("nr_allocated = %d\n", nr_allocated);
	rcu_unरेजिस्टर_thपढ़ो();
	वापस 0;
पूर्ण
