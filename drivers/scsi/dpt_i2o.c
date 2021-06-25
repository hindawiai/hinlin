<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/***************************************************************************
                          dpti.c  -  description
                             -------------------
    begin                : Thu Sep 7 2000
    copyright            : (C) 2000 by Adaptec

			   July 30, 2001 First version being submitted
			   क्रम inclusion in the kernel.  V2.4

    See Documentation/scsi/dpti.rst क्रम history, notes, license info
    and credits
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *                                                                         *
 ***************************************************************************/
/***************************************************************************
 * Sat Dec 20 2003 Go Taniguchi <go@turbolinux.co.jp>
 - Support 2.6 kernel and DMA-mapping
 - ioctl fix क्रम raid tools
 - use schedule_समयout in दीर्घ दीर्घ loop
 **************************************************************************/

/*#घोषणा DEBUG 1 */
/*#घोषणा UARTDELAY 1 */

#समावेश <linux/module.h>
#समावेश <linux/pgtable.h>

MODULE_AUTHOR("Deanna Bonds, with _lots_ of help from Mark Salyzyn");
MODULE_DESCRIPTION("Adaptec I2O RAID Driver");

////////////////////////////////////////////////////////////////

#समावेश <linux/ioctl.h>	/* For SCSI-Passthrough */
#समावेश <linux/uaccess.h>

#समावेश <linux/स्थिति.स>
#समावेश <linux/slab.h>		/* क्रम kदो_स्मृति() */
#समावेश <linux/pci.h>		/* क्रम PCI support */
#समावेश <linux/proc_fs.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/delay.h>	/* क्रम udelay */
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>	/* क्रम prपूर्णांकk */
#समावेश <linux/sched.h>
#समावेश <linux/reboot.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/dma-mapping.h>

#समावेश <linux/समयr.h>
#समावेश <linux/माला.स>
#समावेश <linux/ioport.h>
#समावेश <linux/mutex.h>

#समावेश <यंत्र/processor.h>	/* क्रम boot_cpu_data */
#समावेश <यंत्र/पन.स>		/* क्रम virt_to_bus, etc. */

#समावेश <scsi/scsi.h>
#समावेश <scsi/scsi_cmnd.h>
#समावेश <scsi/scsi_device.h>
#समावेश <scsi/scsi_host.h>
#समावेश <scsi/scsi_tcq.h>

#समावेश "dpt/dptsig.h"
#समावेश "dpti.h"

/*============================================================================
 * Create a binary signature - this is पढ़ो by dptsig
 * Needed क्रम our management apps
 *============================================================================
 */
अटल DEFINE_MUTEX(adpt_mutex);
अटल dpt_sig_S DPTI_sig = अणु
	अणु'd', 'P', 't', 'S', 'i', 'G'पूर्ण, SIG_VERSION,
#अगर_घोषित __i386__
	PROC_INTEL, PROC_386 | PROC_486 | PROC_PENTIUM | PROC_SEXIUM,
#या_अगर defined(__ia64__)
	PROC_INTEL, PROC_IA64,
#या_अगर defined(__sparc__)
	PROC_ULTRASPARC, PROC_ULTRASPARC,
#या_अगर defined(__alpha__)
	PROC_ALPHA, PROC_ALPHA,
#अन्यथा
	(-1),(-1),
#पूर्ण_अगर
	 FT_HBADRVR, 0, OEM_DPT, OS_LINUX, CAP_OVERLAP, DEV_ALL,
	ADF_ALL_SC5, 0, 0, DPT_VERSION, DPT_REVISION, DPT_SUBREVISION,
	DPT_MONTH, DPT_DAY, DPT_YEAR, "Adaptec Linux I2O RAID Driver"
पूर्ण;




/*============================================================================
 * Globals
 *============================================================================
 */

अटल DEFINE_MUTEX(adpt_configuration_lock);

अटल काष्ठा i2o_sys_tbl *sys_tbl;
अटल dma_addr_t sys_tbl_pa;
अटल पूर्णांक sys_tbl_ind;
अटल पूर्णांक sys_tbl_len;

अटल adpt_hba* hba_chain = शून्य;
अटल पूर्णांक hba_count = 0;

अटल काष्ठा class *adpt_sysfs_class;

अटल दीर्घ adpt_unlocked_ioctl(काष्ठा file *, अचिन्हित पूर्णांक, अचिन्हित दीर्घ);
#अगर_घोषित CONFIG_COMPAT
अटल दीर्घ compat_adpt_ioctl(काष्ठा file *, अचिन्हित पूर्णांक, अचिन्हित दीर्घ);
#पूर्ण_अगर

अटल स्थिर काष्ठा file_operations adpt_fops = अणु
	.unlocked_ioctl	= adpt_unlocked_ioctl,
	.खोलो		= adpt_खोलो,
	.release	= adpt_बंद,
#अगर_घोषित CONFIG_COMPAT
	.compat_ioctl	= compat_adpt_ioctl,
#पूर्ण_अगर
	.llseek		= noop_llseek,
पूर्ण;

/* Structures and definitions क्रम synchronous message posting.
 * See adpt_i2o_post_रुको() क्रम description
 * */
काष्ठा adpt_i2o_post_रुको_data
अणु
	पूर्णांक status;
	u32 id;
	adpt_रुको_queue_head_t *wq;
	काष्ठा adpt_i2o_post_रुको_data *next;
पूर्ण;

अटल काष्ठा adpt_i2o_post_रुको_data *adpt_post_रुको_queue = शून्य;
अटल u32 adpt_post_रुको_id = 0;
अटल DEFINE_SPINLOCK(adpt_post_रुको_lock);


/*============================================================================
 * 				Functions
 *============================================================================
 */

अटल अंतरभूत पूर्णांक dpt_dma64(adpt_hba *pHba)
अणु
	वापस (माप(dma_addr_t) > 4 && (pHba)->dma64);
पूर्ण

अटल अंतरभूत u32 dma_high(dma_addr_t addr)
अणु
	वापस upper_32_bits(addr);
पूर्ण

अटल अंतरभूत u32 dma_low(dma_addr_t addr)
अणु
	वापस (u32)addr;
पूर्ण

अटल u8 adpt_पढ़ो_blink_led(adpt_hba* host)
अणु
	अगर (host->FwDebugBLEDflag_P) अणु
		अगर( पढ़ोb(host->FwDebugBLEDflag_P) == 0xbc )अणु
			वापस पढ़ोb(host->FwDebugBLEDvalue_P);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/*============================================================================
 * Scsi host ढाँचा पूर्णांकerface functions
 *============================================================================
 */

#अगर_घोषित MODULE
अटल काष्ठा pci_device_id dptids[] = अणु
	अणु PCI_DPT_VENDOR_ID, PCI_DPT_DEVICE_ID, PCI_ANY_ID, PCI_ANY_ID,पूर्ण,
	अणु PCI_DPT_VENDOR_ID, PCI_DPT_RAPTOR_DEVICE_ID, PCI_ANY_ID, PCI_ANY_ID,पूर्ण,
	अणु 0, पूर्ण
पूर्ण;
#पूर्ण_अगर

MODULE_DEVICE_TABLE(pci,dptids);

अटल पूर्णांक adpt_detect(काष्ठा scsi_host_ढाँचा* sht)
अणु
	काष्ठा pci_dev *pDev = शून्य;
	adpt_hba *pHba;
	adpt_hba *next;

	PINFO("Detecting Adaptec I2O RAID controllers...\n");

        /* search क्रम all Adatpec I2O RAID cards */
	जबतक ((pDev = pci_get_device( PCI_DPT_VENDOR_ID, PCI_ANY_ID, pDev))) अणु
		अगर(pDev->device == PCI_DPT_DEVICE_ID ||
		   pDev->device == PCI_DPT_RAPTOR_DEVICE_ID)अणु
			अगर(adpt_install_hba(sht, pDev) )अणु
				PERROR("Could not Init an I2O RAID device\n");
				PERROR("Will not try to detect others.\n");
				वापस hba_count-1;
			पूर्ण
			pci_dev_get(pDev);
		पूर्ण
	पूर्ण

	/* In INIT state, Activate IOPs */
	क्रम (pHba = hba_chain; pHba; pHba = next) अणु
		next = pHba->next;
		// Activate करोes get status , init outbound, and get hrt
		अगर (adpt_i2o_activate_hba(pHba) < 0) अणु
			adpt_i2o_delete_hba(pHba);
		पूर्ण
	पूर्ण


	/* Active IOPs in HOLD state */

rebuild_sys_tab:
	अगर (hba_chain == शून्य) 
		वापस 0;

	/*
	 * If build_sys_table fails, we समाप्त everything and bail
	 * as we can't init the IOPs w/o a प्रणाली table
	 */	
	अगर (adpt_i2o_build_sys_table() < 0) अणु
		adpt_i2o_sys_shutकरोwn();
		वापस 0;
	पूर्ण

	PDEBUG("HBA's in HOLD state\n");

	/* If IOP करोn't get online, we need to rebuild the System table */
	क्रम (pHba = hba_chain; pHba; pHba = pHba->next) अणु
		अगर (adpt_i2o_online_hba(pHba) < 0) अणु
			adpt_i2o_delete_hba(pHba);	
			जाओ rebuild_sys_tab;
		पूर्ण
	पूर्ण

	/* Active IOPs now in OPERATIONAL state */
	PDEBUG("HBA's in OPERATIONAL state\n");

	prपूर्णांकk("dpti: If you have a lot of devices this could take a few minutes.\n");
	क्रम (pHba = hba_chain; pHba; pHba = next) अणु
		next = pHba->next;
		prपूर्णांकk(KERN_INFO"%s: Reading the hardware resource table.\n", pHba->name);
		अगर (adpt_i2o_lct_get(pHba) < 0)अणु
			adpt_i2o_delete_hba(pHba);
			जारी;
		पूर्ण

		अगर (adpt_i2o_parse_lct(pHba) < 0)अणु
			adpt_i2o_delete_hba(pHba);
			जारी;
		पूर्ण
		adpt_inquiry(pHba);
	पूर्ण

	adpt_sysfs_class = class_create(THIS_MODULE, "dpt_i2o");
	अगर (IS_ERR(adpt_sysfs_class)) अणु
		prपूर्णांकk(KERN_WARNING"dpti: unable to create dpt_i2o class\n");
		adpt_sysfs_class = शून्य;
	पूर्ण

	क्रम (pHba = hba_chain; pHba; pHba = next) अणु
		next = pHba->next;
		अगर (adpt_scsi_host_alloc(pHba, sht) < 0)अणु
			adpt_i2o_delete_hba(pHba);
			जारी;
		पूर्ण
		pHba->initialized = TRUE;
		pHba->state &= ~DPTI_STATE_RESET;
		अगर (adpt_sysfs_class) अणु
			काष्ठा device *dev = device_create(adpt_sysfs_class,
				शून्य, MKDEV(DPTI_I2O_MAJOR, pHba->unit), शून्य,
				"dpti%d", pHba->unit);
			अगर (IS_ERR(dev)) अणु
				prपूर्णांकk(KERN_WARNING"dpti%d: unable to "
					"create device in dpt_i2o class\n",
					pHba->unit);
			पूर्ण
		पूर्ण
	पूर्ण

	// Register our control device node
	// nodes will need to be created in /dev to access this
	// the nodes can not be created from within the driver
	अगर (hba_count && रेजिस्टर_chrdev(DPTI_I2O_MAJOR, DPT_DRIVER, &adpt_fops)) अणु
		adpt_i2o_sys_shutकरोwn();
		वापस 0;
	पूर्ण
	वापस hba_count;
पूर्ण


अटल व्योम adpt_release(adpt_hba *pHba)
अणु
	काष्ठा Scsi_Host *shost = pHba->host;

	scsi_हटाओ_host(shost);
//	adpt_i2o_quiesce_hba(pHba);
	adpt_i2o_delete_hba(pHba);
	scsi_host_put(shost);
पूर्ण


अटल व्योम adpt_inquiry(adpt_hba* pHba)
अणु
	u32 msg[17]; 
	u32 *mptr;
	u32 *lenptr;
	पूर्णांक direction;
	पूर्णांक scsidir;
	u32 len;
	u32 reqlen;
	u8* buf;
	dma_addr_t addr;
	u8  scb[16];
	s32 rcode;

	स_रखो(msg, 0, माप(msg));
	buf = dma_alloc_coherent(&pHba->pDev->dev, 80, &addr, GFP_KERNEL);
	अगर(!buf)अणु
		prपूर्णांकk(KERN_ERR"%s: Could not allocate buffer\n",pHba->name);
		वापस;
	पूर्ण
	स_रखो((व्योम*)buf, 0, 36);
	
	len = 36;
	direction = 0x00000000;	
	scsidir  =0x40000000;	// DATA IN  (iop<--dev)

	अगर (dpt_dma64(pHba))
		reqlen = 17;		// SINGLE SGE, 64 bit
	अन्यथा
		reqlen = 14;		// SINGLE SGE, 32 bit
	/* Stick the headers on */
	msg[0] = reqlen<<16 | SGL_OFFSET_12;
	msg[1] = (0xff<<24|HOST_TID<<12|ADAPTER_TID);
	msg[2] = 0;
	msg[3]  = 0;
	// Adaptec/DPT Private stuff 
	msg[4] = I2O_CMD_SCSI_EXEC|DPT_ORGANIZATION_ID<<16;
	msg[5] = ADAPTER_TID | 1<<16 /* Interpret*/;
	/* Direction, disconnect ok | sense data | simple queue , CDBLen */
	// I2O_SCB_FLAG_ENABLE_DISCONNECT | 
	// I2O_SCB_FLAG_SIMPLE_QUEUE_TAG | 
	// I2O_SCB_FLAG_SENSE_DATA_IN_MESSAGE;
	msg[6] = scsidir|0x20a00000| 6 /* cmd len*/;

	mptr=msg+7;

	स_रखो(scb, 0, माप(scb));
	// Write SCSI command पूर्णांकo the message - always 16 byte block 
	scb[0] = INQUIRY;
	scb[1] = 0;
	scb[2] = 0;
	scb[3] = 0;
	scb[4] = 36;
	scb[5] = 0;
	// Don't care about the rest of scb

	स_नकल(mptr, scb, माप(scb));
	mptr+=4;
	lenptr=mptr++;		/* Remember me - fill in when we know */

	/* Now fill in the SGList and command */
	*lenptr = len;
	अगर (dpt_dma64(pHba)) अणु
		*mptr++ = (0x7C<<24)+(2<<16)+0x02; /* Enable 64 bit */
		*mptr++ = 1 << PAGE_SHIFT;
		*mptr++ = 0xD0000000|direction|len;
		*mptr++ = dma_low(addr);
		*mptr++ = dma_high(addr);
	पूर्ण अन्यथा अणु
		*mptr++ = 0xD0000000|direction|len;
		*mptr++ = addr;
	पूर्ण

	// Send it on it's way
	rcode = adpt_i2o_post_रुको(pHba, msg, reqlen<<2, 120);
	अगर (rcode != 0) अणु
		प्र_लिखो(pHba->detail, "Adaptec I2O RAID");
		prपूर्णांकk(KERN_INFO "%s: Inquiry Error (%d)\n",pHba->name,rcode);
		अगर (rcode != -ETIME && rcode != -EINTR)
			dma_मुक्त_coherent(&pHba->pDev->dev, 80, buf, addr);
	पूर्ण अन्यथा अणु
		स_रखो(pHba->detail, 0, माप(pHba->detail));
		स_नकल(&(pHba->detail), "Vendor: Adaptec ", 16);
		स_नकल(&(pHba->detail[16]), " Model: ", 8);
		स_नकल(&(pHba->detail[24]), (u8*) &buf[16], 16);
		स_नकल(&(pHba->detail[40]), " FW: ", 4);
		स_नकल(&(pHba->detail[44]), (u8*) &buf[32], 4);
		pHba->detail[48] = '\0';	/* precautionary */
		dma_मुक्त_coherent(&pHba->pDev->dev, 80, buf, addr);
	पूर्ण
	adpt_i2o_status_get(pHba);
	वापस ;
पूर्ण


अटल पूर्णांक adpt_slave_configure(काष्ठा scsi_device * device)
अणु
	काष्ठा Scsi_Host *host = device->host;

	अगर (host->can_queue && device->tagged_supported) अणु
		scsi_change_queue_depth(device,
				host->can_queue - 1);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक adpt_queue_lck(काष्ठा scsi_cmnd * cmd, व्योम (*करोne) (काष्ठा scsi_cmnd *))
अणु
	adpt_hba* pHba = शून्य;
	काष्ठा adpt_device* pDev = शून्य;	/* dpt per device inक्रमmation */

	cmd->scsi_करोne = करोne;
	/*
	 * SCSI REQUEST_SENSE commands will be executed स्वतःmatically by the 
	 * Host Adapter क्रम any errors, so they should not be executed 
	 * explicitly unless the Sense Data is zero indicating that no error 
	 * occurred.
	 */

	अगर ((cmd->cmnd[0] == REQUEST_SENSE) && (cmd->sense_buffer[0] != 0)) अणु
		cmd->result = (DID_OK << 16);
		cmd->scsi_करोne(cmd);
		वापस 0;
	पूर्ण

	pHba = (adpt_hba*)cmd->device->host->hostdata[0];
	अगर (!pHba) अणु
		वापस FAILED;
	पूर्ण

	rmb();
	अगर ((pHba->state) & DPTI_STATE_RESET)
		वापस SCSI_MLQUEUE_HOST_BUSY;

	// TODO अगर the cmd->device अगर offline then I may need to issue a bus rescan
	// followed by a get_lct to see अगर the device is there anymore
	अगर((pDev = (काष्ठा adpt_device*) (cmd->device->hostdata)) == शून्य) अणु
		/*
		 * First command request क्रम this device.  Set up a poपूर्णांकer
		 * to the device काष्ठाure.  This should be a TEST_UNIT_READY
		 * command from scan_scsis_single.
		 */
		अगर ((pDev = adpt_find_device(pHba, (u32)cmd->device->channel, (u32)cmd->device->id, cmd->device->lun)) == शून्य) अणु
			// TODO: अगर any luns are at this bus, scsi id then fake a TEST_UNIT_READY and INQUIRY response 
			// with type 7F (क्रम all luns less than the max क्रम this bus,id) so the lun scan will जारी.
			cmd->result = (DID_NO_CONNECT << 16);
			cmd->scsi_करोne(cmd);
			वापस 0;
		पूर्ण
		cmd->device->hostdata = pDev;
	पूर्ण
	pDev->pScsi_dev = cmd->device;

	/*
	 * If we are being called from when the device is being reset, 
	 * delay processing of the command until later.
	 */
	अगर (pDev->state & DPTI_DEV_RESET ) अणु
		वापस FAILED;
	पूर्ण
	वापस adpt_scsi_to_i2o(pHba, cmd, pDev);
पूर्ण

अटल DEF_SCSI_QCMD(adpt_queue)

अटल पूर्णांक adpt_bios_param(काष्ठा scsi_device *sdev, काष्ठा block_device *dev,
		sector_t capacity, पूर्णांक geom[])
अणु
	पूर्णांक heads=-1;
	पूर्णांक sectors=-1;
	पूर्णांक cylinders=-1;

	// *** First lets set the शेष geometry ****
	
	// If the capacity is less than ox2000
	अगर (capacity < 0x2000 ) अणु	// floppy
		heads = 18;
		sectors = 2;
	पूर्ण 
	// अन्यथा अगर between 0x2000 and 0x20000
	अन्यथा अगर (capacity < 0x20000) अणु
		heads = 64;
		sectors = 32;
	पूर्ण
	// अन्यथा अगर between 0x20000 and 0x40000
	अन्यथा अगर (capacity < 0x40000) अणु
		heads = 65;
		sectors = 63;
	पूर्ण
	// अन्यथा अगर between 0x4000 and 0x80000
	अन्यथा अगर (capacity < 0x80000) अणु
		heads = 128;
		sectors = 63;
	पूर्ण
	// अन्यथा अगर greater than 0x80000
	अन्यथा अणु
		heads = 255;
		sectors = 63;
	पूर्ण
	cylinders = sector_भाग(capacity, heads * sectors);

	// Special हाल अगर CDROM
	अगर(sdev->type == 5) अणु  // CDROM
		heads = 252;
		sectors = 63;
		cylinders = 1111;
	पूर्ण

	geom[0] = heads;
	geom[1] = sectors;
	geom[2] = cylinders;
	
	PDEBUG("adpt_bios_param: exit\n");
	वापस 0;
पूर्ण


अटल स्थिर अक्षर *adpt_info(काष्ठा Scsi_Host *host)
अणु
	adpt_hba* pHba;

	pHba = (adpt_hba *) host->hostdata[0];
	वापस (अक्षर *) (pHba->detail);
पूर्ण

अटल पूर्णांक adpt_show_info(काष्ठा seq_file *m, काष्ठा Scsi_Host *host)
अणु
	काष्ठा adpt_device* d;
	पूर्णांक id;
	पूर्णांक chan;
	adpt_hba* pHba;
	पूर्णांक unit;

	// Find HBA (host bus adapter) we are looking क्रम
	mutex_lock(&adpt_configuration_lock);
	क्रम (pHba = hba_chain; pHba; pHba = pHba->next) अणु
		अगर (pHba->host == host) अणु
			अवरोध;	/* found adapter */
		पूर्ण
	पूर्ण
	mutex_unlock(&adpt_configuration_lock);
	अगर (pHba == शून्य) अणु
		वापस 0;
	पूर्ण
	host = pHba->host;

	seq_म_लिखो(m, "Adaptec I2O RAID Driver Version: %s\n\n", DPT_I2O_VERSION);
	seq_म_लिखो(m, "%s\n", pHba->detail);
	seq_म_लिखो(m, "SCSI Host=scsi%d  Control Node=/dev/%s  irq=%d\n", 
			pHba->host->host_no, pHba->name, host->irq);
	seq_म_लिखो(m, "\tpost fifo size  = %d\n\treply fifo size = %d\n\tsg table size   = %d\n\n",
			host->can_queue, (पूर्णांक) pHba->reply_fअगरo_size , host->sg_tablesize);

	seq_माला_दो(m, "Devices:\n");
	क्रम(chan = 0; chan < MAX_CHANNEL; chan++) अणु
		क्रम(id = 0; id < MAX_ID; id++) अणु
			d = pHba->channel[chan].device[id];
			जबतक(d) अणु
				seq_म_लिखो(m,"\t%-24.24s", d->pScsi_dev->venकरोr);
				seq_म_लिखो(m," Rev: %-8.8s\n", d->pScsi_dev->rev);

				unit = d->pI2o_dev->lct_data.tid;
				seq_म_लिखो(m, "\tTID=%d, (Channel=%d, Target=%d, Lun=%llu)  (%s)\n\n",
					       unit, (पूर्णांक)d->scsi_channel, (पूर्णांक)d->scsi_id, d->scsi_lun,
					       scsi_device_online(d->pScsi_dev)? "online":"offline"); 
				d = d->next_lun;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/*
 *	Turn a poपूर्णांकer to ioctl reply data पूर्णांकo an u32 'context'
 */
अटल u32 adpt_ioctl_to_context(adpt_hba * pHba, व्योम *reply)
अणु
#अगर BITS_PER_LONG == 32
	वापस (u32)(अचिन्हित दीर्घ)reply;
#अन्यथा
	uदीर्घ flags = 0;
	u32 nr, i;

	spin_lock_irqsave(pHba->host->host_lock, flags);
	nr = ARRAY_SIZE(pHba->ioctl_reply_context);
	क्रम (i = 0; i < nr; i++) अणु
		अगर (pHba->ioctl_reply_context[i] == शून्य) अणु
			pHba->ioctl_reply_context[i] = reply;
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(pHba->host->host_lock, flags);
	अगर (i >= nr) अणु
		prपूर्णांकk(KERN_WARNING"%s: Too many outstanding "
				"ioctl commands\n", pHba->name);
		वापस (u32)-1;
	पूर्ण

	वापस i;
#पूर्ण_अगर
पूर्ण

/*
 *	Go from an u32 'context' to a poपूर्णांकer to ioctl reply data.
 */
अटल व्योम *adpt_ioctl_from_context(adpt_hba *pHba, u32 context)
अणु
#अगर BITS_PER_LONG == 32
	वापस (व्योम *)(अचिन्हित दीर्घ)context;
#अन्यथा
	व्योम *p = pHba->ioctl_reply_context[context];
	pHba->ioctl_reply_context[context] = शून्य;

	वापस p;
#पूर्ण_अगर
पूर्ण

/*===========================================================================
 * Error Handling routines
 *===========================================================================
 */

अटल पूर्णांक adpt_पात(काष्ठा scsi_cmnd * cmd)
अणु
	adpt_hba* pHba = शून्य;	/* host bus adapter काष्ठाure */
	काष्ठा adpt_device* dptdevice;	/* dpt per device inक्रमmation */
	u32 msg[5];
	पूर्णांक rcode;

	pHba = (adpt_hba*) cmd->device->host->hostdata[0];
	prपूर्णांकk(KERN_INFO"%s: Trying to Abort\n",pHba->name);
	अगर ((dptdevice = (व्योम*) (cmd->device->hostdata)) == शून्य) अणु
		prपूर्णांकk(KERN_ERR "%s: Unable to abort: No device in cmnd\n",pHba->name);
		वापस FAILED;
	पूर्ण

	स_रखो(msg, 0, माप(msg));
	msg[0] = FIVE_WORD_MSG_SIZE|SGL_OFFSET_0;
	msg[1] = I2O_CMD_SCSI_ABORT<<24|HOST_TID<<12|dptdevice->tid;
	msg[2] = 0;
	msg[3]= 0;
	/* Add 1 to aव्योम firmware treating it as invalid command */
	msg[4] = cmd->request->tag + 1;
	अगर (pHba->host)
		spin_lock_irq(pHba->host->host_lock);
	rcode = adpt_i2o_post_रुको(pHba, msg, माप(msg), FOREVER);
	अगर (pHba->host)
		spin_unlock_irq(pHba->host->host_lock);
	अगर (rcode != 0) अणु
		अगर(rcode == -EOPNOTSUPP )अणु
			prपूर्णांकk(KERN_INFO"%s: Abort cmd not supported\n",pHba->name);
			वापस FAILED;
		पूर्ण
		prपूर्णांकk(KERN_INFO"%s: Abort failed.\n",pHba->name);
		वापस FAILED;
	पूर्ण 
	prपूर्णांकk(KERN_INFO"%s: Abort complete.\n",pHba->name);
	वापस SUCCESS;
पूर्ण


#घोषणा I2O_DEVICE_RESET 0x27
// This is the same क्रम BLK and SCSI devices
// NOTE this is wrong in the i2o.h definitions
// This is not currently supported by our adapter but we issue it anyway
अटल पूर्णांक adpt_device_reset(काष्ठा scsi_cmnd* cmd)
अणु
	adpt_hba* pHba;
	u32 msg[4];
	u32 rcode;
	पूर्णांक old_state;
	काष्ठा adpt_device* d = cmd->device->hostdata;

	pHba = (व्योम*) cmd->device->host->hostdata[0];
	prपूर्णांकk(KERN_INFO"%s: Trying to reset device\n",pHba->name);
	अगर (!d) अणु
		prपूर्णांकk(KERN_INFO"%s: Reset Device: Device Not found\n",pHba->name);
		वापस FAILED;
	पूर्ण
	स_रखो(msg, 0, माप(msg));
	msg[0] = FOUR_WORD_MSG_SIZE|SGL_OFFSET_0;
	msg[1] = (I2O_DEVICE_RESET<<24|HOST_TID<<12|d->tid);
	msg[2] = 0;
	msg[3] = 0;

	अगर (pHba->host)
		spin_lock_irq(pHba->host->host_lock);
	old_state = d->state;
	d->state |= DPTI_DEV_RESET;
	rcode = adpt_i2o_post_रुको(pHba, msg,माप(msg), FOREVER);
	d->state = old_state;
	अगर (pHba->host)
		spin_unlock_irq(pHba->host->host_lock);
	अगर (rcode != 0) अणु
		अगर(rcode == -EOPNOTSUPP )अणु
			prपूर्णांकk(KERN_INFO"%s: Device reset not supported\n",pHba->name);
			वापस FAILED;
		पूर्ण
		prपूर्णांकk(KERN_INFO"%s: Device reset failed\n",pHba->name);
		वापस FAILED;
	पूर्ण अन्यथा अणु
		prपूर्णांकk(KERN_INFO"%s: Device reset successful\n",pHba->name);
		वापस SUCCESS;
	पूर्ण
पूर्ण


#घोषणा I2O_HBA_BUS_RESET 0x87
// This version of bus reset is called by the eh_error handler
अटल पूर्णांक adpt_bus_reset(काष्ठा scsi_cmnd* cmd)
अणु
	adpt_hba* pHba;
	u32 msg[4];
	u32 rcode;

	pHba = (adpt_hba*)cmd->device->host->hostdata[0];
	स_रखो(msg, 0, माप(msg));
	prपूर्णांकk(KERN_WARNING"%s: Bus reset: SCSI Bus %d: tid: %d\n",pHba->name, cmd->device->channel,pHba->channel[cmd->device->channel].tid );
	msg[0] = FOUR_WORD_MSG_SIZE|SGL_OFFSET_0;
	msg[1] = (I2O_HBA_BUS_RESET<<24|HOST_TID<<12|pHba->channel[cmd->device->channel].tid);
	msg[2] = 0;
	msg[3] = 0;
	अगर (pHba->host)
		spin_lock_irq(pHba->host->host_lock);
	rcode = adpt_i2o_post_रुको(pHba, msg,माप(msg), FOREVER);
	अगर (pHba->host)
		spin_unlock_irq(pHba->host->host_lock);
	अगर (rcode != 0) अणु
		prपूर्णांकk(KERN_WARNING"%s: Bus reset failed.\n",pHba->name);
		वापस FAILED;
	पूर्ण अन्यथा अणु
		prपूर्णांकk(KERN_WARNING"%s: Bus reset success.\n",pHba->name);
		वापस SUCCESS;
	पूर्ण
पूर्ण

// This version of reset is called by the eh_error_handler
अटल पूर्णांक __adpt_reset(काष्ठा scsi_cmnd* cmd)
अणु
	adpt_hba* pHba;
	पूर्णांक rcode;
	अक्षर name[32];

	pHba = (adpt_hba*)cmd->device->host->hostdata[0];
	म_नकलन(name, pHba->name, माप(name));
	prपूर्णांकk(KERN_WARNING"%s: Hba Reset: scsi id %d: tid: %d\n", name, cmd->device->channel, pHba->channel[cmd->device->channel].tid);
	rcode =  adpt_hba_reset(pHba);
	अगर(rcode == 0)अणु
		prपूर्णांकk(KERN_WARNING"%s: HBA reset complete\n", name);
		वापस SUCCESS;
	पूर्ण अन्यथा अणु
		prपूर्णांकk(KERN_WARNING"%s: HBA reset failed (%x)\n", name, rcode);
		वापस FAILED;
	पूर्ण
पूर्ण

अटल पूर्णांक adpt_reset(काष्ठा scsi_cmnd* cmd)
अणु
	पूर्णांक rc;

	spin_lock_irq(cmd->device->host->host_lock);
	rc = __adpt_reset(cmd);
	spin_unlock_irq(cmd->device->host->host_lock);

	वापस rc;
पूर्ण

// This version of reset is called by the ioctls and indirectly from eh_error_handler via adpt_reset
अटल पूर्णांक adpt_hba_reset(adpt_hba* pHba)
अणु
	पूर्णांक rcode;

	pHba->state |= DPTI_STATE_RESET;

	// Activate करोes get status , init outbound, and get hrt
	अगर ((rcode=adpt_i2o_activate_hba(pHba)) < 0) अणु
		prपूर्णांकk(KERN_ERR "%s: Could not activate\n", pHba->name);
		adpt_i2o_delete_hba(pHba);
		वापस rcode;
	पूर्ण

	अगर ((rcode=adpt_i2o_build_sys_table()) < 0) अणु
		adpt_i2o_delete_hba(pHba);
		वापस rcode;
	पूर्ण
	PDEBUG("%s: in HOLD state\n",pHba->name);

	अगर ((rcode=adpt_i2o_online_hba(pHba)) < 0) अणु
		adpt_i2o_delete_hba(pHba);	
		वापस rcode;
	पूर्ण
	PDEBUG("%s: in OPERATIONAL state\n",pHba->name);

	अगर ((rcode=adpt_i2o_lct_get(pHba)) < 0)अणु
		adpt_i2o_delete_hba(pHba);
		वापस rcode;
	पूर्ण

	अगर ((rcode=adpt_i2o_reparse_lct(pHba)) < 0)अणु
		adpt_i2o_delete_hba(pHba);
		वापस rcode;
	पूर्ण
	pHba->state &= ~DPTI_STATE_RESET;

	scsi_host_complete_all_commands(pHba->host, DID_RESET);
	वापस 0;	/* वापस success */
पूर्ण

/*===========================================================================
 * 
 *===========================================================================
 */


अटल व्योम adpt_i2o_sys_shutकरोwn(व्योम)
अणु
	adpt_hba *pHba, *pNext;
	काष्ठा adpt_i2o_post_रुको_data *p1, *old;

	prपूर्णांकk(KERN_INFO "Shutting down Adaptec I2O controllers.\n");
	prपूर्णांकk(KERN_INFO "   This could take a few minutes if there are many devices attached\n");
	/* Delete all IOPs from the controller chain */
	/* They should have alपढ़ोy been released by the
	 * scsi-core
	 */
	क्रम (pHba = hba_chain; pHba; pHba = pNext) अणु
		pNext = pHba->next;
		adpt_i2o_delete_hba(pHba);
	पूर्ण

	/* Remove any समयकरोut entries from the रुको queue.  */
//	spin_lock_irqsave(&adpt_post_रुको_lock, flags);
	/* Nothing should be outstanding at this poपूर्णांक so just
	 * मुक्त them 
	 */
	क्रम(p1 = adpt_post_रुको_queue; p1;) अणु
		old = p1;
		p1 = p1->next;
		kमुक्त(old);
	पूर्ण
//	spin_unlock_irqrestore(&adpt_post_रुको_lock, flags);
	adpt_post_रुको_queue = शून्य;

	prपूर्णांकk(KERN_INFO "Adaptec I2O controllers down.\n");
पूर्ण

अटल पूर्णांक adpt_install_hba(काष्ठा scsi_host_ढाँचा* sht, काष्ठा pci_dev* pDev)
अणु

	adpt_hba* pHba = शून्य;
	adpt_hba* p = शून्य;
	uदीर्घ base_addr0_phys = 0;
	uदीर्घ base_addr1_phys = 0;
	u32 hba_map0_area_size = 0;
	u32 hba_map1_area_size = 0;
	व्योम __iomem *base_addr_virt = शून्य;
	व्योम __iomem *msg_addr_virt = शून्य;
	पूर्णांक dma64 = 0;

	पूर्णांक raptorFlag = FALSE;

	अगर(pci_enable_device(pDev)) अणु
		वापस -EINVAL;
	पूर्ण

	अगर (pci_request_regions(pDev, "dpt_i2o")) अणु
		PERROR("dpti: adpt_config_hba: pci request region failed\n");
		वापस -EINVAL;
	पूर्ण

	pci_set_master(pDev);

	/*
	 *	See अगर we should enable dma64 mode.
	 */
	अगर (माप(dma_addr_t) > 4 &&
	    dma_get_required_mask(&pDev->dev) > DMA_BIT_MASK(32) &&
	    dma_set_mask(&pDev->dev, DMA_BIT_MASK(64)) == 0)
		dma64 = 1;

	अगर (!dma64 && dma_set_mask(&pDev->dev, DMA_BIT_MASK(32)) != 0)
		वापस -EINVAL;

	/* adapter only supports message blocks below 4GB */
	dma_set_coherent_mask(&pDev->dev, DMA_BIT_MASK(32));

	base_addr0_phys = pci_resource_start(pDev,0);
	hba_map0_area_size = pci_resource_len(pDev,0);

	// Check अगर standard PCI card or single BAR Raptor
	अगर(pDev->device == PCI_DPT_DEVICE_ID)अणु
		अगर(pDev->subप्रणाली_device >=0xc032 && pDev->subप्रणाली_device <= 0xc03b)अणु
			// Raptor card with this device id needs 4M
			hba_map0_area_size = 0x400000;
		पूर्ण अन्यथा अणु // Not Raptor - it is a PCI card
			अगर(hba_map0_area_size > 0x100000 )अणु 
				hba_map0_area_size = 0x100000;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु// Raptor split BAR config
		// Use BAR1 in this configuration
		base_addr1_phys = pci_resource_start(pDev,1);
		hba_map1_area_size = pci_resource_len(pDev,1);
		raptorFlag = TRUE;
	पूर्ण

#अगर BITS_PER_LONG == 64
	/*
	 *	The original Adaptec 64 bit driver has this comment here:
	 *	"x86_64 machines need more optimal mappings"
	 *
	 *	I assume some HBAs report ridiculously large mappings
	 *	and we need to limit them on platक्रमms with IOMMUs.
	 */
	अगर (raptorFlag == TRUE) अणु
		अगर (hba_map0_area_size > 128)
			hba_map0_area_size = 128;
		अगर (hba_map1_area_size > 524288)
			hba_map1_area_size = 524288;
	पूर्ण अन्यथा अणु
		अगर (hba_map0_area_size > 524288)
			hba_map0_area_size = 524288;
	पूर्ण
#पूर्ण_अगर

	base_addr_virt = ioremap(base_addr0_phys,hba_map0_area_size);
	अगर (!base_addr_virt) अणु
		pci_release_regions(pDev);
		PERROR("dpti: adpt_config_hba: io remap failed\n");
		वापस -EINVAL;
	पूर्ण

        अगर(raptorFlag == TRUE) अणु
		msg_addr_virt = ioremap(base_addr1_phys, hba_map1_area_size );
		अगर (!msg_addr_virt) अणु
			PERROR("dpti: adpt_config_hba: io remap failed on BAR1\n");
			iounmap(base_addr_virt);
			pci_release_regions(pDev);
			वापस -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अणु
		msg_addr_virt = base_addr_virt;
	पूर्ण
	
	// Allocate and zero the data काष्ठाure
	pHba = kzalloc(माप(adpt_hba), GFP_KERNEL);
	अगर (!pHba) अणु
		अगर (msg_addr_virt != base_addr_virt)
			iounmap(msg_addr_virt);
		iounmap(base_addr_virt);
		pci_release_regions(pDev);
		वापस -ENOMEM;
	पूर्ण

	mutex_lock(&adpt_configuration_lock);

	अगर(hba_chain != शून्य)अणु
		क्रम(p = hba_chain; p->next; p = p->next);
		p->next = pHba;
	पूर्ण अन्यथा अणु
		hba_chain = pHba;
	पूर्ण
	pHba->next = शून्य;
	pHba->unit = hba_count;
	प्र_लिखो(pHba->name, "dpti%d", hba_count);
	hba_count++;
	
	mutex_unlock(&adpt_configuration_lock);

	pHba->pDev = pDev;
	pHba->base_addr_phys = base_addr0_phys;

	// Set up the Virtual Base Address of the I2O Device
	pHba->base_addr_virt = base_addr_virt;
	pHba->msg_addr_virt = msg_addr_virt;
	pHba->irq_mask = base_addr_virt+0x30;
	pHba->post_port = base_addr_virt+0x40;
	pHba->reply_port = base_addr_virt+0x44;

	pHba->hrt = शून्य;
	pHba->lct = शून्य;
	pHba->lct_size = 0;
	pHba->status_block = शून्य;
	pHba->post_count = 0;
	pHba->state = DPTI_STATE_RESET;
	pHba->pDev = pDev;
	pHba->devices = शून्य;
	pHba->dma64 = dma64;

	// Initializing the spinlocks
	spin_lock_init(&pHba->state_lock);
	spin_lock_init(&adpt_post_रुको_lock);

	अगर(raptorFlag == 0)अणु
		prपूर्णांकk(KERN_INFO "Adaptec I2O RAID controller"
				 " %d at %p size=%x irq=%d%s\n", 
			hba_count-1, base_addr_virt,
			hba_map0_area_size, pDev->irq,
			dma64 ? " (64-bit DMA)" : "");
	पूर्ण अन्यथा अणु
		prपूर्णांकk(KERN_INFO"Adaptec I2O RAID controller %d irq=%d%s\n",
			hba_count-1, pDev->irq,
			dma64 ? " (64-bit DMA)" : "");
		prपूर्णांकk(KERN_INFO"     BAR0 %p - size= %x\n",base_addr_virt,hba_map0_area_size);
		prपूर्णांकk(KERN_INFO"     BAR1 %p - size= %x\n",msg_addr_virt,hba_map1_area_size);
	पूर्ण

	अगर (request_irq (pDev->irq, adpt_isr, IRQF_SHARED, pHba->name, pHba)) अणु
		prपूर्णांकk(KERN_ERR"%s: Couldn't register IRQ %d\n", pHba->name, pDev->irq);
		adpt_i2o_delete_hba(pHba);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण


अटल व्योम adpt_i2o_delete_hba(adpt_hba* pHba)
अणु
	adpt_hba* p1;
	adpt_hba* p2;
	काष्ठा i2o_device* d;
	काष्ठा i2o_device* next;
	पूर्णांक i;
	पूर्णांक j;
	काष्ठा adpt_device* pDev;
	काष्ठा adpt_device* pNext;


	mutex_lock(&adpt_configuration_lock);
	अगर(pHba->host)अणु
		मुक्त_irq(pHba->host->irq, pHba);
	पूर्ण
	p2 = शून्य;
	क्रम( p1 = hba_chain; p1; p2 = p1,p1=p1->next)अणु
		अगर(p1 == pHba) अणु
			अगर(p2) अणु
				p2->next = p1->next;
			पूर्ण अन्यथा अणु
				hba_chain = p1->next;
			पूर्ण
			अवरोध;
		पूर्ण
	पूर्ण

	hba_count--;
	mutex_unlock(&adpt_configuration_lock);

	iounmap(pHba->base_addr_virt);
	pci_release_regions(pHba->pDev);
	अगर(pHba->msg_addr_virt != pHba->base_addr_virt)अणु
		iounmap(pHba->msg_addr_virt);
	पूर्ण
	अगर(pHba->FwDebugBuffer_P)
	   	iounmap(pHba->FwDebugBuffer_P);
	अगर(pHba->hrt) अणु
		dma_मुक्त_coherent(&pHba->pDev->dev,
			pHba->hrt->num_entries * pHba->hrt->entry_len << 2,
			pHba->hrt, pHba->hrt_pa);
	पूर्ण
	अगर(pHba->lct) अणु
		dma_मुक्त_coherent(&pHba->pDev->dev, pHba->lct_size,
			pHba->lct, pHba->lct_pa);
	पूर्ण
	अगर(pHba->status_block) अणु
		dma_मुक्त_coherent(&pHba->pDev->dev, माप(i2o_status_block),
			pHba->status_block, pHba->status_block_pa);
	पूर्ण
	अगर(pHba->reply_pool) अणु
		dma_मुक्त_coherent(&pHba->pDev->dev,
			pHba->reply_fअगरo_size * REPLY_FRAME_SIZE * 4,
			pHba->reply_pool, pHba->reply_pool_pa);
	पूर्ण

	क्रम(d = pHba->devices; d ; d = next)अणु
		next = d->next;
		kमुक्त(d);
	पूर्ण
	क्रम(i = 0 ; i < pHba->top_scsi_channel ; i++)अणु
		क्रम(j = 0; j < MAX_ID; j++)अणु
			अगर(pHba->channel[i].device[j] != शून्य)अणु
				क्रम(pDev = pHba->channel[i].device[j]; pDev; pDev = pNext)अणु
					pNext = pDev->next_lun;
					kमुक्त(pDev);
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
	pci_dev_put(pHba->pDev);
	अगर (adpt_sysfs_class)
		device_destroy(adpt_sysfs_class,
				MKDEV(DPTI_I2O_MAJOR, pHba->unit));
	kमुक्त(pHba);

	अगर(hba_count <= 0)अणु
		unरेजिस्टर_chrdev(DPTI_I2O_MAJOR, DPT_DRIVER);   
		अगर (adpt_sysfs_class) अणु
			class_destroy(adpt_sysfs_class);
			adpt_sysfs_class = शून्य;
		पूर्ण
	पूर्ण
पूर्ण

अटल काष्ठा adpt_device* adpt_find_device(adpt_hba* pHba, u32 chan, u32 id, u64 lun)
अणु
	काष्ठा adpt_device* d;

	अगर (chan >= MAX_CHANNEL)
		वापस शून्य;
	
	d = pHba->channel[chan].device[id];
	अगर(!d || d->tid == 0) अणु
		वापस शून्य;
	पूर्ण

	/* If it is the only lun at that address then this should match*/
	अगर(d->scsi_lun == lun)अणु
		वापस d;
	पूर्ण

	/* अन्यथा we need to look through all the luns */
	क्रम(d=d->next_lun ; d ; d = d->next_lun)अणु
		अगर(d->scsi_lun == lun)अणु
			वापस d;
		पूर्ण
	पूर्ण
	वापस शून्य;
पूर्ण


अटल पूर्णांक adpt_i2o_post_रुको(adpt_hba* pHba, u32* msg, पूर्णांक len, पूर्णांक समयout)
अणु
	// I used my own version of the WAIT_QUEUE_HEAD
	// to handle some version dअगरferences
	// When embedded in the kernel this could go back to the vanilla one
	ADPT_DECLARE_WAIT_QUEUE_HEAD(adpt_wq_i2o_post);
	पूर्णांक status = 0;
	uदीर्घ flags = 0;
	काष्ठा adpt_i2o_post_रुको_data *p1, *p2;
	काष्ठा adpt_i2o_post_रुको_data *रुको_data =
		kदो_स्मृति(माप(काष्ठा adpt_i2o_post_रुको_data), GFP_ATOMIC);
	DECLARE_WAITQUEUE(रुको, current);

	अगर (!रुको_data)
		वापस -ENOMEM;

	/*
	 * The spin locking is needed to keep anyone from playing
	 * with the queue poपूर्णांकers and id जबतक we करो the same
	 */
	spin_lock_irqsave(&adpt_post_रुको_lock, flags);
       // TODO we need a MORE unique way of getting ids
       // to support async LCT get
	रुको_data->next = adpt_post_रुको_queue;
	adpt_post_रुको_queue = रुको_data;
	adpt_post_रुको_id++;
	adpt_post_रुको_id &= 0x7fff;
	रुको_data->id =  adpt_post_रुको_id;
	spin_unlock_irqrestore(&adpt_post_रुको_lock, flags);

	रुको_data->wq = &adpt_wq_i2o_post;
	रुको_data->status = -ETIMEDOUT;

	add_रुको_queue(&adpt_wq_i2o_post, &रुको);

	msg[2] |= 0x80000000 | ((u32)रुको_data->id);
	समयout *= HZ;
	अगर((status = adpt_i2o_post_this(pHba, msg, len)) == 0)अणु
		set_current_state(TASK_INTERRUPTIBLE);
		अगर(pHba->host)
			spin_unlock_irq(pHba->host->host_lock);
		अगर (!समयout)
			schedule();
		अन्यथाअणु
			समयout = schedule_समयout(समयout);
			अगर (समयout == 0) अणु
				// I/O issued, but cannot get result in
				// specअगरied समय. Freeing resorces is
				// dangerous.
				status = -ETIME;
			पूर्ण
		पूर्ण
		अगर(pHba->host)
			spin_lock_irq(pHba->host->host_lock);
	पूर्ण
	हटाओ_रुको_queue(&adpt_wq_i2o_post, &रुको);

	अगर(status == -ETIMEDOUT)अणु
		prपूर्णांकk(KERN_INFO"dpti%d: POST WAIT TIMEOUT\n",pHba->unit);
		// We will have to मुक्त the रुको_data memory during shutकरोwn
		वापस status;
	पूर्ण

	/* Remove the entry from the queue.  */
	p2 = शून्य;
	spin_lock_irqsave(&adpt_post_रुको_lock, flags);
	क्रम(p1 = adpt_post_रुको_queue; p1; p2 = p1, p1 = p1->next) अणु
		अगर(p1 == रुको_data) अणु
			अगर(p1->status == I2O_DETAIL_STATUS_UNSUPPORTED_FUNCTION ) अणु
				status = -EOPNOTSUPP;
			पूर्ण
			अगर(p2) अणु
				p2->next = p1->next;
			पूर्ण अन्यथा अणु
				adpt_post_रुको_queue = p1->next;
			पूर्ण
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&adpt_post_रुको_lock, flags);

	kमुक्त(रुको_data);

	वापस status;
पूर्ण


अटल s32 adpt_i2o_post_this(adpt_hba* pHba, u32* data, पूर्णांक len)
अणु

	u32 m = EMPTY_QUEUE;
	u32 __iomem *msg;
	uदीर्घ समयout = jअगरfies + 30*HZ;
	करो अणु
		rmb();
		m = पढ़ोl(pHba->post_port);
		अगर (m != EMPTY_QUEUE) अणु
			अवरोध;
		पूर्ण
		अगर(समय_after(jअगरfies,समयout))अणु
			prपूर्णांकk(KERN_WARNING"dpti%d: Timeout waiting for message frame!\n", pHba->unit);
			वापस -ETIMEDOUT;
		पूर्ण
		schedule_समयout_unपूर्णांकerruptible(1);
	पूर्ण जबतक(m == EMPTY_QUEUE);
		
	msg = pHba->msg_addr_virt + m;
	स_नकल_toio(msg, data, len);
	wmb();

	//post message
	ग_लिखोl(m, pHba->post_port);
	wmb();

	वापस 0;
पूर्ण


अटल व्योम adpt_i2o_post_रुको_complete(u32 context, पूर्णांक status)
अणु
	काष्ठा adpt_i2o_post_रुको_data *p1 = शून्य;
	/*
	 * We need to search through the adpt_post_रुको
	 * queue to see अगर the given message is still
	 * outstanding.  If not, it means that the IOP
	 * took दीर्घer to respond to the message than we
	 * had allowed and समयr has alपढ़ोy expired.
	 * Not much we can करो about that except log
	 * it क्रम debug purposes, increase समयout, and recompile
	 *
	 * Lock needed to keep anyone from moving queue poपूर्णांकers
	 * around जबतक we're looking through them.
	 */

	context &= 0x7fff;

	spin_lock(&adpt_post_रुको_lock);
	क्रम(p1 = adpt_post_रुको_queue; p1; p1 = p1->next) अणु
		अगर(p1->id == context) अणु
			p1->status = status;
			spin_unlock(&adpt_post_रुको_lock);
			wake_up_पूर्णांकerruptible(p1->wq);
			वापस;
		पूर्ण
	पूर्ण
	spin_unlock(&adpt_post_रुको_lock);
        // If this happens we lose commands that probably really completed
	prपूर्णांकk(KERN_DEBUG"dpti: Could Not find task %d in wait queue\n",context);
	prपूर्णांकk(KERN_DEBUG"      Tasks in wait queue:\n");
	क्रम(p1 = adpt_post_रुको_queue; p1; p1 = p1->next) अणु
		prपूर्णांकk(KERN_DEBUG"           %d\n",p1->id);
	पूर्ण
	वापस;
पूर्ण

अटल s32 adpt_i2o_reset_hba(adpt_hba* pHba)			
अणु
	u32 msg[8];
	u8* status;
	dma_addr_t addr;
	u32 m = EMPTY_QUEUE ;
	uदीर्घ समयout = jअगरfies + (TMOUT_IOPRESET*HZ);

	अगर(pHba->initialized  == FALSE) अणु	// First समय reset should be quick
		समयout = jअगरfies + (25*HZ);
	पूर्ण अन्यथा अणु
		adpt_i2o_quiesce_hba(pHba);
	पूर्ण

	करो अणु
		rmb();
		m = पढ़ोl(pHba->post_port);
		अगर (m != EMPTY_QUEUE) अणु
			अवरोध;
		पूर्ण
		अगर(समय_after(jअगरfies,समयout))अणु
			prपूर्णांकk(KERN_WARNING"Timeout waiting for message!\n");
			वापस -ETIMEDOUT;
		पूर्ण
		schedule_समयout_unपूर्णांकerruptible(1);
	पूर्ण जबतक (m == EMPTY_QUEUE);

	status = dma_alloc_coherent(&pHba->pDev->dev, 4, &addr, GFP_KERNEL);
	अगर(status == शून्य) अणु
		adpt_send_nop(pHba, m);
		prपूर्णांकk(KERN_ERR"IOP reset failed - no free memory.\n");
		वापस -ENOMEM;
	पूर्ण

	msg[0]=EIGHT_WORD_MSG_SIZE|SGL_OFFSET_0;
	msg[1]=I2O_CMD_ADAPTER_RESET<<24|HOST_TID<<12|ADAPTER_TID;
	msg[2]=0;
	msg[3]=0;
	msg[4]=0;
	msg[5]=0;
	msg[6]=dma_low(addr);
	msg[7]=dma_high(addr);

	स_नकल_toio(pHba->msg_addr_virt+m, msg, माप(msg));
	wmb();
	ग_लिखोl(m, pHba->post_port);
	wmb();

	जबतक(*status == 0)अणु
		अगर(समय_after(jअगरfies,समयout))अणु
			prपूर्णांकk(KERN_WARNING"%s: IOP Reset Timeout\n",pHba->name);
			/* We lose 4 bytes of "status" here, but we cannot
			   मुक्त these because controller may awake and corrupt
			   those bytes at any समय */
			/* dma_मुक्त_coherent(&pHba->pDev->dev, 4, buf, addr); */
			वापस -ETIMEDOUT;
		पूर्ण
		rmb();
		schedule_समयout_unपूर्णांकerruptible(1);
	पूर्ण

	अगर(*status == 0x01 /*I2O_EXEC_IOP_RESET_IN_PROGRESS*/) अणु
		PDEBUG("%s: Reset in progress...\n", pHba->name);
		// Here we रुको क्रम message frame to become available
		// indicated that reset has finished
		करो अणु
			rmb();
			m = पढ़ोl(pHba->post_port);
			अगर (m != EMPTY_QUEUE) अणु
				अवरोध;
			पूर्ण
			अगर(समय_after(jअगरfies,समयout))अणु
				prपूर्णांकk(KERN_ERR "%s:Timeout waiting for IOP Reset.\n",pHba->name);
				/* We lose 4 bytes of "status" here, but we
				   cannot मुक्त these because controller may
				   awake and corrupt those bytes at any समय */
				/* dma_मुक्त_coherent(&pHba->pDev->dev, 4, buf, addr); */
				वापस -ETIMEDOUT;
			पूर्ण
			schedule_समयout_unपूर्णांकerruptible(1);
		पूर्ण जबतक (m == EMPTY_QUEUE);
		// Flush the offset
		adpt_send_nop(pHba, m);
	पूर्ण
	adpt_i2o_status_get(pHba);
	अगर(*status == 0x02 ||
			pHba->status_block->iop_state != ADAPTER_STATE_RESET) अणु
		prपूर्णांकk(KERN_WARNING"%s: Reset reject, trying to clear\n",
				pHba->name);
	पूर्ण अन्यथा अणु
		PDEBUG("%s: Reset completed.\n", pHba->name);
	पूर्ण

	dma_मुक्त_coherent(&pHba->pDev->dev, 4, status, addr);
#अगर_घोषित UARTDELAY
	// This delay is to allow someone attached to the card through the debug UART to 
	// set up the dump levels that they want beक्रमe the rest of the initialization sequence
	adpt_delay(20000);
#पूर्ण_अगर
	वापस 0;
पूर्ण


अटल पूर्णांक adpt_i2o_parse_lct(adpt_hba* pHba)
अणु
	पूर्णांक i;
	पूर्णांक max;
	पूर्णांक tid;
	काष्ठा i2o_device *d;
	i2o_lct *lct = pHba->lct;
	u8 bus_no = 0;
	s16 scsi_id;
	u64 scsi_lun;
	u32 buf[10]; // larger than 7, or 8 ...
	काष्ठा adpt_device* pDev; 
	
	अगर (lct == शून्य) अणु
		prपूर्णांकk(KERN_ERR "%s: LCT is empty???\n",pHba->name);
		वापस -1;
	पूर्ण
	
	max = lct->table_size;	
	max -= 3;
	max /= 9;

	क्रम(i=0;i<max;i++) अणु
		अगर( lct->lct_entry[i].user_tid != 0xfff)अणु
			/*
			 * If we have hidden devices, we need to inक्रमm the upper layers about
			 * the possible maximum id reference to handle device access when
			 * an array is disassembled. This code has no other purpose but to
			 * allow us future access to devices that are currently hidden
			 * behind arrays, hotspares or have not been configured (JBOD mode).
			 */
			अगर( lct->lct_entry[i].class_id != I2O_CLASS_RANDOM_BLOCK_STORAGE &&
			    lct->lct_entry[i].class_id != I2O_CLASS_SCSI_PERIPHERAL &&
			    lct->lct_entry[i].class_id != I2O_CLASS_FIBRE_CHANNEL_PERIPHERAL )अणु
			    	जारी;
			पूर्ण
			tid = lct->lct_entry[i].tid;
			// I2O_DPT_DEVICE_INFO_GROUP_NO;
			अगर(adpt_i2o_query_scalar(pHba, tid, 0x8000, -1, buf, 32)<0) अणु
				जारी;
			पूर्ण
			bus_no = buf[0]>>16;
			scsi_id = buf[1];
			scsi_lun = scsilun_to_पूर्णांक((काष्ठा scsi_lun *)&buf[2]);
			अगर(bus_no >= MAX_CHANNEL) अणु	// Something wrong skip it
				prपूर्णांकk(KERN_WARNING"%s: Channel number %d out of range \n", pHba->name, bus_no);
				जारी;
			पूर्ण
			अगर (scsi_id >= MAX_ID)अणु
				prपूर्णांकk(KERN_WARNING"%s: SCSI ID %d out of range \n", pHba->name, bus_no);
				जारी;
			पूर्ण
			अगर(bus_no > pHba->top_scsi_channel)अणु
				pHba->top_scsi_channel = bus_no;
			पूर्ण
			अगर(scsi_id > pHba->top_scsi_id)अणु
				pHba->top_scsi_id = scsi_id;
			पूर्ण
			अगर(scsi_lun > pHba->top_scsi_lun)अणु
				pHba->top_scsi_lun = scsi_lun;
			पूर्ण
			जारी;
		पूर्ण
		d = kदो_स्मृति(माप(काष्ठा i2o_device), GFP_KERNEL);
		अगर(d==शून्य)
		अणु
			prपूर्णांकk(KERN_CRIT"%s: Out of memory for I2O device data.\n",pHba->name);
			वापस -ENOMEM;
		पूर्ण
		
		d->controller = pHba;
		d->next = शून्य;

		स_नकल(&d->lct_data, &lct->lct_entry[i], माप(i2o_lct_entry));

		d->flags = 0;
		tid = d->lct_data.tid;
		adpt_i2o_report_hba_unit(pHba, d);
		adpt_i2o_install_device(pHba, d);
	पूर्ण
	bus_no = 0;
	क्रम(d = pHba->devices; d ; d = d->next) अणु
		अगर(d->lct_data.class_id  == I2O_CLASS_BUS_ADAPTER_PORT ||
		   d->lct_data.class_id  == I2O_CLASS_FIBRE_CHANNEL_PORT)अणु
			tid = d->lct_data.tid;
			// TODO get the bus_no from hrt-but क्रम now they are in order
			//bus_no = 
			अगर(bus_no > pHba->top_scsi_channel)अणु
				pHba->top_scsi_channel = bus_no;
			पूर्ण
			pHba->channel[bus_no].type = d->lct_data.class_id;
			pHba->channel[bus_no].tid = tid;
			अगर(adpt_i2o_query_scalar(pHba, tid, 0x0200, -1, buf, 28)>=0)
			अणु
				pHba->channel[bus_no].scsi_id = buf[1];
				PDEBUG("Bus %d - SCSI ID %d.\n", bus_no, buf[1]);
			पूर्ण
			// TODO हटाओ - this is just until we get from hrt
			bus_no++;
			अगर(bus_no >= MAX_CHANNEL) अणु	// Something wrong skip it
				prपूर्णांकk(KERN_WARNING"%s: Channel number %d out of range - LCT\n", pHba->name, bus_no);
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	// Setup adpt_device table
	क्रम(d = pHba->devices; d ; d = d->next) अणु
		अगर(d->lct_data.class_id  == I2O_CLASS_RANDOM_BLOCK_STORAGE ||
		   d->lct_data.class_id  == I2O_CLASS_SCSI_PERIPHERAL ||
		   d->lct_data.class_id  == I2O_CLASS_FIBRE_CHANNEL_PERIPHERAL )अणु

			tid = d->lct_data.tid;
			scsi_id = -1;
			// I2O_DPT_DEVICE_INFO_GROUP_NO;
			अगर(adpt_i2o_query_scalar(pHba, tid, 0x8000, -1, buf, 32)>=0) अणु
				bus_no = buf[0]>>16;
				scsi_id = buf[1];
				scsi_lun = scsilun_to_पूर्णांक((काष्ठा scsi_lun *)&buf[2]);
				अगर(bus_no >= MAX_CHANNEL) अणु	// Something wrong skip it
					जारी;
				पूर्ण
				अगर (scsi_id >= MAX_ID) अणु
					जारी;
				पूर्ण
				अगर( pHba->channel[bus_no].device[scsi_id] == शून्य)अणु
					pDev =  kzalloc(माप(काष्ठा adpt_device),GFP_KERNEL);
					अगर(pDev == शून्य) अणु
						वापस -ENOMEM;
					पूर्ण
					pHba->channel[bus_no].device[scsi_id] = pDev;
				पूर्ण अन्यथा अणु
					क्रम( pDev = pHba->channel[bus_no].device[scsi_id];	
							pDev->next_lun; pDev = pDev->next_lun)अणु
					पूर्ण
					pDev->next_lun = kzalloc(माप(काष्ठा adpt_device),GFP_KERNEL);
					अगर(pDev->next_lun == शून्य) अणु
						वापस -ENOMEM;
					पूर्ण
					pDev = pDev->next_lun;
				पूर्ण
				pDev->tid = tid;
				pDev->scsi_channel = bus_no;
				pDev->scsi_id = scsi_id;
				pDev->scsi_lun = scsi_lun;
				pDev->pI2o_dev = d;
				d->owner = pDev;
				pDev->type = (buf[0])&0xff;
				pDev->flags = (buf[0]>>8)&0xff;
				अगर(scsi_id > pHba->top_scsi_id)अणु
					pHba->top_scsi_id = scsi_id;
				पूर्ण
				अगर(scsi_lun > pHba->top_scsi_lun)अणु
					pHba->top_scsi_lun = scsi_lun;
				पूर्ण
			पूर्ण
			अगर(scsi_id == -1)अणु
				prपूर्णांकk(KERN_WARNING"Could not find SCSI ID for %s\n",
						d->lct_data.identity_tag);
			पूर्ण
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण


/*
 *	Each I2O controller has a chain of devices on it - these match
 *	the useful parts of the LCT of the board.
 */
 
अटल पूर्णांक adpt_i2o_install_device(adpt_hba* pHba, काष्ठा i2o_device *d)
अणु
	mutex_lock(&adpt_configuration_lock);
	d->controller=pHba;
	d->owner=शून्य;
	d->next=pHba->devices;
	d->prev=शून्य;
	अगर (pHba->devices != शून्य)अणु
		pHba->devices->prev=d;
	पूर्ण
	pHba->devices=d;
	*d->dev_name = 0;

	mutex_unlock(&adpt_configuration_lock);
	वापस 0;
पूर्ण

अटल पूर्णांक adpt_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	पूर्णांक minor;
	adpt_hba* pHba;

	mutex_lock(&adpt_mutex);
	//TODO check क्रम root access
	//
	minor = iminor(inode);
	अगर (minor >= hba_count) अणु
		mutex_unlock(&adpt_mutex);
		वापस -ENXIO;
	पूर्ण
	mutex_lock(&adpt_configuration_lock);
	क्रम (pHba = hba_chain; pHba; pHba = pHba->next) अणु
		अगर (pHba->unit == minor) अणु
			अवरोध;	/* found adapter */
		पूर्ण
	पूर्ण
	अगर (pHba == शून्य) अणु
		mutex_unlock(&adpt_configuration_lock);
		mutex_unlock(&adpt_mutex);
		वापस -ENXIO;
	पूर्ण

//	अगर(pHba->in_use)अणु
	//	mutex_unlock(&adpt_configuration_lock);
//		वापस -EBUSY;
//	पूर्ण

	pHba->in_use = 1;
	mutex_unlock(&adpt_configuration_lock);
	mutex_unlock(&adpt_mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक adpt_बंद(काष्ठा inode *inode, काष्ठा file *file)
अणु
	पूर्णांक minor;
	adpt_hba* pHba;

	minor = iminor(inode);
	अगर (minor >= hba_count) अणु
		वापस -ENXIO;
	पूर्ण
	mutex_lock(&adpt_configuration_lock);
	क्रम (pHba = hba_chain; pHba; pHba = pHba->next) अणु
		अगर (pHba->unit == minor) अणु
			अवरोध;	/* found adapter */
		पूर्ण
	पूर्ण
	mutex_unlock(&adpt_configuration_lock);
	अगर (pHba == शून्य) अणु
		वापस -ENXIO;
	पूर्ण

	pHba->in_use = 0;

	वापस 0;
पूर्ण


अटल पूर्णांक adpt_i2o_passthru(adpt_hba* pHba, u32 __user *arg)
अणु
	u32 msg[MAX_MESSAGE_SIZE];
	u32* reply = शून्य;
	u32 size = 0;
	u32 reply_size = 0;
	u32 __user *user_msg = arg;
	u32 __user * user_reply = शून्य;
	व्योम **sg_list = शून्य;
	u32 sg_offset = 0;
	u32 sg_count = 0;
	पूर्णांक sg_index = 0;
	u32 i = 0;
	u32 rcode = 0;
	व्योम *p = शून्य;
	dma_addr_t addr;
	uदीर्घ flags = 0;

	स_रखो(&msg, 0, MAX_MESSAGE_SIZE*4);
	// get user msg size in u32s 
	अगर(get_user(size, &user_msg[0]))अणु
		वापस -EFAULT;
	पूर्ण
	size = size>>16;

	user_reply = &user_msg[size];
	अगर(size > MAX_MESSAGE_SIZE)अणु
		वापस -EFAULT;
	पूर्ण
	size *= 4; // Convert to bytes

	/* Copy in the user's I2O command */
	अगर(copy_from_user(msg, user_msg, size)) अणु
		वापस -EFAULT;
	पूर्ण
	get_user(reply_size, &user_reply[0]);
	reply_size = reply_size>>16;
	अगर(reply_size > REPLY_FRAME_SIZE)अणु
		reply_size = REPLY_FRAME_SIZE;
	पूर्ण
	reply_size *= 4;
	reply = kzalloc(REPLY_FRAME_SIZE*4, GFP_KERNEL);
	अगर(reply == शून्य) अणु
		prपूर्णांकk(KERN_WARNING"%s: Could not allocate reply buffer\n",pHba->name);
		वापस -ENOMEM;
	पूर्ण
	sg_offset = (msg[0]>>4)&0xf;
	msg[2] = 0x40000000; // IOCTL context
	msg[3] = adpt_ioctl_to_context(pHba, reply);
	अगर (msg[3] == (u32)-1) अणु
		rcode = -EBUSY;
		जाओ मुक्त;
	पूर्ण

	sg_list = kसुस्मृति(pHba->sg_tablesize, माप(*sg_list), GFP_KERNEL);
	अगर (!sg_list) अणु
		rcode = -ENOMEM;
		जाओ मुक्त;
	पूर्ण
	अगर(sg_offset) अणु
		// TODO add 64 bit API
		काष्ठा sg_simple_element *sg =  (काष्ठा sg_simple_element*) (msg+sg_offset);
		sg_count = (size - sg_offset*4) / माप(काष्ठा sg_simple_element);
		अगर (sg_count > pHba->sg_tablesize)अणु
			prपूर्णांकk(KERN_DEBUG"%s:IOCTL SG List too large (%u)\n", pHba->name,sg_count);
			rcode = -EINVAL;
			जाओ मुक्त;
		पूर्ण

		क्रम(i = 0; i < sg_count; i++) अणु
			पूर्णांक sg_size;

			अगर (!(sg[i].flag_count & 0x10000000 /*I2O_SGL_FLAGS_SIMPLE_ADDRESS_ELEMENT*/)) अणु
				prपूर्णांकk(KERN_DEBUG"%s:Bad SG element %d - not simple (%x)\n",pHba->name,i,  sg[i].flag_count);
				rcode = -EINVAL;
				जाओ cleanup;
			पूर्ण
			sg_size = sg[i].flag_count & 0xffffff;      
			/* Allocate memory क्रम the transfer */
			p = dma_alloc_coherent(&pHba->pDev->dev, sg_size, &addr, GFP_KERNEL);
			अगर(!p) अणु
				prपूर्णांकk(KERN_DEBUG"%s: Could not allocate SG buffer - size = %d buffer number %d of %d\n",
						pHba->name,sg_size,i,sg_count);
				rcode = -ENOMEM;
				जाओ cleanup;
			पूर्ण
			sg_list[sg_index++] = p; // sglist indexed with input frame, not our पूर्णांकernal frame.
			/* Copy in the user's SG buffer अगर necessary */
			अगर(sg[i].flag_count & 0x04000000 /*I2O_SGL_FLAGS_सूची*/) अणु
				// sg_simple_element API is 32 bit
				अगर (copy_from_user(p,(व्योम __user *)(uदीर्घ)sg[i].addr_bus, sg_size)) अणु
					prपूर्णांकk(KERN_DEBUG"%s: Could not copy SG buf %d FROM user\n",pHba->name,i);
					rcode = -EFAULT;
					जाओ cleanup;
				पूर्ण
			पूर्ण
			/* sg_simple_element API is 32 bit, but addr < 4GB */
			sg[i].addr_bus = addr;
		पूर्ण
	पूर्ण

	करो अणु
		/*
		 * Stop any new commands from enterring the
		 * controller जबतक processing the ioctl
		 */
		अगर (pHba->host) अणु
			scsi_block_requests(pHba->host);
			spin_lock_irqsave(pHba->host->host_lock, flags);
		पूर्ण
		rcode = adpt_i2o_post_रुको(pHba, msg, size, FOREVER);
		अगर (rcode != 0)
			prपूर्णांकk("adpt_i2o_passthru: post wait failed %d %p\n",
					rcode, reply);
		अगर (pHba->host) अणु
			spin_unlock_irqrestore(pHba->host->host_lock, flags);
			scsi_unblock_requests(pHba->host);
		पूर्ण
	पूर्ण जबतक (rcode == -ETIMEDOUT);

	अगर(rcode)अणु
		जाओ cleanup;
	पूर्ण

	अगर(sg_offset) अणु
	/* Copy back the Scatter Gather buffers back to user space */
		u32 j;
		// TODO add 64 bit API
		काष्ठा sg_simple_element* sg;
		पूर्णांक sg_size;

		// re-acquire the original message to handle correctly the sg copy operation
		स_रखो(&msg, 0, MAX_MESSAGE_SIZE*4); 
		// get user msg size in u32s 
		अगर(get_user(size, &user_msg[0]))अणु
			rcode = -EFAULT; 
			जाओ cleanup; 
		पूर्ण
		size = size>>16;
		size *= 4;
		अगर (size > MAX_MESSAGE_SIZE) अणु
			rcode = -EINVAL;
			जाओ cleanup;
		पूर्ण
		/* Copy in the user's I2O command */
		अगर (copy_from_user (msg, user_msg, size)) अणु
			rcode = -EFAULT;
			जाओ cleanup;
		पूर्ण
		sg_count = (size - sg_offset*4) / माप(काष्ठा sg_simple_element);

		// TODO add 64 bit API
		sg 	 = (काष्ठा sg_simple_element*)(msg + sg_offset);
		क्रम (j = 0; j < sg_count; j++) अणु
			/* Copy out the SG list to user's buffer अगर necessary */
			अगर(! (sg[j].flag_count & 0x4000000 /*I2O_SGL_FLAGS_सूची*/)) अणु
				sg_size = sg[j].flag_count & 0xffffff; 
				// sg_simple_element API is 32 bit
				अगर (copy_to_user((व्योम __user *)(uदीर्घ)sg[j].addr_bus,sg_list[j], sg_size)) अणु
					prपूर्णांकk(KERN_WARNING"%s: Could not copy %p TO user %x\n",pHba->name, sg_list[j], sg[j].addr_bus);
					rcode = -EFAULT;
					जाओ cleanup;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण 

	/* Copy back the reply to user space */
	अगर (reply_size) अणु
		// we wrote our own values क्रम context - now restore the user supplied ones
		अगर(copy_from_user(reply+2, user_msg+2, माप(u32)*2)) अणु
			prपूर्णांकk(KERN_WARNING"%s: Could not copy message context FROM user\n",pHba->name);
			rcode = -EFAULT;
		पूर्ण
		अगर(copy_to_user(user_reply, reply, reply_size)) अणु
			prपूर्णांकk(KERN_WARNING"%s: Could not copy reply TO user\n",pHba->name);
			rcode = -EFAULT;
		पूर्ण
	पूर्ण


cleanup:
	अगर (rcode != -ETIME && rcode != -EINTR) अणु
		काष्ठा sg_simple_element *sg =
				(काष्ठा sg_simple_element*) (msg +sg_offset);
		जबतक(sg_index) अणु
			अगर(sg_list[--sg_index]) अणु
				dma_मुक्त_coherent(&pHba->pDev->dev,
					sg[sg_index].flag_count & 0xffffff,
					sg_list[sg_index],
					sg[sg_index].addr_bus);
			पूर्ण
		पूर्ण
	पूर्ण

मुक्त:
	kमुक्त(sg_list);
	kमुक्त(reply);
	वापस rcode;
पूर्ण

#अगर defined __ia64__ 
अटल व्योम adpt_ia64_info(sysInfo_S* si)
अणु
	// This is all the info we need क्रम now
	// We will add more info as our new
	// managmenent utility requires it
	si->processorType = PROC_IA64;
पूर्ण
#पूर्ण_अगर

#अगर defined __sparc__ 
अटल व्योम adpt_sparc_info(sysInfo_S* si)
अणु
	// This is all the info we need क्रम now
	// We will add more info as our new
	// managmenent utility requires it
	si->processorType = PROC_ULTRASPARC;
पूर्ण
#पूर्ण_अगर
#अगर defined __alpha__ 
अटल व्योम adpt_alpha_info(sysInfo_S* si)
अणु
	// This is all the info we need क्रम now
	// We will add more info as our new
	// managmenent utility requires it
	si->processorType = PROC_ALPHA;
पूर्ण
#पूर्ण_अगर

#अगर defined __i386__

#समावेश <uapi/यंत्र/vm86.h>

अटल व्योम adpt_i386_info(sysInfo_S* si)
अणु
	// This is all the info we need क्रम now
	// We will add more info as our new
	// managmenent utility requires it
	चयन (boot_cpu_data.x86) अणु
	हाल CPU_386:
		si->processorType = PROC_386;
		अवरोध;
	हाल CPU_486:
		si->processorType = PROC_486;
		अवरोध;
	हाल CPU_586:
		si->processorType = PROC_PENTIUM;
		अवरोध;
	शेष:  // Just in हाल 
		si->processorType = PROC_PENTIUM;
		अवरोध;
	पूर्ण
पूर्ण
#पूर्ण_अगर

/*
 * This routine वापसs inक्रमmation about the प्रणाली.  This करोes not effect
 * any logic and अगर the info is wrong - it करोesn't matter.
 */

/* Get all the info we can not get from kernel services */
अटल पूर्णांक adpt_प्रणाली_info(व्योम __user *buffer)
अणु
	sysInfo_S si;

	स_रखो(&si, 0, माप(si));

	si.osType = OS_LINUX;
	si.osMajorVersion = 0;
	si.osMinorVersion = 0;
	si.osRevision = 0;
	si.busType = SI_PCI_BUS;
	si.processorFamily = DPTI_sig.dsProcessorFamily;

#अगर defined __i386__
	adpt_i386_info(&si);
#या_अगर defined (__ia64__)
	adpt_ia64_info(&si);
#या_अगर defined(__sparc__)
	adpt_sparc_info(&si);
#या_अगर defined (__alpha__)
	adpt_alpha_info(&si);
#अन्यथा
	si.processorType = 0xff ;
#पूर्ण_अगर
	अगर (copy_to_user(buffer, &si, माप(si)))अणु
		prपूर्णांकk(KERN_WARNING"dpti: Could not copy buffer TO user\n");
		वापस -EFAULT;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक adpt_ioctl(काष्ठा inode *inode, काष्ठा file *file, uपूर्णांक cmd, uदीर्घ arg)
अणु
	पूर्णांक minor;
	पूर्णांक error = 0;
	adpt_hba* pHba;
	uदीर्घ flags = 0;
	व्योम __user *argp = (व्योम __user *)arg;

	minor = iminor(inode);
	अगर (minor >= DPTI_MAX_HBA)अणु
		वापस -ENXIO;
	पूर्ण
	mutex_lock(&adpt_configuration_lock);
	क्रम (pHba = hba_chain; pHba; pHba = pHba->next) अणु
		अगर (pHba->unit == minor) अणु
			अवरोध;	/* found adapter */
		पूर्ण
	पूर्ण
	mutex_unlock(&adpt_configuration_lock);
	अगर(pHba == शून्य)अणु
		वापस -ENXIO;
	पूर्ण

	जबतक((अस्थिर u32) pHba->state & DPTI_STATE_RESET )
		schedule_समयout_unपूर्णांकerruptible(2);

	चयन (cmd) अणु
	// TODO: handle 3 हालs
	हाल DPT_SIGNATURE:
		अगर (copy_to_user(argp, &DPTI_sig, माप(DPTI_sig))) अणु
			वापस -EFAULT;
		पूर्ण
		अवरोध;
	हाल I2OUSRCMD:
		वापस adpt_i2o_passthru(pHba, argp);

	हाल DPT_CTRLINFO:अणु
		drvrHBAinfo_S HbaInfo;

#घोषणा FLG_OSD_PCI_VALID 0x0001
#घोषणा FLG_OSD_DMA	  0x0002
#घोषणा FLG_OSD_I2O	  0x0004
		स_रखो(&HbaInfo, 0, माप(HbaInfo));
		HbaInfo.drvrHBAnum = pHba->unit;
		HbaInfo.baseAddr = (uदीर्घ) pHba->base_addr_phys;
		HbaInfo.blinkState = adpt_पढ़ो_blink_led(pHba);
		HbaInfo.pciBusNum =  pHba->pDev->bus->number;
		HbaInfo.pciDeviceNum=PCI_SLOT(pHba->pDev->devfn); 
		HbaInfo.Interrupt = pHba->pDev->irq; 
		HbaInfo.hbaFlags = FLG_OSD_PCI_VALID | FLG_OSD_DMA | FLG_OSD_I2O;
		अगर(copy_to_user(argp, &HbaInfo, माप(HbaInfo)))अणु
			prपूर्णांकk(KERN_WARNING"%s: Could not copy HbaInfo TO user\n",pHba->name);
			वापस -EFAULT;
		पूर्ण
		अवरोध;
		पूर्ण
	हाल DPT_SYSINFO:
		वापस adpt_प्रणाली_info(argp);
	हाल DPT_BLINKLED:अणु
		u32 value;
		value = (u32)adpt_पढ़ो_blink_led(pHba);
		अगर (copy_to_user(argp, &value, माप(value))) अणु
			वापस -EFAULT;
		पूर्ण
		अवरोध;
		पूर्ण
	हाल I2ORESETCMD: अणु
		काष्ठा Scsi_Host *shost = pHba->host;

		अगर (shost)
			spin_lock_irqsave(shost->host_lock, flags);
		adpt_hba_reset(pHba);
		अगर (shost)
			spin_unlock_irqrestore(shost->host_lock, flags);
		अवरोध;
	पूर्ण
	हाल I2ORESCANCMD:
		adpt_rescan(pHba);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस error;
पूर्ण

अटल दीर्घ adpt_unlocked_ioctl(काष्ठा file *file, uपूर्णांक cmd, uदीर्घ arg)
अणु
	काष्ठा inode *inode;
	दीर्घ ret;
 
	inode = file_inode(file);
 
	mutex_lock(&adpt_mutex);
	ret = adpt_ioctl(inode, file, cmd, arg);
	mutex_unlock(&adpt_mutex);

	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_COMPAT
अटल दीर्घ compat_adpt_ioctl(काष्ठा file *file,
				अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा inode *inode;
	दीर्घ ret;
 
	inode = file_inode(file);
 
	mutex_lock(&adpt_mutex);
 
	चयन(cmd) अणु
		हाल DPT_SIGNATURE:
		हाल I2OUSRCMD:
		हाल DPT_CTRLINFO:
		हाल DPT_SYSINFO:
		हाल DPT_BLINKLED:
		हाल I2ORESETCMD:
		हाल I2ORESCANCMD:
		हाल (DPT_TARGET_BUSY & 0xFFFF):
		हाल DPT_TARGET_BUSY:
			ret = adpt_ioctl(inode, file, cmd, arg);
			अवरोध;
		शेष:
			ret =  -ENOIOCTLCMD;
	पूर्ण
 
	mutex_unlock(&adpt_mutex);
 
	वापस ret;
पूर्ण
#पूर्ण_अगर

अटल irqवापस_t adpt_isr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा scsi_cmnd* cmd;
	adpt_hba* pHba = dev_id;
	u32 m;
	व्योम __iomem *reply;
	u32 status=0;
	u32 context;
	uदीर्घ flags = 0;
	पूर्णांक handled = 0;

	अगर (pHba == शून्य)अणु
		prपूर्णांकk(KERN_WARNING"adpt_isr: NULL dev_id\n");
		वापस IRQ_NONE;
	पूर्ण
	अगर(pHba->host)
		spin_lock_irqsave(pHba->host->host_lock, flags);

	जबतक( पढ़ोl(pHba->irq_mask) & I2O_INTERRUPT_PENDING_B) अणु
		m = पढ़ोl(pHba->reply_port);
		अगर(m == EMPTY_QUEUE)अणु
			// Try twice then give up
			rmb();
			m = पढ़ोl(pHba->reply_port);
			अगर(m == EMPTY_QUEUE)अणु 
				// This really should not happen
				prपूर्णांकk(KERN_ERR"dpti: Could not get reply frame\n");
				जाओ out;
			पूर्ण
		पूर्ण
		अगर (pHba->reply_pool_pa <= m &&
		    m < pHba->reply_pool_pa +
			(pHba->reply_fअगरo_size * REPLY_FRAME_SIZE * 4)) अणु
			reply = (u8 *)pHba->reply_pool +
						(m - pHba->reply_pool_pa);
		पूर्ण अन्यथा अणु
			/* Ick, we should *never* be here */
			prपूर्णांकk(KERN_ERR "dpti: reply frame not from pool\n");
			reply = (u8 *)bus_to_virt(m);
		पूर्ण

		अगर (पढ़ोl(reply) & MSG_FAIL) अणु
			u32 old_m = पढ़ोl(reply+28); 
			व्योम __iomem *msg;
			u32 old_context;
			PDEBUG("%s: Failed message\n",pHba->name);
			अगर(old_m >= 0x100000)अणु
				prपूर्णांकk(KERN_ERR"%s: Bad preserved MFA (%x)- dropping frame\n",pHba->name,old_m);
				ग_लिखोl(m,pHba->reply_port);
				जारी;
			पूर्ण
			// Transaction context is 0 in failed reply frame
			msg = pHba->msg_addr_virt + old_m;
			old_context = पढ़ोl(msg+12);
			ग_लिखोl(old_context, reply+12);
			adpt_send_nop(pHba, old_m);
		पूर्ण 
		context = पढ़ोl(reply+8);
		अगर(context & 0x40000000)अणु // IOCTL
			व्योम *p = adpt_ioctl_from_context(pHba, पढ़ोl(reply+12));
			अगर( p != शून्य) अणु
				स_नकल_fromio(p, reply, REPLY_FRAME_SIZE * 4);
			पूर्ण
			// All IOCTLs will also be post रुको
		पूर्ण
		अगर(context & 0x80000000)अणु // Post रुको message
			status = पढ़ोl(reply+16);
			अगर(status  >> 24)अणु
				status &=  0xffff; /* Get detail status */
			पूर्ण अन्यथा अणु
				status = I2O_POST_WAIT_OK;
			पूर्ण
			अगर(!(context & 0x40000000)) अणु
				/*
				 * The request tag is one less than the command tag
				 * as the firmware might treat a 0 tag as invalid
				 */
				cmd = scsi_host_find_tag(pHba->host,
							 पढ़ोl(reply + 12) - 1);
				अगर(cmd != शून्य) अणु
					prपूर्णांकk(KERN_WARNING"%s: Apparent SCSI cmd in Post Wait Context - cmd=%p context=%x\n", pHba->name, cmd, context);
				पूर्ण
			पूर्ण
			adpt_i2o_post_रुको_complete(context, status);
		पूर्ण अन्यथा अणु // SCSI message
			/*
			 * The request tag is one less than the command tag
			 * as the firmware might treat a 0 tag as invalid
			 */
			cmd = scsi_host_find_tag(pHba->host,
						 पढ़ोl(reply + 12) - 1);
			अगर(cmd != शून्य)अणु
				scsi_dma_unmap(cmd);
				adpt_i2o_scsi_complete(reply, cmd);
			पूर्ण
		पूर्ण
		ग_लिखोl(m, pHba->reply_port);
		wmb();
		rmb();
	पूर्ण
	handled = 1;
out:	अगर(pHba->host)
		spin_unlock_irqrestore(pHba->host->host_lock, flags);
	वापस IRQ_RETVAL(handled);
पूर्ण

अटल s32 adpt_scsi_to_i2o(adpt_hba* pHba, काष्ठा scsi_cmnd* cmd, काष्ठा adpt_device* d)
अणु
	पूर्णांक i;
	u32 msg[MAX_MESSAGE_SIZE];
	u32* mptr;
	u32* lptr;
	u32 *lenptr;
	पूर्णांक direction;
	पूर्णांक scsidir;
	पूर्णांक nseg;
	u32 len;
	u32 reqlen;
	s32 rcode;
	dma_addr_t addr;

	स_रखो(msg, 0 , माप(msg));
	len = scsi_bufflen(cmd);
	direction = 0x00000000;	
	
	scsidir = 0x00000000;			// DATA NO XFER
	अगर(len) अणु
		/*
		 * Set SCBFlags to indicate अगर data is being transferred
		 * in or out, or no data transfer
		 * Note:  Do not have to verअगरy index is less than 0 since
		 * cmd->cmnd[0] is an अचिन्हित अक्षर
		 */
		चयन(cmd->sc_data_direction)अणु
		हाल DMA_FROM_DEVICE:
			scsidir  =0x40000000;	// DATA IN  (iop<--dev)
			अवरोध;
		हाल DMA_TO_DEVICE:
			direction=0x04000000;	// SGL OUT
			scsidir  =0x80000000;	// DATA OUT (iop-->dev)
			अवरोध;
		हाल DMA_NONE:
			अवरोध;
		हाल DMA_BIसूचीECTIONAL:
			scsidir  =0x40000000;	// DATA IN  (iop<--dev)
			// Assume In - and जारी;
			अवरोध;
		शेष:
			prपूर्णांकk(KERN_WARNING"%s: scsi opcode 0x%x not supported.\n",
			     pHba->name, cmd->cmnd[0]);
			cmd->result = (DID_ERROR <<16);
			cmd->scsi_करोne(cmd);
			वापस 	0;
		पूर्ण
	पूर्ण
	// msg[0] is set later
	// I2O_CMD_SCSI_EXEC
	msg[1] = ((0xff<<24)|(HOST_TID<<12)|d->tid);
	msg[2] = 0;
	/* Add 1 to aव्योम firmware treating it as invalid command */
	msg[3] = cmd->request->tag + 1;
	// Our cards use the transaction context as the tag क्रम queueing
	// Adaptec/DPT Private stuff 
	msg[4] = I2O_CMD_SCSI_EXEC|(DPT_ORGANIZATION_ID<<16);
	msg[5] = d->tid;
	/* Direction, disconnect ok | sense data | simple queue , CDBLen */
	// I2O_SCB_FLAG_ENABLE_DISCONNECT | 
	// I2O_SCB_FLAG_SIMPLE_QUEUE_TAG | 
	// I2O_SCB_FLAG_SENSE_DATA_IN_MESSAGE;
	msg[6] = scsidir|0x20a00000|cmd->cmd_len;

	mptr=msg+7;

	// Write SCSI command पूर्णांकo the message - always 16 byte block 
	स_रखो(mptr, 0,  16);
	स_नकल(mptr, cmd->cmnd, cmd->cmd_len);
	mptr+=4;
	lenptr=mptr++;		/* Remember me - fill in when we know */
	अगर (dpt_dma64(pHba)) अणु
		reqlen = 16;		// SINGLE SGE
		*mptr++ = (0x7C<<24)+(2<<16)+0x02; /* Enable 64 bit */
		*mptr++ = 1 << PAGE_SHIFT;
	पूर्ण अन्यथा अणु
		reqlen = 14;		// SINGLE SGE
	पूर्ण
	/* Now fill in the SGList and command */

	nseg = scsi_dma_map(cmd);
	BUG_ON(nseg < 0);
	अगर (nseg) अणु
		काष्ठा scatterlist *sg;

		len = 0;
		scsi_क्रम_each_sg(cmd, sg, nseg, i) अणु
			lptr = mptr;
			*mptr++ = direction|0x10000000|sg_dma_len(sg);
			len+=sg_dma_len(sg);
			addr = sg_dma_address(sg);
			*mptr++ = dma_low(addr);
			अगर (dpt_dma64(pHba))
				*mptr++ = dma_high(addr);
			/* Make this an end of list */
			अगर (i == nseg - 1)
				*lptr = direction|0xD0000000|sg_dma_len(sg);
		पूर्ण
		reqlen = mptr - msg;
		*lenptr = len;
		
		अगर(cmd->underflow && len != cmd->underflow)अणु
			prपूर्णांकk(KERN_WARNING"Cmd len %08X Cmd underflow %08X\n",
				len, cmd->underflow);
		पूर्ण
	पूर्ण अन्यथा अणु
		*lenptr = len = 0;
		reqlen = 12;
	पूर्ण
	
	/* Stick the headers on */
	msg[0] = reqlen<<16 | ((reqlen > 12) ? SGL_OFFSET_12 : SGL_OFFSET_0);
	
	// Send it on it's way
	rcode = adpt_i2o_post_this(pHba, msg, reqlen<<2);
	अगर (rcode == 0) अणु
		वापस 0;
	पूर्ण
	वापस rcode;
पूर्ण


अटल s32 adpt_scsi_host_alloc(adpt_hba* pHba, काष्ठा scsi_host_ढाँचा *sht)
अणु
	काष्ठा Scsi_Host *host;

	host = scsi_host_alloc(sht, माप(adpt_hba*));
	अगर (host == शून्य) अणु
		prपूर्णांकk("%s: scsi_host_alloc returned NULL\n", pHba->name);
		वापस -1;
	पूर्ण
	host->hostdata[0] = (अचिन्हित दीर्घ)pHba;
	pHba->host = host;

	host->irq = pHba->pDev->irq;
	/* no IO ports, so करोn't have to set host->io_port and
	 * host->n_io_port
	 */
	host->io_port = 0;
	host->n_io_port = 0;
				/* see comments in scsi_host.h */
	host->max_id = 16;
	host->max_lun = 256;
	host->max_channel = pHba->top_scsi_channel + 1;
	host->cmd_per_lun = 1;
	host->unique_id = (u32)sys_tbl_pa + pHba->unit;
	host->sg_tablesize = pHba->sg_tablesize;
	host->can_queue = pHba->post_fअगरo_size;

	वापस 0;
पूर्ण


अटल व्योम adpt_i2o_scsi_complete(व्योम __iomem *reply, काष्ठा scsi_cmnd *cmd)
अणु
	adpt_hba* pHba;
	u32 hba_status;
	u32 dev_status;
	u32 reply_flags = पढ़ोl(reply) & 0xff00; // Leave it shअगरted up 8 bits 
	// I know this would look cleaner अगर I just पढ़ो bytes
	// but the model I have been using क्रम all the rest of the
	// io is in 4 byte words - so I keep that model
	u16 detailed_status = पढ़ोl(reply+16) &0xffff;
	dev_status = (detailed_status & 0xff);
	hba_status = detailed_status >> 8;

	// calculate resid क्रम sg 
	scsi_set_resid(cmd, scsi_bufflen(cmd) - पढ़ोl(reply+20));

	pHba = (adpt_hba*) cmd->device->host->hostdata[0];

	cmd->sense_buffer[0] = '\0';  // initialize sense valid flag to false

	अगर(!(reply_flags & MSG_FAIL)) अणु
		चयन(detailed_status & I2O_SCSI_DSC_MASK) अणु
		हाल I2O_SCSI_DSC_SUCCESS:
			cmd->result = (DID_OK << 16);
			// handle underflow
			अगर (पढ़ोl(reply+20) < cmd->underflow) अणु
				cmd->result = (DID_ERROR <<16);
				prपूर्णांकk(KERN_WARNING"%s: SCSI CMD underflow\n",pHba->name);
			पूर्ण
			अवरोध;
		हाल I2O_SCSI_DSC_REQUEST_ABORTED:
			cmd->result = (DID_ABORT << 16);
			अवरोध;
		हाल I2O_SCSI_DSC_PATH_INVALID:
		हाल I2O_SCSI_DSC_DEVICE_NOT_PRESENT:
		हाल I2O_SCSI_DSC_SELECTION_TIMEOUT:
		हाल I2O_SCSI_DSC_COMMAND_TIMEOUT:
		हाल I2O_SCSI_DSC_NO_ADAPTER:
		हाल I2O_SCSI_DSC_RESOURCE_UNAVAILABLE:
			prपूर्णांकk(KERN_WARNING"%s: SCSI Timeout-Device (%d,%d,%llu) hba status=0x%x, dev status=0x%x, cmd=0x%x\n",
				pHba->name, (u32)cmd->device->channel, (u32)cmd->device->id, cmd->device->lun, hba_status, dev_status, cmd->cmnd[0]);
			cmd->result = (DID_TIME_OUT << 16);
			अवरोध;
		हाल I2O_SCSI_DSC_ADAPTER_BUSY:
		हाल I2O_SCSI_DSC_BUS_BUSY:
			cmd->result = (DID_BUS_BUSY << 16);
			अवरोध;
		हाल I2O_SCSI_DSC_SCSI_BUS_RESET:
		हाल I2O_SCSI_DSC_BDR_MESSAGE_SENT:
			cmd->result = (DID_RESET << 16);
			अवरोध;
		हाल I2O_SCSI_DSC_PARITY_ERROR_FAILURE:
			prपूर्णांकk(KERN_WARNING"%s: SCSI CMD parity error\n",pHba->name);
			cmd->result = (DID_PARITY << 16);
			अवरोध;
		हाल I2O_SCSI_DSC_UNABLE_TO_ABORT:
		हाल I2O_SCSI_DSC_COMPLETE_WITH_ERROR:
		हाल I2O_SCSI_DSC_UNABLE_TO_TERMINATE:
		हाल I2O_SCSI_DSC_MR_MESSAGE_RECEIVED:
		हाल I2O_SCSI_DSC_AUTOSENSE_FAILED:
		हाल I2O_SCSI_DSC_DATA_OVERRUN:
		हाल I2O_SCSI_DSC_UNEXPECTED_BUS_FREE:
		हाल I2O_SCSI_DSC_SEQUENCE_FAILURE:
		हाल I2O_SCSI_DSC_REQUEST_LENGTH_ERROR:
		हाल I2O_SCSI_DSC_PROVIDE_FAILURE:
		हाल I2O_SCSI_DSC_REQUEST_TERMINATED:
		हाल I2O_SCSI_DSC_IDE_MESSAGE_SENT:
		हाल I2O_SCSI_DSC_UNACKNOWLEDGED_EVENT:
		हाल I2O_SCSI_DSC_MESSAGE_RECEIVED:
		हाल I2O_SCSI_DSC_INVALID_CDB:
		हाल I2O_SCSI_DSC_LUN_INVALID:
		हाल I2O_SCSI_DSC_SCSI_TID_INVALID:
		हाल I2O_SCSI_DSC_FUNCTION_UNAVAILABLE:
		हाल I2O_SCSI_DSC_NO_NEXUS:
		हाल I2O_SCSI_DSC_CDB_RECEIVED:
		हाल I2O_SCSI_DSC_LUN_ALREADY_ENABLED:
		हाल I2O_SCSI_DSC_QUEUE_FROZEN:
		हाल I2O_SCSI_DSC_REQUEST_INVALID:
		शेष:
			prपूर्णांकk(KERN_WARNING"%s: SCSI error %0x-Device(%d,%d,%llu) hba_status=0x%x, dev_status=0x%x, cmd=0x%x\n",
				pHba->name, detailed_status & I2O_SCSI_DSC_MASK, (u32)cmd->device->channel, (u32)cmd->device->id, cmd->device->lun,
			       hba_status, dev_status, cmd->cmnd[0]);
			cmd->result = (DID_ERROR << 16);
			अवरोध;
		पूर्ण

		// copy over the request sense data अगर it was a check
		// condition status
		अगर (dev_status == SAM_STAT_CHECK_CONDITION) अणु
			u32 len = min(SCSI_SENSE_BUFFERSIZE, 40);
			// Copy over the sense data
			स_नकल_fromio(cmd->sense_buffer, (reply+28) , len);
			अगर(cmd->sense_buffer[0] == 0x70 /* class 7 */ && 
			   cmd->sense_buffer[2] == DATA_PROTECT )अणु
				/* This is to handle an array failed */
				cmd->result = (DID_TIME_OUT << 16);
				prपूर्णांकk(KERN_WARNING"%s: SCSI Data Protect-Device (%d,%d,%llu) hba_status=0x%x, dev_status=0x%x, cmd=0x%x\n",
					pHba->name, (u32)cmd->device->channel, (u32)cmd->device->id, cmd->device->lun,
					hba_status, dev_status, cmd->cmnd[0]);

			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		/* In this condtion we could not talk to the tid
		 * the card rejected it.  We should संकेत a retry
		 * क्रम a limitted number of retries.
		 */
		cmd->result = (DID_TIME_OUT << 16);
		prपूर्णांकk(KERN_WARNING"%s: I2O MSG_FAIL - Device (%d,%d,%llu) tid=%d, cmd=0x%x\n",
			pHba->name, (u32)cmd->device->channel, (u32)cmd->device->id, cmd->device->lun,
			((काष्ठा adpt_device*)(cmd->device->hostdata))->tid, cmd->cmnd[0]);
	पूर्ण

	cmd->result |= (dev_status);

	अगर(cmd->scsi_करोne != शून्य)अणु
		cmd->scsi_करोne(cmd);
	पूर्ण 
पूर्ण


अटल s32 adpt_rescan(adpt_hba* pHba)
अणु
	s32 rcode;
	uदीर्घ flags = 0;

	अगर(pHba->host)
		spin_lock_irqsave(pHba->host->host_lock, flags);
	अगर ((rcode=adpt_i2o_lct_get(pHba)) < 0)
		जाओ out;
	अगर ((rcode=adpt_i2o_reparse_lct(pHba)) < 0)
		जाओ out;
	rcode = 0;
out:	अगर(pHba->host)
		spin_unlock_irqrestore(pHba->host->host_lock, flags);
	वापस rcode;
पूर्ण


अटल s32 adpt_i2o_reparse_lct(adpt_hba* pHba)
अणु
	पूर्णांक i;
	पूर्णांक max;
	पूर्णांक tid;
	काष्ठा i2o_device *d;
	i2o_lct *lct = pHba->lct;
	u8 bus_no = 0;
	s16 scsi_id;
	u64 scsi_lun;
	u32 buf[10]; // at least 8 u32's
	काष्ठा adpt_device* pDev = शून्य;
	काष्ठा i2o_device* pI2o_dev = शून्य;
	
	अगर (lct == शून्य) अणु
		prपूर्णांकk(KERN_ERR "%s: LCT is empty???\n",pHba->name);
		वापस -1;
	पूर्ण
	
	max = lct->table_size;	
	max -= 3;
	max /= 9;

	// Mark each drive as unscanned
	क्रम (d = pHba->devices; d; d = d->next) अणु
		pDev =(काष्ठा adpt_device*) d->owner;
		अगर(!pDev)अणु
			जारी;
		पूर्ण
		pDev->state |= DPTI_DEV_UNSCANNED;
	पूर्ण

	prपूर्णांकk(KERN_INFO "%s: LCT has %d entries.\n", pHba->name,max);
	
	क्रम(i=0;i<max;i++) अणु
		अगर( lct->lct_entry[i].user_tid != 0xfff)अणु
			जारी;
		पूर्ण

		अगर( lct->lct_entry[i].class_id == I2O_CLASS_RANDOM_BLOCK_STORAGE ||
		    lct->lct_entry[i].class_id == I2O_CLASS_SCSI_PERIPHERAL ||
		    lct->lct_entry[i].class_id == I2O_CLASS_FIBRE_CHANNEL_PERIPHERAL )अणु
			tid = lct->lct_entry[i].tid;
			अगर(adpt_i2o_query_scalar(pHba, tid, 0x8000, -1, buf, 32)<0) अणु
				prपूर्णांकk(KERN_ERR"%s: Could not query device\n",pHba->name);
				जारी;
			पूर्ण
			bus_no = buf[0]>>16;
			अगर (bus_no >= MAX_CHANNEL) अणु	/* Something wrong skip it */
				prपूर्णांकk(KERN_WARNING
					"%s: Channel number %d out of range\n",
					pHba->name, bus_no);
				जारी;
			पूर्ण

			scsi_id = buf[1];
			scsi_lun = scsilun_to_पूर्णांक((काष्ठा scsi_lun *)&buf[2]);
			pDev = pHba->channel[bus_no].device[scsi_id];
			/* da lun */
			जबतक(pDev) अणु
				अगर(pDev->scsi_lun == scsi_lun) अणु
					अवरोध;
				पूर्ण
				pDev = pDev->next_lun;
			पूर्ण
			अगर(!pDev ) अणु // Something new add it
				d = kदो_स्मृति(माप(काष्ठा i2o_device),
					    GFP_ATOMIC);
				अगर(d==शून्य)
				अणु
					prपूर्णांकk(KERN_CRIT "Out of memory for I2O device data.\n");
					वापस -ENOMEM;
				पूर्ण
				
				d->controller = pHba;
				d->next = शून्य;

				स_नकल(&d->lct_data, &lct->lct_entry[i], माप(i2o_lct_entry));

				d->flags = 0;
				adpt_i2o_report_hba_unit(pHba, d);
				adpt_i2o_install_device(pHba, d);
	
				pDev = pHba->channel[bus_no].device[scsi_id];	
				अगर( pDev == शून्य)अणु
					pDev =
					  kzalloc(माप(काष्ठा adpt_device),
						  GFP_ATOMIC);
					अगर(pDev == शून्य) अणु
						वापस -ENOMEM;
					पूर्ण
					pHba->channel[bus_no].device[scsi_id] = pDev;
				पूर्ण अन्यथा अणु
					जबतक (pDev->next_lun) अणु
						pDev = pDev->next_lun;
					पूर्ण
					pDev = pDev->next_lun =
					  kzalloc(माप(काष्ठा adpt_device),
						  GFP_ATOMIC);
					अगर(pDev == शून्य) अणु
						वापस -ENOMEM;
					पूर्ण
				पूर्ण
				pDev->tid = d->lct_data.tid;
				pDev->scsi_channel = bus_no;
				pDev->scsi_id = scsi_id;
				pDev->scsi_lun = scsi_lun;
				pDev->pI2o_dev = d;
				d->owner = pDev;
				pDev->type = (buf[0])&0xff;
				pDev->flags = (buf[0]>>8)&0xff;
				// Too late, SCSI प्रणाली has made up it's mind, but what the hey ...
				अगर(scsi_id > pHba->top_scsi_id)अणु
					pHba->top_scsi_id = scsi_id;
				पूर्ण
				अगर(scsi_lun > pHba->top_scsi_lun)अणु
					pHba->top_scsi_lun = scsi_lun;
				पूर्ण
				जारी;
			पूर्ण // end of new i2o device

			// We found an old device - check it
			जबतक(pDev) अणु
				अगर(pDev->scsi_lun == scsi_lun) अणु
					अगर(!scsi_device_online(pDev->pScsi_dev)) अणु
						prपूर्णांकk(KERN_WARNING"%s: Setting device (%d,%d,%llu) back online\n",
								pHba->name,bus_no,scsi_id,scsi_lun);
						अगर (pDev->pScsi_dev) अणु
							scsi_device_set_state(pDev->pScsi_dev, SDEV_RUNNING);
						पूर्ण
					पूर्ण
					d = pDev->pI2o_dev;
					अगर(d->lct_data.tid != tid) अणु // something changed
						pDev->tid = tid;
						स_नकल(&d->lct_data, &lct->lct_entry[i], माप(i2o_lct_entry));
						अगर (pDev->pScsi_dev) अणु
							pDev->pScsi_dev->changed = TRUE;
							pDev->pScsi_dev->removable = TRUE;
						पूर्ण
					पूर्ण
					// Found it - mark it scanned
					pDev->state = DPTI_DEV_ONLINE;
					अवरोध;
				पूर्ण
				pDev = pDev->next_lun;
			पूर्ण
		पूर्ण
	पूर्ण
	क्रम (pI2o_dev = pHba->devices; pI2o_dev; pI2o_dev = pI2o_dev->next) अणु
		pDev =(काष्ठा adpt_device*) pI2o_dev->owner;
		अगर(!pDev)अणु
			जारी;
		पूर्ण
		// Drive offline drives that previously existed but could not be found
		// in the LCT table
		अगर (pDev->state & DPTI_DEV_UNSCANNED)अणु
			pDev->state = DPTI_DEV_OFFLINE;
			prपूर्णांकk(KERN_WARNING"%s: Device (%d,%d,%llu) offline\n",pHba->name,pDev->scsi_channel,pDev->scsi_id,pDev->scsi_lun);
			अगर (pDev->pScsi_dev) अणु
				scsi_device_set_state(pDev->pScsi_dev, SDEV_OFFLINE);
			पूर्ण
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/*============================================================================
 *  Routines from i2o subप्रणाली
 *============================================================================
 */



/*
 *	Bring an I2O controller पूर्णांकo HOLD state. See the spec.
 */
अटल पूर्णांक adpt_i2o_activate_hba(adpt_hba* pHba)
अणु
	पूर्णांक rcode;

	अगर(pHba->initialized ) अणु
		अगर (adpt_i2o_status_get(pHba) < 0) अणु
			अगर((rcode = adpt_i2o_reset_hba(pHba)) != 0)अणु
				prपूर्णांकk(KERN_WARNING"%s: Could NOT reset.\n", pHba->name);
				वापस rcode;
			पूर्ण
			अगर (adpt_i2o_status_get(pHba) < 0) अणु
				prपूर्णांकk(KERN_INFO "HBA not responding.\n");
				वापस -1;
			पूर्ण
		पूर्ण

		अगर(pHba->status_block->iop_state == ADAPTER_STATE_FAULTED) अणु
			prपूर्णांकk(KERN_CRIT "%s: hardware fault\n", pHba->name);
			वापस -1;
		पूर्ण

		अगर (pHba->status_block->iop_state == ADAPTER_STATE_READY ||
		    pHba->status_block->iop_state == ADAPTER_STATE_OPERATIONAL ||
		    pHba->status_block->iop_state == ADAPTER_STATE_HOLD ||
		    pHba->status_block->iop_state == ADAPTER_STATE_FAILED) अणु
			adpt_i2o_reset_hba(pHba);			
			अगर (adpt_i2o_status_get(pHba) < 0 || pHba->status_block->iop_state != ADAPTER_STATE_RESET) अणु
				prपूर्णांकk(KERN_ERR "%s: Failed to initialize.\n", pHba->name);
				वापस -1;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर((rcode = adpt_i2o_reset_hba(pHba)) != 0)अणु
			prपूर्णांकk(KERN_WARNING"%s: Could NOT reset.\n", pHba->name);
			वापस rcode;
		पूर्ण

	पूर्ण

	अगर (adpt_i2o_init_outbound_q(pHba) < 0) अणु
		वापस -1;
	पूर्ण

	/* In HOLD state */
	
	अगर (adpt_i2o_hrt_get(pHba) < 0) अणु
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

/*
 *	Bring a controller online पूर्णांकo OPERATIONAL state. 
 */
 
अटल पूर्णांक adpt_i2o_online_hba(adpt_hba* pHba)
अणु
	अगर (adpt_i2o_systab_send(pHba) < 0)
		वापस -1;
	/* In READY state */

	अगर (adpt_i2o_enable_hba(pHba) < 0)
		वापस -1;

	/* In OPERATIONAL state  */
	वापस 0;
पूर्ण

अटल s32 adpt_send_nop(adpt_hba*pHba,u32 m)
अणु
	u32 __iomem *msg;
	uदीर्घ समयout = jअगरfies + 5*HZ;

	जबतक(m == EMPTY_QUEUE)अणु
		rmb();
		m = पढ़ोl(pHba->post_port);
		अगर(m != EMPTY_QUEUE)अणु
			अवरोध;
		पूर्ण
		अगर(समय_after(jअगरfies,समयout))अणु
			prपूर्णांकk(KERN_ERR "%s: Timeout waiting for message frame!\n",pHba->name);
			वापस 2;
		पूर्ण
		schedule_समयout_unपूर्णांकerruptible(1);
	पूर्ण
	msg = (u32 __iomem *)(pHba->msg_addr_virt + m);
	ग_लिखोl( THREE_WORD_MSG_SIZE | SGL_OFFSET_0,&msg[0]);
	ग_लिखोl( I2O_CMD_UTIL_NOP << 24 | HOST_TID << 12 | 0,&msg[1]);
	ग_लिखोl( 0,&msg[2]);
	wmb();

	ग_लिखोl(m, pHba->post_port);
	wmb();
	वापस 0;
पूर्ण

अटल s32 adpt_i2o_init_outbound_q(adpt_hba* pHba)
अणु
	u8 *status;
	dma_addr_t addr;
	u32 __iomem *msg = शून्य;
	पूर्णांक i;
	uदीर्घ समयout = jअगरfies + TMOUT_INITOUTBOUND*HZ;
	u32 m;

	करो अणु
		rmb();
		m = पढ़ोl(pHba->post_port);
		अगर (m != EMPTY_QUEUE) अणु
			अवरोध;
		पूर्ण

		अगर(समय_after(jअगरfies,समयout))अणु
			prपूर्णांकk(KERN_WARNING"%s: Timeout waiting for message frame\n",pHba->name);
			वापस -ETIMEDOUT;
		पूर्ण
		schedule_समयout_unपूर्णांकerruptible(1);
	पूर्ण जबतक(m == EMPTY_QUEUE);

	msg=(u32 __iomem *)(pHba->msg_addr_virt+m);

	status = dma_alloc_coherent(&pHba->pDev->dev, 4, &addr, GFP_KERNEL);
	अगर (!status) अणु
		adpt_send_nop(pHba, m);
		prपूर्णांकk(KERN_WARNING"%s: IOP reset failed - no free memory.\n",
			pHba->name);
		वापस -ENOMEM;
	पूर्ण

	ग_लिखोl(EIGHT_WORD_MSG_SIZE| SGL_OFFSET_6, &msg[0]);
	ग_लिखोl(I2O_CMD_OUTBOUND_INIT<<24 | HOST_TID<<12 | ADAPTER_TID, &msg[1]);
	ग_लिखोl(0, &msg[2]);
	ग_लिखोl(0x0106, &msg[3]);	/* Transaction context */
	ग_लिखोl(4096, &msg[4]);		/* Host page frame size */
	ग_लिखोl((REPLY_FRAME_SIZE)<<16|0x80, &msg[5]);	/* Outbound msg frame size and Initcode */
	ग_लिखोl(0xD0000004, &msg[6]);		/* Simple SG LE, EOB */
	ग_लिखोl((u32)addr, &msg[7]);

	ग_लिखोl(m, pHba->post_port);
	wmb();

	// Wait क्रम the reply status to come back
	करो अणु
		अगर (*status) अणु
			अगर (*status != 0x01 /*I2O_EXEC_OUTBOUND_INIT_IN_PROGRESS*/) अणु
				अवरोध;
			पूर्ण
		पूर्ण
		rmb();
		अगर(समय_after(jअगरfies,समयout))अणु
			prपूर्णांकk(KERN_WARNING"%s: Timeout Initializing\n",pHba->name);
			/* We lose 4 bytes of "status" here, but we
			   cannot मुक्त these because controller may
			   awake and corrupt those bytes at any समय */
			/* dma_मुक्त_coherent(&pHba->pDev->dev, 4, status, addr); */
			वापस -ETIMEDOUT;
		पूर्ण
		schedule_समयout_unपूर्णांकerruptible(1);
	पूर्ण जबतक (1);

	// If the command was successful, fill the fअगरo with our reply
	// message packets
	अगर(*status != 0x04 /*I2O_EXEC_OUTBOUND_INIT_COMPLETE*/) अणु
		dma_मुक्त_coherent(&pHba->pDev->dev, 4, status, addr);
		वापस -2;
	पूर्ण
	dma_मुक्त_coherent(&pHba->pDev->dev, 4, status, addr);

	अगर(pHba->reply_pool != शून्य) अणु
		dma_मुक्त_coherent(&pHba->pDev->dev,
			pHba->reply_fअगरo_size * REPLY_FRAME_SIZE * 4,
			pHba->reply_pool, pHba->reply_pool_pa);
	पूर्ण

	pHba->reply_pool = dma_alloc_coherent(&pHba->pDev->dev,
				pHba->reply_fअगरo_size * REPLY_FRAME_SIZE * 4,
				&pHba->reply_pool_pa, GFP_KERNEL);
	अगर (!pHba->reply_pool) अणु
		prपूर्णांकk(KERN_ERR "%s: Could not allocate reply pool\n", pHba->name);
		वापस -ENOMEM;
	पूर्ण

	क्रम(i = 0; i < pHba->reply_fअगरo_size; i++) अणु
		ग_लिखोl(pHba->reply_pool_pa + (i * REPLY_FRAME_SIZE * 4),
			pHba->reply_port);
		wmb();
	पूर्ण
	adpt_i2o_status_get(pHba);
	वापस 0;
पूर्ण


/*
 * I2O System Table.  Contains inक्रमmation about
 * all the IOPs in the प्रणाली.  Used to inक्रमm IOPs
 * about each other's existence.
 *
 * sys_tbl_ver is the CurrentChangeIndicator that is
 * used by IOPs to track changes.
 */



अटल s32 adpt_i2o_status_get(adpt_hba* pHba)
अणु
	uदीर्घ समयout;
	u32 m;
	u32 __iomem *msg;
	u8 *status_block=शून्य;

	अगर(pHba->status_block == शून्य) अणु
		pHba->status_block = dma_alloc_coherent(&pHba->pDev->dev,
					माप(i2o_status_block),
					&pHba->status_block_pa, GFP_KERNEL);
		अगर(pHba->status_block == शून्य) अणु
			prपूर्णांकk(KERN_ERR
			"dpti%d: Get Status Block failed; Out of memory. \n", 
			pHba->unit);
			वापस -ENOMEM;
		पूर्ण
	पूर्ण
	स_रखो(pHba->status_block, 0, माप(i2o_status_block));
	status_block = (u8*)(pHba->status_block);
	समयout = jअगरfies+TMOUT_GETSTATUS*HZ;
	करो अणु
		rmb();
		m = पढ़ोl(pHba->post_port);
		अगर (m != EMPTY_QUEUE) अणु
			अवरोध;
		पूर्ण
		अगर(समय_after(jअगरfies,समयout))अणु
			prपूर्णांकk(KERN_ERR "%s: Timeout waiting for message !\n",
					pHba->name);
			वापस -ETIMEDOUT;
		पूर्ण
		schedule_समयout_unपूर्णांकerruptible(1);
	पूर्ण जबतक(m==EMPTY_QUEUE);

	
	msg=(u32 __iomem *)(pHba->msg_addr_virt+m);

	ग_लिखोl(NINE_WORD_MSG_SIZE|SGL_OFFSET_0, &msg[0]);
	ग_लिखोl(I2O_CMD_STATUS_GET<<24|HOST_TID<<12|ADAPTER_TID, &msg[1]);
	ग_लिखोl(1, &msg[2]);
	ग_लिखोl(0, &msg[3]);
	ग_लिखोl(0, &msg[4]);
	ग_लिखोl(0, &msg[5]);
	ग_लिखोl( dma_low(pHba->status_block_pa), &msg[6]);
	ग_लिखोl( dma_high(pHba->status_block_pa), &msg[7]);
	ग_लिखोl(माप(i2o_status_block), &msg[8]); // 88 bytes

	//post message
	ग_लिखोl(m, pHba->post_port);
	wmb();

	जबतक(status_block[87]!=0xff)अणु
		अगर(समय_after(jअगरfies,समयout))अणु
			prपूर्णांकk(KERN_ERR"dpti%d: Get status timeout.\n",
				pHba->unit);
			वापस -ETIMEDOUT;
		पूर्ण
		rmb();
		schedule_समयout_unपूर्णांकerruptible(1);
	पूर्ण

	// Set up our number of outbound and inbound messages
	pHba->post_fअगरo_size = pHba->status_block->max_inbound_frames;
	अगर (pHba->post_fअगरo_size > MAX_TO_IOP_MESSAGES) अणु
		pHba->post_fअगरo_size = MAX_TO_IOP_MESSAGES;
	पूर्ण

	pHba->reply_fअगरo_size = pHba->status_block->max_outbound_frames;
	अगर (pHba->reply_fअगरo_size > MAX_FROM_IOP_MESSAGES) अणु
		pHba->reply_fअगरo_size = MAX_FROM_IOP_MESSAGES;
	पूर्ण

	// Calculate the Scatter Gather list size
	अगर (dpt_dma64(pHba)) अणु
		pHba->sg_tablesize
		  = ((pHba->status_block->inbound_frame_size * 4
		  - 14 * माप(u32))
		  / (माप(काष्ठा sg_simple_element) + माप(u32)));
	पूर्ण अन्यथा अणु
		pHba->sg_tablesize
		  = ((pHba->status_block->inbound_frame_size * 4
		  - 12 * माप(u32))
		  / माप(काष्ठा sg_simple_element));
	पूर्ण
	अगर (pHba->sg_tablesize > SG_LIST_ELEMENTS) अणु
		pHba->sg_tablesize = SG_LIST_ELEMENTS;
	पूर्ण


#अगर_घोषित DEBUG
	prपूर्णांकk("dpti%d: State = ",pHba->unit);
	चयन(pHba->status_block->iop_state) अणु
		हाल 0x01:
			prपूर्णांकk("INIT\n");
			अवरोध;
		हाल 0x02:
			prपूर्णांकk("RESET\n");
			अवरोध;
		हाल 0x04:
			prपूर्णांकk("HOLD\n");
			अवरोध;
		हाल 0x05:
			prपूर्णांकk("READY\n");
			अवरोध;
		हाल 0x08:
			prपूर्णांकk("OPERATIONAL\n");
			अवरोध;
		हाल 0x10:
			prपूर्णांकk("FAILED\n");
			अवरोध;
		हाल 0x11:
			prपूर्णांकk("FAULTED\n");
			अवरोध;
		शेष:
			prपूर्णांकk("%x (unknown!!)\n",pHba->status_block->iop_state);
	पूर्ण
#पूर्ण_अगर
	वापस 0;
पूर्ण

/*
 * Get the IOP's Logical Configuration Table
 */
अटल पूर्णांक adpt_i2o_lct_get(adpt_hba* pHba)
अणु
	u32 msg[8];
	पूर्णांक ret;
	u32 buf[16];

	अगर ((pHba->lct_size == 0) || (pHba->lct == शून्य))अणु
		pHba->lct_size = pHba->status_block->expected_lct_size;
	पूर्ण
	करो अणु
		अगर (pHba->lct == शून्य) अणु
			pHba->lct = dma_alloc_coherent(&pHba->pDev->dev,
					pHba->lct_size, &pHba->lct_pa,
					GFP_ATOMIC);
			अगर(pHba->lct == शून्य) अणु
				prपूर्णांकk(KERN_CRIT "%s: Lct Get failed. Out of memory.\n",
					pHba->name);
				वापस -ENOMEM;
			पूर्ण
		पूर्ण
		स_रखो(pHba->lct, 0, pHba->lct_size);

		msg[0] = EIGHT_WORD_MSG_SIZE|SGL_OFFSET_6;
		msg[1] = I2O_CMD_LCT_NOTIFY<<24 | HOST_TID<<12 | ADAPTER_TID;
		msg[2] = 0;
		msg[3] = 0;
		msg[4] = 0xFFFFFFFF;	/* All devices */
		msg[5] = 0x00000000;	/* Report now */
		msg[6] = 0xD0000000|pHba->lct_size;
		msg[7] = (u32)pHba->lct_pa;

		अगर ((ret=adpt_i2o_post_रुको(pHba, msg, माप(msg), 360))) अणु
			prपूर्णांकk(KERN_ERR "%s: LCT Get failed (status=%#10x.\n", 
				pHba->name, ret);	
			prपूर्णांकk(KERN_ERR"Adaptec: Error Reading Hardware.\n");
			वापस ret;
		पूर्ण

		अगर ((pHba->lct->table_size << 2) > pHba->lct_size) अणु
			pHba->lct_size = pHba->lct->table_size << 2;
			dma_मुक्त_coherent(&pHba->pDev->dev, pHba->lct_size,
					pHba->lct, pHba->lct_pa);
			pHba->lct = शून्य;
		पूर्ण
	पूर्ण जबतक (pHba->lct == शून्य);

	PDEBUG("%s: Hardware resource table read.\n", pHba->name);


	// I2O_DPT_EXEC_IOP_BUFFERS_GROUP_NO;
	अगर(adpt_i2o_query_scalar(pHba, 0 , 0x8000, -1, buf, माप(buf))>=0) अणु
		pHba->FwDebugBufferSize = buf[1];
		pHba->FwDebugBuffer_P = ioremap(pHba->base_addr_phys + buf[0],
						pHba->FwDebugBufferSize);
		अगर (pHba->FwDebugBuffer_P) अणु
			pHba->FwDebugFlags_P     = pHba->FwDebugBuffer_P +
							FW_DEBUG_FLAGS_OFFSET;
			pHba->FwDebugBLEDvalue_P = pHba->FwDebugBuffer_P +
							FW_DEBUG_BLED_OFFSET;
			pHba->FwDebugBLEDflag_P  = pHba->FwDebugBLEDvalue_P + 1;
			pHba->FwDebugStrLength_P = pHba->FwDebugBuffer_P +
						FW_DEBUG_STR_LENGTH_OFFSET;
			pHba->FwDebugBuffer_P += buf[2]; 
			pHba->FwDebugFlags = 0;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक adpt_i2o_build_sys_table(व्योम)
अणु
	adpt_hba* pHba = hba_chain;
	पूर्णांक count = 0;

	अगर (sys_tbl)
		dma_मुक्त_coherent(&pHba->pDev->dev, sys_tbl_len,
					sys_tbl, sys_tbl_pa);

	sys_tbl_len = माप(काष्ठा i2o_sys_tbl) +	// Header + IOPs
				(hba_count) * माप(काष्ठा i2o_sys_tbl_entry);

	sys_tbl = dma_alloc_coherent(&pHba->pDev->dev,
				sys_tbl_len, &sys_tbl_pa, GFP_KERNEL);
	अगर (!sys_tbl) अणु
		prपूर्णांकk(KERN_WARNING "SysTab Set failed. Out of memory.\n");	
		वापस -ENOMEM;
	पूर्ण

	sys_tbl->num_entries = hba_count;
	sys_tbl->version = I2OVERSION;
	sys_tbl->change_ind = sys_tbl_ind++;

	क्रम(pHba = hba_chain; pHba; pHba = pHba->next) अणु
		u64 addr;
		// Get updated Status Block so we have the latest inक्रमmation
		अगर (adpt_i2o_status_get(pHba)) अणु
			sys_tbl->num_entries--;
			जारी; // try next one	
		पूर्ण

		sys_tbl->iops[count].org_id = pHba->status_block->org_id;
		sys_tbl->iops[count].iop_id = pHba->unit + 2;
		sys_tbl->iops[count].seg_num = 0;
		sys_tbl->iops[count].i2o_version = pHba->status_block->i2o_version;
		sys_tbl->iops[count].iop_state = pHba->status_block->iop_state;
		sys_tbl->iops[count].msg_type = pHba->status_block->msg_type;
		sys_tbl->iops[count].frame_size = pHba->status_block->inbound_frame_size;
		sys_tbl->iops[count].last_changed = sys_tbl_ind - 1; // ??
		sys_tbl->iops[count].iop_capabilities = pHba->status_block->iop_capabilities;
		addr = pHba->base_addr_phys + 0x40;
		sys_tbl->iops[count].inbound_low = dma_low(addr);
		sys_tbl->iops[count].inbound_high = dma_high(addr);

		count++;
	पूर्ण

#अगर_घोषित DEBUG
अणु
	u32 *table = (u32*)sys_tbl;
	prपूर्णांकk(KERN_DEBUG"sys_tbl_len=%d in 32bit words\n",(sys_tbl_len >>2));
	क्रम(count = 0; count < (sys_tbl_len >>2); count++) अणु
		prपूर्णांकk(KERN_INFO "sys_tbl[%d] = %0#10x\n", 
			count, table[count]);
	पूर्ण
पूर्ण
#पूर्ण_अगर

	वापस 0;
पूर्ण


/*
 *	 Dump the inक्रमmation block associated with a given unit (TID)
 */
 
अटल व्योम adpt_i2o_report_hba_unit(adpt_hba* pHba, काष्ठा i2o_device *d)
अणु
	अक्षर buf[64];
	पूर्णांक unit = d->lct_data.tid;

	prपूर्णांकk(KERN_INFO "TID %3.3d ", unit);

	अगर(adpt_i2o_query_scalar(pHba, unit, 0xF100, 3, buf, 16)>=0)
	अणु
		buf[16]=0;
		prपूर्णांकk(" Vendor: %-12.12s", buf);
	पूर्ण
	अगर(adpt_i2o_query_scalar(pHba, unit, 0xF100, 4, buf, 16)>=0)
	अणु
		buf[16]=0;
		prपूर्णांकk(" Device: %-12.12s", buf);
	पूर्ण
	अगर(adpt_i2o_query_scalar(pHba, unit, 0xF100, 6, buf, 8)>=0)
	अणु
		buf[8]=0;
		prपूर्णांकk(" Rev: %-12.12s\n", buf);
	पूर्ण
#अगर_घोषित DEBUG
	 prपूर्णांकk(KERN_INFO "\tClass: %.21s\n", adpt_i2o_get_class_name(d->lct_data.class_id));
	 prपूर्णांकk(KERN_INFO "\tSubclass: 0x%04X\n", d->lct_data.sub_class);
	 prपूर्णांकk(KERN_INFO "\tFlags: ");

	 अगर(d->lct_data.device_flags&(1<<0))
		  prपूर्णांकk("C");	     // ConfigDialog requested
	 अगर(d->lct_data.device_flags&(1<<1))
		  prपूर्णांकk("U");	     // Multi-user capable
	 अगर(!(d->lct_data.device_flags&(1<<4)))
		  prपूर्णांकk("P");	     // Peer service enabled!
	 अगर(!(d->lct_data.device_flags&(1<<5)))
		  prपूर्णांकk("M");	     // Mgmt service enabled!
	 prपूर्णांकk("\n");
#पूर्ण_अगर
पूर्ण

#अगर_घोषित DEBUG
/*
 *	Do i2o class name lookup
 */
अटल स्थिर अक्षर *adpt_i2o_get_class_name(पूर्णांक class)
अणु
	पूर्णांक idx = 16;
	अटल अक्षर *i2o_class_name[] = अणु
		"Executive",
		"Device Driver Module",
		"Block Device",
		"Tape Device",
		"LAN Interface",
		"WAN Interface",
		"Fibre Channel Port",
		"Fibre Channel Device",
		"SCSI Device",
		"ATE Port",
		"ATE Device",
		"Floppy Controller",
		"Floppy Device",
		"Secondary Bus Port",
		"Peer Transport Agent",
		"Peer Transport",
		"Unknown"
	पूर्ण;
	
	चयन(class&0xFFF) अणु
	हाल I2O_CLASS_EXECUTIVE:
		idx = 0; अवरोध;
	हाल I2O_CLASS_DDM:
		idx = 1; अवरोध;
	हाल I2O_CLASS_RANDOM_BLOCK_STORAGE:
		idx = 2; अवरोध;
	हाल I2O_CLASS_SEQUENTIAL_STORAGE:
		idx = 3; अवरोध;
	हाल I2O_CLASS_LAN:
		idx = 4; अवरोध;
	हाल I2O_CLASS_WAN:
		idx = 5; अवरोध;
	हाल I2O_CLASS_FIBRE_CHANNEL_PORT:
		idx = 6; अवरोध;
	हाल I2O_CLASS_FIBRE_CHANNEL_PERIPHERAL:
		idx = 7; अवरोध;
	हाल I2O_CLASS_SCSI_PERIPHERAL:
		idx = 8; अवरोध;
	हाल I2O_CLASS_ATE_PORT:
		idx = 9; अवरोध;
	हाल I2O_CLASS_ATE_PERIPHERAL:
		idx = 10; अवरोध;
	हाल I2O_CLASS_FLOPPY_CONTROLLER:
		idx = 11; अवरोध;
	हाल I2O_CLASS_FLOPPY_DEVICE:
		idx = 12; अवरोध;
	हाल I2O_CLASS_BUS_ADAPTER_PORT:
		idx = 13; अवरोध;
	हाल I2O_CLASS_PEER_TRANSPORT_AGENT:
		idx = 14; अवरोध;
	हाल I2O_CLASS_PEER_TRANSPORT:
		idx = 15; अवरोध;
	पूर्ण
	वापस i2o_class_name[idx];
पूर्ण
#पूर्ण_अगर


अटल s32 adpt_i2o_hrt_get(adpt_hba* pHba)
अणु
	u32 msg[6];
	पूर्णांक ret, size = माप(i2o_hrt);

	करो अणु
		अगर (pHba->hrt == शून्य) अणु
			pHba->hrt = dma_alloc_coherent(&pHba->pDev->dev,
					size, &pHba->hrt_pa, GFP_KERNEL);
			अगर (pHba->hrt == शून्य) अणु
				prपूर्णांकk(KERN_CRIT "%s: Hrt Get failed; Out of memory.\n", pHba->name);
				वापस -ENOMEM;
			पूर्ण
		पूर्ण

		msg[0]= SIX_WORD_MSG_SIZE| SGL_OFFSET_4;
		msg[1]= I2O_CMD_HRT_GET<<24 | HOST_TID<<12 | ADAPTER_TID;
		msg[2]= 0;
		msg[3]= 0;
		msg[4]= (0xD0000000 | size);    /* Simple transaction */
		msg[5]= (u32)pHba->hrt_pa;	/* Dump it here */

		अगर ((ret = adpt_i2o_post_रुको(pHba, msg, माप(msg),20))) अणु
			prपूर्णांकk(KERN_ERR "%s: Unable to get HRT (status=%#10x)\n", pHba->name, ret);
			वापस ret;
		पूर्ण

		अगर (pHba->hrt->num_entries * pHba->hrt->entry_len << 2 > size) अणु
			पूर्णांक newsize = pHba->hrt->num_entries * pHba->hrt->entry_len << 2;
			dma_मुक्त_coherent(&pHba->pDev->dev, size,
				pHba->hrt, pHba->hrt_pa);
			size = newsize;
			pHba->hrt = शून्य;
		पूर्ण
	पूर्ण जबतक(pHba->hrt == शून्य);
	वापस 0;
पूर्ण                                                                                                                                       

/*
 *	 Query one scalar group value or a whole scalar group.
 */		    	
अटल पूर्णांक adpt_i2o_query_scalar(adpt_hba* pHba, पूर्णांक tid, 
			पूर्णांक group, पूर्णांक field, व्योम *buf, पूर्णांक buflen)
अणु
	u16 opblk[] = अणु 1, 0, I2O_PARAMS_FIELD_GET, group, 1, field पूर्ण;
	u8 *opblk_va;
	dma_addr_t opblk_pa;
	u8 *resblk_va;
	dma_addr_t resblk_pa;

	पूर्णांक size;

	/* 8 bytes क्रम header */
	resblk_va = dma_alloc_coherent(&pHba->pDev->dev,
			माप(u8) * (8 + buflen), &resblk_pa, GFP_KERNEL);
	अगर (resblk_va == शून्य) अणु
		prपूर्णांकk(KERN_CRIT "%s: query scalar failed; Out of memory.\n", pHba->name);
		वापस -ENOMEM;
	पूर्ण

	opblk_va = dma_alloc_coherent(&pHba->pDev->dev,
			माप(opblk), &opblk_pa, GFP_KERNEL);
	अगर (opblk_va == शून्य) अणु
		dma_मुक्त_coherent(&pHba->pDev->dev, माप(u8) * (8+buflen),
			resblk_va, resblk_pa);
		prपूर्णांकk(KERN_CRIT "%s: query operation failed; Out of memory.\n",
			pHba->name);
		वापस -ENOMEM;
	पूर्ण
	अगर (field == -1)  		/* whole group */
			opblk[4] = -1;

	स_नकल(opblk_va, opblk, माप(opblk));
	size = adpt_i2o_issue_params(I2O_CMD_UTIL_PARAMS_GET, pHba, tid, 
		opblk_va, opblk_pa, माप(opblk),
		resblk_va, resblk_pa, माप(u8)*(8+buflen));
	dma_मुक्त_coherent(&pHba->pDev->dev, माप(opblk), opblk_va, opblk_pa);
	अगर (size == -ETIME) अणु
		dma_मुक्त_coherent(&pHba->pDev->dev, माप(u8) * (8+buflen),
							resblk_va, resblk_pa);
		prपूर्णांकk(KERN_WARNING "%s: issue params failed; Timed out.\n", pHba->name);
		वापस -ETIME;
	पूर्ण अन्यथा अगर (size == -EINTR) अणु
		dma_मुक्त_coherent(&pHba->pDev->dev, माप(u8) * (8+buflen),
							resblk_va, resblk_pa);
		prपूर्णांकk(KERN_WARNING "%s: issue params failed; Interrupted.\n", pHba->name);
		वापस -EINTR;
	पूर्ण
			
	स_नकल(buf, resblk_va+8, buflen);  /* cut off header */

	dma_मुक्त_coherent(&pHba->pDev->dev, माप(u8) * (8+buflen),
						resblk_va, resblk_pa);
	अगर (size < 0)
		वापस size;	

	वापस buflen;
पूर्ण


/*	Issue UTIL_PARAMS_GET or UTIL_PARAMS_SET
 *
 *	This function can be used क्रम all UtilParamsGet/Set operations.
 *	The OperationBlock is given in opblk-buffer, 
 *	and results are वापसed in resblk-buffer.
 *	Note that the minimum sized resblk is 8 bytes and contains
 *	ResultCount, ErrorInfoSize, BlockStatus and BlockSize.
 */
अटल पूर्णांक adpt_i2o_issue_params(पूर्णांक cmd, adpt_hba* pHba, पूर्णांक tid, 
		  व्योम *opblk_va,  dma_addr_t opblk_pa, पूर्णांक oplen,
		व्योम *resblk_va, dma_addr_t resblk_pa, पूर्णांक reslen)
अणु
	u32 msg[9]; 
	u32 *res = (u32 *)resblk_va;
	पूर्णांक रुको_status;

	msg[0] = NINE_WORD_MSG_SIZE | SGL_OFFSET_5;
	msg[1] = cmd << 24 | HOST_TID << 12 | tid; 
	msg[2] = 0;
	msg[3] = 0;
	msg[4] = 0;
	msg[5] = 0x54000000 | oplen;	/* OperationBlock */
	msg[6] = (u32)opblk_pa;
	msg[7] = 0xD0000000 | reslen;	/* ResultBlock */
	msg[8] = (u32)resblk_pa;

	अगर ((रुको_status = adpt_i2o_post_रुको(pHba, msg, माप(msg), 20))) अणु
		prपूर्णांकk("adpt_i2o_issue_params: post_wait failed (%p)\n", resblk_va);
   		वापस रुको_status; 	/* -DetailedStatus */
	पूर्ण

	अगर (res[1]&0x00FF0000) अणु 	/* BlockStatus != SUCCESS */
		prपूर्णांकk(KERN_WARNING "%s: %s - Error:\n  ErrorInfoSize = 0x%02x, "
			"BlockStatus = 0x%02x, BlockSize = 0x%04x\n",
			pHba->name,
			(cmd == I2O_CMD_UTIL_PARAMS_SET) ? "PARAMS_SET"
							 : "PARAMS_GET",   
			res[1]>>24, (res[1]>>16)&0xFF, res[1]&0xFFFF);
		वापस -((res[1] >> 16) & 0xFF); /* -BlockStatus */
	पूर्ण

	वापस 4 + ((res[1] & 0x0000FFFF) << 2); /* bytes used in resblk */
पूर्ण


अटल s32 adpt_i2o_quiesce_hba(adpt_hba* pHba)
अणु
	u32 msg[4];
	पूर्णांक ret;

	adpt_i2o_status_get(pHba);

	/* SysQuiesce discarded अगर IOP not in READY or OPERATIONAL state */

	अगर((pHba->status_block->iop_state != ADAPTER_STATE_READY) &&
   	   (pHba->status_block->iop_state != ADAPTER_STATE_OPERATIONAL))अणु
		वापस 0;
	पूर्ण

	msg[0] = FOUR_WORD_MSG_SIZE|SGL_OFFSET_0;
	msg[1] = I2O_CMD_SYS_QUIESCE<<24|HOST_TID<<12|ADAPTER_TID;
	msg[2] = 0;
	msg[3] = 0;

	अगर((ret = adpt_i2o_post_रुको(pHba, msg, माप(msg), 240))) अणु
		prपूर्णांकk(KERN_INFO"dpti%d: Unable to quiesce (status=%#x).\n",
				pHba->unit, -ret);
	पूर्ण अन्यथा अणु
		prपूर्णांकk(KERN_INFO"dpti%d: Quiesced.\n",pHba->unit);
	पूर्ण

	adpt_i2o_status_get(pHba);
	वापस ret;
पूर्ण


/* 
 * Enable IOP. Allows the IOP to resume बाह्यal operations.
 */
अटल पूर्णांक adpt_i2o_enable_hba(adpt_hba* pHba)
अणु
	u32 msg[4];
	पूर्णांक ret;
	
	adpt_i2o_status_get(pHba);
	अगर(!pHba->status_block)अणु
		वापस -ENOMEM;
	पूर्ण
	/* Enable only allowed on READY state */
	अगर(pHba->status_block->iop_state == ADAPTER_STATE_OPERATIONAL)
		वापस 0;

	अगर(pHba->status_block->iop_state != ADAPTER_STATE_READY)
		वापस -EINVAL;

	msg[0]=FOUR_WORD_MSG_SIZE|SGL_OFFSET_0;
	msg[1]=I2O_CMD_SYS_ENABLE<<24|HOST_TID<<12|ADAPTER_TID;
	msg[2]= 0;
	msg[3]= 0;

	अगर ((ret = adpt_i2o_post_रुको(pHba, msg, माप(msg), 240))) अणु
		prपूर्णांकk(KERN_WARNING"%s: Could not enable (status=%#10x).\n", 
			pHba->name, ret);
	पूर्ण अन्यथा अणु
		PDEBUG("%s: Enabled.\n", pHba->name);
	पूर्ण

	adpt_i2o_status_get(pHba);
	वापस ret;
पूर्ण


अटल पूर्णांक adpt_i2o_systab_send(adpt_hba* pHba)
अणु
	u32 msg[12];
	पूर्णांक ret;

	msg[0] = I2O_MESSAGE_SIZE(12) | SGL_OFFSET_6;
	msg[1] = I2O_CMD_SYS_TAB_SET<<24 | HOST_TID<<12 | ADAPTER_TID;
	msg[2] = 0;
	msg[3] = 0;
	msg[4] = (0<<16) | ((pHba->unit+2) << 12); /* Host 0 IOP ID (unit + 2) */
	msg[5] = 0;				   /* Segment 0 */

	/* 
	 * Provide three SGL-elements:
	 * System table (SysTab), Private memory space declaration and 
	 * Private i/o space declaration  
	 */
	msg[6] = 0x54000000 | sys_tbl_len;
	msg[7] = (u32)sys_tbl_pa;
	msg[8] = 0x54000000 | 0;
	msg[9] = 0;
	msg[10] = 0xD4000000 | 0;
	msg[11] = 0;

	अगर ((ret=adpt_i2o_post_रुको(pHba, msg, माप(msg), 120))) अणु
		prपूर्णांकk(KERN_INFO "%s: Unable to set SysTab (status=%#10x).\n", 
			pHba->name, ret);
	पूर्ण
#अगर_घोषित DEBUG
	अन्यथा अणु
		PINFO("%s: SysTab set.\n", pHba->name);
	पूर्ण
#पूर्ण_अगर

	वापस ret;	
पूर्ण


/*============================================================================
 *
 *============================================================================
 */


#अगर_घोषित UARTDELAY 

अटल अटल व्योम adpt_delay(पूर्णांक millisec)
अणु
	पूर्णांक i;
	क्रम (i = 0; i < millisec; i++) अणु
		udelay(1000);	/* delay क्रम one millisecond */
	पूर्ण
पूर्ण

#पूर्ण_अगर

अटल काष्ठा scsi_host_ढाँचा driver_ढाँचा = अणु
	.module			= THIS_MODULE,
	.name			= "dpt_i2o",
	.proc_name		= "dpt_i2o",
	.show_info		= adpt_show_info,
	.info			= adpt_info,
	.queuecommand		= adpt_queue,
	.eh_पात_handler	= adpt_पात,
	.eh_device_reset_handler = adpt_device_reset,
	.eh_bus_reset_handler	= adpt_bus_reset,
	.eh_host_reset_handler	= adpt_reset,
	.bios_param		= adpt_bios_param,
	.slave_configure	= adpt_slave_configure,
	.can_queue		= MAX_TO_IOP_MESSAGES,
	.this_id		= 7,
पूर्ण;

अटल पूर्णांक __init adpt_init(व्योम)
अणु
	पूर्णांक		error;
	adpt_hba	*pHba, *next;

	prपूर्णांकk("Loading Adaptec I2O RAID: Version " DPT_I2O_VERSION "\n");

	error = adpt_detect(&driver_ढाँचा);
	अगर (error < 0)
		वापस error;
	अगर (hba_chain == शून्य)
		वापस -ENODEV;

	क्रम (pHba = hba_chain; pHba; pHba = pHba->next) अणु
		error = scsi_add_host(pHba->host, &pHba->pDev->dev);
		अगर (error)
			जाओ fail;
		scsi_scan_host(pHba->host);
	पूर्ण
	वापस 0;
fail:
	क्रम (pHba = hba_chain; pHba; pHba = next) अणु
		next = pHba->next;
		scsi_हटाओ_host(pHba->host);
	पूर्ण
	वापस error;
पूर्ण

अटल व्योम __निकास adpt_निकास(व्योम)
अणु
	adpt_hba	*pHba, *next;

	क्रम (pHba = hba_chain; pHba; pHba = next) अणु
		next = pHba->next;
		adpt_release(pHba);
	पूर्ण
पूर्ण

module_init(adpt_init);
module_निकास(adpt_निकास);

MODULE_LICENSE("GPL");
