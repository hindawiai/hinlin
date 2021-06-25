<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __PERF_MEM_EVENTS_H
#घोषणा __PERF_MEM_EVENTS_H

#समावेश <stdbool.h>
#समावेश <मानक_निवेशt.h>
#समावेश <मानकपन.स>
#समावेश <linux/types.h>
#समावेश <linux/refcount.h>
#समावेश <linux/perf_event.h>
#समावेश "stat.h"
#समावेश "evsel.h"

काष्ठा perf_mem_event अणु
	bool		record;
	bool		supported;
	स्थिर अक्षर	*tag;
	स्थिर अक्षर	*name;
	स्थिर अक्षर	*sysfs_name;
पूर्ण;

काष्ठा mem_info अणु
	काष्ठा addr_map_symbol	iaddr;
	काष्ठा addr_map_symbol	daddr;
	जोड़ perf_mem_data_src	data_src;
	refcount_t		refcnt;
पूर्ण;

क्रमागत अणु
	PERF_MEM_EVENTS__LOAD,
	PERF_MEM_EVENTS__STORE,
	PERF_MEM_EVENTS__LOAD_STORE,
	PERF_MEM_EVENTS__MAX,
पूर्ण;

बाह्य अचिन्हित पूर्णांक perf_mem_events__loads_ldlat;

पूर्णांक perf_mem_events__parse(स्थिर अक्षर *str);
पूर्णांक perf_mem_events__init(व्योम);

अक्षर *perf_mem_events__name(पूर्णांक i);
काष्ठा perf_mem_event *perf_mem_events__ptr(पूर्णांक i);
bool is_mem_loads_aux_event(काष्ठा evsel *leader);

व्योम perf_mem_events__list(व्योम);

पूर्णांक perf_mem__tlb_scnम_लिखो(अक्षर *out, माप_प्रकार sz, काष्ठा mem_info *mem_info);
पूर्णांक perf_mem__lvl_scnम_लिखो(अक्षर *out, माप_प्रकार sz, काष्ठा mem_info *mem_info);
पूर्णांक perf_mem__snp_scnम_लिखो(अक्षर *out, माप_प्रकार sz, काष्ठा mem_info *mem_info);
पूर्णांक perf_mem__lck_scnम_लिखो(अक्षर *out, माप_प्रकार sz, काष्ठा mem_info *mem_info);
पूर्णांक perf_mem__blk_scnम_लिखो(अक्षर *out, माप_प्रकार sz, काष्ठा mem_info *mem_info);

पूर्णांक perf_script__meminfo_scnम_लिखो(अक्षर *bf, माप_प्रकार size, काष्ठा mem_info *mem_info);

काष्ठा c2c_stats अणु
	u32	nr_entries;

	u32	locks;               /* count of 'lock' transactions */
	u32	store;               /* count of all stores in trace */
	u32	st_uncache;          /* stores to uncacheable address */
	u32	st_noadrs;           /* cacheable store with no address */
	u32	st_l1hit;            /* count of stores that hit L1D */
	u32	st_l1miss;           /* count of stores that miss L1D */
	u32	load;                /* count of all loads in trace */
	u32	ld_excl;             /* exclusive loads, rmt/lcl DRAM - snp none/miss */
	u32	ld_shared;           /* shared loads, rmt/lcl DRAM - snp hit */
	u32	ld_uncache;          /* loads to uncacheable address */
	u32	ld_io;               /* loads to io address */
	u32	ld_miss;             /* loads miss */
	u32	ld_noadrs;           /* cacheable load with no address */
	u32	ld_fbhit;            /* count of loads hitting Fill Buffer */
	u32	ld_l1hit;            /* count of loads that hit L1D */
	u32	ld_l2hit;            /* count of loads that hit L2D */
	u32	ld_llchit;           /* count of loads that hit LLC */
	u32	lcl_hiपंचांग;            /* count of loads with local HITM  */
	u32	rmt_hiपंचांग;            /* count of loads with remote HITM */
	u32	tot_hiपंचांग;            /* count of loads with local and remote HITM */
	u32	rmt_hit;             /* count of loads with remote hit clean; */
	u32	lcl_dram;            /* count of loads miss to local DRAM */
	u32	rmt_dram;            /* count of loads miss to remote DRAM */
	u32	blk_data;            /* count of loads blocked by data */
	u32	blk_addr;            /* count of loads blocked by address conflict */
	u32	nomap;               /* count of load/stores with no phys addrs */
	u32	noparse;             /* count of unparsable data sources */
पूर्ण;

काष्ठा hist_entry;
पूर्णांक c2c_decode_stats(काष्ठा c2c_stats *stats, काष्ठा mem_info *mi);
व्योम c2c_add_stats(काष्ठा c2c_stats *stats, काष्ठा c2c_stats *add);

#पूर्ण_अगर /* __PERF_MEM_EVENTS_H */
