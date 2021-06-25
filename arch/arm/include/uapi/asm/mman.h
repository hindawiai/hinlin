<शैली गुरु>
#समावेश <यंत्र-generic/mman.h>

#घोषणा arch_mmap_check(addr, len, flags) \
	(((flags) & MAP_FIXED && (addr) < FIRST_USER_ADDRESS) ? -EINVAL : 0)
