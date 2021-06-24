<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  PS3 platक्रमm declarations.
 *
 *  Copyright (C) 2006 Sony Computer Entertainment Inc.
 *  Copyright 2006 Sony Corp.
 */

#अगर !defined(_PS3_PLATFORM_H)
#घोषणा _PS3_PLATFORM_H

#समावेश <linux/rtc.h>
#समावेश <scsi/scsi.h>

#समावेश <यंत्र/ps3.h>

/* htab */

व्योम __init ps3_hpte_init(अचिन्हित दीर्घ htab_size);
व्योम __init ps3_map_htab(व्योम);

/* mm */

व्योम __init ps3_mm_init(व्योम);
व्योम __init ps3_mm_vas_create(अचिन्हित दीर्घ* htab_size);
व्योम ps3_mm_vas_destroy(व्योम);
व्योम ps3_mm_shutकरोwn(व्योम);

/* irq */

व्योम ps3_init_IRQ(व्योम);
व्योम ps3_shutकरोwn_IRQ(पूर्णांक cpu);
व्योम __init ps3_रेजिस्टर_ipi_debug_brk(अचिन्हित पूर्णांक cpu, अचिन्हित पूर्णांक virq);
व्योम __init ps3_रेजिस्टर_ipi_irq(अचिन्हित पूर्णांक cpu, अचिन्हित पूर्णांक virq);

/* smp */

व्योम smp_init_ps3(व्योम);
#अगर_घोषित CONFIG_SMP
व्योम ps3_smp_cleanup_cpu(पूर्णांक cpu);
#अन्यथा
अटल अंतरभूत व्योम ps3_smp_cleanup_cpu(पूर्णांक cpu) अणु पूर्ण
#पूर्ण_अगर

/* समय */

व्योम __init ps3_calibrate_decr(व्योम);
समय64_t __init ps3_get_boot_समय(व्योम);
व्योम ps3_get_rtc_समय(काष्ठा rtc_समय *समय);
पूर्णांक ps3_set_rtc_समय(काष्ठा rtc_समय *समय);

/* os area */

व्योम __init ps3_os_area_save_params(व्योम);
व्योम __init ps3_os_area_init(व्योम);

/* spu */

#अगर defined(CONFIG_SPU_BASE)
व्योम ps3_spu_set_platक्रमm (व्योम);
#अन्यथा
अटल अंतरभूत व्योम ps3_spu_set_platक्रमm (व्योम) अणुपूर्ण
#पूर्ण_अगर

/* repository bus info */

क्रमागत ps3_bus_type अणु
	PS3_BUS_TYPE_SB = 4,
	PS3_BUS_TYPE_STORAGE = 5,
पूर्ण;

क्रमागत ps3_dev_type अणु
	PS3_DEV_TYPE_STOR_DISK = TYPE_DISK,	/* 0 */
	PS3_DEV_TYPE_SB_GELIC = 3,
	PS3_DEV_TYPE_SB_USB = 4,
	PS3_DEV_TYPE_STOR_ROM = TYPE_ROM,	/* 5 */
	PS3_DEV_TYPE_SB_GPIO = 6,
	PS3_DEV_TYPE_STOR_FLASH = TYPE_RBC,	/* 14 */
पूर्ण;

पूर्णांक ps3_repository_पढ़ो_bus_str(अचिन्हित पूर्णांक bus_index, स्थिर अक्षर *bus_str,
	u64 *value);
पूर्णांक ps3_repository_पढ़ो_bus_id(अचिन्हित पूर्णांक bus_index, u64 *bus_id);
पूर्णांक ps3_repository_पढ़ो_bus_type(अचिन्हित पूर्णांक bus_index,
	क्रमागत ps3_bus_type *bus_type);
पूर्णांक ps3_repository_पढ़ो_bus_num_dev(अचिन्हित पूर्णांक bus_index,
	अचिन्हित पूर्णांक *num_dev);

/* repository bus device info */

क्रमागत ps3_पूर्णांकerrupt_type अणु
	PS3_INTERRUPT_TYPE_EVENT_PORT = 2,
	PS3_INTERRUPT_TYPE_SB_OHCI = 3,
	PS3_INTERRUPT_TYPE_SB_EHCI = 4,
	PS3_INTERRUPT_TYPE_OTHER = 5,
पूर्ण;

क्रमागत ps3_reg_type अणु
	PS3_REG_TYPE_SB_OHCI = 3,
	PS3_REG_TYPE_SB_EHCI = 4,
	PS3_REG_TYPE_SB_GPIO = 5,
पूर्ण;

पूर्णांक ps3_repository_पढ़ो_dev_str(अचिन्हित पूर्णांक bus_index,
	अचिन्हित पूर्णांक dev_index, स्थिर अक्षर *dev_str, u64 *value);
पूर्णांक ps3_repository_पढ़ो_dev_id(अचिन्हित पूर्णांक bus_index, अचिन्हित पूर्णांक dev_index,
	u64 *dev_id);
पूर्णांक ps3_repository_पढ़ो_dev_type(अचिन्हित पूर्णांक bus_index,
	अचिन्हित पूर्णांक dev_index, क्रमागत ps3_dev_type *dev_type);
पूर्णांक ps3_repository_पढ़ो_dev_पूर्णांकr(अचिन्हित पूर्णांक bus_index,
	अचिन्हित पूर्णांक dev_index, अचिन्हित पूर्णांक पूर्णांकr_index,
	क्रमागत ps3_पूर्णांकerrupt_type *पूर्णांकr_type, अचिन्हित पूर्णांक *पूर्णांकerrupt_id);
पूर्णांक ps3_repository_पढ़ो_dev_reg_type(अचिन्हित पूर्णांक bus_index,
	अचिन्हित पूर्णांक dev_index, अचिन्हित पूर्णांक reg_index,
	क्रमागत ps3_reg_type *reg_type);
पूर्णांक ps3_repository_पढ़ो_dev_reg_addr(अचिन्हित पूर्णांक bus_index,
	अचिन्हित पूर्णांक dev_index, अचिन्हित पूर्णांक reg_index, u64 *bus_addr,
	u64 *len);
पूर्णांक ps3_repository_पढ़ो_dev_reg(अचिन्हित पूर्णांक bus_index,
	अचिन्हित पूर्णांक dev_index, अचिन्हित पूर्णांक reg_index,
	क्रमागत ps3_reg_type *reg_type, u64 *bus_addr, u64 *len);

/* repository bus क्रमागतerators */

काष्ठा ps3_repository_device अणु
	अचिन्हित पूर्णांक bus_index;
	अचिन्हित पूर्णांक dev_index;
	क्रमागत ps3_bus_type bus_type;
	क्रमागत ps3_dev_type dev_type;
	u64 bus_id;
	u64 dev_id;
पूर्ण;

पूर्णांक ps3_repository_find_device(काष्ठा ps3_repository_device *repo);
पूर्णांक ps3_repository_find_device_by_id(काष्ठा ps3_repository_device *repo,
				     u64 bus_id, u64 dev_id);
पूर्णांक ps3_repository_find_devices(क्रमागत ps3_bus_type bus_type,
	पूर्णांक (*callback)(स्थिर काष्ठा ps3_repository_device *repo));
पूर्णांक ps3_repository_find_bus(क्रमागत ps3_bus_type bus_type, अचिन्हित पूर्णांक from,
	अचिन्हित पूर्णांक *bus_index);
पूर्णांक ps3_repository_find_पूर्णांकerrupt(स्थिर काष्ठा ps3_repository_device *repo,
	क्रमागत ps3_पूर्णांकerrupt_type पूर्णांकr_type, अचिन्हित पूर्णांक *पूर्णांकerrupt_id);
पूर्णांक ps3_repository_find_reg(स्थिर काष्ठा ps3_repository_device *repo,
	क्रमागत ps3_reg_type reg_type, u64 *bus_addr, u64 *len);

/* repository block device info */

पूर्णांक ps3_repository_पढ़ो_stor_dev_port(अचिन्हित पूर्णांक bus_index,
	अचिन्हित पूर्णांक dev_index, u64 *port);
पूर्णांक ps3_repository_पढ़ो_stor_dev_blk_size(अचिन्हित पूर्णांक bus_index,
	अचिन्हित पूर्णांक dev_index, u64 *blk_size);
पूर्णांक ps3_repository_पढ़ो_stor_dev_num_blocks(अचिन्हित पूर्णांक bus_index,
	अचिन्हित पूर्णांक dev_index, u64 *num_blocks);
पूर्णांक ps3_repository_पढ़ो_stor_dev_num_regions(अचिन्हित पूर्णांक bus_index,
	अचिन्हित पूर्णांक dev_index, अचिन्हित पूर्णांक *num_regions);
पूर्णांक ps3_repository_पढ़ो_stor_dev_region_id(अचिन्हित पूर्णांक bus_index,
	अचिन्हित पूर्णांक dev_index, अचिन्हित पूर्णांक region_index,
	अचिन्हित पूर्णांक *region_id);
पूर्णांक ps3_repository_पढ़ो_stor_dev_region_size(अचिन्हित पूर्णांक bus_index,
	अचिन्हित पूर्णांक dev_index,	अचिन्हित पूर्णांक region_index, u64 *region_size);
पूर्णांक ps3_repository_पढ़ो_stor_dev_region_start(अचिन्हित पूर्णांक bus_index,
	अचिन्हित पूर्णांक dev_index, अचिन्हित पूर्णांक region_index, u64 *region_start);
पूर्णांक ps3_repository_पढ़ो_stor_dev_info(अचिन्हित पूर्णांक bus_index,
	अचिन्हित पूर्णांक dev_index, u64 *port, u64 *blk_size,
	u64 *num_blocks, अचिन्हित पूर्णांक *num_regions);
पूर्णांक ps3_repository_पढ़ो_stor_dev_region(अचिन्हित पूर्णांक bus_index,
	अचिन्हित पूर्णांक dev_index, अचिन्हित पूर्णांक region_index,
	अचिन्हित पूर्णांक *region_id, u64 *region_start, u64 *region_size);

/* repository logical pu and memory info */

पूर्णांक ps3_repository_पढ़ो_num_pu(u64 *num_pu);
पूर्णांक ps3_repository_पढ़ो_pu_id(अचिन्हित पूर्णांक pu_index, u64 *pu_id);
पूर्णांक ps3_repository_पढ़ो_rm_base(अचिन्हित पूर्णांक ppe_id, u64 *rm_base);
पूर्णांक ps3_repository_पढ़ो_rm_size(अचिन्हित पूर्णांक ppe_id, u64 *rm_size);
पूर्णांक ps3_repository_पढ़ो_region_total(u64 *region_total);
पूर्णांक ps3_repository_पढ़ो_mm_info(u64 *rm_base, u64 *rm_size,
	u64 *region_total);
पूर्णांक ps3_repository_पढ़ो_highmem_region_count(अचिन्हित पूर्णांक *region_count);
पूर्णांक ps3_repository_पढ़ो_highmem_base(अचिन्हित पूर्णांक region_index,
	u64 *highmem_base);
पूर्णांक ps3_repository_पढ़ो_highmem_size(अचिन्हित पूर्णांक region_index,
	u64 *highmem_size);
पूर्णांक ps3_repository_पढ़ो_highmem_info(अचिन्हित पूर्णांक region_index,
	u64 *highmem_base, u64 *highmem_size);

#अगर defined (CONFIG_PS3_REPOSITORY_WRITE)
पूर्णांक ps3_repository_ग_लिखो_highmem_region_count(अचिन्हित पूर्णांक region_count);
पूर्णांक ps3_repository_ग_लिखो_highmem_base(अचिन्हित पूर्णांक region_index,
	u64 highmem_base);
पूर्णांक ps3_repository_ग_लिखो_highmem_size(अचिन्हित पूर्णांक region_index,
	u64 highmem_size);
पूर्णांक ps3_repository_ग_लिखो_highmem_info(अचिन्हित पूर्णांक region_index,
	u64 highmem_base, u64 highmem_size);
पूर्णांक ps3_repository_delete_highmem_info(अचिन्हित पूर्णांक region_index);
#अन्यथा
अटल अंतरभूत पूर्णांक ps3_repository_ग_लिखो_highmem_region_count(
	अचिन्हित पूर्णांक region_count) अणुवापस 0;पूर्ण
अटल अंतरभूत पूर्णांक ps3_repository_ग_लिखो_highmem_base(अचिन्हित पूर्णांक region_index,
	u64 highmem_base) अणुवापस 0;पूर्ण
अटल अंतरभूत पूर्णांक ps3_repository_ग_लिखो_highmem_size(अचिन्हित पूर्णांक region_index,
	u64 highmem_size) अणुवापस 0;पूर्ण
अटल अंतरभूत पूर्णांक ps3_repository_ग_लिखो_highmem_info(अचिन्हित पूर्णांक region_index,
	u64 highmem_base, u64 highmem_size) अणुवापस 0;पूर्ण
अटल अंतरभूत पूर्णांक ps3_repository_delete_highmem_info(अचिन्हित पूर्णांक region_index)
	अणुवापस 0;पूर्ण
#पूर्ण_अगर

/* repository pme info */

पूर्णांक ps3_repository_पढ़ो_num_be(अचिन्हित पूर्णांक *num_be);
पूर्णांक ps3_repository_पढ़ो_be_node_id(अचिन्हित पूर्णांक be_index, u64 *node_id);
पूर्णांक ps3_repository_पढ़ो_be_id(u64 node_id, u64 *be_id);
पूर्णांक ps3_repository_पढ़ो_tb_freq(u64 node_id, u64 *tb_freq);
पूर्णांक ps3_repository_पढ़ो_be_tb_freq(अचिन्हित पूर्णांक be_index, u64 *tb_freq);

/* repository perक्रमmance monitor info */

पूर्णांक ps3_repository_पढ़ो_lpm_privileges(अचिन्हित पूर्णांक be_index, u64 *lpar,
	u64 *rights);

/* repository 'Other OS' area */

पूर्णांक ps3_repository_पढ़ो_boot_dat_addr(u64 *lpar_addr);
पूर्णांक ps3_repository_पढ़ो_boot_dat_size(अचिन्हित पूर्णांक *size);
पूर्णांक ps3_repository_पढ़ो_boot_dat_info(u64 *lpar_addr, अचिन्हित पूर्णांक *size);

/* repository spu info */

/**
 * क्रमागत spu_resource_type - Type of spu resource.
 * @spu_resource_type_shared: Logical spu is shared with other partions.
 * @spu_resource_type_exclusive: Logical spu is not shared with other partions.
 *
 * Returned by ps3_repository_पढ़ो_spu_resource_id().
 */

क्रमागत ps3_spu_resource_type अणु
	PS3_SPU_RESOURCE_TYPE_SHARED = 0,
	PS3_SPU_RESOURCE_TYPE_EXCLUSIVE = 0x8000000000000000UL,
पूर्ण;

पूर्णांक ps3_repository_पढ़ो_num_spu_reserved(अचिन्हित पूर्णांक *num_spu_reserved);
पूर्णांक ps3_repository_पढ़ो_num_spu_resource_id(अचिन्हित पूर्णांक *num_resource_id);
पूर्णांक ps3_repository_पढ़ो_spu_resource_id(अचिन्हित पूर्णांक res_index,
	क्रमागत ps3_spu_resource_type* resource_type, अचिन्हित पूर्णांक *resource_id);

/* repository vuart info */

पूर्णांक ps3_repository_पढ़ो_vuart_av_port(अचिन्हित पूर्णांक *port);
पूर्णांक ps3_repository_पढ़ो_vuart_sysmgr_port(अचिन्हित पूर्णांक *port);

#पूर्ण_अगर
