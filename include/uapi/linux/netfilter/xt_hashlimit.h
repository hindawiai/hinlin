<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _UAPI_XT_HASHLIMIT_H
#घोषणा _UAPI_XT_HASHLIMIT_H

#समावेश <linux/types.h>
#समावेश <linux/सीमा.स>
#समावेश <linux/अगर.h>

/* timings are in milliseconds. */
#घोषणा XT_HASHLIMIT_SCALE 10000
#घोषणा XT_HASHLIMIT_SCALE_v2 1000000llu
/* 1/10,000 sec period => max of 10,000/sec.  Min rate is then 429490
 * seconds, or one packet every 59 hours.
 */

/* packet length accounting is करोne in 16-byte steps */
#घोषणा XT_HASHLIMIT_BYTE_SHIFT 4

/* details of this काष्ठाure hidden by the implementation */
काष्ठा xt_hashlimit_htable;

क्रमागत अणु
	XT_HASHLIMIT_HASH_DIP		= 1 << 0,
	XT_HASHLIMIT_HASH_DPT		= 1 << 1,
	XT_HASHLIMIT_HASH_SIP		= 1 << 2,
	XT_HASHLIMIT_HASH_SPT		= 1 << 3,
	XT_HASHLIMIT_INVERT		= 1 << 4,
	XT_HASHLIMIT_BYTES		= 1 << 5,
	XT_HASHLIMIT_RATE_MATCH		= 1 << 6,
पूर्ण;

काष्ठा hashlimit_cfg अणु
	__u32 mode;	  /* biपंचांगask of XT_HASHLIMIT_HASH_* */
	__u32 avg;    /* Average secs between packets * scale */
	__u32 burst;  /* Period multiplier क्रम upper limit. */

	/* user specअगरied */
	__u32 size;		/* how many buckets */
	__u32 max;		/* max number of entries */
	__u32 gc_पूर्णांकerval;	/* gc पूर्णांकerval */
	__u32 expire;	/* when करो entries expire? */
पूर्ण;

काष्ठा xt_hashlimit_info अणु
	अक्षर name [IFNAMSIZ];		/* name */
	काष्ठा hashlimit_cfg cfg;

	/* Used पूर्णांकernally by the kernel */
	काष्ठा xt_hashlimit_htable *hinfo;
	जोड़ अणु
		व्योम *ptr;
		काष्ठा xt_hashlimit_info *master;
	पूर्ण u;
पूर्ण;

काष्ठा hashlimit_cfg1 अणु
	__u32 mode;	  /* biपंचांगask of XT_HASHLIMIT_HASH_* */
	__u32 avg;    /* Average secs between packets * scale */
	__u32 burst;  /* Period multiplier क्रम upper limit. */

	/* user specअगरied */
	__u32 size;		/* how many buckets */
	__u32 max;		/* max number of entries */
	__u32 gc_पूर्णांकerval;	/* gc पूर्णांकerval */
	__u32 expire;	/* when करो entries expire? */

	__u8 srcmask, dsपंचांगask;
पूर्ण;

काष्ठा hashlimit_cfg2 अणु
	__u64 avg;		/* Average secs between packets * scale */
	__u64 burst;		/* Period multiplier क्रम upper limit. */
	__u32 mode;		/* biपंचांगask of XT_HASHLIMIT_HASH_* */

	/* user specअगरied */
	__u32 size;		/* how many buckets */
	__u32 max;		/* max number of entries */
	__u32 gc_पूर्णांकerval;	/* gc पूर्णांकerval */
	__u32 expire;		/* when करो entries expire? */

	__u8 srcmask, dsपंचांगask;
पूर्ण;

काष्ठा hashlimit_cfg3 अणु
	__u64 avg;		/* Average secs between packets * scale */
	__u64 burst;		/* Period multiplier क्रम upper limit. */
	__u32 mode;		/* biपंचांगask of XT_HASHLIMIT_HASH_* */

	/* user specअगरied */
	__u32 size;		/* how many buckets */
	__u32 max;		/* max number of entries */
	__u32 gc_पूर्णांकerval;	/* gc पूर्णांकerval */
	__u32 expire;		/* when करो entries expire? */

	__u32 पूर्णांकerval;
	__u8 srcmask, dsपंचांगask;
पूर्ण;

काष्ठा xt_hashlimit_mtinfo1 अणु
	अक्षर name[IFNAMSIZ];
	काष्ठा hashlimit_cfg1 cfg;

	/* Used पूर्णांकernally by the kernel */
	काष्ठा xt_hashlimit_htable *hinfo __attribute__((aligned(8)));
पूर्ण;

काष्ठा xt_hashlimit_mtinfo2 अणु
	अक्षर name[NAME_MAX];
	काष्ठा hashlimit_cfg2 cfg;

	/* Used पूर्णांकernally by the kernel */
	काष्ठा xt_hashlimit_htable *hinfo __attribute__((aligned(8)));
पूर्ण;

काष्ठा xt_hashlimit_mtinfo3 अणु
	अक्षर name[NAME_MAX];
	काष्ठा hashlimit_cfg3 cfg;

	/* Used पूर्णांकernally by the kernel */
	काष्ठा xt_hashlimit_htable *hinfo __attribute__((aligned(8)));
पूर्ण;

#पूर्ण_अगर /* _UAPI_XT_HASHLIMIT_H */
