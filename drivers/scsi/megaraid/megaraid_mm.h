<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *
 *			Linux MegaRAID device driver
 *
 * Copyright (c) 2003-2004  LSI Logic Corporation.
 *
 * खाता		: megaraid_mm.h
 */

#अगर_अघोषित MEGARAID_MM_H
#घोषणा MEGARAID_MM_H

#समावेश <linux/spinlock.h>
#समावेश <linux/fs.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/pci.h>
#समावेश <linux/list.h>
#समावेश <linux/miscdevice.h>

#समावेश "mbox_defs.h"
#समावेश "megaraid_ioctl.h"


#घोषणा LSI_COMMON_MOD_VERSION	"2.20.2.7"
#घोषणा LSI_COMMON_MOD_EXT_VERSION	\
		"(Release Date: Sun Jul 16 00:01:03 EST 2006)"


#घोषणा LSI_DBGLVL			dbglevel

// The smallest dma pool
#घोषणा MRAID_MM_INIT_BUFF_SIZE		4096

/**
 * mimd_t	: Old style ioctl packet काष्ठाure (deprecated)
 *
 * @inlen	:
 * @outlen	:
 * @fca		:
 * @opcode	:
 * @subopcode	:
 * @adapno	:
 * @buffer	:
 * @pad		:
 * @length	:
 * @mbox	:
 * @pthru	:
 * @data	:
 * @pad		:
 *
 * Note		: This काष्ठाure is DEPRECATED. New applications must use
 *		: uioc_t काष्ठाure instead. All new hba drivers use the new
 *		: क्रमmat. If we get this mimd packet, we will convert it पूर्णांकo
 *		: new uioc_t क्रमmat and send it to the hba drivers.
 */

प्रकार काष्ठा mimd अणु

	uपूर्णांक32_t inlen;
	uपूर्णांक32_t outlen;

	जोड़ अणु
		uपूर्णांक8_t fca[16];
		काष्ठा अणु
			uपूर्णांक8_t opcode;
			uपूर्णांक8_t subopcode;
			uपूर्णांक16_t adapno;
#अगर BITS_PER_LONG == 32
			uपूर्णांक8_t __user *buffer;
			uपूर्णांक8_t pad[4];
#पूर्ण_अगर
#अगर BITS_PER_LONG == 64
			uपूर्णांक8_t __user *buffer;
#पूर्ण_अगर
			uपूर्णांक32_t length;
		पूर्ण __attribute__ ((packed)) fcs;
	पूर्ण __attribute__ ((packed)) ui;

	uपूर्णांक8_t mbox[18];		/* 16 bytes + 2 status bytes */
	mraid_passthru_t pthru;

#अगर BITS_PER_LONG == 32
	अक्षर __user *data;		/* buffer <= 4096 क्रम 0x80 commands */
	अक्षर pad[4];
#पूर्ण_अगर
#अगर BITS_PER_LONG == 64
	अक्षर __user *data;
#पूर्ण_अगर

पूर्ण __attribute__ ((packed))mimd_t;

#पूर्ण_अगर // MEGARAID_MM_H

// vi: set ts=8 sw=8 tw=78:
