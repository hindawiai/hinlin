<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * A tagged poपूर्णांकer implementation
 *
 * Copyright (C) 2018 Gao Xiang <gaoxiang25@huawei.com>
 */
#अगर_अघोषित __EROFS_FS_TAGPTR_H
#घोषणा __EROFS_FS_TAGPTR_H

#समावेश <linux/types.h>
#समावेश <linux/build_bug.h>

/*
 * the name of tagged poपूर्णांकer types are tagptrअणु1, 2, 3...पूर्ण_t
 * aव्योम directly using the पूर्णांकernal काष्ठाs __tagptrअणु1, 2, 3...पूर्ण
 */
#घोषणा __MAKE_TAGPTR(n) \
प्रकार काष्ठा __tagptr##n अणु	\
	uपूर्णांकptr_t v;	\
पूर्ण tagptr##n##_t;

__MAKE_TAGPTR(1)
__MAKE_TAGPTR(2)
__MAKE_TAGPTR(3)
__MAKE_TAGPTR(4)

#अघोषित __MAKE_TAGPTR

बाह्य व्योम __compileसमय_error("bad tagptr tags")
	__bad_tagptr_tags(व्योम);

बाह्य व्योम __compileसमय_error("bad tagptr type")
	__bad_tagptr_type(व्योम);

/* fix the broken usage of "#define tagptr2_t tagptr3_t" by users */
#घोषणा __tagptr_mask_1(ptr, n)	\
	__builtin_types_compatible_p(typeof(ptr), काष्ठा __tagptr##n) ? \
		(1UL << (n)) - 1 :

#घोषणा __tagptr_mask(ptr)	(\
	__tagptr_mask_1(ptr, 1) ( \
	__tagptr_mask_1(ptr, 2) ( \
	__tagptr_mask_1(ptr, 3) ( \
	__tagptr_mask_1(ptr, 4) ( \
	__bad_tagptr_type(), 0)))))

/* generate a tagged poपूर्णांकer from a raw value */
#घोषणा tagptr_init(type, val) \
	((typeof(type))अणु .v = (uपूर्णांकptr_t)(val) पूर्ण)

/*
 * directly cast a tagged poपूर्णांकer to the native poपूर्णांकer type, which
 * could be used क्रम backward compatibility of existing code.
 */
#घोषणा tagptr_cast_ptr(tptr) ((व्योम *)(tptr).v)

/* encode tagged poपूर्णांकers */
#घोषणा tagptr_fold(type, ptr, _tags) (अणु \
	स्थिर typeof(_tags) tags = (_tags); \
	अगर (__builtin_स्थिरant_p(tags) && (tags & ~__tagptr_mask(type))) \
		__bad_tagptr_tags(); \
tagptr_init(type, (uपूर्णांकptr_t)(ptr) | tags); पूर्ण)

/* decode tagged poपूर्णांकers */
#घोषणा tagptr_unfold_ptr(tptr) \
	((व्योम *)((tptr).v & ~__tagptr_mask(tptr)))

#घोषणा tagptr_unfold_tags(tptr) \
	((tptr).v & __tagptr_mask(tptr))

/* operations क्रम the tagger poपूर्णांकer */
#घोषणा tagptr_eq(_tptr1, _tptr2) (अणु \
	typeof(_tptr1) tptr1 = (_tptr1); \
	typeof(_tptr2) tptr2 = (_tptr2); \
	(व्योम)(&tptr1 == &tptr2); \
(tptr1).v == (tptr2).v; पूर्ण)

/* lock-मुक्त CAS operation */
#घोषणा tagptr_cmpxchg(_ptptr, _o, _n) (अणु \
	typeof(_ptptr) ptptr = (_ptptr); \
	typeof(_o) o = (_o); \
	typeof(_n) n = (_n); \
	(व्योम)(&o == &n); \
	(व्योम)(&o == ptptr); \
tagptr_init(o, cmpxchg(&ptptr->v, o.v, n.v)); पूर्ण)

/* wrap WRITE_ONCE अगर atomic update is needed */
#घोषणा tagptr_replace_tags(_ptptr, tags) (अणु \
	typeof(_ptptr) ptptr = (_ptptr); \
	*ptptr = tagptr_fold(*ptptr, tagptr_unfold_ptr(*ptptr), tags); \
*ptptr; पूर्ण)

#घोषणा tagptr_set_tags(_ptptr, _tags) (अणु \
	typeof(_ptptr) ptptr = (_ptptr); \
	स्थिर typeof(_tags) tags = (_tags); \
	अगर (__builtin_स्थिरant_p(tags) && (tags & ~__tagptr_mask(*ptptr))) \
		__bad_tagptr_tags(); \
	ptptr->v |= tags; \
*ptptr; पूर्ण)

#घोषणा tagptr_clear_tags(_ptptr, _tags) (अणु \
	typeof(_ptptr) ptptr = (_ptptr); \
	स्थिर typeof(_tags) tags = (_tags); \
	अगर (__builtin_स्थिरant_p(tags) && (tags & ~__tagptr_mask(*ptptr))) \
		__bad_tagptr_tags(); \
	ptptr->v &= ~tags; \
*ptptr; पूर्ण)

#पूर्ण_अगर	/* __EROFS_FS_TAGPTR_H */

