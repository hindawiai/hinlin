<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * RDMA Transport Layer
 *
 * Copyright (c) 2014 - 2018 ProfitBricks GmbH. All rights reserved.
 * Copyright (c) 2018 - 2019 1&1 IONOS Cloud GmbH. All rights reserved.
 * Copyright (c) 2019 - 2020 1&1 IONOS SE. All rights reserved.
 */
#अगर_अघोषित RTRS_LOG_H
#घोषणा RTRS_LOG_H

#घोषणा rtrs_log(fn, obj, fmt, ...)				\
	fn("<%s>: " fmt, obj->sessname, ##__VA_ARGS__)

#घोषणा rtrs_err(obj, fmt, ...)	\
	rtrs_log(pr_err, obj, fmt, ##__VA_ARGS__)
#घोषणा rtrs_err_rl(obj, fmt, ...)	\
	rtrs_log(pr_err_ratelimited, obj, fmt, ##__VA_ARGS__)
#घोषणा rtrs_wrn(obj, fmt, ...)	\
	rtrs_log(pr_warn, obj, fmt, ##__VA_ARGS__)
#घोषणा rtrs_wrn_rl(obj, fmt, ...) \
	rtrs_log(pr_warn_ratelimited, obj, fmt, ##__VA_ARGS__)
#घोषणा rtrs_info(obj, fmt, ...) \
	rtrs_log(pr_info, obj, fmt, ##__VA_ARGS__)
#घोषणा rtrs_info_rl(obj, fmt, ...) \
	rtrs_log(pr_info_ratelimited, obj, fmt, ##__VA_ARGS__)

#पूर्ण_अगर /* RTRS_LOG_H */
