<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * AppArmor security module
 *
 * This file contains AppArmor policy dfa matching engine definitions.
 *
 * Copyright (C) 1998-2008 Novell/SUSE
 * Copyright 2009-2012 Canonical Ltd.
 */

#अगर_अघोषित __AA_MATCH_H
#घोषणा __AA_MATCH_H

#समावेश <linux/kref.h>

#घोषणा DFA_NOMATCH			0
#घोषणा DFA_START			1


/**
 * The क्रमmat used क्रम transition tables is based on the GNU flex table
 * file क्रमmat (--tables-file option; see Table File Format in the flex
 * info pages and the flex sources क्रम करोcumentation). The magic number
 * used in the header is 0x1B5E783D instead of 0xF13C57B1 though, because
 * new tables have been defined and others YY_ID_CHK (check) and YY_ID_DEF
 * (शेष) tables are used slightly dअगरferently (see the apparmor-parser
 * package).
 *
 *
 * The data in the packed dfa is stored in network byte order, and the tables
 * are arranged क्रम flexibility.  We convert the table data to host native
 * byte order.
 *
 * The dfa begins with a table set header, and is followed by the actual
 * tables.
 */

#घोषणा YYTH_MAGIC	0x1B5E783D
#घोषणा YYTH_FLAG_DIFF_ENCODE	1
#घोषणा YYTH_FLAG_OOB_TRANS	2
#घोषणा YYTH_FLAGS (YYTH_FLAG_DIFF_ENCODE | YYTH_FLAG_OOB_TRANS)

#घोषणा MAX_OOB_SUPPORTED	1

काष्ठा table_set_header अणु
	u32 th_magic;		/* YYTH_MAGIC */
	u32 th_hsize;
	u32 th_ssize;
	u16 th_flags;
	अक्षर th_version[];
पूर्ण;

/* The YYTD_ID are one less than flex table mappings.  The flex id
 * has 1 subtracted at table load समय, this allows us to directly use the
 * ID's as indexes.
 */
#घोषणा	YYTD_ID_ACCEPT	0
#घोषणा YYTD_ID_BASE	1
#घोषणा YYTD_ID_CHK	2
#घोषणा YYTD_ID_DEF	3
#घोषणा YYTD_ID_EC	4
#घोषणा YYTD_ID_META	5
#घोषणा YYTD_ID_ACCEPT2 6
#घोषणा YYTD_ID_NXT	7
#घोषणा YYTD_ID_TSIZE	8
#घोषणा YYTD_ID_MAX	8

#घोषणा YYTD_DATA8	1
#घोषणा YYTD_DATA16	2
#घोषणा YYTD_DATA32	4
#घोषणा YYTD_DATA64	8

/* ACCEPT & ACCEPT2 tables माला_लो 6 dedicated flags, YYTD_DATAX define the
 * first flags
 */
#घोषणा ACCEPT1_FLAGS(X) ((X) & 0x3f)
#घोषणा ACCEPT2_FLAGS(X) ACCEPT1_FLAGS((X) >> YYTD_ID_ACCEPT2)
#घोषणा TO_ACCEPT1_FLAG(X) ACCEPT1_FLAGS(X)
#घोषणा TO_ACCEPT2_FLAG(X) (ACCEPT1_FLAGS(X) << YYTD_ID_ACCEPT2)
#घोषणा DFA_FLAG_VERIFY_STATES 0x1000

काष्ठा table_header अणु
	u16 td_id;
	u16 td_flags;
	u32 td_hilen;
	u32 td_lolen;
	अक्षर td_data[];
पूर्ण;

#घोषणा DEFAULT_TABLE(DFA) ((u16 *)((DFA)->tables[YYTD_ID_DEF]->td_data))
#घोषणा BASE_TABLE(DFA) ((u32 *)((DFA)->tables[YYTD_ID_BASE]->td_data))
#घोषणा NEXT_TABLE(DFA) ((u16 *)((DFA)->tables[YYTD_ID_NXT]->td_data))
#घोषणा CHECK_TABLE(DFA) ((u16 *)((DFA)->tables[YYTD_ID_CHK]->td_data))
#घोषणा EQUIV_TABLE(DFA) ((u8 *)((DFA)->tables[YYTD_ID_EC]->td_data))
#घोषणा ACCEPT_TABLE(DFA) ((u32 *)((DFA)->tables[YYTD_ID_ACCEPT]->td_data))
#घोषणा ACCEPT_TABLE2(DFA) ((u32 *)((DFA)->tables[YYTD_ID_ACCEPT2]->td_data))

काष्ठा aa_dfa अणु
	काष्ठा kref count;
	u16 flags;
	u32 max_oob;
	काष्ठा table_header *tables[YYTD_ID_TSIZE];
पूर्ण;

बाह्य काष्ठा aa_dfa *nulldfa;
बाह्य काष्ठा aa_dfa *stacksplitdfa;

#घोषणा byte_to_byte(X) (X)

#घोषणा UNPACK_ARRAY(TABLE, BLOB, LEN, TTYPE, BTYPE, NTOHX)	\
	करो अणु \
		typeof(LEN) __i; \
		TTYPE *__t = (TTYPE *) TABLE; \
		BTYPE *__b = (BTYPE *) BLOB; \
		क्रम (__i = 0; __i < LEN; __i++) अणु \
			__t[__i] = NTOHX(__b[__i]); \
		पूर्ण \
	पूर्ण जबतक (0)

अटल अंतरभूत माप_प्रकार table_size(माप_प्रकार len, माप_प्रकार el_size)
अणु
	वापस ALIGN(माप(काष्ठा table_header) + len * el_size, 8);
पूर्ण

पूर्णांक aa_setup_dfa_engine(व्योम);
व्योम aa_tearकरोwn_dfa_engine(व्योम);

काष्ठा aa_dfa *aa_dfa_unpack(व्योम *blob, माप_प्रकार size, पूर्णांक flags);
अचिन्हित पूर्णांक aa_dfa_match_len(काष्ठा aa_dfa *dfa, अचिन्हित पूर्णांक start,
			      स्थिर अक्षर *str, पूर्णांक len);
अचिन्हित पूर्णांक aa_dfa_match(काष्ठा aa_dfa *dfa, अचिन्हित पूर्णांक start,
			  स्थिर अक्षर *str);
अचिन्हित पूर्णांक aa_dfa_next(काष्ठा aa_dfa *dfa, अचिन्हित पूर्णांक state,
			 स्थिर अक्षर c);
अचिन्हित पूर्णांक aa_dfa_outofband_transition(काष्ठा aa_dfa *dfa,
					 अचिन्हित पूर्णांक state);
अचिन्हित पूर्णांक aa_dfa_match_until(काष्ठा aa_dfa *dfa, अचिन्हित पूर्णांक start,
				स्थिर अक्षर *str, स्थिर अक्षर **retpos);
अचिन्हित पूर्णांक aa_dfa_matchn_until(काष्ठा aa_dfa *dfa, अचिन्हित पूर्णांक start,
				 स्थिर अक्षर *str, पूर्णांक n, स्थिर अक्षर **retpos);

व्योम aa_dfa_मुक्त_kref(काष्ठा kref *kref);

#घोषणा WB_HISTORY_SIZE 24
काष्ठा match_workbuf अणु
	अचिन्हित पूर्णांक count;
	अचिन्हित पूर्णांक pos;
	अचिन्हित पूर्णांक len;
	अचिन्हित पूर्णांक size;	/* घातer of 2, same as history size */
	अचिन्हित पूर्णांक history[WB_HISTORY_SIZE];
पूर्ण;
#घोषणा DEFINE_MATCH_WB(N)		\
काष्ठा match_workbuf N = अणु		\
	.count = 0,			\
	.pos = 0,			\
	.len = 0,			\
पूर्ण

अचिन्हित पूर्णांक aa_dfa_lefपंचांगatch(काष्ठा aa_dfa *dfa, अचिन्हित पूर्णांक start,
			      स्थिर अक्षर *str, अचिन्हित पूर्णांक *count);

/**
 * aa_get_dfa - increment refcount on dfa @p
 * @dfa: dfa  (MAYBE शून्य)
 *
 * Returns: poपूर्णांकer to @dfa अगर @dfa is शून्य will वापस शून्य
 * Requires: @dfa must be held with valid refcount when called
 */
अटल अंतरभूत काष्ठा aa_dfa *aa_get_dfa(काष्ठा aa_dfa *dfa)
अणु
	अगर (dfa)
		kref_get(&(dfa->count));

	वापस dfa;
पूर्ण

/**
 * aa_put_dfa - put a dfa refcount
 * @dfa: dfa to put refcount   (MAYBE शून्य)
 *
 * Requires: अगर @dfa != शून्य that a valid refcount be held
 */
अटल अंतरभूत व्योम aa_put_dfa(काष्ठा aa_dfa *dfa)
अणु
	अगर (dfa)
		kref_put(&dfa->count, aa_dfa_मुक्त_kref);
पूर्ण

#घोषणा MATCH_FLAG_DIFF_ENCODE 0x80000000
#घोषणा MARK_DIFF_ENCODE 0x40000000
#घोषणा MATCH_FLAG_OOB_TRANSITION 0x20000000
#घोषणा MATCH_FLAGS_MASK 0xff000000
#घोषणा MATCH_FLAGS_VALID (MATCH_FLAG_DIFF_ENCODE | MATCH_FLAG_OOB_TRANSITION)
#घोषणा MATCH_FLAGS_INVALID (MATCH_FLAGS_MASK & ~MATCH_FLAGS_VALID)

#पूर्ण_अगर /* __AA_MATCH_H */
