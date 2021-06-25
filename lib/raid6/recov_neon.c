<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2012 Intel Corporation
 * Copyright (C) 2017 Linaro Ltd. <ard.biesheuvel@linaro.org>
 */

#समावेश <linux/raid/pq.h>

#अगर_घोषित __KERNEL__
#समावेश <यंत्र/neon.h>
#अन्यथा
#घोषणा kernel_neon_begin()
#घोषणा kernel_neon_end()
#घोषणा cpu_has_neon()		(1)
#पूर्ण_अगर

अटल पूर्णांक raid6_has_neon(व्योम)
अणु
	वापस cpu_has_neon();
पूर्ण

व्योम __raid6_2data_recov_neon(पूर्णांक bytes, uपूर्णांक8_t *p, uपूर्णांक8_t *q, uपूर्णांक8_t *dp,
			      uपूर्णांक8_t *dq, स्थिर uपूर्णांक8_t *pbmul,
			      स्थिर uपूर्णांक8_t *qmul);

व्योम __raid6_datap_recov_neon(पूर्णांक bytes, uपूर्णांक8_t *p, uपूर्णांक8_t *q, uपूर्णांक8_t *dq,
			      स्थिर uपूर्णांक8_t *qmul);

अटल व्योम raid6_2data_recov_neon(पूर्णांक disks, माप_प्रकार bytes, पूर्णांक faila,
		पूर्णांक failb, व्योम **ptrs)
अणु
	u8 *p, *q, *dp, *dq;
	स्थिर u8 *pbmul;	/* P multiplier table क्रम B data */
	स्थिर u8 *qmul;		/* Q multiplier table (क्रम both) */

	p = (u8 *)ptrs[disks - 2];
	q = (u8 *)ptrs[disks - 1];

	/*
	 * Compute syndrome with zero क्रम the missing data pages
	 * Use the dead data pages as temporary storage क्रम
	 * delta p and delta q
	 */
	dp = (u8 *)ptrs[faila];
	ptrs[faila] = (व्योम *)raid6_empty_zero_page;
	ptrs[disks - 2] = dp;
	dq = (u8 *)ptrs[failb];
	ptrs[failb] = (व्योम *)raid6_empty_zero_page;
	ptrs[disks - 1] = dq;

	raid6_call.gen_syndrome(disks, bytes, ptrs);

	/* Restore poपूर्णांकer table */
	ptrs[faila]     = dp;
	ptrs[failb]     = dq;
	ptrs[disks - 2] = p;
	ptrs[disks - 1] = q;

	/* Now, pick the proper data tables */
	pbmul = raid6_vgfmul[raid6_gfexi[failb-faila]];
	qmul  = raid6_vgfmul[raid6_gfinv[raid6_gfexp[faila] ^
					 raid6_gfexp[failb]]];

	kernel_neon_begin();
	__raid6_2data_recov_neon(bytes, p, q, dp, dq, pbmul, qmul);
	kernel_neon_end();
पूर्ण

अटल व्योम raid6_datap_recov_neon(पूर्णांक disks, माप_प्रकार bytes, पूर्णांक faila,
		व्योम **ptrs)
अणु
	u8 *p, *q, *dq;
	स्थिर u8 *qmul;		/* Q multiplier table */

	p = (u8 *)ptrs[disks - 2];
	q = (u8 *)ptrs[disks - 1];

	/*
	 * Compute syndrome with zero क्रम the missing data page
	 * Use the dead data page as temporary storage क्रम delta q
	 */
	dq = (u8 *)ptrs[faila];
	ptrs[faila] = (व्योम *)raid6_empty_zero_page;
	ptrs[disks - 1] = dq;

	raid6_call.gen_syndrome(disks, bytes, ptrs);

	/* Restore poपूर्णांकer table */
	ptrs[faila]     = dq;
	ptrs[disks - 1] = q;

	/* Now, pick the proper data tables */
	qmul = raid6_vgfmul[raid6_gfinv[raid6_gfexp[faila]]];

	kernel_neon_begin();
	__raid6_datap_recov_neon(bytes, p, q, dq, qmul);
	kernel_neon_end();
पूर्ण

स्थिर काष्ठा raid6_recov_calls raid6_recov_neon = अणु
	.data2		= raid6_2data_recov_neon,
	.datap		= raid6_datap_recov_neon,
	.valid		= raid6_has_neon,
	.name		= "neon",
	.priority	= 10,
पूर्ण;
