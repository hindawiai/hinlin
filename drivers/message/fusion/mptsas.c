<शैली गुरु>
/*
 *  linux/drivers/message/fusion/mptsas.c
 *      For use with LSI PCI chip/adapter(s)
 *      running LSI Fusion MPT (Message Passing Technology) firmware.
 *
 *  Copyright (c) 1999-2008 LSI Corporation
 *  (mailto:DL-MPTFusionLinux@lsi.com)
 */
/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/*
    This program is मुक्त software; you can redistribute it and/or modअगरy
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; version 2 of the License.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License क्रम more details.

    NO WARRANTY
    THE PROGRAM IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OR
    CONDITIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED INCLUDING, WITHOUT
    LIMITATION, ANY WARRANTIES OR CONDITIONS OF TITLE, NON-INFRINGEMENT,
    MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE. Each Recipient is
    solely responsible क्रम determining the appropriateness of using and
    distributing the Program and assumes all risks associated with its
    exercise of rights under this Agreement, including but not limited to
    the risks and costs of program errors, damage to or loss of data,
    programs or equipment, and unavailability or पूर्णांकerruption of operations.

    DISCLAIMER OF LIABILITY
    NEITHER RECIPIENT NOR ANY CONTRIBUTORS SHALL HAVE ANY LIABILITY FOR ANY
    सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
    DAMAGES (INCLUDING WITHOUT LIMITATION LOST PROFITS), HOWEVER CAUSED AND
    ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR
    TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE
    USE OR DISTRIBUTION OF THE PROGRAM OR THE EXERCISE OF ANY RIGHTS GRANTED
    HEREUNDER, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGES

    You should have received a copy of the GNU General Public License
    aदीर्घ with this program; अगर not, ग_लिखो to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/
/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/init.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/delay.h>	/* क्रम mdelay */

#समावेश <scsi/scsi.h>
#समावेश <scsi/scsi_cmnd.h>
#समावेश <scsi/scsi_device.h>
#समावेश <scsi/scsi_host.h>
#समावेश <scsi/scsi_transport_sas.h>
#समावेश <scsi/scsi_transport.h>
#समावेश <scsi/scsi_dbg.h>

#समावेश "mptbase.h"
#समावेश "mptscsih.h"
#समावेश "mptsas.h"


#घोषणा my_NAME		"Fusion MPT SAS Host driver"
#घोषणा my_VERSION	MPT_LINUX_VERSION_COMMON
#घोषणा MYNAM		"mptsas"

/*
 * Reserved channel क्रम पूर्णांकegrated raid
 */
#घोषणा MPTSAS_RAID_CHANNEL	1

#घोषणा SAS_CONFIG_PAGE_TIMEOUT		30
MODULE_AUTHOR(MODULEAUTHOR);
MODULE_DESCRIPTION(my_NAME);
MODULE_LICENSE("GPL");
MODULE_VERSION(my_VERSION);

अटल पूर्णांक mpt_pt_clear;
module_param(mpt_pt_clear, पूर्णांक, 0);
MODULE_PARM_DESC(mpt_pt_clear,
		" Clear persistency table: enable=1  "
		"(default=MPTSCSIH_PT_CLEAR=0)");

/* scsi-mid layer global parmeter is max_report_luns, which is 511 */
#घोषणा MPTSAS_MAX_LUN (16895)
अटल पूर्णांक max_lun = MPTSAS_MAX_LUN;
module_param(max_lun, पूर्णांक, 0);
MODULE_PARM_DESC(max_lun, " max lun, default=16895 ");

अटल पूर्णांक mpt_loadसमय_max_sectors = 8192;
module_param(mpt_loadसमय_max_sectors, पूर्णांक, 0);
MODULE_PARM_DESC(mpt_loadसमय_max_sectors,
		" Maximum sector define for Host Bus Adaptor.Range 64 to 8192 default=8192");

अटल u8	mptsasDoneCtx = MPT_MAX_PROTOCOL_DRIVERS;
अटल u8	mptsasTaskCtx = MPT_MAX_PROTOCOL_DRIVERS;
अटल u8	mptsasInternalCtx = MPT_MAX_PROTOCOL_DRIVERS; /* Used only क्रम पूर्णांकernal commands */
अटल u8	mptsasMgmtCtx = MPT_MAX_PROTOCOL_DRIVERS;
अटल u8	mptsasDeviceResetCtx = MPT_MAX_PROTOCOL_DRIVERS;

अटल व्योम mptsas_firmware_event_work(काष्ठा work_काष्ठा *work);
अटल व्योम mptsas_send_sas_event(काष्ठा fw_event_work *fw_event);
अटल व्योम mptsas_send_raid_event(काष्ठा fw_event_work *fw_event);
अटल व्योम mptsas_send_ir2_event(काष्ठा fw_event_work *fw_event);
अटल व्योम mptsas_parse_device_info(काष्ठा sas_identअगरy *identअगरy,
		काष्ठा mptsas_devinfo *device_info);
अटल अंतरभूत व्योम mptsas_set_rphy(MPT_ADAPTER *ioc,
		काष्ठा mptsas_phyinfo *phy_info, काष्ठा sas_rphy *rphy);
अटल काष्ठा mptsas_phyinfo	*mptsas_find_phyinfo_by_sas_address
		(MPT_ADAPTER *ioc, u64 sas_address);
अटल पूर्णांक mptsas_sas_device_pg0(MPT_ADAPTER *ioc,
	काष्ठा mptsas_devinfo *device_info, u32 क्रमm, u32 क्रमm_specअगरic);
अटल पूर्णांक mptsas_sas_enclosure_pg0(MPT_ADAPTER *ioc,
	काष्ठा mptsas_enclosure *enclosure, u32 क्रमm, u32 क्रमm_specअगरic);
अटल पूर्णांक mptsas_add_end_device(MPT_ADAPTER *ioc,
	काष्ठा mptsas_phyinfo *phy_info);
अटल व्योम mptsas_del_end_device(MPT_ADAPTER *ioc,
	काष्ठा mptsas_phyinfo *phy_info);
अटल व्योम mptsas_send_link_status_event(काष्ठा fw_event_work *fw_event);
अटल काष्ठा mptsas_portinfo	*mptsas_find_portinfo_by_sas_address
		(MPT_ADAPTER *ioc, u64 sas_address);
अटल व्योम mptsas_expander_delete(MPT_ADAPTER *ioc,
		काष्ठा mptsas_portinfo *port_info, u8 क्रमce);
अटल व्योम mptsas_send_expander_event(काष्ठा fw_event_work *fw_event);
अटल व्योम mptsas_not_responding_devices(MPT_ADAPTER *ioc);
अटल व्योम mptsas_scan_sas_topology(MPT_ADAPTER *ioc);
अटल व्योम mptsas_broadcast_primitive_work(काष्ठा fw_event_work *fw_event);
अटल व्योम mptsas_handle_queue_full_event(काष्ठा fw_event_work *fw_event);
अटल व्योम mptsas_volume_delete(MPT_ADAPTER *ioc, u8 id);
व्योम	mptsas_schedule_target_reset(व्योम *ioc);

अटल व्योम mptsas_prपूर्णांक_phy_data(MPT_ADAPTER *ioc,
					MPI_SAS_IO_UNIT0_PHY_DATA *phy_data)
अणु
	dsasprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT
	    "---- IO UNIT PAGE 0 ------------\n", ioc->name));
	dsasprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT "Handle=0x%X\n",
	    ioc->name, le16_to_cpu(phy_data->AttachedDeviceHandle)));
	dsasprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT "Controller Handle=0x%X\n",
	    ioc->name, le16_to_cpu(phy_data->ControllerDevHandle)));
	dsasprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT "Port=0x%X\n",
	    ioc->name, phy_data->Port));
	dsasprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT "Port Flags=0x%X\n",
	    ioc->name, phy_data->PortFlags));
	dsasprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT "PHY Flags=0x%X\n",
	    ioc->name, phy_data->PhyFlags));
	dsasprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT "Negotiated Link Rate=0x%X\n",
	    ioc->name, phy_data->NegotiatedLinkRate));
	dsasprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT
	    "Controller PHY Device Info=0x%X\n", ioc->name,
	    le32_to_cpu(phy_data->ControllerPhyDeviceInfo)));
	dsasprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT "DiscoveryStatus=0x%X\n\n",
	    ioc->name, le32_to_cpu(phy_data->DiscoveryStatus)));
पूर्ण

अटल व्योम mptsas_prपूर्णांक_phy_pg0(MPT_ADAPTER *ioc, SasPhyPage0_t *pg0)
अणु
	__le64 sas_address;

	स_नकल(&sas_address, &pg0->SASAddress, माप(__le64));

	dsasprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT
	    "---- SAS PHY PAGE 0 ------------\n", ioc->name));
	dsasprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT
	    "Attached Device Handle=0x%X\n", ioc->name,
	    le16_to_cpu(pg0->AttachedDevHandle)));
	dsasprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT "SAS Address=0x%llX\n",
	    ioc->name, (अचिन्हित दीर्घ दीर्घ)le64_to_cpu(sas_address)));
	dsasprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT
	    "Attached PHY Identifier=0x%X\n", ioc->name,
	    pg0->AttachedPhyIdentअगरier));
	dsasprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT "Attached Device Info=0x%X\n",
	    ioc->name, le32_to_cpu(pg0->AttachedDeviceInfo)));
	dsasprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT "Programmed Link Rate=0x%X\n",
	    ioc->name,  pg0->ProgrammedLinkRate));
	dsasprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT "Change Count=0x%X\n",
	    ioc->name, pg0->ChangeCount));
	dsasprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT "PHY Info=0x%X\n\n",
	    ioc->name, le32_to_cpu(pg0->PhyInfo)));
पूर्ण

अटल व्योम mptsas_prपूर्णांक_phy_pg1(MPT_ADAPTER *ioc, SasPhyPage1_t *pg1)
अणु
	dsasprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT
	    "---- SAS PHY PAGE 1 ------------\n", ioc->name));
	dsasprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT "Invalid Dword Count=0x%x\n",
	    ioc->name,  pg1->InvalidDwordCount));
	dsasprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT
	    "Running Disparity Error Count=0x%x\n", ioc->name,
	    pg1->RunningDisparityErrorCount));
	dsasprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT
	    "Loss Dword Synch Count=0x%x\n", ioc->name,
	    pg1->LossDwordSynchCount));
	dsasprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT
	    "PHY Reset Problem Count=0x%x\n\n", ioc->name,
	    pg1->PhyResetProblemCount));
पूर्ण

अटल व्योम mptsas_prपूर्णांक_device_pg0(MPT_ADAPTER *ioc, SasDevicePage0_t *pg0)
अणु
	__le64 sas_address;

	स_नकल(&sas_address, &pg0->SASAddress, माप(__le64));

	dsasprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT
	    "---- SAS DEVICE PAGE 0 ---------\n", ioc->name));
	dsasprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT "Handle=0x%X\n",
	    ioc->name, le16_to_cpu(pg0->DevHandle)));
	dsasprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT "Parent Handle=0x%X\n",
	    ioc->name, le16_to_cpu(pg0->ParentDevHandle)));
	dsasprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT "Enclosure Handle=0x%X\n",
	    ioc->name, le16_to_cpu(pg0->EnclosureHandle)));
	dsasprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT "Slot=0x%X\n",
	    ioc->name, le16_to_cpu(pg0->Slot)));
	dsasprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT "SAS Address=0x%llX\n",
	    ioc->name, (अचिन्हित दीर्घ दीर्घ)le64_to_cpu(sas_address)));
	dsasprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT "Target ID=0x%X\n",
	    ioc->name, pg0->TargetID));
	dsasprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT "Bus=0x%X\n",
	    ioc->name, pg0->Bus));
	dsasprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT "Parent Phy Num=0x%X\n",
	    ioc->name, pg0->PhyNum));
	dsasprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT "Access Status=0x%X\n",
	    ioc->name, le16_to_cpu(pg0->AccessStatus)));
	dsasprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT "Device Info=0x%X\n",
	    ioc->name, le32_to_cpu(pg0->DeviceInfo)));
	dsasprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT "Flags=0x%X\n",
	    ioc->name, le16_to_cpu(pg0->Flags)));
	dsasprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT "Physical Port=0x%X\n\n",
	    ioc->name, pg0->PhysicalPort));
पूर्ण

अटल व्योम mptsas_prपूर्णांक_expander_pg1(MPT_ADAPTER *ioc, SasExpanderPage1_t *pg1)
अणु
	dsasprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT
	    "---- SAS EXPANDER PAGE 1 ------------\n", ioc->name));
	dsasprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT "Physical Port=0x%X\n",
	    ioc->name, pg1->PhysicalPort));
	dsasprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT "PHY Identifier=0x%X\n",
	    ioc->name, pg1->PhyIdentअगरier));
	dsasprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT "Negotiated Link Rate=0x%X\n",
	    ioc->name, pg1->NegotiatedLinkRate));
	dsasprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT "Programmed Link Rate=0x%X\n",
	    ioc->name, pg1->ProgrammedLinkRate));
	dsasprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT "Hardware Link Rate=0x%X\n",
	    ioc->name, pg1->HwLinkRate));
	dsasprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT "Owner Device Handle=0x%X\n",
	    ioc->name, le16_to_cpu(pg1->OwnerDevHandle)));
	dsasprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT
	    "Attached Device Handle=0x%X\n\n", ioc->name,
	    le16_to_cpu(pg1->AttachedDevHandle)));
पूर्ण

/* inhibit sas firmware event handling */
अटल व्योम
mptsas_fw_event_off(MPT_ADAPTER *ioc)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ioc->fw_event_lock, flags);
	ioc->fw_events_off = 1;
	ioc->sas_discovery_quiesce_io = 0;
	spin_unlock_irqrestore(&ioc->fw_event_lock, flags);

पूर्ण

/* enable sas firmware event handling */
अटल व्योम
mptsas_fw_event_on(MPT_ADAPTER *ioc)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ioc->fw_event_lock, flags);
	ioc->fw_events_off = 0;
	spin_unlock_irqrestore(&ioc->fw_event_lock, flags);
पूर्ण

/* queue a sas firmware event */
अटल व्योम
mptsas_add_fw_event(MPT_ADAPTER *ioc, काष्ठा fw_event_work *fw_event,
    अचिन्हित दीर्घ delay)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ioc->fw_event_lock, flags);
	list_add_tail(&fw_event->list, &ioc->fw_event_list);
	fw_event->users = 1;
	INIT_DELAYED_WORK(&fw_event->work, mptsas_firmware_event_work);
	devtprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT "%s: add (fw_event=0x%p)"
		"on cpuid %d\n", ioc->name, __func__,
		fw_event, smp_processor_id()));
	queue_delayed_work_on(smp_processor_id(), ioc->fw_event_q,
	    &fw_event->work, delay);
	spin_unlock_irqrestore(&ioc->fw_event_lock, flags);
पूर्ण

/* requeue a sas firmware event */
अटल व्योम
mptsas_requeue_fw_event(MPT_ADAPTER *ioc, काष्ठा fw_event_work *fw_event,
    अचिन्हित दीर्घ delay)
अणु
	अचिन्हित दीर्घ flags;
	spin_lock_irqsave(&ioc->fw_event_lock, flags);
	devtprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT "%s: reschedule task "
	    "(fw_event=0x%p)on cpuid %d\n", ioc->name, __func__,
		fw_event, smp_processor_id()));
	fw_event->retries++;
	queue_delayed_work_on(smp_processor_id(), ioc->fw_event_q,
	    &fw_event->work, msecs_to_jअगरfies(delay));
	spin_unlock_irqrestore(&ioc->fw_event_lock, flags);
पूर्ण

अटल व्योम __mptsas_मुक्त_fw_event(MPT_ADAPTER *ioc,
				   काष्ठा fw_event_work *fw_event)
अणु
	devtprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT "%s: kfree (fw_event=0x%p)\n",
	    ioc->name, __func__, fw_event));
	list_del(&fw_event->list);
	kमुक्त(fw_event);
पूर्ण

/* मुक्त memory associated to a sas firmware event */
अटल व्योम
mptsas_मुक्त_fw_event(MPT_ADAPTER *ioc, काष्ठा fw_event_work *fw_event)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ioc->fw_event_lock, flags);
	fw_event->users--;
	अगर (!fw_event->users)
		__mptsas_मुक्त_fw_event(ioc, fw_event);
	spin_unlock_irqrestore(&ioc->fw_event_lock, flags);
पूर्ण

/* walk the firmware event queue, and either stop or रुको क्रम
 * outstanding events to complete */
अटल व्योम
mptsas_cleanup_fw_event_q(MPT_ADAPTER *ioc)
अणु
	काष्ठा fw_event_work *fw_event;
	काष्ठा mptsas_target_reset_event *target_reset_list, *n;
	MPT_SCSI_HOST	*hd = shost_priv(ioc->sh);
	अचिन्हित दीर्घ flags;

	/* flush the target_reset_list */
	अगर (!list_empty(&hd->target_reset_list)) अणु
		list_क्रम_each_entry_safe(target_reset_list, n,
		    &hd->target_reset_list, list) अणु
			dपंचांगprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT
			    "%s: removing target reset for id=%d\n",
			    ioc->name, __func__,
			   target_reset_list->sas_event_data.TargetID));
			list_del(&target_reset_list->list);
			kमुक्त(target_reset_list);
		पूर्ण
	पूर्ण

	अगर (list_empty(&ioc->fw_event_list) || !ioc->fw_event_q)
		वापस;

	spin_lock_irqsave(&ioc->fw_event_lock, flags);

	जबतक (!list_empty(&ioc->fw_event_list)) अणु
		bool canceled = false;

		fw_event = list_first_entry(&ioc->fw_event_list,
					    काष्ठा fw_event_work, list);
		fw_event->users++;
		spin_unlock_irqrestore(&ioc->fw_event_lock, flags);
		अगर (cancel_delayed_work_sync(&fw_event->work))
			canceled = true;

		spin_lock_irqsave(&ioc->fw_event_lock, flags);
		अगर (canceled)
			fw_event->users--;
		fw_event->users--;
		WARN_ON_ONCE(fw_event->users);
		__mptsas_मुक्त_fw_event(ioc, fw_event);
	पूर्ण
	spin_unlock_irqrestore(&ioc->fw_event_lock, flags);
पूर्ण


अटल अंतरभूत MPT_ADAPTER *phy_to_ioc(काष्ठा sas_phy *phy)
अणु
	काष्ठा Scsi_Host *shost = dev_to_shost(phy->dev.parent);
	वापस ((MPT_SCSI_HOST *)shost->hostdata)->ioc;
पूर्ण

अटल अंतरभूत MPT_ADAPTER *rphy_to_ioc(काष्ठा sas_rphy *rphy)
अणु
	काष्ठा Scsi_Host *shost = dev_to_shost(rphy->dev.parent->parent);
	वापस ((MPT_SCSI_HOST *)shost->hostdata)->ioc;
पूर्ण

/*
 * mptsas_find_portinfo_by_handle
 *
 * This function should be called with the sas_topology_mutex alपढ़ोy held
 */
अटल काष्ठा mptsas_portinfo *
mptsas_find_portinfo_by_handle(MPT_ADAPTER *ioc, u16 handle)
अणु
	काष्ठा mptsas_portinfo *port_info, *rc=शून्य;
	पूर्णांक i;

	list_क्रम_each_entry(port_info, &ioc->sas_topology, list)
		क्रम (i = 0; i < port_info->num_phys; i++)
			अगर (port_info->phy_info[i].identअगरy.handle == handle) अणु
				rc = port_info;
				जाओ out;
			पूर्ण
 out:
	वापस rc;
पूर्ण

/**
 *	mptsas_find_portinfo_by_sas_address -
 *	@ioc: Poपूर्णांकer to MPT_ADAPTER काष्ठाure
 *	@handle:
 *
 *	This function should be called with the sas_topology_mutex alपढ़ोy held
 *
 **/
अटल काष्ठा mptsas_portinfo *
mptsas_find_portinfo_by_sas_address(MPT_ADAPTER *ioc, u64 sas_address)
अणु
	काष्ठा mptsas_portinfo *port_info, *rc = शून्य;
	पूर्णांक i;

	अगर (sas_address >= ioc->hba_port_sas_addr &&
	    sas_address < (ioc->hba_port_sas_addr +
	    ioc->hba_port_num_phy))
		वापस ioc->hba_port_info;

	mutex_lock(&ioc->sas_topology_mutex);
	list_क्रम_each_entry(port_info, &ioc->sas_topology, list)
		क्रम (i = 0; i < port_info->num_phys; i++)
			अगर (port_info->phy_info[i].identअगरy.sas_address ==
			    sas_address) अणु
				rc = port_info;
				जाओ out;
			पूर्ण
 out:
	mutex_unlock(&ioc->sas_topology_mutex);
	वापस rc;
पूर्ण

/*
 * Returns true अगर there is a scsi end device
 */
अटल अंतरभूत पूर्णांक
mptsas_is_end_device(काष्ठा mptsas_devinfo * attached)
अणु
	अगर ((attached->sas_address) &&
	    (attached->device_info &
	    MPI_SAS_DEVICE_INFO_END_DEVICE) &&
	    ((attached->device_info &
	    MPI_SAS_DEVICE_INFO_SSP_TARGET) |
	    (attached->device_info &
	    MPI_SAS_DEVICE_INFO_STP_TARGET) |
	    (attached->device_info &
	    MPI_SAS_DEVICE_INFO_SATA_DEVICE)))
		वापस 1;
	अन्यथा
		वापस 0;
पूर्ण

/* no mutex */
अटल व्योम
mptsas_port_delete(MPT_ADAPTER *ioc, काष्ठा mptsas_portinfo_details * port_details)
अणु
	काष्ठा mptsas_portinfo *port_info;
	काष्ठा mptsas_phyinfo *phy_info;
	u8	i;

	अगर (!port_details)
		वापस;

	port_info = port_details->port_info;
	phy_info = port_info->phy_info;

	dsaswideprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT "%s: [%p]: num_phys=%02d "
	    "bitmask=0x%016llX\n", ioc->name, __func__, port_details,
	    port_details->num_phys, (अचिन्हित दीर्घ दीर्घ)
	    port_details->phy_biपंचांगask));

	क्रम (i = 0; i < port_info->num_phys; i++, phy_info++) अणु
		अगर(phy_info->port_details != port_details)
			जारी;
		स_रखो(&phy_info->attached, 0, माप(काष्ठा mptsas_devinfo));
		mptsas_set_rphy(ioc, phy_info, शून्य);
		phy_info->port_details = शून्य;
	पूर्ण
	kमुक्त(port_details);
पूर्ण

अटल अंतरभूत काष्ठा sas_rphy *
mptsas_get_rphy(काष्ठा mptsas_phyinfo *phy_info)
अणु
	अगर (phy_info->port_details)
		वापस phy_info->port_details->rphy;
	अन्यथा
		वापस शून्य;
पूर्ण

अटल अंतरभूत व्योम
mptsas_set_rphy(MPT_ADAPTER *ioc, काष्ठा mptsas_phyinfo *phy_info, काष्ठा sas_rphy *rphy)
अणु
	अगर (phy_info->port_details) अणु
		phy_info->port_details->rphy = rphy;
		dsaswideprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT "sas_rphy_add: rphy=%p\n",
		    ioc->name, rphy));
	पूर्ण

	अगर (rphy) अणु
		dsaswideprपूर्णांकk(ioc, dev_prपूर्णांकk(KERN_DEBUG,
		    &rphy->dev, MYIOC_s_FMT "add:", ioc->name));
		dsaswideprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT "rphy=%p release=%p\n",
		    ioc->name, rphy, rphy->dev.release));
	पूर्ण
पूर्ण

अटल अंतरभूत काष्ठा sas_port *
mptsas_get_port(काष्ठा mptsas_phyinfo *phy_info)
अणु
	अगर (phy_info->port_details)
		वापस phy_info->port_details->port;
	अन्यथा
		वापस शून्य;
पूर्ण

अटल अंतरभूत व्योम
mptsas_set_port(MPT_ADAPTER *ioc, काष्ठा mptsas_phyinfo *phy_info, काष्ठा sas_port *port)
अणु
	अगर (phy_info->port_details)
		phy_info->port_details->port = port;

	अगर (port) अणु
		dsaswideprपूर्णांकk(ioc, dev_prपूर्णांकk(KERN_DEBUG,
		    &port->dev, MYIOC_s_FMT "add:", ioc->name));
		dsaswideprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT "port=%p release=%p\n",
		    ioc->name, port, port->dev.release));
	पूर्ण
पूर्ण

अटल अंतरभूत काष्ठा scsi_target *
mptsas_get_starget(काष्ठा mptsas_phyinfo *phy_info)
अणु
	अगर (phy_info->port_details)
		वापस phy_info->port_details->starget;
	अन्यथा
		वापस शून्य;
पूर्ण

अटल अंतरभूत व्योम
mptsas_set_starget(काष्ठा mptsas_phyinfo *phy_info, काष्ठा scsi_target *
starget)
अणु
	अगर (phy_info->port_details)
		phy_info->port_details->starget = starget;
पूर्ण

/**
 *	mptsas_add_device_component -
 *	@ioc: Poपूर्णांकer to MPT_ADAPTER काष्ठाure
 *	@channel: fw mapped id's
 *	@id:
 *	@sas_address:
 *	@device_info:
 *
 **/
अटल व्योम
mptsas_add_device_component(MPT_ADAPTER *ioc, u8 channel, u8 id,
	u64 sas_address, u32 device_info, u16 slot, u64 enclosure_logical_id)
अणु
	काष्ठा mptsas_device_info	*sas_info, *next;
	काष्ठा scsi_device	*sdev;
	काष्ठा scsi_target	*starget;
	काष्ठा sas_rphy	*rphy;

	/*
	 * Delete all matching devices out of the list
	 */
	mutex_lock(&ioc->sas_device_info_mutex);
	list_क्रम_each_entry_safe(sas_info, next, &ioc->sas_device_info_list,
	    list) अणु
		अगर (!sas_info->is_logical_volume &&
		    (sas_info->sas_address == sas_address ||
		    (sas_info->fw.channel == channel &&
		     sas_info->fw.id == id))) अणु
			list_del(&sas_info->list);
			kमुक्त(sas_info);
		पूर्ण
	पूर्ण

	sas_info = kzalloc(माप(काष्ठा mptsas_device_info), GFP_KERNEL);
	अगर (!sas_info)
		जाओ out;

	/*
	 * Set Firmware mapping
	 */
	sas_info->fw.id = id;
	sas_info->fw.channel = channel;

	sas_info->sas_address = sas_address;
	sas_info->device_info = device_info;
	sas_info->slot = slot;
	sas_info->enclosure_logical_id = enclosure_logical_id;
	INIT_LIST_HEAD(&sas_info->list);
	list_add_tail(&sas_info->list, &ioc->sas_device_info_list);

	/*
	 * Set OS mapping
	 */
	shost_क्रम_each_device(sdev, ioc->sh) अणु
		starget = scsi_target(sdev);
		rphy = dev_to_rphy(starget->dev.parent);
		अगर (rphy->identअगरy.sas_address == sas_address) अणु
			sas_info->os.id = starget->id;
			sas_info->os.channel = starget->channel;
		पूर्ण
	पूर्ण

 out:
	mutex_unlock(&ioc->sas_device_info_mutex);
	वापस;
पूर्ण

/**
 *	mptsas_add_device_component_by_fw -
 *	@ioc: Poपूर्णांकer to MPT_ADAPTER काष्ठाure
 *	@channel:  fw mapped id's
 *	@id:
 *
 **/
अटल व्योम
mptsas_add_device_component_by_fw(MPT_ADAPTER *ioc, u8 channel, u8 id)
अणु
	काष्ठा mptsas_devinfo sas_device;
	काष्ठा mptsas_enclosure enclosure_info;
	पूर्णांक rc;

	rc = mptsas_sas_device_pg0(ioc, &sas_device,
	    (MPI_SAS_DEVICE_PGAD_FORM_BUS_TARGET_ID <<
	     MPI_SAS_DEVICE_PGAD_FORM_SHIFT),
	    (channel << 8) + id);
	अगर (rc)
		वापस;

	स_रखो(&enclosure_info, 0, माप(काष्ठा mptsas_enclosure));
	mptsas_sas_enclosure_pg0(ioc, &enclosure_info,
	    (MPI_SAS_ENCLOS_PGAD_FORM_HANDLE <<
	     MPI_SAS_ENCLOS_PGAD_FORM_SHIFT),
	     sas_device.handle_enclosure);

	mptsas_add_device_component(ioc, sas_device.channel,
	    sas_device.id, sas_device.sas_address, sas_device.device_info,
	    sas_device.slot, enclosure_info.enclosure_logical_id);
पूर्ण

/**
 *	mptsas_add_device_component_starget_ir - Handle Integrated RAID, adding each inभागidual device to list
 *	@ioc: Poपूर्णांकer to MPT_ADAPTER काष्ठाure
 *	@channel: fw mapped id's
 *	@id:
 *
 **/
अटल व्योम
mptsas_add_device_component_starget_ir(MPT_ADAPTER *ioc,
		काष्ठा scsi_target *starget)
अणु
	CONFIGPARMS			cfg;
	ConfigPageHeader_t		hdr;
	dma_addr_t			dma_handle;
	pRaidVolumePage0_t		buffer = शून्य;
	पूर्णांक				i;
	RaidPhysDiskPage0_t 		phys_disk;
	काष्ठा mptsas_device_info	*sas_info, *next;

	स_रखो(&cfg, 0 , माप(CONFIGPARMS));
	स_रखो(&hdr, 0 , माप(ConfigPageHeader_t));
	hdr.PageType = MPI_CONFIG_PAGETYPE_RAID_VOLUME;
	/* assumption that all volumes on channel = 0 */
	cfg.pageAddr = starget->id;
	cfg.cfghdr.hdr = &hdr;
	cfg.action = MPI_CONFIG_ACTION_PAGE_HEADER;
	cfg.समयout = SAS_CONFIG_PAGE_TIMEOUT;

	अगर (mpt_config(ioc, &cfg) != 0)
		जाओ out;

	अगर (!hdr.PageLength)
		जाओ out;

	buffer = pci_alloc_consistent(ioc->pcidev, hdr.PageLength * 4,
	    &dma_handle);

	अगर (!buffer)
		जाओ out;

	cfg.physAddr = dma_handle;
	cfg.action = MPI_CONFIG_ACTION_PAGE_READ_CURRENT;

	अगर (mpt_config(ioc, &cfg) != 0)
		जाओ out;

	अगर (!buffer->NumPhysDisks)
		जाओ out;

	/*
	 * Adding entry क्रम hidden components
	 */
	क्रम (i = 0; i < buffer->NumPhysDisks; i++) अणु

		अगर (mpt_raid_phys_disk_pg0(ioc,
		    buffer->PhysDisk[i].PhysDiskNum, &phys_disk) != 0)
			जारी;

		mptsas_add_device_component_by_fw(ioc, phys_disk.PhysDiskBus,
		    phys_disk.PhysDiskID);

		mutex_lock(&ioc->sas_device_info_mutex);
		list_क्रम_each_entry(sas_info, &ioc->sas_device_info_list,
		    list) अणु
			अगर (!sas_info->is_logical_volume &&
			    (sas_info->fw.channel == phys_disk.PhysDiskBus &&
			    sas_info->fw.id == phys_disk.PhysDiskID)) अणु
				sas_info->is_hidden_raid_component = 1;
				sas_info->volume_id = starget->id;
			पूर्ण
		पूर्ण
		mutex_unlock(&ioc->sas_device_info_mutex);

	पूर्ण

	/*
	 * Delete all matching devices out of the list
	 */
	mutex_lock(&ioc->sas_device_info_mutex);
	list_क्रम_each_entry_safe(sas_info, next, &ioc->sas_device_info_list,
	    list) अणु
		अगर (sas_info->is_logical_volume && sas_info->fw.id ==
		    starget->id) अणु
			list_del(&sas_info->list);
			kमुक्त(sas_info);
		पूर्ण
	पूर्ण

	sas_info = kzalloc(माप(काष्ठा mptsas_device_info), GFP_KERNEL);
	अगर (sas_info) अणु
		sas_info->fw.id = starget->id;
		sas_info->os.id = starget->id;
		sas_info->os.channel = starget->channel;
		sas_info->is_logical_volume = 1;
		INIT_LIST_HEAD(&sas_info->list);
		list_add_tail(&sas_info->list, &ioc->sas_device_info_list);
	पूर्ण
	mutex_unlock(&ioc->sas_device_info_mutex);

 out:
	अगर (buffer)
		pci_मुक्त_consistent(ioc->pcidev, hdr.PageLength * 4, buffer,
		    dma_handle);
पूर्ण

/**
 *	mptsas_add_device_component_starget -
 *	@ioc: Poपूर्णांकer to MPT_ADAPTER काष्ठाure
 *	@starget:
 *
 **/
अटल व्योम
mptsas_add_device_component_starget(MPT_ADAPTER *ioc,
	काष्ठा scsi_target *starget)
अणु
	काष्ठा sas_rphy	*rphy;
	काष्ठा mptsas_phyinfo	*phy_info = शून्य;
	काष्ठा mptsas_enclosure	enclosure_info;

	rphy = dev_to_rphy(starget->dev.parent);
	phy_info = mptsas_find_phyinfo_by_sas_address(ioc,
			rphy->identअगरy.sas_address);
	अगर (!phy_info)
		वापस;

	स_रखो(&enclosure_info, 0, माप(काष्ठा mptsas_enclosure));
	mptsas_sas_enclosure_pg0(ioc, &enclosure_info,
		(MPI_SAS_ENCLOS_PGAD_FORM_HANDLE <<
		MPI_SAS_ENCLOS_PGAD_FORM_SHIFT),
		phy_info->attached.handle_enclosure);

	mptsas_add_device_component(ioc, phy_info->attached.channel,
		phy_info->attached.id, phy_info->attached.sas_address,
		phy_info->attached.device_info,
		phy_info->attached.slot, enclosure_info.enclosure_logical_id);
पूर्ण

/**
 *	mptsas_del_device_component_by_os - Once a device has been हटाओd, we mark the entry in the list as being cached
 *	@ioc: Poपूर्णांकer to MPT_ADAPTER काष्ठाure
 *	@channel: os mapped id's
 *	@id:
 *
 **/
अटल व्योम
mptsas_del_device_component_by_os(MPT_ADAPTER *ioc, u8 channel, u8 id)
अणु
	काष्ठा mptsas_device_info	*sas_info, *next;

	/*
	 * Set is_cached flag
	 */
	list_क्रम_each_entry_safe(sas_info, next, &ioc->sas_device_info_list,
		list) अणु
		अगर (sas_info->os.channel == channel && sas_info->os.id == id)
			sas_info->is_cached = 1;
	पूर्ण
पूर्ण

/**
 *	mptsas_del_device_components - Cleaning the list
 *	@ioc: Poपूर्णांकer to MPT_ADAPTER काष्ठाure
 *
 **/
अटल व्योम
mptsas_del_device_components(MPT_ADAPTER *ioc)
अणु
	काष्ठा mptsas_device_info	*sas_info, *next;

	mutex_lock(&ioc->sas_device_info_mutex);
	list_क्रम_each_entry_safe(sas_info, next, &ioc->sas_device_info_list,
		list) अणु
		list_del(&sas_info->list);
		kमुक्त(sas_info);
	पूर्ण
	mutex_unlock(&ioc->sas_device_info_mutex);
पूर्ण


/*
 * mptsas_setup_wide_ports
 *
 * Updates क्रम new and existing narrow/wide port configuration
 * in the sas_topology
 */
अटल व्योम
mptsas_setup_wide_ports(MPT_ADAPTER *ioc, काष्ठा mptsas_portinfo *port_info)
अणु
	काष्ठा mptsas_portinfo_details * port_details;
	काष्ठा mptsas_phyinfo *phy_info, *phy_info_cmp;
	u64	sas_address;
	पूर्णांक	i, j;

	mutex_lock(&ioc->sas_topology_mutex);

	phy_info = port_info->phy_info;
	क्रम (i = 0 ; i < port_info->num_phys ; i++, phy_info++) अणु
		अगर (phy_info->attached.handle)
			जारी;
		port_details = phy_info->port_details;
		अगर (!port_details)
			जारी;
		अगर (port_details->num_phys < 2)
			जारी;
		/*
		 * Removing a phy from a port, letting the last
		 * phy be हटाओd by firmware events.
		 */
		dsaswideprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT
		    "%s: [%p]: deleting phy = %d\n",
		    ioc->name, __func__, port_details, i));
		port_details->num_phys--;
		port_details->phy_biपंचांगask &= ~ (1 << phy_info->phy_id);
		स_रखो(&phy_info->attached, 0, माप(काष्ठा mptsas_devinfo));
		अगर (phy_info->phy) अणु
			devtprपूर्णांकk(ioc, dev_prपूर्णांकk(KERN_DEBUG,
				&phy_info->phy->dev, MYIOC_s_FMT
				"delete phy %d, phy-obj (0x%p)\n", ioc->name,
				phy_info->phy_id, phy_info->phy));
			sas_port_delete_phy(port_details->port, phy_info->phy);
		पूर्ण
		phy_info->port_details = शून्य;
	पूर्ण

	/*
	 * Populate and refresh the tree
	 */
	phy_info = port_info->phy_info;
	क्रम (i = 0 ; i < port_info->num_phys ; i++, phy_info++) अणु
		sas_address = phy_info->attached.sas_address;
		dsaswideprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT "phy_id=%d sas_address=0x%018llX\n",
		    ioc->name, i, (अचिन्हित दीर्घ दीर्घ)sas_address));
		अगर (!sas_address)
			जारी;
		port_details = phy_info->port_details;
		/*
		 * Forming a port
		 */
		अगर (!port_details) अणु
			port_details = kzalloc(माप(काष्ठा
				mptsas_portinfo_details), GFP_KERNEL);
			अगर (!port_details)
				जाओ out;
			port_details->num_phys = 1;
			port_details->port_info = port_info;
			अगर (phy_info->phy_id < 64 )
				port_details->phy_biपंचांगask |=
				    (1 << phy_info->phy_id);
			phy_info->sas_port_add_phy=1;
			dsaswideprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT "\t\tForming port\n\t\t"
			    "phy_id=%d sas_address=0x%018llX\n",
			    ioc->name, i, (अचिन्हित दीर्घ दीर्घ)sas_address));
			phy_info->port_details = port_details;
		पूर्ण

		अगर (i == port_info->num_phys - 1)
			जारी;
		phy_info_cmp = &port_info->phy_info[i + 1];
		क्रम (j = i + 1 ; j < port_info->num_phys ; j++,
		    phy_info_cmp++) अणु
			अगर (!phy_info_cmp->attached.sas_address)
				जारी;
			अगर (sas_address != phy_info_cmp->attached.sas_address)
				जारी;
			अगर (phy_info_cmp->port_details == port_details )
				जारी;
			dsaswideprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT
			    "\t\tphy_id=%d sas_address=0x%018llX\n",
			    ioc->name, j, (अचिन्हित दीर्घ दीर्घ)
			    phy_info_cmp->attached.sas_address));
			अगर (phy_info_cmp->port_details) अणु
				port_details->rphy =
				    mptsas_get_rphy(phy_info_cmp);
				port_details->port =
				    mptsas_get_port(phy_info_cmp);
				port_details->starget =
				    mptsas_get_starget(phy_info_cmp);
				port_details->num_phys =
					phy_info_cmp->port_details->num_phys;
				अगर (!phy_info_cmp->port_details->num_phys)
					kमुक्त(phy_info_cmp->port_details);
			पूर्ण अन्यथा
				phy_info_cmp->sas_port_add_phy=1;
			/*
			 * Adding a phy to a port
			 */
			phy_info_cmp->port_details = port_details;
			अगर (phy_info_cmp->phy_id < 64 )
				port_details->phy_biपंचांगask |=
				(1 << phy_info_cmp->phy_id);
			port_details->num_phys++;
		पूर्ण
	पूर्ण

 out:

	क्रम (i = 0; i < port_info->num_phys; i++) अणु
		port_details = port_info->phy_info[i].port_details;
		अगर (!port_details)
			जारी;
		dsaswideprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT
		    "%s: [%p]: phy_id=%02d num_phys=%02d "
		    "bitmask=0x%016llX\n", ioc->name, __func__,
		    port_details, i, port_details->num_phys,
		    (अचिन्हित दीर्घ दीर्घ)port_details->phy_biपंचांगask));
		dsaswideprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT "\t\tport = %p rphy=%p\n",
		    ioc->name, port_details->port, port_details->rphy));
	पूर्ण
	dsaswideprपूर्णांकk(ioc, prपूर्णांकk("\n"));
	mutex_unlock(&ioc->sas_topology_mutex);
पूर्ण

/**
 * csmisas_find_vtarget
 *
 * @ioc
 * @volume_id
 * @volume_bus
 *
 **/
अटल VirtTarget *
mptsas_find_vtarget(MPT_ADAPTER *ioc, u8 channel, u8 id)
अणु
	काष्ठा scsi_device 		*sdev;
	VirtDevice			*vdevice;
	VirtTarget 			*vtarget = शून्य;

	shost_क्रम_each_device(sdev, ioc->sh) अणु
		vdevice = sdev->hostdata;
		अगर ((vdevice == शून्य) ||
			(vdevice->vtarget == शून्य))
			जारी;
		अगर ((vdevice->vtarget->tflags &
		    MPT_TARGET_FLAGS_RAID_COMPONENT ||
		    vdevice->vtarget->raidVolume))
			जारी;
		अगर (vdevice->vtarget->id == id &&
			vdevice->vtarget->channel == channel)
			vtarget = vdevice->vtarget;
	पूर्ण
	वापस vtarget;
पूर्ण

अटल व्योम
mptsas_queue_device_delete(MPT_ADAPTER *ioc,
	MpiEventDataSasDeviceStatusChange_t *sas_event_data)
अणु
	काष्ठा fw_event_work *fw_event;

	fw_event = kzalloc(माप(*fw_event) +
			   माप(MpiEventDataSasDeviceStatusChange_t),
			   GFP_ATOMIC);
	अगर (!fw_event) अणु
		prपूर्णांकk(MYIOC_s_WARN_FMT "%s: failed at (line=%d)\n",
		    ioc->name, __func__, __LINE__);
		वापस;
	पूर्ण
	स_नकल(fw_event->event_data, sas_event_data,
	    माप(MpiEventDataSasDeviceStatusChange_t));
	fw_event->event = MPI_EVENT_SAS_DEVICE_STATUS_CHANGE;
	fw_event->ioc = ioc;
	mptsas_add_fw_event(ioc, fw_event, msecs_to_jअगरfies(1));
पूर्ण

अटल व्योम
mptsas_queue_rescan(MPT_ADAPTER *ioc)
अणु
	काष्ठा fw_event_work *fw_event;

	fw_event = kzalloc(माप(*fw_event), GFP_ATOMIC);
	अगर (!fw_event) अणु
		prपूर्णांकk(MYIOC_s_WARN_FMT "%s: failed at (line=%d)\n",
		    ioc->name, __func__, __LINE__);
		वापस;
	पूर्ण
	fw_event->event = -1;
	fw_event->ioc = ioc;
	mptsas_add_fw_event(ioc, fw_event, msecs_to_jअगरfies(1));
पूर्ण


/**
 * mptsas_target_reset
 *
 * Issues TARGET_RESET to end device using handshaking method
 *
 * @ioc
 * @channel
 * @id
 *
 * Returns (1) success
 *         (0) failure
 *
 **/
अटल पूर्णांक
mptsas_target_reset(MPT_ADAPTER *ioc, u8 channel, u8 id)
अणु
	MPT_FRAME_HDR	*mf;
	SCSITaskMgmt_t	*pScsiTm;
	अगर (mpt_set_taskmgmt_in_progress_flag(ioc) != 0)
		वापस 0;


	mf = mpt_get_msg_frame(mptsasDeviceResetCtx, ioc);
	अगर (mf == शून्य) अणु
		dfailprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_WARN_FMT
			"%s, no msg frames @%d!!\n", ioc->name,
			__func__, __LINE__));
		जाओ out_fail;
	पूर्ण

	dपंचांगprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT "TaskMgmt request (mf=%p)\n",
		ioc->name, mf));

	/* Format the Request
	 */
	pScsiTm = (SCSITaskMgmt_t *) mf;
	स_रखो (pScsiTm, 0, माप(SCSITaskMgmt_t));
	pScsiTm->TargetID = id;
	pScsiTm->Bus = channel;
	pScsiTm->Function = MPI_FUNCTION_SCSI_TASK_MGMT;
	pScsiTm->TaskType = MPI_SCSITASKMGMT_TASKTYPE_TARGET_RESET;
	pScsiTm->MsgFlags = MPI_SCSITASKMGMT_MSGFLAGS_LIPRESET_RESET_OPTION;

	DBG_DUMP_TM_REQUEST_FRAME(ioc, (u32 *)mf);

	dपंचांगprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT
	   "TaskMgmt type=%d (sas device delete) fw_channel = %d fw_id = %d)\n",
	   ioc->name, MPI_SCSITASKMGMT_TASKTYPE_TARGET_RESET, channel, id));

	mpt_put_msg_frame_hi_pri(mptsasDeviceResetCtx, ioc, mf);

	वापस 1;

 out_fail:

	mpt_clear_taskmgmt_in_progress_flag(ioc);
	वापस 0;
पूर्ण

अटल व्योम
mptsas_block_io_sdev(काष्ठा scsi_device *sdev, व्योम *data)
अणु
	scsi_device_set_state(sdev, SDEV_BLOCK);
पूर्ण

अटल व्योम
mptsas_block_io_starget(काष्ठा scsi_target *starget)
अणु
	अगर (starget)
		starget_क्रम_each_device(starget, शून्य, mptsas_block_io_sdev);
पूर्ण

/**
 * mptsas_target_reset_queue
 *
 * Receive request क्रम TARGET_RESET after receiving an firmware
 * event NOT_RESPONDING_EVENT, then put command in link list
 * and queue अगर task_queue alपढ़ोy in use.
 *
 * @ioc
 * @sas_event_data
 *
 **/
अटल व्योम
mptsas_target_reset_queue(MPT_ADAPTER *ioc,
    EVENT_DATA_SAS_DEVICE_STATUS_CHANGE *sas_event_data)
अणु
	MPT_SCSI_HOST	*hd = shost_priv(ioc->sh);
	VirtTarget *vtarget = शून्य;
	काष्ठा mptsas_target_reset_event *target_reset_list;
	u8		id, channel;

	id = sas_event_data->TargetID;
	channel = sas_event_data->Bus;

	vtarget = mptsas_find_vtarget(ioc, channel, id);
	अगर (vtarget) अणु
		mptsas_block_io_starget(vtarget->starget);
		vtarget->deleted = 1; /* block IO */
	पूर्ण

	target_reset_list = kzalloc(माप(काष्ठा mptsas_target_reset_event),
	    GFP_ATOMIC);
	अगर (!target_reset_list) अणु
		dfailprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_WARN_FMT
			"%s, failed to allocate mem @%d..!!\n",
			ioc->name, __func__, __LINE__));
		वापस;
	पूर्ण

	स_नकल(&target_reset_list->sas_event_data, sas_event_data,
		माप(*sas_event_data));
	list_add_tail(&target_reset_list->list, &hd->target_reset_list);

	target_reset_list->समय_count = jअगरfies;

	अगर (mptsas_target_reset(ioc, channel, id)) अणु
		target_reset_list->target_reset_issued = 1;
	पूर्ण
पूर्ण

/**
 * mptsas_schedule_target_reset- send pending target reset
 * @iocp: per adapter object
 *
 * This function will delete scheduled target reset from the list and
 * try to send next target reset. This will be called from completion
 * context of any Task management command.
 */

व्योम
mptsas_schedule_target_reset(व्योम *iocp)
अणु
	MPT_ADAPTER *ioc = (MPT_ADAPTER *)(iocp);
	MPT_SCSI_HOST	*hd = shost_priv(ioc->sh);
	काष्ठा list_head *head = &hd->target_reset_list;
	काष्ठा mptsas_target_reset_event	*target_reset_list;
	u8		id, channel;
	/*
	 * issue target reset to next device in the queue
	 */

	अगर (list_empty(head))
		वापस;

	target_reset_list = list_entry(head->next,
		काष्ठा mptsas_target_reset_event, list);

	id = target_reset_list->sas_event_data.TargetID;
	channel = target_reset_list->sas_event_data.Bus;
	target_reset_list->समय_count = jअगरfies;

	अगर (mptsas_target_reset(ioc, channel, id))
		target_reset_list->target_reset_issued = 1;
	वापस;
पूर्ण


/**
 *	mptsas_taskmgmt_complete - complete SAS task management function
 *	@ioc: Poपूर्णांकer to MPT_ADAPTER काष्ठाure
 *
 *	Completion क्रम TARGET_RESET after NOT_RESPONDING_EVENT, enable work
 *	queue to finish off removing device from upper layers. then send next
 *	TARGET_RESET in the queue.
 **/
अटल पूर्णांक
mptsas_taskmgmt_complete(MPT_ADAPTER *ioc, MPT_FRAME_HDR *mf, MPT_FRAME_HDR *mr)
अणु
	MPT_SCSI_HOST	*hd = shost_priv(ioc->sh);
        काष्ठा list_head *head = &hd->target_reset_list;
	u8		id, channel;
	काष्ठा mptsas_target_reset_event	*target_reset_list;
	SCSITaskMgmtReply_t *pScsiTmReply;

	dपंचांगprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT "TaskMgmt completed: "
	    "(mf = %p, mr = %p)\n", ioc->name, mf, mr));

	pScsiTmReply = (SCSITaskMgmtReply_t *)mr;
	अगर (!pScsiTmReply)
		वापस 0;

	dपंचांगprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT
	    "\tTaskMgmt completed: fw_channel = %d, fw_id = %d,\n"
	    "\ttask_type = 0x%02X, iocstatus = 0x%04X "
	    "loginfo = 0x%08X,\n\tresponse_code = 0x%02X, "
	    "term_cmnds = %d\n", ioc->name,
	    pScsiTmReply->Bus, pScsiTmReply->TargetID,
	    pScsiTmReply->TaskType,
	    le16_to_cpu(pScsiTmReply->IOCStatus),
	    le32_to_cpu(pScsiTmReply->IOCLogInfo),
	    pScsiTmReply->ResponseCode,
	    le32_to_cpu(pScsiTmReply->TerminationCount)));

	अगर (pScsiTmReply->ResponseCode)
		mptscsih_taskmgmt_response_code(ioc,
		pScsiTmReply->ResponseCode);

	अगर (pScsiTmReply->TaskType ==
	    MPI_SCSITASKMGMT_TASKTYPE_QUERY_TASK || pScsiTmReply->TaskType ==
	     MPI_SCSITASKMGMT_TASKTYPE_ABRT_TASK_SET) अणु
		ioc->taskmgmt_cmds.status |= MPT_MGMT_STATUS_COMMAND_GOOD;
		ioc->taskmgmt_cmds.status |= MPT_MGMT_STATUS_RF_VALID;
		स_नकल(ioc->taskmgmt_cmds.reply, mr,
		    min(MPT_DEFAULT_FRAME_SIZE, 4 * mr->u.reply.MsgLength));
		अगर (ioc->taskmgmt_cmds.status & MPT_MGMT_STATUS_PENDING) अणु
			ioc->taskmgmt_cmds.status &= ~MPT_MGMT_STATUS_PENDING;
			complete(&ioc->taskmgmt_cmds.करोne);
			वापस 1;
		पूर्ण
		वापस 0;
	पूर्ण

	mpt_clear_taskmgmt_in_progress_flag(ioc);

	अगर (list_empty(head))
		वापस 1;

	target_reset_list = list_entry(head->next,
	    काष्ठा mptsas_target_reset_event, list);

	dपंचांगprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT
	    "TaskMgmt: completed (%d seconds)\n",
	    ioc->name, jअगरfies_to_msecs(jअगरfies -
	    target_reset_list->समय_count)/1000));

	id = pScsiTmReply->TargetID;
	channel = pScsiTmReply->Bus;
	target_reset_list->समय_count = jअगरfies;

	/*
	 * retry target reset
	 */
	अगर (!target_reset_list->target_reset_issued) अणु
		अगर (mptsas_target_reset(ioc, channel, id))
			target_reset_list->target_reset_issued = 1;
		वापस 1;
	पूर्ण

	/*
	 * enable work queue to हटाओ device from upper layers
	 */
	list_del(&target_reset_list->list);
	अगर (!ioc->fw_events_off)
		mptsas_queue_device_delete(ioc,
			&target_reset_list->sas_event_data);


	ioc->schedule_target_reset(ioc);

	वापस 1;
पूर्ण

/**
 * mptscsih_ioc_reset
 *
 * @ioc
 * @reset_phase
 *
 **/
अटल पूर्णांक
mptsas_ioc_reset(MPT_ADAPTER *ioc, पूर्णांक reset_phase)
अणु
	MPT_SCSI_HOST	*hd;
	पूर्णांक rc;

	rc = mptscsih_ioc_reset(ioc, reset_phase);
	अगर ((ioc->bus_type != SAS) || (!rc))
		वापस rc;

	hd = shost_priv(ioc->sh);
	अगर (!hd->ioc)
		जाओ out;

	चयन (reset_phase) अणु
	हाल MPT_IOC_SETUP_RESET:
		dपंचांगprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT
		    "%s: MPT_IOC_SETUP_RESET\n", ioc->name, __func__));
		mptsas_fw_event_off(ioc);
		अवरोध;
	हाल MPT_IOC_PRE_RESET:
		dपंचांगprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT
		    "%s: MPT_IOC_PRE_RESET\n", ioc->name, __func__));
		अवरोध;
	हाल MPT_IOC_POST_RESET:
		dपंचांगprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT
		    "%s: MPT_IOC_POST_RESET\n", ioc->name, __func__));
		अगर (ioc->sas_mgmt.status & MPT_MGMT_STATUS_PENDING) अणु
			ioc->sas_mgmt.status |= MPT_MGMT_STATUS_DID_IOCRESET;
			complete(&ioc->sas_mgmt.करोne);
		पूर्ण
		mptsas_cleanup_fw_event_q(ioc);
		mptsas_queue_rescan(ioc);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

 out:
	वापस rc;
पूर्ण


/**
 * क्रमागत device_state -
 * @DEVICE_RETRY: need to retry the TUR
 * @DEVICE_ERROR: TUR वापस error, करोn't add device
 * @DEVICE_READY: device can be added
 *
 */
क्रमागत device_stateअणु
	DEVICE_RETRY,
	DEVICE_ERROR,
	DEVICE_READY,
पूर्ण;

अटल पूर्णांक
mptsas_sas_enclosure_pg0(MPT_ADAPTER *ioc, काष्ठा mptsas_enclosure *enclosure,
		u32 क्रमm, u32 क्रमm_specअगरic)
अणु
	ConfigExtendedPageHeader_t hdr;
	CONFIGPARMS cfg;
	SasEnclosurePage0_t *buffer;
	dma_addr_t dma_handle;
	पूर्णांक error;
	__le64 le_identअगरier;

	स_रखो(&hdr, 0, माप(hdr));
	hdr.PageVersion = MPI_SASENCLOSURE0_PAGEVERSION;
	hdr.PageNumber = 0;
	hdr.PageType = MPI_CONFIG_PAGETYPE_EXTENDED;
	hdr.ExtPageType = MPI_CONFIG_EXTPAGETYPE_ENCLOSURE;

	cfg.cfghdr.ehdr = &hdr;
	cfg.physAddr = -1;
	cfg.pageAddr = क्रमm + क्रमm_specअगरic;
	cfg.action = MPI_CONFIG_ACTION_PAGE_HEADER;
	cfg.dir = 0;	/* पढ़ो */
	cfg.समयout = SAS_CONFIG_PAGE_TIMEOUT;

	error = mpt_config(ioc, &cfg);
	अगर (error)
		जाओ out;
	अगर (!hdr.ExtPageLength) अणु
		error = -ENXIO;
		जाओ out;
	पूर्ण

	buffer = pci_alloc_consistent(ioc->pcidev, hdr.ExtPageLength * 4,
			&dma_handle);
	अगर (!buffer) अणु
		error = -ENOMEM;
		जाओ out;
	पूर्ण

	cfg.physAddr = dma_handle;
	cfg.action = MPI_CONFIG_ACTION_PAGE_READ_CURRENT;

	error = mpt_config(ioc, &cfg);
	अगर (error)
		जाओ out_मुक्त_consistent;

	/* save config data */
	स_नकल(&le_identअगरier, &buffer->EnclosureLogicalID, माप(__le64));
	enclosure->enclosure_logical_id = le64_to_cpu(le_identअगरier);
	enclosure->enclosure_handle = le16_to_cpu(buffer->EnclosureHandle);
	enclosure->flags = le16_to_cpu(buffer->Flags);
	enclosure->num_slot = le16_to_cpu(buffer->NumSlots);
	enclosure->start_slot = le16_to_cpu(buffer->StartSlot);
	enclosure->start_id = buffer->StartTargetID;
	enclosure->start_channel = buffer->StartBus;
	enclosure->sep_id = buffer->SEPTargetID;
	enclosure->sep_channel = buffer->SEPBus;

 out_मुक्त_consistent:
	pci_मुक्त_consistent(ioc->pcidev, hdr.ExtPageLength * 4,
			    buffer, dma_handle);
 out:
	वापस error;
पूर्ण

/**
 *	mptsas_add_end_device - report a new end device to sas transport layer
 *	@ioc: Poपूर्णांकer to MPT_ADAPTER काष्ठाure
 *	@phy_info: describes attached device
 *
 *	वापस (0) success (1) failure
 *
 **/
अटल पूर्णांक
mptsas_add_end_device(MPT_ADAPTER *ioc, काष्ठा mptsas_phyinfo *phy_info)
अणु
	काष्ठा sas_rphy *rphy;
	काष्ठा sas_port *port;
	काष्ठा sas_identअगरy identअगरy;
	अक्षर *ds = शून्य;
	u8 fw_id;

	अगर (!phy_info) अणु
		dfailprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_ERR_FMT
			"%s: exit at line=%d\n", ioc->name,
			 __func__, __LINE__));
		वापस 1;
	पूर्ण

	fw_id = phy_info->attached.id;

	अगर (mptsas_get_rphy(phy_info)) अणु
		dfailprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_ERR_FMT
			"%s: fw_id=%d exit at line=%d\n", ioc->name,
			 __func__, fw_id, __LINE__));
		वापस 2;
	पूर्ण

	port = mptsas_get_port(phy_info);
	अगर (!port) अणु
		dfailprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_ERR_FMT
			"%s: fw_id=%d exit at line=%d\n", ioc->name,
			 __func__, fw_id, __LINE__));
		वापस 3;
	पूर्ण

	अगर (phy_info->attached.device_info &
	    MPI_SAS_DEVICE_INFO_SSP_TARGET)
		ds = "ssp";
	अगर (phy_info->attached.device_info &
	    MPI_SAS_DEVICE_INFO_STP_TARGET)
		ds = "stp";
	अगर (phy_info->attached.device_info &
	    MPI_SAS_DEVICE_INFO_SATA_DEVICE)
		ds = "sata";

	prपूर्णांकk(MYIOC_s_INFO_FMT "attaching %s device: fw_channel %d, fw_id %d,"
	    " phy %d, sas_addr 0x%llx\n", ioc->name, ds,
	    phy_info->attached.channel, phy_info->attached.id,
	    phy_info->attached.phy_id, (अचिन्हित दीर्घ दीर्घ)
	    phy_info->attached.sas_address);

	mptsas_parse_device_info(&identअगरy, &phy_info->attached);
	rphy = sas_end_device_alloc(port);
	अगर (!rphy) अणु
		dfailprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_ERR_FMT
			"%s: fw_id=%d exit at line=%d\n", ioc->name,
			 __func__, fw_id, __LINE__));
		वापस 5; /* non-fatal: an rphy can be added later */
	पूर्ण

	rphy->identअगरy = identअगरy;
	अगर (sas_rphy_add(rphy)) अणु
		dfailprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_ERR_FMT
			"%s: fw_id=%d exit at line=%d\n", ioc->name,
			 __func__, fw_id, __LINE__));
		sas_rphy_मुक्त(rphy);
		वापस 6;
	पूर्ण
	mptsas_set_rphy(ioc, phy_info, rphy);
	वापस 0;
पूर्ण

/**
 *	mptsas_del_end_device - report a deleted end device to sas transport layer
 *	@ioc: Poपूर्णांकer to MPT_ADAPTER काष्ठाure
 *	@phy_info: describes attached device
 *
 **/
अटल व्योम
mptsas_del_end_device(MPT_ADAPTER *ioc, काष्ठा mptsas_phyinfo *phy_info)
अणु
	काष्ठा sas_rphy *rphy;
	काष्ठा sas_port *port;
	काष्ठा mptsas_portinfo *port_info;
	काष्ठा mptsas_phyinfo *phy_info_parent;
	पूर्णांक i;
	अक्षर *ds = शून्य;
	u8 fw_id;
	u64 sas_address;

	अगर (!phy_info)
		वापस;

	fw_id = phy_info->attached.id;
	sas_address = phy_info->attached.sas_address;

	अगर (!phy_info->port_details) अणु
		dfailprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_ERR_FMT
			"%s: fw_id=%d exit at line=%d\n", ioc->name,
			 __func__, fw_id, __LINE__));
		वापस;
	पूर्ण
	rphy = mptsas_get_rphy(phy_info);
	अगर (!rphy) अणु
		dfailprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_ERR_FMT
			"%s: fw_id=%d exit at line=%d\n", ioc->name,
			 __func__, fw_id, __LINE__));
		वापस;
	पूर्ण

	अगर (phy_info->attached.device_info & MPI_SAS_DEVICE_INFO_SSP_INITIATOR
		|| phy_info->attached.device_info
			& MPI_SAS_DEVICE_INFO_SMP_INITIATOR
		|| phy_info->attached.device_info
			& MPI_SAS_DEVICE_INFO_STP_INITIATOR)
		ds = "initiator";
	अगर (phy_info->attached.device_info &
	    MPI_SAS_DEVICE_INFO_SSP_TARGET)
		ds = "ssp";
	अगर (phy_info->attached.device_info &
	    MPI_SAS_DEVICE_INFO_STP_TARGET)
		ds = "stp";
	अगर (phy_info->attached.device_info &
	    MPI_SAS_DEVICE_INFO_SATA_DEVICE)
		ds = "sata";

	dev_prपूर्णांकk(KERN_DEBUG, &rphy->dev, MYIOC_s_FMT
	    "removing %s device: fw_channel %d, fw_id %d, phy %d,"
	    "sas_addr 0x%llx\n", ioc->name, ds, phy_info->attached.channel,
	    phy_info->attached.id, phy_info->attached.phy_id,
	    (अचिन्हित दीर्घ दीर्घ) sas_address);

	port = mptsas_get_port(phy_info);
	अगर (!port) अणु
		dfailprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_ERR_FMT
			"%s: fw_id=%d exit at line=%d\n", ioc->name,
			 __func__, fw_id, __LINE__));
		वापस;
	पूर्ण
	port_info = phy_info->portinfo;
	phy_info_parent = port_info->phy_info;
	क्रम (i = 0; i < port_info->num_phys; i++, phy_info_parent++) अणु
		अगर (!phy_info_parent->phy)
			जारी;
		अगर (phy_info_parent->attached.sas_address !=
		    sas_address)
			जारी;
		dev_prपूर्णांकk(KERN_DEBUG, &phy_info_parent->phy->dev,
		    MYIOC_s_FMT "delete phy %d, phy-obj (0x%p)\n",
		    ioc->name, phy_info_parent->phy_id,
		    phy_info_parent->phy);
		sas_port_delete_phy(port, phy_info_parent->phy);
	पूर्ण

	dev_prपूर्णांकk(KERN_DEBUG, &port->dev, MYIOC_s_FMT
	    "delete port %d, sas_addr (0x%llx)\n", ioc->name,
	     port->port_identअगरier, (अचिन्हित दीर्घ दीर्घ)sas_address);
	sas_port_delete(port);
	mptsas_set_port(ioc, phy_info, शून्य);
	mptsas_port_delete(ioc, phy_info->port_details);
पूर्ण

अटल काष्ठा mptsas_phyinfo *
mptsas_refreshing_device_handles(MPT_ADAPTER *ioc,
	काष्ठा mptsas_devinfo *sas_device)
अणु
	काष्ठा mptsas_phyinfo *phy_info;
	काष्ठा mptsas_portinfo *port_info;
	पूर्णांक i;

	phy_info = mptsas_find_phyinfo_by_sas_address(ioc,
	    sas_device->sas_address);
	अगर (!phy_info)
		जाओ out;
	port_info = phy_info->portinfo;
	अगर (!port_info)
		जाओ out;
	mutex_lock(&ioc->sas_topology_mutex);
	क्रम (i = 0; i < port_info->num_phys; i++) अणु
		अगर (port_info->phy_info[i].attached.sas_address !=
			sas_device->sas_address)
			जारी;
		port_info->phy_info[i].attached.channel = sas_device->channel;
		port_info->phy_info[i].attached.id = sas_device->id;
		port_info->phy_info[i].attached.sas_address =
		    sas_device->sas_address;
		port_info->phy_info[i].attached.handle = sas_device->handle;
		port_info->phy_info[i].attached.handle_parent =
		    sas_device->handle_parent;
		port_info->phy_info[i].attached.handle_enclosure =
		    sas_device->handle_enclosure;
	पूर्ण
	mutex_unlock(&ioc->sas_topology_mutex);
 out:
	वापस phy_info;
पूर्ण

/**
 * mptsas_firmware_event_work - work thपढ़ो क्रम processing fw events
 * @work: work queue payload containing info describing the event
 * Context: user
 *
 */
अटल व्योम
mptsas_firmware_event_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा fw_event_work *fw_event =
		container_of(work, काष्ठा fw_event_work, work.work);
	MPT_ADAPTER *ioc = fw_event->ioc;

	/* special rescan topology handling */
	अगर (fw_event->event == -1) अणु
		अगर (ioc->in_rescan) अणु
			devtprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT
				"%s: rescan ignored as it is in progress\n",
				ioc->name, __func__));
			वापस;
		पूर्ण
		devtprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT "%s: rescan after "
		    "reset\n", ioc->name, __func__));
		ioc->in_rescan = 1;
		mptsas_not_responding_devices(ioc);
		mptsas_scan_sas_topology(ioc);
		ioc->in_rescan = 0;
		mptsas_मुक्त_fw_event(ioc, fw_event);
		mptsas_fw_event_on(ioc);
		वापस;
	पूर्ण

	/* events handling turned off during host reset */
	अगर (ioc->fw_events_off) अणु
		mptsas_मुक्त_fw_event(ioc, fw_event);
		वापस;
	पूर्ण

	devtprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT "%s: fw_event=(0x%p), "
	    "event = (0x%02x)\n", ioc->name, __func__, fw_event,
	    (fw_event->event & 0xFF)));

	चयन (fw_event->event) अणु
	हाल MPI_EVENT_SAS_DEVICE_STATUS_CHANGE:
		mptsas_send_sas_event(fw_event);
		अवरोध;
	हाल MPI_EVENT_INTEGRATED_RAID:
		mptsas_send_raid_event(fw_event);
		अवरोध;
	हाल MPI_EVENT_IR2:
		mptsas_send_ir2_event(fw_event);
		अवरोध;
	हाल MPI_EVENT_PERSISTENT_TABLE_FULL:
		mptbase_sas_persist_operation(ioc,
		    MPI_SAS_OP_CLEAR_NOT_PRESENT);
		mptsas_मुक्त_fw_event(ioc, fw_event);
		अवरोध;
	हाल MPI_EVENT_SAS_BROADCAST_PRIMITIVE:
		mptsas_broadcast_primitive_work(fw_event);
		अवरोध;
	हाल MPI_EVENT_SAS_EXPANDER_STATUS_CHANGE:
		mptsas_send_expander_event(fw_event);
		अवरोध;
	हाल MPI_EVENT_SAS_PHY_LINK_STATUS:
		mptsas_send_link_status_event(fw_event);
		अवरोध;
	हाल MPI_EVENT_QUEUE_FULL:
		mptsas_handle_queue_full_event(fw_event);
		अवरोध;
	पूर्ण
पूर्ण



अटल पूर्णांक
mptsas_slave_configure(काष्ठा scsi_device *sdev)
अणु
	काष्ठा Scsi_Host	*host = sdev->host;
	MPT_SCSI_HOST	*hd = shost_priv(host);
	MPT_ADAPTER	*ioc = hd->ioc;
	VirtDevice	*vdevice = sdev->hostdata;

	अगर (vdevice->vtarget->deleted) अणु
		sdev_prपूर्णांकk(KERN_INFO, sdev, "clearing deleted flag\n");
		vdevice->vtarget->deleted = 0;
	पूर्ण

	/*
	 * RAID volumes placed beyond the last expected port.
	 * Ignore sending sas mode pages in that हाल..
	 */
	अगर (sdev->channel == MPTSAS_RAID_CHANNEL) अणु
		mptsas_add_device_component_starget_ir(ioc, scsi_target(sdev));
		जाओ out;
	पूर्ण

	sas_पढ़ो_port_mode_page(sdev);

	mptsas_add_device_component_starget(ioc, scsi_target(sdev));

 out:
	वापस mptscsih_slave_configure(sdev);
पूर्ण

अटल पूर्णांक
mptsas_target_alloc(काष्ठा scsi_target *starget)
अणु
	काष्ठा Scsi_Host *host = dev_to_shost(&starget->dev);
	MPT_SCSI_HOST		*hd = shost_priv(host);
	VirtTarget		*vtarget;
	u8			id, channel;
	काष्ठा sas_rphy		*rphy;
	काष्ठा mptsas_portinfo	*p;
	पूर्णांक 			 i;
	MPT_ADAPTER		*ioc = hd->ioc;

	vtarget = kzalloc(माप(VirtTarget), GFP_KERNEL);
	अगर (!vtarget)
		वापस -ENOMEM;

	vtarget->starget = starget;
	vtarget->ioc_id = ioc->id;
	vtarget->tflags = MPT_TARGET_FLAGS_Q_YES;
	id = starget->id;
	channel = 0;

	/*
	 * RAID volumes placed beyond the last expected port.
	 */
	अगर (starget->channel == MPTSAS_RAID_CHANNEL) अणु
		अगर (!ioc->raid_data.pIocPg2) अणु
			kमुक्त(vtarget);
			वापस -ENXIO;
		पूर्ण
		क्रम (i = 0; i < ioc->raid_data.pIocPg2->NumActiveVolumes; i++) अणु
			अगर (id == ioc->raid_data.pIocPg2->
					RaidVolume[i].VolumeID) अणु
				channel = ioc->raid_data.pIocPg2->
					RaidVolume[i].VolumeBus;
			पूर्ण
		पूर्ण
		vtarget->raidVolume = 1;
		जाओ out;
	पूर्ण

	rphy = dev_to_rphy(starget->dev.parent);
	mutex_lock(&ioc->sas_topology_mutex);
	list_क्रम_each_entry(p, &ioc->sas_topology, list) अणु
		क्रम (i = 0; i < p->num_phys; i++) अणु
			अगर (p->phy_info[i].attached.sas_address !=
					rphy->identअगरy.sas_address)
				जारी;
			id = p->phy_info[i].attached.id;
			channel = p->phy_info[i].attached.channel;
			mptsas_set_starget(&p->phy_info[i], starget);

			/*
			 * Exposing hidden raid components
			 */
			अगर (mptscsih_is_phys_disk(ioc, channel, id)) अणु
				id = mptscsih_raid_id_to_num(ioc,
						channel, id);
				vtarget->tflags |=
				    MPT_TARGET_FLAGS_RAID_COMPONENT;
				p->phy_info[i].attached.phys_disk_num = id;
			पूर्ण
			mutex_unlock(&ioc->sas_topology_mutex);
			जाओ out;
		पूर्ण
	पूर्ण
	mutex_unlock(&ioc->sas_topology_mutex);

	kमुक्त(vtarget);
	वापस -ENXIO;

 out:
	vtarget->id = id;
	vtarget->channel = channel;
	starget->hostdata = vtarget;
	वापस 0;
पूर्ण

अटल व्योम
mptsas_target_destroy(काष्ठा scsi_target *starget)
अणु
	काष्ठा Scsi_Host *host = dev_to_shost(&starget->dev);
	MPT_SCSI_HOST		*hd = shost_priv(host);
	काष्ठा sas_rphy		*rphy;
	काष्ठा mptsas_portinfo	*p;
	पूर्णांक 			 i;
	MPT_ADAPTER	*ioc = hd->ioc;
	VirtTarget	*vtarget;

	अगर (!starget->hostdata)
		वापस;

	vtarget = starget->hostdata;

	mptsas_del_device_component_by_os(ioc, starget->channel,
	    starget->id);


	अगर (starget->channel == MPTSAS_RAID_CHANNEL)
		जाओ out;

	rphy = dev_to_rphy(starget->dev.parent);
	list_क्रम_each_entry(p, &ioc->sas_topology, list) अणु
		क्रम (i = 0; i < p->num_phys; i++) अणु
			अगर (p->phy_info[i].attached.sas_address !=
					rphy->identअगरy.sas_address)
				जारी;

			starget_prपूर्णांकk(KERN_INFO, starget, MYIOC_s_FMT
			"delete device: fw_channel %d, fw_id %d, phy %d, "
			"sas_addr 0x%llx\n", ioc->name,
			p->phy_info[i].attached.channel,
			p->phy_info[i].attached.id,
			p->phy_info[i].attached.phy_id, (अचिन्हित दीर्घ दीर्घ)
			p->phy_info[i].attached.sas_address);

			mptsas_set_starget(&p->phy_info[i], शून्य);
		पूर्ण
	पूर्ण

 out:
	vtarget->starget = शून्य;
	kमुक्त(starget->hostdata);
	starget->hostdata = शून्य;
पूर्ण


अटल पूर्णांक
mptsas_slave_alloc(काष्ठा scsi_device *sdev)
अणु
	काष्ठा Scsi_Host	*host = sdev->host;
	MPT_SCSI_HOST		*hd = shost_priv(host);
	काष्ठा sas_rphy		*rphy;
	काष्ठा mptsas_portinfo	*p;
	VirtDevice		*vdevice;
	काष्ठा scsi_target 	*starget;
	पूर्णांक 			i;
	MPT_ADAPTER *ioc = hd->ioc;

	vdevice = kzalloc(माप(VirtDevice), GFP_KERNEL);
	अगर (!vdevice) अणु
		prपूर्णांकk(MYIOC_s_ERR_FMT "slave_alloc kzalloc(%zd) FAILED!\n",
				ioc->name, माप(VirtDevice));
		वापस -ENOMEM;
	पूर्ण
	starget = scsi_target(sdev);
	vdevice->vtarget = starget->hostdata;

	अगर (sdev->channel == MPTSAS_RAID_CHANNEL)
		जाओ out;

	rphy = dev_to_rphy(sdev->sdev_target->dev.parent);
	mutex_lock(&ioc->sas_topology_mutex);
	list_क्रम_each_entry(p, &ioc->sas_topology, list) अणु
		क्रम (i = 0; i < p->num_phys; i++) अणु
			अगर (p->phy_info[i].attached.sas_address !=
					rphy->identअगरy.sas_address)
				जारी;
			vdevice->lun = sdev->lun;
			/*
			 * Exposing hidden raid components
			 */
			अगर (mptscsih_is_phys_disk(ioc,
			    p->phy_info[i].attached.channel,
			    p->phy_info[i].attached.id))
				sdev->no_uld_attach = 1;
			mutex_unlock(&ioc->sas_topology_mutex);
			जाओ out;
		पूर्ण
	पूर्ण
	mutex_unlock(&ioc->sas_topology_mutex);

	kमुक्त(vdevice);
	वापस -ENXIO;

 out:
	vdevice->vtarget->num_luns++;
	sdev->hostdata = vdevice;
	वापस 0;
पूर्ण

अटल पूर्णांक
mptsas_qcmd(काष्ठा Scsi_Host *shost, काष्ठा scsi_cmnd *SCpnt)
अणु
	MPT_SCSI_HOST	*hd;
	MPT_ADAPTER	*ioc;
	VirtDevice	*vdevice = SCpnt->device->hostdata;

	अगर (!vdevice || !vdevice->vtarget || vdevice->vtarget->deleted) अणु
		SCpnt->result = DID_NO_CONNECT << 16;
		SCpnt->scsi_करोne(SCpnt);
		वापस 0;
	पूर्ण

	hd = shost_priv(shost);
	ioc = hd->ioc;

	अगर (ioc->sas_discovery_quiesce_io)
		वापस SCSI_MLQUEUE_HOST_BUSY;

	अगर (ioc->debug_level & MPT_DEBUG_SCSI)
		scsi_prपूर्णांक_command(SCpnt);

	वापस mptscsih_qcmd(SCpnt);
पूर्ण

/**
 *	mptsas_mptsas_eh_समयd_out - resets the scsi_cmnd समयout
 *		अगर the device under question is currently in the
 *		device removal delay.
 *	@sc: scsi command that the midlayer is about to समय out
 *
 **/
अटल क्रमागत blk_eh_समयr_वापस mptsas_eh_समयd_out(काष्ठा scsi_cmnd *sc)
अणु
	MPT_SCSI_HOST *hd;
	MPT_ADAPTER   *ioc;
	VirtDevice    *vdevice;
	क्रमागत blk_eh_समयr_वापस rc = BLK_EH_DONE;

	hd = shost_priv(sc->device->host);
	अगर (hd == शून्य) अणु
		prपूर्णांकk(KERN_ERR MYNAM ": %s: Can't locate host! (sc=%p)\n",
		    __func__, sc);
		जाओ करोne;
	पूर्ण

	ioc = hd->ioc;
	अगर (ioc->bus_type != SAS) अणु
		prपूर्णांकk(KERN_ERR MYNAM ": %s: Wrong bus type (sc=%p)\n",
		    __func__, sc);
		जाओ करोne;
	पूर्ण

	/* In हाल अगर IOC is in reset from पूर्णांकernal context.
	*  Do not execute EEH क्रम the same IOC. SML should to reset समयr.
	*/
	अगर (ioc->ioc_reset_in_progress) अणु
		dपंचांगprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_WARN_FMT ": %s: ioc is in reset,"
		    "SML need to reset the timer (sc=%p)\n",
		    ioc->name, __func__, sc));
		rc = BLK_EH_RESET_TIMER;
	पूर्ण
	vdevice = sc->device->hostdata;
	अगर (vdevice && vdevice->vtarget && (vdevice->vtarget->inDMD
		|| vdevice->vtarget->deleted)) अणु
		dपंचांगprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_WARN_FMT ": %s: target removed "
		    "or in device removal delay (sc=%p)\n",
		    ioc->name, __func__, sc));
		rc = BLK_EH_RESET_TIMER;
		जाओ करोne;
	पूर्ण

करोne:
	वापस rc;
पूर्ण


अटल काष्ठा scsi_host_ढाँचा mptsas_driver_ढाँचा = अणु
	.module				= THIS_MODULE,
	.proc_name			= "mptsas",
	.show_info			= mptscsih_show_info,
	.name				= "MPT SAS Host",
	.info				= mptscsih_info,
	.queuecommand			= mptsas_qcmd,
	.target_alloc			= mptsas_target_alloc,
	.slave_alloc			= mptsas_slave_alloc,
	.slave_configure		= mptsas_slave_configure,
	.target_destroy			= mptsas_target_destroy,
	.slave_destroy			= mptscsih_slave_destroy,
	.change_queue_depth 		= mptscsih_change_queue_depth,
	.eh_समयd_out			= mptsas_eh_समयd_out,
	.eh_पात_handler		= mptscsih_पात,
	.eh_device_reset_handler	= mptscsih_dev_reset,
	.eh_host_reset_handler		= mptscsih_host_reset,
	.bios_param			= mptscsih_bios_param,
	.can_queue			= MPT_SAS_CAN_QUEUE,
	.this_id			= -1,
	.sg_tablesize			= MPT_SCSI_SG_DEPTH,
	.max_sectors			= 8192,
	.cmd_per_lun			= 7,
	.shost_attrs			= mptscsih_host_attrs,
	.no_ग_लिखो_same			= 1,
पूर्ण;

अटल पूर्णांक mptsas_get_linkerrors(काष्ठा sas_phy *phy)
अणु
	MPT_ADAPTER *ioc = phy_to_ioc(phy);
	ConfigExtendedPageHeader_t hdr;
	CONFIGPARMS cfg;
	SasPhyPage1_t *buffer;
	dma_addr_t dma_handle;
	पूर्णांक error;

	/* FIXME: only have link errors on local phys */
	अगर (!scsi_is_sas_phy_local(phy))
		वापस -EINVAL;

	hdr.PageVersion = MPI_SASPHY1_PAGEVERSION;
	hdr.ExtPageLength = 0;
	hdr.PageNumber = 1 /* page number 1*/;
	hdr.Reserved1 = 0;
	hdr.Reserved2 = 0;
	hdr.PageType = MPI_CONFIG_PAGETYPE_EXTENDED;
	hdr.ExtPageType = MPI_CONFIG_EXTPAGETYPE_SAS_PHY;

	cfg.cfghdr.ehdr = &hdr;
	cfg.physAddr = -1;
	cfg.pageAddr = phy->identअगरy.phy_identअगरier;
	cfg.action = MPI_CONFIG_ACTION_PAGE_HEADER;
	cfg.dir = 0;    /* पढ़ो */
	cfg.समयout = SAS_CONFIG_PAGE_TIMEOUT;

	error = mpt_config(ioc, &cfg);
	अगर (error)
		वापस error;
	अगर (!hdr.ExtPageLength)
		वापस -ENXIO;

	buffer = pci_alloc_consistent(ioc->pcidev, hdr.ExtPageLength * 4,
				      &dma_handle);
	अगर (!buffer)
		वापस -ENOMEM;

	cfg.physAddr = dma_handle;
	cfg.action = MPI_CONFIG_ACTION_PAGE_READ_CURRENT;

	error = mpt_config(ioc, &cfg);
	अगर (error)
		जाओ out_मुक्त_consistent;

	mptsas_prपूर्णांक_phy_pg1(ioc, buffer);

	phy->invalid_dword_count = le32_to_cpu(buffer->InvalidDwordCount);
	phy->running_disparity_error_count =
		le32_to_cpu(buffer->RunningDisparityErrorCount);
	phy->loss_of_dword_sync_count =
		le32_to_cpu(buffer->LossDwordSynchCount);
	phy->phy_reset_problem_count =
		le32_to_cpu(buffer->PhyResetProblemCount);

 out_मुक्त_consistent:
	pci_मुक्त_consistent(ioc->pcidev, hdr.ExtPageLength * 4,
			    buffer, dma_handle);
	वापस error;
पूर्ण

अटल पूर्णांक mptsas_mgmt_करोne(MPT_ADAPTER *ioc, MPT_FRAME_HDR *req,
		MPT_FRAME_HDR *reply)
अणु
	ioc->sas_mgmt.status |= MPT_MGMT_STATUS_COMMAND_GOOD;
	अगर (reply != शून्य) अणु
		ioc->sas_mgmt.status |= MPT_MGMT_STATUS_RF_VALID;
		स_नकल(ioc->sas_mgmt.reply, reply,
		    min(ioc->reply_sz, 4 * reply->u.reply.MsgLength));
	पूर्ण

	अगर (ioc->sas_mgmt.status & MPT_MGMT_STATUS_PENDING) अणु
		ioc->sas_mgmt.status &= ~MPT_MGMT_STATUS_PENDING;
		complete(&ioc->sas_mgmt.करोne);
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक mptsas_phy_reset(काष्ठा sas_phy *phy, पूर्णांक hard_reset)
अणु
	MPT_ADAPTER *ioc = phy_to_ioc(phy);
	SasIoUnitControlRequest_t *req;
	SasIoUnitControlReply_t *reply;
	MPT_FRAME_HDR *mf;
	MPIHeader_t *hdr;
	अचिन्हित दीर्घ समयleft;
	पूर्णांक error = -ERESTARTSYS;

	/* FIXME: fusion करोesn't allow non-local phy reset */
	अगर (!scsi_is_sas_phy_local(phy))
		वापस -EINVAL;

	/* not implemented क्रम expanders */
	अगर (phy->identअगरy.target_port_protocols & SAS_PROTOCOL_SMP)
		वापस -ENXIO;

	अगर (mutex_lock_पूर्णांकerruptible(&ioc->sas_mgmt.mutex))
		जाओ out;

	mf = mpt_get_msg_frame(mptsasMgmtCtx, ioc);
	अगर (!mf) अणु
		error = -ENOMEM;
		जाओ out_unlock;
	पूर्ण

	hdr = (MPIHeader_t *) mf;
	req = (SasIoUnitControlRequest_t *)mf;
	स_रखो(req, 0, माप(SasIoUnitControlRequest_t));
	req->Function = MPI_FUNCTION_SAS_IO_UNIT_CONTROL;
	req->MsgContext = hdr->MsgContext;
	req->Operation = hard_reset ?
		MPI_SAS_OP_PHY_HARD_RESET : MPI_SAS_OP_PHY_LINK_RESET;
	req->PhyNum = phy->identअगरy.phy_identअगरier;

	INITIALIZE_MGMT_STATUS(ioc->sas_mgmt.status)
	mpt_put_msg_frame(mptsasMgmtCtx, ioc, mf);

	समयleft = रुको_क्रम_completion_समयout(&ioc->sas_mgmt.करोne,
			10 * HZ);
	अगर (!(ioc->sas_mgmt.status & MPT_MGMT_STATUS_COMMAND_GOOD)) अणु
		error = -ETIME;
		mpt_मुक्त_msg_frame(ioc, mf);
		अगर (ioc->sas_mgmt.status & MPT_MGMT_STATUS_DID_IOCRESET)
			जाओ out_unlock;
		अगर (!समयleft)
			mpt_Soft_Hard_ResetHandler(ioc, CAN_SLEEP);
		जाओ out_unlock;
	पूर्ण

	/* a reply frame is expected */
	अगर ((ioc->sas_mgmt.status &
	    MPT_MGMT_STATUS_RF_VALID) == 0) अणु
		error = -ENXIO;
		जाओ out_unlock;
	पूर्ण

	/* process the completed Reply Message Frame */
	reply = (SasIoUnitControlReply_t *)ioc->sas_mgmt.reply;
	अगर (reply->IOCStatus != MPI_IOCSTATUS_SUCCESS) अणु
		prपूर्णांकk(MYIOC_s_INFO_FMT "%s: IOCStatus=0x%X IOCLogInfo=0x%X\n",
		    ioc->name, __func__, reply->IOCStatus, reply->IOCLogInfo);
		error = -ENXIO;
		जाओ out_unlock;
	पूर्ण

	error = 0;

 out_unlock:
	CLEAR_MGMT_STATUS(ioc->sas_mgmt.status)
	mutex_unlock(&ioc->sas_mgmt.mutex);
 out:
	वापस error;
पूर्ण

अटल पूर्णांक
mptsas_get_enclosure_identअगरier(काष्ठा sas_rphy *rphy, u64 *identअगरier)
अणु
	MPT_ADAPTER *ioc = rphy_to_ioc(rphy);
	पूर्णांक i, error;
	काष्ठा mptsas_portinfo *p;
	काष्ठा mptsas_enclosure enclosure_info;
	u64 enclosure_handle;

	mutex_lock(&ioc->sas_topology_mutex);
	list_क्रम_each_entry(p, &ioc->sas_topology, list) अणु
		क्रम (i = 0; i < p->num_phys; i++) अणु
			अगर (p->phy_info[i].attached.sas_address ==
			    rphy->identअगरy.sas_address) अणु
				enclosure_handle = p->phy_info[i].
					attached.handle_enclosure;
				जाओ found_info;
			पूर्ण
		पूर्ण
	पूर्ण
	mutex_unlock(&ioc->sas_topology_mutex);
	वापस -ENXIO;

 found_info:
	mutex_unlock(&ioc->sas_topology_mutex);
	स_रखो(&enclosure_info, 0, माप(काष्ठा mptsas_enclosure));
	error = mptsas_sas_enclosure_pg0(ioc, &enclosure_info,
			(MPI_SAS_ENCLOS_PGAD_FORM_HANDLE <<
			 MPI_SAS_ENCLOS_PGAD_FORM_SHIFT), enclosure_handle);
	अगर (!error)
		*identअगरier = enclosure_info.enclosure_logical_id;
	वापस error;
पूर्ण

अटल पूर्णांक
mptsas_get_bay_identअगरier(काष्ठा sas_rphy *rphy)
अणु
	MPT_ADAPTER *ioc = rphy_to_ioc(rphy);
	काष्ठा mptsas_portinfo *p;
	पूर्णांक i, rc;

	mutex_lock(&ioc->sas_topology_mutex);
	list_क्रम_each_entry(p, &ioc->sas_topology, list) अणु
		क्रम (i = 0; i < p->num_phys; i++) अणु
			अगर (p->phy_info[i].attached.sas_address ==
			    rphy->identअगरy.sas_address) अणु
				rc = p->phy_info[i].attached.slot;
				जाओ out;
			पूर्ण
		पूर्ण
	पूर्ण
	rc = -ENXIO;
 out:
	mutex_unlock(&ioc->sas_topology_mutex);
	वापस rc;
पूर्ण

अटल व्योम mptsas_smp_handler(काष्ठा bsg_job *job, काष्ठा Scsi_Host *shost,
		काष्ठा sas_rphy *rphy)
अणु
	MPT_ADAPTER *ioc = ((MPT_SCSI_HOST *) shost->hostdata)->ioc;
	MPT_FRAME_HDR *mf;
	SmpPassthroughRequest_t *smpreq;
	पूर्णांक flagsLength;
	अचिन्हित दीर्घ समयleft;
	अक्षर *psge;
	u64 sas_address = 0;
	अचिन्हित पूर्णांक reslen = 0;
	पूर्णांक ret = -EINVAL;

	/* करो we need to support multiple segments? */
	अगर (job->request_payload.sg_cnt > 1 ||
	    job->reply_payload.sg_cnt > 1) अणु
		prपूर्णांकk(MYIOC_s_ERR_FMT "%s: multiple segments req %u, rsp %u\n",
		    ioc->name, __func__, job->request_payload.payload_len,
		    job->reply_payload.payload_len);
		जाओ out;
	पूर्ण

	ret = mutex_lock_पूर्णांकerruptible(&ioc->sas_mgmt.mutex);
	अगर (ret)
		जाओ out;

	mf = mpt_get_msg_frame(mptsasMgmtCtx, ioc);
	अगर (!mf) अणु
		ret = -ENOMEM;
		जाओ out_unlock;
	पूर्ण

	smpreq = (SmpPassthroughRequest_t *)mf;
	स_रखो(smpreq, 0, माप(*smpreq));

	smpreq->RequestDataLength =
		cpu_to_le16(job->request_payload.payload_len - 4);
	smpreq->Function = MPI_FUNCTION_SMP_PASSTHROUGH;

	अगर (rphy)
		sas_address = rphy->identअगरy.sas_address;
	अन्यथा अणु
		काष्ठा mptsas_portinfo *port_info;

		mutex_lock(&ioc->sas_topology_mutex);
		port_info = ioc->hba_port_info;
		अगर (port_info && port_info->phy_info)
			sas_address =
				port_info->phy_info[0].phy->identअगरy.sas_address;
		mutex_unlock(&ioc->sas_topology_mutex);
	पूर्ण

	*((u64 *)&smpreq->SASAddress) = cpu_to_le64(sas_address);

	psge = (अक्षर *)
		(((पूर्णांक *) mf) + (दुरत्व(SmpPassthroughRequest_t, SGL) / 4));

	/* request */
	flagsLength = (MPI_SGE_FLAGS_SIMPLE_ELEMENT |
		       MPI_SGE_FLAGS_END_OF_BUFFER |
		       MPI_SGE_FLAGS_सूचीECTION)
		       << MPI_SGE_FLAGS_SHIFT;

	अगर (!dma_map_sg(&ioc->pcidev->dev, job->request_payload.sg_list,
			1, PCI_DMA_BIसूचीECTIONAL))
		जाओ put_mf;

	flagsLength |= (sg_dma_len(job->request_payload.sg_list) - 4);
	ioc->add_sge(psge, flagsLength,
			sg_dma_address(job->request_payload.sg_list));
	psge += ioc->SGE_size;

	/* response */
	flagsLength = MPI_SGE_FLAGS_SIMPLE_ELEMENT |
		MPI_SGE_FLAGS_SYSTEM_ADDRESS |
		MPI_SGE_FLAGS_IOC_TO_HOST |
		MPI_SGE_FLAGS_END_OF_BUFFER;

	flagsLength = flagsLength << MPI_SGE_FLAGS_SHIFT;

	अगर (!dma_map_sg(&ioc->pcidev->dev, job->reply_payload.sg_list,
			1, PCI_DMA_BIसूचीECTIONAL))
		जाओ unmap_out;
	flagsLength |= sg_dma_len(job->reply_payload.sg_list) + 4;
	ioc->add_sge(psge, flagsLength,
			sg_dma_address(job->reply_payload.sg_list));

	INITIALIZE_MGMT_STATUS(ioc->sas_mgmt.status)
	mpt_put_msg_frame(mptsasMgmtCtx, ioc, mf);

	समयleft = रुको_क्रम_completion_समयout(&ioc->sas_mgmt.करोne, 10 * HZ);
	अगर (!(ioc->sas_mgmt.status & MPT_MGMT_STATUS_COMMAND_GOOD)) अणु
		ret = -ETIME;
		mpt_मुक्त_msg_frame(ioc, mf);
		mf = शून्य;
		अगर (ioc->sas_mgmt.status & MPT_MGMT_STATUS_DID_IOCRESET)
			जाओ unmap_in;
		अगर (!समयleft)
			mpt_Soft_Hard_ResetHandler(ioc, CAN_SLEEP);
		जाओ unmap_in;
	पूर्ण
	mf = शून्य;

	अगर (ioc->sas_mgmt.status & MPT_MGMT_STATUS_RF_VALID) अणु
		SmpPassthroughReply_t *smprep;

		smprep = (SmpPassthroughReply_t *)ioc->sas_mgmt.reply;
		स_नकल(job->reply, smprep, माप(*smprep));
		job->reply_len = माप(*smprep);
		reslen = smprep->ResponseDataLength;
	पूर्ण अन्यथा अणु
		prपूर्णांकk(MYIOC_s_ERR_FMT
		    "%s: smp passthru reply failed to be returned\n",
		    ioc->name, __func__);
		ret = -ENXIO;
	पूर्ण

unmap_in:
	dma_unmap_sg(&ioc->pcidev->dev, job->reply_payload.sg_list, 1,
			PCI_DMA_BIसूचीECTIONAL);
unmap_out:
	dma_unmap_sg(&ioc->pcidev->dev, job->request_payload.sg_list, 1,
			PCI_DMA_BIसूचीECTIONAL);
put_mf:
	अगर (mf)
		mpt_मुक्त_msg_frame(ioc, mf);
out_unlock:
	CLEAR_MGMT_STATUS(ioc->sas_mgmt.status)
	mutex_unlock(&ioc->sas_mgmt.mutex);
out:
	bsg_job_करोne(job, ret, reslen);
पूर्ण

अटल काष्ठा sas_function_ढाँचा mptsas_transport_functions = अणु
	.get_linkerrors		= mptsas_get_linkerrors,
	.get_enclosure_identअगरier = mptsas_get_enclosure_identअगरier,
	.get_bay_identअगरier	= mptsas_get_bay_identअगरier,
	.phy_reset		= mptsas_phy_reset,
	.smp_handler		= mptsas_smp_handler,
पूर्ण;

अटल काष्ठा scsi_transport_ढाँचा *mptsas_transport_ढाँचा;

अटल पूर्णांक
mptsas_sas_io_unit_pg0(MPT_ADAPTER *ioc, काष्ठा mptsas_portinfo *port_info)
अणु
	ConfigExtendedPageHeader_t hdr;
	CONFIGPARMS cfg;
	SasIOUnitPage0_t *buffer;
	dma_addr_t dma_handle;
	पूर्णांक error, i;

	hdr.PageVersion = MPI_SASIOUNITPAGE0_PAGEVERSION;
	hdr.ExtPageLength = 0;
	hdr.PageNumber = 0;
	hdr.Reserved1 = 0;
	hdr.Reserved2 = 0;
	hdr.PageType = MPI_CONFIG_PAGETYPE_EXTENDED;
	hdr.ExtPageType = MPI_CONFIG_EXTPAGETYPE_SAS_IO_UNIT;

	cfg.cfghdr.ehdr = &hdr;
	cfg.physAddr = -1;
	cfg.pageAddr = 0;
	cfg.action = MPI_CONFIG_ACTION_PAGE_HEADER;
	cfg.dir = 0;	/* पढ़ो */
	cfg.समयout = SAS_CONFIG_PAGE_TIMEOUT;

	error = mpt_config(ioc, &cfg);
	अगर (error)
		जाओ out;
	अगर (!hdr.ExtPageLength) अणु
		error = -ENXIO;
		जाओ out;
	पूर्ण

	buffer = pci_alloc_consistent(ioc->pcidev, hdr.ExtPageLength * 4,
					    &dma_handle);
	अगर (!buffer) अणु
		error = -ENOMEM;
		जाओ out;
	पूर्ण

	cfg.physAddr = dma_handle;
	cfg.action = MPI_CONFIG_ACTION_PAGE_READ_CURRENT;

	error = mpt_config(ioc, &cfg);
	अगर (error)
		जाओ out_मुक्त_consistent;

	port_info->num_phys = buffer->NumPhys;
	port_info->phy_info = kसुस्मृति(port_info->num_phys,
		माप(काष्ठा mptsas_phyinfo), GFP_KERNEL);
	अगर (!port_info->phy_info) अणु
		error = -ENOMEM;
		जाओ out_मुक्त_consistent;
	पूर्ण

	ioc->nvdata_version_persistent =
	    le16_to_cpu(buffer->NvdataVersionPersistent);
	ioc->nvdata_version_शेष =
	    le16_to_cpu(buffer->NvdataVersionDefault);

	क्रम (i = 0; i < port_info->num_phys; i++) अणु
		mptsas_prपूर्णांक_phy_data(ioc, &buffer->PhyData[i]);
		port_info->phy_info[i].phy_id = i;
		port_info->phy_info[i].port_id =
		    buffer->PhyData[i].Port;
		port_info->phy_info[i].negotiated_link_rate =
		    buffer->PhyData[i].NegotiatedLinkRate;
		port_info->phy_info[i].portinfo = port_info;
		port_info->phy_info[i].handle =
		    le16_to_cpu(buffer->PhyData[i].ControllerDevHandle);
	पूर्ण

 out_मुक्त_consistent:
	pci_मुक्त_consistent(ioc->pcidev, hdr.ExtPageLength * 4,
			    buffer, dma_handle);
 out:
	वापस error;
पूर्ण

अटल पूर्णांक
mptsas_sas_io_unit_pg1(MPT_ADAPTER *ioc)
अणु
	ConfigExtendedPageHeader_t hdr;
	CONFIGPARMS cfg;
	SasIOUnitPage1_t *buffer;
	dma_addr_t dma_handle;
	पूर्णांक error;
	u8 device_missing_delay;

	स_रखो(&hdr, 0, माप(ConfigExtendedPageHeader_t));
	स_रखो(&cfg, 0, माप(CONFIGPARMS));

	cfg.cfghdr.ehdr = &hdr;
	cfg.action = MPI_CONFIG_ACTION_PAGE_HEADER;
	cfg.समयout = SAS_CONFIG_PAGE_TIMEOUT;
	cfg.cfghdr.ehdr->PageType = MPI_CONFIG_PAGETYPE_EXTENDED;
	cfg.cfghdr.ehdr->ExtPageType = MPI_CONFIG_EXTPAGETYPE_SAS_IO_UNIT;
	cfg.cfghdr.ehdr->PageVersion = MPI_SASIOUNITPAGE1_PAGEVERSION;
	cfg.cfghdr.ehdr->PageNumber = 1;

	error = mpt_config(ioc, &cfg);
	अगर (error)
		जाओ out;
	अगर (!hdr.ExtPageLength) अणु
		error = -ENXIO;
		जाओ out;
	पूर्ण

	buffer = pci_alloc_consistent(ioc->pcidev, hdr.ExtPageLength * 4,
					    &dma_handle);
	अगर (!buffer) अणु
		error = -ENOMEM;
		जाओ out;
	पूर्ण

	cfg.physAddr = dma_handle;
	cfg.action = MPI_CONFIG_ACTION_PAGE_READ_CURRENT;

	error = mpt_config(ioc, &cfg);
	अगर (error)
		जाओ out_मुक्त_consistent;

	ioc->io_missing_delay  =
	    le16_to_cpu(buffer->IODeviceMissingDelay);
	device_missing_delay = buffer->ReportDeviceMissingDelay;
	ioc->device_missing_delay = (device_missing_delay & MPI_SAS_IOUNIT1_REPORT_MISSING_UNIT_16) ?
	    (device_missing_delay & MPI_SAS_IOUNIT1_REPORT_MISSING_TIMEOUT_MASK) * 16 :
	    device_missing_delay & MPI_SAS_IOUNIT1_REPORT_MISSING_TIMEOUT_MASK;

 out_मुक्त_consistent:
	pci_मुक्त_consistent(ioc->pcidev, hdr.ExtPageLength * 4,
			    buffer, dma_handle);
 out:
	वापस error;
पूर्ण

अटल पूर्णांक
mptsas_sas_phy_pg0(MPT_ADAPTER *ioc, काष्ठा mptsas_phyinfo *phy_info,
		u32 क्रमm, u32 क्रमm_specअगरic)
अणु
	ConfigExtendedPageHeader_t hdr;
	CONFIGPARMS cfg;
	SasPhyPage0_t *buffer;
	dma_addr_t dma_handle;
	पूर्णांक error;

	hdr.PageVersion = MPI_SASPHY0_PAGEVERSION;
	hdr.ExtPageLength = 0;
	hdr.PageNumber = 0;
	hdr.Reserved1 = 0;
	hdr.Reserved2 = 0;
	hdr.PageType = MPI_CONFIG_PAGETYPE_EXTENDED;
	hdr.ExtPageType = MPI_CONFIG_EXTPAGETYPE_SAS_PHY;

	cfg.cfghdr.ehdr = &hdr;
	cfg.dir = 0;	/* पढ़ो */
	cfg.समयout = SAS_CONFIG_PAGE_TIMEOUT;

	/* Get Phy Pg 0 क्रम each Phy. */
	cfg.physAddr = -1;
	cfg.pageAddr = क्रमm + क्रमm_specअगरic;
	cfg.action = MPI_CONFIG_ACTION_PAGE_HEADER;

	error = mpt_config(ioc, &cfg);
	अगर (error)
		जाओ out;

	अगर (!hdr.ExtPageLength) अणु
		error = -ENXIO;
		जाओ out;
	पूर्ण

	buffer = pci_alloc_consistent(ioc->pcidev, hdr.ExtPageLength * 4,
				      &dma_handle);
	अगर (!buffer) अणु
		error = -ENOMEM;
		जाओ out;
	पूर्ण

	cfg.physAddr = dma_handle;
	cfg.action = MPI_CONFIG_ACTION_PAGE_READ_CURRENT;

	error = mpt_config(ioc, &cfg);
	अगर (error)
		जाओ out_मुक्त_consistent;

	mptsas_prपूर्णांक_phy_pg0(ioc, buffer);

	phy_info->hw_link_rate = buffer->HwLinkRate;
	phy_info->programmed_link_rate = buffer->ProgrammedLinkRate;
	phy_info->identअगरy.handle = le16_to_cpu(buffer->OwnerDevHandle);
	phy_info->attached.handle = le16_to_cpu(buffer->AttachedDevHandle);

 out_मुक्त_consistent:
	pci_मुक्त_consistent(ioc->pcidev, hdr.ExtPageLength * 4,
			    buffer, dma_handle);
 out:
	वापस error;
पूर्ण

अटल पूर्णांक
mptsas_sas_device_pg0(MPT_ADAPTER *ioc, काष्ठा mptsas_devinfo *device_info,
		u32 क्रमm, u32 क्रमm_specअगरic)
अणु
	ConfigExtendedPageHeader_t hdr;
	CONFIGPARMS cfg;
	SasDevicePage0_t *buffer;
	dma_addr_t dma_handle;
	__le64 sas_address;
	पूर्णांक error=0;

	hdr.PageVersion = MPI_SASDEVICE0_PAGEVERSION;
	hdr.ExtPageLength = 0;
	hdr.PageNumber = 0;
	hdr.Reserved1 = 0;
	hdr.Reserved2 = 0;
	hdr.PageType = MPI_CONFIG_PAGETYPE_EXTENDED;
	hdr.ExtPageType = MPI_CONFIG_EXTPAGETYPE_SAS_DEVICE;

	cfg.cfghdr.ehdr = &hdr;
	cfg.pageAddr = क्रमm + क्रमm_specअगरic;
	cfg.physAddr = -1;
	cfg.action = MPI_CONFIG_ACTION_PAGE_HEADER;
	cfg.dir = 0;	/* पढ़ो */
	cfg.समयout = SAS_CONFIG_PAGE_TIMEOUT;

	स_रखो(device_info, 0, माप(काष्ठा mptsas_devinfo));
	error = mpt_config(ioc, &cfg);
	अगर (error)
		जाओ out;
	अगर (!hdr.ExtPageLength) अणु
		error = -ENXIO;
		जाओ out;
	पूर्ण

	buffer = pci_alloc_consistent(ioc->pcidev, hdr.ExtPageLength * 4,
				      &dma_handle);
	अगर (!buffer) अणु
		error = -ENOMEM;
		जाओ out;
	पूर्ण

	cfg.physAddr = dma_handle;
	cfg.action = MPI_CONFIG_ACTION_PAGE_READ_CURRENT;

	error = mpt_config(ioc, &cfg);

	अगर (error == MPI_IOCSTATUS_CONFIG_INVALID_PAGE) अणु
		error = -ENODEV;
		जाओ out_मुक्त_consistent;
	पूर्ण

	अगर (error)
		जाओ out_मुक्त_consistent;

	mptsas_prपूर्णांक_device_pg0(ioc, buffer);

	स_रखो(device_info, 0, माप(काष्ठा mptsas_devinfo));
	device_info->handle = le16_to_cpu(buffer->DevHandle);
	device_info->handle_parent = le16_to_cpu(buffer->ParentDevHandle);
	device_info->handle_enclosure =
	    le16_to_cpu(buffer->EnclosureHandle);
	device_info->slot = le16_to_cpu(buffer->Slot);
	device_info->phy_id = buffer->PhyNum;
	device_info->port_id = buffer->PhysicalPort;
	device_info->id = buffer->TargetID;
	device_info->phys_disk_num = ~0;
	device_info->channel = buffer->Bus;
	स_नकल(&sas_address, &buffer->SASAddress, माप(__le64));
	device_info->sas_address = le64_to_cpu(sas_address);
	device_info->device_info =
	    le32_to_cpu(buffer->DeviceInfo);
	device_info->flags = le16_to_cpu(buffer->Flags);

 out_मुक्त_consistent:
	pci_मुक्त_consistent(ioc->pcidev, hdr.ExtPageLength * 4,
			    buffer, dma_handle);
 out:
	वापस error;
पूर्ण

अटल पूर्णांक
mptsas_sas_expander_pg0(MPT_ADAPTER *ioc, काष्ठा mptsas_portinfo *port_info,
		u32 क्रमm, u32 क्रमm_specअगरic)
अणु
	ConfigExtendedPageHeader_t hdr;
	CONFIGPARMS cfg;
	SasExpanderPage0_t *buffer;
	dma_addr_t dma_handle;
	पूर्णांक i, error;
	__le64 sas_address;

	स_रखो(port_info, 0, माप(काष्ठा mptsas_portinfo));
	hdr.PageVersion = MPI_SASEXPANDER0_PAGEVERSION;
	hdr.ExtPageLength = 0;
	hdr.PageNumber = 0;
	hdr.Reserved1 = 0;
	hdr.Reserved2 = 0;
	hdr.PageType = MPI_CONFIG_PAGETYPE_EXTENDED;
	hdr.ExtPageType = MPI_CONFIG_EXTPAGETYPE_SAS_EXPANDER;

	cfg.cfghdr.ehdr = &hdr;
	cfg.physAddr = -1;
	cfg.pageAddr = क्रमm + क्रमm_specअगरic;
	cfg.action = MPI_CONFIG_ACTION_PAGE_HEADER;
	cfg.dir = 0;	/* पढ़ो */
	cfg.समयout = SAS_CONFIG_PAGE_TIMEOUT;

	स_रखो(port_info, 0, माप(काष्ठा mptsas_portinfo));
	error = mpt_config(ioc, &cfg);
	अगर (error)
		जाओ out;

	अगर (!hdr.ExtPageLength) अणु
		error = -ENXIO;
		जाओ out;
	पूर्ण

	buffer = pci_alloc_consistent(ioc->pcidev, hdr.ExtPageLength * 4,
				      &dma_handle);
	अगर (!buffer) अणु
		error = -ENOMEM;
		जाओ out;
	पूर्ण

	cfg.physAddr = dma_handle;
	cfg.action = MPI_CONFIG_ACTION_PAGE_READ_CURRENT;

	error = mpt_config(ioc, &cfg);
	अगर (error == MPI_IOCSTATUS_CONFIG_INVALID_PAGE) अणु
		error = -ENODEV;
		जाओ out_मुक्त_consistent;
	पूर्ण

	अगर (error)
		जाओ out_मुक्त_consistent;

	/* save config data */
	port_info->num_phys = (buffer->NumPhys) ? buffer->NumPhys : 1;
	port_info->phy_info = kसुस्मृति(port_info->num_phys,
		माप(काष्ठा mptsas_phyinfo), GFP_KERNEL);
	अगर (!port_info->phy_info) अणु
		error = -ENOMEM;
		जाओ out_मुक्त_consistent;
	पूर्ण

	स_नकल(&sas_address, &buffer->SASAddress, माप(__le64));
	क्रम (i = 0; i < port_info->num_phys; i++) अणु
		port_info->phy_info[i].portinfo = port_info;
		port_info->phy_info[i].handle =
		    le16_to_cpu(buffer->DevHandle);
		port_info->phy_info[i].identअगरy.sas_address =
		    le64_to_cpu(sas_address);
		port_info->phy_info[i].identअगरy.handle_parent =
		    le16_to_cpu(buffer->ParentDevHandle);
	पूर्ण

 out_मुक्त_consistent:
	pci_मुक्त_consistent(ioc->pcidev, hdr.ExtPageLength * 4,
			    buffer, dma_handle);
 out:
	वापस error;
पूर्ण

अटल पूर्णांक
mptsas_sas_expander_pg1(MPT_ADAPTER *ioc, काष्ठा mptsas_phyinfo *phy_info,
		u32 क्रमm, u32 क्रमm_specअगरic)
अणु
	ConfigExtendedPageHeader_t hdr;
	CONFIGPARMS cfg;
	SasExpanderPage1_t *buffer;
	dma_addr_t dma_handle;
	पूर्णांक error=0;

	hdr.PageVersion = MPI_SASEXPANDER1_PAGEVERSION;
	hdr.ExtPageLength = 0;
	hdr.PageNumber = 1;
	hdr.Reserved1 = 0;
	hdr.Reserved2 = 0;
	hdr.PageType = MPI_CONFIG_PAGETYPE_EXTENDED;
	hdr.ExtPageType = MPI_CONFIG_EXTPAGETYPE_SAS_EXPANDER;

	cfg.cfghdr.ehdr = &hdr;
	cfg.physAddr = -1;
	cfg.pageAddr = क्रमm + क्रमm_specअगरic;
	cfg.action = MPI_CONFIG_ACTION_PAGE_HEADER;
	cfg.dir = 0;	/* पढ़ो */
	cfg.समयout = SAS_CONFIG_PAGE_TIMEOUT;

	error = mpt_config(ioc, &cfg);
	अगर (error)
		जाओ out;

	अगर (!hdr.ExtPageLength) अणु
		error = -ENXIO;
		जाओ out;
	पूर्ण

	buffer = pci_alloc_consistent(ioc->pcidev, hdr.ExtPageLength * 4,
				      &dma_handle);
	अगर (!buffer) अणु
		error = -ENOMEM;
		जाओ out;
	पूर्ण

	cfg.physAddr = dma_handle;
	cfg.action = MPI_CONFIG_ACTION_PAGE_READ_CURRENT;

	error = mpt_config(ioc, &cfg);

	अगर (error == MPI_IOCSTATUS_CONFIG_INVALID_PAGE) अणु
		error = -ENODEV;
		जाओ out_मुक्त_consistent;
	पूर्ण

	अगर (error)
		जाओ out_मुक्त_consistent;


	mptsas_prपूर्णांक_expander_pg1(ioc, buffer);

	/* save config data */
	phy_info->phy_id = buffer->PhyIdentअगरier;
	phy_info->port_id = buffer->PhysicalPort;
	phy_info->negotiated_link_rate = buffer->NegotiatedLinkRate;
	phy_info->programmed_link_rate = buffer->ProgrammedLinkRate;
	phy_info->hw_link_rate = buffer->HwLinkRate;
	phy_info->identअगरy.handle = le16_to_cpu(buffer->OwnerDevHandle);
	phy_info->attached.handle = le16_to_cpu(buffer->AttachedDevHandle);

 out_मुक्त_consistent:
	pci_मुक्त_consistent(ioc->pcidev, hdr.ExtPageLength * 4,
			    buffer, dma_handle);
 out:
	वापस error;
पूर्ण

काष्ठा rep_manu_requestअणु
	u8 smp_frame_type;
	u8 function;
	u8 reserved;
	u8 request_length;
पूर्ण;

काष्ठा rep_manu_replyअणु
	u8 smp_frame_type; /* 0x41 */
	u8 function; /* 0x01 */
	u8 function_result;
	u8 response_length;
	u16 expander_change_count;
	u8 reserved0[2];
	u8 sas_क्रमmat:1;
	u8 reserved1:7;
	u8 reserved2[3];
	u8 venकरोr_id[SAS_EXPANDER_VENDOR_ID_LEN];
	u8 product_id[SAS_EXPANDER_PRODUCT_ID_LEN];
	u8 product_rev[SAS_EXPANDER_PRODUCT_REV_LEN];
	u8 component_venकरोr_id[SAS_EXPANDER_COMPONENT_VENDOR_ID_LEN];
	u16 component_id;
	u8 component_revision_id;
	u8 reserved3;
	u8 venकरोr_specअगरic[8];
पूर्ण;

/**
  * mptsas_exp_repmanufacture_info -
  * @ioc: per adapter object
  * @sas_address: expander sas address
  * @edev: the sas_expander_device object
  *
  * Fills in the sas_expander_device object when SMP port is created.
  *
  * Returns 0 क्रम success, non-zero क्रम failure.
  */
अटल पूर्णांक
mptsas_exp_repmanufacture_info(MPT_ADAPTER *ioc,
	u64 sas_address, काष्ठा sas_expander_device *edev)
अणु
	MPT_FRAME_HDR *mf;
	SmpPassthroughRequest_t *smpreq;
	SmpPassthroughReply_t *smprep;
	काष्ठा rep_manu_reply *manufacture_reply;
	काष्ठा rep_manu_request *manufacture_request;
	पूर्णांक ret;
	पूर्णांक flagsLength;
	अचिन्हित दीर्घ समयleft;
	अक्षर *psge;
	अचिन्हित दीर्घ flags;
	व्योम *data_out = शून्य;
	dma_addr_t data_out_dma = 0;
	u32 sz;

	spin_lock_irqsave(&ioc->taskmgmt_lock, flags);
	अगर (ioc->ioc_reset_in_progress) अणु
		spin_unlock_irqrestore(&ioc->taskmgmt_lock, flags);
		prपूर्णांकk(MYIOC_s_INFO_FMT "%s: host reset in progress!\n",
			__func__, ioc->name);
		वापस -EFAULT;
	पूर्ण
	spin_unlock_irqrestore(&ioc->taskmgmt_lock, flags);

	ret = mutex_lock_पूर्णांकerruptible(&ioc->sas_mgmt.mutex);
	अगर (ret)
		जाओ out;

	mf = mpt_get_msg_frame(mptsasMgmtCtx, ioc);
	अगर (!mf) अणु
		ret = -ENOMEM;
		जाओ out_unlock;
	पूर्ण

	smpreq = (SmpPassthroughRequest_t *)mf;
	स_रखो(smpreq, 0, माप(*smpreq));

	sz = माप(काष्ठा rep_manu_request) + माप(काष्ठा rep_manu_reply);

	data_out = pci_alloc_consistent(ioc->pcidev, sz, &data_out_dma);
	अगर (!data_out) अणु
		prपूर्णांकk(KERN_ERR "Memory allocation failure at %s:%d/%s()!\n",
			__खाता__, __LINE__, __func__);
		ret = -ENOMEM;
		जाओ put_mf;
	पूर्ण

	manufacture_request = data_out;
	manufacture_request->smp_frame_type = 0x40;
	manufacture_request->function = 1;
	manufacture_request->reserved = 0;
	manufacture_request->request_length = 0;

	smpreq->Function = MPI_FUNCTION_SMP_PASSTHROUGH;
	smpreq->PhysicalPort = 0xFF;
	*((u64 *)&smpreq->SASAddress) = cpu_to_le64(sas_address);
	smpreq->RequestDataLength = माप(काष्ठा rep_manu_request);

	psge = (अक्षर *)
		(((पूर्णांक *) mf) + (दुरत्व(SmpPassthroughRequest_t, SGL) / 4));

	flagsLength = MPI_SGE_FLAGS_SIMPLE_ELEMENT |
		MPI_SGE_FLAGS_SYSTEM_ADDRESS |
		MPI_SGE_FLAGS_HOST_TO_IOC |
		MPI_SGE_FLAGS_END_OF_BUFFER;
	flagsLength = flagsLength << MPI_SGE_FLAGS_SHIFT;
	flagsLength |= माप(काष्ठा rep_manu_request);

	ioc->add_sge(psge, flagsLength, data_out_dma);
	psge += ioc->SGE_size;

	flagsLength = MPI_SGE_FLAGS_SIMPLE_ELEMENT |
		MPI_SGE_FLAGS_SYSTEM_ADDRESS |
		MPI_SGE_FLAGS_IOC_TO_HOST |
		MPI_SGE_FLAGS_END_OF_BUFFER;
	flagsLength = flagsLength << MPI_SGE_FLAGS_SHIFT;
	flagsLength |= माप(काष्ठा rep_manu_reply);
	ioc->add_sge(psge, flagsLength, data_out_dma +
	माप(काष्ठा rep_manu_request));

	INITIALIZE_MGMT_STATUS(ioc->sas_mgmt.status)
	mpt_put_msg_frame(mptsasMgmtCtx, ioc, mf);

	समयleft = रुको_क्रम_completion_समयout(&ioc->sas_mgmt.करोne, 10 * HZ);
	अगर (!(ioc->sas_mgmt.status & MPT_MGMT_STATUS_COMMAND_GOOD)) अणु
		ret = -ETIME;
		mpt_मुक्त_msg_frame(ioc, mf);
		mf = शून्य;
		अगर (ioc->sas_mgmt.status & MPT_MGMT_STATUS_DID_IOCRESET)
			जाओ out_मुक्त;
		अगर (!समयleft)
			mpt_Soft_Hard_ResetHandler(ioc, CAN_SLEEP);
		जाओ out_मुक्त;
	पूर्ण

	mf = शून्य;

	अगर (ioc->sas_mgmt.status & MPT_MGMT_STATUS_RF_VALID) अणु
		u8 *पंचांगp;

		smprep = (SmpPassthroughReply_t *)ioc->sas_mgmt.reply;
		अगर (le16_to_cpu(smprep->ResponseDataLength) !=
		    माप(काष्ठा rep_manu_reply))
			जाओ out_मुक्त;

		manufacture_reply = data_out + माप(काष्ठा rep_manu_request);
		म_नकलन(edev->venकरोr_id, manufacture_reply->venकरोr_id,
			SAS_EXPANDER_VENDOR_ID_LEN);
		म_नकलन(edev->product_id, manufacture_reply->product_id,
			SAS_EXPANDER_PRODUCT_ID_LEN);
		म_नकलन(edev->product_rev, manufacture_reply->product_rev,
			SAS_EXPANDER_PRODUCT_REV_LEN);
		edev->level = manufacture_reply->sas_क्रमmat;
		अगर (manufacture_reply->sas_क्रमmat) अणु
			म_नकलन(edev->component_venकरोr_id,
				manufacture_reply->component_venकरोr_id,
				SAS_EXPANDER_COMPONENT_VENDOR_ID_LEN);
			पंचांगp = (u8 *)&manufacture_reply->component_id;
			edev->component_id = पंचांगp[0] << 8 | पंचांगp[1];
			edev->component_revision_id =
				manufacture_reply->component_revision_id;
		पूर्ण
	पूर्ण अन्यथा अणु
		prपूर्णांकk(MYIOC_s_ERR_FMT
			"%s: smp passthru reply failed to be returned\n",
			ioc->name, __func__);
		ret = -ENXIO;
	पूर्ण
out_मुक्त:
	अगर (data_out_dma)
		pci_मुक्त_consistent(ioc->pcidev, sz, data_out, data_out_dma);
put_mf:
	अगर (mf)
		mpt_मुक्त_msg_frame(ioc, mf);
out_unlock:
	CLEAR_MGMT_STATUS(ioc->sas_mgmt.status)
	mutex_unlock(&ioc->sas_mgmt.mutex);
out:
	वापस ret;
पूर्ण

अटल व्योम
mptsas_parse_device_info(काष्ठा sas_identअगरy *identअगरy,
		काष्ठा mptsas_devinfo *device_info)
अणु
	u16 protocols;

	identअगरy->sas_address = device_info->sas_address;
	identअगरy->phy_identअगरier = device_info->phy_id;

	/*
	 * Fill in Phy Initiator Port Protocol.
	 * Bits 6:3, more than one bit can be set, fall through हालs.
	 */
	protocols = device_info->device_info & 0x78;
	identअगरy->initiator_port_protocols = 0;
	अगर (protocols & MPI_SAS_DEVICE_INFO_SSP_INITIATOR)
		identअगरy->initiator_port_protocols |= SAS_PROTOCOL_SSP;
	अगर (protocols & MPI_SAS_DEVICE_INFO_STP_INITIATOR)
		identअगरy->initiator_port_protocols |= SAS_PROTOCOL_STP;
	अगर (protocols & MPI_SAS_DEVICE_INFO_SMP_INITIATOR)
		identअगरy->initiator_port_protocols |= SAS_PROTOCOL_SMP;
	अगर (protocols & MPI_SAS_DEVICE_INFO_SATA_HOST)
		identअगरy->initiator_port_protocols |= SAS_PROTOCOL_SATA;

	/*
	 * Fill in Phy Target Port Protocol.
	 * Bits 10:7, more than one bit can be set, fall through हालs.
	 */
	protocols = device_info->device_info & 0x780;
	identअगरy->target_port_protocols = 0;
	अगर (protocols & MPI_SAS_DEVICE_INFO_SSP_TARGET)
		identअगरy->target_port_protocols |= SAS_PROTOCOL_SSP;
	अगर (protocols & MPI_SAS_DEVICE_INFO_STP_TARGET)
		identअगरy->target_port_protocols |= SAS_PROTOCOL_STP;
	अगर (protocols & MPI_SAS_DEVICE_INFO_SMP_TARGET)
		identअगरy->target_port_protocols |= SAS_PROTOCOL_SMP;
	अगर (protocols & MPI_SAS_DEVICE_INFO_SATA_DEVICE)
		identअगरy->target_port_protocols |= SAS_PROTOCOL_SATA;

	/*
	 * Fill in Attached device type.
	 */
	चयन (device_info->device_info &
			MPI_SAS_DEVICE_INFO_MASK_DEVICE_TYPE) अणु
	हाल MPI_SAS_DEVICE_INFO_NO_DEVICE:
		identअगरy->device_type = SAS_PHY_UNUSED;
		अवरोध;
	हाल MPI_SAS_DEVICE_INFO_END_DEVICE:
		identअगरy->device_type = SAS_END_DEVICE;
		अवरोध;
	हाल MPI_SAS_DEVICE_INFO_EDGE_EXPANDER:
		identअगरy->device_type = SAS_EDGE_EXPANDER_DEVICE;
		अवरोध;
	हाल MPI_SAS_DEVICE_INFO_FANOUT_EXPANDER:
		identअगरy->device_type = SAS_FANOUT_EXPANDER_DEVICE;
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक mptsas_probe_one_phy(काष्ठा device *dev,
		काष्ठा mptsas_phyinfo *phy_info, पूर्णांक index, पूर्णांक local)
अणु
	MPT_ADAPTER *ioc;
	काष्ठा sas_phy *phy;
	काष्ठा sas_port *port;
	पूर्णांक error = 0;
	VirtTarget *vtarget;

	अगर (!dev) अणु
		error = -ENODEV;
		जाओ out;
	पूर्ण

	अगर (!phy_info->phy) अणु
		phy = sas_phy_alloc(dev, index);
		अगर (!phy) अणु
			error = -ENOMEM;
			जाओ out;
		पूर्ण
	पूर्ण अन्यथा
		phy = phy_info->phy;

	mptsas_parse_device_info(&phy->identअगरy, &phy_info->identअगरy);

	/*
	 * Set Negotiated link rate.
	 */
	चयन (phy_info->negotiated_link_rate) अणु
	हाल MPI_SAS_IOUNIT0_RATE_PHY_DISABLED:
		phy->negotiated_linkrate = SAS_PHY_DISABLED;
		अवरोध;
	हाल MPI_SAS_IOUNIT0_RATE_FAILED_SPEED_NEGOTIATION:
		phy->negotiated_linkrate = SAS_LINK_RATE_FAILED;
		अवरोध;
	हाल MPI_SAS_IOUNIT0_RATE_1_5:
		phy->negotiated_linkrate = SAS_LINK_RATE_1_5_GBPS;
		अवरोध;
	हाल MPI_SAS_IOUNIT0_RATE_3_0:
		phy->negotiated_linkrate = SAS_LINK_RATE_3_0_GBPS;
		अवरोध;
	हाल MPI_SAS_IOUNIT0_RATE_6_0:
		phy->negotiated_linkrate = SAS_LINK_RATE_6_0_GBPS;
		अवरोध;
	हाल MPI_SAS_IOUNIT0_RATE_SATA_OOB_COMPLETE:
	हाल MPI_SAS_IOUNIT0_RATE_UNKNOWN:
	शेष:
		phy->negotiated_linkrate = SAS_LINK_RATE_UNKNOWN;
		अवरोध;
	पूर्ण

	/*
	 * Set Max hardware link rate.
	 */
	चयन (phy_info->hw_link_rate & MPI_SAS_PHY0_PRATE_MAX_RATE_MASK) अणु
	हाल MPI_SAS_PHY0_HWRATE_MAX_RATE_1_5:
		phy->maximum_linkrate_hw = SAS_LINK_RATE_1_5_GBPS;
		अवरोध;
	हाल MPI_SAS_PHY0_PRATE_MAX_RATE_3_0:
		phy->maximum_linkrate_hw = SAS_LINK_RATE_3_0_GBPS;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	/*
	 * Set Max programmed link rate.
	 */
	चयन (phy_info->programmed_link_rate &
			MPI_SAS_PHY0_PRATE_MAX_RATE_MASK) अणु
	हाल MPI_SAS_PHY0_PRATE_MAX_RATE_1_5:
		phy->maximum_linkrate = SAS_LINK_RATE_1_5_GBPS;
		अवरोध;
	हाल MPI_SAS_PHY0_PRATE_MAX_RATE_3_0:
		phy->maximum_linkrate = SAS_LINK_RATE_3_0_GBPS;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	/*
	 * Set Min hardware link rate.
	 */
	चयन (phy_info->hw_link_rate & MPI_SAS_PHY0_HWRATE_MIN_RATE_MASK) अणु
	हाल MPI_SAS_PHY0_HWRATE_MIN_RATE_1_5:
		phy->minimum_linkrate_hw = SAS_LINK_RATE_1_5_GBPS;
		अवरोध;
	हाल MPI_SAS_PHY0_PRATE_MIN_RATE_3_0:
		phy->minimum_linkrate_hw = SAS_LINK_RATE_3_0_GBPS;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	/*
	 * Set Min programmed link rate.
	 */
	चयन (phy_info->programmed_link_rate &
			MPI_SAS_PHY0_PRATE_MIN_RATE_MASK) अणु
	हाल MPI_SAS_PHY0_PRATE_MIN_RATE_1_5:
		phy->minimum_linkrate = SAS_LINK_RATE_1_5_GBPS;
		अवरोध;
	हाल MPI_SAS_PHY0_PRATE_MIN_RATE_3_0:
		phy->minimum_linkrate = SAS_LINK_RATE_3_0_GBPS;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	अगर (!phy_info->phy) अणु

		error = sas_phy_add(phy);
		अगर (error) अणु
			sas_phy_मुक्त(phy);
			जाओ out;
		पूर्ण
		phy_info->phy = phy;
	पूर्ण

	अगर (!phy_info->attached.handle ||
			!phy_info->port_details)
		जाओ out;

	port = mptsas_get_port(phy_info);
	ioc = phy_to_ioc(phy_info->phy);

	अगर (phy_info->sas_port_add_phy) अणु

		अगर (!port) अणु
			port = sas_port_alloc_num(dev);
			अगर (!port) अणु
				error = -ENOMEM;
				जाओ out;
			पूर्ण
			error = sas_port_add(port);
			अगर (error) अणु
				dfailprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_ERR_FMT
					"%s: exit at line=%d\n", ioc->name,
					__func__, __LINE__));
				जाओ out;
			पूर्ण
			mptsas_set_port(ioc, phy_info, port);
			devtprपूर्णांकk(ioc, dev_prपूर्णांकk(KERN_DEBUG, &port->dev,
			    MYIOC_s_FMT "add port %d, sas_addr (0x%llx)\n",
			    ioc->name, port->port_identअगरier,
			    (अचिन्हित दीर्घ दीर्घ)phy_info->
			    attached.sas_address));
		पूर्ण
		dsaswideprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT
			"sas_port_add_phy: phy_id=%d\n",
			ioc->name, phy_info->phy_id));
		sas_port_add_phy(port, phy_info->phy);
		phy_info->sas_port_add_phy = 0;
		devtprपूर्णांकk(ioc, dev_prपूर्णांकk(KERN_DEBUG, &phy_info->phy->dev,
		    MYIOC_s_FMT "add phy %d, phy-obj (0x%p)\n", ioc->name,
		     phy_info->phy_id, phy_info->phy));
	पूर्ण
	अगर (!mptsas_get_rphy(phy_info) && port && !port->rphy) अणु

		काष्ठा sas_rphy *rphy;
		काष्ठा device *parent;
		काष्ठा sas_identअगरy identअगरy;

		parent = dev->parent->parent;
		/*
		 * Let the hotplug_work thपढ़ो handle processing
		 * the adding/removing of devices that occur
		 * after start of day.
		 */
		अगर (mptsas_is_end_device(&phy_info->attached) &&
		    phy_info->attached.handle_parent) अणु
			जाओ out;
		पूर्ण

		mptsas_parse_device_info(&identअगरy, &phy_info->attached);
		अगर (scsi_is_host_device(parent)) अणु
			काष्ठा mptsas_portinfo *port_info;
			पूर्णांक i;

			port_info = ioc->hba_port_info;

			क्रम (i = 0; i < port_info->num_phys; i++)
				अगर (port_info->phy_info[i].identअगरy.sas_address ==
				    identअगरy.sas_address) अणु
					sas_port_mark_backlink(port);
					जाओ out;
				पूर्ण

		पूर्ण अन्यथा अगर (scsi_is_sas_rphy(parent)) अणु
			काष्ठा sas_rphy *parent_rphy = dev_to_rphy(parent);
			अगर (identअगरy.sas_address ==
			    parent_rphy->identअगरy.sas_address) अणु
				sas_port_mark_backlink(port);
				जाओ out;
			पूर्ण
		पूर्ण

		चयन (identअगरy.device_type) अणु
		हाल SAS_END_DEVICE:
			rphy = sas_end_device_alloc(port);
			अवरोध;
		हाल SAS_EDGE_EXPANDER_DEVICE:
		हाल SAS_FANOUT_EXPANDER_DEVICE:
			rphy = sas_expander_alloc(port, identअगरy.device_type);
			अवरोध;
		शेष:
			rphy = शून्य;
			अवरोध;
		पूर्ण
		अगर (!rphy) अणु
			dfailprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_ERR_FMT
				"%s: exit at line=%d\n", ioc->name,
				__func__, __LINE__));
			जाओ out;
		पूर्ण

		rphy->identअगरy = identअगरy;
		error = sas_rphy_add(rphy);
		अगर (error) अणु
			dfailprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_ERR_FMT
				"%s: exit at line=%d\n", ioc->name,
				__func__, __LINE__));
			sas_rphy_मुक्त(rphy);
			जाओ out;
		पूर्ण
		mptsas_set_rphy(ioc, phy_info, rphy);
		अगर (identअगरy.device_type == SAS_EDGE_EXPANDER_DEVICE ||
			identअगरy.device_type == SAS_FANOUT_EXPANDER_DEVICE)
				mptsas_exp_repmanufacture_info(ioc,
					identअगरy.sas_address,
					rphy_to_expander_device(rphy));
	पूर्ण

	/* If the device exists,verअगरy it wasn't previously flagged
	as a missing device.  If so, clear it */
	vtarget = mptsas_find_vtarget(ioc,
	    phy_info->attached.channel,
	    phy_info->attached.id);
	अगर (vtarget && vtarget->inDMD) अणु
		prपूर्णांकk(KERN_INFO "Device returned, unsetting inDMD\n");
		vtarget->inDMD = 0;
	पूर्ण

 out:
	वापस error;
पूर्ण

अटल पूर्णांक
mptsas_probe_hba_phys(MPT_ADAPTER *ioc)
अणु
	काष्ठा mptsas_portinfo *port_info, *hba;
	पूर्णांक error = -ENOMEM, i;

	hba = kzalloc(माप(काष्ठा mptsas_portinfo), GFP_KERNEL);
	अगर (! hba)
		जाओ out;

	error = mptsas_sas_io_unit_pg0(ioc, hba);
	अगर (error)
		जाओ out_मुक्त_port_info;

	mptsas_sas_io_unit_pg1(ioc);
	mutex_lock(&ioc->sas_topology_mutex);
	port_info = ioc->hba_port_info;
	अगर (!port_info) अणु
		ioc->hba_port_info = port_info = hba;
		ioc->hba_port_num_phy = port_info->num_phys;
		list_add_tail(&port_info->list, &ioc->sas_topology);
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < hba->num_phys; i++) अणु
			port_info->phy_info[i].negotiated_link_rate =
				hba->phy_info[i].negotiated_link_rate;
			port_info->phy_info[i].handle =
				hba->phy_info[i].handle;
			port_info->phy_info[i].port_id =
				hba->phy_info[i].port_id;
		पूर्ण
		kमुक्त(hba->phy_info);
		kमुक्त(hba);
		hba = शून्य;
	पूर्ण
	mutex_unlock(&ioc->sas_topology_mutex);
#अगर defined(CPQ_CIM)
	ioc->num_ports = port_info->num_phys;
#पूर्ण_अगर
	क्रम (i = 0; i < port_info->num_phys; i++) अणु
		mptsas_sas_phy_pg0(ioc, &port_info->phy_info[i],
			(MPI_SAS_PHY_PGAD_FORM_PHY_NUMBER <<
			 MPI_SAS_PHY_PGAD_FORM_SHIFT), i);
		port_info->phy_info[i].identअगरy.handle =
		    port_info->phy_info[i].handle;
		mptsas_sas_device_pg0(ioc, &port_info->phy_info[i].identअगरy,
			(MPI_SAS_DEVICE_PGAD_FORM_HANDLE <<
			 MPI_SAS_DEVICE_PGAD_FORM_SHIFT),
			 port_info->phy_info[i].identअगरy.handle);
		अगर (!ioc->hba_port_sas_addr)
			ioc->hba_port_sas_addr =
			    port_info->phy_info[i].identअगरy.sas_address;
		port_info->phy_info[i].identअगरy.phy_id =
		    port_info->phy_info[i].phy_id = i;
		अगर (port_info->phy_info[i].attached.handle)
			mptsas_sas_device_pg0(ioc,
				&port_info->phy_info[i].attached,
				(MPI_SAS_DEVICE_PGAD_FORM_HANDLE <<
				 MPI_SAS_DEVICE_PGAD_FORM_SHIFT),
				port_info->phy_info[i].attached.handle);
	पूर्ण

	mptsas_setup_wide_ports(ioc, port_info);

	क्रम (i = 0; i < port_info->num_phys; i++, ioc->sas_index++)
		mptsas_probe_one_phy(&ioc->sh->shost_gendev,
		    &port_info->phy_info[i], ioc->sas_index, 1);

	वापस 0;

 out_मुक्त_port_info:
	kमुक्त(hba);
 out:
	वापस error;
पूर्ण

अटल व्योम
mptsas_expander_refresh(MPT_ADAPTER *ioc, काष्ठा mptsas_portinfo *port_info)
अणु
	काष्ठा mptsas_portinfo *parent;
	काष्ठा device *parent_dev;
	काष्ठा sas_rphy	*rphy;
	पूर्णांक		i;
	u64		sas_address; /* expander sas address */
	u32		handle;

	handle = port_info->phy_info[0].handle;
	sas_address = port_info->phy_info[0].identअगरy.sas_address;
	क्रम (i = 0; i < port_info->num_phys; i++) अणु
		mptsas_sas_expander_pg1(ioc, &port_info->phy_info[i],
		    (MPI_SAS_EXPAND_PGAD_FORM_HANDLE_PHY_NUM <<
		    MPI_SAS_EXPAND_PGAD_FORM_SHIFT), (i << 16) + handle);

		mptsas_sas_device_pg0(ioc,
		    &port_info->phy_info[i].identअगरy,
		    (MPI_SAS_DEVICE_PGAD_FORM_HANDLE <<
		    MPI_SAS_DEVICE_PGAD_FORM_SHIFT),
		    port_info->phy_info[i].identअगरy.handle);
		port_info->phy_info[i].identअगरy.phy_id =
		    port_info->phy_info[i].phy_id;

		अगर (port_info->phy_info[i].attached.handle) अणु
			mptsas_sas_device_pg0(ioc,
			    &port_info->phy_info[i].attached,
			    (MPI_SAS_DEVICE_PGAD_FORM_HANDLE <<
			     MPI_SAS_DEVICE_PGAD_FORM_SHIFT),
			    port_info->phy_info[i].attached.handle);
			port_info->phy_info[i].attached.phy_id =
			    port_info->phy_info[i].phy_id;
		पूर्ण
	पूर्ण

	mutex_lock(&ioc->sas_topology_mutex);
	parent = mptsas_find_portinfo_by_handle(ioc,
	    port_info->phy_info[0].identअगरy.handle_parent);
	अगर (!parent) अणु
		mutex_unlock(&ioc->sas_topology_mutex);
		वापस;
	पूर्ण
	क्रम (i = 0, parent_dev = शून्य; i < parent->num_phys && !parent_dev;
	    i++) अणु
		अगर (parent->phy_info[i].attached.sas_address == sas_address) अणु
			rphy = mptsas_get_rphy(&parent->phy_info[i]);
			parent_dev = &rphy->dev;
		पूर्ण
	पूर्ण
	mutex_unlock(&ioc->sas_topology_mutex);

	mptsas_setup_wide_ports(ioc, port_info);
	क्रम (i = 0; i < port_info->num_phys; i++, ioc->sas_index++)
		mptsas_probe_one_phy(parent_dev, &port_info->phy_info[i],
		    ioc->sas_index, 0);
पूर्ण

अटल व्योम
mptsas_expander_event_add(MPT_ADAPTER *ioc,
    MpiEventDataSasExpanderStatusChange_t *expander_data)
अणु
	काष्ठा mptsas_portinfo *port_info;
	पूर्णांक i;
	__le64 sas_address;

	port_info = kzalloc(माप(काष्ठा mptsas_portinfo), GFP_KERNEL);
	BUG_ON(!port_info);
	port_info->num_phys = (expander_data->NumPhys) ?
	    expander_data->NumPhys : 1;
	port_info->phy_info = kसुस्मृति(port_info->num_phys,
	    माप(काष्ठा mptsas_phyinfo), GFP_KERNEL);
	BUG_ON(!port_info->phy_info);
	स_नकल(&sas_address, &expander_data->SASAddress, माप(__le64));
	क्रम (i = 0; i < port_info->num_phys; i++) अणु
		port_info->phy_info[i].portinfo = port_info;
		port_info->phy_info[i].handle =
		    le16_to_cpu(expander_data->DevHandle);
		port_info->phy_info[i].identअगरy.sas_address =
		    le64_to_cpu(sas_address);
		port_info->phy_info[i].identअगरy.handle_parent =
		    le16_to_cpu(expander_data->ParentDevHandle);
	पूर्ण

	mutex_lock(&ioc->sas_topology_mutex);
	list_add_tail(&port_info->list, &ioc->sas_topology);
	mutex_unlock(&ioc->sas_topology_mutex);

	prपूर्णांकk(MYIOC_s_INFO_FMT "add expander: num_phys %d, "
	    "sas_addr (0x%llx)\n", ioc->name, port_info->num_phys,
	    (अचिन्हित दीर्घ दीर्घ)sas_address);

	mptsas_expander_refresh(ioc, port_info);
पूर्ण

/**
 * mptsas_delete_expander_siblings - हटाओ siblings attached to expander
 * @ioc: Poपूर्णांकer to MPT_ADAPTER काष्ठाure
 * @parent: the parent port_info object
 * @expander: the expander port_info object
 **/
अटल व्योम
mptsas_delete_expander_siblings(MPT_ADAPTER *ioc, काष्ठा mptsas_portinfo
    *parent, काष्ठा mptsas_portinfo *expander)
अणु
	काष्ठा mptsas_phyinfo *phy_info;
	काष्ठा mptsas_portinfo *port_info;
	काष्ठा sas_rphy *rphy;
	पूर्णांक i;

	phy_info = expander->phy_info;
	क्रम (i = 0; i < expander->num_phys; i++, phy_info++) अणु
		rphy = mptsas_get_rphy(phy_info);
		अगर (!rphy)
			जारी;
		अगर (rphy->identअगरy.device_type == SAS_END_DEVICE)
			mptsas_del_end_device(ioc, phy_info);
	पूर्ण

	phy_info = expander->phy_info;
	क्रम (i = 0; i < expander->num_phys; i++, phy_info++) अणु
		rphy = mptsas_get_rphy(phy_info);
		अगर (!rphy)
			जारी;
		अगर (rphy->identअगरy.device_type ==
		    MPI_SAS_DEVICE_INFO_EDGE_EXPANDER ||
		    rphy->identअगरy.device_type ==
		    MPI_SAS_DEVICE_INFO_FANOUT_EXPANDER) अणु
			port_info = mptsas_find_portinfo_by_sas_address(ioc,
			    rphy->identअगरy.sas_address);
			अगर (!port_info)
				जारी;
			अगर (port_info == parent) /* backlink rphy */
				जारी;
			/*
			Delete this expander even अगर the expdevpage is exists
			because the parent expander is alपढ़ोy deleted
			*/
			mptsas_expander_delete(ioc, port_info, 1);
		पूर्ण
	पूर्ण
पूर्ण


/**
 *	mptsas_expander_delete - हटाओ this expander
 *	@ioc: Poपूर्णांकer to MPT_ADAPTER काष्ठाure
 *	@port_info: expander port_info काष्ठा
 *	@क्रमce: Flag to क्रमcefully delete the expander
 *
 **/

अटल व्योम mptsas_expander_delete(MPT_ADAPTER *ioc,
		काष्ठा mptsas_portinfo *port_info, u8 क्रमce)
अणु

	काष्ठा mptsas_portinfo *parent;
	पूर्णांक		i;
	u64		expander_sas_address;
	काष्ठा mptsas_phyinfo *phy_info;
	काष्ठा mptsas_portinfo buffer;
	काष्ठा mptsas_portinfo_details *port_details;
	काष्ठा sas_port *port;

	अगर (!port_info)
		वापस;

	/* see अगर expander is still there beक्रमe deleting */
	mptsas_sas_expander_pg0(ioc, &buffer,
	    (MPI_SAS_EXPAND_PGAD_FORM_HANDLE <<
	    MPI_SAS_EXPAND_PGAD_FORM_SHIFT),
	    port_info->phy_info[0].identअगरy.handle);

	अगर (buffer.num_phys) अणु
		kमुक्त(buffer.phy_info);
		अगर (!क्रमce)
			वापस;
	पूर्ण


	/*
	 * Obtain the port_info instance to the parent port
	 */
	port_details = शून्य;
	expander_sas_address =
	    port_info->phy_info[0].identअगरy.sas_address;
	parent = mptsas_find_portinfo_by_handle(ioc,
	    port_info->phy_info[0].identअगरy.handle_parent);
	mptsas_delete_expander_siblings(ioc, parent, port_info);
	अगर (!parent)
		जाओ out;

	/*
	 * Delete rphys in the parent that poपूर्णांक
	 * to this expander.
	 */
	phy_info = parent->phy_info;
	port = शून्य;
	क्रम (i = 0; i < parent->num_phys; i++, phy_info++) अणु
		अगर (!phy_info->phy)
			जारी;
		अगर (phy_info->attached.sas_address !=
		    expander_sas_address)
			जारी;
		अगर (!port) अणु
			port = mptsas_get_port(phy_info);
			port_details = phy_info->port_details;
		पूर्ण
		dev_prपूर्णांकk(KERN_DEBUG, &phy_info->phy->dev,
		    MYIOC_s_FMT "delete phy %d, phy-obj (0x%p)\n", ioc->name,
		    phy_info->phy_id, phy_info->phy);
		sas_port_delete_phy(port, phy_info->phy);
	पूर्ण
	अगर (port) अणु
		dev_prपूर्णांकk(KERN_DEBUG, &port->dev,
		    MYIOC_s_FMT "delete port %d, sas_addr (0x%llx)\n",
		    ioc->name, port->port_identअगरier,
		    (अचिन्हित दीर्घ दीर्घ)expander_sas_address);
		sas_port_delete(port);
		mptsas_port_delete(ioc, port_details);
	पूर्ण
 out:

	prपूर्णांकk(MYIOC_s_INFO_FMT "delete expander: num_phys %d, "
	    "sas_addr (0x%llx)\n",  ioc->name, port_info->num_phys,
	    (अचिन्हित दीर्घ दीर्घ)expander_sas_address);

	/*
	 * मुक्त link
	 */
	list_del(&port_info->list);
	kमुक्त(port_info->phy_info);
	kमुक्त(port_info);
पूर्ण


/**
 * mptsas_send_expander_event - expanders events
 * @ioc: Poपूर्णांकer to MPT_ADAPTER काष्ठाure
 * @expander_data: event data
 *
 *
 * This function handles adding, removing, and refreshing
 * device handles within the expander objects.
 */
अटल व्योम
mptsas_send_expander_event(काष्ठा fw_event_work *fw_event)
अणु
	MPT_ADAPTER *ioc;
	MpiEventDataSasExpanderStatusChange_t *expander_data;
	काष्ठा mptsas_portinfo *port_info;
	__le64 sas_address;
	पूर्णांक i;

	ioc = fw_event->ioc;
	expander_data = (MpiEventDataSasExpanderStatusChange_t *)
	    fw_event->event_data;
	स_नकल(&sas_address, &expander_data->SASAddress, माप(__le64));
	sas_address = le64_to_cpu(sas_address);
	port_info = mptsas_find_portinfo_by_sas_address(ioc, sas_address);

	अगर (expander_data->ReasonCode == MPI_EVENT_SAS_EXP_RC_ADDED) अणु
		अगर (port_info) अणु
			क्रम (i = 0; i < port_info->num_phys; i++) अणु
				port_info->phy_info[i].portinfo = port_info;
				port_info->phy_info[i].handle =
				    le16_to_cpu(expander_data->DevHandle);
				port_info->phy_info[i].identअगरy.sas_address =
				    le64_to_cpu(sas_address);
				port_info->phy_info[i].identअगरy.handle_parent =
				    le16_to_cpu(expander_data->ParentDevHandle);
			पूर्ण
			mptsas_expander_refresh(ioc, port_info);
		पूर्ण अन्यथा अगर (!port_info && expander_data->NumPhys)
			mptsas_expander_event_add(ioc, expander_data);
	पूर्ण अन्यथा अगर (expander_data->ReasonCode ==
	    MPI_EVENT_SAS_EXP_RC_NOT_RESPONDING)
		mptsas_expander_delete(ioc, port_info, 0);

	mptsas_मुक्त_fw_event(ioc, fw_event);
पूर्ण


/**
 * mptsas_expander_add -
 * @ioc: Poपूर्णांकer to MPT_ADAPTER काष्ठाure
 * @handle:
 *
 */
अटल काष्ठा mptsas_portinfo *
mptsas_expander_add(MPT_ADAPTER *ioc, u16 handle)
अणु
	काष्ठा mptsas_portinfo buffer, *port_info;
	पूर्णांक i;

	अगर ((mptsas_sas_expander_pg0(ioc, &buffer,
	    (MPI_SAS_EXPAND_PGAD_FORM_HANDLE <<
	    MPI_SAS_EXPAND_PGAD_FORM_SHIFT), handle)))
		वापस शून्य;

	port_info = kzalloc(माप(काष्ठा mptsas_portinfo), GFP_ATOMIC);
	अगर (!port_info) अणु
		dfailprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_ERR_FMT
		"%s: exit at line=%d\n", ioc->name,
		__func__, __LINE__));
		वापस शून्य;
	पूर्ण
	port_info->num_phys = buffer.num_phys;
	port_info->phy_info = buffer.phy_info;
	क्रम (i = 0; i < port_info->num_phys; i++)
		port_info->phy_info[i].portinfo = port_info;
	mutex_lock(&ioc->sas_topology_mutex);
	list_add_tail(&port_info->list, &ioc->sas_topology);
	mutex_unlock(&ioc->sas_topology_mutex);
	prपूर्णांकk(MYIOC_s_INFO_FMT "add expander: num_phys %d, "
	    "sas_addr (0x%llx)\n", ioc->name, port_info->num_phys,
	    (अचिन्हित दीर्घ दीर्घ)buffer.phy_info[0].identअगरy.sas_address);
	mptsas_expander_refresh(ioc, port_info);
	वापस port_info;
पूर्ण

अटल व्योम
mptsas_send_link_status_event(काष्ठा fw_event_work *fw_event)
अणु
	MPT_ADAPTER *ioc;
	MpiEventDataSasPhyLinkStatus_t *link_data;
	काष्ठा mptsas_portinfo *port_info;
	काष्ठा mptsas_phyinfo *phy_info = शून्य;
	__le64 sas_address;
	u8 phy_num;
	u8 link_rate;

	ioc = fw_event->ioc;
	link_data = (MpiEventDataSasPhyLinkStatus_t *)fw_event->event_data;

	स_नकल(&sas_address, &link_data->SASAddress, माप(__le64));
	sas_address = le64_to_cpu(sas_address);
	link_rate = link_data->LinkRates >> 4;
	phy_num = link_data->PhyNum;

	port_info = mptsas_find_portinfo_by_sas_address(ioc, sas_address);
	अगर (port_info) अणु
		phy_info = &port_info->phy_info[phy_num];
		अगर (phy_info)
			phy_info->negotiated_link_rate = link_rate;
	पूर्ण

	अगर (link_rate == MPI_SAS_IOUNIT0_RATE_1_5 ||
	    link_rate == MPI_SAS_IOUNIT0_RATE_3_0 ||
	    link_rate == MPI_SAS_IOUNIT0_RATE_6_0) अणु

		अगर (!port_info) अणु
			अगर (ioc->old_sas_discovery_protocal) अणु
				port_info = mptsas_expander_add(ioc,
					le16_to_cpu(link_data->DevHandle));
				अगर (port_info)
					जाओ out;
			पूर्ण
			जाओ out;
		पूर्ण

		अगर (port_info == ioc->hba_port_info)
			mptsas_probe_hba_phys(ioc);
		अन्यथा
			mptsas_expander_refresh(ioc, port_info);
	पूर्ण अन्यथा अगर (phy_info && phy_info->phy) अणु
		अगर (link_rate ==  MPI_SAS_IOUNIT0_RATE_PHY_DISABLED)
			phy_info->phy->negotiated_linkrate =
			    SAS_PHY_DISABLED;
		अन्यथा अगर (link_rate ==
		    MPI_SAS_IOUNIT0_RATE_FAILED_SPEED_NEGOTIATION)
			phy_info->phy->negotiated_linkrate =
			    SAS_LINK_RATE_FAILED;
		अन्यथा अणु
			phy_info->phy->negotiated_linkrate =
			    SAS_LINK_RATE_UNKNOWN;
			अगर (ioc->device_missing_delay &&
			    mptsas_is_end_device(&phy_info->attached)) अणु
				काष्ठा scsi_device		*sdev;
				VirtDevice			*vdevice;
				u8	channel, id;
				id = phy_info->attached.id;
				channel = phy_info->attached.channel;
				devtprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT
				"Link down for fw_id %d:fw_channel %d\n",
				    ioc->name, phy_info->attached.id,
				    phy_info->attached.channel));

				shost_क्रम_each_device(sdev, ioc->sh) अणु
					vdevice = sdev->hostdata;
					अगर ((vdevice == शून्य) ||
						(vdevice->vtarget == शून्य))
						जारी;
					अगर ((vdevice->vtarget->tflags &
					    MPT_TARGET_FLAGS_RAID_COMPONENT ||
					    vdevice->vtarget->raidVolume))
						जारी;
					अगर (vdevice->vtarget->id == id &&
						vdevice->vtarget->channel ==
						channel)
						devtprपूर्णांकk(ioc,
						prपूर्णांकk(MYIOC_s_DEBUG_FMT
						"SDEV OUTSTANDING CMDS"
						"%d\n", ioc->name,
						scsi_device_busy(sdev)));
				पूर्ण

			पूर्ण
		पूर्ण
	पूर्ण
 out:
	mptsas_मुक्त_fw_event(ioc, fw_event);
पूर्ण

अटल व्योम
mptsas_not_responding_devices(MPT_ADAPTER *ioc)
अणु
	काष्ठा mptsas_portinfo buffer, *port_info;
	काष्ठा mptsas_device_info	*sas_info;
	काष्ठा mptsas_devinfo sas_device;
	u32	handle;
	VirtTarget *vtarget = शून्य;
	काष्ठा mptsas_phyinfo *phy_info;
	u8 found_expander;
	पूर्णांक retval, retry_count;
	अचिन्हित दीर्घ flags;

	mpt_findImVolumes(ioc);

	spin_lock_irqsave(&ioc->taskmgmt_lock, flags);
	अगर (ioc->ioc_reset_in_progress) अणु
		dfailprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT
		   "%s: exiting due to a parallel reset \n", ioc->name,
		    __func__));
		spin_unlock_irqrestore(&ioc->taskmgmt_lock, flags);
		वापस;
	पूर्ण
	spin_unlock_irqrestore(&ioc->taskmgmt_lock, flags);

	/* devices, logical volumes */
	mutex_lock(&ioc->sas_device_info_mutex);
 reकरो_device_scan:
	list_क्रम_each_entry(sas_info, &ioc->sas_device_info_list, list) अणु
		अगर (sas_info->is_cached)
			जारी;
		अगर (!sas_info->is_logical_volume) अणु
			sas_device.handle = 0;
			retry_count = 0;
retry_page:
			retval = mptsas_sas_device_pg0(ioc, &sas_device,
				(MPI_SAS_DEVICE_PGAD_FORM_BUS_TARGET_ID
				<< MPI_SAS_DEVICE_PGAD_FORM_SHIFT),
				(sas_info->fw.channel << 8) +
				sas_info->fw.id);

			अगर (sas_device.handle)
				जारी;
			अगर (retval == -EBUSY) अणु
				spin_lock_irqsave(&ioc->taskmgmt_lock, flags);
				अगर (ioc->ioc_reset_in_progress) अणु
					dfailprपूर्णांकk(ioc,
					prपूर्णांकk(MYIOC_s_DEBUG_FMT
					"%s: exiting due to reset\n",
					ioc->name, __func__));
					spin_unlock_irqrestore
					(&ioc->taskmgmt_lock, flags);
					mutex_unlock(&ioc->
					sas_device_info_mutex);
					वापस;
				पूर्ण
				spin_unlock_irqrestore(&ioc->taskmgmt_lock,
				flags);
			पूर्ण

			अगर (retval && (retval != -ENODEV)) अणु
				अगर (retry_count < 10) अणु
					retry_count++;
					जाओ retry_page;
				पूर्ण अन्यथा अणु
					devtprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT
					"%s: Config page retry exceeded retry "
					"count deleting device 0x%llx\n",
					ioc->name, __func__,
					sas_info->sas_address));
				पूर्ण
			पूर्ण

			/* delete device */
			vtarget = mptsas_find_vtarget(ioc,
				sas_info->fw.channel, sas_info->fw.id);

			अगर (vtarget)
				vtarget->deleted = 1;

			phy_info = mptsas_find_phyinfo_by_sas_address(ioc,
					sas_info->sas_address);

			mptsas_del_end_device(ioc, phy_info);
			जाओ reकरो_device_scan;
		पूर्ण अन्यथा
			mptsas_volume_delete(ioc, sas_info->fw.id);
	पूर्ण
	mutex_unlock(&ioc->sas_device_info_mutex);

	/* expanders */
	mutex_lock(&ioc->sas_topology_mutex);
 reकरो_expander_scan:
	list_क्रम_each_entry(port_info, &ioc->sas_topology, list) अणु

		अगर (!(port_info->phy_info[0].identअगरy.device_info &
		    MPI_SAS_DEVICE_INFO_SMP_TARGET))
			जारी;
		found_expander = 0;
		handle = 0xFFFF;
		जबतक (!mptsas_sas_expander_pg0(ioc, &buffer,
		    (MPI_SAS_EXPAND_PGAD_FORM_GET_NEXT_HANDLE <<
		     MPI_SAS_EXPAND_PGAD_FORM_SHIFT), handle) &&
		    !found_expander) अणु

			handle = buffer.phy_info[0].handle;
			अगर (buffer.phy_info[0].identअगरy.sas_address ==
			    port_info->phy_info[0].identअगरy.sas_address) अणु
				found_expander = 1;
			पूर्ण
			kमुक्त(buffer.phy_info);
		पूर्ण

		अगर (!found_expander) अणु
			mptsas_expander_delete(ioc, port_info, 0);
			जाओ reकरो_expander_scan;
		पूर्ण
	पूर्ण
	mutex_unlock(&ioc->sas_topology_mutex);
पूर्ण

/**
 *	mptsas_probe_expanders - adding expanders
 *	@ioc: Poपूर्णांकer to MPT_ADAPTER काष्ठाure
 *
 **/
अटल व्योम
mptsas_probe_expanders(MPT_ADAPTER *ioc)
अणु
	काष्ठा mptsas_portinfo buffer, *port_info;
	u32 			handle;
	पूर्णांक i;

	handle = 0xFFFF;
	जबतक (!mptsas_sas_expander_pg0(ioc, &buffer,
	    (MPI_SAS_EXPAND_PGAD_FORM_GET_NEXT_HANDLE <<
	     MPI_SAS_EXPAND_PGAD_FORM_SHIFT), handle)) अणु

		handle = buffer.phy_info[0].handle;
		port_info = mptsas_find_portinfo_by_sas_address(ioc,
		    buffer.phy_info[0].identअगरy.sas_address);

		अगर (port_info) अणु
			/* refreshing handles */
			क्रम (i = 0; i < buffer.num_phys; i++) अणु
				port_info->phy_info[i].handle = handle;
				port_info->phy_info[i].identअगरy.handle_parent =
				    buffer.phy_info[0].identअगरy.handle_parent;
			पूर्ण
			mptsas_expander_refresh(ioc, port_info);
			kमुक्त(buffer.phy_info);
			जारी;
		पूर्ण

		port_info = kzalloc(माप(काष्ठा mptsas_portinfo), GFP_KERNEL);
		अगर (!port_info) अणु
			dfailprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_ERR_FMT
			"%s: exit at line=%d\n", ioc->name,
			__func__, __LINE__));
			वापस;
		पूर्ण
		port_info->num_phys = buffer.num_phys;
		port_info->phy_info = buffer.phy_info;
		क्रम (i = 0; i < port_info->num_phys; i++)
			port_info->phy_info[i].portinfo = port_info;
		mutex_lock(&ioc->sas_topology_mutex);
		list_add_tail(&port_info->list, &ioc->sas_topology);
		mutex_unlock(&ioc->sas_topology_mutex);
		prपूर्णांकk(MYIOC_s_INFO_FMT "add expander: num_phys %d, "
		    "sas_addr (0x%llx)\n", ioc->name, port_info->num_phys,
	    (अचिन्हित दीर्घ दीर्घ)buffer.phy_info[0].identअगरy.sas_address);
		mptsas_expander_refresh(ioc, port_info);
	पूर्ण
पूर्ण

अटल व्योम
mptsas_probe_devices(MPT_ADAPTER *ioc)
अणु
	u16 handle;
	काष्ठा mptsas_devinfo sas_device;
	काष्ठा mptsas_phyinfo *phy_info;

	handle = 0xFFFF;
	जबतक (!(mptsas_sas_device_pg0(ioc, &sas_device,
	    MPI_SAS_DEVICE_PGAD_FORM_GET_NEXT_HANDLE, handle))) अणु

		handle = sas_device.handle;

		अगर ((sas_device.device_info &
		     (MPI_SAS_DEVICE_INFO_SSP_TARGET |
		      MPI_SAS_DEVICE_INFO_STP_TARGET |
		      MPI_SAS_DEVICE_INFO_SATA_DEVICE)) == 0)
			जारी;

		/* If there is no FW B_T mapping क्रम this device then जारी
		 * */
		अगर (!(sas_device.flags & MPI_SAS_DEVICE0_FLAGS_DEVICE_PRESENT)
			|| !(sas_device.flags &
			MPI_SAS_DEVICE0_FLAGS_DEVICE_MAPPED))
			जारी;

		phy_info = mptsas_refreshing_device_handles(ioc, &sas_device);
		अगर (!phy_info)
			जारी;

		अगर (mptsas_get_rphy(phy_info))
			जारी;

		mptsas_add_end_device(ioc, phy_info);
	पूर्ण
पूर्ण

/**
 *	mptsas_scan_sas_topology -
 *	@ioc: Poपूर्णांकer to MPT_ADAPTER काष्ठाure
 *	@sas_address:
 *
 **/
अटल व्योम
mptsas_scan_sas_topology(MPT_ADAPTER *ioc)
अणु
	काष्ठा scsi_device *sdev;
	पूर्णांक i;

	mptsas_probe_hba_phys(ioc);
	mptsas_probe_expanders(ioc);
	mptsas_probe_devices(ioc);

	/*
	  Reporting RAID volumes.
	*/
	अगर (!ioc->ir_firmware || !ioc->raid_data.pIocPg2 ||
	    !ioc->raid_data.pIocPg2->NumActiveVolumes)
		वापस;
	क्रम (i = 0; i < ioc->raid_data.pIocPg2->NumActiveVolumes; i++) अणु
		sdev = scsi_device_lookup(ioc->sh, MPTSAS_RAID_CHANNEL,
		    ioc->raid_data.pIocPg2->RaidVolume[i].VolumeID, 0);
		अगर (sdev) अणु
			scsi_device_put(sdev);
			जारी;
		पूर्ण
		prपूर्णांकk(MYIOC_s_INFO_FMT "attaching raid volume, channel %d, "
		    "id %d\n", ioc->name, MPTSAS_RAID_CHANNEL,
		    ioc->raid_data.pIocPg2->RaidVolume[i].VolumeID);
		scsi_add_device(ioc->sh, MPTSAS_RAID_CHANNEL,
		    ioc->raid_data.pIocPg2->RaidVolume[i].VolumeID, 0);
	पूर्ण
पूर्ण


अटल व्योम
mptsas_handle_queue_full_event(काष्ठा fw_event_work *fw_event)
अणु
	MPT_ADAPTER *ioc;
	EventDataQueueFull_t *qfull_data;
	काष्ठा mptsas_device_info *sas_info;
	काष्ठा scsi_device	*sdev;
	पूर्णांक depth;
	पूर्णांक id = -1;
	पूर्णांक channel = -1;
	पूर्णांक fw_id, fw_channel;
	u16 current_depth;


	ioc = fw_event->ioc;
	qfull_data = (EventDataQueueFull_t *)fw_event->event_data;
	fw_id = qfull_data->TargetID;
	fw_channel = qfull_data->Bus;
	current_depth = le16_to_cpu(qfull_data->CurrentDepth);

	/* अगर hidden raid component, look क्रम the volume id */
	mutex_lock(&ioc->sas_device_info_mutex);
	अगर (mptscsih_is_phys_disk(ioc, fw_channel, fw_id)) अणु
		list_क्रम_each_entry(sas_info, &ioc->sas_device_info_list,
		    list) अणु
			अगर (sas_info->is_cached ||
			    sas_info->is_logical_volume)
				जारी;
			अगर (sas_info->is_hidden_raid_component &&
			    (sas_info->fw.channel == fw_channel &&
			    sas_info->fw.id == fw_id)) अणु
				id = sas_info->volume_id;
				channel = MPTSAS_RAID_CHANNEL;
				जाओ out;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		list_क्रम_each_entry(sas_info, &ioc->sas_device_info_list,
		    list) अणु
			अगर (sas_info->is_cached ||
			    sas_info->is_hidden_raid_component ||
			    sas_info->is_logical_volume)
				जारी;
			अगर (sas_info->fw.channel == fw_channel &&
			    sas_info->fw.id == fw_id) अणु
				id = sas_info->os.id;
				channel = sas_info->os.channel;
				जाओ out;
			पूर्ण
		पूर्ण

	पूर्ण

 out:
	mutex_unlock(&ioc->sas_device_info_mutex);

	अगर (id != -1) अणु
		shost_क्रम_each_device(sdev, ioc->sh) अणु
			अगर (sdev->id == id && sdev->channel == channel) अणु
				अगर (current_depth > sdev->queue_depth) अणु
					sdev_prपूर्णांकk(KERN_INFO, sdev,
					    "strange observation, the queue "
					    "depth is (%d) meanwhile fw queue "
					    "depth (%d)\n", sdev->queue_depth,
					    current_depth);
					जारी;
				पूर्ण
				depth = scsi_track_queue_full(sdev,
					sdev->queue_depth - 1);
				अगर (depth > 0)
					sdev_prपूर्णांकk(KERN_INFO, sdev,
					"Queue depth reduced to (%d)\n",
					   depth);
				अन्यथा अगर (depth < 0)
					sdev_prपूर्णांकk(KERN_INFO, sdev,
					"Tagged Command Queueing is being "
					"disabled\n");
				अन्यथा अगर (depth == 0)
					sdev_prपूर्णांकk(KERN_DEBUG, sdev,
					"Queue depth not changed yet\n");
			पूर्ण
		पूर्ण
	पूर्ण

	mptsas_मुक्त_fw_event(ioc, fw_event);
पूर्ण


अटल काष्ठा mptsas_phyinfo *
mptsas_find_phyinfo_by_sas_address(MPT_ADAPTER *ioc, u64 sas_address)
अणु
	काष्ठा mptsas_portinfo *port_info;
	काष्ठा mptsas_phyinfo *phy_info = शून्य;
	पूर्णांक i;

	mutex_lock(&ioc->sas_topology_mutex);
	list_क्रम_each_entry(port_info, &ioc->sas_topology, list) अणु
		क्रम (i = 0; i < port_info->num_phys; i++) अणु
			अगर (!mptsas_is_end_device(
				&port_info->phy_info[i].attached))
				जारी;
			अगर (port_info->phy_info[i].attached.sas_address
			    != sas_address)
				जारी;
			phy_info = &port_info->phy_info[i];
			अवरोध;
		पूर्ण
	पूर्ण
	mutex_unlock(&ioc->sas_topology_mutex);
	वापस phy_info;
पूर्ण

/**
 *	mptsas_find_phyinfo_by_phys_disk_num -
 *	@ioc: Poपूर्णांकer to MPT_ADAPTER काष्ठाure
 *	@phys_disk_num:
 *	@channel:
 *	@id:
 *
 **/
अटल काष्ठा mptsas_phyinfo *
mptsas_find_phyinfo_by_phys_disk_num(MPT_ADAPTER *ioc, u8 phys_disk_num,
	u8 channel, u8 id)
अणु
	काष्ठा mptsas_phyinfo *phy_info = शून्य;
	काष्ठा mptsas_portinfo *port_info;
	RaidPhysDiskPage1_t *phys_disk = शून्य;
	पूर्णांक num_paths;
	u64 sas_address = 0;
	पूर्णांक i;

	phy_info = शून्य;
	अगर (!ioc->raid_data.pIocPg3)
		वापस शून्य;
	/* dual port support */
	num_paths = mpt_raid_phys_disk_get_num_paths(ioc, phys_disk_num);
	अगर (!num_paths)
		जाओ out;
	phys_disk = kzalloc(दुरत्व(RaidPhysDiskPage1_t, Path) +
	   (num_paths * माप(RAID_PHYS_DISK1_PATH)), GFP_KERNEL);
	अगर (!phys_disk)
		जाओ out;
	mpt_raid_phys_disk_pg1(ioc, phys_disk_num, phys_disk);
	क्रम (i = 0; i < num_paths; i++) अणु
		अगर ((phys_disk->Path[i].Flags & 1) != 0)
			/* entry no दीर्घer valid */
			जारी;
		अगर ((id == phys_disk->Path[i].PhysDiskID) &&
		    (channel == phys_disk->Path[i].PhysDiskBus)) अणु
			स_नकल(&sas_address, &phys_disk->Path[i].WWID,
				माप(u64));
			phy_info = mptsas_find_phyinfo_by_sas_address(ioc,
					sas_address);
			जाओ out;
		पूर्ण
	पूर्ण

 out:
	kमुक्त(phys_disk);
	अगर (phy_info)
		वापस phy_info;

	/*
	 * Extra code to handle RAID0 हाल, where the sas_address is not updated
	 * in phys_disk_page_1 when hotswapped
	 */
	mutex_lock(&ioc->sas_topology_mutex);
	list_क्रम_each_entry(port_info, &ioc->sas_topology, list) अणु
		क्रम (i = 0; i < port_info->num_phys && !phy_info; i++) अणु
			अगर (!mptsas_is_end_device(
				&port_info->phy_info[i].attached))
				जारी;
			अगर (port_info->phy_info[i].attached.phys_disk_num == ~0)
				जारी;
			अगर ((port_info->phy_info[i].attached.phys_disk_num ==
			    phys_disk_num) &&
			    (port_info->phy_info[i].attached.id == id) &&
			    (port_info->phy_info[i].attached.channel ==
			     channel))
				phy_info = &port_info->phy_info[i];
		पूर्ण
	पूर्ण
	mutex_unlock(&ioc->sas_topology_mutex);
	वापस phy_info;
पूर्ण

अटल व्योम
mptsas_reprobe_lun(काष्ठा scsi_device *sdev, व्योम *data)
अणु
	पूर्णांक rc;

	sdev->no_uld_attach = data ? 1 : 0;
	rc = scsi_device_reprobe(sdev);
पूर्ण

अटल व्योम
mptsas_reprobe_target(काष्ठा scsi_target *starget, पूर्णांक uld_attach)
अणु
	starget_क्रम_each_device(starget, uld_attach ? (व्योम *)1 : शून्य,
			mptsas_reprobe_lun);
पूर्ण

अटल व्योम
mptsas_adding_inactive_raid_components(MPT_ADAPTER *ioc, u8 channel, u8 id)
अणु
	CONFIGPARMS			cfg;
	ConfigPageHeader_t		hdr;
	dma_addr_t			dma_handle;
	pRaidVolumePage0_t		buffer = शून्य;
	RaidPhysDiskPage0_t 		phys_disk;
	पूर्णांक				i;
	काष्ठा mptsas_phyinfo	*phy_info;
	काष्ठा mptsas_devinfo		sas_device;

	स_रखो(&cfg, 0 , माप(CONFIGPARMS));
	स_रखो(&hdr, 0 , माप(ConfigPageHeader_t));
	hdr.PageType = MPI_CONFIG_PAGETYPE_RAID_VOLUME;
	cfg.pageAddr = (channel << 8) + id;
	cfg.cfghdr.hdr = &hdr;
	cfg.action = MPI_CONFIG_ACTION_PAGE_HEADER;
	cfg.समयout = SAS_CONFIG_PAGE_TIMEOUT;

	अगर (mpt_config(ioc, &cfg) != 0)
		जाओ out;

	अगर (!hdr.PageLength)
		जाओ out;

	buffer = pci_alloc_consistent(ioc->pcidev, hdr.PageLength * 4,
	    &dma_handle);

	अगर (!buffer)
		जाओ out;

	cfg.physAddr = dma_handle;
	cfg.action = MPI_CONFIG_ACTION_PAGE_READ_CURRENT;

	अगर (mpt_config(ioc, &cfg) != 0)
		जाओ out;

	अगर (!(buffer->VolumeStatus.Flags &
	    MPI_RAIDVOL0_STATUS_FLAG_VOLUME_INACTIVE))
		जाओ out;

	अगर (!buffer->NumPhysDisks)
		जाओ out;

	क्रम (i = 0; i < buffer->NumPhysDisks; i++) अणु

		अगर (mpt_raid_phys_disk_pg0(ioc,
		    buffer->PhysDisk[i].PhysDiskNum, &phys_disk) != 0)
			जारी;

		अगर (mptsas_sas_device_pg0(ioc, &sas_device,
		    (MPI_SAS_DEVICE_PGAD_FORM_BUS_TARGET_ID <<
		     MPI_SAS_DEVICE_PGAD_FORM_SHIFT),
			(phys_disk.PhysDiskBus << 8) +
			phys_disk.PhysDiskID))
			जारी;

		/* If there is no FW B_T mapping क्रम this device then जारी
		 * */
		अगर (!(sas_device.flags & MPI_SAS_DEVICE0_FLAGS_DEVICE_PRESENT)
			|| !(sas_device.flags &
			MPI_SAS_DEVICE0_FLAGS_DEVICE_MAPPED))
			जारी;


		phy_info = mptsas_find_phyinfo_by_sas_address(ioc,
		    sas_device.sas_address);
		mptsas_add_end_device(ioc, phy_info);
	पूर्ण

 out:
	अगर (buffer)
		pci_मुक्त_consistent(ioc->pcidev, hdr.PageLength * 4, buffer,
		    dma_handle);
पूर्ण
/*
 * Work queue thपढ़ो to handle SAS hotplug events
 */
अटल व्योम
mptsas_hotplug_work(MPT_ADAPTER *ioc, काष्ठा fw_event_work *fw_event,
    काष्ठा mptsas_hotplug_event *hot_plug_info)
अणु
	काष्ठा mptsas_phyinfo *phy_info;
	काष्ठा scsi_target * starget;
	काष्ठा mptsas_devinfo sas_device;
	VirtTarget *vtarget;
	पूर्णांक i;
	काष्ठा mptsas_portinfo *port_info;

	चयन (hot_plug_info->event_type) अणु

	हाल MPTSAS_ADD_PHYSDISK:

		अगर (!ioc->raid_data.pIocPg2)
			अवरोध;

		क्रम (i = 0; i < ioc->raid_data.pIocPg2->NumActiveVolumes; i++) अणु
			अगर (ioc->raid_data.pIocPg2->RaidVolume[i].VolumeID ==
			    hot_plug_info->id) अणु
				prपूर्णांकk(MYIOC_s_WARN_FMT "firmware bug: unable "
				    "to add hidden disk - target_id matches "
				    "volume_id\n", ioc->name);
				mptsas_मुक्त_fw_event(ioc, fw_event);
				वापस;
			पूर्ण
		पूर्ण
		mpt_findImVolumes(ioc);
		fallthrough;

	हाल MPTSAS_ADD_DEVICE:
		स_रखो(&sas_device, 0, माप(काष्ठा mptsas_devinfo));
		mptsas_sas_device_pg0(ioc, &sas_device,
		    (MPI_SAS_DEVICE_PGAD_FORM_BUS_TARGET_ID <<
		    MPI_SAS_DEVICE_PGAD_FORM_SHIFT),
		    (hot_plug_info->channel << 8) +
		    hot_plug_info->id);

		/* If there is no FW B_T mapping क्रम this device then अवरोध
		 * */
		अगर (!(sas_device.flags & MPI_SAS_DEVICE0_FLAGS_DEVICE_PRESENT)
			|| !(sas_device.flags &
			MPI_SAS_DEVICE0_FLAGS_DEVICE_MAPPED))
			अवरोध;

		अगर (!sas_device.handle)
			वापस;

		phy_info = mptsas_refreshing_device_handles(ioc, &sas_device);
		/* Device hot plug */
		अगर (!phy_info) अणु
			devtprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT
				"%s %d HOT PLUG: "
				"parent handle of device %x\n", ioc->name,
				__func__, __LINE__, sas_device.handle_parent));
			port_info = mptsas_find_portinfo_by_handle(ioc,
				sas_device.handle_parent);

			अगर (port_info == ioc->hba_port_info)
				mptsas_probe_hba_phys(ioc);
			अन्यथा अगर (port_info)
				mptsas_expander_refresh(ioc, port_info);
			अन्यथा अणु
				dfailprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_ERR_FMT
					"%s %d port info is NULL\n",
					ioc->name, __func__, __LINE__));
				अवरोध;
			पूर्ण
			phy_info = mptsas_refreshing_device_handles
				(ioc, &sas_device);
		पूर्ण

		अगर (!phy_info) अणु
			dfailprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_ERR_FMT
				"%s %d phy info is NULL\n",
				ioc->name, __func__, __LINE__));
			अवरोध;
		पूर्ण

		अगर (mptsas_get_rphy(phy_info))
			अवरोध;

		mptsas_add_end_device(ioc, phy_info);
		अवरोध;

	हाल MPTSAS_DEL_DEVICE:
		phy_info = mptsas_find_phyinfo_by_sas_address(ioc,
		    hot_plug_info->sas_address);
		mptsas_del_end_device(ioc, phy_info);
		अवरोध;

	हाल MPTSAS_DEL_PHYSDISK:

		mpt_findImVolumes(ioc);

		phy_info = mptsas_find_phyinfo_by_phys_disk_num(
				ioc, hot_plug_info->phys_disk_num,
				hot_plug_info->channel,
				hot_plug_info->id);
		mptsas_del_end_device(ioc, phy_info);
		अवरोध;

	हाल MPTSAS_ADD_PHYSDISK_REPROBE:

		अगर (mptsas_sas_device_pg0(ioc, &sas_device,
		    (MPI_SAS_DEVICE_PGAD_FORM_BUS_TARGET_ID <<
		     MPI_SAS_DEVICE_PGAD_FORM_SHIFT),
		    (hot_plug_info->channel << 8) + hot_plug_info->id)) अणु
			dfailprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_ERR_FMT
			"%s: fw_id=%d exit at line=%d\n", ioc->name,
				 __func__, hot_plug_info->id, __LINE__));
			अवरोध;
		पूर्ण

		/* If there is no FW B_T mapping क्रम this device then अवरोध
		 * */
		अगर (!(sas_device.flags & MPI_SAS_DEVICE0_FLAGS_DEVICE_PRESENT)
			|| !(sas_device.flags &
			MPI_SAS_DEVICE0_FLAGS_DEVICE_MAPPED))
			अवरोध;

		phy_info = mptsas_find_phyinfo_by_sas_address(
		    ioc, sas_device.sas_address);

		अगर (!phy_info) अणु
			dfailprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_ERR_FMT
				"%s: fw_id=%d exit at line=%d\n", ioc->name,
				 __func__, hot_plug_info->id, __LINE__));
			अवरोध;
		पूर्ण

		starget = mptsas_get_starget(phy_info);
		अगर (!starget) अणु
			dfailprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_ERR_FMT
				"%s: fw_id=%d exit at line=%d\n", ioc->name,
				 __func__, hot_plug_info->id, __LINE__));
			अवरोध;
		पूर्ण

		vtarget = starget->hostdata;
		अगर (!vtarget) अणु
			dfailprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_ERR_FMT
				"%s: fw_id=%d exit at line=%d\n", ioc->name,
				 __func__, hot_plug_info->id, __LINE__));
			अवरोध;
		पूर्ण

		mpt_findImVolumes(ioc);

		starget_prपूर्णांकk(KERN_INFO, starget, MYIOC_s_FMT "RAID Hidding: "
		    "fw_channel=%d, fw_id=%d, physdsk %d, sas_addr 0x%llx\n",
		    ioc->name, hot_plug_info->channel, hot_plug_info->id,
		    hot_plug_info->phys_disk_num, (अचिन्हित दीर्घ दीर्घ)
		    sas_device.sas_address);

		vtarget->id = hot_plug_info->phys_disk_num;
		vtarget->tflags |= MPT_TARGET_FLAGS_RAID_COMPONENT;
		phy_info->attached.phys_disk_num = hot_plug_info->phys_disk_num;
		mptsas_reprobe_target(starget, 1);
		अवरोध;

	हाल MPTSAS_DEL_PHYSDISK_REPROBE:

		अगर (mptsas_sas_device_pg0(ioc, &sas_device,
		    (MPI_SAS_DEVICE_PGAD_FORM_BUS_TARGET_ID <<
		     MPI_SAS_DEVICE_PGAD_FORM_SHIFT),
			(hot_plug_info->channel << 8) + hot_plug_info->id)) अणु
				dfailprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_ERR_FMT
				    "%s: fw_id=%d exit at line=%d\n",
				    ioc->name, __func__,
				    hot_plug_info->id, __LINE__));
			अवरोध;
		पूर्ण

		/* If there is no FW B_T mapping क्रम this device then अवरोध
		 * */
		अगर (!(sas_device.flags & MPI_SAS_DEVICE0_FLAGS_DEVICE_PRESENT)
			|| !(sas_device.flags &
			MPI_SAS_DEVICE0_FLAGS_DEVICE_MAPPED))
			अवरोध;

		phy_info = mptsas_find_phyinfo_by_sas_address(ioc,
				sas_device.sas_address);
		अगर (!phy_info) अणु
			dfailprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_ERR_FMT
			    "%s: fw_id=%d exit at line=%d\n", ioc->name,
			 __func__, hot_plug_info->id, __LINE__));
			अवरोध;
		पूर्ण

		starget = mptsas_get_starget(phy_info);
		अगर (!starget) अणु
			dfailprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_ERR_FMT
			    "%s: fw_id=%d exit at line=%d\n", ioc->name,
			 __func__, hot_plug_info->id, __LINE__));
			अवरोध;
		पूर्ण

		vtarget = starget->hostdata;
		अगर (!vtarget) अणु
			dfailprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_ERR_FMT
			    "%s: fw_id=%d exit at line=%d\n", ioc->name,
			 __func__, hot_plug_info->id, __LINE__));
			अवरोध;
		पूर्ण

		अगर (!(vtarget->tflags & MPT_TARGET_FLAGS_RAID_COMPONENT)) अणु
			dfailprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_ERR_FMT
			    "%s: fw_id=%d exit at line=%d\n", ioc->name,
			 __func__, hot_plug_info->id, __LINE__));
			अवरोध;
		पूर्ण

		mpt_findImVolumes(ioc);

		starget_prपूर्णांकk(KERN_INFO, starget, MYIOC_s_FMT "RAID Exposing:"
		    " fw_channel=%d, fw_id=%d, physdsk %d, sas_addr 0x%llx\n",
		    ioc->name, hot_plug_info->channel, hot_plug_info->id,
		    hot_plug_info->phys_disk_num, (अचिन्हित दीर्घ दीर्घ)
		    sas_device.sas_address);

		vtarget->tflags &= ~MPT_TARGET_FLAGS_RAID_COMPONENT;
		vtarget->id = hot_plug_info->id;
		phy_info->attached.phys_disk_num = ~0;
		mptsas_reprobe_target(starget, 0);
		mptsas_add_device_component_by_fw(ioc,
		    hot_plug_info->channel, hot_plug_info->id);
		अवरोध;

	हाल MPTSAS_ADD_RAID:

		mpt_findImVolumes(ioc);
		prपूर्णांकk(MYIOC_s_INFO_FMT "attaching raid volume, channel %d, "
		    "id %d\n", ioc->name, MPTSAS_RAID_CHANNEL,
		    hot_plug_info->id);
		scsi_add_device(ioc->sh, MPTSAS_RAID_CHANNEL,
		    hot_plug_info->id, 0);
		अवरोध;

	हाल MPTSAS_DEL_RAID:

		mpt_findImVolumes(ioc);
		prपूर्णांकk(MYIOC_s_INFO_FMT "removing raid volume, channel %d, "
		    "id %d\n", ioc->name, MPTSAS_RAID_CHANNEL,
		    hot_plug_info->id);
		scsi_हटाओ_device(hot_plug_info->sdev);
		scsi_device_put(hot_plug_info->sdev);
		अवरोध;

	हाल MPTSAS_ADD_INACTIVE_VOLUME:

		mpt_findImVolumes(ioc);
		mptsas_adding_inactive_raid_components(ioc,
		    hot_plug_info->channel, hot_plug_info->id);
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	mptsas_मुक्त_fw_event(ioc, fw_event);
पूर्ण

अटल व्योम
mptsas_send_sas_event(काष्ठा fw_event_work *fw_event)
अणु
	MPT_ADAPTER *ioc;
	काष्ठा mptsas_hotplug_event hot_plug_info;
	EVENT_DATA_SAS_DEVICE_STATUS_CHANGE *sas_event_data;
	u32 device_info;
	u64 sas_address;

	ioc = fw_event->ioc;
	sas_event_data = (EVENT_DATA_SAS_DEVICE_STATUS_CHANGE *)
	    fw_event->event_data;
	device_info = le32_to_cpu(sas_event_data->DeviceInfo);

	अगर ((device_info &
		(MPI_SAS_DEVICE_INFO_SSP_TARGET |
		MPI_SAS_DEVICE_INFO_STP_TARGET |
		MPI_SAS_DEVICE_INFO_SATA_DEVICE)) == 0) अणु
		mptsas_मुक्त_fw_event(ioc, fw_event);
		वापस;
	पूर्ण

	अगर (sas_event_data->ReasonCode ==
		MPI_EVENT_SAS_DEV_STAT_RC_NO_PERSIST_ADDED) अणु
		mptbase_sas_persist_operation(ioc,
		MPI_SAS_OP_CLEAR_NOT_PRESENT);
		mptsas_मुक्त_fw_event(ioc, fw_event);
		वापस;
	पूर्ण

	चयन (sas_event_data->ReasonCode) अणु
	हाल MPI_EVENT_SAS_DEV_STAT_RC_NOT_RESPONDING:
	हाल MPI_EVENT_SAS_DEV_STAT_RC_ADDED:
		स_रखो(&hot_plug_info, 0, माप(काष्ठा mptsas_hotplug_event));
		hot_plug_info.handle = le16_to_cpu(sas_event_data->DevHandle);
		hot_plug_info.channel = sas_event_data->Bus;
		hot_plug_info.id = sas_event_data->TargetID;
		hot_plug_info.phy_id = sas_event_data->PhyNum;
		स_नकल(&sas_address, &sas_event_data->SASAddress,
		    माप(u64));
		hot_plug_info.sas_address = le64_to_cpu(sas_address);
		hot_plug_info.device_info = device_info;
		अगर (sas_event_data->ReasonCode &
		    MPI_EVENT_SAS_DEV_STAT_RC_ADDED)
			hot_plug_info.event_type = MPTSAS_ADD_DEVICE;
		अन्यथा
			hot_plug_info.event_type = MPTSAS_DEL_DEVICE;
		mptsas_hotplug_work(ioc, fw_event, &hot_plug_info);
		अवरोध;

	हाल MPI_EVENT_SAS_DEV_STAT_RC_NO_PERSIST_ADDED:
		mptbase_sas_persist_operation(ioc,
		    MPI_SAS_OP_CLEAR_NOT_PRESENT);
		mptsas_मुक्त_fw_event(ioc, fw_event);
		अवरोध;

	हाल MPI_EVENT_SAS_DEV_STAT_RC_SMART_DATA:
	/* TODO */
	हाल MPI_EVENT_SAS_DEV_STAT_RC_INTERNAL_DEVICE_RESET:
	/* TODO */
	शेष:
		mptsas_मुक्त_fw_event(ioc, fw_event);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम
mptsas_send_raid_event(काष्ठा fw_event_work *fw_event)
अणु
	MPT_ADAPTER *ioc;
	EVENT_DATA_RAID *raid_event_data;
	काष्ठा mptsas_hotplug_event hot_plug_info;
	पूर्णांक status;
	पूर्णांक state;
	काष्ठा scsi_device *sdev = शून्य;
	VirtDevice *vdevice = शून्य;
	RaidPhysDiskPage0_t phys_disk;

	ioc = fw_event->ioc;
	raid_event_data = (EVENT_DATA_RAID *)fw_event->event_data;
	status = le32_to_cpu(raid_event_data->SettingsStatus);
	state = (status >> 8) & 0xff;

	स_रखो(&hot_plug_info, 0, माप(काष्ठा mptsas_hotplug_event));
	hot_plug_info.id = raid_event_data->VolumeID;
	hot_plug_info.channel = raid_event_data->VolumeBus;
	hot_plug_info.phys_disk_num = raid_event_data->PhysDiskNum;

	अगर (raid_event_data->ReasonCode == MPI_EVENT_RAID_RC_VOLUME_DELETED ||
	    raid_event_data->ReasonCode == MPI_EVENT_RAID_RC_VOLUME_CREATED ||
	    raid_event_data->ReasonCode ==
	    MPI_EVENT_RAID_RC_VOLUME_STATUS_CHANGED) अणु
		sdev = scsi_device_lookup(ioc->sh, MPTSAS_RAID_CHANNEL,
		    hot_plug_info.id, 0);
		hot_plug_info.sdev = sdev;
		अगर (sdev)
			vdevice = sdev->hostdata;
	पूर्ण

	devtprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT "Entering %s: "
	    "ReasonCode=%02x\n", ioc->name, __func__,
	    raid_event_data->ReasonCode));

	चयन (raid_event_data->ReasonCode) अणु
	हाल MPI_EVENT_RAID_RC_PHYSDISK_DELETED:
		hot_plug_info.event_type = MPTSAS_DEL_PHYSDISK_REPROBE;
		अवरोध;
	हाल MPI_EVENT_RAID_RC_PHYSDISK_CREATED:
		hot_plug_info.event_type = MPTSAS_ADD_PHYSDISK_REPROBE;
		अवरोध;
	हाल MPI_EVENT_RAID_RC_PHYSDISK_STATUS_CHANGED:
		चयन (state) अणु
		हाल MPI_PD_STATE_ONLINE:
		हाल MPI_PD_STATE_NOT_COMPATIBLE:
			mpt_raid_phys_disk_pg0(ioc,
			    raid_event_data->PhysDiskNum, &phys_disk);
			hot_plug_info.id = phys_disk.PhysDiskID;
			hot_plug_info.channel = phys_disk.PhysDiskBus;
			hot_plug_info.event_type = MPTSAS_ADD_PHYSDISK;
			अवरोध;
		हाल MPI_PD_STATE_FAILED:
		हाल MPI_PD_STATE_MISSING:
		हाल MPI_PD_STATE_OFFLINE_AT_HOST_REQUEST:
		हाल MPI_PD_STATE_FAILED_AT_HOST_REQUEST:
		हाल MPI_PD_STATE_OFFLINE_FOR_ANOTHER_REASON:
			hot_plug_info.event_type = MPTSAS_DEL_PHYSDISK;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;
	हाल MPI_EVENT_RAID_RC_VOLUME_DELETED:
		अगर (!sdev)
			अवरोध;
		vdevice->vtarget->deleted = 1; /* block IO */
		hot_plug_info.event_type = MPTSAS_DEL_RAID;
		अवरोध;
	हाल MPI_EVENT_RAID_RC_VOLUME_CREATED:
		अगर (sdev) अणु
			scsi_device_put(sdev);
			अवरोध;
		पूर्ण
		hot_plug_info.event_type = MPTSAS_ADD_RAID;
		अवरोध;
	हाल MPI_EVENT_RAID_RC_VOLUME_STATUS_CHANGED:
		अगर (!(status & MPI_RAIDVOL0_STATUS_FLAG_ENABLED)) अणु
			अगर (!sdev)
				अवरोध;
			vdevice->vtarget->deleted = 1; /* block IO */
			hot_plug_info.event_type = MPTSAS_DEL_RAID;
			अवरोध;
		पूर्ण
		चयन (state) अणु
		हाल MPI_RAIDVOL0_STATUS_STATE_FAILED:
		हाल MPI_RAIDVOL0_STATUS_STATE_MISSING:
			अगर (!sdev)
				अवरोध;
			vdevice->vtarget->deleted = 1; /* block IO */
			hot_plug_info.event_type = MPTSAS_DEL_RAID;
			अवरोध;
		हाल MPI_RAIDVOL0_STATUS_STATE_OPTIMAL:
		हाल MPI_RAIDVOL0_STATUS_STATE_DEGRADED:
			अगर (sdev) अणु
				scsi_device_put(sdev);
				अवरोध;
			पूर्ण
			hot_plug_info.event_type = MPTSAS_ADD_RAID;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	अगर (hot_plug_info.event_type != MPTSAS_IGNORE_EVENT)
		mptsas_hotplug_work(ioc, fw_event, &hot_plug_info);
	अन्यथा
		mptsas_मुक्त_fw_event(ioc, fw_event);
पूर्ण

/**
 *	mptsas_issue_पंचांग - send mptsas पूर्णांकernal पंचांग request
 *	@ioc: Poपूर्णांकer to MPT_ADAPTER काष्ठाure
 *	@type: Task Management type
 *	@channel: channel number क्रम task management
 *	@id: Logical Target ID क्रम reset (अगर appropriate)
 *	@lun: Logical unit क्रम reset (अगर appropriate)
 *	@task_context: Context क्रम the task to be पातed
 *	@समयout: समयout क्रम task management control
 *
 *	वापस 0 on success and -1 on failure:
 *
 */
अटल पूर्णांक
mptsas_issue_पंचांग(MPT_ADAPTER *ioc, u8 type, u8 channel, u8 id, u64 lun,
	पूर्णांक task_context, uदीर्घ समयout, u8 *issue_reset)
अणु
	MPT_FRAME_HDR	*mf;
	SCSITaskMgmt_t	*pScsiTm;
	पूर्णांक		 retval;
	अचिन्हित दीर्घ	 समयleft;

	*issue_reset = 0;
	mf = mpt_get_msg_frame(mptsasDeviceResetCtx, ioc);
	अगर (mf == शून्य) अणु
		retval = -1; /* वापस failure */
		dपंचांगprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_WARN_FMT "TaskMgmt request: no "
		    "msg frames!!\n", ioc->name));
		जाओ out;
	पूर्ण

	dपंचांगprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT "TaskMgmt request: mr = %p, "
	    "task_type = 0x%02X,\n\t timeout = %ld, fw_channel = %d, "
	    "fw_id = %d, lun = %lld,\n\t task_context = 0x%x\n", ioc->name, mf,
	     type, समयout, channel, id, (अचिन्हित दीर्घ दीर्घ)lun,
	     task_context));

	pScsiTm = (SCSITaskMgmt_t *) mf;
	स_रखो(pScsiTm, 0, माप(SCSITaskMgmt_t));
	pScsiTm->Function = MPI_FUNCTION_SCSI_TASK_MGMT;
	pScsiTm->TaskType = type;
	pScsiTm->MsgFlags = 0;
	pScsiTm->TargetID = id;
	pScsiTm->Bus = channel;
	pScsiTm->ChainOffset = 0;
	pScsiTm->Reserved = 0;
	pScsiTm->Reserved1 = 0;
	pScsiTm->TaskMsgContext = task_context;
	पूर्णांक_to_scsilun(lun, (काष्ठा scsi_lun *)pScsiTm->LUN);

	INITIALIZE_MGMT_STATUS(ioc->taskmgmt_cmds.status)
	CLEAR_MGMT_STATUS(ioc->पूर्णांकernal_cmds.status)
	retval = 0;
	mpt_put_msg_frame_hi_pri(mptsasDeviceResetCtx, ioc, mf);

	/* Now रुको क्रम the command to complete */
	समयleft = रुको_क्रम_completion_समयout(&ioc->taskmgmt_cmds.करोne,
	    समयout*HZ);
	अगर (!(ioc->taskmgmt_cmds.status & MPT_MGMT_STATUS_COMMAND_GOOD)) अणु
		retval = -1; /* वापस failure */
		dपंचांगprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_ERR_FMT
		    "TaskMgmt request: TIMED OUT!(mr=%p)\n", ioc->name, mf));
		mpt_मुक्त_msg_frame(ioc, mf);
		अगर (ioc->taskmgmt_cmds.status & MPT_MGMT_STATUS_DID_IOCRESET)
			जाओ out;
		*issue_reset = 1;
		जाओ out;
	पूर्ण

	अगर (!(ioc->taskmgmt_cmds.status & MPT_MGMT_STATUS_RF_VALID)) अणु
		retval = -1; /* वापस failure */
		dपंचांगprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT
		    "TaskMgmt request: failed with no reply\n", ioc->name));
		जाओ out;
	पूर्ण

 out:
	CLEAR_MGMT_STATUS(ioc->taskmgmt_cmds.status)
	वापस retval;
पूर्ण

/**
 *	mptsas_broadcast_primitive_work - Handle broadcast primitives
 *	@work: work queue payload containing info describing the event
 *
 *	this will be handled in workqueue context.
 */
अटल व्योम
mptsas_broadcast_primitive_work(काष्ठा fw_event_work *fw_event)
अणु
	MPT_ADAPTER *ioc = fw_event->ioc;
	MPT_FRAME_HDR	*mf;
	VirtDevice	*vdevice;
	पूर्णांक			ii;
	काष्ठा scsi_cmnd	*sc;
	SCSITaskMgmtReply_t	*pScsiTmReply;
	u8			issue_reset;
	पूर्णांक			task_context;
	u8			channel, id;
	पूर्णांक			 lun;
	u32			 termination_count;
	u32			 query_count;

	dपंचांगprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT
	    "%s - enter\n", ioc->name, __func__));

	mutex_lock(&ioc->taskmgmt_cmds.mutex);
	अगर (mpt_set_taskmgmt_in_progress_flag(ioc) != 0) अणु
		mutex_unlock(&ioc->taskmgmt_cmds.mutex);
		mptsas_requeue_fw_event(ioc, fw_event, 1000);
		वापस;
	पूर्ण

	issue_reset = 0;
	termination_count = 0;
	query_count = 0;
	mpt_findImVolumes(ioc);
	pScsiTmReply = (SCSITaskMgmtReply_t *) ioc->taskmgmt_cmds.reply;

	क्रम (ii = 0; ii < ioc->req_depth; ii++) अणु
		अगर (ioc->fw_events_off)
			जाओ out;
		sc = mptscsih_get_scsi_lookup(ioc, ii);
		अगर (!sc)
			जारी;
		mf = MPT_INDEX_2_MFPTR(ioc, ii);
		अगर (!mf)
			जारी;
		task_context = mf->u.frame.hwhdr.msgctxu.MsgContext;
		vdevice = sc->device->hostdata;
		अगर (!vdevice || !vdevice->vtarget)
			जारी;
		अगर (vdevice->vtarget->tflags & MPT_TARGET_FLAGS_RAID_COMPONENT)
			जारी; /* skip hidden raid components */
		अगर (vdevice->vtarget->raidVolume)
			जारी; /* skip hidden raid components */
		channel = vdevice->vtarget->channel;
		id = vdevice->vtarget->id;
		lun = vdevice->lun;
		अगर (mptsas_issue_पंचांग(ioc, MPI_SCSITASKMGMT_TASKTYPE_QUERY_TASK,
		    channel, id, (u64)lun, task_context, 30, &issue_reset))
			जाओ out;
		query_count++;
		termination_count +=
		    le32_to_cpu(pScsiTmReply->TerminationCount);
		अगर ((pScsiTmReply->IOCStatus == MPI_IOCSTATUS_SUCCESS) &&
		    (pScsiTmReply->ResponseCode ==
		    MPI_SCSITASKMGMT_RSP_TM_SUCCEEDED ||
		    pScsiTmReply->ResponseCode ==
		    MPI_SCSITASKMGMT_RSP_IO_QUEUED_ON_IOC))
			जारी;
		अगर (mptsas_issue_पंचांग(ioc,
		    MPI_SCSITASKMGMT_TASKTYPE_ABRT_TASK_SET,
		    channel, id, (u64)lun, 0, 30, &issue_reset))
			जाओ out;
		termination_count +=
		    le32_to_cpu(pScsiTmReply->TerminationCount);
	पूर्ण

 out:
	dपंचांगprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT
	    "%s - exit, query_count = %d termination_count = %d\n",
	    ioc->name, __func__, query_count, termination_count));

	ioc->broadcast_aen_busy = 0;
	mpt_clear_taskmgmt_in_progress_flag(ioc);
	mutex_unlock(&ioc->taskmgmt_cmds.mutex);

	अगर (issue_reset) अणु
		prपूर्णांकk(MYIOC_s_WARN_FMT
		       "Issuing Reset from %s!! doorbell=0x%08x\n",
		       ioc->name, __func__, mpt_GetIocState(ioc, 0));
		mpt_Soft_Hard_ResetHandler(ioc, CAN_SLEEP);
	पूर्ण
	mptsas_मुक्त_fw_event(ioc, fw_event);
पूर्ण

/*
 * mptsas_send_ir2_event - handle exposing hidden disk when
 * an inactive raid volume is added
 *
 * @ioc: Poपूर्णांकer to MPT_ADAPTER काष्ठाure
 * @ir2_data
 *
 */
अटल व्योम
mptsas_send_ir2_event(काष्ठा fw_event_work *fw_event)
अणु
	MPT_ADAPTER	*ioc;
	काष्ठा mptsas_hotplug_event hot_plug_info;
	MPI_EVENT_DATA_IR2	*ir2_data;
	u8 reasonCode;
	RaidPhysDiskPage0_t phys_disk;

	ioc = fw_event->ioc;
	ir2_data = (MPI_EVENT_DATA_IR2 *)fw_event->event_data;
	reasonCode = ir2_data->ReasonCode;

	devtprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT "Entering %s: "
	    "ReasonCode=%02x\n", ioc->name, __func__, reasonCode));

	स_रखो(&hot_plug_info, 0, माप(काष्ठा mptsas_hotplug_event));
	hot_plug_info.id = ir2_data->TargetID;
	hot_plug_info.channel = ir2_data->Bus;
	चयन (reasonCode) अणु
	हाल MPI_EVENT_IR2_RC_FOREIGN_CFG_DETECTED:
		hot_plug_info.event_type = MPTSAS_ADD_INACTIVE_VOLUME;
		अवरोध;
	हाल MPI_EVENT_IR2_RC_DUAL_PORT_REMOVED:
		hot_plug_info.phys_disk_num = ir2_data->PhysDiskNum;
		hot_plug_info.event_type = MPTSAS_DEL_PHYSDISK;
		अवरोध;
	हाल MPI_EVENT_IR2_RC_DUAL_PORT_ADDED:
		hot_plug_info.phys_disk_num = ir2_data->PhysDiskNum;
		mpt_raid_phys_disk_pg0(ioc,
		    ir2_data->PhysDiskNum, &phys_disk);
		hot_plug_info.id = phys_disk.PhysDiskID;
		hot_plug_info.event_type = MPTSAS_ADD_PHYSDISK;
		अवरोध;
	शेष:
		mptsas_मुक्त_fw_event(ioc, fw_event);
		वापस;
	पूर्ण
	mptsas_hotplug_work(ioc, fw_event, &hot_plug_info);
पूर्ण

अटल पूर्णांक
mptsas_event_process(MPT_ADAPTER *ioc, EventNotअगरicationReply_t *reply)
अणु
	u32 event = le32_to_cpu(reply->Event);
	पूर्णांक event_data_sz;
	काष्ठा fw_event_work *fw_event;
	अचिन्हित दीर्घ delay;

	अगर (ioc->bus_type != SAS)
		वापस 0;

	/* events turned off due to host reset or driver unloading */
	अगर (ioc->fw_events_off)
		वापस 0;

	delay = msecs_to_jअगरfies(1);
	चयन (event) अणु
	हाल MPI_EVENT_SAS_BROADCAST_PRIMITIVE:
	अणु
		EVENT_DATA_SAS_BROADCAST_PRIMITIVE *broadcast_event_data =
		    (EVENT_DATA_SAS_BROADCAST_PRIMITIVE *)reply->Data;
		अगर (broadcast_event_data->Primitive !=
		    MPI_EVENT_PRIMITIVE_ASYNCHRONOUS_EVENT)
			वापस 0;
		अगर (ioc->broadcast_aen_busy)
			वापस 0;
		ioc->broadcast_aen_busy = 1;
		अवरोध;
	पूर्ण
	हाल MPI_EVENT_SAS_DEVICE_STATUS_CHANGE:
	अणु
		EVENT_DATA_SAS_DEVICE_STATUS_CHANGE *sas_event_data =
		    (EVENT_DATA_SAS_DEVICE_STATUS_CHANGE *)reply->Data;
		u16	ioc_stat;
		ioc_stat = le16_to_cpu(reply->IOCStatus);

		अगर (sas_event_data->ReasonCode ==
		    MPI_EVENT_SAS_DEV_STAT_RC_NOT_RESPONDING) अणु
			mptsas_target_reset_queue(ioc, sas_event_data);
			वापस 0;
		पूर्ण
		अगर (sas_event_data->ReasonCode ==
			MPI_EVENT_SAS_DEV_STAT_RC_INTERNAL_DEVICE_RESET &&
			ioc->device_missing_delay &&
			(ioc_stat & MPI_IOCSTATUS_FLAG_LOG_INFO_AVAILABLE)) अणु
			VirtTarget *vtarget = शून्य;
			u8		id, channel;

			id = sas_event_data->TargetID;
			channel = sas_event_data->Bus;

			vtarget = mptsas_find_vtarget(ioc, channel, id);
			अगर (vtarget) अणु
				devtprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT
				    "LogInfo (0x%x) available for "
				   "INTERNAL_DEVICE_RESET"
				   "fw_id %d fw_channel %d\n", ioc->name,
				   le32_to_cpu(reply->IOCLogInfo),
				   id, channel));
				अगर (vtarget->raidVolume) अणु
					devtprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT
					"Skipping Raid Volume for inDMD\n",
					ioc->name));
				पूर्ण अन्यथा अणु
					devtprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT
					"Setting device flag inDMD\n",
					ioc->name));
					vtarget->inDMD = 1;
				पूर्ण

			पूर्ण

		पूर्ण

		अवरोध;
	पूर्ण
	हाल MPI_EVENT_SAS_EXPANDER_STATUS_CHANGE:
	अणु
		MpiEventDataSasExpanderStatusChange_t *expander_data =
		    (MpiEventDataSasExpanderStatusChange_t *)reply->Data;

		अगर (ioc->old_sas_discovery_protocal)
			वापस 0;

		अगर (expander_data->ReasonCode ==
		    MPI_EVENT_SAS_EXP_RC_NOT_RESPONDING &&
		    ioc->device_missing_delay)
			delay = HZ * ioc->device_missing_delay;
		अवरोध;
	पूर्ण
	हाल MPI_EVENT_SAS_DISCOVERY:
	अणु
		u32 discovery_status;
		EventDataSasDiscovery_t *discovery_data =
		    (EventDataSasDiscovery_t *)reply->Data;

		discovery_status = le32_to_cpu(discovery_data->DiscoveryStatus);
		ioc->sas_discovery_quiesce_io = discovery_status ? 1 : 0;
		अगर (ioc->old_sas_discovery_protocal && !discovery_status)
			mptsas_queue_rescan(ioc);
		वापस 0;
	पूर्ण
	हाल MPI_EVENT_INTEGRATED_RAID:
	हाल MPI_EVENT_PERSISTENT_TABLE_FULL:
	हाल MPI_EVENT_IR2:
	हाल MPI_EVENT_SAS_PHY_LINK_STATUS:
	हाल MPI_EVENT_QUEUE_FULL:
		अवरोध;
	शेष:
		वापस 0;
	पूर्ण

	event_data_sz = ((reply->MsgLength * 4) -
	    दुरत्व(EventNotअगरicationReply_t, Data));
	fw_event = kzalloc(माप(*fw_event) + event_data_sz, GFP_ATOMIC);
	अगर (!fw_event) अणु
		prपूर्णांकk(MYIOC_s_WARN_FMT "%s: failed at (line=%d)\n", ioc->name,
		 __func__, __LINE__);
		वापस 0;
	पूर्ण
	स_नकल(fw_event->event_data, reply->Data, event_data_sz);
	fw_event->event = event;
	fw_event->ioc = ioc;
	mptsas_add_fw_event(ioc, fw_event, delay);
	वापस 0;
पूर्ण

/* Delete a volume when no दीर्घer listed in ioc pg2
 */
अटल व्योम mptsas_volume_delete(MPT_ADAPTER *ioc, u8 id)
अणु
	काष्ठा scsi_device *sdev;
	पूर्णांक i;

	sdev = scsi_device_lookup(ioc->sh, MPTSAS_RAID_CHANNEL, id, 0);
	अगर (!sdev)
		वापस;
	अगर (!ioc->raid_data.pIocPg2)
		जाओ out;
	अगर (!ioc->raid_data.pIocPg2->NumActiveVolumes)
		जाओ out;
	क्रम (i = 0; i < ioc->raid_data.pIocPg2->NumActiveVolumes; i++)
		अगर (ioc->raid_data.pIocPg2->RaidVolume[i].VolumeID == id)
			जाओ release_sdev;
 out:
	prपूर्णांकk(MYIOC_s_INFO_FMT "removing raid volume, channel %d, "
	    "id %d\n", ioc->name, MPTSAS_RAID_CHANNEL, id);
	scsi_हटाओ_device(sdev);
 release_sdev:
	scsi_device_put(sdev);
पूर्ण

अटल पूर्णांक
mptsas_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *id)
अणु
	काष्ठा Scsi_Host	*sh;
	MPT_SCSI_HOST		*hd;
	MPT_ADAPTER 		*ioc;
	अचिन्हित दीर्घ		 flags;
	पूर्णांक			 ii;
	पूर्णांक			 numSGE = 0;
	पूर्णांक			 scale;
	पूर्णांक			 ioc_cap;
	पूर्णांक			error=0;
	पूर्णांक			r;

	r = mpt_attach(pdev,id);
	अगर (r)
		वापस r;

	ioc = pci_get_drvdata(pdev);
	mptsas_fw_event_off(ioc);
	ioc->DoneCtx = mptsasDoneCtx;
	ioc->TaskCtx = mptsasTaskCtx;
	ioc->InternalCtx = mptsasInternalCtx;
	ioc->schedule_target_reset = &mptsas_schedule_target_reset;
	ioc->schedule_dead_ioc_flush_running_cmds =
				&mptscsih_flush_running_cmds;
	/*  Added sanity check on पढ़ोiness of the MPT adapter.
	 */
	अगर (ioc->last_state != MPI_IOC_STATE_OPERATIONAL) अणु
		prपूर्णांकk(MYIOC_s_WARN_FMT
		  "Skipping because it's not operational!\n",
		  ioc->name);
		error = -ENODEV;
		जाओ out_mptsas_probe;
	पूर्ण

	अगर (!ioc->active) अणु
		prपूर्णांकk(MYIOC_s_WARN_FMT "Skipping because it's disabled!\n",
		  ioc->name);
		error = -ENODEV;
		जाओ out_mptsas_probe;
	पूर्ण

	/*  Sanity check - ensure at least 1 port is INITIATOR capable
	 */
	ioc_cap = 0;
	क्रम (ii = 0; ii < ioc->facts.NumberOfPorts; ii++) अणु
		अगर (ioc->pfacts[ii].ProtocolFlags &
				MPI_PORTFACTS_PROTOCOL_INITIATOR)
			ioc_cap++;
	पूर्ण

	अगर (!ioc_cap) अणु
		prपूर्णांकk(MYIOC_s_WARN_FMT
			"Skipping ioc=%p because SCSI Initiator mode "
			"is NOT enabled!\n", ioc->name, ioc);
		वापस 0;
	पूर्ण

	sh = scsi_host_alloc(&mptsas_driver_ढाँचा, माप(MPT_SCSI_HOST));
	अगर (!sh) अणु
		prपूर्णांकk(MYIOC_s_WARN_FMT
			"Unable to register controller with SCSI subsystem\n",
			ioc->name);
		error = -1;
		जाओ out_mptsas_probe;
        पूर्ण

	spin_lock_irqsave(&ioc->FreeQlock, flags);

	/* Attach the SCSI Host to the IOC काष्ठाure
	 */
	ioc->sh = sh;

	sh->io_port = 0;
	sh->n_io_port = 0;
	sh->irq = 0;

	/* set 16 byte cdb's */
	sh->max_cmd_len = 16;
	sh->can_queue = min_t(पूर्णांक, ioc->req_depth - 10, sh->can_queue);
	sh->max_id = -1;
	sh->max_lun = max_lun;
	sh->transportt = mptsas_transport_ढाँचा;

	/* Required entry.
	 */
	sh->unique_id = ioc->id;

	INIT_LIST_HEAD(&ioc->sas_topology);
	mutex_init(&ioc->sas_topology_mutex);
	mutex_init(&ioc->sas_discovery_mutex);
	mutex_init(&ioc->sas_mgmt.mutex);
	init_completion(&ioc->sas_mgmt.करोne);

	/* Verअगरy that we won't exceed the maximum
	 * number of chain buffers
	 * We can optimize:  ZZ = req_sz/माप(SGE)
	 * For 32bit SGE's:
	 *  numSGE = 1 + (ZZ-1)*(maxChain -1) + ZZ
	 *               + (req_sz - 64)/माप(SGE)
	 * A slightly dअगरferent algorithm is required क्रम
	 * 64bit SGEs.
	 */
	scale = ioc->req_sz/ioc->SGE_size;
	अगर (ioc->sg_addr_size == माप(u64)) अणु
		numSGE = (scale - 1) *
		  (ioc->facts.MaxChainDepth-1) + scale +
		  (ioc->req_sz - 60) / ioc->SGE_size;
	पूर्ण अन्यथा अणु
		numSGE = 1 + (scale - 1) *
		  (ioc->facts.MaxChainDepth-1) + scale +
		  (ioc->req_sz - 64) / ioc->SGE_size;
	पूर्ण

	अगर (numSGE < sh->sg_tablesize) अणु
		/* Reset this value */
		dprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT
		  "Resetting sg_tablesize to %d from %d\n",
		  ioc->name, numSGE, sh->sg_tablesize));
		sh->sg_tablesize = numSGE;
	पूर्ण

	अगर (mpt_loadसमय_max_sectors) अणु
		अगर (mpt_loadसमय_max_sectors < 64 ||
			mpt_loadसमय_max_sectors > 8192) अणु
			prपूर्णांकk(MYIOC_s_INFO_FMT "Invalid value passed for"
				"mpt_loadtime_max_sectors %d."
				"Range from 64 to 8192\n", ioc->name,
				mpt_loadसमय_max_sectors);
		पूर्ण
		mpt_loadसमय_max_sectors &=  0xFFFFFFFE;
		dprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT
			"Resetting max sector to %d from %d\n",
		  ioc->name, mpt_loadसमय_max_sectors, sh->max_sectors));
		sh->max_sectors = mpt_loadसमय_max_sectors;
	पूर्ण

	hd = shost_priv(sh);
	hd->ioc = ioc;

	/* SCSI needs scsi_cmnd lookup table!
	 * (with size equal to req_depth*PtrSz!)
	 */
	ioc->ScsiLookup = kसुस्मृति(ioc->req_depth, माप(व्योम *), GFP_ATOMIC);
	अगर (!ioc->ScsiLookup) अणु
		error = -ENOMEM;
		spin_unlock_irqrestore(&ioc->FreeQlock, flags);
		जाओ out_mptsas_probe;
	पूर्ण
	spin_lock_init(&ioc->scsi_lookup_lock);

	dprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT "ScsiLookup @ %p\n",
		 ioc->name, ioc->ScsiLookup));

	ioc->sas_data.ptClear = mpt_pt_clear;

	hd->last_queue_full = 0;
	INIT_LIST_HEAD(&hd->target_reset_list);
	INIT_LIST_HEAD(&ioc->sas_device_info_list);
	mutex_init(&ioc->sas_device_info_mutex);

	spin_unlock_irqrestore(&ioc->FreeQlock, flags);

	अगर (ioc->sas_data.ptClear==1) अणु
		mptbase_sas_persist_operation(
		    ioc, MPI_SAS_OP_CLEAR_ALL_PERSISTENT);
	पूर्ण

	error = scsi_add_host(sh, &ioc->pcidev->dev);
	अगर (error) अणु
		dprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_ERR_FMT
		  "scsi_add_host failed\n", ioc->name));
		जाओ out_mptsas_probe;
	पूर्ण

	/* older firmware करोesn't support expander events */
	अगर ((ioc->facts.HeaderVersion >> 8) < 0xE)
		ioc->old_sas_discovery_protocal = 1;
	mptsas_scan_sas_topology(ioc);
	mptsas_fw_event_on(ioc);
	वापस 0;

 out_mptsas_probe:

	mptscsih_हटाओ(pdev);
	वापस error;
पूर्ण

अटल व्योम
mptsas_shutकरोwn(काष्ठा pci_dev *pdev)
अणु
	MPT_ADAPTER *ioc = pci_get_drvdata(pdev);

	mptsas_fw_event_off(ioc);
	mptsas_cleanup_fw_event_q(ioc);
पूर्ण

अटल व्योम mptsas_हटाओ(काष्ठा pci_dev *pdev)
अणु
	MPT_ADAPTER *ioc = pci_get_drvdata(pdev);
	काष्ठा mptsas_portinfo *p, *n;
	पूर्णांक i;

	अगर (!ioc->sh) अणु
		prपूर्णांकk(MYIOC_s_INFO_FMT "IOC is in Target mode\n", ioc->name);
		mpt_detach(pdev);
		वापस;
	पूर्ण

	mptsas_shutकरोwn(pdev);

	mptsas_del_device_components(ioc);

	ioc->sas_discovery_ignore_events = 1;
	sas_हटाओ_host(ioc->sh);

	mutex_lock(&ioc->sas_topology_mutex);
	list_क्रम_each_entry_safe(p, n, &ioc->sas_topology, list) अणु
		list_del(&p->list);
		क्रम (i = 0 ; i < p->num_phys ; i++)
			mptsas_port_delete(ioc, p->phy_info[i].port_details);

		kमुक्त(p->phy_info);
		kमुक्त(p);
	पूर्ण
	mutex_unlock(&ioc->sas_topology_mutex);
	ioc->hba_port_info = शून्य;
	mptscsih_हटाओ(pdev);
पूर्ण

अटल काष्ठा pci_device_id mptsas_pci_table[] = अणु
	अणु PCI_VENDOR_ID_LSI_LOGIC, MPI_MANUFACTPAGE_DEVID_SAS1064,
		PCI_ANY_ID, PCI_ANY_ID पूर्ण,
	अणु PCI_VENDOR_ID_LSI_LOGIC, MPI_MANUFACTPAGE_DEVID_SAS1068,
		PCI_ANY_ID, PCI_ANY_ID पूर्ण,
	अणु PCI_VENDOR_ID_LSI_LOGIC, MPI_MANUFACTPAGE_DEVID_SAS1064E,
		PCI_ANY_ID, PCI_ANY_ID पूर्ण,
	अणु PCI_VENDOR_ID_LSI_LOGIC, MPI_MANUFACTPAGE_DEVID_SAS1068E,
		PCI_ANY_ID, PCI_ANY_ID पूर्ण,
	अणु PCI_VENDOR_ID_LSI_LOGIC, MPI_MANUFACTPAGE_DEVID_SAS1078,
		PCI_ANY_ID, PCI_ANY_ID पूर्ण,
	अणु PCI_VENDOR_ID_LSI_LOGIC, MPI_MANUFACTPAGE_DEVID_SAS1068_820XELP,
		PCI_ANY_ID, PCI_ANY_ID पूर्ण,
	अणु0पूर्ण	/* Terminating entry */
पूर्ण;
MODULE_DEVICE_TABLE(pci, mptsas_pci_table);


अटल काष्ठा pci_driver mptsas_driver = अणु
	.name		= "mptsas",
	.id_table	= mptsas_pci_table,
	.probe		= mptsas_probe,
	.हटाओ		= mptsas_हटाओ,
	.shutकरोwn	= mptsas_shutकरोwn,
#अगर_घोषित CONFIG_PM
	.suspend	= mptscsih_suspend,
	.resume		= mptscsih_resume,
#पूर्ण_अगर
पूर्ण;

अटल पूर्णांक __init
mptsas_init(व्योम)
अणु
	पूर्णांक error;

	show_mpपंचांगod_ver(my_NAME, my_VERSION);

	mptsas_transport_ढाँचा =
	    sas_attach_transport(&mptsas_transport_functions);
	अगर (!mptsas_transport_ढाँचा)
		वापस -ENODEV;

	mptsasDoneCtx = mpt_रेजिस्टर(mptscsih_io_करोne, MPTSAS_DRIVER,
	    "mptscsih_io_done");
	mptsasTaskCtx = mpt_रेजिस्टर(mptscsih_taskmgmt_complete, MPTSAS_DRIVER,
	    "mptscsih_taskmgmt_complete");
	mptsasInternalCtx =
		mpt_रेजिस्टर(mptscsih_scandv_complete, MPTSAS_DRIVER,
		    "mptscsih_scandv_complete");
	mptsasMgmtCtx = mpt_रेजिस्टर(mptsas_mgmt_करोne, MPTSAS_DRIVER,
	    "mptsas_mgmt_done");
	mptsasDeviceResetCtx =
		mpt_रेजिस्टर(mptsas_taskmgmt_complete, MPTSAS_DRIVER,
		    "mptsas_taskmgmt_complete");

	mpt_event_रेजिस्टर(mptsasDoneCtx, mptsas_event_process);
	mpt_reset_रेजिस्टर(mptsasDoneCtx, mptsas_ioc_reset);

	error = pci_रेजिस्टर_driver(&mptsas_driver);
	अगर (error)
		sas_release_transport(mptsas_transport_ढाँचा);

	वापस error;
पूर्ण

अटल व्योम __निकास
mptsas_निकास(व्योम)
अणु
	pci_unरेजिस्टर_driver(&mptsas_driver);
	sas_release_transport(mptsas_transport_ढाँचा);

	mpt_reset_deरेजिस्टर(mptsasDoneCtx);
	mpt_event_deरेजिस्टर(mptsasDoneCtx);

	mpt_deरेजिस्टर(mptsasMgmtCtx);
	mpt_deरेजिस्टर(mptsasInternalCtx);
	mpt_deरेजिस्टर(mptsasTaskCtx);
	mpt_deरेजिस्टर(mptsasDoneCtx);
	mpt_deरेजिस्टर(mptsasDeviceResetCtx);
पूर्ण

module_init(mptsas_init);
module_निकास(mptsas_निकास);
