<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  linux/fs/hfsplus/unicode.c
 *
 * Copyright (C) 2001
 * Brad Boyer (flar@allandria.com)
 * (C) 2003 Ardis Technologies <roman@ardistech.com>
 *
 * Handler routines क्रम unicode strings
 */

#समावेश <linux/types.h>
#समावेश <linux/nls.h>
#समावेश "hfsplus_fs.h"
#समावेश "hfsplus_raw.h"

/* Fold the हाल of a unicode अक्षर, given the 16 bit value */
/* Returns folded अक्षर, or 0 अगर ignorable */
अटल अंतरभूत u16 हाल_fold(u16 c)
अणु
	u16 पंचांगp;

	पंचांगp = hfsplus_हाल_fold_table[c >> 8];
	अगर (पंचांगp)
		पंचांगp = hfsplus_हाल_fold_table[पंचांगp + (c & 0xff)];
	अन्यथा
		पंचांगp = c;
	वापस पंचांगp;
पूर्ण

/* Compare unicode strings, वापस values like normal म_भेद */
पूर्णांक hfsplus_strहालcmp(स्थिर काष्ठा hfsplus_unistr *s1,
		       स्थिर काष्ठा hfsplus_unistr *s2)
अणु
	u16 len1, len2, c1, c2;
	स्थिर hfsplus_unichr *p1, *p2;

	len1 = be16_to_cpu(s1->length);
	len2 = be16_to_cpu(s2->length);
	p1 = s1->unicode;
	p2 = s2->unicode;

	जबतक (1) अणु
		c1 = c2 = 0;

		जबतक (len1 && !c1) अणु
			c1 = हाल_fold(be16_to_cpu(*p1));
			p1++;
			len1--;
		पूर्ण
		जबतक (len2 && !c2) अणु
			c2 = हाल_fold(be16_to_cpu(*p2));
			p2++;
			len2--;
		पूर्ण

		अगर (c1 != c2)
			वापस (c1 < c2) ? -1 : 1;
		अगर (!c1 && !c2)
			वापस 0;
	पूर्ण
पूर्ण

/* Compare names as a sequence of 16-bit अचिन्हित पूर्णांकegers */
पूर्णांक hfsplus_म_भेद(स्थिर काष्ठा hfsplus_unistr *s1,
		   स्थिर काष्ठा hfsplus_unistr *s2)
अणु
	u16 len1, len2, c1, c2;
	स्थिर hfsplus_unichr *p1, *p2;
	पूर्णांक len;

	len1 = be16_to_cpu(s1->length);
	len2 = be16_to_cpu(s2->length);
	p1 = s1->unicode;
	p2 = s2->unicode;

	क्रम (len = min(len1, len2); len > 0; len--) अणु
		c1 = be16_to_cpu(*p1);
		c2 = be16_to_cpu(*p2);
		अगर (c1 != c2)
			वापस c1 < c2 ? -1 : 1;
		p1++;
		p2++;
	पूर्ण

	वापस len1 < len2 ? -1 :
	       len1 > len2 ? 1 : 0;
पूर्ण


#घोषणा Hangul_SBase	0xac00
#घोषणा Hangul_LBase	0x1100
#घोषणा Hangul_VBase	0x1161
#घोषणा Hangul_TBase	0x11a7
#घोषणा Hangul_SCount	11172
#घोषणा Hangul_LCount	19
#घोषणा Hangul_VCount	21
#घोषणा Hangul_TCount	28
#घोषणा Hangul_NCount	(Hangul_VCount * Hangul_TCount)


अटल u16 *hfsplus_compose_lookup(u16 *p, u16 cc)
अणु
	पूर्णांक i, s, e;

	s = 1;
	e = p[1];
	अगर (!e || cc < p[s * 2] || cc > p[e * 2])
		वापस शून्य;
	करो अणु
		i = (s + e) / 2;
		अगर (cc > p[i * 2])
			s = i + 1;
		अन्यथा अगर (cc < p[i * 2])
			e = i - 1;
		अन्यथा
			वापस hfsplus_compose_table + p[i * 2 + 1];
	पूर्ण जबतक (s <= e);
	वापस शून्य;
पूर्ण

पूर्णांक hfsplus_uni2asc(काष्ठा super_block *sb,
		स्थिर काष्ठा hfsplus_unistr *ustr,
		अक्षर *astr, पूर्णांक *len_p)
अणु
	स्थिर hfsplus_unichr *ip;
	काष्ठा nls_table *nls = HFSPLUS_SB(sb)->nls;
	u8 *op;
	u16 cc, c0, c1;
	u16 *ce1, *ce2;
	पूर्णांक i, len, uम_माप, res, compose;

	op = astr;
	ip = ustr->unicode;
	uम_माप = be16_to_cpu(ustr->length);
	len = *len_p;
	ce1 = शून्य;
	compose = !test_bit(HFSPLUS_SB_NODECOMPOSE, &HFSPLUS_SB(sb)->flags);

	जबतक (uम_माप > 0) अणु
		c0 = be16_to_cpu(*ip++);
		uम_माप--;
		/* search क्रम single decomposed अक्षर */
		अगर (likely(compose))
			ce1 = hfsplus_compose_lookup(hfsplus_compose_table, c0);
		अगर (ce1)
			cc = ce1[0];
		अन्यथा
			cc = 0;
		अगर (cc) अणु
			/* start of a possibly decomposed Hangul अक्षर */
			अगर (cc != 0xffff)
				जाओ करोne;
			अगर (!uम_माप)
				जाओ same;
			c1 = be16_to_cpu(*ip) - Hangul_VBase;
			अगर (c1 < Hangul_VCount) अणु
				/* compose the Hangul अक्षर */
				cc = (c0 - Hangul_LBase) * Hangul_VCount;
				cc = (cc + c1) * Hangul_TCount;
				cc += Hangul_SBase;
				ip++;
				uम_माप--;
				अगर (!uम_माप)
					जाओ करोne;
				c1 = be16_to_cpu(*ip) - Hangul_TBase;
				अगर (c1 > 0 && c1 < Hangul_TCount) अणु
					cc += c1;
					ip++;
					uम_माप--;
				पूर्ण
				जाओ करोne;
			पूर्ण
		पूर्ण
		जबतक (1) अणु
			/* मुख्य loop क्रम common हाल of not composed अक्षरs */
			अगर (!uम_माप)
				जाओ same;
			c1 = be16_to_cpu(*ip);
			अगर (likely(compose))
				ce1 = hfsplus_compose_lookup(
					hfsplus_compose_table, c1);
			अगर (ce1)
				अवरोध;
			चयन (c0) अणु
			हाल 0:
				c0 = 0x2400;
				अवरोध;
			हाल '/':
				c0 = ':';
				अवरोध;
			पूर्ण
			res = nls->uni2अक्षर(c0, op, len);
			अगर (res < 0) अणु
				अगर (res == -ENAMETOOLONG)
					जाओ out;
				*op = '?';
				res = 1;
			पूर्ण
			op += res;
			len -= res;
			c0 = c1;
			ip++;
			uम_माप--;
		पूर्ण
		ce2 = hfsplus_compose_lookup(ce1, c0);
		अगर (ce2) अणु
			i = 1;
			जबतक (i < uम_माप) अणु
				ce1 = hfsplus_compose_lookup(ce2,
					be16_to_cpu(ip[i]));
				अगर (!ce1)
					अवरोध;
				i++;
				ce2 = ce1;
			पूर्ण
			cc = ce2[0];
			अगर (cc) अणु
				ip += i;
				uम_माप -= i;
				जाओ करोne;
			पूर्ण
		पूर्ण
same:
		चयन (c0) अणु
		हाल 0:
			cc = 0x2400;
			अवरोध;
		हाल '/':
			cc = ':';
			अवरोध;
		शेष:
			cc = c0;
		पूर्ण
करोne:
		res = nls->uni2अक्षर(cc, op, len);
		अगर (res < 0) अणु
			अगर (res == -ENAMETOOLONG)
				जाओ out;
			*op = '?';
			res = 1;
		पूर्ण
		op += res;
		len -= res;
	पूर्ण
	res = 0;
out:
	*len_p = (अक्षर *)op - astr;
	वापस res;
पूर्ण

/*
 * Convert one or more ASCII अक्षरacters पूर्णांकo a single unicode अक्षरacter.
 * Returns the number of ASCII अक्षरacters corresponding to the unicode अक्षर.
 */
अटल अंतरभूत पूर्णांक asc2uniअक्षर(काष्ठा super_block *sb, स्थिर अक्षर *astr, पूर्णांक len,
			      ब_अक्षर_प्रकार *uc)
अणु
	पूर्णांक size = HFSPLUS_SB(sb)->nls->अक्षर2uni(astr, len, uc);
	अगर (size <= 0) अणु
		*uc = '?';
		size = 1;
	पूर्ण
	चयन (*uc) अणु
	हाल 0x2400:
		*uc = 0;
		अवरोध;
	हाल ':':
		*uc = '/';
		अवरोध;
	पूर्ण
	वापस size;
पूर्ण

/* Decomposes a non-Hangul unicode अक्षरacter. */
अटल u16 *hfsplus_decompose_nonhangul(ब_अक्षर_प्रकार uc, पूर्णांक *size)
अणु
	पूर्णांक off;

	off = hfsplus_decompose_table[(uc >> 12) & 0xf];
	अगर (off == 0 || off == 0xffff)
		वापस शून्य;

	off = hfsplus_decompose_table[off + ((uc >> 8) & 0xf)];
	अगर (!off)
		वापस शून्य;

	off = hfsplus_decompose_table[off + ((uc >> 4) & 0xf)];
	अगर (!off)
		वापस शून्य;

	off = hfsplus_decompose_table[off + (uc & 0xf)];
	*size = off & 3;
	अगर (*size == 0)
		वापस शून्य;
	वापस hfsplus_decompose_table + (off / 4);
पूर्ण

/*
 * Try to decompose a unicode अक्षरacter as Hangul. Return 0 अगर @uc is not
 * precomposed Hangul, otherwise वापस the length of the decomposition.
 *
 * This function was adapted from sample code from the Unicode Standard
 * Annex #15: Unicode Normalization Forms, version 3.2.0.
 *
 * Copyright (C) 1991-2018 Unicode, Inc.  All rights reserved.  Distributed
 * under the Terms of Use in http://www.unicode.org/copyright.hपंचांगl.
 */
अटल पूर्णांक hfsplus_try_decompose_hangul(ब_अक्षर_प्रकार uc, u16 *result)
अणु
	पूर्णांक index;
	पूर्णांक l, v, t;

	index = uc - Hangul_SBase;
	अगर (index < 0 || index >= Hangul_SCount)
		वापस 0;

	l = Hangul_LBase + index / Hangul_NCount;
	v = Hangul_VBase + (index % Hangul_NCount) / Hangul_TCount;
	t = Hangul_TBase + index % Hangul_TCount;

	result[0] = l;
	result[1] = v;
	अगर (t != Hangul_TBase) अणु
		result[2] = t;
		वापस 3;
	पूर्ण
	वापस 2;
पूर्ण

/* Decomposes a single unicode अक्षरacter. */
अटल u16 *decompose_uniअक्षर(ब_अक्षर_प्रकार uc, पूर्णांक *size, u16 *hangul_buffer)
अणु
	u16 *result;

	/* Hangul is handled separately */
	result = hangul_buffer;
	*size = hfsplus_try_decompose_hangul(uc, result);
	अगर (*size == 0)
		result = hfsplus_decompose_nonhangul(uc, size);
	वापस result;
पूर्ण

पूर्णांक hfsplus_asc2uni(काष्ठा super_block *sb,
		    काष्ठा hfsplus_unistr *ustr, पूर्णांक max_unistr_len,
		    स्थिर अक्षर *astr, पूर्णांक len)
अणु
	पूर्णांक size, dsize, decompose;
	u16 *dstr, outlen = 0;
	ब_अक्षर_प्रकार c;
	u16 dhangul[3];

	decompose = !test_bit(HFSPLUS_SB_NODECOMPOSE, &HFSPLUS_SB(sb)->flags);
	जबतक (outlen < max_unistr_len && len > 0) अणु
		size = asc2uniअक्षर(sb, astr, len, &c);

		अगर (decompose)
			dstr = decompose_uniअक्षर(c, &dsize, dhangul);
		अन्यथा
			dstr = शून्य;
		अगर (dstr) अणु
			अगर (outlen + dsize > max_unistr_len)
				अवरोध;
			करो अणु
				ustr->unicode[outlen++] = cpu_to_be16(*dstr++);
			पूर्ण जबतक (--dsize > 0);
		पूर्ण अन्यथा
			ustr->unicode[outlen++] = cpu_to_be16(c);

		astr += size;
		len -= size;
	पूर्ण
	ustr->length = cpu_to_be16(outlen);
	अगर (len > 0)
		वापस -ENAMETOOLONG;
	वापस 0;
पूर्ण

/*
 * Hash a string to an पूर्णांकeger as appropriate क्रम the HFS+ fileप्रणाली.
 * Composed unicode अक्षरacters are decomposed and हाल-folding is perक्रमmed
 * अगर the appropriate bits are (un)set on the superblock.
 */
पूर्णांक hfsplus_hash_dentry(स्थिर काष्ठा dentry *dentry, काष्ठा qstr *str)
अणु
	काष्ठा super_block *sb = dentry->d_sb;
	स्थिर अक्षर *astr;
	स्थिर u16 *dstr;
	पूर्णांक हालfold, decompose, size, len;
	अचिन्हित दीर्घ hash;
	ब_अक्षर_प्रकार c;
	u16 c2;
	u16 dhangul[3];

	हालfold = test_bit(HFSPLUS_SB_CASEFOLD, &HFSPLUS_SB(sb)->flags);
	decompose = !test_bit(HFSPLUS_SB_NODECOMPOSE, &HFSPLUS_SB(sb)->flags);
	hash = init_name_hash(dentry);
	astr = str->name;
	len = str->len;
	जबतक (len > 0) अणु
		पूर्णांक dsize;
		size = asc2uniअक्षर(sb, astr, len, &c);
		astr += size;
		len -= size;

		अगर (decompose)
			dstr = decompose_uniअक्षर(c, &dsize, dhangul);
		अन्यथा
			dstr = शून्य;
		अगर (dstr) अणु
			करो अणु
				c2 = *dstr++;
				अगर (हालfold)
					c2 = हाल_fold(c2);
				अगर (!हालfold || c2)
					hash = partial_name_hash(c2, hash);
			पूर्ण जबतक (--dsize > 0);
		पूर्ण अन्यथा अणु
			c2 = c;
			अगर (हालfold)
				c2 = हाल_fold(c2);
			अगर (!हालfold || c2)
				hash = partial_name_hash(c2, hash);
		पूर्ण
	पूर्ण
	str->hash = end_name_hash(hash);

	वापस 0;
पूर्ण

/*
 * Compare strings with HFS+ filename ordering.
 * Composed unicode अक्षरacters are decomposed and हाल-folding is perक्रमmed
 * अगर the appropriate bits are (un)set on the superblock.
 */
पूर्णांक hfsplus_compare_dentry(स्थिर काष्ठा dentry *dentry,
		अचिन्हित पूर्णांक len, स्थिर अक्षर *str, स्थिर काष्ठा qstr *name)
अणु
	काष्ठा super_block *sb = dentry->d_sb;
	पूर्णांक हालfold, decompose, size;
	पूर्णांक dsize1, dsize2, len1, len2;
	स्थिर u16 *dstr1, *dstr2;
	स्थिर अक्षर *astr1, *astr2;
	u16 c1, c2;
	ब_अक्षर_प्रकार c;
	u16 dhangul_1[3], dhangul_2[3];

	हालfold = test_bit(HFSPLUS_SB_CASEFOLD, &HFSPLUS_SB(sb)->flags);
	decompose = !test_bit(HFSPLUS_SB_NODECOMPOSE, &HFSPLUS_SB(sb)->flags);
	astr1 = str;
	len1 = len;
	astr2 = name->name;
	len2 = name->len;
	dsize1 = dsize2 = 0;
	dstr1 = dstr2 = शून्य;

	जबतक (len1 > 0 && len2 > 0) अणु
		अगर (!dsize1) अणु
			size = asc2uniअक्षर(sb, astr1, len1, &c);
			astr1 += size;
			len1 -= size;

			अगर (decompose)
				dstr1 = decompose_uniअक्षर(c, &dsize1,
							  dhangul_1);
			अगर (!decompose || !dstr1) अणु
				c1 = c;
				dstr1 = &c1;
				dsize1 = 1;
			पूर्ण
		पूर्ण

		अगर (!dsize2) अणु
			size = asc2uniअक्षर(sb, astr2, len2, &c);
			astr2 += size;
			len2 -= size;

			अगर (decompose)
				dstr2 = decompose_uniअक्षर(c, &dsize2,
							  dhangul_2);
			अगर (!decompose || !dstr2) अणु
				c2 = c;
				dstr2 = &c2;
				dsize2 = 1;
			पूर्ण
		पूर्ण

		c1 = *dstr1;
		c2 = *dstr2;
		अगर (हालfold) अणु
			c1 = हाल_fold(c1);
			अगर (!c1) अणु
				dstr1++;
				dsize1--;
				जारी;
			पूर्ण
			c2 = हाल_fold(c2);
			अगर (!c2) अणु
				dstr2++;
				dsize2--;
				जारी;
			पूर्ण
		पूर्ण
		अगर (c1 < c2)
			वापस -1;
		अन्यथा अगर (c1 > c2)
			वापस 1;

		dstr1++;
		dsize1--;
		dstr2++;
		dsize2--;
	पूर्ण

	अगर (len1 < len2)
		वापस -1;
	अगर (len1 > len2)
		वापस 1;
	वापस 0;
पूर्ण
