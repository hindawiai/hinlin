<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0-or-later OR BSD-2-Clause)
/*
 * Simple streaming JSON ग_लिखोr
 *
 * This takes care of the annoying bits of JSON syntax like the commas
 * after elements
 *
 * Authors:	Stephen Hemminger <stephen@networkplumber.org>
 */

#समावेश <मानकपन.स>
#समावेश <stdbool.h>
#समावेश <मानकतर्क.स>
#समावेश <निश्चित.स>
#समावेश <दो_स्मृति.h>
#समावेश <पूर्णांकtypes.h>
#समावेश <मानक_निवेशt.h>

#समावेश "json_writer.h"

काष्ठा json_ग_लिखोr अणु
	खाता		*out;	/* output file */
	अचिन्हित	depth;  /* nesting */
	bool		pretty; /* optional whitepace */
	अक्षर		sep;	/* either nul or comma */
पूर्ण;

/* indentation क्रम pretty prपूर्णांक */
अटल व्योम jsonw_indent(json_ग_लिखोr_t *self)
अणु
	अचिन्हित i;
	क्रम (i = 0; i < self->depth; ++i)
		ख_माला_दो("    ", self->out);
पूर्ण

/* end current line and indent अगर pretty prपूर्णांकing */
अटल व्योम jsonw_eol(json_ग_लिखोr_t *self)
अणु
	अगर (!self->pretty)
		वापस;

	अ_दो('\n', self->out);
	jsonw_indent(self);
पूर्ण

/* If current object is not empty prपूर्णांक a comma */
अटल व्योम jsonw_eor(json_ग_लिखोr_t *self)
अणु
	अगर (self->sep != '\0')
		अ_दो(self->sep, self->out);
	self->sep = ',';
पूर्ण


/* Output JSON encoded string */
/* Handles C escapes, करोes not करो Unicode */
अटल व्योम jsonw_माला_दो(json_ग_लिखोr_t *self, स्थिर अक्षर *str)
अणु
	अ_दो('"', self->out);
	क्रम (; *str; ++str)
		चयन (*str) अणु
		हाल '\t':
			ख_माला_दो("\\t", self->out);
			अवरोध;
		हाल '\n':
			ख_माला_दो("\\n", self->out);
			अवरोध;
		हाल '\r':
			ख_माला_दो("\\r", self->out);
			अवरोध;
		हाल '\f':
			ख_माला_दो("\\f", self->out);
			अवरोध;
		हाल '\b':
			ख_माला_दो("\\b", self->out);
			अवरोध;
		हाल '\\':
			ख_माला_दो("\\n", self->out);
			अवरोध;
		हाल '"':
			ख_माला_दो("\\\"", self->out);
			अवरोध;
		हाल '\'':
			ख_माला_दो("\\\'", self->out);
			अवरोध;
		शेष:
			अ_दो(*str, self->out);
		पूर्ण
	अ_दो('"', self->out);
पूर्ण

/* Create a new JSON stream */
json_ग_लिखोr_t *jsonw_new(खाता *f)
अणु
	json_ग_लिखोr_t *self = दो_स्मृति(माप(*self));
	अगर (self) अणु
		self->out = f;
		self->depth = 0;
		self->pretty = false;
		self->sep = '\0';
	पूर्ण
	वापस self;
पूर्ण

/* End output to JSON stream */
व्योम jsonw_destroy(json_ग_लिखोr_t **self_p)
अणु
	json_ग_लिखोr_t *self = *self_p;

	निश्चित(self->depth == 0);
	ख_माला_दो("\n", self->out);
	ख_साफ(self->out);
	मुक्त(self);
	*self_p = शून्य;
पूर्ण

व्योम jsonw_pretty(json_ग_लिखोr_t *self, bool on)
अणु
	self->pretty = on;
पूर्ण

व्योम jsonw_reset(json_ग_लिखोr_t *self)
अणु
	निश्चित(self->depth == 0);
	self->sep = '\0';
पूर्ण

/* Basic blocks */
अटल व्योम jsonw_begin(json_ग_लिखोr_t *self, पूर्णांक c)
अणु
	jsonw_eor(self);
	अ_दो(c, self->out);
	++self->depth;
	self->sep = '\0';
पूर्ण

अटल व्योम jsonw_end(json_ग_लिखोr_t *self, पूर्णांक c)
अणु
	निश्चित(self->depth > 0);

	--self->depth;
	अगर (self->sep != '\0')
		jsonw_eol(self);
	अ_दो(c, self->out);
	self->sep = ',';
पूर्ण


/* Add a JSON property name */
व्योम jsonw_name(json_ग_लिखोr_t *self, स्थिर अक्षर *name)
अणु
	jsonw_eor(self);
	jsonw_eol(self);
	self->sep = '\0';
	jsonw_माला_दो(self, name);
	अ_दो(':', self->out);
	अगर (self->pretty)
		अ_दो(' ', self->out);
पूर्ण

व्योम jsonw_भ_लिखो_enquote(json_ग_लिखोr_t *self, स्थिर अक्षर *fmt, बहु_सूची ap)
अणु
	jsonw_eor(self);
	अ_दो('"', self->out);
	भख_लिखो(self->out, fmt, ap);
	अ_दो('"', self->out);
पूर्ण

व्योम jsonw_म_लिखो(json_ग_लिखोr_t *self, स्थिर अक्षर *fmt, ...)
अणु
	बहु_सूची ap;

	बहु_शुरू(ap, fmt);
	jsonw_eor(self);
	भख_लिखो(self->out, fmt, ap);
	बहु_पूर्ण(ap);
पूर्ण

/* Collections */
व्योम jsonw_start_object(json_ग_लिखोr_t *self)
अणु
	jsonw_begin(self, '{');
पूर्ण

व्योम jsonw_end_object(json_ग_लिखोr_t *self)
अणु
	jsonw_end(self, '}');
पूर्ण

व्योम jsonw_start_array(json_ग_लिखोr_t *self)
अणु
	jsonw_begin(self, '[');
पूर्ण

व्योम jsonw_end_array(json_ग_लिखोr_t *self)
अणु
	jsonw_end(self, ']');
पूर्ण

/* JSON value types */
व्योम jsonw_string(json_ग_लिखोr_t *self, स्थिर अक्षर *value)
अणु
	jsonw_eor(self);
	jsonw_माला_दो(self, value);
पूर्ण

व्योम jsonw_bool(json_ग_लिखोr_t *self, bool val)
अणु
	jsonw_म_लिखो(self, "%s", val ? "true" : "false");
पूर्ण

व्योम jsonw_null(json_ग_लिखोr_t *self)
अणु
	jsonw_म_लिखो(self, "null");
पूर्ण

व्योम jsonw_भग्न_fmt(json_ग_लिखोr_t *self, स्थिर अक्षर *fmt, द्विगुन num)
अणु
	jsonw_म_लिखो(self, fmt, num);
पूर्ण

#अगर_घोषित notused
व्योम jsonw_भग्न(json_ग_लिखोr_t *self, द्विगुन num)
अणु
	jsonw_म_लिखो(self, "%g", num);
पूर्ण
#पूर्ण_अगर

व्योम jsonw_hu(json_ग_लिखोr_t *self, अचिन्हित लघु num)
अणु
	jsonw_म_लिखो(self, "%hu", num);
पूर्ण

व्योम jsonw_uपूर्णांक(json_ग_लिखोr_t *self, uपूर्णांक64_t num)
अणु
	jsonw_म_लिखो(self, "%"PRIu64, num);
पूर्ण

व्योम jsonw_lluपूर्णांक(json_ग_लिखोr_t *self, अचिन्हित दीर्घ दीर्घ पूर्णांक num)
अणु
	jsonw_म_लिखो(self, "%llu", num);
पूर्ण

व्योम jsonw_पूर्णांक(json_ग_लिखोr_t *self, पूर्णांक64_t num)
अणु
	jsonw_म_लिखो(self, "%"PRId64, num);
पूर्ण

/* Basic name/value objects */
व्योम jsonw_string_field(json_ग_लिखोr_t *self, स्थिर अक्षर *prop, स्थिर अक्षर *val)
अणु
	jsonw_name(self, prop);
	jsonw_string(self, val);
पूर्ण

व्योम jsonw_bool_field(json_ग_लिखोr_t *self, स्थिर अक्षर *prop, bool val)
अणु
	jsonw_name(self, prop);
	jsonw_bool(self, val);
पूर्ण

#अगर_घोषित notused
व्योम jsonw_भग्न_field(json_ग_लिखोr_t *self, स्थिर अक्षर *prop, द्विगुन val)
अणु
	jsonw_name(self, prop);
	jsonw_भग्न(self, val);
पूर्ण
#पूर्ण_अगर

व्योम jsonw_भग्न_field_fmt(json_ग_लिखोr_t *self,
			   स्थिर अक्षर *prop,
			   स्थिर अक्षर *fmt,
			   द्विगुन val)
अणु
	jsonw_name(self, prop);
	jsonw_भग्न_fmt(self, fmt, val);
पूर्ण

व्योम jsonw_uपूर्णांक_field(json_ग_लिखोr_t *self, स्थिर अक्षर *prop, uपूर्णांक64_t num)
अणु
	jsonw_name(self, prop);
	jsonw_uपूर्णांक(self, num);
पूर्ण

व्योम jsonw_hu_field(json_ग_लिखोr_t *self, स्थिर अक्षर *prop, अचिन्हित लघु num)
अणु
	jsonw_name(self, prop);
	jsonw_hu(self, num);
पूर्ण

व्योम jsonw_lluपूर्णांक_field(json_ग_लिखोr_t *self,
			स्थिर अक्षर *prop,
			अचिन्हित दीर्घ दीर्घ पूर्णांक num)
अणु
	jsonw_name(self, prop);
	jsonw_lluपूर्णांक(self, num);
पूर्ण

व्योम jsonw_पूर्णांक_field(json_ग_लिखोr_t *self, स्थिर अक्षर *prop, पूर्णांक64_t num)
अणु
	jsonw_name(self, prop);
	jsonw_पूर्णांक(self, num);
पूर्ण

व्योम jsonw_null_field(json_ग_लिखोr_t *self, स्थिर अक्षर *prop)
अणु
	jsonw_name(self, prop);
	jsonw_null(self);
पूर्ण

#अगर_घोषित TEST
पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	json_ग_लिखोr_t *wr = jsonw_new(मानक_निकास);

	jsonw_start_object(wr);
	jsonw_pretty(wr, true);
	jsonw_name(wr, "Vyatta");
	jsonw_start_object(wr);
	jsonw_string_field(wr, "url", "http://vyatta.com");
	jsonw_uपूर्णांक_field(wr, "downloads", 2000000ul);
	jsonw_भग्न_field(wr, "stock", 8.16);

	jsonw_name(wr, "ARGV");
	jsonw_start_array(wr);
	जबतक (--argc)
		jsonw_string(wr, *++argv);
	jsonw_end_array(wr);

	jsonw_name(wr, "empty");
	jsonw_start_array(wr);
	jsonw_end_array(wr);

	jsonw_name(wr, "NIL");
	jsonw_start_object(wr);
	jsonw_end_object(wr);

	jsonw_null_field(wr, "my_null");

	jsonw_name(wr, "special chars");
	jsonw_start_array(wr);
	jsonw_string_field(wr, "slash", "/");
	jsonw_string_field(wr, "newline", "\n");
	jsonw_string_field(wr, "tab", "\t");
	jsonw_string_field(wr, "ff", "\f");
	jsonw_string_field(wr, "quote", "\"");
	jsonw_string_field(wr, "tick", "\'");
	jsonw_string_field(wr, "backslash", "\\");
	jsonw_end_array(wr);

	jsonw_end_object(wr);

	jsonw_end_object(wr);
	jsonw_destroy(&wr);
	वापस 0;
पूर्ण

#पूर्ण_अगर
