<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* -*- linux-c -*- ------------------------------------------------------- *
 *
 *   Copyright 2002 H. Peter Anvin - All Rights Reserved
 *
 * ----------------------------------------------------------------------- */

/*
 * raid6/recov.c
 *
 * RAID-6 data recovery in dual failure mode.  In single failure mode,
 * use the RAID-5 algorithm (or, in the हाल of Q failure, just reस्थिरruct
 * the syndrome.)
 */

#समावेश <linux/export.h>
#समावेश <linux/raid/pq.h>

/* Recover two failed data blocks. */
अटल व्योम raid6_2data_recov_पूर्णांकx1(पूर्णांक disks, माप_प्रकार bytes, पूर्णांक faila,
		पूर्णांक failb, व्योम **ptrs)
अणु
	u8 *p, *q, *dp, *dq;
	u8 px, qx, db;
	स्थिर u8 *pbmul;	/* P multiplier table क्रम B data */
	स्थिर u8 *qmul;		/* Q multiplier table (क्रम both) */

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
	जबतक ( bytes-- ) अणु
		px    = *p ^ *dp;
		qx    = qmul[*q ^ *dq];
		*dq++ = db = pbmul[px] ^ qx; /* Reस्थिरructed B */
		*dp++ = db ^ px; /* Reस्थिरructed A */
		p++; q++;
	पूर्ण
पूर्ण

/* Recover failure of one data block plus the P block */
अटल व्योम raid6_datap_recov_पूर्णांकx1(पूर्णांक disks, माप_प्रकार bytes, पूर्णांक faila,
		व्योम **ptrs)
अणु
	u8 *p, *q, *dq;
	स्थिर u8 *qmul;		/* Q multiplier table */

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
	जबतक ( bytes-- ) अणु
		*p++ ^= *dq = qmul[*q ^ *dq];
		q++; dq++;
	पूर्ण
पूर्ण


स्थिर काष्ठा raid6_recov_calls raid6_recov_पूर्णांकx1 = अणु
	.data2 = raid6_2data_recov_पूर्णांकx1,
	.datap = raid6_datap_recov_पूर्णांकx1,
	.valid = शून्य,
	.name = "intx1",
	.priority = 0,
पूर्ण;

#अगर_अघोषित __KERNEL__
/* Testing only */

/* Recover two failed blocks. */
व्योम raid6_dual_recov(पूर्णांक disks, माप_प्रकार bytes, पूर्णांक faila, पूर्णांक failb, व्योम **ptrs)
अणु
	अगर ( faila > failb ) अणु
		पूर्णांक पंचांगp = faila;
		faila = failb;
		failb = पंचांगp;
	पूर्ण

	अगर ( failb == disks-1 ) अणु
		अगर ( faila == disks-2 ) अणु
			/* P+Q failure.  Just rebuild the syndrome. */
			raid6_call.gen_syndrome(disks, bytes, ptrs);
		पूर्ण अन्यथा अणु
			/* data+Q failure.  Reस्थिरruct data from P,
			   then rebuild syndrome. */
			/* NOT IMPLEMENTED - equivalent to RAID-5 */
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर ( failb == disks-2 ) अणु
			/* data+P failure. */
			raid6_datap_recov(disks, bytes, faila, ptrs);
		पूर्ण अन्यथा अणु
			/* data+data failure. */
			raid6_2data_recov(disks, bytes, faila, failb, ptrs);
		पूर्ण
	पूर्ण
पूर्ण

#पूर्ण_अगर
