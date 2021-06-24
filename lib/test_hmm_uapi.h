<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * This is a module to test the HMM (Heterogeneous Memory Management) API
 * of the kernel. It allows a userspace program to expose its entire address
 * space through the HMM test module device file.
 */
#अगर_अघोषित _LIB_TEST_HMM_UAPI_H
#घोषणा _LIB_TEST_HMM_UAPI_H

#समावेश <linux/types.h>
#समावेश <linux/ioctl.h>

/*
 * Structure to pass to the HMM test driver to mimic a device accessing
 * प्रणाली memory and ZONE_DEVICE निजी memory through device page tables.
 *
 * @addr: (in) user address the device will पढ़ो/ग_लिखो
 * @ptr: (in) user address where device data is copied to/from
 * @npages: (in) number of pages to पढ़ो/ग_लिखो
 * @cpages: (out) number of pages copied
 * @faults: (out) number of device page faults seen
 */
काष्ठा hmm_dmirror_cmd अणु
	__u64		addr;
	__u64		ptr;
	__u64		npages;
	__u64		cpages;
	__u64		faults;
पूर्ण;

/* Expose the address space of the calling process through hmm device file */
#घोषणा HMM_DMIRROR_READ		_IOWR('H', 0x00, काष्ठा hmm_dmirror_cmd)
#घोषणा HMM_DMIRROR_WRITE		_IOWR('H', 0x01, काष्ठा hmm_dmirror_cmd)
#घोषणा HMM_DMIRROR_MIGRATE		_IOWR('H', 0x02, काष्ठा hmm_dmirror_cmd)
#घोषणा HMM_DMIRROR_SNAPSHOT		_IOWR('H', 0x03, काष्ठा hmm_dmirror_cmd)

/*
 * Values वापसed in hmm_dmirror_cmd.ptr क्रम HMM_DMIRROR_SNAPSHOT.
 * HMM_DMIRROR_PROT_ERROR: no valid mirror PTE क्रम this page
 * HMM_DMIRROR_PROT_NONE: unpopulated PTE or PTE with no access
 * HMM_DMIRROR_PROT_READ: पढ़ो-only PTE
 * HMM_DMIRROR_PROT_WRITE: पढ़ो/ग_लिखो PTE
 * HMM_DMIRROR_PROT_PMD: PMD sized page is fully mapped by same permissions
 * HMM_DMIRROR_PROT_PUD: PUD sized page is fully mapped by same permissions
 * HMM_DMIRROR_PROT_ZERO: special पढ़ो-only zero page
 * HMM_DMIRROR_PROT_DEV_PRIVATE_LOCAL: Migrated device निजी page on the
 *					device the ioctl() is made
 * HMM_DMIRROR_PROT_DEV_PRIVATE_REMOTE: Migrated device निजी page on some
 *					other device
 */
क्रमागत अणु
	HMM_DMIRROR_PROT_ERROR			= 0xFF,
	HMM_DMIRROR_PROT_NONE			= 0x00,
	HMM_DMIRROR_PROT_READ			= 0x01,
	HMM_DMIRROR_PROT_WRITE			= 0x02,
	HMM_DMIRROR_PROT_PMD			= 0x04,
	HMM_DMIRROR_PROT_PUD			= 0x08,
	HMM_DMIRROR_PROT_ZERO			= 0x10,
	HMM_DMIRROR_PROT_DEV_PRIVATE_LOCAL	= 0x20,
	HMM_DMIRROR_PROT_DEV_PRIVATE_REMOTE	= 0x30,
पूर्ण;

#पूर्ण_अगर /* _LIB_TEST_HMM_UAPI_H */
