<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LIVEPATCH_PATCH_H
#घोषणा _LIVEPATCH_PATCH_H

#समावेश <linux/livepatch.h>
#समावेश <linux/list.h>
#समावेश <linux/ftrace.h>

/**
 * काष्ठा klp_ops - काष्ठाure क्रम tracking रेजिस्टरed ftrace ops काष्ठाs
 *
 * A single ftrace_ops is shared between all enabled replacement functions
 * (klp_func काष्ठाs) which have the same old_func.  This allows the चयन
 * between function versions to happen instantaneously by updating the klp_ops
 * काष्ठा's func_stack list.  The winner is the klp_func at the top of the
 * func_stack (front of the list).
 *
 * @node:	node क्रम the global klp_ops list
 * @func_stack:	list head क्रम the stack of klp_func's (active func is on top)
 * @fops:	रेजिस्टरed ftrace ops काष्ठा
 */
काष्ठा klp_ops अणु
	काष्ठा list_head node;
	काष्ठा list_head func_stack;
	काष्ठा ftrace_ops fops;
पूर्ण;

काष्ठा klp_ops *klp_find_ops(व्योम *old_func);

पूर्णांक klp_patch_object(काष्ठा klp_object *obj);
व्योम klp_unpatch_object(काष्ठा klp_object *obj);
व्योम klp_unpatch_objects(काष्ठा klp_patch *patch);
व्योम klp_unpatch_objects_dynamic(काष्ठा klp_patch *patch);

#पूर्ण_अगर /* _LIVEPATCH_PATCH_H */
