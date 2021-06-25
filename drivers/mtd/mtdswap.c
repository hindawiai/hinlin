<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Swap block device support क्रम MTDs
 * Turns an MTD device पूर्णांकo a swap device with block wear leveling
 *
 * Copyright तऊ 2007,2011 Nokia Corporation. All rights reserved.
 *
 * Authors: Jarkko Lavinen <jarkko.lavinen@nokia.com>
 *
 * Based on Riअक्षरd Purdie's earlier implementation in 2007. Background
 * support and lock-less operation written by Adrian Hunter.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/blktrans.h>
#समावेश <linux/rbtree.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/genhd.h>
#समावेश <linux/swap.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/device.h>
#समावेश <linux/math64.h>

#घोषणा MTDSWAP_PREFIX "mtdswap"

/*
 * The number of मुक्त eraseblocks when GC should stop
 */
#घोषणा CLEAN_BLOCK_THRESHOLD	20

/*
 * Number of मुक्त eraseblocks below which GC can also collect low frag
 * blocks.
 */
#घोषणा LOW_FRAG_GC_THRESHOLD	5

/*
 * Wear level cost amortization. We want to करो wear leveling on the background
 * without disturbing gc too much. This is made by defining max GC frequency.
 * Frequency value 6 means 1/6 of the GC passes will pick an erase block based
 * on the biggest wear dअगरference rather than the biggest dirtiness.
 *
 * The lower freq2 should be chosen so that it makes sure the maximum erase
 * dअगरference will decrease even अगर a malicious application is deliberately
 * trying to make erase dअगरferences large.
 */
#घोषणा MAX_ERASE_DIFF		4000
#घोषणा COLLECT_NONसूचीTY_BASE	MAX_ERASE_DIFF
#घोषणा COLLECT_NONसूचीTY_FREQ1	6
#घोषणा COLLECT_NONसूचीTY_FREQ2	4

#घोषणा PAGE_UNDEF		अच_पूर्णांक_उच्च
#घोषणा BLOCK_UNDEF		अच_पूर्णांक_उच्च
#घोषणा BLOCK_ERROR		(अच_पूर्णांक_उच्च - 1)
#घोषणा BLOCK_MAX		(अच_पूर्णांक_उच्च - 2)

#घोषणा EBLOCK_BAD		(1 << 0)
#घोषणा EBLOCK_NOMAGIC		(1 << 1)
#घोषणा EBLOCK_BITFLIP		(1 << 2)
#घोषणा EBLOCK_FAILED		(1 << 3)
#घोषणा EBLOCK_READERR		(1 << 4)
#घोषणा EBLOCK_IDX_SHIFT	5

काष्ठा swap_eb अणु
	काष्ठा rb_node rb;
	काष्ठा rb_root *root;

	अचिन्हित पूर्णांक flags;
	अचिन्हित पूर्णांक active_count;
	अचिन्हित पूर्णांक erase_count;
	अचिन्हित पूर्णांक pad;		/* speeds up poपूर्णांकer decrement */
पूर्ण;

#घोषणा MTDSWAP_ECNT_MIN(rbroot) (rb_entry(rb_first(rbroot), काष्ठा swap_eb, \
				rb)->erase_count)
#घोषणा MTDSWAP_ECNT_MAX(rbroot) (rb_entry(rb_last(rbroot), काष्ठा swap_eb, \
				rb)->erase_count)

काष्ठा mtdswap_tree अणु
	काष्ठा rb_root root;
	अचिन्हित पूर्णांक count;
पूर्ण;

क्रमागत अणु
	MTDSWAP_CLEAN,
	MTDSWAP_USED,
	MTDSWAP_LOWFRAG,
	MTDSWAP_HIFRAG,
	MTDSWAP_सूचीTY,
	MTDSWAP_BITFLIP,
	MTDSWAP_FAILING,
	MTDSWAP_TREE_CNT,
पूर्ण;

काष्ठा mtdswap_dev अणु
	काष्ठा mtd_blktrans_dev *mbd_dev;
	काष्ठा mtd_info *mtd;
	काष्ठा device *dev;

	अचिन्हित पूर्णांक *page_data;
	अचिन्हित पूर्णांक *revmap;

	अचिन्हित पूर्णांक eblks;
	अचिन्हित पूर्णांक spare_eblks;
	अचिन्हित पूर्णांक pages_per_eblk;
	अचिन्हित पूर्णांक max_erase_count;
	काष्ठा swap_eb *eb_data;

	काष्ठा mtdswap_tree trees[MTDSWAP_TREE_CNT];

	अचिन्हित दीर्घ दीर्घ sect_पढ़ो_count;
	अचिन्हित दीर्घ दीर्घ sect_ग_लिखो_count;
	अचिन्हित दीर्घ दीर्घ mtd_ग_लिखो_count;
	अचिन्हित दीर्घ दीर्घ mtd_पढ़ो_count;
	अचिन्हित दीर्घ दीर्घ discard_count;
	अचिन्हित दीर्घ दीर्घ discard_page_count;

	अचिन्हित पूर्णांक curr_ग_लिखो_pos;
	काष्ठा swap_eb *curr_ग_लिखो;

	अक्षर *page_buf;
	अक्षर *oob_buf;
पूर्ण;

काष्ठा mtdswap_oobdata अणु
	__le16 magic;
	__le32 count;
पूर्ण __packed;

#घोषणा MTDSWAP_MAGIC_CLEAN	0x2095
#घोषणा MTDSWAP_MAGIC_सूचीTY	(MTDSWAP_MAGIC_CLEAN + 1)
#घोषणा MTDSWAP_TYPE_CLEAN	0
#घोषणा MTDSWAP_TYPE_सूचीTY	1
#घोषणा MTDSWAP_OOBSIZE		माप(काष्ठा mtdswap_oobdata)

#घोषणा MTDSWAP_ERASE_RETRIES	3 /* Beक्रमe marking erase block bad */
#घोषणा MTDSWAP_IO_RETRIES	3

क्रमागत अणु
	MTDSWAP_SCANNED_CLEAN,
	MTDSWAP_SCANNED_सूचीTY,
	MTDSWAP_SCANNED_BITFLIP,
	MTDSWAP_SCANNED_BAD,
पूर्ण;

/*
 * In the worst हाल mtdswap_ग_लिखोsect() has allocated the last clean
 * page from the current block and is then pre-empted by the GC
 * thपढ़ो. The thपढ़ो can consume a full erase block when moving a
 * block.
 */
#घोषणा MIN_SPARE_EBLOCKS	2
#घोषणा MIN_ERASE_BLOCKS	(MIN_SPARE_EBLOCKS + 1)

#घोषणा TREE_ROOT(d, name) (&d->trees[MTDSWAP_ ## name].root)
#घोषणा TREE_EMPTY(d, name) (TREE_ROOT(d, name)->rb_node == शून्य)
#घोषणा TREE_NONEMPTY(d, name) (!TREE_EMPTY(d, name))
#घोषणा TREE_COUNT(d, name) (d->trees[MTDSWAP_ ## name].count)

#घोषणा MTDSWAP_MBD_TO_MTDSWAP(dev) ((काष्ठा mtdswap_dev *)dev->priv)

अटल अक्षर partitions[128] = "";
module_param_string(partitions, partitions, माप(partitions), 0444);
MODULE_PARM_DESC(partitions, "MTD partition numbers to use as swap "
		"partitions=\"1,3,5\"");

अटल अचिन्हित पूर्णांक spare_eblocks = 10;
module_param(spare_eblocks, uपूर्णांक, 0444);
MODULE_PARM_DESC(spare_eblocks, "Percentage of spare erase blocks for "
		"garbage collection (default 10%)");

अटल bool header; /* false */
module_param(header, bool, 0444);
MODULE_PARM_DESC(header,
		"Include builtin swap header (default 0, without header)");

अटल पूर्णांक mtdswap_gc(काष्ठा mtdswap_dev *d, अचिन्हित पूर्णांक background);

अटल loff_t mtdswap_eb_offset(काष्ठा mtdswap_dev *d, काष्ठा swap_eb *eb)
अणु
	वापस (loff_t)(eb - d->eb_data) * d->mtd->erasesize;
पूर्ण

अटल व्योम mtdswap_eb_detach(काष्ठा mtdswap_dev *d, काष्ठा swap_eb *eb)
अणु
	अचिन्हित पूर्णांक oldidx;
	काष्ठा mtdswap_tree *tp;

	अगर (eb->root) अणु
		tp = container_of(eb->root, काष्ठा mtdswap_tree, root);
		oldidx = tp - &d->trees[0];

		d->trees[oldidx].count--;
		rb_erase(&eb->rb, eb->root);
	पूर्ण
पूर्ण

अटल व्योम __mtdswap_rb_add(काष्ठा rb_root *root, काष्ठा swap_eb *eb)
अणु
	काष्ठा rb_node **p, *parent = शून्य;
	काष्ठा swap_eb *cur;

	p = &root->rb_node;
	जबतक (*p) अणु
		parent = *p;
		cur = rb_entry(parent, काष्ठा swap_eb, rb);
		अगर (eb->erase_count > cur->erase_count)
			p = &(*p)->rb_right;
		अन्यथा
			p = &(*p)->rb_left;
	पूर्ण

	rb_link_node(&eb->rb, parent, p);
	rb_insert_color(&eb->rb, root);
पूर्ण

अटल व्योम mtdswap_rb_add(काष्ठा mtdswap_dev *d, काष्ठा swap_eb *eb, पूर्णांक idx)
अणु
	काष्ठा rb_root *root;

	अगर (eb->root == &d->trees[idx].root)
		वापस;

	mtdswap_eb_detach(d, eb);
	root = &d->trees[idx].root;
	__mtdswap_rb_add(root, eb);
	eb->root = root;
	d->trees[idx].count++;
पूर्ण

अटल काष्ठा rb_node *mtdswap_rb_index(काष्ठा rb_root *root, अचिन्हित पूर्णांक idx)
अणु
	काष्ठा rb_node *p;
	अचिन्हित पूर्णांक i;

	p = rb_first(root);
	i = 0;
	जबतक (i < idx && p) अणु
		p = rb_next(p);
		i++;
	पूर्ण

	वापस p;
पूर्ण

अटल पूर्णांक mtdswap_handle_badblock(काष्ठा mtdswap_dev *d, काष्ठा swap_eb *eb)
अणु
	पूर्णांक ret;
	loff_t offset;

	d->spare_eblks--;
	eb->flags |= EBLOCK_BAD;
	mtdswap_eb_detach(d, eb);
	eb->root = शून्य;

	/* badblocks not supported */
	अगर (!mtd_can_have_bb(d->mtd))
		वापस 1;

	offset = mtdswap_eb_offset(d, eb);
	dev_warn(d->dev, "Marking bad block at %08llx\n", offset);
	ret = mtd_block_markbad(d->mtd, offset);

	अगर (ret) अणु
		dev_warn(d->dev, "Mark block bad failed for block at %08llx "
			"error %d\n", offset, ret);
		वापस ret;
	पूर्ण

	वापस 1;

पूर्ण

अटल पूर्णांक mtdswap_handle_ग_लिखो_error(काष्ठा mtdswap_dev *d, काष्ठा swap_eb *eb)
अणु
	अचिन्हित पूर्णांक marked = eb->flags & EBLOCK_FAILED;
	काष्ठा swap_eb *curr_ग_लिखो = d->curr_ग_लिखो;

	eb->flags |= EBLOCK_FAILED;
	अगर (curr_ग_लिखो == eb) अणु
		d->curr_ग_लिखो = शून्य;

		अगर (!marked && d->curr_ग_लिखो_pos != 0) अणु
			mtdswap_rb_add(d, eb, MTDSWAP_FAILING);
			वापस 0;
		पूर्ण
	पूर्ण

	वापस mtdswap_handle_badblock(d, eb);
पूर्ण

अटल पूर्णांक mtdswap_पढ़ो_oob(काष्ठा mtdswap_dev *d, loff_t from,
			काष्ठा mtd_oob_ops *ops)
अणु
	पूर्णांक ret = mtd_पढ़ो_oob(d->mtd, from, ops);

	अगर (mtd_is_bitflip(ret))
		वापस ret;

	अगर (ret) अणु
		dev_warn(d->dev, "Read OOB failed %d for block at %08llx\n",
			ret, from);
		वापस ret;
	पूर्ण

	अगर (ops->oobretlen < ops->ooblen) अणु
		dev_warn(d->dev, "Read OOB return short read (%zd bytes not "
			"%zd) for block at %08llx\n",
			ops->oobretlen, ops->ooblen, from);
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mtdswap_पढ़ो_markers(काष्ठा mtdswap_dev *d, काष्ठा swap_eb *eb)
अणु
	काष्ठा mtdswap_oobdata *data, *data2;
	पूर्णांक ret;
	loff_t offset;
	काष्ठा mtd_oob_ops ops;

	offset = mtdswap_eb_offset(d, eb);

	/* Check first अगर the block is bad. */
	अगर (mtd_can_have_bb(d->mtd) && mtd_block_isbad(d->mtd, offset))
		वापस MTDSWAP_SCANNED_BAD;

	ops.ooblen = 2 * d->mtd->oobavail;
	ops.oobbuf = d->oob_buf;
	ops.ooboffs = 0;
	ops.datbuf = शून्य;
	ops.mode = MTD_OPS_AUTO_OOB;

	ret = mtdswap_पढ़ो_oob(d, offset, &ops);

	अगर (ret && !mtd_is_bitflip(ret))
		वापस ret;

	data = (काष्ठा mtdswap_oobdata *)d->oob_buf;
	data2 = (काष्ठा mtdswap_oobdata *)
		(d->oob_buf + d->mtd->oobavail);

	अगर (le16_to_cpu(data->magic) == MTDSWAP_MAGIC_CLEAN) अणु
		eb->erase_count = le32_to_cpu(data->count);
		अगर (mtd_is_bitflip(ret))
			ret = MTDSWAP_SCANNED_BITFLIP;
		अन्यथा अणु
			अगर (le16_to_cpu(data2->magic) == MTDSWAP_MAGIC_सूचीTY)
				ret = MTDSWAP_SCANNED_सूचीTY;
			अन्यथा
				ret = MTDSWAP_SCANNED_CLEAN;
		पूर्ण
	पूर्ण अन्यथा अणु
		eb->flags |= EBLOCK_NOMAGIC;
		ret = MTDSWAP_SCANNED_सूचीTY;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक mtdswap_ग_लिखो_marker(काष्ठा mtdswap_dev *d, काष्ठा swap_eb *eb,
				u16 marker)
अणु
	काष्ठा mtdswap_oobdata n;
	पूर्णांक ret;
	loff_t offset;
	काष्ठा mtd_oob_ops ops;

	ops.ooboffs = 0;
	ops.oobbuf = (uपूर्णांक8_t *)&n;
	ops.mode = MTD_OPS_AUTO_OOB;
	ops.datbuf = शून्य;

	अगर (marker == MTDSWAP_TYPE_CLEAN) अणु
		n.magic = cpu_to_le16(MTDSWAP_MAGIC_CLEAN);
		n.count = cpu_to_le32(eb->erase_count);
		ops.ooblen = MTDSWAP_OOBSIZE;
		offset = mtdswap_eb_offset(d, eb);
	पूर्ण अन्यथा अणु
		n.magic = cpu_to_le16(MTDSWAP_MAGIC_सूचीTY);
		ops.ooblen = माप(n.magic);
		offset = mtdswap_eb_offset(d, eb) + d->mtd->ग_लिखोsize;
	पूर्ण

	ret = mtd_ग_लिखो_oob(d->mtd, offset, &ops);

	अगर (ret) अणु
		dev_warn(d->dev, "Write OOB failed for block at %08llx "
			"error %d\n", offset, ret);
		अगर (ret == -EIO || mtd_is_eccerr(ret))
			mtdswap_handle_ग_लिखो_error(d, eb);
		वापस ret;
	पूर्ण

	अगर (ops.oobretlen != ops.ooblen) अणु
		dev_warn(d->dev, "Short OOB write for block at %08llx: "
			"%zd not %zd\n",
			offset, ops.oobretlen, ops.ooblen);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Are there any erase blocks without MAGIC_CLEAN header, presumably
 * because घातer was cut off after erase but beक्रमe header ग_लिखो? We
 * need to guestimate the erase count.
 */
अटल व्योम mtdswap_check_counts(काष्ठा mtdswap_dev *d)
अणु
	काष्ठा rb_root hist_root = RB_ROOT;
	काष्ठा rb_node *medrb;
	काष्ठा swap_eb *eb;
	अचिन्हित पूर्णांक i, cnt, median;

	cnt = 0;
	क्रम (i = 0; i < d->eblks; i++) अणु
		eb = d->eb_data + i;

		अगर (eb->flags & (EBLOCK_NOMAGIC | EBLOCK_BAD | EBLOCK_READERR))
			जारी;

		__mtdswap_rb_add(&hist_root, eb);
		cnt++;
	पूर्ण

	अगर (cnt == 0)
		वापस;

	medrb = mtdswap_rb_index(&hist_root, cnt / 2);
	median = rb_entry(medrb, काष्ठा swap_eb, rb)->erase_count;

	d->max_erase_count = MTDSWAP_ECNT_MAX(&hist_root);

	क्रम (i = 0; i < d->eblks; i++) अणु
		eb = d->eb_data + i;

		अगर (eb->flags & (EBLOCK_NOMAGIC | EBLOCK_READERR))
			eb->erase_count = median;

		अगर (eb->flags & (EBLOCK_NOMAGIC | EBLOCK_BAD | EBLOCK_READERR))
			जारी;

		rb_erase(&eb->rb, &hist_root);
	पूर्ण
पूर्ण

अटल व्योम mtdswap_scan_eblks(काष्ठा mtdswap_dev *d)
अणु
	पूर्णांक status;
	अचिन्हित पूर्णांक i, idx;
	काष्ठा swap_eb *eb;

	क्रम (i = 0; i < d->eblks; i++) अणु
		eb = d->eb_data + i;

		status = mtdswap_पढ़ो_markers(d, eb);
		अगर (status < 0)
			eb->flags |= EBLOCK_READERR;
		अन्यथा अगर (status == MTDSWAP_SCANNED_BAD) अणु
			eb->flags |= EBLOCK_BAD;
			जारी;
		पूर्ण

		चयन (status) अणु
		हाल MTDSWAP_SCANNED_CLEAN:
			idx = MTDSWAP_CLEAN;
			अवरोध;
		हाल MTDSWAP_SCANNED_सूचीTY:
		हाल MTDSWAP_SCANNED_BITFLIP:
			idx = MTDSWAP_सूचीTY;
			अवरोध;
		शेष:
			idx = MTDSWAP_FAILING;
		पूर्ण

		eb->flags |= (idx << EBLOCK_IDX_SHIFT);
	पूर्ण

	mtdswap_check_counts(d);

	क्रम (i = 0; i < d->eblks; i++) अणु
		eb = d->eb_data + i;

		अगर (eb->flags & EBLOCK_BAD)
			जारी;

		idx = eb->flags >> EBLOCK_IDX_SHIFT;
		mtdswap_rb_add(d, eb, idx);
	पूर्ण
पूर्ण

/*
 * Place eblk पूर्णांकo a tree corresponding to its number of active blocks
 * it contains.
 */
अटल व्योम mtdswap_store_eb(काष्ठा mtdswap_dev *d, काष्ठा swap_eb *eb)
अणु
	अचिन्हित पूर्णांक weight = eb->active_count;
	अचिन्हित पूर्णांक maxweight = d->pages_per_eblk;

	अगर (eb == d->curr_ग_लिखो)
		वापस;

	अगर (eb->flags & EBLOCK_BITFLIP)
		mtdswap_rb_add(d, eb, MTDSWAP_BITFLIP);
	अन्यथा अगर (eb->flags & (EBLOCK_READERR | EBLOCK_FAILED))
		mtdswap_rb_add(d, eb, MTDSWAP_FAILING);
	अगर (weight == maxweight)
		mtdswap_rb_add(d, eb, MTDSWAP_USED);
	अन्यथा अगर (weight == 0)
		mtdswap_rb_add(d, eb, MTDSWAP_सूचीTY);
	अन्यथा अगर (weight > (maxweight/2))
		mtdswap_rb_add(d, eb, MTDSWAP_LOWFRAG);
	अन्यथा
		mtdswap_rb_add(d, eb, MTDSWAP_HIFRAG);
पूर्ण

अटल पूर्णांक mtdswap_erase_block(काष्ठा mtdswap_dev *d, काष्ठा swap_eb *eb)
अणु
	काष्ठा mtd_info *mtd = d->mtd;
	काष्ठा erase_info erase;
	अचिन्हित पूर्णांक retries = 0;
	पूर्णांक ret;

	eb->erase_count++;
	अगर (eb->erase_count > d->max_erase_count)
		d->max_erase_count = eb->erase_count;

retry:
	स_रखो(&erase, 0, माप(काष्ठा erase_info));
	erase.addr	= mtdswap_eb_offset(d, eb);
	erase.len	= mtd->erasesize;

	ret = mtd_erase(mtd, &erase);
	अगर (ret) अणु
		अगर (retries++ < MTDSWAP_ERASE_RETRIES) अणु
			dev_warn(d->dev,
				"erase of erase block %#llx on %s failed",
				erase.addr, mtd->name);
			yield();
			जाओ retry;
		पूर्ण

		dev_err(d->dev, "Cannot erase erase block %#llx on %s\n",
			erase.addr, mtd->name);

		mtdswap_handle_badblock(d, eb);
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mtdswap_map_मुक्त_block(काष्ठा mtdswap_dev *d, अचिन्हित पूर्णांक page,
				अचिन्हित पूर्णांक *block)
अणु
	पूर्णांक ret;
	काष्ठा swap_eb *old_eb = d->curr_ग_लिखो;
	काष्ठा rb_root *clean_root;
	काष्ठा swap_eb *eb;

	अगर (old_eb == शून्य || d->curr_ग_लिखो_pos >= d->pages_per_eblk) अणु
		करो अणु
			अगर (TREE_EMPTY(d, CLEAN))
				वापस -ENOSPC;

			clean_root = TREE_ROOT(d, CLEAN);
			eb = rb_entry(rb_first(clean_root), काष्ठा swap_eb, rb);
			rb_erase(&eb->rb, clean_root);
			eb->root = शून्य;
			TREE_COUNT(d, CLEAN)--;

			ret = mtdswap_ग_लिखो_marker(d, eb, MTDSWAP_TYPE_सूचीTY);
		पूर्ण जबतक (ret == -EIO || mtd_is_eccerr(ret));

		अगर (ret)
			वापस ret;

		d->curr_ग_लिखो_pos = 0;
		d->curr_ग_लिखो = eb;
		अगर (old_eb)
			mtdswap_store_eb(d, old_eb);
	पूर्ण

	*block = (d->curr_ग_लिखो - d->eb_data) * d->pages_per_eblk +
		d->curr_ग_लिखो_pos;

	d->curr_ग_लिखो->active_count++;
	d->revmap[*block] = page;
	d->curr_ग_लिखो_pos++;

	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक mtdswap_मुक्त_page_cnt(काष्ठा mtdswap_dev *d)
अणु
	वापस TREE_COUNT(d, CLEAN) * d->pages_per_eblk +
		d->pages_per_eblk - d->curr_ग_लिखो_pos;
पूर्ण

अटल अचिन्हित पूर्णांक mtdswap_enough_मुक्त_pages(काष्ठा mtdswap_dev *d)
अणु
	वापस mtdswap_मुक्त_page_cnt(d) > d->pages_per_eblk;
पूर्ण

अटल पूर्णांक mtdswap_ग_लिखो_block(काष्ठा mtdswap_dev *d, अक्षर *buf,
			अचिन्हित पूर्णांक page, अचिन्हित पूर्णांक *bp, पूर्णांक gc_context)
अणु
	काष्ठा mtd_info *mtd = d->mtd;
	काष्ठा swap_eb *eb;
	माप_प्रकार retlen;
	loff_t ग_लिखोpos;
	पूर्णांक ret;

retry:
	अगर (!gc_context)
		जबतक (!mtdswap_enough_मुक्त_pages(d))
			अगर (mtdswap_gc(d, 0) > 0)
				वापस -ENOSPC;

	ret = mtdswap_map_मुक्त_block(d, page, bp);
	eb = d->eb_data + (*bp / d->pages_per_eblk);

	अगर (ret == -EIO || mtd_is_eccerr(ret)) अणु
		d->curr_ग_लिखो = शून्य;
		eb->active_count--;
		d->revmap[*bp] = PAGE_UNDEF;
		जाओ retry;
	पूर्ण

	अगर (ret < 0)
		वापस ret;

	ग_लिखोpos = (loff_t)*bp << PAGE_SHIFT;
	ret =  mtd_ग_लिखो(mtd, ग_लिखोpos, PAGE_SIZE, &retlen, buf);
	अगर (ret == -EIO || mtd_is_eccerr(ret)) अणु
		d->curr_ग_लिखो_pos--;
		eb->active_count--;
		d->revmap[*bp] = PAGE_UNDEF;
		mtdswap_handle_ग_लिखो_error(d, eb);
		जाओ retry;
	पूर्ण

	अगर (ret < 0) अणु
		dev_err(d->dev, "Write to MTD device failed: %d (%zd written)",
			ret, retlen);
		जाओ err;
	पूर्ण

	अगर (retlen != PAGE_SIZE) अणु
		dev_err(d->dev, "Short write to MTD device: %zd written",
			retlen);
		ret = -EIO;
		जाओ err;
	पूर्ण

	वापस ret;

err:
	d->curr_ग_लिखो_pos--;
	eb->active_count--;
	d->revmap[*bp] = PAGE_UNDEF;

	वापस ret;
पूर्ण

अटल पूर्णांक mtdswap_move_block(काष्ठा mtdswap_dev *d, अचिन्हित पूर्णांक oldblock,
		अचिन्हित पूर्णांक *newblock)
अणु
	काष्ठा mtd_info *mtd = d->mtd;
	काष्ठा swap_eb *eb, *oldeb;
	पूर्णांक ret;
	माप_प्रकार retlen;
	अचिन्हित पूर्णांक page, retries;
	loff_t पढ़ोpos;

	page = d->revmap[oldblock];
	पढ़ोpos = (loff_t) oldblock << PAGE_SHIFT;
	retries = 0;

retry:
	ret = mtd_पढ़ो(mtd, पढ़ोpos, PAGE_SIZE, &retlen, d->page_buf);

	अगर (ret < 0 && !mtd_is_bitflip(ret)) अणु
		oldeb = d->eb_data + oldblock / d->pages_per_eblk;
		oldeb->flags |= EBLOCK_READERR;

		dev_err(d->dev, "Read Error: %d (block %u)\n", ret,
			oldblock);
		retries++;
		अगर (retries < MTDSWAP_IO_RETRIES)
			जाओ retry;

		जाओ पढ़ो_error;
	पूर्ण

	अगर (retlen != PAGE_SIZE) अणु
		dev_err(d->dev, "Short read: %zd (block %u)\n", retlen,
		       oldblock);
		ret = -EIO;
		जाओ पढ़ो_error;
	पूर्ण

	ret = mtdswap_ग_लिखो_block(d, d->page_buf, page, newblock, 1);
	अगर (ret < 0) अणु
		d->page_data[page] = BLOCK_ERROR;
		dev_err(d->dev, "Write error: %d\n", ret);
		वापस ret;
	पूर्ण

	eb = d->eb_data + *newblock / d->pages_per_eblk;
	d->page_data[page] = *newblock;
	d->revmap[oldblock] = PAGE_UNDEF;
	eb = d->eb_data + oldblock / d->pages_per_eblk;
	eb->active_count--;

	वापस 0;

पढ़ो_error:
	d->page_data[page] = BLOCK_ERROR;
	d->revmap[oldblock] = PAGE_UNDEF;
	वापस ret;
पूर्ण

अटल पूर्णांक mtdswap_gc_eblock(काष्ठा mtdswap_dev *d, काष्ठा swap_eb *eb)
अणु
	अचिन्हित पूर्णांक i, block, eblk_base, newblock;
	पूर्णांक ret, errcode;

	errcode = 0;
	eblk_base = (eb - d->eb_data) * d->pages_per_eblk;

	क्रम (i = 0; i < d->pages_per_eblk; i++) अणु
		अगर (d->spare_eblks < MIN_SPARE_EBLOCKS)
			वापस -ENOSPC;

		block = eblk_base + i;
		अगर (d->revmap[block] == PAGE_UNDEF)
			जारी;

		ret = mtdswap_move_block(d, block, &newblock);
		अगर (ret < 0 && !errcode)
			errcode = ret;
	पूर्ण

	वापस errcode;
पूर्ण

अटल पूर्णांक __mtdswap_choose_gc_tree(काष्ठा mtdswap_dev *d)
अणु
	पूर्णांक idx, stopat;

	अगर (TREE_COUNT(d, CLEAN) < LOW_FRAG_GC_THRESHOLD)
		stopat = MTDSWAP_LOWFRAG;
	अन्यथा
		stopat = MTDSWAP_HIFRAG;

	क्रम (idx = MTDSWAP_BITFLIP; idx >= stopat; idx--)
		अगर (d->trees[idx].root.rb_node != शून्य)
			वापस idx;

	वापस -1;
पूर्ण

अटल पूर्णांक mtdswap_wlfreq(अचिन्हित पूर्णांक maxdअगरf)
अणु
	अचिन्हित पूर्णांक h, x, y, dist, base;

	/*
	 * Calculate linear ramp करोwn from f1 to f2 when maxdअगरf goes from
	 * MAX_ERASE_DIFF to MAX_ERASE_DIFF + COLLECT_NONसूचीTY_BASE.  Similar
	 * to triangle with height f1 - f1 and width COLLECT_NONसूचीTY_BASE.
	 */

	dist = maxdअगरf - MAX_ERASE_DIFF;
	अगर (dist > COLLECT_NONसूचीTY_BASE)
		dist = COLLECT_NONसूचीTY_BASE;

	/*
	 * Modelling the slop as right angular triangle with base
	 * COLLECT_NONसूचीTY_BASE and height freq1 - freq2. The ratio y/x is
	 * equal to the ratio h/base.
	 */
	h = COLLECT_NONसूचीTY_FREQ1 - COLLECT_NONसूचीTY_FREQ2;
	base = COLLECT_NONसूचीTY_BASE;

	x = dist - base;
	y = (x * h + base / 2) / base;

	वापस COLLECT_NONसूचीTY_FREQ2 + y;
पूर्ण

अटल पूर्णांक mtdswap_choose_wl_tree(काष्ठा mtdswap_dev *d)
अणु
	अटल अचिन्हित पूर्णांक pick_cnt;
	अचिन्हित पूर्णांक i, idx = -1, wear, max;
	काष्ठा rb_root *root;

	max = 0;
	क्रम (i = 0; i <= MTDSWAP_सूचीTY; i++) अणु
		root = &d->trees[i].root;
		अगर (root->rb_node == शून्य)
			जारी;

		wear = d->max_erase_count - MTDSWAP_ECNT_MIN(root);
		अगर (wear > max) अणु
			max = wear;
			idx = i;
		पूर्ण
	पूर्ण

	अगर (max > MAX_ERASE_DIFF && pick_cnt >= mtdswap_wlfreq(max) - 1) अणु
		pick_cnt = 0;
		वापस idx;
	पूर्ण

	pick_cnt++;
	वापस -1;
पूर्ण

अटल पूर्णांक mtdswap_choose_gc_tree(काष्ठा mtdswap_dev *d,
				अचिन्हित पूर्णांक background)
अणु
	पूर्णांक idx;

	अगर (TREE_NONEMPTY(d, FAILING) &&
		(background || (TREE_EMPTY(d, CLEAN) && TREE_EMPTY(d, सूचीTY))))
		वापस MTDSWAP_FAILING;

	idx = mtdswap_choose_wl_tree(d);
	अगर (idx >= MTDSWAP_CLEAN)
		वापस idx;

	वापस __mtdswap_choose_gc_tree(d);
पूर्ण

अटल काष्ठा swap_eb *mtdswap_pick_gc_eblk(काष्ठा mtdswap_dev *d,
					अचिन्हित पूर्णांक background)
अणु
	काष्ठा rb_root *rp = शून्य;
	काष्ठा swap_eb *eb = शून्य;
	पूर्णांक idx;

	अगर (background && TREE_COUNT(d, CLEAN) > CLEAN_BLOCK_THRESHOLD &&
		TREE_EMPTY(d, सूचीTY) && TREE_EMPTY(d, FAILING))
		वापस शून्य;

	idx = mtdswap_choose_gc_tree(d, background);
	अगर (idx < 0)
		वापस शून्य;

	rp = &d->trees[idx].root;
	eb = rb_entry(rb_first(rp), काष्ठा swap_eb, rb);

	rb_erase(&eb->rb, rp);
	eb->root = शून्य;
	d->trees[idx].count--;
	वापस eb;
पूर्ण

अटल अचिन्हित पूर्णांक mtdswap_test_patt(अचिन्हित पूर्णांक i)
अणु
	वापस i % 2 ? 0x55555555 : 0xAAAAAAAA;
पूर्ण

अटल अचिन्हित पूर्णांक mtdswap_eblk_passes(काष्ठा mtdswap_dev *d,
					काष्ठा swap_eb *eb)
अणु
	काष्ठा mtd_info *mtd = d->mtd;
	अचिन्हित पूर्णांक test, i, j, patt, mtd_pages;
	loff_t base, pos;
	अचिन्हित पूर्णांक *p1 = (अचिन्हित पूर्णांक *)d->page_buf;
	अचिन्हित अक्षर *p2 = (अचिन्हित अक्षर *)d->oob_buf;
	काष्ठा mtd_oob_ops ops;
	पूर्णांक ret;

	ops.mode = MTD_OPS_AUTO_OOB;
	ops.len = mtd->ग_लिखोsize;
	ops.ooblen = mtd->oobavail;
	ops.ooboffs = 0;
	ops.datbuf = d->page_buf;
	ops.oobbuf = d->oob_buf;
	base = mtdswap_eb_offset(d, eb);
	mtd_pages = d->pages_per_eblk * PAGE_SIZE / mtd->ग_लिखोsize;

	क्रम (test = 0; test < 2; test++) अणु
		pos = base;
		क्रम (i = 0; i < mtd_pages; i++) अणु
			patt = mtdswap_test_patt(test + i);
			स_रखो(d->page_buf, patt, mtd->ग_लिखोsize);
			स_रखो(d->oob_buf, patt, mtd->oobavail);
			ret = mtd_ग_लिखो_oob(mtd, pos, &ops);
			अगर (ret)
				जाओ error;

			pos += mtd->ग_लिखोsize;
		पूर्ण

		pos = base;
		क्रम (i = 0; i < mtd_pages; i++) अणु
			ret = mtd_पढ़ो_oob(mtd, pos, &ops);
			अगर (ret)
				जाओ error;

			patt = mtdswap_test_patt(test + i);
			क्रम (j = 0; j < mtd->ग_लिखोsize/माप(पूर्णांक); j++)
				अगर (p1[j] != patt)
					जाओ error;

			क्रम (j = 0; j < mtd->oobavail; j++)
				अगर (p2[j] != (अचिन्हित अक्षर)patt)
					जाओ error;

			pos += mtd->ग_लिखोsize;
		पूर्ण

		ret = mtdswap_erase_block(d, eb);
		अगर (ret)
			जाओ error;
	पूर्ण

	eb->flags &= ~EBLOCK_READERR;
	वापस 1;

error:
	mtdswap_handle_badblock(d, eb);
	वापस 0;
पूर्ण

अटल पूर्णांक mtdswap_gc(काष्ठा mtdswap_dev *d, अचिन्हित पूर्णांक background)
अणु
	काष्ठा swap_eb *eb;
	पूर्णांक ret;

	अगर (d->spare_eblks < MIN_SPARE_EBLOCKS)
		वापस 1;

	eb = mtdswap_pick_gc_eblk(d, background);
	अगर (!eb)
		वापस 1;

	ret = mtdswap_gc_eblock(d, eb);
	अगर (ret == -ENOSPC)
		वापस 1;

	अगर (eb->flags & EBLOCK_FAILED) अणु
		mtdswap_handle_badblock(d, eb);
		वापस 0;
	पूर्ण

	eb->flags &= ~EBLOCK_BITFLIP;
	ret = mtdswap_erase_block(d, eb);
	अगर ((eb->flags & EBLOCK_READERR) &&
		(ret || !mtdswap_eblk_passes(d, eb)))
		वापस 0;

	अगर (ret == 0)
		ret = mtdswap_ग_लिखो_marker(d, eb, MTDSWAP_TYPE_CLEAN);

	अगर (ret == 0)
		mtdswap_rb_add(d, eb, MTDSWAP_CLEAN);
	अन्यथा अगर (ret != -EIO && !mtd_is_eccerr(ret))
		mtdswap_rb_add(d, eb, MTDSWAP_सूचीTY);

	वापस 0;
पूर्ण

अटल व्योम mtdswap_background(काष्ठा mtd_blktrans_dev *dev)
अणु
	काष्ठा mtdswap_dev *d = MTDSWAP_MBD_TO_MTDSWAP(dev);
	पूर्णांक ret;

	जबतक (1) अणु
		ret = mtdswap_gc(d, 1);
		अगर (ret || mtd_blktrans_cease_background(dev))
			वापस;
	पूर्ण
पूर्ण

अटल व्योम mtdswap_cleanup(काष्ठा mtdswap_dev *d)
अणु
	vमुक्त(d->eb_data);
	vमुक्त(d->revmap);
	vमुक्त(d->page_data);
	kमुक्त(d->oob_buf);
	kमुक्त(d->page_buf);
पूर्ण

अटल पूर्णांक mtdswap_flush(काष्ठा mtd_blktrans_dev *dev)
अणु
	काष्ठा mtdswap_dev *d = MTDSWAP_MBD_TO_MTDSWAP(dev);

	mtd_sync(d->mtd);
	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक mtdswap_badblocks(काष्ठा mtd_info *mtd, uपूर्णांक64_t size)
अणु
	loff_t offset;
	अचिन्हित पूर्णांक badcnt;

	badcnt = 0;

	अगर (mtd_can_have_bb(mtd))
		क्रम (offset = 0; offset < size; offset += mtd->erasesize)
			अगर (mtd_block_isbad(mtd, offset))
				badcnt++;

	वापस badcnt;
पूर्ण

अटल पूर्णांक mtdswap_ग_लिखोsect(काष्ठा mtd_blktrans_dev *dev,
			अचिन्हित दीर्घ page, अक्षर *buf)
अणु
	काष्ठा mtdswap_dev *d = MTDSWAP_MBD_TO_MTDSWAP(dev);
	अचिन्हित पूर्णांक newblock, mapped;
	काष्ठा swap_eb *eb;
	पूर्णांक ret;

	d->sect_ग_लिखो_count++;

	अगर (d->spare_eblks < MIN_SPARE_EBLOCKS)
		वापस -ENOSPC;

	अगर (header) अणु
		/* Ignore ग_लिखोs to the header page */
		अगर (unlikely(page == 0))
			वापस 0;

		page--;
	पूर्ण

	mapped = d->page_data[page];
	अगर (mapped <= BLOCK_MAX) अणु
		eb = d->eb_data + (mapped / d->pages_per_eblk);
		eb->active_count--;
		mtdswap_store_eb(d, eb);
		d->page_data[page] = BLOCK_UNDEF;
		d->revmap[mapped] = PAGE_UNDEF;
	पूर्ण

	ret = mtdswap_ग_लिखो_block(d, buf, page, &newblock, 0);
	d->mtd_ग_लिखो_count++;

	अगर (ret < 0)
		वापस ret;

	d->page_data[page] = newblock;

	वापस 0;
पूर्ण

/* Provide a dummy swap header क्रम the kernel */
अटल पूर्णांक mtdswap_स्वतः_header(काष्ठा mtdswap_dev *d, अक्षर *buf)
अणु
	जोड़ swap_header *hd = (जोड़ swap_header *)(buf);

	स_रखो(buf, 0, PAGE_SIZE - 10);

	hd->info.version = 1;
	hd->info.last_page = d->mbd_dev->size - 1;
	hd->info.nr_badpages = 0;

	स_नकल(buf + PAGE_SIZE - 10, "SWAPSPACE2", 10);

	वापस 0;
पूर्ण

अटल पूर्णांक mtdswap_पढ़ोsect(काष्ठा mtd_blktrans_dev *dev,
			अचिन्हित दीर्घ page, अक्षर *buf)
अणु
	काष्ठा mtdswap_dev *d = MTDSWAP_MBD_TO_MTDSWAP(dev);
	काष्ठा mtd_info *mtd = d->mtd;
	अचिन्हित पूर्णांक realblock, retries;
	loff_t पढ़ोpos;
	काष्ठा swap_eb *eb;
	माप_प्रकार retlen;
	पूर्णांक ret;

	d->sect_पढ़ो_count++;

	अगर (header) अणु
		अगर (unlikely(page == 0))
			वापस mtdswap_स्वतः_header(d, buf);

		page--;
	पूर्ण

	realblock = d->page_data[page];
	अगर (realblock > BLOCK_MAX) अणु
		स_रखो(buf, 0x0, PAGE_SIZE);
		अगर (realblock == BLOCK_UNDEF)
			वापस 0;
		अन्यथा
			वापस -EIO;
	पूर्ण

	eb = d->eb_data + (realblock / d->pages_per_eblk);
	BUG_ON(d->revmap[realblock] == PAGE_UNDEF);

	पढ़ोpos = (loff_t)realblock << PAGE_SHIFT;
	retries = 0;

retry:
	ret = mtd_पढ़ो(mtd, पढ़ोpos, PAGE_SIZE, &retlen, buf);

	d->mtd_पढ़ो_count++;
	अगर (mtd_is_bitflip(ret)) अणु
		eb->flags |= EBLOCK_BITFLIP;
		mtdswap_rb_add(d, eb, MTDSWAP_BITFLIP);
		ret = 0;
	पूर्ण

	अगर (ret < 0) अणु
		dev_err(d->dev, "Read error %d\n", ret);
		eb->flags |= EBLOCK_READERR;
		mtdswap_rb_add(d, eb, MTDSWAP_FAILING);
		retries++;
		अगर (retries < MTDSWAP_IO_RETRIES)
			जाओ retry;

		वापस ret;
	पूर्ण

	अगर (retlen != PAGE_SIZE) अणु
		dev_err(d->dev, "Short read %zd\n", retlen);
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mtdswap_discard(काष्ठा mtd_blktrans_dev *dev, अचिन्हित दीर्घ first,
			अचिन्हित nr_pages)
अणु
	काष्ठा mtdswap_dev *d = MTDSWAP_MBD_TO_MTDSWAP(dev);
	अचिन्हित दीर्घ page;
	काष्ठा swap_eb *eb;
	अचिन्हित पूर्णांक mapped;

	d->discard_count++;

	क्रम (page = first; page < first + nr_pages; page++) अणु
		mapped = d->page_data[page];
		अगर (mapped <= BLOCK_MAX) अणु
			eb = d->eb_data + (mapped / d->pages_per_eblk);
			eb->active_count--;
			mtdswap_store_eb(d, eb);
			d->page_data[page] = BLOCK_UNDEF;
			d->revmap[mapped] = PAGE_UNDEF;
			d->discard_page_count++;
		पूर्ण अन्यथा अगर (mapped == BLOCK_ERROR) अणु
			d->page_data[page] = BLOCK_UNDEF;
			d->discard_page_count++;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mtdswap_show(काष्ठा seq_file *s, व्योम *data)
अणु
	काष्ठा mtdswap_dev *d = (काष्ठा mtdswap_dev *) s->निजी;
	अचिन्हित दीर्घ sum;
	अचिन्हित पूर्णांक count[MTDSWAP_TREE_CNT];
	अचिन्हित पूर्णांक min[MTDSWAP_TREE_CNT];
	अचिन्हित पूर्णांक max[MTDSWAP_TREE_CNT];
	अचिन्हित पूर्णांक i, cw = 0, cwp = 0, cwecount = 0, bb_cnt, mapped, pages;
	uपूर्णांक64_t use_size;
	अटल स्थिर अक्षर * स्थिर name[] = अणु
		"clean", "used", "low", "high", "dirty", "bitflip", "failing"
	पूर्ण;

	mutex_lock(&d->mbd_dev->lock);

	क्रम (i = 0; i < MTDSWAP_TREE_CNT; i++) अणु
		काष्ठा rb_root *root = &d->trees[i].root;

		अगर (root->rb_node) अणु
			count[i] = d->trees[i].count;
			min[i] = MTDSWAP_ECNT_MIN(root);
			max[i] = MTDSWAP_ECNT_MAX(root);
		पूर्ण अन्यथा
			count[i] = 0;
	पूर्ण

	अगर (d->curr_ग_लिखो) अणु
		cw = 1;
		cwp = d->curr_ग_लिखो_pos;
		cwecount = d->curr_ग_लिखो->erase_count;
	पूर्ण

	sum = 0;
	क्रम (i = 0; i < d->eblks; i++)
		sum += d->eb_data[i].erase_count;

	use_size = (uपूर्णांक64_t)d->eblks * d->mtd->erasesize;
	bb_cnt = mtdswap_badblocks(d->mtd, use_size);

	mapped = 0;
	pages = d->mbd_dev->size;
	क्रम (i = 0; i < pages; i++)
		अगर (d->page_data[i] != BLOCK_UNDEF)
			mapped++;

	mutex_unlock(&d->mbd_dev->lock);

	क्रम (i = 0; i < MTDSWAP_TREE_CNT; i++) अणु
		अगर (!count[i])
			जारी;

		अगर (min[i] != max[i])
			seq_म_लिखो(s, "%s:\t%5d erase blocks, erased min %d, "
				"max %d times\n",
				name[i], count[i], min[i], max[i]);
		अन्यथा
			seq_म_लिखो(s, "%s:\t%5d erase blocks, all erased %d "
				"times\n", name[i], count[i], min[i]);
	पूर्ण

	अगर (bb_cnt)
		seq_म_लिखो(s, "bad:\t%5u erase blocks\n", bb_cnt);

	अगर (cw)
		seq_म_लिखो(s, "current erase block: %u pages used, %u free, "
			"erased %u times\n",
			cwp, d->pages_per_eblk - cwp, cwecount);

	seq_म_लिखो(s, "total erasures: %lu\n", sum);

	seq_माला_दो(s, "\n");

	seq_म_लिखो(s, "mtdswap_readsect count: %llu\n", d->sect_पढ़ो_count);
	seq_म_लिखो(s, "mtdswap_writesect count: %llu\n", d->sect_ग_लिखो_count);
	seq_म_लिखो(s, "mtdswap_discard count: %llu\n", d->discard_count);
	seq_म_लिखो(s, "mtd read count: %llu\n", d->mtd_पढ़ो_count);
	seq_म_लिखो(s, "mtd write count: %llu\n", d->mtd_ग_लिखो_count);
	seq_म_लिखो(s, "discarded pages count: %llu\n", d->discard_page_count);

	seq_माला_दो(s, "\n");
	seq_म_लिखो(s, "total pages: %u\n", pages);
	seq_म_लिखो(s, "pages mapped: %u\n", mapped);

	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(mtdswap);

अटल पूर्णांक mtdswap_add_debugfs(काष्ठा mtdswap_dev *d)
अणु
	काष्ठा dentry *root = d->mtd->dbg.dfs_dir;

	अगर (!IS_ENABLED(CONFIG_DEBUG_FS))
		वापस 0;

	अगर (IS_ERR_OR_शून्य(root))
		वापस -1;

	debugfs_create_file("mtdswap_stats", S_IRUSR, root, d, &mtdswap_fops);

	वापस 0;
पूर्ण

अटल पूर्णांक mtdswap_init(काष्ठा mtdswap_dev *d, अचिन्हित पूर्णांक eblocks,
			अचिन्हित पूर्णांक spare_cnt)
अणु
	काष्ठा mtd_info *mtd = d->mbd_dev->mtd;
	अचिन्हित पूर्णांक i, eblk_bytes, pages, blocks;
	पूर्णांक ret = -ENOMEM;

	d->mtd = mtd;
	d->eblks = eblocks;
	d->spare_eblks = spare_cnt;
	d->pages_per_eblk = mtd->erasesize >> PAGE_SHIFT;

	pages = d->mbd_dev->size;
	blocks = eblocks * d->pages_per_eblk;

	क्रम (i = 0; i < MTDSWAP_TREE_CNT; i++)
		d->trees[i].root = RB_ROOT;

	d->page_data = vदो_स्मृति(array_size(pages, माप(पूर्णांक)));
	अगर (!d->page_data)
		जाओ page_data_fail;

	d->revmap = vदो_स्मृति(array_size(blocks, माप(पूर्णांक)));
	अगर (!d->revmap)
		जाओ revmap_fail;

	eblk_bytes = माप(काष्ठा swap_eb)*d->eblks;
	d->eb_data = vzalloc(eblk_bytes);
	अगर (!d->eb_data)
		जाओ eb_data_fail;

	क्रम (i = 0; i < pages; i++)
		d->page_data[i] = BLOCK_UNDEF;

	क्रम (i = 0; i < blocks; i++)
		d->revmap[i] = PAGE_UNDEF;

	d->page_buf = kदो_स्मृति(PAGE_SIZE, GFP_KERNEL);
	अगर (!d->page_buf)
		जाओ page_buf_fail;

	d->oob_buf = kदो_स्मृति_array(2, mtd->oobavail, GFP_KERNEL);
	अगर (!d->oob_buf)
		जाओ oob_buf_fail;

	mtdswap_scan_eblks(d);

	वापस 0;

oob_buf_fail:
	kमुक्त(d->page_buf);
page_buf_fail:
	vमुक्त(d->eb_data);
eb_data_fail:
	vमुक्त(d->revmap);
revmap_fail:
	vमुक्त(d->page_data);
page_data_fail:
	prपूर्णांकk(KERN_ERR "%s: init failed (%d)\n", MTDSWAP_PREFIX, ret);
	वापस ret;
पूर्ण

अटल व्योम mtdswap_add_mtd(काष्ठा mtd_blktrans_ops *tr, काष्ठा mtd_info *mtd)
अणु
	काष्ठा mtdswap_dev *d;
	काष्ठा mtd_blktrans_dev *mbd_dev;
	अक्षर *parts;
	अक्षर *this_opt;
	अचिन्हित दीर्घ part;
	अचिन्हित पूर्णांक eblocks, eavailable, bad_blocks, spare_cnt;
	uपूर्णांक64_t swap_size, use_size, size_limit;
	पूर्णांक ret;

	parts = &partitions[0];
	अगर (!*parts)
		वापस;

	जबतक ((this_opt = strsep(&parts, ",")) != शून्य) अणु
		अगर (kम_से_अदीर्घ(this_opt, 0, &part) < 0)
			वापस;

		अगर (mtd->index == part)
			अवरोध;
	पूर्ण

	अगर (mtd->index != part)
		वापस;

	अगर (mtd->erasesize < PAGE_SIZE || mtd->erasesize % PAGE_SIZE) अणु
		prपूर्णांकk(KERN_ERR "%s: Erase size %u not multiple of PAGE_SIZE "
			"%lu\n", MTDSWAP_PREFIX, mtd->erasesize, PAGE_SIZE);
		वापस;
	पूर्ण

	अगर (PAGE_SIZE % mtd->ग_लिखोsize || mtd->ग_लिखोsize > PAGE_SIZE) अणु
		prपूर्णांकk(KERN_ERR "%s: PAGE_SIZE %lu not multiple of write size"
			" %u\n", MTDSWAP_PREFIX, PAGE_SIZE, mtd->ग_लिखोsize);
		वापस;
	पूर्ण

	अगर (!mtd->oobsize || mtd->oobavail < MTDSWAP_OOBSIZE) अणु
		prपूर्णांकk(KERN_ERR "%s: Not enough free bytes in OOB, "
			"%d available, %zu needed.\n",
			MTDSWAP_PREFIX, mtd->oobavail, MTDSWAP_OOBSIZE);
		वापस;
	पूर्ण

	अगर (spare_eblocks > 100)
		spare_eblocks = 100;

	use_size = mtd->size;
	size_limit = (uपूर्णांक64_t) BLOCK_MAX * PAGE_SIZE;

	अगर (mtd->size > size_limit) अणु
		prपूर्णांकk(KERN_WARNING "%s: Device too large. Limiting size to "
			"%llu bytes\n", MTDSWAP_PREFIX, size_limit);
		use_size = size_limit;
	पूर्ण

	eblocks = mtd_भाग_by_eb(use_size, mtd);
	use_size = (uपूर्णांक64_t)eblocks * mtd->erasesize;
	bad_blocks = mtdswap_badblocks(mtd, use_size);
	eavailable = eblocks - bad_blocks;

	अगर (eavailable < MIN_ERASE_BLOCKS) अणु
		prपूर्णांकk(KERN_ERR "%s: Not enough erase blocks. %u available, "
			"%d needed\n", MTDSWAP_PREFIX, eavailable,
			MIN_ERASE_BLOCKS);
		वापस;
	पूर्ण

	spare_cnt = भाग_u64((uपूर्णांक64_t)eavailable * spare_eblocks, 100);

	अगर (spare_cnt < MIN_SPARE_EBLOCKS)
		spare_cnt = MIN_SPARE_EBLOCKS;

	अगर (spare_cnt > eavailable - 1)
		spare_cnt = eavailable - 1;

	swap_size = (uपूर्णांक64_t)(eavailable - spare_cnt) * mtd->erasesize +
		(header ? PAGE_SIZE : 0);

	prपूर्णांकk(KERN_INFO "%s: Enabling MTD swap on device %lu, size %llu KB, "
		"%u spare, %u bad blocks\n",
		MTDSWAP_PREFIX, part, swap_size / 1024, spare_cnt, bad_blocks);

	d = kzalloc(माप(काष्ठा mtdswap_dev), GFP_KERNEL);
	अगर (!d)
		वापस;

	mbd_dev = kzalloc(माप(काष्ठा mtd_blktrans_dev), GFP_KERNEL);
	अगर (!mbd_dev) अणु
		kमुक्त(d);
		वापस;
	पूर्ण

	d->mbd_dev = mbd_dev;
	mbd_dev->priv = d;

	mbd_dev->mtd = mtd;
	mbd_dev->devnum = mtd->index;
	mbd_dev->size = swap_size >> PAGE_SHIFT;
	mbd_dev->tr = tr;

	अगर (!(mtd->flags & MTD_WRITEABLE))
		mbd_dev->पढ़ोonly = 1;

	अगर (mtdswap_init(d, eblocks, spare_cnt) < 0)
		जाओ init_failed;

	अगर (add_mtd_blktrans_dev(mbd_dev) < 0)
		जाओ cleanup;

	d->dev = disk_to_dev(mbd_dev->disk);

	ret = mtdswap_add_debugfs(d);
	अगर (ret < 0)
		जाओ debugfs_failed;

	वापस;

debugfs_failed:
	del_mtd_blktrans_dev(mbd_dev);

cleanup:
	mtdswap_cleanup(d);

init_failed:
	kमुक्त(mbd_dev);
	kमुक्त(d);
पूर्ण

अटल व्योम mtdswap_हटाओ_dev(काष्ठा mtd_blktrans_dev *dev)
अणु
	काष्ठा mtdswap_dev *d = MTDSWAP_MBD_TO_MTDSWAP(dev);

	del_mtd_blktrans_dev(dev);
	mtdswap_cleanup(d);
	kमुक्त(d);
पूर्ण

अटल काष्ठा mtd_blktrans_ops mtdswap_ops = अणु
	.name		= "mtdswap",
	.major		= 0,
	.part_bits	= 0,
	.blksize	= PAGE_SIZE,
	.flush		= mtdswap_flush,
	.पढ़ोsect	= mtdswap_पढ़ोsect,
	.ग_लिखोsect	= mtdswap_ग_लिखोsect,
	.discard	= mtdswap_discard,
	.background	= mtdswap_background,
	.add_mtd	= mtdswap_add_mtd,
	.हटाओ_dev	= mtdswap_हटाओ_dev,
	.owner		= THIS_MODULE,
पूर्ण;

module_mtd_blktrans(mtdswap_ops);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Jarkko Lavinen <jarkko.lavinen@nokia.com>");
MODULE_DESCRIPTION("Block device access to an MTD suitable for using as "
		"swap space");
