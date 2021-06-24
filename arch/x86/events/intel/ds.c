<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/bitops.h>
#समावेश <linux/types.h>
#समावेश <linux/slab.h>

#समावेश <यंत्र/cpu_entry_area.h>
#समावेश <यंत्र/perf_event.h>
#समावेश <यंत्र/tlbflush.h>
#समावेश <यंत्र/insn.h>
#समावेश <यंत्र/पन.स>

#समावेश "../perf_event.h"

/* Waste a full page so it can be mapped पूर्णांकo the cpu_entry_area */
DEFINE_PER_CPU_PAGE_ALIGNED(काष्ठा debug_store, cpu_debug_store);

/* The size of a BTS record in bytes: */
#घोषणा BTS_RECORD_SIZE		24

#घोषणा PEBS_FIXUP_SIZE		PAGE_SIZE

/*
 * pebs_record_32 क्रम p4 and core not supported

काष्ठा pebs_record_32 अणु
	u32 flags, ip;
	u32 ax, bc, cx, dx;
	u32 si, di, bp, sp;
पूर्ण;

 */

जोड़ पूर्णांकel_x86_pebs_dse अणु
	u64 val;
	काष्ठा अणु
		अचिन्हित पूर्णांक ld_dse:4;
		अचिन्हित पूर्णांक ld_stlb_miss:1;
		अचिन्हित पूर्णांक ld_locked:1;
		अचिन्हित पूर्णांक ld_data_blk:1;
		अचिन्हित पूर्णांक ld_addr_blk:1;
		अचिन्हित पूर्णांक ld_reserved:24;
	पूर्ण;
	काष्ठा अणु
		अचिन्हित पूर्णांक st_l1d_hit:1;
		अचिन्हित पूर्णांक st_reserved1:3;
		अचिन्हित पूर्णांक st_stlb_miss:1;
		अचिन्हित पूर्णांक st_locked:1;
		अचिन्हित पूर्णांक st_reserved2:26;
	पूर्ण;
	काष्ठा अणु
		अचिन्हित पूर्णांक st_lat_dse:4;
		अचिन्हित पूर्णांक st_lat_stlb_miss:1;
		अचिन्हित पूर्णांक st_lat_locked:1;
		अचिन्हित पूर्णांक ld_reserved3:26;
	पूर्ण;
पूर्ण;


/*
 * Map PEBS Load Latency Data Source encodings to generic
 * memory data source inक्रमmation
 */
#घोषणा P(a, b) PERF_MEM_S(a, b)
#घोषणा OP_LH (P(OP, LOAD) | P(LVL, HIT))
#घोषणा LEVEL(x) P(LVLNUM, x)
#घोषणा REM P(REMOTE, REMOTE)
#घोषणा SNOOP_NONE_MISS (P(SNOOP, NONE) | P(SNOOP, MISS))

/* Version क्रम Sandy Bridge and later */
अटल u64 pebs_data_source[] = अणु
	P(OP, LOAD) | P(LVL, MISS) | LEVEL(L3) | P(SNOOP, NA),/* 0x00:ukn L3 */
	OP_LH | P(LVL, L1)  | LEVEL(L1) | P(SNOOP, NONE),  /* 0x01: L1 local */
	OP_LH | P(LVL, LFB) | LEVEL(LFB) | P(SNOOP, NONE), /* 0x02: LFB hit */
	OP_LH | P(LVL, L2)  | LEVEL(L2) | P(SNOOP, NONE),  /* 0x03: L2 hit */
	OP_LH | P(LVL, L3)  | LEVEL(L3) | P(SNOOP, NONE),  /* 0x04: L3 hit */
	OP_LH | P(LVL, L3)  | LEVEL(L3) | P(SNOOP, MISS),  /* 0x05: L3 hit, snoop miss */
	OP_LH | P(LVL, L3)  | LEVEL(L3) | P(SNOOP, HIT),   /* 0x06: L3 hit, snoop hit */
	OP_LH | P(LVL, L3)  | LEVEL(L3) | P(SNOOP, HITM),  /* 0x07: L3 hit, snoop hiपंचांग */
	OP_LH | P(LVL, REM_CCE1) | REM | LEVEL(L3) | P(SNOOP, HIT),  /* 0x08: L3 miss snoop hit */
	OP_LH | P(LVL, REM_CCE1) | REM | LEVEL(L3) | P(SNOOP, HITM), /* 0x09: L3 miss snoop hiपंचांग*/
	OP_LH | P(LVL, LOC_RAM)  | LEVEL(RAM) | P(SNOOP, HIT),       /* 0x0a: L3 miss, shared */
	OP_LH | P(LVL, REM_RAM1) | REM | LEVEL(L3) | P(SNOOP, HIT),  /* 0x0b: L3 miss, shared */
	OP_LH | P(LVL, LOC_RAM)  | LEVEL(RAM) | SNOOP_NONE_MISS,     /* 0x0c: L3 miss, excl */
	OP_LH | P(LVL, REM_RAM1) | LEVEL(RAM) | REM | SNOOP_NONE_MISS, /* 0x0d: L3 miss, excl */
	OP_LH | P(LVL, IO)  | LEVEL(NA) | P(SNOOP, NONE), /* 0x0e: I/O */
	OP_LH | P(LVL, UNC) | LEVEL(NA) | P(SNOOP, NONE), /* 0x0f: uncached */
पूर्ण;

/* Patch up minor dअगरferences in the bits */
व्योम __init पूर्णांकel_pmu_pebs_data_source_nhm(व्योम)
अणु
	pebs_data_source[0x05] = OP_LH | P(LVL, L3) | LEVEL(L3) | P(SNOOP, HIT);
	pebs_data_source[0x06] = OP_LH | P(LVL, L3) | LEVEL(L3) | P(SNOOP, HITM);
	pebs_data_source[0x07] = OP_LH | P(LVL, L3) | LEVEL(L3) | P(SNOOP, HITM);
पूर्ण

व्योम __init पूर्णांकel_pmu_pebs_data_source_skl(bool pmem)
अणु
	u64 pmem_or_l4 = pmem ? LEVEL(PMEM) : LEVEL(L4);

	pebs_data_source[0x08] = OP_LH | pmem_or_l4 | P(SNOOP, HIT);
	pebs_data_source[0x09] = OP_LH | pmem_or_l4 | REM | P(SNOOP, HIT);
	pebs_data_source[0x0b] = OP_LH | LEVEL(RAM) | REM | P(SNOOP, NONE);
	pebs_data_source[0x0c] = OP_LH | LEVEL(ANY_CACHE) | REM | P(SNOOPX, FWD);
	pebs_data_source[0x0d] = OP_LH | LEVEL(ANY_CACHE) | REM | P(SNOOP, HITM);
पूर्ण

अटल u64 precise_store_data(u64 status)
अणु
	जोड़ पूर्णांकel_x86_pebs_dse dse;
	u64 val = P(OP, STORE) | P(SNOOP, NA) | P(LVL, L1) | P(TLB, L2);

	dse.val = status;

	/*
	 * bit 4: TLB access
	 * 1 = stored missed 2nd level TLB
	 *
	 * so it either hit the walker or the OS
	 * otherwise hit 2nd level TLB
	 */
	अगर (dse.st_stlb_miss)
		val |= P(TLB, MISS);
	अन्यथा
		val |= P(TLB, HIT);

	/*
	 * bit 0: hit L1 data cache
	 * अगर not set, then all we know is that
	 * it missed L1D
	 */
	अगर (dse.st_l1d_hit)
		val |= P(LVL, HIT);
	अन्यथा
		val |= P(LVL, MISS);

	/*
	 * bit 5: Locked prefix
	 */
	अगर (dse.st_locked)
		val |= P(LOCK, LOCKED);

	वापस val;
पूर्ण

अटल u64 precise_datala_hsw(काष्ठा perf_event *event, u64 status)
अणु
	जोड़ perf_mem_data_src dse;

	dse.val = PERF_MEM_NA;

	अगर (event->hw.flags & PERF_X86_EVENT_PEBS_ST_HSW)
		dse.mem_op = PERF_MEM_OP_STORE;
	अन्यथा अगर (event->hw.flags & PERF_X86_EVENT_PEBS_LD_HSW)
		dse.mem_op = PERF_MEM_OP_LOAD;

	/*
	 * L1 info only valid क्रम following events:
	 *
	 * MEM_UOPS_RETIRED.STLB_MISS_STORES
	 * MEM_UOPS_RETIRED.LOCK_STORES
	 * MEM_UOPS_RETIRED.SPLIT_STORES
	 * MEM_UOPS_RETIRED.ALL_STORES
	 */
	अगर (event->hw.flags & PERF_X86_EVENT_PEBS_ST_HSW) अणु
		अगर (status & 1)
			dse.mem_lvl = PERF_MEM_LVL_L1 | PERF_MEM_LVL_HIT;
		अन्यथा
			dse.mem_lvl = PERF_MEM_LVL_L1 | PERF_MEM_LVL_MISS;
	पूर्ण
	वापस dse.val;
पूर्ण

अटल u64 load_latency_data(u64 status)
अणु
	जोड़ पूर्णांकel_x86_pebs_dse dse;
	u64 val;

	dse.val = status;

	/*
	 * use the mapping table क्रम bit 0-3
	 */
	val = pebs_data_source[dse.ld_dse];

	/*
	 * Nehalem models करो not support TLB, Lock infos
	 */
	अगर (x86_pmu.pebs_no_tlb) अणु
		val |= P(TLB, NA) | P(LOCK, NA);
		वापस val;
	पूर्ण
	/*
	 * bit 4: TLB access
	 * 0 = did not miss 2nd level TLB
	 * 1 = missed 2nd level TLB
	 */
	अगर (dse.ld_stlb_miss)
		val |= P(TLB, MISS) | P(TLB, L2);
	अन्यथा
		val |= P(TLB, HIT) | P(TLB, L1) | P(TLB, L2);

	/*
	 * bit 5: locked prefix
	 */
	अगर (dse.ld_locked)
		val |= P(LOCK, LOCKED);

	/*
	 * Ice Lake and earlier models करो not support block infos.
	 */
	अगर (!x86_pmu.pebs_block) अणु
		val |= P(BLK, NA);
		वापस val;
	पूर्ण
	/*
	 * bit 6: load was blocked since its data could not be क्रमwarded
	 *        from a preceding store
	 */
	अगर (dse.ld_data_blk)
		val |= P(BLK, DATA);

	/*
	 * bit 7: load was blocked due to potential address conflict with
	 *        a preceding store
	 */
	अगर (dse.ld_addr_blk)
		val |= P(BLK, ADDR);

	अगर (!dse.ld_data_blk && !dse.ld_addr_blk)
		val |= P(BLK, NA);

	वापस val;
पूर्ण

अटल u64 store_latency_data(u64 status)
अणु
	जोड़ पूर्णांकel_x86_pebs_dse dse;
	u64 val;

	dse.val = status;

	/*
	 * use the mapping table क्रम bit 0-3
	 */
	val = pebs_data_source[dse.st_lat_dse];

	/*
	 * bit 4: TLB access
	 * 0 = did not miss 2nd level TLB
	 * 1 = missed 2nd level TLB
	 */
	अगर (dse.st_lat_stlb_miss)
		val |= P(TLB, MISS) | P(TLB, L2);
	अन्यथा
		val |= P(TLB, HIT) | P(TLB, L1) | P(TLB, L2);

	/*
	 * bit 5: locked prefix
	 */
	अगर (dse.st_lat_locked)
		val |= P(LOCK, LOCKED);

	val |= P(BLK, NA);

	वापस val;
पूर्ण

काष्ठा pebs_record_core अणु
	u64 flags, ip;
	u64 ax, bx, cx, dx;
	u64 si, di, bp, sp;
	u64 r8,  r9,  r10, r11;
	u64 r12, r13, r14, r15;
पूर्ण;

काष्ठा pebs_record_nhm अणु
	u64 flags, ip;
	u64 ax, bx, cx, dx;
	u64 si, di, bp, sp;
	u64 r8,  r9,  r10, r11;
	u64 r12, r13, r14, r15;
	u64 status, dla, dse, lat;
पूर्ण;

/*
 * Same as pebs_record_nhm, with two additional fields.
 */
काष्ठा pebs_record_hsw अणु
	u64 flags, ip;
	u64 ax, bx, cx, dx;
	u64 si, di, bp, sp;
	u64 r8,  r9,  r10, r11;
	u64 r12, r13, r14, r15;
	u64 status, dla, dse, lat;
	u64 real_ip, tsx_tuning;
पूर्ण;

जोड़ hsw_tsx_tuning अणु
	काष्ठा अणु
		u32 cycles_last_block     : 32,
		    hle_पात		  : 1,
		    rपंचांग_पात		  : 1,
		    inकाष्ठाion_पात     : 1,
		    non_inकाष्ठाion_पात : 1,
		    retry		  : 1,
		    data_conflict	  : 1,
		    capacity_ग_लिखोs	  : 1,
		    capacity_पढ़ोs	  : 1;
	पूर्ण;
	u64	    value;
पूर्ण;

#घोषणा PEBS_HSW_TSX_FLAGS	0xff00000000ULL

/* Same as HSW, plus TSC */

काष्ठा pebs_record_skl अणु
	u64 flags, ip;
	u64 ax, bx, cx, dx;
	u64 si, di, bp, sp;
	u64 r8,  r9,  r10, r11;
	u64 r12, r13, r14, r15;
	u64 status, dla, dse, lat;
	u64 real_ip, tsx_tuning;
	u64 tsc;
पूर्ण;

व्योम init_debug_store_on_cpu(पूर्णांक cpu)
अणु
	काष्ठा debug_store *ds = per_cpu(cpu_hw_events, cpu).ds;

	अगर (!ds)
		वापस;

	wrmsr_on_cpu(cpu, MSR_IA32_DS_AREA,
		     (u32)((u64)(अचिन्हित दीर्घ)ds),
		     (u32)((u64)(अचिन्हित दीर्घ)ds >> 32));
पूर्ण

व्योम fini_debug_store_on_cpu(पूर्णांक cpu)
अणु
	अगर (!per_cpu(cpu_hw_events, cpu).ds)
		वापस;

	wrmsr_on_cpu(cpu, MSR_IA32_DS_AREA, 0, 0);
पूर्ण

अटल DEFINE_PER_CPU(व्योम *, insn_buffer);

अटल व्योम ds_update_cea(व्योम *cea, व्योम *addr, माप_प्रकार size, pgprot_t prot)
अणु
	अचिन्हित दीर्घ start = (अचिन्हित दीर्घ)cea;
	phys_addr_t pa;
	माप_प्रकार msz = 0;

	pa = virt_to_phys(addr);

	preempt_disable();
	क्रम (; msz < size; msz += PAGE_SIZE, pa += PAGE_SIZE, cea += PAGE_SIZE)
		cea_set_pte(cea, pa, prot);

	/*
	 * This is a cross-CPU update of the cpu_entry_area, we must shoot करोwn
	 * all TLB entries क्रम it.
	 */
	flush_tlb_kernel_range(start, start + size);
	preempt_enable();
पूर्ण

अटल व्योम ds_clear_cea(व्योम *cea, माप_प्रकार size)
अणु
	अचिन्हित दीर्घ start = (अचिन्हित दीर्घ)cea;
	माप_प्रकार msz = 0;

	preempt_disable();
	क्रम (; msz < size; msz += PAGE_SIZE, cea += PAGE_SIZE)
		cea_set_pte(cea, 0, PAGE_NONE);

	flush_tlb_kernel_range(start, start + size);
	preempt_enable();
पूर्ण

अटल व्योम *dsalloc_pages(माप_प्रकार size, gfp_t flags, पूर्णांक cpu)
अणु
	अचिन्हित पूर्णांक order = get_order(size);
	पूर्णांक node = cpu_to_node(cpu);
	काष्ठा page *page;

	page = __alloc_pages_node(node, flags | __GFP_ZERO, order);
	वापस page ? page_address(page) : शून्य;
पूर्ण

अटल व्योम dsमुक्त_pages(स्थिर व्योम *buffer, माप_प्रकार size)
अणु
	अगर (buffer)
		मुक्त_pages((अचिन्हित दीर्घ)buffer, get_order(size));
पूर्ण

अटल पूर्णांक alloc_pebs_buffer(पूर्णांक cpu)
अणु
	काष्ठा cpu_hw_events *hwev = per_cpu_ptr(&cpu_hw_events, cpu);
	काष्ठा debug_store *ds = hwev->ds;
	माप_प्रकार bsiz = x86_pmu.pebs_buffer_size;
	पूर्णांक max, node = cpu_to_node(cpu);
	व्योम *buffer, *insn_buff, *cea;

	अगर (!x86_pmu.pebs)
		वापस 0;

	buffer = dsalloc_pages(bsiz, GFP_KERNEL, cpu);
	अगर (unlikely(!buffer))
		वापस -ENOMEM;

	/*
	 * HSW+ alपढ़ोy provides us the eventing ip; no need to allocate this
	 * buffer then.
	 */
	अगर (x86_pmu.पूर्णांकel_cap.pebs_क्रमmat < 2) अणु
		insn_buff = kzalloc_node(PEBS_FIXUP_SIZE, GFP_KERNEL, node);
		अगर (!insn_buff) अणु
			dsमुक्त_pages(buffer, bsiz);
			वापस -ENOMEM;
		पूर्ण
		per_cpu(insn_buffer, cpu) = insn_buff;
	पूर्ण
	hwev->ds_pebs_vaddr = buffer;
	/* Update the cpu entry area mapping */
	cea = &get_cpu_entry_area(cpu)->cpu_debug_buffers.pebs_buffer;
	ds->pebs_buffer_base = (अचिन्हित दीर्घ) cea;
	ds_update_cea(cea, buffer, bsiz, PAGE_KERNEL);
	ds->pebs_index = ds->pebs_buffer_base;
	max = x86_pmu.pebs_record_size * (bsiz / x86_pmu.pebs_record_size);
	ds->pebs_असलolute_maximum = ds->pebs_buffer_base + max;
	वापस 0;
पूर्ण

अटल व्योम release_pebs_buffer(पूर्णांक cpu)
अणु
	काष्ठा cpu_hw_events *hwev = per_cpu_ptr(&cpu_hw_events, cpu);
	व्योम *cea;

	अगर (!x86_pmu.pebs)
		वापस;

	kमुक्त(per_cpu(insn_buffer, cpu));
	per_cpu(insn_buffer, cpu) = शून्य;

	/* Clear the fixmap */
	cea = &get_cpu_entry_area(cpu)->cpu_debug_buffers.pebs_buffer;
	ds_clear_cea(cea, x86_pmu.pebs_buffer_size);
	dsमुक्त_pages(hwev->ds_pebs_vaddr, x86_pmu.pebs_buffer_size);
	hwev->ds_pebs_vaddr = शून्य;
पूर्ण

अटल पूर्णांक alloc_bts_buffer(पूर्णांक cpu)
अणु
	काष्ठा cpu_hw_events *hwev = per_cpu_ptr(&cpu_hw_events, cpu);
	काष्ठा debug_store *ds = hwev->ds;
	व्योम *buffer, *cea;
	पूर्णांक max;

	अगर (!x86_pmu.bts)
		वापस 0;

	buffer = dsalloc_pages(BTS_BUFFER_SIZE, GFP_KERNEL | __GFP_NOWARN, cpu);
	अगर (unlikely(!buffer)) अणु
		WARN_ONCE(1, "%s: BTS buffer allocation failure\n", __func__);
		वापस -ENOMEM;
	पूर्ण
	hwev->ds_bts_vaddr = buffer;
	/* Update the fixmap */
	cea = &get_cpu_entry_area(cpu)->cpu_debug_buffers.bts_buffer;
	ds->bts_buffer_base = (अचिन्हित दीर्घ) cea;
	ds_update_cea(cea, buffer, BTS_BUFFER_SIZE, PAGE_KERNEL);
	ds->bts_index = ds->bts_buffer_base;
	max = BTS_BUFFER_SIZE / BTS_RECORD_SIZE;
	ds->bts_असलolute_maximum = ds->bts_buffer_base +
					max * BTS_RECORD_SIZE;
	ds->bts_पूर्णांकerrupt_threshold = ds->bts_असलolute_maximum -
					(max / 16) * BTS_RECORD_SIZE;
	वापस 0;
पूर्ण

अटल व्योम release_bts_buffer(पूर्णांक cpu)
अणु
	काष्ठा cpu_hw_events *hwev = per_cpu_ptr(&cpu_hw_events, cpu);
	व्योम *cea;

	अगर (!x86_pmu.bts)
		वापस;

	/* Clear the fixmap */
	cea = &get_cpu_entry_area(cpu)->cpu_debug_buffers.bts_buffer;
	ds_clear_cea(cea, BTS_BUFFER_SIZE);
	dsमुक्त_pages(hwev->ds_bts_vaddr, BTS_BUFFER_SIZE);
	hwev->ds_bts_vaddr = शून्य;
पूर्ण

अटल पूर्णांक alloc_ds_buffer(पूर्णांक cpu)
अणु
	काष्ठा debug_store *ds = &get_cpu_entry_area(cpu)->cpu_debug_store;

	स_रखो(ds, 0, माप(*ds));
	per_cpu(cpu_hw_events, cpu).ds = ds;
	वापस 0;
पूर्ण

अटल व्योम release_ds_buffer(पूर्णांक cpu)
अणु
	per_cpu(cpu_hw_events, cpu).ds = शून्य;
पूर्ण

व्योम release_ds_buffers(व्योम)
अणु
	पूर्णांक cpu;

	अगर (!x86_pmu.bts && !x86_pmu.pebs)
		वापस;

	क्रम_each_possible_cpu(cpu)
		release_ds_buffer(cpu);

	क्रम_each_possible_cpu(cpu) अणु
		/*
		 * Again, ignore errors from offline CPUs, they will no दीर्घer
		 * observe cpu_hw_events.ds and not program the DS_AREA when
		 * they come up.
		 */
		fini_debug_store_on_cpu(cpu);
	पूर्ण

	क्रम_each_possible_cpu(cpu) अणु
		release_pebs_buffer(cpu);
		release_bts_buffer(cpu);
	पूर्ण
पूर्ण

व्योम reserve_ds_buffers(व्योम)
अणु
	पूर्णांक bts_err = 0, pebs_err = 0;
	पूर्णांक cpu;

	x86_pmu.bts_active = 0;
	x86_pmu.pebs_active = 0;

	अगर (!x86_pmu.bts && !x86_pmu.pebs)
		वापस;

	अगर (!x86_pmu.bts)
		bts_err = 1;

	अगर (!x86_pmu.pebs)
		pebs_err = 1;

	क्रम_each_possible_cpu(cpu) अणु
		अगर (alloc_ds_buffer(cpu)) अणु
			bts_err = 1;
			pebs_err = 1;
		पूर्ण

		अगर (!bts_err && alloc_bts_buffer(cpu))
			bts_err = 1;

		अगर (!pebs_err && alloc_pebs_buffer(cpu))
			pebs_err = 1;

		अगर (bts_err && pebs_err)
			अवरोध;
	पूर्ण

	अगर (bts_err) अणु
		क्रम_each_possible_cpu(cpu)
			release_bts_buffer(cpu);
	पूर्ण

	अगर (pebs_err) अणु
		क्रम_each_possible_cpu(cpu)
			release_pebs_buffer(cpu);
	पूर्ण

	अगर (bts_err && pebs_err) अणु
		क्रम_each_possible_cpu(cpu)
			release_ds_buffer(cpu);
	पूर्ण अन्यथा अणु
		अगर (x86_pmu.bts && !bts_err)
			x86_pmu.bts_active = 1;

		अगर (x86_pmu.pebs && !pebs_err)
			x86_pmu.pebs_active = 1;

		क्रम_each_possible_cpu(cpu) अणु
			/*
			 * Ignores wrmsr_on_cpu() errors क्रम offline CPUs they
			 * will get this call through पूर्णांकel_pmu_cpu_starting().
			 */
			init_debug_store_on_cpu(cpu);
		पूर्ण
	पूर्ण
पूर्ण

/*
 * BTS
 */

काष्ठा event_स्थिरraपूर्णांक bts_स्थिरraपूर्णांक =
	EVENT_CONSTRAINT(0, 1ULL << INTEL_PMC_IDX_FIXED_BTS, 0);

व्योम पूर्णांकel_pmu_enable_bts(u64 config)
अणु
	अचिन्हित दीर्घ debugctlmsr;

	debugctlmsr = get_debugctlmsr();

	debugctlmsr |= DEBUGCTLMSR_TR;
	debugctlmsr |= DEBUGCTLMSR_BTS;
	अगर (config & ARCH_PERFMON_EVENTSEL_INT)
		debugctlmsr |= DEBUGCTLMSR_BTINT;

	अगर (!(config & ARCH_PERFMON_EVENTSEL_OS))
		debugctlmsr |= DEBUGCTLMSR_BTS_OFF_OS;

	अगर (!(config & ARCH_PERFMON_EVENTSEL_USR))
		debugctlmsr |= DEBUGCTLMSR_BTS_OFF_USR;

	update_debugctlmsr(debugctlmsr);
पूर्ण

व्योम पूर्णांकel_pmu_disable_bts(व्योम)
अणु
	काष्ठा cpu_hw_events *cpuc = this_cpu_ptr(&cpu_hw_events);
	अचिन्हित दीर्घ debugctlmsr;

	अगर (!cpuc->ds)
		वापस;

	debugctlmsr = get_debugctlmsr();

	debugctlmsr &=
		~(DEBUGCTLMSR_TR | DEBUGCTLMSR_BTS | DEBUGCTLMSR_BTINT |
		  DEBUGCTLMSR_BTS_OFF_OS | DEBUGCTLMSR_BTS_OFF_USR);

	update_debugctlmsr(debugctlmsr);
पूर्ण

पूर्णांक पूर्णांकel_pmu_drain_bts_buffer(व्योम)
अणु
	काष्ठा cpu_hw_events *cpuc = this_cpu_ptr(&cpu_hw_events);
	काष्ठा debug_store *ds = cpuc->ds;
	काष्ठा bts_record अणु
		u64	from;
		u64	to;
		u64	flags;
	पूर्ण;
	काष्ठा perf_event *event = cpuc->events[INTEL_PMC_IDX_FIXED_BTS];
	काष्ठा bts_record *at, *base, *top;
	काष्ठा perf_output_handle handle;
	काष्ठा perf_event_header header;
	काष्ठा perf_sample_data data;
	अचिन्हित दीर्घ skip = 0;
	काष्ठा pt_regs regs;

	अगर (!event)
		वापस 0;

	अगर (!x86_pmu.bts_active)
		वापस 0;

	base = (काष्ठा bts_record *)(अचिन्हित दीर्घ)ds->bts_buffer_base;
	top  = (काष्ठा bts_record *)(अचिन्हित दीर्घ)ds->bts_index;

	अगर (top <= base)
		वापस 0;

	स_रखो(&regs, 0, माप(regs));

	ds->bts_index = ds->bts_buffer_base;

	perf_sample_data_init(&data, 0, event->hw.last_period);

	/*
	 * BTS leaks kernel addresses in branches across the cpl boundary,
	 * such as traps or प्रणाली calls, so unless the user is asking क्रम
	 * kernel tracing (and right now it's not possible), we'd need to
	 * filter them out. But first we need to count how many of those we
	 * have in the current batch. This is an extra O(n) pass, however,
	 * it's much faster than the other one especially considering that
	 * n <= 2560 (BTS_BUFFER_SIZE / BTS_RECORD_SIZE * 15/16; see the
	 * alloc_bts_buffer()).
	 */
	क्रम (at = base; at < top; at++) अणु
		/*
		 * Note that right now *this* BTS code only works अगर
		 * attr::exclude_kernel is set, but let's keep this extra
		 * check here in हाल that changes.
		 */
		अगर (event->attr.exclude_kernel &&
		    (kernel_ip(at->from) || kernel_ip(at->to)))
			skip++;
	पूर्ण

	/*
	 * Prepare a generic sample, i.e. fill in the invariant fields.
	 * We will overग_लिखो the from and to address beक्रमe we output
	 * the sample.
	 */
	rcu_पढ़ो_lock();
	perf_prepare_sample(&header, &data, event, &regs);

	अगर (perf_output_begin(&handle, &data, event,
			      header.size * (top - base - skip)))
		जाओ unlock;

	क्रम (at = base; at < top; at++) अणु
		/* Filter out any records that contain kernel addresses. */
		अगर (event->attr.exclude_kernel &&
		    (kernel_ip(at->from) || kernel_ip(at->to)))
			जारी;

		data.ip		= at->from;
		data.addr	= at->to;

		perf_output_sample(&handle, &header, &data, event);
	पूर्ण

	perf_output_end(&handle);

	/* There's new data available. */
	event->hw.पूर्णांकerrupts++;
	event->pending_समाप्त = POLL_IN;
unlock:
	rcu_पढ़ो_unlock();
	वापस 1;
पूर्ण

अटल अंतरभूत व्योम पूर्णांकel_pmu_drain_pebs_buffer(व्योम)
अणु
	काष्ठा perf_sample_data data;

	x86_pmu.drain_pebs(शून्य, &data);
पूर्ण

/*
 * PEBS
 */
काष्ठा event_स्थिरraपूर्णांक पूर्णांकel_core2_pebs_event_स्थिरraपूर्णांकs[] = अणु
	INTEL_FLAGS_UEVENT_CONSTRAINT(0x00c0, 0x1), /* INST_RETIRED.ANY */
	INTEL_FLAGS_UEVENT_CONSTRAINT(0xfec1, 0x1), /* X87_OPS_RETIRED.ANY */
	INTEL_FLAGS_UEVENT_CONSTRAINT(0x00c5, 0x1), /* BR_INST_RETIRED.MISPRED */
	INTEL_FLAGS_UEVENT_CONSTRAINT(0x1fc7, 0x1), /* SIMD_INST_RETURED.ANY */
	INTEL_FLAGS_EVENT_CONSTRAINT(0xcb, 0x1),    /* MEM_LOAD_RETIRED.* */
	/* INST_RETIRED.ANY_P, inv=1, cmask=16 (cycles:p). */
	INTEL_FLAGS_UEVENT_CONSTRAINT(0x108000c0, 0x01),
	EVENT_CONSTRAINT_END
पूर्ण;

काष्ठा event_स्थिरraपूर्णांक पूर्णांकel_atom_pebs_event_स्थिरraपूर्णांकs[] = अणु
	INTEL_FLAGS_UEVENT_CONSTRAINT(0x00c0, 0x1), /* INST_RETIRED.ANY */
	INTEL_FLAGS_UEVENT_CONSTRAINT(0x00c5, 0x1), /* MISPREDICTED_BRANCH_RETIRED */
	INTEL_FLAGS_EVENT_CONSTRAINT(0xcb, 0x1),    /* MEM_LOAD_RETIRED.* */
	/* INST_RETIRED.ANY_P, inv=1, cmask=16 (cycles:p). */
	INTEL_FLAGS_UEVENT_CONSTRAINT(0x108000c0, 0x01),
	/* Allow all events as PEBS with no flags */
	INTEL_ALL_EVENT_CONSTRAINT(0, 0x1),
	EVENT_CONSTRAINT_END
पूर्ण;

काष्ठा event_स्थिरraपूर्णांक पूर्णांकel_slm_pebs_event_स्थिरraपूर्णांकs[] = अणु
	/* INST_RETIRED.ANY_P, inv=1, cmask=16 (cycles:p). */
	INTEL_FLAGS_UEVENT_CONSTRAINT(0x108000c0, 0x1),
	/* Allow all events as PEBS with no flags */
	INTEL_ALL_EVENT_CONSTRAINT(0, 0x1),
	EVENT_CONSTRAINT_END
पूर्ण;

काष्ठा event_स्थिरraपूर्णांक पूर्णांकel_glm_pebs_event_स्थिरraपूर्णांकs[] = अणु
	/* Allow all events as PEBS with no flags */
	INTEL_ALL_EVENT_CONSTRAINT(0, 0x1),
	EVENT_CONSTRAINT_END
पूर्ण;

काष्ठा event_स्थिरraपूर्णांक पूर्णांकel_grt_pebs_event_स्थिरraपूर्णांकs[] = अणु
	/* Allow all events as PEBS with no flags */
	INTEL_PLD_CONSTRAINT(0x5d0, 0xf),
	INTEL_PSD_CONSTRAINT(0x6d0, 0xf),
	EVENT_CONSTRAINT_END
पूर्ण;

काष्ठा event_स्थिरraपूर्णांक पूर्णांकel_nehalem_pebs_event_स्थिरraपूर्णांकs[] = अणु
	INTEL_PLD_CONSTRAINT(0x100b, 0xf),      /* MEM_INST_RETIRED.* */
	INTEL_FLAGS_EVENT_CONSTRAINT(0x0f, 0xf),    /* MEM_UNCORE_RETIRED.* */
	INTEL_FLAGS_UEVENT_CONSTRAINT(0x010c, 0xf), /* MEM_STORE_RETIRED.DTLB_MISS */
	INTEL_FLAGS_EVENT_CONSTRAINT(0xc0, 0xf),    /* INST_RETIRED.ANY */
	INTEL_EVENT_CONSTRAINT(0xc2, 0xf),    /* UOPS_RETIRED.* */
	INTEL_FLAGS_EVENT_CONSTRAINT(0xc4, 0xf),    /* BR_INST_RETIRED.* */
	INTEL_FLAGS_UEVENT_CONSTRAINT(0x02c5, 0xf), /* BR_MISP_RETIRED.NEAR_CALL */
	INTEL_FLAGS_EVENT_CONSTRAINT(0xc7, 0xf),    /* SSEX_UOPS_RETIRED.* */
	INTEL_FLAGS_UEVENT_CONSTRAINT(0x20c8, 0xf), /* ITLB_MISS_RETIRED */
	INTEL_FLAGS_EVENT_CONSTRAINT(0xcb, 0xf),    /* MEM_LOAD_RETIRED.* */
	INTEL_FLAGS_EVENT_CONSTRAINT(0xf7, 0xf),    /* FP_ASSIST.* */
	/* INST_RETIRED.ANY_P, inv=1, cmask=16 (cycles:p). */
	INTEL_FLAGS_UEVENT_CONSTRAINT(0x108000c0, 0x0f),
	EVENT_CONSTRAINT_END
पूर्ण;

काष्ठा event_स्थिरraपूर्णांक पूर्णांकel_wesपंचांगere_pebs_event_स्थिरraपूर्णांकs[] = अणु
	INTEL_PLD_CONSTRAINT(0x100b, 0xf),      /* MEM_INST_RETIRED.* */
	INTEL_FLAGS_EVENT_CONSTRAINT(0x0f, 0xf),    /* MEM_UNCORE_RETIRED.* */
	INTEL_FLAGS_UEVENT_CONSTRAINT(0x010c, 0xf), /* MEM_STORE_RETIRED.DTLB_MISS */
	INTEL_FLAGS_EVENT_CONSTRAINT(0xc0, 0xf),    /* INSTR_RETIRED.* */
	INTEL_EVENT_CONSTRAINT(0xc2, 0xf),    /* UOPS_RETIRED.* */
	INTEL_FLAGS_EVENT_CONSTRAINT(0xc4, 0xf),    /* BR_INST_RETIRED.* */
	INTEL_FLAGS_EVENT_CONSTRAINT(0xc5, 0xf),    /* BR_MISP_RETIRED.* */
	INTEL_FLAGS_EVENT_CONSTRAINT(0xc7, 0xf),    /* SSEX_UOPS_RETIRED.* */
	INTEL_FLAGS_UEVENT_CONSTRAINT(0x20c8, 0xf), /* ITLB_MISS_RETIRED */
	INTEL_FLAGS_EVENT_CONSTRAINT(0xcb, 0xf),    /* MEM_LOAD_RETIRED.* */
	INTEL_FLAGS_EVENT_CONSTRAINT(0xf7, 0xf),    /* FP_ASSIST.* */
	/* INST_RETIRED.ANY_P, inv=1, cmask=16 (cycles:p). */
	INTEL_FLAGS_UEVENT_CONSTRAINT(0x108000c0, 0x0f),
	EVENT_CONSTRAINT_END
पूर्ण;

काष्ठा event_स्थिरraपूर्णांक पूर्णांकel_snb_pebs_event_स्थिरraपूर्णांकs[] = अणु
	INTEL_FLAGS_UEVENT_CONSTRAINT(0x01c0, 0x2), /* INST_RETIRED.PRECDIST */
	INTEL_PLD_CONSTRAINT(0x01cd, 0x8),    /* MEM_TRANS_RETIRED.LAT_ABOVE_THR */
	INTEL_PST_CONSTRAINT(0x02cd, 0x8),    /* MEM_TRANS_RETIRED.PRECISE_STORES */
	/* UOPS_RETIRED.ALL, inv=1, cmask=16 (cycles:p). */
	INTEL_FLAGS_UEVENT_CONSTRAINT(0x108001c2, 0xf),
        INTEL_EXCLEVT_CONSTRAINT(0xd0, 0xf),    /* MEM_UOP_RETIRED.* */
        INTEL_EXCLEVT_CONSTRAINT(0xd1, 0xf),    /* MEM_LOAD_UOPS_RETIRED.* */
        INTEL_EXCLEVT_CONSTRAINT(0xd2, 0xf),    /* MEM_LOAD_UOPS_LLC_HIT_RETIRED.* */
        INTEL_EXCLEVT_CONSTRAINT(0xd3, 0xf),    /* MEM_LOAD_UOPS_LLC_MISS_RETIRED.* */
	/* Allow all events as PEBS with no flags */
	INTEL_ALL_EVENT_CONSTRAINT(0, 0xf),
	EVENT_CONSTRAINT_END
पूर्ण;

काष्ठा event_स्थिरraपूर्णांक पूर्णांकel_ivb_pebs_event_स्थिरraपूर्णांकs[] = अणु
        INTEL_FLAGS_UEVENT_CONSTRAINT(0x01c0, 0x2), /* INST_RETIRED.PRECDIST */
        INTEL_PLD_CONSTRAINT(0x01cd, 0x8),    /* MEM_TRANS_RETIRED.LAT_ABOVE_THR */
	INTEL_PST_CONSTRAINT(0x02cd, 0x8),    /* MEM_TRANS_RETIRED.PRECISE_STORES */
	/* UOPS_RETIRED.ALL, inv=1, cmask=16 (cycles:p). */
	INTEL_FLAGS_UEVENT_CONSTRAINT(0x108001c2, 0xf),
	/* INST_RETIRED.PREC_DIST, inv=1, cmask=16 (cycles:ppp). */
	INTEL_FLAGS_UEVENT_CONSTRAINT(0x108001c0, 0x2),
	INTEL_EXCLEVT_CONSTRAINT(0xd0, 0xf),    /* MEM_UOP_RETIRED.* */
	INTEL_EXCLEVT_CONSTRAINT(0xd1, 0xf),    /* MEM_LOAD_UOPS_RETIRED.* */
	INTEL_EXCLEVT_CONSTRAINT(0xd2, 0xf),    /* MEM_LOAD_UOPS_LLC_HIT_RETIRED.* */
	INTEL_EXCLEVT_CONSTRAINT(0xd3, 0xf),    /* MEM_LOAD_UOPS_LLC_MISS_RETIRED.* */
	/* Allow all events as PEBS with no flags */
	INTEL_ALL_EVENT_CONSTRAINT(0, 0xf),
        EVENT_CONSTRAINT_END
पूर्ण;

काष्ठा event_स्थिरraपूर्णांक पूर्णांकel_hsw_pebs_event_स्थिरraपूर्णांकs[] = अणु
	INTEL_FLAGS_UEVENT_CONSTRAINT(0x01c0, 0x2), /* INST_RETIRED.PRECDIST */
	INTEL_PLD_CONSTRAINT(0x01cd, 0xf),    /* MEM_TRANS_RETIRED.* */
	/* UOPS_RETIRED.ALL, inv=1, cmask=16 (cycles:p). */
	INTEL_FLAGS_UEVENT_CONSTRAINT(0x108001c2, 0xf),
	/* INST_RETIRED.PREC_DIST, inv=1, cmask=16 (cycles:ppp). */
	INTEL_FLAGS_UEVENT_CONSTRAINT(0x108001c0, 0x2),
	INTEL_FLAGS_UEVENT_CONSTRAINT_DATALA_NA(0x01c2, 0xf), /* UOPS_RETIRED.ALL */
	INTEL_FLAGS_UEVENT_CONSTRAINT_DATALA_XLD(0x11d0, 0xf), /* MEM_UOPS_RETIRED.STLB_MISS_LOADS */
	INTEL_FLAGS_UEVENT_CONSTRAINT_DATALA_XLD(0x21d0, 0xf), /* MEM_UOPS_RETIRED.LOCK_LOADS */
	INTEL_FLAGS_UEVENT_CONSTRAINT_DATALA_XLD(0x41d0, 0xf), /* MEM_UOPS_RETIRED.SPLIT_LOADS */
	INTEL_FLAGS_UEVENT_CONSTRAINT_DATALA_XLD(0x81d0, 0xf), /* MEM_UOPS_RETIRED.ALL_LOADS */
	INTEL_FLAGS_UEVENT_CONSTRAINT_DATALA_XST(0x12d0, 0xf), /* MEM_UOPS_RETIRED.STLB_MISS_STORES */
	INTEL_FLAGS_UEVENT_CONSTRAINT_DATALA_XST(0x42d0, 0xf), /* MEM_UOPS_RETIRED.SPLIT_STORES */
	INTEL_FLAGS_UEVENT_CONSTRAINT_DATALA_XST(0x82d0, 0xf), /* MEM_UOPS_RETIRED.ALL_STORES */
	INTEL_FLAGS_EVENT_CONSTRAINT_DATALA_XLD(0xd1, 0xf),    /* MEM_LOAD_UOPS_RETIRED.* */
	INTEL_FLAGS_EVENT_CONSTRAINT_DATALA_XLD(0xd2, 0xf),    /* MEM_LOAD_UOPS_L3_HIT_RETIRED.* */
	INTEL_FLAGS_EVENT_CONSTRAINT_DATALA_XLD(0xd3, 0xf),    /* MEM_LOAD_UOPS_L3_MISS_RETIRED.* */
	/* Allow all events as PEBS with no flags */
	INTEL_ALL_EVENT_CONSTRAINT(0, 0xf),
	EVENT_CONSTRAINT_END
पूर्ण;

काष्ठा event_स्थिरraपूर्णांक पूर्णांकel_bdw_pebs_event_स्थिरraपूर्णांकs[] = अणु
	INTEL_FLAGS_UEVENT_CONSTRAINT(0x01c0, 0x2), /* INST_RETIRED.PRECDIST */
	INTEL_PLD_CONSTRAINT(0x01cd, 0xf),    /* MEM_TRANS_RETIRED.* */
	/* UOPS_RETIRED.ALL, inv=1, cmask=16 (cycles:p). */
	INTEL_FLAGS_UEVENT_CONSTRAINT(0x108001c2, 0xf),
	/* INST_RETIRED.PREC_DIST, inv=1, cmask=16 (cycles:ppp). */
	INTEL_FLAGS_UEVENT_CONSTRAINT(0x108001c0, 0x2),
	INTEL_FLAGS_UEVENT_CONSTRAINT_DATALA_NA(0x01c2, 0xf), /* UOPS_RETIRED.ALL */
	INTEL_FLAGS_UEVENT_CONSTRAINT_DATALA_LD(0x11d0, 0xf), /* MEM_UOPS_RETIRED.STLB_MISS_LOADS */
	INTEL_FLAGS_UEVENT_CONSTRAINT_DATALA_LD(0x21d0, 0xf), /* MEM_UOPS_RETIRED.LOCK_LOADS */
	INTEL_FLAGS_UEVENT_CONSTRAINT_DATALA_LD(0x41d0, 0xf), /* MEM_UOPS_RETIRED.SPLIT_LOADS */
	INTEL_FLAGS_UEVENT_CONSTRAINT_DATALA_LD(0x81d0, 0xf), /* MEM_UOPS_RETIRED.ALL_LOADS */
	INTEL_FLAGS_UEVENT_CONSTRAINT_DATALA_ST(0x12d0, 0xf), /* MEM_UOPS_RETIRED.STLB_MISS_STORES */
	INTEL_FLAGS_UEVENT_CONSTRAINT_DATALA_ST(0x42d0, 0xf), /* MEM_UOPS_RETIRED.SPLIT_STORES */
	INTEL_FLAGS_UEVENT_CONSTRAINT_DATALA_ST(0x82d0, 0xf), /* MEM_UOPS_RETIRED.ALL_STORES */
	INTEL_FLAGS_EVENT_CONSTRAINT_DATALA_LD(0xd1, 0xf),    /* MEM_LOAD_UOPS_RETIRED.* */
	INTEL_FLAGS_EVENT_CONSTRAINT_DATALA_LD(0xd2, 0xf),    /* MEM_LOAD_UOPS_L3_HIT_RETIRED.* */
	INTEL_FLAGS_EVENT_CONSTRAINT_DATALA_LD(0xd3, 0xf),    /* MEM_LOAD_UOPS_L3_MISS_RETIRED.* */
	/* Allow all events as PEBS with no flags */
	INTEL_ALL_EVENT_CONSTRAINT(0, 0xf),
	EVENT_CONSTRAINT_END
पूर्ण;


काष्ठा event_स्थिरraपूर्णांक पूर्णांकel_skl_pebs_event_स्थिरraपूर्णांकs[] = अणु
	INTEL_FLAGS_UEVENT_CONSTRAINT(0x1c0, 0x2),	/* INST_RETIRED.PREC_DIST */
	/* INST_RETIRED.PREC_DIST, inv=1, cmask=16 (cycles:ppp). */
	INTEL_FLAGS_UEVENT_CONSTRAINT(0x108001c0, 0x2),
	/* INST_RETIRED.TOTAL_CYCLES_PS (inv=1, cmask=16) (cycles:p). */
	INTEL_FLAGS_UEVENT_CONSTRAINT(0x108000c0, 0x0f),
	INTEL_PLD_CONSTRAINT(0x1cd, 0xf),		      /* MEM_TRANS_RETIRED.* */
	INTEL_FLAGS_UEVENT_CONSTRAINT_DATALA_LD(0x11d0, 0xf), /* MEM_INST_RETIRED.STLB_MISS_LOADS */
	INTEL_FLAGS_UEVENT_CONSTRAINT_DATALA_ST(0x12d0, 0xf), /* MEM_INST_RETIRED.STLB_MISS_STORES */
	INTEL_FLAGS_UEVENT_CONSTRAINT_DATALA_LD(0x21d0, 0xf), /* MEM_INST_RETIRED.LOCK_LOADS */
	INTEL_FLAGS_UEVENT_CONSTRAINT_DATALA_ST(0x22d0, 0xf), /* MEM_INST_RETIRED.LOCK_STORES */
	INTEL_FLAGS_UEVENT_CONSTRAINT_DATALA_LD(0x41d0, 0xf), /* MEM_INST_RETIRED.SPLIT_LOADS */
	INTEL_FLAGS_UEVENT_CONSTRAINT_DATALA_ST(0x42d0, 0xf), /* MEM_INST_RETIRED.SPLIT_STORES */
	INTEL_FLAGS_UEVENT_CONSTRAINT_DATALA_LD(0x81d0, 0xf), /* MEM_INST_RETIRED.ALL_LOADS */
	INTEL_FLAGS_UEVENT_CONSTRAINT_DATALA_ST(0x82d0, 0xf), /* MEM_INST_RETIRED.ALL_STORES */
	INTEL_FLAGS_EVENT_CONSTRAINT_DATALA_LD(0xd1, 0xf),    /* MEM_LOAD_RETIRED.* */
	INTEL_FLAGS_EVENT_CONSTRAINT_DATALA_LD(0xd2, 0xf),    /* MEM_LOAD_L3_HIT_RETIRED.* */
	INTEL_FLAGS_EVENT_CONSTRAINT_DATALA_LD(0xd3, 0xf),    /* MEM_LOAD_L3_MISS_RETIRED.* */
	/* Allow all events as PEBS with no flags */
	INTEL_ALL_EVENT_CONSTRAINT(0, 0xf),
	EVENT_CONSTRAINT_END
पूर्ण;

काष्ठा event_स्थिरraपूर्णांक पूर्णांकel_icl_pebs_event_स्थिरraपूर्णांकs[] = अणु
	INTEL_FLAGS_UEVENT_CONSTRAINT(0x1c0, 0x100000000ULL),	/* INST_RETIRED.PREC_DIST */
	INTEL_FLAGS_UEVENT_CONSTRAINT(0x0400, 0x800000000ULL),	/* SLOTS */

	INTEL_PLD_CONSTRAINT(0x1cd, 0xff),			/* MEM_TRANS_RETIRED.LOAD_LATENCY */
	INTEL_FLAGS_UEVENT_CONSTRAINT_DATALA_LD(0x1d0, 0xf),	/* MEM_INST_RETIRED.LOAD */
	INTEL_FLAGS_UEVENT_CONSTRAINT_DATALA_ST(0x2d0, 0xf),	/* MEM_INST_RETIRED.STORE */

	INTEL_FLAGS_EVENT_CONSTRAINT_DATALA_LD_RANGE(0xd1, 0xd4, 0xf), /* MEM_LOAD_*_RETIRED.* */

	INTEL_FLAGS_EVENT_CONSTRAINT(0xd0, 0xf),		/* MEM_INST_RETIRED.* */

	/*
	 * Everything अन्यथा is handled by PMU_FL_PEBS_ALL, because we
	 * need the full स्थिरraपूर्णांकs from the मुख्य table.
	 */

	EVENT_CONSTRAINT_END
पूर्ण;

काष्ठा event_स्थिरraपूर्णांक पूर्णांकel_spr_pebs_event_स्थिरraपूर्णांकs[] = अणु
	INTEL_FLAGS_UEVENT_CONSTRAINT(0x1c0, 0x100000000ULL),
	INTEL_FLAGS_UEVENT_CONSTRAINT(0x0400, 0x800000000ULL),

	INTEL_FLAGS_EVENT_CONSTRAINT(0xc0, 0xfe),
	INTEL_PLD_CONSTRAINT(0x1cd, 0xfe),
	INTEL_PSD_CONSTRAINT(0x2cd, 0x1),
	INTEL_FLAGS_UEVENT_CONSTRAINT_DATALA_LD(0x1d0, 0xf),
	INTEL_FLAGS_UEVENT_CONSTRAINT_DATALA_ST(0x2d0, 0xf),

	INTEL_FLAGS_EVENT_CONSTRAINT_DATALA_LD_RANGE(0xd1, 0xd4, 0xf),

	INTEL_FLAGS_EVENT_CONSTRAINT(0xd0, 0xf),

	/*
	 * Everything अन्यथा is handled by PMU_FL_PEBS_ALL, because we
	 * need the full स्थिरraपूर्णांकs from the मुख्य table.
	 */

	EVENT_CONSTRAINT_END
पूर्ण;

काष्ठा event_स्थिरraपूर्णांक *पूर्णांकel_pebs_स्थिरraपूर्णांकs(काष्ठा perf_event *event)
अणु
	काष्ठा event_स्थिरraपूर्णांक *pebs_स्थिरraपूर्णांकs = hybrid(event->pmu, pebs_स्थिरraपूर्णांकs);
	काष्ठा event_स्थिरraपूर्णांक *c;

	अगर (!event->attr.precise_ip)
		वापस शून्य;

	अगर (pebs_स्थिरraपूर्णांकs) अणु
		क्रम_each_event_स्थिरraपूर्णांक(c, pebs_स्थिरraपूर्णांकs) अणु
			अगर (स्थिरraपूर्णांक_match(c, event->hw.config)) अणु
				event->hw.flags |= c->flags;
				वापस c;
			पूर्ण
		पूर्ण
	पूर्ण

	/*
	 * Extended PEBS support
	 * Makes the PEBS code search the normal स्थिरraपूर्णांकs.
	 */
	अगर (x86_pmu.flags & PMU_FL_PEBS_ALL)
		वापस शून्य;

	वापस &emptyस्थिरraपूर्णांक;
पूर्ण

/*
 * We need the sched_task callback even क्रम per-cpu events when we use
 * the large पूर्णांकerrupt threshold, such that we can provide PID and TID
 * to PEBS samples.
 */
अटल अंतरभूत bool pebs_needs_sched_cb(काष्ठा cpu_hw_events *cpuc)
अणु
	अगर (cpuc->n_pebs == cpuc->n_pebs_via_pt)
		वापस false;

	वापस cpuc->n_pebs && (cpuc->n_pebs == cpuc->n_large_pebs);
पूर्ण

व्योम पूर्णांकel_pmu_pebs_sched_task(काष्ठा perf_event_context *ctx, bool sched_in)
अणु
	काष्ठा cpu_hw_events *cpuc = this_cpu_ptr(&cpu_hw_events);

	अगर (!sched_in && pebs_needs_sched_cb(cpuc))
		पूर्णांकel_pmu_drain_pebs_buffer();
पूर्ण

अटल अंतरभूत व्योम pebs_update_threshold(काष्ठा cpu_hw_events *cpuc)
अणु
	काष्ठा debug_store *ds = cpuc->ds;
	पूर्णांक max_pebs_events = hybrid(cpuc->pmu, max_pebs_events);
	पूर्णांक num_counters_fixed = hybrid(cpuc->pmu, num_counters_fixed);
	u64 threshold;
	पूर्णांक reserved;

	अगर (cpuc->n_pebs_via_pt)
		वापस;

	अगर (x86_pmu.flags & PMU_FL_PEBS_ALL)
		reserved = max_pebs_events + num_counters_fixed;
	अन्यथा
		reserved = max_pebs_events;

	अगर (cpuc->n_pebs == cpuc->n_large_pebs) अणु
		threshold = ds->pebs_असलolute_maximum -
			reserved * cpuc->pebs_record_size;
	पूर्ण अन्यथा अणु
		threshold = ds->pebs_buffer_base + cpuc->pebs_record_size;
	पूर्ण

	ds->pebs_पूर्णांकerrupt_threshold = threshold;
पूर्ण

अटल व्योम adaptive_pebs_record_size_update(व्योम)
अणु
	काष्ठा cpu_hw_events *cpuc = this_cpu_ptr(&cpu_hw_events);
	u64 pebs_data_cfg = cpuc->pebs_data_cfg;
	पूर्णांक sz = माप(काष्ठा pebs_basic);

	अगर (pebs_data_cfg & PEBS_DATACFG_MEMINFO)
		sz += माप(काष्ठा pebs_meminfo);
	अगर (pebs_data_cfg & PEBS_DATACFG_GP)
		sz += माप(काष्ठा pebs_gprs);
	अगर (pebs_data_cfg & PEBS_DATACFG_XMMS)
		sz += माप(काष्ठा pebs_xmm);
	अगर (pebs_data_cfg & PEBS_DATACFG_LBRS)
		sz += x86_pmu.lbr_nr * माप(काष्ठा lbr_entry);

	cpuc->pebs_record_size = sz;
पूर्ण

#घोषणा PERF_PEBS_MEMINFO_TYPE	(PERF_SAMPLE_ADDR | PERF_SAMPLE_DATA_SRC |   \
				PERF_SAMPLE_PHYS_ADDR |			     \
				PERF_SAMPLE_WEIGHT_TYPE |		     \
				PERF_SAMPLE_TRANSACTION |		     \
				PERF_SAMPLE_DATA_PAGE_SIZE)

अटल u64 pebs_update_adaptive_cfg(काष्ठा perf_event *event)
अणु
	काष्ठा perf_event_attr *attr = &event->attr;
	u64 sample_type = attr->sample_type;
	u64 pebs_data_cfg = 0;
	bool gprs, tsx_weight;

	अगर (!(sample_type & ~(PERF_SAMPLE_IP|PERF_SAMPLE_TIME)) &&
	    attr->precise_ip > 1)
		वापस pebs_data_cfg;

	अगर (sample_type & PERF_PEBS_MEMINFO_TYPE)
		pebs_data_cfg |= PEBS_DATACFG_MEMINFO;

	/*
	 * We need GPRs when:
	 * + user requested them
	 * + precise_ip < 2 क्रम the non event IP
	 * + For RTM TSX weight we need GPRs क्रम the पात code.
	 */
	gprs = (sample_type & PERF_SAMPLE_REGS_INTR) &&
	       (attr->sample_regs_पूर्णांकr & PEBS_GP_REGS);

	tsx_weight = (sample_type & PERF_SAMPLE_WEIGHT_TYPE) &&
		     ((attr->config & INTEL_ARCH_EVENT_MASK) ==
		      x86_pmu.rपंचांग_पात_event);

	अगर (gprs || (attr->precise_ip < 2) || tsx_weight)
		pebs_data_cfg |= PEBS_DATACFG_GP;

	अगर ((sample_type & PERF_SAMPLE_REGS_INTR) &&
	    (attr->sample_regs_पूर्णांकr & PERF_REG_EXTENDED_MASK))
		pebs_data_cfg |= PEBS_DATACFG_XMMS;

	अगर (sample_type & PERF_SAMPLE_BRANCH_STACK) अणु
		/*
		 * For now always log all LBRs. Could configure this
		 * later.
		 */
		pebs_data_cfg |= PEBS_DATACFG_LBRS |
			((x86_pmu.lbr_nr-1) << PEBS_DATACFG_LBR_SHIFT);
	पूर्ण

	वापस pebs_data_cfg;
पूर्ण

अटल व्योम
pebs_update_state(bool needed_cb, काष्ठा cpu_hw_events *cpuc,
		  काष्ठा perf_event *event, bool add)
अणु
	काष्ठा pmu *pmu = event->ctx->pmu;
	/*
	 * Make sure we get updated with the first PEBS
	 * event. It will trigger also during removal, but
	 * that करोes not hurt:
	 */
	bool update = cpuc->n_pebs == 1;

	अगर (needed_cb != pebs_needs_sched_cb(cpuc)) अणु
		अगर (!needed_cb)
			perf_sched_cb_inc(pmu);
		अन्यथा
			perf_sched_cb_dec(pmu);

		update = true;
	पूर्ण

	/*
	 * The PEBS record करोesn't shrink on pmu::del(). Doing so would require
	 * iterating all reमुख्यing PEBS events to reस्थिरruct the config.
	 */
	अगर (x86_pmu.पूर्णांकel_cap.pebs_baseline && add) अणु
		u64 pebs_data_cfg;

		/* Clear pebs_data_cfg and pebs_record_size क्रम first PEBS. */
		अगर (cpuc->n_pebs == 1) अणु
			cpuc->pebs_data_cfg = 0;
			cpuc->pebs_record_size = माप(काष्ठा pebs_basic);
		पूर्ण

		pebs_data_cfg = pebs_update_adaptive_cfg(event);

		/* Update pebs_record_size अगर new event requires more data. */
		अगर (pebs_data_cfg & ~cpuc->pebs_data_cfg) अणु
			cpuc->pebs_data_cfg |= pebs_data_cfg;
			adaptive_pebs_record_size_update();
			update = true;
		पूर्ण
	पूर्ण

	अगर (update)
		pebs_update_threshold(cpuc);
पूर्ण

व्योम पूर्णांकel_pmu_pebs_add(काष्ठा perf_event *event)
अणु
	काष्ठा cpu_hw_events *cpuc = this_cpu_ptr(&cpu_hw_events);
	काष्ठा hw_perf_event *hwc = &event->hw;
	bool needed_cb = pebs_needs_sched_cb(cpuc);

	cpuc->n_pebs++;
	अगर (hwc->flags & PERF_X86_EVENT_LARGE_PEBS)
		cpuc->n_large_pebs++;
	अगर (hwc->flags & PERF_X86_EVENT_PEBS_VIA_PT)
		cpuc->n_pebs_via_pt++;

	pebs_update_state(needed_cb, cpuc, event, true);
पूर्ण

अटल व्योम पूर्णांकel_pmu_pebs_via_pt_disable(काष्ठा perf_event *event)
अणु
	काष्ठा cpu_hw_events *cpuc = this_cpu_ptr(&cpu_hw_events);

	अगर (!is_pebs_pt(event))
		वापस;

	अगर (!(cpuc->pebs_enabled & ~PEBS_VIA_PT_MASK))
		cpuc->pebs_enabled &= ~PEBS_VIA_PT_MASK;
पूर्ण

अटल व्योम पूर्णांकel_pmu_pebs_via_pt_enable(काष्ठा perf_event *event)
अणु
	काष्ठा cpu_hw_events *cpuc = this_cpu_ptr(&cpu_hw_events);
	काष्ठा hw_perf_event *hwc = &event->hw;
	काष्ठा debug_store *ds = cpuc->ds;

	अगर (!is_pebs_pt(event))
		वापस;

	अगर (!(event->hw.flags & PERF_X86_EVENT_LARGE_PEBS))
		cpuc->pebs_enabled |= PEBS_PMI_AFTER_EACH_RECORD;

	cpuc->pebs_enabled |= PEBS_OUTPUT_PT;

	wrmsrl(MSR_RELOAD_PMC0 + hwc->idx, ds->pebs_event_reset[hwc->idx]);
पूर्ण

व्योम पूर्णांकel_pmu_pebs_enable(काष्ठा perf_event *event)
अणु
	काष्ठा cpu_hw_events *cpuc = this_cpu_ptr(&cpu_hw_events);
	काष्ठा hw_perf_event *hwc = &event->hw;
	काष्ठा debug_store *ds = cpuc->ds;

	hwc->config &= ~ARCH_PERFMON_EVENTSEL_INT;

	cpuc->pebs_enabled |= 1ULL << hwc->idx;

	अगर ((event->hw.flags & PERF_X86_EVENT_PEBS_LDLAT) && (x86_pmu.version < 5))
		cpuc->pebs_enabled |= 1ULL << (hwc->idx + 32);
	अन्यथा अगर (event->hw.flags & PERF_X86_EVENT_PEBS_ST)
		cpuc->pebs_enabled |= 1ULL << 63;

	अगर (x86_pmu.पूर्णांकel_cap.pebs_baseline) अणु
		hwc->config |= ICL_EVENTSEL_ADAPTIVE;
		अगर (cpuc->pebs_data_cfg != cpuc->active_pebs_data_cfg) अणु
			wrmsrl(MSR_PEBS_DATA_CFG, cpuc->pebs_data_cfg);
			cpuc->active_pebs_data_cfg = cpuc->pebs_data_cfg;
		पूर्ण
	पूर्ण

	/*
	 * Use स्वतः-reload अगर possible to save a MSR ग_लिखो in the PMI.
	 * This must be करोne in pmu::start(), because PERF_EVENT_IOC_PERIOD.
	 */
	अगर (hwc->flags & PERF_X86_EVENT_AUTO_RELOAD) अणु
		अचिन्हित पूर्णांक idx = hwc->idx;

		अगर (idx >= INTEL_PMC_IDX_FIXED)
			idx = MAX_PEBS_EVENTS + (idx - INTEL_PMC_IDX_FIXED);
		ds->pebs_event_reset[idx] =
			(u64)(-hwc->sample_period) & x86_pmu.cntval_mask;
	पूर्ण अन्यथा अणु
		ds->pebs_event_reset[hwc->idx] = 0;
	पूर्ण

	पूर्णांकel_pmu_pebs_via_pt_enable(event);
पूर्ण

व्योम पूर्णांकel_pmu_pebs_del(काष्ठा perf_event *event)
अणु
	काष्ठा cpu_hw_events *cpuc = this_cpu_ptr(&cpu_hw_events);
	काष्ठा hw_perf_event *hwc = &event->hw;
	bool needed_cb = pebs_needs_sched_cb(cpuc);

	cpuc->n_pebs--;
	अगर (hwc->flags & PERF_X86_EVENT_LARGE_PEBS)
		cpuc->n_large_pebs--;
	अगर (hwc->flags & PERF_X86_EVENT_PEBS_VIA_PT)
		cpuc->n_pebs_via_pt--;

	pebs_update_state(needed_cb, cpuc, event, false);
पूर्ण

व्योम पूर्णांकel_pmu_pebs_disable(काष्ठा perf_event *event)
अणु
	काष्ठा cpu_hw_events *cpuc = this_cpu_ptr(&cpu_hw_events);
	काष्ठा hw_perf_event *hwc = &event->hw;

	अगर (cpuc->n_pebs == cpuc->n_large_pebs &&
	    cpuc->n_pebs != cpuc->n_pebs_via_pt)
		पूर्णांकel_pmu_drain_pebs_buffer();

	cpuc->pebs_enabled &= ~(1ULL << hwc->idx);

	अगर ((event->hw.flags & PERF_X86_EVENT_PEBS_LDLAT) &&
	    (x86_pmu.version < 5))
		cpuc->pebs_enabled &= ~(1ULL << (hwc->idx + 32));
	अन्यथा अगर (event->hw.flags & PERF_X86_EVENT_PEBS_ST)
		cpuc->pebs_enabled &= ~(1ULL << 63);

	पूर्णांकel_pmu_pebs_via_pt_disable(event);

	अगर (cpuc->enabled)
		wrmsrl(MSR_IA32_PEBS_ENABLE, cpuc->pebs_enabled);

	hwc->config |= ARCH_PERFMON_EVENTSEL_INT;
पूर्ण

व्योम पूर्णांकel_pmu_pebs_enable_all(व्योम)
अणु
	काष्ठा cpu_hw_events *cpuc = this_cpu_ptr(&cpu_hw_events);

	अगर (cpuc->pebs_enabled)
		wrmsrl(MSR_IA32_PEBS_ENABLE, cpuc->pebs_enabled);
पूर्ण

व्योम पूर्णांकel_pmu_pebs_disable_all(व्योम)
अणु
	काष्ठा cpu_hw_events *cpuc = this_cpu_ptr(&cpu_hw_events);

	अगर (cpuc->pebs_enabled)
		wrmsrl(MSR_IA32_PEBS_ENABLE, 0);
पूर्ण

अटल पूर्णांक पूर्णांकel_pmu_pebs_fixup_ip(काष्ठा pt_regs *regs)
अणु
	काष्ठा cpu_hw_events *cpuc = this_cpu_ptr(&cpu_hw_events);
	अचिन्हित दीर्घ from = cpuc->lbr_entries[0].from;
	अचिन्हित दीर्घ old_to, to = cpuc->lbr_entries[0].to;
	अचिन्हित दीर्घ ip = regs->ip;
	पूर्णांक is_64bit = 0;
	व्योम *kaddr;
	पूर्णांक size;

	/*
	 * We करोn't need to fixup अगर the PEBS assist is fault like
	 */
	अगर (!x86_pmu.पूर्णांकel_cap.pebs_trap)
		वापस 1;

	/*
	 * No LBR entry, no basic block, no शुरुआतing
	 */
	अगर (!cpuc->lbr_stack.nr || !from || !to)
		वापस 0;

	/*
	 * Basic blocks should never cross user/kernel boundaries
	 */
	अगर (kernel_ip(ip) != kernel_ip(to))
		वापस 0;

	/*
	 * अचिन्हित math, either ip is beक्रमe the start (impossible) or
	 * the basic block is larger than 1 page (sanity)
	 */
	अगर ((ip - to) > PEBS_FIXUP_SIZE)
		वापस 0;

	/*
	 * We sampled a branch insn, शुरुआत using the LBR stack
	 */
	अगर (ip == to) अणु
		set_linear_ip(regs, from);
		वापस 1;
	पूर्ण

	size = ip - to;
	अगर (!kernel_ip(ip)) अणु
		पूर्णांक bytes;
		u8 *buf = this_cpu_पढ़ो(insn_buffer);

		/* 'size' must fit our buffer, see above */
		bytes = copy_from_user_nmi(buf, (व्योम __user *)to, size);
		अगर (bytes != 0)
			वापस 0;

		kaddr = buf;
	पूर्ण अन्यथा अणु
		kaddr = (व्योम *)to;
	पूर्ण

	करो अणु
		काष्ठा insn insn;

		old_to = to;

#अगर_घोषित CONFIG_X86_64
		is_64bit = kernel_ip(to) || any_64bit_mode(regs);
#पूर्ण_अगर
		insn_init(&insn, kaddr, size, is_64bit);

		/*
		 * Make sure there was not a problem decoding the inकाष्ठाion.
		 * This is करोubly important because we have an infinite loop अगर
		 * insn.length=0.
		 */
		अगर (insn_get_length(&insn))
			अवरोध;

		to += insn.length;
		kaddr += insn.length;
		size -= insn.length;
	पूर्ण जबतक (to < ip);

	अगर (to == ip) अणु
		set_linear_ip(regs, old_to);
		वापस 1;
	पूर्ण

	/*
	 * Even though we decoded the basic block, the inकाष्ठाion stream
	 * never matched the given IP, either the TO or the IP got corrupted.
	 */
	वापस 0;
पूर्ण

अटल अंतरभूत u64 पूर्णांकel_get_tsx_weight(u64 tsx_tuning)
अणु
	अगर (tsx_tuning) अणु
		जोड़ hsw_tsx_tuning tsx = अणु .value = tsx_tuning पूर्ण;
		वापस tsx.cycles_last_block;
	पूर्ण
	वापस 0;
पूर्ण

अटल अंतरभूत u64 पूर्णांकel_get_tsx_transaction(u64 tsx_tuning, u64 ax)
अणु
	u64 txn = (tsx_tuning & PEBS_HSW_TSX_FLAGS) >> 32;

	/* For RTM XABORTs also log the पात code from AX */
	अगर ((txn & PERF_TXN_TRANSACTION) && (ax & 1))
		txn |= ((ax >> 24) & 0xff) << PERF_TXN_ABORT_SHIFT;
	वापस txn;
पूर्ण

अटल अंतरभूत u64 get_pebs_status(व्योम *n)
अणु
	अगर (x86_pmu.पूर्णांकel_cap.pebs_क्रमmat < 4)
		वापस ((काष्ठा pebs_record_nhm *)n)->status;
	वापस ((काष्ठा pebs_basic *)n)->applicable_counters;
पूर्ण

#घोषणा PERF_X86_EVENT_PEBS_HSW_PREC \
		(PERF_X86_EVENT_PEBS_ST_HSW | \
		 PERF_X86_EVENT_PEBS_LD_HSW | \
		 PERF_X86_EVENT_PEBS_NA_HSW)

अटल u64 get_data_src(काष्ठा perf_event *event, u64 aux)
अणु
	u64 val = PERF_MEM_NA;
	पूर्णांक fl = event->hw.flags;
	bool fst = fl & (PERF_X86_EVENT_PEBS_ST | PERF_X86_EVENT_PEBS_HSW_PREC);

	अगर (fl & PERF_X86_EVENT_PEBS_LDLAT)
		val = load_latency_data(aux);
	अन्यथा अगर (fl & PERF_X86_EVENT_PEBS_STLAT)
		val = store_latency_data(aux);
	अन्यथा अगर (fst && (fl & PERF_X86_EVENT_PEBS_HSW_PREC))
		val = precise_datala_hsw(event, aux);
	अन्यथा अगर (fst)
		val = precise_store_data(aux);
	वापस val;
पूर्ण

#घोषणा PERF_SAMPLE_ADDR_TYPE	(PERF_SAMPLE_ADDR |		\
				 PERF_SAMPLE_PHYS_ADDR |	\
				 PERF_SAMPLE_DATA_PAGE_SIZE)

अटल व्योम setup_pebs_fixed_sample_data(काष्ठा perf_event *event,
				   काष्ठा pt_regs *iregs, व्योम *__pebs,
				   काष्ठा perf_sample_data *data,
				   काष्ठा pt_regs *regs)
अणु
	/*
	 * We cast to the biggest pebs_record but are careful not to
	 * unconditionally access the 'extra' entries.
	 */
	काष्ठा cpu_hw_events *cpuc = this_cpu_ptr(&cpu_hw_events);
	काष्ठा pebs_record_skl *pebs = __pebs;
	u64 sample_type;
	पूर्णांक fll;

	अगर (pebs == शून्य)
		वापस;

	sample_type = event->attr.sample_type;
	fll = event->hw.flags & PERF_X86_EVENT_PEBS_LDLAT;

	perf_sample_data_init(data, 0, event->hw.last_period);

	data->period = event->hw.last_period;

	/*
	 * Use latency क्रम weight (only avail with PEBS-LL)
	 */
	अगर (fll && (sample_type & PERF_SAMPLE_WEIGHT_TYPE))
		data->weight.full = pebs->lat;

	/*
	 * data.data_src encodes the data source
	 */
	अगर (sample_type & PERF_SAMPLE_DATA_SRC)
		data->data_src.val = get_data_src(event, pebs->dse);

	/*
	 * We must however always use iregs क्रम the unwinder to stay sane; the
	 * record BP,SP,IP can poपूर्णांक पूर्णांकo thin air when the record is from a
	 * previous PMI context or an (I)RET happened between the record and
	 * PMI.
	 */
	अगर (sample_type & PERF_SAMPLE_CALLCHAIN)
		data->callchain = perf_callchain(event, iregs);

	/*
	 * We use the पूर्णांकerrupt regs as a base because the PEBS record करोes not
	 * contain a full regs set, specअगरically it seems to lack segment
	 * descriptors, which get used by things like user_mode().
	 *
	 * In the simple हाल fix up only the IP क्रम PERF_SAMPLE_IP.
	 */
	*regs = *iregs;

	/*
	 * Initialize regs_>flags from PEBS,
	 * Clear exact bit (which uses x86 EFLAGS Reserved bit 3),
	 * i.e., करो not rely on it being zero:
	 */
	regs->flags = pebs->flags & ~PERF_EFLAGS_EXACT;

	अगर (sample_type & PERF_SAMPLE_REGS_INTR) अणु
		regs->ax = pebs->ax;
		regs->bx = pebs->bx;
		regs->cx = pebs->cx;
		regs->dx = pebs->dx;
		regs->si = pebs->si;
		regs->di = pebs->di;

		regs->bp = pebs->bp;
		regs->sp = pebs->sp;

#अगर_अघोषित CONFIG_X86_32
		regs->r8 = pebs->r8;
		regs->r9 = pebs->r9;
		regs->r10 = pebs->r10;
		regs->r11 = pebs->r11;
		regs->r12 = pebs->r12;
		regs->r13 = pebs->r13;
		regs->r14 = pebs->r14;
		regs->r15 = pebs->r15;
#पूर्ण_अगर
	पूर्ण

	अगर (event->attr.precise_ip > 1) अणु
		/*
		 * Haswell and later processors have an 'eventing IP'
		 * (real IP) which fixes the off-by-1 skid in hardware.
		 * Use it when precise_ip >= 2 :
		 */
		अगर (x86_pmu.पूर्णांकel_cap.pebs_क्रमmat >= 2) अणु
			set_linear_ip(regs, pebs->real_ip);
			regs->flags |= PERF_EFLAGS_EXACT;
		पूर्ण अन्यथा अणु
			/* Otherwise, use PEBS off-by-1 IP: */
			set_linear_ip(regs, pebs->ip);

			/*
			 * With precise_ip >= 2, try to fix up the off-by-1 IP
			 * using the LBR. If successful, the fixup function
			 * corrects regs->ip and calls set_linear_ip() on regs:
			 */
			अगर (पूर्णांकel_pmu_pebs_fixup_ip(regs))
				regs->flags |= PERF_EFLAGS_EXACT;
		पूर्ण
	पूर्ण अन्यथा अणु
		/*
		 * When precise_ip == 1, वापस the PEBS off-by-1 IP,
		 * no fixup attempted:
		 */
		set_linear_ip(regs, pebs->ip);
	पूर्ण


	अगर ((sample_type & PERF_SAMPLE_ADDR_TYPE) &&
	    x86_pmu.पूर्णांकel_cap.pebs_क्रमmat >= 1)
		data->addr = pebs->dla;

	अगर (x86_pmu.पूर्णांकel_cap.pebs_क्रमmat >= 2) अणु
		/* Only set the TSX weight when no memory weight. */
		अगर ((sample_type & PERF_SAMPLE_WEIGHT_TYPE) && !fll)
			data->weight.full = पूर्णांकel_get_tsx_weight(pebs->tsx_tuning);

		अगर (sample_type & PERF_SAMPLE_TRANSACTION)
			data->txn = पूर्णांकel_get_tsx_transaction(pebs->tsx_tuning,
							      pebs->ax);
	पूर्ण

	/*
	 * v3 supplies an accurate समय stamp, so we use that
	 * क्रम the समय stamp.
	 *
	 * We can only करो this क्रम the शेष trace घड़ी.
	 */
	अगर (x86_pmu.पूर्णांकel_cap.pebs_क्रमmat >= 3 &&
		event->attr.use_घड़ीid == 0)
		data->समय = native_sched_घड़ी_from_tsc(pebs->tsc);

	अगर (has_branch_stack(event))
		data->br_stack = &cpuc->lbr_stack;
पूर्ण

अटल व्योम adaptive_pebs_save_regs(काष्ठा pt_regs *regs,
				    काष्ठा pebs_gprs *gprs)
अणु
	regs->ax = gprs->ax;
	regs->bx = gprs->bx;
	regs->cx = gprs->cx;
	regs->dx = gprs->dx;
	regs->si = gprs->si;
	regs->di = gprs->di;
	regs->bp = gprs->bp;
	regs->sp = gprs->sp;
#अगर_अघोषित CONFIG_X86_32
	regs->r8 = gprs->r8;
	regs->r9 = gprs->r9;
	regs->r10 = gprs->r10;
	regs->r11 = gprs->r11;
	regs->r12 = gprs->r12;
	regs->r13 = gprs->r13;
	regs->r14 = gprs->r14;
	regs->r15 = gprs->r15;
#पूर्ण_अगर
पूर्ण

#घोषणा PEBS_LATENCY_MASK			0xffff
#घोषणा PEBS_CACHE_LATENCY_OFFSET		32

/*
 * With adaptive PEBS the layout depends on what fields are configured.
 */

अटल व्योम setup_pebs_adaptive_sample_data(काष्ठा perf_event *event,
					    काष्ठा pt_regs *iregs, व्योम *__pebs,
					    काष्ठा perf_sample_data *data,
					    काष्ठा pt_regs *regs)
अणु
	काष्ठा cpu_hw_events *cpuc = this_cpu_ptr(&cpu_hw_events);
	काष्ठा pebs_basic *basic = __pebs;
	व्योम *next_record = basic + 1;
	u64 sample_type;
	u64 क्रमmat_size;
	काष्ठा pebs_meminfo *meminfo = शून्य;
	काष्ठा pebs_gprs *gprs = शून्य;
	काष्ठा x86_perf_regs *perf_regs;

	अगर (basic == शून्य)
		वापस;

	perf_regs = container_of(regs, काष्ठा x86_perf_regs, regs);
	perf_regs->xmm_regs = शून्य;

	sample_type = event->attr.sample_type;
	क्रमmat_size = basic->क्रमmat_size;
	perf_sample_data_init(data, 0, event->hw.last_period);
	data->period = event->hw.last_period;

	अगर (event->attr.use_घड़ीid == 0)
		data->समय = native_sched_घड़ी_from_tsc(basic->tsc);

	/*
	 * We must however always use iregs क्रम the unwinder to stay sane; the
	 * record BP,SP,IP can poपूर्णांक पूर्णांकo thin air when the record is from a
	 * previous PMI context or an (I)RET happened between the record and
	 * PMI.
	 */
	अगर (sample_type & PERF_SAMPLE_CALLCHAIN)
		data->callchain = perf_callchain(event, iregs);

	*regs = *iregs;
	/* The ip in basic is EventingIP */
	set_linear_ip(regs, basic->ip);
	regs->flags = PERF_EFLAGS_EXACT;

	/*
	 * The record क्रम MEMINFO is in front of GP
	 * But PERF_SAMPLE_TRANSACTION needs gprs->ax.
	 * Save the poपूर्णांकer here but process later.
	 */
	अगर (क्रमmat_size & PEBS_DATACFG_MEMINFO) अणु
		meminfo = next_record;
		next_record = meminfo + 1;
	पूर्ण

	अगर (क्रमmat_size & PEBS_DATACFG_GP) अणु
		gprs = next_record;
		next_record = gprs + 1;

		अगर (event->attr.precise_ip < 2) अणु
			set_linear_ip(regs, gprs->ip);
			regs->flags &= ~PERF_EFLAGS_EXACT;
		पूर्ण

		अगर (sample_type & PERF_SAMPLE_REGS_INTR)
			adaptive_pebs_save_regs(regs, gprs);
	पूर्ण

	अगर (क्रमmat_size & PEBS_DATACFG_MEMINFO) अणु
		अगर (sample_type & PERF_SAMPLE_WEIGHT_TYPE) अणु
			u64 weight = meminfo->latency;

			अगर (x86_pmu.flags & PMU_FL_INSTR_LATENCY) अणु
				data->weight.var2_w = weight & PEBS_LATENCY_MASK;
				weight >>= PEBS_CACHE_LATENCY_OFFSET;
			पूर्ण

			/*
			 * Although meminfo::latency is defined as a u64,
			 * only the lower 32 bits include the valid data
			 * in practice on Ice Lake and earlier platक्रमms.
			 */
			अगर (sample_type & PERF_SAMPLE_WEIGHT) अणु
				data->weight.full = weight ?:
					पूर्णांकel_get_tsx_weight(meminfo->tsx_tuning);
			पूर्ण अन्यथा अणु
				data->weight.var1_dw = (u32)(weight & PEBS_LATENCY_MASK) ?:
					पूर्णांकel_get_tsx_weight(meminfo->tsx_tuning);
			पूर्ण
		पूर्ण

		अगर (sample_type & PERF_SAMPLE_DATA_SRC)
			data->data_src.val = get_data_src(event, meminfo->aux);

		अगर (sample_type & PERF_SAMPLE_ADDR_TYPE)
			data->addr = meminfo->address;

		अगर (sample_type & PERF_SAMPLE_TRANSACTION)
			data->txn = पूर्णांकel_get_tsx_transaction(meminfo->tsx_tuning,
							  gprs ? gprs->ax : 0);
	पूर्ण

	अगर (क्रमmat_size & PEBS_DATACFG_XMMS) अणु
		काष्ठा pebs_xmm *xmm = next_record;

		next_record = xmm + 1;
		perf_regs->xmm_regs = xmm->xmm;
	पूर्ण

	अगर (क्रमmat_size & PEBS_DATACFG_LBRS) अणु
		काष्ठा lbr_entry *lbr = next_record;
		पूर्णांक num_lbr = ((क्रमmat_size >> PEBS_DATACFG_LBR_SHIFT)
					& 0xff) + 1;
		next_record = next_record + num_lbr * माप(काष्ठा lbr_entry);

		अगर (has_branch_stack(event)) अणु
			पूर्णांकel_pmu_store_pebs_lbrs(lbr);
			data->br_stack = &cpuc->lbr_stack;
		पूर्ण
	पूर्ण

	WARN_ONCE(next_record != __pebs + (क्रमmat_size >> 48),
			"PEBS record size %llu, expected %llu, config %llx\n",
			क्रमmat_size >> 48,
			(u64)(next_record - __pebs),
			basic->क्रमmat_size);
पूर्ण

अटल अंतरभूत व्योम *
get_next_pebs_record_by_bit(व्योम *base, व्योम *top, पूर्णांक bit)
अणु
	काष्ठा cpu_hw_events *cpuc = this_cpu_ptr(&cpu_hw_events);
	व्योम *at;
	u64 pebs_status;

	/*
	 * fmt0 करोes not have a status bitfield (करोes not use
	 * perf_record_nhm क्रमmat)
	 */
	अगर (x86_pmu.पूर्णांकel_cap.pebs_क्रमmat < 1)
		वापस base;

	अगर (base == शून्य)
		वापस शून्य;

	क्रम (at = base; at < top; at += cpuc->pebs_record_size) अणु
		अचिन्हित दीर्घ status = get_pebs_status(at);

		अगर (test_bit(bit, (अचिन्हित दीर्घ *)&status)) अणु
			/* PEBS v3 has accurate status bits */
			अगर (x86_pmu.पूर्णांकel_cap.pebs_क्रमmat >= 3)
				वापस at;

			अगर (status == (1 << bit))
				वापस at;

			/* clear non-PEBS bit and re-check */
			pebs_status = status & cpuc->pebs_enabled;
			pebs_status &= PEBS_COUNTER_MASK;
			अगर (pebs_status == (1 << bit))
				वापस at;
		पूर्ण
	पूर्ण
	वापस शून्य;
पूर्ण

व्योम पूर्णांकel_pmu_स्वतः_reload_पढ़ो(काष्ठा perf_event *event)
अणु
	WARN_ON(!(event->hw.flags & PERF_X86_EVENT_AUTO_RELOAD));

	perf_pmu_disable(event->pmu);
	पूर्णांकel_pmu_drain_pebs_buffer();
	perf_pmu_enable(event->pmu);
पूर्ण

/*
 * Special variant of पूर्णांकel_pmu_save_and_restart() क्रम स्वतः-reload.
 */
अटल पूर्णांक
पूर्णांकel_pmu_save_and_restart_reload(काष्ठा perf_event *event, पूर्णांक count)
अणु
	काष्ठा hw_perf_event *hwc = &event->hw;
	पूर्णांक shअगरt = 64 - x86_pmu.cntval_bits;
	u64 period = hwc->sample_period;
	u64 prev_raw_count, new_raw_count;
	s64 new, old;

	WARN_ON(!period);

	/*
	 * drain_pebs() only happens when the PMU is disabled.
	 */
	WARN_ON(this_cpu_पढ़ो(cpu_hw_events.enabled));

	prev_raw_count = local64_पढ़ो(&hwc->prev_count);
	rdpmcl(hwc->event_base_rdpmc, new_raw_count);
	local64_set(&hwc->prev_count, new_raw_count);

	/*
	 * Since the counter increments a negative counter value and
	 * overflows on the sign चयन, giving the पूर्णांकerval:
	 *
	 *   [-period, 0]
	 *
	 * the dअगरference between two consecutive पढ़ोs is:
	 *
	 *   A) value2 - value1;
	 *      when no overflows have happened in between,
	 *
	 *   B) (0 - value1) + (value2 - (-period));
	 *      when one overflow happened in between,
	 *
	 *   C) (0 - value1) + (n - 1) * (period) + (value2 - (-period));
	 *      when @n overflows happened in between.
	 *
	 * Here A) is the obvious dअगरference, B) is the extension to the
	 * discrete पूर्णांकerval, where the first term is to the top of the
	 * पूर्णांकerval and the second term is from the bottom of the next
	 * पूर्णांकerval and C) the extension to multiple पूर्णांकervals, where the
	 * middle term is the whole पूर्णांकervals covered.
	 *
	 * An equivalent of C, by reduction, is:
	 *
	 *   value2 - value1 + n * period
	 */
	new = ((s64)(new_raw_count << shअगरt) >> shअगरt);
	old = ((s64)(prev_raw_count << shअगरt) >> shअगरt);
	local64_add(new - old + count * period, &event->count);

	local64_set(&hwc->period_left, -new);

	perf_event_update_userpage(event);

	वापस 0;
पूर्ण

अटल __always_अंतरभूत व्योम
__पूर्णांकel_pmu_pebs_event(काष्ठा perf_event *event,
		       काष्ठा pt_regs *iregs,
		       काष्ठा perf_sample_data *data,
		       व्योम *base, व्योम *top,
		       पूर्णांक bit, पूर्णांक count,
		       व्योम (*setup_sample)(काष्ठा perf_event *,
					    काष्ठा pt_regs *,
					    व्योम *,
					    काष्ठा perf_sample_data *,
					    काष्ठा pt_regs *))
अणु
	काष्ठा cpu_hw_events *cpuc = this_cpu_ptr(&cpu_hw_events);
	काष्ठा hw_perf_event *hwc = &event->hw;
	काष्ठा x86_perf_regs perf_regs;
	काष्ठा pt_regs *regs = &perf_regs.regs;
	व्योम *at = get_next_pebs_record_by_bit(base, top, bit);
	अटल काष्ठा pt_regs dummy_iregs;

	अगर (hwc->flags & PERF_X86_EVENT_AUTO_RELOAD) अणु
		/*
		 * Now, स्वतः-reload is only enabled in fixed period mode.
		 * The reload value is always hwc->sample_period.
		 * May need to change it, अगर स्वतः-reload is enabled in
		 * freq mode later.
		 */
		पूर्णांकel_pmu_save_and_restart_reload(event, count);
	पूर्ण अन्यथा अगर (!पूर्णांकel_pmu_save_and_restart(event))
		वापस;

	अगर (!iregs)
		iregs = &dummy_iregs;

	जबतक (count > 1) अणु
		setup_sample(event, iregs, at, data, regs);
		perf_event_output(event, data, regs);
		at += cpuc->pebs_record_size;
		at = get_next_pebs_record_by_bit(at, top, bit);
		count--;
	पूर्ण

	setup_sample(event, iregs, at, data, regs);
	अगर (iregs == &dummy_iregs) अणु
		/*
		 * The PEBS records may be drained in the non-overflow context,
		 * e.g., large PEBS + context चयन. Perf should treat the
		 * last record the same as other PEBS records, and करोesn't
		 * invoke the generic overflow handler.
		 */
		perf_event_output(event, data, regs);
	पूर्ण अन्यथा अणु
		/*
		 * All but the last records are processed.
		 * The last one is left to be able to call the overflow handler.
		 */
		अगर (perf_event_overflow(event, data, regs))
			x86_pmu_stop(event, 0);
	पूर्ण
पूर्ण

अटल व्योम पूर्णांकel_pmu_drain_pebs_core(काष्ठा pt_regs *iregs, काष्ठा perf_sample_data *data)
अणु
	काष्ठा cpu_hw_events *cpuc = this_cpu_ptr(&cpu_hw_events);
	काष्ठा debug_store *ds = cpuc->ds;
	काष्ठा perf_event *event = cpuc->events[0]; /* PMC0 only */
	काष्ठा pebs_record_core *at, *top;
	पूर्णांक n;

	अगर (!x86_pmu.pebs_active)
		वापस;

	at  = (काष्ठा pebs_record_core *)(अचिन्हित दीर्घ)ds->pebs_buffer_base;
	top = (काष्ठा pebs_record_core *)(अचिन्हित दीर्घ)ds->pebs_index;

	/*
	 * Whatever अन्यथा happens, drain the thing
	 */
	ds->pebs_index = ds->pebs_buffer_base;

	अगर (!test_bit(0, cpuc->active_mask))
		वापस;

	WARN_ON_ONCE(!event);

	अगर (!event->attr.precise_ip)
		वापस;

	n = top - at;
	अगर (n <= 0) अणु
		अगर (event->hw.flags & PERF_X86_EVENT_AUTO_RELOAD)
			पूर्णांकel_pmu_save_and_restart_reload(event, 0);
		वापस;
	पूर्ण

	__पूर्णांकel_pmu_pebs_event(event, iregs, data, at, top, 0, n,
			       setup_pebs_fixed_sample_data);
पूर्ण

अटल व्योम पूर्णांकel_pmu_pebs_event_update_no_drain(काष्ठा cpu_hw_events *cpuc, पूर्णांक size)
अणु
	काष्ठा perf_event *event;
	पूर्णांक bit;

	/*
	 * The drain_pebs() could be called twice in a लघु period
	 * क्रम स्वतः-reload event in pmu::पढ़ो(). There are no
	 * overflows have happened in between.
	 * It needs to call पूर्णांकel_pmu_save_and_restart_reload() to
	 * update the event->count क्रम this हाल.
	 */
	क्रम_each_set_bit(bit, (अचिन्हित दीर्घ *)&cpuc->pebs_enabled, size) अणु
		event = cpuc->events[bit];
		अगर (event->hw.flags & PERF_X86_EVENT_AUTO_RELOAD)
			पूर्णांकel_pmu_save_and_restart_reload(event, 0);
	पूर्ण
पूर्ण

अटल व्योम पूर्णांकel_pmu_drain_pebs_nhm(काष्ठा pt_regs *iregs, काष्ठा perf_sample_data *data)
अणु
	काष्ठा cpu_hw_events *cpuc = this_cpu_ptr(&cpu_hw_events);
	काष्ठा debug_store *ds = cpuc->ds;
	काष्ठा perf_event *event;
	व्योम *base, *at, *top;
	लघु counts[INTEL_PMC_IDX_FIXED + MAX_FIXED_PEBS_EVENTS] = अणुपूर्ण;
	लघु error[INTEL_PMC_IDX_FIXED + MAX_FIXED_PEBS_EVENTS] = अणुपूर्ण;
	पूर्णांक bit, i, size;
	u64 mask;

	अगर (!x86_pmu.pebs_active)
		वापस;

	base = (काष्ठा pebs_record_nhm *)(अचिन्हित दीर्घ)ds->pebs_buffer_base;
	top = (काष्ठा pebs_record_nhm *)(अचिन्हित दीर्घ)ds->pebs_index;

	ds->pebs_index = ds->pebs_buffer_base;

	mask = (1ULL << x86_pmu.max_pebs_events) - 1;
	size = x86_pmu.max_pebs_events;
	अगर (x86_pmu.flags & PMU_FL_PEBS_ALL) अणु
		mask |= ((1ULL << x86_pmu.num_counters_fixed) - 1) << INTEL_PMC_IDX_FIXED;
		size = INTEL_PMC_IDX_FIXED + x86_pmu.num_counters_fixed;
	पूर्ण

	अगर (unlikely(base >= top)) अणु
		पूर्णांकel_pmu_pebs_event_update_no_drain(cpuc, size);
		वापस;
	पूर्ण

	क्रम (at = base; at < top; at += x86_pmu.pebs_record_size) अणु
		काष्ठा pebs_record_nhm *p = at;
		u64 pebs_status;

		pebs_status = p->status & cpuc->pebs_enabled;
		pebs_status &= mask;

		/* PEBS v3 has more accurate status bits */
		अगर (x86_pmu.पूर्णांकel_cap.pebs_क्रमmat >= 3) अणु
			क्रम_each_set_bit(bit, (अचिन्हित दीर्घ *)&pebs_status, size)
				counts[bit]++;

			जारी;
		पूर्ण

		/*
		 * On some CPUs the PEBS status can be zero when PEBS is
		 * racing with clearing of GLOBAL_STATUS.
		 *
		 * Normally we would drop that record, but in the
		 * हाल when there is only a single active PEBS event
		 * we can assume it's क्रम that event.
		 */
		अगर (!pebs_status && cpuc->pebs_enabled &&
			!(cpuc->pebs_enabled & (cpuc->pebs_enabled-1)))
			pebs_status = p->status = cpuc->pebs_enabled;

		bit = find_first_bit((अचिन्हित दीर्घ *)&pebs_status,
					x86_pmu.max_pebs_events);
		अगर (bit >= x86_pmu.max_pebs_events)
			जारी;

		/*
		 * The PEBS hardware करोes not deal well with the situation
		 * when events happen near to each other and multiple bits
		 * are set. But it should happen rarely.
		 *
		 * If these events include one PEBS and multiple non-PEBS
		 * events, it करोesn't impact PEBS record. The record will
		 * be handled normally. (slow path)
		 *
		 * If these events include two or more PEBS events, the
		 * records क्रम the events can be collapsed पूर्णांकo a single
		 * one, and it's not possible to reस्थिरruct all events
		 * that caused the PEBS record. It's called collision.
		 * If collision happened, the record will be dropped.
		 */
		अगर (pebs_status != (1ULL << bit)) अणु
			क्रम_each_set_bit(i, (अचिन्हित दीर्घ *)&pebs_status, size)
				error[i]++;
			जारी;
		पूर्ण

		counts[bit]++;
	पूर्ण

	क्रम_each_set_bit(bit, (अचिन्हित दीर्घ *)&mask, size) अणु
		अगर ((counts[bit] == 0) && (error[bit] == 0))
			जारी;

		event = cpuc->events[bit];
		अगर (WARN_ON_ONCE(!event))
			जारी;

		अगर (WARN_ON_ONCE(!event->attr.precise_ip))
			जारी;

		/* log dropped samples number */
		अगर (error[bit]) अणु
			perf_log_lost_samples(event, error[bit]);

			अगर (iregs && perf_event_account_पूर्णांकerrupt(event))
				x86_pmu_stop(event, 0);
		पूर्ण

		अगर (counts[bit]) अणु
			__पूर्णांकel_pmu_pebs_event(event, iregs, data, base,
					       top, bit, counts[bit],
					       setup_pebs_fixed_sample_data);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम पूर्णांकel_pmu_drain_pebs_icl(काष्ठा pt_regs *iregs, काष्ठा perf_sample_data *data)
अणु
	लघु counts[INTEL_PMC_IDX_FIXED + MAX_FIXED_PEBS_EVENTS] = अणुपूर्ण;
	काष्ठा cpu_hw_events *cpuc = this_cpu_ptr(&cpu_hw_events);
	पूर्णांक max_pebs_events = hybrid(cpuc->pmu, max_pebs_events);
	पूर्णांक num_counters_fixed = hybrid(cpuc->pmu, num_counters_fixed);
	काष्ठा debug_store *ds = cpuc->ds;
	काष्ठा perf_event *event;
	व्योम *base, *at, *top;
	पूर्णांक bit, size;
	u64 mask;

	अगर (!x86_pmu.pebs_active)
		वापस;

	base = (काष्ठा pebs_basic *)(अचिन्हित दीर्घ)ds->pebs_buffer_base;
	top = (काष्ठा pebs_basic *)(अचिन्हित दीर्घ)ds->pebs_index;

	ds->pebs_index = ds->pebs_buffer_base;

	mask = ((1ULL << max_pebs_events) - 1) |
	       (((1ULL << num_counters_fixed) - 1) << INTEL_PMC_IDX_FIXED);
	size = INTEL_PMC_IDX_FIXED + num_counters_fixed;

	अगर (unlikely(base >= top)) अणु
		पूर्णांकel_pmu_pebs_event_update_no_drain(cpuc, size);
		वापस;
	पूर्ण

	क्रम (at = base; at < top; at += cpuc->pebs_record_size) अणु
		u64 pebs_status;

		pebs_status = get_pebs_status(at) & cpuc->pebs_enabled;
		pebs_status &= mask;

		क्रम_each_set_bit(bit, (अचिन्हित दीर्घ *)&pebs_status, size)
			counts[bit]++;
	पूर्ण

	क्रम_each_set_bit(bit, (अचिन्हित दीर्घ *)&mask, size) अणु
		अगर (counts[bit] == 0)
			जारी;

		event = cpuc->events[bit];
		अगर (WARN_ON_ONCE(!event))
			जारी;

		अगर (WARN_ON_ONCE(!event->attr.precise_ip))
			जारी;

		__पूर्णांकel_pmu_pebs_event(event, iregs, data, base,
				       top, bit, counts[bit],
				       setup_pebs_adaptive_sample_data);
	पूर्ण
पूर्ण

/*
 * BTS, PEBS probe and setup
 */

व्योम __init पूर्णांकel_ds_init(व्योम)
अणु
	/*
	 * No support क्रम 32bit क्रमmats
	 */
	अगर (!boot_cpu_has(X86_FEATURE_DTES64))
		वापस;

	x86_pmu.bts  = boot_cpu_has(X86_FEATURE_BTS);
	x86_pmu.pebs = boot_cpu_has(X86_FEATURE_PEBS);
	x86_pmu.pebs_buffer_size = PEBS_BUFFER_SIZE;
	अगर (x86_pmu.version <= 4)
		x86_pmu.pebs_no_isolation = 1;

	अगर (x86_pmu.pebs) अणु
		अक्षर pebs_type = x86_pmu.पूर्णांकel_cap.pebs_trap ?  '+' : '-';
		अक्षर *pebs_qual = "";
		पूर्णांक क्रमmat = x86_pmu.पूर्णांकel_cap.pebs_क्रमmat;

		अगर (क्रमmat < 4)
			x86_pmu.पूर्णांकel_cap.pebs_baseline = 0;

		चयन (क्रमmat) अणु
		हाल 0:
			pr_cont("PEBS fmt0%c, ", pebs_type);
			x86_pmu.pebs_record_size = माप(काष्ठा pebs_record_core);
			/*
			 * Using >PAGE_SIZE buffers makes the WRMSR to
			 * PERF_GLOBAL_CTRL in पूर्णांकel_pmu_enable_all()
			 * mysteriously hang on Core2.
			 *
			 * As a workaround, we करोn't करो this.
			 */
			x86_pmu.pebs_buffer_size = PAGE_SIZE;
			x86_pmu.drain_pebs = पूर्णांकel_pmu_drain_pebs_core;
			अवरोध;

		हाल 1:
			pr_cont("PEBS fmt1%c, ", pebs_type);
			x86_pmu.pebs_record_size = माप(काष्ठा pebs_record_nhm);
			x86_pmu.drain_pebs = पूर्णांकel_pmu_drain_pebs_nhm;
			अवरोध;

		हाल 2:
			pr_cont("PEBS fmt2%c, ", pebs_type);
			x86_pmu.pebs_record_size = माप(काष्ठा pebs_record_hsw);
			x86_pmu.drain_pebs = पूर्णांकel_pmu_drain_pebs_nhm;
			अवरोध;

		हाल 3:
			pr_cont("PEBS fmt3%c, ", pebs_type);
			x86_pmu.pebs_record_size =
						माप(काष्ठा pebs_record_skl);
			x86_pmu.drain_pebs = पूर्णांकel_pmu_drain_pebs_nhm;
			x86_pmu.large_pebs_flags |= PERF_SAMPLE_TIME;
			अवरोध;

		हाल 4:
			x86_pmu.drain_pebs = पूर्णांकel_pmu_drain_pebs_icl;
			x86_pmu.pebs_record_size = माप(काष्ठा pebs_basic);
			अगर (x86_pmu.पूर्णांकel_cap.pebs_baseline) अणु
				x86_pmu.large_pebs_flags |=
					PERF_SAMPLE_BRANCH_STACK |
					PERF_SAMPLE_TIME;
				x86_pmu.flags |= PMU_FL_PEBS_ALL;
				pebs_qual = "-baseline";
				x86_get_pmu(smp_processor_id())->capabilities |= PERF_PMU_CAP_EXTENDED_REGS;
			पूर्ण अन्यथा अणु
				/* Only basic record supported */
				x86_pmu.large_pebs_flags &=
					~(PERF_SAMPLE_ADDR |
					  PERF_SAMPLE_TIME |
					  PERF_SAMPLE_DATA_SRC |
					  PERF_SAMPLE_TRANSACTION |
					  PERF_SAMPLE_REGS_USER |
					  PERF_SAMPLE_REGS_INTR);
			पूर्ण
			pr_cont("PEBS fmt4%c%s, ", pebs_type, pebs_qual);

			अगर (!is_hybrid() && x86_pmu.पूर्णांकel_cap.pebs_output_pt_available) अणु
				pr_cont("PEBS-via-PT, ");
				x86_get_pmu(smp_processor_id())->capabilities |= PERF_PMU_CAP_AUX_OUTPUT;
			पूर्ण

			अवरोध;

		शेष:
			pr_cont("no PEBS fmt%d%c, ", क्रमmat, pebs_type);
			x86_pmu.pebs = 0;
		पूर्ण
	पूर्ण
पूर्ण

व्योम perf_restore_debug_store(व्योम)
अणु
	काष्ठा debug_store *ds = __this_cpu_पढ़ो(cpu_hw_events.ds);

	अगर (!x86_pmu.bts && !x86_pmu.pebs)
		वापस;

	wrmsrl(MSR_IA32_DS_AREA, (अचिन्हित दीर्घ)ds);
पूर्ण
