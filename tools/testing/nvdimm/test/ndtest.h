<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
#अगर_अघोषित NDTEST_H
#घोषणा NDTEST_H

#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/libnvdimm.h>

/* SCM device is unable to persist memory contents */
#घोषणा PAPR_PMEM_UNARMED                   (1ULL << (63 - 0))
/* SCM device failed to persist memory contents */
#घोषणा PAPR_PMEM_SHUTDOWN_सूचीTY            (1ULL << (63 - 1))
/* SCM device contents are not persisted from previous IPL */
#घोषणा PAPR_PMEM_EMPTY                     (1ULL << (63 - 3))
#घोषणा PAPR_PMEM_HEALTH_CRITICAL           (1ULL << (63 - 4))
/* SCM device will be garded off next IPL due to failure */
#घोषणा PAPR_PMEM_HEALTH_FATAL              (1ULL << (63 - 5))
/* SCM contents cannot persist due to current platक्रमm health status */
#घोषणा PAPR_PMEM_HEALTH_UNHEALTHY          (1ULL << (63 - 6))

/* Bits status indicators क्रम health biपंचांगap indicating unarmed dimm */
#घोषणा PAPR_PMEM_UNARMED_MASK (PAPR_PMEM_UNARMED |		\
				PAPR_PMEM_HEALTH_UNHEALTHY)

#घोषणा PAPR_PMEM_SAVE_FAILED                (1ULL << (63 - 10))

/* Bits status indicators क्रम health biपंचांगap indicating unflushed dimm */
#घोषणा PAPR_PMEM_BAD_SHUTDOWN_MASK (PAPR_PMEM_SHUTDOWN_सूचीTY)

/* Bits status indicators क्रम health biपंचांगap indicating unrestored dimm */
#घोषणा PAPR_PMEM_BAD_RESTORE_MASK  (PAPR_PMEM_EMPTY)

/* Bit status indicators क्रम smart event notअगरication */
#घोषणा PAPR_PMEM_SMART_EVENT_MASK (PAPR_PMEM_HEALTH_CRITICAL | \
				    PAPR_PMEM_HEALTH_FATAL |	\
				    PAPR_PMEM_HEALTH_UNHEALTHY)

#घोषणा PAPR_PMEM_SAVE_MASK                (PAPR_PMEM_SAVE_FAILED)

काष्ठा ndtest_config;

काष्ठा ndtest_priv अणु
	काष्ठा platक्रमm_device pdev;
	काष्ठा device_node *dn;
	काष्ठा list_head resources;
	काष्ठा nvdimm_bus_descriptor bus_desc;
	काष्ठा nvdimm_bus *bus;
	काष्ठा ndtest_config *config;

	dma_addr_t *dcr_dma;
	dma_addr_t *label_dma;
	dma_addr_t *dimm_dma;
पूर्ण;

काष्ठा ndtest_blk_mmio अणु
	व्योम __iomem *base;
	u64 size;
	u64 base_offset;
	u32 line_size;
	u32 num_lines;
	u32 table_size;
पूर्ण;

काष्ठा ndtest_dimm अणु
	काष्ठा device *dev;
	काष्ठा nvdimm *nvdimm;
	काष्ठा ndtest_blk_mmio *mmio;
	काष्ठा nd_region *blk_region;

	dma_addr_t address;
	अचिन्हित दीर्घ दीर्घ flags;
	अचिन्हित दीर्घ config_size;
	व्योम *label_area;
	अक्षर *uuid_str;

	अचिन्हित पूर्णांक size;
	अचिन्हित पूर्णांक handle;
	अचिन्हित पूर्णांक fail_cmd;
	अचिन्हित पूर्णांक physical_id;
	अचिन्हित पूर्णांक num_क्रमmats;
	पूर्णांक id;
	पूर्णांक fail_cmd_code;
	u8 no_alias;
पूर्ण;

काष्ठा ndtest_mapping अणु
	u64 start;
	u64 size;
	u8 position;
	u8 dimm;
पूर्ण;

काष्ठा ndtest_region अणु
	काष्ठा nd_region *region;
	काष्ठा ndtest_mapping *mapping;
	u64 size;
	u8 type;
	u8 num_mappings;
	u8 range_index;
पूर्ण;

काष्ठा ndtest_config अणु
	काष्ठा ndtest_dimm *dimms;
	काष्ठा ndtest_region *regions;
	अचिन्हित पूर्णांक dimm_count;
	अचिन्हित पूर्णांक dimm_start;
	u8 num_regions;
पूर्ण;

#पूर्ण_अगर /* NDTEST_H */
