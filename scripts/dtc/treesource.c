<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * (C) Copyright David Gibson <dwg@au1.ibm.com>, IBM Corporation.  2005.
 */

#समावेश "dtc.h"
#समावेश "srcpos.h"

बाह्य खाता *yyin;
बाह्य पूर्णांक yyparse(व्योम);
बाह्य YYLTYPE yylloc;

काष्ठा dt_info *parser_output;
bool treesource_error;

काष्ठा dt_info *dt_from_source(स्थिर अक्षर *fname)
अणु
	parser_output = शून्य;
	treesource_error = false;

	srcfile_push(fname);
	yyin = current_srcfile->f;
	yylloc.file = current_srcfile;

	अगर (yyparse() != 0)
		die("Unable to parse input tree\n");

	अगर (treesource_error)
		die("Syntax error parsing input tree\n");

	वापस parser_output;
पूर्ण

अटल व्योम ग_लिखो_prefix(खाता *f, पूर्णांक level)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < level; i++)
		ख_अक्षर_दो('\t', f);
पूर्ण

अटल bool isstring(अक्षर c)
अणु
	वापस (है_छाप((अचिन्हित अक्षर)c)
		|| (c == '\0')
		|| म_अक्षर("\a\b\t\n\v\f\r", c));
पूर्ण

अटल व्योम ग_लिखो_propval_string(खाता *f, स्थिर अक्षर *s, माप_प्रकार len)
अणु
	स्थिर अक्षर *end = s + len - 1;

	अगर (!len)
		वापस;

	निश्चित(*end == '\0');

	ख_लिखो(f, "\"");
	जबतक (s < end) अणु
		अक्षर c = *s++;
		चयन (c) अणु
		हाल '\a':
			ख_लिखो(f, "\\a");
			अवरोध;
		हाल '\b':
			ख_लिखो(f, "\\b");
			अवरोध;
		हाल '\t':
			ख_लिखो(f, "\\t");
			अवरोध;
		हाल '\n':
			ख_लिखो(f, "\\n");
			अवरोध;
		हाल '\v':
			ख_लिखो(f, "\\v");
			अवरोध;
		हाल '\f':
			ख_लिखो(f, "\\f");
			अवरोध;
		हाल '\r':
			ख_लिखो(f, "\\r");
			अवरोध;
		हाल '\\':
			ख_लिखो(f, "\\\\");
			अवरोध;
		हाल '\"':
			ख_लिखो(f, "\\\"");
			अवरोध;
		हाल '\0':
			ख_लिखो(f, "\\0");
			अवरोध;
		शेष:
			अगर (है_छाप((अचिन्हित अक्षर)c))
				ख_लिखो(f, "%c", c);
			अन्यथा
				ख_लिखो(f, "\\x%02"PRIx8, c);
		पूर्ण
	पूर्ण
	ख_लिखो(f, "\"");
पूर्ण

अटल व्योम ग_लिखो_propval_पूर्णांक(खाता *f, स्थिर अक्षर *p, माप_प्रकार len, माप_प्रकार width)
अणु
	स्थिर अक्षर *end = p + len;
	निश्चित(len % width == 0);

	क्रम (; p < end; p += width) अणु
		चयन (width) अणु
		हाल 1:
			ख_लिखो(f, "%02"PRIx8, *(स्थिर uपूर्णांक8_t*)p);
			अवरोध;
		हाल 2:
			ख_लिखो(f, "0x%02"PRIx16, dtb_ld16(p));
			अवरोध;
		हाल 4:
			ख_लिखो(f, "0x%02"PRIx32, dtb_ld32(p));
			अवरोध;
		हाल 8:
			ख_लिखो(f, "0x%02"PRIx64, dtb_ld64(p));
			अवरोध;
		पूर्ण
		अगर (p + width < end)
			ख_अक्षर_दो(' ', f);
	पूर्ण
पूर्ण

अटल bool has_data_type_inक्रमmation(काष्ठा marker *m)
अणु
	वापस m->type >= TYPE_UINT8;
पूर्ण

अटल काष्ठा marker *next_type_marker(काष्ठा marker *m)
अणु
	जबतक (m && !has_data_type_inक्रमmation(m))
		m = m->next;
	वापस m;
पूर्ण

माप_प्रकार type_marker_length(काष्ठा marker *m)
अणु
	काष्ठा marker *next = next_type_marker(m->next);

	अगर (next)
		वापस next->offset - m->offset;
	वापस 0;
पूर्ण

अटल स्थिर अक्षर *delim_start[] = अणु
	[TYPE_UINT8] = "[",
	[TYPE_UINT16] = "/bits/ 16 <",
	[TYPE_UINT32] = "<",
	[TYPE_UINT64] = "/bits/ 64 <",
	[TYPE_STRING] = "",
पूर्ण;
अटल स्थिर अक्षर *delim_end[] = अणु
	[TYPE_UINT8] = "]",
	[TYPE_UINT16] = ">",
	[TYPE_UINT32] = ">",
	[TYPE_UINT64] = ">",
	[TYPE_STRING] = "",
पूर्ण;

अटल क्रमागत markertype guess_value_type(काष्ठा property *prop)
अणु
	पूर्णांक len = prop->val.len;
	स्थिर अक्षर *p = prop->val.val;
	काष्ठा marker *m = prop->val.markers;
	पूर्णांक nnotstring = 0, nnul = 0;
	पूर्णांक nnotstringlbl = 0, nnotcelllbl = 0;
	पूर्णांक i;

	क्रम (i = 0; i < len; i++) अणु
		अगर (! isstring(p[i]))
			nnotstring++;
		अगर (p[i] == '\0')
			nnul++;
	पूर्ण

	क्रम_each_marker_of_type(m, LABEL) अणु
		अगर ((m->offset > 0) && (prop->val.val[m->offset - 1] != '\0'))
			nnotstringlbl++;
		अगर ((m->offset % माप(cell_t)) != 0)
			nnotcelllbl++;
	पूर्ण

	अगर ((p[len-1] == '\0') && (nnotstring == 0) && (nnul <= (len-nnul))
	    && (nnotstringlbl == 0)) अणु
		वापस TYPE_STRING;
	पूर्ण अन्यथा अगर (((len % माप(cell_t)) == 0) && (nnotcelllbl == 0)) अणु
		वापस TYPE_UINT32;
	पूर्ण

	वापस TYPE_UINT8;
पूर्ण

अटल व्योम ग_लिखो_propval(खाता *f, काष्ठा property *prop)
अणु
	माप_प्रकार len = prop->val.len;
	काष्ठा marker *m = prop->val.markers;
	काष्ठा marker dummy_marker;
	क्रमागत markertype emit_type = TYPE_NONE;
	अक्षर *srcstr;

	अगर (len == 0) अणु
		ख_लिखो(f, ";");
		अगर (annotate) अणु
			srcstr = srcpos_string_first(prop->srcpos, annotate);
			अगर (srcstr) अणु
				ख_लिखो(f, " /* %s */", srcstr);
				मुक्त(srcstr);
			पूर्ण
		पूर्ण
		ख_लिखो(f, "\n");
		वापस;
	पूर्ण

	ख_लिखो(f, " =");

	अगर (!next_type_marker(m)) अणु
		/* data type inक्रमmation missing, need to guess */
		dummy_marker.type = guess_value_type(prop);
		dummy_marker.next = prop->val.markers;
		dummy_marker.offset = 0;
		dummy_marker.ref = शून्य;
		m = &dummy_marker;
	पूर्ण

	क्रम_each_marker(m) अणु
		माप_प्रकार chunk_len = (m->next ? m->next->offset : len) - m->offset;
		माप_प्रकार data_len = type_marker_length(m) ? : len - m->offset;
		स्थिर अक्षर *p = &prop->val.val[m->offset];

		अगर (has_data_type_inक्रमmation(m)) अणु
			emit_type = m->type;
			ख_लिखो(f, " %s", delim_start[emit_type]);
		पूर्ण अन्यथा अगर (m->type == LABEL)
			ख_लिखो(f, " %s:", m->ref);
		अन्यथा अगर (m->offset)
			ख_अक्षर_दो(' ', f);

		अगर (emit_type == TYPE_NONE) अणु
			निश्चित(chunk_len == 0);
			जारी;
		पूर्ण

		चयन(emit_type) अणु
		हाल TYPE_UINT16:
			ग_लिखो_propval_पूर्णांक(f, p, chunk_len, 2);
			अवरोध;
		हाल TYPE_UINT32:
			ग_लिखो_propval_पूर्णांक(f, p, chunk_len, 4);
			अवरोध;
		हाल TYPE_UINT64:
			ग_लिखो_propval_पूर्णांक(f, p, chunk_len, 8);
			अवरोध;
		हाल TYPE_STRING:
			ग_लिखो_propval_string(f, p, chunk_len);
			अवरोध;
		शेष:
			ग_लिखो_propval_पूर्णांक(f, p, chunk_len, 1);
		पूर्ण

		अगर (chunk_len == data_len) अणु
			माप_प्रकार pos = m->offset + chunk_len;
			ख_लिखो(f, pos == len ? "%s" : "%s,",
			        delim_end[emit_type] ? : "");
			emit_type = TYPE_NONE;
		पूर्ण
	पूर्ण
	ख_लिखो(f, ";");
	अगर (annotate) अणु
		srcstr = srcpos_string_first(prop->srcpos, annotate);
		अगर (srcstr) अणु
			ख_लिखो(f, " /* %s */", srcstr);
			मुक्त(srcstr);
		पूर्ण
	पूर्ण
	ख_लिखो(f, "\n");
पूर्ण

अटल व्योम ग_लिखो_tree_source_node(खाता *f, काष्ठा node *tree, पूर्णांक level)
अणु
	काष्ठा property *prop;
	काष्ठा node *child;
	काष्ठा label *l;
	अक्षर *srcstr;

	ग_लिखो_prefix(f, level);
	क्रम_each_label(tree->labels, l)
		ख_लिखो(f, "%s: ", l->label);
	अगर (tree->name && (*tree->name))
		ख_लिखो(f, "%s {", tree->name);
	अन्यथा
		ख_लिखो(f, "/ {");

	अगर (annotate) अणु
		srcstr = srcpos_string_first(tree->srcpos, annotate);
		अगर (srcstr) अणु
			ख_लिखो(f, " /* %s */", srcstr);
			मुक्त(srcstr);
		पूर्ण
	पूर्ण
	ख_लिखो(f, "\n");

	क्रम_each_property(tree, prop) अणु
		ग_लिखो_prefix(f, level+1);
		क्रम_each_label(prop->labels, l)
			ख_लिखो(f, "%s: ", l->label);
		ख_लिखो(f, "%s", prop->name);
		ग_लिखो_propval(f, prop);
	पूर्ण
	क्रम_each_child(tree, child) अणु
		ख_लिखो(f, "\n");
		ग_लिखो_tree_source_node(f, child, level+1);
	पूर्ण
	ग_लिखो_prefix(f, level);
	ख_लिखो(f, "};");
	अगर (annotate) अणु
		srcstr = srcpos_string_last(tree->srcpos, annotate);
		अगर (srcstr) अणु
			ख_लिखो(f, " /* %s */", srcstr);
			मुक्त(srcstr);
		पूर्ण
	पूर्ण
	ख_लिखो(f, "\n");
पूर्ण

व्योम dt_to_source(खाता *f, काष्ठा dt_info *dti)
अणु
	काष्ठा reserve_info *re;

	ख_लिखो(f, "/dts-v1/;\n\n");

	क्रम (re = dti->reservelist; re; re = re->next) अणु
		काष्ठा label *l;

		क्रम_each_label(re->labels, l)
			ख_लिखो(f, "%s: ", l->label);
		ख_लिखो(f, "/memreserve/\t0x%016llx 0x%016llx;\n",
			(अचिन्हित दीर्घ दीर्घ)re->address,
			(अचिन्हित दीर्घ दीर्घ)re->size);
	पूर्ण

	ग_लिखो_tree_source_node(f, dti->dt, 0);
पूर्ण
