<शैली गुरु>
/* SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0 */
/******************************************************************************
 *
 * Name: actypes.h - Common data types क्रम the entire ACPI subप्रणाली
 *
 * Copyright (C) 2000 - 2021, Intel Corp.
 *
 *****************************************************************************/

#अगर_अघोषित __ACTYPES_H__
#घोषणा __ACTYPES_H__

/* acpisrc:काष्ठा_defs -- क्रम acpisrc conversion */

/*
 * ACPI_MACHINE_WIDTH must be specअगरied in an OS- or compiler-dependent
 * header and must be either 32 or 64. 16-bit ACPICA is no दीर्घer
 * supported, as of 12/2006.
 */
#अगर_अघोषित ACPI_MACHINE_WIDTH
#त्रुटि ACPI_MACHINE_WIDTH not defined
#पूर्ण_अगर

/*
 * Data type ranges
 * Note: These macros are deचिन्हित to be compiler independent as well as
 * working around problems that some 32-bit compilers have with 64-bit
 * स्थिरants.
 */
#घोषणा ACPI_UINT8_MAX                  (u8) (~((u8)  0))	/* 0xFF               */
#घोषणा ACPI_UINT16_MAX                 (u16)(~((u16) 0))	/* 0xFFFF             */
#घोषणा ACPI_UINT32_MAX                 (u32)(~((u32) 0))	/* 0xFFFFFFFF         */
#घोषणा ACPI_UINT64_MAX                 (u64)(~((u64) 0))	/* 0xFFFFFFFFFFFFFFFF */
#घोषणा ACPI_ASCII_MAX                  0x7F

/*
 * Architecture-specअगरic ACPICA Subप्रणाली Data Types
 *
 * The goal of these types is to provide source code portability across
 * 16-bit, 32-bit, and 64-bit tarमाला_लो.
 *
 * 1) The following types are of fixed size क्रम all tarमाला_लो (16/32/64):
 *
 * u8           Logical boolean
 *
 * u8           8-bit  (1 byte) अचिन्हित value
 * u16          16-bit (2 byte) अचिन्हित value
 * u32          32-bit (4 byte) अचिन्हित value
 * u64          64-bit (8 byte) अचिन्हित value
 *
 * s16          16-bit (2 byte) चिन्हित value
 * s32          32-bit (4 byte) चिन्हित value
 * s64          64-bit (8 byte) चिन्हित value
 *
 * COMPILER_DEPENDENT_UINT64/s64 - These types are defined in the
 * compiler-dependent header(s) and were पूर्णांकroduced because there is no
 * common 64-bit पूर्णांकeger type across the various compilation models, as
 * shown in the table below.
 *
 * Datatype  LP64 ILP64 LLP64 ILP32 LP32 16bit
 * अक्षर      8    8     8     8     8    8
 * लघु     16   16    16    16    16   16
 * _पूर्णांक32         32
 * पूर्णांक       32   64    32    32    16   16
 * दीर्घ      64   64    32    32    32   32
 * दीर्घ दीर्घ            64    64
 * poपूर्णांकer   64   64    64    32    32   32
 *
 * Note: ILP64 and LP32 are currently not supported.
 *
 *
 * 2) These types represent the native word size of the target mode of the
 * processor, and may be 16-bit, 32-bit, or 64-bit as required. They are
 * usually used क्रम memory allocation, efficient loop counters, and array
 * indexes. The types are similar to the माप_प्रकार type in the C library and
 * are required because there is no C type that consistently represents the
 * native data width. acpi_size is needed because there is no guarantee
 * that a kernel-level C library is present.
 *
 * acpi_size        16/32/64-bit अचिन्हित value
 * acpi_native_पूर्णांक  16/32/64-bit चिन्हित value
 */

/*******************************************************************************
 *
 * Common types क्रम all compilers, all tarमाला_लो
 *
 ******************************************************************************/

#अगर_अघोषित ACPI_USE_SYSTEM_INTTYPES

प्रकार अचिन्हित अक्षर u8;
प्रकार अचिन्हित लघु u16;
प्रकार लघु s16;
प्रकार COMPILER_DEPENDENT_UINT64 u64;
प्रकार COMPILER_DEPENDENT_INT64 s64;

#पूर्ण_अगर				/* ACPI_USE_SYSTEM_INTTYPES */

/*
 * Value वापसed by acpi_os_get_thपढ़ो_id. There is no standard "thread_id"
 * across operating प्रणालीs or even the various UNIX प्रणालीs. Since ACPICA
 * only needs the thपढ़ो ID as a unique thपढ़ो identअगरier, we use a u64
 * as the only common data type - it will accommodate any type of poपूर्णांकer or
 * any type of पूर्णांकeger. It is up to the host-dependent OSL to cast the
 * native thपढ़ो ID type to a u64 (in acpi_os_get_thपढ़ो_id).
 */
#घोषणा acpi_thपढ़ो_id                  u64

/*******************************************************************************
 *
 * Types specअगरic to 64-bit tarमाला_लो
 *
 ******************************************************************************/

#अगर ACPI_MACHINE_WIDTH == 64

#अगर_अघोषित ACPI_USE_SYSTEM_INTTYPES

प्रकार अचिन्हित पूर्णांक u32;
प्रकार पूर्णांक s32;

#पूर्ण_अगर				/* ACPI_USE_SYSTEM_INTTYPES */

प्रकार s64 acpi_native_पूर्णांक;

प्रकार u64 acpi_size;
प्रकार u64 acpi_io_address;
प्रकार u64 acpi_physical_address;

#घोषणा ACPI_MAX_PTR                    ACPI_UINT64_MAX
#घोषणा ACPI_SIZE_MAX                   ACPI_UINT64_MAX

#घोषणा ACPI_USE_NATIVE_DIVIDE	/* Has native 64-bit पूर्णांकeger support */
#घोषणा ACPI_USE_NATIVE_MATH64	/* Has native 64-bit पूर्णांकeger support */

/*
 * In the हाल of the Itanium Processor Family (IPF), the hardware करोes not
 * support misaligned memory transfers. Set the MISALIGNMENT_NOT_SUPPORTED
 * flag to indicate that special precautions must be taken to aव्योम alignment
 * faults. (IA64 or ia64 is currently used by existing compilers to indicate
 * IPF.)
 *
 * Note: EM64T and other X86-64 processors support misaligned transfers,
 * so there is no need to define this flag.
 */
#अगर defined (__IA64__) || defined (__ia64__)
#घोषणा ACPI_MISALIGNMENT_NOT_SUPPORTED
#पूर्ण_अगर

/*******************************************************************************
 *
 * Types specअगरic to 32-bit tarमाला_लो
 *
 ******************************************************************************/

#या_अगर ACPI_MACHINE_WIDTH == 32

#अगर_अघोषित ACPI_USE_SYSTEM_INTTYPES

प्रकार अचिन्हित पूर्णांक u32;
प्रकार पूर्णांक s32;

#पूर्ण_अगर				/* ACPI_USE_SYSTEM_INTTYPES */

प्रकार s32 acpi_native_पूर्णांक;

प्रकार u32 acpi_size;

#अगर_घोषित ACPI_32BIT_PHYSICAL_ADDRESS

/*
 * OSPMs can define this to shrink the size of the काष्ठाures क्रम 32-bit
 * none PAE environment. ASL compiler may always define this to generate
 * 32-bit OSPM compliant tables.
 */
प्रकार u32 acpi_io_address;
प्रकार u32 acpi_physical_address;

#अन्यथा				/* ACPI_32BIT_PHYSICAL_ADDRESS */

/*
 * It is reported that, after some calculations, the physical addresses can
 * wrap over the 32-bit boundary on 32-bit PAE environment.
 * https://bugzilla.kernel.org/show_bug.cgi?id=87971
 */
प्रकार u64 acpi_io_address;
प्रकार u64 acpi_physical_address;

#पूर्ण_अगर				/* ACPI_32BIT_PHYSICAL_ADDRESS */

#घोषणा ACPI_MAX_PTR                    ACPI_UINT32_MAX
#घोषणा ACPI_SIZE_MAX                   ACPI_UINT32_MAX

#अन्यथा

/* ACPI_MACHINE_WIDTH must be either 64 or 32 */

#त्रुटि unknown ACPI_MACHINE_WIDTH
#पूर्ण_अगर

/*******************************************************************************
 *
 * OS-dependent types
 *
 * If the शेषs below are not appropriate क्रम the host प्रणाली, they can
 * be defined in the OS-specअगरic header, and this will take precedence.
 *
 ******************************************************************************/

/* Flags क्रम acpi_os_acquire_lock/acpi_os_release_lock */

#अगर_अघोषित acpi_cpu_flags
#घोषणा acpi_cpu_flags			acpi_size
#पूर्ण_अगर

/* Object वापसed from acpi_os_create_cache */

#अगर_अघोषित acpi_cache_t
#अगर_घोषित ACPI_USE_LOCAL_CACHE
#घोषणा acpi_cache_t                    काष्ठा acpi_memory_list
#अन्यथा
#घोषणा acpi_cache_t                    व्योम *
#पूर्ण_अगर
#पूर्ण_अगर

/*
 * Synchronization objects - Mutexes, Semaphores, and spin_locks
 */
#अगर (ACPI_MUTEX_TYPE == ACPI_BINARY_SEMAPHORE)
/*
 * These macros are used अगर the host OS करोes not support a mutex object.
 * Map the OSL Mutex पूर्णांकerfaces to binary semaphores.
 */
#घोषणा acpi_mutex                      acpi_semaphore
#घोषणा acpi_os_create_mutex(out_handle) acpi_os_create_semaphore (1, 1, out_handle)
#घोषणा acpi_os_delete_mutex(handle)    (व्योम) acpi_os_delete_semaphore (handle)
#घोषणा acpi_os_acquire_mutex(handle,समय) acpi_os_रुको_semaphore (handle, 1, समय)
#घोषणा acpi_os_release_mutex(handle)   (व्योम) acpi_os_संकेत_semaphore (handle, 1)
#पूर्ण_अगर

/* Configurable types क्रम synchronization objects */

#अगर_अघोषित acpi_spinlock
#घोषणा acpi_spinlock                   व्योम *
#पूर्ण_अगर

#अगर_अघोषित acpi_raw_spinlock
#घोषणा acpi_raw_spinlock		acpi_spinlock
#पूर्ण_अगर

#अगर_अघोषित acpi_semaphore
#घोषणा acpi_semaphore                  व्योम *
#पूर्ण_अगर

#अगर_अघोषित acpi_mutex
#घोषणा acpi_mutex                      व्योम *
#पूर्ण_अगर

/*******************************************************************************
 *
 * Compiler-dependent types
 *
 * If the शेषs below are not appropriate क्रम the host compiler, they can
 * be defined in the compiler-specअगरic header, and this will take precedence.
 *
 ******************************************************************************/

/* Use C99 uपूर्णांकptr_t क्रम poपूर्णांकer casting अगर available, "void *" otherwise */

#अगर_अघोषित acpi_uपूर्णांकptr_t
#घोषणा acpi_uपूर्णांकptr_t                  व्योम *
#पूर्ण_अगर

/*
 * ACPI_PRINTF_LIKE is used to tag functions as "printf-like" because
 * some compilers can catch म_लिखो क्रमmat string problems
 */
#अगर_अघोषित ACPI_PRINTF_LIKE
#घोषणा ACPI_PRINTF_LIKE(c)
#पूर्ण_अगर

/*
 * Some compilers complain about unused variables. Someबार we करोn't want
 * to use all the variables (क्रम example, _acpi_module_name). This allows us
 * to tell the compiler in a per-variable manner that a variable
 * is unused
 */
#अगर_अघोषित ACPI_UNUSED_VAR
#घोषणा ACPI_UNUSED_VAR
#पूर्ण_अगर

/*
 * All ACPICA बाह्यal functions that are available to the rest of the
 * kernel are tagged with these macros which can be defined as appropriate
 * क्रम the host.
 *
 * Notes:
 * ACPI_EXPORT_SYMBOL_INIT is used क्रम initialization and termination
 * पूर्णांकerfaces that may need special processing.
 * ACPI_EXPORT_SYMBOL is used क्रम all other खुला बाह्यal functions.
 */
#अगर_अघोषित ACPI_EXPORT_SYMBOL_INIT
#घोषणा ACPI_EXPORT_SYMBOL_INIT(symbol)
#पूर्ण_अगर

#अगर_अघोषित ACPI_EXPORT_SYMBOL
#घोषणा ACPI_EXPORT_SYMBOL(symbol)
#पूर्ण_अगर

/*
 * Compiler/Clibrary-dependent debug initialization. Used क्रम ACPICA
 * utilities only.
 */
#अगर_अघोषित ACPI_DEBUG_INITIALIZE
#घोषणा ACPI_DEBUG_INITIALIZE()
#पूर्ण_अगर

/*******************************************************************************
 *
 * Configuration
 *
 ******************************************************************************/

#अगर_घोषित ACPI_NO_MEM_ALLOCATIONS

#घोषणा ACPI_ALLOCATE(a)                शून्य
#घोषणा ACPI_ALLOCATE_ZEROED(a)         शून्य
#घोषणा ACPI_FREE(a)
#घोषणा ACPI_MEM_TRACKING(a)

#अन्यथा				/* ACPI_NO_MEM_ALLOCATIONS */

#अगर_घोषित ACPI_DBG_TRACK_ALLOCATIONS
/*
 * Memory allocation tracking (used by acpi_exec to detect memory leaks)
 */
#घोषणा ACPI_MEM_PARAMETERS             _COMPONENT, _acpi_module_name, __LINE__
#घोषणा ACPI_ALLOCATE(a)                acpi_ut_allocate_and_track ((acpi_size) (a), ACPI_MEM_PARAMETERS)
#घोषणा ACPI_ALLOCATE_ZEROED(a)         acpi_ut_allocate_zeroed_and_track ((acpi_size) (a), ACPI_MEM_PARAMETERS)
#घोषणा ACPI_FREE(a)                    acpi_ut_मुक्त_and_track (a, ACPI_MEM_PARAMETERS)
#घोषणा ACPI_MEM_TRACKING(a)            a

#अन्यथा
/*
 * Normal memory allocation directly via the OS services layer
 */
#घोषणा ACPI_ALLOCATE(a)                acpi_os_allocate ((acpi_size) (a))
#घोषणा ACPI_ALLOCATE_ZEROED(a)         acpi_os_allocate_zeroed ((acpi_size) (a))
#घोषणा ACPI_FREE(a)                    acpi_os_मुक्त (a)
#घोषणा ACPI_MEM_TRACKING(a)

#पूर्ण_अगर				/* ACPI_DBG_TRACK_ALLOCATIONS */

#पूर्ण_अगर				/* ACPI_NO_MEM_ALLOCATIONS */

/******************************************************************************
 *
 * ACPI Specअगरication स्थिरants (Do not change unless the specअगरication
 * changes)
 *
 *****************************************************************************/

/* Number of distinct FADT-based GPE रेजिस्टर blocks (GPE0 and GPE1) */

#घोषणा ACPI_MAX_GPE_BLOCKS             2

/* Default ACPI रेजिस्टर widths */

#घोषणा ACPI_GPE_REGISTER_WIDTH         8
#घोषणा ACPI_PM1_REGISTER_WIDTH         16
#घोषणा ACPI_PM2_REGISTER_WIDTH         8
#घोषणा ACPI_PM_TIMER_WIDTH             32
#घोषणा ACPI_RESET_REGISTER_WIDTH       8

/* Names within the namespace are 4 bytes दीर्घ */

#घोषणा ACPI_NAMESEG_SIZE               4	/* Fixed by ACPI spec */
#घोषणा ACPI_PATH_SEGMENT_LENGTH        5	/* 4 अक्षरs क्रम name + 1 अक्षर क्रम separator */
#घोषणा ACPI_PATH_SEPARATOR             '.'

/* Sizes क्रम ACPI table headers */

#घोषणा ACPI_OEM_ID_SIZE                6
#घोषणा ACPI_OEM_TABLE_ID_SIZE          8

/* ACPI/PNP hardware IDs */

#घोषणा PCI_ROOT_HID_STRING             "PNP0A03"
#घोषणा PCI_EXPRESS_ROOT_HID_STRING     "PNP0A08"

/* PM Timer ticks per second (HZ) */

#घोषणा ACPI_PM_TIMER_FREQUENCY         3579545

/*******************************************************************************
 *
 * Independent types
 *
 ******************************************************************************/

/* Logical defines and शून्य */

#अगर_घोषित FALSE
#अघोषित FALSE
#पूर्ण_अगर
#घोषणा FALSE                           (1 == 0)

#अगर_घोषित TRUE
#अघोषित TRUE
#पूर्ण_अगर
#घोषणा TRUE                            (1 == 1)

#अगर_अघोषित शून्य
#घोषणा शून्य                            (व्योम *) 0
#पूर्ण_अगर

/*
 * Miscellaneous types
 */
प्रकार u32 acpi_status;	/* All ACPI Exceptions */
प्रकार u32 acpi_name;		/* 4-byte ACPI name */
प्रकार अक्षर *acpi_string;	/* Null terminated ASCII string */
प्रकार व्योम *acpi_handle;	/* Actually a ptr to a NS Node */

/* Time स्थिरants क्रम समयr calculations */

#घोषणा ACPI_MSEC_PER_SEC               1000L

#घोषणा ACPI_USEC_PER_MSEC              1000L
#घोषणा ACPI_USEC_PER_SEC               1000000L

#घोषणा ACPI_100NSEC_PER_USEC           10L
#घोषणा ACPI_100NSEC_PER_MSEC           10000L
#घोषणा ACPI_100NSEC_PER_SEC            10000000L

#घोषणा ACPI_NSEC_PER_USEC              1000L
#घोषणा ACPI_NSEC_PER_MSEC              1000000L
#घोषणा ACPI_NSEC_PER_SEC               1000000000L

#घोषणा ACPI_TIME_AFTER(a, b)           ((s64)((b) - (a)) < 0)

/* Owner IDs are used to track namespace nodes क्रम selective deletion */

प्रकार u16 acpi_owner_id;
#घोषणा ACPI_OWNER_ID_MAX               0xFFF	/* 4095 possible owner IDs */

#घोषणा ACPI_INTEGER_BIT_SIZE           64
#घोषणा ACPI_MAX_DECIMAL_DIGITS         20	/* 2^64 = 18,446,744,073,709,551,616 */
#घोषणा ACPI_MAX64_DECIMAL_DIGITS       20
#घोषणा ACPI_MAX32_DECIMAL_DIGITS       10
#घोषणा ACPI_MAX16_DECIMAL_DIGITS        5
#घोषणा ACPI_MAX8_DECIMAL_DIGITS         3

/*
 * Constants with special meanings
 */
#घोषणा ACPI_ROOT_OBJECT                ((acpi_handle) ACPI_TO_POINTER (ACPI_MAX_PTR))
#घोषणा ACPI_WAIT_FOREVER               0xFFFF	/* u16, as per ACPI spec */
#घोषणा ACPI_DO_NOT_WAIT                0

/*
 * Obsolete: Acpi पूर्णांकeger width. In ACPI version 1 (1996), पूर्णांकegers are
 * 32 bits. In ACPI version 2 (2000) and later, पूर्णांकegers are max 64 bits.
 * Note that this pertains to the ACPI पूर्णांकeger type only, not to other
 * पूर्णांकegers used in the implementation of the ACPICA subप्रणाली.
 *
 * 01/2010: This type is obsolete and has been हटाओd from the entire ACPICA
 * code base. It reमुख्यs here क्रम compatibility with device drivers that use
 * the type. However, it will be हटाओd in the future.
 */
प्रकार u64 acpi_पूर्णांकeger;
#घोषणा ACPI_INTEGER_MAX                ACPI_UINT64_MAX

/*******************************************************************************
 *
 * Commonly used macros
 *
 ******************************************************************************/

/* Data manipulation */

#घोषणा ACPI_LOBYTE(पूर्णांकeger)            ((u8)   (u16)(पूर्णांकeger))
#घोषणा ACPI_HIBYTE(पूर्णांकeger)            ((u8) (((u16)(पूर्णांकeger)) >> 8))
#घोषणा ACPI_LOWORD(पूर्णांकeger)            ((u16)  (u32)(पूर्णांकeger))
#घोषणा ACPI_HIWORD(पूर्णांकeger)            ((u16)(((u32)(पूर्णांकeger)) >> 16))
#घोषणा ACPI_LODWORD(पूर्णांकeger64)         ((u32)  (u64)(पूर्णांकeger64))
#घोषणा ACPI_HIDWORD(पूर्णांकeger64)         ((u32)(((u64)(पूर्णांकeger64)) >> 32))

#घोषणा ACPI_SET_BIT(target,bit)        ((target) |= (bit))
#घोषणा ACPI_CLEAR_BIT(target,bit)      ((target) &= ~(bit))
#घोषणा ACPI_MIN(a,b)                   (((a)<(b))?(a):(b))
#घोषणा ACPI_MAX(a,b)                   (((a)>(b))?(a):(b))

/* Size calculation */

#घोषणा ACPI_ARRAY_LENGTH(x)            (माप(x) / माप((x)[0]))

/* Poपूर्णांकer manipulation */

#घोषणा ACPI_CAST_PTR(t, p)             ((t *) (acpi_uपूर्णांकptr_t) (p))
#घोषणा ACPI_CAST_INसूचीECT_PTR(t, p)    ((t **) (acpi_uपूर्णांकptr_t) (p))
#घोषणा ACPI_ADD_PTR(t, a, b)           ACPI_CAST_PTR (t, (ACPI_CAST_PTR (u8, (a)) + (acpi_size)(b)))
#घोषणा ACPI_SUB_PTR(t, a, b)           ACPI_CAST_PTR (t, (ACPI_CAST_PTR (u8, (a)) - (acpi_size)(b)))
#घोषणा ACPI_PTR_DIFF(a, b)             ((acpi_size) (ACPI_CAST_PTR (u8, (a)) - ACPI_CAST_PTR (u8, (b))))

/* Poपूर्णांकer/Integer type conversions */

#घोषणा ACPI_TO_POINTER(i)              ACPI_CAST_PTR (व्योम, (acpi_size) (i))
#घोषणा ACPI_TO_INTEGER(p)              ACPI_PTR_DIFF (p, (व्योम *) 0)
#घोषणा ACPI_OFFSET(d, f)               ACPI_PTR_DIFF (&(((d *) 0)->f), (व्योम *) 0)
#घोषणा ACPI_PHYSADDR_TO_PTR(i)         ACPI_TO_POINTER(i)
#घोषणा ACPI_PTR_TO_PHYSADDR(i)         ACPI_TO_INTEGER(i)

/* Optimizations क्रम 4-अक्षरacter (32-bit) acpi_name manipulation */

#अगर_अघोषित ACPI_MISALIGNMENT_NOT_SUPPORTED
#घोषणा ACPI_COMPARE_NAMESEG(a,b)       (*ACPI_CAST_PTR (u32, (a)) == *ACPI_CAST_PTR (u32, (b)))
#घोषणा ACPI_COPY_NAMESEG(dest,src)     (*ACPI_CAST_PTR (u32, (dest)) = *ACPI_CAST_PTR (u32, (src)))
#अन्यथा
#घोषणा ACPI_COMPARE_NAMESEG(a,b)       (!म_भेदन (ACPI_CAST_PTR (अक्षर, (a)), ACPI_CAST_PTR (अक्षर, (b)), ACPI_NAMESEG_SIZE))
#घोषणा ACPI_COPY_NAMESEG(dest,src)     (म_नकलन (ACPI_CAST_PTR (अक्षर, (dest)), ACPI_CAST_PTR (अक्षर, (src)), ACPI_NAMESEG_SIZE))
#पूर्ण_अगर

/* Support क्रम the special RSDP signature (8 अक्षरacters) */

#घोषणा ACPI_VALIDATE_RSDP_SIG(a)       (!म_भेदन (ACPI_CAST_PTR (अक्षर, (a)), ACPI_SIG_RSDP, 8))
#घोषणा ACPI_MAKE_RSDP_SIG(dest)        (स_नकल (ACPI_CAST_PTR (अक्षर, (dest)), ACPI_SIG_RSDP, 8))

/* Support क्रम OEMx signature (x can be any अक्षरacter) */
#घोषणा ACPI_IS_OEM_SIG(a)        (!म_भेदन (ACPI_CAST_PTR (अक्षर, (a)), ACPI_OEM_NAME, 3) &&\
	 strnlen (a, ACPI_NAMESEG_SIZE) == ACPI_NAMESEG_SIZE)

/*
 * Algorithm to obtain access bit or byte width.
 * Can be used with access_width of काष्ठा acpi_generic_address and access_size of
 * काष्ठा acpi_resource_generic_रेजिस्टर.
 */
#घोषणा ACPI_ACCESS_BIT_WIDTH(size)     (1 << ((size) + 2))
#घोषणा ACPI_ACCESS_BYTE_WIDTH(size)    (1 << ((size) - 1))

/*******************************************************************************
 *
 * Miscellaneous स्थिरants
 *
 ******************************************************************************/

/*
 * Initialization sequence options
 */
#घोषणा ACPI_FULL_INITIALIZATION        0x0000
#घोषणा ACPI_NO_FACS_INIT               0x0001
#घोषणा ACPI_NO_ACPI_ENABLE             0x0002
#घोषणा ACPI_NO_HARDWARE_INIT           0x0004
#घोषणा ACPI_NO_EVENT_INIT              0x0008
#घोषणा ACPI_NO_HANDLER_INIT            0x0010
#घोषणा ACPI_NO_OBJECT_INIT             0x0020
#घोषणा ACPI_NO_DEVICE_INIT             0x0040
#घोषणा ACPI_NO_ADDRESS_SPACE_INIT      0x0080

/*
 * Initialization state
 */
#घोषणा ACPI_SUBSYSTEM_INITIALIZE       0x01
#घोषणा ACPI_INITIALIZED_OK             0x02

/*
 * Power state values
 */
#घोषणा ACPI_STATE_UNKNOWN              (u8) 0xFF

#घोषणा ACPI_STATE_S0                   (u8) 0
#घोषणा ACPI_STATE_S1                   (u8) 1
#घोषणा ACPI_STATE_S2                   (u8) 2
#घोषणा ACPI_STATE_S3                   (u8) 3
#घोषणा ACPI_STATE_S4                   (u8) 4
#घोषणा ACPI_STATE_S5                   (u8) 5
#घोषणा ACPI_S_STATES_MAX               ACPI_STATE_S5
#घोषणा ACPI_S_STATE_COUNT              6

#घोषणा ACPI_STATE_D0                   (u8) 0
#घोषणा ACPI_STATE_D1                   (u8) 1
#घोषणा ACPI_STATE_D2                   (u8) 2
#घोषणा ACPI_STATE_D3_HOT               (u8) 3
#घोषणा ACPI_STATE_D3                   (u8) 4
#घोषणा ACPI_STATE_D3_COLD              ACPI_STATE_D3
#घोषणा ACPI_D_STATES_MAX               ACPI_STATE_D3
#घोषणा ACPI_D_STATE_COUNT              5

#घोषणा ACPI_STATE_C0                   (u8) 0
#घोषणा ACPI_STATE_C1                   (u8) 1
#घोषणा ACPI_STATE_C2                   (u8) 2
#घोषणा ACPI_STATE_C3                   (u8) 3
#घोषणा ACPI_C_STATES_MAX               ACPI_STATE_C3
#घोषणा ACPI_C_STATE_COUNT              4

/*
 * Sleep type invalid value
 */
#घोषणा ACPI_SLEEP_TYPE_MAX             0x7
#घोषणा ACPI_SLEEP_TYPE_INVALID         0xFF

/*
 * Standard notअगरy values
 */
#घोषणा ACPI_NOTIFY_BUS_CHECK           (u8) 0x00
#घोषणा ACPI_NOTIFY_DEVICE_CHECK        (u8) 0x01
#घोषणा ACPI_NOTIFY_DEVICE_WAKE         (u8) 0x02
#घोषणा ACPI_NOTIFY_EJECT_REQUEST       (u8) 0x03
#घोषणा ACPI_NOTIFY_DEVICE_CHECK_LIGHT  (u8) 0x04
#घोषणा ACPI_NOTIFY_FREQUENCY_MISMATCH  (u8) 0x05
#घोषणा ACPI_NOTIFY_BUS_MODE_MISMATCH   (u8) 0x06
#घोषणा ACPI_NOTIFY_POWER_FAULT         (u8) 0x07
#घोषणा ACPI_NOTIFY_CAPABILITIES_CHECK  (u8) 0x08
#घोषणा ACPI_NOTIFY_DEVICE_PLD_CHECK    (u8) 0x09
#घोषणा ACPI_NOTIFY_RESERVED            (u8) 0x0A
#घोषणा ACPI_NOTIFY_LOCALITY_UPDATE     (u8) 0x0B
#घोषणा ACPI_NOTIFY_SHUTDOWN_REQUEST    (u8) 0x0C
#घोषणा ACPI_NOTIFY_AFFINITY_UPDATE     (u8) 0x0D
#घोषणा ACPI_NOTIFY_MEMORY_UPDATE       (u8) 0x0E
#घोषणा ACPI_NOTIFY_DISCONNECT_RECOVER  (u8) 0x0F

#घोषणा ACPI_GENERIC_NOTIFY_MAX         0x0F
#घोषणा ACPI_SPECIFIC_NOTIFY_MAX        0x84

/*
 * Types associated with ACPI names and objects. The first group of
 * values (up to ACPI_TYPE_EXTERNAL_MAX) correspond to the definition
 * of the ACPI object_type() चालक (See the ACPI Spec). Thereक्रमe,
 * only add to the first group अगर the spec changes.
 *
 * NOTE: Types must be kept in sync with the global acpi_ns_properties
 * and acpi_ns_type_names arrays.
 */
प्रकार u32 acpi_object_type;

#घोषणा ACPI_TYPE_ANY                   0x00
#घोषणा ACPI_TYPE_INTEGER               0x01	/* Byte/Word/Dword/Zero/One/Ones */
#घोषणा ACPI_TYPE_STRING                0x02
#घोषणा ACPI_TYPE_BUFFER                0x03
#घोषणा ACPI_TYPE_PACKAGE               0x04	/* byte_स्थिर, multiple data_term/Constant/super_name */
#घोषणा ACPI_TYPE_FIELD_UNIT            0x05
#घोषणा ACPI_TYPE_DEVICE                0x06	/* Name, multiple Node */
#घोषणा ACPI_TYPE_EVENT                 0x07
#घोषणा ACPI_TYPE_METHOD                0x08	/* Name, byte_स्थिर, multiple Code */
#घोषणा ACPI_TYPE_MUTEX                 0x09
#घोषणा ACPI_TYPE_REGION                0x0A
#घोषणा ACPI_TYPE_POWER                 0x0B	/* Name,byte_स्थिर,word_स्थिर,multi Node */
#घोषणा ACPI_TYPE_PROCESSOR             0x0C	/* Name,byte_स्थिर,Dword_स्थिर,byte_स्थिर,multi nm_o */
#घोषणा ACPI_TYPE_THERMAL               0x0D	/* Name, multiple Node */
#घोषणा ACPI_TYPE_BUFFER_FIELD          0x0E
#घोषणा ACPI_TYPE_DDB_HANDLE            0x0F
#घोषणा ACPI_TYPE_DEBUG_OBJECT          0x10

#घोषणा ACPI_TYPE_EXTERNAL_MAX          0x10
#घोषणा ACPI_NUM_TYPES                  (ACPI_TYPE_EXTERNAL_MAX + 1)

/*
 * These are object types that करो not map directly to the ACPI
 * object_type() चालक. They are used क्रम various पूर्णांकernal purposes
 * only. If new predefined ACPI_TYPEs are added (via the ACPI
 * specअगरication), these पूर्णांकernal types must move upwards. (There
 * is code that depends on these values being contiguous with the
 * बाह्यal types above.)
 */
#घोषणा ACPI_TYPE_LOCAL_REGION_FIELD    0x11
#घोषणा ACPI_TYPE_LOCAL_BANK_FIELD      0x12
#घोषणा ACPI_TYPE_LOCAL_INDEX_FIELD     0x13
#घोषणा ACPI_TYPE_LOCAL_REFERENCE       0x14	/* Arg#, Local#, Name, Debug, ref_of, Index */
#घोषणा ACPI_TYPE_LOCAL_ALIAS           0x15
#घोषणा ACPI_TYPE_LOCAL_METHOD_ALIAS    0x16
#घोषणा ACPI_TYPE_LOCAL_NOTIFY          0x17
#घोषणा ACPI_TYPE_LOCAL_ADDRESS_HANDLER 0x18
#घोषणा ACPI_TYPE_LOCAL_RESOURCE        0x19
#घोषणा ACPI_TYPE_LOCAL_RESOURCE_FIELD  0x1A
#घोषणा ACPI_TYPE_LOCAL_SCOPE           0x1B	/* 1 Name, multiple object_list Nodes */

#घोषणा ACPI_TYPE_NS_NODE_MAX           0x1B	/* Last typecode used within a NS Node */
#घोषणा ACPI_TOTAL_TYPES                (ACPI_TYPE_NS_NODE_MAX + 1)

/*
 * These are special object types that never appear in
 * a Namespace node, only in an object of जोड़ acpi_opeअक्रम_object
 */
#घोषणा ACPI_TYPE_LOCAL_EXTRA           0x1C
#घोषणा ACPI_TYPE_LOCAL_DATA            0x1D

#घोषणा ACPI_TYPE_LOCAL_MAX             0x1D

/* All types above here are invalid */

#घोषणा ACPI_TYPE_INVALID               0x1E
#घोषणा ACPI_TYPE_NOT_FOUND             0xFF

#घोषणा ACPI_NUM_NS_TYPES               (ACPI_TYPE_INVALID + 1)

/*
 * All I/O
 */
#घोषणा ACPI_READ                       0
#घोषणा ACPI_WRITE                      1
#घोषणा ACPI_IO_MASK                    1

/*
 * Event Types: Fixed & General Purpose
 */
प्रकार u32 acpi_event_type;

/*
 * Fixed events
 */
#घोषणा ACPI_EVENT_PMTIMER              0
#घोषणा ACPI_EVENT_GLOBAL               1
#घोषणा ACPI_EVENT_POWER_BUTTON         2
#घोषणा ACPI_EVENT_SLEEP_BUTTON         3
#घोषणा ACPI_EVENT_RTC                  4
#घोषणा ACPI_EVENT_MAX                  4
#घोषणा ACPI_NUM_FIXED_EVENTS           ACPI_EVENT_MAX + 1

/*
 * Event status - Per event
 * -------------
 * The encoding of acpi_event_status is illustrated below.
 * Note that a set bit (1) indicates the property is TRUE
 * (e.g. अगर bit 0 is set then the event is enabled).
 * +-------------+-+-+-+-+-+-+
 * |   Bits 31:6 |5|4|3|2|1|0|
 * +-------------+-+-+-+-+-+-+
 *          |     | | | | | |
 *          |     | | | | | +- Enabled?
 *          |     | | | | +--- Enabled क्रम wake?
 *          |     | | | +----- Status bit set?
 *          |     | | +------- Enable bit set?
 *          |     | +--------- Has a handler?
 *          |     +----------- Masked?
 *          +----------------- <Reserved>
 */
प्रकार u32 acpi_event_status;

#घोषणा ACPI_EVENT_FLAG_DISABLED        (acpi_event_status) 0x00
#घोषणा ACPI_EVENT_FLAG_ENABLED         (acpi_event_status) 0x01
#घोषणा ACPI_EVENT_FLAG_WAKE_ENABLED    (acpi_event_status) 0x02
#घोषणा ACPI_EVENT_FLAG_STATUS_SET      (acpi_event_status) 0x04
#घोषणा ACPI_EVENT_FLAG_ENABLE_SET      (acpi_event_status) 0x08
#घोषणा ACPI_EVENT_FLAG_HAS_HANDLER     (acpi_event_status) 0x10
#घोषणा ACPI_EVENT_FLAG_MASKED          (acpi_event_status) 0x20
#घोषणा ACPI_EVENT_FLAG_SET             ACPI_EVENT_FLAG_STATUS_SET

/* Actions क्रम acpi_set_gpe, acpi_gpe_wakeup, acpi_hw_low_set_gpe */

#घोषणा ACPI_GPE_ENABLE                 0
#घोषणा ACPI_GPE_DISABLE                1
#घोषणा ACPI_GPE_CONDITIONAL_ENABLE     2

/*
 * GPE info flags - Per GPE
 * +---+-+-+-+---+
 * |7:6|5|4|3|2:0|
 * +---+-+-+-+---+
 *   |  | | |  |
 *   |  | | |  +-- Type of dispatch:to method, handler, notअगरy, or none
 *   |  | | +----- Interrupt type: edge or level triggered
 *   |  | +------- Is a Wake GPE
 *   |  +--------- Has been enabled स्वतःmatically at init समय
 *   +------------ <Reserved>
 */
#घोषणा ACPI_GPE_DISPATCH_NONE          (u8) 0x00
#घोषणा ACPI_GPE_DISPATCH_METHOD        (u8) 0x01
#घोषणा ACPI_GPE_DISPATCH_HANDLER       (u8) 0x02
#घोषणा ACPI_GPE_DISPATCH_NOTIFY        (u8) 0x03
#घोषणा ACPI_GPE_DISPATCH_RAW_HANDLER   (u8) 0x04
#घोषणा ACPI_GPE_DISPATCH_MASK          (u8) 0x07
#घोषणा ACPI_GPE_DISPATCH_TYPE(flags)   ((u8) ((flags) & ACPI_GPE_DISPATCH_MASK))

#घोषणा ACPI_GPE_LEVEL_TRIGGERED        (u8) 0x08
#घोषणा ACPI_GPE_EDGE_TRIGGERED         (u8) 0x00
#घोषणा ACPI_GPE_XRUPT_TYPE_MASK        (u8) 0x08

#घोषणा ACPI_GPE_CAN_WAKE               (u8) 0x10
#घोषणा ACPI_GPE_AUTO_ENABLED           (u8) 0x20
#घोषणा ACPI_GPE_INITIALIZED            (u8) 0x40

/*
 * Flags क्रम GPE and Lock पूर्णांकerfaces
 */
#घोषणा ACPI_NOT_ISR                    0x1
#घोषणा ACPI_ISR                        0x0

/* Notअगरy types */

#घोषणा ACPI_SYSTEM_NOTIFY              0x1
#घोषणा ACPI_DEVICE_NOTIFY              0x2
#घोषणा ACPI_ALL_NOTIFY                 (ACPI_SYSTEM_NOTIFY | ACPI_DEVICE_NOTIFY)
#घोषणा ACPI_MAX_NOTIFY_HANDLER_TYPE    0x3
#घोषणा ACPI_NUM_NOTIFY_TYPES           2

#घोषणा ACPI_MAX_SYS_NOTIFY             0x7F
#घोषणा ACPI_MAX_DEVICE_SPECIFIC_NOTIFY 0xBF

#घोषणा ACPI_SYSTEM_HANDLER_LIST        0	/* Used as index, must be SYSTEM_NOTIFY -1 */
#घोषणा ACPI_DEVICE_HANDLER_LIST        1	/* Used as index, must be DEVICE_NOTIFY -1 */

/* Address Space (Operation Region) Types */

प्रकार u8 acpi_adr_space_type;

#घोषणा ACPI_ADR_SPACE_SYSTEM_MEMORY    (acpi_adr_space_type) 0
#घोषणा ACPI_ADR_SPACE_SYSTEM_IO        (acpi_adr_space_type) 1
#घोषणा ACPI_ADR_SPACE_PCI_CONFIG       (acpi_adr_space_type) 2
#घोषणा ACPI_ADR_SPACE_EC               (acpi_adr_space_type) 3
#घोषणा ACPI_ADR_SPACE_SMBUS            (acpi_adr_space_type) 4
#घोषणा ACPI_ADR_SPACE_CMOS             (acpi_adr_space_type) 5
#घोषणा ACPI_ADR_SPACE_PCI_BAR_TARGET   (acpi_adr_space_type) 6
#घोषणा ACPI_ADR_SPACE_IPMI             (acpi_adr_space_type) 7
#घोषणा ACPI_ADR_SPACE_GPIO             (acpi_adr_space_type) 8
#घोषणा ACPI_ADR_SPACE_GSBUS            (acpi_adr_space_type) 9
#घोषणा ACPI_ADR_SPACE_PLATFORM_COMM    (acpi_adr_space_type) 10
#घोषणा ACPI_ADR_SPACE_PLATFORM_RT      (acpi_adr_space_type) 11

#घोषणा ACPI_NUM_PREDEFINED_REGIONS     12

/*
 * Special Address Spaces
 *
 * Note: A Data Table region is a special type of operation region
 * that has its own AML opcode. However, पूर्णांकernally, the AML
 * पूर्णांकerpreter simply creates an operation region with an address
 * space type of ACPI_ADR_SPACE_DATA_TABLE.
 */
#घोषणा ACPI_ADR_SPACE_DATA_TABLE       (acpi_adr_space_type) 0x7E	/* Internal to ACPICA only */
#घोषणा ACPI_ADR_SPACE_FIXED_HARDWARE   (acpi_adr_space_type) 0x7F

/* Values क्रम _REG connection code */

#घोषणा ACPI_REG_DISCONNECT             0
#घोषणा ACPI_REG_CONNECT                1

/*
 * bit_रेजिस्टर IDs
 *
 * These values are पूर्णांकended to be used by the hardware पूर्णांकerfaces
 * and are mapped to inभागidual bitfields defined within the ACPI
 * रेजिस्टरs. See the acpi_gbl_bit_रेजिस्टर_info global table in utglobal.c
 * क्रम this mapping.
 */

/* PM1 Status रेजिस्टर */

#घोषणा ACPI_BITREG_TIMER_STATUS                0x00
#घोषणा ACPI_BITREG_BUS_MASTER_STATUS           0x01
#घोषणा ACPI_BITREG_GLOBAL_LOCK_STATUS          0x02
#घोषणा ACPI_BITREG_POWER_BUTTON_STATUS         0x03
#घोषणा ACPI_BITREG_SLEEP_BUTTON_STATUS         0x04
#घोषणा ACPI_BITREG_RT_CLOCK_STATUS             0x05
#घोषणा ACPI_BITREG_WAKE_STATUS                 0x06
#घोषणा ACPI_BITREG_PCIEXP_WAKE_STATUS          0x07

/* PM1 Enable रेजिस्टर */

#घोषणा ACPI_BITREG_TIMER_ENABLE                0x08
#घोषणा ACPI_BITREG_GLOBAL_LOCK_ENABLE          0x09
#घोषणा ACPI_BITREG_POWER_BUTTON_ENABLE         0x0A
#घोषणा ACPI_BITREG_SLEEP_BUTTON_ENABLE         0x0B
#घोषणा ACPI_BITREG_RT_CLOCK_ENABLE             0x0C
#घोषणा ACPI_BITREG_PCIEXP_WAKE_DISABLE         0x0D

/* PM1 Control रेजिस्टर */

#घोषणा ACPI_BITREG_SCI_ENABLE                  0x0E
#घोषणा ACPI_BITREG_BUS_MASTER_RLD              0x0F
#घोषणा ACPI_BITREG_GLOBAL_LOCK_RELEASE         0x10
#घोषणा ACPI_BITREG_SLEEP_TYPE                  0x11
#घोषणा ACPI_BITREG_SLEEP_ENABLE                0x12

/* PM2 Control रेजिस्टर */

#घोषणा ACPI_BITREG_ARB_DISABLE                 0x13

#घोषणा ACPI_BITREG_MAX                         0x13
#घोषणा ACPI_NUM_BITREG                         ACPI_BITREG_MAX + 1

/* Status रेजिस्टर values. A 1 clears a status bit. 0 = no effect */

#घोषणा ACPI_CLEAR_STATUS                       1

/* Enable and Control रेजिस्टर values */

#घोषणा ACPI_ENABLE_EVENT                       1
#घोषणा ACPI_DISABLE_EVENT                      0

/*
 * External ACPI object definition
 */

/*
 * Note: Type == ACPI_TYPE_ANY (0) is used to indicate a शून्य package
 * element or an unresolved named reference.
 */
जोड़ acpi_object अणु
	acpi_object_type type;	/* See definition of acpi_ns_type क्रम values */
	काष्ठा अणु
		acpi_object_type type;	/* ACPI_TYPE_INTEGER */
		u64 value;	/* The actual number */
	पूर्ण पूर्णांकeger;

	काष्ठा अणु
		acpi_object_type type;	/* ACPI_TYPE_STRING */
		u32 length;	/* # of bytes in string, excluding trailing null */
		अक्षर *poपूर्णांकer;	/* poपूर्णांकs to the string value */
	पूर्ण string;

	काष्ठा अणु
		acpi_object_type type;	/* ACPI_TYPE_BUFFER */
		u32 length;	/* # of bytes in buffer */
		u8 *poपूर्णांकer;	/* poपूर्णांकs to the buffer */
	पूर्ण buffer;

	काष्ठा अणु
		acpi_object_type type;	/* ACPI_TYPE_PACKAGE */
		u32 count;	/* # of elements in package */
		जोड़ acpi_object *elements;	/* Poपूर्णांकer to an array of ACPI_OBJECTs */
	पूर्ण package;

	काष्ठा अणु
		acpi_object_type type;	/* ACPI_TYPE_LOCAL_REFERENCE */
		acpi_object_type actual_type;	/* Type associated with the Handle */
		acpi_handle handle;	/* object reference */
	पूर्ण reference;

	काष्ठा अणु
		acpi_object_type type;	/* ACPI_TYPE_PROCESSOR */
		u32 proc_id;
		acpi_io_address pblk_address;
		u32 pblk_length;
	पूर्ण processor;

	काष्ठा अणु
		acpi_object_type type;	/* ACPI_TYPE_POWER */
		u32 प्रणाली_level;
		u32 resource_order;
	पूर्ण घातer_resource;
पूर्ण;

/*
 * List of objects, used as a parameter list क्रम control method evaluation
 */
काष्ठा acpi_object_list अणु
	u32 count;
	जोड़ acpi_object *poपूर्णांकer;
पूर्ण;

/*
 * Miscellaneous common Data Structures used by the पूर्णांकerfaces
 */
#घोषणा ACPI_NO_BUFFER              0

#अगर_घोषित ACPI_NO_MEM_ALLOCATIONS

#घोषणा ACPI_ALLOCATE_BUFFER        (acpi_size) (0)
#घोषणा ACPI_ALLOCATE_LOCAL_BUFFER  (acpi_size) (0)

#अन्यथा				/* ACPI_NO_MEM_ALLOCATIONS */

#घोषणा ACPI_ALLOCATE_BUFFER        (acpi_size) (-1)	/* Let ACPICA allocate buffer */
#घोषणा ACPI_ALLOCATE_LOCAL_BUFFER  (acpi_size) (-2)	/* For पूर्णांकernal use only (enables tracking) */

#पूर्ण_अगर				/* ACPI_NO_MEM_ALLOCATIONS */

काष्ठा acpi_buffer अणु
	acpi_size length;	/* Length in bytes of the buffer */
	व्योम *poपूर्णांकer;		/* poपूर्णांकer to buffer */
पूर्ण;

/*
 * name_type क्रम acpi_get_name
 */
#घोषणा ACPI_FULL_PATHNAME              0
#घोषणा ACPI_SINGLE_NAME                1
#घोषणा ACPI_FULL_PATHNAME_NO_TRAILING  2
#घोषणा ACPI_NAME_TYPE_MAX              2

/*
 * Predefined Namespace items
 */
काष्ठा acpi_predefined_names अणु
	स्थिर अक्षर *name;
	u8 type;
	अक्षर *val;
पूर्ण;

/*
 * Structure and flags क्रम acpi_get_प्रणाली_info
 */
#घोषणा ACPI_SYS_MODE_UNKNOWN           0x0000
#घोषणा ACPI_SYS_MODE_ACPI              0x0001
#घोषणा ACPI_SYS_MODE_LEGACY            0x0002
#घोषणा ACPI_SYS_MODES_MASK             0x0003

/*
 * System info वापसed by acpi_get_प्रणाली_info()
 */
काष्ठा acpi_प्रणाली_info अणु
	u32 acpi_ca_version;
	u32 flags;
	u32 समयr_resolution;
	u32 reserved1;
	u32 reserved2;
	u32 debug_level;
	u32 debug_layer;
पूर्ण;

/*
 * System statistics वापसed by acpi_get_statistics()
 */
काष्ठा acpi_statistics अणु
	u32 sci_count;
	u32 gpe_count;
	u32 fixed_event_count[ACPI_NUM_FIXED_EVENTS];
	u32 method_count;
पूर्ण;

/*
 * Types specअगरic to the OS service पूर्णांकerfaces
 */
प्रकार u32
 (ACPI_SYSTEM_XFACE * acpi_osd_handler) (व्योम *context);

प्रकार व्योम
 (ACPI_SYSTEM_XFACE * acpi_osd_exec_callback) (व्योम *context);

/*
 * Various handlers and callback procedures
 */
प्रकार
u32 (*acpi_sci_handler) (व्योम *context);

प्रकार
व्योम (*acpi_gbl_event_handler) (u32 event_type,
			       acpi_handle device,
			       u32 event_number, व्योम *context);

#घोषणा ACPI_EVENT_TYPE_GPE         0
#घोषणा ACPI_EVENT_TYPE_FIXED       1

प्रकार
u32(*acpi_event_handler) (व्योम *context);

प्रकार
u32 (*acpi_gpe_handler) (acpi_handle gpe_device, u32 gpe_number, व्योम *context);

प्रकार
व्योम (*acpi_notअगरy_handler) (acpi_handle device, u32 value, व्योम *context);

प्रकार
व्योम (*acpi_object_handler) (acpi_handle object, व्योम *data);

प्रकार
acpi_status (*acpi_init_handler) (acpi_handle object, u32 function);

#घोषणा ACPI_INIT_DEVICE_INI        1

प्रकार
acpi_status (*acpi_exception_handler) (acpi_status aml_status,
				       acpi_name name,
				       u16 opcode,
				       u32 aml_offset, व्योम *context);

/* Table Event handler (Load, load_table, etc.) and types */

प्रकार
acpi_status (*acpi_table_handler) (u32 event, व्योम *table, व्योम *context);

/* Table Event Types */

#घोषणा ACPI_TABLE_EVENT_LOAD           0x0
#घोषणा ACPI_TABLE_EVENT_UNLOAD         0x1
#घोषणा ACPI_TABLE_EVENT_INSTALL        0x2
#घोषणा ACPI_TABLE_EVENT_UNINSTALL      0x3
#घोषणा ACPI_NUM_TABLE_EVENTS           4

/* Address Spaces (For Operation Regions) */

प्रकार
acpi_status (*acpi_adr_space_handler) (u32 function,
				       acpi_physical_address address,
				       u32 bit_width,
				       u64 *value,
				       व्योम *handler_context,
				       व्योम *region_context);

#घोषणा ACPI_DEFAULT_HANDLER            शून्य

/* Special Context data क्रम generic_serial_bus/general_purpose_io (ACPI 5.0) */

काष्ठा acpi_connection_info अणु
	u8 *connection;
	u16 length;
	u8 access_length;
पूर्ण;

प्रकार
acpi_status (*acpi_adr_space_setup) (acpi_handle region_handle,
				     u32 function,
				     व्योम *handler_context,
				     व्योम **region_context);

#घोषणा ACPI_REGION_ACTIVATE    0
#घोषणा ACPI_REGION_DEACTIVATE  1

प्रकार
acpi_status (*acpi_walk_callback) (acpi_handle object,
				   u32 nesting_level,
				   व्योम *context, व्योम **वापस_value);

प्रकार
u32 (*acpi_पूर्णांकerface_handler) (acpi_string पूर्णांकerface_name, u32 supported);

/* Interrupt handler वापस values */

#घोषणा ACPI_INTERRUPT_NOT_HANDLED      0x00
#घोषणा ACPI_INTERRUPT_HANDLED          0x01

/* GPE handler वापस values */

#घोषणा ACPI_REENABLE_GPE               0x80

/* Length of 32-bit EISAID values when converted back to a string */

#घोषणा ACPI_EISAID_STRING_SIZE         8	/* Includes null terminator */

/* Length of UUID (string) values */

#घोषणा ACPI_UUID_LENGTH                16

/* Length of 3-byte PCI class code values when converted back to a string */

#घोषणा ACPI_PCICLS_STRING_SIZE         7	/* Includes null terminator */

/* Structures used क्रम device/processor HID, UID, CID */

काष्ठा acpi_pnp_device_id अणु
	u32 length;		/* Length of string + null */
	अक्षर *string;
पूर्ण;

काष्ठा acpi_pnp_device_id_list अणु
	u32 count;		/* Number of IDs in Ids array */
	u32 list_size;		/* Size of list, including ID strings */
	काष्ठा acpi_pnp_device_id ids[];	/* ID array */
पूर्ण;

/*
 * Structure वापसed from acpi_get_object_info.
 * Optimized क्रम both 32-bit and 64-bit builds.
 */
काष्ठा acpi_device_info अणु
	u32 info_size;		/* Size of info, including ID strings */
	u32 name;		/* ACPI object Name */
	acpi_object_type type;	/* ACPI object Type */
	u8 param_count;		/* If a method, required parameter count */
	u16 valid;		/* Indicates which optional fields are valid */
	u8 flags;		/* Miscellaneous info */
	u8 highest_dstates[4];	/* _sx_d values: 0xFF indicates not valid */
	u8 lowest_dstates[5];	/* _sx_w values: 0xFF indicates not valid */
	u64 address;	/* _ADR value */
	काष्ठा acpi_pnp_device_id hardware_id;	/* _HID value */
	काष्ठा acpi_pnp_device_id unique_id;	/* _UID value */
	काष्ठा acpi_pnp_device_id class_code;	/* _CLS value */
	काष्ठा acpi_pnp_device_id_list compatible_id_list;	/* _CID list <must be last> */
पूर्ण;

/* Values क्रम Flags field above (acpi_get_object_info) */

#घोषणा ACPI_PCI_ROOT_BRIDGE            0x01

/* Flags क्रम Valid field above (acpi_get_object_info) */

#घोषणा ACPI_VALID_ADR                  0x0002
#घोषणा ACPI_VALID_HID                  0x0004
#घोषणा ACPI_VALID_UID                  0x0008
#घोषणा ACPI_VALID_CID                  0x0020
#घोषणा ACPI_VALID_CLS                  0x0040
#घोषणा ACPI_VALID_SXDS                 0x0100
#घोषणा ACPI_VALID_SXWS                 0x0200

/* Flags क्रम _STA method */

#घोषणा ACPI_STA_DEVICE_PRESENT         0x01
#घोषणा ACPI_STA_DEVICE_ENABLED         0x02
#घोषणा ACPI_STA_DEVICE_UI              0x04
#घोषणा ACPI_STA_DEVICE_FUNCTIONING     0x08
#घोषणा ACPI_STA_DEVICE_OK              0x08	/* Synonym */
#घोषणा ACPI_STA_BATTERY_PRESENT        0x10

/* Context काष्ठाs क्रम address space handlers */

काष्ठा acpi_pci_id अणु
	u16 segment;
	u16 bus;
	u16 device;
	u16 function;
पूर्ण;

काष्ठा acpi_mem_mapping अणु
	acpi_physical_address physical_address;
	u8 *logical_address;
	acpi_size length;
	काष्ठा acpi_mem_mapping *next_mm;
पूर्ण;

काष्ठा acpi_mem_space_context अणु
	u32 length;
	acpi_physical_address address;
	काष्ठा acpi_mem_mapping *cur_mm;
	काष्ठा acpi_mem_mapping *first_mm;
पूर्ण;

/*
 * काष्ठा acpi_memory_list is used only अगर the ACPICA local cache is enabled
 */
काष्ठा acpi_memory_list अणु
	स्थिर अक्षर *list_name;
	व्योम *list_head;
	u16 object_size;
	u16 max_depth;
	u16 current_depth;

#अगर_घोषित ACPI_DBG_TRACK_ALLOCATIONS

	/* Statistics क्रम debug memory tracking only */

	u32 total_allocated;
	u32 total_मुक्तd;
	u32 max_occupied;
	u32 total_size;
	u32 current_total_size;
	u32 requests;
	u32 hits;
#पूर्ण_अगर
पूर्ण;

/* Definitions of trace event types */

प्रकार क्रमागत अणु
	ACPI_TRACE_AML_METHOD,
	ACPI_TRACE_AML_OPCODE,
	ACPI_TRACE_AML_REGION
पूर्ण acpi_trace_event_type;

/* Definitions of _OSI support */

#घोषणा ACPI_VENDOR_STRINGS                 0x01
#घोषणा ACPI_FEATURE_STRINGS                0x02
#घोषणा ACPI_ENABLE_INTERFACES              0x00
#घोषणा ACPI_DISABLE_INTERFACES             0x04

#घोषणा ACPI_DISABLE_ALL_VENDOR_STRINGS     (ACPI_DISABLE_INTERFACES | ACPI_VENDOR_STRINGS)
#घोषणा ACPI_DISABLE_ALL_FEATURE_STRINGS    (ACPI_DISABLE_INTERFACES | ACPI_FEATURE_STRINGS)
#घोषणा ACPI_DISABLE_ALL_STRINGS            (ACPI_DISABLE_INTERFACES | ACPI_VENDOR_STRINGS | ACPI_FEATURE_STRINGS)
#घोषणा ACPI_ENABLE_ALL_VENDOR_STRINGS      (ACPI_ENABLE_INTERFACES | ACPI_VENDOR_STRINGS)
#घोषणा ACPI_ENABLE_ALL_FEATURE_STRINGS     (ACPI_ENABLE_INTERFACES | ACPI_FEATURE_STRINGS)
#घोषणा ACPI_ENABLE_ALL_STRINGS             (ACPI_ENABLE_INTERFACES | ACPI_VENDOR_STRINGS | ACPI_FEATURE_STRINGS)

#घोषणा ACPI_OSI_WIN_2000               0x01
#घोषणा ACPI_OSI_WIN_XP                 0x02
#घोषणा ACPI_OSI_WIN_XP_SP1             0x03
#घोषणा ACPI_OSI_WINSRV_2003            0x04
#घोषणा ACPI_OSI_WIN_XP_SP2             0x05
#घोषणा ACPI_OSI_WINSRV_2003_SP1        0x06
#घोषणा ACPI_OSI_WIN_VISTA              0x07
#घोषणा ACPI_OSI_WINSRV_2008            0x08
#घोषणा ACPI_OSI_WIN_VISTA_SP1          0x09
#घोषणा ACPI_OSI_WIN_VISTA_SP2          0x0A
#घोषणा ACPI_OSI_WIN_7                  0x0B
#घोषणा ACPI_OSI_WIN_8                  0x0C
#घोषणा ACPI_OSI_WIN_8_1                0x0D
#घोषणा ACPI_OSI_WIN_10                 0x0E
#घोषणा ACPI_OSI_WIN_10_RS1             0x0F
#घोषणा ACPI_OSI_WIN_10_RS2             0x10
#घोषणा ACPI_OSI_WIN_10_RS3             0x11
#घोषणा ACPI_OSI_WIN_10_RS4             0x12
#घोषणा ACPI_OSI_WIN_10_RS5             0x13
#घोषणा ACPI_OSI_WIN_10_19H1            0x14

/* Definitions of getopt */

#घोषणा ACPI_OPT_END                    -1

/* Definitions क्रम explicit fallthrough */

#अगर_अघोषित ACPI_FALLTHROUGH
#घोषणा ACPI_FALLTHROUGH करो अणुपूर्ण जबतक(0)
#पूर्ण_अगर

#पूर्ण_अगर				/* __ACTYPES_H__ */
