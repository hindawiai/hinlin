<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * ChromeOS EC device पूर्णांकerface.
 *
 * Copyright (C) 2014 Google, Inc.
 */

#अगर_अघोषित _UAPI_LINUX_CROS_EC_DEV_H_
#घोषणा _UAPI_LINUX_CROS_EC_DEV_H_

#समावेश <linux/bits.h>
#समावेश <linux/ioctl.h>
#समावेश <linux/types.h>

#समावेश <linux/platक्रमm_data/cros_ec_commands.h>

#घोषणा CROS_EC_DEV_VERSION "1.0.0"

/**
 * काष्ठा cros_ec_पढ़ोmem - Struct used to पढ़ो mapped memory.
 * @offset: Within EC_LPC_ADDR_MEMMAP region.
 * @bytes: Number of bytes to पढ़ो. Zero means "read a string" (including '\0')
 *         At most only EC_MEMMAP_SIZE bytes can be पढ़ो.
 * @buffer: Where to store the result. The ioctl वापसs the number of bytes
 *         पढ़ो or negative on error.
 */
काष्ठा cros_ec_पढ़ोmem अणु
	uपूर्णांक32_t offset;
	uपूर्णांक32_t bytes;
	uपूर्णांक8_t buffer[EC_MEMMAP_SIZE];
पूर्ण;

#घोषणा CROS_EC_DEV_IOC       0xEC
#घोषणा CROS_EC_DEV_IOCXCMD   _IOWR(CROS_EC_DEV_IOC, 0, काष्ठा cros_ec_command)
#घोषणा CROS_EC_DEV_IOCRDMEM  _IOWR(CROS_EC_DEV_IOC, 1, काष्ठा cros_ec_पढ़ोmem)
#घोषणा CROS_EC_DEV_IOCEVENTMASK _IO(CROS_EC_DEV_IOC, 2)

#पूर्ण_अगर /* _CROS_EC_DEV_H_ */
