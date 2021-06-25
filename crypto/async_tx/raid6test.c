<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * asynchronous raid6 recovery self test
 * Copyright (c) 2009, Intel Corporation.
 *
 * based on drivers/md/raid6test/test.c:
 * 	Copyright 2002-2007 H. Peter Anvin
 */
#समावेश <linux/async_tx.h>
#समावेश <linux/gfp.h>
#समावेश <linux/mm.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/module.h>

#अघोषित pr
#घोषणा pr(fmt, args...) pr_info("raid6test: " fmt, ##args)

#घोषणा NDISKS 64 /* Including P and Q */

अटल काष्ठा page *dataptrs[NDISKS];
अचिन्हित पूर्णांक dataoffs[NDISKS];
अटल addr_conv_t addr_conv[NDISKS];
अटल काष्ठा page *data[NDISKS+3];
अटल काष्ठा page *spare;
अटल काष्ठा page *recovi;
अटल काष्ठा page *recovj;

अटल व्योम callback(व्योम *param)
अणु
	काष्ठा completion *cmp = param;

	complete(cmp);
पूर्ण

अटल व्योम makedata(पूर्णांक disks)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < disks; i++) अणु
		pअक्रमom_bytes(page_address(data[i]), PAGE_SIZE);
		dataptrs[i] = data[i];
		dataoffs[i] = 0;
	पूर्ण
पूर्ण

अटल अक्षर disk_type(पूर्णांक d, पूर्णांक disks)
अणु
	अगर (d == disks - 2)
		वापस 'P';
	अन्यथा अगर (d == disks - 1)
		वापस 'Q';
	अन्यथा
		वापस 'D';
पूर्ण

/* Recover two failed blocks. */
अटल व्योम raid6_dual_recov(पूर्णांक disks, माप_प्रकार bytes, पूर्णांक faila, पूर्णांक failb,
		काष्ठा page **ptrs, अचिन्हित पूर्णांक *offs)
अणु
	काष्ठा async_submit_ctl submit;
	काष्ठा completion cmp;
	काष्ठा dma_async_tx_descriptor *tx = शून्य;
	क्रमागत sum_check_flags result = ~0;

	अगर (faila > failb)
		swap(faila, failb);

	अगर (failb == disks-1) अणु
		अगर (faila == disks-2) अणु
			/* P+Q failure.  Just rebuild the syndrome. */
			init_async_submit(&submit, 0, शून्य, शून्य, शून्य, addr_conv);
			tx = async_gen_syndrome(ptrs, offs,
					disks, bytes, &submit);
		पूर्ण अन्यथा अणु
			काष्ठा page *blocks[NDISKS];
			काष्ठा page *dest;
			पूर्णांक count = 0;
			पूर्णांक i;

			BUG_ON(disks > NDISKS);

			/* data+Q failure.  Reस्थिरruct data from P,
			 * then rebuild syndrome
			 */
			क्रम (i = disks; i-- ; ) अणु
				अगर (i == faila || i == failb)
					जारी;
				blocks[count++] = ptrs[i];
			पूर्ण
			dest = ptrs[faila];
			init_async_submit(&submit, ASYNC_TX_XOR_ZERO_DST, शून्य,
					  शून्य, शून्य, addr_conv);
			tx = async_xor(dest, blocks, 0, count, bytes, &submit);

			init_async_submit(&submit, 0, tx, शून्य, शून्य, addr_conv);
			tx = async_gen_syndrome(ptrs, offs,
					disks, bytes, &submit);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (failb == disks-2) अणु
			/* data+P failure. */
			init_async_submit(&submit, 0, शून्य, शून्य, शून्य, addr_conv);
			tx = async_raid6_datap_recov(disks, bytes,
					faila, ptrs, offs, &submit);
		पूर्ण अन्यथा अणु
			/* data+data failure. */
			init_async_submit(&submit, 0, शून्य, शून्य, शून्य, addr_conv);
			tx = async_raid6_2data_recov(disks, bytes,
					faila, failb, ptrs, offs, &submit);
		पूर्ण
	पूर्ण
	init_completion(&cmp);
	init_async_submit(&submit, ASYNC_TX_ACK, tx, callback, &cmp, addr_conv);
	tx = async_syndrome_val(ptrs, offs,
			disks, bytes, &result, spare, 0, &submit);
	async_tx_issue_pending(tx);

	अगर (रुको_क्रम_completion_समयout(&cmp, msecs_to_jअगरfies(3000)) == 0)
		pr("%s: timeout! (faila: %d failb: %d disks: %d)\n",
		   __func__, faila, failb, disks);

	अगर (result != 0)
		pr("%s: validation failure! faila: %d failb: %d sum_check_flags: %x\n",
		   __func__, faila, failb, result);
पूर्ण

अटल पूर्णांक test_disks(पूर्णांक i, पूर्णांक j, पूर्णांक disks)
अणु
	पूर्णांक erra, errb;

	स_रखो(page_address(recovi), 0xf0, PAGE_SIZE);
	स_रखो(page_address(recovj), 0xba, PAGE_SIZE);

	dataptrs[i] = recovi;
	dataptrs[j] = recovj;

	raid6_dual_recov(disks, PAGE_SIZE, i, j, dataptrs, dataoffs);

	erra = स_भेद(page_address(data[i]), page_address(recovi), PAGE_SIZE);
	errb = स_भेद(page_address(data[j]), page_address(recovj), PAGE_SIZE);

	pr("%s(%d, %d): faila=%3d(%c)  failb=%3d(%c)  %s\n",
	   __func__, i, j, i, disk_type(i, disks), j, disk_type(j, disks),
	   (!erra && !errb) ? "OK" : !erra ? "ERRB" : !errb ? "ERRA" : "ERRAB");

	dataptrs[i] = data[i];
	dataptrs[j] = data[j];

	वापस erra || errb;
पूर्ण

अटल पूर्णांक test(पूर्णांक disks, पूर्णांक *tests)
अणु
	काष्ठा dma_async_tx_descriptor *tx;
	काष्ठा async_submit_ctl submit;
	काष्ठा completion cmp;
	पूर्णांक err = 0;
	पूर्णांक i, j;

	recovi = data[disks];
	recovj = data[disks+1];
	spare  = data[disks+2];

	makedata(disks);

	/* Nuke syndromes */
	स_रखो(page_address(data[disks-2]), 0xee, PAGE_SIZE);
	स_रखो(page_address(data[disks-1]), 0xee, PAGE_SIZE);

	/* Generate assumed good syndrome */
	init_completion(&cmp);
	init_async_submit(&submit, ASYNC_TX_ACK, शून्य, callback, &cmp, addr_conv);
	tx = async_gen_syndrome(dataptrs, dataoffs, disks, PAGE_SIZE, &submit);
	async_tx_issue_pending(tx);

	अगर (रुको_क्रम_completion_समयout(&cmp, msecs_to_jअगरfies(3000)) == 0) अणु
		pr("error: initial gen_syndrome(%d) timed out\n", disks);
		वापस 1;
	पूर्ण

	pr("testing the %d-disk case...\n", disks);
	क्रम (i = 0; i < disks-1; i++)
		क्रम (j = i+1; j < disks; j++) अणु
			(*tests)++;
			err += test_disks(i, j, disks);
		पूर्ण

	वापस err;
पूर्ण


अटल पूर्णांक raid6_test(व्योम)
अणु
	पूर्णांक err = 0;
	पूर्णांक tests = 0;
	पूर्णांक i;

	क्रम (i = 0; i < NDISKS+3; i++) अणु
		data[i] = alloc_page(GFP_KERNEL);
		अगर (!data[i]) अणु
			जबतक (i--)
				put_page(data[i]);
			वापस -ENOMEM;
		पूर्ण
	पूर्ण

	/* the 4-disk and 5-disk हालs are special क्रम the recovery code */
	अगर (NDISKS > 4)
		err += test(4, &tests);
	अगर (NDISKS > 5)
		err += test(5, &tests);
	/* the 11 and 12 disk हालs are special क्रम ioatdma (p-disabled
	 * q-continuation without extended descriptor)
	 */
	अगर (NDISKS > 12) अणु
		err += test(11, &tests);
		err += test(12, &tests);
	पूर्ण

	/* the 24 disk हाल is special क्रम ioatdma as it is the boudary poपूर्णांक
	 * at which it needs to चयन from 8-source ops to 16-source
	 * ops क्रम continuation (assumes DMA_HAS_PQ_CONTINUE is not set)
	 */
	अगर (NDISKS > 24)
		err += test(24, &tests);

	err += test(NDISKS, &tests);

	pr("\n");
	pr("complete (%d tests, %d failure%s)\n",
	   tests, err, err == 1 ? "" : "s");

	क्रम (i = 0; i < NDISKS+3; i++)
		put_page(data[i]);

	वापस 0;
पूर्ण

अटल व्योम raid6_test_निकास(व्योम)
अणु
पूर्ण

/* when compiled-in रुको क्रम drivers to load first (assumes dma drivers
 * are also compliled-in)
 */
late_initcall(raid6_test);
module_निकास(raid6_test_निकास);
MODULE_AUTHOR("Dan Williams <dan.j.williams@intel.com>");
MODULE_DESCRIPTION("asynchronous RAID-6 recovery self tests");
MODULE_LICENSE("GPL");
