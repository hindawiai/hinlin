<शैली गुरु>
#घोषणा  _XOPEN_SOURCE 500	/* needed क्रम nftw() */
#घोषणा  _GNU_SOURCE		/* needed क्रम aप्र_लिखो() */

/* Parse event JSON files */

/*
 * Copyright (c) 2014, Intel Corporation
 * All rights reserved.
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary क्रमm must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * करोcumentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY सूचीECT,
 * INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <त्रुटिसं.स>
#समावेश <माला.स>
#समावेश <प्रकार.स>
#समावेश <unistd.h>
#समावेश <मानकतर्क.स>
#समावेश <libgen.h>
#समावेश <सीमा.स>
#समावेश <dirent.h>
#समावेश <sys/समय.स>			/* getrlimit */
#समावेश <sys/resource.h>		/* getrlimit */
#समावेश <ftw.h>
#समावेश <sys/स्थिति.स>
#समावेश <linux/list.h>
#समावेश "jsmn.h"
#समावेश "json.h"
#समावेश "pmu-events.h"

पूर्णांक verbose;
अक्षर *prog;

काष्ठा json_event अणु
	अक्षर *name;
	अक्षर *compat;
	अक्षर *event;
	अक्षर *desc;
	अक्षर *दीर्घ_desc;
	अक्षर *pmu;
	अक्षर *unit;
	अक्षर *perpkg;
	अक्षर *aggr_mode;
	अक्षर *metric_expr;
	अक्षर *metric_name;
	अक्षर *metric_group;
	अक्षर *deprecated;
	अक्षर *metric_स्थिरraपूर्णांक;
पूर्ण;

क्रमागत aggr_mode_class convert(स्थिर अक्षर *aggr_mode)
अणु
	अगर (!म_भेद(aggr_mode, "PerCore"))
		वापस PerCore;
	अन्यथा अगर (!म_भेद(aggr_mode, "PerChip"))
		वापस PerChip;

	pr_err("%s: Wrong AggregationMode value '%s'\n", prog, aggr_mode);
	वापस -1;
पूर्ण

प्रकार पूर्णांक (*func)(व्योम *data, काष्ठा json_event *je);

अटल LIST_HEAD(sys_event_tables);

काष्ठा sys_event_table अणु
	काष्ठा list_head list;
	अक्षर *soc_id;
पूर्ण;

अटल व्योम मुक्त_sys_event_tables(व्योम)
अणु
	काष्ठा sys_event_table *et, *next;

	list_क्रम_each_entry_safe(et, next, &sys_event_tables, list) अणु
		मुक्त(et->soc_id);
		मुक्त(et);
	पूर्ण
पूर्ण

पूर्णांक eम_लिखो(पूर्णांक level, पूर्णांक var, स्थिर अक्षर *fmt, ...)
अणु

	पूर्णांक ret;
	बहु_सूची args;

	अगर (var < level)
		वापस 0;

	बहु_शुरू(args, fmt);

	ret = भख_लिखो(मानक_त्रुटि, fmt, args);

	बहु_पूर्ण(args);

	वापस ret;
पूर्ण

अटल व्योम addfield(अक्षर *map, अक्षर **dst, स्थिर अक्षर *sep,
		     स्थिर अक्षर *a, jsmntok_t *bt)
अणु
	अचिन्हित पूर्णांक len = म_माप(a) + 1 + म_माप(sep);
	पूर्णांक olen = *dst ? म_माप(*dst) : 0;
	पूर्णांक blen = bt ? json_len(bt) : 0;
	अक्षर *out;

	out = पुनः_स्मृति(*dst, len + olen + blen);
	अगर (!out) अणु
		/* Don't add field in this हाल */
		वापस;
	पूर्ण
	*dst = out;

	अगर (!olen)
		*(*dst) = 0;
	अन्यथा
		म_जोड़ो(*dst, sep);
	म_जोड़ो(*dst, a);
	अगर (bt)
		म_जोड़न(*dst, map + bt->start, blen);
पूर्ण

अटल व्योम fixname(अक्षर *s)
अणु
	क्रम (; *s; s++)
		*s = छोटे(*s);
पूर्ण

अटल व्योम fixdesc(अक्षर *s)
अणु
	अक्षर *e = s + म_माप(s);

	/* Remove trailing करोts that look ugly in perf list */
	--e;
	जबतक (e >= s && है_खाली(*e))
		--e;
	अगर (*e == '.')
		*e = 0;
पूर्ण

/* Add escapes क्रम '\' so they are proper C strings. */
अटल अक्षर *fixregex(अक्षर *s)
अणु
	पूर्णांक len = 0;
	पूर्णांक esc_count = 0;
	अक्षर *fixed = शून्य;
	अक्षर *p, *q;

	/* Count the number of '\' in string */
	क्रम (p = s; *p; p++) अणु
		++len;
		अगर (*p == '\\')
			++esc_count;
	पूर्ण

	अगर (esc_count == 0)
		वापस s;

	/* allocate space क्रम a new string */
	fixed = (अक्षर *) दो_स्मृति(len + esc_count + 1);
	अगर (!fixed)
		वापस शून्य;

	/* copy over the अक्षरacters */
	q = fixed;
	क्रम (p = s; *p; p++) अणु
		अगर (*p == '\\') अणु
			*q = '\\';
			++q;
		पूर्ण
		*q = *p;
		++q;
	पूर्ण
	*q = '\0';
	वापस fixed;
पूर्ण

अटल काष्ठा msrmap अणु
	स्थिर अक्षर *num;
	स्थिर अक्षर *pname;
पूर्ण msrmap[] = अणु
	अणु "0x3F6", "ldlat=" पूर्ण,
	अणु "0x1A6", "offcore_rsp=" पूर्ण,
	अणु "0x1A7", "offcore_rsp=" पूर्ण,
	अणु "0x3F7", "frontend=" पूर्ण,
	अणु शून्य, शून्य पूर्ण
पूर्ण;

अटल काष्ठा field अणु
	स्थिर अक्षर *field;
	स्थिर अक्षर *kernel;
पूर्ण fields[] = अणु
	अणु "UMask",	"umask=" पूर्ण,
	अणु "CounterMask", "cmask=" पूर्ण,
	अणु "Invert",	"inv=" पूर्ण,
	अणु "AnyThread",	"any=" पूर्ण,
	अणु "EdgeDetect",	"edge=" पूर्ण,
	अणु "SampleAfterValue", "period=" पूर्ण,
	अणु "FCMask",	"fc_mask=" पूर्ण,
	अणु "PortMask",	"ch_mask=" पूर्ण,
	अणु शून्य, शून्य पूर्ण
पूर्ण;

अटल व्योम cut_comma(अक्षर *map, jsmntok_t *newval)
अणु
	पूर्णांक i;

	/* Cut off everything after comma */
	क्रम (i = newval->start; i < newval->end; i++) अणु
		अगर (map[i] == ',')
			newval->end = i;
	पूर्ण
पूर्ण

अटल पूर्णांक match_field(अक्षर *map, jsmntok_t *field, पूर्णांक nz,
		       अक्षर **event, jsmntok_t *val)
अणु
	काष्ठा field *f;
	jsmntok_t newval = *val;

	क्रम (f = fields; f->field; f++)
		अगर (json_streq(map, field, f->field) && nz) अणु
			cut_comma(map, &newval);
			addfield(map, event, ",", f->kernel, &newval);
			वापस 1;
		पूर्ण
	वापस 0;
पूर्ण

अटल काष्ठा msrmap *lookup_msr(अक्षर *map, jsmntok_t *val)
अणु
	jsmntok_t newval = *val;
	अटल bool warned;
	पूर्णांक i;

	cut_comma(map, &newval);
	क्रम (i = 0; msrmap[i].num; i++)
		अगर (json_streq(map, &newval, msrmap[i].num))
			वापस &msrmap[i];
	अगर (!warned) अणु
		warned = true;
		pr_err("%s: Unknown MSR in event file %.*s\n", prog,
			json_len(val), map + val->start);
	पूर्ण
	वापस शून्य;
पूर्ण

अटल काष्ठा map अणु
	स्थिर अक्षर *json;
	स्थिर अक्षर *perf;
पूर्ण unit_to_pmu[] = अणु
	अणु "CBO", "uncore_cbox" पूर्ण,
	अणु "QPI LL", "uncore_qpi" पूर्ण,
	अणु "SBO", "uncore_sbox" पूर्ण,
	अणु "iMPH-U", "uncore_arb" पूर्ण,
	अणु "CPU-M-CF", "cpum_cf" पूर्ण,
	अणु "CPU-M-SF", "cpum_sf" पूर्ण,
	अणु "UPI LL", "uncore_upi" पूर्ण,
	अणु "hisi_sccl,ddrc", "hisi_sccl,ddrc" पूर्ण,
	अणु "hisi_sccl,hha", "hisi_sccl,hha" पूर्ण,
	अणु "hisi_sccl,l3c", "hisi_sccl,l3c" पूर्ण,
	/* it's not realistic to keep adding these, we need something more scalable ... */
	अणु "imx8_ddr", "imx8_ddr" पूर्ण,
	अणु "L3PMC", "amd_l3" पूर्ण,
	अणु "DFPMC", "amd_df" पूर्ण,
	अणु "cpu_core", "cpu_core" पूर्ण,
	अणु "cpu_atom", "cpu_atom" पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर अक्षर *field_to_perf(काष्ठा map *table, अक्षर *map, jsmntok_t *val)
अणु
	पूर्णांक i;

	क्रम (i = 0; table[i].json; i++) अणु
		अगर (json_streq(map, val, table[i].json))
			वापस table[i].perf;
	पूर्ण
	वापस शून्य;
पूर्ण

#घोषणा EXPECT(e, t, m) करो अणु अगर (!(e)) अणु			\
	jsmntok_t *loc = (t);					\
	अगर (!(t)->start && (t) > tokens)			\
		loc = (t) - 1;					\
	pr_err("%s:%d: " m ", got %s\n", fn,			\
	       json_line(map, loc),				\
	       json_name(t));					\
	err = -EIO;						\
	जाओ out_मुक्त;						\
पूर्ण पूर्ण जबतक (0)

अटल अक्षर *topic;

अटल अक्षर *get_topic(व्योम)
अणु
	अक्षर *tp;
	पूर्णांक i;

	/* tp is मुक्त'd in process_one_file() */
	i = aप्र_लिखो(&tp, "%s", topic);
	अगर (i < 0) अणु
		pr_info("%s: asprintf() error %s\n", prog);
		वापस शून्य;
	पूर्ण

	क्रम (i = 0; i < (पूर्णांक) म_माप(tp); i++) अणु
		अक्षर c = tp[i];

		अगर (c == '-')
			tp[i] = ' ';
		अन्यथा अगर (c == '.') अणु
			tp[i] = '\0';
			अवरोध;
		पूर्ण
	पूर्ण

	वापस tp;
पूर्ण

अटल पूर्णांक add_topic(अक्षर *bname)
अणु
	मुक्त(topic);
	topic = strdup(bname);
	अगर (!topic) अणु
		pr_info("%s: strdup() error %s for file %s\n", prog,
				म_त्रुटि(त्रुटि_सं), bname);
		वापस -ENOMEM;
	पूर्ण
	वापस 0;
पूर्ण

काष्ठा perf_entry_data अणु
	खाता *outfp;
	अक्षर *topic;
पूर्ण;

अटल पूर्णांक बंद_table;

अटल व्योम prपूर्णांक_events_table_prefix(खाता *fp, स्थिर अक्षर *tblname)
अणु
	ख_लिखो(fp, "struct pmu_event %s[] = {\n", tblname);
	बंद_table = 1;
पूर्ण

अटल पूर्णांक prपूर्णांक_events_table_entry(व्योम *data, काष्ठा json_event *je)
अणु
	काष्ठा perf_entry_data *pd = data;
	खाता *outfp = pd->outfp;
	अक्षर *topic = pd->topic;

	/*
	 * TODO: Remove क्रमmatting अक्षरs after debugging to reduce
	 *	 string lengths.
	 */
	ख_लिखो(outfp, "{\n");

	अगर (je->name)
		ख_लिखो(outfp, "\t.name = \"%s\",\n", je->name);
	अगर (je->event)
		ख_लिखो(outfp, "\t.event = \"%s\",\n", je->event);
	ख_लिखो(outfp, "\t.desc = \"%s\",\n", je->desc);
	अगर (je->compat)
		ख_लिखो(outfp, "\t.compat = \"%s\",\n", je->compat);
	ख_लिखो(outfp, "\t.topic = \"%s\",\n", topic);
	अगर (je->दीर्घ_desc && je->दीर्घ_desc[0])
		ख_लिखो(outfp, "\t.long_desc = \"%s\",\n", je->दीर्घ_desc);
	अगर (je->pmu)
		ख_लिखो(outfp, "\t.pmu = \"%s\",\n", je->pmu);
	अगर (je->unit)
		ख_लिखो(outfp, "\t.unit = \"%s\",\n", je->unit);
	अगर (je->perpkg)
		ख_लिखो(outfp, "\t.perpkg = \"%s\",\n", je->perpkg);
	अगर (je->aggr_mode)
		ख_लिखो(outfp, "\t.aggr_mode = \"%d\",\n", convert(je->aggr_mode));
	अगर (je->metric_expr)
		ख_लिखो(outfp, "\t.metric_expr = \"%s\",\n", je->metric_expr);
	अगर (je->metric_name)
		ख_लिखो(outfp, "\t.metric_name = \"%s\",\n", je->metric_name);
	अगर (je->metric_group)
		ख_लिखो(outfp, "\t.metric_group = \"%s\",\n", je->metric_group);
	अगर (je->deprecated)
		ख_लिखो(outfp, "\t.deprecated = \"%s\",\n", je->deprecated);
	अगर (je->metric_स्थिरraपूर्णांक)
		ख_लिखो(outfp, "\t.metric_constraint = \"%s\",\n", je->metric_स्थिरraपूर्णांक);
	ख_लिखो(outfp, "},\n");

	वापस 0;
पूर्ण

काष्ठा event_काष्ठा अणु
	काष्ठा list_head list;
	अक्षर *name;
	अक्षर *event;
	अक्षर *compat;
	अक्षर *desc;
	अक्षर *दीर्घ_desc;
	अक्षर *pmu;
	अक्षर *unit;
	अक्षर *perpkg;
	अक्षर *aggr_mode;
	अक्षर *metric_expr;
	अक्षर *metric_name;
	अक्षर *metric_group;
	अक्षर *deprecated;
	अक्षर *metric_स्थिरraपूर्णांक;
पूर्ण;

#घोषणा ADD_EVENT_FIELD(field) करो अणु अगर (je->field) अणु		\
	es->field = strdup(je->field);				\
	अगर (!es->field)						\
		जाओ out_मुक्त;					\
पूर्ण पूर्ण जबतक (0)

#घोषणा FREE_EVENT_FIELD(field) मुक्त(es->field)

#घोषणा TRY_FIXUP_FIELD(field) करो अणु अगर (es->field && !je->field) अणु\
	je->field = strdup(es->field);				\
	अगर (!je->field)						\
		वापस -ENOMEM;					\
पूर्ण पूर्ण जबतक (0)

#घोषणा FOR_ALL_EVENT_STRUCT_FIELDS(op) करो अणु			\
	op(name);						\
	op(event);						\
	op(desc);						\
	op(दीर्घ_desc);						\
	op(pmu);						\
	op(unit);						\
	op(perpkg);						\
	op(aggr_mode);						\
	op(metric_expr);					\
	op(metric_name);					\
	op(metric_group);					\
	op(deprecated);						\
पूर्ण जबतक (0)

अटल LIST_HEAD(arch_std_events);

अटल व्योम मुक्त_arch_std_events(व्योम)
अणु
	काष्ठा event_काष्ठा *es, *next;

	list_क्रम_each_entry_safe(es, next, &arch_std_events, list) अणु
		FOR_ALL_EVENT_STRUCT_FIELDS(FREE_EVENT_FIELD);
		list_del_init(&es->list);
		मुक्त(es);
	पूर्ण
पूर्ण

अटल पूर्णांक save_arch_std_events(व्योम *data, काष्ठा json_event *je)
अणु
	काष्ठा event_काष्ठा *es;

	es = दो_स्मृति(माप(*es));
	अगर (!es)
		वापस -ENOMEM;
	स_रखो(es, 0, माप(*es));
	FOR_ALL_EVENT_STRUCT_FIELDS(ADD_EVENT_FIELD);
	list_add_tail(&es->list, &arch_std_events);
	वापस 0;
out_मुक्त:
	FOR_ALL_EVENT_STRUCT_FIELDS(FREE_EVENT_FIELD);
	मुक्त(es);
	वापस -ENOMEM;
पूर्ण

अटल व्योम prपूर्णांक_events_table_suffix(खाता *outfp)
अणु
	ख_लिखो(outfp, "{\n");

	ख_लिखो(outfp, "\t.name = 0,\n");
	ख_लिखो(outfp, "\t.event = 0,\n");
	ख_लिखो(outfp, "\t.desc = 0,\n");

	ख_लिखो(outfp, "},\n");
	ख_लिखो(outfp, "};\n");
	बंद_table = 0;
पूर्ण

अटल काष्ठा fixed अणु
	स्थिर अक्षर *name;
	स्थिर अक्षर *event;
पूर्ण fixed[] = अणु
	अणु "inst_retired.any", "event=0xc0,period=2000003" पूर्ण,
	अणु "inst_retired.any_p", "event=0xc0,period=2000003" पूर्ण,
	अणु "cpu_clk_unhalted.ref", "event=0x0,umask=0x03,period=2000003" पूर्ण,
	अणु "cpu_clk_unhalted.thread", "event=0x3c,period=2000003" पूर्ण,
	अणु "cpu_clk_unhalted.core", "event=0x3c,period=2000003" पूर्ण,
	अणु "cpu_clk_unhalted.thread_any", "event=0x3c,any=1,period=2000003" पूर्ण,
	अणु शून्य, शून्यपूर्ण,
पूर्ण;

/*
 * Handle dअगरferent fixed counter encodings between JSON and perf.
 */
अटल अक्षर *real_event(स्थिर अक्षर *name, अक्षर *event)
अणु
	पूर्णांक i;

	अगर (!name)
		वापस शून्य;

	क्रम (i = 0; fixed[i].name; i++)
		अगर (!strहालcmp(name, fixed[i].name))
			वापस (अक्षर *)fixed[i].event;
	वापस event;
पूर्ण

अटल पूर्णांक
try_fixup(स्थिर अक्षर *fn, अक्षर *arch_std, काष्ठा json_event *je, अक्षर **event)
अणु
	/* try to find matching event from arch standard values */
	काष्ठा event_काष्ठा *es;

	list_क्रम_each_entry(es, &arch_std_events, list) अणु
		अगर (!म_भेद(arch_std, es->name)) अणु
			FOR_ALL_EVENT_STRUCT_FIELDS(TRY_FIXUP_FIELD);
			*event = je->event;
			वापस 0;
		पूर्ण
	पूर्ण

	pr_err("%s: could not find matching %s for %s\n",
					prog, arch_std, fn);
	वापस -1;
पूर्ण

/* Call func with each event in the json file */
अटल पूर्णांक json_events(स्थिर अक्षर *fn,
		पूर्णांक (*func)(व्योम *data, काष्ठा json_event *je),
			व्योम *data)
अणु
	पूर्णांक err;
	माप_प्रकार size;
	jsmntok_t *tokens, *tok;
	पूर्णांक i, j, len;
	अक्षर *map;
	अक्षर buf[128];

	अगर (!fn)
		वापस -ENOENT;

	tokens = parse_json(fn, &map, &size, &len);
	अगर (!tokens)
		वापस -EIO;
	EXPECT(tokens->type == JSMN_ARRAY, tokens, "expected top level array");
	tok = tokens + 1;
	क्रम (i = 0; i < tokens->size; i++) अणु
		अक्षर *event = शून्य;
		अक्षर *extra_desc = शून्य;
		अक्षर *filter = शून्य;
		काष्ठा json_event je = अणुपूर्ण;
		अक्षर *arch_std = शून्य;
		अचिन्हित दीर्घ दीर्घ eventcode = 0;
		काष्ठा msrmap *msr = शून्य;
		jsmntok_t *msrval = शून्य;
		jsmntok_t *precise = शून्य;
		jsmntok_t *obj = tok++;

		EXPECT(obj->type == JSMN_OBJECT, obj, "expected object");
		क्रम (j = 0; j < obj->size; j += 2) अणु
			jsmntok_t *field, *val;
			पूर्णांक nz;
			अक्षर *s;

			field = tok + j;
			EXPECT(field->type == JSMN_STRING, tok + j,
			       "Expected field name");
			val = tok + j + 1;
			EXPECT(val->type == JSMN_STRING, tok + j + 1,
			       "Expected string value");

			nz = !json_streq(map, val, "0");
			अगर (match_field(map, field, nz, &event, val)) अणु
				/* ok */
			पूर्ण अन्यथा अगर (json_streq(map, field, "EventCode")) अणु
				अक्षर *code = शून्य;
				addfield(map, &code, "", "", val);
				eventcode |= म_से_अदीर्घ(code, शून्य, 0);
				मुक्त(code);
			पूर्ण अन्यथा अगर (json_streq(map, field, "ExtSel")) अणु
				अक्षर *code = शून्य;
				addfield(map, &code, "", "", val);
				eventcode |= म_से_अदीर्घ(code, शून्य, 0) << 21;
				मुक्त(code);
			पूर्ण अन्यथा अगर (json_streq(map, field, "EventName")) अणु
				addfield(map, &je.name, "", "", val);
			पूर्ण अन्यथा अगर (json_streq(map, field, "Compat")) अणु
				addfield(map, &je.compat, "", "", val);
			पूर्ण अन्यथा अगर (json_streq(map, field, "BriefDescription")) अणु
				addfield(map, &je.desc, "", "", val);
				fixdesc(je.desc);
			पूर्ण अन्यथा अगर (json_streq(map, field,
					     "PublicDescription")) अणु
				addfield(map, &je.दीर्घ_desc, "", "", val);
				fixdesc(je.दीर्घ_desc);
			पूर्ण अन्यथा अगर (json_streq(map, field, "PEBS") && nz) अणु
				precise = val;
			पूर्ण अन्यथा अगर (json_streq(map, field, "MSRIndex") && nz) अणु
				msr = lookup_msr(map, val);
			पूर्ण अन्यथा अगर (json_streq(map, field, "MSRValue")) अणु
				msrval = val;
			पूर्ण अन्यथा अगर (json_streq(map, field, "Errata") &&
				   !json_streq(map, val, "null")) अणु
				addfield(map, &extra_desc, ". ",
					" Spec update: ", val);
			पूर्ण अन्यथा अगर (json_streq(map, field, "Data_LA") && nz) अणु
				addfield(map, &extra_desc, ". ",
					" Supports address when precise",
					शून्य);
			पूर्ण अन्यथा अगर (json_streq(map, field, "Unit")) अणु
				स्थिर अक्षर *ppmu;

				ppmu = field_to_perf(unit_to_pmu, map, val);
				अगर (ppmu) अणु
					je.pmu = strdup(ppmu);
				पूर्ण अन्यथा अणु
					अगर (!je.pmu)
						je.pmu = strdup("uncore_");
					addfield(map, &je.pmu, "", "", val);
					क्रम (s = je.pmu; *s; s++)
						*s = छोटे(*s);
				पूर्ण
				addfield(map, &je.desc, ". ", "Unit: ", शून्य);
				addfield(map, &je.desc, "", je.pmu, शून्य);
				addfield(map, &je.desc, "", " ", शून्य);
			पूर्ण अन्यथा अगर (json_streq(map, field, "Filter")) अणु
				addfield(map, &filter, "", "", val);
			पूर्ण अन्यथा अगर (json_streq(map, field, "ScaleUnit")) अणु
				addfield(map, &je.unit, "", "", val);
			पूर्ण अन्यथा अगर (json_streq(map, field, "PerPkg")) अणु
				addfield(map, &je.perpkg, "", "", val);
			पूर्ण अन्यथा अगर (json_streq(map, field, "AggregationMode")) अणु
				addfield(map, &je.aggr_mode, "", "", val);
			पूर्ण अन्यथा अगर (json_streq(map, field, "Deprecated")) अणु
				addfield(map, &je.deprecated, "", "", val);
			पूर्ण अन्यथा अगर (json_streq(map, field, "MetricName")) अणु
				addfield(map, &je.metric_name, "", "", val);
			पूर्ण अन्यथा अगर (json_streq(map, field, "MetricGroup")) अणु
				addfield(map, &je.metric_group, "", "", val);
			पूर्ण अन्यथा अगर (json_streq(map, field, "MetricConstraint")) अणु
				addfield(map, &je.metric_स्थिरraपूर्णांक, "", "", val);
			पूर्ण अन्यथा अगर (json_streq(map, field, "MetricExpr")) अणु
				addfield(map, &je.metric_expr, "", "", val);
				क्रम (s = je.metric_expr; *s; s++)
					*s = छोटे(*s);
			पूर्ण अन्यथा अगर (json_streq(map, field, "ArchStdEvent")) अणु
				addfield(map, &arch_std, "", "", val);
				क्रम (s = arch_std; *s; s++)
					*s = छोटे(*s);
			पूर्ण
			/* ignore unknown fields */
		पूर्ण
		अगर (precise && je.desc && !म_माला(je.desc, "(Precise Event)")) अणु
			अगर (json_streq(map, precise, "2"))
				addfield(map, &extra_desc, " ",
						"(Must be precise)", शून्य);
			अन्यथा
				addfield(map, &extra_desc, " ",
						"(Precise event)", शून्य);
		पूर्ण
		snम_लिखो(buf, माप buf, "event=%#llx", eventcode);
		addfield(map, &event, ",", buf, शून्य);
		अगर (je.desc && extra_desc)
			addfield(map, &je.desc, " ", extra_desc, शून्य);
		अगर (je.दीर्घ_desc && extra_desc)
			addfield(map, &je.दीर्घ_desc, " ", extra_desc, शून्य);
		अगर (filter)
			addfield(map, &event, ",", filter, शून्य);
		अगर (msr != शून्य)
			addfield(map, &event, ",", msr->pname, msrval);
		अगर (je.name)
			fixname(je.name);

		अगर (arch_std) अणु
			/*
			 * An arch standard event is referenced, so try to
			 * fixup any unasचिन्हित values.
			 */
			err = try_fixup(fn, arch_std, &je, &event);
			अगर (err)
				जाओ मुक्त_strings;
		पूर्ण
		je.event = real_event(je.name, event);
		err = func(data, &je);
मुक्त_strings:
		मुक्त(event);
		मुक्त(je.desc);
		मुक्त(je.name);
		मुक्त(je.compat);
		मुक्त(je.दीर्घ_desc);
		मुक्त(extra_desc);
		मुक्त(je.pmu);
		मुक्त(filter);
		मुक्त(je.perpkg);
		मुक्त(je.aggr_mode);
		मुक्त(je.deprecated);
		मुक्त(je.unit);
		मुक्त(je.metric_expr);
		मुक्त(je.metric_name);
		मुक्त(je.metric_group);
		मुक्त(je.metric_स्थिरraपूर्णांक);
		मुक्त(arch_std);

		अगर (err)
			अवरोध;
		tok += j;
	पूर्ण
	EXPECT(tok - tokens == len, tok, "unexpected objects at end");
	err = 0;
out_मुक्त:
	मुक्त_json(map, size, tokens);
	वापस err;
पूर्ण

अटल अक्षर *file_name_to_table_name(अक्षर *fname)
अणु
	अचिन्हित पूर्णांक i;
	पूर्णांक n;
	पूर्णांक c;
	अक्षर *tblname;

	/*
	 * Ensure tablename starts with alphabetic अक्षरacter.
	 * Derive rest of table name from basename of the JSON file,
	 * replacing hyphens and stripping out .json suffix.
	 */
	n = aप्र_लिखो(&tblname, "pme_%s", fname);
	अगर (n < 0) अणु
		pr_info("%s: asprintf() error %s for file %s\n", prog,
				म_त्रुटि(त्रुटि_सं), fname);
		वापस शून्य;
	पूर्ण

	क्रम (i = 0; i < म_माप(tblname); i++) अणु
		c = tblname[i];

		अगर (c == '-' || c == '/')
			tblname[i] = '_';
		अन्यथा अगर (c == '.') अणु
			tblname[i] = '\0';
			अवरोध;
		पूर्ण अन्यथा अगर (!है_अक्षर_अंक(c) && c != '_') अणु
			pr_err("%s: Invalid character '%c' in file name %s\n",
					prog, c, basename(fname));
			मुक्त(tblname);
			tblname = शून्य;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस tblname;
पूर्ण

अटल bool is_sys_dir(अक्षर *fname)
अणु
	माप_प्रकार len = म_माप(fname), len2 = म_माप("/sys");

	अगर (len2 > len)
		वापस false;
	वापस !म_भेद(fname+len-len2, "/sys");
पूर्ण

अटल व्योम prपूर्णांक_mapping_table_prefix(खाता *outfp)
अणु
	ख_लिखो(outfp, "struct pmu_events_map pmu_events_map[] = {\n");
पूर्ण

अटल व्योम prपूर्णांक_mapping_table_suffix(खाता *outfp)
अणु
	/*
	 * Prपूर्णांक the terminating, शून्य entry.
	 */
	ख_लिखो(outfp, "{\n");
	ख_लिखो(outfp, "\t.cpuid = 0,\n");
	ख_लिखो(outfp, "\t.version = 0,\n");
	ख_लिखो(outfp, "\t.type = 0,\n");
	ख_लिखो(outfp, "\t.table = 0,\n");
	ख_लिखो(outfp, "},\n");

	/* and finally, the closing curly bracket क्रम the काष्ठा */
	ख_लिखो(outfp, "};\n");
पूर्ण

अटल व्योम prपूर्णांक_mapping_test_table(खाता *outfp)
अणु
	/*
	 * Prपूर्णांक the terminating, शून्य entry.
	 */
	ख_लिखो(outfp, "{\n");
	ख_लिखो(outfp, "\t.cpuid = \"testcpu\",\n");
	ख_लिखो(outfp, "\t.version = \"v1\",\n");
	ख_लिखो(outfp, "\t.type = \"core\",\n");
	ख_लिखो(outfp, "\t.table = pme_test_cpu,\n");
	ख_लिखो(outfp, "},\n");
पूर्ण

अटल व्योम prपूर्णांक_प्रणाली_event_mapping_table_prefix(खाता *outfp)
अणु
	ख_लिखो(outfp, "\nstruct pmu_sys_events pmu_sys_event_tables[] = {");
पूर्ण

अटल व्योम prपूर्णांक_प्रणाली_event_mapping_table_suffix(खाता *outfp)
अणु
	ख_लिखो(outfp, "\n\t{\n\t\t.table = 0\n\t},");
	ख_लिखो(outfp, "\n};\n");
पूर्ण

अटल पूर्णांक process_प्रणाली_event_tables(खाता *outfp)
अणु
	काष्ठा sys_event_table *sys_event_table;

	prपूर्णांक_प्रणाली_event_mapping_table_prefix(outfp);

	list_क्रम_each_entry(sys_event_table, &sys_event_tables, list) अणु
		ख_लिखो(outfp, "\n\t{\n\t\t.table = %s,\n\t},",
			sys_event_table->soc_id);
	पूर्ण

	prपूर्णांक_प्रणाली_event_mapping_table_suffix(outfp);

	वापस 0;
पूर्ण

अटल पूर्णांक process_mapfile(खाता *outfp, अक्षर *fpath)
अणु
	पूर्णांक n = 16384;
	खाता *mapfp;
	अक्षर *save = शून्य;
	अक्षर *line, *p;
	पूर्णांक line_num;
	अक्षर *tblname;
	पूर्णांक ret = 0;

	pr_info("%s: Processing mapfile %s\n", prog, fpath);

	line = दो_स्मृति(n);
	अगर (!line)
		वापस -1;

	mapfp = ख_खोलो(fpath, "r");
	अगर (!mapfp) अणु
		pr_info("%s: Error %s opening %s\n", prog, म_त्रुटि(त्रुटि_सं),
				fpath);
		मुक्त(line);
		वापस -1;
	पूर्ण

	prपूर्णांक_mapping_table_prefix(outfp);

	/* Skip first line (header) */
	p = ख_माला_लो(line, n, mapfp);
	अगर (!p)
		जाओ out;

	line_num = 1;
	जबतक (1) अणु
		अक्षर *cpuid, *version, *type, *fname;

		line_num++;
		p = ख_माला_लो(line, n, mapfp);
		अगर (!p)
			अवरोध;

		अगर (line[0] == '#' || line[0] == '\n')
			जारी;

		अगर (line[म_माप(line)-1] != '\n') अणु
			/* TODO Deal with lines दीर्घer than 16K */
			pr_info("%s: Mapfile %s: line %d too long, aborting\n",
					prog, fpath, line_num);
			ret = -1;
			जाओ out;
		पूर्ण
		line[म_माप(line)-1] = '\0';

		cpuid = fixregex(म_मोहर_r(p, ",", &save));
		version = म_मोहर_r(शून्य, ",", &save);
		fname = म_मोहर_r(शून्य, ",", &save);
		type = म_मोहर_r(शून्य, ",", &save);

		tblname = file_name_to_table_name(fname);
		ख_लिखो(outfp, "{\n");
		ख_लिखो(outfp, "\t.cpuid = \"%s\",\n", cpuid);
		ख_लिखो(outfp, "\t.version = \"%s\",\n", version);
		ख_लिखो(outfp, "\t.type = \"%s\",\n", type);

		/*
		 * CHECK: We can't use the type (eg "core") field in the
		 * table name. For us to करो that, we need to somehow tweak
		 * the other caller of file_name_to_table(), process_json()
		 * to determine the type. process_json() file has no way
		 * of knowing these are "core" events unless file name has
		 * core in it. If filename has core in it, we can safely
		 * ignore the type field here also.
		 */
		ख_लिखो(outfp, "\t.table = %s\n", tblname);
		ख_लिखो(outfp, "},\n");
	पूर्ण

out:
	prपूर्णांक_mapping_test_table(outfp);
	prपूर्णांक_mapping_table_suffix(outfp);
	ख_बंद(mapfp);
	मुक्त(line);
	वापस ret;
पूर्ण

/*
 * If we fail to locate/process JSON and map files, create a शून्य mapping
 * table. This would at least allow perf to build even अगर we can't find/use
 * the aliases.
 */
अटल व्योम create_empty_mapping(स्थिर अक्षर *output_file)
अणु
	खाता *outfp;

	pr_info("%s: Creating empty pmu_events_map[] table\n", prog);

	/* Truncate file to clear any partial ग_लिखोs to it */
	outfp = ख_खोलो(output_file, "w");
	अगर (!outfp) अणु
		लिखो_त्रुटि("fopen()");
		_Exit(1);
	पूर्ण

	ख_लिखो(outfp, "#include \"pmu-events/pmu-events.h\"\n");
	prपूर्णांक_mapping_table_prefix(outfp);
	prपूर्णांक_mapping_table_suffix(outfp);
	prपूर्णांक_प्रणाली_event_mapping_table_prefix(outfp);
	prपूर्णांक_प्रणाली_event_mapping_table_suffix(outfp);
	ख_बंद(outfp);
पूर्ण

अटल पूर्णांक get_maxfds(व्योम)
अणु
	काष्ठा rlimit rlim;

	अगर (getrlimit(RLIMIT_NOखाता, &rlim) == 0)
		वापस min(rlim.rlim_max / 2, (rlim_t)512);

	वापस 512;
पूर्ण

/*
 * nftw() करोesn't let us pass an argument to the processing function,
 * so use a global variables.
 */
अटल खाता *eventsfp;
अटल अक्षर *mapfile;

अटल पूर्णांक is_leaf_dir(स्थिर अक्षर *fpath)
अणु
	सूची *d;
	काष्ठा dirent *dir;
	पूर्णांक res = 1;

	d = सूची_खोलो(fpath);
	अगर (!d)
		वापस 0;

	जबतक ((dir = सूची_पढ़ो(d)) != शून्य) अणु
		अगर (!म_भेद(dir->d_name, ".") || !म_भेद(dir->d_name, ".."))
			जारी;

		अगर (dir->d_type == DT_सूची) अणु
			res = 0;
			अवरोध;
		पूर्ण अन्यथा अगर (dir->d_type == DT_UNKNOWN) अणु
			अक्षर path[PATH_MAX];
			काष्ठा stat st;

			प्र_लिखो(path, "%s/%s", fpath, dir->d_name);
			अगर (stat(path, &st))
				अवरोध;

			अगर (S_ISसूची(st.st_mode)) अणु
				res = 0;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	बंद_सूची(d);

	वापस res;
पूर्ण

अटल पूर्णांक is_json_file(स्थिर अक्षर *name)
अणु
	स्थिर अक्षर *suffix;

	अगर (म_माप(name) < 5)
		वापस 0;

	suffix = name + म_माप(name) - 5;

	अगर (म_भेदन(suffix, ".json", 5) == 0)
		वापस 1;
	वापस 0;
पूर्ण

अटल पूर्णांक preprocess_arch_std_files(स्थिर अक्षर *fpath, स्थिर काष्ठा stat *sb,
				पूर्णांक typeflag, काष्ठा FTW *ftwbuf)
अणु
	पूर्णांक level = ftwbuf->level;
	पूर्णांक is_file = typeflag == FTW_F;

	अगर (level == 1 && is_file && is_json_file(fpath))
		वापस json_events(fpath, save_arch_std_events, (व्योम *)sb);

	वापस 0;
पूर्ण

अटल पूर्णांक process_one_file(स्थिर अक्षर *fpath, स्थिर काष्ठा stat *sb,
			    पूर्णांक typeflag, काष्ठा FTW *ftwbuf)
अणु
	अक्षर *tblname, *bname;
	पूर्णांक is_dir  = typeflag == FTW_D;
	पूर्णांक is_file = typeflag == FTW_F;
	पूर्णांक level   = ftwbuf->level;
	पूर्णांक err = 0;

	अगर (level >= 2 && is_dir) अणु
		पूर्णांक count = 0;
		/*
		 * For level 2 directory, bname will include parent name,
		 * like venकरोr/platक्रमm. So search back from platक्रमm dir
		 * to find this.
		 * Something similar क्रम level 3 directory, but we're a PMU
		 * category folder, like venकरोr/platक्रमm/cpu.
		 */
		bname = (अक्षर *) fpath + ftwbuf->base - 2;
		क्रम (;;) अणु
			अगर (*bname == '/')
				count++;
			अगर (count == level - 1)
				अवरोध;
			bname--;
		पूर्ण
		bname++;
	पूर्ण अन्यथा
		bname = (अक्षर *) fpath + ftwbuf->base;

	pr_debug("%s %d %7jd %-20s %s\n",
		 is_file ? "f" : is_dir ? "d" : "x",
		 level, sb->st_size, bname, fpath);

	/* base dir or too deep */
	अगर (level == 0 || level > 4)
		वापस 0;


	/* model directory, reset topic */
	अगर ((level == 1 && is_dir && is_leaf_dir(fpath)) ||
	    (level >= 2 && is_dir && is_leaf_dir(fpath))) अणु
		अगर (बंद_table)
			prपूर्णांक_events_table_suffix(eventsfp);

		/*
		 * Drop file name suffix. Replace hyphens with underscores.
		 * Fail अगर file name contains any alphanum अक्षरacters besides
		 * underscores.
		 */
		tblname = file_name_to_table_name(bname);
		अगर (!tblname) अणु
			pr_info("%s: Error determining table name for %s\n", prog,
				bname);
			वापस -1;
		पूर्ण

		अगर (is_sys_dir(bname)) अणु
			काष्ठा sys_event_table *sys_event_table;

			sys_event_table = दो_स्मृति(माप(*sys_event_table));
			अगर (!sys_event_table)
				वापस -1;

			sys_event_table->soc_id = strdup(tblname);
			अगर (!sys_event_table->soc_id) अणु
				मुक्त(sys_event_table);
				वापस -1;
			पूर्ण
			list_add_tail(&sys_event_table->list,
				      &sys_event_tables);
		पूर्ण

		prपूर्णांक_events_table_prefix(eventsfp, tblname);
		वापस 0;
	पूर्ण

	/*
	 * Save the mapfile name क्रम now. We will process mapfile
	 * after processing all JSON files (so we can ग_लिखो out the
	 * mapping table after all PMU events tables).
	 *
	 */
	अगर (level == 1 && is_file) अणु
		अगर (!म_भेद(bname, "mapfile.csv")) अणु
			mapfile = strdup(fpath);
			वापस 0;
		पूर्ण
		अगर (is_json_file(bname))
			pr_debug("%s: ArchStd json is preprocessed %s\n", prog, fpath);
		अन्यथा
			pr_info("%s: Ignoring file %s\n", prog, fpath);
		वापस 0;
	पूर्ण

	/*
	 * If the file name करोes not have a .json extension,
	 * ignore it. It could be a पढ़ोme.txt क्रम instance.
	 */
	अगर (is_file) अणु
		अगर (!is_json_file(bname)) अणु
			pr_info("%s: Ignoring file without .json suffix %s\n", prog,
				fpath);
			वापस 0;
		पूर्ण
	पूर्ण

	अगर (level > 1 && add_topic(bname))
		वापस -ENOMEM;

	/*
	 * Assume all other files are JSON files.
	 *
	 * If mapfile refers to 'power7_core.json', we create a table
	 * named 'power7_core'. Any inconsistencies between the mapfile
	 * and directory tree could result in build failure due to table
	 * names not being found.
	 *
	 * At least क्रम now, be strict with processing JSON file names.
	 * i.e. अगर JSON file name cannot be mapped to C-style table name,
	 * fail.
	 */
	अगर (is_file) अणु
		काष्ठा perf_entry_data data = अणु
			.topic = get_topic(),
			.outfp = eventsfp,
		पूर्ण;

		err = json_events(fpath, prपूर्णांक_events_table_entry, &data);

		मुक्त(data.topic);
	पूर्ण

	वापस err;
पूर्ण

#अगर_अघोषित PATH_MAX
#घोषणा PATH_MAX	4096
#पूर्ण_अगर

/*
 * Starting in directory 'start_dirname', find the "mapfile.csv" and
 * the set of JSON files क्रम the architecture 'arch'.
 *
 * From each JSON file, create a C-style "PMU events table" from the
 * JSON file (see काष्ठा pmu_event).
 *
 * From the mapfile, create a mapping between the CPU revisions and
 * PMU event tables (see काष्ठा pmu_events_map).
 *
 * Write out the PMU events tables and the mapping table to pmu-event.c.
 */
पूर्णांक मुख्य(पूर्णांक argc, अक्षर *argv[])
अणु
	पूर्णांक rc, ret = 0, empty_map = 0;
	पूर्णांक maxfds;
	अक्षर lस_नाम[PATH_MAX];
	स्थिर अक्षर *arch;
	स्थिर अक्षर *output_file;
	स्थिर अक्षर *start_स_नाम;
	अक्षर *err_string_ext = "";
	काष्ठा stat stbuf;

	prog = basename(argv[0]);
	अगर (argc < 4) अणु
		pr_err("Usage: %s <arch> <starting_dir> <output_file>\n", prog);
		वापस 1;
	पूर्ण

	arch = argv[1];
	start_स_नाम = argv[2];
	output_file = argv[3];

	अगर (argc > 4)
		verbose = म_से_प(argv[4]);

	eventsfp = ख_खोलो(output_file, "w");
	अगर (!eventsfp) अणु
		pr_err("%s Unable to create required file %s (%s)\n",
				prog, output_file, म_त्रुटि(त्रुटि_सं));
		वापस 2;
	पूर्ण

	प्र_लिखो(lस_नाम, "%s/%s", start_स_नाम, arch);

	/* If architecture करोes not have any event lists, bail out */
	अगर (stat(lस_नाम, &stbuf) < 0) अणु
		pr_info("%s: Arch %s has no PMU event lists\n", prog, arch);
		empty_map = 1;
		जाओ err_बंद_eventsfp;
	पूर्ण

	/* Include pmu-events.h first */
	ख_लिखो(eventsfp, "#include \"pmu-events/pmu-events.h\"\n");

	/*
	 * The mapfile allows multiple CPUids to poपूर्णांक to the same JSON file,
	 * so, not sure अगर there is a need क्रम symlinks within the pmu-events
	 * directory.
	 *
	 * For now, treat symlinks of JSON files as regular files and create
	 * separate tables क्रम each symlink (presumably, each symlink refers
	 * to specअगरic version of the CPU).
	 */

	maxfds = get_maxfds();
	rc = nftw(lस_नाम, preprocess_arch_std_files, maxfds, 0);
	अगर (rc)
		जाओ err_processing_std_arch_event_dir;

	rc = nftw(lस_नाम, process_one_file, maxfds, 0);
	अगर (rc)
		जाओ err_processing_dir;

	प्र_लिखो(lस_नाम, "%s/test", start_स_नाम);

	rc = nftw(lस_नाम, preprocess_arch_std_files, maxfds, 0);
	अगर (rc)
		जाओ err_processing_std_arch_event_dir;

	rc = nftw(lस_नाम, process_one_file, maxfds, 0);
	अगर (rc)
		जाओ err_processing_dir;

	अगर (बंद_table)
		prपूर्णांक_events_table_suffix(eventsfp);

	अगर (!mapfile) अणु
		pr_info("%s: No CPU->JSON mapping?\n", prog);
		empty_map = 1;
		जाओ err_बंद_eventsfp;
	पूर्ण

	rc = process_mapfile(eventsfp, mapfile);
	अगर (rc) अणु
		pr_info("%s: Error processing mapfile %s\n", prog, mapfile);
		/* Make build fail */
		ret = 1;
		जाओ err_बंद_eventsfp;
	पूर्ण

	rc = process_प्रणाली_event_tables(eventsfp);
	ख_बंद(eventsfp);
	अगर (rc) अणु
		ret = 1;
		जाओ err_out;
	पूर्ण

	मुक्त_arch_std_events();
	मुक्त(mapfile);
	वापस 0;

err_processing_std_arch_event_dir:
	err_string_ext = " for std arch event";
err_processing_dir:
	अगर (verbose) अणु
		pr_info("%s: Error walking file tree %s%s\n", prog, lस_नाम,
			err_string_ext);
		empty_map = 1;
	पूर्ण अन्यथा अगर (rc < 0) अणु
		ret = 1;
	पूर्ण अन्यथा अणु
		empty_map = 1;
	पूर्ण
err_बंद_eventsfp:
	ख_बंद(eventsfp);
	अगर (empty_map)
		create_empty_mapping(output_file);
err_out:
	मुक्त_arch_std_events();
	मुक्त(mapfile);
	वापस ret;
पूर्ण
