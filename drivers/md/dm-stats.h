<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित DM_STATS_H
#घोषणा DM_STATS_H

#समावेश <linux/types.h>
#समावेश <linux/mutex.h>
#समावेश <linux/list.h>

पूर्णांक dm_statistics_init(व्योम);
व्योम dm_statistics_निकास(व्योम);

काष्ठा dm_stats अणु
	काष्ठा mutex mutex;
	काष्ठा list_head list;	/* list of काष्ठा dm_stat */
	काष्ठा dm_stats_last_position __percpu *last;
	sector_t last_sector;
	अचिन्हित last_rw;
पूर्ण;

काष्ठा dm_stats_aux अणु
	bool merged;
	अचिन्हित दीर्घ दीर्घ duration_ns;
पूर्ण;

व्योम dm_stats_init(काष्ठा dm_stats *st);
व्योम dm_stats_cleanup(काष्ठा dm_stats *st);

काष्ठा mapped_device;

पूर्णांक dm_stats_message(काष्ठा mapped_device *md, अचिन्हित argc, अक्षर **argv,
		     अक्षर *result, अचिन्हित maxlen);

व्योम dm_stats_account_io(काष्ठा dm_stats *stats, अचिन्हित दीर्घ bi_rw,
			 sector_t bi_sector, अचिन्हित bi_sectors, bool end,
			 अचिन्हित दीर्घ duration_jअगरfies,
			 काष्ठा dm_stats_aux *aux);

अटल अंतरभूत bool dm_stats_used(काष्ठा dm_stats *st)
अणु
	वापस !list_empty(&st->list);
पूर्ण

#पूर्ण_अगर
