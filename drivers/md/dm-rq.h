<शैली गुरु>
/*
 * Internal header file क्रम device mapper
 *
 * Copyright (C) 2016 Red Hat, Inc. All rights reserved.
 *
 * This file is released under the LGPL.
 */

#अगर_अघोषित DM_RQ_INTERNAL_H
#घोषणा DM_RQ_INTERNAL_H

#समावेश <linux/bपन.स>
#समावेश <linux/kthपढ़ो.h>

#समावेश "dm-stats.h"

काष्ठा mapped_device;

/*
 * For request-based dm - the bio clones we allocate are embedded in these
 * काष्ठाs.
 *
 * We allocate these with bio_alloc_bioset, using the front_pad parameter when
 * the bioset is created - this means the bio has to come at the end of the
 * काष्ठा.
 */
काष्ठा dm_rq_clone_bio_info अणु
	काष्ठा bio *orig;
	काष्ठा dm_rq_target_io *tio;
	काष्ठा bio clone;
पूर्ण;

पूर्णांक dm_mq_init_request_queue(काष्ठा mapped_device *md, काष्ठा dm_table *t);
व्योम dm_mq_cleanup_mapped_device(काष्ठा mapped_device *md);

व्योम dm_start_queue(काष्ठा request_queue *q);
व्योम dm_stop_queue(काष्ठा request_queue *q);

व्योम dm_mq_kick_requeue_list(काष्ठा mapped_device *md);

अचिन्हित dm_get_reserved_rq_based_ios(व्योम);

sमाप_प्रकार dm_attr_rq_based_seq_io_merge_deadline_show(काष्ठा mapped_device *md, अक्षर *buf);
sमाप_प्रकार dm_attr_rq_based_seq_io_merge_deadline_store(काष्ठा mapped_device *md,
						     स्थिर अक्षर *buf, माप_प्रकार count);

#पूर्ण_अगर
