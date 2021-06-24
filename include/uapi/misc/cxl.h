<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ WITH Linux-syscall-note */
/*
 * Copyright 2014 IBM Corp.
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version
 * 2 of the License, or (at your option) any later version.
 */

#अगर_अघोषित _UAPI_MISC_CXL_H
#घोषणा _UAPI_MISC_CXL_H

#समावेश <linux/types.h>
#समावेश <linux/ioctl.h>


काष्ठा cxl_ioctl_start_work अणु
	__u64 flags;
	__u64 work_element_descriptor;
	__u64 amr;
	__s16 num_पूर्णांकerrupts;
	__u16 tid;
	__s32 reserved1;
	__u64 reserved2;
	__u64 reserved3;
	__u64 reserved4;
	__u64 reserved5;
पूर्ण;

#घोषणा CXL_START_WORK_AMR		0x0000000000000001ULL
#घोषणा CXL_START_WORK_NUM_IRQS		0x0000000000000002ULL
#घोषणा CXL_START_WORK_ERR_FF		0x0000000000000004ULL
#घोषणा CXL_START_WORK_TID		0x0000000000000008ULL
#घोषणा CXL_START_WORK_ALL		(CXL_START_WORK_AMR |\
					 CXL_START_WORK_NUM_IRQS |\
					 CXL_START_WORK_ERR_FF |\
					 CXL_START_WORK_TID)


/* Possible modes that an afu can be in */
#घोषणा CXL_MODE_DEDICATED   0x1
#घोषणा CXL_MODE_सूचीECTED    0x2

/* possible flags क्रम the cxl_afu_id flags field */
#घोषणा CXL_AFUID_FLAG_SLAVE    0x1  /* In directed-mode afu is in slave mode */

काष्ठा cxl_afu_id अणु
	__u64 flags;     /* One of CXL_AFUID_FLAG_X */
	__u32 card_id;
	__u32 afu_offset;
	__u32 afu_mode;  /* one of the CXL_MODE_X */
	__u32 reserved1;
	__u64 reserved2;
	__u64 reserved3;
	__u64 reserved4;
	__u64 reserved5;
	__u64 reserved6;
पूर्ण;

/* base adapter image header is included in the image */
#घोषणा CXL_AI_NEED_HEADER	0x0000000000000001ULL
#घोषणा CXL_AI_ALL		CXL_AI_NEED_HEADER

#घोषणा CXL_AI_HEADER_SIZE 128
#घोषणा CXL_AI_BUFFER_SIZE 4096
#घोषणा CXL_AI_MAX_ENTRIES 256
#घोषणा CXL_AI_MAX_CHUNK_SIZE (CXL_AI_BUFFER_SIZE * CXL_AI_MAX_ENTRIES)

काष्ठा cxl_adapter_image अणु
	__u64 flags;
	__u64 data;
	__u64 len_data;
	__u64 len_image;
	__u64 reserved1;
	__u64 reserved2;
	__u64 reserved3;
	__u64 reserved4;
पूर्ण;

/* ioctl numbers */
#घोषणा CXL_MAGIC 0xCA
/* AFU devices */
#घोषणा CXL_IOCTL_START_WORK		_IOW(CXL_MAGIC, 0x00, काष्ठा cxl_ioctl_start_work)
#घोषणा CXL_IOCTL_GET_PROCESS_ELEMENT	_IOR(CXL_MAGIC, 0x01, __u32)
#घोषणा CXL_IOCTL_GET_AFU_ID            _IOR(CXL_MAGIC, 0x02, काष्ठा cxl_afu_id)
/* adapter devices */
#घोषणा CXL_IOCTL_DOWNLOAD_IMAGE        _IOW(CXL_MAGIC, 0x0A, काष्ठा cxl_adapter_image)
#घोषणा CXL_IOCTL_VALIDATE_IMAGE        _IOW(CXL_MAGIC, 0x0B, काष्ठा cxl_adapter_image)

#घोषणा CXL_READ_MIN_SIZE 0x1000 /* 4K */

/* Events from पढ़ो() */
क्रमागत cxl_event_type अणु
	CXL_EVENT_RESERVED      = 0,
	CXL_EVENT_AFU_INTERRUPT = 1,
	CXL_EVENT_DATA_STORAGE  = 2,
	CXL_EVENT_AFU_ERROR     = 3,
	CXL_EVENT_AFU_DRIVER    = 4,
पूर्ण;

काष्ठा cxl_event_header अणु
	__u16 type;
	__u16 size;
	__u16 process_element;
	__u16 reserved1;
पूर्ण;

काष्ठा cxl_event_afu_पूर्णांकerrupt अणु
	__u16 flags;
	__u16 irq; /* Raised AFU पूर्णांकerrupt number */
	__u32 reserved1;
पूर्ण;

काष्ठा cxl_event_data_storage अणु
	__u16 flags;
	__u16 reserved1;
	__u32 reserved2;
	__u64 addr;
	__u64 dsisr;
	__u64 reserved3;
पूर्ण;

काष्ठा cxl_event_afu_error अणु
	__u16 flags;
	__u16 reserved1;
	__u32 reserved2;
	__u64 error;
पूर्ण;

काष्ठा cxl_event_afu_driver_reserved अणु
	/*
	 * Defines the buffer passed to the cxl driver by the AFU driver.
	 *
	 * This is not ABI since the event header.size passed to the user क्रम
	 * existing events is set in the पढ़ो call to माप(cxl_event_header)
	 * + माप(whatever event is being dispatched) and the user is alपढ़ोy
	 * required to use a 4K buffer on the पढ़ो call.
	 *
	 * Of course the contents will be ABI, but that's up the AFU driver.
	 */
	__u32 data_size;
	__u8 data[];
पूर्ण;

काष्ठा cxl_event अणु
	काष्ठा cxl_event_header header;
	जोड़ अणु
		काष्ठा cxl_event_afu_पूर्णांकerrupt irq;
		काष्ठा cxl_event_data_storage fault;
		काष्ठा cxl_event_afu_error afu_error;
		काष्ठा cxl_event_afu_driver_reserved afu_driver_event;
	पूर्ण;
पूर्ण;

#पूर्ण_अगर /* _UAPI_MISC_CXL_H */
