<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
#अगर_अघोषित _POWERPC_PROM_H
#घोषणा _POWERPC_PROM_H
#अगर_घोषित __KERNEL__

/*
 * Definitions क्रम talking to the Open Firmware PROM on
 * Power Macपूर्णांकosh computers.
 *
 * Copyright (C) 1996-2005 Paul Mackerras.
 *
 * Updates क्रम PPC64 by Peter Bergner & David Engebretsen, IBM Corp.
 */
#समावेश <linux/types.h>
#समावेश <यंत्र/irq.h>
#समावेश <linux/atomic.h>

/* These includes should be हटाओd once implicit includes are cleaned up. */
#समावेश <linux/of.h>
#समावेश <linux/of_fdt.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/platक्रमm_device.h>

#घोषणा OF_DT_BEGIN_NODE	0x1		/* Start of node, full name */
#घोषणा OF_DT_END_NODE		0x2		/* End node */
#घोषणा OF_DT_PROP		0x3		/* Property: name off, size,
						 * content */
#घोषणा OF_DT_NOP		0x4		/* nop */
#घोषणा OF_DT_END		0x9

#घोषणा OF_DT_VERSION		0x10

/*
 * This is what माला_लो passed to the kernel by prom_init or kexec
 *
 * The dt काष्ठा contains the device tree काष्ठाure, full pathes and
 * property contents. The dt strings contain a separate block with just
 * the strings क्रम the property names, and is fully page aligned and
 * self contained in a page, so that it can be kept around by the kernel,
 * each property name appears only once in this page (cheap compression)
 *
 * the mem_rsvmap contains a map of reserved ranges of physical memory,
 * passing it here instead of in the device-tree itself greatly simplअगरies
 * the job of everybody. It's just a list of u64 pairs (base/size) that
 * ends when size is 0
 */
काष्ठा boot_param_header अणु
	__be32	magic;			/* magic word OF_DT_HEADER */
	__be32	totalsize;		/* total size of DT block */
	__be32	off_dt_काष्ठा;		/* offset to काष्ठाure */
	__be32	off_dt_strings;		/* offset to strings */
	__be32	off_mem_rsvmap;		/* offset to memory reserve map */
	__be32	version;		/* क्रमmat version */
	__be32	last_comp_version;	/* last compatible version */
	/* version 2 fields below */
	__be32	boot_cpuid_phys;	/* Physical CPU id we're booting on */
	/* version 3 fields below */
	__be32	dt_strings_size;	/* size of the DT strings block */
	/* version 17 fields below */
	__be32	dt_काष्ठा_size;		/* size of the DT काष्ठाure block */
पूर्ण;

/*
 * OF address retreival & translation
 */

/* Parse the ibm,dma-winकरोw property of an OF node पूर्णांकo the busno, phys and
 * size parameters.
 */
व्योम of_parse_dma_winकरोw(काष्ठा device_node *dn, स्थिर __be32 *dma_winकरोw,
			 अचिन्हित दीर्घ *busno, अचिन्हित दीर्घ *phys,
			 अचिन्हित दीर्घ *size);

बाह्य व्योम of_instantiate_rtc(व्योम);

बाह्य पूर्णांक of_get_ibm_chip_id(काष्ठा device_node *np);

काष्ठा of_drc_info अणु
	अक्षर *drc_type;
	अक्षर *drc_name_prefix;
	u32 drc_index_start;
	u32 drc_name_suffix_start;
	u32 num_sequential_elems;
	u32 sequential_inc;
	u32 drc_घातer_करोमुख्य;
	u32 last_drc_index;
पूर्ण;

बाह्य पूर्णांक of_पढ़ो_drc_info_cell(काष्ठा property **prop,
			स्थिर __be32 **curval, काष्ठा of_drc_info *data);


/*
 * There are two methods क्रम telling firmware what our capabilities are.
 * Newer machines have an "ibm,client-architecture-support" method on the
 * root node.  For older machines, we have to call the "process-elf-header"
 * method in the /packages/elf-loader node, passing it a fake 32-bit
 * ELF header containing a couple of PT_NOTE sections that contain
 * काष्ठाures that contain various inक्रमmation.
 */

/* New method - extensible architecture description vector. */

/* Option vector bits - generic bits in byte 1 */
#घोषणा OV_IGNORE		0x80	/* ignore this vector */
#घोषणा OV_CESSATION_POLICY	0x40	/* halt अगर unsupported option present*/

/* Option vector 1: processor architectures supported */
#घोषणा OV1_PPC_2_00		0x80	/* set अगर we support PowerPC 2.00 */
#घोषणा OV1_PPC_2_01		0x40	/* set अगर we support PowerPC 2.01 */
#घोषणा OV1_PPC_2_02		0x20	/* set अगर we support PowerPC 2.02 */
#घोषणा OV1_PPC_2_03		0x10	/* set अगर we support PowerPC 2.03 */
#घोषणा OV1_PPC_2_04		0x08	/* set अगर we support PowerPC 2.04 */
#घोषणा OV1_PPC_2_05		0x04	/* set अगर we support PowerPC 2.05 */
#घोषणा OV1_PPC_2_06		0x02	/* set अगर we support PowerPC 2.06 */
#घोषणा OV1_PPC_2_07		0x01	/* set अगर we support PowerPC 2.07 */

#घोषणा OV1_PPC_3_00		0x80	/* set अगर we support PowerPC 3.00 */
#घोषणा OV1_PPC_3_1			0x40	/* set अगर we support PowerPC 3.1 */

/* Option vector 2: Open Firmware options supported */
#घोषणा OV2_REAL_MODE		0x20	/* set अगर we want OF in real mode */

/* Option vector 3: processor options supported */
#घोषणा OV3_FP			0x80	/* भग्नing poपूर्णांक */
#घोषणा OV3_VMX			0x40	/* VMX/Altivec */
#घोषणा OV3_DFP			0x20	/* decimal FP */

/* Option vector 4: IBM PAPR implementation */
#घोषणा OV4_MIN_ENT_CAP		0x01	/* minimum VP entitled capacity */

/* Option vector 5: PAPR/OF options supported
 * These bits are also used in firmware_has_feature() to validate
 * the capabilities reported क्रम vector 5 in the device tree so we
 * encode the vector index in the define and use the OV5_FEAT()
 * and OV5_INDX() macros to extract the desired inक्रमmation.
 */
#घोषणा OV5_FEAT(x)	((x) & 0xff)
#घोषणा OV5_INDX(x)	((x) >> 8)
#घोषणा OV5_LPAR		0x0280	/* logical partitioning supported */
#घोषणा OV5_SPLPAR		0x0240	/* shared-processor LPAR supported */
/* ibm,dynamic-reconfiguration-memory property supported */
#घोषणा OV5_DRCONF_MEMORY	0x0220
#घोषणा OV5_LARGE_PAGES		0x0210	/* large pages supported */
#घोषणा OV5_DONATE_DEDICATE_CPU	0x0202	/* करोnate dedicated CPU support */
#घोषणा OV5_MSI			0x0201	/* PCIe/MSI support */
#घोषणा OV5_CMO			0x0480	/* Cooperative Memory Overcommiपंचांगent */
#घोषणा OV5_XCMO		0x0440	/* Page Coalescing */
#घोषणा OV5_TYPE1_AFFINITY	0x0580	/* Type 1 NUMA affinity */
#घोषणा OV5_PRRN		0x0540	/* Platक्रमm Resource Reassignment */
#घोषणा OV5_HP_EVT		0x0604	/* Hot Plug Event support */
#घोषणा OV5_RESIZE_HPT		0x0601	/* Hash Page Table resizing */
#घोषणा OV5_PFO_HW_RNG		0x1180	/* PFO Ranकरोm Number Generator */
#घोषणा OV5_PFO_HW_842		0x1140	/* PFO Compression Accelerator */
#घोषणा OV5_PFO_HW_ENCR		0x1120	/* PFO Encryption Accelerator */
#घोषणा OV5_SUB_PROCESSORS	0x1501	/* 1,2,or 4 Sub-Processors supported */
#घोषणा OV5_DRMEM_V2		0x1680	/* ibm,dynamic-reconfiguration-v2 */
#घोषणा OV5_XIVE_SUPPORT	0x17C0	/* XIVE Exploitation Support Mask */
#घोषणा OV5_XIVE_LEGACY		0x1700	/* XIVE legacy mode Only */
#घोषणा OV5_XIVE_EXPLOIT	0x1740	/* XIVE exploitation mode Only */
#घोषणा OV5_XIVE_EITHER		0x1780	/* XIVE legacy or exploitation mode */
/* MMU Base Architecture */
#घोषणा OV5_MMU_SUPPORT		0x18C0	/* MMU Mode Support Mask */
#घोषणा OV5_MMU_HASH		0x1800	/* Hash MMU Only */
#घोषणा OV5_MMU_RADIX		0x1840	/* Radix MMU Only */
#घोषणा OV5_MMU_EITHER		0x1880	/* Hash or Radix Supported */
#घोषणा OV5_MMU_DYNAMIC		0x18C0	/* Hash or Radix Can Switch Later */
#घोषणा OV5_NMMU		0x1820	/* Nest MMU Available */
/* Hash Table Extensions */
#घोषणा OV5_HASH_SEG_TBL	0x1980	/* In Memory Segment Tables Available */
#घोषणा OV5_HASH_GTSE		0x1940	/* Guest Translation Shoot Down Avail */
/* Radix Table Extensions */
#घोषणा OV5_RADIX_GTSE		0x1A40	/* Guest Translation Shoot Down Avail */
#घोषणा OV5_DRC_INFO		0x1640	/* Redef Prop Structures: drc-info   */

/* Option Vector 6: IBM PAPR hपूर्णांकs */
#घोषणा OV6_LINUX		0x02	/* Linux is our OS */

#पूर्ण_अगर /* __KERNEL__ */
#पूर्ण_अगर /* _POWERPC_PROM_H */
