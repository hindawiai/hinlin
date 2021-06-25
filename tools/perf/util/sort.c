<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <त्रुटिसं.स>
#समावेश <पूर्णांकtypes.h>
#समावेश <regex.h>
#समावेश <मानककोष.स>
#समावेश <linux/mman.h>
#समावेश <linux/समय64.h>
#समावेश "debug.h"
#समावेश "dso.h"
#समावेश "sort.h"
#समावेश "hist.h"
#समावेश "cacheline.h"
#समावेश "comm.h"
#समावेश "map.h"
#समावेश "maps.h"
#समावेश "symbol.h"
#समावेश "map_symbol.h"
#समावेश "branch.h"
#समावेश "thread.h"
#समावेश "evsel.h"
#समावेश "evlist.h"
#समावेश "srcline.h"
#समावेश "strlist.h"
#समावेश "strbuf.h"
#समावेश <traceevent/event-parse.h>
#समावेश "mem-events.h"
#समावेश "annotate.h"
#समावेश "event.h"
#समावेश "time-utils.h"
#समावेश "cgroup.h"
#समावेश "machine.h"
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>

regex_t		parent_regex;
स्थिर अक्षर	शेष_parent_pattern[] = "^sys_|^करो_page_fault";
स्थिर अक्षर	*parent_pattern = शेष_parent_pattern;
स्थिर अक्षर	*शेष_sort_order = "comm,dso,symbol";
स्थिर अक्षर	शेष_branch_sort_order[] = "comm,dso_from,symbol_from,symbol_to,cycles";
स्थिर अक्षर	शेष_mem_sort_order[] = "local_weight,mem,sym,dso,symbol_daddr,dso_daddr,snoop,tlb,locked,blocked,local_ins_lat,p_stage_cyc";
स्थिर अक्षर	शेष_top_sort_order[] = "dso,symbol";
स्थिर अक्षर	शेष_dअगरf_sort_order[] = "dso,symbol";
स्थिर अक्षर	शेष_tracepoपूर्णांक_sort_order[] = "trace";
स्थिर अक्षर	*sort_order;
स्थिर अक्षर	*field_order;
regex_t		ignore_callees_regex;
पूर्णांक		have_ignore_callees = 0;
क्रमागत sort_mode	sort__mode = SORT_MODE__NORMAL;
स्थिर अक्षर	*dynamic_headers[] = अणु"local_ins_lat", "p_stage_cyc"पूर्ण;
स्थिर अक्षर	*arch_specअगरic_sort_keys[] = अणु"p_stage_cyc"पूर्ण;

/*
 * Replaces all occurrences of a अक्षर used with the:
 *
 * -t, --field-separator
 *
 * option, that uses a special separator अक्षरacter and करोn't pad with spaces,
 * replacing all occurrences of this separator in symbol names (and other
 * output) with a '.' character, that thus it's the only non valid separator.
*/
अटल पूर्णांक repsep_snम_लिखो(अक्षर *bf, माप_प्रकार size, स्थिर अक्षर *fmt, ...)
अणु
	पूर्णांक n;
	बहु_सूची ap;

	बहु_शुरू(ap, fmt);
	n = vsnम_लिखो(bf, size, fmt, ap);
	अगर (symbol_conf.field_sep && n > 0) अणु
		अक्षर *sep = bf;

		जबतक (1) अणु
			sep = म_अक्षर(sep, *symbol_conf.field_sep);
			अगर (sep == शून्य)
				अवरोध;
			*sep = '.';
		पूर्ण
	पूर्ण
	बहु_पूर्ण(ap);

	अगर (n >= (पूर्णांक)size)
		वापस size - 1;
	वापस n;
पूर्ण

अटल पूर्णांक64_t cmp_null(स्थिर व्योम *l, स्थिर व्योम *r)
अणु
	अगर (!l && !r)
		वापस 0;
	अन्यथा अगर (!l)
		वापस -1;
	अन्यथा
		वापस 1;
पूर्ण

/* --sort pid */

अटल पूर्णांक64_t
sort__thपढ़ो_cmp(काष्ठा hist_entry *left, काष्ठा hist_entry *right)
अणु
	वापस right->thपढ़ो->tid - left->thपढ़ो->tid;
पूर्ण

अटल पूर्णांक hist_entry__thपढ़ो_snम_लिखो(काष्ठा hist_entry *he, अक्षर *bf,
				       माप_प्रकार size, अचिन्हित पूर्णांक width)
अणु
	स्थिर अक्षर *comm = thपढ़ो__comm_str(he->thपढ़ो);

	width = max(7U, width) - 8;
	वापस repsep_snम_लिखो(bf, size, "%7d:%-*.*s", he->thपढ़ो->tid,
			       width, width, comm ?: "");
पूर्ण

अटल पूर्णांक hist_entry__thपढ़ो_filter(काष्ठा hist_entry *he, पूर्णांक type, स्थिर व्योम *arg)
अणु
	स्थिर काष्ठा thपढ़ो *th = arg;

	अगर (type != HIST_FILTER__THREAD)
		वापस -1;

	वापस th && he->thपढ़ो != th;
पूर्ण

काष्ठा sort_entry sort_thपढ़ो = अणु
	.se_header	= "    Pid:Command",
	.se_cmp		= sort__thपढ़ो_cmp,
	.se_snम_लिखो	= hist_entry__thपढ़ो_snम_लिखो,
	.se_filter	= hist_entry__thपढ़ो_filter,
	.se_width_idx	= HISTC_THREAD,
पूर्ण;

/* --sort comm */

/*
 * We can't use poपूर्णांकer comparison in functions below,
 * because it gives dअगरferent results based on poपूर्णांकer
 * values, which could अवरोध some sorting assumptions.
 */
अटल पूर्णांक64_t
sort__comm_cmp(काष्ठा hist_entry *left, काष्ठा hist_entry *right)
अणु
	वापस म_भेद(comm__str(right->comm), comm__str(left->comm));
पूर्ण

अटल पूर्णांक64_t
sort__comm_collapse(काष्ठा hist_entry *left, काष्ठा hist_entry *right)
अणु
	वापस म_भेद(comm__str(right->comm), comm__str(left->comm));
पूर्ण

अटल पूर्णांक64_t
sort__comm_sort(काष्ठा hist_entry *left, काष्ठा hist_entry *right)
अणु
	वापस म_भेद(comm__str(right->comm), comm__str(left->comm));
पूर्ण

अटल पूर्णांक hist_entry__comm_snम_लिखो(काष्ठा hist_entry *he, अक्षर *bf,
				     माप_प्रकार size, अचिन्हित पूर्णांक width)
अणु
	वापस repsep_snम_लिखो(bf, size, "%-*.*s", width, width, comm__str(he->comm));
पूर्ण

काष्ठा sort_entry sort_comm = अणु
	.se_header	= "Command",
	.se_cmp		= sort__comm_cmp,
	.se_collapse	= sort__comm_collapse,
	.se_sort	= sort__comm_sort,
	.se_snम_लिखो	= hist_entry__comm_snम_लिखो,
	.se_filter	= hist_entry__thपढ़ो_filter,
	.se_width_idx	= HISTC_COMM,
पूर्ण;

/* --sort dso */

अटल पूर्णांक64_t _sort__dso_cmp(काष्ठा map *map_l, काष्ठा map *map_r)
अणु
	काष्ठा dso *dso_l = map_l ? map_l->dso : शून्य;
	काष्ठा dso *dso_r = map_r ? map_r->dso : शून्य;
	स्थिर अक्षर *dso_name_l, *dso_name_r;

	अगर (!dso_l || !dso_r)
		वापस cmp_null(dso_r, dso_l);

	अगर (verbose > 0) अणु
		dso_name_l = dso_l->दीर्घ_name;
		dso_name_r = dso_r->दीर्घ_name;
	पूर्ण अन्यथा अणु
		dso_name_l = dso_l->लघु_name;
		dso_name_r = dso_r->लघु_name;
	पूर्ण

	वापस म_भेद(dso_name_l, dso_name_r);
पूर्ण

अटल पूर्णांक64_t
sort__dso_cmp(काष्ठा hist_entry *left, काष्ठा hist_entry *right)
अणु
	वापस _sort__dso_cmp(right->ms.map, left->ms.map);
पूर्ण

अटल पूर्णांक _hist_entry__dso_snम_लिखो(काष्ठा map *map, अक्षर *bf,
				     माप_प्रकार size, अचिन्हित पूर्णांक width)
अणु
	अगर (map && map->dso) अणु
		स्थिर अक्षर *dso_name = verbose > 0 ? map->dso->दीर्घ_name :
			map->dso->लघु_name;
		वापस repsep_snम_लिखो(bf, size, "%-*.*s", width, width, dso_name);
	पूर्ण

	वापस repsep_snम_लिखो(bf, size, "%-*.*s", width, width, "[unknown]");
पूर्ण

अटल पूर्णांक hist_entry__dso_snम_लिखो(काष्ठा hist_entry *he, अक्षर *bf,
				    माप_प्रकार size, अचिन्हित पूर्णांक width)
अणु
	वापस _hist_entry__dso_snम_लिखो(he->ms.map, bf, size, width);
पूर्ण

अटल पूर्णांक hist_entry__dso_filter(काष्ठा hist_entry *he, पूर्णांक type, स्थिर व्योम *arg)
अणु
	स्थिर काष्ठा dso *dso = arg;

	अगर (type != HIST_FILTER__DSO)
		वापस -1;

	वापस dso && (!he->ms.map || he->ms.map->dso != dso);
पूर्ण

काष्ठा sort_entry sort_dso = अणु
	.se_header	= "Shared Object",
	.se_cmp		= sort__dso_cmp,
	.se_snम_लिखो	= hist_entry__dso_snम_लिखो,
	.se_filter	= hist_entry__dso_filter,
	.se_width_idx	= HISTC_DSO,
पूर्ण;

/* --sort symbol */

अटल पूर्णांक64_t _sort__addr_cmp(u64 left_ip, u64 right_ip)
अणु
	वापस (पूर्णांक64_t)(right_ip - left_ip);
पूर्ण

पूर्णांक64_t _sort__sym_cmp(काष्ठा symbol *sym_l, काष्ठा symbol *sym_r)
अणु
	अगर (!sym_l || !sym_r)
		वापस cmp_null(sym_l, sym_r);

	अगर (sym_l == sym_r)
		वापस 0;

	अगर (sym_l->अंतरभूतd || sym_r->अंतरभूतd) अणु
		पूर्णांक ret = म_भेद(sym_l->name, sym_r->name);

		अगर (ret)
			वापस ret;
		अगर ((sym_l->start <= sym_r->end) && (sym_l->end >= sym_r->start))
			वापस 0;
	पूर्ण

	अगर (sym_l->start != sym_r->start)
		वापस (पूर्णांक64_t)(sym_r->start - sym_l->start);

	वापस (पूर्णांक64_t)(sym_r->end - sym_l->end);
पूर्ण

अटल पूर्णांक64_t
sort__sym_cmp(काष्ठा hist_entry *left, काष्ठा hist_entry *right)
अणु
	पूर्णांक64_t ret;

	अगर (!left->ms.sym && !right->ms.sym)
		वापस _sort__addr_cmp(left->ip, right->ip);

	/*
	 * comparing symbol address alone is not enough since it's a
	 * relative address within a dso.
	 */
	अगर (!hists__has(left->hists, dso) || hists__has(right->hists, dso)) अणु
		ret = sort__dso_cmp(left, right);
		अगर (ret != 0)
			वापस ret;
	पूर्ण

	वापस _sort__sym_cmp(left->ms.sym, right->ms.sym);
पूर्ण

अटल पूर्णांक64_t
sort__sym_sort(काष्ठा hist_entry *left, काष्ठा hist_entry *right)
अणु
	अगर (!left->ms.sym || !right->ms.sym)
		वापस cmp_null(left->ms.sym, right->ms.sym);

	वापस म_भेद(right->ms.sym->name, left->ms.sym->name);
पूर्ण

अटल पूर्णांक _hist_entry__sym_snम_लिखो(काष्ठा map_symbol *ms,
				     u64 ip, अक्षर level, अक्षर *bf, माप_प्रकार size,
				     अचिन्हित पूर्णांक width)
अणु
	काष्ठा symbol *sym = ms->sym;
	काष्ठा map *map = ms->map;
	माप_प्रकार ret = 0;

	अगर (verbose > 0) अणु
		अक्षर o = map ? dso__symtab_origin(map->dso) : '!';
		u64 rip = ip;

		अगर (map && map->dso && map->dso->kernel
		    && map->dso->adjust_symbols)
			rip = map->unmap_ip(map, ip);

		ret += repsep_snम_लिखो(bf, size, "%-#*llx %c ",
				       BITS_PER_LONG / 4 + 2, rip, o);
	पूर्ण

	ret += repsep_snम_लिखो(bf + ret, size - ret, "[%c] ", level);
	अगर (sym && map) अणु
		अगर (sym->type == STT_OBJECT) अणु
			ret += repsep_snम_लिखो(bf + ret, size - ret, "%s", sym->name);
			ret += repsep_snम_लिखो(bf + ret, size - ret, "+0x%llx",
					ip - map->unmap_ip(map, sym->start));
		पूर्ण अन्यथा अणु
			ret += repsep_snम_लिखो(bf + ret, size - ret, "%.*s",
					       width - ret,
					       sym->name);
			अगर (sym->अंतरभूतd)
				ret += repsep_snम_लिखो(bf + ret, size - ret,
						       " (inlined)");
		पूर्ण
	पूर्ण अन्यथा अणु
		माप_प्रकार len = BITS_PER_LONG / 4;
		ret += repsep_snम_लिखो(bf + ret, size - ret, "%-#.*llx",
				       len, ip);
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक hist_entry__sym_snम_लिखो(काष्ठा hist_entry *he, अक्षर *bf, माप_प्रकार size, अचिन्हित पूर्णांक width)
अणु
	वापस _hist_entry__sym_snम_लिखो(&he->ms, he->ip,
					 he->level, bf, size, width);
पूर्ण

अटल पूर्णांक hist_entry__sym_filter(काष्ठा hist_entry *he, पूर्णांक type, स्थिर व्योम *arg)
अणु
	स्थिर अक्षर *sym = arg;

	अगर (type != HIST_FILTER__SYMBOL)
		वापस -1;

	वापस sym && (!he->ms.sym || !म_माला(he->ms.sym->name, sym));
पूर्ण

काष्ठा sort_entry sort_sym = अणु
	.se_header	= "Symbol",
	.se_cmp		= sort__sym_cmp,
	.se_sort	= sort__sym_sort,
	.se_snम_लिखो	= hist_entry__sym_snम_लिखो,
	.se_filter	= hist_entry__sym_filter,
	.se_width_idx	= HISTC_SYMBOL,
पूर्ण;

/* --sort srcline */

अक्षर *hist_entry__srcline(काष्ठा hist_entry *he)
अणु
	वापस map__srcline(he->ms.map, he->ip, he->ms.sym);
पूर्ण

अटल पूर्णांक64_t
sort__srcline_cmp(काष्ठा hist_entry *left, काष्ठा hist_entry *right)
अणु
	अगर (!left->srcline)
		left->srcline = hist_entry__srcline(left);
	अगर (!right->srcline)
		right->srcline = hist_entry__srcline(right);

	वापस म_भेद(right->srcline, left->srcline);
पूर्ण

अटल पूर्णांक hist_entry__srcline_snम_लिखो(काष्ठा hist_entry *he, अक्षर *bf,
					माप_प्रकार size, अचिन्हित पूर्णांक width)
अणु
	अगर (!he->srcline)
		he->srcline = hist_entry__srcline(he);

	वापस repsep_snम_लिखो(bf, size, "%-.*s", width, he->srcline);
पूर्ण

काष्ठा sort_entry sort_srcline = अणु
	.se_header	= "Source:Line",
	.se_cmp		= sort__srcline_cmp,
	.se_snम_लिखो	= hist_entry__srcline_snम_लिखो,
	.se_width_idx	= HISTC_SRCLINE,
पूर्ण;

/* --sort srcline_from */

अटल अक्षर *addr_map_symbol__srcline(काष्ठा addr_map_symbol *ams)
अणु
	वापस map__srcline(ams->ms.map, ams->al_addr, ams->ms.sym);
पूर्ण

अटल पूर्णांक64_t
sort__srcline_from_cmp(काष्ठा hist_entry *left, काष्ठा hist_entry *right)
अणु
	अगर (!left->branch_info->srcline_from)
		left->branch_info->srcline_from = addr_map_symbol__srcline(&left->branch_info->from);

	अगर (!right->branch_info->srcline_from)
		right->branch_info->srcline_from = addr_map_symbol__srcline(&right->branch_info->from);

	वापस म_भेद(right->branch_info->srcline_from, left->branch_info->srcline_from);
पूर्ण

अटल पूर्णांक hist_entry__srcline_from_snम_लिखो(काष्ठा hist_entry *he, अक्षर *bf,
					माप_प्रकार size, अचिन्हित पूर्णांक width)
अणु
	वापस repsep_snम_लिखो(bf, size, "%-*.*s", width, width, he->branch_info->srcline_from);
पूर्ण

काष्ठा sort_entry sort_srcline_from = अणु
	.se_header	= "From Source:Line",
	.se_cmp		= sort__srcline_from_cmp,
	.se_snम_लिखो	= hist_entry__srcline_from_snम_लिखो,
	.se_width_idx	= HISTC_SRCLINE_FROM,
पूर्ण;

/* --sort srcline_to */

अटल पूर्णांक64_t
sort__srcline_to_cmp(काष्ठा hist_entry *left, काष्ठा hist_entry *right)
अणु
	अगर (!left->branch_info->srcline_to)
		left->branch_info->srcline_to = addr_map_symbol__srcline(&left->branch_info->to);

	अगर (!right->branch_info->srcline_to)
		right->branch_info->srcline_to = addr_map_symbol__srcline(&right->branch_info->to);

	वापस म_भेद(right->branch_info->srcline_to, left->branch_info->srcline_to);
पूर्ण

अटल पूर्णांक hist_entry__srcline_to_snम_लिखो(काष्ठा hist_entry *he, अक्षर *bf,
					माप_प्रकार size, अचिन्हित पूर्णांक width)
अणु
	वापस repsep_snम_लिखो(bf, size, "%-*.*s", width, width, he->branch_info->srcline_to);
पूर्ण

काष्ठा sort_entry sort_srcline_to = अणु
	.se_header	= "To Source:Line",
	.se_cmp		= sort__srcline_to_cmp,
	.se_snम_लिखो	= hist_entry__srcline_to_snम_लिखो,
	.se_width_idx	= HISTC_SRCLINE_TO,
पूर्ण;

अटल पूर्णांक hist_entry__sym_ipc_snम_लिखो(काष्ठा hist_entry *he, अक्षर *bf,
					माप_प्रकार size, अचिन्हित पूर्णांक width)
अणु

	काष्ठा symbol *sym = he->ms.sym;
	काष्ठा annotation *notes;
	द्विगुन ipc = 0.0, coverage = 0.0;
	अक्षर पंचांगp[64];

	अगर (!sym)
		वापस repsep_snम_लिखो(bf, size, "%-*s", width, "-");

	notes = symbol__annotation(sym);

	अगर (notes->hit_cycles)
		ipc = notes->hit_insn / ((द्विगुन)notes->hit_cycles);

	अगर (notes->total_insn) अणु
		coverage = notes->cover_insn * 100.0 /
			((द्विगुन)notes->total_insn);
	पूर्ण

	snम_लिखो(पंचांगp, माप(पंचांगp), "%-5.2f [%5.1f%%]", ipc, coverage);
	वापस repsep_snम_लिखो(bf, size, "%-*s", width, पंचांगp);
पूर्ण

काष्ठा sort_entry sort_sym_ipc = अणु
	.se_header	= "IPC   [IPC Coverage]",
	.se_cmp		= sort__sym_cmp,
	.se_snम_लिखो	= hist_entry__sym_ipc_snम_लिखो,
	.se_width_idx	= HISTC_SYMBOL_IPC,
पूर्ण;

अटल पूर्णांक hist_entry__sym_ipc_null_snम_लिखो(काष्ठा hist_entry *he
					     __maybe_unused,
					     अक्षर *bf, माप_प्रकार size,
					     अचिन्हित पूर्णांक width)
अणु
	अक्षर पंचांगp[64];

	snम_लिखो(पंचांगp, माप(पंचांगp), "%-5s %2s", "-", "-");
	वापस repsep_snम_लिखो(bf, size, "%-*s", width, पंचांगp);
पूर्ण

काष्ठा sort_entry sort_sym_ipc_null = अणु
	.se_header	= "IPC   [IPC Coverage]",
	.se_cmp		= sort__sym_cmp,
	.se_snम_लिखो	= hist_entry__sym_ipc_null_snम_लिखो,
	.se_width_idx	= HISTC_SYMBOL_IPC,
पूर्ण;

/* --sort srcfile */

अटल अक्षर no_srcfile[1];

अटल अक्षर *hist_entry__get_srcfile(काष्ठा hist_entry *e)
अणु
	अक्षर *sf, *p;
	काष्ठा map *map = e->ms.map;

	अगर (!map)
		वापस no_srcfile;

	sf = __get_srcline(map->dso, map__rip_2objdump(map, e->ip),
			 e->ms.sym, false, true, true, e->ip);
	अगर (!म_भेद(sf, SRCLINE_UNKNOWN))
		वापस no_srcfile;
	p = म_अक्षर(sf, ':');
	अगर (p && *sf) अणु
		*p = 0;
		वापस sf;
	पूर्ण
	मुक्त(sf);
	वापस no_srcfile;
पूर्ण

अटल पूर्णांक64_t
sort__srcfile_cmp(काष्ठा hist_entry *left, काष्ठा hist_entry *right)
अणु
	अगर (!left->srcfile)
		left->srcfile = hist_entry__get_srcfile(left);
	अगर (!right->srcfile)
		right->srcfile = hist_entry__get_srcfile(right);

	वापस म_भेद(right->srcfile, left->srcfile);
पूर्ण

अटल पूर्णांक hist_entry__srcfile_snम_लिखो(काष्ठा hist_entry *he, अक्षर *bf,
					माप_प्रकार size, अचिन्हित पूर्णांक width)
अणु
	अगर (!he->srcfile)
		he->srcfile = hist_entry__get_srcfile(he);

	वापस repsep_snम_लिखो(bf, size, "%-.*s", width, he->srcfile);
पूर्ण

काष्ठा sort_entry sort_srcfile = अणु
	.se_header	= "Source File",
	.se_cmp		= sort__srcfile_cmp,
	.se_snम_लिखो	= hist_entry__srcfile_snम_लिखो,
	.se_width_idx	= HISTC_SRCखाता,
पूर्ण;

/* --sort parent */

अटल पूर्णांक64_t
sort__parent_cmp(काष्ठा hist_entry *left, काष्ठा hist_entry *right)
अणु
	काष्ठा symbol *sym_l = left->parent;
	काष्ठा symbol *sym_r = right->parent;

	अगर (!sym_l || !sym_r)
		वापस cmp_null(sym_l, sym_r);

	वापस म_भेद(sym_r->name, sym_l->name);
पूर्ण

अटल पूर्णांक hist_entry__parent_snम_लिखो(काष्ठा hist_entry *he, अक्षर *bf,
				       माप_प्रकार size, अचिन्हित पूर्णांक width)
अणु
	वापस repsep_snम_लिखो(bf, size, "%-*.*s", width, width,
			      he->parent ? he->parent->name : "[other]");
पूर्ण

काष्ठा sort_entry sort_parent = अणु
	.se_header	= "Parent symbol",
	.se_cmp		= sort__parent_cmp,
	.se_snम_लिखो	= hist_entry__parent_snम_लिखो,
	.se_width_idx	= HISTC_PARENT,
पूर्ण;

/* --sort cpu */

अटल पूर्णांक64_t
sort__cpu_cmp(काष्ठा hist_entry *left, काष्ठा hist_entry *right)
अणु
	वापस right->cpu - left->cpu;
पूर्ण

अटल पूर्णांक hist_entry__cpu_snम_लिखो(काष्ठा hist_entry *he, अक्षर *bf,
				    माप_प्रकार size, अचिन्हित पूर्णांक width)
अणु
	वापस repsep_snम_लिखो(bf, size, "%*.*d", width, width, he->cpu);
पूर्ण

काष्ठा sort_entry sort_cpu = अणु
	.se_header      = "CPU",
	.se_cmp	        = sort__cpu_cmp,
	.se_snम_लिखो    = hist_entry__cpu_snम_लिखो,
	.se_width_idx	= HISTC_CPU,
पूर्ण;

/* --sort cgroup_id */

अटल पूर्णांक64_t _sort__cgroup_dev_cmp(u64 left_dev, u64 right_dev)
अणु
	वापस (पूर्णांक64_t)(right_dev - left_dev);
पूर्ण

अटल पूर्णांक64_t _sort__cgroup_inode_cmp(u64 left_ino, u64 right_ino)
अणु
	वापस (पूर्णांक64_t)(right_ino - left_ino);
पूर्ण

अटल पूर्णांक64_t
sort__cgroup_id_cmp(काष्ठा hist_entry *left, काष्ठा hist_entry *right)
अणु
	पूर्णांक64_t ret;

	ret = _sort__cgroup_dev_cmp(right->cgroup_id.dev, left->cgroup_id.dev);
	अगर (ret != 0)
		वापस ret;

	वापस _sort__cgroup_inode_cmp(right->cgroup_id.ino,
				       left->cgroup_id.ino);
पूर्ण

अटल पूर्णांक hist_entry__cgroup_id_snम_लिखो(काष्ठा hist_entry *he,
					  अक्षर *bf, माप_प्रकार size,
					  अचिन्हित पूर्णांक width __maybe_unused)
अणु
	वापस repsep_snम_लिखो(bf, size, "%lu/0x%lx", he->cgroup_id.dev,
			       he->cgroup_id.ino);
पूर्ण

काष्ठा sort_entry sort_cgroup_id = अणु
	.se_header      = "cgroup id (dev/inode)",
	.se_cmp	        = sort__cgroup_id_cmp,
	.se_snम_लिखो    = hist_entry__cgroup_id_snम_लिखो,
	.se_width_idx	= HISTC_CGROUP_ID,
पूर्ण;

/* --sort cgroup */

अटल पूर्णांक64_t
sort__cgroup_cmp(काष्ठा hist_entry *left, काष्ठा hist_entry *right)
अणु
	वापस right->cgroup - left->cgroup;
पूर्ण

अटल पूर्णांक hist_entry__cgroup_snम_लिखो(काष्ठा hist_entry *he,
				       अक्षर *bf, माप_प्रकार size,
				       अचिन्हित पूर्णांक width __maybe_unused)
अणु
	स्थिर अक्षर *cgrp_name = "N/A";

	अगर (he->cgroup) अणु
		काष्ठा cgroup *cgrp = cgroup__find(he->ms.maps->machine->env,
						   he->cgroup);
		अगर (cgrp != शून्य)
			cgrp_name = cgrp->name;
		अन्यथा
			cgrp_name = "unknown";
	पूर्ण

	वापस repsep_snम_लिखो(bf, size, "%s", cgrp_name);
पूर्ण

काष्ठा sort_entry sort_cgroup = अणु
	.se_header      = "Cgroup",
	.se_cmp	        = sort__cgroup_cmp,
	.se_snम_लिखो    = hist_entry__cgroup_snम_लिखो,
	.se_width_idx	= HISTC_CGROUP,
पूर्ण;

/* --sort socket */

अटल पूर्णांक64_t
sort__socket_cmp(काष्ठा hist_entry *left, काष्ठा hist_entry *right)
अणु
	वापस right->socket - left->socket;
पूर्ण

अटल पूर्णांक hist_entry__socket_snम_लिखो(काष्ठा hist_entry *he, अक्षर *bf,
				    माप_प्रकार size, अचिन्हित पूर्णांक width)
अणु
	वापस repsep_snम_लिखो(bf, size, "%*.*d", width, width-3, he->socket);
पूर्ण

अटल पूर्णांक hist_entry__socket_filter(काष्ठा hist_entry *he, पूर्णांक type, स्थिर व्योम *arg)
अणु
	पूर्णांक sk = *(स्थिर पूर्णांक *)arg;

	अगर (type != HIST_FILTER__SOCKET)
		वापस -1;

	वापस sk >= 0 && he->socket != sk;
पूर्ण

काष्ठा sort_entry sort_socket = अणु
	.se_header      = "Socket",
	.se_cmp	        = sort__socket_cmp,
	.se_snम_लिखो    = hist_entry__socket_snम_लिखो,
	.se_filter      = hist_entry__socket_filter,
	.se_width_idx	= HISTC_SOCKET,
पूर्ण;

/* --sort समय */

अटल पूर्णांक64_t
sort__समय_cmp(काष्ठा hist_entry *left, काष्ठा hist_entry *right)
अणु
	वापस right->समय - left->समय;
पूर्ण

अटल पूर्णांक hist_entry__समय_snम_लिखो(काष्ठा hist_entry *he, अक्षर *bf,
				    माप_प्रकार size, अचिन्हित पूर्णांक width)
अणु
	अक्षर he_समय[32];

	अगर (symbol_conf.nanosecs)
		बारtamp__scnम_लिखो_nsec(he->समय, he_समय,
					  माप(he_समय));
	अन्यथा
		बारtamp__scnम_लिखो_usec(he->समय, he_समय,
					  माप(he_समय));

	वापस repsep_snम_लिखो(bf, size, "%-.*s", width, he_समय);
पूर्ण

काष्ठा sort_entry sort_समय = अणु
	.se_header      = "Time",
	.se_cmp	        = sort__समय_cmp,
	.se_snम_लिखो    = hist_entry__समय_snम_लिखो,
	.se_width_idx	= HISTC_TIME,
पूर्ण;

/* --sort trace */

अटल अक्षर *get_trace_output(काष्ठा hist_entry *he)
अणु
	काष्ठा trace_seq seq;
	काष्ठा evsel *evsel;
	काष्ठा tep_record rec = अणु
		.data = he->raw_data,
		.size = he->raw_size,
	पूर्ण;

	evsel = hists_to_evsel(he->hists);

	trace_seq_init(&seq);
	अगर (symbol_conf.raw_trace) अणु
		tep_prपूर्णांक_fields(&seq, he->raw_data, he->raw_size,
				 evsel->tp_क्रमmat);
	पूर्ण अन्यथा अणु
		tep_prपूर्णांक_event(evsel->tp_क्रमmat->tep,
				&seq, &rec, "%s", TEP_PRINT_INFO);
	पूर्ण
	/*
	 * Trim the buffer, it starts at 4KB and we're not going to
	 * add anything more to this buffer.
	 */
	वापस पुनः_स्मृति(seq.buffer, seq.len + 1);
पूर्ण

अटल पूर्णांक64_t
sort__trace_cmp(काष्ठा hist_entry *left, काष्ठा hist_entry *right)
अणु
	काष्ठा evsel *evsel;

	evsel = hists_to_evsel(left->hists);
	अगर (evsel->core.attr.type != PERF_TYPE_TRACEPOINT)
		वापस 0;

	अगर (left->trace_output == शून्य)
		left->trace_output = get_trace_output(left);
	अगर (right->trace_output == शून्य)
		right->trace_output = get_trace_output(right);

	वापस म_भेद(right->trace_output, left->trace_output);
पूर्ण

अटल पूर्णांक hist_entry__trace_snम_लिखो(काष्ठा hist_entry *he, अक्षर *bf,
				    माप_प्रकार size, अचिन्हित पूर्णांक width)
अणु
	काष्ठा evsel *evsel;

	evsel = hists_to_evsel(he->hists);
	अगर (evsel->core.attr.type != PERF_TYPE_TRACEPOINT)
		वापस scnम_लिखो(bf, size, "%-.*s", width, "N/A");

	अगर (he->trace_output == शून्य)
		he->trace_output = get_trace_output(he);
	वापस repsep_snम_लिखो(bf, size, "%-.*s", width, he->trace_output);
पूर्ण

काष्ठा sort_entry sort_trace = अणु
	.se_header      = "Trace output",
	.se_cmp	        = sort__trace_cmp,
	.se_snम_लिखो    = hist_entry__trace_snम_लिखो,
	.se_width_idx	= HISTC_TRACE,
पूर्ण;

/* sort keys क्रम branch stacks */

अटल पूर्णांक64_t
sort__dso_from_cmp(काष्ठा hist_entry *left, काष्ठा hist_entry *right)
अणु
	अगर (!left->branch_info || !right->branch_info)
		वापस cmp_null(left->branch_info, right->branch_info);

	वापस _sort__dso_cmp(left->branch_info->from.ms.map,
			      right->branch_info->from.ms.map);
पूर्ण

अटल पूर्णांक hist_entry__dso_from_snम_लिखो(काष्ठा hist_entry *he, अक्षर *bf,
				    माप_प्रकार size, अचिन्हित पूर्णांक width)
अणु
	अगर (he->branch_info)
		वापस _hist_entry__dso_snम_लिखो(he->branch_info->from.ms.map,
						 bf, size, width);
	अन्यथा
		वापस repsep_snम_लिखो(bf, size, "%-*.*s", width, width, "N/A");
पूर्ण

अटल पूर्णांक hist_entry__dso_from_filter(काष्ठा hist_entry *he, पूर्णांक type,
				       स्थिर व्योम *arg)
अणु
	स्थिर काष्ठा dso *dso = arg;

	अगर (type != HIST_FILTER__DSO)
		वापस -1;

	वापस dso && (!he->branch_info || !he->branch_info->from.ms.map ||
		       he->branch_info->from.ms.map->dso != dso);
पूर्ण

अटल पूर्णांक64_t
sort__dso_to_cmp(काष्ठा hist_entry *left, काष्ठा hist_entry *right)
अणु
	अगर (!left->branch_info || !right->branch_info)
		वापस cmp_null(left->branch_info, right->branch_info);

	वापस _sort__dso_cmp(left->branch_info->to.ms.map,
			      right->branch_info->to.ms.map);
पूर्ण

अटल पूर्णांक hist_entry__dso_to_snम_लिखो(काष्ठा hist_entry *he, अक्षर *bf,
				       माप_प्रकार size, अचिन्हित पूर्णांक width)
अणु
	अगर (he->branch_info)
		वापस _hist_entry__dso_snम_लिखो(he->branch_info->to.ms.map,
						 bf, size, width);
	अन्यथा
		वापस repsep_snम_लिखो(bf, size, "%-*.*s", width, width, "N/A");
पूर्ण

अटल पूर्णांक hist_entry__dso_to_filter(काष्ठा hist_entry *he, पूर्णांक type,
				     स्थिर व्योम *arg)
अणु
	स्थिर काष्ठा dso *dso = arg;

	अगर (type != HIST_FILTER__DSO)
		वापस -1;

	वापस dso && (!he->branch_info || !he->branch_info->to.ms.map ||
		       he->branch_info->to.ms.map->dso != dso);
पूर्ण

अटल पूर्णांक64_t
sort__sym_from_cmp(काष्ठा hist_entry *left, काष्ठा hist_entry *right)
अणु
	काष्ठा addr_map_symbol *from_l = &left->branch_info->from;
	काष्ठा addr_map_symbol *from_r = &right->branch_info->from;

	अगर (!left->branch_info || !right->branch_info)
		वापस cmp_null(left->branch_info, right->branch_info);

	from_l = &left->branch_info->from;
	from_r = &right->branch_info->from;

	अगर (!from_l->ms.sym && !from_r->ms.sym)
		वापस _sort__addr_cmp(from_l->addr, from_r->addr);

	वापस _sort__sym_cmp(from_l->ms.sym, from_r->ms.sym);
पूर्ण

अटल पूर्णांक64_t
sort__sym_to_cmp(काष्ठा hist_entry *left, काष्ठा hist_entry *right)
अणु
	काष्ठा addr_map_symbol *to_l, *to_r;

	अगर (!left->branch_info || !right->branch_info)
		वापस cmp_null(left->branch_info, right->branch_info);

	to_l = &left->branch_info->to;
	to_r = &right->branch_info->to;

	अगर (!to_l->ms.sym && !to_r->ms.sym)
		वापस _sort__addr_cmp(to_l->addr, to_r->addr);

	वापस _sort__sym_cmp(to_l->ms.sym, to_r->ms.sym);
पूर्ण

अटल पूर्णांक hist_entry__sym_from_snम_लिखो(काष्ठा hist_entry *he, अक्षर *bf,
					 माप_प्रकार size, अचिन्हित पूर्णांक width)
अणु
	अगर (he->branch_info) अणु
		काष्ठा addr_map_symbol *from = &he->branch_info->from;

		वापस _hist_entry__sym_snम_लिखो(&from->ms, from->al_addr,
						 he->level, bf, size, width);
	पूर्ण

	वापस repsep_snम_लिखो(bf, size, "%-*.*s", width, width, "N/A");
पूर्ण

अटल पूर्णांक hist_entry__sym_to_snम_लिखो(काष्ठा hist_entry *he, अक्षर *bf,
				       माप_प्रकार size, अचिन्हित पूर्णांक width)
अणु
	अगर (he->branch_info) अणु
		काष्ठा addr_map_symbol *to = &he->branch_info->to;

		वापस _hist_entry__sym_snम_लिखो(&to->ms, to->al_addr,
						 he->level, bf, size, width);
	पूर्ण

	वापस repsep_snम_लिखो(bf, size, "%-*.*s", width, width, "N/A");
पूर्ण

अटल पूर्णांक hist_entry__sym_from_filter(काष्ठा hist_entry *he, पूर्णांक type,
				       स्थिर व्योम *arg)
अणु
	स्थिर अक्षर *sym = arg;

	अगर (type != HIST_FILTER__SYMBOL)
		वापस -1;

	वापस sym && !(he->branch_info && he->branch_info->from.ms.sym &&
			म_माला(he->branch_info->from.ms.sym->name, sym));
पूर्ण

अटल पूर्णांक hist_entry__sym_to_filter(काष्ठा hist_entry *he, पूर्णांक type,
				       स्थिर व्योम *arg)
अणु
	स्थिर अक्षर *sym = arg;

	अगर (type != HIST_FILTER__SYMBOL)
		वापस -1;

	वापस sym && !(he->branch_info && he->branch_info->to.ms.sym &&
		        म_माला(he->branch_info->to.ms.sym->name, sym));
पूर्ण

काष्ठा sort_entry sort_dso_from = अणु
	.se_header	= "Source Shared Object",
	.se_cmp		= sort__dso_from_cmp,
	.se_snम_लिखो	= hist_entry__dso_from_snम_लिखो,
	.se_filter	= hist_entry__dso_from_filter,
	.se_width_idx	= HISTC_DSO_FROM,
पूर्ण;

काष्ठा sort_entry sort_dso_to = अणु
	.se_header	= "Target Shared Object",
	.se_cmp		= sort__dso_to_cmp,
	.se_snम_लिखो	= hist_entry__dso_to_snम_लिखो,
	.se_filter	= hist_entry__dso_to_filter,
	.se_width_idx	= HISTC_DSO_TO,
पूर्ण;

काष्ठा sort_entry sort_sym_from = अणु
	.se_header	= "Source Symbol",
	.se_cmp		= sort__sym_from_cmp,
	.se_snम_लिखो	= hist_entry__sym_from_snम_लिखो,
	.se_filter	= hist_entry__sym_from_filter,
	.se_width_idx	= HISTC_SYMBOL_FROM,
पूर्ण;

काष्ठा sort_entry sort_sym_to = अणु
	.se_header	= "Target Symbol",
	.se_cmp		= sort__sym_to_cmp,
	.se_snम_लिखो	= hist_entry__sym_to_snम_लिखो,
	.se_filter	= hist_entry__sym_to_filter,
	.se_width_idx	= HISTC_SYMBOL_TO,
पूर्ण;

अटल पूर्णांक64_t
sort__mispredict_cmp(काष्ठा hist_entry *left, काष्ठा hist_entry *right)
अणु
	अचिन्हित अक्षर mp, p;

	अगर (!left->branch_info || !right->branch_info)
		वापस cmp_null(left->branch_info, right->branch_info);

	mp = left->branch_info->flags.mispred != right->branch_info->flags.mispred;
	p  = left->branch_info->flags.predicted != right->branch_info->flags.predicted;
	वापस mp || p;
पूर्ण

अटल पूर्णांक hist_entry__mispredict_snम_लिखो(काष्ठा hist_entry *he, अक्षर *bf,
				    माप_प्रकार size, अचिन्हित पूर्णांक width)अणु
	अटल स्थिर अक्षर *out = "N/A";

	अगर (he->branch_info) अणु
		अगर (he->branch_info->flags.predicted)
			out = "N";
		अन्यथा अगर (he->branch_info->flags.mispred)
			out = "Y";
	पूर्ण

	वापस repsep_snम_लिखो(bf, size, "%-*.*s", width, width, out);
पूर्ण

अटल पूर्णांक64_t
sort__cycles_cmp(काष्ठा hist_entry *left, काष्ठा hist_entry *right)
अणु
	अगर (!left->branch_info || !right->branch_info)
		वापस cmp_null(left->branch_info, right->branch_info);

	वापस left->branch_info->flags.cycles -
		right->branch_info->flags.cycles;
पूर्ण

अटल पूर्णांक hist_entry__cycles_snम_लिखो(काष्ठा hist_entry *he, अक्षर *bf,
				    माप_प्रकार size, अचिन्हित पूर्णांक width)
अणु
	अगर (!he->branch_info)
		वापस scnम_लिखो(bf, size, "%-.*s", width, "N/A");
	अगर (he->branch_info->flags.cycles == 0)
		वापस repsep_snम_लिखो(bf, size, "%-*s", width, "-");
	वापस repsep_snम_लिखो(bf, size, "%-*hd", width,
			       he->branch_info->flags.cycles);
पूर्ण

काष्ठा sort_entry sort_cycles = अणु
	.se_header	= "Basic Block Cycles",
	.se_cmp		= sort__cycles_cmp,
	.se_snम_लिखो	= hist_entry__cycles_snम_लिखो,
	.se_width_idx	= HISTC_CYCLES,
पूर्ण;

/* --sort daddr_sym */
पूर्णांक64_t
sort__daddr_cmp(काष्ठा hist_entry *left, काष्ठा hist_entry *right)
अणु
	uपूर्णांक64_t l = 0, r = 0;

	अगर (left->mem_info)
		l = left->mem_info->daddr.addr;
	अगर (right->mem_info)
		r = right->mem_info->daddr.addr;

	वापस (पूर्णांक64_t)(r - l);
पूर्ण

अटल पूर्णांक hist_entry__daddr_snम_लिखो(काष्ठा hist_entry *he, अक्षर *bf,
				    माप_प्रकार size, अचिन्हित पूर्णांक width)
अणु
	uपूर्णांक64_t addr = 0;
	काष्ठा map_symbol *ms = शून्य;

	अगर (he->mem_info) अणु
		addr = he->mem_info->daddr.addr;
		ms = &he->mem_info->daddr.ms;
	पूर्ण
	वापस _hist_entry__sym_snम_लिखो(ms, addr, he->level, bf, size, width);
पूर्ण

पूर्णांक64_t
sort__iaddr_cmp(काष्ठा hist_entry *left, काष्ठा hist_entry *right)
अणु
	uपूर्णांक64_t l = 0, r = 0;

	अगर (left->mem_info)
		l = left->mem_info->iaddr.addr;
	अगर (right->mem_info)
		r = right->mem_info->iaddr.addr;

	वापस (पूर्णांक64_t)(r - l);
पूर्ण

अटल पूर्णांक hist_entry__iaddr_snम_लिखो(काष्ठा hist_entry *he, अक्षर *bf,
				    माप_प्रकार size, अचिन्हित पूर्णांक width)
अणु
	uपूर्णांक64_t addr = 0;
	काष्ठा map_symbol *ms = शून्य;

	अगर (he->mem_info) अणु
		addr = he->mem_info->iaddr.addr;
		ms   = &he->mem_info->iaddr.ms;
	पूर्ण
	वापस _hist_entry__sym_snम_लिखो(ms, addr, he->level, bf, size, width);
पूर्ण

अटल पूर्णांक64_t
sort__dso_daddr_cmp(काष्ठा hist_entry *left, काष्ठा hist_entry *right)
अणु
	काष्ठा map *map_l = शून्य;
	काष्ठा map *map_r = शून्य;

	अगर (left->mem_info)
		map_l = left->mem_info->daddr.ms.map;
	अगर (right->mem_info)
		map_r = right->mem_info->daddr.ms.map;

	वापस _sort__dso_cmp(map_l, map_r);
पूर्ण

अटल पूर्णांक hist_entry__dso_daddr_snम_लिखो(काष्ठा hist_entry *he, अक्षर *bf,
				    माप_प्रकार size, अचिन्हित पूर्णांक width)
अणु
	काष्ठा map *map = शून्य;

	अगर (he->mem_info)
		map = he->mem_info->daddr.ms.map;

	वापस _hist_entry__dso_snम_लिखो(map, bf, size, width);
पूर्ण

अटल पूर्णांक64_t
sort__locked_cmp(काष्ठा hist_entry *left, काष्ठा hist_entry *right)
अणु
	जोड़ perf_mem_data_src data_src_l;
	जोड़ perf_mem_data_src data_src_r;

	अगर (left->mem_info)
		data_src_l = left->mem_info->data_src;
	अन्यथा
		data_src_l.mem_lock = PERF_MEM_LOCK_NA;

	अगर (right->mem_info)
		data_src_r = right->mem_info->data_src;
	अन्यथा
		data_src_r.mem_lock = PERF_MEM_LOCK_NA;

	वापस (पूर्णांक64_t)(data_src_r.mem_lock - data_src_l.mem_lock);
पूर्ण

अटल पूर्णांक hist_entry__locked_snम_लिखो(काष्ठा hist_entry *he, अक्षर *bf,
				    माप_प्रकार size, अचिन्हित पूर्णांक width)
अणु
	अक्षर out[10];

	perf_mem__lck_scnम_लिखो(out, माप(out), he->mem_info);
	वापस repsep_snम_लिखो(bf, size, "%.*s", width, out);
पूर्ण

अटल पूर्णांक64_t
sort__tlb_cmp(काष्ठा hist_entry *left, काष्ठा hist_entry *right)
अणु
	जोड़ perf_mem_data_src data_src_l;
	जोड़ perf_mem_data_src data_src_r;

	अगर (left->mem_info)
		data_src_l = left->mem_info->data_src;
	अन्यथा
		data_src_l.mem_dtlb = PERF_MEM_TLB_NA;

	अगर (right->mem_info)
		data_src_r = right->mem_info->data_src;
	अन्यथा
		data_src_r.mem_dtlb = PERF_MEM_TLB_NA;

	वापस (पूर्णांक64_t)(data_src_r.mem_dtlb - data_src_l.mem_dtlb);
पूर्ण

अटल पूर्णांक hist_entry__tlb_snम_लिखो(काष्ठा hist_entry *he, अक्षर *bf,
				    माप_प्रकार size, अचिन्हित पूर्णांक width)
अणु
	अक्षर out[64];

	perf_mem__tlb_scnम_लिखो(out, माप(out), he->mem_info);
	वापस repsep_snम_लिखो(bf, size, "%-*s", width, out);
पूर्ण

अटल पूर्णांक64_t
sort__lvl_cmp(काष्ठा hist_entry *left, काष्ठा hist_entry *right)
अणु
	जोड़ perf_mem_data_src data_src_l;
	जोड़ perf_mem_data_src data_src_r;

	अगर (left->mem_info)
		data_src_l = left->mem_info->data_src;
	अन्यथा
		data_src_l.mem_lvl = PERF_MEM_LVL_NA;

	अगर (right->mem_info)
		data_src_r = right->mem_info->data_src;
	अन्यथा
		data_src_r.mem_lvl = PERF_MEM_LVL_NA;

	वापस (पूर्णांक64_t)(data_src_r.mem_lvl - data_src_l.mem_lvl);
पूर्ण

अटल पूर्णांक hist_entry__lvl_snम_लिखो(काष्ठा hist_entry *he, अक्षर *bf,
				    माप_प्रकार size, अचिन्हित पूर्णांक width)
अणु
	अक्षर out[64];

	perf_mem__lvl_scnम_लिखो(out, माप(out), he->mem_info);
	वापस repsep_snम_लिखो(bf, size, "%-*s", width, out);
पूर्ण

अटल पूर्णांक64_t
sort__snoop_cmp(काष्ठा hist_entry *left, काष्ठा hist_entry *right)
अणु
	जोड़ perf_mem_data_src data_src_l;
	जोड़ perf_mem_data_src data_src_r;

	अगर (left->mem_info)
		data_src_l = left->mem_info->data_src;
	अन्यथा
		data_src_l.mem_snoop = PERF_MEM_SNOOP_NA;

	अगर (right->mem_info)
		data_src_r = right->mem_info->data_src;
	अन्यथा
		data_src_r.mem_snoop = PERF_MEM_SNOOP_NA;

	वापस (पूर्णांक64_t)(data_src_r.mem_snoop - data_src_l.mem_snoop);
पूर्ण

अटल पूर्णांक hist_entry__snoop_snम_लिखो(काष्ठा hist_entry *he, अक्षर *bf,
				    माप_प्रकार size, अचिन्हित पूर्णांक width)
अणु
	अक्षर out[64];

	perf_mem__snp_scnम_लिखो(out, माप(out), he->mem_info);
	वापस repsep_snम_लिखो(bf, size, "%-*s", width, out);
पूर्ण

पूर्णांक64_t
sort__dcacheline_cmp(काष्ठा hist_entry *left, काष्ठा hist_entry *right)
अणु
	u64 l, r;
	काष्ठा map *l_map, *r_map;
	पूर्णांक rc;

	अगर (!left->mem_info)  वापस -1;
	अगर (!right->mem_info) वापस 1;

	/* group event types together */
	अगर (left->cpumode > right->cpumode) वापस -1;
	अगर (left->cpumode < right->cpumode) वापस 1;

	l_map = left->mem_info->daddr.ms.map;
	r_map = right->mem_info->daddr.ms.map;

	/* अगर both are शून्य, jump to sort on al_addr instead */
	अगर (!l_map && !r_map)
		जाओ addr;

	अगर (!l_map) वापस -1;
	अगर (!r_map) वापस 1;

	rc = dso__cmp_id(l_map->dso, r_map->dso);
	अगर (rc)
		वापस rc;
	/*
	 * Addresses with no major/minor numbers are assumed to be
	 * anonymous in userspace.  Sort those on pid then address.
	 *
	 * The kernel and non-zero major/minor mapped areas are
	 * assumed to be unity mapped.  Sort those on address.
	 */

	अगर ((left->cpumode != PERF_RECORD_MISC_KERNEL) &&
	    (!(l_map->flags & MAP_SHARED)) &&
	    !l_map->dso->id.maj && !l_map->dso->id.min &&
	    !l_map->dso->id.ino && !l_map->dso->id.ino_generation) अणु
		/* userspace anonymous */

		अगर (left->thपढ़ो->pid_ > right->thपढ़ो->pid_) वापस -1;
		अगर (left->thपढ़ो->pid_ < right->thपढ़ो->pid_) वापस 1;
	पूर्ण

addr:
	/* al_addr करोes all the right addr - start + offset calculations */
	l = cl_address(left->mem_info->daddr.al_addr);
	r = cl_address(right->mem_info->daddr.al_addr);

	अगर (l > r) वापस -1;
	अगर (l < r) वापस 1;

	वापस 0;
पूर्ण

अटल पूर्णांक hist_entry__dcacheline_snम_लिखो(काष्ठा hist_entry *he, अक्षर *bf,
					  माप_प्रकार size, अचिन्हित पूर्णांक width)
अणु

	uपूर्णांक64_t addr = 0;
	काष्ठा map_symbol *ms = शून्य;
	अक्षर level = he->level;

	अगर (he->mem_info) अणु
		काष्ठा map *map = he->mem_info->daddr.ms.map;

		addr = cl_address(he->mem_info->daddr.al_addr);
		ms = &he->mem_info->daddr.ms;

		/* prपूर्णांक [s] क्रम shared data mmaps */
		अगर ((he->cpumode != PERF_RECORD_MISC_KERNEL) &&
		     map && !(map->prot & PROT_EXEC) &&
		    (map->flags & MAP_SHARED) &&
		    (map->dso->id.maj || map->dso->id.min ||
		     map->dso->id.ino || map->dso->id.ino_generation))
			level = 's';
		अन्यथा अगर (!map)
			level = 'X';
	पूर्ण
	वापस _hist_entry__sym_snम_लिखो(ms, addr, level, bf, size, width);
पूर्ण

काष्ठा sort_entry sort_mispredict = अणु
	.se_header	= "Branch Mispredicted",
	.se_cmp		= sort__mispredict_cmp,
	.se_snम_लिखो	= hist_entry__mispredict_snम_लिखो,
	.se_width_idx	= HISTC_MISPREDICT,
पूर्ण;

अटल u64 he_weight(काष्ठा hist_entry *he)
अणु
	वापस he->stat.nr_events ? he->stat.weight / he->stat.nr_events : 0;
पूर्ण

अटल पूर्णांक64_t
sort__local_weight_cmp(काष्ठा hist_entry *left, काष्ठा hist_entry *right)
अणु
	वापस he_weight(left) - he_weight(right);
पूर्ण

अटल पूर्णांक hist_entry__local_weight_snम_लिखो(काष्ठा hist_entry *he, अक्षर *bf,
				    माप_प्रकार size, अचिन्हित पूर्णांक width)
अणु
	वापस repsep_snम_लिखो(bf, size, "%-*llu", width, he_weight(he));
पूर्ण

काष्ठा sort_entry sort_local_weight = अणु
	.se_header	= "Local Weight",
	.se_cmp		= sort__local_weight_cmp,
	.se_snम_लिखो	= hist_entry__local_weight_snम_लिखो,
	.se_width_idx	= HISTC_LOCAL_WEIGHT,
पूर्ण;

अटल पूर्णांक64_t
sort__global_weight_cmp(काष्ठा hist_entry *left, काष्ठा hist_entry *right)
अणु
	वापस left->stat.weight - right->stat.weight;
पूर्ण

अटल पूर्णांक hist_entry__global_weight_snम_लिखो(काष्ठा hist_entry *he, अक्षर *bf,
					      माप_प्रकार size, अचिन्हित पूर्णांक width)
अणु
	वापस repsep_snम_लिखो(bf, size, "%-*llu", width, he->stat.weight);
पूर्ण

काष्ठा sort_entry sort_global_weight = अणु
	.se_header	= "Weight",
	.se_cmp		= sort__global_weight_cmp,
	.se_snम_लिखो	= hist_entry__global_weight_snम_लिखो,
	.se_width_idx	= HISTC_GLOBAL_WEIGHT,
पूर्ण;

अटल u64 he_ins_lat(काष्ठा hist_entry *he)
अणु
		वापस he->stat.nr_events ? he->stat.ins_lat / he->stat.nr_events : 0;
पूर्ण

अटल पूर्णांक64_t
sort__local_ins_lat_cmp(काष्ठा hist_entry *left, काष्ठा hist_entry *right)
अणु
		वापस he_ins_lat(left) - he_ins_lat(right);
पूर्ण

अटल पूर्णांक hist_entry__local_ins_lat_snम_लिखो(काष्ठा hist_entry *he, अक्षर *bf,
					      माप_प्रकार size, अचिन्हित पूर्णांक width)
अणु
		वापस repsep_snम_लिखो(bf, size, "%-*u", width, he_ins_lat(he));
पूर्ण

काष्ठा sort_entry sort_local_ins_lat = अणु
	.se_header	= "Local INSTR Latency",
	.se_cmp		= sort__local_ins_lat_cmp,
	.se_snम_लिखो	= hist_entry__local_ins_lat_snम_लिखो,
	.se_width_idx	= HISTC_LOCAL_INS_LAT,
पूर्ण;

अटल पूर्णांक64_t
sort__global_ins_lat_cmp(काष्ठा hist_entry *left, काष्ठा hist_entry *right)
अणु
		वापस left->stat.ins_lat - right->stat.ins_lat;
पूर्ण

अटल पूर्णांक hist_entry__global_ins_lat_snम_लिखो(काष्ठा hist_entry *he, अक्षर *bf,
					       माप_प्रकार size, अचिन्हित पूर्णांक width)
अणु
		वापस repsep_snम_लिखो(bf, size, "%-*u", width, he->stat.ins_lat);
पूर्ण

काष्ठा sort_entry sort_global_ins_lat = अणु
	.se_header	= "INSTR Latency",
	.se_cmp		= sort__global_ins_lat_cmp,
	.se_snम_लिखो	= hist_entry__global_ins_lat_snम_लिखो,
	.se_width_idx	= HISTC_GLOBAL_INS_LAT,
पूर्ण;

अटल पूर्णांक64_t
sort__global_p_stage_cyc_cmp(काष्ठा hist_entry *left, काष्ठा hist_entry *right)
अणु
	वापस left->stat.p_stage_cyc - right->stat.p_stage_cyc;
पूर्ण

अटल पूर्णांक hist_entry__p_stage_cyc_snम_लिखो(काष्ठा hist_entry *he, अक्षर *bf,
					माप_प्रकार size, अचिन्हित पूर्णांक width)
अणु
	वापस repsep_snम_लिखो(bf, size, "%-*u", width, he->stat.p_stage_cyc);
पूर्ण

काष्ठा sort_entry sort_p_stage_cyc = अणु
	.se_header      = "Pipeline Stage Cycle",
	.se_cmp         = sort__global_p_stage_cyc_cmp,
	.se_snम_लिखो	= hist_entry__p_stage_cyc_snम_लिखो,
	.se_width_idx	= HISTC_P_STAGE_CYC,
पूर्ण;

काष्ठा sort_entry sort_mem_daddr_sym = अणु
	.se_header	= "Data Symbol",
	.se_cmp		= sort__daddr_cmp,
	.se_snम_लिखो	= hist_entry__daddr_snम_लिखो,
	.se_width_idx	= HISTC_MEM_DADDR_SYMBOL,
पूर्ण;

काष्ठा sort_entry sort_mem_iaddr_sym = अणु
	.se_header	= "Code Symbol",
	.se_cmp		= sort__iaddr_cmp,
	.se_snम_लिखो	= hist_entry__iaddr_snम_लिखो,
	.se_width_idx	= HISTC_MEM_IADDR_SYMBOL,
पूर्ण;

काष्ठा sort_entry sort_mem_daddr_dso = अणु
	.se_header	= "Data Object",
	.se_cmp		= sort__dso_daddr_cmp,
	.se_snम_लिखो	= hist_entry__dso_daddr_snम_लिखो,
	.se_width_idx	= HISTC_MEM_DADDR_DSO,
पूर्ण;

काष्ठा sort_entry sort_mem_locked = अणु
	.se_header	= "Locked",
	.se_cmp		= sort__locked_cmp,
	.se_snम_लिखो	= hist_entry__locked_snम_लिखो,
	.se_width_idx	= HISTC_MEM_LOCKED,
पूर्ण;

काष्ठा sort_entry sort_mem_tlb = अणु
	.se_header	= "TLB access",
	.se_cmp		= sort__tlb_cmp,
	.se_snम_लिखो	= hist_entry__tlb_snम_लिखो,
	.se_width_idx	= HISTC_MEM_TLB,
पूर्ण;

काष्ठा sort_entry sort_mem_lvl = अणु
	.se_header	= "Memory access",
	.se_cmp		= sort__lvl_cmp,
	.se_snम_लिखो	= hist_entry__lvl_snम_लिखो,
	.se_width_idx	= HISTC_MEM_LVL,
पूर्ण;

काष्ठा sort_entry sort_mem_snoop = अणु
	.se_header	= "Snoop",
	.se_cmp		= sort__snoop_cmp,
	.se_snम_लिखो	= hist_entry__snoop_snम_लिखो,
	.se_width_idx	= HISTC_MEM_SNOOP,
पूर्ण;

काष्ठा sort_entry sort_mem_dcacheline = अणु
	.se_header	= "Data Cacheline",
	.se_cmp		= sort__dcacheline_cmp,
	.se_snम_लिखो	= hist_entry__dcacheline_snम_लिखो,
	.se_width_idx	= HISTC_MEM_DCACHELINE,
पूर्ण;

अटल पूर्णांक64_t
sort__blocked_cmp(काष्ठा hist_entry *left, काष्ठा hist_entry *right)
अणु
	जोड़ perf_mem_data_src data_src_l;
	जोड़ perf_mem_data_src data_src_r;

	अगर (left->mem_info)
		data_src_l = left->mem_info->data_src;
	अन्यथा
		data_src_l.mem_blk = PERF_MEM_BLK_NA;

	अगर (right->mem_info)
		data_src_r = right->mem_info->data_src;
	अन्यथा
		data_src_r.mem_blk = PERF_MEM_BLK_NA;

	वापस (पूर्णांक64_t)(data_src_r.mem_blk - data_src_l.mem_blk);
पूर्ण

अटल पूर्णांक hist_entry__blocked_snम_लिखो(काष्ठा hist_entry *he, अक्षर *bf,
					माप_प्रकार size, अचिन्हित पूर्णांक width)
अणु
	अक्षर out[16];

	perf_mem__blk_scnम_लिखो(out, माप(out), he->mem_info);
	वापस repsep_snम_लिखो(bf, size, "%.*s", width, out);
पूर्ण

काष्ठा sort_entry sort_mem_blocked = अणु
	.se_header	= "Blocked",
	.se_cmp		= sort__blocked_cmp,
	.se_snम_लिखो	= hist_entry__blocked_snम_लिखो,
	.se_width_idx	= HISTC_MEM_BLOCKED,
पूर्ण;

अटल पूर्णांक64_t
sort__phys_daddr_cmp(काष्ठा hist_entry *left, काष्ठा hist_entry *right)
अणु
	uपूर्णांक64_t l = 0, r = 0;

	अगर (left->mem_info)
		l = left->mem_info->daddr.phys_addr;
	अगर (right->mem_info)
		r = right->mem_info->daddr.phys_addr;

	वापस (पूर्णांक64_t)(r - l);
पूर्ण

अटल पूर्णांक hist_entry__phys_daddr_snम_लिखो(काष्ठा hist_entry *he, अक्षर *bf,
					   माप_प्रकार size, अचिन्हित पूर्णांक width)
अणु
	uपूर्णांक64_t addr = 0;
	माप_प्रकार ret = 0;
	माप_प्रकार len = BITS_PER_LONG / 4;

	addr = he->mem_info->daddr.phys_addr;

	ret += repsep_snम_लिखो(bf + ret, size - ret, "[%c] ", he->level);

	ret += repsep_snम_लिखो(bf + ret, size - ret, "%-#.*llx", len, addr);

	ret += repsep_snम_लिखो(bf + ret, size - ret, "%-*s", width - ret, "");

	अगर (ret > width)
		bf[width] = '\0';

	वापस width;
पूर्ण

काष्ठा sort_entry sort_mem_phys_daddr = अणु
	.se_header	= "Data Physical Address",
	.se_cmp		= sort__phys_daddr_cmp,
	.se_snम_लिखो	= hist_entry__phys_daddr_snम_लिखो,
	.se_width_idx	= HISTC_MEM_PHYS_DADDR,
पूर्ण;

अटल पूर्णांक64_t
sort__data_page_size_cmp(काष्ठा hist_entry *left, काष्ठा hist_entry *right)
अणु
	uपूर्णांक64_t l = 0, r = 0;

	अगर (left->mem_info)
		l = left->mem_info->daddr.data_page_size;
	अगर (right->mem_info)
		r = right->mem_info->daddr.data_page_size;

	वापस (पूर्णांक64_t)(r - l);
पूर्ण

अटल पूर्णांक hist_entry__data_page_size_snम_लिखो(काष्ठा hist_entry *he, अक्षर *bf,
					  माप_प्रकार size, अचिन्हित पूर्णांक width)
अणु
	अक्षर str[PAGE_SIZE_NAME_LEN];

	वापस repsep_snम_लिखो(bf, size, "%-*s", width,
			       get_page_size_name(he->mem_info->daddr.data_page_size, str));
पूर्ण

काष्ठा sort_entry sort_mem_data_page_size = अणु
	.se_header	= "Data Page Size",
	.se_cmp		= sort__data_page_size_cmp,
	.se_snम_लिखो	= hist_entry__data_page_size_snम_लिखो,
	.se_width_idx	= HISTC_MEM_DATA_PAGE_SIZE,
पूर्ण;

अटल पूर्णांक64_t
sort__code_page_size_cmp(काष्ठा hist_entry *left, काष्ठा hist_entry *right)
अणु
	uपूर्णांक64_t l = left->code_page_size;
	uपूर्णांक64_t r = right->code_page_size;

	वापस (पूर्णांक64_t)(r - l);
पूर्ण

अटल पूर्णांक hist_entry__code_page_size_snम_लिखो(काष्ठा hist_entry *he, अक्षर *bf,
					  माप_प्रकार size, अचिन्हित पूर्णांक width)
अणु
	अक्षर str[PAGE_SIZE_NAME_LEN];

	वापस repsep_snम_लिखो(bf, size, "%-*s", width,
			       get_page_size_name(he->code_page_size, str));
पूर्ण

काष्ठा sort_entry sort_code_page_size = अणु
	.se_header	= "Code Page Size",
	.se_cmp		= sort__code_page_size_cmp,
	.se_snम_लिखो	= hist_entry__code_page_size_snम_लिखो,
	.se_width_idx	= HISTC_CODE_PAGE_SIZE,
पूर्ण;

अटल पूर्णांक64_t
sort__पात_cmp(काष्ठा hist_entry *left, काष्ठा hist_entry *right)
अणु
	अगर (!left->branch_info || !right->branch_info)
		वापस cmp_null(left->branch_info, right->branch_info);

	वापस left->branch_info->flags.पात !=
		right->branch_info->flags.पात;
पूर्ण

अटल पूर्णांक hist_entry__पात_snम_लिखो(काष्ठा hist_entry *he, अक्षर *bf,
				    माप_प्रकार size, अचिन्हित पूर्णांक width)
अणु
	अटल स्थिर अक्षर *out = "N/A";

	अगर (he->branch_info) अणु
		अगर (he->branch_info->flags.पात)
			out = "A";
		अन्यथा
			out = ".";
	पूर्ण

	वापस repsep_snम_लिखो(bf, size, "%-*s", width, out);
पूर्ण

काष्ठा sort_entry sort_पात = अणु
	.se_header	= "Transaction abort",
	.se_cmp		= sort__पात_cmp,
	.se_snम_लिखो	= hist_entry__पात_snम_लिखो,
	.se_width_idx	= HISTC_ABORT,
पूर्ण;

अटल पूर्णांक64_t
sort__in_tx_cmp(काष्ठा hist_entry *left, काष्ठा hist_entry *right)
अणु
	अगर (!left->branch_info || !right->branch_info)
		वापस cmp_null(left->branch_info, right->branch_info);

	वापस left->branch_info->flags.in_tx !=
		right->branch_info->flags.in_tx;
पूर्ण

अटल पूर्णांक hist_entry__in_tx_snम_लिखो(काष्ठा hist_entry *he, अक्षर *bf,
				    माप_प्रकार size, अचिन्हित पूर्णांक width)
अणु
	अटल स्थिर अक्षर *out = "N/A";

	अगर (he->branch_info) अणु
		अगर (he->branch_info->flags.in_tx)
			out = "T";
		अन्यथा
			out = ".";
	पूर्ण

	वापस repsep_snम_लिखो(bf, size, "%-*s", width, out);
पूर्ण

काष्ठा sort_entry sort_in_tx = अणु
	.se_header	= "Branch in transaction",
	.se_cmp		= sort__in_tx_cmp,
	.se_snम_लिखो	= hist_entry__in_tx_snम_लिखो,
	.se_width_idx	= HISTC_IN_TX,
पूर्ण;

अटल पूर्णांक64_t
sort__transaction_cmp(काष्ठा hist_entry *left, काष्ठा hist_entry *right)
अणु
	वापस left->transaction - right->transaction;
पूर्ण

अटल अंतरभूत अक्षर *add_str(अक्षर *p, स्थिर अक्षर *str)
अणु
	म_नकल(p, str);
	वापस p + म_माप(str);
पूर्ण

अटल काष्ठा txbit अणु
	अचिन्हित flag;
	स्थिर अक्षर *name;
	पूर्णांक skip_क्रम_len;
पूर्ण txbits[] = अणु
	अणु PERF_TXN_ELISION,        "EL ",        0 पूर्ण,
	अणु PERF_TXN_TRANSACTION,    "TX ",        1 पूर्ण,
	अणु PERF_TXN_SYNC,           "SYNC ",      1 पूर्ण,
	अणु PERF_TXN_ASYNC,          "ASYNC ",     0 पूर्ण,
	अणु PERF_TXN_RETRY,          "RETRY ",     0 पूर्ण,
	अणु PERF_TXN_CONFLICT,       "CON ",       0 पूर्ण,
	अणु PERF_TXN_CAPACITY_WRITE, "CAP-WRITE ", 1 पूर्ण,
	अणु PERF_TXN_CAPACITY_READ,  "CAP-READ ",  0 पूर्ण,
	अणु 0, शून्य, 0 पूर्ण
पूर्ण;

पूर्णांक hist_entry__transaction_len(व्योम)
अणु
	पूर्णांक i;
	पूर्णांक len = 0;

	क्रम (i = 0; txbits[i].name; i++) अणु
		अगर (!txbits[i].skip_क्रम_len)
			len += म_माप(txbits[i].name);
	पूर्ण
	len += 4; /* :XX<space> */
	वापस len;
पूर्ण

अटल पूर्णांक hist_entry__transaction_snम_लिखो(काष्ठा hist_entry *he, अक्षर *bf,
					    माप_प्रकार size, अचिन्हित पूर्णांक width)
अणु
	u64 t = he->transaction;
	अक्षर buf[128];
	अक्षर *p = buf;
	पूर्णांक i;

	buf[0] = 0;
	क्रम (i = 0; txbits[i].name; i++)
		अगर (txbits[i].flag & t)
			p = add_str(p, txbits[i].name);
	अगर (t && !(t & (PERF_TXN_SYNC|PERF_TXN_ASYNC)))
		p = add_str(p, "NEITHER ");
	अगर (t & PERF_TXN_ABORT_MASK) अणु
		प्र_लिखो(p, ":%" PRIx64,
			(t & PERF_TXN_ABORT_MASK) >>
			PERF_TXN_ABORT_SHIFT);
		p += म_माप(p);
	पूर्ण

	वापस repsep_snम_लिखो(bf, size, "%-*s", width, buf);
पूर्ण

काष्ठा sort_entry sort_transaction = अणु
	.se_header	= "Transaction                ",
	.se_cmp		= sort__transaction_cmp,
	.se_snम_लिखो	= hist_entry__transaction_snम_लिखो,
	.se_width_idx	= HISTC_TRANSACTION,
पूर्ण;

/* --sort symbol_size */

अटल पूर्णांक64_t _sort__sym_size_cmp(काष्ठा symbol *sym_l, काष्ठा symbol *sym_r)
अणु
	पूर्णांक64_t size_l = sym_l != शून्य ? symbol__size(sym_l) : 0;
	पूर्णांक64_t size_r = sym_r != शून्य ? symbol__size(sym_r) : 0;

	वापस size_l < size_r ? -1 :
		size_l == size_r ? 0 : 1;
पूर्ण

अटल पूर्णांक64_t
sort__sym_size_cmp(काष्ठा hist_entry *left, काष्ठा hist_entry *right)
अणु
	वापस _sort__sym_size_cmp(right->ms.sym, left->ms.sym);
पूर्ण

अटल पूर्णांक _hist_entry__sym_size_snम_लिखो(काष्ठा symbol *sym, अक्षर *bf,
					  माप_प्रकार bf_size, अचिन्हित पूर्णांक width)
अणु
	अगर (sym)
		वापस repsep_snम_लिखो(bf, bf_size, "%*d", width, symbol__size(sym));

	वापस repsep_snम_लिखो(bf, bf_size, "%*s", width, "unknown");
पूर्ण

अटल पूर्णांक hist_entry__sym_size_snम_लिखो(काष्ठा hist_entry *he, अक्षर *bf,
					 माप_प्रकार size, अचिन्हित पूर्णांक width)
अणु
	वापस _hist_entry__sym_size_snम_लिखो(he->ms.sym, bf, size, width);
पूर्ण

काष्ठा sort_entry sort_sym_size = अणु
	.se_header	= "Symbol size",
	.se_cmp		= sort__sym_size_cmp,
	.se_snम_लिखो	= hist_entry__sym_size_snम_लिखो,
	.se_width_idx	= HISTC_SYM_SIZE,
पूर्ण;

/* --sort dso_size */

अटल पूर्णांक64_t _sort__dso_size_cmp(काष्ठा map *map_l, काष्ठा map *map_r)
अणु
	पूर्णांक64_t size_l = map_l != शून्य ? map__size(map_l) : 0;
	पूर्णांक64_t size_r = map_r != शून्य ? map__size(map_r) : 0;

	वापस size_l < size_r ? -1 :
		size_l == size_r ? 0 : 1;
पूर्ण

अटल पूर्णांक64_t
sort__dso_size_cmp(काष्ठा hist_entry *left, काष्ठा hist_entry *right)
अणु
	वापस _sort__dso_size_cmp(right->ms.map, left->ms.map);
पूर्ण

अटल पूर्णांक _hist_entry__dso_size_snम_लिखो(काष्ठा map *map, अक्षर *bf,
					  माप_प्रकार bf_size, अचिन्हित पूर्णांक width)
अणु
	अगर (map && map->dso)
		वापस repsep_snम_लिखो(bf, bf_size, "%*d", width,
				       map__size(map));

	वापस repsep_snम_लिखो(bf, bf_size, "%*s", width, "unknown");
पूर्ण

अटल पूर्णांक hist_entry__dso_size_snम_लिखो(काष्ठा hist_entry *he, अक्षर *bf,
					 माप_प्रकार size, अचिन्हित पूर्णांक width)
अणु
	वापस _hist_entry__dso_size_snम_लिखो(he->ms.map, bf, size, width);
पूर्ण

काष्ठा sort_entry sort_dso_size = अणु
	.se_header	= "DSO size",
	.se_cmp		= sort__dso_size_cmp,
	.se_snम_लिखो	= hist_entry__dso_size_snम_लिखो,
	.se_width_idx	= HISTC_DSO_SIZE,
पूर्ण;


काष्ठा sort_dimension अणु
	स्थिर अक्षर		*name;
	काष्ठा sort_entry	*entry;
	पूर्णांक			taken;
पूर्ण;

पूर्णांक __weak arch_support_sort_key(स्थिर अक्षर *sort_key __maybe_unused)
अणु
	वापस 0;
पूर्ण

स्थिर अक्षर * __weak arch_perf_header_entry(स्थिर अक्षर *se_header)
अणु
	वापस se_header;
पूर्ण

अटल व्योम sort_dimension_add_dynamic_header(काष्ठा sort_dimension *sd)
अणु
	sd->entry->se_header = arch_perf_header_entry(sd->entry->se_header);
पूर्ण

#घोषणा DIM(d, n, func) [d] = अणु .name = n, .entry = &(func) पूर्ण

अटल काष्ठा sort_dimension common_sort_dimensions[] = अणु
	DIM(SORT_PID, "pid", sort_thपढ़ो),
	DIM(SORT_COMM, "comm", sort_comm),
	DIM(SORT_DSO, "dso", sort_dso),
	DIM(SORT_SYM, "symbol", sort_sym),
	DIM(SORT_PARENT, "parent", sort_parent),
	DIM(SORT_CPU, "cpu", sort_cpu),
	DIM(SORT_SOCKET, "socket", sort_socket),
	DIM(SORT_SRCLINE, "srcline", sort_srcline),
	DIM(SORT_SRCखाता, "srcfile", sort_srcfile),
	DIM(SORT_LOCAL_WEIGHT, "local_weight", sort_local_weight),
	DIM(SORT_GLOBAL_WEIGHT, "weight", sort_global_weight),
	DIM(SORT_TRANSACTION, "transaction", sort_transaction),
	DIM(SORT_TRACE, "trace", sort_trace),
	DIM(SORT_SYM_SIZE, "symbol_size", sort_sym_size),
	DIM(SORT_DSO_SIZE, "dso_size", sort_dso_size),
	DIM(SORT_CGROUP, "cgroup", sort_cgroup),
	DIM(SORT_CGROUP_ID, "cgroup_id", sort_cgroup_id),
	DIM(SORT_SYM_IPC_शून्य, "ipc_null", sort_sym_ipc_null),
	DIM(SORT_TIME, "time", sort_समय),
	DIM(SORT_CODE_PAGE_SIZE, "code_page_size", sort_code_page_size),
	DIM(SORT_LOCAL_INS_LAT, "local_ins_lat", sort_local_ins_lat),
	DIM(SORT_GLOBAL_INS_LAT, "ins_lat", sort_global_ins_lat),
	DIM(SORT_PIPELINE_STAGE_CYC, "p_stage_cyc", sort_p_stage_cyc),
पूर्ण;

#अघोषित DIM

#घोषणा DIM(d, n, func) [d - __SORT_BRANCH_STACK] = अणु .name = n, .entry = &(func) पूर्ण

अटल काष्ठा sort_dimension bstack_sort_dimensions[] = अणु
	DIM(SORT_DSO_FROM, "dso_from", sort_dso_from),
	DIM(SORT_DSO_TO, "dso_to", sort_dso_to),
	DIM(SORT_SYM_FROM, "symbol_from", sort_sym_from),
	DIM(SORT_SYM_TO, "symbol_to", sort_sym_to),
	DIM(SORT_MISPREDICT, "mispredict", sort_mispredict),
	DIM(SORT_IN_TX, "in_tx", sort_in_tx),
	DIM(SORT_ABORT, "abort", sort_पात),
	DIM(SORT_CYCLES, "cycles", sort_cycles),
	DIM(SORT_SRCLINE_FROM, "srcline_from", sort_srcline_from),
	DIM(SORT_SRCLINE_TO, "srcline_to", sort_srcline_to),
	DIM(SORT_SYM_IPC, "ipc_lbr", sort_sym_ipc),
पूर्ण;

#अघोषित DIM

#घोषणा DIM(d, n, func) [d - __SORT_MEMORY_MODE] = अणु .name = n, .entry = &(func) पूर्ण

अटल काष्ठा sort_dimension memory_sort_dimensions[] = अणु
	DIM(SORT_MEM_DADDR_SYMBOL, "symbol_daddr", sort_mem_daddr_sym),
	DIM(SORT_MEM_IADDR_SYMBOL, "symbol_iaddr", sort_mem_iaddr_sym),
	DIM(SORT_MEM_DADDR_DSO, "dso_daddr", sort_mem_daddr_dso),
	DIM(SORT_MEM_LOCKED, "locked", sort_mem_locked),
	DIM(SORT_MEM_TLB, "tlb", sort_mem_tlb),
	DIM(SORT_MEM_LVL, "mem", sort_mem_lvl),
	DIM(SORT_MEM_SNOOP, "snoop", sort_mem_snoop),
	DIM(SORT_MEM_DCACHELINE, "dcacheline", sort_mem_dcacheline),
	DIM(SORT_MEM_PHYS_DADDR, "phys_daddr", sort_mem_phys_daddr),
	DIM(SORT_MEM_DATA_PAGE_SIZE, "data_page_size", sort_mem_data_page_size),
	DIM(SORT_MEM_BLOCKED, "blocked", sort_mem_blocked),
पूर्ण;

#अघोषित DIM

काष्ठा hpp_dimension अणु
	स्थिर अक्षर		*name;
	काष्ठा perf_hpp_fmt	*fmt;
	पूर्णांक			taken;
पूर्ण;

#घोषणा DIM(d, n) अणु .name = n, .fmt = &perf_hpp__क्रमmat[d], पूर्ण

अटल काष्ठा hpp_dimension hpp_sort_dimensions[] = अणु
	DIM(PERF_HPP__OVERHEAD, "overhead"),
	DIM(PERF_HPP__OVERHEAD_SYS, "overhead_sys"),
	DIM(PERF_HPP__OVERHEAD_US, "overhead_us"),
	DIM(PERF_HPP__OVERHEAD_GUEST_SYS, "overhead_guest_sys"),
	DIM(PERF_HPP__OVERHEAD_GUEST_US, "overhead_guest_us"),
	DIM(PERF_HPP__OVERHEAD_ACC, "overhead_children"),
	DIM(PERF_HPP__SAMPLES, "sample"),
	DIM(PERF_HPP__PERIOD, "period"),
पूर्ण;

#अघोषित DIM

काष्ठा hpp_sort_entry अणु
	काष्ठा perf_hpp_fmt hpp;
	काष्ठा sort_entry *se;
पूर्ण;

व्योम perf_hpp__reset_sort_width(काष्ठा perf_hpp_fmt *fmt, काष्ठा hists *hists)
अणु
	काष्ठा hpp_sort_entry *hse;

	अगर (!perf_hpp__is_sort_entry(fmt))
		वापस;

	hse = container_of(fmt, काष्ठा hpp_sort_entry, hpp);
	hists__new_col_len(hists, hse->se->se_width_idx, म_माप(fmt->name));
पूर्ण

अटल पूर्णांक __sort__hpp_header(काष्ठा perf_hpp_fmt *fmt, काष्ठा perf_hpp *hpp,
			      काष्ठा hists *hists, पूर्णांक line __maybe_unused,
			      पूर्णांक *span __maybe_unused)
अणु
	काष्ठा hpp_sort_entry *hse;
	माप_प्रकार len = fmt->user_len;

	hse = container_of(fmt, काष्ठा hpp_sort_entry, hpp);

	अगर (!len)
		len = hists__col_len(hists, hse->se->se_width_idx);

	वापस scnम_लिखो(hpp->buf, hpp->size, "%-*.*s", len, len, fmt->name);
पूर्ण

अटल पूर्णांक __sort__hpp_width(काष्ठा perf_hpp_fmt *fmt,
			     काष्ठा perf_hpp *hpp __maybe_unused,
			     काष्ठा hists *hists)
अणु
	काष्ठा hpp_sort_entry *hse;
	माप_प्रकार len = fmt->user_len;

	hse = container_of(fmt, काष्ठा hpp_sort_entry, hpp);

	अगर (!len)
		len = hists__col_len(hists, hse->se->se_width_idx);

	वापस len;
पूर्ण

अटल पूर्णांक __sort__hpp_entry(काष्ठा perf_hpp_fmt *fmt, काष्ठा perf_hpp *hpp,
			     काष्ठा hist_entry *he)
अणु
	काष्ठा hpp_sort_entry *hse;
	माप_प्रकार len = fmt->user_len;

	hse = container_of(fmt, काष्ठा hpp_sort_entry, hpp);

	अगर (!len)
		len = hists__col_len(he->hists, hse->se->se_width_idx);

	वापस hse->se->se_snम_लिखो(he, hpp->buf, hpp->size, len);
पूर्ण

अटल पूर्णांक64_t __sort__hpp_cmp(काष्ठा perf_hpp_fmt *fmt,
			       काष्ठा hist_entry *a, काष्ठा hist_entry *b)
अणु
	काष्ठा hpp_sort_entry *hse;

	hse = container_of(fmt, काष्ठा hpp_sort_entry, hpp);
	वापस hse->se->se_cmp(a, b);
पूर्ण

अटल पूर्णांक64_t __sort__hpp_collapse(काष्ठा perf_hpp_fmt *fmt,
				    काष्ठा hist_entry *a, काष्ठा hist_entry *b)
अणु
	काष्ठा hpp_sort_entry *hse;
	पूर्णांक64_t (*collapse_fn)(काष्ठा hist_entry *, काष्ठा hist_entry *);

	hse = container_of(fmt, काष्ठा hpp_sort_entry, hpp);
	collapse_fn = hse->se->se_collapse ?: hse->se->se_cmp;
	वापस collapse_fn(a, b);
पूर्ण

अटल पूर्णांक64_t __sort__hpp_sort(काष्ठा perf_hpp_fmt *fmt,
				काष्ठा hist_entry *a, काष्ठा hist_entry *b)
अणु
	काष्ठा hpp_sort_entry *hse;
	पूर्णांक64_t (*sort_fn)(काष्ठा hist_entry *, काष्ठा hist_entry *);

	hse = container_of(fmt, काष्ठा hpp_sort_entry, hpp);
	sort_fn = hse->se->se_sort ?: hse->se->se_cmp;
	वापस sort_fn(a, b);
पूर्ण

bool perf_hpp__is_sort_entry(काष्ठा perf_hpp_fmt *क्रमmat)
अणु
	वापस क्रमmat->header == __sort__hpp_header;
पूर्ण

#घोषणा MK_SORT_ENTRY_CHK(key)					\
bool perf_hpp__is_ ## key ## _entry(काष्ठा perf_hpp_fmt *fmt)	\
अणु								\
	काष्ठा hpp_sort_entry *hse;				\
								\
	अगर (!perf_hpp__is_sort_entry(fmt))			\
		वापस false;					\
								\
	hse = container_of(fmt, काष्ठा hpp_sort_entry, hpp);	\
	वापस hse->se == &sort_ ## key ;			\
पूर्ण

MK_SORT_ENTRY_CHK(trace)
MK_SORT_ENTRY_CHK(srcline)
MK_SORT_ENTRY_CHK(srcfile)
MK_SORT_ENTRY_CHK(thपढ़ो)
MK_SORT_ENTRY_CHK(comm)
MK_SORT_ENTRY_CHK(dso)
MK_SORT_ENTRY_CHK(sym)


अटल bool __sort__hpp_equal(काष्ठा perf_hpp_fmt *a, काष्ठा perf_hpp_fmt *b)
अणु
	काष्ठा hpp_sort_entry *hse_a;
	काष्ठा hpp_sort_entry *hse_b;

	अगर (!perf_hpp__is_sort_entry(a) || !perf_hpp__is_sort_entry(b))
		वापस false;

	hse_a = container_of(a, काष्ठा hpp_sort_entry, hpp);
	hse_b = container_of(b, काष्ठा hpp_sort_entry, hpp);

	वापस hse_a->se == hse_b->se;
पूर्ण

अटल व्योम hse_मुक्त(काष्ठा perf_hpp_fmt *fmt)
अणु
	काष्ठा hpp_sort_entry *hse;

	hse = container_of(fmt, काष्ठा hpp_sort_entry, hpp);
	मुक्त(hse);
पूर्ण

अटल काष्ठा hpp_sort_entry *
__sort_dimension__alloc_hpp(काष्ठा sort_dimension *sd, पूर्णांक level)
अणु
	काष्ठा hpp_sort_entry *hse;

	hse = दो_स्मृति(माप(*hse));
	अगर (hse == शून्य) अणु
		pr_err("Memory allocation failed\n");
		वापस शून्य;
	पूर्ण

	hse->se = sd->entry;
	hse->hpp.name = sd->entry->se_header;
	hse->hpp.header = __sort__hpp_header;
	hse->hpp.width = __sort__hpp_width;
	hse->hpp.entry = __sort__hpp_entry;
	hse->hpp.color = शून्य;

	hse->hpp.cmp = __sort__hpp_cmp;
	hse->hpp.collapse = __sort__hpp_collapse;
	hse->hpp.sort = __sort__hpp_sort;
	hse->hpp.equal = __sort__hpp_equal;
	hse->hpp.मुक्त = hse_मुक्त;

	INIT_LIST_HEAD(&hse->hpp.list);
	INIT_LIST_HEAD(&hse->hpp.sort_list);
	hse->hpp.elide = false;
	hse->hpp.len = 0;
	hse->hpp.user_len = 0;
	hse->hpp.level = level;

	वापस hse;
पूर्ण

अटल व्योम hpp_मुक्त(काष्ठा perf_hpp_fmt *fmt)
अणु
	मुक्त(fmt);
पूर्ण

अटल काष्ठा perf_hpp_fmt *__hpp_dimension__alloc_hpp(काष्ठा hpp_dimension *hd,
						       पूर्णांक level)
अणु
	काष्ठा perf_hpp_fmt *fmt;

	fmt = memdup(hd->fmt, माप(*fmt));
	अगर (fmt) अणु
		INIT_LIST_HEAD(&fmt->list);
		INIT_LIST_HEAD(&fmt->sort_list);
		fmt->मुक्त = hpp_मुक्त;
		fmt->level = level;
	पूर्ण

	वापस fmt;
पूर्ण

पूर्णांक hist_entry__filter(काष्ठा hist_entry *he, पूर्णांक type, स्थिर व्योम *arg)
अणु
	काष्ठा perf_hpp_fmt *fmt;
	काष्ठा hpp_sort_entry *hse;
	पूर्णांक ret = -1;
	पूर्णांक r;

	perf_hpp_list__क्रम_each_क्रमmat(he->hpp_list, fmt) अणु
		अगर (!perf_hpp__is_sort_entry(fmt))
			जारी;

		hse = container_of(fmt, काष्ठा hpp_sort_entry, hpp);
		अगर (hse->se->se_filter == शून्य)
			जारी;

		/*
		 * hist entry is filtered अगर any of sort key in the hpp list
		 * is applied.  But it should skip non-matched filter types.
		 */
		r = hse->se->se_filter(he, type, arg);
		अगर (r >= 0) अणु
			अगर (ret < 0)
				ret = 0;
			ret |= r;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक __sort_dimension__add_hpp_sort(काष्ठा sort_dimension *sd,
					  काष्ठा perf_hpp_list *list,
					  पूर्णांक level)
अणु
	काष्ठा hpp_sort_entry *hse = __sort_dimension__alloc_hpp(sd, level);

	अगर (hse == शून्य)
		वापस -1;

	perf_hpp_list__रेजिस्टर_sort_field(list, &hse->hpp);
	वापस 0;
पूर्ण

अटल पूर्णांक __sort_dimension__add_hpp_output(काष्ठा sort_dimension *sd,
					    काष्ठा perf_hpp_list *list)
अणु
	काष्ठा hpp_sort_entry *hse = __sort_dimension__alloc_hpp(sd, 0);

	अगर (hse == शून्य)
		वापस -1;

	perf_hpp_list__column_रेजिस्टर(list, &hse->hpp);
	वापस 0;
पूर्ण

काष्ठा hpp_dynamic_entry अणु
	काष्ठा perf_hpp_fmt hpp;
	काष्ठा evsel *evsel;
	काष्ठा tep_क्रमmat_field *field;
	अचिन्हित dynamic_len;
	bool raw_trace;
पूर्ण;

अटल पूर्णांक hde_width(काष्ठा hpp_dynamic_entry *hde)
अणु
	अगर (!hde->hpp.len) अणु
		पूर्णांक len = hde->dynamic_len;
		पूर्णांक namelen = म_माप(hde->field->name);
		पूर्णांक fieldlen = hde->field->size;

		अगर (namelen > len)
			len = namelen;

		अगर (!(hde->field->flags & TEP_FIELD_IS_STRING)) अणु
			/* length क्रम prपूर्णांक hex numbers */
			fieldlen = hde->field->size * 2 + 2;
		पूर्ण
		अगर (fieldlen > len)
			len = fieldlen;

		hde->hpp.len = len;
	पूर्ण
	वापस hde->hpp.len;
पूर्ण

अटल व्योम update_dynamic_len(काष्ठा hpp_dynamic_entry *hde,
			       काष्ठा hist_entry *he)
अणु
	अक्षर *str, *pos;
	काष्ठा tep_क्रमmat_field *field = hde->field;
	माप_प्रकार namelen;
	bool last = false;

	अगर (hde->raw_trace)
		वापस;

	/* parse pretty prपूर्णांक result and update max length */
	अगर (!he->trace_output)
		he->trace_output = get_trace_output(he);

	namelen = म_माप(field->name);
	str = he->trace_output;

	जबतक (str) अणु
		pos = म_अक्षर(str, ' ');
		अगर (pos == शून्य) अणु
			last = true;
			pos = str + म_माप(str);
		पूर्ण

		अगर (!म_भेदन(str, field->name, namelen)) अणु
			माप_प्रकार len;

			str += namelen + 1;
			len = pos - str;

			अगर (len > hde->dynamic_len)
				hde->dynamic_len = len;
			अवरोध;
		पूर्ण

		अगर (last)
			str = शून्य;
		अन्यथा
			str = pos + 1;
	पूर्ण
पूर्ण

अटल पूर्णांक __sort__hde_header(काष्ठा perf_hpp_fmt *fmt, काष्ठा perf_hpp *hpp,
			      काष्ठा hists *hists __maybe_unused,
			      पूर्णांक line __maybe_unused,
			      पूर्णांक *span __maybe_unused)
अणु
	काष्ठा hpp_dynamic_entry *hde;
	माप_प्रकार len = fmt->user_len;

	hde = container_of(fmt, काष्ठा hpp_dynamic_entry, hpp);

	अगर (!len)
		len = hde_width(hde);

	वापस scnम_लिखो(hpp->buf, hpp->size, "%*.*s", len, len, hde->field->name);
पूर्ण

अटल पूर्णांक __sort__hde_width(काष्ठा perf_hpp_fmt *fmt,
			     काष्ठा perf_hpp *hpp __maybe_unused,
			     काष्ठा hists *hists __maybe_unused)
अणु
	काष्ठा hpp_dynamic_entry *hde;
	माप_प्रकार len = fmt->user_len;

	hde = container_of(fmt, काष्ठा hpp_dynamic_entry, hpp);

	अगर (!len)
		len = hde_width(hde);

	वापस len;
पूर्ण

bool perf_hpp__defined_dynamic_entry(काष्ठा perf_hpp_fmt *fmt, काष्ठा hists *hists)
अणु
	काष्ठा hpp_dynamic_entry *hde;

	hde = container_of(fmt, काष्ठा hpp_dynamic_entry, hpp);

	वापस hists_to_evsel(hists) == hde->evsel;
पूर्ण

अटल पूर्णांक __sort__hde_entry(काष्ठा perf_hpp_fmt *fmt, काष्ठा perf_hpp *hpp,
			     काष्ठा hist_entry *he)
अणु
	काष्ठा hpp_dynamic_entry *hde;
	माप_प्रकार len = fmt->user_len;
	अक्षर *str, *pos;
	काष्ठा tep_क्रमmat_field *field;
	माप_प्रकार namelen;
	bool last = false;
	पूर्णांक ret;

	hde = container_of(fmt, काष्ठा hpp_dynamic_entry, hpp);

	अगर (!len)
		len = hde_width(hde);

	अगर (hde->raw_trace)
		जाओ raw_field;

	अगर (!he->trace_output)
		he->trace_output = get_trace_output(he);

	field = hde->field;
	namelen = म_माप(field->name);
	str = he->trace_output;

	जबतक (str) अणु
		pos = म_अक्षर(str, ' ');
		अगर (pos == शून्य) अणु
			last = true;
			pos = str + म_माप(str);
		पूर्ण

		अगर (!म_भेदन(str, field->name, namelen)) अणु
			str += namelen + 1;
			str = strndup(str, pos - str);

			अगर (str == शून्य)
				वापस scnम_लिखो(hpp->buf, hpp->size,
						 "%*.*s", len, len, "ERROR");
			अवरोध;
		पूर्ण

		अगर (last)
			str = शून्य;
		अन्यथा
			str = pos + 1;
	पूर्ण

	अगर (str == शून्य) अणु
		काष्ठा trace_seq seq;
raw_field:
		trace_seq_init(&seq);
		tep_prपूर्णांक_field(&seq, he->raw_data, hde->field);
		str = seq.buffer;
	पूर्ण

	ret = scnम_लिखो(hpp->buf, hpp->size, "%*.*s", len, len, str);
	मुक्त(str);
	वापस ret;
पूर्ण

अटल पूर्णांक64_t __sort__hde_cmp(काष्ठा perf_hpp_fmt *fmt,
			       काष्ठा hist_entry *a, काष्ठा hist_entry *b)
अणु
	काष्ठा hpp_dynamic_entry *hde;
	काष्ठा tep_क्रमmat_field *field;
	अचिन्हित offset, size;

	hde = container_of(fmt, काष्ठा hpp_dynamic_entry, hpp);

	अगर (b == शून्य) अणु
		update_dynamic_len(hde, a);
		वापस 0;
	पूर्ण

	field = hde->field;
	अगर (field->flags & TEP_FIELD_IS_DYNAMIC) अणु
		अचिन्हित दीर्घ दीर्घ dyn;

		tep_पढ़ो_number_field(field, a->raw_data, &dyn);
		offset = dyn & 0xffff;
		size = (dyn >> 16) & 0xffff;

		/* record max width क्रम output */
		अगर (size > hde->dynamic_len)
			hde->dynamic_len = size;
	पूर्ण अन्यथा अणु
		offset = field->offset;
		size = field->size;
	पूर्ण

	वापस स_भेद(a->raw_data + offset, b->raw_data + offset, size);
पूर्ण

bool perf_hpp__is_dynamic_entry(काष्ठा perf_hpp_fmt *fmt)
अणु
	वापस fmt->cmp == __sort__hde_cmp;
पूर्ण

अटल bool __sort__hde_equal(काष्ठा perf_hpp_fmt *a, काष्ठा perf_hpp_fmt *b)
अणु
	काष्ठा hpp_dynamic_entry *hde_a;
	काष्ठा hpp_dynamic_entry *hde_b;

	अगर (!perf_hpp__is_dynamic_entry(a) || !perf_hpp__is_dynamic_entry(b))
		वापस false;

	hde_a = container_of(a, काष्ठा hpp_dynamic_entry, hpp);
	hde_b = container_of(b, काष्ठा hpp_dynamic_entry, hpp);

	वापस hde_a->field == hde_b->field;
पूर्ण

अटल व्योम hde_मुक्त(काष्ठा perf_hpp_fmt *fmt)
अणु
	काष्ठा hpp_dynamic_entry *hde;

	hde = container_of(fmt, काष्ठा hpp_dynamic_entry, hpp);
	मुक्त(hde);
पूर्ण

अटल काष्ठा hpp_dynamic_entry *
__alloc_dynamic_entry(काष्ठा evsel *evsel, काष्ठा tep_क्रमmat_field *field,
		      पूर्णांक level)
अणु
	काष्ठा hpp_dynamic_entry *hde;

	hde = दो_स्मृति(माप(*hde));
	अगर (hde == शून्य) अणु
		pr_debug("Memory allocation failed\n");
		वापस शून्य;
	पूर्ण

	hde->evsel = evsel;
	hde->field = field;
	hde->dynamic_len = 0;

	hde->hpp.name = field->name;
	hde->hpp.header = __sort__hde_header;
	hde->hpp.width  = __sort__hde_width;
	hde->hpp.entry  = __sort__hde_entry;
	hde->hpp.color  = शून्य;

	hde->hpp.cmp = __sort__hde_cmp;
	hde->hpp.collapse = __sort__hde_cmp;
	hde->hpp.sort = __sort__hde_cmp;
	hde->hpp.equal = __sort__hde_equal;
	hde->hpp.मुक्त = hde_मुक्त;

	INIT_LIST_HEAD(&hde->hpp.list);
	INIT_LIST_HEAD(&hde->hpp.sort_list);
	hde->hpp.elide = false;
	hde->hpp.len = 0;
	hde->hpp.user_len = 0;
	hde->hpp.level = level;

	वापस hde;
पूर्ण

काष्ठा perf_hpp_fmt *perf_hpp_fmt__dup(काष्ठा perf_hpp_fmt *fmt)
अणु
	काष्ठा perf_hpp_fmt *new_fmt = शून्य;

	अगर (perf_hpp__is_sort_entry(fmt)) अणु
		काष्ठा hpp_sort_entry *hse, *new_hse;

		hse = container_of(fmt, काष्ठा hpp_sort_entry, hpp);
		new_hse = memdup(hse, माप(*hse));
		अगर (new_hse)
			new_fmt = &new_hse->hpp;
	पूर्ण अन्यथा अगर (perf_hpp__is_dynamic_entry(fmt)) अणु
		काष्ठा hpp_dynamic_entry *hde, *new_hde;

		hde = container_of(fmt, काष्ठा hpp_dynamic_entry, hpp);
		new_hde = memdup(hde, माप(*hde));
		अगर (new_hde)
			new_fmt = &new_hde->hpp;
	पूर्ण अन्यथा अणु
		new_fmt = memdup(fmt, माप(*fmt));
	पूर्ण

	INIT_LIST_HEAD(&new_fmt->list);
	INIT_LIST_HEAD(&new_fmt->sort_list);

	वापस new_fmt;
पूर्ण

अटल पूर्णांक parse_field_name(अक्षर *str, अक्षर **event, अक्षर **field, अक्षर **opt)
अणु
	अक्षर *event_name, *field_name, *opt_name;

	event_name = str;
	field_name = म_अक्षर(str, '.');

	अगर (field_name) अणु
		*field_name++ = '\0';
	पूर्ण अन्यथा अणु
		event_name = शून्य;
		field_name = str;
	पूर्ण

	opt_name = म_अक्षर(field_name, '/');
	अगर (opt_name)
		*opt_name++ = '\0';

	*event = event_name;
	*field = field_name;
	*opt   = opt_name;

	वापस 0;
पूर्ण

/* find match evsel using a given event name.  The event name can be:
 *   1. '%' + event index (e.g. '%1' क्रम first event)
 *   2. full event name (e.g. sched:sched_चयन)
 *   3. partial event name (should not contain ':')
 */
अटल काष्ठा evsel *find_evsel(काष्ठा evlist *evlist, अक्षर *event_name)
अणु
	काष्ठा evsel *evsel = शून्य;
	काष्ठा evsel *pos;
	bool full_name;

	/* हाल 1 */
	अगर (event_name[0] == '%') अणु
		पूर्णांक nr = म_से_दीर्घ(event_name+1, शून्य, 0);

		अगर (nr > evlist->core.nr_entries)
			वापस शून्य;

		evsel = evlist__first(evlist);
		जबतक (--nr > 0)
			evsel = evsel__next(evsel);

		वापस evsel;
	पूर्ण

	full_name = !!म_अक्षर(event_name, ':');
	evlist__क्रम_each_entry(evlist, pos) अणु
		/* हाल 2 */
		अगर (full_name && !म_भेद(pos->name, event_name))
			वापस pos;
		/* हाल 3 */
		अगर (!full_name && म_माला(pos->name, event_name)) अणु
			अगर (evsel) अणु
				pr_debug("'%s' event is ambiguous: it can be %s or %s\n",
					 event_name, evsel->name, pos->name);
				वापस शून्य;
			पूर्ण
			evsel = pos;
		पूर्ण
	पूर्ण

	वापस evsel;
पूर्ण

अटल पूर्णांक __dynamic_dimension__add(काष्ठा evsel *evsel,
				    काष्ठा tep_क्रमmat_field *field,
				    bool raw_trace, पूर्णांक level)
अणु
	काष्ठा hpp_dynamic_entry *hde;

	hde = __alloc_dynamic_entry(evsel, field, level);
	अगर (hde == शून्य)
		वापस -ENOMEM;

	hde->raw_trace = raw_trace;

	perf_hpp__रेजिस्टर_sort_field(&hde->hpp);
	वापस 0;
पूर्ण

अटल पूर्णांक add_evsel_fields(काष्ठा evsel *evsel, bool raw_trace, पूर्णांक level)
अणु
	पूर्णांक ret;
	काष्ठा tep_क्रमmat_field *field;

	field = evsel->tp_क्रमmat->क्रमmat.fields;
	जबतक (field) अणु
		ret = __dynamic_dimension__add(evsel, field, raw_trace, level);
		अगर (ret < 0)
			वापस ret;

		field = field->next;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक add_all_dynamic_fields(काष्ठा evlist *evlist, bool raw_trace,
				  पूर्णांक level)
अणु
	पूर्णांक ret;
	काष्ठा evsel *evsel;

	evlist__क्रम_each_entry(evlist, evsel) अणु
		अगर (evsel->core.attr.type != PERF_TYPE_TRACEPOINT)
			जारी;

		ret = add_evsel_fields(evsel, raw_trace, level);
		अगर (ret < 0)
			वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक add_all_matching_fields(काष्ठा evlist *evlist,
				   अक्षर *field_name, bool raw_trace, पूर्णांक level)
अणु
	पूर्णांक ret = -ESRCH;
	काष्ठा evsel *evsel;
	काष्ठा tep_क्रमmat_field *field;

	evlist__क्रम_each_entry(evlist, evsel) अणु
		अगर (evsel->core.attr.type != PERF_TYPE_TRACEPOINT)
			जारी;

		field = tep_find_any_field(evsel->tp_क्रमmat, field_name);
		अगर (field == शून्य)
			जारी;

		ret = __dynamic_dimension__add(evsel, field, raw_trace, level);
		अगर (ret < 0)
			अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक add_dynamic_entry(काष्ठा evlist *evlist, स्थिर अक्षर *tok,
			     पूर्णांक level)
अणु
	अक्षर *str, *event_name, *field_name, *opt_name;
	काष्ठा evsel *evsel;
	काष्ठा tep_क्रमmat_field *field;
	bool raw_trace = symbol_conf.raw_trace;
	पूर्णांक ret = 0;

	अगर (evlist == शून्य)
		वापस -ENOENT;

	str = strdup(tok);
	अगर (str == शून्य)
		वापस -ENOMEM;

	अगर (parse_field_name(str, &event_name, &field_name, &opt_name) < 0) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (opt_name) अणु
		अगर (म_भेद(opt_name, "raw")) अणु
			pr_debug("unsupported field option %s\n", opt_name);
			ret = -EINVAL;
			जाओ out;
		पूर्ण
		raw_trace = true;
	पूर्ण

	अगर (!म_भेद(field_name, "trace_fields")) अणु
		ret = add_all_dynamic_fields(evlist, raw_trace, level);
		जाओ out;
	पूर्ण

	अगर (event_name == शून्य) अणु
		ret = add_all_matching_fields(evlist, field_name, raw_trace, level);
		जाओ out;
	पूर्ण

	evsel = find_evsel(evlist, event_name);
	अगर (evsel == शून्य) अणु
		pr_debug("Cannot find event: %s\n", event_name);
		ret = -ENOENT;
		जाओ out;
	पूर्ण

	अगर (evsel->core.attr.type != PERF_TYPE_TRACEPOINT) अणु
		pr_debug("%s is not a tracepoint event\n", event_name);
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (!म_भेद(field_name, "*")) अणु
		ret = add_evsel_fields(evsel, raw_trace, level);
	पूर्ण अन्यथा अणु
		field = tep_find_any_field(evsel->tp_क्रमmat, field_name);
		अगर (field == शून्य) अणु
			pr_debug("Cannot find event field for %s.%s\n",
				 event_name, field_name);
			वापस -ENOENT;
		पूर्ण

		ret = __dynamic_dimension__add(evsel, field, raw_trace, level);
	पूर्ण

out:
	मुक्त(str);
	वापस ret;
पूर्ण

अटल पूर्णांक __sort_dimension__add(काष्ठा sort_dimension *sd,
				 काष्ठा perf_hpp_list *list,
				 पूर्णांक level)
अणु
	अगर (sd->taken)
		वापस 0;

	अगर (__sort_dimension__add_hpp_sort(sd, list, level) < 0)
		वापस -1;

	अगर (sd->entry->se_collapse)
		list->need_collapse = 1;

	sd->taken = 1;

	वापस 0;
पूर्ण

अटल पूर्णांक __hpp_dimension__add(काष्ठा hpp_dimension *hd,
				काष्ठा perf_hpp_list *list,
				पूर्णांक level)
अणु
	काष्ठा perf_hpp_fmt *fmt;

	अगर (hd->taken)
		वापस 0;

	fmt = __hpp_dimension__alloc_hpp(hd, level);
	अगर (!fmt)
		वापस -1;

	hd->taken = 1;
	perf_hpp_list__रेजिस्टर_sort_field(list, fmt);
	वापस 0;
पूर्ण

अटल पूर्णांक __sort_dimension__add_output(काष्ठा perf_hpp_list *list,
					काष्ठा sort_dimension *sd)
अणु
	अगर (sd->taken)
		वापस 0;

	अगर (__sort_dimension__add_hpp_output(sd, list) < 0)
		वापस -1;

	sd->taken = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक __hpp_dimension__add_output(काष्ठा perf_hpp_list *list,
				       काष्ठा hpp_dimension *hd)
अणु
	काष्ठा perf_hpp_fmt *fmt;

	अगर (hd->taken)
		वापस 0;

	fmt = __hpp_dimension__alloc_hpp(hd, 0);
	अगर (!fmt)
		वापस -1;

	hd->taken = 1;
	perf_hpp_list__column_रेजिस्टर(list, fmt);
	वापस 0;
पूर्ण

पूर्णांक hpp_dimension__add_output(अचिन्हित col)
अणु
	BUG_ON(col >= PERF_HPP__MAX_INDEX);
	वापस __hpp_dimension__add_output(&perf_hpp_list, &hpp_sort_dimensions[col]);
पूर्ण

पूर्णांक sort_dimension__add(काष्ठा perf_hpp_list *list, स्थिर अक्षर *tok,
			काष्ठा evlist *evlist,
			पूर्णांक level)
अणु
	अचिन्हित पूर्णांक i, j;

	/*
	 * Check to see अगर there are any arch specअगरic
	 * sort dimensions not applicable क्रम the current
	 * architecture. If so, Skip that sort key since
	 * we करोn't want to display it in the output fields.
	 */
	क्रम (j = 0; j < ARRAY_SIZE(arch_specअगरic_sort_keys); j++) अणु
		अगर (!म_भेद(arch_specअगरic_sort_keys[j], tok) &&
				!arch_support_sort_key(tok)) अणु
			वापस 0;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(common_sort_dimensions); i++) अणु
		काष्ठा sort_dimension *sd = &common_sort_dimensions[i];

		अगर (strnहालcmp(tok, sd->name, म_माप(tok)))
			जारी;

		क्रम (j = 0; j < ARRAY_SIZE(dynamic_headers); j++) अणु
			अगर (!म_भेद(dynamic_headers[j], sd->name))
				sort_dimension_add_dynamic_header(sd);
		पूर्ण

		अगर (sd->entry == &sort_parent) अणु
			पूर्णांक ret = regcomp(&parent_regex, parent_pattern, REG_EXTENDED);
			अगर (ret) अणु
				अक्षर err[बफ_मान];

				regerror(ret, &parent_regex, err, माप(err));
				pr_err("Invalid regex: %s\n%s", parent_pattern, err);
				वापस -EINVAL;
			पूर्ण
			list->parent = 1;
		पूर्ण अन्यथा अगर (sd->entry == &sort_sym) अणु
			list->sym = 1;
			/*
			 * perf dअगरf displays the perक्रमmance dअगरference amongst
			 * two or more perf.data files. Those files could come
			 * from dअगरferent binaries. So we should not compare
			 * their ips, but the name of symbol.
			 */
			अगर (sort__mode == SORT_MODE__DIFF)
				sd->entry->se_collapse = sort__sym_sort;

		पूर्ण अन्यथा अगर (sd->entry == &sort_dso) अणु
			list->dso = 1;
		पूर्ण अन्यथा अगर (sd->entry == &sort_socket) अणु
			list->socket = 1;
		पूर्ण अन्यथा अगर (sd->entry == &sort_thपढ़ो) अणु
			list->thपढ़ो = 1;
		पूर्ण अन्यथा अगर (sd->entry == &sort_comm) अणु
			list->comm = 1;
		पूर्ण

		वापस __sort_dimension__add(sd, list, level);
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(hpp_sort_dimensions); i++) अणु
		काष्ठा hpp_dimension *hd = &hpp_sort_dimensions[i];

		अगर (strnहालcmp(tok, hd->name, म_माप(tok)))
			जारी;

		वापस __hpp_dimension__add(hd, list, level);
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(bstack_sort_dimensions); i++) अणु
		काष्ठा sort_dimension *sd = &bstack_sort_dimensions[i];

		अगर (strnहालcmp(tok, sd->name, म_माप(tok)))
			जारी;

		अगर (sort__mode != SORT_MODE__BRANCH)
			वापस -EINVAL;

		अगर (sd->entry == &sort_sym_from || sd->entry == &sort_sym_to)
			list->sym = 1;

		__sort_dimension__add(sd, list, level);
		वापस 0;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(memory_sort_dimensions); i++) अणु
		काष्ठा sort_dimension *sd = &memory_sort_dimensions[i];

		अगर (strnहालcmp(tok, sd->name, म_माप(tok)))
			जारी;

		अगर (sort__mode != SORT_MODE__MEMORY)
			वापस -EINVAL;

		अगर (sd->entry == &sort_mem_dcacheline && cacheline_size() == 0)
			वापस -EINVAL;

		अगर (sd->entry == &sort_mem_daddr_sym)
			list->sym = 1;

		__sort_dimension__add(sd, list, level);
		वापस 0;
	पूर्ण

	अगर (!add_dynamic_entry(evlist, tok, level))
		वापस 0;

	वापस -ESRCH;
पूर्ण

अटल पूर्णांक setup_sort_list(काष्ठा perf_hpp_list *list, अक्षर *str,
			   काष्ठा evlist *evlist)
अणु
	अक्षर *पंचांगp, *tok;
	पूर्णांक ret = 0;
	पूर्णांक level = 0;
	पूर्णांक next_level = 1;
	bool in_group = false;

	करो अणु
		tok = str;
		पंचांगp = strpbrk(str, "{}, ");
		अगर (पंचांगp) अणु
			अगर (in_group)
				next_level = level;
			अन्यथा
				next_level = level + 1;

			अगर (*पंचांगp == '{')
				in_group = true;
			अन्यथा अगर (*पंचांगp == '}')
				in_group = false;

			*पंचांगp = '\0';
			str = पंचांगp + 1;
		पूर्ण

		अगर (*tok) अणु
			ret = sort_dimension__add(list, tok, evlist, level);
			अगर (ret == -EINVAL) अणु
				अगर (!cacheline_size() && !strnहालcmp(tok, "dcacheline", म_माप(tok)))
					ui__error("The \"dcacheline\" --sort key needs to know the cacheline size and it couldn't be determined on this system");
				अन्यथा
					ui__error("Invalid --sort key: `%s'", tok);
				अवरोध;
			पूर्ण अन्यथा अगर (ret == -ESRCH) अणु
				ui__error("Unknown --sort key: `%s'", tok);
				अवरोध;
			पूर्ण
		पूर्ण

		level = next_level;
	पूर्ण जबतक (पंचांगp);

	वापस ret;
पूर्ण

अटल स्थिर अक्षर *get_शेष_sort_order(काष्ठा evlist *evlist)
अणु
	स्थिर अक्षर *शेष_sort_orders[] = अणु
		शेष_sort_order,
		शेष_branch_sort_order,
		शेष_mem_sort_order,
		शेष_top_sort_order,
		शेष_dअगरf_sort_order,
		शेष_tracepoपूर्णांक_sort_order,
	पूर्ण;
	bool use_trace = true;
	काष्ठा evsel *evsel;

	BUG_ON(sort__mode >= ARRAY_SIZE(शेष_sort_orders));

	अगर (evlist == शून्य || evlist__empty(evlist))
		जाओ out_no_evlist;

	evlist__क्रम_each_entry(evlist, evsel) अणु
		अगर (evsel->core.attr.type != PERF_TYPE_TRACEPOINT) अणु
			use_trace = false;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (use_trace) अणु
		sort__mode = SORT_MODE__TRACEPOINT;
		अगर (symbol_conf.raw_trace)
			वापस "trace_fields";
	पूर्ण
out_no_evlist:
	वापस शेष_sort_orders[sort__mode];
पूर्ण

अटल पूर्णांक setup_sort_order(काष्ठा evlist *evlist)
अणु
	अक्षर *new_sort_order;

	/*
	 * Append '+'-prefixed sort order to the शेष sort
	 * order string.
	 */
	अगर (!sort_order || is_strict_order(sort_order))
		वापस 0;

	अगर (sort_order[1] == '\0') अणु
		ui__error("Invalid --sort key: `+'");
		वापस -EINVAL;
	पूर्ण

	/*
	 * We allocate new sort_order string, but we never मुक्त it,
	 * because it's checked over the rest of the code.
	 */
	अगर (aप्र_लिखो(&new_sort_order, "%s,%s",
		     get_शेष_sort_order(evlist), sort_order + 1) < 0) अणु
		pr_err("Not enough memory to set up --sort");
		वापस -ENOMEM;
	पूर्ण

	sort_order = new_sort_order;
	वापस 0;
पूर्ण

/*
 * Adds 'pre,' prefix into 'str' is 'pre' is
 * not alपढ़ोy part of 'str'.
 */
अटल अक्षर *prefix_अगर_not_in(स्थिर अक्षर *pre, अक्षर *str)
अणु
	अक्षर *n;

	अगर (!str || म_माला(str, pre))
		वापस str;

	अगर (aप्र_लिखो(&n, "%s,%s", pre, str) < 0)
		n = शून्य;

	मुक्त(str);
	वापस n;
पूर्ण

अटल अक्षर *setup_overhead(अक्षर *keys)
अणु
	अगर (sort__mode == SORT_MODE__DIFF)
		वापस keys;

	keys = prefix_अगर_not_in("overhead", keys);

	अगर (symbol_conf.cumulate_callchain)
		keys = prefix_अगर_not_in("overhead_children", keys);

	वापस keys;
पूर्ण

अटल पूर्णांक __setup_sorting(काष्ठा evlist *evlist)
अणु
	अक्षर *str;
	स्थिर अक्षर *sort_keys;
	पूर्णांक ret = 0;

	ret = setup_sort_order(evlist);
	अगर (ret)
		वापस ret;

	sort_keys = sort_order;
	अगर (sort_keys == शून्य) अणु
		अगर (is_strict_order(field_order)) अणु
			/*
			 * If user specअगरied field order but no sort order,
			 * we'll honor it and not add शेष sort orders.
			 */
			वापस 0;
		पूर्ण

		sort_keys = get_शेष_sort_order(evlist);
	पूर्ण

	str = strdup(sort_keys);
	अगर (str == शून्य) अणु
		pr_err("Not enough memory to setup sort keys");
		वापस -ENOMEM;
	पूर्ण

	/*
	 * Prepend overhead fields क्रम backward compatibility.
	 */
	अगर (!is_strict_order(field_order)) अणु
		str = setup_overhead(str);
		अगर (str == शून्य) अणु
			pr_err("Not enough memory to setup overhead keys");
			वापस -ENOMEM;
		पूर्ण
	पूर्ण

	ret = setup_sort_list(&perf_hpp_list, str, evlist);

	मुक्त(str);
	वापस ret;
पूर्ण

व्योम perf_hpp__set_elide(पूर्णांक idx, bool elide)
अणु
	काष्ठा perf_hpp_fmt *fmt;
	काष्ठा hpp_sort_entry *hse;

	perf_hpp_list__क्रम_each_क्रमmat(&perf_hpp_list, fmt) अणु
		अगर (!perf_hpp__is_sort_entry(fmt))
			जारी;

		hse = container_of(fmt, काष्ठा hpp_sort_entry, hpp);
		अगर (hse->se->se_width_idx == idx) अणु
			fmt->elide = elide;
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल bool __get_elide(काष्ठा strlist *list, स्थिर अक्षर *list_name, खाता *fp)
अणु
	अगर (list && strlist__nr_entries(list) == 1) अणु
		अगर (fp != शून्य)
			ख_लिखो(fp, "# %s: %s\n", list_name,
				strlist__entry(list, 0)->s);
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल bool get_elide(पूर्णांक idx, खाता *output)
अणु
	चयन (idx) अणु
	हाल HISTC_SYMBOL:
		वापस __get_elide(symbol_conf.sym_list, "symbol", output);
	हाल HISTC_DSO:
		वापस __get_elide(symbol_conf.dso_list, "dso", output);
	हाल HISTC_COMM:
		वापस __get_elide(symbol_conf.comm_list, "comm", output);
	शेष:
		अवरोध;
	पूर्ण

	अगर (sort__mode != SORT_MODE__BRANCH)
		वापस false;

	चयन (idx) अणु
	हाल HISTC_SYMBOL_FROM:
		वापस __get_elide(symbol_conf.sym_from_list, "sym_from", output);
	हाल HISTC_SYMBOL_TO:
		वापस __get_elide(symbol_conf.sym_to_list, "sym_to", output);
	हाल HISTC_DSO_FROM:
		वापस __get_elide(symbol_conf.dso_from_list, "dso_from", output);
	हाल HISTC_DSO_TO:
		वापस __get_elide(symbol_conf.dso_to_list, "dso_to", output);
	शेष:
		अवरोध;
	पूर्ण

	वापस false;
पूर्ण

व्योम sort__setup_elide(खाता *output)
अणु
	काष्ठा perf_hpp_fmt *fmt;
	काष्ठा hpp_sort_entry *hse;

	perf_hpp_list__क्रम_each_क्रमmat(&perf_hpp_list, fmt) अणु
		अगर (!perf_hpp__is_sort_entry(fmt))
			जारी;

		hse = container_of(fmt, काष्ठा hpp_sort_entry, hpp);
		fmt->elide = get_elide(hse->se->se_width_idx, output);
	पूर्ण

	/*
	 * It makes no sense to elide all of sort entries.
	 * Just revert them to show up again.
	 */
	perf_hpp_list__क्रम_each_क्रमmat(&perf_hpp_list, fmt) अणु
		अगर (!perf_hpp__is_sort_entry(fmt))
			जारी;

		अगर (!fmt->elide)
			वापस;
	पूर्ण

	perf_hpp_list__क्रम_each_क्रमmat(&perf_hpp_list, fmt) अणु
		अगर (!perf_hpp__is_sort_entry(fmt))
			जारी;

		fmt->elide = false;
	पूर्ण
पूर्ण

पूर्णांक output_field_add(काष्ठा perf_hpp_list *list, अक्षर *tok)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(common_sort_dimensions); i++) अणु
		काष्ठा sort_dimension *sd = &common_sort_dimensions[i];

		अगर (strnहालcmp(tok, sd->name, म_माप(tok)))
			जारी;

		वापस __sort_dimension__add_output(list, sd);
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(hpp_sort_dimensions); i++) अणु
		काष्ठा hpp_dimension *hd = &hpp_sort_dimensions[i];

		अगर (strnहालcmp(tok, hd->name, म_माप(tok)))
			जारी;

		वापस __hpp_dimension__add_output(list, hd);
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(bstack_sort_dimensions); i++) अणु
		काष्ठा sort_dimension *sd = &bstack_sort_dimensions[i];

		अगर (strnहालcmp(tok, sd->name, म_माप(tok)))
			जारी;

		अगर (sort__mode != SORT_MODE__BRANCH)
			वापस -EINVAL;

		वापस __sort_dimension__add_output(list, sd);
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(memory_sort_dimensions); i++) अणु
		काष्ठा sort_dimension *sd = &memory_sort_dimensions[i];

		अगर (strnहालcmp(tok, sd->name, म_माप(tok)))
			जारी;

		अगर (sort__mode != SORT_MODE__MEMORY)
			वापस -EINVAL;

		वापस __sort_dimension__add_output(list, sd);
	पूर्ण

	वापस -ESRCH;
पूर्ण

अटल पूर्णांक setup_output_list(काष्ठा perf_hpp_list *list, अक्षर *str)
अणु
	अक्षर *पंचांगp, *tok;
	पूर्णांक ret = 0;

	क्रम (tok = म_मोहर_r(str, ", ", &पंचांगp);
			tok; tok = म_मोहर_r(शून्य, ", ", &पंचांगp)) अणु
		ret = output_field_add(list, tok);
		अगर (ret == -EINVAL) अणु
			ui__error("Invalid --fields key: `%s'", tok);
			अवरोध;
		पूर्ण अन्यथा अगर (ret == -ESRCH) अणु
			ui__error("Unknown --fields key: `%s'", tok);
			अवरोध;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

व्योम reset_dimensions(व्योम)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(common_sort_dimensions); i++)
		common_sort_dimensions[i].taken = 0;

	क्रम (i = 0; i < ARRAY_SIZE(hpp_sort_dimensions); i++)
		hpp_sort_dimensions[i].taken = 0;

	क्रम (i = 0; i < ARRAY_SIZE(bstack_sort_dimensions); i++)
		bstack_sort_dimensions[i].taken = 0;

	क्रम (i = 0; i < ARRAY_SIZE(memory_sort_dimensions); i++)
		memory_sort_dimensions[i].taken = 0;
पूर्ण

bool is_strict_order(स्थिर अक्षर *order)
अणु
	वापस order && (*order != '+');
पूर्ण

अटल पूर्णांक __setup_output_field(व्योम)
अणु
	अक्षर *str, *strp;
	पूर्णांक ret = -EINVAL;

	अगर (field_order == शून्य)
		वापस 0;

	strp = str = strdup(field_order);
	अगर (str == शून्य) अणु
		pr_err("Not enough memory to setup output fields");
		वापस -ENOMEM;
	पूर्ण

	अगर (!is_strict_order(field_order))
		strp++;

	अगर (!म_माप(strp)) अणु
		ui__error("Invalid --fields key: `+'");
		जाओ out;
	पूर्ण

	ret = setup_output_list(&perf_hpp_list, strp);

out:
	मुक्त(str);
	वापस ret;
पूर्ण

पूर्णांक setup_sorting(काष्ठा evlist *evlist)
अणु
	पूर्णांक err;

	err = __setup_sorting(evlist);
	अगर (err < 0)
		वापस err;

	अगर (parent_pattern != शेष_parent_pattern) अणु
		err = sort_dimension__add(&perf_hpp_list, "parent", evlist, -1);
		अगर (err < 0)
			वापस err;
	पूर्ण

	reset_dimensions();

	/*
	 * perf dअगरf करोesn't use शेष hpp output fields.
	 */
	अगर (sort__mode != SORT_MODE__DIFF)
		perf_hpp__init();

	err = __setup_output_field();
	अगर (err < 0)
		वापस err;

	/* copy sort keys to output fields */
	perf_hpp__setup_output_field(&perf_hpp_list);
	/* and then copy output fields to sort keys */
	perf_hpp__append_sort_keys(&perf_hpp_list);

	/* setup hists-specअगरic output fields */
	अगर (perf_hpp__setup_hists_क्रमmats(&perf_hpp_list, evlist) < 0)
		वापस -1;

	वापस 0;
पूर्ण

व्योम reset_output_field(व्योम)
अणु
	perf_hpp_list.need_collapse = 0;
	perf_hpp_list.parent = 0;
	perf_hpp_list.sym = 0;
	perf_hpp_list.dso = 0;

	field_order = शून्य;
	sort_order = शून्य;

	reset_dimensions();
	perf_hpp__reset_output_field(&perf_hpp_list);
पूर्ण

#घोषणा INDENT (3*8 + 1)

अटल व्योम add_key(काष्ठा strbuf *sb, स्थिर अक्षर *str, पूर्णांक *llen)
अणु
	अगर (*llen >= 75) अणु
		strbuf_addstr(sb, "\n\t\t\t ");
		*llen = INDENT;
	पूर्ण
	strbuf_addf(sb, " %s", str);
	*llen += म_माप(str) + 1;
पूर्ण

अटल व्योम add_sort_string(काष्ठा strbuf *sb, काष्ठा sort_dimension *s, पूर्णांक n,
			    पूर्णांक *llen)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < n; i++)
		add_key(sb, s[i].name, llen);
पूर्ण

अटल व्योम add_hpp_sort_string(काष्ठा strbuf *sb, काष्ठा hpp_dimension *s, पूर्णांक n,
				पूर्णांक *llen)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < n; i++)
		add_key(sb, s[i].name, llen);
पूर्ण

स्थिर अक्षर *sort_help(स्थिर अक्षर *prefix)
अणु
	काष्ठा strbuf sb;
	अक्षर *s;
	पूर्णांक len = म_माप(prefix) + INDENT;

	strbuf_init(&sb, 300);
	strbuf_addstr(&sb, prefix);
	add_hpp_sort_string(&sb, hpp_sort_dimensions,
			    ARRAY_SIZE(hpp_sort_dimensions), &len);
	add_sort_string(&sb, common_sort_dimensions,
			    ARRAY_SIZE(common_sort_dimensions), &len);
	add_sort_string(&sb, bstack_sort_dimensions,
			    ARRAY_SIZE(bstack_sort_dimensions), &len);
	add_sort_string(&sb, memory_sort_dimensions,
			    ARRAY_SIZE(memory_sort_dimensions), &len);
	s = strbuf_detach(&sb, शून्य);
	strbuf_release(&sb);
	वापस s;
पूर्ण
