<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * RDMA Network Block Driver
 *
 * Copyright (c) 2014 - 2018 ProfitBricks GmbH. All rights reserved.
 * Copyright (c) 2018 - 2019 1&1 IONOS Cloud GmbH. All rights reserved.
 * Copyright (c) 2019 - 2020 1&1 IONOS SE. All rights reserved.
 */
#अगर_अघोषित RNBD_PROTO_H
#घोषणा RNBD_PROTO_H

#समावेश <linux/types.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/सीमा.स>
#समावेश <linux/inet.h>
#समावेश <linux/in.h>
#समावेश <linux/in6.h>
#समावेश <rdma/ib.h>

#घोषणा RNBD_PROTO_VER_MAJOR 2
#घोषणा RNBD_PROTO_VER_MINOR 0

/* The शेष port number the RTRS server is listening on. */
#घोषणा RTRS_PORT 1234

/**
 * क्रमागत rnbd_msg_types - RNBD message types
 * @RNBD_MSG_SESS_INFO:	initial session info from client to server
 * @RNBD_MSG_SESS_INFO_RSP:	initial session info from server to client
 * @RNBD_MSG_OPEN:		खोलो (map) device request
 * @RNBD_MSG_OPEN_RSP:		response to an @RNBD_MSG_OPEN
 * @RNBD_MSG_IO:		block IO request operation
 * @RNBD_MSG_CLOSE:		बंद (unmap) device request
 */
क्रमागत rnbd_msg_type अणु
	RNBD_MSG_SESS_INFO,
	RNBD_MSG_SESS_INFO_RSP,
	RNBD_MSG_OPEN,
	RNBD_MSG_OPEN_RSP,
	RNBD_MSG_IO,
	RNBD_MSG_CLOSE,
पूर्ण;

/**
 * काष्ठा rnbd_msg_hdr - header of RNBD messages
 * @type:	Message type, valid values see: क्रमागत rnbd_msg_types
 */
काष्ठा rnbd_msg_hdr अणु
	__le16		type;
	__le16		__padding;
पूर्ण;

/**
 * We allow to map RO many बार and RW only once. We allow to map yet another
 * समय RW, अगर MIGRATION is provided (second RW export can be required क्रम
 * example क्रम VM migration)
 */
क्रमागत rnbd_access_mode अणु
	RNBD_ACCESS_RO,
	RNBD_ACCESS_RW,
	RNBD_ACCESS_MIGRATION,
पूर्ण;

/**
 * काष्ठा rnbd_msg_sess_info - initial session info from client to server
 * @hdr:		message header
 * @ver:		RNBD protocol version
 */
काष्ठा rnbd_msg_sess_info अणु
	काष्ठा rnbd_msg_hdr hdr;
	u8		ver;
	u8		reserved[31];
पूर्ण;

/**
 * काष्ठा rnbd_msg_sess_info_rsp - initial session info from server to client
 * @hdr:		message header
 * @ver:		RNBD protocol version
 */
काष्ठा rnbd_msg_sess_info_rsp अणु
	काष्ठा rnbd_msg_hdr hdr;
	u8		ver;
	u8		reserved[31];
पूर्ण;

/**
 * काष्ठा rnbd_msg_खोलो - request to खोलो a remote device.
 * @hdr:		message header
 * @access_mode:	the mode to खोलो remote device, valid values see:
 *			क्रमागत rnbd_access_mode
 * @device_name:	device path on remote side
 */
काष्ठा rnbd_msg_खोलो अणु
	काष्ठा rnbd_msg_hdr hdr;
	u8		access_mode;
	u8		resv1;
	s8		dev_name[NAME_MAX];
	u8		reserved[3];
पूर्ण;

/**
 * काष्ठा rnbd_msg_बंद - request to बंद a remote device.
 * @hdr:	message header
 * @device_id:	device_id on server side to identअगरy the device
 */
काष्ठा rnbd_msg_बंद अणु
	काष्ठा rnbd_msg_hdr hdr;
	__le32		device_id;
पूर्ण;

क्रमागत rnbd_cache_policy अणु
	RNBD_FUA = 1 << 0,
	RNBD_WRITEBACK = 1 << 1,
पूर्ण;

/**
 * काष्ठा rnbd_msg_खोलो_rsp - response message to RNBD_MSG_OPEN
 * @hdr:		message header
 * @device_id:		device_id on server side to identअगरy the device
 * @nsectors:		number of sectors in the usual 512b unit
 * @max_hw_sectors:	max hardware sectors in the usual 512b unit
 * @max_ग_लिखो_same_sectors: max sectors क्रम WRITE SAME in the 512b unit
 * @max_discard_sectors: max. sectors that can be discarded at once in 512b
 * unit.
 * @discard_granularity: size of the पूर्णांकernal discard allocation unit in bytes
 * @discard_alignment: offset from पूर्णांकernal allocation assignment in bytes
 * @physical_block_size: physical block size device supports in bytes
 * @logical_block_size: logical block size device supports in bytes
 * @max_segments:	max segments hardware support in one transfer
 * @secure_discard:	supports secure discard
 * @rotation:		is a rotational disc?
 * @cache_policy: 	support ग_लिखो-back caching or FUA?
 */
काष्ठा rnbd_msg_खोलो_rsp अणु
	काष्ठा rnbd_msg_hdr	hdr;
	__le32			device_id;
	__le64			nsectors;
	__le32			max_hw_sectors;
	__le32			max_ग_लिखो_same_sectors;
	__le32			max_discard_sectors;
	__le32			discard_granularity;
	__le32			discard_alignment;
	__le16			physical_block_size;
	__le16			logical_block_size;
	__le16			max_segments;
	__le16			secure_discard;
	u8			rotational;
	u8			cache_policy;
	u8			reserved[10];
पूर्ण;

/**
 * काष्ठा rnbd_msg_io - message क्रम I/O पढ़ो/ग_लिखो
 * @hdr:	message header
 * @device_id:	device_id on server side to find the right device
 * @sector:	bi_sector attribute from काष्ठा bio
 * @rw:		valid values are defined in क्रमागत rnbd_io_flags
 * @bi_size:    number of bytes क्रम I/O पढ़ो/ग_लिखो
 * @prio:       priority
 */
काष्ठा rnbd_msg_io अणु
	काष्ठा rnbd_msg_hdr hdr;
	__le32		device_id;
	__le64		sector;
	__le32		rw;
	__le32		bi_size;
	__le16		prio;
पूर्ण;

#घोषणा RNBD_OP_BITS  8
#घोषणा RNBD_OP_MASK  ((1 << RNBD_OP_BITS) - 1)

/**
 * क्रमागत rnbd_io_flags - RNBD request types from rq_flag_bits
 * @RNBD_OP_READ:	     पढ़ो sectors from the device
 * @RNBD_OP_WRITE:	     ग_लिखो sectors to the device
 * @RNBD_OP_FLUSH:	     flush the अस्थिर ग_लिखो cache
 * @RNBD_OP_DISCARD:        discard sectors
 * @RNBD_OP_SECURE_ERASE:   securely erase sectors
 * @RNBD_OP_WRITE_SAME:     ग_लिखो the same sectors many बार

 * @RNBD_F_SYNC:	     request is sync (sync ग_लिखो or पढ़ो)
 * @RNBD_F_FUA:             क्रमced unit access
 */
क्रमागत rnbd_io_flags अणु

	/* Operations */

	RNBD_OP_READ		= 0,
	RNBD_OP_WRITE		= 1,
	RNBD_OP_FLUSH		= 2,
	RNBD_OP_DISCARD	= 3,
	RNBD_OP_SECURE_ERASE	= 4,
	RNBD_OP_WRITE_SAME	= 5,

	RNBD_OP_LAST,

	/* Flags */

	RNBD_F_SYNC  = 1<<(RNBD_OP_BITS + 0),
	RNBD_F_FUA   = 1<<(RNBD_OP_BITS + 1),

	RNBD_F_ALL   = (RNBD_F_SYNC | RNBD_F_FUA)

पूर्ण;

अटल अंतरभूत u32 rnbd_op(u32 flags)
अणु
	वापस flags & RNBD_OP_MASK;
पूर्ण

अटल अंतरभूत u32 rnbd_flags(u32 flags)
अणु
	वापस flags & ~RNBD_OP_MASK;
पूर्ण

अटल अंतरभूत bool rnbd_flags_supported(u32 flags)
अणु
	u32 op;

	op = rnbd_op(flags);
	flags = rnbd_flags(flags);

	अगर (op >= RNBD_OP_LAST)
		वापस false;
	अगर (flags & ~RNBD_F_ALL)
		वापस false;

	वापस true;
पूर्ण

अटल अंतरभूत u32 rnbd_to_bio_flags(u32 rnbd_opf)
अणु
	u32 bio_opf;

	चयन (rnbd_op(rnbd_opf)) अणु
	हाल RNBD_OP_READ:
		bio_opf = REQ_OP_READ;
		अवरोध;
	हाल RNBD_OP_WRITE:
		bio_opf = REQ_OP_WRITE;
		अवरोध;
	हाल RNBD_OP_FLUSH:
		bio_opf = REQ_OP_FLUSH | REQ_PREFLUSH;
		अवरोध;
	हाल RNBD_OP_DISCARD:
		bio_opf = REQ_OP_DISCARD;
		अवरोध;
	हाल RNBD_OP_SECURE_ERASE:
		bio_opf = REQ_OP_SECURE_ERASE;
		अवरोध;
	हाल RNBD_OP_WRITE_SAME:
		bio_opf = REQ_OP_WRITE_SAME;
		अवरोध;
	शेष:
		WARN(1, "Unknown RNBD type: %d (flags %d)\n",
		     rnbd_op(rnbd_opf), rnbd_opf);
		bio_opf = 0;
	पूर्ण

	अगर (rnbd_opf & RNBD_F_SYNC)
		bio_opf |= REQ_SYNC;

	अगर (rnbd_opf & RNBD_F_FUA)
		bio_opf |= REQ_FUA;

	वापस bio_opf;
पूर्ण

अटल अंतरभूत u32 rq_to_rnbd_flags(काष्ठा request *rq)
अणु
	u32 rnbd_opf;

	चयन (req_op(rq)) अणु
	हाल REQ_OP_READ:
		rnbd_opf = RNBD_OP_READ;
		अवरोध;
	हाल REQ_OP_WRITE:
		rnbd_opf = RNBD_OP_WRITE;
		अवरोध;
	हाल REQ_OP_DISCARD:
		rnbd_opf = RNBD_OP_DISCARD;
		अवरोध;
	हाल REQ_OP_SECURE_ERASE:
		rnbd_opf = RNBD_OP_SECURE_ERASE;
		अवरोध;
	हाल REQ_OP_WRITE_SAME:
		rnbd_opf = RNBD_OP_WRITE_SAME;
		अवरोध;
	हाल REQ_OP_FLUSH:
		rnbd_opf = RNBD_OP_FLUSH;
		अवरोध;
	शेष:
		WARN(1, "Unknown request type %d (flags %llu)\n",
		     req_op(rq), (अचिन्हित दीर्घ दीर्घ)rq->cmd_flags);
		rnbd_opf = 0;
	पूर्ण

	अगर (op_is_sync(rq->cmd_flags))
		rnbd_opf |= RNBD_F_SYNC;

	अगर (op_is_flush(rq->cmd_flags))
		rnbd_opf |= RNBD_F_FUA;

	वापस rnbd_opf;
पूर्ण

स्थिर अक्षर *rnbd_access_mode_str(क्रमागत rnbd_access_mode mode);

#पूर्ण_अगर /* RNBD_PROTO_H */
