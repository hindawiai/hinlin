<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * OS info memory पूर्णांकerface
 *
 * Copyright IBM Corp. 2012
 * Author(s): Michael Holzheu <holzheu@linux.vnet.ibm.com>
 */
#अगर_अघोषित _ASM_S390_OS_INFO_H
#घोषणा _ASM_S390_OS_INFO_H

#घोषणा OS_INFO_VERSION_MAJOR	1
#घोषणा OS_INFO_VERSION_MINOR	1
#घोषणा OS_INFO_MAGIC		0x4f53494e464f535aULL /* OSINFOSZ */

#घोषणा OS_INFO_VMCOREINFO	0
#घोषणा OS_INFO_REIPL_BLOCK	1

काष्ठा os_info_entry अणु
	u64	addr;
	u64	size;
	u32	csum;
पूर्ण __packed;

काष्ठा os_info अणु
	u64	magic;
	u32	csum;
	u16	version_major;
	u16	version_minor;
	u64	crashkernel_addr;
	u64	crashkernel_size;
	काष्ठा os_info_entry entry[2];
	u8	reserved[4024];
पूर्ण __packed;

व्योम os_info_init(व्योम);
व्योम os_info_entry_add(पूर्णांक nr, व्योम *ptr, u64 len);
व्योम os_info_crashkernel_add(अचिन्हित दीर्घ base, अचिन्हित दीर्घ size);
u32 os_info_csum(काष्ठा os_info *os_info);

#अगर_घोषित CONFIG_CRASH_DUMP
व्योम *os_info_old_entry(पूर्णांक nr, अचिन्हित दीर्घ *size);
पूर्णांक copy_oldmem_kernel(व्योम *dst, व्योम *src, माप_प्रकार count);
#अन्यथा
अटल अंतरभूत व्योम *os_info_old_entry(पूर्णांक nr, अचिन्हित दीर्घ *size)
अणु
	वापस शून्य;
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* _ASM_S390_OS_INFO_H */
