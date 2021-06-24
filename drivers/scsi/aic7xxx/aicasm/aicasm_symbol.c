<शैली गुरु>
/*
 * Aic7xxx SCSI host adapter firmware assembler symbol table implementation
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
 * $Id: //depot/aic7xxx/aic7xxx/aicयंत्र/aicयंत्र_symbol.c#24 $
 *
 * $FreeBSD$
 */

#समावेश <sys/types.h>

#समावेश "aicdb.h"
#समावेश <fcntl.h>
#समावेश <पूर्णांकtypes.h>
#समावेश <regex.h>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <sysनिकासs.h>

#समावेश "aicasm_symbol.h"
#समावेश "aicasm.h"

अटल DB *symtable;

symbol_t *
symbol_create(अक्षर *name)
अणु
	symbol_t *new_symbol;

	new_symbol = (symbol_t *)दो_स्मृति(माप(symbol_t));
	अगर (new_symbol == शून्य) अणु
		लिखो_त्रुटि("Unable to create new symbol");
		निकास(EX_SOFTWARE);
	पूर्ण
	स_रखो(new_symbol, 0, माप(*new_symbol));
	new_symbol->name = strdup(name);
	अगर (new_symbol->name == शून्य)
		 stop("Unable to strdup symbol name", EX_SOFTWARE);
	new_symbol->type = UNINITIALIZED;
	new_symbol->count = 1;
	वापस (new_symbol);
पूर्ण

व्योम
symbol_delete(symbol_t *symbol)
अणु
	अगर (symtable != शून्य) अणु
		DBT	 key;

		key.data = symbol->name;
		key.size = म_माप(symbol->name);
		symtable->del(symtable, &key, /*flags*/0);
	पूर्ण
	चयन(symbol->type) अणु
	हाल SCBLOC:
	हाल SRAMLOC:
	हाल REGISTER:
		अगर (symbol->info.rinfo != शून्य)
			मुक्त(symbol->info.rinfo);
		अवरोध;
	हाल ALIAS:
		अगर (symbol->info.ainfo != शून्य)
			मुक्त(symbol->info.ainfo);
		अवरोध;
	हाल MASK:
	हाल FIELD:
	हाल ENUM:
	हाल ENUM_ENTRY:
		अगर (symbol->info.finfo != शून्य) अणु
			symlist_मुक्त(&symbol->info.finfo->symrefs);
			मुक्त(symbol->info.finfo);
		पूर्ण
		अवरोध;
	हाल DOWNLOAD_CONST:
	हाल CONST:
		अगर (symbol->info.cinfo != शून्य)
			मुक्त(symbol->info.cinfo);
		अवरोध;
	हाल LABEL:
		अगर (symbol->info.linfo != शून्य)
			मुक्त(symbol->info.linfo);
		अवरोध;
	हाल UNINITIALIZED:
	शेष:
		अवरोध;
	पूर्ण
	मुक्त(symbol->name);
	मुक्त(symbol);
पूर्ण

व्योम
symtable_खोलो()
अणु
	symtable = dbखोलो(/*filename*/शून्य,
			  O_CREAT | O_NONBLOCK | O_RDWR, /*mode*/0, DB_HASH,
			  /*खोलोinfo*/शून्य);

	अगर (symtable == शून्य) अणु
		लिखो_त्रुटि("Symbol table creation failed");
		निकास(EX_SOFTWARE);
		/* NOTREACHED */
	पूर्ण
पूर्ण

व्योम
symtable_बंद()
अणु
	अगर (symtable != शून्य) अणु
		DBT	 key;
		DBT	 data;

		जबतक (symtable->seq(symtable, &key, &data, R_FIRST) == 0) अणु
			symbol_t *stored_ptr;

			स_नकल(&stored_ptr, data.data, माप(stored_ptr));
			symbol_delete(stored_ptr);
		पूर्ण
		symtable->बंद(symtable);
	पूर्ण
पूर्ण

/*
 * The semantics of get is to वापस an uninitialized symbol entry
 * अगर a lookup fails.
 */
symbol_t *
symtable_get(अक्षर *name)
अणु
	symbol_t *stored_ptr;
	DBT	  key;
	DBT	  data;
	पूर्णांक	  retval;

	key.data = (व्योम *)name;
	key.size = म_माप(name);

	अगर ((retval = symtable->get(symtable, &key, &data, /*flags*/0)) != 0) अणु
		अगर (retval == -1) अणु
			लिखो_त्रुटि("Symbol table get operation failed");
			निकास(EX_SOFTWARE);
			/* NOTREACHED */
		पूर्ण अन्यथा अगर (retval == 1) अणु
			/* Symbol wasn't found, so create a new one */
			symbol_t *new_symbol;

			new_symbol = symbol_create(name);
			data.data = &new_symbol;
			data.size = माप(new_symbol);
			अगर (symtable->put(symtable, &key, &data,
					  /*flags*/0) !=0) अणु
				लिखो_त्रुटि("Symtable put failed");
				निकास(EX_SOFTWARE);
			पूर्ण
			वापस (new_symbol);
		पूर्ण अन्यथा अणु
			लिखो_त्रुटि("Unexpected return value from db get routine");
			निकास(EX_SOFTWARE);
			/* NOTREACHED */
		पूर्ण
	पूर्ण
	स_नकल(&stored_ptr, data.data, माप(stored_ptr));
	stored_ptr->count++;
	data.data = &stored_ptr;
	अगर (symtable->put(symtable, &key, &data, /*flags*/0) !=0) अणु
		लिखो_त्रुटि("Symtable put failed");
		निकास(EX_SOFTWARE);
	पूर्ण
	वापस (stored_ptr);
पूर्ण

symbol_node_t *
symlist_search(symlist_t *symlist, अक्षर *symname)
अणु
	symbol_node_t *curnode;

	curnode = SLIST_FIRST(symlist);
	जबतक(curnode != शून्य) अणु
		अगर (म_भेद(symname, curnode->symbol->name) == 0)
			अवरोध;
		curnode = SLIST_NEXT(curnode, links);
	पूर्ण
	वापस (curnode);
पूर्ण

व्योम
symlist_add(symlist_t *symlist, symbol_t *symbol, पूर्णांक how)
अणु
	symbol_node_t *newnode;

	newnode = (symbol_node_t *)दो_स्मृति(माप(symbol_node_t));
	अगर (newnode == शून्य) अणु
		stop("symlist_add: Unable to malloc symbol_node", EX_SOFTWARE);
		/* NOTREACHED */
	पूर्ण
	newnode->symbol = symbol;
	अगर (how == SYMLIST_SORT) अणु
		symbol_node_t *curnode;
		पूर्णांक field;

		field = FALSE;
		चयन(symbol->type) अणु
		हाल REGISTER:
		हाल SCBLOC:
		हाल SRAMLOC:
			अवरोध;
		हाल FIELD:
		हाल MASK:
		हाल ENUM:
		हाल ENUM_ENTRY:
			field = TRUE;
			अवरोध;
		शेष:
			stop("symlist_add: Invalid symbol type for sorting",
			     EX_SOFTWARE);
			/* NOTREACHED */
		पूर्ण

		curnode = SLIST_FIRST(symlist);
		अगर (curnode == शून्य
		 || (field
		  && (curnode->symbol->type > newnode->symbol->type
		   || (curnode->symbol->type == newnode->symbol->type
		    && (curnode->symbol->info.finfo->value >
			newnode->symbol->info.finfo->value))))
		 || (!field && (curnode->symbol->info.rinfo->address >
				newnode->symbol->info.rinfo->address))) अणु
			SLIST_INSERT_HEAD(symlist, newnode, links);
			वापस;
		पूर्ण

		जबतक (1) अणु
			अगर (SLIST_NEXT(curnode, links) == शून्य) अणु
				SLIST_INSERT_AFTER(curnode, newnode,
						   links);
				अवरोध;
			पूर्ण अन्यथा अणु
				symbol_t *cursymbol;

				cursymbol = SLIST_NEXT(curnode, links)->symbol;
				अगर ((field
				  && (cursymbol->type > symbol->type
				   || (cursymbol->type == symbol->type
				    && (cursymbol->info.finfo->value >
					symbol->info.finfo->value))))
				 || (!field
				   && (cursymbol->info.rinfo->address >
				       symbol->info.rinfo->address))) अणु
					SLIST_INSERT_AFTER(curnode, newnode,
							   links);
					अवरोध;
				पूर्ण
			पूर्ण
			curnode = SLIST_NEXT(curnode, links);
		पूर्ण
	पूर्ण अन्यथा अणु
		SLIST_INSERT_HEAD(symlist, newnode, links);
	पूर्ण
पूर्ण

व्योम
symlist_मुक्त(symlist_t *symlist)
अणु
	symbol_node_t *node1, *node2;

	node1 = SLIST_FIRST(symlist);
	जबतक (node1 != शून्य) अणु
		node2 = SLIST_NEXT(node1, links);
		मुक्त(node1);
		node1 = node2;
	पूर्ण
	SLIST_INIT(symlist);
पूर्ण

व्योम
symlist_merge(symlist_t *symlist_dest, symlist_t *symlist_src1,
	      symlist_t *symlist_src2)
अणु
	symbol_node_t *node;

	*symlist_dest = *symlist_src1;
	जबतक((node = SLIST_FIRST(symlist_src2)) != शून्य) अणु
		SLIST_REMOVE_HEAD(symlist_src2, links);
		SLIST_INSERT_HEAD(symlist_dest, node, links);
	पूर्ण

	/* These are now empty */
	SLIST_INIT(symlist_src1);
	SLIST_INIT(symlist_src2);
पूर्ण

व्योम
aic_prपूर्णांक_file_prologue(खाता *ofile)
अणु

	अगर (ofile == शून्य)
		वापस;

	ख_लिखो(ofile,
"/*\n"
" * DO NOT EDIT - This file is automatically generated\n"
" *		 from the following source files:\n"
" *\n"
"%s */\n",
		versions);
पूर्ण

व्योम
aic_prपूर्णांक_include(खाता *dfile, अक्षर *include_file)
अणु

	अगर (dfile == शून्य)
		वापस;
	ख_लिखो(dfile, "\n#include \"%s\"\n\n", include_file);
पूर्ण

व्योम
aic_prपूर्णांक_reg_dump_types(खाता *ofile)
अणु
	अगर (ofile == शून्य)
		वापस;

	ख_लिखो(ofile,
"typedef int (%sreg_print_t)(u_int, u_int *, u_int);\n"
"typedef struct %sreg_parse_entry {\n"
"	char	*name;\n"
"	uint8_t	 value;\n"
"	uint8_t	 mask;\n"
"} %sreg_parse_entry_t;\n"
"\n",
		prefix, prefix, prefix);
पूर्ण

अटल व्योम
aic_prपूर्णांक_reg_dump_start(खाता *dfile, symbol_node_t *regnode)
अणु
	अगर (dfile == शून्य)
		वापस;

	ख_लिखो(dfile,
"static const %sreg_parse_entry_t %s_parse_table[] = {\n",
		prefix,
		regnode->symbol->name);
पूर्ण

अटल व्योम
aic_prपूर्णांक_reg_dump_end(खाता *ofile, खाता *dfile,
		       symbol_node_t *regnode, u_पूर्णांक num_entries)
अणु
	अक्षर *lower_name;
	अक्षर *letter;

	lower_name = strdup(regnode->symbol->name);
	अगर (lower_name == शून्य)
		 stop("Unable to strdup symbol name", EX_SOFTWARE);

	क्रम (letter = lower_name; *letter != '\0'; letter++)
		*letter = छोटे(*letter);

	अगर (dfile != शून्य) अणु
		अगर (num_entries != 0)
			ख_लिखो(dfile,
"\n"
"};\n"
"\n");

		ख_लिखो(dfile,
"int\n"
"%s%s_print(u_int regvalue, u_int *cur_col, u_int wrap)\n"
"{\n"
"	return (%sprint_register(%s%s, %d, \"%s\",\n"
"	    0x%02x, regvalue, cur_col, wrap));\n"
"}\n"
"\n",
			prefix,
			lower_name,
			prefix,
			num_entries != 0 ? regnode->symbol->name : "NULL",
			num_entries != 0 ? "_parse_table" : "",
			num_entries,
			regnode->symbol->name,
			regnode->symbol->info.rinfo->address);
	पूर्ण

	ख_लिखो(ofile,
"#if AIC_DEBUG_REGISTERS\n"
"%sreg_print_t %s%s_print;\n"
"#else\n"
"#define %s%s_print(regvalue, cur_col, wrap) \\\n"
"    %sprint_register(NULL, 0, \"%s\", 0x%02x, regvalue, cur_col, wrap)\n"
"#endif\n"
"\n",
		prefix,
		prefix,
		lower_name,
		prefix,
		lower_name,
		prefix,
		regnode->symbol->name,
		regnode->symbol->info.rinfo->address);
पूर्ण

अटल व्योम
aic_prपूर्णांक_reg_dump_entry(खाता *dfile, symbol_node_t *curnode)
अणु
	पूर्णांक num_tअसल;

	अगर (dfile == शून्य)
		वापस;

	ख_लिखो(dfile,
"	{ \"%s\",",
		curnode->symbol->name);

	num_tअसल = 3 - (म_माप(curnode->symbol->name) + 5) / 8;

	जबतक (num_tअसल-- > 0)
		ख_अक्षर_दो('\t', dfile);
	ख_लिखो(dfile, "0x%02x, 0x%02x }",
		curnode->symbol->info.finfo->value,
		curnode->symbol->info.finfo->mask);
पूर्ण

व्योम
symtable_dump(खाता *ofile, खाता *dfile)
अणु
	/*
	 * Sort the रेजिस्टरs by address with a simple insertion sort.
	 * Put biपंचांगasks next to the first रेजिस्टर that defines them.
	 * Put स्थिरants at the end.
	 */
	symlist_t	 रेजिस्टरs;
	symlist_t	 masks;
	symlist_t	 स्थिरants;
	symlist_t	 करोwnload_स्थिरants;
	symlist_t	 aliases;
	symlist_t	 exported_labels;
	symbol_node_t	*curnode;
	symbol_node_t	*regnode;
	DBT		 key;
	DBT		 data;
	पूर्णांक		 flag;
	पूर्णांक		 reg_count = 0, reg_used = 0;
	u_पूर्णांक		 i;

	अगर (symtable == शून्य)
		वापस;

	SLIST_INIT(&रेजिस्टरs);
	SLIST_INIT(&masks);
	SLIST_INIT(&स्थिरants);
	SLIST_INIT(&करोwnload_स्थिरants);
	SLIST_INIT(&aliases);
	SLIST_INIT(&exported_labels);
	flag = R_FIRST;
	जबतक (symtable->seq(symtable, &key, &data, flag) == 0) अणु
		symbol_t *cursym;

		स_नकल(&cursym, data.data, माप(cursym));
		चयन(cursym->type) अणु
		हाल REGISTER:
		हाल SCBLOC:
		हाल SRAMLOC:
			symlist_add(&रेजिस्टरs, cursym, SYMLIST_SORT);
			अवरोध;
		हाल MASK:
		हाल FIELD:
		हाल ENUM:
		हाल ENUM_ENTRY:
			symlist_add(&masks, cursym, SYMLIST_SORT);
			अवरोध;
		हाल CONST:
			symlist_add(&स्थिरants, cursym,
				    SYMLIST_INSERT_HEAD);
			अवरोध;
		हाल DOWNLOAD_CONST:
			symlist_add(&करोwnload_स्थिरants, cursym,
				    SYMLIST_INSERT_HEAD);
			अवरोध;
		हाल ALIAS:
			symlist_add(&aliases, cursym,
				    SYMLIST_INSERT_HEAD);
			अवरोध;
		हाल LABEL:
			अगर (cursym->info.linfo->exported == 0)
				अवरोध;
			symlist_add(&exported_labels, cursym,
				    SYMLIST_INSERT_HEAD);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		flag = R_NEXT;
	पूर्ण

	/* Register dianostic functions/declarations first. */
	aic_prपूर्णांक_file_prologue(ofile);
	aic_prपूर्णांक_reg_dump_types(ofile);
	aic_prपूर्णांक_file_prologue(dfile);
	aic_prपूर्णांक_include(dfile, stock_include_file);
	SLIST_FOREACH(curnode, &रेजिस्टरs, links) अणु

		अगर (curnode->symbol->करोnt_generate_debug_code)
			जारी;

		चयन(curnode->symbol->type) अणु
		हाल REGISTER:
		हाल SCBLOC:
		हाल SRAMLOC:
		अणु
			symlist_t	*fields;
			symbol_node_t	*fieldnode;
			पूर्णांक		 num_entries;

			num_entries = 0;
			reg_count++;
			अगर (curnode->symbol->count == 1)
				अवरोध;
			fields = &curnode->symbol->info.rinfo->fields;
			SLIST_FOREACH(fieldnode, fields, links) अणु
				अगर (num_entries == 0)
					aic_prपूर्णांक_reg_dump_start(dfile,
								 curnode);
				अन्यथा अगर (dfile != शून्य)
					ख_माला_दो(",\n", dfile);
				num_entries++;
				aic_prपूर्णांक_reg_dump_entry(dfile, fieldnode);
			पूर्ण
			aic_prपूर्णांक_reg_dump_end(ofile, dfile,
					       curnode, num_entries);
			reg_used++;
		पूर्ण
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण
	ख_लिखो(मानक_त्रुटि, "%s: %d of %d register definitions used\n", appname,
		reg_used, reg_count);

	/* Fold in the masks and bits */
	जबतक (SLIST_FIRST(&masks) != शून्य) अणु
		अक्षर *regname;

		curnode = SLIST_FIRST(&masks);
		SLIST_REMOVE_HEAD(&masks, links);

		regnode = SLIST_FIRST(&curnode->symbol->info.finfo->symrefs);
		regname = regnode->symbol->name;
		regnode = symlist_search(&रेजिस्टरs, regname);
		SLIST_INSERT_AFTER(regnode, curnode, links);
	पूर्ण

	/* Add the aliases */
	जबतक (SLIST_FIRST(&aliases) != शून्य) अणु
		अक्षर *regname;

		curnode = SLIST_FIRST(&aliases);
		SLIST_REMOVE_HEAD(&aliases, links);

		regname = curnode->symbol->info.ainfo->parent->name;
		regnode = symlist_search(&रेजिस्टरs, regname);
		SLIST_INSERT_AFTER(regnode, curnode, links);
	पूर्ण

	/* Output generated #घोषणाs. */
	जबतक (SLIST_FIRST(&रेजिस्टरs) != शून्य) अणु
		symbol_node_t *curnode;
		u_पूर्णांक value;
		अक्षर *tab_str;
		अक्षर *tab_str2;

		curnode = SLIST_FIRST(&रेजिस्टरs);
		SLIST_REMOVE_HEAD(&रेजिस्टरs, links);
		चयन(curnode->symbol->type) अणु
		हाल REGISTER:
		हाल SCBLOC:
		हाल SRAMLOC:
			ख_लिखो(ofile, "\n");
			value = curnode->symbol->info.rinfo->address;
			tab_str = "\t";
			tab_str2 = "\t\t";
			अवरोध;
		हाल ALIAS:
		अणु
			symbol_t *parent;

			parent = curnode->symbol->info.ainfo->parent;
			value = parent->info.rinfo->address;
			tab_str = "\t";
			tab_str2 = "\t\t";
			अवरोध;
		पूर्ण
		हाल MASK:
		हाल FIELD:
		हाल ENUM:
		हाल ENUM_ENTRY:
			value = curnode->symbol->info.finfo->value;
			tab_str = "\t\t";
			tab_str2 = "\t";
			अवरोध;
		शेष:
			value = 0; /* Quiet compiler */
			tab_str = शून्य;
			tab_str2 = शून्य;
			stop("symtable_dump: Invalid symbol type "
			     "encountered", EX_SOFTWARE);
			अवरोध;
		पूर्ण
		ख_लिखो(ofile, "#define%s%-16s%s0x%02x\n",
			tab_str, curnode->symbol->name, tab_str2,
			value);
		मुक्त(curnode);
	पूर्ण
	ख_लिखो(ofile, "\n\n");

	जबतक (SLIST_FIRST(&स्थिरants) != शून्य) अणु
		symbol_node_t *curnode;

		curnode = SLIST_FIRST(&स्थिरants);
		SLIST_REMOVE_HEAD(&स्थिरants, links);
		ख_लिखो(ofile, "#define\t%-8s\t0x%02x\n",
			curnode->symbol->name,
			curnode->symbol->info.cinfo->value);
		मुक्त(curnode);
	पूर्ण

	ख_लिखो(ofile, "\n\n/* Downloaded Constant Definitions */\n");

	क्रम (i = 0; SLIST_FIRST(&करोwnload_स्थिरants) != शून्य; i++) अणु
		symbol_node_t *curnode;

		curnode = SLIST_FIRST(&करोwnload_स्थिरants);
		SLIST_REMOVE_HEAD(&करोwnload_स्थिरants, links);
		ख_लिखो(ofile, "#define\t%-8s\t0x%02x\n",
			curnode->symbol->name,
			curnode->symbol->info.cinfo->value);
		मुक्त(curnode);
	पूर्ण
	ख_लिखो(ofile, "#define\tDOWNLOAD_CONST_COUNT\t0x%02x\n", i);

	ख_लिखो(ofile, "\n\n/* Exported Labels */\n");

	जबतक (SLIST_FIRST(&exported_labels) != शून्य) अणु
		symbol_node_t *curnode;

		curnode = SLIST_FIRST(&exported_labels);
		SLIST_REMOVE_HEAD(&exported_labels, links);
		ख_लिखो(ofile, "#define\tLABEL_%-8s\t0x%02x\n",
			curnode->symbol->name,
			curnode->symbol->info.linfo->address);
		मुक्त(curnode);
	पूर्ण
पूर्ण

