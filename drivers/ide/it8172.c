<शैली गुरु>
/*
 *
 * BRIEF MODULE DESCRIPTION
 *      IT8172 IDE controller support
 *
 * Copyright (C) 2000 MontaVista Software Inc.
 * Copyright (C) 2008 Shane McDonald
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

#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/ioport.h>
#समावेश <linux/pci.h>
#समावेश <linux/ide.h>
#समावेश <linux/init.h>

#घोषणा DRV_NAME "IT8172"

अटल व्योम it8172_set_pio_mode(ide_hwअगर_t *hwअगर, ide_drive_t *drive)
अणु
	काष्ठा pci_dev *dev	= to_pci_dev(hwअगर->dev);
	u16 drive_enables;
	u32 drive_timing;
	स्थिर u8 pio = drive->pio_mode - XFER_PIO_0;

	/*
	 * The highest value of DIOR/DIOW pulse width and recovery समय
	 * that can be set in the IT8172 is 8 PCI घड़ी cycles.  As a result,
	 * it cannot be configured क्रम PIO mode 0.  This table sets these
	 * parameters to the maximum supported by the IT8172.
	 */
	अटल स्थिर u8 timings[] = अणु 0x3f, 0x3c, 0x1b, 0x12, 0x0a पूर्ण;

	pci_पढ़ो_config_word(dev, 0x40, &drive_enables);
	pci_पढ़ो_config_dword(dev, 0x44, &drive_timing);

	/*
	 * Enable port 0x44. The IT8172 spec is confused; it calls
	 * this रेजिस्टर the "Slave IDE Timing Register", but in fact,
	 * it controls timing क्रम both master and slave drives.
	 */
	drive_enables |= 0x4000;

	drive_enables &= drive->dn ? 0xc006 : 0xc060;
	अगर (drive->media == ide_disk)
		/* enable prefetch */
		drive_enables |= 0x0004 << (drive->dn * 4);
	अगर (ide_pio_need_iordy(drive, pio))
		/* enable IORDY sample-poपूर्णांक */
		drive_enables |= 0x0002 << (drive->dn * 4);

	drive_timing &= drive->dn ? 0x00003f00 : 0x000fc000;
	drive_timing |= timings[pio] << (drive->dn * 6 + 8);

	pci_ग_लिखो_config_word(dev, 0x40, drive_enables);
	pci_ग_लिखो_config_dword(dev, 0x44, drive_timing);
पूर्ण

अटल व्योम it8172_set_dma_mode(ide_hwअगर_t *hwअगर, ide_drive_t *drive)
अणु
	काष्ठा pci_dev *dev	= to_pci_dev(hwअगर->dev);
	पूर्णांक a_speed		= 3 << (drive->dn * 4);
	पूर्णांक u_flag		= 1 << drive->dn;
	पूर्णांक u_speed		= 0;
	u8 reg48, reg4a;
	स्थिर u8 speed		= drive->dma_mode;

	pci_पढ़ो_config_byte(dev, 0x48, &reg48);
	pci_पढ़ो_config_byte(dev, 0x4a, &reg4a);

	अगर (speed >= XFER_UDMA_0) अणु
		u8 udma = speed - XFER_UDMA_0;
		u_speed = udma << (drive->dn * 4);

		pci_ग_लिखो_config_byte(dev, 0x48, reg48 | u_flag);
		reg4a &= ~a_speed;
		pci_ग_लिखो_config_byte(dev, 0x4a, reg4a | u_speed);
	पूर्ण अन्यथा अणु
		स्थिर u8 mwdma_to_pio[] = अणु 0, 3, 4 पूर्ण;

		pci_ग_लिखो_config_byte(dev, 0x48, reg48 & ~u_flag);
		pci_ग_लिखो_config_byte(dev, 0x4a, reg4a & ~a_speed);

		drive->pio_mode =
			mwdma_to_pio[speed - XFER_MW_DMA_0] + XFER_PIO_0;

		it8172_set_pio_mode(hwअगर, drive);
	पूर्ण
पूर्ण


अटल स्थिर काष्ठा ide_port_ops it8172_port_ops = अणु
	.set_pio_mode	= it8172_set_pio_mode,
	.set_dma_mode	= it8172_set_dma_mode,
पूर्ण;

अटल स्थिर काष्ठा ide_port_info it8172_port_info = अणु
	.name		= DRV_NAME,
	.port_ops	= &it8172_port_ops,
	.enablebits	= अणु अणु0x41, 0x80, 0x80पूर्ण, अणु0x00, 0x00, 0x00पूर्ण पूर्ण,
	.host_flags	= IDE_HFLAG_SINGLE,
	.pio_mask	= ATA_PIO4 & ~ATA_PIO0,
	.mwdma_mask	= ATA_MWDMA2,
	.udma_mask	= ATA_UDMA2,
पूर्ण;

अटल पूर्णांक it8172_init_one(काष्ठा pci_dev *dev, स्थिर काष्ठा pci_device_id *id)
अणु
	अगर ((dev->class >> 8) != PCI_CLASS_STORAGE_IDE)
		वापस -ENODEV; /* IT8172 is more than an IDE controller */
	वापस ide_pci_init_one(dev, &it8172_port_info, शून्य);
पूर्ण

अटल काष्ठा pci_device_id it8172_pci_tbl[] = अणु
	अणु PCI_VDEVICE(ITE, PCI_DEVICE_ID_ITE_8172), 0 पूर्ण,
	अणु 0, पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(pci, it8172_pci_tbl);

अटल काष्ठा pci_driver it8172_pci_driver = अणु
	.name		= "IT8172_IDE",
	.id_table	= it8172_pci_tbl,
	.probe		= it8172_init_one,
	.हटाओ		= ide_pci_हटाओ,
	.suspend	= ide_pci_suspend,
	.resume		= ide_pci_resume,
पूर्ण;

अटल पूर्णांक __init it8172_ide_init(व्योम)
अणु
	वापस ide_pci_रेजिस्टर_driver(&it8172_pci_driver);
पूर्ण

अटल व्योम __निकास it8172_ide_निकास(व्योम)
अणु
	pci_unरेजिस्टर_driver(&it8172_pci_driver);
पूर्ण

module_init(it8172_ide_init);
module_निकास(it8172_ide_निकास);

MODULE_AUTHOR("Steve Longerbeam");
MODULE_DESCRIPTION("PCI driver module for ITE 8172 IDE");
MODULE_LICENSE("GPL");
