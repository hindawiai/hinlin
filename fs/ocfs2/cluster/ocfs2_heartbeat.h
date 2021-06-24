<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * ocfs2_heartbeat.h
 *
 * On-disk काष्ठाures क्रम ocfs2_heartbeat
 *
 * Copyright (C) 2002, 2004 Oracle.  All rights reserved.
 */

#अगर_अघोषित _OCFS2_HEARTBEAT_H
#घोषणा _OCFS2_HEARTBEAT_H

काष्ठा o2hb_disk_heartbeat_block अणु
	__le64 hb_seq;
	__u8  hb_node;
	__u8  hb_pad1[3];
	__le32 hb_cksum;
	__le64 hb_generation;
	__le32 hb_dead_ms;
पूर्ण;

#पूर्ण_अगर /* _OCFS2_HEARTBEAT_H */
