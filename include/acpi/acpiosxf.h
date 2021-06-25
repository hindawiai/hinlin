<शैली गुरु>
/* SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0 */
/******************************************************************************
 *
 * Name: acpiosxf.h - All पूर्णांकerfaces to the OS Services Layer (OSL). These
 *                    पूर्णांकerfaces must be implemented by OSL to पूर्णांकerface the
 *                    ACPI components to the host operating प्रणाली.
 *
 * Copyright (C) 2000 - 2021, Intel Corp.
 *
 *****************************************************************************/

#अगर_अघोषित __ACPIOSXF_H__
#घोषणा __ACPIOSXF_H__

#समावेश <acpi/platक्रमm/acenv.h>
#समावेश <acpi/actypes.h>

/* Types क्रम acpi_os_execute */

प्रकार क्रमागत अणु
	OSL_GLOBAL_LOCK_HANDLER,
	OSL_NOTIFY_HANDLER,
	OSL_GPE_HANDLER,
	OSL_DEBUGGER_MAIN_THREAD,
	OSL_DEBUGGER_EXEC_THREAD,
	OSL_EC_POLL_HANDLER,
	OSL_EC_BURST_HANDLER
पूर्ण acpi_execute_type;

#घोषणा ACPI_NO_UNIT_LIMIT          ((u32) -1)
#घोषणा ACPI_MUTEX_SEM              1

/* Functions क्रम acpi_os_संकेत */

#घोषणा ACPI_SIGNAL_FATAL           0
#घोषणा ACPI_SIGNAL_BREAKPOINT      1

काष्ठा acpi_संकेत_fatal_info अणु
	u32 type;
	u32 code;
	u32 argument;
पूर्ण;

/*
 * OSL Initialization and shutकरोwn primitives
 */
#अगर_अघोषित ACPI_USE_ALTERNATE_PROTOTYPE_acpi_os_initialize
acpi_status acpi_os_initialize(व्योम);
#पूर्ण_अगर

#अगर_अघोषित ACPI_USE_ALTERNATE_PROTOTYPE_acpi_os_terminate
acpi_status acpi_os_terminate(व्योम);
#पूर्ण_अगर

/*
 * ACPI Table पूर्णांकerfaces
 */
#अगर_अघोषित ACPI_USE_ALTERNATE_PROTOTYPE_acpi_os_get_root_poपूर्णांकer
acpi_physical_address acpi_os_get_root_poपूर्णांकer(व्योम);
#पूर्ण_अगर

#अगर_अघोषित ACPI_USE_ALTERNATE_PROTOTYPE_acpi_os_predefined_override
acpi_status
acpi_os_predefined_override(स्थिर काष्ठा acpi_predefined_names *init_val,
			    acpi_string *new_val);
#पूर्ण_अगर

#अगर_अघोषित ACPI_USE_ALTERNATE_PROTOTYPE_acpi_os_table_override
acpi_status
acpi_os_table_override(काष्ठा acpi_table_header *existing_table,
		       काष्ठा acpi_table_header **new_table);
#पूर्ण_अगर

#अगर_अघोषित ACPI_USE_ALTERNATE_PROTOTYPE_acpi_os_physical_table_override
acpi_status
acpi_os_physical_table_override(काष्ठा acpi_table_header *existing_table,
				acpi_physical_address *new_address,
				u32 *new_table_length);
#पूर्ण_अगर

/*
 * Spinlock primitives
 */
#अगर_अघोषित ACPI_USE_ALTERNATE_PROTOTYPE_acpi_os_create_lock
acpi_status acpi_os_create_lock(acpi_spinlock * out_handle);
#पूर्ण_अगर

#अगर_अघोषित ACPI_USE_ALTERNATE_PROTOTYPE_acpi_os_delete_lock
व्योम acpi_os_delete_lock(acpi_spinlock handle);
#पूर्ण_अगर

#अगर_अघोषित ACPI_USE_ALTERNATE_PROTOTYPE_acpi_os_acquire_lock
acpi_cpu_flags acpi_os_acquire_lock(acpi_spinlock handle);
#पूर्ण_अगर

#अगर_अघोषित ACPI_USE_ALTERNATE_PROTOTYPE_acpi_os_release_lock
व्योम acpi_os_release_lock(acpi_spinlock handle, acpi_cpu_flags flags);
#पूर्ण_अगर

/*
 * RAW spinlock primitives. If the OS करोes not provide them, fallback to
 * spinlock primitives
 */
#अगर_अघोषित ACPI_USE_ALTERNATE_PROTOTYPE_acpi_os_create_raw_lock
# define acpi_os_create_raw_lock(out_handle)	acpi_os_create_lock(out_handle)
#पूर्ण_अगर

#अगर_अघोषित ACPI_USE_ALTERNATE_PROTOTYPE_acpi_os_delete_raw_lock
# define acpi_os_delete_raw_lock(handle)	acpi_os_delete_lock(handle)
#पूर्ण_अगर

#अगर_अघोषित ACPI_USE_ALTERNATE_PROTOTYPE_acpi_os_acquire_raw_lock
# define acpi_os_acquire_raw_lock(handle)	acpi_os_acquire_lock(handle)
#पूर्ण_अगर

#अगर_अघोषित ACPI_USE_ALTERNATE_PROTOTYPE_acpi_os_release_raw_lock
# define acpi_os_release_raw_lock(handle, flags)	\
	acpi_os_release_lock(handle, flags)
#पूर्ण_अगर

/*
 * Semaphore primitives
 */
#अगर_अघोषित ACPI_USE_ALTERNATE_PROTOTYPE_acpi_os_create_semaphore
acpi_status
acpi_os_create_semaphore(u32 max_units,
			 u32 initial_units, acpi_semaphore * out_handle);
#पूर्ण_अगर

#अगर_अघोषित ACPI_USE_ALTERNATE_PROTOTYPE_acpi_os_delete_semaphore
acpi_status acpi_os_delete_semaphore(acpi_semaphore handle);
#पूर्ण_अगर

#अगर_अघोषित ACPI_USE_ALTERNATE_PROTOTYPE_acpi_os_रुको_semaphore
acpi_status
acpi_os_रुको_semaphore(acpi_semaphore handle, u32 units, u16 समयout);
#पूर्ण_अगर

#अगर_अघोषित ACPI_USE_ALTERNATE_PROTOTYPE_acpi_os_संकेत_semaphore
acpi_status acpi_os_संकेत_semaphore(acpi_semaphore handle, u32 units);
#पूर्ण_अगर

/*
 * Mutex primitives. May be configured to use semaphores instead via
 * ACPI_MUTEX_TYPE (see platक्रमm/acenv.h)
 */
#अगर (ACPI_MUTEX_TYPE != ACPI_BINARY_SEMAPHORE)

#अगर_अघोषित ACPI_USE_ALTERNATE_PROTOTYPE_acpi_os_create_mutex
acpi_status acpi_os_create_mutex(acpi_mutex * out_handle);
#पूर्ण_अगर

#अगर_अघोषित ACPI_USE_ALTERNATE_PROTOTYPE_acpi_os_delete_mutex
व्योम acpi_os_delete_mutex(acpi_mutex handle);
#पूर्ण_अगर

#अगर_अघोषित ACPI_USE_ALTERNATE_PROTOTYPE_acpi_os_acquire_mutex
acpi_status acpi_os_acquire_mutex(acpi_mutex handle, u16 समयout);
#पूर्ण_अगर

#अगर_अघोषित ACPI_USE_ALTERNATE_PROTOTYPE_acpi_os_release_mutex
व्योम acpi_os_release_mutex(acpi_mutex handle);
#पूर्ण_अगर

#पूर्ण_अगर

/*
 * Memory allocation and mapping
 */
#अगर_अघोषित ACPI_USE_ALTERNATE_PROTOTYPE_acpi_os_allocate
व्योम *acpi_os_allocate(acpi_size size);
#पूर्ण_अगर

#अगर_अघोषित ACPI_USE_ALTERNATE_PROTOTYPE_acpi_os_allocate_zeroed
व्योम *acpi_os_allocate_zeroed(acpi_size size);
#पूर्ण_अगर

#अगर_अघोषित ACPI_USE_ALTERNATE_PROTOTYPE_acpi_os_मुक्त
व्योम acpi_os_मुक्त(व्योम *memory);
#पूर्ण_अगर

#अगर_अघोषित ACPI_USE_ALTERNATE_PROTOTYPE_acpi_os_map_memory
व्योम *acpi_os_map_memory(acpi_physical_address where, acpi_size length);
#पूर्ण_अगर

#अगर_अघोषित ACPI_USE_ALTERNATE_PROTOTYPE_acpi_os_unmap_memory
व्योम acpi_os_unmap_memory(व्योम *logical_address, acpi_size size);
#पूर्ण_अगर

#अगर_अघोषित ACPI_USE_ALTERNATE_PROTOTYPE_acpi_os_get_physical_address
acpi_status
acpi_os_get_physical_address(व्योम *logical_address,
			     acpi_physical_address *physical_address);
#पूर्ण_अगर

/*
 * Memory/Object Cache
 */
#अगर_अघोषित ACPI_USE_ALTERNATE_PROTOTYPE_acpi_os_create_cache
acpi_status
acpi_os_create_cache(अक्षर *cache_name,
		     u16 object_size,
		     u16 max_depth, acpi_cache_t ** वापस_cache);
#पूर्ण_अगर

#अगर_अघोषित ACPI_USE_ALTERNATE_PROTOTYPE_acpi_os_delete_cache
acpi_status acpi_os_delete_cache(acpi_cache_t * cache);
#पूर्ण_अगर

#अगर_अघोषित ACPI_USE_ALTERNATE_PROTOTYPE_acpi_os_purge_cache
acpi_status acpi_os_purge_cache(acpi_cache_t * cache);
#पूर्ण_अगर

#अगर_अघोषित ACPI_USE_ALTERNATE_PROTOTYPE_acpi_os_acquire_object
व्योम *acpi_os_acquire_object(acpi_cache_t * cache);
#पूर्ण_अगर

#अगर_अघोषित ACPI_USE_ALTERNATE_PROTOTYPE_acpi_os_release_object
acpi_status acpi_os_release_object(acpi_cache_t * cache, व्योम *object);
#पूर्ण_अगर

/*
 * Interrupt handlers
 */
#अगर_अघोषित ACPI_USE_ALTERNATE_PROTOTYPE_acpi_os_install_पूर्णांकerrupt_handler
acpi_status
acpi_os_install_पूर्णांकerrupt_handler(u32 पूर्णांकerrupt_number,
				  acpi_osd_handler service_routine,
				  व्योम *context);
#पूर्ण_अगर

#अगर_अघोषित ACPI_USE_ALTERNATE_PROTOTYPE_acpi_os_हटाओ_पूर्णांकerrupt_handler
acpi_status
acpi_os_हटाओ_पूर्णांकerrupt_handler(u32 पूर्णांकerrupt_number,
				 acpi_osd_handler service_routine);
#पूर्ण_अगर

/*
 * Thपढ़ोs and Scheduling
 */
#अगर_अघोषित ACPI_USE_ALTERNATE_PROTOTYPE_acpi_os_get_thपढ़ो_id
acpi_thपढ़ो_id acpi_os_get_thपढ़ो_id(व्योम);
#पूर्ण_अगर

#अगर_अघोषित ACPI_USE_ALTERNATE_PROTOTYPE_acpi_os_execute
acpi_status
acpi_os_execute(acpi_execute_type type,
		acpi_osd_exec_callback function, व्योम *context);
#पूर्ण_अगर

#अगर_अघोषित ACPI_USE_ALTERNATE_PROTOTYPE_acpi_os_रुको_events_complete
व्योम acpi_os_रुको_events_complete(व्योम);
#पूर्ण_अगर

#अगर_अघोषित ACPI_USE_ALTERNATE_PROTOTYPE_acpi_os_sleep
व्योम acpi_os_sleep(u64 milliseconds);
#पूर्ण_अगर

#अगर_अघोषित ACPI_USE_ALTERNATE_PROTOTYPE_acpi_os_stall
व्योम acpi_os_stall(u32 microseconds);
#पूर्ण_अगर

/*
 * Platक्रमm and hardware-independent I/O पूर्णांकerfaces
 */
#अगर_अघोषित ACPI_USE_ALTERNATE_PROTOTYPE_acpi_os_पढ़ो_port
acpi_status acpi_os_पढ़ो_port(acpi_io_address address, u32 *value, u32 width);
#पूर्ण_अगर

#अगर_अघोषित ACPI_USE_ALTERNATE_PROTOTYPE_acpi_os_ग_लिखो_port
acpi_status acpi_os_ग_लिखो_port(acpi_io_address address, u32 value, u32 width);
#पूर्ण_अगर

/*
 * Platक्रमm and hardware-independent physical memory पूर्णांकerfaces
 */
पूर्णांक acpi_os_पढ़ो_iomem(व्योम __iomem *virt_addr, u64 *value, u32 width);

#अगर_अघोषित ACPI_USE_ALTERNATE_PROTOTYPE_acpi_os_पढ़ो_memory
acpi_status
acpi_os_पढ़ो_memory(acpi_physical_address address, u64 *value, u32 width);
#पूर्ण_अगर

#अगर_अघोषित ACPI_USE_ALTERNATE_PROTOTYPE_acpi_os_ग_लिखो_memory
acpi_status
acpi_os_ग_लिखो_memory(acpi_physical_address address, u64 value, u32 width);
#पूर्ण_अगर

/*
 * Platक्रमm and hardware-independent PCI configuration space access
 * Note: Can't use "Register" as a parameter, changed to "Reg" --
 * certain compilers complain.
 */
#अगर_अघोषित ACPI_USE_ALTERNATE_PROTOTYPE_acpi_os_पढ़ो_pci_configuration
acpi_status
acpi_os_पढ़ो_pci_configuration(काष्ठा acpi_pci_id *pci_id,
			       u32 reg, u64 *value, u32 width);
#पूर्ण_अगर

#अगर_अघोषित ACPI_USE_ALTERNATE_PROTOTYPE_acpi_os_ग_लिखो_pci_configuration
acpi_status
acpi_os_ग_लिखो_pci_configuration(काष्ठा acpi_pci_id *pci_id,
				u32 reg, u64 value, u32 width);
#पूर्ण_अगर

/*
 * Miscellaneous
 */
#अगर_अघोषित ACPI_USE_ALTERNATE_PROTOTYPE_acpi_os_पढ़ोable
u8 acpi_os_पढ़ोable(व्योम *poपूर्णांकer, acpi_size length);
#पूर्ण_अगर

#अगर_अघोषित ACPI_USE_ALTERNATE_PROTOTYPE_acpi_os_writable
u8 acpi_os_writable(व्योम *poपूर्णांकer, acpi_size length);
#पूर्ण_अगर

#अगर_अघोषित ACPI_USE_ALTERNATE_PROTOTYPE_acpi_os_get_समयr
u64 acpi_os_get_समयr(व्योम);
#पूर्ण_अगर

#अगर_अघोषित ACPI_USE_ALTERNATE_PROTOTYPE_acpi_os_संकेत
acpi_status acpi_os_संकेत(u32 function, व्योम *info);
#पूर्ण_अगर

#अगर_अघोषित ACPI_USE_ALTERNATE_PROTOTYPE_acpi_os_enter_sleep
acpi_status acpi_os_enter_sleep(u8 sleep_state, u32 rega_value, u32 regb_value);
#पूर्ण_अगर

/*
 * Debug prपूर्णांक routines
 */
#अगर_अघोषित ACPI_USE_ALTERNATE_PROTOTYPE_acpi_os_म_लिखो
ACPI_PRINTF_LIKE(1)
व्योम ACPI_INTERNAL_VAR_XFACE acpi_os_म_लिखो(स्थिर अक्षर *क्रमmat, ...);
#पूर्ण_अगर

#अगर_अघोषित ACPI_USE_ALTERNATE_PROTOTYPE_acpi_os_भ_लिखो
व्योम acpi_os_भ_लिखो(स्थिर अक्षर *क्रमmat, बहु_सूची args);
#पूर्ण_अगर

#अगर_अघोषित ACPI_USE_ALTERNATE_PROTOTYPE_acpi_os_redirect_output
व्योम acpi_os_redirect_output(व्योम *destination);
#पूर्ण_अगर

/*
 * Debug IO
 */
#अगर_अघोषित ACPI_USE_ALTERNATE_PROTOTYPE_acpi_os_get_line
acpi_status acpi_os_get_line(अक्षर *buffer, u32 buffer_length, u32 *bytes_पढ़ो);
#पूर्ण_अगर

#अगर_अघोषित ACPI_USE_ALTERNATE_PROTOTYPE_acpi_os_initialize_debugger
acpi_status acpi_os_initialize_debugger(व्योम);
#पूर्ण_अगर

#अगर_अघोषित ACPI_USE_ALTERNATE_PROTOTYPE_acpi_os_terminate_debugger
व्योम acpi_os_terminate_debugger(व्योम);
#पूर्ण_अगर

#अगर_अघोषित ACPI_USE_ALTERNATE_PROTOTYPE_acpi_os_रुको_command_पढ़ोy
acpi_status acpi_os_रुको_command_पढ़ोy(व्योम);
#पूर्ण_अगर

#अगर_अघोषित ACPI_USE_ALTERNATE_PROTOTYPE_acpi_os_notअगरy_command_complete
acpi_status acpi_os_notअगरy_command_complete(व्योम);
#पूर्ण_अगर

#अगर_अघोषित ACPI_USE_ALTERNATE_PROTOTYPE_acpi_os_trace_poपूर्णांक
व्योम
acpi_os_trace_poपूर्णांक(acpi_trace_event_type type,
		    u8 begin, u8 *aml, अक्षर *pathname);
#पूर्ण_अगर

/*
 * Obtain ACPI table(s)
 */
#अगर_अघोषित ACPI_USE_ALTERNATE_PROTOTYPE_acpi_os_get_table_by_name
acpi_status
acpi_os_get_table_by_name(अक्षर *signature,
			  u32 instance,
			  काष्ठा acpi_table_header **table,
			  acpi_physical_address *address);
#पूर्ण_अगर

#अगर_अघोषित ACPI_USE_ALTERNATE_PROTOTYPE_acpi_os_get_table_by_index
acpi_status
acpi_os_get_table_by_index(u32 index,
			   काष्ठा acpi_table_header **table,
			   u32 *instance, acpi_physical_address *address);
#पूर्ण_अगर

#अगर_अघोषित ACPI_USE_ALTERNATE_PROTOTYPE_acpi_os_get_table_by_address
acpi_status
acpi_os_get_table_by_address(acpi_physical_address address,
			     काष्ठा acpi_table_header **table);
#पूर्ण_अगर

/*
 * Directory manipulation
 */
#अगर_अघोषित ACPI_USE_ALTERNATE_PROTOTYPE_acpi_os_खोलो_directory
व्योम *acpi_os_खोलो_directory(अक्षर *pathname,
			     अक्षर *wildcard_spec, अक्षर requested_file_type);
#पूर्ण_अगर

/* requeste_file_type values */

#घोषणा REQUEST_खाता_ONLY                   0
#घोषणा REQUEST_सूची_ONLY                    1

#अगर_अघोषित ACPI_USE_ALTERNATE_PROTOTYPE_acpi_os_get_next_filename
अक्षर *acpi_os_get_next_filename(व्योम *dir_handle);
#पूर्ण_अगर

#अगर_अघोषित ACPI_USE_ALTERNATE_PROTOTYPE_acpi_os_बंद_directory
व्योम acpi_os_बंद_directory(व्योम *dir_handle);
#पूर्ण_अगर

#पूर्ण_अगर				/* __ACPIOSXF_H__ */
