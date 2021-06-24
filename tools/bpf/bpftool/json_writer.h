<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-2-Clause) */
/*
 * Simple streaming JSON ग_लिखोr
 *
 * This takes care of the annoying bits of JSON syntax like the commas
 * after elements
 *
 * Authors:	Stephen Hemminger <stephen@networkplumber.org>
 */

#अगर_अघोषित _JSON_WRITER_H_
#घोषणा _JSON_WRITER_H_

#समावेश <stdbool.h>
#समावेश <मानक_निवेशt.h>
#समावेश <मानकतर्क.स>
#समावेश <linux/compiler.h>

/* Opaque class काष्ठाure */
प्रकार काष्ठा json_ग_लिखोr json_ग_लिखोr_t;

/* Create a new JSON stream */
json_ग_लिखोr_t *jsonw_new(खाता *f);
/* End output to JSON stream */
व्योम jsonw_destroy(json_ग_लिखोr_t **self_p);

/* Cause output to have pretty whitespace */
व्योम jsonw_pretty(json_ग_लिखोr_t *self, bool on);

/* Reset separator to create new JSON */
व्योम jsonw_reset(json_ग_लिखोr_t *self);

/* Add property name */
व्योम jsonw_name(json_ग_लिखोr_t *self, स्थिर अक्षर *name);

/* Add value  */
व्योम __म_लिखो(2, 0) jsonw_भ_लिखो_enquote(json_ग_लिखोr_t *self, स्थिर अक्षर *fmt,
					  बहु_सूची ap);
व्योम __म_लिखो(2, 3) jsonw_म_लिखो(json_ग_लिखोr_t *self, स्थिर अक्षर *fmt, ...);
व्योम jsonw_string(json_ग_लिखोr_t *self, स्थिर अक्षर *value);
व्योम jsonw_bool(json_ग_लिखोr_t *self, bool value);
व्योम jsonw_भग्न(json_ग_लिखोr_t *self, द्विगुन number);
व्योम jsonw_भग्न_fmt(json_ग_लिखोr_t *self, स्थिर अक्षर *fmt, द्विगुन num);
व्योम jsonw_uपूर्णांक(json_ग_लिखोr_t *self, uपूर्णांक64_t number);
व्योम jsonw_hu(json_ग_लिखोr_t *self, अचिन्हित लघु number);
व्योम jsonw_पूर्णांक(json_ग_लिखोr_t *self, पूर्णांक64_t number);
व्योम jsonw_null(json_ग_लिखोr_t *self);
व्योम jsonw_lluपूर्णांक(json_ग_लिखोr_t *self, अचिन्हित दीर्घ दीर्घ पूर्णांक num);

/* Useful Combinations of name and value */
व्योम jsonw_string_field(json_ग_लिखोr_t *self, स्थिर अक्षर *prop, स्थिर अक्षर *val);
व्योम jsonw_bool_field(json_ग_लिखोr_t *self, स्थिर अक्षर *prop, bool value);
व्योम jsonw_भग्न_field(json_ग_लिखोr_t *self, स्थिर अक्षर *prop, द्विगुन num);
व्योम jsonw_uपूर्णांक_field(json_ग_लिखोr_t *self, स्थिर अक्षर *prop, uपूर्णांक64_t num);
व्योम jsonw_hu_field(json_ग_लिखोr_t *self, स्थिर अक्षर *prop, अचिन्हित लघु num);
व्योम jsonw_पूर्णांक_field(json_ग_लिखोr_t *self, स्थिर अक्षर *prop, पूर्णांक64_t num);
व्योम jsonw_null_field(json_ग_लिखोr_t *self, स्थिर अक्षर *prop);
व्योम jsonw_lluपूर्णांक_field(json_ग_लिखोr_t *self, स्थिर अक्षर *prop,
			अचिन्हित दीर्घ दीर्घ पूर्णांक num);
व्योम jsonw_भग्न_field_fmt(json_ग_लिखोr_t *self, स्थिर अक्षर *prop,
			   स्थिर अक्षर *fmt, द्विगुन val);

/* Collections */
व्योम jsonw_start_object(json_ग_लिखोr_t *self);
व्योम jsonw_end_object(json_ग_लिखोr_t *self);

व्योम jsonw_start_array(json_ग_लिखोr_t *self);
व्योम jsonw_end_array(json_ग_लिखोr_t *self);

/* Override शेष exception handling */
प्रकार व्योम (jsonw_err_handler_fn)(स्थिर अक्षर *);

#पूर्ण_अगर /* _JSON_WRITER_H_ */
