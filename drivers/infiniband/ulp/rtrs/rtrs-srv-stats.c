<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * RDMA Transport Layer
 *
 * Copyright (c) 2014 - 2018 ProfitBricks GmbH. All rights reserved.
 * Copyright (c) 2018 - 2019 1&1 IONOS Cloud GmbH. All rights reserved.
 * Copyright (c) 2019 - 2020 1&1 IONOS SE. All rights reserved.
 */
#अघोषित pr_fmt
#घोषणा pr_fmt(fmt) KBUILD_MODNAME " L" __stringअगरy(__LINE__) ": " fmt

#समावेश "rtrs-srv.h"

पूर्णांक rtrs_srv_reset_rdma_stats(काष्ठा rtrs_srv_stats *stats, bool enable)
अणु
	अगर (enable) अणु
		काष्ठा rtrs_srv_stats_rdma_stats *r = &stats->rdma_stats;

		स_रखो(r, 0, माप(*r));
		वापस 0;
	पूर्ण

	वापस -EINVAL;
पूर्ण

sमाप_प्रकार rtrs_srv_stats_rdma_to_str(काष्ठा rtrs_srv_stats *stats,
				    अक्षर *page, माप_प्रकार len)
अणु
	काष्ठा rtrs_srv_stats_rdma_stats *r = &stats->rdma_stats;
	काष्ठा rtrs_srv_sess *sess = stats->sess;

	वापस scnम_लिखो(page, len, "%lld %lld %lld %lld %u\n",
			 (s64)atomic64_पढ़ो(&r->dir[READ].cnt),
			 (s64)atomic64_पढ़ो(&r->dir[READ].माप_प्रकारotal),
			 (s64)atomic64_पढ़ो(&r->dir[WRITE].cnt),
			 (s64)atomic64_पढ़ो(&r->dir[WRITE].माप_प्रकारotal),
			 atomic_पढ़ो(&sess->ids_inflight));
पूर्ण
