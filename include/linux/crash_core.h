<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित LINUX_CRASH_CORE_H
#घोषणा LINUX_CRASH_CORE_H

#समावेश <linux/linkage.h>
#समावेश <linux/elfcore.h>
#समावेश <linux/elf.h>

#घोषणा CRASH_CORE_NOTE_NAME	   "CORE"
#घोषणा CRASH_CORE_NOTE_HEAD_BYTES ALIGN(माप(काष्ठा elf_note), 4)
#घोषणा CRASH_CORE_NOTE_NAME_BYTES ALIGN(माप(CRASH_CORE_NOTE_NAME), 4)
#घोषणा CRASH_CORE_NOTE_DESC_BYTES ALIGN(माप(काष्ठा elf_prstatus), 4)

/*
 * The per-cpu notes area is a list of notes terminated by a "NULL"
 * note header.  For kdump, the code in vmcore.c runs in the context
 * of the second kernel to combine them पूर्णांकo one note.
 */
#घोषणा CRASH_CORE_NOTE_BYTES	   ((CRASH_CORE_NOTE_HEAD_BYTES * 2) +	\
				     CRASH_CORE_NOTE_NAME_BYTES +	\
				     CRASH_CORE_NOTE_DESC_BYTES)

#घोषणा VMCOREINFO_BYTES	   PAGE_SIZE
#घोषणा VMCOREINFO_NOTE_NAME	   "VMCOREINFO"
#घोषणा VMCOREINFO_NOTE_NAME_BYTES ALIGN(माप(VMCOREINFO_NOTE_NAME), 4)
#घोषणा VMCOREINFO_NOTE_SIZE	   ((CRASH_CORE_NOTE_HEAD_BYTES * 2) +	\
				     VMCOREINFO_NOTE_NAME_BYTES +	\
				     VMCOREINFO_BYTES)

प्रकार u32 note_buf_t[CRASH_CORE_NOTE_BYTES/4];

व्योम crash_update_vmcoreinfo_safecopy(व्योम *ptr);
व्योम crash_save_vmcoreinfo(व्योम);
व्योम arch_crash_save_vmcoreinfo(व्योम);
__म_लिखो(1, 2)
व्योम vmcoreinfo_append_str(स्थिर अक्षर *fmt, ...);
phys_addr_t paddr_vmcoreinfo_note(व्योम);

#घोषणा VMCOREINFO_OSRELEASE(value) \
	vmcoreinfo_append_str("OSRELEASE=%s\n", value)
#घोषणा VMCOREINFO_BUILD_ID(value) \
	vmcoreinfo_append_str("BUILD-ID=%s\n", value)
#घोषणा VMCOREINFO_PAGESIZE(value) \
	vmcoreinfo_append_str("PAGESIZE=%ld\n", value)
#घोषणा VMCOREINFO_SYMBOL(name) \
	vmcoreinfo_append_str("SYMBOL(%s)=%lx\n", #name, (अचिन्हित दीर्घ)&name)
#घोषणा VMCOREINFO_SYMBOL_ARRAY(name) \
	vmcoreinfo_append_str("SYMBOL(%s)=%lx\n", #name, (अचिन्हित दीर्घ)name)
#घोषणा VMCOREINFO_SIZE(name) \
	vmcoreinfo_append_str("SIZE(%s)=%lu\n", #name, \
			      (अचिन्हित दीर्घ)माप(name))
#घोषणा VMCOREINFO_STRUCT_SIZE(name) \
	vmcoreinfo_append_str("SIZE(%s)=%lu\n", #name, \
			      (अचिन्हित दीर्घ)माप(काष्ठा name))
#घोषणा VMCOREINFO_OFFSET(name, field) \
	vmcoreinfo_append_str("OFFSET(%s.%s)=%lu\n", #name, #field, \
			      (अचिन्हित दीर्घ)दुरत्व(काष्ठा name, field))
#घोषणा VMCOREINFO_TYPE_OFFSET(name, field) \
	vmcoreinfo_append_str("OFFSET(%s.%s)=%lu\n", #name, #field, \
			      (अचिन्हित दीर्घ)दुरत्व(name, field))
#घोषणा VMCOREINFO_LENGTH(name, value) \
	vmcoreinfo_append_str("LENGTH(%s)=%lu\n", #name, (अचिन्हित दीर्घ)value)
#घोषणा VMCOREINFO_NUMBER(name) \
	vmcoreinfo_append_str("NUMBER(%s)=%ld\n", #name, (दीर्घ)name)
#घोषणा VMCOREINFO_CONFIG(name) \
	vmcoreinfo_append_str("CONFIG_%s=y\n", #name)

बाह्य अचिन्हित अक्षर *vmcoreinfo_data;
बाह्य माप_प्रकार vmcoreinfo_size;
बाह्य u32 *vmcoreinfo_note;

/* raw contents of kernel .notes section */
बाह्य स्थिर व्योम __start_notes __weak;
बाह्य स्थिर व्योम __stop_notes __weak;

Elf_Word *append_elf_note(Elf_Word *buf, अक्षर *name, अचिन्हित पूर्णांक type,
			  व्योम *data, माप_प्रकार data_len);
व्योम final_note(Elf_Word *buf);

पूर्णांक __init parse_crashkernel(अक्षर *cmdline, अचिन्हित दीर्घ दीर्घ प्रणाली_ram,
		अचिन्हित दीर्घ दीर्घ *crash_size, अचिन्हित दीर्घ दीर्घ *crash_base);
पूर्णांक parse_crashkernel_high(अक्षर *cmdline, अचिन्हित दीर्घ दीर्घ प्रणाली_ram,
		अचिन्हित दीर्घ दीर्घ *crash_size, अचिन्हित दीर्घ दीर्घ *crash_base);
पूर्णांक parse_crashkernel_low(अक्षर *cmdline, अचिन्हित दीर्घ दीर्घ प्रणाली_ram,
		अचिन्हित दीर्घ दीर्घ *crash_size, अचिन्हित दीर्घ दीर्घ *crash_base);

#पूर्ण_अगर /* LINUX_CRASH_CORE_H */
