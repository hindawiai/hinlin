<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-1.0+ WITH Linux-syscall-note */
/*
 * include/linux/loop.h
 *
 * Written by Theoकरोre Ts'o, 3/29/93.
 *
 * Copyright 1993 by Theoकरोre Ts'o.  Redistribution of this file is
 * permitted under the GNU General Public License.
 */
#अगर_अघोषित _UAPI_LINUX_LOOP_H
#घोषणा _UAPI_LINUX_LOOP_H


#घोषणा LO_NAME_SIZE	64
#घोषणा LO_KEY_SIZE	32


/*
 * Loop flags
 */
क्रमागत अणु
	LO_FLAGS_READ_ONLY	= 1,
	LO_FLAGS_AUTOCLEAR	= 4,
	LO_FLAGS_PARTSCAN	= 8,
	LO_FLAGS_सूचीECT_IO	= 16,
पूर्ण;

/* LO_FLAGS that can be set using LOOP_SET_STATUS(64) */
#घोषणा LOOP_SET_STATUS_SETTABLE_FLAGS (LO_FLAGS_AUTOCLEAR | LO_FLAGS_PARTSCAN)

/* LO_FLAGS that can be cleared using LOOP_SET_STATUS(64) */
#घोषणा LOOP_SET_STATUS_CLEARABLE_FLAGS (LO_FLAGS_AUTOCLEAR)

/* LO_FLAGS that can be set using LOOP_CONFIGURE */
#घोषणा LOOP_CONFIGURE_SETTABLE_FLAGS (LO_FLAGS_READ_ONLY | LO_FLAGS_AUTOCLEAR \
				       | LO_FLAGS_PARTSCAN | LO_FLAGS_सूचीECT_IO)

#समावेश <यंत्र/posix_types.h>	/* क्रम __kernel_old_dev_t */
#समावेश <linux/types.h>	/* क्रम __u64 */

/* Backwards compatibility version */
काष्ठा loop_info अणु
	पूर्णांक		   lo_number;		/* ioctl r/o */
	__kernel_old_dev_t lo_device; 		/* ioctl r/o */
	अचिन्हित दीर्घ	   lo_inode; 		/* ioctl r/o */
	__kernel_old_dev_t lo_rdevice; 		/* ioctl r/o */
	पूर्णांक		   lo_offset;
	पूर्णांक		   lo_encrypt_type;
	पूर्णांक		   lo_encrypt_key_size; 	/* ioctl w/o */
	पूर्णांक		   lo_flags;
	अक्षर		   lo_name[LO_NAME_SIZE];
	अचिन्हित अक्षर	   lo_encrypt_key[LO_KEY_SIZE]; /* ioctl w/o */
	अचिन्हित दीर्घ	   lo_init[2];
	अक्षर		   reserved[4];
पूर्ण;

काष्ठा loop_info64 अणु
	__u64		   lo_device;			/* ioctl r/o */
	__u64		   lo_inode;			/* ioctl r/o */
	__u64		   lo_rdevice;			/* ioctl r/o */
	__u64		   lo_offset;
	__u64		   lo_sizelimit;/* bytes, 0 == max available */
	__u32		   lo_number;			/* ioctl r/o */
	__u32		   lo_encrypt_type;
	__u32		   lo_encrypt_key_size;		/* ioctl w/o */
	__u32		   lo_flags;
	__u8		   lo_file_name[LO_NAME_SIZE];
	__u8		   lo_crypt_name[LO_NAME_SIZE];
	__u8		   lo_encrypt_key[LO_KEY_SIZE]; /* ioctl w/o */
	__u64		   lo_init[2];
पूर्ण;

/**
 * काष्ठा loop_config - Complete configuration क्रम a loop device.
 * @fd: fd of the file to be used as a backing file क्रम the loop device.
 * @block_size: block size to use; ignored अगर 0.
 * @info: काष्ठा loop_info64 to configure the loop device with.
 *
 * This काष्ठाure is used with the LOOP_CONFIGURE ioctl, and can be used to
 * atomically setup and configure all loop device parameters at once.
 */
काष्ठा loop_config अणु
	__u32			fd;
	__u32                   block_size;
	काष्ठा loop_info64	info;
	__u64			__reserved[8];
पूर्ण;

/*
 * Loop filter types
 */

#घोषणा LO_CRYPT_NONE		0
#घोषणा LO_CRYPT_XOR		1
#घोषणा LO_CRYPT_DES		2
#घोषणा LO_CRYPT_FISH2		3    /* Twofish encryption */
#घोषणा LO_CRYPT_BLOW		4
#घोषणा LO_CRYPT_CAST128	5
#घोषणा LO_CRYPT_IDEA		6
#घोषणा LO_CRYPT_DUMMY		9
#घोषणा LO_CRYPT_SKIPJACK	10
#घोषणा LO_CRYPT_CRYPTOAPI	18
#घोषणा MAX_LO_CRYPT		20

/*
 * IOCTL commands --- we will commandeer 0x4C ('L')
 */

#घोषणा LOOP_SET_FD		0x4C00
#घोषणा LOOP_CLR_FD		0x4C01
#घोषणा LOOP_SET_STATUS		0x4C02
#घोषणा LOOP_GET_STATUS		0x4C03
#घोषणा LOOP_SET_STATUS64	0x4C04
#घोषणा LOOP_GET_STATUS64	0x4C05
#घोषणा LOOP_CHANGE_FD		0x4C06
#घोषणा LOOP_SET_CAPACITY	0x4C07
#घोषणा LOOP_SET_सूचीECT_IO	0x4C08
#घोषणा LOOP_SET_BLOCK_SIZE	0x4C09
#घोषणा LOOP_CONFIGURE		0x4C0A

/* /dev/loop-control पूर्णांकerface */
#घोषणा LOOP_CTL_ADD		0x4C80
#घोषणा LOOP_CTL_REMOVE		0x4C81
#घोषणा LOOP_CTL_GET_FREE	0x4C82
#पूर्ण_अगर /* _UAPI_LINUX_LOOP_H */
