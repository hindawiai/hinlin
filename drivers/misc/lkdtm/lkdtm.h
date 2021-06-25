<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __LKDTM_H
#घोषणा __LKDTM_H

#घोषणा pr_fmt(fmt) "lkdtm: " fmt

#समावेश <linux/kernel.h>

/* bugs.c */
व्योम __init lkdपंचांग_bugs_init(पूर्णांक *recur_param);
व्योम lkdपंचांग_PANIC(व्योम);
व्योम lkdपंचांग_BUG(व्योम);
व्योम lkdपंचांग_WARNING(व्योम);
व्योम lkdपंचांग_WARNING_MESSAGE(व्योम);
व्योम lkdपंचांग_EXCEPTION(व्योम);
व्योम lkdपंचांग_LOOP(व्योम);
व्योम lkdपंचांग_EXHAUST_STACK(व्योम);
व्योम lkdपंचांग_CORRUPT_STACK(व्योम);
व्योम lkdपंचांग_CORRUPT_STACK_STRONG(व्योम);
व्योम lkdपंचांग_REPORT_STACK(व्योम);
व्योम lkdपंचांग_UNALIGNED_LOAD_STORE_WRITE(व्योम);
व्योम lkdपंचांग_SOFTLOCKUP(व्योम);
व्योम lkdपंचांग_HARDLOCKUP(व्योम);
व्योम lkdपंचांग_SPINLOCKUP(व्योम);
व्योम lkdपंचांग_HUNG_TASK(व्योम);
व्योम lkdपंचांग_OVERFLOW_SIGNED(व्योम);
व्योम lkdपंचांग_OVERFLOW_UNSIGNED(व्योम);
व्योम lkdपंचांग_ARRAY_BOUNDS(व्योम);
व्योम lkdपंचांग_CORRUPT_LIST_ADD(व्योम);
व्योम lkdपंचांग_CORRUPT_LIST_DEL(व्योम);
व्योम lkdपंचांग_STACK_GUARD_PAGE_LEADING(व्योम);
व्योम lkdपंचांग_STACK_GUARD_PAGE_TRAILING(व्योम);
व्योम lkdपंचांग_UNSET_SMEP(व्योम);
व्योम lkdपंचांग_DOUBLE_FAULT(व्योम);
व्योम lkdपंचांग_CORRUPT_PAC(व्योम);
व्योम lkdपंचांग_FORTIFY_OBJECT(व्योम);
व्योम lkdपंचांग_FORTIFY_SUBOBJECT(व्योम);

/* heap.c */
व्योम __init lkdपंचांग_heap_init(व्योम);
व्योम __निकास lkdपंचांग_heap_निकास(व्योम);
व्योम lkdपंचांग_OVERWRITE_ALLOCATION(व्योम);
व्योम lkdपंचांग_WRITE_AFTER_FREE(व्योम);
व्योम lkdपंचांग_READ_AFTER_FREE(व्योम);
व्योम lkdपंचांग_WRITE_BUDDY_AFTER_FREE(व्योम);
व्योम lkdपंचांग_READ_BUDDY_AFTER_FREE(व्योम);
व्योम lkdपंचांग_SLAB_FREE_DOUBLE(व्योम);
व्योम lkdपंचांग_SLAB_FREE_CROSS(व्योम);
व्योम lkdपंचांग_SLAB_FREE_PAGE(व्योम);

/* perms.c */
व्योम __init lkdपंचांग_perms_init(व्योम);
व्योम lkdपंचांग_WRITE_RO(व्योम);
व्योम lkdपंचांग_WRITE_RO_AFTER_INIT(व्योम);
व्योम lkdपंचांग_WRITE_KERN(व्योम);
व्योम lkdपंचांग_EXEC_DATA(व्योम);
व्योम lkdपंचांग_EXEC_STACK(व्योम);
व्योम lkdपंचांग_EXEC_KMALLOC(व्योम);
व्योम lkdपंचांग_EXEC_VMALLOC(व्योम);
व्योम lkdपंचांग_EXEC_RODATA(व्योम);
व्योम lkdपंचांग_EXEC_USERSPACE(व्योम);
व्योम lkdपंचांग_EXEC_शून्य(व्योम);
व्योम lkdपंचांग_ACCESS_USERSPACE(व्योम);
व्योम lkdपंचांग_ACCESS_शून्य(व्योम);

/* refcount.c */
व्योम lkdपंचांग_REFCOUNT_INC_OVERFLOW(व्योम);
व्योम lkdपंचांग_REFCOUNT_ADD_OVERFLOW(व्योम);
व्योम lkdपंचांग_REFCOUNT_INC_NOT_ZERO_OVERFLOW(व्योम);
व्योम lkdपंचांग_REFCOUNT_ADD_NOT_ZERO_OVERFLOW(व्योम);
व्योम lkdपंचांग_REFCOUNT_DEC_ZERO(व्योम);
व्योम lkdपंचांग_REFCOUNT_DEC_NEGATIVE(व्योम);
व्योम lkdपंचांग_REFCOUNT_DEC_AND_TEST_NEGATIVE(व्योम);
व्योम lkdपंचांग_REFCOUNT_SUB_AND_TEST_NEGATIVE(व्योम);
व्योम lkdपंचांग_REFCOUNT_INC_ZERO(व्योम);
व्योम lkdपंचांग_REFCOUNT_ADD_ZERO(व्योम);
व्योम lkdपंचांग_REFCOUNT_INC_SATURATED(व्योम);
व्योम lkdपंचांग_REFCOUNT_DEC_SATURATED(व्योम);
व्योम lkdपंचांग_REFCOUNT_ADD_SATURATED(व्योम);
व्योम lkdपंचांग_REFCOUNT_INC_NOT_ZERO_SATURATED(व्योम);
व्योम lkdपंचांग_REFCOUNT_ADD_NOT_ZERO_SATURATED(व्योम);
व्योम lkdपंचांग_REFCOUNT_DEC_AND_TEST_SATURATED(व्योम);
व्योम lkdपंचांग_REFCOUNT_SUB_AND_TEST_SATURATED(व्योम);
व्योम lkdपंचांग_REFCOUNT_TIMING(व्योम);
व्योम lkdपंचांग_ATOMIC_TIMING(व्योम);

/* rodata.c */
व्योम lkdपंचांग_rodata_करो_nothing(व्योम);

/* usercopy.c */
व्योम __init lkdपंचांग_usercopy_init(व्योम);
व्योम __निकास lkdपंचांग_usercopy_निकास(व्योम);
व्योम lkdपंचांग_USERCOPY_HEAP_SIZE_TO(व्योम);
व्योम lkdपंचांग_USERCOPY_HEAP_SIZE_FROM(व्योम);
व्योम lkdपंचांग_USERCOPY_HEAP_WHITELIST_TO(व्योम);
व्योम lkdपंचांग_USERCOPY_HEAP_WHITELIST_FROM(व्योम);
व्योम lkdपंचांग_USERCOPY_STACK_FRAME_TO(व्योम);
व्योम lkdपंचांग_USERCOPY_STACK_FRAME_FROM(व्योम);
व्योम lkdपंचांग_USERCOPY_STACK_BEYOND(व्योम);
व्योम lkdपंचांग_USERCOPY_KERNEL(व्योम);

/* stackleak.c */
व्योम lkdपंचांग_STACKLEAK_ERASING(व्योम);

/* cfi.c */
व्योम lkdपंचांग_CFI_FORWARD_PROTO(व्योम);

/* क्रमtअगरy.c */
व्योम lkdपंचांग_FORTIFIED_STRSCPY(व्योम);

/* घातerpc.c */
व्योम lkdपंचांग_PPC_SLB_MULTIHIT(व्योम);

#पूर्ण_अगर
