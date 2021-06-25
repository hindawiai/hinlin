<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * Copyright IBM Corp. 2021
 * Interface implementation क्रम communication with the CPU Measurement
 * counter facility device driver.
 *
 * Author(s): Thomas Richter <पंचांगricht@linux.ibm.com>
 *
 * Define क्रम ioctl() commands to communicate with the CPU Measurement
 * counter facility device driver.
 */

#अगर_अघोषित _PERF_CPUM_CF_DIAG_H
#घोषणा _PERF_CPUM_CF_DIAG_H

#समावेश <linux/ioctl.h>
#समावेश <linux/types.h>

#घोषणा S390_HWCTR_DEVICE		"hwctr"
#घोषणा S390_HWCTR_START_VERSION	1

काष्ठा s390_ctrset_start अणु		/* Set CPUs to operate on */
	__u64 version;			/* Version of पूर्णांकerface */
	__u64 data_bytes;		/* # of bytes required */
	__u64 cpumask_len;		/* Length of CPU mask in bytes */
	__u64 *cpumask;			/* Poपूर्णांकer to CPU mask */
	__u64 counter_sets;		/* Bit mask of counter sets to get */
पूर्ण;

काष्ठा s390_ctrset_setdata अणु		/* Counter set data */
	__u32 set;			/* Counter set number */
	__u32 no_cnts;			/* # of counters stored in cv[] */
	__u64 cv[0];			/* Counter values (variable length) */
पूर्ण;

काष्ठा s390_ctrset_cpudata अणु		/* Counter set data per CPU */
	__u32 cpu_nr;			/* CPU number */
	__u32 no_sets;			/* # of counters sets in data[] */
	काष्ठा s390_ctrset_setdata data[0];
पूर्ण;

काष्ठा s390_ctrset_पढ़ो अणु		/* Structure to get all ctr sets */
	__u64 no_cpus;			/* Total # of CPUs data taken from */
	काष्ठा s390_ctrset_cpudata data[0];
पूर्ण;

#घोषणा S390_HWCTR_MAGIC	'C'	/* Ranकरोm magic # क्रम ioctls */
#घोषणा	S390_HWCTR_START	_IOWR(S390_HWCTR_MAGIC, 1, काष्ठा s390_ctrset_start)
#घोषणा	S390_HWCTR_STOP		_IO(S390_HWCTR_MAGIC, 2)
#घोषणा	S390_HWCTR_READ		_IOWR(S390_HWCTR_MAGIC, 3, काष्ठा s390_ctrset_पढ़ो)
#पूर्ण_अगर
