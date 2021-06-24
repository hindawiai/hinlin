<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * f2fs shrinker support
 *   the basic infra was copied from fs/ubअगरs/shrinker.c
 *
 * Copyright (c) 2015 Motorola Mobility
 * Copyright (c) 2015 Jaegeuk Kim <jaegeuk@kernel.org>
 */
#समावेश <linux/fs.h>
#समावेश <linux/f2fs_fs.h>

#समावेश "f2fs.h"
#समावेश "node.h"

अटल LIST_HEAD(f2fs_list);
अटल DEFINE_SPINLOCK(f2fs_list_lock);
अटल अचिन्हित पूर्णांक shrinker_run_no;

अटल अचिन्हित दीर्घ __count_nat_entries(काष्ठा f2fs_sb_info *sbi)
अणु
	वापस NM_I(sbi)->nat_cnt[RECLAIMABLE_NAT];
पूर्ण

अटल अचिन्हित दीर्घ __count_मुक्त_nids(काष्ठा f2fs_sb_info *sbi)
अणु
	दीर्घ count = NM_I(sbi)->nid_cnt[FREE_NID] - MAX_FREE_NIDS;

	वापस count > 0 ? count : 0;
पूर्ण

अटल अचिन्हित दीर्घ __count_extent_cache(काष्ठा f2fs_sb_info *sbi)
अणु
	वापस atomic_पढ़ो(&sbi->total_zombie_tree) +
				atomic_पढ़ो(&sbi->total_ext_node);
पूर्ण

अचिन्हित दीर्घ f2fs_shrink_count(काष्ठा shrinker *shrink,
				काष्ठा shrink_control *sc)
अणु
	काष्ठा f2fs_sb_info *sbi;
	काष्ठा list_head *p;
	अचिन्हित दीर्घ count = 0;

	spin_lock(&f2fs_list_lock);
	p = f2fs_list.next;
	जबतक (p != &f2fs_list) अणु
		sbi = list_entry(p, काष्ठा f2fs_sb_info, s_list);

		/* stop f2fs_put_super */
		अगर (!mutex_trylock(&sbi->umount_mutex)) अणु
			p = p->next;
			जारी;
		पूर्ण
		spin_unlock(&f2fs_list_lock);

		/* count extent cache entries */
		count += __count_extent_cache(sbi);

		/* count clean nat cache entries */
		count += __count_nat_entries(sbi);

		/* count मुक्त nids cache entries */
		count += __count_मुक्त_nids(sbi);

		spin_lock(&f2fs_list_lock);
		p = p->next;
		mutex_unlock(&sbi->umount_mutex);
	पूर्ण
	spin_unlock(&f2fs_list_lock);
	वापस count;
पूर्ण

अचिन्हित दीर्घ f2fs_shrink_scan(काष्ठा shrinker *shrink,
				काष्ठा shrink_control *sc)
अणु
	अचिन्हित दीर्घ nr = sc->nr_to_scan;
	काष्ठा f2fs_sb_info *sbi;
	काष्ठा list_head *p;
	अचिन्हित पूर्णांक run_no;
	अचिन्हित दीर्घ मुक्तd = 0;

	spin_lock(&f2fs_list_lock);
	करो अणु
		run_no = ++shrinker_run_no;
	पूर्ण जबतक (run_no == 0);
	p = f2fs_list.next;
	जबतक (p != &f2fs_list) अणु
		sbi = list_entry(p, काष्ठा f2fs_sb_info, s_list);

		अगर (sbi->shrinker_run_no == run_no)
			अवरोध;

		/* stop f2fs_put_super */
		अगर (!mutex_trylock(&sbi->umount_mutex)) अणु
			p = p->next;
			जारी;
		पूर्ण
		spin_unlock(&f2fs_list_lock);

		sbi->shrinker_run_no = run_no;

		/* shrink extent cache entries */
		मुक्तd += f2fs_shrink_extent_tree(sbi, nr >> 1);

		/* shrink clean nat cache entries */
		अगर (मुक्तd < nr)
			मुक्तd += f2fs_try_to_मुक्त_nats(sbi, nr - मुक्तd);

		/* shrink मुक्त nids cache entries */
		अगर (मुक्तd < nr)
			मुक्तd += f2fs_try_to_मुक्त_nids(sbi, nr - मुक्तd);

		spin_lock(&f2fs_list_lock);
		p = p->next;
		list_move_tail(&sbi->s_list, &f2fs_list);
		mutex_unlock(&sbi->umount_mutex);
		अगर (मुक्तd >= nr)
			अवरोध;
	पूर्ण
	spin_unlock(&f2fs_list_lock);
	वापस मुक्तd;
पूर्ण

व्योम f2fs_join_shrinker(काष्ठा f2fs_sb_info *sbi)
अणु
	spin_lock(&f2fs_list_lock);
	list_add_tail(&sbi->s_list, &f2fs_list);
	spin_unlock(&f2fs_list_lock);
पूर्ण

व्योम f2fs_leave_shrinker(काष्ठा f2fs_sb_info *sbi)
अणु
	f2fs_shrink_extent_tree(sbi, __count_extent_cache(sbi));

	spin_lock(&f2fs_list_lock);
	list_del_init(&sbi->s_list);
	spin_unlock(&f2fs_list_lock);
पूर्ण
