<शैली गुरु>
/*
 * SAS Transport Layer क्रम MPT (Message Passing Technology) based controllers
 *
 * This code is based on drivers/scsi/mpt3sas/mpt3sas_transport.c
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
#समावेश <linux/sched.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/delay.h>
#समावेश <linux/pci.h>

#समावेश <scsi/scsi.h>
#समावेश <scsi/scsi_cmnd.h>
#समावेश <scsi/scsi_device.h>
#समावेश <scsi/scsi_host.h>
#समावेश <scsi/scsi_transport_sas.h>
#समावेश <scsi/scsi_dbg.h>

#समावेश "mpt3sas_base.h"

/**
 * _transport_get_port_id_by_sas_phy - get zone's port id that Phy beदीर्घ to
 * @phy: sas_phy object
 *
 * Return Port number
 */
अटल अंतरभूत u8
_transport_get_port_id_by_sas_phy(काष्ठा sas_phy *phy)
अणु
	u8 port_id = 0xFF;
	काष्ठा hba_port *port = phy->hostdata;

	अगर (port)
		port_id = port->port_id;

	वापस port_id;
पूर्ण

/**
 * _transport_sas_node_find_by_sas_address - sas node search
 * @ioc: per adapter object
 * @sas_address: sas address of expander or sas host
 * @port: hba port entry
 * Context: Calling function should acquire ioc->sas_node_lock.
 *
 * Search क्रम either hba phys or expander device based on handle, then वापसs
 * the sas_node object.
 */
अटल काष्ठा _sas_node *
_transport_sas_node_find_by_sas_address(काष्ठा MPT3SAS_ADAPTER *ioc,
	u64 sas_address, काष्ठा hba_port *port)
अणु
	अगर (ioc->sas_hba.sas_address == sas_address)
		वापस &ioc->sas_hba;
	अन्यथा
		वापस mpt3sas_scsih_expander_find_by_sas_address(ioc,
		    sas_address, port);
पूर्ण

/**
 * _transport_get_port_id_by_rphy - Get Port number from rphy object
 * @ioc: per adapter object
 * @rphy: sas_rphy object
 *
 * Returns Port number.
 */
अटल u8
_transport_get_port_id_by_rphy(काष्ठा MPT3SAS_ADAPTER *ioc,
	काष्ठा sas_rphy *rphy)
अणु
	काष्ठा _sas_node *sas_expander;
	काष्ठा _sas_device *sas_device;
	अचिन्हित दीर्घ flags;
	u8 port_id = 0xFF;

	अगर (!rphy)
		वापस port_id;

	अगर (rphy->identअगरy.device_type == SAS_EDGE_EXPANDER_DEVICE ||
	    rphy->identअगरy.device_type == SAS_FANOUT_EXPANDER_DEVICE) अणु
		spin_lock_irqsave(&ioc->sas_node_lock, flags);
		list_क्रम_each_entry(sas_expander,
		    &ioc->sas_expander_list, list) अणु
			अगर (sas_expander->rphy == rphy) अणु
				port_id = sas_expander->port->port_id;
				अवरोध;
			पूर्ण
		पूर्ण
		spin_unlock_irqrestore(&ioc->sas_node_lock, flags);
	पूर्ण अन्यथा अगर (rphy->identअगरy.device_type == SAS_END_DEVICE) अणु
		spin_lock_irqsave(&ioc->sas_device_lock, flags);
		sas_device = __mpt3sas_get_sdev_by_rphy(ioc, rphy);
		अगर (sas_device) अणु
			port_id = sas_device->port->port_id;
			sas_device_put(sas_device);
		पूर्ण
		spin_unlock_irqrestore(&ioc->sas_device_lock, flags);
	पूर्ण

	वापस port_id;
पूर्ण

/**
 * _transport_convert_phy_link_rate -
 * @link_rate: link rate वापसed from mpt firmware
 *
 * Convert link_rate from mpi fusion पूर्णांकo sas_transport क्रमm.
 */
अटल क्रमागत sas_linkrate
_transport_convert_phy_link_rate(u8 link_rate)
अणु
	क्रमागत sas_linkrate rc;

	चयन (link_rate) अणु
	हाल MPI2_SAS_NEG_LINK_RATE_1_5:
		rc = SAS_LINK_RATE_1_5_GBPS;
		अवरोध;
	हाल MPI2_SAS_NEG_LINK_RATE_3_0:
		rc = SAS_LINK_RATE_3_0_GBPS;
		अवरोध;
	हाल MPI2_SAS_NEG_LINK_RATE_6_0:
		rc = SAS_LINK_RATE_6_0_GBPS;
		अवरोध;
	हाल MPI25_SAS_NEG_LINK_RATE_12_0:
		rc = SAS_LINK_RATE_12_0_GBPS;
		अवरोध;
	हाल MPI2_SAS_NEG_LINK_RATE_PHY_DISABLED:
		rc = SAS_PHY_DISABLED;
		अवरोध;
	हाल MPI2_SAS_NEG_LINK_RATE_NEGOTIATION_FAILED:
		rc = SAS_LINK_RATE_FAILED;
		अवरोध;
	हाल MPI2_SAS_NEG_LINK_RATE_PORT_SELECTOR:
		rc = SAS_SATA_PORT_SELECTOR;
		अवरोध;
	हाल MPI2_SAS_NEG_LINK_RATE_SMP_RESET_IN_PROGRESS:
		rc = SAS_PHY_RESET_IN_PROGRESS;
		अवरोध;

	शेष:
	हाल MPI2_SAS_NEG_LINK_RATE_SATA_OOB_COMPLETE:
	हाल MPI2_SAS_NEG_LINK_RATE_UNKNOWN_LINK_RATE:
		rc = SAS_LINK_RATE_UNKNOWN;
		अवरोध;
	पूर्ण
	वापस rc;
पूर्ण

/**
 * _transport_set_identअगरy - set identअगरy क्रम phys and end devices
 * @ioc: per adapter object
 * @handle: device handle
 * @identअगरy: sas identअगरy info
 *
 * Populates sas identअगरy info.
 *
 * Return: 0 क्रम success, non-zero क्रम failure.
 */
अटल पूर्णांक
_transport_set_identअगरy(काष्ठा MPT3SAS_ADAPTER *ioc, u16 handle,
	काष्ठा sas_identअगरy *identअगरy)
अणु
	Mpi2SasDevicePage0_t sas_device_pg0;
	Mpi2ConfigReply_t mpi_reply;
	u32 device_info;
	u32 ioc_status;

	अगर (ioc->shost_recovery || ioc->pci_error_recovery) अणु
		ioc_info(ioc, "%s: host reset in progress!\n", __func__);
		वापस -EFAULT;
	पूर्ण

	अगर ((mpt3sas_config_get_sas_device_pg0(ioc, &mpi_reply, &sas_device_pg0,
	    MPI2_SAS_DEVICE_PGAD_FORM_HANDLE, handle))) अणु
		ioc_err(ioc, "failure at %s:%d/%s()!\n",
			__खाता__, __LINE__, __func__);
		वापस -ENXIO;
	पूर्ण

	ioc_status = le16_to_cpu(mpi_reply.IOCStatus) &
	    MPI2_IOCSTATUS_MASK;
	अगर (ioc_status != MPI2_IOCSTATUS_SUCCESS) अणु
		ioc_err(ioc, "handle(0x%04x), ioc_status(0x%04x) failure at %s:%d/%s()!\n",
			handle, ioc_status, __खाता__, __LINE__, __func__);
		वापस -EIO;
	पूर्ण

	स_रखो(identअगरy, 0, माप(काष्ठा sas_identअगरy));
	device_info = le32_to_cpu(sas_device_pg0.DeviceInfo);

	/* sas_address */
	identअगरy->sas_address = le64_to_cpu(sas_device_pg0.SASAddress);

	/* phy number of the parent device this device is linked to */
	identअगरy->phy_identअगरier = sas_device_pg0.PhyNum;

	/* device_type */
	चयन (device_info & MPI2_SAS_DEVICE_INFO_MASK_DEVICE_TYPE) अणु
	हाल MPI2_SAS_DEVICE_INFO_NO_DEVICE:
		identअगरy->device_type = SAS_PHY_UNUSED;
		अवरोध;
	हाल MPI2_SAS_DEVICE_INFO_END_DEVICE:
		identअगरy->device_type = SAS_END_DEVICE;
		अवरोध;
	हाल MPI2_SAS_DEVICE_INFO_EDGE_EXPANDER:
		identअगरy->device_type = SAS_EDGE_EXPANDER_DEVICE;
		अवरोध;
	हाल MPI2_SAS_DEVICE_INFO_FANOUT_EXPANDER:
		identअगरy->device_type = SAS_FANOUT_EXPANDER_DEVICE;
		अवरोध;
	पूर्ण

	/* initiator_port_protocols */
	अगर (device_info & MPI2_SAS_DEVICE_INFO_SSP_INITIATOR)
		identअगरy->initiator_port_protocols |= SAS_PROTOCOL_SSP;
	अगर (device_info & MPI2_SAS_DEVICE_INFO_STP_INITIATOR)
		identअगरy->initiator_port_protocols |= SAS_PROTOCOL_STP;
	अगर (device_info & MPI2_SAS_DEVICE_INFO_SMP_INITIATOR)
		identअगरy->initiator_port_protocols |= SAS_PROTOCOL_SMP;
	अगर (device_info & MPI2_SAS_DEVICE_INFO_SATA_HOST)
		identअगरy->initiator_port_protocols |= SAS_PROTOCOL_SATA;

	/* target_port_protocols */
	अगर (device_info & MPI2_SAS_DEVICE_INFO_SSP_TARGET)
		identअगरy->target_port_protocols |= SAS_PROTOCOL_SSP;
	अगर (device_info & MPI2_SAS_DEVICE_INFO_STP_TARGET)
		identअगरy->target_port_protocols |= SAS_PROTOCOL_STP;
	अगर (device_info & MPI2_SAS_DEVICE_INFO_SMP_TARGET)
		identअगरy->target_port_protocols |= SAS_PROTOCOL_SMP;
	अगर (device_info & MPI2_SAS_DEVICE_INFO_SATA_DEVICE)
		identअगरy->target_port_protocols |= SAS_PROTOCOL_SATA;

	वापस 0;
पूर्ण

/**
 * mpt3sas_transport_करोne -  पूर्णांकernal transport layer callback handler.
 * @ioc: per adapter object
 * @smid: प्रणाली request message index
 * @msix_index: MSIX table index supplied by the OS
 * @reply: reply message frame(lower 32bit addr)
 *
 * Callback handler when sending पूर्णांकernal generated transport cmds.
 * The callback index passed is `ioc->transport_cb_idx`
 *
 * Return: 1 meaning mf should be मुक्तd from _base_पूर्णांकerrupt
 *         0 means the mf is मुक्तd from this function.
 */
u8
mpt3sas_transport_करोne(काष्ठा MPT3SAS_ADAPTER *ioc, u16 smid, u8 msix_index,
	u32 reply)
अणु
	MPI2DefaultReply_t *mpi_reply;

	mpi_reply =  mpt3sas_base_get_reply_virt_addr(ioc, reply);
	अगर (ioc->transport_cmds.status == MPT3_CMD_NOT_USED)
		वापस 1;
	अगर (ioc->transport_cmds.smid != smid)
		वापस 1;
	ioc->transport_cmds.status |= MPT3_CMD_COMPLETE;
	अगर (mpi_reply) अणु
		स_नकल(ioc->transport_cmds.reply, mpi_reply,
		    mpi_reply->MsgLength*4);
		ioc->transport_cmds.status |= MPT3_CMD_REPLY_VALID;
	पूर्ण
	ioc->transport_cmds.status &= ~MPT3_CMD_PENDING;
	complete(&ioc->transport_cmds.करोne);
	वापस 1;
पूर्ण

/* report manufacture request काष्ठाure */
काष्ठा rep_manu_request अणु
	u8 smp_frame_type;
	u8 function;
	u8 reserved;
	u8 request_length;
पूर्ण;

/* report manufacture reply काष्ठाure */
काष्ठा rep_manu_reply अणु
	u8 smp_frame_type; /* 0x41 */
	u8 function; /* 0x01 */
	u8 function_result;
	u8 response_length;
	u16 expander_change_count;
	u8 reserved0[2];
	u8 sas_क्रमmat;
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
 * _transport_expander_report_manufacture - obtain SMP report_manufacture
 * @ioc: per adapter object
 * @sas_address: expander sas address
 * @edev: the sas_expander_device object
 * @port_id: Port ID number
 *
 * Fills in the sas_expander_device object when SMP port is created.
 *
 * Return: 0 क्रम success, non-zero क्रम failure.
 */
अटल पूर्णांक
_transport_expander_report_manufacture(काष्ठा MPT3SAS_ADAPTER *ioc,
	u64 sas_address, काष्ठा sas_expander_device *edev, u8 port_id)
अणु
	Mpi2SmpPassthroughRequest_t *mpi_request;
	Mpi2SmpPassthroughReply_t *mpi_reply;
	काष्ठा rep_manu_reply *manufacture_reply;
	काष्ठा rep_manu_request *manufacture_request;
	पूर्णांक rc;
	u16 smid;
	व्योम *psge;
	u8 issue_reset = 0;
	व्योम *data_out = शून्य;
	dma_addr_t data_out_dma;
	dma_addr_t data_in_dma;
	माप_प्रकार data_in_sz;
	माप_प्रकार data_out_sz;

	अगर (ioc->shost_recovery || ioc->pci_error_recovery) अणु
		ioc_info(ioc, "%s: host reset in progress!\n", __func__);
		वापस -EFAULT;
	पूर्ण

	mutex_lock(&ioc->transport_cmds.mutex);

	अगर (ioc->transport_cmds.status != MPT3_CMD_NOT_USED) अणु
		ioc_err(ioc, "%s: transport_cmds in use\n", __func__);
		rc = -EAGAIN;
		जाओ out;
	पूर्ण
	ioc->transport_cmds.status = MPT3_CMD_PENDING;

	rc = mpt3sas_रुको_क्रम_ioc(ioc, IOC_OPERATIONAL_WAIT_COUNT);
	अगर (rc)
		जाओ out;

	smid = mpt3sas_base_get_smid(ioc, ioc->transport_cb_idx);
	अगर (!smid) अणु
		ioc_err(ioc, "%s: failed obtaining a smid\n", __func__);
		rc = -EAGAIN;
		जाओ out;
	पूर्ण

	rc = 0;
	mpi_request = mpt3sas_base_get_msg_frame(ioc, smid);
	ioc->transport_cmds.smid = smid;

	data_out_sz = माप(काष्ठा rep_manu_request);
	data_in_sz = माप(काष्ठा rep_manu_reply);
	data_out = dma_alloc_coherent(&ioc->pdev->dev, data_out_sz + data_in_sz,
			&data_out_dma, GFP_KERNEL);
	अगर (!data_out) अणु
		pr_err("failure at %s:%d/%s()!\n", __खाता__,
		    __LINE__, __func__);
		rc = -ENOMEM;
		mpt3sas_base_मुक्त_smid(ioc, smid);
		जाओ out;
	पूर्ण

	data_in_dma = data_out_dma + माप(काष्ठा rep_manu_request);

	manufacture_request = data_out;
	manufacture_request->smp_frame_type = 0x40;
	manufacture_request->function = 1;
	manufacture_request->reserved = 0;
	manufacture_request->request_length = 0;

	स_रखो(mpi_request, 0, माप(Mpi2SmpPassthroughRequest_t));
	mpi_request->Function = MPI2_FUNCTION_SMP_PASSTHROUGH;
	mpi_request->PhysicalPort = port_id;
	mpi_request->SASAddress = cpu_to_le64(sas_address);
	mpi_request->RequestDataLength = cpu_to_le16(data_out_sz);
	psge = &mpi_request->SGL;

	ioc->build_sg(ioc, psge, data_out_dma, data_out_sz, data_in_dma,
	    data_in_sz);

	dtransportprपूर्णांकk(ioc,
			 ioc_info(ioc, "report_manufacture - send to sas_addr(0x%016llx)\n",
				  (u64)sas_address));
	init_completion(&ioc->transport_cmds.करोne);
	ioc->put_smid_शेष(ioc, smid);
	रुको_क्रम_completion_समयout(&ioc->transport_cmds.करोne, 10*HZ);

	अगर (!(ioc->transport_cmds.status & MPT3_CMD_COMPLETE)) अणु
		ioc_err(ioc, "%s: timeout\n", __func__);
		_debug_dump_mf(mpi_request,
		    माप(Mpi2SmpPassthroughRequest_t)/4);
		अगर (!(ioc->transport_cmds.status & MPT3_CMD_RESET))
			issue_reset = 1;
		जाओ issue_host_reset;
	पूर्ण

	dtransportprपूर्णांकk(ioc, ioc_info(ioc, "report_manufacture - complete\n"));

	अगर (ioc->transport_cmds.status & MPT3_CMD_REPLY_VALID) अणु
		u8 *पंचांगp;

		mpi_reply = ioc->transport_cmds.reply;

		dtransportprपूर्णांकk(ioc,
				 ioc_info(ioc, "report_manufacture - reply data transfer size(%d)\n",
					  le16_to_cpu(mpi_reply->ResponseDataLength)));

		अगर (le16_to_cpu(mpi_reply->ResponseDataLength) !=
		    माप(काष्ठा rep_manu_reply))
			जाओ out;

		manufacture_reply = data_out + माप(काष्ठा rep_manu_request);
		म_नकलन(edev->venकरोr_id, manufacture_reply->venकरोr_id,
		     SAS_EXPANDER_VENDOR_ID_LEN);
		म_नकलन(edev->product_id, manufacture_reply->product_id,
		     SAS_EXPANDER_PRODUCT_ID_LEN);
		म_नकलन(edev->product_rev, manufacture_reply->product_rev,
		     SAS_EXPANDER_PRODUCT_REV_LEN);
		edev->level = manufacture_reply->sas_क्रमmat & 1;
		अगर (edev->level) अणु
			म_नकलन(edev->component_venकरोr_id,
			    manufacture_reply->component_venकरोr_id,
			     SAS_EXPANDER_COMPONENT_VENDOR_ID_LEN);
			पंचांगp = (u8 *)&manufacture_reply->component_id;
			edev->component_id = पंचांगp[0] << 8 | पंचांगp[1];
			edev->component_revision_id =
			    manufacture_reply->component_revision_id;
		पूर्ण
	पूर्ण अन्यथा
		dtransportprपूर्णांकk(ioc,
				 ioc_info(ioc, "report_manufacture - no reply\n"));

 issue_host_reset:
	अगर (issue_reset)
		mpt3sas_base_hard_reset_handler(ioc, FORCE_BIG_HAMMER);
 out:
	ioc->transport_cmds.status = MPT3_CMD_NOT_USED;
	अगर (data_out)
		dma_मुक्त_coherent(&ioc->pdev->dev, data_out_sz + data_in_sz,
		    data_out, data_out_dma);

	mutex_unlock(&ioc->transport_cmds.mutex);
	वापस rc;
पूर्ण


/**
 * _transport_delete_port - helper function to removing a port
 * @ioc: per adapter object
 * @mpt3sas_port: mpt3sas per port object
 */
अटल व्योम
_transport_delete_port(काष्ठा MPT3SAS_ADAPTER *ioc,
	काष्ठा _sas_port *mpt3sas_port)
अणु
	u64 sas_address = mpt3sas_port->remote_identअगरy.sas_address;
	काष्ठा hba_port *port = mpt3sas_port->hba_port;
	क्रमागत sas_device_type device_type =
	    mpt3sas_port->remote_identअगरy.device_type;

	dev_prपूर्णांकk(KERN_INFO, &mpt3sas_port->port->dev,
	    "remove: sas_addr(0x%016llx)\n",
	    (अचिन्हित दीर्घ दीर्घ) sas_address);

	ioc->logging_level |= MPT_DEBUG_TRANSPORT;
	अगर (device_type == SAS_END_DEVICE)
		mpt3sas_device_हटाओ_by_sas_address(ioc,
		    sas_address, port);
	अन्यथा अगर (device_type == SAS_EDGE_EXPANDER_DEVICE ||
	    device_type == SAS_FANOUT_EXPANDER_DEVICE)
		mpt3sas_expander_हटाओ(ioc, sas_address, port);
	ioc->logging_level &= ~MPT_DEBUG_TRANSPORT;
पूर्ण

/**
 * _transport_delete_phy - helper function to removing single phy from port
 * @ioc: per adapter object
 * @mpt3sas_port: mpt3sas per port object
 * @mpt3sas_phy: mpt3sas per phy object
 */
अटल व्योम
_transport_delete_phy(काष्ठा MPT3SAS_ADAPTER *ioc,
	काष्ठा _sas_port *mpt3sas_port, काष्ठा _sas_phy *mpt3sas_phy)
अणु
	u64 sas_address = mpt3sas_port->remote_identअगरy.sas_address;

	dev_prपूर्णांकk(KERN_INFO, &mpt3sas_phy->phy->dev,
	    "remove: sas_addr(0x%016llx), phy(%d)\n",
	    (अचिन्हित दीर्घ दीर्घ) sas_address, mpt3sas_phy->phy_id);

	list_del(&mpt3sas_phy->port_siblings);
	mpt3sas_port->num_phys--;
	sas_port_delete_phy(mpt3sas_port->port, mpt3sas_phy->phy);
	mpt3sas_phy->phy_beदीर्घs_to_port = 0;
पूर्ण

/**
 * _transport_add_phy - helper function to adding single phy to port
 * @ioc: per adapter object
 * @mpt3sas_port: mpt3sas per port object
 * @mpt3sas_phy: mpt3sas per phy object
 */
अटल व्योम
_transport_add_phy(काष्ठा MPT3SAS_ADAPTER *ioc, काष्ठा _sas_port *mpt3sas_port,
	काष्ठा _sas_phy *mpt3sas_phy)
अणु
	u64 sas_address = mpt3sas_port->remote_identअगरy.sas_address;

	dev_prपूर्णांकk(KERN_INFO, &mpt3sas_phy->phy->dev,
	    "add: sas_addr(0x%016llx), phy(%d)\n", (अचिन्हित दीर्घ दीर्घ)
	    sas_address, mpt3sas_phy->phy_id);

	list_add_tail(&mpt3sas_phy->port_siblings, &mpt3sas_port->phy_list);
	mpt3sas_port->num_phys++;
	sas_port_add_phy(mpt3sas_port->port, mpt3sas_phy->phy);
	mpt3sas_phy->phy_beदीर्घs_to_port = 1;
पूर्ण

/**
 * mpt3sas_transport_add_phy_to_an_existing_port - adding new phy to existing port
 * @ioc: per adapter object
 * @sas_node: sas node object (either expander or sas host)
 * @mpt3sas_phy: mpt3sas per phy object
 * @sas_address: sas address of device/expander were phy needs to be added to
 * @port: hba port entry
 */
व्योम
mpt3sas_transport_add_phy_to_an_existing_port(काष्ठा MPT3SAS_ADAPTER *ioc,
	काष्ठा _sas_node *sas_node, काष्ठा _sas_phy *mpt3sas_phy,
	u64 sas_address, काष्ठा hba_port *port)
अणु
	काष्ठा _sas_port *mpt3sas_port;
	काष्ठा _sas_phy *phy_srch;

	अगर (mpt3sas_phy->phy_beदीर्घs_to_port == 1)
		वापस;

	अगर (!port)
		वापस;

	list_क्रम_each_entry(mpt3sas_port, &sas_node->sas_port_list,
	    port_list) अणु
		अगर (mpt3sas_port->remote_identअगरy.sas_address !=
		    sas_address)
			जारी;
		अगर (mpt3sas_port->hba_port != port)
			जारी;
		list_क्रम_each_entry(phy_srch, &mpt3sas_port->phy_list,
		    port_siblings) अणु
			अगर (phy_srch == mpt3sas_phy)
				वापस;
		पूर्ण
		_transport_add_phy(ioc, mpt3sas_port, mpt3sas_phy);
		वापस;
	पूर्ण

पूर्ण

/**
 * mpt3sas_transport_del_phy_from_an_existing_port - delete phy from existing port
 * @ioc: per adapter object
 * @sas_node: sas node object (either expander or sas host)
 * @mpt3sas_phy: mpt3sas per phy object
 */
व्योम
mpt3sas_transport_del_phy_from_an_existing_port(काष्ठा MPT3SAS_ADAPTER *ioc,
	काष्ठा _sas_node *sas_node, काष्ठा _sas_phy *mpt3sas_phy)
अणु
	काष्ठा _sas_port *mpt3sas_port, *next;
	काष्ठा _sas_phy *phy_srch;

	अगर (mpt3sas_phy->phy_beदीर्घs_to_port == 0)
		वापस;

	list_क्रम_each_entry_safe(mpt3sas_port, next, &sas_node->sas_port_list,
	    port_list) अणु
		list_क्रम_each_entry(phy_srch, &mpt3sas_port->phy_list,
		    port_siblings) अणु
			अगर (phy_srch != mpt3sas_phy)
				जारी;

			/*
			 * Don't delete port during host reset,
			 * just delete phy.
			 */
			अगर (mpt3sas_port->num_phys == 1 && !ioc->shost_recovery)
				_transport_delete_port(ioc, mpt3sas_port);
			अन्यथा
				_transport_delete_phy(ioc, mpt3sas_port,
				    mpt3sas_phy);
			वापस;
		पूर्ण
	पूर्ण
पूर्ण

/**
 * _transport_sanity_check - sanity check when adding a new port
 * @ioc: per adapter object
 * @sas_node: sas node object (either expander or sas host)
 * @sas_address: sas address of device being added
 * @port: hba port entry
 *
 * See the explanation above from _transport_delete_duplicate_port
 */
अटल व्योम
_transport_sanity_check(काष्ठा MPT3SAS_ADAPTER *ioc, काष्ठा _sas_node *sas_node,
	u64 sas_address, काष्ठा hba_port *port)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < sas_node->num_phys; i++) अणु
		अगर (sas_node->phy[i].remote_identअगरy.sas_address != sas_address)
			जारी;
		अगर (sas_node->phy[i].port != port)
			जारी;
		अगर (sas_node->phy[i].phy_beदीर्घs_to_port == 1)
			mpt3sas_transport_del_phy_from_an_existing_port(ioc,
			    sas_node, &sas_node->phy[i]);
	पूर्ण
पूर्ण

/**
 * mpt3sas_transport_port_add - insert port to the list
 * @ioc: per adapter object
 * @handle: handle of attached device
 * @sas_address: sas address of parent expander or sas host
 * @hba_port: hba port entry
 * Context: This function will acquire ioc->sas_node_lock.
 *
 * Adding new port object to the sas_node->sas_port_list.
 *
 * Return: mpt3sas_port.
 */
काष्ठा _sas_port *
mpt3sas_transport_port_add(काष्ठा MPT3SAS_ADAPTER *ioc, u16 handle,
	u64 sas_address, काष्ठा hba_port *hba_port)
अणु
	काष्ठा _sas_phy *mpt3sas_phy, *next;
	काष्ठा _sas_port *mpt3sas_port;
	अचिन्हित दीर्घ flags;
	काष्ठा _sas_node *sas_node;
	काष्ठा sas_rphy *rphy;
	काष्ठा _sas_device *sas_device = शून्य;
	पूर्णांक i;
	काष्ठा sas_port *port;
	काष्ठा भव_phy *vphy = शून्य;

	अगर (!hba_port) अणु
		ioc_err(ioc, "failure at %s:%d/%s()!\n",
		    __खाता__, __LINE__, __func__);
		वापस शून्य;
	पूर्ण

	mpt3sas_port = kzalloc(माप(काष्ठा _sas_port),
	    GFP_KERNEL);
	अगर (!mpt3sas_port) अणु
		ioc_err(ioc, "failure at %s:%d/%s()!\n",
			__खाता__, __LINE__, __func__);
		वापस शून्य;
	पूर्ण

	INIT_LIST_HEAD(&mpt3sas_port->port_list);
	INIT_LIST_HEAD(&mpt3sas_port->phy_list);
	spin_lock_irqsave(&ioc->sas_node_lock, flags);
	sas_node = _transport_sas_node_find_by_sas_address(ioc,
	    sas_address, hba_port);
	spin_unlock_irqrestore(&ioc->sas_node_lock, flags);

	अगर (!sas_node) अणु
		ioc_err(ioc, "%s: Could not find parent sas_address(0x%016llx)!\n",
			__func__, (u64)sas_address);
		जाओ out_fail;
	पूर्ण

	अगर ((_transport_set_identअगरy(ioc, handle,
	    &mpt3sas_port->remote_identअगरy))) अणु
		ioc_err(ioc, "failure at %s:%d/%s()!\n",
			__खाता__, __LINE__, __func__);
		जाओ out_fail;
	पूर्ण

	अगर (mpt3sas_port->remote_identअगरy.device_type == SAS_PHY_UNUSED) अणु
		ioc_err(ioc, "failure at %s:%d/%s()!\n",
			__खाता__, __LINE__, __func__);
		जाओ out_fail;
	पूर्ण

	mpt3sas_port->hba_port = hba_port;
	_transport_sanity_check(ioc, sas_node,
	    mpt3sas_port->remote_identअगरy.sas_address, hba_port);

	क्रम (i = 0; i < sas_node->num_phys; i++) अणु
		अगर (sas_node->phy[i].remote_identअगरy.sas_address !=
		    mpt3sas_port->remote_identअगरy.sas_address)
			जारी;
		अगर (sas_node->phy[i].port != hba_port)
			जारी;
		list_add_tail(&sas_node->phy[i].port_siblings,
		    &mpt3sas_port->phy_list);
		mpt3sas_port->num_phys++;
		अगर (sas_node->handle <= ioc->sas_hba.num_phys) अणु
			अगर (!sas_node->phy[i].hba_vphy) अणु
				hba_port->phy_mask |= (1 << i);
				जारी;
			पूर्ण

			vphy = mpt3sas_get_vphy_by_phy(ioc, hba_port, i);
			अगर (!vphy) अणु
				ioc_err(ioc, "failure at %s:%d/%s()!\n",
				    __खाता__, __LINE__, __func__);
				जाओ out_fail;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (!mpt3sas_port->num_phys) अणु
		ioc_err(ioc, "failure at %s:%d/%s()!\n",
			__खाता__, __LINE__, __func__);
		जाओ out_fail;
	पूर्ण

	अगर (mpt3sas_port->remote_identअगरy.device_type == SAS_END_DEVICE) अणु
		sas_device = mpt3sas_get_sdev_by_addr(ioc,
		    mpt3sas_port->remote_identअगरy.sas_address,
		    mpt3sas_port->hba_port);
		अगर (!sas_device) अणु
			ioc_err(ioc, "failure at %s:%d/%s()!\n",
			    __खाता__, __LINE__, __func__);
			जाओ out_fail;
		पूर्ण
		sas_device->pend_sas_rphy_add = 1;
	पूर्ण

	अगर (!sas_node->parent_dev) अणु
		ioc_err(ioc, "failure at %s:%d/%s()!\n",
			__खाता__, __LINE__, __func__);
		जाओ out_fail;
	पूर्ण
	port = sas_port_alloc_num(sas_node->parent_dev);
	अगर ((sas_port_add(port))) अणु
		ioc_err(ioc, "failure at %s:%d/%s()!\n",
			__खाता__, __LINE__, __func__);
		जाओ out_fail;
	पूर्ण

	list_क्रम_each_entry(mpt3sas_phy, &mpt3sas_port->phy_list,
	    port_siblings) अणु
		अगर ((ioc->logging_level & MPT_DEBUG_TRANSPORT))
			dev_prपूर्णांकk(KERN_INFO, &port->dev,
				"add: handle(0x%04x), sas_addr(0x%016llx), phy(%d)\n",
				handle, (अचिन्हित दीर्घ दीर्घ)
			    mpt3sas_port->remote_identअगरy.sas_address,
			    mpt3sas_phy->phy_id);
		sas_port_add_phy(port, mpt3sas_phy->phy);
		mpt3sas_phy->phy_beदीर्घs_to_port = 1;
		mpt3sas_phy->port = hba_port;
	पूर्ण

	mpt3sas_port->port = port;
	अगर (mpt3sas_port->remote_identअगरy.device_type == SAS_END_DEVICE) अणु
		rphy = sas_end_device_alloc(port);
		sas_device->rphy = rphy;
		अगर (sas_node->handle <= ioc->sas_hba.num_phys) अणु
			अगर (!vphy)
				hba_port->sas_address =
				    sas_device->sas_address;
			अन्यथा
				vphy->sas_address =
				    sas_device->sas_address;
		पूर्ण
	पूर्ण अन्यथा अणु
		rphy = sas_expander_alloc(port,
		    mpt3sas_port->remote_identअगरy.device_type);
		अगर (sas_node->handle <= ioc->sas_hba.num_phys)
			hba_port->sas_address =
			    mpt3sas_port->remote_identअगरy.sas_address;
	पूर्ण

	rphy->identअगरy = mpt3sas_port->remote_identअगरy;

	अगर ((sas_rphy_add(rphy))) अणु
		ioc_err(ioc, "failure at %s:%d/%s()!\n",
			__खाता__, __LINE__, __func__);
	पूर्ण

	अगर (mpt3sas_port->remote_identअगरy.device_type == SAS_END_DEVICE) अणु
		sas_device->pend_sas_rphy_add = 0;
		sas_device_put(sas_device);
	पूर्ण

	dev_info(&rphy->dev,
	    "add: handle(0x%04x), sas_addr(0x%016llx)\n", handle,
	    (अचिन्हित दीर्घ दीर्घ)mpt3sas_port->remote_identअगरy.sas_address);

	mpt3sas_port->rphy = rphy;
	spin_lock_irqsave(&ioc->sas_node_lock, flags);
	list_add_tail(&mpt3sas_port->port_list, &sas_node->sas_port_list);
	spin_unlock_irqrestore(&ioc->sas_node_lock, flags);

	/* fill in report manufacture */
	अगर (mpt3sas_port->remote_identअगरy.device_type ==
	    MPI2_SAS_DEVICE_INFO_EDGE_EXPANDER ||
	    mpt3sas_port->remote_identअगरy.device_type ==
	    MPI2_SAS_DEVICE_INFO_FANOUT_EXPANDER)
		_transport_expander_report_manufacture(ioc,
		    mpt3sas_port->remote_identअगरy.sas_address,
		    rphy_to_expander_device(rphy), hba_port->port_id);
	वापस mpt3sas_port;

 out_fail:
	list_क्रम_each_entry_safe(mpt3sas_phy, next, &mpt3sas_port->phy_list,
	    port_siblings)
		list_del(&mpt3sas_phy->port_siblings);
	kमुक्त(mpt3sas_port);
	वापस शून्य;
पूर्ण

/**
 * mpt3sas_transport_port_हटाओ - हटाओ port from the list
 * @ioc: per adapter object
 * @sas_address: sas address of attached device
 * @sas_address_parent: sas address of parent expander or sas host
 * @port: hba port entry
 * Context: This function will acquire ioc->sas_node_lock.
 *
 * Removing object and मुक्तing associated memory from the
 * ioc->sas_port_list.
 */
व्योम
mpt3sas_transport_port_हटाओ(काष्ठा MPT3SAS_ADAPTER *ioc, u64 sas_address,
	u64 sas_address_parent, काष्ठा hba_port *port)
अणु
	पूर्णांक i;
	अचिन्हित दीर्घ flags;
	काष्ठा _sas_port *mpt3sas_port, *next;
	काष्ठा _sas_node *sas_node;
	u8 found = 0;
	काष्ठा _sas_phy *mpt3sas_phy, *next_phy;
	काष्ठा hba_port *hba_port_next, *hba_port = शून्य;
	काष्ठा भव_phy *vphy, *vphy_next = शून्य;

	अगर (!port)
		वापस;

	spin_lock_irqsave(&ioc->sas_node_lock, flags);
	sas_node = _transport_sas_node_find_by_sas_address(ioc,
	    sas_address_parent, port);
	अगर (!sas_node) अणु
		spin_unlock_irqrestore(&ioc->sas_node_lock, flags);
		वापस;
	पूर्ण
	list_क्रम_each_entry_safe(mpt3sas_port, next, &sas_node->sas_port_list,
	    port_list) अणु
		अगर (mpt3sas_port->remote_identअगरy.sas_address != sas_address)
			जारी;
		अगर (mpt3sas_port->hba_port != port)
			जारी;
		found = 1;
		list_del(&mpt3sas_port->port_list);
		जाओ out;
	पूर्ण
 out:
	अगर (!found) अणु
		spin_unlock_irqrestore(&ioc->sas_node_lock, flags);
		वापस;
	पूर्ण

	अगर (sas_node->handle <= ioc->sas_hba.num_phys &&
	    (ioc->multipath_on_hba)) अणु
		अगर (port->vphys_mask) अणु
			list_क्रम_each_entry_safe(vphy, vphy_next,
			    &port->vphys_list, list) अणु
				अगर (vphy->sas_address != sas_address)
					जारी;
				ioc_info(ioc,
				    "remove vphy entry: %p of port:%p,from %d port's vphys list\n",
				    vphy, port, port->port_id);
				port->vphys_mask &= ~vphy->phy_mask;
				list_del(&vphy->list);
				kमुक्त(vphy);
			पूर्ण
		पूर्ण

		list_क्रम_each_entry_safe(hba_port, hba_port_next,
		    &ioc->port_table_list, list) अणु
			अगर (hba_port != port)
				जारी;
			/*
			 * Delete hba_port object अगर
			 *  - hba_port object's sas address matches with current
			 *    हटाओd device's sas address and no vphy's
			 *    associated with it.
			 *  - Current हटाओd device is a vSES device and
			 *    none of the other direct attached device have
			 *    this vSES device's port number (hence hba_port
			 *    object sas_address field will be zero).
			 */
			अगर ((hba_port->sas_address == sas_address ||
			    !hba_port->sas_address) && !hba_port->vphys_mask) अणु
				ioc_info(ioc,
				    "remove hba_port entry: %p port: %d from hba_port list\n",
				    hba_port, hba_port->port_id);
				list_del(&hba_port->list);
				kमुक्त(hba_port);
			पूर्ण अन्यथा अगर (hba_port->sas_address == sas_address &&
			    hba_port->vphys_mask) अणु
				/*
				 * Current हटाओd device is a non vSES device
				 * and a vSES device has the same port number
				 * as of current device's port number. Hence
				 * only clear the sas_address filed, करोn't
				 * delete the hba_port object.
				 */
				ioc_info(ioc,
				    "clearing sas_address from hba_port entry: %p port: %d from hba_port list\n",
				    hba_port, hba_port->port_id);
				port->sas_address = 0;
			पूर्ण
			अवरोध;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < sas_node->num_phys; i++) अणु
		अगर (sas_node->phy[i].remote_identअगरy.sas_address == sas_address)
			स_रखो(&sas_node->phy[i].remote_identअगरy, 0 ,
			    माप(काष्ठा sas_identअगरy));
	पूर्ण

	spin_unlock_irqrestore(&ioc->sas_node_lock, flags);

	list_क्रम_each_entry_safe(mpt3sas_phy, next_phy,
	    &mpt3sas_port->phy_list, port_siblings) अणु
		अगर ((ioc->logging_level & MPT_DEBUG_TRANSPORT))
			dev_prपूर्णांकk(KERN_INFO, &mpt3sas_port->port->dev,
			    "remove: sas_addr(0x%016llx), phy(%d)\n",
			    (अचिन्हित दीर्घ दीर्घ)
			    mpt3sas_port->remote_identअगरy.sas_address,
			    mpt3sas_phy->phy_id);
		mpt3sas_phy->phy_beदीर्घs_to_port = 0;
		अगर (!ioc->हटाओ_host)
			sas_port_delete_phy(mpt3sas_port->port,
						mpt3sas_phy->phy);
		list_del(&mpt3sas_phy->port_siblings);
	पूर्ण
	अगर (!ioc->हटाओ_host)
		sas_port_delete(mpt3sas_port->port);
	ioc_info(ioc, "%s: removed: sas_addr(0x%016llx)\n",
	    __func__, (अचिन्हित दीर्घ दीर्घ)sas_address);
	kमुक्त(mpt3sas_port);
पूर्ण

/**
 * mpt3sas_transport_add_host_phy - report sas_host phy to transport
 * @ioc: per adapter object
 * @mpt3sas_phy: mpt3sas per phy object
 * @phy_pg0: sas phy page 0
 * @parent_dev: parent device class object
 *
 * Return: 0 क्रम success, non-zero क्रम failure.
 */
पूर्णांक
mpt3sas_transport_add_host_phy(काष्ठा MPT3SAS_ADAPTER *ioc, काष्ठा _sas_phy
	*mpt3sas_phy, Mpi2SasPhyPage0_t phy_pg0, काष्ठा device *parent_dev)
अणु
	काष्ठा sas_phy *phy;
	पूर्णांक phy_index = mpt3sas_phy->phy_id;


	INIT_LIST_HEAD(&mpt3sas_phy->port_siblings);
	phy = sas_phy_alloc(parent_dev, phy_index);
	अगर (!phy) अणु
		ioc_err(ioc, "failure at %s:%d/%s()!\n",
			__खाता__, __LINE__, __func__);
		वापस -1;
	पूर्ण
	अगर ((_transport_set_identअगरy(ioc, mpt3sas_phy->handle,
	    &mpt3sas_phy->identअगरy))) अणु
		ioc_err(ioc, "failure at %s:%d/%s()!\n",
			__खाता__, __LINE__, __func__);
		sas_phy_मुक्त(phy);
		वापस -1;
	पूर्ण
	phy->identअगरy = mpt3sas_phy->identअगरy;
	mpt3sas_phy->attached_handle = le16_to_cpu(phy_pg0.AttachedDevHandle);
	अगर (mpt3sas_phy->attached_handle)
		_transport_set_identअगरy(ioc, mpt3sas_phy->attached_handle,
		    &mpt3sas_phy->remote_identअगरy);
	phy->identअगरy.phy_identअगरier = mpt3sas_phy->phy_id;
	phy->negotiated_linkrate = _transport_convert_phy_link_rate(
	    phy_pg0.NegotiatedLinkRate & MPI2_SAS_NEG_LINK_RATE_MASK_PHYSICAL);
	phy->minimum_linkrate_hw = _transport_convert_phy_link_rate(
	    phy_pg0.HwLinkRate & MPI2_SAS_HWRATE_MIN_RATE_MASK);
	phy->maximum_linkrate_hw = _transport_convert_phy_link_rate(
	    phy_pg0.HwLinkRate >> 4);
	phy->minimum_linkrate = _transport_convert_phy_link_rate(
	    phy_pg0.ProgrammedLinkRate & MPI2_SAS_PRATE_MIN_RATE_MASK);
	phy->maximum_linkrate = _transport_convert_phy_link_rate(
	    phy_pg0.ProgrammedLinkRate >> 4);
	phy->hostdata = mpt3sas_phy->port;

	अगर ((sas_phy_add(phy))) अणु
		ioc_err(ioc, "failure at %s:%d/%s()!\n",
			__खाता__, __LINE__, __func__);
		sas_phy_मुक्त(phy);
		वापस -1;
	पूर्ण
	अगर ((ioc->logging_level & MPT_DEBUG_TRANSPORT))
		dev_prपूर्णांकk(KERN_INFO, &phy->dev,
		    "add: handle(0x%04x), sas_addr(0x%016llx)\n"
		    "\tattached_handle(0x%04x), sas_addr(0x%016llx)\n",
		    mpt3sas_phy->handle, (अचिन्हित दीर्घ दीर्घ)
		    mpt3sas_phy->identअगरy.sas_address,
		    mpt3sas_phy->attached_handle,
		    (अचिन्हित दीर्घ दीर्घ)
		    mpt3sas_phy->remote_identअगरy.sas_address);
	mpt3sas_phy->phy = phy;
	वापस 0;
पूर्ण


/**
 * mpt3sas_transport_add_expander_phy - report expander phy to transport
 * @ioc: per adapter object
 * @mpt3sas_phy: mpt3sas per phy object
 * @expander_pg1: expander page 1
 * @parent_dev: parent device class object
 *
 * Return: 0 क्रम success, non-zero क्रम failure.
 */
पूर्णांक
mpt3sas_transport_add_expander_phy(काष्ठा MPT3SAS_ADAPTER *ioc, काष्ठा _sas_phy
	*mpt3sas_phy, Mpi2ExpanderPage1_t expander_pg1,
	काष्ठा device *parent_dev)
अणु
	काष्ठा sas_phy *phy;
	पूर्णांक phy_index = mpt3sas_phy->phy_id;

	INIT_LIST_HEAD(&mpt3sas_phy->port_siblings);
	phy = sas_phy_alloc(parent_dev, phy_index);
	अगर (!phy) अणु
		ioc_err(ioc, "failure at %s:%d/%s()!\n",
			__खाता__, __LINE__, __func__);
		वापस -1;
	पूर्ण
	अगर ((_transport_set_identअगरy(ioc, mpt3sas_phy->handle,
	    &mpt3sas_phy->identअगरy))) अणु
		ioc_err(ioc, "failure at %s:%d/%s()!\n",
			__खाता__, __LINE__, __func__);
		sas_phy_मुक्त(phy);
		वापस -1;
	पूर्ण
	phy->identअगरy = mpt3sas_phy->identअगरy;
	mpt3sas_phy->attached_handle =
	    le16_to_cpu(expander_pg1.AttachedDevHandle);
	अगर (mpt3sas_phy->attached_handle)
		_transport_set_identअगरy(ioc, mpt3sas_phy->attached_handle,
		    &mpt3sas_phy->remote_identअगरy);
	phy->identअगरy.phy_identअगरier = mpt3sas_phy->phy_id;
	phy->negotiated_linkrate = _transport_convert_phy_link_rate(
	    expander_pg1.NegotiatedLinkRate &
	    MPI2_SAS_NEG_LINK_RATE_MASK_PHYSICAL);
	phy->minimum_linkrate_hw = _transport_convert_phy_link_rate(
	    expander_pg1.HwLinkRate & MPI2_SAS_HWRATE_MIN_RATE_MASK);
	phy->maximum_linkrate_hw = _transport_convert_phy_link_rate(
	    expander_pg1.HwLinkRate >> 4);
	phy->minimum_linkrate = _transport_convert_phy_link_rate(
	    expander_pg1.ProgrammedLinkRate & MPI2_SAS_PRATE_MIN_RATE_MASK);
	phy->maximum_linkrate = _transport_convert_phy_link_rate(
	    expander_pg1.ProgrammedLinkRate >> 4);
	phy->hostdata = mpt3sas_phy->port;

	अगर ((sas_phy_add(phy))) अणु
		ioc_err(ioc, "failure at %s:%d/%s()!\n",
			__खाता__, __LINE__, __func__);
		sas_phy_मुक्त(phy);
		वापस -1;
	पूर्ण
	अगर ((ioc->logging_level & MPT_DEBUG_TRANSPORT))
		dev_prपूर्णांकk(KERN_INFO, &phy->dev,
		    "add: handle(0x%04x), sas_addr(0x%016llx)\n"
		    "\tattached_handle(0x%04x), sas_addr(0x%016llx)\n",
		    mpt3sas_phy->handle, (अचिन्हित दीर्घ दीर्घ)
		    mpt3sas_phy->identअगरy.sas_address,
		    mpt3sas_phy->attached_handle,
		    (अचिन्हित दीर्घ दीर्घ)
		    mpt3sas_phy->remote_identअगरy.sas_address);
	mpt3sas_phy->phy = phy;
	वापस 0;
पूर्ण

/**
 * mpt3sas_transport_update_links - refreshing phy link changes
 * @ioc: per adapter object
 * @sas_address: sas address of parent expander or sas host
 * @handle: attached device handle
 * @phy_number: phy number
 * @link_rate: new link rate
 * @port: hba port entry
 *
 * Return nothing.
 */
व्योम
mpt3sas_transport_update_links(काष्ठा MPT3SAS_ADAPTER *ioc,
	u64 sas_address, u16 handle, u8 phy_number, u8 link_rate,
	काष्ठा hba_port *port)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा _sas_node *sas_node;
	काष्ठा _sas_phy *mpt3sas_phy;
	काष्ठा hba_port *hba_port = शून्य;

	अगर (ioc->shost_recovery || ioc->pci_error_recovery)
		वापस;

	spin_lock_irqsave(&ioc->sas_node_lock, flags);
	sas_node = _transport_sas_node_find_by_sas_address(ioc,
	    sas_address, port);
	अगर (!sas_node) अणु
		spin_unlock_irqrestore(&ioc->sas_node_lock, flags);
		वापस;
	पूर्ण

	mpt3sas_phy = &sas_node->phy[phy_number];
	mpt3sas_phy->attached_handle = handle;
	spin_unlock_irqrestore(&ioc->sas_node_lock, flags);
	अगर (handle && (link_rate >= MPI2_SAS_NEG_LINK_RATE_1_5)) अणु
		_transport_set_identअगरy(ioc, handle,
		    &mpt3sas_phy->remote_identअगरy);
		अगर ((sas_node->handle <= ioc->sas_hba.num_phys) &&
		    (ioc->multipath_on_hba)) अणु
			list_क्रम_each_entry(hba_port,
			    &ioc->port_table_list, list) अणु
				अगर (hba_port->sas_address == sas_address &&
				    hba_port == port)
					hba_port->phy_mask |=
					    (1 << mpt3sas_phy->phy_id);
			पूर्ण
		पूर्ण
		mpt3sas_transport_add_phy_to_an_existing_port(ioc, sas_node,
		    mpt3sas_phy, mpt3sas_phy->remote_identअगरy.sas_address,
		    port);
	पूर्ण अन्यथा
		स_रखो(&mpt3sas_phy->remote_identअगरy, 0 , माप(काष्ठा
		    sas_identअगरy));

	अगर (mpt3sas_phy->phy)
		mpt3sas_phy->phy->negotiated_linkrate =
		    _transport_convert_phy_link_rate(link_rate);

	अगर ((ioc->logging_level & MPT_DEBUG_TRANSPORT))
		dev_prपूर्णांकk(KERN_INFO, &mpt3sas_phy->phy->dev,
		    "refresh: parent sas_addr(0x%016llx),\n"
		    "\tlink_rate(0x%02x), phy(%d)\n"
		    "\tattached_handle(0x%04x), sas_addr(0x%016llx)\n",
		    (अचिन्हित दीर्घ दीर्घ)sas_address,
		    link_rate, phy_number, handle, (अचिन्हित दीर्घ दीर्घ)
		    mpt3sas_phy->remote_identअगरy.sas_address);
पूर्ण

अटल अंतरभूत व्योम *
phy_to_ioc(काष्ठा sas_phy *phy)
अणु
	काष्ठा Scsi_Host *shost = dev_to_shost(phy->dev.parent);
	वापस shost_priv(shost);
पूर्ण

अटल अंतरभूत व्योम *
rphy_to_ioc(काष्ठा sas_rphy *rphy)
अणु
	काष्ठा Scsi_Host *shost = dev_to_shost(rphy->dev.parent->parent);
	वापस shost_priv(shost);
पूर्ण

/* report phy error log काष्ठाure */
काष्ठा phy_error_log_request अणु
	u8 smp_frame_type; /* 0x40 */
	u8 function; /* 0x11 */
	u8 allocated_response_length;
	u8 request_length; /* 02 */
	u8 reserved_1[5];
	u8 phy_identअगरier;
	u8 reserved_2[2];
पूर्ण;

/* report phy error log reply काष्ठाure */
काष्ठा phy_error_log_reply अणु
	u8 smp_frame_type; /* 0x41 */
	u8 function; /* 0x11 */
	u8 function_result;
	u8 response_length;
	__be16 expander_change_count;
	u8 reserved_1[3];
	u8 phy_identअगरier;
	u8 reserved_2[2];
	__be32 invalid_dword;
	__be32 running_disparity_error;
	__be32 loss_of_dword_sync;
	__be32 phy_reset_problem;
पूर्ण;

/**
 * _transport_get_expander_phy_error_log - वापस expander counters
 * @ioc: per adapter object
 * @phy: The sas phy object
 *
 * Return: 0 क्रम success, non-zero क्रम failure.
 *
 */
अटल पूर्णांक
_transport_get_expander_phy_error_log(काष्ठा MPT3SAS_ADAPTER *ioc,
	काष्ठा sas_phy *phy)
अणु
	Mpi2SmpPassthroughRequest_t *mpi_request;
	Mpi2SmpPassthroughReply_t *mpi_reply;
	काष्ठा phy_error_log_request *phy_error_log_request;
	काष्ठा phy_error_log_reply *phy_error_log_reply;
	पूर्णांक rc;
	u16 smid;
	व्योम *psge;
	u8 issue_reset = 0;
	व्योम *data_out = शून्य;
	dma_addr_t data_out_dma;
	u32 sz;

	अगर (ioc->shost_recovery || ioc->pci_error_recovery) अणु
		ioc_info(ioc, "%s: host reset in progress!\n", __func__);
		वापस -EFAULT;
	पूर्ण

	mutex_lock(&ioc->transport_cmds.mutex);

	अगर (ioc->transport_cmds.status != MPT3_CMD_NOT_USED) अणु
		ioc_err(ioc, "%s: transport_cmds in use\n", __func__);
		rc = -EAGAIN;
		जाओ out;
	पूर्ण
	ioc->transport_cmds.status = MPT3_CMD_PENDING;

	rc = mpt3sas_रुको_क्रम_ioc(ioc, IOC_OPERATIONAL_WAIT_COUNT);
	अगर (rc)
		जाओ out;

	smid = mpt3sas_base_get_smid(ioc, ioc->transport_cb_idx);
	अगर (!smid) अणु
		ioc_err(ioc, "%s: failed obtaining a smid\n", __func__);
		rc = -EAGAIN;
		जाओ out;
	पूर्ण

	mpi_request = mpt3sas_base_get_msg_frame(ioc, smid);
	ioc->transport_cmds.smid = smid;

	sz = माप(काष्ठा phy_error_log_request) +
	    माप(काष्ठा phy_error_log_reply);
	data_out = dma_alloc_coherent(&ioc->pdev->dev, sz, &data_out_dma,
			GFP_KERNEL);
	अगर (!data_out) अणु
		pr_err("failure at %s:%d/%s()!\n", __खाता__,
		    __LINE__, __func__);
		rc = -ENOMEM;
		mpt3sas_base_मुक्त_smid(ioc, smid);
		जाओ out;
	पूर्ण

	rc = -EINVAL;
	स_रखो(data_out, 0, sz);
	phy_error_log_request = data_out;
	phy_error_log_request->smp_frame_type = 0x40;
	phy_error_log_request->function = 0x11;
	phy_error_log_request->request_length = 2;
	phy_error_log_request->allocated_response_length = 0;
	phy_error_log_request->phy_identअगरier = phy->number;

	स_रखो(mpi_request, 0, माप(Mpi2SmpPassthroughRequest_t));
	mpi_request->Function = MPI2_FUNCTION_SMP_PASSTHROUGH;
	mpi_request->PhysicalPort = _transport_get_port_id_by_sas_phy(phy);
	mpi_request->VF_ID = 0; /* TODO */
	mpi_request->VP_ID = 0;
	mpi_request->SASAddress = cpu_to_le64(phy->identअगरy.sas_address);
	mpi_request->RequestDataLength =
	    cpu_to_le16(माप(काष्ठा phy_error_log_request));
	psge = &mpi_request->SGL;

	ioc->build_sg(ioc, psge, data_out_dma,
		माप(काष्ठा phy_error_log_request),
	    data_out_dma + माप(काष्ठा phy_error_log_request),
	    माप(काष्ठा phy_error_log_reply));

	dtransportprपूर्णांकk(ioc,
			 ioc_info(ioc, "phy_error_log - send to sas_addr(0x%016llx), phy(%d)\n",
				  (u64)phy->identअगरy.sas_address,
				  phy->number));
	init_completion(&ioc->transport_cmds.करोne);
	ioc->put_smid_शेष(ioc, smid);
	रुको_क्रम_completion_समयout(&ioc->transport_cmds.करोne, 10*HZ);

	अगर (!(ioc->transport_cmds.status & MPT3_CMD_COMPLETE)) अणु
		ioc_err(ioc, "%s: timeout\n", __func__);
		_debug_dump_mf(mpi_request,
		    माप(Mpi2SmpPassthroughRequest_t)/4);
		अगर (!(ioc->transport_cmds.status & MPT3_CMD_RESET))
			issue_reset = 1;
		जाओ issue_host_reset;
	पूर्ण

	dtransportprपूर्णांकk(ioc, ioc_info(ioc, "phy_error_log - complete\n"));

	अगर (ioc->transport_cmds.status & MPT3_CMD_REPLY_VALID) अणु

		mpi_reply = ioc->transport_cmds.reply;

		dtransportprपूर्णांकk(ioc,
				 ioc_info(ioc, "phy_error_log - reply data transfer size(%d)\n",
					  le16_to_cpu(mpi_reply->ResponseDataLength)));

		अगर (le16_to_cpu(mpi_reply->ResponseDataLength) !=
		    माप(काष्ठा phy_error_log_reply))
			जाओ out;

		phy_error_log_reply = data_out +
		    माप(काष्ठा phy_error_log_request);

		dtransportprपूर्णांकk(ioc,
				 ioc_info(ioc, "phy_error_log - function_result(%d)\n",
					  phy_error_log_reply->function_result));

		phy->invalid_dword_count =
		    be32_to_cpu(phy_error_log_reply->invalid_dword);
		phy->running_disparity_error_count =
		    be32_to_cpu(phy_error_log_reply->running_disparity_error);
		phy->loss_of_dword_sync_count =
		    be32_to_cpu(phy_error_log_reply->loss_of_dword_sync);
		phy->phy_reset_problem_count =
		    be32_to_cpu(phy_error_log_reply->phy_reset_problem);
		rc = 0;
	पूर्ण अन्यथा
		dtransportprपूर्णांकk(ioc,
				 ioc_info(ioc, "phy_error_log - no reply\n"));

 issue_host_reset:
	अगर (issue_reset)
		mpt3sas_base_hard_reset_handler(ioc, FORCE_BIG_HAMMER);
 out:
	ioc->transport_cmds.status = MPT3_CMD_NOT_USED;
	अगर (data_out)
		dma_मुक्त_coherent(&ioc->pdev->dev, sz, data_out, data_out_dma);

	mutex_unlock(&ioc->transport_cmds.mutex);
	वापस rc;
पूर्ण

/**
 * _transport_get_linkerrors - वापस phy counters क्रम both hba and expanders
 * @phy: The sas phy object
 *
 * Return: 0 क्रम success, non-zero क्रम failure.
 *
 */
अटल पूर्णांक
_transport_get_linkerrors(काष्ठा sas_phy *phy)
अणु
	काष्ठा MPT3SAS_ADAPTER *ioc = phy_to_ioc(phy);
	अचिन्हित दीर्घ flags;
	Mpi2ConfigReply_t mpi_reply;
	Mpi2SasPhyPage1_t phy_pg1;
	काष्ठा hba_port *port = phy->hostdata;
	पूर्णांक port_id = port->port_id;

	spin_lock_irqsave(&ioc->sas_node_lock, flags);
	अगर (_transport_sas_node_find_by_sas_address(ioc,
	    phy->identअगरy.sas_address,
	    mpt3sas_get_port_by_id(ioc, port_id, 0)) == शून्य) अणु
		spin_unlock_irqrestore(&ioc->sas_node_lock, flags);
		वापस -EINVAL;
	पूर्ण
	spin_unlock_irqrestore(&ioc->sas_node_lock, flags);

	अगर (phy->identअगरy.sas_address != ioc->sas_hba.sas_address)
		वापस _transport_get_expander_phy_error_log(ioc, phy);

	/* get hba phy error logs */
	अगर ((mpt3sas_config_get_phy_pg1(ioc, &mpi_reply, &phy_pg1,
		    phy->number))) अणु
		ioc_err(ioc, "failure at %s:%d/%s()!\n",
			__खाता__, __LINE__, __func__);
		वापस -ENXIO;
	पूर्ण

	अगर (mpi_reply.IOCStatus || mpi_reply.IOCLogInfo)
		ioc_info(ioc, "phy(%d), ioc_status (0x%04x), loginfo(0x%08x)\n",
			 phy->number,
			 le16_to_cpu(mpi_reply.IOCStatus),
			 le32_to_cpu(mpi_reply.IOCLogInfo));

	phy->invalid_dword_count = le32_to_cpu(phy_pg1.InvalidDwordCount);
	phy->running_disparity_error_count =
	    le32_to_cpu(phy_pg1.RunningDisparityErrorCount);
	phy->loss_of_dword_sync_count =
	    le32_to_cpu(phy_pg1.LossDwordSynchCount);
	phy->phy_reset_problem_count =
	    le32_to_cpu(phy_pg1.PhyResetProblemCount);
	वापस 0;
पूर्ण

/**
 * _transport_get_enclosure_identअगरier -
 * @rphy: The sas phy object
 * @identअगरier: ?
 *
 * Obtain the enclosure logical id क्रम an expander.
 * Return: 0 क्रम success, non-zero क्रम failure.
 */
अटल पूर्णांक
_transport_get_enclosure_identअगरier(काष्ठा sas_rphy *rphy, u64 *identअगरier)
अणु
	काष्ठा MPT3SAS_ADAPTER *ioc = rphy_to_ioc(rphy);
	काष्ठा _sas_device *sas_device;
	अचिन्हित दीर्घ flags;
	पूर्णांक rc;

	spin_lock_irqsave(&ioc->sas_device_lock, flags);
	sas_device = __mpt3sas_get_sdev_by_rphy(ioc, rphy);
	अगर (sas_device) अणु
		*identअगरier = sas_device->enclosure_logical_id;
		rc = 0;
		sas_device_put(sas_device);
	पूर्ण अन्यथा अणु
		*identअगरier = 0;
		rc = -ENXIO;
	पूर्ण

	spin_unlock_irqrestore(&ioc->sas_device_lock, flags);
	वापस rc;
पूर्ण

/**
 * _transport_get_bay_identअगरier -
 * @rphy: The sas phy object
 *
 * Return: the slot id क्रम a device that resides inside an enclosure.
 */
अटल पूर्णांक
_transport_get_bay_identअगरier(काष्ठा sas_rphy *rphy)
अणु
	काष्ठा MPT3SAS_ADAPTER *ioc = rphy_to_ioc(rphy);
	काष्ठा _sas_device *sas_device;
	अचिन्हित दीर्घ flags;
	पूर्णांक rc;

	spin_lock_irqsave(&ioc->sas_device_lock, flags);
	sas_device = __mpt3sas_get_sdev_by_rphy(ioc, rphy);
	अगर (sas_device) अणु
		rc = sas_device->slot;
		sas_device_put(sas_device);
	पूर्ण अन्यथा अणु
		rc = -ENXIO;
	पूर्ण
	spin_unlock_irqrestore(&ioc->sas_device_lock, flags);
	वापस rc;
पूर्ण

/* phy control request काष्ठाure */
काष्ठा phy_control_request अणु
	u8 smp_frame_type; /* 0x40 */
	u8 function; /* 0x91 */
	u8 allocated_response_length;
	u8 request_length; /* 0x09 */
	u16 expander_change_count;
	u8 reserved_1[3];
	u8 phy_identअगरier;
	u8 phy_operation;
	u8 reserved_2[13];
	u64 attached_device_name;
	u8 programmed_min_physical_link_rate;
	u8 programmed_max_physical_link_rate;
	u8 reserved_3[6];
पूर्ण;

/* phy control reply काष्ठाure */
काष्ठा phy_control_reply अणु
	u8 smp_frame_type; /* 0x41 */
	u8 function; /* 0x11 */
	u8 function_result;
	u8 response_length;
पूर्ण;

#घोषणा SMP_PHY_CONTROL_LINK_RESET	(0x01)
#घोषणा SMP_PHY_CONTROL_HARD_RESET	(0x02)
#घोषणा SMP_PHY_CONTROL_DISABLE		(0x03)

/**
 * _transport_expander_phy_control - expander phy control
 * @ioc: per adapter object
 * @phy: The sas phy object
 * @phy_operation: ?
 *
 * Return: 0 क्रम success, non-zero क्रम failure.
 *
 */
अटल पूर्णांक
_transport_expander_phy_control(काष्ठा MPT3SAS_ADAPTER *ioc,
	काष्ठा sas_phy *phy, u8 phy_operation)
अणु
	Mpi2SmpPassthroughRequest_t *mpi_request;
	Mpi2SmpPassthroughReply_t *mpi_reply;
	काष्ठा phy_control_request *phy_control_request;
	काष्ठा phy_control_reply *phy_control_reply;
	पूर्णांक rc;
	u16 smid;
	व्योम *psge;
	u8 issue_reset = 0;
	व्योम *data_out = शून्य;
	dma_addr_t data_out_dma;
	u32 sz;

	अगर (ioc->shost_recovery || ioc->pci_error_recovery) अणु
		ioc_info(ioc, "%s: host reset in progress!\n", __func__);
		वापस -EFAULT;
	पूर्ण

	mutex_lock(&ioc->transport_cmds.mutex);

	अगर (ioc->transport_cmds.status != MPT3_CMD_NOT_USED) अणु
		ioc_err(ioc, "%s: transport_cmds in use\n", __func__);
		rc = -EAGAIN;
		जाओ out;
	पूर्ण
	ioc->transport_cmds.status = MPT3_CMD_PENDING;

	rc = mpt3sas_रुको_क्रम_ioc(ioc, IOC_OPERATIONAL_WAIT_COUNT);
	अगर (rc)
		जाओ out;

	smid = mpt3sas_base_get_smid(ioc, ioc->transport_cb_idx);
	अगर (!smid) अणु
		ioc_err(ioc, "%s: failed obtaining a smid\n", __func__);
		rc = -EAGAIN;
		जाओ out;
	पूर्ण

	mpi_request = mpt3sas_base_get_msg_frame(ioc, smid);
	ioc->transport_cmds.smid = smid;

	sz = माप(काष्ठा phy_control_request) +
	    माप(काष्ठा phy_control_reply);
	data_out = dma_alloc_coherent(&ioc->pdev->dev, sz, &data_out_dma,
			GFP_KERNEL);
	अगर (!data_out) अणु
		pr_err("failure at %s:%d/%s()!\n", __खाता__,
		    __LINE__, __func__);
		rc = -ENOMEM;
		mpt3sas_base_मुक्त_smid(ioc, smid);
		जाओ out;
	पूर्ण

	rc = -EINVAL;
	स_रखो(data_out, 0, sz);
	phy_control_request = data_out;
	phy_control_request->smp_frame_type = 0x40;
	phy_control_request->function = 0x91;
	phy_control_request->request_length = 9;
	phy_control_request->allocated_response_length = 0;
	phy_control_request->phy_identअगरier = phy->number;
	phy_control_request->phy_operation = phy_operation;
	phy_control_request->programmed_min_physical_link_rate =
	    phy->minimum_linkrate << 4;
	phy_control_request->programmed_max_physical_link_rate =
	    phy->maximum_linkrate << 4;

	स_रखो(mpi_request, 0, माप(Mpi2SmpPassthroughRequest_t));
	mpi_request->Function = MPI2_FUNCTION_SMP_PASSTHROUGH;
	mpi_request->PhysicalPort = _transport_get_port_id_by_sas_phy(phy);
	mpi_request->VF_ID = 0; /* TODO */
	mpi_request->VP_ID = 0;
	mpi_request->SASAddress = cpu_to_le64(phy->identअगरy.sas_address);
	mpi_request->RequestDataLength =
	    cpu_to_le16(माप(काष्ठा phy_error_log_request));
	psge = &mpi_request->SGL;

	ioc->build_sg(ioc, psge, data_out_dma,
			    माप(काष्ठा phy_control_request),
	    data_out_dma + माप(काष्ठा phy_control_request),
	    माप(काष्ठा phy_control_reply));

	dtransportprपूर्णांकk(ioc,
			 ioc_info(ioc, "phy_control - send to sas_addr(0x%016llx), phy(%d), opcode(%d)\n",
				  (u64)phy->identअगरy.sas_address,
				  phy->number, phy_operation));
	init_completion(&ioc->transport_cmds.करोne);
	ioc->put_smid_शेष(ioc, smid);
	रुको_क्रम_completion_समयout(&ioc->transport_cmds.करोne, 10*HZ);

	अगर (!(ioc->transport_cmds.status & MPT3_CMD_COMPLETE)) अणु
		ioc_err(ioc, "%s: timeout\n", __func__);
		_debug_dump_mf(mpi_request,
		    माप(Mpi2SmpPassthroughRequest_t)/4);
		अगर (!(ioc->transport_cmds.status & MPT3_CMD_RESET))
			issue_reset = 1;
		जाओ issue_host_reset;
	पूर्ण

	dtransportprपूर्णांकk(ioc, ioc_info(ioc, "phy_control - complete\n"));

	अगर (ioc->transport_cmds.status & MPT3_CMD_REPLY_VALID) अणु

		mpi_reply = ioc->transport_cmds.reply;

		dtransportprपूर्णांकk(ioc,
				 ioc_info(ioc, "phy_control - reply data transfer size(%d)\n",
					  le16_to_cpu(mpi_reply->ResponseDataLength)));

		अगर (le16_to_cpu(mpi_reply->ResponseDataLength) !=
		    माप(काष्ठा phy_control_reply))
			जाओ out;

		phy_control_reply = data_out +
		    माप(काष्ठा phy_control_request);

		dtransportprपूर्णांकk(ioc,
				 ioc_info(ioc, "phy_control - function_result(%d)\n",
					  phy_control_reply->function_result));

		rc = 0;
	पूर्ण अन्यथा
		dtransportprपूर्णांकk(ioc,
				 ioc_info(ioc, "phy_control - no reply\n"));

 issue_host_reset:
	अगर (issue_reset)
		mpt3sas_base_hard_reset_handler(ioc, FORCE_BIG_HAMMER);
 out:
	ioc->transport_cmds.status = MPT3_CMD_NOT_USED;
	अगर (data_out)
		dma_मुक्त_coherent(&ioc->pdev->dev, sz, data_out,
				data_out_dma);

	mutex_unlock(&ioc->transport_cmds.mutex);
	वापस rc;
पूर्ण

/**
 * _transport_phy_reset -
 * @phy: The sas phy object
 * @hard_reset:
 *
 * Return: 0 क्रम success, non-zero क्रम failure.
 */
अटल पूर्णांक
_transport_phy_reset(काष्ठा sas_phy *phy, पूर्णांक hard_reset)
अणु
	काष्ठा MPT3SAS_ADAPTER *ioc = phy_to_ioc(phy);
	Mpi2SasIoUnitControlReply_t mpi_reply;
	Mpi2SasIoUnitControlRequest_t mpi_request;
	काष्ठा hba_port *port = phy->hostdata;
	पूर्णांक port_id = port->port_id;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ioc->sas_node_lock, flags);
	अगर (_transport_sas_node_find_by_sas_address(ioc,
	    phy->identअगरy.sas_address,
	    mpt3sas_get_port_by_id(ioc, port_id, 0)) == शून्य) अणु
		spin_unlock_irqrestore(&ioc->sas_node_lock, flags);
		वापस -EINVAL;
	पूर्ण
	spin_unlock_irqrestore(&ioc->sas_node_lock, flags);

	/* handle expander phys */
	अगर (phy->identअगरy.sas_address != ioc->sas_hba.sas_address)
		वापस _transport_expander_phy_control(ioc, phy,
		    (hard_reset == 1) ? SMP_PHY_CONTROL_HARD_RESET :
		    SMP_PHY_CONTROL_LINK_RESET);

	/* handle hba phys */
	स_रखो(&mpi_request, 0, माप(Mpi2SasIoUnitControlRequest_t));
	mpi_request.Function = MPI2_FUNCTION_SAS_IO_UNIT_CONTROL;
	mpi_request.Operation = hard_reset ?
	    MPI2_SAS_OP_PHY_HARD_RESET : MPI2_SAS_OP_PHY_LINK_RESET;
	mpi_request.PhyNum = phy->number;

	अगर ((mpt3sas_base_sas_iounit_control(ioc, &mpi_reply, &mpi_request))) अणु
		ioc_err(ioc, "failure at %s:%d/%s()!\n",
			__खाता__, __LINE__, __func__);
		वापस -ENXIO;
	पूर्ण

	अगर (mpi_reply.IOCStatus || mpi_reply.IOCLogInfo)
		ioc_info(ioc, "phy(%d), ioc_status(0x%04x), loginfo(0x%08x)\n",
			 phy->number, le16_to_cpu(mpi_reply.IOCStatus),
			 le32_to_cpu(mpi_reply.IOCLogInfo));

	वापस 0;
पूर्ण

/**
 * _transport_phy_enable - enable/disable phys
 * @phy: The sas phy object
 * @enable: enable phy when true
 *
 * Only support sas_host direct attached phys.
 * Return: 0 क्रम success, non-zero क्रम failure.
 */
अटल पूर्णांक
_transport_phy_enable(काष्ठा sas_phy *phy, पूर्णांक enable)
अणु
	काष्ठा MPT3SAS_ADAPTER *ioc = phy_to_ioc(phy);
	Mpi2SasIOUnitPage1_t *sas_iounit_pg1 = शून्य;
	Mpi2SasIOUnitPage0_t *sas_iounit_pg0 = शून्य;
	Mpi2ConfigReply_t mpi_reply;
	u16 ioc_status;
	u16 sz;
	पूर्णांक rc = 0;
	अचिन्हित दीर्घ flags;
	पूर्णांक i, discovery_active;
	काष्ठा hba_port *port = phy->hostdata;
	पूर्णांक port_id = port->port_id;

	spin_lock_irqsave(&ioc->sas_node_lock, flags);
	अगर (_transport_sas_node_find_by_sas_address(ioc,
	    phy->identअगरy.sas_address,
	    mpt3sas_get_port_by_id(ioc, port_id, 0)) == शून्य) अणु
		spin_unlock_irqrestore(&ioc->sas_node_lock, flags);
		वापस -EINVAL;
	पूर्ण
	spin_unlock_irqrestore(&ioc->sas_node_lock, flags);

	/* handle expander phys */
	अगर (phy->identअगरy.sas_address != ioc->sas_hba.sas_address)
		वापस _transport_expander_phy_control(ioc, phy,
		    (enable == 1) ? SMP_PHY_CONTROL_LINK_RESET :
		    SMP_PHY_CONTROL_DISABLE);

	/* handle hba phys */

	/* पढ़ो sas_iounit page 0 */
	sz = दुरत्व(Mpi2SasIOUnitPage0_t, PhyData) + (ioc->sas_hba.num_phys *
	    माप(Mpi2SasIOUnit0PhyData_t));
	sas_iounit_pg0 = kzalloc(sz, GFP_KERNEL);
	अगर (!sas_iounit_pg0) अणु
		ioc_err(ioc, "failure at %s:%d/%s()!\n",
			__खाता__, __LINE__, __func__);
		rc = -ENOMEM;
		जाओ out;
	पूर्ण
	अगर ((mpt3sas_config_get_sas_iounit_pg0(ioc, &mpi_reply,
	    sas_iounit_pg0, sz))) अणु
		ioc_err(ioc, "failure at %s:%d/%s()!\n",
			__खाता__, __LINE__, __func__);
		rc = -ENXIO;
		जाओ out;
	पूर्ण
	ioc_status = le16_to_cpu(mpi_reply.IOCStatus) &
	    MPI2_IOCSTATUS_MASK;
	अगर (ioc_status != MPI2_IOCSTATUS_SUCCESS) अणु
		ioc_err(ioc, "failure at %s:%d/%s()!\n",
			__खाता__, __LINE__, __func__);
		rc = -EIO;
		जाओ out;
	पूर्ण

	/* unable to enable/disable phys when when discovery is active */
	क्रम (i = 0, discovery_active = 0; i < ioc->sas_hba.num_phys ; i++) अणु
		अगर (sas_iounit_pg0->PhyData[i].PortFlags &
		    MPI2_SASIOUNIT0_PORTFLAGS_DISCOVERY_IN_PROGRESS) अणु
			ioc_err(ioc, "discovery is active on port = %d, phy = %d: unable to enable/disable phys, try again later!\n",
				sas_iounit_pg0->PhyData[i].Port, i);
			discovery_active = 1;
		पूर्ण
	पूर्ण

	अगर (discovery_active) अणु
		rc = -EAGAIN;
		जाओ out;
	पूर्ण

	/* पढ़ो sas_iounit page 1 */
	sz = दुरत्व(Mpi2SasIOUnitPage1_t, PhyData) + (ioc->sas_hba.num_phys *
	    माप(Mpi2SasIOUnit1PhyData_t));
	sas_iounit_pg1 = kzalloc(sz, GFP_KERNEL);
	अगर (!sas_iounit_pg1) अणु
		ioc_err(ioc, "failure at %s:%d/%s()!\n",
			__खाता__, __LINE__, __func__);
		rc = -ENOMEM;
		जाओ out;
	पूर्ण
	अगर ((mpt3sas_config_get_sas_iounit_pg1(ioc, &mpi_reply,
	    sas_iounit_pg1, sz))) अणु
		ioc_err(ioc, "failure at %s:%d/%s()!\n",
			__खाता__, __LINE__, __func__);
		rc = -ENXIO;
		जाओ out;
	पूर्ण
	ioc_status = le16_to_cpu(mpi_reply.IOCStatus) &
	    MPI2_IOCSTATUS_MASK;
	अगर (ioc_status != MPI2_IOCSTATUS_SUCCESS) अणु
		ioc_err(ioc, "failure at %s:%d/%s()!\n",
			__खाता__, __LINE__, __func__);
		rc = -EIO;
		जाओ out;
	पूर्ण

	/* copy Port/PortFlags/PhyFlags from page 0 */
	क्रम (i = 0; i < ioc->sas_hba.num_phys ; i++) अणु
		sas_iounit_pg1->PhyData[i].Port =
		    sas_iounit_pg0->PhyData[i].Port;
		sas_iounit_pg1->PhyData[i].PortFlags =
		    (sas_iounit_pg0->PhyData[i].PortFlags &
		    MPI2_SASIOUNIT0_PORTFLAGS_AUTO_PORT_CONFIG);
		sas_iounit_pg1->PhyData[i].PhyFlags =
		    (sas_iounit_pg0->PhyData[i].PhyFlags &
		    (MPI2_SASIOUNIT0_PHYFLAGS_ZONING_ENABLED +
		    MPI2_SASIOUNIT0_PHYFLAGS_PHY_DISABLED));
	पूर्ण

	अगर (enable)
		sas_iounit_pg1->PhyData[phy->number].PhyFlags
		    &= ~MPI2_SASIOUNIT1_PHYFLAGS_PHY_DISABLE;
	अन्यथा
		sas_iounit_pg1->PhyData[phy->number].PhyFlags
		    |= MPI2_SASIOUNIT1_PHYFLAGS_PHY_DISABLE;

	mpt3sas_config_set_sas_iounit_pg1(ioc, &mpi_reply, sas_iounit_pg1, sz);

	/* link reset */
	अगर (enable)
		_transport_phy_reset(phy, 0);

 out:
	kमुक्त(sas_iounit_pg1);
	kमुक्त(sas_iounit_pg0);
	वापस rc;
पूर्ण

/**
 * _transport_phy_speed - set phy min/max link rates
 * @phy: The sas phy object
 * @rates: rates defined in sas_phy_linkrates
 *
 * Only support sas_host direct attached phys.
 *
 * Return: 0 क्रम success, non-zero क्रम failure.
 */
अटल पूर्णांक
_transport_phy_speed(काष्ठा sas_phy *phy, काष्ठा sas_phy_linkrates *rates)
अणु
	काष्ठा MPT3SAS_ADAPTER *ioc = phy_to_ioc(phy);
	Mpi2SasIOUnitPage1_t *sas_iounit_pg1 = शून्य;
	Mpi2SasPhyPage0_t phy_pg0;
	Mpi2ConfigReply_t mpi_reply;
	u16 ioc_status;
	u16 sz;
	पूर्णांक i;
	पूर्णांक rc = 0;
	अचिन्हित दीर्घ flags;
	काष्ठा hba_port *port = phy->hostdata;
	पूर्णांक port_id = port->port_id;

	spin_lock_irqsave(&ioc->sas_node_lock, flags);
	अगर (_transport_sas_node_find_by_sas_address(ioc,
	    phy->identअगरy.sas_address,
	    mpt3sas_get_port_by_id(ioc, port_id, 0)) == शून्य) अणु
		spin_unlock_irqrestore(&ioc->sas_node_lock, flags);
		वापस -EINVAL;
	पूर्ण
	spin_unlock_irqrestore(&ioc->sas_node_lock, flags);

	अगर (!rates->minimum_linkrate)
		rates->minimum_linkrate = phy->minimum_linkrate;
	अन्यथा अगर (rates->minimum_linkrate < phy->minimum_linkrate_hw)
		rates->minimum_linkrate = phy->minimum_linkrate_hw;

	अगर (!rates->maximum_linkrate)
		rates->maximum_linkrate = phy->maximum_linkrate;
	अन्यथा अगर (rates->maximum_linkrate > phy->maximum_linkrate_hw)
		rates->maximum_linkrate = phy->maximum_linkrate_hw;

	/* handle expander phys */
	अगर (phy->identअगरy.sas_address != ioc->sas_hba.sas_address) अणु
		phy->minimum_linkrate = rates->minimum_linkrate;
		phy->maximum_linkrate = rates->maximum_linkrate;
		वापस _transport_expander_phy_control(ioc, phy,
		    SMP_PHY_CONTROL_LINK_RESET);
	पूर्ण

	/* handle hba phys */

	/* sas_iounit page 1 */
	sz = दुरत्व(Mpi2SasIOUnitPage1_t, PhyData) + (ioc->sas_hba.num_phys *
	    माप(Mpi2SasIOUnit1PhyData_t));
	sas_iounit_pg1 = kzalloc(sz, GFP_KERNEL);
	अगर (!sas_iounit_pg1) अणु
		ioc_err(ioc, "failure at %s:%d/%s()!\n",
			__खाता__, __LINE__, __func__);
		rc = -ENOMEM;
		जाओ out;
	पूर्ण
	अगर ((mpt3sas_config_get_sas_iounit_pg1(ioc, &mpi_reply,
	    sas_iounit_pg1, sz))) अणु
		ioc_err(ioc, "failure at %s:%d/%s()!\n",
			__खाता__, __LINE__, __func__);
		rc = -ENXIO;
		जाओ out;
	पूर्ण
	ioc_status = le16_to_cpu(mpi_reply.IOCStatus) &
	    MPI2_IOCSTATUS_MASK;
	अगर (ioc_status != MPI2_IOCSTATUS_SUCCESS) अणु
		ioc_err(ioc, "failure at %s:%d/%s()!\n",
			__खाता__, __LINE__, __func__);
		rc = -EIO;
		जाओ out;
	पूर्ण

	क्रम (i = 0; i < ioc->sas_hba.num_phys; i++) अणु
		अगर (phy->number != i) अणु
			sas_iounit_pg1->PhyData[i].MaxMinLinkRate =
			    (ioc->sas_hba.phy[i].phy->minimum_linkrate +
			    (ioc->sas_hba.phy[i].phy->maximum_linkrate << 4));
		पूर्ण अन्यथा अणु
			sas_iounit_pg1->PhyData[i].MaxMinLinkRate =
			    (rates->minimum_linkrate +
			    (rates->maximum_linkrate << 4));
		पूर्ण
	पूर्ण

	अगर (mpt3sas_config_set_sas_iounit_pg1(ioc, &mpi_reply, sas_iounit_pg1,
	    sz)) अणु
		ioc_err(ioc, "failure at %s:%d/%s()!\n",
			__खाता__, __LINE__, __func__);
		rc = -ENXIO;
		जाओ out;
	पूर्ण

	/* link reset */
	_transport_phy_reset(phy, 0);

	/* पढ़ो phy page 0, then update the rates in the sas transport phy */
	अगर (!mpt3sas_config_get_phy_pg0(ioc, &mpi_reply, &phy_pg0,
	    phy->number)) अणु
		phy->minimum_linkrate = _transport_convert_phy_link_rate(
		    phy_pg0.ProgrammedLinkRate & MPI2_SAS_PRATE_MIN_RATE_MASK);
		phy->maximum_linkrate = _transport_convert_phy_link_rate(
		    phy_pg0.ProgrammedLinkRate >> 4);
		phy->negotiated_linkrate = _transport_convert_phy_link_rate(
		    phy_pg0.NegotiatedLinkRate &
		    MPI2_SAS_NEG_LINK_RATE_MASK_PHYSICAL);
	पूर्ण

 out:
	kमुक्त(sas_iounit_pg1);
	वापस rc;
पूर्ण

अटल पूर्णांक
_transport_map_smp_buffer(काष्ठा device *dev, काष्ठा bsg_buffer *buf,
		dma_addr_t *dma_addr, माप_प्रकार *dma_len, व्योम **p)
अणु
	/* Check अगर the request is split across multiple segments */
	अगर (buf->sg_cnt > 1) अणु
		*p = dma_alloc_coherent(dev, buf->payload_len, dma_addr,
				GFP_KERNEL);
		अगर (!*p)
			वापस -ENOMEM;
		*dma_len = buf->payload_len;
	पूर्ण अन्यथा अणु
		अगर (!dma_map_sg(dev, buf->sg_list, 1, DMA_BIसूचीECTIONAL))
			वापस -ENOMEM;
		*dma_addr = sg_dma_address(buf->sg_list);
		*dma_len = sg_dma_len(buf->sg_list);
		*p = शून्य;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम
_transport_unmap_smp_buffer(काष्ठा device *dev, काष्ठा bsg_buffer *buf,
		dma_addr_t dma_addr, व्योम *p)
अणु
	अगर (p)
		dma_मुक्त_coherent(dev, buf->payload_len, p, dma_addr);
	अन्यथा
		dma_unmap_sg(dev, buf->sg_list, 1, DMA_BIसूचीECTIONAL);
पूर्ण

/**
 * _transport_smp_handler - transport portal क्रम smp passthru
 * @job: ?
 * @shost: shost object
 * @rphy: sas transport rphy object
 *
 * This used primarily क्रम smp_utils.
 * Example:
 *           smp_rep_general /sys/class/bsg/expander-5:0
 */
अटल व्योम
_transport_smp_handler(काष्ठा bsg_job *job, काष्ठा Scsi_Host *shost,
		काष्ठा sas_rphy *rphy)
अणु
	काष्ठा MPT3SAS_ADAPTER *ioc = shost_priv(shost);
	Mpi2SmpPassthroughRequest_t *mpi_request;
	Mpi2SmpPassthroughReply_t *mpi_reply;
	पूर्णांक rc;
	u16 smid;
	व्योम *psge;
	dma_addr_t dma_addr_in;
	dma_addr_t dma_addr_out;
	व्योम *addr_in = शून्य;
	व्योम *addr_out = शून्य;
	माप_प्रकार dma_len_in;
	माप_प्रकार dma_len_out;
	अचिन्हित पूर्णांक reslen = 0;

	अगर (ioc->shost_recovery || ioc->pci_error_recovery) अणु
		ioc_info(ioc, "%s: host reset in progress!\n", __func__);
		rc = -EFAULT;
		जाओ job_करोne;
	पूर्ण

	rc = mutex_lock_पूर्णांकerruptible(&ioc->transport_cmds.mutex);
	अगर (rc)
		जाओ job_करोne;

	अगर (ioc->transport_cmds.status != MPT3_CMD_NOT_USED) अणु
		ioc_err(ioc, "%s: transport_cmds in use\n",
			__func__);
		rc = -EAGAIN;
		जाओ out;
	पूर्ण
	ioc->transport_cmds.status = MPT3_CMD_PENDING;

	rc = _transport_map_smp_buffer(&ioc->pdev->dev, &job->request_payload,
			&dma_addr_out, &dma_len_out, &addr_out);
	अगर (rc)
		जाओ out;
	अगर (addr_out) अणु
		sg_copy_to_buffer(job->request_payload.sg_list,
				job->request_payload.sg_cnt, addr_out,
				job->request_payload.payload_len);
	पूर्ण

	rc = _transport_map_smp_buffer(&ioc->pdev->dev, &job->reply_payload,
			&dma_addr_in, &dma_len_in, &addr_in);
	अगर (rc)
		जाओ unmap_out;

	rc = mpt3sas_रुको_क्रम_ioc(ioc, IOC_OPERATIONAL_WAIT_COUNT);
	अगर (rc)
		जाओ unmap_in;

	smid = mpt3sas_base_get_smid(ioc, ioc->transport_cb_idx);
	अगर (!smid) अणु
		ioc_err(ioc, "%s: failed obtaining a smid\n", __func__);
		rc = -EAGAIN;
		जाओ unmap_in;
	पूर्ण

	rc = 0;
	mpi_request = mpt3sas_base_get_msg_frame(ioc, smid);
	ioc->transport_cmds.smid = smid;

	स_रखो(mpi_request, 0, माप(Mpi2SmpPassthroughRequest_t));
	mpi_request->Function = MPI2_FUNCTION_SMP_PASSTHROUGH;
	mpi_request->PhysicalPort = _transport_get_port_id_by_rphy(ioc, rphy);
	mpi_request->SASAddress = (rphy) ?
	    cpu_to_le64(rphy->identअगरy.sas_address) :
	    cpu_to_le64(ioc->sas_hba.sas_address);
	mpi_request->RequestDataLength = cpu_to_le16(dma_len_out - 4);
	psge = &mpi_request->SGL;

	ioc->build_sg(ioc, psge, dma_addr_out, dma_len_out - 4, dma_addr_in,
			dma_len_in - 4);

	dtransportprपूर्णांकk(ioc,
			 ioc_info(ioc, "%s: sending smp request\n", __func__));

	init_completion(&ioc->transport_cmds.करोne);
	ioc->put_smid_शेष(ioc, smid);
	रुको_क्रम_completion_समयout(&ioc->transport_cmds.करोne, 10*HZ);

	अगर (!(ioc->transport_cmds.status & MPT3_CMD_COMPLETE)) अणु
		ioc_err(ioc, "%s: timeout\n", __func__);
		_debug_dump_mf(mpi_request,
		    माप(Mpi2SmpPassthroughRequest_t)/4);
		अगर (!(ioc->transport_cmds.status & MPT3_CMD_RESET)) अणु
			mpt3sas_base_hard_reset_handler(ioc, FORCE_BIG_HAMMER);
			rc = -ETIMEDOUT;
			जाओ unmap_in;
		पूर्ण
	पूर्ण

	dtransportprपूर्णांकk(ioc, ioc_info(ioc, "%s - complete\n", __func__));

	अगर (!(ioc->transport_cmds.status & MPT3_CMD_REPLY_VALID)) अणु
		dtransportprपूर्णांकk(ioc,
				 ioc_info(ioc, "%s: no reply\n", __func__));
		rc = -ENXIO;
		जाओ unmap_in;
	पूर्ण

	mpi_reply = ioc->transport_cmds.reply;

	dtransportprपूर्णांकk(ioc,
			 ioc_info(ioc, "%s: reply data transfer size(%d)\n",
				  __func__,
				  le16_to_cpu(mpi_reply->ResponseDataLength)));

	स_नकल(job->reply, mpi_reply, माप(*mpi_reply));
	job->reply_len = माप(*mpi_reply);
	reslen = le16_to_cpu(mpi_reply->ResponseDataLength);

	अगर (addr_in) अणु
		sg_copy_to_buffer(job->reply_payload.sg_list,
				job->reply_payload.sg_cnt, addr_in,
				job->reply_payload.payload_len);
	पूर्ण

	rc = 0;
 unmap_in:
	_transport_unmap_smp_buffer(&ioc->pdev->dev, &job->reply_payload,
			dma_addr_in, addr_in);
 unmap_out:
	_transport_unmap_smp_buffer(&ioc->pdev->dev, &job->request_payload,
			dma_addr_out, addr_out);
 out:
	ioc->transport_cmds.status = MPT3_CMD_NOT_USED;
	mutex_unlock(&ioc->transport_cmds.mutex);
job_करोne:
	bsg_job_करोne(job, rc, reslen);
पूर्ण

काष्ठा sas_function_ढाँचा mpt3sas_transport_functions = अणु
	.get_linkerrors		= _transport_get_linkerrors,
	.get_enclosure_identअगरier = _transport_get_enclosure_identअगरier,
	.get_bay_identअगरier	= _transport_get_bay_identअगरier,
	.phy_reset		= _transport_phy_reset,
	.phy_enable		= _transport_phy_enable,
	.set_phy_speed		= _transport_phy_speed,
	.smp_handler		= _transport_smp_handler,
पूर्ण;

काष्ठा scsi_transport_ढाँचा *mpt3sas_transport_ढाँचा;
