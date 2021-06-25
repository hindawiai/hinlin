<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/memblock.h>

#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/bios_ebda.h>

/*
 * This function reserves all conventional PC प्रणाली BIOS related
 * firmware memory areas (some of which are data, some of which
 * are code), that must not be used by the kernel as available
 * RAM.
 *
 * The BIOS places the EBDA/XBDA at the top of conventional
 * memory, and usually decreases the reported amount of
 * conventional memory (पूर्णांक 0x12) too.
 *
 * This means that as a first approximation on most प्रणालीs we can
 * guess the reserved BIOS area by looking at the low BIOS RAM size
 * value and assume that everything above that value (up to 1MB) is
 * reserved.
 *
 * But lअगरe in firmware country is not that simple:
 *
 * - This code also contains a quirk क्रम Dell प्रणालीs that neglect
 *   to reserve the EBDA area in the 'RAM size' value ...
 *
 * - The same quirk also aव्योमs a problem with the AMD768MPX
 *   chipset: reserve a page beक्रमe VGA to prevent PCI prefetch
 *   पूर्णांकo it (errata #56). (Usually the page is reserved anyways,
 *   unless you have no PS/2 mouse plugged in.)
 *
 * - Plus paravirt प्रणालीs करोn't have a reliable value in the
 *   'BIOS RAM size' poपूर्णांकer we can rely on, so we must quirk
 *   them too.
 *
 * Due to those various problems this function is deliberately
 * very conservative and tries to err on the side of reserving
 * too much, to not risk reserving too little.
 *
 * Losing a small amount of memory in the bottom megabyte is
 * rarely a problem, as दीर्घ as we have enough memory to install
 * the SMP bootup trampoline which *must* be in this area.
 *
 * Using memory that is in use by the BIOS or by some DMA device
 * the BIOS didn't shut करोwn *is* a big problem to the kernel,
 * obviously.
 */

#घोषणा BIOS_RAM_SIZE_KB_PTR	0x413

#घोषणा BIOS_START_MIN		0x20000U	/* 128K, less than this is insane */
#घोषणा BIOS_START_MAX		0x9f000U	/* 640K, असलolute maximum */

व्योम __init reserve_bios_regions(व्योम)
अणु
	अचिन्हित पूर्णांक bios_start, ebda_start;

	/*
	 * NOTE: In a paraभव environment the BIOS reserved
	 * area is असलent. We'll just have to assume that the
	 * paravirt हाल can handle memory setup correctly,
	 * without our help.
	 */
	अगर (!x86_platक्रमm.legacy.reserve_bios_regions)
		वापस;

	/*
	 * BIOS RAM size is encoded in kilobytes, convert it
	 * to bytes to get a first guess at where the BIOS
	 * firmware area starts:
	 */
	bios_start = *(अचिन्हित लघु *)__va(BIOS_RAM_SIZE_KB_PTR);
	bios_start <<= 10;

	/*
	 * If bios_start is less than 128K, assume it is bogus
	 * and bump it up to 640K.  Similarly, अगर bios_start is above 640K,
	 * करोn't trust it.
	 */
	अगर (bios_start < BIOS_START_MIN || bios_start > BIOS_START_MAX)
		bios_start = BIOS_START_MAX;

	/* Get the start address of the EBDA page: */
	ebda_start = get_bios_ebda();

	/*
	 * If the EBDA start address is sane and is below the BIOS region,
	 * then also reserve everything from the EBDA start address up to
	 * the BIOS region.
	 */
	अगर (ebda_start >= BIOS_START_MIN && ebda_start < bios_start)
		bios_start = ebda_start;

	/* Reserve all memory between bios_start and the 1MB mark: */
	memblock_reserve(bios_start, 0x100000 - bios_start);
पूर्ण
