<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2002 Roman Zippel <zippel@linux-m68k.org>
 */

#समावेश <प्रकार.स>
#समावेश <त्रुटिसं.स>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>

#समावेश "lkc.h"

#घोषणा DEBUG_EXPR	0

अटल काष्ठा expr *expr_eliminate_yn(काष्ठा expr *e);

काष्ठा expr *expr_alloc_symbol(काष्ठा symbol *sym)
अणु
	काष्ठा expr *e = xसुस्मृति(1, माप(*e));
	e->type = E_SYMBOL;
	e->left.sym = sym;
	वापस e;
पूर्ण

काष्ठा expr *expr_alloc_one(क्रमागत expr_type type, काष्ठा expr *ce)
अणु
	काष्ठा expr *e = xसुस्मृति(1, माप(*e));
	e->type = type;
	e->left.expr = ce;
	वापस e;
पूर्ण

काष्ठा expr *expr_alloc_two(क्रमागत expr_type type, काष्ठा expr *e1, काष्ठा expr *e2)
अणु
	काष्ठा expr *e = xसुस्मृति(1, माप(*e));
	e->type = type;
	e->left.expr = e1;
	e->right.expr = e2;
	वापस e;
पूर्ण

काष्ठा expr *expr_alloc_comp(क्रमागत expr_type type, काष्ठा symbol *s1, काष्ठा symbol *s2)
अणु
	काष्ठा expr *e = xसुस्मृति(1, माप(*e));
	e->type = type;
	e->left.sym = s1;
	e->right.sym = s2;
	वापस e;
पूर्ण

काष्ठा expr *expr_alloc_and(काष्ठा expr *e1, काष्ठा expr *e2)
अणु
	अगर (!e1)
		वापस e2;
	वापस e2 ? expr_alloc_two(E_AND, e1, e2) : e1;
पूर्ण

काष्ठा expr *expr_alloc_or(काष्ठा expr *e1, काष्ठा expr *e2)
अणु
	अगर (!e1)
		वापस e2;
	वापस e2 ? expr_alloc_two(E_OR, e1, e2) : e1;
पूर्ण

काष्ठा expr *expr_copy(स्थिर काष्ठा expr *org)
अणु
	काष्ठा expr *e;

	अगर (!org)
		वापस शून्य;

	e = xदो_स्मृति(माप(*org));
	स_नकल(e, org, माप(*org));
	चयन (org->type) अणु
	हाल E_SYMBOL:
		e->left = org->left;
		अवरोध;
	हाल E_NOT:
		e->left.expr = expr_copy(org->left.expr);
		अवरोध;
	हाल E_EQUAL:
	हाल E_GEQ:
	हाल E_GTH:
	हाल E_LEQ:
	हाल E_LTH:
	हाल E_UNEQUAL:
		e->left.sym = org->left.sym;
		e->right.sym = org->right.sym;
		अवरोध;
	हाल E_AND:
	हाल E_OR:
	हाल E_LIST:
		e->left.expr = expr_copy(org->left.expr);
		e->right.expr = expr_copy(org->right.expr);
		अवरोध;
	शेष:
		ख_लिखो(मानक_त्रुटि, "can't copy type %d\n", e->type);
		मुक्त(e);
		e = शून्य;
		अवरोध;
	पूर्ण

	वापस e;
पूर्ण

व्योम expr_मुक्त(काष्ठा expr *e)
अणु
	अगर (!e)
		वापस;

	चयन (e->type) अणु
	हाल E_SYMBOL:
		अवरोध;
	हाल E_NOT:
		expr_मुक्त(e->left.expr);
		अवरोध;
	हाल E_EQUAL:
	हाल E_GEQ:
	हाल E_GTH:
	हाल E_LEQ:
	हाल E_LTH:
	हाल E_UNEQUAL:
		अवरोध;
	हाल E_OR:
	हाल E_AND:
		expr_मुक्त(e->left.expr);
		expr_मुक्त(e->right.expr);
		अवरोध;
	शेष:
		ख_लिखो(मानक_त्रुटि, "how to free type %d?\n", e->type);
		अवरोध;
	पूर्ण
	मुक्त(e);
पूर्ण

अटल पूर्णांक trans_count;

#घोषणा e1 (*ep1)
#घोषणा e2 (*ep2)

/*
 * expr_eliminate_eq() helper.
 *
 * Walks the two expression trees given in 'ep1' and 'ep2'. Any node that करोes
 * not have type 'type' (E_OR/E_AND) is considered a leaf, and is compared
 * against all other leaves. Two equal leaves are both replaced with either 'y'
 * or 'n' as appropriate for 'type', to be eliminated later.
 */
अटल व्योम __expr_eliminate_eq(क्रमागत expr_type type, काष्ठा expr **ep1, काष्ठा expr **ep2)
अणु
	/* Recurse करोwn to leaves */

	अगर (e1->type == type) अणु
		__expr_eliminate_eq(type, &e1->left.expr, &e2);
		__expr_eliminate_eq(type, &e1->right.expr, &e2);
		वापस;
	पूर्ण
	अगर (e2->type == type) अणु
		__expr_eliminate_eq(type, &e1, &e2->left.expr);
		__expr_eliminate_eq(type, &e1, &e2->right.expr);
		वापस;
	पूर्ण

	/* e1 and e2 are leaves. Compare them. */

	अगर (e1->type == E_SYMBOL && e2->type == E_SYMBOL &&
	    e1->left.sym == e2->left.sym &&
	    (e1->left.sym == &symbol_yes || e1->left.sym == &symbol_no))
		वापस;
	अगर (!expr_eq(e1, e2))
		वापस;

	/* e1 and e2 are equal leaves. Prepare them क्रम elimination. */

	trans_count++;
	expr_मुक्त(e1); expr_मुक्त(e2);
	चयन (type) अणु
	हाल E_OR:
		e1 = expr_alloc_symbol(&symbol_no);
		e2 = expr_alloc_symbol(&symbol_no);
		अवरोध;
	हाल E_AND:
		e1 = expr_alloc_symbol(&symbol_yes);
		e2 = expr_alloc_symbol(&symbol_yes);
		अवरोध;
	शेष:
		;
	पूर्ण
पूर्ण

/*
 * Reग_लिखोs the expressions 'ep1' and 'ep2' to हटाओ opeअक्रमs common to both.
 * Example reductions:
 *
 *	ep1: A && B           ->  ep1: y
 *	ep2: A && B && C      ->  ep2: C
 *
 *	ep1: A || B           ->  ep1: n
 *	ep2: A || B || C      ->  ep2: C
 *
 *	ep1: A && (B && FOO)  ->  ep1: FOO
 *	ep2: (BAR && B) && A  ->  ep2: BAR
 *
 *	ep1: A && (B || C)    ->  ep1: y
 *	ep2: (C || B) && A    ->  ep2: y
 *
 * Comparisons are करोne between all opeअक्रमs at the same "level" of && or ||.
 * For example, in the expression 'e1 && (e2 || e3) && (e4 || e5)', the
 * following opeअक्रमs will be compared:
 *
 *	- 'e1', 'e2 || e3', and 'e4 || e5', against each other
 *	- e2 against e3
 *	- e4 against e5
 *
 * Parentheses are irrelevant within a single level. 'e1 && (e2 && e3)' and
 * '(e1 && e2) && e3' are both a single level.
 *
 * See __expr_eliminate_eq() as well.
 */
व्योम expr_eliminate_eq(काष्ठा expr **ep1, काष्ठा expr **ep2)
अणु
	अगर (!e1 || !e2)
		वापस;
	चयन (e1->type) अणु
	हाल E_OR:
	हाल E_AND:
		__expr_eliminate_eq(e1->type, ep1, ep2);
	शेष:
		;
	पूर्ण
	अगर (e1->type != e2->type) चयन (e2->type) अणु
	हाल E_OR:
	हाल E_AND:
		__expr_eliminate_eq(e2->type, ep1, ep2);
	शेष:
		;
	पूर्ण
	e1 = expr_eliminate_yn(e1);
	e2 = expr_eliminate_yn(e2);
पूर्ण

#अघोषित e1
#अघोषित e2

/*
 * Returns true अगर 'e1' and 'e2' are equal, after minor simplअगरication. Two
 * &&/|| expressions are considered equal अगर every opeअक्रम in one expression
 * equals some opeअक्रम in the other (opeअक्रमs करो not need to appear in the same
 * order), recursively.
 */
पूर्णांक expr_eq(काष्ठा expr *e1, काष्ठा expr *e2)
अणु
	पूर्णांक res, old_count;

	/*
	 * A शून्य expr is taken to be yes, but there's also a dअगरferent way to
	 * represent yes. expr_is_yes() checks क्रम either representation.
	 */
	अगर (!e1 || !e2)
		वापस expr_is_yes(e1) && expr_is_yes(e2);

	अगर (e1->type != e2->type)
		वापस 0;
	चयन (e1->type) अणु
	हाल E_EQUAL:
	हाल E_GEQ:
	हाल E_GTH:
	हाल E_LEQ:
	हाल E_LTH:
	हाल E_UNEQUAL:
		वापस e1->left.sym == e2->left.sym && e1->right.sym == e2->right.sym;
	हाल E_SYMBOL:
		वापस e1->left.sym == e2->left.sym;
	हाल E_NOT:
		वापस expr_eq(e1->left.expr, e2->left.expr);
	हाल E_AND:
	हाल E_OR:
		e1 = expr_copy(e1);
		e2 = expr_copy(e2);
		old_count = trans_count;
		expr_eliminate_eq(&e1, &e2);
		res = (e1->type == E_SYMBOL && e2->type == E_SYMBOL &&
		       e1->left.sym == e2->left.sym);
		expr_मुक्त(e1);
		expr_मुक्त(e2);
		trans_count = old_count;
		वापस res;
	हाल E_LIST:
	हाल E_RANGE:
	हाल E_NONE:
		/* panic */;
	पूर्ण

	अगर (DEBUG_EXPR) अणु
		expr_fprपूर्णांक(e1, मानक_निकास);
		म_लिखो(" = ");
		expr_fprपूर्णांक(e2, मानक_निकास);
		म_लिखो(" ?\n");
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Recursively perक्रमms the following simplअगरications in-place (as well as the
 * corresponding simplअगरications with swapped opeअक्रमs):
 *
 *	expr && n  ->  n
 *	expr && y  ->  expr
 *	expr || n  ->  expr
 *	expr || y  ->  y
 *
 * Returns the optimized expression.
 */
अटल काष्ठा expr *expr_eliminate_yn(काष्ठा expr *e)
अणु
	काष्ठा expr *पंचांगp;

	अगर (e) चयन (e->type) अणु
	हाल E_AND:
		e->left.expr = expr_eliminate_yn(e->left.expr);
		e->right.expr = expr_eliminate_yn(e->right.expr);
		अगर (e->left.expr->type == E_SYMBOL) अणु
			अगर (e->left.expr->left.sym == &symbol_no) अणु
				expr_मुक्त(e->left.expr);
				expr_मुक्त(e->right.expr);
				e->type = E_SYMBOL;
				e->left.sym = &symbol_no;
				e->right.expr = शून्य;
				वापस e;
			पूर्ण अन्यथा अगर (e->left.expr->left.sym == &symbol_yes) अणु
				मुक्त(e->left.expr);
				पंचांगp = e->right.expr;
				*e = *(e->right.expr);
				मुक्त(पंचांगp);
				वापस e;
			पूर्ण
		पूर्ण
		अगर (e->right.expr->type == E_SYMBOL) अणु
			अगर (e->right.expr->left.sym == &symbol_no) अणु
				expr_मुक्त(e->left.expr);
				expr_मुक्त(e->right.expr);
				e->type = E_SYMBOL;
				e->left.sym = &symbol_no;
				e->right.expr = शून्य;
				वापस e;
			पूर्ण अन्यथा अगर (e->right.expr->left.sym == &symbol_yes) अणु
				मुक्त(e->right.expr);
				पंचांगp = e->left.expr;
				*e = *(e->left.expr);
				मुक्त(पंचांगp);
				वापस e;
			पूर्ण
		पूर्ण
		अवरोध;
	हाल E_OR:
		e->left.expr = expr_eliminate_yn(e->left.expr);
		e->right.expr = expr_eliminate_yn(e->right.expr);
		अगर (e->left.expr->type == E_SYMBOL) अणु
			अगर (e->left.expr->left.sym == &symbol_no) अणु
				मुक्त(e->left.expr);
				पंचांगp = e->right.expr;
				*e = *(e->right.expr);
				मुक्त(पंचांगp);
				वापस e;
			पूर्ण अन्यथा अगर (e->left.expr->left.sym == &symbol_yes) अणु
				expr_मुक्त(e->left.expr);
				expr_मुक्त(e->right.expr);
				e->type = E_SYMBOL;
				e->left.sym = &symbol_yes;
				e->right.expr = शून्य;
				वापस e;
			पूर्ण
		पूर्ण
		अगर (e->right.expr->type == E_SYMBOL) अणु
			अगर (e->right.expr->left.sym == &symbol_no) अणु
				मुक्त(e->right.expr);
				पंचांगp = e->left.expr;
				*e = *(e->left.expr);
				मुक्त(पंचांगp);
				वापस e;
			पूर्ण अन्यथा अगर (e->right.expr->left.sym == &symbol_yes) अणु
				expr_मुक्त(e->left.expr);
				expr_मुक्त(e->right.expr);
				e->type = E_SYMBOL;
				e->left.sym = &symbol_yes;
				e->right.expr = शून्य;
				वापस e;
			पूर्ण
		पूर्ण
		अवरोध;
	शेष:
		;
	पूर्ण
	वापस e;
पूर्ण

/*
 * bool FOO!=n => FOO
 */
काष्ठा expr *expr_trans_bool(काष्ठा expr *e)
अणु
	अगर (!e)
		वापस शून्य;
	चयन (e->type) अणु
	हाल E_AND:
	हाल E_OR:
	हाल E_NOT:
		e->left.expr = expr_trans_bool(e->left.expr);
		e->right.expr = expr_trans_bool(e->right.expr);
		अवरोध;
	हाल E_UNEQUAL:
		// FOO!=n -> FOO
		अगर (e->left.sym->type == S_TRISTATE) अणु
			अगर (e->right.sym == &symbol_no) अणु
				e->type = E_SYMBOL;
				e->right.sym = शून्य;
			पूर्ण
		पूर्ण
		अवरोध;
	शेष:
		;
	पूर्ण
	वापस e;
पूर्ण

/*
 * e1 || e2 -> ?
 */
अटल काष्ठा expr *expr_join_or(काष्ठा expr *e1, काष्ठा expr *e2)
अणु
	काष्ठा expr *पंचांगp;
	काष्ठा symbol *sym1, *sym2;

	अगर (expr_eq(e1, e2))
		वापस expr_copy(e1);
	अगर (e1->type != E_EQUAL && e1->type != E_UNEQUAL && e1->type != E_SYMBOL && e1->type != E_NOT)
		वापस शून्य;
	अगर (e2->type != E_EQUAL && e2->type != E_UNEQUAL && e2->type != E_SYMBOL && e2->type != E_NOT)
		वापस शून्य;
	अगर (e1->type == E_NOT) अणु
		पंचांगp = e1->left.expr;
		अगर (पंचांगp->type != E_EQUAL && पंचांगp->type != E_UNEQUAL && पंचांगp->type != E_SYMBOL)
			वापस शून्य;
		sym1 = पंचांगp->left.sym;
	पूर्ण अन्यथा
		sym1 = e1->left.sym;
	अगर (e2->type == E_NOT) अणु
		अगर (e2->left.expr->type != E_SYMBOL)
			वापस शून्य;
		sym2 = e2->left.expr->left.sym;
	पूर्ण अन्यथा
		sym2 = e2->left.sym;
	अगर (sym1 != sym2)
		वापस शून्य;
	अगर (sym1->type != S_BOOLEAN && sym1->type != S_TRISTATE)
		वापस शून्य;
	अगर (sym1->type == S_TRISTATE) अणु
		अगर (e1->type == E_EQUAL && e2->type == E_EQUAL &&
		    ((e1->right.sym == &symbol_yes && e2->right.sym == &symbol_mod) ||
		     (e1->right.sym == &symbol_mod && e2->right.sym == &symbol_yes))) अणु
			// (a='y') || (a='m') -> (a!='n')
			वापस expr_alloc_comp(E_UNEQUAL, sym1, &symbol_no);
		पूर्ण
		अगर (e1->type == E_EQUAL && e2->type == E_EQUAL &&
		    ((e1->right.sym == &symbol_yes && e2->right.sym == &symbol_no) ||
		     (e1->right.sym == &symbol_no && e2->right.sym == &symbol_yes))) अणु
			// (a='y') || (a='n') -> (a!='m')
			वापस expr_alloc_comp(E_UNEQUAL, sym1, &symbol_mod);
		पूर्ण
		अगर (e1->type == E_EQUAL && e2->type == E_EQUAL &&
		    ((e1->right.sym == &symbol_mod && e2->right.sym == &symbol_no) ||
		     (e1->right.sym == &symbol_no && e2->right.sym == &symbol_mod))) अणु
			// (a='m') || (a='n') -> (a!='y')
			वापस expr_alloc_comp(E_UNEQUAL, sym1, &symbol_yes);
		पूर्ण
	पूर्ण
	अगर (sym1->type == S_BOOLEAN && sym1 == sym2) अणु
		अगर ((e1->type == E_NOT && e1->left.expr->type == E_SYMBOL && e2->type == E_SYMBOL) ||
		    (e2->type == E_NOT && e2->left.expr->type == E_SYMBOL && e1->type == E_SYMBOL))
			वापस expr_alloc_symbol(&symbol_yes);
	पूर्ण

	अगर (DEBUG_EXPR) अणु
		म_लिखो("optimize (");
		expr_fprपूर्णांक(e1, मानक_निकास);
		म_लिखो(") || (");
		expr_fprपूर्णांक(e2, मानक_निकास);
		म_लिखो(")?\n");
	पूर्ण
	वापस शून्य;
पूर्ण

अटल काष्ठा expr *expr_join_and(काष्ठा expr *e1, काष्ठा expr *e2)
अणु
	काष्ठा expr *पंचांगp;
	काष्ठा symbol *sym1, *sym2;

	अगर (expr_eq(e1, e2))
		वापस expr_copy(e1);
	अगर (e1->type != E_EQUAL && e1->type != E_UNEQUAL && e1->type != E_SYMBOL && e1->type != E_NOT)
		वापस शून्य;
	अगर (e2->type != E_EQUAL && e2->type != E_UNEQUAL && e2->type != E_SYMBOL && e2->type != E_NOT)
		वापस शून्य;
	अगर (e1->type == E_NOT) अणु
		पंचांगp = e1->left.expr;
		अगर (पंचांगp->type != E_EQUAL && पंचांगp->type != E_UNEQUAL && पंचांगp->type != E_SYMBOL)
			वापस शून्य;
		sym1 = पंचांगp->left.sym;
	पूर्ण अन्यथा
		sym1 = e1->left.sym;
	अगर (e2->type == E_NOT) अणु
		अगर (e2->left.expr->type != E_SYMBOL)
			वापस शून्य;
		sym2 = e2->left.expr->left.sym;
	पूर्ण अन्यथा
		sym2 = e2->left.sym;
	अगर (sym1 != sym2)
		वापस शून्य;
	अगर (sym1->type != S_BOOLEAN && sym1->type != S_TRISTATE)
		वापस शून्य;

	अगर ((e1->type == E_SYMBOL && e2->type == E_EQUAL && e2->right.sym == &symbol_yes) ||
	    (e2->type == E_SYMBOL && e1->type == E_EQUAL && e1->right.sym == &symbol_yes))
		// (a) && (a='y') -> (a='y')
		वापस expr_alloc_comp(E_EQUAL, sym1, &symbol_yes);

	अगर ((e1->type == E_SYMBOL && e2->type == E_UNEQUAL && e2->right.sym == &symbol_no) ||
	    (e2->type == E_SYMBOL && e1->type == E_UNEQUAL && e1->right.sym == &symbol_no))
		// (a) && (a!='n') -> (a)
		वापस expr_alloc_symbol(sym1);

	अगर ((e1->type == E_SYMBOL && e2->type == E_UNEQUAL && e2->right.sym == &symbol_mod) ||
	    (e2->type == E_SYMBOL && e1->type == E_UNEQUAL && e1->right.sym == &symbol_mod))
		// (a) && (a!='m') -> (a='y')
		वापस expr_alloc_comp(E_EQUAL, sym1, &symbol_yes);

	अगर (sym1->type == S_TRISTATE) अणु
		अगर (e1->type == E_EQUAL && e2->type == E_UNEQUAL) अणु
			// (a='b') && (a!='c') -> 'b'='c' ? 'n' : a='b'
			sym2 = e1->right.sym;
			अगर ((e2->right.sym->flags & SYMBOL_CONST) && (sym2->flags & SYMBOL_CONST))
				वापस sym2 != e2->right.sym ? expr_alloc_comp(E_EQUAL, sym1, sym2)
							     : expr_alloc_symbol(&symbol_no);
		पूर्ण
		अगर (e1->type == E_UNEQUAL && e2->type == E_EQUAL) अणु
			// (a='b') && (a!='c') -> 'b'='c' ? 'n' : a='b'
			sym2 = e2->right.sym;
			अगर ((e1->right.sym->flags & SYMBOL_CONST) && (sym2->flags & SYMBOL_CONST))
				वापस sym2 != e1->right.sym ? expr_alloc_comp(E_EQUAL, sym1, sym2)
							     : expr_alloc_symbol(&symbol_no);
		पूर्ण
		अगर (e1->type == E_UNEQUAL && e2->type == E_UNEQUAL &&
			   ((e1->right.sym == &symbol_yes && e2->right.sym == &symbol_no) ||
			    (e1->right.sym == &symbol_no && e2->right.sym == &symbol_yes)))
			// (a!='y') && (a!='n') -> (a='m')
			वापस expr_alloc_comp(E_EQUAL, sym1, &symbol_mod);

		अगर (e1->type == E_UNEQUAL && e2->type == E_UNEQUAL &&
			   ((e1->right.sym == &symbol_yes && e2->right.sym == &symbol_mod) ||
			    (e1->right.sym == &symbol_mod && e2->right.sym == &symbol_yes)))
			// (a!='y') && (a!='m') -> (a='n')
			वापस expr_alloc_comp(E_EQUAL, sym1, &symbol_no);

		अगर (e1->type == E_UNEQUAL && e2->type == E_UNEQUAL &&
			   ((e1->right.sym == &symbol_mod && e2->right.sym == &symbol_no) ||
			    (e1->right.sym == &symbol_no && e2->right.sym == &symbol_mod)))
			// (a!='m') && (a!='n') -> (a='m')
			वापस expr_alloc_comp(E_EQUAL, sym1, &symbol_yes);

		अगर ((e1->type == E_SYMBOL && e2->type == E_EQUAL && e2->right.sym == &symbol_mod) ||
		    (e2->type == E_SYMBOL && e1->type == E_EQUAL && e1->right.sym == &symbol_mod) ||
		    (e1->type == E_SYMBOL && e2->type == E_UNEQUAL && e2->right.sym == &symbol_yes) ||
		    (e2->type == E_SYMBOL && e1->type == E_UNEQUAL && e1->right.sym == &symbol_yes))
			वापस शून्य;
	पूर्ण

	अगर (DEBUG_EXPR) अणु
		म_लिखो("optimize (");
		expr_fprपूर्णांक(e1, मानक_निकास);
		म_लिखो(") && (");
		expr_fprपूर्णांक(e2, मानक_निकास);
		म_लिखो(")?\n");
	पूर्ण
	वापस शून्य;
पूर्ण

/*
 * expr_eliminate_dups() helper.
 *
 * Walks the two expression trees given in 'ep1' and 'ep2'. Any node that करोes
 * not have type 'type' (E_OR/E_AND) is considered a leaf, and is compared
 * against all other leaves to look क्रम simplअगरications.
 */
अटल व्योम expr_eliminate_dups1(क्रमागत expr_type type, काष्ठा expr **ep1, काष्ठा expr **ep2)
अणु
#घोषणा e1 (*ep1)
#घोषणा e2 (*ep2)
	काष्ठा expr *पंचांगp;

	/* Recurse करोwn to leaves */

	अगर (e1->type == type) अणु
		expr_eliminate_dups1(type, &e1->left.expr, &e2);
		expr_eliminate_dups1(type, &e1->right.expr, &e2);
		वापस;
	पूर्ण
	अगर (e2->type == type) अणु
		expr_eliminate_dups1(type, &e1, &e2->left.expr);
		expr_eliminate_dups1(type, &e1, &e2->right.expr);
		वापस;
	पूर्ण

	/* e1 and e2 are leaves. Compare and process them. */

	अगर (e1 == e2)
		वापस;

	चयन (e1->type) अणु
	हाल E_OR: हाल E_AND:
		expr_eliminate_dups1(e1->type, &e1, &e1);
	शेष:
		;
	पूर्ण

	चयन (type) अणु
	हाल E_OR:
		पंचांगp = expr_join_or(e1, e2);
		अगर (पंचांगp) अणु
			expr_मुक्त(e1); expr_मुक्त(e2);
			e1 = expr_alloc_symbol(&symbol_no);
			e2 = पंचांगp;
			trans_count++;
		पूर्ण
		अवरोध;
	हाल E_AND:
		पंचांगp = expr_join_and(e1, e2);
		अगर (पंचांगp) अणु
			expr_मुक्त(e1); expr_मुक्त(e2);
			e1 = expr_alloc_symbol(&symbol_yes);
			e2 = पंचांगp;
			trans_count++;
		पूर्ण
		अवरोध;
	शेष:
		;
	पूर्ण
#अघोषित e1
#अघोषित e2
पूर्ण

/*
 * Reग_लिखोs 'e' in-place to हटाओ ("join") duplicate and other redundant
 * opeअक्रमs.
 *
 * Example simplअगरications:
 *
 *	A || B || A    ->  A || B
 *	A && B && A=y  ->  A=y && B
 *
 * Returns the deduplicated expression.
 */
काष्ठा expr *expr_eliminate_dups(काष्ठा expr *e)
अणु
	पूर्णांक oldcount;
	अगर (!e)
		वापस e;

	oldcount = trans_count;
	जबतक (1) अणु
		trans_count = 0;
		चयन (e->type) अणु
		हाल E_OR: हाल E_AND:
			expr_eliminate_dups1(e->type, &e, &e);
		शेष:
			;
		पूर्ण
		अगर (!trans_count)
			/* No simplअगरications करोne in this pass. We're करोne */
			अवरोध;
		e = expr_eliminate_yn(e);
	पूर्ण
	trans_count = oldcount;
	वापस e;
पूर्ण

/*
 * Perक्रमms various simplअगरications involving logical चालकs and
 * comparisons.
 *
 * Allocates and वापसs a new expression.
 */
काष्ठा expr *expr_transक्रमm(काष्ठा expr *e)
अणु
	काष्ठा expr *पंचांगp;

	अगर (!e)
		वापस शून्य;
	चयन (e->type) अणु
	हाल E_EQUAL:
	हाल E_GEQ:
	हाल E_GTH:
	हाल E_LEQ:
	हाल E_LTH:
	हाल E_UNEQUAL:
	हाल E_SYMBOL:
	हाल E_LIST:
		अवरोध;
	शेष:
		e->left.expr = expr_transक्रमm(e->left.expr);
		e->right.expr = expr_transक्रमm(e->right.expr);
	पूर्ण

	चयन (e->type) अणु
	हाल E_EQUAL:
		अगर (e->left.sym->type != S_BOOLEAN)
			अवरोध;
		अगर (e->right.sym == &symbol_no) अणु
			e->type = E_NOT;
			e->left.expr = expr_alloc_symbol(e->left.sym);
			e->right.sym = शून्य;
			अवरोध;
		पूर्ण
		अगर (e->right.sym == &symbol_mod) अणु
			म_लिखो("boolean symbol %s tested for 'm'? test forced to 'n'\n", e->left.sym->name);
			e->type = E_SYMBOL;
			e->left.sym = &symbol_no;
			e->right.sym = शून्य;
			अवरोध;
		पूर्ण
		अगर (e->right.sym == &symbol_yes) अणु
			e->type = E_SYMBOL;
			e->right.sym = शून्य;
			अवरोध;
		पूर्ण
		अवरोध;
	हाल E_UNEQUAL:
		अगर (e->left.sym->type != S_BOOLEAN)
			अवरोध;
		अगर (e->right.sym == &symbol_no) अणु
			e->type = E_SYMBOL;
			e->right.sym = शून्य;
			अवरोध;
		पूर्ण
		अगर (e->right.sym == &symbol_mod) अणु
			म_लिखो("boolean symbol %s tested for 'm'? test forced to 'y'\n", e->left.sym->name);
			e->type = E_SYMBOL;
			e->left.sym = &symbol_yes;
			e->right.sym = शून्य;
			अवरोध;
		पूर्ण
		अगर (e->right.sym == &symbol_yes) अणु
			e->type = E_NOT;
			e->left.expr = expr_alloc_symbol(e->left.sym);
			e->right.sym = शून्य;
			अवरोध;
		पूर्ण
		अवरोध;
	हाल E_NOT:
		चयन (e->left.expr->type) अणु
		हाल E_NOT:
			// !!a -> a
			पंचांगp = e->left.expr->left.expr;
			मुक्त(e->left.expr);
			मुक्त(e);
			e = पंचांगp;
			e = expr_transक्रमm(e);
			अवरोध;
		हाल E_EQUAL:
		हाल E_UNEQUAL:
			// !a='x' -> a!='x'
			पंचांगp = e->left.expr;
			मुक्त(e);
			e = पंचांगp;
			e->type = e->type == E_EQUAL ? E_UNEQUAL : E_EQUAL;
			अवरोध;
		हाल E_LEQ:
		हाल E_GEQ:
			// !a<='x' -> a>'x'
			पंचांगp = e->left.expr;
			मुक्त(e);
			e = पंचांगp;
			e->type = e->type == E_LEQ ? E_GTH : E_LTH;
			अवरोध;
		हाल E_LTH:
		हाल E_GTH:
			// !a<'x' -> a>='x'
			पंचांगp = e->left.expr;
			मुक्त(e);
			e = पंचांगp;
			e->type = e->type == E_LTH ? E_GEQ : E_LEQ;
			अवरोध;
		हाल E_OR:
			// !(a || b) -> !a && !b
			पंचांगp = e->left.expr;
			e->type = E_AND;
			e->right.expr = expr_alloc_one(E_NOT, पंचांगp->right.expr);
			पंचांगp->type = E_NOT;
			पंचांगp->right.expr = शून्य;
			e = expr_transक्रमm(e);
			अवरोध;
		हाल E_AND:
			// !(a && b) -> !a || !b
			पंचांगp = e->left.expr;
			e->type = E_OR;
			e->right.expr = expr_alloc_one(E_NOT, पंचांगp->right.expr);
			पंचांगp->type = E_NOT;
			पंचांगp->right.expr = शून्य;
			e = expr_transक्रमm(e);
			अवरोध;
		हाल E_SYMBOL:
			अगर (e->left.expr->left.sym == &symbol_yes) अणु
				// !'y' -> 'n'
				पंचांगp = e->left.expr;
				मुक्त(e);
				e = पंचांगp;
				e->type = E_SYMBOL;
				e->left.sym = &symbol_no;
				अवरोध;
			पूर्ण
			अगर (e->left.expr->left.sym == &symbol_mod) अणु
				// !'m' -> 'm'
				पंचांगp = e->left.expr;
				मुक्त(e);
				e = पंचांगp;
				e->type = E_SYMBOL;
				e->left.sym = &symbol_mod;
				अवरोध;
			पूर्ण
			अगर (e->left.expr->left.sym == &symbol_no) अणु
				// !'n' -> 'y'
				पंचांगp = e->left.expr;
				मुक्त(e);
				e = पंचांगp;
				e->type = E_SYMBOL;
				e->left.sym = &symbol_yes;
				अवरोध;
			पूर्ण
			अवरोध;
		शेष:
			;
		पूर्ण
		अवरोध;
	शेष:
		;
	पूर्ण
	वापस e;
पूर्ण

पूर्णांक expr_contains_symbol(काष्ठा expr *dep, काष्ठा symbol *sym)
अणु
	अगर (!dep)
		वापस 0;

	चयन (dep->type) अणु
	हाल E_AND:
	हाल E_OR:
		वापस expr_contains_symbol(dep->left.expr, sym) ||
		       expr_contains_symbol(dep->right.expr, sym);
	हाल E_SYMBOL:
		वापस dep->left.sym == sym;
	हाल E_EQUAL:
	हाल E_GEQ:
	हाल E_GTH:
	हाल E_LEQ:
	हाल E_LTH:
	हाल E_UNEQUAL:
		वापस dep->left.sym == sym ||
		       dep->right.sym == sym;
	हाल E_NOT:
		वापस expr_contains_symbol(dep->left.expr, sym);
	शेष:
		;
	पूर्ण
	वापस 0;
पूर्ण

bool expr_depends_symbol(काष्ठा expr *dep, काष्ठा symbol *sym)
अणु
	अगर (!dep)
		वापस false;

	चयन (dep->type) अणु
	हाल E_AND:
		वापस expr_depends_symbol(dep->left.expr, sym) ||
		       expr_depends_symbol(dep->right.expr, sym);
	हाल E_SYMBOL:
		वापस dep->left.sym == sym;
	हाल E_EQUAL:
		अगर (dep->left.sym == sym) अणु
			अगर (dep->right.sym == &symbol_yes || dep->right.sym == &symbol_mod)
				वापस true;
		पूर्ण
		अवरोध;
	हाल E_UNEQUAL:
		अगर (dep->left.sym == sym) अणु
			अगर (dep->right.sym == &symbol_no)
				वापस true;
		पूर्ण
		अवरोध;
	शेष:
		;
	पूर्ण
 	वापस false;
पूर्ण

/*
 * Inserts explicit comparisons of type 'type' to symbol 'sym' पूर्णांकo the
 * expression 'e'.
 *
 * Examples transक्रमmations क्रम type == E_UNEQUAL, sym == &symbol_no:
 *
 *	A              ->  A!=n
 *	!A             ->  A=n
 *	A && B         ->  !(A=n || B=n)
 *	A || B         ->  !(A=n && B=n)
 *	A && (B || C)  ->  !(A=n || (B=n && C=n))
 *
 * Allocates and वापसs a new expression.
 */
काष्ठा expr *expr_trans_compare(काष्ठा expr *e, क्रमागत expr_type type, काष्ठा symbol *sym)
अणु
	काष्ठा expr *e1, *e2;

	अगर (!e) अणु
		e = expr_alloc_symbol(sym);
		अगर (type == E_UNEQUAL)
			e = expr_alloc_one(E_NOT, e);
		वापस e;
	पूर्ण
	चयन (e->type) अणु
	हाल E_AND:
		e1 = expr_trans_compare(e->left.expr, E_EQUAL, sym);
		e2 = expr_trans_compare(e->right.expr, E_EQUAL, sym);
		अगर (sym == &symbol_yes)
			e = expr_alloc_two(E_AND, e1, e2);
		अगर (sym == &symbol_no)
			e = expr_alloc_two(E_OR, e1, e2);
		अगर (type == E_UNEQUAL)
			e = expr_alloc_one(E_NOT, e);
		वापस e;
	हाल E_OR:
		e1 = expr_trans_compare(e->left.expr, E_EQUAL, sym);
		e2 = expr_trans_compare(e->right.expr, E_EQUAL, sym);
		अगर (sym == &symbol_yes)
			e = expr_alloc_two(E_OR, e1, e2);
		अगर (sym == &symbol_no)
			e = expr_alloc_two(E_AND, e1, e2);
		अगर (type == E_UNEQUAL)
			e = expr_alloc_one(E_NOT, e);
		वापस e;
	हाल E_NOT:
		वापस expr_trans_compare(e->left.expr, type == E_EQUAL ? E_UNEQUAL : E_EQUAL, sym);
	हाल E_UNEQUAL:
	हाल E_LTH:
	हाल E_LEQ:
	हाल E_GTH:
	हाल E_GEQ:
	हाल E_EQUAL:
		अगर (type == E_EQUAL) अणु
			अगर (sym == &symbol_yes)
				वापस expr_copy(e);
			अगर (sym == &symbol_mod)
				वापस expr_alloc_symbol(&symbol_no);
			अगर (sym == &symbol_no)
				वापस expr_alloc_one(E_NOT, expr_copy(e));
		पूर्ण अन्यथा अणु
			अगर (sym == &symbol_yes)
				वापस expr_alloc_one(E_NOT, expr_copy(e));
			अगर (sym == &symbol_mod)
				वापस expr_alloc_symbol(&symbol_yes);
			अगर (sym == &symbol_no)
				वापस expr_copy(e);
		पूर्ण
		अवरोध;
	हाल E_SYMBOL:
		वापस expr_alloc_comp(type, e->left.sym, sym);
	हाल E_LIST:
	हाल E_RANGE:
	हाल E_NONE:
		/* panic */;
	पूर्ण
	वापस शून्य;
पूर्ण

क्रमागत string_value_kind अणु
	k_string,
	k_चिन्हित,
	k_अचिन्हित,
पूर्ण;

जोड़ string_value अणु
	अचिन्हित दीर्घ दीर्घ u;
	चिन्हित दीर्घ दीर्घ s;
पूर्ण;

अटल क्रमागत string_value_kind expr_parse_string(स्थिर अक्षर *str,
						क्रमागत symbol_type type,
						जोड़ string_value *val)
अणु
	अक्षर *tail;
	क्रमागत string_value_kind kind;

	त्रुटि_सं = 0;
	चयन (type) अणु
	हाल S_BOOLEAN:
	हाल S_TRISTATE:
		val->s = !म_भेद(str, "n") ? 0 :
			 !म_भेद(str, "m") ? 1 :
			 !म_भेद(str, "y") ? 2 : -1;
		वापस k_चिन्हित;
	हाल S_INT:
		val->s = म_से_दीर्घl(str, &tail, 10);
		kind = k_चिन्हित;
		अवरोध;
	हाल S_HEX:
		val->u = म_से_अदीर्घl(str, &tail, 16);
		kind = k_अचिन्हित;
		अवरोध;
	शेष:
		val->s = म_से_दीर्घl(str, &tail, 0);
		kind = k_चिन्हित;
		अवरोध;
	पूर्ण
	वापस !त्रुटि_सं && !*tail && tail > str && है_षष्ठादशक(tail[-1])
	       ? kind : k_string;
पूर्ण

tristate expr_calc_value(काष्ठा expr *e)
अणु
	tristate val1, val2;
	स्थिर अक्षर *str1, *str2;
	क्रमागत string_value_kind k1 = k_string, k2 = k_string;
	जोड़ string_value lval = अणुपूर्ण, rval = अणुपूर्ण;
	पूर्णांक res;

	अगर (!e)
		वापस yes;

	चयन (e->type) अणु
	हाल E_SYMBOL:
		sym_calc_value(e->left.sym);
		वापस e->left.sym->curr.tri;
	हाल E_AND:
		val1 = expr_calc_value(e->left.expr);
		val2 = expr_calc_value(e->right.expr);
		वापस EXPR_AND(val1, val2);
	हाल E_OR:
		val1 = expr_calc_value(e->left.expr);
		val2 = expr_calc_value(e->right.expr);
		वापस EXPR_OR(val1, val2);
	हाल E_NOT:
		val1 = expr_calc_value(e->left.expr);
		वापस EXPR_NOT(val1);
	हाल E_EQUAL:
	हाल E_GEQ:
	हाल E_GTH:
	हाल E_LEQ:
	हाल E_LTH:
	हाल E_UNEQUAL:
		अवरोध;
	शेष:
		म_लिखो("expr_calc_value: %d?\n", e->type);
		वापस no;
	पूर्ण

	sym_calc_value(e->left.sym);
	sym_calc_value(e->right.sym);
	str1 = sym_get_string_value(e->left.sym);
	str2 = sym_get_string_value(e->right.sym);

	अगर (e->left.sym->type != S_STRING || e->right.sym->type != S_STRING) अणु
		k1 = expr_parse_string(str1, e->left.sym->type, &lval);
		k2 = expr_parse_string(str2, e->right.sym->type, &rval);
	पूर्ण

	अगर (k1 == k_string || k2 == k_string)
		res = म_भेद(str1, str2);
	अन्यथा अगर (k1 == k_अचिन्हित || k2 == k_अचिन्हित)
		res = (lval.u > rval.u) - (lval.u < rval.u);
	अन्यथा /* अगर (k1 == k_चिन्हित && k2 == k_चिन्हित) */
		res = (lval.s > rval.s) - (lval.s < rval.s);

	चयन(e->type) अणु
	हाल E_EQUAL:
		वापस res ? no : yes;
	हाल E_GEQ:
		वापस res >= 0 ? yes : no;
	हाल E_GTH:
		वापस res > 0 ? yes : no;
	हाल E_LEQ:
		वापस res <= 0 ? yes : no;
	हाल E_LTH:
		वापस res < 0 ? yes : no;
	हाल E_UNEQUAL:
		वापस res ? yes : no;
	शेष:
		म_लिखो("expr_calc_value: relation %d?\n", e->type);
		वापस no;
	पूर्ण
पूर्ण

अटल पूर्णांक expr_compare_type(क्रमागत expr_type t1, क्रमागत expr_type t2)
अणु
	अगर (t1 == t2)
		वापस 0;
	चयन (t1) अणु
	हाल E_LEQ:
	हाल E_LTH:
	हाल E_GEQ:
	हाल E_GTH:
		अगर (t2 == E_EQUAL || t2 == E_UNEQUAL)
			वापस 1;
	हाल E_EQUAL:
	हाल E_UNEQUAL:
		अगर (t2 == E_NOT)
			वापस 1;
	हाल E_NOT:
		अगर (t2 == E_AND)
			वापस 1;
	हाल E_AND:
		अगर (t2 == E_OR)
			वापस 1;
	हाल E_OR:
		अगर (t2 == E_LIST)
			वापस 1;
	हाल E_LIST:
		अगर (t2 == 0)
			वापस 1;
	शेष:
		वापस -1;
	पूर्ण
	म_लिखो("[%dgt%d?]", t1, t2);
	वापस 0;
पूर्ण

व्योम expr_prपूर्णांक(काष्ठा expr *e,
		व्योम (*fn)(व्योम *, काष्ठा symbol *, स्थिर अक्षर *),
		व्योम *data, पूर्णांक prevtoken)
अणु
	अगर (!e) अणु
		fn(data, शून्य, "y");
		वापस;
	पूर्ण

	अगर (expr_compare_type(prevtoken, e->type) > 0)
		fn(data, शून्य, "(");
	चयन (e->type) अणु
	हाल E_SYMBOL:
		अगर (e->left.sym->name)
			fn(data, e->left.sym, e->left.sym->name);
		अन्यथा
			fn(data, शून्य, "<choice>");
		अवरोध;
	हाल E_NOT:
		fn(data, शून्य, "!");
		expr_prपूर्णांक(e->left.expr, fn, data, E_NOT);
		अवरोध;
	हाल E_EQUAL:
		अगर (e->left.sym->name)
			fn(data, e->left.sym, e->left.sym->name);
		अन्यथा
			fn(data, शून्य, "<choice>");
		fn(data, शून्य, "=");
		fn(data, e->right.sym, e->right.sym->name);
		अवरोध;
	हाल E_LEQ:
	हाल E_LTH:
		अगर (e->left.sym->name)
			fn(data, e->left.sym, e->left.sym->name);
		अन्यथा
			fn(data, शून्य, "<choice>");
		fn(data, शून्य, e->type == E_LEQ ? "<=" : "<");
		fn(data, e->right.sym, e->right.sym->name);
		अवरोध;
	हाल E_GEQ:
	हाल E_GTH:
		अगर (e->left.sym->name)
			fn(data, e->left.sym, e->left.sym->name);
		अन्यथा
			fn(data, शून्य, "<choice>");
		fn(data, शून्य, e->type == E_GEQ ? ">=" : ">");
		fn(data, e->right.sym, e->right.sym->name);
		अवरोध;
	हाल E_UNEQUAL:
		अगर (e->left.sym->name)
			fn(data, e->left.sym, e->left.sym->name);
		अन्यथा
			fn(data, शून्य, "<choice>");
		fn(data, शून्य, "!=");
		fn(data, e->right.sym, e->right.sym->name);
		अवरोध;
	हाल E_OR:
		expr_prपूर्णांक(e->left.expr, fn, data, E_OR);
		fn(data, शून्य, " || ");
		expr_prपूर्णांक(e->right.expr, fn, data, E_OR);
		अवरोध;
	हाल E_AND:
		expr_prपूर्णांक(e->left.expr, fn, data, E_AND);
		fn(data, शून्य, " && ");
		expr_prपूर्णांक(e->right.expr, fn, data, E_AND);
		अवरोध;
	हाल E_LIST:
		fn(data, e->right.sym, e->right.sym->name);
		अगर (e->left.expr) अणु
			fn(data, शून्य, " ^ ");
			expr_prपूर्णांक(e->left.expr, fn, data, E_LIST);
		पूर्ण
		अवरोध;
	हाल E_RANGE:
		fn(data, शून्य, "[");
		fn(data, e->left.sym, e->left.sym->name);
		fn(data, शून्य, " ");
		fn(data, e->right.sym, e->right.sym->name);
		fn(data, शून्य, "]");
		अवरोध;
	शेष:
	  अणु
		अक्षर buf[32];
		प्र_लिखो(buf, "<unknown type %d>", e->type);
		fn(data, शून्य, buf);
		अवरोध;
	  पूर्ण
	पूर्ण
	अगर (expr_compare_type(prevtoken, e->type) > 0)
		fn(data, शून्य, ")");
पूर्ण

अटल व्योम expr_prपूर्णांक_file_helper(व्योम *data, काष्ठा symbol *sym, स्थिर अक्षर *str)
अणु
	xख_डालो(str, म_माप(str), 1, data);
पूर्ण

व्योम expr_fprपूर्णांक(काष्ठा expr *e, खाता *out)
अणु
	expr_prपूर्णांक(e, expr_prपूर्णांक_file_helper, out, E_NONE);
पूर्ण

अटल व्योम expr_prपूर्णांक_gstr_helper(व्योम *data, काष्ठा symbol *sym, स्थिर अक्षर *str)
अणु
	काष्ठा gstr *gs = (काष्ठा gstr*)data;
	स्थिर अक्षर *sym_str = शून्य;

	अगर (sym)
		sym_str = sym_get_string_value(sym);

	अगर (gs->max_width) अणु
		अचिन्हित extra_length = म_माप(str);
		स्थिर अक्षर *last_cr = म_खोजप(gs->s, '\n');
		अचिन्हित last_line_length;

		अगर (sym_str)
			extra_length += 4 + म_माप(sym_str);

		अगर (!last_cr)
			last_cr = gs->s;

		last_line_length = म_माप(gs->s) - (last_cr - gs->s);

		अगर ((last_line_length + extra_length) > gs->max_width)
			str_append(gs, "\\\n");
	पूर्ण

	str_append(gs, str);
	अगर (sym && sym->type != S_UNKNOWN)
		str_म_लिखो(gs, " [=%s]", sym_str);
पूर्ण

व्योम expr_gstr_prपूर्णांक(काष्ठा expr *e, काष्ठा gstr *gs)
अणु
	expr_prपूर्णांक(e, expr_prपूर्णांक_gstr_helper, gs, E_NONE);
पूर्ण

/*
 * Transक्रमm the top level "||" tokens पूर्णांकo newlines and prepend each
 * line with a minus. This makes expressions much easier to पढ़ो.
 * Suitable क्रम reverse dependency expressions.
 */
अटल व्योम expr_prपूर्णांक_revdep(काष्ठा expr *e,
			      व्योम (*fn)(व्योम *, काष्ठा symbol *, स्थिर अक्षर *),
			      व्योम *data, tristate pr_type, स्थिर अक्षर **title)
अणु
	अगर (e->type == E_OR) अणु
		expr_prपूर्णांक_revdep(e->left.expr, fn, data, pr_type, title);
		expr_prपूर्णांक_revdep(e->right.expr, fn, data, pr_type, title);
	पूर्ण अन्यथा अगर (expr_calc_value(e) == pr_type) अणु
		अगर (*title) अणु
			fn(data, शून्य, *title);
			*title = शून्य;
		पूर्ण

		fn(data, शून्य, "  - ");
		expr_prपूर्णांक(e, fn, data, E_NONE);
		fn(data, शून्य, "\n");
	पूर्ण
पूर्ण

व्योम expr_gstr_prपूर्णांक_revdep(काष्ठा expr *e, काष्ठा gstr *gs,
			    tristate pr_type, स्थिर अक्षर *title)
अणु
	expr_prपूर्णांक_revdep(e, expr_prपूर्णांक_gstr_helper, gs, pr_type, &title);
पूर्ण
