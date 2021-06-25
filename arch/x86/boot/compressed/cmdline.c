<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश "misc.h"

अटल अचिन्हित दीर्घ fs;
अटल अंतरभूत व्योम set_fs(अचिन्हित दीर्घ seg)
अणु
	fs = seg << 4;  /* shअगरt it back */
पूर्ण
प्रकार अचिन्हित दीर्घ addr_t;
अटल अंतरभूत अक्षर rdfs8(addr_t addr)
अणु
	वापस *((अक्षर *)(fs + addr));
पूर्ण
#समावेश "../cmdline.c"
अचिन्हित दीर्घ get_cmd_line_ptr(व्योम)
अणु
	अचिन्हित दीर्घ cmd_line_ptr = boot_params->hdr.cmd_line_ptr;

	cmd_line_ptr |= (u64)boot_params->ext_cmd_line_ptr << 32;

	वापस cmd_line_ptr;
पूर्ण
पूर्णांक cmdline_find_option(स्थिर अक्षर *option, अक्षर *buffer, पूर्णांक bufsize)
अणु
	वापस __cmdline_find_option(get_cmd_line_ptr(), option, buffer, bufsize);
पूर्ण
पूर्णांक cmdline_find_option_bool(स्थिर अक्षर *option)
अणु
	वापस __cmdline_find_option_bool(get_cmd_line_ptr(), option);
पूर्ण
