<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/compiler.h>
#समावेश <elfutils/libdw.h>
#समावेश <elfutils/libdwfl.h>
#समावेश <पूर्णांकtypes.h>
#समावेश <त्रुटिसं.स>
#समावेश "debug.h"
#समावेश "dso.h"
#समावेश "unwind.h"
#समावेश "unwind-libdw.h"
#समावेश "machine.h"
#समावेश "map.h"
#समावेश "symbol.h"
#समावेश "thread.h"
#समावेश <linux/types.h>
#समावेश <linux/zभाग.स>
#समावेश "event.h"
#समावेश "perf_regs.h"
#समावेश "callchain.h"

अटल अक्षर *debuginfo_path;

अटल पूर्णांक __find_debuginfo(Dwfl_Module *mod __maybe_unused, व्योम **userdata,
			    स्थिर अक्षर *modname __maybe_unused, Dwarf_Addr base __maybe_unused,
			    स्थिर अक्षर *file_name, स्थिर अक्षर *debuglink_file __maybe_unused,
			    GElf_Word debuglink_crc __maybe_unused, अक्षर **debuginfo_file_name)
अणु
	स्थिर काष्ठा dso *dso = *userdata;

	निश्चित(dso);
	अगर (dso->symsrc_filename && म_भेद (file_name, dso->symsrc_filename))
		*debuginfo_file_name = strdup(dso->symsrc_filename);
	वापस -1;
पूर्ण

अटल स्थिर Dwfl_Callbacks offline_callbacks = अणु
	.find_debuginfo		= __find_debuginfo,
	.debuginfo_path		= &debuginfo_path,
	.section_address	= dwfl_offline_section_address,
	// .find_elf is not set as we use dwfl_report_elf() instead.
पूर्ण;

अटल पूर्णांक __report_module(काष्ठा addr_location *al, u64 ip,
			    काष्ठा unwind_info *ui)
अणु
	Dwfl_Module *mod;
	काष्ठा dso *dso = शून्य;
	/*
	 * Some callers will use al->sym, so we can't just use the
	 * cheaper thपढ़ो__find_map() here.
	 */
	thपढ़ो__find_symbol(ui->thपढ़ो, PERF_RECORD_MISC_USER, ip, al);

	अगर (al->map)
		dso = al->map->dso;

	अगर (!dso)
		वापस 0;

	mod = dwfl_addrmodule(ui->dwfl, ip);
	अगर (mod) अणु
		Dwarf_Addr s;

		dwfl_module_info(mod, शून्य, &s, शून्य, शून्य, शून्य, शून्य, शून्य);
		अगर (s != al->map->start - al->map->pgoff)
			mod = 0;
	पूर्ण

	अगर (!mod)
		mod = dwfl_report_elf(ui->dwfl, dso->लघु_name, dso->दीर्घ_name, -1,
				      al->map->start - al->map->pgoff, false);
	अगर (!mod) अणु
		अक्षर filename[PATH_MAX];

		अगर (dso__build_id_filename(dso, filename, माप(filename), false))
			mod = dwfl_report_elf(ui->dwfl, dso->लघु_name, filename, -1,
					      al->map->start - al->map->pgoff, false);
	पूर्ण

	अगर (mod) अणु
		व्योम **userdatap;

		dwfl_module_info(mod, &userdatap, शून्य, शून्य, शून्य, शून्य, शून्य, शून्य);
		*userdatap = dso;
	पूर्ण

	वापस mod && dwfl_addrmodule(ui->dwfl, ip) == mod ? 0 : -1;
पूर्ण

अटल पूर्णांक report_module(u64 ip, काष्ठा unwind_info *ui)
अणु
	काष्ठा addr_location al;

	वापस __report_module(&al, ip, ui);
पूर्ण

/*
 * Store all entries within entries array,
 * we will process it after we finish unwind.
 */
अटल पूर्णांक entry(u64 ip, काष्ठा unwind_info *ui)

अणु
	काष्ठा unwind_entry *e = &ui->entries[ui->idx++];
	काष्ठा addr_location al;

	अगर (__report_module(&al, ip, ui))
		वापस -1;

	e->ip	  = ip;
	e->ms.maps = al.maps;
	e->ms.map = al.map;
	e->ms.sym = al.sym;

	pr_debug("unwind: %s:ip = 0x%" PRIx64 " (0x%" PRIx64 ")\n",
		 al.sym ? al.sym->name : "''",
		 ip,
		 al.map ? al.map->map_ip(al.map, ip) : (u64) 0);
	वापस 0;
पूर्ण

अटल pid_t next_thपढ़ो(Dwfl *dwfl, व्योम *arg, व्योम **thपढ़ो_argp)
अणु
	/* We want only single thपढ़ो to be processed. */
	अगर (*thपढ़ो_argp != शून्य)
		वापस 0;

	*thपढ़ो_argp = arg;
	वापस dwfl_pid(dwfl);
पूर्ण

अटल पूर्णांक access_dso_mem(काष्ठा unwind_info *ui, Dwarf_Addr addr,
			  Dwarf_Word *data)
अणु
	काष्ठा addr_location al;
	sमाप_प्रकार size;

	अगर (!thपढ़ो__find_map(ui->thपढ़ो, PERF_RECORD_MISC_USER, addr, &al)) अणु
		pr_debug("unwind: no map for %lx\n", (अचिन्हित दीर्घ)addr);
		वापस -1;
	पूर्ण

	अगर (!al.map->dso)
		वापस -1;

	size = dso__data_पढ़ो_addr(al.map->dso, al.map, ui->machine,
				   addr, (u8 *) data, माप(*data));

	वापस !(size == माप(*data));
पूर्ण

अटल bool memory_पढ़ो(Dwfl *dwfl __maybe_unused, Dwarf_Addr addr, Dwarf_Word *result,
			व्योम *arg)
अणु
	काष्ठा unwind_info *ui = arg;
	काष्ठा stack_dump *stack = &ui->sample->user_stack;
	u64 start, end;
	पूर्णांक offset;
	पूर्णांक ret;

	ret = perf_reg_value(&start, &ui->sample->user_regs, PERF_REG_SP);
	अगर (ret)
		वापस false;

	end = start + stack->size;

	/* Check overflow. */
	अगर (addr + माप(Dwarf_Word) < addr)
		वापस false;

	अगर (addr < start || addr + माप(Dwarf_Word) > end) अणु
		ret = access_dso_mem(ui, addr, result);
		अगर (ret) अणु
			pr_debug("unwind: access_mem 0x%" PRIx64 " not inside range"
				 " 0x%" PRIx64 "-0x%" PRIx64 "\n",
				addr, start, end);
			वापस false;
		पूर्ण
		वापस true;
	पूर्ण

	offset  = addr - start;
	*result = *(Dwarf_Word *)&stack->data[offset];
	pr_debug("unwind: access_mem addr 0x%" PRIx64 ", val %lx, offset %d\n",
		 addr, (अचिन्हित दीर्घ)*result, offset);
	वापस true;
पूर्ण

अटल स्थिर Dwfl_Thपढ़ो_Callbacks callbacks = अणु
	.next_thपढ़ो		= next_thपढ़ो,
	.memory_पढ़ो		= memory_पढ़ो,
	.set_initial_रेजिस्टरs	= libdw__arch_set_initial_रेजिस्टरs,
पूर्ण;

अटल पूर्णांक
frame_callback(Dwfl_Frame *state, व्योम *arg)
अणु
	काष्ठा unwind_info *ui = arg;
	Dwarf_Addr pc;
	bool isactivation;

	अगर (!dwfl_frame_pc(state, &pc, शून्य)) अणु
		pr_err("%s", dwfl_errmsg(-1));
		वापस DWARF_CB_ABORT;
	पूर्ण

	// report the module beक्रमe we query क्रम isactivation
	report_module(pc, ui);

	अगर (!dwfl_frame_pc(state, &pc, &isactivation)) अणु
		pr_err("%s", dwfl_errmsg(-1));
		वापस DWARF_CB_ABORT;
	पूर्ण

	अगर (!isactivation)
		--pc;

	वापस entry(pc, ui) || !(--ui->max_stack) ?
	       DWARF_CB_ABORT : DWARF_CB_OK;
पूर्ण

पूर्णांक unwind__get_entries(unwind_entry_cb_t cb, व्योम *arg,
			काष्ठा thपढ़ो *thपढ़ो,
			काष्ठा perf_sample *data,
			पूर्णांक max_stack)
अणु
	काष्ठा unwind_info *ui, ui_buf = अणु
		.sample		= data,
		.thपढ़ो		= thपढ़ो,
		.machine	= thपढ़ो->maps->machine,
		.cb		= cb,
		.arg		= arg,
		.max_stack	= max_stack,
	पूर्ण;
	Dwarf_Word ip;
	पूर्णांक err = -EINVAL, i;

	अगर (!data->user_regs.regs)
		वापस -EINVAL;

	ui = zalloc(माप(ui_buf) + माप(ui_buf.entries[0]) * max_stack);
	अगर (!ui)
		वापस -ENOMEM;

	*ui = ui_buf;

	ui->dwfl = dwfl_begin(&offline_callbacks);
	अगर (!ui->dwfl)
		जाओ out;

	err = perf_reg_value(&ip, &data->user_regs, PERF_REG_IP);
	अगर (err)
		जाओ out;

	err = report_module(ip, ui);
	अगर (err)
		जाओ out;

	err = !dwfl_attach_state(ui->dwfl, EM_NONE, thपढ़ो->tid, &callbacks, ui);
	अगर (err)
		जाओ out;

	err = dwfl_getthपढ़ो_frames(ui->dwfl, thपढ़ो->tid, frame_callback, ui);

	अगर (err && ui->max_stack != max_stack)
		err = 0;

	/*
	 * Display what we got based on the order setup.
	 */
	क्रम (i = 0; i < ui->idx && !err; i++) अणु
		पूर्णांक j = i;

		अगर (callchain_param.order == ORDER_CALLER)
			j = ui->idx - i - 1;

		err = ui->entries[j].ip ? ui->cb(&ui->entries[j], ui->arg) : 0;
	पूर्ण

 out:
	अगर (err)
		pr_debug("unwind: failed with '%s'\n", dwfl_errmsg(-1));

	dwfl_end(ui->dwfl);
	मुक्त(ui);
	वापस 0;
पूर्ण
