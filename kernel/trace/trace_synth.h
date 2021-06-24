<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#अगर_अघोषित __TRACE_SYNTH_H
#घोषणा __TRACE_SYNTH_H

#समावेश "trace_dynevent.h"

#घोषणा SYNTH_SYSTEM		"synthetic"
#घोषणा SYNTH_FIELDS_MAX	32

#घोषणा STR_VAR_LEN_MAX		MAX_FILTER_STR_VAL /* must be multiple of माप(u64) */

काष्ठा synth_field अणु
	अक्षर *type;
	अक्षर *name;
	माप_प्रकार size;
	अचिन्हित पूर्णांक offset;
	bool is_चिन्हित;
	bool is_string;
	bool is_dynamic;
	bool field_pos;
पूर्ण;

काष्ठा synth_event अणु
	काष्ठा dyn_event			devent;
	पूर्णांक					ref;
	अक्षर					*name;
	काष्ठा synth_field			**fields;
	अचिन्हित पूर्णांक				n_fields;
	काष्ठा synth_field			**dynamic_fields;
	अचिन्हित पूर्णांक				n_dynamic_fields;
	अचिन्हित पूर्णांक				n_u64;
	काष्ठा trace_event_class		class;
	काष्ठा trace_event_call			call;
	काष्ठा tracepoपूर्णांक			*tp;
	काष्ठा module				*mod;
पूर्ण;

बाह्य काष्ठा synth_event *find_synth_event(स्थिर अक्षर *name);

#पूर्ण_अगर /* __TRACE_SYNTH_H */
