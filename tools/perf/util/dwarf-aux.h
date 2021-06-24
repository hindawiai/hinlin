<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
#अगर_अघोषित _DWARF_AUX_H
#घोषणा _DWARF_AUX_H
/*
 * dwarf-aux.h : libdw auxiliary पूर्णांकerfaces
 */

#समावेश <dwarf.h>
#समावेश <elfutils/libdw.h>
#समावेश <elfutils/libdwfl.h>
#समावेश <elfutils/version.h>

काष्ठा strbuf;

/* Find the realpath of the target file */
स्थिर अक्षर *cu_find_realpath(Dwarf_Die *cu_die, स्थिर अक्षर *fname);

/* Get DW_AT_comp_dir (should be शून्य with older gcc) */
स्थिर अक्षर *cu_get_comp_dir(Dwarf_Die *cu_die);

/* Get a line number and file name क्रम given address */
पूर्णांक cu_find_lineinfo(Dwarf_Die *cudie, अचिन्हित दीर्घ addr,
		     स्थिर अक्षर **fname, पूर्णांक *lineno);

/* Walk on functions at given address */
पूर्णांक cu_walk_functions_at(Dwarf_Die *cu_die, Dwarf_Addr addr,
			 पूर्णांक (*callback)(Dwarf_Die *, व्योम *), व्योम *data);

/* Get DW_AT_linkage_name (should be शून्य क्रम C binary) */
स्थिर अक्षर *die_get_linkage_name(Dwarf_Die *dw_die);

/* Get the lowest PC in DIE (including range list) */
पूर्णांक die_entrypc(Dwarf_Die *dw_die, Dwarf_Addr *addr);

/* Ensure that this DIE is a subprogram and definition (not declaration) */
bool die_is_func_def(Dwarf_Die *dw_die);

/* Ensure that this DIE is an instance of a subprogram */
bool die_is_func_instance(Dwarf_Die *dw_die);

/* Compare diename and tname */
bool die_compare_name(Dwarf_Die *dw_die, स्थिर अक्षर *tname);

/* Matching diename with glob pattern */
bool die_match_name(Dwarf_Die *dw_die, स्थिर अक्षर *glob);

/* Get callsite line number of अंतरभूत-function instance */
पूर्णांक die_get_call_lineno(Dwarf_Die *in_die);

/* Get callsite file name of अंतरभूतd function instance */
स्थिर अक्षर *die_get_call_file(Dwarf_Die *in_die);

/* Get type die */
Dwarf_Die *die_get_type(Dwarf_Die *vr_die, Dwarf_Die *die_mem);

/* Get a type die, but skip qualअगरiers and प्रकार */
Dwarf_Die *die_get_real_type(Dwarf_Die *vr_die, Dwarf_Die *die_mem);

/* Check whether the DIE is चिन्हित or not */
bool die_is_चिन्हित_type(Dwarf_Die *tp_die);

/* Get data_member_location offset */
पूर्णांक die_get_data_member_location(Dwarf_Die *mb_die, Dwarf_Word *offs);

/* Return values क्रम die_find_child() callbacks */
क्रमागत अणु
	DIE_FIND_CB_END = 0,		/* End of Search */
	DIE_FIND_CB_CHILD = 1,		/* Search only children */
	DIE_FIND_CB_SIBLING = 2,	/* Search only siblings */
	DIE_FIND_CB_CONTINUE = 3,	/* Search children and siblings */
पूर्ण;

/* Search child DIEs */
Dwarf_Die *die_find_child(Dwarf_Die *rt_die,
			 पूर्णांक (*callback)(Dwarf_Die *, व्योम *),
			 व्योम *data, Dwarf_Die *die_mem);

/* Search a non-अंतरभूतd function including given address */
Dwarf_Die *die_find_realfunc(Dwarf_Die *cu_die, Dwarf_Addr addr,
			     Dwarf_Die *die_mem);

/* Search a non-अंतरभूतd function with tail call at given address */
Dwarf_Die *die_find_tailfunc(Dwarf_Die *cu_die, Dwarf_Addr addr,
				    Dwarf_Die *die_mem);

/* Search the top अंतरभूतd function including given address */
Dwarf_Die *die_find_top_अंतरभूतfunc(Dwarf_Die *sp_die, Dwarf_Addr addr,
				   Dwarf_Die *die_mem);

/* Search the deepest अंतरभूतd function including given address */
Dwarf_Die *die_find_अंतरभूतfunc(Dwarf_Die *sp_die, Dwarf_Addr addr,
			       Dwarf_Die *die_mem);

/* Walk on the instances of given DIE */
पूर्णांक die_walk_instances(Dwarf_Die *in_die,
		       पूर्णांक (*callback)(Dwarf_Die *, व्योम *), व्योम *data);

/* Walker on lines (Note: line number will not be sorted) */
प्रकार पूर्णांक (* line_walk_callback_t) (स्थिर अक्षर *fname, पूर्णांक lineno,
				      Dwarf_Addr addr, व्योम *data);

/*
 * Walk on lines inside given DIE. If the DIE is a subprogram, walk only on
 * the lines inside the subprogram, otherwise the DIE must be a CU DIE.
 */
पूर्णांक die_walk_lines(Dwarf_Die *rt_die, line_walk_callback_t callback, व्योम *data);

/* Find a variable called 'name' at given address */
Dwarf_Die *die_find_variable_at(Dwarf_Die *sp_die, स्थिर अक्षर *name,
				Dwarf_Addr addr, Dwarf_Die *die_mem);

/* Find a member called 'name' */
Dwarf_Die *die_find_member(Dwarf_Die *st_die, स्थिर अक्षर *name,
			   Dwarf_Die *die_mem);

/* Get the name of given variable DIE */
पूर्णांक die_get_typename(Dwarf_Die *vr_die, काष्ठा strbuf *buf);

/* Get the name and type of given variable DIE, stored as "type\tname" */
पूर्णांक die_get_varname(Dwarf_Die *vr_die, काष्ठा strbuf *buf);
पूर्णांक die_get_var_range(Dwarf_Die *sp_die, Dwarf_Die *vr_die, काष्ठा strbuf *buf);

/* Check अगर target program is compiled with optimization */
bool die_is_optimized_target(Dwarf_Die *cu_die);

/* Use next address after prologue as probe location */
व्योम die_skip_prologue(Dwarf_Die *sp_die, Dwarf_Die *cu_die,
		       Dwarf_Addr *entrypc);

#पूर्ण_अगर
