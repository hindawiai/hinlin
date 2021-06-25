<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * s390x processor specअगरic defines
 */
#अगर_अघोषित SELFTEST_KVM_PROCESSOR_H
#घोषणा SELFTEST_KVM_PROCESSOR_H

/* Bits in the region/segment table entry */
#घोषणा REGION_ENTRY_ORIGIN	~0xfffUL /* region/segment table origin	   */
#घोषणा REGION_ENTRY_PROTECT	0x200	 /* region protection bit	   */
#घोषणा REGION_ENTRY_NOEXEC	0x100	 /* region no-execute bit	   */
#घोषणा REGION_ENTRY_OFFSET	0xc0	 /* region table offset		   */
#घोषणा REGION_ENTRY_INVALID	0x20	 /* invalid region table entry	   */
#घोषणा REGION_ENTRY_TYPE	0x0c	 /* region/segment table type mask */
#घोषणा REGION_ENTRY_LENGTH	0x03	 /* region third length		   */

/* Bits in the page table entry */
#घोषणा PAGE_INVALID	0x400		/* HW invalid bit    */
#घोषणा PAGE_PROTECT	0x200		/* HW पढ़ो-only bit  */
#घोषणा PAGE_NOEXEC	0x100		/* HW no-execute bit */

#पूर्ण_अगर
