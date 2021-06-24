<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _PARISC_PDC_H
#घोषणा _PARISC_PDC_H

#समावेश <uapi/यंत्र/pdc.h>

#अगर !defined(__ASSEMBLY__)

बाह्य पूर्णांक parisc_narrow_firmware;

बाह्य पूर्णांक pdc_type;
बाह्य अचिन्हित दीर्घ parisc_cell_num; /* cell number the CPU runs on (PAT) */
बाह्य अचिन्हित दीर्घ parisc_cell_loc; /* cell location of CPU (PAT)	   */
बाह्य अचिन्हित दीर्घ parisc_pat_pdc_cap; /* PDC capabilities (PAT) */

/* Values क्रम pdc_type */
#घोषणा PDC_TYPE_ILLEGAL	-1
#घोषणा PDC_TYPE_PAT		 0 /* 64-bit PAT-PDC */
#घोषणा PDC_TYPE_SYSTEM_MAP	 1 /* 32-bit, but supports PDC_SYSTEM_MAP */
#घोषणा PDC_TYPE_SNAKE		 2 /* Doesn't support SYSTEM_MAP */

व्योम pdc_console_init(व्योम);	/* in pdc_console.c */
व्योम pdc_console_restart(व्योम);

व्योम setup_pdc(व्योम);		/* in inventory.c */

/* wrapper-functions from pdc.c */

पूर्णांक pdc_add_valid(अचिन्हित दीर्घ address);
पूर्णांक pdc_instr(अचिन्हित पूर्णांक *instr);
पूर्णांक pdc_chassis_info(काष्ठा pdc_chassis_info *chassis_info, व्योम *led_info, अचिन्हित दीर्घ len);
पूर्णांक pdc_chassis_disp(अचिन्हित दीर्घ disp);
पूर्णांक pdc_chassis_warn(अचिन्हित दीर्घ *warn);
पूर्णांक pdc_coproc_cfg(काष्ठा pdc_coproc_cfg *pdc_coproc_info);
पूर्णांक pdc_coproc_cfg_unlocked(काष्ठा pdc_coproc_cfg *pdc_coproc_info);
पूर्णांक pdc_iodc_पढ़ो(अचिन्हित दीर्घ *actcnt, अचिन्हित दीर्घ hpa, अचिन्हित पूर्णांक index,
		  व्योम *iodc_data, अचिन्हित पूर्णांक iodc_data_size);
पूर्णांक pdc_प्रणाली_map_find_mods(काष्ठा pdc_प्रणाली_map_mod_info *pdc_mod_info,
			     काष्ठा pdc_module_path *mod_path, दीर्घ mod_index);
पूर्णांक pdc_प्रणाली_map_find_addrs(काष्ठा pdc_प्रणाली_map_addr_info *pdc_addr_info,
			      दीर्घ mod_index, दीर्घ addr_index);
पूर्णांक pdc_model_info(काष्ठा pdc_model *model);
पूर्णांक pdc_model_sysmodel(अक्षर *name);
पूर्णांक pdc_model_cpuid(अचिन्हित दीर्घ *cpu_id);
पूर्णांक pdc_model_versions(अचिन्हित दीर्घ *versions, पूर्णांक id);
पूर्णांक pdc_model_capabilities(अचिन्हित दीर्घ *capabilities);
पूर्णांक pdc_model_platक्रमm_info(अक्षर *orig_prod_num, अक्षर *current_prod_num, अक्षर *serial_no);
पूर्णांक pdc_cache_info(काष्ठा pdc_cache_info *cache);
पूर्णांक pdc_spaceid_bits(अचिन्हित दीर्घ *space_bits);
#अगर_अघोषित CONFIG_PA20
पूर्णांक pdc_btlb_info(काष्ठा pdc_btlb_info *btlb);
पूर्णांक pdc_mem_map_hpa(काष्ठा pdc_memory_map *r_addr, काष्ठा pdc_module_path *mod_path);
#पूर्ण_अगर /* !CONFIG_PA20 */
पूर्णांक pdc_lan_station_id(अक्षर *lan_addr, अचिन्हित दीर्घ net_hpa);

पूर्णांक pdc_stable_पढ़ो(अचिन्हित दीर्घ staddr, व्योम *memaddr, अचिन्हित दीर्घ count);
पूर्णांक pdc_stable_ग_लिखो(अचिन्हित दीर्घ staddr, व्योम *memaddr, अचिन्हित दीर्घ count);
पूर्णांक pdc_stable_get_size(अचिन्हित दीर्घ *size);
पूर्णांक pdc_stable_verअगरy_contents(व्योम);
पूर्णांक pdc_stable_initialize(व्योम);

पूर्णांक pdc_pci_irt_size(अचिन्हित दीर्घ *num_entries, अचिन्हित दीर्घ hpa);
पूर्णांक pdc_pci_irt(अचिन्हित दीर्घ num_entries, अचिन्हित दीर्घ hpa, व्योम *tbl);

पूर्णांक pdc_get_initiator(काष्ठा hardware_path *, काष्ठा pdc_initiator *);
पूर्णांक pdc_tod_पढ़ो(काष्ठा pdc_tod *tod);
पूर्णांक pdc_tod_set(अचिन्हित दीर्घ sec, अचिन्हित दीर्घ usec);

व्योम pdc_pdt_init(व्योम);	/* in pdt.c */
पूर्णांक pdc_mem_pdt_info(काष्ठा pdc_mem_retinfo *rinfo);
पूर्णांक pdc_mem_pdt_पढ़ो_entries(काष्ठा pdc_mem_पढ़ो_pdt *rpdt_पढ़ो,
		अचिन्हित दीर्घ *pdt_entries_ptr);
#अगर_घोषित CONFIG_64BIT
पूर्णांक pdc_mem_mem_table(काष्ठा pdc_memory_table_raddr *r_addr,
		काष्ठा pdc_memory_table *tbl, अचिन्हित दीर्घ entries);
#पूर्ण_अगर

व्योम set_firmware_width(व्योम);
व्योम set_firmware_width_unlocked(व्योम);
पूर्णांक pdc_करो_firm_test_reset(अचिन्हित दीर्घ ftc_biपंचांगap);
पूर्णांक pdc_करो_reset(व्योम);
पूर्णांक pdc_soft_घातer_info(अचिन्हित दीर्घ *घातer_reg);
पूर्णांक pdc_soft_घातer_button(पूर्णांक sw_control);
व्योम pdc_io_reset(व्योम);
व्योम pdc_io_reset_devices(व्योम);
पूर्णांक pdc_iodc_अ_लो(व्योम);
पूर्णांक pdc_iodc_prपूर्णांक(स्थिर अचिन्हित अक्षर *str, अचिन्हित count);

व्योम pdc_emergency_unlock(व्योम);
पूर्णांक pdc_sti_call(अचिन्हित दीर्घ func, अचिन्हित दीर्घ flags,
                 अचिन्हित दीर्घ inptr, अचिन्हित दीर्घ outputr,
                 अचिन्हित दीर्घ glob_cfg);

पूर्णांक __pdc_cpu_rendezvous(व्योम);
अटल अंतरभूत अक्षर * os_id_to_string(u16 os_id) अणु
	चयन(os_id) अणु
	हाल OS_ID_NONE:	वापस "No OS";
	हाल OS_ID_HPUX:	वापस "HP-UX";
	हाल OS_ID_MPEXL:	वापस "MPE-iX";
	हाल OS_ID_OSF:		वापस "OSF";
	हाल OS_ID_HPRT:	वापस "HP-RT";
	हाल OS_ID_NOVEL:	वापस "Novell Netware";
	हाल OS_ID_LINUX:	वापस "Linux";
	शेष:	वापस "Unknown";
	पूर्ण
पूर्ण

#पूर्ण_अगर /* !defined(__ASSEMBLY__) */
#पूर्ण_अगर /* _PARISC_PDC_H */
