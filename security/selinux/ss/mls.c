<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Implementation of the multi-level security (MLS) policy.
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
 *      Added support to import/export the MLS label from NetLabel
 *
 * (c) Copyright Hewlett-Packard Development Company, L.P., 2006
 */

#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <net/netlabel.h>
#समावेश "sidtab.h"
#समावेश "mls.h"
#समावेश "policydb.h"
#समावेश "services.h"

/*
 * Return the length in bytes क्रम the MLS fields of the
 * security context string representation of `context'.
 */
पूर्णांक mls_compute_context_len(काष्ठा policydb *p, काष्ठा context *context)
अणु
	पूर्णांक i, l, len, head, prev;
	अक्षर *nm;
	काष्ठा ebiपंचांगap *e;
	काष्ठा ebiपंचांगap_node *node;

	अगर (!p->mls_enabled)
		वापस 0;

	len = 1; /* क्रम the beginning ":" */
	क्रम (l = 0; l < 2; l++) अणु
		पूर्णांक index_sens = context->range.level[l].sens;
		len += म_माप(sym_name(p, SYM_LEVELS, index_sens - 1));

		/* categories */
		head = -2;
		prev = -2;
		e = &context->range.level[l].cat;
		ebiपंचांगap_क्रम_each_positive_bit(e, node, i) अणु
			अगर (i - prev > 1) अणु
				/* one or more negative bits are skipped */
				अगर (head != prev) अणु
					nm = sym_name(p, SYM_CATS, prev);
					len += म_माप(nm) + 1;
				पूर्ण
				nm = sym_name(p, SYM_CATS, i);
				len += म_माप(nm) + 1;
				head = i;
			पूर्ण
			prev = i;
		पूर्ण
		अगर (prev != head) अणु
			nm = sym_name(p, SYM_CATS, prev);
			len += म_माप(nm) + 1;
		पूर्ण
		अगर (l == 0) अणु
			अगर (mls_level_eq(&context->range.level[0],
					 &context->range.level[1]))
				अवरोध;
			अन्यथा
				len++;
		पूर्ण
	पूर्ण

	वापस len;
पूर्ण

/*
 * Write the security context string representation of
 * the MLS fields of `context' into the string `*scontext'.
 * Update `*scontext' to poपूर्णांक to the end of the MLS fields.
 */
व्योम mls_sid_to_context(काष्ठा policydb *p,
			काष्ठा context *context,
			अक्षर **scontext)
अणु
	अक्षर *scontextp, *nm;
	पूर्णांक i, l, head, prev;
	काष्ठा ebiपंचांगap *e;
	काष्ठा ebiपंचांगap_node *node;

	अगर (!p->mls_enabled)
		वापस;

	scontextp = *scontext;

	*scontextp = ':';
	scontextp++;

	क्रम (l = 0; l < 2; l++) अणु
		म_नकल(scontextp, sym_name(p, SYM_LEVELS,
					   context->range.level[l].sens - 1));
		scontextp += म_माप(scontextp);

		/* categories */
		head = -2;
		prev = -2;
		e = &context->range.level[l].cat;
		ebiपंचांगap_क्रम_each_positive_bit(e, node, i) अणु
			अगर (i - prev > 1) अणु
				/* one or more negative bits are skipped */
				अगर (prev != head) अणु
					अगर (prev - head > 1)
						*scontextp++ = '.';
					अन्यथा
						*scontextp++ = ',';
					nm = sym_name(p, SYM_CATS, prev);
					म_नकल(scontextp, nm);
					scontextp += म_माप(nm);
				पूर्ण
				अगर (prev < 0)
					*scontextp++ = ':';
				अन्यथा
					*scontextp++ = ',';
				nm = sym_name(p, SYM_CATS, i);
				म_नकल(scontextp, nm);
				scontextp += म_माप(nm);
				head = i;
			पूर्ण
			prev = i;
		पूर्ण

		अगर (prev != head) अणु
			अगर (prev - head > 1)
				*scontextp++ = '.';
			अन्यथा
				*scontextp++ = ',';
			nm = sym_name(p, SYM_CATS, prev);
			म_नकल(scontextp, nm);
			scontextp += म_माप(nm);
		पूर्ण

		अगर (l == 0) अणु
			अगर (mls_level_eq(&context->range.level[0],
					 &context->range.level[1]))
				अवरोध;
			अन्यथा
				*scontextp++ = '-';
		पूर्ण
	पूर्ण

	*scontext = scontextp;
	वापस;
पूर्ण

पूर्णांक mls_level_isvalid(काष्ठा policydb *p, काष्ठा mls_level *l)
अणु
	काष्ठा level_datum *levdatum;

	अगर (!l->sens || l->sens > p->p_levels.nprim)
		वापस 0;
	levdatum = symtab_search(&p->p_levels,
				 sym_name(p, SYM_LEVELS, l->sens - 1));
	अगर (!levdatum)
		वापस 0;

	/*
	 * Return 1 अगरf all the bits set in l->cat are also be set in
	 * levdatum->level->cat and no bit in l->cat is larger than
	 * p->p_cats.nprim.
	 */
	वापस ebiपंचांगap_contains(&levdatum->level->cat, &l->cat,
				p->p_cats.nprim);
पूर्ण

पूर्णांक mls_range_isvalid(काष्ठा policydb *p, काष्ठा mls_range *r)
अणु
	वापस (mls_level_isvalid(p, &r->level[0]) &&
		mls_level_isvalid(p, &r->level[1]) &&
		mls_level_करोm(&r->level[1], &r->level[0]));
पूर्ण

/*
 * Return 1 अगर the MLS fields in the security context
 * काष्ठाure `c' are valid.  Return 0 otherwise.
 */
पूर्णांक mls_context_isvalid(काष्ठा policydb *p, काष्ठा context *c)
अणु
	काष्ठा user_datum *usrdatum;

	अगर (!p->mls_enabled)
		वापस 1;

	अगर (!mls_range_isvalid(p, &c->range))
		वापस 0;

	अगर (c->role == OBJECT_R_VAL)
		वापस 1;

	/*
	 * User must be authorized क्रम the MLS range.
	 */
	अगर (!c->user || c->user > p->p_users.nprim)
		वापस 0;
	usrdatum = p->user_val_to_काष्ठा[c->user - 1];
	अगर (!mls_range_contains(usrdatum->range, c->range))
		वापस 0; /* user may not be associated with range */

	वापस 1;
पूर्ण

/*
 * Set the MLS fields in the security context काष्ठाure
 * `context' based on the string representation in
 * the string `scontext'.
 *
 * This function modअगरies the string in place, inserting
 * शून्य अक्षरacters to terminate the MLS fields.
 *
 * If a def_sid is provided and no MLS field is present,
 * copy the MLS field of the associated शेष context.
 * Used क्रम upgraded to MLS प्रणालीs where objects may lack
 * MLS fields.
 *
 * Policy पढ़ो-lock must be held क्रम sidtab lookup.
 *
 */
पूर्णांक mls_context_to_sid(काष्ठा policydb *pol,
		       अक्षर oldc,
		       अक्षर *scontext,
		       काष्ठा context *context,
		       काष्ठा sidtab *s,
		       u32 def_sid)
अणु
	अक्षर *sensitivity, *cur_cat, *next_cat, *rngptr;
	काष्ठा level_datum *levdatum;
	काष्ठा cat_datum *catdatum, *rngdatum;
	पूर्णांक l, rc, i;
	अक्षर *rangep[2];

	अगर (!pol->mls_enabled) अणु
		/*
		 * With no MLS, only वापस -EINVAL अगर there is a MLS field
		 * and it did not come from an xattr.
		 */
		अगर (oldc && def_sid == SECSID_शून्य)
			वापस -EINVAL;
		वापस 0;
	पूर्ण

	/*
	 * No MLS component to the security context, try and map to
	 * शेष अगर provided.
	 */
	अगर (!oldc) अणु
		काष्ठा context *defcon;

		अगर (def_sid == SECSID_शून्य)
			वापस -EINVAL;

		defcon = sidtab_search(s, def_sid);
		अगर (!defcon)
			वापस -EINVAL;

		वापस mls_context_cpy(context, defcon);
	पूर्ण

	/*
	 * If we're dealing with a range, figure out where the two parts
	 * of the range begin.
	 */
	rangep[0] = scontext;
	rangep[1] = म_अक्षर(scontext, '-');
	अगर (rangep[1]) अणु
		rangep[1][0] = '\0';
		rangep[1]++;
	पूर्ण

	/* For each part of the range: */
	क्रम (l = 0; l < 2; l++) अणु
		/* Split sensitivity and category set. */
		sensitivity = rangep[l];
		अगर (sensitivity == शून्य)
			अवरोध;
		next_cat = म_अक्षर(sensitivity, ':');
		अगर (next_cat)
			*(next_cat++) = '\0';

		/* Parse sensitivity. */
		levdatum = symtab_search(&pol->p_levels, sensitivity);
		अगर (!levdatum)
			वापस -EINVAL;
		context->range.level[l].sens = levdatum->level->sens;

		/* Extract category set. */
		जबतक (next_cat != शून्य) अणु
			cur_cat = next_cat;
			next_cat = म_अक्षर(next_cat, ',');
			अगर (next_cat != शून्य)
				*(next_cat++) = '\0';

			/* Separate पूर्णांकo range अगर exists */
			rngptr = म_अक्षर(cur_cat, '.');
			अगर (rngptr != शून्य) अणु
				/* Remove '.' */
				*rngptr++ = '\0';
			पूर्ण

			catdatum = symtab_search(&pol->p_cats, cur_cat);
			अगर (!catdatum)
				वापस -EINVAL;

			rc = ebiपंचांगap_set_bit(&context->range.level[l].cat,
					     catdatum->value - 1, 1);
			अगर (rc)
				वापस rc;

			/* If range, set all categories in range */
			अगर (rngptr == शून्य)
				जारी;

			rngdatum = symtab_search(&pol->p_cats, rngptr);
			अगर (!rngdatum)
				वापस -EINVAL;

			अगर (catdatum->value >= rngdatum->value)
				वापस -EINVAL;

			क्रम (i = catdatum->value; i < rngdatum->value; i++) अणु
				rc = ebiपंचांगap_set_bit(&context->range.level[l].cat, i, 1);
				अगर (rc)
					वापस rc;
			पूर्ण
		पूर्ण
	पूर्ण

	/* If we didn't see a '-', the range start is also the range end. */
	अगर (rangep[1] == शून्य) अणु
		context->range.level[1].sens = context->range.level[0].sens;
		rc = ebiपंचांगap_cpy(&context->range.level[1].cat,
				 &context->range.level[0].cat);
		अगर (rc)
			वापस rc;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Set the MLS fields in the security context काष्ठाure
 * `context' based on the string representation in
 * the string `str'.  This function will allocate temporary memory with the
 * given स्थिरraपूर्णांकs of gfp_mask.
 */
पूर्णांक mls_from_string(काष्ठा policydb *p, अक्षर *str, काष्ठा context *context,
		    gfp_t gfp_mask)
अणु
	अक्षर *पंचांगpstr;
	पूर्णांक rc;

	अगर (!p->mls_enabled)
		वापस -EINVAL;

	पंचांगpstr = kstrdup(str, gfp_mask);
	अगर (!पंचांगpstr) अणु
		rc = -ENOMEM;
	पूर्ण अन्यथा अणु
		rc = mls_context_to_sid(p, ':', पंचांगpstr, context,
					शून्य, SECSID_शून्य);
		kमुक्त(पंचांगpstr);
	पूर्ण

	वापस rc;
पूर्ण

/*
 * Copies the MLS range `range' into `context'.
 */
पूर्णांक mls_range_set(काष्ठा context *context,
				काष्ठा mls_range *range)
अणु
	पूर्णांक l, rc = 0;

	/* Copy the MLS range पूर्णांकo the  context */
	क्रम (l = 0; l < 2; l++) अणु
		context->range.level[l].sens = range->level[l].sens;
		rc = ebiपंचांगap_cpy(&context->range.level[l].cat,
				 &range->level[l].cat);
		अगर (rc)
			अवरोध;
	पूर्ण

	वापस rc;
पूर्ण

पूर्णांक mls_setup_user_range(काष्ठा policydb *p,
			 काष्ठा context *fromcon, काष्ठा user_datum *user,
			 काष्ठा context *usercon)
अणु
	अगर (p->mls_enabled) अणु
		काष्ठा mls_level *fromcon_sen = &(fromcon->range.level[0]);
		काष्ठा mls_level *fromcon_clr = &(fromcon->range.level[1]);
		काष्ठा mls_level *user_low = &(user->range.level[0]);
		काष्ठा mls_level *user_clr = &(user->range.level[1]);
		काष्ठा mls_level *user_def = &(user->dfltlevel);
		काष्ठा mls_level *usercon_sen = &(usercon->range.level[0]);
		काष्ठा mls_level *usercon_clr = &(usercon->range.level[1]);

		/* Honor the user's शेष level अगर we can */
		अगर (mls_level_between(user_def, fromcon_sen, fromcon_clr))
			*usercon_sen = *user_def;
		अन्यथा अगर (mls_level_between(fromcon_sen, user_def, user_clr))
			*usercon_sen = *fromcon_sen;
		अन्यथा अगर (mls_level_between(fromcon_clr, user_low, user_def))
			*usercon_sen = *user_low;
		अन्यथा
			वापस -EINVAL;

		/* Lower the clearance of available contexts
		   अगर the clearance of "fromcon" is lower than
		   that of the user's शेष clearance (but
		   only अगर the "fromcon" clearance करोminates
		   the user's computed sensitivity level) */
		अगर (mls_level_करोm(user_clr, fromcon_clr))
			*usercon_clr = *fromcon_clr;
		अन्यथा अगर (mls_level_करोm(fromcon_clr, user_clr))
			*usercon_clr = *user_clr;
		अन्यथा
			वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Convert the MLS fields in the security context
 * काष्ठाure `oldc' from the values specअगरied in the
 * policy `oldp' to the values specified in the policy `newp',
 * storing the resulting context in `newc'.
 */
पूर्णांक mls_convert_context(काष्ठा policydb *oldp,
			काष्ठा policydb *newp,
			काष्ठा context *oldc,
			काष्ठा context *newc)
अणु
	काष्ठा level_datum *levdatum;
	काष्ठा cat_datum *catdatum;
	काष्ठा ebiपंचांगap_node *node;
	पूर्णांक l, i;

	अगर (!oldp->mls_enabled || !newp->mls_enabled)
		वापस 0;

	क्रम (l = 0; l < 2; l++) अणु
		अक्षर *name = sym_name(oldp, SYM_LEVELS,
				      oldc->range.level[l].sens - 1);

		levdatum = symtab_search(&newp->p_levels, name);

		अगर (!levdatum)
			वापस -EINVAL;
		newc->range.level[l].sens = levdatum->level->sens;

		ebiपंचांगap_क्रम_each_positive_bit(&oldc->range.level[l].cat,
					      node, i) अणु
			पूर्णांक rc;

			catdatum = symtab_search(&newp->p_cats,
						 sym_name(oldp, SYM_CATS, i));
			अगर (!catdatum)
				वापस -EINVAL;
			rc = ebiपंचांगap_set_bit(&newc->range.level[l].cat,
					     catdatum->value - 1, 1);
			अगर (rc)
				वापस rc;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक mls_compute_sid(काष्ठा policydb *p,
		    काष्ठा context *scontext,
		    काष्ठा context *tcontext,
		    u16 tclass,
		    u32 specअगरied,
		    काष्ठा context *newcontext,
		    bool sock)
अणु
	काष्ठा range_trans rtr;
	काष्ठा mls_range *r;
	काष्ठा class_datum *cladatum;
	पूर्णांक शेष_range = 0;

	अगर (!p->mls_enabled)
		वापस 0;

	चयन (specअगरied) अणु
	हाल AVTAB_TRANSITION:
		/* Look क्रम a range transition rule. */
		rtr.source_type = scontext->type;
		rtr.target_type = tcontext->type;
		rtr.target_class = tclass;
		r = policydb_rangetr_search(p, &rtr);
		अगर (r)
			वापस mls_range_set(newcontext, r);

		अगर (tclass && tclass <= p->p_classes.nprim) अणु
			cladatum = p->class_val_to_काष्ठा[tclass - 1];
			अगर (cladatum)
				शेष_range = cladatum->शेष_range;
		पूर्ण

		चयन (शेष_range) अणु
		हाल DEFAULT_SOURCE_LOW:
			वापस mls_context_cpy_low(newcontext, scontext);
		हाल DEFAULT_SOURCE_HIGH:
			वापस mls_context_cpy_high(newcontext, scontext);
		हाल DEFAULT_SOURCE_LOW_HIGH:
			वापस mls_context_cpy(newcontext, scontext);
		हाल DEFAULT_TARGET_LOW:
			वापस mls_context_cpy_low(newcontext, tcontext);
		हाल DEFAULT_TARGET_HIGH:
			वापस mls_context_cpy_high(newcontext, tcontext);
		हाल DEFAULT_TARGET_LOW_HIGH:
			वापस mls_context_cpy(newcontext, tcontext);
		हाल DEFAULT_GLBLUB:
			वापस mls_context_glblub(newcontext,
						  scontext, tcontext);
		पूर्ण

		fallthrough;
	हाल AVTAB_CHANGE:
		अगर ((tclass == p->process_class) || sock)
			/* Use the process MLS attributes. */
			वापस mls_context_cpy(newcontext, scontext);
		अन्यथा
			/* Use the process effective MLS attributes. */
			वापस mls_context_cpy_low(newcontext, scontext);
	हाल AVTAB_MEMBER:
		/* Use the process effective MLS attributes. */
		वापस mls_context_cpy_low(newcontext, scontext);
	पूर्ण
	वापस -EINVAL;
पूर्ण

#अगर_घोषित CONFIG_NETLABEL
/**
 * mls_export_netlbl_lvl - Export the MLS sensitivity levels to NetLabel
 * @context: the security context
 * @secattr: the NetLabel security attributes
 *
 * Description:
 * Given the security context copy the low MLS sensitivity level पूर्णांकo the
 * NetLabel MLS sensitivity level field.
 *
 */
व्योम mls_export_netlbl_lvl(काष्ठा policydb *p,
			   काष्ठा context *context,
			   काष्ठा netlbl_lsm_secattr *secattr)
अणु
	अगर (!p->mls_enabled)
		वापस;

	secattr->attr.mls.lvl = context->range.level[0].sens - 1;
	secattr->flags |= NETLBL_SECATTR_MLS_LVL;
पूर्ण

/**
 * mls_import_netlbl_lvl - Import the NetLabel MLS sensitivity levels
 * @context: the security context
 * @secattr: the NetLabel security attributes
 *
 * Description:
 * Given the security context and the NetLabel security attributes, copy the
 * NetLabel MLS sensitivity level पूर्णांकo the context.
 *
 */
व्योम mls_import_netlbl_lvl(काष्ठा policydb *p,
			   काष्ठा context *context,
			   काष्ठा netlbl_lsm_secattr *secattr)
अणु
	अगर (!p->mls_enabled)
		वापस;

	context->range.level[0].sens = secattr->attr.mls.lvl + 1;
	context->range.level[1].sens = context->range.level[0].sens;
पूर्ण

/**
 * mls_export_netlbl_cat - Export the MLS categories to NetLabel
 * @context: the security context
 * @secattr: the NetLabel security attributes
 *
 * Description:
 * Given the security context copy the low MLS categories पूर्णांकo the NetLabel
 * MLS category field.  Returns zero on success, negative values on failure.
 *
 */
पूर्णांक mls_export_netlbl_cat(काष्ठा policydb *p,
			  काष्ठा context *context,
			  काष्ठा netlbl_lsm_secattr *secattr)
अणु
	पूर्णांक rc;

	अगर (!p->mls_enabled)
		वापस 0;

	rc = ebiपंचांगap_netlbl_export(&context->range.level[0].cat,
				   &secattr->attr.mls.cat);
	अगर (rc == 0 && secattr->attr.mls.cat != शून्य)
		secattr->flags |= NETLBL_SECATTR_MLS_CAT;

	वापस rc;
पूर्ण

/**
 * mls_import_netlbl_cat - Import the MLS categories from NetLabel
 * @context: the security context
 * @secattr: the NetLabel security attributes
 *
 * Description:
 * Copy the NetLabel security attributes पूर्णांकo the SELinux context; since the
 * NetLabel security attribute only contains a single MLS category use it क्रम
 * both the low and high categories of the context.  Returns zero on success,
 * negative values on failure.
 *
 */
पूर्णांक mls_import_netlbl_cat(काष्ठा policydb *p,
			  काष्ठा context *context,
			  काष्ठा netlbl_lsm_secattr *secattr)
अणु
	पूर्णांक rc;

	अगर (!p->mls_enabled)
		वापस 0;

	rc = ebiपंचांगap_netlbl_import(&context->range.level[0].cat,
				   secattr->attr.mls.cat);
	अगर (rc)
		जाओ import_netlbl_cat_failure;
	स_नकल(&context->range.level[1].cat, &context->range.level[0].cat,
	       माप(context->range.level[0].cat));

	वापस 0;

import_netlbl_cat_failure:
	ebiपंचांगap_destroy(&context->range.level[0].cat);
	वापस rc;
पूर्ण
#पूर्ण_अगर /* CONFIG_NETLABEL */
