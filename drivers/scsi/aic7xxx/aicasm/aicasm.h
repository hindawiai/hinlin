<शैली गुरु>
/*
 * Assembler क्रम the sequencer program करोwnloaded to Aic7xxx SCSI host adapters
 *
 * Copyright (c) 1997 Justin T. Gibbs.
 * Copyright (c) 2001, 2002 Adaptec Inc.
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
 * $Id: //depot/aic7xxx/aic7xxx/aicयंत्र/aicयंत्र.h#14 $
 *
 * $FreeBSD$
 */

#समावेश "../queue.h"

#अगर_अघोषित TRUE
#घोषणा TRUE 1
#पूर्ण_अगर

#अगर_अघोषित FALSE
#घोषणा FALSE 0
#पूर्ण_अगर

प्रकार काष्ठा path_entry अणु
	अक्षर	*directory;
	पूर्णांक	quoted_includes_only;
	SLIST_ENTRY(path_entry) links;
पूर्ण *path_entry_t;

प्रकार क्रमागत अणु  
	QUOTED_INCLUDE,
	BRACKETED_INCLUDE,
	SOURCE_खाता
पूर्ण include_type;

SLIST_HEAD(path_list, path_entry);

बाह्य काष्ठा path_list search_path;
बाह्य काष्ठा cs_tailq cs_tailq;
बाह्य काष्ठा scope_list scope_stack;
बाह्य काष्ठा symlist patch_functions;
बाह्य पूर्णांक includes_search_curdir;		/* False अगर we've seen -I- */
बाह्य अक्षर *appname;
बाह्य अक्षर *stock_include_file;
बाह्य पूर्णांक yylineno;
बाह्य अक्षर *yyfilename;
बाह्य अक्षर *prefix;
बाह्य अक्षर *patch_arg_list;
बाह्य अक्षर *versions;
बाह्य पूर्णांक   src_mode;
बाह्य पूर्णांक   dst_mode;
काष्ठा symbol;

व्योम stop(स्थिर अक्षर *errstring, पूर्णांक err_code);
व्योम include_file(अक्षर *file_name, include_type type);
व्योम expand_macro(काष्ठा symbol *macro_symbol);
काष्ठा inकाष्ठाion *seq_alloc(व्योम);
काष्ठा critical_section *cs_alloc(व्योम);
काष्ठा scope *scope_alloc(व्योम);
व्योम process_scope(काष्ठा scope *);
