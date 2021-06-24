<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_LIST_SORT_H
#घोषणा _LINUX_LIST_SORT_H

#समावेश <linux/types.h>

काष्ठा list_head;

प्रकार पूर्णांक __attribute__((nonnull(2,3))) (*list_cmp_func_t)(व्योम *,
		स्थिर काष्ठा list_head *, स्थिर काष्ठा list_head *);

__attribute__((nonnull(2,3)))
व्योम list_sort(व्योम *priv, काष्ठा list_head *head, list_cmp_func_t cmp);
#पूर्ण_अगर
