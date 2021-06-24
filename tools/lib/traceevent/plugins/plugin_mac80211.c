<शैली गुरु>
// SPDX-License-Identअगरier: LGPL-2.1
/*
 * Copyright (C) 2009 Johannes Berg <johannes@sipsolutions.net>
 */
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>

#समावेश "event-parse.h"
#समावेश "trace-seq.h"

#घोषणा INDENT 65

अटल व्योम prपूर्णांक_string(काष्ठा trace_seq *s, काष्ठा tep_event *event,
			 स्थिर अक्षर *name, स्थिर व्योम *data)
अणु
	काष्ठा tep_क्रमmat_field *f = tep_find_field(event, name);
	पूर्णांक offset;
	पूर्णांक length;

	अगर (!f) अणु
		trace_seq_म_लिखो(s, "NOTFOUND:%s", name);
		वापस;
	पूर्ण

	offset = f->offset;
	length = f->size;

	अगर (!म_भेदन(f->type, "__data_loc", 10)) अणु
		अचिन्हित दीर्घ दीर्घ v;
		अगर (tep_पढ़ो_number_field(f, data, &v)) अणु
			trace_seq_म_लिखो(s, "invalid_data_loc");
			वापस;
		पूर्ण
		offset = v & 0xffff;
		length = v >> 16;
	पूर्ण

	trace_seq_म_लिखो(s, "%.*s", length, (अक्षर *)data + offset);
पूर्ण

#घोषणा SF(fn)	tep_prपूर्णांक_num_field(s, fn ":%d", event, fn, record, 0)
#घोषणा SFX(fn)	tep_prपूर्णांक_num_field(s, fn ":%#x", event, fn, record, 0)
#घोषणा SP()	trace_seq_अ_दो(s, ' ')

अटल पूर्णांक drv_bss_info_changed(काष्ठा trace_seq *s,
				काष्ठा tep_record *record,
				काष्ठा tep_event *event, व्योम *context)
अणु
	व्योम *data = record->data;

	prपूर्णांक_string(s, event, "wiphy_name", data);
	trace_seq_म_लिखो(s, " vif:");
	prपूर्णांक_string(s, event, "vif_name", data);
	tep_prपूर्णांक_num_field(s, "(%d)", event, "vif_type", record, 1);

	trace_seq_म_लिखो(s, "\n%*s", INDENT, "");
	SF("assoc"); SP();
	SF("aid"); SP();
	SF("cts"); SP();
	SF("shortpre"); SP();
	SF("shortslot"); SP();
	SF("dtimper"); SP();
	trace_seq_म_लिखो(s, "\n%*s", INDENT, "");
	SF("bcnint"); SP();
	SFX("assoc_cap"); SP();
	SFX("basic_rates"); SP();
	SF("enable_beacon");
	trace_seq_म_लिखो(s, "\n%*s", INDENT, "");
	SF("ht_operation_mode");

	वापस 0;
पूर्ण

पूर्णांक TEP_PLUGIN_LOADER(काष्ठा tep_handle *tep)
अणु
	tep_रेजिस्टर_event_handler(tep, -1, "mac80211",
				   "drv_bss_info_changed",
				   drv_bss_info_changed, शून्य);
	वापस 0;
पूर्ण

व्योम TEP_PLUGIN_UNLOADER(काष्ठा tep_handle *tep)
अणु
	tep_unरेजिस्टर_event_handler(tep, -1, "mac80211",
				     "drv_bss_info_changed",
				     drv_bss_info_changed, शून्य);
पूर्ण
