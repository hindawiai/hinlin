<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* -*- linux-c -*- ------------------------------------------------------- *
 *
 *   Copyright 2002-2007 H. Peter Anvin - All Rights Reserved
 *
 * ----------------------------------------------------------------------- */

/*
 * raid6test.c
 *
 * Test RAID-6 recovery with various algorithms
 */

#समावेश <मानककोष.स>
#समावेश <मानकपन.स>
#समावेश <माला.स>
#समावेश <linux/raid/pq.h>

#घोषणा NDISKS		16	/* Including P and Q */

स्थिर अक्षर raid6_empty_zero_page[PAGE_SIZE] __attribute__((aligned(PAGE_SIZE)));
काष्ठा raid6_calls raid6_call;

अक्षर *dataptrs[NDISKS];
अक्षर data[NDISKS][PAGE_SIZE] __attribute__((aligned(PAGE_SIZE)));
अक्षर recovi[PAGE_SIZE] __attribute__((aligned(PAGE_SIZE)));
अक्षर recovj[PAGE_SIZE] __attribute__((aligned(PAGE_SIZE)));

अटल व्योम makedata(पूर्णांक start, पूर्णांक stop)
अणु
	पूर्णांक i, j;

	क्रम (i = start; i <= stop; i++) अणु
		क्रम (j = 0; j < PAGE_SIZE; j++)
			data[i][j] = अक्रम();

		dataptrs[i] = data[i];
	पूर्ण
पूर्ण

अटल अक्षर disk_type(पूर्णांक d)
अणु
	चयन (d) अणु
	हाल NDISKS-2:
		वापस 'P';
	हाल NDISKS-1:
		वापस 'Q';
	शेष:
		वापस 'D';
	पूर्ण
पूर्ण

अटल पूर्णांक test_disks(पूर्णांक i, पूर्णांक j)
अणु
	पूर्णांक erra, errb;

	स_रखो(recovi, 0xf0, PAGE_SIZE);
	स_रखो(recovj, 0xba, PAGE_SIZE);

	dataptrs[i] = recovi;
	dataptrs[j] = recovj;

	raid6_dual_recov(NDISKS, PAGE_SIZE, i, j, (व्योम **)&dataptrs);

	erra = स_भेद(data[i], recovi, PAGE_SIZE);
	errb = स_भेद(data[j], recovj, PAGE_SIZE);

	अगर (i < NDISKS-2 && j == NDISKS-1) अणु
		/* We करोn't implement the DQ failure scenario, since it's
		   equivalent to a RAID-5 failure (XOR, then recompute Q) */
		erra = errb = 0;
	पूर्ण अन्यथा अणु
		म_लिखो("algo=%-8s  faila=%3d(%c)  failb=%3d(%c)  %s\n",
		       raid6_call.name,
		       i, disk_type(i),
		       j, disk_type(j),
		       (!erra && !errb) ? "OK" :
		       !erra ? "ERRB" :
		       !errb ? "ERRA" : "ERRAB");
	पूर्ण

	dataptrs[i] = data[i];
	dataptrs[j] = data[j];

	वापस erra || errb;
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर *argv[])
अणु
	स्थिर काष्ठा raid6_calls *स्थिर *algo;
	स्थिर काष्ठा raid6_recov_calls *स्थिर *ra;
	पूर्णांक i, j, p1, p2;
	पूर्णांक err = 0;

	makedata(0, NDISKS-1);

	क्रम (ra = raid6_recov_algos; *ra; ra++) अणु
		अगर ((*ra)->valid  && !(*ra)->valid())
			जारी;

		raid6_2data_recov = (*ra)->data2;
		raid6_datap_recov = (*ra)->datap;

		म_लिखो("using recovery %s\n", (*ra)->name);

		क्रम (algo = raid6_algos; *algo; algo++) अणु
			अगर ((*algo)->valid && !(*algo)->valid())
				जारी;

			raid6_call = **algo;

			/* Nuke syndromes */
			स_रखो(data[NDISKS-2], 0xee, 2*PAGE_SIZE);

			/* Generate assumed good syndrome */
			raid6_call.gen_syndrome(NDISKS, PAGE_SIZE,
						(व्योम **)&dataptrs);

			क्रम (i = 0; i < NDISKS-1; i++)
				क्रम (j = i+1; j < NDISKS; j++)
					err += test_disks(i, j);

			अगर (!raid6_call.xor_syndrome)
				जारी;

			क्रम (p1 = 0; p1 < NDISKS-2; p1++)
				क्रम (p2 = p1; p2 < NDISKS-2; p2++) अणु

					/* Simulate rmw run */
					raid6_call.xor_syndrome(NDISKS, p1, p2, PAGE_SIZE,
								(व्योम **)&dataptrs);
					makedata(p1, p2);
					raid6_call.xor_syndrome(NDISKS, p1, p2, PAGE_SIZE,
                                                                (व्योम **)&dataptrs);

					क्रम (i = 0; i < NDISKS-1; i++)
						क्रम (j = i+1; j < NDISKS; j++)
							err += test_disks(i, j);
				पूर्ण

		पूर्ण
		म_लिखो("\n");
	पूर्ण

	म_लिखो("\n");
	/* Pick the best algorithm test */
	raid6_select_algo();

	अगर (err)
		म_लिखो("\n*** ERRORS FOUND ***\n");

	वापस err;
पूर्ण
