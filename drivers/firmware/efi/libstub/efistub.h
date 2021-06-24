<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

#अगर_अघोषित _DRIVERS_FIRMWARE_EFI_EFISTUB_H
#घोषणा _DRIVERS_FIRMWARE_EFI_EFISTUB_H

#समावेश <linux/compiler.h>
#समावेश <linux/efi.h>
#समावेश <linux/kernel.h>
#समावेश <linux/kern_levels.h>
#समावेश <linux/types.h>
#समावेश <यंत्र/efi.h>

/*
 * __init annotations should not be used in the EFI stub, since the code is
 * either included in the decompressor (x86, ARM) where they have no effect,
 * or the whole stub is __init annotated at the section level (arm64), by
 * renaming the sections, in which हाल the __init annotation will be
 * redundant, and will result in section names like .init.init.text, and our
 * linker script करोes not expect that.
 */
#अघोषित __init

/*
 * Allow the platक्रमm to override the allocation granularity: this allows
 * प्रणालीs that have the capability to run with a larger page size to deal
 * with the allocations क्रम initrd and fdt more efficiently.
 */
#अगर_अघोषित EFI_ALLOC_ALIGN
#घोषणा EFI_ALLOC_ALIGN		EFI_PAGE_SIZE
#पूर्ण_अगर

बाह्य bool efi_nochunk;
बाह्य bool efi_nokaslr;
बाह्य bool efi_noinitrd;
बाह्य पूर्णांक efi_loglevel;
बाह्य bool efi_novamap;

बाह्य स्थिर efi_प्रणाली_table_t *efi_प्रणाली_table;

efi_status_t __efiapi efi_pe_entry(efi_handle_t handle,
				   efi_प्रणाली_table_t *sys_table_arg);

#अगर_अघोषित ARCH_HAS_EFISTUB_WRAPPERS

#घोषणा efi_is_native()		(true)
#घोषणा efi_bs_call(func, ...)	efi_प्रणाली_table->bootसमय->func(__VA_ARGS__)
#घोषणा efi_rt_call(func, ...)	efi_प्रणाली_table->runसमय->func(__VA_ARGS__)
#घोषणा efi_table_attr(inst, attr)	(inst->attr)
#घोषणा efi_call_proto(inst, func, ...) inst->func(inst, ##__VA_ARGS__)

#पूर्ण_अगर

#घोषणा efi_info(fmt, ...) \
	efi_prपूर्णांकk(KERN_INFO fmt, ##__VA_ARGS__)
#घोषणा efi_warn(fmt, ...) \
	efi_prपूर्णांकk(KERN_WARNING "WARNING: " fmt, ##__VA_ARGS__)
#घोषणा efi_err(fmt, ...) \
	efi_prपूर्णांकk(KERN_ERR "ERROR: " fmt, ##__VA_ARGS__)
#घोषणा efi_debug(fmt, ...) \
	efi_prपूर्णांकk(KERN_DEBUG "DEBUG: " fmt, ##__VA_ARGS__)

#घोषणा efi_prपूर्णांकk_once(fmt, ...) 		\
(अणु						\
	अटल bool __prपूर्णांक_once;		\
	bool __ret_prपूर्णांक_once = !__prपूर्णांक_once;	\
						\
	अगर (!__prपूर्णांक_once) अणु			\
		__prपूर्णांक_once = true;		\
		efi_prपूर्णांकk(fmt, ##__VA_ARGS__);	\
	पूर्ण					\
	__ret_prपूर्णांक_once;			\
पूर्ण)

#घोषणा efi_info_once(fmt, ...) \
	efi_prपूर्णांकk_once(KERN_INFO fmt, ##__VA_ARGS__)
#घोषणा efi_warn_once(fmt, ...) \
	efi_prपूर्णांकk_once(KERN_WARNING "WARNING: " fmt, ##__VA_ARGS__)
#घोषणा efi_err_once(fmt, ...) \
	efi_prपूर्णांकk_once(KERN_ERR "ERROR: " fmt, ##__VA_ARGS__)
#घोषणा efi_debug_once(fmt, ...) \
	efi_prपूर्णांकk_once(KERN_DEBUG "DEBUG: " fmt, ##__VA_ARGS__)

/* Helper macros क्रम the usual हाल of using simple C variables: */
#अगर_अघोषित fdt_setprop_inplace_var
#घोषणा fdt_setprop_inplace_var(fdt, node_offset, name, var) \
	fdt_setprop_inplace((fdt), (node_offset), (name), &(var), माप(var))
#पूर्ण_अगर

#अगर_अघोषित fdt_setprop_var
#घोषणा fdt_setprop_var(fdt, node_offset, name, var) \
	fdt_setprop((fdt), (node_offset), (name), &(var), माप(var))
#पूर्ण_अगर

#घोषणा get_efi_var(name, venकरोr, ...)				\
	efi_rt_call(get_variable, (efi_अक्षर16_t *)(name),	\
		    (efi_guid_t *)(venकरोr), __VA_ARGS__)

#घोषणा set_efi_var(name, venकरोr, ...)				\
	efi_rt_call(set_variable, (efi_अक्षर16_t *)(name),	\
		    (efi_guid_t *)(venकरोr), __VA_ARGS__)

#घोषणा efi_get_handle_at(array, idx)					\
	(efi_is_native() ? (array)[idx] 				\
		: (efi_handle_t)(अचिन्हित दीर्घ)((u32 *)(array))[idx])

#घोषणा efi_get_handle_num(size)					\
	((size) / (efi_is_native() ? माप(efi_handle_t) : माप(u32)))

#घोषणा क्रम_each_efi_handle(handle, array, size, i)			\
	क्रम (i = 0;							\
	     i < efi_get_handle_num(size) &&				\
		((handle = efi_get_handle_at((array), i)) || true);	\
	     i++)

अटल अंतरभूत
व्योम efi_set_u64_split(u64 data, u32 *lo, u32 *hi)
अणु
	*lo = lower_32_bits(data);
	*hi = upper_32_bits(data);
पूर्ण

/*
 * Allocation types क्रम calls to bootसमय->allocate_pages.
 */
#घोषणा EFI_ALLOCATE_ANY_PAGES		0
#घोषणा EFI_ALLOCATE_MAX_ADDRESS	1
#घोषणा EFI_ALLOCATE_ADDRESS		2
#घोषणा EFI_MAX_ALLOCATE_TYPE		3

/*
 * The type of search to perक्रमm when calling bootसमय->locate_handle
 */
#घोषणा EFI_LOCATE_ALL_HANDLES			0
#घोषणा EFI_LOCATE_BY_REGISTER_NOTIFY		1
#घोषणा EFI_LOCATE_BY_PROTOCOL			2

/*
 * bootसमय->stall takes the समय period in microseconds
 */
#घोषणा EFI_USEC_PER_SEC		1000000

/*
 * bootसमय->set_समयr takes the समय in 100ns units
 */
#घोषणा EFI_100NSEC_PER_USEC	((u64)10)

/*
 * An efi_boot_memmap is used by efi_get_memory_map() to वापस the
 * EFI memory map in a dynamically allocated buffer.
 *
 * The buffer allocated क्रम the EFI memory map includes extra room क्रम
 * a minimum of EFI_MMAP_NR_SLACK_SLOTS additional EFI memory descriptors.
 * This facilitates the reuse of the EFI memory map buffer when a second
 * call to ExitBootServices() is needed because of पूर्णांकervening changes to
 * the EFI memory map. Other related काष्ठाures, e.g. x86 e820ext, need
 * to factor in this headroom requirement as well.
 */
#घोषणा EFI_MMAP_NR_SLACK_SLOTS	8

काष्ठा efi_boot_memmap अणु
	efi_memory_desc_t	**map;
	अचिन्हित दीर्घ		*map_size;
	अचिन्हित दीर्घ		*desc_size;
	u32			*desc_ver;
	अचिन्हित दीर्घ		*key_ptr;
	अचिन्हित दीर्घ		*buff_size;
पूर्ण;

प्रकार काष्ठा efi_generic_dev_path efi_device_path_protocol_t;

प्रकार व्योम *efi_event_t;
/* Note that notअगरications won't work in mixed mode */
प्रकार व्योम (__efiapi *efi_event_notअगरy_t)(efi_event_t, व्योम *);

#घोषणा EFI_EVT_TIMER		0x80000000U
#घोषणा EFI_EVT_RUNTIME		0x40000000U
#घोषणा EFI_EVT_NOTIFY_WAIT	0x00000100U
#घोषणा EFI_EVT_NOTIFY_SIGNAL	0x00000200U

/**
 * efi_set_event_at() - add event to events array
 *
 * @events:	array of UEFI events
 * @ids:	index where to put the event in the array
 * @event:	event to add to the aray
 *
 * bootसमय->रुको_क्रम_event() takes an array of events as input.
 * Provide a helper to set it up correctly क्रम mixed mode.
 */
अटल अंतरभूत
व्योम efi_set_event_at(efi_event_t *events, माप_प्रकार idx, efi_event_t event)
अणु
	अगर (efi_is_native())
		events[idx] = event;
	अन्यथा
		((u32 *)events)[idx] = (u32)(अचिन्हित दीर्घ)event;
पूर्ण

#घोषणा EFI_TPL_APPLICATION	4
#घोषणा EFI_TPL_CALLBACK	8
#घोषणा EFI_TPL_NOTIFY		16
#घोषणा EFI_TPL_HIGH_LEVEL	31

प्रकार क्रमागत अणु
	EfiTimerCancel,
	EfiTimerPeriodic,
	EfiTimerRelative
पूर्ण EFI_TIMER_DELAY;

/*
 * EFI Boot Services table
 */
जोड़ efi_boot_services अणु
	काष्ठा अणु
		efi_table_hdr_t hdr;
		व्योम *उठाओ_tpl;
		व्योम *restore_tpl;
		efi_status_t (__efiapi *allocate_pages)(पूर्णांक, पूर्णांक, अचिन्हित दीर्घ,
							efi_physical_addr_t *);
		efi_status_t (__efiapi *मुक्त_pages)(efi_physical_addr_t,
						    अचिन्हित दीर्घ);
		efi_status_t (__efiapi *get_memory_map)(अचिन्हित दीर्घ *, व्योम *,
							अचिन्हित दीर्घ *,
							अचिन्हित दीर्घ *, u32 *);
		efi_status_t (__efiapi *allocate_pool)(पूर्णांक, अचिन्हित दीर्घ,
						       व्योम **);
		efi_status_t (__efiapi *मुक्त_pool)(व्योम *);
		efi_status_t (__efiapi *create_event)(u32, अचिन्हित दीर्घ,
						      efi_event_notअगरy_t, व्योम *,
						      efi_event_t *);
		efi_status_t (__efiapi *set_समयr)(efi_event_t,
						  EFI_TIMER_DELAY, u64);
		efi_status_t (__efiapi *रुको_क्रम_event)(अचिन्हित दीर्घ,
							efi_event_t *,
							अचिन्हित दीर्घ *);
		व्योम *संकेत_event;
		efi_status_t (__efiapi *बंद_event)(efi_event_t);
		व्योम *check_event;
		व्योम *install_protocol_पूर्णांकerface;
		व्योम *reinstall_protocol_पूर्णांकerface;
		व्योम *uninstall_protocol_पूर्णांकerface;
		efi_status_t (__efiapi *handle_protocol)(efi_handle_t,
							 efi_guid_t *, व्योम **);
		व्योम *__reserved;
		व्योम *रेजिस्टर_protocol_notअगरy;
		efi_status_t (__efiapi *locate_handle)(पूर्णांक, efi_guid_t *,
						       व्योम *, अचिन्हित दीर्घ *,
						       efi_handle_t *);
		efi_status_t (__efiapi *locate_device_path)(efi_guid_t *,
							    efi_device_path_protocol_t **,
							    efi_handle_t *);
		efi_status_t (__efiapi *install_configuration_table)(efi_guid_t *,
								     व्योम *);
		व्योम *load_image;
		व्योम *start_image;
		efi_status_t __noवापस (__efiapi *निकास)(efi_handle_t,
							 efi_status_t,
							 अचिन्हित दीर्घ,
							 efi_अक्षर16_t *);
		व्योम *unload_image;
		efi_status_t (__efiapi *निकास_boot_services)(efi_handle_t,
							    अचिन्हित दीर्घ);
		व्योम *get_next_monotonic_count;
		efi_status_t (__efiapi *stall)(अचिन्हित दीर्घ);
		व्योम *set_watchकरोg_समयr;
		व्योम *connect_controller;
		efi_status_t (__efiapi *disconnect_controller)(efi_handle_t,
							       efi_handle_t,
							       efi_handle_t);
		व्योम *खोलो_protocol;
		व्योम *बंद_protocol;
		व्योम *खोलो_protocol_inक्रमmation;
		व्योम *protocols_per_handle;
		व्योम *locate_handle_buffer;
		efi_status_t (__efiapi *locate_protocol)(efi_guid_t *, व्योम *,
							 व्योम **);
		व्योम *install_multiple_protocol_पूर्णांकerfaces;
		व्योम *uninstall_multiple_protocol_पूर्णांकerfaces;
		व्योम *calculate_crc32;
		व्योम *copy_mem;
		व्योम *set_mem;
		व्योम *create_event_ex;
	पूर्ण;
	काष्ठा अणु
		efi_table_hdr_t hdr;
		u32 उठाओ_tpl;
		u32 restore_tpl;
		u32 allocate_pages;
		u32 मुक्त_pages;
		u32 get_memory_map;
		u32 allocate_pool;
		u32 मुक्त_pool;
		u32 create_event;
		u32 set_समयr;
		u32 रुको_क्रम_event;
		u32 संकेत_event;
		u32 बंद_event;
		u32 check_event;
		u32 install_protocol_पूर्णांकerface;
		u32 reinstall_protocol_पूर्णांकerface;
		u32 uninstall_protocol_पूर्णांकerface;
		u32 handle_protocol;
		u32 __reserved;
		u32 रेजिस्टर_protocol_notअगरy;
		u32 locate_handle;
		u32 locate_device_path;
		u32 install_configuration_table;
		u32 load_image;
		u32 start_image;
		u32 निकास;
		u32 unload_image;
		u32 निकास_boot_services;
		u32 get_next_monotonic_count;
		u32 stall;
		u32 set_watchकरोg_समयr;
		u32 connect_controller;
		u32 disconnect_controller;
		u32 खोलो_protocol;
		u32 बंद_protocol;
		u32 खोलो_protocol_inक्रमmation;
		u32 protocols_per_handle;
		u32 locate_handle_buffer;
		u32 locate_protocol;
		u32 install_multiple_protocol_पूर्णांकerfaces;
		u32 uninstall_multiple_protocol_पूर्णांकerfaces;
		u32 calculate_crc32;
		u32 copy_mem;
		u32 set_mem;
		u32 create_event_ex;
	पूर्ण mixed_mode;
पूर्ण;

प्रकार जोड़ efi_uga_draw_protocol efi_uga_draw_protocol_t;

जोड़ efi_uga_draw_protocol अणु
	काष्ठा अणु
		efi_status_t (__efiapi *get_mode)(efi_uga_draw_protocol_t *,
						  u32*, u32*, u32*, u32*);
		व्योम *set_mode;
		व्योम *blt;
	पूर्ण;
	काष्ठा अणु
		u32 get_mode;
		u32 set_mode;
		u32 blt;
	पूर्ण mixed_mode;
पूर्ण;

प्रकार काष्ठा अणु
	u16 scan_code;
	efi_अक्षर16_t unicode_अक्षर;
पूर्ण efi_input_key_t;

जोड़ efi_simple_text_input_protocol अणु
	काष्ठा अणु
		व्योम *reset;
		efi_status_t (__efiapi *पढ़ो_keystroke)(efi_simple_text_input_protocol_t *,
							efi_input_key_t *);
		efi_event_t रुको_क्रम_key;
	पूर्ण;
	काष्ठा अणु
		u32 reset;
		u32 पढ़ो_keystroke;
		u32 रुको_क्रम_key;
	पूर्ण mixed_mode;
पूर्ण;

efi_status_t efi_रुको_क्रम_key(अचिन्हित दीर्घ usec, efi_input_key_t *key);

जोड़ efi_simple_text_output_protocol अणु
	काष्ठा अणु
		व्योम *reset;
		efi_status_t (__efiapi *output_string)(efi_simple_text_output_protocol_t *,
						       efi_अक्षर16_t *);
		व्योम *test_string;
	पूर्ण;
	काष्ठा अणु
		u32 reset;
		u32 output_string;
		u32 test_string;
	पूर्ण mixed_mode;
पूर्ण;

#घोषणा PIXEL_RGB_RESERVED_8BIT_PER_COLOR		0
#घोषणा PIXEL_BGR_RESERVED_8BIT_PER_COLOR		1
#घोषणा PIXEL_BIT_MASK					2
#घोषणा PIXEL_BLT_ONLY					3
#घोषणा PIXEL_FORMAT_MAX				4

प्रकार काष्ठा अणु
	u32 red_mask;
	u32 green_mask;
	u32 blue_mask;
	u32 reserved_mask;
पूर्ण efi_pixel_biपंचांगask_t;

प्रकार काष्ठा अणु
	u32 version;
	u32 horizontal_resolution;
	u32 vertical_resolution;
	पूर्णांक pixel_क्रमmat;
	efi_pixel_biपंचांगask_t pixel_inक्रमmation;
	u32 pixels_per_scan_line;
पूर्ण efi_graphics_output_mode_info_t;

प्रकार जोड़ efi_graphics_output_protocol_mode efi_graphics_output_protocol_mode_t;

जोड़ efi_graphics_output_protocol_mode अणु
	काष्ठा अणु
		u32 max_mode;
		u32 mode;
		efi_graphics_output_mode_info_t *info;
		अचिन्हित दीर्घ size_of_info;
		efi_physical_addr_t frame_buffer_base;
		अचिन्हित दीर्घ frame_buffer_size;
	पूर्ण;
	काष्ठा अणु
		u32 max_mode;
		u32 mode;
		u32 info;
		u32 size_of_info;
		u64 frame_buffer_base;
		u32 frame_buffer_size;
	पूर्ण mixed_mode;
पूर्ण;

प्रकार जोड़ efi_graphics_output_protocol efi_graphics_output_protocol_t;

जोड़ efi_graphics_output_protocol अणु
	काष्ठा अणु
		efi_status_t (__efiapi *query_mode)(efi_graphics_output_protocol_t *,
						    u32, अचिन्हित दीर्घ *,
						    efi_graphics_output_mode_info_t **);
		efi_status_t (__efiapi *set_mode)  (efi_graphics_output_protocol_t *, u32);
		व्योम *blt;
		efi_graphics_output_protocol_mode_t *mode;
	पूर्ण;
	काष्ठा अणु
		u32 query_mode;
		u32 set_mode;
		u32 blt;
		u32 mode;
	पूर्ण mixed_mode;
पूर्ण;

प्रकार जोड़ अणु
	काष्ठा अणु
		u32			revision;
		efi_handle_t		parent_handle;
		efi_प्रणाली_table_t	*प्रणाली_table;
		efi_handle_t		device_handle;
		व्योम			*file_path;
		व्योम			*reserved;
		u32			load_options_size;
		व्योम			*load_options;
		व्योम			*image_base;
		__aligned_u64		image_size;
		अचिन्हित पूर्णांक		image_code_type;
		अचिन्हित पूर्णांक		image_data_type;
		efi_status_t		(__efiapi *unload)(efi_handle_t image_handle);
	पूर्ण;
	काष्ठा अणु
		u32		revision;
		u32		parent_handle;
		u32		प्रणाली_table;
		u32		device_handle;
		u32		file_path;
		u32		reserved;
		u32		load_options_size;
		u32		load_options;
		u32		image_base;
		__aligned_u64	image_size;
		u32		image_code_type;
		u32		image_data_type;
		u32		unload;
	पूर्ण mixed_mode;
पूर्ण efi_loaded_image_t;

प्रकार काष्ठा अणु
	u64			size;
	u64			file_size;
	u64			phys_size;
	efi_समय_प्रकार		create_समय;
	efi_समय_प्रकार		last_access_समय;
	efi_समय_प्रकार		modअगरication_समय;
	__aligned_u64		attribute;
	efi_अक्षर16_t		filename[];
पूर्ण efi_file_info_t;

प्रकार काष्ठा efi_file_protocol efi_file_protocol_t;

काष्ठा efi_file_protocol अणु
	u64		revision;
	efi_status_t	(__efiapi *खोलो)	(efi_file_protocol_t *,
						 efi_file_protocol_t **,
						 efi_अक्षर16_t *, u64, u64);
	efi_status_t	(__efiapi *बंद)	(efi_file_protocol_t *);
	efi_status_t	(__efiapi *delete)	(efi_file_protocol_t *);
	efi_status_t	(__efiapi *पढ़ो)	(efi_file_protocol_t *,
						 अचिन्हित दीर्घ *, व्योम *);
	efi_status_t	(__efiapi *ग_लिखो)	(efi_file_protocol_t *,
						 अचिन्हित दीर्घ, व्योम *);
	efi_status_t	(__efiapi *get_position)(efi_file_protocol_t *, u64 *);
	efi_status_t	(__efiapi *set_position)(efi_file_protocol_t *, u64);
	efi_status_t	(__efiapi *get_info)	(efi_file_protocol_t *,
						 efi_guid_t *, अचिन्हित दीर्घ *,
						 व्योम *);
	efi_status_t	(__efiapi *set_info)	(efi_file_protocol_t *,
						 efi_guid_t *, अचिन्हित दीर्घ,
						 व्योम *);
	efi_status_t	(__efiapi *flush)	(efi_file_protocol_t *);
पूर्ण;

प्रकार काष्ठा efi_simple_file_प्रणाली_protocol efi_simple_file_प्रणाली_protocol_t;

काष्ठा efi_simple_file_प्रणाली_protocol अणु
	u64	revision;
	पूर्णांक	(__efiapi *खोलो_volume)(efi_simple_file_प्रणाली_protocol_t *,
					efi_file_protocol_t **);
पूर्ण;

#घोषणा EFI_खाता_MODE_READ	0x0000000000000001
#घोषणा EFI_खाता_MODE_WRITE	0x0000000000000002
#घोषणा EFI_खाता_MODE_CREATE	0x8000000000000000

प्रकार क्रमागत अणु
	EfiPciIoWidthUपूर्णांक8,
	EfiPciIoWidthUपूर्णांक16,
	EfiPciIoWidthUपूर्णांक32,
	EfiPciIoWidthUपूर्णांक64,
	EfiPciIoWidthFअगरoUपूर्णांक8,
	EfiPciIoWidthFअगरoUपूर्णांक16,
	EfiPciIoWidthFअगरoUपूर्णांक32,
	EfiPciIoWidthFअगरoUपूर्णांक64,
	EfiPciIoWidthFillUपूर्णांक8,
	EfiPciIoWidthFillUपूर्णांक16,
	EfiPciIoWidthFillUपूर्णांक32,
	EfiPciIoWidthFillUपूर्णांक64,
	EfiPciIoWidthMaximum
पूर्ण EFI_PCI_IO_PROTOCOL_WIDTH;

प्रकार क्रमागत अणु
	EfiPciIoAttributeOperationGet,
	EfiPciIoAttributeOperationSet,
	EfiPciIoAttributeOperationEnable,
	EfiPciIoAttributeOperationDisable,
	EfiPciIoAttributeOperationSupported,
    EfiPciIoAttributeOperationMaximum
पूर्ण EFI_PCI_IO_PROTOCOL_ATTRIBUTE_OPERATION;

प्रकार काष्ठा अणु
	u32 पढ़ो;
	u32 ग_लिखो;
पूर्ण efi_pci_io_protocol_access_32_t;

प्रकार जोड़ efi_pci_io_protocol efi_pci_io_protocol_t;

प्रकार
efi_status_t (__efiapi *efi_pci_io_protocol_cfg_t)(efi_pci_io_protocol_t *,
						   EFI_PCI_IO_PROTOCOL_WIDTH,
						   u32 offset,
						   अचिन्हित दीर्घ count,
						   व्योम *buffer);

प्रकार काष्ठा अणु
	व्योम *पढ़ो;
	व्योम *ग_लिखो;
पूर्ण efi_pci_io_protocol_access_t;

प्रकार काष्ठा अणु
	efi_pci_io_protocol_cfg_t पढ़ो;
	efi_pci_io_protocol_cfg_t ग_लिखो;
पूर्ण efi_pci_io_protocol_config_access_t;

जोड़ efi_pci_io_protocol अणु
	काष्ठा अणु
		व्योम *poll_mem;
		व्योम *poll_io;
		efi_pci_io_protocol_access_t mem;
		efi_pci_io_protocol_access_t io;
		efi_pci_io_protocol_config_access_t pci;
		व्योम *copy_mem;
		व्योम *map;
		व्योम *unmap;
		व्योम *allocate_buffer;
		व्योम *मुक्त_buffer;
		व्योम *flush;
		efi_status_t (__efiapi *get_location)(efi_pci_io_protocol_t *,
						      अचिन्हित दीर्घ *segment_nr,
						      अचिन्हित दीर्घ *bus_nr,
						      अचिन्हित दीर्घ *device_nr,
						      अचिन्हित दीर्घ *func_nr);
		व्योम *attributes;
		व्योम *get_bar_attributes;
		व्योम *set_bar_attributes;
		uपूर्णांक64_t romsize;
		व्योम *romimage;
	पूर्ण;
	काष्ठा अणु
		u32 poll_mem;
		u32 poll_io;
		efi_pci_io_protocol_access_32_t mem;
		efi_pci_io_protocol_access_32_t io;
		efi_pci_io_protocol_access_32_t pci;
		u32 copy_mem;
		u32 map;
		u32 unmap;
		u32 allocate_buffer;
		u32 मुक्त_buffer;
		u32 flush;
		u32 get_location;
		u32 attributes;
		u32 get_bar_attributes;
		u32 set_bar_attributes;
		u64 romsize;
		u32 romimage;
	पूर्ण mixed_mode;
पूर्ण;

#घोषणा EFI_PCI_IO_ATTRIBUTE_ISA_MOTHERBOARD_IO 0x0001
#घोषणा EFI_PCI_IO_ATTRIBUTE_ISA_IO 0x0002
#घोषणा EFI_PCI_IO_ATTRIBUTE_VGA_PALETTE_IO 0x0004
#घोषणा EFI_PCI_IO_ATTRIBUTE_VGA_MEMORY 0x0008
#घोषणा EFI_PCI_IO_ATTRIBUTE_VGA_IO 0x0010
#घोषणा EFI_PCI_IO_ATTRIBUTE_IDE_PRIMARY_IO 0x0020
#घोषणा EFI_PCI_IO_ATTRIBUTE_IDE_SECONDARY_IO 0x0040
#घोषणा EFI_PCI_IO_ATTRIBUTE_MEMORY_WRITE_COMBINE 0x0080
#घोषणा EFI_PCI_IO_ATTRIBUTE_IO 0x0100
#घोषणा EFI_PCI_IO_ATTRIBUTE_MEMORY 0x0200
#घोषणा EFI_PCI_IO_ATTRIBUTE_BUS_MASTER 0x0400
#घोषणा EFI_PCI_IO_ATTRIBUTE_MEMORY_CACHED 0x0800
#घोषणा EFI_PCI_IO_ATTRIBUTE_MEMORY_DISABLE 0x1000
#घोषणा EFI_PCI_IO_ATTRIBUTE_EMBEDDED_DEVICE 0x2000
#घोषणा EFI_PCI_IO_ATTRIBUTE_EMBEDDED_ROM 0x4000
#घोषणा EFI_PCI_IO_ATTRIBUTE_DUAL_ADDRESS_CYCLE 0x8000
#घोषणा EFI_PCI_IO_ATTRIBUTE_ISA_IO_16 0x10000
#घोषणा EFI_PCI_IO_ATTRIBUTE_VGA_PALETTE_IO_16 0x20000
#घोषणा EFI_PCI_IO_ATTRIBUTE_VGA_IO_16 0x40000

काष्ठा efi_dev_path;

प्रकार जोड़ apple_properties_protocol apple_properties_protocol_t;

जोड़ apple_properties_protocol अणु
	काष्ठा अणु
		अचिन्हित दीर्घ version;
		efi_status_t (__efiapi *get)(apple_properties_protocol_t *,
					     काष्ठा efi_dev_path *,
					     efi_अक्षर16_t *, व्योम *, u32 *);
		efi_status_t (__efiapi *set)(apple_properties_protocol_t *,
					     काष्ठा efi_dev_path *,
					     efi_अक्षर16_t *, व्योम *, u32);
		efi_status_t (__efiapi *del)(apple_properties_protocol_t *,
					     काष्ठा efi_dev_path *,
					     efi_अक्षर16_t *);
		efi_status_t (__efiapi *get_all)(apple_properties_protocol_t *,
						 व्योम *buffer, u32 *);
	पूर्ण;
	काष्ठा अणु
		u32 version;
		u32 get;
		u32 set;
		u32 del;
		u32 get_all;
	पूर्ण mixed_mode;
पूर्ण;

प्रकार u32 efi_tcg2_event_log_क्रमmat;

प्रकार जोड़ efi_tcg2_protocol efi_tcg2_protocol_t;

जोड़ efi_tcg2_protocol अणु
	काष्ठा अणु
		व्योम *get_capability;
		efi_status_t (__efiapi *get_event_log)(efi_tcg2_protocol_t *,
						       efi_tcg2_event_log_क्रमmat,
						       efi_physical_addr_t *,
						       efi_physical_addr_t *,
						       efi_bool_t *);
		व्योम *hash_log_extend_event;
		व्योम *submit_command;
		व्योम *get_active_pcr_banks;
		व्योम *set_active_pcr_banks;
		व्योम *get_result_of_set_active_pcr_banks;
	पूर्ण;
	काष्ठा अणु
		u32 get_capability;
		u32 get_event_log;
		u32 hash_log_extend_event;
		u32 submit_command;
		u32 get_active_pcr_banks;
		u32 set_active_pcr_banks;
		u32 get_result_of_set_active_pcr_banks;
	पूर्ण mixed_mode;
पूर्ण;

प्रकार जोड़ efi_load_file_protocol efi_load_file_protocol_t;
प्रकार जोड़ efi_load_file_protocol efi_load_file2_protocol_t;

जोड़ efi_load_file_protocol अणु
	काष्ठा अणु
		efi_status_t (__efiapi *load_file)(efi_load_file_protocol_t *,
						   efi_device_path_protocol_t *,
						   bool, अचिन्हित दीर्घ *, व्योम *);
	पूर्ण;
	काष्ठा अणु
		u32 load_file;
	पूर्ण mixed_mode;
पूर्ण;

प्रकार काष्ठा अणु
	u32 attributes;
	u16 file_path_list_length;
	u8 variable_data[];
	// efi_अक्षर16_t description[];
	// efi_device_path_protocol_t file_path_list[];
	// u8 optional_data[];
पूर्ण __packed efi_load_option_t;

#घोषणा EFI_LOAD_OPTION_ACTIVE		0x0001U
#घोषणा EFI_LOAD_OPTION_FORCE_RECONNECT	0x0002U
#घोषणा EFI_LOAD_OPTION_HIDDEN		0x0008U
#घोषणा EFI_LOAD_OPTION_CATEGORY	0x1f00U
#घोषणा   EFI_LOAD_OPTION_CATEGORY_BOOT	0x0000U
#घोषणा   EFI_LOAD_OPTION_CATEGORY_APP	0x0100U

#घोषणा EFI_LOAD_OPTION_BOOT_MASK \
	(EFI_LOAD_OPTION_ACTIVE|EFI_LOAD_OPTION_HIDDEN|EFI_LOAD_OPTION_CATEGORY)
#घोषणा EFI_LOAD_OPTION_MASK (EFI_LOAD_OPTION_FORCE_RECONNECT|EFI_LOAD_OPTION_BOOT_MASK)

प्रकार काष्ठा अणु
	u32 attributes;
	u16 file_path_list_length;
	स्थिर efi_अक्षर16_t *description;
	स्थिर efi_device_path_protocol_t *file_path_list;
	माप_प्रकार optional_data_size;
	स्थिर व्योम *optional_data;
पूर्ण efi_load_option_unpacked_t;

व्योम efi_pci_disable_bridge_busmaster(व्योम);

प्रकार efi_status_t (*efi_निकास_boot_map_processing)(
	काष्ठा efi_boot_memmap *map,
	व्योम *priv);

efi_status_t efi_निकास_boot_services(व्योम *handle,
				    काष्ठा efi_boot_memmap *map,
				    व्योम *priv,
				    efi_निकास_boot_map_processing priv_func);

efi_status_t allocate_new_fdt_and_निकास_boot(व्योम *handle,
					    अचिन्हित दीर्घ *new_fdt_addr,
					    u64 initrd_addr, u64 initrd_size,
					    अक्षर *cmdline_ptr,
					    अचिन्हित दीर्घ fdt_addr,
					    अचिन्हित दीर्घ fdt_size);

व्योम *get_fdt(अचिन्हित दीर्घ *fdt_size);

व्योम efi_get_virपंचांगap(efi_memory_desc_t *memory_map, अचिन्हित दीर्घ map_size,
		     अचिन्हित दीर्घ desc_size, efi_memory_desc_t *runसमय_map,
		     पूर्णांक *count);

efi_status_t efi_get_अक्रमom_bytes(अचिन्हित दीर्घ size, u8 *out);

efi_status_t efi_अक्रमom_alloc(अचिन्हित दीर्घ size, अचिन्हित दीर्घ align,
			      अचिन्हित दीर्घ *addr, अचिन्हित दीर्घ अक्रमom_seed);

efi_status_t check_platक्रमm_features(व्योम);

व्योम *get_efi_config_table(efi_guid_t guid);

/* NOTE: These functions करो not prपूर्णांक a trailing newline after the string */
व्योम efi_अक्षर16_माला_दो(efi_अक्षर16_t *);
व्योम efi_माला_दो(स्थिर अक्षर *str);

__म_लिखो(1, 2) पूर्णांक efi_prपूर्णांकk(अक्षर स्थिर *fmt, ...);

व्योम efi_मुक्त(अचिन्हित दीर्घ size, अचिन्हित दीर्घ addr);

व्योम efi_apply_loaकरोptions_quirk(स्थिर व्योम **load_options, पूर्णांक *load_options_size);

अक्षर *efi_convert_cmdline(efi_loaded_image_t *image, पूर्णांक *cmd_line_len);

efi_status_t efi_get_memory_map(काष्ठा efi_boot_memmap *map);

efi_status_t efi_allocate_pages(अचिन्हित दीर्घ size, अचिन्हित दीर्घ *addr,
				अचिन्हित दीर्घ max);

efi_status_t efi_allocate_pages_aligned(अचिन्हित दीर्घ size, अचिन्हित दीर्घ *addr,
					अचिन्हित दीर्घ max, अचिन्हित दीर्घ align);

efi_status_t efi_low_alloc_above(अचिन्हित दीर्घ size, अचिन्हित दीर्घ align,
				 अचिन्हित दीर्घ *addr, अचिन्हित दीर्घ min);

efi_status_t efi_relocate_kernel(अचिन्हित दीर्घ *image_addr,
				 अचिन्हित दीर्घ image_size,
				 अचिन्हित दीर्घ alloc_size,
				 अचिन्हित दीर्घ preferred_addr,
				 अचिन्हित दीर्घ alignment,
				 अचिन्हित दीर्घ min_addr);

efi_status_t efi_parse_options(अक्षर स्थिर *cmdline);

व्योम efi_parse_option_graphics(अक्षर *option);

efi_status_t efi_setup_gop(काष्ठा screen_info *si, efi_guid_t *proto,
			   अचिन्हित दीर्घ size);

efi_status_t handle_cmdline_files(efi_loaded_image_t *image,
				  स्थिर efi_अक्षर16_t *optstr,
				  पूर्णांक optstr_size,
				  अचिन्हित दीर्घ soft_limit,
				  अचिन्हित दीर्घ hard_limit,
				  अचिन्हित दीर्घ *load_addr,
				  अचिन्हित दीर्घ *load_size);


अटल अंतरभूत efi_status_t efi_load_dtb(efi_loaded_image_t *image,
					अचिन्हित दीर्घ *load_addr,
					अचिन्हित दीर्घ *load_size)
अणु
	वापस handle_cmdline_files(image, L"dtb=", माप(L"dtb=") - 2,
				    अच_दीर्घ_उच्च, अच_दीर्घ_उच्च, load_addr, load_size);
पूर्ण

efi_status_t efi_load_initrd(efi_loaded_image_t *image,
			     अचिन्हित दीर्घ *load_addr,
			     अचिन्हित दीर्घ *load_size,
			     अचिन्हित दीर्घ soft_limit,
			     अचिन्हित दीर्घ hard_limit);
/*
 * This function handles the architcture specअगरic dअगरferences between arm and
 * arm64 regarding where the kernel image must be loaded and any memory that
 * must be reserved. On failure it is required to मुक्त all
 * all allocations it has made.
 */
efi_status_t handle_kernel_image(अचिन्हित दीर्घ *image_addr,
				 अचिन्हित दीर्घ *image_size,
				 अचिन्हित दीर्घ *reserve_addr,
				 अचिन्हित दीर्घ *reserve_size,
				 efi_loaded_image_t *image);

यंत्रlinkage व्योम __noवापस efi_enter_kernel(अचिन्हित दीर्घ entrypoपूर्णांक,
					    अचिन्हित दीर्घ fdt_addr,
					    अचिन्हित दीर्घ fdt_size);

व्योम efi_handle_post_ebs_state(व्योम);

क्रमागत efi_secureboot_mode efi_get_secureboot(व्योम);

#अगर_घोषित CONFIG_RESET_ATTACK_MITIGATION
व्योम efi_enable_reset_attack_mitigation(व्योम);
#अन्यथा
अटल अंतरभूत व्योम
efi_enable_reset_attack_mitigation(व्योम) अणु पूर्ण
#पूर्ण_अगर

व्योम efi_retrieve_tpm2_eventlog(व्योम);

#पूर्ण_अगर
