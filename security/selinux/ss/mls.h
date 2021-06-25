<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Multi-level security (MLS) policy operations.
 *
 * Author : Stephen Smalley, <sds@tycho.nsa.gov>
 */
/*
 * Updated: Trusted Computer Solutions, Inc. <dgoeddel@trustedcs.com>
 *
 *	Support क्रम enhanced MLS infraकाष्ठाure.
 *
 * Copyright (C) 2004-2006 Trusted Computer Solutions, Inc.
 */
/*
 * Updated: Hewlett-Packard <paul@paul-moore.com>
 *
 *	Added support to import/export the MLS label from NetLabel
 *
 * (c) Copyright Hewlett-Packard Development Company, L.P., 2006
 */

#अगर_अघोषित _SS_MLS_H_
#घोषणा _SS_MLS_H_

#समावेश <linux/jhash.h>

#समावेश "context.h"
#समावेश "ebitmap.h"
#समावेश "policydb.h"

पूर्णांक mls_compute_context_len(काष्ठा policydb *p, काष्ठा context *context);
व्योम mls_sid_to_context(काष्ठा policydb *p, काष्ठा context *context,
			अक्षर **scontext);
पूर्णांक mls_context_isvalid(काष्ठा policydb *p, काष्ठा context *c);
पूर्णांक mls_range_isvalid(काष्ठा policydb *p, काष्ठा mls_range *r);
पूर्णांक mls_level_isvalid(काष्ठा policydb *p, काष्ठा mls_level *l);

पूर्णांक mls_context_to_sid(काष्ठा policydb *p,
		       अक्षर oldc,
		       अक्षर *scontext,
		       काष्ठा context *context,
		       काष्ठा sidtab *s,
		       u32 def_sid);

पूर्णांक mls_from_string(काष्ठा policydb *p, अक्षर *str, काष्ठा context *context,
		    gfp_t gfp_mask);

पूर्णांक mls_range_set(काष्ठा context *context, काष्ठा mls_range *range);

पूर्णांक mls_convert_context(काष्ठा policydb *oldp,
			काष्ठा policydb *newp,
			काष्ठा context *oldc,
			काष्ठा context *newc);

पूर्णांक mls_compute_sid(काष्ठा policydb *p,
		    काष्ठा context *scontext,
		    काष्ठा context *tcontext,
		    u16 tclass,
		    u32 specअगरied,
		    काष्ठा context *newcontext,
		    bool sock);

पूर्णांक mls_setup_user_range(काष्ठा policydb *p,
			 काष्ठा context *fromcon, काष्ठा user_datum *user,
			 काष्ठा context *usercon);

#अगर_घोषित CONFIG_NETLABEL
व्योम mls_export_netlbl_lvl(काष्ठा policydb *p,
			   काष्ठा context *context,
			   काष्ठा netlbl_lsm_secattr *secattr);
व्योम mls_import_netlbl_lvl(काष्ठा policydb *p,
			   काष्ठा context *context,
			   काष्ठा netlbl_lsm_secattr *secattr);
पूर्णांक mls_export_netlbl_cat(काष्ठा policydb *p,
			  काष्ठा context *context,
			  काष्ठा netlbl_lsm_secattr *secattr);
पूर्णांक mls_import_netlbl_cat(काष्ठा policydb *p,
			  काष्ठा context *context,
			  काष्ठा netlbl_lsm_secattr *secattr);
#अन्यथा
अटल अंतरभूत व्योम mls_export_netlbl_lvl(काष्ठा policydb *p,
					 काष्ठा context *context,
					 काष्ठा netlbl_lsm_secattr *secattr)
अणु
	वापस;
पूर्ण
अटल अंतरभूत व्योम mls_import_netlbl_lvl(काष्ठा policydb *p,
					 काष्ठा context *context,
					 काष्ठा netlbl_lsm_secattr *secattr)
अणु
	वापस;
पूर्ण
अटल अंतरभूत पूर्णांक mls_export_netlbl_cat(काष्ठा policydb *p,
					काष्ठा context *context,
					काष्ठा netlbl_lsm_secattr *secattr)
अणु
	वापस -ENOMEM;
पूर्ण
अटल अंतरभूत पूर्णांक mls_import_netlbl_cat(काष्ठा policydb *p,
					काष्ठा context *context,
					काष्ठा netlbl_lsm_secattr *secattr)
अणु
	वापस -ENOMEM;
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत u32 mls_range_hash(स्थिर काष्ठा mls_range *r, u32 hash)
अणु
	hash = jhash_2words(r->level[0].sens, r->level[1].sens, hash);
	hash = ebiपंचांगap_hash(&r->level[0].cat, hash);
	hash = ebiपंचांगap_hash(&r->level[1].cat, hash);
	वापस hash;
पूर्ण

#पूर्ण_अगर	/* _SS_MLS_H */

