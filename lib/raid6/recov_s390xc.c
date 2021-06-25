<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * RAID-6 data recovery in dual failure mode based on the XC inकाष्ठाion.
 *
 * Copyright IBM Corp. 2016
 * Author(s): Martin Schwidefsky <schwidefsky@de.ibm.com>
 */

#समावेश <linux/export.h>
#समावेश <linux/raid/pq.h>

अटल अंतरभूत व्योम xor_block(u8 *p1, u8 *p2)
अणु
	प्रकार काष्ठा अणु u8 _[256]; पूर्ण addrtype;

	यंत्र अस्थिर(
		"	xc	0(256,%[p1]),0(%[p2])\n"
		: "+m" (*(addrtype *) p1) : "m" (*(addrtype *) p2),
		  [p1] "a" (p1), [p2] "a" (p2) : "cc");
पूर्ण

/* Recover two failed data blocks. */
अटल व्योम raid6_2data_recov_s390xc(पूर्णांक disks, माप_प्रकार bytes, पूर्णांक faila,
		पूर्णांक failb, व्योम **ptrs)
अणु
	u8 *p, *q, *dp, *dq;
	स्थिर u8 *pbmul;	/* P multiplier table क्रम B data */
	स्थिर u8 *qmul;		/* Q multiplier table (क्रम both) */
	पूर्णांक i;

	p = (u8 *)ptrs[disks-2];
	q = (u8 *)ptrs[disks-1];

	/* Compute syndrome with zero क्रम the missing data pages
	   Use the dead data pages as temporary storage क्रम
	   delta p and delta q */
	dp = (u8 *)ptrs[faila];
	ptrs[faila] = (व्योम *)raid6_empty_zero_page;
	ptrs[disks-2] = dp;
	dq = (u8 *)ptrs[failb];
	ptrs[failb] = (व्योम *)raid6_empty_zero_page;
	ptrs[disks-1] = dq;

	raid6_call.gen_syndrome(disks, bytes, ptrs);

	/* Restore poपूर्णांकer table */
	ptrs[faila]   = dp;
	ptrs[failb]   = dq;
	ptrs[disks-2] = p;
	ptrs[disks-1] = q;

	/* Now, pick the proper data tables */
	pbmul = raid6_gfmul[raid6_gfexi[failb-faila]];
	qmul  = raid6_gfmul[raid6_gfinv[raid6_gfexp[faila]^raid6_gfexp[failb]]];

	/* Now करो it... */
	जबतक (bytes) अणु
		xor_block(dp, p);
		xor_block(dq, q);
		क्रम (i = 0; i < 256; i++)
			dq[i] = pbmul[dp[i]] ^ qmul[dq[i]];
		xor_block(dp, dq);
		p += 256;
		q += 256;
		dp += 256;
		dq += 256;
		bytes -= 256;
	पूर्ण
पूर्ण

/* Recover failure of one data block plus the P block */
अटल व्योम raid6_datap_recov_s390xc(पूर्णांक disks, माप_प्रकार bytes, पूर्णांक faila,
		व्योम **ptrs)
अणु
	u8 *p, *q, *dq;
	स्थिर u8 *qmul;		/* Q multiplier table */
	पूर्णांक i;

	p = (u8 *)ptrs[disks-2];
	q = (u8 *)ptrs[disks-1];

	/* Compute syndrome with zero क्रम the missing data page
	   Use the dead data page as temporary storage क्रम delta q */
	dq = (u8 *)ptrs[faila];
	ptrs[faila] = (व्योम *)raid6_empty_zero_page;
	ptrs[disks-1] = dq;

	raid6_call.gen_syndrome(disks, bytes, ptrs);

	/* Restore poपूर्णांकer table */
	ptrs[faila]   = dq;
	ptrs[disks-1] = q;

	/* Now, pick the proper data tables */
	qmul  = raid6_gfmul[raid6_gfinv[raid6_gfexp[faila]]];

	/* Now करो it... */
	जबतक (bytes) अणु
		xor_block(dq, q);
		क्रम (i = 0; i < 256; i++)
			dq[i] = qmul[dq[i]];
		xor_block(p, dq);
		p += 256;
		q += 256;
		dq += 256;
		bytes -= 256;
	पूर्ण
पूर्ण


स्थिर काष्ठा raid6_recov_calls raid6_recov_s390xc = अणु
	.data2 = raid6_2data_recov_s390xc,
	.datap = raid6_datap_recov_s390xc,
	.valid = शून्य,
	.name = "s390xc",
	.priority = 1,
पूर्ण;
