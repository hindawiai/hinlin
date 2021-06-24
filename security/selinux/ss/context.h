<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * A security context is a set of security attributes
 * associated with each subject and object controlled
 * by the security policy.  Security contexts are
  * बाह्यally represented as variable-length strings
 * that can be पूर्णांकerpreted by a user or application
 * with an understanding of the security policy.
 * Internally, the security server uses a simple
 * काष्ठाure.  This काष्ठाure is निजी to the
 * security server and can be changed without affecting
 * clients of the security server.
 *
 * Author : Stephen Smalley, <sds@tycho.nsa.gov>
 */
#अगर_अघोषित _SS_CONTEXT_H_
#घोषणा _SS_CONTEXT_H_

#समावेश "ebitmap.h"
#समावेश "mls_types.h"
#समावेश "security.h"

/*
 * A security context consists of an authenticated user
 * identity, a role, a type and a MLS range.
 */
काष्ठा context अणु
	u32 user;
	u32 role;
	u32 type;
	u32 len;        /* length of string in bytes */
	काष्ठा mls_range range;
	अक्षर *str;	/* string representation अगर context cannot be mapped. */
पूर्ण;

अटल अंतरभूत व्योम mls_context_init(काष्ठा context *c)
अणु
	स_रखो(&c->range, 0, माप(c->range));
पूर्ण

अटल अंतरभूत पूर्णांक mls_context_cpy(काष्ठा context *dst, काष्ठा context *src)
अणु
	पूर्णांक rc;

	dst->range.level[0].sens = src->range.level[0].sens;
	rc = ebiपंचांगap_cpy(&dst->range.level[0].cat, &src->range.level[0].cat);
	अगर (rc)
		जाओ out;

	dst->range.level[1].sens = src->range.level[1].sens;
	rc = ebiपंचांगap_cpy(&dst->range.level[1].cat, &src->range.level[1].cat);
	अगर (rc)
		ebiपंचांगap_destroy(&dst->range.level[0].cat);
out:
	वापस rc;
पूर्ण

/*
 * Sets both levels in the MLS range of 'dst' to the low level of 'src'.
 */
अटल अंतरभूत पूर्णांक mls_context_cpy_low(काष्ठा context *dst, काष्ठा context *src)
अणु
	पूर्णांक rc;

	dst->range.level[0].sens = src->range.level[0].sens;
	rc = ebiपंचांगap_cpy(&dst->range.level[0].cat, &src->range.level[0].cat);
	अगर (rc)
		जाओ out;

	dst->range.level[1].sens = src->range.level[0].sens;
	rc = ebiपंचांगap_cpy(&dst->range.level[1].cat, &src->range.level[0].cat);
	अगर (rc)
		ebiपंचांगap_destroy(&dst->range.level[0].cat);
out:
	वापस rc;
पूर्ण

/*
 * Sets both levels in the MLS range of 'dst' to the high level of 'src'.
 */
अटल अंतरभूत पूर्णांक mls_context_cpy_high(काष्ठा context *dst, काष्ठा context *src)
अणु
	पूर्णांक rc;

	dst->range.level[0].sens = src->range.level[1].sens;
	rc = ebiपंचांगap_cpy(&dst->range.level[0].cat, &src->range.level[1].cat);
	अगर (rc)
		जाओ out;

	dst->range.level[1].sens = src->range.level[1].sens;
	rc = ebiपंचांगap_cpy(&dst->range.level[1].cat, &src->range.level[1].cat);
	अगर (rc)
		ebiपंचांगap_destroy(&dst->range.level[0].cat);
out:
	वापस rc;
पूर्ण


अटल अंतरभूत पूर्णांक mls_context_glblub(काष्ठा context *dst,
				     काष्ठा context *c1, काष्ठा context *c2)
अणु
	काष्ठा mls_range *dr = &dst->range, *r1 = &c1->range, *r2 = &c2->range;
	पूर्णांक rc = 0;

	अगर (r1->level[1].sens < r2->level[0].sens ||
	    r2->level[1].sens < r1->level[0].sens)
		/* These ranges have no common sensitivities */
		वापस -EINVAL;

	/* Take the greatest of the low */
	dr->level[0].sens = max(r1->level[0].sens, r2->level[0].sens);

	/* Take the least of the high */
	dr->level[1].sens = min(r1->level[1].sens, r2->level[1].sens);

	rc = ebiपंचांगap_and(&dr->level[0].cat,
			 &r1->level[0].cat, &r2->level[0].cat);
	अगर (rc)
		जाओ out;

	rc = ebiपंचांगap_and(&dr->level[1].cat,
			 &r1->level[1].cat, &r2->level[1].cat);
	अगर (rc)
		जाओ out;

out:
	वापस rc;
पूर्ण

अटल अंतरभूत पूर्णांक mls_context_cmp(काष्ठा context *c1, काष्ठा context *c2)
अणु
	वापस ((c1->range.level[0].sens == c2->range.level[0].sens) &&
		ebiपंचांगap_cmp(&c1->range.level[0].cat, &c2->range.level[0].cat) &&
		(c1->range.level[1].sens == c2->range.level[1].sens) &&
		ebiपंचांगap_cmp(&c1->range.level[1].cat, &c2->range.level[1].cat));
पूर्ण

अटल अंतरभूत व्योम mls_context_destroy(काष्ठा context *c)
अणु
	ebiपंचांगap_destroy(&c->range.level[0].cat);
	ebiपंचांगap_destroy(&c->range.level[1].cat);
	mls_context_init(c);
पूर्ण

अटल अंतरभूत व्योम context_init(काष्ठा context *c)
अणु
	स_रखो(c, 0, माप(*c));
पूर्ण

अटल अंतरभूत पूर्णांक context_cpy(काष्ठा context *dst, काष्ठा context *src)
अणु
	पूर्णांक rc;

	dst->user = src->user;
	dst->role = src->role;
	dst->type = src->type;
	अगर (src->str) अणु
		dst->str = kstrdup(src->str, GFP_ATOMIC);
		अगर (!dst->str)
			वापस -ENOMEM;
		dst->len = src->len;
	पूर्ण अन्यथा अणु
		dst->str = शून्य;
		dst->len = 0;
	पूर्ण
	rc = mls_context_cpy(dst, src);
	अगर (rc) अणु
		kमुक्त(dst->str);
		वापस rc;
	पूर्ण
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम context_destroy(काष्ठा context *c)
अणु
	c->user = c->role = c->type = 0;
	kमुक्त(c->str);
	c->str = शून्य;
	c->len = 0;
	mls_context_destroy(c);
पूर्ण

अटल अंतरभूत पूर्णांक context_cmp(काष्ठा context *c1, काष्ठा context *c2)
अणु
	अगर (c1->len && c2->len)
		वापस (c1->len == c2->len && !म_भेद(c1->str, c2->str));
	अगर (c1->len || c2->len)
		वापस 0;
	वापस ((c1->user == c2->user) &&
		(c1->role == c2->role) &&
		(c1->type == c2->type) &&
		mls_context_cmp(c1, c2));
पूर्ण

u32 context_compute_hash(स्थिर काष्ठा context *c);

#पूर्ण_अगर	/* _SS_CONTEXT_H_ */

