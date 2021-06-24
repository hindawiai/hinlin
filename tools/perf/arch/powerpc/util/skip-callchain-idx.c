<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Use DWARF Debug inक्रमmation to skip unnecessary callchain entries.
 *
 * Copyright (C) 2014 Sukadev Bhattiprolu, IBM Corporation.
 * Copyright (C) 2014 Ulrich Weigand, IBM Corporation.
 */
#समावेश <पूर्णांकtypes.h>
#समावेश <dwarf.h>
#समावेश <elfutils/libdwfl.h>

#समावेश "util/thread.h"
#समावेश "util/callchain.h"
#समावेश "util/debug.h"
#समावेश "util/dso.h"
#समावेश "util/event.h" // काष्ठा ip_callchain
#समावेश "util/map.h"
#समावेश "util/symbol.h"

/*
 * When saving the callchain on Power, the kernel conservatively saves
 * excess entries in the callchain. A few of these entries are needed
 * in some हालs but not others. If the unnecessary entries are not
 * ignored, we end up with duplicate arcs in the call-graphs. Use
 * DWARF debug inक्रमmation to skip over any unnecessary callchain
 * entries.
 *
 * See function header क्रम arch_adjust_callchain() below क्रम more details.
 *
 * The libdwfl code in this file is based on code from elfutils
 * (libdwfl/argp-std.c, libdwfl/tests/addrcfi.c, etc).
 */
अटल अक्षर *debuginfo_path;

अटल स्थिर Dwfl_Callbacks offline_callbacks = अणु
	.debuginfo_path = &debuginfo_path,
	.find_debuginfo = dwfl_standard_find_debuginfo,
	.section_address = dwfl_offline_section_address,
पूर्ण;


/*
 * Use the DWARF expression क्रम the Call-frame-address and determine
 * अगर वापस address is in LR and अगर a new frame was allocated.
 */
अटल पूर्णांक check_वापस_reg(पूर्णांक ra_regno, Dwarf_Frame *frame)
अणु
	Dwarf_Op ops_mem[2];
	Dwarf_Op dummy;
	Dwarf_Op *ops = &dummy;
	माप_प्रकार nops;
	पूर्णांक result;

	result = dwarf_frame_रेजिस्टर(frame, ra_regno, ops_mem, &ops, &nops);
	अगर (result < 0) अणु
		pr_debug("dwarf_frame_register() %s\n", dwarf_errmsg(-1));
		वापस -1;
	पूर्ण

	/*
	 * Check अगर वापस address is on the stack. If वापस address
	 * is in a रेजिस्टर (typically R0), it is yet to be saved on
	 * the stack.
	 */
	अगर ((nops != 0 || ops != शून्य) &&
		!(nops == 1 && ops[0].atom == DW_OP_regx &&
			ops[0].number2 == 0 && ops[0].offset == 0))
		वापस 0;

	/*
	 * Return address is in LR. Check अगर a frame was allocated
	 * but not-yet used.
	 */
	result = dwarf_frame_cfa(frame, &ops, &nops);
	अगर (result < 0) अणु
		pr_debug("dwarf_frame_cfa() returns %d, %s\n", result,
					dwarf_errmsg(-1));
		वापस -1;
	पूर्ण

	/*
	 * If call frame address is in r1, no new frame was allocated.
	 */
	अगर (nops == 1 && ops[0].atom == DW_OP_bregx && ops[0].number == 1 &&
				ops[0].number2 == 0)
		वापस 1;

	/*
	 * A new frame was allocated but has not yet been used.
	 */
	वापस 2;
पूर्ण

/*
 * Get the DWARF frame from the .eh_frame section.
 */
अटल Dwarf_Frame *get_eh_frame(Dwfl_Module *mod, Dwarf_Addr pc)
अणु
	पूर्णांक		result;
	Dwarf_Addr	bias;
	Dwarf_CFI	*cfi;
	Dwarf_Frame	*frame;

	cfi = dwfl_module_eh_cfi(mod, &bias);
	अगर (!cfi) अणु
		pr_debug("%s(): no CFI - %s\n", __func__, dwfl_errmsg(-1));
		वापस शून्य;
	पूर्ण

	result = dwarf_cfi_addrframe(cfi, pc-bias, &frame);
	अगर (result) अणु
		pr_debug("%s(): %s\n", __func__, dwfl_errmsg(-1));
		वापस शून्य;
	पूर्ण

	वापस frame;
पूर्ण

/*
 * Get the DWARF frame from the .debug_frame section.
 */
अटल Dwarf_Frame *get_dwarf_frame(Dwfl_Module *mod, Dwarf_Addr pc)
अणु
	Dwarf_CFI       *cfi;
	Dwarf_Addr      bias;
	Dwarf_Frame     *frame;
	पूर्णांक             result;

	cfi = dwfl_module_dwarf_cfi(mod, &bias);
	अगर (!cfi) अणु
		pr_debug("%s(): no CFI - %s\n", __func__, dwfl_errmsg(-1));
		वापस शून्य;
	पूर्ण

	result = dwarf_cfi_addrframe(cfi, pc-bias, &frame);
	अगर (result) अणु
		pr_debug("%s(): %s\n", __func__, dwfl_errmsg(-1));
		वापस शून्य;
	पूर्ण

	वापस frame;
पूर्ण

/*
 * Return:
 *	0 अगर वापस address क्रम the program counter @pc is on stack
 *	1 अगर वापस address is in LR and no new stack frame was allocated
 *	2 अगर वापस address is in LR and a new frame was allocated (but not
 *		yet used)
 *	-1 in हाल of errors
 */
अटल पूर्णांक check_वापस_addr(काष्ठा dso *dso, u64 map_start, Dwarf_Addr pc)
अणु
	पूर्णांक		rc = -1;
	Dwfl		*dwfl;
	Dwfl_Module	*mod;
	Dwarf_Frame	*frame;
	पूर्णांक		ra_regno;
	Dwarf_Addr	start = pc;
	Dwarf_Addr	end = pc;
	bool		संकेतp;
	स्थिर अक्षर	*exec_file = dso->दीर्घ_name;

	dwfl = dso->dwfl;

	अगर (!dwfl) अणु
		dwfl = dwfl_begin(&offline_callbacks);
		अगर (!dwfl) अणु
			pr_debug("dwfl_begin() failed: %s\n", dwarf_errmsg(-1));
			वापस -1;
		पूर्ण

		mod = dwfl_report_elf(dwfl, exec_file, exec_file, -1,
						map_start, false);
		अगर (!mod) अणु
			pr_debug("dwfl_report_elf() failed %s\n",
						dwarf_errmsg(-1));
			/*
			 * We normally cache the DWARF debug info and never
			 * call dwfl_end(). But to prevent fd leak, मुक्त in
			 * हाल of error.
			 */
			dwfl_end(dwfl);
			जाओ out;
		पूर्ण
		dso->dwfl = dwfl;
	पूर्ण

	mod = dwfl_addrmodule(dwfl, pc);
	अगर (!mod) अणु
		pr_debug("dwfl_addrmodule() failed, %s\n", dwarf_errmsg(-1));
		जाओ out;
	पूर्ण

	/*
	 * To work with split debug info files (eg: glibc), check both
	 * .eh_frame and .debug_frame sections of the ELF header.
	 */
	frame = get_eh_frame(mod, pc);
	अगर (!frame) अणु
		frame = get_dwarf_frame(mod, pc);
		अगर (!frame)
			जाओ out;
	पूर्ण

	ra_regno = dwarf_frame_info(frame, &start, &end, &संकेतp);
	अगर (ra_regno < 0) अणु
		pr_debug("Return address register unavailable: %s\n",
				dwarf_errmsg(-1));
		जाओ out;
	पूर्ण

	rc = check_वापस_reg(ra_regno, frame);

out:
	वापस rc;
पूर्ण

/*
 * The callchain saved by the kernel always includes the link रेजिस्टर (LR).
 *
 *	0:	PERF_CONTEXT_USER
 *	1:	Program counter (Next inकाष्ठाion poपूर्णांकer)
 *	2:	LR value
 *	3:	Caller's caller
 *	4:	...
 *
 * The value in LR is only needed when it holds a वापस address. If the
 * वापस address is on the stack, we should ignore the LR value.
 *
 * Further, when the वापस address is in the LR, अगर a new frame was just
 * allocated but the LR was not saved पूर्णांकo it, then the LR contains the
 * caller, slot 4: contains the caller's caller and the contents of slot 3:
 * (chain->ips[3]) is undefined and must be ignored.
 *
 * Use DWARF debug inक्रमmation to determine अगर any entries need to be skipped.
 *
 * Return:
 *	index:	of callchain entry that needs to be ignored (अगर any)
 *	-1	अगर no entry needs to be ignored or in हाल of errors
 */
पूर्णांक arch_skip_callchain_idx(काष्ठा thपढ़ो *thपढ़ो, काष्ठा ip_callchain *chain)
अणु
	काष्ठा addr_location al;
	काष्ठा dso *dso = शून्य;
	पूर्णांक rc;
	u64 ip;
	u64 skip_slot = -1;

	अगर (!chain || chain->nr < 3)
		वापस skip_slot;

	ip = chain->ips[1];

	thपढ़ो__find_symbol(thपढ़ो, PERF_RECORD_MISC_USER, ip, &al);

	अगर (al.map)
		dso = al.map->dso;

	अगर (!dso) अणु
		pr_debug("%" PRIx64 " dso is NULL\n", ip);
		वापस skip_slot;
	पूर्ण

	rc = check_वापस_addr(dso, al.map->start, ip);

	pr_debug("[DSO %s, sym %s, ip 0x%" PRIx64 "] rc %d\n",
				dso->दीर्घ_name, al.sym->name, ip, rc);

	अगर (rc == 0) अणु
		/*
		 * Return address on stack. Ignore LR value in callchain
		 */
		skip_slot = 2;
	पूर्ण अन्यथा अगर (rc == 2) अणु
		/*
		 * New frame allocated but वापस address still in LR.
		 * Ignore the caller's caller entry in callchain.
		 */
		skip_slot = 3;
	पूर्ण
	वापस skip_slot;
पूर्ण
