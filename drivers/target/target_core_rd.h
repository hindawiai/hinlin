<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित TARGET_CORE_RD_H
#घोषणा TARGET_CORE_RD_H

#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <target/target_core_base.h>

#घोषणा RD_HBA_VERSION		"v4.0"
#घोषणा RD_MCP_VERSION		"4.0"

/* Largest piece of memory kदो_स्मृति can allocate */
#घोषणा RD_MAX_ALLOCATION_SIZE	65536
#घोषणा RD_DEVICE_QUEUE_DEPTH	32
#घोषणा RD_MAX_DEVICE_QUEUE_DEPTH 128
#घोषणा RD_BLOCKSIZE		512

/* Used in target_core_init_configfs() क्रम भव LUN 0 access */
पूर्णांक __init rd_module_init(व्योम);
व्योम rd_module_निकास(व्योम);

काष्ठा rd_dev_sg_table अणु
	u32		page_start_offset;
	u32		page_end_offset;
	u32		rd_sg_count;
	काष्ठा scatterlist *sg_table;
पूर्ण ____cacheline_aligned;

#घोषणा RDF_HAS_PAGE_COUNT	0x01
#घोषणा RDF_शून्यIO		0x02
#घोषणा RDF_DUMMY		0x04

काष्ठा rd_dev अणु
	काष्ठा se_device dev;
	u32		rd_flags;
	/* Unique Ramdisk Device ID in Ramdisk HBA */
	u32		rd_dev_id;
	/* Total page count क्रम ramdisk device */
	u32		rd_page_count;
	/* Number of SG tables in sg_table_array */
	u32		sg_table_count;
	/* Number of SG tables in sg_prot_array */
	u32		sg_prot_count;
	/* Array of rd_dev_sg_table_t containing scatterlists */
	काष्ठा rd_dev_sg_table *sg_table_array;
	/* Array of rd_dev_sg_table containing protection scatterlists */
	काष्ठा rd_dev_sg_table *sg_prot_array;
	/* Ramdisk HBA device is connected to */
	काष्ठा rd_host *rd_host;
पूर्ण ____cacheline_aligned;

काष्ठा rd_host अणु
	u32		rd_host_dev_id_count;
	u32		rd_host_id;		/* Unique Ramdisk Host ID */
पूर्ण ____cacheline_aligned;

#पूर्ण_अगर /* TARGET_CORE_RD_H */
