<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * Structures क्रम hypfs पूर्णांकerface
 *
 * Copyright IBM Corp. 2013
 *
 * Author: Martin Schwidefsky <schwidefsky@de.ibm.com>
 */

#अगर_अघोषित _ASM_HYPFS_H
#घोषणा _ASM_HYPFS_H

#समावेश <linux/types.h>

/*
 * IOCTL क्रम binary पूर्णांकerface /sys/kernel/debug/diag_304
 */
काष्ठा hypfs_diag304 अणु
	__u32	args[2];
	__u64	data;
	__u64	rc;
पूर्ण __attribute__((packed));

#घोषणा HYPFS_IOCTL_MAGIC 0x10

#घोषणा HYPFS_DIAG304 \
	_IOWR(HYPFS_IOCTL_MAGIC, 0x20, काष्ठा hypfs_diag304)

/*
 * Structures क्रम binary पूर्णांकerface /sys/kernel/debug/diag_0c
 */
काष्ठा hypfs_diag0c_hdr अणु
	__u64	len;		/* Length of diag0c buffer without header */
	__u16	version;	/* Version of header */
	अक्षर	reserved1[6];	/* Reserved */
	अक्षर	tod_ext[16];	/* TOD घड़ी क्रम diag0c */
	__u64	count;		/* Number of entries (CPUs) in diag0c array */
	अक्षर	reserved2[24];	/* Reserved */
पूर्ण;

काष्ठा hypfs_diag0c_entry अणु
	अक्षर	date[8];	/* MM/DD/YY in EBCDIC */
	अक्षर	समय[8];	/* HH:MM:SS in EBCDIC */
	__u64	virtcpu;	/* Virtual समय consumed by the virt CPU (us) */
	__u64	totalproc;	/* Total of भव and simulation समय (us) */
	__u32	cpu;		/* Linux logical CPU number */
	__u32	reserved;	/* Align to 8 byte */
पूर्ण;

काष्ठा hypfs_diag0c_data अणु
	काष्ठा hypfs_diag0c_hdr		hdr;		/* 64 byte header */
	काष्ठा hypfs_diag0c_entry	entry[];	/* diag0c entry array */
पूर्ण;

#पूर्ण_अगर
