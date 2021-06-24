<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * AppArmor security module
 *
 * This file contains AppArmor basic permission sets definitions.
 *
 * Copyright 2017 Canonical Ltd.
 */

#अगर_अघोषित __AA_PERM_H
#घोषणा __AA_PERM_H

#समावेश <linux/fs.h>
#समावेश "label.h"

#घोषणा AA_MAY_EXEC		MAY_EXEC
#घोषणा AA_MAY_WRITE		MAY_WRITE
#घोषणा AA_MAY_READ		MAY_READ
#घोषणा AA_MAY_APPEND		MAY_APPEND

#घोषणा AA_MAY_CREATE		0x0010
#घोषणा AA_MAY_DELETE		0x0020
#घोषणा AA_MAY_OPEN		0x0040
#घोषणा AA_MAY_RENAME		0x0080		/* pair */

#घोषणा AA_MAY_SETATTR		0x0100		/* meta ग_लिखो */
#घोषणा AA_MAY_GETATTR		0x0200		/* meta पढ़ो */
#घोषणा AA_MAY_SETCRED		0x0400		/* security cred/attr */
#घोषणा AA_MAY_GETCRED		0x0800

#घोषणा AA_MAY_CHMOD		0x1000		/* pair */
#घोषणा AA_MAY_CHOWN		0x2000		/* pair */
#घोषणा AA_MAY_CHGRP		0x4000		/* pair */
#घोषणा AA_MAY_LOCK		0x8000		/* LINK_SUBSET overlaid */

#घोषणा AA_EXEC_MMAP		0x00010000
#घोषणा AA_MAY_MPROT		0x00020000	/* extend conditions */
#घोषणा AA_MAY_LINK		0x00040000	/* pair */
#घोषणा AA_MAY_SNAPSHOT		0x00080000	/* pair */

#घोषणा AA_MAY_DELEGATE
#घोषणा AA_CONT_MATCH		0x08000000

#घोषणा AA_MAY_STACK		0x10000000
#घोषणा AA_MAY_ONEXEC		0x20000000 /* either stack or change_profile */
#घोषणा AA_MAY_CHANGE_PROखाता	0x40000000
#घोषणा AA_MAY_CHANGEHAT	0x80000000

#घोषणा AA_LINK_SUBSET		AA_MAY_LOCK	/* overlaid */


#घोषणा PERMS_CHRS_MASK (MAY_READ | MAY_WRITE | AA_MAY_CREATE |		\
			 AA_MAY_DELETE | AA_MAY_LINK | AA_MAY_LOCK |	\
			 AA_MAY_EXEC | AA_EXEC_MMAP | AA_MAY_APPEND)

#घोषणा PERMS_NAMES_MASK (PERMS_CHRS_MASK | AA_MAY_OPEN | AA_MAY_RENAME |     \
			  AA_MAY_SETATTR | AA_MAY_GETATTR | AA_MAY_SETCRED | \
			  AA_MAY_GETCRED | AA_MAY_CHMOD | AA_MAY_CHOWN | \
			  AA_MAY_CHGRP | AA_MAY_MPROT | AA_MAY_SNAPSHOT | \
			  AA_MAY_STACK | AA_MAY_ONEXEC |		\
			  AA_MAY_CHANGE_PROखाता | AA_MAY_CHANGEHAT)

बाह्य स्थिर अक्षर aa_file_perm_chrs[];
बाह्य स्थिर अक्षर *aa_file_perm_names[];

काष्ठा aa_perms अणु
	u32 allow;
	u32 audit;	/* set only when allow is set */

	u32 deny;	/* explicit deny, or conflict अगर allow also set */
	u32 quiet;	/* set only when ~allow | deny */
	u32 समाप्त;	/* set only when ~allow | deny */
	u32 stop;	/* set only when ~allow | deny */

	u32 complain;	/* accumulates only used when ~allow & ~deny */
	u32 cond;	/* set only when ~allow and ~deny */

	u32 hide;	/* set only when  ~allow | deny */
	u32 prompt;	/* accumulates only used when ~allow & ~deny */

	/* Reserved:
	 * u32 subtree;	/ * set only when allow is set * /
	 */
	u16 xindex;
पूर्ण;

#घोषणा ALL_PERMS_MASK 0xffffffff
बाह्य काष्ठा aa_perms nullperms;
बाह्य काष्ठा aa_perms allperms;


#घोषणा xcheck(FN1, FN2)	\
(अणु				\
	पूर्णांक e, error = FN1;	\
	e = FN2;		\
	अगर (e)			\
		error = e;	\
	error;			\
पूर्ण)


/*
 * TODO: update क्रम labels poपूर्णांकing to labels instead of profiles
 * TODO: optimize the walk, currently करोes subwalk of L2 क्रम each P in L1
 * gah this करोesn't allow क्रम label compound check!!!!
 */
#घोषणा xcheck_ns_profile_profile(P1, P2, FN, args...)		\
(अणु								\
	पूर्णांक ____e = 0;						\
	अगर (P1->ns == P2->ns)					\
		____e = FN((P1), (P2), args);			\
	(____e);						\
पूर्ण)

#घोषणा xcheck_ns_profile_label(P, L, FN, args...)		\
(अणु								\
	काष्ठा aa_profile *__p2;				\
	fn_क्रम_each((L), __p2,					\
		    xcheck_ns_profile_profile((P), __p2, (FN), args));	\
पूर्ण)

#घोषणा xcheck_ns_labels(L1, L2, FN, args...)			\
(अणु								\
	काष्ठा aa_profile *__p1;				\
	fn_क्रम_each((L1), __p1, FN(__p1, (L2), args));		\
पूर्ण)

/* Do the cross check but applying FN at the profiles level */
#घोषणा xcheck_labels_profiles(L1, L2, FN, args...)		\
	xcheck_ns_labels((L1), (L2), xcheck_ns_profile_label, (FN), args)

#घोषणा xcheck_labels(L1, L2, P, FN1, FN2)			\
	xcheck(fn_क्रम_each((L1), (P), (FN1)), fn_क्रम_each((L2), (P), (FN2)))


व्योम aa_perm_mask_to_str(अक्षर *str, माप_प्रकार str_size, स्थिर अक्षर *chrs,
			 u32 mask);
व्योम aa_audit_perm_names(काष्ठा audit_buffer *ab, स्थिर अक्षर * स्थिर *names,
			 u32 mask);
व्योम aa_audit_perm_mask(काष्ठा audit_buffer *ab, u32 mask, स्थिर अक्षर *chrs,
			u32 chrsmask, स्थिर अक्षर * स्थिर *names, u32 namesmask);
व्योम aa_apply_modes_to_perms(काष्ठा aa_profile *profile,
			     काष्ठा aa_perms *perms);
व्योम aa_compute_perms(काष्ठा aa_dfa *dfa, अचिन्हित पूर्णांक state,
		      काष्ठा aa_perms *perms);
व्योम aa_perms_accum(काष्ठा aa_perms *accum, काष्ठा aa_perms *addend);
व्योम aa_perms_accum_raw(काष्ठा aa_perms *accum, काष्ठा aa_perms *addend);
व्योम aa_profile_match_label(काष्ठा aa_profile *profile, काष्ठा aa_label *label,
			    पूर्णांक type, u32 request, काष्ठा aa_perms *perms);
पूर्णांक aa_profile_label_perm(काष्ठा aa_profile *profile, काष्ठा aa_profile *target,
			  u32 request, पूर्णांक type, u32 *deny,
			  काष्ठा common_audit_data *sa);
पूर्णांक aa_check_perms(काष्ठा aa_profile *profile, काष्ठा aa_perms *perms,
		   u32 request, काष्ठा common_audit_data *sa,
		   व्योम (*cb)(काष्ठा audit_buffer *, व्योम *));
#पूर्ण_अगर /* __AA_PERM_H */
