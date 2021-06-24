<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Copyright 2007-2008 Pierre Ossman
 */

#समावेश <linux/mmc/core.h>
#समावेश <linux/mmc/card.h>
#समावेश <linux/mmc/host.h>
#समावेश <linux/mmc/mmc.h>
#समावेश <linux/slab.h>

#समावेश <linux/scatterlist.h>
#समावेश <linux/swap.h>		/* For nr_मुक्त_buffer_pages() */
#समावेश <linux/list.h>

#समावेश <linux/debugfs.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/module.h>

#समावेश "core.h"
#समावेश "card.h"
#समावेश "host.h"
#समावेश "bus.h"
#समावेश "mmc_ops.h"

#घोषणा RESULT_OK		0
#घोषणा RESULT_FAIL		1
#घोषणा RESULT_UNSUP_HOST	2
#घोषणा RESULT_UNSUP_CARD	3

#घोषणा BUFFER_ORDER		2
#घोषणा BUFFER_SIZE		(PAGE_SIZE << BUFFER_ORDER)

#घोषणा TEST_ALIGN_END		8

/*
 * Limit the test area size to the maximum MMC HC erase group size.  Note that
 * the maximum SD allocation unit size is just 4MiB.
 */
#घोषणा TEST_AREA_MAX_SIZE (128 * 1024 * 1024)

/**
 * काष्ठा mmc_test_pages - pages allocated by 'alloc_pages()'.
 * @page: first page in the allocation
 * @order: order of the number of pages allocated
 */
काष्ठा mmc_test_pages अणु
	काष्ठा page *page;
	अचिन्हित पूर्णांक order;
पूर्ण;

/**
 * काष्ठा mmc_test_mem - allocated memory.
 * @arr: array of allocations
 * @cnt: number of allocations
 */
काष्ठा mmc_test_mem अणु
	काष्ठा mmc_test_pages *arr;
	अचिन्हित पूर्णांक cnt;
पूर्ण;

/**
 * काष्ठा mmc_test_area - inक्रमmation क्रम perक्रमmance tests.
 * @max_sz: test area size (in bytes)
 * @dev_addr: address on card at which to करो perक्रमmance tests
 * @max_tfr: maximum transfer size allowed by driver (in bytes)
 * @max_segs: maximum segments allowed by driver in scatterlist @sg
 * @max_seg_sz: maximum segment size allowed by driver
 * @blocks: number of (512 byte) blocks currently mapped by @sg
 * @sg_len: length of currently mapped scatterlist @sg
 * @mem: allocated memory
 * @sg: scatterlist
 * @sg_areq: scatterlist क्रम non-blocking request
 */
काष्ठा mmc_test_area अणु
	अचिन्हित दीर्घ max_sz;
	अचिन्हित पूर्णांक dev_addr;
	अचिन्हित पूर्णांक max_tfr;
	अचिन्हित पूर्णांक max_segs;
	अचिन्हित पूर्णांक max_seg_sz;
	अचिन्हित पूर्णांक blocks;
	अचिन्हित पूर्णांक sg_len;
	काष्ठा mmc_test_mem *mem;
	काष्ठा scatterlist *sg;
	काष्ठा scatterlist *sg_areq;
पूर्ण;

/**
 * काष्ठा mmc_test_transfer_result - transfer results क्रम perक्रमmance tests.
 * @link: द्विगुन-linked list
 * @count: amount of group of sectors to check
 * @sectors: amount of sectors to check in one group
 * @ts: समय values of transfer
 * @rate: calculated transfer rate
 * @iops: I/O operations per second (बार 100)
 */
काष्ठा mmc_test_transfer_result अणु
	काष्ठा list_head link;
	अचिन्हित पूर्णांक count;
	अचिन्हित पूर्णांक sectors;
	काष्ठा बारpec64 ts;
	अचिन्हित पूर्णांक rate;
	अचिन्हित पूर्णांक iops;
पूर्ण;

/**
 * काष्ठा mmc_test_general_result - results क्रम tests.
 * @link: द्विगुन-linked list
 * @card: card under test
 * @testहाल: number of test हाल
 * @result: result of test run
 * @tr_lst: transfer measurements अगर any as mmc_test_transfer_result
 */
काष्ठा mmc_test_general_result अणु
	काष्ठा list_head link;
	काष्ठा mmc_card *card;
	पूर्णांक testहाल;
	पूर्णांक result;
	काष्ठा list_head tr_lst;
पूर्ण;

/**
 * काष्ठा mmc_test_dbgfs_file - debugfs related file.
 * @link: द्विगुन-linked list
 * @card: card under test
 * @file: file created under debugfs
 */
काष्ठा mmc_test_dbgfs_file अणु
	काष्ठा list_head link;
	काष्ठा mmc_card *card;
	काष्ठा dentry *file;
पूर्ण;

/**
 * काष्ठा mmc_test_card - test inक्रमmation.
 * @card: card under test
 * @scratch: transfer buffer
 * @buffer: transfer buffer
 * @highmem: buffer क्रम highmem tests
 * @area: inक्रमmation क्रम perक्रमmance tests
 * @gr: poपूर्णांकer to results of current testहाल
 */
काष्ठा mmc_test_card अणु
	काष्ठा mmc_card	*card;

	u8		scratch[BUFFER_SIZE];
	u8		*buffer;
#अगर_घोषित CONFIG_HIGHMEM
	काष्ठा page	*highmem;
#पूर्ण_अगर
	काष्ठा mmc_test_area		area;
	काष्ठा mmc_test_general_result	*gr;
पूर्ण;

क्रमागत mmc_test_prep_media अणु
	MMC_TEST_PREP_NONE = 0,
	MMC_TEST_PREP_WRITE_FULL = 1 << 0,
	MMC_TEST_PREP_ERASE = 1 << 1,
पूर्ण;

काष्ठा mmc_test_multiple_rw अणु
	अचिन्हित पूर्णांक *sg_len;
	अचिन्हित पूर्णांक *bs;
	अचिन्हित पूर्णांक len;
	अचिन्हित पूर्णांक size;
	bool करो_ग_लिखो;
	bool करो_nonblock_req;
	क्रमागत mmc_test_prep_media prepare;
पूर्ण;

/*******************************************************************/
/*  General helper functions                                       */
/*******************************************************************/

/*
 * Configure correct block size in card
 */
अटल पूर्णांक mmc_test_set_blksize(काष्ठा mmc_test_card *test, अचिन्हित size)
अणु
	वापस mmc_set_blocklen(test->card, size);
पूर्ण

अटल bool mmc_test_card_cmd23(काष्ठा mmc_card *card)
अणु
	वापस mmc_card_mmc(card) ||
	       (mmc_card_sd(card) && card->scr.cmds & SD_SCR_CMD23_SUPPORT);
पूर्ण

अटल व्योम mmc_test_prepare_sbc(काष्ठा mmc_test_card *test,
				 काष्ठा mmc_request *mrq, अचिन्हित पूर्णांक blocks)
अणु
	काष्ठा mmc_card *card = test->card;

	अगर (!mrq->sbc || !mmc_host_cmd23(card->host) ||
	    !mmc_test_card_cmd23(card) || !mmc_op_multi(mrq->cmd->opcode) ||
	    (card->quirks & MMC_QUIRK_BLK_NO_CMD23)) अणु
		mrq->sbc = शून्य;
		वापस;
	पूर्ण

	mrq->sbc->opcode = MMC_SET_BLOCK_COUNT;
	mrq->sbc->arg = blocks;
	mrq->sbc->flags = MMC_RSP_R1 | MMC_CMD_AC;
पूर्ण

/*
 * Fill in the mmc_request काष्ठाure given a set of transfer parameters.
 */
अटल व्योम mmc_test_prepare_mrq(काष्ठा mmc_test_card *test,
	काष्ठा mmc_request *mrq, काष्ठा scatterlist *sg, अचिन्हित sg_len,
	अचिन्हित dev_addr, अचिन्हित blocks, अचिन्हित blksz, पूर्णांक ग_लिखो)
अणु
	अगर (WARN_ON(!mrq || !mrq->cmd || !mrq->data || !mrq->stop))
		वापस;

	अगर (blocks > 1) अणु
		mrq->cmd->opcode = ग_लिखो ?
			MMC_WRITE_MULTIPLE_BLOCK : MMC_READ_MULTIPLE_BLOCK;
	पूर्ण अन्यथा अणु
		mrq->cmd->opcode = ग_लिखो ?
			MMC_WRITE_BLOCK : MMC_READ_SINGLE_BLOCK;
	पूर्ण

	mrq->cmd->arg = dev_addr;
	अगर (!mmc_card_blockaddr(test->card))
		mrq->cmd->arg <<= 9;

	mrq->cmd->flags = MMC_RSP_R1 | MMC_CMD_ADTC;

	अगर (blocks == 1)
		mrq->stop = शून्य;
	अन्यथा अणु
		mrq->stop->opcode = MMC_STOP_TRANSMISSION;
		mrq->stop->arg = 0;
		mrq->stop->flags = MMC_RSP_R1B | MMC_CMD_AC;
	पूर्ण

	mrq->data->blksz = blksz;
	mrq->data->blocks = blocks;
	mrq->data->flags = ग_लिखो ? MMC_DATA_WRITE : MMC_DATA_READ;
	mrq->data->sg = sg;
	mrq->data->sg_len = sg_len;

	mmc_test_prepare_sbc(test, mrq, blocks);

	mmc_set_data_समयout(mrq->data, test->card);
पूर्ण

अटल पूर्णांक mmc_test_busy(काष्ठा mmc_command *cmd)
अणु
	वापस !(cmd->resp[0] & R1_READY_FOR_DATA) ||
		(R1_CURRENT_STATE(cmd->resp[0]) == R1_STATE_PRG);
पूर्ण

/*
 * Wait क्रम the card to finish the busy state
 */
अटल पूर्णांक mmc_test_रुको_busy(काष्ठा mmc_test_card *test)
अणु
	पूर्णांक ret, busy;
	काष्ठा mmc_command cmd = अणुपूर्ण;

	busy = 0;
	करो अणु
		स_रखो(&cmd, 0, माप(काष्ठा mmc_command));

		cmd.opcode = MMC_SEND_STATUS;
		cmd.arg = test->card->rca << 16;
		cmd.flags = MMC_RSP_R1 | MMC_CMD_AC;

		ret = mmc_रुको_क्रम_cmd(test->card->host, &cmd, 0);
		अगर (ret)
			अवरोध;

		अगर (!busy && mmc_test_busy(&cmd)) अणु
			busy = 1;
			अगर (test->card->host->caps & MMC_CAP_WAIT_WHILE_BUSY)
				pr_info("%s: Warning: Host did not wait for busy state to end.\n",
					mmc_hostname(test->card->host));
		पूर्ण
	पूर्ण जबतक (mmc_test_busy(&cmd));

	वापस ret;
पूर्ण

/*
 * Transfer a single sector of kernel addressable data
 */
अटल पूर्णांक mmc_test_buffer_transfer(काष्ठा mmc_test_card *test,
	u8 *buffer, अचिन्हित addr, अचिन्हित blksz, पूर्णांक ग_लिखो)
अणु
	काष्ठा mmc_request mrq = अणुपूर्ण;
	काष्ठा mmc_command cmd = अणुपूर्ण;
	काष्ठा mmc_command stop = अणुपूर्ण;
	काष्ठा mmc_data data = अणुपूर्ण;

	काष्ठा scatterlist sg;

	mrq.cmd = &cmd;
	mrq.data = &data;
	mrq.stop = &stop;

	sg_init_one(&sg, buffer, blksz);

	mmc_test_prepare_mrq(test, &mrq, &sg, 1, addr, 1, blksz, ग_लिखो);

	mmc_रुको_क्रम_req(test->card->host, &mrq);

	अगर (cmd.error)
		वापस cmd.error;
	अगर (data.error)
		वापस data.error;

	वापस mmc_test_रुको_busy(test);
पूर्ण

अटल व्योम mmc_test_मुक्त_mem(काष्ठा mmc_test_mem *mem)
अणु
	अगर (!mem)
		वापस;
	जबतक (mem->cnt--)
		__मुक्त_pages(mem->arr[mem->cnt].page,
			     mem->arr[mem->cnt].order);
	kमुक्त(mem->arr);
	kमुक्त(mem);
पूर्ण

/*
 * Allocate a lot of memory, preferably max_sz but at least min_sz.  In हाल
 * there isn't much memory करो not exceed 1/16th total lowmem pages.  Also करो
 * not exceed a maximum number of segments and try not to make segments much
 * bigger than maximum segment size.
 */
अटल काष्ठा mmc_test_mem *mmc_test_alloc_mem(अचिन्हित दीर्घ min_sz,
					       अचिन्हित दीर्घ max_sz,
					       अचिन्हित पूर्णांक max_segs,
					       अचिन्हित पूर्णांक max_seg_sz)
अणु
	अचिन्हित दीर्घ max_page_cnt = DIV_ROUND_UP(max_sz, PAGE_SIZE);
	अचिन्हित दीर्घ min_page_cnt = DIV_ROUND_UP(min_sz, PAGE_SIZE);
	अचिन्हित दीर्घ max_seg_page_cnt = DIV_ROUND_UP(max_seg_sz, PAGE_SIZE);
	अचिन्हित दीर्घ page_cnt = 0;
	अचिन्हित दीर्घ limit = nr_मुक्त_buffer_pages() >> 4;
	काष्ठा mmc_test_mem *mem;

	अगर (max_page_cnt > limit)
		max_page_cnt = limit;
	अगर (min_page_cnt > max_page_cnt)
		min_page_cnt = max_page_cnt;

	अगर (max_seg_page_cnt > max_page_cnt)
		max_seg_page_cnt = max_page_cnt;

	अगर (max_segs > max_page_cnt)
		max_segs = max_page_cnt;

	mem = kzalloc(माप(*mem), GFP_KERNEL);
	अगर (!mem)
		वापस शून्य;

	mem->arr = kसुस्मृति(max_segs, माप(*mem->arr), GFP_KERNEL);
	अगर (!mem->arr)
		जाओ out_मुक्त;

	जबतक (max_page_cnt) अणु
		काष्ठा page *page;
		अचिन्हित पूर्णांक order;
		gfp_t flags = GFP_KERNEL | GFP_DMA | __GFP_NOWARN |
				__GFP_NORETRY;

		order = get_order(max_seg_page_cnt << PAGE_SHIFT);
		जबतक (1) अणु
			page = alloc_pages(flags, order);
			अगर (page || !order)
				अवरोध;
			order -= 1;
		पूर्ण
		अगर (!page) अणु
			अगर (page_cnt < min_page_cnt)
				जाओ out_मुक्त;
			अवरोध;
		पूर्ण
		mem->arr[mem->cnt].page = page;
		mem->arr[mem->cnt].order = order;
		mem->cnt += 1;
		अगर (max_page_cnt <= (1UL << order))
			अवरोध;
		max_page_cnt -= 1UL << order;
		page_cnt += 1UL << order;
		अगर (mem->cnt >= max_segs) अणु
			अगर (page_cnt < min_page_cnt)
				जाओ out_मुक्त;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस mem;

out_मुक्त:
	mmc_test_मुक्त_mem(mem);
	वापस शून्य;
पूर्ण

/*
 * Map memory पूर्णांकo a scatterlist.  Optionally allow the same memory to be
 * mapped more than once.
 */
अटल पूर्णांक mmc_test_map_sg(काष्ठा mmc_test_mem *mem, अचिन्हित दीर्घ size,
			   काष्ठा scatterlist *sglist, पूर्णांक repeat,
			   अचिन्हित पूर्णांक max_segs, अचिन्हित पूर्णांक max_seg_sz,
			   अचिन्हित पूर्णांक *sg_len, पूर्णांक min_sg_len)
अणु
	काष्ठा scatterlist *sg = शून्य;
	अचिन्हित पूर्णांक i;
	अचिन्हित दीर्घ sz = size;

	sg_init_table(sglist, max_segs);
	अगर (min_sg_len > max_segs)
		min_sg_len = max_segs;

	*sg_len = 0;
	करो अणु
		क्रम (i = 0; i < mem->cnt; i++) अणु
			अचिन्हित दीर्घ len = PAGE_SIZE << mem->arr[i].order;

			अगर (min_sg_len && (size / min_sg_len < len))
				len = ALIGN(size / min_sg_len, 512);
			अगर (len > sz)
				len = sz;
			अगर (len > max_seg_sz)
				len = max_seg_sz;
			अगर (sg)
				sg = sg_next(sg);
			अन्यथा
				sg = sglist;
			अगर (!sg)
				वापस -EINVAL;
			sg_set_page(sg, mem->arr[i].page, len, 0);
			sz -= len;
			*sg_len += 1;
			अगर (!sz)
				अवरोध;
		पूर्ण
	पूर्ण जबतक (sz && repeat);

	अगर (sz)
		वापस -EINVAL;

	अगर (sg)
		sg_mark_end(sg);

	वापस 0;
पूर्ण

/*
 * Map memory पूर्णांकo a scatterlist so that no pages are contiguous.  Allow the
 * same memory to be mapped more than once.
 */
अटल पूर्णांक mmc_test_map_sg_max_scatter(काष्ठा mmc_test_mem *mem,
				       अचिन्हित दीर्घ sz,
				       काष्ठा scatterlist *sglist,
				       अचिन्हित पूर्णांक max_segs,
				       अचिन्हित पूर्णांक max_seg_sz,
				       अचिन्हित पूर्णांक *sg_len)
अणु
	काष्ठा scatterlist *sg = शून्य;
	अचिन्हित पूर्णांक i = mem->cnt, cnt;
	अचिन्हित दीर्घ len;
	व्योम *base, *addr, *last_addr = शून्य;

	sg_init_table(sglist, max_segs);

	*sg_len = 0;
	जबतक (sz) अणु
		base = page_address(mem->arr[--i].page);
		cnt = 1 << mem->arr[i].order;
		जबतक (sz && cnt) अणु
			addr = base + PAGE_SIZE * --cnt;
			अगर (last_addr && last_addr + PAGE_SIZE == addr)
				जारी;
			last_addr = addr;
			len = PAGE_SIZE;
			अगर (len > max_seg_sz)
				len = max_seg_sz;
			अगर (len > sz)
				len = sz;
			अगर (sg)
				sg = sg_next(sg);
			अन्यथा
				sg = sglist;
			अगर (!sg)
				वापस -EINVAL;
			sg_set_page(sg, virt_to_page(addr), len, 0);
			sz -= len;
			*sg_len += 1;
		पूर्ण
		अगर (i == 0)
			i = mem->cnt;
	पूर्ण

	अगर (sg)
		sg_mark_end(sg);

	वापस 0;
पूर्ण

/*
 * Calculate transfer rate in bytes per second.
 */
अटल अचिन्हित पूर्णांक mmc_test_rate(uपूर्णांक64_t bytes, काष्ठा बारpec64 *ts)
अणु
	uपूर्णांक64_t ns;

	ns = बारpec64_to_ns(ts);
	bytes *= 1000000000;

	जबतक (ns > अच_पूर्णांक_उच्च) अणु
		bytes >>= 1;
		ns >>= 1;
	पूर्ण

	अगर (!ns)
		वापस 0;

	करो_भाग(bytes, (uपूर्णांक32_t)ns);

	वापस bytes;
पूर्ण

/*
 * Save transfer results क्रम future usage
 */
अटल व्योम mmc_test_save_transfer_result(काष्ठा mmc_test_card *test,
	अचिन्हित पूर्णांक count, अचिन्हित पूर्णांक sectors, काष्ठा बारpec64 ts,
	अचिन्हित पूर्णांक rate, अचिन्हित पूर्णांक iops)
अणु
	काष्ठा mmc_test_transfer_result *tr;

	अगर (!test->gr)
		वापस;

	tr = kदो_स्मृति(माप(*tr), GFP_KERNEL);
	अगर (!tr)
		वापस;

	tr->count = count;
	tr->sectors = sectors;
	tr->ts = ts;
	tr->rate = rate;
	tr->iops = iops;

	list_add_tail(&tr->link, &test->gr->tr_lst);
पूर्ण

/*
 * Prपूर्णांक the transfer rate.
 */
अटल व्योम mmc_test_prपूर्णांक_rate(काष्ठा mmc_test_card *test, uपूर्णांक64_t bytes,
				काष्ठा बारpec64 *ts1, काष्ठा बारpec64 *ts2)
अणु
	अचिन्हित पूर्णांक rate, iops, sectors = bytes >> 9;
	काष्ठा बारpec64 ts;

	ts = बारpec64_sub(*ts2, *ts1);

	rate = mmc_test_rate(bytes, &ts);
	iops = mmc_test_rate(100, &ts); /* I/O ops per sec x 100 */

	pr_info("%s: Transfer of %u sectors (%u%s KiB) took %llu.%09u "
			 "seconds (%u kB/s, %u KiB/s, %u.%02u IOPS)\n",
			 mmc_hostname(test->card->host), sectors, sectors >> 1,
			 (sectors & 1 ? ".5" : ""), (u64)ts.tv_sec,
			 (u32)ts.tv_nsec, rate / 1000, rate / 1024,
			 iops / 100, iops % 100);

	mmc_test_save_transfer_result(test, 1, sectors, ts, rate, iops);
पूर्ण

/*
 * Prपूर्णांक the average transfer rate.
 */
अटल व्योम mmc_test_prपूर्णांक_avg_rate(काष्ठा mmc_test_card *test, uपूर्णांक64_t bytes,
				    अचिन्हित पूर्णांक count, काष्ठा बारpec64 *ts1,
				    काष्ठा बारpec64 *ts2)
अणु
	अचिन्हित पूर्णांक rate, iops, sectors = bytes >> 9;
	uपूर्णांक64_t tot = bytes * count;
	काष्ठा बारpec64 ts;

	ts = बारpec64_sub(*ts2, *ts1);

	rate = mmc_test_rate(tot, &ts);
	iops = mmc_test_rate(count * 100, &ts); /* I/O ops per sec x 100 */

	pr_info("%s: Transfer of %u x %u sectors (%u x %u%s KiB) took "
			 "%llu.%09u seconds (%u kB/s, %u KiB/s, "
			 "%u.%02u IOPS, sg_len %d)\n",
			 mmc_hostname(test->card->host), count, sectors, count,
			 sectors >> 1, (sectors & 1 ? ".5" : ""),
			 (u64)ts.tv_sec, (u32)ts.tv_nsec,
			 rate / 1000, rate / 1024, iops / 100, iops % 100,
			 test->area.sg_len);

	mmc_test_save_transfer_result(test, count, sectors, ts, rate, iops);
पूर्ण

/*
 * Return the card size in sectors.
 */
अटल अचिन्हित पूर्णांक mmc_test_capacity(काष्ठा mmc_card *card)
अणु
	अगर (!mmc_card_sd(card) && mmc_card_blockaddr(card))
		वापस card->ext_csd.sectors;
	अन्यथा
		वापस card->csd.capacity << (card->csd.पढ़ो_blkbits - 9);
पूर्ण

/*******************************************************************/
/*  Test preparation and cleanup                                   */
/*******************************************************************/

/*
 * Fill the first couple of sectors of the card with known data
 * so that bad पढ़ोs/ग_लिखोs can be detected
 */
अटल पूर्णांक __mmc_test_prepare(काष्ठा mmc_test_card *test, पूर्णांक ग_लिखो, पूर्णांक val)
अणु
	पूर्णांक ret, i;

	ret = mmc_test_set_blksize(test, 512);
	अगर (ret)
		वापस ret;

	अगर (ग_लिखो)
		स_रखो(test->buffer, val, 512);
	अन्यथा अणु
		क्रम (i = 0; i < 512; i++)
			test->buffer[i] = i;
	पूर्ण

	क्रम (i = 0; i < BUFFER_SIZE / 512; i++) अणु
		ret = mmc_test_buffer_transfer(test, test->buffer, i, 512, 1);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mmc_test_prepare_ग_लिखो(काष्ठा mmc_test_card *test)
अणु
	वापस __mmc_test_prepare(test, 1, 0xDF);
पूर्ण

अटल पूर्णांक mmc_test_prepare_पढ़ो(काष्ठा mmc_test_card *test)
अणु
	वापस __mmc_test_prepare(test, 0, 0);
पूर्ण

अटल पूर्णांक mmc_test_cleanup(काष्ठा mmc_test_card *test)
अणु
	वापस __mmc_test_prepare(test, 1, 0);
पूर्ण

/*******************************************************************/
/*  Test execution helpers                                         */
/*******************************************************************/

/*
 * Modअगरies the mmc_request to perक्रमm the "short transfer" tests
 */
अटल व्योम mmc_test_prepare_broken_mrq(काष्ठा mmc_test_card *test,
	काष्ठा mmc_request *mrq, पूर्णांक ग_लिखो)
अणु
	अगर (WARN_ON(!mrq || !mrq->cmd || !mrq->data))
		वापस;

	अगर (mrq->data->blocks > 1) अणु
		mrq->cmd->opcode = ग_लिखो ?
			MMC_WRITE_BLOCK : MMC_READ_SINGLE_BLOCK;
		mrq->stop = शून्य;
	पूर्ण अन्यथा अणु
		mrq->cmd->opcode = MMC_SEND_STATUS;
		mrq->cmd->arg = test->card->rca << 16;
	पूर्ण
पूर्ण

/*
 * Checks that a normal transfer didn't have any errors
 */
अटल पूर्णांक mmc_test_check_result(काष्ठा mmc_test_card *test,
				 काष्ठा mmc_request *mrq)
अणु
	पूर्णांक ret;

	अगर (WARN_ON(!mrq || !mrq->cmd || !mrq->data))
		वापस -EINVAL;

	ret = 0;

	अगर (mrq->sbc && mrq->sbc->error)
		ret = mrq->sbc->error;
	अगर (!ret && mrq->cmd->error)
		ret = mrq->cmd->error;
	अगर (!ret && mrq->data->error)
		ret = mrq->data->error;
	अगर (!ret && mrq->stop && mrq->stop->error)
		ret = mrq->stop->error;
	अगर (!ret && mrq->data->bytes_xfered !=
		mrq->data->blocks * mrq->data->blksz)
		ret = RESULT_FAIL;

	अगर (ret == -EINVAL)
		ret = RESULT_UNSUP_HOST;

	वापस ret;
पूर्ण

/*
 * Checks that a "short transfer" behaved as expected
 */
अटल पूर्णांक mmc_test_check_broken_result(काष्ठा mmc_test_card *test,
	काष्ठा mmc_request *mrq)
अणु
	पूर्णांक ret;

	अगर (WARN_ON(!mrq || !mrq->cmd || !mrq->data))
		वापस -EINVAL;

	ret = 0;

	अगर (!ret && mrq->cmd->error)
		ret = mrq->cmd->error;
	अगर (!ret && mrq->data->error == 0)
		ret = RESULT_FAIL;
	अगर (!ret && mrq->data->error != -ETIMEDOUT)
		ret = mrq->data->error;
	अगर (!ret && mrq->stop && mrq->stop->error)
		ret = mrq->stop->error;
	अगर (mrq->data->blocks > 1) अणु
		अगर (!ret && mrq->data->bytes_xfered > mrq->data->blksz)
			ret = RESULT_FAIL;
	पूर्ण अन्यथा अणु
		अगर (!ret && mrq->data->bytes_xfered > 0)
			ret = RESULT_FAIL;
	पूर्ण

	अगर (ret == -EINVAL)
		ret = RESULT_UNSUP_HOST;

	वापस ret;
पूर्ण

काष्ठा mmc_test_req अणु
	काष्ठा mmc_request mrq;
	काष्ठा mmc_command sbc;
	काष्ठा mmc_command cmd;
	काष्ठा mmc_command stop;
	काष्ठा mmc_command status;
	काष्ठा mmc_data data;
पूर्ण;

/*
 * Tests nonblock transfer with certain parameters
 */
अटल व्योम mmc_test_req_reset(काष्ठा mmc_test_req *rq)
अणु
	स_रखो(rq, 0, माप(काष्ठा mmc_test_req));

	rq->mrq.cmd = &rq->cmd;
	rq->mrq.data = &rq->data;
	rq->mrq.stop = &rq->stop;
पूर्ण

अटल काष्ठा mmc_test_req *mmc_test_req_alloc(व्योम)
अणु
	काष्ठा mmc_test_req *rq = kदो_स्मृति(माप(*rq), GFP_KERNEL);

	अगर (rq)
		mmc_test_req_reset(rq);

	वापस rq;
पूर्ण

अटल व्योम mmc_test_रुको_करोne(काष्ठा mmc_request *mrq)
अणु
	complete(&mrq->completion);
पूर्ण

अटल पूर्णांक mmc_test_start_areq(काष्ठा mmc_test_card *test,
			       काष्ठा mmc_request *mrq,
			       काष्ठा mmc_request *prev_mrq)
अणु
	काष्ठा mmc_host *host = test->card->host;
	पूर्णांक err = 0;

	अगर (mrq) अणु
		init_completion(&mrq->completion);
		mrq->करोne = mmc_test_रुको_करोne;
		mmc_pre_req(host, mrq);
	पूर्ण

	अगर (prev_mrq) अणु
		रुको_क्रम_completion(&prev_mrq->completion);
		err = mmc_test_रुको_busy(test);
		अगर (!err)
			err = mmc_test_check_result(test, prev_mrq);
	पूर्ण

	अगर (!err && mrq) अणु
		err = mmc_start_request(host, mrq);
		अगर (err)
			mmc_retune_release(host);
	पूर्ण

	अगर (prev_mrq)
		mmc_post_req(host, prev_mrq, 0);

	अगर (err && mrq)
		mmc_post_req(host, mrq, err);

	वापस err;
पूर्ण

अटल पूर्णांक mmc_test_nonblock_transfer(काष्ठा mmc_test_card *test,
				      अचिन्हित पूर्णांक dev_addr, पूर्णांक ग_लिखो,
				      पूर्णांक count)
अणु
	काष्ठा mmc_test_req *rq1, *rq2;
	काष्ठा mmc_request *mrq, *prev_mrq;
	पूर्णांक i;
	पूर्णांक ret = RESULT_OK;
	काष्ठा mmc_test_area *t = &test->area;
	काष्ठा scatterlist *sg = t->sg;
	काष्ठा scatterlist *sg_areq = t->sg_areq;

	rq1 = mmc_test_req_alloc();
	rq2 = mmc_test_req_alloc();
	अगर (!rq1 || !rq2) अणु
		ret = RESULT_FAIL;
		जाओ err;
	पूर्ण

	mrq = &rq1->mrq;
	prev_mrq = शून्य;

	क्रम (i = 0; i < count; i++) अणु
		mmc_test_req_reset(container_of(mrq, काष्ठा mmc_test_req, mrq));
		mmc_test_prepare_mrq(test, mrq, sg, t->sg_len, dev_addr,
				     t->blocks, 512, ग_लिखो);
		ret = mmc_test_start_areq(test, mrq, prev_mrq);
		अगर (ret)
			जाओ err;

		अगर (!prev_mrq)
			prev_mrq = &rq2->mrq;

		swap(mrq, prev_mrq);
		swap(sg, sg_areq);
		dev_addr += t->blocks;
	पूर्ण

	ret = mmc_test_start_areq(test, शून्य, prev_mrq);
err:
	kमुक्त(rq1);
	kमुक्त(rq2);
	वापस ret;
पूर्ण

/*
 * Tests a basic transfer with certain parameters
 */
अटल पूर्णांक mmc_test_simple_transfer(काष्ठा mmc_test_card *test,
	काष्ठा scatterlist *sg, अचिन्हित sg_len, अचिन्हित dev_addr,
	अचिन्हित blocks, अचिन्हित blksz, पूर्णांक ग_लिखो)
अणु
	काष्ठा mmc_request mrq = अणुपूर्ण;
	काष्ठा mmc_command cmd = अणुपूर्ण;
	काष्ठा mmc_command stop = अणुपूर्ण;
	काष्ठा mmc_data data = अणुपूर्ण;

	mrq.cmd = &cmd;
	mrq.data = &data;
	mrq.stop = &stop;

	mmc_test_prepare_mrq(test, &mrq, sg, sg_len, dev_addr,
		blocks, blksz, ग_लिखो);

	mmc_रुको_क्रम_req(test->card->host, &mrq);

	mmc_test_रुको_busy(test);

	वापस mmc_test_check_result(test, &mrq);
पूर्ण

/*
 * Tests a transfer where the card will fail completely or partly
 */
अटल पूर्णांक mmc_test_broken_transfer(काष्ठा mmc_test_card *test,
	अचिन्हित blocks, अचिन्हित blksz, पूर्णांक ग_लिखो)
अणु
	काष्ठा mmc_request mrq = अणुपूर्ण;
	काष्ठा mmc_command cmd = अणुपूर्ण;
	काष्ठा mmc_command stop = अणुपूर्ण;
	काष्ठा mmc_data data = अणुपूर्ण;

	काष्ठा scatterlist sg;

	mrq.cmd = &cmd;
	mrq.data = &data;
	mrq.stop = &stop;

	sg_init_one(&sg, test->buffer, blocks * blksz);

	mmc_test_prepare_mrq(test, &mrq, &sg, 1, 0, blocks, blksz, ग_लिखो);
	mmc_test_prepare_broken_mrq(test, &mrq, ग_लिखो);

	mmc_रुको_क्रम_req(test->card->host, &mrq);

	mmc_test_रुको_busy(test);

	वापस mmc_test_check_broken_result(test, &mrq);
पूर्ण

/*
 * Does a complete transfer test where data is also validated
 *
 * Note: mmc_test_prepare() must have been करोne beक्रमe this call
 */
अटल पूर्णांक mmc_test_transfer(काष्ठा mmc_test_card *test,
	काष्ठा scatterlist *sg, अचिन्हित sg_len, अचिन्हित dev_addr,
	अचिन्हित blocks, अचिन्हित blksz, पूर्णांक ग_लिखो)
अणु
	पूर्णांक ret, i;
	अचिन्हित दीर्घ flags;

	अगर (ग_लिखो) अणु
		क्रम (i = 0; i < blocks * blksz; i++)
			test->scratch[i] = i;
	पूर्ण अन्यथा अणु
		स_रखो(test->scratch, 0, BUFFER_SIZE);
	पूर्ण
	local_irq_save(flags);
	sg_copy_from_buffer(sg, sg_len, test->scratch, BUFFER_SIZE);
	local_irq_restore(flags);

	ret = mmc_test_set_blksize(test, blksz);
	अगर (ret)
		वापस ret;

	ret = mmc_test_simple_transfer(test, sg, sg_len, dev_addr,
		blocks, blksz, ग_लिखो);
	अगर (ret)
		वापस ret;

	अगर (ग_लिखो) अणु
		पूर्णांक sectors;

		ret = mmc_test_set_blksize(test, 512);
		अगर (ret)
			वापस ret;

		sectors = (blocks * blksz + 511) / 512;
		अगर ((sectors * 512) == (blocks * blksz))
			sectors++;

		अगर ((sectors * 512) > BUFFER_SIZE)
			वापस -EINVAL;

		स_रखो(test->buffer, 0, sectors * 512);

		क्रम (i = 0; i < sectors; i++) अणु
			ret = mmc_test_buffer_transfer(test,
				test->buffer + i * 512,
				dev_addr + i, 512, 0);
			अगर (ret)
				वापस ret;
		पूर्ण

		क्रम (i = 0; i < blocks * blksz; i++) अणु
			अगर (test->buffer[i] != (u8)i)
				वापस RESULT_FAIL;
		पूर्ण

		क्रम (; i < sectors * 512; i++) अणु
			अगर (test->buffer[i] != 0xDF)
				वापस RESULT_FAIL;
		पूर्ण
	पूर्ण अन्यथा अणु
		local_irq_save(flags);
		sg_copy_to_buffer(sg, sg_len, test->scratch, BUFFER_SIZE);
		local_irq_restore(flags);
		क्रम (i = 0; i < blocks * blksz; i++) अणु
			अगर (test->scratch[i] != (u8)i)
				वापस RESULT_FAIL;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/*******************************************************************/
/*  Tests                                                          */
/*******************************************************************/

काष्ठा mmc_test_हाल अणु
	स्थिर अक्षर *name;

	पूर्णांक (*prepare)(काष्ठा mmc_test_card *);
	पूर्णांक (*run)(काष्ठा mmc_test_card *);
	पूर्णांक (*cleanup)(काष्ठा mmc_test_card *);
पूर्ण;

अटल पूर्णांक mmc_test_basic_ग_लिखो(काष्ठा mmc_test_card *test)
अणु
	पूर्णांक ret;
	काष्ठा scatterlist sg;

	ret = mmc_test_set_blksize(test, 512);
	अगर (ret)
		वापस ret;

	sg_init_one(&sg, test->buffer, 512);

	वापस mmc_test_simple_transfer(test, &sg, 1, 0, 1, 512, 1);
पूर्ण

अटल पूर्णांक mmc_test_basic_पढ़ो(काष्ठा mmc_test_card *test)
अणु
	पूर्णांक ret;
	काष्ठा scatterlist sg;

	ret = mmc_test_set_blksize(test, 512);
	अगर (ret)
		वापस ret;

	sg_init_one(&sg, test->buffer, 512);

	वापस mmc_test_simple_transfer(test, &sg, 1, 0, 1, 512, 0);
पूर्ण

अटल पूर्णांक mmc_test_verअगरy_ग_लिखो(काष्ठा mmc_test_card *test)
अणु
	काष्ठा scatterlist sg;

	sg_init_one(&sg, test->buffer, 512);

	वापस mmc_test_transfer(test, &sg, 1, 0, 1, 512, 1);
पूर्ण

अटल पूर्णांक mmc_test_verअगरy_पढ़ो(काष्ठा mmc_test_card *test)
अणु
	काष्ठा scatterlist sg;

	sg_init_one(&sg, test->buffer, 512);

	वापस mmc_test_transfer(test, &sg, 1, 0, 1, 512, 0);
पूर्ण

अटल पूर्णांक mmc_test_multi_ग_लिखो(काष्ठा mmc_test_card *test)
अणु
	अचिन्हित पूर्णांक size;
	काष्ठा scatterlist sg;

	अगर (test->card->host->max_blk_count == 1)
		वापस RESULT_UNSUP_HOST;

	size = PAGE_SIZE * 2;
	size = min(size, test->card->host->max_req_size);
	size = min(size, test->card->host->max_seg_size);
	size = min(size, test->card->host->max_blk_count * 512);

	अगर (size < 1024)
		वापस RESULT_UNSUP_HOST;

	sg_init_one(&sg, test->buffer, size);

	वापस mmc_test_transfer(test, &sg, 1, 0, size / 512, 512, 1);
पूर्ण

अटल पूर्णांक mmc_test_multi_पढ़ो(काष्ठा mmc_test_card *test)
अणु
	अचिन्हित पूर्णांक size;
	काष्ठा scatterlist sg;

	अगर (test->card->host->max_blk_count == 1)
		वापस RESULT_UNSUP_HOST;

	size = PAGE_SIZE * 2;
	size = min(size, test->card->host->max_req_size);
	size = min(size, test->card->host->max_seg_size);
	size = min(size, test->card->host->max_blk_count * 512);

	अगर (size < 1024)
		वापस RESULT_UNSUP_HOST;

	sg_init_one(&sg, test->buffer, size);

	वापस mmc_test_transfer(test, &sg, 1, 0, size / 512, 512, 0);
पूर्ण

अटल पूर्णांक mmc_test_घात2_ग_लिखो(काष्ठा mmc_test_card *test)
अणु
	पूर्णांक ret, i;
	काष्ठा scatterlist sg;

	अगर (!test->card->csd.ग_लिखो_partial)
		वापस RESULT_UNSUP_CARD;

	क्रम (i = 1; i < 512; i <<= 1) अणु
		sg_init_one(&sg, test->buffer, i);
		ret = mmc_test_transfer(test, &sg, 1, 0, 1, i, 1);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mmc_test_घात2_पढ़ो(काष्ठा mmc_test_card *test)
अणु
	पूर्णांक ret, i;
	काष्ठा scatterlist sg;

	अगर (!test->card->csd.पढ़ो_partial)
		वापस RESULT_UNSUP_CARD;

	क्रम (i = 1; i < 512; i <<= 1) अणु
		sg_init_one(&sg, test->buffer, i);
		ret = mmc_test_transfer(test, &sg, 1, 0, 1, i, 0);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mmc_test_weird_ग_लिखो(काष्ठा mmc_test_card *test)
अणु
	पूर्णांक ret, i;
	काष्ठा scatterlist sg;

	अगर (!test->card->csd.ग_लिखो_partial)
		वापस RESULT_UNSUP_CARD;

	क्रम (i = 3; i < 512; i += 7) अणु
		sg_init_one(&sg, test->buffer, i);
		ret = mmc_test_transfer(test, &sg, 1, 0, 1, i, 1);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mmc_test_weird_पढ़ो(काष्ठा mmc_test_card *test)
अणु
	पूर्णांक ret, i;
	काष्ठा scatterlist sg;

	अगर (!test->card->csd.पढ़ो_partial)
		वापस RESULT_UNSUP_CARD;

	क्रम (i = 3; i < 512; i += 7) अणु
		sg_init_one(&sg, test->buffer, i);
		ret = mmc_test_transfer(test, &sg, 1, 0, 1, i, 0);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mmc_test_align_ग_लिखो(काष्ठा mmc_test_card *test)
अणु
	पूर्णांक ret, i;
	काष्ठा scatterlist sg;

	क्रम (i = 1; i < TEST_ALIGN_END; i++) अणु
		sg_init_one(&sg, test->buffer + i, 512);
		ret = mmc_test_transfer(test, &sg, 1, 0, 1, 512, 1);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mmc_test_align_पढ़ो(काष्ठा mmc_test_card *test)
अणु
	पूर्णांक ret, i;
	काष्ठा scatterlist sg;

	क्रम (i = 1; i < TEST_ALIGN_END; i++) अणु
		sg_init_one(&sg, test->buffer + i, 512);
		ret = mmc_test_transfer(test, &sg, 1, 0, 1, 512, 0);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mmc_test_align_multi_ग_लिखो(काष्ठा mmc_test_card *test)
अणु
	पूर्णांक ret, i;
	अचिन्हित पूर्णांक size;
	काष्ठा scatterlist sg;

	अगर (test->card->host->max_blk_count == 1)
		वापस RESULT_UNSUP_HOST;

	size = PAGE_SIZE * 2;
	size = min(size, test->card->host->max_req_size);
	size = min(size, test->card->host->max_seg_size);
	size = min(size, test->card->host->max_blk_count * 512);

	अगर (size < 1024)
		वापस RESULT_UNSUP_HOST;

	क्रम (i = 1; i < TEST_ALIGN_END; i++) अणु
		sg_init_one(&sg, test->buffer + i, size);
		ret = mmc_test_transfer(test, &sg, 1, 0, size / 512, 512, 1);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mmc_test_align_multi_पढ़ो(काष्ठा mmc_test_card *test)
अणु
	पूर्णांक ret, i;
	अचिन्हित पूर्णांक size;
	काष्ठा scatterlist sg;

	अगर (test->card->host->max_blk_count == 1)
		वापस RESULT_UNSUP_HOST;

	size = PAGE_SIZE * 2;
	size = min(size, test->card->host->max_req_size);
	size = min(size, test->card->host->max_seg_size);
	size = min(size, test->card->host->max_blk_count * 512);

	अगर (size < 1024)
		वापस RESULT_UNSUP_HOST;

	क्रम (i = 1; i < TEST_ALIGN_END; i++) अणु
		sg_init_one(&sg, test->buffer + i, size);
		ret = mmc_test_transfer(test, &sg, 1, 0, size / 512, 512, 0);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mmc_test_xfersize_ग_लिखो(काष्ठा mmc_test_card *test)
अणु
	पूर्णांक ret;

	ret = mmc_test_set_blksize(test, 512);
	अगर (ret)
		वापस ret;

	वापस mmc_test_broken_transfer(test, 1, 512, 1);
पूर्ण

अटल पूर्णांक mmc_test_xfersize_पढ़ो(काष्ठा mmc_test_card *test)
अणु
	पूर्णांक ret;

	ret = mmc_test_set_blksize(test, 512);
	अगर (ret)
		वापस ret;

	वापस mmc_test_broken_transfer(test, 1, 512, 0);
पूर्ण

अटल पूर्णांक mmc_test_multi_xfersize_ग_लिखो(काष्ठा mmc_test_card *test)
अणु
	पूर्णांक ret;

	अगर (test->card->host->max_blk_count == 1)
		वापस RESULT_UNSUP_HOST;

	ret = mmc_test_set_blksize(test, 512);
	अगर (ret)
		वापस ret;

	वापस mmc_test_broken_transfer(test, 2, 512, 1);
पूर्ण

अटल पूर्णांक mmc_test_multi_xfersize_पढ़ो(काष्ठा mmc_test_card *test)
अणु
	पूर्णांक ret;

	अगर (test->card->host->max_blk_count == 1)
		वापस RESULT_UNSUP_HOST;

	ret = mmc_test_set_blksize(test, 512);
	अगर (ret)
		वापस ret;

	वापस mmc_test_broken_transfer(test, 2, 512, 0);
पूर्ण

#अगर_घोषित CONFIG_HIGHMEM

अटल पूर्णांक mmc_test_ग_लिखो_high(काष्ठा mmc_test_card *test)
अणु
	काष्ठा scatterlist sg;

	sg_init_table(&sg, 1);
	sg_set_page(&sg, test->highmem, 512, 0);

	वापस mmc_test_transfer(test, &sg, 1, 0, 1, 512, 1);
पूर्ण

अटल पूर्णांक mmc_test_पढ़ो_high(काष्ठा mmc_test_card *test)
अणु
	काष्ठा scatterlist sg;

	sg_init_table(&sg, 1);
	sg_set_page(&sg, test->highmem, 512, 0);

	वापस mmc_test_transfer(test, &sg, 1, 0, 1, 512, 0);
पूर्ण

अटल पूर्णांक mmc_test_multi_ग_लिखो_high(काष्ठा mmc_test_card *test)
अणु
	अचिन्हित पूर्णांक size;
	काष्ठा scatterlist sg;

	अगर (test->card->host->max_blk_count == 1)
		वापस RESULT_UNSUP_HOST;

	size = PAGE_SIZE * 2;
	size = min(size, test->card->host->max_req_size);
	size = min(size, test->card->host->max_seg_size);
	size = min(size, test->card->host->max_blk_count * 512);

	अगर (size < 1024)
		वापस RESULT_UNSUP_HOST;

	sg_init_table(&sg, 1);
	sg_set_page(&sg, test->highmem, size, 0);

	वापस mmc_test_transfer(test, &sg, 1, 0, size / 512, 512, 1);
पूर्ण

अटल पूर्णांक mmc_test_multi_पढ़ो_high(काष्ठा mmc_test_card *test)
अणु
	अचिन्हित पूर्णांक size;
	काष्ठा scatterlist sg;

	अगर (test->card->host->max_blk_count == 1)
		वापस RESULT_UNSUP_HOST;

	size = PAGE_SIZE * 2;
	size = min(size, test->card->host->max_req_size);
	size = min(size, test->card->host->max_seg_size);
	size = min(size, test->card->host->max_blk_count * 512);

	अगर (size < 1024)
		वापस RESULT_UNSUP_HOST;

	sg_init_table(&sg, 1);
	sg_set_page(&sg, test->highmem, size, 0);

	वापस mmc_test_transfer(test, &sg, 1, 0, size / 512, 512, 0);
पूर्ण

#अन्यथा

अटल पूर्णांक mmc_test_no_highmem(काष्ठा mmc_test_card *test)
अणु
	pr_info("%s: Highmem not configured - test skipped\n",
	       mmc_hostname(test->card->host));
	वापस 0;
पूर्ण

#पूर्ण_अगर /* CONFIG_HIGHMEM */

/*
 * Map sz bytes so that it can be transferred.
 */
अटल पूर्णांक mmc_test_area_map(काष्ठा mmc_test_card *test, अचिन्हित दीर्घ sz,
			     पूर्णांक max_scatter, पूर्णांक min_sg_len, bool nonblock)
अणु
	काष्ठा mmc_test_area *t = &test->area;
	पूर्णांक err;
	अचिन्हित पूर्णांक sg_len = 0;

	t->blocks = sz >> 9;

	अगर (max_scatter) अणु
		err = mmc_test_map_sg_max_scatter(t->mem, sz, t->sg,
						  t->max_segs, t->max_seg_sz,
				       &t->sg_len);
	पूर्ण अन्यथा अणु
		err = mmc_test_map_sg(t->mem, sz, t->sg, 1, t->max_segs,
				      t->max_seg_sz, &t->sg_len, min_sg_len);
	पूर्ण

	अगर (err || !nonblock)
		जाओ err;

	अगर (max_scatter) अणु
		err = mmc_test_map_sg_max_scatter(t->mem, sz, t->sg_areq,
						  t->max_segs, t->max_seg_sz,
						  &sg_len);
	पूर्ण अन्यथा अणु
		err = mmc_test_map_sg(t->mem, sz, t->sg_areq, 1, t->max_segs,
				      t->max_seg_sz, &sg_len, min_sg_len);
	पूर्ण
	अगर (!err && sg_len != t->sg_len)
		err = -EINVAL;

err:
	अगर (err)
		pr_info("%s: Failed to map sg list\n",
		       mmc_hostname(test->card->host));
	वापस err;
पूर्ण

/*
 * Transfer bytes mapped by mmc_test_area_map().
 */
अटल पूर्णांक mmc_test_area_transfer(काष्ठा mmc_test_card *test,
				  अचिन्हित पूर्णांक dev_addr, पूर्णांक ग_लिखो)
अणु
	काष्ठा mmc_test_area *t = &test->area;

	वापस mmc_test_simple_transfer(test, t->sg, t->sg_len, dev_addr,
					t->blocks, 512, ग_लिखो);
पूर्ण

/*
 * Map and transfer bytes क्रम multiple transfers.
 */
अटल पूर्णांक mmc_test_area_io_seq(काष्ठा mmc_test_card *test, अचिन्हित दीर्घ sz,
				अचिन्हित पूर्णांक dev_addr, पूर्णांक ग_लिखो,
				पूर्णांक max_scatter, पूर्णांक समयd, पूर्णांक count,
				bool nonblock, पूर्णांक min_sg_len)
अणु
	काष्ठा बारpec64 ts1, ts2;
	पूर्णांक ret = 0;
	पूर्णांक i;

	/*
	 * In the हाल of a maximally scattered transfer, the maximum transfer
	 * size is further limited by using PAGE_SIZE segments.
	 */
	अगर (max_scatter) अणु
		काष्ठा mmc_test_area *t = &test->area;
		अचिन्हित दीर्घ max_tfr;

		अगर (t->max_seg_sz >= PAGE_SIZE)
			max_tfr = t->max_segs * PAGE_SIZE;
		अन्यथा
			max_tfr = t->max_segs * t->max_seg_sz;
		अगर (sz > max_tfr)
			sz = max_tfr;
	पूर्ण

	ret = mmc_test_area_map(test, sz, max_scatter, min_sg_len, nonblock);
	अगर (ret)
		वापस ret;

	अगर (समयd)
		kसमय_get_ts64(&ts1);
	अगर (nonblock)
		ret = mmc_test_nonblock_transfer(test, dev_addr, ग_लिखो, count);
	अन्यथा
		क्रम (i = 0; i < count && ret == 0; i++) अणु
			ret = mmc_test_area_transfer(test, dev_addr, ग_लिखो);
			dev_addr += sz >> 9;
		पूर्ण

	अगर (ret)
		वापस ret;

	अगर (समयd)
		kसमय_get_ts64(&ts2);

	अगर (समयd)
		mmc_test_prपूर्णांक_avg_rate(test, sz, count, &ts1, &ts2);

	वापस 0;
पूर्ण

अटल पूर्णांक mmc_test_area_io(काष्ठा mmc_test_card *test, अचिन्हित दीर्घ sz,
			    अचिन्हित पूर्णांक dev_addr, पूर्णांक ग_लिखो, पूर्णांक max_scatter,
			    पूर्णांक समयd)
अणु
	वापस mmc_test_area_io_seq(test, sz, dev_addr, ग_लिखो, max_scatter,
				    समयd, 1, false, 0);
पूर्ण

/*
 * Write the test area entirely.
 */
अटल पूर्णांक mmc_test_area_fill(काष्ठा mmc_test_card *test)
अणु
	काष्ठा mmc_test_area *t = &test->area;

	वापस mmc_test_area_io(test, t->max_tfr, t->dev_addr, 1, 0, 0);
पूर्ण

/*
 * Erase the test area entirely.
 */
अटल पूर्णांक mmc_test_area_erase(काष्ठा mmc_test_card *test)
अणु
	काष्ठा mmc_test_area *t = &test->area;

	अगर (!mmc_can_erase(test->card))
		वापस 0;

	वापस mmc_erase(test->card, t->dev_addr, t->max_sz >> 9,
			 MMC_ERASE_ARG);
पूर्ण

/*
 * Cleanup काष्ठा mmc_test_area.
 */
अटल पूर्णांक mmc_test_area_cleanup(काष्ठा mmc_test_card *test)
अणु
	काष्ठा mmc_test_area *t = &test->area;

	kमुक्त(t->sg);
	kमुक्त(t->sg_areq);
	mmc_test_मुक्त_mem(t->mem);

	वापस 0;
पूर्ण

/*
 * Initialize an area क्रम testing large transfers.  The test area is set to the
 * middle of the card because cards may have dअगरferent अक्षरacteristics at the
 * front (क्रम FAT file प्रणाली optimization).  Optionally, the area is erased
 * (अगर the card supports it) which may improve ग_लिखो perक्रमmance.  Optionally,
 * the area is filled with data क्रम subsequent पढ़ो tests.
 */
अटल पूर्णांक mmc_test_area_init(काष्ठा mmc_test_card *test, पूर्णांक erase, पूर्णांक fill)
अणु
	काष्ठा mmc_test_area *t = &test->area;
	अचिन्हित दीर्घ min_sz = 64 * 1024, sz;
	पूर्णांक ret;

	ret = mmc_test_set_blksize(test, 512);
	अगर (ret)
		वापस ret;

	/* Make the test area size about 4MiB */
	sz = (अचिन्हित दीर्घ)test->card->pref_erase << 9;
	t->max_sz = sz;
	जबतक (t->max_sz < 4 * 1024 * 1024)
		t->max_sz += sz;
	जबतक (t->max_sz > TEST_AREA_MAX_SIZE && t->max_sz > sz)
		t->max_sz -= sz;

	t->max_segs = test->card->host->max_segs;
	t->max_seg_sz = test->card->host->max_seg_size;
	t->max_seg_sz -= t->max_seg_sz % 512;

	t->max_tfr = t->max_sz;
	अगर (t->max_tfr >> 9 > test->card->host->max_blk_count)
		t->max_tfr = test->card->host->max_blk_count << 9;
	अगर (t->max_tfr > test->card->host->max_req_size)
		t->max_tfr = test->card->host->max_req_size;
	अगर (t->max_tfr / t->max_seg_sz > t->max_segs)
		t->max_tfr = t->max_segs * t->max_seg_sz;

	/*
	 * Try to allocate enough memory क्रम a max. sized transfer.  Less is OK
	 * because the same memory can be mapped पूर्णांकo the scatterlist more than
	 * once.  Also, take पूर्णांकo account the limits imposed on scatterlist
	 * segments by the host driver.
	 */
	t->mem = mmc_test_alloc_mem(min_sz, t->max_tfr, t->max_segs,
				    t->max_seg_sz);
	अगर (!t->mem)
		वापस -ENOMEM;

	t->sg = kदो_स्मृति_array(t->max_segs, माप(*t->sg), GFP_KERNEL);
	अगर (!t->sg) अणु
		ret = -ENOMEM;
		जाओ out_मुक्त;
	पूर्ण

	t->sg_areq = kदो_स्मृति_array(t->max_segs, माप(*t->sg_areq),
				   GFP_KERNEL);
	अगर (!t->sg_areq) अणु
		ret = -ENOMEM;
		जाओ out_मुक्त;
	पूर्ण

	t->dev_addr = mmc_test_capacity(test->card) / 2;
	t->dev_addr -= t->dev_addr % (t->max_sz >> 9);

	अगर (erase) अणु
		ret = mmc_test_area_erase(test);
		अगर (ret)
			जाओ out_मुक्त;
	पूर्ण

	अगर (fill) अणु
		ret = mmc_test_area_fill(test);
		अगर (ret)
			जाओ out_मुक्त;
	पूर्ण

	वापस 0;

out_मुक्त:
	mmc_test_area_cleanup(test);
	वापस ret;
पूर्ण

/*
 * Prepare क्रम large transfers.  Do not erase the test area.
 */
अटल पूर्णांक mmc_test_area_prepare(काष्ठा mmc_test_card *test)
अणु
	वापस mmc_test_area_init(test, 0, 0);
पूर्ण

/*
 * Prepare क्रम large transfers.  Do erase the test area.
 */
अटल पूर्णांक mmc_test_area_prepare_erase(काष्ठा mmc_test_card *test)
अणु
	वापस mmc_test_area_init(test, 1, 0);
पूर्ण

/*
 * Prepare क्रम large transfers.  Erase and fill the test area.
 */
अटल पूर्णांक mmc_test_area_prepare_fill(काष्ठा mmc_test_card *test)
अणु
	वापस mmc_test_area_init(test, 1, 1);
पूर्ण

/*
 * Test best-हाल perक्रमmance.  Best-हाल perक्रमmance is expected from
 * a single large transfer.
 *
 * An additional option (max_scatter) allows the measurement of the same
 * transfer but with no contiguous pages in the scatter list.  This tests
 * the efficiency of DMA to handle scattered pages.
 */
अटल पूर्णांक mmc_test_best_perक्रमmance(काष्ठा mmc_test_card *test, पूर्णांक ग_लिखो,
				     पूर्णांक max_scatter)
अणु
	काष्ठा mmc_test_area *t = &test->area;

	वापस mmc_test_area_io(test, t->max_tfr, t->dev_addr, ग_लिखो,
				max_scatter, 1);
पूर्ण

/*
 * Best-हाल पढ़ो perक्रमmance.
 */
अटल पूर्णांक mmc_test_best_पढ़ो_perक्रमmance(काष्ठा mmc_test_card *test)
अणु
	वापस mmc_test_best_perक्रमmance(test, 0, 0);
पूर्ण

/*
 * Best-हाल ग_लिखो perक्रमmance.
 */
अटल पूर्णांक mmc_test_best_ग_लिखो_perक्रमmance(काष्ठा mmc_test_card *test)
अणु
	वापस mmc_test_best_perक्रमmance(test, 1, 0);
पूर्ण

/*
 * Best-हाल पढ़ो perक्रमmance पूर्णांकo scattered pages.
 */
अटल पूर्णांक mmc_test_best_पढ़ो_perf_max_scatter(काष्ठा mmc_test_card *test)
अणु
	वापस mmc_test_best_perक्रमmance(test, 0, 1);
पूर्ण

/*
 * Best-हाल ग_लिखो perक्रमmance from scattered pages.
 */
अटल पूर्णांक mmc_test_best_ग_लिखो_perf_max_scatter(काष्ठा mmc_test_card *test)
अणु
	वापस mmc_test_best_perक्रमmance(test, 1, 1);
पूर्ण

/*
 * Single पढ़ो perक्रमmance by transfer size.
 */
अटल पूर्णांक mmc_test_profile_पढ़ो_perf(काष्ठा mmc_test_card *test)
अणु
	काष्ठा mmc_test_area *t = &test->area;
	अचिन्हित दीर्घ sz;
	अचिन्हित पूर्णांक dev_addr;
	पूर्णांक ret;

	क्रम (sz = 512; sz < t->max_tfr; sz <<= 1) अणु
		dev_addr = t->dev_addr + (sz >> 9);
		ret = mmc_test_area_io(test, sz, dev_addr, 0, 0, 1);
		अगर (ret)
			वापस ret;
	पूर्ण
	sz = t->max_tfr;
	dev_addr = t->dev_addr;
	वापस mmc_test_area_io(test, sz, dev_addr, 0, 0, 1);
पूर्ण

/*
 * Single ग_लिखो perक्रमmance by transfer size.
 */
अटल पूर्णांक mmc_test_profile_ग_लिखो_perf(काष्ठा mmc_test_card *test)
अणु
	काष्ठा mmc_test_area *t = &test->area;
	अचिन्हित दीर्घ sz;
	अचिन्हित पूर्णांक dev_addr;
	पूर्णांक ret;

	ret = mmc_test_area_erase(test);
	अगर (ret)
		वापस ret;
	क्रम (sz = 512; sz < t->max_tfr; sz <<= 1) अणु
		dev_addr = t->dev_addr + (sz >> 9);
		ret = mmc_test_area_io(test, sz, dev_addr, 1, 0, 1);
		अगर (ret)
			वापस ret;
	पूर्ण
	ret = mmc_test_area_erase(test);
	अगर (ret)
		वापस ret;
	sz = t->max_tfr;
	dev_addr = t->dev_addr;
	वापस mmc_test_area_io(test, sz, dev_addr, 1, 0, 1);
पूर्ण

/*
 * Single trim perक्रमmance by transfer size.
 */
अटल पूर्णांक mmc_test_profile_trim_perf(काष्ठा mmc_test_card *test)
अणु
	काष्ठा mmc_test_area *t = &test->area;
	अचिन्हित दीर्घ sz;
	अचिन्हित पूर्णांक dev_addr;
	काष्ठा बारpec64 ts1, ts2;
	पूर्णांक ret;

	अगर (!mmc_can_trim(test->card))
		वापस RESULT_UNSUP_CARD;

	अगर (!mmc_can_erase(test->card))
		वापस RESULT_UNSUP_HOST;

	क्रम (sz = 512; sz < t->max_sz; sz <<= 1) अणु
		dev_addr = t->dev_addr + (sz >> 9);
		kसमय_get_ts64(&ts1);
		ret = mmc_erase(test->card, dev_addr, sz >> 9, MMC_TRIM_ARG);
		अगर (ret)
			वापस ret;
		kसमय_get_ts64(&ts2);
		mmc_test_prपूर्णांक_rate(test, sz, &ts1, &ts2);
	पूर्ण
	dev_addr = t->dev_addr;
	kसमय_get_ts64(&ts1);
	ret = mmc_erase(test->card, dev_addr, sz >> 9, MMC_TRIM_ARG);
	अगर (ret)
		वापस ret;
	kसमय_get_ts64(&ts2);
	mmc_test_prपूर्णांक_rate(test, sz, &ts1, &ts2);
	वापस 0;
पूर्ण

अटल पूर्णांक mmc_test_seq_पढ़ो_perf(काष्ठा mmc_test_card *test, अचिन्हित दीर्घ sz)
अणु
	काष्ठा mmc_test_area *t = &test->area;
	अचिन्हित पूर्णांक dev_addr, i, cnt;
	काष्ठा बारpec64 ts1, ts2;
	पूर्णांक ret;

	cnt = t->max_sz / sz;
	dev_addr = t->dev_addr;
	kसमय_get_ts64(&ts1);
	क्रम (i = 0; i < cnt; i++) अणु
		ret = mmc_test_area_io(test, sz, dev_addr, 0, 0, 0);
		अगर (ret)
			वापस ret;
		dev_addr += (sz >> 9);
	पूर्ण
	kसमय_get_ts64(&ts2);
	mmc_test_prपूर्णांक_avg_rate(test, sz, cnt, &ts1, &ts2);
	वापस 0;
पूर्ण

/*
 * Consecutive पढ़ो perक्रमmance by transfer size.
 */
अटल पूर्णांक mmc_test_profile_seq_पढ़ो_perf(काष्ठा mmc_test_card *test)
अणु
	काष्ठा mmc_test_area *t = &test->area;
	अचिन्हित दीर्घ sz;
	पूर्णांक ret;

	क्रम (sz = 512; sz < t->max_tfr; sz <<= 1) अणु
		ret = mmc_test_seq_पढ़ो_perf(test, sz);
		अगर (ret)
			वापस ret;
	पूर्ण
	sz = t->max_tfr;
	वापस mmc_test_seq_पढ़ो_perf(test, sz);
पूर्ण

अटल पूर्णांक mmc_test_seq_ग_लिखो_perf(काष्ठा mmc_test_card *test, अचिन्हित दीर्घ sz)
अणु
	काष्ठा mmc_test_area *t = &test->area;
	अचिन्हित पूर्णांक dev_addr, i, cnt;
	काष्ठा बारpec64 ts1, ts2;
	पूर्णांक ret;

	ret = mmc_test_area_erase(test);
	अगर (ret)
		वापस ret;
	cnt = t->max_sz / sz;
	dev_addr = t->dev_addr;
	kसमय_get_ts64(&ts1);
	क्रम (i = 0; i < cnt; i++) अणु
		ret = mmc_test_area_io(test, sz, dev_addr, 1, 0, 0);
		अगर (ret)
			वापस ret;
		dev_addr += (sz >> 9);
	पूर्ण
	kसमय_get_ts64(&ts2);
	mmc_test_prपूर्णांक_avg_rate(test, sz, cnt, &ts1, &ts2);
	वापस 0;
पूर्ण

/*
 * Consecutive ग_लिखो perक्रमmance by transfer size.
 */
अटल पूर्णांक mmc_test_profile_seq_ग_लिखो_perf(काष्ठा mmc_test_card *test)
अणु
	काष्ठा mmc_test_area *t = &test->area;
	अचिन्हित दीर्घ sz;
	पूर्णांक ret;

	क्रम (sz = 512; sz < t->max_tfr; sz <<= 1) अणु
		ret = mmc_test_seq_ग_लिखो_perf(test, sz);
		अगर (ret)
			वापस ret;
	पूर्ण
	sz = t->max_tfr;
	वापस mmc_test_seq_ग_लिखो_perf(test, sz);
पूर्ण

/*
 * Consecutive trim perक्रमmance by transfer size.
 */
अटल पूर्णांक mmc_test_profile_seq_trim_perf(काष्ठा mmc_test_card *test)
अणु
	काष्ठा mmc_test_area *t = &test->area;
	अचिन्हित दीर्घ sz;
	अचिन्हित पूर्णांक dev_addr, i, cnt;
	काष्ठा बारpec64 ts1, ts2;
	पूर्णांक ret;

	अगर (!mmc_can_trim(test->card))
		वापस RESULT_UNSUP_CARD;

	अगर (!mmc_can_erase(test->card))
		वापस RESULT_UNSUP_HOST;

	क्रम (sz = 512; sz <= t->max_sz; sz <<= 1) अणु
		ret = mmc_test_area_erase(test);
		अगर (ret)
			वापस ret;
		ret = mmc_test_area_fill(test);
		अगर (ret)
			वापस ret;
		cnt = t->max_sz / sz;
		dev_addr = t->dev_addr;
		kसमय_get_ts64(&ts1);
		क्रम (i = 0; i < cnt; i++) अणु
			ret = mmc_erase(test->card, dev_addr, sz >> 9,
					MMC_TRIM_ARG);
			अगर (ret)
				वापस ret;
			dev_addr += (sz >> 9);
		पूर्ण
		kसमय_get_ts64(&ts2);
		mmc_test_prपूर्णांक_avg_rate(test, sz, cnt, &ts1, &ts2);
	पूर्ण
	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक rnd_next = 1;

अटल अचिन्हित पूर्णांक mmc_test_rnd_num(अचिन्हित पूर्णांक rnd_cnt)
अणु
	uपूर्णांक64_t r;

	rnd_next = rnd_next * 1103515245 + 12345;
	r = (rnd_next >> 16) & 0x7fff;
	वापस (r * rnd_cnt) >> 15;
पूर्ण

अटल पूर्णांक mmc_test_rnd_perf(काष्ठा mmc_test_card *test, पूर्णांक ग_लिखो, पूर्णांक prपूर्णांक,
			     अचिन्हित दीर्घ sz)
अणु
	अचिन्हित पूर्णांक dev_addr, cnt, rnd_addr, range1, range2, last_ea = 0, ea;
	अचिन्हित पूर्णांक ssz;
	काष्ठा बारpec64 ts1, ts2, ts;
	पूर्णांक ret;

	ssz = sz >> 9;

	rnd_addr = mmc_test_capacity(test->card) / 4;
	range1 = rnd_addr / test->card->pref_erase;
	range2 = range1 / ssz;

	kसमय_get_ts64(&ts1);
	क्रम (cnt = 0; cnt < अच_पूर्णांक_उच्च; cnt++) अणु
		kसमय_get_ts64(&ts2);
		ts = बारpec64_sub(ts2, ts1);
		अगर (ts.tv_sec >= 10)
			अवरोध;
		ea = mmc_test_rnd_num(range1);
		अगर (ea == last_ea)
			ea -= 1;
		last_ea = ea;
		dev_addr = rnd_addr + test->card->pref_erase * ea +
			   ssz * mmc_test_rnd_num(range2);
		ret = mmc_test_area_io(test, sz, dev_addr, ग_लिखो, 0, 0);
		अगर (ret)
			वापस ret;
	पूर्ण
	अगर (prपूर्णांक)
		mmc_test_prपूर्णांक_avg_rate(test, sz, cnt, &ts1, &ts2);
	वापस 0;
पूर्ण

अटल पूर्णांक mmc_test_अक्रमom_perf(काष्ठा mmc_test_card *test, पूर्णांक ग_लिखो)
अणु
	काष्ठा mmc_test_area *t = &test->area;
	अचिन्हित पूर्णांक next;
	अचिन्हित दीर्घ sz;
	पूर्णांक ret;

	क्रम (sz = 512; sz < t->max_tfr; sz <<= 1) अणु
		/*
		 * When writing, try to get more consistent results by running
		 * the test twice with exactly the same I/O but outputting the
		 * results only क्रम the 2nd run.
		 */
		अगर (ग_लिखो) अणु
			next = rnd_next;
			ret = mmc_test_rnd_perf(test, ग_लिखो, 0, sz);
			अगर (ret)
				वापस ret;
			rnd_next = next;
		पूर्ण
		ret = mmc_test_rnd_perf(test, ग_लिखो, 1, sz);
		अगर (ret)
			वापस ret;
	पूर्ण
	sz = t->max_tfr;
	अगर (ग_लिखो) अणु
		next = rnd_next;
		ret = mmc_test_rnd_perf(test, ग_लिखो, 0, sz);
		अगर (ret)
			वापस ret;
		rnd_next = next;
	पूर्ण
	वापस mmc_test_rnd_perf(test, ग_लिखो, 1, sz);
पूर्ण

/*
 * Ranकरोm पढ़ो perक्रमmance by transfer size.
 */
अटल पूर्णांक mmc_test_अक्रमom_पढ़ो_perf(काष्ठा mmc_test_card *test)
अणु
	वापस mmc_test_अक्रमom_perf(test, 0);
पूर्ण

/*
 * Ranकरोm ग_लिखो perक्रमmance by transfer size.
 */
अटल पूर्णांक mmc_test_अक्रमom_ग_लिखो_perf(काष्ठा mmc_test_card *test)
अणु
	वापस mmc_test_अक्रमom_perf(test, 1);
पूर्ण

अटल पूर्णांक mmc_test_seq_perf(काष्ठा mmc_test_card *test, पूर्णांक ग_लिखो,
			     अचिन्हित पूर्णांक tot_sz, पूर्णांक max_scatter)
अणु
	काष्ठा mmc_test_area *t = &test->area;
	अचिन्हित पूर्णांक dev_addr, i, cnt, sz, ssz;
	काष्ठा बारpec64 ts1, ts2;
	पूर्णांक ret;

	sz = t->max_tfr;

	/*
	 * In the हाल of a maximally scattered transfer, the maximum transfer
	 * size is further limited by using PAGE_SIZE segments.
	 */
	अगर (max_scatter) अणु
		अचिन्हित दीर्घ max_tfr;

		अगर (t->max_seg_sz >= PAGE_SIZE)
			max_tfr = t->max_segs * PAGE_SIZE;
		अन्यथा
			max_tfr = t->max_segs * t->max_seg_sz;
		अगर (sz > max_tfr)
			sz = max_tfr;
	पूर्ण

	ssz = sz >> 9;
	dev_addr = mmc_test_capacity(test->card) / 4;
	अगर (tot_sz > dev_addr << 9)
		tot_sz = dev_addr << 9;
	cnt = tot_sz / sz;
	dev_addr &= 0xffff0000; /* Round to 64MiB boundary */

	kसमय_get_ts64(&ts1);
	क्रम (i = 0; i < cnt; i++) अणु
		ret = mmc_test_area_io(test, sz, dev_addr, ग_लिखो,
				       max_scatter, 0);
		अगर (ret)
			वापस ret;
		dev_addr += ssz;
	पूर्ण
	kसमय_get_ts64(&ts2);

	mmc_test_prपूर्णांक_avg_rate(test, sz, cnt, &ts1, &ts2);

	वापस 0;
पूर्ण

अटल पूर्णांक mmc_test_large_seq_perf(काष्ठा mmc_test_card *test, पूर्णांक ग_लिखो)
अणु
	पूर्णांक ret, i;

	क्रम (i = 0; i < 10; i++) अणु
		ret = mmc_test_seq_perf(test, ग_लिखो, 10 * 1024 * 1024, 1);
		अगर (ret)
			वापस ret;
	पूर्ण
	क्रम (i = 0; i < 5; i++) अणु
		ret = mmc_test_seq_perf(test, ग_लिखो, 100 * 1024 * 1024, 1);
		अगर (ret)
			वापस ret;
	पूर्ण
	क्रम (i = 0; i < 3; i++) अणु
		ret = mmc_test_seq_perf(test, ग_लिखो, 1000 * 1024 * 1024, 1);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस ret;
पूर्ण

/*
 * Large sequential पढ़ो perक्रमmance.
 */
अटल पूर्णांक mmc_test_large_seq_पढ़ो_perf(काष्ठा mmc_test_card *test)
अणु
	वापस mmc_test_large_seq_perf(test, 0);
पूर्ण

/*
 * Large sequential ग_लिखो perक्रमmance.
 */
अटल पूर्णांक mmc_test_large_seq_ग_लिखो_perf(काष्ठा mmc_test_card *test)
अणु
	वापस mmc_test_large_seq_perf(test, 1);
पूर्ण

अटल पूर्णांक mmc_test_rw_multiple(काष्ठा mmc_test_card *test,
				काष्ठा mmc_test_multiple_rw *tdata,
				अचिन्हित पूर्णांक reqsize, अचिन्हित पूर्णांक size,
				पूर्णांक min_sg_len)
अणु
	अचिन्हित पूर्णांक dev_addr;
	काष्ठा mmc_test_area *t = &test->area;
	पूर्णांक ret = 0;

	/* Set up test area */
	अगर (size > mmc_test_capacity(test->card) / 2 * 512)
		size = mmc_test_capacity(test->card) / 2 * 512;
	अगर (reqsize > t->max_tfr)
		reqsize = t->max_tfr;
	dev_addr = mmc_test_capacity(test->card) / 4;
	अगर ((dev_addr & 0xffff0000))
		dev_addr &= 0xffff0000; /* Round to 64MiB boundary */
	अन्यथा
		dev_addr &= 0xfffff800; /* Round to 1MiB boundary */
	अगर (!dev_addr)
		जाओ err;

	अगर (reqsize > size)
		वापस 0;

	/* prepare test area */
	अगर (mmc_can_erase(test->card) &&
	    tdata->prepare & MMC_TEST_PREP_ERASE) अणु
		ret = mmc_erase(test->card, dev_addr,
				size / 512, test->card->erase_arg);
		अगर (ret)
			ret = mmc_erase(test->card, dev_addr,
					size / 512, MMC_ERASE_ARG);
		अगर (ret)
			जाओ err;
	पूर्ण

	/* Run test */
	ret = mmc_test_area_io_seq(test, reqsize, dev_addr,
				   tdata->करो_ग_लिखो, 0, 1, size / reqsize,
				   tdata->करो_nonblock_req, min_sg_len);
	अगर (ret)
		जाओ err;

	वापस ret;
 err:
	pr_info("[%s] error\n", __func__);
	वापस ret;
पूर्ण

अटल पूर्णांक mmc_test_rw_multiple_size(काष्ठा mmc_test_card *test,
				     काष्ठा mmc_test_multiple_rw *rw)
अणु
	पूर्णांक ret = 0;
	पूर्णांक i;
	व्योम *pre_req = test->card->host->ops->pre_req;
	व्योम *post_req = test->card->host->ops->post_req;

	अगर (rw->करो_nonblock_req &&
	    ((!pre_req && post_req) || (pre_req && !post_req))) अणु
		pr_info("error: only one of pre/post is defined\n");
		वापस -EINVAL;
	पूर्ण

	क्रम (i = 0 ; i < rw->len && ret == 0; i++) अणु
		ret = mmc_test_rw_multiple(test, rw, rw->bs[i], rw->size, 0);
		अगर (ret)
			अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक mmc_test_rw_multiple_sg_len(काष्ठा mmc_test_card *test,
				       काष्ठा mmc_test_multiple_rw *rw)
अणु
	पूर्णांक ret = 0;
	पूर्णांक i;

	क्रम (i = 0 ; i < rw->len && ret == 0; i++) अणु
		ret = mmc_test_rw_multiple(test, rw, 512 * 1024, rw->size,
					   rw->sg_len[i]);
		अगर (ret)
			अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

/*
 * Multiple blocking ग_लिखो 4k to 4 MB chunks
 */
अटल पूर्णांक mmc_test_profile_mult_ग_लिखो_blocking_perf(काष्ठा mmc_test_card *test)
अणु
	अचिन्हित पूर्णांक bs[] = अणु1 << 12, 1 << 13, 1 << 14, 1 << 15, 1 << 16,
			     1 << 17, 1 << 18, 1 << 19, 1 << 20, 1 << 22पूर्ण;
	काष्ठा mmc_test_multiple_rw test_data = अणु
		.bs = bs,
		.size = TEST_AREA_MAX_SIZE,
		.len = ARRAY_SIZE(bs),
		.करो_ग_लिखो = true,
		.करो_nonblock_req = false,
		.prepare = MMC_TEST_PREP_ERASE,
	पूर्ण;

	वापस mmc_test_rw_multiple_size(test, &test_data);
पूर्ण;

/*
 * Multiple non-blocking ग_लिखो 4k to 4 MB chunks
 */
अटल पूर्णांक mmc_test_profile_mult_ग_लिखो_nonblock_perf(काष्ठा mmc_test_card *test)
अणु
	अचिन्हित पूर्णांक bs[] = अणु1 << 12, 1 << 13, 1 << 14, 1 << 15, 1 << 16,
			     1 << 17, 1 << 18, 1 << 19, 1 << 20, 1 << 22पूर्ण;
	काष्ठा mmc_test_multiple_rw test_data = अणु
		.bs = bs,
		.size = TEST_AREA_MAX_SIZE,
		.len = ARRAY_SIZE(bs),
		.करो_ग_लिखो = true,
		.करो_nonblock_req = true,
		.prepare = MMC_TEST_PREP_ERASE,
	पूर्ण;

	वापस mmc_test_rw_multiple_size(test, &test_data);
पूर्ण

/*
 * Multiple blocking पढ़ो 4k to 4 MB chunks
 */
अटल पूर्णांक mmc_test_profile_mult_पढ़ो_blocking_perf(काष्ठा mmc_test_card *test)
अणु
	अचिन्हित पूर्णांक bs[] = अणु1 << 12, 1 << 13, 1 << 14, 1 << 15, 1 << 16,
			     1 << 17, 1 << 18, 1 << 19, 1 << 20, 1 << 22पूर्ण;
	काष्ठा mmc_test_multiple_rw test_data = अणु
		.bs = bs,
		.size = TEST_AREA_MAX_SIZE,
		.len = ARRAY_SIZE(bs),
		.करो_ग_लिखो = false,
		.करो_nonblock_req = false,
		.prepare = MMC_TEST_PREP_NONE,
	पूर्ण;

	वापस mmc_test_rw_multiple_size(test, &test_data);
पूर्ण

/*
 * Multiple non-blocking पढ़ो 4k to 4 MB chunks
 */
अटल पूर्णांक mmc_test_profile_mult_पढ़ो_nonblock_perf(काष्ठा mmc_test_card *test)
अणु
	अचिन्हित पूर्णांक bs[] = अणु1 << 12, 1 << 13, 1 << 14, 1 << 15, 1 << 16,
			     1 << 17, 1 << 18, 1 << 19, 1 << 20, 1 << 22पूर्ण;
	काष्ठा mmc_test_multiple_rw test_data = अणु
		.bs = bs,
		.size = TEST_AREA_MAX_SIZE,
		.len = ARRAY_SIZE(bs),
		.करो_ग_लिखो = false,
		.करो_nonblock_req = true,
		.prepare = MMC_TEST_PREP_NONE,
	पूर्ण;

	वापस mmc_test_rw_multiple_size(test, &test_data);
पूर्ण

/*
 * Multiple blocking ग_लिखो 1 to 512 sg elements
 */
अटल पूर्णांक mmc_test_profile_sglen_wr_blocking_perf(काष्ठा mmc_test_card *test)
अणु
	अचिन्हित पूर्णांक sg_len[] = अणु1, 1 << 3, 1 << 4, 1 << 5, 1 << 6,
				 1 << 7, 1 << 8, 1 << 9पूर्ण;
	काष्ठा mmc_test_multiple_rw test_data = अणु
		.sg_len = sg_len,
		.size = TEST_AREA_MAX_SIZE,
		.len = ARRAY_SIZE(sg_len),
		.करो_ग_लिखो = true,
		.करो_nonblock_req = false,
		.prepare = MMC_TEST_PREP_ERASE,
	पूर्ण;

	वापस mmc_test_rw_multiple_sg_len(test, &test_data);
पूर्ण;

/*
 * Multiple non-blocking ग_लिखो 1 to 512 sg elements
 */
अटल पूर्णांक mmc_test_profile_sglen_wr_nonblock_perf(काष्ठा mmc_test_card *test)
अणु
	अचिन्हित पूर्णांक sg_len[] = अणु1, 1 << 3, 1 << 4, 1 << 5, 1 << 6,
				 1 << 7, 1 << 8, 1 << 9पूर्ण;
	काष्ठा mmc_test_multiple_rw test_data = अणु
		.sg_len = sg_len,
		.size = TEST_AREA_MAX_SIZE,
		.len = ARRAY_SIZE(sg_len),
		.करो_ग_लिखो = true,
		.करो_nonblock_req = true,
		.prepare = MMC_TEST_PREP_ERASE,
	पूर्ण;

	वापस mmc_test_rw_multiple_sg_len(test, &test_data);
पूर्ण

/*
 * Multiple blocking पढ़ो 1 to 512 sg elements
 */
अटल पूर्णांक mmc_test_profile_sglen_r_blocking_perf(काष्ठा mmc_test_card *test)
अणु
	अचिन्हित पूर्णांक sg_len[] = अणु1, 1 << 3, 1 << 4, 1 << 5, 1 << 6,
				 1 << 7, 1 << 8, 1 << 9पूर्ण;
	काष्ठा mmc_test_multiple_rw test_data = अणु
		.sg_len = sg_len,
		.size = TEST_AREA_MAX_SIZE,
		.len = ARRAY_SIZE(sg_len),
		.करो_ग_लिखो = false,
		.करो_nonblock_req = false,
		.prepare = MMC_TEST_PREP_NONE,
	पूर्ण;

	वापस mmc_test_rw_multiple_sg_len(test, &test_data);
पूर्ण

/*
 * Multiple non-blocking पढ़ो 1 to 512 sg elements
 */
अटल पूर्णांक mmc_test_profile_sglen_r_nonblock_perf(काष्ठा mmc_test_card *test)
अणु
	अचिन्हित पूर्णांक sg_len[] = अणु1, 1 << 3, 1 << 4, 1 << 5, 1 << 6,
				 1 << 7, 1 << 8, 1 << 9पूर्ण;
	काष्ठा mmc_test_multiple_rw test_data = अणु
		.sg_len = sg_len,
		.size = TEST_AREA_MAX_SIZE,
		.len = ARRAY_SIZE(sg_len),
		.करो_ग_लिखो = false,
		.करो_nonblock_req = true,
		.prepare = MMC_TEST_PREP_NONE,
	पूर्ण;

	वापस mmc_test_rw_multiple_sg_len(test, &test_data);
पूर्ण

/*
 * eMMC hardware reset.
 */
अटल पूर्णांक mmc_test_reset(काष्ठा mmc_test_card *test)
अणु
	काष्ठा mmc_card *card = test->card;
	काष्ठा mmc_host *host = card->host;
	पूर्णांक err;

	err = mmc_hw_reset(host);
	अगर (!err) अणु
		/*
		 * Reset will re-enable the card's command queue, but tests
		 * expect it to be disabled.
		 */
		अगर (card->ext_csd.cmdq_en)
			mmc_cmdq_disable(card);
		वापस RESULT_OK;
	पूर्ण अन्यथा अगर (err == -EOPNOTSUPP) अणु
		वापस RESULT_UNSUP_HOST;
	पूर्ण

	वापस RESULT_FAIL;
पूर्ण

अटल पूर्णांक mmc_test_send_status(काष्ठा mmc_test_card *test,
				काष्ठा mmc_command *cmd)
अणु
	स_रखो(cmd, 0, माप(*cmd));

	cmd->opcode = MMC_SEND_STATUS;
	अगर (!mmc_host_is_spi(test->card->host))
		cmd->arg = test->card->rca << 16;
	cmd->flags = MMC_RSP_SPI_R2 | MMC_RSP_R1 | MMC_CMD_AC;

	वापस mmc_रुको_क्रम_cmd(test->card->host, cmd, 0);
पूर्ण

अटल पूर्णांक mmc_test_ongoing_transfer(काष्ठा mmc_test_card *test,
				     अचिन्हित पूर्णांक dev_addr, पूर्णांक use_sbc,
				     पूर्णांक repeat_cmd, पूर्णांक ग_लिखो, पूर्णांक use_areq)
अणु
	काष्ठा mmc_test_req *rq = mmc_test_req_alloc();
	काष्ठा mmc_host *host = test->card->host;
	काष्ठा mmc_test_area *t = &test->area;
	काष्ठा mmc_request *mrq;
	अचिन्हित दीर्घ समयout;
	bool expired = false;
	पूर्णांक ret = 0, cmd_ret;
	u32 status = 0;
	पूर्णांक count = 0;

	अगर (!rq)
		वापस -ENOMEM;

	mrq = &rq->mrq;
	अगर (use_sbc)
		mrq->sbc = &rq->sbc;
	mrq->cap_cmd_during_tfr = true;

	mmc_test_prepare_mrq(test, mrq, t->sg, t->sg_len, dev_addr, t->blocks,
			     512, ग_लिखो);

	अगर (use_sbc && t->blocks > 1 && !mrq->sbc) अणु
		ret =  mmc_host_cmd23(host) ?
		       RESULT_UNSUP_CARD :
		       RESULT_UNSUP_HOST;
		जाओ out_मुक्त;
	पूर्ण

	/* Start ongoing data request */
	अगर (use_areq) अणु
		ret = mmc_test_start_areq(test, mrq, शून्य);
		अगर (ret)
			जाओ out_मुक्त;
	पूर्ण अन्यथा अणु
		mmc_रुको_क्रम_req(host, mrq);
	पूर्ण

	समयout = jअगरfies + msecs_to_jअगरfies(3000);
	करो अणु
		count += 1;

		/* Send status command जबतक data transfer in progress */
		cmd_ret = mmc_test_send_status(test, &rq->status);
		अगर (cmd_ret)
			अवरोध;

		status = rq->status.resp[0];
		अगर (status & R1_ERROR) अणु
			cmd_ret = -EIO;
			अवरोध;
		पूर्ण

		अगर (mmc_is_req_करोne(host, mrq))
			अवरोध;

		expired = समय_after(jअगरfies, समयout);
		अगर (expired) अणु
			pr_info("%s: timeout waiting for Tran state status %#x\n",
				mmc_hostname(host), status);
			cmd_ret = -ETIMEDOUT;
			अवरोध;
		पूर्ण
	पूर्ण जबतक (repeat_cmd && R1_CURRENT_STATE(status) != R1_STATE_TRAN);

	/* Wait क्रम data request to complete */
	अगर (use_areq) अणु
		ret = mmc_test_start_areq(test, शून्य, mrq);
	पूर्ण अन्यथा अणु
		mmc_रुको_क्रम_req_करोne(test->card->host, mrq);
	पूर्ण

	/*
	 * For cap_cmd_during_tfr request, upper layer must send stop अगर
	 * required.
	 */
	अगर (mrq->data->stop && (mrq->data->error || !mrq->sbc)) अणु
		अगर (ret)
			mmc_रुको_क्रम_cmd(host, mrq->data->stop, 0);
		अन्यथा
			ret = mmc_रुको_क्रम_cmd(host, mrq->data->stop, 0);
	पूर्ण

	अगर (ret)
		जाओ out_मुक्त;

	अगर (cmd_ret) अणु
		pr_info("%s: Send Status failed: status %#x, error %d\n",
			mmc_hostname(test->card->host), status, cmd_ret);
	पूर्ण

	ret = mmc_test_check_result(test, mrq);
	अगर (ret)
		जाओ out_मुक्त;

	ret = mmc_test_रुको_busy(test);
	अगर (ret)
		जाओ out_मुक्त;

	अगर (repeat_cmd && (t->blocks + 1) << 9 > t->max_tfr)
		pr_info("%s: %d commands completed during transfer of %u blocks\n",
			mmc_hostname(test->card->host), count, t->blocks);

	अगर (cmd_ret)
		ret = cmd_ret;
out_मुक्त:
	kमुक्त(rq);

	वापस ret;
पूर्ण

अटल पूर्णांक __mmc_test_cmds_during_tfr(काष्ठा mmc_test_card *test,
				      अचिन्हित दीर्घ sz, पूर्णांक use_sbc, पूर्णांक ग_लिखो,
				      पूर्णांक use_areq)
अणु
	काष्ठा mmc_test_area *t = &test->area;
	पूर्णांक ret;

	अगर (!(test->card->host->caps & MMC_CAP_CMD_DURING_TFR))
		वापस RESULT_UNSUP_HOST;

	ret = mmc_test_area_map(test, sz, 0, 0, use_areq);
	अगर (ret)
		वापस ret;

	ret = mmc_test_ongoing_transfer(test, t->dev_addr, use_sbc, 0, ग_लिखो,
					use_areq);
	अगर (ret)
		वापस ret;

	वापस mmc_test_ongoing_transfer(test, t->dev_addr, use_sbc, 1, ग_लिखो,
					 use_areq);
पूर्ण

अटल पूर्णांक mmc_test_cmds_during_tfr(काष्ठा mmc_test_card *test, पूर्णांक use_sbc,
				    पूर्णांक ग_लिखो, पूर्णांक use_areq)
अणु
	काष्ठा mmc_test_area *t = &test->area;
	अचिन्हित दीर्घ sz;
	पूर्णांक ret;

	क्रम (sz = 512; sz <= t->max_tfr; sz += 512) अणु
		ret = __mmc_test_cmds_during_tfr(test, sz, use_sbc, ग_लिखो,
						 use_areq);
		अगर (ret)
			वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Commands during पढ़ो - no Set Block Count (CMD23).
 */
अटल पूर्णांक mmc_test_cmds_during_पढ़ो(काष्ठा mmc_test_card *test)
अणु
	वापस mmc_test_cmds_during_tfr(test, 0, 0, 0);
पूर्ण

/*
 * Commands during ग_लिखो - no Set Block Count (CMD23).
 */
अटल पूर्णांक mmc_test_cmds_during_ग_लिखो(काष्ठा mmc_test_card *test)
अणु
	वापस mmc_test_cmds_during_tfr(test, 0, 1, 0);
पूर्ण

/*
 * Commands during पढ़ो - use Set Block Count (CMD23).
 */
अटल पूर्णांक mmc_test_cmds_during_पढ़ो_cmd23(काष्ठा mmc_test_card *test)
अणु
	वापस mmc_test_cmds_during_tfr(test, 1, 0, 0);
पूर्ण

/*
 * Commands during ग_लिखो - use Set Block Count (CMD23).
 */
अटल पूर्णांक mmc_test_cmds_during_ग_लिखो_cmd23(काष्ठा mmc_test_card *test)
अणु
	वापस mmc_test_cmds_during_tfr(test, 1, 1, 0);
पूर्ण

/*
 * Commands during non-blocking पढ़ो - use Set Block Count (CMD23).
 */
अटल पूर्णांक mmc_test_cmds_during_पढ़ो_cmd23_nonblock(काष्ठा mmc_test_card *test)
अणु
	वापस mmc_test_cmds_during_tfr(test, 1, 0, 1);
पूर्ण

/*
 * Commands during non-blocking ग_लिखो - use Set Block Count (CMD23).
 */
अटल पूर्णांक mmc_test_cmds_during_ग_लिखो_cmd23_nonblock(काष्ठा mmc_test_card *test)
अणु
	वापस mmc_test_cmds_during_tfr(test, 1, 1, 1);
पूर्ण

अटल स्थिर काष्ठा mmc_test_हाल mmc_test_हालs[] = अणु
	अणु
		.name = "Basic write (no data verification)",
		.run = mmc_test_basic_ग_लिखो,
	पूर्ण,

	अणु
		.name = "Basic read (no data verification)",
		.run = mmc_test_basic_पढ़ो,
	पूर्ण,

	अणु
		.name = "Basic write (with data verification)",
		.prepare = mmc_test_prepare_ग_लिखो,
		.run = mmc_test_verअगरy_ग_लिखो,
		.cleanup = mmc_test_cleanup,
	पूर्ण,

	अणु
		.name = "Basic read (with data verification)",
		.prepare = mmc_test_prepare_पढ़ो,
		.run = mmc_test_verअगरy_पढ़ो,
		.cleanup = mmc_test_cleanup,
	पूर्ण,

	अणु
		.name = "Multi-block write",
		.prepare = mmc_test_prepare_ग_लिखो,
		.run = mmc_test_multi_ग_लिखो,
		.cleanup = mmc_test_cleanup,
	पूर्ण,

	अणु
		.name = "Multi-block read",
		.prepare = mmc_test_prepare_पढ़ो,
		.run = mmc_test_multi_पढ़ो,
		.cleanup = mmc_test_cleanup,
	पूर्ण,

	अणु
		.name = "Power of two block writes",
		.prepare = mmc_test_prepare_ग_लिखो,
		.run = mmc_test_घात2_ग_लिखो,
		.cleanup = mmc_test_cleanup,
	पूर्ण,

	अणु
		.name = "Power of two block reads",
		.prepare = mmc_test_prepare_पढ़ो,
		.run = mmc_test_घात2_पढ़ो,
		.cleanup = mmc_test_cleanup,
	पूर्ण,

	अणु
		.name = "Weird sized block writes",
		.prepare = mmc_test_prepare_ग_लिखो,
		.run = mmc_test_weird_ग_लिखो,
		.cleanup = mmc_test_cleanup,
	पूर्ण,

	अणु
		.name = "Weird sized block reads",
		.prepare = mmc_test_prepare_पढ़ो,
		.run = mmc_test_weird_पढ़ो,
		.cleanup = mmc_test_cleanup,
	पूर्ण,

	अणु
		.name = "Badly aligned write",
		.prepare = mmc_test_prepare_ग_लिखो,
		.run = mmc_test_align_ग_लिखो,
		.cleanup = mmc_test_cleanup,
	पूर्ण,

	अणु
		.name = "Badly aligned read",
		.prepare = mmc_test_prepare_पढ़ो,
		.run = mmc_test_align_पढ़ो,
		.cleanup = mmc_test_cleanup,
	पूर्ण,

	अणु
		.name = "Badly aligned multi-block write",
		.prepare = mmc_test_prepare_ग_लिखो,
		.run = mmc_test_align_multi_ग_लिखो,
		.cleanup = mmc_test_cleanup,
	पूर्ण,

	अणु
		.name = "Badly aligned multi-block read",
		.prepare = mmc_test_prepare_पढ़ो,
		.run = mmc_test_align_multi_पढ़ो,
		.cleanup = mmc_test_cleanup,
	पूर्ण,

	अणु
		.name = "Proper xfer_size at write (start failure)",
		.run = mmc_test_xfersize_ग_लिखो,
	पूर्ण,

	अणु
		.name = "Proper xfer_size at read (start failure)",
		.run = mmc_test_xfersize_पढ़ो,
	पूर्ण,

	अणु
		.name = "Proper xfer_size at write (midway failure)",
		.run = mmc_test_multi_xfersize_ग_लिखो,
	पूर्ण,

	अणु
		.name = "Proper xfer_size at read (midway failure)",
		.run = mmc_test_multi_xfersize_पढ़ो,
	पूर्ण,

#अगर_घोषित CONFIG_HIGHMEM

	अणु
		.name = "Highmem write",
		.prepare = mmc_test_prepare_ग_लिखो,
		.run = mmc_test_ग_लिखो_high,
		.cleanup = mmc_test_cleanup,
	पूर्ण,

	अणु
		.name = "Highmem read",
		.prepare = mmc_test_prepare_पढ़ो,
		.run = mmc_test_पढ़ो_high,
		.cleanup = mmc_test_cleanup,
	पूर्ण,

	अणु
		.name = "Multi-block highmem write",
		.prepare = mmc_test_prepare_ग_लिखो,
		.run = mmc_test_multi_ग_लिखो_high,
		.cleanup = mmc_test_cleanup,
	पूर्ण,

	अणु
		.name = "Multi-block highmem read",
		.prepare = mmc_test_prepare_पढ़ो,
		.run = mmc_test_multi_पढ़ो_high,
		.cleanup = mmc_test_cleanup,
	पूर्ण,

#अन्यथा

	अणु
		.name = "Highmem write",
		.run = mmc_test_no_highmem,
	पूर्ण,

	अणु
		.name = "Highmem read",
		.run = mmc_test_no_highmem,
	पूर्ण,

	अणु
		.name = "Multi-block highmem write",
		.run = mmc_test_no_highmem,
	पूर्ण,

	अणु
		.name = "Multi-block highmem read",
		.run = mmc_test_no_highmem,
	पूर्ण,

#पूर्ण_अगर /* CONFIG_HIGHMEM */

	अणु
		.name = "Best-case read performance",
		.prepare = mmc_test_area_prepare_fill,
		.run = mmc_test_best_पढ़ो_perक्रमmance,
		.cleanup = mmc_test_area_cleanup,
	पूर्ण,

	अणु
		.name = "Best-case write performance",
		.prepare = mmc_test_area_prepare_erase,
		.run = mmc_test_best_ग_लिखो_perक्रमmance,
		.cleanup = mmc_test_area_cleanup,
	पूर्ण,

	अणु
		.name = "Best-case read performance into scattered pages",
		.prepare = mmc_test_area_prepare_fill,
		.run = mmc_test_best_पढ़ो_perf_max_scatter,
		.cleanup = mmc_test_area_cleanup,
	पूर्ण,

	अणु
		.name = "Best-case write performance from scattered pages",
		.prepare = mmc_test_area_prepare_erase,
		.run = mmc_test_best_ग_लिखो_perf_max_scatter,
		.cleanup = mmc_test_area_cleanup,
	पूर्ण,

	अणु
		.name = "Single read performance by transfer size",
		.prepare = mmc_test_area_prepare_fill,
		.run = mmc_test_profile_पढ़ो_perf,
		.cleanup = mmc_test_area_cleanup,
	पूर्ण,

	अणु
		.name = "Single write performance by transfer size",
		.prepare = mmc_test_area_prepare,
		.run = mmc_test_profile_ग_लिखो_perf,
		.cleanup = mmc_test_area_cleanup,
	पूर्ण,

	अणु
		.name = "Single trim performance by transfer size",
		.prepare = mmc_test_area_prepare_fill,
		.run = mmc_test_profile_trim_perf,
		.cleanup = mmc_test_area_cleanup,
	पूर्ण,

	अणु
		.name = "Consecutive read performance by transfer size",
		.prepare = mmc_test_area_prepare_fill,
		.run = mmc_test_profile_seq_पढ़ो_perf,
		.cleanup = mmc_test_area_cleanup,
	पूर्ण,

	अणु
		.name = "Consecutive write performance by transfer size",
		.prepare = mmc_test_area_prepare,
		.run = mmc_test_profile_seq_ग_लिखो_perf,
		.cleanup = mmc_test_area_cleanup,
	पूर्ण,

	अणु
		.name = "Consecutive trim performance by transfer size",
		.prepare = mmc_test_area_prepare,
		.run = mmc_test_profile_seq_trim_perf,
		.cleanup = mmc_test_area_cleanup,
	पूर्ण,

	अणु
		.name = "Random read performance by transfer size",
		.prepare = mmc_test_area_prepare,
		.run = mmc_test_अक्रमom_पढ़ो_perf,
		.cleanup = mmc_test_area_cleanup,
	पूर्ण,

	अणु
		.name = "Random write performance by transfer size",
		.prepare = mmc_test_area_prepare,
		.run = mmc_test_अक्रमom_ग_लिखो_perf,
		.cleanup = mmc_test_area_cleanup,
	पूर्ण,

	अणु
		.name = "Large sequential read into scattered pages",
		.prepare = mmc_test_area_prepare,
		.run = mmc_test_large_seq_पढ़ो_perf,
		.cleanup = mmc_test_area_cleanup,
	पूर्ण,

	अणु
		.name = "Large sequential write from scattered pages",
		.prepare = mmc_test_area_prepare,
		.run = mmc_test_large_seq_ग_लिखो_perf,
		.cleanup = mmc_test_area_cleanup,
	पूर्ण,

	अणु
		.name = "Write performance with blocking req 4k to 4MB",
		.prepare = mmc_test_area_prepare,
		.run = mmc_test_profile_mult_ग_लिखो_blocking_perf,
		.cleanup = mmc_test_area_cleanup,
	पूर्ण,

	अणु
		.name = "Write performance with non-blocking req 4k to 4MB",
		.prepare = mmc_test_area_prepare,
		.run = mmc_test_profile_mult_ग_लिखो_nonblock_perf,
		.cleanup = mmc_test_area_cleanup,
	पूर्ण,

	अणु
		.name = "Read performance with blocking req 4k to 4MB",
		.prepare = mmc_test_area_prepare,
		.run = mmc_test_profile_mult_पढ़ो_blocking_perf,
		.cleanup = mmc_test_area_cleanup,
	पूर्ण,

	अणु
		.name = "Read performance with non-blocking req 4k to 4MB",
		.prepare = mmc_test_area_prepare,
		.run = mmc_test_profile_mult_पढ़ो_nonblock_perf,
		.cleanup = mmc_test_area_cleanup,
	पूर्ण,

	अणु
		.name = "Write performance blocking req 1 to 512 sg elems",
		.prepare = mmc_test_area_prepare,
		.run = mmc_test_profile_sglen_wr_blocking_perf,
		.cleanup = mmc_test_area_cleanup,
	पूर्ण,

	अणु
		.name = "Write performance non-blocking req 1 to 512 sg elems",
		.prepare = mmc_test_area_prepare,
		.run = mmc_test_profile_sglen_wr_nonblock_perf,
		.cleanup = mmc_test_area_cleanup,
	पूर्ण,

	अणु
		.name = "Read performance blocking req 1 to 512 sg elems",
		.prepare = mmc_test_area_prepare,
		.run = mmc_test_profile_sglen_r_blocking_perf,
		.cleanup = mmc_test_area_cleanup,
	पूर्ण,

	अणु
		.name = "Read performance non-blocking req 1 to 512 sg elems",
		.prepare = mmc_test_area_prepare,
		.run = mmc_test_profile_sglen_r_nonblock_perf,
		.cleanup = mmc_test_area_cleanup,
	पूर्ण,

	अणु
		.name = "Reset test",
		.run = mmc_test_reset,
	पूर्ण,

	अणु
		.name = "Commands during read - no Set Block Count (CMD23)",
		.prepare = mmc_test_area_prepare,
		.run = mmc_test_cmds_during_पढ़ो,
		.cleanup = mmc_test_area_cleanup,
	पूर्ण,

	अणु
		.name = "Commands during write - no Set Block Count (CMD23)",
		.prepare = mmc_test_area_prepare,
		.run = mmc_test_cmds_during_ग_लिखो,
		.cleanup = mmc_test_area_cleanup,
	पूर्ण,

	अणु
		.name = "Commands during read - use Set Block Count (CMD23)",
		.prepare = mmc_test_area_prepare,
		.run = mmc_test_cmds_during_पढ़ो_cmd23,
		.cleanup = mmc_test_area_cleanup,
	पूर्ण,

	अणु
		.name = "Commands during write - use Set Block Count (CMD23)",
		.prepare = mmc_test_area_prepare,
		.run = mmc_test_cmds_during_ग_लिखो_cmd23,
		.cleanup = mmc_test_area_cleanup,
	पूर्ण,

	अणु
		.name = "Commands during non-blocking read - use Set Block Count (CMD23)",
		.prepare = mmc_test_area_prepare,
		.run = mmc_test_cmds_during_पढ़ो_cmd23_nonblock,
		.cleanup = mmc_test_area_cleanup,
	पूर्ण,

	अणु
		.name = "Commands during non-blocking write - use Set Block Count (CMD23)",
		.prepare = mmc_test_area_prepare,
		.run = mmc_test_cmds_during_ग_लिखो_cmd23_nonblock,
		.cleanup = mmc_test_area_cleanup,
	पूर्ण,
पूर्ण;

अटल DEFINE_MUTEX(mmc_test_lock);

अटल LIST_HEAD(mmc_test_result);

अटल व्योम mmc_test_run(काष्ठा mmc_test_card *test, पूर्णांक testहाल)
अणु
	पूर्णांक i, ret;

	pr_info("%s: Starting tests of card %s...\n",
		mmc_hostname(test->card->host), mmc_card_id(test->card));

	mmc_claim_host(test->card->host);

	क्रम (i = 0; i < ARRAY_SIZE(mmc_test_हालs); i++) अणु
		काष्ठा mmc_test_general_result *gr;

		अगर (testहाल && ((i + 1) != testहाल))
			जारी;

		pr_info("%s: Test case %d. %s...\n",
			mmc_hostname(test->card->host), i + 1,
			mmc_test_हालs[i].name);

		अगर (mmc_test_हालs[i].prepare) अणु
			ret = mmc_test_हालs[i].prepare(test);
			अगर (ret) अणु
				pr_info("%s: Result: Prepare stage failed! (%d)\n",
					mmc_hostname(test->card->host),
					ret);
				जारी;
			पूर्ण
		पूर्ण

		gr = kzalloc(माप(*gr), GFP_KERNEL);
		अगर (gr) अणु
			INIT_LIST_HEAD(&gr->tr_lst);

			/* Assign data what we know alपढ़ोy */
			gr->card = test->card;
			gr->testहाल = i;

			/* Append container to global one */
			list_add_tail(&gr->link, &mmc_test_result);

			/*
			 * Save the poपूर्णांकer to created container in our निजी
			 * काष्ठाure.
			 */
			test->gr = gr;
		पूर्ण

		ret = mmc_test_हालs[i].run(test);
		चयन (ret) अणु
		हाल RESULT_OK:
			pr_info("%s: Result: OK\n",
				mmc_hostname(test->card->host));
			अवरोध;
		हाल RESULT_FAIL:
			pr_info("%s: Result: FAILED\n",
				mmc_hostname(test->card->host));
			अवरोध;
		हाल RESULT_UNSUP_HOST:
			pr_info("%s: Result: UNSUPPORTED (by host)\n",
				mmc_hostname(test->card->host));
			अवरोध;
		हाल RESULT_UNSUP_CARD:
			pr_info("%s: Result: UNSUPPORTED (by card)\n",
				mmc_hostname(test->card->host));
			अवरोध;
		शेष:
			pr_info("%s: Result: ERROR (%d)\n",
				mmc_hostname(test->card->host), ret);
		पूर्ण

		/* Save the result */
		अगर (gr)
			gr->result = ret;

		अगर (mmc_test_हालs[i].cleanup) अणु
			ret = mmc_test_हालs[i].cleanup(test);
			अगर (ret) अणु
				pr_info("%s: Warning: Cleanup stage failed! (%d)\n",
					mmc_hostname(test->card->host),
					ret);
			पूर्ण
		पूर्ण
	पूर्ण

	mmc_release_host(test->card->host);

	pr_info("%s: Tests completed.\n",
		mmc_hostname(test->card->host));
पूर्ण

अटल व्योम mmc_test_मुक्त_result(काष्ठा mmc_card *card)
अणु
	काष्ठा mmc_test_general_result *gr, *grs;

	mutex_lock(&mmc_test_lock);

	list_क्रम_each_entry_safe(gr, grs, &mmc_test_result, link) अणु
		काष्ठा mmc_test_transfer_result *tr, *trs;

		अगर (card && gr->card != card)
			जारी;

		list_क्रम_each_entry_safe(tr, trs, &gr->tr_lst, link) अणु
			list_del(&tr->link);
			kमुक्त(tr);
		पूर्ण

		list_del(&gr->link);
		kमुक्त(gr);
	पूर्ण

	mutex_unlock(&mmc_test_lock);
पूर्ण

अटल LIST_HEAD(mmc_test_file_test);

अटल पूर्णांक mtf_test_show(काष्ठा seq_file *sf, व्योम *data)
अणु
	काष्ठा mmc_card *card = (काष्ठा mmc_card *)sf->निजी;
	काष्ठा mmc_test_general_result *gr;

	mutex_lock(&mmc_test_lock);

	list_क्रम_each_entry(gr, &mmc_test_result, link) अणु
		काष्ठा mmc_test_transfer_result *tr;

		अगर (gr->card != card)
			जारी;

		seq_म_लिखो(sf, "Test %d: %d\n", gr->testहाल + 1, gr->result);

		list_क्रम_each_entry(tr, &gr->tr_lst, link) अणु
			seq_म_लिखो(sf, "%u %d %llu.%09u %u %u.%02u\n",
				tr->count, tr->sectors,
				(u64)tr->ts.tv_sec, (u32)tr->ts.tv_nsec,
				tr->rate, tr->iops / 100, tr->iops % 100);
		पूर्ण
	पूर्ण

	mutex_unlock(&mmc_test_lock);

	वापस 0;
पूर्ण

अटल पूर्णांक mtf_test_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस single_खोलो(file, mtf_test_show, inode->i_निजी);
पूर्ण

अटल sमाप_प्रकार mtf_test_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf,
	माप_प्रकार count, loff_t *pos)
अणु
	काष्ठा seq_file *sf = (काष्ठा seq_file *)file->निजी_data;
	काष्ठा mmc_card *card = (काष्ठा mmc_card *)sf->निजी;
	काष्ठा mmc_test_card *test;
	दीर्घ testहाल;
	पूर्णांक ret;

	ret = kम_से_दीर्घ_from_user(buf, count, 10, &testहाल);
	अगर (ret)
		वापस ret;

	test = kzalloc(माप(*test), GFP_KERNEL);
	अगर (!test)
		वापस -ENOMEM;

	/*
	 * Remove all test हालs associated with given card. Thus we have only
	 * actual data of the last run.
	 */
	mmc_test_मुक्त_result(card);

	test->card = card;

	test->buffer = kzalloc(BUFFER_SIZE, GFP_KERNEL);
#अगर_घोषित CONFIG_HIGHMEM
	test->highmem = alloc_pages(GFP_KERNEL | __GFP_HIGHMEM, BUFFER_ORDER);
#पूर्ण_अगर

#अगर_घोषित CONFIG_HIGHMEM
	अगर (test->buffer && test->highmem) अणु
#अन्यथा
	अगर (test->buffer) अणु
#पूर्ण_अगर
		mutex_lock(&mmc_test_lock);
		mmc_test_run(test, testहाल);
		mutex_unlock(&mmc_test_lock);
	पूर्ण

#अगर_घोषित CONFIG_HIGHMEM
	__मुक्त_pages(test->highmem, BUFFER_ORDER);
#पूर्ण_अगर
	kमुक्त(test->buffer);
	kमुक्त(test);

	वापस count;
पूर्ण

अटल स्थिर काष्ठा file_operations mmc_test_fops_test = अणु
	.खोलो		= mtf_test_खोलो,
	.पढ़ो		= seq_पढ़ो,
	.ग_लिखो		= mtf_test_ग_लिखो,
	.llseek		= seq_lseek,
	.release	= single_release,
पूर्ण;

अटल पूर्णांक mtf_testlist_show(काष्ठा seq_file *sf, व्योम *data)
अणु
	पूर्णांक i;

	mutex_lock(&mmc_test_lock);

	seq_माला_दो(sf, "0:\tRun all tests\n");
	क्रम (i = 0; i < ARRAY_SIZE(mmc_test_हालs); i++)
		seq_म_लिखो(sf, "%d:\t%s\n", i + 1, mmc_test_हालs[i].name);

	mutex_unlock(&mmc_test_lock);

	वापस 0;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(mtf_testlist);

अटल व्योम mmc_test_मुक्त_dbgfs_file(काष्ठा mmc_card *card)
अणु
	काष्ठा mmc_test_dbgfs_file *df, *dfs;

	mutex_lock(&mmc_test_lock);

	list_क्रम_each_entry_safe(df, dfs, &mmc_test_file_test, link) अणु
		अगर (card && df->card != card)
			जारी;
		debugfs_हटाओ(df->file);
		list_del(&df->link);
		kमुक्त(df);
	पूर्ण

	mutex_unlock(&mmc_test_lock);
पूर्ण

अटल पूर्णांक __mmc_test_रेजिस्टर_dbgfs_file(काष्ठा mmc_card *card,
	स्थिर अक्षर *name, umode_t mode, स्थिर काष्ठा file_operations *fops)
अणु
	काष्ठा dentry *file = शून्य;
	काष्ठा mmc_test_dbgfs_file *df;

	अगर (card->debugfs_root)
		debugfs_create_file(name, mode, card->debugfs_root, card, fops);

	df = kदो_स्मृति(माप(*df), GFP_KERNEL);
	अगर (!df) अणु
		debugfs_हटाओ(file);
		वापस -ENOMEM;
	पूर्ण

	df->card = card;
	df->file = file;

	list_add(&df->link, &mmc_test_file_test);
	वापस 0;
पूर्ण

अटल पूर्णांक mmc_test_रेजिस्टर_dbgfs_file(काष्ठा mmc_card *card)
अणु
	पूर्णांक ret;

	mutex_lock(&mmc_test_lock);

	ret = __mmc_test_रेजिस्टर_dbgfs_file(card, "test", S_IWUSR | S_IRUGO,
		&mmc_test_fops_test);
	अगर (ret)
		जाओ err;

	ret = __mmc_test_रेजिस्टर_dbgfs_file(card, "testlist", S_IRUGO,
		&mtf_testlist_fops);
	अगर (ret)
		जाओ err;

err:
	mutex_unlock(&mmc_test_lock);

	वापस ret;
पूर्ण

अटल पूर्णांक mmc_test_probe(काष्ठा mmc_card *card)
अणु
	पूर्णांक ret;

	अगर (!mmc_card_mmc(card) && !mmc_card_sd(card))
		वापस -ENODEV;

	ret = mmc_test_रेजिस्टर_dbgfs_file(card);
	अगर (ret)
		वापस ret;

	अगर (card->ext_csd.cmdq_en) अणु
		mmc_claim_host(card->host);
		ret = mmc_cmdq_disable(card);
		mmc_release_host(card->host);
		अगर (ret)
			वापस ret;
	पूर्ण

	dev_info(&card->dev, "Card claimed for testing.\n");

	वापस 0;
पूर्ण

अटल व्योम mmc_test_हटाओ(काष्ठा mmc_card *card)
अणु
	अगर (card->reenable_cmdq) अणु
		mmc_claim_host(card->host);
		mmc_cmdq_enable(card);
		mmc_release_host(card->host);
	पूर्ण
	mmc_test_मुक्त_result(card);
	mmc_test_मुक्त_dbgfs_file(card);
पूर्ण

अटल काष्ठा mmc_driver mmc_driver = अणु
	.drv		= अणु
		.name	= "mmc_test",
	पूर्ण,
	.probe		= mmc_test_probe,
	.हटाओ		= mmc_test_हटाओ,
पूर्ण;

अटल पूर्णांक __init mmc_test_init(व्योम)
अणु
	वापस mmc_रेजिस्टर_driver(&mmc_driver);
पूर्ण

अटल व्योम __निकास mmc_test_निकास(व्योम)
अणु
	/* Clear stalled data अगर card is still plugged */
	mmc_test_मुक्त_result(शून्य);
	mmc_test_मुक्त_dbgfs_file(शून्य);

	mmc_unरेजिस्टर_driver(&mmc_driver);
पूर्ण

module_init(mmc_test_init);
module_निकास(mmc_test_निकास);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Multimedia Card (MMC) host test driver");
MODULE_AUTHOR("Pierre Ossman");
