<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * trace_events_filter - generic event filtering
 *
 * Copyright (C) 2009 Tom Zanussi <tzanussi@gmail.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/mutex.h>
#समावेश <linux/perf_event.h>
#समावेश <linux/slab.h>

#समावेश "trace.h"
#समावेश "trace_output.h"

#घोषणा DEFAULT_SYS_FILTER_MESSAGE					\
	"### global filter ###\n"					\
	"# Use this to set filters for multiple events.\n"		\
	"# Only events with the given fields will be affected.\n"	\
	"# If no events are modified, an error message will be displayed here"

/* Due to token parsing '<=' must be before '<' and '>=' must be before '>' */
#घोषणा OPS					\
	C( OP_GLOB,	"~"  ),			\
	C( OP_NE,	"!=" ),			\
	C( OP_EQ,	"==" ),			\
	C( OP_LE,	"<=" ),			\
	C( OP_LT,	"<"  ),			\
	C( OP_GE,	">=" ),			\
	C( OP_GT,	">"  ),			\
	C( OP_BAND,	"&"  ),			\
	C( OP_MAX,	शून्य )

#अघोषित C
#घोषणा C(a, b)	a

क्रमागत filter_op_ids अणु OPS पूर्ण;

#अघोषित C
#घोषणा C(a, b)	b

अटल स्थिर अक्षर * ops[] = अणु OPS पूर्ण;

/*
 * pred functions are OP_LE, OP_LT, OP_GE, OP_GT, and OP_BAND
 * pred_funcs_##type below must match the order of them above.
 */
#घोषणा PRED_FUNC_START			OP_LE
#घोषणा PRED_FUNC_MAX			(OP_BAND - PRED_FUNC_START)

#घोषणा ERRORS								\
	C(NONE,			"No error"),				\
	C(INVALID_OP,		"Invalid operator"),			\
	C(TOO_MANY_OPEN,	"Too many '('"),			\
	C(TOO_MANY_CLOSE,	"Too few '('"),				\
	C(MISSING_QUOTE,	"Missing matching quote"),		\
	C(OPERAND_TOO_LONG,	"Operand too long"),			\
	C(EXPECT_STRING,	"Expecting string field"),		\
	C(EXPECT_DIGIT,		"Expecting numeric field"),		\
	C(ILLEGAL_FIELD_OP,	"Illegal operation for field type"),	\
	C(FIELD_NOT_FOUND,	"Field not found"),			\
	C(ILLEGAL_INTVAL,	"Illegal integer value"),		\
	C(BAD_SUBSYS_FILTER,	"Couldn't find or set field in one of a subsystem's events"), \
	C(TOO_MANY_PREDS,	"Too many terms in predicate expression"), \
	C(INVALID_FILTER,	"Meaningless filter expression"),	\
	C(IP_FIELD_ONLY,	"Only 'ip' field is supported for function trace"), \
	C(INVALID_VALUE,	"Invalid value (did you forget quotes)?"), \
	C(ERRNO,		"Error"),				\
	C(NO_FILTER,		"No filter found")

#अघोषित C
#घोषणा C(a, b)		FILT_ERR_##a

क्रमागत अणु ERRORS पूर्ण;

#अघोषित C
#घोषणा C(a, b)		b

अटल स्थिर अक्षर *err_text[] = अणु ERRORS पूर्ण;

/* Called after a '!' अक्षरacter but "!=" and "!~" are not "not"s */
अटल bool is_not(स्थिर अक्षर *str)
अणु
	चयन (str[1]) अणु
	हाल '=':
	हाल '~':
		वापस false;
	पूर्ण
	वापस true;
पूर्ण

/**
 * prog_entry - a singe entry in the filter program
 * @target:	     Index to jump to on a branch (actually one minus the index)
 * @when_to_branch:  The value of the result of the predicate to करो a branch
 * @pred:	     The predicate to execute.
 */
काष्ठा prog_entry अणु
	पूर्णांक			target;
	पूर्णांक			when_to_branch;
	काष्ठा filter_pred	*pred;
पूर्ण;

/**
 * update_preds- assign a program entry a label target
 * @prog: The program array
 * @N: The index of the current entry in @prog
 * @when_to_branch: What to assign a program entry क्रम its branch condition
 *
 * The program entry at @N has a target that poपूर्णांकs to the index of a program
 * entry that can have its target and when_to_branch fields updated.
 * Update the current program entry denoted by index @N target field to be
 * that of the updated entry. This will denote the entry to update अगर
 * we are processing an "||" after an "&&"
 */
अटल व्योम update_preds(काष्ठा prog_entry *prog, पूर्णांक N, पूर्णांक invert)
अणु
	पूर्णांक t, s;

	t = prog[N].target;
	s = prog[t].target;
	prog[t].when_to_branch = invert;
	prog[t].target = N;
	prog[N].target = s;
पूर्ण

काष्ठा filter_parse_error अणु
	पूर्णांक lasterr;
	पूर्णांक lasterr_pos;
पूर्ण;

अटल व्योम parse_error(काष्ठा filter_parse_error *pe, पूर्णांक err, पूर्णांक pos)
अणु
	pe->lasterr = err;
	pe->lasterr_pos = pos;
पूर्ण

प्रकार पूर्णांक (*parse_pred_fn)(स्थिर अक्षर *str, व्योम *data, पूर्णांक pos,
			     काष्ठा filter_parse_error *pe,
			     काष्ठा filter_pred **pred);

क्रमागत अणु
	INVERT		= 1,
	PROCESS_AND	= 2,
	PROCESS_OR	= 4,
पूर्ण;

/*
 * Without going पूर्णांकo a क्रमmal proof, this explains the method that is used in
 * parsing the logical expressions.
 *
 * For example, अगर we have: "a && !(!b || (c && g)) || d || e && !f"
 * The first pass will convert it पूर्णांकo the following program:
 *
 * n1: r=a;       l1: अगर (!r) जाओ l4;
 * n2: r=b;       l2: अगर (!r) जाओ l4;
 * n3: r=c; r=!r; l3: अगर (r) जाओ l4;
 * n4: r=g; r=!r; l4: अगर (r) जाओ l5;
 * n5: r=d;       l5: अगर (r) जाओ T
 * n6: r=e;       l6: अगर (!r) जाओ l7;
 * n7: r=f; r=!r; l7: अगर (!r) जाओ F
 * T: वापस TRUE
 * F: वापस FALSE
 *
 * To करो this, we use a data काष्ठाure to represent each of the above
 * predicate and conditions that has:
 *
 *  predicate, when_to_branch, invert, target
 *
 * The "predicate" will hold the function to determine the result "r".
 * The "when_to_branch" denotes what "r" should be अगर a branch is to be taken
 * "&&" would contain "!r" or (0) and "||" would contain "r" or (1).
 * The "invert" holds whether the value should be reversed beक्रमe testing.
 * The "target" contains the label "l#" to jump to.
 *
 * A stack is created to hold values when parentheses are used.
 *
 * To simplअगरy the logic, the labels will start at 0 and not 1.
 *
 * The possible invert values are 1 and 0. The number of "!"s that are in scope
 * beक्रमe the predicate determines the invert value, अगर the number is odd then
 * the invert value is 1 and 0 otherwise. This means the invert value only
 * needs to be toggled when a new "!" is पूर्णांकroduced compared to what is stored
 * on the stack, where parentheses were used.
 *
 * The top of the stack and "invert" are initialized to zero.
 *
 * ** FIRST PASS **
 *
 * #1 A loop through all the tokens is करोne:
 *
 * #2 If the token is an "(", the stack is push, and the current stack value
 *    माला_लो the current invert value, and the loop जारीs to the next token.
 *    The top of the stack saves the "invert" value to keep track of what
 *    the current inversion is. As "!(a && !b || c)" would require all
 *    predicates being affected separately by the "!" beक्रमe the parentheses.
 *    And that would end up being equivalent to "(!a || b) && !c"
 *
 * #3 If the token is an "!", the current "invert" value माला_लो inverted, and
 *    the loop जारीs. Note, अगर the next token is a predicate, then
 *    this "invert" value is only valid क्रम the current program entry,
 *    and करोes not affect other predicates later on.
 *
 * The only other acceptable token is the predicate string.
 *
 * #4 A new entry पूर्णांकo the program is added saving: the predicate and the
 *    current value of "invert". The target is currently asचिन्हित to the
 *    previous program index (this will not be its final value).
 *
 * #5 We now enter another loop and look at the next token. The only valid
 *    tokens are ")", "&&", "||" or end of the input string "\0".
 *
 * #6 The invert variable is reset to the current value saved on the top of
 *    the stack.
 *
 * #7 The top of the stack holds not only the current invert value, but also
 *    अगर a "&&" or "||" needs to be processed. Note, the "&&" takes higher
 *    precedence than "||". That is "a && b || c && d" is equivalent to
 *    "(a && b) || (c && d)". Thus the first thing to करो is to see अगर "&&" needs
 *    to be processed. This is the हाल अगर an "&&" was the last token. If it was
 *    then we call update_preds(). This takes the program, the current index in
 *    the program, and the current value of "invert".  More will be described
 *    below about this function.
 *
 * #8 If the next token is "&&" then we set a flag in the top of the stack
 *    that denotes that "&&" needs to be processed, अवरोध out of this loop
 *    and जारी with the outer loop.
 *
 * #9 Otherwise, अगर a "||" needs to be processed then update_preds() is called.
 *    This is called with the program, the current index in the program, but
 *    this समय with an inverted value of "invert" (that is !invert). This is
 *    because the value taken will become the "when_to_branch" value of the
 *    program.
 *    Note, this is called when the next token is not an "&&". As stated beक्रमe,
 *    "&&" takes higher precedence, and "||" should not be processed yet अगर the
 *    next logical operation is "&&".
 *
 * #10 If the next token is "||" then we set a flag in the top of the stack
 *     that denotes that "||" needs to be processed, अवरोध out of this loop
 *     and जारी with the outer loop.
 *
 * #11 If this is the end of the input string "\0" then we अवरोध out of both
 *     loops.
 *
 * #12 Otherwise, the next token is ")", where we pop the stack and जारी
 *     this inner loop.
 *
 * Now to discuss the update_pred() function, as that is key to the setting up
 * of the program. Remember the "target" of the program is initialized to the
 * previous index and not the "l" label. The target holds the index पूर्णांकo the
 * program that माला_लो affected by the opeअक्रम. Thus अगर we have something like
 *  "a || b && c", when we process "a" the target will be "-1" (undefined).
 * When we process "b", its target is "0", which is the index of "a", as that's
 * the predicate that is affected by "||". But because the next token after "b"
 * is "&&" we करोn't call update_preds(). Instead जारी to "c". As the
 * next token after "c" is not "&&" but the end of input, we first process the
 * "&&" by calling update_preds() क्रम the "&&" then we process the "||" by
 * calling updates_preds() with the values क्रम processing "||".
 *
 * What करोes that mean? What update_preds() करोes is to first save the "target"
 * of the program entry indexed by the current program entry's "target"
 * (remember the "target" is initialized to previous program entry), and then
 * sets that "target" to the current index which represents the label "l#".
 * That entry's "when_to_branch" is set to the value passed in (the "invert"
 * or "!invert"). Then it sets the current program entry's target to the saved
 * "target" value (the old value of the program that had its "target" updated
 * to the label).
 *
 * Looking back at "a || b && c", we have the following steps:
 *  "a"  - prog[0] = अणु "a", X, -1 पूर्ण // pred, when_to_branch, target
 *  "||" - flag that we need to process "||"; जारी outer loop
 *  "b"  - prog[1] = अणु "b", X, 0 पूर्ण
 *  "&&" - flag that we need to process "&&"; जारी outer loop
 * (Notice we did not process "||")
 *  "c"  - prog[2] = अणु "c", X, 1 पूर्ण
 *  update_preds(prog, 2, 0); // invert = 0 as we are processing "&&"
 *    t = prog[2].target; // t = 1
 *    s = prog[t].target; // s = 0
 *    prog[t].target = 2; // Set target to "l2"
 *    prog[t].when_to_branch = 0;
 *    prog[2].target = s;
 * update_preds(prog, 2, 1); // invert = 1 as we are now processing "||"
 *    t = prog[2].target; // t = 0
 *    s = prog[t].target; // s = -1
 *    prog[t].target = 2; // Set target to "l2"
 *    prog[t].when_to_branch = 1;
 *    prog[2].target = s;
 *
 * #13 Which brings us to the final step of the first pass, which is to set
 *     the last program entry's when_to_branch and target, which will be
 *     when_to_branch = 0; target = N; ( the label after the program entry after
 *     the last program entry processed above).
 *
 * If we denote "TRUE" to be the entry after the last program entry processed,
 * and "FALSE" the program entry after that, we are now करोne with the first
 * pass.
 *
 * Making the above "a || b && c" have a program of:
 *  prog[0] = अणु "a", 1, 2 पूर्ण
 *  prog[1] = अणु "b", 0, 2 पूर्ण
 *  prog[2] = अणु "c", 0, 3 पूर्ण
 *
 * Which translates पूर्णांकo:
 * n0: r = a; l0: अगर (r) जाओ l2;
 * n1: r = b; l1: अगर (!r) जाओ l2;
 * n2: r = c; l2: अगर (!r) जाओ l3;  // Which is the same as "goto F;"
 * T: वापस TRUE; l3:
 * F: वापस FALSE
 *
 * Although, after the first pass, the program is correct, it is
 * inefficient. The simple sample of "a || b && c" could be easily been
 * converted पूर्णांकo:
 * n0: r = a; अगर (r) जाओ T
 * n1: r = b; अगर (!r) जाओ F
 * n2: r = c; अगर (!r) जाओ F
 * T: वापस TRUE;
 * F: वापस FALSE;
 *
 * The First Pass is over the input string. The next too passes are over
 * the program itself.
 *
 * ** SECOND PASS **
 *
 * Which brings us to the second pass. If a jump to a label has the
 * same condition as that label, it can instead jump to its target.
 * The original example of "a && !(!b || (c && g)) || d || e && !f"
 * where the first pass gives us:
 *
 * n1: r=a;       l1: अगर (!r) जाओ l4;
 * n2: r=b;       l2: अगर (!r) जाओ l4;
 * n3: r=c; r=!r; l3: अगर (r) जाओ l4;
 * n4: r=g; r=!r; l4: अगर (r) जाओ l5;
 * n5: r=d;       l5: अगर (r) जाओ T
 * n6: r=e;       l6: अगर (!r) जाओ l7;
 * n7: r=f; r=!r; l7: अगर (!r) जाओ F:
 * T: वापस TRUE;
 * F: वापस FALSE
 *
 * We can see that "l3: if (r) goto l4;" and at l4, we have "if (r) goto l5;".
 * And "l5: if (r) goto T", we could optimize this by converting l3 and l4
 * to go directly to T. To accomplish this, we start from the last
 * entry in the program and work our way back. If the target of the entry
 * has the same "when_to_branch" then we could use that entry's target.
 * Doing this, the above would end up as:
 *
 * n1: r=a;       l1: अगर (!r) जाओ l4;
 * n2: r=b;       l2: अगर (!r) जाओ l4;
 * n3: r=c; r=!r; l3: अगर (r) जाओ T;
 * n4: r=g; r=!r; l4: अगर (r) जाओ T;
 * n5: r=d;       l5: अगर (r) जाओ T;
 * n6: r=e;       l6: अगर (!r) जाओ F;
 * n7: r=f; r=!r; l7: अगर (!r) जाओ F;
 * T: वापस TRUE
 * F: वापस FALSE
 *
 * In that same pass, अगर the "when_to_branch" करोesn't match, we can simply
 * go to the program entry after the label. That is, "l2: if (!r) goto l4;"
 * where "l4: if (r) goto T;", then we can convert l2 to be:
 * "l2: if (!r) goto n5;".
 *
 * This will have the second pass give us:
 * n1: r=a;       l1: अगर (!r) जाओ n5;
 * n2: r=b;       l2: अगर (!r) जाओ n5;
 * n3: r=c; r=!r; l3: अगर (r) जाओ T;
 * n4: r=g; r=!r; l4: अगर (r) जाओ T;
 * n5: r=d;       l5: अगर (r) जाओ T
 * n6: r=e;       l6: अगर (!r) जाओ F;
 * n7: r=f; r=!r; l7: अगर (!r) जाओ F
 * T: वापस TRUE
 * F: वापस FALSE
 *
 * Notice, all the "l#" labels are no दीर्घer used, and they can now
 * be discarded.
 *
 * ** THIRD PASS **
 *
 * For the third pass we deal with the inverts. As they simply just
 * make the "when_to_branch" get inverted, a simple loop over the
 * program to that करोes: "when_to_branch ^= invert;" will करो the
 * job, leaving us with:
 * n1: r=a; अगर (!r) जाओ n5;
 * n2: r=b; अगर (!r) जाओ n5;
 * n3: r=c: अगर (!r) जाओ T;
 * n4: r=g; अगर (!r) जाओ T;
 * n5: r=d; अगर (r) जाओ T
 * n6: r=e; अगर (!r) जाओ F;
 * n7: r=f; अगर (r) जाओ F
 * T: वापस TRUE
 * F: वापस FALSE
 *
 * As "r = a; if (!r) goto n5;" is obviously the same as
 * "if (!a) goto n5;" without करोing anything we can पूर्णांकerpret the
 * program as:
 * n1: अगर (!a) जाओ n5;
 * n2: अगर (!b) जाओ n5;
 * n3: अगर (!c) जाओ T;
 * n4: अगर (!g) जाओ T;
 * n5: अगर (d) जाओ T
 * n6: अगर (!e) जाओ F;
 * n7: अगर (f) जाओ F
 * T: वापस TRUE
 * F: वापस FALSE
 *
 * Since the inverts are discarded at the end, there's no reason to store
 * them in the program array (and waste memory). A separate array to hold
 * the inverts is used and मुक्तd at the end.
 */
अटल काष्ठा prog_entry *
predicate_parse(स्थिर अक्षर *str, पूर्णांक nr_parens, पूर्णांक nr_preds,
		parse_pred_fn parse_pred, व्योम *data,
		काष्ठा filter_parse_error *pe)
अणु
	काष्ठा prog_entry *prog_stack;
	काष्ठा prog_entry *prog;
	स्थिर अक्षर *ptr = str;
	अक्षर *inverts = शून्य;
	पूर्णांक *op_stack;
	पूर्णांक *top;
	पूर्णांक invert = 0;
	पूर्णांक ret = -ENOMEM;
	पूर्णांक len;
	पूर्णांक N = 0;
	पूर्णांक i;

	nr_preds += 2; /* For TRUE and FALSE */

	op_stack = kदो_स्मृति_array(nr_parens, माप(*op_stack), GFP_KERNEL);
	अगर (!op_stack)
		वापस ERR_PTR(-ENOMEM);
	prog_stack = kसुस्मृति(nr_preds, माप(*prog_stack), GFP_KERNEL);
	अगर (!prog_stack) अणु
		parse_error(pe, -ENOMEM, 0);
		जाओ out_मुक्त;
	पूर्ण
	inverts = kदो_स्मृति_array(nr_preds, माप(*inverts), GFP_KERNEL);
	अगर (!inverts) अणु
		parse_error(pe, -ENOMEM, 0);
		जाओ out_मुक्त;
	पूर्ण

	top = op_stack;
	prog = prog_stack;
	*top = 0;

	/* First pass */
	जबतक (*ptr) अणु						/* #1 */
		स्थिर अक्षर *next = ptr++;

		अगर (है_खाली(*next))
			जारी;

		चयन (*next) अणु
		हाल '(':					/* #2 */
			अगर (top - op_stack > nr_parens) अणु
				ret = -EINVAL;
				जाओ out_मुक्त;
			पूर्ण
			*(++top) = invert;
			जारी;
		हाल '!':					/* #3 */
			अगर (!is_not(next))
				अवरोध;
			invert = !invert;
			जारी;
		पूर्ण

		अगर (N >= nr_preds) अणु
			parse_error(pe, FILT_ERR_TOO_MANY_PREDS, next - str);
			जाओ out_मुक्त;
		पूर्ण

		inverts[N] = invert;				/* #4 */
		prog[N].target = N-1;

		len = parse_pred(next, data, ptr - str, pe, &prog[N].pred);
		अगर (len < 0) अणु
			ret = len;
			जाओ out_मुक्त;
		पूर्ण
		ptr = next + len;

		N++;

		ret = -1;
		जबतक (1) अणु					/* #5 */
			next = ptr++;
			अगर (है_खाली(*next))
				जारी;

			चयन (*next) अणु
			हाल ')':
			हाल '\0':
				अवरोध;
			हाल '&':
			हाल '|':
				/* accepting only "&&" or "||" */
				अगर (next[1] == next[0]) अणु
					ptr++;
					अवरोध;
				पूर्ण
				fallthrough;
			शेष:
				parse_error(pe, FILT_ERR_TOO_MANY_PREDS,
					    next - str);
				जाओ out_मुक्त;
			पूर्ण

			invert = *top & INVERT;

			अगर (*top & PROCESS_AND) अणु		/* #7 */
				update_preds(prog, N - 1, invert);
				*top &= ~PROCESS_AND;
			पूर्ण
			अगर (*next == '&') अणु			/* #8 */
				*top |= PROCESS_AND;
				अवरोध;
			पूर्ण
			अगर (*top & PROCESS_OR) अणु		/* #9 */
				update_preds(prog, N - 1, !invert);
				*top &= ~PROCESS_OR;
			पूर्ण
			अगर (*next == '|') अणु			/* #10 */
				*top |= PROCESS_OR;
				अवरोध;
			पूर्ण
			अगर (!*next)				/* #11 */
				जाओ out;

			अगर (top == op_stack) अणु
				ret = -1;
				/* Too few '(' */
				parse_error(pe, FILT_ERR_TOO_MANY_CLOSE, ptr - str);
				जाओ out_मुक्त;
			पूर्ण
			top--;					/* #12 */
		पूर्ण
	पूर्ण
 out:
	अगर (top != op_stack) अणु
		/* Too many '(' */
		parse_error(pe, FILT_ERR_TOO_MANY_OPEN, ptr - str);
		जाओ out_मुक्त;
	पूर्ण

	अगर (!N) अणु
		/* No program? */
		ret = -EINVAL;
		parse_error(pe, FILT_ERR_NO_FILTER, ptr - str);
		जाओ out_मुक्त;
	पूर्ण

	prog[N].pred = शून्य;					/* #13 */
	prog[N].target = 1;		/* TRUE */
	prog[N+1].pred = शून्य;
	prog[N+1].target = 0;		/* FALSE */
	prog[N-1].target = N;
	prog[N-1].when_to_branch = false;

	/* Second Pass */
	क्रम (i = N-1 ; i--; ) अणु
		पूर्णांक target = prog[i].target;
		अगर (prog[i].when_to_branch == prog[target].when_to_branch)
			prog[i].target = prog[target].target;
	पूर्ण

	/* Third Pass */
	क्रम (i = 0; i < N; i++) अणु
		invert = inverts[i] ^ prog[i].when_to_branch;
		prog[i].when_to_branch = invert;
		/* Make sure the program always moves क्रमward */
		अगर (WARN_ON(prog[i].target <= i)) अणु
			ret = -EINVAL;
			जाओ out_मुक्त;
		पूर्ण
	पूर्ण

	kमुक्त(op_stack);
	kमुक्त(inverts);
	वापस prog;
out_मुक्त:
	kमुक्त(op_stack);
	kमुक्त(inverts);
	अगर (prog_stack) अणु
		क्रम (i = 0; prog_stack[i].pred; i++)
			kमुक्त(prog_stack[i].pred);
		kमुक्त(prog_stack);
	पूर्ण
	वापस ERR_PTR(ret);
पूर्ण

#घोषणा DEFINE_COMPARISON_PRED(type)					\
अटल पूर्णांक filter_pred_LT_##type(काष्ठा filter_pred *pred, व्योम *event)	\
अणु									\
	type *addr = (type *)(event + pred->offset);			\
	type val = (type)pred->val;					\
	वापस *addr < val;						\
पूर्ण									\
अटल पूर्णांक filter_pred_LE_##type(काष्ठा filter_pred *pred, व्योम *event)	\
अणु									\
	type *addr = (type *)(event + pred->offset);			\
	type val = (type)pred->val;					\
	वापस *addr <= val;						\
पूर्ण									\
अटल पूर्णांक filter_pred_GT_##type(काष्ठा filter_pred *pred, व्योम *event)	\
अणु									\
	type *addr = (type *)(event + pred->offset);			\
	type val = (type)pred->val;					\
	वापस *addr > val;					\
पूर्ण									\
अटल पूर्णांक filter_pred_GE_##type(काष्ठा filter_pred *pred, व्योम *event)	\
अणु									\
	type *addr = (type *)(event + pred->offset);			\
	type val = (type)pred->val;					\
	वापस *addr >= val;						\
पूर्ण									\
अटल पूर्णांक filter_pred_BAND_##type(काष्ठा filter_pred *pred, व्योम *event) \
अणु									\
	type *addr = (type *)(event + pred->offset);			\
	type val = (type)pred->val;					\
	वापस !!(*addr & val);						\
पूर्ण									\
अटल स्थिर filter_pred_fn_t pred_funcs_##type[] = अणु			\
	filter_pred_LE_##type,						\
	filter_pred_LT_##type,						\
	filter_pred_GE_##type,						\
	filter_pred_GT_##type,						\
	filter_pred_BAND_##type,					\
पूर्ण;

#घोषणा DEFINE_EQUALITY_PRED(size)					\
अटल पूर्णांक filter_pred_##size(काष्ठा filter_pred *pred, व्योम *event)	\
अणु									\
	u##size *addr = (u##size *)(event + pred->offset);		\
	u##size val = (u##size)pred->val;				\
	पूर्णांक match;							\
									\
	match = (val == *addr) ^ pred->not;				\
									\
	वापस match;							\
पूर्ण

DEFINE_COMPARISON_PRED(s64);
DEFINE_COMPARISON_PRED(u64);
DEFINE_COMPARISON_PRED(s32);
DEFINE_COMPARISON_PRED(u32);
DEFINE_COMPARISON_PRED(s16);
DEFINE_COMPARISON_PRED(u16);
DEFINE_COMPARISON_PRED(s8);
DEFINE_COMPARISON_PRED(u8);

DEFINE_EQUALITY_PRED(64);
DEFINE_EQUALITY_PRED(32);
DEFINE_EQUALITY_PRED(16);
DEFINE_EQUALITY_PRED(8);

/* Filter predicate क्रम fixed sized arrays of अक्षरacters */
अटल पूर्णांक filter_pred_string(काष्ठा filter_pred *pred, व्योम *event)
अणु
	अक्षर *addr = (अक्षर *)(event + pred->offset);
	पूर्णांक cmp, match;

	cmp = pred->regex.match(addr, &pred->regex, pred->regex.field_len);

	match = cmp ^ pred->not;

	वापस match;
पूर्ण

/* Filter predicate क्रम अक्षर * poपूर्णांकers */
अटल पूर्णांक filter_pred_pअक्षर(काष्ठा filter_pred *pred, व्योम *event)
अणु
	अक्षर **addr = (अक्षर **)(event + pred->offset);
	पूर्णांक cmp, match;
	पूर्णांक len = म_माप(*addr) + 1;	/* including tailing '\0' */

	cmp = pred->regex.match(*addr, &pred->regex, len);

	match = cmp ^ pred->not;

	वापस match;
पूर्ण

/*
 * Filter predicate क्रम dynamic sized arrays of अक्षरacters.
 * These are implemented through a list of strings at the end
 * of the entry.
 * Also each of these strings have a field in the entry which
 * contains its offset from the beginning of the entry.
 * We have then first to get this field, dereference it
 * and add it to the address of the entry, and at last we have
 * the address of the string.
 */
अटल पूर्णांक filter_pred_strloc(काष्ठा filter_pred *pred, व्योम *event)
अणु
	u32 str_item = *(u32 *)(event + pred->offset);
	पूर्णांक str_loc = str_item & 0xffff;
	पूर्णांक str_len = str_item >> 16;
	अक्षर *addr = (अक्षर *)(event + str_loc);
	पूर्णांक cmp, match;

	cmp = pred->regex.match(addr, &pred->regex, str_len);

	match = cmp ^ pred->not;

	वापस match;
पूर्ण

/* Filter predicate क्रम CPUs. */
अटल पूर्णांक filter_pred_cpu(काष्ठा filter_pred *pred, व्योम *event)
अणु
	पूर्णांक cpu, cmp;

	cpu = raw_smp_processor_id();
	cmp = pred->val;

	चयन (pred->op) अणु
	हाल OP_EQ:
		वापस cpu == cmp;
	हाल OP_NE:
		वापस cpu != cmp;
	हाल OP_LT:
		वापस cpu < cmp;
	हाल OP_LE:
		वापस cpu <= cmp;
	हाल OP_GT:
		वापस cpu > cmp;
	हाल OP_GE:
		वापस cpu >= cmp;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

/* Filter predicate क्रम COMM. */
अटल पूर्णांक filter_pred_comm(काष्ठा filter_pred *pred, व्योम *event)
अणु
	पूर्णांक cmp;

	cmp = pred->regex.match(current->comm, &pred->regex,
				TASK_COMM_LEN);
	वापस cmp ^ pred->not;
पूर्ण

अटल पूर्णांक filter_pred_none(काष्ठा filter_pred *pred, व्योम *event)
अणु
	वापस 0;
पूर्ण

/*
 * regex_match_foo - Basic regex callbacks
 *
 * @str: the string to be searched
 * @r:   the regex काष्ठाure containing the pattern string
 * @len: the length of the string to be searched (including '\0')
 *
 * Note:
 * - @str might not be शून्य-terminated अगर it's of type DYN_STRING
 *   or STATIC_STRING, unless @len is zero.
 */

अटल पूर्णांक regex_match_full(अक्षर *str, काष्ठा regex *r, पूर्णांक len)
अणु
	/* len of zero means str is dynamic and ends with '\0' */
	अगर (!len)
		वापस म_भेद(str, r->pattern) == 0;

	वापस म_भेदन(str, r->pattern, len) == 0;
पूर्ण

अटल पूर्णांक regex_match_front(अक्षर *str, काष्ठा regex *r, पूर्णांक len)
अणु
	अगर (len && len < r->len)
		वापस 0;

	वापस म_भेदन(str, r->pattern, r->len) == 0;
पूर्ण

अटल पूर्णांक regex_match_middle(अक्षर *str, काष्ठा regex *r, पूर्णांक len)
अणु
	अगर (!len)
		वापस म_माला(str, r->pattern) != शून्य;

	वापस strnstr(str, r->pattern, len) != शून्य;
पूर्ण

अटल पूर्णांक regex_match_end(अक्षर *str, काष्ठा regex *r, पूर्णांक len)
अणु
	पूर्णांक म_माप = len - 1;

	अगर (म_माप >= r->len &&
	    स_भेद(str + म_माप - r->len, r->pattern, r->len) == 0)
		वापस 1;
	वापस 0;
पूर्ण

अटल पूर्णांक regex_match_glob(अक्षर *str, काष्ठा regex *r, पूर्णांक len __maybe_unused)
अणु
	अगर (glob_match(r->pattern, str))
		वापस 1;
	वापस 0;
पूर्ण

/**
 * filter_parse_regex - parse a basic regex
 * @buff:   the raw regex
 * @len:    length of the regex
 * @search: will poपूर्णांक to the beginning of the string to compare
 * @not:    tell whether the match will have to be inverted
 *
 * This passes in a buffer containing a regex and this function will
 * set search to poपूर्णांक to the search part of the buffer and
 * वापस the type of search it is (see क्रमागत above).
 * This करोes modअगरy buff.
 *
 * Returns क्रमागत type.
 *  search वापसs the poपूर्णांकer to use क्रम comparison.
 *  not वापसs 1 अगर buff started with a '!'
 *     0 otherwise.
 */
क्रमागत regex_type filter_parse_regex(अक्षर *buff, पूर्णांक len, अक्षर **search, पूर्णांक *not)
अणु
	पूर्णांक type = MATCH_FULL;
	पूर्णांक i;

	अगर (buff[0] == '!') अणु
		*not = 1;
		buff++;
		len--;
	पूर्ण अन्यथा
		*not = 0;

	*search = buff;

	अगर (है_अंक(buff[0]))
		वापस MATCH_INDEX;

	क्रम (i = 0; i < len; i++) अणु
		अगर (buff[i] == '*') अणु
			अगर (!i) अणु
				type = MATCH_END_ONLY;
			पूर्ण अन्यथा अगर (i == len - 1) अणु
				अगर (type == MATCH_END_ONLY)
					type = MATCH_MIDDLE_ONLY;
				अन्यथा
					type = MATCH_FRONT_ONLY;
				buff[i] = 0;
				अवरोध;
			पूर्ण अन्यथा अणु	/* pattern जारीs, use full glob */
				वापस MATCH_GLOB;
			पूर्ण
		पूर्ण अन्यथा अगर (म_अक्षर("[?\\", buff[i])) अणु
			वापस MATCH_GLOB;
		पूर्ण
	पूर्ण
	अगर (buff[0] == '*')
		*search = buff + 1;

	वापस type;
पूर्ण

अटल व्योम filter_build_regex(काष्ठा filter_pred *pred)
अणु
	काष्ठा regex *r = &pred->regex;
	अक्षर *search;
	क्रमागत regex_type type = MATCH_FULL;

	अगर (pred->op == OP_GLOB) अणु
		type = filter_parse_regex(r->pattern, r->len, &search, &pred->not);
		r->len = म_माप(search);
		स_हटाओ(r->pattern, search, r->len+1);
	पूर्ण

	चयन (type) अणु
	/* MATCH_INDEX should not happen, but अगर it करोes, match full */
	हाल MATCH_INDEX:
	हाल MATCH_FULL:
		r->match = regex_match_full;
		अवरोध;
	हाल MATCH_FRONT_ONLY:
		r->match = regex_match_front;
		अवरोध;
	हाल MATCH_MIDDLE_ONLY:
		r->match = regex_match_middle;
		अवरोध;
	हाल MATCH_END_ONLY:
		r->match = regex_match_end;
		अवरोध;
	हाल MATCH_GLOB:
		r->match = regex_match_glob;
		अवरोध;
	पूर्ण
पूर्ण

/* वापस 1 अगर event matches, 0 otherwise (discard) */
पूर्णांक filter_match_preds(काष्ठा event_filter *filter, व्योम *rec)
अणु
	काष्ठा prog_entry *prog;
	पूर्णांक i;

	/* no filter is considered a match */
	अगर (!filter)
		वापस 1;

	/* Protected by either SRCU(tracepoपूर्णांक_srcu) or preempt_disable */
	prog = rcu_dereference_raw(filter->prog);
	अगर (!prog)
		वापस 1;

	क्रम (i = 0; prog[i].pred; i++) अणु
		काष्ठा filter_pred *pred = prog[i].pred;
		पूर्णांक match = pred->fn(pred, rec);
		अगर (match == prog[i].when_to_branch)
			i = prog[i].target;
	पूर्ण
	वापस prog[i].target;
पूर्ण
EXPORT_SYMBOL_GPL(filter_match_preds);

अटल व्योम हटाओ_filter_string(काष्ठा event_filter *filter)
अणु
	अगर (!filter)
		वापस;

	kमुक्त(filter->filter_string);
	filter->filter_string = शून्य;
पूर्ण

अटल व्योम append_filter_err(काष्ठा trace_array *tr,
			      काष्ठा filter_parse_error *pe,
			      काष्ठा event_filter *filter)
अणु
	काष्ठा trace_seq *s;
	पूर्णांक pos = pe->lasterr_pos;
	अक्षर *buf;
	पूर्णांक len;

	अगर (WARN_ON(!filter->filter_string))
		वापस;

	s = kदो_स्मृति(माप(*s), GFP_KERNEL);
	अगर (!s)
		वापस;
	trace_seq_init(s);

	len = म_माप(filter->filter_string);
	अगर (pos > len)
		pos = len;

	/* indexing is off by one */
	अगर (pos)
		pos++;

	trace_seq_माला_दो(s, filter->filter_string);
	अगर (pe->lasterr > 0) अणु
		trace_seq_म_लिखो(s, "\n%*s", pos, "^");
		trace_seq_म_लिखो(s, "\nparse_error: %s\n", err_text[pe->lasterr]);
		tracing_log_err(tr, "event filter parse error",
				filter->filter_string, err_text,
				pe->lasterr, pe->lasterr_pos);
	पूर्ण अन्यथा अणु
		trace_seq_म_लिखो(s, "\nError: (%d)\n", pe->lasterr);
		tracing_log_err(tr, "event filter parse error",
				filter->filter_string, err_text,
				FILT_ERR_ERRNO, 0);
	पूर्ण
	trace_seq_अ_दो(s, 0);
	buf = kmemdup_nul(s->buffer, s->seq.len, GFP_KERNEL);
	अगर (buf) अणु
		kमुक्त(filter->filter_string);
		filter->filter_string = buf;
	पूर्ण
	kमुक्त(s);
पूर्ण

अटल अंतरभूत काष्ठा event_filter *event_filter(काष्ठा trace_event_file *file)
अणु
	वापस file->filter;
पूर्ण

/* caller must hold event_mutex */
व्योम prपूर्णांक_event_filter(काष्ठा trace_event_file *file, काष्ठा trace_seq *s)
अणु
	काष्ठा event_filter *filter = event_filter(file);

	अगर (filter && filter->filter_string)
		trace_seq_म_लिखो(s, "%s\n", filter->filter_string);
	अन्यथा
		trace_seq_माला_दो(s, "none\n");
पूर्ण

व्योम prपूर्णांक_subप्रणाली_event_filter(काष्ठा event_subप्रणाली *प्रणाली,
				  काष्ठा trace_seq *s)
अणु
	काष्ठा event_filter *filter;

	mutex_lock(&event_mutex);
	filter = प्रणाली->filter;
	अगर (filter && filter->filter_string)
		trace_seq_म_लिखो(s, "%s\n", filter->filter_string);
	अन्यथा
		trace_seq_माला_दो(s, DEFAULT_SYS_FILTER_MESSAGE "\n");
	mutex_unlock(&event_mutex);
पूर्ण

अटल व्योम मुक्त_prog(काष्ठा event_filter *filter)
अणु
	काष्ठा prog_entry *prog;
	पूर्णांक i;

	prog = rcu_access_poपूर्णांकer(filter->prog);
	अगर (!prog)
		वापस;

	क्रम (i = 0; prog[i].pred; i++)
		kमुक्त(prog[i].pred);
	kमुक्त(prog);
पूर्ण

अटल व्योम filter_disable(काष्ठा trace_event_file *file)
अणु
	अचिन्हित दीर्घ old_flags = file->flags;

	file->flags &= ~EVENT_खाता_FL_FILTERED;

	अगर (old_flags != file->flags)
		trace_buffered_event_disable();
पूर्ण

अटल व्योम __मुक्त_filter(काष्ठा event_filter *filter)
अणु
	अगर (!filter)
		वापस;

	मुक्त_prog(filter);
	kमुक्त(filter->filter_string);
	kमुक्त(filter);
पूर्ण

व्योम मुक्त_event_filter(काष्ठा event_filter *filter)
अणु
	__मुक्त_filter(filter);
पूर्ण

अटल अंतरभूत व्योम __हटाओ_filter(काष्ठा trace_event_file *file)
अणु
	filter_disable(file);
	हटाओ_filter_string(file->filter);
पूर्ण

अटल व्योम filter_मुक्त_subप्रणाली_preds(काष्ठा trace_subप्रणाली_dir *dir,
					काष्ठा trace_array *tr)
अणु
	काष्ठा trace_event_file *file;

	list_क्रम_each_entry(file, &tr->events, list) अणु
		अगर (file->प्रणाली != dir)
			जारी;
		__हटाओ_filter(file);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम __मुक्त_subप्रणाली_filter(काष्ठा trace_event_file *file)
अणु
	__मुक्त_filter(file->filter);
	file->filter = शून्य;
पूर्ण

अटल व्योम filter_मुक्त_subप्रणाली_filters(काष्ठा trace_subप्रणाली_dir *dir,
					  काष्ठा trace_array *tr)
अणु
	काष्ठा trace_event_file *file;

	list_क्रम_each_entry(file, &tr->events, list) अणु
		अगर (file->प्रणाली != dir)
			जारी;
		__मुक्त_subप्रणाली_filter(file);
	पूर्ण
पूर्ण

पूर्णांक filter_assign_type(स्थिर अक्षर *type)
अणु
	अगर (म_माला(type, "__data_loc") && म_माला(type, "char"))
		वापस FILTER_DYN_STRING;

	अगर (म_अक्षर(type, '[') && म_माला(type, "char"))
		वापस FILTER_STATIC_STRING;

	अगर (म_भेद(type, "char *") == 0 || म_भेद(type, "const char *") == 0)
		वापस FILTER_PTR_STRING;

	वापस FILTER_OTHER;
पूर्ण

अटल filter_pred_fn_t select_comparison_fn(क्रमागत filter_op_ids op,
					    पूर्णांक field_size, पूर्णांक field_is_चिन्हित)
अणु
	filter_pred_fn_t fn = शून्य;
	पूर्णांक pred_func_index = -1;

	चयन (op) अणु
	हाल OP_EQ:
	हाल OP_NE:
		अवरोध;
	शेष:
		अगर (WARN_ON_ONCE(op < PRED_FUNC_START))
			वापस शून्य;
		pred_func_index = op - PRED_FUNC_START;
		अगर (WARN_ON_ONCE(pred_func_index > PRED_FUNC_MAX))
			वापस शून्य;
	पूर्ण

	चयन (field_size) अणु
	हाल 8:
		अगर (pred_func_index < 0)
			fn = filter_pred_64;
		अन्यथा अगर (field_is_चिन्हित)
			fn = pred_funcs_s64[pred_func_index];
		अन्यथा
			fn = pred_funcs_u64[pred_func_index];
		अवरोध;
	हाल 4:
		अगर (pred_func_index < 0)
			fn = filter_pred_32;
		अन्यथा अगर (field_is_चिन्हित)
			fn = pred_funcs_s32[pred_func_index];
		अन्यथा
			fn = pred_funcs_u32[pred_func_index];
		अवरोध;
	हाल 2:
		अगर (pred_func_index < 0)
			fn = filter_pred_16;
		अन्यथा अगर (field_is_चिन्हित)
			fn = pred_funcs_s16[pred_func_index];
		अन्यथा
			fn = pred_funcs_u16[pred_func_index];
		अवरोध;
	हाल 1:
		अगर (pred_func_index < 0)
			fn = filter_pred_8;
		अन्यथा अगर (field_is_चिन्हित)
			fn = pred_funcs_s8[pred_func_index];
		अन्यथा
			fn = pred_funcs_u8[pred_func_index];
		अवरोध;
	पूर्ण

	वापस fn;
पूर्ण

/* Called when a predicate is encountered by predicate_parse() */
अटल पूर्णांक parse_pred(स्थिर अक्षर *str, व्योम *data,
		      पूर्णांक pos, काष्ठा filter_parse_error *pe,
		      काष्ठा filter_pred **pred_ptr)
अणु
	काष्ठा trace_event_call *call = data;
	काष्ठा ftrace_event_field *field;
	काष्ठा filter_pred *pred = शून्य;
	अक्षर num_buf[24];	/* Big enough to hold an address */
	अक्षर *field_name;
	अक्षर q;
	u64 val;
	पूर्णांक len;
	पूर्णांक ret;
	पूर्णांक op;
	पूर्णांक s;
	पूर्णांक i = 0;

	/* First find the field to associate to */
	जबतक (है_खाली(str[i]))
		i++;
	s = i;

	जबतक (है_अक्षर_अंक(str[i]) || str[i] == '_')
		i++;

	len = i - s;

	अगर (!len)
		वापस -1;

	field_name = kmemdup_nul(str + s, len, GFP_KERNEL);
	अगर (!field_name)
		वापस -ENOMEM;

	/* Make sure that the field exists */

	field = trace_find_event_field(call, field_name);
	kमुक्त(field_name);
	अगर (!field) अणु
		parse_error(pe, FILT_ERR_FIELD_NOT_FOUND, pos + i);
		वापस -EINVAL;
	पूर्ण

	जबतक (है_खाली(str[i]))
		i++;

	/* Make sure this op is supported */
	क्रम (op = 0; ops[op]; op++) अणु
		/* This is why '<=' must come before '<' in ops[] */
		अगर (म_भेदन(str + i, ops[op], म_माप(ops[op])) == 0)
			अवरोध;
	पूर्ण

	अगर (!ops[op]) अणु
		parse_error(pe, FILT_ERR_INVALID_OP, pos + i);
		जाओ err_मुक्त;
	पूर्ण

	i += म_माप(ops[op]);

	जबतक (है_खाली(str[i]))
		i++;

	s = i;

	pred = kzalloc(माप(*pred), GFP_KERNEL);
	अगर (!pred)
		वापस -ENOMEM;

	pred->field = field;
	pred->offset = field->offset;
	pred->op = op;

	अगर (ftrace_event_is_function(call)) अणु
		/*
		 * Perf करोes things dअगरferent with function events.
		 * It only allows an "ip" field, and expects a string.
		 * But the string करोes not need to be surrounded by quotes.
		 * If it is a string, the asचिन्हित function as a nop,
		 * (perf करोesn't use it) and grab everything.
		 */
		अगर (म_भेद(field->name, "ip") != 0) अणु
			parse_error(pe, FILT_ERR_IP_FIELD_ONLY, pos + i);
			जाओ err_मुक्त;
		पूर्ण
		pred->fn = filter_pred_none;

		/*
		 * Quotes are not required, but अगर they exist then we need
		 * to पढ़ो them till we hit a matching one.
		 */
		अगर (str[i] == '\'' || str[i] == '"')
			q = str[i];
		अन्यथा
			q = 0;

		क्रम (i++; str[i]; i++) अणु
			अगर (q && str[i] == q)
				अवरोध;
			अगर (!q && (str[i] == ')' || str[i] == '&' ||
				   str[i] == '|'))
				अवरोध;
		पूर्ण
		/* Skip quotes */
		अगर (q)
			s++;
		len = i - s;
		अगर (len >= MAX_FILTER_STR_VAL) अणु
			parse_error(pe, FILT_ERR_OPERAND_TOO_LONG, pos + i);
			जाओ err_मुक्त;
		पूर्ण

		pred->regex.len = len;
		म_नकलन(pred->regex.pattern, str + s, len);
		pred->regex.pattern[len] = 0;

	/* This is either a string, or an पूर्णांकeger */
	पूर्ण अन्यथा अगर (str[i] == '\'' || str[i] == '"') अणु
		अक्षर q = str[i];

		/* Make sure the op is OK क्रम strings */
		चयन (op) अणु
		हाल OP_NE:
			pred->not = 1;
			fallthrough;
		हाल OP_GLOB:
		हाल OP_EQ:
			अवरोध;
		शेष:
			parse_error(pe, FILT_ERR_ILLEGAL_FIELD_OP, pos + i);
			जाओ err_मुक्त;
		पूर्ण

		/* Make sure the field is OK क्रम strings */
		अगर (!is_string_field(field)) अणु
			parse_error(pe, FILT_ERR_EXPECT_DIGIT, pos + i);
			जाओ err_मुक्त;
		पूर्ण

		क्रम (i++; str[i]; i++) अणु
			अगर (str[i] == q)
				अवरोध;
		पूर्ण
		अगर (!str[i]) अणु
			parse_error(pe, FILT_ERR_MISSING_QUOTE, pos + i);
			जाओ err_मुक्त;
		पूर्ण

		/* Skip quotes */
		s++;
		len = i - s;
		अगर (len >= MAX_FILTER_STR_VAL) अणु
			parse_error(pe, FILT_ERR_OPERAND_TOO_LONG, pos + i);
			जाओ err_मुक्त;
		पूर्ण

		pred->regex.len = len;
		म_नकलन(pred->regex.pattern, str + s, len);
		pred->regex.pattern[len] = 0;

		filter_build_regex(pred);

		अगर (field->filter_type == FILTER_COMM) अणु
			pred->fn = filter_pred_comm;

		पूर्ण अन्यथा अगर (field->filter_type == FILTER_STATIC_STRING) अणु
			pred->fn = filter_pred_string;
			pred->regex.field_len = field->size;

		पूर्ण अन्यथा अगर (field->filter_type == FILTER_DYN_STRING)
			pred->fn = filter_pred_strloc;
		अन्यथा
			pred->fn = filter_pred_pअक्षर;
		/* go past the last quote */
		i++;

	पूर्ण अन्यथा अगर (है_अंक(str[i]) || str[i] == '-') अणु

		/* Make sure the field is not a string */
		अगर (is_string_field(field)) अणु
			parse_error(pe, FILT_ERR_EXPECT_STRING, pos + i);
			जाओ err_मुक्त;
		पूर्ण

		अगर (op == OP_GLOB) अणु
			parse_error(pe, FILT_ERR_ILLEGAL_FIELD_OP, pos + i);
			जाओ err_मुक्त;
		पूर्ण

		अगर (str[i] == '-')
			i++;

		/* We allow 0xDEADBEEF */
		जबतक (है_अक्षर_अंक(str[i]))
			i++;

		len = i - s;
		/* 0xfeedfacedeadbeef is 18 अक्षरs max */
		अगर (len >= माप(num_buf)) अणु
			parse_error(pe, FILT_ERR_OPERAND_TOO_LONG, pos + i);
			जाओ err_मुक्त;
		पूर्ण

		म_नकलन(num_buf, str + s, len);
		num_buf[len] = 0;

		/* Make sure it is a value */
		अगर (field->is_चिन्हित)
			ret = kम_से_दीर्घl(num_buf, 0, &val);
		अन्यथा
			ret = kम_से_अदीर्घl(num_buf, 0, &val);
		अगर (ret) अणु
			parse_error(pe, FILT_ERR_ILLEGAL_INTVAL, pos + s);
			जाओ err_मुक्त;
		पूर्ण

		pred->val = val;

		अगर (field->filter_type == FILTER_CPU)
			pred->fn = filter_pred_cpu;
		अन्यथा अणु
			pred->fn = select_comparison_fn(pred->op, field->size,
							field->is_चिन्हित);
			अगर (pred->op == OP_NE)
				pred->not = 1;
		पूर्ण

	पूर्ण अन्यथा अणु
		parse_error(pe, FILT_ERR_INVALID_VALUE, pos + i);
		जाओ err_मुक्त;
	पूर्ण

	*pred_ptr = pred;
	वापस i;

err_मुक्त:
	kमुक्त(pred);
	वापस -EINVAL;
पूर्ण

क्रमागत अणु
	TOO_MANY_CLOSE		= -1,
	TOO_MANY_OPEN		= -2,
	MISSING_QUOTE		= -3,
पूर्ण;

/*
 * Read the filter string once to calculate the number of predicates
 * as well as how deep the parentheses go.
 *
 * Returns:
 *   0 - everything is fine (err is undefined)
 *  -1 - too many ')'
 *  -2 - too many '('
 *  -3 - No matching quote
 */
अटल पूर्णांक calc_stack(स्थिर अक्षर *str, पूर्णांक *parens, पूर्णांक *preds, पूर्णांक *err)
अणु
	bool is_pred = false;
	पूर्णांक nr_preds = 0;
	पूर्णांक खोलो = 1; /* Count the expression as "(E)" */
	पूर्णांक last_quote = 0;
	पूर्णांक max_खोलो = 1;
	पूर्णांक quote = 0;
	पूर्णांक i;

	*err = 0;

	क्रम (i = 0; str[i]; i++) अणु
		अगर (है_खाली(str[i]))
			जारी;
		अगर (quote) अणु
			अगर (str[i] == quote)
			       quote = 0;
			जारी;
		पूर्ण

		चयन (str[i]) अणु
		हाल '\'':
		हाल '"':
			quote = str[i];
			last_quote = i;
			अवरोध;
		हाल '|':
		हाल '&':
			अगर (str[i+1] != str[i])
				अवरोध;
			is_pred = false;
			जारी;
		हाल '(':
			is_pred = false;
			खोलो++;
			अगर (खोलो > max_खोलो)
				max_खोलो = खोलो;
			जारी;
		हाल ')':
			is_pred = false;
			अगर (खोलो == 1) अणु
				*err = i;
				वापस TOO_MANY_CLOSE;
			पूर्ण
			खोलो--;
			जारी;
		पूर्ण
		अगर (!is_pred) अणु
			nr_preds++;
			is_pred = true;
		पूर्ण
	पूर्ण

	अगर (quote) अणु
		*err = last_quote;
		वापस MISSING_QUOTE;
	पूर्ण

	अगर (खोलो != 1) अणु
		पूर्णांक level = खोलो;

		/* find the bad खोलो */
		क्रम (i--; i; i--) अणु
			अगर (quote) अणु
				अगर (str[i] == quote)
					quote = 0;
				जारी;
			पूर्ण
			चयन (str[i]) अणु
			हाल '(':
				अगर (level == खोलो) अणु
					*err = i;
					वापस TOO_MANY_OPEN;
				पूर्ण
				level--;
				अवरोध;
			हाल ')':
				level++;
				अवरोध;
			हाल '\'':
			हाल '"':
				quote = str[i];
				अवरोध;
			पूर्ण
		पूर्ण
		/* First अक्षरacter is the '(' with missing ')' */
		*err = 0;
		वापस TOO_MANY_OPEN;
	पूर्ण

	/* Set the size of the required stacks */
	*parens = max_खोलो;
	*preds = nr_preds;
	वापस 0;
पूर्ण

अटल पूर्णांक process_preds(काष्ठा trace_event_call *call,
			 स्थिर अक्षर *filter_string,
			 काष्ठा event_filter *filter,
			 काष्ठा filter_parse_error *pe)
अणु
	काष्ठा prog_entry *prog;
	पूर्णांक nr_parens;
	पूर्णांक nr_preds;
	पूर्णांक index;
	पूर्णांक ret;

	ret = calc_stack(filter_string, &nr_parens, &nr_preds, &index);
	अगर (ret < 0) अणु
		चयन (ret) अणु
		हाल MISSING_QUOTE:
			parse_error(pe, FILT_ERR_MISSING_QUOTE, index);
			अवरोध;
		हाल TOO_MANY_OPEN:
			parse_error(pe, FILT_ERR_TOO_MANY_OPEN, index);
			अवरोध;
		शेष:
			parse_error(pe, FILT_ERR_TOO_MANY_CLOSE, index);
		पूर्ण
		वापस ret;
	पूर्ण

	अगर (!nr_preds)
		वापस -EINVAL;

	prog = predicate_parse(filter_string, nr_parens, nr_preds,
			       parse_pred, call, pe);
	अगर (IS_ERR(prog))
		वापस PTR_ERR(prog);

	rcu_assign_poपूर्णांकer(filter->prog, prog);
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम event_set_filtered_flag(काष्ठा trace_event_file *file)
अणु
	अचिन्हित दीर्घ old_flags = file->flags;

	file->flags |= EVENT_खाता_FL_FILTERED;

	अगर (old_flags != file->flags)
		trace_buffered_event_enable();
पूर्ण

अटल अंतरभूत व्योम event_set_filter(काष्ठा trace_event_file *file,
				    काष्ठा event_filter *filter)
अणु
	rcu_assign_poपूर्णांकer(file->filter, filter);
पूर्ण

अटल अंतरभूत व्योम event_clear_filter(काष्ठा trace_event_file *file)
अणु
	RCU_INIT_POINTER(file->filter, शून्य);
पूर्ण

काष्ठा filter_list अणु
	काष्ठा list_head	list;
	काष्ठा event_filter	*filter;
पूर्ण;

अटल पूर्णांक process_प्रणाली_preds(काष्ठा trace_subप्रणाली_dir *dir,
				काष्ठा trace_array *tr,
				काष्ठा filter_parse_error *pe,
				अक्षर *filter_string)
अणु
	काष्ठा trace_event_file *file;
	काष्ठा filter_list *filter_item;
	काष्ठा event_filter *filter = शून्य;
	काष्ठा filter_list *पंचांगp;
	LIST_HEAD(filter_list);
	bool fail = true;
	पूर्णांक err;

	list_क्रम_each_entry(file, &tr->events, list) अणु

		अगर (file->प्रणाली != dir)
			जारी;

		filter = kzalloc(माप(*filter), GFP_KERNEL);
		अगर (!filter)
			जाओ fail_mem;

		filter->filter_string = kstrdup(filter_string, GFP_KERNEL);
		अगर (!filter->filter_string)
			जाओ fail_mem;

		err = process_preds(file->event_call, filter_string, filter, pe);
		अगर (err) अणु
			filter_disable(file);
			parse_error(pe, FILT_ERR_BAD_SUBSYS_FILTER, 0);
			append_filter_err(tr, pe, filter);
		पूर्ण अन्यथा
			event_set_filtered_flag(file);


		filter_item = kzalloc(माप(*filter_item), GFP_KERNEL);
		अगर (!filter_item)
			जाओ fail_mem;

		list_add_tail(&filter_item->list, &filter_list);
		/*
		 * Regardless of अगर this वापसed an error, we still
		 * replace the filter क्रम the call.
		 */
		filter_item->filter = event_filter(file);
		event_set_filter(file, filter);
		filter = शून्य;

		fail = false;
	पूर्ण

	अगर (fail)
		जाओ fail;

	/*
	 * The calls can still be using the old filters.
	 * Do a synchronize_rcu() and to ensure all calls are
	 * करोne with them beक्रमe we मुक्त them.
	 */
	tracepoपूर्णांक_synchronize_unरेजिस्टर();
	list_क्रम_each_entry_safe(filter_item, पंचांगp, &filter_list, list) अणु
		__मुक्त_filter(filter_item->filter);
		list_del(&filter_item->list);
		kमुक्त(filter_item);
	पूर्ण
	वापस 0;
 fail:
	/* No call succeeded */
	list_क्रम_each_entry_safe(filter_item, पंचांगp, &filter_list, list) अणु
		list_del(&filter_item->list);
		kमुक्त(filter_item);
	पूर्ण
	parse_error(pe, FILT_ERR_BAD_SUBSYS_FILTER, 0);
	वापस -EINVAL;
 fail_mem:
	__मुक्त_filter(filter);
	/* If any call succeeded, we still need to sync */
	अगर (!fail)
		tracepoपूर्णांक_synchronize_unरेजिस्टर();
	list_क्रम_each_entry_safe(filter_item, पंचांगp, &filter_list, list) अणु
		__मुक्त_filter(filter_item->filter);
		list_del(&filter_item->list);
		kमुक्त(filter_item);
	पूर्ण
	वापस -ENOMEM;
पूर्ण

अटल पूर्णांक create_filter_start(अक्षर *filter_string, bool set_str,
			       काष्ठा filter_parse_error **pse,
			       काष्ठा event_filter **filterp)
अणु
	काष्ठा event_filter *filter;
	काष्ठा filter_parse_error *pe = शून्य;
	पूर्णांक err = 0;

	अगर (WARN_ON_ONCE(*pse || *filterp))
		वापस -EINVAL;

	filter = kzalloc(माप(*filter), GFP_KERNEL);
	अगर (filter && set_str) अणु
		filter->filter_string = kstrdup(filter_string, GFP_KERNEL);
		अगर (!filter->filter_string)
			err = -ENOMEM;
	पूर्ण

	pe = kzalloc(माप(*pe), GFP_KERNEL);

	अगर (!filter || !pe || err) अणु
		kमुक्त(pe);
		__मुक्त_filter(filter);
		वापस -ENOMEM;
	पूर्ण

	/* we're committed to creating a new filter */
	*filterp = filter;
	*pse = pe;

	वापस 0;
पूर्ण

अटल व्योम create_filter_finish(काष्ठा filter_parse_error *pe)
अणु
	kमुक्त(pe);
पूर्ण

/**
 * create_filter - create a filter क्रम a trace_event_call
 * @tr: the trace array associated with these events
 * @call: trace_event_call to create a filter क्रम
 * @filter_str: filter string
 * @set_str: remember @filter_str and enable detailed error in filter
 * @filterp: out param क्रम created filter (always updated on वापस)
 *           Must be a poपूर्णांकer that references a शून्य poपूर्णांकer.
 *
 * Creates a filter क्रम @call with @filter_str.  If @set_str is %true,
 * @filter_str is copied and recorded in the new filter.
 *
 * On success, वापसs 0 and *@filterp poपूर्णांकs to the new filter.  On
 * failure, वापसs -त्रुटि_सं and *@filterp may poपूर्णांक to %शून्य or to a new
 * filter.  In the latter हाल, the वापसed filter contains error
 * inक्रमmation अगर @set_str is %true and the caller is responsible क्रम
 * मुक्तing it.
 */
अटल पूर्णांक create_filter(काष्ठा trace_array *tr,
			 काष्ठा trace_event_call *call,
			 अक्षर *filter_string, bool set_str,
			 काष्ठा event_filter **filterp)
अणु
	काष्ठा filter_parse_error *pe = शून्य;
	पूर्णांक err;

	/* filterp must poपूर्णांक to शून्य */
	अगर (WARN_ON(*filterp))
		*filterp = शून्य;

	err = create_filter_start(filter_string, set_str, &pe, filterp);
	अगर (err)
		वापस err;

	err = process_preds(call, filter_string, *filterp, pe);
	अगर (err && set_str)
		append_filter_err(tr, pe, *filterp);
	create_filter_finish(pe);

	वापस err;
पूर्ण

पूर्णांक create_event_filter(काष्ठा trace_array *tr,
			काष्ठा trace_event_call *call,
			अक्षर *filter_str, bool set_str,
			काष्ठा event_filter **filterp)
अणु
	वापस create_filter(tr, call, filter_str, set_str, filterp);
पूर्ण

/**
 * create_प्रणाली_filter - create a filter क्रम an event subप्रणाली
 * @dir: the descriptor क्रम the subप्रणाली directory
 * @filter_str: filter string
 * @filterp: out param क्रम created filter (always updated on वापस)
 *
 * Identical to create_filter() except that it creates a subप्रणाली filter
 * and always remembers @filter_str.
 */
अटल पूर्णांक create_प्रणाली_filter(काष्ठा trace_subप्रणाली_dir *dir,
				अक्षर *filter_str, काष्ठा event_filter **filterp)
अणु
	काष्ठा filter_parse_error *pe = शून्य;
	पूर्णांक err;

	err = create_filter_start(filter_str, true, &pe, filterp);
	अगर (!err) अणु
		err = process_प्रणाली_preds(dir, dir->tr, pe, filter_str);
		अगर (!err) अणु
			/* System filters just show a शेष message */
			kमुक्त((*filterp)->filter_string);
			(*filterp)->filter_string = शून्य;
		पूर्ण अन्यथा अणु
			append_filter_err(dir->tr, pe, *filterp);
		पूर्ण
	पूर्ण
	create_filter_finish(pe);

	वापस err;
पूर्ण

/* caller must hold event_mutex */
पूर्णांक apply_event_filter(काष्ठा trace_event_file *file, अक्षर *filter_string)
अणु
	काष्ठा trace_event_call *call = file->event_call;
	काष्ठा event_filter *filter = शून्य;
	पूर्णांक err;

	अगर (!म_भेद(म_मालाip(filter_string), "0")) अणु
		filter_disable(file);
		filter = event_filter(file);

		अगर (!filter)
			वापस 0;

		event_clear_filter(file);

		/* Make sure the filter is not being used */
		tracepoपूर्णांक_synchronize_unरेजिस्टर();
		__मुक्त_filter(filter);

		वापस 0;
	पूर्ण

	err = create_filter(file->tr, call, filter_string, true, &filter);

	/*
	 * Always swap the call filter with the new filter
	 * even अगर there was an error. If there was an error
	 * in the filter, we disable the filter and show the error
	 * string
	 */
	अगर (filter) अणु
		काष्ठा event_filter *पंचांगp;

		पंचांगp = event_filter(file);
		अगर (!err)
			event_set_filtered_flag(file);
		अन्यथा
			filter_disable(file);

		event_set_filter(file, filter);

		अगर (पंचांगp) अणु
			/* Make sure the call is करोne with the filter */
			tracepoपूर्णांक_synchronize_unरेजिस्टर();
			__मुक्त_filter(पंचांगp);
		पूर्ण
	पूर्ण

	वापस err;
पूर्ण

पूर्णांक apply_subप्रणाली_event_filter(काष्ठा trace_subप्रणाली_dir *dir,
				 अक्षर *filter_string)
अणु
	काष्ठा event_subप्रणाली *प्रणाली = dir->subप्रणाली;
	काष्ठा trace_array *tr = dir->tr;
	काष्ठा event_filter *filter = शून्य;
	पूर्णांक err = 0;

	mutex_lock(&event_mutex);

	/* Make sure the प्रणाली still has events */
	अगर (!dir->nr_events) अणु
		err = -ENODEV;
		जाओ out_unlock;
	पूर्ण

	अगर (!म_भेद(म_मालाip(filter_string), "0")) अणु
		filter_मुक्त_subप्रणाली_preds(dir, tr);
		हटाओ_filter_string(प्रणाली->filter);
		filter = प्रणाली->filter;
		प्रणाली->filter = शून्य;
		/* Ensure all filters are no दीर्घer used */
		tracepoपूर्णांक_synchronize_unरेजिस्टर();
		filter_मुक्त_subप्रणाली_filters(dir, tr);
		__मुक्त_filter(filter);
		जाओ out_unlock;
	पूर्ण

	err = create_प्रणाली_filter(dir, filter_string, &filter);
	अगर (filter) अणु
		/*
		 * No event actually uses the प्रणाली filter
		 * we can मुक्त it without synchronize_rcu().
		 */
		__मुक्त_filter(प्रणाली->filter);
		प्रणाली->filter = filter;
	पूर्ण
out_unlock:
	mutex_unlock(&event_mutex);

	वापस err;
पूर्ण

#अगर_घोषित CONFIG_PERF_EVENTS

व्योम ftrace_profile_मुक्त_filter(काष्ठा perf_event *event)
अणु
	काष्ठा event_filter *filter = event->filter;

	event->filter = शून्य;
	__मुक्त_filter(filter);
पूर्ण

काष्ठा function_filter_data अणु
	काष्ठा ftrace_ops *ops;
	पूर्णांक first_filter;
	पूर्णांक first_notrace;
पूर्ण;

#अगर_घोषित CONFIG_FUNCTION_TRACER
अटल अक्षर **
ftrace_function_filter_re(अक्षर *buf, पूर्णांक len, पूर्णांक *count)
अणु
	अक्षर *str, **re;

	str = kstrndup(buf, len, GFP_KERNEL);
	अगर (!str)
		वापस शून्य;

	/*
	 * The argv_split function takes white space
	 * as a separator, so convert ',' पूर्णांकo spaces.
	 */
	strreplace(str, ',', ' ');

	re = argv_split(GFP_KERNEL, str, count);
	kमुक्त(str);
	वापस re;
पूर्ण

अटल पूर्णांक ftrace_function_set_regexp(काष्ठा ftrace_ops *ops, पूर्णांक filter,
				      पूर्णांक reset, अक्षर *re, पूर्णांक len)
अणु
	पूर्णांक ret;

	अगर (filter)
		ret = ftrace_set_filter(ops, re, len, reset);
	अन्यथा
		ret = ftrace_set_notrace(ops, re, len, reset);

	वापस ret;
पूर्ण

अटल पूर्णांक __ftrace_function_set_filter(पूर्णांक filter, अक्षर *buf, पूर्णांक len,
					काष्ठा function_filter_data *data)
अणु
	पूर्णांक i, re_cnt, ret = -EINVAL;
	पूर्णांक *reset;
	अक्षर **re;

	reset = filter ? &data->first_filter : &data->first_notrace;

	/*
	 * The 'ip' field could have multiple filters set, separated
	 * either by space or comma. We first cut the filter and apply
	 * all pieces separately.
	 */
	re = ftrace_function_filter_re(buf, len, &re_cnt);
	अगर (!re)
		वापस -EINVAL;

	क्रम (i = 0; i < re_cnt; i++) अणु
		ret = ftrace_function_set_regexp(data->ops, filter, *reset,
						 re[i], म_माप(re[i]));
		अगर (ret)
			अवरोध;

		अगर (*reset)
			*reset = 0;
	पूर्ण

	argv_मुक्त(re);
	वापस ret;
पूर्ण

अटल पूर्णांक ftrace_function_check_pred(काष्ठा filter_pred *pred)
अणु
	काष्ठा ftrace_event_field *field = pred->field;

	/*
	 * Check the predicate क्रम function trace, verअगरy:
	 *  - only '==' and '!=' is used
	 *  - the 'ip' field is used
	 */
	अगर ((pred->op != OP_EQ) && (pred->op != OP_NE))
		वापस -EINVAL;

	अगर (म_भेद(field->name, "ip"))
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक ftrace_function_set_filter_pred(काष्ठा filter_pred *pred,
					   काष्ठा function_filter_data *data)
अणु
	पूर्णांक ret;

	/* Checking the node is valid क्रम function trace. */
	ret = ftrace_function_check_pred(pred);
	अगर (ret)
		वापस ret;

	वापस __ftrace_function_set_filter(pred->op == OP_EQ,
					    pred->regex.pattern,
					    pred->regex.len,
					    data);
पूर्ण

अटल bool is_or(काष्ठा prog_entry *prog, पूर्णांक i)
अणु
	पूर्णांक target;

	/*
	 * Only "||" is allowed क्रम function events, thus,
	 * all true branches should jump to true, and any
	 * false branch should jump to false.
	 */
	target = prog[i].target + 1;
	/* True and false have शून्य preds (all prog entries should jump to one */
	अगर (prog[target].pred)
		वापस false;

	/* prog[target].target is 1 क्रम TRUE, 0 क्रम FALSE */
	वापस prog[i].when_to_branch == prog[target].target;
पूर्ण

अटल पूर्णांक ftrace_function_set_filter(काष्ठा perf_event *event,
				      काष्ठा event_filter *filter)
अणु
	काष्ठा prog_entry *prog = rcu_dereference_रक्षित(filter->prog,
						lockdep_is_held(&event_mutex));
	काष्ठा function_filter_data data = अणु
		.first_filter  = 1,
		.first_notrace = 1,
		.ops           = &event->ftrace_ops,
	पूर्ण;
	पूर्णांक i;

	क्रम (i = 0; prog[i].pred; i++) अणु
		काष्ठा filter_pred *pred = prog[i].pred;

		अगर (!is_or(prog, i))
			वापस -EINVAL;

		अगर (ftrace_function_set_filter_pred(pred, &data) < 0)
			वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण
#अन्यथा
अटल पूर्णांक ftrace_function_set_filter(काष्ठा perf_event *event,
				      काष्ठा event_filter *filter)
अणु
	वापस -ENODEV;
पूर्ण
#पूर्ण_अगर /* CONFIG_FUNCTION_TRACER */

पूर्णांक ftrace_profile_set_filter(काष्ठा perf_event *event, पूर्णांक event_id,
			      अक्षर *filter_str)
अणु
	पूर्णांक err;
	काष्ठा event_filter *filter = शून्य;
	काष्ठा trace_event_call *call;

	mutex_lock(&event_mutex);

	call = event->tp_event;

	err = -EINVAL;
	अगर (!call)
		जाओ out_unlock;

	err = -EEXIST;
	अगर (event->filter)
		जाओ out_unlock;

	err = create_filter(शून्य, call, filter_str, false, &filter);
	अगर (err)
		जाओ मुक्त_filter;

	अगर (ftrace_event_is_function(call))
		err = ftrace_function_set_filter(event, filter);
	अन्यथा
		event->filter = filter;

मुक्त_filter:
	अगर (err || ftrace_event_is_function(call))
		__मुक्त_filter(filter);

out_unlock:
	mutex_unlock(&event_mutex);

	वापस err;
पूर्ण

#पूर्ण_अगर /* CONFIG_PERF_EVENTS */

#अगर_घोषित CONFIG_FTRACE_STARTUP_TEST

#समावेश <linux/types.h>
#समावेश <linux/tracepoपूर्णांक.h>

#घोषणा CREATE_TRACE_POINTS
#समावेश "trace_events_filter_test.h"

#घोषणा DATA_REC(m, va, vb, vc, vd, ve, vf, vg, vh, nvisit) \
अणु \
	.filter = FILTER, \
	.rec    = अणु .a = va, .b = vb, .c = vc, .d = vd, \
		    .e = ve, .f = vf, .g = vg, .h = vh पूर्ण, \
	.match  = m, \
	.not_visited = nvisit, \
पूर्ण
#घोषणा YES 1
#घोषणा NO  0

अटल काष्ठा test_filter_data_t अणु
	अक्षर *filter;
	काष्ठा trace_event_raw_ftrace_test_filter rec;
	पूर्णांक match;
	अक्षर *not_visited;
पूर्ण test_filter_data[] = अणु
#घोषणा FILTER "a == 1 && b == 1 && c == 1 && d == 1 && " \
	       "e == 1 && f == 1 && g == 1 && h == 1"
	DATA_REC(YES, 1, 1, 1, 1, 1, 1, 1, 1, ""),
	DATA_REC(NO,  0, 1, 1, 1, 1, 1, 1, 1, "bcdefgh"),
	DATA_REC(NO,  1, 1, 1, 1, 1, 1, 1, 0, ""),
#अघोषित FILTER
#घोषणा FILTER "a == 1 || b == 1 || c == 1 || d == 1 || " \
	       "e == 1 || f == 1 || g == 1 || h == 1"
	DATA_REC(NO,  0, 0, 0, 0, 0, 0, 0, 0, ""),
	DATA_REC(YES, 0, 0, 0, 0, 0, 0, 0, 1, ""),
	DATA_REC(YES, 1, 0, 0, 0, 0, 0, 0, 0, "bcdefgh"),
#अघोषित FILTER
#घोषणा FILTER "(a == 1 || b == 1) && (c == 1 || d == 1) && " \
	       "(e == 1 || f == 1) && (g == 1 || h == 1)"
	DATA_REC(NO,  0, 0, 1, 1, 1, 1, 1, 1, "dfh"),
	DATA_REC(YES, 0, 1, 0, 1, 0, 1, 0, 1, ""),
	DATA_REC(YES, 1, 0, 1, 0, 0, 1, 0, 1, "bd"),
	DATA_REC(NO,  1, 0, 1, 0, 0, 1, 0, 0, "bd"),
#अघोषित FILTER
#घोषणा FILTER "(a == 1 && b == 1) || (c == 1 && d == 1) || " \
	       "(e == 1 && f == 1) || (g == 1 && h == 1)"
	DATA_REC(YES, 1, 0, 1, 1, 1, 1, 1, 1, "efgh"),
	DATA_REC(YES, 0, 0, 0, 0, 0, 0, 1, 1, ""),
	DATA_REC(NO,  0, 0, 0, 0, 0, 0, 0, 1, ""),
#अघोषित FILTER
#घोषणा FILTER "(a == 1 && b == 1) && (c == 1 && d == 1) && " \
	       "(e == 1 && f == 1) || (g == 1 && h == 1)"
	DATA_REC(YES, 1, 1, 1, 1, 1, 1, 0, 0, "gh"),
	DATA_REC(NO,  0, 0, 0, 0, 0, 0, 0, 1, ""),
	DATA_REC(YES, 1, 1, 1, 1, 1, 0, 1, 1, ""),
#अघोषित FILTER
#घोषणा FILTER "((a == 1 || b == 1) || (c == 1 || d == 1) || " \
	       "(e == 1 || f == 1)) && (g == 1 || h == 1)"
	DATA_REC(YES, 1, 1, 1, 1, 1, 1, 0, 1, "bcdef"),
	DATA_REC(NO,  0, 0, 0, 0, 0, 0, 0, 0, ""),
	DATA_REC(YES, 1, 1, 1, 1, 1, 0, 1, 1, "h"),
#अघोषित FILTER
#घोषणा FILTER "((((((((a == 1) && (b == 1)) || (c == 1)) && (d == 1)) || " \
	       "(e == 1)) && (f == 1)) || (g == 1)) && (h == 1))"
	DATA_REC(YES, 1, 1, 1, 1, 1, 1, 1, 1, "ceg"),
	DATA_REC(NO,  0, 1, 0, 1, 0, 1, 0, 1, ""),
	DATA_REC(NO,  1, 0, 1, 0, 1, 0, 1, 0, ""),
#अघोषित FILTER
#घोषणा FILTER "((((((((a == 1) || (b == 1)) && (c == 1)) || (d == 1)) && " \
	       "(e == 1)) || (f == 1)) && (g == 1)) || (h == 1))"
	DATA_REC(YES, 1, 1, 1, 1, 1, 1, 1, 1, "bdfh"),
	DATA_REC(YES, 0, 1, 0, 1, 0, 1, 0, 1, ""),
	DATA_REC(YES, 1, 0, 1, 0, 1, 0, 1, 0, "bdfh"),
पूर्ण;

#अघोषित DATA_REC
#अघोषित FILTER
#अघोषित YES
#अघोषित NO

#घोषणा DATA_CNT ARRAY_SIZE(test_filter_data)

अटल पूर्णांक test_pred_visited;

अटल पूर्णांक test_pred_visited_fn(काष्ठा filter_pred *pred, व्योम *event)
अणु
	काष्ठा ftrace_event_field *field = pred->field;

	test_pred_visited = 1;
	prपूर्णांकk(KERN_INFO "\npred visited %s\n", field->name);
	वापस 1;
पूर्ण

अटल व्योम update_pred_fn(काष्ठा event_filter *filter, अक्षर *fields)
अणु
	काष्ठा prog_entry *prog = rcu_dereference_रक्षित(filter->prog,
						lockdep_is_held(&event_mutex));
	पूर्णांक i;

	क्रम (i = 0; prog[i].pred; i++) अणु
		काष्ठा filter_pred *pred = prog[i].pred;
		काष्ठा ftrace_event_field *field = pred->field;

		WARN_ON_ONCE(!pred->fn);

		अगर (!field) अणु
			WARN_ONCE(1, "all leafs should have field defined %d", i);
			जारी;
		पूर्ण

		अगर (!म_अक्षर(fields, *field->name))
			जारी;

		pred->fn = test_pred_visited_fn;
	पूर्ण
पूर्ण

अटल __init पूर्णांक ftrace_test_event_filter(व्योम)
अणु
	पूर्णांक i;

	prपूर्णांकk(KERN_INFO "Testing ftrace filter: ");

	क्रम (i = 0; i < DATA_CNT; i++) अणु
		काष्ठा event_filter *filter = शून्य;
		काष्ठा test_filter_data_t *d = &test_filter_data[i];
		पूर्णांक err;

		err = create_filter(शून्य, &event_ftrace_test_filter,
				    d->filter, false, &filter);
		अगर (err) अणु
			prपूर्णांकk(KERN_INFO
			       "Failed to get filter for '%s', err %d\n",
			       d->filter, err);
			__मुक्त_filter(filter);
			अवरोध;
		पूर्ण

		/* Needed to dereference filter->prog */
		mutex_lock(&event_mutex);
		/*
		 * The preemption disabling is not really needed क्रम self
		 * tests, but the rcu dereference will complain without it.
		 */
		preempt_disable();
		अगर (*d->not_visited)
			update_pred_fn(filter, d->not_visited);

		test_pred_visited = 0;
		err = filter_match_preds(filter, &d->rec);
		preempt_enable();

		mutex_unlock(&event_mutex);

		__मुक्त_filter(filter);

		अगर (test_pred_visited) अणु
			prपूर्णांकk(KERN_INFO
			       "Failed, unwanted pred visited for filter %s\n",
			       d->filter);
			अवरोध;
		पूर्ण

		अगर (err != d->match) अणु
			prपूर्णांकk(KERN_INFO
			       "Failed to match filter '%s', expected %d\n",
			       d->filter, d->match);
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (i == DATA_CNT)
		prपूर्णांकk(KERN_CONT "OK\n");

	वापस 0;
पूर्ण

late_initcall(ftrace_test_event_filter);

#पूर्ण_अगर /* CONFIG_FTRACE_STARTUP_TEST */
