<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2007-2010, 2011-2012 Synopsys, Inc. (www.synopsys.com)
 * Copyright (C) 2002-2006 Novell, Inc.
 *	Jan Beulich <jbeulich@novell.com>
 *
 * A simple API क्रम unwinding kernel stacks.  This is used क्रम
 * debugging and error reporting purposes.  The kernel करोesn't need
 * full-blown stack unwinding with all the bells and whistles, so there
 * is not much poपूर्णांक in implementing the full Dwarf2 unwind API.
 */

#समावेश <linux/sched.h>
#समावेश <linux/module.h>
#समावेश <linux/memblock.h>
#समावेश <linux/sort.h>
#समावेश <linux/slab.h>
#समावेश <linux/stop_machine.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/ptrace.h>
#समावेश <यंत्र/sections.h>
#समावेश <यंत्र/unaligned.h>
#समावेश <यंत्र/unwind.h>

बाह्य अक्षर __start_unwind[], __end_unwind[];
/* बाह्य स्थिर u8 __start_unwind_hdr[], __end_unwind_hdr[];*/

/* #घोषणा UNWIND_DEBUG */

#अगर_घोषित UNWIND_DEBUG
पूर्णांक dbg_unw;
#घोषणा unw_debug(fmt, ...)			\
करो अणु						\
	अगर (dbg_unw)				\
		pr_info(fmt, ##__VA_ARGS__);	\
पूर्ण जबतक (0);
#अन्यथा
#घोषणा unw_debug(fmt, ...)
#पूर्ण_अगर

#घोषणा MAX_STACK_DEPTH 8

#घोषणा EXTRA_INFO(f) अणु \
		BUILD_BUG_ON_ZERO(दुरत्व(काष्ठा unwind_frame_info, f) \
				% माप_field(काष्ठा unwind_frame_info, f)) \
				+ दुरत्व(काष्ठा unwind_frame_info, f) \
				/ माप_field(काष्ठा unwind_frame_info, f), \
				माप_field(काष्ठा unwind_frame_info, f) \
	पूर्ण
#घोषणा PTREGS_INFO(f) EXTRA_INFO(regs.f)

अटल स्थिर काष्ठा अणु
	अचिन्हित offs:BITS_PER_LONG / 2;
	अचिन्हित width:BITS_PER_LONG / 2;
पूर्ण reg_info[] = अणु
UNW_REGISTER_INFOपूर्ण;

#अघोषित PTREGS_INFO
#अघोषित EXTRA_INFO

#अगर_अघोषित REG_INVALID
#घोषणा REG_INVALID(r) (reg_info[r].width == 0)
#पूर्ण_अगर

#घोषणा DW_CFA_nop                          0x00
#घोषणा DW_CFA_set_loc                      0x01
#घोषणा DW_CFA_advance_loc1                 0x02
#घोषणा DW_CFA_advance_loc2                 0x03
#घोषणा DW_CFA_advance_loc4                 0x04
#घोषणा DW_CFA_offset_extended              0x05
#घोषणा DW_CFA_restore_extended             0x06
#घोषणा DW_CFA_undefined                    0x07
#घोषणा DW_CFA_same_value                   0x08
#घोषणा DW_CFA_रेजिस्टर                     0x09
#घोषणा DW_CFA_remember_state               0x0a
#घोषणा DW_CFA_restore_state                0x0b
#घोषणा DW_CFA_def_cfa                      0x0c
#घोषणा DW_CFA_def_cfa_रेजिस्टर             0x0d
#घोषणा DW_CFA_def_cfa_offset               0x0e
#घोषणा DW_CFA_def_cfa_expression           0x0f
#घोषणा DW_CFA_expression                   0x10
#घोषणा DW_CFA_offset_extended_sf           0x11
#घोषणा DW_CFA_def_cfa_sf                   0x12
#घोषणा DW_CFA_def_cfa_offset_sf            0x13
#घोषणा DW_CFA_val_offset                   0x14
#घोषणा DW_CFA_val_offset_sf                0x15
#घोषणा DW_CFA_val_expression               0x16
#घोषणा DW_CFA_lo_user                      0x1c
#घोषणा DW_CFA_GNU_winकरोw_save              0x2d
#घोषणा DW_CFA_GNU_args_size                0x2e
#घोषणा DW_CFA_GNU_negative_offset_extended 0x2f
#घोषणा DW_CFA_hi_user                      0x3f

#घोषणा DW_EH_PE_FORM     0x07
#घोषणा DW_EH_PE_native   0x00
#घोषणा DW_EH_PE_leb128   0x01
#घोषणा DW_EH_PE_data2    0x02
#घोषणा DW_EH_PE_data4    0x03
#घोषणा DW_EH_PE_data8    0x04
#घोषणा DW_EH_PE_चिन्हित   0x08
#घोषणा DW_EH_PE_ADJUST   0x70
#घोषणा DW_EH_PE_असल      0x00
#घोषणा DW_EH_PE_pcrel    0x10
#घोषणा DW_EH_PE_textrel  0x20
#घोषणा DW_EH_PE_datarel  0x30
#घोषणा DW_EH_PE_funcrel  0x40
#घोषणा DW_EH_PE_aligned  0x50
#घोषणा DW_EH_PE_indirect 0x80
#घोषणा DW_EH_PE_omit     0xff

#घोषणा CIE_ID	0

प्रकार अचिन्हित दीर्घ uleb128_t;
प्रकार चिन्हित दीर्घ sleb128_t;

अटल काष्ठा unwind_table अणु
	काष्ठा अणु
		अचिन्हित दीर्घ pc;
		अचिन्हित दीर्घ range;
	पूर्ण core, init;
	स्थिर व्योम *address;
	अचिन्हित दीर्घ size;
	स्थिर अचिन्हित अक्षर *header;
	अचिन्हित दीर्घ hdrsz;
	काष्ठा unwind_table *link;
	स्थिर अक्षर *name;
पूर्ण root_table;

काष्ठा unwind_item अणु
	क्रमागत item_location अणु
		Nowhere,
		Memory,
		Register,
		Value
	पूर्ण where;
	uleb128_t value;
पूर्ण;

काष्ठा unwind_state अणु
	uleb128_t loc, org;
	स्थिर u8 *cieStart, *cieEnd;
	uleb128_t codeAlign;
	sleb128_t dataAlign;
	काष्ठा cfa अणु
		uleb128_t reg, offs;
	पूर्ण cfa;
	काष्ठा unwind_item regs[ARRAY_SIZE(reg_info)];
	अचिन्हित stackDepth:8;
	अचिन्हित version:8;
	स्थिर u8 *label;
	स्थिर u8 *stack[MAX_STACK_DEPTH];
पूर्ण;

अटल स्थिर काष्ठा cfa badCFA = अणु ARRAY_SIZE(reg_info), 1 पूर्ण;

अटल काष्ठा unwind_table *find_table(अचिन्हित दीर्घ pc)
अणु
	काष्ठा unwind_table *table;

	क्रम (table = &root_table; table; table = table->link)
		अगर ((pc >= table->core.pc
		     && pc < table->core.pc + table->core.range)
		    || (pc >= table->init.pc
			&& pc < table->init.pc + table->init.range))
			अवरोध;

	वापस table;
पूर्ण

अटल अचिन्हित दीर्घ पढ़ो_poपूर्णांकer(स्थिर u8 **pLoc,
				  स्थिर व्योम *end, चिन्हित ptrType);
अटल व्योम init_unwind_hdr(काष्ठा unwind_table *table,
			    व्योम *(*alloc) (अचिन्हित दीर्घ));

/*
 * wrappers क्रम header alloc (vs. calling one vs. other at call site)
 * to elide section mismatches warnings
 */
अटल व्योम *__init unw_hdr_alloc_early(अचिन्हित दीर्घ sz)
अणु
	वापस memblock_alloc_from(sz, माप(अचिन्हित पूर्णांक), MAX_DMA_ADDRESS);
पूर्ण

अटल व्योम init_unwind_table(काष्ठा unwind_table *table, स्थिर अक्षर *name,
			      स्थिर व्योम *core_start, अचिन्हित दीर्घ core_size,
			      स्थिर व्योम *init_start, अचिन्हित दीर्घ init_size,
			      स्थिर व्योम *table_start, अचिन्हित दीर्घ table_size,
			      स्थिर u8 *header_start, अचिन्हित दीर्घ header_size)
अणु
	table->core.pc = (अचिन्हित दीर्घ)core_start;
	table->core.range = core_size;
	table->init.pc = (अचिन्हित दीर्घ)init_start;
	table->init.range = init_size;
	table->address = table_start;
	table->size = table_size;
	/* To aव्योम the poपूर्णांकer addition with शून्य poपूर्णांकer.*/
	अगर (header_start != शून्य) अणु
		स्थिर u8 *ptr = header_start + 4;
		स्थिर u8 *end = header_start + header_size;
		/* See अगर the linker provided table looks valid. */
		अगर (header_size <= 4
		|| header_start[0] != 1
		|| (व्योम *)पढ़ो_poपूर्णांकer(&ptr, end, header_start[1])
				!= table_start
		|| header_start[2] == DW_EH_PE_omit
		|| पढ़ो_poपूर्णांकer(&ptr, end, header_start[2]) <= 0
		|| header_start[3] == DW_EH_PE_omit)
			header_start = शून्य;
	पूर्ण
	table->hdrsz = header_size;
	smp_wmb();
	table->header = header_start;
	table->link = शून्य;
	table->name = name;
पूर्ण

व्योम __init arc_unwind_init(व्योम)
अणु
	init_unwind_table(&root_table, "kernel", _text, _end - _text, शून्य, 0,
			  __start_unwind, __end_unwind - __start_unwind,
			  शून्य, 0);
	  /*__start_unwind_hdr, __end_unwind_hdr - __start_unwind_hdr);*/

	init_unwind_hdr(&root_table, unw_hdr_alloc_early);
पूर्ण

अटल स्थिर u32 bad_cie, not_fde;
अटल स्थिर u32 *cie_क्रम_fde(स्थिर u32 *fde, स्थिर काष्ठा unwind_table *);
अटल स्थिर u32 *__cie_क्रम_fde(स्थिर u32 *fde);
अटल चिन्हित fde_poपूर्णांकer_type(स्थिर u32 *cie);

काष्ठा eh_frame_hdr_table_entry अणु
	अचिन्हित दीर्घ start, fde;
पूर्ण;

अटल पूर्णांक cmp_eh_frame_hdr_table_entries(स्थिर व्योम *p1, स्थिर व्योम *p2)
अणु
	स्थिर काष्ठा eh_frame_hdr_table_entry *e1 = p1;
	स्थिर काष्ठा eh_frame_hdr_table_entry *e2 = p2;

	वापस (e1->start > e2->start) - (e1->start < e2->start);
पूर्ण

अटल व्योम swap_eh_frame_hdr_table_entries(व्योम *p1, व्योम *p2, पूर्णांक size)
अणु
	काष्ठा eh_frame_hdr_table_entry *e1 = p1;
	काष्ठा eh_frame_hdr_table_entry *e2 = p2;
	अचिन्हित दीर्घ v;

	v = e1->start;
	e1->start = e2->start;
	e2->start = v;
	v = e1->fde;
	e1->fde = e2->fde;
	e2->fde = v;
पूर्ण

अटल व्योम init_unwind_hdr(काष्ठा unwind_table *table,
			    व्योम *(*alloc) (अचिन्हित दीर्घ))
अणु
	स्थिर u8 *ptr;
	अचिन्हित दीर्घ tableSize = table->size, hdrSize;
	अचिन्हित n;
	स्थिर u32 *fde;
	काष्ठा अणु
		u8 version;
		u8 eh_frame_ptr_enc;
		u8 fde_count_enc;
		u8 table_enc;
		अचिन्हित दीर्घ eh_frame_ptr;
		अचिन्हित पूर्णांक fde_count;
		काष्ठा eh_frame_hdr_table_entry table[];
	पूर्ण __attribute__ ((__packed__)) *header;

	अगर (table->header)
		वापस;

	अगर (table->hdrsz)
		pr_warn(".eh_frame_hdr for '%s' present but unusable\n",
			table->name);

	अगर (tableSize & (माप(*fde) - 1))
		वापस;

	क्रम (fde = table->address, n = 0;
	     tableSize > माप(*fde) && tableSize - माप(*fde) >= *fde;
	     tableSize -= माप(*fde) + *fde, fde += 1 + *fde / माप(*fde)) अणु
		स्थिर u32 *cie = cie_क्रम_fde(fde, table);
		चिन्हित ptrType;

		अगर (cie == &not_fde)
			जारी;
		अगर (cie == शून्य || cie == &bad_cie)
			जाओ ret_err;
		ptrType = fde_poपूर्णांकer_type(cie);
		अगर (ptrType < 0)
			जाओ ret_err;

		ptr = (स्थिर u8 *)(fde + 2);
		अगर (!पढ़ो_poपूर्णांकer(&ptr, (स्थिर u8 *)(fde + 1) + *fde,
								ptrType)) अणु
			/* FIXME_Rajesh We have 4 instances of null addresses
			 * instead of the initial loc addr
			 * वापस;
			 */
			WARN(1, "unwinder: FDE->initial_location NULL %p\n",
				(स्थिर u8 *)(fde + 1) + *fde);
		पूर्ण
		++n;
	पूर्ण

	अगर (tableSize || !n)
		जाओ ret_err;

	hdrSize = 4 + माप(अचिन्हित दीर्घ) + माप(अचिन्हित पूर्णांक)
	    + 2 * n * माप(अचिन्हित दीर्घ);

	header = alloc(hdrSize);
	अगर (!header)
		जाओ ret_err;

	header->version = 1;
	header->eh_frame_ptr_enc = DW_EH_PE_असल | DW_EH_PE_native;
	header->fde_count_enc = DW_EH_PE_असल | DW_EH_PE_data4;
	header->table_enc = DW_EH_PE_असल | DW_EH_PE_native;
	put_unaligned((अचिन्हित दीर्घ)table->address, &header->eh_frame_ptr);
	BUILD_BUG_ON(दुरत्व(typeof(*header), fde_count)
		     % __alignof(typeof(header->fde_count)));
	header->fde_count = n;

	BUILD_BUG_ON(दुरत्व(typeof(*header), table)
		     % __alignof(typeof(*header->table)));
	क्रम (fde = table->address, tableSize = table->size, n = 0;
	     tableSize;
	     tableSize -= माप(*fde) + *fde, fde += 1 + *fde / माप(*fde)) अणु
		स्थिर u32 *cie = __cie_क्रम_fde(fde);

		अगर (fde[1] == CIE_ID)
			जारी;	/* this is a CIE */
		ptr = (स्थिर u8 *)(fde + 2);
		header->table[n].start = पढ़ो_poपूर्णांकer(&ptr,
						      (स्थिर u8 *)(fde + 1) +
						      *fde,
						      fde_poपूर्णांकer_type(cie));
		header->table[n].fde = (अचिन्हित दीर्घ)fde;
		++n;
	पूर्ण
	WARN_ON(n != header->fde_count);

	sort(header->table,
	     n,
	     माप(*header->table),
	     cmp_eh_frame_hdr_table_entries, swap_eh_frame_hdr_table_entries);

	table->hdrsz = hdrSize;
	smp_wmb();
	table->header = (स्थिर व्योम *)header;
	वापस;

ret_err:
	panic("Attention !!! Dwarf FDE parsing errors\n");
पूर्ण

#अगर_घोषित CONFIG_MODULES
अटल व्योम *unw_hdr_alloc(अचिन्हित दीर्घ sz)
अणु
	वापस kदो_स्मृति(sz, GFP_KERNEL);
पूर्ण

अटल काष्ठा unwind_table *last_table;

/* Must be called with module_mutex held. */
व्योम *unwind_add_table(काष्ठा module *module, स्थिर व्योम *table_start,
		       अचिन्हित दीर्घ table_size)
अणु
	काष्ठा unwind_table *table;

	अगर (table_size <= 0)
		वापस शून्य;

	table = kदो_स्मृति(माप(*table), GFP_KERNEL);
	अगर (!table)
		वापस शून्य;

	init_unwind_table(table, module->name,
			  module->core_layout.base, module->core_layout.size,
			  module->init_layout.base, module->init_layout.size,
			  table_start, table_size,
			  शून्य, 0);

	init_unwind_hdr(table, unw_hdr_alloc);

#अगर_घोषित UNWIND_DEBUG
	unw_debug("Table added for [%s] %lx %lx\n",
		module->name, table->core.pc, table->core.range);
#पूर्ण_अगर
	अगर (last_table)
		last_table->link = table;
	अन्यथा
		root_table.link = table;
	last_table = table;

	वापस table;
पूर्ण

काष्ठा unlink_table_info अणु
	काष्ठा unwind_table *table;
	पूर्णांक init_only;
पूर्ण;

अटल पूर्णांक unlink_table(व्योम *arg)
अणु
	काष्ठा unlink_table_info *info = arg;
	काष्ठा unwind_table *table = info->table, *prev;

	क्रम (prev = &root_table; prev->link && prev->link != table;
	     prev = prev->link)
		;

	अगर (prev->link) अणु
		अगर (info->init_only) अणु
			table->init.pc = 0;
			table->init.range = 0;
			info->table = शून्य;
		पूर्ण अन्यथा अणु
			prev->link = table->link;
			अगर (!prev->link)
				last_table = prev;
		पूर्ण
	पूर्ण अन्यथा
		info->table = शून्य;

	वापस 0;
पूर्ण

/* Must be called with module_mutex held. */
व्योम unwind_हटाओ_table(व्योम *handle, पूर्णांक init_only)
अणु
	काष्ठा unwind_table *table = handle;
	काष्ठा unlink_table_info info;

	अगर (!table || table == &root_table)
		वापस;

	अगर (init_only && table == last_table) अणु
		table->init.pc = 0;
		table->init.range = 0;
		वापस;
	पूर्ण

	info.table = table;
	info.init_only = init_only;

	unlink_table(&info); /* XXX: SMP */
	kमुक्त(table->header);
	kमुक्त(table);
पूर्ण

#पूर्ण_अगर /* CONFIG_MODULES */

अटल uleb128_t get_uleb128(स्थिर u8 **pcur, स्थिर u8 *end)
अणु
	स्थिर u8 *cur = *pcur;
	uleb128_t value;
	अचिन्हित shअगरt;

	क्रम (shअगरt = 0, value = 0; cur < end; shअगरt += 7) अणु
		अगर (shअगरt + 7 > 8 * माप(value)
		    && (*cur & 0x7fU) >= (1U << (8 * माप(value) - shअगरt))) अणु
			cur = end + 1;
			अवरोध;
		पूर्ण
		value |= (uleb128_t) (*cur & 0x7f) << shअगरt;
		अगर (!(*cur++ & 0x80))
			अवरोध;
	पूर्ण
	*pcur = cur;

	वापस value;
पूर्ण

अटल sleb128_t get_sleb128(स्थिर u8 **pcur, स्थिर u8 *end)
अणु
	स्थिर u8 *cur = *pcur;
	sleb128_t value;
	अचिन्हित shअगरt;

	क्रम (shअगरt = 0, value = 0; cur < end; shअगरt += 7) अणु
		अगर (shअगरt + 7 > 8 * माप(value)
		    && (*cur & 0x7fU) >= (1U << (8 * माप(value) - shअगरt))) अणु
			cur = end + 1;
			अवरोध;
		पूर्ण
		value |= (sleb128_t) (*cur & 0x7f) << shअगरt;
		अगर (!(*cur & 0x80)) अणु
			value |= -(*cur++ & 0x40) << shअगरt;
			अवरोध;
		पूर्ण
	पूर्ण
	*pcur = cur;

	वापस value;
पूर्ण

अटल स्थिर u32 *__cie_क्रम_fde(स्थिर u32 *fde)
अणु
	स्थिर u32 *cie;

	cie = fde + 1 - fde[1] / माप(*fde);

	वापस cie;
पूर्ण

अटल स्थिर u32 *cie_क्रम_fde(स्थिर u32 *fde, स्थिर काष्ठा unwind_table *table)
अणु
	स्थिर u32 *cie;

	अगर (!*fde || (*fde & (माप(*fde) - 1)))
		वापस &bad_cie;

	अगर (fde[1] == CIE_ID)
		वापस &not_fde;	/* this is a CIE */

	अगर ((fde[1] & (माप(*fde) - 1)))
/* || fde[1] > (अचिन्हित दीर्घ)(fde + 1) - (अचिन्हित दीर्घ)table->address) */
		वापस शून्य;	/* this is not a valid FDE */

	cie = __cie_क्रम_fde(fde);

	अगर (*cie <= माप(*cie) + 4 || *cie >= fde[1] - माप(*fde)
	    || (*cie & (माप(*cie) - 1))
	    || (cie[1] != CIE_ID))
		वापस शून्य;	/* this is not a (valid) CIE */
	वापस cie;
पूर्ण

अटल अचिन्हित दीर्घ पढ़ो_poपूर्णांकer(स्थिर u8 **pLoc, स्थिर व्योम *end,
				  चिन्हित ptrType)
अणु
	अचिन्हित दीर्घ value = 0;
	जोड़ अणु
		स्थिर u8 *p8;
		स्थिर u16 *p16u;
		स्थिर s16 *p16s;
		स्थिर u32 *p32u;
		स्थिर s32 *p32s;
		स्थिर अचिन्हित दीर्घ *pul;
	पूर्ण ptr;

	अगर (ptrType < 0 || ptrType == DW_EH_PE_omit)
		वापस 0;
	ptr.p8 = *pLoc;
	चयन (ptrType & DW_EH_PE_FORM) अणु
	हाल DW_EH_PE_data2:
		अगर (end < (स्थिर व्योम *)(ptr.p16u + 1))
			वापस 0;
		अगर (ptrType & DW_EH_PE_चिन्हित)
			value = get_unaligned((u16 *) ptr.p16s++);
		अन्यथा
			value = get_unaligned((u16 *) ptr.p16u++);
		अवरोध;
	हाल DW_EH_PE_data4:
#अगर_घोषित CONFIG_64BIT
		अगर (end < (स्थिर व्योम *)(ptr.p32u + 1))
			वापस 0;
		अगर (ptrType & DW_EH_PE_चिन्हित)
			value = get_unaligned(ptr.p32s++);
		अन्यथा
			value = get_unaligned(ptr.p32u++);
		अवरोध;
	हाल DW_EH_PE_data8:
		BUILD_BUG_ON(माप(u64) != माप(value));
#अन्यथा
		BUILD_BUG_ON(माप(u32) != माप(value));
#पूर्ण_अगर
		fallthrough;
	हाल DW_EH_PE_native:
		अगर (end < (स्थिर व्योम *)(ptr.pul + 1))
			वापस 0;
		value = get_unaligned((अचिन्हित दीर्घ *)ptr.pul++);
		अवरोध;
	हाल DW_EH_PE_leb128:
		BUILD_BUG_ON(माप(uleb128_t) > माप(value));
		value = ptrType & DW_EH_PE_चिन्हित ? get_sleb128(&ptr.p8, end)
		    : get_uleb128(&ptr.p8, end);
		अगर ((स्थिर व्योम *)ptr.p8 > end)
			वापस 0;
		अवरोध;
	शेष:
		वापस 0;
	पूर्ण
	चयन (ptrType & DW_EH_PE_ADJUST) अणु
	हाल DW_EH_PE_असल:
		अवरोध;
	हाल DW_EH_PE_pcrel:
		value += (अचिन्हित दीर्घ)*pLoc;
		अवरोध;
	शेष:
		वापस 0;
	पूर्ण
	अगर ((ptrType & DW_EH_PE_indirect)
	    && __get_user(value, (अचिन्हित दीर्घ __user *)value))
		वापस 0;
	*pLoc = ptr.p8;

	वापस value;
पूर्ण

अटल चिन्हित fde_poपूर्णांकer_type(स्थिर u32 *cie)
अणु
	स्थिर u8 *ptr = (स्थिर u8 *)(cie + 2);
	अचिन्हित version = *ptr;

	अगर (*++ptr) अणु
		स्थिर अक्षर *aug;
		स्थिर u8 *end = (स्थिर u8 *)(cie + 1) + *cie;
		uleb128_t len;

		/* check अगर augmentation size is first (and thus present) */
		अगर (*ptr != 'z')
			वापस -1;

		/* check अगर augmentation string is nul-terminated */
		aug = (स्थिर व्योम *)ptr;
		ptr = स_प्रथम(aug, 0, end - ptr);
		अगर (ptr == शून्य)
			वापस -1;

		++ptr;		/* skip terminator */
		get_uleb128(&ptr, end);	/* skip code alignment */
		get_sleb128(&ptr, end);	/* skip data alignment */
		/* skip वापस address column */
		version <= 1 ? (व्योम) ++ptr : (व्योम)get_uleb128(&ptr, end);
		len = get_uleb128(&ptr, end);	/* augmentation length */

		अगर (ptr + len < ptr || ptr + len > end)
			वापस -1;

		end = ptr + len;
		जबतक (*++aug) अणु
			अगर (ptr >= end)
				वापस -1;
			चयन (*aug) अणु
			हाल 'L':
				++ptr;
				अवरोध;
			हाल 'P':अणु
					चिन्हित ptrType = *ptr++;

					अगर (!पढ़ो_poपूर्णांकer(&ptr, end, ptrType)
					    || ptr > end)
						वापस -1;
				पूर्ण
				अवरोध;
			हाल 'R':
				वापस *ptr;
			शेष:
				वापस -1;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस DW_EH_PE_native | DW_EH_PE_असल;
पूर्ण

अटल पूर्णांक advance_loc(अचिन्हित दीर्घ delta, काष्ठा unwind_state *state)
अणु
	state->loc += delta * state->codeAlign;

	/* FIXME_Rajesh: Probably we are defining क्रम the initial range as well;
	   वापस delta > 0;
	 */
	unw_debug("delta %3lu => loc 0x%lx: ", delta, state->loc);
	वापस 1;
पूर्ण

अटल व्योम set_rule(uleb128_t reg, क्रमागत item_location where, uleb128_t value,
		     काष्ठा unwind_state *state)
अणु
	अगर (reg < ARRAY_SIZE(state->regs)) अणु
		state->regs[reg].where = where;
		state->regs[reg].value = value;

#अगर_घोषित UNWIND_DEBUG
		unw_debug("r%lu: ", reg);
		चयन (where) अणु
		हाल Nowhere:
			unw_debug("s ");
			अवरोध;
		हाल Memory:
			unw_debug("c(%lu) ", value);
			अवरोध;
		हाल Register:
			unw_debug("r(%lu) ", value);
			अवरोध;
		हाल Value:
			unw_debug("v(%lu) ", value);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
#पूर्ण_अगर
	पूर्ण
पूर्ण

अटल पूर्णांक processCFI(स्थिर u8 *start, स्थिर u8 *end, अचिन्हित दीर्घ targetLoc,
		      चिन्हित ptrType, काष्ठा unwind_state *state)
अणु
	जोड़ अणु
		स्थिर u8 *p8;
		स्थिर u16 *p16;
		स्थिर u32 *p32;
	पूर्ण ptr;
	पूर्णांक result = 1;
	u8 opcode;

	अगर (start != state->cieStart) अणु
		state->loc = state->org;
		result =
		    processCFI(state->cieStart, state->cieEnd, 0, ptrType,
			       state);
		अगर (targetLoc == 0 && state->label == शून्य)
			वापस result;
	पूर्ण
	क्रम (ptr.p8 = start; result && ptr.p8 < end;) अणु
		चयन (*ptr.p8 >> 6) अणु
			uleb128_t value;

		हाल 0:
			opcode = *ptr.p8++;

			चयन (opcode) अणु
			हाल DW_CFA_nop:
				unw_debug("cfa nop ");
				अवरोध;
			हाल DW_CFA_set_loc:
				state->loc = पढ़ो_poपूर्णांकer(&ptr.p8, end,
							  ptrType);
				अगर (state->loc == 0)
					result = 0;
				unw_debug("cfa_set_loc: 0x%lx ", state->loc);
				अवरोध;
			हाल DW_CFA_advance_loc1:
				unw_debug("\ncfa advance loc1:");
				result = ptr.p8 < end
				    && advance_loc(*ptr.p8++, state);
				अवरोध;
			हाल DW_CFA_advance_loc2:
				value = *ptr.p8++;
				value += *ptr.p8++ << 8;
				unw_debug("\ncfa advance loc2:");
				result = ptr.p8 <= end + 2
				    /* && advance_loc(*ptr.p16++, state); */
				    && advance_loc(value, state);
				अवरोध;
			हाल DW_CFA_advance_loc4:
				unw_debug("\ncfa advance loc4:");
				result = ptr.p8 <= end + 4
				    && advance_loc(*ptr.p32++, state);
				अवरोध;
			हाल DW_CFA_offset_extended:
				value = get_uleb128(&ptr.p8, end);
				unw_debug("cfa_offset_extended: ");
				set_rule(value, Memory,
					 get_uleb128(&ptr.p8, end), state);
				अवरोध;
			हाल DW_CFA_val_offset:
				value = get_uleb128(&ptr.p8, end);
				set_rule(value, Value,
					 get_uleb128(&ptr.p8, end), state);
				अवरोध;
			हाल DW_CFA_offset_extended_sf:
				value = get_uleb128(&ptr.p8, end);
				set_rule(value, Memory,
					 get_sleb128(&ptr.p8, end), state);
				अवरोध;
			हाल DW_CFA_val_offset_sf:
				value = get_uleb128(&ptr.p8, end);
				set_rule(value, Value,
					 get_sleb128(&ptr.p8, end), state);
				अवरोध;
			हाल DW_CFA_restore_extended:
				unw_debug("cfa_restore_extended: ");
			हाल DW_CFA_undefined:
				unw_debug("cfa_undefined: ");
			हाल DW_CFA_same_value:
				unw_debug("cfa_same_value: ");
				set_rule(get_uleb128(&ptr.p8, end), Nowhere, 0,
					 state);
				अवरोध;
			हाल DW_CFA_रेजिस्टर:
				unw_debug("cfa_register: ");
				value = get_uleb128(&ptr.p8, end);
				set_rule(value,
					 Register,
					 get_uleb128(&ptr.p8, end), state);
				अवरोध;
			हाल DW_CFA_remember_state:
				unw_debug("cfa_remember_state: ");
				अगर (ptr.p8 == state->label) अणु
					state->label = शून्य;
					वापस 1;
				पूर्ण
				अगर (state->stackDepth >= MAX_STACK_DEPTH)
					वापस 0;
				state->stack[state->stackDepth++] = ptr.p8;
				अवरोध;
			हाल DW_CFA_restore_state:
				unw_debug("cfa_restore_state: ");
				अगर (state->stackDepth) अणु
					स्थिर uleb128_t loc = state->loc;
					स्थिर u8 *label = state->label;

					state->label =
					    state->stack[state->stackDepth - 1];
					स_नकल(&state->cfa, &badCFA,
					       माप(state->cfa));
					स_रखो(state->regs, 0,
					       माप(state->regs));
					state->stackDepth = 0;
					result =
					    processCFI(start, end, 0, ptrType,
						       state);
					state->loc = loc;
					state->label = label;
				पूर्ण अन्यथा
					वापस 0;
				अवरोध;
			हाल DW_CFA_def_cfa:
				state->cfa.reg = get_uleb128(&ptr.p8, end);
				unw_debug("cfa_def_cfa: r%lu ", state->cfa.reg);
				fallthrough;
			हाल DW_CFA_def_cfa_offset:
				state->cfa.offs = get_uleb128(&ptr.p8, end);
				unw_debug("cfa_def_cfa_offset: 0x%lx ",
					  state->cfa.offs);
				अवरोध;
			हाल DW_CFA_def_cfa_sf:
				state->cfa.reg = get_uleb128(&ptr.p8, end);
				fallthrough;
			हाल DW_CFA_def_cfa_offset_sf:
				state->cfa.offs = get_sleb128(&ptr.p8, end)
				    * state->dataAlign;
				अवरोध;
			हाल DW_CFA_def_cfa_रेजिस्टर:
				unw_debug("cfa_def_cfa_register: ");
				state->cfa.reg = get_uleb128(&ptr.p8, end);
				अवरोध;
				/*toकरो हाल DW_CFA_def_cfa_expression: */
				/*toकरो हाल DW_CFA_expression: */
				/*toकरो हाल DW_CFA_val_expression: */
			हाल DW_CFA_GNU_args_size:
				get_uleb128(&ptr.p8, end);
				अवरोध;
			हाल DW_CFA_GNU_negative_offset_extended:
				value = get_uleb128(&ptr.p8, end);
				set_rule(value,
					 Memory,
					 (uleb128_t) 0 - get_uleb128(&ptr.p8,
								     end),
					 state);
				अवरोध;
			हाल DW_CFA_GNU_winकरोw_save:
			शेष:
				unw_debug("UNKNOWN OPCODE 0x%x\n", opcode);
				result = 0;
				अवरोध;
			पूर्ण
			अवरोध;
		हाल 1:
			unw_debug("\ncfa_adv_loc: ");
			result = advance_loc(*ptr.p8++ & 0x3f, state);
			अवरोध;
		हाल 2:
			unw_debug("cfa_offset: ");
			value = *ptr.p8++ & 0x3f;
			set_rule(value, Memory, get_uleb128(&ptr.p8, end),
				 state);
			अवरोध;
		हाल 3:
			unw_debug("cfa_restore: ");
			set_rule(*ptr.p8++ & 0x3f, Nowhere, 0, state);
			अवरोध;
		पूर्ण

		अगर (ptr.p8 > end)
			result = 0;
		अगर (result && targetLoc != 0 && targetLoc < state->loc)
			वापस 1;
	पूर्ण

	वापस result && ptr.p8 == end && (targetLoc == 0 || (
		/*toकरो While in theory this should apply, gcc in practice omits
		  everything past the function prolog, and hence the location
		  never reaches the end of the function.
		targetLoc < state->loc && */  state->label == शून्य));
पूर्ण

/* Unwind to previous to frame.  Returns 0 अगर successful, negative
 * number in हाल of an error. */
पूर्णांक arc_unwind(काष्ठा unwind_frame_info *frame)
अणु
#घोषणा FRAME_REG(r, t) (((t *)frame)[reg_info[r].offs])
	स्थिर u32 *fde = शून्य, *cie = शून्य;
	स्थिर u8 *ptr = शून्य, *end = शून्य;
	अचिन्हित दीर्घ pc = UNW_PC(frame) - frame->call_frame;
	अचिन्हित दीर्घ startLoc = 0, endLoc = 0, cfa;
	अचिन्हित i;
	चिन्हित ptrType = -1;
	uleb128_t retAddrReg = 0;
	स्थिर काष्ठा unwind_table *table;
	काष्ठा unwind_state state;
	अचिन्हित दीर्घ *fptr;
	अचिन्हित दीर्घ addr;

	unw_debug("\n\nUNWIND FRAME:\n");
	unw_debug("PC: 0x%lx BLINK: 0x%lx, SP: 0x%lx, FP: 0x%x\n",
		  UNW_PC(frame), UNW_BLINK(frame), UNW_SP(frame),
		  UNW_FP(frame));

	अगर (UNW_PC(frame) == 0)
		वापस -EINVAL;

#अगर_घोषित UNWIND_DEBUG
	अणु
		अचिन्हित दीर्घ *sptr = (अचिन्हित दीर्घ *)UNW_SP(frame);
		unw_debug("\nStack Dump:\n");
		क्रम (i = 0; i < 20; i++, sptr++)
			unw_debug("0x%p:  0x%lx\n", sptr, *sptr);
		unw_debug("\n");
	पूर्ण
#पूर्ण_अगर

	table = find_table(pc);
	अगर (table != शून्य
	    && !(table->size & (माप(*fde) - 1))) अणु
		स्थिर u8 *hdr = table->header;
		अचिन्हित दीर्घ tableSize;

		smp_rmb();
		अगर (hdr && hdr[0] == 1) अणु
			चयन (hdr[3] & DW_EH_PE_FORM) अणु
			हाल DW_EH_PE_native:
				tableSize = माप(अचिन्हित दीर्घ);
				अवरोध;
			हाल DW_EH_PE_data2:
				tableSize = 2;
				अवरोध;
			हाल DW_EH_PE_data4:
				tableSize = 4;
				अवरोध;
			हाल DW_EH_PE_data8:
				tableSize = 8;
				अवरोध;
			शेष:
				tableSize = 0;
				अवरोध;
			पूर्ण
			ptr = hdr + 4;
			end = hdr + table->hdrsz;
			अगर (tableSize && पढ़ो_poपूर्णांकer(&ptr, end, hdr[1])
			    == (अचिन्हित दीर्घ)table->address
			    && (i = पढ़ो_poपूर्णांकer(&ptr, end, hdr[2])) > 0
			    && i == (end - ptr) / (2 * tableSize)
			    && !((end - ptr) % (2 * tableSize))) अणु
				करो अणु
					स्थिर u8 *cur =
					    ptr + (i / 2) * (2 * tableSize);

					startLoc = पढ़ो_poपूर्णांकer(&cur,
								cur + tableSize,
								hdr[3]);
					अगर (pc < startLoc)
						i /= 2;
					अन्यथा अणु
						ptr = cur - tableSize;
						i = (i + 1) / 2;
					पूर्ण
				पूर्ण जबतक (startLoc && i > 1);
				अगर (i == 1
				    && (startLoc = पढ़ो_poपूर्णांकer(&ptr,
								ptr + tableSize,
								hdr[3])) != 0
				    && pc >= startLoc)
					fde = (व्योम *)पढ़ो_poपूर्णांकer(&ptr,
								   ptr +
								   tableSize,
								   hdr[3]);
			पूर्ण
		पूर्ण

		अगर (fde != शून्य) अणु
			cie = cie_क्रम_fde(fde, table);
			ptr = (स्थिर u8 *)(fde + 2);
			अगर (cie != शून्य
			    && cie != &bad_cie
			    && cie != &not_fde
			    && (ptrType = fde_poपूर्णांकer_type(cie)) >= 0
			    && पढ़ो_poपूर्णांकer(&ptr,
					    (स्थिर u8 *)(fde + 1) + *fde,
					    ptrType) == startLoc) अणु
				अगर (!(ptrType & DW_EH_PE_indirect))
					ptrType &=
					    DW_EH_PE_FORM | DW_EH_PE_चिन्हित;
				endLoc =
				    startLoc + पढ़ो_poपूर्णांकer(&ptr,
							    (स्थिर u8 *)(fde +
									 1) +
							    *fde, ptrType);
				अगर (pc >= endLoc) अणु
					fde = शून्य;
					cie = शून्य;
				पूर्ण
			पूर्ण अन्यथा अणु
				fde = शून्य;
				cie = शून्य;
			पूर्ण
		पूर्ण
	पूर्ण
	अगर (cie != शून्य) अणु
		स_रखो(&state, 0, माप(state));
		state.cieEnd = ptr;	/* keep here temporarily */
		ptr = (स्थिर u8 *)(cie + 2);
		end = (स्थिर u8 *)(cie + 1) + *cie;
		frame->call_frame = 1;
		अगर (*++ptr) अणु
			/* check अगर augmentation size is first (thus present) */
			अगर (*ptr == 'z') अणु
				जबतक (++ptr < end && *ptr) अणु
					चयन (*ptr) अणु
					/* chk क्रम ignorable or alपढ़ोy handled
					 * nul-terminated augmentation string */
					हाल 'L':
					हाल 'P':
					हाल 'R':
						जारी;
					हाल 'S':
						frame->call_frame = 0;
						जारी;
					शेष:
						अवरोध;
					पूर्ण
					अवरोध;
				पूर्ण
			पूर्ण
			अगर (ptr >= end || *ptr)
				cie = शून्य;
		पूर्ण
		++ptr;
	पूर्ण
	अगर (cie != शून्य) अणु
		/* get code alignment factor */
		state.codeAlign = get_uleb128(&ptr, end);
		/* get data alignment factor */
		state.dataAlign = get_sleb128(&ptr, end);
		अगर (state.codeAlign == 0 || state.dataAlign == 0 || ptr >= end)
			cie = शून्य;
		अन्यथा अणु
			retAddrReg =
			    state.version <= 1 ? *ptr++ : get_uleb128(&ptr,
								      end);
			unw_debug("CIE Frame Info:\n");
			unw_debug("return Address register 0x%lx\n",
				  retAddrReg);
			unw_debug("data Align: %ld\n", state.dataAlign);
			unw_debug("code Align: %lu\n", state.codeAlign);
			/* skip augmentation */
			अगर (((स्थिर अक्षर *)(cie + 2))[1] == 'z') अणु
				uleb128_t augSize = get_uleb128(&ptr, end);

				ptr += augSize;
			पूर्ण
			अगर (ptr > end || retAddrReg >= ARRAY_SIZE(reg_info)
			    || REG_INVALID(retAddrReg)
			    || reg_info[retAddrReg].width !=
			    माप(अचिन्हित दीर्घ))
				cie = शून्य;
		पूर्ण
	पूर्ण
	अगर (cie != शून्य) अणु
		state.cieStart = ptr;
		ptr = state.cieEnd;
		state.cieEnd = end;
		end = (स्थिर u8 *)(fde + 1) + *fde;
		/* skip augmentation */
		अगर (((स्थिर अक्षर *)(cie + 2))[1] == 'z') अणु
			uleb128_t augSize = get_uleb128(&ptr, end);

			अगर ((ptr += augSize) > end)
				fde = शून्य;
		पूर्ण
	पूर्ण
	अगर (cie == शून्य || fde == शून्य) अणु
#अगर_घोषित CONFIG_FRAME_POINTER
		अचिन्हित दीर्घ top, bottom;

		top = STACK_TOP_UNW(frame->task);
		bottom = STACK_BOTTOM_UNW(frame->task);
#अगर FRAME_RETADDR_OFFSET < 0
		अगर (UNW_SP(frame) < top && UNW_FP(frame) <= UNW_SP(frame)
		    && bottom < UNW_FP(frame)
#अन्यथा
		अगर (UNW_SP(frame) > top && UNW_FP(frame) >= UNW_SP(frame)
		    && bottom > UNW_FP(frame)
#पूर्ण_अगर
		    && !((UNW_SP(frame) | UNW_FP(frame))
			 & (माप(अचिन्हित दीर्घ) - 1))) अणु
			अचिन्हित दीर्घ link;

			अगर (!__get_user(link, (अचिन्हित दीर्घ *)
					(UNW_FP(frame) + FRAME_LINK_OFFSET))
#अगर FRAME_RETADDR_OFFSET < 0
			    && link > bottom && link < UNW_FP(frame)
#अन्यथा
			    && link > UNW_FP(frame) && link < bottom
#पूर्ण_अगर
			    && !(link & (माप(link) - 1))
			    && !__get_user(UNW_PC(frame),
					   (अचिन्हित दीर्घ *)(UNW_FP(frame)
						+ FRAME_RETADDR_OFFSET)))
			अणु
				UNW_SP(frame) =
				    UNW_FP(frame) + FRAME_RETADDR_OFFSET
#अगर FRAME_RETADDR_OFFSET < 0
				    -
#अन्यथा
				    +
#पूर्ण_अगर
				    माप(UNW_PC(frame));
				UNW_FP(frame) = link;
				वापस 0;
			पूर्ण
		पूर्ण
#पूर्ण_अगर
		वापस -ENXIO;
	पूर्ण
	state.org = startLoc;
	स_नकल(&state.cfa, &badCFA, माप(state.cfa));

	unw_debug("\nProcess instructions\n");

	/* process inकाष्ठाions
	 * For ARC, we optimize by having blink(retAddrReg) with
	 * the sameValue in the leaf function, so we should not check
	 * state.regs[retAddrReg].where == Nowhere
	 */
	अगर (!processCFI(ptr, end, pc, ptrType, &state)
	    || state.loc > endLoc
/*	   || state.regs[retAddrReg].where == Nowhere */
	    || state.cfa.reg >= ARRAY_SIZE(reg_info)
	    || reg_info[state.cfa.reg].width != माप(अचिन्हित दीर्घ)
	    || state.cfa.offs % माप(अचिन्हित दीर्घ))
		वापस -EIO;

#अगर_घोषित UNWIND_DEBUG
	unw_debug("\n");

	unw_debug("\nRegister State Based on the rules parsed from FDE:\n");
	क्रम (i = 0; i < ARRAY_SIZE(state.regs); ++i) अणु

		अगर (REG_INVALID(i))
			जारी;

		चयन (state.regs[i].where) अणु
		हाल Nowhere:
			अवरोध;
		हाल Memory:
			unw_debug(" r%d: c(%lu),", i, state.regs[i].value);
			अवरोध;
		हाल Register:
			unw_debug(" r%d: r(%lu),", i, state.regs[i].value);
			अवरोध;
		हाल Value:
			unw_debug(" r%d: v(%lu),", i, state.regs[i].value);
			अवरोध;
		पूर्ण
	पूर्ण

	unw_debug("\n");
#पूर्ण_अगर

	/* update frame */
	अगर (frame->call_frame
	    && !UNW_DEFAULT_RA(state.regs[retAddrReg], state.dataAlign))
		frame->call_frame = 0;
	cfa = FRAME_REG(state.cfa.reg, अचिन्हित दीर्घ) + state.cfa.offs;
	startLoc = min_t(अचिन्हित दीर्घ, UNW_SP(frame), cfa);
	endLoc = max_t(अचिन्हित दीर्घ, UNW_SP(frame), cfa);
	अगर (STACK_LIMIT(startLoc) != STACK_LIMIT(endLoc)) अणु
		startLoc = min(STACK_LIMIT(cfa), cfa);
		endLoc = max(STACK_LIMIT(cfa), cfa);
	पूर्ण

	unw_debug("\nCFA reg: 0x%lx, offset: 0x%lx =>  0x%lx\n",
		  state.cfa.reg, state.cfa.offs, cfa);

	क्रम (i = 0; i < ARRAY_SIZE(state.regs); ++i) अणु
		अगर (REG_INVALID(i)) अणु
			अगर (state.regs[i].where == Nowhere)
				जारी;
			वापस -EIO;
		पूर्ण
		चयन (state.regs[i].where) अणु
		शेष:
			अवरोध;
		हाल Register:
			अगर (state.regs[i].value >= ARRAY_SIZE(reg_info)
			    || REG_INVALID(state.regs[i].value)
			    || reg_info[i].width >
			    reg_info[state.regs[i].value].width)
				वापस -EIO;
			चयन (reg_info[state.regs[i].value].width) अणु
			हाल माप(u8):
				state.regs[i].value =
				FRAME_REG(state.regs[i].value, स्थिर u8);
				अवरोध;
			हाल माप(u16):
				state.regs[i].value =
				FRAME_REG(state.regs[i].value, स्थिर u16);
				अवरोध;
			हाल माप(u32):
				state.regs[i].value =
				FRAME_REG(state.regs[i].value, स्थिर u32);
				अवरोध;
#अगर_घोषित CONFIG_64BIT
			हाल माप(u64):
				state.regs[i].value =
				FRAME_REG(state.regs[i].value, स्थिर u64);
				अवरोध;
#पूर्ण_अगर
			शेष:
				वापस -EIO;
			पूर्ण
			अवरोध;
		पूर्ण
	पूर्ण

	unw_debug("\nRegister state after evaluation with realtime Stack:\n");
	fptr = (अचिन्हित दीर्घ *)(&frame->regs);
	क्रम (i = 0; i < ARRAY_SIZE(state.regs); ++i, fptr++) अणु

		अगर (REG_INVALID(i))
			जारी;
		चयन (state.regs[i].where) अणु
		हाल Nowhere:
			अगर (reg_info[i].width != माप(UNW_SP(frame))
			    || &FRAME_REG(i, __typeof__(UNW_SP(frame)))
			    != &UNW_SP(frame))
				जारी;
			UNW_SP(frame) = cfa;
			अवरोध;
		हाल Register:
			चयन (reg_info[i].width) अणु
			हाल माप(u8):
				FRAME_REG(i, u8) = state.regs[i].value;
				अवरोध;
			हाल माप(u16):
				FRAME_REG(i, u16) = state.regs[i].value;
				अवरोध;
			हाल माप(u32):
				FRAME_REG(i, u32) = state.regs[i].value;
				अवरोध;
#अगर_घोषित CONFIG_64BIT
			हाल माप(u64):
				FRAME_REG(i, u64) = state.regs[i].value;
				अवरोध;
#पूर्ण_अगर
			शेष:
				वापस -EIO;
			पूर्ण
			अवरोध;
		हाल Value:
			अगर (reg_info[i].width != माप(अचिन्हित दीर्घ))
				वापस -EIO;
			FRAME_REG(i, अचिन्हित दीर्घ) = cfa + state.regs[i].value
			    * state.dataAlign;
			अवरोध;
		हाल Memory:
			addr = cfa + state.regs[i].value * state.dataAlign;

			अगर ((state.regs[i].value * state.dataAlign)
			    % माप(अचिन्हित दीर्घ)
			    || addr < startLoc
			    || addr + माप(अचिन्हित दीर्घ) < addr
			    || addr + माप(अचिन्हित दीर्घ) > endLoc)
					वापस -EIO;

			चयन (reg_info[i].width) अणु
			हाल माप(u8):
				__get_user(FRAME_REG(i, u8),
					   (u8 __user *)addr);
				अवरोध;
			हाल माप(u16):
				__get_user(FRAME_REG(i, u16),
					   (u16 __user *)addr);
				अवरोध;
			हाल माप(u32):
				__get_user(FRAME_REG(i, u32),
					   (u32 __user *)addr);
				अवरोध;
#अगर_घोषित CONFIG_64BIT
			हाल माप(u64):
				__get_user(FRAME_REG(i, u64),
					   (u64 __user *)addr);
				अवरोध;
#पूर्ण_अगर
			शेष:
				वापस -EIO;
			पूर्ण

			अवरोध;
		पूर्ण
		unw_debug("r%d: 0x%lx ", i, *fptr);
	पूर्ण

	वापस 0;
#अघोषित FRAME_REG
पूर्ण
EXPORT_SYMBOL(arc_unwind);
