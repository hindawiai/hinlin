<शैली गुरु>
/**********************************************************************
 * Author: Cavium, Inc.
 *
 * Contact: support@cavium.com
 *          Please include "LiquidIO" in the subject.
 *
 * Copyright (c) 2003-2017 Cavium, Inc.
 *
 * This file is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License, Version 2, as
 * published by the Free Software Foundation.
 *
 * This file is distributed in the hope that it will be useful, but
 * AS-IS and WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE, TITLE, or
 * NONINFRINGEMENT.  See the GNU General Public License क्रम more
 * details.
 *
 * This file may also be available under a dअगरferent license from Cavium.
 * Contact Cavium, Inc. क्रम more inक्रमmation
 **********************************************************************/

/*! \पile octeon_vf_मुख्य.h
 *  \मrief Host Driver: This file defines vf_rep related macros and काष्ठाures
 */
#अगर_अघोषित __LIO_VF_REP_H__
#घोषणा __LIO_VF_REP_H__
#घोषणा LIO_VF_REP_REQ_TMO_MS 5000
#घोषणा LIO_VF_REP_STATS_POLL_TIME_MS 200

काष्ठा lio_vf_rep_desc अणु
	काष्ठा net_device *parent_ndev;
	काष्ठा net_device *ndev;
	काष्ठा octeon_device *oct;
	काष्ठा lio_vf_rep_stats stats;
	काष्ठा cavium_wk stats_wk;
	atomic_t अगरstate;
	पूर्णांक अगरidx;
पूर्ण;

काष्ठा lio_vf_rep_sc_ctx अणु
	काष्ठा completion complete;
पूर्ण;

पूर्णांक lio_vf_rep_create(काष्ठा octeon_device *oct);
व्योम lio_vf_rep_destroy(काष्ठा octeon_device *oct);
पूर्णांक lio_vf_rep_modinit(व्योम);
व्योम lio_vf_rep_modनिकास(व्योम);
#पूर्ण_अगर
