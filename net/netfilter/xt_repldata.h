<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Today's hack: quantum tunneling in काष्ठाs
 *
 * 'entries' and 'term' are never anywhere referenced by word in code. In fact,
 * they serve as the hanging-off data accessed through repl.data[].
 */

/* tbl has the following काष्ठाure equivalent, but is C99 compliant:
 * काष्ठा अणु
 *	काष्ठा type##_replace repl;
 *	काष्ठा type##_standard entries[nhooks];
 *	काष्ठा type##_error term;
 * पूर्ण *tbl;
 */

#घोषणा xt_alloc_initial_table(type, typ2) (अणु \
	अचिन्हित पूर्णांक hook_mask = info->valid_hooks; \
	अचिन्हित पूर्णांक nhooks = hweight32(hook_mask); \
	अचिन्हित पूर्णांक bytes = 0, hooknum = 0, i = 0; \
	काष्ठा अणु \
		काष्ठा type##_replace repl; \
		काष्ठा type##_standard entries[]; \
	पूर्ण *tbl; \
	काष्ठा type##_error *term; \
	माप_प्रकार term_offset = (दुरत्व(typeof(*tbl), entries[nhooks]) + \
		__alignof__(*term) - 1) & ~(__alignof__(*term) - 1); \
	tbl = kzalloc(term_offset + माप(*term), GFP_KERNEL); \
	अगर (tbl == शून्य) \
		वापस शून्य; \
	term = (काष्ठा type##_error *)&(((अक्षर *)tbl)[term_offset]); \
	म_नकलन(tbl->repl.name, info->name, माप(tbl->repl.name)); \
	*term = (काष्ठा type##_error)typ2##_ERROR_INIT;  \
	tbl->repl.valid_hooks = hook_mask; \
	tbl->repl.num_entries = nhooks + 1; \
	tbl->repl.size = nhooks * माप(काष्ठा type##_standard) + \
			 माप(काष्ठा type##_error); \
	क्रम (; hook_mask != 0; hook_mask >>= 1, ++hooknum) अणु \
		अगर (!(hook_mask & 1)) \
			जारी; \
		tbl->repl.hook_entry[hooknum] = bytes; \
		tbl->repl.underflow[hooknum]  = bytes; \
		tbl->entries[i++] = (काष्ठा type##_standard) \
			typ2##_STANDARD_INIT(NF_ACCEPT); \
		bytes += माप(काष्ठा type##_standard); \
	पूर्ण \
	tbl; \
पूर्ण)
