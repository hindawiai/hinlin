<शैली गुरु>
/*
 * Copyright (c) 2006, 2007, 2008, 2009, 2010 QLogic Corporation.
 * All rights reserved.
 * Copyright (c) 2003, 2004, 2005, 2006 PathScale, Inc. All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary क्रमms, with or
 *     without modअगरication, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary क्रमm must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the करोcumentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#अगर_अघोषित _QIB_COMMON_H
#घोषणा _QIB_COMMON_H

/*
 * This file contains defines, काष्ठाures, etc. that are used
 * to communicate between kernel and user code.
 */

/* This is the IEEE-asचिन्हित OUI क्रम QLogic Inc. QLogic_IB */
#घोषणा QIB_SRC_OUI_1 0x00
#घोषणा QIB_SRC_OUI_2 0x11
#घोषणा QIB_SRC_OUI_3 0x75

/* version of protocol header (known to chip also). In the दीर्घ run,
 * we should be able to generate and accept a range of version numbers;
 * क्रम now we only accept one, and it's compiled in.
 */
#घोषणा IPS_PROTO_VERSION 2

/*
 * These are compile समय स्थिरants that you may want to enable or disable
 * अगर you are trying to debug problems with code or perक्रमmance.
 * QIB_VERBOSE_TRACING define as 1 अगर you want additional tracing in
 * fastpath code
 * QIB_TRACE_REGWRITES define as 1 अगर you want रेजिस्टर ग_लिखोs to be
 * traced in fastpath code
 * _QIB_TRACING define as 0 अगर you want to हटाओ all tracing in a
 * compilation unit
 */

/*
 * The value in the BTH QP field that QLogic_IB uses to dअगरferentiate
 * an qlogic_ib protocol IB packet vs standard IB transport
 * This it needs to be even (0x656b78), because the LSB is someबार
 * used क्रम the MSB of context. The change may cause a problem
 * पूर्णांकeroperating with older software.
 */
#घोषणा QIB_KD_QP 0x656b78

/*
 * These are the status bits पढ़ोable (in ascii क्रमm, 64bit value)
 * from the "status" sysfs file.  For binary compatibility, values
 * must reमुख्य as is; हटाओd states can be reused क्रम dअगरferent
 * purposes.
 */
#घोषणा QIB_STATUS_INITTED       0x1    /* basic initialization करोne */
/* Chip has been found and initted */
#घोषणा QIB_STATUS_CHIP_PRESENT 0x20
/* IB link is at ACTIVE, usable क्रम data traffic */
#घोषणा QIB_STATUS_IB_READY     0x40
/* link is configured, LID, MTU, etc. have been set */
#घोषणा QIB_STATUS_IB_CONF      0x80
/* A Fatal hardware error has occurred. */
#घोषणा QIB_STATUS_HWERROR     0x200

/*
 * The list of usermode accessible रेजिस्टरs.  Also see Reg_* later in file.
 */
क्रमागत qib_ureg अणु
	/* (RO)  DMA RcvHdr to be used next. */
	ur_rcvhdrtail = 0,
	/* (RW)  RcvHdr entry to be processed next by host. */
	ur_rcvhdrhead = 1,
	/* (RO)  Index of next Eager index to use. */
	ur_rcvegrindextail = 2,
	/* (RW)  Eager TID to be processed next */
	ur_rcvegrindexhead = 3,
	/* For पूर्णांकernal use only; max रेजिस्टर number. */
	_QIB_UregMax
पूर्ण;

/* bit values क्रम spi_runसमय_flags */
#घोषणा QIB_RUNTIME_PCIE                0x0002
#घोषणा QIB_RUNTIME_FORCE_WC_ORDER      0x0004
#घोषणा QIB_RUNTIME_RCVHDR_COPY         0x0008
#घोषणा QIB_RUNTIME_MASTER              0x0010
#घोषणा QIB_RUNTIME_RCHK                0x0020
#घोषणा QIB_RUNTIME_NODMA_RTAIL         0x0080
#घोषणा QIB_RUNTIME_SPECIAL_TRIGGER     0x0100
#घोषणा QIB_RUNTIME_SDMA                0x0200
#घोषणा QIB_RUNTIME_FORCE_PIOAVAIL      0x0400
#घोषणा QIB_RUNTIME_PIO_REGSWAPPED      0x0800
#घोषणा QIB_RUNTIME_CTXT_MSB_IN_QP      0x1000
#घोषणा QIB_RUNTIME_CTXT_REसूचीECT       0x2000
#घोषणा QIB_RUNTIME_HDRSUPP             0x4000

/*
 * This काष्ठाure is वापसed by qib_userinit() immediately after
 * खोलो to get implementation-specअगरic info, and info specअगरic to this
 * instance.
 *
 * This काष्ठा must have explict pad fields where type sizes
 * may result in dअगरferent alignments between 32 and 64 bit
 * programs, since the 64 bit * bit kernel requires the user code
 * to have matching offsets
 */
काष्ठा qib_base_info अणु
	/* version of hardware, क्रम feature checking. */
	__u32 spi_hw_version;
	/* version of software, क्रम feature checking. */
	__u32 spi_sw_version;
	/* QLogic_IB context asचिन्हित, goes पूर्णांकo sent packets */
	__u16 spi_ctxt;
	__u16 spi_subctxt;
	/*
	 * IB MTU, packets IB data must be less than this.
	 * The MTU is in bytes, and will be a multiple of 4 bytes.
	 */
	__u32 spi_mtu;
	/*
	 * Size of a PIO buffer.  Any given packet's total size must be less
	 * than this (in words).  Included is the starting control word, so
	 * अगर 513 is वापसed, then total pkt size is 512 words or less.
	 */
	__u32 spi_piosize;
	/* size of the TID cache in qlogic_ib, in entries */
	__u32 spi_tidcnt;
	/* size of the TID Eager list in qlogic_ib, in entries */
	__u32 spi_tidegrcnt;
	/* size of a single receive header queue entry in words. */
	__u32 spi_rcvhdrent_size;
	/*
	 * Count of receive header queue entries allocated.
	 * This may be less than the spu_rcvhdrcnt passed in!.
	 */
	__u32 spi_rcvhdr_cnt;

	/* per-chip and other runसमय features biपंचांगap (QIB_RUNTIME_*) */
	__u32 spi_runसमय_flags;

	/* address where hardware receive header queue is mapped */
	__u64 spi_rcvhdr_base;

	/* user program. */

	/* base address of eager TID receive buffers used by hardware. */
	__u64 spi_rcv_egrbufs;

	/* Allocated by initialization code, not by protocol. */

	/*
	 * Size of each TID buffer in host memory, starting at
	 * spi_rcv_egrbufs.  The buffers are भवly contiguous.
	 */
	__u32 spi_rcv_egrbufsize;
	/*
	 * The special QP (queue pair) value that identअगरies an qlogic_ib
	 * protocol packet from standard IB packets.  More, probably much
	 * more, to be added.
	 */
	__u32 spi_qpair;

	/*
	 * User रेजिस्टर base क्रम init code, not to be used directly by
	 * protocol or applications.  Always poपूर्णांकs to chip रेजिस्टरs,
	 * क्रम normal or shared context.
	 */
	__u64 spi_uregbase;
	/*
	 * Maximum buffer size in bytes that can be used in a single TID
	 * entry (assuming the buffer is aligned to this boundary).  This is
	 * the minimum of what the hardware and software support Guaranteed
	 * to be a घातer of 2.
	 */
	__u32 spi_tid_maxsize;
	/*
	 * alignment of each pio send buffer (byte count
	 * to add to spi_piobufbase to get to second buffer)
	 */
	__u32 spi_pioalign;
	/*
	 * The index of the first pio buffer available to this process;
	 * needed to करो lookup in spi_pioavailaddr; not added to
	 * spi_piobufbase.
	 */
	__u32 spi_pioindex;
	 /* number of buffers mapped क्रम this process */
	__u32 spi_piocnt;

	/*
	 * Base address of ग_लिखोonly pio buffers क्रम this process.
	 * Each buffer has spi_piosize words, and is aligned on spi_pioalign
	 * boundaries.  spi_piocnt buffers are mapped from this address
	 */
	__u64 spi_piobufbase;

	/*
	 * Base address of पढ़ोonly memory copy of the pioavail रेजिस्टरs.
	 * There are 2 bits क्रम each buffer.
	 */
	__u64 spi_pioavailaddr;

	/*
	 * Address where driver updates a copy of the पूर्णांकerface and driver
	 * status (QIB_STATUS_*) as a 64 bit value.  It's followed by a
	 * link status qword (क्रमmerly combined with driver status), then a
	 * string indicating hardware error, अगर there was one.
	 */
	__u64 spi_status;

	/* number of chip ctxts available to user processes */
	__u32 spi_nctxts;
	__u16 spi_unit; /* unit number of chip we are using */
	__u16 spi_port; /* IB port number we are using */
	/* num bufs in each contiguous set */
	__u32 spi_rcv_egrperchunk;
	/* size in bytes of each contiguous set */
	__u32 spi_rcv_egrchunksize;
	/* total size of mmap to cover full rcvegrbuffers */
	__u32 spi_rcv_egrbuftotlen;
	__u32 spi_rhf_offset; /* dword offset in hdrqent क्रम rcvhdr flags */
	/* address of पढ़ोonly memory copy of the rcvhdrq tail रेजिस्टर. */
	__u64 spi_rcvhdr_tailaddr;

	/*
	 * shared memory pages क्रम subctxts अगर ctxt is shared; these cover
	 * all the processes in the group sharing a single context.
	 * all have enough space क्रम the num_subcontexts value on this job.
	 */
	__u64 spi_subctxt_uregbase;
	__u64 spi_subctxt_rcvegrbuf;
	__u64 spi_subctxt_rcvhdr_base;

	/* shared memory page क्रम send buffer disarm status */
	__u64 spi_sendbuf_status;
पूर्ण __aligned(8);

/*
 * This version number is given to the driver by the user code during
 * initialization in the spu_userversion field of qib_user_info, so
 * the driver can check क्रम compatibility with user code.
 *
 * The major version changes when data काष्ठाures
 * change in an incompatible way.  The driver must be the same or higher
 * क्रम initialization to succeed.  In some हालs, a higher version
 * driver will not पूर्णांकeroperate with older software, and initialization
 * will वापस an error.
 */
#घोषणा QIB_USER_SWMAJOR 1

/*
 * Minor version dअगरferences are always compatible
 * a within a major version, however अगर user software is larger
 * than driver software, some new features and/or काष्ठाure fields
 * may not be implemented; the user code must deal with this अगर it
 * cares, or it must पात after initialization reports the dअगरference.
 */
#घोषणा QIB_USER_SWMINOR 13

#घोषणा QIB_USER_SWVERSION ((QIB_USER_SWMAJOR << 16) | QIB_USER_SWMINOR)

#अगर_अघोषित QIB_KERN_TYPE
#घोषणा QIB_KERN_TYPE 0
#पूर्ण_अगर

/*
 * Similarly, this is the kernel version going back to the user.  It's
 * slightly dअगरferent, in that we want to tell अगर the driver was built as
 * part of a QLogic release, or from the driver from खोलोfabrics.org,
 * kernel.org, or a standard distribution, क्रम support reasons.
 * The high bit is 0 क्रम non-QLogic and 1 क्रम QLogic-built/supplied.
 *
 * It's वापसed by the driver to the user code during initialization in the
 * spi_sw_version field of qib_base_info, so the user code can in turn
 * check क्रम compatibility with the kernel.
*/
#घोषणा QIB_KERN_SWVERSION ((QIB_KERN_TYPE << 31) | QIB_USER_SWVERSION)

/*
 * Define the driver version number.  This is something that refers only
 * to the driver itself, not the software पूर्णांकerfaces it supports.
 */
#घोषणा QIB_DRIVER_VERSION_BASE "1.11"

/* create the final driver version string */
#अगर_घोषित QIB_IDSTR
#घोषणा QIB_DRIVER_VERSION QIB_DRIVER_VERSION_BASE " " QIB_IDSTR
#अन्यथा
#घोषणा QIB_DRIVER_VERSION QIB_DRIVER_VERSION_BASE
#पूर्ण_अगर

/*
 * If the unit is specअगरied via खोलो, HCA choice is fixed.  If port is
 * specअगरied, it's also fixed.  Otherwise we try to spपढ़ो contexts
 * across ports and HCAs, using dअगरferent algorithims.  WITHIN is
 * the old शेष, prior to this mechanism.
 */
#घोषणा QIB_PORT_ALG_ACROSS 0 /* round robin contexts across HCAs, then
			       * ports; this is the शेष */
#घोषणा QIB_PORT_ALG_WITHIN 1 /* use all contexts on an HCA (round robin
			       * active ports within), then next HCA */
#घोषणा QIB_PORT_ALG_COUNT 2 /* number of algorithm choices */

/*
 * This काष्ठाure is passed to qib_userinit() to tell the driver where
 * user code buffers are, sizes, etc.   The offsets and sizes of the
 * fields must reमुख्य unchanged, क्रम binary compatibility.  It can
 * be extended, अगर userversion is changed so user code can tell, अगर needed
 */
काष्ठा qib_user_info अणु
	/*
	 * version of user software, to detect compatibility issues.
	 * Should be set to QIB_USER_SWVERSION.
	 */
	__u32 spu_userversion;

	__u32 _spu_unused2;

	/* size of काष्ठा base_info to ग_लिखो to */
	__u32 spu_base_info_size;

	__u32 spu_port_alg; /* which QIB_PORT_ALG_*; unused user minor < 11 */

	/*
	 * If two or more processes wish to share a context, each process
	 * must set the spu_subctxt_cnt and spu_subctxt_id to the same
	 * values.  The only restriction on the spu_subctxt_id is that
	 * it be unique क्रम a given node.
	 */
	__u16 spu_subctxt_cnt;
	__u16 spu_subctxt_id;

	__u32 spu_port; /* IB port requested by user अगर > 0 */

	/*
	 * address of काष्ठा base_info to ग_लिखो to
	 */
	__u64 spu_base_info;

पूर्ण __aligned(8);

/* User commands. */

/* 16 available, was: old set up userspace (क्रम old user code) */
#घोषणा QIB_CMD_CTXT_INFO       17      /* find out what resources we got */
#घोषणा QIB_CMD_RECV_CTRL       18      /* control receipt of packets */
#घोषणा QIB_CMD_TID_UPDATE      19      /* update expected TID entries */
#घोषणा QIB_CMD_TID_FREE        20      /* मुक्त expected TID entries */
#घोषणा QIB_CMD_SET_PART_KEY    21      /* add partition key */
/* 22 available, was: वापस info on slave processes (क्रम old user code) */
#घोषणा QIB_CMD_ASSIGN_CTXT     23      /* allocate HCA and ctxt */
#घोषणा QIB_CMD_USER_INIT       24      /* set up userspace */
#घोषणा QIB_CMD_UNUSED_1        25
#घोषणा QIB_CMD_UNUSED_2        26
#घोषणा QIB_CMD_PIOAVAILUPD     27      /* क्रमce an update of PIOAvail reg */
#घोषणा QIB_CMD_POLL_TYPE       28      /* set the kind of polling we want */
#घोषणा QIB_CMD_ARMLAUNCH_CTRL  29      /* armlaunch detection control */
/* 30 is unused */
#घोषणा QIB_CMD_SDMA_INFLIGHT   31      /* sdma inflight counter request */
#घोषणा QIB_CMD_SDMA_COMPLETE   32      /* sdma completion counter request */
/* 33 available, was a testing feature  */
#घोषणा QIB_CMD_DISARM_BUFS     34      /* disarm send buffers w/ errors */
#घोषणा QIB_CMD_ACK_EVENT       35      /* ack & clear bits */
#घोषणा QIB_CMD_CPUS_LIST       36      /* list of cpus allocated, क्रम pinned
					 * processes: qib_cpus_list */

/*
 * QIB_CMD_ACK_EVENT obsoletes QIB_CMD_DISARM_BUFS, but we keep it क्रम
 * compatibility with libraries from previous release.   The ACK_EVENT
 * will take appropriate driver action (अगर any, just DISARM क्रम now),
 * then clear the bits passed in as part of the mask.  These bits are
 * in the first 64bit word at spi_sendbuf_status, and are passed to
 * the driver in the event_mask जोड़ as well.
 */
#घोषणा _QIB_EVENT_DISARM_BUFS_BIT	0
#घोषणा _QIB_EVENT_LINKDOWN_BIT		1
#घोषणा _QIB_EVENT_LID_CHANGE_BIT	2
#घोषणा _QIB_EVENT_LMC_CHANGE_BIT	3
#घोषणा _QIB_EVENT_SL2VL_CHANGE_BIT	4
#घोषणा _QIB_MAX_EVENT_BIT _QIB_EVENT_SL2VL_CHANGE_BIT

#घोषणा QIB_EVENT_DISARM_BUFS_BIT	(1UL << _QIB_EVENT_DISARM_BUFS_BIT)
#घोषणा QIB_EVENT_LINKDOWN_BIT		(1UL << _QIB_EVENT_LINKDOWN_BIT)
#घोषणा QIB_EVENT_LID_CHANGE_BIT	(1UL << _QIB_EVENT_LID_CHANGE_BIT)
#घोषणा QIB_EVENT_LMC_CHANGE_BIT	(1UL << _QIB_EVENT_LMC_CHANGE_BIT)
#घोषणा QIB_EVENT_SL2VL_CHANGE_BIT	(1UL << _QIB_EVENT_SL2VL_CHANGE_BIT)


/*
 * Poll types
 */
#घोषणा QIB_POLL_TYPE_ANYRCV     0x0
#घोषणा QIB_POLL_TYPE_URGENT     0x1

काष्ठा qib_ctxt_info अणु
	__u16 num_active;       /* number of active units */
	__u16 unit;             /* unit (chip) asचिन्हित to caller */
	__u16 port;             /* IB port asचिन्हित to caller (1-based) */
	__u16 ctxt;             /* ctxt on unit asचिन्हित to caller */
	__u16 subctxt;          /* subctxt on unit asचिन्हित to caller */
	__u16 num_ctxts;        /* number of ctxts available on unit */
	__u16 num_subctxts;     /* number of subctxts खोलोed on ctxt */
	__u16 rec_cpu;          /* cpu # क्रम affinity (ffff अगर none) */
पूर्ण;

काष्ठा qib_tid_info अणु
	__u32 tidcnt;
	/* make काष्ठाure same size in 32 and 64 bit */
	__u32 tid__unused;
	/* भव address of first page in transfer */
	__u64 tidvaddr;
	/* poपूर्णांकer (same size 32/64 bit) to __u16 tid array */
	__u64 tidlist;

	/*
	 * poपूर्णांकer (same size 32/64 bit) to biपंचांगap of TIDs used
	 * क्रम this call; checked क्रम being large enough at खोलो
	 */
	__u64 tidmap;
पूर्ण;

काष्ठा qib_cmd अणु
	__u32 type;                     /* command type */
	जोड़ अणु
		काष्ठा qib_tid_info tid_info;
		काष्ठा qib_user_info user_info;

		/*
		 * address in userspace where we should put the sdma
		 * inflight counter
		 */
		__u64 sdma_inflight;
		/*
		 * address in userspace where we should put the sdma
		 * completion counter
		 */
		__u64 sdma_complete;
		/* address in userspace of काष्ठा qib_ctxt_info to
		   ग_लिखो result to */
		__u64 ctxt_info;
		/* enable/disable receipt of packets */
		__u32 recv_ctrl;
		/* enable/disable armlaunch errors (non-zero to enable) */
		__u32 armlaunch_ctrl;
		/* partition key to set */
		__u16 part_key;
		/* user address of __u32 biपंचांगask of active slaves */
		__u64 slave_mask_addr;
		/* type of polling we want */
		__u16 poll_type;
		/* back pressure enable bit क्रम one particular context */
		__u8 ctxt_bp;
		/* qib_user_event_ack(), IPATH_EVENT_* bits */
		__u64 event_mask;
	पूर्ण cmd;
पूर्ण;

काष्ठा qib_iovec अणु
	/* Poपूर्णांकer to data, but same size 32 and 64 bit */
	__u64 iov_base;

	/*
	 * Length of data; करोn't need 64 bits, but want
	 * qib_sendpkt to reमुख्य same size as beक्रमe 32 bit changes, so...
	 */
	__u64 iov_len;
पूर्ण;

/*
 * Describes a single packet क्रम send.  Each packet can have one or more
 * buffers, but the total length (exclusive of IB headers) must be less
 * than the MTU, and अगर using the PIO method, entire packet length,
 * including IB headers, must be less than the qib_piosize value (words).
 * Use of this necessitates including sys/uपन.स
 */
काष्ठा __qib_sendpkt अणु
	__u32 sps_flags;        /* flags क्रम packet (TBD) */
	__u32 sps_cnt;          /* number of entries to use in sps_iov */
	/* array of iov's describing packet. TEMPORARY */
	काष्ठा qib_iovec sps_iov[4];
पूर्ण;

/*
 * Diagnostics can send a packet by "writing" the following
 * काष्ठाs to the diag data special file.
 * This allows a custom
 * pbc (+ अटल rate) qword, so that special modes and deliberate
 * changes to CRCs can be used. The elements were also re-ordered
 * क्रम better alignment and to aव्योम padding issues.
 */
#घोषणा _DIAG_XPKT_VERS 3
काष्ठा qib_diag_xpkt अणु
	__u16 version;
	__u16 unit;
	__u16 port;
	__u16 len;
	__u64 data;
	__u64 pbc_wd;
पूर्ण;

/*
 * Data layout in I2C flash (क्रम GUID, etc.)
 * All fields are little-endian binary unless otherwise stated
 */
#घोषणा QIB_FLASH_VERSION 2
काष्ठा qib_flash अणु
	/* flash layout version (QIB_FLASH_VERSION) */
	__u8 अगर_fversion;
	/* checksum protecting अगर_length bytes */
	__u8 अगर_csum;
	/*
	 * valid length (in use, रक्षित by अगर_csum), including
	 * अगर_fversion and अगर_csum themselves)
	 */
	__u8 अगर_length;
	/* the GUID, in network order */
	__u8 अगर_guid[8];
	/* number of GUIDs to use, starting from अगर_guid */
	__u8 अगर_numguid;
	/* the (last 10 अक्षरacters of) board serial number, in ASCII */
	अक्षर अगर_serial[12];
	/* board mfg date (YYYYMMDD ASCII) */
	अक्षर अगर_mfgdate[8];
	/* last board rework/test date (YYYYMMDD ASCII) */
	अक्षर अगर_testdate[8];
	/* logging of error counts, TBD */
	__u8 अगर_errcntp[4];
	/* घातered on hours, updated at driver unload */
	__u8 अगर_घातerhour[2];
	/* ASCII मुक्त-क्रमm comment field */
	अक्षर अगर_comment[32];
	/* Backwards compatible prefix क्रम दीर्घer QLogic Serial Numbers */
	अक्षर अगर_sprefix[4];
	/* 82 bytes used, min flash size is 128 bytes */
	__u8 अगर_future[46];
पूर्ण;

/*
 * These are the counters implemented in the chip, and are listed in order.
 * The InterCaps naming is taken straight from the chip spec.
 */
काष्ठा qlogic_ib_counters अणु
	__u64 LBIntCnt;
	__u64 LBFlowStallCnt;
	__u64 TxSDmaDescCnt;    /* was Reserved1 */
	__u64 TxUnsupVLErrCnt;
	__u64 TxDataPktCnt;
	__u64 TxFlowPktCnt;
	__u64 TxDwordCnt;
	__u64 TxLenErrCnt;
	__u64 TxMaxMinLenErrCnt;
	__u64 TxUnderrunCnt;
	__u64 TxFlowStallCnt;
	__u64 TxDroppedPktCnt;
	__u64 RxDroppedPktCnt;
	__u64 RxDataPktCnt;
	__u64 RxFlowPktCnt;
	__u64 RxDwordCnt;
	__u64 RxLenErrCnt;
	__u64 RxMaxMinLenErrCnt;
	__u64 RxICRCErrCnt;
	__u64 RxVCRCErrCnt;
	__u64 RxFlowCtrlErrCnt;
	__u64 RxBadFormatCnt;
	__u64 RxLinkProblemCnt;
	__u64 RxEBPCnt;
	__u64 RxLPCRCErrCnt;
	__u64 RxBufOvflCnt;
	__u64 RxTIDFullErrCnt;
	__u64 RxTIDValidErrCnt;
	__u64 RxPKeyMismatchCnt;
	__u64 RxP0HdrEgrOvflCnt;
	__u64 RxP1HdrEgrOvflCnt;
	__u64 RxP2HdrEgrOvflCnt;
	__u64 RxP3HdrEgrOvflCnt;
	__u64 RxP4HdrEgrOvflCnt;
	__u64 RxP5HdrEgrOvflCnt;
	__u64 RxP6HdrEgrOvflCnt;
	__u64 RxP7HdrEgrOvflCnt;
	__u64 RxP8HdrEgrOvflCnt;
	__u64 RxP9HdrEgrOvflCnt;
	__u64 RxP10HdrEgrOvflCnt;
	__u64 RxP11HdrEgrOvflCnt;
	__u64 RxP12HdrEgrOvflCnt;
	__u64 RxP13HdrEgrOvflCnt;
	__u64 RxP14HdrEgrOvflCnt;
	__u64 RxP15HdrEgrOvflCnt;
	__u64 RxP16HdrEgrOvflCnt;
	__u64 IBStatusChangeCnt;
	__u64 IBLinkErrRecoveryCnt;
	__u64 IBLinkDownedCnt;
	__u64 IBSymbolErrCnt;
	__u64 RxVL15DroppedPktCnt;
	__u64 RxOtherLocalPhyErrCnt;
	__u64 PcieRetryBufDiagQwordCnt;
	__u64 ExcessBufferOvflCnt;
	__u64 LocalLinkIntegrityErrCnt;
	__u64 RxVlErrCnt;
	__u64 RxDlidFltrCnt;
पूर्ण;

/*
 * The next set of defines are क्रम packet headers, and chip रेजिस्टर
 * and memory bits that are visible to and/or used by user-mode software.
 */

/* RcvHdrFlags bits */
#घोषणा QLOGIC_IB_RHF_LENGTH_MASK 0x7FF
#घोषणा QLOGIC_IB_RHF_LENGTH_SHIFT 0
#घोषणा QLOGIC_IB_RHF_RCVTYPE_MASK 0x7
#घोषणा QLOGIC_IB_RHF_RCVTYPE_SHIFT 11
#घोषणा QLOGIC_IB_RHF_EGRINDEX_MASK 0xFFF
#घोषणा QLOGIC_IB_RHF_EGRINDEX_SHIFT 16
#घोषणा QLOGIC_IB_RHF_SEQ_MASK 0xF
#घोषणा QLOGIC_IB_RHF_SEQ_SHIFT 0
#घोषणा QLOGIC_IB_RHF_HDRQ_OFFSET_MASK 0x7FF
#घोषणा QLOGIC_IB_RHF_HDRQ_OFFSET_SHIFT 4
#घोषणा QLOGIC_IB_RHF_H_ICRCERR   0x80000000
#घोषणा QLOGIC_IB_RHF_H_VCRCERR   0x40000000
#घोषणा QLOGIC_IB_RHF_H_PARITYERR 0x20000000
#घोषणा QLOGIC_IB_RHF_H_LENERR    0x10000000
#घोषणा QLOGIC_IB_RHF_H_MTUERR    0x08000000
#घोषणा QLOGIC_IB_RHF_H_IHDRERR   0x04000000
#घोषणा QLOGIC_IB_RHF_H_TIDERR    0x02000000
#घोषणा QLOGIC_IB_RHF_H_MKERR     0x01000000
#घोषणा QLOGIC_IB_RHF_H_IBERR     0x00800000
#घोषणा QLOGIC_IB_RHF_H_ERR_MASK  0xFF800000
#घोषणा QLOGIC_IB_RHF_L_USE_EGR   0x80000000
#घोषणा QLOGIC_IB_RHF_L_SWA       0x00008000
#घोषणा QLOGIC_IB_RHF_L_SWB       0x00004000

/* qlogic_ib header fields */
#घोषणा QLOGIC_IB_I_VERS_MASK 0xF
#घोषणा QLOGIC_IB_I_VERS_SHIFT 28
#घोषणा QLOGIC_IB_I_CTXT_MASK 0xF
#घोषणा QLOGIC_IB_I_CTXT_SHIFT 24
#घोषणा QLOGIC_IB_I_TID_MASK 0x7FF
#घोषणा QLOGIC_IB_I_TID_SHIFT 13
#घोषणा QLOGIC_IB_I_OFFSET_MASK 0x1FFF
#घोषणा QLOGIC_IB_I_OFFSET_SHIFT 0

/* K_PktFlags bits */
#घोषणा QLOGIC_IB_KPF_INTR 0x1
#घोषणा QLOGIC_IB_KPF_SUBCTXT_MASK 0x3
#घोषणा QLOGIC_IB_KPF_SUBCTXT_SHIFT 1

#घोषणा QLOGIC_IB_MAX_SUBCTXT   4

/* SendPIO per-buffer control */
#घोषणा QLOGIC_IB_SP_TEST    0x40
#घोषणा QLOGIC_IB_SP_TESTEBP 0x20
#घोषणा QLOGIC_IB_SP_TRIGGER_SHIFT  15

/* SendPIOAvail bits */
#घोषणा QLOGIC_IB_SENDPIOAVAIL_BUSY_SHIFT 1
#घोषणा QLOGIC_IB_SENDPIOAVAIL_CHECK_SHIFT 0

/* qlogic_ib header क्रमmat */
काष्ठा qib_header अणु
	/*
	 * Version - 4 bits, Context - 4 bits, TID - 10 bits and Offset -
	 * 14 bits beक्रमe ECO change ~28 Dec 03.  After that, Vers 4,
	 * Context 4, TID 11, offset 13.
	 */
	__le32 ver_ctxt_tid_offset;
	__le16 chksum;
	__le16 pkt_flags;
पूर्ण;

/*
 * qlogic_ib user message header क्रमmat.
 * This काष्ठाure contains the first 4 fields common to all protocols
 * that employ qlogic_ib.
 */
काष्ठा qib_message_header अणु
	__be16 lrh[4];
	__be32 bth[3];
	/* fields below this poपूर्णांक are in host byte order */
	काष्ठा qib_header iph;
	/* fields below are simplअगरied, but should match PSM */
	/* some are accessed by driver when packet spliting is needed */
	__u8 sub_opcode;
	__u8 flags;
	__u16 commidx;
	__u32 ack_seq_num;
	__u8 flowid;
	__u8 hdr_dlen;
	__u16 mqhdr;
	__u32 uwords[4];
पूर्ण;

/* sequence number bits क्रम message */
जोड़ qib_seqnum अणु
	काष्ठा अणु
		__u32 seq:11;
		__u32 gen:8;
		__u32 flow:5;
	पूर्ण;
	काष्ठा अणु
		__u32 pkt:16;
		__u32 msg:8;
	पूर्ण;
	__u32 val;
पूर्ण;

/* qib receiving-dma tid-session-member */
काष्ठा qib_tid_session_member अणु
	__u16 tid;
	__u16 offset;
	__u16 length;
पूर्ण;

/* IB - LRH header स्थिरs */
#घोषणा QIB_LRH_GRH 0x0003      /* 1. word of IB LRH - next header: GRH */
#घोषणा QIB_LRH_BTH 0x0002      /* 1. word of IB LRH - next header: BTH */

/* misc. */
#घोषणा SIZE_OF_CRC 1

#घोषणा QIB_DEFAULT_P_KEY 0xFFFF
#घोषणा QIB_PSN_MASK 0xFFFFFF
#घोषणा QIB_EAGER_TID_ID QLOGIC_IB_I_TID_MASK
#घोषणा QIB_MULTICAST_QPN 0xFFFFFF

/* Receive Header Queue: receive type (from qlogic_ib) */
#घोषणा RCVHQ_RCV_TYPE_EXPECTED  0
#घोषणा RCVHQ_RCV_TYPE_EAGER     1
#घोषणा RCVHQ_RCV_TYPE_NON_KD    2
#घोषणा RCVHQ_RCV_TYPE_ERROR     3

#घोषणा QIB_HEADER_QUEUE_WORDS 9

/* functions क्रम extracting fields from rcvhdrq entries क्रम the driver.
 */
अटल अंतरभूत __u32 qib_hdrget_err_flags(स्थिर __le32 *rbuf)
अणु
	वापस __le32_to_cpu(rbuf[1]) & QLOGIC_IB_RHF_H_ERR_MASK;
पूर्ण

अटल अंतरभूत __u32 qib_hdrget_rcv_type(स्थिर __le32 *rbuf)
अणु
	वापस (__le32_to_cpu(rbuf[0]) >> QLOGIC_IB_RHF_RCVTYPE_SHIFT) &
		QLOGIC_IB_RHF_RCVTYPE_MASK;
पूर्ण

अटल अंतरभूत __u32 qib_hdrget_length_in_bytes(स्थिर __le32 *rbuf)
अणु
	वापस ((__le32_to_cpu(rbuf[0]) >> QLOGIC_IB_RHF_LENGTH_SHIFT) &
		QLOGIC_IB_RHF_LENGTH_MASK) << 2;
पूर्ण

अटल अंतरभूत __u32 qib_hdrget_index(स्थिर __le32 *rbuf)
अणु
	वापस (__le32_to_cpu(rbuf[0]) >> QLOGIC_IB_RHF_EGRINDEX_SHIFT) &
		QLOGIC_IB_RHF_EGRINDEX_MASK;
पूर्ण

अटल अंतरभूत __u32 qib_hdrget_seq(स्थिर __le32 *rbuf)
अणु
	वापस (__le32_to_cpu(rbuf[1]) >> QLOGIC_IB_RHF_SEQ_SHIFT) &
		QLOGIC_IB_RHF_SEQ_MASK;
पूर्ण

अटल अंतरभूत __u32 qib_hdrget_offset(स्थिर __le32 *rbuf)
अणु
	वापस (__le32_to_cpu(rbuf[1]) >> QLOGIC_IB_RHF_HDRQ_OFFSET_SHIFT) &
		QLOGIC_IB_RHF_HDRQ_OFFSET_MASK;
पूर्ण

अटल अंतरभूत __u32 qib_hdrget_use_egr_buf(स्थिर __le32 *rbuf)
अणु
	वापस __le32_to_cpu(rbuf[0]) & QLOGIC_IB_RHF_L_USE_EGR;
पूर्ण
#पूर्ण_अगर                          /* _QIB_COMMON_H */
