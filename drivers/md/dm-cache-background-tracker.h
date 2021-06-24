<शैली गुरु>
/*
 * Copyright (C) 2017 Red Hat. All rights reserved.
 *
 * This file is released under the GPL.
 */

#अगर_अघोषित DM_CACHE_BACKGROUND_WORK_H
#घोषणा DM_CACHE_BACKGROUND_WORK_H

#समावेश <linux/vदो_स्मृति.h>
#समावेश "dm-cache-policy.h"

/*----------------------------------------------------------------*/

काष्ठा background_work;
काष्ठा background_tracker;

/*
 * FIXME: discuss lack of locking in all methods.
 */
काष्ठा background_tracker *btracker_create(अचिन्हित max_work);
व्योम btracker_destroy(काष्ठा background_tracker *b);

अचिन्हित btracker_nr_ग_लिखोbacks_queued(काष्ठा background_tracker *b);
अचिन्हित btracker_nr_demotions_queued(काष्ठा background_tracker *b);

/*
 * वापसs -EINVAL अगरf the work is alपढ़ोy queued.  -ENOMEM अगर the work
 * couldn't be queued क्रम another reason.
 */
पूर्णांक btracker_queue(काष्ठा background_tracker *b,
		   काष्ठा policy_work *work,
		   काष्ठा policy_work **pwork);

/*
 * Returns -ENODATA अगर there's no work.
 */
पूर्णांक btracker_issue(काष्ठा background_tracker *b, काष्ठा policy_work **work);
व्योम btracker_complete(काष्ठा background_tracker *b,
		       काष्ठा policy_work *op);
bool btracker_promotion_alपढ़ोy_present(काष्ठा background_tracker *b,
					dm_oblock_t oblock);

/*----------------------------------------------------------------*/

#पूर्ण_अगर
