<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * (C) Copyright David Gibson <dwg@au1.ibm.com>, IBM Corporation.  2005.
 */

#समावेश "dtc.h"
#समावेश "srcpos.h"

#घोषणा FTF_FULLPATH	0x1
#घोषणा FTF_VARALIGN	0x2
#घोषणा FTF_NAMEPROPS	0x4
#घोषणा FTF_BOOTCPUID	0x8
#घोषणा FTF_STRTABSIZE	0x10
#घोषणा FTF_STRUCTSIZE	0x20
#घोषणा FTF_NOPS	0x40

अटल काष्ठा version_info अणु
	पूर्णांक version;
	पूर्णांक last_comp_version;
	पूर्णांक hdr_size;
	पूर्णांक flags;
पूर्ण version_table[] = अणु
	अणु1, 1, FDT_V1_SIZE,
	 FTF_FULLPATH|FTF_VARALIGN|FTF_NAMEPROPSपूर्ण,
	अणु2, 1, FDT_V2_SIZE,
	 FTF_FULLPATH|FTF_VARALIGN|FTF_NAMEPROPS|FTF_BOOTCPUIDपूर्ण,
	अणु3, 1, FDT_V3_SIZE,
	 FTF_FULLPATH|FTF_VARALIGN|FTF_NAMEPROPS|FTF_BOOTCPUID|FTF_STRTABSIZEपूर्ण,
	अणु16, 16, FDT_V3_SIZE,
	 FTF_BOOTCPUID|FTF_STRTABSIZE|FTF_NOPSपूर्ण,
	अणु17, 16, FDT_V17_SIZE,
	 FTF_BOOTCPUID|FTF_STRTABSIZE|FTF_STRUCTSIZE|FTF_NOPSपूर्ण,
पूर्ण;

काष्ठा emitter अणु
	व्योम (*cell)(व्योम *, cell_t);
	व्योम (*string)(व्योम *, स्थिर अक्षर *, पूर्णांक);
	व्योम (*align)(व्योम *, पूर्णांक);
	व्योम (*data)(व्योम *, काष्ठा data);
	व्योम (*beginnode)(व्योम *, काष्ठा label *labels);
	व्योम (*endnode)(व्योम *, काष्ठा label *labels);
	व्योम (*property)(व्योम *, काष्ठा label *labels);
पूर्ण;

अटल व्योम bin_emit_cell(व्योम *e, cell_t val)
अणु
	काष्ठा data *dtbuf = e;

	*dtbuf = data_append_cell(*dtbuf, val);
पूर्ण

अटल व्योम bin_emit_string(व्योम *e, स्थिर अक्षर *str, पूर्णांक len)
अणु
	काष्ठा data *dtbuf = e;

	अगर (len == 0)
		len = म_माप(str);

	*dtbuf = data_append_data(*dtbuf, str, len);
	*dtbuf = data_append_byte(*dtbuf, '\0');
पूर्ण

अटल व्योम bin_emit_align(व्योम *e, पूर्णांक a)
अणु
	काष्ठा data *dtbuf = e;

	*dtbuf = data_append_align(*dtbuf, a);
पूर्ण

अटल व्योम bin_emit_data(व्योम *e, काष्ठा data d)
अणु
	काष्ठा data *dtbuf = e;

	*dtbuf = data_append_data(*dtbuf, d.val, d.len);
पूर्ण

अटल व्योम bin_emit_beginnode(व्योम *e, काष्ठा label *labels)
अणु
	bin_emit_cell(e, FDT_BEGIN_NODE);
पूर्ण

अटल व्योम bin_emit_endnode(व्योम *e, काष्ठा label *labels)
अणु
	bin_emit_cell(e, FDT_END_NODE);
पूर्ण

अटल व्योम bin_emit_property(व्योम *e, काष्ठा label *labels)
अणु
	bin_emit_cell(e, FDT_PROP);
पूर्ण

अटल काष्ठा emitter bin_emitter = अणु
	.cell = bin_emit_cell,
	.string = bin_emit_string,
	.align = bin_emit_align,
	.data = bin_emit_data,
	.beginnode = bin_emit_beginnode,
	.endnode = bin_emit_endnode,
	.property = bin_emit_property,
पूर्ण;

अटल व्योम emit_label(खाता *f, स्थिर अक्षर *prefix, स्थिर अक्षर *label)
अणु
	ख_लिखो(f, "\t.globl\t%s_%s\n", prefix, label);
	ख_लिखो(f, "%s_%s:\n", prefix, label);
	ख_लिखो(f, "_%s_%s:\n", prefix, label);
पूर्ण

अटल व्योम emit_offset_label(खाता *f, स्थिर अक्षर *label, पूर्णांक offset)
अणु
	ख_लिखो(f, "\t.globl\t%s\n", label);
	ख_लिखो(f, "%s\t= . + %d\n", label, offset);
पूर्ण

#घोषणा ASM_EMIT_BELONG(f, fmt, ...) \
	अणु \
		ख_लिखो((f), "\t.byte\t((" fmt ") >> 24) & 0xff\n", __VA_ARGS__); \
		ख_लिखो((f), "\t.byte\t((" fmt ") >> 16) & 0xff\n", __VA_ARGS__); \
		ख_लिखो((f), "\t.byte\t((" fmt ") >> 8) & 0xff\n", __VA_ARGS__); \
		ख_लिखो((f), "\t.byte\t(" fmt ") & 0xff\n", __VA_ARGS__); \
	पूर्ण

अटल व्योम यंत्र_emit_cell(व्योम *e, cell_t val)
अणु
	खाता *f = e;

	ख_लिखो(f, "\t.byte 0x%02x; .byte 0x%02x; .byte 0x%02x; .byte 0x%02x\n",
		(val >> 24) & 0xff, (val >> 16) & 0xff,
		(val >> 8) & 0xff, val & 0xff);
पूर्ण

अटल व्योम यंत्र_emit_string(व्योम *e, स्थिर अक्षर *str, पूर्णांक len)
अणु
	खाता *f = e;

	अगर (len != 0)
		ख_लिखो(f, "\t.string\t\"%.*s\"\n", len, str);
	अन्यथा
		ख_लिखो(f, "\t.string\t\"%s\"\n", str);
पूर्ण

अटल व्योम यंत्र_emit_align(व्योम *e, पूर्णांक a)
अणु
	खाता *f = e;

	ख_लिखो(f, "\t.balign\t%d, 0\n", a);
पूर्ण

अटल व्योम यंत्र_emit_data(व्योम *e, काष्ठा data d)
अणु
	खाता *f = e;
	अचिन्हित पूर्णांक off = 0;
	काष्ठा marker *m = d.markers;

	क्रम_each_marker_of_type(m, LABEL)
		emit_offset_label(f, m->ref, m->offset);

	जबतक ((d.len - off) >= माप(uपूर्णांक32_t)) अणु
		यंत्र_emit_cell(e, dtb_ld32(d.val + off));
		off += माप(uपूर्णांक32_t);
	पूर्ण

	जबतक ((d.len - off) >= 1) अणु
		ख_लिखो(f, "\t.byte\t0x%hhx\n", d.val[off]);
		off += 1;
	पूर्ण

	निश्चित(off == d.len);
पूर्ण

अटल व्योम यंत्र_emit_beginnode(व्योम *e, काष्ठा label *labels)
अणु
	खाता *f = e;
	काष्ठा label *l;

	क्रम_each_label(labels, l) अणु
		ख_लिखो(f, "\t.globl\t%s\n", l->label);
		ख_लिखो(f, "%s:\n", l->label);
	पूर्ण
	ख_लिखो(f, "\t/* FDT_BEGIN_NODE */\n");
	यंत्र_emit_cell(e, FDT_BEGIN_NODE);
पूर्ण

अटल व्योम यंत्र_emit_endnode(व्योम *e, काष्ठा label *labels)
अणु
	खाता *f = e;
	काष्ठा label *l;

	ख_लिखो(f, "\t/* FDT_END_NODE */\n");
	यंत्र_emit_cell(e, FDT_END_NODE);
	क्रम_each_label(labels, l) अणु
		ख_लिखो(f, "\t.globl\t%s_end\n", l->label);
		ख_लिखो(f, "%s_end:\n", l->label);
	पूर्ण
पूर्ण

अटल व्योम यंत्र_emit_property(व्योम *e, काष्ठा label *labels)
अणु
	खाता *f = e;
	काष्ठा label *l;

	क्रम_each_label(labels, l) अणु
		ख_लिखो(f, "\t.globl\t%s\n", l->label);
		ख_लिखो(f, "%s:\n", l->label);
	पूर्ण
	ख_लिखो(f, "\t/* FDT_PROP */\n");
	यंत्र_emit_cell(e, FDT_PROP);
पूर्ण

अटल काष्ठा emitter यंत्र_emitter = अणु
	.cell = यंत्र_emit_cell,
	.string = यंत्र_emit_string,
	.align = यंत्र_emit_align,
	.data = यंत्र_emit_data,
	.beginnode = यंत्र_emit_beginnode,
	.endnode = यंत्र_emit_endnode,
	.property = यंत्र_emit_property,
पूर्ण;

अटल पूर्णांक stringtable_insert(काष्ठा data *d, स्थिर अक्षर *str)
अणु
	अचिन्हित पूर्णांक i;

	/* FIXME: करो this more efficiently? */

	क्रम (i = 0; i < d->len; i++) अणु
		अगर (streq(str, d->val + i))
			वापस i;
	पूर्ण

	*d = data_append_data(*d, str, म_माप(str)+1);
	वापस i;
पूर्ण

अटल व्योम flatten_tree(काष्ठा node *tree, काष्ठा emitter *emit,
			 व्योम *etarget, काष्ठा data *strbuf,
			 काष्ठा version_info *vi)
अणु
	काष्ठा property *prop;
	काष्ठा node *child;
	bool seen_name_prop = false;

	अगर (tree->deleted)
		वापस;

	emit->beginnode(etarget, tree->labels);

	अगर (vi->flags & FTF_FULLPATH)
		emit->string(etarget, tree->fullpath, 0);
	अन्यथा
		emit->string(etarget, tree->name, 0);

	emit->align(etarget, माप(cell_t));

	क्रम_each_property(tree, prop) अणु
		पूर्णांक nameoff;

		अगर (streq(prop->name, "name"))
			seen_name_prop = true;

		nameoff = stringtable_insert(strbuf, prop->name);

		emit->property(etarget, prop->labels);
		emit->cell(etarget, prop->val.len);
		emit->cell(etarget, nameoff);

		अगर ((vi->flags & FTF_VARALIGN) && (prop->val.len >= 8))
			emit->align(etarget, 8);

		emit->data(etarget, prop->val);
		emit->align(etarget, माप(cell_t));
	पूर्ण

	अगर ((vi->flags & FTF_NAMEPROPS) && !seen_name_prop) अणु
		emit->property(etarget, शून्य);
		emit->cell(etarget, tree->basenamelen+1);
		emit->cell(etarget, stringtable_insert(strbuf, "name"));

		अगर ((vi->flags & FTF_VARALIGN) && ((tree->basenamelen+1) >= 8))
			emit->align(etarget, 8);

		emit->string(etarget, tree->name, tree->basenamelen);
		emit->align(etarget, माप(cell_t));
	पूर्ण

	क्रम_each_child(tree, child) अणु
		flatten_tree(child, emit, etarget, strbuf, vi);
	पूर्ण

	emit->endnode(etarget, tree->labels);
पूर्ण

अटल काष्ठा data flatten_reserve_list(काष्ठा reserve_info *reservelist,
				 काष्ठा version_info *vi)
अणु
	काष्ठा reserve_info *re;
	काष्ठा data d = empty_data;
	पूर्णांक    j;

	क्रम (re = reservelist; re; re = re->next) अणु
		d = data_append_re(d, re->address, re->size);
	पूर्ण
	/*
	 * Add additional reserved slots अगर the user asked क्रम them.
	 */
	क्रम (j = 0; j < reservक्रमागत; j++) अणु
		d = data_append_re(d, 0, 0);
	पूर्ण

	वापस d;
पूर्ण

अटल व्योम make_fdt_header(काष्ठा fdt_header *fdt,
			    काष्ठा version_info *vi,
			    पूर्णांक reservesize, पूर्णांक dtsize, पूर्णांक strsize,
			    पूर्णांक boot_cpuid_phys)
अणु
	पूर्णांक reserve_off;

	reservesize += माप(काष्ठा fdt_reserve_entry);

	स_रखो(fdt, 0xff, माप(*fdt));

	fdt->magic = cpu_to_fdt32(FDT_MAGIC);
	fdt->version = cpu_to_fdt32(vi->version);
	fdt->last_comp_version = cpu_to_fdt32(vi->last_comp_version);

	/* Reserve map should be द्विगुनword aligned */
	reserve_off = ALIGN(vi->hdr_size, 8);

	fdt->off_mem_rsvmap = cpu_to_fdt32(reserve_off);
	fdt->off_dt_काष्ठा = cpu_to_fdt32(reserve_off + reservesize);
	fdt->off_dt_strings = cpu_to_fdt32(reserve_off + reservesize
					  + dtsize);
	fdt->totalsize = cpu_to_fdt32(reserve_off + reservesize + dtsize + strsize);

	अगर (vi->flags & FTF_BOOTCPUID)
		fdt->boot_cpuid_phys = cpu_to_fdt32(boot_cpuid_phys);
	अगर (vi->flags & FTF_STRTABSIZE)
		fdt->size_dt_strings = cpu_to_fdt32(strsize);
	अगर (vi->flags & FTF_STRUCTSIZE)
		fdt->size_dt_काष्ठा = cpu_to_fdt32(dtsize);
पूर्ण

व्योम dt_to_blob(खाता *f, काष्ठा dt_info *dti, पूर्णांक version)
अणु
	काष्ठा version_info *vi = शून्य;
	अचिन्हित पूर्णांक i;
	काष्ठा data blob       = empty_data;
	काष्ठा data reservebuf = empty_data;
	काष्ठा data dtbuf      = empty_data;
	काष्ठा data strbuf     = empty_data;
	काष्ठा fdt_header fdt;
	पूर्णांक padlen = 0;

	क्रम (i = 0; i < ARRAY_SIZE(version_table); i++) अणु
		अगर (version_table[i].version == version)
			vi = &version_table[i];
	पूर्ण
	अगर (!vi)
		die("Unknown device tree blob version %d\n", version);

	flatten_tree(dti->dt, &bin_emitter, &dtbuf, &strbuf, vi);
	bin_emit_cell(&dtbuf, FDT_END);

	reservebuf = flatten_reserve_list(dti->reservelist, vi);

	/* Make header */
	make_fdt_header(&fdt, vi, reservebuf.len, dtbuf.len, strbuf.len,
			dti->boot_cpuid_phys);

	/*
	 * If the user asked क्रम more space than is used, adjust the totalsize.
	 */
	अगर (minsize > 0) अणु
		padlen = minsize - fdt32_to_cpu(fdt.totalsize);
		अगर (padlen < 0) अणु
			padlen = 0;
			अगर (quiet < 1)
				ख_लिखो(मानक_त्रुटि,
					"Warning: blob size %"PRIu32" >= minimum size %d\n",
					fdt32_to_cpu(fdt.totalsize), minsize);
		पूर्ण
	पूर्ण

	अगर (padsize > 0)
		padlen = padsize;

	अगर (alignsize > 0)
		padlen = ALIGN(fdt32_to_cpu(fdt.totalsize) + padlen, alignsize)
			- fdt32_to_cpu(fdt.totalsize);

	अगर (padlen > 0) अणु
		पूर्णांक tsize = fdt32_to_cpu(fdt.totalsize);
		tsize += padlen;
		fdt.totalsize = cpu_to_fdt32(tsize);
	पूर्ण

	/*
	 * Assemble the blob: start with the header, add with alignment
	 * the reserve buffer, add the reserve map terminating zeroes,
	 * the device tree itself, and finally the strings.
	 */
	blob = data_append_data(blob, &fdt, vi->hdr_size);
	blob = data_append_align(blob, 8);
	blob = data_merge(blob, reservebuf);
	blob = data_append_zeroes(blob, माप(काष्ठा fdt_reserve_entry));
	blob = data_merge(blob, dtbuf);
	blob = data_merge(blob, strbuf);

	/*
	 * If the user asked क्रम more space than is used, pad out the blob.
	 */
	अगर (padlen > 0)
		blob = data_append_zeroes(blob, padlen);

	अगर (ख_डालो(blob.val, blob.len, 1, f) != 1) अणु
		अगर (ख_त्रुटि(f))
			die("Error writing device tree blob: %s\n",
			    म_त्रुटि(त्रुटि_सं));
		अन्यथा
			die("Short write on device tree blob\n");
	पूर्ण

	/*
	 * data_merge() मुक्तs the right-hand element so only the blob
	 * reमुख्यs to be मुक्तd.
	 */
	data_मुक्त(blob);
पूर्ण

अटल व्योम dump_stringtable_यंत्र(खाता *f, काष्ठा data strbuf)
अणु
	स्थिर अक्षर *p;
	पूर्णांक len;

	p = strbuf.val;

	जबतक (p < (strbuf.val + strbuf.len)) अणु
		len = म_माप(p);
		ख_लिखो(f, "\t.string \"%s\"\n", p);
		p += len+1;
	पूर्ण
पूर्ण

व्योम dt_to_यंत्र(खाता *f, काष्ठा dt_info *dti, पूर्णांक version)
अणु
	काष्ठा version_info *vi = शून्य;
	अचिन्हित पूर्णांक i;
	काष्ठा data strbuf = empty_data;
	काष्ठा reserve_info *re;
	स्थिर अक्षर *symprefix = "dt";

	क्रम (i = 0; i < ARRAY_SIZE(version_table); i++) अणु
		अगर (version_table[i].version == version)
			vi = &version_table[i];
	पूर्ण
	अगर (!vi)
		die("Unknown device tree blob version %d\n", version);

	ख_लिखो(f, "/* autogenerated by dtc, do not edit */\n\n");

	emit_label(f, symprefix, "blob_start");
	emit_label(f, symprefix, "header");
	ख_लिखो(f, "\t/* magic */\n");
	यंत्र_emit_cell(f, FDT_MAGIC);
	ख_लिखो(f, "\t/* totalsize */\n");
	ASM_EMIT_BELONG(f, "_%s_blob_abs_end - _%s_blob_start",
			symprefix, symprefix);
	ख_लिखो(f, "\t/* off_dt_struct */\n");
	ASM_EMIT_BELONG(f, "_%s_struct_start - _%s_blob_start",
		symprefix, symprefix);
	ख_लिखो(f, "\t/* off_dt_strings */\n");
	ASM_EMIT_BELONG(f, "_%s_strings_start - _%s_blob_start",
		symprefix, symprefix);
	ख_लिखो(f, "\t/* off_mem_rsvmap */\n");
	ASM_EMIT_BELONG(f, "_%s_reserve_map - _%s_blob_start",
		symprefix, symprefix);
	ख_लिखो(f, "\t/* version */\n");
	यंत्र_emit_cell(f, vi->version);
	ख_लिखो(f, "\t/* last_comp_version */\n");
	यंत्र_emit_cell(f, vi->last_comp_version);

	अगर (vi->flags & FTF_BOOTCPUID) अणु
		ख_लिखो(f, "\t/* boot_cpuid_phys */\n");
		यंत्र_emit_cell(f, dti->boot_cpuid_phys);
	पूर्ण

	अगर (vi->flags & FTF_STRTABSIZE) अणु
		ख_लिखो(f, "\t/* size_dt_strings */\n");
		ASM_EMIT_BELONG(f, "_%s_strings_end - _%s_strings_start",
				symprefix, symprefix);
	पूर्ण

	अगर (vi->flags & FTF_STRUCTSIZE) अणु
		ख_लिखो(f, "\t/* size_dt_struct */\n");
		ASM_EMIT_BELONG(f, "_%s_struct_end - _%s_struct_start",
			symprefix, symprefix);
	पूर्ण

	/*
	 * Reserve map entries.
	 * Align the reserve map to a द्विगुनword boundary.
	 * Each entry is an (address, size) pair of u64 values.
	 * Always supply a zero-sized temination entry.
	 */
	यंत्र_emit_align(f, 8);
	emit_label(f, symprefix, "reserve_map");

	ख_लिखो(f, "/* Memory reserve map from source file */\n");

	/*
	 * Use .दीर्घ on high and low halves of u64s to aव्योम .quad
	 * as it appears .quad isn't available in some assemblers.
	 */
	क्रम (re = dti->reservelist; re; re = re->next) अणु
		काष्ठा label *l;

		क्रम_each_label(re->labels, l) अणु
			ख_लिखो(f, "\t.globl\t%s\n", l->label);
			ख_लिखो(f, "%s:\n", l->label);
		पूर्ण
		ASM_EMIT_BELONG(f, "0x%08x", (अचिन्हित पूर्णांक)(re->address >> 32));
		ASM_EMIT_BELONG(f, "0x%08x",
				(अचिन्हित पूर्णांक)(re->address & 0xffffffff));
		ASM_EMIT_BELONG(f, "0x%08x", (अचिन्हित पूर्णांक)(re->size >> 32));
		ASM_EMIT_BELONG(f, "0x%08x", (अचिन्हित पूर्णांक)(re->size & 0xffffffff));
	पूर्ण
	क्रम (i = 0; i < reservक्रमागत; i++) अणु
		ख_लिखो(f, "\t.long\t0, 0\n\t.long\t0, 0\n");
	पूर्ण

	ख_लिखो(f, "\t.long\t0, 0\n\t.long\t0, 0\n");

	emit_label(f, symprefix, "struct_start");
	flatten_tree(dti->dt, &यंत्र_emitter, f, &strbuf, vi);

	ख_लिखो(f, "\t/* FDT_END */\n");
	यंत्र_emit_cell(f, FDT_END);
	emit_label(f, symprefix, "struct_end");

	emit_label(f, symprefix, "strings_start");
	dump_stringtable_यंत्र(f, strbuf);
	emit_label(f, symprefix, "strings_end");

	emit_label(f, symprefix, "blob_end");

	/*
	 * If the user asked क्रम more space than is used, pad it out.
	 */
	अगर (minsize > 0) अणु
		ख_लिखो(f, "\t.space\t%d - (_%s_blob_end - _%s_blob_start), 0\n",
			minsize, symprefix, symprefix);
	पूर्ण
	अगर (padsize > 0) अणु
		ख_लिखो(f, "\t.space\t%d, 0\n", padsize);
	पूर्ण
	अगर (alignsize > 0)
		यंत्र_emit_align(f, alignsize);
	emit_label(f, symprefix, "blob_abs_end");

	data_मुक्त(strbuf);
पूर्ण

काष्ठा inbuf अणु
	अक्षर *base, *limit, *ptr;
पूर्ण;

अटल व्योम inbuf_init(काष्ठा inbuf *inb, व्योम *base, व्योम *limit)
अणु
	inb->base = base;
	inb->limit = limit;
	inb->ptr = inb->base;
पूर्ण

अटल व्योम flat_पढ़ो_chunk(काष्ठा inbuf *inb, व्योम *p, पूर्णांक len)
अणु
	अगर ((inb->ptr + len) > inb->limit)
		die("Premature end of data parsing flat device tree\n");

	स_नकल(p, inb->ptr, len);

	inb->ptr += len;
पूर्ण

अटल uपूर्णांक32_t flat_पढ़ो_word(काष्ठा inbuf *inb)
अणु
	fdt32_t val;

	निश्चित(((inb->ptr - inb->base) % माप(val)) == 0);

	flat_पढ़ो_chunk(inb, &val, माप(val));

	वापस fdt32_to_cpu(val);
पूर्ण

अटल व्योम flat_realign(काष्ठा inbuf *inb, पूर्णांक align)
अणु
	पूर्णांक off = inb->ptr - inb->base;

	inb->ptr = inb->base + ALIGN(off, align);
	अगर (inb->ptr > inb->limit)
		die("Premature end of data parsing flat device tree\n");
पूर्ण

अटल अक्षर *flat_पढ़ो_string(काष्ठा inbuf *inb)
अणु
	पूर्णांक len = 0;
	स्थिर अक्षर *p = inb->ptr;
	अक्षर *str;

	करो अणु
		अगर (p >= inb->limit)
			die("Premature end of data parsing flat device tree\n");
		len++;
	पूर्ण जबतक ((*p++) != '\0');

	str = xstrdup(inb->ptr);

	inb->ptr += len;

	flat_realign(inb, माप(uपूर्णांक32_t));

	वापस str;
पूर्ण

अटल काष्ठा data flat_पढ़ो_data(काष्ठा inbuf *inb, पूर्णांक len)
अणु
	काष्ठा data d = empty_data;

	अगर (len == 0)
		वापस empty_data;

	d = data_grow_क्रम(d, len);
	d.len = len;

	flat_पढ़ो_chunk(inb, d.val, len);

	flat_realign(inb, माप(uपूर्णांक32_t));

	वापस d;
पूर्ण

अटल अक्षर *flat_पढ़ो_stringtable(काष्ठा inbuf *inb, पूर्णांक offset)
अणु
	स्थिर अक्षर *p;

	p = inb->base + offset;
	जबतक (1) अणु
		अगर (p >= inb->limit || p < inb->base)
			die("String offset %d overruns string table\n",
			    offset);

		अगर (*p == '\0')
			अवरोध;

		p++;
	पूर्ण

	वापस xstrdup(inb->base + offset);
पूर्ण

अटल काष्ठा property *flat_पढ़ो_property(काष्ठा inbuf *dtbuf,
					   काष्ठा inbuf *strbuf, पूर्णांक flags)
अणु
	uपूर्णांक32_t proplen, stroff;
	अक्षर *name;
	काष्ठा data val;

	proplen = flat_पढ़ो_word(dtbuf);
	stroff = flat_पढ़ो_word(dtbuf);

	name = flat_पढ़ो_stringtable(strbuf, stroff);

	अगर ((flags & FTF_VARALIGN) && (proplen >= 8))
		flat_realign(dtbuf, 8);

	val = flat_पढ़ो_data(dtbuf, proplen);

	वापस build_property(name, val, शून्य);
पूर्ण


अटल काष्ठा reserve_info *flat_पढ़ो_mem_reserve(काष्ठा inbuf *inb)
अणु
	काष्ठा reserve_info *reservelist = शून्य;
	काष्ठा reserve_info *new;
	काष्ठा fdt_reserve_entry re;

	/*
	 * Each entry is a pair of u64 (addr, size) values क्रम 4 cell_t's.
	 * List terminates at an entry with size equal to zero.
	 *
	 * First pass, count entries.
	 */
	जबतक (1) अणु
		uपूर्णांक64_t address, size;

		flat_पढ़ो_chunk(inb, &re, माप(re));
		address  = fdt64_to_cpu(re.address);
		size = fdt64_to_cpu(re.size);
		अगर (size == 0)
			अवरोध;

		new = build_reserve_entry(address, size);
		reservelist = add_reserve_entry(reservelist, new);
	पूर्ण

	वापस reservelist;
पूर्ण


अटल अक्षर *nodename_from_path(स्थिर अक्षर *ppath, स्थिर अक्षर *cpath)
अणु
	पूर्णांक plen;

	plen = म_माप(ppath);

	अगर (!strstarts(cpath, ppath))
		die("Path \"%s\" is not valid as a child of \"%s\"\n",
		    cpath, ppath);

	/* root node is a special हाल */
	अगर (!streq(ppath, "/"))
		plen++;

	वापस xstrdup(cpath + plen);
पूर्ण

अटल काष्ठा node *unflatten_tree(काष्ठा inbuf *dtbuf,
				   काष्ठा inbuf *strbuf,
				   स्थिर अक्षर *parent_flatname, पूर्णांक flags)
अणु
	काष्ठा node *node;
	अक्षर *flatname;
	uपूर्णांक32_t val;

	node = build_node(शून्य, शून्य, शून्य);

	flatname = flat_पढ़ो_string(dtbuf);

	अगर (flags & FTF_FULLPATH)
		node->name = nodename_from_path(parent_flatname, flatname);
	अन्यथा
		node->name = flatname;

	करो अणु
		काष्ठा property *prop;
		काष्ठा node *child;

		val = flat_पढ़ो_word(dtbuf);
		चयन (val) अणु
		हाल FDT_PROP:
			अगर (node->children)
				ख_लिखो(मानक_त्रुटि, "Warning: Flat tree input has "
					"subnodes preceding a property.\n");
			prop = flat_पढ़ो_property(dtbuf, strbuf, flags);
			add_property(node, prop);
			अवरोध;

		हाल FDT_BEGIN_NODE:
			child = unflatten_tree(dtbuf,strbuf, flatname, flags);
			add_child(node, child);
			अवरोध;

		हाल FDT_END_NODE:
			अवरोध;

		हाल FDT_END:
			die("Premature FDT_END in device tree blob\n");
			अवरोध;

		हाल FDT_NOP:
			अगर (!(flags & FTF_NOPS))
				ख_लिखो(मानक_त्रुटि, "Warning: NOP tag found in flat tree"
					" version <16\n");

			/* Ignore */
			अवरोध;

		शेष:
			die("Invalid opcode word %08x in device tree blob\n",
			    val);
		पूर्ण
	पूर्ण जबतक (val != FDT_END_NODE);

	अगर (node->name != flatname) अणु
		मुक्त(flatname);
	पूर्ण

	वापस node;
पूर्ण


काष्ठा dt_info *dt_from_blob(स्थिर अक्षर *fname)
अणु
	खाता *f;
	fdt32_t magic_buf, totalsize_buf;
	uपूर्णांक32_t magic, totalsize, version, size_dt, boot_cpuid_phys;
	uपूर्णांक32_t off_dt, off_str, off_mem_rsvmap;
	पूर्णांक rc;
	अक्षर *blob;
	काष्ठा fdt_header *fdt;
	अक्षर *p;
	काष्ठा inbuf dtbuf, strbuf;
	काष्ठा inbuf memresvbuf;
	पूर्णांक sizeleft;
	काष्ठा reserve_info *reservelist;
	काष्ठा node *tree;
	uपूर्णांक32_t val;
	पूर्णांक flags = 0;

	f = srcfile_relative_खोलो(fname, शून्य);

	rc = ख_पढ़ो(&magic_buf, माप(magic_buf), 1, f);
	अगर (ख_त्रुटि(f))
		die("Error reading DT blob magic number: %s\n",
		    म_त्रुटि(त्रुटि_सं));
	अगर (rc < 1) अणु
		अगर (ख_पूर्ण(f))
			die("EOF reading DT blob magic number\n");
		अन्यथा
			die("Mysterious short read reading magic number\n");
	पूर्ण

	magic = fdt32_to_cpu(magic_buf);
	अगर (magic != FDT_MAGIC)
		die("Blob has incorrect magic number\n");

	rc = ख_पढ़ो(&totalsize_buf, माप(totalsize_buf), 1, f);
	अगर (ख_त्रुटि(f))
		die("Error reading DT blob size: %s\n", म_त्रुटि(त्रुटि_सं));
	अगर (rc < 1) अणु
		अगर (ख_पूर्ण(f))
			die("EOF reading DT blob size\n");
		अन्यथा
			die("Mysterious short read reading blob size\n");
	पूर्ण

	totalsize = fdt32_to_cpu(totalsize_buf);
	अगर (totalsize < FDT_V1_SIZE)
		die("DT blob size (%d) is too small\n", totalsize);

	blob = xदो_स्मृति(totalsize);

	fdt = (काष्ठा fdt_header *)blob;
	fdt->magic = cpu_to_fdt32(magic);
	fdt->totalsize = cpu_to_fdt32(totalsize);

	sizeleft = totalsize - माप(magic) - माप(totalsize);
	p = blob + माप(magic)  + माप(totalsize);

	जबतक (sizeleft) अणु
		अगर (ख_पूर्ण(f))
			die("EOF before reading %d bytes of DT blob\n",
			    totalsize);

		rc = ख_पढ़ो(p, 1, sizeleft, f);
		अगर (ख_त्रुटि(f))
			die("Error reading DT blob: %s\n",
			    म_त्रुटि(त्रुटि_सं));

		sizeleft -= rc;
		p += rc;
	पूर्ण

	off_dt = fdt32_to_cpu(fdt->off_dt_काष्ठा);
	off_str = fdt32_to_cpu(fdt->off_dt_strings);
	off_mem_rsvmap = fdt32_to_cpu(fdt->off_mem_rsvmap);
	version = fdt32_to_cpu(fdt->version);
	boot_cpuid_phys = fdt32_to_cpu(fdt->boot_cpuid_phys);

	अगर (off_mem_rsvmap >= totalsize)
		die("Mem Reserve structure offset exceeds total size\n");

	अगर (off_dt >= totalsize)
		die("DT structure offset exceeds total size\n");

	अगर (off_str > totalsize)
		die("String table offset exceeds total size\n");

	अगर (version >= 3) अणु
		uपूर्णांक32_t size_str = fdt32_to_cpu(fdt->size_dt_strings);
		अगर ((off_str+size_str < off_str) || (off_str+size_str > totalsize))
			die("String table extends past total size\n");
		inbuf_init(&strbuf, blob + off_str, blob + off_str + size_str);
	पूर्ण अन्यथा अणु
		inbuf_init(&strbuf, blob + off_str, blob + totalsize);
	पूर्ण

	अगर (version >= 17) अणु
		size_dt = fdt32_to_cpu(fdt->size_dt_काष्ठा);
		अगर ((off_dt+size_dt < off_dt) || (off_dt+size_dt > totalsize))
			die("Structure block extends past total size\n");
	पूर्ण

	अगर (version < 16) अणु
		flags |= FTF_FULLPATH | FTF_NAMEPROPS | FTF_VARALIGN;
	पूर्ण अन्यथा अणु
		flags |= FTF_NOPS;
	पूर्ण

	inbuf_init(&memresvbuf,
		   blob + off_mem_rsvmap, blob + totalsize);
	inbuf_init(&dtbuf, blob + off_dt, blob + totalsize);

	reservelist = flat_पढ़ो_mem_reserve(&memresvbuf);

	val = flat_पढ़ो_word(&dtbuf);

	अगर (val != FDT_BEGIN_NODE)
		die("Device tree blob doesn't begin with FDT_BEGIN_NODE (begins with 0x%08x)\n", val);

	tree = unflatten_tree(&dtbuf, &strbuf, "", flags);

	val = flat_पढ़ो_word(&dtbuf);
	अगर (val != FDT_END)
		die("Device tree blob doesn't end with FDT_END\n");

	मुक्त(blob);

	ख_बंद(f);

	वापस build_dt_info(DTSF_V1, reservelist, tree, boot_cpuid_phys);
पूर्ण
