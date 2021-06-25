<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_BADBLOCKS_H
#घोषणा _LINUX_BADBLOCKS_H

#समावेश <linux/seqlock.h>
#समावेश <linux/device.h>
#समावेश <linux/kernel.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/types.h>

#घोषणा BB_LEN_MASK	(0x00000000000001FFULL)
#घोषणा BB_OFFSET_MASK	(0x7FFFFFFFFFFFFE00ULL)
#घोषणा BB_ACK_MASK	(0x8000000000000000ULL)
#घोषणा BB_MAX_LEN	512
#घोषणा BB_OFFSET(x)	(((x) & BB_OFFSET_MASK) >> 9)
#घोषणा BB_LEN(x)	(((x) & BB_LEN_MASK) + 1)
#घोषणा BB_ACK(x)	(!!((x) & BB_ACK_MASK))
#घोषणा BB_MAKE(a, l, ack) (((a)<<9) | ((l)-1) | ((u64)(!!(ack)) << 63))

/* Bad block numbers are stored sorted in a single page.
 * 64bits is used क्रम each block or extent.
 * 54 bits are sector number, 9 bits are extent size,
 * 1 bit is an 'acknowledged' flag.
 */
#घोषणा MAX_BADBLOCKS	(PAGE_SIZE/8)

काष्ठा badblocks अणु
	काष्ठा device *dev;	/* set by devm_init_badblocks */
	पूर्णांक count;		/* count of bad blocks */
	पूर्णांक unacked_exist;	/* there probably are unacknowledged
				 * bad blocks.  This is only cleared
				 * when a पढ़ो discovers none
				 */
	पूर्णांक shअगरt;		/* shअगरt from sectors to block size
				 * a -ve shअगरt means badblocks are
				 * disabled.*/
	u64 *page;		/* badblock list */
	पूर्णांक changed;
	seqlock_t lock;
	sector_t sector;
	sector_t size;		/* in sectors */
पूर्ण;

पूर्णांक badblocks_check(काष्ठा badblocks *bb, sector_t s, पूर्णांक sectors,
		   sector_t *first_bad, पूर्णांक *bad_sectors);
पूर्णांक badblocks_set(काष्ठा badblocks *bb, sector_t s, पूर्णांक sectors,
			पूर्णांक acknowledged);
पूर्णांक badblocks_clear(काष्ठा badblocks *bb, sector_t s, पूर्णांक sectors);
व्योम ack_all_badblocks(काष्ठा badblocks *bb);
sमाप_प्रकार badblocks_show(काष्ठा badblocks *bb, अक्षर *page, पूर्णांक unack);
sमाप_प्रकार badblocks_store(काष्ठा badblocks *bb, स्थिर अक्षर *page, माप_प्रकार len,
			पूर्णांक unack);
पूर्णांक badblocks_init(काष्ठा badblocks *bb, पूर्णांक enable);
व्योम badblocks_निकास(काष्ठा badblocks *bb);
काष्ठा device;
पूर्णांक devm_init_badblocks(काष्ठा device *dev, काष्ठा badblocks *bb);
अटल अंतरभूत व्योम devm_निकास_badblocks(काष्ठा device *dev, काष्ठा badblocks *bb)
अणु
	अगर (bb->dev != dev) अणु
		dev_WARN_ONCE(dev, 1, "%s: badblocks instance not associated\n",
				__func__);
		वापस;
	पूर्ण
	badblocks_निकास(bb);
पूर्ण
#पूर्ण_अगर
