<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2004-2017 Cavium, Inc.
 */


/*
  We install this program at the bootvector:
------------------------------------
	.set noreorder
	.set nomacro
	.set noat
reset_vector:
	dmtc0	$k0, $31, 0	# Save $k0 to DESAVE
	dmtc0	$k1, $31, 3	# Save $k1 to KScratch2

	mfc0	$k0, $12, 0	# Status
	mfc0	$k1, $15, 1	# Ebase

	ori	$k0, 0x84	# Enable 64-bit addressing, set
				# ERL (should alपढ़ोy be set)
	andi	$k1, 0x3ff	# mask out core ID

	mtc0	$k0, $12, 0	# Status
	sll	$k1, 5

	lui	$k0, 0xbfc0
	cache	17, 0($0)	# Core-14345, clear L1 Dcache भव
				# tags अगर the core hit an NMI

	ld	$k0, 0x78($k0)	# k0 <- (bfc00078) poपूर्णांकer to the reset vector
	synci	0($0)		# Invalidate ICache to get coherent
				# view of target code.

	daddu	$k0, $k0, $k1
	nop

	ld	$k0, 0($k0)	# k0 <- core specअगरic target address
	dmfc0	$k1, $31, 3	# Restore $k1 from KScratch2

	beqz	$k0, रुको_loop	# Spin in रुको loop
	nop

	jr	$k0
	nop

	nop			# NOPs needed here to fill delay slots
	nop			# on endian reversal of previous inकाष्ठाions

रुको_loop:
	रुको
	nop

	b	रुको_loop
	nop

	nop
	nop
------------------------------------

0000000000000000 <reset_vector>:
   0:	40baf800	dmtc0	k0,c0_desave
   4:	40bbf803	dmtc0	k1,c0_kscratch2

   8:	401a6000	mfc0	k0,c0_status
   c:	401b7801	mfc0	k1,c0_ebase

  10:	375a0084	ori	k0,k0,0x84
  14:	337b03ff	andi	k1,k1,0x3ff

  18:	409a6000	mtc0	k0,c0_status
  1c:	001bd940	sll	k1,k1,0x5

  20:	3c1abfc0	lui	k0,0xbfc0
  24:	bc110000	cache	0x11,0(zero)

  28:	df5a0078	ld	k0,120(k0)
  2c:	041f0000	synci	0(zero)

  30:	035bd02d	daddu	k0,k0,k1
  34:	00000000	nop

  38:	df5a0000	ld	k0,0(k0)
  3c:	403bf803	dmfc0	k1,c0_kscratch2

  40:	13400005	beqz	k0,58 <रुको_loop>
  44:	00000000	nop

  48:	03400008	jr	k0
  4c:	00000000	nop

  50:	00000000	nop
  54:	00000000	nop

0000000000000058 <रुको_loop>:
  58:	42000020	रुको
  5c:	00000000	nop

  60:	1000fffd	b	58 <रुको_loop>
  64:	00000000	nop

  68:	00000000	nop
  6c:	00000000	nop

 */

#समावेश <यंत्र/octeon/cvmx-boot-vector.h>

अटल अचिन्हित दीर्घ दीर्घ _cvmx_bootvector_data[16] = अणु
	0x40baf80040bbf803ull,  /* patch low order 8-bits अगर no KScratch*/
	0x401a6000401b7801ull,
	0x375a0084337b03ffull,
	0x409a6000001bd940ull,
	0x3c1abfc0bc110000ull,
	0xdf5a0078041f0000ull,
	0x035bd02d00000000ull,
	0xdf5a0000403bf803ull,  /* patch low order 8-bits अगर no KScratch*/
	0x1340000500000000ull,
	0x0340000800000000ull,
	0x0000000000000000ull,
	0x4200002000000000ull,
	0x1000fffd00000000ull,
	0x0000000000000000ull,
	OCTEON_BOOT_MOVEABLE_MAGIC1,
	0 /* To be filled in with address of vector block*/
पूर्ण;

/* 2^10 CPUs */
#घोषणा VECTOR_TABLE_SIZE (1024 * माप(काष्ठा cvmx_boot_vector_element))

अटल व्योम cvmx_boot_vector_init(व्योम *mem)
अणु
	uपूर्णांक64_t kseg0_mem;
	पूर्णांक i;

	स_रखो(mem, 0, VECTOR_TABLE_SIZE);
	kseg0_mem = cvmx_ptr_to_phys(mem) | 0x8000000000000000ull;

	क्रम (i = 0; i < 15; i++) अणु
		uपूर्णांक64_t v = _cvmx_bootvector_data[i];

		अगर (OCTEON_IS_OCTEON1PLUS() && (i == 0 || i == 7))
			v &= 0xffffffff00000000ull; /* KScratch not availble. */
		cvmx_ग_लिखो_csr(CVMX_MIO_BOOT_LOC_ADR, i * 8);
		cvmx_ग_लिखो_csr(CVMX_MIO_BOOT_LOC_DAT, v);
	पूर्ण
	cvmx_ग_लिखो_csr(CVMX_MIO_BOOT_LOC_ADR, 15 * 8);
	cvmx_ग_लिखो_csr(CVMX_MIO_BOOT_LOC_DAT, kseg0_mem);
	cvmx_ग_लिखो_csr(CVMX_MIO_BOOT_LOC_CFGX(0), 0x81fc0000);
पूर्ण

/**
 * Get a poपूर्णांकer to the per-core table of reset vector poपूर्णांकers
 *
 */
काष्ठा cvmx_boot_vector_element *cvmx_boot_vector_get(व्योम)
अणु
	काष्ठा cvmx_boot_vector_element *ret;

	ret = cvmx_booपंचांगem_alloc_named_range_once(VECTOR_TABLE_SIZE, 0,
		(1ull << 32) - 1, 8, "__boot_vector1__", cvmx_boot_vector_init);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(cvmx_boot_vector_get);
