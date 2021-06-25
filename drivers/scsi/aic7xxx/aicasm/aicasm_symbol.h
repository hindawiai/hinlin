<शैली गुरु>
/*
 * Aic7xxx SCSI host adapter firmware assembler symbol table definitions
 *
 * Copyright (c) 1997 Justin T. Gibbs.
 * Copyright (c) 2002 Adaptec Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions, and the following disclaimer,
 *    without modअगरication.
 * 2. Redistributions in binary क्रमm must reproduce at minimum a disclaimer
 *    substantially similar to the "NO WARRANTY" disclaimer below
 *    ("Disclaimer") and any redistribution must be conditioned upon
 *    including a substantially similar Disclaimer requirement क्रम further
 *    binary redistribution.
 * 3. Neither the names of the above-listed copyright holders nor the names
 *    of any contributors may be used to enकरोrse or promote products derived
 *    from this software without specअगरic prior written permission.
 *
 * Alternatively, this software may be distributed under the terms of the
 * GNU General Public License ("GPL") version 2 as published by the Free
 * Software Foundation.
 *
 * NO WARRANTY
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * HOLDERS OR CONTRIBUTORS BE LIABLE FOR SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGES.
 *
 * $Id: //depot/aic7xxx/aic7xxx/aicयंत्र/aicयंत्र_symbol.h#17 $
 *
 * $FreeBSD$
 */

#समावेश "../queue.h"

प्रकार क्रमागत अणु
	UNINITIALIZED,
	REGISTER,
	ALIAS,
	SCBLOC,
	SRAMLOC,
	ENUM_ENTRY,
	FIELD,
	MASK,
	ENUM,
	CONST,
	DOWNLOAD_CONST,
	LABEL,
	CONDITIONAL,
	MACRO
पूर्ण symtype;

प्रकार क्रमागत अणु
	RO = 0x01,
	WO = 0x02,
	RW = 0x03
पूर्णamode_t;

प्रकार SLIST_HEAD(symlist, symbol_node) symlist_t;

काष्ठा reg_info अणु
	u_पूर्णांक	  address;
	पूर्णांक	  size;
	amode_t	  mode;
	symlist_t fields;
	uपूर्णांक8_t	  valid_biपंचांगask;
	uपूर्णांक8_t	  modes;
	पूर्णांक	  typecheck_masks;
पूर्ण;

काष्ठा field_info अणु
	symlist_t symrefs;
	uपूर्णांक8_t	  value;
	uपूर्णांक8_t	  mask;
पूर्ण;

काष्ठा स्थिर_info अणु
	u_पूर्णांक	value;
	पूर्णांक	define;
पूर्ण;

काष्ठा alias_info अणु
	काष्ठा symbol *parent;
पूर्ण;

काष्ठा label_info अणु
	पूर्णांक	address;
	पूर्णांक	exported;
पूर्ण;

काष्ठा cond_info अणु
	पूर्णांक	func_num;
पूर्ण;

काष्ठा macro_arg अणु
	STAILQ_ENTRY(macro_arg)	links;
	regex_t	arg_regex;
	अक्षर   *replacement_text;
पूर्ण;
STAILQ_HEAD(macro_arg_list, macro_arg);

काष्ठा macro_info अणु
	काष्ठा macro_arg_list args;
	पूर्णांक   narg;
	स्थिर अक्षर* body;
पूर्ण;

प्रकार काष्ठा expression_info अणु
        symlist_t       referenced_syms;
        पूर्णांक             value;
पूर्ण expression_t;

प्रकार काष्ठा symbol अणु
	अक्षर	*name;
	symtype	type;
	पूर्णांक	count;
	जोड़	अणु
		काष्ठा reg_info	  *rinfo;
		काष्ठा field_info *finfo;
		काष्ठा स्थिर_info *cinfo;
		काष्ठा alias_info *ainfo;
		काष्ठा label_info *linfo;
		काष्ठा cond_info  *condinfo;
		काष्ठा macro_info *macroinfo;
	पूर्ण info;
	पूर्णांक	करोnt_generate_debug_code;
पूर्ण symbol_t;

प्रकार काष्ठा symbol_ref अणु
	symbol_t *symbol;
	पूर्णांक	 offset;
पूर्ण symbol_ref_t;

प्रकार काष्ठा symbol_node अणु
	SLIST_ENTRY(symbol_node) links;
	symbol_t *symbol;
पूर्ण symbol_node_t;

प्रकार काष्ठा critical_section अणु
	TAILQ_ENTRY(critical_section) links;
	पूर्णांक begin_addr;
	पूर्णांक end_addr;
पूर्ण critical_section_t;

प्रकार क्रमागत अणु
	SCOPE_ROOT,
	SCOPE_IF,
	SCOPE_ELSE_IF,
	SCOPE_ELSE
पूर्ण scope_type;

प्रकार काष्ठा patch_info अणु
	पूर्णांक skip_patch;
	पूर्णांक skip_instr;
पूर्ण patch_info_t;

प्रकार काष्ठा scope अणु
	SLIST_ENTRY(scope) scope_stack_links;
	TAILQ_ENTRY(scope) scope_links;
	TAILQ_HEAD(, scope) inner_scope;
	scope_type type;
	पूर्णांक inner_scope_patches;
	पूर्णांक begin_addr;
        पूर्णांक end_addr;
	patch_info_t patches[2];
	पूर्णांक func_num;
पूर्ण scope_t;

TAILQ_HEAD(cs_tailq, critical_section);
SLIST_HEAD(scope_list, scope);
TAILQ_HEAD(scope_tailq, scope);

व्योम	symbol_delete(symbol_t *symbol);

व्योम	symtable_खोलो(व्योम);

व्योम	symtable_बंद(व्योम);

symbol_t *
	symtable_get(अक्षर *name);

symbol_node_t *
	symlist_search(symlist_t *symlist, अक्षर *symname);

व्योम
	symlist_add(symlist_t *symlist, symbol_t *symbol, पूर्णांक how);
#घोषणा SYMLIST_INSERT_HEAD	0x00
#घोषणा SYMLIST_SORT		0x01

व्योम	symlist_मुक्त(symlist_t *symlist);

व्योम	symlist_merge(symlist_t *symlist_dest, symlist_t *symlist_src1,
		      symlist_t *symlist_src2);
व्योम	symtable_dump(खाता *ofile, खाता *dfile);
