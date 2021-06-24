<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2017 Western Digital Corporation or its affiliates.
 */

#समावेश <linux/blkdev.h>
#समावेश "blk-mq-debugfs.h"

पूर्णांक queue_zone_wlock_show(व्योम *data, काष्ठा seq_file *m)
अणु
	काष्ठा request_queue *q = data;
	अचिन्हित पूर्णांक i;

	अगर (!q->seq_zones_wlock)
		वापस 0;

	क्रम (i = 0; i < q->nr_zones; i++)
		अगर (test_bit(i, q->seq_zones_wlock))
			seq_म_लिखो(m, "%u\n", i);

	वापस 0;
पूर्ण
