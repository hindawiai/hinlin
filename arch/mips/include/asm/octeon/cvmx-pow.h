<शैली गुरु>
/***********************license start***************
 * Author: Cavium Networks
 *
 * Contact: support@caviumnetworks.com
 * This file is part of the OCTEON SDK
 *
 * Copyright (c) 2003-2008 Cavium Networks
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
 * You should have received a copy of the GNU General Public License
 * aदीर्घ with this file; अगर not, ग_लिखो to the Free Software
 * Foundation, Inc., 51 Franklin St, Fअगरth Floor, Boston, MA 02110-1301 USA
 * or visit http://www.gnu.org/licenses/.
 *
 * This file may also be available under a dअगरferent license from Cavium.
 * Contact Cavium Networks क्रम more inक्रमmation
 ***********************license end**************************************/

/**
 * Interface to the hardware Packet Order / Work unit.
 *
 * New, starting with SDK 1.7.0, cvmx-घात supports a number of
 * extended consistency checks. The define
 * CVMX_ENABLE_POW_CHECKS controls the runसमय insertion of POW
 * पूर्णांकernal state checks to find common programming errors. If
 * CVMX_ENABLE_POW_CHECKS is not defined, checks are by शेष
 * enabled. For example, cvmx-घात will check क्रम the following
 * program errors or POW state inconsistency.
 * - Requesting a POW operation with an active tag चयन in
 *   progress.
 * - Waiting क्रम a tag चयन to complete क्रम an excessively
 *   दीर्घ period. This is normally a sign of an error in locking
 *   causing deadlock.
 * - Illegal tag चयनes from शून्य_शून्य.
 * - Illegal tag चयनes from शून्य.
 * - Illegal deschedule request.
 * - WQE poपूर्णांकer not matching the one attached to the core by
 *   the POW.
 *
 */

#अगर_अघोषित __CVMX_POW_H__
#घोषणा __CVMX_POW_H__

#समावेश <यंत्र/octeon/cvmx-घात-defs.h>

#समावेश <यंत्र/octeon/cvmx-scratch.h>
#समावेश <यंत्र/octeon/cvmx-wqe.h>

/* Default to having all POW स्थिरancy checks turned on */
#अगर_अघोषित CVMX_ENABLE_POW_CHECKS
#घोषणा CVMX_ENABLE_POW_CHECKS 1
#पूर्ण_अगर

क्रमागत cvmx_घात_tag_type अणु
	/* Tag ordering is मुख्यtained */
	CVMX_POW_TAG_TYPE_ORDERED   = 0L,
	/* Tag ordering is मुख्यtained, and at most one PP has the tag */
	CVMX_POW_TAG_TYPE_ATOMIC    = 1L,
	/*
	 * The work queue entry from the order - NEVER tag चयन from
	 * शून्य to शून्य
	 */
	CVMX_POW_TAG_TYPE_शून्य	    = 2L,
	/* A tag चयन to शून्य, and there is no space reserved in POW
	 * - NEVER tag चयन to शून्य_शून्य
	 * - NEVER tag चयन from शून्य_शून्य
	 * - शून्य_शून्य is entered at the beginning of समय and on a deschedule.
	 * - शून्य_शून्य can be निकासed by a new work request. A शून्य_SWITCH
	 * load can also चयन the state to शून्य
	 */
	CVMX_POW_TAG_TYPE_शून्य_शून्य = 3L
पूर्ण;

/**
 * Wait flag values क्रम घात functions.
 */
प्रकार क्रमागत अणु
	CVMX_POW_WAIT = 1,
	CVMX_POW_NO_WAIT = 0,
पूर्ण cvmx_घात_रुको_t;

/**
 *  POW tag operations.	 These are used in the data stored to the POW.
 */
प्रकार क्रमागत अणु
	/*
	 * चयन the tag (only) क्रम this PP
	 * - the previous tag should be non-शून्य in this हाल
	 * - tag चयन response required
	 * - fields used: op, type, tag
	 */
	CVMX_POW_TAG_OP_SWTAG = 0L,
	/*
	 * चयन the tag क्रम this PP, with full inक्रमmation
	 * - this should be used when the previous tag is शून्य
	 * - tag चयन response required
	 * - fields used: address, op, grp, type, tag
	 */
	CVMX_POW_TAG_OP_SWTAG_FULL = 1L,
	/*
	 * चयन the tag (and/or group) क्रम this PP and de-schedule
	 * - OK to keep the tag the same and only change the group
	 * - fields used: op, no_sched, grp, type, tag
	 */
	CVMX_POW_TAG_OP_SWTAG_DESCH = 2L,
	/*
	 * just de-schedule
	 * - fields used: op, no_sched
	 */
	CVMX_POW_TAG_OP_DESCH = 3L,
	/*
	 * create an entirely new work queue entry
	 * - fields used: address, op, qos, grp, type, tag
	 */
	CVMX_POW_TAG_OP_ADDWQ = 4L,
	/*
	 * just update the work queue poपूर्णांकer and grp क्रम this PP
	 * - fields used: address, op, grp
	 */
	CVMX_POW_TAG_OP_UPDATE_WQP_GRP = 5L,
	/*
	 * set the no_sched bit on the de-schedule list
	 *
	 * - करोes nothing अगर the selected entry is not on the
	 *   de-schedule list
	 *
	 * - करोes nothing अगर the stored work queue poपूर्णांकer करोes not
	 *   match the address field
	 *
	 * - fields used: address, index, op
	 *
	 *  Beक्रमe issuing a *_NSCHED operation, SW must guarantee
	 *  that all prior deschedules and set/clr NSCHED operations
	 *  are complete and all prior चयनes are complete. The
	 *  hardware provides the opsकरोne bit and swकरोne bit क्रम SW
	 *  polling. After issuing a *_NSCHED operation, SW must
	 *  guarantee that the set/clr NSCHED is complete beक्रमe any
	 *  subsequent operations.
	 */
	CVMX_POW_TAG_OP_SET_NSCHED = 6L,
	/*
	 * clears the no_sched bit on the de-schedule list
	 *
	 * - करोes nothing अगर the selected entry is not on the
	 *   de-schedule list
	 *
	 * - करोes nothing अगर the stored work queue poपूर्णांकer करोes not
	 *   match the address field
	 *
	 * - fields used: address, index, op
	 *
	 * Beक्रमe issuing a *_NSCHED operation, SW must guarantee that
	 * all prior deschedules and set/clr NSCHED operations are
	 * complete and all prior चयनes are complete. The hardware
	 * provides the opsकरोne bit and swकरोne bit क्रम SW
	 * polling. After issuing a *_NSCHED operation, SW must
	 * guarantee that the set/clr NSCHED is complete beक्रमe any
	 * subsequent operations.
	 */
	CVMX_POW_TAG_OP_CLR_NSCHED = 7L,
	/* करो nothing */
	CVMX_POW_TAG_OP_NOP = 15L
पूर्ण cvmx_घात_tag_op_t;

/**
 * This काष्ठाure defines the store data on a store to POW
 */
प्रकार जोड़ अणु
	uपूर्णांक64_t u64;
	काष्ठा अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		/*
		 * Don't reschedule this entry. no_sched is used क्रम
		 * CVMX_POW_TAG_OP_SWTAG_DESCH and
		 * CVMX_POW_TAG_OP_DESCH
		 */
		uपूर्णांक64_t no_sched:1;
		uपूर्णांक64_t unused:2;
		/* Tontains index of entry क्रम a CVMX_POW_TAG_OP_*_NSCHED */
		uपूर्णांक64_t index:13;
		/* The operation to perक्रमm */
		cvmx_घात_tag_op_t op:4;
		uपूर्णांक64_t unused2:2;
		/*
		 * The QOS level क्रम the packet. qos is only used क्रम
		 * CVMX_POW_TAG_OP_ADDWQ
		 */
		uपूर्णांक64_t qos:3;
		/*
		 * The group that the work queue entry will be
		 * scheduled to grp is used क्रम CVMX_POW_TAG_OP_ADDWQ,
		 * CVMX_POW_TAG_OP_SWTAG_FULL,
		 * CVMX_POW_TAG_OP_SWTAG_DESCH, and
		 * CVMX_POW_TAG_OP_UPDATE_WQP_GRP
		 */
		uपूर्णांक64_t grp:4;
		/*
		 * The type of the tag. type is used क्रम everything
		 * except CVMX_POW_TAG_OP_DESCH,
		 * CVMX_POW_TAG_OP_UPDATE_WQP_GRP, and
		 * CVMX_POW_TAG_OP_*_NSCHED
		 */
		uपूर्णांक64_t type:3;
		/*
		 * The actual tag. tag is used क्रम everything except
		 * CVMX_POW_TAG_OP_DESCH,
		 * CVMX_POW_TAG_OP_UPDATE_WQP_GRP, and
		 * CVMX_POW_TAG_OP_*_NSCHED
		 */
		uपूर्णांक64_t tag:32;
#अन्यथा
		uपूर्णांक64_t tag:32;
		uपूर्णांक64_t type:3;
		uपूर्णांक64_t grp:4;
		uपूर्णांक64_t qos:3;
		uपूर्णांक64_t unused2:2;
		cvmx_घात_tag_op_t op:4;
		uपूर्णांक64_t index:13;
		uपूर्णांक64_t unused:2;
		uपूर्णांक64_t no_sched:1;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण cvmx_घात_tag_req_t;

/**
 * This काष्ठाure describes the address to load stuff from POW
 */
प्रकार जोड़ अणु
	uपूर्णांक64_t u64;

    /**
     * Address क्रम new work request loads (did<2:0> == 0)
     */
	काष्ठा अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		/* Mips64 address region. Should be CVMX_IO_SEG */
		uपूर्णांक64_t mem_region:2;
		/* Must be zero */
		uपूर्णांक64_t reserved_49_61:13;
		/* Must be one */
		uपूर्णांक64_t is_io:1;
		/* the ID of POW -- did<2:0> == 0 in this हाल */
		uपूर्णांक64_t did:8;
		/* Must be zero */
		uपूर्णांक64_t reserved_4_39:36;
		/*
		 * If set, करोn't वापस load response until work is
		 * available.
		 */
		uपूर्णांक64_t रुको:1;
		/* Must be zero */
		uपूर्णांक64_t reserved_0_2:3;
#अन्यथा
		uपूर्णांक64_t reserved_0_2:3;
		uपूर्णांक64_t रुको:1;
		uपूर्णांक64_t reserved_4_39:36;
		uपूर्णांक64_t did:8;
		uपूर्णांक64_t is_io:1;
		uपूर्णांक64_t reserved_49_61:13;
		uपूर्णांक64_t mem_region:2;
#पूर्ण_अगर
	पूर्ण swork;

    /**
     * Address क्रम loads to get POW पूर्णांकernal status
     */
	काष्ठा अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		/* Mips64 address region. Should be CVMX_IO_SEG */
		uपूर्णांक64_t mem_region:2;
		/* Must be zero */
		uपूर्णांक64_t reserved_49_61:13;
		/* Must be one */
		uपूर्णांक64_t is_io:1;
		/* the ID of POW -- did<2:0> == 1 in this हाल */
		uपूर्णांक64_t did:8;
		/* Must be zero */
		uपूर्णांक64_t reserved_10_39:30;
		/* The core id to get status क्रम */
		uपूर्णांक64_t coreid:4;
		/*
		 * If set and get_cur is set, वापस reverse tag-list
		 * poपूर्णांकer rather than क्रमward tag-list poपूर्णांकer.
		 */
		uपूर्णांक64_t get_rev:1;
		/*
		 * If set, वापस current status rather than pending
		 * status.
		 */
		uपूर्णांक64_t get_cur:1;
		/*
		 * If set, get the work-queue poपूर्णांकer rather than
		 * tag/type.
		 */
		uपूर्णांक64_t get_wqp:1;
		/* Must be zero */
		uपूर्णांक64_t reserved_0_2:3;
#अन्यथा
		uपूर्णांक64_t reserved_0_2:3;
		uपूर्णांक64_t get_wqp:1;
		uपूर्णांक64_t get_cur:1;
		uपूर्णांक64_t get_rev:1;
		uपूर्णांक64_t coreid:4;
		uपूर्णांक64_t reserved_10_39:30;
		uपूर्णांक64_t did:8;
		uपूर्णांक64_t is_io:1;
		uपूर्णांक64_t reserved_49_61:13;
		uपूर्णांक64_t mem_region:2;
#पूर्ण_अगर
	पूर्ण sstatus;

    /**
     * Address क्रम memory loads to get POW पूर्णांकernal state
     */
	काष्ठा अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		/* Mips64 address region. Should be CVMX_IO_SEG */
		uपूर्णांक64_t mem_region:2;
		/* Must be zero */
		uपूर्णांक64_t reserved_49_61:13;
		/* Must be one */
		uपूर्णांक64_t is_io:1;
		/* the ID of POW -- did<2:0> == 2 in this हाल */
		uपूर्णांक64_t did:8;
		/* Must be zero */
		uपूर्णांक64_t reserved_16_39:24;
		/* POW memory index */
		uपूर्णांक64_t index:11;
		/*
		 * If set, वापस deschedule inक्रमmation rather than
		 * the standard response क्रम work-queue index (invalid
		 * अगर the work-queue entry is not on the deschedule
		 * list).
		 */
		uपूर्णांक64_t get_des:1;
		/*
		 * If set, get the work-queue poपूर्णांकer rather than
		 * tag/type (no effect when get_des set).
		 */
		uपूर्णांक64_t get_wqp:1;
		/* Must be zero */
		uपूर्णांक64_t reserved_0_2:3;
#अन्यथा
		uपूर्णांक64_t reserved_0_2:3;
		uपूर्णांक64_t get_wqp:1;
		uपूर्णांक64_t get_des:1;
		uपूर्णांक64_t index:11;
		uपूर्णांक64_t reserved_16_39:24;
		uपूर्णांक64_t did:8;
		uपूर्णांक64_t is_io:1;
		uपूर्णांक64_t reserved_49_61:13;
		uपूर्णांक64_t mem_region:2;
#पूर्ण_अगर
	पूर्ण smemload;

    /**
     * Address क्रम index/poपूर्णांकer loads
     */
	काष्ठा अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		/* Mips64 address region. Should be CVMX_IO_SEG */
		uपूर्णांक64_t mem_region:2;
		/* Must be zero */
		uपूर्णांक64_t reserved_49_61:13;
		/* Must be one */
		uपूर्णांक64_t is_io:1;
		/* the ID of POW -- did<2:0> == 3 in this हाल */
		uपूर्णांक64_t did:8;
		/* Must be zero */
		uपूर्णांक64_t reserved_9_39:31;
		/*
		 * when अणुget_rmt ==0 AND get_des_get_tail == 0पूर्ण, this
		 * field selects one of eight POW पूर्णांकernal-input
		 * queues (0-7), one per QOS level; values 8-15 are
		 * illegal in this हाल; when अणुget_rmt ==0 AND
		 * get_des_get_tail == 1पूर्ण, this field selects one of
		 * 16 deschedule lists (per group); when get_rmt ==1,
		 * this field selects one of 16 memory-input queue
		 * lists.  The two memory-input queue lists associated
		 * with each QOS level are:
		 *
		 * - qosgrp = 0, qosgrp = 8:	  QOS0
		 * - qosgrp = 1, qosgrp = 9:	  QOS1
		 * - qosgrp = 2, qosgrp = 10:	  QOS2
		 * - qosgrp = 3, qosgrp = 11:	  QOS3
		 * - qosgrp = 4, qosgrp = 12:	  QOS4
		 * - qosgrp = 5, qosgrp = 13:	  QOS5
		 * - qosgrp = 6, qosgrp = 14:	  QOS6
		 * - qosgrp = 7, qosgrp = 15:	  QOS7
		 */
		uपूर्णांक64_t qosgrp:4;
		/*
		 * If set and get_rmt is clear, वापस deschedule list
		 * indexes rather than indexes क्रम the specअगरied qos
		 * level; अगर set and get_rmt is set, वापस the tail
		 * poपूर्णांकer rather than the head poपूर्णांकer क्रम the
		 * specअगरied qos level.
		 */
		uपूर्णांक64_t get_des_get_tail:1;
		/*
		 * If set, वापस remote poपूर्णांकers rather than the
		 * local indexes क्रम the specअगरied qos level.
		 */
		uपूर्णांक64_t get_rmt:1;
		/* Must be zero */
		uपूर्णांक64_t reserved_0_2:3;
#अन्यथा
		uपूर्णांक64_t reserved_0_2:3;
		uपूर्णांक64_t get_rmt:1;
		uपूर्णांक64_t get_des_get_tail:1;
		uपूर्णांक64_t qosgrp:4;
		uपूर्णांक64_t reserved_9_39:31;
		uपूर्णांक64_t did:8;
		uपूर्णांक64_t is_io:1;
		uपूर्णांक64_t reserved_49_61:13;
		uपूर्णांक64_t mem_region:2;
#पूर्ण_अगर
	पूर्ण sindexload;

    /**
     * address क्रम शून्य_RD request (did<2:0> == 4) when this is पढ़ो,
     * HW attempts to change the state to शून्य अगर it is शून्य_शून्य (the
     * hardware cannot चयन from शून्य_शून्य to शून्य अगर a POW entry is
     * not available - software may need to recover by finishing
     * another piece of work beक्रमe a POW entry can ever become
     * available.)
     */
	काष्ठा अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		/* Mips64 address region. Should be CVMX_IO_SEG */
		uपूर्णांक64_t mem_region:2;
		/* Must be zero */
		uपूर्णांक64_t reserved_49_61:13;
		/* Must be one */
		uपूर्णांक64_t is_io:1;
		/* the ID of POW -- did<2:0> == 4 in this हाल */
		uपूर्णांक64_t did:8;
		/* Must be zero */
		uपूर्णांक64_t reserved_0_39:40;
#अन्यथा
		uपूर्णांक64_t reserved_0_39:40;
		uपूर्णांक64_t did:8;
		uपूर्णांक64_t is_io:1;
		uपूर्णांक64_t reserved_49_61:13;
		uपूर्णांक64_t mem_region:2;
#पूर्ण_अगर
	पूर्ण snull_rd;
पूर्ण cvmx_घात_load_addr_t;

/**
 * This काष्ठाure defines the response to a load/SENDSINGLE to POW
 * (except CSR पढ़ोs)
 */
प्रकार जोड़ अणु
	uपूर्णांक64_t u64;

    /**
     * Response to new work request loads
     */
	काष्ठा अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		/*
		 * Set when no new work queue entry was वापसed.  *
		 * If there was de-scheduled work, the HW will
		 * definitely वापस it. When this bit is set, it
		 * could mean either mean:
		 *
		 * - There was no work, or
		 *
		 * - There was no work that the HW could find. This
		 *   हाल can happen, regardless of the रुको bit value
		 *   in the original request, when there is work in
		 *   the IQ's that is too deep करोwn the list.
		 */
		uपूर्णांक64_t no_work:1;
		/* Must be zero */
		uपूर्णांक64_t reserved_40_62:23;
		/* 36 in O1 -- the work queue poपूर्णांकer */
		uपूर्णांक64_t addr:40;
#अन्यथा
		uपूर्णांक64_t addr:40;
		uपूर्णांक64_t reserved_40_62:23;
		uपूर्णांक64_t no_work:1;
#पूर्ण_अगर
	पूर्ण s_work;

    /**
     * Result क्रम a POW Status Load (when get_cur==0 and get_wqp==0)
     */
	काष्ठा अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_62_63:2;
		/* Set when there is a pending non-शून्य SWTAG or
		 * SWTAG_FULL, and the POW entry has not left the list
		 * क्रम the original tag. */
		uपूर्णांक64_t pend_चयन:1;
		/* Set when SWTAG_FULL and pend_चयन is set. */
		uपूर्णांक64_t pend_चयन_full:1;
		/*
		 * Set when there is a pending शून्य SWTAG, or an
		 * implicit चयन to शून्य.
		 */
		uपूर्णांक64_t pend_चयन_null:1;
		/* Set when there is a pending DESCHED or SWTAG_DESCHED. */
		uपूर्णांक64_t pend_desched:1;
		/*
		 * Set when there is a pending SWTAG_DESCHED and
		 * pend_desched is set.
		 */
		uपूर्णांक64_t pend_desched_चयन:1;
		/* Set when nosched is desired and pend_desched is set. */
		uपूर्णांक64_t pend_nosched:1;
		/* Set when there is a pending GET_WORK. */
		uपूर्णांक64_t pend_new_work:1;
		/*
		 * When pend_new_work is set, this bit indicates that
		 * the रुको bit was set.
		 */
		uपूर्णांक64_t pend_new_work_रुको:1;
		/* Set when there is a pending शून्य_RD. */
		uपूर्णांक64_t pend_null_rd:1;
		/* Set when there is a pending CLR_NSCHED. */
		uपूर्णांक64_t pend_nosched_clr:1;
		uपूर्णांक64_t reserved_51:1;
		/* This is the index when pend_nosched_clr is set. */
		uपूर्णांक64_t pend_index:11;
		/*
		 * This is the new_grp when (pend_desched AND
		 * pend_desched_चयन) is set.
		 */
		uपूर्णांक64_t pend_grp:4;
		uपूर्णांक64_t reserved_34_35:2;
		/*
		 * This is the tag type when pend_चयन or
		 * (pend_desched AND pend_desched_चयन) are set.
		 */
		uपूर्णांक64_t pend_type:2;
		/*
		 * - this is the tag when pend_चयन or (pend_desched
		 *    AND pend_desched_चयन) are set.
		 */
		uपूर्णांक64_t pend_tag:32;
#अन्यथा
		uपूर्णांक64_t pend_tag:32;
		uपूर्णांक64_t pend_type:2;
		uपूर्णांक64_t reserved_34_35:2;
		uपूर्णांक64_t pend_grp:4;
		uपूर्णांक64_t pend_index:11;
		uपूर्णांक64_t reserved_51:1;
		uपूर्णांक64_t pend_nosched_clr:1;
		uपूर्णांक64_t pend_null_rd:1;
		uपूर्णांक64_t pend_new_work_रुको:1;
		uपूर्णांक64_t pend_new_work:1;
		uपूर्णांक64_t pend_nosched:1;
		uपूर्णांक64_t pend_desched_चयन:1;
		uपूर्णांक64_t pend_desched:1;
		uपूर्णांक64_t pend_चयन_null:1;
		uपूर्णांक64_t pend_चयन_full:1;
		uपूर्णांक64_t pend_चयन:1;
		uपूर्णांक64_t reserved_62_63:2;
#पूर्ण_अगर
	पूर्ण s_sstatus0;

    /**
     * Result क्रम a POW Status Load (when get_cur==0 and get_wqp==1)
     */
	काष्ठा अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_62_63:2;
		/*
		 * Set when there is a pending non-शून्य SWTAG or
		 * SWTAG_FULL, and the POW entry has not left the list
		 * क्रम the original tag.
		 */
		uपूर्णांक64_t pend_चयन:1;
		/* Set when SWTAG_FULL and pend_चयन is set. */
		uपूर्णांक64_t pend_चयन_full:1;
		/*
		 * Set when there is a pending शून्य SWTAG, or an
		 * implicit चयन to शून्य.
		 */
		uपूर्णांक64_t pend_चयन_null:1;
		/*
		 * Set when there is a pending DESCHED or
		 * SWTAG_DESCHED.
		 */
		uपूर्णांक64_t pend_desched:1;
		/*
		 * Set when there is a pending SWTAG_DESCHED and
		 * pend_desched is set.
		 */
		uपूर्णांक64_t pend_desched_चयन:1;
		/* Set when nosched is desired and pend_desched is set. */
		uपूर्णांक64_t pend_nosched:1;
		/* Set when there is a pending GET_WORK. */
		uपूर्णांक64_t pend_new_work:1;
		/*
		 * When pend_new_work is set, this bit indicates that
		 * the रुको bit was set.
		 */
		uपूर्णांक64_t pend_new_work_रुको:1;
		/* Set when there is a pending शून्य_RD. */
		uपूर्णांक64_t pend_null_rd:1;
		/* Set when there is a pending CLR_NSCHED. */
		uपूर्णांक64_t pend_nosched_clr:1;
		uपूर्णांक64_t reserved_51:1;
		/* This is the index when pend_nosched_clr is set. */
		uपूर्णांक64_t pend_index:11;
		/*
		 * This is the new_grp when (pend_desched AND
		 * pend_desched_चयन) is set.
		 */
		uपूर्णांक64_t pend_grp:4;
		/* This is the wqp when pend_nosched_clr is set. */
		uपूर्णांक64_t pend_wqp:36;
#अन्यथा
	        uपूर्णांक64_t pend_wqp:36;
	        uपूर्णांक64_t pend_grp:4;
	        uपूर्णांक64_t pend_index:11;
	        uपूर्णांक64_t reserved_51:1;
	        uपूर्णांक64_t pend_nosched_clr:1;
	        uपूर्णांक64_t pend_null_rd:1;
	        uपूर्णांक64_t pend_new_work_रुको:1;
	        uपूर्णांक64_t pend_new_work:1;
	        uपूर्णांक64_t pend_nosched:1;
	        uपूर्णांक64_t pend_desched_चयन:1;
	        uपूर्णांक64_t pend_desched:1;
	        uपूर्णांक64_t pend_चयन_null:1;
	        uपूर्णांक64_t pend_चयन_full:1;
	        uपूर्णांक64_t pend_चयन:1;
	        uपूर्णांक64_t reserved_62_63:2;
#पूर्ण_अगर
	पूर्ण s_sstatus1;

    /**
     * Result क्रम a POW Status Load (when get_cur==1, get_wqp==0, and
     * get_rev==0)
     */
	काष्ठा अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_62_63:2;
		/*
		 * Poपूर्णांकs to the next POW entry in the tag list when
		 * tail == 0 (and tag_type is not शून्य or शून्य_शून्य).
		 */
		uपूर्णांक64_t link_index:11;
		/* The POW entry attached to the core. */
		uपूर्णांक64_t index:11;
		/*
		 * The group attached to the core (updated when new
		 * tag list entered on SWTAG_FULL).
		 */
		uपूर्णांक64_t grp:4;
		/*
		 * Set when this POW entry is at the head of its tag
		 * list (also set when in the शून्य or शून्य_शून्य
		 * state).
		 */
		uपूर्णांक64_t head:1;
		/*
		 * Set when this POW entry is at the tail of its tag
		 * list (also set when in the शून्य or शून्य_शून्य
		 * state).
		 */
		uपूर्णांक64_t tail:1;
		/*
		 * The tag type attached to the core (updated when new
		 * tag list entered on SWTAG, SWTAG_FULL, or
		 * SWTAG_DESCHED).
		 */
		uपूर्णांक64_t tag_type:2;
		/*
		 * The tag attached to the core (updated when new tag
		 * list entered on SWTAG, SWTAG_FULL, or
		 * SWTAG_DESCHED).
		 */
		uपूर्णांक64_t tag:32;
#अन्यथा
	        uपूर्णांक64_t tag:32;
	        uपूर्णांक64_t tag_type:2;
	        uपूर्णांक64_t tail:1;
	        uपूर्णांक64_t head:1;
	        uपूर्णांक64_t grp:4;
	        uपूर्णांक64_t index:11;
	        uपूर्णांक64_t link_index:11;
	        uपूर्णांक64_t reserved_62_63:2;
#पूर्ण_अगर
	पूर्ण s_sstatus2;

    /**
     * Result क्रम a POW Status Load (when get_cur==1, get_wqp==0, and get_rev==1)
     */
	काष्ठा अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_62_63:2;
		/*
		 * Poपूर्णांकs to the prior POW entry in the tag list when
		 * head == 0 (and tag_type is not शून्य or
		 * शून्य_शून्य). This field is unpredictable when the
		 * core's state is शून्य or शून्य_शून्य.
		 */
		uपूर्णांक64_t revlink_index:11;
		/* The POW entry attached to the core. */
		uपूर्णांक64_t index:11;
		/*
		 * The group attached to the core (updated when new
		 * tag list entered on SWTAG_FULL).
		 */
		uपूर्णांक64_t grp:4;
		/* Set when this POW entry is at the head of its tag
		 * list (also set when in the शून्य or शून्य_शून्य
		 * state).
		 */
		uपूर्णांक64_t head:1;
		/*
		 * Set when this POW entry is at the tail of its tag
		 * list (also set when in the शून्य or शून्य_शून्य
		 * state).
		 */
		uपूर्णांक64_t tail:1;
		/*
		 * The tag type attached to the core (updated when new
		 * tag list entered on SWTAG, SWTAG_FULL, or
		 * SWTAG_DESCHED).
		 */
		uपूर्णांक64_t tag_type:2;
		/*
		 * The tag attached to the core (updated when new tag
		 * list entered on SWTAG, SWTAG_FULL, or
		 * SWTAG_DESCHED).
		 */
		uपूर्णांक64_t tag:32;
#अन्यथा
	        uपूर्णांक64_t tag:32;
	        uपूर्णांक64_t tag_type:2;
	        uपूर्णांक64_t tail:1;
	        uपूर्णांक64_t head:1;
	        uपूर्णांक64_t grp:4;
	        uपूर्णांक64_t index:11;
	        uपूर्णांक64_t revlink_index:11;
	        uपूर्णांक64_t reserved_62_63:2;
#पूर्ण_अगर
	पूर्ण s_sstatus3;

    /**
     * Result क्रम a POW Status Load (when get_cur==1, get_wqp==1, and
     * get_rev==0)
     */
	काष्ठा अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_62_63:2;
		/*
		 * Poपूर्णांकs to the next POW entry in the tag list when
		 * tail == 0 (and tag_type is not शून्य or शून्य_शून्य).
		 */
		uपूर्णांक64_t link_index:11;
		/* The POW entry attached to the core. */
		uपूर्णांक64_t index:11;
		/*
		 * The group attached to the core (updated when new
		 * tag list entered on SWTAG_FULL).
		 */
		uपूर्णांक64_t grp:4;
		/*
		 * The wqp attached to the core (updated when new tag
		 * list entered on SWTAG_FULL).
		 */
		uपूर्णांक64_t wqp:36;
#अन्यथा
	        uपूर्णांक64_t wqp:36;
	        uपूर्णांक64_t grp:4;
	        uपूर्णांक64_t index:11;
	        uपूर्णांक64_t link_index:11;
	        uपूर्णांक64_t reserved_62_63:2;
#पूर्ण_अगर
	पूर्ण s_sstatus4;

    /**
     * Result क्रम a POW Status Load (when get_cur==1, get_wqp==1, and
     * get_rev==1)
     */
	काष्ठा अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_62_63:2;
		/*
		 * Poपूर्णांकs to the prior POW entry in the tag list when
		 * head == 0 (and tag_type is not शून्य or
		 * शून्य_शून्य). This field is unpredictable when the
		 * core's state is शून्य or शून्य_शून्य.
		 */
		uपूर्णांक64_t revlink_index:11;
		/* The POW entry attached to the core. */
		uपूर्णांक64_t index:11;
		/*
		 * The group attached to the core (updated when new
		 * tag list entered on SWTAG_FULL).
		 */
		uपूर्णांक64_t grp:4;
		/*
		 * The wqp attached to the core (updated when new tag
		 * list entered on SWTAG_FULL).
		 */
		uपूर्णांक64_t wqp:36;
#अन्यथा
	        uपूर्णांक64_t wqp:36;
	        uपूर्णांक64_t grp:4;
	        uपूर्णांक64_t index:11;
	        uपूर्णांक64_t revlink_index:11;
	        uपूर्णांक64_t reserved_62_63:2;
#पूर्ण_अगर
	पूर्ण s_sstatus5;

    /**
     * Result For POW Memory Load (get_des == 0 and get_wqp == 0)
     */
	काष्ठा अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_51_63:13;
		/*
		 * The next entry in the input, मुक्त, descheduled_head
		 * list (unpredictable अगर entry is the tail of the
		 * list).
		 */
		uपूर्णांक64_t next_index:11;
		/* The group of the POW entry. */
		uपूर्णांक64_t grp:4;
		uपूर्णांक64_t reserved_35:1;
		/*
		 * Set when this POW entry is at the tail of its tag
		 * list (also set when in the शून्य or शून्य_शून्य
		 * state).
		 */
		uपूर्णांक64_t tail:1;
		/* The tag type of the POW entry. */
		uपूर्णांक64_t tag_type:2;
		/* The tag of the POW entry. */
		uपूर्णांक64_t tag:32;
#अन्यथा
	        uपूर्णांक64_t tag:32;
	        uपूर्णांक64_t tag_type:2;
	        uपूर्णांक64_t tail:1;
	        uपूर्णांक64_t reserved_35:1;
	        uपूर्णांक64_t grp:4;
	        uपूर्णांक64_t next_index:11;
	        uपूर्णांक64_t reserved_51_63:13;
#पूर्ण_अगर
	पूर्ण s_smemload0;

    /**
     * Result For POW Memory Load (get_des == 0 and get_wqp == 1)
     */
	काष्ठा अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_51_63:13;
		/*
		 * The next entry in the input, मुक्त, descheduled_head
		 * list (unpredictable अगर entry is the tail of the
		 * list).
		 */
		uपूर्णांक64_t next_index:11;
		/* The group of the POW entry. */
		uपूर्णांक64_t grp:4;
		/* The WQP held in the POW entry. */
		uपूर्णांक64_t wqp:36;
#अन्यथा
	        uपूर्णांक64_t wqp:36;
	        uपूर्णांक64_t grp:4;
	        uपूर्णांक64_t next_index:11;
	        uपूर्णांक64_t reserved_51_63:13;
#पूर्ण_अगर
	पूर्ण s_smemload1;

    /**
     * Result For POW Memory Load (get_des == 1)
     */
	काष्ठा अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_51_63:13;
		/*
		 * The next entry in the tag list connected to the
		 * descheduled head.
		 */
		uपूर्णांक64_t fwd_index:11;
		/* The group of the POW entry. */
		uपूर्णांक64_t grp:4;
		/* The nosched bit क्रम the POW entry. */
		uपूर्णांक64_t nosched:1;
		/* There is a pending tag चयन */
		uपूर्णांक64_t pend_चयन:1;
		/*
		 * The next tag type क्रम the new tag list when
		 * pend_चयन is set.
		 */
		uपूर्णांक64_t pend_type:2;
		/*
		 * The next tag क्रम the new tag list when pend_चयन
		 * is set.
		 */
		uपूर्णांक64_t pend_tag:32;
#अन्यथा
	        uपूर्णांक64_t pend_tag:32;
	        uपूर्णांक64_t pend_type:2;
	        uपूर्णांक64_t pend_चयन:1;
	        uपूर्णांक64_t nosched:1;
	        uपूर्णांक64_t grp:4;
	        uपूर्णांक64_t fwd_index:11;
	        uपूर्णांक64_t reserved_51_63:13;
#पूर्ण_अगर
	पूर्ण s_smemload2;

    /**
     * Result For POW Index/Poपूर्णांकer Load (get_rmt == 0/get_des_get_tail == 0)
     */
	काष्ठा अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_52_63:12;
		/*
		 * set when there is one or more POW entries on the
		 * मुक्त list.
		 */
		uपूर्णांक64_t मुक्त_val:1;
		/*
		 * set when there is exactly one POW entry on the मुक्त
		 * list.
		 */
		uपूर्णांक64_t मुक्त_one:1;
		uपूर्णांक64_t reserved_49:1;
		/*
		 * when मुक्त_val is set, indicates the first entry on
		 * the मुक्त list.
		 */
		uपूर्णांक64_t मुक्त_head:11;
		uपूर्णांक64_t reserved_37:1;
		/*
		 * when मुक्त_val is set, indicates the last entry on
		 * the मुक्त list.
		 */
		uपूर्णांक64_t मुक्त_tail:11;
		/*
		 * set when there is one or more POW entries on the
		 * input Q list selected by qosgrp.
		 */
		uपूर्णांक64_t loc_val:1;
		/*
		 * set when there is exactly one POW entry on the
		 * input Q list selected by qosgrp.
		 */
		uपूर्णांक64_t loc_one:1;
		uपूर्णांक64_t reserved_23:1;
		/*
		 * when loc_val is set, indicates the first entry on
		 * the input Q list selected by qosgrp.
		 */
		uपूर्णांक64_t loc_head:11;
		uपूर्णांक64_t reserved_11:1;
		/*
		 * when loc_val is set, indicates the last entry on
		 * the input Q list selected by qosgrp.
		 */
		uपूर्णांक64_t loc_tail:11;
#अन्यथा
	        uपूर्णांक64_t loc_tail:11;
	        uपूर्णांक64_t reserved_11:1;
	        uपूर्णांक64_t loc_head:11;
	        uपूर्णांक64_t reserved_23:1;
	        uपूर्णांक64_t loc_one:1;
	        uपूर्णांक64_t loc_val:1;
	        uपूर्णांक64_t मुक्त_tail:11;
	        uपूर्णांक64_t reserved_37:1;
	        uपूर्णांक64_t मुक्त_head:11;
	        uपूर्णांक64_t reserved_49:1;
	        uपूर्णांक64_t मुक्त_one:1;
	        uपूर्णांक64_t मुक्त_val:1;
	        uपूर्णांक64_t reserved_52_63:12;
#पूर्ण_अगर
	पूर्ण sindexload0;

    /**
     * Result For POW Index/Poपूर्णांकer Load (get_rmt == 0/get_des_get_tail == 1)
     */
	काष्ठा अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_52_63:12;
		/*
		 * set when there is one or more POW entries on the
		 * nosched list.
		 */
		uपूर्णांक64_t nosched_val:1;
		/*
		 * set when there is exactly one POW entry on the
		 * nosched list.
		 */
		uपूर्णांक64_t nosched_one:1;
		uपूर्णांक64_t reserved_49:1;
		/*
		 * when nosched_val is set, indicates the first entry
		 * on the nosched list.
		 */
		uपूर्णांक64_t nosched_head:11;
		uपूर्णांक64_t reserved_37:1;
		/*
		 * when nosched_val is set, indicates the last entry
		 * on the nosched list.
		 */
		uपूर्णांक64_t nosched_tail:11;
		/*
		 * set when there is one or more descheduled heads on
		 * the descheduled list selected by qosgrp.
		 */
		uपूर्णांक64_t des_val:1;
		/*
		 * set when there is exactly one descheduled head on
		 * the descheduled list selected by qosgrp.
		 */
		uपूर्णांक64_t des_one:1;
		uपूर्णांक64_t reserved_23:1;
		/*
		 * when des_val is set, indicates the first
		 * descheduled head on the descheduled list selected
		 * by qosgrp.
		 */
		uपूर्णांक64_t des_head:11;
		uपूर्णांक64_t reserved_11:1;
		/*
		 * when des_val is set, indicates the last descheduled
		 * head on the descheduled list selected by qosgrp.
		 */
		uपूर्णांक64_t des_tail:11;
#अन्यथा
	        uपूर्णांक64_t des_tail:11;
	        uपूर्णांक64_t reserved_11:1;
	        uपूर्णांक64_t des_head:11;
	        uपूर्णांक64_t reserved_23:1;
	        uपूर्णांक64_t des_one:1;
	        uपूर्णांक64_t des_val:1;
	        uपूर्णांक64_t nosched_tail:11;
	        uपूर्णांक64_t reserved_37:1;
	        uपूर्णांक64_t nosched_head:11;
	        uपूर्णांक64_t reserved_49:1;
	        uपूर्णांक64_t nosched_one:1;
	        uपूर्णांक64_t nosched_val:1;
	        uपूर्णांक64_t reserved_52_63:12;
#पूर्ण_अगर
	पूर्ण sindexload1;

    /**
     * Result For POW Index/Poपूर्णांकer Load (get_rmt == 1/get_des_get_tail == 0)
     */
	काष्ठा अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_39_63:25;
		/*
		 * Set when this DRAM list is the current head
		 * (i.e. is the next to be reloaded when the POW
		 * hardware reloads a POW entry from DRAM). The POW
		 * hardware alternates between the two DRAM lists
		 * associated with a QOS level when it reloads work
		 * from DRAM पूर्णांकo the POW unit.
		 */
		uपूर्णांक64_t rmt_is_head:1;
		/*
		 * Set when the DRAM portion of the input Q list
		 * selected by qosgrp contains one or more pieces of
		 * work.
		 */
		uपूर्णांक64_t rmt_val:1;
		/*
		 * Set when the DRAM portion of the input Q list
		 * selected by qosgrp contains exactly one piece of
		 * work.
		 */
		uपूर्णांक64_t rmt_one:1;
		/*
		 * When rmt_val is set, indicates the first piece of
		 * work on the DRAM input Q list selected by
		 * qosgrp.
		 */
		uपूर्णांक64_t rmt_head:36;
#अन्यथा
	        uपूर्णांक64_t rmt_head:36;
	        uपूर्णांक64_t rmt_one:1;
	        uपूर्णांक64_t rmt_val:1;
	        uपूर्णांक64_t rmt_is_head:1;
	        uपूर्णांक64_t reserved_39_63:25;
#पूर्ण_अगर
	पूर्ण sindexload2;

    /**
     * Result For POW Index/Poपूर्णांकer Load (get_rmt ==
     * 1/get_des_get_tail == 1)
     */
	काष्ठा अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t reserved_39_63:25;
		/*
		 * set when this DRAM list is the current head
		 * (i.e. is the next to be reloaded when the POW
		 * hardware reloads a POW entry from DRAM). The POW
		 * hardware alternates between the two DRAM lists
		 * associated with a QOS level when it reloads work
		 * from DRAM पूर्णांकo the POW unit.
		 */
		uपूर्णांक64_t rmt_is_head:1;
		/*
		 * set when the DRAM portion of the input Q list
		 * selected by qosgrp contains one or more pieces of
		 * work.
		 */
		uपूर्णांक64_t rmt_val:1;
		/*
		 * set when the DRAM portion of the input Q list
		 * selected by qosgrp contains exactly one piece of
		 * work.
		 */
		uपूर्णांक64_t rmt_one:1;
		/*
		 * when rmt_val is set, indicates the last piece of
		 * work on the DRAM input Q list selected by
		 * qosgrp.
		 */
		uपूर्णांक64_t rmt_tail:36;
#अन्यथा
	        uपूर्णांक64_t rmt_tail:36;
	        uपूर्णांक64_t rmt_one:1;
	        uपूर्णांक64_t rmt_val:1;
	        uपूर्णांक64_t rmt_is_head:1;
	        uपूर्णांक64_t reserved_39_63:25;
#पूर्ण_अगर
	पूर्ण sindexload3;

    /**
     * Response to शून्य_RD request loads
     */
	काष्ठा अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		uपूर्णांक64_t unused:62;
		/* of type cvmx_घात_tag_type_t. state is one of the
		 * following:
		 *
		 * - CVMX_POW_TAG_TYPE_ORDERED
		 * - CVMX_POW_TAG_TYPE_ATOMIC
		 * - CVMX_POW_TAG_TYPE_शून्य
		 * - CVMX_POW_TAG_TYPE_शून्य_शून्य
		 */
		uपूर्णांक64_t state:2;
#अन्यथा
	        uपूर्णांक64_t state:2;
	        uपूर्णांक64_t unused:62;
#पूर्ण_अगर
	पूर्ण s_null_rd;

पूर्ण cvmx_घात_tag_load_resp_t;

/**
 * This काष्ठाure describes the address used क्रम stores to the POW.
 *  The store address is meaningful on stores to the POW.  The
 *  hardware assumes that an aligned 64-bit store was used क्रम all
 *  these stores.  Note the assumption that the work queue entry is
 *  aligned on an 8-byte boundary (since the low-order 3 address bits
 *  must be zero).  Note that not all fields are used by all
 *  operations.
 *
 *  NOTE: The following is the behavior of the pending चयन bit at the PP
 *	 क्रम POW stores (i.e. when did<7:3> == 0xc)
 *     - did<2:0> == 0	    => pending चयन bit is set
 *     - did<2:0> == 1	    => no affect on the pending चयन bit
 *     - did<2:0> == 3	    => pending चयन bit is cleared
 *     - did<2:0> == 7	    => no affect on the pending चयन bit
 *     - did<2:0> == others => must not be used
 *     - No other loads/stores have an affect on the pending चयन bit
 *     - The चयन bus from POW can clear the pending चयन bit
 *
 *  NOTE: did<2:0> == 2 is used by the HW क्रम a special single-cycle
 *  ADDWQ command that only contains the poपूर्णांकer). SW must never use
 *  did<2:0> == 2.
 */
प्रकार जोड़ अणु
    /**
     * Unचिन्हित 64 bit पूर्णांकeger representation of store address
     */
	uपूर्णांक64_t u64;

	काष्ठा अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		/* Memory region.  Should be CVMX_IO_SEG in most हालs */
		uपूर्णांक64_t mem_reg:2;
		uपूर्णांक64_t reserved_49_61:13;	/* Must be zero */
		uपूर्णांक64_t is_io:1;	/* Must be one */
		/* Device ID of POW.  Note that dअगरferent sub-dids are used. */
		uपूर्णांक64_t did:8;
		uपूर्णांक64_t reserved_36_39:4;	/* Must be zero */
		/* Address field. addr<2:0> must be zero */
		uपूर्णांक64_t addr:36;
#अन्यथा
	        uपूर्णांक64_t addr:36;
	        uपूर्णांक64_t reserved_36_39:4;
	        uपूर्णांक64_t did:8;
	        uपूर्णांक64_t is_io:1;
	        uपूर्णांक64_t reserved_49_61:13;
	        uपूर्णांक64_t mem_reg:2;
#पूर्ण_अगर
	पूर्ण stag;
पूर्ण cvmx_घात_tag_store_addr_t;

/**
 * decode of the store data when an IOBDMA SENDSINGLE is sent to POW
 */
प्रकार जोड़ अणु
	uपूर्णांक64_t u64;

	काष्ठा अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		/*
		 * the (64-bit word) location in scratchpad to ग_लिखो
		 * to (अगर len != 0)
		 */
		uपूर्णांक64_t scraddr:8;
		/* the number of words in the response (0 => no response) */
		uपूर्णांक64_t len:8;
		/* the ID of the device on the non-coherent bus */
		uपूर्णांक64_t did:8;
		uपूर्णांक64_t unused:36;
		/* अगर set, करोn't वापस load response until work is available */
		uपूर्णांक64_t रुको:1;
		uपूर्णांक64_t unused2:3;
#अन्यथा
	        uपूर्णांक64_t unused2:3;
	        uपूर्णांक64_t रुको:1;
	        uपूर्णांक64_t unused:36;
	        uपूर्णांक64_t did:8;
	        uपूर्णांक64_t len:8;
	        uपूर्णांक64_t scraddr:8;
#पूर्ण_अगर
	पूर्ण s;

पूर्ण cvmx_घात_iobdma_store_t;

/* CSR प्रकारs have been moved to cvmx-csr-*.h */

/**
 * Get the POW tag क्रम this core. This वापसs the current
 * tag type, tag, group, and POW entry index associated with
 * this core. Index is only valid अगर the tag type isn't शून्य_शून्य.
 * If a tag चयन is pending this routine वापसs the tag beक्रमe
 * the tag चयन, not after.
 *
 * Returns Current tag
 */
अटल अंतरभूत cvmx_घात_tag_req_t cvmx_घात_get_current_tag(व्योम)
अणु
	cvmx_घात_load_addr_t load_addr;
	cvmx_घात_tag_load_resp_t load_resp;
	cvmx_घात_tag_req_t result;

	load_addr.u64 = 0;
	load_addr.sstatus.mem_region = CVMX_IO_SEG;
	load_addr.sstatus.is_io = 1;
	load_addr.sstatus.did = CVMX_OCT_DID_TAG_TAG1;
	load_addr.sstatus.coreid = cvmx_get_core_num();
	load_addr.sstatus.get_cur = 1;
	load_resp.u64 = cvmx_पढ़ो_csr(load_addr.u64);
	result.u64 = 0;
	result.s.grp = load_resp.s_sstatus2.grp;
	result.s.index = load_resp.s_sstatus2.index;
	result.s.type = load_resp.s_sstatus2.tag_type;
	result.s.tag = load_resp.s_sstatus2.tag;
	वापस result;
पूर्ण

/**
 * Get the POW WQE क्रम this core. This वापसs the work queue
 * entry currently associated with this core.
 *
 * Returns WQE poपूर्णांकer
 */
अटल अंतरभूत काष्ठा cvmx_wqe *cvmx_घात_get_current_wqp(व्योम)
अणु
	cvmx_घात_load_addr_t load_addr;
	cvmx_घात_tag_load_resp_t load_resp;

	load_addr.u64 = 0;
	load_addr.sstatus.mem_region = CVMX_IO_SEG;
	load_addr.sstatus.is_io = 1;
	load_addr.sstatus.did = CVMX_OCT_DID_TAG_TAG1;
	load_addr.sstatus.coreid = cvmx_get_core_num();
	load_addr.sstatus.get_cur = 1;
	load_addr.sstatus.get_wqp = 1;
	load_resp.u64 = cvmx_पढ़ो_csr(load_addr.u64);
	वापस (काष्ठा cvmx_wqe *) cvmx_phys_to_ptr(load_resp.s_sstatus4.wqp);
पूर्ण

#अगर_अघोषित CVMX_MF_CHORD
#घोषणा CVMX_MF_CHORD(dest)	    CVMX_RDHWR(dest, 30)
#पूर्ण_अगर

/**
 * Prपूर्णांक a warning अगर a tag चयन is pending क्रम this core
 *
 * @function: Function name checking क्रम a pending tag चयन
 */
अटल अंतरभूत व्योम __cvmx_घात_warn_अगर_pending_चयन(स्थिर अक्षर *function)
अणु
	uपूर्णांक64_t चयन_complete;
	CVMX_MF_CHORD(चयन_complete);
	अगर (!चयन_complete)
		pr_warn("%s called with tag switch in progress\n", function);
पूर्ण

/**
 * Waits क्रम a tag चयन to complete by polling the completion bit.
 * Note that चयनes to शून्य complete immediately and करो not need
 * to be रुकोed क्रम.
 */
अटल अंतरभूत व्योम cvmx_घात_tag_sw_रुको(व्योम)
अणु
	स्थिर uपूर्णांक64_t MAX_CYCLES = 1ull << 31;
	uपूर्णांक64_t चयन_complete;
	uपूर्णांक64_t start_cycle = cvmx_get_cycle();
	जबतक (1) अणु
		CVMX_MF_CHORD(चयन_complete);
		अगर (unlikely(चयन_complete))
			अवरोध;
		अगर (unlikely(cvmx_get_cycle() > start_cycle + MAX_CYCLES)) अणु
			pr_warn("Tag switch is taking a long time, possible deadlock\n");
			start_cycle = -MAX_CYCLES - 1;
		पूर्ण
	पूर्ण
पूर्ण

/**
 * Synchronous work request.  Requests work from the POW.
 * This function करोes NOT रुको क्रम previous tag चयनes to complete,
 * so the caller must ensure that there is not a pending tag चयन.
 *
 * @रुको:   When set, call stalls until work becomes avaiable, or बार out.
 *		 If not set, वापसs immediately.
 *
 * Returns: the WQE poपूर्णांकer from POW. Returns शून्य अगर no work
 * was available.
 */
अटल अंतरभूत काष्ठा cvmx_wqe *cvmx_घात_work_request_sync_nocheck(cvmx_घात_रुको_t
							     रुको)
अणु
	cvmx_घात_load_addr_t ptr;
	cvmx_घात_tag_load_resp_t result;

	अगर (CVMX_ENABLE_POW_CHECKS)
		__cvmx_घात_warn_अगर_pending_चयन(__func__);

	ptr.u64 = 0;
	ptr.swork.mem_region = CVMX_IO_SEG;
	ptr.swork.is_io = 1;
	ptr.swork.did = CVMX_OCT_DID_TAG_SWTAG;
	ptr.swork.रुको = रुको;

	result.u64 = cvmx_पढ़ो_csr(ptr.u64);

	अगर (result.s_work.no_work)
		वापस शून्य;
	अन्यथा
		वापस (काष्ठा cvmx_wqe *) cvmx_phys_to_ptr(result.s_work.addr);
पूर्ण

/**
 * Synchronous work request.  Requests work from the POW.
 * This function रुकोs क्रम any previous tag चयन to complete beक्रमe
 * requesting the new work.
 *
 * @रुको:   When set, call stalls until work becomes avaiable, or बार out.
 *		 If not set, वापसs immediately.
 *
 * Returns: the WQE poपूर्णांकer from POW. Returns शून्य अगर no work
 * was available.
 */
अटल अंतरभूत काष्ठा cvmx_wqe *cvmx_घात_work_request_sync(cvmx_घात_रुको_t रुको)
अणु
	अगर (CVMX_ENABLE_POW_CHECKS)
		__cvmx_घात_warn_अगर_pending_चयन(__func__);

	/* Must not have a चयन pending when requesting work */
	cvmx_घात_tag_sw_रुको();
	वापस cvmx_घात_work_request_sync_nocheck(रुको);

पूर्ण

/**
 * Synchronous null_rd request.	 Requests a चयन out of शून्य_शून्य POW state.
 * This function रुकोs क्रम any previous tag चयन to complete beक्रमe
 * requesting the null_rd.
 *
 * Returns: the POW state of type cvmx_घात_tag_type_t.
 */
अटल अंतरभूत क्रमागत cvmx_घात_tag_type cvmx_घात_work_request_null_rd(व्योम)
अणु
	cvmx_घात_load_addr_t ptr;
	cvmx_घात_tag_load_resp_t result;

	अगर (CVMX_ENABLE_POW_CHECKS)
		__cvmx_घात_warn_अगर_pending_चयन(__func__);

	/* Must not have a चयन pending when requesting work */
	cvmx_घात_tag_sw_रुको();

	ptr.u64 = 0;
	ptr.snull_rd.mem_region = CVMX_IO_SEG;
	ptr.snull_rd.is_io = 1;
	ptr.snull_rd.did = CVMX_OCT_DID_TAG_शून्य_RD;

	result.u64 = cvmx_पढ़ो_csr(ptr.u64);

	वापस (क्रमागत cvmx_घात_tag_type) result.s_null_rd.state;
पूर्ण

/**
 * Asynchronous work request.  Work is requested from the POW unit,
 * and should later be checked with function
 * cvmx_घात_work_response_async.  This function करोes NOT रुको क्रम
 * previous tag चयनes to complete, so the caller must ensure that
 * there is not a pending tag चयन.
 *
 * @scr_addr: Scratch memory address that response will be वापसed
 *	      to, which is either a valid WQE, or a response with the
 *	      invalid bit set.	Byte address, must be 8 byte aligned.
 *
 * @रुको: 1 to cause response to रुको क्रम work to become available (or
 *	  समयout), 0 to cause response to वापस immediately
 */
अटल अंतरभूत व्योम cvmx_घात_work_request_async_nocheck(पूर्णांक scr_addr,
						       cvmx_घात_रुको_t रुको)
अणु
	cvmx_घात_iobdma_store_t data;

	अगर (CVMX_ENABLE_POW_CHECKS)
		__cvmx_घात_warn_अगर_pending_चयन(__func__);

	/* scr_addr must be 8 byte aligned */
	data.s.scraddr = scr_addr >> 3;
	data.s.len = 1;
	data.s.did = CVMX_OCT_DID_TAG_SWTAG;
	data.s.रुको = रुको;
	cvmx_send_single(data.u64);
पूर्ण

/**
 * Asynchronous work request.  Work is requested from the POW unit,
 * and should later be checked with function
 * cvmx_घात_work_response_async.  This function रुकोs क्रम any previous
 * tag चयन to complete beक्रमe requesting the new work.
 *
 * @scr_addr: Scratch memory address that response will be वापसed
 *	      to, which is either a valid WQE, or a response with the
 *	      invalid bit set.	Byte address, must be 8 byte aligned.
 *
 * @रुको: 1 to cause response to रुको क्रम work to become available (or
 *		    समयout), 0 to cause response to वापस immediately
 */
अटल अंतरभूत व्योम cvmx_घात_work_request_async(पूर्णांक scr_addr,
					       cvmx_घात_रुको_t रुको)
अणु
	अगर (CVMX_ENABLE_POW_CHECKS)
		__cvmx_घात_warn_अगर_pending_चयन(__func__);

	/* Must not have a चयन pending when requesting work */
	cvmx_घात_tag_sw_रुको();
	cvmx_घात_work_request_async_nocheck(scr_addr, रुको);
पूर्ण

/**
 * Gets result of asynchronous work request.  Perक्रमms a IOBDMA sync
 * to रुको क्रम the response.
 *
 * @scr_addr: Scratch memory address to get result from Byte address,
 *	      must be 8 byte aligned.
 *
 * Returns: the WQE from the scratch रेजिस्टर, or शून्य अगर no
 * work was available.
 */
अटल अंतरभूत काष्ठा cvmx_wqe *cvmx_घात_work_response_async(पूर्णांक scr_addr)
अणु
	cvmx_घात_tag_load_resp_t result;

	CVMX_SYNCIOBDMA;
	result.u64 = cvmx_scratch_पढ़ो64(scr_addr);

	अगर (result.s_work.no_work)
		वापस शून्य;
	अन्यथा
		वापस (काष्ठा cvmx_wqe *) cvmx_phys_to_ptr(result.s_work.addr);
पूर्ण

/**
 * Checks अगर a work queue entry poपूर्णांकer वापसed by a work
 * request is valid.  It may be invalid due to no work
 * being available or due to a समयout.
 *
 * @wqe_ptr: poपूर्णांकer to a work queue entry वापसed by the POW
 *
 * Returns 0 अगर poपूर्णांकer is valid
 *	   1 अगर invalid (no work was वापसed)
 */
अटल अंतरभूत uपूर्णांक64_t cvmx_घात_work_invalid(काष्ठा cvmx_wqe *wqe_ptr)
अणु
	वापस wqe_ptr == शून्य;
पूर्ण

/**
 * Starts a tag चयन to the provided tag value and tag type.
 * Completion क्रम the tag चयन must be checked क्रम separately.  This
 * function करोes NOT update the work queue entry in dram to match tag
 * value and type, so the application must keep track of these अगर they
 * are important to the application.  This tag चयन command must not
 * be used क्रम चयनes to शून्य, as the tag चयन pending bit will be
 * set by the चयन request, but never cleared by the hardware.
 *
 * NOTE: This should not be used when चयनing from a शून्य tag.  Use
 * cvmx_घात_tag_sw_full() instead.
 *
 * This function करोes no checks, so the caller must ensure that any
 * previous tag चयन has completed.
 *
 * @tag:      new tag value
 * @tag_type: new tag type (ordered or atomic)
 */
अटल अंतरभूत व्योम cvmx_घात_tag_sw_nocheck(uपूर्णांक32_t tag,
					   क्रमागत cvmx_घात_tag_type tag_type)
अणु
	cvmx_addr_t ptr;
	cvmx_घात_tag_req_t tag_req;

	अगर (CVMX_ENABLE_POW_CHECKS) अणु
		cvmx_घात_tag_req_t current_tag;
		__cvmx_घात_warn_अगर_pending_चयन(__func__);
		current_tag = cvmx_घात_get_current_tag();
		अगर (current_tag.s.type == CVMX_POW_TAG_TYPE_शून्य_शून्य)
			pr_warn("%s called with NULL_NULL tag\n", __func__);
		अगर (current_tag.s.type == CVMX_POW_TAG_TYPE_शून्य)
			pr_warn("%s called with NULL tag\n", __func__);
		अगर ((current_tag.s.type == tag_type)
		   && (current_tag.s.tag == tag))
			pr_warn("%s called to perform a tag switch to the same tag\n",
				__func__);
		अगर (tag_type == CVMX_POW_TAG_TYPE_शून्य)
			pr_warn("%s called to perform a tag switch to NULL. Use cvmx_pow_tag_sw_null() instead\n",
				__func__);
	पूर्ण

	/*
	 * Note that WQE in DRAM is not updated here, as the POW करोes
	 * not पढ़ो from DRAM once the WQE is in flight.  See hardware
	 * manual क्रम complete details.	 It is the application's
	 * responsibility to keep track of the current tag value अगर
	 * that is important.
	 */

	tag_req.u64 = 0;
	tag_req.s.op = CVMX_POW_TAG_OP_SWTAG;
	tag_req.s.tag = tag;
	tag_req.s.type = tag_type;

	ptr.u64 = 0;
	ptr.sio.mem_region = CVMX_IO_SEG;
	ptr.sio.is_io = 1;
	ptr.sio.did = CVMX_OCT_DID_TAG_SWTAG;

	/* once this store arrives at POW, it will attempt the चयन
	   software must रुको क्रम the चयन to complete separately */
	cvmx_ग_लिखो_io(ptr.u64, tag_req.u64);
पूर्ण

/**
 * Starts a tag चयन to the provided tag value and tag type.
 * Completion क्रम the tag चयन must be checked क्रम separately.  This
 * function करोes NOT update the work queue entry in dram to match tag
 * value and type, so the application must keep track of these अगर they
 * are important to the application.  This tag चयन command must not
 * be used क्रम चयनes to शून्य, as the tag चयन pending bit will be
 * set by the चयन request, but never cleared by the hardware.
 *
 * NOTE: This should not be used when चयनing from a शून्य tag.  Use
 * cvmx_घात_tag_sw_full() instead.
 *
 * This function रुकोs क्रम any previous tag चयन to complete, and also
 * displays an error on tag चयनes to शून्य.
 *
 * @tag:      new tag value
 * @tag_type: new tag type (ordered or atomic)
 */
अटल अंतरभूत व्योम cvmx_घात_tag_sw(uपूर्णांक32_t tag,
				   क्रमागत cvmx_घात_tag_type tag_type)
अणु
	अगर (CVMX_ENABLE_POW_CHECKS)
		__cvmx_घात_warn_अगर_pending_चयन(__func__);

	/*
	 * Note that WQE in DRAM is not updated here, as the POW करोes
	 * not पढ़ो from DRAM once the WQE is in flight.  See hardware
	 * manual क्रम complete details.	 It is the application's
	 * responsibility to keep track of the current tag value अगर
	 * that is important.
	 */

	/*
	 * Ensure that there is not a pending tag चयन, as a tag
	 * चयन cannot be started अगर a previous चयन is still
	 * pending.
	 */
	cvmx_घात_tag_sw_रुको();
	cvmx_घात_tag_sw_nocheck(tag, tag_type);
पूर्ण

/**
 * Starts a tag चयन to the provided tag value and tag type.
 * Completion क्रम the tag चयन must be checked क्रम separately.  This
 * function करोes NOT update the work queue entry in dram to match tag
 * value and type, so the application must keep track of these अगर they
 * are important to the application.  This tag चयन command must not
 * be used क्रम चयनes to शून्य, as the tag चयन pending bit will be
 * set by the चयन request, but never cleared by the hardware.
 *
 * This function must be used क्रम tag चयनes from शून्य.
 *
 * This function करोes no checks, so the caller must ensure that any
 * previous tag चयन has completed.
 *
 * @wqp:      poपूर्णांकer to work queue entry to submit.  This entry is
 *	      updated to match the other parameters
 * @tag:      tag value to be asचिन्हित to work queue entry
 * @tag_type: type of tag
 * @group:    group value क्रम the work queue entry.
 */
अटल अंतरभूत व्योम cvmx_घात_tag_sw_full_nocheck(काष्ठा cvmx_wqe *wqp, uपूर्णांक32_t tag,
						क्रमागत cvmx_घात_tag_type tag_type,
						uपूर्णांक64_t group)
अणु
	cvmx_addr_t ptr;
	cvmx_घात_tag_req_t tag_req;

	अगर (CVMX_ENABLE_POW_CHECKS) अणु
		cvmx_घात_tag_req_t current_tag;
		__cvmx_घात_warn_अगर_pending_चयन(__func__);
		current_tag = cvmx_घात_get_current_tag();
		अगर (current_tag.s.type == CVMX_POW_TAG_TYPE_शून्य_शून्य)
			pr_warn("%s called with NULL_NULL tag\n", __func__);
		अगर ((current_tag.s.type == tag_type)
		   && (current_tag.s.tag == tag))
			pr_warn("%s called to perform a tag switch to the same tag\n",
				__func__);
		अगर (tag_type == CVMX_POW_TAG_TYPE_शून्य)
			pr_warn("%s called to perform a tag switch to NULL. Use cvmx_pow_tag_sw_null() instead\n",
				__func__);
		अगर (wqp != cvmx_phys_to_ptr(0x80))
			अगर (wqp != cvmx_घात_get_current_wqp())
				pr_warn("%s passed WQE(%p) doesn't match the address in the POW(%p)\n",
					__func__, wqp,
					cvmx_घात_get_current_wqp());
	पूर्ण

	/*
	 * Note that WQE in DRAM is not updated here, as the POW करोes
	 * not पढ़ो from DRAM once the WQE is in flight.  See hardware
	 * manual क्रम complete details.	 It is the application's
	 * responsibility to keep track of the current tag value अगर
	 * that is important.
	 */

	tag_req.u64 = 0;
	tag_req.s.op = CVMX_POW_TAG_OP_SWTAG_FULL;
	tag_req.s.tag = tag;
	tag_req.s.type = tag_type;
	tag_req.s.grp = group;

	ptr.u64 = 0;
	ptr.sio.mem_region = CVMX_IO_SEG;
	ptr.sio.is_io = 1;
	ptr.sio.did = CVMX_OCT_DID_TAG_SWTAG;
	ptr.sio.offset = CAST64(wqp);

	/*
	 * once this store arrives at POW, it will attempt the चयन
	 * software must रुको क्रम the चयन to complete separately.
	 */
	cvmx_ग_लिखो_io(ptr.u64, tag_req.u64);
पूर्ण

/**
 * Starts a tag चयन to the provided tag value and tag type.
 * Completion क्रम the tag चयन must be checked क्रम separately.  This
 * function करोes NOT update the work queue entry in dram to match tag
 * value and type, so the application must keep track of these अगर they
 * are important to the application.  This tag चयन command must not
 * be used क्रम चयनes to शून्य, as the tag चयन pending bit will be
 * set by the चयन request, but never cleared by the hardware.
 *
 * This function must be used क्रम tag चयनes from शून्य.
 *
 * This function रुकोs क्रम any pending tag चयनes to complete
 * beक्रमe requesting the tag चयन.
 *
 * @wqp:      poपूर्णांकer to work queue entry to submit.  This entry is updated
 *	      to match the other parameters
 * @tag:      tag value to be asचिन्हित to work queue entry
 * @tag_type: type of tag
 * @group:	group value क्रम the work queue entry.
 */
अटल अंतरभूत व्योम cvmx_घात_tag_sw_full(काष्ठा cvmx_wqe *wqp, uपूर्णांक32_t tag,
					क्रमागत cvmx_घात_tag_type tag_type,
					uपूर्णांक64_t group)
अणु
	अगर (CVMX_ENABLE_POW_CHECKS)
		__cvmx_घात_warn_अगर_pending_चयन(__func__);

	/*
	 * Ensure that there is not a pending tag चयन, as a tag
	 * चयन cannot be started अगर a previous चयन is still
	 * pending.
	 */
	cvmx_घात_tag_sw_रुको();
	cvmx_घात_tag_sw_full_nocheck(wqp, tag, tag_type, group);
पूर्ण

/**
 * Switch to a शून्य tag, which ends any ordering or
 * synchronization provided by the POW क्रम the current
 * work queue entry.  This operation completes immediately,
 * so completion should not be रुकोed क्रम.
 * This function करोes NOT रुको क्रम previous tag चयनes to complete,
 * so the caller must ensure that any previous tag चयनes have completed.
 */
अटल अंतरभूत व्योम cvmx_घात_tag_sw_null_nocheck(व्योम)
अणु
	cvmx_addr_t ptr;
	cvmx_घात_tag_req_t tag_req;

	अगर (CVMX_ENABLE_POW_CHECKS) अणु
		cvmx_घात_tag_req_t current_tag;
		__cvmx_घात_warn_अगर_pending_चयन(__func__);
		current_tag = cvmx_घात_get_current_tag();
		अगर (current_tag.s.type == CVMX_POW_TAG_TYPE_शून्य_शून्य)
			pr_warn("%s called with NULL_NULL tag\n", __func__);
		अगर (current_tag.s.type == CVMX_POW_TAG_TYPE_शून्य)
			pr_warn("%s called when we already have a NULL tag\n",
				__func__);
	पूर्ण

	tag_req.u64 = 0;
	tag_req.s.op = CVMX_POW_TAG_OP_SWTAG;
	tag_req.s.type = CVMX_POW_TAG_TYPE_शून्य;

	ptr.u64 = 0;
	ptr.sio.mem_region = CVMX_IO_SEG;
	ptr.sio.is_io = 1;
	ptr.sio.did = CVMX_OCT_DID_TAG_TAG1;

	cvmx_ग_लिखो_io(ptr.u64, tag_req.u64);

	/* चयन to शून्य completes immediately */
पूर्ण

/**
 * Switch to a शून्य tag, which ends any ordering or
 * synchronization provided by the POW क्रम the current
 * work queue entry.  This operation completes immediately,
 * so completion should not be रुकोed क्रम.
 * This function रुकोs क्रम any pending tag चयनes to complete
 * beक्रमe requesting the चयन to शून्य.
 */
अटल अंतरभूत व्योम cvmx_घात_tag_sw_null(व्योम)
अणु
	अगर (CVMX_ENABLE_POW_CHECKS)
		__cvmx_घात_warn_अगर_pending_चयन(__func__);

	/*
	 * Ensure that there is not a pending tag चयन, as a tag
	 * चयन cannot be started अगर a previous चयन is still
	 * pending.
	 */
	cvmx_घात_tag_sw_रुको();
	cvmx_घात_tag_sw_null_nocheck();

	/* चयन to शून्य completes immediately */
पूर्ण

/**
 * Submits work to an input queue.  This function updates the work
 * queue entry in DRAM to match the arguments given.  Note that the
 * tag provided is क्रम the work queue entry submitted, and is
 * unrelated to the tag that the core currently holds.
 *
 * @wqp:      poपूर्णांकer to work queue entry to submit.  This entry is
 *	      updated to match the other parameters
 * @tag:      tag value to be asचिन्हित to work queue entry
 * @tag_type: type of tag
 * @qos:      Input queue to add to.
 * @grp:      group value क्रम the work queue entry.
 */
अटल अंतरभूत व्योम cvmx_घात_work_submit(काष्ठा cvmx_wqe *wqp, uपूर्णांक32_t tag,
					क्रमागत cvmx_घात_tag_type tag_type,
					uपूर्णांक64_t qos, uपूर्णांक64_t grp)
अणु
	cvmx_addr_t ptr;
	cvmx_घात_tag_req_t tag_req;

	wqp->word1.tag = tag;
	wqp->word1.tag_type = tag_type;

	cvmx_wqe_set_qos(wqp, qos);
	cvmx_wqe_set_grp(wqp, grp);

	tag_req.u64 = 0;
	tag_req.s.op = CVMX_POW_TAG_OP_ADDWQ;
	tag_req.s.type = tag_type;
	tag_req.s.tag = tag;
	tag_req.s.qos = qos;
	tag_req.s.grp = grp;

	ptr.u64 = 0;
	ptr.sio.mem_region = CVMX_IO_SEG;
	ptr.sio.is_io = 1;
	ptr.sio.did = CVMX_OCT_DID_TAG_TAG1;
	ptr.sio.offset = cvmx_ptr_to_phys(wqp);

	/*
	 * SYNC ग_लिखो to memory beक्रमe the work submit.	 This is
	 * necessary as POW may पढ़ो values from DRAM at this समय.
	 */
	CVMX_SYNCWS;
	cvmx_ग_लिखो_io(ptr.u64, tag_req.u64);
पूर्ण

/**
 * This function sets the group mask क्रम a core.  The group mask
 * indicates which groups each core will accept work from. There are
 * 16 groups.
 *
 * @core_num:	core to apply mask to
 * @mask:   Group mask. There are 16 groups, so only bits 0-15 are valid,
 *		 representing groups 0-15.
 *		 Each 1 bit in the mask enables the core to accept work from
 *		 the corresponding group.
 */
अटल अंतरभूत व्योम cvmx_घात_set_group_mask(uपूर्णांक64_t core_num, uपूर्णांक64_t mask)
अणु
	जोड़ cvmx_घात_pp_grp_mskx grp_msk;

	grp_msk.u64 = cvmx_पढ़ो_csr(CVMX_POW_PP_GRP_MSKX(core_num));
	grp_msk.s.grp_msk = mask;
	cvmx_ग_लिखो_csr(CVMX_POW_PP_GRP_MSKX(core_num), grp_msk.u64);
पूर्ण

/**
 * This function sets POW अटल priorities क्रम a core. Each input queue has
 * an associated priority value.
 *
 * @core_num:	core to apply priorities to
 * @priority:	Vector of 8 priorities, one per POW Input Queue (0-7).
 *		     Highest priority is 0 and lowest is 7. A priority value
 *		     of 0xF inकाष्ठाs POW to skip the Input Queue when
 *		     scheduling to this specअगरic core.
 *		     NOTE: priorities should not have gaps in values, meaning
 *			   अणु0,1,1,1,1,1,1,1पूर्ण is a valid configuration जबतक
 *			   अणु0,2,2,2,2,2,2,2पूर्ण is not.
 */
अटल अंतरभूत व्योम cvmx_घात_set_priority(uपूर्णांक64_t core_num,
					 स्थिर uपूर्णांक8_t priority[])
अणु
	/* POW priorities are supported on CN5xxx and later */
	अगर (!OCTEON_IS_MODEL(OCTEON_CN3XXX)) अणु
		जोड़ cvmx_घात_pp_grp_mskx grp_msk;

		grp_msk.u64 = cvmx_पढ़ो_csr(CVMX_POW_PP_GRP_MSKX(core_num));
		grp_msk.s.qos0_pri = priority[0];
		grp_msk.s.qos1_pri = priority[1];
		grp_msk.s.qos2_pri = priority[2];
		grp_msk.s.qos3_pri = priority[3];
		grp_msk.s.qos4_pri = priority[4];
		grp_msk.s.qos5_pri = priority[5];
		grp_msk.s.qos6_pri = priority[6];
		grp_msk.s.qos7_pri = priority[7];

		/* Detect gaps between priorities and flag error */
		अणु
			पूर्णांक i;
			uपूर्णांक32_t prio_mask = 0;

			क्रम (i = 0; i < 8; i++)
				अगर (priority[i] != 0xF)
					prio_mask |= 1 << priority[i];

			अगर (prio_mask ^ ((1 << cvmx_pop(prio_mask)) - 1)) अणु
				pr_err("POW static priorities should be "
				       "contiguous (0x%llx)\n",
				     (अचिन्हित दीर्घ दीर्घ)prio_mask);
				वापस;
			पूर्ण
		पूर्ण

		cvmx_ग_लिखो_csr(CVMX_POW_PP_GRP_MSKX(core_num), grp_msk.u64);
	पूर्ण
पूर्ण

/**
 * Perक्रमms a tag चयन and then an immediate deschedule. This completes
 * immediately, so completion must not be रुकोed क्रम.  This function करोes NOT
 * update the wqe in DRAM to match arguments.
 *
 * This function करोes NOT रुको क्रम any prior tag चयनes to complete, so the
 * calling code must करो this.
 *
 * Note the following CAVEAT of the Octeon HW behavior when
 * re-scheduling DE-SCHEDULEd items whose (next) state is
 * ORDERED:
 *   - If there are no चयनes pending at the समय that the
 *     HW executes the de-schedule, the HW will only re-schedule
 *     the head of the FIFO associated with the given tag. This
 *     means that in many respects, the HW treats this ORDERED
 *     tag as an ATOMIC tag. Note that in the SWTAG_DESCH
 *     हाल (to an ORDERED tag), the HW will करो the चयन
 *     beक्रमe the deschedule whenever it is possible to करो
 *     the चयन immediately, so it may often look like
 *     this हाल.
 *   - If there is a pending चयन to ORDERED at the समय
 *     the HW executes the de-schedule, the HW will perक्रमm
 *     the चयन at the समय it re-schedules, and will be
 *     able to reschedule any/all of the entries with the
 *     same tag.
 * Due to this behavior, the RECOMMENDATION to software is
 * that they have a (next) state of ATOMIC when they
 * DE-SCHEDULE. If an ORDERED tag is what was really desired,
 * SW can choose to immediately चयन to an ORDERED tag
 * after the work (that has an ATOMIC tag) is re-scheduled.
 * Note that since there are never any tag चयनes pending
 * when the HW re-schedules, this चयन can be IMMEDIATE upon
 * the reception of the poपूर्णांकer during the re-schedule.
 *
 * @tag:      New tag value
 * @tag_type: New tag type
 * @group:    New group value
 * @no_sched: Control whether this work queue entry will be rescheduled.
 *		   - 1 : करोn't schedule this work
 *		   - 0 : allow this work to be scheduled.
 */
अटल अंतरभूत व्योम cvmx_घात_tag_sw_desched_nocheck(
	uपूर्णांक32_t tag,
	क्रमागत cvmx_घात_tag_type tag_type,
	uपूर्णांक64_t group,
	uपूर्णांक64_t no_sched)
अणु
	cvmx_addr_t ptr;
	cvmx_घात_tag_req_t tag_req;

	अगर (CVMX_ENABLE_POW_CHECKS) अणु
		cvmx_घात_tag_req_t current_tag;
		__cvmx_घात_warn_अगर_pending_चयन(__func__);
		current_tag = cvmx_घात_get_current_tag();
		अगर (current_tag.s.type == CVMX_POW_TAG_TYPE_शून्य_शून्य)
			pr_warn("%s called with NULL_NULL tag\n", __func__);
		अगर (current_tag.s.type == CVMX_POW_TAG_TYPE_शून्य)
			pr_warn("%s called with NULL tag. Deschedule not allowed from NULL state\n",
				__func__);
		अगर ((current_tag.s.type != CVMX_POW_TAG_TYPE_ATOMIC)
			&& (tag_type != CVMX_POW_TAG_TYPE_ATOMIC))
			pr_warn("%s called where neither the before or after tag is ATOMIC\n",
				__func__);
	पूर्ण

	tag_req.u64 = 0;
	tag_req.s.op = CVMX_POW_TAG_OP_SWTAG_DESCH;
	tag_req.s.tag = tag;
	tag_req.s.type = tag_type;
	tag_req.s.grp = group;
	tag_req.s.no_sched = no_sched;

	ptr.u64 = 0;
	ptr.sio.mem_region = CVMX_IO_SEG;
	ptr.sio.is_io = 1;
	ptr.sio.did = CVMX_OCT_DID_TAG_TAG3;
	/*
	 * since TAG3 is used, this store will clear the local pending
	 * चयन bit.
	 */
	cvmx_ग_लिखो_io(ptr.u64, tag_req.u64);
पूर्ण

/**
 * Perक्रमms a tag चयन and then an immediate deschedule. This completes
 * immediately, so completion must not be रुकोed क्रम.  This function करोes NOT
 * update the wqe in DRAM to match arguments.
 *
 * This function रुकोs क्रम any prior tag चयनes to complete, so the
 * calling code may call this function with a pending tag चयन.
 *
 * Note the following CAVEAT of the Octeon HW behavior when
 * re-scheduling DE-SCHEDULEd items whose (next) state is
 * ORDERED:
 *   - If there are no चयनes pending at the समय that the
 *     HW executes the de-schedule, the HW will only re-schedule
 *     the head of the FIFO associated with the given tag. This
 *     means that in many respects, the HW treats this ORDERED
 *     tag as an ATOMIC tag. Note that in the SWTAG_DESCH
 *     हाल (to an ORDERED tag), the HW will करो the चयन
 *     beक्रमe the deschedule whenever it is possible to करो
 *     the चयन immediately, so it may often look like
 *     this हाल.
 *   - If there is a pending चयन to ORDERED at the समय
 *     the HW executes the de-schedule, the HW will perक्रमm
 *     the चयन at the समय it re-schedules, and will be
 *     able to reschedule any/all of the entries with the
 *     same tag.
 * Due to this behavior, the RECOMMENDATION to software is
 * that they have a (next) state of ATOMIC when they
 * DE-SCHEDULE. If an ORDERED tag is what was really desired,
 * SW can choose to immediately चयन to an ORDERED tag
 * after the work (that has an ATOMIC tag) is re-scheduled.
 * Note that since there are never any tag चयनes pending
 * when the HW re-schedules, this चयन can be IMMEDIATE upon
 * the reception of the poपूर्णांकer during the re-schedule.
 *
 * @tag:      New tag value
 * @tag_type: New tag type
 * @group:    New group value
 * @no_sched: Control whether this work queue entry will be rescheduled.
 *		   - 1 : करोn't schedule this work
 *		   - 0 : allow this work to be scheduled.
 */
अटल अंतरभूत व्योम cvmx_घात_tag_sw_desched(uपूर्णांक32_t tag,
					   क्रमागत cvmx_घात_tag_type tag_type,
					   uपूर्णांक64_t group, uपूर्णांक64_t no_sched)
अणु
	अगर (CVMX_ENABLE_POW_CHECKS)
		__cvmx_घात_warn_अगर_pending_चयन(__func__);

	/* Need to make sure any ग_लिखोs to the work queue entry are complete */
	CVMX_SYNCWS;
	/*
	 * Ensure that there is not a pending tag चयन, as a tag
	 * चयन cannot be started अगर a previous चयन is still
	 * pending.
	 */
	cvmx_घात_tag_sw_रुको();
	cvmx_घात_tag_sw_desched_nocheck(tag, tag_type, group, no_sched);
पूर्ण

/**
 * Deschedules the current work queue entry.
 *
 * @no_sched: no schedule flag value to be set on the work queue
 *	      entry.  If this is set the entry will not be
 *	      rescheduled.
 */
अटल अंतरभूत व्योम cvmx_घात_desched(uपूर्णांक64_t no_sched)
अणु
	cvmx_addr_t ptr;
	cvmx_घात_tag_req_t tag_req;

	अगर (CVMX_ENABLE_POW_CHECKS) अणु
		cvmx_घात_tag_req_t current_tag;
		__cvmx_घात_warn_अगर_pending_चयन(__func__);
		current_tag = cvmx_घात_get_current_tag();
		अगर (current_tag.s.type == CVMX_POW_TAG_TYPE_शून्य_शून्य)
			pr_warn("%s called with NULL_NULL tag\n", __func__);
		अगर (current_tag.s.type == CVMX_POW_TAG_TYPE_शून्य)
			pr_warn("%s called with NULL tag. Deschedule not expected from NULL state\n",
				__func__);
	पूर्ण

	/* Need to make sure any ग_लिखोs to the work queue entry are complete */
	CVMX_SYNCWS;

	tag_req.u64 = 0;
	tag_req.s.op = CVMX_POW_TAG_OP_DESCH;
	tag_req.s.no_sched = no_sched;

	ptr.u64 = 0;
	ptr.sio.mem_region = CVMX_IO_SEG;
	ptr.sio.is_io = 1;
	ptr.sio.did = CVMX_OCT_DID_TAG_TAG3;
	/*
	 * since TAG3 is used, this store will clear the local pending
	 * चयन bit.
	 */
	cvmx_ग_लिखो_io(ptr.u64, tag_req.u64);
पूर्ण

/****************************************************
* Define usage of bits within the 32 bit tag values.
*****************************************************/

/*
 * Number of bits of the tag used by software.	The SW bits are always
 * a contiguous block of the high starting at bit 31.  The hardware
 * bits are always the low bits.  By शेष, the top 8 bits of the
 * tag are reserved क्रम software, and the low 24 are set by the IPD
 * unit.
 */
#घोषणा CVMX_TAG_SW_BITS    (8)
#घोषणा CVMX_TAG_SW_SHIFT   (32 - CVMX_TAG_SW_BITS)

/* Below is the list of values क्रम the top 8 bits of the tag. */
/*
 * Tag values with top byte of this value are reserved क्रम पूर्णांकernal
 * executive uses.
 */
#घोषणा CVMX_TAG_SW_BITS_INTERNAL  0x1
/* The executive भागides the reमुख्यing 24 bits as follows:
 *  - the upper 8 bits (bits 23 - 16 of the tag) define a subgroup
 *
 *  - the lower 16 bits (bits 15 - 0 of the tag) define are the value
 *    with the subgroup
 *
 * Note that this section describes the क्रमmat of tags generated by
 * software - refer to the hardware करोcumentation क्रम a description of
 * the tags values generated by the packet input hardware.  Subgroups
 * are defined here.
 */
/* Mask क्रम the value portion of the tag */
#घोषणा CVMX_TAG_SUBGROUP_MASK	0xFFFF
#घोषणा CVMX_TAG_SUBGROUP_SHIFT 16
#घोषणा CVMX_TAG_SUBGROUP_PKO  0x1

/* End of executive tag subgroup definitions */

/*
 * The reमुख्यing values software bit values 0x2 - 0xff are available
 * क्रम application use.
 */

/**
 * This function creates a 32 bit tag value from the two values provided.
 *
 * @sw_bits: The upper bits (number depends on configuration) are set
 *	     to this value.  The reमुख्यder of bits are set by the
 *	     hw_bits parameter.
 *
 * @hw_bits: The lower bits (number depends on configuration) are set
 *	     to this value.  The reमुख्यder of bits are set by the
 *	     sw_bits parameter.
 *
 * Returns 32 bit value of the combined hw and sw bits.
 */
अटल अंतरभूत uपूर्णांक32_t cvmx_घात_tag_compose(uपूर्णांक64_t sw_bits, uपूर्णांक64_t hw_bits)
अणु
	वापस ((sw_bits & cvmx_build_mask(CVMX_TAG_SW_BITS)) <<
			CVMX_TAG_SW_SHIFT) |
		(hw_bits & cvmx_build_mask(32 - CVMX_TAG_SW_BITS));
पूर्ण

/**
 * Extracts the bits allocated क्रम software use from the tag
 *
 * @tag:    32 bit tag value
 *
 * Returns N bit software tag value, where N is configurable with the
 * CVMX_TAG_SW_BITS define
 */
अटल अंतरभूत uपूर्णांक32_t cvmx_घात_tag_get_sw_bits(uपूर्णांक64_t tag)
अणु
	वापस (tag >> (32 - CVMX_TAG_SW_BITS)) &
		cvmx_build_mask(CVMX_TAG_SW_BITS);
पूर्ण

/**
 *
 * Extracts the bits allocated क्रम hardware use from the tag
 *
 * @tag:    32 bit tag value
 *
 * Returns (32 - N) bit software tag value, where N is configurable
 * with the CVMX_TAG_SW_BITS define
 */
अटल अंतरभूत uपूर्णांक32_t cvmx_घात_tag_get_hw_bits(uपूर्णांक64_t tag)
अणु
	वापस tag & cvmx_build_mask(32 - CVMX_TAG_SW_BITS);
पूर्ण

/**
 * Store the current POW पूर्णांकernal state पूर्णांकo the supplied
 * buffer. It is recommended that you pass a buffer of at least
 * 128KB. The क्रमmat of the capture may change based on SDK
 * version and Octeon chip.
 *
 * @buffer: Buffer to store capture पूर्णांकo
 * @buffer_size:
 *		 The size of the supplied buffer
 *
 * Returns Zero on success, negative on failure
 */
बाह्य पूर्णांक cvmx_घात_capture(व्योम *buffer, पूर्णांक buffer_size);

/**
 * Dump a POW capture to the console in a human पढ़ोable क्रमmat.
 *
 * @buffer: POW capture from cvmx_घात_capture()
 * @buffer_size:
 *		 Size of the buffer
 */
बाह्य व्योम cvmx_घात_display(व्योम *buffer, पूर्णांक buffer_size);

/**
 * Return the number of POW entries supported by this chip
 *
 * Returns Number of POW entries
 */
बाह्य पूर्णांक cvmx_घात_get_num_entries(व्योम);

#पूर्ण_अगर /* __CVMX_POW_H__ */
