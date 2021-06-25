<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0-or-later OR BSD-2-Clause)
/*
 * libfdt - Flat Device Tree manipulation
 * Copyright (C) 2006 David Gibson, IBM Corporation.
 */
#समावेश "libfdt_env.h"

#समावेश <fdt.h>
#समावेश <libfdt.h>

#समावेश "libfdt_internal.h"

अटल पूर्णांक fdt_sw_probe_(व्योम *fdt)
अणु
	अगर (!can_assume(VALID_INPUT)) अणु
		अगर (fdt_magic(fdt) == FDT_MAGIC)
			वापस -FDT_ERR_BADSTATE;
		अन्यथा अगर (fdt_magic(fdt) != FDT_SW_MAGIC)
			वापस -FDT_ERR_BADMAGIC;
	पूर्ण

	वापस 0;
पूर्ण

#घोषणा FDT_SW_PROBE(fdt) \
	अणु \
		पूर्णांक err; \
		अगर ((err = fdt_sw_probe_(fdt)) != 0) \
			वापस err; \
	पूर्ण

/* 'memrsv' state:	Initial state after fdt_create()
 *
 * Allowed functions:
 *	fdt_add_reservemap_entry()
 *	fdt_finish_reservemap()		[moves to 'struct' state]
 */
अटल पूर्णांक fdt_sw_probe_memrsv_(व्योम *fdt)
अणु
	पूर्णांक err = fdt_sw_probe_(fdt);
	अगर (err)
		वापस err;

	अगर (!can_assume(VALID_INPUT) && fdt_off_dt_strings(fdt) != 0)
		वापस -FDT_ERR_BADSTATE;
	वापस 0;
पूर्ण

#घोषणा FDT_SW_PROBE_MEMRSV(fdt) \
	अणु \
		पूर्णांक err; \
		अगर ((err = fdt_sw_probe_memrsv_(fdt)) != 0) \
			वापस err; \
	पूर्ण

/* 'struct' state:	Enter this state after fdt_finish_reservemap()
 *
 * Allowed functions:
 *	fdt_begin_node()
 *	fdt_end_node()
 *	fdt_property*()
 *	fdt_finish()			[moves to 'complete' state]
 */
अटल पूर्णांक fdt_sw_probe_काष्ठा_(व्योम *fdt)
अणु
	पूर्णांक err = fdt_sw_probe_(fdt);
	अगर (err)
		वापस err;

	अगर (!can_assume(VALID_INPUT) &&
	    fdt_off_dt_strings(fdt) != fdt_totalsize(fdt))
		वापस -FDT_ERR_BADSTATE;
	वापस 0;
पूर्ण

#घोषणा FDT_SW_PROBE_STRUCT(fdt) \
	अणु \
		पूर्णांक err; \
		अगर ((err = fdt_sw_probe_काष्ठा_(fdt)) != 0) \
			वापस err; \
	पूर्ण

अटल अंतरभूत uपूर्णांक32_t sw_flags(व्योम *fdt)
अणु
	/* निश्चित: (fdt_magic(fdt) == FDT_SW_MAGIC) */
	वापस fdt_last_comp_version(fdt);
पूर्ण

/* 'complete' state:	Enter this state after fdt_finish()
 *
 * Allowed functions: none
 */

अटल व्योम *fdt_grab_space_(व्योम *fdt, माप_प्रकार len)
अणु
	अचिन्हित पूर्णांक offset = fdt_size_dt_काष्ठा(fdt);
	अचिन्हित पूर्णांक spaceleft;

	spaceleft = fdt_totalsize(fdt) - fdt_off_dt_काष्ठा(fdt)
		- fdt_size_dt_strings(fdt);

	अगर ((offset + len < offset) || (offset + len > spaceleft))
		वापस शून्य;

	fdt_set_size_dt_काष्ठा(fdt, offset + len);
	वापस fdt_offset_ptr_w_(fdt, offset);
पूर्ण

पूर्णांक fdt_create_with_flags(व्योम *buf, पूर्णांक bufsize, uपूर्णांक32_t flags)
अणु
	स्थिर पूर्णांक hdrsize = FDT_ALIGN(माप(काष्ठा fdt_header),
				      माप(काष्ठा fdt_reserve_entry));
	व्योम *fdt = buf;

	अगर (bufsize < hdrsize)
		वापस -FDT_ERR_NOSPACE;

	अगर (flags & ~FDT_CREATE_FLAGS_ALL)
		वापस -FDT_ERR_BADFLAGS;

	स_रखो(buf, 0, bufsize);

	/*
	 * magic and last_comp_version keep पूर्णांकermediate state during the fdt
	 * creation process, which is replaced with the proper FDT क्रमmat by
	 * fdt_finish().
	 *
	 * flags should be accessed with sw_flags().
	 */
	fdt_set_magic(fdt, FDT_SW_MAGIC);
	fdt_set_version(fdt, FDT_LAST_SUPPORTED_VERSION);
	fdt_set_last_comp_version(fdt, flags);

	fdt_set_totalsize(fdt,  bufsize);

	fdt_set_off_mem_rsvmap(fdt, hdrsize);
	fdt_set_off_dt_काष्ठा(fdt, fdt_off_mem_rsvmap(fdt));
	fdt_set_off_dt_strings(fdt, 0);

	वापस 0;
पूर्ण

पूर्णांक fdt_create(व्योम *buf, पूर्णांक bufsize)
अणु
	वापस fdt_create_with_flags(buf, bufsize, 0);
पूर्ण

पूर्णांक fdt_resize(व्योम *fdt, व्योम *buf, पूर्णांक bufsize)
अणु
	माप_प्रकार headsize, tailsize;
	अक्षर *oldtail, *newtail;

	FDT_SW_PROBE(fdt);

	अगर (bufsize < 0)
		वापस -FDT_ERR_NOSPACE;

	headsize = fdt_off_dt_काष्ठा(fdt) + fdt_size_dt_काष्ठा(fdt);
	tailsize = fdt_size_dt_strings(fdt);

	अगर (!can_assume(VALID_DTB) &&
	    headsize + tailsize > fdt_totalsize(fdt))
		वापस -FDT_ERR_INTERNAL;

	अगर ((headsize + tailsize) > (अचिन्हित)bufsize)
		वापस -FDT_ERR_NOSPACE;

	oldtail = (अक्षर *)fdt + fdt_totalsize(fdt) - tailsize;
	newtail = (अक्षर *)buf + bufsize - tailsize;

	/* Two हालs to aव्योम clobbering data अगर the old and new
	 * buffers partially overlap */
	अगर (buf <= fdt) अणु
		स_हटाओ(buf, fdt, headsize);
		स_हटाओ(newtail, oldtail, tailsize);
	पूर्ण अन्यथा अणु
		स_हटाओ(newtail, oldtail, tailsize);
		स_हटाओ(buf, fdt, headsize);
	पूर्ण

	fdt_set_totalsize(buf, bufsize);
	अगर (fdt_off_dt_strings(buf))
		fdt_set_off_dt_strings(buf, bufsize);

	वापस 0;
पूर्ण

पूर्णांक fdt_add_reservemap_entry(व्योम *fdt, uपूर्णांक64_t addr, uपूर्णांक64_t size)
अणु
	काष्ठा fdt_reserve_entry *re;
	पूर्णांक offset;

	FDT_SW_PROBE_MEMRSV(fdt);

	offset = fdt_off_dt_काष्ठा(fdt);
	अगर ((offset + माप(*re)) > fdt_totalsize(fdt))
		वापस -FDT_ERR_NOSPACE;

	re = (काष्ठा fdt_reserve_entry *)((अक्षर *)fdt + offset);
	re->address = cpu_to_fdt64(addr);
	re->size = cpu_to_fdt64(size);

	fdt_set_off_dt_काष्ठा(fdt, offset + माप(*re));

	वापस 0;
पूर्ण

पूर्णांक fdt_finish_reservemap(व्योम *fdt)
अणु
	पूर्णांक err = fdt_add_reservemap_entry(fdt, 0, 0);

	अगर (err)
		वापस err;

	fdt_set_off_dt_strings(fdt, fdt_totalsize(fdt));
	वापस 0;
पूर्ण

पूर्णांक fdt_begin_node(व्योम *fdt, स्थिर अक्षर *name)
अणु
	काष्ठा fdt_node_header *nh;
	पूर्णांक namelen;

	FDT_SW_PROBE_STRUCT(fdt);

	namelen = म_माप(name) + 1;
	nh = fdt_grab_space_(fdt, माप(*nh) + FDT_TAGALIGN(namelen));
	अगर (! nh)
		वापस -FDT_ERR_NOSPACE;

	nh->tag = cpu_to_fdt32(FDT_BEGIN_NODE);
	स_नकल(nh->name, name, namelen);
	वापस 0;
पूर्ण

पूर्णांक fdt_end_node(व्योम *fdt)
अणु
	fdt32_t *en;

	FDT_SW_PROBE_STRUCT(fdt);

	en = fdt_grab_space_(fdt, FDT_TAGSIZE);
	अगर (! en)
		वापस -FDT_ERR_NOSPACE;

	*en = cpu_to_fdt32(FDT_END_NODE);
	वापस 0;
पूर्ण

अटल पूर्णांक fdt_add_string_(व्योम *fdt, स्थिर अक्षर *s)
अणु
	अक्षर *strtab = (अक्षर *)fdt + fdt_totalsize(fdt);
	अचिन्हित पूर्णांक strtअसलize = fdt_size_dt_strings(fdt);
	अचिन्हित पूर्णांक len = म_माप(s) + 1;
	अचिन्हित पूर्णांक काष्ठा_top, offset;

	offset = strtअसलize + len;
	काष्ठा_top = fdt_off_dt_काष्ठा(fdt) + fdt_size_dt_काष्ठा(fdt);
	अगर (fdt_totalsize(fdt) - offset < काष्ठा_top)
		वापस 0; /* no more room :( */

	स_नकल(strtab - offset, s, len);
	fdt_set_size_dt_strings(fdt, strtअसलize + len);
	वापस -offset;
पूर्ण

/* Must only be used to roll back in हाल of error */
अटल व्योम fdt_del_last_string_(व्योम *fdt, स्थिर अक्षर *s)
अणु
	पूर्णांक strtअसलize = fdt_size_dt_strings(fdt);
	पूर्णांक len = म_माप(s) + 1;

	fdt_set_size_dt_strings(fdt, strtअसलize - len);
पूर्ण

अटल पूर्णांक fdt_find_add_string_(व्योम *fdt, स्थिर अक्षर *s, पूर्णांक *allocated)
अणु
	अक्षर *strtab = (अक्षर *)fdt + fdt_totalsize(fdt);
	पूर्णांक strtअसलize = fdt_size_dt_strings(fdt);
	स्थिर अक्षर *p;

	*allocated = 0;

	p = fdt_find_string_(strtab - strtअसलize, strtअसलize, s);
	अगर (p)
		वापस p - strtab;

	*allocated = 1;

	वापस fdt_add_string_(fdt, s);
पूर्ण

पूर्णांक fdt_property_placeholder(व्योम *fdt, स्थिर अक्षर *name, पूर्णांक len, व्योम **valp)
अणु
	काष्ठा fdt_property *prop;
	पूर्णांक nameoff;
	पूर्णांक allocated;

	FDT_SW_PROBE_STRUCT(fdt);

	/* String de-duplication can be slow, _NO_NAME_DEDUP skips it */
	अगर (sw_flags(fdt) & FDT_CREATE_FLAG_NO_NAME_DEDUP) अणु
		allocated = 1;
		nameoff = fdt_add_string_(fdt, name);
	पूर्ण अन्यथा अणु
		nameoff = fdt_find_add_string_(fdt, name, &allocated);
	पूर्ण
	अगर (nameoff == 0)
		वापस -FDT_ERR_NOSPACE;

	prop = fdt_grab_space_(fdt, माप(*prop) + FDT_TAGALIGN(len));
	अगर (! prop) अणु
		अगर (allocated)
			fdt_del_last_string_(fdt, name);
		वापस -FDT_ERR_NOSPACE;
	पूर्ण

	prop->tag = cpu_to_fdt32(FDT_PROP);
	prop->nameoff = cpu_to_fdt32(nameoff);
	prop->len = cpu_to_fdt32(len);
	*valp = prop->data;
	वापस 0;
पूर्ण

पूर्णांक fdt_property(व्योम *fdt, स्थिर अक्षर *name, स्थिर व्योम *val, पूर्णांक len)
अणु
	व्योम *ptr;
	पूर्णांक ret;

	ret = fdt_property_placeholder(fdt, name, len, &ptr);
	अगर (ret)
		वापस ret;
	स_नकल(ptr, val, len);
	वापस 0;
पूर्ण

पूर्णांक fdt_finish(व्योम *fdt)
अणु
	अक्षर *p = (अक्षर *)fdt;
	fdt32_t *end;
	पूर्णांक oldstroffset, newstroffset;
	uपूर्णांक32_t tag;
	पूर्णांक offset, nextoffset;

	FDT_SW_PROBE_STRUCT(fdt);

	/* Add terminator */
	end = fdt_grab_space_(fdt, माप(*end));
	अगर (! end)
		वापस -FDT_ERR_NOSPACE;
	*end = cpu_to_fdt32(FDT_END);

	/* Relocate the string table */
	oldstroffset = fdt_totalsize(fdt) - fdt_size_dt_strings(fdt);
	newstroffset = fdt_off_dt_काष्ठा(fdt) + fdt_size_dt_काष्ठा(fdt);
	स_हटाओ(p + newstroffset, p + oldstroffset, fdt_size_dt_strings(fdt));
	fdt_set_off_dt_strings(fdt, newstroffset);

	/* Walk the काष्ठाure, correcting string offsets */
	offset = 0;
	जबतक ((tag = fdt_next_tag(fdt, offset, &nextoffset)) != FDT_END) अणु
		अगर (tag == FDT_PROP) अणु
			काष्ठा fdt_property *prop =
				fdt_offset_ptr_w_(fdt, offset);
			पूर्णांक nameoff;

			nameoff = fdt32_to_cpu(prop->nameoff);
			nameoff += fdt_size_dt_strings(fdt);
			prop->nameoff = cpu_to_fdt32(nameoff);
		पूर्ण
		offset = nextoffset;
	पूर्ण
	अगर (nextoffset < 0)
		वापस nextoffset;

	/* Finally, adjust the header */
	fdt_set_totalsize(fdt, newstroffset + fdt_size_dt_strings(fdt));

	/* And fix up fields that were keeping पूर्णांकermediate state. */
	fdt_set_last_comp_version(fdt, FDT_LAST_COMPATIBLE_VERSION);
	fdt_set_magic(fdt, FDT_MAGIC);

	वापस 0;
पूर्ण
