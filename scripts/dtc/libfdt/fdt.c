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

/*
 * Minimal sanity check क्रम a पढ़ो-only tree. fdt_ro_probe_() checks
 * that the given buffer contains what appears to be a flattened
 * device tree with sane inक्रमmation in its header.
 */
पूर्णांक32_t fdt_ro_probe_(स्थिर व्योम *fdt)
अणु
	uपूर्णांक32_t totalsize = fdt_totalsize(fdt);

	अगर (can_assume(VALID_DTB))
		वापस totalsize;

	/* The device tree must be at an 8-byte aligned address */
	अगर ((uपूर्णांकptr_t)fdt & 7)
		वापस -FDT_ERR_ALIGNMENT;

	अगर (fdt_magic(fdt) == FDT_MAGIC) अणु
		/* Complete tree */
		अगर (!can_assume(LATEST)) अणु
			अगर (fdt_version(fdt) < FDT_FIRST_SUPPORTED_VERSION)
				वापस -FDT_ERR_BADVERSION;
			अगर (fdt_last_comp_version(fdt) >
					FDT_LAST_SUPPORTED_VERSION)
				वापस -FDT_ERR_BADVERSION;
		पूर्ण
	पूर्ण अन्यथा अगर (fdt_magic(fdt) == FDT_SW_MAGIC) अणु
		/* Unfinished sequential-ग_लिखो blob */
		अगर (!can_assume(VALID_INPUT) && fdt_size_dt_काष्ठा(fdt) == 0)
			वापस -FDT_ERR_BADSTATE;
	पूर्ण अन्यथा अणु
		वापस -FDT_ERR_BADMAGIC;
	पूर्ण

	अगर (totalsize < INT32_MAX)
		वापस totalsize;
	अन्यथा
		वापस -FDT_ERR_TRUNCATED;
पूर्ण

अटल पूर्णांक check_off_(uपूर्णांक32_t hdrsize, uपूर्णांक32_t totalsize, uपूर्णांक32_t off)
अणु
	वापस (off >= hdrsize) && (off <= totalsize);
पूर्ण

अटल पूर्णांक check_block_(uपूर्णांक32_t hdrsize, uपूर्णांक32_t totalsize,
			uपूर्णांक32_t base, uपूर्णांक32_t size)
अणु
	अगर (!check_off_(hdrsize, totalsize, base))
		वापस 0; /* block start out of bounds */
	अगर ((base + size) < base)
		वापस 0; /* overflow */
	अगर (!check_off_(hdrsize, totalsize, base + size))
		वापस 0; /* block end out of bounds */
	वापस 1;
पूर्ण

माप_प्रकार fdt_header_size_(uपूर्णांक32_t version)
अणु
	अगर (version <= 1)
		वापस FDT_V1_SIZE;
	अन्यथा अगर (version <= 2)
		वापस FDT_V2_SIZE;
	अन्यथा अगर (version <= 3)
		वापस FDT_V3_SIZE;
	अन्यथा अगर (version <= 16)
		वापस FDT_V16_SIZE;
	अन्यथा
		वापस FDT_V17_SIZE;
पूर्ण

माप_प्रकार fdt_header_size(स्थिर व्योम *fdt)
अणु
	वापस can_assume(LATEST) ? FDT_V17_SIZE :
		fdt_header_size_(fdt_version(fdt));
पूर्ण

पूर्णांक fdt_check_header(स्थिर व्योम *fdt)
अणु
	माप_प्रकार hdrsize;

	अगर (fdt_magic(fdt) != FDT_MAGIC)
		वापस -FDT_ERR_BADMAGIC;
	अगर (!can_assume(LATEST)) अणु
		अगर ((fdt_version(fdt) < FDT_FIRST_SUPPORTED_VERSION)
		    || (fdt_last_comp_version(fdt) >
			FDT_LAST_SUPPORTED_VERSION))
			वापस -FDT_ERR_BADVERSION;
		अगर (fdt_version(fdt) < fdt_last_comp_version(fdt))
			वापस -FDT_ERR_BADVERSION;
	पूर्ण
	hdrsize = fdt_header_size(fdt);
	अगर (!can_assume(VALID_DTB)) अणु

		अगर ((fdt_totalsize(fdt) < hdrsize)
		    || (fdt_totalsize(fdt) > पूर्णांक_उच्च))
			वापस -FDT_ERR_TRUNCATED;

		/* Bounds check memrsv block */
		अगर (!check_off_(hdrsize, fdt_totalsize(fdt),
				fdt_off_mem_rsvmap(fdt)))
			वापस -FDT_ERR_TRUNCATED;
	पूर्ण

	अगर (!can_assume(VALID_DTB)) अणु
		/* Bounds check काष्ठाure block */
		अगर (!can_assume(LATEST) && fdt_version(fdt) < 17) अणु
			अगर (!check_off_(hdrsize, fdt_totalsize(fdt),
					fdt_off_dt_काष्ठा(fdt)))
				वापस -FDT_ERR_TRUNCATED;
		पूर्ण अन्यथा अणु
			अगर (!check_block_(hdrsize, fdt_totalsize(fdt),
					  fdt_off_dt_काष्ठा(fdt),
					  fdt_size_dt_काष्ठा(fdt)))
				वापस -FDT_ERR_TRUNCATED;
		पूर्ण

		/* Bounds check strings block */
		अगर (!check_block_(hdrsize, fdt_totalsize(fdt),
				  fdt_off_dt_strings(fdt),
				  fdt_size_dt_strings(fdt)))
			वापस -FDT_ERR_TRUNCATED;
	पूर्ण

	वापस 0;
पूर्ण

स्थिर व्योम *fdt_offset_ptr(स्थिर व्योम *fdt, पूर्णांक offset, अचिन्हित पूर्णांक len)
अणु
	अचिन्हित पूर्णांक uoffset = offset;
	अचिन्हित पूर्णांक असलoffset = offset + fdt_off_dt_काष्ठा(fdt);

	अगर (offset < 0)
		वापस शून्य;

	अगर (!can_assume(VALID_INPUT))
		अगर ((असलoffset < uoffset)
		    || ((असलoffset + len) < असलoffset)
		    || (असलoffset + len) > fdt_totalsize(fdt))
			वापस शून्य;

	अगर (can_assume(LATEST) || fdt_version(fdt) >= 0x11)
		अगर (((uoffset + len) < uoffset)
		    || ((offset + len) > fdt_size_dt_काष्ठा(fdt)))
			वापस शून्य;

	वापस fdt_offset_ptr_(fdt, offset);
पूर्ण

uपूर्णांक32_t fdt_next_tag(स्थिर व्योम *fdt, पूर्णांक startoffset, पूर्णांक *nextoffset)
अणु
	स्थिर fdt32_t *tagp, *lenp;
	uपूर्णांक32_t tag;
	पूर्णांक offset = startoffset;
	स्थिर अक्षर *p;

	*nextoffset = -FDT_ERR_TRUNCATED;
	tagp = fdt_offset_ptr(fdt, offset, FDT_TAGSIZE);
	अगर (!can_assume(VALID_DTB) && !tagp)
		वापस FDT_END; /* premature end */
	tag = fdt32_to_cpu(*tagp);
	offset += FDT_TAGSIZE;

	*nextoffset = -FDT_ERR_BADSTRUCTURE;
	चयन (tag) अणु
	हाल FDT_BEGIN_NODE:
		/* skip name */
		करो अणु
			p = fdt_offset_ptr(fdt, offset++, 1);
		पूर्ण जबतक (p && (*p != '\0'));
		अगर (!can_assume(VALID_DTB) && !p)
			वापस FDT_END; /* premature end */
		अवरोध;

	हाल FDT_PROP:
		lenp = fdt_offset_ptr(fdt, offset, माप(*lenp));
		अगर (!can_assume(VALID_DTB) && !lenp)
			वापस FDT_END; /* premature end */
		/* skip-name offset, length and value */
		offset += माप(काष्ठा fdt_property) - FDT_TAGSIZE
			+ fdt32_to_cpu(*lenp);
		अगर (!can_assume(LATEST) &&
		    fdt_version(fdt) < 0x10 && fdt32_to_cpu(*lenp) >= 8 &&
		    ((offset - fdt32_to_cpu(*lenp)) % 8) != 0)
			offset += 4;
		अवरोध;

	हाल FDT_END:
	हाल FDT_END_NODE:
	हाल FDT_NOP:
		अवरोध;

	शेष:
		वापस FDT_END;
	पूर्ण

	अगर (!fdt_offset_ptr(fdt, startoffset, offset - startoffset))
		वापस FDT_END; /* premature end */

	*nextoffset = FDT_TAGALIGN(offset);
	वापस tag;
पूर्ण

पूर्णांक fdt_check_node_offset_(स्थिर व्योम *fdt, पूर्णांक offset)
अणु
	अगर (!can_assume(VALID_INPUT)
	    && ((offset < 0) || (offset % FDT_TAGSIZE)))
		वापस -FDT_ERR_BADOFFSET;

	अगर (fdt_next_tag(fdt, offset, &offset) != FDT_BEGIN_NODE)
		वापस -FDT_ERR_BADOFFSET;

	वापस offset;
पूर्ण

पूर्णांक fdt_check_prop_offset_(स्थिर व्योम *fdt, पूर्णांक offset)
अणु
	अगर (!can_assume(VALID_INPUT)
	    && ((offset < 0) || (offset % FDT_TAGSIZE)))
		वापस -FDT_ERR_BADOFFSET;

	अगर (fdt_next_tag(fdt, offset, &offset) != FDT_PROP)
		वापस -FDT_ERR_BADOFFSET;

	वापस offset;
पूर्ण

पूर्णांक fdt_next_node(स्थिर व्योम *fdt, पूर्णांक offset, पूर्णांक *depth)
अणु
	पूर्णांक nextoffset = 0;
	uपूर्णांक32_t tag;

	अगर (offset >= 0)
		अगर ((nextoffset = fdt_check_node_offset_(fdt, offset)) < 0)
			वापस nextoffset;

	करो अणु
		offset = nextoffset;
		tag = fdt_next_tag(fdt, offset, &nextoffset);

		चयन (tag) अणु
		हाल FDT_PROP:
		हाल FDT_NOP:
			अवरोध;

		हाल FDT_BEGIN_NODE:
			अगर (depth)
				(*depth)++;
			अवरोध;

		हाल FDT_END_NODE:
			अगर (depth && ((--(*depth)) < 0))
				वापस nextoffset;
			अवरोध;

		हाल FDT_END:
			अगर ((nextoffset >= 0)
			    || ((nextoffset == -FDT_ERR_TRUNCATED) && !depth))
				वापस -FDT_ERR_NOTFOUND;
			अन्यथा
				वापस nextoffset;
		पूर्ण
	पूर्ण जबतक (tag != FDT_BEGIN_NODE);

	वापस offset;
पूर्ण

पूर्णांक fdt_first_subnode(स्थिर व्योम *fdt, पूर्णांक offset)
अणु
	पूर्णांक depth = 0;

	offset = fdt_next_node(fdt, offset, &depth);
	अगर (offset < 0 || depth != 1)
		वापस -FDT_ERR_NOTFOUND;

	वापस offset;
पूर्ण

पूर्णांक fdt_next_subnode(स्थिर व्योम *fdt, पूर्णांक offset)
अणु
	पूर्णांक depth = 1;

	/*
	 * With respect to the parent, the depth of the next subnode will be
	 * the same as the last.
	 */
	करो अणु
		offset = fdt_next_node(fdt, offset, &depth);
		अगर (offset < 0 || depth < 1)
			वापस -FDT_ERR_NOTFOUND;
	पूर्ण जबतक (depth > 1);

	वापस offset;
पूर्ण

स्थिर अक्षर *fdt_find_string_(स्थिर अक्षर *strtab, पूर्णांक tअसलize, स्थिर अक्षर *s)
अणु
	पूर्णांक len = म_माप(s) + 1;
	स्थिर अक्षर *last = strtab + tअसलize - len;
	स्थिर अक्षर *p;

	क्रम (p = strtab; p <= last; p++)
		अगर (स_भेद(p, s, len) == 0)
			वापस p;
	वापस शून्य;
पूर्ण

पूर्णांक fdt_move(स्थिर व्योम *fdt, व्योम *buf, पूर्णांक bufsize)
अणु
	अगर (!can_assume(VALID_INPUT) && bufsize < 0)
		वापस -FDT_ERR_NOSPACE;

	FDT_RO_PROBE(fdt);

	अगर (fdt_totalsize(fdt) > (अचिन्हित पूर्णांक)bufsize)
		वापस -FDT_ERR_NOSPACE;

	स_हटाओ(buf, fdt, fdt_totalsize(fdt));
	वापस 0;
पूर्ण
