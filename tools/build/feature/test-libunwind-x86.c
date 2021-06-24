<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <libunwind-x86.h>
#समावेश <मानककोष.स>

बाह्य पूर्णांक UNW_OBJ(dwarf_search_unwind_table) (unw_addr_space_t as,
					       unw_word_t ip,
					       unw_dyn_info_t *di,
					       unw_proc_info_t *pi,
					       पूर्णांक need_unwind_info, व्योम *arg);


#घोषणा dwarf_search_unwind_table UNW_OBJ(dwarf_search_unwind_table)

अटल unw_accessors_t accessors;

पूर्णांक मुख्य(व्योम)
अणु
	unw_addr_space_t addr_space;

	addr_space = unw_create_addr_space(&accessors, 0);
	अगर (addr_space)
		वापस 0;

	unw_init_remote(शून्य, addr_space, शून्य);
	dwarf_search_unwind_table(addr_space, 0, शून्य, शून्य, 0, शून्य);

	वापस 0;
पूर्ण
