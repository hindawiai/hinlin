<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
#अगर_अघोषित DTC_H
#घोषणा DTC_H

/*
 * (C) Copyright David Gibson <dwg@au1.ibm.com>, IBM Corporation.  2005.
 */

#समावेश <मानकपन.स>
#समावेश <माला.स>
#समावेश <मानककोष.स>
#समावेश <मानक_निवेशt.h>
#समावेश <stdbool.h>
#समावेश <मानकतर्क.स>
#समावेश <निश्चित.स>
#समावेश <प्रकार.स>
#समावेश <त्रुटिसं.स>
#समावेश <unistd.h>
#समावेश <पूर्णांकtypes.h>

#समावेश <libfdt_env.h>
#समावेश <fdt.h>

#समावेश "util.h"

#अगर_घोषित DEBUG
#घोषणा debug(...)	म_लिखो(__VA_ARGS__)
#अन्यथा
#घोषणा debug(...)
#पूर्ण_अगर

#घोषणा DEFAULT_FDT_VERSION	17

/*
 * Command line options
 */
बाह्य पूर्णांक quiet;		/* Level of quietness */
बाह्य पूर्णांक reservक्रमागत;		/* Number of memory reservation slots */
बाह्य पूर्णांक minsize;		/* Minimum blob size */
बाह्य पूर्णांक padsize;		/* Additional padding to blob */
बाह्य पूर्णांक alignsize;		/* Additional padding to blob accroding to the alignsize */
बाह्य पूर्णांक phandle_क्रमmat;	/* Use linux,phandle or phandle properties */
बाह्य पूर्णांक generate_symbols;	/* generate symbols क्रम nodes with labels */
बाह्य पूर्णांक generate_fixups;	/* generate fixups */
बाह्य पूर्णांक स्वतः_label_aliases;	/* स्वतः generate labels -> aliases */
बाह्य पूर्णांक annotate;		/* annotate .dts with input source location */

#घोषणा PHANDLE_LEGACY	0x1
#घोषणा PHANDLE_EPAPR	0x2
#घोषणा PHANDLE_BOTH	0x3

प्रकार uपूर्णांक32_t cell_t;

अटल अंतरभूत uपूर्णांक16_t dtb_ld16(स्थिर व्योम *p)
अणु
	स्थिर uपूर्णांक8_t *bp = (स्थिर uपूर्णांक8_t *)p;

	वापस ((uपूर्णांक16_t)bp[0] << 8)
		| bp[1];
पूर्ण

अटल अंतरभूत uपूर्णांक32_t dtb_ld32(स्थिर व्योम *p)
अणु
	स्थिर uपूर्णांक8_t *bp = (स्थिर uपूर्णांक8_t *)p;

	वापस ((uपूर्णांक32_t)bp[0] << 24)
		| ((uपूर्णांक32_t)bp[1] << 16)
		| ((uपूर्णांक32_t)bp[2] << 8)
		| bp[3];
पूर्ण

अटल अंतरभूत uपूर्णांक64_t dtb_ld64(स्थिर व्योम *p)
अणु
	स्थिर uपूर्णांक8_t *bp = (स्थिर uपूर्णांक8_t *)p;

	वापस ((uपूर्णांक64_t)bp[0] << 56)
		| ((uपूर्णांक64_t)bp[1] << 48)
		| ((uपूर्णांक64_t)bp[2] << 40)
		| ((uपूर्णांक64_t)bp[3] << 32)
		| ((uपूर्णांक64_t)bp[4] << 24)
		| ((uपूर्णांक64_t)bp[5] << 16)
		| ((uपूर्णांक64_t)bp[6] << 8)
		| bp[7];
पूर्ण

#घोषणा streq(a, b)	(म_भेद((a), (b)) == 0)
#घोषणा strstarts(s, prefix)	(म_भेदन((s), (prefix), म_माप(prefix)) == 0)
#घोषणा strprefixeq(a, n, b)	(म_माप(b) == (n) && (स_भेद(a, b, n) == 0))

#घोषणा ALIGN(x, a)	(((x) + (a) - 1) & ~((a) - 1))

/* Data blobs */
क्रमागत markertype अणु
	TYPE_NONE,
	REF_PHANDLE,
	REF_PATH,
	LABEL,
	TYPE_UINT8,
	TYPE_UINT16,
	TYPE_UINT32,
	TYPE_UINT64,
	TYPE_STRING,
पूर्ण;
बाह्य स्थिर अक्षर *markername(क्रमागत markertype markertype);

काष्ठा  marker अणु
	क्रमागत markertype type;
	अचिन्हित पूर्णांक offset;
	अक्षर *ref;
	काष्ठा marker *next;
पूर्ण;

काष्ठा data अणु
	अचिन्हित पूर्णांक len;
	अक्षर *val;
	काष्ठा marker *markers;
पूर्ण;


#घोषणा empty_data ((काष्ठा data)अणु 0 /* all .members = 0 or शून्य */ पूर्ण)

#घोषणा क्रम_each_marker(m) \
	क्रम (; (m); (m) = (m)->next)
#घोषणा क्रम_each_marker_of_type(m, t) \
	क्रम_each_marker(m) \
		अगर ((m)->type == (t))

माप_प्रकार type_marker_length(काष्ठा marker *m);

व्योम data_मुक्त(काष्ठा data d);

काष्ठा data data_grow_क्रम(काष्ठा data d, अचिन्हित पूर्णांक xlen);

काष्ठा data data_copy_mem(स्थिर अक्षर *mem, पूर्णांक len);
काष्ठा data data_copy_escape_string(स्थिर अक्षर *s, पूर्णांक len);
काष्ठा data data_copy_file(खाता *f, माप_प्रकार len);

काष्ठा data data_append_data(काष्ठा data d, स्थिर व्योम *p, पूर्णांक len);
काष्ठा data data_insert_at_marker(काष्ठा data d, काष्ठा marker *m,
				  स्थिर व्योम *p, पूर्णांक len);
काष्ठा data data_merge(काष्ठा data d1, काष्ठा data d2);
काष्ठा data data_append_cell(काष्ठा data d, cell_t word);
काष्ठा data data_append_पूर्णांकeger(काष्ठा data d, uपूर्णांक64_t word, पूर्णांक bits);
काष्ठा data data_append_re(काष्ठा data d, uपूर्णांक64_t address, uपूर्णांक64_t size);
काष्ठा data data_append_addr(काष्ठा data d, uपूर्णांक64_t addr);
काष्ठा data data_append_byte(काष्ठा data d, uपूर्णांक8_t byte);
काष्ठा data data_append_zeroes(काष्ठा data d, पूर्णांक len);
काष्ठा data data_append_align(काष्ठा data d, पूर्णांक align);

काष्ठा data data_add_marker(काष्ठा data d, क्रमागत markertype type, अक्षर *ref);

bool data_is_one_string(काष्ठा data d);

/* DT स्थिरraपूर्णांकs */

#घोषणा MAX_PROPNAME_LEN	31
#घोषणा MAX_NODENAME_LEN	31

/* Live trees */
काष्ठा label अणु
	bool deleted;
	अक्षर *label;
	काष्ठा label *next;
पूर्ण;

काष्ठा bus_type अणु
	स्थिर अक्षर *name;
पूर्ण;

काष्ठा property अणु
	bool deleted;
	अक्षर *name;
	काष्ठा data val;

	काष्ठा property *next;

	काष्ठा label *labels;
	काष्ठा srcpos *srcpos;
पूर्ण;

काष्ठा node अणु
	bool deleted;
	अक्षर *name;
	काष्ठा property *proplist;
	काष्ठा node *children;

	काष्ठा node *parent;
	काष्ठा node *next_sibling;

	अक्षर *fullpath;
	पूर्णांक basenamelen;

	cell_t phandle;
	पूर्णांक addr_cells, size_cells;

	काष्ठा label *labels;
	स्थिर काष्ठा bus_type *bus;
	काष्ठा srcpos *srcpos;

	bool omit_अगर_unused, is_referenced;
पूर्ण;

#घोषणा क्रम_each_label_withdel(l0, l) \
	क्रम ((l) = (l0); (l); (l) = (l)->next)

#घोषणा क्रम_each_label(l0, l) \
	क्रम_each_label_withdel(l0, l) \
		अगर (!(l)->deleted)

#घोषणा क्रम_each_property_withdel(n, p) \
	क्रम ((p) = (n)->proplist; (p); (p) = (p)->next)

#घोषणा क्रम_each_property(n, p) \
	क्रम_each_property_withdel(n, p) \
		अगर (!(p)->deleted)

#घोषणा क्रम_each_child_withdel(n, c) \
	क्रम ((c) = (n)->children; (c); (c) = (c)->next_sibling)

#घोषणा क्रम_each_child(n, c) \
	क्रम_each_child_withdel(n, c) \
		अगर (!(c)->deleted)

व्योम add_label(काष्ठा label **labels, अक्षर *label);
व्योम delete_labels(काष्ठा label **labels);

काष्ठा property *build_property(अक्षर *name, काष्ठा data val,
				काष्ठा srcpos *srcpos);
काष्ठा property *build_property_delete(अक्षर *name);
काष्ठा property *chain_property(काष्ठा property *first, काष्ठा property *list);
काष्ठा property *reverse_properties(काष्ठा property *first);

काष्ठा node *build_node(काष्ठा property *proplist, काष्ठा node *children,
			काष्ठा srcpos *srcpos);
काष्ठा node *build_node_delete(काष्ठा srcpos *srcpos);
काष्ठा node *name_node(काष्ठा node *node, अक्षर *name);
काष्ठा node *omit_node_अगर_unused(काष्ठा node *node);
काष्ठा node *reference_node(काष्ठा node *node);
काष्ठा node *chain_node(काष्ठा node *first, काष्ठा node *list);
काष्ठा node *merge_nodes(काष्ठा node *old_node, काष्ठा node *new_node);
काष्ठा node *add_orphan_node(काष्ठा node *old_node, काष्ठा node *new_node, अक्षर *ref);

व्योम add_property(काष्ठा node *node, काष्ठा property *prop);
व्योम delete_property_by_name(काष्ठा node *node, अक्षर *name);
व्योम delete_property(काष्ठा property *prop);
व्योम add_child(काष्ठा node *parent, काष्ठा node *child);
व्योम delete_node_by_name(काष्ठा node *parent, अक्षर *name);
व्योम delete_node(काष्ठा node *node);
व्योम append_to_property(काष्ठा node *node,
			अक्षर *name, स्थिर व्योम *data, पूर्णांक len,
			क्रमागत markertype type);

स्थिर अक्षर *get_unitname(काष्ठा node *node);
काष्ठा property *get_property(काष्ठा node *node, स्थिर अक्षर *propname);
cell_t propval_cell(काष्ठा property *prop);
cell_t propval_cell_n(काष्ठा property *prop, अचिन्हित पूर्णांक n);
काष्ठा property *get_property_by_label(काष्ठा node *tree, स्थिर अक्षर *label,
				       काष्ठा node **node);
काष्ठा marker *get_marker_label(काष्ठा node *tree, स्थिर अक्षर *label,
				काष्ठा node **node, काष्ठा property **prop);
काष्ठा node *get_subnode(काष्ठा node *node, स्थिर अक्षर *nodename);
काष्ठा node *get_node_by_path(काष्ठा node *tree, स्थिर अक्षर *path);
काष्ठा node *get_node_by_label(काष्ठा node *tree, स्थिर अक्षर *label);
काष्ठा node *get_node_by_phandle(काष्ठा node *tree, cell_t phandle);
काष्ठा node *get_node_by_ref(काष्ठा node *tree, स्थिर अक्षर *ref);
cell_t get_node_phandle(काष्ठा node *root, काष्ठा node *node);

uपूर्णांक32_t guess_boot_cpuid(काष्ठा node *tree);

/* Boot info (tree plus memreserve inक्रमmation */

काष्ठा reserve_info अणु
	uपूर्णांक64_t address, size;

	काष्ठा reserve_info *next;

	काष्ठा label *labels;
पूर्ण;

काष्ठा reserve_info *build_reserve_entry(uपूर्णांक64_t start, uपूर्णांक64_t len);
काष्ठा reserve_info *chain_reserve_entry(काष्ठा reserve_info *first,
					 काष्ठा reserve_info *list);
काष्ठा reserve_info *add_reserve_entry(काष्ठा reserve_info *list,
				       काष्ठा reserve_info *new);


काष्ठा dt_info अणु
	अचिन्हित पूर्णांक dtsflags;
	काष्ठा reserve_info *reservelist;
	uपूर्णांक32_t boot_cpuid_phys;
	काष्ठा node *dt;		/* the device tree */
	स्थिर अक्षर *outname;		/* filename being written to, "-" क्रम मानक_निकास */
पूर्ण;

/* DTS version flags definitions */
#घोषणा DTSF_V1		0x0001	/* /dts-v1/ */
#घोषणा DTSF_PLUGIN	0x0002	/* /plugin/ */

काष्ठा dt_info *build_dt_info(अचिन्हित पूर्णांक dtsflags,
			      काष्ठा reserve_info *reservelist,
			      काष्ठा node *tree, uपूर्णांक32_t boot_cpuid_phys);
व्योम sort_tree(काष्ठा dt_info *dti);
व्योम generate_label_tree(काष्ठा dt_info *dti, अक्षर *name, bool allocph);
व्योम generate_fixups_tree(काष्ठा dt_info *dti, अक्षर *name);
व्योम generate_local_fixups_tree(काष्ठा dt_info *dti, अक्षर *name);

/* Checks */

व्योम parse_checks_option(bool warn, bool error, स्थिर अक्षर *arg);
व्योम process_checks(bool क्रमce, काष्ठा dt_info *dti);

/* Flattened trees */

व्योम dt_to_blob(खाता *f, काष्ठा dt_info *dti, पूर्णांक version);
व्योम dt_to_यंत्र(खाता *f, काष्ठा dt_info *dti, पूर्णांक version);

काष्ठा dt_info *dt_from_blob(स्थिर अक्षर *fname);

/* Tree source */

व्योम dt_to_source(खाता *f, काष्ठा dt_info *dti);
काष्ठा dt_info *dt_from_source(स्थिर अक्षर *f);

/* YAML source */

व्योम dt_to_yaml(खाता *f, काष्ठा dt_info *dti);

/* FS trees */

काष्ठा dt_info *dt_from_fs(स्थिर अक्षर *स_नाम);

#पूर्ण_अगर /* DTC_H */
