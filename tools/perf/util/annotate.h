<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __PERF_ANNOTATE_H
#घोषणा __PERF_ANNOTATE_H

#समावेश <stdbool.h>
#समावेश <मानक_निवेशt.h>
#समावेश <मानकपन.स>
#समावेश <linux/types.h>
#समावेश <linux/list.h>
#समावेश <linux/rbtree.h>
#समावेश <pthपढ़ो.h>
#समावेश <यंत्र/bug.h>
#समावेश "symbol_conf.h"
#समावेश "spark.h"

काष्ठा hist_browser_समयr;
काष्ठा hist_entry;
काष्ठा ins_ops;
काष्ठा map;
काष्ठा map_symbol;
काष्ठा addr_map_symbol;
काष्ठा option;
काष्ठा perf_sample;
काष्ठा evsel;
काष्ठा symbol;

काष्ठा ins अणु
	स्थिर अक्षर     *name;
	काष्ठा ins_ops *ops;
पूर्ण;

काष्ठा ins_opeअक्रमs अणु
	अक्षर	*raw;
	अक्षर	*raw_comment;
	अक्षर	*raw_func_start;
	काष्ठा अणु
		अक्षर	*raw;
		अक्षर	*name;
		काष्ठा symbol *sym;
		u64	addr;
		s64	offset;
		bool	offset_avail;
		bool	outside;
	पूर्ण target;
	जोड़ अणु
		काष्ठा अणु
			अक्षर	*raw;
			अक्षर	*name;
			u64	addr;
		पूर्ण source;
		काष्ठा अणु
			काष्ठा ins	    ins;
			काष्ठा ins_opeअक्रमs *ops;
		पूर्ण locked;
	पूर्ण;
पूर्ण;

काष्ठा arch;

काष्ठा ins_ops अणु
	व्योम (*मुक्त)(काष्ठा ins_opeअक्रमs *ops);
	पूर्णांक (*parse)(काष्ठा arch *arch, काष्ठा ins_opeअक्रमs *ops, काष्ठा map_symbol *ms);
	पूर्णांक (*scnम_लिखो)(काष्ठा ins *ins, अक्षर *bf, माप_प्रकार size,
			 काष्ठा ins_opeअक्रमs *ops, पूर्णांक max_ins_name);
पूर्ण;

bool ins__is_jump(स्थिर काष्ठा ins *ins);
bool ins__is_call(स्थिर काष्ठा ins *ins);
bool ins__is_ret(स्थिर काष्ठा ins *ins);
bool ins__is_lock(स्थिर काष्ठा ins *ins);
पूर्णांक ins__scnम_लिखो(काष्ठा ins *ins, अक्षर *bf, माप_प्रकार size, काष्ठा ins_opeअक्रमs *ops, पूर्णांक max_ins_name);
bool ins__is_fused(काष्ठा arch *arch, स्थिर अक्षर *ins1, स्थिर अक्षर *ins2);

#घोषणा ANNOTATION__IPC_WIDTH 6
#घोषणा ANNOTATION__CYCLES_WIDTH 6
#घोषणा ANNOTATION__MINMAX_CYCLES_WIDTH 19
#घोषणा ANNOTATION__AVG_IPC_WIDTH 36
#घोषणा ANNOTATION_DUMMY_LEN	256

काष्ठा annotation_options अणु
	bool hide_src_code,
	     use_offset,
	     jump_arrows,
	     prपूर्णांक_lines,
	     full_path,
	     show_linenr,
	     show_fileloc,
	     show_nr_jumps,
	     show_minmax_cycle,
	     show_यंत्र_raw,
	     annotate_src;
	u8   offset_level;
	पूर्णांक  min_pcnt;
	पूर्णांक  max_lines;
	पूर्णांक  context;
	स्थिर अक्षर *objdump_path;
	स्थिर अक्षर *disassembler_style;
	स्थिर अक्षर *prefix;
	स्थिर अक्षर *prefix_strip;
	अचिन्हित पूर्णांक percent_type;
पूर्ण;

क्रमागत अणु
	ANNOTATION__OFFSET_JUMP_TARGETS = 1,
	ANNOTATION__OFFSET_CALL,
	ANNOTATION__MAX_OFFSET_LEVEL,
पूर्ण;

#घोषणा ANNOTATION__MIN_OFFSET_LEVEL ANNOTATION__OFFSET_JUMP_TARGETS

बाह्य काष्ठा annotation_options annotation__शेष_options;

काष्ठा annotation;

काष्ठा sym_hist_entry अणु
	u64		nr_samples;
	u64		period;
पूर्ण;

क्रमागत अणु
	PERCENT_HITS_LOCAL,
	PERCENT_HITS_GLOBAL,
	PERCENT_PERIOD_LOCAL,
	PERCENT_PERIOD_GLOBAL,
	PERCENT_MAX,
पूर्ण;

काष्ठा annotation_data अणु
	द्विगुन			 percent[PERCENT_MAX];
	द्विगुन			 percent_sum;
	काष्ठा sym_hist_entry	 he;
पूर्ण;

काष्ठा annotation_line अणु
	काष्ठा list_head	 node;
	काष्ठा rb_node		 rb_node;
	s64			 offset;
	अक्षर			*line;
	पूर्णांक			 line_nr;
	अक्षर			*fileloc;
	पूर्णांक			 jump_sources;
	भग्न			 ipc;
	u64			 cycles;
	u64			 cycles_max;
	u64			 cycles_min;
	अक्षर			*path;
	u32			 idx;
	पूर्णांक			 idx_यंत्र;
	पूर्णांक			 data_nr;
	काष्ठा annotation_data	 data[];
पूर्ण;

काष्ठा disयंत्र_line अणु
	काष्ठा ins		 ins;
	काष्ठा ins_opeअक्रमs	 ops;

	/* This needs to be at the end. */
	काष्ठा annotation_line	 al;
पूर्ण;

अटल अंतरभूत द्विगुन annotation_data__percent(काष्ठा annotation_data *data,
					      अचिन्हित पूर्णांक which)
अणु
	वापस which < PERCENT_MAX ? data->percent[which] : -1;
पूर्ण

अटल अंतरभूत स्थिर अक्षर *percent_type_str(अचिन्हित पूर्णांक type)
अणु
	अटल स्थिर अक्षर *str[PERCENT_MAX] = अणु
		"local hits",
		"global hits",
		"local period",
		"global period",
	पूर्ण;

	अगर (WARN_ON(type >= PERCENT_MAX))
		वापस "N/A";

	वापस str[type];
पूर्ण

अटल अंतरभूत काष्ठा disयंत्र_line *disयंत्र_line(काष्ठा annotation_line *al)
अणु
	वापस al ? container_of(al, काष्ठा disयंत्र_line, al) : शून्य;
पूर्ण

/*
 * Is this offset in the same function as the line it is used?
 * यंत्र functions jump to other functions, क्रम instance.
 */
अटल अंतरभूत bool disयंत्र_line__has_local_offset(स्थिर काष्ठा disयंत्र_line *dl)
अणु
	वापस dl->ops.target.offset_avail && !dl->ops.target.outside;
पूर्ण

/*
 * Can we draw an arrow from the jump to its target, क्रम instance? I.e.
 * is the jump and its target in the same function?
 */
bool disयंत्र_line__is_valid_local_jump(काष्ठा disयंत्र_line *dl, काष्ठा symbol *sym);

व्योम disयंत्र_line__मुक्त(काष्ठा disयंत्र_line *dl);
काष्ठा annotation_line *
annotation_line__next(काष्ठा annotation_line *pos, काष्ठा list_head *head);

काष्ठा annotation_ग_लिखो_ops अणु
	bool first_line, current_entry, change_color;
	पूर्णांक  width;
	व्योम *obj;
	पूर्णांक  (*set_color)(व्योम *obj, पूर्णांक color);
	व्योम (*set_percent_color)(व्योम *obj, द्विगुन percent, bool current);
	पूर्णांक  (*set_jumps_percent_color)(व्योम *obj, पूर्णांक nr, bool current);
	व्योम (*म_लिखो)(व्योम *obj, स्थिर अक्षर *fmt, ...);
	व्योम (*ग_लिखो_graph)(व्योम *obj, पूर्णांक graph);
पूर्ण;

व्योम annotation_line__ग_लिखो(काष्ठा annotation_line *al, काष्ठा annotation *notes,
			    काष्ठा annotation_ग_लिखो_ops *ops,
			    काष्ठा annotation_options *opts);

पूर्णांक __annotation__scnम_लिखो_samples_period(काष्ठा annotation *notes,
					   अक्षर *bf, माप_प्रकार size,
					   काष्ठा evsel *evsel,
					   bool show_freq);

पूर्णांक disयंत्र_line__scnम_लिखो(काष्ठा disयंत्र_line *dl, अक्षर *bf, माप_प्रकार size, bool raw, पूर्णांक max_ins_name);
माप_प्रकार disयंत्र__ख_लिखो(काष्ठा list_head *head, खाता *fp);
व्योम symbol__calc_percent(काष्ठा symbol *sym, काष्ठा evsel *evsel);

काष्ठा sym_hist अणु
	u64		      nr_samples;
	u64		      period;
	काष्ठा sym_hist_entry addr[];
पूर्ण;

काष्ठा cyc_hist अणु
	u64	start;
	u64	cycles;
	u64	cycles_aggr;
	u64	cycles_max;
	u64	cycles_min;
	s64	cycles_spark[NUM_SPARKS];
	u32	num;
	u32	num_aggr;
	u8	have_start;
	/* 1 byte padding */
	u16	reset;
पूर्ण;

/** काष्ठा annotated_source - symbols with hits have this attached as in sannotation
 *
 * @histograms: Array of addr hit histograms per event being monitored
 * nr_histograms: This may not be the same as evsel->evlist->core.nr_entries अगर
 * 		  we have more than a group in a evlist, where we will want
 * 		  to see each group separately, that is why symbol__annotate2()
 * 		  sets src->nr_histograms to evsel->nr_members.
 * @lines: If 'print_lines' is specअगरied, per source code line percentages
 * @source: source parsed from a disassembler like objdump -dS
 * @cyc_hist: Average cycles per basic block
 *
 * lines is allocated, percentages calculated and all sorted by percentage
 * when the annotation is about to be presented, so the percentages are क्रम
 * one of the entries in the histogram array, i.e. क्रम the event/counter being
 * presented. It is deallocated right after symbol__अणुtui,tty,etcपूर्ण_annotate
 * वापसs.
 */
काष्ठा annotated_source अणु
	काष्ठा list_head   source;
	पूर्णांक    		   nr_histograms;
	माप_प्रकार		   माप_sym_hist;
	काष्ठा cyc_hist	   *cycles_hist;
	काष्ठा sym_hist	   *histograms;
पूर्ण;

काष्ठा annotation अणु
	pthपढ़ो_mutex_t		lock;
	u64			max_coverage;
	u64			start;
	u64			hit_cycles;
	u64			hit_insn;
	अचिन्हित पूर्णांक		total_insn;
	अचिन्हित पूर्णांक		cover_insn;
	काष्ठा annotation_options *options;
	काष्ठा annotation_line	**offsets;
	पूर्णांक			nr_events;
	पूर्णांक			max_jump_sources;
	पूर्णांक			nr_entries;
	पूर्णांक			nr_यंत्र_entries;
	u16			max_line_len;
	काष्ठा अणु
		u8		addr;
		u8		jumps;
		u8		target;
		u8		min_addr;
		u8		max_addr;
		u8		max_ins_name;
	पूर्ण widths;
	bool			have_cycles;
	काष्ठा annotated_source *src;
पूर्ण;

अटल अंतरभूत पूर्णांक annotation__cycles_width(काष्ठा annotation *notes)
अणु
	अगर (notes->have_cycles && notes->options->show_minmax_cycle)
		वापस ANNOTATION__IPC_WIDTH + ANNOTATION__MINMAX_CYCLES_WIDTH;

	वापस notes->have_cycles ? ANNOTATION__IPC_WIDTH + ANNOTATION__CYCLES_WIDTH : 0;
पूर्ण

अटल अंतरभूत पूर्णांक annotation__pcnt_width(काष्ठा annotation *notes)
अणु
	वापस (symbol_conf.show_total_period ? 12 : 7) * notes->nr_events;
पूर्ण

अटल अंतरभूत bool annotation_line__filter(काष्ठा annotation_line *al, काष्ठा annotation *notes)
अणु
	वापस notes->options->hide_src_code && al->offset == -1;
पूर्ण

व्योम annotation__set_offsets(काष्ठा annotation *notes, s64 size);
व्योम annotation__compute_ipc(काष्ठा annotation *notes, माप_प्रकार size);
व्योम annotation__mark_jump_tarमाला_लो(काष्ठा annotation *notes, काष्ठा symbol *sym);
व्योम annotation__update_column_widths(काष्ठा annotation *notes);
व्योम annotation__init_column_widths(काष्ठा annotation *notes, काष्ठा symbol *sym);

अटल अंतरभूत काष्ठा sym_hist *annotated_source__histogram(काष्ठा annotated_source *src, पूर्णांक idx)
अणु
	वापस ((व्योम *)src->histograms) + (src->माप_sym_hist * idx);
पूर्ण

अटल अंतरभूत काष्ठा sym_hist *annotation__histogram(काष्ठा annotation *notes, पूर्णांक idx)
अणु
	वापस annotated_source__histogram(notes->src, idx);
पूर्ण

अटल अंतरभूत काष्ठा annotation *symbol__annotation(काष्ठा symbol *sym)
अणु
	वापस (व्योम *)sym - symbol_conf.priv_size;
पूर्ण

पूर्णांक addr_map_symbol__inc_samples(काष्ठा addr_map_symbol *ams, काष्ठा perf_sample *sample,
				 काष्ठा evsel *evsel);

पूर्णांक addr_map_symbol__account_cycles(काष्ठा addr_map_symbol *ams,
				    काष्ठा addr_map_symbol *start,
				    अचिन्हित cycles);

पूर्णांक hist_entry__inc_addr_samples(काष्ठा hist_entry *he, काष्ठा perf_sample *sample,
				 काष्ठा evsel *evsel, u64 addr);

काष्ठा annotated_source *symbol__hists(काष्ठा symbol *sym, पूर्णांक nr_hists);
व्योम symbol__annotate_zero_histograms(काष्ठा symbol *sym);

पूर्णांक symbol__annotate(काष्ठा map_symbol *ms,
		     काष्ठा evsel *evsel,
		     काष्ठा annotation_options *options,
		     काष्ठा arch **parch);
पूर्णांक symbol__annotate2(काष्ठा map_symbol *ms,
		      काष्ठा evsel *evsel,
		      काष्ठा annotation_options *options,
		      काष्ठा arch **parch);

क्रमागत symbol_disassemble_त्रुटि_सं अणु
	SYMBOL_ANNOTATE_ERRNO__SUCCESS		= 0,

	/*
	 * Choose an arbitrary negative big number not to clash with standard
	 * त्रुटि_सं since SUS requires the त्रुटि_सं has distinct positive values.
	 * See 'Issue 6' in the link below.
	 *
	 * http://pubs.खोलोgroup.org/onlinepubs/9699919799/basedefs/त्रुटिसं.स.hपंचांगl
	 */
	__SYMBOL_ANNOTATE_ERRNO__START		= -10000,

	SYMBOL_ANNOTATE_ERRNO__NO_VMLINUX	= __SYMBOL_ANNOTATE_ERRNO__START,
	SYMBOL_ANNOTATE_ERRNO__NO_LIBOPCODES_FOR_BPF,
	SYMBOL_ANNOTATE_ERRNO__ARCH_INIT_CPUID_PARSING,
	SYMBOL_ANNOTATE_ERRNO__ARCH_INIT_REGEXP,
	SYMBOL_ANNOTATE_ERRNO__BPF_INVALID_खाता,
	SYMBOL_ANNOTATE_ERRNO__BPF_MISSING_BTF,

	__SYMBOL_ANNOTATE_ERRNO__END,
पूर्ण;

पूर्णांक symbol__म_त्रुटि_disassemble(काष्ठा map_symbol *ms, पूर्णांक errnum, अक्षर *buf, माप_प्रकार buflen);

पूर्णांक symbol__annotate_म_लिखो(काष्ठा map_symbol *ms, काष्ठा evsel *evsel,
			    काष्ठा annotation_options *options);
व्योम symbol__annotate_zero_histogram(काष्ठा symbol *sym, पूर्णांक evidx);
व्योम symbol__annotate_decay_histogram(काष्ठा symbol *sym, पूर्णांक evidx);
व्योम annotated_source__purge(काष्ठा annotated_source *as);

पूर्णांक map_symbol__annotation_dump(काष्ठा map_symbol *ms, काष्ठा evsel *evsel,
				काष्ठा annotation_options *opts);

bool ui__has_annotation(व्योम);

पूर्णांक symbol__tty_annotate(काष्ठा map_symbol *ms, काष्ठा evsel *evsel, काष्ठा annotation_options *opts);

पूर्णांक symbol__tty_annotate2(काष्ठा map_symbol *ms, काष्ठा evsel *evsel, काष्ठा annotation_options *opts);

#अगर_घोषित HAVE_SLANG_SUPPORT
पूर्णांक symbol__tui_annotate(काष्ठा map_symbol *ms, काष्ठा evsel *evsel,
			 काष्ठा hist_browser_समयr *hbt,
			 काष्ठा annotation_options *opts);
#अन्यथा
अटल अंतरभूत पूर्णांक symbol__tui_annotate(काष्ठा map_symbol *ms __maybe_unused,
				काष्ठा evsel *evsel  __maybe_unused,
				काष्ठा hist_browser_समयr *hbt __maybe_unused,
				काष्ठा annotation_options *opts __maybe_unused)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

व्योम annotation_config__init(काष्ठा annotation_options *opt);

पूर्णांक annotate_parse_percent_type(स्थिर काष्ठा option *opt, स्थिर अक्षर *_str,
				पूर्णांक unset);

पूर्णांक annotate_check_args(काष्ठा annotation_options *args);

#पूर्ण_अगर	/* __PERF_ANNOTATE_H */
