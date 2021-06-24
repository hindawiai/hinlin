<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _TEST_RADIX_TREE_H
#घोषणा _TEST_RADIX_TREE_H

#समावेश "../../../../include/linux/radix-tree.h"

बाह्य पूर्णांक kदो_स्मृति_verbose;
बाह्य पूर्णांक test_verbose;

अटल अंतरभूत व्योम trace_call_rcu(काष्ठा rcu_head *head,
		व्योम (*func)(काष्ठा rcu_head *head))
अणु
	अगर (kदो_स्मृति_verbose)
		म_लिखो("Delaying free of %p to slab\n", (अक्षर *)head -
				दुरत्व(काष्ठा radix_tree_node, rcu_head));
	call_rcu(head, func);
पूर्ण

#घोषणा prपूर्णांकv(verbosity_level, fmt, ...) \
	अगर(test_verbose >= verbosity_level) \
		म_लिखो(fmt, ##__VA_ARGS__)

#अघोषित call_rcu
#घोषणा call_rcu(x, y) trace_call_rcu(x, y)

#पूर्ण_अगर /* _TEST_RADIX_TREE_H */
