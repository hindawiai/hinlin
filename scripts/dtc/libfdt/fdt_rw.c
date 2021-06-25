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

अटल पूर्णांक fdt_blocks_misordered_(स्थिर व्योम *fdt,
				  पूर्णांक mem_rsv_size, पूर्णांक काष्ठा_size)
अणु
	वापस (fdt_off_mem_rsvmap(fdt) < FDT_ALIGN(माप(काष्ठा fdt_header), 8))
		|| (fdt_off_dt_काष्ठा(fdt) <
		    (fdt_off_mem_rsvmap(fdt) + mem_rsv_size))
		|| (fdt_off_dt_strings(fdt) <
		    (fdt_off_dt_काष्ठा(fdt) + काष्ठा_size))
		|| (fdt_totalsize(fdt) <
		    (fdt_off_dt_strings(fdt) + fdt_size_dt_strings(fdt)));
पूर्ण

अटल पूर्णांक fdt_rw_probe_(व्योम *fdt)
अणु
	अगर (can_assume(VALID_DTB))
		वापस 0;
	FDT_RO_PROBE(fdt);

	अगर (!can_assume(LATEST) && fdt_version(fdt) < 17)
		वापस -FDT_ERR_BADVERSION;
	अगर (fdt_blocks_misordered_(fdt, माप(काष्ठा fdt_reserve_entry),
				   fdt_size_dt_काष्ठा(fdt)))
		वापस -FDT_ERR_BADLAYOUT;
	अगर (!can_assume(LATEST) && fdt_version(fdt) > 17)
		fdt_set_version(fdt, 17);

	वापस 0;
पूर्ण

#घोषणा FDT_RW_PROBE(fdt) \
	अणु \
		पूर्णांक err_; \
		अगर ((err_ = fdt_rw_probe_(fdt)) != 0) \
			वापस err_; \
	पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक fdt_data_size_(व्योम *fdt)
अणु
	वापस fdt_off_dt_strings(fdt) + fdt_size_dt_strings(fdt);
पूर्ण

अटल पूर्णांक fdt_splice_(व्योम *fdt, व्योम *splicepoपूर्णांक, पूर्णांक oldlen, पूर्णांक newlen)
अणु
	अक्षर *p = splicepoपूर्णांक;
	अचिन्हित पूर्णांक dsize = fdt_data_size_(fdt);
	माप_प्रकार soff = p - (अक्षर *)fdt;

	अगर ((oldlen < 0) || (soff + oldlen < soff) || (soff + oldlen > dsize))
		वापस -FDT_ERR_BADOFFSET;
	अगर ((p < (अक्षर *)fdt) || (dsize + newlen < (अचिन्हित)oldlen))
		वापस -FDT_ERR_BADOFFSET;
	अगर (dsize - oldlen + newlen > fdt_totalsize(fdt))
		वापस -FDT_ERR_NOSPACE;
	स_हटाओ(p + newlen, p + oldlen, ((अक्षर *)fdt + dsize) - (p + oldlen));
	वापस 0;
पूर्ण

अटल पूर्णांक fdt_splice_mem_rsv_(व्योम *fdt, काष्ठा fdt_reserve_entry *p,
			       पूर्णांक oldn, पूर्णांक newn)
अणु
	पूर्णांक delta = (newn - oldn) * माप(*p);
	पूर्णांक err;
	err = fdt_splice_(fdt, p, oldn * माप(*p), newn * माप(*p));
	अगर (err)
		वापस err;
	fdt_set_off_dt_काष्ठा(fdt, fdt_off_dt_काष्ठा(fdt) + delta);
	fdt_set_off_dt_strings(fdt, fdt_off_dt_strings(fdt) + delta);
	वापस 0;
पूर्ण

अटल पूर्णांक fdt_splice_काष्ठा_(व्योम *fdt, व्योम *p,
			      पूर्णांक oldlen, पूर्णांक newlen)
अणु
	पूर्णांक delta = newlen - oldlen;
	पूर्णांक err;

	अगर ((err = fdt_splice_(fdt, p, oldlen, newlen)))
		वापस err;

	fdt_set_size_dt_काष्ठा(fdt, fdt_size_dt_काष्ठा(fdt) + delta);
	fdt_set_off_dt_strings(fdt, fdt_off_dt_strings(fdt) + delta);
	वापस 0;
पूर्ण

/* Must only be used to roll back in हाल of error */
अटल व्योम fdt_del_last_string_(व्योम *fdt, स्थिर अक्षर *s)
अणु
	पूर्णांक newlen = म_माप(s) + 1;

	fdt_set_size_dt_strings(fdt, fdt_size_dt_strings(fdt) - newlen);
पूर्ण

अटल पूर्णांक fdt_splice_string_(व्योम *fdt, पूर्णांक newlen)
अणु
	व्योम *p = (अक्षर *)fdt
		+ fdt_off_dt_strings(fdt) + fdt_size_dt_strings(fdt);
	पूर्णांक err;

	अगर ((err = fdt_splice_(fdt, p, 0, newlen)))
		वापस err;

	fdt_set_size_dt_strings(fdt, fdt_size_dt_strings(fdt) + newlen);
	वापस 0;
पूर्ण

/**
 * fdt_find_add_string_() - Find or allocate a string
 *
 * @fdt: poपूर्णांकer to the device tree to check/adjust
 * @s: string to find/add
 * @allocated: Set to 0 अगर the string was found, 1 अगर not found and so
 *	allocated. Ignored अगर can_assume(NO_ROLLBACK)
 * @वापस offset of string in the string table (whether found or added)
 */
अटल पूर्णांक fdt_find_add_string_(व्योम *fdt, स्थिर अक्षर *s, पूर्णांक *allocated)
अणु
	अक्षर *strtab = (अक्षर *)fdt + fdt_off_dt_strings(fdt);
	स्थिर अक्षर *p;
	अक्षर *new;
	पूर्णांक len = म_माप(s) + 1;
	पूर्णांक err;

	अगर (!can_assume(NO_ROLLBACK))
		*allocated = 0;

	p = fdt_find_string_(strtab, fdt_size_dt_strings(fdt), s);
	अगर (p)
		/* found it */
		वापस (p - strtab);

	new = strtab + fdt_size_dt_strings(fdt);
	err = fdt_splice_string_(fdt, len);
	अगर (err)
		वापस err;

	अगर (!can_assume(NO_ROLLBACK))
		*allocated = 1;

	स_नकल(new, s, len);
	वापस (new - strtab);
पूर्ण

पूर्णांक fdt_add_mem_rsv(व्योम *fdt, uपूर्णांक64_t address, uपूर्णांक64_t size)
अणु
	काष्ठा fdt_reserve_entry *re;
	पूर्णांक err;

	FDT_RW_PROBE(fdt);

	re = fdt_mem_rsv_w_(fdt, fdt_num_mem_rsv(fdt));
	err = fdt_splice_mem_rsv_(fdt, re, 0, 1);
	अगर (err)
		वापस err;

	re->address = cpu_to_fdt64(address);
	re->size = cpu_to_fdt64(size);
	वापस 0;
पूर्ण

पूर्णांक fdt_del_mem_rsv(व्योम *fdt, पूर्णांक n)
अणु
	काष्ठा fdt_reserve_entry *re = fdt_mem_rsv_w_(fdt, n);

	FDT_RW_PROBE(fdt);

	अगर (n >= fdt_num_mem_rsv(fdt))
		वापस -FDT_ERR_NOTFOUND;

	वापस fdt_splice_mem_rsv_(fdt, re, 1, 0);
पूर्ण

अटल पूर्णांक fdt_resize_property_(व्योम *fdt, पूर्णांक nodeoffset, स्थिर अक्षर *name,
				पूर्णांक len, काष्ठा fdt_property **prop)
अणु
	पूर्णांक oldlen;
	पूर्णांक err;

	*prop = fdt_get_property_w(fdt, nodeoffset, name, &oldlen);
	अगर (!*prop)
		वापस oldlen;

	अगर ((err = fdt_splice_काष्ठा_(fdt, (*prop)->data, FDT_TAGALIGN(oldlen),
				      FDT_TAGALIGN(len))))
		वापस err;

	(*prop)->len = cpu_to_fdt32(len);
	वापस 0;
पूर्ण

अटल पूर्णांक fdt_add_property_(व्योम *fdt, पूर्णांक nodeoffset, स्थिर अक्षर *name,
			     पूर्णांक len, काष्ठा fdt_property **prop)
अणु
	पूर्णांक proplen;
	पूर्णांक nextoffset;
	पूर्णांक namestroff;
	पूर्णांक err;
	पूर्णांक allocated;

	अगर ((nextoffset = fdt_check_node_offset_(fdt, nodeoffset)) < 0)
		वापस nextoffset;

	namestroff = fdt_find_add_string_(fdt, name, &allocated);
	अगर (namestroff < 0)
		वापस namestroff;

	*prop = fdt_offset_ptr_w_(fdt, nextoffset);
	proplen = माप(**prop) + FDT_TAGALIGN(len);

	err = fdt_splice_काष्ठा_(fdt, *prop, 0, proplen);
	अगर (err) अणु
		/* Delete the string अगर we failed to add it */
		अगर (!can_assume(NO_ROLLBACK) && allocated)
			fdt_del_last_string_(fdt, name);
		वापस err;
	पूर्ण

	(*prop)->tag = cpu_to_fdt32(FDT_PROP);
	(*prop)->nameoff = cpu_to_fdt32(namestroff);
	(*prop)->len = cpu_to_fdt32(len);
	वापस 0;
पूर्ण

पूर्णांक fdt_set_name(व्योम *fdt, पूर्णांक nodeoffset, स्थिर अक्षर *name)
अणु
	अक्षर *namep;
	पूर्णांक oldlen, newlen;
	पूर्णांक err;

	FDT_RW_PROBE(fdt);

	namep = (अक्षर *)(uपूर्णांकptr_t)fdt_get_name(fdt, nodeoffset, &oldlen);
	अगर (!namep)
		वापस oldlen;

	newlen = म_माप(name);

	err = fdt_splice_काष्ठा_(fdt, namep, FDT_TAGALIGN(oldlen+1),
				 FDT_TAGALIGN(newlen+1));
	अगर (err)
		वापस err;

	स_नकल(namep, name, newlen+1);
	वापस 0;
पूर्ण

पूर्णांक fdt_setprop_placeholder(व्योम *fdt, पूर्णांक nodeoffset, स्थिर अक्षर *name,
			    पूर्णांक len, व्योम **prop_data)
अणु
	काष्ठा fdt_property *prop;
	पूर्णांक err;

	FDT_RW_PROBE(fdt);

	err = fdt_resize_property_(fdt, nodeoffset, name, len, &prop);
	अगर (err == -FDT_ERR_NOTFOUND)
		err = fdt_add_property_(fdt, nodeoffset, name, len, &prop);
	अगर (err)
		वापस err;

	*prop_data = prop->data;
	वापस 0;
पूर्ण

पूर्णांक fdt_setprop(व्योम *fdt, पूर्णांक nodeoffset, स्थिर अक्षर *name,
		स्थिर व्योम *val, पूर्णांक len)
अणु
	व्योम *prop_data;
	पूर्णांक err;

	err = fdt_setprop_placeholder(fdt, nodeoffset, name, len, &prop_data);
	अगर (err)
		वापस err;

	अगर (len)
		स_नकल(prop_data, val, len);
	वापस 0;
पूर्ण

पूर्णांक fdt_appendprop(व्योम *fdt, पूर्णांक nodeoffset, स्थिर अक्षर *name,
		   स्थिर व्योम *val, पूर्णांक len)
अणु
	काष्ठा fdt_property *prop;
	पूर्णांक err, oldlen, newlen;

	FDT_RW_PROBE(fdt);

	prop = fdt_get_property_w(fdt, nodeoffset, name, &oldlen);
	अगर (prop) अणु
		newlen = len + oldlen;
		err = fdt_splice_काष्ठा_(fdt, prop->data,
					 FDT_TAGALIGN(oldlen),
					 FDT_TAGALIGN(newlen));
		अगर (err)
			वापस err;
		prop->len = cpu_to_fdt32(newlen);
		स_नकल(prop->data + oldlen, val, len);
	पूर्ण अन्यथा अणु
		err = fdt_add_property_(fdt, nodeoffset, name, len, &prop);
		अगर (err)
			वापस err;
		स_नकल(prop->data, val, len);
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक fdt_delprop(व्योम *fdt, पूर्णांक nodeoffset, स्थिर अक्षर *name)
अणु
	काष्ठा fdt_property *prop;
	पूर्णांक len, proplen;

	FDT_RW_PROBE(fdt);

	prop = fdt_get_property_w(fdt, nodeoffset, name, &len);
	अगर (!prop)
		वापस len;

	proplen = माप(*prop) + FDT_TAGALIGN(len);
	वापस fdt_splice_काष्ठा_(fdt, prop, proplen, 0);
पूर्ण

पूर्णांक fdt_add_subnode_namelen(व्योम *fdt, पूर्णांक parentoffset,
			    स्थिर अक्षर *name, पूर्णांक namelen)
अणु
	काष्ठा fdt_node_header *nh;
	पूर्णांक offset, nextoffset;
	पूर्णांक nodelen;
	पूर्णांक err;
	uपूर्णांक32_t tag;
	fdt32_t *endtag;

	FDT_RW_PROBE(fdt);

	offset = fdt_subnode_offset_namelen(fdt, parentoffset, name, namelen);
	अगर (offset >= 0)
		वापस -FDT_ERR_EXISTS;
	अन्यथा अगर (offset != -FDT_ERR_NOTFOUND)
		वापस offset;

	/* Try to place the new node after the parent's properties */
	fdt_next_tag(fdt, parentoffset, &nextoffset); /* skip the BEGIN_NODE */
	करो अणु
		offset = nextoffset;
		tag = fdt_next_tag(fdt, offset, &nextoffset);
	पूर्ण जबतक ((tag == FDT_PROP) || (tag == FDT_NOP));

	nh = fdt_offset_ptr_w_(fdt, offset);
	nodelen = माप(*nh) + FDT_TAGALIGN(namelen+1) + FDT_TAGSIZE;

	err = fdt_splice_काष्ठा_(fdt, nh, 0, nodelen);
	अगर (err)
		वापस err;

	nh->tag = cpu_to_fdt32(FDT_BEGIN_NODE);
	स_रखो(nh->name, 0, FDT_TAGALIGN(namelen+1));
	स_नकल(nh->name, name, namelen);
	endtag = (fdt32_t *)((अक्षर *)nh + nodelen - FDT_TAGSIZE);
	*endtag = cpu_to_fdt32(FDT_END_NODE);

	वापस offset;
पूर्ण

पूर्णांक fdt_add_subnode(व्योम *fdt, पूर्णांक parentoffset, स्थिर अक्षर *name)
अणु
	वापस fdt_add_subnode_namelen(fdt, parentoffset, name, म_माप(name));
पूर्ण

पूर्णांक fdt_del_node(व्योम *fdt, पूर्णांक nodeoffset)
अणु
	पूर्णांक enकरोffset;

	FDT_RW_PROBE(fdt);

	enकरोffset = fdt_node_end_offset_(fdt, nodeoffset);
	अगर (enकरोffset < 0)
		वापस enकरोffset;

	वापस fdt_splice_काष्ठा_(fdt, fdt_offset_ptr_w_(fdt, nodeoffset),
				  enकरोffset - nodeoffset, 0);
पूर्ण

अटल व्योम fdt_packblocks_(स्थिर अक्षर *old, अक्षर *new,
			    पूर्णांक mem_rsv_size, पूर्णांक काष्ठा_size)
अणु
	पूर्णांक mem_rsv_off, काष्ठा_off, strings_off;

	mem_rsv_off = FDT_ALIGN(माप(काष्ठा fdt_header), 8);
	काष्ठा_off = mem_rsv_off + mem_rsv_size;
	strings_off = काष्ठा_off + काष्ठा_size;

	स_हटाओ(new + mem_rsv_off, old + fdt_off_mem_rsvmap(old), mem_rsv_size);
	fdt_set_off_mem_rsvmap(new, mem_rsv_off);

	स_हटाओ(new + काष्ठा_off, old + fdt_off_dt_काष्ठा(old), काष्ठा_size);
	fdt_set_off_dt_काष्ठा(new, काष्ठा_off);
	fdt_set_size_dt_काष्ठा(new, काष्ठा_size);

	स_हटाओ(new + strings_off, old + fdt_off_dt_strings(old),
		fdt_size_dt_strings(old));
	fdt_set_off_dt_strings(new, strings_off);
	fdt_set_size_dt_strings(new, fdt_size_dt_strings(old));
पूर्ण

पूर्णांक fdt_खोलो_पूर्णांकo(स्थिर व्योम *fdt, व्योम *buf, पूर्णांक bufsize)
अणु
	पूर्णांक err;
	पूर्णांक mem_rsv_size, काष्ठा_size;
	पूर्णांक newsize;
	स्थिर अक्षर *fdtstart = fdt;
	स्थिर अक्षर *fdtend = fdtstart + fdt_totalsize(fdt);
	अक्षर *पंचांगp;

	FDT_RO_PROBE(fdt);

	mem_rsv_size = (fdt_num_mem_rsv(fdt)+1)
		* माप(काष्ठा fdt_reserve_entry);

	अगर (can_assume(LATEST) || fdt_version(fdt) >= 17) अणु
		काष्ठा_size = fdt_size_dt_काष्ठा(fdt);
	पूर्ण अन्यथा अगर (fdt_version(fdt) == 16) अणु
		काष्ठा_size = 0;
		जबतक (fdt_next_tag(fdt, काष्ठा_size, &काष्ठा_size) != FDT_END)
			;
		अगर (काष्ठा_size < 0)
			वापस काष्ठा_size;
	पूर्ण अन्यथा अणु
		वापस -FDT_ERR_BADVERSION;
	पूर्ण

	अगर (can_assume(LIBFDT_ORDER) ||
	    !fdt_blocks_misordered_(fdt, mem_rsv_size, काष्ठा_size)) अणु
		/* no further work necessary */
		err = fdt_move(fdt, buf, bufsize);
		अगर (err)
			वापस err;
		fdt_set_version(buf, 17);
		fdt_set_size_dt_काष्ठा(buf, काष्ठा_size);
		fdt_set_totalsize(buf, bufsize);
		वापस 0;
	पूर्ण

	/* Need to reorder */
	newsize = FDT_ALIGN(माप(काष्ठा fdt_header), 8) + mem_rsv_size
		+ काष्ठा_size + fdt_size_dt_strings(fdt);

	अगर (bufsize < newsize)
		वापस -FDT_ERR_NOSPACE;

	/* First attempt to build converted tree at beginning of buffer */
	पंचांगp = buf;
	/* But अगर that overlaps with the old tree... */
	अगर (((पंचांगp + newsize) > fdtstart) && (पंचांगp < fdtend)) अणु
		/* Try right after the old tree instead */
		पंचांगp = (अक्षर *)(uपूर्णांकptr_t)fdtend;
		अगर ((पंचांगp + newsize) > ((अक्षर *)buf + bufsize))
			वापस -FDT_ERR_NOSPACE;
	पूर्ण

	fdt_packblocks_(fdt, पंचांगp, mem_rsv_size, काष्ठा_size);
	स_हटाओ(buf, पंचांगp, newsize);

	fdt_set_magic(buf, FDT_MAGIC);
	fdt_set_totalsize(buf, bufsize);
	fdt_set_version(buf, 17);
	fdt_set_last_comp_version(buf, 16);
	fdt_set_boot_cpuid_phys(buf, fdt_boot_cpuid_phys(fdt));

	वापस 0;
पूर्ण

पूर्णांक fdt_pack(व्योम *fdt)
अणु
	पूर्णांक mem_rsv_size;

	FDT_RW_PROBE(fdt);

	mem_rsv_size = (fdt_num_mem_rsv(fdt)+1)
		* माप(काष्ठा fdt_reserve_entry);
	fdt_packblocks_(fdt, fdt, mem_rsv_size, fdt_size_dt_काष्ठा(fdt));
	fdt_set_totalsize(fdt, fdt_data_size_(fdt));

	वापस 0;
पूर्ण
