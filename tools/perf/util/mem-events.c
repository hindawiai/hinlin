<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <मानकघोष.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <त्रुटिसं.स>
#समावेश <sys/types.h>
#समावेश <sys/स्थिति.स>
#समावेश <unistd.h>
#समावेश <api/fs/fs.h>
#समावेश <linux/kernel.h>
#समावेश "map_symbol.h"
#समावेश "mem-events.h"
#समावेश "debug.h"
#समावेश "symbol.h"

अचिन्हित पूर्णांक perf_mem_events__loads_ldlat = 30;

#घोषणा E(t, n, s) अणु .tag = t, .name = n, .sysfs_name = s पूर्ण

अटल काष्ठा perf_mem_event perf_mem_events[PERF_MEM_EVENTS__MAX] = अणु
	E("ldlat-loads",	"cpu/mem-loads,ldlat=%u/P",	"cpu/events/mem-loads"),
	E("ldlat-stores",	"cpu/mem-stores/P",		"cpu/events/mem-stores"),
	E(शून्य,			शून्य,				शून्य),
पूर्ण;
#अघोषित E

#अघोषित E

अटल अक्षर mem_loads_name[100];
अटल bool mem_loads_name__init;

काष्ठा perf_mem_event * __weak perf_mem_events__ptr(पूर्णांक i)
अणु
	अगर (i >= PERF_MEM_EVENTS__MAX)
		वापस शून्य;

	वापस &perf_mem_events[i];
पूर्ण

अक्षर * __weak perf_mem_events__name(पूर्णांक i)
अणु
	काष्ठा perf_mem_event *e = perf_mem_events__ptr(i);

	अगर (!e)
		वापस शून्य;

	अगर (i == PERF_MEM_EVENTS__LOAD) अणु
		अगर (!mem_loads_name__init) अणु
			mem_loads_name__init = true;
			scnम_लिखो(mem_loads_name, माप(mem_loads_name),
				  e->name, perf_mem_events__loads_ldlat);
		पूर्ण
		वापस mem_loads_name;
	पूर्ण

	वापस (अक्षर *)e->name;
पूर्ण

__weak bool is_mem_loads_aux_event(काष्ठा evsel *leader __maybe_unused)
अणु
	वापस false;
पूर्ण

पूर्णांक perf_mem_events__parse(स्थिर अक्षर *str)
अणु
	अक्षर *tok, *saveptr = शून्य;
	bool found = false;
	अक्षर *buf;
	पूर्णांक j;

	/* We need buffer that we know we can ग_लिखो to. */
	buf = दो_स्मृति(म_माप(str) + 1);
	अगर (!buf)
		वापस -ENOMEM;

	म_नकल(buf, str);

	tok = म_मोहर_r((अक्षर *)buf, ",", &saveptr);

	जबतक (tok) अणु
		क्रम (j = 0; j < PERF_MEM_EVENTS__MAX; j++) अणु
			काष्ठा perf_mem_event *e = perf_mem_events__ptr(j);

			अगर (!e->tag)
				जारी;

			अगर (म_माला(e->tag, tok))
				e->record = found = true;
		पूर्ण

		tok = म_मोहर_r(शून्य, ",", &saveptr);
	पूर्ण

	मुक्त(buf);

	अगर (found)
		वापस 0;

	pr_err("failed: event '%s' not found, use '-e list' to get list of available events\n", str);
	वापस -1;
पूर्ण

पूर्णांक perf_mem_events__init(व्योम)
अणु
	स्थिर अक्षर *mnt = sysfs__mount();
	bool found = false;
	पूर्णांक j;

	अगर (!mnt)
		वापस -ENOENT;

	क्रम (j = 0; j < PERF_MEM_EVENTS__MAX; j++) अणु
		अक्षर path[PATH_MAX];
		काष्ठा perf_mem_event *e = perf_mem_events__ptr(j);
		काष्ठा stat st;

		/*
		 * If the event entry isn't valid, skip initialization
		 * and "e->supported" will keep false.
		 */
		अगर (!e->tag)
			जारी;

		scnम_लिखो(path, PATH_MAX, "%s/devices/%s",
			  mnt, e->sysfs_name);

		अगर (!stat(path, &st))
			e->supported = found = true;
	पूर्ण

	वापस found ? 0 : -ENOENT;
पूर्ण

व्योम perf_mem_events__list(व्योम)
अणु
	पूर्णांक j;

	क्रम (j = 0; j < PERF_MEM_EVENTS__MAX; j++) अणु
		काष्ठा perf_mem_event *e = perf_mem_events__ptr(j);

		ख_लिखो(मानक_त्रुटि, "%-13s%-*s%s\n",
			e->tag ?: "",
			verbose > 0 ? 25 : 0,
			verbose > 0 ? perf_mem_events__name(j) : "",
			e->supported ? ": available" : "");
	पूर्ण
पूर्ण

अटल स्थिर अक्षर * स्थिर tlb_access[] = अणु
	"N/A",
	"HIT",
	"MISS",
	"L1",
	"L2",
	"Walker",
	"Fault",
पूर्ण;

पूर्णांक perf_mem__tlb_scnम_लिखो(अक्षर *out, माप_प्रकार sz, काष्ठा mem_info *mem_info)
अणु
	माप_प्रकार l = 0, i;
	u64 m = PERF_MEM_TLB_NA;
	u64 hit, miss;

	sz -= 1; /* -1 क्रम null termination */
	out[0] = '\0';

	अगर (mem_info)
		m = mem_info->data_src.mem_dtlb;

	hit = m & PERF_MEM_TLB_HIT;
	miss = m & PERF_MEM_TLB_MISS;

	/* alपढ़ोy taken care of */
	m &= ~(PERF_MEM_TLB_HIT|PERF_MEM_TLB_MISS);

	क्रम (i = 0; m && i < ARRAY_SIZE(tlb_access); i++, m >>= 1) अणु
		अगर (!(m & 0x1))
			जारी;
		अगर (l) अणु
			म_जोड़ो(out, " or ");
			l += 4;
		पूर्ण
		l += scnम_लिखो(out + l, sz - l, tlb_access[i]);
	पूर्ण
	अगर (*out == '\0')
		l += scnम_लिखो(out, sz - l, "N/A");
	अगर (hit)
		l += scnम_लिखो(out + l, sz - l, " hit");
	अगर (miss)
		l += scnम_लिखो(out + l, sz - l, " miss");

	वापस l;
पूर्ण

अटल स्थिर अक्षर * स्थिर mem_lvl[] = अणु
	"N/A",
	"HIT",
	"MISS",
	"L1",
	"LFB",
	"L2",
	"L3",
	"Local RAM",
	"Remote RAM (1 hop)",
	"Remote RAM (2 hops)",
	"Remote Cache (1 hop)",
	"Remote Cache (2 hops)",
	"I/O",
	"Uncached",
पूर्ण;

अटल स्थिर अक्षर * स्थिर mem_lvlnum[] = अणु
	[PERF_MEM_LVLNUM_ANY_CACHE] = "Any cache",
	[PERF_MEM_LVLNUM_LFB] = "LFB",
	[PERF_MEM_LVLNUM_RAM] = "RAM",
	[PERF_MEM_LVLNUM_PMEM] = "PMEM",
	[PERF_MEM_LVLNUM_NA] = "N/A",
पूर्ण;

पूर्णांक perf_mem__lvl_scnम_लिखो(अक्षर *out, माप_प्रकार sz, काष्ठा mem_info *mem_info)
अणु
	माप_प्रकार i, l = 0;
	u64 m =  PERF_MEM_LVL_NA;
	u64 hit, miss;
	पूर्णांक prपूर्णांकed;

	अगर (mem_info)
		m  = mem_info->data_src.mem_lvl;

	sz -= 1; /* -1 क्रम null termination */
	out[0] = '\0';

	hit = m & PERF_MEM_LVL_HIT;
	miss = m & PERF_MEM_LVL_MISS;

	/* alपढ़ोy taken care of */
	m &= ~(PERF_MEM_LVL_HIT|PERF_MEM_LVL_MISS);


	अगर (mem_info && mem_info->data_src.mem_remote) अणु
		म_जोड़ो(out, "Remote ");
		l += 7;
	पूर्ण

	prपूर्णांकed = 0;
	क्रम (i = 0; m && i < ARRAY_SIZE(mem_lvl); i++, m >>= 1) अणु
		अगर (!(m & 0x1))
			जारी;
		अगर (prपूर्णांकed++) अणु
			म_जोड़ो(out, " or ");
			l += 4;
		पूर्ण
		l += scnम_लिखो(out + l, sz - l, mem_lvl[i]);
	पूर्ण

	अगर (mem_info && mem_info->data_src.mem_lvl_num) अणु
		पूर्णांक lvl = mem_info->data_src.mem_lvl_num;
		अगर (prपूर्णांकed++) अणु
			म_जोड़ो(out, " or ");
			l += 4;
		पूर्ण
		अगर (mem_lvlnum[lvl])
			l += scnम_लिखो(out + l, sz - l, mem_lvlnum[lvl]);
		अन्यथा
			l += scnम_लिखो(out + l, sz - l, "L%d", lvl);
	पूर्ण

	अगर (l == 0)
		l += scnम_लिखो(out + l, sz - l, "N/A");
	अगर (hit)
		l += scnम_लिखो(out + l, sz - l, " hit");
	अगर (miss)
		l += scnम_लिखो(out + l, sz - l, " miss");

	वापस l;
पूर्ण

अटल स्थिर अक्षर * स्थिर snoop_access[] = अणु
	"N/A",
	"None",
	"Hit",
	"Miss",
	"HitM",
पूर्ण;

पूर्णांक perf_mem__snp_scnम_लिखो(अक्षर *out, माप_प्रकार sz, काष्ठा mem_info *mem_info)
अणु
	माप_प्रकार i, l = 0;
	u64 m = PERF_MEM_SNOOP_NA;

	sz -= 1; /* -1 क्रम null termination */
	out[0] = '\0';

	अगर (mem_info)
		m = mem_info->data_src.mem_snoop;

	क्रम (i = 0; m && i < ARRAY_SIZE(snoop_access); i++, m >>= 1) अणु
		अगर (!(m & 0x1))
			जारी;
		अगर (l) अणु
			म_जोड़ो(out, " or ");
			l += 4;
		पूर्ण
		l += scnम_लिखो(out + l, sz - l, snoop_access[i]);
	पूर्ण
	अगर (mem_info &&
	     (mem_info->data_src.mem_snoopx & PERF_MEM_SNOOPX_FWD)) अणु
		अगर (l) अणु
			म_जोड़ो(out, " or ");
			l += 4;
		पूर्ण
		l += scnम_लिखो(out + l, sz - l, "Fwd");
	पूर्ण

	अगर (*out == '\0')
		l += scnम_लिखो(out, sz - l, "N/A");

	वापस l;
पूर्ण

पूर्णांक perf_mem__lck_scnम_लिखो(अक्षर *out, माप_प्रकार sz, काष्ठा mem_info *mem_info)
अणु
	u64 mask = PERF_MEM_LOCK_NA;
	पूर्णांक l;

	अगर (mem_info)
		mask = mem_info->data_src.mem_lock;

	अगर (mask & PERF_MEM_LOCK_NA)
		l = scnम_लिखो(out, sz, "N/A");
	अन्यथा अगर (mask & PERF_MEM_LOCK_LOCKED)
		l = scnम_लिखो(out, sz, "Yes");
	अन्यथा
		l = scnम_लिखो(out, sz, "No");

	वापस l;
पूर्ण

पूर्णांक perf_mem__blk_scnम_लिखो(अक्षर *out, माप_प्रकार sz, काष्ठा mem_info *mem_info)
अणु
	माप_प्रकार l = 0;
	u64 mask = PERF_MEM_BLK_NA;

	sz -= 1; /* -1 क्रम null termination */
	out[0] = '\0';

	अगर (mem_info)
		mask = mem_info->data_src.mem_blk;

	अगर (!mask || (mask & PERF_MEM_BLK_NA)) अणु
		l += scnम_लिखो(out + l, sz - l, " N/A");
		वापस l;
	पूर्ण
	अगर (mask & PERF_MEM_BLK_DATA)
		l += scnम_लिखो(out + l, sz - l, " Data");
	अगर (mask & PERF_MEM_BLK_ADDR)
		l += scnम_लिखो(out + l, sz - l, " Addr");

	वापस l;
पूर्ण

पूर्णांक perf_script__meminfo_scnम_लिखो(अक्षर *out, माप_प्रकार sz, काष्ठा mem_info *mem_info)
अणु
	पूर्णांक i = 0;

	i += perf_mem__lvl_scnम_लिखो(out, sz, mem_info);
	i += scnम_लिखो(out + i, sz - i, "|SNP ");
	i += perf_mem__snp_scnम_लिखो(out + i, sz - i, mem_info);
	i += scnम_लिखो(out + i, sz - i, "|TLB ");
	i += perf_mem__tlb_scnम_लिखो(out + i, sz - i, mem_info);
	i += scnम_लिखो(out + i, sz - i, "|LCK ");
	i += perf_mem__lck_scnम_लिखो(out + i, sz - i, mem_info);
	i += scnम_लिखो(out + i, sz - i, "|BLK ");
	i += perf_mem__blk_scnम_लिखो(out + i, sz - i, mem_info);

	वापस i;
पूर्ण

पूर्णांक c2c_decode_stats(काष्ठा c2c_stats *stats, काष्ठा mem_info *mi)
अणु
	जोड़ perf_mem_data_src *data_src = &mi->data_src;
	u64 daddr  = mi->daddr.addr;
	u64 op     = data_src->mem_op;
	u64 lvl    = data_src->mem_lvl;
	u64 snoop  = data_src->mem_snoop;
	u64 lock   = data_src->mem_lock;
	u64 blk    = data_src->mem_blk;
	/*
	 * Skylake might report unknown remote level via this
	 * bit, consider it when evaluating remote HITMs.
	 */
	bool mrem  = data_src->mem_remote;
	पूर्णांक err = 0;

#घोषणा HITM_INC(__f)		\
करो अणु				\
	stats->__f++;		\
	stats->tot_hiपंचांग++;	\
पूर्ण जबतक (0)

#घोषणा P(a, b) PERF_MEM_##a##_##b

	stats->nr_entries++;

	अगर (lock & P(LOCK, LOCKED)) stats->locks++;

	अगर (blk & P(BLK, DATA)) stats->blk_data++;
	अगर (blk & P(BLK, ADDR)) stats->blk_addr++;

	अगर (op & P(OP, LOAD)) अणु
		/* load */
		stats->load++;

		अगर (!daddr) अणु
			stats->ld_noadrs++;
			वापस -1;
		पूर्ण

		अगर (lvl & P(LVL, HIT)) अणु
			अगर (lvl & P(LVL, UNC)) stats->ld_uncache++;
			अगर (lvl & P(LVL, IO))  stats->ld_io++;
			अगर (lvl & P(LVL, LFB)) stats->ld_fbhit++;
			अगर (lvl & P(LVL, L1 )) stats->ld_l1hit++;
			अगर (lvl & P(LVL, L2 )) stats->ld_l2hit++;
			अगर (lvl & P(LVL, L3 )) अणु
				अगर (snoop & P(SNOOP, HITM))
					HITM_INC(lcl_hiपंचांग);
				अन्यथा
					stats->ld_llchit++;
			पूर्ण

			अगर (lvl & P(LVL, LOC_RAM)) अणु
				stats->lcl_dram++;
				अगर (snoop & P(SNOOP, HIT))
					stats->ld_shared++;
				अन्यथा
					stats->ld_excl++;
			पूर्ण

			अगर ((lvl & P(LVL, REM_RAM1)) ||
			    (lvl & P(LVL, REM_RAM2)) ||
			     mrem) अणु
				stats->rmt_dram++;
				अगर (snoop & P(SNOOP, HIT))
					stats->ld_shared++;
				अन्यथा
					stats->ld_excl++;
			पूर्ण
		पूर्ण

		अगर ((lvl & P(LVL, REM_CCE1)) ||
		    (lvl & P(LVL, REM_CCE2)) ||
		     mrem) अणु
			अगर (snoop & P(SNOOP, HIT))
				stats->rmt_hit++;
			अन्यथा अगर (snoop & P(SNOOP, HITM))
				HITM_INC(rmt_hiपंचांग);
		पूर्ण

		अगर ((lvl & P(LVL, MISS)))
			stats->ld_miss++;

	पूर्ण अन्यथा अगर (op & P(OP, STORE)) अणु
		/* store */
		stats->store++;

		अगर (!daddr) अणु
			stats->st_noadrs++;
			वापस -1;
		पूर्ण

		अगर (lvl & P(LVL, HIT)) अणु
			अगर (lvl & P(LVL, UNC)) stats->st_uncache++;
			अगर (lvl & P(LVL, L1 )) stats->st_l1hit++;
		पूर्ण
		अगर (lvl & P(LVL, MISS))
			अगर (lvl & P(LVL, L1)) stats->st_l1miss++;
	पूर्ण अन्यथा अणु
		/* unparsable data_src? */
		stats->noparse++;
		वापस -1;
	पूर्ण

	अगर (!mi->daddr.ms.map || !mi->iaddr.ms.map) अणु
		stats->nomap++;
		वापस -1;
	पूर्ण

#अघोषित P
#अघोषित HITM_INC
	वापस err;
पूर्ण

व्योम c2c_add_stats(काष्ठा c2c_stats *stats, काष्ठा c2c_stats *add)
अणु
	stats->nr_entries	+= add->nr_entries;

	stats->locks		+= add->locks;
	stats->store		+= add->store;
	stats->st_uncache	+= add->st_uncache;
	stats->st_noadrs	+= add->st_noadrs;
	stats->st_l1hit		+= add->st_l1hit;
	stats->st_l1miss	+= add->st_l1miss;
	stats->load		+= add->load;
	stats->ld_excl		+= add->ld_excl;
	stats->ld_shared	+= add->ld_shared;
	stats->ld_uncache	+= add->ld_uncache;
	stats->ld_io		+= add->ld_io;
	stats->ld_miss		+= add->ld_miss;
	stats->ld_noadrs	+= add->ld_noadrs;
	stats->ld_fbhit		+= add->ld_fbhit;
	stats->ld_l1hit		+= add->ld_l1hit;
	stats->ld_l2hit		+= add->ld_l2hit;
	stats->ld_llchit	+= add->ld_llchit;
	stats->lcl_hiपंचांग		+= add->lcl_hiपंचांग;
	stats->rmt_hiपंचांग		+= add->rmt_hiपंचांग;
	stats->tot_hiपंचांग		+= add->tot_hiपंचांग;
	stats->rmt_hit		+= add->rmt_hit;
	stats->lcl_dram		+= add->lcl_dram;
	stats->rmt_dram		+= add->rmt_dram;
	stats->blk_data		+= add->blk_data;
	stats->blk_addr		+= add->blk_addr;
	stats->nomap		+= add->nomap;
	stats->noparse		+= add->noparse;
पूर्ण
