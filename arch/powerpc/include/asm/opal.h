<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * PowerNV OPAL definitions.
 *
 * Copyright 2011 IBM Corp.
 */

#अगर_अघोषित _ASM_POWERPC_OPAL_H
#घोषणा _ASM_POWERPC_OPAL_H

#समावेश <यंत्र/opal-api.h>

#अगर_अघोषित __ASSEMBLY__

#समावेश <linux/notअगरier.h>

/* We calculate number of sg entries based on PAGE_SIZE */
#घोषणा SG_ENTRIES_PER_NODE ((PAGE_SIZE - 16) / माप(काष्ठा opal_sg_entry))

/* Default समय to sleep or delay between OPAL_BUSY/OPAL_BUSY_EVENT loops */
#घोषणा OPAL_BUSY_DELAY_MS	10

/* /sys/firmware/opal */
बाह्य काष्ठा kobject *opal_kobj;

/* /ibm,opal */
बाह्य काष्ठा device_node *opal_node;

/* API functions */
पूर्णांक64_t opal_invalid_call(व्योम);
पूर्णांक64_t opal_npu_map_lpar(uपूर्णांक64_t phb_id, uपूर्णांक64_t bdf, uपूर्णांक64_t lparid,
			uपूर्णांक64_t lpcr);
पूर्णांक64_t opal_npu_spa_setup(uपूर्णांक64_t phb_id, uपूर्णांक32_t bdfn,
			uपूर्णांक64_t addr, uपूर्णांक64_t PE_mask);
पूर्णांक64_t opal_npu_spa_clear_cache(uपूर्णांक64_t phb_id, uपूर्णांक32_t bdfn,
				uपूर्णांक64_t PE_handle);
पूर्णांक64_t opal_npu_tl_set(uपूर्णांक64_t phb_id, uपूर्णांक32_t bdfn, दीर्घ cap,
			uपूर्णांक64_t rate_phys, uपूर्णांक32_t size);

पूर्णांक64_t opal_console_ग_लिखो(पूर्णांक64_t term_number, __be64 *length,
			   स्थिर uपूर्णांक8_t *buffer);
पूर्णांक64_t opal_console_पढ़ो(पूर्णांक64_t term_number, __be64 *length,
			  uपूर्णांक8_t *buffer);
पूर्णांक64_t opal_console_ग_लिखो_buffer_space(पूर्णांक64_t term_number,
					__be64 *length);
पूर्णांक64_t opal_console_flush(पूर्णांक64_t term_number);
पूर्णांक64_t opal_rtc_पढ़ो(__be32 *year_month_day,
		      __be64 *hour_minute_second_millisecond);
पूर्णांक64_t opal_rtc_ग_लिखो(uपूर्णांक32_t year_month_day,
		       uपूर्णांक64_t hour_minute_second_millisecond);
पूर्णांक64_t opal_tpo_पढ़ो(uपूर्णांक64_t token, __be32 *year_mon_day, __be32 *hour_min);
पूर्णांक64_t opal_tpo_ग_लिखो(uपूर्णांक64_t token, uपूर्णांक32_t year_mon_day,
		       uपूर्णांक32_t hour_min);
पूर्णांक64_t opal_cec_घातer_करोwn(uपूर्णांक64_t request);
पूर्णांक64_t opal_cec_reboot(व्योम);
पूर्णांक64_t opal_cec_reboot2(uपूर्णांक32_t reboot_type, स्थिर अक्षर *diag);
पूर्णांक64_t opal_पढ़ो_nvram(uपूर्णांक64_t buffer, uपूर्णांक64_t size, uपूर्णांक64_t offset);
पूर्णांक64_t opal_ग_लिखो_nvram(uपूर्णांक64_t buffer, uपूर्णांक64_t size, uपूर्णांक64_t offset);
पूर्णांक64_t opal_handle_पूर्णांकerrupt(uपूर्णांक64_t isn, __be64 *outstanding_event_mask);
पूर्णांक64_t opal_poll_events(__be64 *outstanding_event_mask);
पूर्णांक64_t opal_pci_set_hub_tce_memory(uपूर्णांक64_t hub_id, uपूर्णांक64_t tce_mem_addr,
				    uपूर्णांक64_t tce_mem_size);
पूर्णांक64_t opal_pci_set_phb_tce_memory(uपूर्णांक64_t phb_id, uपूर्णांक64_t tce_mem_addr,
				    uपूर्णांक64_t tce_mem_size);
पूर्णांक64_t opal_pci_config_पढ़ो_byte(uपूर्णांक64_t phb_id, uपूर्णांक64_t bus_dev_func,
				  uपूर्णांक64_t offset, uपूर्णांक8_t *data);
पूर्णांक64_t opal_pci_config_पढ़ो_half_word(uपूर्णांक64_t phb_id, uपूर्णांक64_t bus_dev_func,
				       uपूर्णांक64_t offset, __be16 *data);
पूर्णांक64_t opal_pci_config_पढ़ो_word(uपूर्णांक64_t phb_id, uपूर्णांक64_t bus_dev_func,
				  uपूर्णांक64_t offset, __be32 *data);
पूर्णांक64_t opal_pci_config_ग_लिखो_byte(uपूर्णांक64_t phb_id, uपूर्णांक64_t bus_dev_func,
				   uपूर्णांक64_t offset, uपूर्णांक8_t data);
पूर्णांक64_t opal_pci_config_ग_लिखो_half_word(uपूर्णांक64_t phb_id, uपूर्णांक64_t bus_dev_func,
					uपूर्णांक64_t offset, uपूर्णांक16_t data);
पूर्णांक64_t opal_pci_config_ग_लिखो_word(uपूर्णांक64_t phb_id, uपूर्णांक64_t bus_dev_func,
				   uपूर्णांक64_t offset, uपूर्णांक32_t data);
पूर्णांक64_t opal_set_xive(uपूर्णांक32_t isn, uपूर्णांक16_t server, uपूर्णांक8_t priority);
पूर्णांक64_t opal_get_xive(uपूर्णांक32_t isn, __be16 *server, uपूर्णांक8_t *priority);
पूर्णांक64_t opal_रेजिस्टर_exception_handler(uपूर्णांक64_t opal_exception,
					uपूर्णांक64_t handler_address,
					uपूर्णांक64_t glue_cache_line);
पूर्णांक64_t opal_pci_eeh_मुक्तze_status(uपूर्णांक64_t phb_id, uपूर्णांक64_t pe_number,
				   uपूर्णांक8_t *मुक्तze_state,
				   __be16 *pci_error_type,
				   __be64 *phb_status);
पूर्णांक64_t opal_pci_eeh_मुक्तze_clear(uपूर्णांक64_t phb_id, uपूर्णांक64_t pe_number,
				  uपूर्णांक64_t eeh_action_token);
पूर्णांक64_t opal_pci_eeh_मुक्तze_set(uपूर्णांक64_t phb_id, uपूर्णांक64_t pe_number,
				uपूर्णांक64_t eeh_action_token);
पूर्णांक64_t opal_pci_err_inject(uपूर्णांक64_t phb_id, uपूर्णांक32_t pe_no, uपूर्णांक32_t type,
			    uपूर्णांक32_t func, uपूर्णांक64_t addr, uपूर्णांक64_t mask);
पूर्णांक64_t opal_pci_shpc(uपूर्णांक64_t phb_id, uपूर्णांक64_t shpc_action, uपूर्णांक8_t *state);



पूर्णांक64_t opal_pci_phb_mmio_enable(uपूर्णांक64_t phb_id, uपूर्णांक16_t winकरोw_type,
				 uपूर्णांक16_t winकरोw_num, uपूर्णांक16_t enable);
पूर्णांक64_t opal_pci_set_phb_mem_winकरोw(uपूर्णांक64_t phb_id, uपूर्णांक16_t winकरोw_type,
				    uपूर्णांक16_t winकरोw_num,
				    uपूर्णांक64_t starting_real_address,
				    uपूर्णांक64_t starting_pci_address,
				    uपूर्णांक64_t size);
पूर्णांक64_t opal_pci_map_pe_mmio_winकरोw(uपूर्णांक64_t phb_id, uपूर्णांक16_t pe_number,
				    uपूर्णांक16_t winकरोw_type, uपूर्णांक16_t winकरोw_num,
				    uपूर्णांक16_t segment_num);
पूर्णांक64_t opal_pci_set_phb_table_memory(uपूर्णांक64_t phb_id, uपूर्णांक64_t rtt_addr,
				      uपूर्णांक64_t ivt_addr, uपूर्णांक64_t ivt_len,
				      uपूर्णांक64_t reject_array_addr,
				      uपूर्णांक64_t peltv_addr);
पूर्णांक64_t opal_pci_set_pe(uपूर्णांक64_t phb_id, uपूर्णांक64_t pe_number, uपूर्णांक64_t bus_dev_func,
			uपूर्णांक8_t bus_compare, uपूर्णांक8_t dev_compare, uपूर्णांक8_t func_compare,
			uपूर्णांक8_t pe_action);
पूर्णांक64_t opal_pci_set_peltv(uपूर्णांक64_t phb_id, uपूर्णांक32_t parent_pe, uपूर्णांक32_t child_pe,
			   uपूर्णांक8_t state);
पूर्णांक64_t opal_pci_set_mve(uपूर्णांक64_t phb_id, uपूर्णांक32_t mve_number, uपूर्णांक32_t pe_number);
पूर्णांक64_t opal_pci_set_mve_enable(uपूर्णांक64_t phb_id, uपूर्णांक32_t mve_number,
				uपूर्णांक32_t state);
पूर्णांक64_t opal_pci_get_xive_reissue(uपूर्णांक64_t phb_id, uपूर्णांक32_t xive_number,
				  uपूर्णांक8_t *p_bit, uपूर्णांक8_t *q_bit);
पूर्णांक64_t opal_pci_set_xive_reissue(uपूर्णांक64_t phb_id, uपूर्णांक32_t xive_number,
				  uपूर्णांक8_t p_bit, uपूर्णांक8_t q_bit);
पूर्णांक64_t opal_pci_msi_eoi(uपूर्णांक64_t phb_id, uपूर्णांक32_t hw_irq);
पूर्णांक64_t opal_pci_set_xive_pe(uपूर्णांक64_t phb_id, uपूर्णांक32_t pe_number,
			     uपूर्णांक32_t xive_num);
पूर्णांक64_t opal_get_xive_source(uपूर्णांक64_t phb_id, uपूर्णांक32_t xive_num,
			     __be32 *पूर्णांकerrupt_source_number);
पूर्णांक64_t opal_get_msi_32(uपूर्णांक64_t phb_id, uपूर्णांक32_t mve_number, uपूर्णांक32_t xive_num,
			uपूर्णांक8_t msi_range, __be32 *msi_address,
			__be32 *message_data);
पूर्णांक64_t opal_get_msi_64(uपूर्णांक64_t phb_id, uपूर्णांक32_t mve_number,
			uपूर्णांक32_t xive_num, uपूर्णांक8_t msi_range,
			__be64 *msi_address, __be32 *message_data);
पूर्णांक64_t opal_start_cpu(uपूर्णांक64_t thपढ़ो_number, uपूर्णांक64_t start_address);
पूर्णांक64_t opal_query_cpu_status(uपूर्णांक64_t thपढ़ो_number, uपूर्णांक8_t *thपढ़ो_status);
पूर्णांक64_t opal_ग_लिखो_oppanel(oppanel_line_t *lines, uपूर्णांक64_t num_lines);
पूर्णांक64_t opal_pci_map_pe_dma_winकरोw(uपूर्णांक64_t phb_id, uपूर्णांक16_t pe_number, uपूर्णांक16_t winकरोw_id,
				   uपूर्णांक16_t tce_levels, uपूर्णांक64_t tce_table_addr,
				   uपूर्णांक64_t tce_table_size, uपूर्णांक64_t tce_page_size);
पूर्णांक64_t opal_pci_map_pe_dma_winकरोw_real(uपूर्णांक64_t phb_id, uपूर्णांक16_t pe_number,
					uपूर्णांक16_t dma_winकरोw_number, uपूर्णांक64_t pci_start_addr,
					uपूर्णांक64_t pci_mem_size);
पूर्णांक64_t opal_pci_reset(uपूर्णांक64_t id, uपूर्णांक8_t reset_scope, uपूर्णांक8_t निश्चित_state);

पूर्णांक64_t opal_pci_get_hub_diag_data(uपूर्णांक64_t hub_id, व्योम *diag_buffer,
				   uपूर्णांक64_t diag_buffer_len);
पूर्णांक64_t opal_pci_get_phb_diag_data(uपूर्णांक64_t phb_id, व्योम *diag_buffer,
				   uपूर्णांक64_t diag_buffer_len);
पूर्णांक64_t opal_pci_get_phb_diag_data2(uपूर्णांक64_t phb_id, व्योम *diag_buffer,
				    uपूर्णांक64_t diag_buffer_len);
पूर्णांक64_t opal_pci_fence_phb(uपूर्णांक64_t phb_id);
पूर्णांक64_t opal_pci_reinit(uपूर्णांक64_t phb_id, uपूर्णांक64_t reinit_scope, uपूर्णांक64_t data);
पूर्णांक64_t opal_pci_mask_pe_error(uपूर्णांक64_t phb_id, uपूर्णांक16_t pe_number, uपूर्णांक8_t error_type, uपूर्णांक8_t mask_action);
पूर्णांक64_t opal_set_slot_led_status(uपूर्णांक64_t phb_id, uपूर्णांक64_t slot_id, uपूर्णांक8_t led_type, uपूर्णांक8_t led_action);
पूर्णांक64_t opal_get_eघात_status(__be16 *eघात_status, __be16 *num_eघात_classes);
पूर्णांक64_t opal_get_dpo_status(__be64 *dpo_समयout);
पूर्णांक64_t opal_set_प्रणाली_attention_led(uपूर्णांक8_t led_action);
पूर्णांक64_t opal_pci_next_error(uपूर्णांक64_t phb_id, __be64 *first_frozen_pe,
			    __be16 *pci_error_type, __be16 *severity);
पूर्णांक64_t opal_pci_poll(uपूर्णांक64_t id);
पूर्णांक64_t opal_वापस_cpu(व्योम);
पूर्णांक64_t opal_check_token(uपूर्णांक64_t token);
पूर्णांक64_t opal_reinit_cpus(uपूर्णांक64_t flags);

पूर्णांक64_t opal_xscom_पढ़ो(uपूर्णांक32_t gcid, uपूर्णांक64_t pcb_addr, __be64 *val);
पूर्णांक64_t opal_xscom_ग_लिखो(uपूर्णांक32_t gcid, uपूर्णांक64_t pcb_addr, uपूर्णांक64_t val);

पूर्णांक64_t opal_lpc_ग_लिखो(uपूर्णांक32_t chip_id, क्रमागत OpalLPCAddressType addr_type,
		       uपूर्णांक32_t addr, uपूर्णांक32_t data, uपूर्णांक32_t sz);
पूर्णांक64_t opal_lpc_पढ़ो(uपूर्णांक32_t chip_id, क्रमागत OpalLPCAddressType addr_type,
		      uपूर्णांक32_t addr, __be32 *data, uपूर्णांक32_t sz);

पूर्णांक64_t opal_पढ़ो_elog(uपूर्णांक64_t buffer, uपूर्णांक64_t size, uपूर्णांक64_t log_id);
पूर्णांक64_t opal_get_elog_size(__be64 *log_id, __be64 *size, __be64 *elog_type);
पूर्णांक64_t opal_ग_लिखो_elog(uपूर्णांक64_t buffer, uपूर्णांक64_t size, uपूर्णांक64_t offset);
पूर्णांक64_t opal_send_ack_elog(uपूर्णांक64_t log_id);
व्योम opal_resend_pending_logs(व्योम);

पूर्णांक64_t opal_validate_flash(uपूर्णांक64_t buffer, uपूर्णांक32_t *size, uपूर्णांक32_t *result);
पूर्णांक64_t opal_manage_flash(uपूर्णांक8_t op);
पूर्णांक64_t opal_update_flash(uपूर्णांक64_t blk_list);
पूर्णांक64_t opal_dump_init(uपूर्णांक8_t dump_type);
पूर्णांक64_t opal_dump_info(__be32 *dump_id, __be32 *dump_size);
पूर्णांक64_t opal_dump_info2(__be32 *dump_id, __be32 *dump_size, __be32 *dump_type);
पूर्णांक64_t opal_dump_पढ़ो(uपूर्णांक32_t dump_id, uपूर्णांक64_t buffer);
पूर्णांक64_t opal_dump_ack(uपूर्णांक32_t dump_id);
पूर्णांक64_t opal_dump_resend_notअगरication(व्योम);

पूर्णांक64_t opal_get_msg(uपूर्णांक64_t buffer, uपूर्णांक64_t size);
पूर्णांक64_t opal_ग_लिखो_oppanel_async(uपूर्णांक64_t token, oppanel_line_t *lines,
					uपूर्णांक64_t num_lines);
पूर्णांक64_t opal_check_completion(uपूर्णांक64_t buffer, uपूर्णांक64_t size, uपूर्णांक64_t token);
पूर्णांक64_t opal_sync_host_reboot(व्योम);
पूर्णांक64_t opal_get_param(uपूर्णांक64_t token, uपूर्णांक32_t param_id, uपूर्णांक64_t buffer,
		uपूर्णांक64_t length);
पूर्णांक64_t opal_set_param(uपूर्णांक64_t token, uपूर्णांक32_t param_id, uपूर्णांक64_t buffer,
		uपूर्णांक64_t length);
पूर्णांक64_t opal_sensor_पढ़ो(uपूर्णांक32_t sensor_hndl, पूर्णांक token, __be32 *sensor_data);
पूर्णांक64_t opal_sensor_पढ़ो_u64(u32 sensor_hndl, पूर्णांक token, __be64 *sensor_data);
पूर्णांक64_t opal_handle_hmi(व्योम);
पूर्णांक64_t opal_handle_hmi2(__be64 *out_flags);
पूर्णांक64_t opal_रेजिस्टर_dump_region(uपूर्णांक32_t id, uपूर्णांक64_t start, uपूर्णांक64_t end);
पूर्णांक64_t opal_unरेजिस्टर_dump_region(uपूर्णांक32_t id);
पूर्णांक64_t opal_slw_set_reg(uपूर्णांक64_t cpu_pir, uपूर्णांक64_t sprn, uपूर्णांक64_t val);
पूर्णांक64_t opal_config_cpu_idle_state(uपूर्णांक64_t state, uपूर्णांक64_t flag);
पूर्णांक64_t opal_pci_set_phb_cxl_mode(uपूर्णांक64_t phb_id, uपूर्णांक64_t mode, uपूर्णांक64_t pe_number);
पूर्णांक64_t opal_pci_get_pbcq_tunnel_bar(uपूर्णांक64_t phb_id, uपूर्णांक64_t *addr);
पूर्णांक64_t opal_pci_set_pbcq_tunnel_bar(uपूर्णांक64_t phb_id, uपूर्णांक64_t addr);
पूर्णांक64_t opal_ipmi_send(uपूर्णांक64_t पूर्णांकerface, काष्ठा opal_ipmi_msg *msg,
		uपूर्णांक64_t msg_len);
पूर्णांक64_t opal_ipmi_recv(uपूर्णांक64_t पूर्णांकerface, काष्ठा opal_ipmi_msg *msg,
		uपूर्णांक64_t *msg_len);
पूर्णांक64_t opal_i2c_request(uपूर्णांक64_t async_token, uपूर्णांक32_t bus_id,
			 काष्ठा opal_i2c_request *oreq);
पूर्णांक64_t opal_prd_msg(काष्ठा opal_prd_msg *msg);
पूर्णांक64_t opal_leds_get_ind(अक्षर *loc_code, __be64 *led_mask,
			  __be64 *led_value, __be64 *max_led_type);
पूर्णांक64_t opal_leds_set_ind(uपूर्णांक64_t token, अक्षर *loc_code, स्थिर u64 led_mask,
			  स्थिर u64 led_value, __be64 *max_led_type);

पूर्णांक64_t opal_flash_पढ़ो(uपूर्णांक64_t id, uपूर्णांक64_t offset, uपूर्णांक64_t buf,
		uपूर्णांक64_t size, uपूर्णांक64_t token);
पूर्णांक64_t opal_flash_ग_लिखो(uपूर्णांक64_t id, uपूर्णांक64_t offset, uपूर्णांक64_t buf,
		uपूर्णांक64_t size, uपूर्णांक64_t token);
पूर्णांक64_t opal_flash_erase(uपूर्णांक64_t id, uपूर्णांक64_t offset, uपूर्णांक64_t size,
		uपूर्णांक64_t token);
पूर्णांक64_t opal_get_device_tree(uपूर्णांक32_t phandle, uपूर्णांक64_t buf, uपूर्णांक64_t len);
पूर्णांक64_t opal_pci_get_presence_state(uपूर्णांक64_t id, uपूर्णांक64_t data);
पूर्णांक64_t opal_pci_get_घातer_state(uपूर्णांक64_t id, uपूर्णांक64_t data);
पूर्णांक64_t opal_pci_set_घातer_state(uपूर्णांक64_t async_token, uपूर्णांक64_t id,
				 uपूर्णांक64_t data);
पूर्णांक64_t opal_pci_poll2(uपूर्णांक64_t id, uपूर्णांक64_t data);

पूर्णांक64_t opal_पूर्णांक_get_xirr(uपूर्णांक32_t *out_xirr, bool just_poll);
पूर्णांक64_t opal_पूर्णांक_set_cppr(uपूर्णांक8_t cppr);
पूर्णांक64_t opal_पूर्णांक_eoi(uपूर्णांक32_t xirr);
पूर्णांक64_t opal_पूर्णांक_set_mfrr(uपूर्णांक32_t cpu, uपूर्णांक8_t mfrr);
पूर्णांक64_t opal_pci_tce_समाप्त(uपूर्णांक64_t phb_id, uपूर्णांक32_t समाप्त_type,
			  uपूर्णांक32_t pe_num, uपूर्णांक32_t tce_size,
			  uपूर्णांक64_t dma_addr, uपूर्णांक32_t npages);
पूर्णांक64_t opal_nmmu_set_ptcr(uपूर्णांक64_t chip_id, uपूर्णांक64_t ptcr);
पूर्णांक64_t opal_xive_reset(uपूर्णांक64_t version);
पूर्णांक64_t opal_xive_get_irq_info(uपूर्णांक32_t girq,
			       __be64 *out_flags,
			       __be64 *out_eoi_page,
			       __be64 *out_trig_page,
			       __be32 *out_esb_shअगरt,
			       __be32 *out_src_chip);
पूर्णांक64_t opal_xive_get_irq_config(uपूर्णांक32_t girq, __be64 *out_vp,
				 uपूर्णांक8_t *out_prio, __be32 *out_lirq);
पूर्णांक64_t opal_xive_set_irq_config(uपूर्णांक32_t girq, uपूर्णांक64_t vp, uपूर्णांक8_t prio,
				 uपूर्णांक32_t lirq);
पूर्णांक64_t opal_xive_get_queue_info(uपूर्णांक64_t vp, uपूर्णांक32_t prio,
				 __be64 *out_qpage,
				 __be64 *out_qsize,
				 __be64 *out_qeoi_page,
				 __be32 *out_escalate_irq,
				 __be64 *out_qflags);
पूर्णांक64_t opal_xive_set_queue_info(uपूर्णांक64_t vp, uपूर्णांक32_t prio,
				 uपूर्णांक64_t qpage,
				 uपूर्णांक64_t qsize,
				 uपूर्णांक64_t qflags);
पूर्णांक64_t opal_xive_करोnate_page(uपूर्णांक32_t chip_id, uपूर्णांक64_t addr);
पूर्णांक64_t opal_xive_alloc_vp_block(uपूर्णांक32_t alloc_order);
पूर्णांक64_t opal_xive_मुक्त_vp_block(uपूर्णांक64_t vp);
पूर्णांक64_t opal_xive_get_vp_info(uपूर्णांक64_t vp,
			      __be64 *out_flags,
			      __be64 *out_cam_value,
			      __be64 *out_report_cl_pair,
			      __be32 *out_chip_id);
पूर्णांक64_t opal_xive_set_vp_info(uपूर्णांक64_t vp,
			      uपूर्णांक64_t flags,
			      uपूर्णांक64_t report_cl_pair);
पूर्णांक64_t opal_xive_allocate_irq_raw(uपूर्णांक32_t chip_id);
पूर्णांक64_t opal_xive_मुक्त_irq(uपूर्णांक32_t girq);
पूर्णांक64_t opal_xive_sync(uपूर्णांक32_t type, uपूर्णांक32_t id);
पूर्णांक64_t opal_xive_dump(uपूर्णांक32_t type, uपूर्णांक32_t id);
पूर्णांक64_t opal_xive_get_queue_state(uपूर्णांक64_t vp, uपूर्णांक32_t prio,
				  __be32 *out_qtoggle,
				  __be32 *out_qindex);
पूर्णांक64_t opal_xive_set_queue_state(uपूर्णांक64_t vp, uपूर्णांक32_t prio,
				  uपूर्णांक32_t qtoggle,
				  uपूर्णांक32_t qindex);
पूर्णांक64_t opal_xive_get_vp_state(uपूर्णांक64_t vp, __be64 *out_w01);

पूर्णांक64_t opal_imc_counters_init(uपूर्णांक32_t type, uपूर्णांक64_t address,
							uपूर्णांक64_t cpu_pir);
पूर्णांक64_t opal_imc_counters_start(uपूर्णांक32_t type, uपूर्णांक64_t cpu_pir);
पूर्णांक64_t opal_imc_counters_stop(uपूर्णांक32_t type, uपूर्णांक64_t cpu_pir);

पूर्णांक opal_get_घातercap(u32 handle, पूर्णांक token, u32 *pcap);
पूर्णांक opal_set_घातercap(u32 handle, पूर्णांक token, u32 pcap);
पूर्णांक opal_get_घातer_shअगरt_ratio(u32 handle, पूर्णांक token, u32 *psr);
पूर्णांक opal_set_घातer_shअगरt_ratio(u32 handle, पूर्णांक token, u32 psr);
पूर्णांक opal_sensor_group_clear(u32 group_hndl, पूर्णांक token);
पूर्णांक opal_sensor_group_enable(u32 group_hndl, पूर्णांक token, bool enable);
पूर्णांक opal_nx_coproc_init(uपूर्णांक32_t chip_id, uपूर्णांक32_t ct);

पूर्णांक opal_secvar_get(स्थिर अक्षर *key, uपूर्णांक64_t key_len, u8 *data,
		    uपूर्णांक64_t *data_size);
पूर्णांक opal_secvar_get_next(स्थिर अक्षर *key, uपूर्णांक64_t *key_len,
			 uपूर्णांक64_t key_buf_size);
पूर्णांक opal_secvar_enqueue_update(स्थिर अक्षर *key, uपूर्णांक64_t key_len, u8 *data,
			       uपूर्णांक64_t data_size);

s64 opal_mpipl_update(क्रमागत opal_mpipl_ops op, u64 src, u64 dest, u64 size);
s64 opal_mpipl_रेजिस्टर_tag(क्रमागत opal_mpipl_tags tag, u64 addr);
s64 opal_mpipl_query_tag(क्रमागत opal_mpipl_tags tag, __be64 *addr);

s64 opal_संकेत_प्रणाली_reset(s32 cpu);
s64 opal_quiesce(u64 shutकरोwn_type, s32 cpu);

/* Internal functions */
बाह्य पूर्णांक early_init_dt_scan_opal(अचिन्हित दीर्घ node, स्थिर अक्षर *uname,
				   पूर्णांक depth, व्योम *data);
बाह्य पूर्णांक early_init_dt_scan_recoverable_ranges(अचिन्हित दीर्घ node,
				 स्थिर अक्षर *uname, पूर्णांक depth, व्योम *data);
बाह्य व्योम opal_configure_cores(व्योम);

बाह्य पूर्णांक opal_get_अक्षरs(uपूर्णांक32_t vtermno, अक्षर *buf, पूर्णांक count);
बाह्य पूर्णांक opal_put_अक्षरs(uपूर्णांक32_t vtermno, स्थिर अक्षर *buf, पूर्णांक total_len);
बाह्य पूर्णांक opal_put_अक्षरs_atomic(uपूर्णांक32_t vtermno, स्थिर अक्षर *buf, पूर्णांक total_len);
बाह्य पूर्णांक opal_flush_अक्षरs(uपूर्णांक32_t vtermno, bool रुको);
बाह्य पूर्णांक opal_flush_console(uपूर्णांक32_t vtermno);

बाह्य व्योम hvc_opal_init_early(व्योम);

बाह्य पूर्णांक opal_notअगरier_रेजिस्टर(काष्ठा notअगरier_block *nb);
बाह्य पूर्णांक opal_notअगरier_unरेजिस्टर(काष्ठा notअगरier_block *nb);

बाह्य पूर्णांक opal_message_notअगरier_रेजिस्टर(क्रमागत opal_msg_type msg_type,
						काष्ठा notअगरier_block *nb);
बाह्य पूर्णांक opal_message_notअगरier_unरेजिस्टर(क्रमागत opal_msg_type msg_type,
					    काष्ठा notअगरier_block *nb);
बाह्य व्योम opal_notअगरier_enable(व्योम);
बाह्य व्योम opal_notअगरier_disable(व्योम);
बाह्य व्योम opal_notअगरier_update_evt(uपूर्णांक64_t evt_mask, uपूर्णांक64_t evt_val);

बाह्य पूर्णांक opal_async_get_token_पूर्णांकerruptible(व्योम);
बाह्य पूर्णांक opal_async_release_token(पूर्णांक token);
बाह्य पूर्णांक opal_async_रुको_response(uपूर्णांक64_t token, काष्ठा opal_msg *msg);
बाह्य पूर्णांक opal_async_रुको_response_पूर्णांकerruptible(uपूर्णांक64_t token,
		काष्ठा opal_msg *msg);
बाह्य पूर्णांक opal_get_sensor_data(u32 sensor_hndl, u32 *sensor_data);
बाह्य पूर्णांक opal_get_sensor_data_u64(u32 sensor_hndl, u64 *sensor_data);
बाह्य पूर्णांक sensor_group_enable(u32 grp_hndl, bool enable);

काष्ठा rtc_समय;
बाह्य समय64_t opal_get_boot_समय(व्योम);
बाह्य व्योम opal_nvram_init(व्योम);
बाह्य व्योम opal_flash_update_init(व्योम);
बाह्य व्योम opal_flash_update_prपूर्णांक_message(व्योम);
बाह्य पूर्णांक opal_elog_init(व्योम);
बाह्य व्योम opal_platक्रमm_dump_init(व्योम);
बाह्य व्योम opal_sys_param_init(व्योम);
बाह्य व्योम opal_msglog_init(व्योम);
बाह्य व्योम opal_msglog_sysfs_init(व्योम);
बाह्य पूर्णांक opal_async_comp_init(व्योम);
बाह्य पूर्णांक opal_sensor_init(व्योम);
बाह्य पूर्णांक opal_hmi_handler_init(व्योम);
बाह्य पूर्णांक opal_event_init(व्योम);
पूर्णांक opal_घातer_control_init(व्योम);

बाह्य पूर्णांक opal_machine_check(काष्ठा pt_regs *regs);
बाह्य bool opal_mce_check_early_recovery(काष्ठा pt_regs *regs);
बाह्य पूर्णांक opal_hmi_exception_early(काष्ठा pt_regs *regs);
बाह्य पूर्णांक opal_hmi_exception_early2(काष्ठा pt_regs *regs);
बाह्य पूर्णांक opal_handle_hmi_exception(काष्ठा pt_regs *regs);

बाह्य व्योम opal_shutकरोwn(व्योम);
बाह्य पूर्णांक opal_resync_समयbase(व्योम);

बाह्य व्योम opal_lpc_init(व्योम);

बाह्य व्योम opal_kmsg_init(व्योम);

बाह्य पूर्णांक opal_event_request(अचिन्हित पूर्णांक opal_event_nr);

काष्ठा opal_sg_list *opal_vदो_स्मृति_to_sg_list(व्योम *vदो_स्मृति_addr,
					     अचिन्हित दीर्घ vदो_स्मृति_size);
व्योम opal_मुक्त_sg_list(काष्ठा opal_sg_list *sg);

बाह्य पूर्णांक opal_error_code(पूर्णांक rc);

sमाप_प्रकार opal_msglog_copy(अक्षर *to, loff_t pos, माप_प्रकार count);

अटल अंतरभूत पूर्णांक opal_get_async_rc(काष्ठा opal_msg msg)
अणु
	अगर (msg.msg_type != OPAL_MSG_ASYNC_COMP)
		वापस OPAL_PARAMETER;
	अन्यथा
		वापस be64_to_cpu(msg.params[1]);
पूर्ण

व्योम opal_wake_poller(व्योम);

व्योम opal_घातercap_init(व्योम);
व्योम opal_psr_init(व्योम);
व्योम opal_sensor_groups_init(व्योम);

#पूर्ण_अगर /* __ASSEMBLY__ */

#पूर्ण_अगर /* _ASM_POWERPC_OPAL_H */
