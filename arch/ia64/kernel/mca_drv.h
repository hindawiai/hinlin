<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * File:	mca_drv.h
 * Purpose:	Define helpers क्रम Generic MCA handling
 *
 * Copyright (C) 2004 FUJITSU LIMITED
 * Copyright (C) 2004 Hidetoshi Seto <seto.hidetoshi@jp.fujitsu.com>
 */
/*
 * Processor error section:
 *
 *  +-sal_log_processor_info_t *info-------------+
 *  | sal_log_section_hdr_t header;              |
 *  | ...                                        |
 *  | sal_log_mod_error_info_t info[0];          |
 *  +-+----------------+-------------------------+
 *    | CACHE_CHECK    |  ^ num_cache_check v
 *    +----------------+
 *    | TLB_CHECK      |  ^ num_tlb_check v
 *    +----------------+
 *    | BUS_CHECK      |  ^ num_bus_check v
 *    +----------------+
 *    | REG_खाता_CHECK |  ^ num_reg_file_check v
 *    +----------------+
 *    | MS_CHECK       |  ^ num_ms_check v
 *  +-काष्ठा cpuid_info *id----------------------+
 *  | regs[5];                                   |
 *  | reserved;                                  |
 *  +-sal_processor_अटल_info_t *regs----------+
 *  | valid;                                     |
 *  | ...                                        |
 *  | fr[128];                                   |
 *  +--------------------------------------------+
 */

/* peidx: index of processor error section */
प्रकार काष्ठा peidx_table अणु
	sal_log_processor_info_t        *info;
	काष्ठा sal_cpuid_info           *id;
	sal_processor_अटल_info_t     *regs;
पूर्ण peidx_table_t;

#घोषणा peidx_head(p)   (((p)->info))
#घोषणा peidx_mid(p)    (((p)->id))
#घोषणा peidx_bottom(p) (((p)->regs))

#घोषणा peidx_psp(p)           (&(peidx_head(p)->proc_state_parameter))
#घोषणा peidx_field_valid(p)   (&(peidx_head(p)->valid))
#घोषणा peidx_minstate_area(p) (&(peidx_bottom(p)->min_state_area))

#घोषणा peidx_cache_check_num(p)    (peidx_head(p)->valid.num_cache_check)
#घोषणा peidx_tlb_check_num(p)      (peidx_head(p)->valid.num_tlb_check)
#घोषणा peidx_bus_check_num(p)      (peidx_head(p)->valid.num_bus_check)
#घोषणा peidx_reg_file_check_num(p) (peidx_head(p)->valid.num_reg_file_check)
#घोषणा peidx_ms_check_num(p)       (peidx_head(p)->valid.num_ms_check)

#घोषणा peidx_cache_check_idx(p, n)    (n)
#घोषणा peidx_tlb_check_idx(p, n)      (peidx_cache_check_idx(p, peidx_cache_check_num(p)) + n)
#घोषणा peidx_bus_check_idx(p, n)      (peidx_tlb_check_idx(p, peidx_tlb_check_num(p)) + n)
#घोषणा peidx_reg_file_check_idx(p, n) (peidx_bus_check_idx(p, peidx_bus_check_num(p)) + n)
#घोषणा peidx_ms_check_idx(p, n)       (peidx_reg_file_check_idx(p, peidx_reg_file_check_num(p)) + n)

#घोषणा peidx_mod_error_info(p, name, n) \
(अणु	पूर्णांक __idx = peidx_##name##_idx(p, n); \
	sal_log_mod_error_info_t *__ret = शून्य; \
	अगर (peidx_##name##_num(p) > n) /*BUG*/ \
		__ret = &(peidx_head(p)->info[__idx]); \
	__ret; पूर्ण)

#घोषणा peidx_cache_check(p, n)    peidx_mod_error_info(p, cache_check, n)
#घोषणा peidx_tlb_check(p, n)      peidx_mod_error_info(p, tlb_check, n)
#घोषणा peidx_bus_check(p, n)      peidx_mod_error_info(p, bus_check, n)
#घोषणा peidx_reg_file_check(p, n) peidx_mod_error_info(p, reg_file_check, n)
#घोषणा peidx_ms_check(p, n)       peidx_mod_error_info(p, ms_check, n)

#घोषणा peidx_check_info(proc, name, n) \
(अणु \
	sal_log_mod_error_info_t *__info = peidx_mod_error_info(proc, name, n);\
	u64 __temp = __info && __info->valid.check_info \
		? __info->check_info : 0; \
	__temp; पूर्ण)

/* slidx: index of SAL log error record */

प्रकार काष्ठा slidx_list अणु
	काष्ठा list_head list;
	sal_log_section_hdr_t *hdr;
पूर्ण slidx_list_t;

प्रकार काष्ठा slidx_table अणु
	sal_log_record_header_t *header;
	पूर्णांक n_sections;			/* # of section headers */
	काष्ठा list_head proc_err;
	काष्ठा list_head mem_dev_err;
	काष्ठा list_head sel_dev_err;
	काष्ठा list_head pci_bus_err;
	काष्ठा list_head smbios_dev_err;
	काष्ठा list_head pci_comp_err;
	काष्ठा list_head plat_specअगरic_err;
	काष्ठा list_head host_ctlr_err;
	काष्ठा list_head plat_bus_err;
	काष्ठा list_head unsupported;	/* list of unsupported sections */
पूर्ण slidx_table_t;

#घोषणा slidx_क्रमeach_entry(pos, head) \
	list_क्रम_each_entry(pos, head, list)
#घोषणा slidx_first_entry(head) \
	(((head)->next != (head)) ? list_entry((head)->next, typeof(slidx_list_t), list) : शून्य)
#घोषणा slidx_count(slidx, sec) \
(अणु	पूर्णांक __count = 0; \
	slidx_list_t *__pos; \
	slidx_क्रमeach_entry(__pos, &((slidx)->sec)) अणु __count++; पूर्ण\
	__count; पूर्ण)

काष्ठा mca_table_entry अणु
	पूर्णांक start_addr;	/* location-relative starting address of MCA recoverable range */
	पूर्णांक end_addr;	/* location-relative ending address of MCA recoverable range */
पूर्ण;

बाह्य स्थिर काष्ठा mca_table_entry *search_mca_tables (अचिन्हित दीर्घ addr);
बाह्य पूर्णांक mca_recover_range(अचिन्हित दीर्घ);
बाह्य व्योम ia64_mlogbuf_dump(व्योम);

