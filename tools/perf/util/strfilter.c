<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश "string2.h"
#समावेश "strfilter.h"

#समावेश <त्रुटिसं.स>
#समावेश <मानककोष.स>
#समावेश <linux/प्रकार.स>
#समावेश <linux/माला.स>
#समावेश <linux/zभाग.स>

/* Operators */
अटल स्थिर अक्षर *OP_and	= "&";	/* Logical AND */
अटल स्थिर अक्षर *OP_or	= "|";	/* Logical OR */
अटल स्थिर अक्षर *OP_not	= "!";	/* Logical NOT */

#घोषणा is_चालक(c)	((c) == '|' || (c) == '&' || (c) == '!')
#घोषणा is_separator(c)	(is_चालक(c) || (c) == '(' || (c) == ')')

अटल व्योम strfilter_node__delete(काष्ठा strfilter_node *node)
अणु
	अगर (node) अणु
		अगर (node->p && !is_चालक(*node->p))
			zमुक्त((अक्षर **)&node->p);
		strfilter_node__delete(node->l);
		strfilter_node__delete(node->r);
		मुक्त(node);
	पूर्ण
पूर्ण

व्योम strfilter__delete(काष्ठा strfilter *filter)
अणु
	अगर (filter) अणु
		strfilter_node__delete(filter->root);
		मुक्त(filter);
	पूर्ण
पूर्ण

अटल स्थिर अक्षर *get_token(स्थिर अक्षर *s, स्थिर अक्षर **e)
अणु
	स्थिर अक्षर *p;

	s = skip_spaces(s);

	अगर (*s == '\0') अणु
		p = s;
		जाओ end;
	पूर्ण

	p = s + 1;
	अगर (!is_separator(*s)) अणु
		/* End search */
retry:
		जबतक (*p && !is_separator(*p) && !है_खाली(*p))
			p++;
		/* Escape and special हाल: '!' is also used in glob pattern */
		अगर (*(p - 1) == '\\' || (*p == '!' && *(p - 1) == '[')) अणु
			p++;
			जाओ retry;
		पूर्ण
	पूर्ण
end:
	*e = p;
	वापस s;
पूर्ण

अटल काष्ठा strfilter_node *strfilter_node__alloc(स्थिर अक्षर *op,
						    काष्ठा strfilter_node *l,
						    काष्ठा strfilter_node *r)
अणु
	काष्ठा strfilter_node *node = zalloc(माप(*node));

	अगर (node) अणु
		node->p = op;
		node->l = l;
		node->r = r;
	पूर्ण

	वापस node;
पूर्ण

अटल काष्ठा strfilter_node *strfilter_node__new(स्थिर अक्षर *s,
						  स्थिर अक्षर **ep)
अणु
	काष्ठा strfilter_node root, *cur, *last_op;
	स्थिर अक्षर *e;

	अगर (!s)
		वापस शून्य;

	स_रखो(&root, 0, माप(root));
	last_op = cur = &root;

	s = get_token(s, &e);
	जबतक (*s != '\0' && *s != ')') अणु
		चयन (*s) अणु
		हाल '&':	/* Exchg last OP->r with AND */
			अगर (!cur->r || !last_op->r)
				जाओ error;
			cur = strfilter_node__alloc(OP_and, last_op->r, शून्य);
			अगर (!cur)
				जाओ nomem;
			last_op->r = cur;
			last_op = cur;
			अवरोध;
		हाल '|':	/* Exchg the root with OR */
			अगर (!cur->r || !root.r)
				जाओ error;
			cur = strfilter_node__alloc(OP_or, root.r, शून्य);
			अगर (!cur)
				जाओ nomem;
			root.r = cur;
			last_op = cur;
			अवरोध;
		हाल '!':	/* Add NOT as a leaf node */
			अगर (cur->r)
				जाओ error;
			cur->r = strfilter_node__alloc(OP_not, शून्य, शून्य);
			अगर (!cur->r)
				जाओ nomem;
			cur = cur->r;
			अवरोध;
		हाल '(':	/* Recursively parses inside the parenthesis */
			अगर (cur->r)
				जाओ error;
			cur->r = strfilter_node__new(s + 1, &s);
			अगर (!s)
				जाओ nomem;
			अगर (!cur->r || *s != ')')
				जाओ error;
			e = s + 1;
			अवरोध;
		शेष:
			अगर (cur->r)
				जाओ error;
			cur->r = strfilter_node__alloc(शून्य, शून्य, शून्य);
			अगर (!cur->r)
				जाओ nomem;
			cur->r->p = strndup(s, e - s);
			अगर (!cur->r->p)
				जाओ nomem;
		पूर्ण
		s = get_token(e, &e);
	पूर्ण
	अगर (!cur->r)
		जाओ error;
	*ep = s;
	वापस root.r;
nomem:
	s = शून्य;
error:
	*ep = s;
	strfilter_node__delete(root.r);
	वापस शून्य;
पूर्ण

/*
 * Parse filter rule and वापस new strfilter.
 * Return शून्य अगर fail, and *ep == शून्य अगर memory allocation failed.
 */
काष्ठा strfilter *strfilter__new(स्थिर अक्षर *rules, स्थिर अक्षर **err)
अणु
	काष्ठा strfilter *filter = zalloc(माप(*filter));
	स्थिर अक्षर *ep = शून्य;

	अगर (filter)
		filter->root = strfilter_node__new(rules, &ep);

	अगर (!filter || !filter->root || *ep != '\0') अणु
		अगर (err)
			*err = ep;
		strfilter__delete(filter);
		filter = शून्य;
	पूर्ण

	वापस filter;
पूर्ण

अटल पूर्णांक strfilter__append(काष्ठा strfilter *filter, bool _or,
			     स्थिर अक्षर *rules, स्थिर अक्षर **err)
अणु
	काष्ठा strfilter_node *right, *root;
	स्थिर अक्षर *ep = शून्य;

	अगर (!filter || !rules)
		वापस -EINVAL;

	right = strfilter_node__new(rules, &ep);
	अगर (!right || *ep != '\0') अणु
		अगर (err)
			*err = ep;
		जाओ error;
	पूर्ण
	root = strfilter_node__alloc(_or ? OP_or : OP_and, filter->root, right);
	अगर (!root) अणु
		ep = शून्य;
		जाओ error;
	पूर्ण

	filter->root = root;
	वापस 0;

error:
	strfilter_node__delete(right);
	वापस ep ? -EINVAL : -ENOMEM;
पूर्ण

पूर्णांक strfilter__or(काष्ठा strfilter *filter, स्थिर अक्षर *rules, स्थिर अक्षर **err)
अणु
	वापस strfilter__append(filter, true, rules, err);
पूर्ण

पूर्णांक strfilter__and(काष्ठा strfilter *filter, स्थिर अक्षर *rules,
		   स्थिर अक्षर **err)
अणु
	वापस strfilter__append(filter, false, rules, err);
पूर्ण

अटल bool strfilter_node__compare(काष्ठा strfilter_node *node,
				    स्थिर अक्षर *str)
अणु
	अगर (!node || !node->p)
		वापस false;

	चयन (*node->p) अणु
	हाल '|':	/* OR */
		वापस strfilter_node__compare(node->l, str) ||
			strfilter_node__compare(node->r, str);
	हाल '&':	/* AND */
		वापस strfilter_node__compare(node->l, str) &&
			strfilter_node__compare(node->r, str);
	हाल '!':	/* NOT */
		वापस !strfilter_node__compare(node->r, str);
	शेष:
		वापस strglobmatch(str, node->p);
	पूर्ण
पूर्ण

/* Return true अगर STR matches the filter rules */
bool strfilter__compare(काष्ठा strfilter *filter, स्थिर अक्षर *str)
अणु
	अगर (!filter)
		वापस false;
	वापस strfilter_node__compare(filter->root, str);
पूर्ण

अटल पूर्णांक strfilter_node__sprपूर्णांक(काष्ठा strfilter_node *node, अक्षर *buf);

/* sprपूर्णांक node in parenthesis अगर needed */
अटल पूर्णांक strfilter_node__sprपूर्णांक_pt(काष्ठा strfilter_node *node, अक्षर *buf)
अणु
	पूर्णांक len;
	पूर्णांक pt = node->r ? 2 : 0;	/* करोn't need to check node->l */

	अगर (buf && pt)
		*buf++ = '(';
	len = strfilter_node__sprपूर्णांक(node, buf);
	अगर (len < 0)
		वापस len;
	अगर (buf && pt)
		*(buf + len) = ')';
	वापस len + pt;
पूर्ण

अटल पूर्णांक strfilter_node__sprपूर्णांक(काष्ठा strfilter_node *node, अक्षर *buf)
अणु
	पूर्णांक len = 0, rlen;

	अगर (!node || !node->p)
		वापस -EINVAL;

	चयन (*node->p) अणु
	हाल '|':
	हाल '&':
		len = strfilter_node__sprपूर्णांक_pt(node->l, buf);
		अगर (len < 0)
			वापस len;
		__fallthrough;
	हाल '!':
		अगर (buf) अणु
			*(buf + len++) = *node->p;
			buf += len;
		पूर्ण अन्यथा
			len++;
		rlen = strfilter_node__sprपूर्णांक_pt(node->r, buf);
		अगर (rlen < 0)
			वापस rlen;
		len += rlen;
		अवरोध;
	शेष:
		len = म_माप(node->p);
		अगर (buf)
			म_नकल(buf, node->p);
	पूर्ण

	वापस len;
पूर्ण

अक्षर *strfilter__string(काष्ठा strfilter *filter)
अणु
	पूर्णांक len;
	अक्षर *ret = शून्य;

	len = strfilter_node__sprपूर्णांक(filter->root, शून्य);
	अगर (len < 0)
		वापस शून्य;

	ret = दो_स्मृति(len + 1);
	अगर (ret)
		strfilter_node__sprपूर्णांक(filter->root, ret);

	वापस ret;
पूर्ण
