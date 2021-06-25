<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* Netfs support statistics
 *
 * Copyright (C) 2021 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */

#समावेश <linux/export.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/netfs.h>
#समावेश "internal.h"

atomic_t netfs_n_rh_पढ़ोahead;
atomic_t netfs_n_rh_पढ़ोpage;
atomic_t netfs_n_rh_rreq;
atomic_t netfs_n_rh_sreq;
atomic_t netfs_n_rh_करोwnload;
atomic_t netfs_n_rh_करोwnload_करोne;
atomic_t netfs_n_rh_करोwnload_failed;
atomic_t netfs_n_rh_करोwnload_instead;
atomic_t netfs_n_rh_पढ़ो;
atomic_t netfs_n_rh_पढ़ो_करोne;
atomic_t netfs_n_rh_पढ़ो_failed;
atomic_t netfs_n_rh_zero;
atomic_t netfs_n_rh_लघु_पढ़ो;
atomic_t netfs_n_rh_ग_लिखो;
atomic_t netfs_n_rh_ग_लिखो_begin;
atomic_t netfs_n_rh_ग_लिखो_करोne;
atomic_t netfs_n_rh_ग_लिखो_failed;
atomic_t netfs_n_rh_ग_लिखो_zskip;

व्योम netfs_stats_show(काष्ठा seq_file *m)
अणु
	seq_म_लिखो(m, "RdHelp : RA=%u RP=%u WB=%u WBZ=%u rr=%u sr=%u\n",
		   atomic_पढ़ो(&netfs_n_rh_पढ़ोahead),
		   atomic_पढ़ो(&netfs_n_rh_पढ़ोpage),
		   atomic_पढ़ो(&netfs_n_rh_ग_लिखो_begin),
		   atomic_पढ़ो(&netfs_n_rh_ग_लिखो_zskip),
		   atomic_पढ़ो(&netfs_n_rh_rreq),
		   atomic_पढ़ो(&netfs_n_rh_sreq));
	seq_म_लिखो(m, "RdHelp : ZR=%u sh=%u sk=%u\n",
		   atomic_पढ़ो(&netfs_n_rh_zero),
		   atomic_पढ़ो(&netfs_n_rh_लघु_पढ़ो),
		   atomic_पढ़ो(&netfs_n_rh_ग_लिखो_zskip));
	seq_म_लिखो(m, "RdHelp : DL=%u ds=%u df=%u di=%u\n",
		   atomic_पढ़ो(&netfs_n_rh_करोwnload),
		   atomic_पढ़ो(&netfs_n_rh_करोwnload_करोne),
		   atomic_पढ़ो(&netfs_n_rh_करोwnload_failed),
		   atomic_पढ़ो(&netfs_n_rh_करोwnload_instead));
	seq_म_लिखो(m, "RdHelp : RD=%u rs=%u rf=%u\n",
		   atomic_पढ़ो(&netfs_n_rh_पढ़ो),
		   atomic_पढ़ो(&netfs_n_rh_पढ़ो_करोne),
		   atomic_पढ़ो(&netfs_n_rh_पढ़ो_failed));
	seq_म_लिखो(m, "RdHelp : WR=%u ws=%u wf=%u\n",
		   atomic_पढ़ो(&netfs_n_rh_ग_लिखो),
		   atomic_पढ़ो(&netfs_n_rh_ग_लिखो_करोne),
		   atomic_पढ़ो(&netfs_n_rh_ग_लिखो_failed));
पूर्ण
EXPORT_SYMBOL(netfs_stats_show);
