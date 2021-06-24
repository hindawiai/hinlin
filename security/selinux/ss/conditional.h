<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/* Authors: Karl MacMillan <kmacmillan@tresys.com>
 *          Frank Mayer <mayerf@tresys.com>
 *
 * Copyright (C) 2003 - 2004 Tresys Technology, LLC
 */

#अगर_अघोषित _CONDITIONAL_H_
#घोषणा _CONDITIONAL_H_

#समावेश "avtab.h"
#समावेश "symtab.h"
#समावेश "policydb.h"
#समावेश "../include/conditional.h"

#घोषणा COND_EXPR_MAXDEPTH 10

/*
 * A conditional expression is a list of चालकs and opeअक्रमs
 * in reverse polish notation.
 */
काष्ठा cond_expr_node अणु
#घोषणा COND_BOOL	1 /* plain bool */
#घोषणा COND_NOT	2 /* !bool */
#घोषणा COND_OR		3 /* bool || bool */
#घोषणा COND_AND	4 /* bool && bool */
#घोषणा COND_XOR	5 /* bool ^ bool */
#घोषणा COND_EQ		6 /* bool == bool */
#घोषणा COND_NEQ	7 /* bool != bool */
#घोषणा COND_LAST	COND_NEQ
	u32 expr_type;
	u32 bool;
पूर्ण;

काष्ठा cond_expr अणु
	काष्ठा cond_expr_node *nodes;
	u32 len;
पूर्ण;

/*
 * Each cond_node contains a list of rules to be enabled/disabled
 * depending on the current value of the conditional expression. This
 * काष्ठा is क्रम that list.
 */
काष्ठा cond_av_list अणु
	काष्ठा avtab_node **nodes;
	u32 len;
पूर्ण;

/*
 * A cond node represents a conditional block in a policy. It
 * contains a conditional expression, the current state of the expression,
 * two lists of rules to enable/disable depending on the value of the
 * expression (the true list corresponds to अगर and the false list corresponds
 * to अन्यथा)..
 */
काष्ठा cond_node अणु
	पूर्णांक cur_state;
	काष्ठा cond_expr expr;
	काष्ठा cond_av_list true_list;
	काष्ठा cond_av_list false_list;
पूर्ण;

व्योम cond_policydb_init(काष्ठा policydb *p);
व्योम cond_policydb_destroy(काष्ठा policydb *p);

पूर्णांक cond_init_bool_indexes(काष्ठा policydb *p);
पूर्णांक cond_destroy_bool(व्योम *key, व्योम *datum, व्योम *p);

पूर्णांक cond_index_bool(व्योम *key, व्योम *datum, व्योम *datap);

पूर्णांक cond_पढ़ो_bool(काष्ठा policydb *p, काष्ठा symtab *s, व्योम *fp);
पूर्णांक cond_पढ़ो_list(काष्ठा policydb *p, व्योम *fp);
पूर्णांक cond_ग_लिखो_bool(व्योम *key, व्योम *datum, व्योम *ptr);
पूर्णांक cond_ग_लिखो_list(काष्ठा policydb *p, व्योम *fp);

व्योम cond_compute_av(काष्ठा avtab *ctab, काष्ठा avtab_key *key,
		काष्ठा av_decision *avd, काष्ठा extended_perms *xperms);
व्योम cond_compute_xperms(काष्ठा avtab *ctab, काष्ठा avtab_key *key,
		काष्ठा extended_perms_decision *xpermd);
व्योम evaluate_cond_nodes(काष्ठा policydb *p);
व्योम cond_policydb_destroy_dup(काष्ठा policydb *p);
पूर्णांक cond_policydb_dup(काष्ठा policydb *new, काष्ठा policydb *orig);

#पूर्ण_अगर /* _CONDITIONAL_H_ */
