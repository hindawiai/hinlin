<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * genelf_debug.c
 * Copyright (C) 2015, Google, Inc
 *
 * Contributed by:
 * 	Stephane Eranian <eranian@google.com>
 *
 * based on GPLv2 source code from Oprofile
 * @remark Copyright 2007 OProfile authors
 * @author Philippe Elie
 */
#समावेश <linux/compiler.h>
#समावेश <sys/types.h>
#समावेश <मानकपन.स>
#समावेश <getopt.h>
#समावेश <मानकघोष.स>
#समावेश <libelf.h>
#समावेश <माला.स>
#समावेश <मानककोष.स>
#समावेश <पूर्णांकtypes.h>
#समावेश <सीमा.स>
#समावेश <fcntl.h>
#समावेश <err.h>
#समावेश <dwarf.h>

#समावेश "genelf.h"
#समावेश "../util/jitdump.h"

#घोषणा BUFFER_EXT_DFL_SIZE	(4 * 1024)

प्रकार uपूर्णांक32_t uword;
प्रकार uपूर्णांक16_t uhalf;
प्रकार पूर्णांक32_t  sword;
प्रकार पूर्णांक16_t  shalf;
प्रकार uपूर्णांक8_t  ubyte;
प्रकार पूर्णांक8_t   sbyte;

काष्ठा buffer_ext अणु
	माप_प्रकार cur_pos;
	माप_प्रकार max_sz;
	व्योम *data;
पूर्ण;

अटल व्योम
buffer_ext_dump(काष्ठा buffer_ext *be, स्थिर अक्षर *msg)
अणु
	माप_प्रकार i;
	warnx("DUMP for %s", msg);
	क्रम (i = 0 ; i < be->cur_pos; i++)
		warnx("%4zu 0x%02x", i, (((अक्षर *)be->data)[i]) & 0xff);
पूर्ण

अटल अंतरभूत पूर्णांक
buffer_ext_add(काष्ठा buffer_ext *be, व्योम *addr, माप_प्रकार sz)
अणु
	व्योम *पंचांगp;
	माप_प्रकार be_sz = be->max_sz;

retry:
	अगर ((be->cur_pos + sz) < be_sz) अणु
		स_नकल(be->data + be->cur_pos, addr, sz);
		be->cur_pos += sz;
		वापस 0;
	पूर्ण

	अगर (!be_sz)
		be_sz = BUFFER_EXT_DFL_SIZE;
	अन्यथा
		be_sz <<= 1;

	पंचांगp = पुनः_स्मृति(be->data, be_sz);
	अगर (!पंचांगp)
		वापस -1;

	be->data   = पंचांगp;
	be->max_sz = be_sz;

	जाओ retry;
पूर्ण

अटल व्योम
buffer_ext_init(काष्ठा buffer_ext *be)
अणु
	be->data = शून्य;
	be->cur_pos = 0;
	be->max_sz = 0;
पूर्ण

अटल अंतरभूत माप_प्रकार
buffer_ext_size(काष्ठा buffer_ext *be)
अणु
	वापस be->cur_pos;
पूर्ण

अटल अंतरभूत व्योम *
buffer_ext_addr(काष्ठा buffer_ext *be)
अणु
	वापस be->data;
पूर्ण

काष्ठा debug_line_header अणु
	// Not counting this field
	uword total_length;
	// version number (2 currently)
	uhalf version;
	// relative offset from next field to
	// program statement
	uword prolog_length;
	ubyte minimum_inकाष्ठाion_length;
	ubyte शेष_is_sपंचांगt;
	// line_base - see DWARF 2 specs
	sbyte line_base;
	// line_range - see DWARF 2 specs
	ubyte line_range;
	// number of opcode + 1
	ubyte opcode_base;
	/* follow the array of opcode args nr: ubytes [nr_opcode_base] */
	/* follow the search directories index, zero terminated string
	 * terminated by an empty string.
	 */
	/* follow an array of अणु filename, LEB128, LEB128, LEB128 पूर्ण, first is
	 * the directory index entry, 0 means current directory, then mसमय
	 * and filesize, last entry is followed by en empty string.
	 */
	/* follow the first program statement */
पूर्ण __packed;

/* DWARF 2 spec talk only about one possible compilation unit header जबतक
 * binutils can handle two flavours of dwarf 2, 32 and 64 bits, this is not
 * related to the used arch, an ELF 32 can hold more than 4 Go of debug
 * inक्रमmation. For now we handle only DWARF 2 32 bits comp unit. It'll only
 * become a problem अगर we generate more than 4GB of debug inक्रमmation.
 */
काष्ठा compilation_unit_header अणु
	uword total_length;
	uhalf version;
	uword debug_abbrev_offset;
	ubyte poपूर्णांकer_size;
पूर्ण __packed;

#घोषणा DW_LNS_num_opcode (DW_LNS_set_isa + 1)

/* field filled at run समय are marked with -1 */
अटल काष्ठा debug_line_header स्थिर शेष_debug_line_header = अणु
	.total_length = -1,
	.version = 2,
	.prolog_length = -1,
	.minimum_inकाष्ठाion_length = 1,	/* could be better when min inकाष्ठाion size != 1 */
	.शेष_is_sपंचांगt = 1,	/* we करोn't take care about basic block */
	.line_base = -5,	/* sensible value क्रम line base ... */
	.line_range = -14,     /* ... and line range are guessed अटलally */
	.opcode_base = DW_LNS_num_opcode
पूर्ण;

अटल ubyte standard_opcode_length[] =
अणु
	0, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 1
पूर्ण;
#अगर 0
अणु
	[DW_LNS_advance_pc]   = 1,
	[DW_LNS_advance_line] = 1,
	[DW_LNS_set_file] =  1,
	[DW_LNS_set_column] = 1,
	[DW_LNS_fixed_advance_pc] = 1,
	[DW_LNS_set_isa] = 1,
पूर्ण;
#पूर्ण_अगर

/* field filled at run समय are marked with -1 */
अटल काष्ठा compilation_unit_header शेष_comp_unit_header = अणु
	.total_length = -1,
	.version = 2,
	.debug_abbrev_offset = 0,     /* we reuse the same abbrev entries क्रम all comp unit */
	.poपूर्णांकer_size = माप(व्योम *)
पूर्ण;

अटल व्योम emit_uword(काष्ठा buffer_ext *be, uword data)
अणु
	buffer_ext_add(be, &data, माप(uword));
पूर्ण

अटल व्योम emit_string(काष्ठा buffer_ext *be, स्थिर अक्षर *s)
अणु
	buffer_ext_add(be, (व्योम *)s, म_माप(s) + 1);
पूर्ण

अटल व्योम emit_अचिन्हित_LEB128(काष्ठा buffer_ext *be,
				 अचिन्हित दीर्घ data)
अणु
	करो अणु
		ubyte cur = data & 0x7F;
		data >>= 7;
		अगर (data)
			cur |= 0x80;
		buffer_ext_add(be, &cur, 1);
	पूर्ण जबतक (data);
पूर्ण

अटल व्योम emit_चिन्हित_LEB128(काष्ठा buffer_ext *be, दीर्घ data)
अणु
	पूर्णांक more = 1;
	पूर्णांक negative = data < 0;
	पूर्णांक size = माप(दीर्घ) * अक्षर_बिट;
	जबतक (more) अणु
		ubyte cur = data & 0x7F;
		data >>= 7;
		अगर (negative)
			data |= - (1 << (size - 7));
		अगर ((data == 0 && !(cur & 0x40)) ||
		    (data == -1l && (cur & 0x40)))
			more = 0;
		अन्यथा
			cur |= 0x80;
		buffer_ext_add(be, &cur, 1);
	पूर्ण
पूर्ण

अटल व्योम emit_extended_opcode(काष्ठा buffer_ext *be, ubyte opcode,
				 व्योम *data, माप_प्रकार data_len)
अणु
	buffer_ext_add(be, (अक्षर *)"", 1);

	emit_अचिन्हित_LEB128(be, data_len + 1);

	buffer_ext_add(be, &opcode, 1);
	buffer_ext_add(be, data, data_len);
पूर्ण

अटल व्योम emit_opcode(काष्ठा buffer_ext *be, ubyte opcode)
अणु
	buffer_ext_add(be, &opcode, 1);
पूर्ण

अटल व्योम emit_opcode_चिन्हित(काष्ठा buffer_ext  *be,
			       ubyte opcode, दीर्घ data)
अणु
	buffer_ext_add(be, &opcode, 1);
	emit_चिन्हित_LEB128(be, data);
पूर्ण

अटल व्योम emit_opcode_अचिन्हित(काष्ठा buffer_ext *be, ubyte opcode,
				 अचिन्हित दीर्घ data)
अणु
	buffer_ext_add(be, &opcode, 1);
	emit_अचिन्हित_LEB128(be, data);
पूर्ण

अटल व्योम emit_advance_pc(काष्ठा buffer_ext *be, अचिन्हित दीर्घ delta_pc)
अणु
	emit_opcode_अचिन्हित(be, DW_LNS_advance_pc, delta_pc);
पूर्ण

अटल व्योम emit_advance_lineno(काष्ठा buffer_ext  *be, दीर्घ delta_lineno)
अणु
	emit_opcode_चिन्हित(be, DW_LNS_advance_line, delta_lineno);
पूर्ण

अटल व्योम emit_lne_end_of_sequence(काष्ठा buffer_ext *be)
अणु
	emit_extended_opcode(be, DW_LNE_end_sequence, शून्य, 0);
पूर्ण

अटल व्योम emit_set_file(काष्ठा buffer_ext *be, अचिन्हित दीर्घ idx)
अणु
	emit_opcode_अचिन्हित(be, DW_LNS_set_file, idx);
पूर्ण

अटल व्योम emit_lne_define_filename(काष्ठा buffer_ext *be,
				     स्थिर अक्षर *filename)
अणु
	buffer_ext_add(be, (व्योम *)"", 1);

	/* LNE field, म_माप(filename) + zero termination, 3 bytes क्रम: the dir entry, बारtamp, filesize */
	emit_अचिन्हित_LEB128(be, म_माप(filename) + 5);
	emit_opcode(be, DW_LNE_define_file);
	emit_string(be, filename);
	/* directory index 0=करो not know */
        emit_अचिन्हित_LEB128(be, 0);
	/* last modअगरication date on file 0=करो not know */
        emit_अचिन्हित_LEB128(be, 0);
	/* filesize 0=करो not know */
        emit_अचिन्हित_LEB128(be, 0);
पूर्ण

अटल व्योम emit_lne_set_address(काष्ठा buffer_ext *be,
				 व्योम *address)
अणु
	emit_extended_opcode(be, DW_LNE_set_address, &address, माप(अचिन्हित दीर्घ));
पूर्ण

अटल ubyte get_special_opcode(काष्ठा debug_entry *ent,
				अचिन्हित पूर्णांक last_line,
				अचिन्हित दीर्घ last_vma)
अणु
	अचिन्हित पूर्णांक temp;
	अचिन्हित दीर्घ delta_addr;

	/*
	 * delta from line_base
	 */
	temp = (ent->lineno - last_line) - शेष_debug_line_header.line_base;

	अगर (temp >= शेष_debug_line_header.line_range)
		वापस 0;

	/*
	 * delta of addresses
	 */
	delta_addr = (ent->addr - last_vma) / शेष_debug_line_header.minimum_inकाष्ठाion_length;

	/* This is not sufficient to ensure opcode will be in [0-256] but
	 * sufficient to ensure when summing with the delta lineno we will
	 * not overflow the अचिन्हित दीर्घ opcode */

	अगर (delta_addr <= 256 / शेष_debug_line_header.line_range) अणु
		अचिन्हित दीर्घ opcode = temp +
			(delta_addr * शेष_debug_line_header.line_range) +
			शेष_debug_line_header.opcode_base;

		वापस opcode <= 255 ? opcode : 0;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम emit_lineno_info(काष्ठा buffer_ext *be,
			     काष्ठा debug_entry *ent, माप_प्रकार nr_entry,
			     अचिन्हित दीर्घ code_addr)
अणु
	माप_प्रकार i;

	/*
	 * Machine state at start of a statement program
	 * address = 0
	 * file    = 1
	 * line    = 1
	 * column  = 0
	 * is_sपंचांगt = शेष_is_sपंचांगt as given in the debug_line_header
	 * basic block = 0
	 * end sequence = 0
	 */

	/* start state of the state machine we take care of */
	अचिन्हित दीर्घ last_vma = 0;
	अक्षर स्थिर  *cur_filename = शून्य;
	अचिन्हित दीर्घ cur_file_idx = 0;
	पूर्णांक last_line = 1;

	emit_lne_set_address(be, (व्योम *)code_addr);

	क्रम (i = 0; i < nr_entry; i++, ent = debug_entry_next(ent)) अणु
		पूर्णांक need_copy = 0;
		ubyte special_opcode;

		/*
		 * check अगर filename changed, अगर so add it
		 */
		अगर (!cur_filename || म_भेद(cur_filename, ent->name)) अणु
			emit_lne_define_filename(be, ent->name);
			cur_filename = ent->name;
			emit_set_file(be, ++cur_file_idx);
			need_copy = 1;
		पूर्ण

		special_opcode = get_special_opcode(ent, last_line, last_vma);
		अगर (special_opcode != 0) अणु
			last_line = ent->lineno;
			last_vma  = ent->addr;
			emit_opcode(be, special_opcode);
		पूर्ण अन्यथा अणु
			/*
			 * lines dअगरfer, emit line delta
			 */
			अगर (last_line != ent->lineno) अणु
				emit_advance_lineno(be, ent->lineno - last_line);
				last_line = ent->lineno;
				need_copy = 1;
			पूर्ण
			/*
			 * addresses dअगरfer, emit address delta
			 */
			अगर (last_vma != ent->addr) अणु
				emit_advance_pc(be, ent->addr - last_vma);
				last_vma = ent->addr;
				need_copy = 1;
			पूर्ण
			/*
			 * add new row to matrix
			 */
			अगर (need_copy)
				emit_opcode(be, DW_LNS_copy);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम add_debug_line(काष्ठा buffer_ext *be,
	काष्ठा debug_entry *ent, माप_प्रकार nr_entry,
	अचिन्हित दीर्घ code_addr)
अणु
	काष्ठा debug_line_header * dbg_header;
	माप_प्रकार old_size;

	old_size = buffer_ext_size(be);

	buffer_ext_add(be, (व्योम *)&शेष_debug_line_header,
		 माप(शेष_debug_line_header));

	buffer_ext_add(be, &standard_opcode_length,  माप(standard_opcode_length));

	// empty directory entry
	buffer_ext_add(be, (व्योम *)"", 1);

	// empty filename directory
	buffer_ext_add(be, (व्योम *)"", 1);

	dbg_header = buffer_ext_addr(be) + old_size;
	dbg_header->prolog_length = (buffer_ext_size(be) - old_size) -
		दुरत्व(काष्ठा debug_line_header, minimum_inकाष्ठाion_length);

	emit_lineno_info(be, ent, nr_entry, code_addr);

	emit_lne_end_of_sequence(be);

	dbg_header = buffer_ext_addr(be) + old_size;
	dbg_header->total_length = (buffer_ext_size(be) - old_size) -
		दुरत्व(काष्ठा debug_line_header, version);
पूर्ण

अटल व्योम
add_debug_abbrev(काष्ठा buffer_ext *be)
अणु
        emit_अचिन्हित_LEB128(be, 1);
        emit_अचिन्हित_LEB128(be, DW_TAG_compile_unit);
        emit_अचिन्हित_LEB128(be, DW_CHILDREN_yes);
        emit_अचिन्हित_LEB128(be, DW_AT_sपंचांगt_list);
        emit_अचिन्हित_LEB128(be, DW_FORM_data4);
        emit_अचिन्हित_LEB128(be, 0);
        emit_अचिन्हित_LEB128(be, 0);
        emit_अचिन्हित_LEB128(be, 0);
पूर्ण

अटल व्योम
add_compilation_unit(काष्ठा buffer_ext *be,
		     माप_प्रकार offset_debug_line)
अणु
	काष्ठा compilation_unit_header *comp_unit_header;
	माप_प्रकार old_size = buffer_ext_size(be);

	buffer_ext_add(be, &शेष_comp_unit_header,
		       माप(शेष_comp_unit_header));

	emit_अचिन्हित_LEB128(be, 1);
	emit_uword(be, offset_debug_line);

	comp_unit_header = buffer_ext_addr(be) + old_size;
	comp_unit_header->total_length = (buffer_ext_size(be) - old_size) -
		दुरत्व(काष्ठा compilation_unit_header, version);
पूर्ण

अटल पूर्णांक
jit_process_debug_info(uपूर्णांक64_t code_addr,
		       व्योम *debug, पूर्णांक nr_debug_entries,
		       काष्ठा buffer_ext *dl,
		       काष्ठा buffer_ext *da,
		       काष्ठा buffer_ext *di)
अणु
	काष्ठा debug_entry *ent = debug;
	पूर्णांक i;

	क्रम (i = 0; i < nr_debug_entries; i++) अणु
		ent->addr = ent->addr - code_addr;
		ent = debug_entry_next(ent);
	पूर्ण
	add_compilation_unit(di, buffer_ext_size(dl));
	add_debug_line(dl, debug, nr_debug_entries, GEN_ELF_TEXT_OFFSET);
	add_debug_abbrev(da);
	अगर (0) buffer_ext_dump(da, "abbrev");

	वापस 0;
पूर्ण

पूर्णांक
jit_add_debug_info(Elf *e, uपूर्णांक64_t code_addr, व्योम *debug, पूर्णांक nr_debug_entries)
अणु
	Elf_Data *d;
	Elf_Scn *scn;
	Elf_Shdr *shdr;
	काष्ठा buffer_ext dl, di, da;
	पूर्णांक ret;

	buffer_ext_init(&dl);
	buffer_ext_init(&di);
	buffer_ext_init(&da);

	ret = jit_process_debug_info(code_addr, debug, nr_debug_entries, &dl, &da, &di);
	अगर (ret)
		वापस -1;
	/*
	 * setup .debug_line section
	 */
	scn = elf_newscn(e);
	अगर (!scn) अणु
		warnx("cannot create section");
		वापस -1;
	पूर्ण

	d = elf_newdata(scn);
	अगर (!d) अणु
		warnx("cannot get new data");
		वापस -1;
	पूर्ण

	d->d_align = 1;
	d->d_off = 0LL;
	d->d_buf = buffer_ext_addr(&dl);
	d->d_type = ELF_T_BYTE;
	d->d_size = buffer_ext_size(&dl);
	d->d_version = EV_CURRENT;

	shdr = elf_माला_लोhdr(scn);
	अगर (!shdr) अणु
		warnx("cannot get section header");
		वापस -1;
	पूर्ण

	shdr->sh_name = 52; /* .debug_line */
	shdr->sh_type = SHT_PROGBITS;
	shdr->sh_addr = 0; /* must be zero or == sh_offset -> dynamic object */
	shdr->sh_flags = 0;
	shdr->sh_entsize = 0;

	/*
	 * setup .debug_info section
	 */
	scn = elf_newscn(e);
	अगर (!scn) अणु
		warnx("cannot create section");
		वापस -1;
	पूर्ण

	d = elf_newdata(scn);
	अगर (!d) अणु
		warnx("cannot get new data");
		वापस -1;
	पूर्ण

	d->d_align = 1;
	d->d_off = 0LL;
	d->d_buf = buffer_ext_addr(&di);
	d->d_type = ELF_T_BYTE;
	d->d_size = buffer_ext_size(&di);
	d->d_version = EV_CURRENT;

	shdr = elf_माला_लोhdr(scn);
	अगर (!shdr) अणु
		warnx("cannot get section header");
		वापस -1;
	पूर्ण

	shdr->sh_name = 64; /* .debug_info */
	shdr->sh_type = SHT_PROGBITS;
	shdr->sh_addr = 0; /* must be zero or == sh_offset -> dynamic object */
	shdr->sh_flags = 0;
	shdr->sh_entsize = 0;

	/*
	 * setup .debug_abbrev section
	 */
	scn = elf_newscn(e);
	अगर (!scn) अणु
		warnx("cannot create section");
		वापस -1;
	पूर्ण

	d = elf_newdata(scn);
	अगर (!d) अणु
		warnx("cannot get new data");
		वापस -1;
	पूर्ण

	d->d_align = 1;
	d->d_off = 0LL;
	d->d_buf = buffer_ext_addr(&da);
	d->d_type = ELF_T_BYTE;
	d->d_size = buffer_ext_size(&da);
	d->d_version = EV_CURRENT;

	shdr = elf_माला_लोhdr(scn);
	अगर (!shdr) अणु
		warnx("cannot get section header");
		वापस -1;
	पूर्ण

	shdr->sh_name = 76; /* .debug_info */
	shdr->sh_type = SHT_PROGBITS;
	shdr->sh_addr = 0; /* must be zero or == sh_offset -> dynamic object */
	shdr->sh_flags = 0;
	shdr->sh_entsize = 0;

	/*
	 * now we update the ELF image with all the sections
	 */
	अगर (elf_update(e, ELF_C_WRITE) < 0) अणु
		warnx("elf_update debug failed");
		वापस -1;
	पूर्ण
	वापस 0;
पूर्ण
