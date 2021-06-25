<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित PERF_SRCLINE_H
#घोषणा PERF_SRCLINE_H

#समावेश <linux/list.h>
#समावेश <linux/rbtree.h>
#समावेश <linux/types.h>

काष्ठा dso;
काष्ठा symbol;

बाह्य bool srcline_full_filename;
अक्षर *get_srcline(काष्ठा dso *dso, u64 addr, काष्ठा symbol *sym,
		  bool show_sym, bool show_addr, u64 ip);
अक्षर *__get_srcline(काष्ठा dso *dso, u64 addr, काष्ठा symbol *sym,
		  bool show_sym, bool show_addr, bool unwind_अंतरभूतs,
		  u64 ip);
व्योम मुक्त_srcline(अक्षर *srcline);
अक्षर *get_srcline_split(काष्ठा dso *dso, u64 addr, अचिन्हित *line);

/* insert the srcline पूर्णांकo the DSO, which will take ownership */
व्योम srcline__tree_insert(काष्ठा rb_root_cached *tree, u64 addr, अक्षर *srcline);
/* find previously inserted srcline */
अक्षर *srcline__tree_find(काष्ठा rb_root_cached *tree, u64 addr);
/* delete all srclines within the tree */
व्योम srcline__tree_delete(काष्ठा rb_root_cached *tree);

#घोषणा SRCLINE_UNKNOWN  ((अक्षर *) "??:0")

काष्ठा अंतरभूत_list अणु
	काष्ठा symbol		*symbol;
	अक्षर			*srcline;
	काष्ठा list_head	list;
पूर्ण;

काष्ठा अंतरभूत_node अणु
	u64			addr;
	काष्ठा list_head	val;
	काष्ठा rb_node		rb_node;
पूर्ण;

/* parse अंतरभूतd frames क्रम the given address */
काष्ठा अंतरभूत_node *dso__parse_addr_अंतरभूतs(काष्ठा dso *dso, u64 addr,
					    काष्ठा symbol *sym);
/* मुक्त resources associated to the अंतरभूत node list */
व्योम अंतरभूत_node__delete(काष्ठा अंतरभूत_node *node);

/* insert the अंतरभूत node list पूर्णांकo the DSO, which will take ownership */
व्योम अंतरभूतs__tree_insert(काष्ठा rb_root_cached *tree,
			  काष्ठा अंतरभूत_node *अंतरभूतs);
/* find previously inserted अंतरभूत node list */
काष्ठा अंतरभूत_node *अंतरभूतs__tree_find(काष्ठा rb_root_cached *tree, u64 addr);
/* delete all nodes within the tree of अंतरभूत_node s */
व्योम अंतरभूतs__tree_delete(काष्ठा rb_root_cached *tree);

#पूर्ण_अगर /* PERF_SRCLINE_H */
