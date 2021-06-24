<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Post mortem Dwarf CFI based unwinding on top of regs and stack dumps.
 *
 * Lots of this code have been borrowed or heavily inspired from parts of
 * the libunwind 0.99 code which are (amongst other contributors I may have
 * क्रमgotten):
 *
 * Copyright (C) 2002-2007 Hewlett-Packard Co
 *	Contributed by David Mosberger-Tang <davidm@hpl.hp.com>
 *
 * And the bugs have been added by:
 *
 * Copyright (C) 2010, Frederic Weisbecker <fweisbec@gmail.com>
 * Copyright (C) 2012, Jiri Olsa <jolsa@redhat.com>
 *
 */

#समावेश <elf.h>
#समावेश <त्रुटिसं.स>
#समावेश <gelf.h>
#समावेश <fcntl.h>
#समावेश <पूर्णांकtypes.h>
#समावेश <माला.स>
#समावेश <unistd.h>
#समावेश <sys/mman.h>
#समावेश <linux/list.h>
#समावेश <linux/zभाग.स>
#अगर_अघोषित REMOTE_UNWIND_LIBUNWIND
#समावेश <libunwind.h>
#समावेश <libunwind-ptrace.h>
#पूर्ण_अगर
#समावेश "callchain.h"
#समावेश "thread.h"
#समावेश "session.h"
#समावेश "perf_regs.h"
#समावेश "unwind.h"
#समावेश "map.h"
#समावेश "symbol.h"
#समावेश "debug.h"
#समावेश "asm/bug.h"
#समावेश "dso.h"

बाह्य पूर्णांक
UNW_OBJ(dwarf_search_unwind_table) (unw_addr_space_t as,
				    unw_word_t ip,
				    unw_dyn_info_t *di,
				    unw_proc_info_t *pi,
				    पूर्णांक need_unwind_info, व्योम *arg);

#घोषणा dwarf_search_unwind_table UNW_OBJ(dwarf_search_unwind_table)

बाह्य पूर्णांक
UNW_OBJ(dwarf_find_debug_frame) (पूर्णांक found, unw_dyn_info_t *di_debug,
				 unw_word_t ip,
				 unw_word_t segbase,
				 स्थिर अक्षर *obj_name, unw_word_t start,
				 unw_word_t end);

#घोषणा dwarf_find_debug_frame UNW_OBJ(dwarf_find_debug_frame)

#घोषणा DW_EH_PE_FORMAT_MASK	0x0f	/* क्रमmat of the encoded value */
#घोषणा DW_EH_PE_APPL_MASK	0x70	/* how the value is to be applied */

/* Poपूर्णांकer-encoding क्रमmats: */
#घोषणा DW_EH_PE_omit		0xff
#घोषणा DW_EH_PE_ptr		0x00	/* poपूर्णांकer-sized अचिन्हित value */
#घोषणा DW_EH_PE_udata4		0x03	/* अचिन्हित 32-bit value */
#घोषणा DW_EH_PE_udata8		0x04	/* अचिन्हित 64-bit value */
#घोषणा DW_EH_PE_sdata4		0x0b	/* चिन्हित 32-bit value */
#घोषणा DW_EH_PE_sdata8		0x0c	/* चिन्हित 64-bit value */

/* Poपूर्णांकer-encoding application: */
#घोषणा DW_EH_PE_असलptr		0x00	/* असलolute value */
#घोषणा DW_EH_PE_pcrel		0x10	/* rel. to addr. of encoded value */

/*
 * The following are not करोcumented by LSB v1.3, yet they are used by
 * GCC, presumably they aren't documented by LSB since they aren't
 * used on Linux:
 */
#घोषणा DW_EH_PE_funcrel	0x40	/* start-of-procedure-relative */
#घोषणा DW_EH_PE_aligned	0x50	/* aligned poपूर्णांकer */

/* Flags पूर्णांकentionally not handled, since they're not needed:
 * #घोषणा DW_EH_PE_indirect      0x80
 * #घोषणा DW_EH_PE_uleb128       0x01
 * #घोषणा DW_EH_PE_udata2        0x02
 * #घोषणा DW_EH_PE_sleb128       0x09
 * #घोषणा DW_EH_PE_sdata2        0x0a
 * #घोषणा DW_EH_PE_textrel       0x20
 * #घोषणा DW_EH_PE_datarel       0x30
 */

काष्ठा unwind_info अणु
	काष्ठा perf_sample	*sample;
	काष्ठा machine		*machine;
	काष्ठा thपढ़ो		*thपढ़ो;
पूर्ण;

#घोषणा dw_पढ़ो(ptr, type, end) (अणु	\
	type *__p = (type *) ptr;	\
	type  __v;			\
	अगर ((__p + 1) > (type *) end)	\
		वापस -EINVAL;		\
	__v = *__p++;			\
	ptr = (typeof(ptr)) __p;	\
	__v;				\
	पूर्ण)

अटल पूर्णांक __dw_पढ़ो_encoded_value(u8 **p, u8 *end, u64 *val,
				   u8 encoding)
अणु
	u8 *cur = *p;
	*val = 0;

	चयन (encoding) अणु
	हाल DW_EH_PE_omit:
		*val = 0;
		जाओ out;
	हाल DW_EH_PE_ptr:
		*val = dw_पढ़ो(cur, अचिन्हित दीर्घ, end);
		जाओ out;
	शेष:
		अवरोध;
	पूर्ण

	चयन (encoding & DW_EH_PE_APPL_MASK) अणु
	हाल DW_EH_PE_असलptr:
		अवरोध;
	हाल DW_EH_PE_pcrel:
		*val = (अचिन्हित दीर्घ) cur;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर ((encoding & 0x07) == 0x00)
		encoding |= DW_EH_PE_udata4;

	चयन (encoding & DW_EH_PE_FORMAT_MASK) अणु
	हाल DW_EH_PE_sdata4:
		*val += dw_पढ़ो(cur, s32, end);
		अवरोध;
	हाल DW_EH_PE_udata4:
		*val += dw_पढ़ो(cur, u32, end);
		अवरोध;
	हाल DW_EH_PE_sdata8:
		*val += dw_पढ़ो(cur, s64, end);
		अवरोध;
	हाल DW_EH_PE_udata8:
		*val += dw_पढ़ो(cur, u64, end);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

 out:
	*p = cur;
	वापस 0;
पूर्ण

#घोषणा dw_पढ़ो_encoded_value(ptr, end, enc) (अणु			\
	u64 __v;						\
	अगर (__dw_पढ़ो_encoded_value(&ptr, end, &__v, enc)) अणु	\
		वापस -EINVAL;                                 \
	पूर्ण                                                       \
	__v;                                                    \
	पूर्ण)

अटल u64 elf_section_offset(पूर्णांक fd, स्थिर अक्षर *name)
अणु
	Elf *elf;
	GElf_Ehdr ehdr;
	GElf_Shdr shdr;
	u64 offset = 0;

	elf = elf_begin(fd, PERF_ELF_C_READ_MMAP, शून्य);
	अगर (elf == शून्य)
		वापस 0;

	करो अणु
		अगर (gelf_getehdr(elf, &ehdr) == शून्य)
			अवरोध;

		अगर (!elf_section_by_name(elf, &ehdr, &shdr, name, शून्य))
			अवरोध;

		offset = shdr.sh_offset;
	पूर्ण जबतक (0);

	elf_end(elf);
	वापस offset;
पूर्ण

#अगर_अघोषित NO_LIBUNWIND_DEBUG_FRAME
अटल पूर्णांक elf_is_exec(पूर्णांक fd, स्थिर अक्षर *name)
अणु
	Elf *elf;
	GElf_Ehdr ehdr;
	पूर्णांक retval = 0;

	elf = elf_begin(fd, PERF_ELF_C_READ_MMAP, शून्य);
	अगर (elf == शून्य)
		वापस 0;
	अगर (gelf_getehdr(elf, &ehdr) == शून्य)
		जाओ out;

	retval = (ehdr.e_type == ET_EXEC);

out:
	elf_end(elf);
	pr_debug("unwind: elf_is_exec(%s): %d\n", name, retval);
	वापस retval;
पूर्ण
#पूर्ण_अगर

काष्ठा table_entry अणु
	u32 start_ip_offset;
	u32 fde_offset;
पूर्ण;

काष्ठा eh_frame_hdr अणु
	अचिन्हित अक्षर version;
	अचिन्हित अक्षर eh_frame_ptr_enc;
	अचिन्हित अक्षर fde_count_enc;
	अचिन्हित अक्षर table_enc;

	/*
	 * The rest of the header is variable-length and consists of the
	 * following members:
	 *
	 *	encoded_t eh_frame_ptr;
	 *	encoded_t fde_count;
	 */

	/* A single encoded poपूर्णांकer should not be more than 8 bytes. */
	u64 enc[2];

	/*
	 * काष्ठा अणु
	 *    encoded_t start_ip;
	 *    encoded_t fde_addr;
	 * पूर्ण binary_search_table[fde_count];
	 */
	अक्षर data[];
पूर्ण __packed;

अटल पूर्णांक unwind_spec_ehframe(काष्ठा dso *dso, काष्ठा machine *machine,
			       u64 offset, u64 *table_data, u64 *segbase,
			       u64 *fde_count)
अणु
	काष्ठा eh_frame_hdr hdr;
	u8 *enc = (u8 *) &hdr.enc;
	u8 *end = (u8 *) &hdr.data;
	sमाप_प्रकार r;

	r = dso__data_पढ़ो_offset(dso, machine, offset,
				  (u8 *) &hdr, माप(hdr));
	अगर (r != माप(hdr))
		वापस -EINVAL;

	/* We करोnt need eh_frame_ptr, just skip it. */
	dw_पढ़ो_encoded_value(enc, end, hdr.eh_frame_ptr_enc);

	*fde_count  = dw_पढ़ो_encoded_value(enc, end, hdr.fde_count_enc);
	*segbase    = offset;
	*table_data = (enc - (u8 *) &hdr) + offset;
	वापस 0;
पूर्ण

अटल पूर्णांक पढ़ो_unwind_spec_eh_frame(काष्ठा dso *dso, काष्ठा machine *machine,
				     u64 *table_data, u64 *segbase,
				     u64 *fde_count)
अणु
	पूर्णांक ret = -EINVAL, fd;
	u64 offset = dso->data.eh_frame_hdr_offset;

	अगर (offset == 0) अणु
		fd = dso__data_get_fd(dso, machine);
		अगर (fd < 0)
			वापस -EINVAL;

		/* Check the .eh_frame section क्रम unwinding info */
		offset = elf_section_offset(fd, ".eh_frame_hdr");
		dso->data.eh_frame_hdr_offset = offset;
		dso__data_put_fd(dso);
	पूर्ण

	अगर (offset)
		ret = unwind_spec_ehframe(dso, machine, offset,
					  table_data, segbase,
					  fde_count);

	वापस ret;
पूर्ण

#अगर_अघोषित NO_LIBUNWIND_DEBUG_FRAME
अटल पूर्णांक पढ़ो_unwind_spec_debug_frame(काष्ठा dso *dso,
					काष्ठा machine *machine, u64 *offset)
अणु
	पूर्णांक fd;
	u64 ofs = dso->data.debug_frame_offset;

	/* debug_frame can reside in:
	 *  - dso
	 *  - debug poपूर्णांकed by symsrc_filename
	 *  - gnu_debuglink, which करोesn't necessary
	 *    has to be poपूर्णांकed by symsrc_filename
	 */
	अगर (ofs == 0) अणु
		fd = dso__data_get_fd(dso, machine);
		अगर (fd >= 0) अणु
			ofs = elf_section_offset(fd, ".debug_frame");
			dso__data_put_fd(dso);
		पूर्ण

		अगर (ofs <= 0) अणु
			fd = खोलो(dso->symsrc_filename, O_RDONLY);
			अगर (fd >= 0) अणु
				ofs = elf_section_offset(fd, ".debug_frame");
				बंद(fd);
			पूर्ण
		पूर्ण

		अगर (ofs <= 0) अणु
			अक्षर *debuglink = दो_स्मृति(PATH_MAX);
			पूर्णांक ret = 0;

			ret = dso__पढ़ो_binary_type_filename(
				dso, DSO_BINARY_TYPE__DEBUGLINK,
				machine->root_dir, debuglink, PATH_MAX);
			अगर (!ret) अणु
				fd = खोलो(debuglink, O_RDONLY);
				अगर (fd >= 0) अणु
					ofs = elf_section_offset(fd,
							".debug_frame");
					बंद(fd);
				पूर्ण
			पूर्ण
			अगर (ofs > 0) अणु
				अगर (dso->symsrc_filename != शून्य) अणु
					pr_warning(
						"%s: overwrite symsrc(%s,%s)\n",
							__func__,
							dso->symsrc_filename,
							debuglink);
					zमुक्त(&dso->symsrc_filename);
				पूर्ण
				dso->symsrc_filename = debuglink;
			पूर्ण अन्यथा अणु
				मुक्त(debuglink);
			पूर्ण
		पूर्ण

		dso->data.debug_frame_offset = ofs;
	पूर्ण

	*offset = ofs;
	अगर (*offset)
		वापस 0;

	वापस -EINVAL;
पूर्ण
#पूर्ण_अगर

अटल काष्ठा map *find_map(unw_word_t ip, काष्ठा unwind_info *ui)
अणु
	काष्ठा addr_location al;
	वापस thपढ़ो__find_map(ui->thपढ़ो, PERF_RECORD_MISC_USER, ip, &al);
पूर्ण

अटल पूर्णांक
find_proc_info(unw_addr_space_t as, unw_word_t ip, unw_proc_info_t *pi,
	       पूर्णांक need_unwind_info, व्योम *arg)
अणु
	काष्ठा unwind_info *ui = arg;
	काष्ठा map *map;
	unw_dyn_info_t di;
	u64 table_data, segbase, fde_count;
	पूर्णांक ret = -EINVAL;

	map = find_map(ip, ui);
	अगर (!map || !map->dso)
		वापस -EINVAL;

	pr_debug("unwind: find_proc_info dso %s\n", map->dso->name);

	/* Check the .eh_frame section क्रम unwinding info */
	अगर (!पढ़ो_unwind_spec_eh_frame(map->dso, ui->machine,
				       &table_data, &segbase, &fde_count)) अणु
		स_रखो(&di, 0, माप(di));
		di.क्रमmat   = UNW_INFO_FORMAT_REMOTE_TABLE;
		di.start_ip = map->start;
		di.end_ip   = map->end;
		di.u.rti.segbase    = map->start + segbase - map->pgoff;
		di.u.rti.table_data = map->start + table_data - map->pgoff;
		di.u.rti.table_len  = fde_count * माप(काष्ठा table_entry)
				      / माप(unw_word_t);
		ret = dwarf_search_unwind_table(as, ip, &di, pi,
						need_unwind_info, arg);
	पूर्ण

#अगर_अघोषित NO_LIBUNWIND_DEBUG_FRAME
	/* Check the .debug_frame section क्रम unwinding info */
	अगर (ret < 0 &&
	    !पढ़ो_unwind_spec_debug_frame(map->dso, ui->machine, &segbase)) अणु
		पूर्णांक fd = dso__data_get_fd(map->dso, ui->machine);
		पूर्णांक is_exec = elf_is_exec(fd, map->dso->name);
		unw_word_t base = is_exec ? 0 : map->start;
		स्थिर अक्षर *symfile;

		अगर (fd >= 0)
			dso__data_put_fd(map->dso);

		symfile = map->dso->symsrc_filename ?: map->dso->name;

		स_रखो(&di, 0, माप(di));
		अगर (dwarf_find_debug_frame(0, &di, ip, base, symfile,
					   map->start, map->end))
			वापस dwarf_search_unwind_table(as, ip, &di, pi,
							 need_unwind_info, arg);
	पूर्ण
#पूर्ण_अगर

	वापस ret;
पूर्ण

अटल पूर्णांक access_fpreg(unw_addr_space_t __maybe_unused as,
			unw_regnum_t __maybe_unused num,
			unw_fpreg_t __maybe_unused *val,
			पूर्णांक __maybe_unused __ग_लिखो,
			व्योम __maybe_unused *arg)
अणु
	pr_err("unwind: access_fpreg unsupported\n");
	वापस -UNW_EINVAL;
पूर्ण

अटल पूर्णांक get_dyn_info_list_addr(unw_addr_space_t __maybe_unused as,
				  unw_word_t __maybe_unused *dil_addr,
				  व्योम __maybe_unused *arg)
अणु
	वापस -UNW_ENOINFO;
पूर्ण

अटल पूर्णांक resume(unw_addr_space_t __maybe_unused as,
		  unw_cursor_t __maybe_unused *cu,
		  व्योम __maybe_unused *arg)
अणु
	pr_err("unwind: resume unsupported\n");
	वापस -UNW_EINVAL;
पूर्ण

अटल पूर्णांक
get_proc_name(unw_addr_space_t __maybe_unused as,
	      unw_word_t __maybe_unused addr,
		अक्षर __maybe_unused *bufp, माप_प्रकार __maybe_unused buf_len,
		unw_word_t __maybe_unused *offp, व्योम __maybe_unused *arg)
अणु
	pr_err("unwind: get_proc_name unsupported\n");
	वापस -UNW_EINVAL;
पूर्ण

अटल पूर्णांक access_dso_mem(काष्ठा unwind_info *ui, unw_word_t addr,
			  unw_word_t *data)
अणु
	काष्ठा map *map;
	sमाप_प्रकार size;

	map = find_map(addr, ui);
	अगर (!map) अणु
		pr_debug("unwind: no map for %lx\n", (अचिन्हित दीर्घ)addr);
		वापस -1;
	पूर्ण

	अगर (!map->dso)
		वापस -1;

	size = dso__data_पढ़ो_addr(map->dso, map, ui->machine,
				   addr, (u8 *) data, माप(*data));

	वापस !(size == माप(*data));
पूर्ण

अटल पूर्णांक access_mem(unw_addr_space_t __maybe_unused as,
		      unw_word_t addr, unw_word_t *valp,
		      पूर्णांक __ग_लिखो, व्योम *arg)
अणु
	काष्ठा unwind_info *ui = arg;
	काष्ठा stack_dump *stack = &ui->sample->user_stack;
	u64 start, end;
	पूर्णांक offset;
	पूर्णांक ret;

	/* Don't support ग_लिखो, probably not needed. */
	अगर (__ग_लिखो || !stack || !ui->sample->user_regs.regs) अणु
		*valp = 0;
		वापस 0;
	पूर्ण

	ret = perf_reg_value(&start, &ui->sample->user_regs,
			     LIBUNWIND__ARCH_REG_SP);
	अगर (ret)
		वापस ret;

	end = start + stack->size;

	/* Check overflow. */
	अगर (addr + माप(unw_word_t) < addr)
		वापस -EINVAL;

	अगर (addr < start || addr + माप(unw_word_t) >= end) अणु
		ret = access_dso_mem(ui, addr, valp);
		अगर (ret) अणु
			pr_debug("unwind: access_mem %p not inside range"
				 " 0x%" PRIx64 "-0x%" PRIx64 "\n",
				 (व्योम *) (uपूर्णांकptr_t) addr, start, end);
			*valp = 0;
			वापस ret;
		पूर्ण
		वापस 0;
	पूर्ण

	offset = addr - start;
	*valp  = *(unw_word_t *)&stack->data[offset];
	pr_debug("unwind: access_mem addr %p val %lx, offset %d\n",
		 (व्योम *) (uपूर्णांकptr_t) addr, (अचिन्हित दीर्घ)*valp, offset);
	वापस 0;
पूर्ण

अटल पूर्णांक access_reg(unw_addr_space_t __maybe_unused as,
		      unw_regnum_t regnum, unw_word_t *valp,
		      पूर्णांक __ग_लिखो, व्योम *arg)
अणु
	काष्ठा unwind_info *ui = arg;
	पूर्णांक id, ret;
	u64 val;

	/* Don't support write, I suspect we don't need it. */
	अगर (__ग_लिखो) अणु
		pr_err("unwind: access_reg w %d\n", regnum);
		वापस 0;
	पूर्ण

	अगर (!ui->sample->user_regs.regs) अणु
		*valp = 0;
		वापस 0;
	पूर्ण

	id = LIBUNWIND__ARCH_REG_ID(regnum);
	अगर (id < 0)
		वापस -EINVAL;

	ret = perf_reg_value(&val, &ui->sample->user_regs, id);
	अगर (ret) अणु
		pr_err("unwind: can't read reg %d\n", regnum);
		वापस ret;
	पूर्ण

	*valp = (unw_word_t) val;
	pr_debug("unwind: reg %d, val %lx\n", regnum, (अचिन्हित दीर्घ)*valp);
	वापस 0;
पूर्ण

अटल व्योम put_unwind_info(unw_addr_space_t __maybe_unused as,
			    unw_proc_info_t *pi __maybe_unused,
			    व्योम *arg __maybe_unused)
अणु
	pr_debug("unwind: put_unwind_info called\n");
पूर्ण

अटल पूर्णांक entry(u64 ip, काष्ठा thपढ़ो *thपढ़ो,
		 unwind_entry_cb_t cb, व्योम *arg)
अणु
	काष्ठा unwind_entry e;
	काष्ठा addr_location al;

	e.ms.sym = thपढ़ो__find_symbol(thपढ़ो, PERF_RECORD_MISC_USER, ip, &al);
	e.ip     = ip;
	e.ms.map = al.map;
	e.ms.maps = al.maps;

	pr_debug("unwind: %s:ip = 0x%" PRIx64 " (0x%" PRIx64 ")\n",
		 al.sym ? al.sym->name : "''",
		 ip,
		 al.map ? al.map->map_ip(al.map, ip) : (u64) 0);

	वापस cb(&e, arg);
पूर्ण

अटल व्योम display_error(पूर्णांक err)
अणु
	चयन (err) अणु
	हाल UNW_EINVAL:
		pr_err("unwind: Only supports local.\n");
		अवरोध;
	हाल UNW_EUNSPEC:
		pr_err("unwind: Unspecified error.\n");
		अवरोध;
	हाल UNW_EBADREG:
		pr_err("unwind: Register unavailable.\n");
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल unw_accessors_t accessors = अणु
	.find_proc_info		= find_proc_info,
	.put_unwind_info	= put_unwind_info,
	.get_dyn_info_list_addr	= get_dyn_info_list_addr,
	.access_mem		= access_mem,
	.access_reg		= access_reg,
	.access_fpreg		= access_fpreg,
	.resume			= resume,
	.get_proc_name		= get_proc_name,
पूर्ण;

अटल पूर्णांक _unwind__prepare_access(काष्ठा maps *maps)
अणु
	maps->addr_space = unw_create_addr_space(&accessors, 0);
	अगर (!maps->addr_space) अणु
		pr_err("unwind: Can't create unwind address space.\n");
		वापस -ENOMEM;
	पूर्ण

	unw_set_caching_policy(maps->addr_space, UNW_CACHE_GLOBAL);
	वापस 0;
पूर्ण

अटल व्योम _unwind__flush_access(काष्ठा maps *maps)
अणु
	unw_flush_cache(maps->addr_space, 0, 0);
पूर्ण

अटल व्योम _unwind__finish_access(काष्ठा maps *maps)
अणु
	unw_destroy_addr_space(maps->addr_space);
पूर्ण

अटल पूर्णांक get_entries(काष्ठा unwind_info *ui, unwind_entry_cb_t cb,
		       व्योम *arg, पूर्णांक max_stack)
अणु
	u64 val;
	unw_word_t ips[max_stack];
	unw_addr_space_t addr_space;
	unw_cursor_t c;
	पूर्णांक ret, i = 0;

	ret = perf_reg_value(&val, &ui->sample->user_regs,
			     LIBUNWIND__ARCH_REG_IP);
	अगर (ret)
		वापस ret;

	ips[i++] = (unw_word_t) val;

	/*
	 * If we need more than one entry, करो the DWARF
	 * unwind itself.
	 */
	अगर (max_stack - 1 > 0) अणु
		WARN_ONCE(!ui->thपढ़ो, "WARNING: ui->thread is NULL");
		addr_space = ui->thपढ़ो->maps->addr_space;

		अगर (addr_space == शून्य)
			वापस -1;

		ret = unw_init_remote(&c, addr_space, ui);
		अगर (ret)
			display_error(ret);

		जबतक (!ret && (unw_step(&c) > 0) && i < max_stack) अणु
			unw_get_reg(&c, UNW_REG_IP, &ips[i]);

			/*
			 * Decrement the IP क्रम any non-activation frames.
			 * this is required to properly find the srcline
			 * क्रम caller frames.
			 * See also the करोcumentation क्रम dwfl_frame_pc(),
			 * which this code tries to replicate.
			 */
			अगर (unw_is_संकेत_frame(&c) <= 0)
				--ips[i];

			++i;
		पूर्ण

		max_stack = i;
	पूर्ण

	/*
	 * Display what we got based on the order setup.
	 */
	क्रम (i = 0; i < max_stack && !ret; i++) अणु
		पूर्णांक j = i;

		अगर (callchain_param.order == ORDER_CALLER)
			j = max_stack - i - 1;
		ret = ips[j] ? entry(ips[j], ui->thपढ़ो, cb, arg) : 0;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक _unwind__get_entries(unwind_entry_cb_t cb, व्योम *arg,
			काष्ठा thपढ़ो *thपढ़ो,
			काष्ठा perf_sample *data, पूर्णांक max_stack)
अणु
	काष्ठा unwind_info ui = अणु
		.sample       = data,
		.thपढ़ो       = thपढ़ो,
		.machine      = thपढ़ो->maps->machine,
	पूर्ण;

	अगर (!data->user_regs.regs)
		वापस -EINVAL;

	अगर (max_stack <= 0)
		वापस -EINVAL;

	वापस get_entries(&ui, cb, arg, max_stack);
पूर्ण

अटल काष्ठा unwind_libunwind_ops
_unwind_libunwind_ops = अणु
	.prepare_access = _unwind__prepare_access,
	.flush_access   = _unwind__flush_access,
	.finish_access  = _unwind__finish_access,
	.get_entries    = _unwind__get_entries,
पूर्ण;

#अगर_अघोषित REMOTE_UNWIND_LIBUNWIND
काष्ठा unwind_libunwind_ops *
local_unwind_libunwind_ops = &_unwind_libunwind_ops;
#पूर्ण_अगर
