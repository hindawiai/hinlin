<शैली गुरु>
/*
 *  Copyright (C) 2008 Aurelien Jarno <aurelien@aurel32.net>
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
#समावेश <linux/ssb/ssb.h>
#समावेश <linux/bcma/bcma.h>
#समावेश <bcm47xx.h>

पूर्णांक pcibios_map_irq(स्थिर काष्ठा pci_dev *dev, u8 slot, u8 pin)
अणु
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_BCM47XX_SSB
अटल पूर्णांक bcm47xx_pcibios_plat_dev_init_ssb(काष्ठा pci_dev *dev)
अणु
	पूर्णांक res;
	u8 slot, pin;

	res = ssb_pcibios_plat_dev_init(dev);
	अगर (res < 0) अणु
		prपूर्णांकk(KERN_ALERT "PCI: Failed to init device %s\n",
		       pci_name(dev));
		वापस res;
	पूर्ण

	pci_पढ़ो_config_byte(dev, PCI_INTERRUPT_PIN, &pin);
	slot = PCI_SLOT(dev->devfn);
	res = ssb_pcibios_map_irq(dev, slot, pin);

	/* IRQ-0 and IRQ-1 are software पूर्णांकerrupts. */
	अगर (res < 2) अणु
		prपूर्णांकk(KERN_ALERT "PCI: Failed to map IRQ of device %s\n",
		       pci_name(dev));
		वापस res;
	पूर्ण

	dev->irq = res;
	वापस 0;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_BCM47XX_BCMA
अटल पूर्णांक bcm47xx_pcibios_plat_dev_init_bcma(काष्ठा pci_dev *dev)
अणु
	पूर्णांक res;

	res = bcma_core_pci_plat_dev_init(dev);
	अगर (res < 0) अणु
		prपूर्णांकk(KERN_ALERT "PCI: Failed to init device %s\n",
		       pci_name(dev));
		वापस res;
	पूर्ण

	res = bcma_core_pci_pcibios_map_irq(dev);

	/* IRQ-0 and IRQ-1 are software पूर्णांकerrupts. */
	अगर (res < 2) अणु
		prपूर्णांकk(KERN_ALERT "PCI: Failed to map IRQ of device %s\n",
		       pci_name(dev));
		वापस res;
	पूर्ण

	dev->irq = res;
	वापस 0;
पूर्ण
#पूर्ण_अगर

पूर्णांक pcibios_plat_dev_init(काष्ठा pci_dev *dev)
अणु
#अगर_घोषित CONFIG_BCM47XX_SSB
	अगर (bcm47xx_bus_type ==	 BCM47XX_BUS_TYPE_SSB)
		वापस bcm47xx_pcibios_plat_dev_init_ssb(dev);
	अन्यथा
#पूर्ण_अगर
#अगर_घोषित CONFIG_BCM47XX_BCMA
	अगर  (bcm47xx_bus_type ==  BCM47XX_BUS_TYPE_BCMA)
		वापस bcm47xx_pcibios_plat_dev_init_bcma(dev);
	अन्यथा
#पूर्ण_अगर
		वापस 0;
पूर्ण
