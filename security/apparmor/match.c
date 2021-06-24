<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * AppArmor security module
 *
 * This file contains AppArmor dfa based regular expression matching engine
 *
 * Copyright (C) 1998-2008 Novell/SUSE
 * Copyright 2009-2012 Canonical Ltd.
 */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/slab.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/err.h>
#समावेश <linux/kref.h>

#समावेश "include/lib.h"
#समावेश "include/match.h"

#घोषणा base_idx(X) ((X) & 0xffffff)

अटल अक्षर nulldfa_src[] = अणु
	#समावेश "nulldfa.in"
पूर्ण;
काष्ठा aa_dfa *nulldfa;

अटल अक्षर stacksplitdfa_src[] = अणु
	#समावेश "stacksplitdfa.in"
पूर्ण;
काष्ठा aa_dfa *stacksplitdfa;

पूर्णांक aa_setup_dfa_engine(व्योम)
अणु
	पूर्णांक error;

	nulldfa = aa_dfa_unpack(nulldfa_src, माप(nulldfa_src),
				TO_ACCEPT1_FLAG(YYTD_DATA32) |
				TO_ACCEPT2_FLAG(YYTD_DATA32));
	अगर (IS_ERR(nulldfa)) अणु
		error = PTR_ERR(nulldfa);
		nulldfa = शून्य;
		वापस error;
	पूर्ण

	stacksplitdfa = aa_dfa_unpack(stacksplitdfa_src,
				      माप(stacksplitdfa_src),
				      TO_ACCEPT1_FLAG(YYTD_DATA32) |
				      TO_ACCEPT2_FLAG(YYTD_DATA32));
	अगर (IS_ERR(stacksplitdfa)) अणु
		aa_put_dfa(nulldfa);
		nulldfa = शून्य;
		error = PTR_ERR(stacksplitdfa);
		stacksplitdfa = शून्य;
		वापस error;
	पूर्ण

	वापस 0;
पूर्ण

व्योम aa_tearकरोwn_dfa_engine(व्योम)
अणु
	aa_put_dfa(stacksplitdfa);
	aa_put_dfa(nulldfa);
पूर्ण

/**
 * unpack_table - unpack a dfa table (one of accept, शेष, base, next check)
 * @blob: data to unpack (NOT शून्य)
 * @bsize: size of blob
 *
 * Returns: poपूर्णांकer to table अन्यथा शून्य on failure
 *
 * NOTE: must be मुक्तd by kvमुक्त (not kमुक्त)
 */
अटल काष्ठा table_header *unpack_table(अक्षर *blob, माप_प्रकार bsize)
अणु
	काष्ठा table_header *table = शून्य;
	काष्ठा table_header th;
	माप_प्रकार tsize;

	अगर (bsize < माप(काष्ठा table_header))
		जाओ out;

	/* loaded td_id's start at 1, subtract 1 now to aव्योम करोing
	 * it every समय we use td_id as an index
	 */
	th.td_id = be16_to_cpu(*(__be16 *) (blob)) - 1;
	अगर (th.td_id > YYTD_ID_MAX)
		जाओ out;
	th.td_flags = be16_to_cpu(*(__be16 *) (blob + 2));
	th.td_lolen = be32_to_cpu(*(__be32 *) (blob + 8));
	blob += माप(काष्ठा table_header);

	अगर (!(th.td_flags == YYTD_DATA16 || th.td_flags == YYTD_DATA32 ||
	      th.td_flags == YYTD_DATA8))
		जाओ out;

	/* अगर we have a table it must have some entries */
	अगर (th.td_lolen == 0)
		जाओ out;
	tsize = table_size(th.td_lolen, th.td_flags);
	अगर (bsize < tsize)
		जाओ out;

	table = kvzalloc(tsize, GFP_KERNEL);
	अगर (table) अणु
		table->td_id = th.td_id;
		table->td_flags = th.td_flags;
		table->td_lolen = th.td_lolen;
		अगर (th.td_flags == YYTD_DATA8)
			UNPACK_ARRAY(table->td_data, blob, th.td_lolen,
				     u8, u8, byte_to_byte);
		अन्यथा अगर (th.td_flags == YYTD_DATA16)
			UNPACK_ARRAY(table->td_data, blob, th.td_lolen,
				     u16, __be16, be16_to_cpu);
		अन्यथा अगर (th.td_flags == YYTD_DATA32)
			UNPACK_ARRAY(table->td_data, blob, th.td_lolen,
				     u32, __be32, be32_to_cpu);
		अन्यथा
			जाओ fail;
		/* अगर table was vदो_स्मृतिed make sure the page tables are synced
		 * beक्रमe it is used, as it goes live to all cpus.
		 */
		अगर (is_vदो_स्मृति_addr(table))
			vm_unmap_aliases();
	पूर्ण

out:
	वापस table;
fail:
	kvमुक्त(table);
	वापस शून्य;
पूर्ण

/**
 * verअगरy_table_headers - verअगरy that the tables headers are as expected
 * @tables - array of dfa tables to check (NOT शून्य)
 * @flags: flags controlling what type of accept table are acceptable
 *
 * Assumes dfa has gone through the first pass verअगरication करोne by unpacking
 * NOTE: this करोes not valid accept table values
 *
 * Returns: %0 अन्यथा error code on failure to verअगरy
 */
अटल पूर्णांक verअगरy_table_headers(काष्ठा table_header **tables, पूर्णांक flags)
अणु
	माप_प्रकार state_count, trans_count;
	पूर्णांक error = -EPROTO;

	/* check that required tables exist */
	अगर (!(tables[YYTD_ID_DEF] && tables[YYTD_ID_BASE] &&
	      tables[YYTD_ID_NXT] && tables[YYTD_ID_CHK]))
		जाओ out;

	/* accept.size == शेष.size == base.size */
	state_count = tables[YYTD_ID_BASE]->td_lolen;
	अगर (ACCEPT1_FLAGS(flags)) अणु
		अगर (!tables[YYTD_ID_ACCEPT])
			जाओ out;
		अगर (state_count != tables[YYTD_ID_ACCEPT]->td_lolen)
			जाओ out;
	पूर्ण
	अगर (ACCEPT2_FLAGS(flags)) अणु
		अगर (!tables[YYTD_ID_ACCEPT2])
			जाओ out;
		अगर (state_count != tables[YYTD_ID_ACCEPT2]->td_lolen)
			जाओ out;
	पूर्ण
	अगर (state_count != tables[YYTD_ID_DEF]->td_lolen)
		जाओ out;

	/* next.size == chk.size */
	trans_count = tables[YYTD_ID_NXT]->td_lolen;
	अगर (trans_count != tables[YYTD_ID_CHK]->td_lolen)
		जाओ out;

	/* अगर equivalence classes then its table size must be 256 */
	अगर (tables[YYTD_ID_EC] && tables[YYTD_ID_EC]->td_lolen != 256)
		जाओ out;

	error = 0;
out:
	वापस error;
पूर्ण

/**
 * verअगरy_dfa - verअगरy that transitions and states in the tables are in bounds.
 * @dfa: dfa to test  (NOT शून्य)
 *
 * Assumes dfa has gone through the first pass verअगरication करोne by unpacking
 * NOTE: this करोes not valid accept table values
 *
 * Returns: %0 अन्यथा error code on failure to verअगरy
 */
अटल पूर्णांक verअगरy_dfa(काष्ठा aa_dfa *dfa)
अणु
	माप_प्रकार i, state_count, trans_count;
	पूर्णांक error = -EPROTO;

	state_count = dfa->tables[YYTD_ID_BASE]->td_lolen;
	trans_count = dfa->tables[YYTD_ID_NXT]->td_lolen;
	अगर (state_count == 0)
		जाओ out;
	क्रम (i = 0; i < state_count; i++) अणु
		अगर (!(BASE_TABLE(dfa)[i] & MATCH_FLAG_DIFF_ENCODE) &&
		    (DEFAULT_TABLE(dfa)[i] >= state_count))
			जाओ out;
		अगर (BASE_TABLE(dfa)[i] & MATCH_FLAGS_INVALID) अणु
			pr_err("AppArmor DFA state with invalid match flags");
			जाओ out;
		पूर्ण
		अगर ((BASE_TABLE(dfa)[i] & MATCH_FLAG_DIFF_ENCODE)) अणु
			अगर (!(dfa->flags & YYTH_FLAG_DIFF_ENCODE)) अणु
				pr_err("AppArmor DFA diff encoded transition state without header flag");
				जाओ out;
			पूर्ण
		पूर्ण
		अगर ((BASE_TABLE(dfa)[i] & MATCH_FLAG_OOB_TRANSITION)) अणु
			अगर (base_idx(BASE_TABLE(dfa)[i]) < dfa->max_oob) अणु
				pr_err("AppArmor DFA out of bad transition out of range");
				जाओ out;
			पूर्ण
			अगर (!(dfa->flags & YYTH_FLAG_OOB_TRANS)) अणु
				pr_err("AppArmor DFA out of bad transition state without header flag");
				जाओ out;
			पूर्ण
		पूर्ण
		अगर (base_idx(BASE_TABLE(dfa)[i]) + 255 >= trans_count) अणु
			pr_err("AppArmor DFA next/check upper bounds error\n");
			जाओ out;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < trans_count; i++) अणु
		अगर (NEXT_TABLE(dfa)[i] >= state_count)
			जाओ out;
		अगर (CHECK_TABLE(dfa)[i] >= state_count)
			जाओ out;
	पूर्ण

	/* Now that all the other tables are verअगरied, verअगरy dअगरfencoding */
	क्रम (i = 0; i < state_count; i++) अणु
		माप_प्रकार j, k;

		क्रम (j = i;
		     (BASE_TABLE(dfa)[j] & MATCH_FLAG_DIFF_ENCODE) &&
		     !(BASE_TABLE(dfa)[j] & MARK_DIFF_ENCODE);
		     j = k) अणु
			k = DEFAULT_TABLE(dfa)[j];
			अगर (j == k)
				जाओ out;
			अगर (k < j)
				अवरोध;		/* alपढ़ोy verअगरied */
			BASE_TABLE(dfa)[j] |= MARK_DIFF_ENCODE;
		पूर्ण
	पूर्ण
	error = 0;

out:
	वापस error;
पूर्ण

/**
 * dfa_मुक्त - मुक्त a dfa allocated by aa_dfa_unpack
 * @dfa: the dfa to मुक्त  (MAYBE शून्य)
 *
 * Requires: reference count to dfa == 0
 */
अटल व्योम dfa_मुक्त(काष्ठा aa_dfa *dfa)
अणु
	अगर (dfa) अणु
		पूर्णांक i;

		क्रम (i = 0; i < ARRAY_SIZE(dfa->tables); i++) अणु
			kvमुक्त(dfa->tables[i]);
			dfa->tables[i] = शून्य;
		पूर्ण
		kमुक्त(dfa);
	पूर्ण
पूर्ण

/**
 * aa_dfa_मुक्त_kref - मुक्त aa_dfa by kref (called by aa_put_dfa)
 * @kr: kref callback क्रम मुक्तing of a dfa  (NOT शून्य)
 */
व्योम aa_dfa_मुक्त_kref(काष्ठा kref *kref)
अणु
	काष्ठा aa_dfa *dfa = container_of(kref, काष्ठा aa_dfa, count);
	dfa_मुक्त(dfa);
पूर्ण

/**
 * aa_dfa_unpack - unpack the binary tables of a serialized dfa
 * @blob: aligned serialized stream of data to unpack  (NOT शून्य)
 * @size: size of data to unpack
 * @flags: flags controlling what type of accept tables are acceptable
 *
 * Unpack a dfa that has been serialized.  To find inक्रमmation on the dfa
 * क्रमmat look in Documentation/admin-guide/LSM/apparmor.rst
 * Assumes the dfa @blob stream has been aligned on a 8 byte boundary
 *
 * Returns: an unpacked dfa पढ़ोy क्रम matching or ERR_PTR on failure
 */
काष्ठा aa_dfa *aa_dfa_unpack(व्योम *blob, माप_प्रकार size, पूर्णांक flags)
अणु
	पूर्णांक hsize;
	पूर्णांक error = -ENOMEM;
	अक्षर *data = blob;
	काष्ठा table_header *table = शून्य;
	काष्ठा aa_dfa *dfa = kzalloc(माप(काष्ठा aa_dfa), GFP_KERNEL);
	अगर (!dfa)
		जाओ fail;

	kref_init(&dfa->count);

	error = -EPROTO;

	/* get dfa table set header */
	अगर (size < माप(काष्ठा table_set_header))
		जाओ fail;

	अगर (ntohl(*(__be32 *) data) != YYTH_MAGIC)
		जाओ fail;

	hsize = ntohl(*(__be32 *) (data + 4));
	अगर (size < hsize)
		जाओ fail;

	dfa->flags = ntohs(*(__be16 *) (data + 12));
	अगर (dfa->flags & ~(YYTH_FLAGS))
		जाओ fail;

	/*
	 * TODO: needed क्रम dfa to support more than 1 oob
	 * अगर (dfa->flags & YYTH_FLAGS_OOB_TRANS) अणु
	 *	अगर (hsize < 16 + 4)
	 *		जाओ fail;
	 *	dfa->max_oob = ntol(*(__be32 *) (data + 16));
	 *	अगर (dfa->max <= MAX_OOB_SUPPORTED) अणु
	 *		pr_err("AppArmor DFA OOB greater than supported\n");
	 *		जाओ fail;
	 *	पूर्ण
	 * पूर्ण
	 */
	dfa->max_oob = 1;

	data += hsize;
	size -= hsize;

	जबतक (size > 0) अणु
		table = unpack_table(data, size);
		अगर (!table)
			जाओ fail;

		चयन (table->td_id) अणु
		हाल YYTD_ID_ACCEPT:
			अगर (!(table->td_flags & ACCEPT1_FLAGS(flags)))
				जाओ fail;
			अवरोध;
		हाल YYTD_ID_ACCEPT2:
			अगर (!(table->td_flags & ACCEPT2_FLAGS(flags)))
				जाओ fail;
			अवरोध;
		हाल YYTD_ID_BASE:
			अगर (table->td_flags != YYTD_DATA32)
				जाओ fail;
			अवरोध;
		हाल YYTD_ID_DEF:
		हाल YYTD_ID_NXT:
		हाल YYTD_ID_CHK:
			अगर (table->td_flags != YYTD_DATA16)
				जाओ fail;
			अवरोध;
		हाल YYTD_ID_EC:
			अगर (table->td_flags != YYTD_DATA8)
				जाओ fail;
			अवरोध;
		शेष:
			जाओ fail;
		पूर्ण
		/* check क्रम duplicate table entry */
		अगर (dfa->tables[table->td_id])
			जाओ fail;
		dfa->tables[table->td_id] = table;
		data += table_size(table->td_lolen, table->td_flags);
		size -= table_size(table->td_lolen, table->td_flags);
		table = शून्य;
	पूर्ण
	error = verअगरy_table_headers(dfa->tables, flags);
	अगर (error)
		जाओ fail;

	अगर (flags & DFA_FLAG_VERIFY_STATES) अणु
		error = verअगरy_dfa(dfa);
		अगर (error)
			जाओ fail;
	पूर्ण

	वापस dfa;

fail:
	kvमुक्त(table);
	dfa_मुक्त(dfa);
	वापस ERR_PTR(error);
पूर्ण

#घोषणा match_अक्षर(state, def, base, next, check, C)	\
करो अणु							\
	u32 b = (base)[(state)];			\
	अचिन्हित पूर्णांक pos = base_idx(b) + (C);		\
	अगर ((check)[pos] != (state)) अणु			\
		(state) = (def)[(state)];		\
		अगर (b & MATCH_FLAG_DIFF_ENCODE)		\
			जारी;			\
		अवरोध;					\
	पूर्ण						\
	(state) = (next)[pos];				\
	अवरोध;						\
पूर्ण जबतक (1)

/**
 * aa_dfa_match_len - traverse @dfa to find state @str stops at
 * @dfa: the dfa to match @str against  (NOT शून्य)
 * @start: the state of the dfa to start matching in
 * @str: the string of bytes to match against the dfa  (NOT शून्य)
 * @len: length of the string of bytes to match
 *
 * aa_dfa_match_len will match @str against the dfa and वापस the state it
 * finished matching in. The final state can be used to look up the accepting
 * label, or as the start state of a continuing match.
 *
 * This function will happily match again the 0 byte and only finishes
 * when @len input is consumed.
 *
 * Returns: final state reached after input is consumed
 */
अचिन्हित पूर्णांक aa_dfa_match_len(काष्ठा aa_dfa *dfa, अचिन्हित पूर्णांक start,
			      स्थिर अक्षर *str, पूर्णांक len)
अणु
	u16 *def = DEFAULT_TABLE(dfa);
	u32 *base = BASE_TABLE(dfa);
	u16 *next = NEXT_TABLE(dfa);
	u16 *check = CHECK_TABLE(dfa);
	अचिन्हित पूर्णांक state = start;

	अगर (state == 0)
		वापस 0;

	/* current state is <state>, matching अक्षरacter *str */
	अगर (dfa->tables[YYTD_ID_EC]) अणु
		/* Equivalence class table defined */
		u8 *equiv = EQUIV_TABLE(dfa);
		क्रम (; len; len--)
			match_अक्षर(state, def, base, next, check,
				   equiv[(u8) *str++]);
	पूर्ण अन्यथा अणु
		/* शेष is direct to next state */
		क्रम (; len; len--)
			match_अक्षर(state, def, base, next, check, (u8) *str++);
	पूर्ण

	वापस state;
पूर्ण

/**
 * aa_dfa_match - traverse @dfa to find state @str stops at
 * @dfa: the dfa to match @str against  (NOT शून्य)
 * @start: the state of the dfa to start matching in
 * @str: the null terminated string of bytes to match against the dfa (NOT शून्य)
 *
 * aa_dfa_match will match @str against the dfa and वापस the state it
 * finished matching in. The final state can be used to look up the accepting
 * label, or as the start state of a continuing match.
 *
 * Returns: final state reached after input is consumed
 */
अचिन्हित पूर्णांक aa_dfa_match(काष्ठा aa_dfa *dfa, अचिन्हित पूर्णांक start,
			  स्थिर अक्षर *str)
अणु
	u16 *def = DEFAULT_TABLE(dfa);
	u32 *base = BASE_TABLE(dfa);
	u16 *next = NEXT_TABLE(dfa);
	u16 *check = CHECK_TABLE(dfa);
	अचिन्हित पूर्णांक state = start;

	अगर (state == 0)
		वापस 0;

	/* current state is <state>, matching अक्षरacter *str */
	अगर (dfa->tables[YYTD_ID_EC]) अणु
		/* Equivalence class table defined */
		u8 *equiv = EQUIV_TABLE(dfa);
		/* शेष is direct to next state */
		जबतक (*str)
			match_अक्षर(state, def, base, next, check,
				   equiv[(u8) *str++]);
	पूर्ण अन्यथा अणु
		/* शेष is direct to next state */
		जबतक (*str)
			match_अक्षर(state, def, base, next, check, (u8) *str++);
	पूर्ण

	वापस state;
पूर्ण

/**
 * aa_dfa_next - step one अक्षरacter to the next state in the dfa
 * @dfa: the dfa to traverse (NOT शून्य)
 * @state: the state to start in
 * @c: the input अक्षरacter to transition on
 *
 * aa_dfa_match will step through the dfa by one input अक्षरacter @c
 *
 * Returns: state reach after input @c
 */
अचिन्हित पूर्णांक aa_dfa_next(काष्ठा aa_dfa *dfa, अचिन्हित पूर्णांक state,
			  स्थिर अक्षर c)
अणु
	u16 *def = DEFAULT_TABLE(dfa);
	u32 *base = BASE_TABLE(dfa);
	u16 *next = NEXT_TABLE(dfa);
	u16 *check = CHECK_TABLE(dfa);

	/* current state is <state>, matching अक्षरacter *str */
	अगर (dfa->tables[YYTD_ID_EC]) अणु
		/* Equivalence class table defined */
		u8 *equiv = EQUIV_TABLE(dfa);
		match_अक्षर(state, def, base, next, check, equiv[(u8) c]);
	पूर्ण अन्यथा
		match_अक्षर(state, def, base, next, check, (u8) c);

	वापस state;
पूर्ण

अचिन्हित पूर्णांक aa_dfa_outofband_transition(काष्ठा aa_dfa *dfa, अचिन्हित पूर्णांक state)
अणु
	u16 *def = DEFAULT_TABLE(dfa);
	u32 *base = BASE_TABLE(dfa);
	u16 *next = NEXT_TABLE(dfa);
	u16 *check = CHECK_TABLE(dfa);
	u32 b = (base)[(state)];

	अगर (!(b & MATCH_FLAG_OOB_TRANSITION))
		वापस DFA_NOMATCH;

	/* No Equivalence class remapping क्रम outofband transitions */
	match_अक्षर(state, def, base, next, check, -1);

	वापस state;
पूर्ण

/**
 * aa_dfa_match_until - traverse @dfa until accept state or end of input
 * @dfa: the dfa to match @str against  (NOT शून्य)
 * @start: the state of the dfa to start matching in
 * @str: the null terminated string of bytes to match against the dfa (NOT शून्य)
 * @retpos: first अक्षरacter in str after match OR end of string
 *
 * aa_dfa_match will match @str against the dfa and वापस the state it
 * finished matching in. The final state can be used to look up the accepting
 * label, or as the start state of a continuing match.
 *
 * Returns: final state reached after input is consumed
 */
अचिन्हित पूर्णांक aa_dfa_match_until(काष्ठा aa_dfa *dfa, अचिन्हित पूर्णांक start,
				स्थिर अक्षर *str, स्थिर अक्षर **retpos)
अणु
	u16 *def = DEFAULT_TABLE(dfa);
	u32 *base = BASE_TABLE(dfa);
	u16 *next = NEXT_TABLE(dfa);
	u16 *check = CHECK_TABLE(dfa);
	u32 *accept = ACCEPT_TABLE(dfa);
	अचिन्हित पूर्णांक state = start, pos;

	अगर (state == 0)
		वापस 0;

	/* current state is <state>, matching अक्षरacter *str */
	अगर (dfa->tables[YYTD_ID_EC]) अणु
		/* Equivalence class table defined */
		u8 *equiv = EQUIV_TABLE(dfa);
		/* शेष is direct to next state */
		जबतक (*str) अणु
			pos = base_idx(base[state]) + equiv[(u8) *str++];
			अगर (check[pos] == state)
				state = next[pos];
			अन्यथा
				state = def[state];
			अगर (accept[state])
				अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* शेष is direct to next state */
		जबतक (*str) अणु
			pos = base_idx(base[state]) + (u8) *str++;
			अगर (check[pos] == state)
				state = next[pos];
			अन्यथा
				state = def[state];
			अगर (accept[state])
				अवरोध;
		पूर्ण
	पूर्ण

	*retpos = str;
	वापस state;
पूर्ण

/**
 * aa_dfa_matchn_until - traverse @dfa until accept or @n bytes consumed
 * @dfa: the dfa to match @str against  (NOT शून्य)
 * @start: the state of the dfa to start matching in
 * @str: the string of bytes to match against the dfa  (NOT शून्य)
 * @n: length of the string of bytes to match
 * @retpos: first अक्षरacter in str after match OR str + n
 *
 * aa_dfa_match_len will match @str against the dfa and वापस the state it
 * finished matching in. The final state can be used to look up the accepting
 * label, or as the start state of a continuing match.
 *
 * This function will happily match again the 0 byte and only finishes
 * when @n input is consumed.
 *
 * Returns: final state reached after input is consumed
 */
अचिन्हित पूर्णांक aa_dfa_matchn_until(काष्ठा aa_dfa *dfa, अचिन्हित पूर्णांक start,
				 स्थिर अक्षर *str, पूर्णांक n, स्थिर अक्षर **retpos)
अणु
	u16 *def = DEFAULT_TABLE(dfa);
	u32 *base = BASE_TABLE(dfa);
	u16 *next = NEXT_TABLE(dfa);
	u16 *check = CHECK_TABLE(dfa);
	u32 *accept = ACCEPT_TABLE(dfa);
	अचिन्हित पूर्णांक state = start, pos;

	*retpos = शून्य;
	अगर (state == 0)
		वापस 0;

	/* current state is <state>, matching अक्षरacter *str */
	अगर (dfa->tables[YYTD_ID_EC]) अणु
		/* Equivalence class table defined */
		u8 *equiv = EQUIV_TABLE(dfa);
		/* शेष is direct to next state */
		क्रम (; n; n--) अणु
			pos = base_idx(base[state]) + equiv[(u8) *str++];
			अगर (check[pos] == state)
				state = next[pos];
			अन्यथा
				state = def[state];
			अगर (accept[state])
				अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* शेष is direct to next state */
		क्रम (; n; n--) अणु
			pos = base_idx(base[state]) + (u8) *str++;
			अगर (check[pos] == state)
				state = next[pos];
			अन्यथा
				state = def[state];
			अगर (accept[state])
				अवरोध;
		पूर्ण
	पूर्ण

	*retpos = str;
	वापस state;
पूर्ण

#घोषणा inc_wb_pos(wb)						\
करो अणु								\
	wb->pos = (wb->pos + 1) & (WB_HISTORY_SIZE - 1);		\
	wb->len = (wb->len + 1) & (WB_HISTORY_SIZE - 1);		\
पूर्ण जबतक (0)

/* For DFAs that करोn't support extended tagging of states */
अटल bool is_loop(काष्ठा match_workbuf *wb, अचिन्हित पूर्णांक state,
		    अचिन्हित पूर्णांक *adjust)
अणु
	अचिन्हित पूर्णांक pos = wb->pos;
	अचिन्हित पूर्णांक i;

	अगर (wb->history[pos] < state)
		वापस false;

	क्रम (i = 0; i <= wb->len; i++) अणु
		अगर (wb->history[pos] == state) अणु
			*adjust = i;
			वापस true;
		पूर्ण
		अगर (pos == 0)
			pos = WB_HISTORY_SIZE;
		pos--;
	पूर्ण

	*adjust = i;
	वापस true;
पूर्ण

अटल अचिन्हित पूर्णांक lefपंचांगatch_fb(काष्ठा aa_dfa *dfa, अचिन्हित पूर्णांक start,
				 स्थिर अक्षर *str, काष्ठा match_workbuf *wb,
				 अचिन्हित पूर्णांक *count)
अणु
	u16 *def = DEFAULT_TABLE(dfa);
	u32 *base = BASE_TABLE(dfa);
	u16 *next = NEXT_TABLE(dfa);
	u16 *check = CHECK_TABLE(dfa);
	अचिन्हित पूर्णांक state = start, pos;

	AA_BUG(!dfa);
	AA_BUG(!str);
	AA_BUG(!wb);
	AA_BUG(!count);

	*count = 0;
	अगर (state == 0)
		वापस 0;

	/* current state is <state>, matching अक्षरacter *str */
	अगर (dfa->tables[YYTD_ID_EC]) अणु
		/* Equivalence class table defined */
		u8 *equiv = EQUIV_TABLE(dfa);
		/* शेष is direct to next state */
		जबतक (*str) अणु
			अचिन्हित पूर्णांक adjust;

			wb->history[wb->pos] = state;
			pos = base_idx(base[state]) + equiv[(u8) *str++];
			अगर (check[pos] == state)
				state = next[pos];
			अन्यथा
				state = def[state];
			अगर (is_loop(wb, state, &adjust)) अणु
				state = aa_dfa_match(dfa, state, str);
				*count -= adjust;
				जाओ out;
			पूर्ण
			inc_wb_pos(wb);
			(*count)++;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* शेष is direct to next state */
		जबतक (*str) अणु
			अचिन्हित पूर्णांक adjust;

			wb->history[wb->pos] = state;
			pos = base_idx(base[state]) + (u8) *str++;
			अगर (check[pos] == state)
				state = next[pos];
			अन्यथा
				state = def[state];
			अगर (is_loop(wb, state, &adjust)) अणु
				state = aa_dfa_match(dfa, state, str);
				*count -= adjust;
				जाओ out;
			पूर्ण
			inc_wb_pos(wb);
			(*count)++;
		पूर्ण
	पूर्ण

out:
	अगर (!state)
		*count = 0;
	वापस state;
पूर्ण

/**
 * aa_dfa_lefपंचांगatch - traverse @dfa to find state @str stops at
 * @dfa: the dfa to match @str against  (NOT शून्य)
 * @start: the state of the dfa to start matching in
 * @str: the null terminated string of bytes to match against the dfa (NOT शून्य)
 * @count: current count of दीर्घest left.
 *
 * aa_dfa_match will match @str against the dfa and वापस the state it
 * finished matching in. The final state can be used to look up the accepting
 * label, or as the start state of a continuing match.
 *
 * Returns: final state reached after input is consumed
 */
अचिन्हित पूर्णांक aa_dfa_lefपंचांगatch(काष्ठा aa_dfa *dfa, अचिन्हित पूर्णांक start,
			      स्थिर अक्षर *str, अचिन्हित पूर्णांक *count)
अणु
	DEFINE_MATCH_WB(wb);

	/* TODO: match क्रम extended state dfas */

	वापस lefपंचांगatch_fb(dfa, start, str, &wb, count);
पूर्ण
