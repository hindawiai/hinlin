<शैली गुरु>
/*
 *  linux/drivers/message/fusion/mptfc.c
 *      For use with LSI PCI chip/adapter(s)
 *      running LSI Fusion MPT (Message Passing Technology) firmware.
 *
 *  Copyright (c) 1999-2008 LSI Corporation
 *  (mailto:DL-MPTFusionLinux@lsi.com)
 *
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
#समावेश <linux/init.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kdev_t.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/delay.h>	/* क्रम mdelay */
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/reboot.h>	/* notअगरier code */
#समावेश <linux/workqueue.h>
#समावेश <linux/sort.h>
#समावेश <linux/slab.h>

#समावेश <scsi/scsi.h>
#समावेश <scsi/scsi_cmnd.h>
#समावेश <scsi/scsi_device.h>
#समावेश <scsi/scsi_host.h>
#समावेश <scsi/scsi_tcq.h>
#समावेश <scsi/scsi_transport_fc.h>

#समावेश "mptbase.h"
#समावेश "mptscsih.h"

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
#घोषणा my_NAME		"Fusion MPT FC Host driver"
#घोषणा my_VERSION	MPT_LINUX_VERSION_COMMON
#घोषणा MYNAM		"mptfc"

MODULE_AUTHOR(MODULEAUTHOR);
MODULE_DESCRIPTION(my_NAME);
MODULE_LICENSE("GPL");
MODULE_VERSION(my_VERSION);

/* Command line args */
#घोषणा MPTFC_DEV_LOSS_TMO (60)
अटल पूर्णांक mptfc_dev_loss_पंचांगo = MPTFC_DEV_LOSS_TMO;	/* reasonable शेष */
module_param(mptfc_dev_loss_पंचांगo, पूर्णांक, 0);
MODULE_PARM_DESC(mptfc_dev_loss_पंचांगo, " Initial time the driver programs the "
    				     " transport to wait for an rport to "
				     " return following a device loss event."
				     "  Default=60.");

/* scsi-mid layer global parmeter is max_report_luns, which is 511 */
#घोषणा MPTFC_MAX_LUN (16895)
अटल पूर्णांक max_lun = MPTFC_MAX_LUN;
module_param(max_lun, पूर्णांक, 0);
MODULE_PARM_DESC(max_lun, " max lun, default=16895 ");

अटल u8	mptfcDoneCtx = MPT_MAX_PROTOCOL_DRIVERS;
अटल u8	mptfcTaskCtx = MPT_MAX_PROTOCOL_DRIVERS;
अटल u8	mptfcInternalCtx = MPT_MAX_PROTOCOL_DRIVERS;

अटल पूर्णांक mptfc_target_alloc(काष्ठा scsi_target *starget);
अटल पूर्णांक mptfc_slave_alloc(काष्ठा scsi_device *sdev);
अटल पूर्णांक mptfc_qcmd(काष्ठा Scsi_Host *shost, काष्ठा scsi_cmnd *SCpnt);
अटल व्योम mptfc_target_destroy(काष्ठा scsi_target *starget);
अटल व्योम mptfc_set_rport_loss_पंचांगo(काष्ठा fc_rport *rport, uपूर्णांक32_t समयout);
अटल व्योम mptfc_हटाओ(काष्ठा pci_dev *pdev);
अटल पूर्णांक mptfc_पात(काष्ठा scsi_cmnd *SCpnt);
अटल पूर्णांक mptfc_dev_reset(काष्ठा scsi_cmnd *SCpnt);
अटल पूर्णांक mptfc_bus_reset(काष्ठा scsi_cmnd *SCpnt);

अटल काष्ठा scsi_host_ढाँचा mptfc_driver_ढाँचा = अणु
	.module				= THIS_MODULE,
	.proc_name			= "mptfc",
	.show_info			= mptscsih_show_info,
	.name				= "MPT FC Host",
	.info				= mptscsih_info,
	.queuecommand			= mptfc_qcmd,
	.target_alloc			= mptfc_target_alloc,
	.slave_alloc			= mptfc_slave_alloc,
	.slave_configure		= mptscsih_slave_configure,
	.target_destroy			= mptfc_target_destroy,
	.slave_destroy			= mptscsih_slave_destroy,
	.change_queue_depth 		= mptscsih_change_queue_depth,
	.eh_समयd_out			= fc_eh_समयd_out,
	.eh_पात_handler		= mptfc_पात,
	.eh_device_reset_handler	= mptfc_dev_reset,
	.eh_bus_reset_handler		= mptfc_bus_reset,
	.eh_host_reset_handler		= mptscsih_host_reset,
	.bios_param			= mptscsih_bios_param,
	.can_queue			= MPT_FC_CAN_QUEUE,
	.this_id			= -1,
	.sg_tablesize			= MPT_SCSI_SG_DEPTH,
	.max_sectors			= 8192,
	.cmd_per_lun			= 7,
	.shost_attrs			= mptscsih_host_attrs,
पूर्ण;

/****************************************************************************
 * Supported hardware
 */

अटल काष्ठा pci_device_id mptfc_pci_table[] = अणु
	अणु PCI_VENDOR_ID_LSI_LOGIC, MPI_MANUFACTPAGE_DEVICEID_FC909,
		PCI_ANY_ID, PCI_ANY_ID पूर्ण,
	अणु PCI_VENDOR_ID_LSI_LOGIC, MPI_MANUFACTPAGE_DEVICEID_FC919,
		PCI_ANY_ID, PCI_ANY_ID पूर्ण,
	अणु PCI_VENDOR_ID_LSI_LOGIC, MPI_MANUFACTPAGE_DEVICEID_FC929,
		PCI_ANY_ID, PCI_ANY_ID पूर्ण,
	अणु PCI_VENDOR_ID_LSI_LOGIC, MPI_MANUFACTPAGE_DEVICEID_FC919X,
		PCI_ANY_ID, PCI_ANY_ID पूर्ण,
	अणु PCI_VENDOR_ID_LSI_LOGIC, MPI_MANUFACTPAGE_DEVICEID_FC929X,
		PCI_ANY_ID, PCI_ANY_ID पूर्ण,
	अणु PCI_VENDOR_ID_LSI_LOGIC, MPI_MANUFACTPAGE_DEVICEID_FC939X,
		PCI_ANY_ID, PCI_ANY_ID पूर्ण,
	अणु PCI_VENDOR_ID_LSI_LOGIC, MPI_MANUFACTPAGE_DEVICEID_FC949X,
		PCI_ANY_ID, PCI_ANY_ID पूर्ण,
	अणु PCI_VENDOR_ID_LSI_LOGIC, MPI_MANUFACTPAGE_DEVICEID_FC949E,
		PCI_ANY_ID, PCI_ANY_ID पूर्ण,
	अणु PCI_VENDOR_ID_BROCADE, MPI_MANUFACTPAGE_DEVICEID_FC949E,
		PCI_ANY_ID, PCI_ANY_ID पूर्ण,
	अणु0पूर्ण	/* Terminating entry */
पूर्ण;
MODULE_DEVICE_TABLE(pci, mptfc_pci_table);

अटल काष्ठा scsi_transport_ढाँचा *mptfc_transport_ढाँचा = शून्य;

अटल काष्ठा fc_function_ढाँचा mptfc_transport_functions = अणु
	.dd_fcrport_size = 8,
	.show_host_node_name = 1,
	.show_host_port_name = 1,
	.show_host_supported_classes = 1,
	.show_host_port_id = 1,
	.show_rport_supported_classes = 1,
	.show_starget_node_name = 1,
	.show_starget_port_name = 1,
	.show_starget_port_id = 1,
	.set_rport_dev_loss_पंचांगo = mptfc_set_rport_loss_पंचांगo,
	.show_rport_dev_loss_पंचांगo = 1,
	.show_host_supported_speeds = 1,
	.show_host_maxframe_size = 1,
	.show_host_speed = 1,
	.show_host_fabric_name = 1,
	.show_host_port_type = 1,
	.show_host_port_state = 1,
	.show_host_symbolic_name = 1,
पूर्ण;

अटल पूर्णांक
mptfc_block_error_handler(काष्ठा scsi_cmnd *SCpnt,
			  पूर्णांक (*func)(काष्ठा scsi_cmnd *SCpnt),
			  स्थिर अक्षर *caller)
अणु
	MPT_SCSI_HOST		*hd;
	काष्ठा scsi_device	*sdev = SCpnt->device;
	काष्ठा Scsi_Host	*shost = sdev->host;
	काष्ठा fc_rport		*rport = starget_to_rport(scsi_target(sdev));
	अचिन्हित दीर्घ		flags;
	पूर्णांक			पढ़ोy;
	MPT_ADAPTER 		*ioc;
	पूर्णांक			loops = 40;	/* seconds */

	hd = shost_priv(SCpnt->device->host);
	ioc = hd->ioc;
	spin_lock_irqsave(shost->host_lock, flags);
	जबतक ((पढ़ोy = fc_remote_port_chkपढ़ोy(rport) >> 16) == DID_IMM_RETRY
	 || (loops > 0 && ioc->active == 0)) अणु
		spin_unlock_irqrestore(shost->host_lock, flags);
		dfcprपूर्णांकk (ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT
			"mptfc_block_error_handler.%d: %d:%llu, port status is "
			"%x, active flag %d, deferring %s recovery.\n",
			ioc->name, ioc->sh->host_no,
			SCpnt->device->id, SCpnt->device->lun,
			पढ़ोy, ioc->active, caller));
		msleep(1000);
		spin_lock_irqsave(shost->host_lock, flags);
		loops --;
	पूर्ण
	spin_unlock_irqrestore(shost->host_lock, flags);

	अगर (पढ़ोy == DID_NO_CONNECT || !SCpnt->device->hostdata
	 || ioc->active == 0) अणु
		dfcprपूर्णांकk (ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT
			"%s.%d: %d:%llu, failing recovery, "
			"port state %x, active %d, vdevice %p.\n", caller,
			ioc->name, ioc->sh->host_no,
			SCpnt->device->id, SCpnt->device->lun, पढ़ोy,
			ioc->active, SCpnt->device->hostdata));
		वापस FAILED;
	पूर्ण
	dfcprपूर्णांकk (ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT
		"%s.%d: %d:%llu, executing recovery.\n", caller,
		ioc->name, ioc->sh->host_no,
		SCpnt->device->id, SCpnt->device->lun));
	वापस (*func)(SCpnt);
पूर्ण

अटल पूर्णांक
mptfc_पात(काष्ठा scsi_cmnd *SCpnt)
अणु
	वापस
	    mptfc_block_error_handler(SCpnt, mptscsih_पात, __func__);
पूर्ण

अटल पूर्णांक
mptfc_dev_reset(काष्ठा scsi_cmnd *SCpnt)
अणु
	वापस
	    mptfc_block_error_handler(SCpnt, mptscsih_dev_reset, __func__);
पूर्ण

अटल पूर्णांक
mptfc_bus_reset(काष्ठा scsi_cmnd *SCpnt)
अणु
	वापस
	    mptfc_block_error_handler(SCpnt, mptscsih_bus_reset, __func__);
पूर्ण

अटल व्योम
mptfc_set_rport_loss_पंचांगo(काष्ठा fc_rport *rport, uपूर्णांक32_t समयout)
अणु
	अगर (समयout > 0)
		rport->dev_loss_पंचांगo = समयout;
	अन्यथा
		rport->dev_loss_पंचांगo = mptfc_dev_loss_पंचांगo;
पूर्ण

अटल पूर्णांक
mptfc_FcDevPage0_cmp_func(स्थिर व्योम *a, स्थिर व्योम *b)
अणु
	FCDevicePage0_t **aa = (FCDevicePage0_t **)a;
	FCDevicePage0_t **bb = (FCDevicePage0_t **)b;

	अगर ((*aa)->CurrentBus == (*bb)->CurrentBus) अणु
		अगर ((*aa)->CurrentTargetID == (*bb)->CurrentTargetID)
			वापस 0;
		अगर ((*aa)->CurrentTargetID < (*bb)->CurrentTargetID)
			वापस -1;
		वापस 1;
	पूर्ण
	अगर ((*aa)->CurrentBus < (*bb)->CurrentBus)
		वापस -1;
	वापस 1;
पूर्ण

अटल पूर्णांक
mptfc_GetFcDevPage0(MPT_ADAPTER *ioc, पूर्णांक ioc_port,
	व्योम(*func)(MPT_ADAPTER *ioc,पूर्णांक channel, FCDevicePage0_t *arg))
अणु
	ConfigPageHeader_t	 hdr;
	CONFIGPARMS		 cfg;
	FCDevicePage0_t		*ppage0_alloc, *fc;
	dma_addr_t		 page0_dma;
	पूर्णांक			 data_sz;
	पूर्णांक			 ii;

	FCDevicePage0_t		*p0_array=शून्य, *p_p0;
	FCDevicePage0_t		**pp0_array=शून्य, **p_pp0;

	पूर्णांक			 rc = -ENOMEM;
	U32			 port_id = 0xffffff;
	पूर्णांक			 num_targ = 0;
	पूर्णांक			 max_bus = ioc->facts.MaxBuses;
	पूर्णांक			 max_targ;

	max_targ = (ioc->facts.MaxDevices == 0) ? 256 : ioc->facts.MaxDevices;

	data_sz = माप(FCDevicePage0_t) * max_bus * max_targ;
	p_p0 = p0_array =  kzalloc(data_sz, GFP_KERNEL);
	अगर (!p0_array)
		जाओ out;

	data_sz = माप(FCDevicePage0_t *) * max_bus * max_targ;
	p_pp0 = pp0_array = kzalloc(data_sz, GFP_KERNEL);
	अगर (!pp0_array)
		जाओ out;

	करो अणु
		/* Get FC Device Page 0 header */
		hdr.PageVersion = 0;
		hdr.PageLength = 0;
		hdr.PageNumber = 0;
		hdr.PageType = MPI_CONFIG_PAGETYPE_FC_DEVICE;
		cfg.cfghdr.hdr = &hdr;
		cfg.physAddr = -1;
		cfg.action = MPI_CONFIG_ACTION_PAGE_HEADER;
		cfg.dir = 0;
		cfg.pageAddr = port_id;
		cfg.समयout = 0;

		अगर ((rc = mpt_config(ioc, &cfg)) != 0)
			अवरोध;

		अगर (hdr.PageLength <= 0)
			अवरोध;

		data_sz = hdr.PageLength * 4;
		ppage0_alloc = pci_alloc_consistent(ioc->pcidev, data_sz,
		    					&page0_dma);
		rc = -ENOMEM;
		अगर (!ppage0_alloc)
			अवरोध;

		cfg.physAddr = page0_dma;
		cfg.action = MPI_CONFIG_ACTION_PAGE_READ_CURRENT;

		अगर ((rc = mpt_config(ioc, &cfg)) == 0) अणु
			ppage0_alloc->PortIdentअगरier =
				le32_to_cpu(ppage0_alloc->PortIdentअगरier);

			ppage0_alloc->WWNN.Low =
				le32_to_cpu(ppage0_alloc->WWNN.Low);

			ppage0_alloc->WWNN.High =
				le32_to_cpu(ppage0_alloc->WWNN.High);

			ppage0_alloc->WWPN.Low =
				le32_to_cpu(ppage0_alloc->WWPN.Low);

			ppage0_alloc->WWPN.High =
				le32_to_cpu(ppage0_alloc->WWPN.High);

			ppage0_alloc->BBCredit =
				le16_to_cpu(ppage0_alloc->BBCredit);

			ppage0_alloc->MaxRxFrameSize =
				le16_to_cpu(ppage0_alloc->MaxRxFrameSize);

			port_id = ppage0_alloc->PortIdentअगरier;
			num_targ++;
			*p_p0 = *ppage0_alloc;	/* save data */
			*p_pp0++ = p_p0++;	/* save addr */
		पूर्ण
		pci_मुक्त_consistent(ioc->pcidev, data_sz,
		    			(u8 *) ppage0_alloc, page0_dma);
		अगर (rc != 0)
			अवरोध;

	पूर्ण जबतक (port_id <= 0xff0000);

	अगर (num_targ) अणु
		/* sort array */
		अगर (num_targ > 1)
			sort (pp0_array, num_targ, माप(FCDevicePage0_t *),
				mptfc_FcDevPage0_cmp_func, शून्य);
		/* call caller's func क्रम each targ */
		क्रम (ii = 0; ii < num_targ;  ii++) अणु
			fc = *(pp0_array+ii);
			func(ioc, ioc_port, fc);
		पूर्ण
	पूर्ण

 out:
	kमुक्त(pp0_array);
	kमुक्त(p0_array);
	वापस rc;
पूर्ण

अटल पूर्णांक
mptfc_generate_rport_ids(FCDevicePage0_t *pg0, काष्ठा fc_rport_identअगरiers *rid)
अणु
	/* not currently usable */
	अगर (pg0->Flags & (MPI_FC_DEVICE_PAGE0_FLAGS_PLOGI_INVALID |
			  MPI_FC_DEVICE_PAGE0_FLAGS_PRLI_INVALID))
		वापस -1;

	अगर (!(pg0->Flags & MPI_FC_DEVICE_PAGE0_FLAGS_TARGETID_BUS_VALID))
		वापस -1;

	अगर (!(pg0->Protocol & MPI_FC_DEVICE_PAGE0_PROT_FCP_TARGET))
		वापस -1;

	/*
	 * board data काष्ठाure alपढ़ोy normalized to platक्रमm endianness
	 * shअगरted to aव्योम unaligned access on 64 bit architecture
	 */
	rid->node_name = ((u64)pg0->WWNN.High) << 32 | (u64)pg0->WWNN.Low;
	rid->port_name = ((u64)pg0->WWPN.High) << 32 | (u64)pg0->WWPN.Low;
	rid->port_id =   pg0->PortIdentअगरier;
	rid->roles = FC_RPORT_ROLE_UNKNOWN;

	वापस 0;
पूर्ण

अटल व्योम
mptfc_रेजिस्टर_dev(MPT_ADAPTER *ioc, पूर्णांक channel, FCDevicePage0_t *pg0)
अणु
	काष्ठा fc_rport_identअगरiers rport_ids;
	काष्ठा fc_rport		*rport;
	काष्ठा mptfc_rport_info	*ri;
	पूर्णांक			new_ri = 1;
	u64			pn, nn;
	VirtTarget		*vtarget;
	u32			roles = FC_RPORT_ROLE_UNKNOWN;

	अगर (mptfc_generate_rport_ids(pg0, &rport_ids) < 0)
		वापस;

	roles |= FC_RPORT_ROLE_FCP_TARGET;
	अगर (pg0->Protocol & MPI_FC_DEVICE_PAGE0_PROT_FCP_INITIATOR)
		roles |= FC_RPORT_ROLE_FCP_INITIATOR;

	/* scan list looking क्रम a match */
	list_क्रम_each_entry(ri, &ioc->fc_rports, list) अणु
		pn = (u64)ri->pg0.WWPN.High << 32 | (u64)ri->pg0.WWPN.Low;
		अगर (pn == rport_ids.port_name) अणु	/* match */
			list_move_tail(&ri->list, &ioc->fc_rports);
			new_ri = 0;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (new_ri) अणु	/* allocate one */
		ri = kzalloc(माप(काष्ठा mptfc_rport_info), GFP_KERNEL);
		अगर (!ri)
			वापस;
		list_add_tail(&ri->list, &ioc->fc_rports);
	पूर्ण

	ri->pg0 = *pg0;	/* add/update pg0 data */
	ri->flags &= ~MPT_RPORT_INFO_FLAGS_MISSING;

	/* MPT_RPORT_INFO_FLAGS_REGISTERED - rport not previously deleted */
	अगर (!(ri->flags & MPT_RPORT_INFO_FLAGS_REGISTERED)) अणु
		ri->flags |= MPT_RPORT_INFO_FLAGS_REGISTERED;
		rport = fc_remote_port_add(ioc->sh, channel, &rport_ids);
		अगर (rport) अणु
			ri->rport = rport;
			अगर (new_ri) /* may have been reset by user */
				rport->dev_loss_पंचांगo = mptfc_dev_loss_पंचांगo;
			/*
			 * अगर alपढ़ोy mapped, remap here.  If not mapped,
			 * target_alloc will allocate vtarget and map,
			 * slave_alloc will fill in vdevice from vtarget.
			 */
			अगर (ri->starget) अणु
				vtarget = ri->starget->hostdata;
				अगर (vtarget) अणु
					vtarget->id = pg0->CurrentTargetID;
					vtarget->channel = pg0->CurrentBus;
					vtarget->deleted = 0;
				पूर्ण
			पूर्ण
			*((काष्ठा mptfc_rport_info **)rport->dd_data) = ri;
			/* scan will be scheduled once rport becomes a target */
			fc_remote_port_rolechg(rport,roles);

			pn = (u64)ri->pg0.WWPN.High << 32 | (u64)ri->pg0.WWPN.Low;
			nn = (u64)ri->pg0.WWNN.High << 32 | (u64)ri->pg0.WWNN.Low;
			dfcprपूर्णांकk (ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT
				"mptfc_reg_dev.%d: %x, %llx / %llx, tid %d, "
				"rport tid %d, tmo %d\n",
					ioc->name,
					ioc->sh->host_no,
					pg0->PortIdentअगरier,
					(अचिन्हित दीर्घ दीर्घ)nn,
					(अचिन्हित दीर्घ दीर्घ)pn,
					pg0->CurrentTargetID,
					ri->rport->scsi_target_id,
					ri->rport->dev_loss_पंचांगo));
		पूर्ण अन्यथा अणु
			list_del(&ri->list);
			kमुक्त(ri);
			ri = शून्य;
		पूर्ण
	पूर्ण
पूर्ण

/*
 *	OS entry poपूर्णांक to allow क्रम host driver to मुक्त allocated memory
 *	Called अगर no device present or device being unloaded
 */
अटल व्योम
mptfc_target_destroy(काष्ठा scsi_target *starget)
अणु
	काष्ठा fc_rport		*rport;
	काष्ठा mptfc_rport_info *ri;

	rport = starget_to_rport(starget);
	अगर (rport) अणु
		ri = *((काष्ठा mptfc_rport_info **)rport->dd_data);
		अगर (ri)	/* better be! */
			ri->starget = शून्य;
	पूर्ण
	kमुक्त(starget->hostdata);
	starget->hostdata = शून्य;
पूर्ण

/*
 *	OS entry poपूर्णांक to allow host driver to alloc memory
 *	क्रम each scsi target. Called once per device the bus scan.
 *	Return non-zero अगर allocation fails.
 */
अटल पूर्णांक
mptfc_target_alloc(काष्ठा scsi_target *starget)
अणु
	VirtTarget		*vtarget;
	काष्ठा fc_rport		*rport;
	काष्ठा mptfc_rport_info *ri;
	पूर्णांक			rc;

	vtarget = kzalloc(माप(VirtTarget), GFP_KERNEL);
	अगर (!vtarget)
		वापस -ENOMEM;
	starget->hostdata = vtarget;

	rc = -ENODEV;
	rport = starget_to_rport(starget);
	अगर (rport) अणु
		ri = *((काष्ठा mptfc_rport_info **)rport->dd_data);
		अगर (ri) अणु	/* better be! */
			vtarget->id = ri->pg0.CurrentTargetID;
			vtarget->channel = ri->pg0.CurrentBus;
			ri->starget = starget;
			rc = 0;
		पूर्ण
	पूर्ण
	अगर (rc != 0) अणु
		kमुक्त(vtarget);
		starget->hostdata = शून्य;
	पूर्ण

	वापस rc;
पूर्ण
/*
 *	mptfc_dump_lun_info
 *	@ioc
 *	@rport
 *	@sdev
 *
 */
अटल व्योम
mptfc_dump_lun_info(MPT_ADAPTER *ioc, काष्ठा fc_rport *rport, काष्ठा scsi_device *sdev,
		VirtTarget *vtarget)
अणु
	u64 nn, pn;
	काष्ठा mptfc_rport_info *ri;

	ri = *((काष्ठा mptfc_rport_info **)rport->dd_data);
	pn = (u64)ri->pg0.WWPN.High << 32 | (u64)ri->pg0.WWPN.Low;
	nn = (u64)ri->pg0.WWNN.High << 32 | (u64)ri->pg0.WWNN.Low;
	dfcprपूर्णांकk (ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT
		"mptfc_slv_alloc.%d: num_luns %d, sdev.id %d, "
		"CurrentTargetID %d, %x %llx %llx\n",
		ioc->name,
		sdev->host->host_no,
		vtarget->num_luns,
		sdev->id, ri->pg0.CurrentTargetID,
		ri->pg0.PortIdentअगरier,
		(अचिन्हित दीर्घ दीर्घ)pn,
		(अचिन्हित दीर्घ दीर्घ)nn));
पूर्ण


/*
 *	OS entry poपूर्णांक to allow host driver to alloc memory
 *	क्रम each scsi device. Called once per device the bus scan.
 *	Return non-zero अगर allocation fails.
 *	Init memory once per LUN.
 */
अटल पूर्णांक
mptfc_slave_alloc(काष्ठा scsi_device *sdev)
अणु
	MPT_SCSI_HOST		*hd;
	VirtTarget		*vtarget;
	VirtDevice		*vdevice;
	काष्ठा scsi_target	*starget;
	काष्ठा fc_rport		*rport;
	MPT_ADAPTER 		*ioc;

	starget = scsi_target(sdev);
	rport = starget_to_rport(starget);

	अगर (!rport || fc_remote_port_chkपढ़ोy(rport))
		वापस -ENXIO;

	hd = shost_priv(sdev->host);
	ioc = hd->ioc;

	vdevice = kzalloc(माप(VirtDevice), GFP_KERNEL);
	अगर (!vdevice) अणु
		prपूर्णांकk(MYIOC_s_ERR_FMT "slave_alloc kmalloc(%zd) FAILED!\n",
				ioc->name, माप(VirtDevice));
		वापस -ENOMEM;
	पूर्ण


	sdev->hostdata = vdevice;
	vtarget = starget->hostdata;

	अगर (vtarget->num_luns == 0) अणु
		vtarget->ioc_id = ioc->id;
		vtarget->tflags = MPT_TARGET_FLAGS_Q_YES;
	पूर्ण

	vdevice->vtarget = vtarget;
	vdevice->lun = sdev->lun;

	vtarget->num_luns++;


	mptfc_dump_lun_info(ioc, rport, sdev, vtarget);

	वापस 0;
पूर्ण

अटल पूर्णांक
mptfc_qcmd(काष्ठा Scsi_Host *shost, काष्ठा scsi_cmnd *SCpnt)
अणु
	काष्ठा mptfc_rport_info	*ri;
	काष्ठा fc_rport	*rport = starget_to_rport(scsi_target(SCpnt->device));
	पूर्णांक		err;
	VirtDevice	*vdevice = SCpnt->device->hostdata;

	अगर (!vdevice || !vdevice->vtarget) अणु
		SCpnt->result = DID_NO_CONNECT << 16;
		SCpnt->scsi_करोne(SCpnt);
		वापस 0;
	पूर्ण

	err = fc_remote_port_chkपढ़ोy(rport);
	अगर (unlikely(err)) अणु
		SCpnt->result = err;
		SCpnt->scsi_करोne(SCpnt);
		वापस 0;
	पूर्ण

	/* dd_data is null until finished adding target */
	ri = *((काष्ठा mptfc_rport_info **)rport->dd_data);
	अगर (unlikely(!ri)) अणु
		SCpnt->result = DID_IMM_RETRY << 16;
		SCpnt->scsi_करोne(SCpnt);
		वापस 0;
	पूर्ण

	वापस mptscsih_qcmd(SCpnt);
पूर्ण

/*
 *	mptfc_display_port_link_speed - displaying link speed
 *	@ioc: Poपूर्णांकer to MPT_ADAPTER काष्ठाure
 *	@portnum: IOC Port number
 *	@pp0dest: port page0 data payload
 *
 */
अटल व्योम
mptfc_display_port_link_speed(MPT_ADAPTER *ioc, पूर्णांक portnum, FCPortPage0_t *pp0dest)
अणु
	u8	old_speed, new_speed, state;
	अक्षर	*old, *new;

	अगर (portnum >= 2)
		वापस;

	old_speed = ioc->fc_link_speed[portnum];
	new_speed = pp0dest->CurrentSpeed;
	state = pp0dest->PortState;

	अगर (state != MPI_FCPORTPAGE0_PORTSTATE_OFFLINE &&
	    new_speed != MPI_FCPORTPAGE0_CURRENT_SPEED_UNKNOWN) अणु

		old = old_speed == MPI_FCPORTPAGE0_CURRENT_SPEED_1GBIT ? "1 Gbps" :
		       old_speed == MPI_FCPORTPAGE0_CURRENT_SPEED_2GBIT ? "2 Gbps" :
			old_speed == MPI_FCPORTPAGE0_CURRENT_SPEED_4GBIT ? "4 Gbps" :
			 "Unknown";
		new = new_speed == MPI_FCPORTPAGE0_CURRENT_SPEED_1GBIT ? "1 Gbps" :
		       new_speed == MPI_FCPORTPAGE0_CURRENT_SPEED_2GBIT ? "2 Gbps" :
			new_speed == MPI_FCPORTPAGE0_CURRENT_SPEED_4GBIT ? "4 Gbps" :
			 "Unknown";
		अगर (old_speed == 0)
			prपूर्णांकk(MYIOC_s_NOTE_FMT
				"FC Link Established, Speed = %s\n",
				ioc->name, new);
		अन्यथा अगर (old_speed != new_speed)
			prपूर्णांकk(MYIOC_s_WARN_FMT
				"FC Link Speed Change, Old Speed = %s, New Speed = %s\n",
				ioc->name, old, new);

		ioc->fc_link_speed[portnum] = new_speed;
	पूर्ण
पूर्ण

/*
 *	mptfc_GetFcPortPage0 - Fetch FCPort config Page0.
 *	@ioc: Poपूर्णांकer to MPT_ADAPTER काष्ठाure
 *	@portnum: IOC Port number
 *
 *	Return: 0 क्रम success
 *	-ENOMEM अगर no memory available
 *		-EPERM अगर not allowed due to ISR context
 *		-EAGAIN अगर no msg frames currently available
 *		-EFAULT क्रम non-successful reply or no reply (समयout)
 *		-EINVAL portnum arg out of range (hardwired to two elements)
 */
अटल पूर्णांक
mptfc_GetFcPortPage0(MPT_ADAPTER *ioc, पूर्णांक portnum)
अणु
	ConfigPageHeader_t	 hdr;
	CONFIGPARMS		 cfg;
	FCPortPage0_t		*ppage0_alloc;
	FCPortPage0_t		*pp0dest;
	dma_addr_t		 page0_dma;
	पूर्णांक			 data_sz;
	पूर्णांक			 copy_sz;
	पूर्णांक			 rc;
	पूर्णांक			 count = 400;

	अगर (portnum > 1)
		वापस -EINVAL;

	/* Get FCPort Page 0 header */
	hdr.PageVersion = 0;
	hdr.PageLength = 0;
	hdr.PageNumber = 0;
	hdr.PageType = MPI_CONFIG_PAGETYPE_FC_PORT;
	cfg.cfghdr.hdr = &hdr;
	cfg.physAddr = -1;
	cfg.action = MPI_CONFIG_ACTION_PAGE_HEADER;
	cfg.dir = 0;
	cfg.pageAddr = portnum;
	cfg.समयout = 0;

	अगर ((rc = mpt_config(ioc, &cfg)) != 0)
		वापस rc;

	अगर (hdr.PageLength == 0)
		वापस 0;

	data_sz = hdr.PageLength * 4;
	rc = -ENOMEM;
	ppage0_alloc = pci_alloc_consistent(ioc->pcidev, data_sz, &page0_dma);
	अगर (ppage0_alloc) अणु

 try_again:
		स_रखो((u8 *)ppage0_alloc, 0, data_sz);
		cfg.physAddr = page0_dma;
		cfg.action = MPI_CONFIG_ACTION_PAGE_READ_CURRENT;

		अगर ((rc = mpt_config(ioc, &cfg)) == 0) अणु
			/* save the data */
			pp0dest = &ioc->fc_port_page0[portnum];
			copy_sz = min_t(पूर्णांक, माप(FCPortPage0_t), data_sz);
			स_नकल(pp0dest, ppage0_alloc, copy_sz);

			/*
			 *	Normalize endianness of काष्ठाure data,
			 *	by byte-swapping all > 1 byte fields!
			 */
			pp0dest->Flags = le32_to_cpu(pp0dest->Flags);
			pp0dest->PortIdentअगरier = le32_to_cpu(pp0dest->PortIdentअगरier);
			pp0dest->WWNN.Low = le32_to_cpu(pp0dest->WWNN.Low);
			pp0dest->WWNN.High = le32_to_cpu(pp0dest->WWNN.High);
			pp0dest->WWPN.Low = le32_to_cpu(pp0dest->WWPN.Low);
			pp0dest->WWPN.High = le32_to_cpu(pp0dest->WWPN.High);
			pp0dest->SupportedServiceClass = le32_to_cpu(pp0dest->SupportedServiceClass);
			pp0dest->SupportedSpeeds = le32_to_cpu(pp0dest->SupportedSpeeds);
			pp0dest->CurrentSpeed = le32_to_cpu(pp0dest->CurrentSpeed);
			pp0dest->MaxFrameSize = le32_to_cpu(pp0dest->MaxFrameSize);
			pp0dest->FabricWWNN.Low = le32_to_cpu(pp0dest->FabricWWNN.Low);
			pp0dest->FabricWWNN.High = le32_to_cpu(pp0dest->FabricWWNN.High);
			pp0dest->FabricWWPN.Low = le32_to_cpu(pp0dest->FabricWWPN.Low);
			pp0dest->FabricWWPN.High = le32_to_cpu(pp0dest->FabricWWPN.High);
			pp0dest->DiscoveredPortsCount = le32_to_cpu(pp0dest->DiscoveredPortsCount);
			pp0dest->MaxInitiators = le32_to_cpu(pp0dest->MaxInitiators);

			/*
			 * अगर still करोing discovery,
			 * hang loose a जबतक until finished
			 */
			अगर ((pp0dest->PortState == MPI_FCPORTPAGE0_PORTSTATE_UNKNOWN) ||
			    (pp0dest->PortState == MPI_FCPORTPAGE0_PORTSTATE_ONLINE &&
			     (pp0dest->Flags & MPI_FCPORTPAGE0_FLAGS_ATTACH_TYPE_MASK)
			      == MPI_FCPORTPAGE0_FLAGS_ATTACH_NO_INIT)) अणु
				अगर (count-- > 0) अणु
					msleep(100);
					जाओ try_again;
				पूर्ण
				prपूर्णांकk(MYIOC_s_INFO_FMT "Firmware discovery not"
							" complete.\n",
						ioc->name);
			पूर्ण
			mptfc_display_port_link_speed(ioc, portnum, pp0dest);
		पूर्ण

		pci_मुक्त_consistent(ioc->pcidev, data_sz, (u8 *) ppage0_alloc, page0_dma);
	पूर्ण

	वापस rc;
पूर्ण

अटल पूर्णांक
mptfc_WriteFcPortPage1(MPT_ADAPTER *ioc, पूर्णांक portnum)
अणु
	ConfigPageHeader_t	 hdr;
	CONFIGPARMS		 cfg;
	पूर्णांक			 rc;

	अगर (portnum > 1)
		वापस -EINVAL;

	अगर (!(ioc->fc_data.fc_port_page1[portnum].data))
		वापस -EINVAL;

	/* get fcport page 1 header */
	hdr.PageVersion = 0;
	hdr.PageLength = 0;
	hdr.PageNumber = 1;
	hdr.PageType = MPI_CONFIG_PAGETYPE_FC_PORT;
	cfg.cfghdr.hdr = &hdr;
	cfg.physAddr = -1;
	cfg.action = MPI_CONFIG_ACTION_PAGE_HEADER;
	cfg.dir = 0;
	cfg.pageAddr = portnum;
	cfg.समयout = 0;

	अगर ((rc = mpt_config(ioc, &cfg)) != 0)
		वापस rc;

	अगर (hdr.PageLength == 0)
		वापस -ENODEV;

	अगर (hdr.PageLength*4 != ioc->fc_data.fc_port_page1[portnum].pg_sz)
		वापस -EINVAL;

	cfg.physAddr = ioc->fc_data.fc_port_page1[portnum].dma;
	cfg.action = MPI_CONFIG_ACTION_PAGE_WRITE_CURRENT;
	cfg.dir = 1;

	rc = mpt_config(ioc, &cfg);

	वापस rc;
पूर्ण

अटल पूर्णांक
mptfc_GetFcPortPage1(MPT_ADAPTER *ioc, पूर्णांक portnum)
अणु
	ConfigPageHeader_t	 hdr;
	CONFIGPARMS		 cfg;
	FCPortPage1_t		*page1_alloc;
	dma_addr_t		 page1_dma;
	पूर्णांक			 data_sz;
	पूर्णांक			 rc;

	अगर (portnum > 1)
		वापस -EINVAL;

	/* get fcport page 1 header */
	hdr.PageVersion = 0;
	hdr.PageLength = 0;
	hdr.PageNumber = 1;
	hdr.PageType = MPI_CONFIG_PAGETYPE_FC_PORT;
	cfg.cfghdr.hdr = &hdr;
	cfg.physAddr = -1;
	cfg.action = MPI_CONFIG_ACTION_PAGE_HEADER;
	cfg.dir = 0;
	cfg.pageAddr = portnum;
	cfg.समयout = 0;

	अगर ((rc = mpt_config(ioc, &cfg)) != 0)
		वापस rc;

	अगर (hdr.PageLength == 0)
		वापस -ENODEV;

start_over:

	अगर (ioc->fc_data.fc_port_page1[portnum].data == शून्य) अणु
		data_sz = hdr.PageLength * 4;
		अगर (data_sz < माप(FCPortPage1_t))
			data_sz = माप(FCPortPage1_t);

		page1_alloc = pci_alloc_consistent(ioc->pcidev,
						data_sz,
						&page1_dma);
		अगर (!page1_alloc)
			वापस -ENOMEM;
	पूर्ण
	अन्यथा अणु
		page1_alloc = ioc->fc_data.fc_port_page1[portnum].data;
		page1_dma = ioc->fc_data.fc_port_page1[portnum].dma;
		data_sz = ioc->fc_data.fc_port_page1[portnum].pg_sz;
		अगर (hdr.PageLength * 4 > data_sz) अणु
			ioc->fc_data.fc_port_page1[portnum].data = शून्य;
			pci_मुक्त_consistent(ioc->pcidev, data_sz, (u8 *)
				page1_alloc, page1_dma);
			जाओ start_over;
		पूर्ण
	पूर्ण

	cfg.physAddr = page1_dma;
	cfg.action = MPI_CONFIG_ACTION_PAGE_READ_CURRENT;

	अगर ((rc = mpt_config(ioc, &cfg)) == 0) अणु
		ioc->fc_data.fc_port_page1[portnum].data = page1_alloc;
		ioc->fc_data.fc_port_page1[portnum].pg_sz = data_sz;
		ioc->fc_data.fc_port_page1[portnum].dma = page1_dma;
	पूर्ण
	अन्यथा अणु
		ioc->fc_data.fc_port_page1[portnum].data = शून्य;
		pci_मुक्त_consistent(ioc->pcidev, data_sz, (u8 *)
			page1_alloc, page1_dma);
	पूर्ण

	वापस rc;
पूर्ण

अटल व्योम
mptfc_SetFcPortPage1_शेषs(MPT_ADAPTER *ioc)
अणु
	पूर्णांक		ii;
	FCPortPage1_t	*pp1;

	#घोषणा MPTFC_FW_DEVICE_TIMEOUT	(1)
	#घोषणा MPTFC_FW_IO_PEND_TIMEOUT (1)
	#घोषणा ON_FLAGS  (MPI_FCPORTPAGE1_FLAGS_IMMEDIATE_ERROR_REPLY)
	#घोषणा OFF_FLAGS (MPI_FCPORTPAGE1_FLAGS_VERBOSE_RESCAN_EVENTS)

	क्रम (ii=0; ii<ioc->facts.NumberOfPorts; ii++) अणु
		अगर (mptfc_GetFcPortPage1(ioc, ii) != 0)
			जारी;
		pp1 = ioc->fc_data.fc_port_page1[ii].data;
		अगर ((pp1->InitiatorDeviceTimeout == MPTFC_FW_DEVICE_TIMEOUT)
		 && (pp1->InitiatorIoPendTimeout == MPTFC_FW_IO_PEND_TIMEOUT)
		 && ((pp1->Flags & ON_FLAGS) == ON_FLAGS)
		 && ((pp1->Flags & OFF_FLAGS) == 0))
			जारी;
		pp1->InitiatorDeviceTimeout = MPTFC_FW_DEVICE_TIMEOUT;
		pp1->InitiatorIoPendTimeout = MPTFC_FW_IO_PEND_TIMEOUT;
		pp1->Flags &= ~OFF_FLAGS;
		pp1->Flags |= ON_FLAGS;
		mptfc_WriteFcPortPage1(ioc, ii);
	पूर्ण
पूर्ण


अटल व्योम
mptfc_init_host_attr(MPT_ADAPTER *ioc,पूर्णांक portnum)
अणु
	अचिन्हित	class = 0;
	अचिन्हित	cos = 0;
	अचिन्हित	speed;
	अचिन्हित	port_type;
	अचिन्हित	port_state;
	FCPortPage0_t	*pp0;
	काष्ठा Scsi_Host *sh;
	अक्षर		*sn;

	/* करोn't know what to करो as only one scsi (fc) host was allocated */
	अगर (portnum != 0)
		वापस;

	pp0 = &ioc->fc_port_page0[portnum];
	sh = ioc->sh;

	sn = fc_host_symbolic_name(sh);
	snम_लिखो(sn, FC_SYMBOLIC_NAME_SIZE, "%s %s%08xh",
	    ioc->prod_name,
	    MPT_FW_REV_MAGIC_ID_STRING,
	    ioc->facts.FWVersion.Word);

	fc_host_tgtid_bind_type(sh) = FC_TGTID_BIND_BY_WWPN;

	fc_host_maxframe_size(sh) = pp0->MaxFrameSize;

	fc_host_node_name(sh) =
	    	(u64)pp0->WWNN.High << 32 | (u64)pp0->WWNN.Low;

	fc_host_port_name(sh) =
	    	(u64)pp0->WWPN.High << 32 | (u64)pp0->WWPN.Low;

	fc_host_port_id(sh) = pp0->PortIdentअगरier;

	class = pp0->SupportedServiceClass;
	अगर (class & MPI_FCPORTPAGE0_SUPPORT_CLASS_1)
		cos |= FC_COS_CLASS1;
	अगर (class & MPI_FCPORTPAGE0_SUPPORT_CLASS_2)
		cos |= FC_COS_CLASS2;
	अगर (class & MPI_FCPORTPAGE0_SUPPORT_CLASS_3)
		cos |= FC_COS_CLASS3;
	fc_host_supported_classes(sh) = cos;

	अगर (pp0->CurrentSpeed == MPI_FCPORTPAGE0_CURRENT_SPEED_1GBIT)
		speed = FC_PORTSPEED_1GBIT;
	अन्यथा अगर (pp0->CurrentSpeed == MPI_FCPORTPAGE0_CURRENT_SPEED_2GBIT)
		speed = FC_PORTSPEED_2GBIT;
	अन्यथा अगर (pp0->CurrentSpeed == MPI_FCPORTPAGE0_CURRENT_SPEED_4GBIT)
		speed = FC_PORTSPEED_4GBIT;
	अन्यथा अगर (pp0->CurrentSpeed == MPI_FCPORTPAGE0_CURRENT_SPEED_10GBIT)
		speed = FC_PORTSPEED_10GBIT;
	अन्यथा
		speed = FC_PORTSPEED_UNKNOWN;
	fc_host_speed(sh) = speed;

	speed = 0;
	अगर (pp0->SupportedSpeeds & MPI_FCPORTPAGE0_SUPPORT_1GBIT_SPEED)
		speed |= FC_PORTSPEED_1GBIT;
	अगर (pp0->SupportedSpeeds & MPI_FCPORTPAGE0_SUPPORT_2GBIT_SPEED)
		speed |= FC_PORTSPEED_2GBIT;
	अगर (pp0->SupportedSpeeds & MPI_FCPORTPAGE0_SUPPORT_4GBIT_SPEED)
		speed |= FC_PORTSPEED_4GBIT;
	अगर (pp0->SupportedSpeeds & MPI_FCPORTPAGE0_SUPPORT_10GBIT_SPEED)
		speed |= FC_PORTSPEED_10GBIT;
	fc_host_supported_speeds(sh) = speed;

	port_state = FC_PORTSTATE_UNKNOWN;
	अगर (pp0->PortState == MPI_FCPORTPAGE0_PORTSTATE_ONLINE)
		port_state = FC_PORTSTATE_ONLINE;
	अन्यथा अगर (pp0->PortState == MPI_FCPORTPAGE0_PORTSTATE_OFFLINE)
		port_state = FC_PORTSTATE_LINKDOWN;
	fc_host_port_state(sh) = port_state;

	port_type = FC_PORTTYPE_UNKNOWN;
	अगर (pp0->Flags & MPI_FCPORTPAGE0_FLAGS_ATTACH_POINT_TO_POINT)
		port_type = FC_PORTTYPE_PTP;
	अन्यथा अगर (pp0->Flags & MPI_FCPORTPAGE0_FLAGS_ATTACH_PRIVATE_LOOP)
		port_type = FC_PORTTYPE_LPORT;
	अन्यथा अगर (pp0->Flags & MPI_FCPORTPAGE0_FLAGS_ATTACH_PUBLIC_LOOP)
		port_type = FC_PORTTYPE_NLPORT;
	अन्यथा अगर (pp0->Flags & MPI_FCPORTPAGE0_FLAGS_ATTACH_FABRIC_सूचीECT)
		port_type = FC_PORTTYPE_NPORT;
	fc_host_port_type(sh) = port_type;

	fc_host_fabric_name(sh) =
	    (pp0->Flags & MPI_FCPORTPAGE0_FLAGS_FABRIC_WWN_VALID) ?
		(u64) pp0->FabricWWNN.High << 32 | (u64) pp0->FabricWWPN.Low :
		(u64)pp0->WWNN.High << 32 | (u64)pp0->WWNN.Low;

पूर्ण

अटल व्योम
mptfc_link_status_change(काष्ठा work_काष्ठा *work)
अणु
	MPT_ADAPTER             *ioc =
		container_of(work, MPT_ADAPTER, fc_rescan_work);
	पूर्णांक ii;

	क्रम (ii=0; ii < ioc->facts.NumberOfPorts; ii++)
		(व्योम) mptfc_GetFcPortPage0(ioc, ii);

पूर्ण

अटल व्योम
mptfc_setup_reset(काष्ठा work_काष्ठा *work)
अणु
	MPT_ADAPTER		*ioc =
		container_of(work, MPT_ADAPTER, fc_setup_reset_work);
	u64			pn;
	काष्ठा mptfc_rport_info *ri;
	काष्ठा scsi_target      *starget;
	VirtTarget              *vtarget;

	/* reset about to happen, delete (block) all rports */
	list_क्रम_each_entry(ri, &ioc->fc_rports, list) अणु
		अगर (ri->flags & MPT_RPORT_INFO_FLAGS_REGISTERED) अणु
			ri->flags &= ~MPT_RPORT_INFO_FLAGS_REGISTERED;
			fc_remote_port_delete(ri->rport);	/* won't sleep */
			ri->rport = शून्य;
			starget = ri->starget;
			अगर (starget) अणु
				vtarget = starget->hostdata;
				अगर (vtarget)
					vtarget->deleted = 1;
			पूर्ण

			pn = (u64)ri->pg0.WWPN.High << 32 |
			     (u64)ri->pg0.WWPN.Low;
			dfcprपूर्णांकk (ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT
				"mptfc_setup_reset.%d: %llx deleted\n",
				ioc->name,
				ioc->sh->host_no,
				(अचिन्हित दीर्घ दीर्घ)pn));
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम
mptfc_rescan_devices(काष्ठा work_काष्ठा *work)
अणु
	MPT_ADAPTER		*ioc =
		container_of(work, MPT_ADAPTER, fc_rescan_work);
	पूर्णांक			ii;
	u64			pn;
	काष्ठा mptfc_rport_info *ri;
	काष्ठा scsi_target      *starget;
	VirtTarget              *vtarget;

	/* start by tagging all ports as missing */
	list_क्रम_each_entry(ri, &ioc->fc_rports, list) अणु
		अगर (ri->flags & MPT_RPORT_INFO_FLAGS_REGISTERED) अणु
			ri->flags |= MPT_RPORT_INFO_FLAGS_MISSING;
		पूर्ण
	पूर्ण

	/*
	 * now rescan devices known to adapter,
	 * will reरेजिस्टर existing rports
	 */
	क्रम (ii=0; ii < ioc->facts.NumberOfPorts; ii++) अणु
		(व्योम) mptfc_GetFcPortPage0(ioc, ii);
		mptfc_init_host_attr(ioc, ii);	/* refresh */
		mptfc_GetFcDevPage0(ioc, ii, mptfc_रेजिस्टर_dev);
	पूर्ण

	/* delete devices still missing */
	list_क्रम_each_entry(ri, &ioc->fc_rports, list) अणु
		/* अगर newly missing, delete it */
		अगर (ri->flags & MPT_RPORT_INFO_FLAGS_MISSING) अणु

			ri->flags &= ~(MPT_RPORT_INFO_FLAGS_REGISTERED|
				       MPT_RPORT_INFO_FLAGS_MISSING);
			fc_remote_port_delete(ri->rport);	/* won't sleep */
			ri->rport = शून्य;
			starget = ri->starget;
			अगर (starget) अणु
				vtarget = starget->hostdata;
				अगर (vtarget)
					vtarget->deleted = 1;
			पूर्ण

			pn = (u64)ri->pg0.WWPN.High << 32 |
			     (u64)ri->pg0.WWPN.Low;
			dfcprपूर्णांकk (ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT
				"mptfc_rescan.%d: %llx deleted\n",
				ioc->name,
				ioc->sh->host_no,
				(अचिन्हित दीर्घ दीर्घ)pn));
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक
mptfc_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *id)
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

	अगर ((r = mpt_attach(pdev,id)) != 0)
		वापस r;

	ioc = pci_get_drvdata(pdev);
	ioc->DoneCtx = mptfcDoneCtx;
	ioc->TaskCtx = mptfcTaskCtx;
	ioc->InternalCtx = mptfcInternalCtx;

	/*  Added sanity check on पढ़ोiness of the MPT adapter.
	 */
	अगर (ioc->last_state != MPI_IOC_STATE_OPERATIONAL) अणु
		prपूर्णांकk(MYIOC_s_WARN_FMT
		  "Skipping because it's not operational!\n",
		  ioc->name);
		error = -ENODEV;
		जाओ out_mptfc_probe;
	पूर्ण

	अगर (!ioc->active) अणु
		prपूर्णांकk(MYIOC_s_WARN_FMT "Skipping because it's disabled!\n",
		  ioc->name);
		error = -ENODEV;
		जाओ out_mptfc_probe;
	पूर्ण

	/*  Sanity check - ensure at least 1 port is INITIATOR capable
	 */
	ioc_cap = 0;
	क्रम (ii=0; ii < ioc->facts.NumberOfPorts; ii++) अणु
		अगर (ioc->pfacts[ii].ProtocolFlags &
		    MPI_PORTFACTS_PROTOCOL_INITIATOR)
			ioc_cap ++;
	पूर्ण

	अगर (!ioc_cap) अणु
		prपूर्णांकk(MYIOC_s_WARN_FMT
			"Skipping ioc=%p because SCSI Initiator mode is NOT enabled!\n",
			ioc->name, ioc);
		वापस 0;
	पूर्ण

	sh = scsi_host_alloc(&mptfc_driver_ढाँचा, माप(MPT_SCSI_HOST));

	अगर (!sh) अणु
		prपूर्णांकk(MYIOC_s_WARN_FMT
			"Unable to register controller with SCSI subsystem\n",
			ioc->name);
		error = -1;
		जाओ out_mptfc_probe;
        पूर्ण

	spin_lock_init(&ioc->fc_rescan_work_lock);
	INIT_WORK(&ioc->fc_rescan_work, mptfc_rescan_devices);
	INIT_WORK(&ioc->fc_setup_reset_work, mptfc_setup_reset);
	INIT_WORK(&ioc->fc_lsc_work, mptfc_link_status_change);

	spin_lock_irqsave(&ioc->FreeQlock, flags);

	/* Attach the SCSI Host to the IOC काष्ठाure
	 */
	ioc->sh = sh;

	sh->io_port = 0;
	sh->n_io_port = 0;
	sh->irq = 0;

	/* set 16 byte cdb's */
	sh->max_cmd_len = 16;

	sh->max_id = ioc->pfacts->MaxDevices;
	sh->max_lun = max_lun;

	/* Required entry.
	 */
	sh->unique_id = ioc->id;

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

	spin_unlock_irqrestore(&ioc->FreeQlock, flags);

	hd = shost_priv(sh);
	hd->ioc = ioc;

	/* SCSI needs scsi_cmnd lookup table!
	 * (with size equal to req_depth*PtrSz!)
	 */
	ioc->ScsiLookup = kसुस्मृति(ioc->req_depth, माप(व्योम *), GFP_KERNEL);
	अगर (!ioc->ScsiLookup) अणु
		error = -ENOMEM;
		जाओ out_mptfc_probe;
	पूर्ण
	spin_lock_init(&ioc->scsi_lookup_lock);

	dprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT "ScsiLookup @ %p\n",
		 ioc->name, ioc->ScsiLookup));

	hd->last_queue_full = 0;

	sh->transportt = mptfc_transport_ढाँचा;
	error = scsi_add_host (sh, &ioc->pcidev->dev);
	अगर(error) अणु
		dprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_ERR_FMT
		  "scsi_add_host failed\n", ioc->name));
		जाओ out_mptfc_probe;
	पूर्ण

	/* initialize workqueue */

	snम_लिखो(ioc->fc_rescan_work_q_name, माप(ioc->fc_rescan_work_q_name),
		 "mptfc_wq_%d", sh->host_no);
	ioc->fc_rescan_work_q =
		alloc_ordered_workqueue(ioc->fc_rescan_work_q_name,
					WQ_MEM_RECLAIM);
	अगर (!ioc->fc_rescan_work_q) अणु
		error = -ENOMEM;
		जाओ out_mptfc_host;
	पूर्ण

	/*
	 *  Pre-fetch FC port WWN and stuff...
	 *  (FCPortPage0_t stuff)
	 */
	क्रम (ii=0; ii < ioc->facts.NumberOfPorts; ii++) अणु
		(व्योम) mptfc_GetFcPortPage0(ioc, ii);
	पूर्ण
	mptfc_SetFcPortPage1_शेषs(ioc);

	/*
	 * scan क्रम rports -
	 *	by करोing it via the workqueue, some locking is eliminated
	 */

	queue_work(ioc->fc_rescan_work_q, &ioc->fc_rescan_work);
	flush_workqueue(ioc->fc_rescan_work_q);

	वापस 0;

out_mptfc_host:
	scsi_हटाओ_host(sh);

out_mptfc_probe:

	mptscsih_हटाओ(pdev);
	वापस error;
पूर्ण

अटल काष्ठा pci_driver mptfc_driver = अणु
	.name		= "mptfc",
	.id_table	= mptfc_pci_table,
	.probe		= mptfc_probe,
	.हटाओ		= mptfc_हटाओ,
	.shutकरोwn	= mptscsih_shutकरोwn,
#अगर_घोषित CONFIG_PM
	.suspend	= mptscsih_suspend,
	.resume		= mptscsih_resume,
#पूर्ण_अगर
पूर्ण;

अटल पूर्णांक
mptfc_event_process(MPT_ADAPTER *ioc, EventNotअगरicationReply_t *pEvReply)
अणु
	MPT_SCSI_HOST *hd;
	u8 event = le32_to_cpu(pEvReply->Event) & 0xFF;
	अचिन्हित दीर्घ flags;
	पूर्णांक rc=1;

	अगर (ioc->bus_type != FC)
		वापस 0;

	devtverboseprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT "MPT event (=%02Xh) routed to SCSI host driver!\n",
			ioc->name, event));

	अगर (ioc->sh == शून्य ||
		((hd = shost_priv(ioc->sh)) == शून्य))
		वापस 1;

	चयन (event) अणु
	हाल MPI_EVENT_RESCAN:
		spin_lock_irqsave(&ioc->fc_rescan_work_lock, flags);
		अगर (ioc->fc_rescan_work_q) अणु
			queue_work(ioc->fc_rescan_work_q,
				   &ioc->fc_rescan_work);
		पूर्ण
		spin_unlock_irqrestore(&ioc->fc_rescan_work_lock, flags);
		अवरोध;
	हाल MPI_EVENT_LINK_STATUS_CHANGE:
		spin_lock_irqsave(&ioc->fc_rescan_work_lock, flags);
		अगर (ioc->fc_rescan_work_q) अणु
			queue_work(ioc->fc_rescan_work_q,
				   &ioc->fc_lsc_work);
		पूर्ण
		spin_unlock_irqrestore(&ioc->fc_rescan_work_lock, flags);
		अवरोध;
	शेष:
		rc = mptscsih_event_process(ioc,pEvReply);
		अवरोध;
	पूर्ण
	वापस rc;
पूर्ण

अटल पूर्णांक
mptfc_ioc_reset(MPT_ADAPTER *ioc, पूर्णांक reset_phase)
अणु
	पूर्णांक		rc;
	अचिन्हित दीर्घ	flags;

	rc = mptscsih_ioc_reset(ioc,reset_phase);
	अगर ((ioc->bus_type != FC) || (!rc))
		वापस rc;


	dपंचांगprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT
		": IOC %s_reset routed to FC host driver!\n",ioc->name,
		reset_phase==MPT_IOC_SETUP_RESET ? "setup" : (
		reset_phase==MPT_IOC_PRE_RESET ? "pre" : "post")));

	अगर (reset_phase == MPT_IOC_SETUP_RESET) अणु
		spin_lock_irqsave(&ioc->fc_rescan_work_lock, flags);
		अगर (ioc->fc_rescan_work_q) अणु
			queue_work(ioc->fc_rescan_work_q,
				   &ioc->fc_setup_reset_work);
		पूर्ण
		spin_unlock_irqrestore(&ioc->fc_rescan_work_lock, flags);
	पूर्ण

	अन्यथा अगर (reset_phase == MPT_IOC_PRE_RESET) अणु
	पूर्ण

	अन्यथा अणु	/* MPT_IOC_POST_RESET */
		mptfc_SetFcPortPage1_शेषs(ioc);
		spin_lock_irqsave(&ioc->fc_rescan_work_lock, flags);
		अगर (ioc->fc_rescan_work_q) अणु
			queue_work(ioc->fc_rescan_work_q,
				   &ioc->fc_rescan_work);
		पूर्ण
		spin_unlock_irqrestore(&ioc->fc_rescan_work_lock, flags);
	पूर्ण
	वापस 1;
पूर्ण

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/**
 *	mptfc_init - Register MPT adapter(s) as SCSI host(s) with SCSI mid-layer.
 *
 *	Returns 0 क्रम success, non-zero क्रम failure.
 */
अटल पूर्णांक __init
mptfc_init(व्योम)
अणु
	पूर्णांक error;

	show_mpपंचांगod_ver(my_NAME, my_VERSION);

	/* sanity check module parameters */
	अगर (mptfc_dev_loss_पंचांगo <= 0)
		mptfc_dev_loss_पंचांगo = MPTFC_DEV_LOSS_TMO;

	mptfc_transport_ढाँचा =
		fc_attach_transport(&mptfc_transport_functions);

	अगर (!mptfc_transport_ढाँचा)
		वापस -ENODEV;

	mptfcDoneCtx = mpt_रेजिस्टर(mptscsih_io_करोne, MPTFC_DRIVER,
	    "mptscsih_scandv_complete");
	mptfcTaskCtx = mpt_रेजिस्टर(mptscsih_taskmgmt_complete, MPTFC_DRIVER,
	    "mptscsih_scandv_complete");
	mptfcInternalCtx = mpt_रेजिस्टर(mptscsih_scandv_complete, MPTFC_DRIVER,
	    "mptscsih_scandv_complete");

	mpt_event_रेजिस्टर(mptfcDoneCtx, mptfc_event_process);
	mpt_reset_रेजिस्टर(mptfcDoneCtx, mptfc_ioc_reset);

	error = pci_रेजिस्टर_driver(&mptfc_driver);
	अगर (error)
		fc_release_transport(mptfc_transport_ढाँचा);

	वापस error;
पूर्ण

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/**
 *	mptfc_हटाओ - Remove fc infraकाष्ठाure क्रम devices
 *	@pdev: Poपूर्णांकer to pci_dev काष्ठाure
 *
 */
अटल व्योम mptfc_हटाओ(काष्ठा pci_dev *pdev)
अणु
	MPT_ADAPTER		*ioc = pci_get_drvdata(pdev);
	काष्ठा mptfc_rport_info	*p, *n;
	काष्ठा workqueue_काष्ठा *work_q;
	अचिन्हित दीर्घ		flags;
	पूर्णांक			ii;

	/* destroy workqueue */
	अगर ((work_q=ioc->fc_rescan_work_q)) अणु
		spin_lock_irqsave(&ioc->fc_rescan_work_lock, flags);
		ioc->fc_rescan_work_q = शून्य;
		spin_unlock_irqrestore(&ioc->fc_rescan_work_lock, flags);
		destroy_workqueue(work_q);
	पूर्ण

	fc_हटाओ_host(ioc->sh);

	list_क्रम_each_entry_safe(p, n, &ioc->fc_rports, list) अणु
		list_del(&p->list);
		kमुक्त(p);
	पूर्ण

	क्रम (ii=0; ii<ioc->facts.NumberOfPorts; ii++) अणु
		अगर (ioc->fc_data.fc_port_page1[ii].data) अणु
			pci_मुक्त_consistent(ioc->pcidev,
				ioc->fc_data.fc_port_page1[ii].pg_sz,
				(u8 *) ioc->fc_data.fc_port_page1[ii].data,
				ioc->fc_data.fc_port_page1[ii].dma);
			ioc->fc_data.fc_port_page1[ii].data = शून्य;
		पूर्ण
	पूर्ण

	scsi_हटाओ_host(ioc->sh);

	mptscsih_हटाओ(pdev);
पूर्ण

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/**
 *	mptfc_निकास - Unरेजिस्टरs MPT adapter(s)
 *
 */
अटल व्योम __निकास
mptfc_निकास(व्योम)
अणु
	pci_unरेजिस्टर_driver(&mptfc_driver);
	fc_release_transport(mptfc_transport_ढाँचा);

	mpt_reset_deरेजिस्टर(mptfcDoneCtx);
	mpt_event_deरेजिस्टर(mptfcDoneCtx);

	mpt_deरेजिस्टर(mptfcInternalCtx);
	mpt_deरेजिस्टर(mptfcTaskCtx);
	mpt_deरेजिस्टर(mptfcDoneCtx);
पूर्ण

module_init(mptfc_init);
module_निकास(mptfc_निकास);
