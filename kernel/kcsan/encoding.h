<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * KCSAN watchpoपूर्णांक encoding.
 *
 * Copyright (C) 2019, Google LLC.
 */

#अगर_अघोषित _KERNEL_KCSAN_ENCODING_H
#घोषणा _KERNEL_KCSAN_ENCODING_H

#समावेश <linux/bits.h>
#समावेश <linux/log2.h>
#समावेश <linux/mm.h>

#समावेश "kcsan.h"

#घोषणा SLOT_RANGE PAGE_SIZE

#घोषणा INVALID_WATCHPOINT  0
#घोषणा CONSUMED_WATCHPOINT 1

/*
 * The maximum useful size of accesses क्रम which we set up watchpoपूर्णांकs is the
 * max range of slots we check on an access.
 */
#घोषणा MAX_ENCODABLE_SIZE (SLOT_RANGE * (1 + KCSAN_CHECK_ADJACENT))

/*
 * Number of bits we use to store size info.
 */
#घोषणा WATCHPOINT_SIZE_BITS bits_per(MAX_ENCODABLE_SIZE)
/*
 * This encoding क्रम addresses discards the upper (1 क्रम is-ग_लिखो + SIZE_BITS);
 * however, most 64-bit architectures करो not use the full 64-bit address space.
 * Also, in order क्रम a false positive to be observable 2 things need to happen:
 *
 *	1. dअगरferent addresses but with the same encoded address race;
 *	2. and both map onto the same watchpoपूर्णांक slots;
 *
 * Both these are assumed to be very unlikely. However, in हाल it still
 * happens, the report logic will filter out the false positive (see report.c).
 */
#घोषणा WATCHPOINT_ADDR_BITS (BITS_PER_LONG-1 - WATCHPOINT_SIZE_BITS)

/* Biपंचांगasks क्रम the encoded watchpoपूर्णांक access inक्रमmation. */
#घोषणा WATCHPOINT_WRITE_MASK	BIT(BITS_PER_LONG-1)
#घोषणा WATCHPOINT_SIZE_MASK	GENMASK(BITS_PER_LONG-2, WATCHPOINT_ADDR_BITS)
#घोषणा WATCHPOINT_ADDR_MASK	GENMASK(WATCHPOINT_ADDR_BITS-1, 0)
अटल_निश्चित(WATCHPOINT_ADDR_MASK == (1UL << WATCHPOINT_ADDR_BITS) - 1);
अटल_निश्चित((WATCHPOINT_WRITE_MASK ^ WATCHPOINT_SIZE_MASK ^ WATCHPOINT_ADDR_MASK) == ~0UL);

अटल अंतरभूत bool check_encodable(अचिन्हित दीर्घ addr, माप_प्रकार size)
अणु
	/*
	 * While we can encode addrs<PAGE_SIZE, aव्योम crashing with a शून्य
	 * poपूर्णांकer deref inside KCSAN.
	 */
	वापस addr >= PAGE_SIZE && size <= MAX_ENCODABLE_SIZE;
पूर्ण

अटल अंतरभूत दीर्घ
encode_watchpoपूर्णांक(अचिन्हित दीर्घ addr, माप_प्रकार size, bool is_ग_लिखो)
अणु
	वापस (दीर्घ)((is_ग_लिखो ? WATCHPOINT_WRITE_MASK : 0) |
		      (size << WATCHPOINT_ADDR_BITS) |
		      (addr & WATCHPOINT_ADDR_MASK));
पूर्ण

अटल __always_अंतरभूत bool decode_watchpoपूर्णांक(दीर्घ watchpoपूर्णांक,
					      अचिन्हित दीर्घ *addr_masked,
					      माप_प्रकार *size,
					      bool *is_ग_लिखो)
अणु
	अगर (watchpoपूर्णांक == INVALID_WATCHPOINT ||
	    watchpoपूर्णांक == CONSUMED_WATCHPOINT)
		वापस false;

	*addr_masked =    (अचिन्हित दीर्घ)watchpoपूर्णांक & WATCHPOINT_ADDR_MASK;
	*size	     =   ((अचिन्हित दीर्घ)watchpoपूर्णांक & WATCHPOINT_SIZE_MASK) >> WATCHPOINT_ADDR_BITS;
	*is_ग_लिखो    = !!((अचिन्हित दीर्घ)watchpoपूर्णांक & WATCHPOINT_WRITE_MASK);

	वापस true;
पूर्ण

/*
 * Return watchpoपूर्णांक slot क्रम an address.
 */
अटल __always_अंतरभूत पूर्णांक watchpoपूर्णांक_slot(अचिन्हित दीर्घ addr)
अणु
	वापस (addr / PAGE_SIZE) % CONFIG_KCSAN_NUM_WATCHPOINTS;
पूर्ण

अटल __always_अंतरभूत bool matching_access(अचिन्हित दीर्घ addr1, माप_प्रकार size1,
					    अचिन्हित दीर्घ addr2, माप_प्रकार size2)
अणु
	अचिन्हित दीर्घ end_range1 = addr1 + size1 - 1;
	अचिन्हित दीर्घ end_range2 = addr2 + size2 - 1;

	वापस addr1 <= end_range2 && addr2 <= end_range1;
पूर्ण

#पूर्ण_अगर /* _KERNEL_KCSAN_ENCODING_H */
