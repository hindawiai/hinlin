<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *  BSG helper library
 *
 *  Copyright (C) 2008   James Smart, Emulex Corporation
 *  Copyright (C) 2011   Red Hat, Inc.  All rights reserved.
 *  Copyright (C) 2011   Mike Christie
 */
#अगर_अघोषित _BLK_BSG_
#घोषणा _BLK_BSG_

#समावेश <linux/blkdev.h>
#समावेश <scsi/scsi_request.h>

काष्ठा request;
काष्ठा device;
काष्ठा scatterlist;
काष्ठा request_queue;

प्रकार पूर्णांक (bsg_job_fn) (काष्ठा bsg_job *);
प्रकार क्रमागत blk_eh_समयr_वापस (bsg_समयout_fn)(काष्ठा request *);

काष्ठा bsg_buffer अणु
	अचिन्हित पूर्णांक payload_len;
	पूर्णांक sg_cnt;
	काष्ठा scatterlist *sg_list;
पूर्ण;

काष्ठा bsg_job अणु
	काष्ठा device *dev;

	काष्ठा kref kref;

	अचिन्हित पूर्णांक समयout;

	/* Transport/driver specअगरic request/reply काष्ठाs */
	व्योम *request;
	व्योम *reply;

	अचिन्हित पूर्णांक request_len;
	अचिन्हित पूर्णांक reply_len;
	/*
	 * On entry : reply_len indicates the buffer size allocated क्रम
	 * the reply.
	 *
	 * Upon completion : the message handler must set reply_len
	 *  to indicates the size of the reply to be वापसed to the
	 *  caller.
	 */

	/* DMA payloads क्रम the request/response */
	काष्ठा bsg_buffer request_payload;
	काष्ठा bsg_buffer reply_payload;

	पूर्णांक result;
	अचिन्हित पूर्णांक reply_payload_rcv_len;

	/* BIDI support */
	काष्ठा request *bidi_rq;
	काष्ठा bio *bidi_bio;

	व्योम *dd_data;		/* Used क्रम driver-specअगरic storage */
पूर्ण;

व्योम bsg_job_करोne(काष्ठा bsg_job *job, पूर्णांक result,
		  अचिन्हित पूर्णांक reply_payload_rcv_len);
काष्ठा request_queue *bsg_setup_queue(काष्ठा device *dev, स्थिर अक्षर *name,
		bsg_job_fn *job_fn, bsg_समयout_fn *समयout, पूर्णांक dd_job_size);
व्योम bsg_हटाओ_queue(काष्ठा request_queue *q);
व्योम bsg_job_put(काष्ठा bsg_job *job);
पूर्णांक __must_check bsg_job_get(काष्ठा bsg_job *job);

#पूर्ण_अगर
