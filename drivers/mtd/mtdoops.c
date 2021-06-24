<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * MTD Oops/Panic logger
 *
 * Copyright तऊ 2007 Nokia Corporation. All rights reserved.
 *
 * Author: Riअक्षरd Purdie <rpurdie@खोलोedhand.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/console.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/sched.h>
#समावेश <linux/रुको.h>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/kmsg_dump.h>

/* Maximum MTD partition size */
#घोषणा MTDOOPS_MAX_MTD_SIZE (8 * 1024 * 1024)

#घोषणा MTDOOPS_KERNMSG_MAGIC 0x5d005d00
#घोषणा MTDOOPS_HEADER_SIZE   8

अटल अचिन्हित दीर्घ record_size = 4096;
module_param(record_size, uदीर्घ, 0400);
MODULE_PARM_DESC(record_size,
		"record size for MTD OOPS pages in bytes (default 4096)");

अटल अक्षर mtddev[80];
module_param_string(mtddev, mtddev, 80, 0400);
MODULE_PARM_DESC(mtddev,
		"name or index number of the MTD device to use");

अटल पूर्णांक dump_oops = 1;
module_param(dump_oops, पूर्णांक, 0600);
MODULE_PARM_DESC(dump_oops,
		"set to 1 to dump oopses, 0 to only dump panics (default 1)");

अटल काष्ठा mtकरोops_context अणु
	काष्ठा kmsg_dumper dump;

	पूर्णांक mtd_index;
	काष्ठा work_काष्ठा work_erase;
	काष्ठा work_काष्ठा work_ग_लिखो;
	काष्ठा mtd_info *mtd;
	पूर्णांक oops_pages;
	पूर्णांक nextpage;
	पूर्णांक nextcount;
	अचिन्हित दीर्घ *oops_page_used;

	अचिन्हित दीर्घ oops_buf_busy;
	व्योम *oops_buf;
पूर्ण oops_cxt;

अटल व्योम mark_page_used(काष्ठा mtकरोops_context *cxt, पूर्णांक page)
अणु
	set_bit(page, cxt->oops_page_used);
पूर्ण

अटल व्योम mark_page_unused(काष्ठा mtकरोops_context *cxt, पूर्णांक page)
अणु
	clear_bit(page, cxt->oops_page_used);
पूर्ण

अटल पूर्णांक page_is_used(काष्ठा mtकरोops_context *cxt, पूर्णांक page)
अणु
	वापस test_bit(page, cxt->oops_page_used);
पूर्ण

अटल पूर्णांक mtकरोops_erase_block(काष्ठा mtकरोops_context *cxt, पूर्णांक offset)
अणु
	काष्ठा mtd_info *mtd = cxt->mtd;
	u32 start_page_offset = mtd_भाग_by_eb(offset, mtd) * mtd->erasesize;
	u32 start_page = start_page_offset / record_size;
	u32 erase_pages = mtd->erasesize / record_size;
	काष्ठा erase_info erase;
	पूर्णांक ret;
	पूर्णांक page;

	erase.addr = offset;
	erase.len = mtd->erasesize;

	ret = mtd_erase(mtd, &erase);
	अगर (ret) अणु
		prपूर्णांकk(KERN_WARNING "mtdoops: erase of region [0x%llx, 0x%llx] on \"%s\" failed\n",
		       (अचिन्हित दीर्घ दीर्घ)erase.addr,
		       (अचिन्हित दीर्घ दीर्घ)erase.len, mtddev);
		वापस ret;
	पूर्ण

	/* Mark pages as unused */
	क्रम (page = start_page; page < start_page + erase_pages; page++)
		mark_page_unused(cxt, page);

	वापस 0;
पूर्ण

अटल व्योम mtकरोops_inc_counter(काष्ठा mtकरोops_context *cxt)
अणु
	cxt->nextpage++;
	अगर (cxt->nextpage >= cxt->oops_pages)
		cxt->nextpage = 0;
	cxt->nextcount++;
	अगर (cxt->nextcount == 0xffffffff)
		cxt->nextcount = 0;

	अगर (page_is_used(cxt, cxt->nextpage)) अणु
		schedule_work(&cxt->work_erase);
		वापस;
	पूर्ण

	prपूर्णांकk(KERN_DEBUG "mtdoops: ready %d, %d (no erase)\n",
	       cxt->nextpage, cxt->nextcount);
पूर्ण

/* Scheduled work - when we can't proceed without erasing a block */
अटल व्योम mtकरोops_workfunc_erase(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा mtकरोops_context *cxt =
			container_of(work, काष्ठा mtकरोops_context, work_erase);
	काष्ठा mtd_info *mtd = cxt->mtd;
	पूर्णांक i = 0, j, ret, mod;

	/* We were unरेजिस्टरed */
	अगर (!mtd)
		वापस;

	mod = (cxt->nextpage * record_size) % mtd->erasesize;
	अगर (mod != 0) अणु
		cxt->nextpage = cxt->nextpage + ((mtd->erasesize - mod) / record_size);
		अगर (cxt->nextpage >= cxt->oops_pages)
			cxt->nextpage = 0;
	पूर्ण

	जबतक ((ret = mtd_block_isbad(mtd, cxt->nextpage * record_size)) > 0) अणु
badblock:
		prपूर्णांकk(KERN_WARNING "mtdoops: bad block at %08lx\n",
		       cxt->nextpage * record_size);
		i++;
		cxt->nextpage = cxt->nextpage + (mtd->erasesize / record_size);
		अगर (cxt->nextpage >= cxt->oops_pages)
			cxt->nextpage = 0;
		अगर (i == cxt->oops_pages / (mtd->erasesize / record_size)) अणु
			prपूर्णांकk(KERN_ERR "mtdoops: all blocks bad!\n");
			वापस;
		पूर्ण
	पूर्ण

	अगर (ret < 0) अणु
		prपूर्णांकk(KERN_ERR "mtdoops: mtd_block_isbad failed, aborting\n");
		वापस;
	पूर्ण

	क्रम (j = 0, ret = -1; (j < 3) && (ret < 0); j++)
		ret = mtकरोops_erase_block(cxt, cxt->nextpage * record_size);

	अगर (ret >= 0) अणु
		prपूर्णांकk(KERN_DEBUG "mtdoops: ready %d, %d\n",
		       cxt->nextpage, cxt->nextcount);
		वापस;
	पूर्ण

	अगर (ret == -EIO) अणु
		ret = mtd_block_markbad(mtd, cxt->nextpage * record_size);
		अगर (ret < 0 && ret != -EOPNOTSUPP) अणु
			prपूर्णांकk(KERN_ERR "mtdoops: block_markbad failed, aborting\n");
			वापस;
		पूर्ण
	पूर्ण
	जाओ badblock;
पूर्ण

अटल व्योम mtकरोops_ग_लिखो(काष्ठा mtकरोops_context *cxt, पूर्णांक panic)
अणु
	काष्ठा mtd_info *mtd = cxt->mtd;
	माप_प्रकार retlen;
	u32 *hdr;
	पूर्णांक ret;

	अगर (test_and_set_bit(0, &cxt->oops_buf_busy))
		वापस;

	/* Add mtकरोops header to the buffer */
	hdr = cxt->oops_buf;
	hdr[0] = cxt->nextcount;
	hdr[1] = MTDOOPS_KERNMSG_MAGIC;

	अगर (panic) अणु
		ret = mtd_panic_ग_लिखो(mtd, cxt->nextpage * record_size,
				      record_size, &retlen, cxt->oops_buf);
		अगर (ret == -EOPNOTSUPP) अणु
			prपूर्णांकk(KERN_ERR "mtdoops: Cannot write from panic without panic_write\n");
			जाओ out;
		पूर्ण
	पूर्ण अन्यथा
		ret = mtd_ग_लिखो(mtd, cxt->nextpage * record_size,
				record_size, &retlen, cxt->oops_buf);

	अगर (retlen != record_size || ret < 0)
		prपूर्णांकk(KERN_ERR "mtdoops: write failure at %ld (%td of %ld written), error %d\n",
		       cxt->nextpage * record_size, retlen, record_size, ret);
	mark_page_used(cxt, cxt->nextpage);
	स_रखो(cxt->oops_buf, 0xff, record_size);

	mtकरोops_inc_counter(cxt);
out:
	clear_bit(0, &cxt->oops_buf_busy);
पूर्ण

अटल व्योम mtकरोops_workfunc_ग_लिखो(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा mtकरोops_context *cxt =
			container_of(work, काष्ठा mtकरोops_context, work_ग_लिखो);

	mtकरोops_ग_लिखो(cxt, 0);
पूर्ण

अटल व्योम find_next_position(काष्ठा mtकरोops_context *cxt)
अणु
	काष्ठा mtd_info *mtd = cxt->mtd;
	पूर्णांक ret, page, maxpos = 0;
	u32 count[2], maxcount = 0xffffffff;
	माप_प्रकार retlen;

	क्रम (page = 0; page < cxt->oops_pages; page++) अणु
		अगर (mtd_block_isbad(mtd, page * record_size))
			जारी;
		/* Assume the page is used */
		mark_page_used(cxt, page);
		ret = mtd_पढ़ो(mtd, page * record_size, MTDOOPS_HEADER_SIZE,
			       &retlen, (u_अक्षर *)&count[0]);
		अगर (retlen != MTDOOPS_HEADER_SIZE ||
				(ret < 0 && !mtd_is_bitflip(ret))) अणु
			prपूर्णांकk(KERN_ERR "mtdoops: read failure at %ld (%td of %d read), err %d\n",
			       page * record_size, retlen,
			       MTDOOPS_HEADER_SIZE, ret);
			जारी;
		पूर्ण

		अगर (count[0] == 0xffffffff && count[1] == 0xffffffff)
			mark_page_unused(cxt, page);
		अगर (count[0] == 0xffffffff || count[1] != MTDOOPS_KERNMSG_MAGIC)
			जारी;
		अगर (maxcount == 0xffffffff) अणु
			maxcount = count[0];
			maxpos = page;
		पूर्ण अन्यथा अगर (count[0] < 0x40000000 && maxcount > 0xc0000000) अणु
			maxcount = count[0];
			maxpos = page;
		पूर्ण अन्यथा अगर (count[0] > maxcount && count[0] < 0xc0000000) अणु
			maxcount = count[0];
			maxpos = page;
		पूर्ण अन्यथा अगर (count[0] > maxcount && count[0] > 0xc0000000
					&& maxcount > 0x80000000) अणु
			maxcount = count[0];
			maxpos = page;
		पूर्ण
	पूर्ण
	अगर (maxcount == 0xffffffff) अणु
		cxt->nextpage = cxt->oops_pages - 1;
		cxt->nextcount = 0;
	पूर्ण
	अन्यथा अणु
		cxt->nextpage = maxpos;
		cxt->nextcount = maxcount;
	पूर्ण

	mtकरोops_inc_counter(cxt);
पूर्ण

अटल व्योम mtकरोops_करो_dump(काष्ठा kmsg_dumper *dumper,
			    क्रमागत kmsg_dump_reason reason)
अणु
	काष्ठा mtकरोops_context *cxt = container_of(dumper,
			काष्ठा mtकरोops_context, dump);
	काष्ठा kmsg_dump_iter iter;

	/* Only dump oopses अगर dump_oops is set */
	अगर (reason == KMSG_DUMP_OOPS && !dump_oops)
		वापस;

	kmsg_dump_शुरुआत(&iter);

	अगर (test_and_set_bit(0, &cxt->oops_buf_busy))
		वापस;
	kmsg_dump_get_buffer(&iter, true, cxt->oops_buf + MTDOOPS_HEADER_SIZE,
			     record_size - MTDOOPS_HEADER_SIZE, शून्य);
	clear_bit(0, &cxt->oops_buf_busy);

	अगर (reason != KMSG_DUMP_OOPS) अणु
		/* Panics must be written immediately */
		mtकरोops_ग_लिखो(cxt, 1);
	पूर्ण अन्यथा अणु
		/* For other हालs, schedule work to ग_लिखो it "nicely" */
		schedule_work(&cxt->work_ग_लिखो);
	पूर्ण
पूर्ण

अटल व्योम mtकरोops_notअगरy_add(काष्ठा mtd_info *mtd)
अणु
	काष्ठा mtकरोops_context *cxt = &oops_cxt;
	u64 mtकरोops_pages = भाग_u64(mtd->size, record_size);
	पूर्णांक err;

	अगर (!म_भेद(mtd->name, mtddev))
		cxt->mtd_index = mtd->index;

	अगर (mtd->index != cxt->mtd_index || cxt->mtd_index < 0)
		वापस;

	अगर (mtd->size < mtd->erasesize * 2) अणु
		prपूर्णांकk(KERN_ERR "mtdoops: MTD partition %d not big enough for mtdoops\n",
		       mtd->index);
		वापस;
	पूर्ण
	अगर (mtd->erasesize < record_size) अणु
		prपूर्णांकk(KERN_ERR "mtdoops: eraseblock size of MTD partition %d too small\n",
		       mtd->index);
		वापस;
	पूर्ण
	अगर (mtd->size > MTDOOPS_MAX_MTD_SIZE) अणु
		prपूर्णांकk(KERN_ERR "mtdoops: mtd%d is too large (limit is %d MiB)\n",
		       mtd->index, MTDOOPS_MAX_MTD_SIZE / 1024 / 1024);
		वापस;
	पूर्ण

	/* oops_page_used is a bit field */
	cxt->oops_page_used =
		vदो_स्मृति(array_size(माप(अचिन्हित दीर्घ),
				   DIV_ROUND_UP(mtकरोops_pages,
						BITS_PER_LONG)));
	अगर (!cxt->oops_page_used) अणु
		prपूर्णांकk(KERN_ERR "mtdoops: could not allocate page array\n");
		वापस;
	पूर्ण

	cxt->dump.max_reason = KMSG_DUMP_OOPS;
	cxt->dump.dump = mtकरोops_करो_dump;
	err = kmsg_dump_रेजिस्टर(&cxt->dump);
	अगर (err) अणु
		prपूर्णांकk(KERN_ERR "mtdoops: registering kmsg dumper failed, error %d\n", err);
		vमुक्त(cxt->oops_page_used);
		cxt->oops_page_used = शून्य;
		वापस;
	पूर्ण

	cxt->mtd = mtd;
	cxt->oops_pages = (पूर्णांक)mtd->size / record_size;
	find_next_position(cxt);
	prपूर्णांकk(KERN_INFO "mtdoops: Attached to MTD device %d\n", mtd->index);
पूर्ण

अटल व्योम mtकरोops_notअगरy_हटाओ(काष्ठा mtd_info *mtd)
अणु
	काष्ठा mtकरोops_context *cxt = &oops_cxt;

	अगर (mtd->index != cxt->mtd_index || cxt->mtd_index < 0)
		वापस;

	अगर (kmsg_dump_unरेजिस्टर(&cxt->dump) < 0)
		prपूर्णांकk(KERN_WARNING "mtdoops: could not unregister kmsg_dumper\n");

	cxt->mtd = शून्य;
	flush_work(&cxt->work_erase);
	flush_work(&cxt->work_ग_लिखो);
पूर्ण


अटल काष्ठा mtd_notअगरier mtकरोops_notअगरier = अणु
	.add	= mtकरोops_notअगरy_add,
	.हटाओ	= mtकरोops_notअगरy_हटाओ,
पूर्ण;

अटल पूर्णांक __init mtकरोops_init(व्योम)
अणु
	काष्ठा mtकरोops_context *cxt = &oops_cxt;
	पूर्णांक mtd_index;
	अक्षर *endp;

	अगर (म_माप(mtddev) == 0) अणु
		prपूर्णांकk(KERN_ERR "mtdoops: mtd device (mtddev=name/number) must be supplied\n");
		वापस -EINVAL;
	पूर्ण
	अगर ((record_size & 4095) != 0) अणु
		prपूर्णांकk(KERN_ERR "mtdoops: record_size must be a multiple of 4096\n");
		वापस -EINVAL;
	पूर्ण
	अगर (record_size < 4096) अणु
		prपूर्णांकk(KERN_ERR "mtdoops: record_size must be over 4096 bytes\n");
		वापस -EINVAL;
	पूर्ण

	/* Setup the MTD device to use */
	cxt->mtd_index = -1;
	mtd_index = simple_म_से_अदीर्घ(mtddev, &endp, 0);
	अगर (*endp == '\0')
		cxt->mtd_index = mtd_index;

	cxt->oops_buf = vदो_स्मृति(record_size);
	अगर (!cxt->oops_buf) अणु
		prपूर्णांकk(KERN_ERR "mtdoops: failed to allocate buffer workspace\n");
		वापस -ENOMEM;
	पूर्ण
	स_रखो(cxt->oops_buf, 0xff, record_size);
	cxt->oops_buf_busy = 0;

	INIT_WORK(&cxt->work_erase, mtकरोops_workfunc_erase);
	INIT_WORK(&cxt->work_ग_लिखो, mtकरोops_workfunc_ग_लिखो);

	रेजिस्टर_mtd_user(&mtकरोops_notअगरier);
	वापस 0;
पूर्ण

अटल व्योम __निकास mtकरोops_निकास(व्योम)
अणु
	काष्ठा mtकरोops_context *cxt = &oops_cxt;

	unरेजिस्टर_mtd_user(&mtकरोops_notअगरier);
	vमुक्त(cxt->oops_buf);
	vमुक्त(cxt->oops_page_used);
पूर्ण


module_init(mtकरोops_init);
module_निकास(mtकरोops_निकास);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Richard Purdie <rpurdie@openedhand.com>");
MODULE_DESCRIPTION("MTD Oops/Panic console logger/driver");
