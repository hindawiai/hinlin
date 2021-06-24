<शैली गुरु>
/*
 *  Copyright (C) 2004 Florian Schirmer <jolt@tuxbox.org>
 *  Copyright (C) 2007 Aurelien Jarno <aurelien@aurel32.net>
 *  Copyright (C) 2010-2012 Hauke Mehrtens <hauke@hauke-m.de>
 *
 *  This program is मुक्त software; you can redistribute  it and/or modअगरy it
 *  under  the terms of  the GNU General  Public License as published by the
 *  Free Software Foundation;  either version 2 of the  License, or (at your
 *  option) any later version.
 *
 *  THIS  SOFTWARE  IS PROVIDED   ``AS  IS'' AND   ANY  EXPRESS OR IMPLIED
 *  WARRANTIES,   INCLUDING, BUT NOT  LIMITED  TO, THE IMPLIED WARRANTIES OF
 *  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN
 *  NO  EVENT  SHALL   THE AUTHOR  BE    LIABLE FOR ANY   सूचीECT, INसूचीECT,
 *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 *  NOT LIMITED   TO, PROCUREMENT OF  SUBSTITUTE GOODS  OR SERVICES; LOSS OF
 *  USE, DATA,  OR PROFITS; OR  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 *  ANY THEORY OF LIABILITY, WHETHER IN  CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 *  THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *  You should have received a copy of the  GNU General Public License aदीर्घ
 *  with this program; अगर not, ग_लिखो  to the Free Software Foundation, Inc.,
 *  675 Mass Ave, Cambridge, MA 02139, USA.
 */

#समावेश <linux/init.h>
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/memblock.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/ssb/ssb_driver_chipcommon.h>
#समावेश <linux/ssb/ssb_regs.h>
#समावेश <linux/smp.h>
#समावेश <यंत्र/bootinfo.h>
#समावेश <bcm47xx.h>
#समावेश <bcm47xx_board.h>

अटल अक्षर bcm47xx_प्रणाली_type[20] = "Broadcom BCM47XX";

स्थिर अक्षर *get_प्रणाली_type(व्योम)
अणु
	वापस bcm47xx_प्रणाली_type;
पूर्ण

__init व्योम bcm47xx_set_प्रणाली_type(u16 chip_id)
अणु
	snम_लिखो(bcm47xx_प्रणाली_type, माप(bcm47xx_प्रणाली_type),
		 (chip_id > 0x9999) ? "Broadcom BCM%d" :
				      "Broadcom BCM%04X",
		 chip_id);
पूर्ण

अटल अचिन्हित दीर्घ lowmem __initdata;

अटल __init व्योम prom_init_mem(व्योम)
अणु
	अचिन्हित दीर्घ mem;
	अचिन्हित दीर्घ max;
	अचिन्हित दीर्घ off;
	काष्ठा cpuinfo_mips *c = &current_cpu_data;

	/* Figure out memory size by finding aliases.
	 *
	 * We should theoretically use the mapping from CFE using cfe_क्रमागतmem().
	 * However as the BCM47XX is mostly used on low-memory प्रणालीs, we
	 * want to reuse the memory used by CFE (around 4MB). That means cfe_*
	 * functions stop to work at some poपूर्णांक during the boot, we should only
	 * call them at the beginning of the boot.
	 *
	 * BCM47XX uses 128MB क्रम addressing the ram, अगर the प्रणाली contains
	 * less that that amount of ram it remaps the ram more often पूर्णांकo the
	 * available space.
	 */

	/* Physical address, without mapping to any kernel segment */
	off = CPHYSADDR((अचिन्हित दीर्घ)prom_init);

	/* Accessing memory after 128 MiB will cause an exception */
	max = 128 << 20;

	क्रम (mem = 1 << 20; mem < max; mem += 1 << 20) अणु
		/* Loop condition may be not enough, off may be over 1 MiB */
		अगर (off + mem >= max) अणु
			mem = max;
			pr_debug("Assume 128MB RAM\n");
			अवरोध;
		पूर्ण
		अगर (!स_भेद(prom_init, prom_init + mem, 32))
			अवरोध;
	पूर्ण
	lowmem = mem;

	/* Ignoring the last page when ddr size is 128M. Cached
	 * accesses to last page is causing the processor to prefetch
	 * using address above 128M stepping out of the ddr address
	 * space.
	 */
	अगर (c->cputype == CPU_74K && (mem == (128  << 20)))
		mem -= 0x1000;
	memblock_add(0, mem);
पूर्ण

/*
 * This is the first serial on the chip common core, it is at this position
 * क्रम sb (ssb) and ai (bcma) bus.
 */
#घोषणा BCM47XX_SERIAL_ADDR (SSB_ENUM_BASE + SSB_CHIPCO_UART0_DATA)

व्योम __init prom_init(व्योम)
अणु
	prom_init_mem();
	setup_8250_early_prपूर्णांकk_port(CKSEG1ADDR(BCM47XX_SERIAL_ADDR), 0, 0);
पूर्ण

#अगर defined(CONFIG_BCM47XX_BCMA) && defined(CONFIG_HIGHMEM)

#घोषणा EXTVBASE	0xc0000000
#घोषणा ENTRYLO(x)	((pte_val(pfn_pte((x) >> _PFN_SHIFT, PAGE_KERNEL_UNCACHED)) >> 6) | 1)

#समावेश <यंत्र/tlbflush.h>

/* Stripped version of tlb_init, with the call to build_tlb_refill_handler
 * dropped. Calling it at this stage causes a hang.
 */
व्योम early_tlb_init(व्योम)
अणु
	ग_लिखो_c0_pagemask(PM_DEFAULT_MASK);
	ग_लिखो_c0_wired(0);
	temp_tlb_entry = current_cpu_data.tlbsize - 1;
	local_flush_tlb_all();
पूर्ण

व्योम __init bcm47xx_prom_highmem_init(व्योम)
अणु
	अचिन्हित दीर्घ off = (अचिन्हित दीर्घ)prom_init;
	अचिन्हित दीर्घ exपंचांगem = 0;
	bool highmem_region = false;

	अगर (WARN_ON(bcm47xx_bus_type != BCM47XX_BUS_TYPE_BCMA))
		वापस;

	अगर (bcm47xx_bus.bcma.bus.chipinfo.id == BCMA_CHIP_ID_BCM4706)
		highmem_region = true;

	अगर (lowmem != 128 << 20 || !highmem_region)
		वापस;

	early_tlb_init();

	/* Add one temporary TLB entry to map SDRAM Region 2.
	 *      Physical        Virtual
	 *      0x80000000      0xc0000000      (1st: 256MB)
	 *      0x90000000      0xd0000000      (2nd: 256MB)
	 */
	add_temporary_entry(ENTRYLO(0x80000000),
			    ENTRYLO(0x80000000 + (256 << 20)),
			    EXTVBASE, PM_256M);

	off = EXTVBASE + __pa(off);
	क्रम (exपंचांगem = 128 << 20; exपंचांगem < 512 << 20; exपंचांगem <<= 1) अणु
		अगर (!स_भेद(prom_init, (व्योम *)(off + exपंचांगem), 16))
			अवरोध;
	पूर्ण
	exपंचांगem -= lowmem;

	early_tlb_init();

	अगर (!exपंचांगem)
		वापस;

	pr_warn("Found %lu MiB of extra memory, but highmem is unsupported yet!\n",
		exपंचांगem >> 20);

	/* TODO: Register extra memory */
पूर्ण

#पूर्ण_अगर /* defined(CONFIG_BCM47XX_BCMA) && defined(CONFIG_HIGHMEM) */
