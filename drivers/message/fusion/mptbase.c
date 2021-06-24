<शैली गुरु>
/*
 *  linux/drivers/message/fusion/mptbase.c
 *      This is the Fusion MPT base driver which supports multiple
 *      (SCSI + LAN) specialized protocol drivers.
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

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/init.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>
#समावेश <linux/pci.h>
#समावेश <linux/kdev_t.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <scsi/scsi_host.h>

#समावेश "mptbase.h"
#समावेश "lsi/mpi_log_fc.h"

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
#घोषणा my_NAME		"Fusion MPT base driver"
#घोषणा my_VERSION	MPT_LINUX_VERSION_COMMON
#घोषणा MYNAM		"mptbase"

MODULE_AUTHOR(MODULEAUTHOR);
MODULE_DESCRIPTION(my_NAME);
MODULE_LICENSE("GPL");
MODULE_VERSION(my_VERSION);

/*
 *  cmd line parameters
 */

अटल पूर्णांक mpt_msi_enable_spi;
module_param(mpt_msi_enable_spi, पूर्णांक, 0);
MODULE_PARM_DESC(mpt_msi_enable_spi,
		 " Enable MSI Support for SPI controllers (default=0)");

अटल पूर्णांक mpt_msi_enable_fc;
module_param(mpt_msi_enable_fc, पूर्णांक, 0);
MODULE_PARM_DESC(mpt_msi_enable_fc,
		 " Enable MSI Support for FC controllers (default=0)");

अटल पूर्णांक mpt_msi_enable_sas;
module_param(mpt_msi_enable_sas, पूर्णांक, 0);
MODULE_PARM_DESC(mpt_msi_enable_sas,
		 " Enable MSI Support for SAS controllers (default=0)");

अटल पूर्णांक mpt_channel_mapping;
module_param(mpt_channel_mapping, पूर्णांक, 0);
MODULE_PARM_DESC(mpt_channel_mapping, " Mapping id's to channels (default=0)");

अटल पूर्णांक mpt_debug_level;
अटल पूर्णांक mpt_set_debug_level(स्थिर अक्षर *val, स्थिर काष्ठा kernel_param *kp);
module_param_call(mpt_debug_level, mpt_set_debug_level, param_get_पूर्णांक,
		  &mpt_debug_level, 0600);
MODULE_PARM_DESC(mpt_debug_level,
		 " debug level - refer to mptdebug.h - (default=0)");

पूर्णांक mpt_fwfault_debug;
EXPORT_SYMBOL(mpt_fwfault_debug);
module_param(mpt_fwfault_debug, पूर्णांक, 0600);
MODULE_PARM_DESC(mpt_fwfault_debug,
		 "Enable detection of Firmware fault and halt Firmware on fault - (default=0)");

अटल अक्षर	MptCallbacksName[MPT_MAX_PROTOCOL_DRIVERS]
				[MPT_MAX_CALLBACKNAME_LEN+1];

#अगर_घोषित MFCNT
अटल पूर्णांक mfcounter = 0;
#घोषणा PRINT_MF_COUNT 20000
#पूर्ण_अगर

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/*
 *  Public data...
 */

#घोषणा WHOINIT_UNKNOWN		0xAA

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/*
 *  Private data...
 */
					/* Adapter link list */
LIST_HEAD(ioc_list);
					/* Callback lookup table */
अटल MPT_CALLBACK		 MptCallbacks[MPT_MAX_PROTOCOL_DRIVERS];
					/* Protocol driver class lookup table */
अटल पूर्णांक			 MptDriverClass[MPT_MAX_PROTOCOL_DRIVERS];
					/* Event handler lookup table */
अटल MPT_EVHANDLER		 MptEvHandlers[MPT_MAX_PROTOCOL_DRIVERS];
					/* Reset handler lookup table */
अटल MPT_RESETHANDLER		 MptResetHandlers[MPT_MAX_PROTOCOL_DRIVERS];
अटल काष्ठा mpt_pci_driver 	*MptDeviceDriverHandlers[MPT_MAX_PROTOCOL_DRIVERS];

#अगर_घोषित CONFIG_PROC_FS
अटल काष्ठा proc_dir_entry 	*mpt_proc_root_dir;
#पूर्ण_अगर

/*
 *  Driver Callback Index's
 */
अटल u8 mpt_base_index = MPT_MAX_PROTOCOL_DRIVERS;
अटल u8 last_drv_idx;

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/*
 *  Forward protos...
 */
अटल irqवापस_t mpt_पूर्णांकerrupt(पूर्णांक irq, व्योम *bus_id);
अटल पूर्णांक	mptbase_reply(MPT_ADAPTER *ioc, MPT_FRAME_HDR *req,
		MPT_FRAME_HDR *reply);
अटल पूर्णांक	mpt_handshake_req_reply_रुको(MPT_ADAPTER *ioc, पूर्णांक reqBytes,
			u32 *req, पूर्णांक replyBytes, u16 *u16reply, पूर्णांक maxरुको,
			पूर्णांक sleepFlag);
अटल पूर्णांक	mpt_करो_ioc_recovery(MPT_ADAPTER *ioc, u32 reason, पूर्णांक sleepFlag);
अटल व्योम	mpt_detect_bound_ports(MPT_ADAPTER *ioc, काष्ठा pci_dev *pdev);
अटल व्योम	mpt_adapter_disable(MPT_ADAPTER *ioc);
अटल व्योम	mpt_adapter_dispose(MPT_ADAPTER *ioc);

अटल व्योम	MptDisplayIocCapabilities(MPT_ADAPTER *ioc);
अटल पूर्णांक	MakeIocReady(MPT_ADAPTER *ioc, पूर्णांक क्रमce, पूर्णांक sleepFlag);
अटल पूर्णांक	GetIocFacts(MPT_ADAPTER *ioc, पूर्णांक sleepFlag, पूर्णांक reason);
अटल पूर्णांक	GetPortFacts(MPT_ADAPTER *ioc, पूर्णांक portnum, पूर्णांक sleepFlag);
अटल पूर्णांक	SendIocInit(MPT_ADAPTER *ioc, पूर्णांक sleepFlag);
अटल पूर्णांक	SendPortEnable(MPT_ADAPTER *ioc, पूर्णांक portnum, पूर्णांक sleepFlag);
अटल पूर्णांक	mpt_करो_upload(MPT_ADAPTER *ioc, पूर्णांक sleepFlag);
अटल पूर्णांक	mpt_करोwnloadboot(MPT_ADAPTER *ioc, MpiFwHeader_t *pFwHeader, पूर्णांक sleepFlag);
अटल पूर्णांक	mpt_diag_reset(MPT_ADAPTER *ioc, पूर्णांक ignore, पूर्णांक sleepFlag);
अटल पूर्णांक	KickStart(MPT_ADAPTER *ioc, पूर्णांक ignore, पूर्णांक sleepFlag);
अटल पूर्णांक	SendIocReset(MPT_ADAPTER *ioc, u8 reset_type, पूर्णांक sleepFlag);
अटल पूर्णांक	PrimeIocFअगरos(MPT_ADAPTER *ioc);
अटल पूर्णांक	WaitForDoorbellAck(MPT_ADAPTER *ioc, पूर्णांक howदीर्घ, पूर्णांक sleepFlag);
अटल पूर्णांक	WaitForDoorbellInt(MPT_ADAPTER *ioc, पूर्णांक howदीर्घ, पूर्णांक sleepFlag);
अटल पूर्णांक	WaitForDoorbellReply(MPT_ADAPTER *ioc, पूर्णांक howदीर्घ, पूर्णांक sleepFlag);
अटल पूर्णांक	GetLanConfigPages(MPT_ADAPTER *ioc);
अटल पूर्णांक	GetIoUnitPage2(MPT_ADAPTER *ioc);
पूर्णांक		mptbase_sas_persist_operation(MPT_ADAPTER *ioc, u8 persist_opcode);
अटल पूर्णांक	mpt_GetScsiPortSettings(MPT_ADAPTER *ioc, पूर्णांक portnum);
अटल पूर्णांक	mpt_पढ़ोScsiDevicePageHeaders(MPT_ADAPTER *ioc, पूर्णांक portnum);
अटल व्योम 	mpt_पढ़ो_ioc_pg_1(MPT_ADAPTER *ioc);
अटल व्योम 	mpt_पढ़ो_ioc_pg_4(MPT_ADAPTER *ioc);
अटल व्योम	mpt_get_manufacturing_pg_0(MPT_ADAPTER *ioc);
अटल पूर्णांक	SendEventNotअगरication(MPT_ADAPTER *ioc, u8 EvSwitch,
	पूर्णांक sleepFlag);
अटल पूर्णांक	SendEventAck(MPT_ADAPTER *ioc, EventNotअगरicationReply_t *evnp);
अटल पूर्णांक	mpt_host_page_access_control(MPT_ADAPTER *ioc, u8 access_control_value, पूर्णांक sleepFlag);
अटल पूर्णांक	mpt_host_page_alloc(MPT_ADAPTER *ioc, pIOCInit_t ioc_init);

#अगर_घोषित CONFIG_PROC_FS
अटल पूर्णांक mpt_summary_proc_show(काष्ठा seq_file *m, व्योम *v);
अटल पूर्णांक mpt_version_proc_show(काष्ठा seq_file *m, व्योम *v);
अटल पूर्णांक mpt_iocinfo_proc_show(काष्ठा seq_file *m, व्योम *v);
#पूर्ण_अगर
अटल व्योम	mpt_get_fw_exp_ver(अक्षर *buf, MPT_ADAPTER *ioc);

अटल पूर्णांक	ProcessEventNotअगरication(MPT_ADAPTER *ioc,
		EventNotअगरicationReply_t *evReply, पूर्णांक *evHandlers);
अटल व्योम	mpt_iocstatus_info(MPT_ADAPTER *ioc, u32 ioc_status, MPT_FRAME_HDR *mf);
अटल व्योम	mpt_fc_log_info(MPT_ADAPTER *ioc, u32 log_info);
अटल व्योम	mpt_spi_log_info(MPT_ADAPTER *ioc, u32 log_info);
अटल व्योम	mpt_sas_log_info(MPT_ADAPTER *ioc, u32 log_info , u8 cb_idx);
अटल पूर्णांक	mpt_पढ़ो_ioc_pg_3(MPT_ADAPTER *ioc);
अटल व्योम	mpt_inactive_raid_list_मुक्त(MPT_ADAPTER *ioc);

/* module entry poपूर्णांक */
अटल पूर्णांक  __init    fusion_init  (व्योम);
अटल व्योम __निकास    fusion_निकास  (व्योम);

#घोषणा CHIPREG_READ32(addr) 		पढ़ोl_relaxed(addr)
#घोषणा CHIPREG_READ32_dmasync(addr)	पढ़ोl(addr)
#घोषणा CHIPREG_WRITE32(addr,val) 	ग_लिखोl(val, addr)
#घोषणा CHIPREG_PIO_WRITE32(addr,val)	outl(val, (अचिन्हित दीर्घ)addr)
#घोषणा CHIPREG_PIO_READ32(addr) 	inl((अचिन्हित दीर्घ)addr)

अटल व्योम
pci_disable_io_access(काष्ठा pci_dev *pdev)
अणु
	u16 command_reg;

	pci_पढ़ो_config_word(pdev, PCI_COMMAND, &command_reg);
	command_reg &= ~1;
	pci_ग_लिखो_config_word(pdev, PCI_COMMAND, command_reg);
पूर्ण

अटल व्योम
pci_enable_io_access(काष्ठा pci_dev *pdev)
अणु
	u16 command_reg;

	pci_पढ़ो_config_word(pdev, PCI_COMMAND, &command_reg);
	command_reg |= 1;
	pci_ग_लिखो_config_word(pdev, PCI_COMMAND, command_reg);
पूर्ण

अटल पूर्णांक mpt_set_debug_level(स्थिर अक्षर *val, स्थिर काष्ठा kernel_param *kp)
अणु
	पूर्णांक ret = param_set_पूर्णांक(val, kp);
	MPT_ADAPTER *ioc;

	अगर (ret)
		वापस ret;

	list_क्रम_each_entry(ioc, &ioc_list, list)
		ioc->debug_level = mpt_debug_level;
	वापस 0;
पूर्ण

/**
 *	mpt_get_cb_idx - obtain cb_idx क्रम रेजिस्टरed driver
 *	@dclass: class driver क्रमागत
 *
 *	Returns cb_idx, or zero means it wasn't found
 **/
अटल u8
mpt_get_cb_idx(MPT_DRIVER_CLASS dclass)
अणु
	u8 cb_idx;

	क्रम (cb_idx = MPT_MAX_PROTOCOL_DRIVERS-1; cb_idx; cb_idx--)
		अगर (MptDriverClass[cb_idx] == dclass)
			वापस cb_idx;
	वापस 0;
पूर्ण

/**
 * mpt_is_discovery_complete - determine अगर discovery has completed
 * @ioc: per adatper instance
 *
 * Returns 1 when discovery completed, अन्यथा zero.
 */
अटल पूर्णांक
mpt_is_discovery_complete(MPT_ADAPTER *ioc)
अणु
	ConfigExtendedPageHeader_t hdr;
	CONFIGPARMS cfg;
	SasIOUnitPage0_t *buffer;
	dma_addr_t dma_handle;
	पूर्णांक rc = 0;

	स_रखो(&hdr, 0, माप(ConfigExtendedPageHeader_t));
	स_रखो(&cfg, 0, माप(CONFIGPARMS));
	hdr.PageVersion = MPI_SASIOUNITPAGE0_PAGEVERSION;
	hdr.PageType = MPI_CONFIG_PAGETYPE_EXTENDED;
	hdr.ExtPageType = MPI_CONFIG_EXTPAGETYPE_SAS_IO_UNIT;
	cfg.cfghdr.ehdr = &hdr;
	cfg.action = MPI_CONFIG_ACTION_PAGE_HEADER;

	अगर ((mpt_config(ioc, &cfg)))
		जाओ out;
	अगर (!hdr.ExtPageLength)
		जाओ out;

	buffer = pci_alloc_consistent(ioc->pcidev, hdr.ExtPageLength * 4,
	    &dma_handle);
	अगर (!buffer)
		जाओ out;

	cfg.physAddr = dma_handle;
	cfg.action = MPI_CONFIG_ACTION_PAGE_READ_CURRENT;

	अगर ((mpt_config(ioc, &cfg)))
		जाओ out_मुक्त_consistent;

	अगर (!(buffer->PhyData[0].PortFlags &
	    MPI_SAS_IOUNIT0_PORT_FLAGS_DISCOVERY_IN_PROGRESS))
		rc = 1;

 out_मुक्त_consistent:
	pci_मुक्त_consistent(ioc->pcidev, hdr.ExtPageLength * 4,
	    buffer, dma_handle);
 out:
	वापस rc;
पूर्ण


/**
 *  mpt_हटाओ_dead_ioc_func - kthपढ़ो context to हटाओ dead ioc
 * @arg: input argument, used to derive ioc
 *
 * Return 0 अगर controller is हटाओd from pci subप्रणाली.
 * Return -1 क्रम other हाल.
 */
अटल पूर्णांक mpt_हटाओ_dead_ioc_func(व्योम *arg)
अणु
	MPT_ADAPTER *ioc = (MPT_ADAPTER *)arg;
	काष्ठा pci_dev *pdev;

	अगर (!ioc)
		वापस -1;

	pdev = ioc->pcidev;
	अगर (!pdev)
		वापस -1;

	pci_stop_and_हटाओ_bus_device_locked(pdev);
	वापस 0;
पूर्ण



/**
 *	mpt_fault_reset_work - work perक्रमmed on workq after ioc fault
 *	@work: input argument, used to derive ioc
 *
**/
अटल व्योम
mpt_fault_reset_work(काष्ठा work_काष्ठा *work)
अणु
	MPT_ADAPTER	*ioc =
	    container_of(work, MPT_ADAPTER, fault_reset_work.work);
	u32		 ioc_raw_state;
	पूर्णांक		 rc;
	अचिन्हित दीर्घ	 flags;
	MPT_SCSI_HOST	*hd;
	काष्ठा task_काष्ठा *p;

	अगर (ioc->ioc_reset_in_progress || !ioc->active)
		जाओ out;


	ioc_raw_state = mpt_GetIocState(ioc, 0);
	अगर ((ioc_raw_state & MPI_IOC_STATE_MASK) == MPI_IOC_STATE_MASK) अणु
		prपूर्णांकk(MYIOC_s_INFO_FMT "%s: IOC is non-operational !!!!\n",
		    ioc->name, __func__);

		/*
		 * Call mptscsih_flush_pending_cmds callback so that we
		 * flush all pending commands back to OS.
		 * This call is required to aovid deadlock at block layer.
		 * Dead IOC will fail to करो diag reset,and this call is safe
		 * since dead ioc will never वापस any command back from HW.
		 */
		hd = shost_priv(ioc->sh);
		ioc->schedule_dead_ioc_flush_running_cmds(hd);

		/*Remove the Dead Host */
		p = kthपढ़ो_run(mpt_हटाओ_dead_ioc_func, ioc,
				"mpt_dead_ioc_%d", ioc->id);
		अगर (IS_ERR(p))	अणु
			prपूर्णांकk(MYIOC_s_ERR_FMT
				"%s: Running mpt_dead_ioc thread failed !\n",
				ioc->name, __func__);
		पूर्ण अन्यथा अणु
			prपूर्णांकk(MYIOC_s_WARN_FMT
				"%s: Running mpt_dead_ioc thread success !\n",
				ioc->name, __func__);
		पूर्ण
		वापस; /* करोn't rearm समयr */
	पूर्ण

	अगर ((ioc_raw_state & MPI_IOC_STATE_MASK)
			== MPI_IOC_STATE_FAULT) अणु
		prपूर्णांकk(MYIOC_s_WARN_FMT "IOC is in FAULT state (%04xh)!!!\n",
		       ioc->name, ioc_raw_state & MPI_DOORBELL_DATA_MASK);
		prपूर्णांकk(MYIOC_s_WARN_FMT "Issuing HardReset from %s!!\n",
		       ioc->name, __func__);
		rc = mpt_HardResetHandler(ioc, CAN_SLEEP);
		prपूर्णांकk(MYIOC_s_WARN_FMT "%s: HardReset: %s\n", ioc->name,
		       __func__, (rc == 0) ? "success" : "failed");
		ioc_raw_state = mpt_GetIocState(ioc, 0);
		अगर ((ioc_raw_state & MPI_IOC_STATE_MASK) == MPI_IOC_STATE_FAULT)
			prपूर्णांकk(MYIOC_s_WARN_FMT "IOC is in FAULT state after "
			    "reset (%04xh)\n", ioc->name, ioc_raw_state &
			    MPI_DOORBELL_DATA_MASK);
	पूर्ण अन्यथा अगर (ioc->bus_type == SAS && ioc->sas_discovery_quiesce_io) अणु
		अगर ((mpt_is_discovery_complete(ioc))) अणु
			devtprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT "clearing "
			    "discovery_quiesce_io flag\n", ioc->name));
			ioc->sas_discovery_quiesce_io = 0;
		पूर्ण
	पूर्ण

 out:
	/*
	 * Take turns polling alternate controller
	 */
	अगर (ioc->alt_ioc)
		ioc = ioc->alt_ioc;

	/* rearm the समयr */
	spin_lock_irqsave(&ioc->taskmgmt_lock, flags);
	अगर (ioc->reset_work_q)
		queue_delayed_work(ioc->reset_work_q, &ioc->fault_reset_work,
			msecs_to_jअगरfies(MPT_POLLING_INTERVAL));
	spin_unlock_irqrestore(&ioc->taskmgmt_lock, flags);
पूर्ण


/*
 *  Process turbo (context) reply...
 */
अटल व्योम
mpt_turbo_reply(MPT_ADAPTER *ioc, u32 pa)
अणु
	MPT_FRAME_HDR *mf = शून्य;
	MPT_FRAME_HDR *mr = शून्य;
	u16 req_idx = 0;
	u8 cb_idx;

	dmfprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT "Got TURBO reply req_idx=%08x\n",
				ioc->name, pa));

	चयन (pa >> MPI_CONTEXT_REPLY_TYPE_SHIFT) अणु
	हाल MPI_CONTEXT_REPLY_TYPE_SCSI_INIT:
		req_idx = pa & 0x0000FFFF;
		cb_idx = (pa & 0x00FF0000) >> 16;
		mf = MPT_INDEX_2_MFPTR(ioc, req_idx);
		अवरोध;
	हाल MPI_CONTEXT_REPLY_TYPE_LAN:
		cb_idx = mpt_get_cb_idx(MPTLAN_DRIVER);
		/*
		 *  Blind set of mf to शून्य here was fatal
		 *  after lan_reply says "freeme"
		 *  Fix sort of combined with an optimization here;
		 *  added explicit check क्रम हाल where lan_reply
		 *  was just वापसing 1 and करोing nothing अन्यथा.
		 *  For this हाल skip the callback, but set up
		 *  proper mf value first here:-)
		 */
		अगर ((pa & 0x58000000) == 0x58000000) अणु
			req_idx = pa & 0x0000FFFF;
			mf = MPT_INDEX_2_MFPTR(ioc, req_idx);
			mpt_मुक्त_msg_frame(ioc, mf);
			mb();
			वापस;
		पूर्ण
		mr = (MPT_FRAME_HDR *) CAST_U32_TO_PTR(pa);
		अवरोध;
	हाल MPI_CONTEXT_REPLY_TYPE_SCSI_TARGET:
		cb_idx = mpt_get_cb_idx(MPTSTM_DRIVER);
		mr = (MPT_FRAME_HDR *) CAST_U32_TO_PTR(pa);
		अवरोध;
	शेष:
		cb_idx = 0;
		BUG();
	पूर्ण

	/*  Check क्रम (valid) IO callback!  */
	अगर (!cb_idx || cb_idx >= MPT_MAX_PROTOCOL_DRIVERS ||
		MptCallbacks[cb_idx] == शून्य) अणु
		prपूर्णांकk(MYIOC_s_WARN_FMT "%s: Invalid cb_idx (%d)!\n",
				__func__, ioc->name, cb_idx);
		जाओ out;
	पूर्ण

	अगर (MptCallbacks[cb_idx](ioc, mf, mr))
		mpt_मुक्त_msg_frame(ioc, mf);
 out:
	mb();
पूर्ण

अटल व्योम
mpt_reply(MPT_ADAPTER *ioc, u32 pa)
अणु
	MPT_FRAME_HDR	*mf;
	MPT_FRAME_HDR	*mr;
	u16		 req_idx;
	u8		 cb_idx;
	पूर्णांक		 मुक्तme;

	u32 reply_dma_low;
	u16 ioc_stat;

	/* non-TURBO reply!  Hmmm, something may be up...
	 *  Newest turbo reply mechanism; get address
	 *  via left shअगरt 1 (get rid of MPI_ADDRESS_REPLY_A_BIT)!
	 */

	/* Map DMA address of reply header to cpu address.
	 * pa is 32 bits - but the dma address may be 32 or 64 bits
	 * get offset based only only the low addresses
	 */

	reply_dma_low = (pa <<= 1);
	mr = (MPT_FRAME_HDR *)((u8 *)ioc->reply_frames +
			 (reply_dma_low - ioc->reply_frames_low_dma));

	req_idx = le16_to_cpu(mr->u.frame.hwhdr.msgctxu.fld.req_idx);
	cb_idx = mr->u.frame.hwhdr.msgctxu.fld.cb_idx;
	mf = MPT_INDEX_2_MFPTR(ioc, req_idx);

	dmfprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT "Got non-TURBO reply=%p req_idx=%x cb_idx=%x Function=%x\n",
			ioc->name, mr, req_idx, cb_idx, mr->u.hdr.Function));
	DBG_DUMP_REPLY_FRAME(ioc, (u32 *)mr);

	 /*  Check/log IOC log info
	 */
	ioc_stat = le16_to_cpu(mr->u.reply.IOCStatus);
	अगर (ioc_stat & MPI_IOCSTATUS_FLAG_LOG_INFO_AVAILABLE) अणु
		u32	 log_info = le32_to_cpu(mr->u.reply.IOCLogInfo);
		अगर (ioc->bus_type == FC)
			mpt_fc_log_info(ioc, log_info);
		अन्यथा अगर (ioc->bus_type == SPI)
			mpt_spi_log_info(ioc, log_info);
		अन्यथा अगर (ioc->bus_type == SAS)
			mpt_sas_log_info(ioc, log_info, cb_idx);
	पूर्ण

	अगर (ioc_stat & MPI_IOCSTATUS_MASK)
		mpt_iocstatus_info(ioc, (u32)ioc_stat, mf);

	/*  Check क्रम (valid) IO callback!  */
	अगर (!cb_idx || cb_idx >= MPT_MAX_PROTOCOL_DRIVERS ||
		MptCallbacks[cb_idx] == शून्य) अणु
		prपूर्णांकk(MYIOC_s_WARN_FMT "%s: Invalid cb_idx (%d)!\n",
				__func__, ioc->name, cb_idx);
		मुक्तme = 0;
		जाओ out;
	पूर्ण

	मुक्तme = MptCallbacks[cb_idx](ioc, mf, mr);

 out:
	/*  Flush (non-TURBO) reply with a WRITE!  */
	CHIPREG_WRITE32(&ioc->chip->ReplyFअगरo, pa);

	अगर (मुक्तme)
		mpt_मुक्त_msg_frame(ioc, mf);
	mb();
पूर्ण

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/**
 *	mpt_पूर्णांकerrupt - MPT adapter (IOC) specअगरic पूर्णांकerrupt handler.
 *	@irq: irq number (not used)
 *	@bus_id: bus identअगरier cookie == poपूर्णांकer to MPT_ADAPTER काष्ठाure
 *
 *	This routine is रेजिस्टरed via the request_irq() kernel API call,
 *	and handles all पूर्णांकerrupts generated from a specअगरic MPT adapter
 *	(also referred to as a IO Controller or IOC).
 *	This routine must clear the पूर्णांकerrupt from the adapter and करोes
 *	so by पढ़ोing the reply FIFO.  Multiple replies may be processed
 *	per single call to this routine.
 *
 *	This routine handles रेजिस्टर-level access of the adapter but
 *	dispatches (calls) a protocol-specअगरic callback routine to handle
 *	the protocol-specअगरic details of the MPT request completion.
 */
अटल irqवापस_t
mpt_पूर्णांकerrupt(पूर्णांक irq, व्योम *bus_id)
अणु
	MPT_ADAPTER *ioc = bus_id;
	u32 pa = CHIPREG_READ32_dmasync(&ioc->chip->ReplyFअगरo);

	अगर (pa == 0xFFFFFFFF)
		वापस IRQ_NONE;

	/*
	 *  Drain the reply FIFO!
	 */
	करो अणु
		अगर (pa & MPI_ADDRESS_REPLY_A_BIT)
			mpt_reply(ioc, pa);
		अन्यथा
			mpt_turbo_reply(ioc, pa);
		pa = CHIPREG_READ32_dmasync(&ioc->chip->ReplyFअगरo);
	पूर्ण जबतक (pa != 0xFFFFFFFF);

	वापस IRQ_HANDLED;
पूर्ण

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/**
 *	mptbase_reply - MPT base driver's callback routine
 *	@ioc: Poपूर्णांकer to MPT_ADAPTER काष्ठाure
 *	@req: Poपूर्णांकer to original MPT request frame
 *	@reply: Poपूर्णांकer to MPT reply frame (शून्य अगर TurboReply)
 *
 *	MPT base driver's callback routine; all base driver
 *	"internal" request/reply processing is routed here.
 *	Currently used क्रम EventNotअगरication and EventAck handling.
 *
 *	Returns 1 indicating original alloc'd request frame ptr
 *	should be मुक्तd, or 0 अगर it shouldn't.
 */
अटल पूर्णांक
mptbase_reply(MPT_ADAPTER *ioc, MPT_FRAME_HDR *req, MPT_FRAME_HDR *reply)
अणु
	EventNotअगरicationReply_t *pEventReply;
	u8 event;
	पूर्णांक evHandlers;
	पूर्णांक मुक्तreq = 1;

	चयन (reply->u.hdr.Function) अणु
	हाल MPI_FUNCTION_EVENT_NOTIFICATION:
		pEventReply = (EventNotअगरicationReply_t *)reply;
		evHandlers = 0;
		ProcessEventNotअगरication(ioc, pEventReply, &evHandlers);
		event = le32_to_cpu(pEventReply->Event) & 0xFF;
		अगर (pEventReply->MsgFlags & MPI_MSGFLAGS_CONTINUATION_REPLY)
			मुक्तreq = 0;
		अगर (event != MPI_EVENT_EVENT_CHANGE)
			अवरोध;
		fallthrough;
	हाल MPI_FUNCTION_CONFIG:
	हाल MPI_FUNCTION_SAS_IO_UNIT_CONTROL:
		ioc->mptbase_cmds.status |= MPT_MGMT_STATUS_COMMAND_GOOD;
		ioc->mptbase_cmds.status |= MPT_MGMT_STATUS_RF_VALID;
		स_नकल(ioc->mptbase_cmds.reply, reply,
		    min(MPT_DEFAULT_FRAME_SIZE,
			4 * reply->u.reply.MsgLength));
		अगर (ioc->mptbase_cmds.status & MPT_MGMT_STATUS_PENDING) अणु
			ioc->mptbase_cmds.status &= ~MPT_MGMT_STATUS_PENDING;
			complete(&ioc->mptbase_cmds.करोne);
		पूर्ण अन्यथा
			मुक्तreq = 0;
		अगर (ioc->mptbase_cmds.status & MPT_MGMT_STATUS_FREE_MF)
			मुक्तreq = 1;
		अवरोध;
	हाल MPI_FUNCTION_EVENT_ACK:
		devtverboseprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT
		    "EventAck reply received\n", ioc->name));
		अवरोध;
	शेष:
		prपूर्णांकk(MYIOC_s_ERR_FMT
		    "Unexpected msg function (=%02Xh) reply received!\n",
		    ioc->name, reply->u.hdr.Function);
		अवरोध;
	पूर्ण

	/*
	 *	Conditionally tell caller to मुक्त the original
	 *	EventNotअगरication/EventAck/unexpected request frame!
	 */
	वापस मुक्तreq;
पूर्ण

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/**
 *	mpt_रेजिस्टर - Register protocol-specअगरic मुख्य callback handler.
 *	@cbfunc: callback function poपूर्णांकer
 *	@dclass: Protocol driver's class (%MPT_DRIVER_CLASS क्रमागत value)
 *	@func_name: call function's name
 *
 *	This routine is called by a protocol-specअगरic driver (SCSI host,
 *	LAN, SCSI target) to रेजिस्टर its reply callback routine.  Each
 *	protocol-specअगरic driver must करो this beक्रमe it will be able to
 *	use any IOC resources, such as obtaining request frames.
 *
 *	NOTES: The SCSI protocol driver currently calls this routine thrice
 *	in order to रेजिस्टर separate callbacks; one क्रम "normal" SCSI IO;
 *	one क्रम MptScsiTaskMgmt requests; one क्रम Scan/DV requests.
 *
 *	Returns u8 valued "handle" in the range (and S.O.D. order)
 *	अणुN,...,7,6,5,...,1पूर्ण अगर successful.
 *	A वापस value of MPT_MAX_PROTOCOL_DRIVERS (including zero!) should be
 *	considered an error by the caller.
 */
u8
mpt_रेजिस्टर(MPT_CALLBACK cbfunc, MPT_DRIVER_CLASS dclass, अक्षर *func_name)
अणु
	u8 cb_idx;
	last_drv_idx = MPT_MAX_PROTOCOL_DRIVERS;

	/*
	 *  Search क्रम empty callback slot in this order: अणुN,...,7,6,5,...,1पूर्ण
	 *  (slot/handle 0 is reserved!)
	 */
	क्रम (cb_idx = MPT_MAX_PROTOCOL_DRIVERS-1; cb_idx; cb_idx--) अणु
		अगर (MptCallbacks[cb_idx] == शून्य) अणु
			MptCallbacks[cb_idx] = cbfunc;
			MptDriverClass[cb_idx] = dclass;
			MptEvHandlers[cb_idx] = शून्य;
			last_drv_idx = cb_idx;
			strlcpy(MptCallbacksName[cb_idx], func_name,
				MPT_MAX_CALLBACKNAME_LEN+1);
			अवरोध;
		पूर्ण
	पूर्ण

	वापस last_drv_idx;
पूर्ण

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/**
 *	mpt_deरेजिस्टर - Deरेजिस्टर a protocol drivers resources.
 *	@cb_idx: previously रेजिस्टरed callback handle
 *
 *	Each protocol-specअगरic driver should call this routine when its
 *	module is unloaded.
 */
व्योम
mpt_deरेजिस्टर(u8 cb_idx)
अणु
	अगर (cb_idx && (cb_idx < MPT_MAX_PROTOCOL_DRIVERS)) अणु
		MptCallbacks[cb_idx] = शून्य;
		MptDriverClass[cb_idx] = MPTUNKNOWN_DRIVER;
		MptEvHandlers[cb_idx] = शून्य;

		last_drv_idx++;
	पूर्ण
पूर्ण

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/**
 *	mpt_event_रेजिस्टर - Register protocol-specअगरic event callback handler.
 *	@cb_idx: previously रेजिस्टरed (via mpt_रेजिस्टर) callback handle
 *	@ev_cbfunc: callback function
 *
 *	This routine can be called by one or more protocol-specअगरic drivers
 *	अगर/when they choose to be notअगरied of MPT events.
 *
 *	Returns 0 क्रम success.
 */
पूर्णांक
mpt_event_रेजिस्टर(u8 cb_idx, MPT_EVHANDLER ev_cbfunc)
अणु
	अगर (!cb_idx || cb_idx >= MPT_MAX_PROTOCOL_DRIVERS)
		वापस -1;

	MptEvHandlers[cb_idx] = ev_cbfunc;
	वापस 0;
पूर्ण

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/**
 *	mpt_event_deरेजिस्टर - Deरेजिस्टर protocol-specअगरic event callback handler
 *	@cb_idx: previously रेजिस्टरed callback handle
 *
 *	Each protocol-specअगरic driver should call this routine
 *	when it करोes not (or can no दीर्घer) handle events,
 *	or when its module is unloaded.
 */
व्योम
mpt_event_deरेजिस्टर(u8 cb_idx)
अणु
	अगर (!cb_idx || cb_idx >= MPT_MAX_PROTOCOL_DRIVERS)
		वापस;

	MptEvHandlers[cb_idx] = शून्य;
पूर्ण

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/**
 *	mpt_reset_रेजिस्टर - Register protocol-specअगरic IOC reset handler.
 *	@cb_idx: previously रेजिस्टरed (via mpt_रेजिस्टर) callback handle
 *	@reset_func: reset function
 *
 *	This routine can be called by one or more protocol-specअगरic drivers
 *	अगर/when they choose to be notअगरied of IOC resets.
 *
 *	Returns 0 क्रम success.
 */
पूर्णांक
mpt_reset_रेजिस्टर(u8 cb_idx, MPT_RESETHANDLER reset_func)
अणु
	अगर (!cb_idx || cb_idx >= MPT_MAX_PROTOCOL_DRIVERS)
		वापस -1;

	MptResetHandlers[cb_idx] = reset_func;
	वापस 0;
पूर्ण

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/**
 *	mpt_reset_deरेजिस्टर - Deरेजिस्टर protocol-specअगरic IOC reset handler.
 *	@cb_idx: previously रेजिस्टरed callback handle
 *
 *	Each protocol-specअगरic driver should call this routine
 *	when it करोes not (or can no दीर्घer) handle IOC reset handling,
 *	or when its module is unloaded.
 */
व्योम
mpt_reset_deरेजिस्टर(u8 cb_idx)
अणु
	अगर (!cb_idx || cb_idx >= MPT_MAX_PROTOCOL_DRIVERS)
		वापस;

	MptResetHandlers[cb_idx] = शून्य;
पूर्ण

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/**
 *	mpt_device_driver_रेजिस्टर - Register device driver hooks
 *	@dd_cbfunc: driver callbacks काष्ठा
 *	@cb_idx: MPT protocol driver index
 */
पूर्णांक
mpt_device_driver_रेजिस्टर(काष्ठा mpt_pci_driver * dd_cbfunc, u8 cb_idx)
अणु
	MPT_ADAPTER	*ioc;
	स्थिर काष्ठा pci_device_id *id;

	अगर (!cb_idx || cb_idx >= MPT_MAX_PROTOCOL_DRIVERS)
		वापस -EINVAL;

	MptDeviceDriverHandlers[cb_idx] = dd_cbfunc;

	/* call per pci device probe entry poपूर्णांक */
	list_क्रम_each_entry(ioc, &ioc_list, list) अणु
		id = ioc->pcidev->driver ?
		    ioc->pcidev->driver->id_table : शून्य;
		अगर (dd_cbfunc->probe)
			dd_cbfunc->probe(ioc->pcidev, id);
	 पूर्ण

	वापस 0;
पूर्ण

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/**
 *	mpt_device_driver_deरेजिस्टर - DeRegister device driver hooks
 *	@cb_idx: MPT protocol driver index
 */
व्योम
mpt_device_driver_deरेजिस्टर(u8 cb_idx)
अणु
	काष्ठा mpt_pci_driver *dd_cbfunc;
	MPT_ADAPTER	*ioc;

	अगर (!cb_idx || cb_idx >= MPT_MAX_PROTOCOL_DRIVERS)
		वापस;

	dd_cbfunc = MptDeviceDriverHandlers[cb_idx];

	list_क्रम_each_entry(ioc, &ioc_list, list) अणु
		अगर (dd_cbfunc->हटाओ)
			dd_cbfunc->हटाओ(ioc->pcidev);
	पूर्ण

	MptDeviceDriverHandlers[cb_idx] = शून्य;
पूर्ण


/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/**
 *	mpt_get_msg_frame - Obtain an MPT request frame from the pool
 *	@cb_idx: Handle of रेजिस्टरed MPT protocol driver
 *	@ioc: Poपूर्णांकer to MPT adapter काष्ठाure
 *
 *	Obtain an MPT request frame from the pool (of 1024) that are
 *	allocated per MPT adapter.
 *
 *	Returns poपूर्णांकer to a MPT request frame or %शून्य अगर none are available
 *	or IOC is not active.
 */
MPT_FRAME_HDR*
mpt_get_msg_frame(u8 cb_idx, MPT_ADAPTER *ioc)
अणु
	MPT_FRAME_HDR *mf;
	अचिन्हित दीर्घ flags;
	u16	 req_idx;	/* Request index */

	/* validate handle and ioc identअगरier */

#अगर_घोषित MFCNT
	अगर (!ioc->active)
		prपूर्णांकk(MYIOC_s_WARN_FMT "IOC Not Active! mpt_get_msg_frame "
		    "returning NULL!\n", ioc->name);
#पूर्ण_अगर

	/* If पूर्णांकerrupts are not attached, करो not वापस a request frame */
	अगर (!ioc->active)
		वापस शून्य;

	spin_lock_irqsave(&ioc->FreeQlock, flags);
	अगर (!list_empty(&ioc->FreeQ)) अणु
		पूर्णांक req_offset;

		mf = list_entry(ioc->FreeQ.next, MPT_FRAME_HDR,
				u.frame.linkage.list);
		list_del(&mf->u.frame.linkage.list);
		mf->u.frame.linkage.arg1 = 0;
		mf->u.frame.hwhdr.msgctxu.fld.cb_idx = cb_idx;	/* byte */
		req_offset = (u8 *)mf - (u8 *)ioc->req_frames;
								/* u16! */
		req_idx = req_offset / ioc->req_sz;
		mf->u.frame.hwhdr.msgctxu.fld.req_idx = cpu_to_le16(req_idx);
		mf->u.frame.hwhdr.msgctxu.fld.rsvd = 0;
		/* Default, will be changed अगर necessary in SG generation */
		ioc->RequestNB[req_idx] = ioc->NB_क्रम_64_byte_frame;
#अगर_घोषित MFCNT
		ioc->mfcnt++;
#पूर्ण_अगर
	पूर्ण
	अन्यथा
		mf = शून्य;
	spin_unlock_irqrestore(&ioc->FreeQlock, flags);

#अगर_घोषित MFCNT
	अगर (mf == शून्य)
		prपूर्णांकk(MYIOC_s_WARN_FMT "IOC Active. No free Msg Frames! "
		    "Count 0x%x Max 0x%x\n", ioc->name, ioc->mfcnt,
		    ioc->req_depth);
	mfcounter++;
	अगर (mfcounter == PRINT_MF_COUNT)
		prपूर्णांकk(MYIOC_s_INFO_FMT "MF Count 0x%x Max 0x%x \n", ioc->name,
		    ioc->mfcnt, ioc->req_depth);
#पूर्ण_अगर

	dmfprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT "mpt_get_msg_frame(%d,%d), got mf=%p\n",
	    ioc->name, cb_idx, ioc->id, mf));
	वापस mf;
पूर्ण

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/**
 *	mpt_put_msg_frame - Send a protocol-specअगरic MPT request frame to an IOC
 *	@cb_idx: Handle of रेजिस्टरed MPT protocol driver
 *	@ioc: Poपूर्णांकer to MPT adapter काष्ठाure
 *	@mf: Poपूर्णांकer to MPT request frame
 *
 *	This routine posts an MPT request frame to the request post FIFO of a
 *	specअगरic MPT adapter.
 */
व्योम
mpt_put_msg_frame(u8 cb_idx, MPT_ADAPTER *ioc, MPT_FRAME_HDR *mf)
अणु
	u32 mf_dma_addr;
	पूर्णांक req_offset;
	u16 req_idx;	/* Request index */

	/* ensure values are reset properly! */
	mf->u.frame.hwhdr.msgctxu.fld.cb_idx = cb_idx;		/* byte */
	req_offset = (u8 *)mf - (u8 *)ioc->req_frames;
								/* u16! */
	req_idx = req_offset / ioc->req_sz;
	mf->u.frame.hwhdr.msgctxu.fld.req_idx = cpu_to_le16(req_idx);
	mf->u.frame.hwhdr.msgctxu.fld.rsvd = 0;

	DBG_DUMP_PUT_MSG_FRAME(ioc, (u32 *)mf);

	mf_dma_addr = (ioc->req_frames_low_dma + req_offset) | ioc->RequestNB[req_idx];
	dsgprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT "mf_dma_addr=%x req_idx=%d "
	    "RequestNB=%x\n", ioc->name, mf_dma_addr, req_idx,
	    ioc->RequestNB[req_idx]));
	CHIPREG_WRITE32(&ioc->chip->RequestFअगरo, mf_dma_addr);
पूर्ण

/**
 *	mpt_put_msg_frame_hi_pri - Send a hi-pri protocol-specअगरic MPT request frame
 *	@cb_idx: Handle of रेजिस्टरed MPT protocol driver
 *	@ioc: Poपूर्णांकer to MPT adapter काष्ठाure
 *	@mf: Poपूर्णांकer to MPT request frame
 *
 *	Send a protocol-specअगरic MPT request frame to an IOC using
 *	hi-priority request queue.
 *
 *	This routine posts an MPT request frame to the request post FIFO of a
 *	specअगरic MPT adapter.
 **/
व्योम
mpt_put_msg_frame_hi_pri(u8 cb_idx, MPT_ADAPTER *ioc, MPT_FRAME_HDR *mf)
अणु
	u32 mf_dma_addr;
	पूर्णांक req_offset;
	u16 req_idx;	/* Request index */

	/* ensure values are reset properly! */
	mf->u.frame.hwhdr.msgctxu.fld.cb_idx = cb_idx;
	req_offset = (u8 *)mf - (u8 *)ioc->req_frames;
	req_idx = req_offset / ioc->req_sz;
	mf->u.frame.hwhdr.msgctxu.fld.req_idx = cpu_to_le16(req_idx);
	mf->u.frame.hwhdr.msgctxu.fld.rsvd = 0;

	DBG_DUMP_PUT_MSG_FRAME(ioc, (u32 *)mf);

	mf_dma_addr = (ioc->req_frames_low_dma + req_offset);
	dsgprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT "mf_dma_addr=%x req_idx=%d\n",
		ioc->name, mf_dma_addr, req_idx));
	CHIPREG_WRITE32(&ioc->chip->RequestHiPriFअगरo, mf_dma_addr);
पूर्ण

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/**
 *	mpt_मुक्त_msg_frame - Place MPT request frame back on FreeQ.
 *	@ioc: Poपूर्णांकer to MPT adapter काष्ठाure
 *	@mf: Poपूर्णांकer to MPT request frame
 *
 *	This routine places a MPT request frame back on the MPT adapter's
 *	FreeQ.
 */
व्योम
mpt_मुक्त_msg_frame(MPT_ADAPTER *ioc, MPT_FRAME_HDR *mf)
अणु
	अचिन्हित दीर्घ flags;

	/*  Put Request back on FreeQ!  */
	spin_lock_irqsave(&ioc->FreeQlock, flags);
	अगर (cpu_to_le32(mf->u.frame.linkage.arg1) == 0xdeadbeaf)
		जाओ out;
	/* signature to know अगर this mf is मुक्तd */
	mf->u.frame.linkage.arg1 = cpu_to_le32(0xdeadbeaf);
	list_add(&mf->u.frame.linkage.list, &ioc->FreeQ);
#अगर_घोषित MFCNT
	ioc->mfcnt--;
#पूर्ण_अगर
 out:
	spin_unlock_irqrestore(&ioc->FreeQlock, flags);
पूर्ण

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/**
 *	mpt_add_sge - Place a simple 32 bit SGE at address pAddr.
 *	@pAddr: भव address क्रम SGE
 *	@flagslength: SGE flags and data transfer length
 *	@dma_addr: Physical address
 *
 *	This routine places a MPT request frame back on the MPT adapter's
 *	FreeQ.
 */
अटल व्योम
mpt_add_sge(व्योम *pAddr, u32 flagslength, dma_addr_t dma_addr)
अणु
	SGESimple32_t *pSge = (SGESimple32_t *) pAddr;
	pSge->FlagsLength = cpu_to_le32(flagslength);
	pSge->Address = cpu_to_le32(dma_addr);
पूर्ण

/**
 *	mpt_add_sge_64bit - Place a simple 64 bit SGE at address pAddr.
 *	@pAddr: भव address क्रम SGE
 *	@flagslength: SGE flags and data transfer length
 *	@dma_addr: Physical address
 *
 *	This routine places a MPT request frame back on the MPT adapter's
 *	FreeQ.
 **/
अटल व्योम
mpt_add_sge_64bit(व्योम *pAddr, u32 flagslength, dma_addr_t dma_addr)
अणु
	SGESimple64_t *pSge = (SGESimple64_t *) pAddr;
	pSge->Address.Low = cpu_to_le32
			(lower_32_bits(dma_addr));
	pSge->Address.High = cpu_to_le32
			(upper_32_bits(dma_addr));
	pSge->FlagsLength = cpu_to_le32
			((flagslength | MPT_SGE_FLAGS_64_BIT_ADDRESSING));
पूर्ण

/**
 *	mpt_add_sge_64bit_1078 - Place a simple 64 bit SGE at address pAddr (1078 workaround).
 *	@pAddr: भव address क्रम SGE
 *	@flagslength: SGE flags and data transfer length
 *	@dma_addr: Physical address
 *
 *	This routine places a MPT request frame back on the MPT adapter's
 *	FreeQ.
 **/
अटल व्योम
mpt_add_sge_64bit_1078(व्योम *pAddr, u32 flagslength, dma_addr_t dma_addr)
अणु
	SGESimple64_t *pSge = (SGESimple64_t *) pAddr;
	u32 पंचांगp;

	pSge->Address.Low = cpu_to_le32
			(lower_32_bits(dma_addr));
	पंचांगp = (u32)(upper_32_bits(dma_addr));

	/*
	 * 1078 errata workaround क्रम the 36GB limitation
	 */
	अगर ((((u64)dma_addr + MPI_SGE_LENGTH(flagslength)) >> 32)  == 9) अणु
		flagslength |=
		    MPI_SGE_SET_FLAGS(MPI_SGE_FLAGS_LOCAL_ADDRESS);
		पंचांगp |= (1<<31);
		अगर (mpt_debug_level & MPT_DEBUG_36GB_MEM)
			prपूर्णांकk(KERN_DEBUG "1078 P0M2 addressing for "
			    "addr = 0x%llx len = %d\n",
			    (अचिन्हित दीर्घ दीर्घ)dma_addr,
			    MPI_SGE_LENGTH(flagslength));
	पूर्ण

	pSge->Address.High = cpu_to_le32(पंचांगp);
	pSge->FlagsLength = cpu_to_le32(
		(flagslength | MPT_SGE_FLAGS_64_BIT_ADDRESSING));
पूर्ण

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/**
 *	mpt_add_chain - Place a 32 bit chain SGE at address pAddr.
 *	@pAddr: भव address क्रम SGE
 *	@next: nextChainOffset value (u32's)
 *	@length: length of next SGL segment
 *	@dma_addr: Physical address
 *
 */
अटल व्योम
mpt_add_chain(व्योम *pAddr, u8 next, u16 length, dma_addr_t dma_addr)
अणु
	SGEChain32_t *pChain = (SGEChain32_t *) pAddr;

	pChain->Length = cpu_to_le16(length);
	pChain->Flags = MPI_SGE_FLAGS_CHAIN_ELEMENT;
	pChain->NextChainOffset = next;
	pChain->Address = cpu_to_le32(dma_addr);
पूर्ण

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/**
 *	mpt_add_chain_64bit - Place a 64 bit chain SGE at address pAddr.
 *	@pAddr: भव address क्रम SGE
 *	@next: nextChainOffset value (u32's)
 *	@length: length of next SGL segment
 *	@dma_addr: Physical address
 *
 */
अटल व्योम
mpt_add_chain_64bit(व्योम *pAddr, u8 next, u16 length, dma_addr_t dma_addr)
अणु
	SGEChain64_t *pChain = (SGEChain64_t *) pAddr;
	u32 पंचांगp = dma_addr & 0xFFFFFFFF;

	pChain->Length = cpu_to_le16(length);
	pChain->Flags = (MPI_SGE_FLAGS_CHAIN_ELEMENT |
			 MPI_SGE_FLAGS_64_BIT_ADDRESSING);

	pChain->NextChainOffset = next;

	pChain->Address.Low = cpu_to_le32(पंचांगp);
	पंचांगp = (u32)(upper_32_bits(dma_addr));
	pChain->Address.High = cpu_to_le32(पंचांगp);
पूर्ण

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/**
 *	mpt_send_handshake_request - Send MPT request via करोorbell handshake method.
 *	@cb_idx: Handle of रेजिस्टरed MPT protocol driver
 *	@ioc: Poपूर्णांकer to MPT adapter काष्ठाure
 *	@reqBytes: Size of the request in bytes
 *	@req: Poपूर्णांकer to MPT request frame
 *	@sleepFlag: Use schedule अगर CAN_SLEEP अन्यथा use udelay.
 *
 *	This routine is used exclusively to send MptScsiTaskMgmt
 *	requests since they are required to be sent via करोorbell handshake.
 *
 *	NOTE: It is the callers responsibility to byte-swap fields in the
 *	request which are greater than 1 byte in size.
 *
 *	Returns 0 क्रम success, non-zero क्रम failure.
 */
पूर्णांक
mpt_send_handshake_request(u8 cb_idx, MPT_ADAPTER *ioc, पूर्णांक reqBytes, u32 *req, पूर्णांक sleepFlag)
अणु
	पूर्णांक	r = 0;
	u8	*req_as_bytes;
	पूर्णांक	 ii;

	/* State is known to be good upon entering
	 * this function so issue the bus reset
	 * request.
	 */

	/*
	 * Emulate what mpt_put_msg_frame() करोes /wrt to sanity
	 * setting cb_idx/req_idx.  But ONLY अगर this request
	 * is in proper (pre-alloc'd) request buffer range...
	 */
	ii = MFPTR_2_MPT_INDEX(ioc,(MPT_FRAME_HDR*)req);
	अगर (reqBytes >= 12 && ii >= 0 && ii < ioc->req_depth) अणु
		MPT_FRAME_HDR *mf = (MPT_FRAME_HDR*)req;
		mf->u.frame.hwhdr.msgctxu.fld.req_idx = cpu_to_le16(ii);
		mf->u.frame.hwhdr.msgctxu.fld.cb_idx = cb_idx;
	पूर्ण

	/* Make sure there are no करोorbells */
	CHIPREG_WRITE32(&ioc->chip->IntStatus, 0);

	CHIPREG_WRITE32(&ioc->chip->Doorbell,
			((MPI_FUNCTION_HANDSHAKE<<MPI_DOORBELL_FUNCTION_SHIFT) |
			 ((reqBytes/4)<<MPI_DOORBELL_ADD_DWORDS_SHIFT)));

	/* Wait क्रम IOC करोorbell पूर्णांक */
	अगर ((ii = WaitForDoorbellInt(ioc, 5, sleepFlag)) < 0) अणु
		वापस ii;
	पूर्ण

	/* Read करोorbell and check क्रम active bit */
	अगर (!(CHIPREG_READ32(&ioc->chip->Doorbell) & MPI_DOORBELL_ACTIVE))
		वापस -5;

	dhsprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT "mpt_send_handshake_request start, WaitCnt=%d\n",
		ioc->name, ii));

	CHIPREG_WRITE32(&ioc->chip->IntStatus, 0);

	अगर ((r = WaitForDoorbellAck(ioc, 5, sleepFlag)) < 0) अणु
		वापस -2;
	पूर्ण

	/* Send request via करोorbell handshake */
	req_as_bytes = (u8 *) req;
	क्रम (ii = 0; ii < reqBytes/4; ii++) अणु
		u32 word;

		word = ((req_as_bytes[(ii*4) + 0] <<  0) |
			(req_as_bytes[(ii*4) + 1] <<  8) |
			(req_as_bytes[(ii*4) + 2] << 16) |
			(req_as_bytes[(ii*4) + 3] << 24));
		CHIPREG_WRITE32(&ioc->chip->Doorbell, word);
		अगर ((r = WaitForDoorbellAck(ioc, 5, sleepFlag)) < 0) अणु
			r = -3;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (r >= 0 && WaitForDoorbellInt(ioc, 10, sleepFlag) >= 0)
		r = 0;
	अन्यथा
		r = -4;

	/* Make sure there are no करोorbells */
	CHIPREG_WRITE32(&ioc->chip->IntStatus, 0);

	वापस r;
पूर्ण

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/**
 * mpt_host_page_access_control - control the IOC's Host Page Buffer access
 * @ioc: Poपूर्णांकer to MPT adapter काष्ठाure
 * @access_control_value: define bits below
 * @sleepFlag: Specअगरies whether the process can sleep
 *
 * Provides mechanism क्रम the host driver to control the IOC's
 * Host Page Buffer access.
 *
 * Access Control Value - bits[15:12]
 * 0h Reserved
 * 1h Enable Access अणु MPI_DB_HPBAC_ENABLE_ACCESS पूर्ण
 * 2h Disable Access अणु MPI_DB_HPBAC_DISABLE_ACCESS पूर्ण
 * 3h Free Buffer अणु MPI_DB_HPBAC_FREE_BUFFER पूर्ण
 *
 * Returns 0 क्रम success, non-zero क्रम failure.
 */

अटल पूर्णांक
mpt_host_page_access_control(MPT_ADAPTER *ioc, u8 access_control_value, पूर्णांक sleepFlag)
अणु
	पूर्णांक	 r = 0;

	/* वापस अगर in use */
	अगर (CHIPREG_READ32(&ioc->chip->Doorbell)
	    & MPI_DOORBELL_ACTIVE)
	    वापस -1;

	CHIPREG_WRITE32(&ioc->chip->IntStatus, 0);

	CHIPREG_WRITE32(&ioc->chip->Doorbell,
		((MPI_FUNCTION_HOST_PAGEBUF_ACCESS_CONTROL
		 <<MPI_DOORBELL_FUNCTION_SHIFT) |
		 (access_control_value<<12)));

	/* Wait क्रम IOC to clear Doorbell Status bit */
	अगर ((r = WaitForDoorbellAck(ioc, 5, sleepFlag)) < 0) अणु
		वापस -2;
	पूर्णअन्यथा
		वापस 0;
पूर्ण

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/**
 *	mpt_host_page_alloc - allocate प्रणाली memory क्रम the fw
 *	@ioc: Poपूर्णांकer to poपूर्णांकer to IOC adapter
 *	@ioc_init: Poपूर्णांकer to ioc init config page
 *
 *	If we alपढ़ोy allocated memory in past, then resend the same poपूर्णांकer.
 *	Returns 0 क्रम success, non-zero क्रम failure.
 */
अटल पूर्णांक
mpt_host_page_alloc(MPT_ADAPTER *ioc, pIOCInit_t ioc_init)
अणु
	अक्षर	*psge;
	पूर्णांक	flags_length;
	u32	host_page_buffer_sz=0;

	अगर(!ioc->HostPageBuffer) अणु

		host_page_buffer_sz =
		    le32_to_cpu(ioc->facts.HostPageBufferSGE.FlagsLength) & 0xFFFFFF;

		अगर(!host_page_buffer_sz)
			वापस 0; /* fw करोesn't need any host buffers */

		/* spin till we get enough memory */
		जबतक (host_page_buffer_sz > 0) अणु
			ioc->HostPageBuffer =
				dma_alloc_coherent(&ioc->pcidev->dev,
						host_page_buffer_sz,
						&ioc->HostPageBuffer_dma,
						GFP_KERNEL);
			अगर (ioc->HostPageBuffer) अणु
				dinitprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT
				    "host_page_buffer @ %p, dma @ %x, sz=%d bytes\n",
				    ioc->name, ioc->HostPageBuffer,
				    (u32)ioc->HostPageBuffer_dma,
				    host_page_buffer_sz));
				ioc->alloc_total += host_page_buffer_sz;
				ioc->HostPageBuffer_sz = host_page_buffer_sz;
				अवरोध;
			पूर्ण

			host_page_buffer_sz -= (4*1024);
		पूर्ण
	पूर्ण

	अगर(!ioc->HostPageBuffer) अणु
		prपूर्णांकk(MYIOC_s_ERR_FMT
		    "Failed to alloc memory for host_page_buffer!\n",
		    ioc->name);
		वापस -999;
	पूर्ण

	psge = (अक्षर *)&ioc_init->HostPageBufferSGE;
	flags_length = MPI_SGE_FLAGS_SIMPLE_ELEMENT |
	    MPI_SGE_FLAGS_SYSTEM_ADDRESS |
	    MPI_SGE_FLAGS_HOST_TO_IOC |
	    MPI_SGE_FLAGS_END_OF_BUFFER;
	flags_length = flags_length << MPI_SGE_FLAGS_SHIFT;
	flags_length |= ioc->HostPageBuffer_sz;
	ioc->add_sge(psge, flags_length, ioc->HostPageBuffer_dma);
	ioc->facts.HostPageBufferSGE = ioc_init->HostPageBufferSGE;

	वापस 0;
पूर्ण

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/**
 *	mpt_verअगरy_adapter - Given IOC identअगरier, set poपूर्णांकer to its adapter काष्ठाure.
 *	@iocid: IOC unique identअगरier (पूर्णांकeger)
 *	@iocpp: Poपूर्णांकer to poपूर्णांकer to IOC adapter
 *
 *	Given a unique IOC identअगरier, set poपूर्णांकer to the associated MPT
 *	adapter काष्ठाure.
 *
 *	Returns iocid and sets iocpp अगर iocid is found.
 *	Returns -1 अगर iocid is not found.
 */
पूर्णांक
mpt_verअगरy_adapter(पूर्णांक iocid, MPT_ADAPTER **iocpp)
अणु
	MPT_ADAPTER *ioc;

	list_क्रम_each_entry(ioc,&ioc_list,list) अणु
		अगर (ioc->id == iocid) अणु
			*iocpp =ioc;
			वापस iocid;
		पूर्ण
	पूर्ण

	*iocpp = शून्य;
	वापस -1;
पूर्ण

/**
 *	mpt_get_product_name - वापसs product string
 *	@venकरोr: pci venकरोr id
 *	@device: pci device id
 *	@revision: pci revision id
 *
 *	Returns product string displayed when driver loads,
 *	in /proc/mpt/summary and /sysfs/class/scsi_host/host<X>/version_product
 *
 **/
अटल स्थिर अक्षर*
mpt_get_product_name(u16 venकरोr, u16 device, u8 revision)
अणु
	अक्षर *product_str = शून्य;

	अगर (venकरोr == PCI_VENDOR_ID_BROCADE) अणु
		चयन (device)
		अणु
		हाल MPI_MANUFACTPAGE_DEVICEID_FC949E:
			चयन (revision)
			अणु
			हाल 0x00:
				product_str = "BRE040 A0";
				अवरोध;
			हाल 0x01:
				product_str = "BRE040 A1";
				अवरोध;
			शेष:
				product_str = "BRE040";
				अवरोध;
			पूर्ण
			अवरोध;
		पूर्ण
		जाओ out;
	पूर्ण

	चयन (device)
	अणु
	हाल MPI_MANUFACTPAGE_DEVICEID_FC909:
		product_str = "LSIFC909 B1";
		अवरोध;
	हाल MPI_MANUFACTPAGE_DEVICEID_FC919:
		product_str = "LSIFC919 B0";
		अवरोध;
	हाल MPI_MANUFACTPAGE_DEVICEID_FC929:
		product_str = "LSIFC929 B0";
		अवरोध;
	हाल MPI_MANUFACTPAGE_DEVICEID_FC919X:
		अगर (revision < 0x80)
			product_str = "LSIFC919X A0";
		अन्यथा
			product_str = "LSIFC919XL A1";
		अवरोध;
	हाल MPI_MANUFACTPAGE_DEVICEID_FC929X:
		अगर (revision < 0x80)
			product_str = "LSIFC929X A0";
		अन्यथा
			product_str = "LSIFC929XL A1";
		अवरोध;
	हाल MPI_MANUFACTPAGE_DEVICEID_FC939X:
		product_str = "LSIFC939X A1";
		अवरोध;
	हाल MPI_MANUFACTPAGE_DEVICEID_FC949X:
		product_str = "LSIFC949X A1";
		अवरोध;
	हाल MPI_MANUFACTPAGE_DEVICEID_FC949E:
		चयन (revision)
		अणु
		हाल 0x00:
			product_str = "LSIFC949E A0";
			अवरोध;
		हाल 0x01:
			product_str = "LSIFC949E A1";
			अवरोध;
		शेष:
			product_str = "LSIFC949E";
			अवरोध;
		पूर्ण
		अवरोध;
	हाल MPI_MANUFACTPAGE_DEVID_53C1030:
		चयन (revision)
		अणु
		हाल 0x00:
			product_str = "LSI53C1030 A0";
			अवरोध;
		हाल 0x01:
			product_str = "LSI53C1030 B0";
			अवरोध;
		हाल 0x03:
			product_str = "LSI53C1030 B1";
			अवरोध;
		हाल 0x07:
			product_str = "LSI53C1030 B2";
			अवरोध;
		हाल 0x08:
			product_str = "LSI53C1030 C0";
			अवरोध;
		हाल 0x80:
			product_str = "LSI53C1030T A0";
			अवरोध;
		हाल 0x83:
			product_str = "LSI53C1030T A2";
			अवरोध;
		हाल 0x87:
			product_str = "LSI53C1030T A3";
			अवरोध;
		हाल 0xc1:
			product_str = "LSI53C1020A A1";
			अवरोध;
		शेष:
			product_str = "LSI53C1030";
			अवरोध;
		पूर्ण
		अवरोध;
	हाल MPI_MANUFACTPAGE_DEVID_1030_53C1035:
		चयन (revision)
		अणु
		हाल 0x03:
			product_str = "LSI53C1035 A2";
			अवरोध;
		हाल 0x04:
			product_str = "LSI53C1035 B0";
			अवरोध;
		शेष:
			product_str = "LSI53C1035";
			अवरोध;
		पूर्ण
		अवरोध;
	हाल MPI_MANUFACTPAGE_DEVID_SAS1064:
		चयन (revision)
		अणु
		हाल 0x00:
			product_str = "LSISAS1064 A1";
			अवरोध;
		हाल 0x01:
			product_str = "LSISAS1064 A2";
			अवरोध;
		हाल 0x02:
			product_str = "LSISAS1064 A3";
			अवरोध;
		हाल 0x03:
			product_str = "LSISAS1064 A4";
			अवरोध;
		शेष:
			product_str = "LSISAS1064";
			अवरोध;
		पूर्ण
		अवरोध;
	हाल MPI_MANUFACTPAGE_DEVID_SAS1064E:
		चयन (revision)
		अणु
		हाल 0x00:
			product_str = "LSISAS1064E A0";
			अवरोध;
		हाल 0x01:
			product_str = "LSISAS1064E B0";
			अवरोध;
		हाल 0x02:
			product_str = "LSISAS1064E B1";
			अवरोध;
		हाल 0x04:
			product_str = "LSISAS1064E B2";
			अवरोध;
		हाल 0x08:
			product_str = "LSISAS1064E B3";
			अवरोध;
		शेष:
			product_str = "LSISAS1064E";
			अवरोध;
		पूर्ण
		अवरोध;
	हाल MPI_MANUFACTPAGE_DEVID_SAS1068:
		चयन (revision)
		अणु
		हाल 0x00:
			product_str = "LSISAS1068 A0";
			अवरोध;
		हाल 0x01:
			product_str = "LSISAS1068 B0";
			अवरोध;
		हाल 0x02:
			product_str = "LSISAS1068 B1";
			अवरोध;
		शेष:
			product_str = "LSISAS1068";
			अवरोध;
		पूर्ण
		अवरोध;
	हाल MPI_MANUFACTPAGE_DEVID_SAS1068E:
		चयन (revision)
		अणु
		हाल 0x00:
			product_str = "LSISAS1068E A0";
			अवरोध;
		हाल 0x01:
			product_str = "LSISAS1068E B0";
			अवरोध;
		हाल 0x02:
			product_str = "LSISAS1068E B1";
			अवरोध;
		हाल 0x04:
			product_str = "LSISAS1068E B2";
			अवरोध;
		हाल 0x08:
			product_str = "LSISAS1068E B3";
			अवरोध;
		शेष:
			product_str = "LSISAS1068E";
			अवरोध;
		पूर्ण
		अवरोध;
	हाल MPI_MANUFACTPAGE_DEVID_SAS1078:
		चयन (revision)
		अणु
		हाल 0x00:
			product_str = "LSISAS1078 A0";
			अवरोध;
		हाल 0x01:
			product_str = "LSISAS1078 B0";
			अवरोध;
		हाल 0x02:
			product_str = "LSISAS1078 C0";
			अवरोध;
		हाल 0x03:
			product_str = "LSISAS1078 C1";
			अवरोध;
		हाल 0x04:
			product_str = "LSISAS1078 C2";
			अवरोध;
		शेष:
			product_str = "LSISAS1078";
			अवरोध;
		पूर्ण
		अवरोध;
	पूर्ण

 out:
	वापस product_str;
पूर्ण

/**
 *	mpt_mapresources - map in memory mapped io
 *	@ioc: Poपूर्णांकer to poपूर्णांकer to IOC adapter
 *
 **/
अटल पूर्णांक
mpt_mapresources(MPT_ADAPTER *ioc)
अणु
	u8		__iomem *mem;
	पूर्णांक		 ii;
	resource_माप_प्रकार	 mem_phys;
	अचिन्हित दीर्घ	 port;
	u32		 msize;
	u32		 psize;
	पूर्णांक		 r = -ENODEV;
	काष्ठा pci_dev *pdev;

	pdev = ioc->pcidev;
	ioc->bars = pci_select_bars(pdev, IORESOURCE_MEM);
	अगर (pci_enable_device_mem(pdev)) अणु
		prपूर्णांकk(MYIOC_s_ERR_FMT "pci_enable_device_mem() "
		    "failed\n", ioc->name);
		वापस r;
	पूर्ण
	अगर (pci_request_selected_regions(pdev, ioc->bars, "mpt")) अणु
		prपूर्णांकk(MYIOC_s_ERR_FMT "pci_request_selected_regions() with "
		    "MEM failed\n", ioc->name);
		जाओ out_pci_disable_device;
	पूर्ण

	अगर (माप(dma_addr_t) > 4) अणु
		स्थिर uपूर्णांक64_t required_mask = dma_get_required_mask
		    (&pdev->dev);
		अगर (required_mask > DMA_BIT_MASK(32)
			&& !pci_set_dma_mask(pdev, DMA_BIT_MASK(64))
			&& !pci_set_consistent_dma_mask(pdev,
						 DMA_BIT_MASK(64))) अणु
			ioc->dma_mask = DMA_BIT_MASK(64);
			dinitprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_INFO_FMT
				": 64 BIT PCI BUS DMA ADDRESSING SUPPORTED\n",
				ioc->name));
		पूर्ण अन्यथा अगर (!pci_set_dma_mask(pdev, DMA_BIT_MASK(32))
			&& !pci_set_consistent_dma_mask(pdev,
						DMA_BIT_MASK(32))) अणु
			ioc->dma_mask = DMA_BIT_MASK(32);
			dinitprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_INFO_FMT
				": 32 BIT PCI BUS DMA ADDRESSING SUPPORTED\n",
				ioc->name));
		पूर्ण अन्यथा अणु
			prपूर्णांकk(MYIOC_s_WARN_FMT "no suitable DMA mask for %s\n",
			    ioc->name, pci_name(pdev));
			जाओ out_pci_release_region;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (!pci_set_dma_mask(pdev, DMA_BIT_MASK(32))
			&& !pci_set_consistent_dma_mask(pdev,
						DMA_BIT_MASK(32))) अणु
			ioc->dma_mask = DMA_BIT_MASK(32);
			dinitprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_INFO_FMT
				": 32 BIT PCI BUS DMA ADDRESSING SUPPORTED\n",
				ioc->name));
		पूर्ण अन्यथा अणु
			prपूर्णांकk(MYIOC_s_WARN_FMT "no suitable DMA mask for %s\n",
			    ioc->name, pci_name(pdev));
			जाओ out_pci_release_region;
		पूर्ण
	पूर्ण

	mem_phys = msize = 0;
	port = psize = 0;
	क्रम (ii = 0; ii < DEVICE_COUNT_RESOURCE; ii++) अणु
		अगर (pci_resource_flags(pdev, ii) & PCI_BASE_ADDRESS_SPACE_IO) अणु
			अगर (psize)
				जारी;
			/* Get I/O space! */
			port = pci_resource_start(pdev, ii);
			psize = pci_resource_len(pdev, ii);
		पूर्ण अन्यथा अणु
			अगर (msize)
				जारी;
			/* Get memmap */
			mem_phys = pci_resource_start(pdev, ii);
			msize = pci_resource_len(pdev, ii);
		पूर्ण
	पूर्ण
	ioc->mem_size = msize;

	mem = शून्य;
	/* Get logical ptr क्रम PciMem0 space */
	/*mem = ioremap(mem_phys, msize);*/
	mem = ioremap(mem_phys, msize);
	अगर (mem == शून्य) अणु
		prपूर्णांकk(MYIOC_s_ERR_FMT ": ERROR - Unable to map adapter"
			" memory!\n", ioc->name);
		r = -EINVAL;
		जाओ out_pci_release_region;
	पूर्ण
	ioc->memmap = mem;
	dinitprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_INFO_FMT "mem = %p, mem_phys = %llx\n",
	    ioc->name, mem, (अचिन्हित दीर्घ दीर्घ)mem_phys));

	ioc->mem_phys = mem_phys;
	ioc->chip = (SYSIF_REGS __iomem *)mem;

	/* Save Port IO values in हाल we need to करो करोwnloadboot */
	ioc->pio_mem_phys = port;
	ioc->pio_chip = (SYSIF_REGS __iomem *)port;

	वापस 0;

out_pci_release_region:
	pci_release_selected_regions(pdev, ioc->bars);
out_pci_disable_device:
	pci_disable_device(pdev);
	वापस r;
पूर्ण

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/**
 *	mpt_attach - Install a PCI पूर्णांकelligent MPT adapter.
 *	@pdev: Poपूर्णांकer to pci_dev काष्ठाure
 *	@id: PCI device ID inक्रमmation
 *
 *	This routine perक्रमms all the steps necessary to bring the IOC of
 *	a MPT adapter to a OPERATIONAL state.  This includes रेजिस्टरing
 *	memory regions, रेजिस्टरing the पूर्णांकerrupt, and allocating request
 *	and reply memory pools.
 *
 *	This routine also pre-fetches the LAN MAC address of a Fibre Channel
 *	MPT adapter.
 *
 *	Returns 0 क्रम success, non-zero क्रम failure.
 *
 *	TODO: Add support क्रम polled controllers
 */
पूर्णांक
mpt_attach(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *id)
अणु
	MPT_ADAPTER	*ioc;
	u8		 cb_idx;
	पूर्णांक		 r = -ENODEV;
	u8		 pcixcmd;
	अटल पूर्णांक	 mpt_ids = 0;
#अगर_घोषित CONFIG_PROC_FS
	काष्ठा proc_dir_entry *dent;
#पूर्ण_अगर

	ioc = kzalloc(माप(MPT_ADAPTER), GFP_KERNEL);
	अगर (ioc == शून्य) अणु
		prपूर्णांकk(KERN_ERR MYNAM ": ERROR - Insufficient memory to add adapter!\n");
		वापस -ENOMEM;
	पूर्ण

	ioc->id = mpt_ids++;
	प्र_लिखो(ioc->name, "ioc%d", ioc->id);
	dinitprपूर्णांकk(ioc, prपूर्णांकk(KERN_WARNING MYNAM ": mpt_adapter_install\n"));

	/*
	 * set initial debug level
	 * (refer to mptdebug.h)
	 *
	 */
	ioc->debug_level = mpt_debug_level;
	अगर (mpt_debug_level)
		prपूर्णांकk(KERN_INFO "mpt_debug_level=%xh\n", mpt_debug_level);

	dinitprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_INFO_FMT ": mpt_adapter_install\n", ioc->name));

	ioc->pcidev = pdev;
	अगर (mpt_mapresources(ioc)) अणु
		जाओ out_मुक्त_ioc;
	पूर्ण

	/*
	 * Setting up proper handlers क्रम scatter gather handling
	 */
	अगर (ioc->dma_mask == DMA_BIT_MASK(64)) अणु
		अगर (pdev->device == MPI_MANUFACTPAGE_DEVID_SAS1078)
			ioc->add_sge = &mpt_add_sge_64bit_1078;
		अन्यथा
			ioc->add_sge = &mpt_add_sge_64bit;
		ioc->add_chain = &mpt_add_chain_64bit;
		ioc->sg_addr_size = 8;
	पूर्ण अन्यथा अणु
		ioc->add_sge = &mpt_add_sge;
		ioc->add_chain = &mpt_add_chain;
		ioc->sg_addr_size = 4;
	पूर्ण
	ioc->SGE_size = माप(u32) + ioc->sg_addr_size;

	ioc->alloc_total = माप(MPT_ADAPTER);
	ioc->req_sz = MPT_DEFAULT_FRAME_SIZE;		/* aव्योम भाग by zero! */
	ioc->reply_sz = MPT_REPLY_FRAME_SIZE;


	spin_lock_init(&ioc->taskmgmt_lock);
	mutex_init(&ioc->पूर्णांकernal_cmds.mutex);
	init_completion(&ioc->पूर्णांकernal_cmds.करोne);
	mutex_init(&ioc->mptbase_cmds.mutex);
	init_completion(&ioc->mptbase_cmds.करोne);
	mutex_init(&ioc->taskmgmt_cmds.mutex);
	init_completion(&ioc->taskmgmt_cmds.करोne);

	/* Initialize the event logging.
	 */
	ioc->eventTypes = 0;	/* None */
	ioc->eventContext = 0;
	ioc->eventLogSize = 0;
	ioc->events = शून्य;

#अगर_घोषित MFCNT
	ioc->mfcnt = 0;
#पूर्ण_अगर

	ioc->sh = शून्य;
	ioc->cached_fw = शून्य;

	/* Initialize SCSI Config Data काष्ठाure
	 */
	स_रखो(&ioc->spi_data, 0, माप(SpiCfgData));

	/* Initialize the fc rport list head.
	 */
	INIT_LIST_HEAD(&ioc->fc_rports);

	/* Find lookup slot. */
	INIT_LIST_HEAD(&ioc->list);


	/* Initialize workqueue */
	INIT_DELAYED_WORK(&ioc->fault_reset_work, mpt_fault_reset_work);

	snम_लिखो(ioc->reset_work_q_name, MPT_KOBJ_NAME_LEN,
		 "mpt_poll_%d", ioc->id);
	ioc->reset_work_q = alloc_workqueue(ioc->reset_work_q_name,
					    WQ_MEM_RECLAIM, 0);
	अगर (!ioc->reset_work_q) अणु
		prपूर्णांकk(MYIOC_s_ERR_FMT "Insufficient memory to add adapter!\n",
		    ioc->name);
		r = -ENOMEM;
		जाओ out_unmap_resources;
	पूर्ण

	dinitprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_INFO_FMT "facts @ %p, pfacts[0] @ %p\n",
	    ioc->name, &ioc->facts, &ioc->pfacts[0]));

	ioc->prod_name = mpt_get_product_name(pdev->venकरोr, pdev->device,
					      pdev->revision);

	चयन (pdev->device)
	अणु
	हाल MPI_MANUFACTPAGE_DEVICEID_FC939X:
	हाल MPI_MANUFACTPAGE_DEVICEID_FC949X:
		ioc->errata_flag_1064 = 1;
		fallthrough;
	हाल MPI_MANUFACTPAGE_DEVICEID_FC909:
	हाल MPI_MANUFACTPAGE_DEVICEID_FC929:
	हाल MPI_MANUFACTPAGE_DEVICEID_FC919:
	हाल MPI_MANUFACTPAGE_DEVICEID_FC949E:
		ioc->bus_type = FC;
		अवरोध;

	हाल MPI_MANUFACTPAGE_DEVICEID_FC929X:
		अगर (pdev->revision < XL_929) अणु
			/* 929X Chip Fix. Set Split transactions level
		 	* क्रम PCIX. Set MOST bits to zero.
		 	*/
			pci_पढ़ो_config_byte(pdev, 0x6a, &pcixcmd);
			pcixcmd &= 0x8F;
			pci_ग_लिखो_config_byte(pdev, 0x6a, pcixcmd);
		पूर्ण अन्यथा अणु
			/* 929XL Chip Fix. Set MMRBC to 0x08.
		 	*/
			pci_पढ़ो_config_byte(pdev, 0x6a, &pcixcmd);
			pcixcmd |= 0x08;
			pci_ग_लिखो_config_byte(pdev, 0x6a, pcixcmd);
		पूर्ण
		ioc->bus_type = FC;
		अवरोध;

	हाल MPI_MANUFACTPAGE_DEVICEID_FC919X:
		/* 919X Chip Fix. Set Split transactions level
		 * क्रम PCIX. Set MOST bits to zero.
		 */
		pci_पढ़ो_config_byte(pdev, 0x6a, &pcixcmd);
		pcixcmd &= 0x8F;
		pci_ग_लिखो_config_byte(pdev, 0x6a, pcixcmd);
		ioc->bus_type = FC;
		अवरोध;

	हाल MPI_MANUFACTPAGE_DEVID_53C1030:
		/* 1030 Chip Fix. Disable Split transactions
		 * क्रम PCIX. Set MOST bits to zero अगर Rev < C0( = 8).
		 */
		अगर (pdev->revision < C0_1030) अणु
			pci_पढ़ो_config_byte(pdev, 0x6a, &pcixcmd);
			pcixcmd &= 0x8F;
			pci_ग_लिखो_config_byte(pdev, 0x6a, pcixcmd);
		पूर्ण
		fallthrough;

	हाल MPI_MANUFACTPAGE_DEVID_1030_53C1035:
		ioc->bus_type = SPI;
		अवरोध;

	हाल MPI_MANUFACTPAGE_DEVID_SAS1064:
	हाल MPI_MANUFACTPAGE_DEVID_SAS1068:
		ioc->errata_flag_1064 = 1;
		ioc->bus_type = SAS;
		अवरोध;

	हाल MPI_MANUFACTPAGE_DEVID_SAS1064E:
	हाल MPI_MANUFACTPAGE_DEVID_SAS1068E:
	हाल MPI_MANUFACTPAGE_DEVID_SAS1078:
		ioc->bus_type = SAS;
		अवरोध;
	पूर्ण


	चयन (ioc->bus_type) अणु

	हाल SAS:
		ioc->msi_enable = mpt_msi_enable_sas;
		अवरोध;

	हाल SPI:
		ioc->msi_enable = mpt_msi_enable_spi;
		अवरोध;

	हाल FC:
		ioc->msi_enable = mpt_msi_enable_fc;
		अवरोध;

	शेष:
		ioc->msi_enable = 0;
		अवरोध;
	पूर्ण

	ioc->fw_events_off = 1;

	अगर (ioc->errata_flag_1064)
		pci_disable_io_access(pdev);

	spin_lock_init(&ioc->FreeQlock);

	/* Disable all! */
	CHIPREG_WRITE32(&ioc->chip->IntMask, 0xFFFFFFFF);
	ioc->active = 0;
	CHIPREG_WRITE32(&ioc->chip->IntStatus, 0);

	/* Set IOC ptr in the pcidev's driver data. */
	pci_set_drvdata(ioc->pcidev, ioc);

	/* Set lookup ptr. */
	list_add_tail(&ioc->list, &ioc_list);

	/* Check क्रम "bound ports" (929, 929X, 1030, 1035) to reduce redundant resets.
	 */
	mpt_detect_bound_ports(ioc, pdev);

	INIT_LIST_HEAD(&ioc->fw_event_list);
	spin_lock_init(&ioc->fw_event_lock);
	snम_लिखो(ioc->fw_event_q_name, MPT_KOBJ_NAME_LEN, "mpt/%d", ioc->id);
	ioc->fw_event_q = alloc_workqueue(ioc->fw_event_q_name,
					  WQ_MEM_RECLAIM, 0);
	अगर (!ioc->fw_event_q) अणु
		prपूर्णांकk(MYIOC_s_ERR_FMT "Insufficient memory to add adapter!\n",
		    ioc->name);
		r = -ENOMEM;
		जाओ out_हटाओ_ioc;
	पूर्ण

	अगर ((r = mpt_करो_ioc_recovery(ioc, MPT_HOSTEVENT_IOC_BRINGUP,
	    CAN_SLEEP)) != 0)अणु
		prपूर्णांकk(MYIOC_s_ERR_FMT "didn't initialize properly! (%d)\n",
		    ioc->name, r);

		destroy_workqueue(ioc->fw_event_q);
		ioc->fw_event_q = शून्य;

		list_del(&ioc->list);
		अगर (ioc->alt_ioc)
			ioc->alt_ioc->alt_ioc = शून्य;
		iounmap(ioc->memmap);
		अगर (pci_is_enabled(pdev))
			pci_disable_device(pdev);
		अगर (r != -5)
			pci_release_selected_regions(pdev, ioc->bars);

		destroy_workqueue(ioc->reset_work_q);
		ioc->reset_work_q = शून्य;

		kमुक्त(ioc);
		वापस r;
	पूर्ण

	/* call per device driver probe entry poपूर्णांक */
	क्रम(cb_idx = 0; cb_idx < MPT_MAX_PROTOCOL_DRIVERS; cb_idx++) अणु
		अगर(MptDeviceDriverHandlers[cb_idx] &&
		  MptDeviceDriverHandlers[cb_idx]->probe) अणु
			MptDeviceDriverHandlers[cb_idx]->probe(pdev,id);
		पूर्ण
	पूर्ण

#अगर_घोषित CONFIG_PROC_FS
	/*
	 *  Create "/proc/mpt/iocN" subdirectory entry क्रम each MPT adapter.
	 */
	dent = proc_सूची_गढ़ो(ioc->name, mpt_proc_root_dir);
	अगर (dent) अणु
		proc_create_single_data("info", S_IRUGO, dent,
				mpt_iocinfo_proc_show, ioc);
		proc_create_single_data("summary", S_IRUGO, dent,
				mpt_summary_proc_show, ioc);
	पूर्ण
#पूर्ण_अगर

	अगर (!ioc->alt_ioc)
		queue_delayed_work(ioc->reset_work_q, &ioc->fault_reset_work,
			msecs_to_jअगरfies(MPT_POLLING_INTERVAL));

	वापस 0;

out_हटाओ_ioc:
	list_del(&ioc->list);
	अगर (ioc->alt_ioc)
		ioc->alt_ioc->alt_ioc = शून्य;

	destroy_workqueue(ioc->reset_work_q);
	ioc->reset_work_q = शून्य;

out_unmap_resources:
	iounmap(ioc->memmap);
	pci_disable_device(pdev);
	pci_release_selected_regions(pdev, ioc->bars);

out_मुक्त_ioc:
	kमुक्त(ioc);

	वापस r;
पूर्ण

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/**
 *	mpt_detach - Remove a PCI पूर्णांकelligent MPT adapter.
 *	@pdev: Poपूर्णांकer to pci_dev काष्ठाure
 */

व्योम
mpt_detach(काष्ठा pci_dev *pdev)
अणु
	MPT_ADAPTER 	*ioc = pci_get_drvdata(pdev);
	अक्षर pname[64];
	u8 cb_idx;
	अचिन्हित दीर्घ flags;
	काष्ठा workqueue_काष्ठा *wq;

	/*
	 * Stop polling ioc क्रम fault condition
	 */
	spin_lock_irqsave(&ioc->taskmgmt_lock, flags);
	wq = ioc->reset_work_q;
	ioc->reset_work_q = शून्य;
	spin_unlock_irqrestore(&ioc->taskmgmt_lock, flags);
	cancel_delayed_work(&ioc->fault_reset_work);
	destroy_workqueue(wq);

	spin_lock_irqsave(&ioc->fw_event_lock, flags);
	wq = ioc->fw_event_q;
	ioc->fw_event_q = शून्य;
	spin_unlock_irqrestore(&ioc->fw_event_lock, flags);
	destroy_workqueue(wq);

	snम_लिखो(pname, माप(pname), MPT_PROCFS_MPTBASEसूची "/%s/summary", ioc->name);
	हटाओ_proc_entry(pname, शून्य);
	snम_लिखो(pname, माप(pname), MPT_PROCFS_MPTBASEसूची "/%s/info", ioc->name);
	हटाओ_proc_entry(pname, शून्य);
	snम_लिखो(pname, माप(pname), MPT_PROCFS_MPTBASEसूची "/%s", ioc->name);
	हटाओ_proc_entry(pname, शून्य);

	/* call per device driver हटाओ entry poपूर्णांक */
	क्रम(cb_idx = 0; cb_idx < MPT_MAX_PROTOCOL_DRIVERS; cb_idx++) अणु
		अगर(MptDeviceDriverHandlers[cb_idx] &&
		  MptDeviceDriverHandlers[cb_idx]->हटाओ) अणु
			MptDeviceDriverHandlers[cb_idx]->हटाओ(pdev);
		पूर्ण
	पूर्ण

	/* Disable पूर्णांकerrupts! */
	CHIPREG_WRITE32(&ioc->chip->IntMask, 0xFFFFFFFF);

	ioc->active = 0;
	synchronize_irq(pdev->irq);

	/* Clear any lingering पूर्णांकerrupt */
	CHIPREG_WRITE32(&ioc->chip->IntStatus, 0);

	CHIPREG_READ32(&ioc->chip->IntStatus);

	mpt_adapter_dispose(ioc);

पूर्ण

/**************************************************************************
 * Power Management
 */
#अगर_घोषित CONFIG_PM
/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/**
 *	mpt_suspend - Fusion MPT base driver suspend routine.
 *	@pdev: Poपूर्णांकer to pci_dev काष्ठाure
 *	@state: new state to enter
 */
पूर्णांक
mpt_suspend(काष्ठा pci_dev *pdev, pm_message_t state)
अणु
	u32 device_state;
	MPT_ADAPTER *ioc = pci_get_drvdata(pdev);

	device_state = pci_choose_state(pdev, state);
	prपूर्णांकk(MYIOC_s_INFO_FMT "pci-suspend: pdev=0x%p, slot=%s, Entering "
	    "operating state [D%d]\n", ioc->name, pdev, pci_name(pdev),
	    device_state);

	/* put ioc पूर्णांकo READY_STATE */
	अगर (SendIocReset(ioc, MPI_FUNCTION_IOC_MESSAGE_UNIT_RESET, CAN_SLEEP)) अणु
		prपूर्णांकk(MYIOC_s_ERR_FMT
		"pci-suspend:  IOC msg unit reset failed!\n", ioc->name);
	पूर्ण

	/* disable पूर्णांकerrupts */
	CHIPREG_WRITE32(&ioc->chip->IntMask, 0xFFFFFFFF);
	ioc->active = 0;

	/* Clear any lingering पूर्णांकerrupt */
	CHIPREG_WRITE32(&ioc->chip->IntStatus, 0);

	मुक्त_irq(ioc->pci_irq, ioc);
	अगर (ioc->msi_enable)
		pci_disable_msi(ioc->pcidev);
	ioc->pci_irq = -1;
	pci_save_state(pdev);
	pci_disable_device(pdev);
	pci_release_selected_regions(pdev, ioc->bars);
	pci_set_घातer_state(pdev, device_state);
	वापस 0;
पूर्ण

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/**
 *	mpt_resume - Fusion MPT base driver resume routine.
 *	@pdev: Poपूर्णांकer to pci_dev काष्ठाure
 */
पूर्णांक
mpt_resume(काष्ठा pci_dev *pdev)
अणु
	MPT_ADAPTER *ioc = pci_get_drvdata(pdev);
	u32 device_state = pdev->current_state;
	पूर्णांक recovery_state;
	पूर्णांक err;

	prपूर्णांकk(MYIOC_s_INFO_FMT "pci-resume: pdev=0x%p, slot=%s, Previous "
	    "operating state [D%d]\n", ioc->name, pdev, pci_name(pdev),
	    device_state);

	pci_set_घातer_state(pdev, PCI_D0);
	pci_enable_wake(pdev, PCI_D0, 0);
	pci_restore_state(pdev);
	ioc->pcidev = pdev;
	err = mpt_mapresources(ioc);
	अगर (err)
		वापस err;

	अगर (ioc->dma_mask == DMA_BIT_MASK(64)) अणु
		अगर (pdev->device == MPI_MANUFACTPAGE_DEVID_SAS1078)
			ioc->add_sge = &mpt_add_sge_64bit_1078;
		अन्यथा
			ioc->add_sge = &mpt_add_sge_64bit;
		ioc->add_chain = &mpt_add_chain_64bit;
		ioc->sg_addr_size = 8;
	पूर्ण अन्यथा अणु

		ioc->add_sge = &mpt_add_sge;
		ioc->add_chain = &mpt_add_chain;
		ioc->sg_addr_size = 4;
	पूर्ण
	ioc->SGE_size = माप(u32) + ioc->sg_addr_size;

	prपूर्णांकk(MYIOC_s_INFO_FMT "pci-resume: ioc-state=0x%x,doorbell=0x%x\n",
	    ioc->name, (mpt_GetIocState(ioc, 1) >> MPI_IOC_STATE_SHIFT),
	    CHIPREG_READ32(&ioc->chip->Doorbell));

	/*
	 * Errata workaround क्रम SAS pci express:
	 * Upon वापसing to the D0 state, the contents of the करोorbell will be
	 * stale data, and this will incorrectly संकेत to the host driver that
	 * the firmware is पढ़ोy to process mpt commands.   The workaround is
	 * to issue a diagnostic reset.
	 */
	अगर (ioc->bus_type == SAS && (pdev->device ==
	    MPI_MANUFACTPAGE_DEVID_SAS1068E || pdev->device ==
	    MPI_MANUFACTPAGE_DEVID_SAS1064E)) अणु
		अगर (KickStart(ioc, 1, CAN_SLEEP) < 0) अणु
			prपूर्णांकk(MYIOC_s_WARN_FMT "pci-resume: Cannot recover\n",
			    ioc->name);
			जाओ out;
		पूर्ण
	पूर्ण

	/* bring ioc to operational state */
	prपूर्णांकk(MYIOC_s_INFO_FMT "Sending mpt_do_ioc_recovery\n", ioc->name);
	recovery_state = mpt_करो_ioc_recovery(ioc, MPT_HOSTEVENT_IOC_BRINGUP,
						 CAN_SLEEP);
	अगर (recovery_state != 0)
		prपूर्णांकk(MYIOC_s_WARN_FMT "pci-resume: Cannot recover, "
		    "error:[%x]\n", ioc->name, recovery_state);
	अन्यथा
		prपूर्णांकk(MYIOC_s_INFO_FMT
		    "pci-resume: success\n", ioc->name);
 out:
	वापस 0;

पूर्ण
#पूर्ण_अगर

अटल पूर्णांक
mpt_संकेत_reset(u8 index, MPT_ADAPTER *ioc, पूर्णांक reset_phase)
अणु
	अगर ((MptDriverClass[index] == MPTSPI_DRIVER &&
	     ioc->bus_type != SPI) ||
	    (MptDriverClass[index] == MPTFC_DRIVER &&
	     ioc->bus_type != FC) ||
	    (MptDriverClass[index] == MPTSAS_DRIVER &&
	     ioc->bus_type != SAS))
		/* make sure we only call the relevant reset handler
		 * क्रम the bus */
		वापस 0;
	वापस (MptResetHandlers[index])(ioc, reset_phase);
पूर्ण

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/**
 *	mpt_करो_ioc_recovery - Initialize or recover MPT adapter.
 *	@ioc: Poपूर्णांकer to MPT adapter काष्ठाure
 *	@reason: Event word / reason
 *	@sleepFlag: Use schedule अगर CAN_SLEEP अन्यथा use udelay.
 *
 *	This routine perक्रमms all the steps necessary to bring the IOC
 *	to a OPERATIONAL state.
 *
 *	This routine also pre-fetches the LAN MAC address of a Fibre Channel
 *	MPT adapter.
 *
 *	Returns:
 *		 0 क्रम success
 *		-1 अगर failed to get board READY
 *		-2 अगर READY but IOCFacts Failed
 *		-3 अगर READY but PrimeIOCFअगरos Failed
 *		-4 अगर READY but IOCInit Failed
 *		-5 अगर failed to enable_device and/or request_selected_regions
 *		-6 अगर failed to upload firmware
 */
अटल पूर्णांक
mpt_करो_ioc_recovery(MPT_ADAPTER *ioc, u32 reason, पूर्णांक sleepFlag)
अणु
	पूर्णांक	 hard_reset_करोne = 0;
	पूर्णांक	 alt_ioc_पढ़ोy = 0;
	पूर्णांक	 hard;
	पूर्णांक	 rc=0;
	पूर्णांक	 ii;
	पूर्णांक	 ret = 0;
	पूर्णांक	 reset_alt_ioc_active = 0;
	पूर्णांक	 irq_allocated = 0;
	u8	*a;

	prपूर्णांकk(MYIOC_s_INFO_FMT "Initiating %s\n", ioc->name,
	    reason == MPT_HOSTEVENT_IOC_BRINGUP ? "bringup" : "recovery");

	/* Disable reply पूर्णांकerrupts (also blocks FreeQ) */
	CHIPREG_WRITE32(&ioc->chip->IntMask, 0xFFFFFFFF);
	ioc->active = 0;

	अगर (ioc->alt_ioc) अणु
		अगर (ioc->alt_ioc->active ||
		    reason == MPT_HOSTEVENT_IOC_RECOVER) अणु
			reset_alt_ioc_active = 1;
			/* Disable alt-IOC's reply पूर्णांकerrupts
			 *  (and FreeQ) क्रम a bit
			 **/
			CHIPREG_WRITE32(&ioc->alt_ioc->chip->IntMask,
				0xFFFFFFFF);
			ioc->alt_ioc->active = 0;
		पूर्ण
	पूर्ण

	hard = 1;
	अगर (reason == MPT_HOSTEVENT_IOC_BRINGUP)
		hard = 0;

	अगर ((hard_reset_करोne = MakeIocReady(ioc, hard, sleepFlag)) < 0) अणु
		अगर (hard_reset_करोne == -4) अणु
			prपूर्णांकk(MYIOC_s_WARN_FMT "Owned by PEER..skipping!\n",
			    ioc->name);

			अगर (reset_alt_ioc_active && ioc->alt_ioc) अणु
				/* (re)Enable alt-IOC! (reply पूर्णांकerrupt, FreeQ) */
				dprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_INFO_FMT
				    "alt_ioc reply irq re-enabled\n", ioc->alt_ioc->name));
				CHIPREG_WRITE32(&ioc->alt_ioc->chip->IntMask, MPI_HIM_DIM);
				ioc->alt_ioc->active = 1;
			पूर्ण

		पूर्ण अन्यथा अणु
			prपूर्णांकk(MYIOC_s_WARN_FMT
			    "NOT READY WARNING!\n", ioc->name);
		पूर्ण
		ret = -1;
		जाओ out;
	पूर्ण

	/* hard_reset_करोne = 0 अगर a soft reset was perक्रमmed
	 * and 1 अगर a hard reset was perक्रमmed.
	 */
	अगर (hard_reset_करोne && reset_alt_ioc_active && ioc->alt_ioc) अणु
		अगर ((rc = MakeIocReady(ioc->alt_ioc, 0, sleepFlag)) == 0)
			alt_ioc_पढ़ोy = 1;
		अन्यथा
			prपूर्णांकk(MYIOC_s_WARN_FMT
			    ": alt-ioc Not ready WARNING!\n",
			    ioc->alt_ioc->name);
	पूर्ण

	क्रम (ii=0; ii<5; ii++) अणु
		/* Get IOC facts! Allow 5 retries */
		अगर ((rc = GetIocFacts(ioc, sleepFlag, reason)) == 0)
			अवरोध;
	पूर्ण


	अगर (ii == 5) अणु
		dinitprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT
		    "Retry IocFacts failed rc=%x\n", ioc->name, rc));
		ret = -2;
	पूर्ण अन्यथा अगर (reason == MPT_HOSTEVENT_IOC_BRINGUP) अणु
		MptDisplayIocCapabilities(ioc);
	पूर्ण

	अगर (alt_ioc_पढ़ोy) अणु
		अगर ((rc = GetIocFacts(ioc->alt_ioc, sleepFlag, reason)) != 0) अणु
			dinitprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT
			    "Initial Alt IocFacts failed rc=%x\n",
			    ioc->name, rc));
			/* Retry - alt IOC was initialized once
			 */
			rc = GetIocFacts(ioc->alt_ioc, sleepFlag, reason);
		पूर्ण
		अगर (rc) अणु
			dinitprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT
			    "Retry Alt IocFacts failed rc=%x\n", ioc->name, rc));
			alt_ioc_पढ़ोy = 0;
			reset_alt_ioc_active = 0;
		पूर्ण अन्यथा अगर (reason == MPT_HOSTEVENT_IOC_BRINGUP) अणु
			MptDisplayIocCapabilities(ioc->alt_ioc);
		पूर्ण
	पूर्ण

	अगर ((ret == 0) && (reason == MPT_HOSTEVENT_IOC_BRINGUP) &&
	    (ioc->facts.Flags & MPI_IOCFACTS_FLAGS_FW_DOWNLOAD_BOOT)) अणु
		pci_release_selected_regions(ioc->pcidev, ioc->bars);
		ioc->bars = pci_select_bars(ioc->pcidev, IORESOURCE_MEM |
		    IORESOURCE_IO);
		अगर (pci_enable_device(ioc->pcidev))
			वापस -5;
		अगर (pci_request_selected_regions(ioc->pcidev, ioc->bars,
			"mpt"))
			वापस -5;
	पूर्ण

	/*
	 * Device is reset now. It must have de-निश्चितed the पूर्णांकerrupt line
	 * (अगर it was निश्चितed) and it should be safe to रेजिस्टर क्रम the
	 * पूर्णांकerrupt now.
	 */
	अगर ((ret == 0) && (reason == MPT_HOSTEVENT_IOC_BRINGUP)) अणु
		ioc->pci_irq = -1;
		अगर (ioc->pcidev->irq) अणु
			अगर (ioc->msi_enable && !pci_enable_msi(ioc->pcidev))
				prपूर्णांकk(MYIOC_s_INFO_FMT "PCI-MSI enabled\n",
				    ioc->name);
			अन्यथा
				ioc->msi_enable = 0;
			rc = request_irq(ioc->pcidev->irq, mpt_पूर्णांकerrupt,
			    IRQF_SHARED, ioc->name, ioc);
			अगर (rc < 0) अणु
				prपूर्णांकk(MYIOC_s_ERR_FMT "Unable to allocate "
				    "interrupt %d!\n",
				    ioc->name, ioc->pcidev->irq);
				अगर (ioc->msi_enable)
					pci_disable_msi(ioc->pcidev);
				ret = -EBUSY;
				जाओ out;
			पूर्ण
			irq_allocated = 1;
			ioc->pci_irq = ioc->pcidev->irq;
			pci_set_master(ioc->pcidev);		/* ?? */
			pci_set_drvdata(ioc->pcidev, ioc);
			dinitprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_INFO_FMT
			    "installed at interrupt %d\n", ioc->name,
			    ioc->pcidev->irq));
		पूर्ण
	पूर्ण

	/* Prime reply & request queues!
	 * (mucho alloc's) Must be करोne prior to
	 * init as upper addresses are needed क्रम init.
	 * If fails, जारी with alt-ioc processing
	 */
	dinitprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_INFO_FMT "PrimeIocFifos\n",
	    ioc->name));
	अगर ((ret == 0) && ((rc = PrimeIocFअगरos(ioc)) != 0))
		ret = -3;

	/* May need to check/upload firmware & data here!
	 * If fails, जारी with alt-ioc processing
	 */
	dinitprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_INFO_FMT "SendIocInit\n",
	    ioc->name));
	अगर ((ret == 0) && ((rc = SendIocInit(ioc, sleepFlag)) != 0))
		ret = -4;
// NEW!
	अगर (alt_ioc_पढ़ोy && ((rc = PrimeIocFअगरos(ioc->alt_ioc)) != 0)) अणु
		prपूर्णांकk(MYIOC_s_WARN_FMT
		    ": alt-ioc (%d) FIFO mgmt alloc WARNING!\n",
		    ioc->alt_ioc->name, rc);
		alt_ioc_पढ़ोy = 0;
		reset_alt_ioc_active = 0;
	पूर्ण

	अगर (alt_ioc_पढ़ोy) अणु
		अगर ((rc = SendIocInit(ioc->alt_ioc, sleepFlag)) != 0) अणु
			alt_ioc_पढ़ोy = 0;
			reset_alt_ioc_active = 0;
			prपूर्णांकk(MYIOC_s_WARN_FMT
				": alt-ioc: (%d) init failure WARNING!\n",
					ioc->alt_ioc->name, rc);
		पूर्ण
	पूर्ण

	अगर (reason == MPT_HOSTEVENT_IOC_BRINGUP)अणु
		अगर (ioc->upload_fw) अणु
			ddlprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT
			    "firmware upload required!\n", ioc->name));

			/* Controller is not operational, cannot करो upload
			 */
			अगर (ret == 0) अणु
				rc = mpt_करो_upload(ioc, sleepFlag);
				अगर (rc == 0) अणु
					अगर (ioc->alt_ioc && ioc->alt_ioc->cached_fw) अणु
						/*
						 * Maपूर्णांकain only one poपूर्णांकer to FW memory
						 * so there will not be two attempt to
						 * करोwnloadboot onboard dual function
						 * chips (mpt_adapter_disable,
						 * mpt_diag_reset)
						 */
						ddlprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT
						    "mpt_upload:  alt_%s has cached_fw=%p \n",
						    ioc->name, ioc->alt_ioc->name, ioc->alt_ioc->cached_fw));
						ioc->cached_fw = शून्य;
					पूर्ण
				पूर्ण अन्यथा अणु
					prपूर्णांकk(MYIOC_s_WARN_FMT
					    "firmware upload failure!\n", ioc->name);
					ret = -6;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	/*  Enable MPT base driver management of EventNotअगरication
	 *  and EventAck handling.
	 */
	अगर ((ret == 0) && (!ioc->facts.EventState)) अणु
		dinitprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_INFO_FMT
			"SendEventNotification\n",
		    ioc->name));
		ret = SendEventNotअगरication(ioc, 1, sleepFlag);	/* 1=Enable */
	पूर्ण

	अगर (ioc->alt_ioc && alt_ioc_पढ़ोy && !ioc->alt_ioc->facts.EventState)
		rc = SendEventNotअगरication(ioc->alt_ioc, 1, sleepFlag);

	अगर (ret == 0) अणु
		/* Enable! (reply पूर्णांकerrupt) */
		CHIPREG_WRITE32(&ioc->chip->IntMask, MPI_HIM_DIM);
		ioc->active = 1;
	पूर्ण
	अगर (rc == 0) अणु	/* alt ioc */
		अगर (reset_alt_ioc_active && ioc->alt_ioc) अणु
			/* (re)Enable alt-IOC! (reply पूर्णांकerrupt) */
			dinitprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT "alt-ioc"
				"reply irq re-enabled\n",
				ioc->alt_ioc->name));
			CHIPREG_WRITE32(&ioc->alt_ioc->chip->IntMask,
				MPI_HIM_DIM);
			ioc->alt_ioc->active = 1;
		पूर्ण
	पूर्ण


	/*	Add additional "reason" check beक्रमe call to GetLanConfigPages
	 *	(combined with GetIoUnitPage2 call).  This prevents a somewhat
	 *	recursive scenario; GetLanConfigPages बार out, समयr expired
	 *	routine calls HardResetHandler, which calls पूर्णांकo here again,
	 *	and we try GetLanConfigPages again...
	 */
	अगर ((ret == 0) && (reason == MPT_HOSTEVENT_IOC_BRINGUP)) अणु

		/*
		 * Initialize link list क्रम inactive raid volumes.
		 */
		mutex_init(&ioc->raid_data.inactive_list_mutex);
		INIT_LIST_HEAD(&ioc->raid_data.inactive_list);

		चयन (ioc->bus_type) अणु

		हाल SAS:
			/* clear persistency table */
			अगर(ioc->facts.IOCExceptions &
			    MPI_IOCFACTS_EXCEPT_PERSISTENT_TABLE_FULL) अणु
				ret = mptbase_sas_persist_operation(ioc,
				    MPI_SAS_OP_CLEAR_NOT_PRESENT);
				अगर(ret != 0)
					जाओ out;
			पूर्ण

			/* Find IM volumes
			 */
			mpt_findImVolumes(ioc);

			/* Check, and possibly reset, the coalescing value
			 */
			mpt_पढ़ो_ioc_pg_1(ioc);

			अवरोध;

		हाल FC:
			अगर ((ioc->pfacts[0].ProtocolFlags &
				MPI_PORTFACTS_PROTOCOL_LAN) &&
			    (ioc->lan_cnfg_page0.Header.PageLength == 0)) अणु
				/*
				 *  Pre-fetch the ports LAN MAC address!
				 *  (LANPage1_t stuff)
				 */
				(व्योम) GetLanConfigPages(ioc);
				a = (u8*)&ioc->lan_cnfg_page1.HardwareAddressLow;
				dprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT
					"LanAddr = %pMR\n", ioc->name, a));
			पूर्ण
			अवरोध;

		हाल SPI:
			/* Get NVRAM and adapter maximums from SPP 0 and 2
			 */
			mpt_GetScsiPortSettings(ioc, 0);

			/* Get version and length of SDP 1
			 */
			mpt_पढ़ोScsiDevicePageHeaders(ioc, 0);

			/* Find IM volumes
			 */
			अगर (ioc->facts.MsgVersion >= MPI_VERSION_01_02)
				mpt_findImVolumes(ioc);

			/* Check, and possibly reset, the coalescing value
			 */
			mpt_पढ़ो_ioc_pg_1(ioc);

			mpt_पढ़ो_ioc_pg_4(ioc);

			अवरोध;
		पूर्ण

		GetIoUnitPage2(ioc);
		mpt_get_manufacturing_pg_0(ioc);
	पूर्ण

 out:
	अगर ((ret != 0) && irq_allocated) अणु
		मुक्त_irq(ioc->pci_irq, ioc);
		अगर (ioc->msi_enable)
			pci_disable_msi(ioc->pcidev);
	पूर्ण
	वापस ret;
पूर्ण

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/**
 *	mpt_detect_bound_ports - Search क्रम matching PCI bus/dev_function
 *	@ioc: Poपूर्णांकer to MPT adapter काष्ठाure
 *	@pdev: Poपूर्णांकer to (काष्ठा pci_dev) काष्ठाure
 *
 *	Search क्रम PCI bus/dev_function which matches
 *	PCI bus/dev_function (+/-1) क्रम newly discovered 929,
 *	929X, 1030 or 1035.
 *
 *	If match on PCI dev_function +/-1 is found, bind the two MPT adapters
 *	using alt_ioc poपूर्णांकer fields in their %MPT_ADAPTER काष्ठाures.
 */
अटल व्योम
mpt_detect_bound_ports(MPT_ADAPTER *ioc, काष्ठा pci_dev *pdev)
अणु
	काष्ठा pci_dev *peer=शून्य;
	अचिन्हित पूर्णांक slot = PCI_SLOT(pdev->devfn);
	अचिन्हित पूर्णांक func = PCI_FUNC(pdev->devfn);
	MPT_ADAPTER *ioc_srch;

	dprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT "PCI device %s devfn=%x/%x,"
	    " searching for devfn match on %x or %x\n",
	    ioc->name, pci_name(pdev), pdev->bus->number,
	    pdev->devfn, func-1, func+1));

	peer = pci_get_slot(pdev->bus, PCI_DEVFN(slot,func-1));
	अगर (!peer) अणु
		peer = pci_get_slot(pdev->bus, PCI_DEVFN(slot,func+1));
		अगर (!peer)
			वापस;
	पूर्ण

	list_क्रम_each_entry(ioc_srch, &ioc_list, list) अणु
		काष्ठा pci_dev *_pcidev = ioc_srch->pcidev;
		अगर (_pcidev == peer) अणु
			/* Paranoia checks */
			अगर (ioc->alt_ioc != शून्य) अणु
				prपूर्णांकk(MYIOC_s_WARN_FMT
				    "Oops, already bound (%s <==> %s)!\n",
				    ioc->name, ioc->name, ioc->alt_ioc->name);
				अवरोध;
			पूर्ण अन्यथा अगर (ioc_srch->alt_ioc != शून्य) अणु
				prपूर्णांकk(MYIOC_s_WARN_FMT
				    "Oops, already bound (%s <==> %s)!\n",
				    ioc_srch->name, ioc_srch->name,
				    ioc_srch->alt_ioc->name);
				अवरोध;
			पूर्ण
			dprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT
				"FOUND! binding %s <==> %s\n",
				ioc->name, ioc->name, ioc_srch->name));
			ioc_srch->alt_ioc = ioc;
			ioc->alt_ioc = ioc_srch;
		पूर्ण
	पूर्ण
	pci_dev_put(peer);
पूर्ण

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/**
 *	mpt_adapter_disable - Disable misbehaving MPT adapter.
 *	@ioc: Poपूर्णांकer to MPT adapter काष्ठाure
 */
अटल व्योम
mpt_adapter_disable(MPT_ADAPTER *ioc)
अणु
	पूर्णांक sz;
	पूर्णांक ret;

	अगर (ioc->cached_fw != शून्य) अणु
		ddlprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT
			"%s: Pushing FW onto adapter\n", __func__, ioc->name));
		अगर ((ret = mpt_करोwnloadboot(ioc, (MpiFwHeader_t *)
		    ioc->cached_fw, CAN_SLEEP)) < 0) अणु
			prपूर्णांकk(MYIOC_s_WARN_FMT
			    ": firmware downloadboot failure (%d)!\n",
			    ioc->name, ret);
		पूर्ण
	पूर्ण

	/*
	 * Put the controller पूर्णांकo पढ़ोy state (अगर its not alपढ़ोy)
	 */
	अगर (mpt_GetIocState(ioc, 1) != MPI_IOC_STATE_READY) अणु
		अगर (!SendIocReset(ioc, MPI_FUNCTION_IOC_MESSAGE_UNIT_RESET,
		    CAN_SLEEP)) अणु
			अगर (mpt_GetIocState(ioc, 1) != MPI_IOC_STATE_READY)
				prपूर्णांकk(MYIOC_s_ERR_FMT "%s:  IOC msg unit "
				    "reset failed to put ioc in ready state!\n",
				    ioc->name, __func__);
		पूर्ण अन्यथा
			prपूर्णांकk(MYIOC_s_ERR_FMT "%s:  IOC msg unit reset "
			    "failed!\n", ioc->name, __func__);
	पूर्ण


	/* Disable adapter पूर्णांकerrupts! */
	synchronize_irq(ioc->pcidev->irq);
	CHIPREG_WRITE32(&ioc->chip->IntMask, 0xFFFFFFFF);
	ioc->active = 0;

	/* Clear any lingering पूर्णांकerrupt */
	CHIPREG_WRITE32(&ioc->chip->IntStatus, 0);
	CHIPREG_READ32(&ioc->chip->IntStatus);

	अगर (ioc->alloc != शून्य) अणु
		sz = ioc->alloc_sz;
		dनिकासprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_INFO_FMT "free  @ %p, sz=%d bytes\n",
		    ioc->name, ioc->alloc, ioc->alloc_sz));
		dma_मुक्त_coherent(&ioc->pcidev->dev, sz, ioc->alloc,
				ioc->alloc_dma);
		ioc->reply_frames = शून्य;
		ioc->req_frames = शून्य;
		ioc->alloc = शून्य;
		ioc->alloc_total -= sz;
	पूर्ण

	अगर (ioc->sense_buf_pool != शून्य) अणु
		sz = (ioc->req_depth * MPT_SENSE_BUFFER_ALLOC);
		dma_मुक्त_coherent(&ioc->pcidev->dev, sz, ioc->sense_buf_pool,
				ioc->sense_buf_pool_dma);
		ioc->sense_buf_pool = शून्य;
		ioc->alloc_total -= sz;
	पूर्ण

	अगर (ioc->events != शून्य)अणु
		sz = MPTCTL_EVENT_LOG_SIZE * माप(MPT_IOCTL_EVENTS);
		kमुक्त(ioc->events);
		ioc->events = शून्य;
		ioc->alloc_total -= sz;
	पूर्ण

	mpt_मुक्त_fw_memory(ioc);

	kमुक्त(ioc->spi_data.nvram);
	mpt_inactive_raid_list_मुक्त(ioc);
	kमुक्त(ioc->raid_data.pIocPg2);
	kमुक्त(ioc->raid_data.pIocPg3);
	ioc->spi_data.nvram = शून्य;
	ioc->raid_data.pIocPg3 = शून्य;

	अगर (ioc->spi_data.pIocPg4 != शून्य) अणु
		sz = ioc->spi_data.IocPg4Sz;
		pci_मुक्त_consistent(ioc->pcidev, sz,
			ioc->spi_data.pIocPg4,
			ioc->spi_data.IocPg4_dma);
		ioc->spi_data.pIocPg4 = शून्य;
		ioc->alloc_total -= sz;
	पूर्ण

	अगर (ioc->ReqToChain != शून्य) अणु
		kमुक्त(ioc->ReqToChain);
		kमुक्त(ioc->RequestNB);
		ioc->ReqToChain = शून्य;
	पूर्ण

	kमुक्त(ioc->ChainToChain);
	ioc->ChainToChain = शून्य;

	अगर (ioc->HostPageBuffer != शून्य) अणु
		अगर((ret = mpt_host_page_access_control(ioc,
		    MPI_DB_HPBAC_FREE_BUFFER, NO_SLEEP)) != 0) अणु
			prपूर्णांकk(MYIOC_s_ERR_FMT
			   ": %s: host page buffers free failed (%d)!\n",
			    ioc->name, __func__, ret);
		पूर्ण
		dनिकासprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT
			"HostPageBuffer free  @ %p, sz=%d bytes\n",
			ioc->name, ioc->HostPageBuffer,
			ioc->HostPageBuffer_sz));
		dma_मुक्त_coherent(&ioc->pcidev->dev, ioc->HostPageBuffer_sz,
		    ioc->HostPageBuffer, ioc->HostPageBuffer_dma);
		ioc->HostPageBuffer = शून्य;
		ioc->HostPageBuffer_sz = 0;
		ioc->alloc_total -= ioc->HostPageBuffer_sz;
	पूर्ण

	pci_set_drvdata(ioc->pcidev, शून्य);
पूर्ण
/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/**
 *	mpt_adapter_dispose - Free all resources associated with an MPT adapter
 *	@ioc: Poपूर्णांकer to MPT adapter काष्ठाure
 *
 *	This routine unरेजिस्टरs h/w resources and मुक्तs all alloc'd memory
 *	associated with a MPT adapter काष्ठाure.
 */
अटल व्योम
mpt_adapter_dispose(MPT_ADAPTER *ioc)
अणु
	पूर्णांक sz_first, sz_last;

	अगर (ioc == शून्य)
		वापस;

	sz_first = ioc->alloc_total;

	mpt_adapter_disable(ioc);

	अगर (ioc->pci_irq != -1) अणु
		मुक्त_irq(ioc->pci_irq, ioc);
		अगर (ioc->msi_enable)
			pci_disable_msi(ioc->pcidev);
		ioc->pci_irq = -1;
	पूर्ण

	अगर (ioc->memmap != शून्य) अणु
		iounmap(ioc->memmap);
		ioc->memmap = शून्य;
	पूर्ण

	pci_disable_device(ioc->pcidev);
	pci_release_selected_regions(ioc->pcidev, ioc->bars);

	/*  Zap the adapter lookup ptr!  */
	list_del(&ioc->list);

	sz_last = ioc->alloc_total;
	dprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_INFO_FMT "free'd %d of %d bytes\n",
	    ioc->name, sz_first-sz_last+(पूर्णांक)माप(*ioc), sz_first));

	अगर (ioc->alt_ioc)
		ioc->alt_ioc->alt_ioc = शून्य;

	kमुक्त(ioc);
पूर्ण

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/**
 *	MptDisplayIocCapabilities - Disply IOC's capabilities.
 *	@ioc: Poपूर्णांकer to MPT adapter काष्ठाure
 */
अटल व्योम
MptDisplayIocCapabilities(MPT_ADAPTER *ioc)
अणु
	पूर्णांक i = 0;

	prपूर्णांकk(KERN_INFO "%s: ", ioc->name);
	अगर (ioc->prod_name)
		pr_cont("%s: ", ioc->prod_name);
	pr_cont("Capabilities={");

	अगर (ioc->pfacts[0].ProtocolFlags & MPI_PORTFACTS_PROTOCOL_INITIATOR) अणु
		pr_cont("Initiator");
		i++;
	पूर्ण

	अगर (ioc->pfacts[0].ProtocolFlags & MPI_PORTFACTS_PROTOCOL_TARGET) अणु
		pr_cont("%sTarget", i ? "," : "");
		i++;
	पूर्ण

	अगर (ioc->pfacts[0].ProtocolFlags & MPI_PORTFACTS_PROTOCOL_LAN) अणु
		pr_cont("%sLAN", i ? "," : "");
		i++;
	पूर्ण

#अगर 0
	/*
	 *  This would probably evoke more questions than it's worth
	 */
	अगर (ioc->pfacts[0].ProtocolFlags & MPI_PORTFACTS_PROTOCOL_TARGET) अणु
		pr_cont("%sLogBusAddr", i ? "," : "");
		i++;
	पूर्ण
#पूर्ण_अगर

	pr_cont("}\n");
पूर्ण

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/**
 *	MakeIocReady - Get IOC to a READY state, using KickStart अगर needed.
 *	@ioc: Poपूर्णांकer to MPT_ADAPTER काष्ठाure
 *	@क्रमce: Force hard KickStart of IOC
 *	@sleepFlag: Specअगरies whether the process can sleep
 *
 *	Returns:
 *		 1 - DIAG reset and READY
 *		 0 - READY initially OR soft reset and READY
 *		-1 - Any failure on KickStart
 *		-2 - Msg Unit Reset Failed
 *		-3 - IO Unit Reset Failed
 *		-4 - IOC owned by a PEER
 */
अटल पूर्णांक
MakeIocReady(MPT_ADAPTER *ioc, पूर्णांक क्रमce, पूर्णांक sleepFlag)
अणु
	u32	 ioc_state;
	पूर्णांक	 statefault = 0;
	पूर्णांक	 cntdn;
	पूर्णांक	 hard_reset_करोne = 0;
	पूर्णांक	 r;
	पूर्णांक	 ii;
	पूर्णांक	 whoinit;

	/* Get current [raw] IOC state  */
	ioc_state = mpt_GetIocState(ioc, 0);
	dhsprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_INFO_FMT "MakeIocReady [raw] state=%08x\n", ioc->name, ioc_state));

	/*
	 *	Check to see अगर IOC got left/stuck in करोorbell handshake
	 *	grip of death.  If so, hard reset the IOC.
	 */
	अगर (ioc_state & MPI_DOORBELL_ACTIVE) अणु
		statefault = 1;
		prपूर्णांकk(MYIOC_s_WARN_FMT "Unexpected doorbell active!\n",
				ioc->name);
	पूर्ण

	/* Is it alपढ़ोy READY? */
	अगर (!statefault &&
	    ((ioc_state & MPI_IOC_STATE_MASK) == MPI_IOC_STATE_READY)) अणु
		dinitprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_INFO_FMT
		    "IOC is in READY state\n", ioc->name));
		वापस 0;
	पूर्ण

	/*
	 *	Check to see अगर IOC is in FAULT state.
	 */
	अगर ((ioc_state & MPI_IOC_STATE_MASK) == MPI_IOC_STATE_FAULT) अणु
		statefault = 2;
		prपूर्णांकk(MYIOC_s_WARN_FMT "IOC is in FAULT state!!!\n",
		    ioc->name);
		prपूर्णांकk(MYIOC_s_WARN_FMT "           FAULT code = %04xh\n",
		    ioc->name, ioc_state & MPI_DOORBELL_DATA_MASK);
	पूर्ण

	/*
	 *	Hmmm...  Did it get left operational?
	 */
	अगर ((ioc_state & MPI_IOC_STATE_MASK) == MPI_IOC_STATE_OPERATIONAL) अणु
		dinitprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT "IOC operational unexpected\n",
				ioc->name));

		/* Check WhoInit.
		 * If PCI Peer, निकास.
		 * Else, अगर no fault conditions are present, issue a MessageUnitReset
		 * Else, fall through to KickStart हाल
		 */
		whoinit = (ioc_state & MPI_DOORBELL_WHO_INIT_MASK) >> MPI_DOORBELL_WHO_INIT_SHIFT;
		dinitprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_INFO_FMT
			"whoinit 0x%x statefault %d force %d\n",
			ioc->name, whoinit, statefault, क्रमce));
		अगर (whoinit == MPI_WHOINIT_PCI_PEER)
			वापस -4;
		अन्यथा अणु
			अगर ((statefault == 0 ) && (क्रमce == 0)) अणु
				अगर ((r = SendIocReset(ioc, MPI_FUNCTION_IOC_MESSAGE_UNIT_RESET, sleepFlag)) == 0)
					वापस 0;
			पूर्ण
			statefault = 3;
		पूर्ण
	पूर्ण

	hard_reset_करोne = KickStart(ioc, statefault||क्रमce, sleepFlag);
	अगर (hard_reset_करोne < 0)
		वापस -1;

	/*
	 *  Loop here रुकोing क्रम IOC to come READY.
	 */
	ii = 0;
	cntdn = ((sleepFlag == CAN_SLEEP) ? HZ : 1000) * 5;	/* 5 seconds */

	जबतक ((ioc_state = mpt_GetIocState(ioc, 1)) != MPI_IOC_STATE_READY) अणु
		अगर (ioc_state == MPI_IOC_STATE_OPERATIONAL) अणु
			/*
			 *  BIOS or previous driver load left IOC in OP state.
			 *  Reset messaging FIFOs.
			 */
			अगर ((r = SendIocReset(ioc, MPI_FUNCTION_IOC_MESSAGE_UNIT_RESET, sleepFlag)) != 0) अणु
				prपूर्णांकk(MYIOC_s_ERR_FMT "IOC msg unit reset failed!\n", ioc->name);
				वापस -2;
			पूर्ण
		पूर्ण अन्यथा अगर (ioc_state == MPI_IOC_STATE_RESET) अणु
			/*
			 *  Something is wrong.  Try to get IOC back
			 *  to a known state.
			 */
			अगर ((r = SendIocReset(ioc, MPI_FUNCTION_IO_UNIT_RESET, sleepFlag)) != 0) अणु
				prपूर्णांकk(MYIOC_s_ERR_FMT "IO unit reset failed!\n", ioc->name);
				वापस -3;
			पूर्ण
		पूर्ण

		ii++; cntdn--;
		अगर (!cntdn) अणु
			prपूर्णांकk(MYIOC_s_ERR_FMT
				"Wait IOC_READY state (0x%x) timeout(%d)!\n",
				ioc->name, ioc_state, (पूर्णांक)((ii+5)/HZ));
			वापस -ETIME;
		पूर्ण

		अगर (sleepFlag == CAN_SLEEP) अणु
			msleep(1);
		पूर्ण अन्यथा अणु
			mdelay (1);	/* 1 msec delay */
		पूर्ण

	पूर्ण

	अगर (statefault < 3) अणु
		prपूर्णांकk(MYIOC_s_INFO_FMT "Recovered from %s\n", ioc->name,
			statefault == 1 ? "stuck handshake" : "IOC FAULT");
	पूर्ण

	वापस hard_reset_करोne;
पूर्ण

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/**
 *	mpt_GetIocState - Get the current state of a MPT adapter.
 *	@ioc: Poपूर्णांकer to MPT_ADAPTER काष्ठाure
 *	@cooked: Request raw or cooked IOC state
 *
 *	Returns all IOC Doorbell रेजिस्टर bits अगर cooked==0, अन्यथा just the
 *	Doorbell bits in MPI_IOC_STATE_MASK.
 */
u32
mpt_GetIocState(MPT_ADAPTER *ioc, पूर्णांक cooked)
अणु
	u32 s, sc;

	/*  Get!  */
	s = CHIPREG_READ32(&ioc->chip->Doorbell);
	sc = s & MPI_IOC_STATE_MASK;

	/*  Save!  */
	ioc->last_state = sc;

	वापस cooked ? sc : s;
पूर्ण

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/**
 *	GetIocFacts - Send IOCFacts request to MPT adapter.
 *	@ioc: Poपूर्णांकer to MPT_ADAPTER काष्ठाure
 *	@sleepFlag: Specअगरies whether the process can sleep
 *	@reason: If recovery, only update facts.
 *
 *	Returns 0 क्रम success, non-zero क्रम failure.
 */
अटल पूर्णांक
GetIocFacts(MPT_ADAPTER *ioc, पूर्णांक sleepFlag, पूर्णांक reason)
अणु
	IOCFacts_t		 get_facts;
	IOCFactsReply_t		*facts;
	पूर्णांक			 r;
	पूर्णांक			 req_sz;
	पूर्णांक			 reply_sz;
	पूर्णांक			 sz;
	u32			 vv;
	u8			 shअगरtFactor=1;

	/* IOC *must* NOT be in RESET state! */
	अगर (ioc->last_state == MPI_IOC_STATE_RESET) अणु
		prपूर्णांकk(KERN_ERR MYNAM
		    ": ERROR - Can't get IOCFacts, %s NOT READY! (%08x)\n",
		    ioc->name, ioc->last_state);
		वापस -44;
	पूर्ण

	facts = &ioc->facts;

	/* Destination (reply area)... */
	reply_sz = माप(*facts);
	स_रखो(facts, 0, reply_sz);

	/* Request area (get_facts on the stack right now!) */
	req_sz = माप(get_facts);
	स_रखो(&get_facts, 0, req_sz);

	get_facts.Function = MPI_FUNCTION_IOC_FACTS;
	/* Assert: All other get_facts fields are zero! */

	dinitprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT
	    "Sending get IocFacts request req_sz=%d reply_sz=%d\n",
	    ioc->name, req_sz, reply_sz));

	/* No non-zero fields in the get_facts request are greater than
	 * 1 byte in size, so we can just fire it off as is.
	 */
	r = mpt_handshake_req_reply_रुको(ioc, req_sz, (u32*)&get_facts,
			reply_sz, (u16*)facts, 5 /*seconds*/, sleepFlag);
	अगर (r != 0)
		वापस r;

	/*
	 * Now byte swap (GRRR) the necessary fields beक्रमe any further
	 * inspection of reply contents.
	 *
	 * But need to करो some sanity checks on MsgLength (byte) field
	 * to make sure we करोn't zero IOC's req_sz!
	 */
	/* Did we get a valid reply? */
	अगर (facts->MsgLength > दुरत्व(IOCFactsReply_t, RequestFrameSize)/माप(u32)) अणु
		अगर (reason == MPT_HOSTEVENT_IOC_BRINGUP) अणु
			/*
			 * If not been here, करोne that, save off first WhoInit value
			 */
			अगर (ioc->FirstWhoInit == WHOINIT_UNKNOWN)
				ioc->FirstWhoInit = facts->WhoInit;
		पूर्ण

		facts->MsgVersion = le16_to_cpu(facts->MsgVersion);
		facts->MsgContext = le32_to_cpu(facts->MsgContext);
		facts->IOCExceptions = le16_to_cpu(facts->IOCExceptions);
		facts->IOCStatus = le16_to_cpu(facts->IOCStatus);
		facts->IOCLogInfo = le32_to_cpu(facts->IOCLogInfo);
		/* CHECKME! IOCStatus, IOCLogInfo */

		facts->ReplyQueueDepth = le16_to_cpu(facts->ReplyQueueDepth);
		facts->RequestFrameSize = le16_to_cpu(facts->RequestFrameSize);

		/*
		 * FC f/w version changed between 1.1 and 1.2
		 *	Old: u16अणुMajor(4),Minor(4),SubMinor(8)पूर्ण
		 *	New: u32अणुMajor(8),Minor(8),Unit(8),Dev(8)पूर्ण
		 */
		अगर (facts->MsgVersion < MPI_VERSION_01_02) अणु
			/*
			 *	Handle old FC f/w style, convert to new...
			 */
			u16	 oldv = le16_to_cpu(facts->Reserved_0101_FWVersion);
			facts->FWVersion.Word =
					((oldv<<12) & 0xFF000000) |
					((oldv<<8)  & 0x000FFF00);
		पूर्ण अन्यथा
			facts->FWVersion.Word = le32_to_cpu(facts->FWVersion.Word);

		facts->ProductID = le16_to_cpu(facts->ProductID);

		अगर ((ioc->facts.ProductID & MPI_FW_HEADER_PID_PROD_MASK)
		    > MPI_FW_HEADER_PID_PROD_TARGET_SCSI)
			ioc->ir_firmware = 1;

		facts->CurrentHostMfaHighAddr =
				le32_to_cpu(facts->CurrentHostMfaHighAddr);
		facts->GlobalCredits = le16_to_cpu(facts->GlobalCredits);
		facts->CurrentSenseBufferHighAddr =
				le32_to_cpu(facts->CurrentSenseBufferHighAddr);
		facts->CurReplyFrameSize =
				le16_to_cpu(facts->CurReplyFrameSize);
		facts->IOCCapabilities = le32_to_cpu(facts->IOCCapabilities);

		/*
		 * Handle NEW (!) IOCFactsReply fields in MPI-1.01.xx
		 * Older MPI-1.00.xx काष्ठा had 13 dwords, and enlarged
		 * to 14 in MPI-1.01.0x.
		 */
		अगर (facts->MsgLength >= (दुरत्व(IOCFactsReply_t,FWImageSize) + 7)/4 &&
		    facts->MsgVersion > MPI_VERSION_01_00) अणु
			facts->FWImageSize = le32_to_cpu(facts->FWImageSize);
		पूर्ण

		facts->FWImageSize = ALIGN(facts->FWImageSize, 4);

		अगर (!facts->RequestFrameSize) अणु
			/*  Something is wrong!  */
			prपूर्णांकk(MYIOC_s_ERR_FMT "IOC reported invalid 0 request size!\n",
					ioc->name);
			वापस -55;
		पूर्ण

		r = sz = facts->BlockSize;
		vv = ((63 / (sz * 4)) + 1) & 0x03;
		ioc->NB_क्रम_64_byte_frame = vv;
		जबतक ( sz )
		अणु
			shअगरtFactor++;
			sz = sz >> 1;
		पूर्ण
		ioc->NBShअगरtFactor  = shअगरtFactor;
		dinitprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT
		    "NB_for_64_byte_frame=%x NBShiftFactor=%x BlockSize=%x\n",
		    ioc->name, vv, shअगरtFactor, r));

		अगर (reason == MPT_HOSTEVENT_IOC_BRINGUP) अणु
			/*
			 * Set values क्रम this IOC's request & reply frame sizes,
			 * and request & reply queue depths...
			 */
			ioc->req_sz = min(MPT_DEFAULT_FRAME_SIZE, facts->RequestFrameSize * 4);
			ioc->req_depth = min_t(पूर्णांक, MPT_MAX_REQ_DEPTH, facts->GlobalCredits);
			ioc->reply_sz = MPT_REPLY_FRAME_SIZE;
			ioc->reply_depth = min_t(पूर्णांक, MPT_DEFAULT_REPLY_DEPTH, facts->ReplyQueueDepth);

			dinitprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT "reply_sz=%3d, reply_depth=%4d\n",
				ioc->name, ioc->reply_sz, ioc->reply_depth));
			dinitprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT "req_sz  =%3d, req_depth  =%4d\n",
				ioc->name, ioc->req_sz, ioc->req_depth));

			/* Get port facts! */
			अगर ( (r = GetPortFacts(ioc, 0, sleepFlag)) != 0 )
				वापस r;
		पूर्ण
	पूर्ण अन्यथा अणु
		prपूर्णांकk(MYIOC_s_ERR_FMT
		     "Invalid IOC facts reply, msgLength=%d offsetof=%zd!\n",
		     ioc->name, facts->MsgLength, (दुरत्व(IOCFactsReply_t,
		     RequestFrameSize)/माप(u32)));
		वापस -66;
	पूर्ण

	वापस 0;
पूर्ण

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/**
 *	GetPortFacts - Send PortFacts request to MPT adapter.
 *	@ioc: Poपूर्णांकer to MPT_ADAPTER काष्ठाure
 *	@portnum: Port number
 *	@sleepFlag: Specअगरies whether the process can sleep
 *
 *	Returns 0 क्रम success, non-zero क्रम failure.
 */
अटल पूर्णांक
GetPortFacts(MPT_ADAPTER *ioc, पूर्णांक portnum, पूर्णांक sleepFlag)
अणु
	PortFacts_t		 get_pfacts;
	PortFactsReply_t	*pfacts;
	पूर्णांक			 ii;
	पूर्णांक			 req_sz;
	पूर्णांक			 reply_sz;
	पूर्णांक			 max_id;

	/* IOC *must* NOT be in RESET state! */
	अगर (ioc->last_state == MPI_IOC_STATE_RESET) अणु
		prपूर्णांकk(MYIOC_s_ERR_FMT "Can't get PortFacts NOT READY! (%08x)\n",
		    ioc->name, ioc->last_state );
		वापस -4;
	पूर्ण

	pfacts = &ioc->pfacts[portnum];

	/* Destination (reply area)...  */
	reply_sz = माप(*pfacts);
	स_रखो(pfacts, 0, reply_sz);

	/* Request area (get_pfacts on the stack right now!) */
	req_sz = माप(get_pfacts);
	स_रखो(&get_pfacts, 0, req_sz);

	get_pfacts.Function = MPI_FUNCTION_PORT_FACTS;
	get_pfacts.PortNumber = portnum;
	/* Assert: All other get_pfacts fields are zero! */

	dinitprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT "Sending get PortFacts(%d) request\n",
			ioc->name, portnum));

	/* No non-zero fields in the get_pfacts request are greater than
	 * 1 byte in size, so we can just fire it off as is.
	 */
	ii = mpt_handshake_req_reply_रुको(ioc, req_sz, (u32*)&get_pfacts,
				reply_sz, (u16*)pfacts, 5 /*seconds*/, sleepFlag);
	अगर (ii != 0)
		वापस ii;

	/* Did we get a valid reply? */

	/* Now byte swap the necessary fields in the response. */
	pfacts->MsgContext = le32_to_cpu(pfacts->MsgContext);
	pfacts->IOCStatus = le16_to_cpu(pfacts->IOCStatus);
	pfacts->IOCLogInfo = le32_to_cpu(pfacts->IOCLogInfo);
	pfacts->MaxDevices = le16_to_cpu(pfacts->MaxDevices);
	pfacts->PortSCSIID = le16_to_cpu(pfacts->PortSCSIID);
	pfacts->ProtocolFlags = le16_to_cpu(pfacts->ProtocolFlags);
	pfacts->MaxPostedCmdBuffers = le16_to_cpu(pfacts->MaxPostedCmdBuffers);
	pfacts->MaxPersistentIDs = le16_to_cpu(pfacts->MaxPersistentIDs);
	pfacts->MaxLanBuckets = le16_to_cpu(pfacts->MaxLanBuckets);

	max_id = (ioc->bus_type == SAS) ? pfacts->PortSCSIID :
	    pfacts->MaxDevices;
	ioc->devices_per_bus = (max_id > 255) ? 256 : max_id;
	ioc->number_of_buses = (ioc->devices_per_bus < 256) ? 1 : max_id/256;

	/*
	 * Place all the devices on channels
	 *
	 * (क्रम debuging)
	 */
	अगर (mpt_channel_mapping) अणु
		ioc->devices_per_bus = 1;
		ioc->number_of_buses = (max_id > 255) ? 255 : max_id;
	पूर्ण

	वापस 0;
पूर्ण

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/**
 *	SendIocInit - Send IOCInit request to MPT adapter.
 *	@ioc: Poपूर्णांकer to MPT_ADAPTER काष्ठाure
 *	@sleepFlag: Specअगरies whether the process can sleep
 *
 *	Send IOCInit followed by PortEnable to bring IOC to OPERATIONAL state.
 *
 *	Returns 0 क्रम success, non-zero क्रम failure.
 */
अटल पूर्णांक
SendIocInit(MPT_ADAPTER *ioc, पूर्णांक sleepFlag)
अणु
	IOCInit_t		 ioc_init;
	MPIDefaultReply_t	 init_reply;
	u32			 state;
	पूर्णांक			 r;
	पूर्णांक			 count;
	पूर्णांक			 cntdn;

	स_रखो(&ioc_init, 0, माप(ioc_init));
	स_रखो(&init_reply, 0, माप(init_reply));

	ioc_init.WhoInit = MPI_WHOINIT_HOST_DRIVER;
	ioc_init.Function = MPI_FUNCTION_IOC_INIT;

	/* If we are in a recovery mode and we uploaded the FW image,
	 * then this poपूर्णांकer is not शून्य. Skip the upload a second समय.
	 * Set this flag अगर cached_fw set क्रम either IOC.
	 */
	अगर (ioc->facts.Flags & MPI_IOCFACTS_FLAGS_FW_DOWNLOAD_BOOT)
		ioc->upload_fw = 1;
	अन्यथा
		ioc->upload_fw = 0;
	ddlprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT "upload_fw %d facts.Flags=%x\n",
		   ioc->name, ioc->upload_fw, ioc->facts.Flags));

	ioc_init.MaxDevices = (U8)ioc->devices_per_bus;
	ioc_init.MaxBuses = (U8)ioc->number_of_buses;

	dinitprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT "facts.MsgVersion=%x\n",
		   ioc->name, ioc->facts.MsgVersion));
	अगर (ioc->facts.MsgVersion >= MPI_VERSION_01_05) अणु
		// set MsgVersion and HeaderVersion host driver was built with
		ioc_init.MsgVersion = cpu_to_le16(MPI_VERSION);
	        ioc_init.HeaderVersion = cpu_to_le16(MPI_HEADER_VERSION);

		अगर (ioc->facts.Flags & MPI_IOCFACTS_FLAGS_HOST_PAGE_BUFFER_PERSISTENT) अणु
			ioc_init.HostPageBufferSGE = ioc->facts.HostPageBufferSGE;
		पूर्ण अन्यथा अगर(mpt_host_page_alloc(ioc, &ioc_init))
			वापस -99;
	पूर्ण
	ioc_init.ReplyFrameSize = cpu_to_le16(ioc->reply_sz);	/* in BYTES */

	अगर (ioc->sg_addr_size == माप(u64)) अणु
		/* Save the upper 32-bits of the request
		 * (reply) and sense buffers.
		 */
		ioc_init.HostMfaHighAddr = cpu_to_le32((u32)((u64)ioc->alloc_dma >> 32));
		ioc_init.SenseBufferHighAddr = cpu_to_le32((u32)((u64)ioc->sense_buf_pool_dma >> 32));
	पूर्ण अन्यथा अणु
		/* Force 32-bit addressing */
		ioc_init.HostMfaHighAddr = cpu_to_le32(0);
		ioc_init.SenseBufferHighAddr = cpu_to_le32(0);
	पूर्ण

	ioc->facts.CurrentHostMfaHighAddr = ioc_init.HostMfaHighAddr;
	ioc->facts.CurrentSenseBufferHighAddr = ioc_init.SenseBufferHighAddr;
	ioc->facts.MaxDevices = ioc_init.MaxDevices;
	ioc->facts.MaxBuses = ioc_init.MaxBuses;

	dhsprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT "Sending IOCInit (req @ %p)\n",
			ioc->name, &ioc_init));

	r = mpt_handshake_req_reply_रुको(ioc, माप(IOCInit_t), (u32*)&ioc_init,
				माप(MPIDefaultReply_t), (u16*)&init_reply, 10 /*seconds*/, sleepFlag);
	अगर (r != 0) अणु
		prपूर्णांकk(MYIOC_s_ERR_FMT "Sending IOCInit failed(%d)!\n",ioc->name, r);
		वापस r;
	पूर्ण

	/* No need to byte swap the multibyte fields in the reply
	 * since we करोn't even look at its contents.
	 */

	dhsprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT "Sending PortEnable (req @ %p)\n",
			ioc->name, &ioc_init));

	अगर ((r = SendPortEnable(ioc, 0, sleepFlag)) != 0) अणु
		prपूर्णांकk(MYIOC_s_ERR_FMT "Sending PortEnable failed(%d)!\n",ioc->name, r);
		वापस r;
	पूर्ण

	/* YIKES!  SUPER IMPORTANT!!!
	 *  Poll IocState until _OPERATIONAL जबतक IOC is करोing
	 *  LoopInit and TargetDiscovery!
	 */
	count = 0;
	cntdn = ((sleepFlag == CAN_SLEEP) ? HZ : 1000) * 60;	/* 60 seconds */
	state = mpt_GetIocState(ioc, 1);
	जबतक (state != MPI_IOC_STATE_OPERATIONAL && --cntdn) अणु
		अगर (sleepFlag == CAN_SLEEP) अणु
			msleep(1);
		पूर्ण अन्यथा अणु
			mdelay(1);
		पूर्ण

		अगर (!cntdn) अणु
			prपूर्णांकk(MYIOC_s_ERR_FMT "Wait IOC_OP state timeout(%d)!\n",
					ioc->name, (पूर्णांक)((count+5)/HZ));
			वापस -9;
		पूर्ण

		state = mpt_GetIocState(ioc, 1);
		count++;
	पूर्ण
	dinitprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT "Wait IOC_OPERATIONAL state (cnt=%d)\n",
			ioc->name, count));

	ioc->aen_event_पढ़ो_flag=0;
	वापस r;
पूर्ण

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/**
 *	SendPortEnable - Send PortEnable request to MPT adapter port.
 *	@ioc: Poपूर्णांकer to MPT_ADAPTER काष्ठाure
 *	@portnum: Port number to enable
 *	@sleepFlag: Specअगरies whether the process can sleep
 *
 *	Send PortEnable to bring IOC to OPERATIONAL state.
 *
 *	Returns 0 क्रम success, non-zero क्रम failure.
 */
अटल पूर्णांक
SendPortEnable(MPT_ADAPTER *ioc, पूर्णांक portnum, पूर्णांक sleepFlag)
अणु
	PortEnable_t		 port_enable;
	MPIDefaultReply_t	 reply_buf;
	पूर्णांक	 rc;
	पूर्णांक	 req_sz;
	पूर्णांक	 reply_sz;

	/*  Destination...  */
	reply_sz = माप(MPIDefaultReply_t);
	स_रखो(&reply_buf, 0, reply_sz);

	req_sz = माप(PortEnable_t);
	स_रखो(&port_enable, 0, req_sz);

	port_enable.Function = MPI_FUNCTION_PORT_ENABLE;
	port_enable.PortNumber = portnum;
/*	port_enable.ChainOffset = 0;		*/
/*	port_enable.MsgFlags = 0;		*/
/*	port_enable.MsgContext = 0;		*/

	dinitprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT "Sending Port(%d)Enable (req @ %p)\n",
			ioc->name, portnum, &port_enable));

	/* RAID FW may take a दीर्घ समय to enable
	 */
	अगर (ioc->ir_firmware || ioc->bus_type == SAS) अणु
		rc = mpt_handshake_req_reply_रुको(ioc, req_sz,
		(u32*)&port_enable, reply_sz, (u16*)&reply_buf,
		300 /*seconds*/, sleepFlag);
	पूर्ण अन्यथा अणु
		rc = mpt_handshake_req_reply_रुको(ioc, req_sz,
		(u32*)&port_enable, reply_sz, (u16*)&reply_buf,
		30 /*seconds*/, sleepFlag);
	पूर्ण
	वापस rc;
पूर्ण

/**
 *	mpt_alloc_fw_memory - allocate firmware memory
 *	@ioc: Poपूर्णांकer to MPT_ADAPTER काष्ठाure
 *      @size: total FW bytes
 *
 *	If memory has alपढ़ोy been allocated, the same (cached) value
 *	is वापसed.
 *
 *	Return 0 अगर successful, or non-zero क्रम failure
 **/
पूर्णांक
mpt_alloc_fw_memory(MPT_ADAPTER *ioc, पूर्णांक size)
अणु
	पूर्णांक rc;

	अगर (ioc->cached_fw) अणु
		rc = 0;  /* use alपढ़ोy allocated memory */
		जाओ out;
	पूर्ण
	अन्यथा अगर (ioc->alt_ioc && ioc->alt_ioc->cached_fw) अणु
		ioc->cached_fw = ioc->alt_ioc->cached_fw;  /* use alt_ioc's memory */
		ioc->cached_fw_dma = ioc->alt_ioc->cached_fw_dma;
		rc = 0;
		जाओ out;
	पूर्ण
	ioc->cached_fw = pci_alloc_consistent(ioc->pcidev, size, &ioc->cached_fw_dma);
	अगर (!ioc->cached_fw) अणु
		prपूर्णांकk(MYIOC_s_ERR_FMT "Unable to allocate memory for the cached firmware image!\n",
		    ioc->name);
		rc = -1;
	पूर्ण अन्यथा अणु
		dinitprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT "FW Image  @ %p[%p], sz=%d[%x] bytes\n",
		    ioc->name, ioc->cached_fw, (व्योम *)(uदीर्घ)ioc->cached_fw_dma, size, size));
		ioc->alloc_total += size;
		rc = 0;
	पूर्ण
 out:
	वापस rc;
पूर्ण

/**
 *	mpt_मुक्त_fw_memory - मुक्त firmware memory
 *	@ioc: Poपूर्णांकer to MPT_ADAPTER काष्ठाure
 *
 *	If alt_img is शून्य, delete from ioc काष्ठाure.
 *	Else, delete a secondary image in same क्रमmat.
 **/
व्योम
mpt_मुक्त_fw_memory(MPT_ADAPTER *ioc)
अणु
	पूर्णांक sz;

	अगर (!ioc->cached_fw)
		वापस;

	sz = ioc->facts.FWImageSize;
	dinitprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT "free_fw_memory: FW Image  @ %p[%p], sz=%d[%x] bytes\n",
		 ioc->name, ioc->cached_fw, (व्योम *)(uदीर्घ)ioc->cached_fw_dma, sz, sz));
	pci_मुक्त_consistent(ioc->pcidev, sz, ioc->cached_fw, ioc->cached_fw_dma);
	ioc->alloc_total -= sz;
	ioc->cached_fw = शून्य;
पूर्ण

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/**
 *	mpt_करो_upload - Conकाष्ठा and Send FWUpload request to MPT adapter port.
 *	@ioc: Poपूर्णांकer to MPT_ADAPTER काष्ठाure
 *	@sleepFlag: Specअगरies whether the process can sleep
 *
 *	Returns 0 क्रम success, >0 क्रम handshake failure
 *		<0 क्रम fw upload failure.
 *
 *	Remark: If bound IOC and a successful FWUpload was perक्रमmed
 *	on the bound IOC, the second image is discarded
 *	and memory is मुक्त'd. Both channels must upload to prevent
 *	IOC from running in degraded mode.
 */
अटल पूर्णांक
mpt_करो_upload(MPT_ADAPTER *ioc, पूर्णांक sleepFlag)
अणु
	u8			 reply[माप(FWUploadReply_t)];
	FWUpload_t		*prequest;
	FWUploadReply_t		*preply;
	FWUploadTCSGE_t		*ptcsge;
	u32			 flagsLength;
	पूर्णांक			 ii, sz, reply_sz;
	पूर्णांक			 cmdStatus;
	पूर्णांक			request_size;
	/* If the image size is 0, we are करोne.
	 */
	अगर ((sz = ioc->facts.FWImageSize) == 0)
		वापस 0;

	अगर (mpt_alloc_fw_memory(ioc, ioc->facts.FWImageSize) != 0)
		वापस -ENOMEM;

	dinitprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_INFO_FMT ": FW Image  @ %p[%p], sz=%d[%x] bytes\n",
	    ioc->name, ioc->cached_fw, (व्योम *)(uदीर्घ)ioc->cached_fw_dma, sz, sz));

	prequest = (sleepFlag == NO_SLEEP) ? kzalloc(ioc->req_sz, GFP_ATOMIC) :
	    kzalloc(ioc->req_sz, GFP_KERNEL);
	अगर (!prequest) अणु
		dinitprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT "fw upload failed "
		    "while allocating memory \n", ioc->name));
		mpt_मुक्त_fw_memory(ioc);
		वापस -ENOMEM;
	पूर्ण

	preply = (FWUploadReply_t *)&reply;

	reply_sz = माप(reply);
	स_रखो(preply, 0, reply_sz);

	prequest->ImageType = MPI_FW_UPLOAD_ITYPE_FW_IOC_MEM;
	prequest->Function = MPI_FUNCTION_FW_UPLOAD;

	ptcsge = (FWUploadTCSGE_t *) &prequest->SGL;
	ptcsge->DetailsLength = 12;
	ptcsge->Flags = MPI_SGE_FLAGS_TRANSACTION_ELEMENT;
	ptcsge->ImageSize = cpu_to_le32(sz);
	ptcsge++;

	flagsLength = MPT_SGE_FLAGS_SSIMPLE_READ | sz;
	ioc->add_sge((अक्षर *)ptcsge, flagsLength, ioc->cached_fw_dma);
	request_size = दुरत्व(FWUpload_t, SGL) + माप(FWUploadTCSGE_t) +
	    ioc->SGE_size;
	dinitprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT "Sending FW Upload "
	    " (req @ %p) fw_size=%d mf_request_size=%d\n", ioc->name, prequest,
	    ioc->facts.FWImageSize, request_size));
	DBG_DUMP_FW_REQUEST_FRAME(ioc, (u32 *)prequest);

	ii = mpt_handshake_req_reply_रुको(ioc, request_size, (u32 *)prequest,
	    reply_sz, (u16 *)preply, 65 /*seconds*/, sleepFlag);

	dinitprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT "FW Upload completed "
	    "rc=%x \n", ioc->name, ii));

	cmdStatus = -EFAULT;
	अगर (ii == 0) अणु
		/* Handshake transfer was complete and successful.
		 * Check the Reply Frame.
		 */
		पूर्णांक status;
		status = le16_to_cpu(preply->IOCStatus) &
				MPI_IOCSTATUS_MASK;
		अगर (status == MPI_IOCSTATUS_SUCCESS &&
		    ioc->facts.FWImageSize ==
		    le32_to_cpu(preply->ActualImageSize))
				cmdStatus = 0;
	पूर्ण
	dinitprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT ": do_upload cmdStatus=%d \n",
			ioc->name, cmdStatus));


	अगर (cmdStatus) अणु
		ddlprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT "fw upload failed, "
		    "freeing image \n", ioc->name));
		mpt_मुक्त_fw_memory(ioc);
	पूर्ण
	kमुक्त(prequest);

	वापस cmdStatus;
पूर्ण

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/**
 *	mpt_करोwnloadboot - DownloadBoot code
 *	@ioc: Poपूर्णांकer to MPT_ADAPTER काष्ठाure
 *	@pFwHeader: Poपूर्णांकer to firmware header info
 *	@sleepFlag: Specअगरies whether the process can sleep
 *
 *	FwDownloadBoot requires Programmed IO access.
 *
 *	Returns 0 क्रम success
 *		-1 FW Image size is 0
 *		-2 No valid cached_fw Poपूर्णांकer
 *		<0 क्रम fw upload failure.
 */
अटल पूर्णांक
mpt_करोwnloadboot(MPT_ADAPTER *ioc, MpiFwHeader_t *pFwHeader, पूर्णांक sleepFlag)
अणु
	MpiExtImageHeader_t	*pExtImage;
	u32			 fwSize;
	u32			 diag0val;
	पूर्णांक			 count;
	u32			*ptrFw;
	u32			 diagRwData;
	u32			 nextImage;
	u32			 load_addr;
	u32 			 ioc_state=0;

	ddlprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT "downloadboot: fw size 0x%x (%d), FW Ptr %p\n",
				ioc->name, pFwHeader->ImageSize, pFwHeader->ImageSize, pFwHeader));

	CHIPREG_WRITE32(&ioc->chip->WriteSequence, 0xFF);
	CHIPREG_WRITE32(&ioc->chip->WriteSequence, MPI_WRSEQ_1ST_KEY_VALUE);
	CHIPREG_WRITE32(&ioc->chip->WriteSequence, MPI_WRSEQ_2ND_KEY_VALUE);
	CHIPREG_WRITE32(&ioc->chip->WriteSequence, MPI_WRSEQ_3RD_KEY_VALUE);
	CHIPREG_WRITE32(&ioc->chip->WriteSequence, MPI_WRSEQ_4TH_KEY_VALUE);
	CHIPREG_WRITE32(&ioc->chip->WriteSequence, MPI_WRSEQ_5TH_KEY_VALUE);

	CHIPREG_WRITE32(&ioc->chip->Diagnostic, (MPI_DIAG_PREVENT_IOC_BOOT | MPI_DIAG_DISABLE_ARM));

	/* रुको 1 msec */
	अगर (sleepFlag == CAN_SLEEP) अणु
		msleep(1);
	पूर्ण अन्यथा अणु
		mdelay (1);
	पूर्ण

	diag0val = CHIPREG_READ32(&ioc->chip->Diagnostic);
	CHIPREG_WRITE32(&ioc->chip->Diagnostic, diag0val | MPI_DIAG_RESET_ADAPTER);

	क्रम (count = 0; count < 30; count ++) अणु
		diag0val = CHIPREG_READ32(&ioc->chip->Diagnostic);
		अगर (!(diag0val & MPI_DIAG_RESET_ADAPTER)) अणु
			ddlprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT "RESET_ADAPTER cleared, count=%d\n",
				ioc->name, count));
			अवरोध;
		पूर्ण
		/* रुको .1 sec */
		अगर (sleepFlag == CAN_SLEEP) अणु
			msleep (100);
		पूर्ण अन्यथा अणु
			mdelay (100);
		पूर्ण
	पूर्ण

	अगर ( count == 30 ) अणु
		ddlprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT "downloadboot failed! "
		"Unable to get MPI_DIAG_DRWE mode, diag0val=%x\n",
		ioc->name, diag0val));
		वापस -3;
	पूर्ण

	CHIPREG_WRITE32(&ioc->chip->WriteSequence, 0xFF);
	CHIPREG_WRITE32(&ioc->chip->WriteSequence, MPI_WRSEQ_1ST_KEY_VALUE);
	CHIPREG_WRITE32(&ioc->chip->WriteSequence, MPI_WRSEQ_2ND_KEY_VALUE);
	CHIPREG_WRITE32(&ioc->chip->WriteSequence, MPI_WRSEQ_3RD_KEY_VALUE);
	CHIPREG_WRITE32(&ioc->chip->WriteSequence, MPI_WRSEQ_4TH_KEY_VALUE);
	CHIPREG_WRITE32(&ioc->chip->WriteSequence, MPI_WRSEQ_5TH_KEY_VALUE);

	/* Set the DiagRwEn and Disable ARM bits */
	CHIPREG_WRITE32(&ioc->chip->Diagnostic, (MPI_DIAG_RW_ENABLE | MPI_DIAG_DISABLE_ARM));

	fwSize = (pFwHeader->ImageSize + 3)/4;
	ptrFw = (u32 *) pFwHeader;

	/* Write the LoadStartAddress to the DiagRw Address Register
	 * using Programmed IO
	 */
	अगर (ioc->errata_flag_1064)
		pci_enable_io_access(ioc->pcidev);

	CHIPREG_PIO_WRITE32(&ioc->pio_chip->DiagRwAddress, pFwHeader->LoadStartAddress);
	ddlprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT "LoadStart addr written 0x%x \n",
		ioc->name, pFwHeader->LoadStartAddress));

	ddlprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT "Write FW Image: 0x%x bytes @ %p\n",
				ioc->name, fwSize*4, ptrFw));
	जबतक (fwSize--) अणु
		CHIPREG_PIO_WRITE32(&ioc->pio_chip->DiagRwData, *ptrFw++);
	पूर्ण

	nextImage = pFwHeader->NextImageHeaderOffset;
	जबतक (nextImage) अणु
		pExtImage = (MpiExtImageHeader_t *) ((अक्षर *)pFwHeader + nextImage);

		load_addr = pExtImage->LoadStartAddress;

		fwSize = (pExtImage->ImageSize + 3) >> 2;
		ptrFw = (u32 *)pExtImage;

		ddlprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT "Write Ext Image: 0x%x (%d) bytes @ %p load_addr=%x\n",
						ioc->name, fwSize*4, fwSize*4, ptrFw, load_addr));
		CHIPREG_PIO_WRITE32(&ioc->pio_chip->DiagRwAddress, load_addr);

		जबतक (fwSize--) अणु
			CHIPREG_PIO_WRITE32(&ioc->pio_chip->DiagRwData, *ptrFw++);
		पूर्ण
		nextImage = pExtImage->NextImageHeaderOffset;
	पूर्ण

	/* Write the IopResetVectorRegAddr */
	ddlprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT "Write IopResetVector Addr=%x! \n", ioc->name, 	pFwHeader->IopResetRegAddr));
	CHIPREG_PIO_WRITE32(&ioc->pio_chip->DiagRwAddress, pFwHeader->IopResetRegAddr);

	/* Write the IopResetVectorValue */
	ddlprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT "Write IopResetVector Value=%x! \n", ioc->name, pFwHeader->IopResetVectorValue));
	CHIPREG_PIO_WRITE32(&ioc->pio_chip->DiagRwData, pFwHeader->IopResetVectorValue);

	/* Clear the पूर्णांकernal flash bad bit - स्वतःincrementing रेजिस्टर,
	 * so must करो two ग_लिखोs.
	 */
	अगर (ioc->bus_type == SPI) अणु
		/*
		 * 1030 and 1035 H/W errata, workaround to access
		 * the ClearFlashBadSignatureBit
		 */
		CHIPREG_PIO_WRITE32(&ioc->pio_chip->DiagRwAddress, 0x3F000000);
		diagRwData = CHIPREG_PIO_READ32(&ioc->pio_chip->DiagRwData);
		diagRwData |= 0x40000000;
		CHIPREG_PIO_WRITE32(&ioc->pio_chip->DiagRwAddress, 0x3F000000);
		CHIPREG_PIO_WRITE32(&ioc->pio_chip->DiagRwData, diagRwData);

	पूर्ण अन्यथा /* अगर((ioc->bus_type == SAS) || (ioc->bus_type == FC)) */ अणु
		diag0val = CHIPREG_READ32(&ioc->chip->Diagnostic);
		CHIPREG_WRITE32(&ioc->chip->Diagnostic, diag0val |
		    MPI_DIAG_CLEAR_FLASH_BAD_SIG);

		/* रुको 1 msec */
		अगर (sleepFlag == CAN_SLEEP) अणु
			msleep (1);
		पूर्ण अन्यथा अणु
			mdelay (1);
		पूर्ण
	पूर्ण

	अगर (ioc->errata_flag_1064)
		pci_disable_io_access(ioc->pcidev);

	diag0val = CHIPREG_READ32(&ioc->chip->Diagnostic);
	ddlprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT "downloadboot diag0val=%x, "
		"turning off PREVENT_IOC_BOOT, DISABLE_ARM, RW_ENABLE\n",
		ioc->name, diag0val));
	diag0val &= ~(MPI_DIAG_PREVENT_IOC_BOOT | MPI_DIAG_DISABLE_ARM | MPI_DIAG_RW_ENABLE);
	ddlprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT "downloadboot now diag0val=%x\n",
		ioc->name, diag0val));
	CHIPREG_WRITE32(&ioc->chip->Diagnostic, diag0val);

	/* Write 0xFF to reset the sequencer */
	CHIPREG_WRITE32(&ioc->chip->WriteSequence, 0xFF);

	अगर (ioc->bus_type == SAS) अणु
		ioc_state = mpt_GetIocState(ioc, 0);
		अगर ( (GetIocFacts(ioc, sleepFlag,
				MPT_HOSTEVENT_IOC_BRINGUP)) != 0 ) अणु
			ddlprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT "GetIocFacts failed: IocState=%x\n",
					ioc->name, ioc_state));
			वापस -EFAULT;
		पूर्ण
	पूर्ण

	क्रम (count=0; count<HZ*20; count++) अणु
		अगर ((ioc_state = mpt_GetIocState(ioc, 0)) & MPI_IOC_STATE_READY) अणु
			ddlprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT
				"downloadboot successful! (count=%d) IocState=%x\n",
				ioc->name, count, ioc_state));
			अगर (ioc->bus_type == SAS) अणु
				वापस 0;
			पूर्ण
			अगर ((SendIocInit(ioc, sleepFlag)) != 0) अणु
				ddlprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT
					"downloadboot: SendIocInit failed\n",
					ioc->name));
				वापस -EFAULT;
			पूर्ण
			ddlprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT
					"downloadboot: SendIocInit successful\n",
					ioc->name));
			वापस 0;
		पूर्ण
		अगर (sleepFlag == CAN_SLEEP) अणु
			msleep (10);
		पूर्ण अन्यथा अणु
			mdelay (10);
		पूर्ण
	पूर्ण
	ddlprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT
		"downloadboot failed! IocState=%x\n",ioc->name, ioc_state));
	वापस -EFAULT;
पूर्ण

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/**
 *	KickStart - Perक्रमm hard reset of MPT adapter.
 *	@ioc: Poपूर्णांकer to MPT_ADAPTER काष्ठाure
 *	@क्रमce: Force hard reset
 *	@sleepFlag: Specअगरies whether the process can sleep
 *
 *	This routine places MPT adapter in diagnostic mode via the
 *	WriteSequence रेजिस्टर, and then perक्रमms a hard reset of adapter
 *	via the Diagnostic रेजिस्टर.
 *
 *	Inमाला_दो:   sleepflag - CAN_SLEEP (non-पूर्णांकerrupt thपढ़ो)
 *			or NO_SLEEP (पूर्णांकerrupt thपढ़ो, use mdelay)
 *		  क्रमce - 1 अगर करोorbell active, board fault state
 *				board operational, IOC_RECOVERY or
 *				IOC_BRINGUP and there is an alt_ioc.
 *			  0 अन्यथा
 *
 *	Returns:
 *		 1 - hard reset, READY
 *		 0 - no reset due to History bit, READY
 *		-1 - no reset due to History bit but not READY
 *		     OR reset but failed to come READY
 *		-2 - no reset, could not enter DIAG mode
 *		-3 - reset but bad FW bit
 */
अटल पूर्णांक
KickStart(MPT_ADAPTER *ioc, पूर्णांक क्रमce, पूर्णांक sleepFlag)
अणु
	पूर्णांक hard_reset_करोne = 0;
	u32 ioc_state=0;
	पूर्णांक cnt,cntdn;

	dinitprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT "KickStarting!\n", ioc->name));
	अगर (ioc->bus_type == SPI) अणु
		/* Always issue a Msg Unit Reset first. This will clear some
		 * SCSI bus hang conditions.
		 */
		SendIocReset(ioc, MPI_FUNCTION_IOC_MESSAGE_UNIT_RESET, sleepFlag);

		अगर (sleepFlag == CAN_SLEEP) अणु
			msleep (1000);
		पूर्ण अन्यथा अणु
			mdelay (1000);
		पूर्ण
	पूर्ण

	hard_reset_करोne = mpt_diag_reset(ioc, क्रमce, sleepFlag);
	अगर (hard_reset_करोne < 0)
		वापस hard_reset_करोne;

	dinitprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT "Diagnostic reset successful!\n",
		ioc->name));

	cntdn = ((sleepFlag == CAN_SLEEP) ? HZ : 1000) * 2;	/* 2 seconds */
	क्रम (cnt=0; cnt<cntdn; cnt++) अणु
		ioc_state = mpt_GetIocState(ioc, 1);
		अगर ((ioc_state == MPI_IOC_STATE_READY) || (ioc_state == MPI_IOC_STATE_OPERATIONAL)) अणु
			dinitprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT "KickStart successful! (cnt=%d)\n",
 					ioc->name, cnt));
			वापस hard_reset_करोne;
		पूर्ण
		अगर (sleepFlag == CAN_SLEEP) अणु
			msleep (10);
		पूर्ण अन्यथा अणु
			mdelay (10);
		पूर्ण
	पूर्ण

	dinitprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_ERR_FMT "Failed to come READY after reset! IocState=%x\n",
		ioc->name, mpt_GetIocState(ioc, 0)));
	वापस -1;
पूर्ण

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/**
 *	mpt_diag_reset - Perक्रमm hard reset of the adapter.
 *	@ioc: Poपूर्णांकer to MPT_ADAPTER काष्ठाure
 *	@ignore: Set अगर to honor and clear to ignore
 *		the reset history bit
 *	@sleepFlag: CAN_SLEEP अगर called in a non-पूर्णांकerrupt thपढ़ो,
 *		अन्यथा set to NO_SLEEP (use mdelay instead)
 *
 *	This routine places the adapter in diagnostic mode via the
 *	WriteSequence रेजिस्टर and then perक्रमms a hard reset of adapter
 *	via the Diagnostic रेजिस्टर. Adapter should be in पढ़ोy state
 *	upon successful completion.
 *
 *	Returns:  1  hard reset successful
 *		  0  no reset perक्रमmed because reset history bit set
 *		 -2  enabling diagnostic mode failed
 *		 -3  diagnostic reset failed
 */
अटल पूर्णांक
mpt_diag_reset(MPT_ADAPTER *ioc, पूर्णांक ignore, पूर्णांक sleepFlag)
अणु
	u32 diag0val;
	u32 करोorbell;
	पूर्णांक hard_reset_करोne = 0;
	पूर्णांक count = 0;
	u32 diag1val = 0;
	MpiFwHeader_t *cached_fw;	/* Poपूर्णांकer to FW */
	u8	 cb_idx;

	/* Clear any existing पूर्णांकerrupts */
	CHIPREG_WRITE32(&ioc->chip->IntStatus, 0);

	अगर (ioc->pcidev->device == MPI_MANUFACTPAGE_DEVID_SAS1078) अणु

		अगर (!ignore)
			वापस 0;

		drsprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_WARN_FMT "%s: Doorbell=%p; 1078 reset "
			"address=%p\n",  ioc->name, __func__,
			&ioc->chip->Doorbell, &ioc->chip->Reset_1078));
		CHIPREG_WRITE32(&ioc->chip->Reset_1078, 0x07);
		अगर (sleepFlag == CAN_SLEEP)
			msleep(1);
		अन्यथा
			mdelay(1);

		/*
		 * Call each currently रेजिस्टरed protocol IOC reset handler
		 * with pre-reset indication.
		 * NOTE: If we're करोing _IOC_BRINGUP, there can be no
		 * MptResetHandlers[] रेजिस्टरed yet.
		 */
		क्रम (cb_idx = MPT_MAX_PROTOCOL_DRIVERS-1; cb_idx; cb_idx--) अणु
			अगर (MptResetHandlers[cb_idx])
				(*(MptResetHandlers[cb_idx]))(ioc,
						MPT_IOC_PRE_RESET);
		पूर्ण

		क्रम (count = 0; count < 60; count ++) अणु
			करोorbell = CHIPREG_READ32(&ioc->chip->Doorbell);
			करोorbell &= MPI_IOC_STATE_MASK;

			drsprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT
				"looking for READY STATE: doorbell=%x"
			        " count=%d\n",
				ioc->name, करोorbell, count));

			अगर (करोorbell == MPI_IOC_STATE_READY) अणु
				वापस 1;
			पूर्ण

			/* रुको 1 sec */
			अगर (sleepFlag == CAN_SLEEP)
				msleep(1000);
			अन्यथा
				mdelay(1000);
		पूर्ण
		वापस -1;
	पूर्ण

	/* Use "Diagnostic reset" method! (only thing available!) */
	diag0val = CHIPREG_READ32(&ioc->chip->Diagnostic);

	अगर (ioc->debug_level & MPT_DEBUG) अणु
		अगर (ioc->alt_ioc)
			diag1val = CHIPREG_READ32(&ioc->alt_ioc->chip->Diagnostic);
		dprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT "DbG1: diag0=%08x, diag1=%08x\n",
			ioc->name, diag0val, diag1val));
	पूर्ण

	/* Do the reset अगर we are told to ignore the reset history
	 * or अगर the reset history is 0
	 */
	अगर (ignore || !(diag0val & MPI_DIAG_RESET_HISTORY)) अणु
		जबतक ((diag0val & MPI_DIAG_DRWE) == 0) अणु
			/* Write magic sequence to WriteSequence रेजिस्टर
			 * Loop until in diagnostic mode
			 */
			CHIPREG_WRITE32(&ioc->chip->WriteSequence, 0xFF);
			CHIPREG_WRITE32(&ioc->chip->WriteSequence, MPI_WRSEQ_1ST_KEY_VALUE);
			CHIPREG_WRITE32(&ioc->chip->WriteSequence, MPI_WRSEQ_2ND_KEY_VALUE);
			CHIPREG_WRITE32(&ioc->chip->WriteSequence, MPI_WRSEQ_3RD_KEY_VALUE);
			CHIPREG_WRITE32(&ioc->chip->WriteSequence, MPI_WRSEQ_4TH_KEY_VALUE);
			CHIPREG_WRITE32(&ioc->chip->WriteSequence, MPI_WRSEQ_5TH_KEY_VALUE);

			/* रुको 100 msec */
			अगर (sleepFlag == CAN_SLEEP) अणु
				msleep (100);
			पूर्ण अन्यथा अणु
				mdelay (100);
			पूर्ण

			count++;
			अगर (count > 20) अणु
				prपूर्णांकk(MYIOC_s_ERR_FMT "Enable Diagnostic mode FAILED! (%02xh)\n",
						ioc->name, diag0val);
				वापस -2;

			पूर्ण

			diag0val = CHIPREG_READ32(&ioc->chip->Diagnostic);

			dprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT "Wrote magic DiagWriteEn sequence (%x)\n",
					ioc->name, diag0val));
		पूर्ण

		अगर (ioc->debug_level & MPT_DEBUG) अणु
			अगर (ioc->alt_ioc)
				diag1val = CHIPREG_READ32(&ioc->alt_ioc->chip->Diagnostic);
			dprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT "DbG2: diag0=%08x, diag1=%08x\n",
				ioc->name, diag0val, diag1val));
		पूर्ण
		/*
		 * Disable the ARM (Bug fix)
		 *
		 */
		CHIPREG_WRITE32(&ioc->chip->Diagnostic, diag0val | MPI_DIAG_DISABLE_ARM);
		mdelay(1);

		/*
		 * Now hit the reset bit in the Diagnostic रेजिस्टर
		 * (THE BIG HAMMER!) (Clears DRWE bit).
		 */
		CHIPREG_WRITE32(&ioc->chip->Diagnostic, diag0val | MPI_DIAG_RESET_ADAPTER);
		hard_reset_करोne = 1;
		dprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT "Diagnostic reset performed\n",
				ioc->name));

		/*
		 * Call each currently रेजिस्टरed protocol IOC reset handler
		 * with pre-reset indication.
		 * NOTE: If we're करोing _IOC_BRINGUP, there can be no
		 * MptResetHandlers[] रेजिस्टरed yet.
		 */
		क्रम (cb_idx = MPT_MAX_PROTOCOL_DRIVERS-1; cb_idx; cb_idx--) अणु
			अगर (MptResetHandlers[cb_idx]) अणु
				mpt_संकेत_reset(cb_idx,
					ioc, MPT_IOC_PRE_RESET);
				अगर (ioc->alt_ioc) अणु
					mpt_संकेत_reset(cb_idx,
					ioc->alt_ioc, MPT_IOC_PRE_RESET);
				पूर्ण
			पूर्ण
		पूर्ण

		अगर (ioc->cached_fw)
			cached_fw = (MpiFwHeader_t *)ioc->cached_fw;
		अन्यथा अगर (ioc->alt_ioc && ioc->alt_ioc->cached_fw)
			cached_fw = (MpiFwHeader_t *)ioc->alt_ioc->cached_fw;
		अन्यथा
			cached_fw = शून्य;
		अगर (cached_fw) अणु
			/* If the DownloadBoot operation fails, the
			 * IOC will be left unusable. This is a fatal error
			 * हाल.  _diag_reset will वापस < 0
			 */
			क्रम (count = 0; count < 30; count ++) अणु
				diag0val = CHIPREG_READ32(&ioc->chip->Diagnostic);
				अगर (!(diag0val & MPI_DIAG_RESET_ADAPTER)) अणु
					अवरोध;
				पूर्ण

				dprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT "cached_fw: diag0val=%x count=%d\n",
					ioc->name, diag0val, count));
				/* रुको 1 sec */
				अगर (sleepFlag == CAN_SLEEP) अणु
					msleep (1000);
				पूर्ण अन्यथा अणु
					mdelay (1000);
				पूर्ण
			पूर्ण
			अगर ((count = mpt_करोwnloadboot(ioc, cached_fw, sleepFlag)) < 0) अणु
				prपूर्णांकk(MYIOC_s_WARN_FMT
					"firmware downloadboot failure (%d)!\n", ioc->name, count);
			पूर्ण

		पूर्ण अन्यथा अणु
			/* Wait क्रम FW to reload and क्रम board
			 * to go to the READY state.
			 * Maximum रुको is 60 seconds.
			 * If fail, no error will check again
			 * with calling program.
			 */
			क्रम (count = 0; count < 60; count ++) अणु
				करोorbell = CHIPREG_READ32(&ioc->chip->Doorbell);
				करोorbell &= MPI_IOC_STATE_MASK;

				drsprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT
				    "looking for READY STATE: doorbell=%x"
				    " count=%d\n", ioc->name, करोorbell, count));

				अगर (करोorbell == MPI_IOC_STATE_READY) अणु
					अवरोध;
				पूर्ण

				/* रुको 1 sec */
				अगर (sleepFlag == CAN_SLEEP) अणु
					msleep (1000);
				पूर्ण अन्यथा अणु
					mdelay (1000);
				पूर्ण
			पूर्ण

			अगर (करोorbell != MPI_IOC_STATE_READY)
				prपूर्णांकk(MYIOC_s_ERR_FMT "Failed to come READY "
				    "after reset! IocState=%x", ioc->name,
				    करोorbell);
		पूर्ण
	पूर्ण

	diag0val = CHIPREG_READ32(&ioc->chip->Diagnostic);
	अगर (ioc->debug_level & MPT_DEBUG) अणु
		अगर (ioc->alt_ioc)
			diag1val = CHIPREG_READ32(&ioc->alt_ioc->chip->Diagnostic);
		dprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT "DbG3: diag0=%08x, diag1=%08x\n",
			ioc->name, diag0val, diag1val));
	पूर्ण

	/* Clear RESET_HISTORY bit!  Place board in the
	 * diagnostic mode to update the diag रेजिस्टर.
	 */
	diag0val = CHIPREG_READ32(&ioc->chip->Diagnostic);
	count = 0;
	जबतक ((diag0val & MPI_DIAG_DRWE) == 0) अणु
		/* Write magic sequence to WriteSequence रेजिस्टर
		 * Loop until in diagnostic mode
		 */
		CHIPREG_WRITE32(&ioc->chip->WriteSequence, 0xFF);
		CHIPREG_WRITE32(&ioc->chip->WriteSequence, MPI_WRSEQ_1ST_KEY_VALUE);
		CHIPREG_WRITE32(&ioc->chip->WriteSequence, MPI_WRSEQ_2ND_KEY_VALUE);
		CHIPREG_WRITE32(&ioc->chip->WriteSequence, MPI_WRSEQ_3RD_KEY_VALUE);
		CHIPREG_WRITE32(&ioc->chip->WriteSequence, MPI_WRSEQ_4TH_KEY_VALUE);
		CHIPREG_WRITE32(&ioc->chip->WriteSequence, MPI_WRSEQ_5TH_KEY_VALUE);

		/* रुको 100 msec */
		अगर (sleepFlag == CAN_SLEEP) अणु
			msleep (100);
		पूर्ण अन्यथा अणु
			mdelay (100);
		पूर्ण

		count++;
		अगर (count > 20) अणु
			prपूर्णांकk(MYIOC_s_ERR_FMT "Enable Diagnostic mode FAILED! (%02xh)\n",
					ioc->name, diag0val);
			अवरोध;
		पूर्ण
		diag0val = CHIPREG_READ32(&ioc->chip->Diagnostic);
	पूर्ण
	diag0val &= ~MPI_DIAG_RESET_HISTORY;
	CHIPREG_WRITE32(&ioc->chip->Diagnostic, diag0val);
	diag0val = CHIPREG_READ32(&ioc->chip->Diagnostic);
	अगर (diag0val & MPI_DIAG_RESET_HISTORY) अणु
		prपूर्णांकk(MYIOC_s_WARN_FMT "ResetHistory bit failed to clear!\n",
				ioc->name);
	पूर्ण

	/* Disable Diagnostic Mode
	 */
	CHIPREG_WRITE32(&ioc->chip->WriteSequence, 0xFFFFFFFF);

	/* Check FW reload status flags.
	 */
	diag0val = CHIPREG_READ32(&ioc->chip->Diagnostic);
	अगर (diag0val & (MPI_DIAG_FLASH_BAD_SIG | MPI_DIAG_RESET_ADAPTER | MPI_DIAG_DISABLE_ARM)) अणु
		prपूर्णांकk(MYIOC_s_ERR_FMT "Diagnostic reset FAILED! (%02xh)\n",
				ioc->name, diag0val);
		वापस -3;
	पूर्ण

	अगर (ioc->debug_level & MPT_DEBUG) अणु
		अगर (ioc->alt_ioc)
			diag1val = CHIPREG_READ32(&ioc->alt_ioc->chip->Diagnostic);
		dprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT "DbG4: diag0=%08x, diag1=%08x\n",
			ioc->name, diag0val, diag1val));
	पूर्ण

	/*
	 * Reset flag that says we've enabled event notअगरication
	 */
	ioc->facts.EventState = 0;

	अगर (ioc->alt_ioc)
		ioc->alt_ioc->facts.EventState = 0;

	वापस hard_reset_करोne;
पूर्ण

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/**
 *	SendIocReset - Send IOCReset request to MPT adapter.
 *	@ioc: Poपूर्णांकer to MPT_ADAPTER काष्ठाure
 *	@reset_type: reset type, expected values are
 *	%MPI_FUNCTION_IOC_MESSAGE_UNIT_RESET or %MPI_FUNCTION_IO_UNIT_RESET
 *	@sleepFlag: Specअगरies whether the process can sleep
 *
 *	Send IOCReset request to the MPT adapter.
 *
 *	Returns 0 क्रम success, non-zero क्रम failure.
 */
अटल पूर्णांक
SendIocReset(MPT_ADAPTER *ioc, u8 reset_type, पूर्णांक sleepFlag)
अणु
	पूर्णांक r;
	u32 state;
	पूर्णांक cntdn, count;

	drsprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT "Sending IOC reset(0x%02x)!\n",
			ioc->name, reset_type));
	CHIPREG_WRITE32(&ioc->chip->Doorbell, reset_type<<MPI_DOORBELL_FUNCTION_SHIFT);
	अगर ((r = WaitForDoorbellAck(ioc, 5, sleepFlag)) < 0)
		वापस r;

	/* FW ACK'd request, रुको क्रम READY state
	 */
	count = 0;
	cntdn = ((sleepFlag == CAN_SLEEP) ? HZ : 1000) * 15;	/* 15 seconds */

	जबतक ((state = mpt_GetIocState(ioc, 1)) != MPI_IOC_STATE_READY) अणु
		cntdn--;
		count++;
		अगर (!cntdn) अणु
			अगर (sleepFlag != CAN_SLEEP)
				count *= 10;

			prपूर्णांकk(MYIOC_s_ERR_FMT
			    "Wait IOC_READY state (0x%x) timeout(%d)!\n",
			    ioc->name, state, (पूर्णांक)((count+5)/HZ));
			वापस -ETIME;
		पूर्ण

		अगर (sleepFlag == CAN_SLEEP) अणु
			msleep(1);
		पूर्ण अन्यथा अणु
			mdelay (1);	/* 1 msec delay */
		पूर्ण
	पूर्ण

	/* TODO!
	 *  Cleanup all event stuff क्रम this IOC; re-issue EventNotअगरication
	 *  request अगर needed.
	 */
	अगर (ioc->facts.Function)
		ioc->facts.EventState = 0;

	वापस 0;
पूर्ण

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/**
 *	initChainBuffers - Allocate memory क्रम and initialize chain buffers
 *	@ioc: Poपूर्णांकer to MPT_ADAPTER काष्ठाure
 *
 *	Allocates memory क्रम and initializes chain buffers,
 *	chain buffer control arrays and spinlock.
 */
अटल पूर्णांक
initChainBuffers(MPT_ADAPTER *ioc)
अणु
	u8		*mem;
	पूर्णांक		sz, ii, num_chain;
	पूर्णांक 		scale, num_sge, numSGE;

	/* ReqToChain size must equal the req_depth
	 * index = req_idx
	 */
	अगर (ioc->ReqToChain == शून्य) अणु
		sz = ioc->req_depth * माप(पूर्णांक);
		mem = kदो_स्मृति(sz, GFP_ATOMIC);
		अगर (mem == शून्य)
			वापस -1;

		ioc->ReqToChain = (पूर्णांक *) mem;
		dinitprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT "ReqToChain alloc  @ %p, sz=%d bytes\n",
			 	ioc->name, mem, sz));
		mem = kदो_स्मृति(sz, GFP_ATOMIC);
		अगर (mem == शून्य)
			वापस -1;

		ioc->RequestNB = (पूर्णांक *) mem;
		dinitprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT "RequestNB alloc  @ %p, sz=%d bytes\n",
			 	ioc->name, mem, sz));
	पूर्ण
	क्रम (ii = 0; ii < ioc->req_depth; ii++) अणु
		ioc->ReqToChain[ii] = MPT_HOST_NO_CHAIN;
	पूर्ण

	/* ChainToChain size must equal the total number
	 * of chain buffers to be allocated.
	 * index = chain_idx
	 *
	 * Calculate the number of chain buffers needed(plus 1) per I/O
	 * then multiply the maximum number of simultaneous cmds
	 *
	 * num_sge = num sge in request frame + last chain buffer
	 * scale = num sge per chain buffer अगर no chain element
	 */
	scale = ioc->req_sz / ioc->SGE_size;
	अगर (ioc->sg_addr_size == माप(u64))
		num_sge =  scale + (ioc->req_sz - 60) / ioc->SGE_size;
	अन्यथा
		num_sge =  1 + scale + (ioc->req_sz - 64) / ioc->SGE_size;

	अगर (ioc->sg_addr_size == माप(u64)) अणु
		numSGE = (scale - 1) * (ioc->facts.MaxChainDepth-1) + scale +
			(ioc->req_sz - 60) / ioc->SGE_size;
	पूर्ण अन्यथा अणु
		numSGE = 1 + (scale - 1) * (ioc->facts.MaxChainDepth-1) +
		    scale + (ioc->req_sz - 64) / ioc->SGE_size;
	पूर्ण
	dinitprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT "num_sge=%d numSGE=%d\n",
		ioc->name, num_sge, numSGE));

	अगर (ioc->bus_type == FC) अणु
		अगर (numSGE > MPT_SCSI_FC_SG_DEPTH)
			numSGE = MPT_SCSI_FC_SG_DEPTH;
	पूर्ण अन्यथा अणु
		अगर (numSGE > MPT_SCSI_SG_DEPTH)
			numSGE = MPT_SCSI_SG_DEPTH;
	पूर्ण

	num_chain = 1;
	जबतक (numSGE - num_sge > 0) अणु
		num_chain++;
		num_sge += (scale - 1);
	पूर्ण
	num_chain++;

	dinitprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT "Now numSGE=%d num_sge=%d num_chain=%d\n",
		ioc->name, numSGE, num_sge, num_chain));

	अगर (ioc->bus_type == SPI)
		num_chain *= MPT_SCSI_CAN_QUEUE;
	अन्यथा अगर (ioc->bus_type == SAS)
		num_chain *= MPT_SAS_CAN_QUEUE;
	अन्यथा
		num_chain *= MPT_FC_CAN_QUEUE;

	ioc->num_chain = num_chain;

	sz = num_chain * माप(पूर्णांक);
	अगर (ioc->ChainToChain == शून्य) अणु
		mem = kदो_स्मृति(sz, GFP_ATOMIC);
		अगर (mem == शून्य)
			वापस -1;

		ioc->ChainToChain = (पूर्णांक *) mem;
		dinitprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT "ChainToChain alloc @ %p, sz=%d bytes\n",
			 	ioc->name, mem, sz));
	पूर्ण अन्यथा अणु
		mem = (u8 *) ioc->ChainToChain;
	पूर्ण
	स_रखो(mem, 0xFF, sz);
	वापस num_chain;
पूर्ण

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/**
 *	PrimeIocFअगरos - Initialize IOC request and reply FIFOs.
 *	@ioc: Poपूर्णांकer to MPT_ADAPTER काष्ठाure
 *
 *	This routine allocates memory क्रम the MPT reply and request frame
 *	pools (अगर necessary), and primes the IOC reply FIFO with
 *	reply frames.
 *
 *	Returns 0 क्रम success, non-zero क्रम failure.
 */
अटल पूर्णांक
PrimeIocFअगरos(MPT_ADAPTER *ioc)
अणु
	MPT_FRAME_HDR *mf;
	अचिन्हित दीर्घ flags;
	dma_addr_t alloc_dma;
	u8 *mem;
	पूर्णांक i, reply_sz, sz, total_size, num_chain;
	u64	dma_mask;

	dma_mask = 0;

	/*  Prime reply FIFO...  */

	अगर (ioc->reply_frames == शून्य) अणु
		अगर ( (num_chain = initChainBuffers(ioc)) < 0)
			वापस -1;
		/*
		 * 1078 errata workaround क्रम the 36GB limitation
		 */
		अगर (ioc->pcidev->device == MPI_MANUFACTPAGE_DEVID_SAS1078 &&
		    ioc->dma_mask > DMA_BIT_MASK(35)) अणु
			अगर (!pci_set_dma_mask(ioc->pcidev, DMA_BIT_MASK(32))
			    && !pci_set_consistent_dma_mask(ioc->pcidev,
			    DMA_BIT_MASK(32))) अणु
				dma_mask = DMA_BIT_MASK(35);
				d36memprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT
				    "setting 35 bit addressing for "
				    "Request/Reply/Chain and Sense Buffers\n",
				    ioc->name));
			पूर्ण अन्यथा अणु
				/*Reseting DMA mask to 64 bit*/
				pci_set_dma_mask(ioc->pcidev,
					DMA_BIT_MASK(64));
				pci_set_consistent_dma_mask(ioc->pcidev,
					DMA_BIT_MASK(64));

				prपूर्णांकk(MYIOC_s_ERR_FMT
				    "failed setting 35 bit addressing for "
				    "Request/Reply/Chain and Sense Buffers\n",
				    ioc->name);
				वापस -1;
			पूर्ण
		पूर्ण

		total_size = reply_sz = (ioc->reply_sz * ioc->reply_depth);
		dinitprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT "ReplyBuffer sz=%d bytes, ReplyDepth=%d\n",
			 	ioc->name, ioc->reply_sz, ioc->reply_depth));
		dinitprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT "ReplyBuffer sz=%d[%x] bytes\n",
			 	ioc->name, reply_sz, reply_sz));

		sz = (ioc->req_sz * ioc->req_depth);
		dinitprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT "RequestBuffer sz=%d bytes, RequestDepth=%d\n",
			 	ioc->name, ioc->req_sz, ioc->req_depth));
		dinitprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT "RequestBuffer sz=%d[%x] bytes\n",
			 	ioc->name, sz, sz));
		total_size += sz;

		sz = num_chain * ioc->req_sz; /* chain buffer pool size */
		dinitprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT "ChainBuffer sz=%d bytes, ChainDepth=%d\n",
			 	ioc->name, ioc->req_sz, num_chain));
		dinitprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT "ChainBuffer sz=%d[%x] bytes num_chain=%d\n",
			 	ioc->name, sz, sz, num_chain));

		total_size += sz;
		mem = dma_alloc_coherent(&ioc->pcidev->dev, total_size,
				&alloc_dma, GFP_KERNEL);
		अगर (mem == शून्य) अणु
			prपूर्णांकk(MYIOC_s_ERR_FMT "Unable to allocate Reply, Request, Chain Buffers!\n",
				ioc->name);
			जाओ out_fail;
		पूर्ण

		dinitprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT "Total alloc @ %p[%p], sz=%d[%x] bytes\n",
			 	ioc->name, mem, (व्योम *)(uदीर्घ)alloc_dma, total_size, total_size));

		स_रखो(mem, 0, total_size);
		ioc->alloc_total += total_size;
		ioc->alloc = mem;
		ioc->alloc_dma = alloc_dma;
		ioc->alloc_sz = total_size;
		ioc->reply_frames = (MPT_FRAME_HDR *) mem;
		ioc->reply_frames_low_dma = (u32) (alloc_dma & 0xFFFFFFFF);

		dinitprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT "ReplyBuffers @ %p[%p]\n",
	 		ioc->name, ioc->reply_frames, (व्योम *)(uदीर्घ)alloc_dma));

		alloc_dma += reply_sz;
		mem += reply_sz;

		/*  Request FIFO - WE manage this!  */

		ioc->req_frames = (MPT_FRAME_HDR *) mem;
		ioc->req_frames_dma = alloc_dma;

		dinitprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT "RequestBuffers @ %p[%p]\n",
			 	ioc->name, mem, (व्योम *)(uदीर्घ)alloc_dma));

		ioc->req_frames_low_dma = (u32) (alloc_dma & 0xFFFFFFFF);

		क्रम (i = 0; i < ioc->req_depth; i++) अणु
			alloc_dma += ioc->req_sz;
			mem += ioc->req_sz;
		पूर्ण

		ioc->ChainBuffer = mem;
		ioc->ChainBufferDMA = alloc_dma;

		dinitprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT "ChainBuffers @ %p(%p)\n",
			ioc->name, ioc->ChainBuffer, (व्योम *)(uदीर्घ)ioc->ChainBufferDMA));

		/* Initialize the मुक्त chain Q.
	 	*/

		INIT_LIST_HEAD(&ioc->FreeChainQ);

		/* Post the chain buffers to the FreeChainQ.
	 	*/
		mem = (u8 *)ioc->ChainBuffer;
		क्रम (i=0; i < num_chain; i++) अणु
			mf = (MPT_FRAME_HDR *) mem;
			list_add_tail(&mf->u.frame.linkage.list, &ioc->FreeChainQ);
			mem += ioc->req_sz;
		पूर्ण

		/* Initialize Request frames linked list
		 */
		alloc_dma = ioc->req_frames_dma;
		mem = (u8 *) ioc->req_frames;

		spin_lock_irqsave(&ioc->FreeQlock, flags);
		INIT_LIST_HEAD(&ioc->FreeQ);
		क्रम (i = 0; i < ioc->req_depth; i++) अणु
			mf = (MPT_FRAME_HDR *) mem;

			/*  Queue REQUESTs *पूर्णांकernally*!  */
			list_add_tail(&mf->u.frame.linkage.list, &ioc->FreeQ);

			mem += ioc->req_sz;
		पूर्ण
		spin_unlock_irqrestore(&ioc->FreeQlock, flags);

		sz = (ioc->req_depth * MPT_SENSE_BUFFER_ALLOC);
		ioc->sense_buf_pool = dma_alloc_coherent(&ioc->pcidev->dev, sz,
				&ioc->sense_buf_pool_dma, GFP_KERNEL);
		अगर (ioc->sense_buf_pool == शून्य) अणु
			prपूर्णांकk(MYIOC_s_ERR_FMT "Unable to allocate Sense Buffers!\n",
				ioc->name);
			जाओ out_fail;
		पूर्ण

		ioc->sense_buf_low_dma = (u32) (ioc->sense_buf_pool_dma & 0xFFFFFFFF);
		ioc->alloc_total += sz;
		dinitprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT "SenseBuffers @ %p[%p]\n",
 			ioc->name, ioc->sense_buf_pool, (व्योम *)(uदीर्घ)ioc->sense_buf_pool_dma));

	पूर्ण

	/* Post Reply frames to FIFO
	 */
	alloc_dma = ioc->alloc_dma;
	dinitprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT "ReplyBuffers @ %p[%p]\n",
	 	ioc->name, ioc->reply_frames, (व्योम *)(uदीर्घ)alloc_dma));

	क्रम (i = 0; i < ioc->reply_depth; i++) अणु
		/*  Write each address to the IOC!  */
		CHIPREG_WRITE32(&ioc->chip->ReplyFअगरo, alloc_dma);
		alloc_dma += ioc->reply_sz;
	पूर्ण

	अगर (dma_mask == DMA_BIT_MASK(35) && !pci_set_dma_mask(ioc->pcidev,
	    ioc->dma_mask) && !pci_set_consistent_dma_mask(ioc->pcidev,
	    ioc->dma_mask))
		d36memprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT
		    "restoring 64 bit addressing\n", ioc->name));

	वापस 0;

out_fail:

	अगर (ioc->alloc != शून्य) अणु
		sz = ioc->alloc_sz;
		dma_मुक्त_coherent(&ioc->pcidev->dev, sz, ioc->alloc,
				ioc->alloc_dma);
		ioc->reply_frames = शून्य;
		ioc->req_frames = शून्य;
		ioc->alloc_total -= sz;
	पूर्ण
	अगर (ioc->sense_buf_pool != शून्य) अणु
		sz = (ioc->req_depth * MPT_SENSE_BUFFER_ALLOC);
		dma_मुक्त_coherent(&ioc->pcidev->dev, sz, ioc->sense_buf_pool,
				ioc->sense_buf_pool_dma);
		ioc->sense_buf_pool = शून्य;
	पूर्ण

	अगर (dma_mask == DMA_BIT_MASK(35) && !pci_set_dma_mask(ioc->pcidev,
	    DMA_BIT_MASK(64)) && !pci_set_consistent_dma_mask(ioc->pcidev,
	    DMA_BIT_MASK(64)))
		d36memprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT
		    "restoring 64 bit addressing\n", ioc->name));

	वापस -1;
पूर्ण

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/**
 *	mpt_handshake_req_reply_रुको - Send MPT request to and receive reply
 *	from IOC via करोorbell handshake method.
 *	@ioc: Poपूर्णांकer to MPT_ADAPTER काष्ठाure
 *	@reqBytes: Size of the request in bytes
 *	@req: Poपूर्णांकer to MPT request frame
 *	@replyBytes: Expected size of the reply in bytes
 *	@u16reply: Poपूर्णांकer to area where reply should be written
 *	@maxरुको: Max रुको समय क्रम a reply (in seconds)
 *	@sleepFlag: Specअगरies whether the process can sleep
 *
 *	NOTES: It is the callers responsibility to byte-swap fields in the
 *	request which are greater than 1 byte in size.  It is also the
 *	callers responsibility to byte-swap response fields which are
 *	greater than 1 byte in size.
 *
 *	Returns 0 क्रम success, non-zero क्रम failure.
 */
अटल पूर्णांक
mpt_handshake_req_reply_रुको(MPT_ADAPTER *ioc, पूर्णांक reqBytes, u32 *req,
		पूर्णांक replyBytes, u16 *u16reply, पूर्णांक maxरुको, पूर्णांक sleepFlag)
अणु
	MPIDefaultReply_t *mptReply;
	पूर्णांक failcnt = 0;
	पूर्णांक t;

	/*
	 * Get पढ़ोy to cache a handshake reply
	 */
	ioc->hs_reply_idx = 0;
	mptReply = (MPIDefaultReply_t *) ioc->hs_reply;
	mptReply->MsgLength = 0;

	/*
	 * Make sure there are no करोorbells (WRITE 0 to IntStatus reg),
	 * then tell IOC that we want to handshake a request of N words.
	 * (WRITE u32val to Doorbell reg).
	 */
	CHIPREG_WRITE32(&ioc->chip->IntStatus, 0);
	CHIPREG_WRITE32(&ioc->chip->Doorbell,
			((MPI_FUNCTION_HANDSHAKE<<MPI_DOORBELL_FUNCTION_SHIFT) |
			 ((reqBytes/4)<<MPI_DOORBELL_ADD_DWORDS_SHIFT)));

	/*
	 * Wait क्रम IOC's करोorbell handshake पूर्णांक
	 */
	अगर ((t = WaitForDoorbellInt(ioc, 5, sleepFlag)) < 0)
		failcnt++;

	dhsprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT "HandShake request start reqBytes=%d, WaitCnt=%d%s\n",
			ioc->name, reqBytes, t, failcnt ? " - MISSING DOORBELL HANDSHAKE!" : ""));

	/* Read करोorbell and check क्रम active bit */
	अगर (!(CHIPREG_READ32(&ioc->chip->Doorbell) & MPI_DOORBELL_ACTIVE))
			वापस -1;

	/*
	 * Clear करोorbell पूर्णांक (WRITE 0 to IntStatus reg),
	 * then रुको क्रम IOC to ACKnowledge that it's पढ़ोy क्रम
	 * our handshake request.
	 */
	CHIPREG_WRITE32(&ioc->chip->IntStatus, 0);
	अगर (!failcnt && (t = WaitForDoorbellAck(ioc, 5, sleepFlag)) < 0)
		failcnt++;

	अगर (!failcnt) अणु
		पूर्णांक	 ii;
		u8	*req_as_bytes = (u8 *) req;

		/*
		 * Stuff request words via करोorbell handshake,
		 * with ACK from IOC क्रम each.
		 */
		क्रम (ii = 0; !failcnt && ii < reqBytes/4; ii++) अणु
			u32 word = ((req_as_bytes[(ii*4) + 0] <<  0) |
				    (req_as_bytes[(ii*4) + 1] <<  8) |
				    (req_as_bytes[(ii*4) + 2] << 16) |
				    (req_as_bytes[(ii*4) + 3] << 24));

			CHIPREG_WRITE32(&ioc->chip->Doorbell, word);
			अगर ((t = WaitForDoorbellAck(ioc, 5, sleepFlag)) < 0)
				failcnt++;
		पूर्ण

		dhsprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT "Handshake request frame (@%p) header\n", ioc->name, req));
		DBG_DUMP_REQUEST_FRAME_HDR(ioc, (u32 *)req);

		dhsprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT "HandShake request post done, WaitCnt=%d%s\n",
				ioc->name, t, failcnt ? " - MISSING DOORBELL ACK!" : ""));

		/*
		 * Wait क्रम completion of करोorbell handshake reply from the IOC
		 */
		अगर (!failcnt && (t = WaitForDoorbellReply(ioc, maxरुको, sleepFlag)) < 0)
			failcnt++;

		dhsprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT "HandShake reply count=%d%s\n",
				ioc->name, t, failcnt ? " - MISSING DOORBELL REPLY!" : ""));

		/*
		 * Copy out the cached reply...
		 */
		क्रम (ii=0; ii < min(replyBytes/2,mptReply->MsgLength*2); ii++)
			u16reply[ii] = ioc->hs_reply[ii];
	पूर्ण अन्यथा अणु
		वापस -99;
	पूर्ण

	वापस -failcnt;
पूर्ण

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/**
 *	WaitForDoorbellAck - Wait क्रम IOC करोorbell handshake acknowledge
 *	@ioc: Poपूर्णांकer to MPT_ADAPTER काष्ठाure
 *	@howदीर्घ: How दीर्घ to रुको (in seconds)
 *	@sleepFlag: Specअगरies whether the process can sleep
 *
 *	This routine रुकोs (up to ~2 seconds max) क्रम IOC करोorbell
 *	handshake ACKnowledge, indicated by the IOP_DOORBELL_STATUS
 *	bit in its IntStatus रेजिस्टर being clear.
 *
 *	Returns a negative value on failure, अन्यथा रुको loop count.
 */
अटल पूर्णांक
WaitForDoorbellAck(MPT_ADAPTER *ioc, पूर्णांक howदीर्घ, पूर्णांक sleepFlag)
अणु
	पूर्णांक cntdn;
	पूर्णांक count = 0;
	u32 पूर्णांकstat=0;

	cntdn = 1000 * howदीर्घ;

	अगर (sleepFlag == CAN_SLEEP) अणु
		जबतक (--cntdn) अणु
			msleep (1);
			पूर्णांकstat = CHIPREG_READ32(&ioc->chip->IntStatus);
			अगर (! (पूर्णांकstat & MPI_HIS_IOP_DOORBELL_STATUS))
				अवरोध;
			count++;
		पूर्ण
	पूर्ण अन्यथा अणु
		जबतक (--cntdn) अणु
			udelay (1000);
			पूर्णांकstat = CHIPREG_READ32(&ioc->chip->IntStatus);
			अगर (! (पूर्णांकstat & MPI_HIS_IOP_DOORBELL_STATUS))
				अवरोध;
			count++;
		पूर्ण
	पूर्ण

	अगर (cntdn) अणु
		dprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT "WaitForDoorbell ACK (count=%d)\n",
				ioc->name, count));
		वापस count;
	पूर्ण

	prपूर्णांकk(MYIOC_s_ERR_FMT "Doorbell ACK timeout (count=%d), IntStatus=%x!\n",
			ioc->name, count, पूर्णांकstat);
	वापस -1;
पूर्ण

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/**
 *	WaitForDoorbellInt - Wait क्रम IOC to set its करोorbell पूर्णांकerrupt bit
 *	@ioc: Poपूर्णांकer to MPT_ADAPTER काष्ठाure
 *	@howदीर्घ: How दीर्घ to रुको (in seconds)
 *	@sleepFlag: Specअगरies whether the process can sleep
 *
 *	This routine रुकोs (up to ~2 seconds max) क्रम IOC करोorbell पूर्णांकerrupt
 *	(MPI_HIS_DOORBELL_INTERRUPT) to be set in the IntStatus रेजिस्टर.
 *
 *	Returns a negative value on failure, अन्यथा रुको loop count.
 */
अटल पूर्णांक
WaitForDoorbellInt(MPT_ADAPTER *ioc, पूर्णांक howदीर्घ, पूर्णांक sleepFlag)
अणु
	पूर्णांक cntdn;
	पूर्णांक count = 0;
	u32 पूर्णांकstat=0;

	cntdn = 1000 * howदीर्घ;
	अगर (sleepFlag == CAN_SLEEP) अणु
		जबतक (--cntdn) अणु
			पूर्णांकstat = CHIPREG_READ32(&ioc->chip->IntStatus);
			अगर (पूर्णांकstat & MPI_HIS_DOORBELL_INTERRUPT)
				अवरोध;
			msleep(1);
			count++;
		पूर्ण
	पूर्ण अन्यथा अणु
		जबतक (--cntdn) अणु
			पूर्णांकstat = CHIPREG_READ32(&ioc->chip->IntStatus);
			अगर (पूर्णांकstat & MPI_HIS_DOORBELL_INTERRUPT)
				अवरोध;
			udelay (1000);
			count++;
		पूर्ण
	पूर्ण

	अगर (cntdn) अणु
		dprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT "WaitForDoorbell INT (cnt=%d) howlong=%d\n",
				ioc->name, count, howदीर्घ));
		वापस count;
	पूर्ण

	prपूर्णांकk(MYIOC_s_ERR_FMT "Doorbell INT timeout (count=%d), IntStatus=%x!\n",
			ioc->name, count, पूर्णांकstat);
	वापस -1;
पूर्ण

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/**
 *	WaitForDoorbellReply - Wait क्रम and capture an IOC handshake reply.
 *	@ioc: Poपूर्णांकer to MPT_ADAPTER काष्ठाure
 *	@howदीर्घ: How दीर्घ to रुको (in seconds)
 *	@sleepFlag: Specअगरies whether the process can sleep
 *
 *	This routine polls the IOC क्रम a handshake reply, 16 bits at a समय.
 *	Reply is cached to IOC निजी area large enough to hold a maximum
 *	of 128 bytes of reply data.
 *
 *	Returns a negative value on failure, अन्यथा size of reply in WORDS.
 */
अटल पूर्णांक
WaitForDoorbellReply(MPT_ADAPTER *ioc, पूर्णांक howदीर्घ, पूर्णांक sleepFlag)
अणु
	पूर्णांक u16cnt = 0;
	पूर्णांक failcnt = 0;
	पूर्णांक t;
	u16 *hs_reply = ioc->hs_reply;
	अस्थिर MPIDefaultReply_t *mptReply = (MPIDefaultReply_t *) ioc->hs_reply;
	u16 hword;

	hs_reply[0] = hs_reply[1] = hs_reply[7] = 0;

	/*
	 * Get first two u16's so we can look at IOC's पूर्णांकended reply MsgLength
	 */
	u16cnt=0;
	अगर ((t = WaitForDoorbellInt(ioc, howदीर्घ, sleepFlag)) < 0) अणु
		failcnt++;
	पूर्ण अन्यथा अणु
		hs_reply[u16cnt++] = le16_to_cpu(CHIPREG_READ32(&ioc->chip->Doorbell) & 0x0000FFFF);
		CHIPREG_WRITE32(&ioc->chip->IntStatus, 0);
		अगर ((t = WaitForDoorbellInt(ioc, 5, sleepFlag)) < 0)
			failcnt++;
		अन्यथा अणु
			hs_reply[u16cnt++] = le16_to_cpu(CHIPREG_READ32(&ioc->chip->Doorbell) & 0x0000FFFF);
			CHIPREG_WRITE32(&ioc->chip->IntStatus, 0);
		पूर्ण
	पूर्ण

	dhsprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT "WaitCnt=%d First handshake reply word=%08x%s\n",
			ioc->name, t, le32_to_cpu(*(u32 *)hs_reply),
			failcnt ? " - MISSING DOORBELL HANDSHAKE!" : ""));

	/*
	 * If no error (and IOC said MsgLength is > 0), piece together
	 * reply 16 bits at a समय.
	 */
	क्रम (u16cnt=2; !failcnt && u16cnt < (2 * mptReply->MsgLength); u16cnt++) अणु
		अगर ((t = WaitForDoorbellInt(ioc, 5, sleepFlag)) < 0)
			failcnt++;
		hword = le16_to_cpu(CHIPREG_READ32(&ioc->chip->Doorbell) & 0x0000FFFF);
		/* करोn't overflow our IOC hs_reply[] buffer! */
		अगर (u16cnt < ARRAY_SIZE(ioc->hs_reply))
			hs_reply[u16cnt] = hword;
		CHIPREG_WRITE32(&ioc->chip->IntStatus, 0);
	पूर्ण

	अगर (!failcnt && (t = WaitForDoorbellInt(ioc, 5, sleepFlag)) < 0)
		failcnt++;
	CHIPREG_WRITE32(&ioc->chip->IntStatus, 0);

	अगर (failcnt) अणु
		prपूर्णांकk(MYIOC_s_ERR_FMT "Handshake reply failure!\n",
				ioc->name);
		वापस -failcnt;
	पूर्ण
#अगर 0
	अन्यथा अगर (u16cnt != (2 * mptReply->MsgLength)) अणु
		वापस -101;
	पूर्ण
	अन्यथा अगर ((mptReply->IOCStatus & MPI_IOCSTATUS_MASK) != MPI_IOCSTATUS_SUCCESS) अणु
		वापस -102;
	पूर्ण
#पूर्ण_अगर

	dhsprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT "Got Handshake reply:\n", ioc->name));
	DBG_DUMP_REPLY_FRAME(ioc, (u32 *)mptReply);

	dhsprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT "WaitForDoorbell REPLY WaitCnt=%d (sz=%d)\n",
			ioc->name, t, u16cnt/2));
	वापस u16cnt/2;
पूर्ण

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/**
 *	GetLanConfigPages - Fetch LANConfig pages.
 *	@ioc: Poपूर्णांकer to MPT_ADAPTER काष्ठाure
 *
 *	Return: 0 क्रम success
 *	-ENOMEM अगर no memory available
 *		-EPERM अगर not allowed due to ISR context
 *		-EAGAIN अगर no msg frames currently available
 *		-EFAULT क्रम non-successful reply or no reply (समयout)
 */
अटल पूर्णांक
GetLanConfigPages(MPT_ADAPTER *ioc)
अणु
	ConfigPageHeader_t	 hdr;
	CONFIGPARMS		 cfg;
	LANPage0_t		*ppage0_alloc;
	dma_addr_t		 page0_dma;
	LANPage1_t		*ppage1_alloc;
	dma_addr_t		 page1_dma;
	पूर्णांक			 rc = 0;
	पूर्णांक			 data_sz;
	पूर्णांक			 copy_sz;

	/* Get LAN Page 0 header */
	hdr.PageVersion = 0;
	hdr.PageLength = 0;
	hdr.PageNumber = 0;
	hdr.PageType = MPI_CONFIG_PAGETYPE_LAN;
	cfg.cfghdr.hdr = &hdr;
	cfg.physAddr = -1;
	cfg.action = MPI_CONFIG_ACTION_PAGE_HEADER;
	cfg.dir = 0;
	cfg.pageAddr = 0;
	cfg.समयout = 0;

	अगर ((rc = mpt_config(ioc, &cfg)) != 0)
		वापस rc;

	अगर (hdr.PageLength > 0) अणु
		data_sz = hdr.PageLength * 4;
		ppage0_alloc = pci_alloc_consistent(ioc->pcidev, data_sz, &page0_dma);
		rc = -ENOMEM;
		अगर (ppage0_alloc) अणु
			स_रखो((u8 *)ppage0_alloc, 0, data_sz);
			cfg.physAddr = page0_dma;
			cfg.action = MPI_CONFIG_ACTION_PAGE_READ_CURRENT;

			अगर ((rc = mpt_config(ioc, &cfg)) == 0) अणु
				/* save the data */
				copy_sz = min_t(पूर्णांक, माप(LANPage0_t), data_sz);
				स_नकल(&ioc->lan_cnfg_page0, ppage0_alloc, copy_sz);

			पूर्ण

			pci_मुक्त_consistent(ioc->pcidev, data_sz, (u8 *) ppage0_alloc, page0_dma);

			/* FIXME!
			 *	Normalize endianness of काष्ठाure data,
			 *	by byte-swapping all > 1 byte fields!
			 */

		पूर्ण

		अगर (rc)
			वापस rc;
	पूर्ण

	/* Get LAN Page 1 header */
	hdr.PageVersion = 0;
	hdr.PageLength = 0;
	hdr.PageNumber = 1;
	hdr.PageType = MPI_CONFIG_PAGETYPE_LAN;
	cfg.cfghdr.hdr = &hdr;
	cfg.physAddr = -1;
	cfg.action = MPI_CONFIG_ACTION_PAGE_HEADER;
	cfg.dir = 0;
	cfg.pageAddr = 0;

	अगर ((rc = mpt_config(ioc, &cfg)) != 0)
		वापस rc;

	अगर (hdr.PageLength == 0)
		वापस 0;

	data_sz = hdr.PageLength * 4;
	rc = -ENOMEM;
	ppage1_alloc = pci_alloc_consistent(ioc->pcidev, data_sz, &page1_dma);
	अगर (ppage1_alloc) अणु
		स_रखो((u8 *)ppage1_alloc, 0, data_sz);
		cfg.physAddr = page1_dma;
		cfg.action = MPI_CONFIG_ACTION_PAGE_READ_CURRENT;

		अगर ((rc = mpt_config(ioc, &cfg)) == 0) अणु
			/* save the data */
			copy_sz = min_t(पूर्णांक, माप(LANPage1_t), data_sz);
			स_नकल(&ioc->lan_cnfg_page1, ppage1_alloc, copy_sz);
		पूर्ण

		pci_मुक्त_consistent(ioc->pcidev, data_sz, (u8 *) ppage1_alloc, page1_dma);

		/* FIXME!
		 *	Normalize endianness of काष्ठाure data,
		 *	by byte-swapping all > 1 byte fields!
		 */

	पूर्ण

	वापस rc;
पूर्ण

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/**
 *	mptbase_sas_persist_operation - Perक्रमm operation on SAS Persistent Table
 *	@ioc: Poपूर्णांकer to MPT_ADAPTER काष्ठाure
 *	@persist_opcode: see below
 *
 *	===============================  ======================================
 *	MPI_SAS_OP_CLEAR_NOT_PRESENT     Free all persist TargetID mappings क्रम
 *					 devices not currently present.
 *	MPI_SAS_OP_CLEAR_ALL_PERSISTENT  Clear al persist TargetID mappings
 *	===============================  ======================================
 *
 *	NOTE: Don't use not this function during पूर्णांकerrupt समय.
 *
 *	Returns 0 क्रम success, non-zero error
 */

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
पूर्णांक
mptbase_sas_persist_operation(MPT_ADAPTER *ioc, u8 persist_opcode)
अणु
	SasIoUnitControlRequest_t	*sasIoUnitCntrReq;
	SasIoUnitControlReply_t		*sasIoUnitCntrReply;
	MPT_FRAME_HDR			*mf = शून्य;
	MPIHeader_t			*mpi_hdr;
	पूर्णांक				ret = 0;
	अचिन्हित दीर्घ 	 		समयleft;

	mutex_lock(&ioc->mptbase_cmds.mutex);

	/* init the पूर्णांकernal cmd काष्ठा */
	स_रखो(ioc->mptbase_cmds.reply, 0 , MPT_DEFAULT_FRAME_SIZE);
	INITIALIZE_MGMT_STATUS(ioc->mptbase_cmds.status)

	/* insure garbage is not sent to fw */
	चयन(persist_opcode) अणु

	हाल MPI_SAS_OP_CLEAR_NOT_PRESENT:
	हाल MPI_SAS_OP_CLEAR_ALL_PERSISTENT:
		अवरोध;

	शेष:
		ret = -1;
		जाओ out;
	पूर्ण

	prपूर्णांकk(KERN_DEBUG  "%s: persist_opcode=%x\n",
		__func__, persist_opcode);

	/* Get a MF क्रम this command.
	 */
	अगर ((mf = mpt_get_msg_frame(mpt_base_index, ioc)) == शून्य) अणु
		prपूर्णांकk(KERN_DEBUG "%s: no msg frames!\n", __func__);
		ret = -1;
		जाओ out;
        पूर्ण

	mpi_hdr = (MPIHeader_t *) mf;
	sasIoUnitCntrReq = (SasIoUnitControlRequest_t *)mf;
	स_रखो(sasIoUnitCntrReq,0,माप(SasIoUnitControlRequest_t));
	sasIoUnitCntrReq->Function = MPI_FUNCTION_SAS_IO_UNIT_CONTROL;
	sasIoUnitCntrReq->MsgContext = mpi_hdr->MsgContext;
	sasIoUnitCntrReq->Operation = persist_opcode;

	mpt_put_msg_frame(mpt_base_index, ioc, mf);
	समयleft = रुको_क्रम_completion_समयout(&ioc->mptbase_cmds.करोne, 10*HZ);
	अगर (!(ioc->mptbase_cmds.status & MPT_MGMT_STATUS_COMMAND_GOOD)) अणु
		ret = -ETIME;
		prपूर्णांकk(KERN_DEBUG "%s: failed\n", __func__);
		अगर (ioc->mptbase_cmds.status & MPT_MGMT_STATUS_DID_IOCRESET)
			जाओ out;
		अगर (!समयleft) अणु
			prपूर्णांकk(MYIOC_s_WARN_FMT
			       "Issuing Reset from %s!!, doorbell=0x%08x\n",
			       ioc->name, __func__, mpt_GetIocState(ioc, 0));
			mpt_Soft_Hard_ResetHandler(ioc, CAN_SLEEP);
			mpt_मुक्त_msg_frame(ioc, mf);
		पूर्ण
		जाओ out;
	पूर्ण

	अगर (!(ioc->mptbase_cmds.status & MPT_MGMT_STATUS_RF_VALID)) अणु
		ret = -1;
		जाओ out;
	पूर्ण

	sasIoUnitCntrReply =
	    (SasIoUnitControlReply_t *)ioc->mptbase_cmds.reply;
	अगर (le16_to_cpu(sasIoUnitCntrReply->IOCStatus) != MPI_IOCSTATUS_SUCCESS) अणु
		prपूर्णांकk(KERN_DEBUG "%s: IOCStatus=0x%X IOCLogInfo=0x%X\n",
		    __func__, sasIoUnitCntrReply->IOCStatus,
		    sasIoUnitCntrReply->IOCLogInfo);
		prपूर्णांकk(KERN_DEBUG "%s: failed\n", __func__);
		ret = -1;
	पूर्ण अन्यथा
		prपूर्णांकk(KERN_DEBUG "%s: success\n", __func__);
 out:

	CLEAR_MGMT_STATUS(ioc->mptbase_cmds.status)
	mutex_unlock(&ioc->mptbase_cmds.mutex);
	वापस ret;
पूर्ण

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/

अटल व्योम
mptbase_raid_process_event_data(MPT_ADAPTER *ioc,
    MpiEventDataRaid_t * pRaidEventData)
अणु
	पूर्णांक 	volume;
	पूर्णांक 	reason;
	पूर्णांक 	disk;
	पूर्णांक 	status;
	पूर्णांक 	flags;
	पूर्णांक 	state;

	volume	= pRaidEventData->VolumeID;
	reason	= pRaidEventData->ReasonCode;
	disk	= pRaidEventData->PhysDiskNum;
	status	= le32_to_cpu(pRaidEventData->SettingsStatus);
	flags	= (status >> 0) & 0xff;
	state	= (status >> 8) & 0xff;

	अगर (reason == MPI_EVENT_RAID_RC_DOMAIN_VAL_NEEDED) अणु
		वापस;
	पूर्ण

	अगर ((reason >= MPI_EVENT_RAID_RC_PHYSDISK_CREATED &&
	     reason <= MPI_EVENT_RAID_RC_PHYSDISK_STATUS_CHANGED) ||
	    (reason == MPI_EVENT_RAID_RC_SMART_DATA)) अणु
		prपूर्णांकk(MYIOC_s_INFO_FMT "RAID STATUS CHANGE for PhysDisk %d id=%d\n",
			ioc->name, disk, volume);
	पूर्ण अन्यथा अणु
		prपूर्णांकk(MYIOC_s_INFO_FMT "RAID STATUS CHANGE for VolumeID %d\n",
			ioc->name, volume);
	पूर्ण

	चयन(reason) अणु
	हाल MPI_EVENT_RAID_RC_VOLUME_CREATED:
		prपूर्णांकk(MYIOC_s_INFO_FMT "  volume has been created\n",
			ioc->name);
		अवरोध;

	हाल MPI_EVENT_RAID_RC_VOLUME_DELETED:

		prपूर्णांकk(MYIOC_s_INFO_FMT "  volume has been deleted\n",
			ioc->name);
		अवरोध;

	हाल MPI_EVENT_RAID_RC_VOLUME_SETTINGS_CHANGED:
		prपूर्णांकk(MYIOC_s_INFO_FMT "  volume settings have been changed\n",
			ioc->name);
		अवरोध;

	हाल MPI_EVENT_RAID_RC_VOLUME_STATUS_CHANGED:
		prपूर्णांकk(MYIOC_s_INFO_FMT "  volume is now %s%s%s%s\n",
			ioc->name,
			state == MPI_RAIDVOL0_STATUS_STATE_OPTIMAL
			 ? "optimal"
			 : state == MPI_RAIDVOL0_STATUS_STATE_DEGRADED
			  ? "degraded"
			  : state == MPI_RAIDVOL0_STATUS_STATE_FAILED
			   ? "failed"
			   : "state unknown",
			flags & MPI_RAIDVOL0_STATUS_FLAG_ENABLED
			 ? ", enabled" : "",
			flags & MPI_RAIDVOL0_STATUS_FLAG_QUIESCED
			 ? ", quiesced" : "",
			flags & MPI_RAIDVOL0_STATUS_FLAG_RESYNC_IN_PROGRESS
			 ? ", resync in progress" : "" );
		अवरोध;

	हाल MPI_EVENT_RAID_RC_VOLUME_PHYSDISK_CHANGED:
		prपूर्णांकk(MYIOC_s_INFO_FMT "  volume membership of PhysDisk %d has changed\n",
			ioc->name, disk);
		अवरोध;

	हाल MPI_EVENT_RAID_RC_PHYSDISK_CREATED:
		prपूर्णांकk(MYIOC_s_INFO_FMT "  PhysDisk has been created\n",
			ioc->name);
		अवरोध;

	हाल MPI_EVENT_RAID_RC_PHYSDISK_DELETED:
		prपूर्णांकk(MYIOC_s_INFO_FMT "  PhysDisk has been deleted\n",
			ioc->name);
		अवरोध;

	हाल MPI_EVENT_RAID_RC_PHYSDISK_SETTINGS_CHANGED:
		prपूर्णांकk(MYIOC_s_INFO_FMT "  PhysDisk settings have been changed\n",
			ioc->name);
		अवरोध;

	हाल MPI_EVENT_RAID_RC_PHYSDISK_STATUS_CHANGED:
		prपूर्णांकk(MYIOC_s_INFO_FMT "  PhysDisk is now %s%s%s\n",
			ioc->name,
			state == MPI_PHYSDISK0_STATUS_ONLINE
			 ? "online"
			 : state == MPI_PHYSDISK0_STATUS_MISSING
			  ? "missing"
			  : state == MPI_PHYSDISK0_STATUS_NOT_COMPATIBLE
			   ? "not compatible"
			   : state == MPI_PHYSDISK0_STATUS_FAILED
			    ? "failed"
			    : state == MPI_PHYSDISK0_STATUS_INITIALIZING
			     ? "initializing"
			     : state == MPI_PHYSDISK0_STATUS_OFFLINE_REQUESTED
			      ? "offline requested"
			      : state == MPI_PHYSDISK0_STATUS_FAILED_REQUESTED
			       ? "failed requested"
			       : state == MPI_PHYSDISK0_STATUS_OTHER_OFFLINE
			        ? "offline"
			        : "state unknown",
			flags & MPI_PHYSDISK0_STATUS_FLAG_OUT_OF_SYNC
			 ? ", out of sync" : "",
			flags & MPI_PHYSDISK0_STATUS_FLAG_QUIESCED
			 ? ", quiesced" : "" );
		अवरोध;

	हाल MPI_EVENT_RAID_RC_DOMAIN_VAL_NEEDED:
		prपूर्णांकk(MYIOC_s_INFO_FMT "  Domain Validation needed for PhysDisk %d\n",
			ioc->name, disk);
		अवरोध;

	हाल MPI_EVENT_RAID_RC_SMART_DATA:
		prपूर्णांकk(MYIOC_s_INFO_FMT "  SMART data received, ASC/ASCQ = %02xh/%02xh\n",
			ioc->name, pRaidEventData->ASC, pRaidEventData->ASCQ);
		अवरोध;

	हाल MPI_EVENT_RAID_RC_REPLACE_ACTION_STARTED:
		prपूर्णांकk(MYIOC_s_INFO_FMT "  replacement of PhysDisk %d has started\n",
			ioc->name, disk);
		अवरोध;
	पूर्ण
पूर्ण

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/**
 *	GetIoUnitPage2 - Retrieve BIOS version and boot order inक्रमmation.
 *	@ioc: Poपूर्णांकer to MPT_ADAPTER काष्ठाure
 *
 *	Returns: 0 क्रम success
 *	-ENOMEM अगर no memory available
 *		-EPERM अगर not allowed due to ISR context
 *		-EAGAIN अगर no msg frames currently available
 *		-EFAULT क्रम non-successful reply or no reply (समयout)
 */
अटल पूर्णांक
GetIoUnitPage2(MPT_ADAPTER *ioc)
अणु
	ConfigPageHeader_t	 hdr;
	CONFIGPARMS		 cfg;
	IOUnitPage2_t		*ppage_alloc;
	dma_addr_t		 page_dma;
	पूर्णांक			 data_sz;
	पूर्णांक			 rc;

	/* Get the page header */
	hdr.PageVersion = 0;
	hdr.PageLength = 0;
	hdr.PageNumber = 2;
	hdr.PageType = MPI_CONFIG_PAGETYPE_IO_UNIT;
	cfg.cfghdr.hdr = &hdr;
	cfg.physAddr = -1;
	cfg.action = MPI_CONFIG_ACTION_PAGE_HEADER;
	cfg.dir = 0;
	cfg.pageAddr = 0;
	cfg.समयout = 0;

	अगर ((rc = mpt_config(ioc, &cfg)) != 0)
		वापस rc;

	अगर (hdr.PageLength == 0)
		वापस 0;

	/* Read the config page */
	data_sz = hdr.PageLength * 4;
	rc = -ENOMEM;
	ppage_alloc = pci_alloc_consistent(ioc->pcidev, data_sz, &page_dma);
	अगर (ppage_alloc) अणु
		स_रखो((u8 *)ppage_alloc, 0, data_sz);
		cfg.physAddr = page_dma;
		cfg.action = MPI_CONFIG_ACTION_PAGE_READ_CURRENT;

		/* If Good, save data */
		अगर ((rc = mpt_config(ioc, &cfg)) == 0)
			ioc->biosVersion = le32_to_cpu(ppage_alloc->BiosVersion);

		pci_मुक्त_consistent(ioc->pcidev, data_sz, (u8 *) ppage_alloc, page_dma);
	पूर्ण

	वापस rc;
पूर्ण

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/**
 *	mpt_GetScsiPortSettings - पढ़ो SCSI Port Page 0 and 2
 *	@ioc: Poपूर्णांकer to a Adapter Strucutre
 *	@portnum: IOC port number
 *
 *	Return: -EFAULT अगर पढ़ो of config page header fails
 *			or अगर no nvram
 *	If पढ़ो of SCSI Port Page 0 fails,
 *		NVRAM = MPT_HOST_NVRAM_INVALID  (0xFFFFFFFF)
 *		Adapter settings: async, narrow
 *		Return 1
 *	If पढ़ो of SCSI Port Page 2 fails,
 *		Adapter settings valid
 *		NVRAM = MPT_HOST_NVRAM_INVALID  (0xFFFFFFFF)
 *		Return 1
 *	Else
 *		Both valid
 *		Return 0
 *	CHECK - what type of locking mechanisms should be used????
 */
अटल पूर्णांक
mpt_GetScsiPortSettings(MPT_ADAPTER *ioc, पूर्णांक portnum)
अणु
	u8			*pbuf;
	dma_addr_t		 buf_dma;
	CONFIGPARMS		 cfg;
	ConfigPageHeader_t	 header;
	पूर्णांक			 ii;
	पूर्णांक			 data, rc = 0;

	/* Allocate memory
	 */
	अगर (!ioc->spi_data.nvram) अणु
		पूर्णांक	 sz;
		u8	*mem;
		sz = MPT_MAX_SCSI_DEVICES * माप(पूर्णांक);
		mem = kदो_स्मृति(sz, GFP_ATOMIC);
		अगर (mem == शून्य)
			वापस -EFAULT;

		ioc->spi_data.nvram = (पूर्णांक *) mem;

		dprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT "SCSI device NVRAM settings @ %p, sz=%d\n",
			ioc->name, ioc->spi_data.nvram, sz));
	पूर्ण

	/* Invalidate NVRAM inक्रमmation
	 */
	क्रम (ii=0; ii < MPT_MAX_SCSI_DEVICES; ii++) अणु
		ioc->spi_data.nvram[ii] = MPT_HOST_NVRAM_INVALID;
	पूर्ण

	/* Read SPP0 header, allocate memory, then पढ़ो page.
	 */
	header.PageVersion = 0;
	header.PageLength = 0;
	header.PageNumber = 0;
	header.PageType = MPI_CONFIG_PAGETYPE_SCSI_PORT;
	cfg.cfghdr.hdr = &header;
	cfg.physAddr = -1;
	cfg.pageAddr = portnum;
	cfg.action = MPI_CONFIG_ACTION_PAGE_HEADER;
	cfg.dir = 0;
	cfg.समयout = 0;	/* use शेष */
	अगर (mpt_config(ioc, &cfg) != 0)
		 वापस -EFAULT;

	अगर (header.PageLength > 0) अणु
		pbuf = pci_alloc_consistent(ioc->pcidev, header.PageLength * 4, &buf_dma);
		अगर (pbuf) अणु
			cfg.action = MPI_CONFIG_ACTION_PAGE_READ_CURRENT;
			cfg.physAddr = buf_dma;
			अगर (mpt_config(ioc, &cfg) != 0) अणु
				ioc->spi_data.maxBusWidth = MPT_NARROW;
				ioc->spi_data.maxSyncOffset = 0;
				ioc->spi_data.minSyncFactor = MPT_ASYNC;
				ioc->spi_data.busType = MPT_HOST_BUS_UNKNOWN;
				rc = 1;
				ddvprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT
					"Unable to read PortPage0 minSyncFactor=%x\n",
					ioc->name, ioc->spi_data.minSyncFactor));
			पूर्ण अन्यथा अणु
				/* Save the Port Page 0 data
				 */
				SCSIPortPage0_t  *pPP0 = (SCSIPortPage0_t  *) pbuf;
				pPP0->Capabilities = le32_to_cpu(pPP0->Capabilities);
				pPP0->PhysicalInterface = le32_to_cpu(pPP0->PhysicalInterface);

				अगर ( (pPP0->Capabilities & MPI_SCSIPORTPAGE0_CAP_QAS) == 0 ) अणु
					ioc->spi_data.noQas |= MPT_TARGET_NO_NEGO_QAS;
					ddvprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT
						"noQas due to Capabilities=%x\n",
						ioc->name, pPP0->Capabilities));
				पूर्ण
				ioc->spi_data.maxBusWidth = pPP0->Capabilities & MPI_SCSIPORTPAGE0_CAP_WIDE ? 1 : 0;
				data = pPP0->Capabilities & MPI_SCSIPORTPAGE0_CAP_MAX_SYNC_OFFSET_MASK;
				अगर (data) अणु
					ioc->spi_data.maxSyncOffset = (u8) (data >> 16);
					data = pPP0->Capabilities & MPI_SCSIPORTPAGE0_CAP_MIN_SYNC_PERIOD_MASK;
					ioc->spi_data.minSyncFactor = (u8) (data >> 8);
					ddvprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT
						"PortPage0 minSyncFactor=%x\n",
						ioc->name, ioc->spi_data.minSyncFactor));
				पूर्ण अन्यथा अणु
					ioc->spi_data.maxSyncOffset = 0;
					ioc->spi_data.minSyncFactor = MPT_ASYNC;
				पूर्ण

				ioc->spi_data.busType = pPP0->PhysicalInterface & MPI_SCSIPORTPAGE0_PHY_SIGNAL_TYPE_MASK;

				/* Update the minSyncFactor based on bus type.
				 */
				अगर ((ioc->spi_data.busType == MPI_SCSIPORTPAGE0_PHY_SIGNAL_HVD) ||
					(ioc->spi_data.busType == MPI_SCSIPORTPAGE0_PHY_SIGNAL_SE))  अणु

					अगर (ioc->spi_data.minSyncFactor < MPT_ULTRA) अणु
						ioc->spi_data.minSyncFactor = MPT_ULTRA;
						ddvprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT
							"HVD or SE detected, minSyncFactor=%x\n",
							ioc->name, ioc->spi_data.minSyncFactor));
					पूर्ण
				पूर्ण
			पूर्ण
			अगर (pbuf) अणु
				pci_मुक्त_consistent(ioc->pcidev, header.PageLength * 4, pbuf, buf_dma);
			पूर्ण
		पूर्ण
	पूर्ण

	/* SCSI Port Page 2 - Read the header then the page.
	 */
	header.PageVersion = 0;
	header.PageLength = 0;
	header.PageNumber = 2;
	header.PageType = MPI_CONFIG_PAGETYPE_SCSI_PORT;
	cfg.cfghdr.hdr = &header;
	cfg.physAddr = -1;
	cfg.pageAddr = portnum;
	cfg.action = MPI_CONFIG_ACTION_PAGE_HEADER;
	cfg.dir = 0;
	अगर (mpt_config(ioc, &cfg) != 0)
		वापस -EFAULT;

	अगर (header.PageLength > 0) अणु
		/* Allocate memory and पढ़ो SCSI Port Page 2
		 */
		pbuf = pci_alloc_consistent(ioc->pcidev, header.PageLength * 4, &buf_dma);
		अगर (pbuf) अणु
			cfg.action = MPI_CONFIG_ACTION_PAGE_READ_NVRAM;
			cfg.physAddr = buf_dma;
			अगर (mpt_config(ioc, &cfg) != 0) अणु
				/* Nvram data is left with INVALID mark
				 */
				rc = 1;
			पूर्ण अन्यथा अगर (ioc->pcidev->venकरोr == PCI_VENDOR_ID_ATTO) अणु

				/* This is an ATTO adapter, पढ़ो Page2 accordingly
				*/
				ATTO_SCSIPortPage2_t *pPP2 = (ATTO_SCSIPortPage2_t  *) pbuf;
				ATTODeviceInfo_t *pdevice = शून्य;
				u16 ATTOFlags;

				/* Save the Port Page 2 data
				 * (reक्रमmat पूर्णांकo a 32bit quantity)
				 */
				क्रम (ii=0; ii < MPT_MAX_SCSI_DEVICES; ii++) अणु
				  pdevice = &pPP2->DeviceSettings[ii];
				  ATTOFlags = le16_to_cpu(pdevice->ATTOFlags);
				  data = 0;

				  /* Translate ATTO device flags to LSI क्रमmat
				   */
				  अगर (ATTOFlags & ATTOFLAG_DISC)
				    data |= (MPI_SCSIPORTPAGE2_DEVICE_DISCONNECT_ENABLE);
				  अगर (ATTOFlags & ATTOFLAG_ID_ENB)
				    data |= (MPI_SCSIPORTPAGE2_DEVICE_ID_SCAN_ENABLE);
				  अगर (ATTOFlags & ATTOFLAG_LUN_ENB)
				    data |= (MPI_SCSIPORTPAGE2_DEVICE_LUN_SCAN_ENABLE);
				  अगर (ATTOFlags & ATTOFLAG_TAGGED)
				    data |= (MPI_SCSIPORTPAGE2_DEVICE_TAG_QUEUE_ENABLE);
				  अगर (!(ATTOFlags & ATTOFLAG_WIDE_ENB))
				    data |= (MPI_SCSIPORTPAGE2_DEVICE_WIDE_DISABLE);

				  data = (data << 16) | (pdevice->Period << 8) | 10;
				  ioc->spi_data.nvram[ii] = data;
				पूर्ण
			पूर्ण अन्यथा अणु
				SCSIPortPage2_t *pPP2 = (SCSIPortPage2_t  *) pbuf;
				MpiDeviceInfo_t	*pdevice = शून्य;

				/*
				 * Save "Set to Avoid SCSI Bus Resets" flag
				 */
				ioc->spi_data.bus_reset =
				    (le32_to_cpu(pPP2->PortFlags) &
			        MPI_SCSIPORTPAGE2_PORT_FLAGS_AVOID_SCSI_RESET) ?
				    0 : 1 ;

				/* Save the Port Page 2 data
				 * (reक्रमmat पूर्णांकo a 32bit quantity)
				 */
				data = le32_to_cpu(pPP2->PortFlags) & MPI_SCSIPORTPAGE2_PORT_FLAGS_DV_MASK;
				ioc->spi_data.PortFlags = data;
				क्रम (ii=0; ii < MPT_MAX_SCSI_DEVICES; ii++) अणु
					pdevice = &pPP2->DeviceSettings[ii];
					data = (le16_to_cpu(pdevice->DeviceFlags) << 16) |
						(pdevice->SyncFactor << 8) | pdevice->Timeout;
					ioc->spi_data.nvram[ii] = data;
				पूर्ण
			पूर्ण

			pci_मुक्त_consistent(ioc->pcidev, header.PageLength * 4, pbuf, buf_dma);
		पूर्ण
	पूर्ण

	/* Update Adapter limits with those from NVRAM
	 * Comment: Don't need to करो this. Target perक्रमmance
	 * parameters will never exceed the adapters limits.
	 */

	वापस rc;
पूर्ण

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/**
 *	mpt_पढ़ोScsiDevicePageHeaders - save version and length of SDP1
 *	@ioc: Poपूर्णांकer to a Adapter Strucutre
 *	@portnum: IOC port number
 *
 *	Return: -EFAULT अगर पढ़ो of config page header fails
 *		or 0 अगर success.
 */
अटल पूर्णांक
mpt_पढ़ोScsiDevicePageHeaders(MPT_ADAPTER *ioc, पूर्णांक portnum)
अणु
	CONFIGPARMS		 cfg;
	ConfigPageHeader_t	 header;

	/* Read the SCSI Device Page 1 header
	 */
	header.PageVersion = 0;
	header.PageLength = 0;
	header.PageNumber = 1;
	header.PageType = MPI_CONFIG_PAGETYPE_SCSI_DEVICE;
	cfg.cfghdr.hdr = &header;
	cfg.physAddr = -1;
	cfg.pageAddr = portnum;
	cfg.action = MPI_CONFIG_ACTION_PAGE_HEADER;
	cfg.dir = 0;
	cfg.समयout = 0;
	अगर (mpt_config(ioc, &cfg) != 0)
		 वापस -EFAULT;

	ioc->spi_data.sdp1version = cfg.cfghdr.hdr->PageVersion;
	ioc->spi_data.sdp1length = cfg.cfghdr.hdr->PageLength;

	header.PageVersion = 0;
	header.PageLength = 0;
	header.PageNumber = 0;
	header.PageType = MPI_CONFIG_PAGETYPE_SCSI_DEVICE;
	अगर (mpt_config(ioc, &cfg) != 0)
		 वापस -EFAULT;

	ioc->spi_data.sdp0version = cfg.cfghdr.hdr->PageVersion;
	ioc->spi_data.sdp0length = cfg.cfghdr.hdr->PageLength;

	dcprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT "Headers: 0: version %d length %d\n",
			ioc->name, ioc->spi_data.sdp0version, ioc->spi_data.sdp0length));

	dcprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT "Headers: 1: version %d length %d\n",
			ioc->name, ioc->spi_data.sdp1version, ioc->spi_data.sdp1length));
	वापस 0;
पूर्ण

/**
 * mpt_inactive_raid_list_मुक्त - This clears this link list.
 * @ioc : poपूर्णांकer to per adapter काष्ठाure
 **/
अटल व्योम
mpt_inactive_raid_list_मुक्त(MPT_ADAPTER *ioc)
अणु
	काष्ठा inactive_raid_component_info *component_info, *pNext;

	अगर (list_empty(&ioc->raid_data.inactive_list))
		वापस;

	mutex_lock(&ioc->raid_data.inactive_list_mutex);
	list_क्रम_each_entry_safe(component_info, pNext,
	    &ioc->raid_data.inactive_list, list) अणु
		list_del(&component_info->list);
		kमुक्त(component_info);
	पूर्ण
	mutex_unlock(&ioc->raid_data.inactive_list_mutex);
पूर्ण

/**
 * mpt_inactive_raid_volumes - sets up link list of phy_disk_nums क्रम devices beदीर्घing in an inactive volume
 *
 * @ioc : poपूर्णांकer to per adapter काष्ठाure
 * @channel : volume channel
 * @id : volume target id
 **/
अटल व्योम
mpt_inactive_raid_volumes(MPT_ADAPTER *ioc, u8 channel, u8 id)
अणु
	CONFIGPARMS			cfg;
	ConfigPageHeader_t		hdr;
	dma_addr_t			dma_handle;
	pRaidVolumePage0_t		buffer = शून्य;
	पूर्णांक				i;
	RaidPhysDiskPage0_t 		phys_disk;
	काष्ठा inactive_raid_component_info *component_info;
	पूर्णांक				handle_inactive_volumes;

	स_रखो(&cfg, 0 , माप(CONFIGPARMS));
	स_रखो(&hdr, 0 , माप(ConfigPageHeader_t));
	hdr.PageType = MPI_CONFIG_PAGETYPE_RAID_VOLUME;
	cfg.pageAddr = (channel << 8) + id;
	cfg.cfghdr.hdr = &hdr;
	cfg.action = MPI_CONFIG_ACTION_PAGE_HEADER;

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

	handle_inactive_volumes =
	   (buffer->VolumeStatus.Flags & MPI_RAIDVOL0_STATUS_FLAG_VOLUME_INACTIVE ||
	   (buffer->VolumeStatus.Flags & MPI_RAIDVOL0_STATUS_FLAG_ENABLED) == 0 ||
	    buffer->VolumeStatus.State == MPI_RAIDVOL0_STATUS_STATE_FAILED ||
	    buffer->VolumeStatus.State == MPI_RAIDVOL0_STATUS_STATE_MISSING) ? 1 : 0;

	अगर (!handle_inactive_volumes)
		जाओ out;

	mutex_lock(&ioc->raid_data.inactive_list_mutex);
	क्रम (i = 0; i < buffer->NumPhysDisks; i++) अणु
		अगर(mpt_raid_phys_disk_pg0(ioc,
		    buffer->PhysDisk[i].PhysDiskNum, &phys_disk) != 0)
			जारी;

		अगर ((component_info = kदो_स्मृति(माप (*component_info),
		 GFP_KERNEL)) == शून्य)
			जारी;

		component_info->volumeID = id;
		component_info->volumeBus = channel;
		component_info->d.PhysDiskNum = phys_disk.PhysDiskNum;
		component_info->d.PhysDiskBus = phys_disk.PhysDiskBus;
		component_info->d.PhysDiskID = phys_disk.PhysDiskID;
		component_info->d.PhysDiskIOC = phys_disk.PhysDiskIOC;

		list_add_tail(&component_info->list,
		    &ioc->raid_data.inactive_list);
	पूर्ण
	mutex_unlock(&ioc->raid_data.inactive_list_mutex);

 out:
	अगर (buffer)
		pci_मुक्त_consistent(ioc->pcidev, hdr.PageLength * 4, buffer,
		    dma_handle);
पूर्ण

/**
 *	mpt_raid_phys_disk_pg0 - वापसs phys disk page zero
 *	@ioc: Poपूर्णांकer to a Adapter Structure
 *	@phys_disk_num: io unit unique phys disk num generated by the ioc
 *	@phys_disk: requested payload data वापसed
 *
 *	Return:
 *	0 on success
 *	-EFAULT अगर पढ़ो of config page header fails or data poपूर्णांकer not शून्य
 *	-ENOMEM अगर pci_alloc failed
 **/
पूर्णांक
mpt_raid_phys_disk_pg0(MPT_ADAPTER *ioc, u8 phys_disk_num,
			RaidPhysDiskPage0_t *phys_disk)
अणु
	CONFIGPARMS			cfg;
	ConfigPageHeader_t		hdr;
	dma_addr_t			dma_handle;
	pRaidPhysDiskPage0_t		buffer = शून्य;
	पूर्णांक				rc;

	स_रखो(&cfg, 0 , माप(CONFIGPARMS));
	स_रखो(&hdr, 0 , माप(ConfigPageHeader_t));
	स_रखो(phys_disk, 0, माप(RaidPhysDiskPage0_t));

	hdr.PageVersion = MPI_RAIDPHYSDISKPAGE0_PAGEVERSION;
	hdr.PageType = MPI_CONFIG_PAGETYPE_RAID_PHYSDISK;
	cfg.cfghdr.hdr = &hdr;
	cfg.physAddr = -1;
	cfg.action = MPI_CONFIG_ACTION_PAGE_HEADER;

	अगर (mpt_config(ioc, &cfg) != 0) अणु
		rc = -EFAULT;
		जाओ out;
	पूर्ण

	अगर (!hdr.PageLength) अणु
		rc = -EFAULT;
		जाओ out;
	पूर्ण

	buffer = pci_alloc_consistent(ioc->pcidev, hdr.PageLength * 4,
	    &dma_handle);

	अगर (!buffer) अणु
		rc = -ENOMEM;
		जाओ out;
	पूर्ण

	cfg.physAddr = dma_handle;
	cfg.action = MPI_CONFIG_ACTION_PAGE_READ_CURRENT;
	cfg.pageAddr = phys_disk_num;

	अगर (mpt_config(ioc, &cfg) != 0) अणु
		rc = -EFAULT;
		जाओ out;
	पूर्ण

	rc = 0;
	स_नकल(phys_disk, buffer, माप(*buffer));
	phys_disk->MaxLBA = le32_to_cpu(buffer->MaxLBA);

 out:

	अगर (buffer)
		pci_मुक्त_consistent(ioc->pcidev, hdr.PageLength * 4, buffer,
		    dma_handle);

	वापस rc;
पूर्ण

/**
 *	mpt_raid_phys_disk_get_num_paths - वापसs number paths associated to this phys_num
 *	@ioc: Poपूर्णांकer to a Adapter Structure
 *	@phys_disk_num: io unit unique phys disk num generated by the ioc
 *
 *	Return:
 *	वापसs number paths
 **/
पूर्णांक
mpt_raid_phys_disk_get_num_paths(MPT_ADAPTER *ioc, u8 phys_disk_num)
अणु
	CONFIGPARMS		 	cfg;
	ConfigPageHeader_t	 	hdr;
	dma_addr_t			dma_handle;
	pRaidPhysDiskPage1_t		buffer = शून्य;
	पूर्णांक				rc;

	स_रखो(&cfg, 0 , माप(CONFIGPARMS));
	स_रखो(&hdr, 0 , माप(ConfigPageHeader_t));

	hdr.PageVersion = MPI_RAIDPHYSDISKPAGE1_PAGEVERSION;
	hdr.PageType = MPI_CONFIG_PAGETYPE_RAID_PHYSDISK;
	hdr.PageNumber = 1;
	cfg.cfghdr.hdr = &hdr;
	cfg.physAddr = -1;
	cfg.action = MPI_CONFIG_ACTION_PAGE_HEADER;

	अगर (mpt_config(ioc, &cfg) != 0) अणु
		rc = 0;
		जाओ out;
	पूर्ण

	अगर (!hdr.PageLength) अणु
		rc = 0;
		जाओ out;
	पूर्ण

	buffer = pci_alloc_consistent(ioc->pcidev, hdr.PageLength * 4,
	    &dma_handle);

	अगर (!buffer) अणु
		rc = 0;
		जाओ out;
	पूर्ण

	cfg.physAddr = dma_handle;
	cfg.action = MPI_CONFIG_ACTION_PAGE_READ_CURRENT;
	cfg.pageAddr = phys_disk_num;

	अगर (mpt_config(ioc, &cfg) != 0) अणु
		rc = 0;
		जाओ out;
	पूर्ण

	rc = buffer->NumPhysDiskPaths;
 out:

	अगर (buffer)
		pci_मुक्त_consistent(ioc->pcidev, hdr.PageLength * 4, buffer,
		    dma_handle);

	वापस rc;
पूर्ण
EXPORT_SYMBOL(mpt_raid_phys_disk_get_num_paths);

/**
 *	mpt_raid_phys_disk_pg1 - वापसs phys disk page 1
 *	@ioc: Poपूर्णांकer to a Adapter Structure
 *	@phys_disk_num: io unit unique phys disk num generated by the ioc
 *	@phys_disk: requested payload data वापसed
 *
 *	Return:
 *	0 on success
 *	-EFAULT अगर पढ़ो of config page header fails or data poपूर्णांकer not शून्य
 *	-ENOMEM अगर pci_alloc failed
 **/
पूर्णांक
mpt_raid_phys_disk_pg1(MPT_ADAPTER *ioc, u8 phys_disk_num,
		RaidPhysDiskPage1_t *phys_disk)
अणु
	CONFIGPARMS		 	cfg;
	ConfigPageHeader_t	 	hdr;
	dma_addr_t			dma_handle;
	pRaidPhysDiskPage1_t		buffer = शून्य;
	पूर्णांक				rc;
	पूर्णांक				i;
	__le64				sas_address;

	स_रखो(&cfg, 0 , माप(CONFIGPARMS));
	स_रखो(&hdr, 0 , माप(ConfigPageHeader_t));
	rc = 0;

	hdr.PageVersion = MPI_RAIDPHYSDISKPAGE1_PAGEVERSION;
	hdr.PageType = MPI_CONFIG_PAGETYPE_RAID_PHYSDISK;
	hdr.PageNumber = 1;
	cfg.cfghdr.hdr = &hdr;
	cfg.physAddr = -1;
	cfg.action = MPI_CONFIG_ACTION_PAGE_HEADER;

	अगर (mpt_config(ioc, &cfg) != 0) अणु
		rc = -EFAULT;
		जाओ out;
	पूर्ण

	अगर (!hdr.PageLength) अणु
		rc = -EFAULT;
		जाओ out;
	पूर्ण

	buffer = pci_alloc_consistent(ioc->pcidev, hdr.PageLength * 4,
	    &dma_handle);

	अगर (!buffer) अणु
		rc = -ENOMEM;
		जाओ out;
	पूर्ण

	cfg.physAddr = dma_handle;
	cfg.action = MPI_CONFIG_ACTION_PAGE_READ_CURRENT;
	cfg.pageAddr = phys_disk_num;

	अगर (mpt_config(ioc, &cfg) != 0) अणु
		rc = -EFAULT;
		जाओ out;
	पूर्ण

	phys_disk->NumPhysDiskPaths = buffer->NumPhysDiskPaths;
	phys_disk->PhysDiskNum = phys_disk_num;
	क्रम (i = 0; i < phys_disk->NumPhysDiskPaths; i++) अणु
		phys_disk->Path[i].PhysDiskID = buffer->Path[i].PhysDiskID;
		phys_disk->Path[i].PhysDiskBus = buffer->Path[i].PhysDiskBus;
		phys_disk->Path[i].OwnerIdentअगरier =
				buffer->Path[i].OwnerIdentअगरier;
		phys_disk->Path[i].Flags = le16_to_cpu(buffer->Path[i].Flags);
		स_नकल(&sas_address, &buffer->Path[i].WWID, माप(__le64));
		sas_address = le64_to_cpu(sas_address);
		स_नकल(&phys_disk->Path[i].WWID, &sas_address, माप(__le64));
		स_नकल(&sas_address,
				&buffer->Path[i].OwnerWWID, माप(__le64));
		sas_address = le64_to_cpu(sas_address);
		स_नकल(&phys_disk->Path[i].OwnerWWID,
				&sas_address, माप(__le64));
	पूर्ण

 out:

	अगर (buffer)
		pci_मुक्त_consistent(ioc->pcidev, hdr.PageLength * 4, buffer,
		    dma_handle);

	वापस rc;
पूर्ण
EXPORT_SYMBOL(mpt_raid_phys_disk_pg1);


/**
 *	mpt_findImVolumes - Identअगरy IDs of hidden disks and RAID Volumes
 *	@ioc: Poपूर्णांकer to a Adapter Strucutre
 *
 *	Return:
 *	0 on success
 *	-EFAULT अगर पढ़ो of config page header fails or data poपूर्णांकer not शून्य
 *	-ENOMEM अगर pci_alloc failed
 **/
पूर्णांक
mpt_findImVolumes(MPT_ADAPTER *ioc)
अणु
	IOCPage2_t		*pIoc2;
	u8			*mem;
	dma_addr_t		 ioc2_dma;
	CONFIGPARMS		 cfg;
	ConfigPageHeader_t	 header;
	पूर्णांक			 rc = 0;
	पूर्णांक			 iocpage2sz;
	पूर्णांक			 i;

	अगर (!ioc->ir_firmware)
		वापस 0;

	/* Free the old page
	 */
	kमुक्त(ioc->raid_data.pIocPg2);
	ioc->raid_data.pIocPg2 = शून्य;
	mpt_inactive_raid_list_मुक्त(ioc);

	/* Read IOCP2 header then the page.
	 */
	header.PageVersion = 0;
	header.PageLength = 0;
	header.PageNumber = 2;
	header.PageType = MPI_CONFIG_PAGETYPE_IOC;
	cfg.cfghdr.hdr = &header;
	cfg.physAddr = -1;
	cfg.pageAddr = 0;
	cfg.action = MPI_CONFIG_ACTION_PAGE_HEADER;
	cfg.dir = 0;
	cfg.समयout = 0;
	अगर (mpt_config(ioc, &cfg) != 0)
		 वापस -EFAULT;

	अगर (header.PageLength == 0)
		वापस -EFAULT;

	iocpage2sz = header.PageLength * 4;
	pIoc2 = pci_alloc_consistent(ioc->pcidev, iocpage2sz, &ioc2_dma);
	अगर (!pIoc2)
		वापस -ENOMEM;

	cfg.action = MPI_CONFIG_ACTION_PAGE_READ_CURRENT;
	cfg.physAddr = ioc2_dma;
	अगर (mpt_config(ioc, &cfg) != 0)
		जाओ out;

	mem = kmemdup(pIoc2, iocpage2sz, GFP_KERNEL);
	अगर (!mem) अणु
		rc = -ENOMEM;
		जाओ out;
	पूर्ण

	ioc->raid_data.pIocPg2 = (IOCPage2_t *) mem;

	mpt_पढ़ो_ioc_pg_3(ioc);

	क्रम (i = 0; i < pIoc2->NumActiveVolumes ; i++)
		mpt_inactive_raid_volumes(ioc,
		    pIoc2->RaidVolume[i].VolumeBus,
		    pIoc2->RaidVolume[i].VolumeID);

 out:
	pci_मुक्त_consistent(ioc->pcidev, iocpage2sz, pIoc2, ioc2_dma);

	वापस rc;
पूर्ण

अटल पूर्णांक
mpt_पढ़ो_ioc_pg_3(MPT_ADAPTER *ioc)
अणु
	IOCPage3_t		*pIoc3;
	u8			*mem;
	CONFIGPARMS		 cfg;
	ConfigPageHeader_t	 header;
	dma_addr_t		 ioc3_dma;
	पूर्णांक			 iocpage3sz = 0;

	/* Free the old page
	 */
	kमुक्त(ioc->raid_data.pIocPg3);
	ioc->raid_data.pIocPg3 = शून्य;

	/* There is at least one physical disk.
	 * Read and save IOC Page 3
	 */
	header.PageVersion = 0;
	header.PageLength = 0;
	header.PageNumber = 3;
	header.PageType = MPI_CONFIG_PAGETYPE_IOC;
	cfg.cfghdr.hdr = &header;
	cfg.physAddr = -1;
	cfg.pageAddr = 0;
	cfg.action = MPI_CONFIG_ACTION_PAGE_HEADER;
	cfg.dir = 0;
	cfg.समयout = 0;
	अगर (mpt_config(ioc, &cfg) != 0)
		वापस 0;

	अगर (header.PageLength == 0)
		वापस 0;

	/* Read Header good, alloc memory
	 */
	iocpage3sz = header.PageLength * 4;
	pIoc3 = pci_alloc_consistent(ioc->pcidev, iocpage3sz, &ioc3_dma);
	अगर (!pIoc3)
		वापस 0;

	/* Read the Page and save the data
	 * पूर्णांकo दो_स्मृति'd memory.
	 */
	cfg.physAddr = ioc3_dma;
	cfg.action = MPI_CONFIG_ACTION_PAGE_READ_CURRENT;
	अगर (mpt_config(ioc, &cfg) == 0) अणु
		mem = kदो_स्मृति(iocpage3sz, GFP_KERNEL);
		अगर (mem) अणु
			स_नकल(mem, (u8 *)pIoc3, iocpage3sz);
			ioc->raid_data.pIocPg3 = (IOCPage3_t *) mem;
		पूर्ण
	पूर्ण

	pci_मुक्त_consistent(ioc->pcidev, iocpage3sz, pIoc3, ioc3_dma);

	वापस 0;
पूर्ण

अटल व्योम
mpt_पढ़ो_ioc_pg_4(MPT_ADAPTER *ioc)
अणु
	IOCPage4_t		*pIoc4;
	CONFIGPARMS		 cfg;
	ConfigPageHeader_t	 header;
	dma_addr_t		 ioc4_dma;
	पूर्णांक			 iocpage4sz;

	/* Read and save IOC Page 4
	 */
	header.PageVersion = 0;
	header.PageLength = 0;
	header.PageNumber = 4;
	header.PageType = MPI_CONFIG_PAGETYPE_IOC;
	cfg.cfghdr.hdr = &header;
	cfg.physAddr = -1;
	cfg.pageAddr = 0;
	cfg.action = MPI_CONFIG_ACTION_PAGE_HEADER;
	cfg.dir = 0;
	cfg.समयout = 0;
	अगर (mpt_config(ioc, &cfg) != 0)
		वापस;

	अगर (header.PageLength == 0)
		वापस;

	अगर ( (pIoc4 = ioc->spi_data.pIocPg4) == शून्य ) अणु
		iocpage4sz = (header.PageLength + 4) * 4; /* Allow 4 additional SEP's */
		pIoc4 = pci_alloc_consistent(ioc->pcidev, iocpage4sz, &ioc4_dma);
		अगर (!pIoc4)
			वापस;
		ioc->alloc_total += iocpage4sz;
	पूर्ण अन्यथा अणु
		ioc4_dma = ioc->spi_data.IocPg4_dma;
		iocpage4sz = ioc->spi_data.IocPg4Sz;
	पूर्ण

	/* Read the Page पूर्णांकo dma memory.
	 */
	cfg.physAddr = ioc4_dma;
	cfg.action = MPI_CONFIG_ACTION_PAGE_READ_CURRENT;
	अगर (mpt_config(ioc, &cfg) == 0) अणु
		ioc->spi_data.pIocPg4 = (IOCPage4_t *) pIoc4;
		ioc->spi_data.IocPg4_dma = ioc4_dma;
		ioc->spi_data.IocPg4Sz = iocpage4sz;
	पूर्ण अन्यथा अणु
		pci_मुक्त_consistent(ioc->pcidev, iocpage4sz, pIoc4, ioc4_dma);
		ioc->spi_data.pIocPg4 = शून्य;
		ioc->alloc_total -= iocpage4sz;
	पूर्ण
पूर्ण

अटल व्योम
mpt_पढ़ो_ioc_pg_1(MPT_ADAPTER *ioc)
अणु
	IOCPage1_t		*pIoc1;
	CONFIGPARMS		 cfg;
	ConfigPageHeader_t	 header;
	dma_addr_t		 ioc1_dma;
	पूर्णांक			 iocpage1sz = 0;
	u32			 पंचांगp;

	/* Check the Coalescing Timeout in IOC Page 1
	 */
	header.PageVersion = 0;
	header.PageLength = 0;
	header.PageNumber = 1;
	header.PageType = MPI_CONFIG_PAGETYPE_IOC;
	cfg.cfghdr.hdr = &header;
	cfg.physAddr = -1;
	cfg.pageAddr = 0;
	cfg.action = MPI_CONFIG_ACTION_PAGE_HEADER;
	cfg.dir = 0;
	cfg.समयout = 0;
	अगर (mpt_config(ioc, &cfg) != 0)
		वापस;

	अगर (header.PageLength == 0)
		वापस;

	/* Read Header good, alloc memory
	 */
	iocpage1sz = header.PageLength * 4;
	pIoc1 = pci_alloc_consistent(ioc->pcidev, iocpage1sz, &ioc1_dma);
	अगर (!pIoc1)
		वापस;

	/* Read the Page and check coalescing समयout
	 */
	cfg.physAddr = ioc1_dma;
	cfg.action = MPI_CONFIG_ACTION_PAGE_READ_CURRENT;
	अगर (mpt_config(ioc, &cfg) == 0) अणु

		पंचांगp = le32_to_cpu(pIoc1->Flags) & MPI_IOCPAGE1_REPLY_COALESCING;
		अगर (पंचांगp == MPI_IOCPAGE1_REPLY_COALESCING) अणु
			पंचांगp = le32_to_cpu(pIoc1->CoalescingTimeout);

			dprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT "Coalescing Enabled Timeout = %d\n",
					ioc->name, पंचांगp));

			अगर (पंचांगp > MPT_COALESCING_TIMEOUT) अणु
				pIoc1->CoalescingTimeout = cpu_to_le32(MPT_COALESCING_TIMEOUT);

				/* Write NVRAM and current
				 */
				cfg.dir = 1;
				cfg.action = MPI_CONFIG_ACTION_PAGE_WRITE_CURRENT;
				अगर (mpt_config(ioc, &cfg) == 0) अणु
					dprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT "Reset Current Coalescing Timeout to = %d\n",
							ioc->name, MPT_COALESCING_TIMEOUT));

					cfg.action = MPI_CONFIG_ACTION_PAGE_WRITE_NVRAM;
					अगर (mpt_config(ioc, &cfg) == 0) अणु
						dprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT
								"Reset NVRAM Coalescing Timeout to = %d\n",
								ioc->name, MPT_COALESCING_TIMEOUT));
					पूर्ण अन्यथा अणु
						dprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT
								"Reset NVRAM Coalescing Timeout Failed\n",
								ioc->name));
					पूर्ण

				पूर्ण अन्यथा अणु
					dprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_WARN_FMT
						"Reset of Current Coalescing Timeout Failed!\n",
						ioc->name));
				पूर्ण
			पूर्ण

		पूर्ण अन्यथा अणु
			dprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_WARN_FMT "Coalescing Disabled\n", ioc->name));
		पूर्ण
	पूर्ण

	pci_मुक्त_consistent(ioc->pcidev, iocpage1sz, pIoc1, ioc1_dma);

	वापस;
पूर्ण

अटल व्योम
mpt_get_manufacturing_pg_0(MPT_ADAPTER *ioc)
अणु
	CONFIGPARMS		cfg;
	ConfigPageHeader_t	hdr;
	dma_addr_t		buf_dma;
	ManufacturingPage0_t	*pbuf = शून्य;

	स_रखो(&cfg, 0 , माप(CONFIGPARMS));
	स_रखो(&hdr, 0 , माप(ConfigPageHeader_t));

	hdr.PageType = MPI_CONFIG_PAGETYPE_MANUFACTURING;
	cfg.cfghdr.hdr = &hdr;
	cfg.physAddr = -1;
	cfg.action = MPI_CONFIG_ACTION_PAGE_HEADER;
	cfg.समयout = 10;

	अगर (mpt_config(ioc, &cfg) != 0)
		जाओ out;

	अगर (!cfg.cfghdr.hdr->PageLength)
		जाओ out;

	cfg.action = MPI_CONFIG_ACTION_PAGE_READ_CURRENT;
	pbuf = pci_alloc_consistent(ioc->pcidev, hdr.PageLength * 4, &buf_dma);
	अगर (!pbuf)
		जाओ out;

	cfg.physAddr = buf_dma;

	अगर (mpt_config(ioc, &cfg) != 0)
		जाओ out;

	स_नकल(ioc->board_name, pbuf->BoardName, माप(ioc->board_name));
	स_नकल(ioc->board_assembly, pbuf->BoardAssembly, माप(ioc->board_assembly));
	स_नकल(ioc->board_tracer, pbuf->BoardTracerNumber, माप(ioc->board_tracer));

out:

	अगर (pbuf)
		pci_मुक्त_consistent(ioc->pcidev, hdr.PageLength * 4, pbuf, buf_dma);
पूर्ण

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/**
 *	SendEventNotअगरication - Send EventNotअगरication (on or off) request to adapter
 *	@ioc: Poपूर्णांकer to MPT_ADAPTER काष्ठाure
 *	@EvSwitch: Event चयन flags
 *	@sleepFlag: Specअगरies whether the process can sleep
 */
अटल पूर्णांक
SendEventNotअगरication(MPT_ADAPTER *ioc, u8 EvSwitch, पूर्णांक sleepFlag)
अणु
	EventNotअगरication_t	evn;
	MPIDefaultReply_t	reply_buf;

	स_रखो(&evn, 0, माप(EventNotअगरication_t));
	स_रखो(&reply_buf, 0, माप(MPIDefaultReply_t));

	evn.Function = MPI_FUNCTION_EVENT_NOTIFICATION;
	evn.Switch = EvSwitch;
	evn.MsgContext = cpu_to_le32(mpt_base_index << 16);

	devtverboseprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT
	    "Sending EventNotification (%d) request %p\n",
	    ioc->name, EvSwitch, &evn));

	वापस mpt_handshake_req_reply_रुको(ioc, माप(EventNotअगरication_t),
	    (u32 *)&evn, माप(MPIDefaultReply_t), (u16 *)&reply_buf, 30,
	    sleepFlag);
पूर्ण

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/**
 *	SendEventAck - Send EventAck request to MPT adapter.
 *	@ioc: Poपूर्णांकer to MPT_ADAPTER काष्ठाure
 *	@evnp: Poपूर्णांकer to original EventNotअगरication request
 */
अटल पूर्णांक
SendEventAck(MPT_ADAPTER *ioc, EventNotअगरicationReply_t *evnp)
अणु
	EventAck_t	*pAck;

	अगर ((pAck = (EventAck_t *) mpt_get_msg_frame(mpt_base_index, ioc)) == शून्य) अणु
		dfailprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_WARN_FMT "%s, no msg frames!!\n",
		    ioc->name, __func__));
		वापस -1;
	पूर्ण

	devtverboseprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT "Sending EventAck\n", ioc->name));

	pAck->Function     = MPI_FUNCTION_EVENT_ACK;
	pAck->ChainOffset  = 0;
	pAck->Reserved[0]  = pAck->Reserved[1] = 0;
	pAck->MsgFlags     = 0;
	pAck->Reserved1[0] = pAck->Reserved1[1] = pAck->Reserved1[2] = 0;
	pAck->Event        = evnp->Event;
	pAck->EventContext = evnp->EventContext;

	mpt_put_msg_frame(mpt_base_index, ioc, (MPT_FRAME_HDR *)pAck);

	वापस 0;
पूर्ण

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/**
 *	mpt_config - Generic function to issue config message
 *	@ioc:   Poपूर्णांकer to an adapter काष्ठाure
 *	@pCfg:  Poपूर्णांकer to a configuration काष्ठाure. Struct contains
 *		action, page address, direction, physical address
 *		and poपूर्णांकer to a configuration page header
 *		Page header is updated.
 *
 *	Returns 0 क्रम success
 *	-EAGAIN अगर no msg frames currently available
 *	-EFAULT क्रम non-successful reply or no reply (समयout)
 */
पूर्णांक
mpt_config(MPT_ADAPTER *ioc, CONFIGPARMS *pCfg)
अणु
	Config_t	*pReq;
	ConfigReply_t	*pReply;
	ConfigExtendedPageHeader_t  *pExtHdr = शून्य;
	MPT_FRAME_HDR	*mf;
	पूर्णांक		 ii;
	पूर्णांक		 flagsLength;
	दीर्घ		 समयout;
	पूर्णांक		 ret;
	u8		 page_type = 0, extend_page;
	अचिन्हित दीर्घ 	 समयleft;
	अचिन्हित दीर्घ	 flags;
	u8		 issue_hard_reset = 0;
	u8		 retry_count = 0;

	might_sleep();

	/* करोn't send a config page during diag reset */
	spin_lock_irqsave(&ioc->taskmgmt_lock, flags);
	अगर (ioc->ioc_reset_in_progress) अणु
		dfailprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT
		    "%s: busy with host reset\n", ioc->name, __func__));
		spin_unlock_irqrestore(&ioc->taskmgmt_lock, flags);
		वापस -EBUSY;
	पूर्ण
	spin_unlock_irqrestore(&ioc->taskmgmt_lock, flags);

	/* करोn't send अगर no chance of success */
	अगर (!ioc->active ||
	    mpt_GetIocState(ioc, 1) != MPI_IOC_STATE_OPERATIONAL) अणु
		dfailprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT
		    "%s: ioc not operational, %d, %xh\n",
		    ioc->name, __func__, ioc->active,
		    mpt_GetIocState(ioc, 0)));
		वापस -EFAULT;
	पूर्ण

 retry_config:
	mutex_lock(&ioc->mptbase_cmds.mutex);
	/* init the पूर्णांकernal cmd काष्ठा */
	स_रखो(ioc->mptbase_cmds.reply, 0 , MPT_DEFAULT_FRAME_SIZE);
	INITIALIZE_MGMT_STATUS(ioc->mptbase_cmds.status)

	/* Get and Populate a मुक्त Frame
	 */
	अगर ((mf = mpt_get_msg_frame(mpt_base_index, ioc)) == शून्य) अणु
		dcprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_WARN_FMT
		"mpt_config: no msg frames!\n", ioc->name));
		ret = -EAGAIN;
		जाओ out;
	पूर्ण

	pReq = (Config_t *)mf;
	pReq->Action = pCfg->action;
	pReq->Reserved = 0;
	pReq->ChainOffset = 0;
	pReq->Function = MPI_FUNCTION_CONFIG;

	/* Assume page type is not extended and clear "reserved" fields. */
	pReq->ExtPageLength = 0;
	pReq->ExtPageType = 0;
	pReq->MsgFlags = 0;

	क्रम (ii=0; ii < 8; ii++)
		pReq->Reserved2[ii] = 0;

	pReq->Header.PageVersion = pCfg->cfghdr.hdr->PageVersion;
	pReq->Header.PageLength = pCfg->cfghdr.hdr->PageLength;
	pReq->Header.PageNumber = pCfg->cfghdr.hdr->PageNumber;
	pReq->Header.PageType = (pCfg->cfghdr.hdr->PageType & MPI_CONFIG_PAGETYPE_MASK);

	अगर ((pCfg->cfghdr.hdr->PageType & MPI_CONFIG_PAGETYPE_MASK) == MPI_CONFIG_PAGETYPE_EXTENDED) अणु
		pExtHdr = (ConfigExtendedPageHeader_t *)pCfg->cfghdr.ehdr;
		pReq->ExtPageLength = cpu_to_le16(pExtHdr->ExtPageLength);
		pReq->ExtPageType = pExtHdr->ExtPageType;
		pReq->Header.PageType = MPI_CONFIG_PAGETYPE_EXTENDED;

		/* Page Length must be treated as a reserved field क्रम the
		 * extended header.
		 */
		pReq->Header.PageLength = 0;
	पूर्ण

	pReq->PageAddress = cpu_to_le32(pCfg->pageAddr);

	/* Add a SGE to the config request.
	 */
	अगर (pCfg->dir)
		flagsLength = MPT_SGE_FLAGS_SSIMPLE_WRITE;
	अन्यथा
		flagsLength = MPT_SGE_FLAGS_SSIMPLE_READ;

	अगर ((pCfg->cfghdr.hdr->PageType & MPI_CONFIG_PAGETYPE_MASK) ==
	    MPI_CONFIG_PAGETYPE_EXTENDED) अणु
		flagsLength |= pExtHdr->ExtPageLength * 4;
		page_type = pReq->ExtPageType;
		extend_page = 1;
	पूर्ण अन्यथा अणु
		flagsLength |= pCfg->cfghdr.hdr->PageLength * 4;
		page_type = pReq->Header.PageType;
		extend_page = 0;
	पूर्ण

	dcprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT
	    "Sending Config request type 0x%x, page 0x%x and action %d\n",
	    ioc->name, page_type, pReq->Header.PageNumber, pReq->Action));

	ioc->add_sge((अक्षर *)&pReq->PageBufferSGE, flagsLength, pCfg->physAddr);
	समयout = (pCfg->समयout < 15) ? HZ*15 : HZ*pCfg->समयout;
	mpt_put_msg_frame(mpt_base_index, ioc, mf);
	समयleft = रुको_क्रम_completion_समयout(&ioc->mptbase_cmds.करोne,
		समयout);
	अगर (!(ioc->mptbase_cmds.status & MPT_MGMT_STATUS_COMMAND_GOOD)) अणु
		ret = -ETIME;
		dfailprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT
		    "Failed Sending Config request type 0x%x, page 0x%x,"
		    " action %d, status %xh, time left %ld\n\n",
			ioc->name, page_type, pReq->Header.PageNumber,
			pReq->Action, ioc->mptbase_cmds.status, समयleft));
		अगर (ioc->mptbase_cmds.status & MPT_MGMT_STATUS_DID_IOCRESET)
			जाओ out;
		अगर (!समयleft) अणु
			spin_lock_irqsave(&ioc->taskmgmt_lock, flags);
			अगर (ioc->ioc_reset_in_progress) अणु
				spin_unlock_irqrestore(&ioc->taskmgmt_lock,
					flags);
				prपूर्णांकk(MYIOC_s_INFO_FMT "%s: host reset in"
					" progress mpt_config timed out.!!\n",
					__func__, ioc->name);
				mutex_unlock(&ioc->mptbase_cmds.mutex);
				वापस -EFAULT;
			पूर्ण
			spin_unlock_irqrestore(&ioc->taskmgmt_lock, flags);
			issue_hard_reset = 1;
		पूर्ण
		जाओ out;
	पूर्ण

	अगर (!(ioc->mptbase_cmds.status & MPT_MGMT_STATUS_RF_VALID)) अणु
		ret = -1;
		जाओ out;
	पूर्ण
	pReply = (ConfigReply_t	*)ioc->mptbase_cmds.reply;
	ret = le16_to_cpu(pReply->IOCStatus) & MPI_IOCSTATUS_MASK;
	अगर (ret == MPI_IOCSTATUS_SUCCESS) अणु
		अगर (extend_page) अणु
			pCfg->cfghdr.ehdr->ExtPageLength =
			    le16_to_cpu(pReply->ExtPageLength);
			pCfg->cfghdr.ehdr->ExtPageType =
			    pReply->ExtPageType;
		पूर्ण
		pCfg->cfghdr.hdr->PageVersion = pReply->Header.PageVersion;
		pCfg->cfghdr.hdr->PageLength = pReply->Header.PageLength;
		pCfg->cfghdr.hdr->PageNumber = pReply->Header.PageNumber;
		pCfg->cfghdr.hdr->PageType = pReply->Header.PageType;

	पूर्ण

	अगर (retry_count)
		prपूर्णांकk(MYIOC_s_INFO_FMT "Retry completed "
		    "ret=0x%x timeleft=%ld\n",
		    ioc->name, ret, समयleft);

	dcprपूर्णांकk(ioc, prपूर्णांकk(KERN_DEBUG "IOCStatus=%04xh, IOCLogInfo=%08xh\n",
	     ret, le32_to_cpu(pReply->IOCLogInfo)));

out:

	CLEAR_MGMT_STATUS(ioc->mptbase_cmds.status)
	mutex_unlock(&ioc->mptbase_cmds.mutex);
	अगर (issue_hard_reset) अणु
		issue_hard_reset = 0;
		prपूर्णांकk(MYIOC_s_WARN_FMT
		       "Issuing Reset from %s!!, doorbell=0x%08x\n",
		       ioc->name, __func__, mpt_GetIocState(ioc, 0));
		अगर (retry_count == 0) अणु
			अगर (mpt_Soft_Hard_ResetHandler(ioc, CAN_SLEEP) != 0)
				retry_count++;
		पूर्ण अन्यथा
			mpt_HardResetHandler(ioc, CAN_SLEEP);

		mpt_मुक्त_msg_frame(ioc, mf);
		/* attempt one retry क्रम a समयd out command */
		अगर (retry_count < 2) अणु
			prपूर्णांकk(MYIOC_s_INFO_FMT
			    "Attempting Retry Config request"
			    " type 0x%x, page 0x%x,"
			    " action %d\n", ioc->name, page_type,
			    pCfg->cfghdr.hdr->PageNumber, pCfg->action);
			retry_count++;
			जाओ retry_config;
		पूर्ण
	पूर्ण
	वापस ret;

पूर्ण

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/**
 *	mpt_ioc_reset - Base cleanup क्रम hard reset
 *	@ioc: Poपूर्णांकer to the adapter काष्ठाure
 *	@reset_phase: Indicates pre- or post-reset functionality
 *
 *	Remark: Frees resources with पूर्णांकernally generated commands.
 */
अटल पूर्णांक
mpt_ioc_reset(MPT_ADAPTER *ioc, पूर्णांक reset_phase)
अणु
	चयन (reset_phase) अणु
	हाल MPT_IOC_SETUP_RESET:
		ioc->taskmgmt_quiesce_io = 1;
		dपंचांगprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT
		    "%s: MPT_IOC_SETUP_RESET\n", ioc->name, __func__));
		अवरोध;
	हाल MPT_IOC_PRE_RESET:
		dपंचांगprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT
		    "%s: MPT_IOC_PRE_RESET\n", ioc->name, __func__));
		अवरोध;
	हाल MPT_IOC_POST_RESET:
		dपंचांगprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT
		    "%s: MPT_IOC_POST_RESET\n",  ioc->name, __func__));
/* wake up mptbase_cmds */
		अगर (ioc->mptbase_cmds.status & MPT_MGMT_STATUS_PENDING) अणु
			ioc->mptbase_cmds.status |=
			    MPT_MGMT_STATUS_DID_IOCRESET;
			complete(&ioc->mptbase_cmds.करोne);
		पूर्ण
/* wake up taskmgmt_cmds */
		अगर (ioc->taskmgmt_cmds.status & MPT_MGMT_STATUS_PENDING) अणु
			ioc->taskmgmt_cmds.status |=
				MPT_MGMT_STATUS_DID_IOCRESET;
			complete(&ioc->taskmgmt_cmds.करोne);
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 1;		/* currently means nothing really */
पूर्ण


#अगर_घोषित CONFIG_PROC_FS		/* अणु */
/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/*
 *	procfs (%MPT_PROCFS_MPTBASEसूची/...) support stuff...
 */
/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/**
 *	procmpt_create - Create %MPT_PROCFS_MPTBASEसूची entries.
 *
 *	Returns 0 क्रम success, non-zero क्रम failure.
 */
अटल पूर्णांक
procmpt_create(व्योम)
अणु
	mpt_proc_root_dir = proc_सूची_गढ़ो(MPT_PROCFS_MPTBASEसूची, शून्य);
	अगर (mpt_proc_root_dir == शून्य)
		वापस -ENOTसूची;

	proc_create_single("summary", S_IRUGO, mpt_proc_root_dir,
			mpt_summary_proc_show);
	proc_create_single("version", S_IRUGO, mpt_proc_root_dir,
			mpt_version_proc_show);
	वापस 0;
पूर्ण

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/**
 *	procmpt_destroy - Tear करोwn %MPT_PROCFS_MPTBASEसूची entries.
 *
 *	Returns 0 क्रम success, non-zero क्रम failure.
 */
अटल व्योम
procmpt_destroy(व्योम)
अणु
	हटाओ_proc_entry("version", mpt_proc_root_dir);
	हटाओ_proc_entry("summary", mpt_proc_root_dir);
	हटाओ_proc_entry(MPT_PROCFS_MPTBASEसूची, शून्य);
पूर्ण

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/*
 *	Handles पढ़ो request from /proc/mpt/summary or /proc/mpt/iocN/summary.
 */
अटल व्योम seq_mpt_prपूर्णांक_ioc_summary(MPT_ADAPTER *ioc, काष्ठा seq_file *m, पूर्णांक showlan);

अटल पूर्णांक mpt_summary_proc_show(काष्ठा seq_file *m, व्योम *v)
अणु
	MPT_ADAPTER *ioc = m->निजी;

	अगर (ioc) अणु
		seq_mpt_prपूर्णांक_ioc_summary(ioc, m, 1);
	पूर्ण अन्यथा अणु
		list_क्रम_each_entry(ioc, &ioc_list, list) अणु
			seq_mpt_prपूर्णांक_ioc_summary(ioc, m, 1);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mpt_version_proc_show(काष्ठा seq_file *m, व्योम *v)
अणु
	u8	 cb_idx;
	पूर्णांक	 scsi, fc, sas, lan, ctl, targ, dmp;
	अक्षर	*drvname;

	seq_म_लिखो(m, "%s-%s\n", "mptlinux", MPT_LINUX_VERSION_COMMON);
	seq_म_लिखो(m, "  Fusion MPT base driver\n");

	scsi = fc = sas = lan = ctl = targ = dmp = 0;
	क्रम (cb_idx = MPT_MAX_PROTOCOL_DRIVERS-1; cb_idx; cb_idx--) अणु
		drvname = शून्य;
		अगर (MptCallbacks[cb_idx]) अणु
			चयन (MptDriverClass[cb_idx]) अणु
			हाल MPTSPI_DRIVER:
				अगर (!scsi++) drvname = "SPI host";
				अवरोध;
			हाल MPTFC_DRIVER:
				अगर (!fc++) drvname = "FC host";
				अवरोध;
			हाल MPTSAS_DRIVER:
				अगर (!sas++) drvname = "SAS host";
				अवरोध;
			हाल MPTLAN_DRIVER:
				अगर (!lan++) drvname = "LAN";
				अवरोध;
			हाल MPTSTM_DRIVER:
				अगर (!targ++) drvname = "SCSI target";
				अवरोध;
			हाल MPTCTL_DRIVER:
				अगर (!ctl++) drvname = "ioctl";
				अवरोध;
			पूर्ण

			अगर (drvname)
				seq_म_लिखो(m, "  Fusion MPT %s driver\n", drvname);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mpt_iocinfo_proc_show(काष्ठा seq_file *m, व्योम *v)
अणु
	MPT_ADAPTER	*ioc = m->निजी;
	अक्षर		 expVer[32];
	पूर्णांक		 sz;
	पूर्णांक		 p;

	mpt_get_fw_exp_ver(expVer, ioc);

	seq_म_लिखो(m, "%s:", ioc->name);
	अगर (ioc->facts.Flags & MPI_IOCFACTS_FLAGS_FW_DOWNLOAD_BOOT)
		seq_म_लिखो(m, "  (f/w download boot flag set)");
//	अगर (ioc->facts.IOCExceptions & MPI_IOCFACTS_EXCEPT_CONFIG_CHECKSUM_FAIL)
//		seq_म_लिखो(m, "  CONFIG_CHECKSUM_FAIL!");

	seq_म_लिखो(m, "\n  ProductID = 0x%04x (%s)\n",
			ioc->facts.ProductID,
			ioc->prod_name);
	seq_म_लिखो(m, "  FWVersion = 0x%08x%s", ioc->facts.FWVersion.Word, expVer);
	अगर (ioc->facts.FWImageSize)
		seq_म_लिखो(m, " (fw_size=%d)", ioc->facts.FWImageSize);
	seq_म_लिखो(m, "\n  MsgVersion = 0x%04x\n", ioc->facts.MsgVersion);
	seq_म_लिखो(m, "  FirstWhoInit = 0x%02x\n", ioc->FirstWhoInit);
	seq_म_लिखो(m, "  EventState = 0x%02x\n", ioc->facts.EventState);

	seq_म_लिखो(m, "  CurrentHostMfaHighAddr = 0x%08x\n",
			ioc->facts.CurrentHostMfaHighAddr);
	seq_म_लिखो(m, "  CurrentSenseBufferHighAddr = 0x%08x\n",
			ioc->facts.CurrentSenseBufferHighAddr);

	seq_म_लिखो(m, "  MaxChainDepth = 0x%02x frames\n", ioc->facts.MaxChainDepth);
	seq_म_लिखो(m, "  MinBlockSize = 0x%02x bytes\n", 4*ioc->facts.BlockSize);

	seq_म_लिखो(m, "  RequestFrames @ 0x%p (Dma @ 0x%p)\n",
					(व्योम *)ioc->req_frames, (व्योम *)(uदीर्घ)ioc->req_frames_dma);
	/*
	 *  Rounding UP to nearest 4-kB boundary here...
	 */
	sz = (ioc->req_sz * ioc->req_depth) + 128;
	sz = ((sz + 0x1000UL - 1UL) / 0x1000) * 0x1000;
	seq_म_लिखो(m, "    अणुCurReqSz=%dपूर्ण x अणुCurReqDepth=%dपूर्ण = %d bytes ^= 0x%x\न",
					ioc->req_sz, ioc->req_depth, ioc->req_sz*ioc->req_depth, sz);
	seq_म_लिखो(m, "    {MaxReqSz=%d}   {MaxReqDepth=%d}\n",
					4*ioc->facts.RequestFrameSize,
					ioc->facts.GlobalCredits);

	seq_म_लिखो(m, "  Frames   @ 0x%p (Dma @ 0x%p)\n",
					(व्योम *)ioc->alloc, (व्योम *)(uदीर्घ)ioc->alloc_dma);
	sz = (ioc->reply_sz * ioc->reply_depth) + 128;
	seq_म_लिखो(m, "    अणुCurRepSz=%dपूर्ण x अणुCurRepDepth=%dपूर्ण = %d bytes ^= 0x%x\न",
					ioc->reply_sz, ioc->reply_depth, ioc->reply_sz*ioc->reply_depth, sz);
	seq_म_लिखो(m, "    {MaxRepSz=%d}   {MaxRepDepth=%d}\n",
					ioc->facts.CurReplyFrameSize,
					ioc->facts.ReplyQueueDepth);

	seq_म_लिखो(m, "  MaxDevices = %d\n",
			(ioc->facts.MaxDevices==0) ? 255 : ioc->facts.MaxDevices);
	seq_म_लिखो(m, "  MaxBuses = %d\n", ioc->facts.MaxBuses);

	/* per-port info */
	क्रम (p=0; p < ioc->facts.NumberOfPorts; p++) अणु
		seq_म_लिखो(m, "  PortNumber = %d (of %d)\n",
				p+1,
				ioc->facts.NumberOfPorts);
		अगर (ioc->bus_type == FC) अणु
			अगर (ioc->pfacts[p].ProtocolFlags & MPI_PORTFACTS_PROTOCOL_LAN) अणु
				u8 *a = (u8*)&ioc->lan_cnfg_page1.HardwareAddressLow;
				seq_म_लिखो(m, "    LanAddr = %pMR\n", a);
			पूर्ण
			seq_म_लिखो(m, "    WWN = %08X%08X:%08X%08X\n",
					ioc->fc_port_page0[p].WWNN.High,
					ioc->fc_port_page0[p].WWNN.Low,
					ioc->fc_port_page0[p].WWPN.High,
					ioc->fc_port_page0[p].WWPN.Low);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण
#पूर्ण_अगर		/* CONFIG_PROC_FS पूर्ण */

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
अटल व्योम
mpt_get_fw_exp_ver(अक्षर *buf, MPT_ADAPTER *ioc)
अणु
	buf[0] ='\0';
	अगर ((ioc->facts.FWVersion.Word >> 24) == 0x0E) अणु
		प्र_लिखो(buf, " (Exp %02d%02d)",
			(ioc->facts.FWVersion.Word >> 16) & 0x00FF,	/* Month */
			(ioc->facts.FWVersion.Word >> 8) & 0x1F);	/* Day */

		/* insider hack! */
		अगर ((ioc->facts.FWVersion.Word >> 8) & 0x80)
			म_जोड़ो(buf, " [MDBG]");
	पूर्ण
पूर्ण

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/**
 *	mpt_prपूर्णांक_ioc_summary - Write ASCII summary of IOC to a buffer.
 *	@ioc: Poपूर्णांकer to MPT_ADAPTER काष्ठाure
 *	@buffer: Poपूर्णांकer to buffer where IOC summary info should be written
 *	@size: Poपूर्णांकer to number of bytes we wrote (set by this routine)
 *	@len: Offset at which to start writing in buffer
 *	@showlan: Display LAN stuff?
 *
 *	This routine ग_लिखोs (english पढ़ोable) ASCII text, which represents
 *	a summary of IOC inक्रमmation, to a buffer.
 */
व्योम
mpt_prपूर्णांक_ioc_summary(MPT_ADAPTER *ioc, अक्षर *buffer, पूर्णांक *size, पूर्णांक len, पूर्णांक showlan)
अणु
	अक्षर expVer[32];
	पूर्णांक y;

	mpt_get_fw_exp_ver(expVer, ioc);

	/*
	 *  Shorter summary of attached ioc's...
	 */
	y = प्र_लिखो(buffer+len, "%s: %s, %s%08xh%s, Ports=%d, MaxQ=%d",
			ioc->name,
			ioc->prod_name,
			MPT_FW_REV_MAGIC_ID_STRING,	/* "FwRev=" or somesuch */
			ioc->facts.FWVersion.Word,
			expVer,
			ioc->facts.NumberOfPorts,
			ioc->req_depth);

	अगर (showlan && (ioc->pfacts[0].ProtocolFlags & MPI_PORTFACTS_PROTOCOL_LAN)) अणु
		u8 *a = (u8*)&ioc->lan_cnfg_page1.HardwareAddressLow;
		y += प्र_लिखो(buffer+len+y, ", LanAddr=%pMR", a);
	पूर्ण

	y += प्र_लिखो(buffer+len+y, ", IRQ=%d", ioc->pci_irq);

	अगर (!ioc->active)
		y += प्र_लिखो(buffer+len+y, " (disabled)");

	y += प्र_लिखो(buffer+len+y, "\n");

	*size = y;
पूर्ण

#अगर_घोषित CONFIG_PROC_FS
अटल व्योम seq_mpt_prपूर्णांक_ioc_summary(MPT_ADAPTER *ioc, काष्ठा seq_file *m, पूर्णांक showlan)
अणु
	अक्षर expVer[32];

	mpt_get_fw_exp_ver(expVer, ioc);

	/*
	 *  Shorter summary of attached ioc's...
	 */
	seq_म_लिखो(m, "%s: %s, %s%08xh%s, Ports=%d, MaxQ=%d",
			ioc->name,
			ioc->prod_name,
			MPT_FW_REV_MAGIC_ID_STRING,	/* "FwRev=" or somesuch */
			ioc->facts.FWVersion.Word,
			expVer,
			ioc->facts.NumberOfPorts,
			ioc->req_depth);

	अगर (showlan && (ioc->pfacts[0].ProtocolFlags & MPI_PORTFACTS_PROTOCOL_LAN)) अणु
		u8 *a = (u8*)&ioc->lan_cnfg_page1.HardwareAddressLow;
		seq_म_लिखो(m, ", LanAddr=%pMR", a);
	पूर्ण

	seq_म_लिखो(m, ", IRQ=%d", ioc->pci_irq);

	अगर (!ioc->active)
		seq_म_लिखो(m, " (disabled)");

	seq_अ_दो(m, '\n');
पूर्ण
#पूर्ण_अगर

/**
 *	mpt_set_taskmgmt_in_progress_flag - set flags associated with task management
 *	@ioc: Poपूर्णांकer to MPT_ADAPTER काष्ठाure
 *
 *	Returns 0 क्रम SUCCESS or -1 अगर FAILED.
 *
 *	If -1 is वापस, then it was not possible to set the flags
 **/
पूर्णांक
mpt_set_taskmgmt_in_progress_flag(MPT_ADAPTER *ioc)
अणु
	अचिन्हित दीर्घ	 flags;
	पूर्णांक		 retval;

	spin_lock_irqsave(&ioc->taskmgmt_lock, flags);
	अगर (ioc->ioc_reset_in_progress || ioc->taskmgmt_in_progress ||
	    (ioc->alt_ioc && ioc->alt_ioc->taskmgmt_in_progress)) अणु
		retval = -1;
		जाओ out;
	पूर्ण
	retval = 0;
	ioc->taskmgmt_in_progress = 1;
	ioc->taskmgmt_quiesce_io = 1;
	अगर (ioc->alt_ioc) अणु
		ioc->alt_ioc->taskmgmt_in_progress = 1;
		ioc->alt_ioc->taskmgmt_quiesce_io = 1;
	पूर्ण
 out:
	spin_unlock_irqrestore(&ioc->taskmgmt_lock, flags);
	वापस retval;
पूर्ण
EXPORT_SYMBOL(mpt_set_taskmgmt_in_progress_flag);

/**
 *	mpt_clear_taskmgmt_in_progress_flag - clear flags associated with task management
 *	@ioc: Poपूर्णांकer to MPT_ADAPTER काष्ठाure
 *
 **/
व्योम
mpt_clear_taskmgmt_in_progress_flag(MPT_ADAPTER *ioc)
अणु
	अचिन्हित दीर्घ	 flags;

	spin_lock_irqsave(&ioc->taskmgmt_lock, flags);
	ioc->taskmgmt_in_progress = 0;
	ioc->taskmgmt_quiesce_io = 0;
	अगर (ioc->alt_ioc) अणु
		ioc->alt_ioc->taskmgmt_in_progress = 0;
		ioc->alt_ioc->taskmgmt_quiesce_io = 0;
	पूर्ण
	spin_unlock_irqrestore(&ioc->taskmgmt_lock, flags);
पूर्ण
EXPORT_SYMBOL(mpt_clear_taskmgmt_in_progress_flag);


/**
 *	mpt_halt_firmware - Halts the firmware अगर it is operational and panic
 *	the kernel
 *	@ioc: Poपूर्णांकer to MPT_ADAPTER काष्ठाure
 *
 **/
व्योम
mpt_halt_firmware(MPT_ADAPTER *ioc)
अणु
	u32	 ioc_raw_state;

	ioc_raw_state = mpt_GetIocState(ioc, 0);

	अगर ((ioc_raw_state & MPI_IOC_STATE_MASK) == MPI_IOC_STATE_FAULT) अणु
		prपूर्णांकk(MYIOC_s_ERR_FMT "IOC is in FAULT state (%04xh)!!!\n",
			ioc->name, ioc_raw_state & MPI_DOORBELL_DATA_MASK);
		panic("%s: IOC Fault (%04xh)!!!\n", ioc->name,
			ioc_raw_state & MPI_DOORBELL_DATA_MASK);
	पूर्ण अन्यथा अणु
		CHIPREG_WRITE32(&ioc->chip->Doorbell, 0xC0FFEE00);
		panic("%s: Firmware is halted due to command timeout\n",
			ioc->name);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(mpt_halt_firmware);

/**
 *	mpt_SoftResetHandler - Issues a less expensive reset
 *	@ioc: Poपूर्णांकer to MPT_ADAPTER काष्ठाure
 *	@sleepFlag: Indicates अगर sleep or schedule must be called.
 *
 *	Returns 0 क्रम SUCCESS or -1 अगर FAILED.
 *
 *	Message Unit Reset - inकाष्ठाs the IOC to reset the Reply Post and
 *	Free FIFO's. All the Message Frames on Reply Free FIFO are discarded.
 *	All posted buffers are मुक्तd, and event notअगरication is turned off.
 *	IOC करोesn't reply to any outstanding request. This will transfer IOC
 *	to READY state.
 **/
अटल पूर्णांक
mpt_SoftResetHandler(MPT_ADAPTER *ioc, पूर्णांक sleepFlag)
अणु
	पूर्णांक		 rc;
	पूर्णांक		 ii;
	u8		 cb_idx;
	अचिन्हित दीर्घ	 flags;
	u32		 ioc_state;
	अचिन्हित दीर्घ	 समय_count;

	dपंचांगprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT "SoftResetHandler Entered!\n",
		ioc->name));

	ioc_state = mpt_GetIocState(ioc, 0) & MPI_IOC_STATE_MASK;

	अगर (mpt_fwfault_debug)
		mpt_halt_firmware(ioc);

	अगर (ioc_state == MPI_IOC_STATE_FAULT ||
	    ioc_state == MPI_IOC_STATE_RESET) अणु
		dपंचांगprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT
		    "skipping, either in FAULT or RESET state!\n", ioc->name));
		वापस -1;
	पूर्ण

	अगर (ioc->bus_type == FC) अणु
		dपंचांगprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT
		    "skipping, because the bus type is FC!\n", ioc->name));
		वापस -1;
	पूर्ण

	spin_lock_irqsave(&ioc->taskmgmt_lock, flags);
	अगर (ioc->ioc_reset_in_progress) अणु
		spin_unlock_irqrestore(&ioc->taskmgmt_lock, flags);
		वापस -1;
	पूर्ण
	ioc->ioc_reset_in_progress = 1;
	spin_unlock_irqrestore(&ioc->taskmgmt_lock, flags);

	rc = -1;

	क्रम (cb_idx = MPT_MAX_PROTOCOL_DRIVERS-1; cb_idx; cb_idx--) अणु
		अगर (MptResetHandlers[cb_idx])
			mpt_संकेत_reset(cb_idx, ioc, MPT_IOC_SETUP_RESET);
	पूर्ण

	spin_lock_irqsave(&ioc->taskmgmt_lock, flags);
	अगर (ioc->taskmgmt_in_progress) अणु
		ioc->ioc_reset_in_progress = 0;
		spin_unlock_irqrestore(&ioc->taskmgmt_lock, flags);
		वापस -1;
	पूर्ण
	spin_unlock_irqrestore(&ioc->taskmgmt_lock, flags);
	/* Disable reply पूर्णांकerrupts (also blocks FreeQ) */
	CHIPREG_WRITE32(&ioc->chip->IntMask, 0xFFFFFFFF);
	ioc->active = 0;
	समय_count = jअगरfies;

	rc = SendIocReset(ioc, MPI_FUNCTION_IOC_MESSAGE_UNIT_RESET, sleepFlag);

	क्रम (cb_idx = MPT_MAX_PROTOCOL_DRIVERS-1; cb_idx; cb_idx--) अणु
		अगर (MptResetHandlers[cb_idx])
			mpt_संकेत_reset(cb_idx, ioc, MPT_IOC_PRE_RESET);
	पूर्ण

	अगर (rc)
		जाओ out;

	ioc_state = mpt_GetIocState(ioc, 0) & MPI_IOC_STATE_MASK;
	अगर (ioc_state != MPI_IOC_STATE_READY)
		जाओ out;

	क्रम (ii = 0; ii < 5; ii++) अणु
		/* Get IOC facts! Allow 5 retries */
		rc = GetIocFacts(ioc, sleepFlag,
			MPT_HOSTEVENT_IOC_RECOVER);
		अगर (rc == 0)
			अवरोध;
		अगर (sleepFlag == CAN_SLEEP)
			msleep(100);
		अन्यथा
			mdelay(100);
	पूर्ण
	अगर (ii == 5)
		जाओ out;

	rc = PrimeIocFअगरos(ioc);
	अगर (rc != 0)
		जाओ out;

	rc = SendIocInit(ioc, sleepFlag);
	अगर (rc != 0)
		जाओ out;

	rc = SendEventNotअगरication(ioc, 1, sleepFlag);
	अगर (rc != 0)
		जाओ out;

	अगर (ioc->hard_resets < -1)
		ioc->hard_resets++;

	/*
	 * At this poपूर्णांक, we know soft reset succeeded.
	 */

	ioc->active = 1;
	CHIPREG_WRITE32(&ioc->chip->IntMask, MPI_HIM_DIM);

 out:
	spin_lock_irqsave(&ioc->taskmgmt_lock, flags);
	ioc->ioc_reset_in_progress = 0;
	ioc->taskmgmt_quiesce_io = 0;
	ioc->taskmgmt_in_progress = 0;
	spin_unlock_irqrestore(&ioc->taskmgmt_lock, flags);

	अगर (ioc->active) अणु	/* otherwise, hard reset coming */
		क्रम (cb_idx = MPT_MAX_PROTOCOL_DRIVERS-1; cb_idx; cb_idx--) अणु
			अगर (MptResetHandlers[cb_idx])
				mpt_संकेत_reset(cb_idx, ioc,
					MPT_IOC_POST_RESET);
		पूर्ण
	पूर्ण

	dपंचांगprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT
		"SoftResetHandler: completed (%d seconds): %s\n",
		ioc->name, jअगरfies_to_msecs(jअगरfies - समय_count)/1000,
		((rc == 0) ? "SUCCESS" : "FAILED")));

	वापस rc;
पूर्ण

/**
 *	mpt_Soft_Hard_ResetHandler - Try less expensive reset
 *	@ioc: Poपूर्णांकer to MPT_ADAPTER काष्ठाure
 *	@sleepFlag: Indicates अगर sleep or schedule must be called.
 *
 *	Returns 0 क्रम SUCCESS or -1 अगर FAILED.
 *	Try क्रम softreset first, only अगर it fails go क्रम expensive
 *	HardReset.
 **/
पूर्णांक
mpt_Soft_Hard_ResetHandler(MPT_ADAPTER *ioc, पूर्णांक sleepFlag) अणु
	पूर्णांक ret = -1;

	ret = mpt_SoftResetHandler(ioc, sleepFlag);
	अगर (ret == 0)
		वापस ret;
	ret = mpt_HardResetHandler(ioc, sleepFlag);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(mpt_Soft_Hard_ResetHandler);

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/*
 *	Reset Handling
 */
/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/**
 *	mpt_HardResetHandler - Generic reset handler
 *	@ioc: Poपूर्णांकer to MPT_ADAPTER काष्ठाure
 *	@sleepFlag: Indicates अगर sleep or schedule must be called.
 *
 *	Issues SCSI Task Management call based on input arg values.
 *	If TaskMgmt fails, वापसs associated SCSI request.
 *
 *	Remark: _HardResetHandler can be invoked from an पूर्णांकerrupt thपढ़ो (समयr)
 *	or a non-पूर्णांकerrupt thपढ़ो.  In the क्रमmer, must not call schedule().
 *
 *	Note: A वापस of -1 is a FATAL error हाल, as it means a
 *	FW reload/initialization failed.
 *
 *	Returns 0 क्रम SUCCESS or -1 अगर FAILED.
 */
पूर्णांक
mpt_HardResetHandler(MPT_ADAPTER *ioc, पूर्णांक sleepFlag)
अणु
	पूर्णांक	 rc;
	u8	 cb_idx;
	अचिन्हित दीर्घ	 flags;
	अचिन्हित दीर्घ	 समय_count;

	dपंचांगprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT "HardResetHandler Entered!\n", ioc->name));
#अगर_घोषित MFCNT
	prपूर्णांकk(MYIOC_s_INFO_FMT "HardResetHandler Entered!\n", ioc->name);
	prपूर्णांकk("MF count 0x%x !\n", ioc->mfcnt);
#पूर्ण_अगर
	अगर (mpt_fwfault_debug)
		mpt_halt_firmware(ioc);

	/* Reset the adapter. Prevent more than 1 call to
	 * mpt_करो_ioc_recovery at any instant in समय.
	 */
	spin_lock_irqsave(&ioc->taskmgmt_lock, flags);
	अगर (ioc->ioc_reset_in_progress) अणु
		spin_unlock_irqrestore(&ioc->taskmgmt_lock, flags);
		ioc->रुको_on_reset_completion = 1;
		करो अणु
			ssleep(1);
		पूर्ण जबतक (ioc->ioc_reset_in_progress == 1);
		ioc->रुको_on_reset_completion = 0;
		वापस ioc->reset_status;
	पूर्ण
	अगर (ioc->रुको_on_reset_completion) अणु
		spin_unlock_irqrestore(&ioc->taskmgmt_lock, flags);
		rc = 0;
		समय_count = jअगरfies;
		जाओ निकास;
	पूर्ण
	ioc->ioc_reset_in_progress = 1;
	अगर (ioc->alt_ioc)
		ioc->alt_ioc->ioc_reset_in_progress = 1;
	spin_unlock_irqrestore(&ioc->taskmgmt_lock, flags);


	/* The SCSI driver needs to adjust समयouts on all current
	 * commands prior to the diagnostic reset being issued.
	 * Prevents समयouts occurring during a diagnostic reset...very bad.
	 * For all other protocol drivers, this is a no-op.
	 */
	क्रम (cb_idx = MPT_MAX_PROTOCOL_DRIVERS-1; cb_idx; cb_idx--) अणु
		अगर (MptResetHandlers[cb_idx]) अणु
			mpt_संकेत_reset(cb_idx, ioc, MPT_IOC_SETUP_RESET);
			अगर (ioc->alt_ioc)
				mpt_संकेत_reset(cb_idx, ioc->alt_ioc,
					MPT_IOC_SETUP_RESET);
		पूर्ण
	पूर्ण

	समय_count = jअगरfies;
	rc = mpt_करो_ioc_recovery(ioc, MPT_HOSTEVENT_IOC_RECOVER, sleepFlag);
	अगर (rc != 0) अणु
		prपूर्णांकk(KERN_WARNING MYNAM
		       ": WARNING - (%d) Cannot recover %s, doorbell=0x%08x\n",
		       rc, ioc->name, mpt_GetIocState(ioc, 0));
	पूर्ण अन्यथा अणु
		अगर (ioc->hard_resets < -1)
			ioc->hard_resets++;
	पूर्ण

	spin_lock_irqsave(&ioc->taskmgmt_lock, flags);
	ioc->ioc_reset_in_progress = 0;
	ioc->taskmgmt_quiesce_io = 0;
	ioc->taskmgmt_in_progress = 0;
	ioc->reset_status = rc;
	अगर (ioc->alt_ioc) अणु
		ioc->alt_ioc->ioc_reset_in_progress = 0;
		ioc->alt_ioc->taskmgmt_quiesce_io = 0;
		ioc->alt_ioc->taskmgmt_in_progress = 0;
	पूर्ण
	spin_unlock_irqrestore(&ioc->taskmgmt_lock, flags);

	क्रम (cb_idx = MPT_MAX_PROTOCOL_DRIVERS-1; cb_idx; cb_idx--) अणु
		अगर (MptResetHandlers[cb_idx]) अणु
			mpt_संकेत_reset(cb_idx, ioc, MPT_IOC_POST_RESET);
			अगर (ioc->alt_ioc)
				mpt_संकेत_reset(cb_idx,
					ioc->alt_ioc, MPT_IOC_POST_RESET);
		पूर्ण
	पूर्ण
निकास:
	dपंचांगprपूर्णांकk(ioc,
	    prपूर्णांकk(MYIOC_s_DEBUG_FMT
		"HardResetHandler: completed (%d seconds): %s\n", ioc->name,
		jअगरfies_to_msecs(jअगरfies - समय_count)/1000, ((rc == 0) ?
		"SUCCESS" : "FAILED")));

	वापस rc;
पूर्ण

#अगर_घोषित CONFIG_FUSION_LOGGING
अटल व्योम
mpt_display_event_info(MPT_ADAPTER *ioc, EventNotअगरicationReply_t *pEventReply)
अणु
	अक्षर *ds = शून्य;
	u32 evData0;
	पूर्णांक ii;
	u8 event;
	अक्षर *evStr = ioc->evStr;

	event = le32_to_cpu(pEventReply->Event) & 0xFF;
	evData0 = le32_to_cpu(pEventReply->Data[0]);

	चयन(event) अणु
	हाल MPI_EVENT_NONE:
		ds = "None";
		अवरोध;
	हाल MPI_EVENT_LOG_DATA:
		ds = "Log Data";
		अवरोध;
	हाल MPI_EVENT_STATE_CHANGE:
		ds = "State Change";
		अवरोध;
	हाल MPI_EVENT_UNIT_ATTENTION:
		ds = "Unit Attention";
		अवरोध;
	हाल MPI_EVENT_IOC_BUS_RESET:
		ds = "IOC Bus Reset";
		अवरोध;
	हाल MPI_EVENT_EXT_BUS_RESET:
		ds = "External Bus Reset";
		अवरोध;
	हाल MPI_EVENT_RESCAN:
		ds = "Bus Rescan Event";
		अवरोध;
	हाल MPI_EVENT_LINK_STATUS_CHANGE:
		अगर (evData0 == MPI_EVENT_LINK_STATUS_FAILURE)
			ds = "Link Status(FAILURE) Change";
		अन्यथा
			ds = "Link Status(ACTIVE) Change";
		अवरोध;
	हाल MPI_EVENT_LOOP_STATE_CHANGE:
		अगर (evData0 == MPI_EVENT_LOOP_STATE_CHANGE_LIP)
			ds = "Loop State(LIP) Change";
		अन्यथा अगर (evData0 == MPI_EVENT_LOOP_STATE_CHANGE_LPE)
			ds = "Loop State(LPE) Change";
		अन्यथा
			ds = "Loop State(LPB) Change";
		अवरोध;
	हाल MPI_EVENT_LOGOUT:
		ds = "Logout";
		अवरोध;
	हाल MPI_EVENT_EVENT_CHANGE:
		अगर (evData0)
			ds = "Events ON";
		अन्यथा
			ds = "Events OFF";
		अवरोध;
	हाल MPI_EVENT_INTEGRATED_RAID:
	अणु
		u8 ReasonCode = (u8)(evData0 >> 16);
		चयन (ReasonCode) अणु
		हाल MPI_EVENT_RAID_RC_VOLUME_CREATED :
			ds = "Integrated Raid: Volume Created";
			अवरोध;
		हाल MPI_EVENT_RAID_RC_VOLUME_DELETED :
			ds = "Integrated Raid: Volume Deleted";
			अवरोध;
		हाल MPI_EVENT_RAID_RC_VOLUME_SETTINGS_CHANGED :
			ds = "Integrated Raid: Volume Settings Changed";
			अवरोध;
		हाल MPI_EVENT_RAID_RC_VOLUME_STATUS_CHANGED :
			ds = "Integrated Raid: Volume Status Changed";
			अवरोध;
		हाल MPI_EVENT_RAID_RC_VOLUME_PHYSDISK_CHANGED :
			ds = "Integrated Raid: Volume Physdisk Changed";
			अवरोध;
		हाल MPI_EVENT_RAID_RC_PHYSDISK_CREATED :
			ds = "Integrated Raid: Physdisk Created";
			अवरोध;
		हाल MPI_EVENT_RAID_RC_PHYSDISK_DELETED :
			ds = "Integrated Raid: Physdisk Deleted";
			अवरोध;
		हाल MPI_EVENT_RAID_RC_PHYSDISK_SETTINGS_CHANGED :
			ds = "Integrated Raid: Physdisk Settings Changed";
			अवरोध;
		हाल MPI_EVENT_RAID_RC_PHYSDISK_STATUS_CHANGED :
			ds = "Integrated Raid: Physdisk Status Changed";
			अवरोध;
		हाल MPI_EVENT_RAID_RC_DOMAIN_VAL_NEEDED :
			ds = "Integrated Raid: Domain Validation Needed";
			अवरोध;
		हाल MPI_EVENT_RAID_RC_SMART_DATA :
			ds = "Integrated Raid; Smart Data";
			अवरोध;
		हाल MPI_EVENT_RAID_RC_REPLACE_ACTION_STARTED :
			ds = "Integrated Raid: Replace Action Started";
			अवरोध;
		शेष:
			ds = "Integrated Raid";
		अवरोध;
		पूर्ण
		अवरोध;
	पूर्ण
	हाल MPI_EVENT_SCSI_DEVICE_STATUS_CHANGE:
		ds = "SCSI Device Status Change";
		अवरोध;
	हाल MPI_EVENT_SAS_DEVICE_STATUS_CHANGE:
	अणु
		u8 id = (u8)(evData0);
		u8 channel = (u8)(evData0 >> 8);
		u8 ReasonCode = (u8)(evData0 >> 16);
		चयन (ReasonCode) अणु
		हाल MPI_EVENT_SAS_DEV_STAT_RC_ADDED:
			snम_लिखो(evStr, EVENT_DESCR_STR_SZ,
			    "SAS Device Status Change: Added: "
			    "id=%d channel=%d", id, channel);
			अवरोध;
		हाल MPI_EVENT_SAS_DEV_STAT_RC_NOT_RESPONDING:
			snम_लिखो(evStr, EVENT_DESCR_STR_SZ,
			    "SAS Device Status Change: Deleted: "
			    "id=%d channel=%d", id, channel);
			अवरोध;
		हाल MPI_EVENT_SAS_DEV_STAT_RC_SMART_DATA:
			snम_लिखो(evStr, EVENT_DESCR_STR_SZ,
			    "SAS Device Status Change: SMART Data: "
			    "id=%d channel=%d", id, channel);
			अवरोध;
		हाल MPI_EVENT_SAS_DEV_STAT_RC_NO_PERSIST_ADDED:
			snम_लिखो(evStr, EVENT_DESCR_STR_SZ,
			    "SAS Device Status Change: No Persistency: "
			    "id=%d channel=%d", id, channel);
			अवरोध;
		हाल MPI_EVENT_SAS_DEV_STAT_RC_UNSUPPORTED:
			snम_लिखो(evStr, EVENT_DESCR_STR_SZ,
			    "SAS Device Status Change: Unsupported Device "
			    "Discovered : id=%d channel=%d", id, channel);
			अवरोध;
		हाल MPI_EVENT_SAS_DEV_STAT_RC_INTERNAL_DEVICE_RESET:
			snम_लिखो(evStr, EVENT_DESCR_STR_SZ,
			    "SAS Device Status Change: Internal Device "
			    "Reset : id=%d channel=%d", id, channel);
			अवरोध;
		हाल MPI_EVENT_SAS_DEV_STAT_RC_TASK_ABORT_INTERNAL:
			snम_लिखो(evStr, EVENT_DESCR_STR_SZ,
			    "SAS Device Status Change: Internal Task "
			    "Abort : id=%d channel=%d", id, channel);
			अवरोध;
		हाल MPI_EVENT_SAS_DEV_STAT_RC_ABORT_TASK_SET_INTERNAL:
			snम_लिखो(evStr, EVENT_DESCR_STR_SZ,
			    "SAS Device Status Change: Internal Abort "
			    "Task Set : id=%d channel=%d", id, channel);
			अवरोध;
		हाल MPI_EVENT_SAS_DEV_STAT_RC_CLEAR_TASK_SET_INTERNAL:
			snम_लिखो(evStr, EVENT_DESCR_STR_SZ,
			    "SAS Device Status Change: Internal Clear "
			    "Task Set : id=%d channel=%d", id, channel);
			अवरोध;
		हाल MPI_EVENT_SAS_DEV_STAT_RC_QUERY_TASK_INTERNAL:
			snम_लिखो(evStr, EVENT_DESCR_STR_SZ,
			    "SAS Device Status Change: Internal Query "
			    "Task : id=%d channel=%d", id, channel);
			अवरोध;
		शेष:
			snम_लिखो(evStr, EVENT_DESCR_STR_SZ,
			    "SAS Device Status Change: Unknown: "
			    "id=%d channel=%d", id, channel);
			अवरोध;
		पूर्ण
		अवरोध;
	पूर्ण
	हाल MPI_EVENT_ON_BUS_TIMER_EXPIRED:
		ds = "Bus Timer Expired";
		अवरोध;
	हाल MPI_EVENT_QUEUE_FULL:
	अणु
		u16 curr_depth = (u16)(evData0 >> 16);
		u8 channel = (u8)(evData0 >> 8);
		u8 id = (u8)(evData0);

		snम_लिखो(evStr, EVENT_DESCR_STR_SZ,
		   "Queue Full: channel=%d id=%d depth=%d",
		   channel, id, curr_depth);
		अवरोध;
	पूर्ण
	हाल MPI_EVENT_SAS_SES:
		ds = "SAS SES Event";
		अवरोध;
	हाल MPI_EVENT_PERSISTENT_TABLE_FULL:
		ds = "Persistent Table Full";
		अवरोध;
	हाल MPI_EVENT_SAS_PHY_LINK_STATUS:
	अणु
		u8 LinkRates = (u8)(evData0 >> 8);
		u8 PhyNumber = (u8)(evData0);
		LinkRates = (LinkRates & MPI_EVENT_SAS_PLS_LR_CURRENT_MASK) >>
			MPI_EVENT_SAS_PLS_LR_CURRENT_SHIFT;
		चयन (LinkRates) अणु
		हाल MPI_EVENT_SAS_PLS_LR_RATE_UNKNOWN:
			snम_लिखो(evStr, EVENT_DESCR_STR_SZ,
			   "SAS PHY Link Status: Phy=%d:"
			   " Rate Unknown",PhyNumber);
			अवरोध;
		हाल MPI_EVENT_SAS_PLS_LR_RATE_PHY_DISABLED:
			snम_लिखो(evStr, EVENT_DESCR_STR_SZ,
			   "SAS PHY Link Status: Phy=%d:"
			   " Phy Disabled",PhyNumber);
			अवरोध;
		हाल MPI_EVENT_SAS_PLS_LR_RATE_FAILED_SPEED_NEGOTIATION:
			snम_लिखो(evStr, EVENT_DESCR_STR_SZ,
			   "SAS PHY Link Status: Phy=%d:"
			   " Failed Speed Nego",PhyNumber);
			अवरोध;
		हाल MPI_EVENT_SAS_PLS_LR_RATE_SATA_OOB_COMPLETE:
			snम_लिखो(evStr, EVENT_DESCR_STR_SZ,
			   "SAS PHY Link Status: Phy=%d:"
			   " Sata OOB Completed",PhyNumber);
			अवरोध;
		हाल MPI_EVENT_SAS_PLS_LR_RATE_1_5:
			snम_लिखो(evStr, EVENT_DESCR_STR_SZ,
			   "SAS PHY Link Status: Phy=%d:"
			   " Rate 1.5 Gbps",PhyNumber);
			अवरोध;
		हाल MPI_EVENT_SAS_PLS_LR_RATE_3_0:
			snम_लिखो(evStr, EVENT_DESCR_STR_SZ,
			   "SAS PHY Link Status: Phy=%d:"
			   " Rate 3.0 Gbps", PhyNumber);
			अवरोध;
		हाल MPI_EVENT_SAS_PLS_LR_RATE_6_0:
			snम_लिखो(evStr, EVENT_DESCR_STR_SZ,
			   "SAS PHY Link Status: Phy=%d:"
			   " Rate 6.0 Gbps", PhyNumber);
			अवरोध;
		शेष:
			snम_लिखो(evStr, EVENT_DESCR_STR_SZ,
			   "SAS PHY Link Status: Phy=%d", PhyNumber);
			अवरोध;
		पूर्ण
		अवरोध;
	पूर्ण
	हाल MPI_EVENT_SAS_DISCOVERY_ERROR:
		ds = "SAS Discovery Error";
		अवरोध;
	हाल MPI_EVENT_IR_RESYNC_UPDATE:
	अणु
		u8 resync_complete = (u8)(evData0 >> 16);
		snम_लिखो(evStr, EVENT_DESCR_STR_SZ,
		    "IR Resync Update: Complete = %d:",resync_complete);
		अवरोध;
	पूर्ण
	हाल MPI_EVENT_IR2:
	अणु
		u8 id = (u8)(evData0);
		u8 channel = (u8)(evData0 >> 8);
		u8 phys_num = (u8)(evData0 >> 24);
		u8 ReasonCode = (u8)(evData0 >> 16);

		चयन (ReasonCode) अणु
		हाल MPI_EVENT_IR2_RC_LD_STATE_CHANGED:
			snम_लिखो(evStr, EVENT_DESCR_STR_SZ,
			    "IR2: LD State Changed: "
			    "id=%d channel=%d phys_num=%d",
			    id, channel, phys_num);
			अवरोध;
		हाल MPI_EVENT_IR2_RC_PD_STATE_CHANGED:
			snम_लिखो(evStr, EVENT_DESCR_STR_SZ,
			    "IR2: PD State Changed "
			    "id=%d channel=%d phys_num=%d",
			    id, channel, phys_num);
			अवरोध;
		हाल MPI_EVENT_IR2_RC_BAD_BLOCK_TABLE_FULL:
			snम_लिखो(evStr, EVENT_DESCR_STR_SZ,
			    "IR2: Bad Block Table Full: "
			    "id=%d channel=%d phys_num=%d",
			    id, channel, phys_num);
			अवरोध;
		हाल MPI_EVENT_IR2_RC_PD_INSERTED:
			snम_लिखो(evStr, EVENT_DESCR_STR_SZ,
			    "IR2: PD Inserted: "
			    "id=%d channel=%d phys_num=%d",
			    id, channel, phys_num);
			अवरोध;
		हाल MPI_EVENT_IR2_RC_PD_REMOVED:
			snम_लिखो(evStr, EVENT_DESCR_STR_SZ,
			    "IR2: PD Removed: "
			    "id=%d channel=%d phys_num=%d",
			    id, channel, phys_num);
			अवरोध;
		हाल MPI_EVENT_IR2_RC_FOREIGN_CFG_DETECTED:
			snम_लिखो(evStr, EVENT_DESCR_STR_SZ,
			    "IR2: Foreign CFG Detected: "
			    "id=%d channel=%d phys_num=%d",
			    id, channel, phys_num);
			अवरोध;
		हाल MPI_EVENT_IR2_RC_REBUILD_MEDIUM_ERROR:
			snम_लिखो(evStr, EVENT_DESCR_STR_SZ,
			    "IR2: Rebuild Medium Error: "
			    "id=%d channel=%d phys_num=%d",
			    id, channel, phys_num);
			अवरोध;
		हाल MPI_EVENT_IR2_RC_DUAL_PORT_ADDED:
			snम_लिखो(evStr, EVENT_DESCR_STR_SZ,
			    "IR2: Dual Port Added: "
			    "id=%d channel=%d phys_num=%d",
			    id, channel, phys_num);
			अवरोध;
		हाल MPI_EVENT_IR2_RC_DUAL_PORT_REMOVED:
			snम_लिखो(evStr, EVENT_DESCR_STR_SZ,
			    "IR2: Dual Port Removed: "
			    "id=%d channel=%d phys_num=%d",
			    id, channel, phys_num);
			अवरोध;
		शेष:
			ds = "IR2";
		अवरोध;
		पूर्ण
		अवरोध;
	पूर्ण
	हाल MPI_EVENT_SAS_DISCOVERY:
	अणु
		अगर (evData0)
			ds = "SAS Discovery: Start";
		अन्यथा
			ds = "SAS Discovery: Stop";
		अवरोध;
	पूर्ण
	हाल MPI_EVENT_LOG_ENTRY_ADDED:
		ds = "SAS Log Entry Added";
		अवरोध;

	हाल MPI_EVENT_SAS_BROADCAST_PRIMITIVE:
	अणु
		u8 phy_num = (u8)(evData0);
		u8 port_num = (u8)(evData0 >> 8);
		u8 port_width = (u8)(evData0 >> 16);
		u8 primitive = (u8)(evData0 >> 24);
		snम_लिखो(evStr, EVENT_DESCR_STR_SZ,
		    "SAS Broadcast Primitive: phy=%d port=%d "
		    "width=%d primitive=0x%02x",
		    phy_num, port_num, port_width, primitive);
		अवरोध;
	पूर्ण

	हाल MPI_EVENT_SAS_INIT_DEVICE_STATUS_CHANGE:
	अणु
		u8 reason = (u8)(evData0);

		चयन (reason) अणु
		हाल MPI_EVENT_SAS_INIT_RC_ADDED:
			ds = "SAS Initiator Status Change: Added";
			अवरोध;
		हाल MPI_EVENT_SAS_INIT_RC_REMOVED:
			ds = "SAS Initiator Status Change: Deleted";
			अवरोध;
		शेष:
			ds = "SAS Initiator Status Change";
			अवरोध;
		पूर्ण
		अवरोध;
	पूर्ण

	हाल MPI_EVENT_SAS_INIT_TABLE_OVERFLOW:
	अणु
		u8 max_init = (u8)(evData0);
		u8 current_init = (u8)(evData0 >> 8);

		snम_लिखो(evStr, EVENT_DESCR_STR_SZ,
		    "SAS Initiator Device Table Overflow: max initiators=%02d "
		    "current initiators=%02d",
		    max_init, current_init);
		अवरोध;
	पूर्ण
	हाल MPI_EVENT_SAS_SMP_ERROR:
	अणु
		u8 status = (u8)(evData0);
		u8 port_num = (u8)(evData0 >> 8);
		u8 result = (u8)(evData0 >> 16);

		अगर (status == MPI_EVENT_SAS_SMP_FUNCTION_RESULT_VALID)
			snम_लिखो(evStr, EVENT_DESCR_STR_SZ,
			    "SAS SMP Error: port=%d result=0x%02x",
			    port_num, result);
		अन्यथा अगर (status == MPI_EVENT_SAS_SMP_CRC_ERROR)
			snम_लिखो(evStr, EVENT_DESCR_STR_SZ,
			    "SAS SMP Error: port=%d : CRC Error",
			    port_num);
		अन्यथा अगर (status == MPI_EVENT_SAS_SMP_TIMEOUT)
			snम_लिखो(evStr, EVENT_DESCR_STR_SZ,
			    "SAS SMP Error: port=%d : Timeout",
			    port_num);
		अन्यथा अगर (status == MPI_EVENT_SAS_SMP_NO_DESTINATION)
			snम_लिखो(evStr, EVENT_DESCR_STR_SZ,
			    "SAS SMP Error: port=%d : No Destination",
			    port_num);
		अन्यथा अगर (status == MPI_EVENT_SAS_SMP_BAD_DESTINATION)
			snम_लिखो(evStr, EVENT_DESCR_STR_SZ,
			    "SAS SMP Error: port=%d : Bad Destination",
			    port_num);
		अन्यथा
			snम_लिखो(evStr, EVENT_DESCR_STR_SZ,
			    "SAS SMP Error: port=%d : status=0x%02x",
			    port_num, status);
		अवरोध;
	पूर्ण

	हाल MPI_EVENT_SAS_EXPANDER_STATUS_CHANGE:
	अणु
		u8 reason = (u8)(evData0);

		चयन (reason) अणु
		हाल MPI_EVENT_SAS_EXP_RC_ADDED:
			ds = "Expander Status Change: Added";
			अवरोध;
		हाल MPI_EVENT_SAS_EXP_RC_NOT_RESPONDING:
			ds = "Expander Status Change: Deleted";
			अवरोध;
		शेष:
			ds = "Expander Status Change";
			अवरोध;
		पूर्ण
		अवरोध;
	पूर्ण

	/*
	 *  MPT base "custom" events may be added here...
	 */
	शेष:
		ds = "Unknown";
		अवरोध;
	पूर्ण
	अगर (ds)
		strlcpy(evStr, ds, EVENT_DESCR_STR_SZ);


	devtprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT
	    "MPT event:(%02Xh) : %s\n",
	    ioc->name, event, evStr));

	devtverboseprपूर्णांकk(ioc, prपूर्णांकk(KERN_DEBUG MYNAM
	    ": Event data:\n"));
	क्रम (ii = 0; ii < le16_to_cpu(pEventReply->EventDataLength); ii++)
		devtverboseprपूर्णांकk(ioc, prपूर्णांकk(" %08x",
		    le32_to_cpu(pEventReply->Data[ii])));
	devtverboseprपूर्णांकk(ioc, prपूर्णांकk(KERN_DEBUG "\n"));
पूर्ण
#पूर्ण_अगर
/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/**
 *	ProcessEventNotअगरication - Route EventNotअगरicationReply to all event handlers
 *	@ioc: Poपूर्णांकer to MPT_ADAPTER काष्ठाure
 *	@pEventReply: Poपूर्णांकer to EventNotअगरication reply frame
 *	@evHandlers: Poपूर्णांकer to पूर्णांकeger, number of event handlers
 *
 *	Routes a received EventNotअगरicationReply to all currently रेजिस्टरed
 *	event handlers.
 *	Returns sum of event handlers वापस values.
 */
अटल पूर्णांक
ProcessEventNotअगरication(MPT_ADAPTER *ioc, EventNotअगरicationReply_t *pEventReply, पूर्णांक *evHandlers)
अणु
	u16 evDataLen;
	u32 evData0 = 0;
	पूर्णांक ii;
	u8 cb_idx;
	पूर्णांक r = 0;
	पूर्णांक handlers = 0;
	u8 event;

	/*
	 *  Do platक्रमm normalization of values
	 */
	event = le32_to_cpu(pEventReply->Event) & 0xFF;
	evDataLen = le16_to_cpu(pEventReply->EventDataLength);
	अगर (evDataLen) अणु
		evData0 = le32_to_cpu(pEventReply->Data[0]);
	पूर्ण

#अगर_घोषित CONFIG_FUSION_LOGGING
	अगर (evDataLen)
		mpt_display_event_info(ioc, pEventReply);
#पूर्ण_अगर

	/*
	 *  Do general / base driver event processing
	 */
	चयन(event) अणु
	हाल MPI_EVENT_EVENT_CHANGE:		/* 0A */
		अगर (evDataLen) अणु
			u8 evState = evData0 & 0xFF;

			/* CHECKME! What अगर evState unexpectedly says OFF (0)? */

			/* Update EventState field in cached IocFacts */
			अगर (ioc->facts.Function) अणु
				ioc->facts.EventState = evState;
			पूर्ण
		पूर्ण
		अवरोध;
	हाल MPI_EVENT_INTEGRATED_RAID:
		mptbase_raid_process_event_data(ioc,
		    (MpiEventDataRaid_t *)pEventReply->Data);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	/*
	 * Should this event be logged? Events are written sequentially.
	 * When buffer is full, start again at the top.
	 */
	अगर (ioc->events && (ioc->eventTypes & ( 1 << event))) अणु
		पूर्णांक idx;

		idx = ioc->eventContext % MPTCTL_EVENT_LOG_SIZE;

		ioc->events[idx].event = event;
		ioc->events[idx].eventContext = ioc->eventContext;

		क्रम (ii = 0; ii < 2; ii++) अणु
			अगर (ii < evDataLen)
				ioc->events[idx].data[ii] = le32_to_cpu(pEventReply->Data[ii]);
			अन्यथा
				ioc->events[idx].data[ii] =  0;
		पूर्ण

		ioc->eventContext++;
	पूर्ण


	/*
	 *  Call each currently रेजिस्टरed protocol event handler.
	 */
	क्रम (cb_idx = MPT_MAX_PROTOCOL_DRIVERS-1; cb_idx; cb_idx--) अणु
		अगर (MptEvHandlers[cb_idx]) अणु
			devtverboseprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT
			    "Routing Event to event handler #%d\n",
			    ioc->name, cb_idx));
			r += (*(MptEvHandlers[cb_idx]))(ioc, pEventReply);
			handlers++;
		पूर्ण
	पूर्ण
	/* FIXME?  Examine results here? */

	/*
	 *  If needed, send (a single) EventAck.
	 */
	अगर (pEventReply->AckRequired == MPI_EVENT_NOTIFICATION_ACK_REQUIRED) अणु
		devtverboseprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT
			"EventAck required\n",ioc->name));
		अगर ((ii = SendEventAck(ioc, pEventReply)) != 0) अणु
			devtverboseprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT "SendEventAck returned %d\n",
					ioc->name, ii));
		पूर्ण
	पूर्ण

	*evHandlers = handlers;
	वापस r;
पूर्ण

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/**
 *	mpt_fc_log_info - Log inक्रमmation वापसed from Fibre Channel IOC.
 *	@ioc: Poपूर्णांकer to MPT_ADAPTER काष्ठाure
 *	@log_info: U32 LogInfo reply word from the IOC
 *
 *	Refer to lsi/mpi_log_fc.h.
 */
अटल व्योम
mpt_fc_log_info(MPT_ADAPTER *ioc, u32 log_info)
अणु
	अक्षर *desc = "unknown";

	चयन (log_info & 0xFF000000) अणु
	हाल MPI_IOCLOGINFO_FC_INIT_BASE:
		desc = "FCP Initiator";
		अवरोध;
	हाल MPI_IOCLOGINFO_FC_TARGET_BASE:
		desc = "FCP Target";
		अवरोध;
	हाल MPI_IOCLOGINFO_FC_LAN_BASE:
		desc = "LAN";
		अवरोध;
	हाल MPI_IOCLOGINFO_FC_MSG_BASE:
		desc = "MPI Message Layer";
		अवरोध;
	हाल MPI_IOCLOGINFO_FC_LINK_BASE:
		desc = "FC Link";
		अवरोध;
	हाल MPI_IOCLOGINFO_FC_CTX_BASE:
		desc = "Context Manager";
		अवरोध;
	हाल MPI_IOCLOGINFO_FC_INVALID_FIELD_BYTE_OFFSET:
		desc = "Invalid Field Offset";
		अवरोध;
	हाल MPI_IOCLOGINFO_FC_STATE_CHANGE:
		desc = "State Change Info";
		अवरोध;
	पूर्ण

	prपूर्णांकk(MYIOC_s_INFO_FMT "LogInfo(0x%08x): SubClass={%s}, Value=(0x%06x)\n",
			ioc->name, log_info, desc, (log_info & 0xFFFFFF));
पूर्ण

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/**
 *	mpt_spi_log_info - Log inक्रमmation वापसed from SCSI Parallel IOC.
 *	@ioc: Poपूर्णांकer to MPT_ADAPTER काष्ठाure
 *	@log_info: U32 LogInfo word from the IOC
 *
 *	Refer to lsi/sp_log.h.
 */
अटल व्योम
mpt_spi_log_info(MPT_ADAPTER *ioc, u32 log_info)
अणु
	u32 info = log_info & 0x00FF0000;
	अक्षर *desc = "unknown";

	चयन (info) अणु
	हाल 0x00010000:
		desc = "bug! MID not found";
		अवरोध;

	हाल 0x00020000:
		desc = "Parity Error";
		अवरोध;

	हाल 0x00030000:
		desc = "ASYNC Outbound Overrun";
		अवरोध;

	हाल 0x00040000:
		desc = "SYNC Offset Error";
		अवरोध;

	हाल 0x00050000:
		desc = "BM Change";
		अवरोध;

	हाल 0x00060000:
		desc = "Msg In Overflow";
		अवरोध;

	हाल 0x00070000:
		desc = "DMA Error";
		अवरोध;

	हाल 0x00080000:
		desc = "Outbound DMA Overrun";
		अवरोध;

	हाल 0x00090000:
		desc = "Task Management";
		अवरोध;

	हाल 0x000A0000:
		desc = "Device Problem";
		अवरोध;

	हाल 0x000B0000:
		desc = "Invalid Phase Change";
		अवरोध;

	हाल 0x000C0000:
		desc = "Untagged Table Size";
		अवरोध;

	पूर्ण

	prपूर्णांकk(MYIOC_s_INFO_FMT "LogInfo(0x%08x): F/W: %s\n", ioc->name, log_info, desc);
पूर्ण

/* strings क्रम sas loginfo */
	अटल अक्षर *originator_str[] = अणु
		"IOP",						/* 00h */
		"PL",						/* 01h */
		"IR"						/* 02h */
	पूर्ण;
	अटल अक्षर *iop_code_str[] = अणु
		शून्य,						/* 00h */
		"Invalid SAS Address",				/* 01h */
		शून्य,						/* 02h */
		"Invalid Page",					/* 03h */
		"Diag Message Error",				/* 04h */
		"Task Terminated",				/* 05h */
		"Enclosure Management",				/* 06h */
		"Target Mode"					/* 07h */
	पूर्ण;
	अटल अक्षर *pl_code_str[] = अणु
		शून्य,						/* 00h */
		"Open Failure",					/* 01h */
		"Invalid Scatter Gather List",			/* 02h */
		"Wrong Relative Offset or Frame Length",	/* 03h */
		"Frame Transfer Error",				/* 04h */
		"Transmit Frame Connected Low",			/* 05h */
		"SATA Non-NCQ RW Error Bit Set",		/* 06h */
		"SATA Read Log Receive Data Error",		/* 07h */
		"SATA NCQ Fail All Commands After Error",	/* 08h */
		"SATA Error in Receive Set Device Bit FIS",	/* 09h */
		"Receive Frame Invalid Message",		/* 0Ah */
		"Receive Context Message Valid Error",		/* 0Bh */
		"Receive Frame Current Frame Error",		/* 0Ch */
		"SATA Link Down",				/* 0Dh */
		"Discovery SATA Init W IOS",			/* 0Eh */
		"Config Invalid Page",				/* 0Fh */
		"Discovery SATA Init Timeout",			/* 10h */
		"Reset",					/* 11h */
		"Abort",					/* 12h */
		"IO Not Yet Executed",				/* 13h */
		"IO Executed",					/* 14h */
		"Persistent Reservation Out Not Affiliation "
		    "Owner", 					/* 15h */
		"Open Transmit DMA Abort",			/* 16h */
		"IO Device Missing Delay Retry",		/* 17h */
		"IO Cancelled Due to Receive Error",		/* 18h */
		शून्य,						/* 19h */
		शून्य,						/* 1Ah */
		शून्य,						/* 1Bh */
		शून्य,						/* 1Ch */
		शून्य,						/* 1Dh */
		शून्य,						/* 1Eh */
		शून्य,						/* 1Fh */
		"Enclosure Management"				/* 20h */
	पूर्ण;
	अटल अक्षर *ir_code_str[] = अणु
		"Raid Action Error",				/* 00h */
		शून्य,						/* 00h */
		शून्य,						/* 01h */
		शून्य,						/* 02h */
		शून्य,						/* 03h */
		शून्य,						/* 04h */
		शून्य,						/* 05h */
		शून्य,						/* 06h */
		शून्य						/* 07h */
	पूर्ण;
	अटल अक्षर *raid_sub_code_str[] = अणु
		शून्य, 						/* 00h */
		"Volume Creation Failed: Data Passed too "
		    "Large", 					/* 01h */
		"Volume Creation Failed: Duplicate Volumes "
		    "Attempted", 				/* 02h */
		"Volume Creation Failed: Max Number "
		    "Supported Volumes Exceeded",		/* 03h */
		"Volume Creation Failed: DMA Error",		/* 04h */
		"Volume Creation Failed: Invalid Volume Type",	/* 05h */
		"Volume Creation Failed: Error Reading "
		    "MFG Page 4", 				/* 06h */
		"Volume Creation Failed: Creating Internal "
		    "Structures", 				/* 07h */
		शून्य,						/* 08h */
		शून्य,						/* 09h */
		शून्य,						/* 0Ah */
		शून्य,						/* 0Bh */
		शून्य,						/* 0Ch */
		शून्य,						/* 0Dh */
		शून्य,						/* 0Eh */
		शून्य,						/* 0Fh */
		"Activation failed: Already Active Volume", 	/* 10h */
		"Activation failed: Unsupported Volume Type", 	/* 11h */
		"Activation failed: Too Many Active Volumes", 	/* 12h */
		"Activation failed: Volume ID in Use", 		/* 13h */
		"Activation failed: Reported Failure", 		/* 14h */
		"Activation failed: Importing a Volume", 	/* 15h */
		शून्य,						/* 16h */
		शून्य,						/* 17h */
		शून्य,						/* 18h */
		शून्य,						/* 19h */
		शून्य,						/* 1Ah */
		शून्य,						/* 1Bh */
		शून्य,						/* 1Ch */
		शून्य,						/* 1Dh */
		शून्य,						/* 1Eh */
		शून्य,						/* 1Fh */
		"Phys Disk failed: Too Many Phys Disks", 	/* 20h */
		"Phys Disk failed: Data Passed too Large",	/* 21h */
		"Phys Disk failed: DMA Error", 			/* 22h */
		"Phys Disk failed: Invalid <channel:id>", 	/* 23h */
		"Phys Disk failed: Creating Phys Disk Config "
		    "Page", 					/* 24h */
		शून्य,						/* 25h */
		शून्य,						/* 26h */
		शून्य,						/* 27h */
		शून्य,						/* 28h */
		शून्य,						/* 29h */
		शून्य,						/* 2Ah */
		शून्य,						/* 2Bh */
		शून्य,						/* 2Ch */
		शून्य,						/* 2Dh */
		शून्य,						/* 2Eh */
		शून्य,						/* 2Fh */
		"Compatibility Error: IR Disabled",		/* 30h */
		"Compatibility Error: Inquiry Command Failed",	/* 31h */
		"Compatibility Error: Device not Direct Access "
		    "Device ",					/* 32h */
		"Compatibility Error: Removable Device Found",	/* 33h */
		"Compatibility Error: Device SCSI Version not "
		    "2 or Higher", 				/* 34h */
		"Compatibility Error: SATA Device, 48 BIT LBA "
		    "not Supported", 				/* 35h */
		"Compatibility Error: Device doesn't have "
		    "512 Byte Block Sizes", 			/* 36h */
		"Compatibility Error: Volume Type Check Failed", /* 37h */
		"Compatibility Error: Volume Type is "
		    "Unsupported by FW", 			/* 38h */
		"Compatibility Error: Disk Drive too Small for "
		    "use in Volume", 				/* 39h */
		"Compatibility Error: Phys Disk for Create "
		    "Volume not Found", 			/* 3Ah */
		"Compatibility Error: Too Many or too Few "
		    "Disks for Volume Type", 			/* 3Bh */
		"Compatibility Error: Disk stripe Sizes "
		    "Must be 64KB", 				/* 3Ch */
		"Compatibility Error: IME Size Limited to < 2TB", /* 3Dh */
	पूर्ण;

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/**
 *	mpt_sas_log_info - Log inक्रमmation वापसed from SAS IOC.
 *	@ioc: Poपूर्णांकer to MPT_ADAPTER काष्ठाure
 *	@log_info: U32 LogInfo reply word from the IOC
 *	@cb_idx: callback function's handle
 *
 *	Refer to lsi/mpi_log_sas.h.
 **/
अटल व्योम
mpt_sas_log_info(MPT_ADAPTER *ioc, u32 log_info, u8 cb_idx)
अणु
	जोड़ loginfo_type अणु
		u32	loginfo;
		काष्ठा अणु
			u32	subcode:16;
			u32	code:8;
			u32	originator:4;
			u32	bus_type:4;
		पूर्ण dw;
	पूर्ण;
	जोड़ loginfo_type sas_loginfo;
	अक्षर *originator_desc = शून्य;
	अक्षर *code_desc = शून्य;
	अक्षर *sub_code_desc = शून्य;

	sas_loginfo.loginfo = log_info;
	अगर ((sas_loginfo.dw.bus_type != 3 /*SAS*/) &&
	    (sas_loginfo.dw.originator < ARRAY_SIZE(originator_str)))
		वापस;

	originator_desc = originator_str[sas_loginfo.dw.originator];

	चयन (sas_loginfo.dw.originator) अणु

		हाल 0:  /* IOP */
			अगर (sas_loginfo.dw.code <
			    ARRAY_SIZE(iop_code_str))
				code_desc = iop_code_str[sas_loginfo.dw.code];
			अवरोध;
		हाल 1:  /* PL */
			अगर (sas_loginfo.dw.code <
			    ARRAY_SIZE(pl_code_str))
				code_desc = pl_code_str[sas_loginfo.dw.code];
			अवरोध;
		हाल 2:  /* IR */
			अगर (sas_loginfo.dw.code >=
			    ARRAY_SIZE(ir_code_str))
				अवरोध;
			code_desc = ir_code_str[sas_loginfo.dw.code];
			अगर (sas_loginfo.dw.subcode >=
			    ARRAY_SIZE(raid_sub_code_str))
				अवरोध;
			अगर (sas_loginfo.dw.code == 0)
				sub_code_desc =
				    raid_sub_code_str[sas_loginfo.dw.subcode];
			अवरोध;
		शेष:
			वापस;
	पूर्ण

	अगर (sub_code_desc != शून्य)
		prपूर्णांकk(MYIOC_s_INFO_FMT
			"LogInfo(0x%08x): Originator={%s}, Code={%s},"
			" SubCode={%s} cb_idx %s\n",
			ioc->name, log_info, originator_desc, code_desc,
			sub_code_desc, MptCallbacksName[cb_idx]);
	अन्यथा अगर (code_desc != शून्य)
		prपूर्णांकk(MYIOC_s_INFO_FMT
			"LogInfo(0x%08x): Originator={%s}, Code={%s},"
			" SubCode(0x%04x) cb_idx %s\n",
			ioc->name, log_info, originator_desc, code_desc,
			sas_loginfo.dw.subcode, MptCallbacksName[cb_idx]);
	अन्यथा
		prपूर्णांकk(MYIOC_s_INFO_FMT
			"LogInfo(0x%08x): Originator={%s}, Code=(0x%02x),"
			" SubCode(0x%04x) cb_idx %s\n",
			ioc->name, log_info, originator_desc,
			sas_loginfo.dw.code, sas_loginfo.dw.subcode,
			MptCallbacksName[cb_idx]);
पूर्ण

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/**
 *	mpt_iocstatus_info_config - IOCSTATUS inक्रमmation क्रम config pages
 *	@ioc: Poपूर्णांकer to MPT_ADAPTER काष्ठाure
 *	@ioc_status: U32 IOCStatus word from IOC
 *	@mf: Poपूर्णांकer to MPT request frame
 *
 *	Refer to lsi/mpi.h.
 **/
अटल व्योम
mpt_iocstatus_info_config(MPT_ADAPTER *ioc, u32 ioc_status, MPT_FRAME_HDR *mf)
अणु
	Config_t *pReq = (Config_t *)mf;
	अक्षर extend_desc[EVENT_DESCR_STR_SZ];
	अक्षर *desc = शून्य;
	u32 क्रमm;
	u8 page_type;

	अगर (pReq->Header.PageType == MPI_CONFIG_PAGETYPE_EXTENDED)
		page_type = pReq->ExtPageType;
	अन्यथा
		page_type = pReq->Header.PageType;

	/*
	 * ignore invalid page messages क्रम GET_NEXT_HANDLE
	 */
	क्रमm = le32_to_cpu(pReq->PageAddress);
	अगर (ioc_status == MPI_IOCSTATUS_CONFIG_INVALID_PAGE) अणु
		अगर (page_type == MPI_CONFIG_EXTPAGETYPE_SAS_DEVICE ||
		    page_type == MPI_CONFIG_EXTPAGETYPE_SAS_EXPANDER ||
		    page_type == MPI_CONFIG_EXTPAGETYPE_ENCLOSURE) अणु
			अगर ((क्रमm >> MPI_SAS_DEVICE_PGAD_FORM_SHIFT) ==
				MPI_SAS_DEVICE_PGAD_FORM_GET_NEXT_HANDLE)
				वापस;
		पूर्ण
		अगर (page_type == MPI_CONFIG_PAGETYPE_FC_DEVICE)
			अगर ((क्रमm & MPI_FC_DEVICE_PGAD_FORM_MASK) ==
				MPI_FC_DEVICE_PGAD_FORM_NEXT_DID)
				वापस;
	पूर्ण

	snम_लिखो(extend_desc, EVENT_DESCR_STR_SZ,
	    "type=%02Xh, page=%02Xh, action=%02Xh, form=%08Xh",
	    page_type, pReq->Header.PageNumber, pReq->Action, क्रमm);

	चयन (ioc_status) अणु

	हाल MPI_IOCSTATUS_CONFIG_INVALID_ACTION: /* 0x0020 */
		desc = "Config Page Invalid Action";
		अवरोध;

	हाल MPI_IOCSTATUS_CONFIG_INVALID_TYPE:   /* 0x0021 */
		desc = "Config Page Invalid Type";
		अवरोध;

	हाल MPI_IOCSTATUS_CONFIG_INVALID_PAGE:   /* 0x0022 */
		desc = "Config Page Invalid Page";
		अवरोध;

	हाल MPI_IOCSTATUS_CONFIG_INVALID_DATA:   /* 0x0023 */
		desc = "Config Page Invalid Data";
		अवरोध;

	हाल MPI_IOCSTATUS_CONFIG_NO_DEFAULTS:    /* 0x0024 */
		desc = "Config Page No Defaults";
		अवरोध;

	हाल MPI_IOCSTATUS_CONFIG_CANT_COMMIT:    /* 0x0025 */
		desc = "Config Page Can't Commit";
		अवरोध;
	पूर्ण

	अगर (!desc)
		वापस;

	dreplyprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT "IOCStatus(0x%04X): %s: %s\n",
	    ioc->name, ioc_status, desc, extend_desc));
पूर्ण

/**
 *	mpt_iocstatus_info - IOCSTATUS inक्रमmation वापसed from IOC.
 *	@ioc: Poपूर्णांकer to MPT_ADAPTER काष्ठाure
 *	@ioc_status: U32 IOCStatus word from IOC
 *	@mf: Poपूर्णांकer to MPT request frame
 *
 *	Refer to lsi/mpi.h.
 **/
अटल व्योम
mpt_iocstatus_info(MPT_ADAPTER *ioc, u32 ioc_status, MPT_FRAME_HDR *mf)
अणु
	u32 status = ioc_status & MPI_IOCSTATUS_MASK;
	अक्षर *desc = शून्य;

	चयन (status) अणु

/****************************************************************************/
/*  Common IOCStatus values क्रम all replies                                 */
/****************************************************************************/

	हाल MPI_IOCSTATUS_INVALID_FUNCTION: /* 0x0001 */
		desc = "Invalid Function";
		अवरोध;

	हाल MPI_IOCSTATUS_BUSY: /* 0x0002 */
		desc = "Busy";
		अवरोध;

	हाल MPI_IOCSTATUS_INVALID_SGL: /* 0x0003 */
		desc = "Invalid SGL";
		अवरोध;

	हाल MPI_IOCSTATUS_INTERNAL_ERROR: /* 0x0004 */
		desc = "Internal Error";
		अवरोध;

	हाल MPI_IOCSTATUS_RESERVED: /* 0x0005 */
		desc = "Reserved";
		अवरोध;

	हाल MPI_IOCSTATUS_INSUFFICIENT_RESOURCES: /* 0x0006 */
		desc = "Insufficient Resources";
		अवरोध;

	हाल MPI_IOCSTATUS_INVALID_FIELD: /* 0x0007 */
		desc = "Invalid Field";
		अवरोध;

	हाल MPI_IOCSTATUS_INVALID_STATE: /* 0x0008 */
		desc = "Invalid State";
		अवरोध;

/****************************************************************************/
/*  Config IOCStatus values                                                 */
/****************************************************************************/

	हाल MPI_IOCSTATUS_CONFIG_INVALID_ACTION: /* 0x0020 */
	हाल MPI_IOCSTATUS_CONFIG_INVALID_TYPE:   /* 0x0021 */
	हाल MPI_IOCSTATUS_CONFIG_INVALID_PAGE:   /* 0x0022 */
	हाल MPI_IOCSTATUS_CONFIG_INVALID_DATA:   /* 0x0023 */
	हाल MPI_IOCSTATUS_CONFIG_NO_DEFAULTS:    /* 0x0024 */
	हाल MPI_IOCSTATUS_CONFIG_CANT_COMMIT:    /* 0x0025 */
		mpt_iocstatus_info_config(ioc, status, mf);
		अवरोध;

/****************************************************************************/
/*  SCSIIO Reply (SPI, FCP, SAS) initiator values                           */
/*                                                                          */
/*  Look at mptscsih_iocstatus_info_scsiio in mptscsih.c */
/*                                                                          */
/****************************************************************************/

	हाल MPI_IOCSTATUS_SCSI_RECOVERED_ERROR: /* 0x0040 */
	हाल MPI_IOCSTATUS_SCSI_DATA_UNDERRUN: /* 0x0045 */
	हाल MPI_IOCSTATUS_SCSI_INVALID_BUS: /* 0x0041 */
	हाल MPI_IOCSTATUS_SCSI_INVALID_TARGETID: /* 0x0042 */
	हाल MPI_IOCSTATUS_SCSI_DEVICE_NOT_THERE: /* 0x0043 */
	हाल MPI_IOCSTATUS_SCSI_DATA_OVERRUN: /* 0x0044 */
	हाल MPI_IOCSTATUS_SCSI_IO_DATA_ERROR: /* 0x0046 */
	हाल MPI_IOCSTATUS_SCSI_PROTOCOL_ERROR: /* 0x0047 */
	हाल MPI_IOCSTATUS_SCSI_TASK_TERMINATED: /* 0x0048 */
	हाल MPI_IOCSTATUS_SCSI_RESIDUAL_MISMATCH: /* 0x0049 */
	हाल MPI_IOCSTATUS_SCSI_TASK_MGMT_FAILED: /* 0x004A */
	हाल MPI_IOCSTATUS_SCSI_IOC_TERMINATED: /* 0x004B */
	हाल MPI_IOCSTATUS_SCSI_EXT_TERMINATED: /* 0x004C */
		अवरोध;

/****************************************************************************/
/*  SCSI Target values                                                      */
/****************************************************************************/

	हाल MPI_IOCSTATUS_TARGET_PRIORITY_IO: /* 0x0060 */
		desc = "Target: Priority IO";
		अवरोध;

	हाल MPI_IOCSTATUS_TARGET_INVALID_PORT: /* 0x0061 */
		desc = "Target: Invalid Port";
		अवरोध;

	हाल MPI_IOCSTATUS_TARGET_INVALID_IO_INDEX: /* 0x0062 */
		desc = "Target Invalid IO Index:";
		अवरोध;

	हाल MPI_IOCSTATUS_TARGET_ABORTED: /* 0x0063 */
		desc = "Target: Aborted";
		अवरोध;

	हाल MPI_IOCSTATUS_TARGET_NO_CONN_RETRYABLE: /* 0x0064 */
		desc = "Target: No Conn Retryable";
		अवरोध;

	हाल MPI_IOCSTATUS_TARGET_NO_CONNECTION: /* 0x0065 */
		desc = "Target: No Connection";
		अवरोध;

	हाल MPI_IOCSTATUS_TARGET_XFER_COUNT_MISMATCH: /* 0x006A */
		desc = "Target: Transfer Count Mismatch";
		अवरोध;

	हाल MPI_IOCSTATUS_TARGET_STS_DATA_NOT_SENT: /* 0x006B */
		desc = "Target: STS Data not Sent";
		अवरोध;

	हाल MPI_IOCSTATUS_TARGET_DATA_OFFSET_ERROR: /* 0x006D */
		desc = "Target: Data Offset Error";
		अवरोध;

	हाल MPI_IOCSTATUS_TARGET_TOO_MUCH_WRITE_DATA: /* 0x006E */
		desc = "Target: Too Much Write Data";
		अवरोध;

	हाल MPI_IOCSTATUS_TARGET_IU_TOO_SHORT: /* 0x006F */
		desc = "Target: IU Too Short";
		अवरोध;

	हाल MPI_IOCSTATUS_TARGET_ACK_NAK_TIMEOUT: /* 0x0070 */
		desc = "Target: ACK NAK Timeout";
		अवरोध;

	हाल MPI_IOCSTATUS_TARGET_NAK_RECEIVED: /* 0x0071 */
		desc = "Target: Nak Received";
		अवरोध;

/****************************************************************************/
/*  Fibre Channel Direct Access values                                      */
/****************************************************************************/

	हाल MPI_IOCSTATUS_FC_ABORTED: /* 0x0066 */
		desc = "FC: Aborted";
		अवरोध;

	हाल MPI_IOCSTATUS_FC_RX_ID_INVALID: /* 0x0067 */
		desc = "FC: RX ID Invalid";
		अवरोध;

	हाल MPI_IOCSTATUS_FC_DID_INVALID: /* 0x0068 */
		desc = "FC: DID Invalid";
		अवरोध;

	हाल MPI_IOCSTATUS_FC_NODE_LOGGED_OUT: /* 0x0069 */
		desc = "FC: Node Logged Out";
		अवरोध;

	हाल MPI_IOCSTATUS_FC_EXCHANGE_CANCELED: /* 0x006C */
		desc = "FC: Exchange Canceled";
		अवरोध;

/****************************************************************************/
/*  LAN values                                                              */
/****************************************************************************/

	हाल MPI_IOCSTATUS_LAN_DEVICE_NOT_FOUND: /* 0x0080 */
		desc = "LAN: Device not Found";
		अवरोध;

	हाल MPI_IOCSTATUS_LAN_DEVICE_FAILURE: /* 0x0081 */
		desc = "LAN: Device Failure";
		अवरोध;

	हाल MPI_IOCSTATUS_LAN_TRANSMIT_ERROR: /* 0x0082 */
		desc = "LAN: Transmit Error";
		अवरोध;

	हाल MPI_IOCSTATUS_LAN_TRANSMIT_ABORTED: /* 0x0083 */
		desc = "LAN: Transmit Aborted";
		अवरोध;

	हाल MPI_IOCSTATUS_LAN_RECEIVE_ERROR: /* 0x0084 */
		desc = "LAN: Receive Error";
		अवरोध;

	हाल MPI_IOCSTATUS_LAN_RECEIVE_ABORTED: /* 0x0085 */
		desc = "LAN: Receive Aborted";
		अवरोध;

	हाल MPI_IOCSTATUS_LAN_PARTIAL_PACKET: /* 0x0086 */
		desc = "LAN: Partial Packet";
		अवरोध;

	हाल MPI_IOCSTATUS_LAN_CANCELED: /* 0x0087 */
		desc = "LAN: Canceled";
		अवरोध;

/****************************************************************************/
/*  Serial Attached SCSI values                                             */
/****************************************************************************/

	हाल MPI_IOCSTATUS_SAS_SMP_REQUEST_FAILED: /* 0x0090 */
		desc = "SAS: SMP Request Failed";
		अवरोध;

	हाल MPI_IOCSTATUS_SAS_SMP_DATA_OVERRUN: /* 0x0090 */
		desc = "SAS: SMP Data Overrun";
		अवरोध;

	शेष:
		desc = "Others";
		अवरोध;
	पूर्ण

	अगर (!desc)
		वापस;

	dreplyprपूर्णांकk(ioc, prपूर्णांकk(MYIOC_s_DEBUG_FMT "IOCStatus(0x%04X): %s\n",
	    ioc->name, status, desc));
पूर्ण

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
EXPORT_SYMBOL(mpt_attach);
EXPORT_SYMBOL(mpt_detach);
#अगर_घोषित CONFIG_PM
EXPORT_SYMBOL(mpt_resume);
EXPORT_SYMBOL(mpt_suspend);
#पूर्ण_अगर
EXPORT_SYMBOL(ioc_list);
EXPORT_SYMBOL(mpt_रेजिस्टर);
EXPORT_SYMBOL(mpt_deरेजिस्टर);
EXPORT_SYMBOL(mpt_event_रेजिस्टर);
EXPORT_SYMBOL(mpt_event_deरेजिस्टर);
EXPORT_SYMBOL(mpt_reset_रेजिस्टर);
EXPORT_SYMBOL(mpt_reset_deरेजिस्टर);
EXPORT_SYMBOL(mpt_device_driver_रेजिस्टर);
EXPORT_SYMBOL(mpt_device_driver_deरेजिस्टर);
EXPORT_SYMBOL(mpt_get_msg_frame);
EXPORT_SYMBOL(mpt_put_msg_frame);
EXPORT_SYMBOL(mpt_put_msg_frame_hi_pri);
EXPORT_SYMBOL(mpt_मुक्त_msg_frame);
EXPORT_SYMBOL(mpt_send_handshake_request);
EXPORT_SYMBOL(mpt_verअगरy_adapter);
EXPORT_SYMBOL(mpt_GetIocState);
EXPORT_SYMBOL(mpt_prपूर्णांक_ioc_summary);
EXPORT_SYMBOL(mpt_HardResetHandler);
EXPORT_SYMBOL(mpt_config);
EXPORT_SYMBOL(mpt_findImVolumes);
EXPORT_SYMBOL(mpt_alloc_fw_memory);
EXPORT_SYMBOL(mpt_मुक्त_fw_memory);
EXPORT_SYMBOL(mptbase_sas_persist_operation);
EXPORT_SYMBOL(mpt_raid_phys_disk_pg0);

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/**
 *	fusion_init - Fusion MPT base driver initialization routine.
 *
 *	Returns 0 क्रम success, non-zero क्रम failure.
 */
अटल पूर्णांक __init
fusion_init(व्योम)
अणु
	u8 cb_idx;

	show_mpपंचांगod_ver(my_NAME, my_VERSION);
	prपूर्णांकk(KERN_INFO COPYRIGHT "\n");

	क्रम (cb_idx = 0; cb_idx < MPT_MAX_PROTOCOL_DRIVERS; cb_idx++) अणु
		MptCallbacks[cb_idx] = शून्य;
		MptDriverClass[cb_idx] = MPTUNKNOWN_DRIVER;
		MptEvHandlers[cb_idx] = शून्य;
		MptResetHandlers[cb_idx] = शून्य;
	पूर्ण

	/*  Register ourselves (mptbase) in order to facilitate
	 *  EventNotअगरication handling.
	 */
	mpt_base_index = mpt_रेजिस्टर(mptbase_reply, MPTBASE_DRIVER,
	    "mptbase_reply");

	/* Register क्रम hard reset handling callbacks.
	 */
	mpt_reset_रेजिस्टर(mpt_base_index, mpt_ioc_reset);

#अगर_घोषित CONFIG_PROC_FS
	(व्योम) procmpt_create();
#पूर्ण_अगर
	वापस 0;
पूर्ण

/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
/**
 *	fusion_निकास - Perक्रमm driver unload cleanup.
 *
 *	This routine मुक्तs all resources associated with each MPT adapter
 *	and हटाओs all %MPT_PROCFS_MPTBASEसूची entries.
 */
अटल व्योम __निकास
fusion_निकास(व्योम)
अणु

	mpt_reset_deरेजिस्टर(mpt_base_index);

#अगर_घोषित CONFIG_PROC_FS
	procmpt_destroy();
#पूर्ण_अगर
पूर्ण

module_init(fusion_init);
module_निकास(fusion_निकास);
