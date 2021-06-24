<शैली गुरु>
/*
 * Copyright 2000, 2007-2008 MontaVista Software Inc.
 * Author: MontaVista Software, Inc. <source@mvista.com
 *
 * Updates to 2.6, Pete Popov, Embedded Alley Solutions, Inc.
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
#समावेश <linux/ioport.h>
#समावेश <linux/mm.h>
#समावेश <linux/dma-map-ops.h> /* क्रम dma_शेष_coherent */

#समावेश <यंत्र/mipsregs.h>

#समावेश <au1000.h>

बाह्य व्योम __init board_setup(व्योम);
बाह्य व्योम __init alchemy_set_lpj(व्योम);

अटल bool alchemy_dma_coherent(व्योम)
अणु
	चयन (alchemy_get_cputype()) अणु
	हाल ALCHEMY_CPU_AU1000:
	हाल ALCHEMY_CPU_AU1500:
	हाल ALCHEMY_CPU_AU1100:
		वापस false;
	हाल ALCHEMY_CPU_AU1200:
		/* Au1200 AB USB करोes not support coherent memory */
		अगर ((पढ़ो_c0_prid() & PRID_REV_MASK) == 0)
			वापस false;
		वापस true;
	शेष:
		वापस true;
	पूर्ण
पूर्ण

व्योम __init plat_mem_setup(व्योम)
अणु
	alchemy_set_lpj();

	अगर (au1xxx_cpu_needs_config_od())
		/* Various early Au1xx0 errata corrected by this */
		set_c0_config(1 << 19); /* Set Config[OD] */
	अन्यथा
		/* Clear to obtain best प्रणाली bus perक्रमmance */
		clear_c0_config(1 << 19); /* Clear Config[OD] */

	dma_शेष_coherent = alchemy_dma_coherent();

	board_setup();	/* board specअगरic setup */

	/* IO/MEM resources. */
	set_io_port_base(0);
	ioport_resource.start = IOPORT_RESOURCE_START;
	ioport_resource.end = IOPORT_RESOURCE_END;
	iomem_resource.start = IOMEM_RESOURCE_START;
	iomem_resource.end = IOMEM_RESOURCE_END;
पूर्ण

#अगर_घोषित CONFIG_MIPS_FIXUP_BIGPHYS_ADDR
/* This routine should be valid क्रम all Au1x based boards */
phys_addr_t fixup_bigphys_addr(phys_addr_t phys_addr, phys_addr_t size)
अणु
	अचिन्हित दीर्घ start = ALCHEMY_PCI_MEMWIN_START;
	अचिन्हित दीर्घ end = ALCHEMY_PCI_MEMWIN_END;

	/* Don't fixup 36-bit addresses */
	अगर ((phys_addr >> 32) != 0)
		वापस phys_addr;

	/* Check क्रम PCI memory winकरोw */
	अगर (phys_addr >= start && (phys_addr + size - 1) <= end)
		वापस (phys_addr_t)(AU1500_PCI_MEM_PHYS_ADDR + phys_addr);

	/* शेष nop */
	वापस phys_addr;
पूर्ण

पूर्णांक io_remap_pfn_range(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ vaddr,
		अचिन्हित दीर्घ pfn, अचिन्हित दीर्घ size, pgprot_t prot)
अणु
	phys_addr_t phys_addr = fixup_bigphys_addr(pfn << PAGE_SHIFT, size);

	वापस remap_pfn_range(vma, vaddr, phys_addr >> PAGE_SHIFT, size, prot);
पूर्ण
EXPORT_SYMBOL(io_remap_pfn_range);
#पूर्ण_अगर /* CONFIG_MIPS_FIXUP_BIGPHYS_ADDR */
