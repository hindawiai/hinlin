<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later

/* NCR (or Symbios) 53c700 and 53c700-66 Driver
 *
 * Copyright (C) 2001 by James.Bottomley@HansenPartnership.com
**-----------------------------------------------------------------------------
**  
**
**-----------------------------------------------------------------------------
 */

/* Notes:
 *
 * This driver is deचिन्हित exclusively क्रम these chips (भवly the
 * earliest of the scripts engine chips).  They need their own drivers
 * because they are missing so many of the scripts and snazzy रेजिस्टर
 * features of their elder brothers (the 710, 720 and 770).
 *
 * The 700 is the lowliest of the line, it can only करो async SCSI.
 * The 700-66 can at least करो synchronous SCSI up to 10MHz.
 * 
 * The 700 chip has no host bus पूर्णांकerface logic of its own.  However,
 * it is usually mapped to a location with well defined रेजिस्टर
 * offsets.  Thereक्रमe, अगर you can determine the base address and the
 * irq your board incorporating this chip uses, you can probably use
 * this driver to run it (although you'll probably have to ग_लिखो a
 * minimal wrapper क्रम the purpose---see the NCR_D700 driver क्रम
 * details about how to करो this).
 *
 *
 * TODO List:
 *
 * 1. Better statistics in the proc fs
 *
 * 2. Implement message queue (queues SCSI messages like commands) and make
 *    the पात and device reset functions use them.
 * */

/* CHANGELOG
 *
 * Version 2.8
 *
 * Fixed bad bug affecting tag starvation processing (previously the
 * driver would hang the प्रणाली अगर too many tags starved.  Also fixed
 * bad bug having to करो with 10 byte command processing and REQUEST
 * SENSE (the command would loop क्रमever getting a transfer length
 * mismatch in the CMD phase).
 *
 * Version 2.7
 *
 * Fixed scripts problem which caused certain devices (notably CDRWs)
 * to hang on initial INQUIRY.  Updated NCR_700_पढ़ोl/ग_लिखोl to use
 * __raw_पढ़ोl/ग_लिखोl क्रम parisc compatibility (Thomas
 * Bogenकरोerfer). Added missing SCp->request_bufflen initialisation
 * क्रम sense requests (Ryan Bradetich).
 *
 * Version 2.6
 *
 * Following test of the 64 bit parisc kernel by Riअक्षरd Hirst,
 * several problems have now been corrected.  Also adds support क्रम
 * consistent memory allocation.
 *
 * Version 2.5
 * 
 * More Compatibility changes क्रम 710 (now actually works).  Enhanced
 * support क्रम odd घड़ी speeds which स्थिरrain SDTR negotiations.
 * correct cacheline separation क्रम scsi messages and status क्रम
 * incoherent architectures.  Use of the pci mapping functions on
 * buffers to begin support क्रम 64 bit drivers.
 *
 * Version 2.4
 *
 * Added support क्रम the 53c710 chip (in 53c700 emulation mode only---no 
 * special 53c710 inकाष्ठाions or रेजिस्टरs are used).
 *
 * Version 2.3
 *
 * More endianness/cache coherency changes.
 *
 * Better bad device handling (handles devices lying about tag
 * queueing support and devices which fail to provide sense data on
 * contingent allegiance conditions)
 *
 * Many thanks to Riअक्षरd Hirst <rhirst@linuxcare.com> क्रम patiently
 * debugging this driver on the parisc architecture and suggesting
 * many improvements and bug fixes.
 *
 * Thanks also go to Linuxcare Inc. क्रम providing several PARISC
 * machines क्रम me to debug the driver on.
 *
 * Version 2.2
 *
 * Made the driver mem or io mapped; added endian invariance; added
 * dma cache flushing operations क्रम architectures which need it;
 * added support क्रम more varied घड़ीing speeds.
 *
 * Version 2.1
 *
 * Initial modularisation from the D700.  See NCR_D700.c क्रम the rest of
 * the changelog.
 * */
#घोषणा NCR_700_VERSION "2.8"

#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/माला.स>
#समावेश <linux/slab.h>
#समावेश <linux/ioport.h>
#समावेश <linux/delay.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/completion.h>
#समावेश <linux/init.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/device.h>
#समावेश <linux/pgtable.h>
#समावेश <यंत्र/dma.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/byteorder.h>

#समावेश <scsi/scsi.h>
#समावेश <scsi/scsi_cmnd.h>
#समावेश <scsi/scsi_dbg.h>
#समावेश <scsi/scsi_eh.h>
#समावेश <scsi/scsi_host.h>
#समावेश <scsi/scsi_tcq.h>
#समावेश <scsi/scsi_transport.h>
#समावेश <scsi/scsi_transport_spi.h>

#समावेश "53c700.h"

/* NOTE: For 64 bit drivers there are poपूर्णांकs in the code where we use
 * a non dereferenceable poपूर्णांकer to poपूर्णांक to a काष्ठाure in dma-able
 * memory (which is 32 bits) so that we can use all of the काष्ठाure
 * operations but take the address at the end.  This macro allows us
 * to truncate the 64 bit poपूर्णांकer करोwn to 32 bits without the compiler
 * complaining */
#घोषणा to32bit(x)	((__u32)((अचिन्हित दीर्घ)(x)))

#अगर_घोषित NCR_700_DEBUG
#घोषणा STATIC
#अन्यथा
#घोषणा STATIC अटल
#पूर्ण_अगर

MODULE_AUTHOR("James Bottomley");
MODULE_DESCRIPTION("53c700 and 53c700-66 Driver");
MODULE_LICENSE("GPL");

/* This is the script */
#समावेश "53c700_d.h"


STATIC पूर्णांक NCR_700_queuecommand(काष्ठा Scsi_Host *h, काष्ठा scsi_cmnd *);
STATIC पूर्णांक NCR_700_पात(काष्ठा scsi_cmnd * SCpnt);
STATIC पूर्णांक NCR_700_host_reset(काष्ठा scsi_cmnd * SCpnt);
STATIC व्योम NCR_700_chip_setup(काष्ठा Scsi_Host *host);
STATIC व्योम NCR_700_chip_reset(काष्ठा Scsi_Host *host);
STATIC पूर्णांक NCR_700_slave_alloc(काष्ठा scsi_device *SDpnt);
STATIC पूर्णांक NCR_700_slave_configure(काष्ठा scsi_device *SDpnt);
STATIC व्योम NCR_700_slave_destroy(काष्ठा scsi_device *SDpnt);
अटल पूर्णांक NCR_700_change_queue_depth(काष्ठा scsi_device *SDpnt, पूर्णांक depth);

STATIC काष्ठा device_attribute *NCR_700_dev_attrs[];

STATIC काष्ठा scsi_transport_ढाँचा *NCR_700_transport_ढाँचा = शून्य;

अटल अक्षर *NCR_700_phase[] = अणु
	"",
	"after selection",
	"before command phase",
	"after command phase",
	"after status phase",
	"after data in phase",
	"after data out phase",
	"during data phase",
पूर्ण;

अटल अक्षर *NCR_700_condition[] = अणु
	"",
	"NOT MSG_OUT",
	"UNEXPECTED PHASE",
	"NOT MSG_IN",
	"UNEXPECTED MSG",
	"MSG_IN",
	"SDTR_MSG RECEIVED",
	"REJECT_MSG RECEIVED",
	"DISCONNECT_MSG RECEIVED",
	"MSG_OUT",
	"DATA_IN",
	
पूर्ण;

अटल अक्षर *NCR_700_fatal_messages[] = अणु
	"unexpected message after reselection",
	"still MSG_OUT after message injection",
	"not MSG_IN after selection",
	"Illegal message length received",
पूर्ण;

अटल अक्षर *NCR_700_SBCL_bits[] = अणु
	"IO ",
	"CD ",
	"MSG ",
	"ATN ",
	"SEL ",
	"BSY ",
	"ACK ",
	"REQ ",
पूर्ण;

अटल अक्षर *NCR_700_SBCL_to_phase[] = अणु
	"DATA_OUT",
	"DATA_IN",
	"CMD_OUT",
	"STATE",
	"ILLEGAL PHASE",
	"ILLEGAL PHASE",
	"MSG OUT",
	"MSG IN",
पूर्ण;

/* This translates the SDTR message offset and period to a value
 * which can be loaded पूर्णांकo the SXFER_REG.
 *
 * NOTE: According to SCSI-2, the true transfer period (in ns) is
 *       actually four बार this period value */
अटल अंतरभूत __u8
NCR_700_offset_period_to_sxfer(काष्ठा NCR_700_Host_Parameters *hostdata,
			       __u8 offset, __u8 period)
अणु
	पूर्णांक XFERP;

	__u8 min_xferp = (hostdata->chip710
			  ? NCR_710_MIN_XFERP : NCR_700_MIN_XFERP);
	__u8 max_offset = (hostdata->chip710
			   ? NCR_710_MAX_OFFSET : NCR_700_MAX_OFFSET);

	अगर(offset == 0)
		वापस 0;

	अगर(period < hostdata->min_period) अणु
		prपूर्णांकk(KERN_WARNING "53c700: Period %dns is less than this chip's minimum, setting to %d\n", period*4, NCR_700_MIN_PERIOD*4);
		period = hostdata->min_period;
	पूर्ण
	XFERP = (period*4 * hostdata->sync_घड़ी)/1000 - 4;
	अगर(offset > max_offset) अणु
		prपूर्णांकk(KERN_WARNING "53c700: Offset %d exceeds chip maximum, setting to %d\n",
		       offset, max_offset);
		offset = max_offset;
	पूर्ण
	अगर(XFERP < min_xferp) अणु
		XFERP =  min_xferp;
	पूर्ण
	वापस (offset & 0x0f) | (XFERP & 0x07)<<4;
पूर्ण

अटल अंतरभूत __u8
NCR_700_get_SXFER(काष्ठा scsi_device *SDp)
अणु
	काष्ठा NCR_700_Host_Parameters *hostdata = 
		(काष्ठा NCR_700_Host_Parameters *)SDp->host->hostdata[0];

	वापस NCR_700_offset_period_to_sxfer(hostdata,
					      spi_offset(SDp->sdev_target),
					      spi_period(SDp->sdev_target));
पूर्ण

अटल अंतरभूत dma_addr_t virt_to_dma(काष्ठा NCR_700_Host_Parameters *h, व्योम *p)
अणु
	वापस h->pScript + ((uपूर्णांकptr_t)p - (uपूर्णांकptr_t)h->script);
पूर्ण

अटल अंतरभूत व्योम dma_sync_to_dev(काष्ठा NCR_700_Host_Parameters *h,
		व्योम *addr, माप_प्रकार size)
अणु
	अगर (h->noncoherent)
		dma_sync_single_क्रम_device(h->dev, virt_to_dma(h, addr),
					   size, DMA_BIसूचीECTIONAL);
पूर्ण

अटल अंतरभूत व्योम dma_sync_from_dev(काष्ठा NCR_700_Host_Parameters *h,
		व्योम *addr, माप_प्रकार size)
अणु
	अगर (h->noncoherent)
		dma_sync_single_क्रम_device(h->dev, virt_to_dma(h, addr), size,
					   DMA_BIसूचीECTIONAL);
पूर्ण

काष्ठा Scsi_Host *
NCR_700_detect(काष्ठा scsi_host_ढाँचा *tpnt,
	       काष्ठा NCR_700_Host_Parameters *hostdata, काष्ठा device *dev)
अणु
	dma_addr_t pScript, pSlots;
	__u8 *memory;
	__u32 *script;
	काष्ठा Scsi_Host *host;
	अटल पूर्णांक banner = 0;
	पूर्णांक j;

	अगर(tpnt->sdev_attrs == शून्य)
		tpnt->sdev_attrs = NCR_700_dev_attrs;

	memory = dma_alloc_coherent(dev, TOTAL_MEM_SIZE, &pScript, GFP_KERNEL);
	अगर (!memory) अणु
		hostdata->noncoherent = 1;
		memory = dma_alloc_noncoherent(dev, TOTAL_MEM_SIZE, &pScript,
					 DMA_BIसूचीECTIONAL, GFP_KERNEL);
	पूर्ण
	अगर (!memory) अणु
		prपूर्णांकk(KERN_ERR "53c700: Failed to allocate memory for driver, detaching\n");
		वापस शून्य;
	पूर्ण

	script = (__u32 *)memory;
	hostdata->msgin = memory + MSGIN_OFFSET;
	hostdata->msgout = memory + MSGOUT_OFFSET;
	hostdata->status = memory + STATUS_OFFSET;
	hostdata->slots = (काष्ठा NCR_700_command_slot *)(memory + SLOTS_OFFSET);
	hostdata->dev = dev;

	pSlots = pScript + SLOTS_OFFSET;

	/* Fill in the missing routines from the host ढाँचा */
	tpnt->queuecommand = NCR_700_queuecommand;
	tpnt->eh_पात_handler = NCR_700_पात;
	tpnt->eh_host_reset_handler = NCR_700_host_reset;
	tpnt->can_queue = NCR_700_COMMAND_SLOTS_PER_HOST;
	tpnt->sg_tablesize = NCR_700_SG_SEGMENTS;
	tpnt->cmd_per_lun = NCR_700_CMD_PER_LUN;
	tpnt->slave_configure = NCR_700_slave_configure;
	tpnt->slave_destroy = NCR_700_slave_destroy;
	tpnt->slave_alloc = NCR_700_slave_alloc;
	tpnt->change_queue_depth = NCR_700_change_queue_depth;

	अगर(tpnt->name == शून्य)
		tpnt->name = "53c700";
	अगर(tpnt->proc_name == शून्य)
		tpnt->proc_name = "53c700";

	host = scsi_host_alloc(tpnt, 4);
	अगर (!host)
		वापस शून्य;
	स_रखो(hostdata->slots, 0, माप(काष्ठा NCR_700_command_slot)
	       * NCR_700_COMMAND_SLOTS_PER_HOST);
	क्रम (j = 0; j < NCR_700_COMMAND_SLOTS_PER_HOST; j++) अणु
		dma_addr_t offset = (dma_addr_t)((अचिन्हित दीर्घ)&hostdata->slots[j].SG[0]
					  - (अचिन्हित दीर्घ)&hostdata->slots[0].SG[0]);
		hostdata->slots[j].pSG = (काष्ठा NCR_700_SG_List *)((अचिन्हित दीर्घ)(pSlots + offset));
		अगर(j == 0)
			hostdata->मुक्त_list = &hostdata->slots[j];
		अन्यथा
			hostdata->slots[j-1].ITL_क्रमw = &hostdata->slots[j];
		hostdata->slots[j].state = NCR_700_SLOT_FREE;
	पूर्ण

	क्रम (j = 0; j < ARRAY_SIZE(SCRIPT); j++)
		script[j] = bS_to_host(SCRIPT[j]);

	/* adjust all labels to be bus physical */
	क्रम (j = 0; j < PATCHES; j++)
		script[LABELPATCHES[j]] = bS_to_host(pScript + SCRIPT[LABELPATCHES[j]]);
	/* now patch up fixed addresses. */
	script_patch_32(hostdata, script, MessageLocation,
			pScript + MSGOUT_OFFSET);
	script_patch_32(hostdata, script, StatusAddress,
			pScript + STATUS_OFFSET);
	script_patch_32(hostdata, script, ReceiveMsgAddress,
			pScript + MSGIN_OFFSET);

	hostdata->script = script;
	hostdata->pScript = pScript;
	dma_sync_single_क्रम_device(hostdata->dev, pScript, माप(SCRIPT), DMA_TO_DEVICE);
	hostdata->state = NCR_700_HOST_FREE;
	hostdata->cmd = शून्य;
	host->max_id = 8;
	host->max_lun = NCR_700_MAX_LUNS;
	BUG_ON(NCR_700_transport_ढाँचा == शून्य);
	host->transportt = NCR_700_transport_ढाँचा;
	host->unique_id = (अचिन्हित दीर्घ)hostdata->base;
	hostdata->eh_complete = शून्य;
	host->hostdata[0] = (अचिन्हित दीर्घ)hostdata;
	/* kick the chip */
	NCR_700_ग_लिखोb(0xff, host, CTEST9_REG);
	अगर (hostdata->chip710)
		hostdata->rev = (NCR_700_पढ़ोb(host, CTEST8_REG)>>4) & 0x0f;
	अन्यथा
		hostdata->rev = (NCR_700_पढ़ोb(host, CTEST7_REG)>>4) & 0x0f;
	hostdata->fast = (NCR_700_पढ़ोb(host, CTEST9_REG) == 0);
	अगर (banner == 0) अणु
		prपूर्णांकk(KERN_NOTICE "53c700: Version " NCR_700_VERSION " By James.Bottomley@HansenPartnership.com\n");
		banner = 1;
	पूर्ण
	prपूर्णांकk(KERN_NOTICE "scsi%d: %s rev %d %s\n", host->host_no,
	       hostdata->chip710 ? "53c710" :
	       (hostdata->fast ? "53c700-66" : "53c700"),
	       hostdata->rev, hostdata->dअगरferential ?
	       "(Differential)" : "");
	/* reset the chip */
	NCR_700_chip_reset(host);

	अगर (scsi_add_host(host, dev)) अणु
		dev_prपूर्णांकk(KERN_ERR, dev, "53c700: scsi_add_host failed\n");
		scsi_host_put(host);
		वापस शून्य;
	पूर्ण

	spi_संकेतling(host) = hostdata->dअगरferential ? SPI_SIGNAL_HVD :
		SPI_SIGNAL_SE;

	वापस host;
पूर्ण

पूर्णांक
NCR_700_release(काष्ठा Scsi_Host *host)
अणु
	काष्ठा NCR_700_Host_Parameters *hostdata = 
		(काष्ठा NCR_700_Host_Parameters *)host->hostdata[0];

	अगर (hostdata->noncoherent)
		dma_मुक्त_noncoherent(hostdata->dev, TOTAL_MEM_SIZE,
				hostdata->script, hostdata->pScript,
				DMA_BIसूचीECTIONAL);
	अन्यथा
		dma_मुक्त_coherent(hostdata->dev, TOTAL_MEM_SIZE,
				  hostdata->script, hostdata->pScript);
	वापस 1;
पूर्ण

अटल अंतरभूत __u8
NCR_700_identअगरy(पूर्णांक can_disconnect, __u8 lun)
अणु
	वापस IDENTIFY_BASE |
		((can_disconnect) ? 0x40 : 0) |
		(lun & NCR_700_LUN_MASK);
पूर्ण

/*
 * Function : अटल पूर्णांक data_residual (Scsi_Host *host)
 *
 * Purpose : वापस residual data count of what's in the chip.  If you
 * really want to know what this function is करोing, it's almost a
 * direct transcription of the algorithm described in the 53c710
 * guide, except that the DBC and DFIFO रेजिस्टरs are only 6 bits
 * wide on a 53c700.
 *
 * Inमाला_दो : host - SCSI host */
अटल अंतरभूत पूर्णांक
NCR_700_data_residual (काष्ठा Scsi_Host *host) अणु
	काष्ठा NCR_700_Host_Parameters *hostdata = 
		(काष्ठा NCR_700_Host_Parameters *)host->hostdata[0];
	पूर्णांक count, synchronous = 0;
	अचिन्हित पूर्णांक ddir;

	अगर(hostdata->chip710) अणु
		count = ((NCR_700_पढ़ोb(host, DFIFO_REG) & 0x7f) -
			 (NCR_700_पढ़ोl(host, DBC_REG) & 0x7f)) & 0x7f;
	पूर्ण अन्यथा अणु
		count = ((NCR_700_पढ़ोb(host, DFIFO_REG) & 0x3f) -
			 (NCR_700_पढ़ोl(host, DBC_REG) & 0x3f)) & 0x3f;
	पूर्ण
	
	अगर(hostdata->fast)
		synchronous = NCR_700_पढ़ोb(host, SXFER_REG) & 0x0f;
	
	/* get the data direction */
	ddir = NCR_700_पढ़ोb(host, CTEST0_REG) & 0x01;

	अगर (ddir) अणु
		/* Receive */
		अगर (synchronous) 
			count += (NCR_700_पढ़ोb(host, SSTAT2_REG) & 0xf0) >> 4;
		अन्यथा
			अगर (NCR_700_पढ़ोb(host, SSTAT1_REG) & SIDL_REG_FULL)
				++count;
	पूर्ण अन्यथा अणु
		/* Send */
		__u8 sstat = NCR_700_पढ़ोb(host, SSTAT1_REG);
		अगर (sstat & SODL_REG_FULL)
			++count;
		अगर (synchronous && (sstat & SODR_REG_FULL))
			++count;
	पूर्ण
#अगर_घोषित NCR_700_DEBUG
	अगर(count)
		prपूर्णांकk("RESIDUAL IS %d (ddir %d)\n", count, ddir);
#पूर्ण_अगर
	वापस count;
पूर्ण

/* prपूर्णांक out the SCSI wires and corresponding phase from the SBCL रेजिस्टर
 * in the chip */
अटल अंतरभूत अक्षर *
sbcl_to_string(__u8 sbcl)
अणु
	पूर्णांक i;
	अटल अक्षर ret[256];

	ret[0]='\0';
	क्रम(i=0; i<8; i++) अणु
		अगर((1<<i) & sbcl) 
			म_जोड़ो(ret, NCR_700_SBCL_bits[i]);
	पूर्ण
	म_जोड़ो(ret, NCR_700_SBCL_to_phase[sbcl & 0x07]);
	वापस ret;
पूर्ण

अटल अंतरभूत __u8
biपंचांगap_to_number(__u8 biपंचांगap)
अणु
	__u8 i;

	क्रम(i=0; i<8 && !(biपंचांगap &(1<<i)); i++)
		;
	वापस i;
पूर्ण

/* Pull a slot off the मुक्त list */
STATIC काष्ठा NCR_700_command_slot *
find_empty_slot(काष्ठा NCR_700_Host_Parameters *hostdata)
अणु
	काष्ठा NCR_700_command_slot *slot = hostdata->मुक्त_list;

	अगर(slot == शून्य) अणु
		/* sanity check */
		अगर(hostdata->command_slot_count != NCR_700_COMMAND_SLOTS_PER_HOST)
			prपूर्णांकk(KERN_ERR "SLOTS FULL, but count is %d, should be %d\n", hostdata->command_slot_count, NCR_700_COMMAND_SLOTS_PER_HOST);
		वापस शून्य;
	पूर्ण

	अगर(slot->state != NCR_700_SLOT_FREE)
		/* should panic! */
		prपूर्णांकk(KERN_ERR "BUSY SLOT ON FREE LIST!!!\n");
		

	hostdata->मुक्त_list = slot->ITL_क्रमw;
	slot->ITL_क्रमw = शून्य;


	/* NOTE: set the state to busy here, not queued, since this
	 * indicates the slot is in use and cannot be run by the IRQ
	 * finish routine.  If we cannot queue the command when it
	 * is properly build, we then change to NCR_700_SLOT_QUEUED */
	slot->state = NCR_700_SLOT_BUSY;
	slot->flags = 0;
	hostdata->command_slot_count++;
	
	वापस slot;
पूर्ण

STATIC व्योम 
मुक्त_slot(काष्ठा NCR_700_command_slot *slot,
	  काष्ठा NCR_700_Host_Parameters *hostdata)
अणु
	अगर((slot->state & NCR_700_SLOT_MASK) != NCR_700_SLOT_MAGIC) अणु
		prपूर्णांकk(KERN_ERR "53c700: SLOT %p is not MAGIC!!!\n", slot);
	पूर्ण
	अगर(slot->state == NCR_700_SLOT_FREE) अणु
		prपूर्णांकk(KERN_ERR "53c700: SLOT %p is FREE!!!\n", slot);
	पूर्ण
	
	slot->resume_offset = 0;
	slot->cmnd = शून्य;
	slot->state = NCR_700_SLOT_FREE;
	slot->ITL_क्रमw = hostdata->मुक्त_list;
	hostdata->मुक्त_list = slot;
	hostdata->command_slot_count--;
पूर्ण


/* This routine really करोes very little.  The command is indexed on
   the ITL and (अगर tagged) the ITLQ lists in _queuecommand */
STATIC व्योम
save_क्रम_reselection(काष्ठा NCR_700_Host_Parameters *hostdata,
		     काष्ठा scsi_cmnd *SCp, __u32 dsp)
अणु
	/* Its just possible that this माला_लो executed twice */
	अगर(SCp != शून्य) अणु
		काष्ठा NCR_700_command_slot *slot =
			(काष्ठा NCR_700_command_slot *)SCp->host_scribble;

		slot->resume_offset = dsp;
	पूर्ण
	hostdata->state = NCR_700_HOST_FREE;
	hostdata->cmd = शून्य;
पूर्ण

STATIC अंतरभूत व्योम
NCR_700_unmap(काष्ठा NCR_700_Host_Parameters *hostdata, काष्ठा scsi_cmnd *SCp,
	      काष्ठा NCR_700_command_slot *slot)
अणु
	अगर(SCp->sc_data_direction != DMA_NONE &&
	   SCp->sc_data_direction != DMA_BIसूचीECTIONAL)
		scsi_dma_unmap(SCp);
पूर्ण

STATIC अंतरभूत व्योम
NCR_700_scsi_करोne(काष्ठा NCR_700_Host_Parameters *hostdata,
	       काष्ठा scsi_cmnd *SCp, पूर्णांक result)
अणु
	hostdata->state = NCR_700_HOST_FREE;
	hostdata->cmd = शून्य;

	अगर(SCp != शून्य) अणु
		काष्ठा NCR_700_command_slot *slot =
			(काष्ठा NCR_700_command_slot *)SCp->host_scribble;

		dma_unmap_single(hostdata->dev, slot->pCmd,
				 MAX_COMMAND_SIZE, DMA_TO_DEVICE);
		अगर (slot->flags == NCR_700_FLAG_AUTOSENSE) अणु
			अक्षर *cmnd = NCR_700_get_sense_cmnd(SCp->device);

			dma_unmap_single(hostdata->dev, slot->dma_handle,
					 SCSI_SENSE_BUFFERSIZE, DMA_FROM_DEVICE);
			/* restore the old result अगर the request sense was
			 * successful */
			अगर (result == 0)
				result = cmnd[7];
			/* restore the original length */
			SCp->cmd_len = cmnd[8];
		पूर्ण अन्यथा
			NCR_700_unmap(hostdata, SCp, slot);

		मुक्त_slot(slot, hostdata);
#अगर_घोषित NCR_700_DEBUG
		अगर(NCR_700_get_depth(SCp->device) == 0 ||
		   NCR_700_get_depth(SCp->device) > SCp->device->queue_depth)
			prपूर्णांकk(KERN_ERR "Invalid depth in NCR_700_scsi_done(): %d\n",
			       NCR_700_get_depth(SCp->device));
#पूर्ण_अगर /* NCR_700_DEBUG */
		NCR_700_set_depth(SCp->device, NCR_700_get_depth(SCp->device) - 1);

		SCp->host_scribble = शून्य;
		SCp->result = result;
		SCp->scsi_करोne(SCp);
	पूर्ण अन्यथा अणु
		prपूर्णांकk(KERN_ERR "53c700: SCSI DONE HAS NULL SCp\n");
	पूर्ण
पूर्ण


STATIC व्योम
NCR_700_पूर्णांकernal_bus_reset(काष्ठा Scsi_Host *host)
अणु
	/* Bus reset */
	NCR_700_ग_लिखोb(ASSERT_RST, host, SCNTL1_REG);
	udelay(50);
	NCR_700_ग_लिखोb(0, host, SCNTL1_REG);

पूर्ण

STATIC व्योम
NCR_700_chip_setup(काष्ठा Scsi_Host *host)
अणु
	काष्ठा NCR_700_Host_Parameters *hostdata = 
		(काष्ठा NCR_700_Host_Parameters *)host->hostdata[0];
	__u8 min_period;
	__u8 min_xferp = (hostdata->chip710 ? NCR_710_MIN_XFERP : NCR_700_MIN_XFERP);

	अगर(hostdata->chip710) अणु
		__u8 burst_disable = 0;
		__u8 burst_length = 0;

		चयन (hostdata->burst_length) अणु
			हाल 1:
			        burst_length = BURST_LENGTH_1;
			        अवरोध;
			हाल 2:
			        burst_length = BURST_LENGTH_2;
			        अवरोध;
			हाल 4:
			        burst_length = BURST_LENGTH_4;
			        अवरोध;
			हाल 8:
			        burst_length = BURST_LENGTH_8;
			        अवरोध;
			शेष:
			        burst_disable = BURST_DISABLE;
			        अवरोध;
		पूर्ण
		hostdata->dcntl_extra |= COMPAT_700_MODE;

		NCR_700_ग_लिखोb(hostdata->dcntl_extra, host, DCNTL_REG);
		NCR_700_ग_लिखोb(burst_length | hostdata->dmode_extra,
			       host, DMODE_710_REG);
		NCR_700_ग_लिखोb(burst_disable | hostdata->ctest7_extra |
			       (hostdata->dअगरferential ? DIFF : 0),
			       host, CTEST7_REG);
		NCR_700_ग_लिखोb(BTB_TIMER_DISABLE, host, CTEST0_REG);
		NCR_700_ग_लिखोb(FULL_ARBITRATION | ENABLE_PARITY | PARITY
			       | AUTO_ATN, host, SCNTL0_REG);
	पूर्ण अन्यथा अणु
		NCR_700_ग_लिखोb(BURST_LENGTH_8 | hostdata->dmode_extra,
			       host, DMODE_700_REG);
		NCR_700_ग_लिखोb(hostdata->dअगरferential ? 
			       DIFF : 0, host, CTEST7_REG);
		अगर(hostdata->fast) अणु
			/* this is क्रम 700-66, करोes nothing on 700 */
			NCR_700_ग_लिखोb(LAST_DIS_ENBL | ENABLE_ACTIVE_NEGATION 
				       | GENERATE_RECEIVE_PARITY, host,
				       CTEST8_REG);
		पूर्ण अन्यथा अणु
			NCR_700_ग_लिखोb(FULL_ARBITRATION | ENABLE_PARITY
				       | PARITY | AUTO_ATN, host, SCNTL0_REG);
		पूर्ण
	पूर्ण

	NCR_700_ग_लिखोb(1 << host->this_id, host, SCID_REG);
	NCR_700_ग_लिखोb(0, host, SBCL_REG);
	NCR_700_ग_लिखोb(ASYNC_OPERATION, host, SXFER_REG);

	NCR_700_ग_लिखोb(PHASE_MM_INT | SEL_TIMEOUT_INT | GROSS_ERR_INT | UX_DISC_INT
	     | RST_INT | PAR_ERR_INT | SELECT_INT, host, SIEN_REG);

	NCR_700_ग_लिखोb(ABORT_INT | INT_INST_INT | ILGL_INST_INT, host, DIEN_REG);
	NCR_700_ग_लिखोb(ENABLE_SELECT, host, SCNTL1_REG);
	अगर(hostdata->घड़ी > 75) अणु
		prपूर्णांकk(KERN_ERR "53c700: Clock speed %dMHz is too high: 75Mhz is the maximum this chip can be driven at\n", hostdata->घड़ी);
		/* करो the best we can, but the async घड़ी will be out
		 * of spec: sync भागider 2, async भागider 3 */
		DEBUG(("53c700: sync 2 async 3\n"));
		NCR_700_ग_लिखोb(SYNC_DIV_2_0, host, SBCL_REG);
		NCR_700_ग_लिखोb(ASYNC_DIV_3_0 | hostdata->dcntl_extra, host, DCNTL_REG);
		hostdata->sync_घड़ी = hostdata->घड़ी/2;
	पूर्ण अन्यथा	अगर(hostdata->घड़ी > 50  && hostdata->घड़ी <= 75) अणु
		/* sync भागider 1.5, async भागider 3 */
		DEBUG(("53c700: sync 1.5 async 3\n"));
		NCR_700_ग_लिखोb(SYNC_DIV_1_5, host, SBCL_REG);
		NCR_700_ग_लिखोb(ASYNC_DIV_3_0 | hostdata->dcntl_extra, host, DCNTL_REG);
		hostdata->sync_घड़ी = hostdata->घड़ी*2;
		hostdata->sync_घड़ी /= 3;
		
	पूर्ण अन्यथा अगर(hostdata->घड़ी > 37 && hostdata->घड़ी <= 50) अणु
		/* sync भागider 1, async भागider 2 */
		DEBUG(("53c700: sync 1 async 2\n"));
		NCR_700_ग_लिखोb(SYNC_DIV_1_0, host, SBCL_REG);
		NCR_700_ग_लिखोb(ASYNC_DIV_2_0 | hostdata->dcntl_extra, host, DCNTL_REG);
		hostdata->sync_घड़ी = hostdata->घड़ी;
	पूर्ण अन्यथा अगर(hostdata->घड़ी > 25 && hostdata->घड़ी <=37) अणु
		/* sync भागider 1, async भागider 1.5 */
		DEBUG(("53c700: sync 1 async 1.5\n"));
		NCR_700_ग_लिखोb(SYNC_DIV_1_0, host, SBCL_REG);
		NCR_700_ग_लिखोb(ASYNC_DIV_1_5 | hostdata->dcntl_extra, host, DCNTL_REG);
		hostdata->sync_घड़ी = hostdata->घड़ी;
	पूर्ण अन्यथा अणु
		DEBUG(("53c700: sync 1 async 1\n"));
		NCR_700_ग_लिखोb(SYNC_DIV_1_0, host, SBCL_REG);
		NCR_700_ग_लिखोb(ASYNC_DIV_1_0 | hostdata->dcntl_extra, host, DCNTL_REG);
		/* sync भागider 1, async भागider 1 */
		hostdata->sync_घड़ी = hostdata->घड़ी;
	पूर्ण
	/* Calculate the actual minimum period that can be supported
	 * by our synchronous घड़ी speed.  See the 710 manual क्रम
	 * exact details of this calculation which is based on a
	 * setting of the SXFER रेजिस्टर */
	min_period = 1000*(4+min_xferp)/(4*hostdata->sync_घड़ी);
	hostdata->min_period = NCR_700_MIN_PERIOD;
	अगर(min_period > NCR_700_MIN_PERIOD)
		hostdata->min_period = min_period;
पूर्ण

STATIC व्योम
NCR_700_chip_reset(काष्ठा Scsi_Host *host)
अणु
	काष्ठा NCR_700_Host_Parameters *hostdata = 
		(काष्ठा NCR_700_Host_Parameters *)host->hostdata[0];
	अगर(hostdata->chip710) अणु
		NCR_700_ग_लिखोb(SOFTWARE_RESET_710, host, ISTAT_REG);
		udelay(100);

		NCR_700_ग_लिखोb(0, host, ISTAT_REG);
	पूर्ण अन्यथा अणु
		NCR_700_ग_लिखोb(SOFTWARE_RESET, host, DCNTL_REG);
		udelay(100);
		
		NCR_700_ग_लिखोb(0, host, DCNTL_REG);
	पूर्ण

	mdelay(1000);

	NCR_700_chip_setup(host);
पूर्ण

/* The heart of the message processing engine is that the inकाष्ठाion
 * immediately after the INT is the normal हाल (and so must be CLEAR
 * ACK).  If we want to करो something अन्यथा, we call that routine in
 * scripts and set temp to be the normal हाल + 8 (skipping the CLEAR
 * ACK) so that the routine वापसs correctly to resume its activity
 * */
STATIC __u32
process_extended_message(काष्ठा Scsi_Host *host, 
			 काष्ठा NCR_700_Host_Parameters *hostdata,
			 काष्ठा scsi_cmnd *SCp, __u32 dsp, __u32 dsps)
अणु
	__u32 resume_offset = dsp, temp = dsp + 8;
	__u8 pun = 0xff, lun = 0xff;

	अगर(SCp != शून्य) अणु
		pun = SCp->device->id;
		lun = SCp->device->lun;
	पूर्ण

	चयन(hostdata->msgin[2]) अणु
	हाल A_SDTR_MSG:
		अगर(SCp != शून्य && NCR_700_is_flag_set(SCp->device, NCR_700_DEV_BEGIN_SYNC_NEGOTIATION)) अणु
			काष्ठा scsi_target *starget = SCp->device->sdev_target;
			__u8 period = hostdata->msgin[3];
			__u8 offset = hostdata->msgin[4];

			अगर(offset == 0 || period == 0) अणु
				offset = 0;
				period = 0;
			पूर्ण

			spi_offset(starget) = offset;
			spi_period(starget) = period;
			
			अगर(NCR_700_is_flag_set(SCp->device, NCR_700_DEV_PRINT_SYNC_NEGOTIATION)) अणु
				spi_display_xfer_agreement(starget);
				NCR_700_clear_flag(SCp->device, NCR_700_DEV_PRINT_SYNC_NEGOTIATION);
			पूर्ण
			
			NCR_700_set_flag(SCp->device, NCR_700_DEV_NEGOTIATED_SYNC);
			NCR_700_clear_flag(SCp->device, NCR_700_DEV_BEGIN_SYNC_NEGOTIATION);
			
			NCR_700_ग_लिखोb(NCR_700_get_SXFER(SCp->device),
				       host, SXFER_REG);

		पूर्ण अन्यथा अणु
			/* SDTR message out of the blue, reject it */
			shost_prपूर्णांकk(KERN_WARNING, host,
				"Unexpected SDTR msg\n");
			hostdata->msgout[0] = A_REJECT_MSG;
			dma_sync_to_dev(hostdata, hostdata->msgout, 1);
			script_patch_16(hostdata, hostdata->script,
			                MessageCount, 1);
			/* SendMsgOut वापसs, so set up the वापस
			 * address */
			resume_offset = hostdata->pScript + Ent_SendMessageWithATN;
		पूर्ण
		अवरोध;
	
	हाल A_WDTR_MSG:
		prपूर्णांकk(KERN_INFO "scsi%d: (%d:%d), Unsolicited WDTR after CMD, Rejecting\n",
		       host->host_no, pun, lun);
		hostdata->msgout[0] = A_REJECT_MSG;
		dma_sync_to_dev(hostdata, hostdata->msgout, 1);
		script_patch_16(hostdata, hostdata->script, MessageCount, 1);
		resume_offset = hostdata->pScript + Ent_SendMessageWithATN;

		अवरोध;

	शेष:
		prपूर्णांकk(KERN_INFO "scsi%d (%d:%d): Unexpected message %s: ",
		       host->host_no, pun, lun,
		       NCR_700_phase[(dsps & 0xf00) >> 8]);
		spi_prपूर्णांक_msg(hostdata->msgin);
		prपूर्णांकk("\n");
		/* just reject it */
		hostdata->msgout[0] = A_REJECT_MSG;
		dma_sync_to_dev(hostdata, hostdata->msgout, 1);
		script_patch_16(hostdata, hostdata->script, MessageCount, 1);
		/* SendMsgOut वापसs, so set up the वापस
		 * address */
		resume_offset = hostdata->pScript + Ent_SendMessageWithATN;
	पूर्ण
	NCR_700_ग_लिखोl(temp, host, TEMP_REG);
	वापस resume_offset;
पूर्ण

STATIC __u32
process_message(काष्ठा Scsi_Host *host,	काष्ठा NCR_700_Host_Parameters *hostdata,
		काष्ठा scsi_cmnd *SCp, __u32 dsp, __u32 dsps)
अणु
	/* work out where to वापस to */
	__u32 temp = dsp + 8, resume_offset = dsp;
	__u8 pun = 0xff, lun = 0xff;

	अगर(SCp != शून्य) अणु
		pun = SCp->device->id;
		lun = SCp->device->lun;
	पूर्ण

#अगर_घोषित NCR_700_DEBUG
	prपूर्णांकk("scsi%d (%d:%d): message %s: ", host->host_no, pun, lun,
	       NCR_700_phase[(dsps & 0xf00) >> 8]);
	spi_prपूर्णांक_msg(hostdata->msgin);
	prपूर्णांकk("\n");
#पूर्ण_अगर

	चयन(hostdata->msgin[0]) अणु

	हाल A_EXTENDED_MSG:
		resume_offset =  process_extended_message(host, hostdata, SCp,
							  dsp, dsps);
		अवरोध;

	हाल A_REJECT_MSG:
		अगर(SCp != शून्य && NCR_700_is_flag_set(SCp->device, NCR_700_DEV_BEGIN_SYNC_NEGOTIATION)) अणु
			/* Rejected our sync negotiation attempt */
			spi_period(SCp->device->sdev_target) =
				spi_offset(SCp->device->sdev_target) = 0;
			NCR_700_set_flag(SCp->device, NCR_700_DEV_NEGOTIATED_SYNC);
			NCR_700_clear_flag(SCp->device, NCR_700_DEV_BEGIN_SYNC_NEGOTIATION);
		पूर्ण अन्यथा अगर(SCp != शून्य && NCR_700_get_tag_neg_state(SCp->device) == NCR_700_DURING_TAG_NEGOTIATION) अणु
			/* rejected our first simple tag message */
			scmd_prपूर्णांकk(KERN_WARNING, SCp,
				"Rejected first tag queue attempt, turning off tag queueing\n");
			/* we're करोne negotiating */
			NCR_700_set_tag_neg_state(SCp->device, NCR_700_FINISHED_TAG_NEGOTIATION);
			hostdata->tag_negotiated &= ~(1<<scmd_id(SCp));

			SCp->device->tagged_supported = 0;
			SCp->device->simple_tags = 0;
			scsi_change_queue_depth(SCp->device, host->cmd_per_lun);
		पूर्ण अन्यथा अणु
			shost_prपूर्णांकk(KERN_WARNING, host,
				"(%d:%d) Unexpected REJECT Message %s\n",
			       pun, lun,
			       NCR_700_phase[(dsps & 0xf00) >> 8]);
			/* however, just ignore it */
		पूर्ण
		अवरोध;

	हाल A_PARITY_ERROR_MSG:
		prपूर्णांकk(KERN_ERR "scsi%d (%d:%d) Parity Error!\n", host->host_no,
		       pun, lun);
		NCR_700_पूर्णांकernal_bus_reset(host);
		अवरोध;
	हाल A_SIMPLE_TAG_MSG:
		prपूर्णांकk(KERN_INFO "scsi%d (%d:%d) SIMPLE TAG %d %s\n", host->host_no,
		       pun, lun, hostdata->msgin[1],
		       NCR_700_phase[(dsps & 0xf00) >> 8]);
		/* just ignore it */
		अवरोध;
	शेष:
		prपूर्णांकk(KERN_INFO "scsi%d (%d:%d): Unexpected message %s: ",
		       host->host_no, pun, lun,
		       NCR_700_phase[(dsps & 0xf00) >> 8]);

		spi_prपूर्णांक_msg(hostdata->msgin);
		prपूर्णांकk("\n");
		/* just reject it */
		hostdata->msgout[0] = A_REJECT_MSG;
		dma_sync_to_dev(hostdata, hostdata->msgout, 1);
		script_patch_16(hostdata, hostdata->script, MessageCount, 1);
		/* SendMsgOut वापसs, so set up the वापस
		 * address */
		resume_offset = hostdata->pScript + Ent_SendMessageWithATN;

		अवरोध;
	पूर्ण
	NCR_700_ग_लिखोl(temp, host, TEMP_REG);
	/* set us up to receive another message */
	dma_sync_from_dev(hostdata, hostdata->msgin, MSG_ARRAY_SIZE);
	वापस resume_offset;
पूर्ण

STATIC __u32
process_script_पूर्णांकerrupt(__u32 dsps, __u32 dsp, काष्ठा scsi_cmnd *SCp,
			 काष्ठा Scsi_Host *host,
			 काष्ठा NCR_700_Host_Parameters *hostdata)
अणु
	__u32 resume_offset = 0;
	__u8 pun = 0xff, lun=0xff;

	अगर(SCp != शून्य) अणु
		pun = SCp->device->id;
		lun = SCp->device->lun;
	पूर्ण

	अगर(dsps == A_GOOD_STATUS_AFTER_STATUS) अणु
		DEBUG(("  COMMAND COMPLETE, status=%02x\n",
		       hostdata->status[0]));
		/* OK, अगर TCQ still under negotiation, we now know it works */
		अगर (NCR_700_get_tag_neg_state(SCp->device) == NCR_700_DURING_TAG_NEGOTIATION)
			NCR_700_set_tag_neg_state(SCp->device,
						  NCR_700_FINISHED_TAG_NEGOTIATION);
			
		/* check क्रम contingent allegiance conditions */
		अगर (hostdata->status[0] >> 1 == CHECK_CONDITION ||
		    hostdata->status[0] >> 1 == COMMAND_TERMINATED) अणु
			काष्ठा NCR_700_command_slot *slot =
				(काष्ठा NCR_700_command_slot *)SCp->host_scribble;
			अगर(slot->flags == NCR_700_FLAG_AUTOSENSE) अणु
				/* OOPS: bad device, वापसing another
				 * contingent allegiance condition */
				scmd_prपूर्णांकk(KERN_ERR, SCp,
					"broken device is looping in contingent allegiance: ignoring\n");
				NCR_700_scsi_करोne(hostdata, SCp, hostdata->status[0]);
			पूर्ण अन्यथा अणु
				अक्षर *cmnd =
					NCR_700_get_sense_cmnd(SCp->device);
#अगर_घोषित NCR_DEBUG
				scsi_prपूर्णांक_command(SCp);
				prपूर्णांकk("  cmd %p has status %d, requesting sense\n",
				       SCp, hostdata->status[0]);
#पूर्ण_अगर
				/* we can destroy the command here
				 * because the contingent allegiance
				 * condition will cause a retry which
				 * will re-copy the command from the
				 * saved data_cmnd.  We also unmap any
				 * data associated with the command
				 * here */
				NCR_700_unmap(hostdata, SCp, slot);
				dma_unmap_single(hostdata->dev, slot->pCmd,
						 MAX_COMMAND_SIZE,
						 DMA_TO_DEVICE);

				cmnd[0] = REQUEST_SENSE;
				cmnd[1] = (lun & 0x7) << 5;
				cmnd[2] = 0;
				cmnd[3] = 0;
				cmnd[4] = SCSI_SENSE_BUFFERSIZE;
				cmnd[5] = 0;
				/* Here's a quiet hack: the
				 * REQUEST_SENSE command is six bytes,
				 * so store a flag indicating that
				 * this was an पूर्णांकernal sense request
				 * and the original status at the end
				 * of the command */
				cmnd[6] = NCR_700_INTERNAL_SENSE_MAGIC;
				cmnd[7] = hostdata->status[0];
				cmnd[8] = SCp->cmd_len;
				SCp->cmd_len = 6; /* command length क्रम
						   * REQUEST_SENSE */
				slot->pCmd = dma_map_single(hostdata->dev, cmnd, MAX_COMMAND_SIZE, DMA_TO_DEVICE);
				slot->dma_handle = dma_map_single(hostdata->dev, SCp->sense_buffer, SCSI_SENSE_BUFFERSIZE, DMA_FROM_DEVICE);
				slot->SG[0].ins = bS_to_host(SCRIPT_MOVE_DATA_IN | SCSI_SENSE_BUFFERSIZE);
				slot->SG[0].pAddr = bS_to_host(slot->dma_handle);
				slot->SG[1].ins = bS_to_host(SCRIPT_RETURN);
				slot->SG[1].pAddr = 0;
				slot->resume_offset = hostdata->pScript;
				dma_sync_to_dev(hostdata, slot->SG, माप(slot->SG[0])*2);
				dma_sync_from_dev(hostdata, SCp->sense_buffer, SCSI_SENSE_BUFFERSIZE);

				/* queue the command क्रम reissue */
				slot->state = NCR_700_SLOT_QUEUED;
				slot->flags = NCR_700_FLAG_AUTOSENSE;
				hostdata->state = NCR_700_HOST_FREE;
				hostdata->cmd = शून्य;
			पूर्ण
		पूर्ण अन्यथा अणु
			// Currently rely on the mid layer evaluation
			// of the tag queuing capability
			//
			//अगर(status_byte(hostdata->status[0]) == GOOD &&
			//   SCp->cmnd[0] == INQUIRY && SCp->use_sg == 0) अणु
			//	/* Piggy back the tag queueing support
			//	 * on this command */
			//	dma_sync_single_क्रम_cpu(hostdata->dev,
			//			    slot->dma_handle,
			//			    SCp->request_bufflen,
			//			    DMA_FROM_DEVICE);
			//	अगर(((अक्षर *)SCp->request_buffer)[7] & 0x02) अणु
			//		scmd_prपूर्णांकk(KERN_INFO, SCp,
			//		     "Enabling Tag Command Queuing\n");
			//		hostdata->tag_negotiated |= (1<<scmd_id(SCp));
			//		NCR_700_set_flag(SCp->device, NCR_700_DEV_BEGIN_TAG_QUEUEING);
			//	पूर्ण अन्यथा अणु
			//		NCR_700_clear_flag(SCp->device, NCR_700_DEV_BEGIN_TAG_QUEUEING);
			//		hostdata->tag_negotiated &= ~(1<<scmd_id(SCp));
			//	पूर्ण
			//पूर्ण
			NCR_700_scsi_करोne(hostdata, SCp, hostdata->status[0]);
		पूर्ण
	पूर्ण अन्यथा अगर((dsps & 0xfffff0f0) == A_UNEXPECTED_PHASE) अणु
		__u8 i = (dsps & 0xf00) >> 8;

		scmd_prपूर्णांकk(KERN_ERR, SCp, "UNEXPECTED PHASE %s (%s)\n",
		       NCR_700_phase[i],
		       sbcl_to_string(NCR_700_पढ़ोb(host, SBCL_REG)));
		scmd_prपूर्णांकk(KERN_ERR, SCp, "         len = %d, cmd =",
			SCp->cmd_len);
		scsi_prपूर्णांक_command(SCp);

		NCR_700_पूर्णांकernal_bus_reset(host);
	पूर्ण अन्यथा अगर((dsps & 0xfffff000) == A_FATAL) अणु
		पूर्णांक i = (dsps & 0xfff);

		prपूर्णांकk(KERN_ERR "scsi%d: (%d:%d) FATAL ERROR: %s\n",
		       host->host_no, pun, lun, NCR_700_fatal_messages[i]);
		अगर(dsps == A_FATAL_ILLEGAL_MSG_LENGTH) अणु
			prपूर्णांकk(KERN_ERR "     msg begins %02x %02x\n",
			       hostdata->msgin[0], hostdata->msgin[1]);
		पूर्ण
		NCR_700_पूर्णांकernal_bus_reset(host);
	पूर्ण अन्यथा अगर((dsps & 0xfffff0f0) == A_DISCONNECT) अणु
#अगर_घोषित NCR_700_DEBUG
		__u8 i = (dsps & 0xf00) >> 8;

		prपूर्णांकk("scsi%d: (%d:%d), DISCONNECTED (%d) %s\n",
		       host->host_no, pun, lun,
		       i, NCR_700_phase[i]);
#पूर्ण_अगर
		save_क्रम_reselection(hostdata, SCp, dsp);

	पूर्ण अन्यथा अगर(dsps == A_RESELECTION_IDENTIFIED) अणु
		__u8 lun;
		काष्ठा NCR_700_command_slot *slot;
		__u8 reselection_id = hostdata->reselection_id;
		काष्ठा scsi_device *SDp;

		lun = hostdata->msgin[0] & 0x1f;

		hostdata->reselection_id = 0xff;
		DEBUG(("scsi%d: (%d:%d) RESELECTED!\n",
		       host->host_no, reselection_id, lun));
		/* clear the reselection indicator */
		SDp = __scsi_device_lookup(host, 0, reselection_id, lun);
		अगर(unlikely(SDp == शून्य)) अणु
			prपूर्णांकk(KERN_ERR "scsi%d: (%d:%d) HAS NO device\n",
			       host->host_no, reselection_id, lun);
			BUG();
		पूर्ण
		अगर(hostdata->msgin[1] == A_SIMPLE_TAG_MSG) अणु
			काष्ठा scsi_cmnd *SCp;

			SCp = scsi_host_find_tag(SDp->host, hostdata->msgin[2]);
			अगर(unlikely(SCp == शून्य)) अणु
				prपूर्णांकk(KERN_ERR "scsi%d: (%d:%d) no saved request for tag %d\n", 
				       host->host_no, reselection_id, lun, hostdata->msgin[2]);
				BUG();
			पूर्ण

			slot = (काष्ठा NCR_700_command_slot *)SCp->host_scribble;
			DDEBUG(KERN_DEBUG, SDp,
				"reselection is tag %d, slot %p(%d)\n",
				hostdata->msgin[2], slot, slot->tag);
		पूर्ण अन्यथा अणु
			काष्ठा NCR_700_Device_Parameters *p = SDp->hostdata;
			काष्ठा scsi_cmnd *SCp = p->current_cmnd;

			अगर(unlikely(SCp == शून्य)) अणु
				sdev_prपूर्णांकk(KERN_ERR, SDp,
					"no saved request for untagged cmd\n");
				BUG();
			पूर्ण
			slot = (काष्ठा NCR_700_command_slot *)SCp->host_scribble;
		पूर्ण

		अगर(slot == शून्य) अणु
			prपूर्णांकk(KERN_ERR "scsi%d: (%d:%d) RESELECTED but no saved command (MSG = %02x %02x %02x)!!\n",
			       host->host_no, reselection_id, lun,
			       hostdata->msgin[0], hostdata->msgin[1],
			       hostdata->msgin[2]);
		पूर्ण अन्यथा अणु
			अगर(hostdata->state != NCR_700_HOST_BUSY)
				prपूर्णांकk(KERN_ERR "scsi%d: FATAL, host not busy during valid reselection!\n",
				       host->host_no);
			resume_offset = slot->resume_offset;
			hostdata->cmd = slot->cmnd;

			/* re-patch क्रम this command */
			script_patch_32_असल(hostdata, hostdata->script,
			                    CommandAddress, slot->pCmd);
			script_patch_16(hostdata, hostdata->script,
					CommandCount, slot->cmnd->cmd_len);
			script_patch_32_असल(hostdata, hostdata->script,
			                    SGScriptStartAddress,
					    to32bit(&slot->pSG[0].ins));

			/* Note: setting SXFER only works अगर we're
			 * still in the MESSAGE phase, so it is vital
			 * that ACK is still निश्चितed when we process
			 * the reselection message.  The resume offset
			 * should thereक्रमe always clear ACK */
			NCR_700_ग_लिखोb(NCR_700_get_SXFER(hostdata->cmd->device),
				       host, SXFER_REG);
			dma_sync_from_dev(hostdata, hostdata->msgin,
				       MSG_ARRAY_SIZE);
			dma_sync_to_dev(hostdata, hostdata->msgout,
				       MSG_ARRAY_SIZE);
			/* I'm just being paranoid here, the command should
			 * alपढ़ोy have been flushed from the cache */
			dma_sync_to_dev(hostdata, slot->cmnd->cmnd,
				       slot->cmnd->cmd_len);


			
		पूर्ण
	पूर्ण अन्यथा अगर(dsps == A_RESELECTED_DURING_SELECTION) अणु

		/* This section is full of debugging code because I've
		 * never managed to reach it.  I think what happens is
		 * that, because the 700 runs with selection
		 * पूर्णांकerrupts enabled the whole समय that we take a
		 * selection पूर्णांकerrupt beक्रमe we manage to get to the
		 * reselected script पूर्णांकerrupt */

		__u8 reselection_id = NCR_700_पढ़ोb(host, SFBR_REG);
		काष्ठा NCR_700_command_slot *slot;
		
		/* Take out our own ID */
		reselection_id &= ~(1<<host->this_id);
		
		/* I've never seen this happen, so keep this as a prपूर्णांकk rather
		 * than a debug */
		prपूर्णांकk(KERN_INFO "scsi%d: (%d:%d) RESELECTION DURING SELECTION, dsp=%08x[%04x] state=%d, count=%d\n",
		       host->host_no, reselection_id, lun, dsp, dsp - hostdata->pScript, hostdata->state, hostdata->command_slot_count);

		अणु
			/* FIXME: DEBUGGING CODE */
			__u32 SG = (__u32)bS_to_cpu(hostdata->script[A_SGScriptStartAddress_used[0]]);
			पूर्णांक i;

			क्रम(i=0; i< NCR_700_COMMAND_SLOTS_PER_HOST; i++) अणु
				अगर(SG >= to32bit(&hostdata->slots[i].pSG[0])
				   && SG <= to32bit(&hostdata->slots[i].pSG[NCR_700_SG_SEGMENTS]))
					अवरोध;
			पूर्ण
			prपूर्णांकk(KERN_INFO "IDENTIFIED SG segment as being %08x in slot %p, cmd %p, slot->resume_offset=%08x\n", SG, &hostdata->slots[i], hostdata->slots[i].cmnd, hostdata->slots[i].resume_offset);
			SCp =  hostdata->slots[i].cmnd;
		पूर्ण

		अगर(SCp != शून्य) अणु
			slot = (काष्ठा NCR_700_command_slot *)SCp->host_scribble;
			/* change slot from busy to queued to reकरो command */
			slot->state = NCR_700_SLOT_QUEUED;
		पूर्ण
		hostdata->cmd = शून्य;
		
		अगर(reselection_id == 0) अणु
			अगर(hostdata->reselection_id == 0xff) अणु
				prपूर्णांकk(KERN_ERR "scsi%d: Invalid reselection during selection!!\n", host->host_no);
				वापस 0;
			पूर्ण अन्यथा अणु
				prपूर्णांकk(KERN_ERR "scsi%d: script reselected and we took a selection interrupt\n",
				       host->host_no);
				reselection_id = hostdata->reselection_id;
			पूर्ण
		पूर्ण अन्यथा अणु
			
			/* convert to real ID */
			reselection_id = biपंचांगap_to_number(reselection_id);
		पूर्ण
		hostdata->reselection_id = reselection_id;
		/* just in हाल we have a stale simple tag message, clear it */
		hostdata->msgin[1] = 0;
		dma_sync_to_dev(hostdata, hostdata->msgin, MSG_ARRAY_SIZE);
		अगर(hostdata->tag_negotiated & (1<<reselection_id)) अणु
			resume_offset = hostdata->pScript + Ent_GetReselectionWithTag;
		पूर्ण अन्यथा अणु
			resume_offset = hostdata->pScript + Ent_GetReselectionData;
		पूर्ण
	पूर्ण अन्यथा अगर(dsps == A_COMPLETED_SELECTION_AS_TARGET) अणु
		/* we've just disconnected from the bus, करो nothing since
		 * a वापस here will re-run the queued command slot
		 * that may have been पूर्णांकerrupted by the initial selection */
		DEBUG((" SELECTION COMPLETED\n"));
	पूर्ण अन्यथा अगर((dsps & 0xfffff0f0) == A_MSG_IN) अणु 
		resume_offset = process_message(host, hostdata, SCp,
						dsp, dsps);
	पूर्ण अन्यथा अगर((dsps &  0xfffff000) == 0) अणु
		__u8 i = (dsps & 0xf0) >> 4, j = (dsps & 0xf00) >> 8;
		prपूर्णांकk(KERN_ERR "scsi%d: (%d:%d), unhandled script condition %s %s at %04x\n",
		       host->host_no, pun, lun, NCR_700_condition[i],
		       NCR_700_phase[j], dsp - hostdata->pScript);
		अगर(SCp != शून्य) अणु
			काष्ठा scatterlist *sg;

			scsi_prपूर्णांक_command(SCp);
			scsi_क्रम_each_sg(SCp, sg, scsi_sg_count(SCp) + 1, i) अणु
				prपूर्णांकk(KERN_INFO " SG[%d].length = %d, move_insn=%08x, addr %08x\n", i, sg->length, ((काष्ठा NCR_700_command_slot *)SCp->host_scribble)->SG[i].ins, ((काष्ठा NCR_700_command_slot *)SCp->host_scribble)->SG[i].pAddr);
			पूर्ण
		पूर्ण
		NCR_700_पूर्णांकernal_bus_reset(host);
	पूर्ण अन्यथा अगर((dsps & 0xfffff000) == A_DEBUG_INTERRUPT) अणु
		prपूर्णांकk(KERN_NOTICE "scsi%d (%d:%d) DEBUG INTERRUPT %d AT %08x[%04x], continuing\n",
		       host->host_no, pun, lun, dsps & 0xfff, dsp, dsp - hostdata->pScript);
		resume_offset = dsp;
	पूर्ण अन्यथा अणु
		prपूर्णांकk(KERN_ERR "scsi%d: (%d:%d), unidentified script interrupt 0x%x at %04x\n",
		       host->host_no, pun, lun, dsps, dsp - hostdata->pScript);
		NCR_700_पूर्णांकernal_bus_reset(host);
	पूर्ण
	वापस resume_offset;
पूर्ण

/* We run the 53c700 with selection पूर्णांकerrupts always enabled.  This
 * means that the chip may be selected as soon as the bus मुक्तs.  On a
 * busy bus, this can be beक्रमe the scripts engine finishes its
 * processing.  Thereक्रमe, part of the selection processing has to be
 * to find out what the scripts engine is करोing and complete the
 * function अगर necessary (i.e. process the pending disconnect or save
 * the पूर्णांकerrupted initial selection */
STATIC अंतरभूत __u32
process_selection(काष्ठा Scsi_Host *host, __u32 dsp)
अणु
	__u8 id = 0;	/* Squash compiler warning */
	पूर्णांक count = 0;
	__u32 resume_offset = 0;
	काष्ठा NCR_700_Host_Parameters *hostdata =
		(काष्ठा NCR_700_Host_Parameters *)host->hostdata[0];
	काष्ठा scsi_cmnd *SCp = hostdata->cmd;
	__u8 sbcl;

	क्रम(count = 0; count < 5; count++) अणु
		id = NCR_700_पढ़ोb(host, hostdata->chip710 ?
				   CTEST9_REG : SFBR_REG);

		/* Take out our own ID */
		id &= ~(1<<host->this_id);
		अगर(id != 0) 
			अवरोध;
		udelay(5);
	पूर्ण
	sbcl = NCR_700_पढ़ोb(host, SBCL_REG);
	अगर((sbcl & SBCL_IO) == 0) अणु
		/* mark as having been selected rather than reselected */
		id = 0xff;
	पूर्ण अन्यथा अणु
		/* convert to real ID */
		hostdata->reselection_id = id = biपंचांगap_to_number(id);
		DEBUG(("scsi%d:  Reselected by %d\n",
		       host->host_no, id));
	पूर्ण
	अगर(hostdata->state == NCR_700_HOST_BUSY && SCp != शून्य) अणु
		काष्ठा NCR_700_command_slot *slot =
			(काष्ठा NCR_700_command_slot *)SCp->host_scribble;
		DEBUG(("  ID %d WARNING: RESELECTION OF BUSY HOST, saving cmd %p, slot %p, addr %x [%04x], resume %x!\n", id, hostdata->cmd, slot, dsp, dsp - hostdata->pScript, resume_offset));
		
		चयन(dsp - hostdata->pScript) अणु
		हाल Ent_Disconnect1:
		हाल Ent_Disconnect2:
			save_क्रम_reselection(hostdata, SCp, Ent_Disconnect2 + hostdata->pScript);
			अवरोध;
		हाल Ent_Disconnect3:
		हाल Ent_Disconnect4:
			save_क्रम_reselection(hostdata, SCp, Ent_Disconnect4 + hostdata->pScript);
			अवरोध;
		हाल Ent_Disconnect5:
		हाल Ent_Disconnect6:
			save_क्रम_reselection(hostdata, SCp, Ent_Disconnect6 + hostdata->pScript);
			अवरोध;
		हाल Ent_Disconnect7:
		हाल Ent_Disconnect8:
			save_क्रम_reselection(hostdata, SCp, Ent_Disconnect8 + hostdata->pScript);
			अवरोध;
		हाल Ent_Finish1:
		हाल Ent_Finish2:
			process_script_पूर्णांकerrupt(A_GOOD_STATUS_AFTER_STATUS, dsp, SCp, host, hostdata);
			अवरोध;
			
		शेष:
			slot->state = NCR_700_SLOT_QUEUED;
			अवरोध;
			पूर्ण
	पूर्ण
	hostdata->state = NCR_700_HOST_BUSY;
	hostdata->cmd = शून्य;
	/* clear any stale simple tag message */
	hostdata->msgin[1] = 0;
	dma_sync_to_dev(hostdata, hostdata->msgin, MSG_ARRAY_SIZE);

	अगर(id == 0xff) अणु
		/* Selected as target, Ignore */
		resume_offset = hostdata->pScript + Ent_SelectedAsTarget;
	पूर्ण अन्यथा अगर(hostdata->tag_negotiated & (1<<id)) अणु
		resume_offset = hostdata->pScript + Ent_GetReselectionWithTag;
	पूर्ण अन्यथा अणु
		resume_offset = hostdata->pScript + Ent_GetReselectionData;
	पूर्ण
	वापस resume_offset;
पूर्ण

अटल अंतरभूत व्योम
NCR_700_clear_fअगरo(काष्ठा Scsi_Host *host) अणु
	स्थिर काष्ठा NCR_700_Host_Parameters *hostdata
		= (काष्ठा NCR_700_Host_Parameters *)host->hostdata[0];
	अगर(hostdata->chip710) अणु
		NCR_700_ग_लिखोb(CLR_FIFO_710, host, CTEST8_REG);
	पूर्ण अन्यथा अणु
		NCR_700_ग_लिखोb(CLR_FIFO, host, DFIFO_REG);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम
NCR_700_flush_fअगरo(काष्ठा Scsi_Host *host) अणु
	स्थिर काष्ठा NCR_700_Host_Parameters *hostdata
		= (काष्ठा NCR_700_Host_Parameters *)host->hostdata[0];
	अगर(hostdata->chip710) अणु
		NCR_700_ग_लिखोb(FLUSH_DMA_FIFO_710, host, CTEST8_REG);
		udelay(10);
		NCR_700_ग_लिखोb(0, host, CTEST8_REG);
	पूर्ण अन्यथा अणु
		NCR_700_ग_लिखोb(FLUSH_DMA_FIFO, host, DFIFO_REG);
		udelay(10);
		NCR_700_ग_लिखोb(0, host, DFIFO_REG);
	पूर्ण
पूर्ण


/* The queue lock with पूर्णांकerrupts disabled must be held on entry to
 * this function */
STATIC पूर्णांक
NCR_700_start_command(काष्ठा scsi_cmnd *SCp)
अणु
	काष्ठा NCR_700_command_slot *slot =
		(काष्ठा NCR_700_command_slot *)SCp->host_scribble;
	काष्ठा NCR_700_Host_Parameters *hostdata =
		(काष्ठा NCR_700_Host_Parameters *)SCp->device->host->hostdata[0];
	__u16 count = 1;	/* क्रम IDENTIFY message */
	u8 lun = SCp->device->lun;

	अगर(hostdata->state != NCR_700_HOST_FREE) अणु
		/* keep this inside the lock to बंद the race winकरोw where
		 * the running command finishes on another CPU जबतक we करोn't
		 * change the state to queued on this one */
		slot->state = NCR_700_SLOT_QUEUED;

		DEBUG(("scsi%d: host busy, queueing command %p, slot %p\n",
		       SCp->device->host->host_no, slot->cmnd, slot));
		वापस 0;
	पूर्ण
	hostdata->state = NCR_700_HOST_BUSY;
	hostdata->cmd = SCp;
	slot->state = NCR_700_SLOT_BUSY;
	/* keep पूर्णांकerrupts disabled until we have the command correctly
	 * set up so we cannot take a selection पूर्णांकerrupt */

	hostdata->msgout[0] = NCR_700_identअगरy((SCp->cmnd[0] != REQUEST_SENSE &&
						slot->flags != NCR_700_FLAG_AUTOSENSE),
					       lun);
	/* क्रम INQUIRY or REQUEST_SENSE commands, we cannot be sure
	 * अगर the negotiated transfer parameters still hold, so
	 * always renegotiate them */
	अगर(SCp->cmnd[0] == INQUIRY || SCp->cmnd[0] == REQUEST_SENSE ||
	   slot->flags == NCR_700_FLAG_AUTOSENSE) अणु
		NCR_700_clear_flag(SCp->device, NCR_700_DEV_NEGOTIATED_SYNC);
	पूर्ण

	/* REQUEST_SENSE is asking क्रम contingent I_T_L(_Q) status.
	 * If a contingent allegiance condition exists, the device
	 * will refuse all tags, so send the request sense as untagged
	 * */
	अगर((hostdata->tag_negotiated & (1<<scmd_id(SCp)))
	   && (slot->tag != SCSI_NO_TAG && SCp->cmnd[0] != REQUEST_SENSE &&
	       slot->flags != NCR_700_FLAG_AUTOSENSE)) अणु
		count += spi_populate_tag_msg(&hostdata->msgout[count], SCp);
	पूर्ण

	अगर(hostdata->fast &&
	   NCR_700_is_flag_clear(SCp->device, NCR_700_DEV_NEGOTIATED_SYNC)) अणु
		count += spi_populate_sync_msg(&hostdata->msgout[count],
				spi_period(SCp->device->sdev_target),
				spi_offset(SCp->device->sdev_target));
		NCR_700_set_flag(SCp->device, NCR_700_DEV_BEGIN_SYNC_NEGOTIATION);
	पूर्ण

	script_patch_16(hostdata, hostdata->script, MessageCount, count);

	script_patch_ID(hostdata, hostdata->script, Device_ID, 1<<scmd_id(SCp));

	script_patch_32_असल(hostdata, hostdata->script, CommandAddress,
			    slot->pCmd);
	script_patch_16(hostdata, hostdata->script, CommandCount, SCp->cmd_len);
	/* finally plumb the beginning of the SG list पूर्णांकo the script
	 * */
	script_patch_32_असल(hostdata, hostdata->script,
	                    SGScriptStartAddress, to32bit(&slot->pSG[0].ins));
	NCR_700_clear_fअगरo(SCp->device->host);

	अगर(slot->resume_offset == 0)
		slot->resume_offset = hostdata->pScript;
	/* now perक्रमm all the ग_लिखोbacks and invalidates */
	dma_sync_to_dev(hostdata, hostdata->msgout, count);
	dma_sync_from_dev(hostdata, hostdata->msgin, MSG_ARRAY_SIZE);
	dma_sync_to_dev(hostdata, SCp->cmnd, SCp->cmd_len);
	dma_sync_from_dev(hostdata, hostdata->status, 1);

	/* set the synchronous period/offset */
	NCR_700_ग_लिखोb(NCR_700_get_SXFER(SCp->device),
		       SCp->device->host, SXFER_REG);
	NCR_700_ग_लिखोl(slot->temp, SCp->device->host, TEMP_REG);
	NCR_700_ग_लिखोl(slot->resume_offset, SCp->device->host, DSP_REG);

	वापस 1;
पूर्ण

irqवापस_t
NCR_700_पूर्णांकr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा Scsi_Host *host = (काष्ठा Scsi_Host *)dev_id;
	काष्ठा NCR_700_Host_Parameters *hostdata =
		(काष्ठा NCR_700_Host_Parameters *)host->hostdata[0];
	__u8 istat;
	__u32 resume_offset = 0;
	__u8 pun = 0xff, lun = 0xff;
	अचिन्हित दीर्घ flags;
	पूर्णांक handled = 0;

	/* Use the host lock to serialise access to the 53c700
	 * hardware.  Note: In future, we may need to take the queue
	 * lock to enter the करोne routines.  When that happens, we
	 * need to ensure that क्रम this driver, the host lock and the
	 * queue lock poपूर्णांक to the same thing. */
	spin_lock_irqsave(host->host_lock, flags);
	अगर((istat = NCR_700_पढ़ोb(host, ISTAT_REG))
	      & (SCSI_INT_PENDING | DMA_INT_PENDING)) अणु
		__u32 dsps;
		__u8 sstat0 = 0, dstat = 0;
		__u32 dsp;
		काष्ठा scsi_cmnd *SCp = hostdata->cmd;

		handled = 1;
		SCp = hostdata->cmd;

		अगर(istat & SCSI_INT_PENDING) अणु
			udelay(10);

			sstat0 = NCR_700_पढ़ोb(host, SSTAT0_REG);
		पूर्ण

		अगर(istat & DMA_INT_PENDING) अणु
			udelay(10);

			dstat = NCR_700_पढ़ोb(host, DSTAT_REG);
		पूर्ण

		dsps = NCR_700_पढ़ोl(host, DSPS_REG);
		dsp = NCR_700_पढ़ोl(host, DSP_REG);

		DEBUG(("scsi%d: istat %02x sstat0 %02x dstat %02x dsp %04x[%08x] dsps 0x%x\n",
		       host->host_no, istat, sstat0, dstat,
		       (dsp - (__u32)(hostdata->pScript))/4,
		       dsp, dsps));

		अगर(SCp != शून्य) अणु
			pun = SCp->device->id;
			lun = SCp->device->lun;
		पूर्ण

		अगर(sstat0 & SCSI_RESET_DETECTED) अणु
			काष्ठा scsi_device *SDp;
			पूर्णांक i;

			hostdata->state = NCR_700_HOST_BUSY;

			prपूर्णांकk(KERN_ERR "scsi%d: Bus Reset detected, executing command %p, slot %p, dsp %08x[%04x]\n",
			       host->host_no, SCp, SCp == शून्य ? शून्य : SCp->host_scribble, dsp, dsp - hostdata->pScript);

			scsi_report_bus_reset(host, 0);

			/* clear all the negotiated parameters */
			__shost_क्रम_each_device(SDp, host)
				NCR_700_clear_flag(SDp, ~0);
			
			/* clear all the slots and their pending commands */
			क्रम(i = 0; i < NCR_700_COMMAND_SLOTS_PER_HOST; i++) अणु
				काष्ठा scsi_cmnd *SCp;
				काष्ठा NCR_700_command_slot *slot =
					&hostdata->slots[i];

				अगर(slot->state == NCR_700_SLOT_FREE)
					जारी;
				
				SCp = slot->cmnd;
				prपूर्णांकk(KERN_ERR " failing command because of reset, slot %p, cmnd %p\n",
				       slot, SCp);
				मुक्त_slot(slot, hostdata);
				SCp->host_scribble = शून्य;
				NCR_700_set_depth(SCp->device, 0);
				/* NOTE: deadlock potential here: we
				 * rely on mid-layer guarantees that
				 * scsi_करोne won't try to issue the
				 * command again otherwise we'll
				 * deadlock on the
				 * hostdata->state_lock */
				SCp->result = DID_RESET << 16;
				SCp->scsi_करोne(SCp);
			पूर्ण
			mdelay(25);
			NCR_700_chip_setup(host);

			hostdata->state = NCR_700_HOST_FREE;
			hostdata->cmd = शून्य;
			/* संकेत back अगर this was an eh induced reset */
			अगर(hostdata->eh_complete != शून्य)
				complete(hostdata->eh_complete);
			जाओ out_unlock;
		पूर्ण अन्यथा अगर(sstat0 & SELECTION_TIMEOUT) अणु
			DEBUG(("scsi%d: (%d:%d) selection timeout\n",
			       host->host_no, pun, lun));
			NCR_700_scsi_करोne(hostdata, SCp, DID_NO_CONNECT<<16);
		पूर्ण अन्यथा अगर(sstat0 & PHASE_MISMATCH) अणु
			काष्ठा NCR_700_command_slot *slot = (SCp == शून्य) ? शून्य :
				(काष्ठा NCR_700_command_slot *)SCp->host_scribble;

			अगर(dsp == Ent_SendMessage + 8 + hostdata->pScript) अणु
				/* It wants to reply to some part of
				 * our message */
#अगर_घोषित NCR_700_DEBUG
				__u32 temp = NCR_700_पढ़ोl(host, TEMP_REG);
				पूर्णांक count = (hostdata->script[Ent_SendMessage/4] & 0xffffff) - ((NCR_700_पढ़ोl(host, DBC_REG) & 0xffffff) + NCR_700_data_residual(host));
				prपूर्णांकk("scsi%d (%d:%d) PHASE MISMATCH IN SEND MESSAGE %d remain, return %p[%04x], phase %s\n", host->host_no, pun, lun, count, (व्योम *)temp, temp - hostdata->pScript, sbcl_to_string(NCR_700_पढ़ोb(host, SBCL_REG)));
#पूर्ण_अगर
				resume_offset = hostdata->pScript + Ent_SendMessagePhaseMismatch;
			पूर्ण अन्यथा अगर(dsp >= to32bit(&slot->pSG[0].ins) &&
				  dsp <= to32bit(&slot->pSG[NCR_700_SG_SEGMENTS].ins)) अणु
				पूर्णांक data_transfer = NCR_700_पढ़ोl(host, DBC_REG) & 0xffffff;
				पूर्णांक SGcount = (dsp - to32bit(&slot->pSG[0].ins))/माप(काष्ठा NCR_700_SG_List);
				पूर्णांक residual = NCR_700_data_residual(host);
				पूर्णांक i;
#अगर_घोषित NCR_700_DEBUG
				__u32 naddr = NCR_700_पढ़ोl(host, DNAD_REG);

				prपूर्णांकk("scsi%d: (%d:%d) Expected phase mismatch in slot->SG[%d], transferred 0x%x\n",
				       host->host_no, pun, lun,
				       SGcount, data_transfer);
				scsi_prपूर्णांक_command(SCp);
				अगर(residual) अणु
					prपूर्णांकk("scsi%d: (%d:%d) Expected phase mismatch in slot->SG[%d], transferred 0x%x, residual %d\n",
				       host->host_no, pun, lun,
				       SGcount, data_transfer, residual);
				पूर्ण
#पूर्ण_अगर
				data_transfer += residual;

				अगर(data_transfer != 0) अणु
					पूर्णांक count; 
					__u32 pAddr;

					SGcount--;

					count = (bS_to_cpu(slot->SG[SGcount].ins) & 0x00ffffff);
					DEBUG(("DATA TRANSFER MISMATCH, count = %d, transferred %d\n", count, count-data_transfer));
					slot->SG[SGcount].ins &= bS_to_host(0xff000000);
					slot->SG[SGcount].ins |= bS_to_host(data_transfer);
					pAddr = bS_to_cpu(slot->SG[SGcount].pAddr);
					pAddr += (count - data_transfer);
#अगर_घोषित NCR_700_DEBUG
					अगर(pAddr != naddr) अणु
						prपूर्णांकk("scsi%d (%d:%d) transfer mismatch pAddr=%lx, naddr=%lx, data_transfer=%d, residual=%d\n", host->host_no, pun, lun, (अचिन्हित दीर्घ)pAddr, (अचिन्हित दीर्घ)naddr, data_transfer, residual);
					पूर्ण
#पूर्ण_अगर
					slot->SG[SGcount].pAddr = bS_to_host(pAddr);
				पूर्ण
				/* set the executed moves to nops */
				क्रम(i=0; i<SGcount; i++) अणु
					slot->SG[i].ins = bS_to_host(SCRIPT_NOP);
					slot->SG[i].pAddr = 0;
				पूर्ण
				dma_sync_to_dev(hostdata, slot->SG, माप(slot->SG));
				/* and pretend we disconnected after
				 * the command phase */
				resume_offset = hostdata->pScript + Ent_MsgInDuringData;
				/* make sure all the data is flushed */
				NCR_700_flush_fअगरo(host);
			पूर्ण अन्यथा अणु
				__u8 sbcl = NCR_700_पढ़ोb(host, SBCL_REG);
				prपूर्णांकk(KERN_ERR "scsi%d: (%d:%d) phase mismatch at %04x, phase %s\n",
				       host->host_no, pun, lun, dsp - hostdata->pScript, sbcl_to_string(sbcl));
				NCR_700_पूर्णांकernal_bus_reset(host);
			पूर्ण

		पूर्ण अन्यथा अगर(sstat0 & SCSI_GROSS_ERROR) अणु
			prपूर्णांकk(KERN_ERR "scsi%d: (%d:%d) GROSS ERROR\n",
			       host->host_no, pun, lun);
			NCR_700_scsi_करोne(hostdata, SCp, DID_ERROR<<16);
		पूर्ण अन्यथा अगर(sstat0 & PARITY_ERROR) अणु
			prपूर्णांकk(KERN_ERR "scsi%d: (%d:%d) PARITY ERROR\n",
			       host->host_no, pun, lun);
			NCR_700_scsi_करोne(hostdata, SCp, DID_ERROR<<16);
		पूर्ण अन्यथा अगर(dstat & SCRIPT_INT_RECEIVED) अणु
			DEBUG(("scsi%d: (%d:%d) ====>SCRIPT INTERRUPT<====\n",
			       host->host_no, pun, lun));
			resume_offset = process_script_पूर्णांकerrupt(dsps, dsp, SCp, host, hostdata);
		पूर्ण अन्यथा अगर(dstat & (ILGL_INST_DETECTED)) अणु
			prपूर्णांकk(KERN_ERR "scsi%d: (%d:%d) Illegal Instruction detected at 0x%08x[0x%x]!!!\n"
			       "         Please email James.Bottomley@HansenPartnership.com with the details\n",
			       host->host_no, pun, lun,
			       dsp, dsp - hostdata->pScript);
			NCR_700_scsi_करोne(hostdata, SCp, DID_ERROR<<16);
		पूर्ण अन्यथा अगर(dstat & (WATCH_DOG_INTERRUPT|ABORTED)) अणु
			prपूर्णांकk(KERN_ERR "scsi%d: (%d:%d) serious DMA problem, dstat=%02x\n",
			       host->host_no, pun, lun, dstat);
			NCR_700_scsi_करोne(hostdata, SCp, DID_ERROR<<16);
		पूर्ण

		
		/* NOTE: selection पूर्णांकerrupt processing MUST occur
		 * after script पूर्णांकerrupt processing to correctly cope
		 * with the हाल where we process a disconnect and
		 * then get reselected beक्रमe we process the
		 * disconnection */
		अगर(sstat0 & SELECTED) अणु
			/* FIXME: It currently takes at least FOUR
			 * पूर्णांकerrupts to complete a command that
			 * disconnects: one क्रम the disconnect, one
			 * क्रम the reselection, one to get the
			 * reselection data and one to complete the
			 * command.  If we guess the reselected
			 * command here and prepare it, we only need
			 * to get a reselection data पूर्णांकerrupt अगर we
			 * guessed wrongly.  Since the पूर्णांकerrupt
			 * overhead is much greater than the command
			 * setup, this would be an efficient
			 * optimisation particularly as we probably
			 * only have one outstanding command on a
			 * target most of the समय */

			resume_offset = process_selection(host, dsp);

		पूर्ण

	पूर्ण

	अगर(resume_offset) अणु
		अगर(hostdata->state != NCR_700_HOST_BUSY) अणु
			prपूर्णांकk(KERN_ERR "scsi%d: Driver error: resume at 0x%08x [0x%04x] with non busy host!\n",
			       host->host_no, resume_offset, resume_offset - hostdata->pScript);
			hostdata->state = NCR_700_HOST_BUSY;
		पूर्ण

		DEBUG(("Attempting to resume at %x\n", resume_offset));
		NCR_700_clear_fअगरo(host);
		NCR_700_ग_लिखोl(resume_offset, host, DSP_REG);
	पूर्ण 
	/* There is probably a technical no-no about this: If we're a
	 * shared पूर्णांकerrupt and we got this पूर्णांकerrupt because the
	 * other device needs servicing not us, we're still going to
	 * check our queued commands here---of course, there shouldn't
	 * be any outstanding.... */
	अगर(hostdata->state == NCR_700_HOST_FREE) अणु
		पूर्णांक i;

		क्रम(i = 0; i < NCR_700_COMMAND_SLOTS_PER_HOST; i++) अणु
			/* fairness: always run the queue from the last
			 * position we left off */
			पूर्णांक j = (i + hostdata->saved_slot_position)
				% NCR_700_COMMAND_SLOTS_PER_HOST;
			
			अगर(hostdata->slots[j].state != NCR_700_SLOT_QUEUED)
				जारी;
			अगर(NCR_700_start_command(hostdata->slots[j].cmnd)) अणु
				DEBUG(("scsi%d: Issuing saved command slot %p, cmd %p\t\n",
				       host->host_no, &hostdata->slots[j],
				       hostdata->slots[j].cmnd));
				hostdata->saved_slot_position = j + 1;
			पूर्ण

			अवरोध;
		पूर्ण
	पूर्ण
 out_unlock:
	spin_unlock_irqrestore(host->host_lock, flags);
	वापस IRQ_RETVAL(handled);
पूर्ण

अटल पूर्णांक
NCR_700_queuecommand_lck(काष्ठा scsi_cmnd *SCp, व्योम (*करोne)(काष्ठा scsi_cmnd *))
अणु
	काष्ठा NCR_700_Host_Parameters *hostdata = 
		(काष्ठा NCR_700_Host_Parameters *)SCp->device->host->hostdata[0];
	__u32 move_ins;
	काष्ठा NCR_700_command_slot *slot;

	अगर(hostdata->command_slot_count >= NCR_700_COMMAND_SLOTS_PER_HOST) अणु
		/* We're over our allocation, this should never happen
		 * since we report the max allocation to the mid layer */
		prपूर्णांकk(KERN_WARNING "scsi%d: Command depth has gone over queue depth\n", SCp->device->host->host_no);
		वापस 1;
	पूर्ण
	/* check क्रम untagged commands.  We cannot have any outstanding
	 * commands अगर we accept them.  Commands could be untagged because:
	 *
	 * - The tag negotiated biपंचांगap is clear
	 * - The blk layer sent and untagged command
	 */
	अगर(NCR_700_get_depth(SCp->device) != 0
	   && (!(hostdata->tag_negotiated & (1<<scmd_id(SCp)))
	       || !(SCp->flags & SCMD_TAGGED))) अणु
		CDEBUG(KERN_ERR, SCp, "has non zero depth %d\n",
		       NCR_700_get_depth(SCp->device));
		वापस SCSI_MLQUEUE_DEVICE_BUSY;
	पूर्ण
	अगर(NCR_700_get_depth(SCp->device) >= SCp->device->queue_depth) अणु
		CDEBUG(KERN_ERR, SCp, "has max tag depth %d\n",
		       NCR_700_get_depth(SCp->device));
		वापस SCSI_MLQUEUE_DEVICE_BUSY;
	पूर्ण
	NCR_700_set_depth(SCp->device, NCR_700_get_depth(SCp->device) + 1);

	/* begin the command here */
	/* no need to check क्रम शून्य, test क्रम command_slot_count above
	 * ensures a slot is मुक्त */
	slot = find_empty_slot(hostdata);

	slot->cmnd = SCp;

	SCp->scsi_करोne = करोne;
	SCp->host_scribble = (अचिन्हित अक्षर *)slot;
	SCp->SCp.ptr = शून्य;
	SCp->SCp.buffer = शून्य;

#अगर_घोषित NCR_700_DEBUG
	prपूर्णांकk("53c700: scsi%d, command ", SCp->device->host->host_no);
	scsi_prपूर्णांक_command(SCp);
#पूर्ण_अगर
	अगर ((SCp->flags & SCMD_TAGGED)
	   && (hostdata->tag_negotiated &(1<<scmd_id(SCp))) == 0
	   && NCR_700_get_tag_neg_state(SCp->device) == NCR_700_START_TAG_NEGOTIATION) अणु
		scmd_prपूर्णांकk(KERN_ERR, SCp, "Enabling Tag Command Queuing\n");
		hostdata->tag_negotiated |= (1<<scmd_id(SCp));
		NCR_700_set_tag_neg_state(SCp->device, NCR_700_DURING_TAG_NEGOTIATION);
	पूर्ण

	/* here we may have to process an untagged command.  The gate
	 * above ensures that this will be the only one outstanding,
	 * so clear the tag negotiated bit.
	 *
	 * FIXME: This will royally screw up on multiple LUN devices
	 * */
	अगर (!(SCp->flags & SCMD_TAGGED)
	   && (hostdata->tag_negotiated &(1<<scmd_id(SCp)))) अणु
		scmd_prपूर्णांकk(KERN_INFO, SCp, "Disabling Tag Command Queuing\n");
		hostdata->tag_negotiated &= ~(1<<scmd_id(SCp));
	पूर्ण

	अगर ((hostdata->tag_negotiated & (1<<scmd_id(SCp))) &&
	    SCp->device->simple_tags) अणु
		slot->tag = SCp->request->tag;
		CDEBUG(KERN_DEBUG, SCp, "sending out tag %d, slot %p\n",
		       slot->tag, slot);
	पूर्ण अन्यथा अणु
		काष्ठा NCR_700_Device_Parameters *p = SCp->device->hostdata;

		slot->tag = SCSI_NO_TAG;
		/* save current command क्रम reselection */
		p->current_cmnd = SCp;
	पूर्ण
	/* sanity check: some of the commands generated by the mid-layer
	 * have an eccentric idea of their sc_data_direction */
	अगर(!scsi_sg_count(SCp) && !scsi_bufflen(SCp) &&
	   SCp->sc_data_direction != DMA_NONE) अणु
#अगर_घोषित NCR_700_DEBUG
		prपूर्णांकk("53c700: Command");
		scsi_prपूर्णांक_command(SCp);
		prपूर्णांकk("Has wrong data direction %d\n", SCp->sc_data_direction);
#पूर्ण_अगर
		SCp->sc_data_direction = DMA_NONE;
	पूर्ण

	चयन (SCp->cmnd[0]) अणु
	हाल REQUEST_SENSE:
		/* clear the पूर्णांकernal sense magic */
		SCp->cmnd[6] = 0;
		fallthrough;
	शेष:
		/* OK, get it from the command */
		चयन(SCp->sc_data_direction) अणु
		हाल DMA_BIसूचीECTIONAL:
		शेष:
			prपूर्णांकk(KERN_ERR "53c700: Unknown command for data direction ");
			scsi_prपूर्णांक_command(SCp);
			
			move_ins = 0;
			अवरोध;
		हाल DMA_NONE:
			move_ins = 0;
			अवरोध;
		हाल DMA_FROM_DEVICE:
			move_ins = SCRIPT_MOVE_DATA_IN;
			अवरोध;
		हाल DMA_TO_DEVICE:
			move_ins = SCRIPT_MOVE_DATA_OUT;
			अवरोध;
		पूर्ण
	पूर्ण

	/* now build the scatter gather list */
	अगर(move_ins != 0) अणु
		पूर्णांक i;
		पूर्णांक sg_count;
		dma_addr_t vPtr = 0;
		काष्ठा scatterlist *sg;
		__u32 count = 0;

		sg_count = scsi_dma_map(SCp);
		BUG_ON(sg_count < 0);

		scsi_क्रम_each_sg(SCp, sg, sg_count, i) अणु
			vPtr = sg_dma_address(sg);
			count = sg_dma_len(sg);

			slot->SG[i].ins = bS_to_host(move_ins | count);
			DEBUG((" scatter block %d: move %d[%08x] from 0x%lx\n",
			       i, count, slot->SG[i].ins, (अचिन्हित दीर्घ)vPtr));
			slot->SG[i].pAddr = bS_to_host(vPtr);
		पूर्ण
		slot->SG[i].ins = bS_to_host(SCRIPT_RETURN);
		slot->SG[i].pAddr = 0;
		dma_sync_to_dev(hostdata, slot->SG, माप(slot->SG));
		DEBUG((" SETTING %p to %x\n",
		       (&slot->pSG[i].ins),
		       slot->SG[i].ins));
	पूर्ण
	slot->resume_offset = 0;
	slot->pCmd = dma_map_single(hostdata->dev, SCp->cmnd,
				    MAX_COMMAND_SIZE, DMA_TO_DEVICE);
	NCR_700_start_command(SCp);
	वापस 0;
पूर्ण

STATIC DEF_SCSI_QCMD(NCR_700_queuecommand)

STATIC पूर्णांक
NCR_700_पात(काष्ठा scsi_cmnd * SCp)
अणु
	काष्ठा NCR_700_command_slot *slot;

	scmd_prपूर्णांकk(KERN_INFO, SCp, "abort command\n");

	slot = (काष्ठा NCR_700_command_slot *)SCp->host_scribble;

	अगर(slot == शून्य)
		/* no outstanding command to पात */
		वापस SUCCESS;
	अगर(SCp->cmnd[0] == TEST_UNIT_READY) अणु
		/* FIXME: This is because of a problem in the new
		 * error handler.  When it is in error recovery, it
		 * will send a TUR to a device it thinks may still be
		 * showing a problem.  If the TUR isn't responded to,
		 * it will पात it and mark the device off line.
		 * Unक्रमtunately, it करोes no other error recovery, so
		 * this would leave us with an outstanding command
		 * occupying a slot.  Rather than allow this to
		 * happen, we issue a bus reset to क्रमce all
		 * outstanding commands to terminate here. */
		NCR_700_पूर्णांकernal_bus_reset(SCp->device->host);
		/* still drop through and वापस failed */
	पूर्ण
	वापस FAILED;

पूर्ण

STATIC पूर्णांक
NCR_700_host_reset(काष्ठा scsi_cmnd * SCp)
अणु
	DECLARE_COMPLETION_ONSTACK(complete);
	काष्ठा NCR_700_Host_Parameters *hostdata = 
		(काष्ठा NCR_700_Host_Parameters *)SCp->device->host->hostdata[0];

	scmd_prपूर्णांकk(KERN_INFO, SCp,
		"New error handler wants HOST reset, cmd %p\n\t", SCp);
	scsi_prपूर्णांक_command(SCp);

	/* In theory, eh_complete should always be null because the
	 * eh is single thपढ़ोed, but just in हाल we're handling a
	 * reset via sg or something */
	spin_lock_irq(SCp->device->host->host_lock);
	जबतक (hostdata->eh_complete != शून्य) अणु
		spin_unlock_irq(SCp->device->host->host_lock);
		msleep_पूर्णांकerruptible(100);
		spin_lock_irq(SCp->device->host->host_lock);
	पूर्ण

	hostdata->eh_complete = &complete;
	NCR_700_पूर्णांकernal_bus_reset(SCp->device->host);
	NCR_700_chip_reset(SCp->device->host);

	spin_unlock_irq(SCp->device->host->host_lock);
	रुको_क्रम_completion(&complete);
	spin_lock_irq(SCp->device->host->host_lock);

	hostdata->eh_complete = शून्य;
	/* Revalidate the transport parameters of the failing device */
	अगर(hostdata->fast)
		spi_schedule_dv_device(SCp->device);

	spin_unlock_irq(SCp->device->host->host_lock);
	वापस SUCCESS;
पूर्ण

STATIC व्योम
NCR_700_set_period(काष्ठा scsi_target *STp, पूर्णांक period)
अणु
	काष्ठा Scsi_Host *SHp = dev_to_shost(STp->dev.parent);
	काष्ठा NCR_700_Host_Parameters *hostdata = 
		(काष्ठा NCR_700_Host_Parameters *)SHp->hostdata[0];
	
	अगर(!hostdata->fast)
		वापस;

	अगर(period < hostdata->min_period)
		period = hostdata->min_period;

	spi_period(STp) = period;
	spi_flags(STp) &= ~(NCR_700_DEV_NEGOTIATED_SYNC |
			    NCR_700_DEV_BEGIN_SYNC_NEGOTIATION);
	spi_flags(STp) |= NCR_700_DEV_PRINT_SYNC_NEGOTIATION;
पूर्ण

STATIC व्योम
NCR_700_set_offset(काष्ठा scsi_target *STp, पूर्णांक offset)
अणु
	काष्ठा Scsi_Host *SHp = dev_to_shost(STp->dev.parent);
	काष्ठा NCR_700_Host_Parameters *hostdata = 
		(काष्ठा NCR_700_Host_Parameters *)SHp->hostdata[0];
	पूर्णांक max_offset = hostdata->chip710
		? NCR_710_MAX_OFFSET : NCR_700_MAX_OFFSET;
	
	अगर(!hostdata->fast)
		वापस;

	अगर(offset > max_offset)
		offset = max_offset;

	/* अगर we're currently async, make sure the period is reasonable */
	अगर(spi_offset(STp) == 0 && (spi_period(STp) < hostdata->min_period ||
				    spi_period(STp) > 0xff))
		spi_period(STp) = hostdata->min_period;

	spi_offset(STp) = offset;
	spi_flags(STp) &= ~(NCR_700_DEV_NEGOTIATED_SYNC |
			    NCR_700_DEV_BEGIN_SYNC_NEGOTIATION);
	spi_flags(STp) |= NCR_700_DEV_PRINT_SYNC_NEGOTIATION;
पूर्ण

STATIC पूर्णांक
NCR_700_slave_alloc(काष्ठा scsi_device *SDp)
अणु
	SDp->hostdata = kzalloc(माप(काष्ठा NCR_700_Device_Parameters),
				GFP_KERNEL);

	अगर (!SDp->hostdata)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

STATIC पूर्णांक
NCR_700_slave_configure(काष्ठा scsi_device *SDp)
अणु
	काष्ठा NCR_700_Host_Parameters *hostdata = 
		(काष्ठा NCR_700_Host_Parameters *)SDp->host->hostdata[0];

	/* to करो here: allocate memory; build a queue_full list */
	अगर(SDp->tagged_supported) अणु
		scsi_change_queue_depth(SDp, NCR_700_DEFAULT_TAGS);
		NCR_700_set_tag_neg_state(SDp, NCR_700_START_TAG_NEGOTIATION);
	पूर्ण

	अगर(hostdata->fast) अणु
		/* Find the correct offset and period via करोमुख्य validation */
		अगर (!spi_initial_dv(SDp->sdev_target))
			spi_dv_device(SDp);
	पूर्ण अन्यथा अणु
		spi_offset(SDp->sdev_target) = 0;
		spi_period(SDp->sdev_target) = 0;
	पूर्ण
	वापस 0;
पूर्ण

STATIC व्योम
NCR_700_slave_destroy(काष्ठा scsi_device *SDp)
अणु
	kमुक्त(SDp->hostdata);
	SDp->hostdata = शून्य;
पूर्ण

अटल पूर्णांक
NCR_700_change_queue_depth(काष्ठा scsi_device *SDp, पूर्णांक depth)
अणु
	अगर (depth > NCR_700_MAX_TAGS)
		depth = NCR_700_MAX_TAGS;
	वापस scsi_change_queue_depth(SDp, depth);
पूर्ण

अटल sमाप_प्रकार
NCR_700_show_active_tags(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा scsi_device *SDp = to_scsi_device(dev);

	वापस snम_लिखो(buf, 20, "%d\n", NCR_700_get_depth(SDp));
पूर्ण

अटल काष्ठा device_attribute NCR_700_active_tags_attr = अणु
	.attr = अणु
		.name =		"active_tags",
		.mode =		S_IRUGO,
	पूर्ण,
	.show = NCR_700_show_active_tags,
पूर्ण;

STATIC काष्ठा device_attribute *NCR_700_dev_attrs[] = अणु
	&NCR_700_active_tags_attr,
	शून्य,
पूर्ण;

EXPORT_SYMBOL(NCR_700_detect);
EXPORT_SYMBOL(NCR_700_release);
EXPORT_SYMBOL(NCR_700_पूर्णांकr);

अटल काष्ठा spi_function_ढाँचा NCR_700_transport_functions =  अणु
	.set_period	= NCR_700_set_period,
	.show_period	= 1,
	.set_offset	= NCR_700_set_offset,
	.show_offset	= 1,
पूर्ण;

अटल पूर्णांक __init NCR_700_init(व्योम)
अणु
	NCR_700_transport_ढाँचा = spi_attach_transport(&NCR_700_transport_functions);
	अगर(!NCR_700_transport_ढाँचा)
		वापस -ENODEV;
	वापस 0;
पूर्ण

अटल व्योम __निकास NCR_700_निकास(व्योम)
अणु
	spi_release_transport(NCR_700_transport_ढाँचा);
पूर्ण

module_init(NCR_700_init);
module_निकास(NCR_700_निकास);

