<शैली गुरु>
/*
 * Scsi Host Layer क्रम MPT (Message Passing Technology) based controllers
 *
 * This code is based on drivers/scsi/mpt3sas/mpt3sas_scsih.c
 * Copyright (C) 2012-2014  LSI Corporation
 * Copyright (C) 2013-2014 Avago Technologies
 *  (mailto: MPT-FusionLinux.pdl@avagotech.com)
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 *
 * NO WARRANTY
 * THE PROGRAM IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OR
 * CONDITIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED INCLUDING, WITHOUT
 * LIMITATION, ANY WARRANTIES OR CONDITIONS OF TITLE, NON-INFRINGEMENT,
 * MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE. Each Recipient is
 * solely responsible क्रम determining the appropriateness of using and
 * distributing the Program and assumes all risks associated with its
 * exercise of rights under this Agreement, including but not limited to
 * the risks and costs of program errors, damage to or loss of data,
 * programs or equipment, and unavailability or पूर्णांकerruption of operations.

 * DISCLAIMER OF LIABILITY
 * NEITHER RECIPIENT NOR ANY CONTRIBUTORS SHALL HAVE ANY LIABILITY FOR ANY
 * सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING WITHOUT LIMITATION LOST PROFITS), HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR
 * TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE
 * USE OR DISTRIBUTION OF THE PROGRAM OR THE EXERCISE OF ANY RIGHTS GRANTED
 * HEREUNDER, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGES

 * You should have received a copy of the GNU General Public License
 * aदीर्घ with this program; अगर not, ग_लिखो to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fअगरth Floor, Boston, MA  02110-1301,
 * USA.
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/blkdev.h>
#समावेश <linux/sched.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/delay.h>
#समावेश <linux/pci.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/aer.h>
#समावेश <linux/raid_class.h>
#समावेश <linux/blk-mq-pci.h>
#समावेश <यंत्र/unaligned.h>

#समावेश "mpt3sas_base.h"

#घोषणा RAID_CHANNEL 1

#घोषणा PCIE_CHANNEL 2

/* क्रमward proto's */
अटल व्योम _scsih_expander_node_हटाओ(काष्ठा MPT3SAS_ADAPTER *ioc,
	काष्ठा _sas_node *sas_expander);
अटल व्योम _firmware_event_work(काष्ठा work_काष्ठा *work);

अटल व्योम _scsih_हटाओ_device(काष्ठा MPT3SAS_ADAPTER *ioc,
	काष्ठा _sas_device *sas_device);
अटल पूर्णांक _scsih_add_device(काष्ठा MPT3SAS_ADAPTER *ioc, u16 handle,
	u8 retry_count, u8 is_pd);
अटल पूर्णांक _scsih_pcie_add_device(काष्ठा MPT3SAS_ADAPTER *ioc, u16 handle);
अटल व्योम _scsih_pcie_device_हटाओ_from_sml(काष्ठा MPT3SAS_ADAPTER *ioc,
	काष्ठा _pcie_device *pcie_device);
अटल व्योम
_scsih_pcie_check_device(काष्ठा MPT3SAS_ADAPTER *ioc, u16 handle);
अटल u8 _scsih_check_क्रम_pending_पंचांग(काष्ठा MPT3SAS_ADAPTER *ioc, u16 smid);

/* global parameters */
LIST_HEAD(mpt3sas_ioc_list);
/* global ioc lock क्रम list operations */
DEFINE_SPINLOCK(gioc_lock);

MODULE_AUTHOR(MPT3SAS_AUTHOR);
MODULE_DESCRIPTION(MPT3SAS_DESCRIPTION);
MODULE_LICENSE("GPL");
MODULE_VERSION(MPT3SAS_DRIVER_VERSION);
MODULE_ALIAS("mpt2sas");

/* local parameters */
अटल u8 scsi_io_cb_idx = -1;
अटल u8 पंचांग_cb_idx = -1;
अटल u8 ctl_cb_idx = -1;
अटल u8 base_cb_idx = -1;
अटल u8 port_enable_cb_idx = -1;
अटल u8 transport_cb_idx = -1;
अटल u8 scsih_cb_idx = -1;
अटल u8 config_cb_idx = -1;
अटल पूर्णांक mpt2_ids;
अटल पूर्णांक mpt3_ids;

अटल u8 पंचांग_tr_cb_idx = -1 ;
अटल u8 पंचांग_tr_volume_cb_idx = -1 ;
अटल u8 पंचांग_sas_control_cb_idx = -1;

/* command line options */
अटल u32 logging_level;
MODULE_PARM_DESC(logging_level,
	" bits for enabling additional logging info (default=0)");


अटल uलघु max_sectors = 0xFFFF;
module_param(max_sectors, uलघु, 0444);
MODULE_PARM_DESC(max_sectors, "max sectors, range 64 to 32767  default=32767");


अटल पूर्णांक missing_delay[2] = अणु-1, -1पूर्ण;
module_param_array(missing_delay, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(missing_delay, " device missing delay , io missing delay");

/* scsi-mid layer global parmeter is max_report_luns, which is 511 */
#घोषणा MPT3SAS_MAX_LUN (16895)
अटल u64 max_lun = MPT3SAS_MAX_LUN;
module_param(max_lun, ulदीर्घ, 0444);
MODULE_PARM_DESC(max_lun, " max lun, default=16895 ");

अटल uलघु hbas_to_क्रमागतerate;
module_param(hbas_to_क्रमागतerate, uलघु, 0444);
MODULE_PARM_DESC(hbas_to_क्रमागतerate,
		" 0 - क्रमागतerates both SAS 2.0 & SAS 3.0 generation HBAs\न \
		  1 - क्रमागतerates only SAS 2.0 generation HBAs\न \
		  2 - क्रमागतerates only SAS 3.0 generation HBAs (शेष=0)");

/* diag_buffer_enable is bitwise
 * bit 0 set = TRACE
 * bit 1 set = SNAPSHOT
 * bit 2 set = EXTENDED
 *
 * Either bit can be set, or both
 */
अटल पूर्णांक diag_buffer_enable = -1;
module_param(diag_buffer_enable, पूर्णांक, 0444);
MODULE_PARM_DESC(diag_buffer_enable,
	" post diag buffers (TRACE=1/SNAPSHOT=2/EXTENDED=4/default=0)");
अटल पूर्णांक disable_discovery = -1;
module_param(disable_discovery, पूर्णांक, 0444);
MODULE_PARM_DESC(disable_discovery, " disable discovery ");


/* permit overriding the host protection capabilities mask (EEDP/T10 PI) */
अटल पूर्णांक prot_mask = -1;
module_param(prot_mask, पूर्णांक, 0444);
MODULE_PARM_DESC(prot_mask, " host protection capabilities mask, def=7 ");

अटल bool enable_sdev_max_qd;
module_param(enable_sdev_max_qd, bool, 0444);
MODULE_PARM_DESC(enable_sdev_max_qd,
	"Enable sdev max qd as can_queue, def=disabled(0)");

अटल पूर्णांक multipath_on_hba = -1;
module_param(multipath_on_hba, पूर्णांक, 0);
MODULE_PARM_DESC(multipath_on_hba,
	"Multipath support to add same target device\n\t\t"
	"as many times as it is visible to HBA from various paths\n\t\t"
	"(by default:\n\t\t"
	"\t SAS 2.0 & SAS 3.0 HBA - This will be disabled,\n\t\t"
	"\t SAS 3.5 HBA - This will be enabled)");

अटल पूर्णांक host_tagset_enable = 1;
module_param(host_tagset_enable, पूर्णांक, 0444);
MODULE_PARM_DESC(host_tagset_enable,
	"Shared host tagset enable/disable Default: enable(1)");

/* raid transport support */
अटल काष्ठा raid_ढाँचा *mpt3sas_raid_ढाँचा;
अटल काष्ठा raid_ढाँचा *mpt2sas_raid_ढाँचा;


/**
 * काष्ठा sense_info - common काष्ठाure क्रम obtaining sense keys
 * @skey: sense key
 * @asc: additional sense code
 * @ascq: additional sense code qualअगरier
 */
काष्ठा sense_info अणु
	u8 skey;
	u8 asc;
	u8 ascq;
पूर्ण;

#घोषणा MPT3SAS_PROCESS_TRIGGER_DIAG (0xFFFB)
#घोषणा MPT3SAS_TURN_ON_PFA_LED (0xFFFC)
#घोषणा MPT3SAS_PORT_ENABLE_COMPLETE (0xFFFD)
#घोषणा MPT3SAS_ABRT_TASK_SET (0xFFFE)
#घोषणा MPT3SAS_REMOVE_UNRESPONDING_DEVICES (0xFFFF)
/**
 * काष्ठा fw_event_work - firmware event काष्ठा
 * @list: link list framework
 * @work: work object (ioc->fault_reset_work_q)
 * @ioc: per adapter object
 * @device_handle: device handle
 * @VF_ID: भव function id
 * @VP_ID: भव port id
 * @ignore: flag meaning this event has been marked to ignore
 * @event: firmware event MPI2_EVENT_XXX defined in mpi2_ioc.h
 * @refcount: kref क्रम this event
 * @event_data: reply event data payload follows
 *
 * This object stored on ioc->fw_event_list.
 */
काष्ठा fw_event_work अणु
	काष्ठा list_head	list;
	काष्ठा work_काष्ठा	work;

	काष्ठा MPT3SAS_ADAPTER *ioc;
	u16			device_handle;
	u8			VF_ID;
	u8			VP_ID;
	u8			ignore;
	u16			event;
	काष्ठा kref		refcount;
	अक्षर			event_data[] __aligned(4);
पूर्ण;

अटल व्योम fw_event_work_मुक्त(काष्ठा kref *r)
अणु
	kमुक्त(container_of(r, काष्ठा fw_event_work, refcount));
पूर्ण

अटल व्योम fw_event_work_get(काष्ठा fw_event_work *fw_work)
अणु
	kref_get(&fw_work->refcount);
पूर्ण

अटल व्योम fw_event_work_put(काष्ठा fw_event_work *fw_work)
अणु
	kref_put(&fw_work->refcount, fw_event_work_मुक्त);
पूर्ण

अटल काष्ठा fw_event_work *alloc_fw_event_work(पूर्णांक len)
अणु
	काष्ठा fw_event_work *fw_event;

	fw_event = kzalloc(माप(*fw_event) + len, GFP_ATOMIC);
	अगर (!fw_event)
		वापस शून्य;

	kref_init(&fw_event->refcount);
	वापस fw_event;
पूर्ण

/**
 * काष्ठा _scsi_io_transfer - scsi io transfer
 * @handle: sas device handle (asचिन्हित by firmware)
 * @is_raid: flag set क्रम hidden raid components
 * @dir: DMA_TO_DEVICE, DMA_FROM_DEVICE,
 * @data_length: data transfer length
 * @data_dma: dma poपूर्णांकer to data
 * @sense: sense data
 * @lun: lun number
 * @cdb_length: cdb length
 * @cdb: cdb contents
 * @समयout: समयout क्रम this command
 * @VF_ID: भव function id
 * @VP_ID: भव port id
 * @valid_reply: flag set क्रम reply message
 * @sense_length: sense length
 * @ioc_status: ioc status
 * @scsi_state: scsi state
 * @scsi_status: scsi staus
 * @log_info: log inक्रमmation
 * @transfer_length: data length transfer when there is a reply message
 *
 * Used क्रम sending पूर्णांकernal scsi commands to devices within this module.
 * Refer to _scsi_send_scsi_io().
 */
काष्ठा _scsi_io_transfer अणु
	u16	handle;
	u8	is_raid;
	क्रमागत dma_data_direction dir;
	u32	data_length;
	dma_addr_t data_dma;
	u8	sense[SCSI_SENSE_BUFFERSIZE];
	u32	lun;
	u8	cdb_length;
	u8	cdb[32];
	u8	समयout;
	u8	VF_ID;
	u8	VP_ID;
	u8	valid_reply;
  /* the following bits are only valid when 'valid_reply = 1' */
	u32	sense_length;
	u16	ioc_status;
	u8	scsi_state;
	u8	scsi_status;
	u32	log_info;
	u32	transfer_length;
पूर्ण;

/**
 * _scsih_set_debug_level - global setting of ioc->logging_level.
 * @val: ?
 * @kp: ?
 *
 * Note: The logging levels are defined in mpt3sas_debug.h.
 */
अटल पूर्णांक
_scsih_set_debug_level(स्थिर अक्षर *val, स्थिर काष्ठा kernel_param *kp)
अणु
	पूर्णांक ret = param_set_पूर्णांक(val, kp);
	काष्ठा MPT3SAS_ADAPTER *ioc;

	अगर (ret)
		वापस ret;

	pr_info("setting logging_level(0x%08x)\n", logging_level);
	spin_lock(&gioc_lock);
	list_क्रम_each_entry(ioc, &mpt3sas_ioc_list, list)
		ioc->logging_level = logging_level;
	spin_unlock(&gioc_lock);
	वापस 0;
पूर्ण
module_param_call(logging_level, _scsih_set_debug_level, param_get_पूर्णांक,
	&logging_level, 0644);

/**
 * _scsih_srch_boot_sas_address - search based on sas_address
 * @sas_address: sas address
 * @boot_device: boot device object from bios page 2
 *
 * Return: 1 when there's a match, 0 means no match.
 */
अटल अंतरभूत पूर्णांक
_scsih_srch_boot_sas_address(u64 sas_address,
	Mpi2BootDeviceSasWwid_t *boot_device)
अणु
	वापस (sas_address == le64_to_cpu(boot_device->SASAddress)) ?  1 : 0;
पूर्ण

/**
 * _scsih_srch_boot_device_name - search based on device name
 * @device_name: device name specअगरied in INDENTIFY fram
 * @boot_device: boot device object from bios page 2
 *
 * Return: 1 when there's a match, 0 means no match.
 */
अटल अंतरभूत पूर्णांक
_scsih_srch_boot_device_name(u64 device_name,
	Mpi2BootDeviceDeviceName_t *boot_device)
अणु
	वापस (device_name == le64_to_cpu(boot_device->DeviceName)) ? 1 : 0;
पूर्ण

/**
 * _scsih_srch_boot_encl_slot - search based on enclosure_logical_id/slot
 * @enclosure_logical_id: enclosure logical id
 * @slot_number: slot number
 * @boot_device: boot device object from bios page 2
 *
 * Return: 1 when there's a match, 0 means no match.
 */
अटल अंतरभूत पूर्णांक
_scsih_srch_boot_encl_slot(u64 enclosure_logical_id, u16 slot_number,
	Mpi2BootDeviceEnclosureSlot_t *boot_device)
अणु
	वापस (enclosure_logical_id == le64_to_cpu(boot_device->
	    EnclosureLogicalID) && slot_number == le16_to_cpu(boot_device->
	    SlotNumber)) ? 1 : 0;
पूर्ण

/**
 * mpt3sas_get_port_by_id - get hba port entry corresponding to provided
 *			  port number from port list
 * @ioc: per adapter object
 * @port_id: port number
 * @bypass_dirty_port_flag: when set look the matching hba port entry even
 *			अगर hba port entry is marked as dirty.
 *
 * Search क्रम hba port entry corresponding to provided port number,
 * अगर available वापस port object otherwise वापस शून्य.
 */
काष्ठा hba_port *
mpt3sas_get_port_by_id(काष्ठा MPT3SAS_ADAPTER *ioc,
	u8 port_id, u8 bypass_dirty_port_flag)
अणु
	काष्ठा hba_port *port, *port_next;

	/*
	 * When multipath_on_hba is disabled then
	 * search the hba_port entry using शेष
	 * port id i.e. 255
	 */
	अगर (!ioc->multipath_on_hba)
		port_id = MULTIPATH_DISABLED_PORT_ID;

	list_क्रम_each_entry_safe(port, port_next,
	    &ioc->port_table_list, list) अणु
		अगर (port->port_id != port_id)
			जारी;
		अगर (bypass_dirty_port_flag)
			वापस port;
		अगर (port->flags & HBA_PORT_FLAG_सूचीTY_PORT)
			जारी;
		वापस port;
	पूर्ण

	/*
	 * Allocate hba_port object क्रम शेष port id (i.e. 255)
	 * when multipath_on_hba is disabled क्रम the HBA.
	 * And add this object to port_table_list.
	 */
	अगर (!ioc->multipath_on_hba) अणु
		port = kzalloc(माप(काष्ठा hba_port), GFP_ATOMIC);
		अगर (!port)
			वापस शून्य;

		port->port_id = port_id;
		ioc_info(ioc,
		   "hba_port entry: %p, port: %d is added to hba_port list\n",
		   port, port->port_id);
		list_add_tail(&port->list,
		    &ioc->port_table_list);
		वापस port;
	पूर्ण
	वापस शून्य;
पूर्ण

/**
 * mpt3sas_get_vphy_by_phy - get भव_phy object corresponding to phy number
 * @ioc: per adapter object
 * @port: hba_port object
 * @phy: phy number
 *
 * Return भव_phy object corresponding to phy number.
 */
काष्ठा भव_phy *
mpt3sas_get_vphy_by_phy(काष्ठा MPT3SAS_ADAPTER *ioc,
	काष्ठा hba_port *port, u32 phy)
अणु
	काष्ठा भव_phy *vphy, *vphy_next;

	अगर (!port->vphys_mask)
		वापस शून्य;

	list_क्रम_each_entry_safe(vphy, vphy_next, &port->vphys_list, list) अणु
		अगर (vphy->phy_mask & (1 << phy))
			वापस vphy;
	पूर्ण
	वापस शून्य;
पूर्ण

/**
 * _scsih_is_boot_device - search क्रम matching boot device.
 * @sas_address: sas address
 * @device_name: device name specअगरied in INDENTIFY fram
 * @enclosure_logical_id: enclosure logical id
 * @slot: slot number
 * @क्रमm: specअगरies boot device क्रमm
 * @boot_device: boot device object from bios page 2
 *
 * Return: 1 when there's a match, 0 means no match.
 */
अटल पूर्णांक
_scsih_is_boot_device(u64 sas_address, u64 device_name,
	u64 enclosure_logical_id, u16 slot, u8 क्रमm,
	Mpi2BiosPage2BootDevice_t *boot_device)
अणु
	पूर्णांक rc = 0;

	चयन (क्रमm) अणु
	हाल MPI2_BIOSPAGE2_FORM_SAS_WWID:
		अगर (!sas_address)
			अवरोध;
		rc = _scsih_srch_boot_sas_address(
		    sas_address, &boot_device->SasWwid);
		अवरोध;
	हाल MPI2_BIOSPAGE2_FORM_ENCLOSURE_SLOT:
		अगर (!enclosure_logical_id)
			अवरोध;
		rc = _scsih_srch_boot_encl_slot(
		    enclosure_logical_id,
		    slot, &boot_device->EnclosureSlot);
		अवरोध;
	हाल MPI2_BIOSPAGE2_FORM_DEVICE_NAME:
		अगर (!device_name)
			अवरोध;
		rc = _scsih_srch_boot_device_name(
		    device_name, &boot_device->DeviceName);
		अवरोध;
	हाल MPI2_BIOSPAGE2_FORM_NO_DEVICE_SPECIFIED:
		अवरोध;
	पूर्ण

	वापस rc;
पूर्ण

/**
 * _scsih_get_sas_address - set the sas_address क्रम given device handle
 * @ioc: ?
 * @handle: device handle
 * @sas_address: sas address
 *
 * Return: 0 success, non-zero when failure
 */
अटल पूर्णांक
_scsih_get_sas_address(काष्ठा MPT3SAS_ADAPTER *ioc, u16 handle,
	u64 *sas_address)
अणु
	Mpi2SasDevicePage0_t sas_device_pg0;
	Mpi2ConfigReply_t mpi_reply;
	u32 ioc_status;

	*sas_address = 0;

	अगर ((mpt3sas_config_get_sas_device_pg0(ioc, &mpi_reply, &sas_device_pg0,
	    MPI2_SAS_DEVICE_PGAD_FORM_HANDLE, handle))) अणु
		ioc_err(ioc, "failure at %s:%d/%s()!\n",
			__खाता__, __LINE__, __func__);
		वापस -ENXIO;
	पूर्ण

	ioc_status = le16_to_cpu(mpi_reply.IOCStatus) & MPI2_IOCSTATUS_MASK;
	अगर (ioc_status == MPI2_IOCSTATUS_SUCCESS) अणु
		/* For HBA, vSES करोesn't वापस HBA SAS address. Instead वापस
		 * vSES's sas address.
		 */
		अगर ((handle <= ioc->sas_hba.num_phys) &&
		   (!(le32_to_cpu(sas_device_pg0.DeviceInfo) &
		   MPI2_SAS_DEVICE_INFO_SEP)))
			*sas_address = ioc->sas_hba.sas_address;
		अन्यथा
			*sas_address = le64_to_cpu(sas_device_pg0.SASAddress);
		वापस 0;
	पूर्ण

	/* we hit this because the given parent handle करोesn't exist */
	अगर (ioc_status == MPI2_IOCSTATUS_CONFIG_INVALID_PAGE)
		वापस -ENXIO;

	/* अन्यथा error हाल */
	ioc_err(ioc, "handle(0x%04x), ioc_status(0x%04x), failure at %s:%d/%s()!\n",
		handle, ioc_status, __खाता__, __LINE__, __func__);
	वापस -EIO;
पूर्ण

/**
 * _scsih_determine_boot_device - determine boot device.
 * @ioc: per adapter object
 * @device: sas_device or pcie_device object
 * @channel: SAS or PCIe channel
 *
 * Determines whether this device should be first reported device to
 * to scsi-ml or sas transport, this purpose is क्रम persistent boot device.
 * There are primary, alternate, and current entries in bios page 2. The order
 * priority is primary, alternate, then current.  This routine saves
 * the corresponding device object.
 * The saved data to be used later in _scsih_probe_boot_devices().
 */
अटल व्योम
_scsih_determine_boot_device(काष्ठा MPT3SAS_ADAPTER *ioc, व्योम *device,
	u32 channel)
अणु
	काष्ठा _sas_device *sas_device;
	काष्ठा _pcie_device *pcie_device;
	काष्ठा _raid_device *raid_device;
	u64 sas_address;
	u64 device_name;
	u64 enclosure_logical_id;
	u16 slot;

	 /* only process this function when driver loads */
	अगर (!ioc->is_driver_loading)
		वापस;

	 /* no Bios, वापस immediately */
	अगर (!ioc->bios_pg3.BiosVersion)
		वापस;

	अगर (channel == RAID_CHANNEL) अणु
		raid_device = device;
		sas_address = raid_device->wwid;
		device_name = 0;
		enclosure_logical_id = 0;
		slot = 0;
	पूर्ण अन्यथा अगर (channel == PCIE_CHANNEL) अणु
		pcie_device = device;
		sas_address = pcie_device->wwid;
		device_name = 0;
		enclosure_logical_id = 0;
		slot = 0;
	पूर्ण अन्यथा अणु
		sas_device = device;
		sas_address = sas_device->sas_address;
		device_name = sas_device->device_name;
		enclosure_logical_id = sas_device->enclosure_logical_id;
		slot = sas_device->slot;
	पूर्ण

	अगर (!ioc->req_boot_device.device) अणु
		अगर (_scsih_is_boot_device(sas_address, device_name,
		    enclosure_logical_id, slot,
		    (ioc->bios_pg2.ReqBootDeviceForm &
		    MPI2_BIOSPAGE2_FORM_MASK),
		    &ioc->bios_pg2.RequestedBootDevice)) अणु
			dinitprपूर्णांकk(ioc,
				    ioc_info(ioc, "%s: req_boot_device(0x%016llx)\n",
					     __func__, (u64)sas_address));
			ioc->req_boot_device.device = device;
			ioc->req_boot_device.channel = channel;
		पूर्ण
	पूर्ण

	अगर (!ioc->req_alt_boot_device.device) अणु
		अगर (_scsih_is_boot_device(sas_address, device_name,
		    enclosure_logical_id, slot,
		    (ioc->bios_pg2.ReqAltBootDeviceForm &
		    MPI2_BIOSPAGE2_FORM_MASK),
		    &ioc->bios_pg2.RequestedAltBootDevice)) अणु
			dinitprपूर्णांकk(ioc,
				    ioc_info(ioc, "%s: req_alt_boot_device(0x%016llx)\n",
					     __func__, (u64)sas_address));
			ioc->req_alt_boot_device.device = device;
			ioc->req_alt_boot_device.channel = channel;
		पूर्ण
	पूर्ण

	अगर (!ioc->current_boot_device.device) अणु
		अगर (_scsih_is_boot_device(sas_address, device_name,
		    enclosure_logical_id, slot,
		    (ioc->bios_pg2.CurrentBootDeviceForm &
		    MPI2_BIOSPAGE2_FORM_MASK),
		    &ioc->bios_pg2.CurrentBootDevice)) अणु
			dinitprपूर्णांकk(ioc,
				    ioc_info(ioc, "%s: current_boot_device(0x%016llx)\n",
					     __func__, (u64)sas_address));
			ioc->current_boot_device.device = device;
			ioc->current_boot_device.channel = channel;
		पूर्ण
	पूर्ण
पूर्ण

अटल काष्ठा _sas_device *
__mpt3sas_get_sdev_from_target(काष्ठा MPT3SAS_ADAPTER *ioc,
		काष्ठा MPT3SAS_TARGET *tgt_priv)
अणु
	काष्ठा _sas_device *ret;

	निश्चित_spin_locked(&ioc->sas_device_lock);

	ret = tgt_priv->sas_dev;
	अगर (ret)
		sas_device_get(ret);

	वापस ret;
पूर्ण

अटल काष्ठा _sas_device *
mpt3sas_get_sdev_from_target(काष्ठा MPT3SAS_ADAPTER *ioc,
		काष्ठा MPT3SAS_TARGET *tgt_priv)
अणु
	काष्ठा _sas_device *ret;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ioc->sas_device_lock, flags);
	ret = __mpt3sas_get_sdev_from_target(ioc, tgt_priv);
	spin_unlock_irqrestore(&ioc->sas_device_lock, flags);

	वापस ret;
पूर्ण

अटल काष्ठा _pcie_device *
__mpt3sas_get_pdev_from_target(काष्ठा MPT3SAS_ADAPTER *ioc,
	काष्ठा MPT3SAS_TARGET *tgt_priv)
अणु
	काष्ठा _pcie_device *ret;

	निश्चित_spin_locked(&ioc->pcie_device_lock);

	ret = tgt_priv->pcie_dev;
	अगर (ret)
		pcie_device_get(ret);

	वापस ret;
पूर्ण

/**
 * mpt3sas_get_pdev_from_target - pcie device search
 * @ioc: per adapter object
 * @tgt_priv: starget निजी object
 *
 * Context: This function will acquire ioc->pcie_device_lock and will release
 * beक्रमe वापसing the pcie_device object.
 *
 * This searches क्रम pcie_device from target, then वापस pcie_device object.
 */
अटल काष्ठा _pcie_device *
mpt3sas_get_pdev_from_target(काष्ठा MPT3SAS_ADAPTER *ioc,
	काष्ठा MPT3SAS_TARGET *tgt_priv)
अणु
	काष्ठा _pcie_device *ret;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ioc->pcie_device_lock, flags);
	ret = __mpt3sas_get_pdev_from_target(ioc, tgt_priv);
	spin_unlock_irqrestore(&ioc->pcie_device_lock, flags);

	वापस ret;
पूर्ण


/**
 * __mpt3sas_get_sdev_by_rphy - sas device search
 * @ioc: per adapter object
 * @rphy: sas_rphy poपूर्णांकer
 *
 * Context: This function will acquire ioc->sas_device_lock and will release
 * beक्रमe वापसing the sas_device object.
 *
 * This searches क्रम sas_device from rphy object
 * then वापस sas_device object.
 */
काष्ठा _sas_device *
__mpt3sas_get_sdev_by_rphy(काष्ठा MPT3SAS_ADAPTER *ioc,
	काष्ठा sas_rphy *rphy)
अणु
	काष्ठा _sas_device *sas_device;

	निश्चित_spin_locked(&ioc->sas_device_lock);

	list_क्रम_each_entry(sas_device, &ioc->sas_device_list, list) अणु
		अगर (sas_device->rphy != rphy)
			जारी;
		sas_device_get(sas_device);
		वापस sas_device;
	पूर्ण

	sas_device = शून्य;
	list_क्रम_each_entry(sas_device, &ioc->sas_device_init_list, list) अणु
		अगर (sas_device->rphy != rphy)
			जारी;
		sas_device_get(sas_device);
		वापस sas_device;
	पूर्ण

	वापस शून्य;
पूर्ण

/**
 * __mpt3sas_get_sdev_by_addr - get _sas_device object corresponding to provided
 *				sas address from sas_device_list list
 * @ioc: per adapter object
 * @sas_address: device sas address
 * @port: port number
 *
 * Search क्रम _sas_device object corresponding to provided sas address,
 * अगर available वापस _sas_device object address otherwise वापस शून्य.
 */
काष्ठा _sas_device *
__mpt3sas_get_sdev_by_addr(काष्ठा MPT3SAS_ADAPTER *ioc,
	u64 sas_address, काष्ठा hba_port *port)
अणु
	काष्ठा _sas_device *sas_device;

	अगर (!port)
		वापस शून्य;

	निश्चित_spin_locked(&ioc->sas_device_lock);

	list_क्रम_each_entry(sas_device, &ioc->sas_device_list, list) अणु
		अगर (sas_device->sas_address != sas_address)
			जारी;
		अगर (sas_device->port != port)
			जारी;
		sas_device_get(sas_device);
		वापस sas_device;
	पूर्ण

	list_क्रम_each_entry(sas_device, &ioc->sas_device_init_list, list) अणु
		अगर (sas_device->sas_address != sas_address)
			जारी;
		अगर (sas_device->port != port)
			जारी;
		sas_device_get(sas_device);
		वापस sas_device;
	पूर्ण

	वापस शून्य;
पूर्ण

/**
 * mpt3sas_get_sdev_by_addr - sas device search
 * @ioc: per adapter object
 * @sas_address: sas address
 * @port: hba port entry
 * Context: Calling function should acquire ioc->sas_device_lock
 *
 * This searches क्रम sas_device based on sas_address & port number,
 * then वापस sas_device object.
 */
काष्ठा _sas_device *
mpt3sas_get_sdev_by_addr(काष्ठा MPT3SAS_ADAPTER *ioc,
	u64 sas_address, काष्ठा hba_port *port)
अणु
	काष्ठा _sas_device *sas_device;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ioc->sas_device_lock, flags);
	sas_device = __mpt3sas_get_sdev_by_addr(ioc,
	    sas_address, port);
	spin_unlock_irqrestore(&ioc->sas_device_lock, flags);

	वापस sas_device;
पूर्ण

अटल काष्ठा _sas_device *
__mpt3sas_get_sdev_by_handle(काष्ठा MPT3SAS_ADAPTER *ioc, u16 handle)
अणु
	काष्ठा _sas_device *sas_device;

	निश्चित_spin_locked(&ioc->sas_device_lock);

	list_क्रम_each_entry(sas_device, &ioc->sas_device_list, list)
		अगर (sas_device->handle == handle)
			जाओ found_device;

	list_क्रम_each_entry(sas_device, &ioc->sas_device_init_list, list)
		अगर (sas_device->handle == handle)
			जाओ found_device;

	वापस शून्य;

found_device:
	sas_device_get(sas_device);
	वापस sas_device;
पूर्ण

/**
 * mpt3sas_get_sdev_by_handle - sas device search
 * @ioc: per adapter object
 * @handle: sas device handle (asचिन्हित by firmware)
 * Context: Calling function should acquire ioc->sas_device_lock
 *
 * This searches क्रम sas_device based on sas_address, then वापस sas_device
 * object.
 */
काष्ठा _sas_device *
mpt3sas_get_sdev_by_handle(काष्ठा MPT3SAS_ADAPTER *ioc, u16 handle)
अणु
	काष्ठा _sas_device *sas_device;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ioc->sas_device_lock, flags);
	sas_device = __mpt3sas_get_sdev_by_handle(ioc, handle);
	spin_unlock_irqrestore(&ioc->sas_device_lock, flags);

	वापस sas_device;
पूर्ण

/**
 * _scsih_display_enclosure_chassis_info - display device location info
 * @ioc: per adapter object
 * @sas_device: per sas device object
 * @sdev: scsi device काष्ठा
 * @starget: scsi target काष्ठा
 */
अटल व्योम
_scsih_display_enclosure_chassis_info(काष्ठा MPT3SAS_ADAPTER *ioc,
	काष्ठा _sas_device *sas_device, काष्ठा scsi_device *sdev,
	काष्ठा scsi_target *starget)
अणु
	अगर (sdev) अणु
		अगर (sas_device->enclosure_handle != 0)
			sdev_prपूर्णांकk(KERN_INFO, sdev,
			    "enclosure logical id (0x%016llx), slot(%d) \n",
			    (अचिन्हित दीर्घ दीर्घ)
			    sas_device->enclosure_logical_id,
			    sas_device->slot);
		अगर (sas_device->connector_name[0] != '\0')
			sdev_prपूर्णांकk(KERN_INFO, sdev,
			    "enclosure level(0x%04x), connector name( %s)\n",
			    sas_device->enclosure_level,
			    sas_device->connector_name);
		अगर (sas_device->is_chassis_slot_valid)
			sdev_prपूर्णांकk(KERN_INFO, sdev, "chassis slot(0x%04x)\n",
			    sas_device->chassis_slot);
	पूर्ण अन्यथा अगर (starget) अणु
		अगर (sas_device->enclosure_handle != 0)
			starget_prपूर्णांकk(KERN_INFO, starget,
			    "enclosure logical id(0x%016llx), slot(%d) \n",
			    (अचिन्हित दीर्घ दीर्घ)
			    sas_device->enclosure_logical_id,
			    sas_device->slot);
		अगर (sas_device->connector_name[0] != '\0')
			starget_prपूर्णांकk(KERN_INFO, starget,
			    "enclosure level(0x%04x), connector name( %s)\n",
			    sas_device->enclosure_level,
			    sas_device->connector_name);
		अगर (sas_device->is_chassis_slot_valid)
			starget_prपूर्णांकk(KERN_INFO, starget,
			    "chassis slot(0x%04x)\n",
			    sas_device->chassis_slot);
	पूर्ण अन्यथा अणु
		अगर (sas_device->enclosure_handle != 0)
			ioc_info(ioc, "enclosure logical id(0x%016llx), slot(%d)\n",
				 (u64)sas_device->enclosure_logical_id,
				 sas_device->slot);
		अगर (sas_device->connector_name[0] != '\0')
			ioc_info(ioc, "enclosure level(0x%04x), connector name( %s)\n",
				 sas_device->enclosure_level,
				 sas_device->connector_name);
		अगर (sas_device->is_chassis_slot_valid)
			ioc_info(ioc, "chassis slot(0x%04x)\n",
				 sas_device->chassis_slot);
	पूर्ण
पूर्ण

/**
 * _scsih_sas_device_हटाओ - हटाओ sas_device from list.
 * @ioc: per adapter object
 * @sas_device: the sas_device object
 * Context: This function will acquire ioc->sas_device_lock.
 *
 * If sas_device is on the list, हटाओ it and decrement its reference count.
 */
अटल व्योम
_scsih_sas_device_हटाओ(काष्ठा MPT3SAS_ADAPTER *ioc,
	काष्ठा _sas_device *sas_device)
अणु
	अचिन्हित दीर्घ flags;

	अगर (!sas_device)
		वापस;
	ioc_info(ioc, "removing handle(0x%04x), sas_addr(0x%016llx)\n",
		 sas_device->handle, (u64)sas_device->sas_address);

	_scsih_display_enclosure_chassis_info(ioc, sas_device, शून्य, शून्य);

	/*
	 * The lock serializes access to the list, but we still need to verअगरy
	 * that nobody हटाओd the entry जबतक we were रुकोing on the lock.
	 */
	spin_lock_irqsave(&ioc->sas_device_lock, flags);
	अगर (!list_empty(&sas_device->list)) अणु
		list_del_init(&sas_device->list);
		sas_device_put(sas_device);
	पूर्ण
	spin_unlock_irqrestore(&ioc->sas_device_lock, flags);
पूर्ण

/**
 * _scsih_device_हटाओ_by_handle - removing device object by handle
 * @ioc: per adapter object
 * @handle: device handle
 */
अटल व्योम
_scsih_device_हटाओ_by_handle(काष्ठा MPT3SAS_ADAPTER *ioc, u16 handle)
अणु
	काष्ठा _sas_device *sas_device;
	अचिन्हित दीर्घ flags;

	अगर (ioc->shost_recovery)
		वापस;

	spin_lock_irqsave(&ioc->sas_device_lock, flags);
	sas_device = __mpt3sas_get_sdev_by_handle(ioc, handle);
	अगर (sas_device) अणु
		list_del_init(&sas_device->list);
		sas_device_put(sas_device);
	पूर्ण
	spin_unlock_irqrestore(&ioc->sas_device_lock, flags);
	अगर (sas_device) अणु
		_scsih_हटाओ_device(ioc, sas_device);
		sas_device_put(sas_device);
	पूर्ण
पूर्ण

/**
 * mpt3sas_device_हटाओ_by_sas_address - removing device object by
 *					sas address & port number
 * @ioc: per adapter object
 * @sas_address: device sas_address
 * @port: hba port entry
 *
 * Return nothing.
 */
व्योम
mpt3sas_device_हटाओ_by_sas_address(काष्ठा MPT3SAS_ADAPTER *ioc,
	u64 sas_address, काष्ठा hba_port *port)
अणु
	काष्ठा _sas_device *sas_device;
	अचिन्हित दीर्घ flags;

	अगर (ioc->shost_recovery)
		वापस;

	spin_lock_irqsave(&ioc->sas_device_lock, flags);
	sas_device = __mpt3sas_get_sdev_by_addr(ioc, sas_address, port);
	अगर (sas_device) अणु
		list_del_init(&sas_device->list);
		sas_device_put(sas_device);
	पूर्ण
	spin_unlock_irqrestore(&ioc->sas_device_lock, flags);
	अगर (sas_device) अणु
		_scsih_हटाओ_device(ioc, sas_device);
		sas_device_put(sas_device);
	पूर्ण
पूर्ण

/**
 * _scsih_sas_device_add - insert sas_device to the list.
 * @ioc: per adapter object
 * @sas_device: the sas_device object
 * Context: This function will acquire ioc->sas_device_lock.
 *
 * Adding new object to the ioc->sas_device_list.
 */
अटल व्योम
_scsih_sas_device_add(काष्ठा MPT3SAS_ADAPTER *ioc,
	काष्ठा _sas_device *sas_device)
अणु
	अचिन्हित दीर्घ flags;

	dewtprपूर्णांकk(ioc,
		   ioc_info(ioc, "%s: handle(0x%04x), sas_addr(0x%016llx)\n",
			    __func__, sas_device->handle,
			    (u64)sas_device->sas_address));

	dewtprपूर्णांकk(ioc, _scsih_display_enclosure_chassis_info(ioc, sas_device,
	    शून्य, शून्य));

	spin_lock_irqsave(&ioc->sas_device_lock, flags);
	sas_device_get(sas_device);
	list_add_tail(&sas_device->list, &ioc->sas_device_list);
	spin_unlock_irqrestore(&ioc->sas_device_lock, flags);

	अगर (ioc->hide_drives) अणु
		clear_bit(sas_device->handle, ioc->pend_os_device_add);
		वापस;
	पूर्ण

	अगर (!mpt3sas_transport_port_add(ioc, sas_device->handle,
	     sas_device->sas_address_parent, sas_device->port)) अणु
		_scsih_sas_device_हटाओ(ioc, sas_device);
	पूर्ण अन्यथा अगर (!sas_device->starget) अणु
		/*
		 * When asyn scanning is enabled, its not possible to हटाओ
		 * devices जबतक scanning is turned on due to an oops in
		 * scsi_sysfs_add_sdev()->add_device()->sysfs_addrm_start()
		 */
		अगर (!ioc->is_driver_loading) अणु
			mpt3sas_transport_port_हटाओ(ioc,
			    sas_device->sas_address,
			    sas_device->sas_address_parent,
			    sas_device->port);
			_scsih_sas_device_हटाओ(ioc, sas_device);
		पूर्ण
	पूर्ण अन्यथा
		clear_bit(sas_device->handle, ioc->pend_os_device_add);
पूर्ण

/**
 * _scsih_sas_device_init_add - insert sas_device to the list.
 * @ioc: per adapter object
 * @sas_device: the sas_device object
 * Context: This function will acquire ioc->sas_device_lock.
 *
 * Adding new object at driver load समय to the ioc->sas_device_init_list.
 */
अटल व्योम
_scsih_sas_device_init_add(काष्ठा MPT3SAS_ADAPTER *ioc,
	काष्ठा _sas_device *sas_device)
अणु
	अचिन्हित दीर्घ flags;

	dewtprपूर्णांकk(ioc,
		   ioc_info(ioc, "%s: handle(0x%04x), sas_addr(0x%016llx)\n",
			    __func__, sas_device->handle,
			    (u64)sas_device->sas_address));

	dewtprपूर्णांकk(ioc, _scsih_display_enclosure_chassis_info(ioc, sas_device,
	    शून्य, शून्य));

	spin_lock_irqsave(&ioc->sas_device_lock, flags);
	sas_device_get(sas_device);
	list_add_tail(&sas_device->list, &ioc->sas_device_init_list);
	_scsih_determine_boot_device(ioc, sas_device, 0);
	spin_unlock_irqrestore(&ioc->sas_device_lock, flags);
पूर्ण


अटल काष्ठा _pcie_device *
__mpt3sas_get_pdev_by_wwid(काष्ठा MPT3SAS_ADAPTER *ioc, u64 wwid)
अणु
	काष्ठा _pcie_device *pcie_device;

	निश्चित_spin_locked(&ioc->pcie_device_lock);

	list_क्रम_each_entry(pcie_device, &ioc->pcie_device_list, list)
		अगर (pcie_device->wwid == wwid)
			जाओ found_device;

	list_क्रम_each_entry(pcie_device, &ioc->pcie_device_init_list, list)
		अगर (pcie_device->wwid == wwid)
			जाओ found_device;

	वापस शून्य;

found_device:
	pcie_device_get(pcie_device);
	वापस pcie_device;
पूर्ण


/**
 * mpt3sas_get_pdev_by_wwid - pcie device search
 * @ioc: per adapter object
 * @wwid: wwid
 *
 * Context: This function will acquire ioc->pcie_device_lock and will release
 * beक्रमe वापसing the pcie_device object.
 *
 * This searches क्रम pcie_device based on wwid, then वापस pcie_device object.
 */
अटल काष्ठा _pcie_device *
mpt3sas_get_pdev_by_wwid(काष्ठा MPT3SAS_ADAPTER *ioc, u64 wwid)
अणु
	काष्ठा _pcie_device *pcie_device;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ioc->pcie_device_lock, flags);
	pcie_device = __mpt3sas_get_pdev_by_wwid(ioc, wwid);
	spin_unlock_irqrestore(&ioc->pcie_device_lock, flags);

	वापस pcie_device;
पूर्ण


अटल काष्ठा _pcie_device *
__mpt3sas_get_pdev_by_idchannel(काष्ठा MPT3SAS_ADAPTER *ioc, पूर्णांक id,
	पूर्णांक channel)
अणु
	काष्ठा _pcie_device *pcie_device;

	निश्चित_spin_locked(&ioc->pcie_device_lock);

	list_क्रम_each_entry(pcie_device, &ioc->pcie_device_list, list)
		अगर (pcie_device->id == id && pcie_device->channel == channel)
			जाओ found_device;

	list_क्रम_each_entry(pcie_device, &ioc->pcie_device_init_list, list)
		अगर (pcie_device->id == id && pcie_device->channel == channel)
			जाओ found_device;

	वापस शून्य;

found_device:
	pcie_device_get(pcie_device);
	वापस pcie_device;
पूर्ण

अटल काष्ठा _pcie_device *
__mpt3sas_get_pdev_by_handle(काष्ठा MPT3SAS_ADAPTER *ioc, u16 handle)
अणु
	काष्ठा _pcie_device *pcie_device;

	निश्चित_spin_locked(&ioc->pcie_device_lock);

	list_क्रम_each_entry(pcie_device, &ioc->pcie_device_list, list)
		अगर (pcie_device->handle == handle)
			जाओ found_device;

	list_क्रम_each_entry(pcie_device, &ioc->pcie_device_init_list, list)
		अगर (pcie_device->handle == handle)
			जाओ found_device;

	वापस शून्य;

found_device:
	pcie_device_get(pcie_device);
	वापस pcie_device;
पूर्ण


/**
 * mpt3sas_get_pdev_by_handle - pcie device search
 * @ioc: per adapter object
 * @handle: Firmware device handle
 *
 * Context: This function will acquire ioc->pcie_device_lock and will release
 * beक्रमe वापसing the pcie_device object.
 *
 * This searches क्रम pcie_device based on handle, then वापस pcie_device
 * object.
 */
काष्ठा _pcie_device *
mpt3sas_get_pdev_by_handle(काष्ठा MPT3SAS_ADAPTER *ioc, u16 handle)
अणु
	काष्ठा _pcie_device *pcie_device;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ioc->pcie_device_lock, flags);
	pcie_device = __mpt3sas_get_pdev_by_handle(ioc, handle);
	spin_unlock_irqrestore(&ioc->pcie_device_lock, flags);

	वापस pcie_device;
पूर्ण

/**
 * _scsih_set_nvme_max_shutकरोwn_latency - Update max_shutकरोwn_latency.
 * @ioc: per adapter object
 * Context: This function will acquire ioc->pcie_device_lock
 *
 * Update ioc->max_shutकरोwn_latency to that NVMe drives RTD3 Entry Latency
 * which has reported maximum among all available NVMe drives.
 * Minimum max_shutकरोwn_latency will be six seconds.
 */
अटल व्योम
_scsih_set_nvme_max_shutकरोwn_latency(काष्ठा MPT3SAS_ADAPTER *ioc)
अणु
	काष्ठा _pcie_device *pcie_device;
	अचिन्हित दीर्घ flags;
	u16 shutकरोwn_latency = IO_UNIT_CONTROL_SHUTDOWN_TIMEOUT;

	spin_lock_irqsave(&ioc->pcie_device_lock, flags);
	list_क्रम_each_entry(pcie_device, &ioc->pcie_device_list, list) अणु
		अगर (pcie_device->shutकरोwn_latency) अणु
			अगर (shutकरोwn_latency < pcie_device->shutकरोwn_latency)
				shutकरोwn_latency =
					pcie_device->shutकरोwn_latency;
		पूर्ण
	पूर्ण
	ioc->max_shutकरोwn_latency = shutकरोwn_latency;
	spin_unlock_irqrestore(&ioc->pcie_device_lock, flags);
पूर्ण

/**
 * _scsih_pcie_device_हटाओ - हटाओ pcie_device from list.
 * @ioc: per adapter object
 * @pcie_device: the pcie_device object
 * Context: This function will acquire ioc->pcie_device_lock.
 *
 * If pcie_device is on the list, हटाओ it and decrement its reference count.
 */
अटल व्योम
_scsih_pcie_device_हटाओ(काष्ठा MPT3SAS_ADAPTER *ioc,
	काष्ठा _pcie_device *pcie_device)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक was_on_pcie_device_list = 0;
	u8 update_latency = 0;

	अगर (!pcie_device)
		वापस;
	ioc_info(ioc, "removing handle(0x%04x), wwid(0x%016llx)\n",
		 pcie_device->handle, (u64)pcie_device->wwid);
	अगर (pcie_device->enclosure_handle != 0)
		ioc_info(ioc, "removing enclosure logical id(0x%016llx), slot(%d)\n",
			 (u64)pcie_device->enclosure_logical_id,
			 pcie_device->slot);
	अगर (pcie_device->connector_name[0] != '\0')
		ioc_info(ioc, "removing enclosure level(0x%04x), connector name( %s)\n",
			 pcie_device->enclosure_level,
			 pcie_device->connector_name);

	spin_lock_irqsave(&ioc->pcie_device_lock, flags);
	अगर (!list_empty(&pcie_device->list)) अणु
		list_del_init(&pcie_device->list);
		was_on_pcie_device_list = 1;
	पूर्ण
	अगर (pcie_device->shutकरोwn_latency == ioc->max_shutकरोwn_latency)
		update_latency = 1;
	spin_unlock_irqrestore(&ioc->pcie_device_lock, flags);
	अगर (was_on_pcie_device_list) अणु
		kमुक्त(pcie_device->serial_number);
		pcie_device_put(pcie_device);
	पूर्ण

	/*
	 * This device's RTD3 Entry Latency matches IOC's
	 * max_shutकरोwn_latency. Recalculate IOC's max_shutकरोwn_latency
	 * from the available drives as current drive is getting हटाओd.
	 */
	अगर (update_latency)
		_scsih_set_nvme_max_shutकरोwn_latency(ioc);
पूर्ण


/**
 * _scsih_pcie_device_हटाओ_by_handle - removing pcie device object by handle
 * @ioc: per adapter object
 * @handle: device handle
 */
अटल व्योम
_scsih_pcie_device_हटाओ_by_handle(काष्ठा MPT3SAS_ADAPTER *ioc, u16 handle)
अणु
	काष्ठा _pcie_device *pcie_device;
	अचिन्हित दीर्घ flags;
	पूर्णांक was_on_pcie_device_list = 0;
	u8 update_latency = 0;

	अगर (ioc->shost_recovery)
		वापस;

	spin_lock_irqsave(&ioc->pcie_device_lock, flags);
	pcie_device = __mpt3sas_get_pdev_by_handle(ioc, handle);
	अगर (pcie_device) अणु
		अगर (!list_empty(&pcie_device->list)) अणु
			list_del_init(&pcie_device->list);
			was_on_pcie_device_list = 1;
			pcie_device_put(pcie_device);
		पूर्ण
		अगर (pcie_device->shutकरोwn_latency == ioc->max_shutकरोwn_latency)
			update_latency = 1;
	पूर्ण
	spin_unlock_irqrestore(&ioc->pcie_device_lock, flags);
	अगर (was_on_pcie_device_list) अणु
		_scsih_pcie_device_हटाओ_from_sml(ioc, pcie_device);
		pcie_device_put(pcie_device);
	पूर्ण

	/*
	 * This device's RTD3 Entry Latency matches IOC's
	 * max_shutकरोwn_latency. Recalculate IOC's max_shutकरोwn_latency
	 * from the available drives as current drive is getting हटाओd.
	 */
	अगर (update_latency)
		_scsih_set_nvme_max_shutकरोwn_latency(ioc);
पूर्ण

/**
 * _scsih_pcie_device_add - add pcie_device object
 * @ioc: per adapter object
 * @pcie_device: pcie_device object
 *
 * This is added to the pcie_device_list link list.
 */
अटल व्योम
_scsih_pcie_device_add(काष्ठा MPT3SAS_ADAPTER *ioc,
	काष्ठा _pcie_device *pcie_device)
अणु
	अचिन्हित दीर्घ flags;

	dewtprपूर्णांकk(ioc,
		   ioc_info(ioc, "%s: handle (0x%04x), wwid(0x%016llx)\n",
			    __func__,
			    pcie_device->handle, (u64)pcie_device->wwid));
	अगर (pcie_device->enclosure_handle != 0)
		dewtprपूर्णांकk(ioc,
			   ioc_info(ioc, "%s: enclosure logical id(0x%016llx), slot( %d)\n",
				    __func__,
				    (u64)pcie_device->enclosure_logical_id,
				    pcie_device->slot));
	अगर (pcie_device->connector_name[0] != '\0')
		dewtprपूर्णांकk(ioc,
			   ioc_info(ioc, "%s: enclosure level(0x%04x), connector name( %s)\n",
				    __func__, pcie_device->enclosure_level,
				    pcie_device->connector_name));

	spin_lock_irqsave(&ioc->pcie_device_lock, flags);
	pcie_device_get(pcie_device);
	list_add_tail(&pcie_device->list, &ioc->pcie_device_list);
	spin_unlock_irqrestore(&ioc->pcie_device_lock, flags);

	अगर (pcie_device->access_status ==
	    MPI26_PCIEDEV0_ASTATUS_DEVICE_BLOCKED) अणु
		clear_bit(pcie_device->handle, ioc->pend_os_device_add);
		वापस;
	पूर्ण
	अगर (scsi_add_device(ioc->shost, PCIE_CHANNEL, pcie_device->id, 0)) अणु
		_scsih_pcie_device_हटाओ(ioc, pcie_device);
	पूर्ण अन्यथा अगर (!pcie_device->starget) अणु
		अगर (!ioc->is_driver_loading) अणु
/*TODO-- Need to find out whether this condition will occur or not*/
			clear_bit(pcie_device->handle, ioc->pend_os_device_add);
		पूर्ण
	पूर्ण अन्यथा
		clear_bit(pcie_device->handle, ioc->pend_os_device_add);
पूर्ण

/*
 * _scsih_pcie_device_init_add - insert pcie_device to the init list.
 * @ioc: per adapter object
 * @pcie_device: the pcie_device object
 * Context: This function will acquire ioc->pcie_device_lock.
 *
 * Adding new object at driver load समय to the ioc->pcie_device_init_list.
 */
अटल व्योम
_scsih_pcie_device_init_add(काष्ठा MPT3SAS_ADAPTER *ioc,
				काष्ठा _pcie_device *pcie_device)
अणु
	अचिन्हित दीर्घ flags;

	dewtprपूर्णांकk(ioc,
		   ioc_info(ioc, "%s: handle (0x%04x), wwid(0x%016llx)\n",
			    __func__,
			    pcie_device->handle, (u64)pcie_device->wwid));
	अगर (pcie_device->enclosure_handle != 0)
		dewtprपूर्णांकk(ioc,
			   ioc_info(ioc, "%s: enclosure logical id(0x%016llx), slot( %d)\n",
				    __func__,
				    (u64)pcie_device->enclosure_logical_id,
				    pcie_device->slot));
	अगर (pcie_device->connector_name[0] != '\0')
		dewtprपूर्णांकk(ioc,
			   ioc_info(ioc, "%s: enclosure level(0x%04x), connector name( %s)\n",
				    __func__, pcie_device->enclosure_level,
				    pcie_device->connector_name));

	spin_lock_irqsave(&ioc->pcie_device_lock, flags);
	pcie_device_get(pcie_device);
	list_add_tail(&pcie_device->list, &ioc->pcie_device_init_list);
	अगर (pcie_device->access_status !=
	    MPI26_PCIEDEV0_ASTATUS_DEVICE_BLOCKED)
		_scsih_determine_boot_device(ioc, pcie_device, PCIE_CHANNEL);
	spin_unlock_irqrestore(&ioc->pcie_device_lock, flags);
पूर्ण
/**
 * _scsih_raid_device_find_by_id - raid device search
 * @ioc: per adapter object
 * @id: sas device target id
 * @channel: sas device channel
 * Context: Calling function should acquire ioc->raid_device_lock
 *
 * This searches क्रम raid_device based on target id, then वापस raid_device
 * object.
 */
अटल काष्ठा _raid_device *
_scsih_raid_device_find_by_id(काष्ठा MPT3SAS_ADAPTER *ioc, पूर्णांक id, पूर्णांक channel)
अणु
	काष्ठा _raid_device *raid_device, *r;

	r = शून्य;
	list_क्रम_each_entry(raid_device, &ioc->raid_device_list, list) अणु
		अगर (raid_device->id == id && raid_device->channel == channel) अणु
			r = raid_device;
			जाओ out;
		पूर्ण
	पूर्ण

 out:
	वापस r;
पूर्ण

/**
 * mpt3sas_raid_device_find_by_handle - raid device search
 * @ioc: per adapter object
 * @handle: sas device handle (asचिन्हित by firmware)
 * Context: Calling function should acquire ioc->raid_device_lock
 *
 * This searches क्रम raid_device based on handle, then वापस raid_device
 * object.
 */
काष्ठा _raid_device *
mpt3sas_raid_device_find_by_handle(काष्ठा MPT3SAS_ADAPTER *ioc, u16 handle)
अणु
	काष्ठा _raid_device *raid_device, *r;

	r = शून्य;
	list_क्रम_each_entry(raid_device, &ioc->raid_device_list, list) अणु
		अगर (raid_device->handle != handle)
			जारी;
		r = raid_device;
		जाओ out;
	पूर्ण

 out:
	वापस r;
पूर्ण

/**
 * _scsih_raid_device_find_by_wwid - raid device search
 * @ioc: per adapter object
 * @wwid: ?
 * Context: Calling function should acquire ioc->raid_device_lock
 *
 * This searches क्रम raid_device based on wwid, then वापस raid_device
 * object.
 */
अटल काष्ठा _raid_device *
_scsih_raid_device_find_by_wwid(काष्ठा MPT3SAS_ADAPTER *ioc, u64 wwid)
अणु
	काष्ठा _raid_device *raid_device, *r;

	r = शून्य;
	list_क्रम_each_entry(raid_device, &ioc->raid_device_list, list) अणु
		अगर (raid_device->wwid != wwid)
			जारी;
		r = raid_device;
		जाओ out;
	पूर्ण

 out:
	वापस r;
पूर्ण

/**
 * _scsih_raid_device_add - add raid_device object
 * @ioc: per adapter object
 * @raid_device: raid_device object
 *
 * This is added to the raid_device_list link list.
 */
अटल व्योम
_scsih_raid_device_add(काष्ठा MPT3SAS_ADAPTER *ioc,
	काष्ठा _raid_device *raid_device)
अणु
	अचिन्हित दीर्घ flags;

	dewtprपूर्णांकk(ioc,
		   ioc_info(ioc, "%s: handle(0x%04x), wwid(0x%016llx)\n",
			    __func__,
			    raid_device->handle, (u64)raid_device->wwid));

	spin_lock_irqsave(&ioc->raid_device_lock, flags);
	list_add_tail(&raid_device->list, &ioc->raid_device_list);
	spin_unlock_irqrestore(&ioc->raid_device_lock, flags);
पूर्ण

/**
 * _scsih_raid_device_हटाओ - delete raid_device object
 * @ioc: per adapter object
 * @raid_device: raid_device object
 *
 */
अटल व्योम
_scsih_raid_device_हटाओ(काष्ठा MPT3SAS_ADAPTER *ioc,
	काष्ठा _raid_device *raid_device)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ioc->raid_device_lock, flags);
	list_del(&raid_device->list);
	kमुक्त(raid_device);
	spin_unlock_irqrestore(&ioc->raid_device_lock, flags);
पूर्ण

/**
 * mpt3sas_scsih_expander_find_by_handle - expander device search
 * @ioc: per adapter object
 * @handle: expander handle (asचिन्हित by firmware)
 * Context: Calling function should acquire ioc->sas_device_lock
 *
 * This searches क्रम expander device based on handle, then वापसs the
 * sas_node object.
 */
काष्ठा _sas_node *
mpt3sas_scsih_expander_find_by_handle(काष्ठा MPT3SAS_ADAPTER *ioc, u16 handle)
अणु
	काष्ठा _sas_node *sas_expander, *r;

	r = शून्य;
	list_क्रम_each_entry(sas_expander, &ioc->sas_expander_list, list) अणु
		अगर (sas_expander->handle != handle)
			जारी;
		r = sas_expander;
		जाओ out;
	पूर्ण
 out:
	वापस r;
पूर्ण

/**
 * mpt3sas_scsih_enclosure_find_by_handle - exclosure device search
 * @ioc: per adapter object
 * @handle: enclosure handle (asचिन्हित by firmware)
 * Context: Calling function should acquire ioc->sas_device_lock
 *
 * This searches क्रम enclosure device based on handle, then वापसs the
 * enclosure object.
 */
अटल काष्ठा _enclosure_node *
mpt3sas_scsih_enclosure_find_by_handle(काष्ठा MPT3SAS_ADAPTER *ioc, u16 handle)
अणु
	काष्ठा _enclosure_node *enclosure_dev, *r;

	r = शून्य;
	list_क्रम_each_entry(enclosure_dev, &ioc->enclosure_list, list) अणु
		अगर (le16_to_cpu(enclosure_dev->pg0.EnclosureHandle) != handle)
			जारी;
		r = enclosure_dev;
		जाओ out;
	पूर्ण
out:
	वापस r;
पूर्ण
/**
 * mpt3sas_scsih_expander_find_by_sas_address - expander device search
 * @ioc: per adapter object
 * @sas_address: sas address
 * @port: hba port entry
 * Context: Calling function should acquire ioc->sas_node_lock.
 *
 * This searches क्रम expander device based on sas_address & port number,
 * then वापसs the sas_node object.
 */
काष्ठा _sas_node *
mpt3sas_scsih_expander_find_by_sas_address(काष्ठा MPT3SAS_ADAPTER *ioc,
	u64 sas_address, काष्ठा hba_port *port)
अणु
	काष्ठा _sas_node *sas_expander, *r = शून्य;

	अगर (!port)
		वापस r;

	list_क्रम_each_entry(sas_expander, &ioc->sas_expander_list, list) अणु
		अगर (sas_expander->sas_address != sas_address)
			जारी;
		अगर (sas_expander->port != port)
			जारी;
		r = sas_expander;
		जाओ out;
	पूर्ण
 out:
	वापस r;
पूर्ण

/**
 * _scsih_expander_node_add - insert expander device to the list.
 * @ioc: per adapter object
 * @sas_expander: the sas_device object
 * Context: This function will acquire ioc->sas_node_lock.
 *
 * Adding new object to the ioc->sas_expander_list.
 */
अटल व्योम
_scsih_expander_node_add(काष्ठा MPT3SAS_ADAPTER *ioc,
	काष्ठा _sas_node *sas_expander)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ioc->sas_node_lock, flags);
	list_add_tail(&sas_expander->list, &ioc->sas_expander_list);
	spin_unlock_irqrestore(&ioc->sas_node_lock, flags);
पूर्ण

/**
 * _scsih_is_end_device - determines अगर device is an end device
 * @device_info: bitfield providing inक्रमmation about the device.
 * Context: none
 *
 * Return: 1 अगर end device.
 */
अटल पूर्णांक
_scsih_is_end_device(u32 device_info)
अणु
	अगर (device_info & MPI2_SAS_DEVICE_INFO_END_DEVICE &&
		((device_info & MPI2_SAS_DEVICE_INFO_SSP_TARGET) |
		(device_info & MPI2_SAS_DEVICE_INFO_STP_TARGET) |
		(device_info & MPI2_SAS_DEVICE_INFO_SATA_DEVICE)))
		वापस 1;
	अन्यथा
		वापस 0;
पूर्ण

/**
 * _scsih_is_nvme_pciescsi_device - determines अगर
 *			device is an pcie nvme/scsi device
 * @device_info: bitfield providing inक्रमmation about the device.
 * Context: none
 *
 * Returns 1 अगर device is pcie device type nvme/scsi.
 */
अटल पूर्णांक
_scsih_is_nvme_pciescsi_device(u32 device_info)
अणु
	अगर (((device_info & MPI26_PCIE_DEVINFO_MASK_DEVICE_TYPE)
	    == MPI26_PCIE_DEVINFO_NVME) ||
	    ((device_info & MPI26_PCIE_DEVINFO_MASK_DEVICE_TYPE)
	    == MPI26_PCIE_DEVINFO_SCSI))
		वापस 1;
	अन्यथा
		वापस 0;
पूर्ण

/**
 * _scsih_scsi_lookup_find_by_target - search क्रम matching channel:id
 * @ioc: per adapter object
 * @id: target id
 * @channel: channel
 * Context: This function will acquire ioc->scsi_lookup_lock.
 *
 * This will search क्रम a matching channel:id in the scsi_lookup array,
 * वापसing 1 अगर found.
 */
अटल u8
_scsih_scsi_lookup_find_by_target(काष्ठा MPT3SAS_ADAPTER *ioc, पूर्णांक id,
	पूर्णांक channel)
अणु
	पूर्णांक smid;
	काष्ठा scsi_cmnd *scmd;

	क्रम (smid = 1;
	     smid <= ioc->shost->can_queue; smid++) अणु
		scmd = mpt3sas_scsih_scsi_lookup_get(ioc, smid);
		अगर (!scmd)
			जारी;
		अगर (scmd->device->id == id &&
		    scmd->device->channel == channel)
			वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

/**
 * _scsih_scsi_lookup_find_by_lun - search क्रम matching channel:id:lun
 * @ioc: per adapter object
 * @id: target id
 * @lun: lun number
 * @channel: channel
 * Context: This function will acquire ioc->scsi_lookup_lock.
 *
 * This will search क्रम a matching channel:id:lun in the scsi_lookup array,
 * वापसing 1 अगर found.
 */
अटल u8
_scsih_scsi_lookup_find_by_lun(काष्ठा MPT3SAS_ADAPTER *ioc, पूर्णांक id,
	अचिन्हित पूर्णांक lun, पूर्णांक channel)
अणु
	पूर्णांक smid;
	काष्ठा scsi_cmnd *scmd;

	क्रम (smid = 1; smid <= ioc->shost->can_queue; smid++) अणु

		scmd = mpt3sas_scsih_scsi_lookup_get(ioc, smid);
		अगर (!scmd)
			जारी;
		अगर (scmd->device->id == id &&
		    scmd->device->channel == channel &&
		    scmd->device->lun == lun)
			वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

/**
 * mpt3sas_scsih_scsi_lookup_get - वापसs scmd entry
 * @ioc: per adapter object
 * @smid: प्रणाली request message index
 *
 * Return: the smid stored scmd poपूर्णांकer.
 * Then will dereference the stored scmd poपूर्णांकer.
 */
काष्ठा scsi_cmnd *
mpt3sas_scsih_scsi_lookup_get(काष्ठा MPT3SAS_ADAPTER *ioc, u16 smid)
अणु
	काष्ठा scsi_cmnd *scmd = शून्य;
	काष्ठा scsiio_tracker *st;
	Mpi25SCSIIORequest_t *mpi_request;
	u16 tag = smid - 1;

	अगर (smid > 0  &&
	    smid <= ioc->scsiio_depth - INTERNAL_SCSIIO_CMDS_COUNT) अणु
		u32 unique_tag =
		    ioc->io_queue_num[tag] << BLK_MQ_UNIQUE_TAG_BITS | tag;

		mpi_request = mpt3sas_base_get_msg_frame(ioc, smid);

		/*
		 * If SCSI IO request is outstanding at driver level then
		 * DevHandle filed must be non-zero. If DevHandle is zero
		 * then it means that this smid is मुक्त at driver level,
		 * so वापस शून्य.
		 */
		अगर (!mpi_request->DevHandle)
			वापस scmd;

		scmd = scsi_host_find_tag(ioc->shost, unique_tag);
		अगर (scmd) अणु
			st = scsi_cmd_priv(scmd);
			अगर (st->cb_idx == 0xFF || st->smid == 0)
				scmd = शून्य;
		पूर्ण
	पूर्ण
	वापस scmd;
पूर्ण

/**
 * scsih_change_queue_depth - setting device queue depth
 * @sdev: scsi device काष्ठा
 * @qdepth: requested queue depth
 *
 * Return: queue depth.
 */
अटल पूर्णांक
scsih_change_queue_depth(काष्ठा scsi_device *sdev, पूर्णांक qdepth)
अणु
	काष्ठा Scsi_Host *shost = sdev->host;
	पूर्णांक max_depth;
	काष्ठा MPT3SAS_ADAPTER *ioc = shost_priv(shost);
	काष्ठा MPT3SAS_DEVICE *sas_device_priv_data;
	काष्ठा MPT3SAS_TARGET *sas_target_priv_data;
	काष्ठा _sas_device *sas_device;
	अचिन्हित दीर्घ flags;

	max_depth = shost->can_queue;

	/*
	 * limit max device queue क्रम SATA to 32 अगर enable_sdev_max_qd
	 * is disabled.
	 */
	अगर (ioc->enable_sdev_max_qd)
		जाओ not_sata;

	sas_device_priv_data = sdev->hostdata;
	अगर (!sas_device_priv_data)
		जाओ not_sata;
	sas_target_priv_data = sas_device_priv_data->sas_target;
	अगर (!sas_target_priv_data)
		जाओ not_sata;
	अगर ((sas_target_priv_data->flags & MPT_TARGET_FLAGS_VOLUME))
		जाओ not_sata;

	spin_lock_irqsave(&ioc->sas_device_lock, flags);
	sas_device = __mpt3sas_get_sdev_from_target(ioc, sas_target_priv_data);
	अगर (sas_device) अणु
		अगर (sas_device->device_info & MPI2_SAS_DEVICE_INFO_SATA_DEVICE)
			max_depth = MPT3SAS_SATA_QUEUE_DEPTH;

		sas_device_put(sas_device);
	पूर्ण
	spin_unlock_irqrestore(&ioc->sas_device_lock, flags);

 not_sata:

	अगर (!sdev->tagged_supported)
		max_depth = 1;
	अगर (qdepth > max_depth)
		qdepth = max_depth;
	scsi_change_queue_depth(sdev, qdepth);
	sdev_prपूर्णांकk(KERN_INFO, sdev,
	    "qdepth(%d), tagged(%d), scsi_level(%d), cmd_que(%d)\n",
	    sdev->queue_depth, sdev->tagged_supported,
	    sdev->scsi_level, ((sdev->inquiry[7] & 2) >> 1));
	वापस sdev->queue_depth;
पूर्ण

/**
 * mpt3sas_scsih_change_queue_depth - setting device queue depth
 * @sdev: scsi device काष्ठा
 * @qdepth: requested queue depth
 *
 * Returns nothing.
 */
व्योम
mpt3sas_scsih_change_queue_depth(काष्ठा scsi_device *sdev, पूर्णांक qdepth)
अणु
	काष्ठा Scsi_Host *shost = sdev->host;
	काष्ठा MPT3SAS_ADAPTER *ioc = shost_priv(shost);

	अगर (ioc->enable_sdev_max_qd)
		qdepth = shost->can_queue;

	scsih_change_queue_depth(sdev, qdepth);
पूर्ण

/**
 * scsih_target_alloc - target add routine
 * @starget: scsi target काष्ठा
 *
 * Return: 0 अगर ok. Any other वापस is assumed to be an error and
 * the device is ignored.
 */
अटल पूर्णांक
scsih_target_alloc(काष्ठा scsi_target *starget)
अणु
	काष्ठा Scsi_Host *shost = dev_to_shost(&starget->dev);
	काष्ठा MPT3SAS_ADAPTER *ioc = shost_priv(shost);
	काष्ठा MPT3SAS_TARGET *sas_target_priv_data;
	काष्ठा _sas_device *sas_device;
	काष्ठा _raid_device *raid_device;
	काष्ठा _pcie_device *pcie_device;
	अचिन्हित दीर्घ flags;
	काष्ठा sas_rphy *rphy;

	sas_target_priv_data = kzalloc(माप(*sas_target_priv_data),
				       GFP_KERNEL);
	अगर (!sas_target_priv_data)
		वापस -ENOMEM;

	starget->hostdata = sas_target_priv_data;
	sas_target_priv_data->starget = starget;
	sas_target_priv_data->handle = MPT3SAS_INVALID_DEVICE_HANDLE;

	/* RAID volumes */
	अगर (starget->channel == RAID_CHANNEL) अणु
		spin_lock_irqsave(&ioc->raid_device_lock, flags);
		raid_device = _scsih_raid_device_find_by_id(ioc, starget->id,
		    starget->channel);
		अगर (raid_device) अणु
			sas_target_priv_data->handle = raid_device->handle;
			sas_target_priv_data->sas_address = raid_device->wwid;
			sas_target_priv_data->flags |= MPT_TARGET_FLAGS_VOLUME;
			अगर (ioc->is_warpdrive)
				sas_target_priv_data->raid_device = raid_device;
			raid_device->starget = starget;
		पूर्ण
		spin_unlock_irqrestore(&ioc->raid_device_lock, flags);
		वापस 0;
	पूर्ण

	/* PCIe devices */
	अगर (starget->channel == PCIE_CHANNEL) अणु
		spin_lock_irqsave(&ioc->pcie_device_lock, flags);
		pcie_device = __mpt3sas_get_pdev_by_idchannel(ioc, starget->id,
			starget->channel);
		अगर (pcie_device) अणु
			sas_target_priv_data->handle = pcie_device->handle;
			sas_target_priv_data->sas_address = pcie_device->wwid;
			sas_target_priv_data->port = शून्य;
			sas_target_priv_data->pcie_dev = pcie_device;
			pcie_device->starget = starget;
			pcie_device->id = starget->id;
			pcie_device->channel = starget->channel;
			sas_target_priv_data->flags |=
				MPT_TARGET_FLAGS_PCIE_DEVICE;
			अगर (pcie_device->fast_path)
				sas_target_priv_data->flags |=
					MPT_TARGET_FASTPATH_IO;
		पूर्ण
		spin_unlock_irqrestore(&ioc->pcie_device_lock, flags);
		वापस 0;
	पूर्ण

	/* sas/sata devices */
	spin_lock_irqsave(&ioc->sas_device_lock, flags);
	rphy = dev_to_rphy(starget->dev.parent);
	sas_device = __mpt3sas_get_sdev_by_rphy(ioc, rphy);

	अगर (sas_device) अणु
		sas_target_priv_data->handle = sas_device->handle;
		sas_target_priv_data->sas_address = sas_device->sas_address;
		sas_target_priv_data->port = sas_device->port;
		sas_target_priv_data->sas_dev = sas_device;
		sas_device->starget = starget;
		sas_device->id = starget->id;
		sas_device->channel = starget->channel;
		अगर (test_bit(sas_device->handle, ioc->pd_handles))
			sas_target_priv_data->flags |=
			    MPT_TARGET_FLAGS_RAID_COMPONENT;
		अगर (sas_device->fast_path)
			sas_target_priv_data->flags |=
					MPT_TARGET_FASTPATH_IO;
	पूर्ण
	spin_unlock_irqrestore(&ioc->sas_device_lock, flags);

	वापस 0;
पूर्ण

/**
 * scsih_target_destroy - target destroy routine
 * @starget: scsi target काष्ठा
 */
अटल व्योम
scsih_target_destroy(काष्ठा scsi_target *starget)
अणु
	काष्ठा Scsi_Host *shost = dev_to_shost(&starget->dev);
	काष्ठा MPT3SAS_ADAPTER *ioc = shost_priv(shost);
	काष्ठा MPT3SAS_TARGET *sas_target_priv_data;
	काष्ठा _sas_device *sas_device;
	काष्ठा _raid_device *raid_device;
	काष्ठा _pcie_device *pcie_device;
	अचिन्हित दीर्घ flags;

	sas_target_priv_data = starget->hostdata;
	अगर (!sas_target_priv_data)
		वापस;

	अगर (starget->channel == RAID_CHANNEL) अणु
		spin_lock_irqsave(&ioc->raid_device_lock, flags);
		raid_device = _scsih_raid_device_find_by_id(ioc, starget->id,
		    starget->channel);
		अगर (raid_device) अणु
			raid_device->starget = शून्य;
			raid_device->sdev = शून्य;
		पूर्ण
		spin_unlock_irqrestore(&ioc->raid_device_lock, flags);
		जाओ out;
	पूर्ण

	अगर (starget->channel == PCIE_CHANNEL) अणु
		spin_lock_irqsave(&ioc->pcie_device_lock, flags);
		pcie_device = __mpt3sas_get_pdev_from_target(ioc,
							sas_target_priv_data);
		अगर (pcie_device && (pcie_device->starget == starget) &&
			(pcie_device->id == starget->id) &&
			(pcie_device->channel == starget->channel))
			pcie_device->starget = शून्य;

		अगर (pcie_device) अणु
			/*
			 * Corresponding get() is in _scsih_target_alloc()
			 */
			sas_target_priv_data->pcie_dev = शून्य;
			pcie_device_put(pcie_device);
			pcie_device_put(pcie_device);
		पूर्ण
		spin_unlock_irqrestore(&ioc->pcie_device_lock, flags);
		जाओ out;
	पूर्ण

	spin_lock_irqsave(&ioc->sas_device_lock, flags);
	sas_device = __mpt3sas_get_sdev_from_target(ioc, sas_target_priv_data);
	अगर (sas_device && (sas_device->starget == starget) &&
	    (sas_device->id == starget->id) &&
	    (sas_device->channel == starget->channel))
		sas_device->starget = शून्य;

	अगर (sas_device) अणु
		/*
		 * Corresponding get() is in _scsih_target_alloc()
		 */
		sas_target_priv_data->sas_dev = शून्य;
		sas_device_put(sas_device);

		sas_device_put(sas_device);
	पूर्ण
	spin_unlock_irqrestore(&ioc->sas_device_lock, flags);

 out:
	kमुक्त(sas_target_priv_data);
	starget->hostdata = शून्य;
पूर्ण

/**
 * scsih_slave_alloc - device add routine
 * @sdev: scsi device काष्ठा
 *
 * Return: 0 अगर ok. Any other वापस is assumed to be an error and
 * the device is ignored.
 */
अटल पूर्णांक
scsih_slave_alloc(काष्ठा scsi_device *sdev)
अणु
	काष्ठा Scsi_Host *shost;
	काष्ठा MPT3SAS_ADAPTER *ioc;
	काष्ठा MPT3SAS_TARGET *sas_target_priv_data;
	काष्ठा MPT3SAS_DEVICE *sas_device_priv_data;
	काष्ठा scsi_target *starget;
	काष्ठा _raid_device *raid_device;
	काष्ठा _sas_device *sas_device;
	काष्ठा _pcie_device *pcie_device;
	अचिन्हित दीर्घ flags;

	sas_device_priv_data = kzalloc(माप(*sas_device_priv_data),
				       GFP_KERNEL);
	अगर (!sas_device_priv_data)
		वापस -ENOMEM;

	sas_device_priv_data->lun = sdev->lun;
	sas_device_priv_data->flags = MPT_DEVICE_FLAGS_INIT;

	starget = scsi_target(sdev);
	sas_target_priv_data = starget->hostdata;
	sas_target_priv_data->num_luns++;
	sas_device_priv_data->sas_target = sas_target_priv_data;
	sdev->hostdata = sas_device_priv_data;
	अगर ((sas_target_priv_data->flags & MPT_TARGET_FLAGS_RAID_COMPONENT))
		sdev->no_uld_attach = 1;

	shost = dev_to_shost(&starget->dev);
	ioc = shost_priv(shost);
	अगर (starget->channel == RAID_CHANNEL) अणु
		spin_lock_irqsave(&ioc->raid_device_lock, flags);
		raid_device = _scsih_raid_device_find_by_id(ioc,
		    starget->id, starget->channel);
		अगर (raid_device)
			raid_device->sdev = sdev; /* raid is single lun */
		spin_unlock_irqrestore(&ioc->raid_device_lock, flags);
	पूर्ण
	अगर (starget->channel == PCIE_CHANNEL) अणु
		spin_lock_irqsave(&ioc->pcie_device_lock, flags);
		pcie_device = __mpt3sas_get_pdev_by_wwid(ioc,
				sas_target_priv_data->sas_address);
		अगर (pcie_device && (pcie_device->starget == शून्य)) अणु
			sdev_prपूर्णांकk(KERN_INFO, sdev,
			    "%s : pcie_device->starget set to starget @ %d\n",
			    __func__, __LINE__);
			pcie_device->starget = starget;
		पूर्ण

		अगर (pcie_device)
			pcie_device_put(pcie_device);
		spin_unlock_irqrestore(&ioc->pcie_device_lock, flags);

	पूर्ण अन्यथा  अगर (!(sas_target_priv_data->flags & MPT_TARGET_FLAGS_VOLUME)) अणु
		spin_lock_irqsave(&ioc->sas_device_lock, flags);
		sas_device = __mpt3sas_get_sdev_by_addr(ioc,
		    sas_target_priv_data->sas_address,
		    sas_target_priv_data->port);
		अगर (sas_device && (sas_device->starget == शून्य)) अणु
			sdev_prपूर्णांकk(KERN_INFO, sdev,
			"%s : sas_device->starget set to starget @ %d\n",
			     __func__, __LINE__);
			sas_device->starget = starget;
		पूर्ण

		अगर (sas_device)
			sas_device_put(sas_device);

		spin_unlock_irqrestore(&ioc->sas_device_lock, flags);
	पूर्ण

	वापस 0;
पूर्ण

/**
 * scsih_slave_destroy - device destroy routine
 * @sdev: scsi device काष्ठा
 */
अटल व्योम
scsih_slave_destroy(काष्ठा scsi_device *sdev)
अणु
	काष्ठा MPT3SAS_TARGET *sas_target_priv_data;
	काष्ठा scsi_target *starget;
	काष्ठा Scsi_Host *shost;
	काष्ठा MPT3SAS_ADAPTER *ioc;
	काष्ठा _sas_device *sas_device;
	काष्ठा _pcie_device *pcie_device;
	अचिन्हित दीर्घ flags;

	अगर (!sdev->hostdata)
		वापस;

	starget = scsi_target(sdev);
	sas_target_priv_data = starget->hostdata;
	sas_target_priv_data->num_luns--;

	shost = dev_to_shost(&starget->dev);
	ioc = shost_priv(shost);

	अगर (sas_target_priv_data->flags & MPT_TARGET_FLAGS_PCIE_DEVICE) अणु
		spin_lock_irqsave(&ioc->pcie_device_lock, flags);
		pcie_device = __mpt3sas_get_pdev_from_target(ioc,
				sas_target_priv_data);
		अगर (pcie_device && !sas_target_priv_data->num_luns)
			pcie_device->starget = शून्य;

		अगर (pcie_device)
			pcie_device_put(pcie_device);

		spin_unlock_irqrestore(&ioc->pcie_device_lock, flags);

	पूर्ण अन्यथा अगर (!(sas_target_priv_data->flags & MPT_TARGET_FLAGS_VOLUME)) अणु
		spin_lock_irqsave(&ioc->sas_device_lock, flags);
		sas_device = __mpt3sas_get_sdev_from_target(ioc,
				sas_target_priv_data);
		अगर (sas_device && !sas_target_priv_data->num_luns)
			sas_device->starget = शून्य;

		अगर (sas_device)
			sas_device_put(sas_device);
		spin_unlock_irqrestore(&ioc->sas_device_lock, flags);
	पूर्ण

	kमुक्त(sdev->hostdata);
	sdev->hostdata = शून्य;
पूर्ण

/**
 * _scsih_display_sata_capabilities - sata capabilities
 * @ioc: per adapter object
 * @handle: device handle
 * @sdev: scsi device काष्ठा
 */
अटल व्योम
_scsih_display_sata_capabilities(काष्ठा MPT3SAS_ADAPTER *ioc,
	u16 handle, काष्ठा scsi_device *sdev)
अणु
	Mpi2ConfigReply_t mpi_reply;
	Mpi2SasDevicePage0_t sas_device_pg0;
	u32 ioc_status;
	u16 flags;
	u32 device_info;

	अगर ((mpt3sas_config_get_sas_device_pg0(ioc, &mpi_reply, &sas_device_pg0,
	    MPI2_SAS_DEVICE_PGAD_FORM_HANDLE, handle))) अणु
		ioc_err(ioc, "failure at %s:%d/%s()!\n",
			__खाता__, __LINE__, __func__);
		वापस;
	पूर्ण

	ioc_status = le16_to_cpu(mpi_reply.IOCStatus) &
	    MPI2_IOCSTATUS_MASK;
	अगर (ioc_status != MPI2_IOCSTATUS_SUCCESS) अणु
		ioc_err(ioc, "failure at %s:%d/%s()!\n",
			__खाता__, __LINE__, __func__);
		वापस;
	पूर्ण

	flags = le16_to_cpu(sas_device_pg0.Flags);
	device_info = le32_to_cpu(sas_device_pg0.DeviceInfo);

	sdev_prपूर्णांकk(KERN_INFO, sdev,
	    "atapi(%s), ncq(%s), asyn_notify(%s), smart(%s), fua(%s), "
	    "sw_preserve(%s)\n",
	    (device_info & MPI2_SAS_DEVICE_INFO_ATAPI_DEVICE) ? "y" : "n",
	    (flags & MPI2_SAS_DEVICE0_FLAGS_SATA_NCQ_SUPPORTED) ? "y" : "n",
	    (flags & MPI2_SAS_DEVICE0_FLAGS_SATA_ASYNCHRONOUS_NOTIFY) ? "y" :
	    "n",
	    (flags & MPI2_SAS_DEVICE0_FLAGS_SATA_SMART_SUPPORTED) ? "y" : "n",
	    (flags & MPI2_SAS_DEVICE0_FLAGS_SATA_FUA_SUPPORTED) ? "y" : "n",
	    (flags & MPI2_SAS_DEVICE0_FLAGS_SATA_SW_PRESERVE) ? "y" : "n");
पूर्ण

/*
 * raid transport support -
 * Enabled क्रम SLES11 and newer, in older kernels the driver will panic when
 * unloading the driver followed by a load - I believe that the subroutine
 * raid_class_release() is not cleaning up properly.
 */

/**
 * scsih_is_raid - वापस boolean indicating device is raid volume
 * @dev: the device काष्ठा object
 */
अटल पूर्णांक
scsih_is_raid(काष्ठा device *dev)
अणु
	काष्ठा scsi_device *sdev = to_scsi_device(dev);
	काष्ठा MPT3SAS_ADAPTER *ioc = shost_priv(sdev->host);

	अगर (ioc->is_warpdrive)
		वापस 0;
	वापस (sdev->channel == RAID_CHANNEL) ? 1 : 0;
पूर्ण

अटल पूर्णांक
scsih_is_nvme(काष्ठा device *dev)
अणु
	काष्ठा scsi_device *sdev = to_scsi_device(dev);

	वापस (sdev->channel == PCIE_CHANNEL) ? 1 : 0;
पूर्ण

/**
 * scsih_get_resync - get raid volume resync percent complete
 * @dev: the device काष्ठा object
 */
अटल व्योम
scsih_get_resync(काष्ठा device *dev)
अणु
	काष्ठा scsi_device *sdev = to_scsi_device(dev);
	काष्ठा MPT3SAS_ADAPTER *ioc = shost_priv(sdev->host);
	अटल काष्ठा _raid_device *raid_device;
	अचिन्हित दीर्घ flags;
	Mpi2RaidVolPage0_t vol_pg0;
	Mpi2ConfigReply_t mpi_reply;
	u32 volume_status_flags;
	u8 percent_complete;
	u16 handle;

	percent_complete = 0;
	handle = 0;
	अगर (ioc->is_warpdrive)
		जाओ out;

	spin_lock_irqsave(&ioc->raid_device_lock, flags);
	raid_device = _scsih_raid_device_find_by_id(ioc, sdev->id,
	    sdev->channel);
	अगर (raid_device) अणु
		handle = raid_device->handle;
		percent_complete = raid_device->percent_complete;
	पूर्ण
	spin_unlock_irqrestore(&ioc->raid_device_lock, flags);

	अगर (!handle)
		जाओ out;

	अगर (mpt3sas_config_get_raid_volume_pg0(ioc, &mpi_reply, &vol_pg0,
	     MPI2_RAID_VOLUME_PGAD_FORM_HANDLE, handle,
	     माप(Mpi2RaidVolPage0_t))) अणु
		ioc_err(ioc, "failure at %s:%d/%s()!\n",
			__खाता__, __LINE__, __func__);
		percent_complete = 0;
		जाओ out;
	पूर्ण

	volume_status_flags = le32_to_cpu(vol_pg0.VolumeStatusFlags);
	अगर (!(volume_status_flags &
	    MPI2_RAIDVOL0_STATUS_FLAG_RESYNC_IN_PROGRESS))
		percent_complete = 0;

 out:

	चयन (ioc->hba_mpi_version_beदीर्घed) अणु
	हाल MPI2_VERSION:
		raid_set_resync(mpt2sas_raid_ढाँचा, dev, percent_complete);
		अवरोध;
	हाल MPI25_VERSION:
	हाल MPI26_VERSION:
		raid_set_resync(mpt3sas_raid_ढाँचा, dev, percent_complete);
		अवरोध;
	पूर्ण
पूर्ण

/**
 * scsih_get_state - get raid volume level
 * @dev: the device काष्ठा object
 */
अटल व्योम
scsih_get_state(काष्ठा device *dev)
अणु
	काष्ठा scsi_device *sdev = to_scsi_device(dev);
	काष्ठा MPT3SAS_ADAPTER *ioc = shost_priv(sdev->host);
	अटल काष्ठा _raid_device *raid_device;
	अचिन्हित दीर्घ flags;
	Mpi2RaidVolPage0_t vol_pg0;
	Mpi2ConfigReply_t mpi_reply;
	u32 volstate;
	क्रमागत raid_state state = RAID_STATE_UNKNOWN;
	u16 handle = 0;

	spin_lock_irqsave(&ioc->raid_device_lock, flags);
	raid_device = _scsih_raid_device_find_by_id(ioc, sdev->id,
	    sdev->channel);
	अगर (raid_device)
		handle = raid_device->handle;
	spin_unlock_irqrestore(&ioc->raid_device_lock, flags);

	अगर (!raid_device)
		जाओ out;

	अगर (mpt3sas_config_get_raid_volume_pg0(ioc, &mpi_reply, &vol_pg0,
	     MPI2_RAID_VOLUME_PGAD_FORM_HANDLE, handle,
	     माप(Mpi2RaidVolPage0_t))) अणु
		ioc_err(ioc, "failure at %s:%d/%s()!\n",
			__खाता__, __LINE__, __func__);
		जाओ out;
	पूर्ण

	volstate = le32_to_cpu(vol_pg0.VolumeStatusFlags);
	अगर (volstate & MPI2_RAIDVOL0_STATUS_FLAG_RESYNC_IN_PROGRESS) अणु
		state = RAID_STATE_RESYNCING;
		जाओ out;
	पूर्ण

	चयन (vol_pg0.VolumeState) अणु
	हाल MPI2_RAID_VOL_STATE_OPTIMAL:
	हाल MPI2_RAID_VOL_STATE_ONLINE:
		state = RAID_STATE_ACTIVE;
		अवरोध;
	हाल  MPI2_RAID_VOL_STATE_DEGRADED:
		state = RAID_STATE_DEGRADED;
		अवरोध;
	हाल MPI2_RAID_VOL_STATE_FAILED:
	हाल MPI2_RAID_VOL_STATE_MISSING:
		state = RAID_STATE_OFFLINE;
		अवरोध;
	पूर्ण
 out:
	चयन (ioc->hba_mpi_version_beदीर्घed) अणु
	हाल MPI2_VERSION:
		raid_set_state(mpt2sas_raid_ढाँचा, dev, state);
		अवरोध;
	हाल MPI25_VERSION:
	हाल MPI26_VERSION:
		raid_set_state(mpt3sas_raid_ढाँचा, dev, state);
		अवरोध;
	पूर्ण
पूर्ण

/**
 * _scsih_set_level - set raid level
 * @ioc: ?
 * @sdev: scsi device काष्ठा
 * @volume_type: volume type
 */
अटल व्योम
_scsih_set_level(काष्ठा MPT3SAS_ADAPTER *ioc,
	काष्ठा scsi_device *sdev, u8 volume_type)
अणु
	क्रमागत raid_level level = RAID_LEVEL_UNKNOWN;

	चयन (volume_type) अणु
	हाल MPI2_RAID_VOL_TYPE_RAID0:
		level = RAID_LEVEL_0;
		अवरोध;
	हाल MPI2_RAID_VOL_TYPE_RAID10:
		level = RAID_LEVEL_10;
		अवरोध;
	हाल MPI2_RAID_VOL_TYPE_RAID1E:
		level = RAID_LEVEL_1E;
		अवरोध;
	हाल MPI2_RAID_VOL_TYPE_RAID1:
		level = RAID_LEVEL_1;
		अवरोध;
	पूर्ण

	चयन (ioc->hba_mpi_version_beदीर्घed) अणु
	हाल MPI2_VERSION:
		raid_set_level(mpt2sas_raid_ढाँचा,
			&sdev->sdev_gendev, level);
		अवरोध;
	हाल MPI25_VERSION:
	हाल MPI26_VERSION:
		raid_set_level(mpt3sas_raid_ढाँचा,
			&sdev->sdev_gendev, level);
		अवरोध;
	पूर्ण
पूर्ण


/**
 * _scsih_get_volume_capabilities - volume capabilities
 * @ioc: per adapter object
 * @raid_device: the raid_device object
 *
 * Return: 0 क्रम success, अन्यथा 1
 */
अटल पूर्णांक
_scsih_get_volume_capabilities(काष्ठा MPT3SAS_ADAPTER *ioc,
	काष्ठा _raid_device *raid_device)
अणु
	Mpi2RaidVolPage0_t *vol_pg0;
	Mpi2RaidPhysDiskPage0_t pd_pg0;
	Mpi2SasDevicePage0_t sas_device_pg0;
	Mpi2ConfigReply_t mpi_reply;
	u16 sz;
	u8 num_pds;

	अगर ((mpt3sas_config_get_number_pds(ioc, raid_device->handle,
	    &num_pds)) || !num_pds) अणु
		dfailprपूर्णांकk(ioc,
			    ioc_warn(ioc, "failure at %s:%d/%s()!\n",
				     __खाता__, __LINE__, __func__));
		वापस 1;
	पूर्ण

	raid_device->num_pds = num_pds;
	sz = दुरत्व(Mpi2RaidVolPage0_t, PhysDisk) + (num_pds *
	    माप(Mpi2RaidVol0PhysDisk_t));
	vol_pg0 = kzalloc(sz, GFP_KERNEL);
	अगर (!vol_pg0) अणु
		dfailprपूर्णांकk(ioc,
			    ioc_warn(ioc, "failure at %s:%d/%s()!\n",
				     __खाता__, __LINE__, __func__));
		वापस 1;
	पूर्ण

	अगर ((mpt3sas_config_get_raid_volume_pg0(ioc, &mpi_reply, vol_pg0,
	     MPI2_RAID_VOLUME_PGAD_FORM_HANDLE, raid_device->handle, sz))) अणु
		dfailprपूर्णांकk(ioc,
			    ioc_warn(ioc, "failure at %s:%d/%s()!\n",
				     __खाता__, __LINE__, __func__));
		kमुक्त(vol_pg0);
		वापस 1;
	पूर्ण

	raid_device->volume_type = vol_pg0->VolumeType;

	/* figure out what the underlying devices are by
	 * obtaining the device_info bits क्रम the 1st device
	 */
	अगर (!(mpt3sas_config_get_phys_disk_pg0(ioc, &mpi_reply,
	    &pd_pg0, MPI2_PHYSDISK_PGAD_FORM_PHYSDISKNUM,
	    vol_pg0->PhysDisk[0].PhysDiskNum))) अणु
		अगर (!(mpt3sas_config_get_sas_device_pg0(ioc, &mpi_reply,
		    &sas_device_pg0, MPI2_SAS_DEVICE_PGAD_FORM_HANDLE,
		    le16_to_cpu(pd_pg0.DevHandle)))) अणु
			raid_device->device_info =
			    le32_to_cpu(sas_device_pg0.DeviceInfo);
		पूर्ण
	पूर्ण

	kमुक्त(vol_pg0);
	वापस 0;
पूर्ण

/**
 * _scsih_enable_tlr - setting TLR flags
 * @ioc: per adapter object
 * @sdev: scsi device काष्ठा
 *
 * Enabling Transaction Layer Retries क्रम tape devices when
 * vpd page 0x90 is present
 *
 */
अटल व्योम
_scsih_enable_tlr(काष्ठा MPT3SAS_ADAPTER *ioc, काष्ठा scsi_device *sdev)
अणु

	/* only क्रम TAPE */
	अगर (sdev->type != TYPE_TAPE)
		वापस;

	अगर (!(ioc->facts.IOCCapabilities & MPI2_IOCFACTS_CAPABILITY_TLR))
		वापस;

	sas_enable_tlr(sdev);
	sdev_prपूर्णांकk(KERN_INFO, sdev, "TLR %s\n",
	    sas_is_tlr_enabled(sdev) ? "Enabled" : "Disabled");
	वापस;

पूर्ण

/**
 * scsih_slave_configure - device configure routine.
 * @sdev: scsi device काष्ठा
 *
 * Return: 0 अगर ok. Any other वापस is assumed to be an error and
 * the device is ignored.
 */
अटल पूर्णांक
scsih_slave_configure(काष्ठा scsi_device *sdev)
अणु
	काष्ठा Scsi_Host *shost = sdev->host;
	काष्ठा MPT3SAS_ADAPTER *ioc = shost_priv(shost);
	काष्ठा MPT3SAS_DEVICE *sas_device_priv_data;
	काष्ठा MPT3SAS_TARGET *sas_target_priv_data;
	काष्ठा _sas_device *sas_device;
	काष्ठा _pcie_device *pcie_device;
	काष्ठा _raid_device *raid_device;
	अचिन्हित दीर्घ flags;
	पूर्णांक qdepth;
	u8 ssp_target = 0;
	अक्षर *ds = "";
	अक्षर *r_level = "";
	u16 handle, volume_handle = 0;
	u64 volume_wwid = 0;

	qdepth = 1;
	sas_device_priv_data = sdev->hostdata;
	sas_device_priv_data->configured_lun = 1;
	sas_device_priv_data->flags &= ~MPT_DEVICE_FLAGS_INIT;
	sas_target_priv_data = sas_device_priv_data->sas_target;
	handle = sas_target_priv_data->handle;

	/* raid volume handling */
	अगर (sas_target_priv_data->flags & MPT_TARGET_FLAGS_VOLUME) अणु

		spin_lock_irqsave(&ioc->raid_device_lock, flags);
		raid_device = mpt3sas_raid_device_find_by_handle(ioc, handle);
		spin_unlock_irqrestore(&ioc->raid_device_lock, flags);
		अगर (!raid_device) अणु
			dfailprपूर्णांकk(ioc,
				    ioc_warn(ioc, "failure at %s:%d/%s()!\n",
					     __खाता__, __LINE__, __func__));
			वापस 1;
		पूर्ण

		अगर (_scsih_get_volume_capabilities(ioc, raid_device)) अणु
			dfailprपूर्णांकk(ioc,
				    ioc_warn(ioc, "failure at %s:%d/%s()!\n",
					     __खाता__, __LINE__, __func__));
			वापस 1;
		पूर्ण

		/*
		 * WARPDRIVE: Initialize the required data क्रम Direct IO
		 */
		mpt3sas_init_warpdrive_properties(ioc, raid_device);

		/* RAID Queue Depth Support
		 * IS volume = underlying qdepth of drive type, either
		 *    MPT3SAS_SAS_QUEUE_DEPTH or MPT3SAS_SATA_QUEUE_DEPTH
		 * IM/IME/R10 = 128 (MPT3SAS_RAID_QUEUE_DEPTH)
		 */
		अगर (raid_device->device_info &
		    MPI2_SAS_DEVICE_INFO_SSP_TARGET) अणु
			qdepth = MPT3SAS_SAS_QUEUE_DEPTH;
			ds = "SSP";
		पूर्ण अन्यथा अणु
			qdepth = MPT3SAS_SATA_QUEUE_DEPTH;
			अगर (raid_device->device_info &
			    MPI2_SAS_DEVICE_INFO_SATA_DEVICE)
				ds = "SATA";
			अन्यथा
				ds = "STP";
		पूर्ण

		चयन (raid_device->volume_type) अणु
		हाल MPI2_RAID_VOL_TYPE_RAID0:
			r_level = "RAID0";
			अवरोध;
		हाल MPI2_RAID_VOL_TYPE_RAID1E:
			qdepth = MPT3SAS_RAID_QUEUE_DEPTH;
			अगर (ioc->manu_pg10.OEMIdentअगरier &&
			    (le32_to_cpu(ioc->manu_pg10.GenericFlags0) &
			    MFG10_GF0_R10_DISPLAY) &&
			    !(raid_device->num_pds % 2))
				r_level = "RAID10";
			अन्यथा
				r_level = "RAID1E";
			अवरोध;
		हाल MPI2_RAID_VOL_TYPE_RAID1:
			qdepth = MPT3SAS_RAID_QUEUE_DEPTH;
			r_level = "RAID1";
			अवरोध;
		हाल MPI2_RAID_VOL_TYPE_RAID10:
			qdepth = MPT3SAS_RAID_QUEUE_DEPTH;
			r_level = "RAID10";
			अवरोध;
		हाल MPI2_RAID_VOL_TYPE_UNKNOWN:
		शेष:
			qdepth = MPT3SAS_RAID_QUEUE_DEPTH;
			r_level = "RAIDX";
			अवरोध;
		पूर्ण

		अगर (!ioc->hide_ir_msg)
			sdev_prपूर्णांकk(KERN_INFO, sdev,
			   "%s: handle(0x%04x), wwid(0x%016llx),"
			    " pd_count(%d), type(%s)\n",
			    r_level, raid_device->handle,
			    (अचिन्हित दीर्घ दीर्घ)raid_device->wwid,
			    raid_device->num_pds, ds);

		अगर (shost->max_sectors > MPT3SAS_RAID_MAX_SECTORS) अणु
			blk_queue_max_hw_sectors(sdev->request_queue,
						MPT3SAS_RAID_MAX_SECTORS);
			sdev_prपूर्णांकk(KERN_INFO, sdev,
					"Set queue's max_sector to: %u\n",
						MPT3SAS_RAID_MAX_SECTORS);
		पूर्ण

		mpt3sas_scsih_change_queue_depth(sdev, qdepth);

		/* raid transport support */
		अगर (!ioc->is_warpdrive)
			_scsih_set_level(ioc, sdev, raid_device->volume_type);
		वापस 0;
	पूर्ण

	/* non-raid handling */
	अगर (sas_target_priv_data->flags & MPT_TARGET_FLAGS_RAID_COMPONENT) अणु
		अगर (mpt3sas_config_get_volume_handle(ioc, handle,
		    &volume_handle)) अणु
			dfailprपूर्णांकk(ioc,
				    ioc_warn(ioc, "failure at %s:%d/%s()!\n",
					     __खाता__, __LINE__, __func__));
			वापस 1;
		पूर्ण
		अगर (volume_handle && mpt3sas_config_get_volume_wwid(ioc,
		    volume_handle, &volume_wwid)) अणु
			dfailprपूर्णांकk(ioc,
				    ioc_warn(ioc, "failure at %s:%d/%s()!\n",
					     __खाता__, __LINE__, __func__));
			वापस 1;
		पूर्ण
	पूर्ण

	/* PCIe handling */
	अगर (sas_target_priv_data->flags & MPT_TARGET_FLAGS_PCIE_DEVICE) अणु
		spin_lock_irqsave(&ioc->pcie_device_lock, flags);
		pcie_device = __mpt3sas_get_pdev_by_wwid(ioc,
				sas_device_priv_data->sas_target->sas_address);
		अगर (!pcie_device) अणु
			spin_unlock_irqrestore(&ioc->pcie_device_lock, flags);
			dfailprपूर्णांकk(ioc,
				    ioc_warn(ioc, "failure at %s:%d/%s()!\n",
					     __खाता__, __LINE__, __func__));
			वापस 1;
		पूर्ण

		qdepth = MPT3SAS_NVME_QUEUE_DEPTH;
		ds = "NVMe";
		sdev_prपूर्णांकk(KERN_INFO, sdev,
			"%s: handle(0x%04x), wwid(0x%016llx), port(%d)\n",
			ds, handle, (अचिन्हित दीर्घ दीर्घ)pcie_device->wwid,
			pcie_device->port_num);
		अगर (pcie_device->enclosure_handle != 0)
			sdev_prपूर्णांकk(KERN_INFO, sdev,
			"%s: enclosure logical id(0x%016llx), slot(%d)\n",
			ds,
			(अचिन्हित दीर्घ दीर्घ)pcie_device->enclosure_logical_id,
			pcie_device->slot);
		अगर (pcie_device->connector_name[0] != '\0')
			sdev_prपूर्णांकk(KERN_INFO, sdev,
				"%s: enclosure level(0x%04x),"
				"connector name( %s)\n", ds,
				pcie_device->enclosure_level,
				pcie_device->connector_name);

		अगर (pcie_device->nvme_mdts)
			blk_queue_max_hw_sectors(sdev->request_queue,
					pcie_device->nvme_mdts/512);

		pcie_device_put(pcie_device);
		spin_unlock_irqrestore(&ioc->pcie_device_lock, flags);
		mpt3sas_scsih_change_queue_depth(sdev, qdepth);
		/* Enable QUEUE_FLAG_NOMERGES flag, so that IOs won't be
		 ** merged and can eliminate holes created during merging
		 ** operation.
		 **/
		blk_queue_flag_set(QUEUE_FLAG_NOMERGES,
				sdev->request_queue);
		blk_queue_virt_boundary(sdev->request_queue,
				ioc->page_size - 1);
		वापस 0;
	पूर्ण

	spin_lock_irqsave(&ioc->sas_device_lock, flags);
	sas_device = __mpt3sas_get_sdev_by_addr(ioc,
	   sas_device_priv_data->sas_target->sas_address,
	   sas_device_priv_data->sas_target->port);
	अगर (!sas_device) अणु
		spin_unlock_irqrestore(&ioc->sas_device_lock, flags);
		dfailprपूर्णांकk(ioc,
			    ioc_warn(ioc, "failure at %s:%d/%s()!\n",
				     __खाता__, __LINE__, __func__));
		वापस 1;
	पूर्ण

	sas_device->volume_handle = volume_handle;
	sas_device->volume_wwid = volume_wwid;
	अगर (sas_device->device_info & MPI2_SAS_DEVICE_INFO_SSP_TARGET) अणु
		qdepth = MPT3SAS_SAS_QUEUE_DEPTH;
		ssp_target = 1;
		अगर (sas_device->device_info &
				MPI2_SAS_DEVICE_INFO_SEP) अणु
			sdev_prपूर्णांकk(KERN_WARNING, sdev,
			"set ignore_delay_remove for handle(0x%04x)\n",
			sas_device_priv_data->sas_target->handle);
			sas_device_priv_data->ignore_delay_हटाओ = 1;
			ds = "SES";
		पूर्ण अन्यथा
			ds = "SSP";
	पूर्ण अन्यथा अणु
		qdepth = MPT3SAS_SATA_QUEUE_DEPTH;
		अगर (sas_device->device_info & MPI2_SAS_DEVICE_INFO_STP_TARGET)
			ds = "STP";
		अन्यथा अगर (sas_device->device_info &
		    MPI2_SAS_DEVICE_INFO_SATA_DEVICE)
			ds = "SATA";
	पूर्ण

	sdev_prपूर्णांकk(KERN_INFO, sdev, "%s: handle(0x%04x), " \
	    "sas_addr(0x%016llx), phy(%d), device_name(0x%016llx)\n",
	    ds, handle, (अचिन्हित दीर्घ दीर्घ)sas_device->sas_address,
	    sas_device->phy, (अचिन्हित दीर्घ दीर्घ)sas_device->device_name);

	_scsih_display_enclosure_chassis_info(शून्य, sas_device, sdev, शून्य);

	sas_device_put(sas_device);
	spin_unlock_irqrestore(&ioc->sas_device_lock, flags);

	अगर (!ssp_target)
		_scsih_display_sata_capabilities(ioc, handle, sdev);


	mpt3sas_scsih_change_queue_depth(sdev, qdepth);

	अगर (ssp_target) अणु
		sas_पढ़ो_port_mode_page(sdev);
		_scsih_enable_tlr(ioc, sdev);
	पूर्ण

	वापस 0;
पूर्ण

/**
 * scsih_bios_param - fetch head, sector, cylinder info क्रम a disk
 * @sdev: scsi device काष्ठा
 * @bdev: poपूर्णांकer to block device context
 * @capacity: device size (in 512 byte sectors)
 * @params: three element array to place output:
 *              params[0] number of heads (max 255)
 *              params[1] number of sectors (max 63)
 *              params[2] number of cylinders
 */
अटल पूर्णांक
scsih_bios_param(काष्ठा scsi_device *sdev, काष्ठा block_device *bdev,
	sector_t capacity, पूर्णांक params[])
अणु
	पूर्णांक		heads;
	पूर्णांक		sectors;
	sector_t	cylinders;
	uदीर्घ		dummy;

	heads = 64;
	sectors = 32;

	dummy = heads * sectors;
	cylinders = capacity;
	sector_भाग(cylinders, dummy);

	/*
	 * Handle extended translation size क्रम logical drives
	 * > 1Gb
	 */
	अगर ((uदीर्घ)capacity >= 0x200000) अणु
		heads = 255;
		sectors = 63;
		dummy = heads * sectors;
		cylinders = capacity;
		sector_भाग(cylinders, dummy);
	पूर्ण

	/* वापस result */
	params[0] = heads;
	params[1] = sectors;
	params[2] = cylinders;

	वापस 0;
पूर्ण

/**
 * _scsih_response_code - translation of device response code
 * @ioc: per adapter object
 * @response_code: response code वापसed by the device
 */
अटल व्योम
_scsih_response_code(काष्ठा MPT3SAS_ADAPTER *ioc, u8 response_code)
अणु
	अक्षर *desc;

	चयन (response_code) अणु
	हाल MPI2_SCSITASKMGMT_RSP_TM_COMPLETE:
		desc = "task management request completed";
		अवरोध;
	हाल MPI2_SCSITASKMGMT_RSP_INVALID_FRAME:
		desc = "invalid frame";
		अवरोध;
	हाल MPI2_SCSITASKMGMT_RSP_TM_NOT_SUPPORTED:
		desc = "task management request not supported";
		अवरोध;
	हाल MPI2_SCSITASKMGMT_RSP_TM_FAILED:
		desc = "task management request failed";
		अवरोध;
	हाल MPI2_SCSITASKMGMT_RSP_TM_SUCCEEDED:
		desc = "task management request succeeded";
		अवरोध;
	हाल MPI2_SCSITASKMGMT_RSP_TM_INVALID_LUN:
		desc = "invalid lun";
		अवरोध;
	हाल 0xA:
		desc = "overlapped tag attempted";
		अवरोध;
	हाल MPI2_SCSITASKMGMT_RSP_IO_QUEUED_ON_IOC:
		desc = "task queued, however not sent to target";
		अवरोध;
	शेष:
		desc = "unknown";
		अवरोध;
	पूर्ण
	ioc_warn(ioc, "response_code(0x%01x): %s\n", response_code, desc);
पूर्ण

/**
 * _scsih_पंचांग_करोne - पंचांग completion routine
 * @ioc: per adapter object
 * @smid: प्रणाली request message index
 * @msix_index: MSIX table index supplied by the OS
 * @reply: reply message frame(lower 32bit addr)
 * Context: none.
 *
 * The callback handler when using scsih_issue_पंचांग.
 *
 * Return: 1 meaning mf should be मुक्तd from _base_पूर्णांकerrupt
 *         0 means the mf is मुक्तd from this function.
 */
अटल u8
_scsih_पंचांग_करोne(काष्ठा MPT3SAS_ADAPTER *ioc, u16 smid, u8 msix_index, u32 reply)
अणु
	MPI2DefaultReply_t *mpi_reply;

	अगर (ioc->पंचांग_cmds.status == MPT3_CMD_NOT_USED)
		वापस 1;
	अगर (ioc->पंचांग_cmds.smid != smid)
		वापस 1;
	ioc->पंचांग_cmds.status |= MPT3_CMD_COMPLETE;
	mpi_reply =  mpt3sas_base_get_reply_virt_addr(ioc, reply);
	अगर (mpi_reply) अणु
		स_नकल(ioc->पंचांग_cmds.reply, mpi_reply, mpi_reply->MsgLength*4);
		ioc->पंचांग_cmds.status |= MPT3_CMD_REPLY_VALID;
	पूर्ण
	ioc->पंचांग_cmds.status &= ~MPT3_CMD_PENDING;
	complete(&ioc->पंचांग_cmds.करोne);
	वापस 1;
पूर्ण

/**
 * mpt3sas_scsih_set_पंचांग_flag - set per target पंचांग_busy
 * @ioc: per adapter object
 * @handle: device handle
 *
 * During taskmangement request, we need to मुक्तze the device queue.
 */
व्योम
mpt3sas_scsih_set_पंचांग_flag(काष्ठा MPT3SAS_ADAPTER *ioc, u16 handle)
अणु
	काष्ठा MPT3SAS_DEVICE *sas_device_priv_data;
	काष्ठा scsi_device *sdev;
	u8 skip = 0;

	shost_क्रम_each_device(sdev, ioc->shost) अणु
		अगर (skip)
			जारी;
		sas_device_priv_data = sdev->hostdata;
		अगर (!sas_device_priv_data)
			जारी;
		अगर (sas_device_priv_data->sas_target->handle == handle) अणु
			sas_device_priv_data->sas_target->पंचांग_busy = 1;
			skip = 1;
			ioc->ignore_loginfos = 1;
		पूर्ण
	पूर्ण
पूर्ण

/**
 * mpt3sas_scsih_clear_पंचांग_flag - clear per target पंचांग_busy
 * @ioc: per adapter object
 * @handle: device handle
 *
 * During taskmangement request, we need to मुक्तze the device queue.
 */
व्योम
mpt3sas_scsih_clear_पंचांग_flag(काष्ठा MPT3SAS_ADAPTER *ioc, u16 handle)
अणु
	काष्ठा MPT3SAS_DEVICE *sas_device_priv_data;
	काष्ठा scsi_device *sdev;
	u8 skip = 0;

	shost_क्रम_each_device(sdev, ioc->shost) अणु
		अगर (skip)
			जारी;
		sas_device_priv_data = sdev->hostdata;
		अगर (!sas_device_priv_data)
			जारी;
		अगर (sas_device_priv_data->sas_target->handle == handle) अणु
			sas_device_priv_data->sas_target->पंचांग_busy = 0;
			skip = 1;
			ioc->ignore_loginfos = 0;
		पूर्ण
	पूर्ण
पूर्ण

/**
 * scsih_पंचांग_cmd_map_status - map the target reset & LUN reset TM status
 * @ioc: per adapter object
 * @channel: the channel asचिन्हित by the OS
 * @id: the id asचिन्हित by the OS
 * @lun: lun number
 * @type: MPI2_SCSITASKMGMT_TASKTYPE__XXX (defined in mpi2_init.h)
 * @smid_task: smid asचिन्हित to the task
 *
 * Look whether TM has पातed the समयd out SCSI command, अगर
 * TM has पातed the IO then वापस SUCCESS अन्यथा वापस FAILED.
 */
अटल पूर्णांक
scsih_पंचांग_cmd_map_status(काष्ठा MPT3SAS_ADAPTER *ioc, uपूर्णांक channel,
	uपूर्णांक id, uपूर्णांक lun, u8 type, u16 smid_task)
अणु

	अगर (smid_task <= ioc->shost->can_queue) अणु
		चयन (type) अणु
		हाल MPI2_SCSITASKMGMT_TASKTYPE_TARGET_RESET:
			अगर (!(_scsih_scsi_lookup_find_by_target(ioc,
			    id, channel)))
				वापस SUCCESS;
			अवरोध;
		हाल MPI2_SCSITASKMGMT_TASKTYPE_ABRT_TASK_SET:
		हाल MPI2_SCSITASKMGMT_TASKTYPE_LOGICAL_UNIT_RESET:
			अगर (!(_scsih_scsi_lookup_find_by_lun(ioc, id,
			    lun, channel)))
				वापस SUCCESS;
			अवरोध;
		शेष:
			वापस SUCCESS;
		पूर्ण
	पूर्ण अन्यथा अगर (smid_task == ioc->scsih_cmds.smid) अणु
		अगर ((ioc->scsih_cmds.status & MPT3_CMD_COMPLETE) ||
		    (ioc->scsih_cmds.status & MPT3_CMD_NOT_USED))
			वापस SUCCESS;
	पूर्ण अन्यथा अगर (smid_task == ioc->ctl_cmds.smid) अणु
		अगर ((ioc->ctl_cmds.status & MPT3_CMD_COMPLETE) ||
		    (ioc->ctl_cmds.status & MPT3_CMD_NOT_USED))
			वापस SUCCESS;
	पूर्ण

	वापस FAILED;
पूर्ण

/**
 * scsih_पंचांग_post_processing - post processing of target & LUN reset
 * @ioc: per adapter object
 * @handle: device handle
 * @channel: the channel asचिन्हित by the OS
 * @id: the id asचिन्हित by the OS
 * @lun: lun number
 * @type: MPI2_SCSITASKMGMT_TASKTYPE__XXX (defined in mpi2_init.h)
 * @smid_task: smid asचिन्हित to the task
 *
 * Post processing of target & LUN reset. Due to पूर्णांकerrupt latency
 * issue it possible that पूर्णांकerrupt क्रम पातed IO might not be
 * received yet. So beक्रमe वापसing failure status, poll the
 * reply descriptor pools क्रम the reply of समयd out SCSI command.
 * Return FAILED status अगर reply क्रम समयd out is not received
 * otherwise वापस SUCCESS.
 */
अटल पूर्णांक
scsih_पंचांग_post_processing(काष्ठा MPT3SAS_ADAPTER *ioc, u16 handle,
	uपूर्णांक channel, uपूर्णांक id, uपूर्णांक lun, u8 type, u16 smid_task)
अणु
	पूर्णांक rc;

	rc = scsih_पंचांग_cmd_map_status(ioc, channel, id, lun, type, smid_task);
	अगर (rc == SUCCESS)
		वापस rc;

	ioc_info(ioc,
	    "Poll ReplyDescriptor queues for completion of"
	    " smid(%d), task_type(0x%02x), handle(0x%04x)\n",
	    smid_task, type, handle);

	/*
	 * Due to पूर्णांकerrupt latency issues, driver may receive पूर्णांकerrupt क्रम
	 * TM first and then क्रम पातed SCSI IO command. So, poll all the
	 * ReplyDescriptor pools beक्रमe वापसing the FAILED status to SML.
	 */
	mpt3sas_base_mask_पूर्णांकerrupts(ioc);
	mpt3sas_base_sync_reply_irqs(ioc, 1);
	mpt3sas_base_unmask_पूर्णांकerrupts(ioc);

	वापस scsih_पंचांग_cmd_map_status(ioc, channel, id, lun, type, smid_task);
पूर्ण

/**
 * mpt3sas_scsih_issue_पंचांग - मुख्य routine क्रम sending पंचांग requests
 * @ioc: per adapter काष्ठा
 * @handle: device handle
 * @channel: the channel asचिन्हित by the OS
 * @id: the id asचिन्हित by the OS
 * @lun: lun number
 * @type: MPI2_SCSITASKMGMT_TASKTYPE__XXX (defined in mpi2_init.h)
 * @smid_task: smid asचिन्हित to the task
 * @msix_task: MSIX table index supplied by the OS
 * @समयout: समयout in seconds
 * @tr_method: Target Reset Method
 * Context: user
 *
 * A generic API क्रम sending task management requests to firmware.
 *
 * The callback index is set inside `ioc->पंचांग_cb_idx`.
 * The caller is responsible to check क्रम outstanding commands.
 *
 * Return: SUCCESS or FAILED.
 */
पूर्णांक
mpt3sas_scsih_issue_पंचांग(काष्ठा MPT3SAS_ADAPTER *ioc, u16 handle, uपूर्णांक channel,
	uपूर्णांक id, u64 lun, u8 type, u16 smid_task, u16 msix_task,
	u8 समयout, u8 tr_method)
अणु
	Mpi2SCSITaskManagementRequest_t *mpi_request;
	Mpi2SCSITaskManagementReply_t *mpi_reply;
	Mpi25SCSIIORequest_t *request;
	u16 smid = 0;
	u32 ioc_state;
	पूर्णांक rc;
	u8 issue_reset = 0;

	lockdep_निश्चित_held(&ioc->पंचांग_cmds.mutex);

	अगर (ioc->पंचांग_cmds.status != MPT3_CMD_NOT_USED) अणु
		ioc_info(ioc, "%s: tm_cmd busy!!!\n", __func__);
		वापस FAILED;
	पूर्ण

	अगर (ioc->shost_recovery || ioc->हटाओ_host ||
	    ioc->pci_error_recovery) अणु
		ioc_info(ioc, "%s: host reset in progress!\n", __func__);
		वापस FAILED;
	पूर्ण

	ioc_state = mpt3sas_base_get_iocstate(ioc, 0);
	अगर (ioc_state & MPI2_DOORBELL_USED) अणु
		dhsprपूर्णांकk(ioc, ioc_info(ioc, "unexpected doorbell active!\n"));
		rc = mpt3sas_base_hard_reset_handler(ioc, FORCE_BIG_HAMMER);
		वापस (!rc) ? SUCCESS : FAILED;
	पूर्ण

	अगर ((ioc_state & MPI2_IOC_STATE_MASK) == MPI2_IOC_STATE_FAULT) अणु
		mpt3sas_prपूर्णांक_fault_code(ioc, ioc_state &
		    MPI2_DOORBELL_DATA_MASK);
		rc = mpt3sas_base_hard_reset_handler(ioc, FORCE_BIG_HAMMER);
		वापस (!rc) ? SUCCESS : FAILED;
	पूर्ण अन्यथा अगर ((ioc_state & MPI2_IOC_STATE_MASK) ==
	    MPI2_IOC_STATE_COREDUMP) अणु
		mpt3sas_prपूर्णांक_coredump_info(ioc, ioc_state &
		    MPI2_DOORBELL_DATA_MASK);
		rc = mpt3sas_base_hard_reset_handler(ioc, FORCE_BIG_HAMMER);
		वापस (!rc) ? SUCCESS : FAILED;
	पूर्ण

	smid = mpt3sas_base_get_smid_hpr(ioc, ioc->पंचांग_cb_idx);
	अगर (!smid) अणु
		ioc_err(ioc, "%s: failed obtaining a smid\n", __func__);
		वापस FAILED;
	पूर्ण

	dपंचांगprपूर्णांकk(ioc,
		  ioc_info(ioc, "sending tm: handle(0x%04x), task_type(0x%02x), smid(%d), timeout(%d), tr_method(0x%x)\n",
			   handle, type, smid_task, समयout, tr_method));
	ioc->पंचांग_cmds.status = MPT3_CMD_PENDING;
	mpi_request = mpt3sas_base_get_msg_frame(ioc, smid);
	ioc->पंचांग_cmds.smid = smid;
	स_रखो(mpi_request, 0, माप(Mpi2SCSITaskManagementRequest_t));
	स_रखो(ioc->पंचांग_cmds.reply, 0, माप(Mpi2SCSITaskManagementReply_t));
	mpi_request->Function = MPI2_FUNCTION_SCSI_TASK_MGMT;
	mpi_request->DevHandle = cpu_to_le16(handle);
	mpi_request->TaskType = type;
	अगर (type == MPI2_SCSITASKMGMT_TASKTYPE_ABORT_TASK ||
	    type == MPI2_SCSITASKMGMT_TASKTYPE_QUERY_TASK)
		mpi_request->MsgFlags = tr_method;
	mpi_request->TaskMID = cpu_to_le16(smid_task);
	पूर्णांक_to_scsilun(lun, (काष्ठा scsi_lun *)mpi_request->LUN);
	mpt3sas_scsih_set_पंचांग_flag(ioc, handle);
	init_completion(&ioc->पंचांग_cmds.करोne);
	ioc->put_smid_hi_priority(ioc, smid, msix_task);
	रुको_क्रम_completion_समयout(&ioc->पंचांग_cmds.करोne, समयout*HZ);
	अगर (!(ioc->पंचांग_cmds.status & MPT3_CMD_COMPLETE)) अणु
		mpt3sas_check_cmd_समयout(ioc,
		    ioc->पंचांग_cmds.status, mpi_request,
		    माप(Mpi2SCSITaskManagementRequest_t)/4, issue_reset);
		अगर (issue_reset) अणु
			rc = mpt3sas_base_hard_reset_handler(ioc,
					FORCE_BIG_HAMMER);
			rc = (!rc) ? SUCCESS : FAILED;
			जाओ out;
		पूर्ण
	पूर्ण

	/* sync IRQs in हाल those were busy during flush. */
	mpt3sas_base_sync_reply_irqs(ioc, 0);

	अगर (ioc->पंचांग_cmds.status & MPT3_CMD_REPLY_VALID) अणु
		mpt3sas_trigger_master(ioc, MASTER_TRIGGER_TASK_MANAGMENT);
		mpi_reply = ioc->पंचांग_cmds.reply;
		dपंचांगprपूर्णांकk(ioc,
			  ioc_info(ioc, "complete tm: ioc_status(0x%04x), loginfo(0x%08x), term_count(0x%08x)\n",
				   le16_to_cpu(mpi_reply->IOCStatus),
				   le32_to_cpu(mpi_reply->IOCLogInfo),
				   le32_to_cpu(mpi_reply->TerminationCount)));
		अगर (ioc->logging_level & MPT_DEBUG_TM) अणु
			_scsih_response_code(ioc, mpi_reply->ResponseCode);
			अगर (mpi_reply->IOCStatus)
				_debug_dump_mf(mpi_request,
				    माप(Mpi2SCSITaskManagementRequest_t)/4);
		पूर्ण
	पूर्ण

	चयन (type) अणु
	हाल MPI2_SCSITASKMGMT_TASKTYPE_ABORT_TASK:
		rc = SUCCESS;
		/*
		 * If DevHandle filed in smid_task's entry of request pool
		 * करोesn't match with device handle on which this task पात
		 * TM is received then it means that TM has successfully
		 * पातed the समयd out command. Since smid_task's entry in
		 * request pool will be स_रखो to zero once the समयd out
		 * command is वापसed to the SML. If the command is not
		 * पातed then smid_taskै s entry wonै t be cleared and it
		 * will have same DevHandle value on which this task पात TM
		 * is received and driver will वापस the TM status as FAILED.
		 */
		request = mpt3sas_base_get_msg_frame(ioc, smid_task);
		अगर (le16_to_cpu(request->DevHandle) != handle)
			अवरोध;

		ioc_info(ioc, "Task abort tm failed: handle(0x%04x),"
		    "timeout(%d) tr_method(0x%x) smid(%d) msix_index(%d)\n",
		    handle, समयout, tr_method, smid_task, msix_task);
		rc = FAILED;
		अवरोध;

	हाल MPI2_SCSITASKMGMT_TASKTYPE_TARGET_RESET:
	हाल MPI2_SCSITASKMGMT_TASKTYPE_ABRT_TASK_SET:
	हाल MPI2_SCSITASKMGMT_TASKTYPE_LOGICAL_UNIT_RESET:
		rc = scsih_पंचांग_post_processing(ioc, handle, channel, id, lun,
		    type, smid_task);
		अवरोध;
	हाल MPI2_SCSITASKMGMT_TASKTYPE_QUERY_TASK:
		rc = SUCCESS;
		अवरोध;
	शेष:
		rc = FAILED;
		अवरोध;
	पूर्ण

out:
	mpt3sas_scsih_clear_पंचांग_flag(ioc, handle);
	ioc->पंचांग_cmds.status = MPT3_CMD_NOT_USED;
	वापस rc;
पूर्ण

पूर्णांक mpt3sas_scsih_issue_locked_पंचांग(काष्ठा MPT3SAS_ADAPTER *ioc, u16 handle,
		uपूर्णांक channel, uपूर्णांक id, u64 lun, u8 type, u16 smid_task,
		u16 msix_task, u8 समयout, u8 tr_method)
अणु
	पूर्णांक ret;

	mutex_lock(&ioc->पंचांग_cmds.mutex);
	ret = mpt3sas_scsih_issue_पंचांग(ioc, handle, channel, id, lun, type,
			smid_task, msix_task, समयout, tr_method);
	mutex_unlock(&ioc->पंचांग_cmds.mutex);

	वापस ret;
पूर्ण

/**
 * _scsih_पंचांग_display_info - displays info about the device
 * @ioc: per adapter काष्ठा
 * @scmd: poपूर्णांकer to scsi command object
 *
 * Called by task management callback handlers.
 */
अटल व्योम
_scsih_पंचांग_display_info(काष्ठा MPT3SAS_ADAPTER *ioc, काष्ठा scsi_cmnd *scmd)
अणु
	काष्ठा scsi_target *starget = scmd->device->sdev_target;
	काष्ठा MPT3SAS_TARGET *priv_target = starget->hostdata;
	काष्ठा _sas_device *sas_device = शून्य;
	काष्ठा _pcie_device *pcie_device = शून्य;
	अचिन्हित दीर्घ flags;
	अक्षर *device_str = शून्य;

	अगर (!priv_target)
		वापस;
	अगर (ioc->hide_ir_msg)
		device_str = "WarpDrive";
	अन्यथा
		device_str = "volume";

	scsi_prपूर्णांक_command(scmd);
	अगर (priv_target->flags & MPT_TARGET_FLAGS_VOLUME) अणु
		starget_prपूर्णांकk(KERN_INFO, starget,
			"%s handle(0x%04x), %s wwid(0x%016llx)\n",
			device_str, priv_target->handle,
		    device_str, (अचिन्हित दीर्घ दीर्घ)priv_target->sas_address);

	पूर्ण अन्यथा अगर (priv_target->flags & MPT_TARGET_FLAGS_PCIE_DEVICE) अणु
		spin_lock_irqsave(&ioc->pcie_device_lock, flags);
		pcie_device = __mpt3sas_get_pdev_from_target(ioc, priv_target);
		अगर (pcie_device) अणु
			starget_prपूर्णांकk(KERN_INFO, starget,
				"handle(0x%04x), wwid(0x%016llx), port(%d)\n",
				pcie_device->handle,
				(अचिन्हित दीर्घ दीर्घ)pcie_device->wwid,
				pcie_device->port_num);
			अगर (pcie_device->enclosure_handle != 0)
				starget_prपूर्णांकk(KERN_INFO, starget,
					"enclosure logical id(0x%016llx), slot(%d)\n",
					(अचिन्हित दीर्घ दीर्घ)
					pcie_device->enclosure_logical_id,
					pcie_device->slot);
			अगर (pcie_device->connector_name[0] != '\0')
				starget_prपूर्णांकk(KERN_INFO, starget,
					"enclosure level(0x%04x), connector name( %s)\n",
					pcie_device->enclosure_level,
					pcie_device->connector_name);
			pcie_device_put(pcie_device);
		पूर्ण
		spin_unlock_irqrestore(&ioc->pcie_device_lock, flags);

	पूर्ण अन्यथा अणु
		spin_lock_irqsave(&ioc->sas_device_lock, flags);
		sas_device = __mpt3sas_get_sdev_from_target(ioc, priv_target);
		अगर (sas_device) अणु
			अगर (priv_target->flags &
			    MPT_TARGET_FLAGS_RAID_COMPONENT) अणु
				starget_prपूर्णांकk(KERN_INFO, starget,
				    "volume handle(0x%04x), "
				    "volume wwid(0x%016llx)\n",
				    sas_device->volume_handle,
				   (अचिन्हित दीर्घ दीर्घ)sas_device->volume_wwid);
			पूर्ण
			starget_prपूर्णांकk(KERN_INFO, starget,
			    "handle(0x%04x), sas_address(0x%016llx), phy(%d)\n",
			    sas_device->handle,
			    (अचिन्हित दीर्घ दीर्घ)sas_device->sas_address,
			    sas_device->phy);

			_scsih_display_enclosure_chassis_info(शून्य, sas_device,
			    शून्य, starget);

			sas_device_put(sas_device);
		पूर्ण
		spin_unlock_irqrestore(&ioc->sas_device_lock, flags);
	पूर्ण
पूर्ण

/**
 * scsih_पात - eh thपढ़ोs मुख्य पात routine
 * @scmd: poपूर्णांकer to scsi command object
 *
 * Return: SUCCESS अगर command पातed अन्यथा FAILED
 */
अटल पूर्णांक
scsih_पात(काष्ठा scsi_cmnd *scmd)
अणु
	काष्ठा MPT3SAS_ADAPTER *ioc = shost_priv(scmd->device->host);
	काष्ठा MPT3SAS_DEVICE *sas_device_priv_data;
	काष्ठा scsiio_tracker *st = scsi_cmd_priv(scmd);
	u16 handle;
	पूर्णांक r;

	u8 समयout = 30;
	काष्ठा _pcie_device *pcie_device = शून्य;
	sdev_prपूर्णांकk(KERN_INFO, scmd->device, "attempting task abort!"
	    "scmd(0x%p), outstanding for %u ms & timeout %u ms\n",
	    scmd, jअगरfies_to_msecs(jअगरfies - scmd->jअगरfies_at_alloc),
	    (scmd->request->समयout / HZ) * 1000);
	_scsih_पंचांग_display_info(ioc, scmd);

	sas_device_priv_data = scmd->device->hostdata;
	अगर (!sas_device_priv_data || !sas_device_priv_data->sas_target ||
	    ioc->हटाओ_host) अणु
		sdev_prपूर्णांकk(KERN_INFO, scmd->device,
		    "device been deleted! scmd(0x%p)\n", scmd);
		scmd->result = DID_NO_CONNECT << 16;
		scmd->scsi_करोne(scmd);
		r = SUCCESS;
		जाओ out;
	पूर्ण

	/* check क्रम completed command */
	अगर (st == शून्य || st->cb_idx == 0xFF) अणु
		sdev_prपूर्णांकk(KERN_INFO, scmd->device, "No reference found at "
		    "driver, assuming scmd(0x%p) might have completed\n", scmd);
		scmd->result = DID_RESET << 16;
		r = SUCCESS;
		जाओ out;
	पूर्ण

	/* क्रम hidden raid components and volumes this is not supported */
	अगर (sas_device_priv_data->sas_target->flags &
	    MPT_TARGET_FLAGS_RAID_COMPONENT ||
	    sas_device_priv_data->sas_target->flags & MPT_TARGET_FLAGS_VOLUME) अणु
		scmd->result = DID_RESET << 16;
		r = FAILED;
		जाओ out;
	पूर्ण

	mpt3sas_halt_firmware(ioc);

	handle = sas_device_priv_data->sas_target->handle;
	pcie_device = mpt3sas_get_pdev_by_handle(ioc, handle);
	अगर (pcie_device && (!ioc->पंचांग_custom_handling) &&
	    (!(mpt3sas_scsih_is_pcie_scsi_device(pcie_device->device_info))))
		समयout = ioc->nvme_पात_समयout;
	r = mpt3sas_scsih_issue_locked_पंचांग(ioc, handle, scmd->device->channel,
		scmd->device->id, scmd->device->lun,
		MPI2_SCSITASKMGMT_TASKTYPE_ABORT_TASK,
		st->smid, st->msix_io, समयout, 0);
	/* Command must be cleared after पात */
	अगर (r == SUCCESS && st->cb_idx != 0xFF)
		r = FAILED;
 out:
	sdev_prपूर्णांकk(KERN_INFO, scmd->device, "task abort: %s scmd(0x%p)\n",
	    ((r == SUCCESS) ? "SUCCESS" : "FAILED"), scmd);
	अगर (pcie_device)
		pcie_device_put(pcie_device);
	वापस r;
पूर्ण

/**
 * scsih_dev_reset - eh thपढ़ोs मुख्य device reset routine
 * @scmd: poपूर्णांकer to scsi command object
 *
 * Return: SUCCESS अगर command पातed अन्यथा FAILED
 */
अटल पूर्णांक
scsih_dev_reset(काष्ठा scsi_cmnd *scmd)
अणु
	काष्ठा MPT3SAS_ADAPTER *ioc = shost_priv(scmd->device->host);
	काष्ठा MPT3SAS_DEVICE *sas_device_priv_data;
	काष्ठा _sas_device *sas_device = शून्य;
	काष्ठा _pcie_device *pcie_device = शून्य;
	u16	handle;
	u8	tr_method = 0;
	u8	tr_समयout = 30;
	पूर्णांक r;

	काष्ठा scsi_target *starget = scmd->device->sdev_target;
	काष्ठा MPT3SAS_TARGET *target_priv_data = starget->hostdata;

	sdev_prपूर्णांकk(KERN_INFO, scmd->device,
	    "attempting device reset! scmd(0x%p)\n", scmd);
	_scsih_पंचांग_display_info(ioc, scmd);

	sas_device_priv_data = scmd->device->hostdata;
	अगर (!sas_device_priv_data || !sas_device_priv_data->sas_target ||
	    ioc->हटाओ_host) अणु
		sdev_prपूर्णांकk(KERN_INFO, scmd->device,
		    "device been deleted! scmd(0x%p)\n", scmd);
		scmd->result = DID_NO_CONNECT << 16;
		scmd->scsi_करोne(scmd);
		r = SUCCESS;
		जाओ out;
	पूर्ण

	/* क्रम hidden raid components obtain the volume_handle */
	handle = 0;
	अगर (sas_device_priv_data->sas_target->flags &
	    MPT_TARGET_FLAGS_RAID_COMPONENT) अणु
		sas_device = mpt3sas_get_sdev_from_target(ioc,
				target_priv_data);
		अगर (sas_device)
			handle = sas_device->volume_handle;
	पूर्ण अन्यथा
		handle = sas_device_priv_data->sas_target->handle;

	अगर (!handle) अणु
		scmd->result = DID_RESET << 16;
		r = FAILED;
		जाओ out;
	पूर्ण

	pcie_device = mpt3sas_get_pdev_by_handle(ioc, handle);

	अगर (pcie_device && (!ioc->पंचांग_custom_handling) &&
	    (!(mpt3sas_scsih_is_pcie_scsi_device(pcie_device->device_info)))) अणु
		tr_समयout = pcie_device->reset_समयout;
		tr_method = MPI26_SCSITASKMGMT_MSGFLAGS_PROTOCOL_LVL_RST_PCIE;
	पूर्ण अन्यथा
		tr_method = MPI2_SCSITASKMGMT_MSGFLAGS_LINK_RESET;

	r = mpt3sas_scsih_issue_locked_पंचांग(ioc, handle, scmd->device->channel,
		scmd->device->id, scmd->device->lun,
		MPI2_SCSITASKMGMT_TASKTYPE_LOGICAL_UNIT_RESET, 0, 0,
		tr_समयout, tr_method);
	/* Check क्रम busy commands after reset */
	अगर (r == SUCCESS && scsi_device_busy(scmd->device))
		r = FAILED;
 out:
	sdev_prपूर्णांकk(KERN_INFO, scmd->device, "device reset: %s scmd(0x%p)\n",
	    ((r == SUCCESS) ? "SUCCESS" : "FAILED"), scmd);

	अगर (sas_device)
		sas_device_put(sas_device);
	अगर (pcie_device)
		pcie_device_put(pcie_device);

	वापस r;
पूर्ण

/**
 * scsih_target_reset - eh thपढ़ोs मुख्य target reset routine
 * @scmd: poपूर्णांकer to scsi command object
 *
 * Return: SUCCESS अगर command पातed अन्यथा FAILED
 */
अटल पूर्णांक
scsih_target_reset(काष्ठा scsi_cmnd *scmd)
अणु
	काष्ठा MPT3SAS_ADAPTER *ioc = shost_priv(scmd->device->host);
	काष्ठा MPT3SAS_DEVICE *sas_device_priv_data;
	काष्ठा _sas_device *sas_device = शून्य;
	काष्ठा _pcie_device *pcie_device = शून्य;
	u16	handle;
	u8	tr_method = 0;
	u8	tr_समयout = 30;
	पूर्णांक r;
	काष्ठा scsi_target *starget = scmd->device->sdev_target;
	काष्ठा MPT3SAS_TARGET *target_priv_data = starget->hostdata;

	starget_prपूर्णांकk(KERN_INFO, starget,
	    "attempting target reset! scmd(0x%p)\n", scmd);
	_scsih_पंचांग_display_info(ioc, scmd);

	sas_device_priv_data = scmd->device->hostdata;
	अगर (!sas_device_priv_data || !sas_device_priv_data->sas_target ||
	    ioc->हटाओ_host) अणु
		starget_prपूर्णांकk(KERN_INFO, starget,
		    "target been deleted! scmd(0x%p)\n", scmd);
		scmd->result = DID_NO_CONNECT << 16;
		scmd->scsi_करोne(scmd);
		r = SUCCESS;
		जाओ out;
	पूर्ण

	/* क्रम hidden raid components obtain the volume_handle */
	handle = 0;
	अगर (sas_device_priv_data->sas_target->flags &
	    MPT_TARGET_FLAGS_RAID_COMPONENT) अणु
		sas_device = mpt3sas_get_sdev_from_target(ioc,
				target_priv_data);
		अगर (sas_device)
			handle = sas_device->volume_handle;
	पूर्ण अन्यथा
		handle = sas_device_priv_data->sas_target->handle;

	अगर (!handle) अणु
		scmd->result = DID_RESET << 16;
		r = FAILED;
		जाओ out;
	पूर्ण

	pcie_device = mpt3sas_get_pdev_by_handle(ioc, handle);

	अगर (pcie_device && (!ioc->पंचांग_custom_handling) &&
	    (!(mpt3sas_scsih_is_pcie_scsi_device(pcie_device->device_info)))) अणु
		tr_समयout = pcie_device->reset_समयout;
		tr_method = MPI26_SCSITASKMGMT_MSGFLAGS_PROTOCOL_LVL_RST_PCIE;
	पूर्ण अन्यथा
		tr_method = MPI2_SCSITASKMGMT_MSGFLAGS_LINK_RESET;
	r = mpt3sas_scsih_issue_locked_पंचांग(ioc, handle, scmd->device->channel,
		scmd->device->id, 0,
		MPI2_SCSITASKMGMT_TASKTYPE_TARGET_RESET, 0, 0,
	    tr_समयout, tr_method);
	/* Check क्रम busy commands after reset */
	अगर (r == SUCCESS && atomic_पढ़ो(&starget->target_busy))
		r = FAILED;
 out:
	starget_prपूर्णांकk(KERN_INFO, starget, "target reset: %s scmd(0x%p)\n",
	    ((r == SUCCESS) ? "SUCCESS" : "FAILED"), scmd);

	अगर (sas_device)
		sas_device_put(sas_device);
	अगर (pcie_device)
		pcie_device_put(pcie_device);
	वापस r;
पूर्ण


/**
 * scsih_host_reset - eh thपढ़ोs मुख्य host reset routine
 * @scmd: poपूर्णांकer to scsi command object
 *
 * Return: SUCCESS अगर command पातed अन्यथा FAILED
 */
अटल पूर्णांक
scsih_host_reset(काष्ठा scsi_cmnd *scmd)
अणु
	काष्ठा MPT3SAS_ADAPTER *ioc = shost_priv(scmd->device->host);
	पूर्णांक r, retval;

	ioc_info(ioc, "attempting host reset! scmd(0x%p)\n", scmd);
	scsi_prपूर्णांक_command(scmd);

	अगर (ioc->is_driver_loading || ioc->हटाओ_host) अणु
		ioc_info(ioc, "Blocking the host reset\n");
		r = FAILED;
		जाओ out;
	पूर्ण

	retval = mpt3sas_base_hard_reset_handler(ioc, FORCE_BIG_HAMMER);
	r = (retval < 0) ? FAILED : SUCCESS;
out:
	ioc_info(ioc, "host reset: %s scmd(0x%p)\n",
		 r == SUCCESS ? "SUCCESS" : "FAILED", scmd);

	वापस r;
पूर्ण

/**
 * _scsih_fw_event_add - insert and queue up fw_event
 * @ioc: per adapter object
 * @fw_event: object describing the event
 * Context: This function will acquire ioc->fw_event_lock.
 *
 * This adds the firmware event object पूर्णांकo link list, then queues it up to
 * be processed from user context.
 */
अटल व्योम
_scsih_fw_event_add(काष्ठा MPT3SAS_ADAPTER *ioc, काष्ठा fw_event_work *fw_event)
अणु
	अचिन्हित दीर्घ flags;

	अगर (ioc->firmware_event_thपढ़ो == शून्य)
		वापस;

	spin_lock_irqsave(&ioc->fw_event_lock, flags);
	fw_event_work_get(fw_event);
	INIT_LIST_HEAD(&fw_event->list);
	list_add_tail(&fw_event->list, &ioc->fw_event_list);
	INIT_WORK(&fw_event->work, _firmware_event_work);
	fw_event_work_get(fw_event);
	queue_work(ioc->firmware_event_thपढ़ो, &fw_event->work);
	spin_unlock_irqrestore(&ioc->fw_event_lock, flags);
पूर्ण

/**
 * _scsih_fw_event_del_from_list - delete fw_event from the list
 * @ioc: per adapter object
 * @fw_event: object describing the event
 * Context: This function will acquire ioc->fw_event_lock.
 *
 * If the fw_event is on the fw_event_list, हटाओ it and करो a put.
 */
अटल व्योम
_scsih_fw_event_del_from_list(काष्ठा MPT3SAS_ADAPTER *ioc, काष्ठा fw_event_work
	*fw_event)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ioc->fw_event_lock, flags);
	अगर (!list_empty(&fw_event->list)) अणु
		list_del_init(&fw_event->list);
		fw_event_work_put(fw_event);
	पूर्ण
	spin_unlock_irqrestore(&ioc->fw_event_lock, flags);
पूर्ण


 /**
 * mpt3sas_send_trigger_data_event - send event क्रम processing trigger data
 * @ioc: per adapter object
 * @event_data: trigger event data
 */
व्योम
mpt3sas_send_trigger_data_event(काष्ठा MPT3SAS_ADAPTER *ioc,
	काष्ठा SL_WH_TRIGGERS_EVENT_DATA_T *event_data)
अणु
	काष्ठा fw_event_work *fw_event;
	u16 sz;

	अगर (ioc->is_driver_loading)
		वापस;
	sz = माप(*event_data);
	fw_event = alloc_fw_event_work(sz);
	अगर (!fw_event)
		वापस;
	fw_event->event = MPT3SAS_PROCESS_TRIGGER_DIAG;
	fw_event->ioc = ioc;
	स_नकल(fw_event->event_data, event_data, माप(*event_data));
	_scsih_fw_event_add(ioc, fw_event);
	fw_event_work_put(fw_event);
पूर्ण

/**
 * _scsih_error_recovery_delete_devices - हटाओ devices not responding
 * @ioc: per adapter object
 */
अटल व्योम
_scsih_error_recovery_delete_devices(काष्ठा MPT3SAS_ADAPTER *ioc)
अणु
	काष्ठा fw_event_work *fw_event;

	अगर (ioc->is_driver_loading)
		वापस;
	fw_event = alloc_fw_event_work(0);
	अगर (!fw_event)
		वापस;
	fw_event->event = MPT3SAS_REMOVE_UNRESPONDING_DEVICES;
	fw_event->ioc = ioc;
	_scsih_fw_event_add(ioc, fw_event);
	fw_event_work_put(fw_event);
पूर्ण

/**
 * mpt3sas_port_enable_complete - port enable completed (fake event)
 * @ioc: per adapter object
 */
व्योम
mpt3sas_port_enable_complete(काष्ठा MPT3SAS_ADAPTER *ioc)
अणु
	काष्ठा fw_event_work *fw_event;

	fw_event = alloc_fw_event_work(0);
	अगर (!fw_event)
		वापस;
	fw_event->event = MPT3SAS_PORT_ENABLE_COMPLETE;
	fw_event->ioc = ioc;
	_scsih_fw_event_add(ioc, fw_event);
	fw_event_work_put(fw_event);
पूर्ण

अटल काष्ठा fw_event_work *dequeue_next_fw_event(काष्ठा MPT3SAS_ADAPTER *ioc)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा fw_event_work *fw_event = शून्य;

	spin_lock_irqsave(&ioc->fw_event_lock, flags);
	अगर (!list_empty(&ioc->fw_event_list)) अणु
		fw_event = list_first_entry(&ioc->fw_event_list,
				काष्ठा fw_event_work, list);
		list_del_init(&fw_event->list);
	पूर्ण
	spin_unlock_irqrestore(&ioc->fw_event_lock, flags);

	वापस fw_event;
पूर्ण

/**
 * _scsih_fw_event_cleanup_queue - cleanup event queue
 * @ioc: per adapter object
 *
 * Walk the firmware event queue, either समाप्तing समयrs, or रुकोing
 * क्रम outstanding events to complete
 *
 * Context: task, can sleep
 */
अटल व्योम
_scsih_fw_event_cleanup_queue(काष्ठा MPT3SAS_ADAPTER *ioc)
अणु
	काष्ठा fw_event_work *fw_event;

	अगर ((list_empty(&ioc->fw_event_list) && !ioc->current_event) ||
	    !ioc->firmware_event_thपढ़ो)
		वापस;

	ioc->fw_events_cleanup = 1;
	जबतक ((fw_event = dequeue_next_fw_event(ioc)) ||
	     (fw_event = ioc->current_event)) अणु
		/*
		 * Wait on the fw_event to complete. If this वापसs 1, then
		 * the event was never executed, and we need a put क्रम the
		 * reference the work had on the fw_event.
		 *
		 * If it did execute, we रुको क्रम it to finish, and the put will
		 * happen from _firmware_event_work()
		 */
		अगर (cancel_work_sync(&fw_event->work))
			fw_event_work_put(fw_event);

		fw_event_work_put(fw_event);
	पूर्ण
	ioc->fw_events_cleanup = 0;
पूर्ण

/**
 * _scsih_पूर्णांकernal_device_block - block the sdev device
 * @sdev: per device object
 * @sas_device_priv_data : per device driver निजी data
 *
 * make sure device is blocked without error, अगर not
 * prपूर्णांक an error
 */
अटल व्योम
_scsih_पूर्णांकernal_device_block(काष्ठा scsi_device *sdev,
			काष्ठा MPT3SAS_DEVICE *sas_device_priv_data)
अणु
	पूर्णांक r = 0;

	sdev_prपूर्णांकk(KERN_INFO, sdev, "device_block, handle(0x%04x)\n",
	    sas_device_priv_data->sas_target->handle);
	sas_device_priv_data->block = 1;

	r = scsi_पूर्णांकernal_device_block_noरुको(sdev);
	अगर (r == -EINVAL)
		sdev_prपूर्णांकk(KERN_WARNING, sdev,
		    "device_block failed with return(%d) for handle(0x%04x)\n",
		    r, sas_device_priv_data->sas_target->handle);
पूर्ण

/**
 * _scsih_पूर्णांकernal_device_unblock - unblock the sdev device
 * @sdev: per device object
 * @sas_device_priv_data : per device driver निजी data
 * make sure device is unblocked without error, अगर not retry
 * by blocking and then unblocking
 */

अटल व्योम
_scsih_पूर्णांकernal_device_unblock(काष्ठा scsi_device *sdev,
			काष्ठा MPT3SAS_DEVICE *sas_device_priv_data)
अणु
	पूर्णांक r = 0;

	sdev_prपूर्णांकk(KERN_WARNING, sdev, "device_unblock and setting to running, "
	    "handle(0x%04x)\n", sas_device_priv_data->sas_target->handle);
	sas_device_priv_data->block = 0;
	r = scsi_पूर्णांकernal_device_unblock_noरुको(sdev, SDEV_RUNNING);
	अगर (r == -EINVAL) अणु
		/* The device has been set to SDEV_RUNNING by SD layer during
		 * device addition but the request queue is still stopped by
		 * our earlier block call. We need to perक्रमm a block again
		 * to get the device to SDEV_BLOCK and then to SDEV_RUNNING */

		sdev_prपूर्णांकk(KERN_WARNING, sdev,
		    "device_unblock failed with return(%d) for handle(0x%04x) "
		    "performing a block followed by an unblock\n",
		    r, sas_device_priv_data->sas_target->handle);
		sas_device_priv_data->block = 1;
		r = scsi_पूर्णांकernal_device_block_noरुको(sdev);
		अगर (r)
			sdev_prपूर्णांकk(KERN_WARNING, sdev, "retried device_block "
			    "failed with return(%d) for handle(0x%04x)\n",
			    r, sas_device_priv_data->sas_target->handle);

		sas_device_priv_data->block = 0;
		r = scsi_पूर्णांकernal_device_unblock_noरुको(sdev, SDEV_RUNNING);
		अगर (r)
			sdev_prपूर्णांकk(KERN_WARNING, sdev, "retried device_unblock"
			    " failed with return(%d) for handle(0x%04x)\n",
			    r, sas_device_priv_data->sas_target->handle);
	पूर्ण
पूर्ण

/**
 * _scsih_ublock_io_all_device - unblock every device
 * @ioc: per adapter object
 *
 * change the device state from block to running
 */
अटल व्योम
_scsih_ublock_io_all_device(काष्ठा MPT3SAS_ADAPTER *ioc)
अणु
	काष्ठा MPT3SAS_DEVICE *sas_device_priv_data;
	काष्ठा scsi_device *sdev;

	shost_क्रम_each_device(sdev, ioc->shost) अणु
		sas_device_priv_data = sdev->hostdata;
		अगर (!sas_device_priv_data)
			जारी;
		अगर (!sas_device_priv_data->block)
			जारी;

		dewtprपूर्णांकk(ioc, sdev_prपूर्णांकk(KERN_INFO, sdev,
			"device_running, handle(0x%04x)\n",
		    sas_device_priv_data->sas_target->handle));
		_scsih_पूर्णांकernal_device_unblock(sdev, sas_device_priv_data);
	पूर्ण
पूर्ण


/**
 * _scsih_ublock_io_device - prepare device to be deleted
 * @ioc: per adapter object
 * @sas_address: sas address
 * @port: hba port entry
 *
 * unblock then put device in offline state
 */
अटल व्योम
_scsih_ublock_io_device(काष्ठा MPT3SAS_ADAPTER *ioc,
	u64 sas_address, काष्ठा hba_port *port)
अणु
	काष्ठा MPT3SAS_DEVICE *sas_device_priv_data;
	काष्ठा scsi_device *sdev;

	shost_क्रम_each_device(sdev, ioc->shost) अणु
		sas_device_priv_data = sdev->hostdata;
		अगर (!sas_device_priv_data)
			जारी;
		अगर (sas_device_priv_data->sas_target->sas_address
		    != sas_address)
			जारी;
		अगर (sas_device_priv_data->sas_target->port != port)
			जारी;
		अगर (sas_device_priv_data->block)
			_scsih_पूर्णांकernal_device_unblock(sdev,
				sas_device_priv_data);
	पूर्ण
पूर्ण

/**
 * _scsih_block_io_all_device - set the device state to SDEV_BLOCK
 * @ioc: per adapter object
 *
 * During device pull we need to appropriately set the sdev state.
 */
अटल व्योम
_scsih_block_io_all_device(काष्ठा MPT3SAS_ADAPTER *ioc)
अणु
	काष्ठा MPT3SAS_DEVICE *sas_device_priv_data;
	काष्ठा scsi_device *sdev;

	shost_क्रम_each_device(sdev, ioc->shost) अणु
		sas_device_priv_data = sdev->hostdata;
		अगर (!sas_device_priv_data)
			जारी;
		अगर (sas_device_priv_data->block)
			जारी;
		अगर (sas_device_priv_data->ignore_delay_हटाओ) अणु
			sdev_prपूर्णांकk(KERN_INFO, sdev,
			"%s skip device_block for SES handle(0x%04x)\n",
			__func__, sas_device_priv_data->sas_target->handle);
			जारी;
		पूर्ण
		_scsih_पूर्णांकernal_device_block(sdev, sas_device_priv_data);
	पूर्ण
पूर्ण

/**
 * _scsih_block_io_device - set the device state to SDEV_BLOCK
 * @ioc: per adapter object
 * @handle: device handle
 *
 * During device pull we need to appropriately set the sdev state.
 */
अटल व्योम
_scsih_block_io_device(काष्ठा MPT3SAS_ADAPTER *ioc, u16 handle)
अणु
	काष्ठा MPT3SAS_DEVICE *sas_device_priv_data;
	काष्ठा scsi_device *sdev;
	काष्ठा _sas_device *sas_device;

	sas_device = mpt3sas_get_sdev_by_handle(ioc, handle);

	shost_क्रम_each_device(sdev, ioc->shost) अणु
		sas_device_priv_data = sdev->hostdata;
		अगर (!sas_device_priv_data)
			जारी;
		अगर (sas_device_priv_data->sas_target->handle != handle)
			जारी;
		अगर (sas_device_priv_data->block)
			जारी;
		अगर (sas_device && sas_device->pend_sas_rphy_add)
			जारी;
		अगर (sas_device_priv_data->ignore_delay_हटाओ) अणु
			sdev_prपूर्णांकk(KERN_INFO, sdev,
			"%s skip device_block for SES handle(0x%04x)\n",
			__func__, sas_device_priv_data->sas_target->handle);
			जारी;
		पूर्ण
		_scsih_पूर्णांकernal_device_block(sdev, sas_device_priv_data);
	पूर्ण

	अगर (sas_device)
		sas_device_put(sas_device);
पूर्ण

/**
 * _scsih_block_io_to_children_attached_to_ex
 * @ioc: per adapter object
 * @sas_expander: the sas_device object
 *
 * This routine set sdev state to SDEV_BLOCK क्रम all devices
 * attached to this expander. This function called when expander is
 * pulled.
 */
अटल व्योम
_scsih_block_io_to_children_attached_to_ex(काष्ठा MPT3SAS_ADAPTER *ioc,
	काष्ठा _sas_node *sas_expander)
अणु
	काष्ठा _sas_port *mpt3sas_port;
	काष्ठा _sas_device *sas_device;
	काष्ठा _sas_node *expander_sibling;
	अचिन्हित दीर्घ flags;

	अगर (!sas_expander)
		वापस;

	list_क्रम_each_entry(mpt3sas_port,
	   &sas_expander->sas_port_list, port_list) अणु
		अगर (mpt3sas_port->remote_identअगरy.device_type ==
		    SAS_END_DEVICE) अणु
			spin_lock_irqsave(&ioc->sas_device_lock, flags);
			sas_device = __mpt3sas_get_sdev_by_addr(ioc,
			    mpt3sas_port->remote_identअगरy.sas_address,
			    mpt3sas_port->hba_port);
			अगर (sas_device) अणु
				set_bit(sas_device->handle,
						ioc->blocking_handles);
				sas_device_put(sas_device);
			पूर्ण
			spin_unlock_irqrestore(&ioc->sas_device_lock, flags);
		पूर्ण
	पूर्ण

	list_क्रम_each_entry(mpt3sas_port,
	   &sas_expander->sas_port_list, port_list) अणु

		अगर (mpt3sas_port->remote_identअगरy.device_type ==
		    SAS_EDGE_EXPANDER_DEVICE ||
		    mpt3sas_port->remote_identअगरy.device_type ==
		    SAS_FANOUT_EXPANDER_DEVICE) अणु
			expander_sibling =
			    mpt3sas_scsih_expander_find_by_sas_address(
			    ioc, mpt3sas_port->remote_identअगरy.sas_address,
			    mpt3sas_port->hba_port);
			_scsih_block_io_to_children_attached_to_ex(ioc,
			    expander_sibling);
		पूर्ण
	पूर्ण
पूर्ण

/**
 * _scsih_block_io_to_children_attached_directly
 * @ioc: per adapter object
 * @event_data: topology change event data
 *
 * This routine set sdev state to SDEV_BLOCK क्रम all devices
 * direct attached during device pull.
 */
अटल व्योम
_scsih_block_io_to_children_attached_directly(काष्ठा MPT3SAS_ADAPTER *ioc,
	Mpi2EventDataSasTopologyChangeList_t *event_data)
अणु
	पूर्णांक i;
	u16 handle;
	u16 reason_code;

	क्रम (i = 0; i < event_data->NumEntries; i++) अणु
		handle = le16_to_cpu(event_data->PHY[i].AttachedDevHandle);
		अगर (!handle)
			जारी;
		reason_code = event_data->PHY[i].PhyStatus &
		    MPI2_EVENT_SAS_TOPO_RC_MASK;
		अगर (reason_code == MPI2_EVENT_SAS_TOPO_RC_DELAY_NOT_RESPONDING)
			_scsih_block_io_device(ioc, handle);
	पूर्ण
पूर्ण

/**
 * _scsih_block_io_to_pcie_children_attached_directly
 * @ioc: per adapter object
 * @event_data: topology change event data
 *
 * This routine set sdev state to SDEV_BLOCK क्रम all devices
 * direct attached during device pull/reconnect.
 */
अटल व्योम
_scsih_block_io_to_pcie_children_attached_directly(काष्ठा MPT3SAS_ADAPTER *ioc,
		Mpi26EventDataPCIeTopologyChangeList_t *event_data)
अणु
	पूर्णांक i;
	u16 handle;
	u16 reason_code;

	क्रम (i = 0; i < event_data->NumEntries; i++) अणु
		handle =
			le16_to_cpu(event_data->PortEntry[i].AttachedDevHandle);
		अगर (!handle)
			जारी;
		reason_code = event_data->PortEntry[i].PortStatus;
		अगर (reason_code ==
				MPI26_EVENT_PCIE_TOPO_PS_DELAY_NOT_RESPONDING)
			_scsih_block_io_device(ioc, handle);
	पूर्ण
पूर्ण
/**
 * _scsih_पंचांग_tr_send - send task management request
 * @ioc: per adapter object
 * @handle: device handle
 * Context: पूर्णांकerrupt समय.
 *
 * This code is to initiate the device removal handshake protocol
 * with controller firmware.  This function will issue target reset
 * using high priority request queue.  It will send a sas iounit
 * control request (MPI2_SAS_OP_REMOVE_DEVICE) from this completion.
 *
 * This is deचिन्हित to send muliple task management request at the same
 * समय to the fअगरo. If the fअगरo is full, we will append the request,
 * and process it in a future completion.
 */
अटल व्योम
_scsih_पंचांग_tr_send(काष्ठा MPT3SAS_ADAPTER *ioc, u16 handle)
अणु
	Mpi2SCSITaskManagementRequest_t *mpi_request;
	u16 smid;
	काष्ठा _sas_device *sas_device = शून्य;
	काष्ठा _pcie_device *pcie_device = शून्य;
	काष्ठा MPT3SAS_TARGET *sas_target_priv_data = शून्य;
	u64 sas_address = 0;
	अचिन्हित दीर्घ flags;
	काष्ठा _tr_list *delayed_tr;
	u32 ioc_state;
	u8 tr_method = 0;
	काष्ठा hba_port *port = शून्य;

	अगर (ioc->pci_error_recovery) अणु
		dewtprपूर्णांकk(ioc,
			   ioc_info(ioc, "%s: host in pci error recovery: handle(0x%04x)\n",
				    __func__, handle));
		वापस;
	पूर्ण
	ioc_state = mpt3sas_base_get_iocstate(ioc, 1);
	अगर (ioc_state != MPI2_IOC_STATE_OPERATIONAL) अणु
		dewtprपूर्णांकk(ioc,
			   ioc_info(ioc, "%s: host is not operational: handle(0x%04x)\n",
				    __func__, handle));
		वापस;
	पूर्ण

	/* अगर PD, then वापस */
	अगर (test_bit(handle, ioc->pd_handles))
		वापस;

	clear_bit(handle, ioc->pend_os_device_add);

	spin_lock_irqsave(&ioc->sas_device_lock, flags);
	sas_device = __mpt3sas_get_sdev_by_handle(ioc, handle);
	अगर (sas_device && sas_device->starget &&
	    sas_device->starget->hostdata) अणु
		sas_target_priv_data = sas_device->starget->hostdata;
		sas_target_priv_data->deleted = 1;
		sas_address = sas_device->sas_address;
		port = sas_device->port;
	पूर्ण
	spin_unlock_irqrestore(&ioc->sas_device_lock, flags);
	अगर (!sas_device) अणु
		spin_lock_irqsave(&ioc->pcie_device_lock, flags);
		pcie_device = __mpt3sas_get_pdev_by_handle(ioc, handle);
		अगर (pcie_device && pcie_device->starget &&
			pcie_device->starget->hostdata) अणु
			sas_target_priv_data = pcie_device->starget->hostdata;
			sas_target_priv_data->deleted = 1;
			sas_address = pcie_device->wwid;
		पूर्ण
		spin_unlock_irqrestore(&ioc->pcie_device_lock, flags);
		अगर (pcie_device && (!ioc->पंचांग_custom_handling) &&
		    (!(mpt3sas_scsih_is_pcie_scsi_device(
		    pcie_device->device_info))))
			tr_method =
			    MPI26_SCSITASKMGMT_MSGFLAGS_PROTOCOL_LVL_RST_PCIE;
		अन्यथा
			tr_method = MPI2_SCSITASKMGMT_MSGFLAGS_LINK_RESET;
	पूर्ण
	अगर (sas_target_priv_data) अणु
		dewtprपूर्णांकk(ioc,
			   ioc_info(ioc, "setting delete flag: handle(0x%04x), sas_addr(0x%016llx)\n",
				    handle, (u64)sas_address));
		अगर (sas_device) अणु
			अगर (sas_device->enclosure_handle != 0)
				dewtprपूर्णांकk(ioc,
					   ioc_info(ioc, "setting delete flag:enclosure logical id(0x%016llx), slot(%d)\n",
						    (u64)sas_device->enclosure_logical_id,
						    sas_device->slot));
			अगर (sas_device->connector_name[0] != '\0')
				dewtprपूर्णांकk(ioc,
					   ioc_info(ioc, "setting delete flag: enclosure level(0x%04x), connector name( %s)\n",
						    sas_device->enclosure_level,
						    sas_device->connector_name));
		पूर्ण अन्यथा अगर (pcie_device) अणु
			अगर (pcie_device->enclosure_handle != 0)
				dewtprपूर्णांकk(ioc,
					   ioc_info(ioc, "setting delete flag: logical id(0x%016llx), slot(%d)\n",
						    (u64)pcie_device->enclosure_logical_id,
						    pcie_device->slot));
			अगर (pcie_device->connector_name[0] != '\0')
				dewtprपूर्णांकk(ioc,
					   ioc_info(ioc, "setting delete flag:, enclosure level(0x%04x), connector name( %s)\n",
						    pcie_device->enclosure_level,
						    pcie_device->connector_name));
		पूर्ण
		_scsih_ublock_io_device(ioc, sas_address, port);
		sas_target_priv_data->handle = MPT3SAS_INVALID_DEVICE_HANDLE;
	पूर्ण

	smid = mpt3sas_base_get_smid_hpr(ioc, ioc->पंचांग_tr_cb_idx);
	अगर (!smid) अणु
		delayed_tr = kzalloc(माप(*delayed_tr), GFP_ATOMIC);
		अगर (!delayed_tr)
			जाओ out;
		INIT_LIST_HEAD(&delayed_tr->list);
		delayed_tr->handle = handle;
		list_add_tail(&delayed_tr->list, &ioc->delayed_tr_list);
		dewtprपूर्णांकk(ioc,
			   ioc_info(ioc, "DELAYED:tr:handle(0x%04x), (open)\n",
				    handle));
		जाओ out;
	पूर्ण

	dewtprपूर्णांकk(ioc,
		   ioc_info(ioc, "tr_send:handle(0x%04x), (open), smid(%d), cb(%d)\n",
			    handle, smid, ioc->पंचांग_tr_cb_idx));
	mpi_request = mpt3sas_base_get_msg_frame(ioc, smid);
	स_रखो(mpi_request, 0, माप(Mpi2SCSITaskManagementRequest_t));
	mpi_request->Function = MPI2_FUNCTION_SCSI_TASK_MGMT;
	mpi_request->DevHandle = cpu_to_le16(handle);
	mpi_request->TaskType = MPI2_SCSITASKMGMT_TASKTYPE_TARGET_RESET;
	mpi_request->MsgFlags = tr_method;
	set_bit(handle, ioc->device_हटाओ_in_progress);
	ioc->put_smid_hi_priority(ioc, smid, 0);
	mpt3sas_trigger_master(ioc, MASTER_TRIGGER_DEVICE_REMOVAL);

out:
	अगर (sas_device)
		sas_device_put(sas_device);
	अगर (pcie_device)
		pcie_device_put(pcie_device);
पूर्ण

/**
 * _scsih_पंचांग_tr_complete -
 * @ioc: per adapter object
 * @smid: प्रणाली request message index
 * @msix_index: MSIX table index supplied by the OS
 * @reply: reply message frame(lower 32bit addr)
 * Context: पूर्णांकerrupt समय.
 *
 * This is the target reset completion routine.
 * This code is part of the code to initiate the device removal
 * handshake protocol with controller firmware.
 * It will send a sas iounit control request (MPI2_SAS_OP_REMOVE_DEVICE)
 *
 * Return: 1 meaning mf should be मुक्तd from _base_पूर्णांकerrupt
 *         0 means the mf is मुक्तd from this function.
 */
अटल u8
_scsih_पंचांग_tr_complete(काष्ठा MPT3SAS_ADAPTER *ioc, u16 smid, u8 msix_index,
	u32 reply)
अणु
	u16 handle;
	Mpi2SCSITaskManagementRequest_t *mpi_request_पंचांग;
	Mpi2SCSITaskManagementReply_t *mpi_reply =
	    mpt3sas_base_get_reply_virt_addr(ioc, reply);
	Mpi2SasIoUnitControlRequest_t *mpi_request;
	u16 smid_sas_ctrl;
	u32 ioc_state;
	काष्ठा _sc_list *delayed_sc;

	अगर (ioc->pci_error_recovery) अणु
		dewtprपूर्णांकk(ioc,
			   ioc_info(ioc, "%s: host in pci error recovery\n",
				    __func__));
		वापस 1;
	पूर्ण
	ioc_state = mpt3sas_base_get_iocstate(ioc, 1);
	अगर (ioc_state != MPI2_IOC_STATE_OPERATIONAL) अणु
		dewtprपूर्णांकk(ioc,
			   ioc_info(ioc, "%s: host is not operational\n",
				    __func__));
		वापस 1;
	पूर्ण
	अगर (unlikely(!mpi_reply)) अणु
		ioc_err(ioc, "mpi_reply not valid at %s:%d/%s()!\n",
			__खाता__, __LINE__, __func__);
		वापस 1;
	पूर्ण
	mpi_request_पंचांग = mpt3sas_base_get_msg_frame(ioc, smid);
	handle = le16_to_cpu(mpi_request_पंचांग->DevHandle);
	अगर (handle != le16_to_cpu(mpi_reply->DevHandle)) अणु
		dewtprपूर्णांकk(ioc,
			   ioc_err(ioc, "spurious interrupt: handle(0x%04x:0x%04x), smid(%d)!!!\n",
				   handle,
				   le16_to_cpu(mpi_reply->DevHandle), smid));
		वापस 0;
	पूर्ण

	mpt3sas_trigger_master(ioc, MASTER_TRIGGER_TASK_MANAGMENT);
	dewtprपूर्णांकk(ioc,
		   ioc_info(ioc, "tr_complete:handle(0x%04x), (open) smid(%d), ioc_status(0x%04x), loginfo(0x%08x), completed(%d)\n",
			    handle, smid, le16_to_cpu(mpi_reply->IOCStatus),
			    le32_to_cpu(mpi_reply->IOCLogInfo),
			    le32_to_cpu(mpi_reply->TerminationCount)));

	smid_sas_ctrl = mpt3sas_base_get_smid(ioc, ioc->पंचांग_sas_control_cb_idx);
	अगर (!smid_sas_ctrl) अणु
		delayed_sc = kzalloc(माप(*delayed_sc), GFP_ATOMIC);
		अगर (!delayed_sc)
			वापस _scsih_check_क्रम_pending_पंचांग(ioc, smid);
		INIT_LIST_HEAD(&delayed_sc->list);
		delayed_sc->handle = le16_to_cpu(mpi_request_पंचांग->DevHandle);
		list_add_tail(&delayed_sc->list, &ioc->delayed_sc_list);
		dewtprपूर्णांकk(ioc,
			   ioc_info(ioc, "DELAYED:sc:handle(0x%04x), (open)\n",
				    handle));
		वापस _scsih_check_क्रम_pending_पंचांग(ioc, smid);
	पूर्ण

	dewtprपूर्णांकk(ioc,
		   ioc_info(ioc, "sc_send:handle(0x%04x), (open), smid(%d), cb(%d)\n",
			    handle, smid_sas_ctrl, ioc->पंचांग_sas_control_cb_idx));
	mpi_request = mpt3sas_base_get_msg_frame(ioc, smid_sas_ctrl);
	स_रखो(mpi_request, 0, माप(Mpi2SasIoUnitControlRequest_t));
	mpi_request->Function = MPI2_FUNCTION_SAS_IO_UNIT_CONTROL;
	mpi_request->Operation = MPI2_SAS_OP_REMOVE_DEVICE;
	mpi_request->DevHandle = mpi_request_पंचांग->DevHandle;
	ioc->put_smid_शेष(ioc, smid_sas_ctrl);

	वापस _scsih_check_क्रम_pending_पंचांग(ioc, smid);
पूर्ण

/** _scsih_allow_scmd_to_device - check whether scmd needs to
 *				 issue to IOC or not.
 * @ioc: per adapter object
 * @scmd: poपूर्णांकer to scsi command object
 *
 * Returns true अगर scmd can be issued to IOC otherwise वापसs false.
 */
अंतरभूत bool _scsih_allow_scmd_to_device(काष्ठा MPT3SAS_ADAPTER *ioc,
	काष्ठा scsi_cmnd *scmd)
अणु

	अगर (ioc->pci_error_recovery)
		वापस false;

	अगर (ioc->hba_mpi_version_beदीर्घed == MPI2_VERSION) अणु
		अगर (ioc->हटाओ_host)
			वापस false;

		वापस true;
	पूर्ण

	अगर (ioc->हटाओ_host) अणु

		चयन (scmd->cmnd[0]) अणु
		हाल SYNCHRONIZE_CACHE:
		हाल START_STOP:
			वापस true;
		शेष:
			वापस false;
		पूर्ण
	पूर्ण

	वापस true;
पूर्ण

/**
 * _scsih_sas_control_complete - completion routine
 * @ioc: per adapter object
 * @smid: प्रणाली request message index
 * @msix_index: MSIX table index supplied by the OS
 * @reply: reply message frame(lower 32bit addr)
 * Context: पूर्णांकerrupt समय.
 *
 * This is the sas iounit control completion routine.
 * This code is part of the code to initiate the device removal
 * handshake protocol with controller firmware.
 *
 * Return: 1 meaning mf should be मुक्तd from _base_पूर्णांकerrupt
 *         0 means the mf is मुक्तd from this function.
 */
अटल u8
_scsih_sas_control_complete(काष्ठा MPT3SAS_ADAPTER *ioc, u16 smid,
	u8 msix_index, u32 reply)
अणु
	Mpi2SasIoUnitControlReply_t *mpi_reply =
	    mpt3sas_base_get_reply_virt_addr(ioc, reply);

	अगर (likely(mpi_reply)) अणु
		dewtprपूर्णांकk(ioc,
			   ioc_info(ioc, "sc_complete:handle(0x%04x), (open) smid(%d), ioc_status(0x%04x), loginfo(0x%08x)\n",
				    le16_to_cpu(mpi_reply->DevHandle), smid,
				    le16_to_cpu(mpi_reply->IOCStatus),
				    le32_to_cpu(mpi_reply->IOCLogInfo)));
		अगर (le16_to_cpu(mpi_reply->IOCStatus) ==
		     MPI2_IOCSTATUS_SUCCESS) अणु
			clear_bit(le16_to_cpu(mpi_reply->DevHandle),
			    ioc->device_हटाओ_in_progress);
		पूर्ण
	पूर्ण अन्यथा अणु
		ioc_err(ioc, "mpi_reply not valid at %s:%d/%s()!\n",
			__खाता__, __LINE__, __func__);
	पूर्ण
	वापस mpt3sas_check_क्रम_pending_पूर्णांकernal_cmds(ioc, smid);
पूर्ण

/**
 * _scsih_पंचांग_tr_volume_send - send target reset request क्रम volumes
 * @ioc: per adapter object
 * @handle: device handle
 * Context: पूर्णांकerrupt समय.
 *
 * This is deचिन्हित to send muliple task management request at the same
 * समय to the fअगरo. If the fअगरo is full, we will append the request,
 * and process it in a future completion.
 */
अटल व्योम
_scsih_पंचांग_tr_volume_send(काष्ठा MPT3SAS_ADAPTER *ioc, u16 handle)
अणु
	Mpi2SCSITaskManagementRequest_t *mpi_request;
	u16 smid;
	काष्ठा _tr_list *delayed_tr;

	अगर (ioc->pci_error_recovery) अणु
		dewtprपूर्णांकk(ioc,
			   ioc_info(ioc, "%s: host reset in progress!\n",
				    __func__));
		वापस;
	पूर्ण

	smid = mpt3sas_base_get_smid_hpr(ioc, ioc->पंचांग_tr_volume_cb_idx);
	अगर (!smid) अणु
		delayed_tr = kzalloc(माप(*delayed_tr), GFP_ATOMIC);
		अगर (!delayed_tr)
			वापस;
		INIT_LIST_HEAD(&delayed_tr->list);
		delayed_tr->handle = handle;
		list_add_tail(&delayed_tr->list, &ioc->delayed_tr_volume_list);
		dewtprपूर्णांकk(ioc,
			   ioc_info(ioc, "DELAYED:tr:handle(0x%04x), (open)\n",
				    handle));
		वापस;
	पूर्ण

	dewtprपूर्णांकk(ioc,
		   ioc_info(ioc, "tr_send:handle(0x%04x), (open), smid(%d), cb(%d)\n",
			    handle, smid, ioc->पंचांग_tr_volume_cb_idx));
	mpi_request = mpt3sas_base_get_msg_frame(ioc, smid);
	स_रखो(mpi_request, 0, माप(Mpi2SCSITaskManagementRequest_t));
	mpi_request->Function = MPI2_FUNCTION_SCSI_TASK_MGMT;
	mpi_request->DevHandle = cpu_to_le16(handle);
	mpi_request->TaskType = MPI2_SCSITASKMGMT_TASKTYPE_TARGET_RESET;
	ioc->put_smid_hi_priority(ioc, smid, 0);
पूर्ण

/**
 * _scsih_पंचांग_volume_tr_complete - target reset completion
 * @ioc: per adapter object
 * @smid: प्रणाली request message index
 * @msix_index: MSIX table index supplied by the OS
 * @reply: reply message frame(lower 32bit addr)
 * Context: पूर्णांकerrupt समय.
 *
 * Return: 1 meaning mf should be मुक्तd from _base_पूर्णांकerrupt
 *         0 means the mf is मुक्तd from this function.
 */
अटल u8
_scsih_पंचांग_volume_tr_complete(काष्ठा MPT3SAS_ADAPTER *ioc, u16 smid,
	u8 msix_index, u32 reply)
अणु
	u16 handle;
	Mpi2SCSITaskManagementRequest_t *mpi_request_पंचांग;
	Mpi2SCSITaskManagementReply_t *mpi_reply =
	    mpt3sas_base_get_reply_virt_addr(ioc, reply);

	अगर (ioc->shost_recovery || ioc->pci_error_recovery) अणु
		dewtprपूर्णांकk(ioc,
			   ioc_info(ioc, "%s: host reset in progress!\n",
				    __func__));
		वापस 1;
	पूर्ण
	अगर (unlikely(!mpi_reply)) अणु
		ioc_err(ioc, "mpi_reply not valid at %s:%d/%s()!\n",
			__खाता__, __LINE__, __func__);
		वापस 1;
	पूर्ण

	mpi_request_पंचांग = mpt3sas_base_get_msg_frame(ioc, smid);
	handle = le16_to_cpu(mpi_request_पंचांग->DevHandle);
	अगर (handle != le16_to_cpu(mpi_reply->DevHandle)) अणु
		dewtprपूर्णांकk(ioc,
			   ioc_err(ioc, "spurious interrupt: handle(0x%04x:0x%04x), smid(%d)!!!\n",
				   handle, le16_to_cpu(mpi_reply->DevHandle),
				   smid));
		वापस 0;
	पूर्ण

	dewtprपूर्णांकk(ioc,
		   ioc_info(ioc, "tr_complete:handle(0x%04x), (open) smid(%d), ioc_status(0x%04x), loginfo(0x%08x), completed(%d)\n",
			    handle, smid, le16_to_cpu(mpi_reply->IOCStatus),
			    le32_to_cpu(mpi_reply->IOCLogInfo),
			    le32_to_cpu(mpi_reply->TerminationCount)));

	वापस _scsih_check_क्रम_pending_पंचांग(ioc, smid);
पूर्ण

/**
 * _scsih_issue_delayed_event_ack - issue delayed Event ACK messages
 * @ioc: per adapter object
 * @smid: प्रणाली request message index
 * @event: Event ID
 * @event_context: used to track events uniquely
 *
 * Context - processed in पूर्णांकerrupt context.
 */
अटल व्योम
_scsih_issue_delayed_event_ack(काष्ठा MPT3SAS_ADAPTER *ioc, u16 smid, U16 event,
				U32 event_context)
अणु
	Mpi2EventAckRequest_t *ack_request;
	पूर्णांक i = smid - ioc->पूर्णांकernal_smid;
	अचिन्हित दीर्घ flags;

	/* Without releasing the smid just update the
	 * call back index and reuse the same smid क्रम
	 * processing this delayed request
	 */
	spin_lock_irqsave(&ioc->scsi_lookup_lock, flags);
	ioc->पूर्णांकernal_lookup[i].cb_idx = ioc->base_cb_idx;
	spin_unlock_irqrestore(&ioc->scsi_lookup_lock, flags);

	dewtprपूर्णांकk(ioc,
		   ioc_info(ioc, "EVENT ACK: event(0x%04x), smid(%d), cb(%d)\n",
			    le16_to_cpu(event), smid, ioc->base_cb_idx));
	ack_request = mpt3sas_base_get_msg_frame(ioc, smid);
	स_रखो(ack_request, 0, माप(Mpi2EventAckRequest_t));
	ack_request->Function = MPI2_FUNCTION_EVENT_ACK;
	ack_request->Event = event;
	ack_request->EventContext = event_context;
	ack_request->VF_ID = 0;  /* TODO */
	ack_request->VP_ID = 0;
	ioc->put_smid_शेष(ioc, smid);
पूर्ण

/**
 * _scsih_issue_delayed_sas_io_unit_ctrl - issue delayed
 *				sas_io_unit_ctrl messages
 * @ioc: per adapter object
 * @smid: प्रणाली request message index
 * @handle: device handle
 *
 * Context - processed in पूर्णांकerrupt context.
 */
अटल व्योम
_scsih_issue_delayed_sas_io_unit_ctrl(काष्ठा MPT3SAS_ADAPTER *ioc,
					u16 smid, u16 handle)
अणु
	Mpi2SasIoUnitControlRequest_t *mpi_request;
	u32 ioc_state;
	पूर्णांक i = smid - ioc->पूर्णांकernal_smid;
	अचिन्हित दीर्घ flags;

	अगर (ioc->हटाओ_host) अणु
		dewtprपूर्णांकk(ioc,
			   ioc_info(ioc, "%s: host has been removed\n",
				    __func__));
		वापस;
	पूर्ण अन्यथा अगर (ioc->pci_error_recovery) अणु
		dewtprपूर्णांकk(ioc,
			   ioc_info(ioc, "%s: host in pci error recovery\n",
				    __func__));
		वापस;
	पूर्ण
	ioc_state = mpt3sas_base_get_iocstate(ioc, 1);
	अगर (ioc_state != MPI2_IOC_STATE_OPERATIONAL) अणु
		dewtprपूर्णांकk(ioc,
			   ioc_info(ioc, "%s: host is not operational\n",
				    __func__));
		वापस;
	पूर्ण

	/* Without releasing the smid just update the
	 * call back index and reuse the same smid क्रम
	 * processing this delayed request
	 */
	spin_lock_irqsave(&ioc->scsi_lookup_lock, flags);
	ioc->पूर्णांकernal_lookup[i].cb_idx = ioc->पंचांग_sas_control_cb_idx;
	spin_unlock_irqrestore(&ioc->scsi_lookup_lock, flags);

	dewtprपूर्णांकk(ioc,
		   ioc_info(ioc, "sc_send:handle(0x%04x), (open), smid(%d), cb(%d)\n",
			    handle, smid, ioc->पंचांग_sas_control_cb_idx));
	mpi_request = mpt3sas_base_get_msg_frame(ioc, smid);
	स_रखो(mpi_request, 0, माप(Mpi2SasIoUnitControlRequest_t));
	mpi_request->Function = MPI2_FUNCTION_SAS_IO_UNIT_CONTROL;
	mpi_request->Operation = MPI2_SAS_OP_REMOVE_DEVICE;
	mpi_request->DevHandle = cpu_to_le16(handle);
	ioc->put_smid_शेष(ioc, smid);
पूर्ण

/**
 * mpt3sas_check_क्रम_pending_पूर्णांकernal_cmds - check क्रम pending पूर्णांकernal messages
 * @ioc: per adapter object
 * @smid: प्रणाली request message index
 *
 * Context: Executed in पूर्णांकerrupt context
 *
 * This will check delayed पूर्णांकernal messages list, and process the
 * next request.
 *
 * Return: 1 meaning mf should be मुक्तd from _base_पूर्णांकerrupt
 *         0 means the mf is मुक्तd from this function.
 */
u8
mpt3sas_check_क्रम_pending_पूर्णांकernal_cmds(काष्ठा MPT3SAS_ADAPTER *ioc, u16 smid)
अणु
	काष्ठा _sc_list *delayed_sc;
	काष्ठा _event_ack_list *delayed_event_ack;

	अगर (!list_empty(&ioc->delayed_event_ack_list)) अणु
		delayed_event_ack = list_entry(ioc->delayed_event_ack_list.next,
						काष्ठा _event_ack_list, list);
		_scsih_issue_delayed_event_ack(ioc, smid,
		  delayed_event_ack->Event, delayed_event_ack->EventContext);
		list_del(&delayed_event_ack->list);
		kमुक्त(delayed_event_ack);
		वापस 0;
	पूर्ण

	अगर (!list_empty(&ioc->delayed_sc_list)) अणु
		delayed_sc = list_entry(ioc->delayed_sc_list.next,
						काष्ठा _sc_list, list);
		_scsih_issue_delayed_sas_io_unit_ctrl(ioc, smid,
						 delayed_sc->handle);
		list_del(&delayed_sc->list);
		kमुक्त(delayed_sc);
		वापस 0;
	पूर्ण
	वापस 1;
पूर्ण

/**
 * _scsih_check_क्रम_pending_पंचांग - check क्रम pending task management
 * @ioc: per adapter object
 * @smid: प्रणाली request message index
 *
 * This will check delayed target reset list, and feed the
 * next reqeust.
 *
 * Return: 1 meaning mf should be मुक्तd from _base_पूर्णांकerrupt
 *         0 means the mf is मुक्तd from this function.
 */
अटल u8
_scsih_check_क्रम_pending_पंचांग(काष्ठा MPT3SAS_ADAPTER *ioc, u16 smid)
अणु
	काष्ठा _tr_list *delayed_tr;

	अगर (!list_empty(&ioc->delayed_tr_volume_list)) अणु
		delayed_tr = list_entry(ioc->delayed_tr_volume_list.next,
		    काष्ठा _tr_list, list);
		mpt3sas_base_मुक्त_smid(ioc, smid);
		_scsih_पंचांग_tr_volume_send(ioc, delayed_tr->handle);
		list_del(&delayed_tr->list);
		kमुक्त(delayed_tr);
		वापस 0;
	पूर्ण

	अगर (!list_empty(&ioc->delayed_tr_list)) अणु
		delayed_tr = list_entry(ioc->delayed_tr_list.next,
		    काष्ठा _tr_list, list);
		mpt3sas_base_मुक्त_smid(ioc, smid);
		_scsih_पंचांग_tr_send(ioc, delayed_tr->handle);
		list_del(&delayed_tr->list);
		kमुक्त(delayed_tr);
		वापस 0;
	पूर्ण

	वापस 1;
पूर्ण

/**
 * _scsih_check_topo_delete_events - sanity check on topo events
 * @ioc: per adapter object
 * @event_data: the event data payload
 *
 * This routine added to better handle cable अवरोधer.
 *
 * This handles the हाल where driver receives multiple expander
 * add and delete events in a single shot.  When there is a delete event
 * the routine will व्योम any pending add events रुकोing in the event queue.
 */
अटल व्योम
_scsih_check_topo_delete_events(काष्ठा MPT3SAS_ADAPTER *ioc,
	Mpi2EventDataSasTopologyChangeList_t *event_data)
अणु
	काष्ठा fw_event_work *fw_event;
	Mpi2EventDataSasTopologyChangeList_t *local_event_data;
	u16 expander_handle;
	काष्ठा _sas_node *sas_expander;
	अचिन्हित दीर्घ flags;
	पूर्णांक i, reason_code;
	u16 handle;

	क्रम (i = 0 ; i < event_data->NumEntries; i++) अणु
		handle = le16_to_cpu(event_data->PHY[i].AttachedDevHandle);
		अगर (!handle)
			जारी;
		reason_code = event_data->PHY[i].PhyStatus &
		    MPI2_EVENT_SAS_TOPO_RC_MASK;
		अगर (reason_code == MPI2_EVENT_SAS_TOPO_RC_TARG_NOT_RESPONDING)
			_scsih_पंचांग_tr_send(ioc, handle);
	पूर्ण

	expander_handle = le16_to_cpu(event_data->ExpanderDevHandle);
	अगर (expander_handle < ioc->sas_hba.num_phys) अणु
		_scsih_block_io_to_children_attached_directly(ioc, event_data);
		वापस;
	पूर्ण
	अगर (event_data->ExpStatus ==
	    MPI2_EVENT_SAS_TOPO_ES_DELAY_NOT_RESPONDING) अणु
		/* put expander attached devices पूर्णांकo blocking state */
		spin_lock_irqsave(&ioc->sas_node_lock, flags);
		sas_expander = mpt3sas_scsih_expander_find_by_handle(ioc,
		    expander_handle);
		_scsih_block_io_to_children_attached_to_ex(ioc, sas_expander);
		spin_unlock_irqrestore(&ioc->sas_node_lock, flags);
		करो अणु
			handle = find_first_bit(ioc->blocking_handles,
			    ioc->facts.MaxDevHandle);
			अगर (handle < ioc->facts.MaxDevHandle)
				_scsih_block_io_device(ioc, handle);
		पूर्ण जबतक (test_and_clear_bit(handle, ioc->blocking_handles));
	पूर्ण अन्यथा अगर (event_data->ExpStatus == MPI2_EVENT_SAS_TOPO_ES_RESPONDING)
		_scsih_block_io_to_children_attached_directly(ioc, event_data);

	अगर (event_data->ExpStatus != MPI2_EVENT_SAS_TOPO_ES_NOT_RESPONDING)
		वापस;

	/* mark ignore flag क्रम pending events */
	spin_lock_irqsave(&ioc->fw_event_lock, flags);
	list_क्रम_each_entry(fw_event, &ioc->fw_event_list, list) अणु
		अगर (fw_event->event != MPI2_EVENT_SAS_TOPOLOGY_CHANGE_LIST ||
		    fw_event->ignore)
			जारी;
		local_event_data = (Mpi2EventDataSasTopologyChangeList_t *)
				   fw_event->event_data;
		अगर (local_event_data->ExpStatus ==
		    MPI2_EVENT_SAS_TOPO_ES_ADDED ||
		    local_event_data->ExpStatus ==
		    MPI2_EVENT_SAS_TOPO_ES_RESPONDING) अणु
			अगर (le16_to_cpu(local_event_data->ExpanderDevHandle) ==
			    expander_handle) अणु
				dewtprपूर्णांकk(ioc,
					   ioc_info(ioc, "setting ignoring flag\n"));
				fw_event->ignore = 1;
			पूर्ण
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&ioc->fw_event_lock, flags);
पूर्ण

/**
 * _scsih_check_pcie_topo_हटाओ_events - sanity check on topo
 * events
 * @ioc: per adapter object
 * @event_data: the event data payload
 *
 * This handles the हाल where driver receives multiple चयन
 * or device add and delete events in a single shot.  When there
 * is a delete event the routine will व्योम any pending add
 * events रुकोing in the event queue.
 */
अटल व्योम
_scsih_check_pcie_topo_हटाओ_events(काष्ठा MPT3SAS_ADAPTER *ioc,
	Mpi26EventDataPCIeTopologyChangeList_t *event_data)
अणु
	काष्ठा fw_event_work *fw_event;
	Mpi26EventDataPCIeTopologyChangeList_t *local_event_data;
	अचिन्हित दीर्घ flags;
	पूर्णांक i, reason_code;
	u16 handle, चयन_handle;

	क्रम (i = 0; i < event_data->NumEntries; i++) अणु
		handle =
			le16_to_cpu(event_data->PortEntry[i].AttachedDevHandle);
		अगर (!handle)
			जारी;
		reason_code = event_data->PortEntry[i].PortStatus;
		अगर (reason_code == MPI26_EVENT_PCIE_TOPO_PS_NOT_RESPONDING)
			_scsih_पंचांग_tr_send(ioc, handle);
	पूर्ण

	चयन_handle = le16_to_cpu(event_data->SwitchDevHandle);
	अगर (!चयन_handle) अणु
		_scsih_block_io_to_pcie_children_attached_directly(
							ioc, event_data);
		वापस;
	पूर्ण
    /* TODO We are not supporting cascaded PCIe Switch removal yet*/
	अगर ((event_data->SwitchStatus
		== MPI26_EVENT_PCIE_TOPO_SS_DELAY_NOT_RESPONDING) ||
		(event_data->SwitchStatus ==
					MPI26_EVENT_PCIE_TOPO_SS_RESPONDING))
		_scsih_block_io_to_pcie_children_attached_directly(
							ioc, event_data);

	अगर (event_data->SwitchStatus != MPI2_EVENT_SAS_TOPO_ES_NOT_RESPONDING)
		वापस;

	/* mark ignore flag क्रम pending events */
	spin_lock_irqsave(&ioc->fw_event_lock, flags);
	list_क्रम_each_entry(fw_event, &ioc->fw_event_list, list) अणु
		अगर (fw_event->event != MPI2_EVENT_PCIE_TOPOLOGY_CHANGE_LIST ||
			fw_event->ignore)
			जारी;
		local_event_data =
			(Mpi26EventDataPCIeTopologyChangeList_t *)
			fw_event->event_data;
		अगर (local_event_data->SwitchStatus ==
		    MPI2_EVENT_SAS_TOPO_ES_ADDED ||
		    local_event_data->SwitchStatus ==
		    MPI2_EVENT_SAS_TOPO_ES_RESPONDING) अणु
			अगर (le16_to_cpu(local_event_data->SwitchDevHandle) ==
				चयन_handle) अणु
				dewtprपूर्णांकk(ioc,
					   ioc_info(ioc, "setting ignoring flag for switch event\n"));
				fw_event->ignore = 1;
			पूर्ण
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&ioc->fw_event_lock, flags);
पूर्ण

/**
 * _scsih_set_volume_delete_flag - setting volume delete flag
 * @ioc: per adapter object
 * @handle: device handle
 *
 * This वापसs nothing.
 */
अटल व्योम
_scsih_set_volume_delete_flag(काष्ठा MPT3SAS_ADAPTER *ioc, u16 handle)
अणु
	काष्ठा _raid_device *raid_device;
	काष्ठा MPT3SAS_TARGET *sas_target_priv_data;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ioc->raid_device_lock, flags);
	raid_device = mpt3sas_raid_device_find_by_handle(ioc, handle);
	अगर (raid_device && raid_device->starget &&
	    raid_device->starget->hostdata) अणु
		sas_target_priv_data =
		    raid_device->starget->hostdata;
		sas_target_priv_data->deleted = 1;
		dewtprपूर्णांकk(ioc,
			   ioc_info(ioc, "setting delete flag: handle(0x%04x), wwid(0x%016llx)\n",
				    handle, (u64)raid_device->wwid));
	पूर्ण
	spin_unlock_irqrestore(&ioc->raid_device_lock, flags);
पूर्ण

/**
 * _scsih_set_volume_handle_क्रम_tr - set handle क्रम target reset to volume
 * @handle: input handle
 * @a: handle क्रम volume a
 * @b: handle क्रम volume b
 *
 * IR firmware only supports two raid volumes.  The purpose of this
 * routine is to set the volume handle in either a or b. When the given
 * input handle is non-zero, or when a and b have not been set beक्रमe.
 */
अटल व्योम
_scsih_set_volume_handle_क्रम_tr(u16 handle, u16 *a, u16 *b)
अणु
	अगर (!handle || handle == *a || handle == *b)
		वापस;
	अगर (!*a)
		*a = handle;
	अन्यथा अगर (!*b)
		*b = handle;
पूर्ण

/**
 * _scsih_check_ir_config_unhide_events - check क्रम UNHIDE events
 * @ioc: per adapter object
 * @event_data: the event data payload
 * Context: पूर्णांकerrupt समय.
 *
 * This routine will send target reset to volume, followed by target
 * resets to the PDs. This is called when a PD has been हटाओd, or
 * volume has been deleted or हटाओd. When the target reset is sent
 * to volume, the PD target resets need to be queued to start upon
 * completion of the volume target reset.
 */
अटल व्योम
_scsih_check_ir_config_unhide_events(काष्ठा MPT3SAS_ADAPTER *ioc,
	Mpi2EventDataIrConfigChangeList_t *event_data)
अणु
	Mpi2EventIrConfigElement_t *element;
	पूर्णांक i;
	u16 handle, volume_handle, a, b;
	काष्ठा _tr_list *delayed_tr;

	a = 0;
	b = 0;

	अगर (ioc->is_warpdrive)
		वापस;

	/* Volume Resets क्रम Deleted or Removed */
	element = (Mpi2EventIrConfigElement_t *)&event_data->ConfigElement[0];
	क्रम (i = 0; i < event_data->NumElements; i++, element++) अणु
		अगर (le32_to_cpu(event_data->Flags) &
		    MPI2_EVENT_IR_CHANGE_FLAGS_FOREIGN_CONFIG)
			जारी;
		अगर (element->ReasonCode ==
		    MPI2_EVENT_IR_CHANGE_RC_VOLUME_DELETED ||
		    element->ReasonCode ==
		    MPI2_EVENT_IR_CHANGE_RC_REMOVED) अणु
			volume_handle = le16_to_cpu(element->VolDevHandle);
			_scsih_set_volume_delete_flag(ioc, volume_handle);
			_scsih_set_volume_handle_क्रम_tr(volume_handle, &a, &b);
		पूर्ण
	पूर्ण

	/* Volume Resets क्रम UNHIDE events */
	element = (Mpi2EventIrConfigElement_t *)&event_data->ConfigElement[0];
	क्रम (i = 0; i < event_data->NumElements; i++, element++) अणु
		अगर (le32_to_cpu(event_data->Flags) &
		    MPI2_EVENT_IR_CHANGE_FLAGS_FOREIGN_CONFIG)
			जारी;
		अगर (element->ReasonCode == MPI2_EVENT_IR_CHANGE_RC_UNHIDE) अणु
			volume_handle = le16_to_cpu(element->VolDevHandle);
			_scsih_set_volume_handle_क्रम_tr(volume_handle, &a, &b);
		पूर्ण
	पूर्ण

	अगर (a)
		_scsih_पंचांग_tr_volume_send(ioc, a);
	अगर (b)
		_scsih_पंचांग_tr_volume_send(ioc, b);

	/* PD target resets */
	element = (Mpi2EventIrConfigElement_t *)&event_data->ConfigElement[0];
	क्रम (i = 0; i < event_data->NumElements; i++, element++) अणु
		अगर (element->ReasonCode != MPI2_EVENT_IR_CHANGE_RC_UNHIDE)
			जारी;
		handle = le16_to_cpu(element->PhysDiskDevHandle);
		volume_handle = le16_to_cpu(element->VolDevHandle);
		clear_bit(handle, ioc->pd_handles);
		अगर (!volume_handle)
			_scsih_पंचांग_tr_send(ioc, handle);
		अन्यथा अगर (volume_handle == a || volume_handle == b) अणु
			delayed_tr = kzalloc(माप(*delayed_tr), GFP_ATOMIC);
			BUG_ON(!delayed_tr);
			INIT_LIST_HEAD(&delayed_tr->list);
			delayed_tr->handle = handle;
			list_add_tail(&delayed_tr->list, &ioc->delayed_tr_list);
			dewtprपूर्णांकk(ioc,
				   ioc_info(ioc, "DELAYED:tr:handle(0x%04x), (open)\n",
					    handle));
		पूर्ण अन्यथा
			_scsih_पंचांग_tr_send(ioc, handle);
	पूर्ण
पूर्ण


/**
 * _scsih_check_volume_delete_events - set delete flag क्रम volumes
 * @ioc: per adapter object
 * @event_data: the event data payload
 * Context: पूर्णांकerrupt समय.
 *
 * This will handle the हाल when the cable connected to entire volume is
 * pulled. We will take care of setting the deleted flag so normal IO will
 * not be sent.
 */
अटल व्योम
_scsih_check_volume_delete_events(काष्ठा MPT3SAS_ADAPTER *ioc,
	Mpi2EventDataIrVolume_t *event_data)
अणु
	u32 state;

	अगर (event_data->ReasonCode != MPI2_EVENT_IR_VOLUME_RC_STATE_CHANGED)
		वापस;
	state = le32_to_cpu(event_data->NewValue);
	अगर (state == MPI2_RAID_VOL_STATE_MISSING || state ==
	    MPI2_RAID_VOL_STATE_FAILED)
		_scsih_set_volume_delete_flag(ioc,
		    le16_to_cpu(event_data->VolDevHandle));
पूर्ण

/**
 * _scsih_temp_threshold_events - display temperature threshold exceeded events
 * @ioc: per adapter object
 * @event_data: the temp threshold event data
 * Context: पूर्णांकerrupt समय.
 */
अटल व्योम
_scsih_temp_threshold_events(काष्ठा MPT3SAS_ADAPTER *ioc,
	Mpi2EventDataTemperature_t *event_data)
अणु
	u32 करोorbell;
	अगर (ioc->temp_sensors_count >= event_data->SensorNum) अणु
		ioc_err(ioc, "Temperature Threshold flags %s%s%s%s exceeded for Sensor: %d !!!\n",
			le16_to_cpu(event_data->Status) & 0x1 ? "0 " : " ",
			le16_to_cpu(event_data->Status) & 0x2 ? "1 " : " ",
			le16_to_cpu(event_data->Status) & 0x4 ? "2 " : " ",
			le16_to_cpu(event_data->Status) & 0x8 ? "3 " : " ",
			event_data->SensorNum);
		ioc_err(ioc, "Current Temp In Celsius: %d\n",
			event_data->CurrentTemperature);
		अगर (ioc->hba_mpi_version_beदीर्घed != MPI2_VERSION) अणु
			करोorbell = mpt3sas_base_get_iocstate(ioc, 0);
			अगर ((करोorbell & MPI2_IOC_STATE_MASK) ==
			    MPI2_IOC_STATE_FAULT) अणु
				mpt3sas_prपूर्णांक_fault_code(ioc,
				    करोorbell & MPI2_DOORBELL_DATA_MASK);
			पूर्ण अन्यथा अगर ((करोorbell & MPI2_IOC_STATE_MASK) ==
			    MPI2_IOC_STATE_COREDUMP) अणु
				mpt3sas_prपूर्णांक_coredump_info(ioc,
				    करोorbell & MPI2_DOORBELL_DATA_MASK);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक _scsih_set_satl_pending(काष्ठा scsi_cmnd *scmd, bool pending)
अणु
	काष्ठा MPT3SAS_DEVICE *priv = scmd->device->hostdata;

	अगर (scmd->cmnd[0] != ATA_12 && scmd->cmnd[0] != ATA_16)
		वापस 0;

	अगर (pending)
		वापस test_and_set_bit(0, &priv->ata_command_pending);

	clear_bit(0, &priv->ata_command_pending);
	वापस 0;
पूर्ण

/**
 * _scsih_flush_running_cmds - completing outstanding commands.
 * @ioc: per adapter object
 *
 * The flushing out of all pending scmd commands following host reset,
 * where all IO is dropped to the न्यूनमान.
 */
अटल व्योम
_scsih_flush_running_cmds(काष्ठा MPT3SAS_ADAPTER *ioc)
अणु
	काष्ठा scsi_cmnd *scmd;
	काष्ठा scsiio_tracker *st;
	u16 smid;
	पूर्णांक count = 0;

	क्रम (smid = 1; smid <= ioc->scsiio_depth; smid++) अणु
		scmd = mpt3sas_scsih_scsi_lookup_get(ioc, smid);
		अगर (!scmd)
			जारी;
		count++;
		_scsih_set_satl_pending(scmd, false);
		st = scsi_cmd_priv(scmd);
		mpt3sas_base_clear_st(ioc, st);
		scsi_dma_unmap(scmd);
		अगर (ioc->pci_error_recovery || ioc->हटाओ_host)
			scmd->result = DID_NO_CONNECT << 16;
		अन्यथा
			scmd->result = DID_RESET << 16;
		scmd->scsi_करोne(scmd);
	पूर्ण
	dपंचांगprपूर्णांकk(ioc, ioc_info(ioc, "completing %d cmds\n", count));
पूर्ण

/**
 * _scsih_setup_eedp - setup MPI request क्रम EEDP transfer
 * @ioc: per adapter object
 * @scmd: poपूर्णांकer to scsi command object
 * @mpi_request: poपूर्णांकer to the SCSI_IO request message frame
 *
 * Supporting protection 1 and 3.
 */
अटल व्योम
_scsih_setup_eedp(काष्ठा MPT3SAS_ADAPTER *ioc, काष्ठा scsi_cmnd *scmd,
	Mpi25SCSIIORequest_t *mpi_request)
अणु
	u16 eedp_flags;
	अचिन्हित अक्षर prot_op = scsi_get_prot_op(scmd);
	अचिन्हित अक्षर prot_type = scsi_get_prot_type(scmd);
	Mpi25SCSIIORequest_t *mpi_request_3v =
	   (Mpi25SCSIIORequest_t *)mpi_request;

	अगर (prot_type == SCSI_PROT_DIF_TYPE0 || prot_op == SCSI_PROT_NORMAL)
		वापस;

	अगर (prot_op ==  SCSI_PROT_READ_STRIP)
		eedp_flags = MPI2_SCSIIO_EEDPFLAGS_CHECK_REMOVE_OP;
	अन्यथा अगर (prot_op ==  SCSI_PROT_WRITE_INSERT)
		eedp_flags = MPI2_SCSIIO_EEDPFLAGS_INSERT_OP;
	अन्यथा
		वापस;

	चयन (prot_type) अणु
	हाल SCSI_PROT_DIF_TYPE1:
	हाल SCSI_PROT_DIF_TYPE2:

		/*
		* enable ref/guard checking
		* स्वतः increment ref tag
		*/
		eedp_flags |= MPI2_SCSIIO_EEDPFLAGS_INC_PRI_REFTAG |
		    MPI2_SCSIIO_EEDPFLAGS_CHECK_REFTAG |
		    MPI2_SCSIIO_EEDPFLAGS_CHECK_GUARD;
		mpi_request->CDB.EEDP32.PrimaryReferenceTag =
		    cpu_to_be32(t10_pi_ref_tag(scmd->request));
		अवरोध;

	हाल SCSI_PROT_DIF_TYPE3:

		/*
		* enable guard checking
		*/
		eedp_flags |= MPI2_SCSIIO_EEDPFLAGS_CHECK_GUARD;

		अवरोध;
	पूर्ण

	mpi_request_3v->EEDPBlockSize =
	    cpu_to_le16(scmd->device->sector_size);

	अगर (ioc->is_gen35_ioc)
		eedp_flags |= MPI25_SCSIIO_EEDPFLAGS_APPTAG_DISABLE_MODE;
	mpi_request->EEDPFlags = cpu_to_le16(eedp_flags);
पूर्ण

/**
 * _scsih_eedp_error_handling - वापस sense code क्रम EEDP errors
 * @scmd: poपूर्णांकer to scsi command object
 * @ioc_status: ioc status
 */
अटल व्योम
_scsih_eedp_error_handling(काष्ठा scsi_cmnd *scmd, u16 ioc_status)
अणु
	u8 ascq;

	चयन (ioc_status) अणु
	हाल MPI2_IOCSTATUS_EEDP_GUARD_ERROR:
		ascq = 0x01;
		अवरोध;
	हाल MPI2_IOCSTATUS_EEDP_APP_TAG_ERROR:
		ascq = 0x02;
		अवरोध;
	हाल MPI2_IOCSTATUS_EEDP_REF_TAG_ERROR:
		ascq = 0x03;
		अवरोध;
	शेष:
		ascq = 0x00;
		अवरोध;
	पूर्ण
	scsi_build_sense_buffer(0, scmd->sense_buffer, ILLEGAL_REQUEST, 0x10,
	    ascq);
	scmd->result = DRIVER_SENSE << 24 | (DID_ABORT << 16) |
	    SAM_STAT_CHECK_CONDITION;
पूर्ण

/**
 * scsih_qcmd - मुख्य scsi request entry poपूर्णांक
 * @shost: SCSI host poपूर्णांकer
 * @scmd: poपूर्णांकer to scsi command object
 *
 * The callback index is set inside `ioc->scsi_io_cb_idx`.
 *
 * Return: 0 on success.  If there's a failure, वापस either:
 * SCSI_MLQUEUE_DEVICE_BUSY अगर the device queue is full, or
 * SCSI_MLQUEUE_HOST_BUSY अगर the entire host queue is full
 */
अटल पूर्णांक
scsih_qcmd(काष्ठा Scsi_Host *shost, काष्ठा scsi_cmnd *scmd)
अणु
	काष्ठा MPT3SAS_ADAPTER *ioc = shost_priv(shost);
	काष्ठा MPT3SAS_DEVICE *sas_device_priv_data;
	काष्ठा MPT3SAS_TARGET *sas_target_priv_data;
	काष्ठा _raid_device *raid_device;
	काष्ठा request *rq = scmd->request;
	पूर्णांक class;
	Mpi25SCSIIORequest_t *mpi_request;
	काष्ठा _pcie_device *pcie_device = शून्य;
	u32 mpi_control;
	u16 smid;
	u16 handle;

	अगर (ioc->logging_level & MPT_DEBUG_SCSI)
		scsi_prपूर्णांक_command(scmd);

	sas_device_priv_data = scmd->device->hostdata;
	अगर (!sas_device_priv_data || !sas_device_priv_data->sas_target) अणु
		scmd->result = DID_NO_CONNECT << 16;
		scmd->scsi_करोne(scmd);
		वापस 0;
	पूर्ण

	अगर (!(_scsih_allow_scmd_to_device(ioc, scmd))) अणु
		scmd->result = DID_NO_CONNECT << 16;
		scmd->scsi_करोne(scmd);
		वापस 0;
	पूर्ण

	sas_target_priv_data = sas_device_priv_data->sas_target;

	/* invalid device handle */
	handle = sas_target_priv_data->handle;
	अगर (handle == MPT3SAS_INVALID_DEVICE_HANDLE) अणु
		scmd->result = DID_NO_CONNECT << 16;
		scmd->scsi_करोne(scmd);
		वापस 0;
	पूर्ण


	अगर (ioc->shost_recovery || ioc->ioc_link_reset_in_progress) अणु
		/* host recovery or link resets sent via IOCTLs */
		वापस SCSI_MLQUEUE_HOST_BUSY;
	पूर्ण अन्यथा अगर (sas_target_priv_data->deleted) अणु
		/* device has been deleted */
		scmd->result = DID_NO_CONNECT << 16;
		scmd->scsi_करोne(scmd);
		वापस 0;
	पूर्ण अन्यथा अगर (sas_target_priv_data->पंचांग_busy ||
		   sas_device_priv_data->block) अणु
		/* device busy with task management */
		वापस SCSI_MLQUEUE_DEVICE_BUSY;
	पूर्ण

	/*
	 * Bug work around क्रम firmware SATL handling.  The loop
	 * is based on atomic operations and ensures consistency
	 * since we're lockless at this poपूर्णांक
	 */
	करो अणु
		अगर (test_bit(0, &sas_device_priv_data->ata_command_pending))
			वापस SCSI_MLQUEUE_DEVICE_BUSY;
	पूर्ण जबतक (_scsih_set_satl_pending(scmd, true));

	अगर (scmd->sc_data_direction == DMA_FROM_DEVICE)
		mpi_control = MPI2_SCSIIO_CONTROL_READ;
	अन्यथा अगर (scmd->sc_data_direction == DMA_TO_DEVICE)
		mpi_control = MPI2_SCSIIO_CONTROL_WRITE;
	अन्यथा
		mpi_control = MPI2_SCSIIO_CONTROL_NODATATRANSFER;

	/* set tags */
	mpi_control |= MPI2_SCSIIO_CONTROL_SIMPLEQ;
	/* NCQ Prio supported, make sure control indicated high priority */
	अगर (sas_device_priv_data->ncq_prio_enable) अणु
		class = IOPRIO_PRIO_CLASS(req_get_ioprio(rq));
		अगर (class == IOPRIO_CLASS_RT)
			mpi_control |= 1 << MPI2_SCSIIO_CONTROL_CMDPRI_SHIFT;
	पूर्ण
	/* Make sure Device is not raid volume.
	 * We करो not expose raid functionality to upper layer क्रम warpdrive.
	 */
	अगर (((!ioc->is_warpdrive && !scsih_is_raid(&scmd->device->sdev_gendev))
		&& !scsih_is_nvme(&scmd->device->sdev_gendev))
		&& sas_is_tlr_enabled(scmd->device) && scmd->cmd_len != 32)
		mpi_control |= MPI2_SCSIIO_CONTROL_TLR_ON;

	smid = mpt3sas_base_get_smid_scsiio(ioc, ioc->scsi_io_cb_idx, scmd);
	अगर (!smid) अणु
		ioc_err(ioc, "%s: failed obtaining a smid\n", __func__);
		_scsih_set_satl_pending(scmd, false);
		जाओ out;
	पूर्ण
	mpi_request = mpt3sas_base_get_msg_frame(ioc, smid);
	स_रखो(mpi_request, 0, ioc->request_sz);
	_scsih_setup_eedp(ioc, scmd, mpi_request);

	अगर (scmd->cmd_len == 32)
		mpi_control |= 4 << MPI2_SCSIIO_CONTROL_ADDCDBLEN_SHIFT;
	mpi_request->Function = MPI2_FUNCTION_SCSI_IO_REQUEST;
	अगर (sas_device_priv_data->sas_target->flags &
	    MPT_TARGET_FLAGS_RAID_COMPONENT)
		mpi_request->Function = MPI2_FUNCTION_RAID_SCSI_IO_PASSTHROUGH;
	अन्यथा
		mpi_request->Function = MPI2_FUNCTION_SCSI_IO_REQUEST;
	mpi_request->DevHandle = cpu_to_le16(handle);
	mpi_request->DataLength = cpu_to_le32(scsi_bufflen(scmd));
	mpi_request->Control = cpu_to_le32(mpi_control);
	mpi_request->IoFlags = cpu_to_le16(scmd->cmd_len);
	mpi_request->MsgFlags = MPI2_SCSIIO_MSGFLAGS_SYSTEM_SENSE_ADDR;
	mpi_request->SenseBufferLength = SCSI_SENSE_BUFFERSIZE;
	mpi_request->SenseBufferLowAddress =
	    mpt3sas_base_get_sense_buffer_dma(ioc, smid);
	mpi_request->SGLOffset0 = दुरत्व(Mpi25SCSIIORequest_t, SGL) / 4;
	पूर्णांक_to_scsilun(sas_device_priv_data->lun, (काष्ठा scsi_lun *)
	    mpi_request->LUN);
	स_नकल(mpi_request->CDB.CDB32, scmd->cmnd, scmd->cmd_len);

	अगर (mpi_request->DataLength) अणु
		pcie_device = sas_target_priv_data->pcie_dev;
		अगर (ioc->build_sg_scmd(ioc, scmd, smid, pcie_device)) अणु
			mpt3sas_base_मुक्त_smid(ioc, smid);
			_scsih_set_satl_pending(scmd, false);
			जाओ out;
		पूर्ण
	पूर्ण अन्यथा
		ioc->build_zero_len_sge(ioc, &mpi_request->SGL);

	raid_device = sas_target_priv_data->raid_device;
	अगर (raid_device && raid_device->direct_io_enabled)
		mpt3sas_setup_direct_io(ioc, scmd,
			raid_device, mpi_request);

	अगर (likely(mpi_request->Function == MPI2_FUNCTION_SCSI_IO_REQUEST)) अणु
		अगर (sas_target_priv_data->flags & MPT_TARGET_FASTPATH_IO) अणु
			mpi_request->IoFlags = cpu_to_le16(scmd->cmd_len |
			    MPI25_SCSIIO_IOFLAGS_FAST_PATH);
			ioc->put_smid_fast_path(ioc, smid, handle);
		पूर्ण अन्यथा
			ioc->put_smid_scsi_io(ioc, smid,
			    le16_to_cpu(mpi_request->DevHandle));
	पूर्ण अन्यथा
		ioc->put_smid_शेष(ioc, smid);
	वापस 0;

 out:
	वापस SCSI_MLQUEUE_HOST_BUSY;
पूर्ण

/**
 * _scsih_normalize_sense - normalize descriptor and fixed क्रमmat sense data
 * @sense_buffer: sense data वापसed by target
 * @data: normalized skey/asc/ascq
 */
अटल व्योम
_scsih_normalize_sense(अक्षर *sense_buffer, काष्ठा sense_info *data)
अणु
	अगर ((sense_buffer[0] & 0x7F) >= 0x72) अणु
		/* descriptor क्रमmat */
		data->skey = sense_buffer[1] & 0x0F;
		data->asc = sense_buffer[2];
		data->ascq = sense_buffer[3];
	पूर्ण अन्यथा अणु
		/* fixed क्रमmat */
		data->skey = sense_buffer[2] & 0x0F;
		data->asc = sense_buffer[12];
		data->ascq = sense_buffer[13];
	पूर्ण
पूर्ण

/**
 * _scsih_scsi_ioc_info - translated non-succesfull SCSI_IO request
 * @ioc: per adapter object
 * @scmd: poपूर्णांकer to scsi command object
 * @mpi_reply: reply mf payload वापसed from firmware
 * @smid: ?
 *
 * scsi_status - SCSI Status code वापसed from target device
 * scsi_state - state info associated with SCSI_IO determined by ioc
 * ioc_status - ioc supplied status info
 */
अटल व्योम
_scsih_scsi_ioc_info(काष्ठा MPT3SAS_ADAPTER *ioc, काष्ठा scsi_cmnd *scmd,
	Mpi2SCSIIOReply_t *mpi_reply, u16 smid)
अणु
	u32 response_info;
	u8 *response_bytes;
	u16 ioc_status = le16_to_cpu(mpi_reply->IOCStatus) &
	    MPI2_IOCSTATUS_MASK;
	u8 scsi_state = mpi_reply->SCSIState;
	u8 scsi_status = mpi_reply->SCSIStatus;
	अक्षर *desc_ioc_state = शून्य;
	अक्षर *desc_scsi_status = शून्य;
	अक्षर *desc_scsi_state = ioc->पंचांगp_string;
	u32 log_info = le32_to_cpu(mpi_reply->IOCLogInfo);
	काष्ठा _sas_device *sas_device = शून्य;
	काष्ठा _pcie_device *pcie_device = शून्य;
	काष्ठा scsi_target *starget = scmd->device->sdev_target;
	काष्ठा MPT3SAS_TARGET *priv_target = starget->hostdata;
	अक्षर *device_str = शून्य;

	अगर (!priv_target)
		वापस;
	अगर (ioc->hide_ir_msg)
		device_str = "WarpDrive";
	अन्यथा
		device_str = "volume";

	अगर (log_info == 0x31170000)
		वापस;

	चयन (ioc_status) अणु
	हाल MPI2_IOCSTATUS_SUCCESS:
		desc_ioc_state = "success";
		अवरोध;
	हाल MPI2_IOCSTATUS_INVALID_FUNCTION:
		desc_ioc_state = "invalid function";
		अवरोध;
	हाल MPI2_IOCSTATUS_SCSI_RECOVERED_ERROR:
		desc_ioc_state = "scsi recovered error";
		अवरोध;
	हाल MPI2_IOCSTATUS_SCSI_INVALID_DEVHANDLE:
		desc_ioc_state = "scsi invalid dev handle";
		अवरोध;
	हाल MPI2_IOCSTATUS_SCSI_DEVICE_NOT_THERE:
		desc_ioc_state = "scsi device not there";
		अवरोध;
	हाल MPI2_IOCSTATUS_SCSI_DATA_OVERRUN:
		desc_ioc_state = "scsi data overrun";
		अवरोध;
	हाल MPI2_IOCSTATUS_SCSI_DATA_UNDERRUN:
		desc_ioc_state = "scsi data underrun";
		अवरोध;
	हाल MPI2_IOCSTATUS_SCSI_IO_DATA_ERROR:
		desc_ioc_state = "scsi io data error";
		अवरोध;
	हाल MPI2_IOCSTATUS_SCSI_PROTOCOL_ERROR:
		desc_ioc_state = "scsi protocol error";
		अवरोध;
	हाल MPI2_IOCSTATUS_SCSI_TASK_TERMINATED:
		desc_ioc_state = "scsi task terminated";
		अवरोध;
	हाल MPI2_IOCSTATUS_SCSI_RESIDUAL_MISMATCH:
		desc_ioc_state = "scsi residual mismatch";
		अवरोध;
	हाल MPI2_IOCSTATUS_SCSI_TASK_MGMT_FAILED:
		desc_ioc_state = "scsi task mgmt failed";
		अवरोध;
	हाल MPI2_IOCSTATUS_SCSI_IOC_TERMINATED:
		desc_ioc_state = "scsi ioc terminated";
		अवरोध;
	हाल MPI2_IOCSTATUS_SCSI_EXT_TERMINATED:
		desc_ioc_state = "scsi ext terminated";
		अवरोध;
	हाल MPI2_IOCSTATUS_EEDP_GUARD_ERROR:
		desc_ioc_state = "eedp guard error";
		अवरोध;
	हाल MPI2_IOCSTATUS_EEDP_REF_TAG_ERROR:
		desc_ioc_state = "eedp ref tag error";
		अवरोध;
	हाल MPI2_IOCSTATUS_EEDP_APP_TAG_ERROR:
		desc_ioc_state = "eedp app tag error";
		अवरोध;
	हाल MPI2_IOCSTATUS_INSUFFICIENT_POWER:
		desc_ioc_state = "insufficient power";
		अवरोध;
	शेष:
		desc_ioc_state = "unknown";
		अवरोध;
	पूर्ण

	चयन (scsi_status) अणु
	हाल MPI2_SCSI_STATUS_GOOD:
		desc_scsi_status = "good";
		अवरोध;
	हाल MPI2_SCSI_STATUS_CHECK_CONDITION:
		desc_scsi_status = "check condition";
		अवरोध;
	हाल MPI2_SCSI_STATUS_CONDITION_MET:
		desc_scsi_status = "condition met";
		अवरोध;
	हाल MPI2_SCSI_STATUS_BUSY:
		desc_scsi_status = "busy";
		अवरोध;
	हाल MPI2_SCSI_STATUS_INTERMEDIATE:
		desc_scsi_status = "intermediate";
		अवरोध;
	हाल MPI2_SCSI_STATUS_INTERMEDIATE_CONDMET:
		desc_scsi_status = "intermediate condmet";
		अवरोध;
	हाल MPI2_SCSI_STATUS_RESERVATION_CONFLICT:
		desc_scsi_status = "reservation conflict";
		अवरोध;
	हाल MPI2_SCSI_STATUS_COMMAND_TERMINATED:
		desc_scsi_status = "command terminated";
		अवरोध;
	हाल MPI2_SCSI_STATUS_TASK_SET_FULL:
		desc_scsi_status = "task set full";
		अवरोध;
	हाल MPI2_SCSI_STATUS_ACA_ACTIVE:
		desc_scsi_status = "aca active";
		अवरोध;
	हाल MPI2_SCSI_STATUS_TASK_ABORTED:
		desc_scsi_status = "task aborted";
		अवरोध;
	शेष:
		desc_scsi_status = "unknown";
		अवरोध;
	पूर्ण

	desc_scsi_state[0] = '\0';
	अगर (!scsi_state)
		desc_scsi_state = " ";
	अगर (scsi_state & MPI2_SCSI_STATE_RESPONSE_INFO_VALID)
		म_जोड़ो(desc_scsi_state, "response info ");
	अगर (scsi_state & MPI2_SCSI_STATE_TERMINATED)
		म_जोड़ो(desc_scsi_state, "state terminated ");
	अगर (scsi_state & MPI2_SCSI_STATE_NO_SCSI_STATUS)
		म_जोड़ो(desc_scsi_state, "no status ");
	अगर (scsi_state & MPI2_SCSI_STATE_AUTOSENSE_FAILED)
		म_जोड़ो(desc_scsi_state, "autosense failed ");
	अगर (scsi_state & MPI2_SCSI_STATE_AUTOSENSE_VALID)
		म_जोड़ो(desc_scsi_state, "autosense valid ");

	scsi_prपूर्णांक_command(scmd);

	अगर (priv_target->flags & MPT_TARGET_FLAGS_VOLUME) अणु
		ioc_warn(ioc, "\t%s wwid(0x%016llx)\n",
			 device_str, (u64)priv_target->sas_address);
	पूर्ण अन्यथा अगर (priv_target->flags & MPT_TARGET_FLAGS_PCIE_DEVICE) अणु
		pcie_device = mpt3sas_get_pdev_from_target(ioc, priv_target);
		अगर (pcie_device) अणु
			ioc_info(ioc, "\twwid(0x%016llx), port(%d)\n",
				 (u64)pcie_device->wwid, pcie_device->port_num);
			अगर (pcie_device->enclosure_handle != 0)
				ioc_info(ioc, "\tenclosure logical id(0x%016llx), slot(%d)\n",
					 (u64)pcie_device->enclosure_logical_id,
					 pcie_device->slot);
			अगर (pcie_device->connector_name[0])
				ioc_info(ioc, "\tenclosure level(0x%04x), connector name( %s)\n",
					 pcie_device->enclosure_level,
					 pcie_device->connector_name);
			pcie_device_put(pcie_device);
		पूर्ण
	पूर्ण अन्यथा अणु
		sas_device = mpt3sas_get_sdev_from_target(ioc, priv_target);
		अगर (sas_device) अणु
			ioc_warn(ioc, "\tsas_address(0x%016llx), phy(%d)\n",
				 (u64)sas_device->sas_address, sas_device->phy);

			_scsih_display_enclosure_chassis_info(ioc, sas_device,
			    शून्य, शून्य);

			sas_device_put(sas_device);
		पूर्ण
	पूर्ण

	ioc_warn(ioc, "\thandle(0x%04x), ioc_status(%s)(0x%04x), smid(%d)\n",
		 le16_to_cpu(mpi_reply->DevHandle),
		 desc_ioc_state, ioc_status, smid);
	ioc_warn(ioc, "\trequest_len(%d), underflow(%d), resid(%d)\n",
		 scsi_bufflen(scmd), scmd->underflow, scsi_get_resid(scmd));
	ioc_warn(ioc, "\ttag(%d), transfer_count(%d), sc->result(0x%08x)\n",
		 le16_to_cpu(mpi_reply->TaskTag),
		 le32_to_cpu(mpi_reply->TransferCount), scmd->result);
	ioc_warn(ioc, "\tscsi_status(%s)(0x%02x), scsi_state(%s)(0x%02x)\n",
		 desc_scsi_status, scsi_status, desc_scsi_state, scsi_state);

	अगर (scsi_state & MPI2_SCSI_STATE_AUTOSENSE_VALID) अणु
		काष्ठा sense_info data;
		_scsih_normalize_sense(scmd->sense_buffer, &data);
		ioc_warn(ioc, "\t[sense_key,asc,ascq]: [0x%02x,0x%02x,0x%02x], count(%d)\n",
			 data.skey, data.asc, data.ascq,
			 le32_to_cpu(mpi_reply->SenseCount));
	पूर्ण
	अगर (scsi_state & MPI2_SCSI_STATE_RESPONSE_INFO_VALID) अणु
		response_info = le32_to_cpu(mpi_reply->ResponseInfo);
		response_bytes = (u8 *)&response_info;
		_scsih_response_code(ioc, response_bytes[0]);
	पूर्ण
पूर्ण

/**
 * _scsih_turn_on_pfa_led - illuminate PFA LED
 * @ioc: per adapter object
 * @handle: device handle
 * Context: process
 */
अटल व्योम
_scsih_turn_on_pfa_led(काष्ठा MPT3SAS_ADAPTER *ioc, u16 handle)
अणु
	Mpi2SepReply_t mpi_reply;
	Mpi2SepRequest_t mpi_request;
	काष्ठा _sas_device *sas_device;

	sas_device = mpt3sas_get_sdev_by_handle(ioc, handle);
	अगर (!sas_device)
		वापस;

	स_रखो(&mpi_request, 0, माप(Mpi2SepRequest_t));
	mpi_request.Function = MPI2_FUNCTION_SCSI_ENCLOSURE_PROCESSOR;
	mpi_request.Action = MPI2_SEP_REQ_ACTION_WRITE_STATUS;
	mpi_request.SlotStatus =
	    cpu_to_le32(MPI2_SEP_REQ_SLOTSTATUS_PREDICTED_FAULT);
	mpi_request.DevHandle = cpu_to_le16(handle);
	mpi_request.Flags = MPI2_SEP_REQ_FLAGS_DEVHANDLE_ADDRESS;
	अगर ((mpt3sas_base_scsi_enclosure_processor(ioc, &mpi_reply,
	    &mpi_request)) != 0) अणु
		ioc_err(ioc, "failure at %s:%d/%s()!\n",
			__खाता__, __LINE__, __func__);
		जाओ out;
	पूर्ण
	sas_device->pfa_led_on = 1;

	अगर (mpi_reply.IOCStatus || mpi_reply.IOCLogInfo) अणु
		dewtprपूर्णांकk(ioc,
			   ioc_info(ioc, "enclosure_processor: ioc_status (0x%04x), loginfo(0x%08x)\n",
				    le16_to_cpu(mpi_reply.IOCStatus),
				    le32_to_cpu(mpi_reply.IOCLogInfo)));
		जाओ out;
	पूर्ण
out:
	sas_device_put(sas_device);
पूर्ण

/**
 * _scsih_turn_off_pfa_led - turn off Fault LED
 * @ioc: per adapter object
 * @sas_device: sas device whose PFA LED has to turned off
 * Context: process
 */
अटल व्योम
_scsih_turn_off_pfa_led(काष्ठा MPT3SAS_ADAPTER *ioc,
	काष्ठा _sas_device *sas_device)
अणु
	Mpi2SepReply_t mpi_reply;
	Mpi2SepRequest_t mpi_request;

	स_रखो(&mpi_request, 0, माप(Mpi2SepRequest_t));
	mpi_request.Function = MPI2_FUNCTION_SCSI_ENCLOSURE_PROCESSOR;
	mpi_request.Action = MPI2_SEP_REQ_ACTION_WRITE_STATUS;
	mpi_request.SlotStatus = 0;
	mpi_request.Slot = cpu_to_le16(sas_device->slot);
	mpi_request.DevHandle = 0;
	mpi_request.EnclosureHandle = cpu_to_le16(sas_device->enclosure_handle);
	mpi_request.Flags = MPI2_SEP_REQ_FLAGS_ENCLOSURE_SLOT_ADDRESS;
	अगर ((mpt3sas_base_scsi_enclosure_processor(ioc, &mpi_reply,
		&mpi_request)) != 0) अणु
		ioc_err(ioc, "failure at %s:%d/%s()!\n",
			__खाता__, __LINE__, __func__);
		वापस;
	पूर्ण

	अगर (mpi_reply.IOCStatus || mpi_reply.IOCLogInfo) अणु
		dewtprपूर्णांकk(ioc,
			   ioc_info(ioc, "enclosure_processor: ioc_status (0x%04x), loginfo(0x%08x)\n",
				    le16_to_cpu(mpi_reply.IOCStatus),
				    le32_to_cpu(mpi_reply.IOCLogInfo)));
		वापस;
	पूर्ण
पूर्ण

/**
 * _scsih_send_event_to_turn_on_pfa_led - fire delayed event
 * @ioc: per adapter object
 * @handle: device handle
 * Context: पूर्णांकerrupt.
 */
अटल व्योम
_scsih_send_event_to_turn_on_pfa_led(काष्ठा MPT3SAS_ADAPTER *ioc, u16 handle)
अणु
	काष्ठा fw_event_work *fw_event;

	fw_event = alloc_fw_event_work(0);
	अगर (!fw_event)
		वापस;
	fw_event->event = MPT3SAS_TURN_ON_PFA_LED;
	fw_event->device_handle = handle;
	fw_event->ioc = ioc;
	_scsih_fw_event_add(ioc, fw_event);
	fw_event_work_put(fw_event);
पूर्ण

/**
 * _scsih_smart_predicted_fault - process smart errors
 * @ioc: per adapter object
 * @handle: device handle
 * Context: पूर्णांकerrupt.
 */
अटल व्योम
_scsih_smart_predicted_fault(काष्ठा MPT3SAS_ADAPTER *ioc, u16 handle)
अणु
	काष्ठा scsi_target *starget;
	काष्ठा MPT3SAS_TARGET *sas_target_priv_data;
	Mpi2EventNotअगरicationReply_t *event_reply;
	Mpi2EventDataSasDeviceStatusChange_t *event_data;
	काष्ठा _sas_device *sas_device;
	sमाप_प्रकार sz;
	अचिन्हित दीर्घ flags;

	/* only handle non-raid devices */
	spin_lock_irqsave(&ioc->sas_device_lock, flags);
	sas_device = __mpt3sas_get_sdev_by_handle(ioc, handle);
	अगर (!sas_device)
		जाओ out_unlock;

	starget = sas_device->starget;
	sas_target_priv_data = starget->hostdata;

	अगर ((sas_target_priv_data->flags & MPT_TARGET_FLAGS_RAID_COMPONENT) ||
	   ((sas_target_priv_data->flags & MPT_TARGET_FLAGS_VOLUME)))
		जाओ out_unlock;

	_scsih_display_enclosure_chassis_info(शून्य, sas_device, शून्य, starget);

	spin_unlock_irqrestore(&ioc->sas_device_lock, flags);

	अगर (ioc->pdev->subप्रणाली_venकरोr == PCI_VENDOR_ID_IBM)
		_scsih_send_event_to_turn_on_pfa_led(ioc, handle);

	/* insert पूर्णांकo event log */
	sz = दुरत्व(Mpi2EventNotअगरicationReply_t, EventData) +
	     माप(Mpi2EventDataSasDeviceStatusChange_t);
	event_reply = kzalloc(sz, GFP_ATOMIC);
	अगर (!event_reply) अणु
		ioc_err(ioc, "failure at %s:%d/%s()!\n",
			__खाता__, __LINE__, __func__);
		जाओ out;
	पूर्ण

	event_reply->Function = MPI2_FUNCTION_EVENT_NOTIFICATION;
	event_reply->Event =
	    cpu_to_le16(MPI2_EVENT_SAS_DEVICE_STATUS_CHANGE);
	event_reply->MsgLength = sz/4;
	event_reply->EventDataLength =
	    cpu_to_le16(माप(Mpi2EventDataSasDeviceStatusChange_t)/4);
	event_data = (Mpi2EventDataSasDeviceStatusChange_t *)
	    event_reply->EventData;
	event_data->ReasonCode = MPI2_EVENT_SAS_DEV_STAT_RC_SMART_DATA;
	event_data->ASC = 0x5D;
	event_data->DevHandle = cpu_to_le16(handle);
	event_data->SASAddress = cpu_to_le64(sas_target_priv_data->sas_address);
	mpt3sas_ctl_add_to_event_log(ioc, event_reply);
	kमुक्त(event_reply);
out:
	अगर (sas_device)
		sas_device_put(sas_device);
	वापस;

out_unlock:
	spin_unlock_irqrestore(&ioc->sas_device_lock, flags);
	जाओ out;
पूर्ण

/**
 * _scsih_io_करोne - scsi request callback
 * @ioc: per adapter object
 * @smid: प्रणाली request message index
 * @msix_index: MSIX table index supplied by the OS
 * @reply: reply message frame(lower 32bit addr)
 *
 * Callback handler when using _scsih_qcmd.
 *
 * Return: 1 meaning mf should be मुक्तd from _base_पूर्णांकerrupt
 *         0 means the mf is मुक्तd from this function.
 */
अटल u8
_scsih_io_करोne(काष्ठा MPT3SAS_ADAPTER *ioc, u16 smid, u8 msix_index, u32 reply)
अणु
	Mpi25SCSIIORequest_t *mpi_request;
	Mpi2SCSIIOReply_t *mpi_reply;
	काष्ठा scsi_cmnd *scmd;
	काष्ठा scsiio_tracker *st;
	u16 ioc_status;
	u32 xfer_cnt;
	u8 scsi_state;
	u8 scsi_status;
	u32 log_info;
	काष्ठा MPT3SAS_DEVICE *sas_device_priv_data;
	u32 response_code = 0;

	mpi_reply = mpt3sas_base_get_reply_virt_addr(ioc, reply);

	scmd = mpt3sas_scsih_scsi_lookup_get(ioc, smid);
	अगर (scmd == शून्य)
		वापस 1;

	_scsih_set_satl_pending(scmd, false);

	mpi_request = mpt3sas_base_get_msg_frame(ioc, smid);

	अगर (mpi_reply == शून्य) अणु
		scmd->result = DID_OK << 16;
		जाओ out;
	पूर्ण

	sas_device_priv_data = scmd->device->hostdata;
	अगर (!sas_device_priv_data || !sas_device_priv_data->sas_target ||
	     sas_device_priv_data->sas_target->deleted) अणु
		scmd->result = DID_NO_CONNECT << 16;
		जाओ out;
	पूर्ण
	ioc_status = le16_to_cpu(mpi_reply->IOCStatus);

	/*
	 * WARPDRIVE: If direct_io is set then it is directIO,
	 * the failed direct I/O should be redirected to volume
	 */
	st = scsi_cmd_priv(scmd);
	अगर (st->direct_io &&
	     ((ioc_status & MPI2_IOCSTATUS_MASK)
	      != MPI2_IOCSTATUS_SCSI_TASK_TERMINATED)) अणु
		st->direct_io = 0;
		st->scmd = scmd;
		स_नकल(mpi_request->CDB.CDB32, scmd->cmnd, scmd->cmd_len);
		mpi_request->DevHandle =
		    cpu_to_le16(sas_device_priv_data->sas_target->handle);
		ioc->put_smid_scsi_io(ioc, smid,
		    sas_device_priv_data->sas_target->handle);
		वापस 0;
	पूर्ण
	/* turning off TLR */
	scsi_state = mpi_reply->SCSIState;
	अगर (scsi_state & MPI2_SCSI_STATE_RESPONSE_INFO_VALID)
		response_code =
		    le32_to_cpu(mpi_reply->ResponseInfo) & 0xFF;
	अगर (!sas_device_priv_data->tlr_snoop_check) अणु
		sas_device_priv_data->tlr_snoop_check++;
		अगर ((!ioc->is_warpdrive &&
		    !scsih_is_raid(&scmd->device->sdev_gendev) &&
		    !scsih_is_nvme(&scmd->device->sdev_gendev))
		    && sas_is_tlr_enabled(scmd->device) &&
		    response_code == MPI2_SCSITASKMGMT_RSP_INVALID_FRAME) अणु
			sas_disable_tlr(scmd->device);
			sdev_prपूर्णांकk(KERN_INFO, scmd->device, "TLR disabled\n");
		पूर्ण
	पूर्ण

	xfer_cnt = le32_to_cpu(mpi_reply->TransferCount);
	scsi_set_resid(scmd, scsi_bufflen(scmd) - xfer_cnt);
	अगर (ioc_status & MPI2_IOCSTATUS_FLAG_LOG_INFO_AVAILABLE)
		log_info =  le32_to_cpu(mpi_reply->IOCLogInfo);
	अन्यथा
		log_info = 0;
	ioc_status &= MPI2_IOCSTATUS_MASK;
	scsi_status = mpi_reply->SCSIStatus;

	अगर (ioc_status == MPI2_IOCSTATUS_SCSI_DATA_UNDERRUN && xfer_cnt == 0 &&
	    (scsi_status == MPI2_SCSI_STATUS_BUSY ||
	     scsi_status == MPI2_SCSI_STATUS_RESERVATION_CONFLICT ||
	     scsi_status == MPI2_SCSI_STATUS_TASK_SET_FULL)) अणु
		ioc_status = MPI2_IOCSTATUS_SUCCESS;
	पूर्ण

	अगर (scsi_state & MPI2_SCSI_STATE_AUTOSENSE_VALID) अणु
		काष्ठा sense_info data;
		स्थिर व्योम *sense_data = mpt3sas_base_get_sense_buffer(ioc,
		    smid);
		u32 sz = min_t(u32, SCSI_SENSE_BUFFERSIZE,
		    le32_to_cpu(mpi_reply->SenseCount));
		स_नकल(scmd->sense_buffer, sense_data, sz);
		_scsih_normalize_sense(scmd->sense_buffer, &data);
		/* failure prediction threshold exceeded */
		अगर (data.asc == 0x5D)
			_scsih_smart_predicted_fault(ioc,
			    le16_to_cpu(mpi_reply->DevHandle));
		mpt3sas_trigger_scsi(ioc, data.skey, data.asc, data.ascq);

		अगर ((ioc->logging_level & MPT_DEBUG_REPLY) &&
		     ((scmd->sense_buffer[2] == UNIT_ATTENTION) ||
		     (scmd->sense_buffer[2] == MEDIUM_ERROR) ||
		     (scmd->sense_buffer[2] == HARDWARE_ERROR)))
			_scsih_scsi_ioc_info(ioc, scmd, mpi_reply, smid);
	पूर्ण
	चयन (ioc_status) अणु
	हाल MPI2_IOCSTATUS_BUSY:
	हाल MPI2_IOCSTATUS_INSUFFICIENT_RESOURCES:
		scmd->result = SAM_STAT_BUSY;
		अवरोध;

	हाल MPI2_IOCSTATUS_SCSI_DEVICE_NOT_THERE:
		scmd->result = DID_NO_CONNECT << 16;
		अवरोध;

	हाल MPI2_IOCSTATUS_SCSI_IOC_TERMINATED:
		अगर (sas_device_priv_data->block) अणु
			scmd->result = DID_TRANSPORT_DISRUPTED << 16;
			जाओ out;
		पूर्ण
		अगर (log_info == 0x31110630) अणु
			अगर (scmd->retries > 2) अणु
				scmd->result = DID_NO_CONNECT << 16;
				scsi_device_set_state(scmd->device,
				    SDEV_OFFLINE);
			पूर्ण अन्यथा अणु
				scmd->result = DID_SOFT_ERROR << 16;
				scmd->device->expecting_cc_ua = 1;
			पूर्ण
			अवरोध;
		पूर्ण अन्यथा अगर (log_info == VIRTUAL_IO_FAILED_RETRY) अणु
			scmd->result = DID_RESET << 16;
			अवरोध;
		पूर्ण अन्यथा अगर ((scmd->device->channel == RAID_CHANNEL) &&
		   (scsi_state == (MPI2_SCSI_STATE_TERMINATED |
		   MPI2_SCSI_STATE_NO_SCSI_STATUS))) अणु
			scmd->result = DID_RESET << 16;
			अवरोध;
		पूर्ण
		scmd->result = DID_SOFT_ERROR << 16;
		अवरोध;
	हाल MPI2_IOCSTATUS_SCSI_TASK_TERMINATED:
	हाल MPI2_IOCSTATUS_SCSI_EXT_TERMINATED:
		scmd->result = DID_RESET << 16;
		अवरोध;

	हाल MPI2_IOCSTATUS_SCSI_RESIDUAL_MISMATCH:
		अगर ((xfer_cnt == 0) || (scmd->underflow > xfer_cnt))
			scmd->result = DID_SOFT_ERROR << 16;
		अन्यथा
			scmd->result = (DID_OK << 16) | scsi_status;
		अवरोध;

	हाल MPI2_IOCSTATUS_SCSI_DATA_UNDERRUN:
		scmd->result = (DID_OK << 16) | scsi_status;

		अगर ((scsi_state & MPI2_SCSI_STATE_AUTOSENSE_VALID))
			अवरोध;

		अगर (xfer_cnt < scmd->underflow) अणु
			अगर (scsi_status == SAM_STAT_BUSY)
				scmd->result = SAM_STAT_BUSY;
			अन्यथा
				scmd->result = DID_SOFT_ERROR << 16;
		पूर्ण अन्यथा अगर (scsi_state & (MPI2_SCSI_STATE_AUTOSENSE_FAILED |
		     MPI2_SCSI_STATE_NO_SCSI_STATUS))
			scmd->result = DID_SOFT_ERROR << 16;
		अन्यथा अगर (scsi_state & MPI2_SCSI_STATE_TERMINATED)
			scmd->result = DID_RESET << 16;
		अन्यथा अगर (!xfer_cnt && scmd->cmnd[0] == REPORT_LUNS) अणु
			mpi_reply->SCSIState = MPI2_SCSI_STATE_AUTOSENSE_VALID;
			mpi_reply->SCSIStatus = SAM_STAT_CHECK_CONDITION;
			scmd->result = (DRIVER_SENSE << 24) |
			    SAM_STAT_CHECK_CONDITION;
			scmd->sense_buffer[0] = 0x70;
			scmd->sense_buffer[2] = ILLEGAL_REQUEST;
			scmd->sense_buffer[12] = 0x20;
			scmd->sense_buffer[13] = 0;
		पूर्ण
		अवरोध;

	हाल MPI2_IOCSTATUS_SCSI_DATA_OVERRUN:
		scsi_set_resid(scmd, 0);
		fallthrough;
	हाल MPI2_IOCSTATUS_SCSI_RECOVERED_ERROR:
	हाल MPI2_IOCSTATUS_SUCCESS:
		scmd->result = (DID_OK << 16) | scsi_status;
		अगर (response_code ==
		    MPI2_SCSITASKMGMT_RSP_INVALID_FRAME ||
		    (scsi_state & (MPI2_SCSI_STATE_AUTOSENSE_FAILED |
		     MPI2_SCSI_STATE_NO_SCSI_STATUS)))
			scmd->result = DID_SOFT_ERROR << 16;
		अन्यथा अगर (scsi_state & MPI2_SCSI_STATE_TERMINATED)
			scmd->result = DID_RESET << 16;
		अवरोध;

	हाल MPI2_IOCSTATUS_EEDP_GUARD_ERROR:
	हाल MPI2_IOCSTATUS_EEDP_REF_TAG_ERROR:
	हाल MPI2_IOCSTATUS_EEDP_APP_TAG_ERROR:
		_scsih_eedp_error_handling(scmd, ioc_status);
		अवरोध;

	हाल MPI2_IOCSTATUS_SCSI_PROTOCOL_ERROR:
	हाल MPI2_IOCSTATUS_INVALID_FUNCTION:
	हाल MPI2_IOCSTATUS_INVALID_SGL:
	हाल MPI2_IOCSTATUS_INTERNAL_ERROR:
	हाल MPI2_IOCSTATUS_INVALID_FIELD:
	हाल MPI2_IOCSTATUS_INVALID_STATE:
	हाल MPI2_IOCSTATUS_SCSI_IO_DATA_ERROR:
	हाल MPI2_IOCSTATUS_SCSI_TASK_MGMT_FAILED:
	हाल MPI2_IOCSTATUS_INSUFFICIENT_POWER:
	शेष:
		scmd->result = DID_SOFT_ERROR << 16;
		अवरोध;

	पूर्ण

	अगर (scmd->result && (ioc->logging_level & MPT_DEBUG_REPLY))
		_scsih_scsi_ioc_info(ioc , scmd, mpi_reply, smid);

 out:

	scsi_dma_unmap(scmd);
	mpt3sas_base_मुक्त_smid(ioc, smid);
	scmd->scsi_करोne(scmd);
	वापस 0;
पूर्ण

/**
 * _scsih_update_vphys_after_reset - update the Port's
 *			vphys_list after reset
 * @ioc: per adapter object
 *
 * Returns nothing.
 */
अटल व्योम
_scsih_update_vphys_after_reset(काष्ठा MPT3SAS_ADAPTER *ioc)
अणु
	u16 sz, ioc_status;
	पूर्णांक i;
	Mpi2ConfigReply_t mpi_reply;
	Mpi2SasIOUnitPage0_t *sas_iounit_pg0 = शून्य;
	u16 attached_handle;
	u64 attached_sas_addr;
	u8 found = 0, port_id;
	Mpi2SasPhyPage0_t phy_pg0;
	काष्ठा hba_port *port, *port_next, *mport;
	काष्ठा भव_phy *vphy, *vphy_next;
	काष्ठा _sas_device *sas_device;

	/*
	 * Mark all the vphys objects as dirty.
	 */
	list_क्रम_each_entry_safe(port, port_next,
	    &ioc->port_table_list, list) अणु
		अगर (!port->vphys_mask)
			जारी;
		list_क्रम_each_entry_safe(vphy, vphy_next,
		    &port->vphys_list, list) अणु
			vphy->flags |= MPT_VPHY_FLAG_सूचीTY_PHY;
		पूर्ण
	पूर्ण

	/*
	 * Read SASIOUnitPage0 to get each HBA Phy's data.
	 */
	sz = दुरत्व(Mpi2SasIOUnitPage0_t, PhyData) +
	    (ioc->sas_hba.num_phys * माप(Mpi2SasIOUnit0PhyData_t));
	sas_iounit_pg0 = kzalloc(sz, GFP_KERNEL);
	अगर (!sas_iounit_pg0) अणु
		ioc_err(ioc, "failure at %s:%d/%s()!\n",
		    __खाता__, __LINE__, __func__);
		वापस;
	पूर्ण
	अगर ((mpt3sas_config_get_sas_iounit_pg0(ioc, &mpi_reply,
	    sas_iounit_pg0, sz)) != 0)
		जाओ out;
	ioc_status = le16_to_cpu(mpi_reply.IOCStatus) & MPI2_IOCSTATUS_MASK;
	अगर (ioc_status != MPI2_IOCSTATUS_SUCCESS)
		जाओ out;
	/*
	 * Loop over each HBA Phy.
	 */
	क्रम (i = 0; i < ioc->sas_hba.num_phys; i++) अणु
		/*
		 * Check whether Phy's Negotiation Link Rate is > 1.5G or not.
		 */
		अगर ((sas_iounit_pg0->PhyData[i].NegotiatedLinkRate >> 4) <
		    MPI2_SAS_NEG_LINK_RATE_1_5)
			जारी;
		/*
		 * Check whether Phy is connected to SEP device or not,
		 * अगर it is SEP device then पढ़ो the Phy's SASPHYPage0 data to
		 * determine whether Phy is a भव Phy or not. अगर it is
		 * भव phy then it is conक्रमmed that the attached remote
		 * device is a HBA's vSES device.
		 */
		अगर (!(le32_to_cpu(
		    sas_iounit_pg0->PhyData[i].ControllerPhyDeviceInfo) &
		    MPI2_SAS_DEVICE_INFO_SEP))
			जारी;

		अगर ((mpt3sas_config_get_phy_pg0(ioc, &mpi_reply, &phy_pg0,
		    i))) अणु
			ioc_err(ioc, "failure at %s:%d/%s()!\n",
			    __खाता__, __LINE__, __func__);
			जारी;
		पूर्ण

		अगर (!(le32_to_cpu(phy_pg0.PhyInfo) &
		    MPI2_SAS_PHYINFO_VIRTUAL_PHY))
			जारी;
		/*
		 * Get the vSES device's SAS Address.
		 */
		attached_handle = le16_to_cpu(
		    sas_iounit_pg0->PhyData[i].AttachedDevHandle);
		अगर (_scsih_get_sas_address(ioc, attached_handle,
		    &attached_sas_addr) != 0) अणु
			ioc_err(ioc, "failure at %s:%d/%s()!\n",
			    __खाता__, __LINE__, __func__);
			जारी;
		पूर्ण

		found = 0;
		port = port_next = शून्य;
		/*
		 * Loop over each भव_phy object from
		 * each port's vphys_list.
		 */
		list_क्रम_each_entry_safe(port,
		    port_next, &ioc->port_table_list, list) अणु
			अगर (!port->vphys_mask)
				जारी;
			list_क्रम_each_entry_safe(vphy, vphy_next,
			    &port->vphys_list, list) अणु
				/*
				 * Continue with next भव_phy object
				 * अगर the object is not marked as dirty.
				 */
				अगर (!(vphy->flags & MPT_VPHY_FLAG_सूचीTY_PHY))
					जारी;

				/*
				 * Continue with next भव_phy object
				 * अगर the object's SAS Address is not equals
				 * to current Phy's vSES device SAS Address.
				 */
				अगर (vphy->sas_address != attached_sas_addr)
					जारी;
				/*
				 * Enable current Phy number bit in object's
				 * phy_mask field.
				 */
				अगर (!(vphy->phy_mask & (1 << i)))
					vphy->phy_mask = (1 << i);
				/*
				 * Get hba_port object from hba_port table
				 * corresponding to current phy's Port ID.
				 * अगर there is no hba_port object corresponding
				 * to Phy's Port ID then create a new hba_port
				 * object & add to hba_port table.
				 */
				port_id = sas_iounit_pg0->PhyData[i].Port;
				mport = mpt3sas_get_port_by_id(ioc, port_id, 1);
				अगर (!mport) अणु
					mport = kzalloc(
					    माप(काष्ठा hba_port), GFP_KERNEL);
					अगर (!mport)
						अवरोध;
					mport->port_id = port_id;
					ioc_info(ioc,
					    "%s: hba_port entry: %p, port: %d is added to hba_port list\n",
					    __func__, mport, mport->port_id);
					list_add_tail(&mport->list,
						&ioc->port_table_list);
				पूर्ण
				/*
				 * If mport & port poपूर्णांकers are not poपूर्णांकing to
				 * same hba_port object then it means that vSES
				 * device's Port ID got changed after reset and
				 * hence move current भव_phy object from
				 * port's vphys_list to mport's vphys_list.
				 */
				अगर (port != mport) अणु
					अगर (!mport->vphys_mask)
						INIT_LIST_HEAD(
						    &mport->vphys_list);
					mport->vphys_mask |= (1 << i);
					port->vphys_mask &= ~(1 << i);
					list_move(&vphy->list,
					    &mport->vphys_list);
					sas_device = mpt3sas_get_sdev_by_addr(
					    ioc, attached_sas_addr, port);
					अगर (sas_device)
						sas_device->port = mport;
				पूर्ण
				/*
				 * Earlier जबतक updating the hba_port table,
				 * it is determined that there is no other
				 * direct attached device with mport's Port ID,
				 * Hence mport was marked as dirty. Only vSES
				 * device has this Port ID, so unmark the mport
				 * as dirt.
				 */
				अगर (mport->flags & HBA_PORT_FLAG_सूचीTY_PORT) अणु
					mport->sas_address = 0;
					mport->phy_mask = 0;
					mport->flags &=
					    ~HBA_PORT_FLAG_सूचीTY_PORT;
				पूर्ण
				/*
				 * Unmark current भव_phy object as dirty.
				 */
				vphy->flags &= ~MPT_VPHY_FLAG_सूचीTY_PHY;
				found = 1;
				अवरोध;
			पूर्ण
			अगर (found)
				अवरोध;
		पूर्ण
	पूर्ण
out:
	kमुक्त(sas_iounit_pg0);
पूर्ण

/**
 * _scsih_get_port_table_after_reset - Conकाष्ठा temporary port table
 * @ioc: per adapter object
 * @port_table: address where port table needs to be स्थिरructed
 *
 * वापस number of HBA port entries available after reset.
 */
अटल पूर्णांक
_scsih_get_port_table_after_reset(काष्ठा MPT3SAS_ADAPTER *ioc,
	काष्ठा hba_port *port_table)
अणु
	u16 sz, ioc_status;
	पूर्णांक i, j;
	Mpi2ConfigReply_t mpi_reply;
	Mpi2SasIOUnitPage0_t *sas_iounit_pg0 = शून्य;
	u16 attached_handle;
	u64 attached_sas_addr;
	u8 found = 0, port_count = 0, port_id;

	sz = दुरत्व(Mpi2SasIOUnitPage0_t, PhyData) + (ioc->sas_hba.num_phys
	    * माप(Mpi2SasIOUnit0PhyData_t));
	sas_iounit_pg0 = kzalloc(sz, GFP_KERNEL);
	अगर (!sas_iounit_pg0) अणु
		ioc_err(ioc, "failure at %s:%d/%s()!\n",
		    __खाता__, __LINE__, __func__);
		वापस port_count;
	पूर्ण

	अगर ((mpt3sas_config_get_sas_iounit_pg0(ioc, &mpi_reply,
	    sas_iounit_pg0, sz)) != 0)
		जाओ out;
	ioc_status = le16_to_cpu(mpi_reply.IOCStatus) & MPI2_IOCSTATUS_MASK;
	अगर (ioc_status != MPI2_IOCSTATUS_SUCCESS)
		जाओ out;
	क्रम (i = 0; i < ioc->sas_hba.num_phys; i++) अणु
		found = 0;
		अगर ((sas_iounit_pg0->PhyData[i].NegotiatedLinkRate >> 4) <
		    MPI2_SAS_NEG_LINK_RATE_1_5)
			जारी;
		attached_handle =
		    le16_to_cpu(sas_iounit_pg0->PhyData[i].AttachedDevHandle);
		अगर (_scsih_get_sas_address(
		    ioc, attached_handle, &attached_sas_addr) != 0) अणु
			ioc_err(ioc, "failure at %s:%d/%s()!\n",
			    __खाता__, __LINE__, __func__);
			जारी;
		पूर्ण

		क्रम (j = 0; j < port_count; j++) अणु
			port_id = sas_iounit_pg0->PhyData[i].Port;
			अगर (port_table[j].port_id == port_id &&
			    port_table[j].sas_address == attached_sas_addr) अणु
				port_table[j].phy_mask |= (1 << i);
				found = 1;
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (found)
			जारी;

		port_id = sas_iounit_pg0->PhyData[i].Port;
		port_table[port_count].port_id = port_id;
		port_table[port_count].phy_mask = (1 << i);
		port_table[port_count].sas_address = attached_sas_addr;
		port_count++;
	पूर्ण
out:
	kमुक्त(sas_iounit_pg0);
	वापस port_count;
पूर्ण

क्रमागत hba_port_matched_codes अणु
	NOT_MATCHED = 0,
	MATCHED_WITH_ADDR_AND_PHYMASK,
	MATCHED_WITH_ADDR_SUBPHYMASK_AND_PORT,
	MATCHED_WITH_ADDR_AND_SUBPHYMASK,
	MATCHED_WITH_ADDR,
पूर्ण;

/**
 * _scsih_look_and_get_matched_port_entry - Get matched hba port entry
 *					from HBA port table
 * @ioc: per adapter object
 * @port_entry: hba port entry from temporary port table which needs to be
 *		searched क्रम matched entry in the HBA port table
 * @matched_port_entry: save matched hba port entry here
 * @count: count of matched entries
 *
 * वापस type of matched entry found.
 */
अटल क्रमागत hba_port_matched_codes
_scsih_look_and_get_matched_port_entry(काष्ठा MPT3SAS_ADAPTER *ioc,
	काष्ठा hba_port *port_entry,
	काष्ठा hba_port **matched_port_entry, पूर्णांक *count)
अणु
	काष्ठा hba_port *port_table_entry, *matched_port = शून्य;
	क्रमागत hba_port_matched_codes matched_code = NOT_MATCHED;
	पूर्णांक lcount = 0;
	*matched_port_entry = शून्य;

	list_क्रम_each_entry(port_table_entry, &ioc->port_table_list, list) अणु
		अगर (!(port_table_entry->flags & HBA_PORT_FLAG_सूचीTY_PORT))
			जारी;

		अगर ((port_table_entry->sas_address == port_entry->sas_address)
		    && (port_table_entry->phy_mask == port_entry->phy_mask)) अणु
			matched_code = MATCHED_WITH_ADDR_AND_PHYMASK;
			matched_port = port_table_entry;
			अवरोध;
		पूर्ण

		अगर ((port_table_entry->sas_address == port_entry->sas_address)
		    && (port_table_entry->phy_mask & port_entry->phy_mask)
		    && (port_table_entry->port_id == port_entry->port_id)) अणु
			matched_code = MATCHED_WITH_ADDR_SUBPHYMASK_AND_PORT;
			matched_port = port_table_entry;
			जारी;
		पूर्ण

		अगर ((port_table_entry->sas_address == port_entry->sas_address)
		    && (port_table_entry->phy_mask & port_entry->phy_mask)) अणु
			अगर (matched_code ==
			    MATCHED_WITH_ADDR_SUBPHYMASK_AND_PORT)
				जारी;
			matched_code = MATCHED_WITH_ADDR_AND_SUBPHYMASK;
			matched_port = port_table_entry;
			जारी;
		पूर्ण

		अगर (port_table_entry->sas_address == port_entry->sas_address) अणु
			अगर (matched_code ==
			    MATCHED_WITH_ADDR_SUBPHYMASK_AND_PORT)
				जारी;
			अगर (matched_code == MATCHED_WITH_ADDR_AND_SUBPHYMASK)
				जारी;
			matched_code = MATCHED_WITH_ADDR;
			matched_port = port_table_entry;
			lcount++;
		पूर्ण
	पूर्ण

	*matched_port_entry = matched_port;
	अगर (matched_code ==  MATCHED_WITH_ADDR)
		*count = lcount;
	वापस matched_code;
पूर्ण

/**
 * _scsih_del_phy_part_of_anther_port - हटाओ phy अगर it
 *				is a part of anther port
 *@ioc: per adapter object
 *@port_table: port table after reset
 *@index: hba port entry index
 *@port_count: number of ports available after host reset
 *@offset: HBA phy bit offset
 *
 */
अटल व्योम
_scsih_del_phy_part_of_anther_port(काष्ठा MPT3SAS_ADAPTER *ioc,
	काष्ठा hba_port *port_table,
	पूर्णांक index, u8 port_count, पूर्णांक offset)
अणु
	काष्ठा _sas_node *sas_node = &ioc->sas_hba;
	u32 i, found = 0;

	क्रम (i = 0; i < port_count; i++) अणु
		अगर (i == index)
			जारी;

		अगर (port_table[i].phy_mask & (1 << offset)) अणु
			mpt3sas_transport_del_phy_from_an_existing_port(
			    ioc, sas_node, &sas_node->phy[offset]);
			found = 1;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (!found)
		port_table[index].phy_mask |= (1 << offset);
पूर्ण

/**
 * _scsih_add_or_del_phys_from_existing_port - add/हटाओ phy to/from
 *						right port
 *@ioc: per adapter object
 *@hba_port_entry: hba port table entry
 *@port_table: temporary port table
 *@index: hba port entry index
 *@port_count: number of ports available after host reset
 *
 */
अटल व्योम
_scsih_add_or_del_phys_from_existing_port(काष्ठा MPT3SAS_ADAPTER *ioc,
	काष्ठा hba_port *hba_port_entry, काष्ठा hba_port *port_table,
	पूर्णांक index, पूर्णांक port_count)
अणु
	u32 phy_mask, offset = 0;
	काष्ठा _sas_node *sas_node = &ioc->sas_hba;

	phy_mask = hba_port_entry->phy_mask ^ port_table[index].phy_mask;

	क्रम (offset = 0; offset < ioc->sas_hba.num_phys; offset++) अणु
		अगर (phy_mask & (1 << offset)) अणु
			अगर (!(port_table[index].phy_mask & (1 << offset))) अणु
				_scsih_del_phy_part_of_anther_port(
				    ioc, port_table, index, port_count,
				    offset);
				जारी;
			पूर्ण
			अगर (sas_node->phy[offset].phy_beदीर्घs_to_port)
				mpt3sas_transport_del_phy_from_an_existing_port(
				    ioc, sas_node, &sas_node->phy[offset]);
			mpt3sas_transport_add_phy_to_an_existing_port(
			    ioc, sas_node, &sas_node->phy[offset],
			    hba_port_entry->sas_address,
			    hba_port_entry);
		पूर्ण
	पूर्ण
पूर्ण

/**
 * _scsih_del_dirty_vphy - delete भव_phy objects marked as dirty.
 * @ioc: per adapter object
 *
 * Returns nothing.
 */
अटल व्योम
_scsih_del_dirty_vphy(काष्ठा MPT3SAS_ADAPTER *ioc)
अणु
	काष्ठा hba_port *port, *port_next;
	काष्ठा भव_phy *vphy, *vphy_next;

	list_क्रम_each_entry_safe(port, port_next,
	    &ioc->port_table_list, list) अणु
		अगर (!port->vphys_mask)
			जारी;
		list_क्रम_each_entry_safe(vphy, vphy_next,
		    &port->vphys_list, list) अणु
			अगर (vphy->flags & MPT_VPHY_FLAG_सूचीTY_PHY) अणु
				drsprपूर्णांकk(ioc, ioc_info(ioc,
				    "Deleting vphy %p entry from port id: %d\t, Phy_mask 0x%08x\n",
				    vphy, port->port_id,
				    vphy->phy_mask));
				port->vphys_mask &= ~vphy->phy_mask;
				list_del(&vphy->list);
				kमुक्त(vphy);
			पूर्ण
		पूर्ण
		अगर (!port->vphys_mask && !port->sas_address)
			port->flags |= HBA_PORT_FLAG_सूचीTY_PORT;
	पूर्ण
पूर्ण

/**
 * _scsih_del_dirty_port_entries - delete dirty port entries from port list
 *					after host reset
 *@ioc: per adapter object
 *
 */
अटल व्योम
_scsih_del_dirty_port_entries(काष्ठा MPT3SAS_ADAPTER *ioc)
अणु
	काष्ठा hba_port *port, *port_next;

	list_क्रम_each_entry_safe(port, port_next,
	    &ioc->port_table_list, list) अणु
		अगर (!(port->flags & HBA_PORT_FLAG_सूचीTY_PORT) ||
		    port->flags & HBA_PORT_FLAG_NEW_PORT)
			जारी;

		drsprपूर्णांकk(ioc, ioc_info(ioc,
		    "Deleting port table entry %p having Port: %d\t Phy_mask 0x%08x\n",
		    port, port->port_id, port->phy_mask));
		list_del(&port->list);
		kमुक्त(port);
	पूर्ण
पूर्ण

/**
 * _scsih_sas_port_refresh - Update HBA port table after host reset
 * @ioc: per adapter object
 */
अटल व्योम
_scsih_sas_port_refresh(काष्ठा MPT3SAS_ADAPTER *ioc)
अणु
	u32 port_count = 0;
	काष्ठा hba_port *port_table;
	काष्ठा hba_port *port_table_entry;
	काष्ठा hba_port *port_entry = शून्य;
	पूर्णांक i, j, count = 0, lcount = 0;
	पूर्णांक ret;
	u64 sas_addr;

	drsprपूर्णांकk(ioc, ioc_info(ioc,
	    "updating ports for sas_host(0x%016llx)\n",
	    (अचिन्हित दीर्घ दीर्घ)ioc->sas_hba.sas_address));

	port_table = kसुस्मृति(ioc->sas_hba.num_phys,
	    माप(काष्ठा hba_port), GFP_KERNEL);
	अगर (!port_table)
		वापस;

	port_count = _scsih_get_port_table_after_reset(ioc, port_table);
	अगर (!port_count)
		वापस;

	drsprपूर्णांकk(ioc, ioc_info(ioc, "New Port table\n"));
	क्रम (j = 0; j < port_count; j++)
		drsprपूर्णांकk(ioc, ioc_info(ioc,
		    "Port: %d\t Phy_mask 0x%08x\t sas_addr(0x%016llx)\n",
		    port_table[j].port_id,
		    port_table[j].phy_mask, port_table[j].sas_address));

	list_क्रम_each_entry(port_table_entry, &ioc->port_table_list, list)
		port_table_entry->flags |= HBA_PORT_FLAG_सूचीTY_PORT;

	drsprपूर्णांकk(ioc, ioc_info(ioc, "Old Port table\n"));
	port_table_entry = शून्य;
	list_क्रम_each_entry(port_table_entry, &ioc->port_table_list, list) अणु
		drsprपूर्णांकk(ioc, ioc_info(ioc,
		    "Port: %d\t Phy_mask 0x%08x\t sas_addr(0x%016llx)\n",
		    port_table_entry->port_id,
		    port_table_entry->phy_mask,
		    port_table_entry->sas_address));
	पूर्ण

	क्रम (j = 0; j < port_count; j++) अणु
		ret = _scsih_look_and_get_matched_port_entry(ioc,
		    &port_table[j], &port_entry, &count);
		अगर (!port_entry) अणु
			drsprपूर्णांकk(ioc, ioc_info(ioc,
			    "No Matched entry for sas_addr(0x%16llx), Port:%d\n",
			    port_table[j].sas_address,
			    port_table[j].port_id));
			जारी;
		पूर्ण

		चयन (ret) अणु
		हाल MATCHED_WITH_ADDR_SUBPHYMASK_AND_PORT:
		हाल MATCHED_WITH_ADDR_AND_SUBPHYMASK:
			_scsih_add_or_del_phys_from_existing_port(ioc,
			    port_entry, port_table, j, port_count);
			अवरोध;
		हाल MATCHED_WITH_ADDR:
			sas_addr = port_table[j].sas_address;
			क्रम (i = 0; i < port_count; i++) अणु
				अगर (port_table[i].sas_address == sas_addr)
					lcount++;
			पूर्ण

			अगर (count > 1 || lcount > 1)
				port_entry = शून्य;
			अन्यथा
				_scsih_add_or_del_phys_from_existing_port(ioc,
				    port_entry, port_table, j, port_count);
		पूर्ण

		अगर (!port_entry)
			जारी;

		अगर (port_entry->port_id != port_table[j].port_id)
			port_entry->port_id = port_table[j].port_id;
		port_entry->flags &= ~HBA_PORT_FLAG_सूचीTY_PORT;
		port_entry->phy_mask = port_table[j].phy_mask;
	पूर्ण

	port_table_entry = शून्य;
पूर्ण

/**
 * _scsih_alloc_vphy - allocate भव_phy object
 * @ioc: per adapter object
 * @port_id: Port ID number
 * @phy_num: HBA Phy number
 *
 * Returns allocated भव_phy object.
 */
अटल काष्ठा भव_phy *
_scsih_alloc_vphy(काष्ठा MPT3SAS_ADAPTER *ioc, u8 port_id, u8 phy_num)
अणु
	काष्ठा भव_phy *vphy;
	काष्ठा hba_port *port;

	port = mpt3sas_get_port_by_id(ioc, port_id, 0);
	अगर (!port)
		वापस शून्य;

	vphy = mpt3sas_get_vphy_by_phy(ioc, port, phy_num);
	अगर (!vphy) अणु
		vphy = kzalloc(माप(काष्ठा भव_phy), GFP_KERNEL);
		अगर (!vphy)
			वापस शून्य;

		अगर (!port->vphys_mask)
			INIT_LIST_HEAD(&port->vphys_list);

		/*
		 * Enable bit corresponding to HBA phy number on its
		 * parent hba_port object's vphys_mask field.
		 */
		port->vphys_mask |= (1 << phy_num);
		vphy->phy_mask |= (1 << phy_num);

		list_add_tail(&vphy->list, &port->vphys_list);

		ioc_info(ioc,
		    "vphy entry: %p, port id: %d, phy:%d is added to port's vphys_list\n",
		    vphy, port->port_id, phy_num);
	पूर्ण
	वापस vphy;
पूर्ण

/**
 * _scsih_sas_host_refresh - refreshing sas host object contents
 * @ioc: per adapter object
 * Context: user
 *
 * During port enable, fw will send topology events क्रम every device. Its
 * possible that the handles may change from the previous setting, so this
 * code keeping handles updating अगर changed.
 */
अटल व्योम
_scsih_sas_host_refresh(काष्ठा MPT3SAS_ADAPTER *ioc)
अणु
	u16 sz;
	u16 ioc_status;
	पूर्णांक i;
	Mpi2ConfigReply_t mpi_reply;
	Mpi2SasIOUnitPage0_t *sas_iounit_pg0 = शून्य;
	u16 attached_handle;
	u8 link_rate, port_id;
	काष्ठा hba_port *port;
	Mpi2SasPhyPage0_t phy_pg0;

	dपंचांगprपूर्णांकk(ioc,
		  ioc_info(ioc, "updating handles for sas_host(0x%016llx)\n",
			   (u64)ioc->sas_hba.sas_address));

	sz = दुरत्व(Mpi2SasIOUnitPage0_t, PhyData) + (ioc->sas_hba.num_phys
	    * माप(Mpi2SasIOUnit0PhyData_t));
	sas_iounit_pg0 = kzalloc(sz, GFP_KERNEL);
	अगर (!sas_iounit_pg0) अणु
		ioc_err(ioc, "failure at %s:%d/%s()!\n",
			__खाता__, __LINE__, __func__);
		वापस;
	पूर्ण

	अगर ((mpt3sas_config_get_sas_iounit_pg0(ioc, &mpi_reply,
	    sas_iounit_pg0, sz)) != 0)
		जाओ out;
	ioc_status = le16_to_cpu(mpi_reply.IOCStatus) & MPI2_IOCSTATUS_MASK;
	अगर (ioc_status != MPI2_IOCSTATUS_SUCCESS)
		जाओ out;
	क्रम (i = 0; i < ioc->sas_hba.num_phys ; i++) अणु
		link_rate = sas_iounit_pg0->PhyData[i].NegotiatedLinkRate >> 4;
		अगर (i == 0)
			ioc->sas_hba.handle = le16_to_cpu(
			    sas_iounit_pg0->PhyData[0].ControllerDevHandle);
		port_id = sas_iounit_pg0->PhyData[i].Port;
		अगर (!(mpt3sas_get_port_by_id(ioc, port_id, 0))) अणु
			port = kzalloc(माप(काष्ठा hba_port), GFP_KERNEL);
			अगर (!port)
				जाओ out;

			port->port_id = port_id;
			ioc_info(ioc,
			    "hba_port entry: %p, port: %d is added to hba_port list\n",
			    port, port->port_id);
			अगर (ioc->shost_recovery)
				port->flags = HBA_PORT_FLAG_NEW_PORT;
			list_add_tail(&port->list, &ioc->port_table_list);
		पूर्ण
		/*
		 * Check whether current Phy beदीर्घs to HBA vSES device or not.
		 */
		अगर (le32_to_cpu(sas_iounit_pg0->PhyData[i].ControllerPhyDeviceInfo) &
		    MPI2_SAS_DEVICE_INFO_SEP &&
		    (link_rate >=  MPI2_SAS_NEG_LINK_RATE_1_5)) अणु
			अगर ((mpt3sas_config_get_phy_pg0(ioc, &mpi_reply,
			    &phy_pg0, i))) अणु
				ioc_err(ioc,
				    "failure at %s:%d/%s()!\n",
				     __खाता__, __LINE__, __func__);
				जाओ out;
			पूर्ण
			अगर (!(le32_to_cpu(phy_pg0.PhyInfo) &
			    MPI2_SAS_PHYINFO_VIRTUAL_PHY))
				जारी;
			/*
			 * Allocate a भव_phy object क्रम vSES device, अगर
			 * this vSES device is hot added.
			 */
			अगर (!_scsih_alloc_vphy(ioc, port_id, i))
				जाओ out;
			ioc->sas_hba.phy[i].hba_vphy = 1;
		पूर्ण

		ioc->sas_hba.phy[i].handle = ioc->sas_hba.handle;
		attached_handle = le16_to_cpu(sas_iounit_pg0->PhyData[i].
		    AttachedDevHandle);
		अगर (attached_handle && link_rate < MPI2_SAS_NEG_LINK_RATE_1_5)
			link_rate = MPI2_SAS_NEG_LINK_RATE_1_5;
		ioc->sas_hba.phy[i].port =
		    mpt3sas_get_port_by_id(ioc, port_id, 0);
		mpt3sas_transport_update_links(ioc, ioc->sas_hba.sas_address,
		    attached_handle, i, link_rate,
		    ioc->sas_hba.phy[i].port);
	पूर्ण
 out:
	kमुक्त(sas_iounit_pg0);
पूर्ण

/**
 * _scsih_sas_host_add - create sas host object
 * @ioc: per adapter object
 *
 * Creating host side data object, stored in ioc->sas_hba
 */
अटल व्योम
_scsih_sas_host_add(काष्ठा MPT3SAS_ADAPTER *ioc)
अणु
	पूर्णांक i;
	Mpi2ConfigReply_t mpi_reply;
	Mpi2SasIOUnitPage0_t *sas_iounit_pg0 = शून्य;
	Mpi2SasIOUnitPage1_t *sas_iounit_pg1 = शून्य;
	Mpi2SasPhyPage0_t phy_pg0;
	Mpi2SasDevicePage0_t sas_device_pg0;
	Mpi2SasEnclosurePage0_t enclosure_pg0;
	u16 ioc_status;
	u16 sz;
	u8 device_missing_delay;
	u8 num_phys, port_id;
	काष्ठा hba_port *port;

	mpt3sas_config_get_number_hba_phys(ioc, &num_phys);
	अगर (!num_phys) अणु
		ioc_err(ioc, "failure at %s:%d/%s()!\n",
			__खाता__, __LINE__, __func__);
		वापस;
	पूर्ण
	ioc->sas_hba.phy = kसुस्मृति(num_phys,
	    माप(काष्ठा _sas_phy), GFP_KERNEL);
	अगर (!ioc->sas_hba.phy) अणु
		ioc_err(ioc, "failure at %s:%d/%s()!\n",
			__खाता__, __LINE__, __func__);
		जाओ out;
	पूर्ण
	ioc->sas_hba.num_phys = num_phys;

	/* sas_iounit page 0 */
	sz = दुरत्व(Mpi2SasIOUnitPage0_t, PhyData) + (ioc->sas_hba.num_phys *
	    माप(Mpi2SasIOUnit0PhyData_t));
	sas_iounit_pg0 = kzalloc(sz, GFP_KERNEL);
	अगर (!sas_iounit_pg0) अणु
		ioc_err(ioc, "failure at %s:%d/%s()!\n",
			__खाता__, __LINE__, __func__);
		वापस;
	पूर्ण
	अगर ((mpt3sas_config_get_sas_iounit_pg0(ioc, &mpi_reply,
	    sas_iounit_pg0, sz))) अणु
		ioc_err(ioc, "failure at %s:%d/%s()!\n",
			__खाता__, __LINE__, __func__);
		जाओ out;
	पूर्ण
	ioc_status = le16_to_cpu(mpi_reply.IOCStatus) &
	    MPI2_IOCSTATUS_MASK;
	अगर (ioc_status != MPI2_IOCSTATUS_SUCCESS) अणु
		ioc_err(ioc, "failure at %s:%d/%s()!\n",
			__खाता__, __LINE__, __func__);
		जाओ out;
	पूर्ण

	/* sas_iounit page 1 */
	sz = दुरत्व(Mpi2SasIOUnitPage1_t, PhyData) + (ioc->sas_hba.num_phys *
	    माप(Mpi2SasIOUnit1PhyData_t));
	sas_iounit_pg1 = kzalloc(sz, GFP_KERNEL);
	अगर (!sas_iounit_pg1) अणु
		ioc_err(ioc, "failure at %s:%d/%s()!\n",
			__खाता__, __LINE__, __func__);
		जाओ out;
	पूर्ण
	अगर ((mpt3sas_config_get_sas_iounit_pg1(ioc, &mpi_reply,
	    sas_iounit_pg1, sz))) अणु
		ioc_err(ioc, "failure at %s:%d/%s()!\n",
			__खाता__, __LINE__, __func__);
		जाओ out;
	पूर्ण
	ioc_status = le16_to_cpu(mpi_reply.IOCStatus) &
	    MPI2_IOCSTATUS_MASK;
	अगर (ioc_status != MPI2_IOCSTATUS_SUCCESS) अणु
		ioc_err(ioc, "failure at %s:%d/%s()!\n",
			__खाता__, __LINE__, __func__);
		जाओ out;
	पूर्ण

	ioc->io_missing_delay =
	    sas_iounit_pg1->IODeviceMissingDelay;
	device_missing_delay =
	    sas_iounit_pg1->ReportDeviceMissingDelay;
	अगर (device_missing_delay & MPI2_SASIOUNIT1_REPORT_MISSING_UNIT_16)
		ioc->device_missing_delay = (device_missing_delay &
		    MPI2_SASIOUNIT1_REPORT_MISSING_TIMEOUT_MASK) * 16;
	अन्यथा
		ioc->device_missing_delay = device_missing_delay &
		    MPI2_SASIOUNIT1_REPORT_MISSING_TIMEOUT_MASK;

	ioc->sas_hba.parent_dev = &ioc->shost->shost_gendev;
	क्रम (i = 0; i < ioc->sas_hba.num_phys ; i++) अणु
		अगर ((mpt3sas_config_get_phy_pg0(ioc, &mpi_reply, &phy_pg0,
		    i))) अणु
			ioc_err(ioc, "failure at %s:%d/%s()!\n",
				__खाता__, __LINE__, __func__);
			जाओ out;
		पूर्ण
		ioc_status = le16_to_cpu(mpi_reply.IOCStatus) &
		    MPI2_IOCSTATUS_MASK;
		अगर (ioc_status != MPI2_IOCSTATUS_SUCCESS) अणु
			ioc_err(ioc, "failure at %s:%d/%s()!\n",
				__खाता__, __LINE__, __func__);
			जाओ out;
		पूर्ण

		अगर (i == 0)
			ioc->sas_hba.handle = le16_to_cpu(sas_iounit_pg0->
			    PhyData[0].ControllerDevHandle);

		port_id = sas_iounit_pg0->PhyData[i].Port;
		अगर (!(mpt3sas_get_port_by_id(ioc, port_id, 0))) अणु
			port = kzalloc(माप(काष्ठा hba_port), GFP_KERNEL);
			अगर (!port)
				जाओ out;

			port->port_id = port_id;
			ioc_info(ioc,
			   "hba_port entry: %p, port: %d is added to hba_port list\n",
			   port, port->port_id);
			list_add_tail(&port->list,
			    &ioc->port_table_list);
		पूर्ण

		/*
		 * Check whether current Phy beदीर्घs to HBA vSES device or not.
		 */
		अगर ((le32_to_cpu(phy_pg0.PhyInfo) &
		    MPI2_SAS_PHYINFO_VIRTUAL_PHY) &&
		    (phy_pg0.NegotiatedLinkRate >> 4) >=
		    MPI2_SAS_NEG_LINK_RATE_1_5) अणु
			/*
			 * Allocate a भव_phy object क्रम vSES device.
			 */
			अगर (!_scsih_alloc_vphy(ioc, port_id, i))
				जाओ out;
			ioc->sas_hba.phy[i].hba_vphy = 1;
		पूर्ण

		ioc->sas_hba.phy[i].handle = ioc->sas_hba.handle;
		ioc->sas_hba.phy[i].phy_id = i;
		ioc->sas_hba.phy[i].port =
		    mpt3sas_get_port_by_id(ioc, port_id, 0);
		mpt3sas_transport_add_host_phy(ioc, &ioc->sas_hba.phy[i],
		    phy_pg0, ioc->sas_hba.parent_dev);
	पूर्ण
	अगर ((mpt3sas_config_get_sas_device_pg0(ioc, &mpi_reply, &sas_device_pg0,
	    MPI2_SAS_DEVICE_PGAD_FORM_HANDLE, ioc->sas_hba.handle))) अणु
		ioc_err(ioc, "failure at %s:%d/%s()!\n",
			__खाता__, __LINE__, __func__);
		जाओ out;
	पूर्ण
	ioc->sas_hba.enclosure_handle =
	    le16_to_cpu(sas_device_pg0.EnclosureHandle);
	ioc->sas_hba.sas_address = le64_to_cpu(sas_device_pg0.SASAddress);
	ioc_info(ioc, "host_add: handle(0x%04x), sas_addr(0x%016llx), phys(%d)\n",
		 ioc->sas_hba.handle,
		 (u64)ioc->sas_hba.sas_address,
		 ioc->sas_hba.num_phys);

	अगर (ioc->sas_hba.enclosure_handle) अणु
		अगर (!(mpt3sas_config_get_enclosure_pg0(ioc, &mpi_reply,
		    &enclosure_pg0, MPI2_SAS_ENCLOS_PGAD_FORM_HANDLE,
		   ioc->sas_hba.enclosure_handle)))
			ioc->sas_hba.enclosure_logical_id =
			    le64_to_cpu(enclosure_pg0.EnclosureLogicalID);
	पूर्ण

 out:
	kमुक्त(sas_iounit_pg1);
	kमुक्त(sas_iounit_pg0);
पूर्ण

/**
 * _scsih_expander_add -  creating expander object
 * @ioc: per adapter object
 * @handle: expander handle
 *
 * Creating expander object, stored in ioc->sas_expander_list.
 *
 * Return: 0 क्रम success, अन्यथा error.
 */
अटल पूर्णांक
_scsih_expander_add(काष्ठा MPT3SAS_ADAPTER *ioc, u16 handle)
अणु
	काष्ठा _sas_node *sas_expander;
	काष्ठा _enclosure_node *enclosure_dev;
	Mpi2ConfigReply_t mpi_reply;
	Mpi2ExpanderPage0_t expander_pg0;
	Mpi2ExpanderPage1_t expander_pg1;
	u32 ioc_status;
	u16 parent_handle;
	u64 sas_address, sas_address_parent = 0;
	पूर्णांक i;
	अचिन्हित दीर्घ flags;
	काष्ठा _sas_port *mpt3sas_port = शून्य;
	u8 port_id;

	पूर्णांक rc = 0;

	अगर (!handle)
		वापस -1;

	अगर (ioc->shost_recovery || ioc->pci_error_recovery)
		वापस -1;

	अगर ((mpt3sas_config_get_expander_pg0(ioc, &mpi_reply, &expander_pg0,
	    MPI2_SAS_EXPAND_PGAD_FORM_HNDL, handle))) अणु
		ioc_err(ioc, "failure at %s:%d/%s()!\n",
			__खाता__, __LINE__, __func__);
		वापस -1;
	पूर्ण

	ioc_status = le16_to_cpu(mpi_reply.IOCStatus) &
	    MPI2_IOCSTATUS_MASK;
	अगर (ioc_status != MPI2_IOCSTATUS_SUCCESS) अणु
		ioc_err(ioc, "failure at %s:%d/%s()!\n",
			__खाता__, __LINE__, __func__);
		वापस -1;
	पूर्ण

	/* handle out of order topology events */
	parent_handle = le16_to_cpu(expander_pg0.ParentDevHandle);
	अगर (_scsih_get_sas_address(ioc, parent_handle, &sas_address_parent)
	    != 0) अणु
		ioc_err(ioc, "failure at %s:%d/%s()!\n",
			__खाता__, __LINE__, __func__);
		वापस -1;
	पूर्ण

	port_id = expander_pg0.PhysicalPort;
	अगर (sas_address_parent != ioc->sas_hba.sas_address) अणु
		spin_lock_irqsave(&ioc->sas_node_lock, flags);
		sas_expander = mpt3sas_scsih_expander_find_by_sas_address(ioc,
		    sas_address_parent,
		    mpt3sas_get_port_by_id(ioc, port_id, 0));
		spin_unlock_irqrestore(&ioc->sas_node_lock, flags);
		अगर (!sas_expander) अणु
			rc = _scsih_expander_add(ioc, parent_handle);
			अगर (rc != 0)
				वापस rc;
		पूर्ण
	पूर्ण

	spin_lock_irqsave(&ioc->sas_node_lock, flags);
	sas_address = le64_to_cpu(expander_pg0.SASAddress);
	sas_expander = mpt3sas_scsih_expander_find_by_sas_address(ioc,
	    sas_address, mpt3sas_get_port_by_id(ioc, port_id, 0));
	spin_unlock_irqrestore(&ioc->sas_node_lock, flags);

	अगर (sas_expander)
		वापस 0;

	sas_expander = kzalloc(माप(काष्ठा _sas_node),
	    GFP_KERNEL);
	अगर (!sas_expander) अणु
		ioc_err(ioc, "failure at %s:%d/%s()!\n",
			__खाता__, __LINE__, __func__);
		वापस -1;
	पूर्ण

	sas_expander->handle = handle;
	sas_expander->num_phys = expander_pg0.NumPhys;
	sas_expander->sas_address_parent = sas_address_parent;
	sas_expander->sas_address = sas_address;
	sas_expander->port = mpt3sas_get_port_by_id(ioc, port_id, 0);
	अगर (!sas_expander->port) अणु
		ioc_err(ioc, "failure at %s:%d/%s()!\n",
		    __खाता__, __LINE__, __func__);
		rc = -1;
		जाओ out_fail;
	पूर्ण

	ioc_info(ioc, "expander_add: handle(0x%04x), parent(0x%04x), sas_addr(0x%016llx), phys(%d)\n",
		 handle, parent_handle,
		 (u64)sas_expander->sas_address, sas_expander->num_phys);

	अगर (!sas_expander->num_phys)
		जाओ out_fail;
	sas_expander->phy = kसुस्मृति(sas_expander->num_phys,
	    माप(काष्ठा _sas_phy), GFP_KERNEL);
	अगर (!sas_expander->phy) अणु
		ioc_err(ioc, "failure at %s:%d/%s()!\n",
			__खाता__, __LINE__, __func__);
		rc = -1;
		जाओ out_fail;
	पूर्ण

	INIT_LIST_HEAD(&sas_expander->sas_port_list);
	mpt3sas_port = mpt3sas_transport_port_add(ioc, handle,
	    sas_address_parent, sas_expander->port);
	अगर (!mpt3sas_port) अणु
		ioc_err(ioc, "failure at %s:%d/%s()!\n",
			__खाता__, __LINE__, __func__);
		rc = -1;
		जाओ out_fail;
	पूर्ण
	sas_expander->parent_dev = &mpt3sas_port->rphy->dev;
	sas_expander->rphy = mpt3sas_port->rphy;

	क्रम (i = 0 ; i < sas_expander->num_phys ; i++) अणु
		अगर ((mpt3sas_config_get_expander_pg1(ioc, &mpi_reply,
		    &expander_pg1, i, handle))) अणु
			ioc_err(ioc, "failure at %s:%d/%s()!\n",
				__खाता__, __LINE__, __func__);
			rc = -1;
			जाओ out_fail;
		पूर्ण
		sas_expander->phy[i].handle = handle;
		sas_expander->phy[i].phy_id = i;
		sas_expander->phy[i].port =
		    mpt3sas_get_port_by_id(ioc, port_id, 0);

		अगर ((mpt3sas_transport_add_expander_phy(ioc,
		    &sas_expander->phy[i], expander_pg1,
		    sas_expander->parent_dev))) अणु
			ioc_err(ioc, "failure at %s:%d/%s()!\n",
				__खाता__, __LINE__, __func__);
			rc = -1;
			जाओ out_fail;
		पूर्ण
	पूर्ण

	अगर (sas_expander->enclosure_handle) अणु
		enclosure_dev =
			mpt3sas_scsih_enclosure_find_by_handle(ioc,
						sas_expander->enclosure_handle);
		अगर (enclosure_dev)
			sas_expander->enclosure_logical_id =
			    le64_to_cpu(enclosure_dev->pg0.EnclosureLogicalID);
	पूर्ण

	_scsih_expander_node_add(ioc, sas_expander);
	वापस 0;

 out_fail:

	अगर (mpt3sas_port)
		mpt3sas_transport_port_हटाओ(ioc, sas_expander->sas_address,
		    sas_address_parent, sas_expander->port);
	kमुक्त(sas_expander);
	वापस rc;
पूर्ण

/**
 * mpt3sas_expander_हटाओ - removing expander object
 * @ioc: per adapter object
 * @sas_address: expander sas_address
 * @port: hba port entry
 */
व्योम
mpt3sas_expander_हटाओ(काष्ठा MPT3SAS_ADAPTER *ioc, u64 sas_address,
	काष्ठा hba_port *port)
अणु
	काष्ठा _sas_node *sas_expander;
	अचिन्हित दीर्घ flags;

	अगर (ioc->shost_recovery)
		वापस;

	अगर (!port)
		वापस;

	spin_lock_irqsave(&ioc->sas_node_lock, flags);
	sas_expander = mpt3sas_scsih_expander_find_by_sas_address(ioc,
	    sas_address, port);
	spin_unlock_irqrestore(&ioc->sas_node_lock, flags);
	अगर (sas_expander)
		_scsih_expander_node_हटाओ(ioc, sas_expander);
पूर्ण

/**
 * _scsih_करोne -  पूर्णांकernal SCSI_IO callback handler.
 * @ioc: per adapter object
 * @smid: प्रणाली request message index
 * @msix_index: MSIX table index supplied by the OS
 * @reply: reply message frame(lower 32bit addr)
 *
 * Callback handler when sending पूर्णांकernal generated SCSI_IO.
 * The callback index passed is `ioc->scsih_cb_idx`
 *
 * Return: 1 meaning mf should be मुक्तd from _base_पूर्णांकerrupt
 *         0 means the mf is मुक्तd from this function.
 */
अटल u8
_scsih_करोne(काष्ठा MPT3SAS_ADAPTER *ioc, u16 smid, u8 msix_index, u32 reply)
अणु
	MPI2DefaultReply_t *mpi_reply;

	mpi_reply =  mpt3sas_base_get_reply_virt_addr(ioc, reply);
	अगर (ioc->scsih_cmds.status == MPT3_CMD_NOT_USED)
		वापस 1;
	अगर (ioc->scsih_cmds.smid != smid)
		वापस 1;
	ioc->scsih_cmds.status |= MPT3_CMD_COMPLETE;
	अगर (mpi_reply) अणु
		स_नकल(ioc->scsih_cmds.reply, mpi_reply,
		    mpi_reply->MsgLength*4);
		ioc->scsih_cmds.status |= MPT3_CMD_REPLY_VALID;
	पूर्ण
	ioc->scsih_cmds.status &= ~MPT3_CMD_PENDING;
	complete(&ioc->scsih_cmds.करोne);
	वापस 1;
पूर्ण




#घोषणा MPT3_MAX_LUNS (255)


/**
 * _scsih_check_access_status - check access flags
 * @ioc: per adapter object
 * @sas_address: sas address
 * @handle: sas device handle
 * @access_status: errors वापसed during discovery of the device
 *
 * Return: 0 क्रम success, अन्यथा failure
 */
अटल u8
_scsih_check_access_status(काष्ठा MPT3SAS_ADAPTER *ioc, u64 sas_address,
	u16 handle, u8 access_status)
अणु
	u8 rc = 1;
	अक्षर *desc = शून्य;

	चयन (access_status) अणु
	हाल MPI2_SAS_DEVICE0_ASTATUS_NO_ERRORS:
	हाल MPI2_SAS_DEVICE0_ASTATUS_SATA_NEEDS_INITIALIZATION:
		rc = 0;
		अवरोध;
	हाल MPI2_SAS_DEVICE0_ASTATUS_SATA_CAPABILITY_FAILED:
		desc = "sata capability failed";
		अवरोध;
	हाल MPI2_SAS_DEVICE0_ASTATUS_SATA_AFFILIATION_CONFLICT:
		desc = "sata affiliation conflict";
		अवरोध;
	हाल MPI2_SAS_DEVICE0_ASTATUS_ROUTE_NOT_ADDRESSABLE:
		desc = "route not addressable";
		अवरोध;
	हाल MPI2_SAS_DEVICE0_ASTATUS_SMP_ERROR_NOT_ADDRESSABLE:
		desc = "smp error not addressable";
		अवरोध;
	हाल MPI2_SAS_DEVICE0_ASTATUS_DEVICE_BLOCKED:
		desc = "device blocked";
		अवरोध;
	हाल MPI2_SAS_DEVICE0_ASTATUS_SATA_INIT_FAILED:
	हाल MPI2_SAS_DEVICE0_ASTATUS_SIF_UNKNOWN:
	हाल MPI2_SAS_DEVICE0_ASTATUS_SIF_AFFILIATION_CONFLICT:
	हाल MPI2_SAS_DEVICE0_ASTATUS_SIF_DIAG:
	हाल MPI2_SAS_DEVICE0_ASTATUS_SIF_IDENTIFICATION:
	हाल MPI2_SAS_DEVICE0_ASTATUS_SIF_CHECK_POWER:
	हाल MPI2_SAS_DEVICE0_ASTATUS_SIF_PIO_SN:
	हाल MPI2_SAS_DEVICE0_ASTATUS_SIF_MDMA_SN:
	हाल MPI2_SAS_DEVICE0_ASTATUS_SIF_UDMA_SN:
	हाल MPI2_SAS_DEVICE0_ASTATUS_SIF_ZONING_VIOLATION:
	हाल MPI2_SAS_DEVICE0_ASTATUS_SIF_NOT_ADDRESSABLE:
	हाल MPI2_SAS_DEVICE0_ASTATUS_SIF_MAX:
		desc = "sata initialization failed";
		अवरोध;
	शेष:
		desc = "unknown";
		अवरोध;
	पूर्ण

	अगर (!rc)
		वापस 0;

	ioc_err(ioc, "discovery errors(%s): sas_address(0x%016llx), handle(0x%04x)\n",
		desc, (u64)sas_address, handle);
	वापस rc;
पूर्ण

/**
 * _scsih_check_device - checking device responsiveness
 * @ioc: per adapter object
 * @parent_sas_address: sas address of parent expander or sas host
 * @handle: attached device handle
 * @phy_number: phy number
 * @link_rate: new link rate
 */
अटल व्योम
_scsih_check_device(काष्ठा MPT3SAS_ADAPTER *ioc,
	u64 parent_sas_address, u16 handle, u8 phy_number, u8 link_rate)
अणु
	Mpi2ConfigReply_t mpi_reply;
	Mpi2SasDevicePage0_t sas_device_pg0;
	काष्ठा _sas_device *sas_device = शून्य;
	काष्ठा _enclosure_node *enclosure_dev = शून्य;
	u32 ioc_status;
	अचिन्हित दीर्घ flags;
	u64 sas_address;
	काष्ठा scsi_target *starget;
	काष्ठा MPT3SAS_TARGET *sas_target_priv_data;
	u32 device_info;
	काष्ठा hba_port *port;

	अगर ((mpt3sas_config_get_sas_device_pg0(ioc, &mpi_reply, &sas_device_pg0,
	    MPI2_SAS_DEVICE_PGAD_FORM_HANDLE, handle)))
		वापस;

	ioc_status = le16_to_cpu(mpi_reply.IOCStatus) & MPI2_IOCSTATUS_MASK;
	अगर (ioc_status != MPI2_IOCSTATUS_SUCCESS)
		वापस;

	/* wide port handling ~ we need only handle device once क्रम the phy that
	 * is matched in sas device page zero
	 */
	अगर (phy_number != sas_device_pg0.PhyNum)
		वापस;

	/* check अगर this is end device */
	device_info = le32_to_cpu(sas_device_pg0.DeviceInfo);
	अगर (!(_scsih_is_end_device(device_info)))
		वापस;

	spin_lock_irqsave(&ioc->sas_device_lock, flags);
	sas_address = le64_to_cpu(sas_device_pg0.SASAddress);
	port = mpt3sas_get_port_by_id(ioc, sas_device_pg0.PhysicalPort, 0);
	अगर (!port)
		जाओ out_unlock;
	sas_device = __mpt3sas_get_sdev_by_addr(ioc,
	    sas_address, port);

	अगर (!sas_device)
		जाओ out_unlock;

	अगर (unlikely(sas_device->handle != handle)) अणु
		starget = sas_device->starget;
		sas_target_priv_data = starget->hostdata;
		starget_prपूर्णांकk(KERN_INFO, starget,
			"handle changed from(0x%04x) to (0x%04x)!!!\n",
			sas_device->handle, handle);
		sas_target_priv_data->handle = handle;
		sas_device->handle = handle;
		अगर (le16_to_cpu(sas_device_pg0.Flags) &
		     MPI2_SAS_DEVICE0_FLAGS_ENCL_LEVEL_VALID) अणु
			sas_device->enclosure_level =
				sas_device_pg0.EnclosureLevel;
			स_नकल(sas_device->connector_name,
				sas_device_pg0.ConnectorName, 4);
			sas_device->connector_name[4] = '\0';
		पूर्ण अन्यथा अणु
			sas_device->enclosure_level = 0;
			sas_device->connector_name[0] = '\0';
		पूर्ण

		sas_device->enclosure_handle =
				le16_to_cpu(sas_device_pg0.EnclosureHandle);
		sas_device->is_chassis_slot_valid = 0;
		enclosure_dev = mpt3sas_scsih_enclosure_find_by_handle(ioc,
						sas_device->enclosure_handle);
		अगर (enclosure_dev) अणु
			sas_device->enclosure_logical_id =
			    le64_to_cpu(enclosure_dev->pg0.EnclosureLogicalID);
			अगर (le16_to_cpu(enclosure_dev->pg0.Flags) &
			    MPI2_SAS_ENCLS0_FLAGS_CHASSIS_SLOT_VALID) अणु
				sas_device->is_chassis_slot_valid = 1;
				sas_device->chassis_slot =
					enclosure_dev->pg0.ChassisSlot;
			पूर्ण
		पूर्ण
	पूर्ण

	/* check अगर device is present */
	अगर (!(le16_to_cpu(sas_device_pg0.Flags) &
	    MPI2_SAS_DEVICE0_FLAGS_DEVICE_PRESENT)) अणु
		ioc_err(ioc, "device is not present handle(0x%04x), flags!!!\n",
			handle);
		जाओ out_unlock;
	पूर्ण

	/* check अगर there were any issues with discovery */
	अगर (_scsih_check_access_status(ioc, sas_address, handle,
	    sas_device_pg0.AccessStatus))
		जाओ out_unlock;

	spin_unlock_irqrestore(&ioc->sas_device_lock, flags);
	_scsih_ublock_io_device(ioc, sas_address, port);

	अगर (sas_device)
		sas_device_put(sas_device);
	वापस;

out_unlock:
	spin_unlock_irqrestore(&ioc->sas_device_lock, flags);
	अगर (sas_device)
		sas_device_put(sas_device);
पूर्ण

/**
 * _scsih_add_device -  creating sas device object
 * @ioc: per adapter object
 * @handle: sas device handle
 * @phy_num: phy number end device attached to
 * @is_pd: is this hidden raid component
 *
 * Creating end device object, stored in ioc->sas_device_list.
 *
 * Return: 0 क्रम success, non-zero क्रम failure.
 */
अटल पूर्णांक
_scsih_add_device(काष्ठा MPT3SAS_ADAPTER *ioc, u16 handle, u8 phy_num,
	u8 is_pd)
अणु
	Mpi2ConfigReply_t mpi_reply;
	Mpi2SasDevicePage0_t sas_device_pg0;
	काष्ठा _sas_device *sas_device;
	काष्ठा _enclosure_node *enclosure_dev = शून्य;
	u32 ioc_status;
	u64 sas_address;
	u32 device_info;
	u8 port_id;

	अगर ((mpt3sas_config_get_sas_device_pg0(ioc, &mpi_reply, &sas_device_pg0,
	    MPI2_SAS_DEVICE_PGAD_FORM_HANDLE, handle))) अणु
		ioc_err(ioc, "failure at %s:%d/%s()!\n",
			__खाता__, __LINE__, __func__);
		वापस -1;
	पूर्ण

	ioc_status = le16_to_cpu(mpi_reply.IOCStatus) &
	    MPI2_IOCSTATUS_MASK;
	अगर (ioc_status != MPI2_IOCSTATUS_SUCCESS) अणु
		ioc_err(ioc, "failure at %s:%d/%s()!\n",
			__खाता__, __LINE__, __func__);
		वापस -1;
	पूर्ण

	/* check अगर this is end device */
	device_info = le32_to_cpu(sas_device_pg0.DeviceInfo);
	अगर (!(_scsih_is_end_device(device_info)))
		वापस -1;
	set_bit(handle, ioc->pend_os_device_add);
	sas_address = le64_to_cpu(sas_device_pg0.SASAddress);

	/* check अगर device is present */
	अगर (!(le16_to_cpu(sas_device_pg0.Flags) &
	    MPI2_SAS_DEVICE0_FLAGS_DEVICE_PRESENT)) अणु
		ioc_err(ioc, "device is not present handle(0x04%x)!!!\n",
			handle);
		वापस -1;
	पूर्ण

	/* check अगर there were any issues with discovery */
	अगर (_scsih_check_access_status(ioc, sas_address, handle,
	    sas_device_pg0.AccessStatus))
		वापस -1;

	port_id = sas_device_pg0.PhysicalPort;
	sas_device = mpt3sas_get_sdev_by_addr(ioc,
	    sas_address, mpt3sas_get_port_by_id(ioc, port_id, 0));
	अगर (sas_device) अणु
		clear_bit(handle, ioc->pend_os_device_add);
		sas_device_put(sas_device);
		वापस -1;
	पूर्ण

	अगर (sas_device_pg0.EnclosureHandle) अणु
		enclosure_dev =
			mpt3sas_scsih_enclosure_find_by_handle(ioc,
			    le16_to_cpu(sas_device_pg0.EnclosureHandle));
		अगर (enclosure_dev == शून्य)
			ioc_info(ioc, "Enclosure handle(0x%04x) doesn't match with enclosure device!\n",
				 sas_device_pg0.EnclosureHandle);
	पूर्ण

	sas_device = kzalloc(माप(काष्ठा _sas_device),
	    GFP_KERNEL);
	अगर (!sas_device) अणु
		ioc_err(ioc, "failure at %s:%d/%s()!\n",
			__खाता__, __LINE__, __func__);
		वापस 0;
	पूर्ण

	kref_init(&sas_device->refcount);
	sas_device->handle = handle;
	अगर (_scsih_get_sas_address(ioc,
	    le16_to_cpu(sas_device_pg0.ParentDevHandle),
	    &sas_device->sas_address_parent) != 0)
		ioc_err(ioc, "failure at %s:%d/%s()!\n",
			__खाता__, __LINE__, __func__);
	sas_device->enclosure_handle =
	    le16_to_cpu(sas_device_pg0.EnclosureHandle);
	अगर (sas_device->enclosure_handle != 0)
		sas_device->slot =
		    le16_to_cpu(sas_device_pg0.Slot);
	sas_device->device_info = device_info;
	sas_device->sas_address = sas_address;
	sas_device->phy = sas_device_pg0.PhyNum;
	sas_device->fast_path = (le16_to_cpu(sas_device_pg0.Flags) &
	    MPI25_SAS_DEVICE0_FLAGS_FAST_PATH_CAPABLE) ? 1 : 0;
	sas_device->port = mpt3sas_get_port_by_id(ioc, port_id, 0);
	अगर (!sas_device->port) अणु
		ioc_err(ioc, "failure at %s:%d/%s()!\n",
		    __खाता__, __LINE__, __func__);
		जाओ out;
	पूर्ण

	अगर (le16_to_cpu(sas_device_pg0.Flags)
		& MPI2_SAS_DEVICE0_FLAGS_ENCL_LEVEL_VALID) अणु
		sas_device->enclosure_level =
			sas_device_pg0.EnclosureLevel;
		स_नकल(sas_device->connector_name,
			sas_device_pg0.ConnectorName, 4);
		sas_device->connector_name[4] = '\0';
	पूर्ण अन्यथा अणु
		sas_device->enclosure_level = 0;
		sas_device->connector_name[0] = '\0';
	पूर्ण
	/* get enclosure_logical_id & chassis_slot*/
	sas_device->is_chassis_slot_valid = 0;
	अगर (enclosure_dev) अणु
		sas_device->enclosure_logical_id =
		    le64_to_cpu(enclosure_dev->pg0.EnclosureLogicalID);
		अगर (le16_to_cpu(enclosure_dev->pg0.Flags) &
		    MPI2_SAS_ENCLS0_FLAGS_CHASSIS_SLOT_VALID) अणु
			sas_device->is_chassis_slot_valid = 1;
			sas_device->chassis_slot =
					enclosure_dev->pg0.ChassisSlot;
		पूर्ण
	पूर्ण

	/* get device name */
	sas_device->device_name = le64_to_cpu(sas_device_pg0.DeviceName);

	अगर (ioc->रुको_क्रम_discovery_to_complete)
		_scsih_sas_device_init_add(ioc, sas_device);
	अन्यथा
		_scsih_sas_device_add(ioc, sas_device);

out:
	sas_device_put(sas_device);
	वापस 0;
पूर्ण

/**
 * _scsih_हटाओ_device -  removing sas device object
 * @ioc: per adapter object
 * @sas_device: the sas_device object
 */
अटल व्योम
_scsih_हटाओ_device(काष्ठा MPT3SAS_ADAPTER *ioc,
	काष्ठा _sas_device *sas_device)
अणु
	काष्ठा MPT3SAS_TARGET *sas_target_priv_data;

	अगर ((ioc->pdev->subप्रणाली_venकरोr == PCI_VENDOR_ID_IBM) &&
	     (sas_device->pfa_led_on)) अणु
		_scsih_turn_off_pfa_led(ioc, sas_device);
		sas_device->pfa_led_on = 0;
	पूर्ण

	dewtprपूर्णांकk(ioc,
		   ioc_info(ioc, "%s: enter: handle(0x%04x), sas_addr(0x%016llx)\n",
			    __func__,
			    sas_device->handle, (u64)sas_device->sas_address));

	dewtprपूर्णांकk(ioc, _scsih_display_enclosure_chassis_info(ioc, sas_device,
	    शून्य, शून्य));

	अगर (sas_device->starget && sas_device->starget->hostdata) अणु
		sas_target_priv_data = sas_device->starget->hostdata;
		sas_target_priv_data->deleted = 1;
		_scsih_ublock_io_device(ioc, sas_device->sas_address,
		    sas_device->port);
		sas_target_priv_data->handle =
		     MPT3SAS_INVALID_DEVICE_HANDLE;
	पूर्ण

	अगर (!ioc->hide_drives)
		mpt3sas_transport_port_हटाओ(ioc,
		    sas_device->sas_address,
		    sas_device->sas_address_parent,
		    sas_device->port);

	ioc_info(ioc, "removing handle(0x%04x), sas_addr(0x%016llx)\n",
		 sas_device->handle, (u64)sas_device->sas_address);

	_scsih_display_enclosure_chassis_info(ioc, sas_device, शून्य, शून्य);

	dewtprपूर्णांकk(ioc,
		   ioc_info(ioc, "%s: exit: handle(0x%04x), sas_addr(0x%016llx)\n",
			    __func__,
			    sas_device->handle, (u64)sas_device->sas_address));
	dewtprपूर्णांकk(ioc, _scsih_display_enclosure_chassis_info(ioc, sas_device,
	    शून्य, शून्य));
पूर्ण

/**
 * _scsih_sas_topology_change_event_debug - debug क्रम topology event
 * @ioc: per adapter object
 * @event_data: event data payload
 * Context: user.
 */
अटल व्योम
_scsih_sas_topology_change_event_debug(काष्ठा MPT3SAS_ADAPTER *ioc,
	Mpi2EventDataSasTopologyChangeList_t *event_data)
अणु
	पूर्णांक i;
	u16 handle;
	u16 reason_code;
	u8 phy_number;
	अक्षर *status_str = शून्य;
	u8 link_rate, prev_link_rate;

	चयन (event_data->ExpStatus) अणु
	हाल MPI2_EVENT_SAS_TOPO_ES_ADDED:
		status_str = "add";
		अवरोध;
	हाल MPI2_EVENT_SAS_TOPO_ES_NOT_RESPONDING:
		status_str = "remove";
		अवरोध;
	हाल MPI2_EVENT_SAS_TOPO_ES_RESPONDING:
	हाल 0:
		status_str =  "responding";
		अवरोध;
	हाल MPI2_EVENT_SAS_TOPO_ES_DELAY_NOT_RESPONDING:
		status_str = "remove delay";
		अवरोध;
	शेष:
		status_str = "unknown status";
		अवरोध;
	पूर्ण
	ioc_info(ioc, "sas topology change: (%s)\n", status_str);
	pr_info("\thandle(0x%04x), enclosure_handle(0x%04x) " \
	    "start_phy(%02d), count(%d)\n",
	    le16_to_cpu(event_data->ExpanderDevHandle),
	    le16_to_cpu(event_data->EnclosureHandle),
	    event_data->StartPhyNum, event_data->NumEntries);
	क्रम (i = 0; i < event_data->NumEntries; i++) अणु
		handle = le16_to_cpu(event_data->PHY[i].AttachedDevHandle);
		अगर (!handle)
			जारी;
		phy_number = event_data->StartPhyNum + i;
		reason_code = event_data->PHY[i].PhyStatus &
		    MPI2_EVENT_SAS_TOPO_RC_MASK;
		चयन (reason_code) अणु
		हाल MPI2_EVENT_SAS_TOPO_RC_TARG_ADDED:
			status_str = "target add";
			अवरोध;
		हाल MPI2_EVENT_SAS_TOPO_RC_TARG_NOT_RESPONDING:
			status_str = "target remove";
			अवरोध;
		हाल MPI2_EVENT_SAS_TOPO_RC_DELAY_NOT_RESPONDING:
			status_str = "delay target remove";
			अवरोध;
		हाल MPI2_EVENT_SAS_TOPO_RC_PHY_CHANGED:
			status_str = "link rate change";
			अवरोध;
		हाल MPI2_EVENT_SAS_TOPO_RC_NO_CHANGE:
			status_str = "target responding";
			अवरोध;
		शेष:
			status_str = "unknown";
			अवरोध;
		पूर्ण
		link_rate = event_data->PHY[i].LinkRate >> 4;
		prev_link_rate = event_data->PHY[i].LinkRate & 0xF;
		pr_info("\tphy(%02d), attached_handle(0x%04x): %s:" \
		    " link rate: new(0x%02x), old(0x%02x)\n", phy_number,
		    handle, status_str, link_rate, prev_link_rate);

	पूर्ण
पूर्ण

/**
 * _scsih_sas_topology_change_event - handle topology changes
 * @ioc: per adapter object
 * @fw_event: The fw_event_work object
 * Context: user.
 *
 */
अटल पूर्णांक
_scsih_sas_topology_change_event(काष्ठा MPT3SAS_ADAPTER *ioc,
	काष्ठा fw_event_work *fw_event)
अणु
	पूर्णांक i;
	u16 parent_handle, handle;
	u16 reason_code;
	u8 phy_number, max_phys;
	काष्ठा _sas_node *sas_expander;
	u64 sas_address;
	अचिन्हित दीर्घ flags;
	u8 link_rate, prev_link_rate;
	काष्ठा hba_port *port;
	Mpi2EventDataSasTopologyChangeList_t *event_data =
		(Mpi2EventDataSasTopologyChangeList_t *)
		fw_event->event_data;

	अगर (ioc->logging_level & MPT_DEBUG_EVENT_WORK_TASK)
		_scsih_sas_topology_change_event_debug(ioc, event_data);

	अगर (ioc->shost_recovery || ioc->हटाओ_host || ioc->pci_error_recovery)
		वापस 0;

	अगर (!ioc->sas_hba.num_phys)
		_scsih_sas_host_add(ioc);
	अन्यथा
		_scsih_sas_host_refresh(ioc);

	अगर (fw_event->ignore) अणु
		dewtprपूर्णांकk(ioc, ioc_info(ioc, "ignoring expander event\n"));
		वापस 0;
	पूर्ण

	parent_handle = le16_to_cpu(event_data->ExpanderDevHandle);
	port = mpt3sas_get_port_by_id(ioc, event_data->PhysicalPort, 0);

	/* handle expander add */
	अगर (event_data->ExpStatus == MPI2_EVENT_SAS_TOPO_ES_ADDED)
		अगर (_scsih_expander_add(ioc, parent_handle) != 0)
			वापस 0;

	spin_lock_irqsave(&ioc->sas_node_lock, flags);
	sas_expander = mpt3sas_scsih_expander_find_by_handle(ioc,
	    parent_handle);
	अगर (sas_expander) अणु
		sas_address = sas_expander->sas_address;
		max_phys = sas_expander->num_phys;
		port = sas_expander->port;
	पूर्ण अन्यथा अगर (parent_handle < ioc->sas_hba.num_phys) अणु
		sas_address = ioc->sas_hba.sas_address;
		max_phys = ioc->sas_hba.num_phys;
	पूर्ण अन्यथा अणु
		spin_unlock_irqrestore(&ioc->sas_node_lock, flags);
		वापस 0;
	पूर्ण
	spin_unlock_irqrestore(&ioc->sas_node_lock, flags);

	/* handle siblings events */
	क्रम (i = 0; i < event_data->NumEntries; i++) अणु
		अगर (fw_event->ignore) अणु
			dewtprपूर्णांकk(ioc,
				   ioc_info(ioc, "ignoring expander event\n"));
			वापस 0;
		पूर्ण
		अगर (ioc->हटाओ_host || ioc->pci_error_recovery)
			वापस 0;
		phy_number = event_data->StartPhyNum + i;
		अगर (phy_number >= max_phys)
			जारी;
		reason_code = event_data->PHY[i].PhyStatus &
		    MPI2_EVENT_SAS_TOPO_RC_MASK;
		अगर ((event_data->PHY[i].PhyStatus &
		    MPI2_EVENT_SAS_TOPO_PHYSTATUS_VACANT) && (reason_code !=
		    MPI2_EVENT_SAS_TOPO_RC_TARG_NOT_RESPONDING))
				जारी;
		handle = le16_to_cpu(event_data->PHY[i].AttachedDevHandle);
		अगर (!handle)
			जारी;
		link_rate = event_data->PHY[i].LinkRate >> 4;
		prev_link_rate = event_data->PHY[i].LinkRate & 0xF;
		चयन (reason_code) अणु
		हाल MPI2_EVENT_SAS_TOPO_RC_PHY_CHANGED:

			अगर (ioc->shost_recovery)
				अवरोध;

			अगर (link_rate == prev_link_rate)
				अवरोध;

			mpt3sas_transport_update_links(ioc, sas_address,
			    handle, phy_number, link_rate, port);

			अगर (link_rate < MPI2_SAS_NEG_LINK_RATE_1_5)
				अवरोध;

			_scsih_check_device(ioc, sas_address, handle,
			    phy_number, link_rate);

			अगर (!test_bit(handle, ioc->pend_os_device_add))
				अवरोध;

			fallthrough;

		हाल MPI2_EVENT_SAS_TOPO_RC_TARG_ADDED:

			अगर (ioc->shost_recovery)
				अवरोध;

			mpt3sas_transport_update_links(ioc, sas_address,
			    handle, phy_number, link_rate, port);

			_scsih_add_device(ioc, handle, phy_number, 0);

			अवरोध;
		हाल MPI2_EVENT_SAS_TOPO_RC_TARG_NOT_RESPONDING:

			_scsih_device_हटाओ_by_handle(ioc, handle);
			अवरोध;
		पूर्ण
	पूर्ण

	/* handle expander removal */
	अगर (event_data->ExpStatus == MPI2_EVENT_SAS_TOPO_ES_NOT_RESPONDING &&
	    sas_expander)
		mpt3sas_expander_हटाओ(ioc, sas_address, port);

	वापस 0;
पूर्ण

/**
 * _scsih_sas_device_status_change_event_debug - debug क्रम device event
 * @ioc: ?
 * @event_data: event data payload
 * Context: user.
 */
अटल व्योम
_scsih_sas_device_status_change_event_debug(काष्ठा MPT3SAS_ADAPTER *ioc,
	Mpi2EventDataSasDeviceStatusChange_t *event_data)
अणु
	अक्षर *reason_str = शून्य;

	चयन (event_data->ReasonCode) अणु
	हाल MPI2_EVENT_SAS_DEV_STAT_RC_SMART_DATA:
		reason_str = "smart data";
		अवरोध;
	हाल MPI2_EVENT_SAS_DEV_STAT_RC_UNSUPPORTED:
		reason_str = "unsupported device discovered";
		अवरोध;
	हाल MPI2_EVENT_SAS_DEV_STAT_RC_INTERNAL_DEVICE_RESET:
		reason_str = "internal device reset";
		अवरोध;
	हाल MPI2_EVENT_SAS_DEV_STAT_RC_TASK_ABORT_INTERNAL:
		reason_str = "internal task abort";
		अवरोध;
	हाल MPI2_EVENT_SAS_DEV_STAT_RC_ABORT_TASK_SET_INTERNAL:
		reason_str = "internal task abort set";
		अवरोध;
	हाल MPI2_EVENT_SAS_DEV_STAT_RC_CLEAR_TASK_SET_INTERNAL:
		reason_str = "internal clear task set";
		अवरोध;
	हाल MPI2_EVENT_SAS_DEV_STAT_RC_QUERY_TASK_INTERNAL:
		reason_str = "internal query task";
		अवरोध;
	हाल MPI2_EVENT_SAS_DEV_STAT_RC_SATA_INIT_FAILURE:
		reason_str = "sata init failure";
		अवरोध;
	हाल MPI2_EVENT_SAS_DEV_STAT_RC_CMP_INTERNAL_DEV_RESET:
		reason_str = "internal device reset complete";
		अवरोध;
	हाल MPI2_EVENT_SAS_DEV_STAT_RC_CMP_TASK_ABORT_INTERNAL:
		reason_str = "internal task abort complete";
		अवरोध;
	हाल MPI2_EVENT_SAS_DEV_STAT_RC_ASYNC_NOTIFICATION:
		reason_str = "internal async notification";
		अवरोध;
	हाल MPI2_EVENT_SAS_DEV_STAT_RC_EXPANDER_REDUCED_FUNCTIONALITY:
		reason_str = "expander reduced functionality";
		अवरोध;
	हाल MPI2_EVENT_SAS_DEV_STAT_RC_CMP_EXPANDER_REDUCED_FUNCTIONALITY:
		reason_str = "expander reduced functionality complete";
		अवरोध;
	शेष:
		reason_str = "unknown reason";
		अवरोध;
	पूर्ण
	ioc_info(ioc, "device status change: (%s)\thandle(0x%04x), sas address(0x%016llx), tag(%d)",
		 reason_str, le16_to_cpu(event_data->DevHandle),
		 (u64)le64_to_cpu(event_data->SASAddress),
		 le16_to_cpu(event_data->TaskTag));
	अगर (event_data->ReasonCode == MPI2_EVENT_SAS_DEV_STAT_RC_SMART_DATA)
		pr_cont(", ASC(0x%x), ASCQ(0x%x)\n",
			event_data->ASC, event_data->ASCQ);
	pr_cont("\n");
पूर्ण

/**
 * _scsih_sas_device_status_change_event - handle device status change
 * @ioc: per adapter object
 * @event_data: The fw event
 * Context: user.
 */
अटल व्योम
_scsih_sas_device_status_change_event(काष्ठा MPT3SAS_ADAPTER *ioc,
	Mpi2EventDataSasDeviceStatusChange_t *event_data)
अणु
	काष्ठा MPT3SAS_TARGET *target_priv_data;
	काष्ठा _sas_device *sas_device;
	u64 sas_address;
	अचिन्हित दीर्घ flags;

	/* In MPI Revision K (0xC), the पूर्णांकernal device reset complete was
	 * implemented, so aव्योम setting पंचांग_busy flag क्रम older firmware.
	 */
	अगर ((ioc->facts.HeaderVersion >> 8) < 0xC)
		वापस;

	अगर (event_data->ReasonCode !=
	    MPI2_EVENT_SAS_DEV_STAT_RC_INTERNAL_DEVICE_RESET &&
	   event_data->ReasonCode !=
	    MPI2_EVENT_SAS_DEV_STAT_RC_CMP_INTERNAL_DEV_RESET)
		वापस;

	spin_lock_irqsave(&ioc->sas_device_lock, flags);
	sas_address = le64_to_cpu(event_data->SASAddress);
	sas_device = __mpt3sas_get_sdev_by_addr(ioc,
	    sas_address,
	    mpt3sas_get_port_by_id(ioc, event_data->PhysicalPort, 0));

	अगर (!sas_device || !sas_device->starget)
		जाओ out;

	target_priv_data = sas_device->starget->hostdata;
	अगर (!target_priv_data)
		जाओ out;

	अगर (event_data->ReasonCode ==
	    MPI2_EVENT_SAS_DEV_STAT_RC_INTERNAL_DEVICE_RESET)
		target_priv_data->पंचांग_busy = 1;
	अन्यथा
		target_priv_data->पंचांग_busy = 0;

	अगर (ioc->logging_level & MPT_DEBUG_EVENT_WORK_TASK)
		ioc_info(ioc,
		    "%s tm_busy flag for handle(0x%04x)\n",
		    (target_priv_data->पंचांग_busy == 1) ? "Enable" : "Disable",
		    target_priv_data->handle);

out:
	अगर (sas_device)
		sas_device_put(sas_device);

	spin_unlock_irqrestore(&ioc->sas_device_lock, flags);
पूर्ण


/**
 * _scsih_check_pcie_access_status - check access flags
 * @ioc: per adapter object
 * @wwid: wwid
 * @handle: sas device handle
 * @access_status: errors वापसed during discovery of the device
 *
 * Return: 0 क्रम success, अन्यथा failure
 */
अटल u8
_scsih_check_pcie_access_status(काष्ठा MPT3SAS_ADAPTER *ioc, u64 wwid,
	u16 handle, u8 access_status)
अणु
	u8 rc = 1;
	अक्षर *desc = शून्य;

	चयन (access_status) अणु
	हाल MPI26_PCIEDEV0_ASTATUS_NO_ERRORS:
	हाल MPI26_PCIEDEV0_ASTATUS_NEEDS_INITIALIZATION:
		rc = 0;
		अवरोध;
	हाल MPI26_PCIEDEV0_ASTATUS_CAPABILITY_FAILED:
		desc = "PCIe device capability failed";
		अवरोध;
	हाल MPI26_PCIEDEV0_ASTATUS_DEVICE_BLOCKED:
		desc = "PCIe device blocked";
		ioc_info(ioc,
		    "Device with Access Status (%s): wwid(0x%016llx), "
		    "handle(0x%04x)\n ll only be added to the internal list",
		    desc, (u64)wwid, handle);
		rc = 0;
		अवरोध;
	हाल MPI26_PCIEDEV0_ASTATUS_MEMORY_SPACE_ACCESS_FAILED:
		desc = "PCIe device mem space access failed";
		अवरोध;
	हाल MPI26_PCIEDEV0_ASTATUS_UNSUPPORTED_DEVICE:
		desc = "PCIe device unsupported";
		अवरोध;
	हाल MPI26_PCIEDEV0_ASTATUS_MSIX_REQUIRED:
		desc = "PCIe device MSIx Required";
		अवरोध;
	हाल MPI26_PCIEDEV0_ASTATUS_INIT_FAIL_MAX:
		desc = "PCIe device init fail max";
		अवरोध;
	हाल MPI26_PCIEDEV0_ASTATUS_UNKNOWN:
		desc = "PCIe device status unknown";
		अवरोध;
	हाल MPI26_PCIEDEV0_ASTATUS_NVME_READY_TIMEOUT:
		desc = "nvme ready timeout";
		अवरोध;
	हाल MPI26_PCIEDEV0_ASTATUS_NVME_DEVCFG_UNSUPPORTED:
		desc = "nvme device configuration unsupported";
		अवरोध;
	हाल MPI26_PCIEDEV0_ASTATUS_NVME_IDENTIFY_FAILED:
		desc = "nvme identify failed";
		अवरोध;
	हाल MPI26_PCIEDEV0_ASTATUS_NVME_QCONFIG_FAILED:
		desc = "nvme qconfig failed";
		अवरोध;
	हाल MPI26_PCIEDEV0_ASTATUS_NVME_QCREATION_FAILED:
		desc = "nvme qcreation failed";
		अवरोध;
	हाल MPI26_PCIEDEV0_ASTATUS_NVME_EVENTCFG_FAILED:
		desc = "nvme eventcfg failed";
		अवरोध;
	हाल MPI26_PCIEDEV0_ASTATUS_NVME_GET_FEATURE_STAT_FAILED:
		desc = "nvme get feature stat failed";
		अवरोध;
	हाल MPI26_PCIEDEV0_ASTATUS_NVME_IDLE_TIMEOUT:
		desc = "nvme idle timeout";
		अवरोध;
	हाल MPI26_PCIEDEV0_ASTATUS_NVME_FAILURE_STATUS:
		desc = "nvme failure status";
		अवरोध;
	शेष:
		ioc_err(ioc, "NVMe discovery error(0x%02x): wwid(0x%016llx), handle(0x%04x)\n",
			access_status, (u64)wwid, handle);
		वापस rc;
	पूर्ण

	अगर (!rc)
		वापस rc;

	ioc_info(ioc, "NVMe discovery error(%s): wwid(0x%016llx), handle(0x%04x)\n",
		 desc, (u64)wwid, handle);
	वापस rc;
पूर्ण

/**
 * _scsih_pcie_device_हटाओ_from_sml -  removing pcie device
 * from SML and मुक्त up associated memory
 * @ioc: per adapter object
 * @pcie_device: the pcie_device object
 */
अटल व्योम
_scsih_pcie_device_हटाओ_from_sml(काष्ठा MPT3SAS_ADAPTER *ioc,
	काष्ठा _pcie_device *pcie_device)
अणु
	काष्ठा MPT3SAS_TARGET *sas_target_priv_data;

	dewtprपूर्णांकk(ioc,
		   ioc_info(ioc, "%s: enter: handle(0x%04x), wwid(0x%016llx)\n",
			    __func__,
			    pcie_device->handle, (u64)pcie_device->wwid));
	अगर (pcie_device->enclosure_handle != 0)
		dewtprपूर्णांकk(ioc,
			   ioc_info(ioc, "%s: enter: enclosure logical id(0x%016llx), slot(%d)\n",
				    __func__,
				    (u64)pcie_device->enclosure_logical_id,
				    pcie_device->slot));
	अगर (pcie_device->connector_name[0] != '\0')
		dewtprपूर्णांकk(ioc,
			   ioc_info(ioc, "%s: enter: enclosure level(0x%04x), connector name(%s)\n",
				    __func__,
				    pcie_device->enclosure_level,
				    pcie_device->connector_name));

	अगर (pcie_device->starget && pcie_device->starget->hostdata) अणु
		sas_target_priv_data = pcie_device->starget->hostdata;
		sas_target_priv_data->deleted = 1;
		_scsih_ublock_io_device(ioc, pcie_device->wwid, शून्य);
		sas_target_priv_data->handle = MPT3SAS_INVALID_DEVICE_HANDLE;
	पूर्ण

	ioc_info(ioc, "removing handle(0x%04x), wwid(0x%016llx)\n",
		 pcie_device->handle, (u64)pcie_device->wwid);
	अगर (pcie_device->enclosure_handle != 0)
		ioc_info(ioc, "removing : enclosure logical id(0x%016llx), slot(%d)\n",
			 (u64)pcie_device->enclosure_logical_id,
			 pcie_device->slot);
	अगर (pcie_device->connector_name[0] != '\0')
		ioc_info(ioc, "removing: enclosure level(0x%04x), connector name( %s)\n",
			 pcie_device->enclosure_level,
			 pcie_device->connector_name);

	अगर (pcie_device->starget && (pcie_device->access_status !=
				MPI26_PCIEDEV0_ASTATUS_DEVICE_BLOCKED))
		scsi_हटाओ_target(&pcie_device->starget->dev);
	dewtprपूर्णांकk(ioc,
		   ioc_info(ioc, "%s: exit: handle(0x%04x), wwid(0x%016llx)\n",
			    __func__,
			    pcie_device->handle, (u64)pcie_device->wwid));
	अगर (pcie_device->enclosure_handle != 0)
		dewtprपूर्णांकk(ioc,
			   ioc_info(ioc, "%s: exit: enclosure logical id(0x%016llx), slot(%d)\n",
				    __func__,
				    (u64)pcie_device->enclosure_logical_id,
				    pcie_device->slot));
	अगर (pcie_device->connector_name[0] != '\0')
		dewtprपूर्णांकk(ioc,
			   ioc_info(ioc, "%s: exit: enclosure level(0x%04x), connector name( %s)\n",
				    __func__,
				    pcie_device->enclosure_level,
				    pcie_device->connector_name));

	kमुक्त(pcie_device->serial_number);
पूर्ण


/**
 * _scsih_pcie_check_device - checking device responsiveness
 * @ioc: per adapter object
 * @handle: attached device handle
 */
अटल व्योम
_scsih_pcie_check_device(काष्ठा MPT3SAS_ADAPTER *ioc, u16 handle)
अणु
	Mpi2ConfigReply_t mpi_reply;
	Mpi26PCIeDevicePage0_t pcie_device_pg0;
	u32 ioc_status;
	काष्ठा _pcie_device *pcie_device;
	u64 wwid;
	अचिन्हित दीर्घ flags;
	काष्ठा scsi_target *starget;
	काष्ठा MPT3SAS_TARGET *sas_target_priv_data;
	u32 device_info;

	अगर ((mpt3sas_config_get_pcie_device_pg0(ioc, &mpi_reply,
		&pcie_device_pg0, MPI26_PCIE_DEVICE_PGAD_FORM_HANDLE, handle)))
		वापस;

	ioc_status = le16_to_cpu(mpi_reply.IOCStatus) & MPI2_IOCSTATUS_MASK;
	अगर (ioc_status != MPI2_IOCSTATUS_SUCCESS)
		वापस;

	/* check अगर this is end device */
	device_info = le32_to_cpu(pcie_device_pg0.DeviceInfo);
	अगर (!(_scsih_is_nvme_pciescsi_device(device_info)))
		वापस;

	wwid = le64_to_cpu(pcie_device_pg0.WWID);
	spin_lock_irqsave(&ioc->pcie_device_lock, flags);
	pcie_device = __mpt3sas_get_pdev_by_wwid(ioc, wwid);

	अगर (!pcie_device) अणु
		spin_unlock_irqrestore(&ioc->pcie_device_lock, flags);
		वापस;
	पूर्ण

	अगर (unlikely(pcie_device->handle != handle)) अणु
		starget = pcie_device->starget;
		sas_target_priv_data = starget->hostdata;
		pcie_device->access_status = pcie_device_pg0.AccessStatus;
		starget_prपूर्णांकk(KERN_INFO, starget,
		    "handle changed from(0x%04x) to (0x%04x)!!!\n",
		    pcie_device->handle, handle);
		sas_target_priv_data->handle = handle;
		pcie_device->handle = handle;

		अगर (le32_to_cpu(pcie_device_pg0.Flags) &
		    MPI26_PCIEDEV0_FLAGS_ENCL_LEVEL_VALID) अणु
			pcie_device->enclosure_level =
			    pcie_device_pg0.EnclosureLevel;
			स_नकल(&pcie_device->connector_name[0],
			    &pcie_device_pg0.ConnectorName[0], 4);
		पूर्ण अन्यथा अणु
			pcie_device->enclosure_level = 0;
			pcie_device->connector_name[0] = '\0';
		पूर्ण
	पूर्ण

	/* check अगर device is present */
	अगर (!(le32_to_cpu(pcie_device_pg0.Flags) &
	    MPI26_PCIEDEV0_FLAGS_DEVICE_PRESENT)) अणु
		ioc_info(ioc, "device is not present handle(0x%04x), flags!!!\n",
			 handle);
		spin_unlock_irqrestore(&ioc->pcie_device_lock, flags);
		pcie_device_put(pcie_device);
		वापस;
	पूर्ण

	/* check अगर there were any issues with discovery */
	अगर (_scsih_check_pcie_access_status(ioc, wwid, handle,
	    pcie_device_pg0.AccessStatus)) अणु
		spin_unlock_irqrestore(&ioc->pcie_device_lock, flags);
		pcie_device_put(pcie_device);
		वापस;
	पूर्ण

	spin_unlock_irqrestore(&ioc->pcie_device_lock, flags);
	pcie_device_put(pcie_device);

	_scsih_ublock_io_device(ioc, wwid, शून्य);

	वापस;
पूर्ण

/**
 * _scsih_pcie_add_device -  creating pcie device object
 * @ioc: per adapter object
 * @handle: pcie device handle
 *
 * Creating end device object, stored in ioc->pcie_device_list.
 *
 * Return: 1 means queue the event later, 0 means complete the event
 */
अटल पूर्णांक
_scsih_pcie_add_device(काष्ठा MPT3SAS_ADAPTER *ioc, u16 handle)
अणु
	Mpi26PCIeDevicePage0_t pcie_device_pg0;
	Mpi26PCIeDevicePage2_t pcie_device_pg2;
	Mpi2ConfigReply_t mpi_reply;
	काष्ठा _pcie_device *pcie_device;
	काष्ठा _enclosure_node *enclosure_dev;
	u32 ioc_status;
	u64 wwid;

	अगर ((mpt3sas_config_get_pcie_device_pg0(ioc, &mpi_reply,
	    &pcie_device_pg0, MPI26_PCIE_DEVICE_PGAD_FORM_HANDLE, handle))) अणु
		ioc_err(ioc, "failure at %s:%d/%s()!\n",
			__खाता__, __LINE__, __func__);
		वापस 0;
	पूर्ण
	ioc_status = le16_to_cpu(mpi_reply.IOCStatus) &
	    MPI2_IOCSTATUS_MASK;
	अगर (ioc_status != MPI2_IOCSTATUS_SUCCESS) अणु
		ioc_err(ioc, "failure at %s:%d/%s()!\n",
			__खाता__, __LINE__, __func__);
		वापस 0;
	पूर्ण

	set_bit(handle, ioc->pend_os_device_add);
	wwid = le64_to_cpu(pcie_device_pg0.WWID);

	/* check अगर device is present */
	अगर (!(le32_to_cpu(pcie_device_pg0.Flags) &
		MPI26_PCIEDEV0_FLAGS_DEVICE_PRESENT)) अणु
		ioc_err(ioc, "device is not present handle(0x04%x)!!!\n",
			handle);
		वापस 0;
	पूर्ण

	/* check अगर there were any issues with discovery */
	अगर (_scsih_check_pcie_access_status(ioc, wwid, handle,
	    pcie_device_pg0.AccessStatus))
		वापस 0;

	अगर (!(_scsih_is_nvme_pciescsi_device(le32_to_cpu
	    (pcie_device_pg0.DeviceInfo))))
		वापस 0;

	pcie_device = mpt3sas_get_pdev_by_wwid(ioc, wwid);
	अगर (pcie_device) अणु
		clear_bit(handle, ioc->pend_os_device_add);
		pcie_device_put(pcie_device);
		वापस 0;
	पूर्ण

	/* PCIe Device Page 2 contains पढ़ो-only inक्रमmation about a
	 * specअगरic NVMe device; thereक्रमe, this page is only
	 * valid क्रम NVMe devices and skip क्रम pcie devices of type scsi.
	 */
	अगर (!(mpt3sas_scsih_is_pcie_scsi_device(
		le32_to_cpu(pcie_device_pg0.DeviceInfo)))) अणु
		अगर (mpt3sas_config_get_pcie_device_pg2(ioc, &mpi_reply,
		    &pcie_device_pg2, MPI2_SAS_DEVICE_PGAD_FORM_HANDLE,
		    handle)) अणु
			ioc_err(ioc,
			    "failure at %s:%d/%s()!\n", __खाता__,
			    __LINE__, __func__);
			वापस 0;
		पूर्ण

		ioc_status = le16_to_cpu(mpi_reply.IOCStatus) &
					MPI2_IOCSTATUS_MASK;
		अगर (ioc_status != MPI2_IOCSTATUS_SUCCESS) अणु
			ioc_err(ioc,
			    "failure at %s:%d/%s()!\n", __खाता__,
			    __LINE__, __func__);
			वापस 0;
		पूर्ण
	पूर्ण

	pcie_device = kzalloc(माप(काष्ठा _pcie_device), GFP_KERNEL);
	अगर (!pcie_device) अणु
		ioc_err(ioc, "failure at %s:%d/%s()!\n",
			__खाता__, __LINE__, __func__);
		वापस 0;
	पूर्ण

	kref_init(&pcie_device->refcount);
	pcie_device->id = ioc->pcie_target_id++;
	pcie_device->channel = PCIE_CHANNEL;
	pcie_device->handle = handle;
	pcie_device->access_status = pcie_device_pg0.AccessStatus;
	pcie_device->device_info = le32_to_cpu(pcie_device_pg0.DeviceInfo);
	pcie_device->wwid = wwid;
	pcie_device->port_num = pcie_device_pg0.PortNum;
	pcie_device->fast_path = (le32_to_cpu(pcie_device_pg0.Flags) &
	    MPI26_PCIEDEV0_FLAGS_FAST_PATH_CAPABLE) ? 1 : 0;

	pcie_device->enclosure_handle =
	    le16_to_cpu(pcie_device_pg0.EnclosureHandle);
	अगर (pcie_device->enclosure_handle != 0)
		pcie_device->slot = le16_to_cpu(pcie_device_pg0.Slot);

	अगर (le32_to_cpu(pcie_device_pg0.Flags) &
	    MPI26_PCIEDEV0_FLAGS_ENCL_LEVEL_VALID) अणु
		pcie_device->enclosure_level = pcie_device_pg0.EnclosureLevel;
		स_नकल(&pcie_device->connector_name[0],
		    &pcie_device_pg0.ConnectorName[0], 4);
	पूर्ण अन्यथा अणु
		pcie_device->enclosure_level = 0;
		pcie_device->connector_name[0] = '\0';
	पूर्ण

	/* get enclosure_logical_id */
	अगर (pcie_device->enclosure_handle) अणु
		enclosure_dev =
			mpt3sas_scsih_enclosure_find_by_handle(ioc,
						pcie_device->enclosure_handle);
		अगर (enclosure_dev)
			pcie_device->enclosure_logical_id =
			    le64_to_cpu(enclosure_dev->pg0.EnclosureLogicalID);
	पूर्ण
	/* TODO -- Add device name once FW supports it */
	अगर (!(mpt3sas_scsih_is_pcie_scsi_device(
	    le32_to_cpu(pcie_device_pg0.DeviceInfo)))) अणु
		pcie_device->nvme_mdts =
		    le32_to_cpu(pcie_device_pg2.MaximumDataTransferSize);
		pcie_device->shutकरोwn_latency =
			le16_to_cpu(pcie_device_pg2.ShutकरोwnLatency);
		/*
		 * Set IOC's max_shutdown_latency to drive's RTD3 Entry Latency
		 * अगर drive's RTD3 Entry Latency is greater then IOC's
		 * max_shutकरोwn_latency.
		 */
		अगर (pcie_device->shutकरोwn_latency > ioc->max_shutकरोwn_latency)
			ioc->max_shutकरोwn_latency =
				pcie_device->shutकरोwn_latency;
		अगर (pcie_device_pg2.ControllerResetTO)
			pcie_device->reset_समयout =
			    pcie_device_pg2.ControllerResetTO;
		अन्यथा
			pcie_device->reset_समयout = 30;
	पूर्ण अन्यथा
		pcie_device->reset_समयout = 30;

	अगर (ioc->रुको_क्रम_discovery_to_complete)
		_scsih_pcie_device_init_add(ioc, pcie_device);
	अन्यथा
		_scsih_pcie_device_add(ioc, pcie_device);

	pcie_device_put(pcie_device);
	वापस 0;
पूर्ण

/**
 * _scsih_pcie_topology_change_event_debug - debug क्रम topology
 * event
 * @ioc: per adapter object
 * @event_data: event data payload
 * Context: user.
 */
अटल व्योम
_scsih_pcie_topology_change_event_debug(काष्ठा MPT3SAS_ADAPTER *ioc,
	Mpi26EventDataPCIeTopologyChangeList_t *event_data)
अणु
	पूर्णांक i;
	u16 handle;
	u16 reason_code;
	u8 port_number;
	अक्षर *status_str = शून्य;
	u8 link_rate, prev_link_rate;

	चयन (event_data->SwitchStatus) अणु
	हाल MPI26_EVENT_PCIE_TOPO_SS_ADDED:
		status_str = "add";
		अवरोध;
	हाल MPI26_EVENT_PCIE_TOPO_SS_NOT_RESPONDING:
		status_str = "remove";
		अवरोध;
	हाल MPI26_EVENT_PCIE_TOPO_SS_RESPONDING:
	हाल 0:
		status_str =  "responding";
		अवरोध;
	हाल MPI26_EVENT_PCIE_TOPO_SS_DELAY_NOT_RESPONDING:
		status_str = "remove delay";
		अवरोध;
	शेष:
		status_str = "unknown status";
		अवरोध;
	पूर्ण
	ioc_info(ioc, "pcie topology change: (%s)\n", status_str);
	pr_info("\tswitch_handle(0x%04x), enclosure_handle(0x%04x)"
		"start_port(%02d), count(%d)\n",
		le16_to_cpu(event_data->SwitchDevHandle),
		le16_to_cpu(event_data->EnclosureHandle),
		event_data->StartPortNum, event_data->NumEntries);
	क्रम (i = 0; i < event_data->NumEntries; i++) अणु
		handle =
			le16_to_cpu(event_data->PortEntry[i].AttachedDevHandle);
		अगर (!handle)
			जारी;
		port_number = event_data->StartPortNum + i;
		reason_code = event_data->PortEntry[i].PortStatus;
		चयन (reason_code) अणु
		हाल MPI26_EVENT_PCIE_TOPO_PS_DEV_ADDED:
			status_str = "target add";
			अवरोध;
		हाल MPI26_EVENT_PCIE_TOPO_PS_NOT_RESPONDING:
			status_str = "target remove";
			अवरोध;
		हाल MPI26_EVENT_PCIE_TOPO_PS_DELAY_NOT_RESPONDING:
			status_str = "delay target remove";
			अवरोध;
		हाल MPI26_EVENT_PCIE_TOPO_PS_PORT_CHANGED:
			status_str = "link rate change";
			अवरोध;
		हाल MPI26_EVENT_PCIE_TOPO_PS_NO_CHANGE:
			status_str = "target responding";
			अवरोध;
		शेष:
			status_str = "unknown";
			अवरोध;
		पूर्ण
		link_rate = event_data->PortEntry[i].CurrentPortInfo &
			MPI26_EVENT_PCIE_TOPO_PI_RATE_MASK;
		prev_link_rate = event_data->PortEntry[i].PreviousPortInfo &
			MPI26_EVENT_PCIE_TOPO_PI_RATE_MASK;
		pr_info("\tport(%02d), attached_handle(0x%04x): %s:"
			" link rate: new(0x%02x), old(0x%02x)\n", port_number,
			handle, status_str, link_rate, prev_link_rate);
	पूर्ण
पूर्ण

/**
 * _scsih_pcie_topology_change_event - handle PCIe topology
 *  changes
 * @ioc: per adapter object
 * @fw_event: The fw_event_work object
 * Context: user.
 *
 */
अटल व्योम
_scsih_pcie_topology_change_event(काष्ठा MPT3SAS_ADAPTER *ioc,
	काष्ठा fw_event_work *fw_event)
अणु
	पूर्णांक i;
	u16 handle;
	u16 reason_code;
	u8 link_rate, prev_link_rate;
	अचिन्हित दीर्घ flags;
	पूर्णांक rc;
	Mpi26EventDataPCIeTopologyChangeList_t *event_data =
		(Mpi26EventDataPCIeTopologyChangeList_t *) fw_event->event_data;
	काष्ठा _pcie_device *pcie_device;

	अगर (ioc->logging_level & MPT_DEBUG_EVENT_WORK_TASK)
		_scsih_pcie_topology_change_event_debug(ioc, event_data);

	अगर (ioc->shost_recovery || ioc->हटाओ_host ||
		ioc->pci_error_recovery)
		वापस;

	अगर (fw_event->ignore) अणु
		dewtprपूर्णांकk(ioc, ioc_info(ioc, "ignoring switch event\n"));
		वापस;
	पूर्ण

	/* handle siblings events */
	क्रम (i = 0; i < event_data->NumEntries; i++) अणु
		अगर (fw_event->ignore) अणु
			dewtprपूर्णांकk(ioc,
				   ioc_info(ioc, "ignoring switch event\n"));
			वापस;
		पूर्ण
		अगर (ioc->हटाओ_host || ioc->pci_error_recovery)
			वापस;
		reason_code = event_data->PortEntry[i].PortStatus;
		handle =
			le16_to_cpu(event_data->PortEntry[i].AttachedDevHandle);
		अगर (!handle)
			जारी;

		link_rate = event_data->PortEntry[i].CurrentPortInfo
			& MPI26_EVENT_PCIE_TOPO_PI_RATE_MASK;
		prev_link_rate = event_data->PortEntry[i].PreviousPortInfo
			& MPI26_EVENT_PCIE_TOPO_PI_RATE_MASK;

		चयन (reason_code) अणु
		हाल MPI26_EVENT_PCIE_TOPO_PS_PORT_CHANGED:
			अगर (ioc->shost_recovery)
				अवरोध;
			अगर (link_rate == prev_link_rate)
				अवरोध;
			अगर (link_rate < MPI26_EVENT_PCIE_TOPO_PI_RATE_2_5)
				अवरोध;

			_scsih_pcie_check_device(ioc, handle);

			/* This code after this poपूर्णांक handles the test हाल
			 * where a device has been added, however its वापसing
			 * BUSY क्रम someसमय.  Then beक्रमe the Device Missing
			 * Delay expires and the device becomes READY, the
			 * device is हटाओd and added back.
			 */
			spin_lock_irqsave(&ioc->pcie_device_lock, flags);
			pcie_device = __mpt3sas_get_pdev_by_handle(ioc, handle);
			spin_unlock_irqrestore(&ioc->pcie_device_lock, flags);

			अगर (pcie_device) अणु
				pcie_device_put(pcie_device);
				अवरोध;
			पूर्ण

			अगर (!test_bit(handle, ioc->pend_os_device_add))
				अवरोध;

			dewtprपूर्णांकk(ioc,
				   ioc_info(ioc, "handle(0x%04x) device not found: convert event to a device add\n",
					    handle));
			event_data->PortEntry[i].PortStatus &= 0xF0;
			event_data->PortEntry[i].PortStatus |=
				MPI26_EVENT_PCIE_TOPO_PS_DEV_ADDED;
			fallthrough;
		हाल MPI26_EVENT_PCIE_TOPO_PS_DEV_ADDED:
			अगर (ioc->shost_recovery)
				अवरोध;
			अगर (link_rate < MPI26_EVENT_PCIE_TOPO_PI_RATE_2_5)
				अवरोध;

			rc = _scsih_pcie_add_device(ioc, handle);
			अगर (!rc) अणु
				/* mark entry vacant */
				/* TODO This needs to be reviewed and fixed,
				 * we करोnt have an entry
				 * to make an event व्योम like vacant
				 */
				event_data->PortEntry[i].PortStatus |=
					MPI26_EVENT_PCIE_TOPO_PS_NO_CHANGE;
			पूर्ण
			अवरोध;
		हाल MPI26_EVENT_PCIE_TOPO_PS_NOT_RESPONDING:
			_scsih_pcie_device_हटाओ_by_handle(ioc, handle);
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

/**
 * _scsih_pcie_device_status_change_event_debug - debug क्रम device event
 * @ioc: ?
 * @event_data: event data payload
 * Context: user.
 */
अटल व्योम
_scsih_pcie_device_status_change_event_debug(काष्ठा MPT3SAS_ADAPTER *ioc,
	Mpi26EventDataPCIeDeviceStatusChange_t *event_data)
अणु
	अक्षर *reason_str = शून्य;

	चयन (event_data->ReasonCode) अणु
	हाल MPI26_EVENT_PCIDEV_STAT_RC_SMART_DATA:
		reason_str = "smart data";
		अवरोध;
	हाल MPI26_EVENT_PCIDEV_STAT_RC_UNSUPPORTED:
		reason_str = "unsupported device discovered";
		अवरोध;
	हाल MPI26_EVENT_PCIDEV_STAT_RC_INTERNAL_DEVICE_RESET:
		reason_str = "internal device reset";
		अवरोध;
	हाल MPI26_EVENT_PCIDEV_STAT_RC_TASK_ABORT_INTERNAL:
		reason_str = "internal task abort";
		अवरोध;
	हाल MPI26_EVENT_PCIDEV_STAT_RC_ABORT_TASK_SET_INTERNAL:
		reason_str = "internal task abort set";
		अवरोध;
	हाल MPI26_EVENT_PCIDEV_STAT_RC_CLEAR_TASK_SET_INTERNAL:
		reason_str = "internal clear task set";
		अवरोध;
	हाल MPI26_EVENT_PCIDEV_STAT_RC_QUERY_TASK_INTERNAL:
		reason_str = "internal query task";
		अवरोध;
	हाल MPI26_EVENT_PCIDEV_STAT_RC_DEV_INIT_FAILURE:
		reason_str = "device init failure";
		अवरोध;
	हाल MPI26_EVENT_PCIDEV_STAT_RC_CMP_INTERNAL_DEV_RESET:
		reason_str = "internal device reset complete";
		अवरोध;
	हाल MPI26_EVENT_PCIDEV_STAT_RC_CMP_TASK_ABORT_INTERNAL:
		reason_str = "internal task abort complete";
		अवरोध;
	हाल MPI26_EVENT_PCIDEV_STAT_RC_ASYNC_NOTIFICATION:
		reason_str = "internal async notification";
		अवरोध;
	हाल MPI26_EVENT_PCIDEV_STAT_RC_PCIE_HOT_RESET_FAILED:
		reason_str = "pcie hot reset failed";
		अवरोध;
	शेष:
		reason_str = "unknown reason";
		अवरोध;
	पूर्ण

	ioc_info(ioc, "PCIE device status change: (%s)\n"
		 "\thandle(0x%04x), WWID(0x%016llx), tag(%d)",
		 reason_str, le16_to_cpu(event_data->DevHandle),
		 (u64)le64_to_cpu(event_data->WWID),
		 le16_to_cpu(event_data->TaskTag));
	अगर (event_data->ReasonCode == MPI26_EVENT_PCIDEV_STAT_RC_SMART_DATA)
		pr_cont(", ASC(0x%x), ASCQ(0x%x)\n",
			event_data->ASC, event_data->ASCQ);
	pr_cont("\n");
पूर्ण

/**
 * _scsih_pcie_device_status_change_event - handle device status
 * change
 * @ioc: per adapter object
 * @fw_event: The fw_event_work object
 * Context: user.
 */
अटल व्योम
_scsih_pcie_device_status_change_event(काष्ठा MPT3SAS_ADAPTER *ioc,
	काष्ठा fw_event_work *fw_event)
अणु
	काष्ठा MPT3SAS_TARGET *target_priv_data;
	काष्ठा _pcie_device *pcie_device;
	u64 wwid;
	अचिन्हित दीर्घ flags;
	Mpi26EventDataPCIeDeviceStatusChange_t *event_data =
		(Mpi26EventDataPCIeDeviceStatusChange_t *)fw_event->event_data;
	अगर (ioc->logging_level & MPT_DEBUG_EVENT_WORK_TASK)
		_scsih_pcie_device_status_change_event_debug(ioc,
			event_data);

	अगर (event_data->ReasonCode !=
		MPI26_EVENT_PCIDEV_STAT_RC_INTERNAL_DEVICE_RESET &&
		event_data->ReasonCode !=
		MPI26_EVENT_PCIDEV_STAT_RC_CMP_INTERNAL_DEV_RESET)
		वापस;

	spin_lock_irqsave(&ioc->pcie_device_lock, flags);
	wwid = le64_to_cpu(event_data->WWID);
	pcie_device = __mpt3sas_get_pdev_by_wwid(ioc, wwid);

	अगर (!pcie_device || !pcie_device->starget)
		जाओ out;

	target_priv_data = pcie_device->starget->hostdata;
	अगर (!target_priv_data)
		जाओ out;

	अगर (event_data->ReasonCode ==
		MPI26_EVENT_PCIDEV_STAT_RC_INTERNAL_DEVICE_RESET)
		target_priv_data->पंचांग_busy = 1;
	अन्यथा
		target_priv_data->पंचांग_busy = 0;
out:
	अगर (pcie_device)
		pcie_device_put(pcie_device);

	spin_unlock_irqrestore(&ioc->pcie_device_lock, flags);
पूर्ण

/**
 * _scsih_sas_enclosure_dev_status_change_event_debug - debug क्रम enclosure
 * event
 * @ioc: per adapter object
 * @event_data: event data payload
 * Context: user.
 */
अटल व्योम
_scsih_sas_enclosure_dev_status_change_event_debug(काष्ठा MPT3SAS_ADAPTER *ioc,
	Mpi2EventDataSasEnclDevStatusChange_t *event_data)
अणु
	अक्षर *reason_str = शून्य;

	चयन (event_data->ReasonCode) अणु
	हाल MPI2_EVENT_SAS_ENCL_RC_ADDED:
		reason_str = "enclosure add";
		अवरोध;
	हाल MPI2_EVENT_SAS_ENCL_RC_NOT_RESPONDING:
		reason_str = "enclosure remove";
		अवरोध;
	शेष:
		reason_str = "unknown reason";
		अवरोध;
	पूर्ण

	ioc_info(ioc, "enclosure status change: (%s)\n"
		 "\thandle(0x%04x), enclosure logical id(0x%016llx) number slots(%d)\n",
		 reason_str,
		 le16_to_cpu(event_data->EnclosureHandle),
		 (u64)le64_to_cpu(event_data->EnclosureLogicalID),
		 le16_to_cpu(event_data->StartSlot));
पूर्ण

/**
 * _scsih_sas_enclosure_dev_status_change_event - handle enclosure events
 * @ioc: per adapter object
 * @fw_event: The fw_event_work object
 * Context: user.
 */
अटल व्योम
_scsih_sas_enclosure_dev_status_change_event(काष्ठा MPT3SAS_ADAPTER *ioc,
	काष्ठा fw_event_work *fw_event)
अणु
	Mpi2ConfigReply_t mpi_reply;
	काष्ठा _enclosure_node *enclosure_dev = शून्य;
	Mpi2EventDataSasEnclDevStatusChange_t *event_data =
		(Mpi2EventDataSasEnclDevStatusChange_t *)fw_event->event_data;
	पूर्णांक rc;
	u16 enclosure_handle = le16_to_cpu(event_data->EnclosureHandle);

	अगर (ioc->logging_level & MPT_DEBUG_EVENT_WORK_TASK)
		_scsih_sas_enclosure_dev_status_change_event_debug(ioc,
		     (Mpi2EventDataSasEnclDevStatusChange_t *)
		     fw_event->event_data);
	अगर (ioc->shost_recovery)
		वापस;

	अगर (enclosure_handle)
		enclosure_dev =
			mpt3sas_scsih_enclosure_find_by_handle(ioc,
						enclosure_handle);
	चयन (event_data->ReasonCode) अणु
	हाल MPI2_EVENT_SAS_ENCL_RC_ADDED:
		अगर (!enclosure_dev) अणु
			enclosure_dev =
				kzalloc(माप(काष्ठा _enclosure_node),
					GFP_KERNEL);
			अगर (!enclosure_dev) अणु
				ioc_info(ioc, "failure at %s:%d/%s()!\n",
					 __खाता__, __LINE__, __func__);
				वापस;
			पूर्ण
			rc = mpt3sas_config_get_enclosure_pg0(ioc, &mpi_reply,
				&enclosure_dev->pg0,
				MPI2_SAS_ENCLOS_PGAD_FORM_HANDLE,
				enclosure_handle);

			अगर (rc || (le16_to_cpu(mpi_reply.IOCStatus) &
						MPI2_IOCSTATUS_MASK)) अणु
				kमुक्त(enclosure_dev);
				वापस;
			पूर्ण

			list_add_tail(&enclosure_dev->list,
							&ioc->enclosure_list);
		पूर्ण
		अवरोध;
	हाल MPI2_EVENT_SAS_ENCL_RC_NOT_RESPONDING:
		अगर (enclosure_dev) अणु
			list_del(&enclosure_dev->list);
			kमुक्त(enclosure_dev);
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

/**
 * _scsih_sas_broadcast_primitive_event - handle broadcast events
 * @ioc: per adapter object
 * @fw_event: The fw_event_work object
 * Context: user.
 */
अटल व्योम
_scsih_sas_broadcast_primitive_event(काष्ठा MPT3SAS_ADAPTER *ioc,
	काष्ठा fw_event_work *fw_event)
अणु
	काष्ठा scsi_cmnd *scmd;
	काष्ठा scsi_device *sdev;
	काष्ठा scsiio_tracker *st;
	u16 smid, handle;
	u32 lun;
	काष्ठा MPT3SAS_DEVICE *sas_device_priv_data;
	u32 termination_count;
	u32 query_count;
	Mpi2SCSITaskManagementReply_t *mpi_reply;
	Mpi2EventDataSasBroadcastPrimitive_t *event_data =
		(Mpi2EventDataSasBroadcastPrimitive_t *)
		fw_event->event_data;
	u16 ioc_status;
	अचिन्हित दीर्घ flags;
	पूर्णांक r;
	u8 max_retries = 0;
	u8 task_पात_retries;

	mutex_lock(&ioc->पंचांग_cmds.mutex);
	ioc_info(ioc, "%s: enter: phy number(%d), width(%d)\n",
		 __func__, event_data->PhyNum, event_data->PortWidth);

	_scsih_block_io_all_device(ioc);

	spin_lock_irqsave(&ioc->scsi_lookup_lock, flags);
	mpi_reply = ioc->पंचांग_cmds.reply;
 broadcast_aen_retry:

	/* sanity checks क्रम retrying this loop */
	अगर (max_retries++ == 5) अणु
		dewtprपूर्णांकk(ioc, ioc_info(ioc, "%s: giving up\n", __func__));
		जाओ out;
	पूर्ण अन्यथा अगर (max_retries > 1)
		dewtprपूर्णांकk(ioc,
			   ioc_info(ioc, "%s: %d retry\n",
				    __func__, max_retries - 1));

	termination_count = 0;
	query_count = 0;
	क्रम (smid = 1; smid <= ioc->scsiio_depth; smid++) अणु
		अगर (ioc->shost_recovery)
			जाओ out;
		scmd = mpt3sas_scsih_scsi_lookup_get(ioc, smid);
		अगर (!scmd)
			जारी;
		st = scsi_cmd_priv(scmd);
		sdev = scmd->device;
		sas_device_priv_data = sdev->hostdata;
		अगर (!sas_device_priv_data || !sas_device_priv_data->sas_target)
			जारी;
		 /* skip hidden raid components */
		अगर (sas_device_priv_data->sas_target->flags &
		    MPT_TARGET_FLAGS_RAID_COMPONENT)
			जारी;
		 /* skip volumes */
		अगर (sas_device_priv_data->sas_target->flags &
		    MPT_TARGET_FLAGS_VOLUME)
			जारी;
		 /* skip PCIe devices */
		अगर (sas_device_priv_data->sas_target->flags &
		    MPT_TARGET_FLAGS_PCIE_DEVICE)
			जारी;

		handle = sas_device_priv_data->sas_target->handle;
		lun = sas_device_priv_data->lun;
		query_count++;

		अगर (ioc->shost_recovery)
			जाओ out;

		spin_unlock_irqrestore(&ioc->scsi_lookup_lock, flags);
		r = mpt3sas_scsih_issue_पंचांग(ioc, handle, 0, 0, lun,
			MPI2_SCSITASKMGMT_TASKTYPE_QUERY_TASK, st->smid,
			st->msix_io, 30, 0);
		अगर (r == FAILED) अणु
			sdev_prपूर्णांकk(KERN_WARNING, sdev,
			    "mpt3sas_scsih_issue_tm: FAILED when sending "
			    "QUERY_TASK: scmd(%p)\n", scmd);
			spin_lock_irqsave(&ioc->scsi_lookup_lock, flags);
			जाओ broadcast_aen_retry;
		पूर्ण
		ioc_status = le16_to_cpu(mpi_reply->IOCStatus)
		    & MPI2_IOCSTATUS_MASK;
		अगर (ioc_status != MPI2_IOCSTATUS_SUCCESS) अणु
			sdev_prपूर्णांकk(KERN_WARNING, sdev,
				"query task: FAILED with IOCSTATUS(0x%04x), scmd(%p)\n",
				ioc_status, scmd);
			spin_lock_irqsave(&ioc->scsi_lookup_lock, flags);
			जाओ broadcast_aen_retry;
		पूर्ण

		/* see अगर IO is still owned by IOC and target */
		अगर (mpi_reply->ResponseCode ==
		     MPI2_SCSITASKMGMT_RSP_TM_SUCCEEDED ||
		     mpi_reply->ResponseCode ==
		     MPI2_SCSITASKMGMT_RSP_IO_QUEUED_ON_IOC) अणु
			spin_lock_irqsave(&ioc->scsi_lookup_lock, flags);
			जारी;
		पूर्ण
		task_पात_retries = 0;
 पंचांग_retry:
		अगर (task_पात_retries++ == 60) अणु
			dewtprपूर्णांकk(ioc,
				   ioc_info(ioc, "%s: ABORT_TASK: giving up\n",
					    __func__));
			spin_lock_irqsave(&ioc->scsi_lookup_lock, flags);
			जाओ broadcast_aen_retry;
		पूर्ण

		अगर (ioc->shost_recovery)
			जाओ out_no_lock;

		r = mpt3sas_scsih_issue_पंचांग(ioc, handle, sdev->channel, sdev->id,
			sdev->lun, MPI2_SCSITASKMGMT_TASKTYPE_ABORT_TASK,
			st->smid, st->msix_io, 30, 0);
		अगर (r == FAILED || st->cb_idx != 0xFF) अणु
			sdev_prपूर्णांकk(KERN_WARNING, sdev,
			    "mpt3sas_scsih_issue_tm: ABORT_TASK: FAILED : "
			    "scmd(%p)\n", scmd);
			जाओ पंचांग_retry;
		पूर्ण

		अगर (task_पात_retries > 1)
			sdev_prपूर्णांकk(KERN_WARNING, sdev,
			    "mpt3sas_scsih_issue_tm: ABORT_TASK: RETRIES (%d):"
			    " scmd(%p)\n",
			    task_पात_retries - 1, scmd);

		termination_count += le32_to_cpu(mpi_reply->TerminationCount);
		spin_lock_irqsave(&ioc->scsi_lookup_lock, flags);
	पूर्ण

	अगर (ioc->broadcast_aen_pending) अणु
		dewtprपूर्णांकk(ioc,
			   ioc_info(ioc,
				    "%s: loop back due to pending AEN\n",
				    __func__));
		 ioc->broadcast_aen_pending = 0;
		 जाओ broadcast_aen_retry;
	पूर्ण

 out:
	spin_unlock_irqrestore(&ioc->scsi_lookup_lock, flags);
 out_no_lock:

	dewtprपूर्णांकk(ioc,
		   ioc_info(ioc, "%s - exit, query_count = %d termination_count = %d\n",
			    __func__, query_count, termination_count));

	ioc->broadcast_aen_busy = 0;
	अगर (!ioc->shost_recovery)
		_scsih_ublock_io_all_device(ioc);
	mutex_unlock(&ioc->पंचांग_cmds.mutex);
पूर्ण

/**
 * _scsih_sas_discovery_event - handle discovery events
 * @ioc: per adapter object
 * @fw_event: The fw_event_work object
 * Context: user.
 */
अटल व्योम
_scsih_sas_discovery_event(काष्ठा MPT3SAS_ADAPTER *ioc,
	काष्ठा fw_event_work *fw_event)
अणु
	Mpi2EventDataSasDiscovery_t *event_data =
		(Mpi2EventDataSasDiscovery_t *) fw_event->event_data;

	अगर (ioc->logging_level & MPT_DEBUG_EVENT_WORK_TASK) अणु
		ioc_info(ioc, "discovery event: (%s)",
			 event_data->ReasonCode == MPI2_EVENT_SAS_DISC_RC_STARTED ?
			 "start" : "stop");
		अगर (event_data->DiscoveryStatus)
			pr_cont("discovery_status(0x%08x)",
				le32_to_cpu(event_data->DiscoveryStatus));
		pr_cont("\n");
	पूर्ण

	अगर (event_data->ReasonCode == MPI2_EVENT_SAS_DISC_RC_STARTED &&
	    !ioc->sas_hba.num_phys) अणु
		अगर (disable_discovery > 0 && ioc->shost_recovery) अणु
			/* Wait क्रम the reset to complete */
			जबतक (ioc->shost_recovery)
				ssleep(1);
		पूर्ण
		_scsih_sas_host_add(ioc);
	पूर्ण
पूर्ण

/**
 * _scsih_sas_device_discovery_error_event - display SAS device discovery error
 *						events
 * @ioc: per adapter object
 * @fw_event: The fw_event_work object
 * Context: user.
 */
अटल व्योम
_scsih_sas_device_discovery_error_event(काष्ठा MPT3SAS_ADAPTER *ioc,
	काष्ठा fw_event_work *fw_event)
अणु
	Mpi25EventDataSasDeviceDiscoveryError_t *event_data =
		(Mpi25EventDataSasDeviceDiscoveryError_t *)fw_event->event_data;

	चयन (event_data->ReasonCode) अणु
	हाल MPI25_EVENT_SAS_DISC_ERR_SMP_FAILED:
		ioc_warn(ioc, "SMP command sent to the expander (handle:0x%04x, sas_address:0x%016llx, physical_port:0x%02x) has failed\n",
			 le16_to_cpu(event_data->DevHandle),
			 (u64)le64_to_cpu(event_data->SASAddress),
			 event_data->PhysicalPort);
		अवरोध;
	हाल MPI25_EVENT_SAS_DISC_ERR_SMP_TIMEOUT:
		ioc_warn(ioc, "SMP command sent to the expander (handle:0x%04x, sas_address:0x%016llx, physical_port:0x%02x) has timed out\n",
			 le16_to_cpu(event_data->DevHandle),
			 (u64)le64_to_cpu(event_data->SASAddress),
			 event_data->PhysicalPort);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

/**
 * _scsih_pcie_क्रमागतeration_event - handle क्रमागतeration events
 * @ioc: per adapter object
 * @fw_event: The fw_event_work object
 * Context: user.
 */
अटल व्योम
_scsih_pcie_क्रमागतeration_event(काष्ठा MPT3SAS_ADAPTER *ioc,
	काष्ठा fw_event_work *fw_event)
अणु
	Mpi26EventDataPCIeEnumeration_t *event_data =
		(Mpi26EventDataPCIeEnumeration_t *)fw_event->event_data;

	अगर (!(ioc->logging_level & MPT_DEBUG_EVENT_WORK_TASK))
		वापस;

	ioc_info(ioc, "pcie enumeration event: (%s) Flag 0x%02x",
		 (event_data->ReasonCode == MPI26_EVENT_PCIE_ENUM_RC_STARTED) ?
		 "started" : "completed",
		 event_data->Flags);
	अगर (event_data->EnumerationStatus)
		pr_cont("enumeration_status(0x%08x)",
			le32_to_cpu(event_data->EnumerationStatus));
	pr_cont("\n");
पूर्ण

/**
 * _scsih_ir_fastpath - turn on fastpath क्रम IR physdisk
 * @ioc: per adapter object
 * @handle: device handle क्रम physical disk
 * @phys_disk_num: physical disk number
 *
 * Return: 0 क्रम success, अन्यथा failure.
 */
अटल पूर्णांक
_scsih_ir_fastpath(काष्ठा MPT3SAS_ADAPTER *ioc, u16 handle, u8 phys_disk_num)
अणु
	Mpi2RaidActionRequest_t *mpi_request;
	Mpi2RaidActionReply_t *mpi_reply;
	u16 smid;
	u8 issue_reset = 0;
	पूर्णांक rc = 0;
	u16 ioc_status;
	u32 log_info;

	अगर (ioc->hba_mpi_version_beदीर्घed == MPI2_VERSION)
		वापस rc;

	mutex_lock(&ioc->scsih_cmds.mutex);

	अगर (ioc->scsih_cmds.status != MPT3_CMD_NOT_USED) अणु
		ioc_err(ioc, "%s: scsih_cmd in use\n", __func__);
		rc = -EAGAIN;
		जाओ out;
	पूर्ण
	ioc->scsih_cmds.status = MPT3_CMD_PENDING;

	smid = mpt3sas_base_get_smid(ioc, ioc->scsih_cb_idx);
	अगर (!smid) अणु
		ioc_err(ioc, "%s: failed obtaining a smid\n", __func__);
		ioc->scsih_cmds.status = MPT3_CMD_NOT_USED;
		rc = -EAGAIN;
		जाओ out;
	पूर्ण

	mpi_request = mpt3sas_base_get_msg_frame(ioc, smid);
	ioc->scsih_cmds.smid = smid;
	स_रखो(mpi_request, 0, माप(Mpi2RaidActionRequest_t));

	mpi_request->Function = MPI2_FUNCTION_RAID_ACTION;
	mpi_request->Action = MPI2_RAID_ACTION_PHYSDISK_HIDDEN;
	mpi_request->PhysDiskNum = phys_disk_num;

	dewtprपूर्णांकk(ioc,
		   ioc_info(ioc, "IR RAID_ACTION: turning fast path on for handle(0x%04x), phys_disk_num (0x%02x)\n",
			    handle, phys_disk_num));

	init_completion(&ioc->scsih_cmds.करोne);
	ioc->put_smid_शेष(ioc, smid);
	रुको_क्रम_completion_समयout(&ioc->scsih_cmds.करोne, 10*HZ);

	अगर (!(ioc->scsih_cmds.status & MPT3_CMD_COMPLETE)) अणु
		mpt3sas_check_cmd_समयout(ioc,
		    ioc->scsih_cmds.status, mpi_request,
		    माप(Mpi2RaidActionRequest_t)/4, issue_reset);
		rc = -EFAULT;
		जाओ out;
	पूर्ण

	अगर (ioc->scsih_cmds.status & MPT3_CMD_REPLY_VALID) अणु

		mpi_reply = ioc->scsih_cmds.reply;
		ioc_status = le16_to_cpu(mpi_reply->IOCStatus);
		अगर (ioc_status & MPI2_IOCSTATUS_FLAG_LOG_INFO_AVAILABLE)
			log_info =  le32_to_cpu(mpi_reply->IOCLogInfo);
		अन्यथा
			log_info = 0;
		ioc_status &= MPI2_IOCSTATUS_MASK;
		अगर (ioc_status != MPI2_IOCSTATUS_SUCCESS) अणु
			dewtprपूर्णांकk(ioc,
				   ioc_info(ioc, "IR RAID_ACTION: failed: ioc_status(0x%04x), loginfo(0x%08x)!!!\n",
					    ioc_status, log_info));
			rc = -EFAULT;
		पूर्ण अन्यथा
			dewtprपूर्णांकk(ioc,
				   ioc_info(ioc, "IR RAID_ACTION: completed successfully\n"));
	पूर्ण

 out:
	ioc->scsih_cmds.status = MPT3_CMD_NOT_USED;
	mutex_unlock(&ioc->scsih_cmds.mutex);

	अगर (issue_reset)
		mpt3sas_base_hard_reset_handler(ioc, FORCE_BIG_HAMMER);
	वापस rc;
पूर्ण

/**
 * _scsih_reprobe_lun - reprobing lun
 * @sdev: scsi device काष्ठा
 * @no_uld_attach: sdev->no_uld_attach flag setting
 *
 **/
अटल व्योम
_scsih_reprobe_lun(काष्ठा scsi_device *sdev, व्योम *no_uld_attach)
अणु
	sdev->no_uld_attach = no_uld_attach ? 1 : 0;
	sdev_prपूर्णांकk(KERN_INFO, sdev, "%s raid component\n",
	    sdev->no_uld_attach ? "hiding" : "exposing");
	WARN_ON(scsi_device_reprobe(sdev));
पूर्ण

/**
 * _scsih_sas_volume_add - add new volume
 * @ioc: per adapter object
 * @element: IR config element data
 * Context: user.
 */
अटल व्योम
_scsih_sas_volume_add(काष्ठा MPT3SAS_ADAPTER *ioc,
	Mpi2EventIrConfigElement_t *element)
अणु
	काष्ठा _raid_device *raid_device;
	अचिन्हित दीर्घ flags;
	u64 wwid;
	u16 handle = le16_to_cpu(element->VolDevHandle);
	पूर्णांक rc;

	mpt3sas_config_get_volume_wwid(ioc, handle, &wwid);
	अगर (!wwid) अणु
		ioc_err(ioc, "failure at %s:%d/%s()!\n",
			__खाता__, __LINE__, __func__);
		वापस;
	पूर्ण

	spin_lock_irqsave(&ioc->raid_device_lock, flags);
	raid_device = _scsih_raid_device_find_by_wwid(ioc, wwid);
	spin_unlock_irqrestore(&ioc->raid_device_lock, flags);

	अगर (raid_device)
		वापस;

	raid_device = kzalloc(माप(काष्ठा _raid_device), GFP_KERNEL);
	अगर (!raid_device) अणु
		ioc_err(ioc, "failure at %s:%d/%s()!\n",
			__खाता__, __LINE__, __func__);
		वापस;
	पूर्ण

	raid_device->id = ioc->sas_id++;
	raid_device->channel = RAID_CHANNEL;
	raid_device->handle = handle;
	raid_device->wwid = wwid;
	_scsih_raid_device_add(ioc, raid_device);
	अगर (!ioc->रुको_क्रम_discovery_to_complete) अणु
		rc = scsi_add_device(ioc->shost, RAID_CHANNEL,
		    raid_device->id, 0);
		अगर (rc)
			_scsih_raid_device_हटाओ(ioc, raid_device);
	पूर्ण अन्यथा अणु
		spin_lock_irqsave(&ioc->raid_device_lock, flags);
		_scsih_determine_boot_device(ioc, raid_device, 1);
		spin_unlock_irqrestore(&ioc->raid_device_lock, flags);
	पूर्ण
पूर्ण

/**
 * _scsih_sas_volume_delete - delete volume
 * @ioc: per adapter object
 * @handle: volume device handle
 * Context: user.
 */
अटल व्योम
_scsih_sas_volume_delete(काष्ठा MPT3SAS_ADAPTER *ioc, u16 handle)
अणु
	काष्ठा _raid_device *raid_device;
	अचिन्हित दीर्घ flags;
	काष्ठा MPT3SAS_TARGET *sas_target_priv_data;
	काष्ठा scsi_target *starget = शून्य;

	spin_lock_irqsave(&ioc->raid_device_lock, flags);
	raid_device = mpt3sas_raid_device_find_by_handle(ioc, handle);
	अगर (raid_device) अणु
		अगर (raid_device->starget) अणु
			starget = raid_device->starget;
			sas_target_priv_data = starget->hostdata;
			sas_target_priv_data->deleted = 1;
		पूर्ण
		ioc_info(ioc, "removing handle(0x%04x), wwid(0x%016llx)\n",
			 raid_device->handle, (u64)raid_device->wwid);
		list_del(&raid_device->list);
		kमुक्त(raid_device);
	पूर्ण
	spin_unlock_irqrestore(&ioc->raid_device_lock, flags);
	अगर (starget)
		scsi_हटाओ_target(&starget->dev);
पूर्ण

/**
 * _scsih_sas_pd_expose - expose pd component to /dev/sdX
 * @ioc: per adapter object
 * @element: IR config element data
 * Context: user.
 */
अटल व्योम
_scsih_sas_pd_expose(काष्ठा MPT3SAS_ADAPTER *ioc,
	Mpi2EventIrConfigElement_t *element)
अणु
	काष्ठा _sas_device *sas_device;
	काष्ठा scsi_target *starget = शून्य;
	काष्ठा MPT3SAS_TARGET *sas_target_priv_data;
	अचिन्हित दीर्घ flags;
	u16 handle = le16_to_cpu(element->PhysDiskDevHandle);

	spin_lock_irqsave(&ioc->sas_device_lock, flags);
	sas_device = __mpt3sas_get_sdev_by_handle(ioc, handle);
	अगर (sas_device) अणु
		sas_device->volume_handle = 0;
		sas_device->volume_wwid = 0;
		clear_bit(handle, ioc->pd_handles);
		अगर (sas_device->starget && sas_device->starget->hostdata) अणु
			starget = sas_device->starget;
			sas_target_priv_data = starget->hostdata;
			sas_target_priv_data->flags &=
			    ~MPT_TARGET_FLAGS_RAID_COMPONENT;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&ioc->sas_device_lock, flags);
	अगर (!sas_device)
		वापस;

	/* exposing raid component */
	अगर (starget)
		starget_क्रम_each_device(starget, शून्य, _scsih_reprobe_lun);

	sas_device_put(sas_device);
पूर्ण

/**
 * _scsih_sas_pd_hide - hide pd component from /dev/sdX
 * @ioc: per adapter object
 * @element: IR config element data
 * Context: user.
 */
अटल व्योम
_scsih_sas_pd_hide(काष्ठा MPT3SAS_ADAPTER *ioc,
	Mpi2EventIrConfigElement_t *element)
अणु
	काष्ठा _sas_device *sas_device;
	काष्ठा scsi_target *starget = शून्य;
	काष्ठा MPT3SAS_TARGET *sas_target_priv_data;
	अचिन्हित दीर्घ flags;
	u16 handle = le16_to_cpu(element->PhysDiskDevHandle);
	u16 volume_handle = 0;
	u64 volume_wwid = 0;

	mpt3sas_config_get_volume_handle(ioc, handle, &volume_handle);
	अगर (volume_handle)
		mpt3sas_config_get_volume_wwid(ioc, volume_handle,
		    &volume_wwid);

	spin_lock_irqsave(&ioc->sas_device_lock, flags);
	sas_device = __mpt3sas_get_sdev_by_handle(ioc, handle);
	अगर (sas_device) अणु
		set_bit(handle, ioc->pd_handles);
		अगर (sas_device->starget && sas_device->starget->hostdata) अणु
			starget = sas_device->starget;
			sas_target_priv_data = starget->hostdata;
			sas_target_priv_data->flags |=
			    MPT_TARGET_FLAGS_RAID_COMPONENT;
			sas_device->volume_handle = volume_handle;
			sas_device->volume_wwid = volume_wwid;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&ioc->sas_device_lock, flags);
	अगर (!sas_device)
		वापस;

	/* hiding raid component */
	_scsih_ir_fastpath(ioc, handle, element->PhysDiskNum);

	अगर (starget)
		starget_क्रम_each_device(starget, (व्योम *)1, _scsih_reprobe_lun);

	sas_device_put(sas_device);
पूर्ण

/**
 * _scsih_sas_pd_delete - delete pd component
 * @ioc: per adapter object
 * @element: IR config element data
 * Context: user.
 */
अटल व्योम
_scsih_sas_pd_delete(काष्ठा MPT3SAS_ADAPTER *ioc,
	Mpi2EventIrConfigElement_t *element)
अणु
	u16 handle = le16_to_cpu(element->PhysDiskDevHandle);

	_scsih_device_हटाओ_by_handle(ioc, handle);
पूर्ण

/**
 * _scsih_sas_pd_add - हटाओ pd component
 * @ioc: per adapter object
 * @element: IR config element data
 * Context: user.
 */
अटल व्योम
_scsih_sas_pd_add(काष्ठा MPT3SAS_ADAPTER *ioc,
	Mpi2EventIrConfigElement_t *element)
अणु
	काष्ठा _sas_device *sas_device;
	u16 handle = le16_to_cpu(element->PhysDiskDevHandle);
	Mpi2ConfigReply_t mpi_reply;
	Mpi2SasDevicePage0_t sas_device_pg0;
	u32 ioc_status;
	u64 sas_address;
	u16 parent_handle;

	set_bit(handle, ioc->pd_handles);

	sas_device = mpt3sas_get_sdev_by_handle(ioc, handle);
	अगर (sas_device) अणु
		_scsih_ir_fastpath(ioc, handle, element->PhysDiskNum);
		sas_device_put(sas_device);
		वापस;
	पूर्ण

	अगर ((mpt3sas_config_get_sas_device_pg0(ioc, &mpi_reply, &sas_device_pg0,
	    MPI2_SAS_DEVICE_PGAD_FORM_HANDLE, handle))) अणु
		ioc_err(ioc, "failure at %s:%d/%s()!\n",
			__खाता__, __LINE__, __func__);
		वापस;
	पूर्ण

	ioc_status = le16_to_cpu(mpi_reply.IOCStatus) &
	    MPI2_IOCSTATUS_MASK;
	अगर (ioc_status != MPI2_IOCSTATUS_SUCCESS) अणु
		ioc_err(ioc, "failure at %s:%d/%s()!\n",
			__खाता__, __LINE__, __func__);
		वापस;
	पूर्ण

	parent_handle = le16_to_cpu(sas_device_pg0.ParentDevHandle);
	अगर (!_scsih_get_sas_address(ioc, parent_handle, &sas_address))
		mpt3sas_transport_update_links(ioc, sas_address, handle,
		    sas_device_pg0.PhyNum, MPI2_SAS_NEG_LINK_RATE_1_5,
		    mpt3sas_get_port_by_id(ioc,
		    sas_device_pg0.PhysicalPort, 0));

	_scsih_ir_fastpath(ioc, handle, element->PhysDiskNum);
	_scsih_add_device(ioc, handle, 0, 1);
पूर्ण

/**
 * _scsih_sas_ir_config_change_event_debug - debug क्रम IR Config Change events
 * @ioc: per adapter object
 * @event_data: event data payload
 * Context: user.
 */
अटल व्योम
_scsih_sas_ir_config_change_event_debug(काष्ठा MPT3SAS_ADAPTER *ioc,
	Mpi2EventDataIrConfigChangeList_t *event_data)
अणु
	Mpi2EventIrConfigElement_t *element;
	u8 element_type;
	पूर्णांक i;
	अक्षर *reason_str = शून्य, *element_str = शून्य;

	element = (Mpi2EventIrConfigElement_t *)&event_data->ConfigElement[0];

	ioc_info(ioc, "raid config change: (%s), elements(%d)\n",
		 le32_to_cpu(event_data->Flags) & MPI2_EVENT_IR_CHANGE_FLAGS_FOREIGN_CONFIG ?
		 "foreign" : "native",
		 event_data->NumElements);
	क्रम (i = 0; i < event_data->NumElements; i++, element++) अणु
		चयन (element->ReasonCode) अणु
		हाल MPI2_EVENT_IR_CHANGE_RC_ADDED:
			reason_str = "add";
			अवरोध;
		हाल MPI2_EVENT_IR_CHANGE_RC_REMOVED:
			reason_str = "remove";
			अवरोध;
		हाल MPI2_EVENT_IR_CHANGE_RC_NO_CHANGE:
			reason_str = "no change";
			अवरोध;
		हाल MPI2_EVENT_IR_CHANGE_RC_HIDE:
			reason_str = "hide";
			अवरोध;
		हाल MPI2_EVENT_IR_CHANGE_RC_UNHIDE:
			reason_str = "unhide";
			अवरोध;
		हाल MPI2_EVENT_IR_CHANGE_RC_VOLUME_CREATED:
			reason_str = "volume_created";
			अवरोध;
		हाल MPI2_EVENT_IR_CHANGE_RC_VOLUME_DELETED:
			reason_str = "volume_deleted";
			अवरोध;
		हाल MPI2_EVENT_IR_CHANGE_RC_PD_CREATED:
			reason_str = "pd_created";
			अवरोध;
		हाल MPI2_EVENT_IR_CHANGE_RC_PD_DELETED:
			reason_str = "pd_deleted";
			अवरोध;
		शेष:
			reason_str = "unknown reason";
			अवरोध;
		पूर्ण
		element_type = le16_to_cpu(element->ElementFlags) &
		    MPI2_EVENT_IR_CHANGE_EFLAGS_ELEMENT_TYPE_MASK;
		चयन (element_type) अणु
		हाल MPI2_EVENT_IR_CHANGE_EFLAGS_VOLUME_ELEMENT:
			element_str = "volume";
			अवरोध;
		हाल MPI2_EVENT_IR_CHANGE_EFLAGS_VOLPHYSDISK_ELEMENT:
			element_str = "phys disk";
			अवरोध;
		हाल MPI2_EVENT_IR_CHANGE_EFLAGS_HOTSPARE_ELEMENT:
			element_str = "hot spare";
			अवरोध;
		शेष:
			element_str = "unknown element";
			अवरोध;
		पूर्ण
		pr_info("\t(%s:%s), vol handle(0x%04x), " \
		    "pd handle(0x%04x), pd num(0x%02x)\n", element_str,
		    reason_str, le16_to_cpu(element->VolDevHandle),
		    le16_to_cpu(element->PhysDiskDevHandle),
		    element->PhysDiskNum);
	पूर्ण
पूर्ण

/**
 * _scsih_sas_ir_config_change_event - handle ir configuration change events
 * @ioc: per adapter object
 * @fw_event: The fw_event_work object
 * Context: user.
 */
अटल व्योम
_scsih_sas_ir_config_change_event(काष्ठा MPT3SAS_ADAPTER *ioc,
	काष्ठा fw_event_work *fw_event)
अणु
	Mpi2EventIrConfigElement_t *element;
	पूर्णांक i;
	u8 क्रमeign_config;
	Mpi2EventDataIrConfigChangeList_t *event_data =
		(Mpi2EventDataIrConfigChangeList_t *)
		fw_event->event_data;

	अगर ((ioc->logging_level & MPT_DEBUG_EVENT_WORK_TASK) &&
	     (!ioc->hide_ir_msg))
		_scsih_sas_ir_config_change_event_debug(ioc, event_data);

	क्रमeign_config = (le32_to_cpu(event_data->Flags) &
	    MPI2_EVENT_IR_CHANGE_FLAGS_FOREIGN_CONFIG) ? 1 : 0;

	element = (Mpi2EventIrConfigElement_t *)&event_data->ConfigElement[0];
	अगर (ioc->shost_recovery &&
	    ioc->hba_mpi_version_beदीर्घed != MPI2_VERSION) अणु
		क्रम (i = 0; i < event_data->NumElements; i++, element++) अणु
			अगर (element->ReasonCode == MPI2_EVENT_IR_CHANGE_RC_HIDE)
				_scsih_ir_fastpath(ioc,
					le16_to_cpu(element->PhysDiskDevHandle),
					element->PhysDiskNum);
		पूर्ण
		वापस;
	पूर्ण

	क्रम (i = 0; i < event_data->NumElements; i++, element++) अणु

		चयन (element->ReasonCode) अणु
		हाल MPI2_EVENT_IR_CHANGE_RC_VOLUME_CREATED:
		हाल MPI2_EVENT_IR_CHANGE_RC_ADDED:
			अगर (!क्रमeign_config)
				_scsih_sas_volume_add(ioc, element);
			अवरोध;
		हाल MPI2_EVENT_IR_CHANGE_RC_VOLUME_DELETED:
		हाल MPI2_EVENT_IR_CHANGE_RC_REMOVED:
			अगर (!क्रमeign_config)
				_scsih_sas_volume_delete(ioc,
				    le16_to_cpu(element->VolDevHandle));
			अवरोध;
		हाल MPI2_EVENT_IR_CHANGE_RC_PD_CREATED:
			अगर (!ioc->is_warpdrive)
				_scsih_sas_pd_hide(ioc, element);
			अवरोध;
		हाल MPI2_EVENT_IR_CHANGE_RC_PD_DELETED:
			अगर (!ioc->is_warpdrive)
				_scsih_sas_pd_expose(ioc, element);
			अवरोध;
		हाल MPI2_EVENT_IR_CHANGE_RC_HIDE:
			अगर (!ioc->is_warpdrive)
				_scsih_sas_pd_add(ioc, element);
			अवरोध;
		हाल MPI2_EVENT_IR_CHANGE_RC_UNHIDE:
			अगर (!ioc->is_warpdrive)
				_scsih_sas_pd_delete(ioc, element);
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

/**
 * _scsih_sas_ir_volume_event - IR volume event
 * @ioc: per adapter object
 * @fw_event: The fw_event_work object
 * Context: user.
 */
अटल व्योम
_scsih_sas_ir_volume_event(काष्ठा MPT3SAS_ADAPTER *ioc,
	काष्ठा fw_event_work *fw_event)
अणु
	u64 wwid;
	अचिन्हित दीर्घ flags;
	काष्ठा _raid_device *raid_device;
	u16 handle;
	u32 state;
	पूर्णांक rc;
	Mpi2EventDataIrVolume_t *event_data =
		(Mpi2EventDataIrVolume_t *) fw_event->event_data;

	अगर (ioc->shost_recovery)
		वापस;

	अगर (event_data->ReasonCode != MPI2_EVENT_IR_VOLUME_RC_STATE_CHANGED)
		वापस;

	handle = le16_to_cpu(event_data->VolDevHandle);
	state = le32_to_cpu(event_data->NewValue);
	अगर (!ioc->hide_ir_msg)
		dewtprपूर्णांकk(ioc,
			   ioc_info(ioc, "%s: handle(0x%04x), old(0x%08x), new(0x%08x)\n",
				    __func__, handle,
				    le32_to_cpu(event_data->PreviousValue),
				    state));
	चयन (state) अणु
	हाल MPI2_RAID_VOL_STATE_MISSING:
	हाल MPI2_RAID_VOL_STATE_FAILED:
		_scsih_sas_volume_delete(ioc, handle);
		अवरोध;

	हाल MPI2_RAID_VOL_STATE_ONLINE:
	हाल MPI2_RAID_VOL_STATE_DEGRADED:
	हाल MPI2_RAID_VOL_STATE_OPTIMAL:

		spin_lock_irqsave(&ioc->raid_device_lock, flags);
		raid_device = mpt3sas_raid_device_find_by_handle(ioc, handle);
		spin_unlock_irqrestore(&ioc->raid_device_lock, flags);

		अगर (raid_device)
			अवरोध;

		mpt3sas_config_get_volume_wwid(ioc, handle, &wwid);
		अगर (!wwid) अणु
			ioc_err(ioc, "failure at %s:%d/%s()!\n",
				__खाता__, __LINE__, __func__);
			अवरोध;
		पूर्ण

		raid_device = kzalloc(माप(काष्ठा _raid_device), GFP_KERNEL);
		अगर (!raid_device) अणु
			ioc_err(ioc, "failure at %s:%d/%s()!\n",
				__खाता__, __LINE__, __func__);
			अवरोध;
		पूर्ण

		raid_device->id = ioc->sas_id++;
		raid_device->channel = RAID_CHANNEL;
		raid_device->handle = handle;
		raid_device->wwid = wwid;
		_scsih_raid_device_add(ioc, raid_device);
		rc = scsi_add_device(ioc->shost, RAID_CHANNEL,
		    raid_device->id, 0);
		अगर (rc)
			_scsih_raid_device_हटाओ(ioc, raid_device);
		अवरोध;

	हाल MPI2_RAID_VOL_STATE_INITIALIZING:
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

/**
 * _scsih_sas_ir_physical_disk_event - PD event
 * @ioc: per adapter object
 * @fw_event: The fw_event_work object
 * Context: user.
 */
अटल व्योम
_scsih_sas_ir_physical_disk_event(काष्ठा MPT3SAS_ADAPTER *ioc,
	काष्ठा fw_event_work *fw_event)
अणु
	u16 handle, parent_handle;
	u32 state;
	काष्ठा _sas_device *sas_device;
	Mpi2ConfigReply_t mpi_reply;
	Mpi2SasDevicePage0_t sas_device_pg0;
	u32 ioc_status;
	Mpi2EventDataIrPhysicalDisk_t *event_data =
		(Mpi2EventDataIrPhysicalDisk_t *) fw_event->event_data;
	u64 sas_address;

	अगर (ioc->shost_recovery)
		वापस;

	अगर (event_data->ReasonCode != MPI2_EVENT_IR_PHYSDISK_RC_STATE_CHANGED)
		वापस;

	handle = le16_to_cpu(event_data->PhysDiskDevHandle);
	state = le32_to_cpu(event_data->NewValue);

	अगर (!ioc->hide_ir_msg)
		dewtprपूर्णांकk(ioc,
			   ioc_info(ioc, "%s: handle(0x%04x), old(0x%08x), new(0x%08x)\n",
				    __func__, handle,
				    le32_to_cpu(event_data->PreviousValue),
				    state));

	चयन (state) अणु
	हाल MPI2_RAID_PD_STATE_ONLINE:
	हाल MPI2_RAID_PD_STATE_DEGRADED:
	हाल MPI2_RAID_PD_STATE_REBUILDING:
	हाल MPI2_RAID_PD_STATE_OPTIMAL:
	हाल MPI2_RAID_PD_STATE_HOT_SPARE:

		अगर (!ioc->is_warpdrive)
			set_bit(handle, ioc->pd_handles);

		sas_device = mpt3sas_get_sdev_by_handle(ioc, handle);
		अगर (sas_device) अणु
			sas_device_put(sas_device);
			वापस;
		पूर्ण

		अगर ((mpt3sas_config_get_sas_device_pg0(ioc, &mpi_reply,
		    &sas_device_pg0, MPI2_SAS_DEVICE_PGAD_FORM_HANDLE,
		    handle))) अणु
			ioc_err(ioc, "failure at %s:%d/%s()!\n",
				__खाता__, __LINE__, __func__);
			वापस;
		पूर्ण

		ioc_status = le16_to_cpu(mpi_reply.IOCStatus) &
		    MPI2_IOCSTATUS_MASK;
		अगर (ioc_status != MPI2_IOCSTATUS_SUCCESS) अणु
			ioc_err(ioc, "failure at %s:%d/%s()!\n",
				__खाता__, __LINE__, __func__);
			वापस;
		पूर्ण

		parent_handle = le16_to_cpu(sas_device_pg0.ParentDevHandle);
		अगर (!_scsih_get_sas_address(ioc, parent_handle, &sas_address))
			mpt3sas_transport_update_links(ioc, sas_address, handle,
			    sas_device_pg0.PhyNum, MPI2_SAS_NEG_LINK_RATE_1_5,
			    mpt3sas_get_port_by_id(ioc,
			    sas_device_pg0.PhysicalPort, 0));

		_scsih_add_device(ioc, handle, 0, 1);

		अवरोध;

	हाल MPI2_RAID_PD_STATE_OFFLINE:
	हाल MPI2_RAID_PD_STATE_NOT_CONFIGURED:
	हाल MPI2_RAID_PD_STATE_NOT_COMPATIBLE:
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

/**
 * _scsih_sas_ir_operation_status_event_debug - debug क्रम IR op event
 * @ioc: per adapter object
 * @event_data: event data payload
 * Context: user.
 */
अटल व्योम
_scsih_sas_ir_operation_status_event_debug(काष्ठा MPT3SAS_ADAPTER *ioc,
	Mpi2EventDataIrOperationStatus_t *event_data)
अणु
	अक्षर *reason_str = शून्य;

	चयन (event_data->RAIDOperation) अणु
	हाल MPI2_EVENT_IR_RAIDOP_RESYNC:
		reason_str = "resync";
		अवरोध;
	हाल MPI2_EVENT_IR_RAIDOP_ONLINE_CAP_EXPANSION:
		reason_str = "online capacity expansion";
		अवरोध;
	हाल MPI2_EVENT_IR_RAIDOP_CONSISTENCY_CHECK:
		reason_str = "consistency check";
		अवरोध;
	हाल MPI2_EVENT_IR_RAIDOP_BACKGROUND_INIT:
		reason_str = "background init";
		अवरोध;
	हाल MPI2_EVENT_IR_RAIDOP_MAKE_DATA_CONSISTENT:
		reason_str = "make data consistent";
		अवरोध;
	पूर्ण

	अगर (!reason_str)
		वापस;

	ioc_info(ioc, "raid operational status: (%s)\thandle(0x%04x), percent complete(%d)\n",
		 reason_str,
		 le16_to_cpu(event_data->VolDevHandle),
		 event_data->PercentComplete);
पूर्ण

/**
 * _scsih_sas_ir_operation_status_event - handle RAID operation events
 * @ioc: per adapter object
 * @fw_event: The fw_event_work object
 * Context: user.
 */
अटल व्योम
_scsih_sas_ir_operation_status_event(काष्ठा MPT3SAS_ADAPTER *ioc,
	काष्ठा fw_event_work *fw_event)
अणु
	Mpi2EventDataIrOperationStatus_t *event_data =
		(Mpi2EventDataIrOperationStatus_t *)
		fw_event->event_data;
	अटल काष्ठा _raid_device *raid_device;
	अचिन्हित दीर्घ flags;
	u16 handle;

	अगर ((ioc->logging_level & MPT_DEBUG_EVENT_WORK_TASK) &&
	    (!ioc->hide_ir_msg))
		_scsih_sas_ir_operation_status_event_debug(ioc,
		     event_data);

	/* code added क्रम raid transport support */
	अगर (event_data->RAIDOperation == MPI2_EVENT_IR_RAIDOP_RESYNC) अणु

		spin_lock_irqsave(&ioc->raid_device_lock, flags);
		handle = le16_to_cpu(event_data->VolDevHandle);
		raid_device = mpt3sas_raid_device_find_by_handle(ioc, handle);
		अगर (raid_device)
			raid_device->percent_complete =
			    event_data->PercentComplete;
		spin_unlock_irqrestore(&ioc->raid_device_lock, flags);
	पूर्ण
पूर्ण

/**
 * _scsih_prep_device_scan - initialize parameters prior to device scan
 * @ioc: per adapter object
 *
 * Set the deleted flag prior to device scan.  If the device is found during
 * the scan, then we clear the deleted flag.
 */
अटल व्योम
_scsih_prep_device_scan(काष्ठा MPT3SAS_ADAPTER *ioc)
अणु
	काष्ठा MPT3SAS_DEVICE *sas_device_priv_data;
	काष्ठा scsi_device *sdev;

	shost_क्रम_each_device(sdev, ioc->shost) अणु
		sas_device_priv_data = sdev->hostdata;
		अगर (sas_device_priv_data && sas_device_priv_data->sas_target)
			sas_device_priv_data->sas_target->deleted = 1;
	पूर्ण
पूर्ण

/**
 * _scsih_mark_responding_sas_device - mark a sas_devices as responding
 * @ioc: per adapter object
 * @sas_device_pg0: SAS Device page 0
 *
 * After host reset, find out whether devices are still responding.
 * Used in _scsih_हटाओ_unresponsive_sas_devices.
 */
अटल व्योम
_scsih_mark_responding_sas_device(काष्ठा MPT3SAS_ADAPTER *ioc,
Mpi2SasDevicePage0_t *sas_device_pg0)
अणु
	काष्ठा MPT3SAS_TARGET *sas_target_priv_data = शून्य;
	काष्ठा scsi_target *starget;
	काष्ठा _sas_device *sas_device = शून्य;
	काष्ठा _enclosure_node *enclosure_dev = शून्य;
	अचिन्हित दीर्घ flags;
	काष्ठा hba_port *port = mpt3sas_get_port_by_id(
	    ioc, sas_device_pg0->PhysicalPort, 0);

	अगर (sas_device_pg0->EnclosureHandle) अणु
		enclosure_dev =
			mpt3sas_scsih_enclosure_find_by_handle(ioc,
				le16_to_cpu(sas_device_pg0->EnclosureHandle));
		अगर (enclosure_dev == शून्य)
			ioc_info(ioc, "Enclosure handle(0x%04x) doesn't match with enclosure device!\n",
				 sas_device_pg0->EnclosureHandle);
	पूर्ण
	spin_lock_irqsave(&ioc->sas_device_lock, flags);
	list_क्रम_each_entry(sas_device, &ioc->sas_device_list, list) अणु
		अगर (sas_device->sas_address != le64_to_cpu(
		    sas_device_pg0->SASAddress))
			जारी;
		अगर (sas_device->slot != le16_to_cpu(sas_device_pg0->Slot))
			जारी;
		अगर (sas_device->port != port)
			जारी;
		sas_device->responding = 1;
		starget = sas_device->starget;
		अगर (starget && starget->hostdata) अणु
			sas_target_priv_data = starget->hostdata;
			sas_target_priv_data->पंचांग_busy = 0;
			sas_target_priv_data->deleted = 0;
		पूर्ण अन्यथा
			sas_target_priv_data = शून्य;
		अगर (starget) अणु
			starget_prपूर्णांकk(KERN_INFO, starget,
			    "handle(0x%04x), sas_addr(0x%016llx)\n",
			    le16_to_cpu(sas_device_pg0->DevHandle),
			    (अचिन्हित दीर्घ दीर्घ)
			    sas_device->sas_address);

			अगर (sas_device->enclosure_handle != 0)
				starget_prपूर्णांकk(KERN_INFO, starget,
				 "enclosure logical id(0x%016llx), slot(%d)\n",
				 (अचिन्हित दीर्घ दीर्घ)
				 sas_device->enclosure_logical_id,
				 sas_device->slot);
		पूर्ण
		अगर (le16_to_cpu(sas_device_pg0->Flags) &
		      MPI2_SAS_DEVICE0_FLAGS_ENCL_LEVEL_VALID) अणु
			sas_device->enclosure_level =
			   sas_device_pg0->EnclosureLevel;
			स_नकल(&sas_device->connector_name[0],
				&sas_device_pg0->ConnectorName[0], 4);
		पूर्ण अन्यथा अणु
			sas_device->enclosure_level = 0;
			sas_device->connector_name[0] = '\0';
		पूर्ण

		sas_device->enclosure_handle =
			le16_to_cpu(sas_device_pg0->EnclosureHandle);
		sas_device->is_chassis_slot_valid = 0;
		अगर (enclosure_dev) अणु
			sas_device->enclosure_logical_id = le64_to_cpu(
				enclosure_dev->pg0.EnclosureLogicalID);
			अगर (le16_to_cpu(enclosure_dev->pg0.Flags) &
			    MPI2_SAS_ENCLS0_FLAGS_CHASSIS_SLOT_VALID) अणु
				sas_device->is_chassis_slot_valid = 1;
				sas_device->chassis_slot =
					enclosure_dev->pg0.ChassisSlot;
			पूर्ण
		पूर्ण

		अगर (sas_device->handle == le16_to_cpu(
		    sas_device_pg0->DevHandle))
			जाओ out;
		pr_info("\thandle changed from(0x%04x)!!!\n",
		    sas_device->handle);
		sas_device->handle = le16_to_cpu(
		    sas_device_pg0->DevHandle);
		अगर (sas_target_priv_data)
			sas_target_priv_data->handle =
			    le16_to_cpu(sas_device_pg0->DevHandle);
		जाओ out;
	पूर्ण
 out:
	spin_unlock_irqrestore(&ioc->sas_device_lock, flags);
पूर्ण

/**
 * _scsih_create_enclosure_list_after_reset - Free Existing list,
 *	And create enclosure list by scanning all Enclosure Page(0)s
 * @ioc: per adapter object
 */
अटल व्योम
_scsih_create_enclosure_list_after_reset(काष्ठा MPT3SAS_ADAPTER *ioc)
अणु
	काष्ठा _enclosure_node *enclosure_dev;
	Mpi2ConfigReply_t mpi_reply;
	u16 enclosure_handle;
	पूर्णांक rc;

	/* Free existing enclosure list */
	mpt3sas_मुक्त_enclosure_list(ioc);

	/* Re स्थिरructing enclosure list after reset*/
	enclosure_handle = 0xFFFF;
	करो अणु
		enclosure_dev =
			kzalloc(माप(काष्ठा _enclosure_node), GFP_KERNEL);
		अगर (!enclosure_dev) अणु
			ioc_err(ioc, "failure at %s:%d/%s()!\n",
				__खाता__, __LINE__, __func__);
			वापस;
		पूर्ण
		rc = mpt3sas_config_get_enclosure_pg0(ioc, &mpi_reply,
				&enclosure_dev->pg0,
				MPI2_SAS_ENCLOS_PGAD_FORM_GET_NEXT_HANDLE,
				enclosure_handle);

		अगर (rc || (le16_to_cpu(mpi_reply.IOCStatus) &
						MPI2_IOCSTATUS_MASK)) अणु
			kमुक्त(enclosure_dev);
			वापस;
		पूर्ण
		list_add_tail(&enclosure_dev->list,
						&ioc->enclosure_list);
		enclosure_handle =
			le16_to_cpu(enclosure_dev->pg0.EnclosureHandle);
	पूर्ण जबतक (1);
पूर्ण

/**
 * _scsih_search_responding_sas_devices -
 * @ioc: per adapter object
 *
 * After host reset, find out whether devices are still responding.
 * If not हटाओ.
 */
अटल व्योम
_scsih_search_responding_sas_devices(काष्ठा MPT3SAS_ADAPTER *ioc)
अणु
	Mpi2SasDevicePage0_t sas_device_pg0;
	Mpi2ConfigReply_t mpi_reply;
	u16 ioc_status;
	u16 handle;
	u32 device_info;

	ioc_info(ioc, "search for end-devices: start\n");

	अगर (list_empty(&ioc->sas_device_list))
		जाओ out;

	handle = 0xFFFF;
	जबतक (!(mpt3sas_config_get_sas_device_pg0(ioc, &mpi_reply,
	    &sas_device_pg0, MPI2_SAS_DEVICE_PGAD_FORM_GET_NEXT_HANDLE,
	    handle))) अणु
		ioc_status = le16_to_cpu(mpi_reply.IOCStatus) &
		    MPI2_IOCSTATUS_MASK;
		अगर (ioc_status != MPI2_IOCSTATUS_SUCCESS)
			अवरोध;
		handle = le16_to_cpu(sas_device_pg0.DevHandle);
		device_info = le32_to_cpu(sas_device_pg0.DeviceInfo);
		अगर (!(_scsih_is_end_device(device_info)))
			जारी;
		_scsih_mark_responding_sas_device(ioc, &sas_device_pg0);
	पूर्ण

 out:
	ioc_info(ioc, "search for end-devices: complete\n");
पूर्ण

/**
 * _scsih_mark_responding_pcie_device - mark a pcie_device as responding
 * @ioc: per adapter object
 * @pcie_device_pg0: PCIe Device page 0
 *
 * After host reset, find out whether devices are still responding.
 * Used in _scsih_हटाओ_unresponding_devices.
 */
अटल व्योम
_scsih_mark_responding_pcie_device(काष्ठा MPT3SAS_ADAPTER *ioc,
	Mpi26PCIeDevicePage0_t *pcie_device_pg0)
अणु
	काष्ठा MPT3SAS_TARGET *sas_target_priv_data = शून्य;
	काष्ठा scsi_target *starget;
	काष्ठा _pcie_device *pcie_device;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ioc->pcie_device_lock, flags);
	list_क्रम_each_entry(pcie_device, &ioc->pcie_device_list, list) अणु
		अगर ((pcie_device->wwid == le64_to_cpu(pcie_device_pg0->WWID))
		    && (pcie_device->slot == le16_to_cpu(
		    pcie_device_pg0->Slot))) अणु
			pcie_device->access_status =
					pcie_device_pg0->AccessStatus;
			pcie_device->responding = 1;
			starget = pcie_device->starget;
			अगर (starget && starget->hostdata) अणु
				sas_target_priv_data = starget->hostdata;
				sas_target_priv_data->पंचांग_busy = 0;
				sas_target_priv_data->deleted = 0;
			पूर्ण अन्यथा
				sas_target_priv_data = शून्य;
			अगर (starget) अणु
				starget_prपूर्णांकk(KERN_INFO, starget,
				    "handle(0x%04x), wwid(0x%016llx) ",
				    pcie_device->handle,
				    (अचिन्हित दीर्घ दीर्घ)pcie_device->wwid);
				अगर (pcie_device->enclosure_handle != 0)
					starget_prपूर्णांकk(KERN_INFO, starget,
					    "enclosure logical id(0x%016llx), "
					    "slot(%d)\n",
					    (अचिन्हित दीर्घ दीर्घ)
					    pcie_device->enclosure_logical_id,
					    pcie_device->slot);
			पूर्ण

			अगर (((le32_to_cpu(pcie_device_pg0->Flags)) &
			    MPI26_PCIEDEV0_FLAGS_ENCL_LEVEL_VALID) &&
			    (ioc->hba_mpi_version_beदीर्घed != MPI2_VERSION)) अणु
				pcie_device->enclosure_level =
				    pcie_device_pg0->EnclosureLevel;
				स_नकल(&pcie_device->connector_name[0],
				    &pcie_device_pg0->ConnectorName[0], 4);
			पूर्ण अन्यथा अणु
				pcie_device->enclosure_level = 0;
				pcie_device->connector_name[0] = '\0';
			पूर्ण

			अगर (pcie_device->handle == le16_to_cpu(
			    pcie_device_pg0->DevHandle))
				जाओ out;
			pr_info("\thandle changed from(0x%04x)!!!\n",
			    pcie_device->handle);
			pcie_device->handle = le16_to_cpu(
			    pcie_device_pg0->DevHandle);
			अगर (sas_target_priv_data)
				sas_target_priv_data->handle =
				    le16_to_cpu(pcie_device_pg0->DevHandle);
			जाओ out;
		पूर्ण
	पूर्ण

 out:
	spin_unlock_irqrestore(&ioc->pcie_device_lock, flags);
पूर्ण

/**
 * _scsih_search_responding_pcie_devices -
 * @ioc: per adapter object
 *
 * After host reset, find out whether devices are still responding.
 * If not हटाओ.
 */
अटल व्योम
_scsih_search_responding_pcie_devices(काष्ठा MPT3SAS_ADAPTER *ioc)
अणु
	Mpi26PCIeDevicePage0_t pcie_device_pg0;
	Mpi2ConfigReply_t mpi_reply;
	u16 ioc_status;
	u16 handle;
	u32 device_info;

	ioc_info(ioc, "search for end-devices: start\n");

	अगर (list_empty(&ioc->pcie_device_list))
		जाओ out;

	handle = 0xFFFF;
	जबतक (!(mpt3sas_config_get_pcie_device_pg0(ioc, &mpi_reply,
		&pcie_device_pg0, MPI26_PCIE_DEVICE_PGAD_FORM_GET_NEXT_HANDLE,
		handle))) अणु
		ioc_status = le16_to_cpu(mpi_reply.IOCStatus) &
		    MPI2_IOCSTATUS_MASK;
		अगर (ioc_status != MPI2_IOCSTATUS_SUCCESS) अणु
			ioc_info(ioc, "\tbreak from %s: ioc_status(0x%04x), loginfo(0x%08x)\n",
				 __func__, ioc_status,
				 le32_to_cpu(mpi_reply.IOCLogInfo));
			अवरोध;
		पूर्ण
		handle = le16_to_cpu(pcie_device_pg0.DevHandle);
		device_info = le32_to_cpu(pcie_device_pg0.DeviceInfo);
		अगर (!(_scsih_is_nvme_pciescsi_device(device_info)))
			जारी;
		_scsih_mark_responding_pcie_device(ioc, &pcie_device_pg0);
	पूर्ण
out:
	ioc_info(ioc, "search for PCIe end-devices: complete\n");
पूर्ण

/**
 * _scsih_mark_responding_raid_device - mark a raid_device as responding
 * @ioc: per adapter object
 * @wwid: world wide identअगरier क्रम raid volume
 * @handle: device handle
 *
 * After host reset, find out whether devices are still responding.
 * Used in _scsih_हटाओ_unresponsive_raid_devices.
 */
अटल व्योम
_scsih_mark_responding_raid_device(काष्ठा MPT3SAS_ADAPTER *ioc, u64 wwid,
	u16 handle)
अणु
	काष्ठा MPT3SAS_TARGET *sas_target_priv_data = शून्य;
	काष्ठा scsi_target *starget;
	काष्ठा _raid_device *raid_device;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ioc->raid_device_lock, flags);
	list_क्रम_each_entry(raid_device, &ioc->raid_device_list, list) अणु
		अगर (raid_device->wwid == wwid && raid_device->starget) अणु
			starget = raid_device->starget;
			अगर (starget && starget->hostdata) अणु
				sas_target_priv_data = starget->hostdata;
				sas_target_priv_data->deleted = 0;
			पूर्ण अन्यथा
				sas_target_priv_data = शून्य;
			raid_device->responding = 1;
			spin_unlock_irqrestore(&ioc->raid_device_lock, flags);
			starget_prपूर्णांकk(KERN_INFO, raid_device->starget,
			    "handle(0x%04x), wwid(0x%016llx)\n", handle,
			    (अचिन्हित दीर्घ दीर्घ)raid_device->wwid);

			/*
			 * WARPDRIVE: The handles of the PDs might have changed
			 * across the host reset so re-initialize the
			 * required data क्रम Direct IO
			 */
			mpt3sas_init_warpdrive_properties(ioc, raid_device);
			spin_lock_irqsave(&ioc->raid_device_lock, flags);
			अगर (raid_device->handle == handle) अणु
				spin_unlock_irqrestore(&ioc->raid_device_lock,
				    flags);
				वापस;
			पूर्ण
			pr_info("\thandle changed from(0x%04x)!!!\n",
			    raid_device->handle);
			raid_device->handle = handle;
			अगर (sas_target_priv_data)
				sas_target_priv_data->handle = handle;
			spin_unlock_irqrestore(&ioc->raid_device_lock, flags);
			वापस;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&ioc->raid_device_lock, flags);
पूर्ण

/**
 * _scsih_search_responding_raid_devices -
 * @ioc: per adapter object
 *
 * After host reset, find out whether devices are still responding.
 * If not हटाओ.
 */
अटल व्योम
_scsih_search_responding_raid_devices(काष्ठा MPT3SAS_ADAPTER *ioc)
अणु
	Mpi2RaidVolPage1_t volume_pg1;
	Mpi2RaidVolPage0_t volume_pg0;
	Mpi2RaidPhysDiskPage0_t pd_pg0;
	Mpi2ConfigReply_t mpi_reply;
	u16 ioc_status;
	u16 handle;
	u8 phys_disk_num;

	अगर (!ioc->ir_firmware)
		वापस;

	ioc_info(ioc, "search for raid volumes: start\n");

	अगर (list_empty(&ioc->raid_device_list))
		जाओ out;

	handle = 0xFFFF;
	जबतक (!(mpt3sas_config_get_raid_volume_pg1(ioc, &mpi_reply,
	    &volume_pg1, MPI2_RAID_VOLUME_PGAD_FORM_GET_NEXT_HANDLE, handle))) अणु
		ioc_status = le16_to_cpu(mpi_reply.IOCStatus) &
		    MPI2_IOCSTATUS_MASK;
		अगर (ioc_status != MPI2_IOCSTATUS_SUCCESS)
			अवरोध;
		handle = le16_to_cpu(volume_pg1.DevHandle);

		अगर (mpt3sas_config_get_raid_volume_pg0(ioc, &mpi_reply,
		    &volume_pg0, MPI2_RAID_VOLUME_PGAD_FORM_HANDLE, handle,
		     माप(Mpi2RaidVolPage0_t)))
			जारी;

		अगर (volume_pg0.VolumeState == MPI2_RAID_VOL_STATE_OPTIMAL ||
		    volume_pg0.VolumeState == MPI2_RAID_VOL_STATE_ONLINE ||
		    volume_pg0.VolumeState == MPI2_RAID_VOL_STATE_DEGRADED)
			_scsih_mark_responding_raid_device(ioc,
			    le64_to_cpu(volume_pg1.WWID), handle);
	पूर्ण

	/* refresh the pd_handles */
	अगर (!ioc->is_warpdrive) अणु
		phys_disk_num = 0xFF;
		स_रखो(ioc->pd_handles, 0, ioc->pd_handles_sz);
		जबतक (!(mpt3sas_config_get_phys_disk_pg0(ioc, &mpi_reply,
		    &pd_pg0, MPI2_PHYSDISK_PGAD_FORM_GET_NEXT_PHYSDISKNUM,
		    phys_disk_num))) अणु
			ioc_status = le16_to_cpu(mpi_reply.IOCStatus) &
			    MPI2_IOCSTATUS_MASK;
			अगर (ioc_status != MPI2_IOCSTATUS_SUCCESS)
				अवरोध;
			phys_disk_num = pd_pg0.PhysDiskNum;
			handle = le16_to_cpu(pd_pg0.DevHandle);
			set_bit(handle, ioc->pd_handles);
		पूर्ण
	पूर्ण
 out:
	ioc_info(ioc, "search for responding raid volumes: complete\n");
पूर्ण

/**
 * _scsih_mark_responding_expander - mark a expander as responding
 * @ioc: per adapter object
 * @expander_pg0:SAS Expander Config Page0
 *
 * After host reset, find out whether devices are still responding.
 * Used in _scsih_हटाओ_unresponsive_expanders.
 */
अटल व्योम
_scsih_mark_responding_expander(काष्ठा MPT3SAS_ADAPTER *ioc,
	Mpi2ExpanderPage0_t *expander_pg0)
अणु
	काष्ठा _sas_node *sas_expander = शून्य;
	अचिन्हित दीर्घ flags;
	पूर्णांक i;
	काष्ठा _enclosure_node *enclosure_dev = शून्य;
	u16 handle = le16_to_cpu(expander_pg0->DevHandle);
	u16 enclosure_handle = le16_to_cpu(expander_pg0->EnclosureHandle);
	u64 sas_address = le64_to_cpu(expander_pg0->SASAddress);
	काष्ठा hba_port *port = mpt3sas_get_port_by_id(
	    ioc, expander_pg0->PhysicalPort, 0);

	अगर (enclosure_handle)
		enclosure_dev =
			mpt3sas_scsih_enclosure_find_by_handle(ioc,
							enclosure_handle);

	spin_lock_irqsave(&ioc->sas_node_lock, flags);
	list_क्रम_each_entry(sas_expander, &ioc->sas_expander_list, list) अणु
		अगर (sas_expander->sas_address != sas_address)
			जारी;
		अगर (sas_expander->port != port)
			जारी;
		sas_expander->responding = 1;

		अगर (enclosure_dev) अणु
			sas_expander->enclosure_logical_id =
			    le64_to_cpu(enclosure_dev->pg0.EnclosureLogicalID);
			sas_expander->enclosure_handle =
			    le16_to_cpu(expander_pg0->EnclosureHandle);
		पूर्ण

		अगर (sas_expander->handle == handle)
			जाओ out;
		pr_info("\texpander(0x%016llx): handle changed" \
		    " from(0x%04x) to (0x%04x)!!!\n",
		    (अचिन्हित दीर्घ दीर्घ)sas_expander->sas_address,
		    sas_expander->handle, handle);
		sas_expander->handle = handle;
		क्रम (i = 0 ; i < sas_expander->num_phys ; i++)
			sas_expander->phy[i].handle = handle;
		जाओ out;
	पूर्ण
 out:
	spin_unlock_irqrestore(&ioc->sas_node_lock, flags);
पूर्ण

/**
 * _scsih_search_responding_expanders -
 * @ioc: per adapter object
 *
 * After host reset, find out whether devices are still responding.
 * If not हटाओ.
 */
अटल व्योम
_scsih_search_responding_expanders(काष्ठा MPT3SAS_ADAPTER *ioc)
अणु
	Mpi2ExpanderPage0_t expander_pg0;
	Mpi2ConfigReply_t mpi_reply;
	u16 ioc_status;
	u64 sas_address;
	u16 handle;
	u8 port;

	ioc_info(ioc, "search for expanders: start\n");

	अगर (list_empty(&ioc->sas_expander_list))
		जाओ out;

	handle = 0xFFFF;
	जबतक (!(mpt3sas_config_get_expander_pg0(ioc, &mpi_reply, &expander_pg0,
	    MPI2_SAS_EXPAND_PGAD_FORM_GET_NEXT_HNDL, handle))) अणु

		ioc_status = le16_to_cpu(mpi_reply.IOCStatus) &
		    MPI2_IOCSTATUS_MASK;
		अगर (ioc_status != MPI2_IOCSTATUS_SUCCESS)
			अवरोध;

		handle = le16_to_cpu(expander_pg0.DevHandle);
		sas_address = le64_to_cpu(expander_pg0.SASAddress);
		port = expander_pg0.PhysicalPort;
		pr_info(
		    "\texpander present: handle(0x%04x), sas_addr(0x%016llx), port:%d\n",
		    handle, (अचिन्हित दीर्घ दीर्घ)sas_address,
		    (ioc->multipath_on_hba ?
		    port : MULTIPATH_DISABLED_PORT_ID));
		_scsih_mark_responding_expander(ioc, &expander_pg0);
	पूर्ण

 out:
	ioc_info(ioc, "search for expanders: complete\n");
पूर्ण

/**
 * _scsih_हटाओ_unresponding_devices - removing unresponding devices
 * @ioc: per adapter object
 */
अटल व्योम
_scsih_हटाओ_unresponding_devices(काष्ठा MPT3SAS_ADAPTER *ioc)
अणु
	काष्ठा _sas_device *sas_device, *sas_device_next;
	काष्ठा _sas_node *sas_expander, *sas_expander_next;
	काष्ठा _raid_device *raid_device, *raid_device_next;
	काष्ठा _pcie_device *pcie_device, *pcie_device_next;
	काष्ठा list_head पंचांगp_list;
	अचिन्हित दीर्घ flags;
	LIST_HEAD(head);

	ioc_info(ioc, "removing unresponding devices: start\n");

	/* removing unresponding end devices */
	ioc_info(ioc, "removing unresponding devices: end-devices\n");
	/*
	 * Iterate, pulling off devices marked as non-responding. We become the
	 * owner क्रम the reference the list had on any object we prune.
	 */
	spin_lock_irqsave(&ioc->sas_device_lock, flags);
	list_क्रम_each_entry_safe(sas_device, sas_device_next,
	    &ioc->sas_device_list, list) अणु
		अगर (!sas_device->responding)
			list_move_tail(&sas_device->list, &head);
		अन्यथा
			sas_device->responding = 0;
	पूर्ण
	spin_unlock_irqrestore(&ioc->sas_device_lock, flags);

	/*
	 * Now, uninitialize and हटाओ the unresponding devices we pruned.
	 */
	list_क्रम_each_entry_safe(sas_device, sas_device_next, &head, list) अणु
		_scsih_हटाओ_device(ioc, sas_device);
		list_del_init(&sas_device->list);
		sas_device_put(sas_device);
	पूर्ण

	ioc_info(ioc, "Removing unresponding devices: pcie end-devices\n");
	INIT_LIST_HEAD(&head);
	spin_lock_irqsave(&ioc->pcie_device_lock, flags);
	list_क्रम_each_entry_safe(pcie_device, pcie_device_next,
	    &ioc->pcie_device_list, list) अणु
		अगर (!pcie_device->responding)
			list_move_tail(&pcie_device->list, &head);
		अन्यथा
			pcie_device->responding = 0;
	पूर्ण
	spin_unlock_irqrestore(&ioc->pcie_device_lock, flags);

	list_क्रम_each_entry_safe(pcie_device, pcie_device_next, &head, list) अणु
		_scsih_pcie_device_हटाओ_from_sml(ioc, pcie_device);
		list_del_init(&pcie_device->list);
		pcie_device_put(pcie_device);
	पूर्ण

	/* removing unresponding volumes */
	अगर (ioc->ir_firmware) अणु
		ioc_info(ioc, "removing unresponding devices: volumes\n");
		list_क्रम_each_entry_safe(raid_device, raid_device_next,
		    &ioc->raid_device_list, list) अणु
			अगर (!raid_device->responding)
				_scsih_sas_volume_delete(ioc,
				    raid_device->handle);
			अन्यथा
				raid_device->responding = 0;
		पूर्ण
	पूर्ण

	/* removing unresponding expanders */
	ioc_info(ioc, "removing unresponding devices: expanders\n");
	spin_lock_irqsave(&ioc->sas_node_lock, flags);
	INIT_LIST_HEAD(&पंचांगp_list);
	list_क्रम_each_entry_safe(sas_expander, sas_expander_next,
	    &ioc->sas_expander_list, list) अणु
		अगर (!sas_expander->responding)
			list_move_tail(&sas_expander->list, &पंचांगp_list);
		अन्यथा
			sas_expander->responding = 0;
	पूर्ण
	spin_unlock_irqrestore(&ioc->sas_node_lock, flags);
	list_क्रम_each_entry_safe(sas_expander, sas_expander_next, &पंचांगp_list,
	    list) अणु
		_scsih_expander_node_हटाओ(ioc, sas_expander);
	पूर्ण

	ioc_info(ioc, "removing unresponding devices: complete\n");

	/* unblock devices */
	_scsih_ublock_io_all_device(ioc);
पूर्ण

अटल व्योम
_scsih_refresh_expander_links(काष्ठा MPT3SAS_ADAPTER *ioc,
	काष्ठा _sas_node *sas_expander, u16 handle)
अणु
	Mpi2ExpanderPage1_t expander_pg1;
	Mpi2ConfigReply_t mpi_reply;
	पूर्णांक i;

	क्रम (i = 0 ; i < sas_expander->num_phys ; i++) अणु
		अगर ((mpt3sas_config_get_expander_pg1(ioc, &mpi_reply,
		    &expander_pg1, i, handle))) अणु
			ioc_err(ioc, "failure at %s:%d/%s()!\n",
				__खाता__, __LINE__, __func__);
			वापस;
		पूर्ण

		mpt3sas_transport_update_links(ioc, sas_expander->sas_address,
		    le16_to_cpu(expander_pg1.AttachedDevHandle), i,
		    expander_pg1.NegotiatedLinkRate >> 4,
		    sas_expander->port);
	पूर्ण
पूर्ण

/**
 * _scsih_scan_क्रम_devices_after_reset - scan क्रम devices after host reset
 * @ioc: per adapter object
 */
अटल व्योम
_scsih_scan_क्रम_devices_after_reset(काष्ठा MPT3SAS_ADAPTER *ioc)
अणु
	Mpi2ExpanderPage0_t expander_pg0;
	Mpi2SasDevicePage0_t sas_device_pg0;
	Mpi26PCIeDevicePage0_t pcie_device_pg0;
	Mpi2RaidVolPage1_t *volume_pg1;
	Mpi2RaidVolPage0_t *volume_pg0;
	Mpi2RaidPhysDiskPage0_t pd_pg0;
	Mpi2EventIrConfigElement_t element;
	Mpi2ConfigReply_t mpi_reply;
	u8 phys_disk_num, port_id;
	u16 ioc_status;
	u16 handle, parent_handle;
	u64 sas_address;
	काष्ठा _sas_device *sas_device;
	काष्ठा _pcie_device *pcie_device;
	काष्ठा _sas_node *expander_device;
	अटल काष्ठा _raid_device *raid_device;
	u8 retry_count;
	अचिन्हित दीर्घ flags;

	volume_pg0 = kzalloc(माप(*volume_pg0), GFP_KERNEL);
	अगर (!volume_pg0)
		वापस;

	volume_pg1 = kzalloc(माप(*volume_pg1), GFP_KERNEL);
	अगर (!volume_pg1) अणु
		kमुक्त(volume_pg0);
		वापस;
	पूर्ण

	ioc_info(ioc, "scan devices: start\n");

	_scsih_sas_host_refresh(ioc);

	ioc_info(ioc, "\tscan devices: expanders start\n");

	/* expanders */
	handle = 0xFFFF;
	जबतक (!(mpt3sas_config_get_expander_pg0(ioc, &mpi_reply, &expander_pg0,
	    MPI2_SAS_EXPAND_PGAD_FORM_GET_NEXT_HNDL, handle))) अणु
		ioc_status = le16_to_cpu(mpi_reply.IOCStatus) &
		    MPI2_IOCSTATUS_MASK;
		अगर (ioc_status != MPI2_IOCSTATUS_SUCCESS) अणु
			ioc_info(ioc, "\tbreak from expander scan: ioc_status(0x%04x), loginfo(0x%08x)\n",
				 ioc_status, le32_to_cpu(mpi_reply.IOCLogInfo));
			अवरोध;
		पूर्ण
		handle = le16_to_cpu(expander_pg0.DevHandle);
		spin_lock_irqsave(&ioc->sas_node_lock, flags);
		port_id = expander_pg0.PhysicalPort;
		expander_device = mpt3sas_scsih_expander_find_by_sas_address(
		    ioc, le64_to_cpu(expander_pg0.SASAddress),
		    mpt3sas_get_port_by_id(ioc, port_id, 0));
		spin_unlock_irqrestore(&ioc->sas_node_lock, flags);
		अगर (expander_device)
			_scsih_refresh_expander_links(ioc, expander_device,
			    handle);
		अन्यथा अणु
			ioc_info(ioc, "\tBEFORE adding expander: handle (0x%04x), sas_addr(0x%016llx)\n",
				 handle,
				 (u64)le64_to_cpu(expander_pg0.SASAddress));
			_scsih_expander_add(ioc, handle);
			ioc_info(ioc, "\tAFTER adding expander: handle (0x%04x), sas_addr(0x%016llx)\n",
				 handle,
				 (u64)le64_to_cpu(expander_pg0.SASAddress));
		पूर्ण
	पूर्ण

	ioc_info(ioc, "\tscan devices: expanders complete\n");

	अगर (!ioc->ir_firmware)
		जाओ skip_to_sas;

	ioc_info(ioc, "\tscan devices: phys disk start\n");

	/* phys disk */
	phys_disk_num = 0xFF;
	जबतक (!(mpt3sas_config_get_phys_disk_pg0(ioc, &mpi_reply,
	    &pd_pg0, MPI2_PHYSDISK_PGAD_FORM_GET_NEXT_PHYSDISKNUM,
	    phys_disk_num))) अणु
		ioc_status = le16_to_cpu(mpi_reply.IOCStatus) &
		    MPI2_IOCSTATUS_MASK;
		अगर (ioc_status != MPI2_IOCSTATUS_SUCCESS) अणु
			ioc_info(ioc, "\tbreak from phys disk scan: ioc_status(0x%04x), loginfo(0x%08x)\n",
				 ioc_status, le32_to_cpu(mpi_reply.IOCLogInfo));
			अवरोध;
		पूर्ण
		phys_disk_num = pd_pg0.PhysDiskNum;
		handle = le16_to_cpu(pd_pg0.DevHandle);
		sas_device = mpt3sas_get_sdev_by_handle(ioc, handle);
		अगर (sas_device) अणु
			sas_device_put(sas_device);
			जारी;
		पूर्ण
		अगर (mpt3sas_config_get_sas_device_pg0(ioc, &mpi_reply,
		    &sas_device_pg0, MPI2_SAS_DEVICE_PGAD_FORM_HANDLE,
		    handle) != 0)
			जारी;
		ioc_status = le16_to_cpu(mpi_reply.IOCStatus) &
		    MPI2_IOCSTATUS_MASK;
		अगर (ioc_status != MPI2_IOCSTATUS_SUCCESS) अणु
			ioc_info(ioc, "\tbreak from phys disk scan ioc_status(0x%04x), loginfo(0x%08x)\n",
				 ioc_status, le32_to_cpu(mpi_reply.IOCLogInfo));
			अवरोध;
		पूर्ण
		parent_handle = le16_to_cpu(sas_device_pg0.ParentDevHandle);
		अगर (!_scsih_get_sas_address(ioc, parent_handle,
		    &sas_address)) अणु
			ioc_info(ioc, "\tBEFORE adding phys disk: handle (0x%04x), sas_addr(0x%016llx)\n",
				 handle,
				 (u64)le64_to_cpu(sas_device_pg0.SASAddress));
			port_id = sas_device_pg0.PhysicalPort;
			mpt3sas_transport_update_links(ioc, sas_address,
			    handle, sas_device_pg0.PhyNum,
			    MPI2_SAS_NEG_LINK_RATE_1_5,
			    mpt3sas_get_port_by_id(ioc, port_id, 0));
			set_bit(handle, ioc->pd_handles);
			retry_count = 0;
			/* This will retry adding the end device.
			 * _scsih_add_device() will decide on retries and
			 * वापस "1" when it should be retried
			 */
			जबतक (_scsih_add_device(ioc, handle, retry_count++,
			    1)) अणु
				ssleep(1);
			पूर्ण
			ioc_info(ioc, "\tAFTER adding phys disk: handle (0x%04x), sas_addr(0x%016llx)\n",
				 handle,
				 (u64)le64_to_cpu(sas_device_pg0.SASAddress));
		पूर्ण
	पूर्ण

	ioc_info(ioc, "\tscan devices: phys disk complete\n");

	ioc_info(ioc, "\tscan devices: volumes start\n");

	/* volumes */
	handle = 0xFFFF;
	जबतक (!(mpt3sas_config_get_raid_volume_pg1(ioc, &mpi_reply,
	    volume_pg1, MPI2_RAID_VOLUME_PGAD_FORM_GET_NEXT_HANDLE, handle))) अणु
		ioc_status = le16_to_cpu(mpi_reply.IOCStatus) &
		    MPI2_IOCSTATUS_MASK;
		अगर (ioc_status != MPI2_IOCSTATUS_SUCCESS) अणु
			ioc_info(ioc, "\tbreak from volume scan: ioc_status(0x%04x), loginfo(0x%08x)\n",
				 ioc_status, le32_to_cpu(mpi_reply.IOCLogInfo));
			अवरोध;
		पूर्ण
		handle = le16_to_cpu(volume_pg1->DevHandle);
		spin_lock_irqsave(&ioc->raid_device_lock, flags);
		raid_device = _scsih_raid_device_find_by_wwid(ioc,
		    le64_to_cpu(volume_pg1->WWID));
		spin_unlock_irqrestore(&ioc->raid_device_lock, flags);
		अगर (raid_device)
			जारी;
		अगर (mpt3sas_config_get_raid_volume_pg0(ioc, &mpi_reply,
		    volume_pg0, MPI2_RAID_VOLUME_PGAD_FORM_HANDLE, handle,
		     माप(Mpi2RaidVolPage0_t)))
			जारी;
		ioc_status = le16_to_cpu(mpi_reply.IOCStatus) &
		    MPI2_IOCSTATUS_MASK;
		अगर (ioc_status != MPI2_IOCSTATUS_SUCCESS) अणु
			ioc_info(ioc, "\tbreak from volume scan: ioc_status(0x%04x), loginfo(0x%08x)\n",
				 ioc_status, le32_to_cpu(mpi_reply.IOCLogInfo));
			अवरोध;
		पूर्ण
		अगर (volume_pg0->VolumeState == MPI2_RAID_VOL_STATE_OPTIMAL ||
		    volume_pg0->VolumeState == MPI2_RAID_VOL_STATE_ONLINE ||
		    volume_pg0->VolumeState == MPI2_RAID_VOL_STATE_DEGRADED) अणु
			स_रखो(&element, 0, माप(Mpi2EventIrConfigElement_t));
			element.ReasonCode = MPI2_EVENT_IR_CHANGE_RC_ADDED;
			element.VolDevHandle = volume_pg1->DevHandle;
			ioc_info(ioc, "\tBEFORE adding volume: handle (0x%04x)\n",
				 volume_pg1->DevHandle);
			_scsih_sas_volume_add(ioc, &element);
			ioc_info(ioc, "\tAFTER adding volume: handle (0x%04x)\n",
				 volume_pg1->DevHandle);
		पूर्ण
	पूर्ण

	ioc_info(ioc, "\tscan devices: volumes complete\n");

 skip_to_sas:

	ioc_info(ioc, "\tscan devices: end devices start\n");

	/* sas devices */
	handle = 0xFFFF;
	जबतक (!(mpt3sas_config_get_sas_device_pg0(ioc, &mpi_reply,
	    &sas_device_pg0, MPI2_SAS_DEVICE_PGAD_FORM_GET_NEXT_HANDLE,
	    handle))) अणु
		ioc_status = le16_to_cpu(mpi_reply.IOCStatus) &
		    MPI2_IOCSTATUS_MASK;
		अगर (ioc_status != MPI2_IOCSTATUS_SUCCESS) अणु
			ioc_info(ioc, "\tbreak from end device scan: ioc_status(0x%04x), loginfo(0x%08x)\n",
				 ioc_status, le32_to_cpu(mpi_reply.IOCLogInfo));
			अवरोध;
		पूर्ण
		handle = le16_to_cpu(sas_device_pg0.DevHandle);
		अगर (!(_scsih_is_end_device(
		    le32_to_cpu(sas_device_pg0.DeviceInfo))))
			जारी;
		port_id = sas_device_pg0.PhysicalPort;
		sas_device = mpt3sas_get_sdev_by_addr(ioc,
		    le64_to_cpu(sas_device_pg0.SASAddress),
		    mpt3sas_get_port_by_id(ioc, port_id, 0));
		अगर (sas_device) अणु
			sas_device_put(sas_device);
			जारी;
		पूर्ण
		parent_handle = le16_to_cpu(sas_device_pg0.ParentDevHandle);
		अगर (!_scsih_get_sas_address(ioc, parent_handle, &sas_address)) अणु
			ioc_info(ioc, "\tBEFORE adding end device: handle (0x%04x), sas_addr(0x%016llx)\n",
				 handle,
				 (u64)le64_to_cpu(sas_device_pg0.SASAddress));
			mpt3sas_transport_update_links(ioc, sas_address, handle,
			    sas_device_pg0.PhyNum, MPI2_SAS_NEG_LINK_RATE_1_5,
			    mpt3sas_get_port_by_id(ioc, port_id, 0));
			retry_count = 0;
			/* This will retry adding the end device.
			 * _scsih_add_device() will decide on retries and
			 * वापस "1" when it should be retried
			 */
			जबतक (_scsih_add_device(ioc, handle, retry_count++,
			    0)) अणु
				ssleep(1);
			पूर्ण
			ioc_info(ioc, "\tAFTER adding end device: handle (0x%04x), sas_addr(0x%016llx)\n",
				 handle,
				 (u64)le64_to_cpu(sas_device_pg0.SASAddress));
		पूर्ण
	पूर्ण
	ioc_info(ioc, "\tscan devices: end devices complete\n");
	ioc_info(ioc, "\tscan devices: pcie end devices start\n");

	/* pcie devices */
	handle = 0xFFFF;
	जबतक (!(mpt3sas_config_get_pcie_device_pg0(ioc, &mpi_reply,
		&pcie_device_pg0, MPI26_PCIE_DEVICE_PGAD_FORM_GET_NEXT_HANDLE,
		handle))) अणु
		ioc_status = le16_to_cpu(mpi_reply.IOCStatus)
				& MPI2_IOCSTATUS_MASK;
		अगर (ioc_status != MPI2_IOCSTATUS_SUCCESS) अणु
			ioc_info(ioc, "\tbreak from pcie end device scan: ioc_status(0x%04x), loginfo(0x%08x)\n",
				 ioc_status, le32_to_cpu(mpi_reply.IOCLogInfo));
			अवरोध;
		पूर्ण
		handle = le16_to_cpu(pcie_device_pg0.DevHandle);
		अगर (!(_scsih_is_nvme_pciescsi_device(
			le32_to_cpu(pcie_device_pg0.DeviceInfo))))
			जारी;
		pcie_device = mpt3sas_get_pdev_by_wwid(ioc,
				le64_to_cpu(pcie_device_pg0.WWID));
		अगर (pcie_device) अणु
			pcie_device_put(pcie_device);
			जारी;
		पूर्ण
		retry_count = 0;
		parent_handle = le16_to_cpu(pcie_device_pg0.ParentDevHandle);
		_scsih_pcie_add_device(ioc, handle);

		ioc_info(ioc, "\tAFTER adding pcie end device: handle (0x%04x), wwid(0x%016llx)\n",
			 handle, (u64)le64_to_cpu(pcie_device_pg0.WWID));
	पूर्ण

	kमुक्त(volume_pg0);
	kमुक्त(volume_pg1);

	ioc_info(ioc, "\tpcie devices: pcie end devices complete\n");
	ioc_info(ioc, "scan devices: complete\n");
पूर्ण

/**
 * mpt3sas_scsih_pre_reset_handler - reset callback handler (क्रम scsih)
 * @ioc: per adapter object
 *
 * The handler क्रम करोing any required cleanup or initialization.
 */
व्योम mpt3sas_scsih_pre_reset_handler(काष्ठा MPT3SAS_ADAPTER *ioc)
अणु
	dपंचांगprपूर्णांकk(ioc, ioc_info(ioc, "%s: MPT3_IOC_PRE_RESET\n", __func__));
पूर्ण

/**
 * mpt3sas_scsih_clear_outstanding_scsi_पंचांग_commands - clears outstanding
 *							scsi & पंचांग cmds.
 * @ioc: per adapter object
 *
 * The handler क्रम करोing any required cleanup or initialization.
 */
व्योम
mpt3sas_scsih_clear_outstanding_scsi_पंचांग_commands(काष्ठा MPT3SAS_ADAPTER *ioc)
अणु
	dपंचांगprपूर्णांकk(ioc,
	    ioc_info(ioc, "%s: clear outstanding scsi & tm cmds\n", __func__));
	अगर (ioc->scsih_cmds.status & MPT3_CMD_PENDING) अणु
		ioc->scsih_cmds.status |= MPT3_CMD_RESET;
		mpt3sas_base_मुक्त_smid(ioc, ioc->scsih_cmds.smid);
		complete(&ioc->scsih_cmds.करोne);
	पूर्ण
	अगर (ioc->पंचांग_cmds.status & MPT3_CMD_PENDING) अणु
		ioc->पंचांग_cmds.status |= MPT3_CMD_RESET;
		mpt3sas_base_मुक्त_smid(ioc, ioc->पंचांग_cmds.smid);
		complete(&ioc->पंचांग_cmds.करोne);
	पूर्ण

	स_रखो(ioc->pend_os_device_add, 0, ioc->pend_os_device_add_sz);
	स_रखो(ioc->device_हटाओ_in_progress, 0,
	       ioc->device_हटाओ_in_progress_sz);
	_scsih_fw_event_cleanup_queue(ioc);
	_scsih_flush_running_cmds(ioc);
पूर्ण

/**
 * mpt3sas_scsih_reset_करोne_handler - reset callback handler (क्रम scsih)
 * @ioc: per adapter object
 *
 * The handler क्रम करोing any required cleanup or initialization.
 */
व्योम
mpt3sas_scsih_reset_करोne_handler(काष्ठा MPT3SAS_ADAPTER *ioc)
अणु
	dपंचांगprपूर्णांकk(ioc, ioc_info(ioc, "%s: MPT3_IOC_DONE_RESET\n", __func__));
	अगर ((!ioc->is_driver_loading) && !(disable_discovery > 0 &&
					   !ioc->sas_hba.num_phys)) अणु
		अगर (ioc->multipath_on_hba) अणु
			_scsih_sas_port_refresh(ioc);
			_scsih_update_vphys_after_reset(ioc);
		पूर्ण
		_scsih_prep_device_scan(ioc);
		_scsih_create_enclosure_list_after_reset(ioc);
		_scsih_search_responding_sas_devices(ioc);
		_scsih_search_responding_pcie_devices(ioc);
		_scsih_search_responding_raid_devices(ioc);
		_scsih_search_responding_expanders(ioc);
		_scsih_error_recovery_delete_devices(ioc);
	पूर्ण
पूर्ण

/**
 * _mpt3sas_fw_work - delayed task क्रम processing firmware events
 * @ioc: per adapter object
 * @fw_event: The fw_event_work object
 * Context: user.
 */
अटल व्योम
_mpt3sas_fw_work(काष्ठा MPT3SAS_ADAPTER *ioc, काष्ठा fw_event_work *fw_event)
अणु
	ioc->current_event = fw_event;
	_scsih_fw_event_del_from_list(ioc, fw_event);

	/* the queue is being flushed so ignore this event */
	अगर (ioc->हटाओ_host || ioc->pci_error_recovery) अणु
		fw_event_work_put(fw_event);
		ioc->current_event = शून्य;
		वापस;
	पूर्ण

	चयन (fw_event->event) अणु
	हाल MPT3SAS_PROCESS_TRIGGER_DIAG:
		mpt3sas_process_trigger_data(ioc,
			(काष्ठा SL_WH_TRIGGERS_EVENT_DATA_T *)
			fw_event->event_data);
		अवरोध;
	हाल MPT3SAS_REMOVE_UNRESPONDING_DEVICES:
		जबतक (scsi_host_in_recovery(ioc->shost) ||
					 ioc->shost_recovery) अणु
			/*
			 * If we're unloading or cancelling the work, bail.
			 * Otherwise, this can become an infinite loop.
			 */
			अगर (ioc->हटाओ_host || ioc->fw_events_cleanup)
				जाओ out;
			ssleep(1);
		पूर्ण
		_scsih_हटाओ_unresponding_devices(ioc);
		_scsih_del_dirty_vphy(ioc);
		_scsih_del_dirty_port_entries(ioc);
		_scsih_scan_क्रम_devices_after_reset(ioc);
		_scsih_set_nvme_max_shutकरोwn_latency(ioc);
		अवरोध;
	हाल MPT3SAS_PORT_ENABLE_COMPLETE:
		ioc->start_scan = 0;
		अगर (missing_delay[0] != -1 && missing_delay[1] != -1)
			mpt3sas_base_update_missing_delay(ioc, missing_delay[0],
			    missing_delay[1]);
		dewtprपूर्णांकk(ioc,
			   ioc_info(ioc, "port enable: complete from worker thread\n"));
		अवरोध;
	हाल MPT3SAS_TURN_ON_PFA_LED:
		_scsih_turn_on_pfa_led(ioc, fw_event->device_handle);
		अवरोध;
	हाल MPI2_EVENT_SAS_TOPOLOGY_CHANGE_LIST:
		_scsih_sas_topology_change_event(ioc, fw_event);
		अवरोध;
	हाल MPI2_EVENT_SAS_DEVICE_STATUS_CHANGE:
		अगर (ioc->logging_level & MPT_DEBUG_EVENT_WORK_TASK)
			_scsih_sas_device_status_change_event_debug(ioc,
			    (Mpi2EventDataSasDeviceStatusChange_t *)
			    fw_event->event_data);
		अवरोध;
	हाल MPI2_EVENT_SAS_DISCOVERY:
		_scsih_sas_discovery_event(ioc, fw_event);
		अवरोध;
	हाल MPI2_EVENT_SAS_DEVICE_DISCOVERY_ERROR:
		_scsih_sas_device_discovery_error_event(ioc, fw_event);
		अवरोध;
	हाल MPI2_EVENT_SAS_BROADCAST_PRIMITIVE:
		_scsih_sas_broadcast_primitive_event(ioc, fw_event);
		अवरोध;
	हाल MPI2_EVENT_SAS_ENCL_DEVICE_STATUS_CHANGE:
		_scsih_sas_enclosure_dev_status_change_event(ioc,
		    fw_event);
		अवरोध;
	हाल MPI2_EVENT_IR_CONFIGURATION_CHANGE_LIST:
		_scsih_sas_ir_config_change_event(ioc, fw_event);
		अवरोध;
	हाल MPI2_EVENT_IR_VOLUME:
		_scsih_sas_ir_volume_event(ioc, fw_event);
		अवरोध;
	हाल MPI2_EVENT_IR_PHYSICAL_DISK:
		_scsih_sas_ir_physical_disk_event(ioc, fw_event);
		अवरोध;
	हाल MPI2_EVENT_IR_OPERATION_STATUS:
		_scsih_sas_ir_operation_status_event(ioc, fw_event);
		अवरोध;
	हाल MPI2_EVENT_PCIE_DEVICE_STATUS_CHANGE:
		_scsih_pcie_device_status_change_event(ioc, fw_event);
		अवरोध;
	हाल MPI2_EVENT_PCIE_ENUMERATION:
		_scsih_pcie_क्रमागतeration_event(ioc, fw_event);
		अवरोध;
	हाल MPI2_EVENT_PCIE_TOPOLOGY_CHANGE_LIST:
		_scsih_pcie_topology_change_event(ioc, fw_event);
		ioc->current_event = शून्य;
			वापस;
	अवरोध;
	पूर्ण
out:
	fw_event_work_put(fw_event);
	ioc->current_event = शून्य;
पूर्ण

/**
 * _firmware_event_work
 * @work: The fw_event_work object
 * Context: user.
 *
 * wrappers क्रम the work thपढ़ो handling firmware events
 */

अटल व्योम
_firmware_event_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा fw_event_work *fw_event = container_of(work,
	    काष्ठा fw_event_work, work);

	_mpt3sas_fw_work(fw_event->ioc, fw_event);
पूर्ण

/**
 * mpt3sas_scsih_event_callback - firmware event handler (called at ISR समय)
 * @ioc: per adapter object
 * @msix_index: MSIX table index supplied by the OS
 * @reply: reply message frame(lower 32bit addr)
 * Context: पूर्णांकerrupt.
 *
 * This function merely adds a new work task पूर्णांकo ioc->firmware_event_thपढ़ो.
 * The tasks are worked from _firmware_event_work in user context.
 *
 * Return: 1 meaning mf should be मुक्तd from _base_पूर्णांकerrupt
 *         0 means the mf is मुक्तd from this function.
 */
u8
mpt3sas_scsih_event_callback(काष्ठा MPT3SAS_ADAPTER *ioc, u8 msix_index,
	u32 reply)
अणु
	काष्ठा fw_event_work *fw_event;
	Mpi2EventNotअगरicationReply_t *mpi_reply;
	u16 event;
	u16 sz;
	Mpi26EventDataActiveCableExcept_t *ActiveCableEventData;

	/* events turned off due to host reset */
	अगर (ioc->pci_error_recovery)
		वापस 1;

	mpi_reply = mpt3sas_base_get_reply_virt_addr(ioc, reply);

	अगर (unlikely(!mpi_reply)) अणु
		ioc_err(ioc, "mpi_reply not valid at %s:%d/%s()!\n",
			__खाता__, __LINE__, __func__);
		वापस 1;
	पूर्ण

	event = le16_to_cpu(mpi_reply->Event);

	अगर (event != MPI2_EVENT_LOG_ENTRY_ADDED)
		mpt3sas_trigger_event(ioc, event, 0);

	चयन (event) अणु
	/* handle these */
	हाल MPI2_EVENT_SAS_BROADCAST_PRIMITIVE:
	अणु
		Mpi2EventDataSasBroadcastPrimitive_t *baen_data =
		    (Mpi2EventDataSasBroadcastPrimitive_t *)
		    mpi_reply->EventData;

		अगर (baen_data->Primitive !=
		    MPI2_EVENT_PRIMITIVE_ASYNCHRONOUS_EVENT)
			वापस 1;

		अगर (ioc->broadcast_aen_busy) अणु
			ioc->broadcast_aen_pending++;
			वापस 1;
		पूर्ण अन्यथा
			ioc->broadcast_aen_busy = 1;
		अवरोध;
	पूर्ण

	हाल MPI2_EVENT_SAS_TOPOLOGY_CHANGE_LIST:
		_scsih_check_topo_delete_events(ioc,
		    (Mpi2EventDataSasTopologyChangeList_t *)
		    mpi_reply->EventData);
		अवरोध;
	हाल MPI2_EVENT_PCIE_TOPOLOGY_CHANGE_LIST:
	_scsih_check_pcie_topo_हटाओ_events(ioc,
		    (Mpi26EventDataPCIeTopologyChangeList_t *)
		    mpi_reply->EventData);
		अवरोध;
	हाल MPI2_EVENT_IR_CONFIGURATION_CHANGE_LIST:
		_scsih_check_ir_config_unhide_events(ioc,
		    (Mpi2EventDataIrConfigChangeList_t *)
		    mpi_reply->EventData);
		अवरोध;
	हाल MPI2_EVENT_IR_VOLUME:
		_scsih_check_volume_delete_events(ioc,
		    (Mpi2EventDataIrVolume_t *)
		    mpi_reply->EventData);
		अवरोध;
	हाल MPI2_EVENT_LOG_ENTRY_ADDED:
	अणु
		Mpi2EventDataLogEntryAdded_t *log_entry;
		u32 *log_code;

		अगर (!ioc->is_warpdrive)
			अवरोध;

		log_entry = (Mpi2EventDataLogEntryAdded_t *)
		    mpi_reply->EventData;
		log_code = (u32 *)log_entry->LogData;

		अगर (le16_to_cpu(log_entry->LogEntryQualअगरier)
		    != MPT2_WARPDRIVE_LOGENTRY)
			अवरोध;

		चयन (le32_to_cpu(*log_code)) अणु
		हाल MPT2_WARPDRIVE_LC_SSDT:
			ioc_warn(ioc, "WarpDrive Warning: IO Throttling has occurred in the WarpDrive subsystem. Check WarpDrive documentation for additional details.\n");
			अवरोध;
		हाल MPT2_WARPDRIVE_LC_SSDLW:
			ioc_warn(ioc, "WarpDrive Warning: Program/Erase Cycles for the WarpDrive subsystem in degraded range. Check WarpDrive documentation for additional details.\n");
			अवरोध;
		हाल MPT2_WARPDRIVE_LC_SSDLF:
			ioc_err(ioc, "WarpDrive Fatal Error: There are no Program/Erase Cycles for the WarpDrive subsystem. The storage device will be in read-only mode. Check WarpDrive documentation for additional details.\n");
			अवरोध;
		हाल MPT2_WARPDRIVE_LC_BRMF:
			ioc_err(ioc, "WarpDrive Fatal Error: The Backup Rail Monitor has failed on the WarpDrive subsystem. Check WarpDrive documentation for additional details.\n");
			अवरोध;
		पूर्ण

		अवरोध;
	पूर्ण
	हाल MPI2_EVENT_SAS_DEVICE_STATUS_CHANGE:
		_scsih_sas_device_status_change_event(ioc,
		    (Mpi2EventDataSasDeviceStatusChange_t *)
		    mpi_reply->EventData);
		अवरोध;
	हाल MPI2_EVENT_IR_OPERATION_STATUS:
	हाल MPI2_EVENT_SAS_DISCOVERY:
	हाल MPI2_EVENT_SAS_DEVICE_DISCOVERY_ERROR:
	हाल MPI2_EVENT_SAS_ENCL_DEVICE_STATUS_CHANGE:
	हाल MPI2_EVENT_IR_PHYSICAL_DISK:
	हाल MPI2_EVENT_PCIE_ENUMERATION:
	हाल MPI2_EVENT_PCIE_DEVICE_STATUS_CHANGE:
		अवरोध;

	हाल MPI2_EVENT_TEMP_THRESHOLD:
		_scsih_temp_threshold_events(ioc,
			(Mpi2EventDataTemperature_t *)
			mpi_reply->EventData);
		अवरोध;
	हाल MPI2_EVENT_ACTIVE_CABLE_EXCEPTION:
		ActiveCableEventData =
		    (Mpi26EventDataActiveCableExcept_t *) mpi_reply->EventData;
		चयन (ActiveCableEventData->ReasonCode) अणु
		हाल MPI26_EVENT_ACTIVE_CABLE_INSUFFICIENT_POWER:
			ioc_notice(ioc, "Currently an active cable with ReceptacleID %d\n",
				   ActiveCableEventData->ReceptacleID);
			pr_notice("cannot be powered and devices connected\n");
			pr_notice("to this active cable will not be seen\n");
			pr_notice("This active cable requires %d mW of power\n",
			    le32_to_cpu(
			    ActiveCableEventData->ActiveCablePowerRequirement));
			अवरोध;

		हाल MPI26_EVENT_ACTIVE_CABLE_DEGRADED:
			ioc_notice(ioc, "Currently a cable with ReceptacleID %d\n",
				   ActiveCableEventData->ReceptacleID);
			pr_notice(
			    "is not running at optimal speed(12 Gb/s rate)\n");
			अवरोध;
		पूर्ण

		अवरोध;

	शेष: /* ignore the rest */
		वापस 1;
	पूर्ण

	sz = le16_to_cpu(mpi_reply->EventDataLength) * 4;
	fw_event = alloc_fw_event_work(sz);
	अगर (!fw_event) अणु
		ioc_err(ioc, "failure at %s:%d/%s()!\n",
			__खाता__, __LINE__, __func__);
		वापस 1;
	पूर्ण

	स_नकल(fw_event->event_data, mpi_reply->EventData, sz);
	fw_event->ioc = ioc;
	fw_event->VF_ID = mpi_reply->VF_ID;
	fw_event->VP_ID = mpi_reply->VP_ID;
	fw_event->event = event;
	_scsih_fw_event_add(ioc, fw_event);
	fw_event_work_put(fw_event);
	वापस 1;
पूर्ण

/**
 * _scsih_expander_node_हटाओ - removing expander device from list.
 * @ioc: per adapter object
 * @sas_expander: the sas_device object
 *
 * Removing object and मुक्तing associated memory from the
 * ioc->sas_expander_list.
 */
अटल व्योम
_scsih_expander_node_हटाओ(काष्ठा MPT3SAS_ADAPTER *ioc,
	काष्ठा _sas_node *sas_expander)
अणु
	काष्ठा _sas_port *mpt3sas_port, *next;
	अचिन्हित दीर्घ flags;

	/* हटाओ sibling ports attached to this expander */
	list_क्रम_each_entry_safe(mpt3sas_port, next,
	   &sas_expander->sas_port_list, port_list) अणु
		अगर (ioc->shost_recovery)
			वापस;
		अगर (mpt3sas_port->remote_identअगरy.device_type ==
		    SAS_END_DEVICE)
			mpt3sas_device_हटाओ_by_sas_address(ioc,
			    mpt3sas_port->remote_identअगरy.sas_address,
			    mpt3sas_port->hba_port);
		अन्यथा अगर (mpt3sas_port->remote_identअगरy.device_type ==
		    SAS_EDGE_EXPANDER_DEVICE ||
		    mpt3sas_port->remote_identअगरy.device_type ==
		    SAS_FANOUT_EXPANDER_DEVICE)
			mpt3sas_expander_हटाओ(ioc,
			    mpt3sas_port->remote_identअगरy.sas_address,
			    mpt3sas_port->hba_port);
	पूर्ण

	mpt3sas_transport_port_हटाओ(ioc, sas_expander->sas_address,
	    sas_expander->sas_address_parent, sas_expander->port);

	ioc_info(ioc,
	    "expander_remove: handle(0x%04x), sas_addr(0x%016llx), port:%d\n",
	    sas_expander->handle, (अचिन्हित दीर्घ दीर्घ)
	    sas_expander->sas_address,
	    sas_expander->port->port_id);

	spin_lock_irqsave(&ioc->sas_node_lock, flags);
	list_del(&sas_expander->list);
	spin_unlock_irqrestore(&ioc->sas_node_lock, flags);

	kमुक्त(sas_expander->phy);
	kमुक्त(sas_expander);
पूर्ण

/**
 * _scsih_nvme_shutकरोwn - NVMe shutकरोwn notअगरication
 * @ioc: per adapter object
 *
 * Sending IoUnitControl request with shutकरोwn operation code to alert IOC that
 * the host प्रणाली is shutting करोwn so that IOC can issue NVMe shutकरोwn to
 * NVMe drives attached to it.
 */
अटल व्योम
_scsih_nvme_shutकरोwn(काष्ठा MPT3SAS_ADAPTER *ioc)
अणु
	Mpi26IoUnitControlRequest_t *mpi_request;
	Mpi26IoUnitControlReply_t *mpi_reply;
	u16 smid;

	/* are there any NVMe devices ? */
	अगर (list_empty(&ioc->pcie_device_list))
		वापस;

	mutex_lock(&ioc->scsih_cmds.mutex);

	अगर (ioc->scsih_cmds.status != MPT3_CMD_NOT_USED) अणु
		ioc_err(ioc, "%s: scsih_cmd in use\n", __func__);
		जाओ out;
	पूर्ण

	ioc->scsih_cmds.status = MPT3_CMD_PENDING;

	smid = mpt3sas_base_get_smid(ioc, ioc->scsih_cb_idx);
	अगर (!smid) अणु
		ioc_err(ioc,
		    "%s: failed obtaining a smid\n", __func__);
		ioc->scsih_cmds.status = MPT3_CMD_NOT_USED;
		जाओ out;
	पूर्ण

	mpi_request = mpt3sas_base_get_msg_frame(ioc, smid);
	ioc->scsih_cmds.smid = smid;
	स_रखो(mpi_request, 0, माप(Mpi26IoUnitControlRequest_t));
	mpi_request->Function = MPI2_FUNCTION_IO_UNIT_CONTROL;
	mpi_request->Operation = MPI26_CTRL_OP_SHUTDOWN;

	init_completion(&ioc->scsih_cmds.करोne);
	ioc->put_smid_शेष(ioc, smid);
	/* Wait क्रम max_shutकरोwn_latency seconds */
	ioc_info(ioc,
		"Io Unit Control shutdown (sending), Shutdown latency %d sec\n",
		ioc->max_shutकरोwn_latency);
	रुको_क्रम_completion_समयout(&ioc->scsih_cmds.करोne,
			ioc->max_shutकरोwn_latency*HZ);

	अगर (!(ioc->scsih_cmds.status & MPT3_CMD_COMPLETE)) अणु
		ioc_err(ioc, "%s: timeout\n", __func__);
		जाओ out;
	पूर्ण

	अगर (ioc->scsih_cmds.status & MPT3_CMD_REPLY_VALID) अणु
		mpi_reply = ioc->scsih_cmds.reply;
		ioc_info(ioc, "Io Unit Control shutdown (complete):"
			"ioc_status(0x%04x), loginfo(0x%08x)\n",
			le16_to_cpu(mpi_reply->IOCStatus),
			le32_to_cpu(mpi_reply->IOCLogInfo));
	पूर्ण
 out:
	ioc->scsih_cmds.status = MPT3_CMD_NOT_USED;
	mutex_unlock(&ioc->scsih_cmds.mutex);
पूर्ण


/**
 * _scsih_ir_shutकरोwn - IR shutकरोwn notअगरication
 * @ioc: per adapter object
 *
 * Sending RAID Action to alert the Integrated RAID subप्रणाली of the IOC that
 * the host प्रणाली is shutting करोwn.
 */
अटल व्योम
_scsih_ir_shutकरोwn(काष्ठा MPT3SAS_ADAPTER *ioc)
अणु
	Mpi2RaidActionRequest_t *mpi_request;
	Mpi2RaidActionReply_t *mpi_reply;
	u16 smid;

	/* is IR firmware build loaded ? */
	अगर (!ioc->ir_firmware)
		वापस;

	/* are there any volumes ? */
	अगर (list_empty(&ioc->raid_device_list))
		वापस;

	mutex_lock(&ioc->scsih_cmds.mutex);

	अगर (ioc->scsih_cmds.status != MPT3_CMD_NOT_USED) अणु
		ioc_err(ioc, "%s: scsih_cmd in use\n", __func__);
		जाओ out;
	पूर्ण
	ioc->scsih_cmds.status = MPT3_CMD_PENDING;

	smid = mpt3sas_base_get_smid(ioc, ioc->scsih_cb_idx);
	अगर (!smid) अणु
		ioc_err(ioc, "%s: failed obtaining a smid\n", __func__);
		ioc->scsih_cmds.status = MPT3_CMD_NOT_USED;
		जाओ out;
	पूर्ण

	mpi_request = mpt3sas_base_get_msg_frame(ioc, smid);
	ioc->scsih_cmds.smid = smid;
	स_रखो(mpi_request, 0, माप(Mpi2RaidActionRequest_t));

	mpi_request->Function = MPI2_FUNCTION_RAID_ACTION;
	mpi_request->Action = MPI2_RAID_ACTION_SYSTEM_SHUTDOWN_INITIATED;

	अगर (!ioc->hide_ir_msg)
		ioc_info(ioc, "IR shutdown (sending)\n");
	init_completion(&ioc->scsih_cmds.करोne);
	ioc->put_smid_शेष(ioc, smid);
	रुको_क्रम_completion_समयout(&ioc->scsih_cmds.करोne, 10*HZ);

	अगर (!(ioc->scsih_cmds.status & MPT3_CMD_COMPLETE)) अणु
		ioc_err(ioc, "%s: timeout\n", __func__);
		जाओ out;
	पूर्ण

	अगर (ioc->scsih_cmds.status & MPT3_CMD_REPLY_VALID) अणु
		mpi_reply = ioc->scsih_cmds.reply;
		अगर (!ioc->hide_ir_msg)
			ioc_info(ioc, "IR shutdown (complete): ioc_status(0x%04x), loginfo(0x%08x)\n",
				 le16_to_cpu(mpi_reply->IOCStatus),
				 le32_to_cpu(mpi_reply->IOCLogInfo));
	पूर्ण

 out:
	ioc->scsih_cmds.status = MPT3_CMD_NOT_USED;
	mutex_unlock(&ioc->scsih_cmds.mutex);
पूर्ण

/**
 * _scsih_get_shost_and_ioc - get shost and ioc
 *			and verअगरy whether they are शून्य or not
 * @pdev: PCI device काष्ठा
 * @shost: address of scsi host poपूर्णांकer
 * @ioc: address of HBA adapter poपूर्णांकer
 *
 * Return zero अगर *shost and *ioc are not शून्य otherwise वापस error number.
 */
अटल पूर्णांक
_scsih_get_shost_and_ioc(काष्ठा pci_dev *pdev,
	काष्ठा Scsi_Host **shost, काष्ठा MPT3SAS_ADAPTER **ioc)
अणु
	*shost = pci_get_drvdata(pdev);
	अगर (*shost == शून्य) अणु
		dev_err(&pdev->dev, "pdev's driver data is null\n");
		वापस -ENXIO;
	पूर्ण

	*ioc = shost_priv(*shost);
	अगर (*ioc == शून्य) अणु
		dev_err(&pdev->dev, "shost's private data is null\n");
		वापस -ENXIO;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * scsih_हटाओ - detach and हटाओ add host
 * @pdev: PCI device काष्ठा
 *
 * Routine called when unloading the driver.
 */
अटल व्योम scsih_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा Scsi_Host *shost;
	काष्ठा MPT3SAS_ADAPTER *ioc;
	काष्ठा _sas_port *mpt3sas_port, *next_port;
	काष्ठा _raid_device *raid_device, *next;
	काष्ठा MPT3SAS_TARGET *sas_target_priv_data;
	काष्ठा _pcie_device *pcie_device, *pcienext;
	काष्ठा workqueue_काष्ठा	*wq;
	अचिन्हित दीर्घ flags;
	Mpi2ConfigReply_t mpi_reply;
	काष्ठा hba_port *port, *port_next;

	अगर (_scsih_get_shost_and_ioc(pdev, &shost, &ioc))
		वापस;

	ioc->हटाओ_host = 1;

	अगर (!pci_device_is_present(pdev))
		_scsih_flush_running_cmds(ioc);

	_scsih_fw_event_cleanup_queue(ioc);

	spin_lock_irqsave(&ioc->fw_event_lock, flags);
	wq = ioc->firmware_event_thपढ़ो;
	ioc->firmware_event_thपढ़ो = शून्य;
	spin_unlock_irqrestore(&ioc->fw_event_lock, flags);
	अगर (wq)
		destroy_workqueue(wq);
	/*
	 * Copy back the unmodअगरied ioc page1. so that on next driver load,
	 * current modअगरied changes on ioc page1 won't take effect.
	 */
	अगर (ioc->is_aero_ioc)
		mpt3sas_config_set_ioc_pg1(ioc, &mpi_reply,
				&ioc->ioc_pg1_copy);
	/* release all the volumes */
	_scsih_ir_shutकरोwn(ioc);
	mpt3sas_destroy_debugfs(ioc);
	sas_हटाओ_host(shost);
	list_क्रम_each_entry_safe(raid_device, next, &ioc->raid_device_list,
	    list) अणु
		अगर (raid_device->starget) अणु
			sas_target_priv_data =
			    raid_device->starget->hostdata;
			sas_target_priv_data->deleted = 1;
			scsi_हटाओ_target(&raid_device->starget->dev);
		पूर्ण
		ioc_info(ioc, "removing handle(0x%04x), wwid(0x%016llx)\n",
			 raid_device->handle, (u64)raid_device->wwid);
		_scsih_raid_device_हटाओ(ioc, raid_device);
	पूर्ण
	list_क्रम_each_entry_safe(pcie_device, pcienext, &ioc->pcie_device_list,
		list) अणु
		_scsih_pcie_device_हटाओ_from_sml(ioc, pcie_device);
		list_del_init(&pcie_device->list);
		pcie_device_put(pcie_device);
	पूर्ण

	/* मुक्त ports attached to the sas_host */
	list_क्रम_each_entry_safe(mpt3sas_port, next_port,
	   &ioc->sas_hba.sas_port_list, port_list) अणु
		अगर (mpt3sas_port->remote_identअगरy.device_type ==
		    SAS_END_DEVICE)
			mpt3sas_device_हटाओ_by_sas_address(ioc,
			    mpt3sas_port->remote_identअगरy.sas_address,
			    mpt3sas_port->hba_port);
		अन्यथा अगर (mpt3sas_port->remote_identअगरy.device_type ==
		    SAS_EDGE_EXPANDER_DEVICE ||
		    mpt3sas_port->remote_identअगरy.device_type ==
		    SAS_FANOUT_EXPANDER_DEVICE)
			mpt3sas_expander_हटाओ(ioc,
			    mpt3sas_port->remote_identअगरy.sas_address,
			    mpt3sas_port->hba_port);
	पूर्ण

	list_क्रम_each_entry_safe(port, port_next,
	    &ioc->port_table_list, list) अणु
		list_del(&port->list);
		kमुक्त(port);
	पूर्ण

	/* मुक्त phys attached to the sas_host */
	अगर (ioc->sas_hba.num_phys) अणु
		kमुक्त(ioc->sas_hba.phy);
		ioc->sas_hba.phy = शून्य;
		ioc->sas_hba.num_phys = 0;
	पूर्ण

	mpt3sas_base_detach(ioc);
	spin_lock(&gioc_lock);
	list_del(&ioc->list);
	spin_unlock(&gioc_lock);
	scsi_host_put(shost);
पूर्ण

/**
 * scsih_shutकरोwn - routine call during प्रणाली shutकरोwn
 * @pdev: PCI device काष्ठा
 */
अटल व्योम
scsih_shutकरोwn(काष्ठा pci_dev *pdev)
अणु
	काष्ठा Scsi_Host *shost;
	काष्ठा MPT3SAS_ADAPTER *ioc;
	काष्ठा workqueue_काष्ठा	*wq;
	अचिन्हित दीर्घ flags;
	Mpi2ConfigReply_t mpi_reply;

	अगर (_scsih_get_shost_and_ioc(pdev, &shost, &ioc))
		वापस;

	ioc->हटाओ_host = 1;

	अगर (!pci_device_is_present(pdev))
		_scsih_flush_running_cmds(ioc);

	_scsih_fw_event_cleanup_queue(ioc);

	spin_lock_irqsave(&ioc->fw_event_lock, flags);
	wq = ioc->firmware_event_thपढ़ो;
	ioc->firmware_event_thपढ़ो = शून्य;
	spin_unlock_irqrestore(&ioc->fw_event_lock, flags);
	अगर (wq)
		destroy_workqueue(wq);
	/*
	 * Copy back the unmodअगरied ioc page1 so that on next driver load,
	 * current modअगरied changes on ioc page1 won't take effect.
	 */
	अगर (ioc->is_aero_ioc)
		mpt3sas_config_set_ioc_pg1(ioc, &mpi_reply,
				&ioc->ioc_pg1_copy);

	_scsih_ir_shutकरोwn(ioc);
	_scsih_nvme_shutकरोwn(ioc);
	mpt3sas_base_detach(ioc);
पूर्ण


/**
 * _scsih_probe_boot_devices - reports 1st device
 * @ioc: per adapter object
 *
 * If specअगरied in bios page 2, this routine reports the 1st
 * device scsi-ml or sas transport क्रम persistent boot device
 * purposes.  Please refer to function _scsih_determine_boot_device()
 */
अटल व्योम
_scsih_probe_boot_devices(काष्ठा MPT3SAS_ADAPTER *ioc)
अणु
	u32 channel;
	व्योम *device;
	काष्ठा _sas_device *sas_device;
	काष्ठा _raid_device *raid_device;
	काष्ठा _pcie_device *pcie_device;
	u16 handle;
	u64 sas_address_parent;
	u64 sas_address;
	अचिन्हित दीर्घ flags;
	पूर्णांक rc;
	पूर्णांक tid;
	काष्ठा hba_port *port;

	 /* no Bios, वापस immediately */
	अगर (!ioc->bios_pg3.BiosVersion)
		वापस;

	device = शून्य;
	अगर (ioc->req_boot_device.device) अणु
		device =  ioc->req_boot_device.device;
		channel = ioc->req_boot_device.channel;
	पूर्ण अन्यथा अगर (ioc->req_alt_boot_device.device) अणु
		device =  ioc->req_alt_boot_device.device;
		channel = ioc->req_alt_boot_device.channel;
	पूर्ण अन्यथा अगर (ioc->current_boot_device.device) अणु
		device =  ioc->current_boot_device.device;
		channel = ioc->current_boot_device.channel;
	पूर्ण

	अगर (!device)
		वापस;

	अगर (channel == RAID_CHANNEL) अणु
		raid_device = device;
		rc = scsi_add_device(ioc->shost, RAID_CHANNEL,
		    raid_device->id, 0);
		अगर (rc)
			_scsih_raid_device_हटाओ(ioc, raid_device);
	पूर्ण अन्यथा अगर (channel == PCIE_CHANNEL) अणु
		spin_lock_irqsave(&ioc->pcie_device_lock, flags);
		pcie_device = device;
		tid = pcie_device->id;
		list_move_tail(&pcie_device->list, &ioc->pcie_device_list);
		spin_unlock_irqrestore(&ioc->pcie_device_lock, flags);
		rc = scsi_add_device(ioc->shost, PCIE_CHANNEL, tid, 0);
		अगर (rc)
			_scsih_pcie_device_हटाओ(ioc, pcie_device);
	पूर्ण अन्यथा अणु
		spin_lock_irqsave(&ioc->sas_device_lock, flags);
		sas_device = device;
		handle = sas_device->handle;
		sas_address_parent = sas_device->sas_address_parent;
		sas_address = sas_device->sas_address;
		port = sas_device->port;
		list_move_tail(&sas_device->list, &ioc->sas_device_list);
		spin_unlock_irqrestore(&ioc->sas_device_lock, flags);

		अगर (ioc->hide_drives)
			वापस;

		अगर (!port)
			वापस;

		अगर (!mpt3sas_transport_port_add(ioc, handle,
		    sas_address_parent, port)) अणु
			_scsih_sas_device_हटाओ(ioc, sas_device);
		पूर्ण अन्यथा अगर (!sas_device->starget) अणु
			अगर (!ioc->is_driver_loading) अणु
				mpt3sas_transport_port_हटाओ(ioc,
				    sas_address,
				    sas_address_parent, port);
				_scsih_sas_device_हटाओ(ioc, sas_device);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

/**
 * _scsih_probe_raid - reporting raid volumes to scsi-ml
 * @ioc: per adapter object
 *
 * Called during initial loading of the driver.
 */
अटल व्योम
_scsih_probe_raid(काष्ठा MPT3SAS_ADAPTER *ioc)
अणु
	काष्ठा _raid_device *raid_device, *raid_next;
	पूर्णांक rc;

	list_क्रम_each_entry_safe(raid_device, raid_next,
	    &ioc->raid_device_list, list) अणु
		अगर (raid_device->starget)
			जारी;
		rc = scsi_add_device(ioc->shost, RAID_CHANNEL,
		    raid_device->id, 0);
		अगर (rc)
			_scsih_raid_device_हटाओ(ioc, raid_device);
	पूर्ण
पूर्ण

अटल काष्ठा _sas_device *get_next_sas_device(काष्ठा MPT3SAS_ADAPTER *ioc)
अणु
	काष्ठा _sas_device *sas_device = शून्य;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ioc->sas_device_lock, flags);
	अगर (!list_empty(&ioc->sas_device_init_list)) अणु
		sas_device = list_first_entry(&ioc->sas_device_init_list,
				काष्ठा _sas_device, list);
		sas_device_get(sas_device);
	पूर्ण
	spin_unlock_irqrestore(&ioc->sas_device_lock, flags);

	वापस sas_device;
पूर्ण

अटल व्योम sas_device_make_active(काष्ठा MPT3SAS_ADAPTER *ioc,
		काष्ठा _sas_device *sas_device)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ioc->sas_device_lock, flags);

	/*
	 * Since we dropped the lock during the call to port_add(), we need to
	 * be careful here that somebody अन्यथा didn't move or delete this item
	 * जबतक we were busy with other things.
	 *
	 * If it was on the list, we need a put() क्रम the reference the list
	 * had. Either way, we need a get() क्रम the destination list.
	 */
	अगर (!list_empty(&sas_device->list)) अणु
		list_del_init(&sas_device->list);
		sas_device_put(sas_device);
	पूर्ण

	sas_device_get(sas_device);
	list_add_tail(&sas_device->list, &ioc->sas_device_list);

	spin_unlock_irqrestore(&ioc->sas_device_lock, flags);
पूर्ण

/**
 * _scsih_probe_sas - reporting sas devices to sas transport
 * @ioc: per adapter object
 *
 * Called during initial loading of the driver.
 */
अटल व्योम
_scsih_probe_sas(काष्ठा MPT3SAS_ADAPTER *ioc)
अणु
	काष्ठा _sas_device *sas_device;

	अगर (ioc->hide_drives)
		वापस;

	जबतक ((sas_device = get_next_sas_device(ioc))) अणु
		अगर (!mpt3sas_transport_port_add(ioc, sas_device->handle,
		    sas_device->sas_address_parent, sas_device->port)) अणु
			_scsih_sas_device_हटाओ(ioc, sas_device);
			sas_device_put(sas_device);
			जारी;
		पूर्ण अन्यथा अगर (!sas_device->starget) अणु
			/*
			 * When asyn scanning is enabled, its not possible to
			 * हटाओ devices जबतक scanning is turned on due to an
			 * oops in scsi_sysfs_add_sdev()->add_device()->
			 * sysfs_addrm_start()
			 */
			अगर (!ioc->is_driver_loading) अणु
				mpt3sas_transport_port_हटाओ(ioc,
				    sas_device->sas_address,
				    sas_device->sas_address_parent,
				    sas_device->port);
				_scsih_sas_device_हटाओ(ioc, sas_device);
				sas_device_put(sas_device);
				जारी;
			पूर्ण
		पूर्ण
		sas_device_make_active(ioc, sas_device);
		sas_device_put(sas_device);
	पूर्ण
पूर्ण

/**
 * get_next_pcie_device - Get the next pcie device
 * @ioc: per adapter object
 *
 * Get the next pcie device from pcie_device_init_list list.
 *
 * Return: pcie device काष्ठाure अगर pcie_device_init_list list is not empty
 * otherwise वापसs शून्य
 */
अटल काष्ठा _pcie_device *get_next_pcie_device(काष्ठा MPT3SAS_ADAPTER *ioc)
अणु
	काष्ठा _pcie_device *pcie_device = शून्य;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ioc->pcie_device_lock, flags);
	अगर (!list_empty(&ioc->pcie_device_init_list)) अणु
		pcie_device = list_first_entry(&ioc->pcie_device_init_list,
				काष्ठा _pcie_device, list);
		pcie_device_get(pcie_device);
	पूर्ण
	spin_unlock_irqrestore(&ioc->pcie_device_lock, flags);

	वापस pcie_device;
पूर्ण

/**
 * pcie_device_make_active - Add pcie device to pcie_device_list list
 * @ioc: per adapter object
 * @pcie_device: pcie device object
 *
 * Add the pcie device which has रेजिस्टरed with SCSI Transport Later to
 * pcie_device_list list
 */
अटल व्योम pcie_device_make_active(काष्ठा MPT3SAS_ADAPTER *ioc,
		काष्ठा _pcie_device *pcie_device)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ioc->pcie_device_lock, flags);

	अगर (!list_empty(&pcie_device->list)) अणु
		list_del_init(&pcie_device->list);
		pcie_device_put(pcie_device);
	पूर्ण
	pcie_device_get(pcie_device);
	list_add_tail(&pcie_device->list, &ioc->pcie_device_list);

	spin_unlock_irqrestore(&ioc->pcie_device_lock, flags);
पूर्ण

/**
 * _scsih_probe_pcie - reporting PCIe devices to scsi-ml
 * @ioc: per adapter object
 *
 * Called during initial loading of the driver.
 */
अटल व्योम
_scsih_probe_pcie(काष्ठा MPT3SAS_ADAPTER *ioc)
अणु
	काष्ठा _pcie_device *pcie_device;
	पूर्णांक rc;

	/* PCIe Device List */
	जबतक ((pcie_device = get_next_pcie_device(ioc))) अणु
		अगर (pcie_device->starget) अणु
			pcie_device_put(pcie_device);
			जारी;
		पूर्ण
		अगर (pcie_device->access_status ==
		    MPI26_PCIEDEV0_ASTATUS_DEVICE_BLOCKED) अणु
			pcie_device_make_active(ioc, pcie_device);
			pcie_device_put(pcie_device);
			जारी;
		पूर्ण
		rc = scsi_add_device(ioc->shost, PCIE_CHANNEL,
			pcie_device->id, 0);
		अगर (rc) अणु
			_scsih_pcie_device_हटाओ(ioc, pcie_device);
			pcie_device_put(pcie_device);
			जारी;
		पूर्ण अन्यथा अगर (!pcie_device->starget) अणु
			/*
			 * When async scanning is enabled, its not possible to
			 * हटाओ devices जबतक scanning is turned on due to an
			 * oops in scsi_sysfs_add_sdev()->add_device()->
			 * sysfs_addrm_start()
			 */
			अगर (!ioc->is_driver_loading) अणु
			/* TODO-- Need to find out whether this condition will
			 * occur or not
			 */
				_scsih_pcie_device_हटाओ(ioc, pcie_device);
				pcie_device_put(pcie_device);
				जारी;
			पूर्ण
		पूर्ण
		pcie_device_make_active(ioc, pcie_device);
		pcie_device_put(pcie_device);
	पूर्ण
पूर्ण

/**
 * _scsih_probe_devices - probing क्रम devices
 * @ioc: per adapter object
 *
 * Called during initial loading of the driver.
 */
अटल व्योम
_scsih_probe_devices(काष्ठा MPT3SAS_ADAPTER *ioc)
अणु
	u16 volume_mapping_flags;

	अगर (!(ioc->facts.ProtocolFlags & MPI2_IOCFACTS_PROTOCOL_SCSI_INITIATOR))
		वापस;  /* वापस when IOC करोesn't support initiator mode */

	_scsih_probe_boot_devices(ioc);

	अगर (ioc->ir_firmware) अणु
		volume_mapping_flags =
		    le16_to_cpu(ioc->ioc_pg8.IRVolumeMappingFlags) &
		    MPI2_IOCPAGE8_IRFLAGS_MASK_VOLUME_MAPPING_MODE;
		अगर (volume_mapping_flags ==
		    MPI2_IOCPAGE8_IRFLAGS_LOW_VOLUME_MAPPING) अणु
			_scsih_probe_raid(ioc);
			_scsih_probe_sas(ioc);
		पूर्ण अन्यथा अणु
			_scsih_probe_sas(ioc);
			_scsih_probe_raid(ioc);
		पूर्ण
	पूर्ण अन्यथा अणु
		_scsih_probe_sas(ioc);
		_scsih_probe_pcie(ioc);
	पूर्ण
पूर्ण

/**
 * scsih_scan_start - scsi lld callback क्रम .scan_start
 * @shost: SCSI host poपूर्णांकer
 *
 * The shost has the ability to discover tarमाला_लो on its own instead
 * of scanning the entire bus.  In our implemention, we will kick off
 * firmware discovery.
 */
अटल व्योम
scsih_scan_start(काष्ठा Scsi_Host *shost)
अणु
	काष्ठा MPT3SAS_ADAPTER *ioc = shost_priv(shost);
	पूर्णांक rc;
	अगर (diag_buffer_enable != -1 && diag_buffer_enable != 0)
		mpt3sas_enable_diag_buffer(ioc, diag_buffer_enable);
	अन्यथा अगर (ioc->manu_pg11.HostTraceBufferMaxSizeKB != 0)
		mpt3sas_enable_diag_buffer(ioc, 1);

	अगर (disable_discovery > 0)
		वापस;

	ioc->start_scan = 1;
	rc = mpt3sas_port_enable(ioc);

	अगर (rc != 0)
		ioc_info(ioc, "port enable: FAILED\n");
पूर्ण

/**
 * scsih_scan_finished - scsi lld callback क्रम .scan_finished
 * @shost: SCSI host poपूर्णांकer
 * @समय: elapsed समय of the scan in jअगरfies
 *
 * This function will be called periodicallyn until it वापसs 1 with the
 * scsi_host and the elapsed समय of the scan in jअगरfies. In our implemention,
 * we रुको क्रम firmware discovery to complete, then वापस 1.
 */
अटल पूर्णांक
scsih_scan_finished(काष्ठा Scsi_Host *shost, अचिन्हित दीर्घ समय)
अणु
	काष्ठा MPT3SAS_ADAPTER *ioc = shost_priv(shost);

	अगर (disable_discovery > 0) अणु
		ioc->is_driver_loading = 0;
		ioc->रुको_क्रम_discovery_to_complete = 0;
		वापस 1;
	पूर्ण

	अगर (समय >= (300 * HZ)) अणु
		ioc->port_enable_cmds.status = MPT3_CMD_NOT_USED;
		ioc_info(ioc, "port enable: FAILED with timeout (timeout=300s)\n");
		ioc->is_driver_loading = 0;
		वापस 1;
	पूर्ण

	अगर (ioc->start_scan)
		वापस 0;

	अगर (ioc->start_scan_failed) अणु
		ioc_info(ioc, "port enable: FAILED with (ioc_status=0x%08x)\n",
			 ioc->start_scan_failed);
		ioc->is_driver_loading = 0;
		ioc->रुको_क्रम_discovery_to_complete = 0;
		ioc->हटाओ_host = 1;
		वापस 1;
	पूर्ण

	ioc_info(ioc, "port enable: SUCCESS\n");
	ioc->port_enable_cmds.status = MPT3_CMD_NOT_USED;

	अगर (ioc->रुको_क्रम_discovery_to_complete) अणु
		ioc->रुको_क्रम_discovery_to_complete = 0;
		_scsih_probe_devices(ioc);
	पूर्ण
	mpt3sas_base_start_watchकरोg(ioc);
	ioc->is_driver_loading = 0;
	वापस 1;
पूर्ण

/**
 * scsih_map_queues - map reply queues with request queues
 * @shost: SCSI host poपूर्णांकer
 */
अटल पूर्णांक scsih_map_queues(काष्ठा Scsi_Host *shost)
अणु
	काष्ठा MPT3SAS_ADAPTER *ioc =
	    (काष्ठा MPT3SAS_ADAPTER *)shost->hostdata;

	अगर (ioc->shost->nr_hw_queues == 1)
		वापस 0;

	वापस blk_mq_pci_map_queues(&shost->tag_set.map[HCTX_TYPE_DEFAULT],
	    ioc->pdev, ioc->high_iops_queues);
पूर्ण

/* shost ढाँचा क्रम SAS 2.0 HBA devices */
अटल काष्ठा scsi_host_ढाँचा mpt2sas_driver_ढाँचा = अणु
	.module				= THIS_MODULE,
	.name				= "Fusion MPT SAS Host",
	.proc_name			= MPT2SAS_DRIVER_NAME,
	.queuecommand			= scsih_qcmd,
	.target_alloc			= scsih_target_alloc,
	.slave_alloc			= scsih_slave_alloc,
	.slave_configure		= scsih_slave_configure,
	.target_destroy			= scsih_target_destroy,
	.slave_destroy			= scsih_slave_destroy,
	.scan_finished			= scsih_scan_finished,
	.scan_start			= scsih_scan_start,
	.change_queue_depth		= scsih_change_queue_depth,
	.eh_पात_handler		= scsih_पात,
	.eh_device_reset_handler	= scsih_dev_reset,
	.eh_target_reset_handler	= scsih_target_reset,
	.eh_host_reset_handler		= scsih_host_reset,
	.bios_param			= scsih_bios_param,
	.can_queue			= 1,
	.this_id			= -1,
	.sg_tablesize			= MPT2SAS_SG_DEPTH,
	.max_sectors			= 32767,
	.cmd_per_lun			= 7,
	.shost_attrs			= mpt3sas_host_attrs,
	.sdev_attrs			= mpt3sas_dev_attrs,
	.track_queue_depth		= 1,
	.cmd_size			= माप(काष्ठा scsiio_tracker),
पूर्ण;

/* raid transport support क्रम SAS 2.0 HBA devices */
अटल काष्ठा raid_function_ढाँचा mpt2sas_raid_functions = अणु
	.cookie		= &mpt2sas_driver_ढाँचा,
	.is_raid	= scsih_is_raid,
	.get_resync	= scsih_get_resync,
	.get_state	= scsih_get_state,
पूर्ण;

/* shost ढाँचा क्रम SAS 3.0 HBA devices */
अटल काष्ठा scsi_host_ढाँचा mpt3sas_driver_ढाँचा = अणु
	.module				= THIS_MODULE,
	.name				= "Fusion MPT SAS Host",
	.proc_name			= MPT3SAS_DRIVER_NAME,
	.queuecommand			= scsih_qcmd,
	.target_alloc			= scsih_target_alloc,
	.slave_alloc			= scsih_slave_alloc,
	.slave_configure		= scsih_slave_configure,
	.target_destroy			= scsih_target_destroy,
	.slave_destroy			= scsih_slave_destroy,
	.scan_finished			= scsih_scan_finished,
	.scan_start			= scsih_scan_start,
	.change_queue_depth		= scsih_change_queue_depth,
	.eh_पात_handler		= scsih_पात,
	.eh_device_reset_handler	= scsih_dev_reset,
	.eh_target_reset_handler	= scsih_target_reset,
	.eh_host_reset_handler		= scsih_host_reset,
	.bios_param			= scsih_bios_param,
	.can_queue			= 1,
	.this_id			= -1,
	.sg_tablesize			= MPT3SAS_SG_DEPTH,
	.max_sectors			= 32767,
	.max_segment_size		= 0xffffffff,
	.cmd_per_lun			= 7,
	.shost_attrs			= mpt3sas_host_attrs,
	.sdev_attrs			= mpt3sas_dev_attrs,
	.track_queue_depth		= 1,
	.cmd_size			= माप(काष्ठा scsiio_tracker),
	.map_queues			= scsih_map_queues,
पूर्ण;

/* raid transport support क्रम SAS 3.0 HBA devices */
अटल काष्ठा raid_function_ढाँचा mpt3sas_raid_functions = अणु
	.cookie		= &mpt3sas_driver_ढाँचा,
	.is_raid	= scsih_is_raid,
	.get_resync	= scsih_get_resync,
	.get_state	= scsih_get_state,
पूर्ण;

/**
 * _scsih_determine_hba_mpi_version - determine in which MPI version class
 *					this device beदीर्घs to.
 * @pdev: PCI device काष्ठा
 *
 * वापस MPI2_VERSION क्रम SAS 2.0 HBA devices,
 *	MPI25_VERSION क्रम SAS 3.0 HBA devices, and
 *	MPI26 VERSION क्रम Cutlass & Invader SAS 3.0 HBA devices
 */
अटल u16
_scsih_determine_hba_mpi_version(काष्ठा pci_dev *pdev)
अणु

	चयन (pdev->device) अणु
	हाल MPI2_MFGPAGE_DEVID_SSS6200:
	हाल MPI2_MFGPAGE_DEVID_SAS2004:
	हाल MPI2_MFGPAGE_DEVID_SAS2008:
	हाल MPI2_MFGPAGE_DEVID_SAS2108_1:
	हाल MPI2_MFGPAGE_DEVID_SAS2108_2:
	हाल MPI2_MFGPAGE_DEVID_SAS2108_3:
	हाल MPI2_MFGPAGE_DEVID_SAS2116_1:
	हाल MPI2_MFGPAGE_DEVID_SAS2116_2:
	हाल MPI2_MFGPAGE_DEVID_SAS2208_1:
	हाल MPI2_MFGPAGE_DEVID_SAS2208_2:
	हाल MPI2_MFGPAGE_DEVID_SAS2208_3:
	हाल MPI2_MFGPAGE_DEVID_SAS2208_4:
	हाल MPI2_MFGPAGE_DEVID_SAS2208_5:
	हाल MPI2_MFGPAGE_DEVID_SAS2208_6:
	हाल MPI2_MFGPAGE_DEVID_SAS2308_1:
	हाल MPI2_MFGPAGE_DEVID_SAS2308_2:
	हाल MPI2_MFGPAGE_DEVID_SAS2308_3:
	हाल MPI2_MFGPAGE_DEVID_SWITCH_MPI_EP:
	हाल MPI2_MFGPAGE_DEVID_SWITCH_MPI_EP_1:
		वापस MPI2_VERSION;
	हाल MPI25_MFGPAGE_DEVID_SAS3004:
	हाल MPI25_MFGPAGE_DEVID_SAS3008:
	हाल MPI25_MFGPAGE_DEVID_SAS3108_1:
	हाल MPI25_MFGPAGE_DEVID_SAS3108_2:
	हाल MPI25_MFGPAGE_DEVID_SAS3108_5:
	हाल MPI25_MFGPAGE_DEVID_SAS3108_6:
		वापस MPI25_VERSION;
	हाल MPI26_MFGPAGE_DEVID_SAS3216:
	हाल MPI26_MFGPAGE_DEVID_SAS3224:
	हाल MPI26_MFGPAGE_DEVID_SAS3316_1:
	हाल MPI26_MFGPAGE_DEVID_SAS3316_2:
	हाल MPI26_MFGPAGE_DEVID_SAS3316_3:
	हाल MPI26_MFGPAGE_DEVID_SAS3316_4:
	हाल MPI26_MFGPAGE_DEVID_SAS3324_1:
	हाल MPI26_MFGPAGE_DEVID_SAS3324_2:
	हाल MPI26_MFGPAGE_DEVID_SAS3324_3:
	हाल MPI26_MFGPAGE_DEVID_SAS3324_4:
	हाल MPI26_MFGPAGE_DEVID_SAS3508:
	हाल MPI26_MFGPAGE_DEVID_SAS3508_1:
	हाल MPI26_MFGPAGE_DEVID_SAS3408:
	हाल MPI26_MFGPAGE_DEVID_SAS3516:
	हाल MPI26_MFGPAGE_DEVID_SAS3516_1:
	हाल MPI26_MFGPAGE_DEVID_SAS3416:
	हाल MPI26_MFGPAGE_DEVID_SAS3616:
	हाल MPI26_ATLAS_PCIe_SWITCH_DEVID:
	हाल MPI26_MFGPAGE_DEVID_CFG_SEC_3916:
	हाल MPI26_MFGPAGE_DEVID_HARD_SEC_3916:
	हाल MPI26_MFGPAGE_DEVID_CFG_SEC_3816:
	हाल MPI26_MFGPAGE_DEVID_HARD_SEC_3816:
	हाल MPI26_MFGPAGE_DEVID_INVALID0_3916:
	हाल MPI26_MFGPAGE_DEVID_INVALID1_3916:
	हाल MPI26_MFGPAGE_DEVID_INVALID0_3816:
	हाल MPI26_MFGPAGE_DEVID_INVALID1_3816:
		वापस MPI26_VERSION;
	पूर्ण
	वापस 0;
पूर्ण

/**
 * _scsih_probe - attach and add scsi host
 * @pdev: PCI device काष्ठा
 * @id: pci device id
 *
 * Return: 0 success, anything अन्यथा error.
 */
अटल पूर्णांक
_scsih_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *id)
अणु
	काष्ठा MPT3SAS_ADAPTER *ioc;
	काष्ठा Scsi_Host *shost = शून्य;
	पूर्णांक rv;
	u16 hba_mpi_version;

	/* Determine in which MPI version class this pci device beदीर्घs */
	hba_mpi_version = _scsih_determine_hba_mpi_version(pdev);
	अगर (hba_mpi_version == 0)
		वापस -ENODEV;

	/* Enumerate only SAS 2.0 HBA's अगर hbas_to_क्रमागतerate is one,
	 * क्रम other generation HBA's वापस with -ENODEV
	 */
	अगर ((hbas_to_क्रमागतerate == 1) && (hba_mpi_version !=  MPI2_VERSION))
		वापस -ENODEV;

	/* Enumerate only SAS 3.0 HBA's अगर hbas_to_क्रमागतerate is two,
	 * क्रम other generation HBA's वापस with -ENODEV
	 */
	अगर ((hbas_to_क्रमागतerate == 2) && (!(hba_mpi_version ==  MPI25_VERSION
		|| hba_mpi_version ==  MPI26_VERSION)))
		वापस -ENODEV;

	चयन (hba_mpi_version) अणु
	हाल MPI2_VERSION:
		pci_disable_link_state(pdev, PCIE_LINK_STATE_L0S |
			PCIE_LINK_STATE_L1 | PCIE_LINK_STATE_CLKPM);
		/* Use mpt2sas driver host ढाँचा क्रम SAS 2.0 HBA's */
		shost = scsi_host_alloc(&mpt2sas_driver_ढाँचा,
		  माप(काष्ठा MPT3SAS_ADAPTER));
		अगर (!shost)
			वापस -ENODEV;
		ioc = shost_priv(shost);
		स_रखो(ioc, 0, माप(काष्ठा MPT3SAS_ADAPTER));
		ioc->hba_mpi_version_beदीर्घed = hba_mpi_version;
		ioc->id = mpt2_ids++;
		प्र_लिखो(ioc->driver_name, "%s", MPT2SAS_DRIVER_NAME);
		चयन (pdev->device) अणु
		हाल MPI2_MFGPAGE_DEVID_SSS6200:
			ioc->is_warpdrive = 1;
			ioc->hide_ir_msg = 1;
			अवरोध;
		हाल MPI2_MFGPAGE_DEVID_SWITCH_MPI_EP:
		हाल MPI2_MFGPAGE_DEVID_SWITCH_MPI_EP_1:
			ioc->is_mcpu_endpoपूर्णांक = 1;
			अवरोध;
		शेष:
			ioc->mfg_pg10_hide_flag = MFG_PAGE10_EXPOSE_ALL_DISKS;
			अवरोध;
		पूर्ण

		अगर (multipath_on_hba == -1 || multipath_on_hba == 0)
			ioc->multipath_on_hba = 0;
		अन्यथा
			ioc->multipath_on_hba = 1;

		अवरोध;
	हाल MPI25_VERSION:
	हाल MPI26_VERSION:
		/* Use mpt3sas driver host ढाँचा क्रम SAS 3.0 HBA's */
		shost = scsi_host_alloc(&mpt3sas_driver_ढाँचा,
		  माप(काष्ठा MPT3SAS_ADAPTER));
		अगर (!shost)
			वापस -ENODEV;
		ioc = shost_priv(shost);
		स_रखो(ioc, 0, माप(काष्ठा MPT3SAS_ADAPTER));
		ioc->hba_mpi_version_beदीर्घed = hba_mpi_version;
		ioc->id = mpt3_ids++;
		प्र_लिखो(ioc->driver_name, "%s", MPT3SAS_DRIVER_NAME);
		चयन (pdev->device) अणु
		हाल MPI26_MFGPAGE_DEVID_SAS3508:
		हाल MPI26_MFGPAGE_DEVID_SAS3508_1:
		हाल MPI26_MFGPAGE_DEVID_SAS3408:
		हाल MPI26_MFGPAGE_DEVID_SAS3516:
		हाल MPI26_MFGPAGE_DEVID_SAS3516_1:
		हाल MPI26_MFGPAGE_DEVID_SAS3416:
		हाल MPI26_MFGPAGE_DEVID_SAS3616:
		हाल MPI26_ATLAS_PCIe_SWITCH_DEVID:
			ioc->is_gen35_ioc = 1;
			अवरोध;
		हाल MPI26_MFGPAGE_DEVID_INVALID0_3816:
		हाल MPI26_MFGPAGE_DEVID_INVALID0_3916:
			dev_err(&pdev->dev,
			    "HBA with DeviceId 0x%04x, sub VendorId 0x%04x, sub DeviceId 0x%04x is Invalid",
			    pdev->device, pdev->subप्रणाली_venकरोr,
			    pdev->subप्रणाली_device);
			वापस 1;
		हाल MPI26_MFGPAGE_DEVID_INVALID1_3816:
		हाल MPI26_MFGPAGE_DEVID_INVALID1_3916:
			dev_err(&pdev->dev,
			    "HBA with DeviceId 0x%04x, sub VendorId 0x%04x, sub DeviceId 0x%04x is Tampered",
			    pdev->device, pdev->subप्रणाली_venकरोr,
			    pdev->subप्रणाली_device);
			वापस 1;
		हाल MPI26_MFGPAGE_DEVID_CFG_SEC_3816:
		हाल MPI26_MFGPAGE_DEVID_CFG_SEC_3916:
			dev_info(&pdev->dev,
			    "HBA is in Configurable Secure mode\n");
			fallthrough;
		हाल MPI26_MFGPAGE_DEVID_HARD_SEC_3816:
		हाल MPI26_MFGPAGE_DEVID_HARD_SEC_3916:
			ioc->is_aero_ioc = ioc->is_gen35_ioc = 1;
			अवरोध;
		शेष:
			ioc->is_gen35_ioc = ioc->is_aero_ioc = 0;
		पूर्ण
		अगर ((ioc->hba_mpi_version_beदीर्घed == MPI25_VERSION &&
			pdev->revision >= SAS3_PCI_DEVICE_C0_REVISION) ||
			(ioc->hba_mpi_version_beदीर्घed == MPI26_VERSION)) अणु
			ioc->combined_reply_queue = 1;
			अगर (ioc->is_gen35_ioc)
				ioc->combined_reply_index_count =
				 MPT3_SUP_REPLY_POST_HOST_INDEX_REG_COUNT_G35;
			अन्यथा
				ioc->combined_reply_index_count =
				 MPT3_SUP_REPLY_POST_HOST_INDEX_REG_COUNT_G3;
		पूर्ण

		चयन (ioc->is_gen35_ioc) अणु
		हाल 0:
			अगर (multipath_on_hba == -1 || multipath_on_hba == 0)
				ioc->multipath_on_hba = 0;
			अन्यथा
				ioc->multipath_on_hba = 1;
			अवरोध;
		हाल 1:
			अगर (multipath_on_hba == -1 || multipath_on_hba > 0)
				ioc->multipath_on_hba = 1;
			अन्यथा
				ioc->multipath_on_hba = 0;
		शेष:
			अवरोध;
		पूर्ण

		अवरोध;
	शेष:
		वापस -ENODEV;
	पूर्ण

	INIT_LIST_HEAD(&ioc->list);
	spin_lock(&gioc_lock);
	list_add_tail(&ioc->list, &mpt3sas_ioc_list);
	spin_unlock(&gioc_lock);
	ioc->shost = shost;
	ioc->pdev = pdev;
	ioc->scsi_io_cb_idx = scsi_io_cb_idx;
	ioc->पंचांग_cb_idx = पंचांग_cb_idx;
	ioc->ctl_cb_idx = ctl_cb_idx;
	ioc->base_cb_idx = base_cb_idx;
	ioc->port_enable_cb_idx = port_enable_cb_idx;
	ioc->transport_cb_idx = transport_cb_idx;
	ioc->scsih_cb_idx = scsih_cb_idx;
	ioc->config_cb_idx = config_cb_idx;
	ioc->पंचांग_tr_cb_idx = पंचांग_tr_cb_idx;
	ioc->पंचांग_tr_volume_cb_idx = पंचांग_tr_volume_cb_idx;
	ioc->पंचांग_sas_control_cb_idx = पंचांग_sas_control_cb_idx;
	ioc->logging_level = logging_level;
	ioc->schedule_dead_ioc_flush_running_cmds = &_scsih_flush_running_cmds;
	/* Host रुकोs क्रम minimum of six seconds */
	ioc->max_shutकरोwn_latency = IO_UNIT_CONTROL_SHUTDOWN_TIMEOUT;
	/*
	 * Enable MEMORY MOVE support flag.
	 */
	ioc->drv_support_biपंचांगap |= MPT_DRV_SUPPORT_BITMAP_MEMMOVE;
	/* Enable ADDITIONAL QUERY support flag. */
	ioc->drv_support_biपंचांगap |= MPT_DRV_SUPPORT_BITMAP_ADDNLQUERY;

	ioc->enable_sdev_max_qd = enable_sdev_max_qd;

	/* misc semaphores and spin locks */
	mutex_init(&ioc->reset_in_progress_mutex);
	/* initializing pci_access_mutex lock */
	mutex_init(&ioc->pci_access_mutex);
	spin_lock_init(&ioc->ioc_reset_in_progress_lock);
	spin_lock_init(&ioc->scsi_lookup_lock);
	spin_lock_init(&ioc->sas_device_lock);
	spin_lock_init(&ioc->sas_node_lock);
	spin_lock_init(&ioc->fw_event_lock);
	spin_lock_init(&ioc->raid_device_lock);
	spin_lock_init(&ioc->pcie_device_lock);
	spin_lock_init(&ioc->diag_trigger_lock);

	INIT_LIST_HEAD(&ioc->sas_device_list);
	INIT_LIST_HEAD(&ioc->sas_device_init_list);
	INIT_LIST_HEAD(&ioc->sas_expander_list);
	INIT_LIST_HEAD(&ioc->enclosure_list);
	INIT_LIST_HEAD(&ioc->pcie_device_list);
	INIT_LIST_HEAD(&ioc->pcie_device_init_list);
	INIT_LIST_HEAD(&ioc->fw_event_list);
	INIT_LIST_HEAD(&ioc->raid_device_list);
	INIT_LIST_HEAD(&ioc->sas_hba.sas_port_list);
	INIT_LIST_HEAD(&ioc->delayed_tr_list);
	INIT_LIST_HEAD(&ioc->delayed_sc_list);
	INIT_LIST_HEAD(&ioc->delayed_event_ack_list);
	INIT_LIST_HEAD(&ioc->delayed_tr_volume_list);
	INIT_LIST_HEAD(&ioc->reply_queue_list);
	INIT_LIST_HEAD(&ioc->port_table_list);

	प्र_लिखो(ioc->name, "%s_cm%d", ioc->driver_name, ioc->id);

	/* init shost parameters */
	shost->max_cmd_len = 32;
	shost->max_lun = max_lun;
	shost->transportt = mpt3sas_transport_ढाँचा;
	shost->unique_id = ioc->id;

	अगर (ioc->is_mcpu_endpoपूर्णांक) अणु
		/* mCPU MPI support 64K max IO */
		shost->max_sectors = 128;
		ioc_info(ioc, "The max_sectors value is set to %d\n",
			 shost->max_sectors);
	पूर्ण अन्यथा अणु
		अगर (max_sectors != 0xFFFF) अणु
			अगर (max_sectors < 64) अणु
				shost->max_sectors = 64;
				ioc_warn(ioc, "Invalid value %d passed for max_sectors, range is 64 to 32767. Assigning value of 64.\n",
					 max_sectors);
			पूर्ण अन्यथा अगर (max_sectors > 32767) अणु
				shost->max_sectors = 32767;
				ioc_warn(ioc, "Invalid value %d passed for max_sectors, range is 64 to 32767.Assigning default value of 32767.\n",
					 max_sectors);
			पूर्ण अन्यथा अणु
				shost->max_sectors = max_sectors & 0xFFFE;
				ioc_info(ioc, "The max_sectors value is set to %d\n",
					 shost->max_sectors);
			पूर्ण
		पूर्ण
	पूर्ण
	/* रेजिस्टर EEDP capabilities with SCSI layer */
	अगर (prot_mask >= 0)
		scsi_host_set_prot(shost, (prot_mask & 0x07));
	अन्यथा
		scsi_host_set_prot(shost, SHOST_DIF_TYPE1_PROTECTION
				   | SHOST_DIF_TYPE2_PROTECTION
				   | SHOST_DIF_TYPE3_PROTECTION);

	scsi_host_set_guard(shost, SHOST_DIX_GUARD_CRC);

	/* event thपढ़ो */
	snम_लिखो(ioc->firmware_event_name, माप(ioc->firmware_event_name),
	    "fw_event_%s%d", ioc->driver_name, ioc->id);
	ioc->firmware_event_thपढ़ो = alloc_ordered_workqueue(
	    ioc->firmware_event_name, 0);
	अगर (!ioc->firmware_event_thपढ़ो) अणु
		ioc_err(ioc, "failure at %s:%d/%s()!\n",
			__खाता__, __LINE__, __func__);
		rv = -ENODEV;
		जाओ out_thपढ़ो_fail;
	पूर्ण

	ioc->is_driver_loading = 1;
	अगर ((mpt3sas_base_attach(ioc))) अणु
		ioc_err(ioc, "failure at %s:%d/%s()!\n",
			__खाता__, __LINE__, __func__);
		rv = -ENODEV;
		जाओ out_attach_fail;
	पूर्ण

	अगर (ioc->is_warpdrive) अणु
		अगर (ioc->mfg_pg10_hide_flag ==  MFG_PAGE10_EXPOSE_ALL_DISKS)
			ioc->hide_drives = 0;
		अन्यथा अगर (ioc->mfg_pg10_hide_flag ==  MFG_PAGE10_HIDE_ALL_DISKS)
			ioc->hide_drives = 1;
		अन्यथा अणु
			अगर (mpt3sas_get_num_volumes(ioc))
				ioc->hide_drives = 1;
			अन्यथा
				ioc->hide_drives = 0;
		पूर्ण
	पूर्ण अन्यथा
		ioc->hide_drives = 0;

	shost->host_tagset = 0;
	shost->nr_hw_queues = 1;

	अगर (ioc->is_gen35_ioc && ioc->reply_queue_count > 1 &&
	    host_tagset_enable && ioc->smp_affinity_enable) अणु

		shost->host_tagset = 1;
		shost->nr_hw_queues =
		    ioc->reply_queue_count - ioc->high_iops_queues;

		dev_info(&ioc->pdev->dev,
		    "Max SCSIIO MPT commands: %d shared with nr_hw_queues = %d\n",
		    shost->can_queue, shost->nr_hw_queues);
	पूर्ण

	rv = scsi_add_host(shost, &pdev->dev);
	अगर (rv) अणु
		ioc_err(ioc, "failure at %s:%d/%s()!\n",
			__खाता__, __LINE__, __func__);
		जाओ out_add_shost_fail;
	पूर्ण

	scsi_scan_host(shost);
	mpt3sas_setup_debugfs(ioc);
	वापस 0;
out_add_shost_fail:
	mpt3sas_base_detach(ioc);
 out_attach_fail:
	destroy_workqueue(ioc->firmware_event_thपढ़ो);
 out_thपढ़ो_fail:
	spin_lock(&gioc_lock);
	list_del(&ioc->list);
	spin_unlock(&gioc_lock);
	scsi_host_put(shost);
	वापस rv;
पूर्ण

/**
 * scsih_suspend - घातer management suspend मुख्य entry poपूर्णांक
 * @dev: Device काष्ठा
 *
 * Return: 0 success, anything अन्यथा error.
 */
अटल पूर्णांक __maybe_unused
scsih_suspend(काष्ठा device *dev)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev);
	काष्ठा Scsi_Host *shost;
	काष्ठा MPT3SAS_ADAPTER *ioc;
	पूर्णांक rc;

	rc = _scsih_get_shost_and_ioc(pdev, &shost, &ioc);
	अगर (rc)
		वापस rc;

	mpt3sas_base_stop_watchकरोg(ioc);
	flush_scheduled_work();
	scsi_block_requests(shost);
	_scsih_nvme_shutकरोwn(ioc);
	ioc_info(ioc, "pdev=0x%p, slot=%s, entering operating state\n",
		 pdev, pci_name(pdev));

	mpt3sas_base_मुक्त_resources(ioc);
	वापस 0;
पूर्ण

/**
 * scsih_resume - घातer management resume मुख्य entry poपूर्णांक
 * @dev: Device काष्ठा
 *
 * Return: 0 success, anything अन्यथा error.
 */
अटल पूर्णांक __maybe_unused
scsih_resume(काष्ठा device *dev)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev);
	काष्ठा Scsi_Host *shost;
	काष्ठा MPT3SAS_ADAPTER *ioc;
	pci_घातer_t device_state = pdev->current_state;
	पूर्णांक r;

	r = _scsih_get_shost_and_ioc(pdev, &shost, &ioc);
	अगर (r)
		वापस r;

	ioc_info(ioc, "pdev=0x%p, slot=%s, previous operating state [D%d]\n",
		 pdev, pci_name(pdev), device_state);

	ioc->pdev = pdev;
	r = mpt3sas_base_map_resources(ioc);
	अगर (r)
		वापस r;
	ioc_info(ioc, "Issuing Hard Reset as part of OS Resume\n");
	mpt3sas_base_hard_reset_handler(ioc, SOFT_RESET);
	scsi_unblock_requests(shost);
	mpt3sas_base_start_watchकरोg(ioc);
	वापस 0;
पूर्ण

/**
 * scsih_pci_error_detected - Called when a PCI error is detected.
 * @pdev: PCI device काष्ठा
 * @state: PCI channel state
 *
 * Description: Called when a PCI error is detected.
 *
 * Return: PCI_ERS_RESULT_NEED_RESET or PCI_ERS_RESULT_DISCONNECT.
 */
अटल pci_ers_result_t
scsih_pci_error_detected(काष्ठा pci_dev *pdev, pci_channel_state_t state)
अणु
	काष्ठा Scsi_Host *shost;
	काष्ठा MPT3SAS_ADAPTER *ioc;

	अगर (_scsih_get_shost_and_ioc(pdev, &shost, &ioc))
		वापस PCI_ERS_RESULT_DISCONNECT;

	ioc_info(ioc, "PCI error: detected callback, state(%d)!!\n", state);

	चयन (state) अणु
	हाल pci_channel_io_normal:
		वापस PCI_ERS_RESULT_CAN_RECOVER;
	हाल pci_channel_io_frozen:
		/* Fatal error, prepare क्रम slot reset */
		ioc->pci_error_recovery = 1;
		scsi_block_requests(ioc->shost);
		mpt3sas_base_stop_watchकरोg(ioc);
		mpt3sas_base_मुक्त_resources(ioc);
		वापस PCI_ERS_RESULT_NEED_RESET;
	हाल pci_channel_io_perm_failure:
		/* Permanent error, prepare क्रम device removal */
		ioc->pci_error_recovery = 1;
		mpt3sas_base_stop_watchकरोg(ioc);
		_scsih_flush_running_cmds(ioc);
		वापस PCI_ERS_RESULT_DISCONNECT;
	पूर्ण
	वापस PCI_ERS_RESULT_NEED_RESET;
पूर्ण

/**
 * scsih_pci_slot_reset - Called when PCI slot has been reset.
 * @pdev: PCI device काष्ठा
 *
 * Description: This routine is called by the pci error recovery
 * code after the PCI slot has been reset, just beक्रमe we
 * should resume normal operations.
 */
अटल pci_ers_result_t
scsih_pci_slot_reset(काष्ठा pci_dev *pdev)
अणु
	काष्ठा Scsi_Host *shost;
	काष्ठा MPT3SAS_ADAPTER *ioc;
	पूर्णांक rc;

	अगर (_scsih_get_shost_and_ioc(pdev, &shost, &ioc))
		वापस PCI_ERS_RESULT_DISCONNECT;

	ioc_info(ioc, "PCI error: slot reset callback!!\n");

	ioc->pci_error_recovery = 0;
	ioc->pdev = pdev;
	pci_restore_state(pdev);
	rc = mpt3sas_base_map_resources(ioc);
	अगर (rc)
		वापस PCI_ERS_RESULT_DISCONNECT;

	ioc_info(ioc, "Issuing Hard Reset as part of PCI Slot Reset\n");
	rc = mpt3sas_base_hard_reset_handler(ioc, FORCE_BIG_HAMMER);

	ioc_warn(ioc, "hard reset: %s\n",
		 (rc == 0) ? "success" : "failed");

	अगर (!rc)
		वापस PCI_ERS_RESULT_RECOVERED;
	अन्यथा
		वापस PCI_ERS_RESULT_DISCONNECT;
पूर्ण

/**
 * scsih_pci_resume() - resume normal ops after PCI reset
 * @pdev: poपूर्णांकer to PCI device
 *
 * Called when the error recovery driver tells us that its
 * OK to resume normal operation. Use completion to allow
 * halted scsi ops to resume.
 */
अटल व्योम
scsih_pci_resume(काष्ठा pci_dev *pdev)
अणु
	काष्ठा Scsi_Host *shost;
	काष्ठा MPT3SAS_ADAPTER *ioc;

	अगर (_scsih_get_shost_and_ioc(pdev, &shost, &ioc))
		वापस;

	ioc_info(ioc, "PCI error: resume callback!!\n");

	mpt3sas_base_start_watchकरोg(ioc);
	scsi_unblock_requests(ioc->shost);
पूर्ण

/**
 * scsih_pci_mmio_enabled - Enable MMIO and dump debug रेजिस्टरs
 * @pdev: poपूर्णांकer to PCI device
 */
अटल pci_ers_result_t
scsih_pci_mmio_enabled(काष्ठा pci_dev *pdev)
अणु
	काष्ठा Scsi_Host *shost;
	काष्ठा MPT3SAS_ADAPTER *ioc;

	अगर (_scsih_get_shost_and_ioc(pdev, &shost, &ioc))
		वापस PCI_ERS_RESULT_DISCONNECT;

	ioc_info(ioc, "PCI error: mmio enabled callback!!\n");

	/* TODO - dump whatever क्रम debugging purposes */

	/* This called only अगर scsih_pci_error_detected वापसs
	 * PCI_ERS_RESULT_CAN_RECOVER. Read/ग_लिखो to the device still
	 * works, no need to reset slot.
	 */
	वापस PCI_ERS_RESULT_RECOVERED;
पूर्ण

/**
 * scsih_ncq_prio_supp - Check क्रम NCQ command priority support
 * @sdev: scsi device काष्ठा
 *
 * This is called when a user indicates they would like to enable
 * ncq command priorities. This works only on SATA devices.
 */
bool scsih_ncq_prio_supp(काष्ठा scsi_device *sdev)
अणु
	अचिन्हित अक्षर *buf;
	bool ncq_prio_supp = false;

	अगर (!scsi_device_supports_vpd(sdev))
		वापस ncq_prio_supp;

	buf = kदो_स्मृति(SCSI_VPD_PG_LEN, GFP_KERNEL);
	अगर (!buf)
		वापस ncq_prio_supp;

	अगर (!scsi_get_vpd_page(sdev, 0x89, buf, SCSI_VPD_PG_LEN))
		ncq_prio_supp = (buf[213] >> 4) & 1;

	kमुक्त(buf);
	वापस ncq_prio_supp;
पूर्ण
/*
 * The pci device ids are defined in mpi/mpi2_cnfg.h.
 */
अटल स्थिर काष्ठा pci_device_id mpt3sas_pci_table[] = अणु
	/* Spitfire ~ 2004 */
	अणु MPI2_MFGPAGE_VENDORID_LSI, MPI2_MFGPAGE_DEVID_SAS2004,
		PCI_ANY_ID, PCI_ANY_ID पूर्ण,
	/* Falcon ~ 2008 */
	अणु MPI2_MFGPAGE_VENDORID_LSI, MPI2_MFGPAGE_DEVID_SAS2008,
		PCI_ANY_ID, PCI_ANY_ID पूर्ण,
	/* Liberator ~ 2108 */
	अणु MPI2_MFGPAGE_VENDORID_LSI, MPI2_MFGPAGE_DEVID_SAS2108_1,
		PCI_ANY_ID, PCI_ANY_ID पूर्ण,
	अणु MPI2_MFGPAGE_VENDORID_LSI, MPI2_MFGPAGE_DEVID_SAS2108_2,
		PCI_ANY_ID, PCI_ANY_ID पूर्ण,
	अणु MPI2_MFGPAGE_VENDORID_LSI, MPI2_MFGPAGE_DEVID_SAS2108_3,
		PCI_ANY_ID, PCI_ANY_ID पूर्ण,
	/* Meteor ~ 2116 */
	अणु MPI2_MFGPAGE_VENDORID_LSI, MPI2_MFGPAGE_DEVID_SAS2116_1,
		PCI_ANY_ID, PCI_ANY_ID पूर्ण,
	अणु MPI2_MFGPAGE_VENDORID_LSI, MPI2_MFGPAGE_DEVID_SAS2116_2,
		PCI_ANY_ID, PCI_ANY_ID पूर्ण,
	/* Thunderbolt ~ 2208 */
	अणु MPI2_MFGPAGE_VENDORID_LSI, MPI2_MFGPAGE_DEVID_SAS2208_1,
		PCI_ANY_ID, PCI_ANY_ID पूर्ण,
	अणु MPI2_MFGPAGE_VENDORID_LSI, MPI2_MFGPAGE_DEVID_SAS2208_2,
		PCI_ANY_ID, PCI_ANY_ID पूर्ण,
	अणु MPI2_MFGPAGE_VENDORID_LSI, MPI2_MFGPAGE_DEVID_SAS2208_3,
		PCI_ANY_ID, PCI_ANY_ID पूर्ण,
	अणु MPI2_MFGPAGE_VENDORID_LSI, MPI2_MFGPAGE_DEVID_SAS2208_4,
		PCI_ANY_ID, PCI_ANY_ID पूर्ण,
	अणु MPI2_MFGPAGE_VENDORID_LSI, MPI2_MFGPAGE_DEVID_SAS2208_5,
		PCI_ANY_ID, PCI_ANY_ID पूर्ण,
	अणु MPI2_MFGPAGE_VENDORID_LSI, MPI2_MFGPAGE_DEVID_SAS2208_6,
		PCI_ANY_ID, PCI_ANY_ID पूर्ण,
	/* Mustang ~ 2308 */
	अणु MPI2_MFGPAGE_VENDORID_LSI, MPI2_MFGPAGE_DEVID_SAS2308_1,
		PCI_ANY_ID, PCI_ANY_ID पूर्ण,
	अणु MPI2_MFGPAGE_VENDORID_LSI, MPI2_MFGPAGE_DEVID_SAS2308_2,
		PCI_ANY_ID, PCI_ANY_ID पूर्ण,
	अणु MPI2_MFGPAGE_VENDORID_LSI, MPI2_MFGPAGE_DEVID_SAS2308_3,
		PCI_ANY_ID, PCI_ANY_ID पूर्ण,
	अणु MPI2_MFGPAGE_VENDORID_LSI, MPI2_MFGPAGE_DEVID_SWITCH_MPI_EP,
		PCI_ANY_ID, PCI_ANY_ID पूर्ण,
	अणु MPI2_MFGPAGE_VENDORID_LSI, MPI2_MFGPAGE_DEVID_SWITCH_MPI_EP_1,
		PCI_ANY_ID, PCI_ANY_ID पूर्ण,
	/* SSS6200 */
	अणु MPI2_MFGPAGE_VENDORID_LSI, MPI2_MFGPAGE_DEVID_SSS6200,
		PCI_ANY_ID, PCI_ANY_ID पूर्ण,
	/* Fury ~ 3004 and 3008 */
	अणु MPI2_MFGPAGE_VENDORID_LSI, MPI25_MFGPAGE_DEVID_SAS3004,
		PCI_ANY_ID, PCI_ANY_ID पूर्ण,
	अणु MPI2_MFGPAGE_VENDORID_LSI, MPI25_MFGPAGE_DEVID_SAS3008,
		PCI_ANY_ID, PCI_ANY_ID पूर्ण,
	/* Invader ~ 3108 */
	अणु MPI2_MFGPAGE_VENDORID_LSI, MPI25_MFGPAGE_DEVID_SAS3108_1,
		PCI_ANY_ID, PCI_ANY_ID पूर्ण,
	अणु MPI2_MFGPAGE_VENDORID_LSI, MPI25_MFGPAGE_DEVID_SAS3108_2,
		PCI_ANY_ID, PCI_ANY_ID पूर्ण,
	अणु MPI2_MFGPAGE_VENDORID_LSI, MPI25_MFGPAGE_DEVID_SAS3108_5,
		PCI_ANY_ID, PCI_ANY_ID पूर्ण,
	अणु MPI2_MFGPAGE_VENDORID_LSI, MPI25_MFGPAGE_DEVID_SAS3108_6,
		PCI_ANY_ID, PCI_ANY_ID पूर्ण,
	/* Cutlass ~ 3216 and 3224 */
	अणु MPI2_MFGPAGE_VENDORID_LSI, MPI26_MFGPAGE_DEVID_SAS3216,
		PCI_ANY_ID, PCI_ANY_ID पूर्ण,
	अणु MPI2_MFGPAGE_VENDORID_LSI, MPI26_MFGPAGE_DEVID_SAS3224,
		PCI_ANY_ID, PCI_ANY_ID पूर्ण,
	/* Intruder ~ 3316 and 3324 */
	अणु MPI2_MFGPAGE_VENDORID_LSI, MPI26_MFGPAGE_DEVID_SAS3316_1,
		PCI_ANY_ID, PCI_ANY_ID पूर्ण,
	अणु MPI2_MFGPAGE_VENDORID_LSI, MPI26_MFGPAGE_DEVID_SAS3316_2,
		PCI_ANY_ID, PCI_ANY_ID पूर्ण,
	अणु MPI2_MFGPAGE_VENDORID_LSI, MPI26_MFGPAGE_DEVID_SAS3316_3,
		PCI_ANY_ID, PCI_ANY_ID पूर्ण,
	अणु MPI2_MFGPAGE_VENDORID_LSI, MPI26_MFGPAGE_DEVID_SAS3316_4,
		PCI_ANY_ID, PCI_ANY_ID पूर्ण,
	अणु MPI2_MFGPAGE_VENDORID_LSI, MPI26_MFGPAGE_DEVID_SAS3324_1,
		PCI_ANY_ID, PCI_ANY_ID पूर्ण,
	अणु MPI2_MFGPAGE_VENDORID_LSI, MPI26_MFGPAGE_DEVID_SAS3324_2,
		PCI_ANY_ID, PCI_ANY_ID पूर्ण,
	अणु MPI2_MFGPAGE_VENDORID_LSI, MPI26_MFGPAGE_DEVID_SAS3324_3,
		PCI_ANY_ID, PCI_ANY_ID पूर्ण,
	अणु MPI2_MFGPAGE_VENDORID_LSI, MPI26_MFGPAGE_DEVID_SAS3324_4,
		PCI_ANY_ID, PCI_ANY_ID पूर्ण,
	/* Ventura, Crusader, Harpoon & Tomcat ~ 3516, 3416, 3508 & 3408*/
	अणु MPI2_MFGPAGE_VENDORID_LSI, MPI26_MFGPAGE_DEVID_SAS3508,
		PCI_ANY_ID, PCI_ANY_ID पूर्ण,
	अणु MPI2_MFGPAGE_VENDORID_LSI, MPI26_MFGPAGE_DEVID_SAS3508_1,
		PCI_ANY_ID, PCI_ANY_ID पूर्ण,
	अणु MPI2_MFGPAGE_VENDORID_LSI, MPI26_MFGPAGE_DEVID_SAS3408,
		PCI_ANY_ID, PCI_ANY_ID पूर्ण,
	अणु MPI2_MFGPAGE_VENDORID_LSI, MPI26_MFGPAGE_DEVID_SAS3516,
		PCI_ANY_ID, PCI_ANY_ID पूर्ण,
	अणु MPI2_MFGPAGE_VENDORID_LSI, MPI26_MFGPAGE_DEVID_SAS3516_1,
		PCI_ANY_ID, PCI_ANY_ID पूर्ण,
	अणु MPI2_MFGPAGE_VENDORID_LSI, MPI26_MFGPAGE_DEVID_SAS3416,
		PCI_ANY_ID, PCI_ANY_ID पूर्ण,
	/* Mercator ~ 3616*/
	अणु MPI2_MFGPAGE_VENDORID_LSI, MPI26_MFGPAGE_DEVID_SAS3616,
		PCI_ANY_ID, PCI_ANY_ID पूर्ण,

	/* Aero SI 0x00E1 Configurable Secure
	 * 0x00E2 Hard Secure
	 */
	अणु MPI2_MFGPAGE_VENDORID_LSI, MPI26_MFGPAGE_DEVID_CFG_SEC_3916,
		PCI_ANY_ID, PCI_ANY_ID पूर्ण,
	अणु MPI2_MFGPAGE_VENDORID_LSI, MPI26_MFGPAGE_DEVID_HARD_SEC_3916,
		PCI_ANY_ID, PCI_ANY_ID पूर्ण,

	/*
	 *  Aero SI ै > 0x00E0 Invalid, 0x00E3 Tampered
	 */
	अणु MPI2_MFGPAGE_VENDORID_LSI, MPI26_MFGPAGE_DEVID_INVALID0_3916,
		PCI_ANY_ID, PCI_ANY_ID पूर्ण,
	अणु MPI2_MFGPAGE_VENDORID_LSI, MPI26_MFGPAGE_DEVID_INVALID1_3916,
		PCI_ANY_ID, PCI_ANY_ID पूर्ण,

	/* Atlas PCIe Switch Management Port */
	अणु MPI2_MFGPAGE_VENDORID_LSI, MPI26_ATLAS_PCIe_SWITCH_DEVID,
		PCI_ANY_ID, PCI_ANY_ID पूर्ण,

	/* Sea SI 0x00E5 Configurable Secure
	 * 0x00E6 Hard Secure
	 */
	अणु MPI2_MFGPAGE_VENDORID_LSI, MPI26_MFGPAGE_DEVID_CFG_SEC_3816,
		PCI_ANY_ID, PCI_ANY_ID पूर्ण,
	अणु MPI2_MFGPAGE_VENDORID_LSI, MPI26_MFGPAGE_DEVID_HARD_SEC_3816,
		PCI_ANY_ID, PCI_ANY_ID पूर्ण,

	/*
	 *  Sea SI ै > 0x00E4 Invalid, 0x00E7 Tampered
	 */
	अणु MPI2_MFGPAGE_VENDORID_LSI, MPI26_MFGPAGE_DEVID_INVALID0_3816,
		PCI_ANY_ID, PCI_ANY_ID पूर्ण,
	अणु MPI2_MFGPAGE_VENDORID_LSI, MPI26_MFGPAGE_DEVID_INVALID1_3816,
		PCI_ANY_ID, PCI_ANY_ID पूर्ण,

	अणु0पूर्ण     /* Terminating entry */
पूर्ण;
MODULE_DEVICE_TABLE(pci, mpt3sas_pci_table);

अटल काष्ठा pci_error_handlers _mpt3sas_err_handler = अणु
	.error_detected	= scsih_pci_error_detected,
	.mmio_enabled	= scsih_pci_mmio_enabled,
	.slot_reset	= scsih_pci_slot_reset,
	.resume		= scsih_pci_resume,
पूर्ण;

अटल SIMPLE_DEV_PM_OPS(scsih_pm_ops, scsih_suspend, scsih_resume);

अटल काष्ठा pci_driver mpt3sas_driver = अणु
	.name		= MPT3SAS_DRIVER_NAME,
	.id_table	= mpt3sas_pci_table,
	.probe		= _scsih_probe,
	.हटाओ		= scsih_हटाओ,
	.shutकरोwn	= scsih_shutकरोwn,
	.err_handler	= &_mpt3sas_err_handler,
	.driver.pm	= &scsih_pm_ops,
पूर्ण;

/**
 * scsih_init - मुख्य entry poपूर्णांक क्रम this driver.
 *
 * Return: 0 success, anything अन्यथा error.
 */
अटल पूर्णांक
scsih_init(व्योम)
अणु
	mpt2_ids = 0;
	mpt3_ids = 0;

	mpt3sas_base_initialize_callback_handler();

	 /* queuecommand callback hander */
	scsi_io_cb_idx = mpt3sas_base_रेजिस्टर_callback_handler(_scsih_io_करोne);

	/* task management callback handler */
	पंचांग_cb_idx = mpt3sas_base_रेजिस्टर_callback_handler(_scsih_पंचांग_करोne);

	/* base पूर्णांकernal commands callback handler */
	base_cb_idx = mpt3sas_base_रेजिस्टर_callback_handler(mpt3sas_base_करोne);
	port_enable_cb_idx = mpt3sas_base_रेजिस्टर_callback_handler(
	    mpt3sas_port_enable_करोne);

	/* transport पूर्णांकernal commands callback handler */
	transport_cb_idx = mpt3sas_base_रेजिस्टर_callback_handler(
	    mpt3sas_transport_करोne);

	/* scsih पूर्णांकernal commands callback handler */
	scsih_cb_idx = mpt3sas_base_रेजिस्टर_callback_handler(_scsih_करोne);

	/* configuration page API पूर्णांकernal commands callback handler */
	config_cb_idx = mpt3sas_base_रेजिस्टर_callback_handler(
	    mpt3sas_config_करोne);

	/* ctl module callback handler */
	ctl_cb_idx = mpt3sas_base_रेजिस्टर_callback_handler(mpt3sas_ctl_करोne);

	पंचांग_tr_cb_idx = mpt3sas_base_रेजिस्टर_callback_handler(
	    _scsih_पंचांग_tr_complete);

	पंचांग_tr_volume_cb_idx = mpt3sas_base_रेजिस्टर_callback_handler(
	    _scsih_पंचांग_volume_tr_complete);

	पंचांग_sas_control_cb_idx = mpt3sas_base_रेजिस्टर_callback_handler(
	    _scsih_sas_control_complete);

	mpt3sas_init_debugfs();
	वापस 0;
पूर्ण

/**
 * scsih_निकास - निकास poपूर्णांक क्रम this driver (when it is a module).
 *
 * Return: 0 success, anything अन्यथा error.
 */
अटल व्योम
scsih_निकास(व्योम)
अणु

	mpt3sas_base_release_callback_handler(scsi_io_cb_idx);
	mpt3sas_base_release_callback_handler(पंचांग_cb_idx);
	mpt3sas_base_release_callback_handler(base_cb_idx);
	mpt3sas_base_release_callback_handler(port_enable_cb_idx);
	mpt3sas_base_release_callback_handler(transport_cb_idx);
	mpt3sas_base_release_callback_handler(scsih_cb_idx);
	mpt3sas_base_release_callback_handler(config_cb_idx);
	mpt3sas_base_release_callback_handler(ctl_cb_idx);

	mpt3sas_base_release_callback_handler(पंचांग_tr_cb_idx);
	mpt3sas_base_release_callback_handler(पंचांग_tr_volume_cb_idx);
	mpt3sas_base_release_callback_handler(पंचांग_sas_control_cb_idx);

/* raid transport support */
	अगर (hbas_to_क्रमागतerate != 1)
		raid_class_release(mpt3sas_raid_ढाँचा);
	अगर (hbas_to_क्रमागतerate != 2)
		raid_class_release(mpt2sas_raid_ढाँचा);
	sas_release_transport(mpt3sas_transport_ढाँचा);
	mpt3sas_निकास_debugfs();
पूर्ण

/**
 * _mpt3sas_init - मुख्य entry poपूर्णांक क्रम this driver.
 *
 * Return: 0 success, anything अन्यथा error.
 */
अटल पूर्णांक __init
_mpt3sas_init(व्योम)
अणु
	पूर्णांक error;

	pr_info("%s version %s loaded\n", MPT3SAS_DRIVER_NAME,
					MPT3SAS_DRIVER_VERSION);

	mpt3sas_transport_ढाँचा =
	    sas_attach_transport(&mpt3sas_transport_functions);
	अगर (!mpt3sas_transport_ढाँचा)
		वापस -ENODEV;

	/* No need attach mpt3sas raid functions ढाँचा
	 * अगर hbas_to_क्रमागतarate value is one.
	 */
	अगर (hbas_to_क्रमागतerate != 1) अणु
		mpt3sas_raid_ढाँचा =
				raid_class_attach(&mpt3sas_raid_functions);
		अगर (!mpt3sas_raid_ढाँचा) अणु
			sas_release_transport(mpt3sas_transport_ढाँचा);
			वापस -ENODEV;
		पूर्ण
	पूर्ण

	/* No need to attach mpt2sas raid functions ढाँचा
	 * अगर hbas_to_क्रमागतarate value is two
	 */
	अगर (hbas_to_क्रमागतerate != 2) अणु
		mpt2sas_raid_ढाँचा =
				raid_class_attach(&mpt2sas_raid_functions);
		अगर (!mpt2sas_raid_ढाँचा) अणु
			sas_release_transport(mpt3sas_transport_ढाँचा);
			वापस -ENODEV;
		पूर्ण
	पूर्ण

	error = scsih_init();
	अगर (error) अणु
		scsih_निकास();
		वापस error;
	पूर्ण

	mpt3sas_ctl_init(hbas_to_क्रमागतerate);

	error = pci_रेजिस्टर_driver(&mpt3sas_driver);
	अगर (error)
		scsih_निकास();

	वापस error;
पूर्ण

/**
 * _mpt3sas_निकास - निकास poपूर्णांक क्रम this driver (when it is a module).
 *
 */
अटल व्योम __निकास
_mpt3sas_निकास(व्योम)
अणु
	pr_info("mpt3sas version %s unloading\n",
				MPT3SAS_DRIVER_VERSION);

	mpt3sas_ctl_निकास(hbas_to_क्रमागतerate);

	pci_unरेजिस्टर_driver(&mpt3sas_driver);

	scsih_निकास();
पूर्ण

module_init(_mpt3sas_init);
module_निकास(_mpt3sas_निकास);
