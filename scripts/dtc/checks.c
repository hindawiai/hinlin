<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * (C) Copyright David Gibson <dwg@au1.ibm.com>, IBM Corporation.  2007.
 */

#समावेश "dtc.h"
#समावेश "srcpos.h"

#अगर_घोषित TRACE_CHECKS
#घोषणा TRACE(c, ...) \
	करो अणु \
		ख_लिखो(मानक_त्रुटि, "=== %s: ", (c)->name); \
		ख_लिखो(मानक_त्रुटि, __VA_ARGS__); \
		ख_लिखो(मानक_त्रुटि, "\n"); \
	पूर्ण जबतक (0)
#अन्यथा
#घोषणा TRACE(c, fmt, ...)	करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर

क्रमागत checkstatus अणु
	UNCHECKED = 0,
	PREREQ,
	PASSED,
	FAILED,
पूर्ण;

काष्ठा check;

प्रकार व्योम (*check_fn)(काष्ठा check *c, काष्ठा dt_info *dti, काष्ठा node *node);

काष्ठा check अणु
	स्थिर अक्षर *name;
	check_fn fn;
	व्योम *data;
	bool warn, error;
	क्रमागत checkstatus status;
	bool inprogress;
	पूर्णांक num_prereqs;
	काष्ठा check **prereq;
पूर्ण;

#घोषणा CHECK_ENTRY(nm_, fn_, d_, w_, e_, ...)	       \
	अटल काष्ठा check *nm_##_prereqs[] = अणु __VA_ARGS__ पूर्ण; \
	अटल काष्ठा check nm_ = अणु \
		.name = #nm_, \
		.fn = (fn_), \
		.data = (d_), \
		.warn = (w_), \
		.error = (e_), \
		.status = UNCHECKED, \
		.num_prereqs = ARRAY_SIZE(nm_##_prereqs), \
		.prereq = nm_##_prereqs, \
	पूर्ण;
#घोषणा WARNING(nm_, fn_, d_, ...) \
	CHECK_ENTRY(nm_, fn_, d_, true, false, __VA_ARGS__)
#घोषणा ERROR(nm_, fn_, d_, ...) \
	CHECK_ENTRY(nm_, fn_, d_, false, true, __VA_ARGS__)
#घोषणा CHECK(nm_, fn_, d_, ...) \
	CHECK_ENTRY(nm_, fn_, d_, false, false, __VA_ARGS__)

अटल अंतरभूत व्योम  PRINTF(5, 6) check_msg(काष्ठा check *c, काष्ठा dt_info *dti,
					   काष्ठा node *node,
					   काष्ठा property *prop,
					   स्थिर अक्षर *fmt, ...)
अणु
	बहु_सूची ap;
	अक्षर *str = शून्य;
	काष्ठा srcpos *pos = शून्य;
	अक्षर *file_str;

	अगर (!(c->warn && (quiet < 1)) && !(c->error && (quiet < 2)))
		वापस;

	अगर (prop && prop->srcpos)
		pos = prop->srcpos;
	अन्यथा अगर (node && node->srcpos)
		pos = node->srcpos;

	अगर (pos) अणु
		file_str = srcpos_string(pos);
		xaप्र_लिखो(&str, "%s", file_str);
		मुक्त(file_str);
	पूर्ण अन्यथा अगर (streq(dti->outname, "-")) अणु
		xaप्र_लिखो(&str, "<stdout>");
	पूर्ण अन्यथा अणु
		xaप्र_लिखो(&str, "%s", dti->outname);
	पूर्ण

	xaप्र_लिखो_append(&str, ": %s (%s): ",
			(c->error) ? "ERROR" : "Warning", c->name);

	अगर (node) अणु
		अगर (prop)
			xaप्र_लिखो_append(&str, "%s:%s: ", node->fullpath, prop->name);
		अन्यथा
			xaप्र_लिखो_append(&str, "%s: ", node->fullpath);
	पूर्ण

	बहु_शुरू(ap, fmt);
	xaभम_लिखो_append(&str, fmt, ap);
	बहु_पूर्ण(ap);

	xaप्र_लिखो_append(&str, "\n");

	अगर (!prop && pos) अणु
		pos = node->srcpos;
		जबतक (pos->next) अणु
			pos = pos->next;

			file_str = srcpos_string(pos);
			xaप्र_लिखो_append(&str, "  also defined at %s\n", file_str);
			मुक्त(file_str);
		पूर्ण
	पूर्ण

	ख_माला_दो(str, मानक_त्रुटि);
पूर्ण

#घोषणा FAIL(c, dti, node, ...)						\
	करो अणु								\
		TRACE((c), "\t\tFAILED at %s:%d", __खाता__, __LINE__);	\
		(c)->status = FAILED;					\
		check_msg((c), dti, node, शून्य, __VA_ARGS__);		\
	पूर्ण जबतक (0)

#घोषणा FAIL_PROP(c, dti, node, prop, ...)				\
	करो अणु								\
		TRACE((c), "\t\tFAILED at %s:%d", __खाता__, __LINE__);	\
		(c)->status = FAILED;					\
		check_msg((c), dti, node, prop, __VA_ARGS__);		\
	पूर्ण जबतक (0)


अटल व्योम check_nodes_props(काष्ठा check *c, काष्ठा dt_info *dti, काष्ठा node *node)
अणु
	काष्ठा node *child;

	TRACE(c, "%s", node->fullpath);
	अगर (c->fn)
		c->fn(c, dti, node);

	क्रम_each_child(node, child)
		check_nodes_props(c, dti, child);
पूर्ण

अटल bool run_check(काष्ठा check *c, काष्ठा dt_info *dti)
अणु
	काष्ठा node *dt = dti->dt;
	bool error = false;
	पूर्णांक i;

	निश्चित(!c->inprogress);

	अगर (c->status != UNCHECKED)
		जाओ out;

	c->inprogress = true;

	क्रम (i = 0; i < c->num_prereqs; i++) अणु
		काष्ठा check *prq = c->prereq[i];
		error = error || run_check(prq, dti);
		अगर (prq->status != PASSED) अणु
			c->status = PREREQ;
			check_msg(c, dti, शून्य, शून्य, "Failed prerequisite '%s'",
				  c->prereq[i]->name);
		पूर्ण
	पूर्ण

	अगर (c->status != UNCHECKED)
		जाओ out;

	check_nodes_props(c, dti, dt);

	अगर (c->status == UNCHECKED)
		c->status = PASSED;

	TRACE(c, "\tCompleted, status %d", c->status);

out:
	c->inprogress = false;
	अगर ((c->status != PASSED) && (c->error))
		error = true;
	वापस error;
पूर्ण

/*
 * Utility check functions
 */

/* A check which always fails, क्रम testing purposes only */
अटल अंतरभूत व्योम check_always_fail(काष्ठा check *c, काष्ठा dt_info *dti,
				     काष्ठा node *node)
अणु
	FAIL(c, dti, node, "always_fail check");
पूर्ण
CHECK(always_fail, check_always_fail, शून्य);

अटल व्योम check_is_string(काष्ठा check *c, काष्ठा dt_info *dti,
			    काष्ठा node *node)
अणु
	काष्ठा property *prop;
	अक्षर *propname = c->data;

	prop = get_property(node, propname);
	अगर (!prop)
		वापस; /* Not present, assumed ok */

	अगर (!data_is_one_string(prop->val))
		FAIL_PROP(c, dti, node, prop, "property is not a string");
पूर्ण
#घोषणा WARNING_IF_NOT_STRING(nm, propname) \
	WARNING(nm, check_is_string, (propname))
#घोषणा ERROR_IF_NOT_STRING(nm, propname) \
	ERROR(nm, check_is_string, (propname))

अटल व्योम check_is_string_list(काष्ठा check *c, काष्ठा dt_info *dti,
				 काष्ठा node *node)
अणु
	पूर्णांक rem, l;
	काष्ठा property *prop;
	अक्षर *propname = c->data;
	अक्षर *str;

	prop = get_property(node, propname);
	अगर (!prop)
		वापस; /* Not present, assumed ok */

	str = prop->val.val;
	rem = prop->val.len;
	जबतक (rem > 0) अणु
		l = strnlen(str, rem);
		अगर (l == rem) अणु
			FAIL_PROP(c, dti, node, prop, "property is not a string list");
			अवरोध;
		पूर्ण
		rem -= l + 1;
		str += l + 1;
	पूर्ण
पूर्ण
#घोषणा WARNING_IF_NOT_STRING_LIST(nm, propname) \
	WARNING(nm, check_is_string_list, (propname))
#घोषणा ERROR_IF_NOT_STRING_LIST(nm, propname) \
	ERROR(nm, check_is_string_list, (propname))

अटल व्योम check_is_cell(काष्ठा check *c, काष्ठा dt_info *dti,
			  काष्ठा node *node)
अणु
	काष्ठा property *prop;
	अक्षर *propname = c->data;

	prop = get_property(node, propname);
	अगर (!prop)
		वापस; /* Not present, assumed ok */

	अगर (prop->val.len != माप(cell_t))
		FAIL_PROP(c, dti, node, prop, "property is not a single cell");
पूर्ण
#घोषणा WARNING_IF_NOT_CELL(nm, propname) \
	WARNING(nm, check_is_cell, (propname))
#घोषणा ERROR_IF_NOT_CELL(nm, propname) \
	ERROR(nm, check_is_cell, (propname))

/*
 * Structural check functions
 */

अटल व्योम check_duplicate_node_names(काष्ठा check *c, काष्ठा dt_info *dti,
				       काष्ठा node *node)
अणु
	काष्ठा node *child, *child2;

	क्रम_each_child(node, child)
		क्रम (child2 = child->next_sibling;
		     child2;
		     child2 = child2->next_sibling)
			अगर (streq(child->name, child2->name))
				FAIL(c, dti, child2, "Duplicate node name");
पूर्ण
ERROR(duplicate_node_names, check_duplicate_node_names, शून्य);

अटल व्योम check_duplicate_property_names(काष्ठा check *c, काष्ठा dt_info *dti,
					   काष्ठा node *node)
अणु
	काष्ठा property *prop, *prop2;

	क्रम_each_property(node, prop) अणु
		क्रम (prop2 = prop->next; prop2; prop2 = prop2->next) अणु
			अगर (prop2->deleted)
				जारी;
			अगर (streq(prop->name, prop2->name))
				FAIL_PROP(c, dti, node, prop, "Duplicate property name");
		पूर्ण
	पूर्ण
पूर्ण
ERROR(duplicate_property_names, check_duplicate_property_names, शून्य);

#घोषणा LOWERCASE	"abcdefghijklmnopqrstuvwxyz"
#घोषणा UPPERCASE	"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
#घोषणा DIGITS		"0123456789"
#घोषणा PROPNODECHARS	LOWERCASE UPPERCASE DIGITS ",._+*#?-"
#घोषणा PROPNODECHARSSTRICT	LOWERCASE UPPERCASE DIGITS ",-"

अटल व्योम check_node_name_अक्षरs(काष्ठा check *c, काष्ठा dt_info *dti,
				  काष्ठा node *node)
अणु
	पूर्णांक n = म_अखोज(node->name, c->data);

	अगर (n < म_माप(node->name))
		FAIL(c, dti, node, "Bad character '%c' in node name",
		     node->name[n]);
पूर्ण
ERROR(node_name_अक्षरs, check_node_name_अक्षरs, PROPNODECHARS "@");

अटल व्योम check_node_name_अक्षरs_strict(काष्ठा check *c, काष्ठा dt_info *dti,
					 काष्ठा node *node)
अणु
	पूर्णांक n = म_अखोज(node->name, c->data);

	अगर (n < node->basenamelen)
		FAIL(c, dti, node, "Character '%c' not recommended in node name",
		     node->name[n]);
पूर्ण
CHECK(node_name_अक्षरs_strict, check_node_name_अक्षरs_strict, PROPNODECHARSSTRICT);

अटल व्योम check_node_name_क्रमmat(काष्ठा check *c, काष्ठा dt_info *dti,
				   काष्ठा node *node)
अणु
	अगर (म_अक्षर(get_unitname(node), '@'))
		FAIL(c, dti, node, "multiple '@' characters in node name");
पूर्ण
ERROR(node_name_क्रमmat, check_node_name_क्रमmat, शून्य, &node_name_अक्षरs);

अटल व्योम check_unit_address_vs_reg(काष्ठा check *c, काष्ठा dt_info *dti,
				      काष्ठा node *node)
अणु
	स्थिर अक्षर *unitname = get_unitname(node);
	काष्ठा property *prop = get_property(node, "reg");

	अगर (get_subnode(node, "__overlay__")) अणु
		/* HACK: Overlay fragments are a special हाल */
		वापस;
	पूर्ण

	अगर (!prop) अणु
		prop = get_property(node, "ranges");
		अगर (prop && !prop->val.len)
			prop = शून्य;
	पूर्ण

	अगर (prop) अणु
		अगर (!unitname[0])
			FAIL(c, dti, node, "node has a reg or ranges property, but no unit name");
	पूर्ण अन्यथा अणु
		अगर (unitname[0])
			FAIL(c, dti, node, "node has a unit name, but no reg or ranges property");
	पूर्ण
पूर्ण
WARNING(unit_address_vs_reg, check_unit_address_vs_reg, शून्य);

अटल व्योम check_property_name_अक्षरs(काष्ठा check *c, काष्ठा dt_info *dti,
				      काष्ठा node *node)
अणु
	काष्ठा property *prop;

	क्रम_each_property(node, prop) अणु
		पूर्णांक n = म_अखोज(prop->name, c->data);

		अगर (n < म_माप(prop->name))
			FAIL_PROP(c, dti, node, prop, "Bad character '%c' in property name",
				  prop->name[n]);
	पूर्ण
पूर्ण
ERROR(property_name_अक्षरs, check_property_name_अक्षरs, PROPNODECHARS);

अटल व्योम check_property_name_अक्षरs_strict(काष्ठा check *c,
					     काष्ठा dt_info *dti,
					     काष्ठा node *node)
अणु
	काष्ठा property *prop;

	क्रम_each_property(node, prop) अणु
		स्थिर अक्षर *name = prop->name;
		पूर्णांक n = म_अखोज(name, c->data);

		अगर (n == म_माप(prop->name))
			जारी;

		/* Certain names are whitelisted */
		अगर (streq(name, "device_type"))
			जारी;

		/*
		 * # is only allowed at the beginning of property names not counting
		 * the venकरोr prefix.
		 */
		अगर (name[n] == '#' && ((n == 0) || (name[n-1] == ','))) अणु
			name += n + 1;
			n = म_अखोज(name, c->data);
		पूर्ण
		अगर (n < म_माप(name))
			FAIL_PROP(c, dti, node, prop, "Character '%c' not recommended in property name",
				  name[n]);
	पूर्ण
पूर्ण
CHECK(property_name_अक्षरs_strict, check_property_name_अक्षरs_strict, PROPNODECHARSSTRICT);

#घोषणा DESCLABEL_FMT	"%s%s%s%s%s"
#घोषणा DESCLABEL_ARGS(node,prop,mark)		\
	((mark) ? "value of " : ""),		\
	((prop) ? "'" : ""), \
	((prop) ? (prop)->name : ""), \
	((prop) ? "' in " : ""), (node)->fullpath

अटल व्योम check_duplicate_label(काष्ठा check *c, काष्ठा dt_info *dti,
				  स्थिर अक्षर *label, काष्ठा node *node,
				  काष्ठा property *prop, काष्ठा marker *mark)
अणु
	काष्ठा node *dt = dti->dt;
	काष्ठा node *othernode = शून्य;
	काष्ठा property *otherprop = शून्य;
	काष्ठा marker *othermark = शून्य;

	othernode = get_node_by_label(dt, label);

	अगर (!othernode)
		otherprop = get_property_by_label(dt, label, &othernode);
	अगर (!othernode)
		othermark = get_marker_label(dt, label, &othernode,
					       &otherprop);

	अगर (!othernode)
		वापस;

	अगर ((othernode != node) || (otherprop != prop) || (othermark != mark))
		FAIL(c, dti, node, "Duplicate label '%s' on " DESCLABEL_FMT
		     " and " DESCLABEL_FMT,
		     label, DESCLABEL_ARGS(node, prop, mark),
		     DESCLABEL_ARGS(othernode, otherprop, othermark));
पूर्ण

अटल व्योम check_duplicate_label_node(काष्ठा check *c, काष्ठा dt_info *dti,
				       काष्ठा node *node)
अणु
	काष्ठा label *l;
	काष्ठा property *prop;

	क्रम_each_label(node->labels, l)
		check_duplicate_label(c, dti, l->label, node, शून्य, शून्य);

	क्रम_each_property(node, prop) अणु
		काष्ठा marker *m = prop->val.markers;

		क्रम_each_label(prop->labels, l)
			check_duplicate_label(c, dti, l->label, node, prop, शून्य);

		क्रम_each_marker_of_type(m, LABEL)
			check_duplicate_label(c, dti, m->ref, node, prop, m);
	पूर्ण
पूर्ण
ERROR(duplicate_label, check_duplicate_label_node, शून्य);

अटल cell_t check_phandle_prop(काष्ठा check *c, काष्ठा dt_info *dti,
				 काष्ठा node *node, स्थिर अक्षर *propname)
अणु
	काष्ठा node *root = dti->dt;
	काष्ठा property *prop;
	काष्ठा marker *m;
	cell_t phandle;

	prop = get_property(node, propname);
	अगर (!prop)
		वापस 0;

	अगर (prop->val.len != माप(cell_t)) अणु
		FAIL_PROP(c, dti, node, prop, "bad length (%d) %s property",
			  prop->val.len, prop->name);
		वापस 0;
	पूर्ण

	m = prop->val.markers;
	क्रम_each_marker_of_type(m, REF_PHANDLE) अणु
		निश्चित(m->offset == 0);
		अगर (node != get_node_by_ref(root, m->ref))
			/* "Set this node's phandle equal to some
			 * other node's phandle".  That's nonsensical
			 * by स्थिरruction. */ अणु
			FAIL(c, dti, node, "%s is a reference to another node",
			     prop->name);
		पूर्ण
		/* But setting this node's phandle equal to its own
		 * phandle is allowed - that means allocate a unique
		 * phandle क्रम this node, even अगर it's not otherwise
		 * referenced.  The value will be filled in later, so
		 * we treat it as having no phandle data क्रम now. */
		वापस 0;
	पूर्ण

	phandle = propval_cell(prop);

	अगर ((phandle == 0) || (phandle == -1)) अणु
		FAIL_PROP(c, dti, node, prop, "bad value (0x%x) in %s property",
		     phandle, prop->name);
		वापस 0;
	पूर्ण

	वापस phandle;
पूर्ण

अटल व्योम check_explicit_phandles(काष्ठा check *c, काष्ठा dt_info *dti,
				    काष्ठा node *node)
अणु
	काष्ठा node *root = dti->dt;
	काष्ठा node *other;
	cell_t phandle, linux_phandle;

	/* Nothing should have asचिन्हित phandles yet */
	निश्चित(!node->phandle);

	phandle = check_phandle_prop(c, dti, node, "phandle");

	linux_phandle = check_phandle_prop(c, dti, node, "linux,phandle");

	अगर (!phandle && !linux_phandle)
		/* No valid phandles; nothing further to check */
		वापस;

	अगर (linux_phandle && phandle && (phandle != linux_phandle))
		FAIL(c, dti, node, "mismatching 'phandle' and 'linux,phandle'"
		     " properties");

	अगर (linux_phandle && !phandle)
		phandle = linux_phandle;

	other = get_node_by_phandle(root, phandle);
	अगर (other && (other != node)) अणु
		FAIL(c, dti, node, "duplicated phandle 0x%x (seen before at %s)",
		     phandle, other->fullpath);
		वापस;
	पूर्ण

	node->phandle = phandle;
पूर्ण
ERROR(explicit_phandles, check_explicit_phandles, शून्य);

अटल व्योम check_name_properties(काष्ठा check *c, काष्ठा dt_info *dti,
				  काष्ठा node *node)
अणु
	काष्ठा property **pp, *prop = शून्य;

	क्रम (pp = &node->proplist; *pp; pp = &((*pp)->next))
		अगर (streq((*pp)->name, "name")) अणु
			prop = *pp;
			अवरोध;
		पूर्ण

	अगर (!prop)
		वापस; /* No name property, that's fine */

	अगर ((prop->val.len != node->basenamelen+1)
	    || (स_भेद(prop->val.val, node->name, node->basenamelen) != 0)) अणु
		FAIL(c, dti, node, "\"name\" property is incorrect (\"%s\" instead"
		     " of base node name)", prop->val.val);
	पूर्ण अन्यथा अणु
		/* The name property is correct, and thereक्रमe redundant.
		 * Delete it */
		*pp = prop->next;
		मुक्त(prop->name);
		data_मुक्त(prop->val);
		मुक्त(prop);
	पूर्ण
पूर्ण
ERROR_IF_NOT_STRING(name_is_string, "name");
ERROR(name_properties, check_name_properties, शून्य, &name_is_string);

/*
 * Reference fixup functions
 */

अटल व्योम fixup_phandle_references(काष्ठा check *c, काष्ठा dt_info *dti,
				     काष्ठा node *node)
अणु
	काष्ठा node *dt = dti->dt;
	काष्ठा property *prop;

	क्रम_each_property(node, prop) अणु
		काष्ठा marker *m = prop->val.markers;
		काष्ठा node *refnode;
		cell_t phandle;

		क्रम_each_marker_of_type(m, REF_PHANDLE) अणु
			निश्चित(m->offset + माप(cell_t) <= prop->val.len);

			refnode = get_node_by_ref(dt, m->ref);
			अगर (! refnode) अणु
				अगर (!(dti->dtsflags & DTSF_PLUGIN))
					FAIL(c, dti, node, "Reference to non-existent node or "
							"label \"%s\"\n", m->ref);
				अन्यथा /* mark the entry as unresolved */
					*((fdt32_t *)(prop->val.val + m->offset)) =
						cpu_to_fdt32(0xffffffff);
				जारी;
			पूर्ण

			phandle = get_node_phandle(dt, refnode);
			*((fdt32_t *)(prop->val.val + m->offset)) = cpu_to_fdt32(phandle);

			reference_node(refnode);
		पूर्ण
	पूर्ण
पूर्ण
ERROR(phandle_references, fixup_phandle_references, शून्य,
      &duplicate_node_names, &explicit_phandles);

अटल व्योम fixup_path_references(काष्ठा check *c, काष्ठा dt_info *dti,
				  काष्ठा node *node)
अणु
	काष्ठा node *dt = dti->dt;
	काष्ठा property *prop;

	क्रम_each_property(node, prop) अणु
		काष्ठा marker *m = prop->val.markers;
		काष्ठा node *refnode;
		अक्षर *path;

		क्रम_each_marker_of_type(m, REF_PATH) अणु
			निश्चित(m->offset <= prop->val.len);

			refnode = get_node_by_ref(dt, m->ref);
			अगर (!refnode) अणु
				FAIL(c, dti, node, "Reference to non-existent node or label \"%s\"\n",
				     m->ref);
				जारी;
			पूर्ण

			path = refnode->fullpath;
			prop->val = data_insert_at_marker(prop->val, m, path,
							  म_माप(path) + 1);

			reference_node(refnode);
		पूर्ण
	पूर्ण
पूर्ण
ERROR(path_references, fixup_path_references, शून्य, &duplicate_node_names);

अटल व्योम fixup_omit_unused_nodes(काष्ठा check *c, काष्ठा dt_info *dti,
				    काष्ठा node *node)
अणु
	अगर (generate_symbols && node->labels)
		वापस;
	अगर (node->omit_अगर_unused && !node->is_referenced)
		delete_node(node);
पूर्ण
ERROR(omit_unused_nodes, fixup_omit_unused_nodes, शून्य, &phandle_references, &path_references);

/*
 * Semantic checks
 */
WARNING_IF_NOT_CELL(address_cells_is_cell, "#address-cells");
WARNING_IF_NOT_CELL(size_cells_is_cell, "#size-cells");
WARNING_IF_NOT_CELL(पूर्णांकerrupt_cells_is_cell, "#interrupt-cells");

WARNING_IF_NOT_STRING(device_type_is_string, "device_type");
WARNING_IF_NOT_STRING(model_is_string, "model");
WARNING_IF_NOT_STRING(status_is_string, "status");
WARNING_IF_NOT_STRING(label_is_string, "label");

WARNING_IF_NOT_STRING_LIST(compatible_is_string_list, "compatible");

अटल व्योम check_names_is_string_list(काष्ठा check *c, काष्ठा dt_info *dti,
				       काष्ठा node *node)
अणु
	काष्ठा property *prop;

	क्रम_each_property(node, prop) अणु
		स्थिर अक्षर *s = म_खोजप(prop->name, '-');
		अगर (!s || !streq(s, "-names"))
			जारी;

		c->data = prop->name;
		check_is_string_list(c, dti, node);
	पूर्ण
पूर्ण
WARNING(names_is_string_list, check_names_is_string_list, शून्य);

अटल व्योम check_alias_paths(काष्ठा check *c, काष्ठा dt_info *dti,
				    काष्ठा node *node)
अणु
	काष्ठा property *prop;

	अगर (!streq(node->name, "aliases"))
		वापस;

	क्रम_each_property(node, prop) अणु
		अगर (streq(prop->name, "phandle")
		    || streq(prop->name, "linux,phandle")) अणु
			जारी;
		पूर्ण

		अगर (!prop->val.val || !get_node_by_path(dti->dt, prop->val.val)) अणु
			FAIL_PROP(c, dti, node, prop, "aliases property is not a valid node (%s)",
				  prop->val.val);
			जारी;
		पूर्ण
		अगर (म_अखोज(prop->name, LOWERCASE DIGITS "-") != म_माप(prop->name))
			FAIL(c, dti, node, "aliases property name must include only lowercase and '-'");
	पूर्ण
पूर्ण
WARNING(alias_paths, check_alias_paths, शून्य);

अटल व्योम fixup_addr_size_cells(काष्ठा check *c, काष्ठा dt_info *dti,
				  काष्ठा node *node)
अणु
	काष्ठा property *prop;

	node->addr_cells = -1;
	node->size_cells = -1;

	prop = get_property(node, "#address-cells");
	अगर (prop)
		node->addr_cells = propval_cell(prop);

	prop = get_property(node, "#size-cells");
	अगर (prop)
		node->size_cells = propval_cell(prop);
पूर्ण
WARNING(addr_size_cells, fixup_addr_size_cells, शून्य,
	&address_cells_is_cell, &size_cells_is_cell);

#घोषणा node_addr_cells(n) \
	(((n)->addr_cells == -1) ? 2 : (n)->addr_cells)
#घोषणा node_size_cells(n) \
	(((n)->size_cells == -1) ? 1 : (n)->size_cells)

अटल व्योम check_reg_क्रमmat(काष्ठा check *c, काष्ठा dt_info *dti,
			     काष्ठा node *node)
अणु
	काष्ठा property *prop;
	पूर्णांक addr_cells, size_cells, entrylen;

	prop = get_property(node, "reg");
	अगर (!prop)
		वापस; /* No "reg", that's fine */

	अगर (!node->parent) अणु
		FAIL(c, dti, node, "Root node has a \"reg\" property");
		वापस;
	पूर्ण

	अगर (prop->val.len == 0)
		FAIL_PROP(c, dti, node, prop, "property is empty");

	addr_cells = node_addr_cells(node->parent);
	size_cells = node_size_cells(node->parent);
	entrylen = (addr_cells + size_cells) * माप(cell_t);

	अगर (!entrylen || (prop->val.len % entrylen) != 0)
		FAIL_PROP(c, dti, node, prop, "property has invalid length (%d bytes) "
			  "(#address-cells == %d, #size-cells == %d)",
			  prop->val.len, addr_cells, size_cells);
पूर्ण
WARNING(reg_क्रमmat, check_reg_क्रमmat, शून्य, &addr_size_cells);

अटल व्योम check_ranges_क्रमmat(काष्ठा check *c, काष्ठा dt_info *dti,
				काष्ठा node *node)
अणु
	काष्ठा property *prop;
	पूर्णांक c_addr_cells, p_addr_cells, c_size_cells, p_size_cells, entrylen;
	स्थिर अक्षर *ranges = c->data;

	prop = get_property(node, ranges);
	अगर (!prop)
		वापस;

	अगर (!node->parent) अणु
		FAIL_PROP(c, dti, node, prop, "Root node has a \"%s\" property",
			  ranges);
		वापस;
	पूर्ण

	p_addr_cells = node_addr_cells(node->parent);
	p_size_cells = node_size_cells(node->parent);
	c_addr_cells = node_addr_cells(node);
	c_size_cells = node_size_cells(node);
	entrylen = (p_addr_cells + c_addr_cells + c_size_cells) * माप(cell_t);

	अगर (prop->val.len == 0) अणु
		अगर (p_addr_cells != c_addr_cells)
			FAIL_PROP(c, dti, node, prop, "empty \"%s\" property but its "
				  "#address-cells (%d) differs from %s (%d)",
				  ranges, c_addr_cells, node->parent->fullpath,
				  p_addr_cells);
		अगर (p_size_cells != c_size_cells)
			FAIL_PROP(c, dti, node, prop, "empty \"%s\" property but its "
				  "#size-cells (%d) differs from %s (%d)",
				  ranges, c_size_cells, node->parent->fullpath,
				  p_size_cells);
	पूर्ण अन्यथा अगर ((prop->val.len % entrylen) != 0) अणु
		FAIL_PROP(c, dti, node, prop, "\"%s\" property has invalid length (%d bytes) "
			  "(parent #address-cells == %d, child #address-cells == %d, "
			  "#size-cells == %d)", ranges, prop->val.len,
			  p_addr_cells, c_addr_cells, c_size_cells);
	पूर्ण
पूर्ण
WARNING(ranges_क्रमmat, check_ranges_क्रमmat, "ranges", &addr_size_cells);
WARNING(dma_ranges_क्रमmat, check_ranges_क्रमmat, "dma-ranges", &addr_size_cells);

अटल स्थिर काष्ठा bus_type pci_bus = अणु
	.name = "PCI",
पूर्ण;

अटल व्योम check_pci_bridge(काष्ठा check *c, काष्ठा dt_info *dti, काष्ठा node *node)
अणु
	काष्ठा property *prop;
	cell_t *cells;

	prop = get_property(node, "device_type");
	अगर (!prop || !streq(prop->val.val, "pci"))
		वापस;

	node->bus = &pci_bus;

	अगर (!strprefixeq(node->name, node->basenamelen, "pci") &&
	    !strprefixeq(node->name, node->basenamelen, "pcie"))
		FAIL(c, dti, node, "node name is not \"pci\" or \"pcie\"");

	prop = get_property(node, "ranges");
	अगर (!prop)
		FAIL(c, dti, node, "missing ranges for PCI bridge (or not a bridge)");

	अगर (node_addr_cells(node) != 3)
		FAIL(c, dti, node, "incorrect #address-cells for PCI bridge");
	अगर (node_size_cells(node) != 2)
		FAIL(c, dti, node, "incorrect #size-cells for PCI bridge");

	prop = get_property(node, "bus-range");
	अगर (!prop)
		वापस;

	अगर (prop->val.len != (माप(cell_t) * 2)) अणु
		FAIL_PROP(c, dti, node, prop, "value must be 2 cells");
		वापस;
	पूर्ण
	cells = (cell_t *)prop->val.val;
	अगर (fdt32_to_cpu(cells[0]) > fdt32_to_cpu(cells[1]))
		FAIL_PROP(c, dti, node, prop, "1st cell must be less than or equal to 2nd cell");
	अगर (fdt32_to_cpu(cells[1]) > 0xff)
		FAIL_PROP(c, dti, node, prop, "maximum bus number must be less than 256");
पूर्ण
WARNING(pci_bridge, check_pci_bridge, शून्य,
	&device_type_is_string, &addr_size_cells);

अटल व्योम check_pci_device_bus_num(काष्ठा check *c, काष्ठा dt_info *dti, काष्ठा node *node)
अणु
	काष्ठा property *prop;
	अचिन्हित पूर्णांक bus_num, min_bus, max_bus;
	cell_t *cells;

	अगर (!node->parent || (node->parent->bus != &pci_bus))
		वापस;

	prop = get_property(node, "reg");
	अगर (!prop)
		वापस;

	cells = (cell_t *)prop->val.val;
	bus_num = (fdt32_to_cpu(cells[0]) & 0x00ff0000) >> 16;

	prop = get_property(node->parent, "bus-range");
	अगर (!prop) अणु
		min_bus = max_bus = 0;
	पूर्ण अन्यथा अणु
		cells = (cell_t *)prop->val.val;
		min_bus = fdt32_to_cpu(cells[0]);
		max_bus = fdt32_to_cpu(cells[0]);
	पूर्ण
	अगर ((bus_num < min_bus) || (bus_num > max_bus))
		FAIL_PROP(c, dti, node, prop, "PCI bus number %d out of range, expected (%d - %d)",
			  bus_num, min_bus, max_bus);
पूर्ण
WARNING(pci_device_bus_num, check_pci_device_bus_num, शून्य, &reg_क्रमmat, &pci_bridge);

अटल व्योम check_pci_device_reg(काष्ठा check *c, काष्ठा dt_info *dti, काष्ठा node *node)
अणु
	काष्ठा property *prop;
	स्थिर अक्षर *unitname = get_unitname(node);
	अक्षर unit_addr[5];
	अचिन्हित पूर्णांक dev, func, reg;
	cell_t *cells;

	अगर (!node->parent || (node->parent->bus != &pci_bus))
		वापस;

	prop = get_property(node, "reg");
	अगर (!prop)
		वापस;

	cells = (cell_t *)prop->val.val;
	अगर (cells[1] || cells[2])
		FAIL_PROP(c, dti, node, prop, "PCI reg config space address cells 2 and 3 must be 0");

	reg = fdt32_to_cpu(cells[0]);
	dev = (reg & 0xf800) >> 11;
	func = (reg & 0x700) >> 8;

	अगर (reg & 0xff000000)
		FAIL_PROP(c, dti, node, prop, "PCI reg address is not configuration space");
	अगर (reg & 0x000000ff)
		FAIL_PROP(c, dti, node, prop, "PCI reg config space address register number must be 0");

	अगर (func == 0) अणु
		snम_लिखो(unit_addr, माप(unit_addr), "%x", dev);
		अगर (streq(unitname, unit_addr))
			वापस;
	पूर्ण

	snम_लिखो(unit_addr, माप(unit_addr), "%x,%x", dev, func);
	अगर (streq(unitname, unit_addr))
		वापस;

	FAIL(c, dti, node, "PCI unit address format error, expected \"%s\"",
	     unit_addr);
पूर्ण
WARNING(pci_device_reg, check_pci_device_reg, शून्य, &reg_क्रमmat, &pci_bridge);

अटल स्थिर काष्ठा bus_type simple_bus = अणु
	.name = "simple-bus",
पूर्ण;

अटल bool node_is_compatible(काष्ठा node *node, स्थिर अक्षर *compat)
अणु
	काष्ठा property *prop;
	स्थिर अक्षर *str, *end;

	prop = get_property(node, "compatible");
	अगर (!prop)
		वापस false;

	क्रम (str = prop->val.val, end = str + prop->val.len; str < end;
	     str += strnlen(str, end - str) + 1) अणु
		अगर (streq(str, compat))
			वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल व्योम check_simple_bus_bridge(काष्ठा check *c, काष्ठा dt_info *dti, काष्ठा node *node)
अणु
	अगर (node_is_compatible(node, "simple-bus"))
		node->bus = &simple_bus;
पूर्ण
WARNING(simple_bus_bridge, check_simple_bus_bridge, शून्य,
	&addr_size_cells, &compatible_is_string_list);

अटल व्योम check_simple_bus_reg(काष्ठा check *c, काष्ठा dt_info *dti, काष्ठा node *node)
अणु
	काष्ठा property *prop;
	स्थिर अक्षर *unitname = get_unitname(node);
	अक्षर unit_addr[17];
	अचिन्हित पूर्णांक size;
	uपूर्णांक64_t reg = 0;
	cell_t *cells = शून्य;

	अगर (!node->parent || (node->parent->bus != &simple_bus))
		वापस;

	prop = get_property(node, "reg");
	अगर (prop)
		cells = (cell_t *)prop->val.val;
	अन्यथा अणु
		prop = get_property(node, "ranges");
		अगर (prop && prop->val.len)
			/* skip of child address */
			cells = ((cell_t *)prop->val.val) + node_addr_cells(node);
	पूर्ण

	अगर (!cells) अणु
		अगर (node->parent->parent && !(node->bus == &simple_bus))
			FAIL(c, dti, node, "missing or empty reg/ranges property");
		वापस;
	पूर्ण

	size = node_addr_cells(node->parent);
	जबतक (size--)
		reg = (reg << 32) | fdt32_to_cpu(*(cells++));

	snम_लिखो(unit_addr, माप(unit_addr), "%"PRIx64, reg);
	अगर (!streq(unitname, unit_addr))
		FAIL(c, dti, node, "simple-bus unit address format error, expected \"%s\"",
		     unit_addr);
पूर्ण
WARNING(simple_bus_reg, check_simple_bus_reg, शून्य, &reg_क्रमmat, &simple_bus_bridge);

अटल स्थिर काष्ठा bus_type i2c_bus = अणु
	.name = "i2c-bus",
पूर्ण;

अटल व्योम check_i2c_bus_bridge(काष्ठा check *c, काष्ठा dt_info *dti, काष्ठा node *node)
अणु
	अगर (strprefixeq(node->name, node->basenamelen, "i2c-bus") ||
	    strprefixeq(node->name, node->basenamelen, "i2c-arb")) अणु
		node->bus = &i2c_bus;
	पूर्ण अन्यथा अगर (strprefixeq(node->name, node->basenamelen, "i2c")) अणु
		काष्ठा node *child;
		क्रम_each_child(node, child) अणु
			अगर (strprefixeq(child->name, node->basenamelen, "i2c-bus"))
				वापस;
		पूर्ण
		node->bus = &i2c_bus;
	पूर्ण अन्यथा
		वापस;

	अगर (!node->children)
		वापस;

	अगर (node_addr_cells(node) != 1)
		FAIL(c, dti, node, "incorrect #address-cells for I2C bus");
	अगर (node_size_cells(node) != 0)
		FAIL(c, dti, node, "incorrect #size-cells for I2C bus");

पूर्ण
WARNING(i2c_bus_bridge, check_i2c_bus_bridge, शून्य, &addr_size_cells);

#घोषणा I2C_OWN_SLAVE_ADDRESS	(1U << 30)
#घोषणा I2C_TEN_BIT_ADDRESS	(1U << 31)

अटल व्योम check_i2c_bus_reg(काष्ठा check *c, काष्ठा dt_info *dti, काष्ठा node *node)
अणु
	काष्ठा property *prop;
	स्थिर अक्षर *unitname = get_unitname(node);
	अक्षर unit_addr[17];
	uपूर्णांक32_t reg = 0;
	पूर्णांक len;
	cell_t *cells = शून्य;

	अगर (!node->parent || (node->parent->bus != &i2c_bus))
		वापस;

	prop = get_property(node, "reg");
	अगर (prop)
		cells = (cell_t *)prop->val.val;

	अगर (!cells) अणु
		FAIL(c, dti, node, "missing or empty reg property");
		वापस;
	पूर्ण

	reg = fdt32_to_cpu(*cells);
	/* Ignore I2C_OWN_SLAVE_ADDRESS */
	reg &= ~I2C_OWN_SLAVE_ADDRESS;
	snम_लिखो(unit_addr, माप(unit_addr), "%x", reg);
	अगर (!streq(unitname, unit_addr))
		FAIL(c, dti, node, "I2C bus unit address format error, expected \"%s\"",
		     unit_addr);

	क्रम (len = prop->val.len; len > 0; len -= 4) अणु
		reg = fdt32_to_cpu(*(cells++));
		/* Ignore I2C_OWN_SLAVE_ADDRESS */
		reg &= ~I2C_OWN_SLAVE_ADDRESS;

		अगर ((reg & I2C_TEN_BIT_ADDRESS) && ((reg & ~I2C_TEN_BIT_ADDRESS) > 0x3ff))
			FAIL_PROP(c, dti, node, prop, "I2C address must be less than 10-bits, got \"0x%x\"",
				  reg);
		अन्यथा अगर (reg > 0x7f)
			FAIL_PROP(c, dti, node, prop, "I2C address must be less than 7-bits, got \"0x%x\". Set I2C_TEN_BIT_ADDRESS for 10 bit addresses or fix the property",
				  reg);
	पूर्ण
पूर्ण
WARNING(i2c_bus_reg, check_i2c_bus_reg, शून्य, &reg_क्रमmat, &i2c_bus_bridge);

अटल स्थिर काष्ठा bus_type spi_bus = अणु
	.name = "spi-bus",
पूर्ण;

अटल व्योम check_spi_bus_bridge(काष्ठा check *c, काष्ठा dt_info *dti, काष्ठा node *node)
अणु
	पूर्णांक spi_addr_cells = 1;

	अगर (strprefixeq(node->name, node->basenamelen, "spi")) अणु
		node->bus = &spi_bus;
	पूर्ण अन्यथा अणु
		/* Try to detect SPI buses which करोn't have proper node name */
		काष्ठा node *child;

		अगर (node_addr_cells(node) != 1 || node_size_cells(node) != 0)
			वापस;

		क्रम_each_child(node, child) अणु
			काष्ठा property *prop;
			क्रम_each_property(child, prop) अणु
				अगर (strprefixeq(prop->name, 4, "spi-")) अणु
					node->bus = &spi_bus;
					अवरोध;
				पूर्ण
			पूर्ण
			अगर (node->bus == &spi_bus)
				अवरोध;
		पूर्ण

		अगर (node->bus == &spi_bus && get_property(node, "reg"))
			FAIL(c, dti, node, "node name for SPI buses should be 'spi'");
	पूर्ण
	अगर (node->bus != &spi_bus || !node->children)
		वापस;

	अगर (get_property(node, "spi-slave"))
		spi_addr_cells = 0;
	अगर (node_addr_cells(node) != spi_addr_cells)
		FAIL(c, dti, node, "incorrect #address-cells for SPI bus");
	अगर (node_size_cells(node) != 0)
		FAIL(c, dti, node, "incorrect #size-cells for SPI bus");

पूर्ण
WARNING(spi_bus_bridge, check_spi_bus_bridge, शून्य, &addr_size_cells);

अटल व्योम check_spi_bus_reg(काष्ठा check *c, काष्ठा dt_info *dti, काष्ठा node *node)
अणु
	काष्ठा property *prop;
	स्थिर अक्षर *unitname = get_unitname(node);
	अक्षर unit_addr[9];
	uपूर्णांक32_t reg = 0;
	cell_t *cells = शून्य;

	अगर (!node->parent || (node->parent->bus != &spi_bus))
		वापस;

	अगर (get_property(node->parent, "spi-slave"))
		वापस;

	prop = get_property(node, "reg");
	अगर (prop)
		cells = (cell_t *)prop->val.val;

	अगर (!cells) अणु
		FAIL(c, dti, node, "missing or empty reg property");
		वापस;
	पूर्ण

	reg = fdt32_to_cpu(*cells);
	snम_लिखो(unit_addr, माप(unit_addr), "%x", reg);
	अगर (!streq(unitname, unit_addr))
		FAIL(c, dti, node, "SPI bus unit address format error, expected \"%s\"",
		     unit_addr);
पूर्ण
WARNING(spi_bus_reg, check_spi_bus_reg, शून्य, &reg_क्रमmat, &spi_bus_bridge);

अटल व्योम check_unit_address_क्रमmat(काष्ठा check *c, काष्ठा dt_info *dti,
				      काष्ठा node *node)
अणु
	स्थिर अक्षर *unitname = get_unitname(node);

	अगर (node->parent && node->parent->bus)
		वापस;

	अगर (!unitname[0])
		वापस;

	अगर (!म_भेदन(unitname, "0x", 2)) अणु
		FAIL(c, dti, node, "unit name should not have leading \"0x\"");
		/* skip over 0x क्रम next test */
		unitname += 2;
	पूर्ण
	अगर (unitname[0] == '0' && है_षष्ठादशक(unitname[1]))
		FAIL(c, dti, node, "unit name should not have leading 0s");
पूर्ण
WARNING(unit_address_क्रमmat, check_unit_address_क्रमmat, शून्य,
	&node_name_क्रमmat, &pci_bridge, &simple_bus_bridge);

/*
 * Style checks
 */
अटल व्योम check_aव्योम_शेष_addr_size(काष्ठा check *c, काष्ठा dt_info *dti,
					  काष्ठा node *node)
अणु
	काष्ठा property *reg, *ranges;

	अगर (!node->parent)
		वापस; /* Ignore root node */

	reg = get_property(node, "reg");
	ranges = get_property(node, "ranges");

	अगर (!reg && !ranges)
		वापस;

	अगर (node->parent->addr_cells == -1)
		FAIL(c, dti, node, "Relying on default #address-cells value");

	अगर (node->parent->size_cells == -1)
		FAIL(c, dti, node, "Relying on default #size-cells value");
पूर्ण
WARNING(aव्योम_शेष_addr_size, check_aव्योम_शेष_addr_size, शून्य,
	&addr_size_cells);

अटल व्योम check_aव्योम_unnecessary_addr_size(काष्ठा check *c, काष्ठा dt_info *dti,
					      काष्ठा node *node)
अणु
	काष्ठा property *prop;
	काष्ठा node *child;
	bool has_reg = false;

	अगर (!node->parent || node->addr_cells < 0 || node->size_cells < 0)
		वापस;

	अगर (get_property(node, "ranges") || !node->children)
		वापस;

	क्रम_each_child(node, child) अणु
		prop = get_property(child, "reg");
		अगर (prop)
			has_reg = true;
	पूर्ण

	अगर (!has_reg)
		FAIL(c, dti, node, "unnecessary #address-cells/#size-cells without \"ranges\" or child \"reg\" property");
पूर्ण
WARNING(aव्योम_unnecessary_addr_size, check_aव्योम_unnecessary_addr_size, शून्य, &aव्योम_शेष_addr_size);

अटल bool node_is_disabled(काष्ठा node *node)
अणु
	काष्ठा property *prop;

	prop = get_property(node, "status");
	अगर (prop) अणु
		अक्षर *str = prop->val.val;
		अगर (streq("disabled", str))
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल व्योम check_unique_unit_address_common(काष्ठा check *c,
						काष्ठा dt_info *dti,
						काष्ठा node *node,
						bool disable_check)
अणु
	काष्ठा node *childa;

	अगर (node->addr_cells < 0 || node->size_cells < 0)
		वापस;

	अगर (!node->children)
		वापस;

	क्रम_each_child(node, childa) अणु
		काष्ठा node *childb;
		स्थिर अक्षर *addr_a = get_unitname(childa);

		अगर (!म_माप(addr_a))
			जारी;

		अगर (disable_check && node_is_disabled(childa))
			जारी;

		क्रम_each_child(node, childb) अणु
			स्थिर अक्षर *addr_b = get_unitname(childb);
			अगर (childa == childb)
				अवरोध;

			अगर (disable_check && node_is_disabled(childb))
				जारी;

			अगर (streq(addr_a, addr_b))
				FAIL(c, dti, childb, "duplicate unit-address (also used in node %s)", childa->fullpath);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम check_unique_unit_address(काष्ठा check *c, काष्ठा dt_info *dti,
					      काष्ठा node *node)
अणु
	check_unique_unit_address_common(c, dti, node, false);
पूर्ण
WARNING(unique_unit_address, check_unique_unit_address, शून्य, &aव्योम_शेष_addr_size);

अटल व्योम check_unique_unit_address_अगर_enabled(काष्ठा check *c, काष्ठा dt_info *dti,
					      काष्ठा node *node)
अणु
	check_unique_unit_address_common(c, dti, node, true);
पूर्ण
CHECK_ENTRY(unique_unit_address_अगर_enabled, check_unique_unit_address_अगर_enabled,
	    शून्य, false, false, &aव्योम_शेष_addr_size);

अटल व्योम check_obsolete_chosen_पूर्णांकerrupt_controller(काष्ठा check *c,
						       काष्ठा dt_info *dti,
						       काष्ठा node *node)
अणु
	काष्ठा node *dt = dti->dt;
	काष्ठा node *chosen;
	काष्ठा property *prop;

	अगर (node != dt)
		वापस;


	chosen = get_node_by_path(dt, "/chosen");
	अगर (!chosen)
		वापस;

	prop = get_property(chosen, "interrupt-controller");
	अगर (prop)
		FAIL_PROP(c, dti, node, prop,
			  "/chosen has obsolete \"interrupt-controller\" property");
पूर्ण
WARNING(obsolete_chosen_पूर्णांकerrupt_controller,
	check_obsolete_chosen_पूर्णांकerrupt_controller, शून्य);

अटल व्योम check_chosen_node_is_root(काष्ठा check *c, काष्ठा dt_info *dti,
				      काष्ठा node *node)
अणु
	अगर (!streq(node->name, "chosen"))
		वापस;

	अगर (node->parent != dti->dt)
		FAIL(c, dti, node, "chosen node must be at root node");
पूर्ण
WARNING(chosen_node_is_root, check_chosen_node_is_root, शून्य);

अटल व्योम check_chosen_node_bootargs(काष्ठा check *c, काष्ठा dt_info *dti,
				       काष्ठा node *node)
अणु
	काष्ठा property *prop;

	अगर (!streq(node->name, "chosen"))
		वापस;

	prop = get_property(node, "bootargs");
	अगर (!prop)
		वापस;

	c->data = prop->name;
	check_is_string(c, dti, node);
पूर्ण
WARNING(chosen_node_bootargs, check_chosen_node_bootargs, शून्य);

अटल व्योम check_chosen_node_मानक_निकास_path(काष्ठा check *c, काष्ठा dt_info *dti,
					  काष्ठा node *node)
अणु
	काष्ठा property *prop;

	अगर (!streq(node->name, "chosen"))
		वापस;

	prop = get_property(node, "stdout-path");
	अगर (!prop) अणु
		prop = get_property(node, "linux,stdout-path");
		अगर (!prop)
			वापस;
		FAIL_PROP(c, dti, node, prop, "Use 'stdout-path' instead");
	पूर्ण

	c->data = prop->name;
	check_is_string(c, dti, node);
पूर्ण
WARNING(chosen_node_मानक_निकास_path, check_chosen_node_मानक_निकास_path, शून्य);

काष्ठा provider अणु
	स्थिर अक्षर *prop_name;
	स्थिर अक्षर *cell_name;
	bool optional;
पूर्ण;

अटल व्योम check_property_phandle_args(काष्ठा check *c,
					  काष्ठा dt_info *dti,
				          काष्ठा node *node,
				          काष्ठा property *prop,
				          स्थिर काष्ठा provider *provider)
अणु
	काष्ठा node *root = dti->dt;
	पूर्णांक cell, cellsize = 0;

	अगर (prop->val.len % माप(cell_t)) अणु
		FAIL_PROP(c, dti, node, prop,
			  "property size (%d) is invalid, expected multiple of %zu",
			  prop->val.len, माप(cell_t));
		वापस;
	पूर्ण

	क्रम (cell = 0; cell < prop->val.len / माप(cell_t); cell += cellsize + 1) अणु
		काष्ठा node *provider_node;
		काष्ठा property *cellprop;
		पूर्णांक phandle;

		phandle = propval_cell_n(prop, cell);
		/*
		 * Some bindings use a cell value 0 or -1 to skip over optional
		 * entries when each index position has a specअगरic definition.
		 */
		अगर (phandle == 0 || phandle == -1) अणु
			/* Give up अगर this is an overlay with बाह्यal references */
			अगर (dti->dtsflags & DTSF_PLUGIN)
				अवरोध;

			cellsize = 0;
			जारी;
		पूर्ण

		/* If we have markers, verअगरy the current cell is a phandle */
		अगर (prop->val.markers) अणु
			काष्ठा marker *m = prop->val.markers;
			क्रम_each_marker_of_type(m, REF_PHANDLE) अणु
				अगर (m->offset == (cell * माप(cell_t)))
					अवरोध;
			पूर्ण
			अगर (!m)
				FAIL_PROP(c, dti, node, prop,
					  "cell %d is not a phandle reference",
					  cell);
		पूर्ण

		provider_node = get_node_by_phandle(root, phandle);
		अगर (!provider_node) अणु
			FAIL_PROP(c, dti, node, prop,
				  "Could not get phandle node for (cell %d)",
				  cell);
			अवरोध;
		पूर्ण

		cellprop = get_property(provider_node, provider->cell_name);
		अगर (cellprop) अणु
			cellsize = propval_cell(cellprop);
		पूर्ण अन्यथा अगर (provider->optional) अणु
			cellsize = 0;
		पूर्ण अन्यथा अणु
			FAIL(c, dti, node, "Missing property '%s' in node %s or bad phandle (referred from %s[%d])",
			     provider->cell_name,
			     provider_node->fullpath,
			     prop->name, cell);
			अवरोध;
		पूर्ण

		अगर (prop->val.len < ((cell + cellsize + 1) * माप(cell_t))) अणु
			FAIL_PROP(c, dti, node, prop,
				  "property size (%d) too small for cell size %d",
				  prop->val.len, cellsize);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम check_provider_cells_property(काष्ठा check *c,
					  काष्ठा dt_info *dti,
				          काष्ठा node *node)
अणु
	काष्ठा provider *provider = c->data;
	काष्ठा property *prop;

	prop = get_property(node, provider->prop_name);
	अगर (!prop)
		वापस;

	check_property_phandle_args(c, dti, node, prop, provider);
पूर्ण
#घोषणा WARNING_PROPERTY_PHANDLE_CELLS(nm, propname, cells_name, ...) \
	अटल काष्ठा provider nm##_provider = अणु (propname), (cells_name), __VA_ARGS__ पूर्ण; \
	WARNING(nm##_property, check_provider_cells_property, &nm##_provider, &phandle_references);

WARNING_PROPERTY_PHANDLE_CELLS(घड़ीs, "clocks", "#clock-cells");
WARNING_PROPERTY_PHANDLE_CELLS(cooling_device, "cooling-device", "#cooling-cells");
WARNING_PROPERTY_PHANDLE_CELLS(dmas, "dmas", "#dma-cells");
WARNING_PROPERTY_PHANDLE_CELLS(hwlocks, "hwlocks", "#hwlock-cells");
WARNING_PROPERTY_PHANDLE_CELLS(पूर्णांकerrupts_extended, "interrupts-extended", "#interrupt-cells");
WARNING_PROPERTY_PHANDLE_CELLS(io_channels, "io-channels", "#io-channel-cells");
WARNING_PROPERTY_PHANDLE_CELLS(iommus, "iommus", "#iommu-cells");
WARNING_PROPERTY_PHANDLE_CELLS(mboxes, "mboxes", "#mbox-cells");
WARNING_PROPERTY_PHANDLE_CELLS(msi_parent, "msi-parent", "#msi-cells", true);
WARNING_PROPERTY_PHANDLE_CELLS(mux_controls, "mux-controls", "#mux-control-cells");
WARNING_PROPERTY_PHANDLE_CELLS(phys, "phys", "#phy-cells");
WARNING_PROPERTY_PHANDLE_CELLS(घातer_करोमुख्यs, "power-domains", "#power-domain-cells");
WARNING_PROPERTY_PHANDLE_CELLS(pwms, "pwms", "#pwm-cells");
WARNING_PROPERTY_PHANDLE_CELLS(resets, "resets", "#reset-cells");
WARNING_PROPERTY_PHANDLE_CELLS(sound_dai, "sound-dai", "#sound-dai-cells");
WARNING_PROPERTY_PHANDLE_CELLS(thermal_sensors, "thermal-sensors", "#thermal-sensor-cells");

अटल bool prop_is_gpio(काष्ठा property *prop)
अणु
	अक्षर *str;

	/*
	 * *-gpios and *-gpio can appear in property names,
	 * so skip over any false matches (only one known ATM)
	 */
	अगर (म_माला(prop->name, "nr-gpio"))
		वापस false;

	str = म_खोजप(prop->name, '-');
	अगर (str)
		str++;
	अन्यथा
		str = prop->name;
	अगर (!(streq(str, "gpios") || streq(str, "gpio")))
		वापस false;

	वापस true;
पूर्ण

अटल व्योम check_gpios_property(काष्ठा check *c,
					  काष्ठा dt_info *dti,
				          काष्ठा node *node)
अणु
	काष्ठा property *prop;

	/* Skip GPIO hog nodes which have 'gpios' property */
	अगर (get_property(node, "gpio-hog"))
		वापस;

	क्रम_each_property(node, prop) अणु
		काष्ठा provider provider;

		अगर (!prop_is_gpio(prop))
			जारी;

		provider.prop_name = prop->name;
		provider.cell_name = "#gpio-cells";
		provider.optional = false;
		check_property_phandle_args(c, dti, node, prop, &provider);
	पूर्ण

पूर्ण
WARNING(gpios_property, check_gpios_property, शून्य, &phandle_references);

अटल व्योम check_deprecated_gpio_property(काष्ठा check *c,
					   काष्ठा dt_info *dti,
				           काष्ठा node *node)
अणु
	काष्ठा property *prop;

	क्रम_each_property(node, prop) अणु
		अक्षर *str;

		अगर (!prop_is_gpio(prop))
			जारी;

		str = म_माला(prop->name, "gpio");
		अगर (!streq(str, "gpio"))
			जारी;

		FAIL_PROP(c, dti, node, prop,
			  "'[*-]gpio' is deprecated, use '[*-]gpios' instead");
	पूर्ण

पूर्ण
CHECK(deprecated_gpio_property, check_deprecated_gpio_property, शून्य);

अटल bool node_is_पूर्णांकerrupt_provider(काष्ठा node *node)
अणु
	काष्ठा property *prop;

	prop = get_property(node, "interrupt-controller");
	अगर (prop)
		वापस true;

	prop = get_property(node, "interrupt-map");
	अगर (prop)
		वापस true;

	वापस false;
पूर्ण

अटल व्योम check_पूर्णांकerrupt_provider(काष्ठा check *c,
				     काष्ठा dt_info *dti,
				     काष्ठा node *node)
अणु
	काष्ठा property *prop;

	अगर (!node_is_पूर्णांकerrupt_provider(node))
		वापस;

	prop = get_property(node, "#interrupt-cells");
	अगर (!prop)
		FAIL(c, dti, node,
		     "Missing #interrupt-cells in interrupt provider");

	prop = get_property(node, "#address-cells");
	अगर (!prop)
		FAIL(c, dti, node,
		     "Missing #address-cells in interrupt provider");
पूर्ण
WARNING(पूर्णांकerrupt_provider, check_पूर्णांकerrupt_provider, शून्य);

अटल व्योम check_पूर्णांकerrupts_property(काष्ठा check *c,
				      काष्ठा dt_info *dti,
				      काष्ठा node *node)
अणु
	काष्ठा node *root = dti->dt;
	काष्ठा node *irq_node = शून्य, *parent = node;
	काष्ठा property *irq_prop, *prop = शून्य;
	पूर्णांक irq_cells, phandle;

	irq_prop = get_property(node, "interrupts");
	अगर (!irq_prop)
		वापस;

	अगर (irq_prop->val.len % माप(cell_t))
		FAIL_PROP(c, dti, node, irq_prop, "size (%d) is invalid, expected multiple of %zu",
		     irq_prop->val.len, माप(cell_t));

	जबतक (parent && !prop) अणु
		अगर (parent != node && node_is_पूर्णांकerrupt_provider(parent)) अणु
			irq_node = parent;
			अवरोध;
		पूर्ण

		prop = get_property(parent, "interrupt-parent");
		अगर (prop) अणु
			phandle = propval_cell(prop);
			अगर ((phandle == 0) || (phandle == -1)) अणु
				/* Give up अगर this is an overlay with
				 * बाह्यal references */
				अगर (dti->dtsflags & DTSF_PLUGIN)
					वापस;
				FAIL_PROP(c, dti, parent, prop, "Invalid phandle");
				जारी;
			पूर्ण

			irq_node = get_node_by_phandle(root, phandle);
			अगर (!irq_node) अणु
				FAIL_PROP(c, dti, parent, prop, "Bad phandle");
				वापस;
			पूर्ण
			अगर (!node_is_पूर्णांकerrupt_provider(irq_node))
				FAIL(c, dti, irq_node,
				     "Missing interrupt-controller or interrupt-map property");

			अवरोध;
		पूर्ण

		parent = parent->parent;
	पूर्ण

	अगर (!irq_node) अणु
		FAIL(c, dti, node, "Missing interrupt-parent");
		वापस;
	पूर्ण

	prop = get_property(irq_node, "#interrupt-cells");
	अगर (!prop) अणु
		/* We warn about that alपढ़ोy in another test. */
		वापस;
	पूर्ण

	irq_cells = propval_cell(prop);
	अगर (irq_prop->val.len % (irq_cells * माप(cell_t))) अणु
		FAIL_PROP(c, dti, node, prop,
			  "size is (%d), expected multiple of %d",
			  irq_prop->val.len, (पूर्णांक)(irq_cells * माप(cell_t)));
	पूर्ण
पूर्ण
WARNING(पूर्णांकerrupts_property, check_पूर्णांकerrupts_property, &phandle_references);

अटल स्थिर काष्ठा bus_type graph_port_bus = अणु
	.name = "graph-port",
पूर्ण;

अटल स्थिर काष्ठा bus_type graph_ports_bus = अणु
	.name = "graph-ports",
पूर्ण;

अटल व्योम check_graph_nodes(काष्ठा check *c, काष्ठा dt_info *dti,
			      काष्ठा node *node)
अणु
	काष्ठा node *child;

	क्रम_each_child(node, child) अणु
		अगर (!(strprefixeq(child->name, child->basenamelen, "endpoint") ||
		      get_property(child, "remote-endpoint")))
			जारी;

		node->bus = &graph_port_bus;

		/* The parent of 'port' nodes can be either 'ports' or a device */
		अगर (!node->parent->bus &&
		    (streq(node->parent->name, "ports") || get_property(node, "reg")))
			node->parent->bus = &graph_ports_bus;

		अवरोध;
	पूर्ण

पूर्ण
WARNING(graph_nodes, check_graph_nodes, शून्य);

अटल व्योम check_graph_child_address(काष्ठा check *c, काष्ठा dt_info *dti,
				      काष्ठा node *node)
अणु
	पूर्णांक cnt = 0;
	काष्ठा node *child;

	अगर (node->bus != &graph_ports_bus && node->bus != &graph_port_bus)
		वापस;

	क्रम_each_child(node, child) अणु
		काष्ठा property *prop = get_property(child, "reg");

		/* No error अगर we have any non-zero unit address */
		अगर (prop && propval_cell(prop) != 0)
			वापस;

		cnt++;
	पूर्ण

	अगर (cnt == 1 && node->addr_cells != -1)
		FAIL(c, dti, node, "graph node has single child node '%s', #address-cells/#size-cells are not necessary",
		     node->children->name);
पूर्ण
WARNING(graph_child_address, check_graph_child_address, शून्य, &graph_nodes);

अटल व्योम check_graph_reg(काष्ठा check *c, काष्ठा dt_info *dti,
			    काष्ठा node *node)
अणु
	अक्षर unit_addr[9];
	स्थिर अक्षर *unitname = get_unitname(node);
	काष्ठा property *prop;

	prop = get_property(node, "reg");
	अगर (!prop || !unitname)
		वापस;

	अगर (!(prop->val.val && prop->val.len == माप(cell_t))) अणु
		FAIL(c, dti, node, "graph node malformed 'reg' property");
		वापस;
	पूर्ण

	snम_लिखो(unit_addr, माप(unit_addr), "%x", propval_cell(prop));
	अगर (!streq(unitname, unit_addr))
		FAIL(c, dti, node, "graph node unit address error, expected \"%s\"",
		     unit_addr);

	अगर (node->parent->addr_cells != 1)
		FAIL_PROP(c, dti, node, get_property(node, "#address-cells"),
			  "graph node '#address-cells' is %d, must be 1",
			  node->parent->addr_cells);
	अगर (node->parent->size_cells != 0)
		FAIL_PROP(c, dti, node, get_property(node, "#size-cells"),
			  "graph node '#size-cells' is %d, must be 0",
			  node->parent->size_cells);
पूर्ण

अटल व्योम check_graph_port(काष्ठा check *c, काष्ठा dt_info *dti,
			     काष्ठा node *node)
अणु
	अगर (node->bus != &graph_port_bus)
		वापस;

	अगर (!strprefixeq(node->name, node->basenamelen, "port"))
		FAIL(c, dti, node, "graph port node name should be 'port'");

	check_graph_reg(c, dti, node);
पूर्ण
WARNING(graph_port, check_graph_port, शून्य, &graph_nodes);

अटल काष्ठा node *get_remote_endpoपूर्णांक(काष्ठा check *c, काष्ठा dt_info *dti,
					काष्ठा node *endpoपूर्णांक)
अणु
	पूर्णांक phandle;
	काष्ठा node *node;
	काष्ठा property *prop;

	prop = get_property(endpoपूर्णांक, "remote-endpoint");
	अगर (!prop)
		वापस शून्य;

	phandle = propval_cell(prop);
	/* Give up अगर this is an overlay with बाह्यal references */
	अगर (phandle == 0 || phandle == -1)
		वापस शून्य;

	node = get_node_by_phandle(dti->dt, phandle);
	अगर (!node)
		FAIL_PROP(c, dti, endpoपूर्णांक, prop, "graph phandle is not valid");

	वापस node;
पूर्ण

अटल व्योम check_graph_endpoपूर्णांक(काष्ठा check *c, काष्ठा dt_info *dti,
				 काष्ठा node *node)
अणु
	काष्ठा node *remote_node;

	अगर (!node->parent || node->parent->bus != &graph_port_bus)
		वापस;

	अगर (!strprefixeq(node->name, node->basenamelen, "endpoint"))
		FAIL(c, dti, node, "graph endpoint node name should be 'endpoint'");

	check_graph_reg(c, dti, node);

	remote_node = get_remote_endpoपूर्णांक(c, dti, node);
	अगर (!remote_node)
		वापस;

	अगर (get_remote_endpoपूर्णांक(c, dti, remote_node) != node)
		FAIL(c, dti, node, "graph connection to node '%s' is not bidirectional",
		     remote_node->fullpath);
पूर्ण
WARNING(graph_endpoपूर्णांक, check_graph_endpoपूर्णांक, शून्य, &graph_nodes);

अटल काष्ठा check *check_table[] = अणु
	&duplicate_node_names, &duplicate_property_names,
	&node_name_अक्षरs, &node_name_क्रमmat, &property_name_अक्षरs,
	&name_is_string, &name_properties,

	&duplicate_label,

	&explicit_phandles,
	&phandle_references, &path_references,
	&omit_unused_nodes,

	&address_cells_is_cell, &size_cells_is_cell, &पूर्णांकerrupt_cells_is_cell,
	&device_type_is_string, &model_is_string, &status_is_string,
	&label_is_string,

	&compatible_is_string_list, &names_is_string_list,

	&property_name_अक्षरs_strict,
	&node_name_अक्षरs_strict,

	&addr_size_cells, &reg_क्रमmat, &ranges_क्रमmat, &dma_ranges_क्रमmat,

	&unit_address_vs_reg,
	&unit_address_क्रमmat,

	&pci_bridge,
	&pci_device_reg,
	&pci_device_bus_num,

	&simple_bus_bridge,
	&simple_bus_reg,

	&i2c_bus_bridge,
	&i2c_bus_reg,

	&spi_bus_bridge,
	&spi_bus_reg,

	&aव्योम_शेष_addr_size,
	&aव्योम_unnecessary_addr_size,
	&unique_unit_address,
	&unique_unit_address_अगर_enabled,
	&obsolete_chosen_पूर्णांकerrupt_controller,
	&chosen_node_is_root, &chosen_node_bootargs, &chosen_node_मानक_निकास_path,

	&घड़ीs_property,
	&cooling_device_property,
	&dmas_property,
	&hwlocks_property,
	&पूर्णांकerrupts_extended_property,
	&io_channels_property,
	&iommus_property,
	&mboxes_property,
	&msi_parent_property,
	&mux_controls_property,
	&phys_property,
	&घातer_करोमुख्यs_property,
	&pwms_property,
	&resets_property,
	&sound_dai_property,
	&thermal_sensors_property,

	&deprecated_gpio_property,
	&gpios_property,
	&पूर्णांकerrupts_property,
	&पूर्णांकerrupt_provider,

	&alias_paths,

	&graph_nodes, &graph_child_address, &graph_port, &graph_endpoपूर्णांक,

	&always_fail,
पूर्ण;

अटल व्योम enable_warning_error(काष्ठा check *c, bool warn, bool error)
अणु
	पूर्णांक i;

	/* Raising level, also उठाओ it क्रम prereqs */
	अगर ((warn && !c->warn) || (error && !c->error))
		क्रम (i = 0; i < c->num_prereqs; i++)
			enable_warning_error(c->prereq[i], warn, error);

	c->warn = c->warn || warn;
	c->error = c->error || error;
पूर्ण

अटल व्योम disable_warning_error(काष्ठा check *c, bool warn, bool error)
अणु
	पूर्णांक i;

	/* Lowering level, also lower it क्रम things this is the prereq
	 * क्रम */
	अगर ((warn && c->warn) || (error && c->error)) अणु
		क्रम (i = 0; i < ARRAY_SIZE(check_table); i++) अणु
			काष्ठा check *cc = check_table[i];
			पूर्णांक j;

			क्रम (j = 0; j < cc->num_prereqs; j++)
				अगर (cc->prereq[j] == c)
					disable_warning_error(cc, warn, error);
		पूर्ण
	पूर्ण

	c->warn = c->warn && !warn;
	c->error = c->error && !error;
पूर्ण

व्योम parse_checks_option(bool warn, bool error, स्थिर अक्षर *arg)
अणु
	पूर्णांक i;
	स्थिर अक्षर *name = arg;
	bool enable = true;

	अगर ((म_भेदन(arg, "no-", 3) == 0)
	    || (म_भेदन(arg, "no_", 3) == 0)) अणु
		name = arg + 3;
		enable = false;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(check_table); i++) अणु
		काष्ठा check *c = check_table[i];

		अगर (streq(c->name, name)) अणु
			अगर (enable)
				enable_warning_error(c, warn, error);
			अन्यथा
				disable_warning_error(c, warn, error);
			वापस;
		पूर्ण
	पूर्ण

	die("Unrecognized check name \"%s\"\n", name);
पूर्ण

व्योम process_checks(bool क्रमce, काष्ठा dt_info *dti)
अणु
	पूर्णांक i;
	पूर्णांक error = 0;

	क्रम (i = 0; i < ARRAY_SIZE(check_table); i++) अणु
		काष्ठा check *c = check_table[i];

		अगर (c->warn || c->error)
			error = error || run_check(c, dti);
	पूर्ण

	अगर (error) अणु
		अगर (!क्रमce) अणु
			ख_लिखो(मानक_त्रुटि, "ERROR: Input tree has errors, aborting "
				"(use -f to force output)\n");
			निकास(2);
		पूर्ण अन्यथा अगर (quiet < 3) अणु
			ख_लिखो(मानक_त्रुटि, "Warning: Input tree has errors, "
				"output forced\n");
		पूर्ण
	पूर्ण
पूर्ण
