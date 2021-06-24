<शैली गुरु>
/*
 * Copyright 2001 MontaVista Software Inc.
 * Author: MontaVista Software, Inc.
 *         	stevel@mvista.com or source@mvista.com
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

#समावेश <linux/types.h>
#समावेश <linux/pci.h>
#समावेश <linux/kernel.h>

#समावेश <यंत्र/mach-rc32434/rc32434.h>
#समावेश <यंत्र/mach-rc32434/irq.h>

अटल पूर्णांक irq_map[2][12] = अणु
	अणु0, 0, 2, 3, 2, 3, 0, 0, 0, 0, 0, 1पूर्ण,
	अणु0, 0, 1, 3, 0, 2, 1, 3, 0, 2, 1, 3पूर्ण
पूर्ण;

पूर्णांक pcibios_map_irq(स्थिर काष्ठा pci_dev *dev, u8 slot, u8 pin)
अणु
	पूर्णांक irq = 0;

	अगर (dev->bus->number < 2 && PCI_SLOT(dev->devfn) < 12)
		irq = irq_map[dev->bus->number][PCI_SLOT(dev->devfn)];

	वापस irq + GROUP4_IRQ_BASE + 4;
पूर्ण

अटल व्योम rc32434_pci_early_fixup(काष्ठा pci_dev *dev)
अणु
	अगर (PCI_SLOT(dev->devfn) == 6 && dev->bus->number == 0) अणु
		/* disable prefetched memory range */
		pci_ग_लिखो_config_word(dev, PCI_PREF_MEMORY_LIMIT, 0);
		pci_ग_लिखो_config_word(dev, PCI_PREF_MEMORY_BASE, 0x10);

		pci_ग_लिखो_config_byte(dev, PCI_CACHE_LINE_SIZE, 4);
	पूर्ण
पूर्ण

/*
 * The fixup applies to both the IDT and VIA devices present on the board
 */
DECLARE_PCI_FIXUP_HEADER(PCI_ANY_ID, PCI_ANY_ID, rc32434_pci_early_fixup);

/* Do platक्रमm specअगरic device initialization at pci_enable_device() समय */
पूर्णांक pcibios_plat_dev_init(काष्ठा pci_dev *dev)
अणु
	वापस 0;
पूर्ण
