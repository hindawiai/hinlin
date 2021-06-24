<शैली गुरु>
#अगर_अघोषित __MEM2NODE_H
#घोषणा __MEM2NODE_H

#समावेश <linux/rbtree.h>
#समावेश <linux/types.h>

काष्ठा perf_env;
काष्ठा phys_entry;

काष्ठा mem2node अणु
	काष्ठा rb_root		 root;
	काष्ठा phys_entry	*entries;
	पूर्णांक			 cnt;
पूर्ण;

पूर्णांक  mem2node__init(काष्ठा mem2node *map, काष्ठा perf_env *env);
व्योम mem2node__निकास(काष्ठा mem2node *map);
पूर्णांक  mem2node__node(काष्ठा mem2node *map, u64 addr);

#पूर्ण_अगर /* __MEM2NODE_H */
