<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (c) 2015 Mellanox Technologies. All rights reserved.
 */

#अगर_अघोषित _LINUX_NVME_RDMA_H
#घोषणा _LINUX_NVME_RDMA_H

क्रमागत nvme_rdma_cm_fmt अणु
	NVME_RDMA_CM_FMT_1_0 = 0x0,
पूर्ण;

क्रमागत nvme_rdma_cm_status अणु
	NVME_RDMA_CM_INVALID_LEN	= 0x01,
	NVME_RDMA_CM_INVALID_RECFMT	= 0x02,
	NVME_RDMA_CM_INVALID_QID	= 0x03,
	NVME_RDMA_CM_INVALID_HSQSIZE	= 0x04,
	NVME_RDMA_CM_INVALID_HRQSIZE	= 0x05,
	NVME_RDMA_CM_NO_RSC		= 0x06,
	NVME_RDMA_CM_INVALID_IRD	= 0x07,
	NVME_RDMA_CM_INVALID_ORD	= 0x08,
पूर्ण;

अटल अंतरभूत स्थिर अक्षर *nvme_rdma_cm_msg(क्रमागत nvme_rdma_cm_status status)
अणु
	चयन (status) अणु
	हाल NVME_RDMA_CM_INVALID_LEN:
		वापस "invalid length";
	हाल NVME_RDMA_CM_INVALID_RECFMT:
		वापस "invalid record format";
	हाल NVME_RDMA_CM_INVALID_QID:
		वापस "invalid queue ID";
	हाल NVME_RDMA_CM_INVALID_HSQSIZE:
		वापस "invalid host SQ size";
	हाल NVME_RDMA_CM_INVALID_HRQSIZE:
		वापस "invalid host RQ size";
	हाल NVME_RDMA_CM_NO_RSC:
		वापस "resource not found";
	हाल NVME_RDMA_CM_INVALID_IRD:
		वापस "invalid IRD";
	हाल NVME_RDMA_CM_INVALID_ORD:
		वापस "Invalid ORD";
	शेष:
		वापस "unrecognized reason";
	पूर्ण
पूर्ण

/**
 * काष्ठा nvme_rdma_cm_req - rdma connect request
 *
 * @recfmt:        क्रमmat of the RDMA Private Data
 * @qid:           queue Identअगरier क्रम the Admin or I/O Queue
 * @hrqsize:       host receive queue size to be created
 * @hsqsize:       host send queue size to be created
 */
काष्ठा nvme_rdma_cm_req अणु
	__le16		recfmt;
	__le16		qid;
	__le16		hrqsize;
	__le16		hsqsize;
	u8		rsvd[24];
पूर्ण;

/**
 * काष्ठा nvme_rdma_cm_rep - rdma connect reply
 *
 * @recfmt:        क्रमmat of the RDMA Private Data
 * @crqsize:       controller receive queue size
 */
काष्ठा nvme_rdma_cm_rep अणु
	__le16		recfmt;
	__le16		crqsize;
	u8		rsvd[28];
पूर्ण;

/**
 * काष्ठा nvme_rdma_cm_rej - rdma connect reject
 *
 * @recfmt:        क्रमmat of the RDMA Private Data
 * @sts:           error status क्रम the associated connect request
 */
काष्ठा nvme_rdma_cm_rej अणु
	__le16		recfmt;
	__le16		sts;
पूर्ण;

#पूर्ण_अगर /* _LINUX_NVME_RDMA_H */
