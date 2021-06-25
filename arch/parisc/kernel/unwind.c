<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Kernel unwinding support
 *
 * (c) 2002-2004 Ranकरोlph Chung <tausq@debian.org>
 *
 * Derived partially from the IA64 implementation. The PA-RISC
 * Runसमय Architecture Document is also a useful reference to
 * understand what is happening here
 */

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/sort.h>

#समावेश <linux/uaccess.h>
#समावेश <यंत्र/assembly.h>
#समावेश <यंत्र/यंत्र-offsets.h>
#समावेश <यंत्र/ptrace.h>

#समावेश <यंत्र/unwind.h>

/* #घोषणा DEBUG 1 */
#अगर_घोषित DEBUG
#घोषणा dbg(x...) pr_debug(x)
#अन्यथा
#घोषणा dbg(x...)
#पूर्ण_अगर

#घोषणा KERNEL_START (KERNEL_BINARY_TEXT_START)

बाह्य काष्ठा unwind_table_entry __start___unwind[];
बाह्य काष्ठा unwind_table_entry __stop___unwind[];

अटल DEFINE_SPINLOCK(unwind_lock);
/*
 * the kernel unwind block is not dynamically allocated so that
 * we can call unwind_init as early in the bootup process as 
 * possible (beक्रमe the slab allocator is initialized)
 */
अटल काष्ठा unwind_table kernel_unwind_table __ro_after_init;
अटल LIST_HEAD(unwind_tables);

अटल अंतरभूत स्थिर काष्ठा unwind_table_entry *
find_unwind_entry_in_table(स्थिर काष्ठा unwind_table *table, अचिन्हित दीर्घ addr)
अणु
	स्थिर काष्ठा unwind_table_entry *e = शून्य;
	अचिन्हित दीर्घ lo, hi, mid;

	lo = 0; 
	hi = table->length - 1; 
	
	जबतक (lo <= hi) अणु
		mid = (hi - lo) / 2 + lo;
		e = &table->table[mid];
		अगर (addr < e->region_start)
			hi = mid - 1;
		अन्यथा अगर (addr > e->region_end)
			lo = mid + 1;
		अन्यथा
			वापस e;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल स्थिर काष्ठा unwind_table_entry *
find_unwind_entry(अचिन्हित दीर्घ addr)
अणु
	काष्ठा unwind_table *table;
	स्थिर काष्ठा unwind_table_entry *e = शून्य;

	अगर (addr >= kernel_unwind_table.start && 
	    addr <= kernel_unwind_table.end)
		e = find_unwind_entry_in_table(&kernel_unwind_table, addr);
	अन्यथा अणु
		अचिन्हित दीर्घ flags;

		spin_lock_irqsave(&unwind_lock, flags);
		list_क्रम_each_entry(table, &unwind_tables, list) अणु
			अगर (addr >= table->start && 
			    addr <= table->end)
				e = find_unwind_entry_in_table(table, addr);
			अगर (e) अणु
				/* Move-to-front to exploit common traces */
				list_move(&table->list, &unwind_tables);
				अवरोध;
			पूर्ण
		पूर्ण
		spin_unlock_irqrestore(&unwind_lock, flags);
	पूर्ण

	वापस e;
पूर्ण

अटल व्योम
unwind_table_init(काष्ठा unwind_table *table, स्थिर अक्षर *name,
		  अचिन्हित दीर्घ base_addr, अचिन्हित दीर्घ gp,
		  व्योम *table_start, व्योम *table_end)
अणु
	काष्ठा unwind_table_entry *start = table_start;
	काष्ठा unwind_table_entry *end = 
		(काष्ठा unwind_table_entry *)table_end - 1;

	table->name = name;
	table->base_addr = base_addr;
	table->gp = gp;
	table->start = base_addr + start->region_start;
	table->end = base_addr + end->region_end;
	table->table = (काष्ठा unwind_table_entry *)table_start;
	table->length = end - start + 1;
	INIT_LIST_HEAD(&table->list);

	क्रम (; start <= end; start++) अणु
		अगर (start < end && 
		    start->region_end > (start+1)->region_start) अणु
			pr_warn("Out of order unwind entry! %px and %px\n",
				start, start+1);
		पूर्ण

		start->region_start += base_addr;
		start->region_end += base_addr;
	पूर्ण
पूर्ण

अटल पूर्णांक cmp_unwind_table_entry(स्थिर व्योम *a, स्थिर व्योम *b)
अणु
	वापस ((स्थिर काष्ठा unwind_table_entry *)a)->region_start
	     - ((स्थिर काष्ठा unwind_table_entry *)b)->region_start;
पूर्ण

अटल व्योम
unwind_table_sort(काष्ठा unwind_table_entry *start,
		  काष्ठा unwind_table_entry *finish)
अणु
	sort(start, finish - start, माप(काष्ठा unwind_table_entry),
	     cmp_unwind_table_entry, शून्य);
पूर्ण

काष्ठा unwind_table *
unwind_table_add(स्थिर अक्षर *name, अचिन्हित दीर्घ base_addr, 
		 अचिन्हित दीर्घ gp,
                 व्योम *start, व्योम *end)
अणु
	काष्ठा unwind_table *table;
	अचिन्हित दीर्घ flags;
	काष्ठा unwind_table_entry *s = (काष्ठा unwind_table_entry *)start;
	काष्ठा unwind_table_entry *e = (काष्ठा unwind_table_entry *)end;

	unwind_table_sort(s, e);

	table = kदो_स्मृति(माप(काष्ठा unwind_table), GFP_USER);
	अगर (table == शून्य)
		वापस शून्य;
	unwind_table_init(table, name, base_addr, gp, start, end);
	spin_lock_irqsave(&unwind_lock, flags);
	list_add_tail(&table->list, &unwind_tables);
	spin_unlock_irqrestore(&unwind_lock, flags);

	वापस table;
पूर्ण

व्योम unwind_table_हटाओ(काष्ठा unwind_table *table)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&unwind_lock, flags);
	list_del(&table->list);
	spin_unlock_irqrestore(&unwind_lock, flags);

	kमुक्त(table);
पूर्ण

/* Called from setup_arch to import the kernel unwind info */
पूर्णांक __init unwind_init(व्योम)
अणु
	दीर्घ start, stop;
	रेजिस्टर अचिन्हित दीर्घ gp __यंत्र__ ("r27");

	start = (दीर्घ)&__start___unwind[0];
	stop = (दीर्घ)&__stop___unwind[0];

	dbg("unwind_init: start = 0x%lx, end = 0x%lx, entries = %lu\n",
	    start, stop,
	    (stop - start) / माप(काष्ठा unwind_table_entry));

	unwind_table_init(&kernel_unwind_table, "kernel", KERNEL_START,
			  gp, 
			  &__start___unwind[0], &__stop___unwind[0]);
#अगर 0
	अणु
		पूर्णांक i;
		क्रम (i = 0; i < 10; i++)
		अणु
			prपूर्णांकk("region 0x%x-0x%x\n", 
				__start___unwind[i].region_start, 
				__start___unwind[i].region_end);
		पूर्ण
	पूर्ण
#पूर्ण_अगर
	वापस 0;
पूर्ण

अटल पूर्णांक unwind_special(काष्ठा unwind_frame_info *info, अचिन्हित दीर्घ pc, पूर्णांक frame_size)
अणु
	/*
	 * We have to use व्योम * instead of a function poपूर्णांकer, because
	 * function poपूर्णांकers aren't a poपूर्णांकer to the function on 64-bit.
	 * Make them स्थिर so the compiler knows they live in .text
	 * Note: We could use dereference_kernel_function_descriptor()
	 * instead but we want to keep it simple here.
	 */
	बाह्य व्योम * स्थिर handle_पूर्णांकerruption;
	बाह्य व्योम * स्थिर ret_from_kernel_thपढ़ो;
	बाह्य व्योम * स्थिर syscall_निकास;
	बाह्य व्योम * स्थिर पूर्णांकr_वापस;
	बाह्य व्योम * स्थिर _चयन_to_ret;
#अगर_घोषित CONFIG_IRQSTACKS
	बाह्य व्योम * स्थिर _call_on_stack;
#पूर्ण_अगर /* CONFIG_IRQSTACKS */

	अगर (pc == (अचिन्हित दीर्घ) &handle_पूर्णांकerruption) अणु
		काष्ठा pt_regs *regs = (काष्ठा pt_regs *)(info->sp - frame_size - PT_SZ_ALGN);
		dbg("Unwinding through handle_interruption()\n");
		info->prev_sp = regs->gr[30];
		info->prev_ip = regs->iaoq[0];
		वापस 1;
	पूर्ण

	अगर (pc == (अचिन्हित दीर्घ) &ret_from_kernel_thपढ़ो ||
	    pc == (अचिन्हित दीर्घ) &syscall_निकास) अणु
		info->prev_sp = info->prev_ip = 0;
		वापस 1;
	पूर्ण

	अगर (pc == (अचिन्हित दीर्घ) &पूर्णांकr_वापस) अणु
		काष्ठा pt_regs *regs;

		dbg("Found intr_return()\n");
		regs = (काष्ठा pt_regs *)(info->sp - PT_SZ_ALGN);
		info->prev_sp = regs->gr[30];
		info->prev_ip = regs->iaoq[0];
		info->rp = regs->gr[2];
		वापस 1;
	पूर्ण

	अगर (pc == (अचिन्हित दीर्घ) &_चयन_to_ret) अणु
		info->prev_sp = info->sp - CALLEE_SAVE_FRAME_SIZE;
		info->prev_ip = *(अचिन्हित दीर्घ *)(info->prev_sp - RP_OFFSET);
		वापस 1;
	पूर्ण

#अगर_घोषित CONFIG_IRQSTACKS
	अगर (pc == (अचिन्हित दीर्घ) &_call_on_stack) अणु
		info->prev_sp = *(अचिन्हित दीर्घ *)(info->sp - FRAME_SIZE - REG_SZ);
		info->prev_ip = *(अचिन्हित दीर्घ *)(info->sp - FRAME_SIZE - RP_OFFSET);
		वापस 1;
	पूर्ण
#पूर्ण_अगर

	वापस 0;
पूर्ण

अटल व्योम unwind_frame_regs(काष्ठा unwind_frame_info *info)
अणु
	स्थिर काष्ठा unwind_table_entry *e;
	अचिन्हित दीर्घ npc;
	अचिन्हित पूर्णांक insn;
	दीर्घ frame_size = 0;
	पूर्णांक looking_क्रम_rp, rpoffset = 0;

	e = find_unwind_entry(info->ip);
	अगर (e == शून्य) अणु
		अचिन्हित दीर्घ sp;

		dbg("Cannot find unwind entry for %pS; forced unwinding\n",
			(व्योम *) info->ip);

		/* Since we are करोing the unwinding blind, we करोn't know अगर
		   we are adjusting the stack correctly or extracting the rp
		   correctly. The rp is checked to see अगर it beदीर्घs to the
		   kernel text section, अगर not we assume we करोn't have a 
		   correct stack frame and we जारी to unwind the stack.
		   This is not quite correct, and will fail क्रम loadable
		   modules. */
		sp = info->sp & ~63;
		करो अणु
			अचिन्हित दीर्घ पंचांगp;

			info->prev_sp = sp - 64;
			info->prev_ip = 0;

			/* The stack is at the end inside the thपढ़ो_जोड़
			 * काष्ठा. If we reach data, we have reached the
			 * beginning of the stack and should stop unwinding. */
			अगर (info->prev_sp >= (अचिन्हित दीर्घ) task_thपढ़ो_info(info->t) &&
			    info->prev_sp < ((अचिन्हित दीर्घ) task_thपढ़ो_info(info->t)
						+ THREAD_SZ_ALGN)) अणु
				info->prev_sp = 0;
				अवरोध;
			पूर्ण

			अगर (get_user(पंचांगp, (अचिन्हित दीर्घ *)(info->prev_sp - RP_OFFSET))) 
				अवरोध;
			info->prev_ip = पंचांगp;
			sp = info->prev_sp;
		पूर्ण जबतक (!kernel_text_address(info->prev_ip));

		info->rp = 0;

		dbg("analyzing func @ %lx with no unwind info, setting "
		    "prev_sp=%lx prev_ip=%lx\n", info->ip, 
		    info->prev_sp, info->prev_ip);
	पूर्ण अन्यथा अणु
		dbg("e->start = 0x%x, e->end = 0x%x, Save_SP = %d, "
		    "Save_RP = %d, Millicode = %d size = %u\n", 
		    e->region_start, e->region_end, e->Save_SP, e->Save_RP, 
		    e->Millicode, e->Total_frame_size);

		looking_क्रम_rp = e->Save_RP;

		क्रम (npc = e->region_start; 
		     (frame_size < (e->Total_frame_size << 3) || 
		      looking_क्रम_rp) && 
		     npc < info->ip; 
		     npc += 4) अणु

			insn = *(अचिन्हित पूर्णांक *)npc;

			अगर ((insn & 0xffffc001) == 0x37de0000 ||
			    (insn & 0xffe00001) == 0x6fc00000) अणु
				/* lकरो X(sp), sp, or stwm X,D(sp) */
				frame_size += (insn & 0x3fff) >> 1;
				dbg("analyzing func @ %lx, insn=%08x @ "
				    "%lx, frame_size = %ld\n", info->ip,
				    insn, npc, frame_size);
			पूर्ण अन्यथा अगर ((insn & 0xffe00009) == 0x73c00008) अणु
				/* std,ma X,D(sp) */
				frame_size += ((insn >> 4) & 0x3ff) << 3;
				dbg("analyzing func @ %lx, insn=%08x @ "
				    "%lx, frame_size = %ld\n", info->ip,
				    insn, npc, frame_size);
			पूर्ण अन्यथा अगर (insn == 0x6bc23fd9) अणु 
				/* stw rp,-20(sp) */
				rpoffset = 20;
				looking_क्रम_rp = 0;
				dbg("analyzing func @ %lx, insn=stw rp,"
				    "-20(sp) @ %lx\n", info->ip, npc);
			पूर्ण अन्यथा अगर (insn == 0x0fc212c1) अणु
				/* std rp,-16(sr0,sp) */
				rpoffset = 16;
				looking_क्रम_rp = 0;
				dbg("analyzing func @ %lx, insn=std rp,"
				    "-16(sp) @ %lx\n", info->ip, npc);
			पूर्ण
		पूर्ण

		अगर (frame_size > e->Total_frame_size << 3)
			frame_size = e->Total_frame_size << 3;

		अगर (!unwind_special(info, e->region_start, frame_size)) अणु
			info->prev_sp = info->sp - frame_size;
			अगर (e->Millicode)
				info->rp = info->r31;
			अन्यथा अगर (rpoffset)
				info->rp = *(अचिन्हित दीर्घ *)(info->prev_sp - rpoffset);
			info->prev_ip = info->rp;
			info->rp = 0;
		पूर्ण

		dbg("analyzing func @ %lx, setting prev_sp=%lx "
		    "prev_ip=%lx npc=%lx\n", info->ip, info->prev_sp, 
		    info->prev_ip, npc);
	पूर्ण
पूर्ण

व्योम unwind_frame_init(काष्ठा unwind_frame_info *info, काष्ठा task_काष्ठा *t, 
		       काष्ठा pt_regs *regs)
अणु
	स_रखो(info, 0, माप(काष्ठा unwind_frame_info));
	info->t = t;
	info->sp = regs->gr[30];
	info->ip = regs->iaoq[0];
	info->rp = regs->gr[2];
	info->r31 = regs->gr[31];

	dbg("(%d) Start unwind from sp=%08lx ip=%08lx\n", 
	    t ? (पूर्णांक)t->pid : -1, info->sp, info->ip);
पूर्ण

व्योम unwind_frame_init_from_blocked_task(काष्ठा unwind_frame_info *info, काष्ठा task_काष्ठा *t)
अणु
	काष्ठा pt_regs *r = &t->thपढ़ो.regs;
	काष्ठा pt_regs *r2;

	r2 = kदो_स्मृति(माप(काष्ठा pt_regs), GFP_ATOMIC);
	अगर (!r2)
		वापस;
	*r2 = *r;
	r2->gr[30] = r->ksp;
	r2->iaoq[0] = r->kpc;
	unwind_frame_init(info, t, r2);
	kमुक्त(r2);
पूर्ण

#घोषणा get_parisc_stackpoपूर्णांकer() (अणु \
	अचिन्हित दीर्घ sp; \
	__यंत्र__("copy %%r30, %0" : "=r"(sp)); \
	(sp); \
पूर्ण)

व्योम unwind_frame_init_task(काष्ठा unwind_frame_info *info,
	काष्ठा task_काष्ठा *task, काष्ठा pt_regs *regs)
अणु
	task = task ? task : current;

	अगर (task == current) अणु
		काष्ठा pt_regs r;

		अगर (!regs) अणु
			स_रखो(&r, 0, माप(r));
			r.iaoq[0] =  _THIS_IP_;
			r.gr[2] = _RET_IP_;
			r.gr[30] = get_parisc_stackpoपूर्णांकer();
			regs = &r;
		पूर्ण
		unwind_frame_init(info, task, regs);
	पूर्ण अन्यथा अणु
		unwind_frame_init_from_blocked_task(info, task);
	पूर्ण
पूर्ण

पूर्णांक unwind_once(काष्ठा unwind_frame_info *next_frame)
अणु
	unwind_frame_regs(next_frame);

	अगर (next_frame->prev_sp == 0 ||
	    next_frame->prev_ip == 0)
		वापस -1;

	next_frame->sp = next_frame->prev_sp;
	next_frame->ip = next_frame->prev_ip;
	next_frame->prev_sp = 0;
	next_frame->prev_ip = 0;

	dbg("(%d) Continue unwind to sp=%08lx ip=%08lx\n", 
	    next_frame->t ? (पूर्णांक)next_frame->t->pid : -1, 
	    next_frame->sp, next_frame->ip);

	वापस 0;
पूर्ण

पूर्णांक unwind_to_user(काष्ठा unwind_frame_info *info)
अणु
	पूर्णांक ret;
	
	करो अणु
		ret = unwind_once(info);
	पूर्ण जबतक (!ret && !(info->ip & 3));

	वापस ret;
पूर्ण

अचिन्हित दीर्घ वापस_address(अचिन्हित पूर्णांक level)
अणु
	काष्ठा unwind_frame_info info;

	/* initialize unwind info */
	unwind_frame_init_task(&info, current, शून्य);

	/* unwind stack */
	level += 2;
	करो अणु
		अगर (unwind_once(&info) < 0 || info.ip == 0)
			वापस 0;
		अगर (!kernel_text_address(info.ip))
			वापस 0;
	पूर्ण जबतक (info.ip && level--);

	वापस info.ip;
पूर्ण
