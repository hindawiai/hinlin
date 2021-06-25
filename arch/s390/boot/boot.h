<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित BOOT_BOOT_H
#घोषणा BOOT_BOOT_H

#समावेश <linux/types.h>

#घोषणा BOOT_STACK_OFFSET 0x8000

#अगर_अघोषित __ASSEMBLY__

#समावेश <linux/compiler.h>

व्योम startup_kernel(व्योम);
अचिन्हित दीर्घ detect_memory(व्योम);
bool is_ipl_block_dump(व्योम);
व्योम store_ipl_parmblock(व्योम);
व्योम setup_boot_command_line(व्योम);
व्योम parse_boot_command_line(व्योम);
व्योम verअगरy_facilities(व्योम);
व्योम prपूर्णांक_missing_facilities(व्योम);
व्योम prपूर्णांक_pgm_check_info(व्योम);
अचिन्हित दीर्घ get_अक्रमom_base(अचिन्हित दीर्घ safe_addr);
व्योम __म_लिखो(1, 2) decompressor_prपूर्णांकk(स्थिर अक्षर *fmt, ...);

बाह्य स्थिर अक्षर kernel_version[];
बाह्य अचिन्हित दीर्घ memory_limit;
बाह्य पूर्णांक vदो_स्मृति_size_set;
बाह्य पूर्णांक kaslr_enabled;

अचिन्हित दीर्घ पढ़ो_ipl_report(अचिन्हित दीर्घ safe_offset);

#पूर्ण_अगर /* __ASSEMBLY__ */
#पूर्ण_अगर /* BOOT_BOOT_H */
