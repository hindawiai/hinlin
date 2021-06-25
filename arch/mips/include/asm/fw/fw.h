<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2012 MIPS Technologies, Inc.
 */
#अगर_अघोषित __ASM_FW_H_
#घोषणा __ASM_FW_H_

#समावेश <यंत्र/bootinfo.h>	/* For cleaner code... */

बाह्य पूर्णांक fw_argc;
बाह्य पूर्णांक *_fw_argv;
बाह्य पूर्णांक *_fw_envp;

/*
 * Most firmware like YAMON, PMON, etc. pass arguments and environment
 * variables as 32-bit poपूर्णांकers. These take care of sign extension.
 */
#घोषणा fw_argv(index)		((अक्षर *)(दीर्घ)_fw_argv[(index)])
#घोषणा fw_envp(index)		((अक्षर *)(दीर्घ)_fw_envp[(index)])

बाह्य व्योम fw_init_cmdline(व्योम);
बाह्य अक्षर *fw_अ_लोmdline(व्योम);
बाह्य व्योम fw_meminit(व्योम);
बाह्य अक्षर *fw_दो_पर्या(अक्षर *name);
बाह्य अचिन्हित दीर्घ fw_दो_पर्याl(अक्षर *name);
बाह्य व्योम fw_init_early_console(अक्षर port);

#पूर्ण_अगर /* __ASM_FW_H_ */
