<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright तऊ 2009 - Maxim Levitsky
 * SmartMedia/xD translation layer
 *
 * Based loosly on ssfdc.c which is
 *  तऊ 2005 Eptar srl
 *  Author: Claudio Lanconelli <lanconelli.claudio@eptar.com>
 */

#समावेश <linux/mtd/blktrans.h>
#समावेश <linux/kfअगरo.h>
#समावेश <linux/sched.h>
#समावेश <linux/completion.h>
#समावेश <linux/mtd/mtd.h>



काष्ठा ftl_zone अणु
	bool initialized;
	पूर्णांक16_t *lba_to_phys_table;		/* LBA to physical table */
	काष्ठा kfअगरo मुक्त_sectors;	/* queue of मुक्त sectors */
पूर्ण;

काष्ठा sm_ftl अणु
	काष्ठा mtd_blktrans_dev *trans;

	काष्ठा mutex mutex;		/* protects the काष्ठाure */
	काष्ठा ftl_zone *zones;		/* FTL tables क्रम each zone */

	/* Media inक्रमmation */
	पूर्णांक block_size;			/* block size in bytes */
	पूर्णांक zone_size;			/* zone size in blocks */
	पूर्णांक zone_count;			/* number of zones */
	पूर्णांक max_lba;			/* maximum lba in a zone */
	पूर्णांक smallpagenand;		/* 256 bytes/page nand */
	bool पढ़ोonly;			/* is FS पढ़ोonly */
	bool unstable;
	पूर्णांक cis_block;			/* CIS block location */
	पूर्णांक cis_boffset;		/* CIS offset in the block */
	पूर्णांक cis_page_offset;		/* CIS offset in the page */
	व्योम *cis_buffer;		/* पंचांगp buffer क्रम cis पढ़ोs */

	/* Cache */
	पूर्णांक cache_block;		/* block number of cached block */
	पूर्णांक cache_zone;			/* zone of cached block */
	अचिन्हित अक्षर *cache_data;	/* cached block data */
	दीर्घ अचिन्हित पूर्णांक cache_data_invalid_biपंचांगap;
	bool cache_clean;
	काष्ठा work_काष्ठा flush_work;
	काष्ठा समयr_list समयr;

	/* Geometry stuff */
	पूर्णांक heads;
	पूर्णांक sectors;
	पूर्णांक cylinders;

	काष्ठा attribute_group *disk_attributes;
पूर्ण;

काष्ठा chs_entry अणु
	अचिन्हित दीर्घ size;
	अचिन्हित लघु cyl;
	अचिन्हित अक्षर head;
	अचिन्हित अक्षर sec;
पूर्ण;


#घोषणा SM_FTL_PARTN_BITS	3

#घोषणा sm_prपूर्णांकk(क्रमmat, ...) \
	prपूर्णांकk(KERN_WARNING "sm_ftl" ": " क्रमmat "\n", ## __VA_ARGS__)

#घोषणा dbg(क्रमmat, ...) \
	अगर (debug) \
		prपूर्णांकk(KERN_DEBUG "sm_ftl" ": " क्रमmat "\n", ## __VA_ARGS__)

#घोषणा dbg_verbose(क्रमmat, ...) \
	अगर (debug > 1) \
		prपूर्णांकk(KERN_DEBUG "sm_ftl" ": " क्रमmat "\n", ## __VA_ARGS__)


अटल पूर्णांक sm_erase_block(काष्ठा sm_ftl *ftl, पूर्णांक zone_num, uपूर्णांक16_t block,
								पूर्णांक put_मुक्त);
अटल व्योम sm_mark_block_bad(काष्ठा sm_ftl *ftl, पूर्णांक zone_num, पूर्णांक block);

अटल पूर्णांक sm_recheck_media(काष्ठा sm_ftl *ftl);
