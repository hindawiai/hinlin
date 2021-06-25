<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/******************************************************************************
 * blkअगर.h
 *
 * Unअगरied block-device I/O पूर्णांकerface क्रम Xen guest OSes.
 *
 * Copyright (c) 2003-2004, Keir Fraser
 */

#अगर_अघोषित __XEN_PUBLIC_IO_BLKIF_H__
#घोषणा __XEN_PUBLIC_IO_BLKIF_H__

#समावेश <xen/पूर्णांकerface/io/ring.h>
#समावेश <xen/पूर्णांकerface/grant_table.h>

/*
 * Front->back notअगरications: When enqueuing a new request, sending a
 * notअगरication can be made conditional on req_event (i.e., the generic
 * hold-off mechanism provided by the ring macros). Backends must set
 * req_event appropriately (e.g., using RING_FINAL_CHECK_FOR_REQUESTS()).
 *
 * Back->front notअगरications: When enqueuing a new response, sending a
 * notअगरication can be made conditional on rsp_event (i.e., the generic
 * hold-off mechanism provided by the ring macros). Frontends must set
 * rsp_event appropriately (e.g., using RING_FINAL_CHECK_FOR_RESPONSES()).
 */

प्रकार uपूर्णांक16_t blkअगर_vdev_t;
प्रकार uपूर्णांक64_t blkअगर_sector_t;

/*
 * Multiple hardware queues/rings:
 * If supported, the backend will ग_लिखो the key "multi-queue-max-queues" to
 * the directory क्रम that vbd, and set its value to the maximum supported
 * number of queues.
 * Frontends that are aware of this feature and wish to use it can ग_लिखो the
 * key "multi-queue-num-queues" with the number they wish to use, which must be
 * greater than zero, and no more than the value reported by the backend in
 * "multi-queue-max-queues".
 *
 * For frontends requesting just one queue, the usual event-channel and
 * ring-ref keys are written as beक्रमe, simplअगरying the backend processing
 * to aव्योम distinguishing between a frontend that करोesn't understand the
 * multi-queue feature, and one that करोes, but requested only one queue.
 *
 * Frontends requesting two or more queues must not ग_लिखो the toplevel
 * event-channel and ring-ref keys, instead writing those keys under sub-keys
 * having the name "queue-N" where N is the पूर्णांकeger ID of the queue/ring क्रम
 * which those keys beदीर्घ. Queues are indexed from zero.
 * For example, a frontend with two queues must ग_लिखो the following set of
 * queue-related keys:
 *
 * /local/करोमुख्य/1/device/vbd/0/multi-queue-num-queues = "2"
 * /local/करोमुख्य/1/device/vbd/0/queue-0 = ""
 * /local/करोमुख्य/1/device/vbd/0/queue-0/ring-ref = "<ring-ref#0>"
 * /local/करोमुख्य/1/device/vbd/0/queue-0/event-channel = "<evtchn#0>"
 * /local/करोमुख्य/1/device/vbd/0/queue-1 = ""
 * /local/करोमुख्य/1/device/vbd/0/queue-1/ring-ref = "<ring-ref#1>"
 * /local/करोमुख्य/1/device/vbd/0/queue-1/event-channel = "<evtchn#1>"
 *
 * It is also possible to use multiple queues/rings together with
 * feature multi-page ring buffer.
 * For example, a frontend requests two queues/rings and the size of each ring
 * buffer is two pages must ग_लिखो the following set of related keys:
 *
 * /local/करोमुख्य/1/device/vbd/0/multi-queue-num-queues = "2"
 * /local/करोमुख्य/1/device/vbd/0/ring-page-order = "1"
 * /local/करोमुख्य/1/device/vbd/0/queue-0 = ""
 * /local/करोमुख्य/1/device/vbd/0/queue-0/ring-ref0 = "<ring-ref#0>"
 * /local/करोमुख्य/1/device/vbd/0/queue-0/ring-ref1 = "<ring-ref#1>"
 * /local/करोमुख्य/1/device/vbd/0/queue-0/event-channel = "<evtchn#0>"
 * /local/करोमुख्य/1/device/vbd/0/queue-1 = ""
 * /local/करोमुख्य/1/device/vbd/0/queue-1/ring-ref0 = "<ring-ref#2>"
 * /local/करोमुख्य/1/device/vbd/0/queue-1/ring-ref1 = "<ring-ref#3>"
 * /local/करोमुख्य/1/device/vbd/0/queue-1/event-channel = "<evtchn#1>"
 *
 */

/*
 * REQUEST CODES.
 */
#घोषणा BLKIF_OP_READ              0
#घोषणा BLKIF_OP_WRITE             1
/*
 * Recognised only अगर "feature-barrier" is present in backend xenbus info.
 * The "feature_barrier" node contains a boolean indicating whether barrier
 * requests are likely to succeed or fail. Either way, a barrier request
 * may fail at any समय with BLKIF_RSP_EOPNOTSUPP अगर it is unsupported by
 * the underlying block-device hardware. The boolean simply indicates whether
 * or not it is worthजबतक क्रम the frontend to attempt barrier requests.
 * If a backend करोes not recognise BLKIF_OP_WRITE_BARRIER, it should *not*
 * create the "feature-barrier" node!
 */
#घोषणा BLKIF_OP_WRITE_BARRIER     2

/*
 * Recognised अगर "feature-flush-cache" is present in backend xenbus
 * info.  A flush will ask the underlying storage hardware to flush its
 * non-अस्थिर caches as appropriate.  The "feature-flush-cache" node
 * contains a boolean indicating whether flush requests are likely to
 * succeed or fail. Either way, a flush request may fail at any समय
 * with BLKIF_RSP_EOPNOTSUPP अगर it is unsupported by the underlying
 * block-device hardware. The boolean simply indicates whether or not it
 * is worthजबतक क्रम the frontend to attempt flushes.  If a backend करोes
 * not recognise BLKIF_OP_WRITE_FLUSH_CACHE, it should *not* create the
 * "feature-flush-cache" node!
 */
#घोषणा BLKIF_OP_FLUSH_DISKCACHE   3

/*
 * Recognised only अगर "feature-discard" is present in backend xenbus info.
 * The "feature-discard" node contains a boolean indicating whether trim
 * (ATA) or unmap (SCSI) - conviently called discard requests are likely
 * to succeed or fail. Either way, a discard request
 * may fail at any समय with BLKIF_RSP_EOPNOTSUPP अगर it is unsupported by
 * the underlying block-device hardware. The boolean simply indicates whether
 * or not it is worthजबतक क्रम the frontend to attempt discard requests.
 * If a backend करोes not recognise BLKIF_OP_DISCARD, it should *not*
 * create the "feature-discard" node!
 *
 * Discard operation is a request क्रम the underlying block device to mark
 * extents to be erased. However, discard करोes not guarantee that the blocks
 * will be erased from the device - it is just a hपूर्णांक to the device
 * controller that these blocks are no दीर्घer in use. What the device
 * controller करोes with that inक्रमmation is left to the controller.
 * Discard operations are passed with sector_number as the
 * sector index to begin discard operations at and nr_sectors as the number of
 * sectors to be discarded. The specअगरied sectors should be discarded अगर the
 * underlying block device supports trim (ATA) or unmap (SCSI) operations,
 * or a BLKIF_RSP_EOPNOTSUPP  should be वापसed.
 * More inक्रमmation about trim/unmap operations at:
 * http://t13.org/Documents/UploadedDocuments/करोcs2008/
 *     e07154r6-Data_Set_Management_Proposal_क्रम_ATA-ACS2.करोc
 * http://www.seagate.com/अटलfiles/support/disc/manuals/
 *     Interface%20manuals/100293068c.pdf
 * The backend can optionally provide three extra XenBus attributes to
 * further optimize the discard functionality:
 * 'discard-alignment' - Devices that support discard functionality may
 * पूर्णांकernally allocate space in units that are bigger than the exported
 * logical block size. The discard-alignment parameter indicates how many bytes
 * the beginning of the partition is offset from the पूर्णांकernal allocation unit's
 * natural alignment.
 * 'discard-granularity'  - Devices that support discard functionality may
 * पूर्णांकernally allocate space using units that are bigger than the logical block
 * size. The discard-granularity parameter indicates the size of the पूर्णांकernal
 * allocation unit in bytes अगर reported by the device. Otherwise the
 * discard-granularity will be set to match the device's physical block size.
 * 'discard-secure' - All copies of the discarded sectors (potentially created
 * by garbage collection) must also be erased.  To use this feature, the flag
 * BLKIF_DISCARD_SECURE must be set in the blkअगर_request_trim.
 */
#घोषणा BLKIF_OP_DISCARD           5

/*
 * Recognized अगर "feature-max-indirect-segments" in present in the backend
 * xenbus info. The "feature-max-indirect-segments" node contains the maximum
 * number of segments allowed by the backend per request. If the node is
 * present, the frontend might use blkअगर_request_indirect काष्ठाs in order to
 * issue requests with more than BLKIF_MAX_SEGMENTS_PER_REQUEST (11). The
 * maximum number of indirect segments is fixed by the backend, but the
 * frontend can issue requests with any number of indirect segments as दीर्घ as
 * it's less than the number provided by the backend. The indirect_grefs field
 * in blkअगर_request_indirect should be filled by the frontend with the
 * grant references of the pages that are holding the indirect segments.
 * These pages are filled with an array of blkअगर_request_segment that hold the
 * inक्रमmation about the segments. The number of indirect pages to use is
 * determined by the number of segments an indirect request contains. Every
 * indirect page can contain a maximum of
 * (PAGE_SIZE / माप(काष्ठा blkअगर_request_segment)) segments, so to
 * calculate the number of indirect pages to use we have to करो
 * उच्चमान(indirect_segments / (PAGE_SIZE / माप(काष्ठा blkअगर_request_segment))).
 *
 * If a backend करोes not recognize BLKIF_OP_INसूचीECT, it should *not*
 * create the "feature-max-indirect-segments" node!
 */
#घोषणा BLKIF_OP_INसूचीECT          6

/*
 * Maximum scatter/gather segments per request.
 * This is carefully chosen so that माप(काष्ठा blkअगर_ring) <= PAGE_SIZE.
 * NB. This could be 12 अगर the ring indexes weren't stored in the same page.
 */
#घोषणा BLKIF_MAX_SEGMENTS_PER_REQUEST 11

#घोषणा BLKIF_MAX_INसूचीECT_PAGES_PER_REQUEST 8

काष्ठा blkअगर_request_segment अणु
		grant_ref_t gref;        /* reference to I/O buffer frame        */
		/* @first_sect: first sector in frame to transfer (inclusive).   */
		/* @last_sect: last sector in frame to transfer (inclusive).     */
		uपूर्णांक8_t     first_sect, last_sect;
पूर्ण;

काष्ठा blkअगर_request_rw अणु
	uपूर्णांक8_t        nr_segments;  /* number of segments                   */
	blkअगर_vdev_t   handle;       /* only क्रम पढ़ो/ग_लिखो requests         */
#अगर_अघोषित CONFIG_X86_32
	uपूर्णांक32_t       _pad1;	     /* दुरत्व(blkअगर_request,u.rw.id) == 8 */
#पूर्ण_अगर
	uपूर्णांक64_t       id;           /* निजी guest value, echoed in resp  */
	blkअगर_sector_t sector_number;/* start sector idx on disk (r/w only)  */
	काष्ठा blkअगर_request_segment seg[BLKIF_MAX_SEGMENTS_PER_REQUEST];
पूर्ण __attribute__((__packed__));

काष्ठा blkअगर_request_discard अणु
	uपूर्णांक8_t        flag;         /* BLKIF_DISCARD_SECURE or zero.        */
#घोषणा BLKIF_DISCARD_SECURE (1<<0)  /* ignored अगर discard-secure=0          */
	blkअगर_vdev_t   _pad1;        /* only क्रम पढ़ो/ग_लिखो requests         */
#अगर_अघोषित CONFIG_X86_32
	uपूर्णांक32_t       _pad2;        /* दुरत्व(blkअगर_req..,u.discard.id)==8*/
#पूर्ण_अगर
	uपूर्णांक64_t       id;           /* निजी guest value, echoed in resp  */
	blkअगर_sector_t sector_number;
	uपूर्णांक64_t       nr_sectors;
	uपूर्णांक8_t        _pad3;
पूर्ण __attribute__((__packed__));

काष्ठा blkअगर_request_other अणु
	uपूर्णांक8_t      _pad1;
	blkअगर_vdev_t _pad2;        /* only क्रम पढ़ो/ग_लिखो requests         */
#अगर_अघोषित CONFIG_X86_32
	uपूर्णांक32_t     _pad3;        /* दुरत्व(blkअगर_req..,u.other.id)==8*/
#पूर्ण_अगर
	uपूर्णांक64_t     id;           /* निजी guest value, echoed in resp  */
पूर्ण __attribute__((__packed__));

काष्ठा blkअगर_request_indirect अणु
	uपूर्णांक8_t        indirect_op;
	uपूर्णांक16_t       nr_segments;
#अगर_अघोषित CONFIG_X86_32
	uपूर्णांक32_t       _pad1;        /* दुरत्व(blkअगर_...,u.indirect.id) == 8 */
#पूर्ण_अगर
	uपूर्णांक64_t       id;
	blkअगर_sector_t sector_number;
	blkअगर_vdev_t   handle;
	uपूर्णांक16_t       _pad2;
	grant_ref_t    indirect_grefs[BLKIF_MAX_INसूचीECT_PAGES_PER_REQUEST];
#अगर_अघोषित CONFIG_X86_32
	uपूर्णांक32_t      _pad3;         /* make it 64 byte aligned */
#अन्यथा
	uपूर्णांक64_t      _pad3;         /* make it 64 byte aligned */
#पूर्ण_अगर
पूर्ण __attribute__((__packed__));

काष्ठा blkअगर_request अणु
	uपूर्णांक8_t        operation;    /* BLKIF_OP_???                         */
	जोड़ अणु
		काष्ठा blkअगर_request_rw rw;
		काष्ठा blkअगर_request_discard discard;
		काष्ठा blkअगर_request_other other;
		काष्ठा blkअगर_request_indirect indirect;
	पूर्ण u;
पूर्ण __attribute__((__packed__));

काष्ठा blkअगर_response अणु
	uपूर्णांक64_t        id;              /* copied from request */
	uपूर्णांक8_t         operation;       /* copied from request */
	पूर्णांक16_t         status;          /* BLKIF_RSP_???       */
पूर्ण;

/*
 * STATUS RETURN CODES.
 */
 /* Operation not supported (only happens on barrier ग_लिखोs). */
#घोषणा BLKIF_RSP_EOPNOTSUPP  -2
 /* Operation failed क्रम some unspecअगरied reason (-EIO). */
#घोषणा BLKIF_RSP_ERROR       -1
 /* Operation completed successfully. */
#घोषणा BLKIF_RSP_OKAY         0

/*
 * Generate blkअगर ring काष्ठाures and types.
 */

DEFINE_RING_TYPES(blkअगर, काष्ठा blkअगर_request, काष्ठा blkअगर_response);

#घोषणा VDISK_CDROM        0x1
#घोषणा VDISK_REMOVABLE    0x2
#घोषणा VDISK_READONLY     0x4

/* Xen-defined major numbers क्रम भव disks, they look strangely
 * familiar */
#घोषणा XEN_IDE0_MAJOR	3
#घोषणा XEN_IDE1_MAJOR	22
#घोषणा XEN_SCSI_DISK0_MAJOR	8
#घोषणा XEN_SCSI_DISK1_MAJOR	65
#घोषणा XEN_SCSI_DISK2_MAJOR	66
#घोषणा XEN_SCSI_DISK3_MAJOR	67
#घोषणा XEN_SCSI_DISK4_MAJOR	68
#घोषणा XEN_SCSI_DISK5_MAJOR	69
#घोषणा XEN_SCSI_DISK6_MAJOR	70
#घोषणा XEN_SCSI_DISK7_MAJOR	71
#घोषणा XEN_SCSI_DISK8_MAJOR	128
#घोषणा XEN_SCSI_DISK9_MAJOR	129
#घोषणा XEN_SCSI_DISK10_MAJOR	130
#घोषणा XEN_SCSI_DISK11_MAJOR	131
#घोषणा XEN_SCSI_DISK12_MAJOR	132
#घोषणा XEN_SCSI_DISK13_MAJOR	133
#घोषणा XEN_SCSI_DISK14_MAJOR	134
#घोषणा XEN_SCSI_DISK15_MAJOR	135

#पूर्ण_अगर /* __XEN_PUBLIC_IO_BLKIF_H__ */
