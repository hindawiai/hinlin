<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * A स्थिरraपूर्णांक is a condition that must be satisfied in
 * order क्रम one or more permissions to be granted.
 * Constraपूर्णांकs are used to impose additional restrictions
 * beyond the type-based rules in `te' or the role-based
 * transition rules in `rbac'.  Constraपूर्णांकs are typically
 * used to prevent a process from transitioning to a new user
 * identity or role unless it is in a privileged type.
 * Constraपूर्णांकs are likewise typically used to prevent a
 * process from labeling an object with a dअगरferent user
 * identity.
 *
 * Author : Stephen Smalley, <sds@tycho.nsa.gov>
 */
#अगर_अघोषित _SS_CONSTRAINT_H_
#घोषणा _SS_CONSTRAINT_H_

#समावेश "ebitmap.h"

#घोषणा CEXPR_MAXDEPTH 5

काष्ठा स्थिरraपूर्णांक_expr अणु
#घोषणा CEXPR_NOT		1 /* not expr */
#घोषणा CEXPR_AND		2 /* expr and expr */
#घोषणा CEXPR_OR		3 /* expr or expr */
#घोषणा CEXPR_ATTR		4 /* attr op attr */
#घोषणा CEXPR_NAMES		5 /* attr op names */
	u32 expr_type;		/* expression type */

#घोषणा CEXPR_USER 1		/* user */
#घोषणा CEXPR_ROLE 2		/* role */
#घोषणा CEXPR_TYPE 4		/* type */
#घोषणा CEXPR_TARGET 8		/* target अगर set, source otherwise */
#घोषणा CEXPR_XTARGET 16	/* special 3rd target क्रम validatetrans rule */
#घोषणा CEXPR_L1L2 32		/* low level 1 vs. low level 2 */
#घोषणा CEXPR_L1H2 64		/* low level 1 vs. high level 2 */
#घोषणा CEXPR_H1L2 128		/* high level 1 vs. low level 2 */
#घोषणा CEXPR_H1H2 256		/* high level 1 vs. high level 2 */
#घोषणा CEXPR_L1H1 512		/* low level 1 vs. high level 1 */
#घोषणा CEXPR_L2H2 1024		/* low level 2 vs. high level 2 */
	u32 attr;		/* attribute */

#घोषणा CEXPR_EQ     1		/* == or eq */
#घोषणा CEXPR_NEQ    2		/* != */
#घोषणा CEXPR_DOM    3		/* करोm */
#घोषणा CEXPR_DOMBY  4		/* करोmby  */
#घोषणा CEXPR_INCOMP 5		/* incomp */
	u32 op;			/* चालक */

	काष्ठा ebiपंचांगap names;	/* names */
	काष्ठा type_set *type_names;

	काष्ठा स्थिरraपूर्णांक_expr *next;   /* next expression */
पूर्ण;

काष्ठा स्थिरraपूर्णांक_node अणु
	u32 permissions;	/* स्थिरrained permissions */
	काष्ठा स्थिरraपूर्णांक_expr *expr;	/* स्थिरraपूर्णांक on permissions */
	काष्ठा स्थिरraपूर्णांक_node *next;	/* next स्थिरraपूर्णांक */
पूर्ण;

#पूर्ण_अगर	/* _SS_CONSTRAINT_H_ */
