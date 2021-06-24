<शैली गुरु>
/**********************************************************************
 * Author: Cavium, Inc.
 *
 * Contact: support@cavium.com
 *          Please include "LiquidIO" in the subject.
 *
 * Copyright (c) 2003-2016 Cavium, Inc.
 *
 * This file is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License, Version 2, as
 * published by the Free Software Foundation.
 *
 * This file is distributed in the hope that it will be useful, but
 * AS-IS and WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE, TITLE, or
 * NONINFRINGEMENT.  See the GNU General Public License क्रम more details.
 ***********************************************************************/
#अगर_अघोषित _LIQUIDIO_IMAGE_H_
#घोषणा _LIQUIDIO_IMAGE_H_

#घोषणा LIO_MAX_FW_TYPE_LEN     (8)
#घोषणा LIO_MAX_FW_खाताNAME_LEN (256)
#घोषणा LIO_FW_सूची              "liquidio/"
#घोषणा LIO_FW_BASE_NAME        "lio_"
#घोषणा LIO_FW_NAME_SUFFIX      ".bin"
#घोषणा LIO_FW_NAME_TYPE_NIC    "nic"
#घोषणा LIO_FW_NAME_TYPE_AUTO   "auto"
#घोषणा LIO_FW_NAME_TYPE_NONE   "none"
#घोषणा LIO_MAX_FIRMWARE_VERSION_LEN 16

#घोषणा LIO_MAX_BOOTCMD_LEN 1024
#घोषणा LIO_MAX_IMAGES 16
#घोषणा LIO_NIC_MAGIC 0x434E4943     /* "CNIC" */
काष्ठा octeon_firmware_desc अणु
	__be64 addr;
	__be32 len;
	__be32 crc32;         /* crc32 of image */
पूर्ण;

/* Following the header is a list of 64-bit aligned binary images,
 * as described by the desc field.
 * Numeric fields are in network byte order.
 */
काष्ठा octeon_firmware_file_header अणु
	__be32 magic;
	अक्षर version[LIO_MAX_FIRMWARE_VERSION_LEN];
	अक्षर bootcmd[LIO_MAX_BOOTCMD_LEN];
	__be32 num_images;
	काष्ठा octeon_firmware_desc desc[LIO_MAX_IMAGES];
	__be32 pad;
	__be32 crc32;         /* header checksum */
पूर्ण;

#पूर्ण_अगर /* _LIQUIDIO_IMAGE_H_ */
