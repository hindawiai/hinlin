<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  linux/fs/hpfs/buffer.c
 *
 *  Mikulas Patocka (mikulas@artax.karlin.mff.cuni.cz), 1998-1999
 *
 *  general buffer i/o
 */
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/blkdev.h>
#समावेश "hpfs_fn.h"

secno hpfs_search_hotfix_map(काष्ठा super_block *s, secno sec)
अणु
	अचिन्हित i;
	काष्ठा hpfs_sb_info *sbi = hpfs_sb(s);
	क्रम (i = 0; unlikely(i < sbi->n_hotfixes); i++) अणु
		अगर (sbi->hotfix_from[i] == sec) अणु
			वापस sbi->hotfix_to[i];
		पूर्ण
	पूर्ण
	वापस sec;
पूर्ण

अचिन्हित hpfs_search_hotfix_map_क्रम_range(काष्ठा super_block *s, secno sec, अचिन्हित n)
अणु
	अचिन्हित i;
	काष्ठा hpfs_sb_info *sbi = hpfs_sb(s);
	क्रम (i = 0; unlikely(i < sbi->n_hotfixes); i++) अणु
		अगर (sbi->hotfix_from[i] >= sec && sbi->hotfix_from[i] < sec + n) अणु
			n = sbi->hotfix_from[i] - sec;
		पूर्ण
	पूर्ण
	वापस n;
पूर्ण

व्योम hpfs_prefetch_sectors(काष्ठा super_block *s, अचिन्हित secno, पूर्णांक n)
अणु
	काष्ठा buffer_head *bh;
	काष्ठा blk_plug plug;

	अगर (n <= 0 || unlikely(secno >= hpfs_sb(s)->sb_fs_size))
		वापस;

	अगर (unlikely(hpfs_search_hotfix_map_क्रम_range(s, secno, n) != n))
		वापस;

	bh = sb_find_get_block(s, secno);
	अगर (bh) अणु
		अगर (buffer_uptodate(bh)) अणु
			brअन्यथा(bh);
			वापस;
		पूर्ण
		brअन्यथा(bh);
	पूर्ण

	blk_start_plug(&plug);
	जबतक (n > 0) अणु
		अगर (unlikely(secno >= hpfs_sb(s)->sb_fs_size))
			अवरोध;
		sb_bपढ़ोahead(s, secno);
		secno++;
		n--;
	पूर्ण
	blk_finish_plug(&plug);
पूर्ण

/* Map a sector पूर्णांकo a buffer and वापस poपूर्णांकers to it and to the buffer. */

व्योम *hpfs_map_sector(काष्ठा super_block *s, अचिन्हित secno, काष्ठा buffer_head **bhp,
		 पूर्णांक ahead)
अणु
	काष्ठा buffer_head *bh;

	hpfs_lock_निश्चित(s);

	hpfs_prefetch_sectors(s, secno, ahead);

	cond_resched();

	*bhp = bh = sb_bपढ़ो(s, hpfs_search_hotfix_map(s, secno));
	अगर (bh != शून्य)
		वापस bh->b_data;
	अन्यथा अणु
		pr_err("%s(): read error\n", __func__);
		वापस शून्य;
	पूर्ण
पूर्ण

/* Like hpfs_map_sector but करोn't पढ़ो anything */

व्योम *hpfs_get_sector(काष्ठा super_block *s, अचिन्हित secno, काष्ठा buffer_head **bhp)
अणु
	काष्ठा buffer_head *bh;
	/*वापस hpfs_map_sector(s, secno, bhp, 0);*/

	hpfs_lock_निश्चित(s);

	cond_resched();

	अगर ((*bhp = bh = sb_getblk(s, hpfs_search_hotfix_map(s, secno))) != शून्य) अणु
		अगर (!buffer_uptodate(bh)) रुको_on_buffer(bh);
		set_buffer_uptodate(bh);
		वापस bh->b_data;
	पूर्ण अन्यथा अणु
		pr_err("%s(): getblk failed\n", __func__);
		वापस शून्य;
	पूर्ण
पूर्ण

/* Map 4 sectors पूर्णांकo a 4buffer and वापस poपूर्णांकers to it and to the buffer. */

व्योम *hpfs_map_4sectors(काष्ठा super_block *s, अचिन्हित secno, काष्ठा quad_buffer_head *qbh,
		   पूर्णांक ahead)
अणु
	अक्षर *data;

	hpfs_lock_निश्चित(s);

	cond_resched();

	अगर (secno & 3) अणु
		pr_err("%s(): unaligned read\n", __func__);
		वापस शून्य;
	पूर्ण

	hpfs_prefetch_sectors(s, secno, 4 + ahead);

	अगर (!hpfs_map_sector(s, secno + 0, &qbh->bh[0], 0)) जाओ bail0;
	अगर (!hpfs_map_sector(s, secno + 1, &qbh->bh[1], 0)) जाओ bail1;
	अगर (!hpfs_map_sector(s, secno + 2, &qbh->bh[2], 0)) जाओ bail2;
	अगर (!hpfs_map_sector(s, secno + 3, &qbh->bh[3], 0)) जाओ bail3;

	अगर (likely(qbh->bh[1]->b_data == qbh->bh[0]->b_data + 1 * 512) &&
	    likely(qbh->bh[2]->b_data == qbh->bh[0]->b_data + 2 * 512) &&
	    likely(qbh->bh[3]->b_data == qbh->bh[0]->b_data + 3 * 512)) अणु
		वापस qbh->data = qbh->bh[0]->b_data;
	पूर्ण

	qbh->data = data = kदो_स्मृति(2048, GFP_NOFS);
	अगर (!data) अणु
		pr_err("%s(): out of memory\n", __func__);
		जाओ bail4;
	पूर्ण

	स_नकल(data + 0 * 512, qbh->bh[0]->b_data, 512);
	स_नकल(data + 1 * 512, qbh->bh[1]->b_data, 512);
	स_नकल(data + 2 * 512, qbh->bh[2]->b_data, 512);
	स_नकल(data + 3 * 512, qbh->bh[3]->b_data, 512);

	वापस data;

 bail4:
	brअन्यथा(qbh->bh[3]);
 bail3:
	brअन्यथा(qbh->bh[2]);
 bail2:
	brअन्यथा(qbh->bh[1]);
 bail1:
	brअन्यथा(qbh->bh[0]);
 bail0:
	वापस शून्य;
पूर्ण

/* Don't पढ़ो sectors */

व्योम *hpfs_get_4sectors(काष्ठा super_block *s, अचिन्हित secno,
                          काष्ठा quad_buffer_head *qbh)
अणु
	cond_resched();

	hpfs_lock_निश्चित(s);

	अगर (secno & 3) अणु
		pr_err("%s(): unaligned read\n", __func__);
		वापस शून्य;
	पूर्ण

	अगर (!hpfs_get_sector(s, secno + 0, &qbh->bh[0])) जाओ bail0;
	अगर (!hpfs_get_sector(s, secno + 1, &qbh->bh[1])) जाओ bail1;
	अगर (!hpfs_get_sector(s, secno + 2, &qbh->bh[2])) जाओ bail2;
	अगर (!hpfs_get_sector(s, secno + 3, &qbh->bh[3])) जाओ bail3;

	अगर (likely(qbh->bh[1]->b_data == qbh->bh[0]->b_data + 1 * 512) &&
	    likely(qbh->bh[2]->b_data == qbh->bh[0]->b_data + 2 * 512) &&
	    likely(qbh->bh[3]->b_data == qbh->bh[0]->b_data + 3 * 512)) अणु
		वापस qbh->data = qbh->bh[0]->b_data;
	पूर्ण

	अगर (!(qbh->data = kदो_स्मृति(2048, GFP_NOFS))) अणु
		pr_err("%s(): out of memory\n", __func__);
		जाओ bail4;
	पूर्ण
	वापस qbh->data;

bail4:
	brअन्यथा(qbh->bh[3]);
bail3:
	brअन्यथा(qbh->bh[2]);
bail2:
	brअन्यथा(qbh->bh[1]);
bail1:
	brअन्यथा(qbh->bh[0]);
bail0:
	वापस शून्य;
पूर्ण
	

व्योम hpfs_brअन्यथा4(काष्ठा quad_buffer_head *qbh)
अणु
	अगर (unlikely(qbh->data != qbh->bh[0]->b_data))
		kमुक्त(qbh->data);
	brअन्यथा(qbh->bh[0]);
	brअन्यथा(qbh->bh[1]);
	brअन्यथा(qbh->bh[2]);
	brअन्यथा(qbh->bh[3]);
पूर्ण	

व्योम hpfs_mark_4buffers_dirty(काष्ठा quad_buffer_head *qbh)
अणु
	अगर (unlikely(qbh->data != qbh->bh[0]->b_data)) अणु
		स_नकल(qbh->bh[0]->b_data, qbh->data + 0 * 512, 512);
		स_नकल(qbh->bh[1]->b_data, qbh->data + 1 * 512, 512);
		स_नकल(qbh->bh[2]->b_data, qbh->data + 2 * 512, 512);
		स_नकल(qbh->bh[3]->b_data, qbh->data + 3 * 512, 512);
	पूर्ण
	mark_buffer_dirty(qbh->bh[0]);
	mark_buffer_dirty(qbh->bh[1]);
	mark_buffer_dirty(qbh->bh[2]);
	mark_buffer_dirty(qbh->bh[3]);
पूर्ण
