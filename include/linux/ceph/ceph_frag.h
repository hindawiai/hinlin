<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित FS_CEPH_FRAG_H
#घोषणा FS_CEPH_FRAG_H

/*
 * "Frags" are a way to describe a subset of a 32-bit number space,
 * using a mask and a value to match against that mask.  Any given frag
 * (subset of the number space) can be partitioned पूर्णांकo 2^n sub-frags.
 *
 * Frags are encoded पूर्णांकo a 32-bit word:
 *   8 upper bits = "bits"
 *  24 lower bits = "value"
 * (We could go to 5+27 bits, but who cares.)
 *
 * We use the _most_ signअगरicant bits of the 24 bit value.  This makes
 * values logically sort.
 *
 * Unक्रमtunately, because the "bits" field is still in the high bits, we
 * can't sort encoded frags numerically.  However, it करोes allow you
 * to feed encoded frags as values पूर्णांकo frag_contains_value.
 */
अटल अंतरभूत __u32 ceph_frag_make(__u32 b, __u32 v)
अणु
	वापस (b << 24) |
		(v & (0xffffffu << (24-b)) & 0xffffffu);
पूर्ण
अटल अंतरभूत __u32 ceph_frag_bits(__u32 f)
अणु
	वापस f >> 24;
पूर्ण
अटल अंतरभूत __u32 ceph_frag_value(__u32 f)
अणु
	वापस f & 0xffffffu;
पूर्ण
अटल अंतरभूत __u32 ceph_frag_mask(__u32 f)
अणु
	वापस (0xffffffu << (24-ceph_frag_bits(f))) & 0xffffffu;
पूर्ण
अटल अंतरभूत __u32 ceph_frag_mask_shअगरt(__u32 f)
अणु
	वापस 24 - ceph_frag_bits(f);
पूर्ण

अटल अंतरभूत bool ceph_frag_contains_value(__u32 f, __u32 v)
अणु
	वापस (v & ceph_frag_mask(f)) == ceph_frag_value(f);
पूर्ण

अटल अंतरभूत __u32 ceph_frag_make_child(__u32 f, पूर्णांक by, पूर्णांक i)
अणु
	पूर्णांक newbits = ceph_frag_bits(f) + by;
	वापस ceph_frag_make(newbits,
			 ceph_frag_value(f) | (i << (24 - newbits)));
पूर्ण
अटल अंतरभूत bool ceph_frag_is_lefपंचांगost(__u32 f)
अणु
	वापस ceph_frag_value(f) == 0;
पूर्ण
अटल अंतरभूत bool ceph_frag_is_righपंचांगost(__u32 f)
अणु
	वापस ceph_frag_value(f) == ceph_frag_mask(f);
पूर्ण
अटल अंतरभूत __u32 ceph_frag_next(__u32 f)
अणु
	वापस ceph_frag_make(ceph_frag_bits(f),
			 ceph_frag_value(f) + (0x1000000 >> ceph_frag_bits(f)));
पूर्ण

/*
 * comparator to sort frags logically, as when traversing the
 * number space in ascending order...
 */
पूर्णांक ceph_frag_compare(__u32 a, __u32 b);

#पूर्ण_अगर
