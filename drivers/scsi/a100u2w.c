<शैली गुरु>
/*
 * Initio A100 device driver क्रम Linux.
 *
 * Copyright (c) 1994-1998 Initio Corporation
 * Copyright (c) 2003-2004 Christoph Hellwig
 * All rights reserved.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 *
 * You should have received a copy of the GNU General Public License
 * aदीर्घ with this program; see the file COPYING.  If not, ग_लिखो to
 * the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE FOR
 * ANY सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

/*
 * Revision History:
 * 07/02/98 hl	- v.91n Initial drivers.
 * 09/14/98 hl - v1.01 Support new Kernel.
 * 09/22/98 hl - v1.01a Support reset.
 * 09/24/98 hl - v1.01b Fixed reset.
 * 10/05/98 hl - v1.02 split the source code and release.
 * 12/19/98 bv - v1.02a Use spinlocks क्रम 2.1.95 and up
 * 01/31/99 bv - v1.02b Use mdelay instead of रुकोForPause
 * 08/08/99 bv - v1.02c Use रुकोForPause again.
 * 06/25/02 Doug Ledक्रमd <dledक्रमd@redhat.com> - v1.02d
 *          - Remove limit on number of controllers
 *          - Port to DMA mapping API
 *          - Clean up पूर्णांकerrupt handler registration
 *          - Fix memory leaks
 *          - Fix allocation of scsi host काष्ठाs and निजी data
 * 11/18/03 Christoph Hellwig <hch@lst.de>
 *	    - Port to new probing API
 *	    - Fix some more leaks in init failure हालs
 * 9/28/04 Christoph Hellwig <hch@lst.de>
 *	    - merge the two source files
 *	    - हटाओ पूर्णांकernal queueing code
 * 14/06/07 Alan Cox <alan@lxorguk.ukuu.org.uk>
 *	 - Gअक्रम cleanup and Linuxisation
 */

#समावेश <linux/module.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/pci.h>
#समावेश <linux/init.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/ioport.h>
#समावेश <linux/dma-mapping.h>

#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/irq.h>

#समावेश <scsi/scsi.h>
#समावेश <scsi/scsi_cmnd.h>
#समावेश <scsi/scsi_device.h>
#समावेश <scsi/scsi_host.h>

#समावेश "a100u2w.h"


अटल काष्ठा orc_scb *__orc_alloc_scb(काष्ठा orc_host * host);
अटल व्योम inia100_scb_handler(काष्ठा orc_host *host, काष्ठा orc_scb *scb);

अटल काष्ठा orc_nvram nvram, *nvramp = &nvram;

अटल u8 शेष_nvram[64] =
अणु
/*----------header -------------*/
	0x01,			/* 0x00: Sub System Venकरोr ID 0 */
	0x11,			/* 0x01: Sub System Venकरोr ID 1 */
	0x60,			/* 0x02: Sub System ID 0        */
	0x10,			/* 0x03: Sub System ID 1        */
	0x00,			/* 0x04: SubClass               */
	0x01,			/* 0x05: Venकरोr ID 0            */
	0x11,			/* 0x06: Venकरोr ID 1            */
	0x60,			/* 0x07: Device ID 0            */
	0x10,			/* 0x08: Device ID 1            */
	0x00,			/* 0x09: Reserved               */
	0x00,			/* 0x0A: Reserved               */
	0x01,			/* 0x0B: Revision of Data Structure     */
				/* -- Host Adapter Structure --- */
	0x01,			/* 0x0C: Number Of SCSI Channel */
	0x01,			/* 0x0D: BIOS Configuration 1   */
	0x00,			/* 0x0E: BIOS Configuration 2   */
	0x00,			/* 0x0F: BIOS Configuration 3   */
				/* --- SCSI Channel 0 Configuration --- */
	0x07,			/* 0x10: H/A ID                 */
	0x83,			/* 0x11: Channel Configuration  */
	0x20,			/* 0x12: MAX TAG per target     */
	0x0A,			/* 0x13: SCSI Reset Recovering समय     */
	0x00,			/* 0x14: Channel Configuration4 */
	0x00,			/* 0x15: Channel Configuration5 */
				/* SCSI Channel 0 Target Configuration  */
				/* 0x16-0x25                    */
	0xC8, 0xC8, 0xC8, 0xC8, 0xC8, 0xC8, 0xC8, 0xC8,
	0xC8, 0xC8, 0xC8, 0xC8, 0xC8, 0xC8, 0xC8, 0xC8,
				/* --- SCSI Channel 1 Configuration --- */
	0x07,			/* 0x26: H/A ID                 */
	0x83,			/* 0x27: Channel Configuration  */
	0x20,			/* 0x28: MAX TAG per target     */
	0x0A,			/* 0x29: SCSI Reset Recovering समय     */
	0x00,			/* 0x2A: Channel Configuration4 */
	0x00,			/* 0x2B: Channel Configuration5 */
				/* SCSI Channel 1 Target Configuration  */
				/* 0x2C-0x3B                    */
	0xC8, 0xC8, 0xC8, 0xC8, 0xC8, 0xC8, 0xC8, 0xC8,
	0xC8, 0xC8, 0xC8, 0xC8, 0xC8, 0xC8, 0xC8, 0xC8,
	0x00,			/* 0x3C: Reserved               */
	0x00,			/* 0x3D: Reserved               */
	0x00,			/* 0x3E: Reserved               */
	0x00			/* 0x3F: Checksum               */
पूर्ण;


अटल u8 रुको_chip_पढ़ोy(काष्ठा orc_host * host)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 10; i++) अणु	/* Wait 1 second क्रम report समयout     */
		अगर (inb(host->base + ORC_HCTRL) & HOSTSTOP)	/* Wait HOSTSTOP set */
			वापस 1;
		msleep(100);
	पूर्ण
	वापस 0;
पूर्ण

अटल u8 रुको_firmware_पढ़ोy(काष्ठा orc_host * host)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 10; i++) अणु	/* Wait 1 second क्रम report समयout     */
		अगर (inb(host->base + ORC_HSTUS) & RREADY)		/* Wait READY set */
			वापस 1;
		msleep(100);	/* रुको 100ms beक्रमe try again  */
	पूर्ण
	वापस 0;
पूर्ण

/***************************************************************************/
अटल u8 रुको_scsi_reset_करोne(काष्ठा orc_host * host)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 10; i++) अणु	/* Wait 1 second क्रम report समयout     */
		अगर (!(inb(host->base + ORC_HCTRL) & SCSIRST))	/* Wait SCSIRST करोne */
			वापस 1;
		mdelay(100);	/* रुको 100ms beक्रमe try again  */
	पूर्ण
	वापस 0;
पूर्ण

/***************************************************************************/
अटल u8 रुको_HDO_off(काष्ठा orc_host * host)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 10; i++) अणु	/* Wait 1 second क्रम report समयout     */
		अगर (!(inb(host->base + ORC_HCTRL) & HDO))		/* Wait HDO off */
			वापस 1;
		mdelay(100);	/* रुको 100ms beक्रमe try again  */
	पूर्ण
	वापस 0;
पूर्ण

/***************************************************************************/
अटल u8 रुको_hdi_set(काष्ठा orc_host * host, u8 * data)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 10; i++) अणु	/* Wait 1 second क्रम report समयout     */
		अगर ((*data = inb(host->base + ORC_HSTUS)) & HDI)
			वापस 1;	/* Wait HDI set */
		mdelay(100);	/* रुको 100ms beक्रमe try again  */
	पूर्ण
	वापस 0;
पूर्ण

/***************************************************************************/
अटल अचिन्हित लघु orc_पढ़ो_fwrev(काष्ठा orc_host * host)
अणु
	u16 version;
	u8 data;

	outb(ORC_CMD_VERSION, host->base + ORC_HDATA);
	outb(HDO, host->base + ORC_HCTRL);
	अगर (रुको_HDO_off(host) == 0)	/* Wait HDO off   */
		वापस 0;

	अगर (रुको_hdi_set(host, &data) == 0)	/* Wait HDI set   */
		वापस 0;
	version = inb(host->base + ORC_HDATA);
	outb(data, host->base + ORC_HSTUS);	/* Clear HDI            */

	अगर (रुको_hdi_set(host, &data) == 0)	/* Wait HDI set   */
		वापस 0;
	version |= inb(host->base + ORC_HDATA) << 8;
	outb(data, host->base + ORC_HSTUS);	/* Clear HDI            */

	वापस version;
पूर्ण

/***************************************************************************/
अटल u8 orc_nv_ग_लिखो(काष्ठा orc_host * host, अचिन्हित अक्षर address, अचिन्हित अक्षर value)
अणु
	outb(ORC_CMD_SET_NVM, host->base + ORC_HDATA);	/* Write command */
	outb(HDO, host->base + ORC_HCTRL);
	अगर (रुको_HDO_off(host) == 0)	/* Wait HDO off   */
		वापस 0;

	outb(address, host->base + ORC_HDATA);	/* Write address */
	outb(HDO, host->base + ORC_HCTRL);
	अगर (रुको_HDO_off(host) == 0)	/* Wait HDO off   */
		वापस 0;

	outb(value, host->base + ORC_HDATA);	/* Write value  */
	outb(HDO, host->base + ORC_HCTRL);
	अगर (रुको_HDO_off(host) == 0)	/* Wait HDO off   */
		वापस 0;

	वापस 1;
पूर्ण

/***************************************************************************/
अटल u8 orc_nv_पढ़ो(काष्ठा orc_host * host, u8 address, u8 *ptr)
अणु
	अचिन्हित अक्षर data;

	outb(ORC_CMD_GET_NVM, host->base + ORC_HDATA);	/* Write command */
	outb(HDO, host->base + ORC_HCTRL);
	अगर (रुको_HDO_off(host) == 0)	/* Wait HDO off   */
		वापस 0;

	outb(address, host->base + ORC_HDATA);	/* Write address */
	outb(HDO, host->base + ORC_HCTRL);
	अगर (रुको_HDO_off(host) == 0)	/* Wait HDO off   */
		वापस 0;

	अगर (रुको_hdi_set(host, &data) == 0)	/* Wait HDI set   */
		वापस 0;
	*ptr = inb(host->base + ORC_HDATA);
	outb(data, host->base + ORC_HSTUS);	/* Clear HDI    */

	वापस 1;

पूर्ण

/**
 *	orc_exec_scb		-	Queue an SCB with the HA
 *	@host: host adapter the SCB beदीर्घs to
 *	@scb: SCB to queue क्रम execution
 */

अटल व्योम orc_exec_scb(काष्ठा orc_host * host, काष्ठा orc_scb * scb)
अणु
	scb->status = ORCSCB_POST;
	outb(scb->scbidx, host->base + ORC_PQUEUE);
पूर्ण


/**
 *	se2_rd_all	-	पढ़ो SCSI parameters from EEPROM
 *	@host: Host whose EEPROM is being loaded
 *
 *	Read SCSI H/A configuration parameters from serial EEPROM
 */

अटल पूर्णांक se2_rd_all(काष्ठा orc_host * host)
अणु
	पूर्णांक i;
	u8 *np, chksum = 0;

	np = (u8 *) nvramp;
	क्रम (i = 0; i < 64; i++, np++) अणु	/* <01> */
		अगर (orc_nv_पढ़ो(host, (u8) i, np) == 0)
			वापस -1;
	पूर्ण

	/*------ Is ckecksum ok ? ------*/
	np = (u8 *) nvramp;
	क्रम (i = 0; i < 63; i++)
		chksum += *np++;

	अगर (nvramp->CheckSum != (u8) chksum)
		वापस -1;
	वापस 1;
पूर्ण

/**
 *	se2_update_all		-	update the EEPROM
 *	@host: Host whose EEPROM is being updated
 *
 *	Update changed bytes in the EEPROM image.
 */

अटल व्योम se2_update_all(काष्ठा orc_host * host)
अणु				/* setup शेष pattern  */
	पूर्णांक i;
	u8 *np, *np1, chksum = 0;

	/* Calculate checksum first   */
	np = (u8 *) शेष_nvram;
	क्रम (i = 0; i < 63; i++)
		chksum += *np++;
	*np = chksum;

	np = (u8 *) शेष_nvram;
	np1 = (u8 *) nvramp;
	क्रम (i = 0; i < 64; i++, np++, np1++) अणु
		अगर (*np != *np1)
			orc_nv_ग_लिखो(host, (u8) i, *np);
	पूर्ण
पूर्ण

/**
 *	पढ़ो_eeprom		-	load EEPROM
 *	@host: Host EEPROM to पढ़ो
 *
 *	Read the EEPROM क्रम a given host. If it is invalid or fails
 *	the restore the शेषs and use them.
 */

अटल व्योम पढ़ो_eeprom(काष्ठा orc_host * host)
अणु
	अगर (se2_rd_all(host) != 1) अणु
		se2_update_all(host);	/* setup शेष pattern        */
		se2_rd_all(host);	/* load again                   */
	पूर्ण
पूर्ण


/**
 *	orc_load_firmware	-	initialise firmware
 *	@host: Host to set up
 *
 *	Load the firmware from the EEPROM पूर्णांकo controller SRAM. This
 *	is basically a 4K block copy and then a 4K block पढ़ो to check
 *	correctness. The rest is convulted by the indirect पूर्णांकerfaces
 *	in the hardware
 */

अटल u8 orc_load_firmware(काष्ठा orc_host * host)
अणु
	u32 data32;
	u16 bios_addr;
	u16 i;
	u8 *data32_ptr, data;


	/* Set up the EEPROM क्रम access */

	data = inb(host->base + ORC_GCFG);
	outb(data | EEPRG, host->base + ORC_GCFG);	/* Enable EEPROM programming */
	outb(0x00, host->base + ORC_EBIOSADR2);
	outw(0x0000, host->base + ORC_EBIOSADR0);
	अगर (inb(host->base + ORC_EBIOSDATA) != 0x55) अणु
		outb(data, host->base + ORC_GCFG);	/* Disable EEPROM programming */
		वापस 0;
	पूर्ण
	outw(0x0001, host->base + ORC_EBIOSADR0);
	अगर (inb(host->base + ORC_EBIOSDATA) != 0xAA) अणु
		outb(data, host->base + ORC_GCFG);	/* Disable EEPROM programming */
		वापस 0;
	पूर्ण

	outb(PRGMRST | DOWNLOAD, host->base + ORC_RISCCTL);	/* Enable SRAM programming */
	data32_ptr = (u8 *) & data32;
	data32 = cpu_to_le32(0);		/* Initial FW address to 0 */
	outw(0x0010, host->base + ORC_EBIOSADR0);
	*data32_ptr = inb(host->base + ORC_EBIOSDATA);		/* Read from BIOS */
	outw(0x0011, host->base + ORC_EBIOSADR0);
	*(data32_ptr + 1) = inb(host->base + ORC_EBIOSDATA);	/* Read from BIOS */
	outw(0x0012, host->base + ORC_EBIOSADR0);
	*(data32_ptr + 2) = inb(host->base + ORC_EBIOSDATA);	/* Read from BIOS */
	outw(*(data32_ptr + 2), host->base + ORC_EBIOSADR2);
	outl(le32_to_cpu(data32), host->base + ORC_FWBASEADR);		/* Write FW address */

	/* Copy the code from the BIOS to the SRAM */

	udelay(500);	/* Required on Sun Ultra 5 ... 350 -> failures */
	bios_addr = (u16) le32_to_cpu(data32);	/* FW code locate at BIOS address + ? */
	क्रम (i = 0, data32_ptr = (u8 *) & data32;	/* Download the code    */
	     i < 0x1000;	/* Firmware code size = 4K      */
	     i++, bios_addr++) अणु
		outw(bios_addr, host->base + ORC_EBIOSADR0);
		*data32_ptr++ = inb(host->base + ORC_EBIOSDATA);	/* Read from BIOS */
		अगर ((i % 4) == 3) अणु
			outl(le32_to_cpu(data32), host->base + ORC_RISCRAM);	/* Write every 4 bytes */
			data32_ptr = (u8 *) & data32;
		पूर्ण
	पूर्ण

	/* Go back and check they match */

	outb(PRGMRST | DOWNLOAD, host->base + ORC_RISCCTL);	/* Reset program count 0 */
	bios_addr -= 0x1000;	/* Reset the BIOS address */
	क्रम (i = 0, data32_ptr = (u8 *) & data32;	/* Check the code       */
	     i < 0x1000;	/* Firmware code size = 4K      */
	     i++, bios_addr++) अणु
		outw(bios_addr, host->base + ORC_EBIOSADR0);
		*data32_ptr++ = inb(host->base + ORC_EBIOSDATA);	/* Read from BIOS */
		अगर ((i % 4) == 3) अणु
			अगर (inl(host->base + ORC_RISCRAM) != le32_to_cpu(data32)) अणु
				outb(PRGMRST, host->base + ORC_RISCCTL);	/* Reset program to 0 */
				outb(data, host->base + ORC_GCFG);	/*Disable EEPROM programming */
				वापस 0;
			पूर्ण
			data32_ptr = (u8 *) & data32;
		पूर्ण
	पूर्ण

	/* Success */
	outb(PRGMRST, host->base + ORC_RISCCTL);	/* Reset program to 0   */
	outb(data, host->base + ORC_GCFG);	/* Disable EEPROM programming */
	वापस 1;
पूर्ण

/***************************************************************************/
अटल व्योम setup_SCBs(काष्ठा orc_host * host)
अणु
	काष्ठा orc_scb *scb;
	पूर्णांक i;
	काष्ठा orc_extended_scb *escb;
	dma_addr_t escb_phys;

	/* Setup SCB base and SCB Size रेजिस्टरs */
	outb(ORC_MAXQUEUE, host->base + ORC_SCBSIZE);	/* Total number of SCBs */
	/* SCB base address 0      */
	outl(host->scb_phys, host->base + ORC_SCBBASE0);
	/* SCB base address 1      */
	outl(host->scb_phys, host->base + ORC_SCBBASE1);

	/* setup scatter list address with one buffer */
	scb = host->scb_virt;
	escb = host->escb_virt;

	क्रम (i = 0; i < ORC_MAXQUEUE; i++) अणु
		escb_phys = (host->escb_phys + (माप(काष्ठा orc_extended_scb) * i));
		scb->sg_addr = cpu_to_le32((u32) escb_phys);
		scb->sense_addr = cpu_to_le32((u32) escb_phys);
		scb->escb = escb;
		scb->scbidx = i;
		scb++;
		escb++;
	पूर्ण
पूर्ण

/**
 *	init_alloc_map		-	initialise allocation map
 *	@host: host map to configure
 *
 *	Initialise the allocation maps क्रम this device. If the device
 *	is not quiescent the caller must hold the allocation lock
 */

अटल व्योम init_alloc_map(काष्ठा orc_host * host)
अणु
	u8 i, j;

	क्रम (i = 0; i < MAX_CHANNELS; i++) अणु
		क्रम (j = 0; j < 8; j++) अणु
			host->allocation_map[i][j] = 0xffffffff;
		पूर्ण
	पूर्ण
पूर्ण

/**
 *	init_orchid		-	initialise the host adapter
 *	@host:host adapter to initialise
 *
 *	Initialise the controller and अगर necessary load the firmware.
 *
 *	Returns -1 अगर the initialisation fails.
 */

अटल पूर्णांक init_orchid(काष्ठा orc_host * host)
अणु
	u8 *ptr;
	u16 revision;
	u8 i;

	init_alloc_map(host);
	outb(0xFF, host->base + ORC_GIMSK);	/* Disable all पूर्णांकerrupts */

	अगर (inb(host->base + ORC_HSTUS) & RREADY) अणु	/* Orchid is पढ़ोy */
		revision = orc_पढ़ो_fwrev(host);
		अगर (revision == 0xFFFF) अणु
			outb(DEVRST, host->base + ORC_HCTRL);	/* Reset Host Adapter   */
			अगर (रुको_chip_पढ़ोy(host) == 0)
				वापस -1;
			orc_load_firmware(host);	/* Download FW                  */
			setup_SCBs(host);	/* Setup SCB base and SCB Size रेजिस्टरs */
			outb(0x00, host->base + ORC_HCTRL);	/* clear HOSTSTOP       */
			अगर (रुको_firmware_पढ़ोy(host) == 0)
				वापस -1;
			/* Wait क्रम firmware पढ़ोy     */
		पूर्ण अन्यथा अणु
			setup_SCBs(host);	/* Setup SCB base and SCB Size रेजिस्टरs */
		पूर्ण
	पूर्ण अन्यथा अणु		/* Orchid is not Ready          */
		outb(DEVRST, host->base + ORC_HCTRL);	/* Reset Host Adapter   */
		अगर (रुको_chip_पढ़ोy(host) == 0)
			वापस -1;
		orc_load_firmware(host);	/* Download FW                  */
		setup_SCBs(host);	/* Setup SCB base and SCB Size रेजिस्टरs */
		outb(HDO, host->base + ORC_HCTRL);	/* Do Hardware Reset &  */

		/*     clear HOSTSTOP  */
		अगर (रुको_firmware_पढ़ोy(host) == 0)		/* Wait क्रम firmware पढ़ोy      */
			वापस -1;
	पूर्ण

	/* Load an EEProm copy पूर्णांकo RAM */
	/* Assumes single thपढ़ोed at this poपूर्णांक */
	पढ़ो_eeprom(host);

	अगर (nvramp->revision != 1)
		वापस -1;

	host->scsi_id = nvramp->scsi_id;
	host->BIOScfg = nvramp->BIOSConfig1;
	host->max_tarमाला_लो = MAX_TARGETS;
	ptr = (u8 *) & (nvramp->Target00Config);
	क्रम (i = 0; i < 16; ptr++, i++) अणु
		host->target_flag[i] = *ptr;
		host->max_tags[i] = ORC_MAXTAGS;
	पूर्ण

	अगर (nvramp->SCSI0Config & NCC_BUSRESET)
		host->flags |= HCF_SCSI_RESET;
	outb(0xFB, host->base + ORC_GIMSK);	/* enable RP FIFO पूर्णांकerrupt     */
	वापस 0;
पूर्ण

/**
 *	orc_reset_scsi_bus		-	perक्रमm bus reset
 *	@host: host being reset
 *
 *	Perक्रमm a full bus reset on the adapter.
 */

अटल पूर्णांक orc_reset_scsi_bus(काष्ठा orc_host * host)
अणु				/* I need Host Control Block Inक्रमmation */
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&host->allocation_lock, flags);

	init_alloc_map(host);
	/* reset scsi bus */
	outb(SCSIRST, host->base + ORC_HCTRL);
	/* FIXME: We can spend up to a second with the lock held and
	   पूर्णांकerrupts off here */
	अगर (रुको_scsi_reset_करोne(host) == 0) अणु
		spin_unlock_irqrestore(&host->allocation_lock, flags);
		वापस FAILED;
	पूर्ण अन्यथा अणु
		spin_unlock_irqrestore(&host->allocation_lock, flags);
		वापस SUCCESS;
	पूर्ण
पूर्ण

/**
 *	orc_device_reset	-	device reset handler
 *	@host: host to reset
 *	@cmd: command causing the reset
 *	@target: target device
 *
 *	Reset रेजिस्टरs, reset a hanging bus and समाप्त active and disconnected
 *	commands क्रम target w/o soft reset
 */

अटल पूर्णांक orc_device_reset(काष्ठा orc_host * host, काष्ठा scsi_cmnd *cmd, अचिन्हित पूर्णांक target)
अणु				/* I need Host Control Block Inक्रमmation */
	काष्ठा orc_scb *scb;
	काष्ठा orc_extended_scb *escb;
	काष्ठा orc_scb *host_scb;
	u8 i;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&(host->allocation_lock), flags);
	scb = (काष्ठा orc_scb *) शून्य;
	escb = (काष्ठा orc_extended_scb *) शून्य;

	/* setup scatter list address with one buffer */
	host_scb = host->scb_virt;

	/* FIXME: is this safe अगर we then fail to issue the reset or race
	   a completion ? */
	init_alloc_map(host);

	/* Find the scb corresponding to the command */
	क्रम (i = 0; i < ORC_MAXQUEUE; i++) अणु
		escb = host_scb->escb;
		अगर (host_scb->status && escb->srb == cmd)
			अवरोध;
		host_scb++;
	पूर्ण

	अगर (i == ORC_MAXQUEUE) अणु
		prपूर्णांकk(KERN_ERR "Unable to Reset - No SCB Found\n");
		spin_unlock_irqrestore(&(host->allocation_lock), flags);
		वापस FAILED;
	पूर्ण

	/* Allocate a new SCB क्रम the reset command to the firmware */
	अगर ((scb = __orc_alloc_scb(host)) == शून्य) अणु
		/* Can't happen.. */
		spin_unlock_irqrestore(&(host->allocation_lock), flags);
		वापस FAILED;
	पूर्ण

	/* Reset device is handled by the firmware, we fill in an SCB and
	   fire it at the controller, it करोes the rest */
	scb->opcode = ORC_BUSDEVRST;
	scb->target = target;
	scb->hastat = 0;
	scb->tastat = 0;
	scb->status = 0x0;
	scb->link = 0xFF;
	scb->reserved0 = 0;
	scb->reserved1 = 0;
	scb->xferlen = cpu_to_le32(0);
	scb->sg_len = cpu_to_le32(0);

	escb->srb = शून्य;
	escb->srb = cmd;
	orc_exec_scb(host, scb);	/* Start execute SCB            */
	spin_unlock_irqrestore(&host->allocation_lock, flags);
	वापस SUCCESS;
पूर्ण

/**
 *	__orc_alloc_scb		-		allocate an SCB
 *	@host: host to allocate from
 *
 *	Allocate an SCB and वापस a poपूर्णांकer to the SCB object. शून्य
 *	is वापसed अगर no SCB is मुक्त. The caller must alपढ़ोy hold
 *	the allocator lock at this poपूर्णांक.
 */


अटल काष्ठा orc_scb *__orc_alloc_scb(काष्ठा orc_host * host)
अणु
	u8 channel;
	अचिन्हित दीर्घ idx;
	u8 index;
	u8 i;

	channel = host->index;
	क्रम (i = 0; i < 8; i++) अणु
		क्रम (index = 0; index < 32; index++) अणु
			अगर ((host->allocation_map[channel][i] >> index) & 0x01) अणु
				host->allocation_map[channel][i] &= ~(1 << index);
				idx = index + 32 * i;
				/*
				 * Translate the index to a काष्ठाure instance
				 */
				वापस host->scb_virt + idx;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस शून्य;
पूर्ण

/**
 *	orc_alloc_scb		-		allocate an SCB
 *	@host: host to allocate from
 *
 *	Allocate an SCB and वापस a poपूर्णांकer to the SCB object. शून्य
 *	is वापसed अगर no SCB is मुक्त.
 */

अटल काष्ठा orc_scb *orc_alloc_scb(काष्ठा orc_host * host)
अणु
	काष्ठा orc_scb *scb;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&host->allocation_lock, flags);
	scb = __orc_alloc_scb(host);
	spin_unlock_irqrestore(&host->allocation_lock, flags);
	वापस scb;
पूर्ण

/**
 *	orc_release_scb			-	release an SCB
 *	@host: host owning the SCB
 *	@scb: SCB that is now मुक्त
 *
 *	Called to वापस a completed SCB to the allocation pool. Beक्रमe
 *	calling the SCB must be out of use on both the host and the HA.
 */

अटल व्योम orc_release_scb(काष्ठा orc_host *host, काष्ठा orc_scb *scb)
अणु
	अचिन्हित दीर्घ flags;
	u8 index, i, channel;

	spin_lock_irqsave(&(host->allocation_lock), flags);
	channel = host->index;	/* Channel */
	index = scb->scbidx;
	i = index / 32;
	index %= 32;
	host->allocation_map[channel][i] |= (1 << index);
	spin_unlock_irqrestore(&(host->allocation_lock), flags);
पूर्ण

/*
 *	orchid_पात_scb	-	पात a command
 *
 *	Abort a queued command that has been passed to the firmware layer
 *	अगर possible. This is all handled by the firmware. We aks the firmware
 *	and it either पातs the command or fails
 */

अटल पूर्णांक orchid_पात_scb(काष्ठा orc_host * host, काष्ठा orc_scb * scb)
अणु
	अचिन्हित अक्षर data, status;

	outb(ORC_CMD_ABORT_SCB, host->base + ORC_HDATA);	/* Write command */
	outb(HDO, host->base + ORC_HCTRL);
	अगर (रुको_HDO_off(host) == 0)	/* Wait HDO off   */
		वापस 0;

	outb(scb->scbidx, host->base + ORC_HDATA);	/* Write address */
	outb(HDO, host->base + ORC_HCTRL);
	अगर (रुको_HDO_off(host) == 0)	/* Wait HDO off   */
		वापस 0;

	अगर (रुको_hdi_set(host, &data) == 0)	/* Wait HDI set   */
		वापस 0;
	status = inb(host->base + ORC_HDATA);
	outb(data, host->base + ORC_HSTUS);	/* Clear HDI    */

	अगर (status == 1)	/* 0 - Successfully               */
		वापस 0;	/* 1 - Fail                     */
	वापस 1;
पूर्ण

अटल पूर्णांक inia100_पात_cmd(काष्ठा orc_host * host, काष्ठा scsi_cmnd *cmd)
अणु
	काष्ठा orc_extended_scb *escb;
	काष्ठा orc_scb *scb;
	u8 i;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&(host->allocation_lock), flags);

	scb = host->scb_virt;

	/* Walk the queue until we find the SCB that beदीर्घs to the command
	   block. This isn't a perक्रमmance critical path so a walk in the park
	   here करोes no harm */

	क्रम (i = 0; i < ORC_MAXQUEUE; i++, scb++) अणु
		escb = scb->escb;
		अगर (scb->status && escb->srb == cmd) अणु
			अगर (scb->tag_msg == 0) अणु
				जाओ out;
			पूर्ण अन्यथा अणु
				/* Issue an ABORT to the firmware */
				अगर (orchid_पात_scb(host, scb)) अणु
					escb->srb = शून्य;
					spin_unlock_irqrestore(&host->allocation_lock, flags);
					वापस SUCCESS;
				पूर्ण अन्यथा
					जाओ out;
			पूर्ण
		पूर्ण
	पूर्ण
out:
	spin_unlock_irqrestore(&host->allocation_lock, flags);
	वापस FAILED;
पूर्ण

/**
 *	orc_पूर्णांकerrupt		-	IRQ processing
 *	@host: Host causing the पूर्णांकerrupt
 *
 *	This function is called from the IRQ handler and रक्षित
 *	by the host lock. While the controller reports that there are
 *	scb's क्रम processing we pull them off the controller, turn the
 *	index पूर्णांकo a host address poपूर्णांकer to the scb and call the scb
 *	handler.
 *
 *	Returns IRQ_HANDLED अगर any SCBs were processed, IRQ_NONE otherwise
 */

अटल irqवापस_t orc_पूर्णांकerrupt(काष्ठा orc_host * host)
अणु
	u8 scb_index;
	काष्ठा orc_scb *scb;

	/* Check अगर we have an SCB queued क्रम servicing */
	अगर (inb(host->base + ORC_RQUEUECNT) == 0)
		वापस IRQ_NONE;

	करो अणु
		/* Get the SCB index of the SCB to service */
		scb_index = inb(host->base + ORC_RQUEUE);

		/* Translate it back to a host poपूर्णांकer */
		scb = (काष्ठा orc_scb *) ((अचिन्हित दीर्घ) host->scb_virt + (अचिन्हित दीर्घ) (माप(काष्ठा orc_scb) * scb_index));
		scb->status = 0x0;
		/* Process the SCB */
		inia100_scb_handler(host, scb);
	पूर्ण जबतक (inb(host->base + ORC_RQUEUECNT));
	वापस IRQ_HANDLED;
पूर्ण				/* End of I1060Interrupt() */

/**
 *	inia100_build_scb	-	build SCB
 *	@host: host owing the control block
 *	@scb: control block to use
 *	@cmd: Mid layer command
 *
 *	Build a host adapter control block from the SCSI mid layer command
 */

अटल पूर्णांक inia100_build_scb(काष्ठा orc_host * host, काष्ठा orc_scb * scb, काष्ठा scsi_cmnd * cmd)
अणु				/* Create corresponding SCB     */
	काष्ठा scatterlist *sg;
	काष्ठा orc_sgent *sgent;		/* Poपूर्णांकer to SG list           */
	पूर्णांक i, count_sg;
	काष्ठा orc_extended_scb *escb;

	/* Links between the escb, scb and Linux scsi midlayer cmd */
	escb = scb->escb;
	escb->srb = cmd;
	sgent = शून्य;

	/* Set up the SCB to करो a SCSI command block */
	scb->opcode = ORC_EXECSCSI;
	scb->flags = SCF_NO_DCHK;	/* Clear करोne bit               */
	scb->target = cmd->device->id;
	scb->lun = cmd->device->lun;
	scb->reserved0 = 0;
	scb->reserved1 = 0;
	scb->sg_len = cpu_to_le32(0);

	scb->xferlen = cpu_to_le32((u32) scsi_bufflen(cmd));
	sgent = (काष्ठा orc_sgent *) & escb->sglist[0];

	count_sg = scsi_dma_map(cmd);
	अगर (count_sg < 0)
		वापस count_sg;
	BUG_ON(count_sg > TOTAL_SG_ENTRY);

	/* Build the scatter gather lists */
	अगर (count_sg) अणु
		scb->sg_len = cpu_to_le32((u32) (count_sg * 8));
		scsi_क्रम_each_sg(cmd, sg, count_sg, i) अणु
			sgent->base = cpu_to_le32((u32) sg_dma_address(sg));
			sgent->length = cpu_to_le32((u32) sg_dma_len(sg));
			sgent++;
		पूर्ण
	पूर्ण अन्यथा अणु
		scb->sg_len = cpu_to_le32(0);
		sgent->base = cpu_to_le32(0);
		sgent->length = cpu_to_le32(0);
	पूर्ण
	scb->sg_addr = (u32) scb->sense_addr;	/* sense_addr is alपढ़ोy little endian */
	scb->hastat = 0;
	scb->tastat = 0;
	scb->link = 0xFF;
	scb->sense_len = SENSE_SIZE;
	scb->cdb_len = cmd->cmd_len;
	अगर (scb->cdb_len >= IMAX_CDB) अणु
		prपूर्णांकk("max cdb length= %x\n", cmd->cmd_len);
		scb->cdb_len = IMAX_CDB;
	पूर्ण
	scb->ident = (u8)(cmd->device->lun & 0xff) | DISC_ALLOW;
	अगर (cmd->device->tagged_supported) अणु	/* Tag Support                  */
		scb->tag_msg = SIMPLE_QUEUE_TAG;	/* Do simple tag only   */
	पूर्ण अन्यथा अणु
		scb->tag_msg = 0;	/* No tag support               */
	पूर्ण
	स_नकल(scb->cdb, cmd->cmnd, scb->cdb_len);
	वापस 0;
पूर्ण

/**
 *	inia100_queue_lck		-	queue command with host
 *	@cmd: Command block
 *	@करोne: Completion function
 *
 *	Called by the mid layer to queue a command. Process the command
 *	block, build the host specअगरic scb काष्ठाures and अगर there is room
 *	queue the command करोwn to the controller
 */

अटल पूर्णांक inia100_queue_lck(काष्ठा scsi_cmnd * cmd, व्योम (*करोne) (काष्ठा scsi_cmnd *))
अणु
	काष्ठा orc_scb *scb;
	काष्ठा orc_host *host;		/* Poपूर्णांक to Host adapter control block */

	host = (काष्ठा orc_host *) cmd->device->host->hostdata;
	cmd->scsi_करोne = करोne;
	/* Get मुक्त SCSI control block  */
	अगर ((scb = orc_alloc_scb(host)) == शून्य)
		वापस SCSI_MLQUEUE_HOST_BUSY;

	अगर (inia100_build_scb(host, scb, cmd)) अणु
		orc_release_scb(host, scb);
		वापस SCSI_MLQUEUE_HOST_BUSY;
	पूर्ण
	orc_exec_scb(host, scb);	/* Start execute SCB            */
	वापस 0;
पूर्ण

अटल DEF_SCSI_QCMD(inia100_queue)

/*****************************************************************************
 Function name  : inia100_पात
 Description    : Abort a queued command.
	                 (commands that are on the bus can't be पातed easily)
 Input          : host  -       Poपूर्णांकer to host adapter काष्ठाure
 Output         : None.
 Return         : pSRB  -       Poपूर्णांकer to SCSI request block.
*****************************************************************************/
अटल पूर्णांक inia100_पात(काष्ठा scsi_cmnd * cmd)
अणु
	काष्ठा orc_host *host;

	host = (काष्ठा orc_host *) cmd->device->host->hostdata;
	वापस inia100_पात_cmd(host, cmd);
पूर्ण

/*****************************************************************************
 Function name  : inia100_reset
 Description    : Reset रेजिस्टरs, reset a hanging bus and
                  समाप्त active and disconnected commands क्रम target w/o soft reset
 Input          : host  -       Poपूर्णांकer to host adapter काष्ठाure
 Output         : None.
 Return         : pSRB  -       Poपूर्णांकer to SCSI request block.
*****************************************************************************/
अटल पूर्णांक inia100_bus_reset(काष्ठा scsi_cmnd * cmd)
अणु				/* I need Host Control Block Inक्रमmation */
	काष्ठा orc_host *host;
	host = (काष्ठा orc_host *) cmd->device->host->hostdata;
	वापस orc_reset_scsi_bus(host);
पूर्ण

/*****************************************************************************
 Function name  : inia100_device_reset
 Description    : Reset the device
 Input          : host  -       Poपूर्णांकer to host adapter काष्ठाure
 Output         : None.
 Return         : pSRB  -       Poपूर्णांकer to SCSI request block.
*****************************************************************************/
अटल पूर्णांक inia100_device_reset(काष्ठा scsi_cmnd * cmd)
अणु				/* I need Host Control Block Inक्रमmation */
	काष्ठा orc_host *host;
	host = (काष्ठा orc_host *) cmd->device->host->hostdata;
	वापस orc_device_reset(host, cmd, scmd_id(cmd));

पूर्ण

/**
 *	inia100_scb_handler	-	पूर्णांकerrupt callback
 *	@host: Host causing the पूर्णांकerrupt
 *	@scb: SCB the controller वापसed as needing processing
 *
 *	Perक्रमm completion processing on a control block. Do the conversions
 *	from host to SCSI midlayer error coding, save any sense data and
 *	the complete with the midlayer and recycle the scb.
 */

अटल व्योम inia100_scb_handler(काष्ठा orc_host *host, काष्ठा orc_scb *scb)
अणु
	काष्ठा scsi_cmnd *cmd;	/* Poपूर्णांकer to SCSI request block */
	काष्ठा orc_extended_scb *escb;

	escb = scb->escb;
	अगर ((cmd = (काष्ठा scsi_cmnd *) escb->srb) == शून्य) अणु
		prपूर्णांकk(KERN_ERR "inia100_scb_handler: SRB pointer is empty\n");
		orc_release_scb(host, scb);	/* Release SCB क्रम current channel */
		वापस;
	पूर्ण
	escb->srb = शून्य;

	चयन (scb->hastat) अणु
	हाल 0x0:
	हाल 0xa:		/* Linked command complete without error and linked normally */
	हाल 0xb:		/* Linked command complete without error पूर्णांकerrupt generated */
		scb->hastat = 0;
		अवरोध;

	हाल 0x11:		/* Selection समय out-The initiator selection or target
				   reselection was not complete within the SCSI Time out period */
		scb->hastat = DID_TIME_OUT;
		अवरोध;

	हाल 0x14:		/* Target bus phase sequence failure-An invalid bus phase or bus
				   phase sequence was requested by the target. The host adapter
				   will generate a SCSI Reset Condition, notअगरying the host with
				   a SCRD पूर्णांकerrupt */
		scb->hastat = DID_RESET;
		अवरोध;

	हाल 0x1a:		/* SCB Aborted. 07/21/98 */
		scb->hastat = DID_ABORT;
		अवरोध;

	हाल 0x12:		/* Data overrun/underrun-The target attempted to transfer more data
				   than was allocated by the Data Length field or the sum of the
				   Scatter / Gather Data Length fields. */
	हाल 0x13:		/* Unexpected bus मुक्त-The target dropped the SCSI BSY at an unexpected समय. */
	हाल 0x16:		/* Invalid CCB Operation Code-The first byte of the CCB was invalid. */

	शेष:
		prपूर्णांकk(KERN_DEBUG "inia100: %x %x\n", scb->hastat, scb->tastat);
		scb->hastat = DID_ERROR;	/* Couldn't find any better */
		अवरोध;
	पूर्ण

	अगर (scb->tastat == 2) अणु	/* Check condition              */
		स_नकल((अचिन्हित अक्षर *) &cmd->sense_buffer[0],
		   (अचिन्हित अक्षर *) &escb->sglist[0], SENSE_SIZE);
	पूर्ण
	cmd->result = scb->tastat | (scb->hastat << 16);
	scsi_dma_unmap(cmd);
	cmd->scsi_करोne(cmd);	/* Notअगरy प्रणाली DONE           */
	orc_release_scb(host, scb);	/* Release SCB क्रम current channel */
पूर्ण

/**
 *	inia100_पूर्णांकr		-	पूर्णांकerrupt handler
 *	@irqno: Interrupt value
 *	@devid: Host adapter
 *
 *	Entry poपूर्णांक क्रम IRQ handling. All the real work is perक्रमmed
 *	by orc_पूर्णांकerrupt.
 */
अटल irqवापस_t inia100_पूर्णांकr(पूर्णांक irqno, व्योम *devid)
अणु
	काष्ठा Scsi_Host *shost = (काष्ठा Scsi_Host *)devid;
	काष्ठा orc_host *host = (काष्ठा orc_host *)shost->hostdata;
	अचिन्हित दीर्घ flags;
	irqवापस_t res;

	spin_lock_irqsave(shost->host_lock, flags);
	res = orc_पूर्णांकerrupt(host);
	spin_unlock_irqrestore(shost->host_lock, flags);

	वापस res;
पूर्ण

अटल काष्ठा scsi_host_ढाँचा inia100_ढाँचा = अणु
	.proc_name		= "inia100",
	.name			= inia100_REVID,
	.queuecommand		= inia100_queue,
	.eh_पात_handler	= inia100_पात,
	.eh_bus_reset_handler	= inia100_bus_reset,
	.eh_device_reset_handler = inia100_device_reset,
	.can_queue		= 1,
	.this_id		= 1,
	.sg_tablesize		= SG_ALL,
पूर्ण;

अटल पूर्णांक inia100_probe_one(काष्ठा pci_dev *pdev,
			     स्थिर काष्ठा pci_device_id *id)
अणु
	काष्ठा Scsi_Host *shost;
	काष्ठा orc_host *host;
	अचिन्हित दीर्घ port, bios;
	पूर्णांक error = -ENODEV;
	u32 sz;

	अगर (pci_enable_device(pdev))
		जाओ out;
	अगर (dma_set_mask(&pdev->dev, DMA_BIT_MASK(32))) अणु
		prपूर्णांकk(KERN_WARNING "Unable to set 32bit DMA "
				    "on inia100 adapter, ignoring.\n");
		जाओ out_disable_device;
	पूर्ण

	pci_set_master(pdev);

	port = pci_resource_start(pdev, 0);
	अगर (!request_region(port, 256, "inia100")) अणु
		prपूर्णांकk(KERN_WARNING "inia100: io port 0x%lx, is busy.\n", port);
		जाओ out_disable_device;
	पूर्ण

	/* <02> पढ़ो from base address + 0x50 offset to get the bios value. */
	bios = inw(port + 0x50);


	shost = scsi_host_alloc(&inia100_ढाँचा, माप(काष्ठा orc_host));
	अगर (!shost)
		जाओ out_release_region;

	host = (काष्ठा orc_host *)shost->hostdata;
	host->pdev = pdev;
	host->base = port;
	host->BIOScfg = bios;
	spin_lock_init(&host->allocation_lock);

	/* Get total memory needed क्रम SCB */
	sz = ORC_MAXQUEUE * माप(काष्ठा orc_scb);
	host->scb_virt = dma_alloc_coherent(&pdev->dev, sz, &host->scb_phys,
					    GFP_KERNEL);
	अगर (!host->scb_virt) अणु
		prपूर्णांकk("inia100: SCB memory allocation error\n");
		जाओ out_host_put;
	पूर्ण

	/* Get total memory needed क्रम ESCB */
	sz = ORC_MAXQUEUE * माप(काष्ठा orc_extended_scb);
	host->escb_virt = dma_alloc_coherent(&pdev->dev, sz, &host->escb_phys,
					     GFP_KERNEL);
	अगर (!host->escb_virt) अणु
		prपूर्णांकk("inia100: ESCB memory allocation error\n");
		जाओ out_मुक्त_scb_array;
	पूर्ण

	अगर (init_orchid(host)) अणु	/* Initialize orchid chip */
		prपूर्णांकk("inia100: initial orchid fail!!\n");
		जाओ out_मुक्त_escb_array;
	पूर्ण

	shost->io_port = host->base;
	shost->n_io_port = 0xff;
	shost->can_queue = ORC_MAXQUEUE;
	shost->unique_id = shost->io_port;
	shost->max_id = host->max_tarमाला_लो;
	shost->max_lun = 16;
	shost->irq = pdev->irq;
	shost->this_id = host->scsi_id;	/* Assign HCS index */
	shost->sg_tablesize = TOTAL_SG_ENTRY;

	/* Initial orc chip           */
	error = request_irq(pdev->irq, inia100_पूर्णांकr, IRQF_SHARED,
			"inia100", shost);
	अगर (error < 0) अणु
		prपूर्णांकk(KERN_WARNING "inia100: unable to get irq %d\n",
				pdev->irq);
		जाओ out_मुक्त_escb_array;
	पूर्ण

	pci_set_drvdata(pdev, shost);

	error = scsi_add_host(shost, &pdev->dev);
	अगर (error)
		जाओ out_मुक्त_irq;

	scsi_scan_host(shost);
	वापस 0;

out_मुक्त_irq:
        मुक्त_irq(shost->irq, shost);
out_मुक्त_escb_array:
	dma_मुक्त_coherent(&pdev->dev,
			ORC_MAXQUEUE * माप(काष्ठा orc_extended_scb),
			host->escb_virt, host->escb_phys);
out_मुक्त_scb_array:
	dma_मुक्त_coherent(&pdev->dev,
			ORC_MAXQUEUE * माप(काष्ठा orc_scb),
			host->scb_virt, host->scb_phys);
out_host_put:
	scsi_host_put(shost);
out_release_region:
        release_region(port, 256);
out_disable_device:
	pci_disable_device(pdev);
out:
	वापस error;
पूर्ण

अटल व्योम inia100_हटाओ_one(काष्ठा pci_dev *pdev)
अणु
	काष्ठा Scsi_Host *shost = pci_get_drvdata(pdev);
	काष्ठा orc_host *host = (काष्ठा orc_host *)shost->hostdata;

	scsi_हटाओ_host(shost);

        मुक्त_irq(shost->irq, shost);
	dma_मुक्त_coherent(&pdev->dev,
			ORC_MAXQUEUE * माप(काष्ठा orc_extended_scb),
			host->escb_virt, host->escb_phys);
	dma_मुक्त_coherent(&pdev->dev,
			ORC_MAXQUEUE * माप(काष्ठा orc_scb),
			host->scb_virt, host->scb_phys);
        release_region(shost->io_port, 256);

	scsi_host_put(shost);
पूर्ण 

अटल काष्ठा pci_device_id inia100_pci_tbl[] = अणु
	अणुPCI_VENDOR_ID_INIT, 0x1060, PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0पूर्ण,
	अणु0,पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, inia100_pci_tbl);

अटल काष्ठा pci_driver inia100_pci_driver = अणु
	.name		= "inia100",
	.id_table	= inia100_pci_tbl,
	.probe		= inia100_probe_one,
	.हटाओ		= inia100_हटाओ_one,
पूर्ण;

module_pci_driver(inia100_pci_driver);

MODULE_DESCRIPTION("Initio A100U2W SCSI driver");
MODULE_AUTHOR("Initio Corporation");
MODULE_LICENSE("Dual BSD/GPL");
